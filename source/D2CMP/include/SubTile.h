#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"


//D2CMP.0x6FDFE050
uint8_t* __fastcall SUBTILE_CompressSubTile(const uint8_t* pPixels, int* pSize);
//D2CMP.0x6FDFE130
void __fastcall SUBTILE_Convert24To8(D2TileLibraryBlockStrc* ptComp8, const D2TileLibraryBlockStrc* ptComp24, uint32_t dwTransparentColor, D2CMPColorConvertCallback pfnConvert);
//D2CMP.0x6FDFE2F0
void __fastcall SUBTILE_CompressGameSquare(D2TileLibraryBlockStrc* ptComp);
//D2CMP.0x6FDFE370
void __fastcall SUBTILE_CompressGameSquareRLE(D2TileLibraryBlockStrc* ptComp, const uint8_t* pPixels);
//D2CMP.0x6FDFE530
void __fastcall SUBTILE_SquishGameSquare(D2TileLibraryBlockStrc* ptComp, const uint8_t* pPixels);
