#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"
#include "CelDataHash.h"
#include "GfxHash.h"

#pragma pack(push, 1)

enum D2GfxCacheBlockFlags : uint32_t
{
	GFXCACHEBLOCK_FLAG_ASYNC = 0x1,		// The block is in the async list
	GFXCACHEBLOCK_FLAG_LOCKED = 0x2,	// The block can not be freed
};

struct D2GfxCacheBlockStrc
{
	void* lpData;								//0x00
	uint32_t dwSize;							//0x04
	D2GfxHashElementStrc* pUserData;			//0x08
	uint32_t dwFlags;							//0x0C D2GfxCacheBlockFlags
	uint32_t dwTimestamp;						//0x10
	D2GfxCacheBlockStrc* pNext;					//0x14
	D2GfxCacheBlockStrc* pPrev;					//0x18
};

using GfxCacheFreeCallback = void(__fastcall*)(D2GfxHashElementStrc* pElement);

constexpr int GFXCACHE_MAX_BLOCKS = 0x1400;

struct D2GfxCacheStrc
{
	void* pMemPool;								//0x00
	uint32_t dwMaxAllocated;					//0x04
	uint32_t dwAllocated;						//0x08
	uint32_t nUsedBlocks;						//0x0C
	D2GfxCacheBlockStrc* pBlocks;				//0x10
	D2GfxCacheBlockStrc* pUsedHead;				//0x14
	D2GfxCacheBlockStrc* pUsedTail;				//0x18
	D2GfxCacheBlockStrc* pAsyncHead;			//0x1C
	D2GfxCacheBlockStrc* pAsyncTail;			//0x20
	D2GfxCacheBlockStrc* pFreeHead;				//0x24
	D2GfxCacheBlockStrc* pFreeTail;				//0x28
	GfxCacheFreeCallback pfnFree;				//0x2C
	CRITICAL_SECTION* pcs;						//0x30
	uint32_t nMisses;							//0x34
	uint32_t nRequests;							//0x38
};

#pragma pack(pop)

// Whether .dcc files can be used, defined in D2CMP.cpp
extern BOOL gbCompressedData;	//D2CMP.0x6FE0F058
