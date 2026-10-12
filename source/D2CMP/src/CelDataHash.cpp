#include "CelDataHash.h"

#include <cstring>

#include <Fog.h>
#include <Storm.h>


// Inlined helper
static uint32_t CELDATAHASH_GetKey(const char* szName)
{
	const uint32_t nHash = SStrHash(szName, 1, 0);
	uint32_t nKey = ((nHash & 0x1FF0000) ^ (nHash >> 8)) >> 8;
	nKey = ((nKey ^ (nHash & 0x1FF00)) >> 8) ^ (nHash & 0x1FF);
	return nKey;
}

//D2CMP.0x6FDF3D10
void __fastcall CELDATAHASH_Init(D2CelDataHashStrc* pHash)
{
	memset(pHash, 0x00, sizeof(*pHash));
}

//D2CMP.0x6FDF3D20
D2CelDataHashElementStrc* __fastcall CELDATAHASH_Find(D2CelDataHashStrc* pHash, const char* szName)
{
	if (!szName[0])
	{
		return nullptr;
	}

	for (D2CelDataHashElementStrc* pElement = pHash->pBuckets[CELDATAHASH_GetKey(szName)]; pElement; pElement = pElement->pNext)
	{
		if (!strcmp(szName, pElement->szName))
		{
			return pElement;
		}
	}

	return nullptr;
}

//D2CMP.0x6FDF3DC0
D2CelDataHashElementStrc* __fastcall CELDATAHASH_Add(void* pMemPool, D2CelDataHashStrc* pHash, D2LRUCacheBlockStrc* pBlock, const char* szName)
{
	D2CelDataHashElementStrc* pElement = (D2CelDataHashElementStrc*)D2_ALLOC_POOL(pMemPool, sizeof(D2CelDataHashElementStrc));
	pElement->pBlock = pBlock;

	const uint32_t nKey = CELDATAHASH_GetKey(szName);
	pElement->pPrev = nullptr;
	pElement->pNext = pHash->pBuckets[nKey];
	if (pElement->pNext)
	{
		pElement->pNext->pPrev = pElement;
	}

	pElement->nKey = nKey;
	strcpy(pElement->szName, szName);
	pHash->pBuckets[nKey] = pElement;
	return pElement;
}

//D2CMP.0x6FDF3E60
void __fastcall CELDATAHASH_Remove(void* pMemPool, D2CelDataHashStrc* pHash, D2CelDataHashElementStrc* ptElement)
{
	D2_ASSERT(ptElement);

	if (ptElement->pPrev)
	{
		ptElement->pPrev->pNext = ptElement->pNext;
	}

	if (ptElement->pNext)
	{
		ptElement->pNext->pPrev = ptElement->pPrev;
	}

	if (pHash->pBuckets[ptElement->nKey] == ptElement)
	{
		pHash->pBuckets[ptElement->nKey] = ptElement->pNext;
	}

	D2_FREE_POOL(pMemPool, ptElement);
}
