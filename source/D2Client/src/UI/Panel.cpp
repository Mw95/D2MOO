#include "UI/Panel.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Engine/GfxUtil.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/SCmd.h"
#include "Sound/SoundInst.h"
#include "UI/CmdTbl.h"
#include "UI/Inv.h"
#include "UI/Mods.h"
#include "UI/NpcMenu.h"
#include "UI/Party.h"
#include "UI/SkillsTree.h"
#include "UI/Text.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB7CD70
int32_t dword_6FB7CD70 = 2;
//D2Client.0x6FB7CD74
uint8_t byte_6FB7CD74 = 1;
//D2Client.0x6FB7CD78
int32_t dword_6FB7CD78 = -1;
//D2Client.0x6FB7CD7C
int32_t dword_6FB7CD7C = -1;
//D2Client.0x6FB7CD80
int32_t dword_6FB7CD80 = -1;
//D2Client.0x6FB7CD90
uint32_t dword_6FB7CD90[4] = {0x17, 0x18, 0x19, 0x1A};
//D2Client.0x6FB7CDA0
uint32_t dword_6FB7CDA0[2] = {4, 5};
//D2Client.0x6FB7CDA8
uint32_t dword_6FB7CDA8 = 2;
//D2Client.0x6FB7CDC0
uint32_t dword_6FB7CDC0 = 0xA;
//D2Client.0x6FB7CE14
uint32_t dword_6FB7CE14 = 5;
//D2Client.0x6FB7CE18
uint32_t dword_6FB7CE18 = 1;
//D2Client.0x6FB7CE33
uint8_t tbl_6FB7CE33[1];
//D2Client.0x6FBB5E38
uint8_t byte_6FBB5E38;
//D2Client.0x6FBB5E39
uint8_t byte_6FBB5E39;
//D2Client.0x6FBB5E3A
uint8_t byte_6FBB5E3A;
//D2Client.0x6FBB5E3B
uint8_t byte_6FBB5E3B;
//D2Client.0x6FBB5E60
uint32_t dword_6FBB5E60[7];
//D2Client.0x6FBB5E90
uint8_t byte_6FBB5E90;
//D2Client.0x6FBB5E94
uint8_t byte_6FBB5E94;
//D2Client.0x6FBB5EA0
uint32_t dword_6FBB5EA0;
//D2Client.0x6FBB5EA4
int32_t dword_6FBB5EA4;
//D2Client.0x6FBB5EA8
int32_t dword_6FBB5EA8;
//D2Client.0x6FBB5EAC
int32_t dword_6FBB5EAC;
//D2Client.0x6FBB5EB0
int32_t dword_6FBB5EB0;
//D2Client.0x6FBB5EB4
D2UnitStrc* gpUnit_6FBB5EB4;
//D2Client.0x6FBB5EB8
uint32_t dword_6FBB5EB8;
//D2Client.0x6FBB5EBC
char byte_6FBB5EBC;
//D2Client.0x6FBB5EBD
char byte_6FBB5EBD;
//D2Client.0x6FBB5EBE
char byte_6FBB5EBE;
//D2Client.0x6FBB5EBF
char byte_6FBB5EBF;
//D2Client.0x6FBB5EC0
uint8_t byte_6FBB5EC0;
//D2Client.0x6FBB5EC4
uint8_t byte_6FBB5EC4;
//D2Client.0x6FBB5EDC
int32_t dword_6FBB5EDC;
//D2Client.0x6FBB5EE0
uint32_t dword_6FBB5EE0;
//D2Client.0x6FBB5EE4
uint32_t dword_6FBB5EE4;
//D2Client.0x6FBB5EE8
uint8_t byte_6FBB5EE8;
//D2Client.0x6FBB5EE9
uint8_t byte_6FBB5EE9;
//D2Client.0x6FBB5EEA
uint8_t byte_6FBB5EEA;
//D2Client.0x6FBB5EF0
int32_t dword_6FBB5EF0;
//D2Client.0x6FBB5EF4
uint8_t byte_6FBB5EF4;

//D2Client.0x6FAFE730
void __fastcall sub_6FAFE730(D2UnitStrc* pUnit, D2SkillStrc* pSkill, char* a3, int a4, uint32_t a5)
{
	D2SkillsTxt* pDVar1;
	int iVar2;
	D2ActiveRoomStrc* pRoom;
	int iVar3;
	int iStack_14;
	int iStack_10;
	uint32_t uStack_c;
	int iStack_8;
	D2CellFileStrc* pDStack_4;

	if ((pUnit != nullptr) && (pSkill != nullptr))
	{
		pDVar1 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
		if (pDVar1 != nullptr)
		{
			pDStack_4 = sub_6FB18700(&pDVar1->nSkillId);
			iVar2 = sub_6FB18770(pUnit, pSkill);
			if (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)((int)pDVar1->dwFlags + 1)) == 0)
			{
				pRoom = UNITS_GetRoom(pUnit);
				if (pRoom != nullptr)
				{
					iVar3 = DUNGEON_IsRoomInTown(pRoom);
					if (iVar3 != 0)
					{
						iVar2 = 1;
					}
				}
			}
			uStack_c = 0xffffffff;
			iStack_10 = 0;
			iStack_14 = 0;
			iStack_8 = SKILLS_GetSkillInfo(pSkill, &uStack_c, nullptr, &iStack_10, &iStack_14);
			if (iStack_8 == 0)
			{
				iStack_10 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
			}
			iVar3 = 0;
			if (iStack_8 == 0)
			{
				iVar3 = SKILLS_GetQuantity(pSkill);
			}
			sub_6FB18AC0(pDStack_4, &pDVar1->nSkillId, uStack_c, iStack_14, iVar2, a3, a4, a5);
			if (iVar3 != 0)
			{
				sub_6FB18790(&pDVar1->nSkillId, iVar2, iVar3, (int)a3, a4);
				return;
			}
			sub_6FB18940(&pDVar1->nSkillId, iVar2, iStack_10, iStack_14, (int)a3, a4);
		}
	}
}

//D2Client.0x6FAFE850
void __cdecl sub_6FAFE850()
{
	D2UnitStrc* pUnit;
	D2SkillStrc* pDVar1;
	int iVar2;
	char* pcVar3;
	int iVar4;

	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pDVar1 = UNITS_GetLeftSkill(pUnit);
		if (pDVar1 != nullptr)
		{
			iVar2 = SKILLS_GetSkillLevel(pUnit, pDVar1, 1);
			if (iVar2 < 1)
			{
				iVar4 = 0x280;
				pcVar3 = __FILE__;
				iVar2 = SKILLS_GetSkillIdFromSkill(pDVar1, __FILE__, __LINE__);
				SKILLS_RemoveSkill(pUnit, iVar2, pcVar3, iVar4);
				SKILLS_SetLeftActiveSkill(pUnit, 0, 0xffffffff);
				pDVar1 = UNITS_GetLeftSkill(pUnit);
			}
		}
		sub_6FAFE730(pUnit, pDVar1, (char*)(0x75), gnScreenHeight, 1);
		pDVar1 = UNITS_GetRightSkill(pUnit);
		if (pDVar1 != nullptr)
		{
			iVar2 = SKILLS_GetSkillLevel(pUnit, pDVar1, 1);
			if (iVar2 < 1)
			{
				iVar4 = 0x28b;
				pcVar3 = __FILE__;
				iVar2 = SKILLS_GetSkillIdFromSkill(pDVar1, __FILE__, __LINE__);
				SKILLS_RemoveSkill(pUnit, iVar2, pcVar3, iVar4);
				SKILLS_SetRightActiveSkill(pUnit, 0, 0xffffffff);
				pDVar1 = UNITS_GetRightSkill(pUnit);
			}
		}
		sub_6FAFE730(pUnit, pDVar1, (char*)(gnScreenWidth + -0xa5), gnScreenHeight, 0);
	}
}

//D2Client.0x6FAFE930
void __cdecl sub_6FAFE930()
{
	byte_6FBB5EE8 = D2Win_10034_MixRGB(0xff, 0, 0);
}

//D2Client.0x6FAFE950
void __cdecl sub_6FAFE950()
{
	byte_6FBB5EE9 = D2Win_10034_MixRGB(0xf4, 0xc0, 0x4c);
}

//D2Client.0x6FAFE970
void __cdecl sub_6FAFE970()
{
	byte_6FBB5EEA = D2Win_10034_MixRGB(0, 0, 0xff);
}

//D2Client.0x6FAFE990
void __cdecl sub_6FAFE990()
{
	byte_6FBB5E38 = D2Win_10034_MixRGB(0x80, 0, 0);
	byte_6FBB5E39 = D2Win_10034_MixRGB(0, 0x80, 0);
	byte_6FBB5E3A = D2Win_10034_MixRGB(0, 0, 0x80);
	byte_6FBB5E3B = D2Win_10034_MixRGB(0x80, 0x80, 0);
}

//D2Client.0x6FAFE9E0
bool __cdecl sub_6FAFE9E0()
{
	return dword_6FBB5EAC != 0;
}

//D2Client.0x6FAFE9F0
uint32_t __cdecl sub_6FAFE9F0()
{
	switch (dword_6FB7CD70)
	{
	case 0:
	case 5:
		return 3;
	case 1:
	case 4:
		return 2;
	case 2:
		return 1;
	default:
		return 4;
	}
}

//D2Client.0x6FAFEA40
void __cdecl sub_6FAFEA40()
{
	D2InventoryStrc* pInventory;
	uint8_t bVar1;
	uint8_t bVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t uVar6;
	D2ItemsTxt* pDVar7;
	D2UnitStrc* pItem;
	D2ItemsTxt* pDVar8;
	uint32_t uVar9;
	int iVar10;
	D2GfxDataStrc* pDVar11;
	int iVar12;
	uint32_t* puStack_f8;
	uint32_t uStack_f4;
	uint32_t uStack_e8;
	D2GfxDataStrc DStack_d8;
	D2GfxDataStrc DStack_90;
	D2GfxDataStrc DStack_48;

	byte_6FBB5EC0 = 0;
	byte_6FBB5EC4 = 0;
	pDVar3 = CUNIT_GetPlayer();
	pInventory = pDVar3->pInventory;
	pDVar3 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
	pDVar4 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
	if ((pDVar3 == nullptr) || (iVar5 = ITEMS_GetAmmoType(pDVar3), iVar5 == 0))
	{
	LAB_6fafea9a:
		if ((pDVar4 == nullptr) || (iVar5 = ITEMS_GetAmmoType(pDVar4), iVar5 == 0))
			goto LAB_6fafeb55;
		if (pDVar3 != nullptr)
		{
			iVar5 = ITEMS_GetAmmoType(pDVar4);
			iVar5 = ITEMS_CheckItemTypeId(pDVar3, iVar5);
			if (iVar5 != 0)
				goto LAB_6fafeb55;
		}
	}
	else if (pDVar4 != nullptr)
	{
		iVar5 = ITEMS_GetAmmoType(pDVar3);
		iVar5 = ITEMS_CheckItemTypeId(pDVar4, iVar5);
		if (iVar5 != 0)
			goto LAB_6fafea9a;
	}
	iVar12 = 0x9b;
	uVar6 = 0;
	iVar5 = gnScreenWidth + -0x37;
	do
	{
		if ((&byte_6FBB5EC0)[uVar6] == '\0')
		{
			(&byte_6FBB5EC0)[uVar6] = 1;
			iVar5 = iVar5 + uVar6 * -0x28;
			break;
		}
		uVar6 = uVar6 + 1;
	} while (uVar6 < 6);
	pDVar11 = &DStack_d8;
	for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1)
	{
		pDVar11->pCurrentCell = nullptr;
		pDVar11 = (D2GfxDataStrc*)&pDVar11->pCellFile;
	}
	DStack_d8.pCellFile = gpCellFile_6FBB5E58;
	DStack_d8.nDirection = 0;
	DStack_d8.nFrame = 2;
	iVar10 = sub_6FB23230(10);
	if (iVar10 != 0)
	{
		iVar10 = sub_6FAB12F0();
		if (iVar10 != 0)
		{
			iVar12 = 0xc6;
		}
		iVar12 = iVar12 + 0x1e;
	}
	TEXTURE_CelDraw(&DStack_d8, iVar5, iVar12, 0xffffffff, DRAWMODE_NORMAL, nullptr);
LAB_6fafeb55:
	uStack_e8 = 0;
	if (dword_6FB7CDA8 != 0)
	{
		do
		{
			pDVar3 = INVENTORY_GetItemFromBodyLoc(pInventory, dword_6FB7CDA0[uStack_e8]);
			if (((pDVar3 != nullptr) && (bVar1 = ITEMS_GetQtyWarnCount(pDVar3), bVar1 != 0)) &&
			    (uStack_f4 = 0, dword_6FB7CE14 != 0))
			{
				puStack_f8 = &dword_6FB7CDC0;
				do
				{
					if ((uint32_t)bVar1 == puStack_f8[-4])
					{
						pDVar7 = DATATBLS_GetItemsTxtRecord(pDVar3->dwClassId);
						uVar6 = STATLIST_UnitGetStatValue(pDVar3, 0x46, 0);
						iVar5 = ITEMS_IsMagSetRarUniCrfOrTmp(pDVar3);
						if (iVar5 == 0)
						{
							for (pDVar4 = INVENTORY_GetFirstItem(pInventory); pDVar4 != nullptr;
							     pDVar4 = INVENTORY_GetNextItem(pDVar4))
							{
								pItem = INVENTORY_UnitIsItem(pDVar4);
								if ((pItem != pDVar3) && (bVar2 = ITEMS_GetInvPage(pItem), bVar2 == 0))
								{
									if (pItem == nullptr)
									{
										iVar5 = -1;
									}
									else
									{
										iVar5 = pItem->dwClassId;
									}
									pDVar8 = DATATBLS_GetItemsTxtRecord(iVar5);
									if (pDVar8->dwCode == pDVar7->dwCode)
									{
										iVar5 = STATLIST_UnitGetStatValue(pItem, 0x46, 0);
										uVar6 = uVar6 + iVar5;
									}
								}
							}
						}
						if (*puStack_f8 < uVar6)
						{
							if (puStack_f8[-1] < uVar6)
							{
								if (puStack_f8[-2] < uVar6)
									goto LAB_6fafee1e;
								uVar6 = puStack_f8[-3];
								iVar12 = 0x9b;
								iVar5 = gnScreenWidth + -0x37;
								uVar9 = 0;
								do
								{
									if ((&byte_6FBB5EC0)[uVar9] == '\0')
									{
										(&byte_6FBB5EC0)[uVar9] = 1;
										iVar5 = iVar5 + uVar9 * -0x28;
										break;
									}
									uVar9 = uVar9 + 1;
								} while (uVar9 < 6);
								pDVar11 = &DStack_48;
								for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1)
								{
									pDVar11->pCurrentCell = nullptr;
									pDVar11 = (D2GfxDataStrc*)&pDVar11->pCellFile;
								}
								DStack_48.pCellFile = gpCellFile_6FBB5E58;
								DStack_48.nDirection = 0;
								DStack_48.nFrame = uVar6;
								iVar10 = sub_6FB23230(10);
								if (iVar10 != 0)
								{
									iVar10 = sub_6FAB12F0();
									if (iVar10 != 0)
									{
										iVar12 = 0xc6;
									}
									iVar12 = iVar12 + 0x1e;
								}
								pDVar11 = &DStack_48;
							}
							else
							{
								uVar6 = puStack_f8[-3];
								iVar12 = 0x9b;
								iVar5 = gnScreenWidth + -0x37;
								uVar9 = 0;
								do
								{
									if ((&byte_6FBB5EC0)[uVar9] == '\0')
									{
										(&byte_6FBB5EC0)[uVar9] = 1;
										iVar5 = iVar5 + uVar9 * -0x28;
										break;
									}
									uVar9 = uVar9 + 1;
								} while (uVar9 < 6);
								pDVar11 = &DStack_90;
								for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1)
								{
									pDVar11->pCurrentCell = nullptr;
									pDVar11 = (D2GfxDataStrc*)&pDVar11->pCellFile;
								}
								DStack_90.pCellFile = gpCellFile_6FBB5E58;
								DStack_90.nDirection = 0;
								DStack_90.nFrame = uVar6 + 1;
								iVar10 = sub_6FB23230(10);
								if (iVar10 != 0)
								{
									iVar10 = sub_6FAB12F0();
									if (iVar10 != 0)
									{
										iVar12 = 0xc6;
									}
									iVar12 = iVar12 + 0x1e;
								}
								pDVar11 = &DStack_90;
							}
						}
						else
						{
							uVar6 = puStack_f8[-3];
							iVar12 = 0x9b;
							iVar5 = gnScreenWidth + -0x37;
							uVar9 = 0;
							do
							{
								if ((&byte_6FBB5EC0)[uVar9] == '\0')
								{
									(&byte_6FBB5EC0)[uVar9] = 1;
									iVar5 = iVar5 + uVar9 * -0x28;
									break;
								}
								uVar9 = uVar9 + 1;
							} while (uVar9 < 6);
							pDVar11 = &DStack_d8;
							for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1)
							{
								pDVar11->pCurrentCell = nullptr;
								pDVar11 = (D2GfxDataStrc*)&pDVar11->pCellFile;
							}
							DStack_d8.pCellFile = gpCellFile_6FBB5E58;
							DStack_d8.nDirection = 0;
							DStack_d8.nFrame = uVar6 + 2;
							iVar10 = sub_6FB23230(10);
							if (iVar10 != 0)
							{
								iVar10 = sub_6FAB12F0();
								if (iVar10 != 0)
								{
									iVar12 = 0xc6;
								}
								iVar12 = iVar12 + 0x1e;
							}
							pDVar11 = &DStack_d8;
						}
						TEXTURE_CelDraw(pDVar11, iVar5, iVar12, 0xffffffff, DRAWMODE_NORMAL, nullptr);
					}
				LAB_6fafee1e:
					uStack_f4 = uStack_f4 + 1;
					puStack_f8 = puStack_f8 + 5;
				} while (uStack_f4 < dword_6FB7CE14);
			}
			uStack_e8 = uStack_e8 + 1;
		} while (uStack_e8 < dword_6FB7CDA8);
	}
}

//D2Client.0x6FAFEE70
void __cdecl sub_6FAFEE70()
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int* piVar7;
	D2GfxDataStrc* pDVar8;
	int iStack_58;
	int iStack_54;
	int* piStack_50;
	D2GfxDataStrc DStack_48;

	pDVar1 = CUNIT_GetPlayer();
	pInventory = pDVar1->pInventory;
	piVar7 = (int*)(&dword_6FB7CE18);
	while ((((pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, *piVar7), pDVar1 == nullptr || (iVar2 = ITEMS_HasDurability(pDVar1), iVar2 == 0)) ||
	            (uVar3 = ITEMS_CheckIfStackable(pDVar1), uVar3 != 0)) ||
	        ((iVar2 = STATLIST_GetMaxDurabilityFromUnit(pDVar1), iVar2 == 0 ||
	                                                                 (iVar4 = STATLIST_UnitGetStatValue(pDVar1, 0x48, 0), 0x14 < (iVar4 * 100) / iVar2)))))
	{
		piVar7 = piVar7 + 1;
		if ((int)&tbl_6FB7CE33 < (int)piVar7)
		{
			return;
		}
	}
	piStack_50 = (int*)(&dword_6FB7CE18);
	do
	{
		iVar2 = *piStack_50;
		pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, iVar2);
		iVar4 = 0;
		iStack_54 = 0;
		iStack_58 = 0;
		if (pDVar1 == nullptr)
		{
			if ((iVar2 != 4) && (iVar2 != 5))
				goto LAB_6fafef84;
		}
		else
		{
			iVar5 = ITEMS_HasDurability(pDVar1);
			if ((iVar5 != 0) && (uVar3 = ITEMS_CheckIfStackable(pDVar1), uVar3 == 0))
			{
				iVar5 = STATLIST_GetMaxDurabilityFromUnit(pDVar1);
				iStack_54 = ITEMS_CheckItemTypeId(pDVar1, 0x33);
				iStack_58 = ITEMS_GetQuiverType(pDVar1);
				if (iVar5 != 0)
				{
					iVar6 = STATLIST_UnitGetStatValue(pDVar1, 0x48, 0);
					iVar5 = (iVar6 * 100) / iVar5;
					if (iVar5 < 1)
					{
						iVar4 = 2;
					}
					else if (iVar5 < 0x15)
					{
						iVar4 = 1;
					}
				}
			}
		LAB_6fafef84:
			uVar3 = iVar4 * 0xb;
			switch (iVar2)
			{
			case 1:
				uVar3 = uVar3 + 1;
				break;
			case 3:
				uVar3 = uVar3 + 4;
				break;
			case 4:
				if (iStack_58 == 0)
				{
					if (iStack_54 == 0)
					{
						uVar3 = uVar3 + 6;
					}
					else
					{
						uVar3 = uVar3 + 7;
					}
				}
				else
				{
					uVar3 = uVar3 + 10;
				}
				break;
			case 5:
				if (iStack_58 == 0)
				{
					if (iStack_54 == 0)
					{
						uVar3 = uVar3 + 8;
					}
					else
					{
						uVar3 = uVar3 + 5;
					}
				}
				else
				{
					uVar3 = uVar3 + 9;
				}
				break;
			case 8:
				uVar3 = uVar3 + 2;
				break;
			case 9:
				uVar3 = uVar3 + 3;
			}
			iVar4 = 0;
			pDVar8 = &DStack_48;
			for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				pDVar8->pCurrentCell = nullptr;
				pDVar8 = (D2GfxDataStrc*)&pDVar8->pCellFile;
			}
			DStack_48.nDirection = 0;
			DStack_48.pCellFile = gpCellFile_6FBB5E28;
			DStack_48.nFrame = uVar3;
			iVar2 = sub_6FB23230(10);
			if (iVar2 == 0)
			{
				iVar4 = 0x6e;
			}
			else
			{
				iVar2 = sub_6FAB12F0();
				if (iVar2 != 0)
				{
					iVar4 = 0x2b;
				}
				iVar4 = iVar4 + 0x8c;
			}
			TEXTURE_CelDraw(&DStack_48, gnScreenWidth + -0x3c, iVar4, 0xffffffff, DRAWMODE_TRANS50, nullptr);
		}
		piStack_50 = piStack_50 + 1;
		if ((int)&tbl_6FB7CE33 < (int)piStack_50)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FAFF0B0
void __cdecl sub_6FAFF0B0()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	Unicode* pUVar4;
	int iVar5;
	Unicode local_258[100];
	Unicode aUStack_190[100];
	Unicode aUStack_c8[100];

	pDVar1 = CUNIT_GetPlayer();
	iVar2 = sub_6FB57BC0();
	iVar3 = sub_6FB57BD0();
	if ((((0x1d < iVar2) && (iVar2 < 0x6f)) && (gnScreenHeight + -0x4b <= iVar3)) &&
	    (iVar3 <= gnScreenHeight + -0xf))
	{
		iVar2 = sub_6FAFF2D0(6);
		iVar2 = iVar2 >> 8;
		iVar3 = STATLIST_GetMaxLifeFromUnit(pDVar1);
		iVar3 = iVar3 >> 8;
		pDVar1 = CUNIT_GetPlayer();
		if (((pDVar1 != nullptr) && (pDVar1->dwUnitType == 0)) &&
		    ((pDVar1->dwAnimMode != 0x11 && ((-1 < iVar2 && (iVar2 < 2))))))
		{
			iVar2 = 1;
		}
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1045));
		Unicode::sprintf(100, aUStack_190, pUVar4, iVar2, iVar3);
		Unicode::strcat(local_258, aUStack_190);
		iVar2 = D2Win_10121_GetTextWidth(local_258);
		D2Win_10117_DrawText(local_258, 0x41 - iVar2 / 2, gnScreenHeight + -0x5f, 0, 0);
		return;
	}
	if (((gnScreenWidth + -0x6f <= iVar2) && (iVar2 <= gnScreenWidth + -0x1f)) &&
	    ((gnScreenHeight + -0x4b <= iVar3 && (iVar3 <= gnScreenHeight + -0xf))))
	{
		iVar2 = sub_6FAFF2D0(8);
		iVar2 = iVar2 >> 8;
		iVar3 = STATLIST_GetMaxManaFromUnit(pDVar1);
		pUVar4 = aUStack_190;
		iVar3 = iVar3 >> 8;
		iVar5 = 100;
		do
		{
			pUVar4 = pUVar4 + 1;
			iVar5 = iVar5 + -1;
		} while (iVar5 != 0);
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1046));
		Unicode::sprintf(100, aUStack_190, pUVar4, iVar2, iVar3);
		Unicode::strcat(local_258, aUStack_190);
		iVar2 = D2Win_10121_GetTextWidth(local_258);
		D2Win_10117_DrawText(local_258, (gnScreenWidth - iVar2 / 2) + -0x41, gnScreenHeight + -0x5f, 0, 0);
	}
}

//D2Client.0x6FAFF2D0
int __fastcall sub_6FAFF2D0(int a1)
{
	int iVar1;
	bool bVar2;
	D2UnitStrc* pUnit;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int64_t lVar10;

	bVar2 = true;
	pUnit = CUNIT_GetPlayer();
	iVar3 = STATLIST_UnitGetStatValue(pUnit, a1, 0);
	if (a1 == 6)
	{
		iVar4 = STATLIST_GetMaxLifeFromUnit(pUnit);
		iVar9 = 0;
		bVar2 = false;
	}
	else if (a1 == 8)
	{
		iVar4 = STATLIST_GetMaxManaFromUnit(pUnit);
		iVar9 = 1;
	}
	else
	{
		if (a1 != 10)
		{
			return 0;
		}
		iVar4 = STATLIST_GetMaxStaminaFromUnit(pUnit);
		iVar9 = 2;
	}
	if (iVar4 == 0)
	{
		return 0;
	}
	uVar5 = sub_6FAABF80();
	if (uVar5 < 2)
	{
		dword_6FBB5E60[iVar9 * 4 + 1] = iVar3;
		(&dword_6FBB5E5C)[iVar9 * 4] = iVar3;
	}
	if ((!bVar2) && (iVar3 < (int)(&dword_6FBB5E5C)[iVar9 * 4]))
	{
		dword_6FBB5E60[iVar9 * 4 + 1] = iVar3;
		(&dword_6FBB5E5C)[iVar9 * 4] = iVar3;
		uVar6 = sub_6FAABF80();
		dword_6FBB5E60[iVar9 * 4] = uVar6;
		dword_6FBB5E60[iVar9 * 4 + 2] = uVar6;
	}
	iVar8 = (&dword_6FBB5E5C)[iVar9 * 4];
	if (iVar8 != iVar3)
	{
		iVar7 = iVar8 - iVar3;
		if (iVar7 < 0)
		{
			iVar7 = -iVar7;
		}
		if (iVar7 < (int)(iVar4 + (iVar4 >> 0x1f & 7U)) >> 3)
		{
			dword_6FBB5E60[iVar9 * 4 + 2] = dword_6FBB5E60[iVar9 * 4];
			if (iVar3 == iVar4)
			{
				dword_6FBB5E60[iVar9 * 4 + 1] = iVar3;
			}
			else
			{
				dword_6FBB5E60[iVar9 * 4 + 1] = iVar8;
			}
		}
		else
		{
			dword_6FBB5E60[iVar9 * 4 + 1] = iVar3;
			uVar6 = sub_6FAABF80();
			dword_6FBB5E60[iVar9 * 4 + 2] = uVar6;
		}
		(&dword_6FBB5E5C)[iVar9 * 4] = iVar3;
		uVar6 = sub_6FAABF80();
		dword_6FBB5E60[iVar9 * 4] = uVar6;
	}
	iVar8 = dword_6FBB5E60[iVar9 * 4];
	iVar7 = sub_6FAABF80();
	iVar7 = iVar7 - iVar8;
	iVar8 = iVar8 - dword_6FBB5E60[iVar9 * 4 + 2];
	if (iVar8 < 7)
	{
		iVar8 = 7;
	}
	else if (0xf < iVar8)
	{
		iVar8 = 0xf;
	}
	if ((0 < iVar3) && (iVar7 < iVar8))
	{
		iVar1 = dword_6FBB5E60[iVar9 * 4 + 1];
		iVar9 = (&dword_6FBB5E5C)[iVar9 * 4] - iVar1;
		if (iVar9 != 0)
		{
			lVar10 = (int64_t)(((double)(iVar7 + 1) / (double)iVar8) * (double)iVar9);
			iVar3 = (int)lVar10 + iVar1;
		}
	}
	if (iVar3 < 0)
	{
		return 0;
	}
	if (iVar4 < iVar3)
	{
		iVar3 = iVar4;
	}
	return iVar3;
}

//D2Client.0x6FAFF480
void __cdecl sub_6FAFF480()
{
	DisplayType DVar1;
	D2GameResolutionMode DVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	D2GfxDataStrc* pDVar7;
	D2GfxDataStrc DStack_110;
	uint8_t auStack_c8[200];

	DVar1 = D2GFX_GetDisplayType();
	uVar6 = (uint32_t)(DVar1 == DISPLAYTYPE_DDRAW);
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		iVar3 = sub_6FAB5750();
		if ((iVar3 == 2) || (iVar3 = sub_6FAB5750(), iVar3 == 3))
		{
			pDVar7 = &DStack_110;
			for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				pDVar7->pCurrentCell = nullptr;
				pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
			}
			if (gpCellFile_6FBB5E3C == nullptr)
			{
				gpCellFile_6FBB5E3C = sub_6FB20100("Panel\\800BorderFrame");
			}
			DStack_110.nDirection = 0;
			DStack_110.nFrame = 0;
			DStack_110.pCellFile = gpCellFile_6FBB5E3C;
			TEXTURE_CelDraw(&DStack_110, 0, 0xfd, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_110.nFrame = 1;
			TEXTURE_CelDraw(&DStack_110, 0x100, 0x3f, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_110.nFrame = 2;
			TEXTURE_CelDraw(&DStack_110, 0, 0x1e4, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_110.nFrame = 3;
			TEXTURE_CelDraw(&DStack_110, 0, 0x229, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_110.nFrame = 4;
			TEXTURE_CelDraw(&DStack_110, 0x100, 0x229, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		}
		iVar3 = sub_6FAB5750();
		if ((iVar3 == 1) || (iVar3 = sub_6FAB5750(), iVar3 == 3))
		{
			if (gpCellFile_6FBB5E3C == nullptr)
			{
				gpCellFile_6FBB5E3C = sub_6FB20100("Panel\\800BorderFrame");
			}
			pDVar7 = &DStack_110;
			for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				pDVar7->pCurrentCell = nullptr;
				pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
			}
			DStack_110.nDirection = 0;
			DStack_110.nFrame = 5;
			DStack_110.pCellFile = gpCellFile_6FBB5E3C;
			TEXTURE_CelDraw(&DStack_110, 400, 0x3f, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_110.nFrame = 6;
			TEXTURE_CelDraw(&DStack_110, 0x220, 0xfd, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_110.nFrame = 7;
			TEXTURE_CelDraw(&DStack_110, 0x2c9, 0x1e4, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_110.nFrame = 8;
			TEXTURE_CelDraw(&DStack_110, 0x220, 0x229, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_110.nFrame = 9;
			TEXTURE_CelDraw(&DStack_110, 400, 0x229, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		}
	}
	pDVar7 = &DStack_110;
	for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		pDVar7->pCurrentCell = nullptr;
		pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
	}
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		if (gpCellFile_6FBB5E44 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBB5E44);
			gpCellFile_6FBB5E44 = nullptr;
		}
		if (gpCellFile_6FBB5E54 == nullptr)
		{
			gpCellFile_6FBB5E54 = sub_6FB20100("Panel\\800CtrlPnl7");
		}
		DStack_110.nDirection = 0;
		DStack_110.nFrame = 0;
		DStack_110.pCellFile = gpCellFile_6FBB5E54;
		TEXTURE_CelDraw(&DStack_110, 0, gnScreenHeight - uVar6, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_110.nFrame = 1;
		TEXTURE_CelDraw(&DStack_110, 0xa5, gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_110.nFrame = 2;
		TEXTURE_CelDraw(&DStack_110, 0x125, gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_110.nFrame = 3;
		TEXTURE_CelDraw(&DStack_110, 0x1a5, gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_110.nFrame = 4;
		TEXTURE_CelDraw(&DStack_110, 0x225, gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		iVar3 = gnScreenHeight - uVar6;
		DStack_110.nFrame = 5;
	}
	else
	{
		if (gpCellFile_6FBB5E44 == nullptr)
		{
			gpCellFile_6FBB5E44 = sub_6FB20100("Panel\\CtrlPnl7");
		}
		if (gpCellFile_6FBB5E54 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBB5E54);
			gpCellFile_6FBB5E54 = nullptr;
		}
		if (gpCellFile_6FBB5E3C != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBB5E3C);
			gpCellFile_6FBB5E3C = nullptr;
		}
		DStack_110.pCellFile = gpCellFile_6FBB5E44;
		DStack_110.nDirection = 0;
		DStack_110.nFrame = 0;
		TEXTURE_CelDraw(&DStack_110, 0, gnScreenHeight - uVar6, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_110.nFrame = 1;
		TEXTURE_CelDraw(&DStack_110, gnScreenWidth / 2 + -0x9b, gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL,
		    nullptr);
		DStack_110.nFrame = 2;
		TEXTURE_CelDraw(&DStack_110, gnScreenWidth / 2 + -0x1b, gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL,
		    nullptr);
		DStack_110.nFrame = 3;
		TEXTURE_CelDraw(&DStack_110, gnScreenWidth / 2 + 0x65, gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL,
		    nullptr);
		iVar3 = gnScreenHeight - uVar6;
		DStack_110.nFrame = 4;
	}
	TEXTURE_CelDraw(&DStack_110, gnScreenWidth + -0x75, iVar3, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	sub_6FAFF9D0();
	sub_6FAFFB60();
	sub_6FAFFCA0();
	iVar3 = sub_6FB57BC0();
	iVar4 = sub_6FB57BD0();
	memset(auStack_c8, 0, 2 * (100));
	pDVar7 = &DStack_110;
	for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		pDVar7->pCurrentCell = nullptr;
		pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
	}
	DStack_110.nDirection = 0;
	DStack_110.pCellFile = gpCellFile_6FBB5E48;
	iVar5 = sub_6FAA8B30();
	if (iVar5 == 0)
	{
		if (dword_6FBB5EE4 != 0)
		{
			iVar5 = sub_6FAFFF90(iVar3, iVar4);
			DStack_110.nFrame = 1;
			if (iVar5 != 0)
				goto LAB_6faff93c;
		}
		DStack_110.nFrame = 0;
	}
	else if ((dword_6FBB5EE4 == 0) || (iVar5 = sub_6FAFFF90(iVar3, iVar4), iVar5 == 0))
	{
		DStack_110.nFrame = 2;
	}
	else
	{
		DStack_110.nFrame = 3;
	}
LAB_6faff93c:
	TEXTURE_CelDraw(&DStack_110, gnScreenWidth / 2 + -0x91, gnScreenHeight + -10, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	if ((((gnScreenWidth / 2 + -0x91 <= iVar3) && (iVar3 <= gnScreenWidth / 2 + -0x80)) &&
	        (gnScreenHeight + -0x1c <= iVar4)) &&
	    (iVar4 <= gnScreenHeight + -8))
	{
		sub_6FAFFE60();
	}
	sub_6FAFFFD0();
	sub_6FB001B0();
	sub_6FB002B0();
	sub_6FAFE850();
	sub_6FB00990();
	sub_6FB00C10();
	sub_6FB00C40();
}

//D2Client.0x6FAFF9D0
void __cdecl sub_6FAFF9D0()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	DisplayType DVar4;
	D2GfxDataStrc* pDVar5;
	uint16_t nLayer;
	int iVar6;
	D2GfxDataStrc DStack_48;

	pDVar1 = CUNIT_GetPlayer();
	iVar2 = sub_6FAFF2D0(6);
	iVar3 = STATLIST_GetMaxLifeFromUnit(pDVar1);
	if (iVar3 != 0)
	{
		iVar3 = (iVar2 * 0x50) / iVar3;
		if ((((0 < iVar3) && (iVar3 < 3)) && (pDVar1 = CUNIT_GetPlayer(), pDVar1 != nullptr)) &&
		    ((pDVar1->dwUnitType == 0 && (pDVar1->dwAnimMode != 0x11))))
		{
			iVar3 = 2;
		}
		iVar6 = 100;
		pDVar5 = &DStack_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar5->pCurrentCell = nullptr;
			pDVar5 = (D2GfxDataStrc*)&pDVar5->pCellFile;
		}
		DStack_48.nDirection = 0;
		DStack_48.pCellFile = gpCellFile_6FBB5E30;
		DStack_48.nFrame = 0;
		pDVar1 = CUNIT_GetPlayer();
		iVar2 = STATES_CheckState(pDVar1, iVar6);
		if (iVar2 != 0)
		{
			nLayer = 0;
			iVar2 = 0x4a;
			pDVar1 = CUNIT_GetPlayer();
			iVar2 = STATLIST_UnitGetStatValue(pDVar1, iVar2, nLayer);
			iVar2 = (iVar2 * 0x50) / 100;
			if (0x50 < iVar2)
			{
				iVar2 = 0x50;
			}
			if (iVar3 < iVar2)
			{
				DVar4 = D2GFX_GetDisplayType();
				if (DVar4 == DISPLAYTYPE_DIRECT3D)
				{
					iVar6 = 0x1c;
				}
				else
				{
					iVar6 = 0x1d;
				}
				TEXTURE_CelDrawEx(&DStack_48, iVar6, gnScreenHeight + -0xd, iVar3, iVar2 - iVar3, DRAWMODE_TRANS25);
			}
		}
		iVar2 = 2;
		pDVar1 = CUNIT_GetPlayer();
		iVar2 = STATES_CheckState(pDVar1, iVar2);
		DStack_48.nFrame = -(uint32_t)(iVar2 != 0) & 2;
		if (iVar3 != 0)
		{
			D2GFX_GetDisplayType();
			TEXTURE_CelDrawEx(&DStack_48, 0x1d, gnScreenHeight + -0xd, 0, iVar3, DRAWMODE_NORMAL);
		}
		DStack_48.pCellFile = gpCellFile_6FBB5E8C;
		DStack_48.nFrame = 0;
		TEXTURE_CelDraw(&DStack_48, 0x1c, gnScreenHeight + -5, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
}

//D2Client.0x6FAFFB60
void __cdecl sub_6FAFFB60()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	DisplayType DVar4;
	D2GfxDataStrc* pDVar5;
	uint16_t nLayer;
	int iVar6;
	D2GfxDataStrc DStack_48;

	pDVar1 = CUNIT_GetPlayer();
	iVar2 = sub_6FAFF2D0(8);
	iVar3 = STATLIST_GetMaxManaFromUnit(pDVar1);
	if (iVar3 != 0)
	{
		if (iVar3 < iVar2)
		{
			iVar2 = iVar3;
		}
		iVar3 = (iVar2 * 0x50) / iVar3;
		iVar6 = 0x6a;
		pDVar5 = &DStack_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar5->pCurrentCell = nullptr;
			pDVar5 = (D2GfxDataStrc*)&pDVar5->pCellFile;
		}
		DStack_48.nDirection = 0;
		DStack_48.pCellFile = gpCellFile_6FBB5E30;
		DStack_48.nFrame = 1;
		pDVar1 = CUNIT_GetPlayer();
		iVar2 = STATES_CheckState(pDVar1, iVar6);
		if (iVar2 != 0)
		{
			nLayer = 0;
			iVar2 = 0x1a;
			pDVar1 = CUNIT_GetPlayer();
			iVar2 = STATLIST_UnitGetStatValue(pDVar1, iVar2, nLayer);
			iVar2 = (iVar2 * 0x50) / 100;
			if (0x50 < iVar2)
			{
				iVar2 = 0x50;
			}
			if (iVar3 < iVar2)
			{
				DVar4 = D2GFX_GetDisplayType();
				if (DVar4 == DISPLAYTYPE_DIRECT3D)
				{
					iVar6 = gnScreenWidth + -0x70;
				}
				else
				{
					iVar6 = gnScreenWidth + -0x6f;
				}
				TEXTURE_CelDrawEx(&DStack_48, iVar6, gnScreenHeight + -0xd, iVar3, iVar2 - iVar3, DRAWMODE_TRANS25);
			}
		}
		D2GFX_GetDisplayType();
		TEXTURE_CelDrawEx(&DStack_48, gnScreenWidth + -0x6f, gnScreenHeight + -0xd, 0, iVar3, DRAWMODE_NORMAL);
		DStack_48.pCellFile = gpCellFile_6FBB5E8C;
		DStack_48.nFrame = 1;
		TEXTURE_CelDraw(&DStack_48, gnScreenWidth + -0x6e, gnScreenHeight + -9, 0xffffffff, DRAWMODE_NORMAL,
		    nullptr);
	}
}

//D2Client.0x6FAFFCA0
void __cdecl sub_6FAFFCA0()
{
	D2UnitStrc* pUnit;
	uint32_t uVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	Unicode* pUVar7;
	uint32_t uVar8;
	int local_e0;
	int iStack_dc;
	Unicode aUStack_c8[100];

	pUnit = CUNIT_GetPlayer();
	if (pUnit == nullptr)
	{
		local_e0 = -1;
	}
	else
	{
		local_e0 = pUnit->dwClassId;
	}
	uVar1 = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
	uVar2 = STATLIST_UnitGetStatValue(pUnit, 0xd, 0);
	uVar3 = STATLIST_GetUnitBaseStat(pUnit, 0xc, 0);
	uVar3 = DATATBLS_GetLevelThreshold(local_e0, uVar3);
	uVar4 = DATATBLS_GetLevelThreshold(local_e0, uVar1 - 1);
	uVar8 = uVar3 - uVar4;
	if (uVar4 < uVar2)
	{
		uVar4 = uVar2 - uVar4;
	}
	else
	{
		uVar4 = 0;
	}
	iVar5 = sub_6FB57BC0();
	iVar6 = sub_6FB57BD0();
	if ((gnScreenWidth / 2 + -0x92 <= iVar5) && (iVar5 <= gnScreenWidth / 2 + -0x17))
	{
		if ((gnScreenHeight + -0x2b <= iVar6) && (iVar6 <= gnScreenHeight + -0x22))
		{
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1043));
			Unicode::sprintf(100, aUStack_c8, pUVar7, uVar2, uVar3);
			D2Win_10129_DrawFramedText(aUStack_c8, gnScreenWidth / 2 + -0x92, gnScreenHeight + -0x33, 0, 1);
		}
	}
	if (uVar8 != 0)
	{
		if (0x226b901 < uVar4)
		{
			uVar4 = uVar4 >> 7;
			uVar8 = uVar8 >> 7;
		}
		uVar8 = (uVar4 * 0x77) / uVar8;
		if (0x77 < uVar8)
		{
			uVar8 = 0;
		}
		uVar2 = DATATBLS_GetMaxLevel(local_e0);
		iVar5 = gnScreenHeight;
		if ((uVar1 < uVar2) && (uVar8 != 0))
		{
			iVar6 = gnScreenWidth / 2 + -0x90;
			D2GFX_DrawLine(iVar6, gnScreenHeight + -0x26, uVar8 + iVar6, gnScreenHeight + -0x26, 0xff, 0xff);
			D2GFX_DrawLine(iVar6, iVar5 + -0x25, uVar8 + iVar6, iVar5 + -0x25, 0xff, 0xff);
		}
	}
}

//D2Client.0x6FAFFE60
void __cdecl sub_6FAFFE60()
{
	Unicode* pUVar1;
	uint32_t uVar2;
	Unicode* pUVar3;
	int iVar4;
	Unicode aUStack_1cc[30];
	Unicode local_190[200];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1053));
	Unicode::strcpy(local_190, pUVar1);
	uVar2 = sub_6FAD4B60(0x23, 1);
	if ((short)uVar2 != -1)
	{
		pUVar1 = aUStack_1cc;
		for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*(uint32_t*)pUVar1 = 0;
			pUVar1 = pUVar1 + 2;
		}
		pUVar1 = sub_6FAD56B0(0x23, 1);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1052));
		Unicode::sprintf(0x1e, aUStack_1cc, pUVar3, pUVar1);
		Unicode::strcat(local_190, aUStack_1cc);
	}
	uVar2 = sub_6FAD4B60(0x23, 0);
	if ((short)uVar2 != -1)
	{
		pUVar1 = aUStack_1cc;
		for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*(uint32_t*)pUVar1 = 0;
			pUVar1 = pUVar1 + 2;
		}
		pUVar1 = sub_6FAD56B0(0x23, 0);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1052));
		Unicode::sprintf(0x1e, aUStack_1cc, pUVar3, pUVar1);
		Unicode::strcat(local_190, aUStack_1cc);
	}
	D2Win_10129_DrawFramedText(local_190, gnScreenWidth / 2 + -0x91, gnScreenHeight + -0x17, 0, 1);
}

//D2Client.0x6FAFFF90
uint32_t __fastcall sub_6FAFFF90(int a1, int a2)
{
	if ((((gnScreenWidth / 2 + -0x91 <= a1) && (a1 <= gnScreenWidth / 2 + -0x80)) &&
	        (gnScreenHeight + -0x1c <= a2)) &&
	    (a2 <= gnScreenHeight + -8))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FAFFFD0
void __cdecl sub_6FAFFFD0()
{
	uint8_t bVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	Unicode* pUVar7;
	int nTextColor;
	uint32_t uVar8;
	int iStack_d4;
	Unicode aUStack_c8[100];

	pUnit = CUNIT_GetPlayer();
	iVar2 = sub_6FAFF2D0(10);
	iVar3 = STATLIST_GetMaxStaminaFromUnit(pUnit);
	if (byte_6FBB5EE8 == '\0')
	{
		bVar1 = D2Win_10034_MixRGB(0xff, 0, 0);
		byte_6FBB5EE8 = CONCAT31(byte_6FBB5EE9, bVar1);
		bVar1 = D2Win_10034_MixRGB(0xf4, 0xc0, 0x4c);
		byte_6FBB5EE8 = CONCAT11(bVar1, byte_6FBB5EE8);
		bVar1 = D2Win_10034_MixRGB(0, 0, 0xff);
		byte_6FBB5EE8 = CONCAT12(bVar1, byte_6FBB5EE8);
	}
	bVar1 = byte_6FBB5EE9;
	if (iVar3 + 5 < iVar2)
	{
	LAB_6fb00056:
		iVar3 = iVar2;
		bVar1 = byte_6FBB5EEA;
	}
	else
	{
		iVar4 = STATES_CheckStateMaskOnUnit(pUnit, 0x18);
		if (iVar4 != 0)
			goto LAB_6fb00056;
	}
	uVar8 = (uint32_t)bVar1;
	if (iVar3 < 1)
	{
		iVar3 = 0;
	LAB_6fb0007e:
		uVar8 = byte_6FBB5EE8 & 0xff;
	}
	else
	{
		iVar3 = (iVar2 * 0x66) / iVar3;
		if (iVar3 < 0x19)
			goto LAB_6fb0007e;
	}
	sub_6FB5B0F0(gnScreenWidth / 2 + -0x7f, gnScreenHeight + -0x1b, iVar3, 0x12, uVar8, (DrawMode)(2));
	iVar2 = sub_6FB57BC0();
	iVar4 = sub_6FB57BD0();
	iVar3 = sub_6FAFF2D0(10);
	iVar3 = (int)(iVar3 + (iVar3 >> 0x1f & 0xffU)) >> 8;
	iVar5 = STATLIST_GetMaxStaminaFromUnit(pUnit);
	nTextColor = 0;
	iVar5 = (int)(iVar5 + (iVar5 >> 0x1f & 0xffU)) >> 8;
	if (iVar3 <= iVar5)
	{
		iVar6 = STATES_CheckState(pUnit, 0x88);
		if (iVar6 == 0)
			goto LAB_6fb00108;
	}
	nTextColor = 3;
	iVar3 = iVar5;
LAB_6fb00108:
	if ((gnScreenWidth / 2 + -0x7f <= iVar2) && (iVar2 <= gnScreenWidth / 2 + -0x19))
	{
		if ((gnScreenHeight + -0x1b <= iVar4) && (iVar4 <= gnScreenHeight + -9))
		{
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1044));
			Unicode::sprintf(100, aUStack_c8, pUVar7, iVar3, iVar5);
			D2Win_10129_DrawFramedText(aUStack_c8, gnScreenWidth / 2 + -0x4c, gnScreenHeight + -0x34, nTextColor, 1);
		}
	}
}

//D2Client.0x6FB001B0
void __cdecl sub_6FB001B0()
{
	int iVar1;
	int iVar2;
	D2GfxDataStrc* pDVar3;
	D2GfxDataStrc local_48;

	pDVar3 = &local_48;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar3->pCurrentCell = nullptr;
		pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
	}
	local_48.pCellFile = gpCellFile_6FBB5E18;
	local_48.nDirection = 0;
	iVar2 = sub_6FB23230(0x15);
	if (iVar2 == 0)
	{
		if (dword_6FBB5EDC != 0)
		{
			iVar2 = sub_6FB57BD0();
			iVar1 = sub_6FB57BC0();
			if ((((gnScreenWidth / 2 + -8 <= iVar1) && (iVar1 <= gnScreenWidth / 2 + 5)) &&
			        (gnScreenHeight + -0x27 <= iVar2)) &&
			    (iVar2 <= gnScreenHeight + -0xd))
			{
				local_48.nFrame = 1;
				goto LAB_6fb00285;
			}
		}
		local_48.nFrame = 0;
	}
	else
	{
		if (dword_6FBB5EDC != 0)
		{
			iVar2 = sub_6FB57BD0();
			iVar1 = sub_6FB57BC0();
			if (((gnScreenWidth / 2 + -8 <= iVar1) && (iVar1 <= gnScreenWidth / 2 + 5)) &&
			    ((gnScreenHeight + -0x27 <= iVar2 && (iVar2 <= gnScreenHeight + -0xd))))
			{
				local_48.nFrame = 3;
				goto LAB_6fb00285;
			}
		}
		local_48.nFrame = 2;
	}
LAB_6fb00285:
	TEXTURE_CelDraw(&local_48, gnScreenWidth / 2 + -8, gnScreenHeight + -0x10, 0xffffffff, DRAWMODE_NORMAL,
	    nullptr);
}

//D2Client.0x6FB002B0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB002B0()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	int iVar4;
	uint32_t extraout_EAX;
	uint32_t uVar5;
	Unicode* a2;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar6;
	uint32_t extraout_EAX_00;
	uint32_t extraout_EAX_01;
	uint32_t extraout_ECX;
	uint32_t extraout_EDX;
	int iVar7;
	int iVar8;
	D2BeltsTxt* pThis;
	uint8_t* pbVar9;
	D2GfxDataStrc* pDVar10;
	char* pcVar11;
	char acStack_290[4];
	D2UnitStrc* pDStack_28c;
	D2InvRectStrc DStack_288;
	D2InvRectStrc DStack_278;
	D2InvRectStrc DStack_268;
	D2GfxDataStrc DStack_258;
	D2BeltsTxt DStack_210;
	D2BeltsTxt DStack_108;

	D2Win_10127_SetFont(D2FONT_FONT16);
	pDVar2 = CUNIT_GetPlayer();
	pDStack_28c = (D2UnitStrc*)pDVar2->pInventory;
	pDVar2 = INVENTORY_GetItemFromBodyLoc((D2InventoryStrc*)pDStack_28c, 8);
	if (pDVar2 == nullptr)
	{
		dword_6FB7CD70 = 2;
		iVar4 = dword_6FB7CD70;
	}
	else
	{
		uVar3 = ITEMS_GetItemType(pDVar2);
		iVar4 = dword_6FB7CD70;
		D2_ASSERT(!((uVar3 == 0x13) && (iVar4 = UNITS_GetBeltType(pDVar2), iVar4 < 0)));
	}
	dword_6FB7CD70 = iVar4;
	iVar4 = sub_6FB23230(0x1f);
	if ((iVar4 == 0) && (dword_6FBB5EA8 == 0))
	{
		dword_6FBB5EA4 = 0;
	}
	iVar4 = sub_6FB23230(9);
	if (iVar4 != 0)
	{
		dword_6FBB5EA4 = 0;
	}
	dword_6FBB5EAC = 0;
	if (dword_6FBB5EA4 != 0)
	{
		acStack_290[0] = '\x01';
		acStack_290[1] = 1;
		acStack_290[2] = 1;
		switch (dword_6FB7CD70)
		{
		case 1:
		case 4:
			acStack_290[1] = 0;
		case 0:
		case 5:
			acStack_290[2] = 0;
		default:
			dword_6FBB5EAC = 1;
			break;
		case 2:
			acStack_290[0] = '\0';
			acStack_290[1] = 0;
			acStack_290[2] = 0;
			dword_6FBB5EAC = 0;
		}
		pDVar10 = &DStack_258;
		for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			pDVar10->pCurrentCell = nullptr;
			pDVar10 = (D2GfxDataStrc*)&pDVar10->pCellFile;
		}
		DStack_258.nDirection = 0;
		DStack_258.pCellFile = gpCellFile_6FBB5E1C;
		DStack_258.nFrame = 0;
		iVar8 = 0;
		pcVar11 = acStack_290;
		iVar4 = 3;
		do
		{
			if (*pcVar11 != '\0')
			{
				TEXTURE_CelDraw(&DStack_258, gnScreenWidth / 2 + 0x15, (gnScreenHeight - iVar8) + -0x29,
				    0xffffffff, DRAWMODE_NORMAL, nullptr);
			}
			pcVar11 = pcVar11 + 1;
			iVar8 = iVar8 + 0x20;
			iVar4 = iVar4 + -1;
		} while (iVar4 != 0);
	}
	DATATBLS_GetBeltsTxtRecord(dword_6FB7CD70, gbIsHighResolution, &DStack_108);
	uVar3 = 0;
	if ((char)DStack_108.nBoxes != '\0')
	{
		do
		{
			if ((3 < (int)uVar3) && (dword_6FBB5EAC == 0))
				break;
			pDVar2 = INVENTORY_GetItemFromBeltSlot((D2InventoryStrc*)pDStack_28c, uVar3);
			if (pDVar2 != nullptr)
			{
				uVar1 = pDVar2->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar4 = pDVar2->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar2->pDynamicPath == nullptr)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = PATH_GetXPosition(pDVar2->pDynamicPath);
				}
				iVar8 = ITEMS_CheckItemFlag(pDVar2, 4, __LINE__, __FILE__);
				if (((iVar8 == 0) && (iVar8 = ITEMS_CheckIfUseable(pDVar2), iVar8 != 0)) &&
				    (iVar8 = sub_6FB2FB90(pDVar2), iVar8 == 0))
				{
					if ((pDVar2 == gpUnit_6FBB5EB4) && (dword_6FBB5EA0 != 0))
					{
						byte_6FBB5E38 = D2Win_10034_MixRGB(0x80, 0, 0);
						byte_6FBB5E39 = D2Win_10034_MixRGB(0, 0x80, 0);
						byte_6FBB5E3A = D2Win_10034_MixRGB(0, 0, 0x80);
						byte_6FBB5E3B = D2Win_10034_MixRGB(0x80, 0x80, 0);
						DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_268, iVar4);
						uVar5 = CONCAT31((int32_t)((uint32_t)extraout_EDX >> 8), byte_6FBB5E39);
						iVar8 = DStack_268.nLeft;
						iVar7 = DStack_268.nTop;
						goto LAB_6fb00621;
					}
					byte_6FBB5E38 = D2Win_10034_MixRGB(0x80, 0, 0);
					byte_6FBB5E39 = D2Win_10034_MixRGB(0, 0x80, 0);
					byte_6FBB5E3A = D2Win_10034_MixRGB(0, 0, 0x80);
					byte_6FBB5E3B = D2Win_10034_MixRGB(0x80, 0x80, 0);
				}
				else
				{
					byte_6FBB5E38 = D2Win_10034_MixRGB(0x80, 0, 0);
					byte_6FBB5E39 = D2Win_10034_MixRGB(0, 0x80, 0);
					byte_6FBB5E3A = D2Win_10034_MixRGB(0, 0, 0x80);
					byte_6FBB5E3B = D2Win_10034_MixRGB(0x80, 0x80, 0);
					DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_288, iVar4);
					uVar5 = CONCAT31((int32_t)((uint32_t)extraout_EAX >> 8), byte_6FBB5E38);
					iVar8 = DStack_288.nLeft;
					iVar7 = DStack_288.nTop;
				LAB_6fb00621:
					sub_6FB5B0F0(iVar8, iVar7, 0x1d, 0x1d, uVar5, (DrawMode)(0));
				}
				DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_278, iVar4);
				sub_6FB5A320(pDVar2, (D2CellFileStrc*)DStack_278.nLeft, DStack_278.nTop);
				if ((uVar3 < 4) && (iVar4 = ITEMS_CheckIfUseable(pDVar2), iVar4 != 0))
				{
					pThis = &DStack_210;
					iVar4 = 100;
					do
					{
						memset((Unicode*)pThis, 0, sizeof(Unicode));
						pThis = (D2BeltsTxt*)(pThis->pad0x01 + 1);
						iVar4 = iVar4 + -1;
					} while (iVar4 != 0);
					uVar5 = sub_6FAD4B60(dword_6FB7CD90[uVar3], 1);
					if (((short)uVar5 != -1) ||
					    (uVar5 = sub_6FAD4B60(dword_6FB7CD90[uVar3], 0), (short)uVar5 != -1))
					{
						a2 = sub_6FAD56B0(dword_6FB7CD90[uVar3], 1);
						Unicode::strcpy((Unicode*)&DStack_210, a2);
						iVar4 = Unicode::strlen((Unicode*)&DStack_210);
						iVar8 = D2Win_10121_GetTextWidth((Unicode*)&DStack_210);
						if (0x1c < iVar8)
						{
							pbVar9 = DStack_210.pad0x01 + iVar4 * 2 + -1;
							do
							{
								pbVar9[0] = 0;
								pbVar9[1] = 0;
								pbVar9 = pbVar9 + -2;
								iVar4 = D2Win_10121_GetTextWidth((Unicode*)&DStack_210);
							} while (0x1c < iVar4);
						}
						D2Win_10117_DrawText((Unicode*)&DStack_210, (int)((int)(uint32_t*)DStack_278.nLeft + 2),
						    DStack_278.nBottom + -2, 4, 0);
					}
				}
			}
			uVar3 = uVar3 + 1;
		} while ((int)uVar3 < (int)(DStack_108.nBoxes & 0xffU));
	}
	if (((((dword_6FB7CD70 == 2) || (iVar4 = sub_6FB23230(0x1f), iVar4 != 0)) || (dword_6FBB5EA4 != 0)) &&
	        ((pDVar2 = pDStack_28c, pItem = INVENTORY_GetCursorItem((D2InventoryStrc*)pDStack_28c),
	            pItem != nullptr && (dword_6FBB5EA0 != 0)))) &&
	    ((DATATBLS_GetBeltsTxtRecord(dword_6FB7CD70, gbIsHighResolution, &DStack_210), -1 < dword_6FB7CD78 &&
	                                                                                       (dword_6FB7CD78 < (int)(DStack_210.nBoxes & 0xffU)))))
	{
		pDVar6 = INVENTORY_GetItemFromBeltSlot((D2InventoryStrc*)pDVar2, dword_6FB7CD78);
		if ((pDVar6 == nullptr) &&
		    (uVar3 = ITEMS_CheckIfBeltable(pItem), iVar4 = dword_6FB7CD78, uVar3 != 0))
		{
			byte_6FBB5E38 = D2Win_10034_MixRGB(0x80, 0, 0);
			byte_6FBB5E39 = D2Win_10034_MixRGB(0, 0x80, 0);
			byte_6FBB5E3A = D2Win_10034_MixRGB(0, 0, 0x80);
			byte_6FBB5E3B = D2Win_10034_MixRGB(0x80, 0x80, 0);
			DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_288, iVar4);
			uVar5 = CONCAT31((int32_t)((uint32_t)extraout_EAX_00 >> 8), byte_6FBB5E39);
		}
		else
		{
			iVar8 = INVENTORY_GetUseableItemFromBeltSlot((D2InventoryStrc*)pDVar2, pItem, dword_6FB7CD78, &pDStack_28c);
			iVar4 = dword_6FB7CD78;
			if (iVar8 == 0)
			{
				byte_6FBB5E38 = D2Win_10034_MixRGB(0x80, 0, 0);
				byte_6FBB5E39 = D2Win_10034_MixRGB(0, 0x80, 0);
				byte_6FBB5E3A = D2Win_10034_MixRGB(0, 0, 0x80);
				byte_6FBB5E3B = D2Win_10034_MixRGB(0x80, 0x80, 0);
				DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_288, iVar4);
				uVar5 = CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), byte_6FBB5E38);
			}
			else
			{
				byte_6FBB5E38 = D2Win_10034_MixRGB(0x80, 0, 0);
				byte_6FBB5E39 = D2Win_10034_MixRGB(0, 0x80, 0);
				byte_6FBB5E3A = D2Win_10034_MixRGB(0, 0, 0x80);
				byte_6FBB5E3B = D2Win_10034_MixRGB(0x80, 0x80, 0);
				DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_288, iVar4);
				uVar5 = CONCAT31((int32_t)((uint32_t)extraout_EAX_01 >> 8), byte_6FBB5E3B);
			}
		}
		sub_6FB5B0F0(DStack_288.nLeft, DStack_288.nTop, 0x1d, 0x1d, uVar5, (DrawMode)(0));
	}
}

//D2Client.0x6FB00990
void __cdecl sub_6FB00990()
{
	D2UnitStrc* pDVar1;
	D2ItemsTxt* pDVar2;
	Unicode* pUVar3;
	int iVar4;
	Unicode* pUVar5;
	int iStack_684;
	Unicode UStack_680;
	Unicode aUStack_67e[63];
	short sStack_600;
	Unicode aUStack_5fe[127];
	Unicode UStack_500;
	Unicode aUStack_4fe[383];
	short local_200;
	Unicode local_1fe[255];

	local_200 = 0;
	pUVar3 = local_1fe;
	pUVar5 = local_1fe;
	for (iVar4 = 0x7f; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*(uint32_t*)pUVar5 = 0;
		pUVar5 = pUVar5 + 2;
	}
	pUVar5->ch = 0;
	iVar4 = 0xff;
	do
	{
		pUVar3 = pUVar3 + 1;
		iVar4 = iVar4 + -1;
	} while (iVar4 != 0);
	sStack_600 = 0;
	pUVar3 = aUStack_5fe;
	for (iVar4 = 0x3f; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*(uint32_t*)pUVar3 = 0;
		pUVar3 = pUVar3 + 2;
	}
	pUVar3->ch = 0;
	UStack_500.ch = 0;
	pUVar3 = aUStack_4fe;
	for (iVar4 = 0xbf; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*(uint32_t*)pUVar3 = 0;
		pUVar3 = pUVar3 + 2;
	}
	pUVar3->ch = 0;
	pDVar1 = CUNIT_GetPlayer();
	if ((dword_6FBB5EA0 != 0) && (gpUnit_6FBB5EB4 != nullptr))
	{
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		if ((pDVar1 == nullptr) &&
		    (((dword_6FB7CD78 < 4 || (dword_6FBB5EA4 != 0)) || (dword_6FBB5EA8 != 0))))
		{
			if (gpUnit_6FBB5EB4 == nullptr)
			{
				iVar4 = -1;
			}
			else
			{
				iVar4 = gpUnit_6FBB5EB4->dwClassId;
			}
			pDVar2 = DATATBLS_GetItemsTxtRecord(iVar4);
			D2_ASSERT(pDVar2 != nullptr);
			sub_6FADD360(0x80);
			iVar4 = ITEMS_GetItemQuality(gpUnit_6FBB5EB4);
			if (iVar4 != 3)
			{
				sub_6FAF3160(gpUnit_6FBB5EB4, (Unicode*)(&local_200), 0x100, 1, 0);
			}
			pUVar3 = (Unicode*)sub_6FB20430(&local_200, '\x03');
			Unicode::strcpy(&UStack_500, pUVar3);
			pUVar3 = (Unicode*)sub_6FB20430(&sStack_600, '\0');
			Unicode::strcat(&UStack_500, pUVar3);
			if ((-1 < dword_6FB7CD7C) && (-1 < dword_6FB7CD80))
			{
				sub_6FB5EF30(&UStack_500);
				iVar4 = sub_6FAEB910();
				if (iVar4 != 0)
				{
					UStack_680.ch = 0;
					pUVar3 = aUStack_67e;
					for (iVar4 = 0x1f; iVar4 != 0; iVar4 = iVar4 + -1)
					{
						*(uint32_t*)pUVar3 = 0;
						pUVar3 = pUVar3 + 2;
					}
					pUVar3->ch = 0;
					iVar4 = sub_6FAFB200(gpUnit_6FBB5EB4, 1, &iStack_684, &UStack_680, 0x40);
					if ((iVar4 != 0) && (UStack_680.ch != 0))
					{
						pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
						Unicode::strcat(&UStack_500, pUVar3);
						Unicode::strcat(&UStack_500, &UStack_680);
					}
				}
				D2Win_10129_DrawFramedText(&UStack_500, dword_6FB7CD7C, dword_6FB7CD80, 0, 1);
			}
		}
	}
}

//D2Client.0x6FB00C10
void __cdecl sub_6FB00C10()
{
	D2ActiveRoomStrc* pRoom;
	int iVar1;

	pRoom = CUNIT_GetPlayerRoom();
	if (pRoom != nullptr)
	{
		iVar1 = DUNGEON_GetLevelIdFromRoom(pRoom);
		if (dword_6FBB5EF0 != iVar1)
		{
			byte_6FBB5EF4 = 0x3c;
			dword_6FBB5EF0 = iVar1;
		}
	}
}

//D2Client.0x6FB00C40
void __cdecl sub_6FB00C40()
{
	int iVar1;
	int iVar2;
	Unicode* wszText;
	short index;
	int nY;
	int nAlign;

	iVar1 = sub_6FB57BC0();
	iVar2 = sub_6FB57BD0();
	if ((((gnScreenWidth / 2 + -8 <= iVar1) && (iVar1 <= gnScreenWidth / 2 + 5)) &&
	        (gnScreenHeight + -0x27 <= iVar2)) &&
	    (iVar2 <= gnScreenHeight + -0xd))
	{
		iVar1 = sub_6FB23230(0x15);
		nAlign = 1;
		iVar2 = 0;
		if (iVar1 == 0)
		{
			index = 0x1047;
		}
		else
		{
			index = 0x1048;
		}
		nY = gnScreenHeight + -0x27;
		iVar1 = gnScreenWidth / 2;
		wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		D2Win_10129_DrawFramedText(wszText, iVar1 + -1, nY, iVar2, nAlign);
	}
}

//D2Client.0x6FB00CD0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB00CD0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	bool bVar2;
	int iVar3;
	uint32_t extraout_var;
	uint32_t uVar4;
	uint32_t uVar5;

	iVar3 = sub_6FAABF20();
	if (iVar3 != 0)
	{
	LAB_6fb00e09:
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	bVar2 = sub_6FB283E0();
	if (D2C_ZEXT(bVar2) != 0)
		goto LAB_6fb00e09;
	uVar1 = (uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar4 = (uint32_t)uVar1;
	uVar5 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	iVar3 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar3 != 0)
	{
		dword_6FBB5EB0 = 1;
		goto LAB_6fb00de4;
	}
	if ((int)uVar5 <= gnScreenHeight + -0x30)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	if (((uVar1 < 0x75) || (uVar4 != 0xa5 && 0xa4 < uVar1)) || (gnScreenHeight < (int)uVar5))
	{
		if ((((int)uVar4 < gnScreenWidth + -0xa5) || (gnScreenWidth + -0x75 < (int)uVar4)) ||
		    (gnScreenHeight < (int)uVar5))
		{
			iVar3 = gnScreenWidth / 2;
			if ((((int)uVar4 < iVar3 + -8) || (iVar3 + 5 < (int)uVar4)) ||
			    (((int)uVar5 < gnScreenHeight + -0x27 || (gnScreenHeight + -0xd < (int)uVar5))))
			{
				if (((((int)uVar4 < iVar3 + -0x91) || (iVar3 + -0x80 < (int)uVar4)) ||
				        ((int)uVar5 < gnScreenHeight + -0x1c)) ||
				    (gnScreenHeight + -8 < (int)uVar5))
					goto LAB_6fb00dde;
				dword_6FBB5EE4 = 1;
			}
			else
			{
				dword_6FBB5EDC = 1;
			}
			dword_6FBB5EB0 = 1;
			sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		}
		else
		{
			dword_6FBB5EB0 = 1;
			byte_6FBB5E94 = 1;
		}
	}
	else
	{
		dword_6FBB5EB0 = 1;
		byte_6FBB5E90 = 1;
	}
LAB_6fb00dde:
	byte_6FB7CD74 = 1;
LAB_6fb00de4:
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB00E20
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB00E20(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	bool bVar2;
	int iVar3;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t uVar5;
	uint32_t uVar6;

	iVar3 = sub_6FAABF20();
	if ((iVar3 != 0) || (bVar2 = sub_6FB283E0(), D2C_ZEXT(bVar2) != 0))
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	pDVar4 = CUNIT_GetPlayer();
	uVar1 = (uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar5 = (uint32_t)uVar1;
	uVar6 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	byte_6FBB5E94 = 0;
	byte_6FBB5E90 = 0;
	if (dword_6FBB5EB0 == 0)
	{
		if ((((((0x74 < uVar1) && (uVar1 < 0xa6)) && (gnScreenHeight + -0x30 <= (int)uVar6)) &&
		         ((int)uVar6 <= gnScreenHeight)) ||
		        (((gnScreenWidth + -0xa5 <= (int)uVar5 && ((int)uVar5 <= gnScreenWidth + -0x75)) &&
		            ((gnScreenHeight + -0x30 <= (int)uVar6 && ((int)uVar6 <= gnScreenHeight)))))) &&
		    (iVar3 = sub_6FB23230(3), iVar3 != 0))
		{
			sub_6FB23260(3, 1, 0);
		}
		dword_6FBB5EB0 = 0;
	}
	else
	{
		if (dword_6FBB5EA4 != 0)
		{
			iVar3 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
			if (iVar3 != 0)
			{
				iVar3 = sub_6FB57CC0();
				if (iVar3 == 6)
				{
					sub_6FB23A40();
				}
				else
				{
					iVar3 = sub_6FB57CC0();
					if (iVar3 == 8)
					{
						sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4c), 0xffffffff);
					}
				}
				sub_6FB012E0(pDVar4, pDVar4->pInventory, uVar5, uVar6);
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				dword_6FBB5EB0 = 0;
				dword_6FBB5EDC = 0;
				dword_6FBB5EE4 = 0;
				return;
			}
			iVar3 = gnScreenWidth / 2;
			if (((iVar3 + -8 <= (int)uVar5) && ((int)uVar5 <= iVar3 + 5)) &&
			    ((gnScreenHeight + -0x27 <= (int)uVar6 && ((int)uVar6 <= gnScreenHeight + -0xd))))
			{
				iVar3 = sub_6FB23230(0x15);
				if (iVar3 != 0)
				{
					sub_6FB23260(0x15, 1, 0);
					dword_6FBB5EB0 = 0;
					dword_6FBB5EDC = 0;
					dword_6FBB5EE4 = 0;
					return;
				}
				sub_6FB23260(0x15, 2, 0);
				dword_6FBB5EB0 = 0;
				dword_6FBB5EDC = 0;
				dword_6FBB5EE4 = 0;
				return;
			}
			if ((((0x74 < uVar1) && (uVar1 < 0xa6)) && (gnScreenHeight + -0x30 <= (int)uVar6)) &&
			    ((int)uVar6 <= gnScreenHeight))
			{
				sub_6FB23260(3, 2, 0);
				sub_6FB18760(1);
				dword_6FBB5EB0 = 0;
				dword_6FBB5EDC = 0;
				dword_6FBB5EE4 = 0;
				return;
			}
			if ((((gnScreenWidth + -0xa5 <= (int)uVar5) && ((int)uVar5 <= gnScreenWidth + -0x75)) &&
			        (gnScreenHeight + -0x30 <= (int)uVar6)) &&
			    ((int)uVar6 <= gnScreenHeight))
			{
				sub_6FB23260(3, 2, 0);
				sub_6FB18760(0);
				dword_6FBB5EB0 = 0;
				dword_6FBB5EDC = 0;
				dword_6FBB5EE4 = 0;
				return;
			}
			if (((iVar3 + -0x91 <= (int)uVar5) && ((int)uVar5 <= iVar3 + -0x80)) &&
			    ((gnScreenHeight + -0x1c <= (int)uVar6 && ((int)uVar6 <= gnScreenHeight + -8))))
			{
				iVar3 = sub_6FAA8B30();
				sub_6FAA8B20((uint32_t)(iVar3 == 0));
			}
			dword_6FBB5EB0 = 0;
			dword_6FBB5EDC = 0;
			dword_6FBB5EE4 = 0;
			return;
		}
		if (gnScreenHeight + -0x30 < (int)uVar6)
		{
			iVar3 = gnScreenWidth / 2;
			if (((((int)uVar5 < iVar3 + 0x17) || (iVar3 + 0x91 < (int)uVar5)) ||
			        ((int)uVar6 < gnScreenHeight + -0x27)) ||
			    (gnScreenHeight + -10 < (int)uVar6))
			{
				if (((uVar1 < 0x75) || (uVar5 != 0xa5 && 0xa4 < uVar1)) || (gnScreenHeight < (int)uVar6))
				{
					if ((((int)uVar5 < gnScreenWidth + -0xa5) || (gnScreenWidth + -0x75 < (int)uVar5)) ||
					    (gnScreenHeight < (int)uVar6))
					{
						if (((((int)uVar5 < iVar3 + -0x91) || (iVar3 + -0x80 < (int)uVar5)) ||
						        ((int)uVar6 < gnScreenHeight + -0x1c)) ||
						    (gnScreenHeight + -8 < (int)uVar6))
						{
							if (((iVar3 + -8 <= (int)uVar5) && ((int)uVar5 <= iVar3 + 5)) &&
							    ((gnScreenHeight + -0x27 <= (int)uVar6 && ((int)uVar6 <= gnScreenHeight + -0xd))))
							{
								iVar3 = sub_6FB23230(0x15);
								uVar5 = 1;
								if (iVar3 == 0)
								{
									uVar5 = 2;
								}
								sub_6FB23260(0x15, uVar5, 0);
								if (dword_6FBB5EDC != 0)
								{
									dword_6FBB5EE0 = (uint32_t)(dword_6FBB5EE0 == 0);
								}
							}
						}
						else
						{
							iVar3 = sub_6FAA8B30();
							sub_6FAA8B20((uint32_t)(iVar3 == 0));
						}
					}
					else
					{
						iVar3 = sub_6FB57CC0();
						if (iVar3 == 6)
						{
							sub_6FB23A40();
						}
						else
						{
							iVar3 = sub_6FB57CC0();
							if (iVar3 == 8)
							{
								sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX_02 >> 8), 0x4c), 0xffffffff);
							}
						}
						iVar3 = sub_6FB23230(3);
						if (iVar3 == 0)
						{
							sub_6FB23260(3, 0, 0);
							sub_6FB18760(0);
						}
						else
						{
							sub_6FB23260(3, 1, 0);
							sub_6FB18760(0);
						}
					}
				}
				else
				{
					iVar3 = sub_6FB57CC0();
					if (iVar3 == 6)
					{
						sub_6FB23A40();
					}
					else
					{
						iVar3 = sub_6FB57CC0();
						if (iVar3 == 8)
						{
							sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX_01 >> 8), 0x4c), 0xffffffff);
						}
					}
					iVar3 = sub_6FB23230(3);
					if (iVar3 == 0)
					{
						sub_6FB23260(3, 0, 0);
						sub_6FB18760(1);
					}
					else
					{
						sub_6FB23260(3, 1, 0);
						sub_6FB18760(1);
					}
				}
			}
			else
			{
				iVar3 = sub_6FB57CC0();
				if (iVar3 == 6)
				{
					sub_6FB23A40();
					sub_6FB012E0(pDVar4, pDVar4->pInventory, uVar5, uVar6);
				}
				else
				{
					iVar3 = sub_6FB57CC0();
					if (iVar3 == 8)
					{
						sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x4c), 0xffffffff);
					}
					sub_6FB012E0(pDVar4, pDVar4->pInventory, uVar5, uVar6);
				}
			}
			dword_6FBB5EB0 = 0;
			byte_6FB7CD74 = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			dword_6FBB5EDC = 0;
			dword_6FBB5EE4 = 0;
			return;
		}
	}
	pSMSGHANDLER_PARAMS->bUseResult = 0;
	dword_6FBB5EDC = 0;
	dword_6FBB5EE4 = 0;
}

//D2Client.0x6FB012E0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB012E0(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, int a3, int a4)
{
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t extraout_ECX;
	uint32_t uVar5;
	uint32_t uVar4;
	uint32_t extraout_ECX_00;
	uint32_t uVar6;
	float fVar7;
	float fVar8;
	int iVar9;
	D2InvRectStrc DStack_118;
	D2BeltsTxt local_108;

	DATATBLS_GetBeltsTxtRecord(dword_6FB7CD70, gbIsHighResolution, &local_108);
	uVar6 = 0;
	if ((char)local_108.nBoxes == '\0')
	{
		return;
	}
	while ((((DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_118, uVar6),
	             a3 < DStack_118.nLeft || (DStack_118.nRight < a3)) ||
	            (a4 < DStack_118.nTop)) ||
	        (DStack_118.nBottom < a4)))
	{
		uVar6 = uVar6 + 1;
		if ((int)(local_108.nBoxes & 0xffU) <= (int)uVar6)
		{
			return;
		}
	}
	if (uVar6 == 0xffffffff)
	{
		return;
	}
	pItem = INVENTORY_GetCursorItem(pInventory);
	pDVar1 = INVENTORY_GetItemFromBeltSlot(pInventory, uVar6);
	iVar2 = sub_6FB57CC0();
	if (iVar2 == 6)
	{
		return;
	}
	if ((pItem == nullptr) || (uVar3 = ITEMS_CheckIfBeltable(pItem), uVar3 == 0))
	{
		if (pDVar1 == nullptr)
		{
			return;
		}
		if (pItem != nullptr)
		{
			return;
		}
		iVar2 = sub_6FB2FB90(pDVar1);
		if (iVar2 != 0)
		{
			return;
		}
		sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x24), pDVar1->dwUnitId);
		sub_6FB2FB30(pDVar1);
		return;
	}
	iVar2 = sub_6FB2FB90(pItem);
	uVar5 = (uint32_t)((uint32_t)extraout_ECX >> 8);
	if (pDVar1 == nullptr)
	{
		if (iVar2 != 0)
			goto LAB_6fb013d5;
		uVar6 = uVar6 & 0xffff;
		uVar4 = CONCAT31(uVar5, 0x23);
	}
	else
	{
		if (iVar2 != 0)
			goto LAB_6fb013d5;
		uVar6 = pDVar1->dwUnitId;
		uVar4 = CONCAT31(uVar5, 0x25);
	}
	sub_6FAADA40(uVar4, pItem->dwUnitId, uVar6);
	sub_6FB2FB30(pItem);
LAB_6fb013d5:
	iVar9 = 0;
	fVar8 = 0.0;
	fVar7 = 0.0;
	iVar2 = sub_6FB2E590(pItem);
	sub_6FB55820(iVar2, nullptr, fVar7, fVar8, iVar9);
}

//D2Client.0x6FB01430
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB01430(int a1)
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	D2UnitStrc* pDVar3;
	uint32_t extraout_var_00;
	uint32_t uVar4;
	uint32_t uVar5;

	if (((dword_6FBA796C == 0) || (iVar2 = sub_6FAABF20(), iVar2 != 0)) ||
	    (bVar1 = sub_6FB283E0(), D2C_ZEXT(bVar1) != 0))
	{
		*(uint32_t*)(a1 + 0x18) = 0;
		return;
	}
	uVar4 = (uint32_t) * (uint16_t*)(a1 + 0xc);
	uVar5 = (uint32_t) * (uint16_t*)(a1 + 0xe);
	pDVar3 = CUNIT_GetPlayer();
	bVar1 = sub_6FAA8CB0();
	if (D2C_ZEXT(bVar1) != 0)
	{
		return;
	}
	if (dword_6FBB5EA4 != 0)
	{
		iVar2 = sub_6FB01B50(a1);
		if (iVar2 != 0)
		{
			iVar2 = sub_6FB23230(0x1f);
			if (iVar2 != 0)
			{
				*(uint32_t*)(a1 + 0x18) = 1;
				*(uint32_t*)(a1 + 0x1c) = 0;
			}
			sub_6FB01590(pDVar3, pDVar3->pInventory, uVar4, uVar5);
			return;
		}
		dword_6FBB5EA0 = sub_6FB23230(0x1f);
		if (dword_6FBB5EA0 != 0)
		{
			dword_6FBB5EA8 = 0;
			*(uint32_t*)(a1 + 0x18) = 0;
			dword_6FBB5EA0 = 0;
			return;
		}
		dword_6FBB5EA4 = dword_6FBB5EA0;
		dword_6FBB5EA8 = dword_6FBB5EA0;
		*(uint32_t*)(a1 + 0x18) = 0;
		return;
	}
	if (((gnScreenWidth / 2 + 0x17 <= (int)uVar4) && ((int)uVar4 <= gnScreenWidth / 2 + 0x91)) &&
	    ((gnScreenHeight + -0x27 <= (int)uVar5 && ((int)uVar5 <= gnScreenHeight + -10))))
	{
		iVar2 = sub_6FB23860(9);
		if (iVar2 == 0)
		{
			dword_6FBB5EA4 = 1;
			dword_6FBB5EA8 = 1;
			sub_6FB01590(pDVar3, pDVar3->pInventory, uVar4, uVar5);
		}
		*(uint32_t*)(a1 + 0x18) = 1;
		*(uint32_t*)(a1 + 0x1c) = 0;
		return;
	}
	*(uint32_t*)(a1 + 0x18) = 0;
	dword_6FBB5EA0 = 0;
}

//D2Client.0x6FB01590
void __fastcall sub_6FB01590(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, int a3, int a4)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int nBoxId;
	D2InvRectStrc DStack_118;
	D2BeltsTxt local_108;

	DATATBLS_GetBeltsTxtRecord(dword_6FB7CD70, gbIsHighResolution, &local_108);
	nBoxId = 0;
	if ((char)local_108.nBoxes != '\0')
	{
		while ((((DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_118, nBoxId),
		             a3 < DStack_118.nLeft || (DStack_118.nRight < a3)) ||
		            (a4 < DStack_118.nTop)) ||
		        (DStack_118.nBottom < a4)))
		{
			nBoxId = nBoxId + 1;
			if ((int)(local_108.nBoxes & 0xffU) <= nBoxId)
			{
				return;
			}
		}
		if (-1 < nBoxId)
		{
			pDVar2 = INVENTORY_GetCursorItem(pInventory);
			iVar3 = sub_6FB57CC0();
			if ((iVar3 != 6) && (iVar3 = sub_6FB57CC0(), iVar3 != 8))
			{
				if (pDVar2 == nullptr)
				{
					pDVar2 = INVENTORY_GetItemFromBeltSlot(pInventory, nBoxId);
					if (pDVar2 != nullptr)
					{
						dword_6FBB5EA0 = 1;
						if (pDVar2 == (D2UnitStrc*)(dword_6FBB5EB8))
						{
							dword_6FB7CD78 = nBoxId;
							dword_6FBB5EA0 = 1;
							return;
						}
						uVar1 = pDVar2->dwUnitType;
						if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
						{
							iVar3 = pDVar2->pDynamicPath->dwClientCoordY;
							dword_6FB7CD78 = nBoxId;
						}
						else if (pDVar2->pDynamicPath == nullptr)
						{
							iVar3 = 0;
							dword_6FB7CD78 = nBoxId;
						}
						else
						{
							dword_6FB7CD78 = nBoxId;
							iVar3 = PATH_GetXPosition(pDVar2->pDynamicPath);
						}
						DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_118, iVar3);
						gpUnit_6FBB5EB4 = pDVar2;
						dword_6FBB5EB8 = (uint32_t)(pDVar2);
						dword_6FB7CD7C = DStack_118.nLeft + 0xe;
						dword_6FB7CD80 = DStack_118.nTop;
						return;
					}
					dword_6FBB5EA0 = 0;
				}
				else
				{
					dword_6FBB5EA0 = 1;
				}
				gpUnit_6FBB5EB4 = nullptr;
				dword_6FBB5EB8 = (uint32_t)(nullptr);
				dword_6FB7CD78 = nBoxId;
			}
		}
	}
}

//D2Client.0x6FB01730
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB01730(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	D2UnitStrc* pDVar3;
	uint32_t extraout_ECX;
	uint32_t uVar4;
	uint32_t uVar5;
	int nBoxId;
	D2InvRectStrc DStack_118;
	D2BeltsTxt local_108;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			uVar5 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
			uVar4 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
			pDVar3 = CUNIT_GetPlayer();
			iVar2 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
			if (iVar2 == 0)
			{
				pSMSGHANDLER_PARAMS->bUseResult = 0;
				dword_6FBB5EA0 = 0;
				return;
			}
			nBoxId = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			iVar2 = sub_6FB57CC0();
			if (iVar2 == 6)
			{
				sub_6FB23A40();
			}
			else
			{
				iVar2 = sub_6FB57CC0();
				if (iVar2 == 8)
				{
					sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4c), 0xffffffff);
				}
			}
			DATATBLS_GetBeltsTxtRecord(dword_6FB7CD70, gbIsHighResolution, &local_108);
			if ((char)local_108.nBoxes != '\0')
			{
				while (true)
				{
					DATATBLS_GetInvRectFromBeltsTxt(dword_6FB7CD70, gbIsHighResolution, &DStack_118, nBoxId);
					if ((((DStack_118.nLeft <= (int)uVar5) && ((int)uVar5 <= DStack_118.nRight)) &&
					        (DStack_118.nTop <= (int)uVar4)) &&
					    ((int)uVar4 <= DStack_118.nBottom))
						break;
					nBoxId = nBoxId + 1;
					if ((int)(local_108.nBoxes & 0xffU) <= nBoxId)
					{
						pSMSGHANDLER_PARAMS->bUseResult = 0;
						return;
					}
				}
				if (-1 < nBoxId)
				{
					sub_6FB018A0(pDVar3, pDVar3->pInventory, nBoxId, pSMSGHANDLER_PARAMS->wParam >> 2 & 1);
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					return;
				}
			}
			pSMSGHANDLER_PARAMS->bUseResult = 0;
			return;
		}
	}
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FB018A0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB018A0(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, int a3, int a4)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2ItemsTxt* pDVar3;
	uint32_t uVar4;
	uint32_t extraout_ECX;
	uint32_t extraout_EDX;
	float fVar5;
	float fVar6;
	int iVar7;
	D2InventoryGridInfoStrc DStack_18;

	iVar1 = sub_6FAAC080();
	if (iVar1 == 0)
	{
		a4 = 0;
	}
	pDVar2 = INVENTORY_GetCursorItem(pInventory);
	if ((pDVar2 == nullptr) && (iVar1 = sub_6FB23230(9), iVar1 == 0))
	{
		iVar1 = sub_6FAAC080();
		iVar1 = UNITS_GetInventoryRecordId(pUnit, 0, iVar1);
		DATATBLS_GetInventoryGridInfo(iVar1, gbIsHighResolution, &DStack_18);
		pDVar2 = INVENTORY_GetItemFromBeltSlot(pInventory, a3);
		if (pDVar2 != nullptr)
		{
			pDVar3 = DATATBLS_GetItemsTxtRecord(pDVar2->dwClassId);
			D2_ASSERT(pDVar3 != nullptr);
			if ((pDVar3->nUnique == 1) || (pDVar3->nQuest == 1))
			{
				sub_6FB1EE20((int)pDVar2, (int)pDVar3);
				return;
			}
			if (pDVar3->nUseable != 1)
			{
				sub_6FB514E0(pUnit, 0x14);
				return;
			}
			iVar1 = sub_6FB2FB90(pDVar2);
			if (iVar1 == 0)
			{
				sub_6FAADA70(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x26), pDVar2->dwUnitId, a4, 0);
				sub_6FB2FB30(pDVar2);
				if ((a4 != 0) && (uVar4 = sub_6FAB1920((int)pUnit, 7, 0), uVar4 != 0xffffffff))
				{
					sub_6FB51920(uVar4, CONCAT31((int32_t)((uint32_t)extraout_EDX >> 8), 1), 0x54);
					dword_6FBB5EA0 = 0;
					return;
				}
				iVar7 = 0;
				fVar6 = 0.0;
				fVar5 = 0.0;
				iVar1 = sub_6FB2E5A0(pDVar2);
				sub_6FB55820(iVar1, nullptr, fVar5, fVar6, iVar7);
				dword_6FBB5EA0 = 0;
			}
		}
	}
}

//D2Client.0x6FB01A00
void __cdecl sub_6FB01A00(uint32_t a1)
{
	sub_6FB23800(1, 0);
}

//D2Client.0x6FB01A10
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB01A10()
{
	bool bVar1;
	uint16_t uVar2;
	int iVar3;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;

	iVar3 = sub_6FAABF20();
	if (iVar3 == 0)
	{
		bVar1 = sub_6FB283E0();
		if ((D2C_ZEXT(bVar1) == 0) && (byte_6FBB5EBC == '\x01'))
		{
			pDVar4 = CUNIT_GetPlayer();
			uVar2 = GetKeyState(0x10);
			sub_6FB018A0(pDVar4, pDVar4->pInventory, 0, uVar2 & 0x8000);
		}
	}
}

//D2Client.0x6FB01A50
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB01A50()
{
	bool bVar1;
	uint16_t uVar2;
	int iVar3;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;

	iVar3 = sub_6FAABF20();
	if (iVar3 == 0)
	{
		bVar1 = sub_6FB283E0();
		if ((D2C_ZEXT(bVar1) == 0) && (byte_6FBB5EBD == '\x01'))
		{
			pDVar4 = CUNIT_GetPlayer();
			uVar2 = GetKeyState(0x10);
			sub_6FB018A0(pDVar4, pDVar4->pInventory, 1, uVar2 & 0x8000);
		}
	}
}

//D2Client.0x6FB01A90
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB01A90()
{
	bool bVar1;
	uint16_t uVar2;
	int iVar3;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;

	iVar3 = sub_6FAABF20();
	if (iVar3 == 0)
	{
		bVar1 = sub_6FB283E0();
		if ((D2C_ZEXT(bVar1) == 0) && (byte_6FBB5EBE == '\x01'))
		{
			pDVar4 = CUNIT_GetPlayer();
			uVar2 = GetKeyState(0x10);
			sub_6FB018A0(pDVar4, pDVar4->pInventory, 2, uVar2 & 0x8000);
		}
	}
}

//D2Client.0x6FB01AD0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB01AD0()
{
	bool bVar1;
	uint16_t uVar2;
	int iVar3;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;

	iVar3 = sub_6FAABF20();
	if (iVar3 == 0)
	{
		bVar1 = sub_6FB283E0();
		if ((D2C_ZEXT(bVar1) == 0) && (byte_6FBB5EBF == '\x01'))
		{
			pDVar4 = CUNIT_GetPlayer();
			uVar2 = GetKeyState(0x10);
			sub_6FB018A0(pDVar4, pDVar4->pInventory, 3, uVar2 & 0x8000);
		}
	}
}

//D2Client.0x6FB01B10
void __fastcall sub_6FB01B10(uint32_t a1, char a2)
{
	if (a1 < 4)
	{
		(&byte_6FBB5EBC)[a1] = a2;
	}
}

//D2Client.0x6FB01B20
void __cdecl sub_6FB01B20()
{
	dword_6FB7CD78 = -1;
	dword_6FB7CD7C = -1;
	dword_6FB7CD80 = -1;
	dword_6FBB5EA0 = 0;
	gpUnit_6FBB5EB4 = nullptr;
	dword_6FBB5EB8 = 0;
}

//D2Client.0x6FB01B50
uint32_t __fastcall sub_6FB01B50(int a1)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint8_t abStackY_140[8];
	uint8_t abStackY_138[28];
	D2BeltsTxt local_108;

	uVar2 = (uint32_t) * (uint16_t*)(a1 + 0xc);
	uVar3 = (uint32_t) * (uint16_t*)(a1 + 0xe);
	DATATBLS_GetBeltsTxtRecord(dword_6FB7CD70, gbIsHighResolution, &local_108);
	if (dword_6FBB5EA4 == 0)
	{
		if ((((gnScreenHeight + -0x30 < (int)uVar3) && (gnScreenWidth / 2 + 0x17 <= (int)uVar2)) &&
		        ((int)uVar2 <= gnScreenWidth / 2 + 0x91)) &&
		    ((gnScreenHeight + -0x27 <= (int)uVar3 && ((int)uVar3 <= gnScreenHeight + -10))))
		{
			return 1;
		}
	}
	else
	{
		iVar1 = (local_108.nBoxes & 0xffU) * 0x10;
		if (((*(int*)(local_108.pad0x01 + iVar1 + -0x39) <= (int)uVar2) &&
		        ((int)uVar2 <= local_108.beltBoxes[3].nRight)) &&
		    ((*(int*)(local_108.pad0x01 + iVar1 + -0x31) <= (int)uVar3 &&
		        ((int)uVar3 <= local_108.beltBoxes[3].nBottom))))
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FB01C10
void __cdecl sub_6FB01C10()
{
	gpUnit_6FBB5EB4 = nullptr;
	dword_6FBB5EB8 = 0;
}

//D2Client.0x6FB01C20
void __cdecl sub_6FB01C20()
{
	dword_6FBB5EA4 = 1;
}

//D2Client.0x6FB01C30
void __cdecl sub_6FB01C30()
{
	byte_6FBB5F38 = D2Win_10034_MixRGB(0xff, 0, 0);
}

//D2Client.0x6FB01C50
int32_t __cdecl sub_6FB01C50()
{
	byte_6FBB5F38 = D2Win_10034_MixRGB(0, 0, 0);
	return 0;
}
