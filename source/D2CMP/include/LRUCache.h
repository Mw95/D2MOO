#pragma once

#include <D2BasicTypes.h>

#pragma pack(push, 1)

struct D2LRUCacheBlockStrc;

using LRUCacheFreeCallback = void(__fastcall*)(D2LRUCacheBlockStrc* ptBlock);

struct D2LRUCacheBlockStrc
{
	void* lpData;									//0x00
	uint32_t dwSize;								//0x04
	void* pUserData;								//0x08
	D2LRUCacheBlockStrc* pNext;						//0x0C
	D2LRUCacheBlockStrc* pPrev;						//0x10
};

struct D2LRUCacheStrc
{
	void* pMemPool;									//0x00
	uint32_t dwMaxAllocated;						//0x04
	uint32_t dwAllocated;							//0x08
	uint32_t nUsedBlocks;							//0x0C
	D2LRUCacheBlockStrc* pBlocks;					//0x10
	uint32_t nMaxBlocks;							//0x14
	D2LRUCacheBlockStrc* pUsedHead;					//0x18 Least recently used
	D2LRUCacheBlockStrc* pUsedTail;					//0x1C Most recently used
	D2LRUCacheBlockStrc* pFreeHead;					//0x20
	D2LRUCacheBlockStrc* pFreeTail;					//0x24
	LRUCacheFreeCallback pfnFree;					//0x28
	uint32_t nMisses;								//0x2C
	uint32_t nRequests;								//0x30
};

#pragma pack(pop)

//D2CMP.0x6FDF8B30
void __fastcall LRUCACHE_Init(D2LRUCacheStrc* ptCache, void* pMemPool, uint32_t dwMaxAllocated, LRUCacheFreeCallback pfnFree, uint32_t nMaxBlocks);
//D2CMP.0x6FDF8BF0
void __fastcall LRUCACHE_Destroy(D2LRUCacheStrc* ptCache);
//D2CMP.0x6FDF8C30
D2LRUCacheBlockStrc* __fastcall LRUCACHE_Alloc(D2LRUCacheStrc* ptCache, uint32_t dwSize, void* pUserData);
//D2CMP.0x6FDF8DC0
void __fastcall LRUCACHE_Free(D2LRUCacheStrc* ptCache, D2LRUCacheBlockStrc* ptBlock);
//D2CMP.0x6FDF8EB0
void __fastcall LRUCACHE_Touch(D2LRUCacheStrc* ptCache, D2LRUCacheBlockStrc* ptBlock);
