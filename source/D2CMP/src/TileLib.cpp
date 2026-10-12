#include "TileLib.h"

#include <Fog.h>

#include "FindTiles.h"


//D2CMP.0x6FDFFDE0 (#10087)
void __stdcall D2CMP_TileLibraryAddProject(D2TileLibraryHashStrc** ptTileLibrary, const char* szName)
{
	D2_ASSERT(ptTileLibrary);
	D2_ASSERT(szName);

	int ii = 0;
	for (; ii < MAX_TILEPROJECT; ++ii)
	{
		if (!ptTileLibrary[ii])
		{
			D2CMP_LoadProjectRecord(&ptTileLibrary[ii], szName);
			break;
		}
	}

	D2_ASSERT(ii < MAX_TILEPROJECT);
}

//D2CMP.0x6FDFFE70 (#10088)
int __stdcall D2CMP_TileLibraryGetTiles(D2TileLibraryHashStrc** ptTileLibrary, int nType, int nStyle, int nSequence, D2TileLibraryEntryStrc** pTileList, int nTileListSize)
{
	D2_ASSERT(ptTileLibrary);

	int nRemaining = nTileListSize;
	int nFound = 0;
	for (int ii = 0; ii < MAX_TILEPROJECT && ptTileLibrary[ii]; ++ii)
	{
		const int nTiles = FINDTILES_GetTiles(ptTileLibrary[ii], &pTileList[nFound], nRemaining, nType, nStyle, nSequence);
		nRemaining -= nTiles;
		nFound += nTiles;
		if (!nRemaining)
		{
			return nTileListSize;
		}
	}

	return nTileListSize - nRemaining;
}

//D2CMP.0x6FDFFF00 (#10077)
int __stdcall D2CMP_TileGetType(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nType;
}

//D2CMP.0x6FDFFF30 (#10078)
int __stdcall D2CMP_TileGetStyle(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nStyle;
}

//D2CMP.0x6FDFFF60 (#10079)
int __stdcall D2CMP_TileGetFlags(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nFlags;
}

//D2CMP.0x6FDFFF90 (#10080)
int __stdcall D2CMP_TileGetWidth(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nWidth;
}

//D2CMP.0x6FDFFFC0 (#10081)
int __stdcall D2CMP_TileGetRarity(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nRarity_Frame;
}

//D2CMP.0x6FDFFFF0 (#10082)
int __stdcall D2CMP_TileGetSequence(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nSequence;
}

//D2CMP.0x6FE00020 (#10083)
int __stdcall D2CMP_TileGetTileLight(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nLightDirection;
}

//D2CMP.0x6FE00050 (#10084)
int __stdcall D2CMP_TileGetTotalHeight(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nTotalHeight;
}

//D2CMP.0x6FE00080 (#10085)
uint8_t* __stdcall D2CMP_TileGetCollisionInfo(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->pCollisionInfo;
}

//D2CMP.0x6FE000B0 (#10086)
int __stdcall D2CMP_TileGetHeightToBottom(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nHeightToBottom;
}

//D2CMP.0x6FE000E0 (#10100)
uint16_t __stdcall D2CMP_TileGetRoofHeight(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->nRoofHeight;
}

//D2CMP.0x6FE00110 (#10101)
const char* __stdcall D2CMP_TileGetFilename(D2TileLibraryEntryStrc* hTile)
{
	D2_CHECK(hTile);
	return hTile->szLibraryName;
}
