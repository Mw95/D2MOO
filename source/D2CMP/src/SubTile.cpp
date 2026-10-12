#include "SubTile.h"

#include <cstring>

#include <Fog.h>

#include "Count.h"


constexpr int SUBTILE_SIZE = 32;
constexpr int GAMESQUARE_HEIGHT = 15;
constexpr int RLE_MAX_RUN = 0x7F;

// Inlined helper: Run length encodes nRows rows of a 8 bits image of width SUBTILE_SIZE.
// Each row is encoded as pairs of (transparent pixels to skip, number of pixels to copy) followed by the pixels.
// The end of a row is marked by a (0, 0) pair.
static uint8_t* SUBTILE_EncodeRLE(uint8_t* pDest, const uint8_t* pPixels, uint32_t nRows)
{
	const uint8_t* pSrc = pPixels;
	const uint8_t* pRowEnd = pPixels + SUBTILE_SIZE;
	const uint8_t* pNextRow = pPixels + SUBTILE_SIZE;
	uint32_t nRow = 0;
	while (nRow < nRows)
	{
		BOOL bCountEqualsDist = FALSE;
		BOOL bIsRemainingSame = FALSE;
		const int nSkip = CountConsecutive(0, pSrc, pRowEnd, RLE_MAX_RUN, &bCountEqualsDist, &bIsRemainingSame);
		pSrc += nSkip;

		if (!bCountEqualsDist && !bIsRemainingSame)
		{
			if (nSkip == RLE_MAX_RUN)
			{
				*pDest++ = (uint8_t)nSkip;
				continue;
			}

			const int nCopy = CountConsecutiveDiff(pSrc, pRowEnd, 0, RLE_MAX_RUN, &bCountEqualsDist, &bIsRemainingSame);
			*pDest++ = (uint8_t)nSkip;
			*pDest++ = (uint8_t)nCopy;
			for (int i = 0; i < nCopy; ++i)
			{
				*pDest++ = *pSrc++;
			}

			if (!bCountEqualsDist && !bIsRemainingSame)
			{
				continue;
			}
		}

		// End of row
		*pDest++ = 0;
		*pDest++ = 0;
		pSrc = pNextRow;
		pRowEnd += SUBTILE_SIZE;
		pNextRow += SUBTILE_SIZE;
		++nRow;
	}
	return pDest;
}

//D2CMP.0x6FDFE050
uint8_t* __fastcall SUBTILE_CompressSubTile(const uint8_t* pPixels, int* pSize)
{
	uint8_t* pBuffer = (uint8_t*)D2_ALLOC(0xC20);
	uint8_t* pEnd = SUBTILE_EncodeRLE(pBuffer, pPixels, SUBTILE_SIZE);
	*pSize = pEnd - pBuffer;
	return pBuffer;
}

//D2CMP.0x6FDFE130
void __fastcall SUBTILE_Convert24To8(D2TileLibraryBlockStrc* ptComp8, const D2TileLibraryBlockStrc* ptComp24, uint32_t dwTransparentColor, D2CMPColorConvertCallback pfnConvert)
{
	D2_ASSERT(ptComp8);
	D2_ASSERT(ptComp24);
	D2_ASSERT(ptComp24->dwOffset_pData);

	*ptComp8 = *ptComp24;
	ptComp8->nFormat &= ~TILECOMP_HASDATA;
	ptComp8->dwOffset_pData = nullptr;
	ptComp8->nLength = 0;

	const int nSize = (uint16_t)ptComp24->nLength / 3;
	D2_ASSERT(nSize);
	D2_ASSERT(nSize < 0x00010000);

	ptComp8->dwOffset_pData = (uint8_t*)D2_ALLOC(nSize);
	D2_ASSERT(ptComp8->dwOffset_pData);
	memset(ptComp8->dwOffset_pData, 0x00, nSize);

	ptComp8->nFormat |= TILECOMP_HASDATA;
	ptComp8->nLength = (uint16_t)nSize;

	uint8_t* pDest = ptComp8->dwOffset_pData;
	const uint8_t* pSrc = ptComp24->dwOffset_pData;
	const uint8_t* pTransparentColor = (const uint8_t*)&dwTransparentColor;
	for (int i = 0; i < nSize; ++i)
	{
		uint8_t bColor = 0;
		if (pSrc[0] != pTransparentColor[0] || pSrc[1] != pTransparentColor[1] || pSrc[2] != pTransparentColor[2])
		{
			bColor = pfnConvert(pSrc[0], pSrc[1], pSrc[2]);
			D2_ASSERT(bColor);
		}

		*pDest = bColor;
		++pDest;
		pSrc += 3;
	}
}

//D2CMP.0x6FDFE2F0
void __fastcall SUBTILE_CompressGameSquare(D2TileLibraryBlockStrc* ptComp)
{
	uint8_t* pPixels = ptComp->dwOffset_pData;

	// Check if the isometric square has any transparent pixel
	const uint8_t* pRow = pPixels;
	int nStart = 14;
	int nWidth = 4;
	for (int nY = 0; nY < GAMESQUARE_HEIGHT; ++nY)
	{
		for (int nX = 0; nX < nWidth; ++nX)
		{
			if (pRow[nStart + nX] == 0)
			{
				SUBTILE_CompressGameSquareRLE(ptComp, pPixels);
				D2_FREE(pPixels);
				return;
			}
		}

		pRow += SUBTILE_SIZE;
		if (nY < 7)
		{
			nStart -= 2;
			nWidth += 4;
		}
		else
		{
			nStart += 2;
			nWidth -= 4;
		}
	}

	SUBTILE_SquishGameSquare(ptComp, pPixels);
	D2_FREE(pPixels);
}

//D2CMP.0x6FDFE370
void __fastcall SUBTILE_CompressGameSquareRLE(D2TileLibraryBlockStrc* ptComp, const uint8_t* pPixels)
{
	uint8_t* ptDestBuffer = (uint8_t*)D2_ALLOC(0x5AF);
	D2_ASSERT(ptDestBuffer);
	memset(ptDestBuffer, 0x00, 0x5AF);

	uint8_t* pEnd = SUBTILE_EncodeRLE(ptDestBuffer, pPixels, GAMESQUARE_HEIGHT);
	const int nSize = pEnd - ptDestBuffer;
	D2_ASSERT(nSize < 0x00010000);

	uint8_t* ptNewData = (uint8_t*)D2_ALLOC(nSize);
	D2_ASSERT(ptNewData);
	memset(ptNewData, 0x00, nSize);
	memcpy(ptNewData, ptDestBuffer, nSize);

	ptComp->nFormat |= TILECOMP_HASDATA | TILECOMP_RLE;
	ptComp->dwOffset_pData = ptNewData;
	ptComp->nLength = (uint16_t)nSize;
	D2_FREE(ptDestBuffer);
}

//D2CMP.0x6FDFE530
void __fastcall SUBTILE_SquishGameSquare(D2TileLibraryBlockStrc* ptComp, const uint8_t* pPixels)
{
	uint8_t* ptSquished = (uint8_t*)D2_ALLOC(256);
	D2_ASSERT(ptSquished);
	memset(ptSquished, 0x00, 256);

	uint8_t* pDest = ptSquished;
	const uint8_t* pRow = pPixels;
	int nStart = 14;
	int nWidth = 4;
	for (int nY = 0; nY < GAMESQUARE_HEIGHT; ++nY)
	{
		memcpy(pDest, &pRow[nStart], nWidth);
		pDest += nWidth;
		pRow += SUBTILE_SIZE;
		if (nY < 7)
		{
			nStart -= 2;
			nWidth += 4;
		}
		else
		{
			nStart += 2;
			nWidth -= 4;
		}
	}

	ptComp->nFormat = TILECOMP_HASDATA;
	ptComp->nLength = 256;
	ptComp->dwOffset_pData = ptSquished;
}
