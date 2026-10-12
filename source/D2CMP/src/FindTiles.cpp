#include "FindTiles.h"

#include <cstring>

#include <Fog.h>


// Inlined helper
static uint8_t FINDTILES_GetHashKey(int nType, int nStyle, int nSequence)
{
	const uint8_t tKey = ((uint8_t)(2 * nSequence - nType + nStyle)) % FIND_TILE_HASH_SIZE;
	D2_ASSERT(tKey < FIND_TILE_HASH_SIZE);
	return tKey;
}

//D2CMP.0x6FDF82A0
D2TileLibraryHashStrc* __fastcall FINDTILES_CreateHash()
{
	D2TileLibraryHashStrc* ptHash = D2_ALLOC_STRC(D2TileLibraryHashStrc);
	D2_ASSERT(ptHash);
	memset(ptHash, 0x00, sizeof(*ptHash));
	return ptHash;
}

//D2CMP.0x6FDF82F0
void __fastcall FINDTILES_DestroyHash(D2TileLibraryHashStrc* ptHash)
{
	if (!ptHash)
	{
		return;
	}

	for (int i = 0; i < FIND_TILE_HASH_SIZE; ++i)
	{
		D2TileLibraryHashNodeStrc* ptNode = ptHash->pNodes[i];
		while (ptNode)
		{
			D2TileLibraryHashNodeStrc* ptNextNode = ptNode->pNext;

			D2TileLibraryHashRefStrc* ptRef = ptNode->pRef;
			while (ptRef)
			{
				D2TileLibraryHashRefStrc* ptNextRef = ptRef->pNext;
				D2_FREE(ptRef);
				ptRef = ptNextRef;
			}

			ptNode->pRef = nullptr;
			D2_FREE(ptNode);
			ptNode = ptNextNode;
		}
		ptHash->pNodes[i] = nullptr;
	}

	D2_FREE(ptHash);
}

//D2CMP.0x6FDF8380
void __fastcall FINDTILES_AddTile(D2TileLibraryHashStrc* ptHash, D2TileLibraryEntryStrc* ptTile)
{
	D2_ASSERT(ptHash);
	D2_ASSERT(ptTile);

	const uint8_t tKey = FINDTILES_GetHashKey(ptTile->nType, ptTile->nStyle, ptTile->nSequence);

	D2TileLibraryHashNodeStrc* ptKeyNode = ptHash->pNodes[tKey];
	while (ptKeyNode)
	{
		if (ptKeyNode->nSequence == ptTile->nSequence && ptKeyNode->nStyle == ptTile->nStyle && ptKeyNode->nType == ptTile->nType)
		{
			break;
		}
		ptKeyNode = ptKeyNode->pNext;
	}

	if (!ptKeyNode)
	{
		ptKeyNode = D2_ALLOC_STRC(D2TileLibraryHashNodeStrc);
		D2_ASSERT(ptKeyNode);
		memset(ptKeyNode, 0x00, sizeof(*ptKeyNode));
		ptKeyNode->nSequence = ptTile->nSequence;
		ptKeyNode->nStyle = ptTile->nStyle;
		ptKeyNode->nType = ptTile->nType;
		ptKeyNode->pNext = ptHash->pNodes[tKey];
		ptHash->pNodes[tKey] = ptKeyNode;

		D2TileLibraryHashRefStrc* ptTileRef = D2_ALLOC_STRC(D2TileLibraryHashRefStrc);
		D2_ASSERT(ptTileRef);
		memset(ptTileRef, 0x00, sizeof(*ptTileRef));
		ptTileRef->pTile = ptTile;
		ptKeyNode->pRef = ptTileRef;
		return;
	}

	for (D2TileLibraryHashRefStrc* ptRef = ptKeyNode->pRef; ptRef; ptRef = ptRef->pNext)
	{
		if (ptRef->pTile == ptTile)
		{
			return;
		}
	}

	D2TileLibraryHashRefStrc* ptRef = D2_ALLOC_STRC(D2TileLibraryHashRefStrc);
	D2_ASSERT(ptRef);
	memset(ptRef, 0x00, sizeof(*ptRef));
	ptRef->pTile = ptTile;
	ptRef->pNext = ptKeyNode->pRef;
	ptKeyNode->pRef = ptRef;
}

//D2CMP.0x6FDF8570
int __fastcall FINDTILES_GetTiles(D2TileLibraryHashStrc* ptHash, D2TileLibraryEntryStrc** hTileList, int nMaxTiles, int nType, int nStyle, int nSequence)
{
	int nFound = 0;

	D2_ASSERT(ptHash);
	D2_ASSERT(hTileList);

	if (!nMaxTiles)
	{
		return 0;
	}

	const uint8_t tKey = FINDTILES_GetHashKey(nType, nStyle, nSequence);

	D2TileLibraryHashNodeStrc* ptKeyNode = ptHash->pNodes[tKey];
	while (ptKeyNode)
	{
		if (ptKeyNode->nSequence == nSequence && ptKeyNode->nStyle == nStyle && ptKeyNode->nType == nType)
		{
			break;
		}
		ptKeyNode = ptKeyNode->pNext;
	}

	if (!ptKeyNode)
	{
		return 0;
	}

	for (D2TileLibraryHashRefStrc* ptRef = ptKeyNode->pRef; ptRef && nFound < nMaxTiles; ptRef = ptRef->pNext)
	{
		hTileList[nFound] = ptRef->pTile;
		++nFound;
	}

	return nFound;
}
