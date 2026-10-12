#include "Tilecmp.h"

#include <cstring>

#include <Fog.h>

#include "FindTiles.h"
#include "SubTile.h"
#include "TileCache.h"


constexpr int SUBTILE_SIZE = 32;
constexpr int SUBTILE_24BIT_STRIDE = SUBTILE_SIZE * 3;
constexpr int FLOORTILE_WIDTH = 160;
constexpr int FLOORTILE_24BIT_STRIDE = FLOORTILE_WIDTH * 3;
constexpr int FLOORTILE_GRID_SIZE = 5;
constexpr int GAMESQUARE_HEIGHT = 15;
constexpr int GAMESQUARE_24BIT_SIZE = SUBTILE_24BIT_STRIDE * 16;

struct D2TilePositionStrc
{
	int32_t nX;
	int32_t nY;
};

//D2CMP.0x6FE0F7E8
static const D2TilePositionStrc gatFloorTileSquarePositions[FLOORTILE_GRID_SIZE * FLOORTILE_GRID_SIZE] = {
	{ 64,  0 }, { 80,  8 }, { 96, 16 }, { 112, 24 }, { 128, 32 },
	{ 48,  8 }, { 64, 16 }, { 80, 24 }, {  96, 32 }, { 112, 40 },
	{ 32, 16 }, { 48, 24 }, { 64, 32 }, {  80, 40 }, {  96, 48 },
	{ 16, 24 }, { 32, 32 }, { 48, 40 }, {  64, 48 }, {  80, 56 },
	{  0, 32 }, { 16, 40 }, { 32, 48 }, {  48, 56 }, {  64, 64 },
};


//D2CMP.0x6FE00388
static void __fastcall TILECMP_CopyRect(uint8_t* pDest, const uint8_t* pSrc, int nDestStride, int nSrcStride, int nHeight, int nWidth)
{
	for (int nY = 0; nY < nHeight; ++nY)
	{
		memcpy(pDest, pSrc, nWidth);
		pDest += nDestStride;
		pSrc += nSrcStride;
	}
}

//D2CMP.0x6FDFE8D0 (#10065)
D2TileListStrc* __stdcall D2CMP_TileListCreate(BOOL b24Bit, uint32_t dwTransparentColor)
{
	D2TileListStrc* ptList = D2_ALLOC_STRC(D2TileListStrc);
	D2_ASSERT(ptList);
	memset(ptList, 0x00, sizeof(*ptList));
	ptList->b24Bit = b24Bit;
	ptList->dwTransparentColor = dwTransparentColor;
	return ptList;
}

//D2CMP.0x6FDFE930 (#10066)
void __stdcall D2CMP_TileListDestroy(D2TileListStrc* ptList)
{
	D2_ASSERT(ptList);

	D2TileAddStrc* ptTile = ptList->ptFirstTile;
	while (ptTile)
	{
		D2TileAddStrc* ptNextTile = ptTile->pNext;

		D2TileAddCompStrc* ptComp = ptTile->ptCompList;
		while (ptComp)
		{
			D2TileAddCompStrc* ptNextComp = ptComp->pNext;
			if (ptComp->ptData)
			{
				D2_FREE(ptComp->ptData);
			}
			D2_FREE(ptComp);
			ptComp = ptNextComp;
		}

		D2_FREE(ptTile);
		ptTile = ptNextTile;
	}

	D2_FREE(ptList);
}

//D2CMP.0x6FDFE9D0 (#10067)
D2TileAddStrc* __stdcall D2CMP_TileListAddTile(D2TileListStrc* ptList, uint16_t nFlags, uint16_t nRoofHeight, int nType, int nStyle, int nSequence, int nRarity, int nLightDirection, const uint8_t* pCollisionInfo)
{
	D2_ASSERT(ptList);

	D2TileAddStrc* ptTile = D2_ALLOC_STRC(D2TileAddStrc);
	D2_ASSERT(ptTile);
	memset(ptTile, 0x00, sizeof(*ptTile));

	ptTile->pNext = ptList->ptFirstTile;
	ptList->ptFirstTile = ptTile;
	++ptList->nNumTiles;

	ptTile->nFlags = nFlags;
	ptTile->nRoofHeight = nRoofHeight;
	ptTile->nType = nType;
	ptTile->nStyle = nStyle;
	ptTile->nSequence = nSequence;
	ptTile->nRarity = nRarity;
	ptTile->nLightDirection = nLightDirection;
	ptTile->dwTransparentColor = ptList->dwTransparentColor;
	ptTile->nAddFlags = TILEADD_FLAG_24BIT;
	memcpy(ptTile->pCollisionInfo, pCollisionInfo, sizeof(ptTile->pCollisionInfo));
	return ptTile;
}

//D2CMP.0x6FDFEAA0 (#10068)
void __stdcall D2CMP_TileAddAddSubTile(D2TileAddStrc* hTileAdd, const uint8_t* ptImage, int nStride, int nOffsetX, int nOffsetY)
{
	D2_ASSERT(hTileAdd);
	D2_ASSERT(ptImage);

	const uint8_t* pPixel = ptImage;
	bool bEmpty = true;
	if (hTileAdd->nAddFlags & TILEADD_FLAG_24BIT)
	{
		const uint32_t dwTransparentColor = hTileAdd->dwTransparentColor & 0xFFFFFF;
		for (int nY = 0; nY < SUBTILE_SIZE && bEmpty; ++nY)
		{
			for (int nX = 0; nX < SUBTILE_SIZE; ++nX)
			{
				const uint32_t dwColor = pPixel[0] | (pPixel[1] << 8) | (pPixel[2] << 16);
				pPixel += 3;
				if (dwColor != dwTransparentColor)
				{
					bEmpty = false;
					break;
				}
			}
			pPixel += nStride - SUBTILE_24BIT_STRIDE;
		}
	}

	if (bEmpty && (hTileAdd->nAddFlags & TILEADD_FLAG_8BIT))
	{
		for (int nY = 0; nY < SUBTILE_SIZE && bEmpty; ++nY)
		{
			for (int nX = 0; nX < SUBTILE_SIZE; ++nX)
			{
				if (*pPixel++)
				{
					bEmpty = false;
					break;
				}
			}
			pPixel += nStride - SUBTILE_SIZE;
		}
	}

	if (bEmpty)
	{
		return;
	}

	D2TileAddCompStrc* ptComp = D2_ALLOC_STRC(D2TileAddCompStrc);
	D2_ASSERT(ptComp);
	memset(ptComp, 0x00, sizeof(*ptComp));
	ptComp->pNext = hTileAdd->ptCompList;
	hTileAdd->ptCompList = ptComp;
	++hTileAdd->nCompCount;

	D2_ASSERT(nOffsetX < 0x00010000 && nOffsetY < 0x00010000);
	ptComp->nPosY = (int16_t)nOffsetY;
	ptComp->nPosX = (int16_t)nOffsetX;

	uint8_t* ptData = (uint8_t*)D2_ALLOC(SUBTILE_24BIT_STRIDE * SUBTILE_SIZE);
	D2_ASSERT(ptData);
	memset(ptData, 0x00, SUBTILE_24BIT_STRIDE * SUBTILE_SIZE);
	ptComp->wSize = SUBTILE_24BIT_STRIDE * SUBTILE_SIZE;
	ptComp->ptData = ptData;
	ptComp->wFlags = TILECOMP_SUBTILE | TILECOMP_HASDATA;
	TILECMP_CopyRect(ptData, ptImage, SUBTILE_24BIT_STRIDE, nStride, SUBTILE_SIZE, SUBTILE_24BIT_STRIDE);

	if (nOffsetX < hTileAdd->nMinX)
	{
		hTileAdd->nMinX = nOffsetX;
	}

	if (nOffsetX + SUBTILE_SIZE > hTileAdd->nMaxX)
	{
		hTileAdd->nMaxX = nOffsetX + SUBTILE_SIZE;
	}

	if (nOffsetY > hTileAdd->nMaxY)
	{
		hTileAdd->nMaxY = nOffsetY;
	}

	if (nOffsetY - SUBTILE_SIZE < hTileAdd->nMinY)
	{
		hTileAdd->nMinY = nOffsetY - SUBTILE_SIZE;
	}
}

//D2CMP.0x6FDFECB0 (#10069)
void __stdcall D2CMP_TileAddAddFloorTile(D2TileAddStrc* ptTileAdd, const uint8_t* ptImage)
{
	D2_ASSERT(ptTileAdd);
	D2_ASSERT(ptImage);

	for (int nSquare = 0; nSquare < FLOORTILE_GRID_SIZE * FLOORTILE_GRID_SIZE; ++nSquare)
	{
		const D2TilePositionStrc& tPosition = gatFloorTileSquarePositions[nSquare];

		D2TileAddCompStrc tComp = {};
		const uint32_t dwTransparentColor = ptTileAdd->dwTransparentColor;
		const uint8_t* pTransparentColor = (const uint8_t*)&dwTransparentColor;

		uint8_t* ptSquare = (uint8_t*)D2_ALLOC(GAMESQUARE_24BIT_SIZE);
		D2_ASSERT(ptSquare);
		memset(ptSquare, 0x00, GAMESQUARE_24BIT_SIZE);

		for (int i = 0; i < GAMESQUARE_24BIT_SIZE / 3; ++i)
		{
			ptSquare[3 * i + 0] = pTransparentColor[0];
			ptSquare[3 * i + 1] = pTransparentColor[1];
			ptSquare[3 * i + 2] = pTransparentColor[2];
		}

		// Copy the isometric diamond
		uint8_t* pDestRow = ptSquare;
		const uint8_t* pSrcRow = &ptImage[3 * (tPosition.nX + FLOORTILE_WIDTH * tPosition.nY)];
		int nStart = 14 * 3;
		int nWidth = 4 * 3;
		for (int nY = 0; nY < GAMESQUARE_HEIGHT; ++nY)
		{
			memcpy(&pDestRow[nStart], &pSrcRow[nStart], nWidth);
			if (nY < 7)
			{
				nStart -= 2 * 3;
				nWidth += 4 * 3;
			}
			else
			{
				nStart += 2 * 3;
				nWidth -= 4 * 3;
			}
			pDestRow += SUBTILE_24BIT_STRIDE;
			pSrcRow += FLOORTILE_24BIT_STRIDE;
		}

		bool bEmpty = true;
		for (int i = 0; i < GAMESQUARE_24BIT_SIZE / 3; ++i)
		{
			if (ptSquare[3 * i + 0] != pTransparentColor[0] || ptSquare[3 * i + 1] != pTransparentColor[1] || ptSquare[3 * i + 2] != pTransparentColor[2])
			{
				bEmpty = false;
				break;
			}
		}

		if (bEmpty)
		{
			D2_FREE(ptSquare);
		}
		else
		{
			tComp.wFlags |= TILECOMP_GAMESQUARE | TILECOMP_HASDATA;
			tComp.wSize = GAMESQUARE_24BIT_SIZE;
			tComp.ptData = ptSquare;
		}

		tComp.nGridY = nSquare / FLOORTILE_GRID_SIZE;
		tComp.nGridX = nSquare % FLOORTILE_GRID_SIZE;

		if (tComp.wFlags & TILECOMP_HASDATA)
		{
			D2TileAddCompStrc* ptComp = D2_ALLOC_STRC(D2TileAddCompStrc);
			D2_ASSERT(ptComp);
			memset(ptComp, 0x00, sizeof(*ptComp));
			*ptComp = tComp;
			ptComp->pNext = ptTileAdd->ptCompList;
			ptTileAdd->ptCompList = ptComp;
			++ptTileAdd->nCompCount;
			ptComp->nPosX = (int16_t)tPosition.nX;
			ptComp->nPosY = (int16_t)tPosition.nY;
		}
	}

	ptTileAdd->nMaxY = 0;
	ptTileAdd->nMinY = -128;
	ptTileAdd->nMinX = 0;
	ptTileAdd->nMaxX = FLOORTILE_WIDTH;
}

//D2CMP.0x6FDFEF60 (#10070)
uint32_t __stdcall D2CMP_TileListCreateProject(D2TileListStrc* ptTileList, D2TileLibraryHeaderStrc** pptProject)
{
	D2_ASSERT(ptTileList);

	if (!ptTileList->nNumTiles)
	{
		*pptProject = nullptr;
		return 0x85200004;
	}

	D2TileLibraryHeaderStrc* ptProject = D2_ALLOC_STRC(D2TileLibraryHeaderStrc);
	D2_ASSERT(ptProject);
	memset(ptProject, 0x00, sizeof(*ptProject));

	ptProject->dwVersion = TILEPROJECT_VERSION;
	if (ptTileList->b24Bit)
	{
		ptProject->dwFlags = TILEPROJECT_FLAG_24BIT;
	}

	ptProject->nTiles = ptTileList->nNumTiles;
	const int nTileArraySize = sizeof(D2TileLibraryEntryStrc) * ptTileList->nNumTiles;
	ptProject->pTiles = (D2TileLibraryEntryStrc*)D2_ALLOC(nTileArraySize);
	D2_ASSERT(ptProject->pTiles);
	memset(ptProject->pTiles, 0x00, nTileArraySize);

	int nTile = 0;
	for (D2TileAddStrc* ptTileAdd = ptTileList->ptFirstTile; ptTileAdd; ptTileAdd = ptTileAdd->pNext)
	{
		D2TileLibraryEntryStrc* ptTile = &ptProject->pTiles[nTile];
		ptTile->nLightDirection = ptTileAdd->nLightDirection;
		ptTile->nRoofHeight = ptTileAdd->nRoofHeight;
		ptTile->nFlags = ptTileAdd->nFlags;
		ptTile->nWidth = ptTileAdd->nMaxX - ptTileAdd->nMinX;
		ptTile->nTotalHeight = ptTileAdd->nMinY - ptTileAdd->nMaxY;
		ptTile->nType = ptTileAdd->nType;
		ptTile->nStyle = ptTileAdd->nStyle;
		ptTile->nSequence = ptTileAdd->nSequence;
		ptTile->nRarity_Frame = ptTileAdd->nRarity;
		ptTile->transparentColorRGB24 = ptTileAdd->dwTransparentColor;
		ptTile->nBlocks = ptTileAdd->nCompCount;
		memcpy(ptTile->pCollisionInfo, ptTileAdd->pCollisionInfo, sizeof(ptTile->pCollisionInfo));

		const int nSize = sizeof(D2TileLibraryBlockStrc) * ptTile->nBlocks;
		if (nSize)
		{
			ptTile->pBlocks = (D2TileLibraryBlockStrc*)D2_ALLOC(nSize);
			D2_ASSERT(ptTile->pBlocks);
			memset(ptTile->pBlocks, 0x00, nSize);
		}
		else
		{
			ptTile->pBlocks = nullptr;
		}

		int nTileComp = 0;
		for (D2TileAddCompStrc* ptComp = ptTileAdd->ptCompList; ptComp; ptComp = ptComp->pNext)
		{
			D2TileLibraryBlockStrc* ptBlock = &ptTile->pBlocks[nTileComp];
			ptBlock->nPosX = ptComp->nPosX;
			ptBlock->nPosY = ptComp->nPosY;
			ptBlock->nGridX = ptComp->nGridX;
			ptBlock->nGridY = ptComp->nGridY;
			ptBlock->nFormat = ptComp->wFlags;
			ptBlock->nLength = ptComp->wSize;
			ptBlock->dwOffset_pData = ptComp->ptData;
			ptComp->ptData = nullptr;
			++nTileComp;
		}

		D2_ASSERT(nTileComp == ptTile->nBlocks);
		++nTile;
	}

	D2_ASSERT(nTile == ptProject->nTiles);
	*pptProject = ptProject;
	return 0;
}

//D2CMP.0x6FDFF220 (#10073)
void __stdcall D2CMP_TileProjectDestroy(D2TileLibraryHeaderStrc* ptProject, BOOL bDoNotFree)
{
	if (bDoNotFree)
	{
		return;
	}

	D2_ASSERT(ptProject);

	TILECACHE_FreeProjectTiles(ptProject);

	if (ptProject->dwFlags & TILEPROJECT_FLAG_SINGLEBLOCK)
	{
		D2_FREE(ptProject);
		return;
	}

	D2_ASSERT(!(ptProject->dwFlags & TILEPROJECT_FEWBLOCKS));

	for (int nTile = 0; nTile < ptProject->nTiles; ++nTile)
	{
		D2TileLibraryEntryStrc* ptTile = &ptProject->pTiles[nTile];
		for (int nBlock = 0; nBlock < ptTile->nBlocks; ++nBlock)
		{
			D2TileLibraryBlockStrc* ptBlock = &ptTile->pBlocks[nBlock];
			if (ptBlock->dwOffset_pData)
			{
				D2_FREE(ptBlock->dwOffset_pData);
			}
			ptBlock->nLength = 0;
			ptBlock->dwOffset_pData = nullptr;
		}

		if (ptTile->pBlocks)
		{
			D2_FREE(ptTile->pBlocks);
		}
		ptTile->pBlocks = nullptr;
		ptTile->nBlocks = 0;
	}

	D2_FREE(ptProject->pTiles);
	ptProject->pTiles = nullptr;
	ptProject->nTiles = 0;
	D2_FREE(ptProject);
}

//D2CMP.0x6FDFF380 (#10071)
void __stdcall D2CMP_TileProjectSerialize(D2TileLibraryHeaderStrc* ptProject, void** ptptData, int* ptnSize)
{
	D2_ASSERT(ptProject);
	D2_ASSERT(ptptData);
	D2_ASSERT(ptnSize);
	D2_ASSERT(ptProject->nTiles);

	int nSize = sizeof(D2TileLibraryHeaderStrc) + sizeof(D2TileLibraryEntryStrc) * ptProject->nTiles;
	for (int nTile = 0; nTile < ptProject->nTiles; ++nTile)
	{
		const D2TileLibraryEntryStrc* ptTile = &ptProject->pTiles[nTile];
		nSize += sizeof(D2TileLibraryBlockStrc) * ptTile->nBlocks;
		for (int nBlock = 0; nBlock < ptTile->nBlocks; ++nBlock)
		{
			nSize += (uint16_t)ptTile->pBlocks[nBlock].nLength;
		}
	}

	D2_ASSERT(nSize);

	uint8_t* ptData = (uint8_t*)D2_ALLOC(nSize);
	D2_ASSERT(ptData);
	memset(ptData, 0x00, nSize);
	*ptptData = ptData;
	*ptnSize = nSize;

	D2TileLibraryHeaderStrc* ptSerializedProject = (D2TileLibraryHeaderStrc*)ptData;
	memcpy(ptSerializedProject, ptProject, sizeof(D2TileLibraryHeaderStrc));

	D2TileLibraryEntryStrc* ptSerializedTiles = (D2TileLibraryEntryStrc*)(ptData + sizeof(D2TileLibraryHeaderStrc));
	const int nTileArraySize = sizeof(D2TileLibraryEntryStrc) * ptProject->nTiles;
	memcpy(ptSerializedTiles, ptProject->pTiles, nTileArraySize);
	ptSerializedProject->dwTileStart = (uint8_t*)ptSerializedTiles - ptData;

	uint8_t* pCursor = (uint8_t*)ptSerializedTiles + nTileArraySize;
	for (int nTile = 0; nTile < ptProject->nTiles; ++nTile)
	{
		const D2TileLibraryEntryStrc* ptTile = &ptProject->pTiles[nTile];
		D2TileLibraryEntryStrc* ptSerializedTile = &ptSerializedTiles[nTile];
		ptSerializedTile->pBlocks = nullptr;

		D2TileLibraryBlockStrc* ptSerializedBlocks = (D2TileLibraryBlockStrc*)pCursor;
		int nTileDataSize = sizeof(D2TileLibraryBlockStrc) * ptTile->nBlocks;
		memcpy(ptSerializedBlocks, ptTile->pBlocks, nTileDataSize);

		uint8_t* pBlockData = pCursor + nTileDataSize;
		for (int nBlock = 0; nBlock < ptTile->nBlocks; ++nBlock)
		{
			const D2TileLibraryBlockStrc* ptBlock = &ptTile->pBlocks[nBlock];
			const uint16_t nLength = (uint16_t)ptBlock->nLength;
			memcpy(pBlockData, ptBlock->dwOffset_pData, nLength);
			ptSerializedBlocks[nBlock].dwOffset = pBlockData - pCursor;
			pBlockData += nLength;
			nTileDataSize += nLength;
		}

		ptSerializedTile->nBlockDataSize = nTileDataSize;
		ptSerializedTile->dwBlockOffset = pCursor - ptData;
		pCursor += nTileDataSize;
	}

	ptProject->dwFlags |= TILEPROJECT_FLAG_SERIALIZED;
	ptSerializedProject->dwFlags |= TILEPROJECT_FLAG_SERIALIZED | TILEPROJECT_FLAG_SINGLEBLOCK;
}

//D2CMP.0x6FDFF670 (#10072)
void __stdcall D2CMP_TileProjectNormalize(D2TileLibraryHeaderStrc* ptProject, D2TileLibraryHeaderStrc** pptOutProject, const char* szName)
{
	D2_ASSERT(ptProject->dwVersion == TILEPROJECT_VERSION);

	if (!(ptProject->dwFlags & (TILEPROJECT_FLAG_24BIT | TILEPROJECT_FLAG_SERIALIZED)))
	{
		return;
	}

	uint8_t* pBase = (uint8_t*)ptProject;
	ptProject->pTiles = (D2TileLibraryEntryStrc*)(pBase + ptProject->dwTileStart);
	if (szName)
	{
		strcpy(ptProject->szLibraryName, szName);
	}

	uint8_t* pBlockStart = pBase + sizeof(D2TileLibraryHeaderStrc) + sizeof(D2TileLibraryEntryStrc) * ptProject->nTiles;
	for (int nTile = 0; nTile < ptProject->nTiles; ++nTile)
	{
		D2TileLibraryEntryStrc* ptTile = &ptProject->pTiles[nTile];
		ptTile->szLibraryName = ptProject->szLibraryName;
		ptTile->pBlocks = (D2TileLibraryBlockStrc*)(pBase + ptTile->dwBlockOffset);

		int nTileDataSize = sizeof(D2TileLibraryBlockStrc) * ptTile->nBlocks;
		for (int nBlock = 0; nBlock < ptTile->nBlocks; ++nBlock)
		{
			D2TileLibraryBlockStrc* ptBlock = &ptTile->pBlocks[nBlock];
			ptBlock->dwOffset_pData = pBlockStart + ptBlock->dwOffset;
			nTileDataSize += (uint16_t)ptBlock->nLength;
		}
		pBlockStart += nTileDataSize;
	}

	ptProject->dwFlags = (ptProject->dwFlags & ~TILEPROJECT_FLAG_SERIALIZED) | TILEPROJECT_FLAG_SINGLEBLOCK;
	*pptOutProject = ptProject;
}

//D2CMP.0x6FDFF780
void __stdcall TILECMP_NormalizeHeaderOnly(D2TileLibraryHeaderStrc* ptProject, D2TileLibraryHeaderStrc** pptOutProject, const char* szName)
{
	D2_ASSERT(ptProject->dwVersion == TILEPROJECT_VERSION);

	if (!(ptProject->dwFlags & TILEPROJECT_FLAG_SERIALIZED))
	{
		return;
	}

	ptProject->pTiles = (D2TileLibraryEntryStrc*)((uint8_t*)ptProject + ptProject->dwTileStart);
	strcpy(ptProject->szLibraryName, szName);

	for (int nTile = 0; nTile < ptProject->nTiles; ++nTile)
	{
		D2TileLibraryEntryStrc* ptTile = &ptProject->pTiles[nTile];
		ptTile->szLibraryName = ptProject->szLibraryName;
		D2_ASSERT(ptTile->pBlocks == nullptr);			// ptTile->ptCompArray == NULL
		D2_ASSERT(ptTile->pLRUCacheBlock == nullptr);	// ptTile->ptLRUCache == NULL
	}

	ptProject->dwFlags = (ptProject->dwFlags & ~TILEPROJECT_FLAG_SERIALIZED) | TILEPROJECT_FLAG_SINGLEBLOCK;
	*pptOutProject = ptProject;
}

//D2CMP.0x6FDFF860
D2TileLibraryHashStrc* __fastcall TILECMP_CreateFindTileHash(D2TileLibraryHeaderStrc* ptProject)
{
	D2TileLibraryHashStrc* hFindTile = FINDTILES_CreateHash();
	D2_ASSERT(hFindTile);
	D2_ASSERT(ptProject); // hProject

	for (int nTile = 0; nTile < ptProject->nTiles; ++nTile)
	{
		FINDTILES_AddTile(hFindTile, &ptProject->pTiles[nTile]);
	}

	return hFindTile;
}

//D2CMP.0x6FDFF8F0
void __stdcall TILECMP_FixupBlockPointers(D2TileLibraryEntryStrc* ptTile)
{
	D2_ASSERT(ptTile);

	uint8_t* pBase = (uint8_t*)ptTile->pBlocks;
	for (int nBlock = 0; nBlock < ptTile->nBlocks; ++nBlock)
	{
		ptTile->pBlocks[nBlock].dwOffset_pData = pBase + ptTile->pBlocks[nBlock].dwOffset;
	}
}

//D2CMP.0x6FDFF950 (#10074)
void __stdcall D2CMP_TileProjectIteratePixels(D2TileLibraryHeaderStrc* ptProject, D2CMPPixelCallback pfnCallback)
{
	D2_ASSERT(ptProject);
	D2_ASSERT(ptProject->dwFlags & TILEPROJECT_FLAG_24BIT);

	for (int nTile = 0; nTile < ptProject->nTiles; ++nTile)
	{
		const D2TileLibraryEntryStrc* ptTile = &ptProject->pTiles[nTile];
		for (int nBlock = 0; nBlock < ptTile->nBlocks; ++nBlock)
		{
			const D2TileLibraryBlockStrc* ptBlock = &ptTile->pBlocks[nBlock];
			const int nLength = (uint16_t)ptBlock->nLength;
			const uint8_t* pPixel = ptBlock->dwOffset_pData;
			for (int i = 0; i < nLength; i += 3)
			{
				pfnCallback(pPixel[0] | (pPixel[1] << 8) | (pPixel[2] << 16));
				pPixel += 3;
			}
		}
	}
}

//D2CMP.0x6FDFFA60 (#10075)
void __stdcall D2CMP_TileProjectConvert24To8(D2TileLibraryHeaderStrc* ptProject24, D2TileLibraryHeaderStrc** pptProject8, D2CMPColorConvertCallback pfnConvert)
{
	D2_ASSERT(ptProject24);
	D2_ASSERT(ptProject24->dwFlags & TILEPROJECT_FLAG_24BIT);

	D2TileLibraryHeaderStrc* ptProject8 = D2_ALLOC_STRC(D2TileLibraryHeaderStrc);
	D2_ASSERT(ptProject8);
	memset(ptProject8, 0x00, sizeof(*ptProject8));
	memcpy(ptProject8, ptProject24, sizeof(*ptProject8));
	ptProject8->dwFlags &= ~TILEPROJECT_FLAG_24BIT;
	ptProject8->pTiles = nullptr;

	const int nTileArraySize = sizeof(D2TileLibraryEntryStrc) * ptProject8->nTiles;
	ptProject8->pTiles = (D2TileLibraryEntryStrc*)D2_ALLOC(nTileArraySize);
	D2_ASSERT(ptProject8->pTiles);
	memset(ptProject8->pTiles, 0x00, nTileArraySize);

	for (int nTile = 0; nTile < ptProject24->nTiles; ++nTile)
	{
		const D2TileLibraryEntryStrc* ptTile24 = &ptProject24->pTiles[nTile];
		D2TileLibraryEntryStrc* ptTile8 = &ptProject8->pTiles[nTile];
		memcpy(ptTile8, ptTile24, sizeof(*ptTile8));
		ptTile8->pBlocks = nullptr;

		if (!ptTile8->nBlocks)
		{
			continue;
		}

		const int nSize = sizeof(D2TileLibraryBlockStrc) * ptTile8->nBlocks;
		D2_ASSERT(nSize);
		ptTile8->pBlocks = (D2TileLibraryBlockStrc*)D2_ALLOC(nSize);
		D2_ASSERT(ptTile8->pBlocks); // ptTile8->ptCompArray
		memset(ptTile8->pBlocks, 0x00, nSize);

		for (int nBlock = 0; nBlock < ptTile24->nBlocks; ++nBlock)
		{
			const D2TileLibraryBlockStrc* ptComp24 = &ptTile24->pBlocks[nBlock];
			D2TileLibraryBlockStrc* ptComp8 = &ptTile8->pBlocks[nBlock];
			if (!ptComp24->dwOffset_pData)
			{
				ptComp8->nFormat &= ~TILECOMP_HASDATA;
				ptComp8->nLength = 0;
				ptComp8->dwOffset_pData = nullptr;
				continue;
			}

			SUBTILE_Convert24To8(ptComp8, ptComp24, ptTile24->transparentColorRGB24, pfnConvert);

			const int nLength = (uint16_t)ptComp8->nLength;
			bool bEmpty = true;
			for (int i = 0; i < nLength; ++i)
			{
				if (ptComp8->dwOffset_pData[i])
				{
					bEmpty = false;
					break;
				}
			}

			if (bEmpty)
			{
				D2_FREE(ptComp8->dwOffset_pData);
				ptComp8->nFormat &= ~TILECOMP_HASDATA;
				ptComp8->nLength = 0;
				ptComp8->dwOffset_pData = nullptr;
			}
			else if (ptComp8->nFormat & TILECOMP_SUBTILE)
			{
				int nCompressedSize = 0;
				uint8_t* ptData = SUBTILE_CompressSubTile(ptComp8->dwOffset_pData, &nCompressedSize);
				D2_ASSERT(ptData);
				D2_ASSERT(nCompressedSize < 0x00010000);
				D2_FREE(ptComp8->dwOffset_pData);
				ptComp8->dwOffset_pData = ptData;
				ptComp8->nLength = (uint16_t)nCompressedSize;
			}
			else
			{
				D2_ASSERT(ptComp8->nFormat & TILECOMP_GAMESQUARE);
				SUBTILE_CompressGameSquare(ptComp8);
			}
		}
	}

	*pptProject8 = ptProject8;
}

//D2CMP.0x6FDFFDD0 (#10076)
void __stdcall D2CMP_TileSetHardwareFreeCallback(TileHardwareFreeCallback pfnCallback)
{
	TILECACHE_SetHardwareFreeCallback(pfnCallback);
}
