#pragma once

#include <cstdint>

#include <Windows.h>

#include <D2Gfx.h>


// The OpenGL renderer draws the game exactly like D2Gdi.dll and D2DDraw.dll do: everything is rendered into an 8 bits
// back buffer by D2CMP (cels) and D2Gfx (tiles), which guarantees the same output as the original software renderers.
// The back buffer is then converted to 32 bits using the gamma corrected palette and presented with OpenGL,
// which takes care of scaling, vertical synchronization and fullscreen.

constexpr int32_t BOTTOM_PANEL_HEIGHT = 47;

extern D2GfxSettingsStrc* gpGfxSettings;
extern const D2GfxHelperStrc* gpGfxHelpers;
extern D2PaletteTableStrc* gpPaletteTables;

extern CRITICAL_SECTION* gpcsPause;
extern int32_t gbPaused;
extern int32_t gbWindowed;
extern HWND ghWnd;

// The 8 bits back buffer. Its pitch is always gnBufferWidth.
extern uint8_t* gpbOffscreenBuffer;
extern HBITMAP ghOffscreenBitmap;
extern int32_t gnBufferWidth;
extern int32_t gnBufferHeight;

// Horizontal clipping of the cels
extern int32_t gnCelClipLeft;
extern int32_t gnCelClipRight;

// The last palette set by the game, without gamma correction
extern PALETTEENTRY gGamePalette[256];
// gGamePalette with gamma correction, as 0xAARRGGBB (BGRA in memory)
extern uint32_t gDisplayPalette[256];


//pfDetect
BOOL __fastcall OGL_Detect(HINSTANCE hInstance);
//pfInit
BOOL __fastcall OGL_Init(D2GfxSettingsStrc* pSettings, const D2GfxHelperStrc* pHelpers);
//pfClose
BOOL __fastcall OGL_Close();
//pfCreateSurface
BOOL __fastcall OGL_CreateSurface(HWND hWnd, D2GameResolutionMode nResolutionMode);
//pfCloseSurface
BOOL __fastcall OGL_CloseSurface();
//pfPauseSurface
void __fastcall OGL_PauseSurface(HWND hWnd, D2GameResolutionMode nResolutionMode, int32_t bPaused);
//pfStartDraw
BOOL __fastcall OGL_StartDraw(int32_t bClear, uint8_t nRed, uint8_t nGreen, uint8_t nBlue);
//pfEndDraw
BOOL __fastcall OGL_EndDraw();
//pfBlit
BOOL __fastcall OGL_Blit();
//pfChangeRes
BOOL __fastcall OGL_ChangeRes(HWND hWnd, D2GameResolutionMode nResolutionMode);
//pfGetBackBuffer
BOOL __fastcall OGL_GetBackBuffer(uint8_t* pBuffer);
//pfActivateWindow
BOOL __fastcall OGL_ActivateWindow();
//pfSetOption
BOOL __fastcall OGL_SetOption(int32_t nOption, int32_t nValue);
//pfPlayCutscene
BOOL __fastcall OGL_PlayCutscene();
//pfGetCacheResults
void* __fastcall OGL_GetCacheResults();
//pfGetDimensions
BOOL __fastcall OGL_GetDimensions(int32_t* pWidth, int32_t* pHeight);
//pfSetGlobalScale
void __fastcall OGL_SetGlobalScale(int32_t nScaleFactor);
//pfSetGamma
BOOL __fastcall OGL_SetGamma(int32_t nGamma);
//pfGammaCanBeControlled
int32_t __fastcall OGL_GammaCanBeControlled();
//pfUpdatePerspective
void __fastcall OGL_UpdatePerspective(int32_t nScaleX, int32_t nScaleY);
//pfPerspectiveTransform
void __fastcall OGL_PerspectiveTransform(int32_t nPosX, int32_t nPosY, int32_t nBias, int32_t* pXAdjust, int32_t* pYAdjust);
//pfPerspectiveTransformScale
void __fastcall OGL_PerspectiveTransformScale(int32_t nPosX, int32_t nPosY, int32_t nAngle, int32_t* pXAdjust, int32_t* pYAdjust, int32_t bOrder);
//pfPerspectiveClearScale
void __fastcall OGL_PerspectiveClearScale();
//pfSetPalette
void __fastcall OGL_SetPalette(LPPALETTEENTRY pPalette);
//pfSetPaletteTables
void __fastcall OGL_SetPaletteTables(D2PaletteTableStrc* pPaletteTables);
//pfSetAmbientColor
void __fastcall OGL_SetAmbientColor(uint8_t nRed, uint8_t nGreen, uint8_t nBlue);
//pfOutputString
void __fastcall OGL_OutputString(int32_t nPosX, int32_t nPosY, const char* szFormat, va_list va);
//pfDebugDraw
void __fastcall OGL_DebugDraw(uint32_t* pLight, uint32_t* pPlayerLight, int32_t nPosX, int32_t nPosY);
//pfClearCaches
void __fastcall OGL_ClearCaches();

// Returns the blend table matching the draw mode, or nullptr if the cel is opaque
uint8_t* __fastcall OGL_GetBlendTable(DrawMode eDrawMode);
