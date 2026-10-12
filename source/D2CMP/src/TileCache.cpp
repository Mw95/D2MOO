#include "TileCache.h"

#include <cstring>

#include <Archive.h>
#include <Fog.h>

#include "LRUCache.h"
#include "Tilecmp.h"


static D2LRUCacheStrc sgtTileCache;						//D2CMP.0x6FEF1D98
static BOOL sgbTileCacheInitialized;					//D2CMP.0x6FEF1DCC
static uint32_t sgdwTileCacheMaxMemory;					//D2CMP.0x6FEF1DD0
static TileHardwareFreeCallback sgpfnHardwareFreeCallback;	//D2CMP.0x6FEF1DD4


//D2CMP.0x6FDFE680
static void __fastcall TILECACHE_FreeBlockCallback(D2LRUCacheBlockStrc* ptBlock)
{
	D2TileLibraryEntryStrc* ptTile = (D2TileLibraryEntryStrc*)ptBlock->pUserData;
	if (sgpfnHardwareFreeCallback)
	{
		D2_ASSERT(!IsBadCodePtr((FARPROC)sgpfnHardwareFreeCallback));
		sgpfnHardwareFreeCallback(ptTile);
	}

	ptTile->pBlocks = nullptr;
	ptTile->pLRUCacheBlock = nullptr;
}

//D2CMP.0x6FDFE600 (#10089)
void __stdcall D2CMP_TileCacheInit(void* pMemPool, uint32_t dwMaxMemory)
{
	memset(&sgtTileCache, 0x00, sizeof(sgtTileCache));
	sgdwTileCacheMaxMemory = dwMaxMemory;
	LRUCACHE_Init(&sgtTileCache, pMemPool, dwMaxMemory, TILECACHE_FreeBlockCallback, 4096);
	sgbTileCacheInitialized = TRUE;
}

//D2CMP.0x6FDFE640 (#10090)
void __stdcall D2CMP_TileCacheDestroy(BOOL bFreeCache)
{
	if (!sgbTileCacheInitialized)
	{
		D2CMP_DestroyTileHeaders();
		return;
	}

	if (bFreeCache)
	{
		LRUCACHE_Destroy(&sgtTileCache);
	}

	memset(&sgtTileCache, 0x00, sizeof(sgtTileCache));
	sgdwTileCacheMaxMemory = 0;
	D2CMP_DestroyTileHeaders();
}

//D2CMP.0x6FDFE6D0 (#10091)
BOOL __stdcall D2CMP_TileValidate(D2TileLibraryEntryStrc* pTile, int nUnused1, int nUnused2)
{
	if (pTile->pLRUCacheBlock)
	{
		LRUCACHE_Touch(&sgtTileCache, pTile->pLRUCacheBlock);
		return TRUE;
	}

	if (!pTile->nBlocks)
	{
		return FALSE;
	}

	pTile->pLRUCacheBlock = LRUCACHE_Alloc(&sgtTileCache, pTile->nBlockDataSize, pTile);
	pTile->pBlocks = (D2TileLibraryBlockStrc*)pTile->pLRUCacheBlock->lpData;
	memset(pTile->pBlocks, 0x00, pTile->nBlockDataSize);

	HSFILE hFile = nullptr;
	if (!ARCHIVE_OpenFile(nullptr, pTile->szLibraryName, &hFile, FALSE))
	{
		return FALSE;
	}

	ARCHIVE_SetFilePointer(nullptr, hFile, pTile->dwBlockOffset, nullptr, FILE_BEGIN);
	ARCHIVE_ReadFileToBuffer(nullptr, hFile, pTile->pBlocks, pTile->nBlockDataSize);
	ARCHIVE_CloseFile(nullptr, hFile);
	TILECMP_FixupBlockPointers(pTile);
	return TRUE;
}

//D2CMP.0x6FDFE780
int __fastcall TILECACHE_GetProjectHeaderSize(const char* szFileName)
{
	D2TileLibraryHeaderStrc tHeader;
	HSFILE hFile = nullptr;
	if (!ARCHIVE_OpenFile(nullptr, szFileName, &hFile, FALSE))
	{
		return 0;
	}

	ARCHIVE_ReadFileToBuffer(nullptr, hFile, &tHeader, sizeof(tHeader));
	ARCHIVE_CloseFile(nullptr, hFile);
	return sizeof(D2TileLibraryHeaderStrc) + sizeof(D2TileLibraryEntryStrc) * tHeader.nTiles;
}

//D2CMP.0x6FDFE7E0
void __fastcall TILECACHE_SetHardwareFreeCallback(TileHardwareFreeCallback pfnCallback)
{
	sgpfnHardwareFreeCallback = pfnCallback;
}

//D2CMP.0x6FDFE7F0 (#10092)
void __stdcall D2CMP_GetTileCacheHits(uint32_t* pMaxMemory, uint32_t* pMisses, uint32_t* pRequests, int* pUsagePercent)
{
	*pMaxMemory = sgdwTileCacheMaxMemory;
	*pRequests = sgtTileCache.nRequests;
	*pMisses = sgtTileCache.nMisses;
	if (sgtTileCache.dwMaxAllocated)
	{
		*pUsagePercent = 100 * sgtTileCache.dwAllocated / sgtTileCache.dwMaxAllocated;
	}
	else
	{
		*pUsagePercent = -1;
	}
}

//D2CMP.0x6FDFE850 (#10093)
void __stdcall D2CMP_ResetTileCacheHits()
{
	sgtTileCache.nRequests = 0;
	sgtTileCache.nMisses = 0;
}

//D2CMP.0x6FDFE860 (#10102)
void __stdcall D2CMP_TileFreeAsyncLoads()
{
	LRUCACHE_Destroy(&sgtTileCache);
}

//D2CMP.0x6FDFE870
void __fastcall TILECACHE_FreeProjectTiles(D2TileLibraryHeaderStrc* ptProject)
{
	for (int i = 0; i < ptProject->nTiles; ++i)
	{
		D2TileLibraryEntryStrc* ptTile = &ptProject->pTiles[i];
		if (ptTile->pLRUCacheBlock)
		{
			LRUCACHE_Free(&sgtTileCache, ptTile->pLRUCacheBlock);
			ptTile->pBlocks = nullptr;
			ptTile->pLRUCacheBlock = nullptr;
		}
	}
}

//D2CMP.0x6FDFE8C0 (#10105)
void __stdcall D2CMP_10105(int nUnused1, int nUnused2)
{
}
