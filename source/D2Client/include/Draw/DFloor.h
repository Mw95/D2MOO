#pragma once

#include <D2Client.h>


//D2Client.0x6FBA7984
extern D2DrlgActStrc* ghAct;


//D2Client.0x6FAA2E70
void __fastcall DFLOOR_DrawFloorTile(D2FloorDrawContextStrc* pContext, int32_t nUnused, D2DrlgTileDataStrc* pTileData, BOOL bFloorFilter, int32_t nXPos, int32_t nYPos, int32_t nWorldX, int32_t nWorldY);
//D2Client.0x6FAA3290
void __fastcall DFLOOR_DrawEdgeTile(D2FloorDrawContextStrc* pContext, int32_t nUnused, int32_t nX, int32_t nY);
//D2Client.0x6FAA3330
void __fastcall DFLOOR_DrawFloor(D2FloorDrawContextStrc* pContext, int32_t nUnused, D2GameViewStrc* pView);
//D2Client.0x6FAA3B90
void __fastcall DFLOOR_DrawRoofTiles(D2GameViewStrc* pView);
//D2Client.0x6FAA3E70
void __fastcall DFLOOR_ComputeTileLights(D2GfxLightExStrc* pLights, int32_t nWorldX, int32_t nWorldY, int32_t nHeight);
//D2Client.0x6FAA3F40
void __fastcall DFLOOR_ComputeTileLightsEx(D2GfxLightExStrc* pLights, int32_t nXPos, int32_t nYPos, int32_t nWorldX, int32_t nWorldY, int32_t nHeight, int32_t nScreenPanels, BOOL bLowQuality);
//D2Client.0x6FAA4060
void __fastcall DFLOOR_ComputeTileLightsPerspective(D2GfxLightExStrc* pLights, int32_t nWorldX, int32_t nWorldY, int32_t nHeight, int32_t nScreenPanels, BOOL bLowQuality);
//D2Client.0x6FAA4210
int32_t __fastcall DFLOOR_ApproximateDistance(int32_t nX, int32_t nY);
