#include "OglSmack.h"

#include <cstring>

#include <Fog.h>

#include "OglCore.h"
#include "OglImports.h"


constexpr int32_t BANNER_WIDTH = 468;
constexpr int32_t BANNER_HEIGHT = 60;

// Decoded frame of the banner, shared by all the contexts like in D2Gdi.dll
static uint8_t* gpSmackFrame;
static int32_t gbSmackPaletteValid;
// Maps the colors of the banner to the nearest colors of the game palette
static uint8_t gSmackRemap[256];


static void SMACK_FreeFrame()
{
    if (gpSmackFrame)
    {
        D2_FREE(gpSmackFrame);
        gpSmackFrame = nullptr;
    }
}

static void SMACK_CloseContext(D2GfxSmackContextStrc* pContext)
{
    SMACK_FreeFrame();

    if (pContext->nType == SMACKTYPE_SMACKER && pContext->pHandle)
    {
        SMACK_Close((D2SmackStrc*)pContext->pHandle);
        pContext->pHandle = nullptr;
    }

    pContext->nType = SMACKTYPE_NONE;
}

// Copies the frame to the back buffer, its bottom left corner being at (nX, nY)
static void SMACK_DrawFrame(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight)
{
    if (!gpSmackFrame || !gpbOffscreenBuffer)
    {
        return;
    }

    for (int32_t nLine = 0; nLine < nHeight; ++nLine)
    {
        // Note: the original dll does not clip the frame
        const int32_t nDstY = nY - nHeight + nLine;
        if (nDstY < 0 || nDstY >= gnBufferHeight)
        {
            continue;
        }

        const uint8_t* pSrc = &gpSmackFrame[nLine * nWidth];
        uint8_t* pDst = &gpbOffscreenBuffer[nDstY * gnBufferWidth];
        for (int32_t nColumn = 0; nColumn < nWidth; ++nColumn)
        {
            const int32_t nDstX = nX + nColumn;
            if (nDstX >= 0 && nDstX < gnBufferWidth)
            {
                pDst[nDstX] = gSmackRemap[pSrc[nColumn]];
            }
        }
    }
}

static BOOL SMACK_DecodePcx(const char* szFileName)
{
    gpSmackFrame = (uint8_t*)D2_CALLOC(BANNER_WIDTH * BANNER_HEIGHT);

    void* pFileData = nullptr;
    uint32_t nFileSize = 0;
    if (!STORM_SFileLoadFileEx(nullptr, szFileName, &pFileData, &nFileSize, 0, 3, nullptr) || !pFileData)
    {
        return FALSE;
    }

    PALETTEENTRY palette[256] = {};
    uint32_t nWidth = 0;
    uint32_t nHeight = 0;
    uint32_t nBitsPerPixel = 0;
    const BOOL bDecoded = STORM_SBmpDecodeImage(2, pFileData, nFileSize, palette, gpSmackFrame, BANNER_WIDTH * BANNER_HEIGHT, &nWidth, &nHeight, &nBitsPerPixel);
    STORM_SMemFree(pFileData, __FILE__, __LINE__, 0);

    if (!bDecoded || nWidth != BANNER_WIDTH || nHeight != BANNER_HEIGHT || nBitsPerPixel != 8)
    {
        return FALSE;
    }

    for (int32_t i = 0; i < 256; ++i)
    {
        gSmackRemap[i] = D2CMP_GetNearestPaletteIndex(gGamePalette, 256, palette[i].peRed, palette[i].peGreen, palette[i].peBlue);
    }

    return TRUE;
}

static BOOL SMACK_DecodeSmacker(D2GfxSmackContextStrc* pContext, const char* szFileName)
{
    if (!IMPORTS_HasSmack())
    {
        return FALSE;
    }

    D2SmackStrc* pSmack = SMACK_Open(szFileName, 0xFE000, (uint32_t)-1);
    pContext->pHandle = pSmack;
    if (!pSmack)
    {
        return FALSE;
    }

    gpSmackFrame = (uint8_t*)D2_CALLOC(pSmack->nWidth * pSmack->nHeight);
    SMACK_ToBuffer(pSmack, 0, 0, pSmack->nWidth, pSmack->nHeight, gpSmackFrame, 0);

    // The palette is only known once the first frame was decoded
    gbSmackPaletteValid = FALSE;
    return TRUE;
}

//pfDecodeSmacker
// Port of D2Gdi.0x6F832120
void __fastcall OGL_DecodeSmacker(const char* szSmacker, uint8_t* pBuffer, int32_t nVersion)
{
    D2GfxSmackContextStrc* pContext = (D2GfxSmackContextStrc*)pBuffer;
    pContext->nType = (uint8_t)nVersion;

    BOOL bDecoded = FALSE;
    if (pContext->nType == SMACKTYPE_PCX)
    {
        bDecoded = SMACK_DecodePcx(szSmacker);
    }
    else if (pContext->nType == SMACKTYPE_SMACKER)
    {
        if (pContext->pHandle)
        {
            return;
        }

        bDecoded = SMACK_DecodeSmacker(pContext, szSmacker);
    }
    else
    {
        return;
    }

    if (!bDecoded)
    {
        SMACK_CloseContext(pContext);
    }
}

//pfPlaySmacker
// Port of D2Gdi.0x6F832310
void __fastcall OGL_PlaySmacker(void* pContext)
{
    D2GfxSmackContextStrc* pSmackContext = (D2GfxSmackContextStrc*)pContext;

    if (pSmackContext->nType == SMACKTYPE_PCX)
    {
        if (!gbPaused)
        {
            SMACK_DrawFrame(pSmackContext->nX, pSmackContext->nY, BANNER_WIDTH, BANNER_HEIGHT);
        }
        return;
    }

    if (pSmackContext->nType != SMACKTYPE_SMACKER || !pSmackContext->pHandle)
    {
        return;
    }

    D2SmackStrc* pSmack = (D2SmackStrc*)pSmackContext->pHandle;
    if (!SMACK_Wait(pSmack))
    {
        if (!ghWnd)
        {
            return;
        }

        if (pSmack->bNewPalette)
        {
            for (int32_t i = 0; i < 256; ++i)
            {
                const uint8_t* pColor = &pSmack->pPalette[3 * i];
                gSmackRemap[i] = D2CMP_GetNearestPaletteIndex(gGamePalette, 256, pColor[0], pColor[1], pColor[2]);
            }

            gbSmackPaletteValid = TRUE;
        }

        SMACK_DoFrame(pSmack);

        if (pSmack->nFrameNum == pSmack->nFrames)
        {
            // Note: the original dll keeps on using the closed smacker to draw the frame
            SMACK_CloseContext(pSmackContext);
            return;
        }

        SMACK_NextFrame(pSmack);
    }

    if (!gbPaused && gbSmackPaletteValid)
    {
        SMACK_DrawFrame(pSmackContext->nX, pSmackContext->nY, pSmack->nWidth, pSmack->nHeight);
    }
}

//pfCloseSmacker
// Port of D2Gdi.0x6F8324F0
void __fastcall OGL_CloseSmacker(void* pContext)
{
    SMACK_CloseContext((D2GfxSmackContextStrc*)pContext);
}
