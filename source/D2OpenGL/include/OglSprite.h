#pragma once

#include <cstdint>

#include <DrawMode.h>


struct D2GfxDataStrc;


// Cels drawn into the 8 bits back buffer by D2CMP, ported from D2Gdi.dll (gdiSprite.cpp)

#pragma pack(push, 1)
// Crop rectangle passed to pfCelDrawClipped. Note that the order differs from RECT.
struct D2GfxCropRectStrc
{
    int32_t nLeft;                              //0x00
    int32_t nRight;                             //0x04
    int32_t nTop;                               //0x08
    int32_t nBottom;                            //0x0C
};
#pragma pack(pop)


//pfCelFlatSpriteDraw
void __fastcall OGL_CelFlatSpriteDraw(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, int32_t nScreenMode, uint8_t* pPalette);
//pfCelDraw
void __fastcall OGL_CelDraw(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, uint8_t* pPalette);
//pfCelDrawColor
void __fastcall OGL_CelDrawColor(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, int32_t nGlobalPaletteShift);
//pfCelDrawEx
void __fastcall OGL_CelDrawEx(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, int32_t nSkipLines, int32_t nDrawLines, DrawMode eDrawMode);
//pfCelDrawShadow
void __fastcall OGL_CelDrawShadow(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY);
//pfCelDrawHilight
void __fastcall OGL_CelDrawHilight(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint8_t nPaletteIndex);
//pfCelDrawClipped
void __fastcall OGL_CelDrawClipped(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, void* pCropRect, DrawMode eDrawMode);
//pfDebugFillBackBuffer
void __fastcall OGL_DebugFillBackBuffer(int32_t nPosX, int32_t nPosY);
