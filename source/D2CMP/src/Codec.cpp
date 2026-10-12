#include "Codec.h"

#include <climits>
#include <cstdio>
#include <cstring>

#include <D2BitManip.h>
#include <Fog.h>


constexpr int DCC_MAX_FRAMES = 256;
constexpr int DCC_PIXEL_BUFFER_SIZE = 5625;
constexpr int DCC_PIXEL_VALUES_SIZE = 0x40000;
constexpr int DCC_DIRECTION_IMAGE_SIZE = 120000;
constexpr int DCC_CELL_SIZE = 4;

// Number of bits of the fields of the frame headers
//D2CMP.0x6FE0B940
static const uint32_t gaDccFieldBitWidths[16] = { 0, 1, 2, 4, 6, 8, 10, 12, 14, 16, 20, 24, 26, 28, 30, 32 };

static D2DccFrameStrc sgtDccFrames[DCC_MAX_FRAMES];					//D2CMP.0x6FE12D18
static D2DccCellStrc sgtDccPixelBuffer[DCC_PIXEL_BUFFER_SIZE];		//D2CMP.0x6FE15918
static uint8_t sgDccPixelValues[DCC_PIXEL_VALUES_SIZE];				//D2CMP.0x6FE31090
static uint8_t sgDccDirectionImage[DCC_DIRECTION_IMAGE_SIZE];		//D2CMP.0x6FE71090
static CRITICAL_SECTION sgtCodecLock;								//D2CMP.0x6FE8E550
static BOOL sgbCodecLockInitialized;								//D2CMP.0x6FE8E568


// Inlined helper
static uint32_t BITSTREAM_GetPosition(const D2DccBitstreamStrc* pBitstream)
{
	return (((const uint8_t*)pBitstream->pCurrent - pBitstream->pStart) >> 2 << 5) + pBitstream->nBitOffset;
}

//D2CMP.0x6FDF4F10
static void __fastcall BITSTREAM_Skip(D2DccBitstreamStrc* pBitstream, int nBits)
{
	const int nTotal = pBitstream->nBitOffset + nBits;
	pBitstream->nBitOffset = nTotal & 0x1F;
	pBitstream->pCurrent += nTotal / 32;
}

//D2CMP.0x6FDF4F40
static void __fastcall BITSTREAM_AlignToByte(D2DccBitstreamStrc* pBitstream)
{
	const uint32_t nBits = (pBitstream->nBitOffset + 7) & ~7;
	pBitstream->nBitOffset = nBits & 0x1F;
	pBitstream->pCurrent += nBits >> 5;
}

// Bit masks of the n lowest bits
//D2CMP.0x6FE0BA00
static uint32_t BITSTREAM_LowMask(uint32_t nBits)
{
	return nBits >= 32 ? 0xFFFFFFFF : ((1u << nBits) - 1);
}

//D2CMP.0x6FDF4F60
static uint32_t __fastcall BITSTREAM_ReadBits(D2DccBitstreamStrc* pBitstream, uint32_t nBits)
{
	if (!nBits)
	{
		return 0;
	}

	const uint32_t nAvailable = 32 - pBitstream->nBitOffset;
	if (nBits <= nAvailable)
	{
		const uint32_t nValue = BITSTREAM_LowMask(nBits) & (*pBitstream->pCurrent >> pBitstream->nBitOffset);
		pBitstream->nBitOffset += nBits;
		if (pBitstream->nBitOffset == 32)
		{
			++pBitstream->pCurrent;
			pBitstream->nBitOffset = 0;
		}
		return nValue;
	}

	const uint32_t nLow = BITSTREAM_LowMask(nAvailable) & (*pBitstream->pCurrent >> pBitstream->nBitOffset);
	++pBitstream->pCurrent;
	pBitstream->nBitOffset = nBits - nAvailable;
	const uint32_t nHigh = BITSTREAM_LowMask(pBitstream->nBitOffset) & *pBitstream->pCurrent;
	return nLow | (nHigh << nAvailable);
}

// Inlined helper
static int32_t BITSTREAM_ReadSignedBits(D2DccBitstreamStrc* pBitstream, uint32_t nBits)
{
	uint32_t nValue = BITSTREAM_ReadBits(pBitstream, nBits);
	// Note: the original game reads past the end of its sign extension table for 32 bits fields
	if (nBits && nBits < 32 && (nValue & (1u << (nBits - 1))))
	{
		nValue |= ~BITSTREAM_LowMask(nBits);
	}
	return (int32_t)nValue;
}

//D2CMP.0x6FDF3EE0
BOOL __fastcall CODEC_EncodeFrame(D2DccFrameStrc* pFrame, D2GfxCellStrc* pCel, uint8_t* pDest)
{
	int nStride = pFrame->nStride;
	uint8_t* pRow = pFrame->pImage;
	if (!pFrame->bBottomUp)
	{
		nStride = -nStride;
		pRow += (pFrame->nHeight - 1) * pFrame->nStride;
	}

	for (int nY = 0; nY < pFrame->nHeight; ++nY)
	{
		int nX = 0;
		while (nX < pFrame->nWidth)
		{
			int nStart = nX;
			while (nX < pFrame->nWidth && !pRow[nX])
			{
				++nX;
			}

			if (nX >= pFrame->nWidth)
			{
				break;
			}

			while (nStart < nX)
			{
				int nCount = nX - nStart;
				if (nCount > 0x7F)
				{
					nCount = 0x7F;
				}
				*pDest++ = (uint8_t)nCount | 0x80;
				nStart += nCount;
			}

			nStart = nX;
			while (nX < pFrame->nWidth && pRow[nX])
			{
				++nX;
			}

			while (nStart < nX)
			{
				int nCount = nX - nStart;
				if (nCount > 0x7F)
				{
					nCount = 0x7F;
				}
				*pDest++ = (uint8_t)nCount;
				memcpy(pDest, &pRow[nStart], nCount);
				pDest += nCount;
				nStart += nCount;
			}
		}

		*pDest++ = 0x80;
		pRow += nStride;
	}

	if (pDest != &pCel->pPixels[pCel->dwLength])
	{
		FOG_Trace("Sprite Decompression Error -- EXP: (dest != &pCel->bControlData[pCel->dwControlSize])   VALUE: dest == %x   &pCel->bControlData[pCel->dwControlSize] == %x   FILE: %s   LINE: %d", pDest, &pCel->pPixels[pCel->dwLength], __FILE__, __LINE__);
		return FALSE;
	}

	return TRUE;
}

#pragma pack(push, 1)
struct D2DccFileHeaderStrc
{
	uint8_t nSignature;							//0x00
	uint8_t nVersion;							//0x01
	uint8_t nDirections;						//0x02
	uint32_t nFramesPerDirection;				//0x03
	uint32_t nTag;								//0x07
	uint32_t nFinalDc6Size;						//0x0B
};
#pragma pack(pop)

//D2CMP.0x6FDF4050
BOOL __fastcall CODEC_ReadCelDataHeader(const char* szPath, D2CelDataStrc* ptCelData)
{
	HSFILE hFile = nullptr;
	FOG_FOpenFile(szPath, &hFile);
	if (!hFile)
	{
		return FALSE;
	}

	D2DccFileHeaderStrc tHeader = {};
	int nBytesRead = 0;
	if (!FOG_FReadFile(hFile, &tHeader, sizeof(tHeader), &nBytesRead, 0, 0, 0) || nBytesRead != sizeof(tHeader) || tHeader.nSignature != 0x74)
	{
		FOG_FCloseFile(hFile);
		return FALSE;
	}

	ptCelData->tHeader.dwFlags = tHeader.nTag;
	ptCelData->tHeader.dwVersion = tHeader.nVersion;
	ptCelData->tHeader.eFormat = 0;
	ptCelData->tHeader.dwFramesPerDirection = tHeader.nFramesPerDirection;
	ptCelData->tHeader.dwNumDirections = tHeader.nDirections;
	D2_ASSERT(tHeader.nDirections <= 32); // header.spriteDirections <= 32

	const int nOffsetsSize = sizeof(int32_t) * tHeader.nDirections;
	if (!FOG_FReadFile(hFile, ptCelData->nOffsets, nOffsetsSize, &nBytesRead, 0, 0, 0) || nBytesRead != nOffsetsSize)
	{
		FOG_FCloseFile(hFile);
		return FALSE;
	}

	ptCelData->nOffsets[tHeader.nDirections] = FOG_FGetFileSize(hFile, nullptr);
	FOG_FCloseFile(hFile);
	ptCelData->bFlags |= CELDATAFLAG_DCC;
	return TRUE;
}

//D2CMP.0x6FDF4FE0
static BOOL __fastcall CODEC_NextCell(D2DccDirectionStrc* pDirection, D2DccCellIteratorStrc* pIterator)
{
	// Next cell of the row
	pIterator->nX += pIterator->nCellWidth;
	if (pIterator->nX < pIterator->nFrameWidth)
	{
		pIterator->nPixelOffset += pIterator->nCellWidth;
		++pIterator->nCell;
		if (pIterator->nX + 5 >= pIterator->nFrameWidth)
		{
			pIterator->nCellWidth = pIterator->nFrameWidth - pIterator->nX;
		}
		else
		{
			pIterator->nCellWidth = DCC_CELL_SIZE;
		}
		return TRUE;
	}

	// Next row
	pIterator->nY += pIterator->nCellHeight;
	if (pIterator->nY < pIterator->nFrameHeight)
	{
		const int nFirstCellWidth = -(pIterator->nFrameX % DCC_CELL_SIZE);
		pIterator->nX = 0;
		if (nFirstCellWidth + 5 >= pIterator->nFrameWidth)
		{
			pIterator->nCellWidth = pIterator->nFrameWidth;
		}
		else
		{
			pIterator->nCellWidth = nFirstCellWidth + DCC_CELL_SIZE;
		}

		pIterator->nRowOffset += pIterator->nFrameStride * pIterator->nCellHeight;
		pIterator->nPixelOffset = pIterator->nRowOffset;
		pIterator->nRowCell += pDirection->nCellsPerRow;
		pIterator->nCell = pIterator->nRowCell;
		if (pIterator->nY + 5 >= pIterator->nFrameHeight)
		{
			pIterator->nCellHeight = pIterator->nFrameHeight - pIterator->nY;
		}
		else
		{
			pIterator->nCellHeight = DCC_CELL_SIZE;
		}
		return TRUE;
	}

	// Next frame
	++pIterator->nFrame;
	while (true)
	{
		if (pIterator->nFrame >= pDirection->nFrames)
		{
			return FALSE;
		}

		const D2DccFrameStrc* pFrame = &pDirection->pFrames[pIterator->nFrame];
		if (pFrame->nWidth && pFrame->nHeight)
		{
			break;
		}
		++pIterator->nFrame;
	}

	const D2DccFrameStrc* pFrame = &pDirection->pFrames[pIterator->nFrame];
	pIterator->nFrameWidth = pFrame->nWidth;
	pIterator->nFrameHeight = pFrame->nHeight;
	pIterator->nFrameX = pFrame->nXOffset - pDirection->nMinX;
	pIterator->nFrameY = pFrame->nYOffset - pDirection->nMinY - (pFrame->bBottomUp ? 0 : pFrame->nHeight);
	pIterator->pFrameImage = pFrame->pImage;
	pIterator->nFrameStride = pFrame->nStride;
	pIterator->nRowCell = pIterator->nFrameX / DCC_CELL_SIZE + pIterator->nFrameY / DCC_CELL_SIZE * pDirection->nCellsPerRow;
	pIterator->nX = 0;
	pIterator->nY = 0;
	pIterator->nRowOffset = 0;
	pIterator->nCell = pIterator->nRowCell;
	pIterator->nPixelOffset = 0;

	const int nFirstCellWidth = -(pIterator->nFrameX % DCC_CELL_SIZE);
	const int nFirstCellHeight = -(pIterator->nFrameY % DCC_CELL_SIZE);
	if (nFirstCellWidth + 5 >= pIterator->nFrameWidth)
	{
		pIterator->nCellWidth = pIterator->nFrameWidth;
	}
	else
	{
		pIterator->nCellWidth = nFirstCellWidth + DCC_CELL_SIZE;
	}

	if (nFirstCellHeight + 5 >= pIterator->nFrameHeight)
	{
		pIterator->nCellHeight = pIterator->nFrameHeight;
	}
	else
	{
		pIterator->nCellHeight = nFirstCellHeight + DCC_CELL_SIZE;
	}
	return TRUE;
}

//D2CMP.0x6FDF51B0
static BOOL __fastcall CODEC_FirstCell(D2DccDirectionStrc* pDirection, D2DccCellIteratorStrc* pIterator)
{
	if (!pDirection->nFrames)
	{
		return FALSE;
	}

	memset(pIterator, 0x00, sizeof(*pIterator));
	pIterator->nFrame = -1;
	return CODEC_NextCell(pDirection, pIterator);
}

//D2CMP.0x6FDF51E0
static void __fastcall CODEC_BuildPixelValuesMap(const uint8_t* pUsedPixelValues, uint8_t* pPixelMap, uint8_t* pPalette)
{
	int nCount = 0;
	for (int i = 0; i < 256; ++i)
	{
		if (pUsedPixelValues[i])
		{
			pPixelMap[i] = (uint8_t)nCount;
			pPalette[nCount] = (uint8_t)i;
			++nCount;
		}
	}

	*(int*)&pPixelMap[256] = 256;
	*(int*)&pPalette[256] = nCount;
}

//D2CMP.0x6FDF5220
static void __fastcall CODEC_DecodeCell(D2DccCellStrc* pCell, D2DccBitstreamStrc* pBitstream, D2DccCellStrc* pPreviousCell, D2DccBitstreamStrc* pEqualCellBitstream, uint8_t** ppPixelValues)
{
	if (pEqualCellBitstream && pPreviousCell->pPixelValues && BITSTREAM_ReadBits(pEqualCellBitstream, 1))
	{
		if (pCell->nWidth == pPreviousCell->nWidth && pCell->nHeight == pPreviousCell->nHeight)
		{
			if (pCell->pDest == pPreviousCell->pDest)
			{
				return;
			}

			// Copy the previous cell through a temporary buffer, as both cells may overlap
			uint8_t aTemp[DCC_CELL_SIZE * (DCC_CELL_SIZE + 1)];
			const uint8_t* pSrc = pPreviousCell->pDest;
			for (int nY = 0; nY < pCell->nHeight; ++nY)
			{
				memcpy(&aTemp[nY * (DCC_CELL_SIZE + 1)], pSrc, pCell->nWidth);
				pSrc += pPreviousCell->nStride;
			}

			uint8_t* pDest = pCell->pDest;
			for (int nY = 0; nY < pCell->nHeight; ++nY)
			{
				memcpy(pDest, &aTemp[nY * (DCC_CELL_SIZE + 1)], pCell->nWidth);
				pDest += pCell->nStride;
			}
		}
		else
		{
			uint8_t* pDest = pCell->pDest;
			for (int nY = 0; nY < pCell->nHeight; ++nY)
			{
				memset(pDest, 0x00, pCell->nWidth);
				pDest += pCell->nStride;
			}
		}
		return;
	}

	// The 4 pixel values of the cell are sorted, a repeated value marks the end of the values
	const uint8_t* pValues = pCell->pPixelValues;
	int nBits = 0;
	for (int i = 1; pValues[i] != pValues[i - 1]; )
	{
		++nBits;
		i = 1 << nBits;
		if (i + 1 > 4)
		{
			break;
		}
	}

	uint8_t* pDest = pCell->pDest;
	if (!nBits)
	{
		const uint8_t nColor = (*ppPixelValues)[0];
		for (int nY = 0; nY < pCell->nHeight; ++nY)
		{
			memset(pDest, nColor, pCell->nWidth);
			pDest += pCell->nStride;
		}
	}
	else
	{
		for (int nY = 0; nY < pCell->nHeight; ++nY)
		{
			for (int nX = 0; nX < pCell->nWidth; ++nX)
			{
				pDest[nX] = (*ppPixelValues)[BITSTREAM_ReadBits(pBitstream, nBits)];
			}
			pDest += pCell->nStride;
		}
	}

	*ppPixelValues += DCC_CELL_SIZE;
}

// Inlined helper
static bool CODEC_IsPixelDecoded(uint32_t nDecodeMask, int nPosition)
{
	return (nDecodeMask & gdwBitMasks[nPosition & 0x1F]) != 0;
}

//D2CMP.0x6FDF5520
static void __fastcall CODEC_FillPixelBuffer(D2DccDirectionStrc* pDirection, D2DccCellStrc* pPixelBuffer, D2DccBitstreamStrc* pEqualCellBitstream, D2DccBitstreamStrc* pPixelMaskBitstream, D2DccBitstreamStrc* pEncodingTypeBitstream, D2DccBitstreamStrc* pRawPixelBitstream, D2DccBitstreamStrc* pPixelCodeBitstream, D2DccPixelValuesStrc* pPixelValues, uint32_t* pBitsConsumed)
{
	const uint32_t nStartPosition = BITSTREAM_GetPosition(pPixelCodeBitstream);
	uint8_t* pCursor = pPixelValues->pData;

	D2DccCellIteratorStrc tIterator;
	if (pDirection->nFrames && CODEC_FirstCell(pDirection, &tIterator))
	{
		do
		{
			D2DccCellStrc* pEntry = &pPixelBuffer[tIterator.nCell];
			const uint8_t* pPrevious = pEntry->pPixelValues;
			uint32_t nPixelMask = 0xF;
			if (pPrevious)
			{
				if (pEqualCellBitstream && BITSTREAM_ReadBits(pEqualCellBitstream, 1))
				{
					continue;
				}
				nPixelMask = BITSTREAM_ReadBits(pPixelMaskBitstream, 4);
			}

			BOOL bRawEncoding = FALSE;
			if (nPixelMask && pEncodingTypeBitstream)
			{
				bRawEncoding = BITSTREAM_ReadBits(pEncodingTypeBitstream, 1);
			}

			// Positions above the cell size are flagged so that searches always end
			const uint32_t nDecodeMask = nPixelMask | 0xFFFFFFF0;
			uint8_t nLastPixel = 0;
			int nPosition = DCC_CELL_SIZE;
			while (nPosition)
			{
				--nPosition;
				if (!CODEC_IsPixelDecoded(nDecodeMask, nPosition))
				{
					pCursor[nPosition] = pPrevious[nPosition];
					continue;
				}

				uint8_t nPixel;
				if (bRawEncoding)
				{
					nPixel = (uint8_t)BITSTREAM_ReadBits(pRawPixelBitstream, 8);
				}
				else
				{
					nPixel = nLastPixel;
					uint32_t nDisplacement;
					do
					{
						nDisplacement = BITSTREAM_ReadBits(pPixelCodeBitstream, 4);
						nPixel += (uint8_t)nDisplacement;
					}
					while (nDisplacement == 15);
				}

				pCursor[nPosition] = nPixel;
				if (nLastPixel != nPixel)
				{
					nLastPixel = nPixel;
					continue;
				}

				// A repeated pixel ends the decoding: move the decoded pixels to the lowest positions
				int nSrc = nPosition;
				int nDst = -1;
				while (true)
				{
					do
					{
						++nSrc;
					}
					while (!CODEC_IsPixelDecoded(nDecodeMask, nSrc));

					if (nSrc >= DCC_CELL_SIZE)
					{
						break;
					}

					do
					{
						++nDst;
					}
					while (!CODEC_IsPixelDecoded(nDecodeMask, nDst));

					pCursor[nDst] = pCursor[nSrc];
				}

				// The other positions to decode are transparent
				while (true)
				{
					do
					{
						++nDst;
					}
					while (!CODEC_IsPixelDecoded(nDecodeMask, nDst));

					if (nDst >= DCC_CELL_SIZE)
					{
						break;
					}

					pCursor[nDst] = 0;
				}

				// Remaining positions which were not decoded use the previous pixels
				while (nPosition)
				{
					--nPosition;
					if (!CODEC_IsPixelDecoded(nDecodeMask, nPosition))
					{
						pCursor[nPosition] = pPrevious[nPosition];
					}
				}
				break;
			}

			pEntry->pPixelValues = pCursor;
			pCursor += DCC_CELL_SIZE;
		}
		while (CODEC_NextCell(pDirection, &tIterator));
	}

	*pBitsConsumed = BITSTREAM_GetPosition(pPixelCodeBitstream) - nStartPosition;
	pPixelValues->nCount = pCursor - pPixelValues->pData;
}

//D2CMP.0x6FDF59E0
static void __fastcall CODEC_RemapPixelValues(D2DccPixelValuesStrc* pPixelValues, const uint8_t* pPalette)
{
	for (uint32_t i = 0; i < pPixelValues->nCount; ++i)
	{
		pPixelValues->pData[i] = pPalette[pPixelValues->pData[i]];
	}
}

//D2CMP.0x6FDF5A10
void __fastcall CODEC_InitLock()
{
	if (!sgbCodecLockInitialized)
	{
		InitializeCriticalSection(&sgtCodecLock);
		sgbCodecLockInitialized = TRUE;
	}
}

//D2CMP.0x6FDF5A30
void __fastcall CODEC_DestroyLock()
{
	if (sgbCodecLockInitialized)
	{
		EnterCriticalSection(&sgtCodecLock);
		sgbCodecLockInitialized = FALSE;
		DeleteCriticalSection(&sgtCodecLock);
	}
}

// Inlined helper
static void CODEC_ReportDecompressionError(const uint8_t* pData, int nDataLength, int nDirection, int nFrame, const D2GfxCellStrc* pCel, const char* szFileName)
{
	FOG_Trace("Sprite Decompression Error -- File:%s", szFileName);
	FOG_Trace("Dir:%d  Cell#:%d  Wid:%d  Ht:%d  OffX:%d  OffY:%d", nDirection, nFrame, pCel->dwWidth, pCel->dwHeight, pCel->nXOffset, pCel->nYOffset);
	FOG_Trace("ControlSize:%d", pCel->dwLength);

	int nChecksum = 0;
	for (int i = 0; i < nDataLength; ++i)
	{
		nChecksum += pData[i];
	}
	FOG_Trace("Buffer -- Len:%d  Checksum:%d", nDataLength, nChecksum);

	char szMessage[512];
	sprintf(szMessage, "Error decompressing sprite - Possible corruption in data file: %s", szFileName);
	FOG_DisplayHalt(szMessage, __FILE__, __LINE__);
	exit(-1);
}

//D2CMP.0x6FDF4160
uint8_t* __fastcall CODEC_DecodeDirections(const uint8_t* pData, void* pMemPool, int nDataLength, D2CelDataStrc* ptCelData, D2GfxBlockStrc* ptGfxBlock, int nFirstDirection, int nDirections, uint32_t* pDecodedSize, const char* szFileName)
{
	EnterCriticalSection(&sgtCodecLock);

	D2DccBitstreamStrc tBitstream = { pData, (const uint32_t*)pData, (uint32_t)nDataLength * 8, 0 };

	D2DccHeaderInfoStrc tHeader = {};
	tHeader.dwVersion = ptCelData->tHeader.dwVersion;
	tHeader.dwNumDirections = ptCelData->tHeader.dwNumDirections;
	tHeader.dwFramesPerDirection = ptCelData->tHeader.dwFramesPerDirection;
	tHeader.dwFlags = ptCelData->tHeader.dwFlags;

	// Each direction starts with the size of its decoded cels
	*pDecodedSize = 0;
	const int nLastDirection = nFirstDirection + nDirections;
	for (int nDirection = nFirstDirection; nDirection < nLastDirection; ++nDirection)
	{
		const uint32_t nDecodedDirectionSize = *(const uint32_t*)&pData[ptCelData->nOffsets[nDirection] - ptCelData->nOffsets[nFirstDirection]];
		ptGfxBlock->nOffsets[nDirection] = *pDecodedSize;
		*pDecodedSize += nDecodedDirectionSize;
	}

	uint8_t* pDecoded = (uint8_t*)D2_ALLOC_POOL(pMemPool, *pDecodedSize);
	uint8_t* pCurrentCel = pDecoded;

	for (int nDirection = nFirstDirection; nDirection < nLastDirection; ++nDirection)
	{
		BITSTREAM_Skip(&tBitstream, 32);
		const uint32_t nCompressionFlags = BITSTREAM_ReadBits(&tBitstream, 2);
		const uint32_t nFieldSizes = BITSTREAM_ReadBits(&tBitstream, 28);
		const uint32_t nVariable0Bits = gaDccFieldBitWidths[nFieldSizes & 0xF];
		const uint32_t nWidthBits = gaDccFieldBitWidths[(nFieldSizes >> 4) & 0xF];
		const uint32_t nHeightBits = gaDccFieldBitWidths[(nFieldSizes >> 8) & 0xF];
		const uint32_t nXOffsetBits = gaDccFieldBitWidths[(nFieldSizes >> 12) & 0xF];
		const uint32_t nYOffsetBits = gaDccFieldBitWidths[(nFieldSizes >> 16) & 0xF];
		const uint32_t nOptionalDataBits = gaDccFieldBitWidths[(nFieldSizes >> 20) & 0xF];
		const uint32_t nCodedBytesBits = gaDccFieldBitWidths[(nFieldSizes >> 24) & 0xF];

		// Frame headers
		const int nFrames = tHeader.dwFramesPerDirection;
		uint32_t nTotalOptionalDataSize = 0;
		for (int nFrame = 0; nFrame < nFrames; ++nFrame)
		{
			D2DccFrameStrc* pFrame = &sgtDccFrames[nFrame];
			pFrame->nVariable0 = BITSTREAM_ReadBits(&tBitstream, nVariable0Bits);
			pFrame->nWidth = BITSTREAM_ReadBits(&tBitstream, nWidthBits);
			pFrame->nHeight = BITSTREAM_ReadBits(&tBitstream, nHeightBits);
			pFrame->nXOffset = BITSTREAM_ReadSignedBits(&tBitstream, nXOffsetBits);
			pFrame->nYOffset = BITSTREAM_ReadSignedBits(&tBitstream, nYOffsetBits);
			pFrame->nOptionalDataSize = BITSTREAM_ReadBits(&tBitstream, nOptionalDataBits);
			pFrame->pOptionalData = nullptr;
			pFrame->nCodedBytes = BITSTREAM_ReadBits(&tBitstream, nCodedBytesBits);
			pFrame->pImage = nullptr;
			pFrame->nStride = 0;
			pFrame->bBottomUp = BITSTREAM_ReadBits(&tBitstream, 1);
			nTotalOptionalDataSize += pFrame->nOptionalDataSize;
		}

		if (nTotalOptionalDataSize)
		{
			BITSTREAM_AlignToByte(&tBitstream);
			const uint8_t* pOptionalData = (const uint8_t*)tBitstream.pCurrent + tBitstream.nBitOffset / 8;
			for (int nFrame = 0; nFrame < nFrames; ++nFrame)
			{
				D2DccFrameStrc* pFrame = &sgtDccFrames[nFrame];
				if (pFrame->nOptionalDataSize)
				{
					pFrame->pOptionalData = pOptionalData;
					pOptionalData += pFrame->nOptionalDataSize;
				}
			}
			BITSTREAM_Skip(&tBitstream, 8 * nTotalOptionalDataSize);
		}

		D2_ASSERT((uint32_t)nDirection < tHeader.dwNumDirections); // dir < sprite->directions

		// Bounding box of the direction
		D2DccDirectionStrc tDirection = {};
		tDirection.pHeader = &tHeader;
		tDirection.pFrames = sgtDccFrames;
		tDirection.nDirection = nDirection;
		tDirection.nFrames = nFrames;

		int nMinX = INT_MAX;
		int nMinY = INT_MAX;
		int nMaxX = INT_MIN;
		int nMaxY = INT_MIN;
		for (int nFrame = 0; nFrame < nFrames; ++nFrame)
		{
			const D2DccFrameStrc* pFrame = &sgtDccFrames[nFrame];
			const int nTop = pFrame->nYOffset - (pFrame->bBottomUp ? 0 : pFrame->nHeight);
			if (pFrame->nXOffset < nMinX)
			{
				nMinX = pFrame->nXOffset;
			}

			if (pFrame->nXOffset + pFrame->nWidth > nMaxX)
			{
				nMaxX = pFrame->nXOffset + pFrame->nWidth;
			}

			if (nTop < nMinY)
			{
				nMinY = nTop;
			}

			if (nTop + pFrame->nHeight > nMaxY)
			{
				nMaxY = nTop + pFrame->nHeight;
			}
		}

		tDirection.nMinX = nMinX;
		tDirection.nMinY = nMinY;
		tDirection.nWidth = nMaxX - nMinX;
		tDirection.nHeight = nMaxY - nMinY;
		tDirection.nCellCount = 0;
		tDirection.nCellsPerRow = (tDirection.nWidth + 3) / DCC_CELL_SIZE;
		tDirection.nBufferCells = ((tDirection.nHeight + 3) / DCC_CELL_SIZE) * tDirection.nCellsPerRow;

		if (nFrames)
		{
			D2DccCellIteratorStrc tIterator = {};
			tIterator.nFrame = -1;
			while (CODEC_NextCell(&tDirection, &tIterator))
			{
				++tDirection.nCellCount;
			}
		}

		memset(sgtDccPixelBuffer, 0x00, sizeof(D2DccCellStrc) * tDirection.nBufferCells);

		// Bitstreams sizes
		uint32_t nEqualCellsSize = 0;
		if (nCompressionFlags & 2)
		{
			nEqualCellsSize = BITSTREAM_ReadBits(&tBitstream, 20);
		}

		const uint32_t nPixelMaskSize = BITSTREAM_ReadBits(&tBitstream, 20);

		uint32_t nEncodingTypeSize = 0;
		uint32_t nRawPixelSize = 0;
		if (nCompressionFlags & 1)
		{
			nEncodingTypeSize = BITSTREAM_ReadBits(&tBitstream, 20);
			nRawPixelSize = BITSTREAM_ReadBits(&tBitstream, 20);
		}

		// Pixel values used by the direction
		uint32_t aPixelValuesBits[8];
		for (int i = 0; i < 8; ++i)
		{
			aPixelValuesBits[i] = BITSTREAM_ReadBits(&tBitstream, 32);
		}

		uint8_t aUsedPixelValues[256];
		for (int i = 0; i < 256; ++i)
		{
			aUsedPixelValues[i] = (aPixelValuesBits[i >> 5] & gdwBitMasks[i & 0x1F]) != 0;
		}

		uint8_t aPixelMap[256 + sizeof(int)];
		uint8_t aPalette[256 + sizeof(int)];
		CODEC_BuildPixelValuesMap(aUsedPixelValues, aPixelMap, aPalette);

		// Setup the bitstreams, which follow each other
		D2DccBitstreamStrc tEqualCellBitstream = tBitstream;
		D2DccBitstreamStrc tPixelMaskBitstream = tEqualCellBitstream;
		BITSTREAM_Skip(&tPixelMaskBitstream, nEqualCellsSize);
		D2DccBitstreamStrc tEncodingTypeBitstream = tPixelMaskBitstream;
		BITSTREAM_Skip(&tEncodingTypeBitstream, nPixelMaskSize);
		D2DccBitstreamStrc tRawPixelBitstream = tEncodingTypeBitstream;
		BITSTREAM_Skip(&tRawPixelBitstream, nEncodingTypeSize);
		tBitstream = tRawPixelBitstream;
		BITSTREAM_Skip(&tBitstream, nRawPixelSize);
		D2DccBitstreamStrc tPixelCodeBitstream = tBitstream;
		D2DccBitstreamStrc tPixelBufferEqualCellBitstream = tEqualCellBitstream;

		// First pass: fill the pixel buffer
		D2DccPixelValuesStrc tPixelValues = { sgDccPixelValues, 0 };
		uint32_t nPixelCodeBits = 0;
		CODEC_FillPixelBuffer(&tDirection, sgtDccPixelBuffer,
			nEqualCellsSize ? &tPixelBufferEqualCellBitstream : nullptr,
			&tPixelMaskBitstream,
			nEncodingTypeSize ? &tEncodingTypeBitstream : nullptr,
			nRawPixelSize ? &tRawPixelBitstream : nullptr,
			&tPixelCodeBitstream, &tPixelValues, &nPixelCodeBits);
		BITSTREAM_Skip(&tBitstream, nPixelCodeBits);
		CODEC_RemapPixelValues(&tPixelValues, aPalette);

		// Frames are drawn in the direction image
		for (int nFrame = 0; nFrame < nFrames; ++nFrame)
		{
			D2DccFrameStrc* pFrame = &sgtDccFrames[nFrame];
			const int left = pFrame->nXOffset - tDirection.nMinX;
			const int top = pFrame->nYOffset - (pFrame->bBottomUp ? 0 : pFrame->nHeight) - tDirection.nMinY;
			D2_ASSERT(left >= 0);
			D2_ASSERT(top >= 0);
			pFrame->nStride = tDirection.nWidth;
			pFrame->pImage = &sgDccDirectionImage[left + top * tDirection.nWidth];
		}

		// Second pass: decode the cells, and convert each frame to a cel
		uint8_t* pPixelValuesCursor = tPixelValues.pData;
		D2DccCellIteratorStrc tIterator;
		if (CODEC_FirstCell(&tDirection, &tIterator))
		{
			memset(sgtDccPixelBuffer, 0x00, sizeof(sgtDccPixelBuffer));
			D2DccBitstreamStrc* pEqualCellBitstream = nEqualCellsSize ? &tEqualCellBitstream : nullptr;
			int nCurrentFrame = 0;
			BOOL bHasNextCell = TRUE;
			do
			{
				D2DccCellStrc tCell;
				tCell.pPixelValues = pPixelValuesCursor;
				tCell.pDest = tIterator.pFrameImage + tIterator.nPixelOffset;
				tCell.nStride = tIterator.nFrameStride;
				tCell.nWidth = tIterator.nCellWidth;
				tCell.nHeight = tIterator.nCellHeight;
				CODEC_DecodeCell(&tCell, &tBitstream, &sgtDccPixelBuffer[tIterator.nCell], pEqualCellBitstream, &pPixelValuesCursor);
				sgtDccPixelBuffer[tIterator.nCell] = tCell;

				bHasNextCell = CODEC_NextCell(&tDirection, &tIterator);
				if (tIterator.nFrame != nCurrentFrame)
				{
					D2DccFrameStrc* pFrame = &sgtDccFrames[nCurrentFrame];
					D2GfxCellStrc* pCel = (D2GfxCellStrc*)pCurrentCel;
					pCel->dwFlags = pFrame->nVariable0;
					pCel->dwWidth = pFrame->nWidth;
					pCel->dwHeight = pFrame->nHeight;
					pCel->nXOffset = pFrame->nXOffset;
					pCel->nYOffset = pFrame->nYOffset;
					pCel->dwLength = pFrame->nCodedBytes;
					pCel->dwHardwareDataSize = 0;
					pCel->pCellNode = nullptr;
					D2_ASSERT(pFrame->pImage); // curcell->image

					if (!CODEC_EncodeFrame(pFrame, pCel, pCel->pPixels))
					{
						CODEC_ReportDecompressionError(pData, nDataLength, nDirection, tIterator.nFrame, pCel, szFileName);
					}

					pCurrentCel += pCel->dwLength + pCel->dwHardwareDataSize + offsetof(D2GfxCellStrc, pPixels) + 3;
					nCurrentFrame = tIterator.nFrame;
				}
			}
			while (bHasNextCell);
		}

		BITSTREAM_AlignToByte(&tBitstream);
	}

	LeaveCriticalSection(&sgtCodecLock);
	return pDecoded;
}
