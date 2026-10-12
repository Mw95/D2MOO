#include "OglEngine.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iterator>

#include <Fog.h>

#include "OglCore.h"


enum D2OglBoxBlendType
{
    BOXBLEND_NONE,      // Filled with the color
    BOXBLEND_REMAP,     // Each pixel is remapped with the first line of the blend table, the color is ignored
    BOXBLEND_COLOR,     // Each pixel is blended with the color
};

// D2Gdi.0x6F839484
constexpr D2OglBoxBlendType gnBoxBlendTypes[] =
{
    BOXBLEND_COLOR,     // DRAWMODE_TRANS25
    BOXBLEND_COLOR,     // DRAWMODE_TRANS50
    BOXBLEND_COLOR,     // DRAWMODE_TRANS75
    BOXBLEND_REMAP,     // DRAWMODE_MODULATE
    BOXBLEND_REMAP,     // DRAWMODE_BURN
    BOXBLEND_NONE,      // DRAWMODE_NORMAL
    BOXBLEND_REMAP,     // DRAWMODE_TRANSHIGHLIGHT
    BOXBLEND_NONE,      // DRAWMODE_HIGHLIGHT
};


// Draws a line of the given color, clipped to the back buffer
// Port of D2Gdi.0x6F831C10
static void OGL_UtilLine(const POINT* pFrom, const POINT* pTo, uint8_t nPaletteIndex)
{
    const int32_t nDeltaX = pTo->x - pFrom->x;
    const int32_t nDeltaY = pTo->y - pFrom->y;
    if (!nDeltaX && !nDeltaY)
    {
        return;
    }

    // Length of the line, rounded up
    const int32_t nSquaredLength = nDeltaX * nDeltaX + nDeltaY * nDeltaY;
    int32_t nLength = 0;
    while (nLength * nLength < nSquaredLength)
    {
        ++nLength;
    }

    // 16.16 fixed point steps
    const int32_t nStepX = (nDeltaX << 16) / nLength;
    const int32_t nStepY = (nDeltaY << 16) / nLength;

    int32_t nX = pFrom->x;
    int32_t nY = pFrom->y;
    int32_t nFractionX = 0;
    int32_t nFractionY = 0;

    auto advance = [](int32_t& nPos, int32_t& nFraction, int32_t nStep)
    {
        nFraction += nStep;
        if (nFraction >= 0x10000 || nFraction <= -0x10000)
        {
            const int32_t nMove = nFraction / 0x10000;
            nPos += nMove;
            nFraction -= nMove << 16;
        }
    };

    // Skip the points outside of the buffer, until the line enters it
    // Note: the original dll never increments the counter here, so a line that never enters the buffer loops (almost) forever
    int32_t nPoint = 0;
    while (nY < 0 || nY >= gnBufferHeight || nX < 0 || nX >= gnBufferWidth)
    {
        if (nPoint >= nLength)
        {
            return;
        }

        advance(nX, nFractionX, nStepX);
        advance(nY, nFractionY, nStepY);
        ++nPoint;
    }

    // Draw until the line leaves the buffer
    while (true)
    {
        gpbOffscreenBuffer[nY * gnBufferWidth + nX] = nPaletteIndex;

        ++nPoint;
        if (nPoint >= nLength)
        {
            return;
        }

        advance(nX, nFractionX, nStepX);
        if (nX < 0 || nX >= gnBufferWidth)
        {
            return;
        }

        advance(nY, nFractionY, nStepY);
        if (nY < 0 || nY >= gnBufferHeight)
        {
            return;
        }
    }
}

//pfUtilDiamond
// Port of D2Gdi.0x6F831B40
void __fastcall OGL_UtilDiamond(RECT* pRect, uint8_t nPaletteIndex)
{
    D2_ASSERT(pRect->left <= pRect->right);
    D2_ASSERT(pRect->top <= pRect->bottom);

    const uint32_t nWidth = pRect->right - pRect->left;
    const uint32_t nHeight = pRect->bottom - pRect->top;
    if (!nWidth || !nHeight)
    {
        return;
    }

    const int32_t nCenterX = pRect->left + (nWidth >> 1);
    const int32_t nCenterY = pRect->top + (nHeight >> 1);

    const POINT top = { nCenterX, pRect->top };
    const POINT right = { pRect->right, nCenterY };
    const POINT bottom = { nCenterX, pRect->bottom };
    const POINT left = { pRect->left, nCenterY };

    OGL_UtilLine(&top, &right, nPaletteIndex);
    OGL_UtilLine(&right, &bottom, nPaletteIndex);
    OGL_UtilLine(&bottom, &left, nPaletteIndex);
    OGL_UtilLine(&left, &top, nPaletteIndex);
}

//pfUtilRect
// Port of D2Gdi.0x6F831DF0
void __fastcall OGL_UtilRect(RECT* pRect, uint8_t nPaletteIndex)
{
    D2_ASSERT(pRect->left <= pRect->right);
    D2_ASSERT(pRect->top <= pRect->bottom);

    if (pRect->right == pRect->left || pRect->bottom == pRect->top)
    {
        return;
    }

    const POINT topLeft = { pRect->left, pRect->top };
    const POINT topRight = { pRect->right, pRect->top };
    const POINT bottomRight = { pRect->right, pRect->bottom };
    const POINT bottomLeft = { pRect->left, pRect->bottom };

    OGL_UtilLine(&topLeft, &topRight, nPaletteIndex);
    OGL_UtilLine(&topRight, &bottomRight, nPaletteIndex);
    OGL_UtilLine(&bottomRight, &bottomLeft, nPaletteIndex);
    OGL_UtilLine(&bottomLeft, &topLeft, nPaletteIndex);
}

//pfUtilFilledRect
// Port of D2Gdi.0x6F831EC0
void __fastcall OGL_UtilFilledRect(RECT* pRect, uint8_t nPaletteIndex)
{
    D2_ASSERT(pRect->left <= pRect->right);
    D2_ASSERT(pRect->top <= pRect->bottom);

    if (pRect->right < 0 || pRect->left >= gnBufferWidth || pRect->bottom < 0 || pRect->top >= gnBufferHeight)
    {
        return;
    }

    // Note: the rectangle of the caller is clipped
    if (pRect->left < 0)
    {
        pRect->left = 0;
    }

    if (pRect->right >= gnBufferWidth)
    {
        pRect->right = gnBufferWidth - 1;
    }

    if (pRect->top < 0)
    {
        pRect->top = 0;
    }

    if (pRect->bottom >= gnBufferHeight)
    {
        pRect->bottom = gnBufferHeight - 1;
    }

    const int32_t nWidth = pRect->right - pRect->left;
    const int32_t nHeight = pRect->bottom - pRect->top;
    if (!nWidth || !nHeight)
    {
        return;
    }

    uint8_t* pLine = &gpbOffscreenBuffer[pRect->top * gnBufferWidth + pRect->left];
    for (int32_t nLine = 0; nLine < nHeight; ++nLine)
    {
        memset(pLine, nPaletteIndex, nWidth);
        pLine += gnBufferWidth;
    }
}

//pfUtilPoint
// Port of D2Gdi.0x6F831FE0
void __fastcall OGL_UtilPoint(POINT* pPoint, uint8_t nSize, uint8_t nPaletteIndex)
{
    if (!nSize)
    {
        return;
    }

    const int32_t nExtent = nSize - 1;

    RECT rect = {};
    SetRect(&rect, pPoint->x - nExtent, pPoint->y - nExtent, pPoint->x + nExtent + 1, pPoint->y + nExtent + 1);
    OGL_UtilFilledRect(&rect, nPaletteIndex);
}

//pfDrawBox
// Port of D2Gdi.0x6F8317F0
void __fastcall OGL_DrawBox(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, DrawMode eDrawMode)
{
    const D2OglBoxBlendType eBlendType = eDrawMode >= 0 && eDrawMode < std::size(gnBoxBlendTypes) ? gnBoxBlendTypes[eDrawMode] : BOXBLEND_NONE;
    const uint8_t* pBlendTable = OGL_GetBlendTable(eDrawMode);
    if (eBlendType != BOXBLEND_NONE && !pBlendTable)
    {
        // The palette tables were not set yet
        return;
    }

    // Note: the last column and line of the buffer are never drawn
    const int32_t nLeft = std::clamp(nXStart, 0, gnBufferWidth - 1);
    const int32_t nRight = std::clamp(nXEnd, 0, gnBufferWidth - 1);
    if (nLeft == nRight)
    {
        return;
    }

    const int32_t nTop = std::clamp(nYStart, 0, gnBufferHeight - 1);
    const int32_t nBottom = std::clamp(nYEnd, 0, gnBufferHeight - 1);
    if (nTop == nBottom)
    {
        return;
    }

    D2_ASSERT(nBottom > nTop);

    const int32_t nWidth = nRight - nLeft;
    const uint8_t nColor = dwColor & 0xFF;

    uint8_t* pLine = &gpbOffscreenBuffer[nTop * gnBufferWidth + nLeft];
    for (int32_t nLine = nTop; nLine < nBottom; ++nLine)
    {
        switch (eBlendType)
        {
        case BOXBLEND_REMAP:
            for (int32_t i = 0; i < nWidth; ++i)
            {
                pLine[i] = pBlendTable[pLine[i]];
            }
            break;

        case BOXBLEND_COLOR:
            for (int32_t i = 0; i < nWidth; ++i)
            {
                pLine[i] = pBlendTable[(pLine[i] << 8) + nColor];
            }
            break;

        default:
            memset(pLine, nColor, nWidth);
            break;
        }

        pLine += gnBufferWidth;
    }
}

//pfDrawBoxAlpha
// Port of D2Gdi.0x6F8319A0
void __fastcall OGL_DrawBoxAlpha(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha)
{
    if (nAlpha >= 192)
    {
        OGL_DrawBox(nXStart, nYStart, nXEnd, nYEnd, dwColor, DRAWMODE_NORMAL);
    }
    else if (nAlpha >= 128)
    {
        OGL_DrawBox(nXStart, nYStart, nXEnd, nYEnd, dwColor, DRAWMODE_TRANS75);
    }
    else if (nAlpha >= 64)
    {
        OGL_DrawBox(nXStart, nYStart, nXEnd, nYEnd, dwColor, DRAWMODE_TRANS50);
    }
    else if (nAlpha > 0)
    {
        OGL_DrawBox(nXStart, nYStart, nXEnd, nYEnd, dwColor, DRAWMODE_TRANS25);
    }
}

//pfDrawLine
// Port of D2Gdi.0x6F831A10, the alpha is ignored
void __fastcall OGL_DrawLine(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha)
{
    const uint8_t nColor = dwColor & 0xFF;

    auto plot = [nColor](int32_t nX, int32_t nY)
    {
        if (nX >= 0 && nX < gnBufferWidth && nY >= 0 && nY < gnBufferHeight)
        {
            gpbOffscreenBuffer[nY * gnBufferWidth + nX] = nColor;
        }
    };

    int32_t nDeltaX = nXEnd - nXStart;
    int32_t nDeltaY = nYEnd - nYStart;
    const int32_t nStepX = nDeltaX < 0 ? -1 : 1;
    const int32_t nStepY = nDeltaY < 0 ? -1 : 1;
    nDeltaX = std::abs(nDeltaX);
    nDeltaY = std::abs(nDeltaY);

    int32_t nX = nXStart;
    int32_t nY = nYStart;
    plot(nX, nY);

    int32_t nError = 0;
    if (nDeltaX < nDeltaY)
    {
        for (int32_t i = 0; i < nDeltaY; ++i)
        {
            nError += nDeltaX;
            nY += nStepY;
            if (nError > nDeltaY)
            {
                nX += nStepX;
                nError -= nDeltaY;
            }
            plot(nX, nY);
        }
    }
    else
    {
        for (int32_t i = 0; i < nDeltaX; ++i)
        {
            nError += nDeltaY;
            nX += nStepX;
            if (nError > nDeltaX)
            {
                nY += nStepY;
                nError -= nDeltaX;
            }
            plot(nX, nY);
        }
    }
}

//pfClearScreen
// Port of D2Gdi.0x6F832040
void __fastcall OGL_ClearScreen(int32_t bPartial)
{
    if (!gpbOffscreenBuffer)
    {
        return;
    }

    const int32_t nLines = bPartial ? gnBufferHeight - BOTTOM_PANEL_HEIGHT : gnBufferHeight;
    memset(gpbOffscreenBuffer, 0, gnBufferWidth * nLines);
}
