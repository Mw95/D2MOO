#pragma once

#include <cstdint>

#include <Windows.h>

#include <DrawMode.h>


// Primitives drawn into the 8 bits back buffer, ported from D2Gdi.dll (gdiEngine.cpp)

//pfUtilDiamond
void __fastcall OGL_UtilDiamond(RECT* pRect, uint8_t nPaletteIndex);
//pfUtilRect
void __fastcall OGL_UtilRect(RECT* pRect, uint8_t nPaletteIndex);
//pfUtilFilledRect
void __fastcall OGL_UtilFilledRect(RECT* pRect, uint8_t nPaletteIndex);
//pfUtilPoint
void __fastcall OGL_UtilPoint(POINT* pPoint, uint8_t nSize, uint8_t nPaletteIndex);
//pfDrawBox
void __fastcall OGL_DrawBox(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, DrawMode eDrawMode);
//pfDrawBoxAlpha
void __fastcall OGL_DrawBoxAlpha(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha);
//pfDrawLine
void __fastcall OGL_DrawLine(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha);
//pfClearScreen
void __fastcall OGL_ClearScreen(int32_t bPartial);
