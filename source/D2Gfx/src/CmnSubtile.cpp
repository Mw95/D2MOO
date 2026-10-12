#include "CmnSubtile.h"

#include <algorithm>

#include <D2Math.h>
#include <Fog.h>
#include <Storm.h>

#include "DisplayType.h"
#include "D2Gfx.h"


extern int32_t gnViewMatrixAdjust_6FA8D254;
extern DisplayType gnDisplayType;


constexpr int32_t GOURAUD_SHIFT = 24;
constexpr int32_t VISTILE_SIZE = 32;
constexpr int32_t ISOBLOCK_LINES = 15;

uint8_t** gpTransPalettes_6FA81448;

uint8_t* gpPaletteTable_6FA81460[72];
D2PaletteStrc gShadowLightPalettes_6FA81580[49];

uint8_t* gCmnInfo_pBuffer_6FA8144C;
int32_t gCmnInfo_nPitch_6FA81450;
int32_t gCmnInfo_nHeight_6FA81454;
int32_t gCmnInfo_nUnknown_6FA81458;

// Offset of each line in the back buffer, starting at line -32
int32_t gnLineOffsets_6FA846A8[732];
int32_t gnLineOffsetsPitch_6FA84680;

// Clip rectangle of the spans
int32_t gnClipLeft_6FA8D220;
int32_t gnClipTop_6FA84690;
int32_t gnClipRight_6FA8469C;
int32_t gnClipBottom_6FA8D240;

// Positions of 32x32 vis tiles that are drawn at all / drawn without clipping
int32_t gnVisTileMinX_6FA84688;
int32_t gnVisTileMaxX_6FA85218;
int32_t gnVisTileMinY_6FA8D230;
int32_t gnVisTileMaxY_6FA8D24C;
int32_t gnVisTileUnclippedMinX_6FA846A0;
int32_t gnVisTileUnclippedMaxX_6FA8D234;
int32_t gnVisTileUnclippedMinY_6FA8D238;
int32_t gnVisTileUnclippedMaxY_6FA8D248;

// Positions of 32x15 floor blocks that are drawn at all / drawn without clipping
int32_t gnFloorBlockMinX_6FA8D244;
int32_t gnFloorBlockMaxX_6FA84698;
int32_t gnFloorBlockMinY_6FA8D224;
int32_t gnFloorBlockMaxY_6FA8D23C;
int32_t gnFloorBlockUnclippedMinX_6FA8468C;
int32_t gnFloorBlockUnclippedMaxX_6FA8D22C;
int32_t gnFloorBlockUnclippedMinY_6FA8D228;
int32_t gnFloorBlockUnclippedMaxY_6FA84694;

// Never set in the original dll, so the viewport is recomputed every frame
int32_t gnViewportViewMatrixAdjust_6FA7E040 = -1;

int32_t gbForceFlatLighting_6FA8D250;

// [nLeftIntensity][nRightIntensity][nX]: intensity interpolated over 32 pixels
uint8_t gGouraudCache_6FA85220[32][32][32];


// Returns the line of the gouraud cache interpolating between the two intensities
static inline uint8_t* D2GFX_GetGouraudLine(int32_t nLeftIntensity, int32_t nRightIntensity, uint8_t nIntensityShift)
{
    return &gGouraudCache_6FA85220[0][0][0] + 32 * ((nRightIntensity >> nIntensityShift) + 32 * (nLeftIntensity >> nIntensityShift));
}


// Layout of the lines of a 32x15 isometric diamond
constexpr int32_t gnIsoBlockLineX_6FA7E064[ISOBLOCK_LINES] =
{
    14, 12, 10, 8, 6, 4, 2, 0, 2, 4, 6, 8, 10, 12, 14
};

constexpr int32_t gnIsoBlockLineWidth_6FA7E0A0[ISOBLOCK_LINES] =
{
    4, 8, 12, 16, 20, 24, 28, 32, 28, 24, 20, 16, 12, 8, 4
};

constexpr int32_t gnIsoBlockLineDataOffset_6FA7E0DC[ISOBLOCK_LINES] =
{
    0, 4, 12, 24, 40, 60, 84, 112, 144, 172, 196, 216, 232, 244, 252
};


//D2Gfx.0x6FA71000
void __fastcall D2GFX_InitGouraudCache_6FA71000()
{
    D2GFX_BuildGouraudCache_6FA72570();
    gCmnInfo_pBuffer_6FA8144C = nullptr;
}

//D2Gfx.0x6FA71010
void __fastcall D2GFX_FillYBufferTable_6FA71010(uint8_t* pBuffer, int32_t nPitch, int32_t nHeight, int32_t nUnknown)
{
    gCmnInfo_pBuffer_6FA8144C = pBuffer;
    gCmnInfo_nPitch_6FA81450 = nPitch;
    gCmnInfo_nHeight_6FA81454 = nHeight;
    gCmnInfo_nUnknown_6FA81458 = nUnknown;

    if (nPitch != gnLineOffsetsPitch_6FA84680)
    {
        gCmnInfo_nPitch_6FA81450 = nPitch;
        gnLineOffsetsPitch_6FA84680 = nPitch;
        D2GFX_BuildLineOffsets_6FA72700();
    }

    if (gnViewMatrixAdjust_6FA8D254 != gnViewportViewMatrixAdjust_6FA7E040)
    {
        D2GFX_SetViewport_6FA72630(nPitch, nHeight);
    }
}

//D2Gfx.0x6FA71070
void __fastcall D2GFX_SetPaletteTables_6FA71070(D2PaletteTableStrc* pPaletteTable)
{
    memcpy(gpPaletteTable_6FA81460, pPaletteTable, sizeof(gpPaletteTable_6FA81460));
    gpTransPalettes_6FA81448 = gpPaletteTable_6FA81460;
    for (int32_t i = 0; i < std::size(gShadowLightPalettes_6FA81580); ++i)
    {
        memcpy(&gShadowLightPalettes_6FA81580[i], gpPaletteTable_6FA81460[i + 3], sizeof(D2PaletteStrc));
    }
}

//D2Gfx.0x6FA710C0
int32_t __fastcall D2GFX_SetContrastAndGamma_6FA710C0()
{
    DWORD nContrast = gnDisplayType != DISPLAYTYPE_GLIDE ? 100 : 0;
    SRegLoadValue("Diablo II", "Contrast", 0, &nContrast);
    D2GFX_SetOption(11, nContrast);

    DWORD nGamma = 155;
    SRegLoadValue("Diablo II", "Gamma", 0, &nGamma);
    gGfxSettings.nGamma = nGamma;
    return D2GFX_SetGamma(nGamma);
}

//D2Gfx.0x6FA71130
void __fastcall D2GFX_DrawIsoBlockFlat_6FA71130(uint8_t* pSrc, uint8_t* pDst, uint8_t* pPalette)
{
    for (int32_t nLine = 0; nLine < ISOBLOCK_LINES; ++nLine)
    {
        const uint8_t* pLineSrc = &pSrc[gnIsoBlockLineDataOffset_6FA7E0DC[nLine]];
        uint8_t* pLineDst = &pDst[gnIsoBlockLineX_6FA7E064[nLine]];

        // Unrolled in original dll
        for (int32_t i = gnIsoBlockLineWidth_6FA7E0A0[nLine] - 1; i >= 0; --i)
        {
            pLineDst[i] = pPalette[pLineSrc[i]];
        }

        pDst += gCmnInfo_nPitch_6FA81450;
    }
}

//D2Gfx.0x6FA71340
void __fastcall D2GFX_DrawIsoBlockGouraud_6FA71340(uint8_t* pSrc, uint8_t* pDst, int32_t nLeftIntensity, int32_t nLeftIntensityStep, int32_t nRightIntensity, int32_t nRightIntensityStep)
{
    for (int32_t nLine = 0; nLine < ISOBLOCK_LINES; ++nLine)
    {
        const int32_t nLineX = gnIsoBlockLineX_6FA7E064[nLine];
        const uint8_t* pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, 7) + nLineX;
        const uint8_t* pLineSrc = &pSrc[gnIsoBlockLineDataOffset_6FA7E0DC[nLine]];
        uint8_t* pLineDst = &pDst[nLineX];

        // Unrolled in orginal dll
        for (int32_t i = gnIsoBlockLineWidth_6FA7E0A0[nLine] - 1; i >= 0; --i)
        {
            pLineDst[i] = gShadowLightPalettes_6FA81580[pGouraud[i]].nRemap[pLineSrc[i]];
        }

        pDst += gCmnInfo_nPitch_6FA81450;
        nLeftIntensity += nLeftIntensityStep;
        nRightIntensity += nRightIntensityStep;
    }
}

//D2Gfx.0x6FA71720
void __fastcall D2GFX_DrawRleFlat_6FA71720(uint8_t* pSrc, uint8_t* pDst, uint8_t* pPalette, int32_t nLines)
{
    uint8_t* pSpanDst = pDst;
    while (nLines)
    {
        const uint8_t nSkip = pSrc[0];
        const uint8_t nLength = pSrc[1];
        pSrc += 2;

        if (nSkip || nLength)
        {
            pSpanDst += nSkip;

            // Unrolled in original dll
            for (int32_t i = nLength - 1; i >= 0; --i)
            {
                pSpanDst[i] = pPalette[pSrc[i]];
            }

            pSpanDst += nLength;
            pSrc += nLength;
        }
        else
        {
            pDst += gCmnInfo_nPitch_6FA81450;
            --nLines;
            pSpanDst = pDst;
        }
    }
}

//D2Gfx.0x6FA71970
void __fastcall D2GFX_DrawRleGouraud_6FA71970(uint8_t* pSrc, uint8_t* pDst, int32_t nLeftIntensity, int32_t nLeftIntensityStep, int32_t nRightIntensity, int32_t nRightIntensityStep, int32_t nLines, uint8_t nIntensityShift)
{
    uint8_t* pSpanDst = pDst;
    uint8_t* pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, nIntensityShift);

    while (nLines)
    {
        const uint8_t nSkip = pSrc[0];
        const uint8_t nLength = pSrc[1];
        pSrc += 2;

        if (nSkip || nLength)
        {
            pSpanDst += nSkip;
            pGouraud += nSkip;

            // Unrolled in original dll
            for (int32_t i = nLength - 1; i >= 0; --i)
            {
                pSpanDst[i] = gShadowLightPalettes_6FA81580[pGouraud[i]].nRemap[pSrc[i]];
            }

            pSpanDst += nLength;
            pSrc += nLength;
            pGouraud += nLength;
        }
        else
        {
            --nLines;
            nLeftIntensity += nLeftIntensityStep;
            nRightIntensity += nRightIntensityStep;
            pDst += gCmnInfo_nPitch_6FA81450;
            pSpanDst = pDst;
            pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, nIntensityShift);
        }
    }
}

//D2Gfx.0x6FA71D90
void __fastcall D2GFX_DrawRleFlatClipped_6FA71D90(int32_t nX, int32_t nY, uint8_t* pSrc, uint8_t* pDst, uint8_t* pPalette, int32_t nLines)
{
    uint8_t* pSpanDst = pDst;

    int32_t nLine = 0;
    while (nLine < nLines)
    {
        const uint8_t nSkip = pSrc[0];
        const uint8_t nLength = pSrc[1];
        pSrc += 2;

        if (nSkip || nLength)
        {
            if (nY >= gnClipBottom_6FA8D240)
            {
                return;
            }

            pSpanDst += nSkip;

            if (nY >= gnClipTop_6FA84690)
            {
                const int32_t nSpanX = nX + (int32_t)(pSpanDst - pDst);
                const int32_t nStart = std::max(gnClipLeft_6FA8D220 - nSpanX, 0);
                const int32_t nEnd = std::min(std::max(gnClipRight_6FA8469C - nSpanX, 0), (int32_t)nLength);

                // Unrolled in original dll
                for (int32_t i = nEnd - 1; i >= nStart; --i)
                {
                    pSpanDst[i] = pPalette[pSrc[i]];
                }
            }

            pSpanDst += nLength;
            pSrc += nLength;
        }
        else
        {
            ++nLine;
            ++nY;
            pDst += gCmnInfo_nPitch_6FA81450;
            pSpanDst = pDst;
        }
    }
}

//D2Gfx.0x6FA72090
void __fastcall D2GFX_DrawRleGouraudClipped_6FA72090(int32_t nX, int32_t nY, uint8_t* pSrc, uint8_t* pDst, int32_t nLeftIntensity, int32_t nLeftIntensityStep, int32_t nRightIntensity, int32_t nRightIntensityStep, int32_t nLines, uint8_t nIntensityShift)
{
    uint8_t* pSpanDst = pDst;
    uint8_t* pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, nIntensityShift);

    int32_t nLine = 0;
    while (nLine < nLines)
    {
        const uint8_t nSkip = pSrc[0];
        const uint8_t nLength = pSrc[1];
        pSrc += 2;

        if (nSkip || nLength)
        {
            if (nY >= gnClipBottom_6FA8D240)
            {
                return;
            }

            pSpanDst += nSkip;
            pGouraud += nSkip;

            if (nY >= gnClipTop_6FA84690)
            {
                const int32_t nSpanX = nX + (int32_t)(pSpanDst - pDst);
                const int32_t nStart = std::max(gnClipLeft_6FA8D220 - nSpanX, 0);
                const int32_t nEnd = std::min(std::max(gnClipRight_6FA8469C - nSpanX, 0), (int32_t)nLength);

                // Unrolled in original dll. Note: the gouraud line is not offset by nStart in the original dll
                for (int32_t i = nEnd - 1; i >= nStart; --i)
                {
                    pSpanDst[i] = gShadowLightPalettes_6FA81580[pGouraud[i - nStart]].nRemap[pSrc[i]];
                }
            }

            pSpanDst += nLength;
            pGouraud += nLength;
            pSrc += nLength;
        }
        else
        {
            ++nLine;
            ++nY;
            pDst += gCmnInfo_nPitch_6FA81450;
            pSpanDst = pDst;
            nLeftIntensity += nLeftIntensityStep;
            nRightIntensity += nRightIntensityStep;
            pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, nIntensityShift);
        }
    }
}

//D2Gfx.0x6FA72570
void __fastcall D2GFX_BuildGouraudCache_6FA72570()
{
    // Fixed point intensities with GOURAUD_SHIFT bits of fraction
    int32_t nFirstRightDelta = 0;
    for (int32_t nLeftIntensity = 0; nLeftIntensity < 32; ++nLeftIntensity)
    {
        const int32_t nStartValue = nLeftIntensity << GOURAUD_SHIFT;
        int32_t nDelta = nFirstRightDelta; // (nRightIntensity - nLeftIntensity) << GOURAUD_SHIFT
        for (int32_t nRightIntensity = 0; nRightIntensity < 32; ++nRightIntensity)
        {
            int32_t nVal = nStartValue;
            for (int32_t nX = 0; nX < 32; ++nX)
            {
                nVal = D2Clamp(nVal, 0, 0x1F000000);
                gGouraudCache_6FA85220[nLeftIntensity][nRightIntensity][nX] = (nVal >> GOURAUD_SHIFT) & 0xFF;
                nVal += nDelta >> 5;
            }

            D2_ASSERT((nVal >> GOURAUD_SHIFT) == nRightIntensity);

            nDelta += (1 << GOURAUD_SHIFT);
        }

        nFirstRightDelta -= (1 << GOURAUD_SHIFT);
    }
}

//D2Gfx.0x6FA72630
void __fastcall D2GFX_SetViewport_6FA72630(int32_t nWidth, int32_t nHeight)
{
    int32_t nLeft = 0;
    if (gnViewMatrixAdjust_6FA8D254 == 1)
    {
        nWidth -= nWidth / 2;
    }
    else if (gnViewMatrixAdjust_6FA8D254 == 2)
    {
        nLeft = nWidth / 2;
    }

    gnFloorBlockMinX_6FA8D244 = nLeft - 32;
    gnFloorBlockUnclippedMaxY_6FA84694 = nHeight - 63;
    gnVisTileMinX_6FA84688 = nLeft - 32;
    gnFloorBlockMaxY_6FA8D23C = nHeight - 47;
    gnVisTileMaxY_6FA8D24C = nHeight - 47;
    gnClipBottom_6FA8D240 = nHeight - 47;
    gnFloorBlockUnclippedMinX_6FA8468C = nLeft;
    gnVisTileUnclippedMinX_6FA846A0 = nLeft;
    gnClipLeft_6FA8D220 = nLeft;
    gnFloorBlockMinY_6FA8D224 = -16;
    gnFloorBlockMaxX_6FA84698 = nWidth;
    gnFloorBlockUnclippedMinY_6FA8D228 = 0;
    gnFloorBlockUnclippedMaxX_6FA8D22C = nWidth - 32;
    gnVisTileMinY_6FA8D230 = -32;
    gnVisTileMaxX_6FA85218 = nWidth;
    gnVisTileUnclippedMinY_6FA8D238 = 0;
    gnVisTileUnclippedMaxY_6FA8D248 = nHeight - 79;
    gnVisTileUnclippedMaxX_6FA8D234 = nWidth - 32;
    gnClipTop_6FA84690 = 0;
    gnClipRight_6FA8469C = nWidth;
}

//D2Gfx.0x6FA72700
void __fastcall D2GFX_BuildLineOffsets_6FA72700()
{
    int32_t nOffset = -32 * gCmnInfo_nPitch_6FA81450;
    for (int32_t i = 0; i < std::size(gnLineOffsets_6FA846A8); ++i)
    {
        gnLineOffsets_6FA846A8[i] = nOffset;
        nOffset += gCmnInfo_nPitch_6FA81450;
    }
}

//D2Gfx.0x6FA72730
void __fastcall D2GFX_DrawVisTile_6FA72730(uint8_t* pSrc, int32_t nX, int32_t nY)
{
    if (nY < gnVisTileMinY_6FA8D230 || nY >= gnVisTileMaxY_6FA8D24C || nX < gnVisTileMinX_6FA84688 || nX >= gnVisTileMaxX_6FA85218)
    {
        return;
    }

    D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

    uint8_t* pLine = &gCmnInfo_pBuffer_6FA8144C[gnLineOffsets_6FA846A8[nY + 32]] + nX;
    uint8_t* pDst = pLine;

    if (nY < gnVisTileUnclippedMinY_6FA8D238 || nY >= gnVisTileUnclippedMaxY_6FA8D248 || nX < gnVisTileUnclippedMinX_6FA846A0 || nX >= gnVisTileUnclippedMaxX_6FA8D234)
    {
        int32_t nCurrentY = nY;
        int32_t nLine = 0;
        while (nLine < VISTILE_SIZE)
        {
            const uint8_t nSkip = pSrc[0];
            const uint8_t nLength = pSrc[1];
            pSrc += 2;

            if (nSkip || nLength)
            {
                if (nCurrentY >= gnClipBottom_6FA8D240)
                {
                    return;
                }

                pDst += nSkip;

                if (nCurrentY >= gnClipTop_6FA84690)
                {
                    const int32_t nPosX = nX + (int32_t)(pDst - pLine);
                    const int32_t nStart = std::max(gnClipLeft_6FA8D220 - nPosX, 0);
                    const int32_t nEnd = std::min(std::max(gnClipRight_6FA8469C - nPosX, 0), (int32_t)nLength);
                    if (nEnd - nStart > 0)
                    {
                        memcpy(&pDst[nStart], &pSrc[nStart], nEnd - nStart);
                    }
                }

                pDst += nLength;
                pSrc += nLength;
            }
            else
            {
                ++nLine;
                ++nCurrentY;
                pLine += gCmnInfo_nPitch_6FA81450;
                pDst = pLine;
            }
        }
    }
    else
    {
        int32_t nLines = VISTILE_SIZE;
        while (nLines)
        {
            const uint8_t nSkip = pSrc[0];
            const uint8_t nLength = pSrc[1];
            pSrc += 2;

            if (nSkip || nLength)
            {
                pDst += nSkip;
                memcpy(pDst, pSrc, nLength);
                pDst += nLength;
                pSrc += nLength;
            }
            else
            {
                --nLines;
                pLine += gCmnInfo_nPitch_6FA81450;
                pDst = pLine;
            }
        }
    }
}

//D2Gfx.0x6FA72900
void __fastcall D2GFX_DrawFlatLitVisTile_6FA72900(uint8_t* pSrc, int32_t nX, int32_t nY, uint8_t nIntensity)
{
    if (nY < gnVisTileMinY_6FA8D230 || nY >= gnVisTileMaxY_6FA8D24C || nX < gnVisTileMinX_6FA84688 || nX >= gnVisTileMaxX_6FA85218)
    {
        return;
    }

    uint8_t* pDst = &gCmnInfo_pBuffer_6FA8144C[gnLineOffsets_6FA846A8[nY + 32]] + nX;

    D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

    uint8_t* pPalette = gShadowLightPalettes_6FA81580[nIntensity >> 3].nRemap;
    if (nY < gnVisTileUnclippedMinY_6FA8D238 || nY >= gnVisTileUnclippedMaxY_6FA8D248 || nX < gnVisTileUnclippedMinX_6FA846A0 || nX >= gnVisTileUnclippedMaxX_6FA8D234)
    {
        D2GFX_DrawRleFlatClipped_6FA71D90(nX, nY, pSrc, pDst, pPalette, VISTILE_SIZE);
    }
    else
    {
        D2GFX_DrawRleFlat_6FA71720(pSrc, pDst, pPalette, VISTILE_SIZE);
    }
}

//D2Gfx.0x6FA729D0
void __fastcall TILE_TileDrawLit_6FA729D0(uint8_t* pSrc, int32_t nX, int32_t nY, int32_t* pIntensities)
{
    if (gbForceFlatLighting_6FA8D250)
    {
        if ((*(uint8_t*)pIntensities & 0xF8) == 0xF8)
        {
            D2GFX_DrawVisTile_6FA72730(pSrc, nX, nY);
        }
        else
        {
            D2GFX_DrawFlatLitVisTile_6FA72900(pSrc, nX, nY, *(uint8_t*)pIntensities);
        }
    }
    else
    {
        const int32_t nLeftIntensity = 32 * pIntensities[0];
        const int32_t nLeftIntensityStep = pIntensities[3] - pIntensities[0];
        const int32_t nRightIntensityStep = pIntensities[2] - pIntensities[1];
        const int32_t nRightIntensity = 32 * pIntensities[1];

        if (gGfxSettings.bLowQuality || std::abs(pIntensities[1] - pIntensities[0]) + std::abs(nLeftIntensityStep) + std::abs(nRightIntensityStep) < 10)
        {
            if ((nLeftIntensity & 0xFFFFFF00) == 0x1F00)
            {
                // Full intensity
                D2GFX_DrawVisTile_6FA72730(pSrc, nX, nY);
            }
            else
            {
                D2GFX_DrawFlatLitVisTile_6FA72900(pSrc, nX, nY, *(uint8_t*)pIntensities);
            }
        }
        else
        {
            if (nY >= gnVisTileMinY_6FA8D230 && nY < gnVisTileMaxY_6FA8D24C && nX >= gnVisTileMinX_6FA84688 && nX < gnVisTileMaxX_6FA85218)
            {
                D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

                uint8_t* pDst = &gCmnInfo_pBuffer_6FA8144C[gnLineOffsets_6FA846A8[nY + 32]] + nX;
                if (nY < gnVisTileUnclippedMinY_6FA8D238 || nY >= gnVisTileUnclippedMaxY_6FA8D248 || nX < gnVisTileUnclippedMinX_6FA846A0 || nX >= gnVisTileUnclippedMaxX_6FA8D234)
                {
                    D2GFX_DrawRleGouraudClipped_6FA72090(nX, nY, pSrc, pDst, nLeftIntensity, nLeftIntensityStep, nRightIntensity, nRightIntensityStep, VISTILE_SIZE, 8);
                }
                else
                {
                    D2GFX_DrawRleGouraud_6FA71970(pSrc, pDst, nLeftIntensity, nLeftIntensityStep, nRightIntensity, nRightIntensityStep, VISTILE_SIZE, 8);
                }
            }
        }
    }
}

//D2Gfx.0x6FA72B80
void __fastcall D2GFX_DrawBlendedVisTile_6FA72B80(uint8_t* pSrc, int32_t nX, int32_t nY, uint8_t nAlpha)
{
    uint8_t* pBlendTable = nullptr;
    if (nAlpha >= 192)
    {
        pBlendTable = gpTransPalettes_6FA81448[0];
    }
    else if (nAlpha >= 128)
    {
        pBlendTable = gpTransPalettes_6FA81448[1];
    }
    else if (nAlpha >= 64)
    {
        pBlendTable = gpTransPalettes_6FA81448[2];
    }
    else
    {
        return;
    }

    if (nY < gnVisTileMinY_6FA8D230 || nY >= gnVisTileMaxY_6FA8D24C || nX < gnVisTileMinX_6FA84688 || nX >= gnVisTileMaxX_6FA85218)
    {
        return;
    }

    D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

    uint8_t* pLine = &gCmnInfo_pBuffer_6FA8144C[gnLineOffsets_6FA846A8[nY + 32]] + nX;
    uint8_t* pDst = pLine;

    if (nY < gnVisTileUnclippedMinY_6FA8D238 || nY >= gnVisTileUnclippedMaxY_6FA8D248 || nX < gnVisTileUnclippedMinX_6FA846A0 || nX >= gnVisTileUnclippedMaxX_6FA8D234)
    {
        int32_t nCurrentY = nY;
        int32_t nLine = 0;
        while (nLine < VISTILE_SIZE)
        {
            const uint8_t nSkip = pSrc[0];
            const uint8_t nLength = pSrc[1];
            pSrc += 2;

            if (nSkip || nLength)
            {
                if (nCurrentY >= gnClipBottom_6FA8D240)
                {
                    return;
                }

                pDst += nSkip;

                if (nCurrentY >= gnClipTop_6FA84690)
                {
                    const int32_t nPosX = nX + (int32_t)(pDst - pLine);
                    const int32_t nStart = std::max(gnClipLeft_6FA8D220 - nPosX, 0);
                    const int32_t nEnd = std::min(std::max(gnClipRight_6FA8469C - nPosX, 0), (int32_t)nLength);
                    for (int32_t i = nStart; i < nEnd; ++i)
                    {
                        pDst[i] = pBlendTable[(pDst[i] << 8) + pSrc[i]];
                    }
                }

                pDst += nLength;
                pSrc += nLength;
            }
            else
            {
                ++nLine;
                ++nCurrentY;
                pLine += gCmnInfo_nPitch_6FA81450;
                pDst = pLine;
            }
        }
    }
    else
    {
        int32_t nLines = VISTILE_SIZE;
        while (nLines)
        {
            const uint8_t nSkip = pSrc[0];
            const uint8_t nLength = pSrc[1];
            pSrc += 2;

            if (nSkip || nLength)
            {
                pDst += nSkip;
                for (int32_t i = 0; i < nLength; ++i)
                {
                    pDst[i] = pBlendTable[(pDst[i] << 8) + pSrc[i]];
                }
                pDst += nLength;
                pSrc += nLength;
            }
            else
            {
                --nLines;
                pLine += gCmnInfo_nPitch_6FA81450;
                pDst = pLine;
            }
        }
    }
}

//D2Gfx.0x6FA72DC0
void __fastcall D2GFX_DrawRoofTile_6FA72DC0(uint8_t* pSrc, int32_t nX, int32_t nY, int32_t* pIntensities, uint8_t nAlpha)
{
    uint8_t* pBlendTable = nullptr;
    if (nAlpha >= 192)
    {
        pBlendTable = gpTransPalettes_6FA81448[0];
    }
    else if (nAlpha >= 128)
    {
        pBlendTable = gpTransPalettes_6FA81448[1];
    }
    else if (nAlpha >= 64)
    {
        pBlendTable = gpTransPalettes_6FA81448[2];
    }
    else
    {
        return;
    }

    const int32_t nLeftIntensityStep = pIntensities[3] - pIntensities[0];
    const int32_t nRightIntensityStep = pIntensities[2] - pIntensities[1];
    int32_t nLeftIntensity = 32 * pIntensities[0];
    int32_t nRightIntensity = 32 * pIntensities[1];

    if (nY < gnVisTileMinY_6FA8D230 || nY >= gnVisTileMaxY_6FA8D24C || nX < gnVisTileMinX_6FA84688 || nX >= gnVisTileMaxX_6FA85218)
    {
        return;
    }

    D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

    uint8_t* pLine = &gCmnInfo_pBuffer_6FA8144C[gnLineOffsets_6FA846A8[nY + 32]] + nX;
    uint8_t* pDst = pLine;
    uint8_t* pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, 8);

    if (nY < gnVisTileUnclippedMinY_6FA8D238 || nY >= gnVisTileUnclippedMaxY_6FA8D248 || nX < gnVisTileUnclippedMinX_6FA846A0 || nX >= gnVisTileUnclippedMaxX_6FA8D234)
    {
        int32_t nCurrentY = nY;
        int32_t nLine = 0;
        while (nLine < VISTILE_SIZE)
        {
            const uint8_t nSkip = pSrc[0];
            const uint8_t nLength = pSrc[1];
            pSrc += 2;

            if (nSkip || nLength)
            {
                if (nCurrentY >= gnClipBottom_6FA8D240)
                {
                    return;
                }

                pDst += nSkip;
                pGouraud += nSkip;

                if (nCurrentY >= gnClipTop_6FA84690)
                {
                    const int32_t nPosX = nX + (int32_t)(pDst - pLine);
                    const int32_t nStart = std::max(gnClipLeft_6FA8D220 - nPosX, 0);
                    const int32_t nEnd = std::min(std::max(gnClipRight_6FA8469C - nPosX, 0), (int32_t)nLength);
                    // Note: the gouraud row is not offset by nStart in the original dll
                    for (int32_t i = nStart; i < nEnd; ++i)
                    {
                        const uint8_t nLitColor = gShadowLightPalettes_6FA81580[pGouraud[i - nStart]].nRemap[pSrc[i]];
                        pDst[i] = pBlendTable[(nLitColor << 8) + pDst[i]];
                    }
                }

                pDst += nLength;
                pGouraud += nLength;
                pSrc += nLength;
            }
            else
            {
                ++nLine;
                ++nCurrentY;
                pLine += gCmnInfo_nPitch_6FA81450;
                pDst = pLine;
                nLeftIntensity += nLeftIntensityStep;
                nRightIntensity += nRightIntensityStep;
                pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, 8);
            }
        }
    }
    else
    {
        int32_t nLines = VISTILE_SIZE;
        while (nLines)
        {
            const uint8_t nSkip = pSrc[0];
            const uint8_t nLength = pSrc[1];
            pSrc += 2;

            if (nSkip || nLength)
            {
                pDst += nSkip;
                pGouraud += nSkip;
                for (int32_t i = 0; i < nLength; ++i)
                {
                    const uint8_t nLitColor = gShadowLightPalettes_6FA81580[pGouraud[i]].nRemap[pSrc[i]];
                    pDst[i] = pBlendTable[(nLitColor << 8) + pDst[i]];
                }
                pDst += nLength;
                pGouraud += nLength;
                pSrc += nLength;
            }
            else
            {
                --nLines;
                pLine += gCmnInfo_nPitch_6FA81450;
                pDst = pLine;
                nLeftIntensity += nLeftIntensityStep;
                nRightIntensity += nRightIntensityStep;
                pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, 8);
            }
        }
    }
}

//D2Gfx.0x6FA73130
void __fastcall D2GFX_DrawFloorBlockFlatClipped_6FA73130(D2TileLibraryBlockStrc* pBlock, int32_t nX, int32_t nY, uint8_t* pDst, uint8_t nIntensity)
{
    uint8_t* pPalette = gShadowLightPalettes_6FA81580[nIntensity >> 3].nRemap;

    if (pBlock->nFormat & TILEBLOCKFORMAT_RLE)
    {
        D2GFX_DrawRleFlatClipped_6FA71D90(nX, nY, pBlock->dwOffset_pData, pDst, pPalette, ISOBLOCK_LINES);
    }
    else
    {
        const int32_t nLastLine = std::min(gnClipBottom_6FA8D240 - nY, ISOBLOCK_LINES);
        for (int32_t nLine = std::max(gnClipTop_6FA84690 - nY, 0); nLine < nLastLine; ++nLine)
        {
            const int32_t nLineX = nX + gnIsoBlockLineX_6FA7E064[nLine];
            const int32_t nStart = std::max(gnClipLeft_6FA8D220 - nLineX, 0);
            const int32_t nCount = D2Clamp(gnClipRight_6FA8469C - nLineX, 0, gnIsoBlockLineWidth_6FA7E0A0[nLine]) - nStart;
            if (nCount > 0)
            {
                uint8_t* pLineDst = &pDst[nLine * gCmnInfo_nPitch_6FA81450 + gnIsoBlockLineX_6FA7E064[nLine] + nStart];
                const uint8_t* pLineSrc = &pBlock->dwOffset_pData[gnIsoBlockLineDataOffset_6FA7E0DC[nLine] + nStart];
                for (int32_t i = 0; i < nCount; ++i)
                {
                    pLineDst[i] = pPalette[pLineSrc[i]];
                }
            }
        }
    }
}

//D2Gfx.0x6FA73270
void __fastcall D2GFX_DrawFloorBlockGouraudClipped_6FA73270(D2TileLibraryBlockStrc* pBlock, int32_t nX, int32_t nY, uint8_t* pDst, int32_t* pIntensities)
{
    const int32_t nLeftIntensityStep = pIntensities[3] - pIntensities[0];
    const int32_t nRightIntensityStep = pIntensities[2] - pIntensities[1];
    int32_t nLeftIntensity = 16 * pIntensities[0];
    int32_t nRightIntensity = 16 * pIntensities[1];

    if (pBlock->nFormat & TILEBLOCKFORMAT_RLE)
    {
        D2GFX_DrawRleGouraudClipped_6FA72090(nX, nY, pBlock->dwOffset_pData, pDst, nLeftIntensity, nLeftIntensityStep, nRightIntensity, nRightIntensityStep, ISOBLOCK_LINES, 7);
    }
    else
    {
        // Note: the intensities are only interpolated for the visible lines in the original dll
        const int32_t nLastLine = std::min(gnClipBottom_6FA8D240 - nY, ISOBLOCK_LINES);
        for (int32_t nLine = std::max(gnClipTop_6FA84690 - nY, 0); nLine < nLastLine; ++nLine)
        {
            const int32_t nLineX = nX + gnIsoBlockLineX_6FA7E064[nLine];
            const int32_t nStart = std::max(gnClipLeft_6FA8D220 - nLineX, 0);
            const int32_t nCount = D2Clamp(gnClipRight_6FA8469C - nLineX, 0, gnIsoBlockLineWidth_6FA7E0A0[nLine]) - nStart;
            if (nCount > 0)
            {
                // Note: the gouraud line is not offset by nStart in the original dll
                const uint8_t* pGouraud = D2GFX_GetGouraudLine(nLeftIntensity, nRightIntensity, 7) + gnIsoBlockLineX_6FA7E064[nLine];
                uint8_t* pLineDst = &pDst[nLine * gCmnInfo_nPitch_6FA81450 + gnIsoBlockLineX_6FA7E064[nLine] + nStart];
                const uint8_t* pLineSrc = &pBlock->dwOffset_pData[gnIsoBlockLineDataOffset_6FA7E0DC[nLine] + nStart];
                for (int32_t i = 0; i < nCount; ++i)
                {
                    pLineDst[i] = gShadowLightPalettes_6FA81580[pGouraud[i]].nRemap[pLineSrc[i]];
                }
            }

            nLeftIntensity += nLeftIntensityStep;
            nRightIntensity += nRightIntensityStep;
        }
    }
}

//D2Gfx.0x6FA73410
void __fastcall D2GFX_FloorTileDraw_6FA73410(D2TileLibraryEntryStrc* pTileLibraryEntry, int32_t nX, int32_t nY, D2GfxLightExStrc* pLightEx)
{
    D2GfxTileLibraryEntryStrc* pTile = (D2GfxTileLibraryEntryStrc*)pTileLibraryEntry;
    uint8_t* pTileBuffer = gCmnInfo_pBuffer_6FA8144C + nY * gCmnInfo_nPitch_6FA81450 + nX;

    for (int32_t i = 0; i < pTile->nBlocks; ++i)
    {
        D2TileLibraryBlockStrc* pBlock = &pTile->pBlocks[i];
        uint8_t* pDst = pTileBuffer + pBlock->nPosY * gCmnInfo_nPitch_6FA81450 + pBlock->nPosX;

        if (!(pBlock->nFormat & TILEBLOCKFORMAT_VISIBLE))
        {
            continue;
        }

        const int32_t nBlockX = nX + pBlock->nPosX;
        const int32_t nBlockY = nY + pBlock->nPosY;
        if (nBlockY < gnFloorBlockMinY_6FA8D224 || nBlockY >= gnFloorBlockMaxY_6FA8D23C || nBlockX < gnFloorBlockMinX_6FA8D244 || nBlockX >= gnFloorBlockMaxX_6FA84698)
        {
            continue;
        }

        // Light grid around the block, 8 entries per row
        const D2GfxLightExStrc* pLight = &pLightEx[pBlock->nGridX + 8 * pBlock->nGridY];

        int32_t bFlatLight = 0;
        uint8_t nIntensity = 0;
        int32_t pIntensities[4];

        if (gbForceFlatLighting_6FA8D250)
        {
            bFlatLight = 1;
            nIntensity = pLight[9].nIntensity;
        }
        else
        {
            const int32_t nCenterIntensity = pLight[9].nIntensity;
            const int32_t nRightIntensity = pLight[10].nIntensity;
            const int32_t nBottomIntensity = pLight[17].nIntensity;
            const int32_t nBottomRightIntensity = pLight[18].nIntensity;

            if (gGfxSettings.bLowQuality
                || std::abs(nRightIntensity - nCenterIntensity) + std::abs(nBottomIntensity - nCenterIntensity) + std::abs(nBottomRightIntensity - nRightIntensity) < 10)
            {
                bFlatLight = 1;
                nIntensity = nCenterIntensity;
            }
            else
            {
                // Average the intensity at each corner of the block
                pIntensities[0] = (pLight[8].nIntensity + nCenterIntensity + pLight[16].nIntensity + nBottomIntensity) >> 2;
                pIntensities[1] = (pLight[1].nIntensity + pLight[2].nIntensity + nCenterIntensity + nRightIntensity) >> 2;
                pIntensities[2] = (nRightIntensity + pLight[11].nIntensity + nBottomIntensity + pLight[19].nIntensity) >> 2;
                pIntensities[3] = (nBottomIntensity + nBottomRightIntensity + pLight[25].nIntensity + pLight[26].nIntensity) >> 2;
            }
        }

        if (nBlockY >= gnFloorBlockUnclippedMinY_6FA8D228 && nBlockY < gnFloorBlockUnclippedMaxY_6FA84694 && nBlockX >= gnFloorBlockUnclippedMinX_6FA8468C && nBlockX < gnFloorBlockUnclippedMaxX_6FA8D22C)
        {
            if (bFlatLight)
            {
                uint8_t* pPalette = gShadowLightPalettes_6FA81580[nIntensity >> 3].nRemap;
                if (pBlock->nFormat & TILEBLOCKFORMAT_RLE)
                {
                    D2GFX_DrawRleFlat_6FA71720(pBlock->dwOffset_pData, pDst, pPalette, ISOBLOCK_LINES);
                }
                else
                {
                    D2GFX_DrawIsoBlockFlat_6FA71130(pBlock->dwOffset_pData, pDst, pPalette);
                }
            }
            else
            {
                if (pBlock->nFormat & TILEBLOCKFORMAT_RLE)
                {
                    D2GFX_DrawRleGouraud_6FA71970(pBlock->dwOffset_pData, pDst, 16 * pIntensities[0], pIntensities[3] - pIntensities[0], 16 * pIntensities[1], pIntensities[2] - pIntensities[1], ISOBLOCK_LINES, 7);
                }
                else
                {
                    D2GFX_DrawIsoBlockGouraud_6FA71340(pBlock->dwOffset_pData, pDst, 16 * pIntensities[0], pIntensities[3] - pIntensities[0], 16 * pIntensities[1], pIntensities[2] - pIntensities[1]);
                }
            }
        }
        else
        {
            if (bFlatLight)
            {
                D2GFX_DrawFloorBlockFlatClipped_6FA73130(pBlock, nBlockX, nBlockY, pDst, nIntensity);
            }
            else
            {
                D2GFX_DrawFloorBlockGouraudClipped_6FA73270(pBlock, nBlockX, nBlockY, pDst, pIntensities);
            }
        }
    }
}
