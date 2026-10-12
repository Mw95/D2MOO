#include "GfxHash.h"

#include <cstring>

#include <Fog.h>
#include <Storm.h>


// Inlined helper: overlays and missiles/items are identified by their name instead of their tokens
static bool GFXHASH_IsNamedSprite(const D2GfxDataStrc* ptCelContext)
{
	return (ptCelContext->nUnitType == GFXUNIT_OVERLAY && (ptCelContext->fState & 2)) || ptCelContext->nUnitType == GFXUNIT_MISSILE || ptCelContext->nUnitType == GFXUNIT_ITEM;
}

//D2CMP.0x6FDF8690
void __fastcall GFXHASH_Init(D2GfxHashStrc* pHash)
{
	memset(pHash, 0x00, sizeof(*pHash));
}

//D2CMP.0x6FDF86A0
D2GfxHashElementStrc* __fastcall GFXHASH_Find(D2GfxHashStrc* pHash, D2GfxDataStrc* ptCelContext, uint32_t* pDirBlock, uint32_t* pDirBlockSize, D2CelDataStrc* ptCelData)
{
	const uint32_t nKey = GFXHASH_GetKey(ptCelContext, ptCelData, pDirBlock, pDirBlockSize);
	for (D2GfxHashElementStrc* pElement = pHash->pBuckets[nKey]; pElement; pElement = pElement->pNext)
	{
		if (pElement->dwName[0] != ptCelContext->dwName[0]
			|| pElement->dwName[1] != ptCelContext->dwName[1]
			|| pElement->dwName[2] != ptCelContext->dwName[2]
			|| pElement->dwName[3] != ptCelContext->dwName[3]
			|| pElement->dwName[4] != ptCelContext->dwName[4])
		{
			continue;
		}

		if (ptCelContext->nUnitType == GFXUNIT_OVERLAY && (ptCelContext->fState & 2))
		{
			if (pElement->nIndex != ptCelContext->nOverlay)
			{
				continue;
			}
		}
		else if (ptCelContext->nUnitType == GFXUNIT_ITEM || ptCelContext->nUnitType == GFXUNIT_MISSILE)
		{
			if (pElement->nIndex != ptCelContext->nUnitIndex)
			{
				continue;
			}
		}

		if (*pDirBlock == pElement->dwDirBlock)
		{
			return pElement;
		}
	}

	return nullptr;
}

//D2CMP.0x6FDF8780
uint32_t __fastcall GFXHASH_GetKey(D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData, uint32_t* pDirBlock, uint32_t* pDirBlockSize)
{
	*pDirBlock = GFXHASH_GetDirBlock(ptCelContext, pDirBlockSize, ptCelData);

	uint32_t nSum;
	if (GFXHASH_IsNamedSprite(ptCelContext))
	{
		D2_ASSERT(ptCelContext->pName); // ptCelContext->tUnitInfo.pszFileName
		nSum = SStrHash(ptCelContext->pName, 1, 0) + *pDirBlock;
	}
	else
	{
		nSum = ptCelContext->dwName[4] + ptCelContext->dwName[3] + ptCelContext->dwName[2] + ptCelContext->dwName[1] + ptCelContext->dwName[0] + *pDirBlock;
	}

	uint32_t nKey = ((nSum & 0x1FFF0000) ^ (nSum >> 8)) >> 8;
	nKey = ((nKey ^ (nSum & 0x1FFF00)) >> 8) ^ (nSum & 0x1FFF);
	return nKey;
}

//D2CMP.0x6FDF8830
D2GfxHashElementStrc* __fastcall GFXHASH_Add(void* pMemPool, D2GfxHashStrc* pHash, D2GfxNodeStrc* ptGfxNode, D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData)
{
	D2GfxHashElementStrc* pElement = (D2GfxHashElementStrc*)D2_ALLOC_POOL(pMemPool, sizeof(D2GfxHashElementStrc));
	pElement->ptGfxNode = ptGfxNode;

	uint32_t nDirBlockSize = 0;
	const uint32_t nKey = GFXHASH_GetKey(ptCelContext, ptCelData, &pElement->dwDirBlock, &nDirBlockSize);
	pElement->dwName[0] = ptCelContext->dwName[0];
	pElement->dwName[1] = ptCelContext->dwName[1];
	pElement->dwName[2] = ptCelContext->dwName[2];
	pElement->dwName[3] = ptCelContext->dwName[3];
	pElement->dwName[4] = ptCelContext->dwName[4];

	if (ptCelContext->nUnitType == GFXUNIT_OVERLAY && (ptCelContext->fState & 2))
	{
		pElement->nIndex = ptCelContext->nOverlay;
	}
	else if (ptCelContext->nUnitType == GFXUNIT_ITEM || ptCelContext->nUnitType == GFXUNIT_MISSILE)
	{
		pElement->nIndex = ptCelContext->nUnitIndex;
	}

	pElement->pPrev = nullptr;
	pElement->pNext = pHash->pBuckets[nKey];
	if (pElement->pNext)
	{
		pElement->pNext->pPrev = pElement;
	}

	pElement->nKey = nKey;
	pHash->pBuckets[nKey] = pElement;
	return pElement;
}

//D2CMP.0x6FDF88F0
void __fastcall GFXHASH_Remove(void* pMemPool, D2GfxHashStrc* pHash, D2GfxHashElementStrc* ptElement)
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

	D2GfxNodeStrc* ptGfxNode = ptElement->ptGfxNode;
	AsyncData* pAsyncData = ptGfxNode->tGfxBlock.lpAsyncData;
	if (pAsyncData)
	{
		if (ptGfxNode->tGfxBlock.fHardwareCelData)
		{
			CelHardwareFreeCallback pfnHardwareFree = D2CMP_CelGetHardwareFreeCallback();
			uint8_t* lpbData = (uint8_t*)FOG_AsyncDataGetBuffer(pAsyncData);
			D2_ASSERT(lpbData);

			// The hardware data of all the cels was allocated as a single block, pointed by the first cel
			D2GfxCellNodeStrc* pCellNodes = ((D2GfxCellStrc*)lpbData)->pCellNode;
			int nOffset = 0;
			for (uint32_t i = 0; i < (uint32_t)ptGfxNode->tGfxBlock.bNumCelsPerDir * ptGfxNode->tGfxBlock.bNumDirections; ++i)
			{
				D2GfxCellStrc* pCel = (D2GfxCellStrc*)&lpbData[nOffset];
				if (pCel->pCellNode)
				{
					if (pfnHardwareFree)
					{
						pfnHardwareFree(pCel->pCellNode);
					}
					pCel->pCellNode = nullptr;
				}
				nOffset += pCel->dwLength + pCel->dwHardwareDataSize + offsetof(D2GfxCellStrc, pPixels) + 3;
			}

			if (pCellNodes)
			{
				D2_FREE_POOL(pMemPool, pCellNodes);
			}
		}

		FOG_AsyncDataFree(pAsyncData);
		ptGfxNode->tGfxBlock.lpAsyncData = nullptr;
	}

	D2_FREE_POOL(pMemPool, ptElement);
}

//D2CMP.0x6FDF8A60
uint32_t __fastcall GFXHASH_GetDirBlock(D2GfxDataStrc* ptCelContext, uint32_t* pDirBlockSize, D2CelDataStrc* ptCelData)
{
	uint32_t nFileDirection = 0;
	*pDirBlockSize = 0;

	switch (ptCelContext->nUnitType)
	{
	case GFXUNIT_PLAYER:
		*pDirBlockSize = 8;
		if (!ptCelContext->nMode || ptCelContext->nMode == 17 || (ptCelContext->fFlags & 2))
		{
			*pDirBlockSize = 1;
		}

		if (!(ptCelData->bFlags & CELDATAFLAG_NOFILE))
		{
			nFileDirection = D2CMP_CelGameDirToFileDir(ptCelContext->nDirection, ptCelData->tHeader.dwNumDirections);
		}

		if (!*pDirBlockSize)
		{
			return 0;
		}
		return nFileDirection / *pDirBlockSize;

	case GFXUNIT_MONSTER:
		if (ptCelData->bFlags & CELDATAFLAG_NOFILE)
		{
			return 0;
		}

		*pDirBlockSize = ptCelData->tHeader.dwNumDirections == 8 ? 4 : 1;
		nFileDirection = D2CMP_CelGameDirToFileDir(ptCelContext->nDirection, ptCelData->tHeader.dwNumDirections);
		return nFileDirection / *pDirBlockSize;

	default:
		*pDirBlockSize = 1;
		if (ptCelContext->nUnitType == GFXUNIT_OBJECT)
		{
			return 0;
		}

		if (ptCelContext->nUnitType == GFXUNIT_ITEM)
		{
			return ptCelContext->nDirection;
		}

		if ((ptCelContext->nUnitType == GFXUNIT_OVERLAY && (ptCelContext->fState & 2)) || ptCelContext->nUnitType == GFXUNIT_MISSILE)
		{
			if (ptCelData->bFlags & CELDATAFLAG_NOFILE)
			{
				return 0;
			}
			return D2CMP_CelGameDirToFileDir(ptCelContext->nDirection, ptCelData->tHeader.dwNumDirections);
		}

		return 0;
	}
}
