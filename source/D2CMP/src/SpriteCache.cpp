#include "SpriteCache.h"

#include <cstring>

#include <Fog.h>
#include <Storm.h>

#include "Codec.h"
#include "LRUCache.h"


constexpr int CELDATA_CACHE_MAX_BLOCKS = 0x1000;
constexpr int OFFSET_ARRAYSIZE = 0x4000;
constexpr int SPRITECACHE_PATH_LENGTH = 260;

static D2CelDataHashStrc sgtCelDataHash;					//D2CMP.0x6FED0D18
static D2GfxHashStrc sgtGfxHash;							//D2CMP.0x6FED1D18
static D2GfxCacheStrc sgtGfxCache;							//D2CMP.0x6FEE1D18
static D2LRUCacheStrc sgtCelDataCache;						//D2CMP.0x6FEE1D54
static int32_t sgnCelOffsets[OFFSET_ARRAYSIZE];				//D2CMP.0x6FEE1D88
static BOOL sgbLowEndMachine;								//D2CMP.0x6FEF1D88
static void(__fastcall* sgpfnSpriteHardwareFreeCallback)(int nUnitType, int nClass, int nMode);	//D2CMP.0x6FEF1D8C
static BOOL sgbMissingCelReported;							//D2CMP.0x6FEF1D90
static char sgszTraceFileName[1];							//D2CMP.0x6FEF1D94
static uint32_t sgnCelDataCacheMaxBlocks = CELDATA_CACHE_MAX_BLOCKS;	//D2CMP.0x6FE0F054

static void __fastcall GFXCACHE_Init(D2GfxCacheStrc* pCache, void* pMemPool, uint32_t dwMaxAllocated, GfxCacheFreeCallback pfnFree);
static D2GfxCacheBlockStrc* __fastcall GFXCACHE_AllocBlock(D2GfxCacheStrc* pCache, uint32_t dwSize, D2GfxHashElementStrc* pUserData, BOOL bAsync);
static D2GfxCacheBlockStrc* __fastcall GFXCACHE_FreeBlock(D2GfxCacheStrc* pCache, D2GfxCacheBlockStrc* ptBlock, BOOL bAllowAsync);
static void __fastcall GFXCACHE_ResizeBlock(D2GfxCacheStrc* pCache, D2GfxCacheBlockStrc* ptBlock, uint32_t dwAdditionalSize, BOOL bAllowAsync);
static void __fastcall GFXCACHE_LinkBlock(D2GfxCacheStrc* pCache, D2GfxCacheBlockStrc* ptBlock, BOOL bAsync);
static D2GfxCacheBlockStrc* __fastcall GFXCACHE_PopBlock(D2GfxCacheStrc* pCache, BOOL bAsync);
static void __fastcall GFXCACHE_UnlinkBlock(D2GfxCacheStrc* pCache, D2GfxCacheBlockStrc* ptBlock);

static BOOL __fastcall SPRITECACHE_BuildFilePath(D2GfxDataStrc* ptCelContext, char* szPath, const char* szName);
static D2CelDataStrc* __fastcall SPRITECACHE_GetCelData(D2GfxDataStrc* ptCelContext, char* szPath, char* szName);
static BOOL __fastcall SPRITECACHE_BuildCelName(D2GfxDataStrc* ptCelContext, char* szName);
static void __fastcall SPRITECACHE_InitializeHardwareCelData(D2CelDataStrc* ptCelData, D2GfxDataStrc* ptCelContext, D2GfxNodeStrc* ptGfxNode);
static BOOL __fastcall SPRITECACHE_LoadGfxBlock(D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData, uint32_t nDirBlock, uint32_t nDirBlockSize, const char* szPath);
static D2GfxCellStrc* __fastcall SPRITECACHE_FindCel(D2GfxDataStrc* ptCelContext, D2GfxBlockStrc* ptGfxBlock, uint8_t* pBuffer);
static void __fastcall SPRITECACHE_LoadSiblings(D2GfxDataStrc* ptCelContext, uint32_t nDirBlock, uint32_t nDirBlockSize, D2CelDataStrc* ptCelData, char* szName, char* szPath, BOOL bAsync);
static BOOL __fastcall SPRITECACHE_AsyncLoadGfxBlock(D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData, uint32_t nDirBlock, uint32_t nDirBlockSize, const char* szPath);


//D2CMP.0x6FDFBB70
static void __fastcall SPRITECACHE_FreeGfxBlockCallback(D2GfxHashElementStrc* pElement)
{
	if (sgpfnSpriteHardwareFreeCallback)
	{
		D2GfxNodeStrc* ptGfxNode = pElement->ptGfxNode;
		D2_ASSERT(ptGfxNode);
		sgpfnSpriteHardwareFreeCallback(ptGfxNode->nUnitType, ptGfxNode->nClass, ptGfxNode->nMode);
	}

	GFXHASH_Remove(sgtGfxCache.pMemPool, &sgtGfxHash, pElement);
}

//D2CMP.0x6FDFBBD0
static void __fastcall SPRITECACHE_FreeCelDataCallback(D2LRUCacheBlockStrc* pBlock)
{
	D2CelDataHashElementStrc* pElement = (D2CelDataHashElementStrc*)pBlock->pUserData;
	pElement->pBlock = nullptr;
	CELDATAHASH_Remove(sgtCelDataCache.pMemPool, &sgtCelDataHash, pElement);
}

// Inlined helper
static void SPRITECACHE_DestroyGfxCache()
{
	while (sgtGfxCache.nUsedBlocks)
	{
		if (!GFXCACHE_FreeBlock(&sgtGfxCache, nullptr, TRUE))
		{
			break;
		}
	}

	if (sgtGfxCache.pBlocks)
	{
		D2_FREE_POOL(sgtGfxCache.pMemPool, sgtGfxCache.pBlocks);
		sgtGfxCache.pBlocks = nullptr;
	}

	if (sgtGfxCache.pcs)
	{
		DeleteCriticalSection(sgtGfxCache.pcs);
		D2_FREE(sgtGfxCache.pcs);
	}
}

//D2CMP.0x6FDFB9F0 (#10052)
void __stdcall D2CMP_SpriteCacheInit(void* pMemPool, uint32_t dwSpriteCacheSize, uint32_t dwCelDataCacheSize, uint32_t dwMemoryOverride)
{
	CODEC_InitLock();

	uint32_t dwMemory = dwMemoryOverride;
	if (!dwMemory)
	{
		uint8_t* pSysInfo = (uint8_t*)FOG_GetSystemInfo();
		D2_ASSERT(pSysInfo != NULL);
		dwMemory = *(uint32_t*)&pSysInfo[0xC] - 0xB00000;
	}

	sgbLowEndMachine = dwMemory < 0x4000000;
	FOG_Trace("Low End Machine: %s", sgbLowEndMachine ? "TRUE" : "FALSE");

	CELDATAHASH_Init(&sgtCelDataHash);
	LRUCACHE_Destroy(&sgtCelDataCache);
	memset(&sgtCelDataCache, 0x00, sizeof(sgtCelDataCache));
	LRUCACHE_Init(&sgtCelDataCache, pMemPool, dwCelDataCacheSize, SPRITECACHE_FreeCelDataCallback, sgnCelDataCacheMaxBlocks);
	FOG_Trace("D2CMPSpriteCacheInit: %d", sgtCelDataCache.dwMaxAllocated);

	memset(&sgtGfxHash, 0x00, sizeof(sgtGfxHash));
	GFXHASH_Init(&sgtGfxHash);

	SPRITECACHE_DestroyGfxCache();
	memset(&sgtGfxCache, 0x00, sizeof(sgtGfxCache));
	GFXCACHE_Init(&sgtGfxCache, pMemPool, dwSpriteCacheSize, SPRITECACHE_FreeGfxBlockCallback);
}

//D2CMP.0x6FDFBBF0 (#10053)
void __stdcall D2CMP_SpriteCacheDestroy(BOOL bFreeMemory)
{
	if (bFreeMemory)
	{
		SPRITECACHE_DestroyGfxCache();
	}

	memset(&sgtGfxCache, 0x00, sizeof(sgtGfxCache));

	if (bFreeMemory)
	{
		LRUCACHE_Destroy(&sgtCelDataCache);
	}

	memset(&sgtCelDataCache, 0x00, sizeof(sgtCelDataCache));
	CODEC_DestroyLock();
}

//D2CMP.0x6FDFBCB0
static DWORD __stdcall SPRITECACHE_DecodeCallback(void* pFileData, size_t nDataLength, AsyncDataLoadFileCallback* pCallbackData)
{
	if (!sgtGfxCache.pcs)
	{
		return 0;
	}

	D2CelDataStrc* ptCelData = (D2CelDataStrc*)(uintptr_t)pCallbackData->userData[0];
	D2GfxBlockStrc* ptGfxBlock = (D2GfxBlockStrc*)(uintptr_t)pCallbackData->userData[1];
	D2GfxCacheBlockStrc* ptCacheBlock = ptGfxBlock->pCacheBlock;
	ptCacheBlock->dwFlags |= GFXCACHEBLOCK_FLAG_LOCKED;

	pCallbackData->pData = CODEC_DecodeDirections((const uint8_t*)pFileData, sgtGfxCache.pMemPool, nDataLength, ptCelData, ptGfxBlock, pCallbackData->userData[2], pCallbackData->userData[3], (uint32_t*)&pCallbackData->nFileSize, ptCelData->szName);

	ptCacheBlock->dwFlags &= ~GFXCACHEBLOCK_FLAG_LOCKED;
	ptGfxBlock->bFlags &= ~GFXBLOCK_FLAG_DECODING;
	GFXCACHE_ResizeBlock(&sgtGfxCache, ptCacheBlock, pCallbackData->nFileSize, FALSE);
	if (!pCallbackData->pData)
	{
		ptGfxBlock->bFlags |= GFXBLOCK_FLAG_NOFILE;
	}
	return 1;
}

// Inlined helper: the direction blocks may use less directions than the file
static void SPRITECACHE_ConvertDirection(D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData, uint32_t nDirBlockSize)
{
	const uint32_t nDirections = ptCelData->tHeader.dwNumDirections;
	const int nDirection = D2CMP_CelConvertDir((ptCelContext->nDirection * nDirections) >> 6, nDirections, nDirBlockSize, ptCelContext->fState & 4);
	if (nDirections > 1)
	{
		ptCelContext->nDirection = ((uint32_t)nDirection << 6) / nDirections;
	}
	else
	{
		ptCelContext->nDirection = 1;
	}
}

//D2CMP.0x6FDFBD40 (#10055)
BOOL __stdcall D2CMP_SpriteValidate(D2GfxDataStrc* ptCelContext, BOOL bTestOnly, BOOL bAsync)
{
	if (!ptCelContext)
	{
		return FALSE;
	}

	ptCelContext->pCurrentCell = nullptr;
	if (ptCelContext->pCellFile)
	{
		ptCelContext->pCurrentCell = D2CMP_CelGetHandle(ptCelContext);
		return TRUE;
	}

	char szPath[SPRITECACHE_PATH_LENGTH];
	char szName[SPRITECACHE_PATH_LENGTH];
	D2CelDataStrc* ptCelData = SPRITECACHE_GetCelData(ptCelContext, szPath, szName);

	uint32_t nDirBlock = 0;
	uint32_t nDirBlockSize = 0;
	D2GfxHashElementStrc* pElement = GFXHASH_Find(&sgtGfxHash, ptCelContext, &nDirBlock, &nDirBlockSize, ptCelData);
	BOOL bResult = TRUE;
	BOOL bLoaded = FALSE;
	if (nDirBlockSize > 1 && nDirBlock)
	{
		if (pElement)
		{
			if (!pElement->ptGfxNode->tGfxBlock.lpAsyncData)
			{
				return FALSE;
			}

			bLoaded = FOG_AsyncDataTestLoaded(pElement->ptGfxNode->tGfxBlock.lpAsyncData);
		}

		if (!bLoaded && !(ptCelData->bFlags & CELDATAFLAG_NOFILE))
		{
			SPRITECACHE_ConvertDirection(ptCelContext, ptCelData, nDirBlockSize);
			pElement = GFXHASH_Find(&sgtGfxHash, ptCelContext, &nDirBlock, &nDirBlockSize, ptCelData);
		}
	}

	if (!pElement)
	{
		if (bTestOnly)
		{
			return FALSE;
		}

		if (!szPath[0] && !SPRITECACHE_BuildFilePath(ptCelContext, szPath, szName))
		{
			return FALSE;
		}

		bResult = SPRITECACHE_LoadGfxBlock(ptCelContext, ptCelData, nDirBlock, nDirBlockSize, szPath);
		if (bResult)
		{
			SPRITECACHE_LoadSiblings(ptCelContext, nDirBlock, nDirBlockSize, ptCelData, szName, szPath, bAsync);
		}
		return bResult;
	}

	D2GfxNodeStrc* ptGfxNode = pElement->ptGfxNode;
	if (!ptGfxNode || (ptGfxNode->tGfxBlock.bFlags & GFXBLOCK_FLAG_NOFILE) || !ptGfxNode->tGfxBlock.lpAsyncData)
	{
		return FALSE;
	}

	if (bTestOnly)
	{
		return FOG_AsyncDataTestLoaded(ptGfxNode->tGfxBlock.lpAsyncData) != 0;
	}

	// Move the block at the end of the least recently used list
	D2GfxCacheBlockStrc* ptBlock = pElement->pCacheBlock;
	if (sgtGfxCache.nUsedBlocks)
	{
		++sgtGfxCache.nRequests;
		EnterCriticalSection(sgtGfxCache.pcs);
		D2_ASSERT(ptBlock);
		GFXCACHE_UnlinkBlock(&sgtGfxCache, ptBlock);
		ptBlock->dwFlags &= ~GFXCACHEBLOCK_FLAG_ASYNC;
		GFXCACHE_LinkBlock(&sgtGfxCache, ptBlock, FALSE);
		LeaveCriticalSection(sgtGfxCache.pcs);
	}

	if (!ptGfxNode->tGfxBlock.fHardwareCelData)
	{
		SPRITECACHE_InitializeHardwareCelData(ptCelData, ptCelContext, ptGfxNode);
	}

	D2GfxCellStrc* pCel = nullptr;
	if (ptGfxNode->tGfxBlock.lpAsyncData)
	{
		uint8_t* pBuffer = (uint8_t*)FOG_AsyncDataGetBuffer(ptGfxNode->tGfxBlock.lpAsyncData);
		if (pBuffer)
		{
			ptCelContext->nMaxFrames = ptGfxNode->tGfxBlock.bNumCelsPerDir;
			pCel = SPRITECACHE_FindCel(ptCelContext, &ptGfxNode->tGfxBlock, pBuffer);
		}
	}

	ptCelContext->pCurrentCell = pCel;
	if (!pCel)
	{
		if (!sgbMissingCelReported)
		{
			sgbMissingCelReported = TRUE;
			FOG_Trace("Couldn't get cel handle in for:%s  TYPE:%d  CLASS:%d  MODE:%d  FILE:%s  LINE:%d", ptCelContext->pName, ptCelContext->nUnitType, ptCelContext->nUnitIndex, ptCelContext->nMode, __FILE__, __LINE__);
		}
		return FALSE;
	}

	if (!bLoaded && !nDirBlock && nDirBlockSize > 1)
	{
		if (!szPath[0] && !SPRITECACHE_BuildFilePath(ptCelContext, szPath, szName))
		{
			return FALSE;
		}

		SPRITECACHE_LoadSiblings(ptCelContext, nDirBlock, nDirBlockSize, ptCelData, szName, szPath, bAsync);
	}

	return bResult;
}

// Inlined helper: tokens are 3 characters long, padded with spaces
static void SPRITECACHE_CopyToken(char* szDest, const char* szToken)
{
	for (int i = 0; i < 3; ++i)
	{
		szDest[i] = szToken[i] == ' ' ? '\0' : szToken[i];
	}
	szDest[3] = '\0';
}

// Inlined helper: some monster sprites are never compressed
static bool SPRITECACHE_IsMonsterUncompressed(const D2GfxDataStrc* ptCelContext)
{
	switch (ptCelContext->nUnitIndex)
	{
	case 242:
	case 251:
	case 367:
	case 521:
		return true;

	case 243:
	case 284:
	case 333:
	case 544:
	case 559:
	case 570:
		return ptCelContext->nMode == 0;

	default:
		return false;
	}
}

// Inlined helper: some object sprites are never compressed
static bool SPRITECACHE_IsObjectUncompressed(const D2GfxDataStrc* ptCelContext)
{
	return ptCelContext->nUnitIndex == 342 || ptCelContext->nUnitIndex == 563;
}

//D2CMP.0x6FDFC200
static BOOL __fastcall SPRITECACHE_BuildFilePath(D2GfxDataStrc* ptCelContext, char* szPath, const char* szName)
{
	if (!szName[0])
	{
		szPath[0] = '\0';
		return FALSE;
	}

	switch (ptCelContext->nUnitType)
	{
	case GFXUNIT_MISSILE:
		if (!ptCelContext->pName)
		{
			szPath[0] = '\0';
			return FALSE;
		}

		if (gbCompressedData)
		{
			wsprintfA(szPath, "%s\\%s.dcc", "DATA\\GLOBAL\\MISSILES", ptCelContext->pName);
			ptCelContext->fFlags |= 1;
		}
		else
		{
			wsprintfA(szPath, "%s\\%s.dc6", "DATA\\GLOBAL\\MISSILES", ptCelContext->pName);
		}
		return TRUE;

	case GFXUNIT_ITEM:
		if (!ptCelContext->pName)
		{
			szPath[0] = '\0';
			return FALSE;
		}

		if (ptCelContext->nMode != 4 && ptCelContext->nMode != 3)
		{
			szPath[0] = '\0';
			return FALSE;
		}

		wsprintfA(szPath, "%s\\items\\%s.dc6", "DATA\\GLOBAL", szName);
		return TRUE;

	case GFXUNIT_OVERLAY:
		if (!(ptCelContext->fState & 2))
		{
			szPath[0] = '\0';
			return FALSE;
		}

		if (ptCelContext->nOverlay != 122 && gbCompressedData)
		{
			wsprintfA(szPath, "%s\\%s.dcc", "DATA\\GLOBAL\\OVERLAYS", szName);
			ptCelContext->fFlags |= 1;
		}
		else
		{
			wsprintfA(szPath, "%s\\%s.dc6", "DATA\\GLOBAL\\OVERLAYS", szName);
		}
		return TRUE;

	default:
		break;
	}

	BOOL bCompressed = gbCompressedData;
	if (bCompressed && !SStrCmpI(szName, "OYTRlitTNhth", 0x7FFFFFFF))
	{
		bCompressed = FALSE;
		ptCelContext->fFlags &= ~1;
	}

	const char* szDirectory = nullptr;
	switch (ptCelContext->nUnitType)
	{
	case GFXUNIT_PLAYER:
		szDirectory = "DATA\\GLOBAL\\CHARS";
		break;

	case GFXUNIT_MONSTER:
		szDirectory = "DATA\\GLOBAL\\MONSTERS";
		if (SPRITECACHE_IsMonsterUncompressed(ptCelContext))
		{
			bCompressed = FALSE;
		}
		break;

	case GFXUNIT_OBJECT:
		szDirectory = "DATA\\GLOBAL\\OBJECTS";
		if (SPRITECACHE_IsObjectUncompressed(ptCelContext))
		{
			bCompressed = FALSE;
		}
		break;

	default:
		szPath[0] = '\0';
		return FALSE;
	}

	char szToken[4];
	char szComponent[4];
	SPRITECACHE_CopyToken(szToken, ptCelContext->szToken);
	SPRITECACHE_CopyToken(szComponent, ptCelContext->szComponent);
	if (bCompressed)
	{
		wsprintfA(szPath, "%s\\%s\\%s\\%s.dcc", szDirectory, szToken, szComponent, szName);
		ptCelContext->fFlags |= 1;
	}
	else
	{
		wsprintfA(szPath, "%s\\%s\\%s\\%s.dc6", szDirectory, szToken, szComponent, szName);
	}
	return TRUE;
}

//D2CMP.0x6FDFC530
static D2CelDataStrc* __fastcall SPRITECACHE_GetCelData(D2GfxDataStrc* ptCelContext, char* szPath, char* szName)
{
	szPath[0] = '\0';
	if (!SPRITECACHE_BuildCelName(ptCelContext, szName))
	{
		return nullptr;
	}

	D2CelDataStrc* ptCelData = nullptr;
	D2CelDataHashElementStrc* ptHashTableElement = CELDATAHASH_Find(&sgtCelDataHash, szName);
	if (ptHashTableElement)
	{
		LRUCACHE_Touch(&sgtCelDataCache, ptHashTableElement->pBlock);
		ptCelData = (D2CelDataStrc*)ptHashTableElement->pBlock->lpData;
	}
	else
	{
		if (!SPRITECACHE_BuildFilePath(ptCelContext, szPath, szName))
		{
			return nullptr;
		}

		ptHashTableElement = CELDATAHASH_Add(sgtCelDataCache.pMemPool, &sgtCelDataHash, nullptr, szName);
		D2_ASSERT(ptHashTableElement);

		ptHashTableElement->pBlock = LRUCACHE_Alloc(&sgtCelDataCache, sizeof(D2CelDataStrc), ptHashTableElement);
		D2_ASSERT(ptHashTableElement->pBlock); // ptHashTableElement->lpBlock

		ptCelData = (D2CelDataStrc*)ptHashTableElement->pBlock->lpData;
		memset(ptCelData, 0x00, sizeof(*ptCelData));
		strcpy(ptCelData->szName, szName);

		if (ptCelContext->fFlags & 1)
		{
			if (!CODEC_ReadCelDataHeader(szPath, ptCelData))
			{
				ptCelData->bFlags |= CELDATAFLAG_NOFILE;
			}
		}
		else
		{
			HSFILE hFile = nullptr;
			FOG_FOpenFile(szPath, &hFile);
			if (!hFile)
			{
				ptCelData->bFlags |= CELDATAFLAG_NOFILE;
			}
			else
			{
				uint32_t aHeader[7] = {};
				FOG_FReadFile(hFile, aHeader, 6 * sizeof(uint32_t), nullptr, 0, 0, 0);
				const uint32_t nFileSize = FOG_FGetFileSize(hFile, nullptr);
				ptCelData->tHeader.dwFramesPerDirection = aHeader[5];
				ptCelData->tHeader.dwFlags = aHeader[1];
				ptCelData->tHeader.dwVersion = aHeader[0];
				ptCelData->tHeader.dwNumDirections = aHeader[4];
				ptCelData->tHeader.eFormat = aHeader[2];

				const uint32_t dwTotalCels = aHeader[5] * aHeader[4];
				D2_ASSERT(dwTotalCels < OFFSET_ARRAYSIZE);
				FOG_FReadFile(hFile, sgnCelOffsets, sizeof(int32_t) * dwTotalCels, nullptr, 0, 0, 0);
				FOG_FCloseFile(hFile);

				D2_ASSERT(ptCelData->tHeader.dwNumDirections < MAX_DIROFFSETS);
				for (uint32_t i = 0; i < ptCelData->tHeader.dwNumDirections; ++i)
				{
					ptCelData->nOffsets[i] = sgnCelOffsets[i * ptCelData->tHeader.dwFramesPerDirection];
				}
				ptCelData->nOffsets[ptCelData->tHeader.dwNumDirections] = nFileSize;
			}
		}
	}

	D2_ASSERTM(ptCelData, "[sValidateCelData] ptCelData was NULL.\n");
	return ptCelData;
}

// Inlined helper: appends the characters of a token until the first space
static char* SPRITECACHE_AppendToken(char* szDest, const char* szToken)
{
	for (int i = 0; i < 3 && szToken[i] != ' '; ++i)
	{
		*szDest++ = szToken[i];
	}
	return szDest;
}

//D2CMP.0x6FDFC780
static BOOL __fastcall SPRITECACHE_BuildCelName(D2GfxDataStrc* ptCelContext, char* szName)
{
	const BOOL bCompressed = gbCompressedData;
	switch (ptCelContext->nUnitType)
	{
	case GFXUNIT_PLAYER:
	case GFXUNIT_MONSTER:
	case GFXUNIT_OBJECT:
	{
		char* pEnd = szName;
		pEnd = SPRITECACHE_AppendToken(pEnd, ptCelContext->szToken);
		pEnd = SPRITECACHE_AppendToken(pEnd, ptCelContext->szComponent);
		pEnd = SPRITECACHE_AppendToken(pEnd, ptCelContext->szArmorType);
		pEnd = SPRITECACHE_AppendToken(pEnd, ptCelContext->szMode);
		pEnd = SPRITECACHE_AppendToken(pEnd, ptCelContext->szHitClass);
		*pEnd = '\0';

		if (ptCelContext->nUnitType == GFXUNIT_MONSTER && SPRITECACHE_IsMonsterUncompressed(ptCelContext))
		{
			return TRUE;
		}

		if (ptCelContext->nUnitType == GFXUNIT_OBJECT && SPRITECACHE_IsObjectUncompressed(ptCelContext))
		{
			return TRUE;
		}

		if (bCompressed)
		{
			ptCelContext->fFlags |= 1;
		}
		return TRUE;
	}

	case GFXUNIT_MISSILE:
		if (!ptCelContext->pName)
		{
			break;
		}

		if (bCompressed)
		{
			ptCelContext->fFlags |= 1;
		}
		strcpy(szName, ptCelContext->pName);
		return TRUE;

	case GFXUNIT_ITEM:
		if (!ptCelContext->pName)
		{
			break;
		}

		strcpy(szName, ptCelContext->pName);
		return TRUE;

	case GFXUNIT_OVERLAY:
		if (!(ptCelContext->fState & 2) || !ptCelContext->pName)
		{
			break;
		}

		if (ptCelContext->nOverlay != 122 && bCompressed)
		{
			ptCelContext->fFlags |= 1;
		}
		strcpy(szName, ptCelContext->pName);
		return TRUE;

	default:
		break;
	}

	szName[0] = '\0';
	return FALSE;
}

// Inlined helper
static int SPRITECACHE_GetCelSize(const D2GfxCellStrc* pCel)
{
	return pCel->dwLength + pCel->dwHardwareDataSize + offsetof(D2GfxCellStrc, pPixels) + 3;
}

//D2CMP.0x6FDFCA30
static void __fastcall SPRITECACHE_InitializeHardwareCelData(D2CelDataStrc* ptCelData, D2GfxDataStrc* ptCelContext, D2GfxNodeStrc* ptGfxNode)
{
	D2_ASSERT(ptCelContext);
	D2_ASSERT(ptGfxNode);
	D2_ASSERT(!(ptCelData->bFlags & CELDATAFLAG_NOFILE));

	D2GfxBlockStrc* ptGfxBlock = &ptGfxNode->tGfxBlock;
	D2_ASSERT(!ptGfxBlock->fHardwareCelData);

	const uint32_t nCels = (uint32_t)ptGfxBlock->bNumCelsPerDir * ptGfxBlock->bNumDirections;
	D2GfxCellNodeStrc* pCellNodes = (D2GfxCellNodeStrc*)D2_ALLOC_POOL(sgtGfxCache.pMemPool, sizeof(D2GfxCellNodeStrc) * nCels);
	memset(pCellNodes, 0x00, sizeof(D2GfxCellNodeStrc) * nCels);

	uint8_t* lpbData = (uint8_t*)FOG_AsyncDataGetBuffer(ptGfxBlock->lpAsyncData);
	D2_ASSERT(lpbData);

	int nOffset = ptGfxBlock->nOffsets[ptGfxBlock->bFirstDirection];
	for (uint32_t i = 0; i < nCels; ++i)
	{
		D2GfxCellStrc* pCel = (D2GfxCellStrc*)&lpbData[nOffset];
		if (pCel->dwFlags || pCel->dwWidth > 256 || pCel->dwHeight > 256)
		{
			char szName[SPRITECACHE_PATH_LENGTH];
			char szPath[SPRITECACHE_PATH_LENGTH];
			char szMessage[512];
			SPRITECACHE_BuildCelName(ptCelContext, szName);
			SPRITECACHE_BuildFilePath(ptCelContext, szPath, szName);
			FOG_DisplayHalt(FOG_csprintf(szMessage, "[sInitializeHardwareCelData] There offsets are screwed for the Cel File:\n\n%s\n", szPath), __FILE__, __LINE__);
			exit(-1);
		}

		pCel->pCellNode = &pCellNodes[i];
		nOffset += SPRITECACHE_GetCelSize(pCel);
	}

	ptGfxBlock->fHardwareCelData = TRUE;
}

// Inlined helper
static void SPRITECACHE_SetupGfxNode(D2GfxNodeStrc* ptGfxNode, D2GfxDataStrc* ptCelContext, D2GfxCacheBlockStrc* ptCacheBlock)
{
	memset(ptGfxNode, 0x00, sizeof(*ptGfxNode));
	ptGfxNode->dwName[0] = ptCelContext->dwName[0];
	ptGfxNode->dwName[3] = ptCelContext->dwName[3];
	ptGfxNode->dwName[1] = ptCelContext->dwName[1];
	ptGfxNode->dwName[2] = ptCelContext->dwName[2];
	ptGfxNode->dwName[4] = ptCelContext->dwName[4];
	ptGfxNode->tGfxBlock.pCacheBlock = ptCacheBlock;
}

// Inlined helper: copies the offsets of the loaded directions into the block
static void SPRITECACHE_SetupGfxBlockOffsets(D2GfxBlockStrc* ptGfxBlock, D2CelDataStrc* ptCelData, uint32_t nDirBlock, uint32_t nDirBlockSize, uint32_t nFirst, uint32_t nLast)
{
	ptGfxBlock->bNumDirections = (uint8_t)nDirBlockSize;
	ptGfxBlock->bFirstDirection = (uint8_t)(nDirBlockSize * nDirBlock);
	ptGfxBlock->bNumCelsPerDir = (uint8_t)ptCelData->tHeader.dwFramesPerDirection;
	ptGfxBlock->bNumOffsets = (uint8_t)ptCelData->tHeader.dwNumDirections + 1;

	const int32_t nBaseOffset = ptCelData->nOffsets[nFirst];
	for (uint32_t i = nFirst; i <= nLast; ++i)
	{
		D2_ASSERT(i < MAX_DIROFFSETS);
		ptGfxBlock->nOffsets[i] = ptCelData->nOffsets[i] - nBaseOffset;
		D2_ASSERT(ptGfxBlock->nOffsets[i] >= 0); // ptGfxNode->tGfxBlock.nOffsets[i] >= 0
	}
}

// Inlined helper
static void SPRITECACHE_SetupDecodeCallback(AsyncDataLoadFileCallback* pCallback, D2CelDataStrc* ptCelData, D2GfxBlockStrc* ptGfxBlock, uint32_t nFirstDirection, uint32_t nDirections)
{
	memset(pCallback, 0x00, sizeof(*pCallback));
	pCallback->callback = SPRITECACHE_DecodeCallback;
	pCallback->userData[0] = (DWORD)(uintptr_t)ptCelData;
	pCallback->userData[1] = (DWORD)(uintptr_t)ptGfxBlock;
	pCallback->userData[2] = nFirstDirection;
	pCallback->userData[3] = nDirections;
}

//D2CMP.0x6FDFCC10
static BOOL __fastcall SPRITECACHE_LoadGfxBlock(D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData, uint32_t nDirBlock, uint32_t nDirBlockSize, const char* szPath)
{
	if (!ptCelData)
	{
		return FALSE;
	}

	D2GfxCacheBlockStrc* ptCacheBlock = GFXCACHE_AllocBlock(&sgtGfxCache, sizeof(D2GfxNodeStrc), nullptr, FALSE);
	if (!ptCacheBlock)
	{
		return FALSE;
	}

	D2GfxNodeStrc* ptGfxNode = (D2GfxNodeStrc*)ptCacheBlock->lpData;
	SPRITECACHE_SetupGfxNode(ptGfxNode, ptCelContext, ptCacheBlock);
	ptGfxNode->nUnitType = ptCelContext->nUnitType;

	if (!(ptCelData->bFlags & CELDATAFLAG_NOFILE))
	{
		ptGfxNode->nClass = ptCelContext->nUnitIndex;
		ptGfxNode->nMode = ptCelContext->nMode;

		bool bLoad = true;
		uint32_t nFirst = 0;
		uint32_t nLast = 0;
		if ((ptCelContext->nUnitType == GFXUNIT_OVERLAY && (ptCelContext->fState & 2)) || ptCelContext->nUnitType == GFXUNIT_MISSILE)
		{
			if (nDirBlockSize == 1)
			{
				nFirst = D2CMP_CelGameDirToFileDir(ptCelContext->nDirection, ptCelData->tHeader.dwNumDirections);
				nLast = nFirst + 1;
			}
			else
			{
				bLoad = false;
			}
		}
		else if (ptCelContext->nUnitType == GFXUNIT_OBJECT)
		{
			nFirst = 0;
			nLast = 1;
		}
		else if (ptCelContext->nUnitType == GFXUNIT_ITEM)
		{
			nFirst = ptCelContext->nDirection;
			nLast = nFirst + 1;
		}
		else if (ptCelContext->nUnitType == GFXUNIT_MONSTER && nDirBlockSize == 1)
		{
			nFirst = D2CMP_CelGameDirToFileDir(ptCelContext->nDirection, ptCelData->tHeader.dwNumDirections);
			nLast = nFirst + nDirBlockSize;
		}
		else
		{
			nFirst = nDirBlock * nDirBlockSize;
			nLast = nFirst + nDirBlockSize;
		}

		if (bLoad)
		{
			const int nSize = ptCelData->nOffsets[nLast] - ptCelData->nOffsets[nFirst];
			if (!nSize)
			{
				char szName[SPRITECACHE_PATH_LENGTH];
				char szFilePath[SPRITECACHE_PATH_LENGTH];
				SPRITECACHE_BuildCelName(ptCelContext, szName);
				SPRITECACHE_BuildFilePath(ptCelContext, szFilePath, szName);
				FOG_Trace("[sValidateSynchLoadDirectionBlock] There are differences between the CEL Data and the Cel File: %s", szFilePath);
			}
			else if (!ptGfxNode->tGfxBlock.lpAsyncData)
			{
				SPRITECACHE_SetupGfxBlockOffsets(&ptGfxNode->tGfxBlock, ptCelData, nDirBlock, nDirBlockSize, nFirst, nLast);

				if (ptCelData->bFlags & CELDATAFLAG_DCC)
				{
					AsyncDataLoadFileCallback tCallback;
					SPRITECACHE_SetupDecodeCallback(&tCallback, ptCelData, &ptGfxNode->tGfxBlock, nDirBlock * nDirBlockSize, nDirBlockSize);
					ptGfxNode->tGfxBlock.bFlags |= GFXBLOCK_FLAG_DECODING;
					ptGfxNode->tGfxBlock.lpAsyncData = FOG_AsyncDataLoadFileEx(sgtGfxCache.pMemPool, szPath, FALSE, ptCelData->nOffsets[nFirst], nSize, nullptr, &tCallback, -2, __FILE__, __LINE__);
					FOG_AsyncDataGetBufferSize(ptGfxNode->tGfxBlock.lpAsyncData);
				}
				else
				{
					ptGfxNode->tGfxBlock.lpAsyncData = FOG_AsyncDataLoadFileEx(sgtGfxCache.pMemPool, szPath, FALSE, ptCelData->nOffsets[nFirst], nSize, nullptr, nullptr, -2, __FILE__, __LINE__);
				}

				D2_ASSERT(ptGfxNode->tGfxBlock.lpAsyncData);
			}
		}
	}

	D2GfxHashElementStrc* ptHashTableElement = GFXHASH_Add(sgtGfxCache.pMemPool, &sgtGfxHash, ptGfxNode, ptCelContext, ptCelData);
	D2_ASSERT(ptHashTableElement);
	ptCacheBlock->pUserData = ptHashTableElement;
	ptHashTableElement->pCacheBlock = ptCacheBlock;

	if (ptCelData->bFlags & CELDATAFLAG_NOFILE)
	{
		ptGfxNode->tGfxBlock.bFlags |= GFXBLOCK_FLAG_NOFILE;
		return FALSE;
	}

	if (!ptGfxNode->tGfxBlock.fHardwareCelData)
	{
		SPRITECACHE_InitializeHardwareCelData(ptCelData, ptCelContext, ptGfxNode);
	}

	D2GfxCellStrc* pCel = nullptr;
	if (ptGfxNode->tGfxBlock.lpAsyncData)
	{
		uint8_t* pBuffer = (uint8_t*)FOG_AsyncDataGetBuffer(ptGfxNode->tGfxBlock.lpAsyncData);
		if (pBuffer)
		{
			ptCelContext->nMaxFrames = ptGfxNode->tGfxBlock.bNumCelsPerDir;
			pCel = SPRITECACHE_FindCel(ptCelContext, &ptGfxNode->tGfxBlock, pBuffer);
		}
	}

	ptCelContext->pCurrentCell = pCel;
	if (!pCel)
	{
		FOG_Trace("Couldn't get cel handle in for:%s  FILE:%s  LINE:%d", ptCelContext->pName, __FILE__, __LINE__);
		return FALSE;
	}

	return TRUE;
}

//D2CMP.0x6FDFD020
static D2GfxCellStrc* __fastcall SPRITECACHE_FindCel(D2GfxDataStrc* ptCelContext, D2GfxBlockStrc* ptGfxBlock, uint8_t* pBuffer)
{
	if (!pBuffer || !ptGfxBlock)
	{
		return nullptr;
	}

	if (ptCelContext->nFrame >= ptGfxBlock->bNumCelsPerDir)
	{
		FOG_Trace("(ptCelContext->dwCel < ptGfxBlock->bNumCelsPerDir)");
		return nullptr;
	}

	int nDirection;
	if (ptCelContext->nUnitType == GFXUNIT_OBJECT)
	{
		nDirection = 0;
	}
	else if (ptCelContext->nUnitType == GFXUNIT_ITEM)
	{
		nDirection = ptCelContext->nDirection;
	}
	else
	{
		nDirection = D2CMP_CelGameDirToFileDir(ptCelContext->nDirection, ptGfxBlock->bNumOffsets - 1);
	}

	if (nDirection >= ptGfxBlock->bNumOffsets - 1)
	{
		FOG_Trace("SpriteCache.cpp:sFindCel()  (nDirection >= (int)ptGfxBlock->bNumOffsets - 1)");
		return nullptr;
	}

	int nOffset = ptGfxBlock->nOffsets[nDirection];
	if (nOffset < 0)
	{
		FOG_Trace("SpriteCache.cpp:sFindCel()  (nOffset < 0)");
		return nullptr;
	}

	D2GfxCellStrc* pCel = nullptr;
	for (int nFrame = 0; nFrame <= (int)ptCelContext->nFrame; ++nFrame)
	{
		pCel = (D2GfxCellStrc*)&pBuffer[nOffset];
		if (pCel->dwFlags)
		{
			FOG_Trace("SpriteCache.cpp:sFindCel()  (ptCel->dwFlags != 0)");
			return nullptr;
		}

		if (pCel->dwWidth > 256 || pCel->dwHeight > 256)
		{
			FOG_Trace("SpriteCache.cpp:sFindCel()  (ptCel->dwWidth > 256 || ptCel->dwHeight > 256)");
			return nullptr;
		}

		nOffset += SPRITECACHE_GetCelSize(pCel);
		if (nOffset < 0)
		{
			FOG_Trace("SpriteCache.cpp:sFindCel():2  (nOffset < 0)");
			return nullptr;
		}
	}

	return pCel;
}

//D2CMP.0x6FDFD160
static void __fastcall SPRITECACHE_LoadSiblings(D2GfxDataStrc* ptCelContext, uint32_t nDirBlock, uint32_t nDirBlockSize, D2CelDataStrc* ptCelData, char* szName, char* szPath, BOOL bAsync)
{
	if (!ptCelData || !ptCelContext)
	{
		return;
	}

	BOOL bLoadSiblings = TRUE;
	if (!(ptCelContext->nUnitType == GFXUNIT_OVERLAY && (ptCelContext->fState & 2)) && ptCelContext->nUnitType == GFXUNIT_PLAYER)
	{
		if (!(ptCelContext->fState & 8) || !ptCelContext->nMode || ptCelContext->nMode == 17 || sgbLowEndMachine)
		{
			bLoadSiblings = FALSE;
		}
	}

	if (nDirBlock || nDirBlockSize <= 1 || !bLoadSiblings)
	{
		return;
	}

	const int nDirection = D2CMP_CelConvertBlock(nDirBlockSize, 2 * nDirBlockSize);
	if (ptCelData->tHeader.dwNumDirections > 1)
	{
		ptCelContext->nDirection = ((uint32_t)nDirection << 6) / ptCelData->tHeader.dwNumDirections;
	}
	else
	{
		ptCelContext->nDirection = 1;
	}

	if (GFXHASH_Find(&sgtGfxHash, ptCelContext, &nDirBlock, &nDirBlockSize, ptCelData))
	{
		return;
	}

	D2_ASSERT(nDirBlock == 1); // dwDirBlock == 1
	D2_ASSERT(nDirBlockSize > 1); // dwDirBlockSize > 1

	if (!szName[0] && !SPRITECACHE_BuildCelName(ptCelContext, szName))
	{
		return;
	}

	if (!szPath[0] && !SPRITECACHE_BuildFilePath(ptCelContext, szPath, szName))
	{
		return;
	}

	if (bAsync)
	{
		SPRITECACHE_AsyncLoadGfxBlock(ptCelContext, ptCelData, nDirBlock, nDirBlockSize, szPath);
	}
	else
	{
		SPRITECACHE_LoadGfxBlock(ptCelContext, ptCelData, nDirBlock, nDirBlockSize, szPath);
	}
}

//D2CMP.0x6FDFD2D0
static BOOL __fastcall SPRITECACHE_AsyncLoadGfxBlock(D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData, uint32_t nDirBlock, uint32_t nDirBlockSize, const char* szPath)
{
	if (!sgtGfxCache.pcs)
	{
		return FALSE;
	}

	D2GfxCacheBlockStrc* ptCacheBlock = GFXCACHE_AllocBlock(&sgtGfxCache, sizeof(D2GfxNodeStrc), nullptr, TRUE);
	if (!ptCacheBlock)
	{
		return FALSE;
	}

	D2GfxNodeStrc* ptGfxNode = (D2GfxNodeStrc*)ptCacheBlock->lpData;
	SPRITECACHE_SetupGfxNode(ptGfxNode, ptCelContext, ptCacheBlock);

	if (!(ptCelData->bFlags & CELDATAFLAG_NOFILE))
	{
		ptGfxNode->nClass = ptCelContext->nUnitIndex;
		ptGfxNode->nMode = ptCelContext->nMode;

		uint32_t nFirst = 0;
		uint32_t nLast = 0;
		if (ptCelContext->nUnitType == GFXUNIT_MONSTER || ptCelContext->nUnitType == GFXUNIT_PLAYER)
		{
			if (ptCelContext->nUnitType == GFXUNIT_MONSTER && nDirBlockSize == 1 && ptCelData->tHeader.dwNumDirections != 1)
			{
				GFXCACHE_FreeBlock(&sgtGfxCache, ptCacheBlock, TRUE);
				return FALSE;
			}

			nFirst = nDirBlock * nDirBlockSize;
			nLast = nFirst + nDirBlockSize;
		}

		const int dwSize = ptCelData->nOffsets[nLast] - ptCelData->nOffsets[nFirst];
		D2_ASSERT(dwSize);
		D2_ASSERT(!ptGfxNode->tGfxBlock.lpAsyncData);

		SPRITECACHE_SetupGfxBlockOffsets(&ptGfxNode->tGfxBlock, ptCelData, nDirBlock, nDirBlockSize, nFirst, nLast);

		AsyncData* pAsyncData = nullptr;
		if (ptCelData->bFlags & CELDATAFLAG_DCC)
		{
			AsyncDataLoadFileCallback tCallback;
			SPRITECACHE_SetupDecodeCallback(&tCallback, ptCelData, &ptGfxNode->tGfxBlock, nDirBlock * nDirBlockSize, nDirBlockSize);
			ptGfxNode->tGfxBlock.bFlags |= GFXBLOCK_FLAG_DECODING;
			pAsyncData = FOG_AsyncDataLoadFileEx(sgtGfxCache.pMemPool, szPath, TRUE, ptCelData->nOffsets[nFirst], dwSize, nullptr, &tCallback, -2, __FILE__, __LINE__);
		}
		else
		{
			pAsyncData = FOG_AsyncDataLoadFileEx(sgtGfxCache.pMemPool, szPath, TRUE, ptCelData->nOffsets[nFirst], dwSize, nullptr, nullptr, -2, __FILE__, __LINE__);
		}

		ptGfxNode->tGfxBlock.lpAsyncData = pAsyncData;
		if (!pAsyncData || dwSize == -1)
		{
			GFXCACHE_FreeBlock(&sgtGfxCache, ptCacheBlock, TRUE);
			return FALSE;
		}

		GFXCACHE_ResizeBlock(&sgtGfxCache, ptCacheBlock, dwSize, TRUE);
	}

	D2GfxHashElementStrc* ptHashTableElement = GFXHASH_Add(sgtGfxCache.pMemPool, &sgtGfxHash, ptGfxNode, ptCelContext, ptCelData);
	D2_ASSERT(ptHashTableElement);
	ptCacheBlock->pUserData = ptHashTableElement;
	ptHashTableElement->pCacheBlock = ptCacheBlock;

	if (ptCelData->bFlags & CELDATAFLAG_NOFILE)
	{
		ptGfxNode->tGfxBlock.bFlags |= GFXBLOCK_FLAG_NOFILE;
		return FALSE;
	}

	ptGfxNode->tGfxBlock.bFlags |= GFXBLOCK_FLAG_ASYNC;
	return TRUE;
}

//D2CMP.0x6FDFD600 (#10056)
BOOL __stdcall D2CMP_SpriteRequest(D2GfxDataStrc* ptCelContext)
{
	D2_ASSERT(ptCelContext);

	if (ptCelContext->pCellFile)
	{
		ptCelContext->pCurrentCell = D2CMP_CelGetHandle(ptCelContext);
		return TRUE;
	}

	char szPath[SPRITECACHE_PATH_LENGTH];
	char szName[SPRITECACHE_PATH_LENGTH];
	D2CelDataStrc* ptCelData = SPRITECACHE_GetCelData(ptCelContext, szPath, szName);
	if (!ptCelData)
	{
		return FALSE;
	}

	uint32_t nDirBlock = 0;
	uint32_t nDirBlockSize = 0;
	D2GfxHashElementStrc* ptHashTableElement = GFXHASH_Find(&sgtGfxHash, ptCelContext, &nDirBlock, &nDirBlockSize, ptCelData);
	if (ptHashTableElement)
	{
		if (ptHashTableElement->ptGfxNode->tGfxBlock.bFlags & GFXBLOCK_FLAG_NOFILE)
		{
			ptCelContext->fFlags |= 4;
		}
		return TRUE;
	}

	if (nDirBlockSize > 1 && nDirBlock && !(ptCelData->bFlags & CELDATAFLAG_NOFILE))
	{
		SPRITECACHE_ConvertDirection(ptCelContext, ptCelData, nDirBlockSize);
		ptHashTableElement = GFXHASH_Find(&sgtGfxHash, ptCelContext, &nDirBlock, &nDirBlockSize, ptCelData);
		D2_ASSERT(ptHashTableElement);
		D2_ASSERT(nDirBlock == 0); // dwDirBlock == 0
	}

	if (!szPath[0] && !SPRITECACHE_BuildFilePath(ptCelContext, szPath, szName))
	{
		return FALSE;
	}

	return SPRITECACHE_AsyncLoadGfxBlock(ptCelContext, ptCelData, nDirBlock, nDirBlockSize, szPath);
}

//D2CMP.0x6FDFD7D0 (#10059)
void __stdcall D2CMP_SpriteCacheDumpHashTableStats()
{
	// Empty in release builds (D2CMP.0x6FDF3ED0)
}

//D2CMP.0x6FDFD7E0 (#10060)
uint32_t __stdcall D2CMP_SpriteCacheGetUsedMemory()
{
	D2_ASSERT(sgtGfxCache.pcs);
	EnterCriticalSection(sgtGfxCache.pcs);
	const uint32_t dwAllocated = sgtGfxCache.dwAllocated;
	LeaveCriticalSection(sgtGfxCache.pcs);
	return dwAllocated;
}

//D2CMP.0x6FDFD830 (#10061)
uint32_t __stdcall D2CMP_SpriteCacheGetMaxMemory()
{
	return sgtGfxCache.dwMaxAllocated;
}

//D2CMP.0x6FDFD840 (#10062)
void __stdcall D2CMP_CelDataCacheDumpHashTableStats()
{
	// Empty in release builds (D2CMP.0x6FDF3ED0)
}

//D2CMP.0x6FDFD850 (#10063)
uint32_t __stdcall D2CMP_CelDataCacheGetUsedMemory()
{
	return sgtCelDataCache.dwAllocated;
}

//D2CMP.0x6FDFD860 (#10064)
uint32_t __stdcall D2CMP_CelDataCacheGetMaxMemory()
{
	return sgtCelDataCache.dwMaxAllocated;
}

//D2CMP.0x6FDFD870
static void __fastcall GFXCACHE_Init(D2GfxCacheStrc* pCache, void* pMemPool, uint32_t dwMaxAllocated, GfxCacheFreeCallback pfnFree)
{
	pCache->dwMaxAllocated = dwMaxAllocated;
	pCache->pfnFree = pfnFree;
	pCache->pMemPool = pMemPool;
	pCache->dwAllocated = 0;

	pCache->pBlocks = (D2GfxCacheBlockStrc*)D2_ALLOC_POOL(pMemPool, sizeof(D2GfxCacheBlockStrc) * GFXCACHE_MAX_BLOCKS);
	memset(pCache->pBlocks, 0x00, sizeof(D2GfxCacheBlockStrc) * GFXCACHE_MAX_BLOCKS);
	for (int i = 0; i < GFXCACHE_MAX_BLOCKS; ++i)
	{
		D2GfxCacheBlockStrc* pBlock = &pCache->pBlocks[i];
		if (i < GFXCACHE_MAX_BLOCKS - 1)
		{
			pBlock->pNext = &pCache->pBlocks[i + 1];
		}

		if (i > 0)
		{
			pBlock->pPrev = &pCache->pBlocks[i - 1];
		}

		pBlock->lpData = nullptr;
		pBlock->dwSize = 0;
		pBlock->pUserData = nullptr;
	}

	pCache->nUsedBlocks = 0;
	pCache->pFreeHead = pCache->pBlocks;
	pCache->pFreeTail = &pCache->pBlocks[GFXCACHE_MAX_BLOCKS - 1];
	pCache->pUsedHead = nullptr;
	pCache->pUsedTail = nullptr;
	pCache->pAsyncHead = nullptr;
	pCache->pAsyncTail = nullptr;
	pCache->nMisses = 0;
	pCache->nRequests = 0;

	if (!pCache->pcs)
	{
		pCache->pcs = (CRITICAL_SECTION*)D2_ALLOC(sizeof(CRITICAL_SECTION));
		InitializeCriticalSection(pCache->pcs);
	}
}

// Inlined helper: takes a block from the free list if there is enough memory left
static D2GfxCacheBlockStrc* GFXCACHE_TakeFreeBlock(D2GfxCacheStrc* pCache, uint32_t dwSize, BOOL bAsync)
{
	if (pCache->nUsedBlocks == GFXCACHE_MAX_BLOCKS || pCache->dwAllocated + dwSize > pCache->dwMaxAllocated)
	{
		return nullptr;
	}

	D2GfxCacheBlockStrc* ptBlock = pCache->pFreeHead;
	if (ptBlock)
	{
		if (ptBlock->dwFlags & GFXCACHEBLOCK_FLAG_LOCKED)
		{
			ptBlock = nullptr;
		}
		else
		{
			pCache->pFreeHead = ptBlock->pNext;
			if (ptBlock->pNext)
			{
				ptBlock->pNext->pPrev = nullptr;
			}
			else
			{
				pCache->pFreeTail = nullptr;
			}
			ptBlock->pNext = nullptr;
			ptBlock->pPrev = nullptr;
		}
	}

	D2_ASSERT(ptBlock);
	GFXCACHE_LinkBlock(pCache, ptBlock, bAsync);
	++pCache->nUsedBlocks;
	pCache->dwAllocated += dwSize;
	return ptBlock;
}

//D2CMP.0x6FDFD940
static D2GfxCacheBlockStrc* __fastcall GFXCACHE_AllocBlock(D2GfxCacheStrc* pCache, uint32_t dwSize, D2GfxHashElementStrc* pUserData, BOOL bAsync)
{
	D2_ASSERT(dwSize < pCache->dwMaxAllocated); // dwSize < ptCache->dwMaxAllocated

	uint32_t nOldestTimestamp = 0;
	if (bAsync)
	{
		if (pCache->pUsedHead)
		{
			nOldestTimestamp = pCache->pUsedHead->dwTimestamp;
		}

		if (pCache->pAsyncHead && (int)nOldestTimestamp >= (int)pCache->pAsyncHead->dwTimestamp)
		{
			nOldestTimestamp = pCache->pAsyncHead->dwTimestamp;
		}
	}

	D2GfxCacheBlockStrc* ptBlock = nullptr;
	if (pCache->pcs)
	{
		EnterCriticalSection(pCache->pcs);
		ptBlock = GFXCACHE_TakeFreeBlock(pCache, dwSize, bAsync);
		LeaveCriticalSection(pCache->pcs);
	}

	while (!ptBlock)
	{
		// Async loads do not evict recently used blocks
		if (bAsync && GetTickCount() - nOldestTimestamp < 15000)
		{
			return nullptr;
		}

		if (!GFXCACHE_FreeBlock(pCache, nullptr, TRUE))
		{
			FOG_TraceF(sgszTraceFileName, "SpriteCacheBlockNew: SpriteCacheBlockFree failed");
			return nullptr;
		}

		if (pCache->pcs)
		{
			EnterCriticalSection(pCache->pcs);
			ptBlock = GFXCACHE_TakeFreeBlock(pCache, dwSize, bAsync);
			LeaveCriticalSection(pCache->pcs);
		}
	}

	if (bAsync)
	{
		ptBlock->dwFlags |= GFXCACHEBLOCK_FLAG_ASYNC;
	}
	else
	{
		ptBlock->dwFlags &= ~GFXCACHEBLOCK_FLAG_ASYNC;
	}

	ptBlock->lpData = D2_ALLOC_POOL(pCache->pMemPool, dwSize);
	ptBlock->dwSize = dwSize;
	ptBlock->pUserData = pUserData;
	++pCache->nMisses;
	++pCache->nRequests;
	return ptBlock;
}

//D2CMP.0x6FDFDBA0
static D2GfxCacheBlockStrc* __fastcall GFXCACHE_FreeBlock(D2GfxCacheStrc* pCache, D2GfxCacheBlockStrc* ptBlock, BOOL bAllowAsync)
{
	if (!pCache->nUsedBlocks)
	{
		return nullptr;
	}

	if (!ptBlock)
	{
		BOOL bAsync = FALSE;
		if (pCache->pAsyncHead)
		{
			if (!pCache->pUsedHead)
			{
				bAsync = bAllowAsync;
			}
			else if (bAllowAsync)
			{
				bAsync = pCache->pAsyncHead->dwTimestamp < pCache->pUsedHead->dwTimestamp;
			}
		}

		ptBlock = GFXCACHE_PopBlock(pCache, bAsync);
		if (!ptBlock || (ptBlock->dwFlags & GFXCACHEBLOCK_FLAG_LOCKED))
		{
			return nullptr;
		}
	}
	else
	{
		if (ptBlock->dwFlags & GFXCACHEBLOCK_FLAG_LOCKED)
		{
			return nullptr;
		}
		GFXCACHE_UnlinkBlock(pCache, ptBlock);
	}

	if (!pCache->pcs)
	{
		return nullptr;
	}

	EnterCriticalSection(pCache->pcs);
	pCache->dwAllocated -= ptBlock->dwSize;
	LeaveCriticalSection(pCache->pcs);

	if (ptBlock->pUserData)
	{
		pCache->pfnFree(ptBlock->pUserData);
		ptBlock->pUserData = nullptr;
	}

	if (ptBlock->lpData)
	{
		D2_FREE_POOL(pCache->pMemPool, ptBlock->lpData);
		ptBlock->lpData = nullptr;
	}

	if (pCache->pFreeTail)
	{
		pCache->pFreeTail->pNext = ptBlock;
		ptBlock->pPrev = pCache->pFreeTail;
		pCache->pFreeTail = ptBlock;
	}
	else
	{
		pCache->pFreeHead = ptBlock;
		pCache->pFreeTail = ptBlock;
	}

	--pCache->nUsedBlocks;
	return ptBlock;
}

//D2CMP.0x6FDFDCA0
static void __fastcall GFXCACHE_ResizeBlock(D2GfxCacheStrc* pCache, D2GfxCacheBlockStrc* ptBlock, uint32_t dwAdditionalSize, BOOL bAllowAsync)
{
	if (!pCache->pcs)
	{
		return;
	}

	EnterCriticalSection(pCache->pcs);
	pCache->dwAllocated -= ptBlock->dwSize;
	ptBlock->dwSize += dwAdditionalSize;
	ptBlock->dwFlags |= GFXCACHEBLOCK_FLAG_LOCKED;
	pCache->dwAllocated += ptBlock->dwSize;
	uint32_t dwAllocated = pCache->dwAllocated;
	LeaveCriticalSection(pCache->pcs);

	while (dwAllocated > pCache->dwMaxAllocated)
	{
		D2GfxCacheBlockStrc* ptFreedBlock = GFXCACHE_FreeBlock(pCache, nullptr, bAllowAsync);
		if (!ptFreedBlock)
		{
			break;
		}

		D2_ASSERT(ptFreedBlock != ptBlock);

		EnterCriticalSection(pCache->pcs);
		dwAllocated = pCache->dwAllocated;
		LeaveCriticalSection(pCache->pcs);
	}

	EnterCriticalSection(pCache->pcs);
	ptBlock->dwFlags &= ~GFXCACHEBLOCK_FLAG_LOCKED;
	LeaveCriticalSection(pCache->pcs);
}

//D2CMP.0x6FDFDD60
static void __fastcall GFXCACHE_LinkBlock(D2GfxCacheStrc* pCache, D2GfxCacheBlockStrc* ptBlock, BOOL bAsync)
{
	D2GfxCacheBlockStrc** ppHead = bAsync ? &pCache->pAsyncHead : &pCache->pUsedHead;
	D2GfxCacheBlockStrc** ppTail = bAsync ? &pCache->pAsyncTail : &pCache->pUsedTail;
	if (*ppTail)
	{
		(*ppTail)->pNext = ptBlock;
		ptBlock->pPrev = *ppTail;
		*ppTail = ptBlock;
	}
	else
	{
		*ppHead = ptBlock;
		*ppTail = ptBlock;
	}

	ptBlock->dwTimestamp = GetTickCount();
}

//D2CMP.0x6FDFDDE0
static D2GfxCacheBlockStrc* __fastcall GFXCACHE_PopBlock(D2GfxCacheStrc* pCache, BOOL bAsync)
{
	D2GfxCacheBlockStrc** ppHead = bAsync ? &pCache->pAsyncHead : &pCache->pUsedHead;
	D2GfxCacheBlockStrc** ppTail = bAsync ? &pCache->pAsyncTail : &pCache->pUsedTail;
	D2GfxCacheBlockStrc* ptBlock = *ppHead;
	if (!ptBlock || (ptBlock->dwFlags & GFXCACHEBLOCK_FLAG_LOCKED))
	{
		return nullptr;
	}

	*ppHead = ptBlock->pNext;
	if (ptBlock->pNext)
	{
		ptBlock->pNext->pPrev = nullptr;
	}
	else
	{
		*ppTail = nullptr;
	}

	ptBlock->pNext = nullptr;
	ptBlock->pPrev = nullptr;
	return ptBlock;
}

//D2CMP.0x6FDFDE60
static void __fastcall GFXCACHE_UnlinkBlock(D2GfxCacheStrc* pCache, D2GfxCacheBlockStrc* ptBlock)
{
	D2_ASSERT(ptBlock);

	const BOOL bAsync = (ptBlock->dwFlags & GFXCACHEBLOCK_FLAG_ASYNC) != 0;
	D2GfxCacheBlockStrc** ppHead = bAsync ? &pCache->pAsyncHead : &pCache->pUsedHead;
	D2GfxCacheBlockStrc** ppTail = bAsync ? &pCache->pAsyncTail : &pCache->pUsedTail;
	if (!*ppHead)
	{
		return;
	}

	if (ptBlock == *ppHead)
	{
		GFXCACHE_PopBlock(pCache, bAsync);
		return;
	}

	if (ptBlock == *ppTail)
	{
		*ppTail = ptBlock->pPrev;
		(*ppTail)->pNext = nullptr;
		ptBlock->pNext = nullptr;
		ptBlock->pPrev = nullptr;
		return;
	}

	if (!ptBlock->pPrev && !ptBlock->pNext)
	{
		return;
	}

	ptBlock->pPrev->pNext = ptBlock->pNext;
	ptBlock->pNext->pPrev = ptBlock->pPrev;
	ptBlock->pNext = nullptr;
	ptBlock->pPrev = nullptr;
}

//D2CMP.0x6FDFDF10 (#10057)
int __stdcall D2CMP_SpriteNumAsyncLoads()
{
	int nAsyncLoads = 0;
	for (D2GfxCacheBlockStrc* ptBlock = sgtGfxCache.pAsyncHead; ptBlock; ptBlock = ptBlock->pNext)
	{
		D2GfxNodeStrc* ptGfxNode = (D2GfxNodeStrc*)ptBlock->lpData;
		if (ptGfxNode && !(ptGfxNode->tGfxBlock.bFlags & GFXBLOCK_FLAG_NOFILE))
		{
			AsyncData* hAsyncData = ptGfxNode->tGfxBlock.lpAsyncData;
			D2_ASSERT(hAsyncData);
			if (!FOG_AsyncDataTestLoaded(hAsyncData))
			{
				++nAsyncLoads;
			}
		}
	}
	return nAsyncLoads;
}

//D2CMP.0x6FDFDF70 (#10058)
BOOL __stdcall D2CMP_SpriteFindAsynchSiblings(int nUnitType, int nMode, int nClass)
{
	for (D2GfxCacheBlockStrc* ptBlock = sgtGfxCache.pAsyncHead; ptBlock; ptBlock = ptBlock->pNext)
	{
		D2GfxNodeStrc* ptGfxNode = (D2GfxNodeStrc*)ptBlock->lpData;
		if (ptGfxNode && !(ptGfxNode->tGfxBlock.bFlags & GFXBLOCK_FLAG_NOFILE) && ptGfxNode->nClass == nClass && ptGfxNode->nMode == nMode && ptGfxNode->nUnitType == nUnitType)
		{
			AsyncData* hAsyncData = ptGfxNode->tGfxBlock.lpAsyncData;
			D2_ASSERT(hAsyncData);
			if (!FOG_AsyncDataTestLoaded(hAsyncData))
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

//D2CMP.0x6FDFE000 (#10099)
void __stdcall D2CMP_SpriteFreeAsyncLoads()
{
	for (D2GfxCacheBlockStrc* ptBlock = sgtGfxCache.pAsyncHead; ptBlock; ptBlock = ptBlock->pNext)
	{
		D2GfxNodeStrc* ptGfxNode = (D2GfxNodeStrc*)ptBlock->lpData;
		if (ptGfxNode && ptGfxNode->tGfxBlock.lpAsyncData && !FOG_AsyncDataTestLoaded(ptGfxNode->tGfxBlock.lpAsyncData))
		{
			FOG_AsyncDataFree(ptGfxNode->tGfxBlock.lpAsyncData);
			ptGfxNode->tGfxBlock.lpAsyncData = nullptr;
		}
	}
}
