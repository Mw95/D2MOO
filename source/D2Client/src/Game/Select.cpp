#include "Game/Select.h"

#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/RosterPets.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Game/View.h"
#include "Quest/QuestsFX.h"
#include "UI/NpcMenu.h"
#include "UI/Text.h"
#include "Unit/CUnit.h"
#include "Unit/PlrSkills.h"

//D2Client.0x6FB6E27C
uint8_t byte_6FB6E27C[32] = {0, 0, 0, 0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2};
//D2Client.0x6FB6E29C
uint8_t byte_6FB6E29C[32] = {3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2};
//D2Client.0x6FB6E2BC
uint32_t dword_6FB6E2BC;
//D2Client.0x6FB6E2CF
uint8_t tbl_6FB6E2CF[1];
//D2Client.0x6FB77080
uint32_t dword_6FB77080 = 0x13;
//D2Client.0x6FB77084
uint32_t dword_6FB77084 = 0x13;
//D2Client.0x6FB77088
uint8_t byte_6FB77088[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0xFA, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0xFC, 0xFF, 0xFF, 0xFF};
//D2Client.0x6FBAB9CC
int32_t dword_6FBAB9CC;
//D2Client.0x6FBAB9D0
uint32_t dword_6FBAB9D0;
//D2Client.0x6FBAB9D4
int32_t dword_6FBAB9D4;
//D2Client.0x6FBAB9D8
int32_t dword_6FBAB9D8;
//D2Client.0x6FBAB9DC
int32_t dword_6FBAB9DC;
//D2Client.0x6FBAB9E0
int32_t dword_6FBAB9E0;
//D2Client.0x6FBAB9E4
uint32_t dword_6FBAB9E4;
//D2Client.0x6FBAB9E8
int32_t dword_6FBAB9E8;
//D2Client.0x6FBAB9EC
uint32_t dword_6FBAB9EC;
//D2Client.0x6FBAB9F0
int32_t dword_6FBAB9F0;
//D2Client.0x6FBAB9F4
int32_t dword_6FBAB9F4;
//D2Client.0x6FBAB9F8
D2ActiveRoomStrc* gpActiveRoom_6FBAB9F8;

//D2Client.0x6FAB5AE0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAB5AE0(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	bool bVar3;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;
	uint32_t uVar5;
	D2ActiveRoomStrc* pDVar6;
	int iVar7;
	DWORD DVar8;
	uint32_t extraout_ECX;
	int iVar9;
	char acStack_200[512];

	if (dword_6FBAB9EC != 0)
	{
		return;
	}
	bVar3 = sub_6FB1EE90();
	if ((D2C_ZEXT(bVar3) != 0) && (pDVar4 = sub_6FB1D380(), pDVar4 == pUnit))
	{
		sub_6FB1B1D0((int)pUnit);
		return;
	}
	sub_6FB1B1F0();
	bVar3 = false;
	if (pUnit != nullptr)
	{
		uVar5 = sub_6FB286F0(pUnit, 0, 0, 0);
		if (uVar5 == 0)
		{
			FOG_DisplayWarning("UnitTestSelect (hUnit, 0, 0, FALSE)",
			    __FILE__, __LINE__);
		}
		if (dword_6FBAB9E8 == 0)
			goto LAB_6fab5bb2;
		if ((pUnit->dwUnitType == dword_6FBAB9CC) && (pUnit->dwUnitId == dword_6FBAB9D0))
		{
			bVar3 = true;
			goto LAB_6fab5bb2;
		}
	}
	if ((dword_6FBAB9E8 != 0) &&
	    ((dword_6FBAB9CC == 5 && (pDVar4 = sub_6FB269F0(dword_6FBAB9D0, 5), pDVar4 != nullptr))))
	{
		iVar7 = pDVar4->dwClassId;
		pDVar6 = UNITS_GetRoom(pDVar4);
		DUNGEON_UpdateWarpRoomDeselect(pDVar6, iVar7);
		sub_6FAB70F0((uint32_t*)dword_6FBA7990);
	}
LAB_6fab5bb2:
	if (pUnit == nullptr)
	{
		dword_6FBAB9E8 = (int)pUnit;
		return;
	}
	dword_6FBAB9CC = pUnit->dwUnitType;
	dword_6FBAB9D0 = pUnit->dwUnitId;
	dword_6FBAB9E8 = 1;
	if (dword_6FBAB9CC == 1)
	{
		if ((!bVar3) && (iVar7 = pUnit->dwClassId, -1 < iVar7))
		{
			iVar2 = *(int*)((uint8_t*)&sgptDataTables);
			if (iVar7 < *(int*)(iVar2 + 0xa80))
			{
				iVar1 = *(int*)(iVar2 + 0xa78) + iVar7 * 0x1a8;
				if ((((((iVar1 != 0) && (-1 < iVar7)) && (iVar7 < *(int*)(iVar2 + 0xa80))) &&
				         (((iVar9 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar7 * 0x1a8), -1 < iVar9 && (iVar9 < *(int*)(iVar2 + 0xa98))) &&
				             ((iVar2 = *(int*)(iVar2 + 0xa90) + iVar9 * 0x134, iVar2 != 0 &&
				                                                                   ((((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar1 + 0xd)) == 0 &&
				                                                                       (*(char*)(iVar1 + 0x4c) != '\x01')))))))) &&
				        (((uint8_t) * (uint32_t*)(((uint8_t*)&gdwBitMasks) + 4) & *(uint8_t*)(iVar2 + 5)) != 0)) &&
				    (dword_6FB77080 = iVar7,
				        (*(uint8_t*)(iVar2 + 6) & (uint8_t) * (uint32_t*)(((uint8_t*)&gdwBitMasks) + 4)) == 0))
				{
					dword_6FB77084 = iVar7;
				}
			}
		}
	}
	else if (dword_6FBAB9CC == 2)
	{
		iVar7 = UNITS_IsDoor(pUnit);
		if (((iVar7 != 0) && (pUnit->dwAnimMode != 4)) &&
		    (DVar8 = GetTickCount(), 500 < DVar8 - pUnit->dwTickCount))
		{
			sprintf(acStack_200, "msg at %d\n", DVar8);
			OutputDebugStringA(acStack_200);
			pUnit->dwTickCount = DVar8;
			sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x3d), dword_6FBAB9D0);
			return;
		}
	}
	else if ((dword_6FBAB9CC == 5) && (!bVar3))
	{
		iVar7 = pUnit->dwClassId;
		pDVar6 = UNITS_GetRoom(pUnit);
		DUNGEON_UpdateWarpRoomSelect(pDVar6, iVar7);
		sub_6FAB70F0((uint32_t*)dword_6FBA7990);
		return;
	}
}

//D2Client.0x6FAB5D40
void __cdecl sub_6FAB5D40()
{
	dword_6FBAB9EC = 0;
	dword_6FBAB9E8 = 0;
}

//D2Client.0x6FAB5D50
void __cdecl sub_6FAB5D50()
{
	dword_6FBAB9EC = 0;
}

//D2Client.0x6FAB5D60
void __cdecl sub_6FAB5D60()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar7;
	uint32_t uVar8;
	D2ObjectsTxt* pDVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	D2UnitStrc* pDVar14;
	D2UnitStrc* pMonster;
	D2UnitStrc* pMonster_00;
	D2UnitStrc* pDStack_68;
	int iStack_64;
	int iStack_60;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_54;
	D2UnitStrc* pDStack_50;
	int iStack_4c;
	int32_t DStack_48;
	int iStack_44;
	int iStack_40;
	uint32_t uStack_3c;
	uint32_t uStack_38;
	D2ActiveRoomStrc** ppDStack_34;
	D2CoordStrc DStack_30;
	D2CoordStrc DStack_28;
	D2CoordStrc DStack_20;
	D2CoordStrc DStack_18;
	D2CoordStrc DStack_10;
	D2CoordStrc DStack_8;

	if (dword_6FBAB9EC != 0)
	{
		return;
	}
	iVar2 = sub_6FAB5750();
	if (iVar2 == 3)
	{
		sub_6FAB5AE0(nullptr);
		return;
	}
	iVar3 = sub_6FB57BC0();
	iVar4 = sub_6FB57BD0();
	if (gnScreenHeight + -0x31 < iVar4)
	{
		sub_6FAB5AE0(nullptr);
		return;
	}
	if ((((dword_6FBAB9F0 != 0) && (dword_6FBAB9D4 < iVar3)) && (iVar3 < dword_6FBAB9DC)) &&
	    ((dword_6FBAB9D8 < iVar4 && (iVar4 < dword_6FBAB9E0))))
	{
		sub_6FAB5AE0(nullptr);
		return;
	}
	if (iVar2 == 1)
	{
		if (gnScreenWidth / 2 <= iVar3)
		{
			sub_6FAB5AE0(nullptr);
			return;
		}
	}
	else if ((iVar2 == 2) && (iVar3 < gnScreenWidth / 2))
	{
		sub_6FAB5AE0(nullptr);
		return;
	}
	iVar2 = D2GFX_CheckPerspective();
	if (iVar2 != 0)
	{
		iVar2 = (int)((uint64_t)((int64_t)iVar4 * -0x66666667) >> 0x20);
		iVar4 = iVar4 + ((iVar2 >> 4) - (iVar2 >> 0x1f));
		iVar3 = iVar3 + ((0x28 - ((int)((iVar4 >> 0x1f & 3U) + iVar4) >> 2)) *
		                    (iVar3 - gnScreenWidth / 2)) /
		                    (gnScreenWidth / 2);
	}
	iVar2 = sub_6FAB5890();
	uStack_3c = iVar3 + iVar2;
	iVar5 = sub_6FAB58A0();
	iVar4 = iVar4 + iVar5;
	iStack_40 = iVar4;
	if (dword_6FBAB9E8 != 0)
	{
		pDStack_58 = sub_6FB269F0(dword_6FBAB9D0, dword_6FBAB9CC);
		if ((pDStack_58 != nullptr) && (uVar6 = sub_6FB286F0(pDStack_58, 0, 0, 0), uVar6 != 0))
		{
			uVar6 = sub_6FB286F0(pDStack_58, iVar3 + iVar2, iVar4, 1);
			if ((uVar6 != 0) && ((pDStack_58->dwUnitType != 4 || (dword_6FBAB9E4 == 0))))
			{
				sub_6FAB5AE0(pDStack_58);
				return;
			}
			goto LAB_6fab5efe;
		}
		dword_6FBAB9EC = 0;
		dword_6FBAB9E8 = 0;
	}
	pDStack_58 = nullptr;
LAB_6fab5efe:
	pUnit = CUNIT_GetPlayer();
	if ((pUnit != nullptr) &&
	    (pRoom = UNITS_GetRoom(pUnit), pRoom != nullptr))
	{
		if (gpActiveRoom_6FBAB9F8 != pRoom)
		{
			dword_6FBAB9F4 = 1;
		}
		uVar6 = pUnit->dwUnitType;
		gpActiveRoom_6FBAB9F8 = pRoom;
		if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
		{
			iStack_44 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_44 = 0;
		}
		else
		{
			iStack_44 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar6 = pUnit->dwUnitType;
		if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
		{
			DStack_48 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_48 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_48 + 2)) = 0;
		}
		else
		{
			DStack_48 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		DUNGEON_GameSubtileToClientCoords(&iStack_44, (int*)&DStack_48);
		pDVar14 = nullptr;
		pDStack_68 = nullptr;
		DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_34, (int*)&uStack_38);
		uStack_54 = 0;
		pMonster = pDVar14;
		if (uStack_38 != 0)
		{
			do
			{
				pDStack_50 = nullptr;
				iStack_4c = 0;
				pMonster_00 = ppDStack_34[uStack_54]->pUnitFirst;
				pDVar14 = pMonster;
				pDVar1 = pDStack_68;
				if (pMonster_00 != nullptr)
				{
					if (pMonster_00 != nullptr)
						goto LAB_6fab5ff7;
					uVar6 = 6;
					while (pDVar14 = pMonster, pDVar1 = pDStack_68, pDStack_50 != pMonster_00)
					{
						iVar2 = iStack_4c + 1;
						if (30000 < iStack_4c)
						{
							FOG_DisplayWarning("Far too many units on screen",
							    __FILE__, __LINE__);
							break;
						}
						pDStack_50 = pMonster_00;
						iStack_4c = iVar2;
						if (pMonster_00 != pUnit)
						{
							if (pMonster_00 != nullptr)
							{
								if ((((pMonster_00->dwUnitType == 5) &&
								         (iVar2 = sub_6FB284D0(pMonster_00, iStack_44, DStack_48), iVar2 != 0)) &&
								        (iVar2 = sub_6FB284D0(pMonster_00, uStack_3c, iStack_40), iVar2 != 0)) &&
								    ((iVar2 = UNITS_IsInMovingMode(pUnit), iVar2 != 0 &&
								                                               (iVar2 = sub_6FAA8BB0(), iVar2 != 0))))
								{
									uVar7 = sub_6FAABFA0();
									uVar8 = sub_6FAABF90();
									if (uVar8 < uVar7)
									{
										iVar2 = sub_6FAABF90();
										sub_6FAABFB0(iVar2 + 500);
										goto LAB_6fab63d5;
									}
									if (dword_6FBAB9F4 == 0)
									{
										iVar2 = sub_6FAABF90();
										sub_6FAABFB0(iVar2 + 500);
										dword_6FBAB9F4 = 1;
									}
								}
								if ((pMonster_00->dwUnitType == 4) && (dword_6FBAB9E4 != 0))
									goto LAB_6fab63d5;
							}
							uVar7 = sub_6FB286F0(pMonster_00, uStack_3c, iStack_40, 1);
							if (uVar7 != 0)
							{
								if ((pDStack_58 == pMonster_00) &&
								    (iVar2 = sub_6FB29550((int*)pMonster_00), pDVar14 = pMonster_00,
								        pDVar1 = pMonster_00, iVar2 == 0))
									break;
								if (pMonster != nullptr)
								{
									uVar7 = pMonster->dwUnitType;
									iStack_64 = *(int*)(byte_6FB77088 + uVar6 * 4);
									iStack_60 = *(int*)(byte_6FB77088 + uVar7 * 4);
									if (uVar6 == 0)
									{
										iVar2 = sub_6FB29550((int*)pMonster_00);
										if (iVar2 != 0)
										{
											iStack_64 = 1;
										}
									}
									else if (uVar6 == 1)
									{
										iVar2 = MONSTERS_IsDead(pMonster_00);
										if (iVar2 != 0)
										{
											iStack_64 = -8;
										}
										iVar2 = STATES_CheckState(pMonster_00, 0x8f);
										if (iVar2 != 0)
											goto LAB_6fab63d5;
									}
									if ((uVar7 == 1) && (iVar2 = MONSTERS_IsDead(pMonster), iVar2 != 0))
									{
										iStack_60 = -8;
									}
									if (uVar6 == 2)
									{
										if (uVar7 != 2)
										{
											iVar2 = UNITS_IsDoor(pMonster_00);
											if (iVar2 == 0)
												goto LAB_6fab624c;
											if ((pMonster_00 == nullptr) || (pMonster_00->dwAnimMode == 0))
											{
												pDVar9 = UNITS_GetObjectTxtRecordFromObject(pMonster_00);
												pDVar14 = CUNIT_GetPlayer();
												if (pDVar14 == nullptr)
												{
													DStack_28.nX = 0;
													DStack_28.nY = 0;
												}
												else
												{
													UNITS_GetCoords(pDVar14, &DStack_28);
												}
												UNITS_GetCoords(pMonster_00, &DStack_8);
												UNITS_GetCoords(pMonster, &DStack_10);
												if (pDVar9->nOrientation == 1)
												{
													if ((((uint32_t)DStack_8.nY < (uint32_t)DStack_10.nY) &&
													        ((uint32_t)DStack_28.nY < (uint32_t)DStack_8.nY)) ||
													    (((uint32_t)DStack_10.nY < (uint32_t)DStack_8.nY &&
													        ((uint32_t)DStack_8.nY < (uint32_t)DStack_28.nY))))
													{
													LAB_6fab631a:
														if (iStack_60 < iStack_64)
														{
															pMonster = pMonster_00;
															pDStack_68 = pMonster_00;
														}
													}
												}
												else if ((((uint32_t)DStack_10.nX < (uint32_t)DStack_8.nX) &&
												             ((uint32_t)DStack_8.nX < (uint32_t)DStack_28.nX)) ||
												         (((uint32_t)DStack_8.nX < (uint32_t)DStack_10.nX &&
												             ((uint32_t)DStack_28.nX < (uint32_t)DStack_8.nX))))
													goto LAB_6fab631a;
											}
											goto LAB_6fab63d5;
										}
									LAB_6fab6335:
										iVar2 = iStack_60 - iStack_64;
										if (iVar2 == 0)
										{
											iVar2 = UNITS_GetClientCoordX(pMonster_00);
											iVar3 = UNITS_GetClientCoordX(pUnit);
											iVar4 = UNITS_GetClientCoordY(pMonster_00);
											iVar5 = UNITS_GetClientCoordY(pUnit);
											iVar10 = UNITS_GetClientCoordX(pMonster);
											iVar11 = UNITS_GetClientCoordX(pUnit);
											iVar12 = UNITS_GetClientCoordY(pDStack_68);
											iVar13 = UNITS_GetClientCoordY(pUnit);
											pMonster = pDStack_68;
											if ((iVar5 - iVar4) * (iVar5 - iVar4) + (iVar3 - iVar2) * (iVar3 - iVar2) <
											    (iVar13 - iVar12) * (iVar13 - iVar12) +
											        (iVar11 - iVar10) * (iVar11 - iVar10))
											{
												pMonster = pMonster_00;
												pDStack_68 = pMonster_00;
											}
											goto LAB_6fab63d5;
										}
									}
									else
									{
										if (uVar7 != 2)
											goto LAB_6fab6335;
										iVar2 = UNITS_IsDoor(pMonster);
										if (iVar2 != 0)
										{
											if (pMonster->dwAnimMode == 0)
											{
												pDVar14 = CUNIT_GetPlayer();
												if (pDVar14 == nullptr)
												{
													DStack_30.nX = 0;
													DStack_30.nY = 0;
												}
												else
												{
													UNITS_GetCoords(pDVar14, &DStack_30);
												}
												UNITS_GetCoords(pMonster_00, &DStack_18);
												UNITS_GetCoords(pMonster, &DStack_20);
												pDVar9 = UNITS_GetObjectTxtRecordFromObject(pMonster);
												if (pDVar9->nOrientation == 1)
												{
													if ((((uint32_t)DStack_20.nY <= (uint32_t)DStack_18.nY) ||
													        ((uint32_t)DStack_30.nY <= (uint32_t)DStack_20.nY)) &&
													    (((uint32_t)DStack_18.nY <= (uint32_t)DStack_20.nY ||
													        ((uint32_t)DStack_20.nY <= (uint32_t)DStack_30.nY))))
													{
													LAB_6fab6241:
														pMonster = pMonster_00;
														pDStack_68 = pMonster_00;
													}
												}
												else if ((((uint32_t)DStack_18.nX <= (uint32_t)DStack_20.nX) ||
												             ((uint32_t)DStack_20.nX <= (uint32_t)DStack_30.nX)) &&
												         (((uint32_t)DStack_20.nX <= (uint32_t)DStack_18.nX ||
												             ((uint32_t)DStack_30.nX <= (uint32_t)DStack_20.nX))))
													goto LAB_6fab6241;
											}
											goto LAB_6fab63d5;
										}
									LAB_6fab624c:
										iVar2 = iStack_60 - iStack_64;
									}
									if (SBORROW4(iStack_60, iStack_64) == iVar2 < 0)
										goto LAB_6fab63d5;
								}
								pMonster = pMonster_00;
								pDStack_68 = pMonster_00;
							}
						}
					LAB_6fab63d5:
						do
						{
							pMonster_00 = pMonster_00->pRoomNext;
							pDVar14 = pMonster;
							pDVar1 = pDStack_68;
							if (pMonster_00 == nullptr)
								goto LAB_6fab6404;
						LAB_6fab5ff7:
							uVar6 = pMonster_00->dwUnitType;
						} while (uVar6 == 3);
					}
				}
			LAB_6fab6404:
				pDStack_68 = pDVar1;
				uStack_54 = uStack_54 + 1;
				pMonster = pDVar14;
			} while (uStack_54 < uStack_38);
		}
		sub_6FAB5AE0(pDVar14);
	}
}

//D2Client.0x6FAB6430
void __fastcall sub_6FAB6430(int a1, int a2, uint32_t a3)
{
	int iVar1;

	if ((a1 != 0) && (a2 != 0))
	{
		iVar1 = sub_6FAB18D0(*(int*)(a2 + 0xc));
		*(uint32_t*)(iVar1 + 8) = a3;
	}
}

//D2Client.0x6FAB6450
void __fastcall sub_6FAB6450(uint32_t* a1)
{
	if (a1 != nullptr)
	{
		dword_6FBAB9D4 = *a1;
		dword_6FBAB9D8 = a1[1];
		dword_6FBAB9DC = a1[2];
		dword_6FBAB9E0 = a1[3];
		dword_6FBAB9F0 = 1;
		return;
	}
	dword_6FBAB9F0 = 0;
}

//D2Client.0x6FAB6490
// TODO: decompilation needs review (unaff_)
int* __fastcall sub_6FAB6490(D2SkillStrc* pSkill, int* a2, int* a3, int* a4, uint8_t a5, int a6)
{
	D2SkillsTxt* pUnit;
	uint16_t uVar1;
	D2UnitStrc* pUnit_00;
	int iVar2;
	int32_t DVar3;
	D2UnitStrc** ppDVar4;
	D2ActiveRoomStrc* pDVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	int* piVar8;
	void* pMemPool;
	D2UnitFindDataStrc* pUnitFindData;
	int iVar9;
	uint32_t uVar10;
	int* unaff_retaddr;
	void* pfnUnitTest;
	D2UnitFindArgStrc* pUnitFindArg;
	D2SkillsTxt* pDStack_74;
	D2UnitFindDataStrc DStack_6c;
	int aiStack_38[2];
	D2UnitStrc* pDStack_30;
	int iStack_2c;
	void* pvStack_28;
	uint32_t uStack_24;
	int* piStack_4;

	pDStack_74 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
	pUnit_00 = CUNIT_GetPlayer();
	if (a2 != nullptr)
	{
		if ((*a2 == 0) && (iVar2 = sub_6FB29550(a2), iVar2 != 0))
		{
			return a2;
		}
		if ((((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)((int)pDStack_74->dwFlags + 3)) != 0) ||
		    (iVar2 = sub_6FB29550(a2), iVar2 == 0))
			goto LAB_6fab65fa;
		sub_6FAB5AE0(nullptr);
		iVar2 = *a2;
		if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
		{
			iVar2 = *(int*)(a2[0xb] + 0xc);
		}
		else if ((D2DynamicPathStrc*)a2[0xb] == nullptr)
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = PATH_GetXPosition((D2DynamicPathStrc*)a2[0xb]);
		}
		*a3 = iVar2;
		iVar2 = *a2;
		if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
		{
			piVar8 = a2 + 0xb;
			a2 = nullptr;
			*a4 = *(int*)(*piVar8 + 0x10);
		}
		else if ((D2DynamicPathStrc*)a2[0xb] == nullptr)
		{
			a2 = nullptr;
			*a4 = 0;
		}
		else
		{
			iVar2 = PATH_GetYPosition((D2DynamicPathStrc*)a2[0xb]);
			a2 = nullptr;
			*a4 = iVar2;
		}
	}
	uVar10 = pUnit_00->dwUnitType;
	if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
	{
		iVar2 = pUnit_00->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit_00->pDynamicPath == nullptr)
	{
		iVar2 = 0;
	}
	else
	{
		iVar2 = PATH_GetXPosition(pUnit_00->pDynamicPath);
	}
	if (*a3 == iVar2)
	{
		uVar10 = pUnit_00->dwUnitType;
		if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
		{
			DVar3 = (*(int32_t*)&pUnit_00->pDynamicPath->tTargetCoord);
		}
		else if (pUnit_00->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
		}
		else
		{
			DVar3 = (int32_t)PATH_GetYPosition(pUnit_00->pDynamicPath);
		}
		if ((int32_t)*a4 == DVar3)
		{
			sub_6FABA860(pUnit_00, a3, a4);
		}
	}
LAB_6fab65fa:
	if ((((((a5 & 8) == 0) || ((a5 & 1) == 0)) || ((a5 & 0x20) != 0)) ||
	        (iVar2 = UNITS_IsInMovingMode(pUnit_00), iVar2 == 0)) &&
	    (iVar2 = sub_6FB4DA80(pUnit_00, pSkill), iVar2 == 0))
	{
		uVar10 = (uint32_t) * (uint8_t*)((int)pDStack_74->dwFlags + 2);
		if ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x18) & uVar10) != 0)
		{
			DStack_6c.pMemPool = a2;
			if (a2 != nullptr)
			{
				if ((((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)((int)pDStack_74->dwFlags + 3)) != 0) &&
				    (iVar2 = sub_6FB29550(a2), iVar2 != 0))
				{
					return a2;
				}
				iVar2 = sub_6FAB6A60(a2);
				*a3 = iVar2;
				ppDVar4 = sub_6FAB6A90(a2);
				*a4 = (int)ppDVar4;
			}
			iVar9 = (-(uint32_t)((*(uint8_t*)((int)pDStack_74->dwFlags + 3) & (uint8_t) * ((uint8_t*)&gdwBitMasks)) != 0) &
			            0xfff) +
			        0x2003;
			iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			if (iVar2 == 0x5a)
			{
				if (((a2 != nullptr) && (*a2 == 4)) &&
				    (iVar2 = ITEMS_IsMetalItem(a2[1]), iVar2 != 0))
				{
					return a2;
				}
				iVar9 = 0x20;
			}
			piVar8 = aiStack_38;
			for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*piVar8 = 0;
				piVar8 = piVar8 + 1;
			}
			aiStack_38[0] = iVar9;
			pDStack_30 = CUNIT_GetPlayer();
			pfnUnitTest = (void*)*a4;
			iVar2 = *a3;
			pUnitFindArg = (D2UnitFindArgStrc*)0x9;
			uStack_24 = 9;
			iStack_2c = iVar2;
			pvStack_28 = pfnUnitTest;
			pDVar5 = CUNIT_GetPlayerRoom();
			UNITFINDS_InitializeUnitFindData(pMemPool, pUnitFindData, nullptr, (int)&DStack_6c.pRoom, (int)pDVar5,
			    iVar2, (UNITFINDTEST)(pfnUnitTest), pUnitFindArg);
			DStack_6c.nFlags = iVar9;
			UNITFINDS_FindAllMatchingUnitsInNeighboredRooms(&DStack_6c);
			iVar2 = 0;
			uVar10 = 10;
			if (0 < DStack_6c.nIndex)
			{
				do
				{
					pUnit = (D2SkillsTxt*)DStack_6c.pUnitsArray[iVar2];
					uVar6 = UNITS_GetDistanceToCoordinates((D2UnitStrc*)pUnit, *piStack_4, *unaff_retaddr);
					uVar7 = sub_6FB286F0((D2UnitStrc*)pUnit, 0, 0, 0);
					if ((uVar7 != 0) && ((int)uVar6 < (int)uVar10))
					{
						uVar10 = uVar6;
						pDStack_74 = pUnit;
					}
					iVar2 = iVar2 + 1;
				} while (iVar2 < DStack_6c.nIndex);
			}
			UNITFINDS_FreeUnitFindData(&DStack_6c);
			return (int*)pDStack_74;
		}
		if (((a2 == nullptr) && ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x14) & uVar10) != 0)) &&
		    (a6 != 0))
		{
			piVar8 = sub_6FAB6880(pUnit_00);
			return piVar8;
		}
		if ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x1c) & uVar10) != 0)
		{
			if (a2 == nullptr)
			{
				DStack_6c.pMemPool = (void*)*a3;
				DStack_6c.pUnitsArray = (D2UnitStrc**)*a4;
			}
			else
			{
				DStack_6c.pMemPool = (void*)sub_6FAB6A60(a2);
				DStack_6c.pUnitsArray = sub_6FAB6A90(a2);
			}
			pDVar5 = CUNIT_GetPlayerRoom();
			if (((pDVar5 != nullptr) &&
			        (uVar1 = COLLISION_CheckMask(pDVar5, (int)DStack_6c.pMemPool, (int)DStack_6c.pUnitsArray, 1),
			            uVar1 != 0)) &&
			    (pDVar5 = COLLISION_GetFreeCoordinatesWithMaxDistance(pDVar5, (D2CoordStrc*)&DStack_6c, 1, 1, 0, 7),
			        pDVar5 != nullptr))
			{
				*a3 = (int)DStack_6c.pMemPool;
				*a4 = (int)DStack_6c.pUnitsArray;
				return nullptr;
			}
		}
	}
	return a2;
}

//D2Client.0x6FAB6860
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FAB6860()
{
	int iVar1;
	int* in_ECX;

	if ((in_ECX != nullptr) && (*in_ECX == 4))
	{
		iVar1 = ITEMS_IsMetalItem(in_ECX[1]);
		if (iVar1 != 0)
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAB6880
int* __fastcall sub_6FAB6880(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	uint16_t uVar3;
	uint32_t uVar4;
	D2ActiveRoomStrc* pRoom;
	int iVar5;
	int32_t DVar6;
	D2UnitStrc* pTargetUnit;
	D2ActiveRoomStrc* pRoom_00;
	int nX;
	uint32_t uVar7;
	int* piStack_10;
	uint32_t uStack_c;

	uVar4 = UNITS_GetNewDirection(pUnit);
	uStack_c = (uVar4 & 0xff) >> 3;
	pRoom = UNITS_GetRoom(pUnit);
	piStack_10 = (int*)(&dword_6FB6E2BC);
	do
	{
		uVar4 = pUnit->dwUnitType;
		uVar7 = *piStack_10 + uStack_c & 7;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
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
		iVar1 = *(int*)(byte_6FB6E27C + uVar7 * 4);
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
		}
		else
		{
			DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iVar2 = *(int*)(byte_6FB6E29C + uVar7 * 4);
		uVar3 = COLLISION_CheckMaskWithSize(pRoom, iVar1 + iVar5, iVar2 + (int)DVar6, 1, 0x180);
		if (uVar3 != 0)
		{
			pTargetUnit = D2Common_10407(pRoom_00, nX, (int)pRoom, (int(__fastcall*)(D2UnitStrc*, void*))((void*)(iVar1 + iVar5)),
			    (void*)(iVar2 + (int)DVar6), 0x6fab6a30);
			if ((pTargetUnit != nullptr) &&
			    (uStack_c = pTargetUnit->dwFlags >> 2 & 1, uStack_c != 0))
			{
				if ((((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)((int)piStack_10 + 6)) == 0) ||
				    ((((pTargetUnit->dwUnitType == 1 && (iVar5 = pTargetUnit->dwClassId, -1 < iVar5)) &&
				          (iVar1 = *(int*)((uint8_t*)&sgptDataTables), iVar5 < *(int*)(iVar1 + 0xa80))) &&
				        (((iVar5 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + iVar5 * 0x1a8), -1 < iVar5 && (iVar5 < *(int*)(iVar1 + 0xa98))) &&
				            ((iVar5 = *(int*)(iVar1 + 0xa90) + iVar5 * 0x134, iVar5 != 0 &&
				                                                                  (uStack_c = (uint32_t) * (uint8_t*)(iVar5 + 4) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x18),
				                                                                      uStack_c != 0))))))))
				{
				LAB_6fab6a15:
					UNITS_SetTargetUnitForDynamicUnit(pUnit, pTargetUnit);
					return (int*)pTargetUnit;
				}
				uVar4 = sub_6FB29D80(pUnit, pTargetUnit);
				if (uVar4 != 0)
					goto LAB_6fab6a15;
			}
		}
		piStack_10 = piStack_10 + 1;
		if ((int)&tbl_6FB6E2CF < (int)piStack_10)
		{
			return nullptr;
		}
	} while (true);
}

//D2Client.0x6FAB6A30
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FAB6A30()
{
	int* in_ECX;

	if ((in_ECX != nullptr) && (*in_ECX == 1))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FAB6A50
void __cdecl sub_6FAB6A50()
{
	dword_6FB77080 = 0x13;
	dword_6FB77084 = 0x13;
}

//D2Client.0x6FAB6A60
int __fastcall sub_6FAB6A60(int* a1)
{
	int iVar1;

	iVar1 = *a1;
	if ((iVar1 != 2) && ((iVar1 < 4 || (5 < iVar1))))
	{
		if ((D2DynamicPathStrc*)a1[0xb] != nullptr)
		{
			iVar1 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
			return iVar1;
		}
		return 0;
	}
	return *(uint32_t*)(a1[0xb] + 0xc);
}

//D2Client.0x6FAB6A90
D2UnitStrc** __fastcall sub_6FAB6A90(int* a1)
{
	int iVar1;
	D2UnitStrc** ppDVar2;

	iVar1 = *a1;
	if ((iVar1 != 2) && ((iVar1 < 4 || (5 < iVar1))))
	{
		if ((D2DynamicPathStrc*)a1[0xb] != nullptr)
		{
			ppDVar2 = (D2UnitStrc**)PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
			return ppDVar2;
		}
		return nullptr;
	}
	return *(D2UnitStrc***)(a1[0xb] + 0x10);
}
