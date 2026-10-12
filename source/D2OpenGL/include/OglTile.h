#pragma once

#include <cstdint>

#include <DrawMode.h>


struct D2GfxLightStrc;
struct D2GfxLightExStrc;
struct D2TileLibraryEntryStrc;


// Tiles drawn into the 8 bits back buffer with the D2Gfx software helpers, ported from D2Gdi.dll

//pfFloorTileDraw
int32_t __fastcall OGL_FloorTileDraw(D2TileLibraryEntryStrc* pTile, D2GfxLightExStrc* pLight, int32_t nPosX, int32_t nPosY, int32_t nWorldXpos, int32_t nWorldYpos, uint8_t nAlpha, int32_t nScreenPanels, void* pTileData);
//pfTileDrawLit
int32_t __fastcall OGL_TileDrawLit(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, D2GfxLightStrc* pLight, int32_t nScreenPanels);
//pfTileDrawTrans
int32_t __fastcall OGL_TileDrawTrans(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, D2GfxLightStrc* pLight, int32_t nScreenPanels, uint8_t nAlpha);
//pfShadowTileDraw
int32_t __fastcall OGL_ShadowTileDraw(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, DrawMode eDrawMode, int32_t nScreenPanels);
