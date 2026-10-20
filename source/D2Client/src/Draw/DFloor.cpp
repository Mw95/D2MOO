#include "Draw/DFloor.h"

#include <D2Gfx.h>
#include <Scale.h>
#include <D2Dungeon.h>
#include <D2Environment.h>
#include <D2Seed.h>
#include <Path/Path.h>

#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Draw/DLightMap.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/SCmd.h"
#include "Unit/CUnit.h"


//D2Client.0x6FBA7984
D2DrlgActStrc* ghAct;


//D2Client.0x6FAA2E70 (inlined)
static int32_t DFLOOR_GetScreenPanelsOffset(int32_t nScreenPanels)
{
	if (nScreenPanels == 1)
	{
		return -(gnScreenWidth / 4);
	}

	if (nScreenPanels == 2)
	{
		return gnScreenWidth / 4;
	}

	return 0;
}

//D2Client.0x6FAA2E70
void __fastcall DFLOOR_DrawFloorTile(D2FloorDrawContextStrc* pContext, int32_t nUnused, D2DrlgTileDataStrc* pTileData, BOOL bFloorFilter, int32_t nXPos, int32_t nYPos, int32_t nWorldX, int32_t nWorldY)
{
	if (pTileData->dwFlags & 0x408)
	{
		return;
	}

	const RECT* ptRect = &pContext->pView->tViewRect;
	D2_ASSERT(ptRect);

	if (nXPos < ptRect->left || nXPos >= ptRect->right || nYPos < ptRect->top || nYPos >= ptRect->bottom)
	{
		return;
	}

	D2TileLibraryEntryStrc* pTile = pTileData->pTile;
	if (pTile->nType != 0)
	{
		return;
	}

	if (WNDPROC_GetDisplayType() < DISPLAYTYPE_GLIDE)
	{
		D2GfxLightExStrc aLights[64];
		if (pTile->nFlags & 0x100)
		{
			for (int32_t i = 0; i < ARRAY_SIZE(aLights); ++i)
			{
				aLights[i].nIntensity = 255;
				aLights[i].nRed = 255;
				aLights[i].nBlue = 255;
				aLights[i].nGreen = 255;
			}
		}
		else
		{
			DFLOOR_ComputeTileLights(aLights, nWorldX, nWorldY, 0);
		}

		D2GFX_FloorTileDraw(pTileData->pTile, aLights, nXPos, nYPos, nWorldX, nWorldY, 255, pContext->nScreenPanels, (void*)bFloorFilter);
	}
	else
	{
		D2GfxLightExStrc aLights[36];
		if (!pContext->bPerspective)
		{
			if (pTile->nFlags & 0x100)
			{
				const int32_t nX = nXPos + DFLOOR_GetScreenPanelsOffset(pContext->nScreenPanels);
				D2GfxLightExStrc* pLight = aLights;
				for (int32_t nRow = 0; nRow < 6; ++nRow)
				{
					for (int32_t nColumn = 0; nColumn < 6; ++nColumn)
					{
						if (!pContext->bLowQuality || (nColumn == 0 || nColumn == 5) && (nRow == 0 || nRow == 5))
						{
							pLight->nIntensity = 255;
							pLight->nRed = 255;
							pLight->nBlue = 255;
							pLight->nX = nX + 16 * (nColumn - nRow);
							pLight->nGreen = 255;
							pLight->nY = nYPos + 8 * (nColumn + nRow);
						}
						++pLight;
					}
				}
			}
			else
			{
				DFLOOR_ComputeTileLightsEx(aLights, nXPos, nYPos, nWorldX, nWorldY, 0, pContext->nScreenPanels, pContext->bLowQuality);
			}
		}
		else
		{
			const BOOL bLowQuality = pContext->bLowQuality;
			if (pTile->nFlags & 0x100)
			{
				const int32_t nOffsetX = DFLOOR_GetScreenPanelsOffset(pContext->nScreenPanels);
				D2GfxLightExStrc* pLight = aLights;
				for (int32_t nRow = 0; nRow < 6; ++nRow)
				{
					for (int32_t nColumn = 0; nColumn < 6; ++nColumn)
					{
						if (!bLowQuality || (nColumn == 0 || nColumn == 5) && (nRow == 0 || nRow == 5))
						{
							SCALE_AdjustPerspectivePosition((nWorldX + nColumn) << 16, (nRow + nWorldY) << 16, 0, &pLight->nX, &pLight->nY);
							pLight->nIntensity = 255;
							pLight->nX += nOffsetX;
							pLight->nRed = 255;
							pLight->nBlue = 255;
							pLight->nGreen = 255;
						}
						++pLight;
					}
				}
			}
			else
			{
				DFLOOR_ComputeTileLightsPerspective(aLights, nWorldX, nWorldY, 0, pContext->nScreenPanels, bLowQuality);
			}
		}

		D2GFX_FloorTileDraw(pTileData->pTile, aLights, nXPos, nYPos, nWorldX, nWorldY, 255, pContext->nScreenPanels, (void*)bFloorFilter);
	}

	if (pTile->nFlags & 2)
	{
		const uint32_t nRand = (uint32_t)SEED_RollRandomNumber(pContext->pSeed) % 1000;
		if (pContext->bSpawnFloorParticles && (int32_t)nRand < pContext->nFloorParticleChance)
		{
			sub_6FAA7590(nXPos, nYPos, nWorldX << 16, nWorldY << 16);
		}

		if (pContext->bSpawnFloorSplashes && nRand < 100)
		{
			sub_6FAA7760(nXPos, nYPos, nWorldX << 16, nWorldY << 16);
		}
	}

	pTileData->dwFlags |= 0x20000;

	if (pContext->bDrawEdges)
	{
		if (nWorldX < pContext->nMinX)
		{
			pContext->nMinX = nWorldX;
		}

		if (nWorldX > pContext->nMaxX)
		{
			pContext->nMaxX = nWorldX;
		}

		if (nWorldY < pContext->nMinY)
		{
			pContext->nMinY = nWorldY;
		}

		if (nWorldY > pContext->nMaxY)
		{
			pContext->nMaxY = nWorldY;
		}
	}
}

//D2Client.0x6FAA3290
void __fastcall DFLOOR_DrawEdgeTile(D2FloorDrawContextStrc* pContext, int32_t nUnused, int32_t nX, int32_t nY)
{
	int32_t nClientX = nX;
	int32_t nClientY = nY + 5;
	DUNGEON_GameSubtileToClientCoords(&nClientX, &nClientY);
	nClientY += 40;

	D2_ASSERT(ghAct);

	nClientX += pContext->nOffsetX;
	nClientY += pContext->nOffsetY;

	if (D2DrlgTileDataStrc* pTileData = DUNGEON_GetTileDataFromAct(ghAct))
	{
		DFLOOR_DrawFloorTile(pContext, nClientX, pTileData, TRUE, nClientX, nClientY, nX, nY);
	}
}

//D2Client.0x6FAA3330 (inlined)
static int32_t DFLOOR_GetUnitClientX(D2UnitStrc* pUnit)
{
	if (pUnit->dwUnitType == UNIT_OBJECT || pUnit->dwUnitType == UNIT_ITEM || pUnit->dwUnitType == UNIT_TILE)
	{
		return pUnit->pStaticPath->dwClientCoordX;
	}

	if (!pUnit->pDynamicPath)
	{
		return 0;
	}

	return PATH_GetXPosition(pUnit->pDynamicPath);
}

//D2Client.0x6FAA3330 (inlined)
static int32_t DFLOOR_GetUnitClientY(D2UnitStrc* pUnit)
{
	if (pUnit->dwUnitType == UNIT_OBJECT || pUnit->dwUnitType == UNIT_ITEM || pUnit->dwUnitType == UNIT_TILE)
	{
		return pUnit->pStaticPath->dwClientCoordY;
	}

	if (!pUnit->pDynamicPath)
	{
		return 0;
	}

	return PATH_GetYPosition(pUnit->pDynamicPath);
}

//D2Client.0x6FAA3330 (inlined)
static void DFLOOR_DrawSingleEdgeTile(D2FloorDrawContextStrc* pContext, int32_t nX, int32_t nY, int32_t nTileX, int32_t nTileY)
{
	int32_t nClientX = nX;
	int32_t nClientY = nY;
	DUNGEON_GameSubtileToClientCoords(&nClientX, &nClientY);
	nClientY += 40;

	D2_ASSERT(ghAct);

	nClientX += pContext->nOffsetX;
	nClientY += pContext->nOffsetY;

	if (D2DrlgTileDataStrc* pTileData = DUNGEON_GetTileDataFromAct(ghAct))
	{
		DFLOOR_DrawFloorTile(pContext, nClientX, pTileData, TRUE, nClientX, nClientY, nTileX, nTileY);
	}
}

//D2Client.0x6FAA3330
void __fastcall DFLOOR_DrawFloor(D2FloorDrawContextStrc* pContext, int32_t nUnused, D2GameViewStrc* pView)
{
	pContext->bLowQuality = D2GFX_CheckLowQuality();
	pContext->bPerspective = D2GFX_CheckPerspective();

	const uint32_t nFrame = sub_6FAABF80();
	pContext->bSpawnFloorParticles = FALSE;
	pContext->bSpawnFloorSplashes = FALSE;
	pContext->nFloorParticleChance = (int32_t)sub_6FAA88B0();

	const int32_t nScreenPanels = sub_6FAB5750();
	pContext->nScreenPanels = nScreenPanels;
	pContext->pView = pView;

	BOOL bDrawEdges = FALSE;
	if (D2ActiveRoomStrc* pRoom = CUNIT_GetPlayerRoom())
	{
		D2LevelsTxt* pLevelsTxtRecord = DATATBLS_GetLevelsTxtRecord(DUNGEON_GetLevelIdFromRoom(pRoom));
		if (pLevelsTxtRecord->nDrawEdges && !nScreenPanels && D2GFX_GetResolutionMode() == 2)
		{
			bDrawEdges = TRUE;
		}
	}

	pContext->bDrawEdges = bDrawEdges;
	pContext->nMaxX = INT32_MIN;
	pContext->nMaxY = INT32_MIN;
	pContext->nMinX = INT32_MAX;
	pContext->nMinY = INT32_MAX;
	pContext->nOffsetX = 80 - pContext->pView->nViewX;
	pContext->nOffsetY = -80 - pContext->pView->nViewY;

	if (pContext->dwLastFloorParticleTick + 3 < nFrame)
	{
		pContext->dwLastFloorParticleTick = nFrame;
		if (pContext->nFloorParticleChance)
		{
			pContext->bSpawnFloorParticles = TRUE;
		}
	}

	if (sub_6FAA7900() && pContext->dwLastFloorSplashTick + 25 < nFrame)
	{
		pContext->dwLastFloorSplashTick = nFrame;
		pContext->bSpawnFloorSplashes = TRUE;
	}

	D2UnitStrc* pPlayer = CUNIT_GetPlayer();
	D2_ASSERT(pPlayer);
	pContext->pSeed = &pPlayer->pSeed;

	D2ActiveRoomStrc* pRoom = CUNIT_GetPlayerRoom();
	if (!pRoom)
	{
		return;
	}

	D2ActiveRoomStrc** ppRoomList = nullptr;
	int32_t nNumRooms = 0;
	DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppRoomList, &nNumRooms);

	D2LevelsTxt* pLevelsTxtRecord = DATATBLS_GetLevelsTxtRecord(DUNGEON_GetLevelIdFromRoom(pRoom));
	D2_ASSERT(pLevelsTxtRecord);

	const BOOL bNoFloorFilter = pLevelsTxtRecord->dwFloorFilter == 0;

	for (int32_t i = 0; i < nNumRooms; ++i)
	{
		D2DrlgCoordsStrc tCoords = {};
		DUNGEON_GetRoomCoordinates(ppRoomList[i], &tCoords);

		for (uint32_t nLayer = 1; nLayer < 3; ++nLayer)
		{
			const BOOL bFloorFilter = !bNoFloorFilter && nLayer == 1;

			int32_t nFloorTiles = 0;
			D2DrlgTileDataStrc* pTileData = DUNGEON_GetFloorTilesFromRoom(ppRoomList[i], &nFloorTiles);
			for (; nFloorTiles; --nFloorTiles, ++pTileData)
			{
				if (((pTileData->dwFlags >> 14) & 7) == nLayer)
				{
					const int32_t nYPos = pTileData->nHeight + pContext->nOffsetY;
					DFLOOR_DrawFloorTile(pContext, nYPos, pTileData, bFloorFilter, pTileData->nWidth + pContext->nOffsetX, nYPos, tCoords.nSubtileX + 5 * pTileData->nPosX, tCoords.nSubtileY + 5 * pTileData->nPosY);
				}
			}
		}
	}

	if (!pContext->bDrawEdges)
	{
		return;
	}

	const int32_t nMarginLeft = pContext->bPerspective ? 33 : 30;
	const int32_t nMarginRight = pContext->bPerspective ? 23 : 25;

	if (!pPlayer)
	{
		return;
	}

	const int32_t nPlayerX = DFLOOR_GetUnitClientX(pPlayer);
	const int32_t nPlayerY = DFLOOR_GetUnitClientY(pPlayer);

	if (nPlayerX - pContext->nMinX < nMarginLeft)
	{
		const int32_t nX = 5 * ((pContext->nMinX - 5) / 5);
		const int32_t nY = 5 * (nPlayerY / 5);
		DFLOOR_DrawSingleEdgeTile(pContext, nX, nY + 5, nX, nY);
		DFLOOR_DrawSingleEdgeTile(pContext, nX, nY, nX, nY - 5);
		DFLOOR_DrawEdgeTile(pContext, 0, nX, nY - 10);
	}

	if (pContext->nMaxX - nPlayerX < nMarginRight)
	{
		const int32_t nX = 5 * ((pContext->nMaxX + 5) / 5);
		const int32_t nY = 5 * (nPlayerY / 5);
		DFLOOR_DrawSingleEdgeTile(pContext, nX, nY + 5, nX, nY);
		DFLOOR_DrawSingleEdgeTile(pContext, nX, nY + 10, nX, nY + 5);
		DFLOOR_DrawEdgeTile(pContext, 0, nX, nY + 10);
	}

	if (nPlayerY - pContext->nMinY < nMarginLeft)
	{
		const int32_t nX = 5 * (nPlayerX / 5);
		const int32_t nY = 5 * ((pContext->nMinY - 5) / 5);
		DFLOOR_DrawSingleEdgeTile(pContext, nX, nY + 5, nX, nY);
		DFLOOR_DrawSingleEdgeTile(pContext, nX - 5, nY + 5, nX - 5, nY);
		DFLOOR_DrawEdgeTile(pContext, 0, nX - 10, nY);
	}

	if (pContext->nMaxY - nPlayerY < nMarginRight)
	{
		const int32_t nX = 5 * (nPlayerX / 5);
		const int32_t nY = 5 * ((pContext->nMaxY + 5) / 5);
		DFLOOR_DrawSingleEdgeTile(pContext, nX, nY + 5, nX, nY);
		DFLOOR_DrawSingleEdgeTile(pContext, nX + 5, nY + 5, nX + 5, nY);
		DFLOOR_DrawEdgeTile(pContext, 0, nX + 10, nY);
	}
}

//D2Client.0x6FAA3B90
void __fastcall DFLOOR_DrawRoofTiles(D2GameViewStrc* pView)
{
	const uint32_t dwTickCount = GetTickCount();
	const int32_t nDisplayType = WNDPROC_GetDisplayType();
	const BOOL bPerspective = D2GFX_CheckPerspective();
	const BOOL bLowQuality = D2GFX_CheckLowQuality();
	const int32_t nViewX = pView->nViewX;
	const int32_t nViewY = pView->nViewY;
	const int32_t nCells = pView->nTileGridSize * pView->nTileGridSize;
	const int32_t nScreenPanels = sub_6FAB5750();

	for (uint32_t nLayer = 1; nLayer <= 4; ++nLayer)
	{
		const uint32_t nLayerFlag = nLayer << 14;
		for (int32_t i = 0; i < nCells; ++i)
		{
			for (D2ViewTileNodeStrc* pNode = pView->pTileGrid[i].pFirstNode; pNode; pNode = pNode->pNext)
			{
				D2DrlgTileDataStrc* pTileData = pNode->pTileData;
				uint32_t dwFlags = pTileData->dwFlags;
				if ((dwFlags & nLayerFlag) != nLayerFlag)
				{
					continue;
				}

				// unk0x24 & 2: alpha is fading, nRed is the current alpha, nGreen the start alpha, nBlue the target alpha and unk0x2C the end tick
				if (pTileData->unk0x24 & 2)
				{
					if (nDisplayType < DISPLAYTYPE_GLIDE || (uint32_t)pTileData->unk0x2C <= dwTickCount)
					{
						pTileData->nRed = pTileData->nBlue;
						pTileData->unk0x24 &= ~2;
					}
					else
					{
						const int32_t nDelta = (pTileData->nBlue - pTileData->nGreen) * (int32_t)(dwTickCount - pTileData->unk0x2C + 500);
						pTileData->nRed = (uint8_t)(nDelta / 500) + pTileData->nGreen;
					}

					if (pTileData->nRed)
					{
						dwFlags &= ~0x400;
					}
					else
					{
						dwFlags |= 0x400;
					}
					pTileData->dwFlags = dwFlags;
				}

				if (pTileData->dwFlags & 0x408)
				{
					continue;
				}

				D2TileLibraryEntryStrc* pTile = pTileData->pTile;
				const int32_t nXPos = pTileData->nWidth + 80 - nViewX;
				const int32_t nYPos = pTileData->nHeight - pTile->nRoofHeight - 80 - nViewY;

				const RECT* ptRect = &pView->tViewRect;
				D2_ASSERT(ptRect);

				if (nXPos < ptRect->left || nXPos >= ptRect->right || nYPos < ptRect->top || nYPos >= ptRect->bottom)
				{
					continue;
				}

				const int32_t nWorldX = pNode->nX >> 3;
				const int32_t nWorldY = pNode->nY >> 3;
				if (WNDPROC_GetDisplayType() < DISPLAYTYPE_GLIDE)
				{
					D2GfxLightExStrc aLights[64];
					DFLOOR_ComputeTileLights(aLights, nWorldX, nWorldY, pTile->nRoofHeight);
					D2GFX_FloorTileDraw(pTileData->pTile, aLights, nXPos, nYPos, nWorldX, nWorldY, pTileData->nRed, nScreenPanels, nullptr);
				}
				else
				{
					D2GfxLightExStrc aLights[36];
					if (!bPerspective)
					{
						DFLOOR_ComputeTileLightsEx(aLights, nXPos, nYPos, nWorldX, nWorldY, pTile->nRoofHeight, nScreenPanels, bLowQuality);
					}
					else
					{
						DFLOOR_ComputeTileLightsPerspective(aLights, nWorldX, nWorldY, pTile->nRoofHeight, nScreenPanels, bLowQuality);
					}
					D2GFX_FloorTileDraw(pTileData->pTile, aLights, nXPos, nYPos, nWorldX, nWorldY, pTileData->nRed, nScreenPanels, nullptr);
				}

				pTileData->dwFlags |= 0x20000;
			}
		}
	}
}

//D2Client.0x6FAA3E70
void __fastcall DFLOOR_ComputeTileLights(D2GfxLightExStrc* pLights, int32_t nWorldX, int32_t nWorldY, int32_t nHeight)
{
	if (nHeight)
	{
		const uint8_t nIntensity = (uint8_t)ENVIRONMENT_GetIntensityFromAct(ghAct);
		uint8_t nRed = 0;
		uint8_t nGreen = 0;
		uint8_t nBlue = 0;
		ENVIRONMENT_GetLightColorFromAct(ghAct, &nRed, &nGreen, &nBlue);

		for (int32_t i = 0; i < 64; ++i)
		{
			pLights[i].nIntensity = nIntensity;
			pLights[i].nRed = nRed;
			pLights[i].nBlue = nBlue;
			pLights[i].nGreen = nGreen;
		}
		return;
	}

	D2GfxLightExStrc* pLight = pLights;
	for (int32_t nRow = 0; nRow < 8; ++nRow)
	{
		for (int32_t nColumn = 0; nColumn < 8; ++nColumn)
		{
			sub_6FAA60B0(8 * (nWorldX + nColumn) - 8, 8 * (nWorldY + nRow) - 8, &pLight->nIntensity, &pLight->nRed, &pLight->nGreen, &pLight->nBlue);
			++pLight;
		}
	}
}

//D2Client.0x6FAA3F40
void __fastcall DFLOOR_ComputeTileLightsEx(D2GfxLightExStrc* pLights, int32_t nXPos, int32_t nYPos, int32_t nWorldX, int32_t nWorldY, int32_t nHeight, int32_t nScreenPanels, BOOL bLowQuality)
{
	const uint8_t nIntensity = (uint8_t)ENVIRONMENT_GetIntensityFromAct(ghAct);
	const int32_t nX = nXPos + DFLOOR_GetScreenPanelsOffset(nScreenPanels);

	uint8_t nRed = 0;
	uint8_t nGreen = 0;
	uint8_t nBlue = 0;
	ENVIRONMENT_GetLightColorFromAct(ghAct, &nRed, &nGreen, &nBlue);

	D2GfxLightExStrc* pLight = pLights;
	for (int32_t nRow = 0; nRow < 6; ++nRow)
	{
		for (int32_t nColumn = 0; nColumn < 6; ++nColumn)
		{
			if (!bLowQuality || (nColumn == 0 || nColumn == 5) && (nRow == 0 || nRow == 5))
			{
				pLight->nX = nX + 16 * (nColumn - nRow);
				pLight->nY = nYPos + 8 * (nColumn + nRow);
				if (nHeight)
				{
					pLight->nIntensity = nIntensity;
					pLight->nRed = nRed;
					pLight->nBlue = nBlue;
					pLight->nGreen = nGreen;
				}
				else
				{
					sub_6FAA60B0(8 * (nColumn + nWorldX), 8 * (nWorldY + nRow), &pLight->nIntensity, &pLight->nRed, &pLight->nGreen, &pLight->nBlue);
				}
			}
			++pLight;
		}
	}
}

//D2Client.0x6FAA4060
void __fastcall DFLOOR_ComputeTileLightsPerspective(D2GfxLightExStrc* pLights, int32_t nWorldX, int32_t nWorldY, int32_t nHeight, int32_t nScreenPanels, BOOL bLowQuality)
{
	const uint8_t nIntensity = (uint8_t)ENVIRONMENT_GetIntensityFromAct(ghAct);
	const int32_t nOffsetX = DFLOOR_GetScreenPanelsOffset(nScreenPanels);

	uint8_t nRed = 0;
	uint8_t nGreen = 0;
	uint8_t nBlue = 0;
	ENVIRONMENT_GetLightColorFromAct(ghAct, &nRed, &nGreen, &nBlue);

	D2GfxLightExStrc* pLight = pLights;
	for (int32_t nRow = 0; nRow < 6; ++nRow)
	{
		for (int32_t nColumn = 0; nColumn < 6; ++nColumn)
		{
			if (!bLowQuality || (nColumn == 0 || nColumn == 5) && (nRow == 0 || nRow == 5))
			{
				SCALE_AdjustPerspectivePosition((nWorldX + nColumn) << 16, (nRow + nWorldY) << 16, nHeight, &pLight->nX, &pLight->nY);
				pLight->nX += nOffsetX;

				if (nHeight)
				{
					pLight->nIntensity = nIntensity;
					pLight->nRed = nRed;
					pLight->nBlue = nBlue;
					pLight->nGreen = nGreen;
				}
				else
				{
					sub_6FAA60B0(8 * (nWorldX + nColumn), 8 * (nRow + nWorldY), &pLight->nIntensity, &pLight->nRed, &pLight->nGreen, &pLight->nBlue);
				}
			}
			++pLight;
		}
	}
}

//D2Client.0x6FAA4210
int32_t __fastcall DFLOOR_ApproximateDistance(int32_t nX, int32_t nY)
{
	const int32_t nAbsX = std::abs(nX);
	const int32_t nAbsY = std::abs(nY);

	if (nAbsX >= nAbsY)
	{
		return (uint32_t)(nAbsX * 983 + nAbsY * 407) >> 10;
	}

	return (uint32_t)(nAbsY * 983 + nAbsX * 407) >> 10;
}
