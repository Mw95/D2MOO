#include "StormInternal.h"

#include "SCompInternal.h"
#include "PKWare/PKWare.h"

// Data compression

#define SCOMP_FILENAME "C:\\projects\\D2\\head\\Diablo2\\3rdParty\\STORM\\SOURCE\\SCOMP.CPP"

// Compression functions receive the destination in ecx and the destination size in edx in the original code.
typedef void(*SCOMPCOMPRESSFUNC)(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize, uint32_t* pType, uint32_t nLevel);
typedef void(*SCOMPDECOMPRESSFUNC)(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize);

struct SCOMPCOMPRESSOR
{
	uint32_t dwMask;
	SCOMPCOMPRESSFUNC pfnCompress;
};

struct SCOMPDECOMPRESSOR
{
	uint32_t dwMask;
	SCOMPDECOMPRESSFUNC pfnDecompress;
};

// Parameter of the PKWARE read and write callbacks
struct SCOMPPKWAREPARAM
{
	uint8_t* pDest;
	uint32_t nDestPos;
	uint32_t nDestSize;
	const uint8_t* pSource;
	uint32_t nSourcePos;
	uint32_t nSourceSize;
};

// Storm.0x6FFBC0D0
static uint32_t __cdecl SCompPKWareRead(char* buf, uint32_t* size, void* param)
{
	SCOMPPKWAREPARAM* pParam = (SCOMPPKWAREPARAM*)param;
	uint32_t nSize = *size;
	if (nSize >= pParam->nSourceSize - pParam->nSourcePos)
	{
		nSize = pParam->nSourceSize - pParam->nSourcePos;
	}
	SMemCopy(buf, pParam->pSource + pParam->nSourcePos, nSize);
	pParam->nSourcePos += nSize;
	return nSize;
}

// Storm.0x6FFBC110
static void __cdecl SCompPKWareWrite(char* buf, uint32_t* size, void* param)
{
	SCOMPPKWAREPARAM* pParam = (SCOMPPKWAREPARAM*)param;
	uint32_t nSize = *size;
	if (nSize >= pParam->nDestSize - pParam->nDestPos)
	{
		nSize = pParam->nDestSize - pParam->nDestPos;
	}
	SMemCopy(pParam->pDest + pParam->nDestPos, buf, nSize);
	pParam->nDestPos += nSize;
}

// Storm.0x6FFBC000
static void SCompImplode(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize, uint32_t* pType, uint32_t nLevel)
{
	void* pWorkBuffer = SMemAlloc(PKWARE_IMPLODE_BUFFER_SIZE, SCOMP_FILENAME, 1009, 0);

	SCOMPPKWAREPARAM param;
	param.pDest = (uint8_t*)pDest;
	param.nDestPos = 0;
	param.nDestSize = *pDestSize;
	param.pSource = (const uint8_t*)pSource;
	param.nSourcePos = 0;
	param.nSourceSize = nSourceSize;

	uint32_t nType = *pType == 2 ? PKWARE_CMP_ASCII : PKWARE_CMP_BINARY;
	uint32_t nDictSize;
	if (nSourceSize < 0x600)
	{
		nDictSize = 0x400;
	}
	else if (nSourceSize < 0xC00)
	{
		nDictSize = 0x800;
	}
	else
	{
		nDictSize = 0x1000;
	}

	PKWareImplode(SCompPKWareRead, SCompPKWareWrite, pWorkBuffer, &param, &nType, &nDictSize);
	SMemFree(pWorkBuffer, SCOMP_FILENAME, 1039, 0);
	*pDestSize = param.nDestPos;
	*pType = 0;
}

// Storm.0x6FFBC150
static void SCompExplode(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize)
{
	void* pWorkBuffer = SMemAlloc(PKWARE_EXPLODE_BUFFER_SIZE, SCOMP_FILENAME, 1052, 0);

	SCOMPPKWAREPARAM param;
	param.pDest = (uint8_t*)pDest;
	param.nDestPos = 0;
	param.nDestSize = *pDestSize;
	param.pSource = (const uint8_t*)pSource;
	param.nSourcePos = 0;
	param.nSourceSize = nSourceSize;

	PKWareExplode(SCompPKWareRead, SCompPKWareWrite, pWorkBuffer, &param);
	SMemFree(pWorkBuffer, SCOMP_FILENAME, 1070, 0);
	*pDestSize = param.nDestPos;
}

// Storm.0x6FFBC220
// Also changes the type used by the following huffman compression to the one best suited for ADPCM data.
static uint8_t SCompGetADPCMLevel(uint32_t nLevel, uint32_t* pType)
{
	if (nLevel && nLevel <= 2)
	{
		*pType = 6;
		return 4;
	}
	if (nLevel == 3)
	{
		*pType = 8;
		return 6;
	}
	*pType = 7;
	return 5;
}

// Storm.0x6FFBC1E0
static void SCompADPCMMonoCompress(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize, uint32_t* pType, uint32_t nLevel)
{
	*pDestSize = SCompADPCMCompress(pDest, *pDestSize, pSource, nSourceSize, 1, SCompGetADPCMLevel(nLevel, pType));
}

// Storm.0x6FFBC540
static void SCompADPCMMonoDecompress(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize)
{
	*pDestSize = SCompADPCMDecompress(pDest, *pDestSize, pSource, nSourceSize, 1);
}

// Storm.0x6FFBC750
static void SCompADPCMStereoCompress(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize, uint32_t* pType, uint32_t nLevel)
{
	*pDestSize = SCompADPCMCompress(pDest, *pDestSize, pSource, nSourceSize, 2, SCompGetADPCMLevel(nLevel, pType));
}

// Storm.0x6FFBC790
static void SCompADPCMStereoDecompress(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize)
{
	*pDestSize = SCompADPCMDecompress(pDest, *pDestSize, pSource, nSourceSize, 2);
}

// Storm.0x6FFBC7B0
static void SCompHuffmanCompressData(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize, uint32_t* pType, uint32_t nLevel)
{
	*pDestSize = SCompHuffmanCompress(pDest, *pDestSize, pSource, nSourceSize, *(uint8_t*)pType);
}

// Storm.0x6FFBC8F0
static void SCompHuffmanDecompressData(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize)
{
	*pDestSize = SCompHuffmanDecompress(pDest, *pDestSize, pSource);
}

// Storm.0x6FFE2274 : in the order of the compression
static const SCOMPCOMPRESSOR sgCompressors[] =
{
	{ SCOMP_ADPCM_MONO,   SCompADPCMMonoCompress },
	{ SCOMP_ADPCM_STEREO, SCompADPCMStereoCompress },
	{ SCOMP_HUFFMAN,      SCompHuffmanCompressData },
	{ SCOMP_IMPLODE,      SCompImplode },
};

// Storm.0x6FFE2294 : decompression is done in the reverse order
static const SCOMPDECOMPRESSOR sgDecompressors[] =
{
	{ SCOMP_ADPCM_MONO,   SCompADPCMMonoDecompress },
	{ SCOMP_ADPCM_STEREO, SCompADPCMStereoDecompress },
	{ SCOMP_HUFFMAN,      SCompHuffmanDecompressData },
	{ SCOMP_IMPLODE,      SCompExplode },
};

static inline bool SCompOverlaps(const void* p1, const void* p2, uint32_t nSize)
{
	return (const uint8_t*)p1 + nSize > (const uint8_t*)p2 && (const uint8_t*)p2 + nSize > (const uint8_t*)p1;
}

// Storm.#551
BOOL __stdcall SCompCompress(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize, uint32_t dwCompressionMask, uint32_t dwType, uint32_t dwLevel)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(pDest);
	STORM_VALIDATE_ARG(pDestSize);
	STORM_VALIDATE_ARG(*pDestSize >= nSourceSize);
	STORM_VALIDATE_ARG(pSource);
	STORM_VALIDATE_END(FALSE);

	uint32_t nRemainingCompressions = 0;
	uint32_t dwUnknownMask = dwCompressionMask;
	for (const SCOMPCOMPRESSOR& compressor : sgCompressors)
	{
		if (dwCompressionMask & compressor.dwMask)
		{
			++nRemainingCompressions;
		}
		dwUnknownMask &= ~compressor.dwMask;
	}
	if (dwUnknownMask)
	{
		return FALSE;
	}

	// A temporary buffer is needed for multiple compressions, or if the buffers overlap
	uint8_t* pTempBuffer = nullptr;
	if (nRemainingCompressions >= 2 || (nRemainingCompressions && SCompOverlaps(pDest, pSource, nSourceSize)))
	{
		pTempBuffer = (uint8_t*)SMemAlloc(nSourceSize, SCOMP_FILENAME, 1252, 0);
	}

	const uint8_t* pCurrentData = (const uint8_t*)pSource;
	uint32_t nCurrentSize = nSourceSize;
	for (const SCOMPCOMPRESSOR& compressor : sgCompressors)
	{
		if (!(dwCompressionMask & compressor.dwMask))
		{
			continue;
		}

		// Alternate between the buffers so that the last compression ends in the destination
		--nRemainingCompressions;
		uint8_t* pTarget = (nRemainingCompressions & 1) ? pTempBuffer : (uint8_t*)pDest + 1;
		if (SCompOverlaps(pTarget, pCurrentData, nCurrentSize))
		{
			if (SCompOverlaps(pTarget, pTempBuffer, nCurrentSize))
			{
				pTarget = (uint8_t*)pDest + 1;
			}
			else
			{
				pTarget = pTempBuffer;
			}
		}

		uint32_t nCompressedSize = nCurrentSize - 1;
		compressor.pfnCompress(pTarget, &nCompressedSize, pCurrentData, nCurrentSize, &dwType, dwLevel);
		if (nCompressedSize + 1 < nCurrentSize)
		{
			pCurrentData = pTarget;
			nCurrentSize = nCompressedSize;
		}
		else
		{
			// Not worth it
			dwCompressionMask &= ~compressor.dwMask;
		}
	}

	if (pCurrentData != pDest)
	{
		if (pCurrentData == (uint8_t*)pDest + 1)
		{
			*(uint8_t*)pDest = (uint8_t)dwCompressionMask;
			++nCurrentSize;
		}
		else if (dwCompressionMask)
		{
			SMemCopy((uint8_t*)pDest + 1, pCurrentData, nCurrentSize);
			++nCurrentSize;
			*(uint8_t*)pDest = (uint8_t)dwCompressionMask;
		}
		else
		{
			SMemCopy(pDest, pCurrentData, nCurrentSize);
		}
	}

	*pDestSize = nCurrentSize;
	if (pTempBuffer)
	{
		SMemFree(pTempBuffer, SCOMP_FILENAME, 1304, 0);
	}
	return TRUE;
}

// Storm.#552
BOOL __stdcall SCompDecompress(void* pDest, uint32_t* pDestSize, const void* pSource, uint32_t nSourceSize)
{
	const uint32_t nDestSize = *pDestSize;

	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(pDest);
	STORM_VALIDATE_ARG(nDestSize >= nSourceSize);
	STORM_VALIDATE_ARG(pSource);
	STORM_VALIDATE_ARG(nSourceSize >= 1);
	STORM_VALIDATE_END(FALSE);

	// Data that was not compressed
	if (nSourceSize == nDestSize)
	{
		if (pDest != pSource)
		{
			SMemCopy(pDest, pSource, nSourceSize);
		}
		return TRUE;
	}

	const uint8_t* pCurrentData = (const uint8_t*)pSource;
	const uint32_t dwCompressionMask = *pCurrentData++;
	uint32_t nCurrentSize = nSourceSize - 1;

	uint32_t nRemainingDecompressions = 0;
	uint32_t dwUnknownMask = dwCompressionMask;
	for (int32_t i = STORM_ARRAYSIZE(sgDecompressors) - 1; i >= 0; --i)
	{
		if (dwCompressionMask & sgDecompressors[i].dwMask)
		{
			++nRemainingDecompressions;
		}
		dwUnknownMask &= ~sgDecompressors[i].dwMask;
	}
	if (dwUnknownMask)
	{
		return FALSE;
	}

	uint8_t* pTempBuffer = nullptr;
	if (nRemainingDecompressions >= 2 || (nRemainingDecompressions && SCompOverlaps(pDest, pCurrentData, nCurrentSize)))
	{
		pTempBuffer = (uint8_t*)SMemAlloc(nDestSize, SCOMP_FILENAME, 1353, 0);
	}

	for (int32_t i = STORM_ARRAYSIZE(sgDecompressors) - 1; i >= 0; --i)
	{
		if (!(dwCompressionMask & sgDecompressors[i].dwMask))
		{
			continue;
		}

		--nRemainingDecompressions;
		uint8_t* pTarget = (nRemainingDecompressions & 1) ? pTempBuffer : (uint8_t*)pDest;
		if (SCompOverlaps(pTarget, pCurrentData, nCurrentSize))
		{
			if (SCompOverlaps(pTarget, pTempBuffer, nCurrentSize))
			{
				pTarget = (uint8_t*)pDest;
			}
			else
			{
				pTarget = pTempBuffer;
			}
		}

		uint32_t nDecompressedSize = nDestSize;
		sgDecompressors[i].pfnDecompress(pTarget, &nDecompressedSize, pCurrentData, nCurrentSize);
		nCurrentSize = nDecompressedSize;
		pCurrentData = pTarget;
	}

	if (pCurrentData != pDest)
	{
		SMemCopy(pDest, pCurrentData, nCurrentSize);
	}

	*pDestSize = nCurrentSize;
	if (pTempBuffer)
	{
		SMemFree(pTempBuffer, SCOMP_FILENAME, 1384, 0);
	}
	return TRUE;
}
