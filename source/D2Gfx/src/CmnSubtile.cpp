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

uint8_t** dword_6FA81448;

uint8_t* gpPaletteTable_6FA81460[72];
D2PaletteStrc stru_6FA81580[49];

uint8_t* gCmnInfo_pBuffer_6FA8144C;
int32_t dword_6FA8D244;
int32_t dword_6FA84694;
int32_t dword_6FA84688;
int32_t dword_6FA8D23C;
int32_t dword_6FA8D24C;
int32_t dword_6FA8D240;
int32_t dword_6FA8468C;
int32_t dword_6FA846A0;
int32_t dword_6FA8D220;
int32_t dword_6FA8D224;
int32_t dword_6FA84698;
int32_t dword_6FA846A8[732];
int32_t dword_6FA8D228;
int32_t dword_6FA8D22C;
int32_t dword_6FA8D230;
int32_t dword_6FA85218;
int32_t dword_6FA8D238;
int32_t dword_6FA8D248;
int32_t dword_6FA8D234;
int32_t dword_6FA84690;
int32_t dword_6FA8469C;

int32_t dword_6FA8D250;

int32_t dword_6FA81450;
int32_t dword_6FA81454;
int32_t dword_6FA81458;

int32_t dword_6FA84680;
int32_t dword_6FA7E040 = -1;

uint8_t byte_6FA85220[32][32][32];


// Returns the row of the gouraud cache used to interpolate between two intensities
static inline uint8_t* CMNSUBTILE_GetGouraudRow(int32_t nIntensity1, int32_t nIntensity2, uint8_t nShift)
{
    return &byte_6FA85220[0][0][0] + 32 * ((nIntensity2 >> nShift) + 32 * (nIntensity1 >> nShift));
}


// TODO: Names
constexpr int32_t dword_6FA7E064[] =
{
    14, 12, 10, 8, 6, 4, 2, 0, 2, 4, 6, 8, 10, 12, 14
};

constexpr int32_t dword_6FA7E0A0[] =
{
    4, 8, 12, 16, 20, 24, 28, 32, 28, 24, 20, 16, 12, 8, 4
};

constexpr int32_t dword_6FA7E0DC[] =
{
    0, 4, 12, 24, 40, 60, 84, 112, 144, 172, 196, 216, 232, 244, 252
};



//D2Gfx.0x6FA71000
void __fastcall D2GFX_InitGouraudCache_6FA71000()
{
    DGFX_InitGouraudCache_6FA72570();
    gCmnInfo_pBuffer_6FA8144C = nullptr;
}

//D2Gfx.0x6FA71010
void __fastcall D2GFX_FillYBufferTable_6FA71010(uint8_t* a1, int32_t a2, int32_t a3, int32_t a4)
{
    gCmnInfo_pBuffer_6FA8144C = a1;
    dword_6FA81450 = a2;
    dword_6FA81454 = a3;
    dword_6FA81458 = a4;

    if (a2 != dword_6FA84680)
    {
        dword_6FA81450 = a2;
        dword_6FA84680 = a2;
        sub_6FA72700();
    }

    if (gnViewMatrixAdjust_6FA8D254 != dword_6FA7E040)
    {
        sub_6FA72630(a2, a3);
    }
}

//D2Gfx.0x6FA71070
void __fastcall sub_6FA71070(D2PaletteTableStrc* pPaletteTable)
{
    memcpy(gpPaletteTable_6FA81460, pPaletteTable, sizeof(gpPaletteTable_6FA81460));
    dword_6FA81448 = gpPaletteTable_6FA81460;
    for (int32_t i = 0; i < std::size(stru_6FA81580); ++i)
    {
        memcpy(&stru_6FA81580[i], gpPaletteTable_6FA81460[i + 3], sizeof(D2PaletteStrc));
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
void __fastcall sub_6FA71130(uint8_t* a1, uint8_t* a2, uint8_t* a3)
{
    for (int32_t i = 0; i < std::size(dword_6FA7E064); ++i)
    {
        const uint8_t* pSrc = &a1[dword_6FA7E0DC[i]];
        uint8_t* pDst = &a2[dword_6FA7E064[i]];

        // Unrolled in original dll
        for (int32_t j = dword_6FA7E0A0[i] - 1; j >= 0; --j)
        {
            pDst[j] = a3[pSrc[j]];
        }

        a2 += dword_6FA81450;
    }
}

//D2Gfx.0x6FA71340
void __fastcall sub_6FA71340(uint8_t* a1, uint8_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6)
{
    uint8_t* v6 = a2;

    for (int32_t i = 0; i < std::size(dword_6FA7E064); ++i)
    {
        const int32_t v8 = dword_6FA7E064[i];
        uint8_t* v9 = CMNSUBTILE_GetGouraudRow(a3, a5, 7) + v8;
        uint8_t* v10 = &a1[dword_6FA7E0DC[i]];

        // Unrolled in orginal dll
        const int nValues = dword_6FA7E0A0[i];
        for (int j = nValues-1; j >= 0; j--)
        {
            v6[v8 + j] = stru_6FA81580[v9[j]].unk0x00[v10[j]];
        }

        v6 += dword_6FA81450;
        a3 += a4;
        a5 += a6;
    }
}

//D2Gfx.0x6FA71720
void __fastcall sub_6FA71720(uint8_t* a1, uint8_t* a2, uint8_t* a3, int32_t a4)
{
    // TODO: Names
    uint8_t* v4 = a2;
    while (a4)
    {
        uint8_t v7 = a1[0];
        uint8_t v8 = a1[1];

        a1 += 2;

        if (v7 || v8)
        {
            uint8_t* v9 = &v4[v7];
            // Unrolled in original dll
            for (int j = v8 - 1; j >= 0; j--)
            {
                v9[j] = a3[a1[j]];
            }

            v4 = &v9[v8];
            a1 += v8;
        }
        else
        {
            a2 += dword_6FA81450;
            --a4;
            v4 = a2;
        }
    }
}

//D2Gfx.0x6FA71970
void __fastcall sub_6FA71970(uint8_t* a1, uint8_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, uint8_t a8)
{
    // TODO: Names
    uint8_t* v8 = a1;
    uint8_t* v9 = a2;
    uint8_t* v10 = CMNSUBTILE_GetGouraudRow(a3, a5, a8);
    
    while (a7)
    {
        const uint8_t v11 = v8[0];
        const uint8_t v12 = v8[1];
        v8 += 2;
        
        if (v11 || v12)
        {
            uint8_t* v13 = &v9[v11];
            uint8_t* v14 = &v10[v11];
            // Unrolled in original dll
            for (int i = v12 - 1; i >= 0; i--)
            {
                v13[i] = stru_6FA81580[v14[i]].unk0x00[v8[i]];
            }

            v9 = &v13[v12];
            v8 += v12;
            v10 = &v14[v12];
        }
        else
        {
            --a7;
            a3 += a4;
            a5 += a6;
            a2 += dword_6FA81450;
            v9 = a2;
            v10 = CMNSUBTILE_GetGouraudRow(a3, a5, a8);
        }
    }
}

//D2Gfx.0x6FA71D90
void __fastcall sub_6FA71D90(int32_t a1, int32_t a2, uint8_t* a3, uint8_t* a4, uint8_t* a5, int32_t a6)
{
    // TODO: Names
    int32_t nY = a2;
    uint8_t* pDst = a4;

    int32_t nLine = 0;
    while (nLine < a6)
    {
        const uint8_t nSkip = a3[0];
        const uint8_t nLength = a3[1];
        a3 += 2;

        if (nSkip || nLength)
        {
            if (nY >= dword_6FA8D240)
            {
                return;
            }

            pDst += nSkip;

            if (nY >= dword_6FA84690)
            {
                const int32_t nPosX = a1 + (int32_t)(pDst - a4);
                const int32_t nStart = std::max(dword_6FA8D220 - nPosX, 0);
                const int32_t nEnd = std::min(std::max(dword_6FA8469C - nPosX, 0), (int32_t)nLength);

                // Unrolled in original dll
                for (int32_t i = nEnd - 1; i >= nStart; --i)
                {
                    pDst[i] = a5[a3[i]];
                }
            }

            pDst += nLength;
            a3 += nLength;
        }
        else
        {
            ++nLine;
            ++nY;
            a4 += dword_6FA81450;
            pDst = a4;
        }
    }
}

//D2Gfx.0x6FA72090
void __fastcall sub_6FA72090(int32_t a1, int32_t a2, uint8_t* a3, uint8_t* a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9, uint8_t a10)
{
    // TODO: Names
    int32_t nY = a2;
    uint8_t* pDst = a4;
    uint8_t* pGouraud = CMNSUBTILE_GetGouraudRow(a5, a7, a10);

    int32_t nLine = 0;
    while (nLine < a9)
    {
        const uint8_t nSkip = a3[0];
        const uint8_t nLength = a3[1];
        a3 += 2;

        if (nSkip || nLength)
        {
            if (nY >= dword_6FA8D240)
            {
                return;
            }

            pDst += nSkip;
            pGouraud += nSkip;

            if (nY >= dword_6FA84690)
            {
                const int32_t nPosX = a1 + (int32_t)(pDst - a4);
                const int32_t nStart = std::max(dword_6FA8D220 - nPosX, 0);
                const int32_t nEnd = std::min(std::max(dword_6FA8469C - nPosX, 0), (int32_t)nLength);

                // Unrolled in original dll. Note: the gouraud row is not offset by nStart in the original dll
                for (int32_t i = nEnd - 1; i >= nStart; --i)
                {
                    pDst[i] = stru_6FA81580[pGouraud[i - nStart]].unk0x00[a3[i]];
                }
            }

            pDst += nLength;
            pGouraud += nLength;
            a3 += nLength;
        }
        else
        {
            ++nLine;
            ++nY;
            a4 += dword_6FA81450;
            pDst = a4;
            a5 += a6;
            a7 += a8;
            pGouraud = CMNSUBTILE_GetGouraudRow(a5, a7, a10);
        }
    }
}

//D2Gfx.0x6FA72570
void __fastcall DGFX_InitGouraudCache_6FA72570()
{
    // TODO: Check, Names
    int32_t v1 = 0;
    int32_t v10 = 0;
    for (int32_t i = 0; i < 32; ++i)
    {
        int32_t nVal = i << GOURAUD_SHIFT;
        const int32_t nOriginalValue = nVal;
        for (int32_t j = 0; j < 32; ++j)
        {
            for (int32_t k = 0; k < 32; ++k)
            {
                nVal = D2Clamp(nVal, 0, 0x1F000000);
                byte_6FA85220[i][j][k] = (nVal >> GOURAUD_SHIFT) & 0XFF;
                nVal += v1 >> 5;
            }

            D2_ASSERT((nVal >> GOURAUD_SHIFT) == j);

            v1 += (1 << GOURAUD_SHIFT);
            nVal = nOriginalValue;
        }

        v10 -= (1 << GOURAUD_SHIFT);
        v1 = v10;
    }
}

//D2Gfx.0x6FA72630
void __fastcall sub_6FA72630(int32_t a1, int32_t a2)
{
    //TODO: Names
    int32_t v2 = 0;
    if (gnViewMatrixAdjust_6FA8D254 == 1)
    {
        a1 -= a1 / 2;
    }
    else if (gnViewMatrixAdjust_6FA8D254 == 2)
    {
        v2 = a1 / 2;
    }

    dword_6FA8D244 = v2 - 32;
    dword_6FA84694 = a2 - 63;
    dword_6FA84688 = v2 - 32;
    dword_6FA8D23C = a2 - 47;
    dword_6FA8D24C = a2 - 47;
    dword_6FA8D240 = a2 - 47;
    dword_6FA8468C = v2;
    dword_6FA846A0 = v2;
    dword_6FA8D220 = v2;
    dword_6FA8D224 = -16;
    dword_6FA84698 = a1;
    dword_6FA8D228 = 0;
    dword_6FA8D22C = a1 - 32;
    dword_6FA8D230 = -32;
    dword_6FA85218 = a1;
    dword_6FA8D238 = 0;
    dword_6FA8D248 = a2 - 79;
    dword_6FA8D234 = a1 - 32;
    dword_6FA84690 = 0;
    dword_6FA8469C = a1;
}

//D2Gfx.0x6FA72700
void __fastcall sub_6FA72700()
{
    int32_t v2 = -32 * dword_6FA81450;
    for (int32_t i = 0; i < std::size(dword_6FA846A8); ++i)
    {
        dword_6FA846A8[i] = v2;
        v2 += dword_6FA81450;
    }
}

//D2Gfx.0x6FA72730
void __fastcall D2GFX_DrawVisTile_6FA72730(uint8_t* a1, int32_t nX, int32_t nY)
{
    if (nY < dword_6FA8D230 || nY >= dword_6FA8D24C || nX < dword_6FA84688 || nX >= dword_6FA85218)
    {
        return;
    }

    D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

    uint8_t* pLine = &gCmnInfo_pBuffer_6FA8144C[dword_6FA846A8[nY + 32]] + nX;
    uint8_t* pDst = pLine;

    if (nY < dword_6FA8D238 || nY >= dword_6FA8D248 || nX < dword_6FA846A0 || nX >= dword_6FA8D234)
    {
        int32_t nCurrentY = nY;
        int32_t nLine = 0;
        while (nLine < 32)
        {
            const uint8_t nSkip = a1[0];
            const uint8_t nLength = a1[1];
            a1 += 2;

            if (nSkip || nLength)
            {
                if (nCurrentY >= dword_6FA8D240)
                {
                    return;
                }

                pDst += nSkip;

                if (nCurrentY >= dword_6FA84690)
                {
                    const int32_t nPosX = nX + (int32_t)(pDst - pLine);
                    const int32_t nStart = std::max(dword_6FA8D220 - nPosX, 0);
                    const int32_t nEnd = std::min(std::max(dword_6FA8469C - nPosX, 0), (int32_t)nLength);
                    if (nEnd - nStart > 0)
                    {
                        memcpy(&pDst[nStart], &a1[nStart], nEnd - nStart);
                    }
                }

                pDst += nLength;
                a1 += nLength;
            }
            else
            {
                ++nLine;
                ++nCurrentY;
                pLine += dword_6FA81450;
                pDst = pLine;
            }
        }
    }
    else
    {
        int32_t nLines = 32;
        while (nLines)
        {
            const uint8_t nSkip = a1[0];
            const uint8_t nLength = a1[1];
            a1 += 2;

            if (nSkip || nLength)
            {
                pDst += nSkip;
                memcpy(pDst, a1, nLength);
                pDst += nLength;
                a1 += nLength;
            }
            else
            {
                --nLines;
                pLine += dword_6FA81450;
                pDst = pLine;
            }
        }
    }
}

//D2Gfx.0x6FA72900
void __fastcall sub_6FA72900(uint8_t* a1, int32_t nX, int32_t nY, uint8_t a4)
{
    if (nY < dword_6FA8D230 || nY >= dword_6FA8D24C || nX < dword_6FA84688 || nX >= dword_6FA85218)
    {
        return;
    }

    uint8_t* pBuffer = &gCmnInfo_pBuffer_6FA8144C[dword_6FA846A8[nY + 32]] + nX;

    D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

    if (nY < dword_6FA8D238 || nY >= dword_6FA8D248 || nX < dword_6FA846A0 || nX >= dword_6FA8D234)
    {
        sub_6FA71D90(nX, nY, a1, pBuffer, stru_6FA81580[(uint32_t)a4 >> 3].unk0x00, 32);
    }
    else
    {
        sub_6FA71720(a1, pBuffer, stru_6FA81580[(uint32_t)a4 >> 3].unk0x00, 32);
    }
}

//D2Gfx.0x6FA729D0
void __fastcall TILE_TileDrawLit_6FA729D0(uint8_t* a1, int32_t nX, int32_t nY, int32_t* pIntensities)
{
    if (dword_6FA8D250)
    {
        if ((*(uint8_t*)pIntensities & 0xF8) == 0xF8)
        {
            D2GFX_DrawVisTile_6FA72730(a1, nX, nY);
        }
        else
        {
            sub_6FA72900(a1, nX, nY, *(uint8_t*)pIntensities);
        }
    }
    else
    {
        // TODO: Names
        const int32_t v6 = 32 * pIntensities[0];
        const int32_t v7 = pIntensities[3] - pIntensities[0];
        const int32_t v8 = pIntensities[2] - pIntensities[1];
        const int32_t v9 = 32 * pIntensities[1];

        if (gGfxSettings.bLowQuality || std::abs(pIntensities[1] - pIntensities[0]) + std::abs(v7) + std::abs(v8) < 10)
        {
            if ((v6 & 0xFFFFFF00) == 0x1F00)
            {
                D2GFX_DrawVisTile_6FA72730(a1, nX, nY);
            }
            else
            {
                sub_6FA72900(a1, nX, nY, *(uint8_t*)pIntensities);
            }
        }
        else
        {
            if (nY >= dword_6FA8D230 && nY < dword_6FA8D24C && nX >= dword_6FA84688 && nX < dword_6FA85218)
            {
                D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

                uint8_t* pBuffer = &gCmnInfo_pBuffer_6FA8144C[dword_6FA846A8[nY + 32]] + nX;
                if (nY < dword_6FA8D238 || nY >= dword_6FA8D248 || nX < dword_6FA846A0 || nX >= dword_6FA8D234)
                {
                    sub_6FA72090(nX, nY, a1, pBuffer, v6, v7, v9, v8, 32, 8);
                }
                else
                {
                    sub_6FA71970(a1, pBuffer, v6, v7, v9, v8, 32, 8);
                }
            }
        }
    }
}

//D2Gfx.0x6FA72B80
void __fastcall D2GFX_DrawBlendedVisTile_6FA72B80(uint8_t* a1, int32_t nX, int32_t nY, uint8_t nAlpha)
{
    uint8_t* pBlendTable = nullptr;
    if (nAlpha >= 192)
    {
        pBlendTable = dword_6FA81448[0];
    }
    else if (nAlpha >= 128)
    {
        pBlendTable = dword_6FA81448[1];
    }
    else if (nAlpha >= 64)
    {
        pBlendTable = dword_6FA81448[2];
    }
    else
    {
        return;
    }

    if (nY < dword_6FA8D230 || nY >= dword_6FA8D24C || nX < dword_6FA84688 || nX >= dword_6FA85218)
    {
        return;
    }

    D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

    uint8_t* pLine = &gCmnInfo_pBuffer_6FA8144C[dword_6FA846A8[nY + 32]] + nX;
    uint8_t* pDst = pLine;

    if (nY < dword_6FA8D238 || nY >= dword_6FA8D248 || nX < dword_6FA846A0 || nX >= dword_6FA8D234)
    {
        int32_t nCurrentY = nY;
        int32_t nLine = 0;
        while (nLine < 32)
        {
            const uint8_t nSkip = a1[0];
            const uint8_t nLength = a1[1];
            a1 += 2;

            if (nSkip || nLength)
            {
                if (nCurrentY >= dword_6FA8D240)
                {
                    return;
                }

                pDst += nSkip;

                if (nCurrentY >= dword_6FA84690)
                {
                    const int32_t nPosX = nX + (int32_t)(pDst - pLine);
                    const int32_t nStart = std::max(dword_6FA8D220 - nPosX, 0);
                    const int32_t nEnd = std::min(std::max(dword_6FA8469C - nPosX, 0), (int32_t)nLength);
                    for (int32_t i = nStart; i < nEnd; ++i)
                    {
                        pDst[i] = pBlendTable[(pDst[i] << 8) + a1[i]];
                    }
                }

                pDst += nLength;
                a1 += nLength;
            }
            else
            {
                ++nLine;
                ++nCurrentY;
                pLine += dword_6FA81450;
                pDst = pLine;
            }
        }
    }
    else
    {
        int32_t nLines = 32;
        while (nLines)
        {
            const uint8_t nSkip = a1[0];
            const uint8_t nLength = a1[1];
            a1 += 2;

            if (nSkip || nLength)
            {
                pDst += nSkip;
                for (int32_t i = 0; i < nLength; ++i)
                {
                    pDst[i] = pBlendTable[(pDst[i] << 8) + a1[i]];
                }
                pDst += nLength;
                a1 += nLength;
            }
            else
            {
                --nLines;
                pLine += dword_6FA81450;
                pDst = pLine;
            }
        }
    }
}

//D2Gfx.0x6FA72DC0
void __fastcall D2GFX_DrawRoofTile_6FA72DC0(uint8_t* a1, int32_t nX, int32_t nY, int32_t* pIntensities, uint8_t nAlpha)
{
    uint8_t* pBlendTable = nullptr;
    if (nAlpha >= 192)
    {
        pBlendTable = dword_6FA81448[0];
    }
    else if (nAlpha >= 128)
    {
        pBlendTable = dword_6FA81448[1];
    }
    else if (nAlpha >= 64)
    {
        pBlendTable = dword_6FA81448[2];
    }
    else
    {
        return;
    }

    const int32_t nLeftIntensityStep = pIntensities[3] - pIntensities[0];
    const int32_t nRightIntensityStep = pIntensities[2] - pIntensities[1];
    int32_t nLeftIntensity = 32 * pIntensities[0];
    int32_t nRightIntensity = 32 * pIntensities[1];

    if (nY < dword_6FA8D230 || nY >= dword_6FA8D24C || nX < dword_6FA84688 || nX >= dword_6FA85218)
    {
        return;
    }

    D2_ASSERT(gCmnInfo_pBuffer_6FA8144C);

    uint8_t* pLine = &gCmnInfo_pBuffer_6FA8144C[dword_6FA846A8[nY + 32]] + nX;
    uint8_t* pDst = pLine;
    uint8_t* pGouraud = CMNSUBTILE_GetGouraudRow(nLeftIntensity, nRightIntensity, 8);

    if (nY < dword_6FA8D238 || nY >= dword_6FA8D248 || nX < dword_6FA846A0 || nX >= dword_6FA8D234)
    {
        int32_t nCurrentY = nY;
        int32_t nLine = 0;
        while (nLine < 32)
        {
            const uint8_t nSkip = a1[0];
            const uint8_t nLength = a1[1];
            a1 += 2;

            if (nSkip || nLength)
            {
                if (nCurrentY >= dword_6FA8D240)
                {
                    return;
                }

                pDst += nSkip;
                pGouraud += nSkip;

                if (nCurrentY >= dword_6FA84690)
                {
                    const int32_t nPosX = nX + (int32_t)(pDst - pLine);
                    const int32_t nStart = std::max(dword_6FA8D220 - nPosX, 0);
                    const int32_t nEnd = std::min(std::max(dword_6FA8469C - nPosX, 0), (int32_t)nLength);
                    // Note: the gouraud row is not offset by nStart in the original dll
                    for (int32_t i = nStart; i < nEnd; ++i)
                    {
                        const uint8_t nLitColor = stru_6FA81580[pGouraud[i - nStart]].unk0x00[a1[i]];
                        pDst[i] = pBlendTable[(nLitColor << 8) + pDst[i]];
                    }
                }

                pDst += nLength;
                pGouraud += nLength;
                a1 += nLength;
            }
            else
            {
                ++nLine;
                ++nCurrentY;
                pLine += dword_6FA81450;
                pDst = pLine;
                nLeftIntensity += nLeftIntensityStep;
                nRightIntensity += nRightIntensityStep;
                pGouraud = CMNSUBTILE_GetGouraudRow(nLeftIntensity, nRightIntensity, 8);
            }
        }
    }
    else
    {
        int32_t nLines = 32;
        while (nLines)
        {
            const uint8_t nSkip = a1[0];
            const uint8_t nLength = a1[1];
            a1 += 2;

            if (nSkip || nLength)
            {
                pDst += nSkip;
                pGouraud += nSkip;
                for (int32_t i = 0; i < nLength; ++i)
                {
                    const uint8_t nLitColor = stru_6FA81580[pGouraud[i]].unk0x00[a1[i]];
                    pDst[i] = pBlendTable[(nLitColor << 8) + pDst[i]];
                }
                pDst += nLength;
                pGouraud += nLength;
                a1 += nLength;
            }
            else
            {
                --nLines;
                pLine += dword_6FA81450;
                pDst = pLine;
                nLeftIntensity += nLeftIntensityStep;
                nRightIntensity += nRightIntensityStep;
                pGouraud = CMNSUBTILE_GetGouraudRow(nLeftIntensity, nRightIntensity, 8);
            }
        }
    }
}

//D2Gfx.0x6FA73130
void __fastcall sub_6FA73130(D2TileLibraryBlockStrc* a1, int32_t a2, int32_t a3, uint8_t* a4, uint8_t a5)
{
    D2PaletteStrc* pPalette = &stru_6FA81580[(uint32_t)a5 >> 3];

    if (a1->nFormat & 4)
    {
        sub_6FA71D90(a2, a3, a1->dwOffset_pData, a4, pPalette->unk0x00, 15);
    }
    else
    {
        const int32_t nEnd = std::min(dword_6FA8D240 - a3, 15);
        for (int32_t nStart = std::max(dword_6FA84690 - a3, 0); nStart < nEnd; ++nStart)
        {
            const int32_t nOffset = a2 + dword_6FA7E064[nStart];
            const int32_t nIndex = std::max(dword_6FA8D220 - nOffset, 0);
            const int32_t nSize = D2Clamp(dword_6FA8469C - nOffset, 0, dword_6FA7E0A0[nStart]) - nIndex;
            if (nSize > 0)
            {
                uint8_t* pCurrent = &a4[nStart * dword_6FA81450 + dword_6FA7E064[nStart] + nIndex];
                uint8_t* pStart = &a1->dwOffset_pData[dword_6FA7E0DC[nStart] + nIndex];
                uint8_t* pEnd = &pStart[nSize];
                while (pStart < pEnd)
                {
                    *pCurrent = pPalette->unk0x00[*pStart];
                    ++pCurrent;
                    ++pStart;
                }
            }
        }
    }
}

//D2Gfx.0x6FA73270
void __fastcall sub_6FA73270(D2TileLibraryBlockStrc* a1, int32_t a2, int32_t a3, uint8_t* a4, int32_t* a5)
{
    // TODO: Names
    const int32_t v7 = a5[3] - a5[0];
    const int32_t v9 = a5[2] - a5[1];
    int32_t v11 = 16 * a5[0];
    int32_t v12 = 16 * a5[1];

    if (a1->nFormat & 4)
    {
        sub_6FA72090(a2, a3, a1->dwOffset_pData, a4, v11, v7, v12, v9, 15, 7);
    }
    else
    {
        const int32_t nEnd = std::min(dword_6FA8D240 - a3, 15);
        for (int32_t nStart = std::max(dword_6FA84690 - a3, 0); nStart < nEnd; ++nStart)
        {
            const int32_t nOffset = a2 + dword_6FA7E064[nStart];
            const int32_t nIndex = std::max(dword_6FA8D220 - nOffset, 0);
            const int32_t nSize = D2Clamp(dword_6FA8469C - nOffset, 0, dword_6FA7E0A0[nStart]) - nIndex;
            if (nSize > 0)
            {
                uint8_t* pIndex = CMNSUBTILE_GetGouraudRow(v11, v12, 7) + dword_6FA7E064[nStart];
                uint8_t* pCurrent = &a4[nStart * dword_6FA81450 + dword_6FA7E064[nStart] + nIndex];
                uint8_t* pStart = &a1->dwOffset_pData[dword_6FA7E0DC[nStart] + nIndex];
                uint8_t* pEnd = &pStart[nSize];
                while (pStart < pEnd)
                {
                    *pCurrent = stru_6FA81580[*pIndex].unk0x00[*pStart];
                    ++pCurrent;
                    ++pStart;
                    ++pIndex;
                }
            }

            v11 += v7;
            v12 += v9;
        }
    }
}

//D2Gfx.0x6FA73410
void __fastcall D2GFX_FloorTileDraw_6FA73410(D2TileLibraryEntryStrc* pTileLibraryEntry, int32_t nX, int32_t nY, D2GfxLightExStrc* pLightEx)
{
    D2GfxTileLibraryEntryStrc* pTile = (D2GfxTileLibraryEntryStrc*)pTileLibraryEntry;
    uint8_t* pTileBuffer = gCmnInfo_pBuffer_6FA8144C + nY * dword_6FA81450 + nX;

    for (int32_t i = 0; i < pTile->nBlocks; ++i)
    {
        D2TileLibraryBlockStrc* pBlock = &pTile->pBlocks[i];
        uint8_t* pDst = pTileBuffer + pBlock->nPosY * dword_6FA81450 + pBlock->nPosX;

        if (!(pBlock->nFormat & 1))
        {
            continue;
        }

        const int32_t nBlockX = nX + pBlock->nPosX;
        const int32_t nBlockY = nY + pBlock->nPosY;
        if (nBlockY < dword_6FA8D224 || nBlockY >= dword_6FA8D23C || nBlockX < dword_6FA8D244 || nBlockX >= dword_6FA84698)
        {
            continue;
        }

        // Light grid around the block, 8 entries per row
        const D2GfxLightExStrc* pLight = &pLightEx[pBlock->nGridX + 8 * pBlock->nGridY];

        int32_t bFlatLight = 0;
        uint8_t nIntensity = 0;
        int32_t pIntensities[4];

        if (dword_6FA8D250)
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

        if (nBlockY >= dword_6FA8D228 && nBlockY < dword_6FA84694 && nBlockX >= dword_6FA8468C && nBlockX < dword_6FA8D22C)
        {
            if (bFlatLight)
            {
                uint8_t* pPalette = stru_6FA81580[nIntensity >> 3].unk0x00;
                if (pBlock->nFormat & 4)
                {
                    sub_6FA71720(pBlock->dwOffset_pData, pDst, pPalette, 15);
                }
                else
                {
                    sub_6FA71130(pBlock->dwOffset_pData, pDst, pPalette);
                }
            }
            else
            {
                if (pBlock->nFormat & 4)
                {
                    sub_6FA71970(pBlock->dwOffset_pData, pDst, 16 * pIntensities[0], pIntensities[3] - pIntensities[0], 16 * pIntensities[1], pIntensities[2] - pIntensities[1], 15, 7);
                }
                else
                {
                    sub_6FA71340(pBlock->dwOffset_pData, pDst, 16 * pIntensities[0], pIntensities[3] - pIntensities[0], 16 * pIntensities[1], pIntensities[2] - pIntensities[1]);
                }
            }
        }
        else
        {
            if (bFlatLight)
            {
                sub_6FA73130(pBlock, nBlockX, nBlockY, pDst, nIntensity);
            }
            else
            {
                sub_6FA73270(pBlock, nBlockX, nBlockY, pDst, pIntensities);
            }
        }
    }
}
