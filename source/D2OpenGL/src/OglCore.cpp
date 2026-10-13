#include "OglCore.h"

#include <cmath>
#include <cstddef>
#include <cstring>
#include <iterator>

#include <Fog.h>

#include "OglDevice.h"
#include "OglImports.h"


D2GfxSettingsStrc* gpGfxSettings;
const D2GfxHelperStrc* gpGfxHelpers;
static D2PaletteTableStrc gPaletteTables;
D2PaletteTableStrc* gpPaletteTables = &gPaletteTables;

CRITICAL_SECTION* gpcsPause;
int32_t gbPaused;
int32_t gbWindowed;
HWND ghWnd;

uint8_t* gpbOffscreenBuffer;
HBITMAP ghOffscreenBitmap;
int32_t gnBufferWidth;
int32_t gnBufferHeight;

int32_t gnCelClipLeft;
int32_t gnCelClipRight;

PALETTEENTRY gGamePalette[256];
uint32_t gDisplayPalette[256];

// gGamePalette as the color table of the back buffer bitmap, used to draw text with GDI
static RGBQUAD gBitmapColorTable[256];
static HFONT ghFont;
static int32_t gbInitialized;
static int32_t gbDrawing;
static int32_t gnContrast = 100;
static int32_t gnGamma = 100;
static uint8_t gGammaRamp[256];


// Same resolutions as D2Gdi.dll
static void OGL_GetResolutionSize(D2GameResolutionMode nResolutionMode, int32_t* pWidth, int32_t* pHeight)
{
    switch (nResolutionMode)
    {
    case D2GAMERES_640x480:
        *pWidth = 640;
        *pHeight = 480;
        break;

    case D2GAMERES_1344x700:
        *pWidth = 1344;
        *pHeight = 700;
        break;

    default:
        *pWidth = 800;
        *pHeight = 600;
        break;
    }
}

static void OGL_BuildGammaRamp()
{
    if (FOG_BuildGammaRamp)
    {
        FOG_BuildGammaRamp(gnGamma, gGammaRamp, (double)gnContrast, sizeof(gGammaRamp[0]), std::size(gGammaRamp), 255);
        return;
    }

    // Approximation used if Fog.#10198 is not available, a gamma of 100 does not change the colors
    const double fExponent = 100.0 / (gnGamma > 0 ? gnGamma : 1);
    for (int32_t i = 0; i < std::size(gGammaRamp); ++i)
    {
        const double fValue = 255.0 * std::pow(i / 255.0, fExponent) * gnContrast / 100.0;
        gGammaRamp[i] = (uint8_t)(fValue < 0.0 ? 0.0 : fValue > 255.0 ? 255.0 : fValue + 0.5);
    }
}

static void OGL_UpdateDisplayPalette()
{
    for (int32_t i = 0; i < std::size(gDisplayPalette); ++i)
    {
        const PALETTEENTRY* pEntry = &gGamePalette[i];
        gDisplayPalette[i] = 0xFF000000u | (gGammaRamp[pEntry->peRed] << 16) | (gGammaRamp[pEntry->peGreen] << 8) | gGammaRamp[pEntry->peBlue];
    }
}

// Creates the 8 bits back buffer. This is a DIB section so that OGL_OutputString can draw into it with GDI.
static BOOL OGL_CreateBackBuffer(D2GameResolutionMode nResolutionMode)
{
    D2_ASSERT(gpbOffscreenBuffer == nullptr);

    OGL_GetResolutionSize(nResolutionMode, &gnBufferWidth, &gnBufferHeight);
    FOG_Trace("Opening OpenGL window at %dx%d...", gnBufferWidth, gnBufferHeight);

    struct
    {
        BITMAPINFOHEADER header;
        RGBQUAD colors[256];
    } bitmapInfo = {};

    bitmapInfo.header.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.header.biWidth = gnBufferWidth;
    bitmapInfo.header.biHeight = -gnBufferHeight; // Top-down
    bitmapInfo.header.biPlanes = 1;
    bitmapInfo.header.biBitCount = 8;
    bitmapInfo.header.biCompression = BI_RGB;
    memcpy(bitmapInfo.colors, gBitmapColorTable, sizeof(bitmapInfo.colors));

    HDC hScreenDC = GetDC(nullptr);
    ghOffscreenBitmap = CreateDIBSection(hScreenDC, (BITMAPINFO*)&bitmapInfo, DIB_RGB_COLORS, (void**)&gpbOffscreenBuffer, nullptr, 0);
    ReleaseDC(nullptr, hScreenDC);

    if (!ghOffscreenBitmap || !gpbOffscreenBuffer)
    {
        FOG_Trace("D2OpenGL: CreateDIBSection failed (%d)", GetLastError());
        ghOffscreenBitmap = nullptr;
        gpbOffscreenBuffer = nullptr;
        return FALSE;
    }

    // DIB rows are aligned on 4 bytes, which all the resolutions are
    D2_ASSERT((gnBufferWidth & 3) == 0);

    gnCelClipLeft = 0;
    gnCelClipRight = gnBufferWidth;

    gpGfxHelpers->pfFillYBufferTable(gpbOffscreenBuffer, gnBufferWidth, gnBufferHeight, 0);
    return TRUE;
}

static void OGL_DestroyBackBuffer()
{
    if (ghOffscreenBitmap)
    {
        DeleteObject(ghOffscreenBitmap);
        ghOffscreenBitmap = nullptr;
    }

    gpbOffscreenBuffer = nullptr;
    gpGfxHelpers->pfFillYBufferTable(nullptr, 0, 0, 0);
}

// Fullscreen windows are borderless windows covering the whole screen, which uses the game resolution
static void OGL_UpdateDisplayMode()
{
    if (gbWindowed || !ghWnd)
    {
        return;
    }

    DEVICE_SetDisplayMode(gnBufferWidth, gnBufferHeight);
    SetWindowPos(ghWnd, nullptr, 0, 0, gnBufferWidth, gnBufferHeight, SWP_NOZORDER | SWP_NOACTIVATE);
}

static BOOL OGL_SetResolution(D2GameResolutionMode nResolutionMode)
{
    if (gpbOffscreenBuffer)
    {
        OGL_DestroyBackBuffer();
    }

    if (!OGL_CreateBackBuffer(nResolutionMode))
    {
        return FALSE;
    }

    OGL_UpdateDisplayMode();

    if (!DEVICE_SetFrameSize(gnBufferWidth, gnBufferHeight))
    {
        return FALSE;
    }

    memset(DEVICE_GetFrameBuffer(), 0, sizeof(uint32_t) * gnBufferWidth * gnBufferHeight);
    return TRUE;
}

//pfDetect
BOOL __fastcall OGL_Detect(HINSTANCE hInstance)
{
    FOG_Trace("Detecting OpenGL support...");
    return TRUE;
}

//pfInit
BOOL __fastcall OGL_Init(D2GfxSettingsStrc* pSettings, const D2GfxHelperStrc* pHelpers)
{
    D2_ASSERT(!gbInitialized);

    FOG_Trace("Initializing for OpenGL...");

    gpGfxSettings = pSettings;
    gpGfxHelpers = pHelpers;

    // The game is rendered in software, there is no support for the perspective mode
    pSettings->bPerspectiveCapable = FALSE;

    if (!IMPORTS_Load())
    {
        FOG_Trace("D2OpenGL: Some functions required for rendering are missing.");
        IMPORTS_Unload();
        return FALSE;
    }

    OGL_BuildGammaRamp();
    OGL_UpdateDisplayPalette();

    gpcsPause = (CRITICAL_SECTION*)D2_ALLOC(sizeof(CRITICAL_SECTION));
    InitializeCriticalSection(gpcsPause);

    gbInitialized = TRUE;
    return TRUE;
}

//pfClose
BOOL __fastcall OGL_Close()
{
    if (gpcsPause)
    {
        DeleteCriticalSection(gpcsPause);
        D2_FREE(gpcsPause);
        gpcsPause = nullptr;
    }

    if (gbInitialized)
    {
        IMPORTS_Unload();
        gbInitialized = FALSE;
    }

    return TRUE;
}

//pfCreateSurface
BOOL __fastcall OGL_CreateSurface(HWND hWnd, D2GameResolutionMode nResolutionMode)
{
    ghWnd = hWnd;

    if (!DEVICE_Create(hWnd))
    {
        FOG_Trace("Opening OpenGL window failed!");
        ghWnd = nullptr;
        return FALSE;
    }

    if (!OGL_SetResolution(nResolutionMode))
    {
        FOG_Trace("Opening OpenGL window failed!");
        OGL_CloseSurface();
        return FALSE;
    }

    DEVICE_SetVSync(gpGfxSettings->bVSync);

    // Same font as D2Gdi.dll
    ghFont = CreateFontA(10, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, "Courier");

    FOG_Trace("Opening OpenGL window succeeded.");
    return TRUE;
}

//pfCloseSurface
BOOL __fastcall OGL_CloseSurface()
{
    if (ghFont)
    {
        DeleteObject(ghFont);
        ghFont = nullptr;
    }

    if (gpbOffscreenBuffer)
    {
        OGL_DestroyBackBuffer();
    }

    DEVICE_Destroy();
    DEVICE_RestoreDisplayMode();
    ghWnd = nullptr;
    return TRUE;
}

//pfPauseSurface
void __fastcall OGL_PauseSurface(HWND hWnd, D2GameResolutionMode nResolutionMode, int32_t bPaused)
{
    D2_ASSERT(gpcsPause);

    EnterCriticalSection(gpcsPause);
    gbPaused = bPaused;

    // Give back the desktop resolution while the game is minimized
    if (bPaused)
    {
        DEVICE_RestoreDisplayMode();
    }
    else
    {
        OGL_UpdateDisplayMode();
    }

    LeaveCriticalSection(gpcsPause);
}

//pfStartDraw
BOOL __fastcall OGL_StartDraw(int32_t bClear, uint8_t nRed, uint8_t nGreen, uint8_t nBlue)
{
    if (gbPaused || !gpbOffscreenBuffer)
    {
        return FALSE;
    }

    D2_ASSERT(gpcsPause);

    EnterCriticalSection(gpcsPause);
    gbDrawing = TRUE;

    if (bClear)
    {
        // Same as D2Gdi.dll, the color is ignored and the bottom panel is not cleared
        memset(gpbOffscreenBuffer, 0, gnBufferWidth * (gnBufferHeight - BOTTOM_PANEL_HEIGHT));
    }

    return TRUE;
}

//pfEndDraw
BOOL __fastcall OGL_EndDraw()
{
    D2_ASSERT(gpcsPause);

    if (gbDrawing)
    {
        gbDrawing = FALSE;
        LeaveCriticalSection(gpcsPause);
    }

    return TRUE;
}

//pfBlit
BOOL __fastcall OGL_Blit()
{
    if (gbPaused || !gpbOffscreenBuffer)
    {
        return TRUE;
    }

    if (!DEVICE_IsCreated())
    {
        return FALSE;
    }

    // The palette is applied by the GPU
    DEVICE_PresentIndexed(gpbOffscreenBuffer, gDisplayPalette);
    return TRUE;
}

//pfChangeRes
BOOL __fastcall OGL_ChangeRes(HWND hWnd, D2GameResolutionMode nResolutionMode)
{
    return OGL_SetResolution(nResolutionMode);
}

//pfGetBackBuffer
BOOL __fastcall OGL_GetBackBuffer(uint8_t* pBuffer)
{
    // 24 bits RGB, top-down, same as the other renderers
    const uint8_t* pSrc = gpbOffscreenBuffer;
    for (int32_t nY = 0; nY < gnBufferHeight; ++nY)
    {
        for (int32_t nX = 0; nX < gnBufferWidth; ++nX)
        {
            const uint32_t nColor = gDisplayPalette[*pSrc++];
            *pBuffer++ = (nColor >> 16) & 0xFF;
            *pBuffer++ = (nColor >> 8) & 0xFF;
            *pBuffer++ = nColor & 0xFF;
        }
    }

    return TRUE;
}

//pfActivateWindow
BOOL __fastcall OGL_ActivateWindow()
{
    return FALSE;
}

//pfSetOption
BOOL __fastcall OGL_SetOption(int32_t nOption, int32_t nValue)
{
    switch (nOption)
    {
    case 8: // Windowed, set by D2Gfx before pfDetect
        gbWindowed = nValue;
        return TRUE;

    case 11: // Contrast, applied by the next pfSetGamma
        gnContrast = nValue;
        return TRUE;

    default:
        return FALSE;
    }
}

//pfPlayCutscene
BOOL __fastcall OGL_PlayCutscene()
{
    if (gbPaused)
    {
        return FALSE;
    }

    // Same as D2DDraw.dll, cutscenes are played at 640x480. The game restores its resolution with pfChangeRes afterwards.
    FOG_Trace("Opening OpenGL window at 640x480 for cutscenes...");
    return OGL_SetResolution(D2GAMERES_640x480);
}

//pfGetCacheResults
void* __fastcall OGL_GetCacheResults()
{
    return nullptr;
}

//pfGetDimensions
BOOL __fastcall OGL_GetDimensions(int32_t* pWidth, int32_t* pHeight)
{
    *pWidth = gnBufferWidth;
    *pHeight = gnBufferHeight;
    return TRUE;
}

//pfSetGlobalScale
void __fastcall OGL_SetGlobalScale(int32_t nScaleFactor)
{
}

//pfSetGamma
BOOL __fastcall OGL_SetGamma(int32_t nGamma)
{
    gnGamma = nGamma;
    OGL_BuildGammaRamp();
    OGL_UpdateDisplayPalette();
    return TRUE;
}

//pfGammaCanBeControlled
int32_t __fastcall OGL_GammaCanBeControlled()
{
    return TRUE;
}

//pfUpdatePerspective
void __fastcall OGL_UpdatePerspective(int32_t nScaleX, int32_t nScaleY)
{
}

//pfPerspectiveTransform
void __fastcall OGL_PerspectiveTransform(int32_t nPosX, int32_t nPosY, int32_t nBias, int32_t* pXAdjust, int32_t* pYAdjust)
{
    // Perspective is not supported, same as the software renderers
}

//pfPerspectiveTransformScale
void __fastcall OGL_PerspectiveTransformScale(int32_t nPosX, int32_t nPosY, int32_t nAngle, int32_t* pXAdjust, int32_t* pYAdjust, int32_t bOrder)
{
    // Perspective is not supported, same as the software renderers
}

//pfPerspectiveClearScale
void __fastcall OGL_PerspectiveClearScale()
{
}

//pfSetPalette
void __fastcall OGL_SetPalette(LPPALETTEENTRY pPalette)
{
    memcpy(gGamePalette, pPalette, sizeof(gGamePalette));

    for (int32_t i = 0; i < std::size(gBitmapColorTable); ++i)
    {
        gBitmapColorTable[i].rgbRed = pPalette[i].peRed;
        gBitmapColorTable[i].rgbGreen = pPalette[i].peGreen;
        gBitmapColorTable[i].rgbBlue = pPalette[i].peBlue;
        gBitmapColorTable[i].rgbReserved = 0;
    }

    OGL_UpdateDisplayPalette();
}

//pfSetPaletteTables
void __fastcall OGL_SetPaletteTables(D2PaletteTableStrc* pPaletteTables)
{
    // Only the pointers are copied, the palettes are owned by the game
    memcpy(&gPaletteTables, pPaletteTables, offsetof(D2PaletteTableStrc, datFilePalette));
    gpPaletteTables = &gPaletteTables;
}

//pfSetAmbientColor
void __fastcall OGL_SetAmbientColor(uint8_t nRed, uint8_t nGreen, uint8_t nBlue)
{
    // The software renderers only support the light intensity
}

//pfOutputString
void __fastcall OGL_OutputString(int32_t nPosX, int32_t nPosY, const char* szFormat, va_list va)
{
    if (!ghOffscreenBitmap)
    {
        return;
    }

    char szBuffer[512] = {};
    wvsprintfA(szBuffer, szFormat, va);

    HDC hScreenDC = GetDC(nullptr);
    HDC hDC = CreateCompatibleDC(hScreenDC);
    HGDIOBJ hOldBitmap = SelectObject(hDC, ghOffscreenBitmap);
    HGDIOBJ hOldFont = SelectObject(hDC, ghFont);

    // The text color is matched against the color table of the bitmap
    SetDIBColorTable(hDC, 0, std::size(gBitmapColorTable), gBitmapColorTable);
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkColor(hDC, RGB(0, 0, 0));
    SetBkMode(hDC, TRANSPARENT);

    RECT rect = {};
    SetRect(&rect, nPosX, nPosY, gnBufferWidth - nPosX, gnBufferHeight - nPosY);
    DrawTextA(hDC, szBuffer, -1, &rect, 0);
    GdiFlush();

    SelectObject(hDC, hOldFont);
    SelectObject(hDC, hOldBitmap);
    DeleteDC(hDC);
    ReleaseDC(nullptr, hScreenDC);
}

//pfDebugDraw
void __fastcall OGL_DebugDraw(uint32_t* pLight, uint32_t* pPlayerLight, int32_t nPosX, int32_t nPosY)
{
}

//pfClearCaches
void __fastcall OGL_ClearCaches()
{
}

uint8_t* __fastcall OGL_GetBlendTable(DrawMode eDrawMode)
{
    switch (eDrawMode)
    {
    case DRAWMODE_TRANS25:
        return (uint8_t*)gpPaletteTables->transPalettes[2];

    case DRAWMODE_TRANS50:
        return (uint8_t*)gpPaletteTables->transPalettes[1];

    case DRAWMODE_TRANS75:
        return (uint8_t*)gpPaletteTables->transPalettes[0];

    case DRAWMODE_MODULATE:
        return (uint8_t*)gpPaletteTables->pScreenPalette;

    case DRAWMODE_BURN:
        return (uint8_t*)gpPaletteTables->pLuminancePalette;

    case DRAWMODE_TRANSHIGHLIGHT:
        return (uint8_t*)gpPaletteTables->pDarkBlendPalette;

    default:
        return nullptr;
    }
}
