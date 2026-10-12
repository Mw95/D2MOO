#include "OglTile.h"

#include <D2Gfx.h>
#include <CmnSubtile.h>

#include "OglCore.h"
#include "OglImports.h"


// Wall tiles are made of 32x32 blocks, 5 blocks wide
constexpr int32_t TILE_BLOCK_SIZE = 32;
constexpr int32_t TILE_BLOCK_SHIFT = 5;
// Floor tiles are 160 pixels wide, and are drawn from their center
constexpr int32_t FLOOR_TILE_HALF_WIDTH = 80;


enum D2OglScreenPanels
{
    SCREENPANELS_NONE,
    SCREENPANELS_LEFT,      // The left panel is open, only the right half of the screen is visible
    SCREENPANELS_RIGHT,     // The right panel is open, only the left half of the screen is visible
};


struct D2OglTileBoundsStrc
{
    int32_t nMinX;
    int32_t nMaxX;
    int32_t nMaxY;
};

// Positions of the blocks that can be drawn, depending on the open panels
static D2OglTileBoundsStrc OGL_GetTileBounds(int32_t nScreenPanels)
{
    D2OglTileBoundsStrc bounds = { -TILE_BLOCK_SIZE, gnBufferWidth, gnBufferHeight + TILE_BLOCK_SIZE };

    if (nScreenPanels == SCREENPANELS_LEFT)
    {
        bounds.nMaxX = gnBufferWidth - gnBufferWidth / 2;
    }
    else if (nScreenPanels == SCREENPANELS_RIGHT)
    {
        bounds.nMinX = gnBufferWidth / 2 - TILE_BLOCK_SIZE;
    }

    return bounds;
}

static BOOL OGL_IsBlockVisible(const D2OglTileBoundsStrc& bounds, int32_t nX, int32_t nY)
{
    return nX >= bounds.nMinX && nX < bounds.nMaxX && nY >= -TILE_BLOCK_SIZE && nY < bounds.nMaxY;
}

// The light is given for each column of blocks, interpolated horizontally
static void OGL_GetBlockIntensities(const D2GfxLightStrc* pLight, const D2TileLibraryBlockStrc* pBlock, int32_t pIntensities[4])
{
    const int32_t nColumn = pBlock->nPosX >> TILE_BLOCK_SHIFT;
    pIntensities[0] = pLight[nColumn].nIntensity;       // Top left
    pIntensities[1] = pLight[nColumn + 1].nIntensity;   // Top right
    pIntensities[2] = pLight[nColumn + 1].nIntensity;   // Bottom right
    pIntensities[3] = pLight[nColumn].nIntensity;       // Bottom left
}

//pfFloorTileDraw
// Port of D2Gdi.0x6F8320C0
int32_t __fastcall OGL_FloorTileDraw(D2TileLibraryEntryStrc* pTile, D2GfxLightExStrc* pLight, int32_t nPosX, int32_t nPosY, int32_t nWorldXpos, int32_t nWorldYpos, uint8_t nAlpha, int32_t nScreenPanels, void* pTileData)
{
    if (!D2CMP_TileValidate(pTile, TRUE, 0))
    {
        return FALSE;
    }

    int32_t nX = nPosX - FLOOR_TILE_HALF_WIDTH;
    if (nScreenPanels == SCREENPANELS_LEFT)
    {
        nX -= gnBufferWidth / 4;
    }
    else if (nScreenPanels == SCREENPANELS_RIGHT)
    {
        nX += gnBufferWidth / 4;
    }

    gpGfxHelpers->pfFloorTileDraw(pTile, nX, nPosY, pLight);
    return TRUE;
}

//pfTileDrawLit
// Port of D2Gdi.0x6F832F40
int32_t __fastcall OGL_TileDrawLit(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, D2GfxLightStrc* pLight, int32_t nScreenPanels)
{
    if (!D2CMP_TileValidate(pTile, TRUE, 0))
    {
        return FALSE;
    }

    const D2GfxTileLibraryEntryStrc* pGfxTile = (const D2GfxTileLibraryEntryStrc*)pTile;
    const D2OglTileBoundsStrc bounds = OGL_GetTileBounds(nScreenPanels);

    int32_t bDrawn = FALSE;
    for (int32_t i = 0; i < pGfxTile->nBlocks; ++i)
    {
        const D2TileLibraryBlockStrc* pBlock = &pGfxTile->pBlocks[i];
        const int32_t nX = pBlock->nPosX + nPosX;
        const int32_t nY = pBlock->nPosY + nPosY;
        if (OGL_IsBlockVisible(bounds, nX, nY))
        {
            bDrawn = TRUE;

            int32_t pIntensities[4];
            OGL_GetBlockIntensities(pLight, pBlock, pIntensities);
            gpGfxHelpers->pfTileDrawLit(pBlock->dwOffset_pData, nX, nY, pIntensities);
        }
    }

    return bDrawn;
}

//pfTileDrawTrans
// Port of D2Gdi.0x6F832E00
int32_t __fastcall OGL_TileDrawTrans(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, D2GfxLightStrc* pLight, int32_t nScreenPanels, uint8_t nAlpha)
{
    if (!D2CMP_TileValidate(pTile, TRUE, 0))
    {
        return FALSE;
    }

    const D2GfxTileLibraryEntryStrc* pGfxTile = (const D2GfxTileLibraryEntryStrc*)pTile;
    const D2OglTileBoundsStrc bounds = OGL_GetTileBounds(nScreenPanels);

    int32_t bDrawn = FALSE;
    for (int32_t i = 0; i < pGfxTile->nBlocks; ++i)
    {
        const D2TileLibraryBlockStrc* pBlock = &pGfxTile->pBlocks[i];
        const int32_t nX = pBlock->nPosX + nPosX;
        const int32_t nY = pBlock->nPosY + nPosY;
        if (OGL_IsBlockVisible(bounds, nX, nY))
        {
            bDrawn = TRUE;

            int32_t pIntensities[4];
            OGL_GetBlockIntensities(pLight, pBlock, pIntensities);
            gpGfxHelpers->pfDrawRoofTile(pBlock->dwOffset_pData, nX, nY, pIntensities, nAlpha);
        }
    }

    return bDrawn;
}

//pfShadowTileDraw
// Port of D2Gdi.0x6F832CE0, the draw mode is ignored
int32_t __fastcall OGL_ShadowTileDraw(D2TileLibraryEntryStrc* pTile, int32_t nPosX, int32_t nPosY, DrawMode eDrawMode, int32_t nScreenPanels)
{
    if (!D2CMP_TileValidate(pTile, TRUE, 0))
    {
        return FALSE;
    }

    const D2GfxTileLibraryEntryStrc* pGfxTile = (const D2GfxTileLibraryEntryStrc*)pTile;
    const D2OglTileBoundsStrc bounds = OGL_GetTileBounds(nScreenPanels);

    int32_t bDrawn = FALSE;
    for (int32_t i = 0; i < pGfxTile->nBlocks; ++i)
    {
        const D2TileLibraryBlockStrc* pBlock = &pGfxTile->pBlocks[i];
        const int32_t nX = pBlock->nPosX + nPosX;
        const int32_t nY = pBlock->nPosY + nPosY;
        if (OGL_IsBlockVisible(bounds, nX, nY))
        {
            bDrawn = TRUE;

            if (gpGfxSettings->bBlendedShadows)
            {
                gpGfxHelpers->pfDrawBlendedVisTile(pBlock->dwOffset_pData, nX, nY, 192);
            }
            else
            {
                gpGfxHelpers->pfDrawVisTile(pBlock->dwOffset_pData, nX, nY);
            }
        }
    }

    return bDrawn;
}
