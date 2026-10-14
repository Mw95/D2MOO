#include <Mem/Mem.h>
#include <Storm.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Fog.0x6FF7568C
static BOOL gbUseMemoryPools = TRUE;

// Fog.0x6FF7AF00
static BOOL gbPoolSystemsInitialized;
// Fog.0x6FF7AF04
static CRITICAL_SECTION gtPoolSystemsLock;
// Fog.0x6FF7AF1C
// The first pool system is the default one, used when no pool system is given
static D2PoolSystemStrc gtPoolSystems[D2POOL_MAX_SYSTEMS];
// Fog.0x6FF86D7C
static int32_t gnPoolSystemsUsed;
// Fog.0x6FF86D80
static int32_t gnFreePoolSystems[D2POOL_MAX_SYSTEMS];
// Fog.0x6FF86DA0
static int32_t gnFreePoolSystemsCount;

#define DEFAULT_POOL_SYSTEM (&gtPoolSystems[0])

static void MEMORY_Halt(const char* szMessage, int nLine)
{
	FOG_DisplayHalt(szMessage, __FILE__, nLine);
	exit(-1);
}

// 1.10f: 0x6FF590B0
static void MEMORY_LogOutOfMemory(D2PoolSystemStrc* pPoolSystem, const char* szFormat, ...)
{
	char szMessage[4096];
	va_list args;
	va_start(args, szFormat);
	vsprintf(szMessage, szFormat, args);
	va_end(args);

	FOG_TraceF("", "--------------------------------------------------------");
	FOG_TraceF("", "ERROR: Out of memory!");
	FOG_TraceF("", "%s", szMessage);

	MEMORYSTATUS tMemoryStatus;
	GlobalMemoryStatus(&tMemoryStatus);
	char szNumber[32];
	FOG_TraceF("", "total physical:     %s", FOG_FormatNumberWithSeparators(szNumber, sizeof(szNumber), tMemoryStatus.dwTotalPhys));
	FOG_TraceF("", "available physical: %s", FOG_FormatNumberWithSeparators(szNumber, sizeof(szNumber), tMemoryStatus.dwAvailPhys));
	FOG_TraceF("", "total page:         %s", FOG_FormatNumberWithSeparators(szNumber, sizeof(szNumber), tMemoryStatus.dwTotalPageFile));
	FOG_TraceF("", "available page:     %s", FOG_FormatNumberWithSeparators(szNumber, sizeof(szNumber), tMemoryStatus.dwAvailPageFile));
	FOG_TraceF("", "total virtual:      %s", FOG_FormatNumberWithSeparators(szNumber, sizeof(szNumber), tMemoryStatus.dwTotalVirtual));
	FOG_TraceF("", "available virtual:  %s", FOG_FormatNumberWithSeparators(szNumber, sizeof(szNumber), tMemoryStatus.dwAvailVirtual));
	FOG_TraceF("", "");
}

// Index of the pool for a given size, pools have blocks of 16 << nPoolIndex bytes
static int MEMORY_GetPoolIndex(int nSize)
{
	if (nSize <= 16)
	{
		return 0;
	}

	uint32_t nValue = nSize - 1;
	int nHighestBit = 0;
	while (nValue >>= 1)
	{
		++nHighestBit;
	}
	return nHighestBit + 1 - 4;
}

static D2LargeBlockStrc** MEMORY_GetLargeBlockBucket(D2PoolSystemStrc* pPoolSystem, D2LargeBlockStrc* pLargeBlock)
{
	// Note: the original code uses a signed modulo, which results in a negative index for addresses above 2GB
	return &pPoolSystem->pLargeBlocks[(uint32_t)(uintptr_t)pLargeBlock % D2POOL_LARGE_BLOCKS_HASH_SIZE];
}

// Removes the block from the hash table, returns FALSE if it was not found
static BOOL MEMORY_UnlinkLargeBlock(D2PoolSystemStrc* pPoolSystem, D2LargeBlockStrc* pLargeBlock)
{
	D2LargeBlockStrc** ppBucket = MEMORY_GetLargeBlockBucket(pPoolSystem, pLargeBlock);
	D2LargeBlockStrc* pPrevious = nullptr;
	for (D2LargeBlockStrc* pCurrent = *ppBucket; pCurrent; pPrevious = pCurrent, pCurrent = pCurrent->pNext)
	{
		if (pCurrent == pLargeBlock)
		{
			if (pPrevious)
			{
				pPrevious->pNext = pCurrent->pNext;
			}
			else
			{
				*ppBucket = pCurrent->pNext;
			}
			return TRUE;
		}
	}
	return FALSE;
}

static void MEMORY_LinkLargeBlock(D2PoolSystemStrc* pPoolSystem, D2LargeBlockStrc* pLargeBlock)
{
	D2LargeBlockStrc** ppBucket = MEMORY_GetLargeBlockBucket(pPoolSystem, pLargeBlock);
	pLargeBlock->pNext = *ppBucket;
	*ppBucket = pLargeBlock;
}

static void MEMORY_GrowPoolBlocksArray(D2PoolSystemStrc* pPoolSystem, int nLine)
{
	if (pPoolSystem->nPoolBlocks < pPoolSystem->nAllocatedPoolBlocks)
	{
		return;
	}

	pPoolSystem->nAllocatedPoolBlocks += 0x20;
	D2PoolBlockEntryStrc* pPoolBlocks = (D2PoolBlockEntryStrc*)realloc(pPoolSystem->pPoolBlocks, pPoolSystem->nAllocatedPoolBlocks * sizeof(D2PoolBlockEntryStrc));
	pPoolSystem->pPoolBlocks = pPoolBlocks;
	if (!pPoolBlocks)
	{
		MEMORY_LogOutOfMemory(pPoolSystem, "(1) Pool Blocks overflowed at %d", pPoolSystem->nAllocatedPoolBlocks);
		MEMORY_Halt("MEMORY ERROR: Pool Blocks Overflowed", nLine);
	}
}

static int32_t MEMORY_GetUsageTableSize(const D2PoolStrc* pPool)
{
	return ((pPool->nMemBlocksPerPool + 31) >> 5) * sizeof(uint32_t);
}

// 1.10f: 0x6FF59780
static D2PoolBlockStrc* MEMORY_CreatePoolBlock(D2PoolSystemStrc* pPoolSystem, D2PoolStrc* pPool)
{
	MEMORY_GrowPoolBlocksArray(pPoolSystem, __LINE__);

	const int32_t nUsageTableSize = MEMORY_GetUsageTableSize(pPool);
	D2PoolBlockStrc* pPoolBlock = (D2PoolBlockStrc*)malloc(sizeof(D2PoolBlockStrc) + nUsageTableSize);
	uint8_t* pMemory = (uint8_t*)VirtualAlloc(nullptr, pPool->nPoolBlockMemorySize, MEM_COMMIT, PAGE_READWRITE);
	if (!pPoolBlock || !pMemory)
	{
		MEMORY_LogOutOfMemory(pPoolSystem, "(2) nPoolBlocks = %d/%d  nBlockSize = %d  nUsageTableSize = %d",
			pPoolSystem->nPoolBlocks, pPoolSystem->nAllocatedPoolBlocks, pPool->nPoolBlockMemorySize, nUsageTableSize);
		MEMORY_Halt("MEMORY ERROR: Out of Memory", __LINE__);
	}

	memset(pPoolBlock, 0, sizeof(D2PoolBlockStrc));
	pPoolBlock->pUsageTable = (uint32_t*)&pPoolBlock[1];
	memset(pPoolBlock->pUsageTable, 0, nUsageTableSize);
	pPoolBlock->pMemory = pMemory;
	pPoolBlock->pPool = pPool;
	++pPool->nPoolBlocks;

	D2_LOCK(&pPoolSystem->tLock);
	MEMORY_GrowPoolBlocksArray(pPoolSystem, __LINE__);
	pPoolSystem->nMemoryUsage += pPool->nPoolBlockMemorySize + nUsageTableSize + sizeof(D2PoolBlockStrc);

	// Keep the array sorted by memory address
	int nLow = 0;
	int nHigh = pPoolSystem->nPoolBlocks;
	while (nLow < nHigh)
	{
		const int nMiddle = nLow + (nHigh - nLow) / 2;
		if (pMemory > pPoolSystem->pPoolBlocks[nMiddle].pMemory)
		{
			nLow = nMiddle + 1;
		}
		else
		{
			nHigh = nMiddle;
		}
	}

	if (nLow < pPoolSystem->nPoolBlocks)
	{
		memmove(&pPoolSystem->pPoolBlocks[nLow + 1], &pPoolSystem->pPoolBlocks[nLow], (pPoolSystem->nPoolBlocks - nLow) * sizeof(D2PoolBlockEntryStrc));
	}
	pPoolSystem->pPoolBlocks[nLow].pPoolBlock = pPoolBlock;
	pPoolSystem->pPoolBlocks[nLow].pMemory = pMemory;
	++pPoolSystem->nPoolBlocks;
	D2_UNLOCK(&pPoolSystem->tLock);
	return pPoolBlock;
}

static int MEMORY_FindFreeBitInDword(uint32_t nUsage)
{
	int nBit = 0;
	while (nUsage & 1)
	{
		nUsage >>= 1;
		++nBit;
	}
	return nBit;
}

// 1.10f: 0x6FF595A0
// Returns the index of a free block, or -1. Each group of 8 full dwords is scanned from the last dword to the first.
static int MEMORY_FindFreeBlock(const uint32_t* pUsageTable, int nBlocks)
{
	int nRemainingDwords = nBlocks >> 5;
	int nFirstBlock = 0;
	while (true)
	{
		const int nDwordsToCheck = nRemainingDwords > 7 ? 8 : nRemainingDwords;
		for (int i = nDwordsToCheck - 1; i >= 0; --i)
		{
			if (pUsageTable[i] != 0xFFFFFFFF)
			{
				return nFirstBlock + 32 * i + MEMORY_FindFreeBitInDword(pUsageTable[i]);
			}
		}

		if (nRemainingDwords <= 8)
		{
			break;
		}
		nRemainingDwords -= 8;
		pUsageTable += 8;
		nFirstBlock += 0x100;
	}

	// Last partial dword
	const int nRemainingBits = nBlocks & 0x1F;
	if (!nRemainingBits)
	{
		return -1;
	}

	const uint32_t nUsage = pUsageTable[nRemainingDwords];
	if (nUsage == (1u << nRemainingBits) - 1)
	{
		return -1;
	}
	return nFirstBlock + 32 * nRemainingDwords + MEMORY_FindFreeBitInDword(nUsage);
}

// 1.10f: 0x6FF59310
static void* MEMORY_AllocImpl(D2PoolSystemStrc* pPoolSystem, int nSize, const char* szFile, int nLine)
{
	if (!pPoolSystem)
	{
		pPoolSystem = DEFAULT_POOL_SYSTEM;
	}

	if (!gbPoolSystemsInitialized)
	{
		FOG_CreateNewPoolSystem(nullptr, "Global Pool System", 0x40000, 0x8000);
	}

	const int nPoolIndex = MEMORY_GetPoolIndex(nSize);
	if (pPoolSystem->bUseLargeBlocksOnly || nPoolIndex >= pPoolSystem->nPools)
	{
		D2LargeBlockStrc* pLargeBlock = (D2LargeBlockStrc*)malloc(nSize + sizeof(D2LargeBlockStrc));
		if (!pLargeBlock)
		{
			MEMORY_LogOutOfMemory(pPoolSystem, "(3) Pool Blocks overflowed at %d", pPoolSystem->nPoolBlocks);
			MEMORY_Halt("MEMORY ERROR: Out of Memory", __LINE__);
		}

		D2_LOCK(&pPoolSystem->tLock);
		MEMORY_LinkLargeBlock(pPoolSystem, pLargeBlock);
		D2_UNLOCK(&pPoolSystem->tLock);
		return &pLargeBlock[1];
	}

	D2PoolStrc* pPool = &pPoolSystem->tPools[nPoolIndex];
	D2_LOCK(&pPool->tLock);

	int nBlockOffset = -1;
	D2PoolBlockStrc* pPoolBlock = pPool->pHead;
	if (!pPoolBlock)
	{
		pPoolBlock = MEMORY_CreatePoolBlock(pPoolSystem, pPool);
		if (pPoolBlock)
		{
			pPool->pTail = pPoolBlock;
			pPool->pHead = pPoolBlock;
		}
		nBlockOffset = 0;
	}
	else
	{
		if (pPoolBlock->nUsedBlocks < pPool->nMemBlocksPerPool)
		{
			nBlockOffset = MEMORY_FindFreeBlock(pPoolBlock->pUsageTable, pPool->nMemBlocksPerPool);
		}

		if (nBlockOffset < 0)
		{
			// Pool blocks with free blocks are at the head of the list, so all of them are full
			pPoolBlock = MEMORY_CreatePoolBlock(pPoolSystem, pPool);
			if (pPoolBlock)
			{
				pPoolBlock->pNext = pPool->pHead;
				pPool->pHead->pPrevious = pPoolBlock;
				pPool->pHead = pPoolBlock;
			}
			nBlockOffset = 0;
		}
	}

	D2_ASSERT(nBlockOffset < pPool->nMemBlocksPerPool);
	if (!pPoolBlock)
	{
		D2_UNLOCK(&pPool->tLock);
		FOG_DisplayWarning("insufficient memory for allocation allowed by memory system", __FILE__, __LINE__);
		return nullptr;
	}

	++pPoolBlock->nUsedBlocks;
	uint32_t* pUsage = &pPoolBlock->pUsageTable[nBlockOffset >> 5];
	const uint32_t nMask = 1u << (nBlockOffset & 0x1F);
	D2_ASSERTM(!(*pUsage & nMask), "!TESTBITDWORD( pPoolBlock->pUsageTable, nBlockOffset )");
	*pUsage |= nMask;

	// Move the full pool block at the end of the list
	if (pPoolBlock->nUsedBlocks >= pPool->nMemBlocksPerPool && pPoolBlock->pNext && pPoolBlock->pNext->nUsedBlocks < pPool->nMemBlocksPerPool)
	{
		if (pPoolBlock->pPrevious)
		{
			pPoolBlock->pPrevious->pNext = pPoolBlock->pNext;
		}
		else
		{
			pPool->pHead = pPoolBlock->pNext;
		}

		if (pPoolBlock->pNext)
		{
			pPoolBlock->pNext->pPrevious = pPoolBlock->pPrevious;
		}

		D2_ASSERT(pPool->pTail);
		pPool->pTail->pNext = pPoolBlock;
		pPoolBlock->pPrevious = pPool->pTail;
		pPool->pTail = pPoolBlock;
		pPoolBlock->pNext = nullptr;
	}

	void* pResult = pPoolBlock->pMemory + pPool->nBlockSize * nBlockOffset;
	D2_UNLOCK(&pPool->tLock);
	return pResult;
}

// Returns the pool block containing the address, or nullptr
static D2PoolBlockStrc* MEMORY_FindPoolBlock(D2PoolSystemStrc* pPoolSystem, const void* pMemory)
{
	D2_LOCK(&pPoolSystem->tLock);
	int nLow = 0;
	int nHigh = pPoolSystem->nPoolBlocks;
	while (nLow < nHigh)
	{
		const int nMiddle = nLow + (nHigh - nLow) / 2;
		if (pMemory < pPoolSystem->pPoolBlocks[nMiddle].pMemory)
		{
			nHigh = nMiddle;
		}
		else
		{
			nLow = nMiddle + 1;
		}
	}

	const int nIndex = nLow - 1;
	D2PoolBlockStrc* pPoolBlock = nIndex >= 0 && nIndex < pPoolSystem->nPoolBlocks ? pPoolSystem->pPoolBlocks[nIndex].pPoolBlock : nullptr;
	D2_UNLOCK(&pPoolSystem->tLock);
	return pPoolBlock;
}

// Returns the index of the block containing the address, or -1 if it is not a pool block
static int MEMORY_GetBlockOffset(D2PoolBlockStrc* pPoolBlock, const void* pMemory)
{
	if (!pPoolBlock || (const uint8_t*)pMemory < pPoolBlock->pMemory)
	{
		return -1;
	}

	const int nBlockOffset = (int)((const uint8_t*)pMemory - pPoolBlock->pMemory) / pPoolBlock->pPool->nBlockSize;
	return nBlockOffset < pPoolBlock->pPool->nMemBlocksPerPool ? nBlockOffset : -1;
}

// 1.10f: 0x6FF599C0
static void MEMORY_FreeImpl(D2PoolSystemStrc* pPoolSystem, void** ppMemory, const char* szFile, int nLine)
{
	if (!pPoolSystem)
	{
		pPoolSystem = DEFAULT_POOL_SYSTEM;
	}

	void* pMemory = *ppMemory;
	if (!pMemory)
	{
		return;
	}

	D2PoolBlockStrc* pPoolBlock = MEMORY_FindPoolBlock(pPoolSystem, pMemory);
	const int nBlockOffset = MEMORY_GetBlockOffset(pPoolBlock, pMemory);
	if (nBlockOffset < 0)
	{
		D2LargeBlockStrc* pLargeBlock = (D2LargeBlockStrc*)pMemory - 1;
		D2_LOCK(&pPoolSystem->tLock);
		MEMORY_UnlinkLargeBlock(pPoolSystem, pLargeBlock);
		D2_UNLOCK(&pPoolSystem->tLock);
		free(pLargeBlock);
		return;
	}

	D2PoolStrc* pPool = pPoolBlock->pPool;
	D2_LOCK(&pPool->tLock);
	uint32_t* pUsage = &pPoolBlock->pUsageTable[nBlockOffset >> 5];
	const uint32_t nMask = 1u << (nBlockOffset & 0x1F);
	if (*pUsage & nMask)
	{
		*pUsage &= ~nMask;
		--pPoolBlock->nUsedBlocks;

		// Move the pool block at the head of the list since it now has a free block
		if (pPoolBlock->pPrevious && pPoolBlock->pPrevious->nUsedBlocks >= pPool->nMemBlocksPerPool)
		{
			pPoolBlock->pPrevious->pNext = pPoolBlock->pNext;
			if (pPoolBlock->pNext)
			{
				pPoolBlock->pNext->pPrevious = pPoolBlock->pPrevious;
			}
			else
			{
				pPool->pTail = pPoolBlock->pPrevious;
			}

			pPoolBlock->pNext = pPool->pHead;
			pPool->pHead->pPrevious = pPoolBlock;
			pPool->pHead = pPoolBlock;
			pPoolBlock->pPrevious = nullptr;
		}
	}
	D2_UNLOCK(&pPool->tLock);
}

// 1.10f: 0x6FF59220
static void* MEMORY_ReallocLargeBlock(D2PoolSystemStrc* pPoolSystem, void* pMemory, int nSize)
{
	D2LargeBlockStrc* pLargeBlock = (D2LargeBlockStrc*)pMemory - 1;
	D2_LOCK(&pPoolSystem->tLock);
	if (!MEMORY_UnlinkLargeBlock(pPoolSystem, pLargeBlock))
	{
		D2_UNLOCK(&pPoolSystem->tLock);
		return nullptr;
	}

	D2LargeBlockStrc* pNewLargeBlock = (D2LargeBlockStrc*)realloc(pLargeBlock, nSize + sizeof(D2LargeBlockStrc));
	if (!pNewLargeBlock)
	{
		// Note: the original format uses %s for the size
		MEMORY_LogOutOfMemory(pPoolSystem, "Unable to allocate free block of %d", nSize);
		MEMORY_Halt("MEMORY ERROR: Out of Memory", __LINE__);
	}

	MEMORY_LinkLargeBlock(pPoolSystem, pNewLargeBlock);
	D2_UNLOCK(&pPoolSystem->tLock);
	return &pNewLargeBlock[1];
}

// 1.10f: 0x6FF59BE0
static void* MEMORY_ReallocImpl(D2PoolSystemStrc* pPoolSystem, void* pMemory, int nSize, const char* szFile, int nLine)
{
	if (!pPoolSystem)
	{
		pPoolSystem = DEFAULT_POOL_SYSTEM;
	}

	if (!pMemory)
	{
		void* pNew = MEMORY_AllocImpl(pPoolSystem, nSize, szFile, nLine);
		D2_ASSERT(pNew);
		return pNew;
	}

	D2PoolBlockStrc* pPoolBlock = MEMORY_FindPoolBlock(pPoolSystem, pMemory);
	const int nBlockOffset = MEMORY_GetBlockOffset(pPoolBlock, pMemory);
	if (nBlockOffset < 0)
	{
		void* pNew = MEMORY_ReallocLargeBlock(pPoolSystem, pMemory, nSize);
		D2_ASSERT(pNew);
		return pNew;
	}

	D2PoolStrc* pPool = pPoolBlock->pPool;
	D2_LOCK(&pPool->tLock);
	if (!(pPoolBlock->pUsageTable[nBlockOffset >> 5] & (1u << (nBlockOffset & 0x1F))))
	{
		D2_UNLOCK(&pPool->tLock);
		FOG_DisplayWarning("pool realloc was called for a block that has already been freed", __FILE__, __LINE__);
		FOG_DisplayWarning("Failure to reallocate memory", __FILE__, __LINE__);
		return nullptr;
	}

	const int nBlockSize = pPool->nBlockSize;
	D2_UNLOCK(&pPool->tLock);
	if (nBlockSize >= nSize)
	{
		return pMemory;
	}

	void* pNew = MEMORY_AllocImpl(pPoolSystem, nSize, szFile, nLine);
	D2_ASSERT(pNew);
	memcpy(pNew, pMemory, nBlockSize);
	MEMORY_FreeImpl(pPoolSystem, &pMemory, szFile, nLine);
	return pNew;
}

static void MEMORY_ReportAllocationFailure(const char* szFile, int nLine)
{
	FOG_10028(2, szFile, nLine, "");
}

// 1.10f: 0x6FF58F40 (#10041)
void __fastcall FOG_EnableMemoryPools(BOOL bEnable)
{
	gbUseMemoryPools = bEnable;
}

// 1.10f: 0x6FF58F50 (#10042)
void* __fastcall FOG_Alloc(int nSize, const char* szFile, int nLine, int n0)
{
	void* pMemory = MEMORY_AllocImpl(nullptr, nSize, szFile, nLine);
	if (!pMemory)
	{
		MEMORY_ReportAllocationFailure(szFile, nLine);
	}
	return pMemory;
}

// 1.10f: 0x6FF58F90 (#10043)
void __fastcall FOG_Free(void* pFree, const char* szFile, int nLine, int n0)
{
	MEMORY_FreeImpl(nullptr, &pFree, szFile, nLine);
}

// 1.10f: 0x6FF58FB0 (#10044)
void* __fastcall FOG_Realloc(void* pMemory, int nSize, const char* szFile, int nLine, int n0)
{
	void* pNew = MEMORY_ReallocImpl(nullptr, pMemory, nSize, szFile, nLine);
	if (!pNew)
	{
		MEMORY_ReportAllocationFailure(szFile, nLine);
	}
	return pNew;
}

// 1.10f: 0x6FF58FF0 (#10045)
void* __fastcall FOG_AllocPool(void* pMemPool, int nSize, const char* szFile, int nLine, int n0)
{
	void* pMemory = MEMORY_AllocImpl(gbUseMemoryPools ? (D2PoolSystemStrc*)pMemPool : nullptr, nSize, szFile, nLine);
	if (!pMemory)
	{
		MEMORY_ReportAllocationFailure(szFile, nLine);
	}
	return pMemory;
}

// 1.10f: 0x6FF59030 (#10046)
void __fastcall FOG_FreePool(void* pMemPool, void* pFree, const char* szFile, int nLine, int n0)
{
	MEMORY_FreeImpl(gbUseMemoryPools ? (D2PoolSystemStrc*)pMemPool : nullptr, &pFree, szFile, nLine);
}

// 1.10f: 0x6FF59060 (#10047)
void* __fastcall FOG_ReallocPool(void* pMemPool, void* pMemory, int nSize, const char* szFile, int nLine, int n0)
{
	void* pNew = MEMORY_ReallocImpl(gbUseMemoryPools ? (D2PoolSystemStrc*)pMemPool : nullptr, pMemory, nSize, szFile, nLine);
	if (!pNew)
	{
		MEMORY_ReportAllocationFailure(szFile, nLine);
	}
	return pNew;
}

// 1.10f: 0x6FF5A280 (#10142)
// Creates a pool system with pools of blocks up to nMaxBlockSize bytes, larger allocations use malloc.
// Passing nullptr for pMemPoolSystem (re)initializes the global state and creates the default pool system.
void __cdecl FOG_CreateNewPoolSystem(void** pMemPoolSystem, const char* szName, uint32_t nPools, uint32_t nUnused)
{
	const int nMaxBlockSize = (int)nPools;
	if (!pMemPoolSystem)
	{
		memset(gtPoolSystems, 0, sizeof(gtPoolSystems));
		gnPoolSystemsUsed = 0;
		memset(gnFreePoolSystems, 0, sizeof(gnFreePoolSystems));
		gnFreePoolSystemsCount = 0;
		InitializeCriticalSection(&gtPoolSystemsLock);
		gbPoolSystemsInitialized = TRUE;
	}

	EnterCriticalSection(&gtPoolSystemsLock);
	D2PoolSystemStrc* pPoolSystem;
	if (gnFreePoolSystemsCount)
	{
		--gnFreePoolSystemsCount;
		pPoolSystem = &gtPoolSystems[gnFreePoolSystems[gnFreePoolSystemsCount]];
	}
	else if (gnPoolSystemsUsed < D2POOL_MAX_SYSTEMS)
	{
		pPoolSystem = &gtPoolSystems[gnPoolSystemsUsed++];
	}
	else
	{
		LeaveCriticalSection(&gtPoolSystemsLock);
		MEMORY_LogOutOfMemory(nullptr, "Insufficient pre-allocated pool systems");
		RaiseException(0xE0000001, 0, 0, nullptr);
		return;
	}
	LeaveCriticalSection(&gtPoolSystemsLock);

	memset(pPoolSystem, 0, sizeof(*pPoolSystem));
	if (pMemPoolSystem)
	{
		*pMemPoolSystem = pPoolSystem;
	}

	InitializeCriticalSection(&pPoolSystem->tLock);
	D2_LOCK(&pPoolSystem->tLock);
	if (szName)
	{
		SStrCopy(pPoolSystem->szName, szName, sizeof(pPoolSystem->szName));
		pPoolSystem->szName[sizeof(pPoolSystem->szName) - 1] = '\0';
	}

	const int nPoolsCount = MEMORY_GetPoolIndex(nMaxBlockSize) + 1;
	D2_ASSERT(nPoolsCount <= D2POOL_MAX_POOLS);
	pPoolSystem->nPools = nPoolsCount;
	pPoolSystem->pPoolBlocks = nullptr;
	for (int i = 0; i < nPoolsCount; ++i)
	{
		D2PoolStrc* pPool = &pPoolSystem->tPools[i];
		InitializeCriticalSection(&pPool->tLock);
		const int nBlockSize = i == 0 ? 16 : 1 << (i + 4);
		pPool->nBlockSize = nBlockSize;

		int nBlocksPerPool;
		if (nBlockSize > 1000000 || nBlockSize * 256 >= 0x40000)
		{
			nBlocksPerPool = 0x80000 / nBlockSize;
		}
		else if (nBlockSize * 256 >= 0x10000)
		{
			nBlocksPerPool = 256;
		}
		else
		{
			nBlocksPerPool = 0x10000 / nBlockSize;
		}
		pPool->nMemBlocksPerPool = nBlocksPerPool;
		pPool->nPoolBlockMemorySize = nBlockSize * nBlocksPerPool;
	}

	for (D2LargeBlockStrc*& pLargeBlock : pPoolSystem->pLargeBlocks)
	{
		pLargeBlock = nullptr;
	}
	D2_UNLOCK(&pPoolSystem->tLock);
}

// 1.10f: 0x6FF5A100 (#10143)
void __cdecl FOG_DestroyMemoryPoolSystem(void* pMemoryPoolSystem)
{
	if (!gbPoolSystemsInitialized)
	{
		return;
	}

	D2PoolSystemStrc* pPoolSystem = pMemoryPoolSystem ? (D2PoolSystemStrc*)pMemoryPoolSystem : DEFAULT_POOL_SYSTEM;
	if (!pPoolSystem->nPools)
	{
		return;
	}

	// Note: locks are never released, they are destroyed instead
	D2_LOCK(&pPoolSystem->tLock);
	if (pPoolSystem->nPools)
	{
		for (int i = 0; i < pPoolSystem->nPools; ++i)
		{
			D2PoolStrc* pPool = &pPoolSystem->tPools[i];
			D2_LOCK(&pPool->tLock);
			D2PoolBlockStrc* pPoolBlock = pPool->pHead;
			while (pPoolBlock)
			{
				D2PoolBlockStrc* pNext = pPoolBlock->pNext;
				VirtualFree(pPoolBlock->pMemory, 0, MEM_RELEASE);
				free(pPoolBlock);
				pPoolBlock = pNext;
			}
			DeleteCriticalSection(&pPool->tLock);
		}

		free(pPoolSystem->pPoolBlocks);

		for (int i = 0; i < D2POOL_LARGE_BLOCKS_HASH_SIZE; ++i)
		{
			D2LargeBlockStrc* pLargeBlock = pPoolSystem->pLargeBlocks[i];
			while (pLargeBlock)
			{
				D2LargeBlockStrc* pNext = pLargeBlock->pNext;
				free(pLargeBlock);
				pLargeBlock = pNext;
			}
		}

		DeleteCriticalSection(&pPoolSystem->tLock);
	}
	else
	{
		D2_UNLOCK(&pPoolSystem->tLock);
	}

	memset(pPoolSystem, 0, sizeof(*pPoolSystem));

	D2_LOCK(&gtPoolSystemsLock);
	gnFreePoolSystems[gnFreePoolSystemsCount++] = (int32_t)(pPoolSystem - gtPoolSystems);
	D2_UNLOCK(&gtPoolSystemsLock);

	if (pPoolSystem == DEFAULT_POOL_SYSTEM)
	{
		D2_LOCK(&gtPoolSystemsLock);
		gbPoolSystemsInitialized = FALSE;
		DeleteCriticalSection(&gtPoolSystemsLock);
	}
}

// 1.10f: 0x6FF59E90 (#10144)
// Releases the pool blocks that are not used anymore.
void __cdecl FOG_CompactMemoryPoolSystem(void* pMemoryPoolSystem)
{
	D2PoolSystemStrc* pPoolSystem = pMemoryPoolSystem ? (D2PoolSystemStrc*)pMemoryPoolSystem : DEFAULT_POOL_SYSTEM;
	if (!pPoolSystem->nPools)
	{
		return;
	}

	D2_LOCK(&pPoolSystem->tLock);
	for (int i = 0; i < pPoolSystem->nPools; ++i)
	{
		D2PoolStrc* pPool = &pPoolSystem->tPools[i];
		D2_LOCK(&pPool->tLock);
		D2PoolBlockStrc* pPoolBlock = pPool->pHead;
		while (pPoolBlock)
		{
			D2PoolBlockStrc* pNext = pPoolBlock->pNext;
			if (pPoolBlock->nUsedBlocks == 0)
			{
				if (pPoolBlock->pPrevious)
				{
					pPoolBlock->pPrevious->pNext = pNext;
				}
				if (pNext)
				{
					pNext->pPrevious = pPoolBlock->pPrevious;
				}
				if (pPool->pHead == pPoolBlock)
				{
					pPool->pHead = pNext;
				}
				if (pPool->pTail == pPoolBlock)
				{
					pPool->pTail = pPoolBlock->pPrevious;
				}
				--pPool->nPoolBlocks;

				// Note: the system lock is already held, this is a recursive lock
				D2_LOCK(&pPoolSystem->tLock);
				int nLow = 0;
				int nHigh = pPoolSystem->nPoolBlocks;
				int nFoundIndex = -1;
				while (nLow < nHigh)
				{
					const int nMiddle = nLow + (nHigh - nLow) / 2;
					if (pPoolBlock->pMemory > pPoolSystem->pPoolBlocks[nMiddle].pMemory)
					{
						nLow = nMiddle + 1;
					}
					else if (pPoolBlock->pMemory < pPoolSystem->pPoolBlocks[nMiddle].pMemory)
					{
						nHigh = nMiddle;
					}
					else
					{
						nFoundIndex = nMiddle;
						break;
					}
				}

				if (nFoundIndex >= 0)
				{
					if (nFoundIndex < pPoolSystem->nPoolBlocks - 1)
					{
						memmove(&pPoolSystem->pPoolBlocks[nFoundIndex], &pPoolSystem->pPoolBlocks[nFoundIndex + 1], (pPoolSystem->nPoolBlocks - (nFoundIndex + 1)) * sizeof(D2PoolBlockEntryStrc));
					}
					--pPoolSystem->nPoolBlocks;
					pPoolSystem->nMemoryUsage -= pPool->nPoolBlockMemorySize + MEMORY_GetUsageTableSize(pPool) + sizeof(D2PoolBlockStrc);

					if (pPoolSystem->nPoolBlocks + 0x40 < pPoolSystem->nAllocatedPoolBlocks)
					{
						pPoolSystem->nAllocatedPoolBlocks -= 0x20;
						D2PoolBlockEntryStrc* pPoolBlocks = (D2PoolBlockEntryStrc*)realloc(pPoolSystem->pPoolBlocks, pPoolSystem->nAllocatedPoolBlocks * sizeof(D2PoolBlockEntryStrc));
						pPoolSystem->pPoolBlocks = pPoolBlocks;
						if (!pPoolBlocks)
						{
							MEMORY_LogOutOfMemory(pPoolSystem, "(1) Pool Blocks overflowed at %d", pPoolSystem->nAllocatedPoolBlocks);
							MEMORY_Halt("MEMORY ERROR: Pool Blocks Overflowed", __LINE__);
						}
					}
					D2_UNLOCK(&pPoolSystem->tLock);
				}
				else
				{
					D2_UNLOCK(&pPoolSystem->tLock);
					FOG_DisplayWarning("Unable to find pool block in allocation tree!", __FILE__, __LINE__);
				}

				VirtualFree(pPoolBlock->pMemory, 0, MEM_RELEASE);
				free(pPoolBlock);
			}
			pPoolBlock = pNext;
		}
		D2_UNLOCK(&pPool->tLock);
	}
	D2_UNLOCK(&pPoolSystem->tLock);
}

// 1.10f: 0x6FF5A4A0 (#10145)
// When bFreePoolAlloc is set, all the allocations of the pool system use malloc
void __cdecl FOG_SetMemoryPoolSystemMode(void* pMemoryPoolSystem, BOOL bFreePoolAlloc)
{
	D2PoolSystemStrc* pPoolSystem = pMemoryPoolSystem ? (D2PoolSystemStrc*)pMemoryPoolSystem : DEFAULT_POOL_SYSTEM;
	if (pPoolSystem->nPools)
	{
		D2_LOCK(&pPoolSystem->tLock);
		pPoolSystem->bUseLargeBlocksOnly = bFreePoolAlloc;
		D2_UNLOCK(&pPoolSystem->tLock);
	}
}

// 1.10f: 0x6FF5A4E0 (#10147)
DWORD __cdecl FOG_GetMemoryUsage(void* pMemoryPoolSystem)
{
	D2PoolSystemStrc* pPoolSystem = pMemoryPoolSystem ? (D2PoolSystemStrc*)pMemoryPoolSystem : DEFAULT_POOL_SYSTEM;
	D2_LOCK(&pPoolSystem->tLock);
	const DWORD nMemoryUsage = pPoolSystem->nMemoryUsage;
	D2_UNLOCK(&pPoolSystem->tLock);
	return nMemoryUsage;
}
