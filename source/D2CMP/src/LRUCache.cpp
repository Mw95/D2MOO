#include "LRUCache.h"

#include <cstring>

#include <Fog.h>


//D2CMP.0x6FDF8B30
void __fastcall LRUCACHE_Init(D2LRUCacheStrc* ptCache, void* pMemPool, uint32_t dwMaxAllocated, LRUCacheFreeCallback pfnFree, uint32_t nMaxBlocks)
{
	ptCache->pMemPool = pMemPool;
	ptCache->dwMaxAllocated = dwMaxAllocated;
	ptCache->dwAllocated = 0;
	ptCache->pfnFree = pfnFree;
	ptCache->nMaxBlocks = nMaxBlocks;

	ptCache->pBlocks = (D2LRUCacheBlockStrc*)D2_ALLOC_POOL(pMemPool, sizeof(D2LRUCacheBlockStrc) * nMaxBlocks);
	memset(ptCache->pBlocks, 0x00, sizeof(D2LRUCacheBlockStrc) * nMaxBlocks);

	for (uint32_t i = 0; i < ptCache->nMaxBlocks; ++i)
	{
		D2LRUCacheBlockStrc* ptBlock = &ptCache->pBlocks[i];
		if (i < ptCache->nMaxBlocks - 1)
		{
			ptBlock->pNext = &ptCache->pBlocks[i + 1];
		}

		if (i > 0)
		{
			ptBlock->pPrev = &ptCache->pBlocks[i - 1];
		}

		ptBlock->lpData = nullptr;
		ptBlock->dwSize = 0;
		ptBlock->pUserData = nullptr;
	}

	ptCache->nUsedBlocks = 0;
	ptCache->pUsedHead = nullptr;
	ptCache->pUsedTail = nullptr;
	ptCache->pFreeHead = ptCache->pBlocks;
	ptCache->nMisses = 0;
	ptCache->nRequests = 0;
	ptCache->pFreeTail = &ptCache->pBlocks[ptCache->nMaxBlocks - 1];
}

//D2CMP.0x6FDF8BF0
void __fastcall LRUCACHE_Destroy(D2LRUCacheStrc* ptCache)
{
	while (ptCache->nUsedBlocks)
	{
		LRUCACHE_Free(ptCache, nullptr);
	}

	if (ptCache->pBlocks)
	{
		D2_FREE_POOL(ptCache->pMemPool, ptCache->pBlocks);
		ptCache->pBlocks = nullptr;
	}
}

// Helper function
static D2LRUCacheBlockStrc* LRUCACHE_PopFreeBlock(D2LRUCacheStrc* ptCache)
{
	D2LRUCacheBlockStrc* ptBlock = ptCache->pFreeHead;
	if (!ptBlock)
	{
		return nullptr;
	}

	ptCache->pFreeHead = ptBlock->pNext;
	if (ptBlock->pNext)
	{
		ptBlock->pNext->pPrev = nullptr;
	}
	else
	{
		ptCache->pFreeTail = nullptr;
	}

	ptBlock->pNext = nullptr;
	ptBlock->pPrev = nullptr;
	return ptBlock;
}

// Helper function
static void LRUCACHE_PushUsedBlock(D2LRUCacheStrc* ptCache, D2LRUCacheBlockStrc* ptBlock)
{
	if (ptCache->pUsedTail)
	{
		ptCache->pUsedTail->pNext = ptBlock;
		ptBlock->pPrev = ptCache->pUsedTail;
	}
	else
	{
		ptCache->pUsedHead = ptBlock;
	}
	ptCache->pUsedTail = ptBlock;
}

// Helper function
static void LRUCACHE_UnlinkUsedBlock(D2LRUCacheStrc* ptCache, D2LRUCacheBlockStrc* ptBlock)
{
	if (ptBlock == ptCache->pUsedHead)
	{
		ptCache->pUsedHead = ptBlock->pNext;
		if (ptBlock->pNext)
		{
			ptBlock->pNext->pPrev = nullptr;
		}
		else
		{
			ptCache->pUsedTail = nullptr;
		}
	}
	else if (ptBlock == ptCache->pUsedTail)
	{
		ptCache->pUsedTail = ptBlock->pPrev;
		ptBlock->pPrev->pNext = nullptr;
	}
	else
	{
		ptBlock->pPrev->pNext = ptBlock->pNext;
		ptBlock->pNext->pPrev = ptBlock->pPrev;
	}

	ptBlock->pNext = nullptr;
	ptBlock->pPrev = nullptr;
}

//D2CMP.0x6FDF8C30
D2LRUCacheBlockStrc* __fastcall LRUCACHE_Alloc(D2LRUCacheStrc* ptCache, uint32_t dwSize, void* pUserData)
{
	D2_ASSERT(dwSize < ptCache->dwMaxAllocated);

	++ptCache->nMisses;
	++ptCache->nRequests;

	// Evict the least recently used blocks until we have room
	while (ptCache->nUsedBlocks == ptCache->nMaxBlocks || ptCache->dwAllocated + dwSize > ptCache->dwMaxAllocated)
	{
		LRUCACHE_Free(ptCache, nullptr);
	}

	D2LRUCacheBlockStrc* ptBlock = LRUCACHE_PopFreeBlock(ptCache);
	LRUCACHE_PushUsedBlock(ptCache, ptBlock);
	D2_ASSERT(ptBlock);

	++ptCache->nUsedBlocks;
	ptCache->dwAllocated += dwSize;

	ptBlock->lpData = D2_ALLOC_POOL(ptCache->pMemPool, dwSize);
	D2_ASSERT(ptBlock->lpData);

	ptBlock->dwSize = dwSize;
	ptBlock->pUserData = pUserData;
	return ptBlock;
}

//D2CMP.0x6FDF8DC0
void __fastcall LRUCACHE_Free(D2LRUCacheStrc* ptCache, D2LRUCacheBlockStrc* ptBlock)
{
	if (!ptCache->nUsedBlocks)
	{
		return;
	}

	if (!ptBlock)
	{
		ptBlock = ptCache->pUsedHead;
		if (!ptBlock)
		{
			--ptCache->nUsedBlocks;
			return;
		}
		LRUCACHE_UnlinkUsedBlock(ptCache, ptBlock);
	}
	else if (ptCache->pUsedHead)
	{
		LRUCACHE_UnlinkUsedBlock(ptCache, ptBlock);
	}

	ptCache->dwAllocated -= ptBlock->dwSize;

	if (ptBlock->pUserData)
	{
		ptCache->pfnFree(ptBlock);
	}

	if (ptBlock->lpData)
	{
		D2_FREE_POOL(ptCache->pMemPool, ptBlock->lpData);
		ptBlock->lpData = nullptr;
		ptBlock->dwSize = 0;
		ptBlock->pUserData = nullptr;
	}

	if (ptCache->pFreeTail)
	{
		ptCache->pFreeTail->pNext = ptBlock;
		ptBlock->pPrev = ptCache->pFreeTail;
		ptCache->pFreeTail = ptBlock;
	}
	else
	{
		ptCache->pFreeHead = ptBlock;
		ptCache->pFreeTail = ptBlock;
	}

	--ptCache->nUsedBlocks;
}

//D2CMP.0x6FDF8EB0
void __fastcall LRUCACHE_Touch(D2LRUCacheStrc* ptCache, D2LRUCacheBlockStrc* ptBlock)
{
	if (!ptCache->nUsedBlocks)
	{
		return;
	}

	++ptCache->nRequests;
	D2_ASSERT(ptBlock);

	if (ptCache->pUsedHead)
	{
		LRUCACHE_UnlinkUsedBlock(ptCache, ptBlock);
	}

	if (ptCache->pUsedTail)
	{
		ptCache->pUsedTail->pNext = ptBlock;
		ptBlock->pPrev = ptCache->pUsedTail;
		ptCache->pUsedTail = ptBlock;
	}
	else
	{
		ptCache->pUsedHead = ptBlock;
		ptCache->pUsedTail = ptBlock;
	}
}
