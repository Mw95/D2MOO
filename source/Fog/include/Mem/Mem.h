#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

#define D2POOL_MAX_POOLS 40
#define D2POOL_MAX_SYSTEMS 8
#define D2POOL_LARGE_BLOCKS_HASH_SIZE 0x3FF

#pragma pack(push, 1)

struct D2PoolStrc;

// A chunk of memory split in nMemBlocksPerPool blocks of the same size
struct D2PoolBlockStrc					// sizeof 0x18
{
	uint8_t* pMemory;					// 0x00
	uint32_t* pUsageTable;				// 0x04 One bit per block
	int32_t nUsedBlocks;				// 0x08
	D2PoolBlockStrc* pPrevious;			// 0x0C
	D2PoolBlockStrc* pNext;				// 0x10
	D2PoolStrc* pPool;					// 0x14
	// Usage table follows
};

// Pool of blocks of the same size. Pool blocks with free blocks are kept at the head of the list.
struct D2PoolStrc						// sizeof 0x30
{
	CRITICAL_SECTION tLock;				// 0x00
	int32_t nBlockSize;					// 0x18
	int32_t nMemBlocksPerPool;			// 0x1C
	int32_t nPoolBlockMemorySize;		// 0x20
	int32_t nPoolBlocks;				// 0x24
	D2PoolBlockStrc* pHead;				// 0x28
	D2PoolBlockStrc* pTail;				// 0x2C
};

struct D2PoolBlockEntryStrc				// sizeof 0x08
{
	D2PoolBlockStrc* pPoolBlock;		// 0x00
	uint8_t* pMemory;					// 0x04
};

// Allocations larger than the biggest pool are allocated with malloc, with a 4 bytes header used to link them in a hash table
struct D2LargeBlockStrc					// sizeof 0x04
{
	D2LargeBlockStrc* pNext;			// 0x00
	// Data follows
};

struct D2PoolSystemStrc												// sizeof 0x17CC
{
	BOOL bUseLargeBlocksOnly;										// 0x0000
	CRITICAL_SECTION tLock;											// 0x0004
	int32_t nPools;													// 0x001C
	D2PoolStrc tPools[D2POOL_MAX_POOLS];							// 0x0020
	int32_t nPoolBlocks;											// 0x07A0
	int32_t nAllocatedPoolBlocks;									// 0x07A4
	D2PoolBlockEntryStrc* pPoolBlocks;								// 0x07A8 Sorted by memory address
	D2LargeBlockStrc* pLargeBlocks[D2POOL_LARGE_BLOCKS_HASH_SIZE];	// 0x07AC
	uint32_t nMemoryUsage;											// 0x17A8 Memory used by the pool blocks
	char szName[32];												// 0x17AC
};

#pragma pack(pop)

// 1.10f: 0x6FF58F40 (#10041)
FOG_DLL_DECL void __fastcall FOG_EnableMemoryPools(BOOL bEnable);
// 1.10f: 0x6FF59E90 (#10144)
FOG_DLL_DECL void __cdecl FOG_CompactMemoryPoolSystem(void* pMemoryPoolSystem);
