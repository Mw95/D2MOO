#include "Game/Wall2.h"

#include "Core/WinMain.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Select.h"
#include "Quest/Quests.h"
#include "UI/NpcMenu.h"
#include "UI/QuestLog.h"
#include "UI/Text.h"
#include "Unit/CUnit.h"

//D2Client.0x6FB77264
int32_t dword_6FB77264 = 1;
//D2Client.0x6FBAF900
int32_t dword_6FBAF900;
//D2Client.0x6FBAF904
uint32_t dword_6FBAF904;
//D2Client.0x6FBAF908
uint32_t dword_6FBAF908;
//D2Client.0x6FBAF90C
uint8_t byte_6FBAF90C;
//D2Client.0x6FBAF910
uint8_t byte_6FBAF910;
//D2Client.0x6FBAF914
uint8_t byte_6FBAF914;
//D2Client.0x6FBAF918
uint8_t byte_6FBAF918;
//D2Client.0x6FBAF91C
uint32_t dword_6FBAF91C;

//D2Client.0x6FAB7F20
void __fastcall sub_6FAB7F20(int a1)
{
	if (*(void**)(a1 + 0xeaa8) != nullptr)
	{
		D2_FREE(*(void**)(a1 + 0xeaa8));
	}
	*(uint32_t*)(a1 + 0xeaa8) = 0;
	*(uint32_t*)(a1 + 0xeab0) = 0;
	*(uint32_t*)(a1 + 0xea9c) = 0;
	*(uint32_t*)(a1 + 0x38) = 0;
}

//D2Client.0x6FAB7F60
void __fastcall sub_6FAB7F60(int a1, uint32_t a2)
{
	void* pvVar1;
	int iVar2;
	int yTop;
	uint32_t uVar3;
	D2UnitStrc* pUnit;
	int32_t DVar4;
	int32_t nY;
	D2ActiveRoomStrc* pRoom;
	int iVar5;
	uint32_t uVar6;
	int iVar7;
	uint32_t uVar8;
	int iVar9;
	uint32_t* puVar10;
	int iStack_24;
	int iStack_20;
	int local_1c;
	tagRECT tStack_18;
	D2ActiveRoomStrc* pDStack_8;
	uint32_t local_4;

	iVar5 = (*(int*)(a1 + 0xc) - *(int*)(a1 + 4)) / 0xa0 + 0xb;
	iVar2 = (*(int*)(a1 + 0x10) - *(int*)(a1 + 8)) / 0x50;
	pvVar1 = *(void**)(a1 + 0xeaa8);
	iVar7 = iVar2 + 0xb + iVar5;
	iVar9 = iVar7 * iVar7;
	if (pvVar1 != nullptr)
	{
		if (iVar9 - *(int*)(a1 + 0xeaac) == 0)
			goto LAB_6fab7ff8;
		if (pvVar1 != nullptr)
		{
			D2_FREE(pvVar1);
		}
	}
	pvVar1 = D2_ALLOC(iVar9 * 0x24);
	*(void**)(a1 + 0xeaa8) = pvVar1;
	*(int*)(a1 + 0xeaac) = iVar9;
LAB_6fab7ff8:
	*(int*)(a1 + 0xeab8) = iVar2 + 0xc;
	*(int*)(a1 + 0xeab4) = iVar5;
	*(int*)(a1 + 0xeab0) = iVar7;
	local_1c = a1;
	local_4 = a2;
	iVar2 = D2GFX_CheckPerspective();
	iVar5 = *(int*)(a1 + 0x24);
	iVar7 = *(int*)(a1 + 0x28);
	if (iVar2 == 0)
	{
		iVar9 = *(int*)(a1 + 8);
		iVar2 = (iVar5 - *(int*)(a1 + 4)) + *(int*)(a1 + 0xc);
		yTop = iVar7;
	}
	else
	{
		iVar9 = *(int*)(a1 + 8);
		iVar2 = iVar5 - *(int*)(a1 + 4);
		iVar5 = iVar5 + -0x30;
		iVar2 = iVar2 + 0x30 + *(int*)(a1 + 0xc);
		yTop = iVar7 + -0x30;
	}
	SetRect(&tStack_18, iVar5, yTop, iVar2, (*(int*)(a1 + 0x10) - iVar9) + iVar7);
	byte_6FBAF90C = tStack_18.left;
	byte_6FBAF910 = tStack_18.top;
	byte_6FBAF914 = tStack_18.right;
	byte_6FBAF918 = tStack_18.bottom;
	*(uint32_t*)(a1 + 0xea9c) = 0;
	*(uint32_t*)(a1 + 0x38) = 0;
	D2_ASSERT(*(uint32_t**)(a1 + 0xeaa8) != nullptr);
	puVar10 = *(uint32_t**)(a1 + 0xeaa8);
	for (uVar6 = *(int*)(a1 + 0xeaac) * 9 & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1)
	{
		*puVar10 = 0;
		puVar10 = puVar10 + 1;
	}
	for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		*(uint8_t*)puVar10 = 0;
		puVar10 = (uint32_t*)((int)puVar10 + 1);
	}
	DUNGEON_ClientTileDrawPositionToGameCoords(*(int*)(a1 + 0x24), *(int*)(a1 + 0x28), &iStack_24, &iStack_20);
	uVar6 = *(uint32_t*)(a1 + 0xeab0);
	iStack_24 = iStack_24 + -3;
	iStack_20 = iStack_20 - *(int*)(a1 + 0xeab4);
	uVar8 = 0;
	*(int*)(a1 + 0xeaa0) = iStack_24;
	iVar5 = *(int*)(a1 + 0xeaa8);
	*(int*)(a1 + 0xeaa4) = iStack_20;
	if (uVar6 != 0)
	{
		do
		{
			uVar3 = 0;
			iVar7 = iVar5;
			if (uVar6 != 0)
			{
				do
				{
					iVar5 = iVar7 + 0x24;
					*(uint32_t*)(iVar7 + 8) = iStack_24 + uVar3;
					uVar3 = uVar3 + 1;
					*(uint32_t*)(iVar7 + 0xc) = iStack_20 + uVar8;
					iVar7 = iVar5;
				} while (uVar3 < *(uint32_t*)(a1 + 0xeab0));
			}
			uVar6 = *(uint32_t*)(a1 + 0xeab0);
			uVar8 = uVar8 + 1;
		} while (uVar8 < uVar6);
	}
	pUnit = CUNIT_GetPlayer();
	D2_ASSERT(pUnit != nullptr);
	pDStack_8 = CUNIT_GetPlayerRoom();
	uVar6 = pUnit->dwUnitType;
	if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
	{
		uVar6 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		uVar6 = 0;
	}
	else
	{
		uVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	dword_6FBAF908 = uVar6 / 5;
	uVar6 = pUnit->dwUnitType;
	if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
	{
		DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
	}
	else
	{
		DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	dword_6FBAF904 = (uint32_t)DVar4 / 5;
	uVar6 = pUnit->dwUnitType;
	if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
	{
		nY = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
	}
	else
	{
		nY = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	uVar6 = pUnit->dwUnitType;
	if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
	{
		iVar5 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	pRoom = UNITS_GetRoom(pUnit);
	dword_6FBAF900 = D2Common_10095(pRoom, iVar5, (int)nY);
	DUNGEON_CallRoomCallback(pDStack_8, (ROOMCALLBACKFN)(sub_6FAB8290), &local_1c);
}

//D2Client.0x6FAB8290
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAB8290(D2ActiveRoomStrc* pActiveRoom, int* a2)
{
	int iVar1;
	D2TileLibraryEntryStrc* a1;
	int iVar2;
	uint32_t uVar3;
	uint32_t* puVar4;
	uint32_t* puVar5;
	bool bVar6;
	D2DrlgTileDataStrc* pDVar7;
	int iVar8;
	DWORD DVar9;
	uint32_t extraout_var;
	uint32_t* puVar10;
	D2UnitStrc* pUnit;
	uint32_t extraout_var_00;
	D2UnitStrc** ppDVar11;
	uint32_t* puVar12;
	int iVar13;
	uint32_t* puVar14;
	int* piVar15;
	uint32_t* puVar16;
	int iStack_88;
	uint32_t* puStack_84;
	uint32_t* puStack_80;
	uint32_t uStack_7c;
	uint32_t uStack_78;
	int iStack_74;
	tagRECT tStack_70;
	D2DrlgCoordsStrc DStack_60;
	D2DrlgCoordsStrc DStack_40;
	D2DrlgCoordsStrc DStack_20;

	iVar1 = *a2;
	puVar14 = (uint32_t*)(iVar1 + 0x38);
	D2Common_10052(pActiveRoom, &tStack_70);
	if ((((tStack_70.left <= a2[3]) && (tStack_70.top <= a2[4] + 400)) &&
	        (a2[1] + -200 <= tStack_70.right)) &&
	    (a2[2] <= tStack_70.bottom))
	{
		pDVar7 = DUNGEON_GetWallTilesFromRoom(pActiveRoom, (int*)&uStack_7c);
		uStack_78 = 0;
		if (uStack_7c != 0)
		{
			piVar15 = &pDVar7->nTileType;
			do
			{
				a1 = (D2TileLibraryEntryStrc*)piVar15[-1];
				puStack_84 = (uint32_t*)D2CMP_10084((int)a1);
				DUNGEON_ClientTileDrawPositionToGameCoords(((D2DrlgTileDataStrc*)(piVar15 + -7))->nWidth, piVar15[-6], &iStack_74, &iStack_88);
				iVar13 = iStack_88 + -1;
				if (((((D2DrlgTileDataStrc*)(piVar15 + -7))->nWidth <= a2[3]) &&
				        (a2[1] <= ((D2DrlgTileDataStrc*)(piVar15 + -7))->nWidth + 0xa0)) &&
				    ((iVar8 = piVar15[-6] - (uint32_t)a1->nRoofHeight, iVar8 + (int)puStack_84 <= a2[4] &&
				                                                           (a2[2] <= iVar8 - (int)puStack_84))))
				{
					iVar8 = iStack_74 - *(int*)(iVar1 + 0xeaa0);
					iStack_88 = iVar13 - *(int*)(iVar1 + 0xeaa4);
					if (((-1 < iVar8) && (-1 < iStack_88)) &&
					    ((iVar2 = *(int*)(iVar1 + 0xeab0), iVar8 < iVar2 && (iStack_88 < iVar2))))
					{
						puVar12 = (uint32_t*)(*(int*)(iVar1 + 0xeaa8) + (iVar2 * iStack_88 + iVar8) * 0x24);
						*puVar12 = 0;
						uVar3 = piVar15[-2];
						puStack_84 = puVar12;
						iStack_74 = iVar8;
						if ((uVar3 & 0x1c000) == 0)
						{
							sub_6FAB8C60(puVar14, (int)puVar12, (uint32_t)(piVar15 + -7), pActiveRoom);
							iVar13 = iStack_88;
						}
						else
						{
							iVar8 = *piVar15;
							iVar13 = iStack_88;
							if (iVar8 == 0xf)
							{
								uVar3 = *(uint32_t*)(iVar1 + 0xea9c);
								*(uint32_t*)(iVar1 + 0xea9c) = uVar3 + 1;
								if (uVar3 < 3000)
								{
									puVar16 = (uint32_t*)(iVar1 + 0x3c + uVar3 * 0x14);
									puVar16[3] = (uint32_t)((D2DrlgTileDataStrc*)(piVar15 + -7));
									*puVar16 = 1;
									puVar16[4] = 0;
									DUNGEON_GetRoomCoordinates(pActiveRoom, &DStack_20);
									puVar16[1] = (DStack_20.nSubtileX + piVar15[-5] * 5) * 8;
									puVar16[2] = (DStack_20.nSubtileY + piVar15[-4] * 5) * 8;
									*puVar14 = *puVar14 | *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4);
									puVar4 = (uint32_t*)puVar12[7];
									if (puVar4 != nullptr)
									{
										puStack_84 = nullptr;
										puStack_80 = (uint32_t*)(*(uint32_t*)(puVar16[3] + 0x14) >> 0xe & 7);
										for (puVar5 = (uint32_t*)puVar4[4]; puVar10 = puVar4,
										    puVar5 != nullptr;
										     puVar5 = (uint32_t*)puVar5[4])
										{
											if (puStack_80 < (uint32_t*)(*(uint32_t*)(puVar10[3] + 0x14) >> 0xe & 7))
											{
												puVar16[4] = (uint32_t)(puVar10);
												if (puStack_84 == nullptr)
												{
													puVar12[7] = (uint32_t)(puVar16);
												}
												else
												{
													puStack_84[4] = (uint32_t)(puVar16);
												}
												break;
											}
											puVar4 = puVar5;
											puStack_84 = puVar10;
										}
										goto LAB_6fab87e7;
									}
									puVar12[7] = (uint32_t)(puVar16);
									iVar13 = iStack_88;
								}
							}
							else if ((iVar8 < 0x10) || (0x13 < iVar8))
							{
								if ((iVar8 != 0) && ((iVar8 != 0xd && ((uVar3 & 4) == 0))))
								{
									*puVar12 = 4;
								}
								uVar3 = *(uint32_t*)(iVar1 + 0xea9c);
								*(uint32_t*)(iVar1 + 0xea9c) = uVar3 + 1;
								if (uVar3 < 3000)
								{
									DVar9 = GetTickCount();
									iVar13 = DVar9 + 500;
									puVar16 = (uint32_t*)(iVar1 + 0x3c + uVar3 * 0x14);
									*puVar16 = 1;
									puVar16[3] = (uint32_t)((D2DrlgTileDataStrc*)(piVar15 + -7));
									puVar16[4] = 0;
									if ((piVar15[-2] & 4U) == 0)
									{
										bVar6 = sub_6FAB8B50(pActiveRoom, (int)(piVar15 + -7));
										if (D2C_ZEXT(bVar6) == 0)
										{
											puStack_80 = (uint32_t*)piVar15[2];
											if (((uint32_t)puStack_80 & 1) != 0)
											{
												*(uint8_t*)((int)piVar15 + 0xd) = 0x80;
												*(uint8_t*)((int)piVar15 + 0xe) = 0xff;
												if (*(uint8_t*)(piVar15 + 3) == 0x80)
												{
													piVar15[4] = iVar13;
												}
												else
												{
													piVar15[4] = (int)((0x80 - (uint32_t) * (uint8_t*)(piVar15 + 3)) * 500) / 0x7f +
													             iVar13;
												}
												piVar15[2] = (uint32_t)puStack_80 & 0xfffffffe | 2;
											}
										}
										else
										{
											puStack_80 = (uint32_t*)piVar15[2];
											if (((uint32_t)puStack_80 & 1) == 0)
											{
												*(uint8_t*)((int)piVar15 + 0xd) = 0xff;
												*(uint8_t*)((int)piVar15 + 0xe) = 0x80;
												if (*(uint8_t*)(piVar15 + 3) == 0xff)
												{
													piVar15[4] = iVar13;
													piVar15[2] = (uint32_t)puStack_80 | 3;
												}
												else
												{
													piVar15[4] = (int)((*(uint8_t*)(piVar15 + 3) - 0xff) * 500) / 0x7f + iVar13;
													piVar15[2] = (uint32_t)puStack_80 | 3;
												}
											}
										}
									}
									DUNGEON_GetRoomCoordinates(pActiveRoom, &DStack_40);
									puVar16[1] = (DStack_40.nSubtileX + piVar15[-5] * 5) * 8;
									puVar16[2] = (DStack_40.nSubtileY + piVar15[-4] * 5) * 8;
									puVar12 = (uint32_t*)puStack_84[5];
									if (puVar12 != nullptr)
									{
										puStack_80 = (uint32_t*)(*(uint32_t*)(puVar16[3] + 0x14) >> 0xe & 7);
										puVar4 = nullptr;
										for (puVar5 = (uint32_t*)puVar12[4]; puVar10 = puVar12,
										    puVar5 != nullptr;
										     puVar5 = (uint32_t*)puVar5[4])
										{
											if (puStack_80 < (uint32_t*)(*(uint32_t*)(puVar10[3] + 0x14) >> 0xe & 7))
											{
												puVar16[4] = (uint32_t)(puVar10);
												if (puVar4 == nullptr)
												{
													puStack_84[5] = (uint32_t)(puVar16);
												}
												else
												{
													puVar4[4] = (uint32_t)(puVar16);
												}
												break;
											}
											puVar12 = puVar5;
											puVar4 = puVar10;
										}
										goto LAB_6fab87e7;
									}
									puStack_84[5] = (uint32_t)(puVar16);
									iVar13 = iStack_88;
								}
							}
							else
							{
								if (((iVar8 != 0) && (iVar8 != 0xd)) && ((uVar3 & 4) == 0))
								{
									*puVar12 = 4;
								}
								uVar3 = *(uint32_t*)(iVar1 + 0xea9c);
								*(uint32_t*)(iVar1 + 0xea9c) = uVar3 + 1;
								if (uVar3 < 3000)
								{
									puVar16 = (uint32_t*)(iVar1 + 0x3c + uVar3 * 0x14);
									puVar16[3] = (uint32_t)((D2DrlgTileDataStrc*)(piVar15 + -7));
									*puVar16 = 1;
									puVar16[4] = 0;
									DUNGEON_GetRoomCoordinates(pActiveRoom, &DStack_60);
									puVar16[1] = (DStack_60.nSubtileX + piVar15[-5] * 5) * 8;
									puVar16[2] = (DStack_60.nSubtileY + piVar15[-4] * 5) * 8;
									*puVar14 = *puVar14 | *(uint32_t*)((uint8_t*)&gdwBitMasks);
									puVar4 = (uint32_t*)puVar12[8];
									if (puVar4 == nullptr)
									{
										puVar12[8] = (uint32_t)(puVar16);
										iVar13 = iStack_88;
									}
									else
									{
										puStack_80 = nullptr;
										puStack_84 = (uint32_t*)(*(uint32_t*)(puVar16[3] + 0x14) >> 0xe & 7);
										for (puVar5 = (uint32_t*)puVar4[4]; puVar10 = puVar4,
										    puVar5 != nullptr;
										     puVar5 = (uint32_t*)puVar5[4])
										{
											if (puStack_84 < (uint32_t*)(*(uint32_t*)(puVar10[3] + 0x14) >> 0xe & 7))
											{
												puVar16[4] = (uint32_t)(puVar10);
												if (puStack_80 == nullptr)
												{
													puVar12[8] = (uint32_t)(puVar16);
												}
												else
												{
													puStack_80[4] = (uint32_t)(puVar16);
												}
												break;
											}
											puVar4 = puVar5;
											puStack_80 = puVar10;
										}
									LAB_6fab87e7:
										iVar13 = iStack_88;
										if (puVar10[4] == 0)
										{
											puVar10[4] = (uint32_t)(puVar16);
										}
									}
								}
							}
						}
					}
				}
				iStack_88 = iVar13;
				uStack_78 = uStack_78 + 1;
				piVar15 = piVar15 + 0xc;
			} while (uStack_78 < uStack_7c);
		}
		pDVar7 = DUNGEON_GetRoofTilesFromRoom(pActiveRoom, (int*)&uStack_7c);
		uStack_78 = 0;
		if (uStack_7c != 0)
		{
			do
			{
				iVar8 = D2CMP_10084((int)pDVar7->pTile);
				DUNGEON_ClientTileDrawPositionToGameCoords(pDVar7->nWidth, pDVar7->nHeight, (int*)&puStack_84, &iStack_88);
				iVar13 = iStack_88 + -1;
				if (((pDVar7->nWidth <= a2[3]) && (a2[1] <= pDVar7->nWidth + 0xa0)) &&
				    ((iVar8 + pDVar7->nHeight <= a2[4] && (a2[2] <= pDVar7->nHeight - iVar8))))
				{
					puVar12 = (uint32_t*)((int)puStack_84 - *(int*)(iVar1 + 0xeaa0));
					iStack_88 = iVar13 - *(int*)(iVar1 + 0xeaa4);
					if (((-1 < (int)puVar12) && (-1 < iStack_88)) &&
					    ((iVar8 = *(int*)(iVar1 + 0xeab0), (int)puVar12 < iVar8 && (iStack_88 < iVar8))))
					{
						puStack_84 = puVar12;
						sub_6FAB8C60(puVar14, *(int*)(iVar1 + 0xeaa8) + (int)(iVar8 * iStack_88 + (int)puVar12) * 0x24, (uint32_t)pDVar7, pActiveRoom);
						iVar13 = iStack_88;
					}
				}
				iStack_88 = iVar13;
				uStack_78 = uStack_78 + 1;
				pDVar7 = pDVar7 + 1;
			} while (uStack_78 < uStack_7c);
		}
		if (a2[6] == 0)
		{
			for (pUnit = DUNGEON_GetFirstUnitInRoom(pActiveRoom); pUnit != nullptr;
			     pUnit = pUnit->pRoomNext)
			{
				iStack_88 = UNITS_GetClientCoordX(pUnit);
				puStack_80 = (uint32_t*)UNITS_GetClientCoordY(pUnit);
				DUNGEON_ClientTileDrawPositionToGameCoords(iStack_88, (int)puStack_80, &iStack_88, (int*)&puStack_80);
				iVar13 = iStack_88 - *(int*)(iVar1 + 0xeaa0);
				puVar12 = (uint32_t*)((int)puStack_80 - *(int*)(iVar1 + 0xeaa4));
				if ((((-1 < iVar13) && (-1 < (int)puVar12)) &&
				        (iVar8 = *(int*)(iVar1 + 0xeab0), iVar13 < iVar8)) &&
				    ((int)puVar12 < iVar8))
				{
					iStack_88 = iVar13;
					puStack_80 = puVar12;
					D2_ASSERT(!((iVar13 < 0) || (iVar8 <= iVar13)));
					D2_ASSERT(!(((int)puVar12 < 0) || (iVar8 <= (int)puVar12)));
					iVar13 = *(int*)(iVar1 + 0xeaa8) + (iVar8 * (int)puVar12 + iVar13) * 0x24;
					bVar6 = sub_6FB29590(&pUnit->dwUnitType);
					if (D2C_ZEXT(bVar6) == 0)
					{
						if ((pUnit == nullptr) ||
						    (puStack_84 = (uint32_t*)(pUnit->dwFlags >> 0x14 & 1),
						        puStack_84 == nullptr))
						{
							uVar3 = *(uint32_t*)(iVar1 + 0xea9c);
							*(uint32_t*)(iVar1 + 0xea9c) = uVar3 + 1;
							if (uVar3 < 3000)
							{
								puVar12 = (uint32_t*)(iVar1 + 0x3c + uVar3 * 0x14);
								*puVar12 = 0;
								puVar12[3] = (uint32_t)(pUnit);
								puVar12[4] = 0;
								iVar8 = sub_6FAB6A60((int*)pUnit);
								puVar12[1] = iVar8 << 3;
								ppDVar11 = sub_6FAB6A90((int*)pUnit);
								puVar12[2] = (int)ppDVar11 << 3;
								iVar8 = *(int*)(iVar13 + 0x18);
								if (iVar8 == 0)
								{
									*(uint32_t**)(iVar13 + 0x18) = puVar12;
								}
								else
								{
									for (iVar2 = *(int*)(iVar8 + 0x10); iVar2 != 0; iVar2 = *(int*)(iVar2 + 0x10))
									{
										iVar8 = iVar2;
									}
									*(uint32_t**)(iVar8 + 0x10) = puVar12;
								}
							}
							if ((pUnit != nullptr) &&
							    (puStack_84 = (uint32_t*)(pUnit->dwFlagEx >> 7 & 1),
							        puStack_84 != nullptr))
							{
								uVar3 = *(uint32_t*)(iVar1 + 0xea9c);
								*(uint32_t*)(iVar1 + 0xea9c) = uVar3 + 1;
								if (uVar3 < 3000)
								{
									puVar12 = (uint32_t*)(iVar1 + 0x3c + uVar3 * 0x14);
									*puVar12 = 2;
									puVar12[3] = (uint32_t)(pUnit);
									puVar12[4] = 0;
									iVar8 = sub_6FAB6A60((int*)pUnit);
									puVar12[1] = iVar8 << 3;
									ppDVar11 = sub_6FAB6A90((int*)pUnit);
									puVar12[2] = (int)ppDVar11 << 3;
									*puVar14 = *puVar14 | *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0xc);
									iVar8 = *(int*)(iVar13 + 0x10);
									if (iVar8 == 0)
									{
										*(uint32_t**)(iVar13 + 0x10) = puVar12;
									}
									else
									{
										for (iVar13 = *(int*)(iVar8 + 0x10); iVar13 != 0;
										     iVar13 = *(int*)(iVar13 + 0x10))
										{
											iVar8 = iVar13;
										}
										*(uint32_t**)(iVar8 + 0x10) = puVar12;
									}
								}
							}
						}
						else
						{
							sub_6FAB8D20(puVar14, iVar13, (int*)pUnit);
						}
					}
					else
					{
						sub_6FAB8D20(puVar14, iVar13, (int*)pUnit);
					}
				}
			}
		}
	}
	return 1;
}

//D2Client.0x6FAB8B50
bool __fastcall sub_6FAB8B50(D2ActiveRoomStrc* pActiveRoom, int a2)
{
	int* piVar1;
	D2DrlgCoordsStrc local_20;

	if (dword_6FB77264 == 0)
	{
		DUNGEON_GetRoomCoordinates(pActiveRoom, &local_20);
		local_20.nSubtileX = local_20.nSubtileX + *(int*)(a2 + 8) * 5;
		local_20.nSubtileY = local_20.nSubtileY + *(int*)(a2 + 0xc) * 5;
		if (((int)(dword_6FBAF908 * 5) < local_20.nSubtileX) &&
		    (local_20.nSubtileX + -0x14 < (int)(dword_6FBAF908 * 5)))
		{
			switch (*(uint32_t*)(a2 + 0x1c))
			{
			case 1:
			case 4:
			case 5:
			case 7:
			case 8:
			case 10:
			case 0xc:
				goto switchD_6fab8bfc_caseD_1;
			}
		}
		if (((int)(dword_6FBAF904 * 5) < local_20.nSubtileY) &&
		    (local_20.nSubtileY + -0x14 < (int)(dword_6FBAF904 * 5)))
		{
			switch (*(uint32_t*)(a2 + 0x1c))
			{
			case 2:
			case 3:
			case 6:
			case 7:
			case 9:
			case 0xb:
			case 0xc:
				goto switchD_6fab8bfc_caseD_1;
			}
		}
	}
	else
	{
		piVar1 = *(int**)(a2 + 0x10);
		if ((piVar1 != nullptr) && (piVar1[10] != dword_6FBAF900))
		{
			if (*piVar1 <= (int)dword_6FBAF908)
			{
				return (int)dword_6FBAF904 < piVar1[1];
			}
		switchD_6fab8bfc_caseD_1:
			return true;
		}
	}
	return false;
}

//D2Client.0x6FAB8C60
void __fastcall sub_6FAB8C60(uint32_t* a1, int a2, uint32_t a3, D2ActiveRoomStrc* pActiveRoom)
{
	uint32_t* puVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	D2DrlgCoordsStrc local_20;

	uVar2 = a1[0x3a99];
	a1[0x3a99] = uVar2 + 1;
	if (uVar2 < 3000)
	{
		puVar1 = a1 + uVar2 * 5 + 1;
		*puVar1 = 1;
		puVar1[3] = a3;
		puVar1[4] = 0;
		DUNGEON_GetRoomCoordinates(pActiveRoom, &local_20);
		puVar1[1] = (local_20.nSubtileX + *(int*)(a3 + 8) * 5) * 8;
		puVar1[2] = (local_20.nSubtileY + *(int*)(a3 + 0xc) * 5) * 8;
		*a1 = *a1 | *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0xc);
		iVar3 = *(int*)(a2 + 0x10);
		if (iVar3 == 0)
		{
			*(uint32_t**)(a2 + 0x10) = puVar1;
			return;
		}
		for (iVar4 = *(int*)(iVar3 + 0x10); iVar4 != 0; iVar4 = *(int*)(iVar4 + 0x10))
		{
			iVar3 = iVar4;
		}
		*(uint32_t**)(iVar3 + 0x10) = puVar1;
	}
}

//D2Client.0x6FAB8D20
void __fastcall sub_6FAB8D20(uint32_t* a1, int a2, int* a3)
{
	uint32_t* puVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;

	uVar2 = a1[0x3a99];
	a1[0x3a99] = uVar2 + 1;
	if (uVar2 < 3000)
	{
		puVar1 = a1 + uVar2 * 5 + 1;
		*puVar1 = 0;
		puVar1[3] = (uint32_t)a3;
		puVar1[4] = 0;
		iVar4 = *a3;
		if ((iVar4 == 2) || ((3 < iVar4 && (iVar4 < 6))))
		{
			iVar4 = *(int*)(a3[0xb] + 0xc);
		}
		else if ((D2DynamicPathStrc*)a3[0xb] == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetXPosition((D2DynamicPathStrc*)a3[0xb]);
		}
		puVar1[1] = iVar4 * 8;
		iVar4 = *a3;
		if ((iVar4 == 2) || ((3 < iVar4 && (iVar4 < 6))))
		{
			iVar4 = *(int*)(a3[0xb] + 0x10);
		}
		else if ((D2DynamicPathStrc*)a3[0xb] == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetYPosition((D2DynamicPathStrc*)a3[0xb]);
		}
		puVar1[2] = iVar4 << 3;
		*a1 = *a1 | *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0xc);
		iVar4 = *(int*)(a2 + 0x10);
		if (*(int*)(a2 + 0x10) == 0)
		{
			*(uint32_t**)(a2 + 0x10) = puVar1;
			return;
		}
		do
		{
			iVar3 = *(int*)(iVar4 + 0x10);
			if (iVar3 == 0)
				break;
			iVar4 = iVar3;
		} while (iVar3 != 0);
		*(uint32_t**)(iVar4 + 0x10) = puVar1;
	}
}

//D2Client.0x6FAB8E00
void __fastcall sub_6FAB8E00(int a1)
{
	switch ((uint32_t) * (uint16_t*)(a1 + 1))
	{
	case 1:
		sub_6FB06280(a1);
		return;
	case 2:
		sub_6FAFBE30(*(short*)(a1 + 3));
		return;
	case 3:
	case 6:
		sub_6FAF7F40(a1);
		return;
	case 4:
	case 0xd:
		sub_6FB1EDF0(a1);
		return;
	default:
		FOG_Trace("Invalid %d Quest data\n", (uint32_t) * (uint16_t*)(a1 + 1));
		return;
	case 0x17:
		sub_6FAAD420((int32_t)a1);
		CLIENT_SetExitToMenu(0);
		sub_6FAA9430(1);
		sub_6FAAB240();
		return;
	case 0x24:
		sub_6FB06ED0((uint32_t) * (uint16_t*)(a1 + 3));
		return;
	}
}

//D2Client.0x6FAB8EC0
void __fastcall sub_6FAB8EC0(int a1)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t* puVar3;

	puVar2 = (uint32_t*)(a1 + 1);
	puVar3 = &dword_6FBAF91C;
	for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar3 = *puVar2;
		puVar2 = puVar2 + 1;
		puVar3 = puVar3 + 1;
	}
	*(uint8_t*)puVar3 = *(uint8_t*)puVar2;
	sgbInit = 1;
}
