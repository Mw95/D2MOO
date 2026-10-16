#include "StormInternal.h"

#include <cstring>

// Storm memory manager.
//
// Every allocation belongs to a heap. Heaps created implicitly by SMemAlloc are identified
// by the hash of the caller's (filename, line) pair, while heaps created with SMemHeapCreate
// get an identifier >= 0x80000000. Heaps are stored in 256 hash buckets, each protected by
// its own critical section.
//
// A heap is a region of address space reserved with VirtualAlloc (and thus 64KB aligned)
// which starts with a HEAP header followed by a sequence of blocks. Each block starts with a
// BLOCK header, which contains a signature allowing to retrieve the heap from any block.
// Big allocations are stored in their own VirtualAlloc region, the heap only containing a
// small block pointing to it.

#define SMEM_HEAP_SIGNATURE      0x6F6D // 'mo'
#define SMEM_SENTINEL_VALUE      0x12B1
#define SMEM_FREELIST_COUNT      9
#define SMEM_MAX_SMALL_ALLOC     0xFE87
#define SMEM_USERHEAP_FIRST_KEY  0x80000000

enum SMemBlockFlags : uint8_t
{
	SMEM_BLOCK_SENTINEL   = 0x01, // Block is followed by a sentinel value
	SMEM_BLOCK_FREE       = 0x02, // Block is not allocated
	SMEM_BLOCK_LARGE      = 0x04, // Data lives in its own VirtualAlloc region
	SMEM_BLOCK_INDIRECT   = 0x08, // Header of a large allocation, real block header is referenced
	SMEM_BLOCK_PREVFREE   = 0x10, // Previous block is (or was) free
	SMEM_BLOCK_USERFLAG1  = 0x40,
	SMEM_BLOCK_USERFLAG2  = 0x80,
};

#pragma pack(push, 1)
struct BLOCK
{
	uint16_t nSize;                 // 0x00 Total size of the block, including this header
	uint8_t nAlignPadding;          // 0x02
	uint8_t nFlags;                 // 0x03
	union
	{
		uint32_t dwSignature;       // 0x04 Allocated blocks: (SMEM_HEAP_SIGNATURE << 16) | (heap >> 16)
		BLOCK* pNextFree;           // 0x04 Free blocks: next block in the free list
	};
	// 0x08 Data or pointer to the large allocation
};

struct LARGEBLOCK
{
	uint32_t nSize;                 // 0x00
	BLOCK* pBlock;                  // 0x04
	uint16_t nPages;                // 0x08 Same position as BLOCK::nSize relatively to the data
	uint8_t nAlignPadding;          // 0x0A
	uint8_t nFlags;                 // 0x0B
	uint32_t dwSignature;           // 0x0C
	// 0x10 Data
};

struct HEAP
{
	HEAP* pNext;                    // 0x00
	uint32_t dwHeapId;              // 0x04
	uint32_t nBucket;               // 0x08
	uint32_t dwSignature;           // 0x0C
	uint32_t bIsPrimary;            // 0x10 Only the last region of a heap is used for allocations
	uint32_t nBlockCount;           // 0x14
	uint32_t nBytesAllocated;       // 0x18
	BLOCK* pFirstBlock;             // 0x1C
	BLOCK* pTop;                    // 0x20
	uint32_t nFragmentation;        // 0x24
	uint32_t nCommitStep;           // 0x28
	uint32_t nCommitted;            // 0x2C
	uint32_t nReserved;             // 0x30
	uint32_t nLargeBytes;           // 0x34
	BLOCK* pFreeLists[SMEM_FREELIST_COUNT]; // 0x38
	int32_t nLine;                  // 0x5C
	char szFilename[4];             // 0x60
};
#pragma pack(pop)

static_assert(sizeof(BLOCK) == 0x08, "Size mismatch");
static_assert(sizeof(LARGEBLOCK) == 0x10, "Size mismatch");
static_assert(offsetof(HEAP, szFilename) == 0x60, "Size mismatch");

#define SMEM_LOCK_NONE ((uint32_t)-1)

struct SMemCallerCache
{
	uint32_t bEnabled = TRUE;       // Storm.0x6FFE7BD8
	uint32_t dwFirstChars = 0;      // Storm.0x6FFEC4B4
	int32_t nLine = 0;              // Storm.0x6FFEC4B8
	const char* szFilename = nullptr; // Storm.0x6FFEC4BC
	uint32_t dwHeapId = 0;          // Storm.0x6FFEC4C0
};

// Storm.0x6FFEA490
static CRITICAL_SECTION sgHeapCritSects[256];
// Storm.0x6FFEBC90
static uint32_t sgbDebugMemory;
// Storm.0x6FFEBC98
static HEAP* sgpHeapBuckets[256];
// Storm.0x6FFEC098
static uint32_t sgbProtectMemory;
// Storm.0x6FFEC0A0
static uint32_t sgbBucketHasEmptyHeap[256];
// Storm.0x6FFEC4A0
static uint32_t sgbFillMemory;
// Storm.0x6FFEC4A4
static uint32_t sgnPageSize;
// Storm.0x6FFEC4A8
static uint32_t sgbInitialized;
// Storm.0x6FFEC4AC
static uint32_t sgbDisplayErrors;
// Storm.0x6FFEC4B0
static HEAP* sgpLastEmptyHeap;
static SMemCallerCache sgCallerCache;
// Storm.0x6FFE7BDC
static uint32_t sgnLastUserHeapId = SMEM_USERHEAP_FIRST_KEY;


static inline HEAP* SMemGetHeapFromSignature(uint32_t dwSignature)
{
	return (HEAP*)(uintptr_t)((dwSignature & 0xFFFF) << 16);
}

static inline BLOCK* SMemGetBlockFromPtr(void* ptr)
{
	if (!ptr)
	{
		return nullptr;
	}

	BLOCK* pBlock = (BLOCK*)((uint8_t*)ptr - sizeof(BLOCK));
	if (pBlock->nFlags & SMEM_BLOCK_INDIRECT)
	{
		pBlock = ((LARGEBLOCK*)((uint8_t*)ptr - sizeof(LARGEBLOCK)))->pBlock;
	}
	return pBlock;
}

static inline uint32_t SMemGetFreeListIndex(uint32_t nSize)
{
	const uint32_t nIndex = nSize >> 5;
	return nIndex >= 8 ? 8 : nIndex;
}

static inline void SMemLeaveBucket(uint32_t* pLockedBucket)
{
	if (*pLockedBucket != SMEM_LOCK_NONE)
	{
		LeaveCriticalSection(&sgHeapCritSects[*pLockedBucket]);
		*pLockedBucket = SMEM_LOCK_NONE;
	}
}

// Storm.0x6FFCB280
[[noreturn]] static void SMemFatal(uint32_t errorCode, const char* szName, int32_t nLine)
{
	SErrDisplayError(errorCode, szName, nLine, nullptr, FALSE, 1);
	ExitProcess(1);
}

// Storm.0x6FFCBD30
void SMemReportError(uint32_t errorCode, const char* filename, int32_t linenumber)
{
	SErrSetLastError(errorCode);
	if (sgbDisplayErrors)
	{
		SErrDisplayError(errorCode, filename, linenumber, nullptr, TRUE, 1);
	}
}

// Storm.0x6FFCB980
static void SMemComputePageSize()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	uint32_t nPageSize = 1;
	sgnPageSize = 1;
	if (systemInfo.dwPageSize > 1)
	{
		do
		{
			nPageSize *= 2;
		}
		while (nPageSize < systemInfo.dwPageSize);
		sgnPageSize = nPageSize;
	}
}

// Storm.0x6FFCB2A0
static HEAP* SMemCreateHeap(const char* szFilename, int32_t nLine, uint32_t dwHeapId, uint32_t nBucket, uint32_t nCommitStep, uint32_t nInitialCommit, uint32_t nReserve)
{
	HEAP* pHeap = (HEAP*)VirtualAlloc(nullptr, nReserve, MEM_RESERVE, PAGE_NOACCESS);
	if (!pHeap || !VirtualAlloc(pHeap, nInitialCommit, MEM_COMMIT, PAGE_READWRITE))
	{
		SMemFatal(ERROR_NOT_ENOUGH_MEMORY, szFilename, nLine);
	}

	const uint32_t nFilenameSize = (szFilename ? SStrLen(szFilename) : 0) + 1;
	uint32_t nHeaderSize = nFilenameSize + offsetof(HEAP, szFilename);
	if (nHeaderSize & 3)
	{
		nHeaderSize += 4 - (nHeaderSize & 3);
	}

	pHeap->dwHeapId = dwHeapId;
	pHeap->pFirstBlock = (BLOCK*)((uint8_t*)pHeap + nHeaderSize);
	pHeap->pTop = pHeap->pFirstBlock;
	pHeap->pNext = sgpHeapBuckets[nBucket];
	pHeap->nCommitStep = nCommitStep;
	pHeap->nCommitted = nInitialCommit;
	pHeap->nReserved = nReserve;
	pHeap->nLine = nLine;
	pHeap->nBucket = nBucket;
	pHeap->bIsPrimary = TRUE;
	pHeap->nFragmentation = 0;
	for (BLOCK*& pFreeList : pHeap->pFreeLists)
	{
		pFreeList = nullptr;
	}

	if (szFilename)
	{
		SMemCopy(pHeap->szFilename, szFilename, nFilenameSize);
	}
	else
	{
		pHeap->szFilename[0] = '\0';
	}

	pHeap->dwSignature = (SMEM_HEAP_SIGNATURE << 16) | (uint16_t)((uintptr_t)pHeap >> 16);
	sgpHeapBuckets[nBucket] = pHeap;
	return pHeap;
}

// Storm.0x6FFCB440
static void SMemReleaseHeap(HEAP** ppHeap)
{
	HEAP* pHeap = *ppHeap;
	*ppHeap = pHeap->pNext;
	VirtualFree(pHeap, 0, MEM_RELEASE);
}

// Storm.0x6FFCB3B0
static void SMemReleaseEmptyHeaps()
{
	sgpLastEmptyHeap = nullptr;
	for (uint32_t nBucket = 0; nBucket < 256; ++nBucket)
	{
		if (sgbBucketHasEmptyHeap[nBucket])
		{
			EnterCriticalSection(&sgHeapCritSects[nBucket]);
			sgbBucketHasEmptyHeap[nBucket] = FALSE;

			HEAP** ppHeap = &sgpHeapBuckets[nBucket];
			while (*ppHeap)
			{
				HEAP* pHeap = *ppHeap;
				if (!pHeap->nBlockCount && pHeap->dwHeapId < SMEM_USERHEAP_FIRST_KEY)
				{
					SMemReleaseHeap(ppHeap);
				}
				else
				{
					ppHeap = &pHeap->pNext;
				}
			}

			LeaveCriticalSection(&sgHeapCritSects[nBucket]);
		}
	}
}

// Storm.0x6FFCBAF0
static BOOL SMemCommit(HEAP* pHeap, uint32_t nRequiredSize)
{
	uint32_t nSizeToCommit = nRequiredSize - pHeap->nCommitted;
	const uint32_t nMask = pHeap->nCommitStep - 1;
	if (nMask & nSizeToCommit)
	{
		nSizeToCommit += pHeap->nCommitStep - (nMask & nSizeToCommit);
	}

	if (pHeap->nCommitted + nSizeToCommit > pHeap->nReserved)
	{
		nSizeToCommit = pHeap->nReserved - pHeap->nCommitted;
	}

	if (!VirtualAlloc((uint8_t*)pHeap + pHeap->nCommitted, nSizeToCommit, MEM_COMMIT, PAGE_READWRITE))
	{
		return FALSE;
	}

	pHeap->nCommitted += nSizeToCommit;
	return TRUE;
}

// Storm.0x6FFCB9B0
static void SMemSetBlockHeader(HEAP* pHeap, BLOCK* pBlock, uint32_t nSize, uint32_t nAlignPadding, uint8_t nFlags)
{
	pBlock->nAlignPadding = (uint8_t)nAlignPadding;
	pBlock->nSize = (uint16_t)nSize;
	pBlock->nFlags = nFlags;
	pBlock->dwSignature = pHeap->dwSignature;
	if (nFlags & SMEM_BLOCK_SENTINEL)
	{
		*(uint16_t*)((uint8_t*)pBlock + nSize - nAlignPadding - sizeof(uint16_t)) = SMEM_SENTINEL_VALUE;
	}
}

// Storm.0x6FFCB8A0
// Merges adjacent free blocks and rebuilds the free lists in address order.
static void SMemCoalesceFreeBlocks(HEAP* pHeap)
{
	BLOCK** ppListTails[SMEM_FREELIST_COUNT];
	for (uint32_t i = 0; i < SMEM_FREELIST_COUNT; ++i)
	{
		ppListTails[i] = &pHeap->pFreeLists[i];
	}

	BLOCK* pPreviousFree = nullptr;
	for (BLOCK* pBlock = pHeap->pFirstBlock; pBlock != pHeap->pTop; pBlock = (BLOCK*)((uint8_t*)pBlock + pBlock->nSize))
	{
		if (!(pBlock->nFlags & SMEM_BLOCK_FREE))
		{
			continue;
		}

		pBlock->pNextFree = nullptr;
		if (pPreviousFree)
		{
			const uint32_t nPreviousSize = pPreviousFree->nSize;
			if (pBlock == (BLOCK*)((uint8_t*)pPreviousFree + nPreviousSize) && nPreviousSize + pBlock->nSize <= 0xFFFF)
			{
				pPreviousFree->nSize = (uint16_t)(nPreviousSize + pBlock->nSize);
				continue;
			}

			const uint32_t nIndex = SMemGetFreeListIndex(nPreviousSize);
			*ppListTails[nIndex] = pPreviousFree;
			ppListTails[nIndex] = &pPreviousFree->pNextFree;
		}
		pPreviousFree = pBlock;
	}

	if (pPreviousFree)
	{
		const uint32_t nIndex = SMemGetFreeListIndex(pPreviousFree->nSize);
		*ppListTails[nIndex] = pPreviousFree;
		ppListTails[nIndex] = &pPreviousFree->pNextFree;
	}

	for (uint32_t i = 0; i < SMEM_FREELIST_COUNT; ++i)
	{
		*ppListTails[i] = nullptr;
	}
	pHeap->nFragmentation = 0;
}

// Storm.0x6FFCBB40
// Shrinks pBlock to *pNewSize, returning the remaining space to the heap.
static void SMemSplitBlock(HEAP* pHeap, BLOCK* pBlock, uint32_t* pNewSize, uint32_t* pAlignPadding)
{
	const uint32_t nBlockSize = pBlock->nSize;
	BLOCK* pNextBlock = (BLOCK*)((uint8_t*)pBlock + nBlockSize);
	const uint32_t nRemaining = nBlockSize - *pNewSize;
	if (pNextBlock == pHeap->pTop)
	{
		pHeap->pTop = (BLOCK*)((uint8_t*)pBlock + *pNewSize);
	}
	else if (nRemaining >= 16)
	{
		BLOCK* pRemaining = (BLOCK*)((uint8_t*)pBlock + *pNewSize);
		pRemaining->nSize = (uint16_t)nRemaining;
		pRemaining->nAlignPadding = 0;
		pRemaining->nFlags = SMEM_BLOCK_FREE;

		const uint32_t nIndex = SMemGetFreeListIndex(nRemaining & 0xFFFF);
		pRemaining->pNextFree = pHeap->pFreeLists[nIndex];
		pHeap->pFreeLists[nIndex] = pRemaining;
	}
	else
	{
		pNextBlock->nFlags &= ~SMEM_BLOCK_PREVFREE;
		*pNewSize += nRemaining;
		*pAlignPadding += nRemaining;
	}
}

// Storm.0x6FFCB9E0
static void SMemFreeBlock(HEAP* pHeap, BLOCK* pBlock)
{
	uint32_t nFreedBytes;
	if (pBlock->nFlags & SMEM_BLOCK_LARGE)
	{
		uint8_t* pLargeData = *(uint8_t**)(pBlock + 1);
		if (pLargeData)
		{
			nFreedBytes = ((LARGEBLOCK*)(pLargeData - sizeof(LARGEBLOCK)))->nSize;
			pHeap->nLargeBytes -= nFreedBytes;
			VirtualFree((void*)((uintptr_t)(pLargeData - sizeof(LARGEBLOCK)) & ~(uintptr_t)(sgnPageSize - 1)), 0, MEM_RELEASE);
		}
		else
		{
			nFreedBytes = 0;
		}
	}
	else
	{
		nFreedBytes = pBlock->nSize - pBlock->nAlignPadding - sizeof(BLOCK);
		if (pBlock->nFlags & SMEM_BLOCK_SENTINEL)
		{
			nFreedBytes -= sizeof(uint16_t);
		}
	}

	--pHeap->nBlockCount;
	pHeap->nBytesAllocated -= nFreedBytes;

	pBlock->nAlignPadding = 0;
	pBlock->nFlags = (pBlock->nFlags & SMEM_BLOCK_PREVFREE) | SMEM_BLOCK_FREE;

	BLOCK* pNextBlock = (BLOCK*)((uint8_t*)pBlock + pBlock->nSize);
	if (pHeap->pTop == pNextBlock)
	{
		pBlock->pNextFree = nullptr;
		pHeap->pTop = pBlock;
	}
	else
	{
		pNextBlock->nFlags |= SMEM_BLOCK_PREVFREE;

		const uint32_t nIndex = SMemGetFreeListIndex(pBlock->nSize);
		pBlock->pNextFree = pHeap->pFreeLists[nIndex];
		pHeap->pFreeLists[nIndex] = pBlock;

		if ((pBlock->nFlags & SMEM_BLOCK_PREVFREE) || (pNextBlock->nFlags & SMEM_BLOCK_FREE))
		{
			++pHeap->nFragmentation;
		}
	}

	if (pHeap->nBlockCount)
	{
		return;
	}

	pHeap->pTop = pHeap->pFirstBlock;
	for (BLOCK*& pFreeList : pHeap->pFreeLists)
	{
		pFreeList = nullptr;
	}
	pHeap->nFragmentation = 0;

	if (pHeap->dwHeapId < SMEM_USERHEAP_FIRST_KEY)
	{
		sgpLastEmptyHeap = pHeap;
		sgbBucketHasEmptyHeap[pHeap->nBucket] = TRUE;
	}
}

static inline void SMemComputeBlockSize(uint32_t nBytes, BOOL* pIsLarge, BOOL* pHasSentinel, uint32_t* pBlockSize, uint32_t* pAlignPadding)
{
	const BOOL bIsLarge = sgbProtectMemory || nBytes > SMEM_MAX_SMALL_ALLOC;
	const BOOL bHasSentinel = sgbDebugMemory && !bIsLarge;
	const uint32_t nDataSize = bIsLarge ? sizeof(void*) : nBytes;
	const uint32_t nUnalignedSize = nDataSize + sizeof(BLOCK) + (bHasSentinel ? sizeof(uint16_t) : 0);
	const uint32_t nBlockSize = nUnalignedSize + ((0 - nUnalignedSize) & 7);
	*pIsLarge = bIsLarge;
	*pHasSentinel = bHasSentinel;
	*pBlockSize = nBlockSize;
	*pAlignPadding = nBlockSize - nUnalignedSize;
}

// Storm.0x6FFCB560
static void* SMemAllocateBlock(HEAP* pHeap, uint32_t nBytes, uint8_t nExtraFlags)
{
	BOOL bIsLarge;
	BOOL bHasSentinel;
	uint32_t nBlockSize;
	uint32_t nAlignPadding;
	SMemComputeBlockSize(nBytes, &bIsLarge, &bHasSentinel, &nBlockSize, &nAlignPadding);

	const uint32_t nListIndex = SMemGetFreeListIndex(nBlockSize);
	if (pHeap->nFragmentation >= 4 && !pHeap->pFreeLists[nListIndex])
	{
		SMemCoalesceFreeBlocks(pHeap);
	}

	// Find the first non empty free list that may contain blocks big enough
	BLOCK** ppList = &pHeap->pFreeLists[nListIndex];
	if (!*ppList)
	{
		for (uint32_t nIndex = nListIndex + 1; nIndex < SMEM_FREELIST_COUNT; ++nIndex)
		{
			++ppList;
			if (*ppList)
			{
				break;
			}
		}
	}

	// Best fit, but stop as soon as the wasted space is small enough
	BLOCK** ppBestLink = nullptr;
	uint32_t nBestWaste = 0x7FFFFFFF;
	uint32_t nAcceptableWaste = 16;
	for (BLOCK* pFree = *ppList; pFree; ppList = &pFree->pNextFree, pFree = pFree->pNextFree)
	{
		const uint32_t nWaste = pFree->nSize - nBlockSize;
		if (nWaste < nBestWaste)
		{
			ppBestLink = ppList;
			nBestWaste = nWaste;
			if (nWaste < nAcceptableWaste)
			{
				break;
			}
			nAcceptableWaste += 4;
		}
	}

	BLOCK* pBlock;
	BOOL bPreviousIsFree = FALSE;
	if (ppBestLink)
	{
		pBlock = *ppBestLink;
		bPreviousIsFree = (pBlock->nFlags >> 4) & 1;
		*ppBestLink = pBlock->pNextFree;

		BLOCK* pNextBlock = (BLOCK*)((uint8_t*)pBlock + pBlock->nSize);
		if (pHeap->nFragmentation)
		{
			if (bPreviousIsFree || (pNextBlock != pHeap->pTop && (pNextBlock->nFlags & SMEM_BLOCK_FREE)))
			{
				--pHeap->nFragmentation;
			}
		}

		SMemSplitBlock(pHeap, pBlock, &nBlockSize, &nAlignPadding);
	}
	else
	{
		uint32_t nRequiredSize = (uint32_t)((uint8_t*)pHeap->pTop - (uint8_t*)pHeap) + nBlockSize;
		if (nRequiredSize > pHeap->nReserved)
		{
			// The heap is full, create a new bigger region for the same heap
			const uint32_t nReserve = pHeap->nReserved >= 0x10000000 ? pHeap->nReserved : pHeap->nReserved * 2;
			HEAP* pNewHeap = SMemCreateHeap(pHeap->szFilename, pHeap->nLine, pHeap->dwHeapId, pHeap->nBucket, nReserve >> 3, nReserve >> 3, nReserve);
			if (!pNewHeap)
			{
				return nullptr;
			}

			pHeap->bIsPrimary = FALSE;
			pHeap = pNewHeap;
			nRequiredSize = (uint32_t)((uint8_t*)pHeap->pTop - (uint8_t*)pHeap) + nBlockSize;
		}

		if (nRequiredSize > pHeap->nCommitted && !SMemCommit(pHeap, nRequiredSize))
		{
			return nullptr;
		}

		pBlock = pHeap->pTop;
		pHeap->pTop = (BLOCK*)((uint8_t*)pBlock + nBlockSize);
	}

	++pHeap->nBlockCount;
	pHeap->nBytesAllocated += nBytes;

	uint8_t nFlags = nExtraFlags;
	if (bPreviousIsFree)
	{
		nFlags |= SMEM_BLOCK_PREVFREE;
	}
	if (bIsLarge)
	{
		nFlags |= SMEM_BLOCK_LARGE;
	}
	if (bHasSentinel)
	{
		nFlags |= SMEM_BLOCK_SENTINEL;
	}
	SMemSetBlockHeader(pHeap, pBlock, nBlockSize, nAlignPadding, nFlags);

	if (!bIsLarge)
	{
		return pBlock + 1;
	}

	// Large allocation, place it in its own region.
	// With debug or protected memory, the data is placed at the end of the pages so that overflows are caught.
	*(void**)(pBlock + 1) = nullptr;
	if (!sgnPageSize)
	{
		SMemComputePageSize();
	}

	const uint32_t nTotalSize = nBytes + sizeof(LARGEBLOCK);
	uint32_t nOffset = 0;
	void* pReserved = nullptr;
	if (sgbDebugMemory || sgbProtectMemory)
	{
		const uint32_t nPageMask = sgnPageSize - 1;
		nOffset = sgnPageSize - (nPageMask & nTotalSize);
		if (sgbProtectMemory)
		{
			nOffset &= nPageMask;
			pReserved = VirtualAlloc(nullptr, nTotalSize + nOffset + sizeof(uint32_t), MEM_RESERVE, PAGE_NOACCESS);
		}
		else
		{
			nOffset &= sgnPageSize - 4;
		}
	}

	uint8_t* pRegion = (uint8_t*)VirtualAlloc(pReserved, nTotalSize + nOffset, MEM_COMMIT, PAGE_READWRITE);
	if (!pRegion)
	{
		SMemFreeBlock(pHeap, pBlock);
		return nullptr;
	}

	LARGEBLOCK* pLargeBlock = (LARGEBLOCK*)(pRegion + nOffset);
	pLargeBlock->nSize = nBytes;
	pLargeBlock->pBlock = pBlock;
	pLargeBlock->nPages = (uint16_t)((nBytes + 0xFFFF) >> 16);
	pLargeBlock->nAlignPadding = 0;
	pLargeBlock->nFlags = SMEM_BLOCK_LARGE | SMEM_BLOCK_INDIRECT;
	pLargeBlock->dwSignature = pHeap->dwSignature;
	*(void**)(pBlock + 1) = pLargeBlock + 1;
	pHeap->nLargeBytes += nBytes;
	return pLargeBlock + 1;
}

// Storm.0x6FFCB460
static void* SMemAllocateInHeap(uint32_t* pLockedBucket, HEAP* pHeap, uint32_t dwFlags, uint32_t nBytes)
{
	if (nBytes > 0x7FFFFFFF)
	{
		SMemLeaveBucket(pLockedBucket);
		SMemFatal(ERROR_NOT_ENOUGH_MEMORY, pHeap->szFilename, pHeap->nLine);
	}

	void* pResult = nullptr;
	if (pHeap)
	{
		uint8_t nExtraFlags = 0;
		if (dwFlags & SMEM_NOLEAKREPORT)
		{
			nExtraFlags = SMEM_BLOCK_USERFLAG1;
		}
		if (dwFlags & SMEM_KEEPONDESTROY)
		{
			nExtraFlags |= SMEM_BLOCK_USERFLAG2;
		}
		pResult = SMemAllocateBlock(pHeap, nBytes, nExtraFlags);
	}

	if (!pResult)
	{
		SMemLeaveBucket(pLockedBucket);
		if (pHeap->szFilename[0])
		{
			SMemFatal(ERROR_NOT_ENOUGH_MEMORY, pHeap->szFilename, pHeap->nLine);
		}
		SMemFatal(ERROR_NOT_ENOUGH_MEMORY, "SMemHeapAlloc()", -1);
	}

	if (dwFlags & SMEM_ZEROMEMORY)
	{
		SMemZero(pResult, nBytes);
	}
	else if (sgbFillMemory)
	{
		SMemFill(pResult, nBytes, 0xEE);
	}
	return pResult;
}

// Storm.0x6FFCC030
static BOOL SMemValidatePtr(void* ptr, BOOL bReportErrors, const char* szFilename, int32_t nLine)
{
	if (!ptr)
	{
		if (bReportErrors)
		{
			SMemReportError(STORM_ERROR_MEMORY_NULL_POINTER, szFilename, nLine);
		}
		return FALSE;
	}

	BLOCK* pBlock = (BLOCK*)((uint8_t*)ptr - sizeof(BLOCK));
	if ((pBlock->dwSignature >> 16) != SMEM_HEAP_SIGNATURE)
	{
		if (bReportErrors)
		{
			SMemReportError(STORM_ERROR_MEMORY_INVALID_BLOCK, szFilename, nLine);
		}
		return FALSE;
	}

	if (pBlock->nFlags & SMEM_BLOCK_FREE)
	{
		if (bReportErrors)
		{
			SMemReportError(STORM_ERROR_MEMORY_ALREADY_FREED, szFilename, nLine);
		}
		return FALSE;
	}

	if (pBlock->nFlags & SMEM_BLOCK_SENTINEL)
	{
		const uint16_t nSentinel = *(uint16_t*)((uint8_t*)ptr + pBlock->nSize - pBlock->nAlignPadding - sizeof(BLOCK) - sizeof(uint16_t));
		if (nSentinel != SMEM_SENTINEL_VALUE && bReportErrors)
		{
			SMemReportError(STORM_ERROR_MEMORY_CORRUPT, szFilename, nLine);
		}
	}
	return TRUE;
}

// Storm.0x6FFCC0E0
static void SMemGetBlockSizes(BLOCK* pBlock, void* ptr, uint32_t* pDataSize, uint32_t* pOverhead)
{
	if (pBlock->nFlags & SMEM_BLOCK_LARGE)
	{
		*pDataSize = ((LARGEBLOCK*)((uint8_t*)ptr - sizeof(LARGEBLOCK)))->nSize;
		*pOverhead = pBlock->nAlignPadding + sizeof(BLOCK) + sizeof(void*) + sizeof(LARGEBLOCK);
		return;
	}

	*pOverhead = pBlock->nAlignPadding + sizeof(BLOCK);
	if (pBlock->nFlags & SMEM_BLOCK_SENTINEL)
	{
		*pOverhead += sizeof(uint16_t);
	}
	*pDataSize = pBlock->nSize - *pOverhead;
}

// Storm.0x6FFCC390
static void SMemFreePtr(HEAP* pHeap, void* ptr, BLOCK* pBlock)
{
	if (sgbFillMemory && !(pBlock->nFlags & SMEM_BLOCK_LARGE))
	{
		SMemFill(ptr, pBlock->nSize - (pBlock->nFlags & SMEM_BLOCK_SENTINEL) * sizeof(uint16_t) - pBlock->nAlignPadding - sizeof(BLOCK), 0xDD);
	}
	SMemFreeBlock(pHeap, pBlock);
}

// Storm.0x6FFCCC90
static void SMemShrinkBlock(HEAP* pHeap, BLOCK* pBlock, uint32_t nOldBytes, uint32_t nNewBytes)
{
	BOOL bIsLarge;
	BOOL bHasSentinel;
	uint32_t nBlockSize;
	uint32_t nAlignPadding;
	SMemComputeBlockSize(nNewBytes, &bIsLarge, &bHasSentinel, &nBlockSize, &nAlignPadding);

	const uint8_t nFlags = (pBlock->nFlags & ~SMEM_BLOCK_SENTINEL) | (bHasSentinel ? SMEM_BLOCK_SENTINEL : 0);
	SMemSplitBlock(pHeap, pBlock, &nBlockSize, &nAlignPadding);
	SMemSetBlockHeader(pHeap, pBlock, nBlockSize, nAlignPadding, nFlags);
	pHeap->nBytesAllocated += nNewBytes - nOldBytes;
}

// Storm.0x6FFCCAD0
static BOOL SMemGrowBlock(HEAP* pHeap, BLOCK* pBlock, uint32_t nOldBytes, uint32_t nNewBytes)
{
	BOOL bIsLarge;
	BOOL bHasSentinel;
	uint32_t nBlockSize;
	uint32_t nAlignPadding;
	SMemComputeBlockSize(nNewBytes, &bIsLarge, &bHasSentinel, &nBlockSize, &nAlignPadding);

	if (nBlockSize > 0xFFFF || bIsLarge)
	{
		return FALSE;
	}

	uint32_t nCurrentSize = pBlock->nSize;
	if (nBlockSize <= nCurrentSize)
	{
		// The block is already big enough, only the padding changes
		const uint32_t nExtra = nCurrentSize - nBlockSize;
		nBlockSize += nExtra;
		nAlignPadding += nExtra;
	}
	else
	{
		const uint32_t nMissing = nBlockSize - nCurrentSize;
		BLOCK* pNewEnd = (BLOCK*)((uint8_t*)pBlock + nBlockSize);

		// Absorb the following free blocks (or the top of the heap)
		uint32_t nAvailable = 0;
		BLOCK* pNext = (BLOCK*)((uint8_t*)pBlock + nCurrentSize);
		do
		{
			if (pNext == pHeap->pTop)
			{
				break;
			}
			if (!(pNext->nFlags & SMEM_BLOCK_FREE))
			{
				return FALSE;
			}
			nAvailable += pNext->nSize;
			pNext = (BLOCK*)((uint8_t*)pNext + pNext->nSize);
		}
		while (nAvailable < nMissing);

		const uint32_t nAbsorbedSize = nCurrentSize + (nAvailable > nMissing ? nAvailable : nMissing);
		if (nAbsorbedSize > 0xFFFF)
		{
			return FALSE;
		}

		if (nAvailable < nMissing)
		{
			const uint32_t nRequiredSize = (uint32_t)((uint8_t*)pNewEnd - (uint8_t*)pHeap);
			if (nRequiredSize > pHeap->nCommitted)
			{
				if (nRequiredSize > pHeap->nReserved || !SMemCommit(pHeap, nRequiredSize))
				{
					return FALSE;
				}
			}
			pHeap->pTop = pNewEnd;
		}

		pBlock->nSize = (uint16_t)nAbsorbedSize;
		SMemSplitBlock(pHeap, pBlock, &nBlockSize, &nAlignPadding);
		pBlock->nSize = (uint16_t)nBlockSize;

		if (pNewEnd != pHeap->pTop)
		{
			pNewEnd->nFlags &= ~SMEM_BLOCK_PREVFREE;
			if ((pNewEnd->nFlags & SMEM_BLOCK_FREE) && pHeap->nFragmentation)
			{
				--pHeap->nFragmentation;
			}
		}

		// The absorbed blocks are still referenced by the free lists, rebuild them.
		SMemCoalesceFreeBlocks(pHeap);
	}

	const uint8_t nFlags = (pBlock->nFlags & ~SMEM_BLOCK_SENTINEL) | (bHasSentinel ? SMEM_BLOCK_SENTINEL : 0);
	SMemSetBlockHeader(pHeap, pBlock, nBlockSize, nAlignPadding, nFlags);
	pHeap->nBytesAllocated += nNewBytes - nOldBytes;
	return TRUE;
}

// Storm.0x6FFCC9B0
static void* SMemReAllocInHeap(uint32_t* pLockedBucket, HEAP* pHeap, void* ptr, BLOCK* pBlock, uint32_t nNewBytes, uint32_t dwFlags)
{
	uint32_t nOldBytes;
	uint32_t nOverhead;
	SMemGetBlockSizes(pBlock, ptr, &nOldBytes, &nOverhead);

	void* pResult = nullptr;
	if (!(pBlock->nFlags & SMEM_BLOCK_LARGE))
	{
		if (nNewBytes < nOldBytes)
		{
			SMemShrinkBlock(pHeap, pBlock, nOldBytes, nNewBytes);
			pResult = ptr;
		}
		else if (nNewBytes > nOldBytes && SMemGrowBlock(pHeap, pBlock, nOldBytes, nNewBytes))
		{
			pResult = ptr;
		}
	}

	if (!pResult)
	{
		if (dwFlags & SMEM_NOMOVE)
		{
			return nullptr;
		}

		pResult = SMemAllocateInHeap(pLockedBucket, pHeap, 0, nNewBytes);
		if (pResult && nOldBytes && nNewBytes)
		{
			SMemCopy(pResult, ptr, nOldBytes < nNewBytes ? nOldBytes : nNewBytes);
		}
		SMemFreePtr(pHeap, ptr, pBlock);
		if (!pResult)
		{
			return nullptr;
		}
	}

	if (nNewBytes > nOldBytes)
	{
		if (dwFlags & SMEM_ZEROMEMORY)
		{
			SMemZero((uint8_t*)pResult + nOldBytes, nNewBytes - nOldBytes);
		}
		else if (sgbFillMemory)
		{
			SMemFill((uint8_t*)pResult + nOldBytes, nNewBytes - nOldBytes, 0xEE);
		}
	}
	return pResult;
}

// Computes the heap identifier of a caller, caching the result of the last call.
static uint32_t SMemGetCallerHeapId(const char* szFilename, int32_t nLine)
{
	const uint32_t dwFirstChars = szFilename ? *(const uint32_t*)szFilename : 0;
	if (sgCallerCache.bEnabled && szFilename == sgCallerCache.szFilename && nLine == sgCallerCache.nLine)
	{
		if (dwFirstChars == sgCallerCache.dwFirstChars)
		{
			return sgCallerCache.dwHeapId;
		}
		// Same pointer but different content: the strings are not constant, stop caching.
		sgCallerCache.bEnabled = FALSE;
	}

	uint32_t dwHash = 0;
	if (szFilename)
	{
		dwHash = SStrHash(szFilename, SSTR_HASH_CASESENSITIVE, nLine);
	}

	uint32_t dwHeapId = dwHash & 0x7FFFFFFF;
	if (!dwHeapId)
	{
		dwHeapId = 1;
	}

	sgCallerCache.dwFirstChars = dwFirstChars;
	sgCallerCache.szFilename = szFilename;
	sgCallerCache.nLine = nLine;
	sgCallerCache.dwHeapId = dwHeapId;
	return dwHeapId;
}

static inline HEAP* SMemFindHeap(uint32_t nBucket, uint32_t dwHeapId)
{
	for (HEAP* pHeap = sgpHeapBuckets[nBucket]; pHeap; pHeap = pHeap->pNext)
	{
		if (pHeap->dwHeapId == dwHeapId)
		{
			return pHeap;
		}
	}
	return nullptr;
}

// Storm.0x6FFCCDE0
void SMemInitialize()
{
	if (sgbInitialized)
	{
		return;
	}

	SRegLoadValue("Internal", "Debug Memory", 0, (DWORD*)&sgbDebugMemory);
	SRegLoadValue("Internal", "Protect Memory", 0, (DWORD*)&sgbProtectMemory);
	for (CRITICAL_SECTION& critSect : sgHeapCritSects)
	{
		InitializeCriticalSection(&critSect);
	}
	sgbInitialized = TRUE;
}

// Storm.0x6FFCBC70
// Releases a heap region, reporting the blocks that were never freed.
// Returns the address of the link to the next heap to process.
static HEAP** SMemDestroyHeap(HEAP** ppHeap)
{
	HEAP* pHeap = *ppHeap;
	uint32_t bHasKeptBlocks = FALSE;
	for (BLOCK* pBlock = pHeap->pFirstBlock; pBlock < pHeap->pTop; )
	{
		BLOCK* pNext = (BLOCK*)((uint8_t*)pBlock + pBlock->nSize);
		if (pBlock->nFlags & (SMEM_BLOCK_FREE | SMEM_BLOCK_USERFLAG2))
		{
			bHasKeptBlocks |= pBlock->nFlags & SMEM_BLOCK_USERFLAG2;
		}
		else
		{
			if (!(pBlock->nFlags & SMEM_BLOCK_USERFLAG1))
			{
				if (gStormOptionReportMemoryLeaksToDebugger)
				{
					char szMessage[512];
					wsprintfA(szMessage, "Storm Error : memory never released -- %s, %i\n", pHeap->szFilename, pHeap->nLine);
					OutputDebugStringA(szMessage);
				}
				else
				{
					SMemReportError(STORM_ERROR_MEMORY_NEVER_RELEASED, pHeap->szFilename, pHeap->nLine);
				}
			}
			SMemFreeBlock(pHeap, pBlock);
		}
		pBlock = pNext;
	}

	if (bHasKeptBlocks)
	{
		return &pHeap->pNext;
	}

	SMemReleaseHeap(ppHeap);
	return ppHeap;
}

// Storm.0x6FFCBBC0
BOOL SMemDestroy()
{
	if (!sgbInitialized)
	{
		return TRUE;
	}

	sgbInitialized = FALSE;
	for (uint32_t nBucket = 0; nBucket < 256; ++nBucket)
	{
		EnterCriticalSection(&sgHeapCritSects[nBucket]);
		sgbBucketHasEmptyHeap[nBucket] = FALSE;

		HEAP** ppHeap = &sgpHeapBuckets[nBucket];
		while (*ppHeap)
		{
			HEAP* pHeap = *ppHeap;
			if (pHeap->nBlockCount)
			{
				ppHeap = SMemDestroyHeap(ppHeap);
			}
			else
			{
				if (pHeap->bIsPrimary && pHeap->dwHeapId >= SMEM_USERHEAP_FIRST_KEY)
				{
					SErrReportResourceLeak("HSHEAP");
				}
				SMemReleaseHeap(ppHeap);
			}
		}

		LeaveCriticalSection(&sgHeapCritSects[nBucket]);
		DeleteCriticalSection(&sgHeapCritSects[nBucket]);
	}
	return TRUE;
}

// Storm.#401
void* __stdcall SMemAlloc(size_t bytes, const char* logfilename, int logline, uint32_t flags)
{
	if (!sgbInitialized)
	{
		SMemFatal(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemAlloc()", -1);
	}

	const uint32_t dwHeapId = SMemGetCallerHeapId(logfilename, logline);
	uint32_t nLockedBucket = dwHeapId & 0xFF;
	EnterCriticalSection(&sgHeapCritSects[nLockedBucket]);

	HEAP* pHeap = SMemFindHeap(nLockedBucket, dwHeapId);
	if (!pHeap)
	{
		pHeap = SMemCreateHeap(logfilename, logline, dwHeapId, nLockedBucket, 0x1000, 0x1000, 0x10000);
	}

	void* pResult = SMemAllocateInHeap(&nLockedBucket, pHeap, flags, bytes);
	SMemLeaveBucket(&nLockedBucket);

	if (sgpLastEmptyHeap && sgpLastEmptyHeap != pHeap)
	{
		SMemReleaseEmptyHeaps();
	}
	return pResult;
}

// Storm.#403
int32_t __stdcall SMemFree(void* location, const char* logfilename, int logline, uint32_t flags)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemFree()", -1);
		return FALSE;
	}

	if (!SMemValidatePtr(location, TRUE, logfilename, logline))
	{
		return FALSE;
	}

	BLOCK* pBlock = SMemGetBlockFromPtr(location);
	HEAP* pHeap = SMemGetHeapFromSignature(pBlock->dwSignature);
	EnterCriticalSection(&sgHeapCritSects[pHeap->nBucket]);
	SMemFreePtr(pHeap, location, pBlock);
	if (pHeap->nBucket != SMEM_LOCK_NONE)
	{
		LeaveCriticalSection(&sgHeapCritSects[pHeap->nBucket]);
	}
	return TRUE;
}

// Not exported, used by the squall templates
void SMemFree(void* ptr)
{
	SMemFree(ptr, __FILE__, __LINE__, 0);
}

// Storm.#404
size_t __stdcall SMemGetSize(void* location, const char* logfilename, int logline)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemGetSize()", -1);
		return (size_t)-1;
	}

	if (!SMemValidatePtr(location, TRUE, logfilename, logline))
	{
		return (size_t)-1;
	}

	uint32_t nSize;
	uint32_t nOverhead;
	SMemGetBlockSizes(SMemGetBlockFromPtr(location), location, &nSize, &nOverhead);
	return nSize;
}

// Storm.#405
void* __stdcall SMemReAlloc(void* location, int amount, const char* logfilename, int logline, uint32_t flags)
{
	if (!sgbInitialized)
	{
		SMemFatal(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemReAlloc()", -1);
	}

	if (!location || !SMemValidatePtr(location, TRUE, logfilename, logline))
	{
		return SMemAlloc(amount, logfilename, logline, flags);
	}

	BLOCK* pBlock = SMemGetBlockFromPtr(location);
	HEAP* pHeap = SMemGetHeapFromSignature(pBlock->dwSignature);
	EnterCriticalSection(&sgHeapCritSects[pHeap->nBucket]);
	uint32_t nLockedBucket = pHeap->nBucket;
	void* pResult = SMemReAllocInHeap(&nLockedBucket, pHeap, location, pBlock, amount, flags);
	SMemLeaveBucket(&nLockedBucket);
	return pResult;
}

// Storm.#481
BOOL __stdcall SMemFindNextBlock(uint32_t dwHeapId, void* pPrevious, void** ppNext, SMEMBLOCKDETAILS* pDetails)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemFindNextBlock()", -1);
		return FALSE;
	}

	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(dwHeapId);
	STORM_VALIDATE_ARG(ppNext);
	STORM_VALIDATE_ARG(pDetails);
	STORM_VALIDATE_ARG(pDetails->cbSize == sizeof(SMEMBLOCKDETAILS));
	STORM_VALIDATE_END(FALSE);

	SMemZero(&pDetails->pData, sizeof(SMEMBLOCKDETAILS) - sizeof(pDetails->cbSize));

	const uint32_t nBucket = dwHeapId & 0xFF;
	EnterCriticalSection(&sgHeapCritSects[nBucket]);

	BLOCK* pPreviousBlock = SMemGetBlockFromPtr(pPrevious);

	// Heap regions are stored from the most recent to the oldest one, walk them from the oldest.
	HEAP* pFirstHeap = sgpHeapBuckets[nBucket];
	BLOCK* pFound = nullptr;
	BOOL bFound = FALSE;
	if (pFirstHeap)
	{
		HEAP* pHeap = pFirstHeap;
		while (pHeap->pNext)
		{
			pHeap = pHeap->pNext;
		}

		BLOCK* pLastSeen = nullptr;
		while (true)
		{
			if (pHeap->dwHeapId == dwHeapId)
			{
				for (BLOCK* pBlock = pHeap->pFirstBlock; pBlock != pHeap->pTop; pBlock = (BLOCK*)((uint8_t*)pBlock + pBlock->nSize))
				{
					if (pLastSeen == pPreviousBlock)
					{
						pFound = pBlock;
						bFound = TRUE;
						break;
					}
					pLastSeen = pBlock;
				}
			}

			if (bFound || pHeap == pFirstHeap)
			{
				break;
			}

			// Find the region preceding the current one
			HEAP* pPreviousHeap = pFirstHeap;
			while (pPreviousHeap->pNext != pHeap)
			{
				pPreviousHeap = pPreviousHeap->pNext;
			}
			pHeap = pPreviousHeap;
		}
	}

	if (!bFound)
	{
		*ppNext = nullptr;
		LeaveCriticalSection(&sgHeapCritSects[nBucket]);
		return FALSE;
	}

	void* pData = pFound + 1;
	if (pFound->nFlags & SMEM_BLOCK_LARGE)
	{
		pData = *(void**)pData;
	}
	*ppNext = pData;
	pDetails->pData = pData;
	pDetails->bAllocated = ((uint8_t)~pFound->nFlags >> 1) & 1;
	pDetails->bValid = SMemValidatePtr(pData, FALSE, nullptr, 0);
	SMemGetBlockSizes(pFound, pData, &pDetails->nSize, &pDetails->nOverhead);
	LeaveCriticalSection(&sgHeapCritSects[nBucket]);
	return TRUE;
}

// Storm.#482
BOOL __stdcall SMemFindNextHeap(uint32_t dwPreviousHeapId, uint32_t* pNextHeapId, SMEMHEAPDETAILS* pDetails)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemFindNextHeap()", -1);
		return FALSE;
	}

	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(pNextHeapId);
	STORM_VALIDATE_ARG(pDetails);
	STORM_VALIDATE_ARG(pDetails->cbSize == sizeof(SMEMHEAPDETAILS));
	STORM_VALIDATE_END(FALSE);

	SMemZero(&pDetails->dwHeapId, sizeof(SMEMHEAPDETAILS) - sizeof(pDetails->cbSize));

	uint32_t dwLastSeenHeapId = 0;
	for (uint32_t nBucket = dwPreviousHeapId ? (dwPreviousHeapId & 0xFF) : 0; nBucket < 256; ++nBucket)
	{
		EnterCriticalSection(&sgHeapCritSects[nBucket]);
		for (HEAP* pHeap = sgpHeapBuckets[nBucket]; pHeap; pHeap = pHeap->pNext)
		{
			if (!pHeap->bIsPrimary)
			{
				continue;
			}

			if (dwLastSeenHeapId == dwPreviousHeapId && pHeap->dwHeapId != dwPreviousHeapId)
			{
				*pNextHeapId = pHeap->dwHeapId;
				pDetails->dwHeapId = pHeap->dwHeapId;
				pDetails->nLine = pHeap->nLine;
				pDetails->nMaxBlockSize = 0x7FFFFFFF;
				SStrCopy(pDetails->szFilename, pHeap->szFilename, sizeof(pDetails->szFilename));
				for (; pHeap; pHeap = pHeap->pNext)
				{
					if (pHeap->dwHeapId == *pNextHeapId)
					{
						pDetails->nCommitted += pHeap->nCommitted + pHeap->nLargeBytes;
						pDetails->nReserved += pHeap->nReserved + pHeap->nLargeBytes;
						pDetails->nBlockCount += pHeap->nBlockCount;
						pDetails->nBytesAllocated += pHeap->nBytesAllocated;
					}
				}
				LeaveCriticalSection(&sgHeapCritSects[nBucket]);
				return TRUE;
			}
			dwLastSeenHeapId = pHeap->dwHeapId;
		}
		LeaveCriticalSection(&sgHeapCritSects[nBucket]);
	}

	*pNextHeapId = 0;
	return FALSE;
}

// Storm.#497
BOOL __stdcall SMemDumpState(SMEMDUMPCALLBACK pfnCallback, void* pContext)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemDumpState()", -1);
		return FALSE;
	}

	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(pfnCallback);
	STORM_VALIDATE_END(FALSE);

	uint32_t dwHeapId = 0;
	SMEMHEAPDETAILS details;
	details.cbSize = sizeof(details);
	if (SMemFindNextHeap(0, &dwHeapId, &details))
	{
		do
		{
			char szLine[256];
			wsprintfA(szLine, "%s:%d  blocks=%u  %uk/%uk/%uk",
				details.szFilename,
				details.nLine,
				details.nBlockCount,
				(details.nBytesAllocated + 512) >> 10,
				(details.nCommitted + 512) >> 10,
				(details.nReserved + 512) >> 10);
			pfnCallback(pContext, szLine);
		}
		while (SMemFindNextHeap(dwHeapId, &dwHeapId, &details));
	}
	return TRUE;
}

// Storm.#483
uint32_t __stdcall SMemGetHeapByCaller(const char* logfilename, int logline)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemGetHeapByCaller()", -1);
		return 0;
	}

	return SMemGetCallerHeapId(logfilename, logline);
}

// Storm.#484
uint32_t __stdcall SMemGetHeapByPtr(void* ptr)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemGetHeapByPtr()", -1);
		return 0;
	}

	if (!SMemValidatePtr(ptr, FALSE, nullptr, 0))
	{
		return 0;
	}

	return SMemGetHeapFromSignature(SMemGetBlockFromPtr(ptr)->dwSignature)->dwHeapId;
}

// Storm.#485
void* __stdcall SMemHeapAlloc(uint32_t dwHeapId, uint32_t dwFlags, size_t nBytes)
{
	if (!sgbInitialized)
	{
		SMemFatal(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemHeapAlloc()", -1);
	}

	uint32_t nLockedBucket = dwHeapId & 0xFF;
	EnterCriticalSection(&sgHeapCritSects[nLockedBucket]);

	HEAP* pHeap = SMemFindHeap(nLockedBucket, dwHeapId);
	if (!pHeap)
	{
		LeaveCriticalSection(&sgHeapCritSects[nLockedBucket]);
		SMemFatal(ERROR_INVALID_PARAMETER, "SMemHeapAlloc()", -1);
	}

	void* pResult = SMemAllocateInHeap(&nLockedBucket, pHeap, dwFlags, nBytes);
	SMemLeaveBucket(&nLockedBucket);

	if (sgpLastEmptyHeap && sgpLastEmptyHeap != pHeap)
	{
		SMemReleaseEmptyHeaps();
	}
	return pResult;
}

// Storm.#486
uint32_t __stdcall SMemHeapCreate(uint32_t dwOptions, size_t nInitialSize, size_t nMaximumSize)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemHeapCreate()", -1);
		return 0;
	}

	if (dwOptions)
	{
		SMemReportError(ERROR_INVALID_PARAMETER, "SMemHeapCreate()", -1);
		return 0;
	}

	uint32_t nCommit = nInitialSize;
	if (nCommit & 0xFFF)
	{
		nCommit += 0x1000 - (nCommit & 0xFFF);
	}
	if (nCommit <= 0x1000)
	{
		nCommit = 0x1000;
	}

	// Find an identifier that is not used yet
	uint32_t nBucket;
	while (true)
	{
		if (++sgnLastUserHeapId == 0)
		{
			sgnLastUserHeapId = SMEM_USERHEAP_FIRST_KEY;
		}

		nBucket = sgnLastUserHeapId & 0xFF;
		EnterCriticalSection(&sgHeapCritSects[nBucket]);
		const BOOL bAlreadyUsed = SMemFindHeap(nBucket, sgnLastUserHeapId) != nullptr;
		LeaveCriticalSection(&sgHeapCritSects[nBucket]);
		if (!bAlreadyUsed)
		{
			break;
		}
	}

	nBucket = sgnLastUserHeapId & 0xFF;
	EnterCriticalSection(&sgHeapCritSects[nBucket]);
	SMemCreateHeap(nullptr, 0, sgnLastUserHeapId, nBucket, 0x1000, nCommit, 0x10000);
	LeaveCriticalSection(&sgHeapCritSects[nBucket]);

	if (!sgnLastUserHeapId)
	{
		SMemReportError(ERROR_NOT_ENOUGH_MEMORY, "SMemHeapCreate()", -1);
	}
	return sgnLastUserHeapId;
}

// Storm.#487
BOOL __stdcall SMemHeapDestroy(uint32_t dwHeapId)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemHeapDestroy()", -1);
		return FALSE;
	}

	const uint32_t nBucket = dwHeapId & 0xFF;
	EnterCriticalSection(&sgHeapCritSects[nBucket]);

	BOOL bFound = FALSE;
	HEAP** ppHeap = &sgpHeapBuckets[nBucket];
	while (*ppHeap)
	{
		if ((*ppHeap)->dwHeapId == dwHeapId)
		{
			bFound = TRUE;
			ppHeap = SMemDestroyHeap(ppHeap);
		}
		else
		{
			ppHeap = &(*ppHeap)->pNext;
		}
	}

	LeaveCriticalSection(&sgHeapCritSects[nBucket]);
	return bFound;
}

// Storm.#488
BOOL __stdcall SMemHeapFree(uint32_t dwHeapId, uint32_t dwFlags, void* ptr)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemHeapFree()", -1);
		return FALSE;
	}

	if (!SMemValidatePtr(ptr, TRUE, nullptr, 0))
	{
		return FALSE;
	}

	BLOCK* pBlock = SMemGetBlockFromPtr(ptr);
	HEAP* pHeap = SMemGetHeapFromSignature(pBlock->dwSignature);
	if (pHeap->dwHeapId != dwHeapId)
	{
		return FALSE;
	}

	EnterCriticalSection(&sgHeapCritSects[pHeap->nBucket]);
	SMemFreePtr(pHeap, ptr, pBlock);
	if (pHeap->nBucket != SMEM_LOCK_NONE)
	{
		LeaveCriticalSection(&sgHeapCritSects[pHeap->nBucket]);
	}
	return TRUE;
}

// Storm.#489
void* __stdcall SMemHeapRealloc(uint32_t dwHeapId, uint32_t dwFlags, void* ptr, size_t nBytes)
{
	if (!sgbInitialized)
	{
		SMemFatal(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemHeapReAlloc()", -1);
	}

	if (!ptr || !SMemValidatePtr(ptr, TRUE, nullptr, 0))
	{
		return SMemHeapAlloc(dwHeapId, dwFlags, nBytes);
	}

	BLOCK* pBlock = SMemGetBlockFromPtr(ptr);
	HEAP* pHeap = SMemGetHeapFromSignature(pBlock->dwSignature);
	if (pHeap->dwHeapId != dwHeapId)
	{
		return nullptr;
	}

	EnterCriticalSection(&sgHeapCritSects[pHeap->nBucket]);
	uint32_t nLockedBucket = pHeap->nBucket;
	void* pResult = SMemReAllocInHeap(&nLockedBucket, pHeap, ptr, pBlock, nBytes, dwFlags);
	SMemLeaveBucket(&nLockedBucket);
	return pResult;
}

// Storm.#490
size_t __stdcall SMemHeapSize(uint32_t dwHeapId, uint32_t dwFlags, void* ptr)
{
	if (!sgbInitialized)
	{
		SMemReportError(STORM_ERROR_MEMORY_MANAGER_INACTIVE, "SMemHeapSize()", -1);
		return (size_t)-1;
	}

	if (!SMemValidatePtr(ptr, TRUE, nullptr, 0))
	{
		return (size_t)-1;
	}

	BLOCK* pBlock = SMemGetBlockFromPtr(ptr);
	if (SMemGetHeapFromSignature(pBlock->dwSignature)->dwHeapId != dwHeapId)
	{
		return (size_t)-1;
	}

	uint32_t nSize;
	uint32_t nOverhead;
	SMemGetBlockSizes(pBlock, ptr, &nSize, &nOverhead);
	return nSize;
}

// Storm.#491
void __stdcall SMemCopy(void* dest, const void* source, size_t size)
{
	uint32_t* pDest32 = (uint32_t*)dest;
	const uint32_t* pSource32 = (const uint32_t*)source;
	for (size_t i = size >> 2; i; --i)
	{
		*pDest32++ = *pSource32++;
	}

	uint8_t* pDest8 = (uint8_t*)pDest32;
	const uint8_t* pSource8 = (const uint8_t*)pSource32;
	for (size_t i = size & 3; i; --i)
	{
		*pDest8++ = *pSource8++;
	}
}

// Storm.#492
void __stdcall SMemFill(void* location, size_t length, uint8_t fillWith)
{
	const uint32_t dwFill = fillWith | (fillWith << 8) | (fillWith << 16) | (fillWith << 24);
	uint32_t* pDest32 = (uint32_t*)location;
	for (size_t i = length >> 2; i; --i)
	{
		*pDest32++ = dwFill;
	}

	uint8_t* pDest8 = (uint8_t*)pDest32;
	for (size_t i = length & 3; i; --i)
	{
		*pDest8++ = fillWith;
	}
}

// Storm.#493
void __stdcall SMemMove(void* dest, const void* source, size_t size)
{
	memmove(dest, source, size);
}

// Storm.#494
void __stdcall SMemZero(void* location, size_t length)
{
	uint32_t* pDest32 = (uint32_t*)location;
	for (size_t i = length >> 2; i; --i)
	{
		*pDest32++ = 0;
	}

	uint8_t* pDest8 = (uint8_t*)pDest32;
	for (size_t i = length & 3; i; --i)
	{
		*pDest8++ = 0;
	}
}

// Storm.#495
int __stdcall SMemCmp(const void* location1, const void* location2, size_t size)
{
	const uint8_t* p1 = (const uint8_t*)location1;
	const uint8_t* p2 = (const uint8_t*)location2;
	for (; size; --size, ++p1, ++p2)
	{
		if (*p1 != *p2)
		{
			return *p1 < *p2 ? -1 : 1;
		}
	}
	return 0;
}

// Storm.#496
uint32_t __stdcall SMemSetDebugFlags(uint32_t dwFlags, uint32_t dwMask)
{
	if (dwMask & 1)
	{
		sgbDebugMemory = dwFlags & 1;
	}
	if (dwMask & 8)
	{
		sgbFillMemory = (dwFlags >> 3) & 1;
	}
	if (dwMask & 4)
	{
		sgbProtectMemory = (dwFlags >> 2) & 1;
	}
	if (dwMask & 2)
	{
		sgbDisplayErrors = (dwFlags >> 1) & 1;
		return sgbDisplayErrors;
	}
	return dwFlags;
}
