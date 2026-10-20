#include "UI/ShowItems.h"

#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "UI/Automap.h"
#include "UI/Inv.h"
#include "UI/Restart.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"

//D2Client.0x6FB6FB74
uint32_t dword_6FB6FB74 = 0x149;
//D2Client.0x6FB6FB9C
uint8_t byte_6FB6FB9C = 1;
//D2Client.0x6FB6FBA4
uint32_t tbl_6FB6FBA4[2] = {3, 3};
//D2Client.0x6FB8CCF4
int32_t dword_6FB8CCF4 = -6;
//D2Client.0x6FB8CCF8
int32_t dword_6FB8CCF8 = 2;
//D2Client.0x6FBB7028
uint32_t dword_6FBB7028;
//D2Client.0x6FBB702C
uint32_t dword_6FBB702C;
//D2Client.0x6FBB7030
uint32_t dword_6FBB7030;
//D2Client.0x6FBB7034
uint32_t dword_6FBB7034;
//D2Client.0x6FBB7038
uint32_t dword_6FBB7038;
//D2Client.0x6FBB713C
uint32_t dword_6FBB713C;
//D2Client.0x6FBB7140
uint32_t dword_6FBB7140;
//D2Client.0x6FBB7144
uint32_t dword_6FBB7144;
//D2Client.0x6FBB9428
int32_t dword_6FBB9428;
//D2Client.0x6FBB942C
char byte_6FBB942C;

//D2Client.0x6FB09D80
uint32_t __fastcall sub_6FB09D80(int* a1, int* a2, int* a3, int* a4, int a5, int a6, int a7)
{
	int iVar1;
	bool bVar2;
	bool bVar3;
	int iVar4;
	int iVar5;
	int* piVar6;
	int iVar7;

	iVar4 = gnScreenHeight + -0x30;
	if (*a1 < a7)
	{
		*a3 = *a3 + (a7 - *a1);
		*a1 = 6;
	}
	if (*a2 < 6)
	{
		*a4 = *a4 + (6 - *a2);
		*a2 = 6;
	}
	iVar7 = *a3;
	if (a6 <= iVar7)
	{
		iVar5 = (iVar7 - a6) + 1;
		*a3 = iVar7 - iVar5;
		*a1 = *a1 - iVar5;
	}
	iVar7 = *a4;
	if (iVar4 <= iVar7)
	{
		*a4 = iVar7 - (iVar7 - iVar4);
		*a2 = *a2 - (iVar7 - iVar4);
	}
	D2_ASSERT(0x1f >= dword_6FBB9428);
	iVar7 = 0;
	if (0 < dword_6FBB9428)
	{
		iVar5 = *a1;
		iVar1 = *a2;
		piVar6 = (int*)(&dword_6FBB7028);
		do
		{
			if ((piVar6[2] < iVar5) || (*a3 < *piVar6))
			{
				bVar2 = false;
			}
			else
			{
				bVar2 = true;
			}
			if ((piVar6[3] < iVar1) || (*a4 < piVar6[1]))
			{
				bVar3 = false;
			}
			else
			{
				bVar3 = true;
			}
			if ((bVar2) && (bVar3))
			{
				if (a5 < 7)
				{
					if (((*a4 - iVar1) / 2 == 0) || (iVar4 < iVar1))
					{
						iVar4 = ((&dword_6FBB7034)[iVar7 * 0x48] - iVar1) + 5;
					}
					else
					{
						iVar4 = ((&dword_6FBB702C)[iVar7 * 0x48] - *a4) + -3;
					}
					*a2 = iVar1 + iVar4;
					*a4 = *a4 + iVar4;
					return 0;
				}
				if (((*a3 - iVar5) / 2 != 0) && (a6 <= iVar5))
				{
					iVar4 = ((&dword_6FBB7028)[iVar7 * 0x48] - *a3) + -1;
					*a1 = iVar5 + iVar4;
					*a3 = *a3 + iVar4;
					return 0;
				}
				iVar4 = ((&dword_6FBB7030)[iVar7 * 0x48] - iVar5) + 1;
				*a1 = iVar5 + iVar4;
				*a3 = *a3 + iVar4;
				return 0;
			}
			iVar7 = iVar7 + 1;
			piVar6 = piVar6 + 0x48;
		} while (iVar7 < dword_6FBB9428);
	}
	return 1;
}

//D2Client.0x6FB09F60
void __cdecl sub_6FB09F60()
{
	Unicode* pText;
	uint8_t bVar1;
	D2UnitStrc* pDVar2;
	D2ActiveRoomStrc* pRoom;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	D2ItemsTxt* pDVar7;
	uint32_t uVar8;
	int iVar9;
	DrawMode* pDVar10;
	uint32_t uVar11;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_38;
	int iStack_34;
	int iStack_30;
	int iStack_2c;
	uint32_t uStack_28;
	uint32_t uStack_24;
	uint32_t uStack_20;
	D2ActiveRoomStrc** ppDStack_1c;
	int iStack_18;
	int iStack_14;
	uint32_t uStack_10;
	int iStack_c;
	int iStack_8;
	D2UnitStrc* pDStack_4;

	iStack_18 = D2GFX_CheckPerspective();
	pDVar2 = CUNIT_GetPlayer();
	if ((pDVar2 != nullptr) &&
	    (pRoom = UNITS_GetRoom(pDVar2), pRoom != nullptr))
	{
		pDStack_4 = sub_6FAB5A20();
		iStack_c = sub_6FB57BC0();
		iStack_8 = sub_6FB57BD0();
		DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_1c, (int*)&uStack_20);
		bVar1 = D2Win_10034_MixRGB(0, 0x40, 0x80);
		iVar9 = 0;
		uStack_28 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_28 + 1)), bVar1);
		dword_6FBB9428 = 0;
		iStack_44 = 0;
		uStack_24 = 0;
		if (uStack_20 != 0)
		{
			do
			{
				for (pDVar2 = ppDStack_1c[uStack_24]->pUnitFirst; pDVar2 != nullptr;
				     pDVar2 = pDVar2->pRoomNext)
				{
					iVar6 = iVar9;
					if ((((pDVar2 != nullptr) &&
					         (uStack_10 = pDVar2->dwFlagEx >> 7 & 1, uStack_10 != 0)) &&
					        (pDVar2->dwUnitType == 4)) &&
					    (iVar9 < 0x20))
					{
						(&dword_6FBB7038)[iVar9 * 0x48] = (uint32_t)(pDVar2);
						if (iStack_18 == 0)
						{
							iVar6 = UNITS_GetClientCoordX(pDVar2);
							iVar3 = sub_6FAB5890();
							iVar4 = sub_6FAB58A0();
							iVar5 = UNITS_GetClientCoordY(pDVar2);
							iVar3 = iVar6 - iVar3;
							iVar4 = (-0x10 - iVar4) + iVar5;
						}
						else
						{
							iVar3 = UNITS_GetPrecisionX(pDVar2);
							iVar4 = UNITS_GetPrecisionY(pDVar2);
							iVar5 = SCALE_CheckPerspectivePosition(iVar3, iVar4);
							iVar6 = dword_6FBB9428;
							if (iVar5 == 0)
								goto LAB_6fb0a399;
							SCALE_AdjustPerspectivePosition(iVar3, iVar4, 0, &iStack_4c, &iStack_14);
							iVar6 = sub_6FAB5750();
							iVar4 = iStack_14;
							if (iVar6 == 1)
							{
								iVar3 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
							}
							else
							{
								iVar3 = iStack_4c;
								if (iVar6 != 2)
									goto LAB_6fb0a0df;
								iVar3 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
							}
							iVar3 = iStack_4c + iVar3;
							iStack_4c = iVar3;
						}
					LAB_6fb0a0df:
						iStack_40 = 0;
						iStack_3c = gnScreenWidth;
						iStack_38 = iVar4;
						iVar6 = sub_6FAB5750();
						if (iVar6 == 1)
						{
							iStack_3c = gnScreenWidth / 2 + -0x20;
						}
						else if (iVar6 == 2)
						{
							iStack_40 = gnScreenWidth / 2;
						}
						iVar6 = dword_6FBB9428;
						if (((iStack_40 <= iVar3) && (iVar3 <= iStack_3c)) &&
						    ((-9 < iVar4 && (iVar4 <= gnScreenHeight + -0x10))))
						{
							pText = (Unicode*)(word_6FBB703C + iVar9 * 0x90);
							pText->ch = 0;
							sub_6FB20740(pDVar2, pText, 0x100);
							D2Win_10131_GetTextDimensions(pText, &iStack_34, &iStack_48);
							uStack_10 = 1;
							iStack_34 = iStack_34 + 8;
							iStack_2c = iVar3 - (iStack_34 >> 1);
							iStack_30 = iStack_34 + iStack_2c;
							iStack_48 = (iVar4 - iStack_48) + 4;
							iVar6 = 0;
							do
							{
								iVar4 = iStack_3c;
								iVar3 = iStack_40;
								iVar5 = sub_6FB09D80(&iStack_2c, &iStack_48, &iStack_30, &iStack_38, iVar6, iStack_3c,
								    iStack_40);
								uVar8 = uStack_10;
								if (iVar5 != 0)
									goto LAB_6fb0a1d8;
								iVar6 = iVar6 + 1;
							} while (iVar6 < 0xc);
							uVar8 = 0;
						LAB_6fb0a1d8:
							iVar6 = dword_6FBB9428;
							if (((iStack_30 <= iVar4) && (iVar3 <= iStack_2c)) && (uVar8 != 0))
							{
								uVar11 = 0;
								(&dword_6FBB7028)[iVar9 * 0x48] = iStack_2c;
								(&dword_6FBB702C)[iVar9 * 0x48] = iStack_48;
								(&dword_6FBB7030)[iVar9 * 0x48] = iStack_30;
								(&dword_6FBB7034)[iVar9 * 0x48] = iStack_38;
								if (iStack_44 == 0)
								{
									if ((((iStack_c < iStack_2c) || (iStack_30 < iStack_c)) || (iStack_8 < iStack_48)) || (iStack_38 + 4 < iStack_8))
									{
										if (pDVar2 != pDStack_4)
											goto LAB_6fb0a2b8;
										(&dword_6FBB713C)[iVar9 * 0x48] = uStack_28 & 0xff;
										(&dword_6FBB7140)[iVar9 * 0x48] = 5;
										(&dword_6FBB7144)[iVar9 * 0x48] = 0;
										D2Win_10129_DrawFramedText(nullptr, 0, 0, 0, 0);
										sub_6FAB5D40();
										iStack_44 = 1;
									}
									else
									{
										(&dword_6FBB7140)[iVar9 * 0x48] = 5;
										(&dword_6FBB7144)[iVar9 * 0x48] = 0;
										(&dword_6FBB713C)[iVar9 * 0x48] = uStack_28 & 0xff;
										sub_6FAB5A90(pDVar2);
										iStack_44 = 1;
									}
								}
								else
								{
								LAB_6fb0a2b8:
									(&dword_6FBB713C)[iVar9 * 0x48] = 0;
									(&dword_6FBB7140)[iVar9 * 0x48] = 1;
									iVar6 = ITEMS_GetItemQuality(pDVar2);
									switch (iVar6)
									{
									case 4:
										uVar11 = 3;
										break;
									case 5:
										uVar11 = 2;
										break;
									case 6:
										uVar11 = 9;
										break;
									case 7:
										uVar11 = 4;
										break;
									case 8:
										uVar11 = 8;
										break;
									case 9:
										uVar11 = 10;
										break;
									default:
										iVar6 = ITEMS_CheckItemFlag(pDVar2, 0x800, __LINE__, __FILE__);
										if ((((iVar6 != 0) && (iVar6 = ITEMS_CheckIfSocketable(pDVar2), iVar6 != 0)) &&
										        (bVar1 = ITEMS_GetMaxSockets(pDVar2), bVar1 != 0)) ||
										    (iVar6 = ITEMS_CheckItemFlag(pDVar2, 0x400000, __LINE__, __FILE__),
										        iVar6 != 0))
										{
											uVar11 = 5;
										}
									}
									pDVar7 = DATATBLS_GetItemsTxtRecord(pDVar2->dwClassId);
									if ((pDVar7->nQuest != 0) && (pDVar7->dwCode != 0x2067656c))
									{
										uVar11 = 4;
									}
									(&dword_6FBB7144)[iVar9 * 0x48] = uVar11;
								}
								dword_6FBB9428 = dword_6FBB9428 + 1;
								iVar6 = dword_6FBB9428;
							}
						}
					}
				LAB_6fb0a399:
					iVar9 = iVar6;
				}
				uStack_24 = uStack_24 + 1;
			} while (uStack_24 < uStack_20);
		}
		iVar6 = 0;
		if (0 < iVar9)
		{
			pDVar10 = (DrawMode*)(&dword_6FBB7140);
			do
			{
				D2Win_10132((Unicode*)(pDVar10 + -0x41), pDVar10[-0x46], pDVar10[-0x43], pDVar10[-1], *pDVar10,
				    pDVar10[1]);
				iVar6 = iVar6 + 1;
				pDVar10 = pDVar10 + 0x48;
			} while (iVar6 < dword_6FBB9428);
		}
		if (iStack_44 == 0)
		{
			sub_6FAB5D40();
			D2Win_10129_DrawFramedText(nullptr, 0, 0, 0, 0);
		}
	}
}

//D2Client.0x6FB0A440
uint16_t __fastcall sub_6FB0A440(int a1, int a2)
{
	int iVar1;
	int iVar2;

	if ((((-1 < a1) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a1 < *(int*)(iVar2 + 0xba0))) && (iVar1 = *(int*)(iVar2 + 0xb98) + a1 * 0x23c, iVar1 != 0)) &&
	    (((iVar1 = (int)*(short*)(iVar1 + 0x194), -1 < iVar1 && (iVar1 < *(int*)(iVar2 + 0xb94))) &&
	        (iVar2 = iVar1 * 0x120 + *(int*)(iVar2 + 0xb8c), iVar2 != 0))))
	{
		return *(uint16_t*)(iVar2 + 8 + a2 * 2);
	}
	return 0x1506;
}

//D2Client.0x6FB0A4A0
void __fastcall sub_6FB0A4A0(D2UnitStrc* pUnit, D2SkillStrc* pSkill, uint32_t a3, uint32_t a4, int* a5, uint32_t* a6, uint32_t a7, uint32_t a8)
{
	D2UnitStrc* pDVar1;

	pDVar1 = nullptr;
	if (pUnit->pInventory != nullptr)
	{
		pDVar1 = INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
	}
	*a5 = 0;
	*a6 = 0;
	sub_6FB0A4E0(pUnit, a5, a6, a4, pSkill, pDVar1);
}

//D2Client.0x6FB0A4E0
uint32_t __fastcall sub_6FB0A4E0(D2UnitStrc* pUnit, int* a2, uint32_t* a3, int a4, D2SkillStrc* pSkill, D2UnitStrc* pUnit2)
{
	D2SkillsTxt* pDVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;

	if ((pUnit != nullptr) && (pSkill != nullptr))
	{
		pDVar1 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
		if (pDVar1 != nullptr)
		{
			*a3 = 0;
			iVar2 = UNITS_GetAttackRate(pUnit);
			*a2 = iVar2;
			if (((pUnit2 != nullptr) ||
			        ((pUnit->pInventory != nullptr &&
			            (pUnit2 = INVENTORY_GetLeftHandWeapon(pUnit->pInventory), pUnit2 != nullptr)))) &&
			    (uVar3 = ITEMS_GetItemType(pUnit2), uVar3 == 0x26))
			{
				*a2 = 0;
				*a3 = 0;
			}
			iVar2 = SKILLS_GetWeaponMasteryBonus(pUnit, pUnit2, pSkill, 0);
			iVar4 = STATLIST_UnitGetItemStatOrSkillStatValue(pUnit, 0x77, 0);
			iVar5 = SKILLS_GetToHitFactor(pUnit, (int)pDVar1->nSkillId, a4);
			iVar5 = iVar2 + iVar4 + iVar5;
			if ((((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & (uint8_t)pDVar1->dwFlags[0]) != 0) &&
			    (iVar2 = STATLIST_UnitGetStatValue(pUnit, 0x145, 0), iVar2 != 0))
			{
				iVar5 = iVar5 + iVar2;
				*a3 = 3;
			}
			*a2 = (*a2 * iVar5) / 100 + *a2;
			iVar2 = STATES_CheckStateMaskAttBlueOnUnit(pUnit);
			if (iVar2 != 0)
			{
				*a3 = 3;
			}
			iVar2 = STATES_CheckStateMaskAttRedOnUnit(pUnit);
			if (iVar2 != 0)
			{
				*a3 = 1;
			}
			return 1;
		}
		return 0;
	}
	return 0;
}

//D2Client.0x6FB0A610
void __fastcall sub_6FB0A610(D2UnitStrc* pUnit2, int a2, short* a3, int a4, int* a5, uint32_t* a6, uint32_t a7, uint32_t a8)
{
	int* piVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	D2UnitStrc* pUnit;

	pUnit = nullptr;
	if (pUnit2->pInventory != nullptr)
	{
		pUnit = INVENTORY_GetLeftHandWeapon(pUnit2->pInventory);
	}
	piVar1 = a5;
	*a5 = 0;
	*a6 = 0;
	if (a2 != 0)
	{
		if (pUnit == nullptr)
		{
			iVar3 = UNITS_GetAttackRate(pUnit2);
			*piVar1 = iVar3;
		}
		else
		{
			a5 = nullptr;
			pDVar2 = STATLIST_GetOwner(pUnit, (int*)&a5);
			STATLIST_MergeStatLists(pUnit2, pUnit, 0);
			iVar3 = UNITS_GetAttackRate(pUnit2);
			*piVar1 = iVar3;
			if (pDVar2 == nullptr)
			{
				STATLIST_ExpireUnitStatlist(pUnit2, pUnit);
			}
			else
			{
				STATLIST_MergeStatLists(pUnit2, pUnit, (int)a5);
			}
		}
		iVar3 = STATLIST_UnitGetItemStatOrSkillStatValue(pUnit2, 0x77, 0);
		iVar4 = SKILLS_GetToHitFactor(pUnit2, (int)*a3, a4);
		iVar3 = iVar3 + iVar4;
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(a3 + 2)) != 0)
		{
			iVar4 = STATLIST_UnitGetStatValue(pUnit2, 0x145, 0);
			if (iVar4 != 0)
			{
				iVar3 = iVar3 + iVar4;
				*a6 = 3;
			}
		}
		*piVar1 = (*piVar1 * iVar3) / 100 + *piVar1;
		iVar3 = STATES_CheckStateMaskAttBlueOnUnit(pUnit2);
		if (iVar3 != 0)
		{
			*a6 = 3;
		}
		iVar3 = STATES_CheckStateMaskAttRedOnUnit(pUnit2);
		if (iVar3 != 0)
		{
			*a6 = 1;
		}
	}
}

//D2Client.0x6FB0A730
void __fastcall sub_6FB0A730(D2UnitStrc* pUnit, D2SkillStrc* pSkill, uint32_t a3, int* a4, uint32_t* a5, uint32_t* a6, uint32_t a7, uint32_t a8)
{
	int iVar1;
	D2UnitStrc* pDVar2;

	iVar1 = UNITS_CanDualWield(pUnit);
	if (iVar1 != 0)
	{
		sub_6FB0A7D0(pUnit, (uint8_t*)a5, a6, 0, (uint32_t*)(a7), (uint32_t*)(a8), 0, pSkill, (code*)(sub_6FB0A7B0), 0,
		    (uint32_t)(a4));
		return;
	}
	pDVar2 = nullptr;
	if (pUnit->pInventory != nullptr)
	{
		pDVar2 = INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
	}
	*a5 = 0;
	*a6 = 0;
	sub_6FB0A4E0(pUnit, (int*)(a5), a6, (int)(a4), pSkill, pDVar2);
}

//D2Client.0x6FB0A7B0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB0A7B0(uint32_t* a1, uint32_t a2, uint32_t a3, uint32_t a4, D2SkillStrc* pSkill, uint32_t a6, uint32_t a7)
{
	D2UnitStrc* in_ECX;
	int* in_EDX;

	sub_6FB0A4E0(in_ECX, in_EDX, a1, a4, pSkill, (D2UnitStrc*)(a7));
}

//D2Client.0x6FB0A7D0
uint32_t __fastcall sub_6FB0A7D0(D2UnitStrc* pUnit, uint8_t* a2, uint32_t* a3, uint32_t a4, uint32_t* a5, uint32_t* a6, uint32_t a7, D2SkillStrc* pSkill, code* a9, uint32_t a10, uint32_t a11)
{
	D2InventoryStrc* pInventory;
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pItem;

	pInventory = pUnit->pInventory;
	if (pInventory == nullptr)
	{
		return 0;
	}
	iVar1 = UNITS_CanDualWield(pUnit);
	if (iVar1 == 0)
	{
		return 0;
	}
	pDVar2 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
	iVar1 = ITEMS_CanBeEquipped(pDVar2);
	if (iVar1 == 0)
	{
	LAB_6fb0a81e:
		pDVar2 = nullptr;
	}
	else
	{
		iVar1 = ITEMS_CheckItemTypeId(pDVar2, 0x26);
		if (iVar1 != 0)
			goto LAB_6fb0a81e;
	}
	pItem = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
	iVar1 = ITEMS_CanBeEquipped(pItem);
	if (iVar1 != 0)
	{
		iVar1 = ITEMS_CheckItemTypeId(pItem, 0x26);
		if (iVar1 == 0)
			goto LAB_6fb0a842;
	}
	pItem = nullptr;
LAB_6fb0a842:
	if ((pDVar2 == nullptr) || (pItem == nullptr))
	{
		pDVar2 = INVENTORY_GetLeftHandWeapon(pInventory);
		if (pDVar2 != nullptr)
		{
			iVar1 = ITEMS_CanBeEquipped(pDVar2);
			if (iVar1 != 0)
			{
				STATLIST_MergeStatLists(pUnit, pDVar2, 1);
			}
		}
		(*a9)(a3, a4, a10, a11, pSkill, 0, 0);
		return 1;
	}
	iVar1 = sub_6FB0A950(pUnit);
	if (iVar1 == 0)
	{
		*a5 = 0;
		*a6 = 0;
	}
	else
	{
		(*a9)(a6, a7, a10, a11, pSkill, 0, iVar1);
	}
	iVar1 = sub_6FB0AA00(pUnit);
	if (iVar1 != 0)
	{
		(*a9)(a3, a4, a10, a11, pSkill, 0, iVar1);
		return 1;
	}
	*(uint32_t*)a2 = 0;
	*a3 = 0;
	return 1;
}

//D2Client.0x6FB0A950
int __fastcall sub_6FB0A950(D2UnitStrc* pUnit)
{
	D2InventoryStrc* pInventory;
	uint8_t bVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar4;

	iVar2 = UNITS_CanDualWield(pUnit);
	if ((iVar2 != 0) && (pInventory = pUnit->pInventory, pInventory != nullptr))
	{
		pDVar3 = INVENTORY_GetLeftHandWeapon(pInventory);
		if (pDVar3 != nullptr)
		{
			bVar1 = ITEMS_GetBodyLocation(pDVar3);
			pItem = INVENTORY_GetItemFromBodyLoc(pInventory, (bVar1 == 4) + 4);
			if ((pItem != nullptr) && (pItem != pDVar3))
			{
				iVar2 = ITEMS_CheckItemTypeId(pItem, 0x2d);
				if (iVar2 != 0)
				{
					iVar2 = ITEMS_CanBeEquipped(pDVar3);
					if (iVar2 != 0)
					{
						iVar2 = ITEMS_CanBeEquipped(pItem);
						if (iVar2 != 0)
						{
							pDVar4 = STATLIST_GetOwner(pDVar3, nullptr);
							if (pDVar4 != nullptr)
							{
								STATLIST_MergeStatLists(pUnit, pDVar3, 0);
							}
							pDVar3 = STATLIST_GetOwner(pItem, nullptr);
							if (pDVar3 != nullptr)
							{
								STATLIST_MergeStatLists(pUnit, pItem, 1);
							}
							return (int)pItem;
						}
					}
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FB0AA00
int __fastcall sub_6FB0AA00(D2UnitStrc* pUnit)
{
	D2InventoryStrc* pInventory;
	uint8_t bVar1;
	int iVar2;
	D2UnitStrc* pItem;
	D2UnitStrc* pItem_00;

	iVar2 = UNITS_CanDualWield(pUnit);
	if (iVar2 == 0)
	{
		return 0;
	}
	pInventory = pUnit->pInventory;
	if (pInventory == nullptr)
	{
		return 0;
	}
	pItem = INVENTORY_GetLeftHandWeapon(pInventory);
	if (pItem == nullptr)
	{
		return 0;
	}
	bVar1 = ITEMS_GetBodyLocation(pItem);
	pItem_00 = INVENTORY_GetItemFromBodyLoc(pInventory, (bVar1 == 4) + 4);
	if ((((pItem_00 != nullptr) && (pItem_00 != pItem)) &&
	        (iVar2 = ITEMS_CheckItemTypeId(pItem_00, 0x2d), iVar2 != 0)) &&
	    ((iVar2 = ITEMS_CanBeEquipped(pItem), iVar2 != 0 &&
	                                              (iVar2 = ITEMS_CanBeEquipped(pItem_00), iVar2 != 0))))
	{
		STATLIST_MergeStatLists(pUnit, pItem_00, 0);
		STATLIST_MergeStatLists(pUnit, pItem, 1);
		return (int)pItem;
	}
	iVar2 = ITEMS_CanBeEquipped(pItem);
	if (iVar2 != 0)
	{
		STATLIST_MergeStatLists(pUnit, pItem, 1);
	}
	return (int)pItem;
}

//D2Client.0x6FB0AAB0
void __fastcall sub_6FB0AAB0(D2UnitStrc* pUnit, D2SkillStrc* pSkill, uint32_t a3, int a4, D2UnitStrc* pUnit2, uint32_t* a6, uint32_t a7, uint32_t a8)
{
	D2UnitStrc* pDVar1;
	D2SkillsTxt* pDVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	pDVar1 = pUnit2;
	pUnit2->dwUnitType = 0;
	*a6 = 0;
	pUnit2 = nullptr;
	if (pSkill != nullptr)
	{
		pDVar2 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
		if (pDVar2 != nullptr)
		{
			uVar3 = UNITS_GetAttackRate(pUnit);
			pDVar1->dwUnitType = uVar3;
			if (pUnit->pInventory != nullptr)
			{
				pUnit2 = INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
				if (pUnit2 != nullptr)
				{
					uVar3 = ITEMS_GetItemType(pUnit2);
					if (uVar3 == 0x26)
					{
						pDVar1->dwUnitType = 0;
						*a6 = 0;
					}
				}
			}
			iVar6 = 0;
			iVar4 = STATES_CheckState(pUnit, 0x4e);
			if (iVar4 != 0)
			{
				iVar6 = SKILLS_GetWeaponMasteryBonus(pUnit, pUnit2, pSkill, 0);
			}
			iVar4 = STATLIST_UnitGetItemStatOrSkillStatValue(pUnit, 0x77, 0);
			iVar5 = SKILLS_GetToHitFactor(pUnit, (int)pDVar2->nSkillId, a4);
			pDVar1->dwUnitType =
			    (int)(pDVar1->dwUnitType * (iVar6 + iVar4 + iVar5)) / 100 + pDVar1->dwUnitType;
			*a6 = 0;
			iVar4 = STATES_CheckStateMaskAttBlueOnUnit(pUnit);
			if (iVar4 != 0)
			{
				*a6 = 3;
			}
			iVar4 = STATES_CheckStateMaskAttRedOnUnit(pUnit);
			if (iVar4 != 0)
			{
				*a6 = 1;
			}
		}
	}
}

//D2Client.0x6FB0ABC0
void __fastcall sub_6FB0ABC0(D2UnitStrc* pUnit, D2SkillStrc* pSkill, uint32_t a3, uint32_t* a4, uint32_t* a5, uint32_t* a6, uint32_t* a7, uint32_t* a8)
{
	sub_6FB0A7D0(pUnit, (uint8_t*)a5, a6, 0, a7, a8, 0, pSkill, (code*)(sub_6FB0A7B0), 0,
	    (uint32_t)(a4));
	*a5 = *a7;
	*a6 = *a8;
	*a7 = 0;
	*a8 = 0;
}

//D2Client.0x6FB0AC10
void __fastcall sub_6FB0AC10(uint32_t a1, uint32_t a2, int a3, int a4, int a5, D2SkillsTxt* pSkillsTxtRecord, D2SkillsTxt* pSkillsTxtRecord2)
{
	D2C_Language DVar1;

	D2Win_10127_SetFont(D2FONT_FONT6);
	if (byte_6FBB942C != '\0')
		goto LAB_6fb0ac5a;
	DVar1 = STRTABLE_GetLanguage();
	if ((int)DVar1 < 6)
	{
	LAB_6fb0ac49:
		dword_6FB8CCF4 = -6;
	}
	else
	{
		DVar1 = STRTABLE_GetLanguage();
		dword_6FB8CCF4 = -7;
		if (9 < (int)DVar1)
			goto LAB_6fb0ac49;
	}
	byte_6FBB942C = '\x01';
LAB_6fb0ac5a:
	sub_6FACFCD0(dword_6FBBA748 + a3, dword_6FBBA74C + gnScreenHeight + dword_6FB8CCF4 + -0x1e0 + a4,
	    dword_6FBBA748 + a5, (Unicode*)(a1), pSkillsTxtRecord);
	sub_6FACFCD0(dword_6FBBA748 + a3, dword_6FB8CCF8 + dword_6FBBA74C + gnScreenHeight + -0x1e0 + a4,
	    dword_6FBBA748 + a5, (Unicode*)(a2), pSkillsTxtRecord2);
}

//D2Client.0x6FB0ACE0
void __fastcall sub_6FB0ACE0(D2UnitStrc* pUnit, int a2, short* a3, int* a4, int a5, int a6, int a7)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	Unicode* pUVar5;
	int local_9c;
	D2SkillsTxt* local_98;
	int local_94;
	int local_90;
	int local_8c;
	D2SkillsTxt* local_88;
	int iStack_84;
	Unicode aUStack_80[32];
	Unicode aUStack_40[32];

	if ((a2 == 0) || (a3 == nullptr))
	{
		return;
	}
	iVar3 = 0;
	uVar2 = (uint32_t) * (uint8_t*)((int)a3 + 0x1a5);
	local_9c = 0;
	local_88 = nullptr;
	local_8c = a2;
	if (uVar2 != 0)
	{
		local_98 = nullptr;
		local_9c = 0;
		sub_6FB0B2C0(pUnit, (uint32_t)&local_98, &local_9c, (uint32_t*)(&local_88), 0, 0, (D2SkillStrc*)(a2), 0x80, 0, 0);
		sub_6FB0B6F0(pUnit, (int*)&local_98, &local_9c, (uint32_t*)(&local_88), nullptr, (D2SkillStrc*)(local_8c));
		local_9c = (int)(local_9c * uVar2 + ((int)(local_9c * uVar2) >> 0x1f & 0x7fU)) >> 7;
		iVar3 = (int)((int)local_98 * uVar2 + ((int)((int)local_98 * uVar2) >> 0x1f & 0x7fU)) >> 7;
	}
	local_94 = 0;
	local_90 = 0;
	switch ((char)a3[0xee])
	{
	case '\x01':
		local_98 = (D2SkillsTxt*)0x1;
		break;
	case '\x02':
		local_98 = (D2SkillsTxt*)0x9;
		break;
	case '\x03':
	case '\x04':
		local_98 = (D2SkillsTxt*)0x3;
		break;
	case '\x05':
		local_98 = (D2SkillsTxt*)0x2;
		break;
	default:
		local_98 = nullptr;
	}
	iVar1 = SKILLS_GetMinPhysDamage(pUnit, (int)*a3, (int)a4, 0);
	local_94 = local_94 + (iVar1 >> 8);
	iVar1 = SKILLS_GetMaxPhysDamage(pUnit, (int)*a3, (int)a4, 0);
	local_90 = local_90 + (iVar1 >> 8);
	iVar1 = SKILLS_GetMinElemDamage(pUnit, (int)*a3, (int)a4, 1);
	local_94 = local_94 + (iVar1 >> 8);
	iVar1 = SKILLS_GetMaxElemDamage(pUnit, (int)*a3, (int)a4, 1);
	local_90 = local_90 + (iVar1 >> 8);
	sub_6FB0BD60(pUnit, &local_94, &local_90, (char)a3[0xee]);
	iVar4 = local_94;
	iVar1 = local_9c;
	if ((iVar3 == 0) && (local_9c == 0))
	{
		iStack_84 = a6;
		iVar3 = local_90;
		if (local_90 <= local_94)
		{
			iVar3 = local_94 + 1;
		}
		sub_6FB0B250((Unicode*)aUStack_80, iVar4, iVar3, 0);
		local_9c = 0;
		local_8c = 0;
		D2Win_10131_GetTextDimensions(aUStack_80, &local_9c, &local_8c);
		local_9c = (local_9c * 0xb) / 7;
		if (local_9c <= a7 - a5)
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar3 = iStack_84;
			goto LAB_6fb0af12;
		}
	}
	else
	{
		if ((local_94 != 0) || (local_90 != 0))
		{
			if (iVar3 == iVar1)
			{
				sub_6FB0B0F0((Unicode*)aUStack_40, iVar3, 0);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_40, iVar3, iVar1, 0, 1);
			}
			if (local_94 == local_90)
			{
				sub_6FB0B0F0((Unicode*)aUStack_80, local_94, 0);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_80, local_94, local_90, 0, 1);
			}
			sub_6FB0AC10((uint32_t)(aUStack_40), (uint32_t)(aUStack_80), a5, a6, a7, local_88, local_98);
			return;
		}
		local_8c = a6;
		local_98 = local_88;
		if (local_9c <= iVar3)
		{
			iVar1 = iVar3 + 1;
		}
		sub_6FB0B250((Unicode*)aUStack_80, iVar3, iVar1, 0);
		local_9c = 0;
		iStack_84 = 0;
		D2Win_10131_GetTextDimensions(aUStack_80, &local_9c, &iStack_84);
		local_9c = (local_9c * 0xb) / 7;
		if (local_9c <= a7 - a5)
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar3 = local_8c;
			goto LAB_6fb0af12;
		}
	}
	D2Win_10127_SetFont(D2FONT_FONT6);
	iVar3 = a6 + -1;
LAB_6fb0af12:
	sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar3,
	    dword_6FBBA748 + a7, aUStack_80, local_98);
}

//D2Client.0x6FB0B0F0
uint32_t __fastcall sub_6FB0B0F0(Unicode* pUnicode, int a2, int a3)
{
	LPCSTR pCVar1;
	CHAR local_20[32];

	if ((a3 == 0) || (a2 < 0))
	{
		pCVar1 = "%d";
	}
	else
	{
		pCVar1 = "+%d";
	}
	wsprintfA(local_20, pCVar1, a2);
	Unicode::toUnicode((Unicode*)pUnicode, local_20, 0x20);
	return 1;
}

//D2Client.0x6FB0B140
void __fastcall sub_6FB0B140(Unicode* pUnicode, int a2, int a3, int a4, int a5)
{
	char* pcVar1;
	CHAR local_20[32];

	if (a5 != 0)
	{
		if (9999 < a2)
		{
			pcVar1 = "+";
			if (a4 == 0)
			{
				pcVar1 = &byte_6FB9A828;
			}
			wsprintfA(local_20, "%s%dK-%dK", pcVar1, (a2 + 500) / 1000, (a3 + 500) / 1000);
			goto LAB_6fb0b236;
		}
		if (9999 < a3)
		{
			pcVar1 = "+";
			if (a4 == 0)
			{
				pcVar1 = &byte_6FB9A828;
			}
			wsprintfA(local_20, "%s%d-%dK", pcVar1, a2, (a3 + 500) / 1000);
			goto LAB_6fb0b236;
		}
	}
	if (a4 == 0)
	{
		pcVar1 = "%d-%d";
	}
	else
	{
		pcVar1 = "+%d-%d";
	}
	wsprintfA(local_20, pcVar1, a2, a3);
LAB_6fb0b236:
	Unicode::toUnicode((Unicode*)pUnicode, local_20, 0x20);
}

//D2Client.0x6FB0B250
uint32_t __fastcall sub_6FB0B250(Unicode* pUnicode, int a2, int a3, int a4)
{
	LPCSTR pCVar1;
	CHAR local_20[32];

	if (a2 == a3)
	{
		if ((a4 == 0) || (a2 < 0))
		{
			pCVar1 = "%d";
		}
		else
		{
			pCVar1 = "+%d";
		}
		wsprintfA(local_20, pCVar1, a2);
		Unicode::toUnicode((Unicode*)pUnicode, local_20, 0x20);
		return 1;
	}
	sub_6FB0B140(pUnicode, a2, a3, a4, 1);
	return 1;
}

//D2Client.0x6FB0B2C0
uint32_t __fastcall sub_6FB0B2C0(D2UnitStrc* pUnit, uint32_t a2, int* a3, uint32_t* a4, int a5, int a6, D2SkillStrc* pSkill, uint32_t a8, D2UnitStrc* pUnit2, int a10)
{
	D2InventoryStrc* pInventory;
	short sVar1;
	D2SkillsTxt* pDVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;

	if (pSkill == nullptr)
	{
		return 0;
	}
	pDVar2 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
	if (pDVar2 == nullptr)
	{
		return 0;
	}
	pInventory = pUnit->pInventory;
	if (pInventory == nullptr)
	{
		return 0;
	}
	if (pUnit2 == nullptr)
	{
		pUnit2 = INVENTORY_GetLeftHandWeapon(pInventory);
		if (pUnit2 == nullptr)
		{
			iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x15, 0);
			iVar3 = iVar3 + 1;
			iVar4 = STATLIST_UnitGetStatValue(pUnit, 0x16, 0);
			iVar4 = iVar4 + 2;
			goto LAB_6fb0b39c;
		}
	}
	DATATBLS_GetItemsTxtRecord(pUnit2->dwClassId);
	if (a10 == 0)
	{
		iVar3 = INVENTORY_GetWieldType(pUnit, pInventory);
		if (iVar3 == 2)
		{
			iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x17, 0);
			iVar4 = STATLIST_UnitGetStatValue(pUnit, 0x18, 0);
		}
		else
		{
			iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x15, 0);
			iVar4 = STATLIST_UnitGetStatValue(pUnit, 0x16, 0);
		}
	}
	else
	{
		iVar3 = D2Common_11248(pUnit, pUnit2, 0x15);
		iVar4 = D2Common_11248(pUnit, pUnit2, 0x16);
	}
LAB_6fb0b39c:
	if (a8 == 0)
	{
		a8 = (uint32_t)pDVar2->nSrcDam;
	}
	if (a8 != 0x80)
	{
		iVar3 = (int)(iVar3 * a8 + ((int)(iVar3 * a8) >> 0x1f & 0x7fU)) >> 7;
		iVar4 = (int)(iVar4 * a8 + ((int)(iVar4 * a8) >> 0x1f & 0x7fU)) >> 7;
	}
	if (a8 != 0)
	{
		if (iVar3 < 1)
		{
			iVar3 = 1;
		}
		*(int*)a2 = *(int*)a2 + iVar3;
		if (iVar4 < 2)
		{
			iVar4 = 2;
		}
		*a3 = *a3 + iVar4;
	}
	iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x19, 0);
	iVar4 = SKILLS_GetWeaponMasteryBonus(pUnit, pUnit2, pSkill, 1);
	iVar4 = a5 + iVar3 + iVar4;
	iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x12, 0);
	iVar5 = STATLIST_UnitGetStatValue(pUnit, 0x11, 0);
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & (uint8_t)pDVar2->dwFlags[0]) != 0)
	{
		iVar6 = sub_6FB0B580();
		if (iVar6 != 0)
		{
			iVar4 = iVar4 + iVar6;
			*a4 = 3;
		}
	}
	iVar6 = 0;
	if (pUnit2 == nullptr)
	{
		iVar7 = STATLIST_UnitGetStatValue(pUnit, 0, 0);
		iVar4 = iVar4 + iVar7;
	}
	else
	{
		sVar1 = ITEMS_GetStrengthBonus(pUnit2);
		if (sVar1 != 0)
		{
			iVar6 = STATLIST_UnitGetStatValue(pUnit, 0, 0);
			iVar4 = iVar4 + (iVar6 * sVar1) / 100;
		}
		sVar1 = ITEMS_GetDexBonus(pUnit2);
		if (sVar1 != 0)
		{
			iVar6 = STATLIST_UnitGetStatValue(pUnit, 2, 0);
			iVar4 = iVar4 + (iVar6 * sVar1) / 100;
		}
		iVar6 = STATLIST_UnitGetItemStatOrSkillStatValue(pUnit2, 0x6f, 0);
	}
	iVar7 = STATES_CheckStateMaskDamBlueOnUnit(pUnit);
	if (iVar7 != 0)
	{
		*a4 = 3;
	}
	iVar7 = STATES_CheckStateMaskDamRedOnUnit(pUnit);
	if (iVar7 != 0)
	{
		*a4 = 1;
	}
	if (iVar4 < -0x59)
	{
		iVar4 = -0x5a;
	}
	*(int*)a2 = ((iVar3 + 100 + iVar4) * *(int*)a2) / 100 + iVar6 + a6;
	*a3 = ((iVar5 + 100 + iVar4) * *a3) / 100 + iVar6 + a6;
	return 1;
}

//D2Client.0x6FB0B580
int __cdecl sub_6FB0B580()
{
	short sVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	D2StatListStrc* pStatList;
	int iVar3;
	int iVar4;
	int local_10;
	int local_c;

	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		local_10 = 0;
		local_c = 0;
		iVar2 = *(int*)((uint8_t*)&sgptDataTables);
		if (0 < *(short*)(iVar2 + 0x170))
		{
			do
			{
				iVar2 = STATES_CheckState(pUnit, (int)*(short*)(*(int*)(iVar2 + 0x16c) + local_c * 2));
				if ((((iVar2 != 0) &&
				         (pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) +
				                                                                                         0x16c) +
				                                                                                 local_c * 2)),
				             pStatList != nullptr)) &&
				        (iVar2 = STATLIST_GetStatValue(pStatList, 0x15e, 0), 0 < iVar2)) &&
				    (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)))
				{
					iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c;
					if ((((iVar4 != 0) && (iVar3 = STATLIST_GetStatValue(pStatList, 0x15f, 0), 0 < iVar3)) &&
					        ((*(char*)(iVar4 + 0x44) == '\x01' &&
					            ((sVar1 = *(short*)(iVar4 + 0x54), -1 < sVar1 &&
					                                                   ((int)sVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4))))))) &&
					    (iVar4 = STATLIST_GetStatValue(pStatList, (int)sVar1, 0), 0 < iVar4))
					{
						if ((iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)) &&
						    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar2 != 0))
						{
							iVar2 = *(int*)(iVar2 + 0x14c) * (iVar3 + -1) + *(int*)(iVar2 + 0x148);
						}
						else
						{
							iVar2 = 0;
						}
						local_10 = local_10 + iVar2 * iVar4;
					}
				}
				local_c = local_c + 1;
				iVar2 = *(int*)((uint8_t*)&sgptDataTables);
			} while (local_c < *(short*)(iVar2 + 0x170));
		}
		return local_10;
	}
	return 0;
}

//D2Client.0x6FB0B6F0
void __fastcall sub_6FB0B6F0(D2UnitStrc* pUnit, int* a2, int* a3, uint32_t* a4, D2UnitStrc* pUnit2, D2SkillStrc* pSkill)
{
	uint32_t uVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;
	D2SkillsTxt* pDVar6;
	int* piVar7;
	uint64_t uVar8;
	uint32_t* local_4;

	local_4 = (uint32_t*)&byte_6FB6FB9C;
	piVar7 = (int*)(&dword_6FB6FB74);
	do
	{
		uVar1 = STATLIST_UnitGetStatValue(pUnit, piVar7[-2], 0);
		uVar2 = STATLIST_UnitGetStatValue(pUnit, piVar7[-1], 0);
		if ((*piVar7 != -1) && (uVar3 = STATLIST_UnitGetStatValue(pUnit, *piVar7, 0), uVar3 != 0))
		{
			if ((int)uVar1 < 0x100001)
			{
				if ((int)uVar3 < 0x10001)
				{
					iVar4 = (int)(uVar3 * uVar1) / 100;
				}
				else if ((int)(uVar3 & 0xfffffff0) < 0x640)
				{
					uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar1),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar1) >> 0x20),
					    100, 0);
					iVar4 = (int)uVar8;
				}
				else
				{
					iVar4 = ((int)uVar3 / 100) * uVar1;
				}
			}
			else if ((int)(uVar1 & 0xfffffff0) < 0x640)
			{
				uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar1),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar1) >> 0x20),
				    100, 0);
				iVar4 = (int)uVar8;
			}
			else
			{
				iVar4 = ((int)uVar1 / 100) * uVar3;
			}
			uVar1 = uVar1 + iVar4;
			if ((int)uVar2 < 0x100001)
			{
				if ((int)uVar3 < 0x10001)
				{
					iVar4 = (int)(uVar3 * uVar2) / 100;
				}
				else if ((int)(uVar3 & 0xfffffff0) < 0x640)
				{
					uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					iVar4 = (int)uVar8;
				}
				else
				{
					iVar4 = ((int)uVar3 / 100) * uVar2;
				}
			}
			else if ((int)(uVar2 & 0xfffffff0) < 0x640)
			{
				uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2) >> 0x20),
				    100, 0);
				iVar4 = (int)uVar8;
			}
			else
			{
				iVar4 = ((int)uVar2 / 100) * uVar3;
			}
			uVar2 = uVar2 + iVar4;
		}
		if ((int)uVar2 <= (int)uVar1)
		{
			uVar1 = uVar2;
		}
		*a2 = *a2 + uVar1;
		*a3 = *a3 + uVar2;
		if ((uVar1 != 0) || (uVar2 != 0))
		{
			*a4 = *local_4;
		}
		piVar7 = piVar7 + 3;
		local_4 = local_4 + 1;
	} while ((int)piVar7 < (int)&tbl_6FB6FBA4);
	uVar1 = STATLIST_UnitGetStatValue(pUnit, 0x39, 0);
	uVar2 = STATLIST_UnitGetStatValue(pUnit, 0x3a, 0);
	if (uVar2 != 0)
	{
		uVar3 = STATLIST_UnitGetStatValue(pUnit, 0x14c, 0);
		if (uVar3 != 0)
		{
			if ((int)uVar1 < 0x100001)
			{
				if ((int)uVar3 < 0x10001)
				{
					iVar4 = (int)(uVar3 * uVar1) / 100;
				}
				else if ((int)(uVar3 & 0xfffffff0) < 0x640)
				{
					uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar1),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar1) >> 0x20),
					    100, 0);
					iVar4 = (int)uVar8;
				}
				else
				{
					iVar4 = ((int)uVar3 / 100) * uVar1;
				}
			}
			else if ((int)(uVar1 & 0xfffffff0) < 0x640)
			{
				uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar1),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar1) >> 0x20),
				    100, 0);
				iVar4 = (int)uVar8;
			}
			else
			{
				iVar4 = ((int)uVar1 / 100) * uVar3;
			}
			uVar1 = uVar1 + iVar4;
			if ((int)uVar2 < 0x100001)
			{
				if ((int)uVar3 < 0x10001)
				{
					iVar4 = (int)(uVar3 * uVar2) / 100;
				}
				else if ((int)(uVar3 & 0xfffffff0) < 0x640)
				{
					uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					iVar4 = (int)uVar8;
				}
				else
				{
					iVar4 = ((int)uVar3 / 100) * uVar2;
				}
			}
			else if ((int)(uVar2 & 0xfffffff0) < 0x640)
			{
				uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2) >> 0x20),
				    100, 0);
				iVar4 = (int)uVar8;
			}
			else
			{
				iVar4 = ((int)uVar2 / 100) * uVar3;
			}
			uVar2 = uVar2 + iVar4;
		}
		iVar4 = STATLIST_UnitGetStatValue(pUnit, 0x65, 0);
		if (iVar4 < 1)
		{
			iVar5 = STATLIST_UnitGetStatValue(pUnit, 0x146, 0);
			if (iVar5 < 2)
			{
				iVar5 = 1;
			}
			iVar4 = STATLIST_UnitGetStatValue(pUnit, 0x3b, 0);
			iVar4 = iVar4 / iVar5;
		}
		*a4 = 2;
		*a2 = *a2 + ((int)(iVar4 * uVar1) >> 8);
		*a3 = *a3 + ((int)(iVar4 * uVar2) >> 8);
	}
	if (0 < *a3)
	{
		iVar4 = *a2;
		if (iVar4 < 1)
		{
			iVar4 = 1;
		}
		*a2 = iVar4;
		iVar5 = iVar4 + 1;
		if (iVar4 + 1 <= *a3)
		{
			iVar5 = *a3;
		}
		*a3 = iVar5;
	}
	if (((pSkill != nullptr) &&
	        (pDVar6 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill), pDVar6 != nullptr)) &&
	    (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & (uint8_t)pDVar6->dwFlags[0]) != 0))
	{
		sub_6FB0BB10(pUnit, a2, (uint32_t*)(a3), a4);
	}
	iVar4 = STATES_CheckStateMaskDamBlueOnUnit(pUnit);
	if (iVar4 != 0)
	{
		*a4 = 3;
	}
	iVar4 = STATES_CheckStateMaskDamRedOnUnit(pUnit);
	if (iVar4 != 0)
	{
		*a4 = 1;
	}
}

//D2Client.0x6FB0BB10
uint32_t __fastcall sub_6FB0BB10(D2UnitStrc* pUnit, int* a2, uint32_t* a3, uint32_t* a4)
{
	uint8_t bVar1;
	short sVar2;
	int iVar3;
	D2StatListStrc* pStatList;
	int iVar4;
	int nSkillLevel;
	uint32_t uVar5;
	int iVar6;
	int iVar7;
	int local_8;

	iVar3 = *(int*)((uint8_t*)&sgptDataTables);
	local_8 = 0;
	if (0 < *(short*)(iVar3 + 0x170))
	{
		do
		{
			iVar3 = STATES_CheckState(pUnit, (int)*(short*)(*(int*)(iVar3 + 0x16c) + local_8 * 2));
			if ((((iVar3 != 0) &&
			         (pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) +
			                                                                                         0x16c) +
			                                                                                 local_8 * 2)),
			             pStatList != nullptr)) &&
			        (iVar3 = STATLIST_GetStatValue(pStatList, 0x15e, 0), 0 < iVar3)) &&
			    (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)))
			{
				iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c;
				if (((iVar4 != 0) &&
				        (nSkillLevel = STATLIST_GetStatValue(pStatList, 0x15f, 0), 0 < nSkillLevel)) &&
				    ((sVar2 = *(short*)(iVar4 + 0x54), -1 < sVar2 &&
				                                           (((int)sVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4) &&
				                                               (iVar4 = STATLIST_GetStatValue(pStatList, (int)sVar2, 0), 0 < iVar4))))))
				{
					iVar7 = *(int*)((uint8_t*)&sgptDataTables);
					if ((iVar3 < *(int*)(iVar7 + 0xba0)) &&
					    ((((iVar6 = *(int*)(iVar7 + 0xb98) + iVar3 * 0x23c, iVar6 != 0 &&
					                                                            (iVar6 = (int)*(short*)(iVar6 + 0x194), -1 < iVar6)) &&
					          (iVar6 < *(int*)(iVar7 + 0xb94))) &&
					        (iVar7 = iVar6 * 0x120 + *(int*)(iVar7 + 0xb8c), iVar7 != 0))))
					{
						if (iVar4 < 2)
						{
							iVar4 = 1;
						}
						else if (2 < iVar4)
						{
							iVar4 = 3;
						}
						iVar6 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar7 + 0x20 + iVar4 * 4), iVar3, nSkillLevel);
						*a2 = *a2 + iVar6;
						iVar3 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar7 + 0x2c + iVar4 * 4), iVar3, nSkillLevel);
						*a3 = *a3 + iVar3;
						bVar1 = *(uint8_t*)(iVar7 + 0x1f + iVar4);
						if ((bVar1 != 0) && (bVar1 < 0xd))
						{
							switch (bVar1)
							{
							case 1:
								uVar5 = 1;
								break;
							case 2:
								uVar5 = 9;
								break;
							case 3:
							case 4:
								uVar5 = 3;
								break;
							case 5:
								uVar5 = 2;
								break;
							default:
								uVar5 = 0;
							}
							*a4 = uVar5;
						}
					}
					else
					{
						iVar4 = SKILLS_GetMinElemDamage(pUnit, iVar3, nSkillLevel, 1);
						*a2 = *a2 + (iVar4 >> 8);
						iVar3 = SKILLS_GetMaxElemDamage(pUnit, iVar3, nSkillLevel, 1);
						*a3 = *a3 + (iVar3 >> 8);
					}
				}
			}
			local_8 = local_8 + 1;
			iVar3 = *(int*)((uint8_t*)&sgptDataTables);
		} while (local_8 < *(short*)(iVar3 + 0x170));
	}
	return 1;
}

//D2Client.0x6FB0BD60
void __fastcall sub_6FB0BD60(D2UnitStrc* pUnit, int* a2, int* a3, uint8_t a4)
{
	int iVar1;
	int iVar2;
	int iVar3;

	switch (a4)
	{
	case 1:
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x30, 0);
		*a2 = *a2 + iVar1;
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x31, 0);
		*a3 = *a3 + iVar1;
		return;
	case 2:
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x32, 0);
		*a2 = *a2 + iVar1;
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x33, 0);
		*a3 = *a3 + iVar1;
		return;
	case 3:
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x34, 0);
		*a2 = *a2 + iVar1;
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x35, 0);
		*a3 = *a3 + iVar1;
		return;
	case 4:
	case 0xc:
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x36, 0);
		*a2 = *a2 + iVar1;
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x37, 0);
		*a3 = *a3 + iVar1;
		return;
	case 5:
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x65, 0);
		if (iVar1 < 1)
		{
			iVar2 = STATLIST_UnitGetStatValue(pUnit, 0x146, 0);
			if (iVar2 < 2)
			{
				iVar2 = 1;
			}
			iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x3b, 0);
			iVar1 = iVar1 / iVar2;
		}
		iVar2 = STATLIST_UnitGetStatValue(pUnit, 0x39, 0);
		iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x3a, 0);
		*a2 = *a2 + (iVar2 * iVar1 >> 8);
		*a3 = *a3 + (iVar3 * iVar1 >> 8);
	}
}
