#include "OglSprite.h"

#include <algorithm>

#include <Fog.h>

#include "OglCore.h"
#include "OglImports.h"


// Returns the light palette matching the intensity in the low byte of dwGamma, nullptr for full intensity.
// The hardware renderers also use the color stored in the other bytes, which is ignored here.
static uint8_t* OGL_GetLightPalette(uint32_t dwGamma, DrawMode eDrawMode)
{
    if (eDrawMode == DRAWMODE_HIGHLIGHT)
    {
        return gpPaletteTables->unk0x118;
    }

    const uint8_t nIntensity = dwGamma & 0xFF;
    if (nIntensity == 0xFF)
    {
        return nullptr;
    }

    return (uint8_t*)gpPaletteTables->shadowLightGammaPalettes[nIntensity >> 3];
}

// Returns TRUE if the cel is (at least partially) inside the back buffer
static BOOL OGL_IsCelVisible(D2GfxCellStrc* pCell, int32_t nPosX, int32_t nPosY)
{
    const int32_t nLeft = D2CMP_CelGetOffsetX(pCell) + nPosX;
    if (nLeft >= gnBufferWidth || nLeft + D2CMP_CelGetWidth(pCell) < 0)
    {
        return FALSE;
    }

    // Cels are drawn upwards from their bottom line
    const int32_t nBottom = D2CMP_CelGetOffsetY(pCell) + nPosY;
    if (nBottom < 0 || nBottom - D2CMP_CelGetHeight(pCell) >= gnBufferHeight)
    {
        return FALSE;
    }

    return TRUE;
}

//pfCelFlatSpriteDraw
// Port of D2Gdi.0x6F832600
void __fastcall OGL_CelFlatSpriteDraw(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, int32_t nScreenMode, uint8_t* pPalette)
{
    OGL_CelDraw(pData, nPosX, nPosY, dwGamma, eDrawMode, pPalette);
}

//pfCelDraw
// Port of D2Gdi.0x6F832620
void __fastcall OGL_CelDraw(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, uint8_t* pPalette)
{
    if (!D2CMP_SpriteValidate(pData, 0, TRUE) || !OGL_IsCelVisible(pData->pCurrentCell, nPosX, nPosY))
    {
        return;
    }

    D2CMP_CelDraw(pData, nPosX, nPosY, gnCelClipLeft, gnCelClipRight, gpbOffscreenBuffer, gnBufferHeight, gnBufferWidth,
        OGL_GetLightPalette(dwGamma, eDrawMode), OGL_GetBlendTable(eDrawMode), pPalette);
}

//pfCelDrawColor
// Port of D2Gdi.0x6F832750
void __fastcall OGL_CelDrawColor(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint32_t dwGamma, DrawMode eDrawMode, int32_t nGlobalPaletteShift)
{
    if (!D2CMP_SpriteValidate(pData, 0, TRUE) || !OGL_IsCelVisible(pData->pCurrentCell, nPosX, nPosY))
    {
        return;
    }

    uint8_t* pPalette = nullptr;
    if (nGlobalPaletteShift)
    {
        pPalette = (uint8_t*)gpPaletteTables->standardShiftPalettes[nGlobalPaletteShift];
    }

    D2CMP_CelDraw(pData, nPosX, nPosY, gnCelClipLeft, gnCelClipRight, gpbOffscreenBuffer, gnBufferHeight, gnBufferWidth,
        OGL_GetLightPalette(dwGamma, eDrawMode), OGL_GetBlendTable(eDrawMode), pPalette);
}

//pfCelDrawEx
// Port of D2Gdi.0x6F832890
void __fastcall OGL_CelDrawEx(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, int32_t nSkipLines, int32_t nDrawLines, DrawMode eDrawMode)
{
    if (!D2CMP_SpriteValidate(pData, 0, TRUE) || !OGL_IsCelVisible(pData->pCurrentCell, nPosX, nPosY))
    {
        return;
    }

    D2CMP_CelDrawEx(pData, nPosX, nPosY, gnCelClipLeft, gnCelClipRight, gpbOffscreenBuffer, gnBufferHeight, gnBufferWidth,
        nullptr, OGL_GetBlendTable(eDrawMode), nSkipLines, nDrawLines, nullptr);
}

//pfCelDrawShadow
// Port of D2Gdi.0x6F832B90
void __fastcall OGL_CelDrawShadow(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY)
{
    if (!D2CMP_SpriteValidate(pData, 0, TRUE))
    {
        return;
    }

    D2GfxCellStrc* pCell = pData->pCurrentCell;
    const int32_t nWidth = D2CMP_CelGetWidth(pCell);
    const int32_t nHeight = D2CMP_CelGetHeight(pCell);

    // Shadows are skewed to the left, and half as high as the cel
    const int32_t nLeft = nPosX - nHeight + D2CMP_CelGetOffsetX(pCell);
    if (nLeft >= gnBufferWidth || nLeft + nWidth + nHeight < 0)
    {
        return;
    }

    const int32_t nBottom = D2CMP_CelGetOffsetY(pCell) + nPosY;
    if (nBottom < 0 || nBottom - (nHeight >> 1) >= gnBufferHeight)
    {
        return;
    }

    uint8_t* pBlendTable = nullptr;
    if (gpGfxSettings->bBlendedShadows)
    {
        pBlendTable = (uint8_t*)gpPaletteTables->transPalettes[0];
    }

    D2CMP_CelDrawShadow(pData, nPosX, nPosY, gnCelClipLeft, gnCelClipRight, gpbOffscreenBuffer, gnBufferHeight, gnBufferWidth, pBlendTable, 0);
}

//pfCelDrawHilight
// Not supported by the software renderers either
void __fastcall OGL_CelDrawHilight(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, uint8_t nPaletteIndex)
{
}

//pfCelDrawClipped
// Port of D2Gdi.0x6F8329C0
void __fastcall OGL_CelDrawClipped(D2GfxDataStrc* pData, int32_t nPosX, int32_t nPosY, void* pCropRect, DrawMode eDrawMode)
{
    if (!D2CMP_SpriteValidate(pData, 0, TRUE))
    {
        return;
    }

    const D2GfxCropRectStrc* pClipRect = (const D2GfxCropRectStrc*)pCropRect;
    D2GfxCellStrc* pCell = pData->pCurrentCell;
    const int32_t nWidth = D2CMP_CelGetWidth(pCell);
    const int32_t nHeight = D2CMP_CelGetHeight(pCell);

    const int32_t nClipLeft = std::max(pClipRect->nLeft, 0);
    const int32_t nClipRight = std::min(pClipRect->nRight, gnBufferWidth);
    if (nClipLeft > nClipRight)
    {
        return;
    }

    const int32_t nLeft = D2CMP_CelGetOffsetX(pCell) + nPosX;
    if (nLeft >= nClipRight || nLeft + nWidth < nClipLeft)
    {
        return;
    }

    const int32_t nClipTop = std::max(pClipRect->nTop, 0);
    const int32_t nClipBottom = std::min(pClipRect->nBottom, gnBufferHeight);
    if (nClipTop > nClipBottom)
    {
        return;
    }

    const int32_t nBottom = D2CMP_CelGetOffsetY(pCell) + nPosY;
    if (nBottom < nClipTop)
    {
        return;
    }

    const int32_t nTop = nBottom - nHeight;
    if (nTop > nClipBottom)
    {
        return;
    }

    // Cels are drawn upwards, so lines are skipped from the bottom
    const int32_t nSkipLines = nBottom > nClipBottom ? nBottom - nClipBottom - 1 : 0;
    const int32_t nDrawLines = nTop >= nClipTop ? nHeight - nSkipLines : nBottom - nClipTop - nSkipLines + 1;
    D2_ASSERT(nDrawLines > 0);

    D2CMP_CelDrawEx(pData, nPosX, nPosY, nClipLeft, nClipRight, gpbOffscreenBuffer, gnBufferHeight, gnBufferWidth,
        nullptr, OGL_GetBlendTable(eDrawMode), nSkipLines, nDrawLines, nullptr);
}

//pfDebugFillBackBuffer
// Port of D2Gdi.0x6F832C60
void __fastcall OGL_DebugFillBackBuffer(int32_t nPosX, int32_t nPosY)
{
    D2_ASSERT(nPosX > 0 && nPosX < gnBufferWidth - 80);
    D2_ASSERT(nPosY > 0 && nPosY < gnBufferHeight - 80);

    D2CMP_DebugFillBuffer(&gpbOffscreenBuffer[nPosY * gnBufferWidth + nPosX], gnBufferWidth);
}
