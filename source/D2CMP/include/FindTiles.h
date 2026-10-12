#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"

//D2CMP.0x6FDF82A0
D2TileLibraryHashStrc* __fastcall FINDTILES_CreateHash();
//D2CMP.0x6FDF82F0
void __fastcall FINDTILES_DestroyHash(D2TileLibraryHashStrc* ptHash);
//D2CMP.0x6FDF8380
void __fastcall FINDTILES_AddTile(D2TileLibraryHashStrc* ptHash, D2TileLibraryEntryStrc* ptTile);
//D2CMP.0x6FDF8570
int __fastcall FINDTILES_GetTiles(D2TileLibraryHashStrc* ptHash, D2TileLibraryEntryStrc** hTileList, int nMaxTiles, int nType, int nStyle, int nSequence);
