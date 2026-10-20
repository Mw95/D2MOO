#include "Skills/Skills.h"

#include "Core/MemoryPartitions.h"
#include "Draw/DLightMap.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/Select.h"
#include "Quest/QuestsFX.h"
#include "Skills/SkillsAma.h"
#include "Skills/SkillsBar.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/CUnitEvent.h"
#include "Unit/Missile.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB6E2E0
uint32_t dword_6FB6E2E0 = 0x1E;
//D2Client.0x6FB6E3E0
uint32_t dword_6FB6E3E0;
//D2Client.0x6FB6E4E0
uint32_t dword_6FB6E4E0 = 0xFFFFFFFF;
//D2Client.0x6FB6E4F0
uint32_t dword_6FB6E4F0 = 0xFFFFFFFF;
//D2Client.0x6FB6E500
uint32_t dword_6FB6E500 = 0x12;
//D2Client.0x6FB6E51C
uint32_t dword_6FB6E51C = 8;
//D2Client.0x6FB6E538
uint32_t dword_6FB6E538[8] = {0x14, 0xFFFFFFEC, 0, 0, 0xE, 0xFFFFFFF2, 0xFFFFFFF2, 0xE};
//D2Client.0x6FB6E558
uint32_t dword_6FB6E558[8] = {0, 0, 0x14, 0xFFFFFFEC, 0xE, 0xE, 0xFFFFFFF2, 0xFFFFFFF2};
//D2Client.0x6FB77488
uint8_t byte_6FB77488[280] = {0, 0, 0, 0, 0x60, 0xB9, 0xAB, 0x6F, 0xB0, 0xB9, 0xAB, 0x6F, 0xE0, 0xB9, 0xAB, 0x6F, 0x80, 0xBA, 0xAB, 0x6F, 0xB0, 0xF4, 0xAB, 0x6F, 0x80, 0xF5, 0xAB, 0x6F, 0x10, 0xF9, 0xAB, 0x6F, 0xC0, 0xFA, 0xAB, 0x6F, 0x50, 0xFC, 0xAB, 0x6F, 0x60, 0xFE, 0xAB, 0x6F, 0xA0, 0xE2, 0xAB, 0x6F, 0xB0, 0xE2, 0xAB, 0x6F, 0xD0, 0xE2, 0xAB, 0x6F, 0x90, 0xE4, 0xAB, 0x6F, 0x50, 0xA0, 0xAC, 0x6F, 0xD0, 0xA3, 0xAC, 0x6F, 0xA0, 0xAC, 0xAC, 0x6F, 0x90, 0x7F, 0xAC, 0x6F, 0x50, 0x81, 0xAC, 0x6F, 0x70, 0x83, 0xAC, 0x6F, 0x30, 0x85, 0xAC, 0x6F, 0x30, 0x8B, 0xAC, 0x6F, 0x80, 0x8C, 0xAC, 0x6F, 0, 0x8D, 0xAC, 0x6F, 0x20, 0x98, 0xAC, 0x6F, 0x30, 0xD, 0xAC, 0x6F, 0x90, 0xD, 0xAC, 0x6F, 0, 0x10, 0xAC, 0x6F, 0x10, 0x13, 0xAC, 0x6F, 0x80, 0x21, 0xAC, 0x6F, 0xC0, 0x24, 0xAC, 0x6F, 0xF0, 0x51, 0xAC, 0x6F, 0x40, 0x54, 0xAC, 0x6F, 0x10, 0x55, 0xAC, 0x6F, 0xD0, 0x57, 0xAC, 0x6F, 0, 0x59, 0xAC, 0x6F, 0xC0, 0x5D, 0xAC, 0x6F, 0x40, 0x62, 0xAC, 0x6F, 0x60, 0x62, 0xAC, 0x6F, 0x60, 0x64, 0xAC, 0x6F, 0x50, 0x6B, 0xAC, 0x6F, 0xE0, 0x71, 0xAC, 0x6F, 0, 0x74, 0xAC, 0x6F, 0x70, 0x77, 0xAC, 0x6F, 0x40, 0x28, 0xAC, 0x6F, 0xE0, 0x38, 0xAC, 0x6F, 0x70, 0x39, 0xAC, 0x6F, 0, 0x3B, 0xAC, 0x6F, 0x50, 0x3D, 0xAC, 0x6F, 0x40, 0x45, 0xAC, 0x6F, 0x10, 0x47, 0xAC, 0x6F, 0xB0, 0x43, 0xAC, 0x6F, 0x10, 0xE6, 0xAB, 0x6F};
//D2Client.0x6FB775A0
int32_t dword_6FB775A0 = 70;
//D2Client.0x6FB775A8
uint8_t byte_6FB775A8[520] = {0, 0, 0, 0, 0x90, 0xBA, 0xAB, 0x6F, 0x70, 0xBC, 0xAB, 0x6F, 0x10, 0xF5, 0xAB, 0x6F, 0x20, 0xF6, 0xAB, 0x6F, 0x50, 0xF8, 0xAB, 0x6F, 0xD0, 0xFA, 0xAB, 0x6F, 0xB0, 0xFC, 0xAB, 0x6F, 0x40, 0xFD, 0xAB, 0x6F, 0xB0, 0, 0xAC, 0x6F, 0xF0, 1, 0xAC, 0x6F, 0x80, 2, 0xAC, 0x6F, 0xE0, 8, 0xAC, 0x6F, 0xF0, 9, 0xAC, 0x6F, 0xE0, 0xA, 0xAC, 0x6F, 0x80, 0xB, 0xAC, 0x6F, 0x60, 0xE7, 0xAB, 0x6F, 0xF0, 0xE7, 0xAB, 0x6F, 0x20, 0xEA, 0xAB, 0x6F, 0xC0, 0xEB, 0xAB, 0x6F, 0xC0, 0xED, 0xAB, 0x6F, 0xC0, 0xF0, 0xAB, 0x6F, 0xA0, 0xF2, 0xAB, 0x6F, 0xE0, 0x9E, 0xAC, 0x6F, 0xB0, 0xA3, 0xAC, 0x6F, 0x70, 0xA5, 0xAC, 0x6F, 0x30, 0xA6, 0xAC, 0x6F, 0, 0xA9, 0xAC, 0x6F, 0x10, 0xAC, 0xAC, 0x6F, 0xF0, 0xAD, 0xAC, 0x6F, 0xF0, 0x7F, 0xAC, 0x6F, 0x40, 0x84, 0xAC, 0x6F, 0xF0, 0x88, 0xAC, 0x6F, 0xE0, 0x8A, 0xAC, 0x6F, 0xE0, 0x8E, 0xAC, 0x6F, 0xE0, 0x90, 0xAC, 0x6F, 0xF0, 0x91, 0xAC, 0x6F, 0x50, 0x9B, 0xAC, 0x6F, 0x50, 0xD, 0xAC, 0x6F, 0xF0, 0xD, 0xAC, 0x6F, 0x20, 0x10, 0xAC, 0x6F, 0x70, 0x10, 0xAC, 0x6F, 0x40, 0xF, 0xAC, 0x6F, 0xC0, 0x1D, 0xAC, 0x6F, 0xF0, 0x22, 0xAC, 0x6F, 0, 0x27, 0xAC, 0x6F, 0xE0, 0x51, 0xAC, 0x6F, 0xD0, 0x54, 0xAC, 0x6F, 0xC0, 0x55, 0xAC, 0x6F, 0x60, 0x58, 0xAC, 0x6F, 0x50, 0x5A, 0xAC, 0x6F, 0x50, 0x5B, 0xAC, 0x6F, 0xD0, 0x54, 0xAC, 0x6F, 0xE0, 0x5D, 0xAC, 0x6F, 0xD0, 0x5E, 0xAC, 0x6F, 0x90, 0x62, 0xAC, 0x6F, 0xE0, 0x64, 0xAC, 0x6F, 0xA0, 0x66, 0xAC, 0x6F, 0x60, 0x69, 0xAC, 0x6F, 0x70, 0x6B, 0xAC, 0x6F, 0xB0, 0x6D, 0xAC, 0x6F, 0x30, 0x70, 0xAC, 0x6F, 0x30, 0x73, 0xAC, 0x6F, 0x60, 0x74, 0xAC, 0x6F, 0xC0, 0x75, 0xAC, 0x6F, 0x50, 0x76, 0xAC, 0x6F, 0x30, 0x7C, 0xAC, 0x6F, 0x80, 0x2A, 0xAC, 0x6F, 0x30, 0x2B, 0xAC, 0x6F, 0xE0, 0x2B, 0xAC, 0x6F, 0x10, 0x33, 0xAC, 0x6F, 0x80, 0x34, 0xAC, 0x6F, 0xC0, 0x37, 0xAC, 0x6F, 0xC0, 0x3B, 0xAC, 0x6F, 0x90, 0x3C, 0xAC, 0x6F, 0x30, 0x3F, 0xAC, 0x6F, 0x70, 0x40, 0xAC, 0x6F, 0x50, 0x44, 0xAC, 0x6F, 0, 0x46, 0xAC, 0x6F, 0xC0, 0x47, 0xAC, 0x6F, 0xA0, 0x4C, 0xAC, 0x6F, 0xC0, 0x4E, 0xAC, 0x6F, 0xE0, 0x4F, 0xAC, 0x6F, 0xE0, 4, 0xAC, 0x6F, 0x70, 0xB0, 0xAC, 0x6F, 0xE0, 0xA5, 0xAB, 0x6F, 0x50, 0x93, 0xAC, 0x6F, 0xC0, 0xB3, 0xAC, 0x6F, 0x70, 0x48, 0xAC, 0x6F, 0x90, 0x48, 0xAC, 0x6F, 0x90, 0x2C, 0xAC, 0x6F, 0, 0x32, 0xAC, 0x6F, 0x10, 0x30, 0xAC, 0x6F, 0xE0, 0x4B, 0xAC, 0x6F, 0xF0, 0x79, 0xAC, 0x6F, 0x10, 0x7B, 0xAC, 0x6F, 0xC0, 0xA9, 0xAC, 0x6F};
//D2Client.0x6FB777B0
int32_t dword_6FB777B0 = 130;
//D2Client.0x6FB777B4
uint8_t byte_6FB777B4[7] = {0, 0, 0, 0, 0xF0, 0xB1, 0xAC};
//D2Client.0x6FB777BB
uint32_t dword_6FB777BB = 0x5C3A436F;

//D2Client.0x6FABAEB0
uint32_t __fastcall sub_6FABAEB0(D2UnitStrc* pUnit)
{
	D2InventoryStrc* pInventory;
	bool bVar1;
	D2UnitStrc* pItem;
	int iVar2;
	D2SkillStrc* pSkill;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	char* szFile;

	if (pUnit != nullptr)
	{
		if (pUnit->dwUnitType != 0)
		{
			return 1;
		}
		pItem = D2Common_10434(pUnit, 0);
		bVar1 = true;
		if (pItem == nullptr)
		{
			return 1;
		}
		iVar2 = ITEMS_GetAmmoType(pItem);
		if (iVar2 != 0)
		{
			iVar2 = 0xb6;
			szFile = (char*)(dword_6FB777BB + 1);
			bVar1 = false;
			pSkill = UNITS_GetUsedSkill(pUnit);
			iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, szFile, iVar2);
			if ((iVar2 == 0) &&
			    (iVar2 = STATLIST_UnitGetItemStatOrSkillStatValue(pItem, 0x9d, 0), iVar2 != 0))
			{
				return 1;
			}
		}
		pInventory = pUnit->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
			if (((pDVar3 != nullptr) && ((!bVar1 || (pDVar3 == pItem)))) &&
			    ((uVar4 = ITEMS_CheckIfStackable(pDVar3), uVar4 != 0 ||
			                                                  ((iVar2 = ITEMS_CheckIfThrowable(pDVar3), iVar2 != 0 ||
			                                                                                                (iVar2 = STATLIST_UnitGetItemStatOrSkillStatValue(pDVar3, 0x7d, 0), iVar2 != 0))))))
			{
				iVar2 = ITEMS_CanItemBeUsedForThrowSkill(pDVar3);
				return iVar2;
			}
			pDVar3 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
			if ((pDVar3 != nullptr) && ((!bVar1 || (pDVar3 == pItem))))
			{
				uVar4 = ITEMS_CheckIfStackable(pDVar3);
				if ((uVar4 == 0) &&
				    ((iVar2 = ITEMS_CheckIfThrowable(pDVar3), iVar2 == 0 &&
				                                                  (iVar2 = STATLIST_UnitGetItemStatOrSkillStatValue(pDVar3, 0x7d, 0), iVar2 == 0))))
				{
					return 0;
				}
				iVar2 = ITEMS_CanItemBeUsedForThrowSkill(pDVar3);
				return iVar2;
			}
		}
	}
	return 0;
}

//D2Client.0x6FABAFC0
uint32_t* __fastcall sub_6FABAFC0(uint32_t a1, D2UnitStrc* pUnit, uint32_t a3, uint32_t a4, int a5, int a6, int a7, int a8)
{
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint8_t bVar2;
	int32_t DVar3;
	int32_t DVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	int* piVar7;
	int aiStack_9c[17];
	D2UnitStrc* local_58;
	uint32_t uStack_4c;
	int local_48;
	int iStack_44;
	int iStack_40;
	int32_t DStack_3c;
	uint32_t uStack_30;
	uint32_t uStack_2c;

	piVar7 = aiStack_9c + 0x10;
	for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*piVar7 = 0;
		piVar7 = piVar7 + 1;
	}
	uVar1 = pUnit->dwUnitType;
	aiStack_9c[0x10] = 0x21;
	local_58 = pUnit;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		local_48 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_48 = 0;
	}
	else
	{
		local_48 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	local_48 = local_48 + a5;
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar3 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
	}
	else
	{
		DVar3 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	iStack_44 = (int)DVar3 + a6;
	uStack_30 = a3;
	uStack_2c = a4;
	uStack_4c = a1;
	if ((a7 == 0) || (a8 == 0))
	{
		pDVar5 = sub_6FB296A0((int)pUnit);
		if (pDVar5 == nullptr)
		{
			pDynamicPath = pUnit->pDynamicPath;
			iStack_40 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
			a8 = D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
		}
		else
		{
			uVar1 = pDVar5->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iStack_40 = pDVar5->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar5->pDynamicPath == nullptr)
			{
				iStack_40 = 0;
			}
			else
			{
				iStack_40 = PATH_GetXPosition(pDVar5->pDynamicPath);
			}
			uVar1 = pDVar5->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				a8 = *(int*)&pDVar5->pDynamicPath->tTargetCoord;
			}
			else if (pDVar5->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&a8 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&a8 + 2)) = 0;
			}
			else
			{
				a8 = PATH_GetYPosition(pDVar5->pDynamicPath);
			}
		}
		if ((iStack_40 == 0) || ((int32_t)a8 == (int32_t)0x0))
		{
			DStack_3c = (int32_t)a8;
			bVar2 = UNITS_GetDirection(pUnit);
			aiStack_9c[0xd] = 1;
			aiStack_9c[0xf] = 1;
			aiStack_9c[1] = 1;
			aiStack_9c[7] = 1;
			uVar1 = pUnit->dwUnitType;
			aiStack_9c[8] = 0;
			aiStack_9c[9] = 0xffffffff;
			aiStack_9c[10] = 0xfffffffe;
			aiStack_9c[0xb] = 0xffffffff;
			aiStack_9c[0xc] = 0;
			aiStack_9c[0xe] = 2;
			aiStack_9c[0] = 2;
			aiStack_9c[2] = 0;
			aiStack_9c[3] = 0xffffffff;
			aiStack_9c[4] = 0xfffffffe;
			aiStack_9c[5] = 0xffffffff;
			aiStack_9c[6] = 0;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iVar6 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar1 = pUnit->dwUnitType;
			iStack_40 = aiStack_9c[(bVar2 >> 3) + 8] + iVar6;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
			a8 = aiStack_9c[bVar2 >> 3] + (int)DVar4;
		}
	}
	else
	{
		iStack_40 = a7;
	}
	if ((iStack_40 != 0) && ((int32_t)a8 != (int32_t)0x0))
	{
		DStack_3c = (int32_t)a8;
		pDVar5 = sub_6FB3E070((uint32_t*)(aiStack_9c + 0x10));
		return &pDVar5->dwUnitType;
	}
	return nullptr;
}

//D2Client.0x6FABB220
int __fastcall sub_6FABB220(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, uint32_t a3)
{
	D2ActiveRoomStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	D2ActiveRoomStrc* pDVar4;
	uint32_t uVar5;
	bool bVar6;
	D2CoordStrc DStack_10;
	D2CoordStrc DStack_8;

	if (pUnit2 == nullptr)
	{
		return 0;
	}
	switch (pUnit2->dwUnitType)
	{
	case 0:
		if ((a3 & 1) == 0)
		{
			return 0;
		}
		uVar3 = pUnit2->dwAnimMode;
		if ((a3 & 0x1000) == 0)
		{
			if (uVar3 == 0x11)
			{
				return 0;
			}
			if (uVar3 == 0)
			{
				return uVar3;
			}
			goto LAB_6fabb357;
		}
		bVar6 = uVar3 == 0x11;
		break;
	case 1:
		if ((a3 & 2) == 0)
		{
			return 0;
		}
		uVar3 = pUnit2->dwAnimMode;
		if ((a3 & 0x1000) == 0)
		{
			if (uVar3 == 0xc)
			{
				return 0;
			}
			if (uVar3 == 0)
			{
				return 0;
			}
		}
		else if (uVar3 != 0xc)
		{
			return 0;
		}
		if (((a3 & 4) != 0) && (iVar2 = MONSTERS_IsUndead(pUnit2), iVar2 == 0))
		{
			return 0;
		}
		if (((a3 & 0x4000) != 0) &&
		    (iVar2 = MONSTERS_IsBoss(nullptr, pUnit2), iVar2 != 0))
		{
			return 0;
		}
		if ((a3 & 0x40000) == 0)
			goto LAB_6fabb357;
		iVar2 = MONSTERS_IsPrimeEvil(pUnit2);
		bVar6 = iVar2 == 0;
		break;
	case 2:
		if ((a3 & 0x10) == 0)
		{
			return 0;
		}
		goto LAB_6fabb357;
	case 3:
		if ((a3 & 8) == 0)
		{
			return 0;
		}
		iVar2 = pUnit2->dwClassId;
		if (iVar2 < 0)
		{
			return 0;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar2)
		{
			return 0;
		}
		iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4;
		if (iVar2 == 0)
		{
			return 0;
		}
		bVar6 = ((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar2 + 4)) == 0;
		break;
	case 4:
		if ((a3 & 0x20) == 0)
		{
			return 0;
		}
		goto LAB_6fabb357;
	default:
		return 0;
	}
	if (!bVar6)
	{
		return 0;
	}
LAB_6fabb357:
	if (((char)a3 < '\0') && ((pUnit2->dwFlags >> 2 & 1) == 0))
	{
		return 0;
	}
	if (((a3 & 0x400) != 0) && ((pUnit2->dwFlags >> 3 & 1) == 0))
	{
		return 0;
	}
	if ((a3 & 0x100) != 0)
	{
		pDVar1 = UNITS_GetRoom(pUnit2);
		iVar2 = DUNGEON_IsRoomInTown(pDVar1);
		if (iVar2 != 0)
		{
			return 0;
		}
	}
	if ((a3 & 0x10000) != 0)
	{
		uVar3 = pUnit2->dwUnitId;
		if ((pUnit2->dwUnitType == 1) && (uVar3 = sub_6FAB1B00(uVar3), uVar3 == 0xffffffff))
		{
			return 0;
		}
		if (pUnit == nullptr)
		{
			uVar5 = 0xffffffff;
		}
		else
		{
			uVar5 = pUnit->dwUnitId;
		}
		iVar2 = sub_6FAB1260(uVar5, uVar3);
		if (iVar2 == 0)
		{
			return 0;
		}
		if (pUnit2->dwUnitType == 1)
		{
			iVar2 = pUnit2->dwClassId;
			if (iVar2 < 0)
			{
				return 0;
			}
			if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar2)
			{
				return 0;
			}
			iVar2 = iVar2 * 0x1a8 + *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78);
			if (iVar2 == 0)
			{
				return 0;
			}
			if (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar2 + 0xd)) != 0)
			{
				return 0;
			}
		}
	}
	if ((((-1 < (char)(a3 >> 8)) || (uVar3 = sub_6FB29D80(pUnit, pUnit2), uVar3 != 0)) &&
	        (((a3 & 0x20000) == 0 || (iVar2 = UNITS_IsInMeleeRange(pUnit, pUnit2, 0), iVar2 != 0)))) &&
	    (((a3 & 0x80000) == 0 || (iVar2 = STATES_CheckState(pUnit2, 0x56), iVar2 == 0))))
	{
		if ((a3 & 0x200) == 0)
		{
			return 1;
		}
		pDVar1 = UNITS_GetRoom(pUnit);
		if ((pDVar1 != nullptr) &&
		    (pDVar4 = UNITS_GetRoom(pUnit2), pDVar4 != nullptr))
		{
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_8.nX = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				DStack_8.nX = 0;
			}
			else
			{
				DStack_8.nX = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_8.nY = *(int*)&pUnit->pDynamicPath->tTargetCoord;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_8.nY + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_8.nY + 2)) = 0;
			}
			else
			{
				DStack_8.nY = PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar3 = pUnit2->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_10.nX = pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				DStack_10.nX = 0;
			}
			else
			{
				DStack_10.nX = PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			uVar3 = pUnit2->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_10.nY = *(int*)&pUnit2->pDynamicPath->tTargetCoord;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_10.nY + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_10.nY + 2)) = 0;
			}
			else
			{
				DStack_10.nY = PATH_GetYPosition(pUnit2->pDynamicPath);
			}
			iVar2 = COLLISION_RayTrace(pDVar1, &DStack_8, &DStack_10, 4);
			if (iVar2 == 0)
			{
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FABB590
void __fastcall sub_6FABB590(D2UnitStrc* pUnit, int a2, int32_t a3, int a4, uint32_t a5, int a6, uint32_t a7, int a8)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	D2ActiveRoomStrc* pRoom;
	int32_t nY1;
	int iVar4;
	int32_t nY2;
	D2ActiveRoomStrc** ppDStack_44;
	int local_40;
	D2UnitStrc* local_3c;
	uint32_t uStack_38;
	int iStack_34;
	uint32_t uStack_30;
	D2UnitStrc* pDStack_2c;
	int iStack_28;
	uint32_t uStack_24;
	D2DrlgCoordsStrc DStack_20;

	if ((((pUnit != nullptr) && (a6 != 0)) && (a4 != 0)) &&
	    (local_40 = a2, local_3c = pUnit, pRoom = UNITS_GetRoom(pUnit),
	        pRoom != nullptr))
	{
		if ((a2 == 0) || (nY1 = a3, a3 == (int32_t)0x0))
		{
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				local_40 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				local_40 = 0;
			}
			else
			{
				local_40 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				nY1 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&nY1 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&nY1 + 2)) = 0;
			}
			else
			{
				nY1 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
		}
		if (a5 == 0)
		{
			a5 = 0x583;
		}
		iStack_34 = a4 * a4;
		uStack_24 = a7;
		iStack_28 = 0;
		pDStack_2c = pUnit;
		DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_44, (int*)&uStack_38);
		a3 = (int32_t)0x0;
		if (uStack_38 != 0)
		{
			do
			{
				if (((((a5 & 0x2000) == 0) ||
				         (iVar4 = DUNGEON_IsRoomInTown(ppDStack_44[(int)a3]), iVar4 == 0)) &&
				        ((DUNGEON_GetRoomCoordinates(ppDStack_44[(int)a3], &DStack_20),
				            DStack_20.nSubtileX <= local_40 + a4 ||
				                (local_40 - a4 <= DStack_20.nSubtileWidth + DStack_20.nSubtileX)))) &&
				    ((DStack_20.nSubtileY <= a4 + (int)nY1 ||
				        ((int)nY1 - a4 <= DStack_20.nSubtileHeight + DStack_20.nSubtileY))))
				{
					pDVar2 = ppDStack_44[(int)a3]->pUnitFirst;
					while (pDVar3 = pDVar2, pDVar3 != nullptr)
					{
						pDVar2 = pDVar3->pRoomNext;
						if (pDVar3 != local_3c)
						{
							uVar1 = pDVar3->dwUnitType;
							if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
							{
								nY2 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
							}
							else if (pDVar3->pDynamicPath == nullptr)
							{
								(*(uint16_t*)((uint8_t*)&nY2 + 0)) = 0;
								(*(uint16_t*)((uint8_t*)&nY2 + 2)) = 0;
							}
							else
							{
								nY2 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
							}
							uVar1 = pDVar3->dwUnitType;
							if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
							{
								iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
							}
							else if (pDVar3->pDynamicPath == nullptr)
							{
								iVar4 = 0;
							}
							else
							{
								iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
							}
							iVar4 = PATH_ComputeSquaredDistance(local_40, (int)nY1, iVar4, (int)nY2);
							if ((((iVar4 <= iStack_34) &&
							         (iVar4 = sub_6FABB220(local_3c, pDVar3, a5), iVar4 != 0)) &&
							        ((a8 == 0 ||
							            ((((pDVar3->dwUnitType != 1 || (iVar4 = pDVar3->dwClassId, iVar4 < 0)) ||
							                  (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar4)) ||
							                ((iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar4 * 0x1a8,
							                    iVar4 == 0 ||
							                        (uStack_30 = (uint32_t) * (uint8_t*)(iVar4 + 0xf) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0xc),
							                            uStack_30 == 0)))))))) &&
							    (iVar4 = (*(code*)a6)(), iVar4 != 0))
							{
								iStack_28 = iStack_28 + 1;
							}
						}
					}
				}
				a3 = (int32_t)((int)a3 + 1);
			} while ((uint32_t)a3 < uStack_38);
		}
	}
}

//D2Client.0x6FABB840
uint32_t __fastcall sub_6FABB840(D2UnitStrc* pUnit, int a2, uint32_t a3, int a4, uint32_t a5)
{
	uint32_t local_4;

	local_4 = 0;
	sub_6FABB590(pUnit, a2, a3, a4, a5 | 0xa783, 0x6fabb880, (uint32_t)(&local_4), 0);
	return local_4;
}

//D2Client.0x6FABB880
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FABB880()
{
	int in_ECX;

	**(int**)(in_ECX + 8) = **(int**)(in_ECX + 8) + 1;
	return 1;
}

//D2Client.0x6FABB890
D2UnitStrc* __fastcall sub_6FABB890(D2UnitStrc* pUnit, int a2, uint32_t a3, int a4, uint32_t a5, uint32_t a6, uint32_t* a7)
{
	D2UnitStrc* local_18;
	uint32_t local_14;
	D2UnitStrc* local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint32_t local_4;

	local_18 = nullptr;
	local_c = a6;
	local_8 = a6;
	local_14 = 0xffffffff;
	local_10 = nullptr;
	local_4 = 0;
	if (a5 == 0)
	{
		a5 = 0x583;
	}
	sub_6FABB590(pUnit, a2, a3, a4, a5 | 0xa280, 0x6fabb910, (uint32_t)(&local_18), 0);
	if (local_18 == nullptr)
	{
		local_18 = local_10;
	}
	if (a7 != nullptr)
	{
		*a7 = local_4;
	}
	return local_18;
}

//D2Client.0x6FABB910
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FABB910()
{
	int* piVar1;
	int in_ECX;
	uint32_t uVar2;
	int in_EDX;

	piVar1 = *(int**)(in_ECX + 8);
	if (in_EDX == 0)
	{
		uVar2 = 0xffffffff;
	}
	else
	{
		uVar2 = *(uint32_t*)(in_EDX + 0xc);
	}
	if (((uint32_t)piVar1[4] < uVar2) && (uVar2 < (uint32_t)piVar1[1]))
	{
		piVar1[1] = uVar2;
		*piVar1 = in_EDX;
		piVar1[5] = piVar1[5] + 1;
		return 1;
	}
	if (uVar2 <= (uint32_t)piVar1[3])
	{
		piVar1[3] = uVar2;
		piVar1[2] = in_EDX;
	}
	piVar1[5] = piVar1[5] + 1;
	return 1;
}

//D2Client.0x6FABB960
uint32_t __fastcall sub_6FABB960(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	int iVar1;
	D2UnitStrc* pItem;

	iVar1 = COMPOSIT_IsWeaponBowOrXBow(pUnit);
	if (iVar1 == 0)
	{
		pItem = D2Common_10434(pUnit, 0);
		if (pItem != nullptr)
		{
			iVar1 = ITEMS_CheckItemTypeId(pItem, 0x26);
			if (iVar1 != 0)
			{
				return 0;
			}
		}
	}
	else
	{
		iVar1 = sub_6FABAEB0(pUnit);
		if (iVar1 == 0)
		{
			return 0;
		}
	}
	return 1;
}

//D2Client.0x6FABB9B0
bool __fastcall sub_6FABB9B0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	int iVar1;
	D2UnitStrc* pDVar2;

	iVar1 = sub_6FABAEB0(pUnit);
	if (iVar1 == 0)
	{
		return false;
	}
	pDVar2 = D2Common_10434(pUnit, 0);
	return pDVar2 != nullptr;
}

//D2Client.0x6FABB9E0
bool __fastcall sub_6FABB9E0(int a1, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;

	pDVar1 = sub_6FB296A0(a1);
	if (pDVar1 == nullptr)
	{
		return false;
	}
	if (pDVar1->dwUnitType != 1)
	{
		return false;
	}
	iVar2 = sub_6FAB1B00(pDVar1->dwUnitId);
	if (a1 == 0)
	{
		iVar3 = -1;
	}
	else
	{
		iVar3 = *(int*)(a1 + 0xc);
	}
	if (iVar2 != iVar3)
	{
		return false;
	}
	iVar2 = sub_6FAB1B20(pDVar1->dwUnitId);
	if (((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbf0))) &&
	    (iVar2 = iVar2 * 0xe0 + *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbe8), iVar2 != 0))
	{
		return ((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(iVar2 + 4)) != 0;
	}
	return false;
}

//D2Client.0x6FABBA80
uint32_t __cdecl sub_6FABBA80(uint32_t a1)
{
	return 1;
}

//D2Client.0x6FABBA90
uint32_t __fastcall sub_6FABBA90(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar2;
	uint8_t bVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	int32_t DVar7;
	int32_t DVar8;
	int aiStack_40[16];

	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x40;
	}
	iVar4 = COMPOSIT_IsWeaponBowOrXBow(pUnit);
	if (iVar4 == 0)
	{
		sub_6FB296A0((int)pUnit);
		MEMORY_Nop();
	}
	else
	{
		iVar4 = D2COMMON_11039_CheckWeaponIsMissileBased(pUnit, (int*)(&a3));
		uVar2 = a3;
		if (iVar4 != -1)
		{
			pDVar5 = sub_6FB296A0((int)pUnit);
			if (pDVar5 == nullptr)
			{
				pDynamicPath = pUnit->pDynamicPath;
				iVar6 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
				DVar7 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
			}
			else
			{
				uVar1 = pDVar5->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar6 = pDVar5->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar5->pDynamicPath == nullptr)
				{
					iVar6 = 0;
				}
				else
				{
					iVar6 = PATH_GetXPosition(pDVar5->pDynamicPath);
				}
				uVar1 = pDVar5->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar7 = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
				}
				else if (pDVar5->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
				}
				else
				{
					DVar7 = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
				}
			}
			if ((iVar6 == 0) || (DVar7 == (int32_t)0x0))
			{
				bVar3 = UNITS_GetDirection(pUnit);
				aiStack_40[2] = 0xfffffffe;
				aiStack_40[0xc] = 0xfffffffe;
				uVar1 = pUnit->dwUnitType;
				aiStack_40[0] = 0;
				aiStack_40[1] = 0xffffffff;
				aiStack_40[3] = 0xffffffff;
				aiStack_40[4] = 0;
				aiStack_40[5] = 1;
				aiStack_40[6] = 2;
				aiStack_40[7] = 1;
				aiStack_40[8] = 2;
				aiStack_40[9] = 1;
				aiStack_40[10] = 0;
				aiStack_40[0xb] = 0xffffffff;
				aiStack_40[0xd] = 0xffffffff;
				aiStack_40[0xe] = 0;
				aiStack_40[0xf] = 1;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar6 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar6 = 0;
				}
				else
				{
					iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
				iVar6 = aiStack_40[bVar3 >> 3] + iVar6;
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar8 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath != nullptr)
				{
					DVar8 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				DVar7 = (int32_t)(aiStack_40[(bVar3 >> 3) + 8] + (int)DVar8);
			}
			if ((iVar6 != 0) && (DVar7 != (int32_t)0x0))
			{
				sub_6FB3EB50(pUnit, iVar4, iVar6, (D2UnitStrc*)DVar7, a2, uVar2);
			}
			return 1;
		}
	}
	return 1;
}

//D2Client.0x6FABBC70
uint32_t __fastcall sub_6FABBC70(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2DynamicPathStrc* pDVar1;
	uint8_t bVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	int iVar5;
	int32_t DVar6;
	D2UnitStrc** ppDVar7;
	int32_t DStack_50;
	int iStack_4c;
	uint32_t local_48;
	int iStack_44;
	int aiStack_40[16];

	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x40;
	}
	local_48 = a2;
	pDVar3 = D2Common_10434(pUnit, 0);
	if (pDVar3 == nullptr)
	{
		return 0;
	}
	iStack_44 = ITEMS_GetMissileType(pDVar3);
	uVar4 = ITEMS_GetItemType(pDVar3);
	if (uVar4 == 0x26)
	{
		pDVar3 = sub_6FB296A0((int)pUnit);
		if (pDVar3 == nullptr)
		{
			pDVar1 = pUnit->pDynamicPath;
			iVar5 = D2COMMON_10175_PathGetFirstPointX(pDVar1);
			DVar6 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDVar1);
		}
		else
		{
			uVar4 = pDVar3->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				iVar5 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iVar5 = 0;
			}
			else
			{
				iVar5 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar4 = pDVar3->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				DVar6 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
			}
			else
			{
				DVar6 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
		}
		if ((iVar5 == 0) || (DVar6 == (int32_t)0x0))
		{
			bVar2 = UNITS_GetDirection(pUnit);
			aiStack_40[2] = 0xfffffffe;
			aiStack_40[0xc] = 0xfffffffe;
			aiStack_40[0] = 0;
			aiStack_40[1] = 0xffffffff;
			aiStack_40[3] = 0xffffffff;
			aiStack_40[4] = 0;
			aiStack_40[5] = 1;
			aiStack_40[6] = 2;
			aiStack_40[7] = 1;
			aiStack_40[8] = 2;
			aiStack_40[9] = 1;
			aiStack_40[10] = 0;
			aiStack_40[0xb] = 0xffffffff;
			aiStack_40[0xd] = 0xffffffff;
			aiStack_40[0xe] = 0;
			aiStack_40[0xf] = 1;
			iVar5 = sub_6FAB6A60((int*)pUnit);
			iVar5 = iVar5 + aiStack_40[bVar2 >> 3];
			ppDVar7 = sub_6FAB6A90((int*)pUnit);
			DVar6 = (int32_t)((int)ppDVar7 + aiStack_40[(bVar2 >> 3) + 8]);
		}
		sub_6FB3EBE0(pUnit, iStack_44, 0, 0, iVar5, (int)DVar6, local_48, 1, 0);
		return 1;
	}
	pDVar3 = sub_6FB296A0((int)pUnit);
	if (pDVar3 == nullptr)
	{
		pDVar1 = pUnit->pDynamicPath;
		iVar5 = D2COMMON_10175_PathGetFirstPointX(pDVar1);
		iStack_4c = iVar5;
		DStack_50 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDVar1);
	}
	else
	{
		uVar4 = pDVar3->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			iVar5 = pDVar3->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			iVar5 = 0;
		}
		else
		{
			iVar5 = PATH_GetXPosition(pDVar3->pDynamicPath);
		}
		uVar4 = pDVar3->dwUnitType;
		iStack_4c = iVar5;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DStack_50 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_50 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_50 + 2)) = 0;
		}
		else
		{
			DStack_50 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
		}
	}
	if ((iVar5 == 0) || (DStack_50 == (int32_t)0x0))
	{
		sub_6FABA860(pUnit, &iStack_4c, &DStack_50);
		iVar5 = iStack_4c;
	}
	if ((iVar5 != 0) && (DStack_50 != (int32_t)0x0))
	{
		sub_6FB3EB50(pUnit, iStack_44, iVar5, (D2UnitStrc*)DStack_50, local_48, 1);
	}
	return 1;
}

//D2Client.0x6FABBEB0
int32_t __fastcall sub_6FABBEB0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, int* a4)
{
	return sub_6FABBED0(pUnit, a2, a4, a3);
}

//D2Client.0x6FABBED0
// TODO: decompilation needs review (extraout)
int __fastcall sub_6FABBED0(D2UnitStrc* pUnit, uint32_t a22, int* a3, int a4)
{
	D2DynamicPathStrc* pDynamicPath;
	bool bVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* nX;
	D2SkillStrc* pSkill;
	uint32_t uVar3;
	uint32_t extraout_var;
	D2ActiveRoomStrc* pRoom;
	float fVar4;
	int iVar5;
	uint32_t* a2;
	void* pvVar6;
	uint16_t nColMask;
	int iVar7;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t extraout_EDX_01;
	uint32_t extraout_EDX_02;
	uint32_t uVar8;
	uint32_t extraout_EDX_03;
	uint32_t extraout_EDX_04;
	uint32_t extraout_EDX_05;
	uint32_t extraout_EDX_06;
	uint32_t extraout_EDX_07;
	uint32_t extraout_EDX_08;
	int* piVar9;
	int iVar10;
	short sVar11;
	uint32_t* puVar12;
	uint64_t uVar13;
	D2UnitStrc** local_2c;
	D2UnitStrc* local_28;
	int local_24;
	uint32_t uStack_20;
	uint32_t auStack_1c[7];

	if (((int)a22 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= (int)a22))
	{
		return 0;
	}
	iVar10 = a22 * 0x23c;
	local_24 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar10;
	if (local_24 == 0)
	{
		return 0;
	}
	if (*(char*)(local_24 + 399) != '\0')
	{
		pDVar2 = sub_6FB296A0((int)pUnit);
		if (pDVar2 == nullptr)
		{
			pDynamicPath = pUnit->pDynamicPath;
			nX = (D2UnitStrc*)D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
			local_28 = nX;
			local_2c = (D2UnitStrc**)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
		}
		else
		{
			uVar3 = pDVar2->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				nX = (D2UnitStrc*)pDVar2->pDynamicPath->dwClientCoordY;
				local_28 = nX;
				local_2c = sub_6FAB6A90((int*)pDVar2);
			}
			else if (pDVar2->pDynamicPath == nullptr)
			{
				nX = nullptr;
				local_28 = nullptr;
				local_2c = sub_6FAB6A90((int*)pDVar2);
			}
			else
			{
				nX = (D2UnitStrc*)PATH_GetXPosition(pDVar2->pDynamicPath);
				local_28 = nX;
				local_2c = sub_6FAB6A90((int*)pDVar2);
			}
		}
		if ((nX == nullptr) || (local_2c == nullptr))
		{
			sub_6FABA860(pUnit, (int*)&local_28, (int*)(&local_2c));
			nX = local_28;
		}
		switch (*(uint8_t*)(local_24 + 399))
		{
		case 1:
			nColMask = 4;
			break;
		case 2:
			nColMask = 0x1c09;
			break;
		case 3:
			nColMask = 0x180;
			break;
		case 4:
			nColMask = 0x804;
			break;
		case 5:
			nColMask = 0x805;
			break;
		default:
			goto switchD_6fabbfd6_default;
		}
		iVar7 = D2Common_11026((int)nX, (int)local_2c, pUnit, nColMask);
		if (iVar7 == 0)
		{
			return 0;
		}
	}
	pDVar2 = sub_6FB296A0((int)pUnit);
	if ((pDVar2 != nullptr) &&
	    (((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= (int)a22 ||
	          (iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar10, iVar7 == 0)) ||
	        ((((uint8_t)((uint8_t*)&gdwBitMasks)[0x14] & *(uint8_t*)(iVar7 + 6)) != 0 &&
	            (((pDVar2->dwUnitType == 1 && (pDVar2->dwAnimMode == 0xc)) &&
	                (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar7 + 7)) == 0))))))))
	{
		return 0;
	}
	pSkill = UNITS_GetUsedSkill(pUnit);
	if ((pSkill == nullptr) ||
	    (uVar3 = SKILLS_GetSkillIdFromSkill(pSkill, (const char*)(dword_6FB777BB + 1), 0x504),
	        uVar3 != a22))
	{
		pSkill = SKILLS_GetSkillById(pUnit, a22, (uint32_t)a3);
		if (pSkill == nullptr)
		{
			SKILLS_AddSkill(pUnit, a22);
			pSkill = SKILLS_GetSkillById(pUnit, a22, (uint32_t)a3);
			if (((pSkill != nullptr) && (pDVar2 = CUNIT_GetPlayer(), pUnit == pDVar2)) &&
			    (a3 == (int*)0xffffffff))
			{
				SKILLS_SetFlags(pSkill, 8);
			}
			if ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= (int)a22) ||
			    (iVar7 = (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + 300 + iVar10),
			        iVar7 < 1))
			{
				iVar7 = 0x14;
			}
			if (iVar7 < a4)
			{
				SKILLS_AssignSkill(pUnit, a22, iVar7, 0, (const char*)(dword_6FB777BB + 1),
				    0x513);
				D2Common_11030(pUnit, a22, a4 - iVar7);
			}
			else
			{
				SKILLS_AssignSkill(pUnit, a22, a4, 0, (const char*)(dword_6FB777BB + 1), 0x518);
			}
			if (pSkill == nullptr)
			{
				return 0;
			}
		}
		UNITS_SetUsedSkill(pUnit, pSkill);
	}
	if (a3 != (int*)0xffffffff)
	{
		iVar7 = SKILLS_GetSkillInfo(pSkill, &uStack_20, (int*)&local_2c, &a4, (int*)&local_28);
		if (iVar7 == 0)
		{
			return 0;
		}
		if (local_28 == nullptr)
		{
			return 0;
		}
	}
	pDVar2 = CUNIT_GetPlayer();
	if (pUnit == pDVar2)
	{
		a4 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
	}
	else
	{
		if ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= (int)a22) ||
		    (iVar10 = (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + 300 + iVar10),
		        iVar10 < 1))
		{
			iVar10 = 0x14;
		}
		if (iVar10 < a4)
		{
			SKILLS_AssignSkill(pUnit, a22, iVar10, 0, (const char*)(dword_6FB777BB + 1),
			    0x53a);
			D2Common_11030(pUnit, a22, a4 - iVar10);
		}
		else
		{
			SKILLS_AssignSkill(pUnit, a22, a4, 0, (const char*)(dword_6FB777BB + 1),
			    0x53f);
		}
	}
	pDVar2 = sub_6FB296A0((int)pUnit);
	iVar10 = local_24;
	if (((pDVar2 != nullptr) &&
	        (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(local_24 + 7)) == 0)) &&
	    (bVar1 = sub_6FB2A1C0(pUnit, (int*)pDVar2), D2C_ZEXT(bVar1) != 0))
	{
		return 0;
	}
	if (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar10 + 5)) == 0)
	{
		pRoom = UNITS_GetRoom(pUnit);
		iVar7 = DUNGEON_IsRoomInTown(pRoom);
		if (iVar7 != 0)
		{
			UNITS_SetUsedSkill(pUnit, nullptr);
			puVar12 = auStack_1c;
			for (iVar10 = 7; iVar10 != 0; iVar10 = iVar10 + -1)
			{
				*puVar12 = 0;
				puVar12 = puVar12 + 1;
			}
			sub_6FB4EE00(7, pUnit, auStack_1c, 0);
			pDVar2 = CUNIT_GetPlayer();
			if (pUnit == pDVar2)
			{
				sub_6FB514E0(pUnit, 0x18);
			}
		switchD_6fabbfd6_default:
			return 0;
		}
	}
	if (((pUnit == nullptr) || ((char)pUnit->dwUnitType != '\0')) || (a22 != 0))
	{
		piVar9 = (int*)SKILLS_GetSkillModeFromUnit(pUnit, pSkill);
	}
	else
	{
		piVar9 = (int*)0x7;
		pDVar2 = sub_6FB296A0((int)pUnit);
		bVar1 = true;
		if ((pDVar2 != nullptr) && (pDVar2->dwUnitType == 1))
		{
			iVar7 = pDVar2->dwClassId;
			if ((iVar7 < 0) ||
			    (((iVar5 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar5 + 0xa80) <= iVar7 ||
			                                                       (iVar7 = (int)*(short*)(*(int*)(iVar5 + 0xa78) + 0x18 + iVar7 * 0x1a8), iVar7 < 0)) ||
			        (*(int*)(iVar5 + 0xa98) <= iVar7))))
			{
				iVar7 = 0;
			}
			else
			{
				iVar7 = *(int*)(iVar5 + 0xa90) + iVar7 * 0x134;
			}
			bVar1 = *(char*)(iVar7 + 0xb) != '\x02';
			if (!bVar1)
			{
				piVar9 = (int*)0x8;
			}
			if (*(char*)(iVar7 + 0xb) == '\x01')
			{
				bVar1 = false;
			}
		}
		iVar7 = COMPOSIT_IsWeaponBowOrXBow(pUnit);
		if (iVar7 != 0)
		{
			piVar9 = (int*)0x7;
			bVar1 = false;
		}
		iVar7 = INVENTORY_GetEquippedWeapon(pUnit->pInventory, &local_28, &local_24, (int*)&uStack_20);
		if (iVar7 == 0)
		{
			piVar9 = (int*)0x7;
		}
		else if ((bVar1) && (uVar3 = sub_6FAA88D0(&(pUnit->pSeed).nLowSeed), (uVar3 & 0x3f) < 0x20))
		{
			piVar9 = (int*)0x8;
		}
	}
	if (piVar9 == nullptr)
	{
		iVar7 = STATES_CheckState(pUnit, 0xc);
		uVar8 = extraout_EDX;
		if (((iVar7 != 0) && (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(iVar10 + 5)) != 0)) ||
		    ((pUnit == nullptr || ((pUnit->dwUnitType != 0 && (pUnit->dwUnitType != 1))))))
			goto LAB_6fabc3fc;
		piVar9 = (int*)0x1;
	}
	sub_6FB4F410(pUnit, piVar9);
	uVar8 = extraout_EDX_00;
LAB_6fabc3fc:
	sVar11 = *(short*)(iVar10 + 0xf2);
	local_24 = 1;
	uVar13 = CONCAT44(uVar8, 1);
	if (((-1 < sVar11) && (uVar13 = CONCAT44(uVar8, 1), sVar11 < dword_6FB775A0)) &&
	    (uVar13 = CONCAT44(uVar8, 1), *(code**)(byte_6FB77488 + sVar11 * 4) != nullptr))
	{
		uVar13 = (**(code**)(byte_6FB77488 + sVar11 * 4))(a4);
		local_24 = (int)uVar13;
		if (local_24 == 0)
		{
			UNITS_SetUsedSkill(pUnit, nullptr);
			uVar8 = extraout_EDX_01;
			if ((pUnit != nullptr) &&
			    ((pUnit->dwUnitType == 0 || (pUnit->dwUnitType == 1))))
			{
				sub_6FB4F410(pUnit, (int*)0x1);
				uVar8 = extraout_EDX_02;
			}
			uVar13 = CONCAT44(uVar8, local_24);
			if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar10 + 5)) != 0)
			{
				return local_24;
			}
		}
	}
	local_24 = (int)uVar13;
	sVar11 = *(short*)(iVar10 + 0xfc);
	if ((a3 != (int*)0xffffffff) && (0 < *(short*)(iVar10 + 0x122)))
	{
		sVar11 = *(short*)(iVar10 + 0x122);
	}
	if (0 < sVar11)
	{
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x14] & *(uint8_t*)(iVar10 + 5)) == 0)
		{
			fVar4 = 0.0;
		}
		else
		{
			uVar3 = UNITS_GetHitClass(pUnit);
			uVar3 = sub_6FB4F530((int)pUnit, uVar3);
			fVar4 = (float)(uVar3 - 3 & ((int)(uVar3 - 3) < 0) - 1);
		}
		sub_6FB55820((int)sVar11, pUnit, fVar4, 0.0, 0);
		uVar13 = CONCAT44(extraout_EDX_03, local_24);
	}
	local_24 = (int)uVar13;
	uVar3 = CONCAT31((int32_t)((uint64_t)uVar13 >> 0x28), *(uint8_t*)(iVar10 + 5));
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x18] & *(uint8_t*)(iVar10 + 5)) != 0)
	{
		uVar3 = UNITS_GetHitClass(pUnit);
		iVar7 = sub_6FB4F4D0((int)pUnit, uVar3);
		uVar3 = extraout_EDX_04;
		if (iVar7 != 0)
		{
			uVar3 = UNITS_GetHitClass(pUnit);
			uVar3 = sub_6FB4F530((int)pUnit, uVar3);
			sub_6FB55820(iVar7, pUnit, (float)(uVar3 & ((int)uVar3 < 0) - 1), 0.0, 0);
			uVar3 = extraout_EDX_05;
		}
	}
	sVar11 = *(short*)(iVar10 + 0xfe);
	if (((((a3 == (int*)0xffffffff) || (*(short*)(iVar10 + 0x122) < 1)) && (0 < sVar11)) &&
	        ((pUnit != nullptr && (pUnit->dwUnitType == 0)))) &&
	    (uVar3 = (uint32_t) * (uint8_t*)(iVar10 + 0xc), pUnit->dwClassId == uVar3))
	{
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x14] & *(uint8_t*)(iVar10 + 5)) == 0)
		{
			fVar4 = 0.0;
		}
		else
		{
			uVar3 = UNITS_GetHitClass(pUnit);
			uVar3 = sub_6FB4F530((int)pUnit, uVar3);
			fVar4 = (float)(uVar3 - 3 & ((int)(uVar3 - 3) < 0) - 1);
		}
		sub_6FB55820((int)sVar11, pUnit, fVar4, 0.0, 0);
		uVar3 = extraout_EDX_06;
	}
	iVar7 = (int)*(short*)(iVar10 + 0x106);
	if ((a3 != (int*)0xffffffff) && (0 < *(short*)(iVar10 + 0x124)))
	{
		iVar7 = (int)*(short*)(iVar10 + 0x124);
	}
	if (((0 < iVar7) && (iVar7 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0))) &&
	    (iVar5 = sub_6FB57CD0((int)pUnit, iVar7), uVar3 = extraout_EDX_07, iVar5 == 0))
	{
		sub_6FB5BA70(pUnit, iVar7, 2, 0, 0, 0, 0, 0);
		uVar3 = extraout_EDX_08;
	}
	if (local_24 != 0)
	{
		sVar11 = *(short*)(iVar10 + 0xe8);
		iVar10 = CONCAT22((short)((uint32_t)local_24 >> 0x10), sVar11);
		if (0 < sVar11)
		{
			iVar7 = (int)sVar11;
			if ((iVar7 < 0) || (uVar3 = *(uint32_t*)((uint8_t*)&sgptDataTables), *(int*)(uVar3 + 0xb6c) <= iVar7))
			{
				iVar5 = 0;
			}
			else
			{
				iVar10 = iVar7 * 0x69;
				iVar5 = *(int*)(uVar3 + 0xb64) + iVar7 * 0x1a4;
				iVar7 = *(int*)(uVar3 + 0xb64);
			}
			if (*(char*)(iVar5 + 0x130) != '\0')
			{
				a2 = sub_6FAA4280(pUnit, 1, 1, 0xff,
				    CONCAT31((int32_t)((uint32_t)iVar7 >> 8), *(uint8_t*)(iVar5 + 0x132)),
				    CONCAT31((int32_t)((uint32_t)iVar10 >> 8), *(uint8_t*)(iVar5 + 0x133)),
				    D2C_ZEXT(*(uint8_t*)(iVar5 + 0x134)));
				sub_6FAA43A0((int)a2, (uint32_t) * (uint8_t*)(iVar5 + 0x130));
				pvVar6 = D2Common_10958(pUnit, a2);
				if (pvVar6 != nullptr)
				{
					sub_6FAA44D0((int)pvVar6);
				}
			}
		}
	}
	return local_24;
}

//D2Client.0x6FABC6B0
uint32_t __fastcall sub_6FABC6B0(D2UnitStrc* pUnit, int a2, int a3, int a4)
{
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	int32_t DVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	int32_t DVar6;
	uint32_t* puVar7;
	void* pvVar8;
	int iVar9;
	int iVar10;
	int32_t DVar11;
	bool bVar12;
	int local_18;
	int local_8;
	int32_t DStack_4;

	(*(uint16_t*)((uint8_t*)&DVar11 + 0)) = 0;
	(*(uint16_t*)((uint8_t*)&DVar11 + 2)) = 0;
	if (a2 < 0)
	{
		return 0;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)
	{
		return 0;
	}
	iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c;
	if (iVar9 == 0)
	{
		return 0;
	}
	if (*(short*)(iVar9 + 0xf4) < 0)
	{
		return 0;
	}
	if (dword_6FB777B0 <= *(short*)(iVar9 + 0xf4))
	{
		return 0;
	}
	bVar12 = false;
	if (0 < *(short*)(iVar9 + 0xe8))
	{
		iVar10 = 0;
		local_18 = 0;
		iVar5 = 0;
		if (a4 != 0)
		{
			pDVar3 = sub_6FB296A0((int)pUnit);
			if (pDVar3 == nullptr)
			{
				pDynamicPath = pUnit->pDynamicPath;
				iVar4 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
				local_8 = iVar4;
				DStack_4 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
			}
			else
			{
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
				}
				uVar1 = pDVar3->dwUnitType;
				local_8 = iVar4;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DStack_4 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_4 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_4 + 2)) = 0;
				}
				else
				{
					DStack_4 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
				}
			}
			if ((iVar4 == 0) || (DStack_4 == (int32_t)0x0))
			{
				sub_6FABA860(pUnit, &local_8, &DStack_4);
				iVar4 = local_8;
			}
			DVar2 = DStack_4;
			DVar11 = DStack_4;
			iVar5 = iVar4;
			if ((iVar4 != 0) && (DStack_4 != (int32_t)0x0))
			{
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
				iVar5 = iVar4 - iVar5;
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
				DVar11 = (int32_t)((int)DVar2 - (int)DVar6);
				iVar10 = iVar4 + iVar5;
				local_18 = (int)DVar2 + (int)DVar11;
			}
		}
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar9 + 4)) == 0)
		{
			puVar7 = sub_6FABAFC0((int)*(short*)(iVar9 + 0xe8), pUnit, a2, a3, iVar5, (int)DVar11,
			    iVar10, local_18);
		}
		else
		{
			puVar7 = sub_6FB3EBE0(pUnit, (int)*(short*)(iVar9 + 0xe8), iVar5, (int)DVar11, iVar10, local_18,
			    a2, a3, 0);
		}
		bVar12 = puVar7 != nullptr;
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
	}
	iVar5 = (int)*(short*)(iVar9 + 0xf4);
	if ((a4 != 0) && (1 < *(short*)(iVar9 + 0x16c)))
	{
		iVar5 = (int)*(short*)(iVar9 + 0x16c);
	}
	if (((iVar5 < 0) || (dword_6FB777B0 <= iVar5)) ||
	    (*(code**)(byte_6FB775A8 + iVar5 * 4) == nullptr))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
	}
	else
	{
		iVar5 = (**(code**)(byte_6FB775A8 + iVar5 * 4))(a3);
		if (iVar5 == 0)
			goto LAB_6fabc92b;
	}
	bVar12 = true;
LAB_6fabc92b:
	pvVar8 = D2Common_10958(pUnit, nullptr);
	if (pvVar8 != nullptr)
	{
		sub_6FAA44D0((int)pvVar8);
	}
	if (!bVar12)
	{
		return 0;
	}
	if (0 < *(short*)(iVar9 + 0x100))
	{
		sub_6FB55820((int)*(short*)(iVar9 + 0x100), pUnit, 0.0, 0.0, 0);
	}
	if ((0 < *(short*)(iVar9 + 0x10a)) &&
	    (pDVar3 = sub_6FB296A0((int)pUnit), pDVar3 != nullptr))
	{
		sub_6FB55820((int)*(short*)(iVar9 + 0x10a), pDVar3, 0.0, 0.0, 0);
	}
	if ((0 < *(short*)(iVar9 + 0x108)) &&
	    (pDVar3 = sub_6FB296A0((int)pUnit), pDVar3 != nullptr))
	{
		sub_6FB5BA70(pDVar3, (int)*(short*)(iVar9 + 0x108), 2, 0, 0, 0, 0, 0);
	}
	iVar5 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 400), a2, a3);
	if ((0 < iVar5) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 == pUnit))
	{
		if (0xc < iVar5)
		{
			iVar5 = 0xc;
		}
		if ((*(char*)(iVar9 + 0x10) != '\x12') || ((pUnit->dwSeqFrame & 0xffffff00U) == 0))
		{
			iVar9 = sub_6FAABF80();
			sub_6FAA9AB0(iVar9 + iVar5);
		}
	}
	return 1;
}

//D2Client.0x6FABCA30
void __fastcall sub_6FABCA30(D2UnitStrc* pUnit)
{
	D2SkillStrc* pSkill;
	int iVar1;
	int iVar2;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return;
	}
	iVar1 = SKILLS_GetSkillIdFromSkill(pSkill, (const char*)(dword_6FB777BB + 1), 0x697);
	iVar2 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
	sub_6FABC6B0(pUnit, iVar1, iVar2, 0);
}

//D2Client.0x6FABCA70
void __fastcall sub_6FABCA70(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3, uint32_t a4, int a5, int a6, uint32_t a7)
{
	int iVar1;
	short sVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	D2DynamicPathStrc* pDynamicPath;
	uint8_t bVar5;
	D2UnitStrc* pDVar6;
	int32_t nY;
	int32_t DVar7;
	int iVar8;
	D2UnitStrc* pDVar9;
	int local_54;
	int aiStack_40[16];

	if (pUnit == nullptr)
	{
		return;
	}
	if (a3 < 0)
	{
		return;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a3)
	{
		return;
	}
	iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a3 * 0x23c;
	if (iVar1 == 0)
	{
		return;
	}
	uVar3 = pUnit->dwInitSeed;
	pDVar6 = sub_6FB296A0((int)pUnit);
	if (pDVar6 == nullptr)
	{
		pDynamicPath = pUnit->pDynamicPath;
		local_54 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
		nY = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
	}
	else
	{
		uVar4 = pDVar6->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			local_54 = pDVar6->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar6->pDynamicPath == nullptr)
		{
			local_54 = 0;
		}
		else
		{
			local_54 = PATH_GetXPosition(pDVar6->pDynamicPath);
		}
		uVar4 = pDVar6->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			nY = (*(int32_t*)&pDVar6->pDynamicPath->tTargetCoord);
		}
		else if (pDVar6->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
		}
		else
		{
			nY = (int32_t)PATH_GetYPosition(pDVar6->pDynamicPath);
		}
	}
	if ((local_54 == 0) || (nY == (int32_t)0x0))
	{
		bVar5 = UNITS_GetDirection(pUnit);
		aiStack_40[5] = 1;
		aiStack_40[7] = 1;
		aiStack_40[9] = 1;
		aiStack_40[0xf] = 1;
		uVar4 = pUnit->dwUnitType;
		aiStack_40[0] = 0;
		aiStack_40[1] = 0xffffffff;
		aiStack_40[2] = 0xfffffffe;
		aiStack_40[3] = 0xffffffff;
		aiStack_40[4] = 0;
		aiStack_40[6] = 2;
		aiStack_40[8] = 2;
		aiStack_40[10] = 0;
		aiStack_40[0xb] = 0xffffffff;
		aiStack_40[0xc] = 0xfffffffe;
		aiStack_40[0xd] = 0xffffffff;
		aiStack_40[0xe] = 0;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			local_54 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			local_54 = 0;
		}
		else
		{
			local_54 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		local_54 = aiStack_40[bVar5 >> 3] + local_54;
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
		}
		else
		{
			DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		nY = (int32_t)(aiStack_40[(bVar5 >> 3) + 8] + (int)DVar7);
	}
	pDVar6 = sub_6FB296A0((int)pUnit);
	if (pUnit2 == nullptr)
	{
		if (a5 == 0)
			goto LAB_6fabcc75;
		if (a6 != 0)
		{
			D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, a5, a6);
			pUnit->dwInitSeed = a7 & 0xff;
		}
	}
	else
	{
		UNITS_SetTargetUnitForDynamicUnit(pUnit, pUnit2);
		pUnit->dwInitSeed = a7 & 0xff;
	}
	if ((a5 != 0) && (a6 == 0))
	{
		pUnit->dwInitSeed = a5;
	}
LAB_6fabcc75:
	sVar2 = *(short*)(iVar1 + 0xf6);
	if ((((-1 < sVar2) && (sVar2 < dword_6FB777B0)) &&
	        (*(code**)(byte_6FB775A8 + sVar2 * 4) != nullptr)) &&
	    (iVar8 = (**(code**)(byte_6FB775A8 + sVar2 * 4))(a4), iVar8 != 0))
	{
		if (0 < *(short*)(iVar1 + 0x100))
		{
			sub_6FB55820((int)*(short*)(iVar1 + 0x100), pUnit, 0.0, 0.0, 0);
		}
		if ((0 < *(short*)(iVar1 + 0x10a)) &&
		    (pDVar9 = sub_6FB296A0((int)pUnit), pDVar9 != nullptr))
		{
			sub_6FB55820((int)*(short*)(iVar1 + 0x10a), pDVar9, 0.0, 0.0, 0);
		}
		if ((0 < *(short*)(iVar1 + 0x108)) &&
		    (pDVar9 = sub_6FB296A0((int)pUnit), pDVar9 != nullptr))
		{
			sub_6FB5BA70(pDVar9, (int)*(short*)(iVar1 + 0x108), 2, 0, 0, 0, 0, 0);
		}
	}
	UNITS_SetTargetUnitForDynamicUnit(pUnit, pDVar6);
	if (pDVar6 == nullptr)
	{
		D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, local_54, (int)nY);
	}
	pUnit->dwInitSeed = uVar3;
}

//D2Client.0x6FABCD70
void __fastcall sub_6FABCD70(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3, int a4, int a5, int a6, int a7)
{
	int iVar1;
	short sVar2;
	uint32_t uVar3;
	D2DynamicPathStrc* pDVar4;
	D2StatListStrc* pStatList;
	D2UnitStrc* pDVar5;
	int iVar6;
	int32_t DVar7;
	int32_t DVar8;
	short* psVar9;
	int iVar10;
	int32_t DStack_18;
	int iStack_14;
	int32_t DStack_10;
	int32_t local_c;
	D2UnitStrc* pDStack_8;
	uint32_t uStack_4;

	if (((((pUnit != nullptr) && (-1 < a3)) &&
	         (iVar6 = *(int*)((uint8_t*)&sgptDataTables), a3 < *(int*)(iVar6 + 0xba0))) &&
	        ((iVar1 = *(int*)(iVar6 + 0xb98) + a3 * 0x23c, iVar1 != 0 &&
	                                                           (sVar2 = *(short*)(iVar1 + 0x80), -1 < sVar2)))) &&
	    (((int)sVar2 < *(int*)(iVar6 + 0xc4) &&
	        ((-1 < *(short*)(iVar1 + 0x54) && ((int)*(short*)(iVar1 + 0x54) < *(int*)(iVar6 + 0xbd4)))))))
	{
		local_c = (int32_t)pUnit2;
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, (int)sVar2);
		if (pStatList == nullptr)
		{
			pStatList = STATLIST_AllocStatList(nullptr, 0, 0, pUnit->dwUnitType, pUnit->dwUnitId);
			if (pStatList == nullptr)
			{
				return;
			}
			STATLIST_SetState(pStatList, (int)*(short*)(iVar1 + 0x80));
			D2COMMON_10475_PostStatToStatList(pUnit, pStatList, 1);
			STATLIST_SetStatIfListIsValid(pStatList, (int)*(short*)(iVar1 + 0x54), a7, 0);
		}
		pDVar5 = sub_6FB296A0((int)pUnit);
		if (pDVar5 == nullptr)
		{
			pDVar4 = pUnit->pDynamicPath;
			iStack_14 = D2COMMON_10175_PathGetFirstPointX(pDVar4);
			DStack_18 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDVar4);
		}
		else
		{
			uVar3 = pDVar5->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				iStack_14 = pDVar5->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar5->pDynamicPath == nullptr)
			{
				iStack_14 = 0;
			}
			else
			{
				iStack_14 = PATH_GetXPosition(pDVar5->pDynamicPath);
			}
			uVar3 = pDVar5->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_18 = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
			}
			else if (pDVar5->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0;
			}
			else
			{
				DStack_18 = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
			}
		}
		if ((iStack_14 == 0) || (DStack_18 == (int32_t)0x0))
		{
			sub_6FABA860(pUnit, &iStack_14, &DStack_18);
		}
		pDStack_8 = sub_6FB296A0((int)pUnit);
		if (local_c == (int32_t)0x0)
		{
			if ((a5 != 0) && (a6 != 0))
			{
				D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, a5, a6);
			}
		}
		else
		{
			UNITS_SetTargetUnitForDynamicUnit(pUnit, (D2UnitStrc*)local_c);
		}
		uStack_4 = pUnit->dwInitSeed;
		if ((a5 != 0) && (a6 == 0))
		{
			pUnit->dwInitSeed = a5;
		}
		iVar6 = a7 + -1;
		if ((*(uint8_t*)(iVar1 + 4) & (uint8_t)((uint8_t*)&gdwBitMasks)[0x1c]) != 0)
		{
			iVar10 = 0;
			if (0 < iVar6)
			{
				psVar9 = (short*)(iVar1 + 0xf6);
				do
				{
					if (*(int*)(byte_6FB775A8 + *psVar9 * 4) != 0)
					{
						STATLIST_SetStatIfListIsValid(pStatList, (int)*(short*)(iVar1 + 0x54), iVar10 + 1, 0);
						(**(code**)(byte_6FB775A8 + *psVar9 * 4))(a4);
					}
					iVar10 = iVar10 + 1;
					psVar9 = psVar9 + 1;
				} while (iVar10 < iVar6);
			}
			STATLIST_SetStatIfListIsValid(pStatList, (int)*(short*)(iVar1 + 0x54), a7, 0);
		}
		sVar2 = *(short*)(iVar1 + 0xf6 + iVar6 * 2);
		if ((-1 < sVar2) && (sVar2 < dword_6FB777B0))
		{
			sVar2 = *(short*)(iVar1 + 0xe8);
			if (0 < sVar2)
			{
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar1 + 4)) == 0)
				{
					pDVar5 = sub_6FB296A0((int)pUnit);
					if (pDVar5 == nullptr)
					{
						pDVar4 = pUnit->pDynamicPath;
						DVar8 = (int32_t)D2COMMON_10175_PathGetFirstPointX(pDVar4);
						DStack_10 = DVar8;
						local_c = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDVar4);
					}
					else
					{
						uVar3 = pDVar5->dwUnitType;
						if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
						{
							DVar8 = (int32_t)pDVar5->pDynamicPath->dwClientCoordY;
						}
						else if (pDVar5->pDynamicPath == nullptr)
						{
							(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
							(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
						}
						else
						{
							DVar8 = (int32_t)PATH_GetXPosition(pDVar5->pDynamicPath);
						}
						uVar3 = pDVar5->dwUnitType;
						DStack_10 = DVar8;
						if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
						{
							local_c = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
						}
						else if (pDVar5->pDynamicPath == nullptr)
						{
							(*(uint16_t*)((uint8_t*)&local_c + 0)) = 0;
							(*(uint16_t*)((uint8_t*)&local_c + 2)) = 0;
						}
						else
						{
							local_c = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
						}
					}
					if ((DVar8 == (int32_t)0x0) || (local_c == (int32_t)0x0))
					{
						sub_6FABA860(pUnit, (int*)&DStack_10, &local_c);
						DVar8 = DStack_10;
					}
					if ((DVar8 != (int32_t)0x0) && (local_c != (int32_t)0x0))
					{
						sub_6FB3EB50(pUnit, (int)sVar2, DVar8, (D2UnitStrc*)local_c, a3, a4);
					}
				}
				else
				{
					pDVar5 = sub_6FB296A0((int)pUnit);
					if (pDVar5 == nullptr)
					{
						pDVar4 = pUnit->pDynamicPath;
						DVar7 = (int32_t)D2COMMON_10175_PathGetFirstPointX(pDVar4);
						local_c = DVar7;
						DStack_10 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDVar4);
					}
					else
					{
						uVar3 = pDVar5->dwUnitType;
						if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
						{
							DVar7 = (int32_t)pDVar5->pDynamicPath->dwClientCoordY;
						}
						else if (pDVar5->pDynamicPath == nullptr)
						{
							(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
							(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
						}
						else
						{
							DVar7 = (int32_t)PATH_GetXPosition(pDVar5->pDynamicPath);
						}
						uVar3 = pDVar5->dwUnitType;
						local_c = DVar7;
						if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
						{
							DStack_10 = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
						}
						else if (pDVar5->pDynamicPath == nullptr)
						{
							(*(uint16_t*)((uint8_t*)&DStack_10 + 0)) = 0;
							(*(uint16_t*)((uint8_t*)&DStack_10 + 2)) = 0;
						}
						else
						{
							DStack_10 = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
						}
					}
					if ((DVar7 == (int32_t)0x0) || (DStack_10 == (int32_t)0x0))
					{
						sub_6FABA860(pUnit, (int*)&local_c, &DStack_10);
						DVar7 = local_c;
					}
					sub_6FB3EBE0(pUnit, (int)*(short*)(iVar1 + 0xe8), 0, 0, (int)DVar7, (int)DStack_10, a3,
					    a4, 0);
				}
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			if (*(code**)(byte_6FB775A8 + *(short*)(iVar1 + 0xf6 + iVar6 * 2) * 4) == nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			else
			{
				iVar6 = (**(code**)(byte_6FB775A8 + *(short*)(iVar1 + 0xf6 + iVar6 * 2) * 4))(a4);
				if (iVar6 != 0)
				{
					if (0 < *(short*)(iVar1 + 0x100))
					{
						sub_6FB55820((int)*(short*)(iVar1 + 0x100), pUnit, 0.0, 0.0, 0);
					}
					if ((0 < *(short*)(iVar1 + 0x10a)) &&
					    (pDVar5 = sub_6FB296A0((int)pUnit), pDVar5 != nullptr))
					{
						sub_6FB55820((int)*(short*)(iVar1 + 0x10a), pDVar5, 0.0, 0.0, 0);
					}
					if ((0 < *(short*)(iVar1 + 0x108)) &&
					    (pDVar5 = sub_6FB296A0((int)pUnit), pDVar5 != nullptr))
					{
						sub_6FB5BA70(pDVar5, (int)*(short*)(iVar1 + 0x108), 2, 0, 0, 0, 0, 0);
					}
				}
			}
		}
		UNITS_SetTargetUnitForDynamicUnit(pUnit, pDStack_8);
		D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iStack_14, (int)DStack_18);
		if ((a5 != 0) && (a6 == 0))
		{
			pUnit->dwInitSeed = uStack_4;
		}
	}
}

//D2Client.0x6FABD2A0
int __fastcall sub_6FABD2A0(D2UnitStrc* pUnit, uint32_t* a2)
{
	int iVar1;
	D2UnitStrc* pTargetUnit;

	iVar1 = UNITS_CanDualWield(pUnit);
	if ((iVar1 != 0) && ((pUnit == nullptr || (pUnit->dwUnitType != 1))))
	{
		sub_6FABD330(pUnit, (int*)a2);
	}
	pTargetUnit = sub_6FB269F0(a2[3], a2[2]);
	if (pTargetUnit != nullptr)
	{
		UNITS_SetTargetUnitForDynamicUnit(pUnit, pTargetUnit);
		sub_6FB29010(pUnit, 0);
		iVar1 = sub_6FABBED0(pUnit, *a2, (int*)a2[1], a2[4]);
		return iVar1;
	}
	sub_6FB4EE00(7, pUnit, nullptr, 0);
	LOG_11100(1, 2, 4, 0x40, (const char*)(dword_6FB777BB + 1), 0x7c2,
	    "StartsStartSkillID - Invalid Target");
	return 0;
}

//D2Client.0x6FABD330
void __fastcall sub_6FABD330(D2UnitStrc* pUnit, int* a2)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pItem;
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pItem_00;
	D2SkillStrc* pDVar3;

	if (*a2 != 0)
	{
		return;
	}
	pInventory = pUnit->pInventory;
	pItem = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
	if ((pItem != nullptr) &&
	    ((iVar1 = ITEMS_CanBeEquipped(pItem), iVar1 == 0 ||
	                                              (uVar2 = ITEMS_GetItemType(pItem), uVar2 == 0x26))))
	{
		pItem = nullptr;
	}
	pItem_00 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
	if ((pItem_00 != nullptr) &&
	    ((iVar1 = ITEMS_CanBeEquipped(pItem_00), iVar1 == 0 ||
	                                                 (uVar2 = ITEMS_GetItemType(pItem_00), uVar2 == 0x26))))
	{
		pItem_00 = nullptr;
	}
	iVar1 = ITEMS_CheckItemTypeId(pItem, 0x2d);
	if ((iVar1 != 0) && (iVar1 = ITEMS_CheckItemTypeId(pItem_00, 0x2d), iVar1 != 0))
	{
		pDVar3 = SKILLS_GetSkillById(pUnit, 0, 0xffffffff);
		iVar1 = SKILLS_GetParam4(pDVar3);
		if (iVar1 == 0)
		{
			*a2 = 5;
			SKILLS_SetParam4(pDVar3, 5);
			pDVar3 = SKILLS_GetSkillById(pUnit, 5, 0xffffffff);
			UNITS_SetUsedSkill(pUnit, pDVar3);
			return;
		}
		SKILLS_SetParam4(pDVar3, 0);
		UNITS_SetUsedSkill(pUnit, pDVar3);
	}
}

//D2Client.0x6FABD400
int32_t __fastcall sub_6FABD400(D2UnitStrc* pUnit, int* a2)
{
	int iVar1;
	int nY;
	uint8_t bVar2;
	int iVar3;

	iVar1 = a2[2];
	nY = a2[3];
	iVar3 = UNITS_CanDualWield(pUnit);
	if (iVar3 != 0)
	{
		sub_6FABD330(pUnit, a2);
	}
	D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iVar1, nY);
	UNITS_UpdateDirectionAndSpeed(pUnit, iVar1, nY);
	if ((((pUnit->dwUnitType == 1) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar1 * 0x1a8, iVar1 != 0 &&
	                                                                                       (*(int*)(iVar1 + 0x10) == 0x20204250))))
	{
		bVar2 = PATH_GetNewDirection(pUnit->pDynamicPath);
		D2COMMON_10160_PathUpdateDirection(pUnit->pDynamicPath, bVar2 + 0x38 & 0x3f);
	}
	UNITS_SetTargetUnitForDynamicUnit(pUnit, nullptr);
	return sub_6FABBED0(pUnit, *a2, (int*)a2[1], a2[4]);
}

//D2Client.0x6FABD4D0
void __fastcall sub_6FABD4D0(D2UnitStrc* pUnit, int* a2, uint32_t a3, int a4, uint32_t a5, uint32_t a6, int a7)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t* puVar3;
	uint32_t* puVar4;
	uint32_t local_b8;
	D2UnitStrc* pDStack_b4;
	uint32_t uStack_a8;
	int local_a4;
	int iStack_a0;
	int iStack_90;
	uint32_t uStack_8c;
	uint32_t uStack_88;
	uint32_t auStack_5c[4];
	int iStack_4c;

	puVar2 = &local_b8;
	for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	iVar1 = *a2;
	local_b8 = 3;
	if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
	{
		local_a4 = *(int*)(a2[0xb] + 0xc);
	}
	else if ((D2DynamicPathStrc*)a2[0xb] == nullptr)
	{
		local_a4 = 0;
	}
	else
	{
		local_a4 = PATH_GetXPosition((D2DynamicPathStrc*)a2[0xb]);
	}
	iVar1 = *a2;
	if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
	{
		iStack_a0 = *(int*)(a2[0xb] + 0x10);
	}
	else if ((D2DynamicPathStrc*)a2[0xb] == nullptr)
	{
		iStack_a0 = 0;
	}
	else
	{
		iStack_a0 = PATH_GetYPosition((D2DynamicPathStrc*)a2[0xb]);
	}
	uStack_8c = a5;
	pDStack_b4 = pUnit;
	uStack_a8 = a3;
	uStack_88 = a6;
	if (a7 != 0)
	{
		iStack_90 = a7;
		local_b8 = local_b8 | 4;
	}
	if (a4 == -1)
	{
		puVar2 = nullptr;
	}
	else
	{
		puVar2 = auStack_5c;
		puVar3 = &local_b8;
		puVar4 = auStack_5c;
		for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar4 = *puVar3;
			puVar3 = puVar3 + 1;
			puVar4 = puVar4 + 1;
		}
		iStack_4c = a4;
	}
	sub_6FABD5D0(&local_b8, puVar2);
}

//D2Client.0x6FABD5D0
void __fastcall sub_6FABD5D0(uint32_t* a1, uint32_t* a2)
{
	uint64_t uVar1;
	uint64_t* puVar2;
	uint32_t* puVar3;
	int iVar4;

	iVar4 = 0;
	if (a2 == nullptr)
	{
		do
		{
			a1[7] = *(uint32_t*)((int)&dword_6FB6E2E0 + iVar4);
			a1[8] = *(uint32_t*)((int)&dword_6FB6E3E0 + iVar4);
			if (a1[4] == 0xb0)
			{
				*a1 = *a1 ^ 0x4000;
			}
			sub_6FB3E070(a1);
			iVar4 = iVar4 + 4;
		} while (iVar4 < 0x100);
		return;
	}
	do
	{
		puVar2 = (uint64_t*)(a1[1] + 0x20);
		uVar1 = (uint64_t) * (uint32_t*)puVar2 * 0x6ac690c5 + (uint64_t) * (uint32_t*)(a1[1] + 0x24);
		*puVar2 = uVar1;
		if ((int)((uVar1 & 0xffffffff) % 6) == 0)
		{
			a2[7] = *(uint32_t*)((int)&dword_6FB6E2E0 + iVar4);
			a2[8] = *(uint32_t*)((int)&dword_6FB6E3E0 + iVar4);
			puVar3 = a2;
		}
		else
		{
			a1[7] = *(uint32_t*)((int)&dword_6FB6E2E0 + iVar4);
			a1[8] = *(uint32_t*)((int)&dword_6FB6E3E0 + iVar4);
			puVar3 = a1;
		}
		sub_6FB3E070(puVar3);
		iVar4 = iVar4 + 4;
	} while (iVar4 < 0x100);
}

//D2Client.0x6FABD690
void __fastcall sub_6FABD690(int a1, uint32_t* a2)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar2 = a1 + -1;
	D2_ASSERT(7 >= iVar2 / 5);
	a2[7] = 0xe;
	a2[8] = 0xfffffff2;
	sub_6FB3E070(a2);
	iVar1 = 0;
	do
	{
		if (iVar2 == 0)
		{
			return;
		}
		iVar3 = 0;
		do
		{
			if (iVar2 < 1)
				break;
			a2[7] = *(int*)((int)&dword_6FB6E4E0 + iVar3) * *(int*)((int)&dword_6FB6E500 + iVar1);
			a2[8] = *(int*)((int)&dword_6FB6E4F0 + iVar3) * *(int*)((int)&dword_6FB6E51C + iVar1);
			sub_6FB3E070(a2);
			a2[7] = *(int*)((int)&dword_6FB6E4E0 + iVar3) * *(int*)((int)&dword_6FB6E51C + iVar1);
			a2[8] = *(int*)((int)&dword_6FB6E4F0 + iVar3) * *(int*)((int)&dword_6FB6E500 + iVar1);
			sub_6FB3E070(a2);
			iVar3 = iVar3 + 4;
			iVar2 = iVar2 + -2;
		} while (iVar3 < 0x10);
		a2[7] = *(uint32_t*)((int)dword_6FB6E538 + iVar1);
		a2[8] = *(uint32_t*)((int)dword_6FB6E558 + iVar1);
		sub_6FB3E070(a2);
		iVar1 = iVar1 + 4;
		iVar2 = iVar2 + -1;
		if (0x1b < iVar1)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FABD780
void __fastcall sub_6FABD780(D2UnitStrc* pUnit)
{
	short sVar1;
	int iVar2;
	D2StatListStrc* pStatList;
	int iVar3;
	int nState;
	int iStack_4;

	iVar2 = STATES_CheckStateMaskActiveOnUnit(pUnit);
	if (iVar2 != 0)
	{
		iStack_4 = 0;
		iVar2 = *(int*)((uint8_t*)&sgptDataTables);
		if (0 < *(short*)(iVar2 + 0x188))
		{
			do
			{
				nState = (int)*(short*)(*(int*)(iVar2 + 0x184) + iStack_4 * 2);
				iVar2 = STATES_CheckState(pUnit, nState);
				if ((((iVar2 != 0) && (-1 < nState)) &&
				        (nState < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
				    (((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + nState * 0x3c, iVar2 != 0 &&
				                                                                                       (sVar1 = *(short*)(iVar2 + 0x34), -1 < sVar1)) &&
				        ((sVar1 < dword_6FB777B0 && (*(int*)(byte_6FB775A8 + sVar1 * 4) != 0))))))
				{
					iVar3 = 1;
					pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, nState);
					if (pStatList != nullptr)
					{
						STATLIST_GetStatValue(pStatList, 0x15e, 0);
						iVar3 = STATLIST_GetStatValue(pStatList, 0x15f, 0);
					}
					(**(code**)(byte_6FB775A8 + *(short*)(iVar2 + 0x34) * 4))(iVar3);
				}
				iStack_4 = iStack_4 + 1;
				iVar2 = *(int*)((uint8_t*)&sgptDataTables);
			} while (iStack_4 < *(short*)(iVar2 + 0x188));
		}
	}
}

//D2Client.0x6FABD8A0
void __fastcall sub_6FABD8A0(int a1, uint32_t* a2, int a3, int a4)
{
	uint32_t uVar1;
	uint32_t uVar2;
	int64_t lVar3;
	uint64_t uVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	int local_14;
	int local_c;

	lVar3 = (uint64_t) * (uint32_t*)(a1 + 0x20) * 0x6ac690c5 + (uint64_t) * (uint32_t*)(a1 + 0x24);
	uVar6 = (uint32_t)lVar3 & 3;
	*(int64_t*)(a1 + 0x20) = lVar3;
	uVar1 = a2[5];
	uVar2 = a2[6];
	if (0 < a4)
	{
		local_c = a4;
		uVar5 = a3 * 2;
		do
		{
			switch (uVar6)
			{
			case 0:
				a4 = -0x10;
				local_14 = a4;
				break;
			case 1:
				a4 = -0x10;
				local_14 = 0x10;
				break;
			case 2:
				a4 = 0x10;
				local_14 = a4;
				break;
			case 3:
				a4 = 0x10;
				local_14 = -0x10;
				break;
			default:
				a4 = 0;
				local_14 = a4;
			}
			uVar6 = uVar6 + 1 & 0x80000003;
			if ((int)uVar6 < 0)
			{
				uVar6 = (uVar6 - 1 | 0xfffffffc) + 1;
			}
			if ((int)uVar5 < 1)
			{
				uVar7 = 0;
			}
			else if ((uVar5 & uVar5 - 1) == 0)
			{
				lVar3 = (uint64_t) * (uint32_t*)(a1 + 0x20) * 0x6ac690c5 +
				        (uint64_t) * (uint32_t*)(a1 + 0x24);
				*(int64_t*)(a1 + 0x20) = lVar3;
				uVar7 = uVar5 - 1 & (uint32_t)lVar3;
			}
			else
			{
				uVar4 = (uint64_t) * (uint32_t*)(a1 + 0x20) * 0x6ac690c5 +
				        (uint64_t) * (uint32_t*)(a1 + 0x24);
				*(uint64_t*)(a1 + 0x20) = uVar4;
				uVar7 = (uint32_t)((uVar4 & 0xffffffff) % (uint64_t)uVar5);
			}
			a2[5] = (uVar7 - a3) + uVar1;
			if ((int)uVar5 < 1)
			{
				uVar7 = 0;
			}
			else if ((uVar5 & uVar5 - 1) == 0)
			{
				lVar3 = (uint64_t) * (uint32_t*)(a1 + 0x20) * 0x6ac690c5 +
				        (uint64_t) * (uint32_t*)(a1 + 0x24);
				*(int64_t*)(a1 + 0x20) = lVar3;
				uVar7 = uVar5 - 1 & (uint32_t)lVar3;
			}
			else
			{
				uVar4 = (uint64_t) * (uint32_t*)(a1 + 0x20) * 0x6ac690c5 +
				        (uint64_t) * (uint32_t*)(a1 + 0x24);
				*(uint64_t*)(a1 + 0x20) = uVar4;
				uVar7 = (uint32_t)((uVar4 & 0xffffffff) % (uint64_t)uVar5);
			}
			uVar7 = uVar2 + (uVar7 - a3);
			a2[6] = uVar7;
			a2[8] = uVar7 + local_14;
			a2[7] = a2[5] + a4;
			a2[0x15] = (uint32_t)sub_6FABDA50;
			a2[0x16] = uVar6 << 4;
			sub_6FB3E070(a2);
			local_c = local_c + -1;
		} while (local_c != 0);
	}
}

//D2Client.0x6FABDA50
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FABDA50()
{
	int in_ECX;
	uint8_t in_DL;

	PATH_SetDirection(*(D2DynamicPathStrc**)(in_ECX + 0x2c), in_DL);
}

//D2Client.0x6FABDA60
uint32_t __fastcall sub_6FABDA60(D2UnitStrc* pUnit, uint32_t* a2)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_1c[4];
	uint32_t local_c;

	puVar2 = local_1c;
	for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	local_1c[0] = 0;
	local_1c[1] = 0xffffffff;
	local_1c[2] = 6;
	if (a2 == nullptr)
	{
		local_1c[3] = 0xffffffff;
	}
	else
	{
		local_1c[2] = *a2;
		local_1c[3] = a2[3];
	}
	local_c = 1;
	sub_6FB4EE00(0x16, pUnit, local_1c, 1);
	return 1;
}

//D2Client.0x6FABDAD0
void __fastcall sub_6FABDAD0(int a1, int a2)
{
	*(int*)(a1 + 0x44) = (((100 - a2) * (*(int*)(a1 + 0x44) >> 8)) / 100) * 0x100;
}

//D2Client.0x6FABDB00
uint32_t __fastcall sub_6FABDB00(D2UnitStrc* pUnit, uint32_t a2, int a3, int a4, uint32_t a5, uint32_t a6)
{
	D2SeedStrc* pSeed;
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar2;
	uint64_t DVar3;
	D2UnitStrc* pDVar4;
	uint32_t uVar5;
	int iVar6;
	int nY2;
	int local_14;
	D2UnitStrc** local_10;
	int iStack_c;
	int iStack_8;
	uint32_t local_4;

	local_4 = a2;
	pDVar4 = sub_6FB296A0((int)pUnit);
	if (pDVar4 == nullptr)
	{
		pDynamicPath = pUnit->pDynamicPath;
		local_14 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
		local_10 = (D2UnitStrc**)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
	}
	else
	{
		uVar1 = pDVar4->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			local_14 = pDVar4->pDynamicPath->dwClientCoordY;
			local_10 = sub_6FAB6A90((int*)pDVar4);
		}
		else if (pDVar4->pDynamicPath == nullptr)
		{
			local_14 = 0;
			local_10 = sub_6FAB6A90((int*)pDVar4);
		}
		else
		{
			local_14 = PATH_GetXPosition(pDVar4->pDynamicPath);
			local_10 = sub_6FAB6A90((int*)pDVar4);
		}
	}
	if ((local_14 == 0) || (local_10 == nullptr))
	{
		sub_6FABA860(pUnit, &local_14, (int*)(&local_10));
	}
	pSeed = &pUnit->pSeed;
	SEED_InitLowSeed(pSeed, local_14);
	if (0 < a3)
	{
		iStack_8 = a3;
		uVar1 = a4 * 2;
		do
		{
			if ((int)uVar1 < 1)
			{
				uVar5 = 0;
			}
			else if ((uVar1 & uVar1 - 1) == 0)
			{
				uVar5 = sub_6FAA88D0(&pSeed->nLowSeed);
				uVar5 = uVar5 & uVar1 - 1;
			}
			else
			{
				DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pSeed = DVar3;
				uVar5 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
			}
			iStack_c = (uVar5 - a4) + local_14;
			if ((int)uVar1 < 1)
			{
				uVar5 = 0;
			}
			else if ((uVar1 & uVar1 - 1) == 0)
			{
				DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pSeed = DVar3;
				uVar5 = uVar1 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
			}
			else
			{
				DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pSeed = DVar3;
				uVar5 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
			}
			uVar2 = pUnit->dwUnitType;
			nY2 = (uVar5 - a4) + (int)local_10;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				a3 = *(int*)&pUnit->pDynamicPath->tTargetCoord;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				a3 = 0;
			}
			else
			{
				a3 = PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				iVar6 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			iVar6 = PATH_ComputeSquaredDistance(iVar6, a3, iStack_c, nY2);
			if (3 < iVar6)
			{
				sub_6FB3EBE0(pUnit, local_4, 0, 0, iStack_c, nY2, a5, a6, 0);
			}
			iStack_8 = iStack_8 + -1;
		} while (iStack_8 != 0);
	}
	return 1;
}

//D2Client.0x6FABDD20
void __fastcall sub_6FABDD20(D2UnitStrc* pUnit)
{
	uint32_t nUnitType;
	D2StatListStrc* pStatList;
	uint32_t nUnitGUID;
	D2StatListStrc* pStatList_00;
	void* pfStatRemove;

	if (pUnit == nullptr)
	{
		nUnitGUID = 0xffffffff;
		nUnitType = 6;
	}
	else
	{
		nUnitGUID = pUnit->dwUnitId;
		nUnitType = pUnit->dwUnitType;
	}
	pStatList = STATLIST_AllocStatList(nullptr, 6, 0x32, nUnitType, nUnitGUID);
	if (pStatList != nullptr)
	{
		STATLIST_SetStatRemoveCallback(pStatList_00, (StatListRemoveCallback)(pfStatRemove));
		D2COMMON_10475_PostStatToStatList(pUnit, pStatList, 1);
	}
}

//D2Client.0x6FABDD70
void __fastcall sub_6FABDD70(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	int iVar1;
	uint32_t uVar2;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if ((((pSkill != nullptr) && (iVar1 = STATES_CheckState(pUnit, 0x12), iVar1 == 0)) &&
	        (uVar2 = SKILLS_GetFlags(pSkill), (uVar2 & 2) == 0)) &&
	    (((iVar1 = SKILLS_GetSkillIdFromSkill(pSkill, (const char*)(dword_6FB777BB + 1), 0x93c), -1 < iVar1 && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	        (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar1 * 0x23c, iVar1 != 0))))
	{
		switch (*(uint16_t*)(iVar1 + 0x2e))
		{
		case 0x43:
			sub_6FAC9E50(pUnit);
			return;
		case 0x4c:
			sub_6FAC2800(pUnit);
			break;
		case 0x4d:
		case 0x4e:
			sub_6FAC1C00(pUnit);
			return;
		}
	}
}

//D2Client.0x6FABDE30
void __fastcall sub_6FABDE30(D2UnitStrc* hUnit, int a2, uint32_t a3, uint32_t a4)
{
	int iVar1;
	D2SkillStrc* pDVar2;
	D2SkillStrc* pDVar3;
	int nSkillId;
	int iVar4;
	uint32_t uVar5;
	D2SkillStrc* pDVar6;
	int iVar7;

	D2_ASSERT(hUnit != nullptr);
	if (a2 != 0)
	{
		if (hUnit->pSkills != nullptr)
		{
			pDVar2 = SKILLS_GetFirstSkillFromSkillList(hUnit->pSkills);
			while (pDVar6 = pDVar2, pDVar6 != nullptr)
			{
				pDVar3 = SKILLS_GetNextSkill(pDVar6);
				nSkillId = SKILLS_GetSkillIdFromSkill(pDVar6, (const char*)(dword_6FB777BB + 1), 0x973);
				pDVar2 = pDVar6;
				if ((((((-1 < nSkillId) &&
				           (iVar7 = *(int*)((uint8_t*)&sgptDataTables), nSkillId < *(int*)(iVar7 + 0xba0))) &&
				          (iVar1 = *(int*)(iVar7 + 0xb98) + nSkillId * 0x23c, iVar1 != 0)) &&
				         (((iVar4 = (int)*(short*)(iVar1 + 0x194), -1 < iVar4 &&
				                                                       (iVar4 < *(int*)(iVar7 + 0xb94))) &&
				             ((iVar7 = iVar4 * 0x120 + *(int*)(iVar7 + 0xb8c), iVar7 != 0 &&
				                                                                   ((iVar4 = SKILLS_GetSkillLevel(hUnit, pDVar6, 1), pDVar2 = pDVar3, 0 < iVar4 && (iVar4 = SKILLS_IsEnhanceable(nSkillId), iVar4 != 0)))))))) &&
				        ((a3 == 0 || (*(uint8_t*)(iVar1 + 0x1dc) == a3)))) &&
				    ((((uint8_t)a4 == 4 || ((int)*(char*)(iVar7 + 2) == (uint8_t)a4 + 1)) &&
				        (uVar5 = SKILLS_GetOwnerGUIDFromSkill(pDVar6), uVar5 == 0xffffffff))))
				{
					D2Common_11031(hUnit, nSkillId, a2);
					pDVar6 = SKILLS_GetSkillById(hUnit, nSkillId, 0xffffffff);
					if ((pDVar6 != nullptr) &&
					    (iVar7 = SKILLS_GetSkillLevel(hUnit, pDVar6, 1), iVar7 == 0))
					{
						SKILLS_RemoveSkill(hUnit, nSkillId, (const char*)(dword_6FB777BB + 1),
						    0x9a0);
					}
				}
			}
			SKILLS_RefreshPassiveSkills(hUnit);
			return;
		}
		FOG_DisplayAssert("hSkillInfo", (const char*)(dword_6FB777BB + 1), 0x96c);
		exit(-1);
	}
	FOG_DisplayAssert("nDelta != 0", (const char*)(dword_6FB777BB + 1), 0x96a);
	exit(-1);
}

//D2Client.0x6FABDFF0
// TODO: decompilation needs review (in_reg)
bool __fastcall sub_6FABDFF0(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint8_t bVar2;
	uint16_t uVar3;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar4;
	int iVar5;
	int32_t nY;
	int32_t DVar6;
	int in_EDX;
	int local_48;
	int aiStack_40[16];

	if ((in_EDX < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= in_EDX))
	{
		local_48 = 0;
	}
	else
	{
		local_48 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + in_EDX * 0x1a4;
	}
	pRoom = UNITS_GetRoom(pUnit);
	D2_ASSERT(local_48);
	if (pRoom != nullptr)
	{
		pDVar4 = sub_6FB296A0((int)pUnit);
		if (pDVar4 == nullptr)
		{
			pDynamicPath = pUnit->pDynamicPath;
			iVar5 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
			nY = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
		}
		else
		{
			uVar1 = pDVar4->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iVar5 = pDVar4->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar4->pDynamicPath == nullptr)
			{
				iVar5 = 0;
			}
			else
			{
				iVar5 = PATH_GetXPosition(pDVar4->pDynamicPath);
			}
			uVar1 = pDVar4->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				nY = (*(int32_t*)&pDVar4->pDynamicPath->tTargetCoord);
			}
			else if (pDVar4->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
			}
			else
			{
				nY = (int32_t)PATH_GetYPosition(pDVar4->pDynamicPath);
			}
		}
		if ((iVar5 == 0) || (nY == (int32_t)0x0))
		{
			bVar2 = UNITS_GetDirection(pUnit);
			aiStack_40[5] = 1;
			aiStack_40[7] = 1;
			aiStack_40[9] = 1;
			aiStack_40[0xf] = 1;
			uVar1 = pUnit->dwUnitType;
			aiStack_40[0] = 0;
			aiStack_40[1] = 0xffffffff;
			aiStack_40[2] = 0xfffffffe;
			aiStack_40[3] = 0xffffffff;
			aiStack_40[4] = 0;
			aiStack_40[6] = 2;
			aiStack_40[8] = 2;
			aiStack_40[10] = 0;
			aiStack_40[0xb] = 0xffffffff;
			aiStack_40[0xc] = 0xfffffffe;
			aiStack_40[0xd] = 0xffffffff;
			aiStack_40[0xe] = 0;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
			iVar5 = aiStack_40[bVar2 >> 3] + iVar5;
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
			nY = (int32_t)(aiStack_40[(bVar2 >> 3) + 8] + (int)DVar6);
		}
		if ((iVar5 != 0) && (nY != (int32_t)0x0))
		{
			uVar3 = COLLISION_CheckMaskWithSizeXY(pRoom, iVar5, (int)nY, (uint32_t) * (uint8_t*)(local_48 + 0x18a),
			    (uint32_t) * (uint8_t*)(local_48 + 0x18a), 5);
			return (bool)('\x01' - (uVar3 != 0));
		}
	}
	return false;
}

//D2Client.0x6FABE1F0
int __fastcall sub_6FABE1F0(D2UnitStrc* pUnit)
{
	int iVar1;

	iVar1 = UNITS_GetMeleeRange(pUnit);
	return iVar1 + 4;
}

//D2Client.0x6FABE200
void __fastcall sub_6FABE200(D2UnitStrc* pUnit, int a2)
{
	uint32_t nUnitType;
	D2StatListStrc* pStatList;
	uint32_t nUnitGUID;

	if (pUnit == nullptr)
	{
		nUnitGUID = 0xffffffff;
		nUnitType = 6;
	}
	else
	{
		nUnitGUID = pUnit->dwUnitId;
		nUnitType = pUnit->dwUnitType;
	}
	pStatList = STATLIST_AllocStatList(nullptr, 4, 0, nUnitType, nUnitGUID);
	if (pStatList != nullptr)
	{
		D2COMMON_10475_PostStatToStatList(pUnit, pStatList, 1);
		STATLIST_SetStatIfListIsValid(pStatList, 0x44, a2, 0);
		UNITS_UpdateAnimRateAndVelocity(pUnit, (const char*)(dword_6FB777BB + 1), 0x9e4);
	}
}

//D2Client.0x6FABE260
uint32_t* __fastcall sub_6FABE260(int a1, uint32_t a2, uint32_t a3, uint32_t a4, int a5, uint32_t a6, uint32_t a7)
{
	uint32_t* puVar1;

	if (((-1 < a5) && (a5 < 2)) && (*(int*)(byte_6FB777B4 + a5 * 4) != 0))
	{
		puVar1 = sub_6FB2A740(a1, a2, a3, a4, *(int*)(byte_6FB777B4 + a5 * 4),
		    a6, a7);
		return puVar1;
	}
	return nullptr;
}

//D2Client.0x6FABE2A0
bool __fastcall sub_6FABE2A0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	int iVar1;

	iVar1 = sub_6FABAEB0(pUnit);
	return iVar1 != 0;
}

//D2Client.0x6FABE2B0
uint32_t __fastcall sub_6FABE2B0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2SkillStrc* pSkill;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	SKILLS_SetParam1(pSkill, 0);
	return 1;
}

//D2Client.0x6FABE2D0
uint32_t __fastcall sub_6FABE2D0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2SkillStrc* pSkill;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int32_t nY;
	int iStack_10;
	int iStack_c;
	D2UnitStrc* local_8;
	D2SkillStrc* pDStack_4;

	local_8 = pUnit;
	iVar3 = sub_6FABAEB0(pUnit);
	if (iVar3 == 0)
	{
		return 0;
	}
	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar3 == 0))
	{
		return 0;
	}
	pDStack_4 = UNITS_GetUsedSkill(pUnit);
	if (pDStack_4 == nullptr)
	{
		return 0;
	}
	iStack_c = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 100), a2, a3);
	pDVar4 = sub_6FB296A0((int)pUnit);
	iStack_10 = 0;
	if (pDVar4 == nullptr)
	{
		pDVar4 = sub_6FABB890(pUnit, 0, 0, iStack_c, 3, 0xffffffff, (uint32_t*)(&iStack_10));
	}
	else
	{
		iStack_10 = sub_6FABB840(pUnit, 0, 0, iStack_c, 3);
	}
	iVar5 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x140), a2, a3);
	pDVar2 = local_8;
	iVar3 = SKILLS_EvaluateSkillFormula(local_8, *(uint32_t*)(iVar3 + 0x138), a2, a3);
	pSkill = pDStack_4;
	if (iVar3 < iVar5)
	{
		iVar5 = iVar3;
	}
	if (iVar5 < iStack_10)
	{
		iVar5 = iStack_10;
	}
	iStack_10 = iVar3;
	if (iVar5 < iVar3)
	{
		iStack_10 = iVar5;
	}
	SKILLS_SetParam1(pDStack_4, iStack_10);
	if (pDVar4 != nullptr)
	{
		SKILLS_SetParam2(pSkill, pDVar4->dwUnitType);
		SKILLS_SetParam3(pSkill, pDVar4->dwUnitId);
		uVar1 = pDVar4->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nY = (*(int32_t*)&pDVar4->pDynamicPath->tTargetCoord);
		}
		else if (pDVar4->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
		}
		else
		{
			nY = (int32_t)PATH_GetYPosition(pDVar4->pDynamicPath);
		}
		uVar1 = pDVar4->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar3 = pDVar4->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar4->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pDVar4->pDynamicPath);
		}
		D2Common_10216(pDVar2->pDynamicPath, iVar3, (int)nY, 0);
		return 1;
	}
	SKILLS_SetParam2(pSkill, 1);
	SKILLS_SetParam3(pSkill, -1);
	return 1;
}

//D2Client.0x6FABE490
uint32_t __fastcall sub_6FABE490(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	D2SkillStrc* pSkill;
	int iVar2;
	D2UnitStrc* pDVar3;
	int32_t nY;
	int iStack_c;
	D2SkillStrc* pDStack_8;
	int local_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (local_4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, local_4 != 0))
	{
		pDStack_8 = UNITS_GetUsedSkill(pUnit);
		if (pDStack_8 == nullptr)
		{
			return 0;
		}
		iVar2 = sub_6FABE1F0(pUnit);
		pDVar3 = sub_6FB296A0((int)pUnit);
		iStack_c = 0;
		if (pDVar3 == nullptr)
		{
			pDVar3 = sub_6FABB890(pUnit, 0, 0, iVar2, 0x20003, 0xffffffff, (uint32_t*)(&iStack_c));
			if (pDVar3 == nullptr)
			{
				SKILLS_SetParam1(pDStack_8, 0);
				return 1;
			}
		}
		else
		{
			iStack_c = sub_6FABB840(pUnit, 0, 0, iVar2, 0x20003);
		}
		iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(local_4 + 0x138), a2, a3);
		pSkill = pDStack_8;
		if (iVar2 <= iStack_c)
		{
			iStack_c = iVar2;
		}
		SKILLS_SetParam1(pDStack_8, iStack_c);
		uVar1 = pDVar3->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nY = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
		}
		else
		{
			nY = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
		}
		uVar1 = pDVar3->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar2 = pDVar3->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = PATH_GetXPosition(pDVar3->pDynamicPath);
		}
		D2Common_10216(pUnit->pDynamicPath, iVar2, (int)nY, 0);
		SKILLS_SetParam2(pSkill, pDVar3->dwUnitType);
		SKILLS_SetParam3(pSkill, pDVar3->dwUnitId);
		return 1;
	}
	return 0;
}

//D2Client.0x6FABE610
uint32_t __fastcall sub_6FABE610(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	D2SkillStrc* pSkill;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t nY;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar4 != 0))
	{
		pSkill = UNITS_GetUsedSkill(pUnit);
		if (pSkill == nullptr)
		{
			return 0;
		}
		iVar2 = sub_6FABE1F0(pUnit);
		pDVar3 = sub_6FB296A0((int)pUnit);
		if (pDVar3 == nullptr)
		{
			pDVar3 = sub_6FABB890(pUnit, 0, 0, iVar2, 0x20003, 0xffffffff, nullptr);
			if (pDVar3 == nullptr)
			{
				SKILLS_SetParam1(pSkill, 0);
				return 1;
			}
		}
		iVar4 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x138), a2, a3);
		SKILLS_SetParam1(pSkill, iVar4);
		uVar1 = pDVar3->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nY = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
		}
		else
		{
			nY = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
		}
		uVar1 = pDVar3->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
		}
		D2Common_10216(pUnit->pDynamicPath, iVar4, (int)nY, 0);
		SKILLS_SetParam2(pSkill, pDVar3->dwUnitType);
		SKILLS_SetParam3(pSkill, pDVar3->dwUnitId);
		return 1;
	}
	return 0;
}

//D2Client.0x6FABE760
uint32_t __fastcall sub_6FABE760(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;

	if (pUnit->nActionFrame == 3)
	{
		if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
		{
			return 0;
		}
		if ((pUnit->dwUnitType == 0) && (0 < *(short*)(iVar1 + 0x102)))
		{
			sub_6FB55820((int)*(short*)(iVar1 + 0x102), pUnit, 0.0, 0.0, 0);
		}
		if ((pUnit->dwUnitType == 1) && (0 < *(short*)(iVar1 + 0x104)))
		{
			sub_6FB55820((int)*(short*)(iVar1 + 0x104), pUnit, 0.0, 0.0, 0);
		}
	}
	return 1;
}

//D2Client.0x6FABE7F0
uint32_t __fastcall sub_6FABE7F0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	int32_t DVar4;
	int iVar5;
	uint32_t* puVar6;
	int iStack_74;
	int iStack_70;
	int iStack_6c;
	int iStack_68;
	int local_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	int iStack_2c;
	int iStack_18;

	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x40;
	}
	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar3 != 0))
	{
		iVar5 = (int)*(short*)(iVar3 + 0xea);
		local_64 = iVar5;
		local_60 = iVar3;
		iVar2 = UNITS_GetWeaponClass(pUnit);
		if ((iVar2 != 1) && (-1 < *(short*)(iVar3 + 0xec)))
		{
			iVar5 = (int)*(short*)(iVar3 + 0xec);
			local_64 = iVar5;
		}
		if ((-1 < iVar5) && (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x138), a2, a3);
			iVar2 = sub_6FABA950(pUnit, &iStack_74, &iStack_70);
			if (iVar2 != 0)
			{
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iStack_6c = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_6c = 0;
				}
				else
				{
					iStack_6c = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				iStack_6c = iStack_74 - iStack_6c;
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
				iStack_68 = iStack_70 - (int)DVar4;
				sub_6FABAB20(&iStack_6c, &iStack_68);
				sub_6FABAB70(&iStack_6c, &iStack_68);
				iStack_74 = iStack_74 - (iStack_6c * iVar3) / 2;
				iStack_70 = iStack_70 - (iStack_68 * iVar3) / 2;
				puVar6 = &uStack_5c;
				for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
				{
					*puVar6 = 0;
					puVar6 = puVar6 + 1;
				}
				iStack_2c = a3;
				uStack_5c = 0x820;
				iStack_4c = local_64;
				pDStack_58 = pUnit;
				pDStack_54 = pUnit;
				iStack_30 = a2;
				iStack_18 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(local_60 + 0x13c), a2, a3);
				if (0 < iVar3)
				{
					do
					{
						iStack_40 = iStack_74;
						iStack_3c = iStack_70;
						sub_6FB3E070(&uStack_5c);
						iStack_74 = iStack_74 + iStack_6c;
						iStack_70 = iStack_70 + iStack_68;
						iVar3 = iVar3 + -1;
					} while (iVar3 != 0);
				}
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FABEA20
uint32_t __fastcall sub_6FABEA20(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint32_t uVar1;
	short sVar2;
	uint16_t uVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	D2UnitStrc* pMissile;
	uint32_t* puVar6;
	int local_68;
	int local_64;
	int local_60;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	D2UnitStrc* local_50;
	int local_4c;
	int local_40;
	int local_3c;
	int local_30;
	uint32_t local_2c;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		iVar4 = sub_6FABA950(pUnit, &local_68, &local_64);
		if (iVar4 != 0)
		{
			local_60 = sub_6FABF670(pUnit, a2);
			if ((-1 < local_60) && (local_60 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
			{
				pDVar5 = sub_6FB296A0((int)pUnit);
				puVar6 = &local_5c;
				for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
				{
					*puVar6 = 0;
					puVar6 = puVar6 + 1;
				}
				local_40 = local_68;
				local_5c = 0x20;
				local_3c = local_64;
				local_2c = a3;
				local_4c = local_60;
				if (pDVar5 == nullptr)
				{
					local_5c = 0x420;
				}
				local_58 = pUnit;
				local_54 = pUnit;
				local_50 = pDVar5;
				local_30 = a2;
				pMissile = sub_6FB3E070(&local_5c);
				if (pMissile != nullptr)
				{
					if (pDVar5 == nullptr)
					{
						iVar4 = 2;
					}
					else
					{
						iVar4 = 1;
					}
					MISSILE_SetTargetX(pMissile, iVar4);
					uVar1 = pUnit->dwUnitType;
					if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
					{
						sVar2 = (short)pUnit->pDynamicPath->dwClientCoordY;
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						sVar2 = 0;
					}
					else
					{
						iVar4 = PATH_GetXPosition(pUnit->pDynamicPath);
						sVar2 = (short)iVar4;
					}
					uVar1 = pUnit->dwUnitType;
					if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
					{
						uVar3 = (pUnit->pDynamicPath->tTargetCoord).X;
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						uVar3 = 0;
					}
					else
					{
						iVar4 = PATH_GetYPosition(pUnit->pDynamicPath);
						uVar3 = (uint16_t)iVar4;
					}
					MISSILE_SetTargetY(pMissile, (short)((short)local_64 - uVar3) * 0x10000 +
					                                 (int)(short)((short)local_68 - sVar2));
				}
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FABEBC0
uint32_t __fastcall sub_6FABEBC0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	int local_78;
	int32_t DStack_74;
	int32_t DStack_70;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	int iStack_2c;
	code* pcStack_8;
	int iStack_4;

	if (((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	         (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar5 != 0)) &&
	        ((pDVar2 = sub_6FB296A0((int)pUnit), pDVar2 != nullptr &&
	                                                 (iVar3 = sub_6FABF670(pUnit, a2), -1 < iVar3)))) &&
	    (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			local_78 = pDVar2->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			local_78 = 0;
		}
		else
		{
			local_78 = PATH_GetXPosition(pDVar2->pDynamicPath);
		}
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_74 = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_74 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_74 + 2)) = 0;
		}
		else
		{
			DStack_74 = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar4 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_70 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_70 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_70 + 2)) = 0;
		}
		else
		{
			DStack_70 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iVar5 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar5 + 0x138), a2, a3);
		puVar7 = &uStack_5c;
		for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar7 = 0;
			puVar7 = puVar7 + 1;
		}
		iStack_48 = local_78;
		DStack_44 = DStack_74;
		iStack_3c = (int)DStack_74 * 2 - (int)DStack_70;
		iVar6 = 0;
		uStack_5c = 0x21;
		iStack_2c = a3;
		pcStack_8 = (code*)(sub_6FAC9E80);
		pDStack_58 = pUnit;
		iStack_4c = iVar3;
		iStack_40 = local_78 * 2 - iVar4;
		iStack_30 = a2;
		if (0 < iVar5)
		{
			do
			{
				iStack_4 = iVar6;
				sub_6FB3E070(&uStack_5c);
				iVar6 = iVar6 + 1;
			} while (iVar6 < iVar5);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FABEDC0
uint32_t __fastcall sub_6FABEDC0(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SkillStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	int32_t nY;
	int iVar6;
	uint32_t* puVar7;
	int iStack_7c;
	int iStack_70;
	int iStack_6c;
	int iStack_68;
	D2SkillStrc* pDStack_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	int iStack_2c;

	if (a2 < 0)
	{
		return 0;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)
	{
		return 0;
	}
	local_60 = a2 * 0x23c;
	iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + local_60;
	if (iVar6 == 0)
	{
		return 0;
	}
	pDVar1 = UNITS_GetUsedSkill(pUnit);
	if (pDVar1 != nullptr)
	{
		pDStack_64 = pDVar1;
		iStack_68 = SKILLS_GetParam1(pDVar1);
		if (iStack_68 < 1)
		{
			return 0;
		}
		iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar6 + 100), a2, a3);
		uVar3 = SKILLS_GetParam3(pDVar1);
		iVar4 = SKILLS_GetParam2(pDVar1);
		pDVar5 = sub_6FB269F0(uVar3, iVar4);
		if ((pDVar5 != nullptr) ||
		    (pDVar5 = sub_6FABB890(pUnit, 0, 0, iVar2, 3, uVar3, nullptr),
		        pDVar5 != nullptr))
		{
			UNITS_SetTargetUnitForDynamicUnit(pUnit, pDVar5);
		}
		iVar4 = sub_6FABA950(pUnit, &iStack_70, &iStack_6c);
		if (iVar4 != 0)
		{
			iStack_7c = (int)*(short*)(iVar6 + 0xea);
			iVar4 = UNITS_GetWeaponClass(pUnit);
			if ((iVar4 != 1) && (-1 < *(short*)(iVar6 + 0xec)))
			{
				iStack_7c = (int)*(short*)(iVar6 + 0xec);
			}
			if ((-1 < iStack_7c) && (iStack_7c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
			{
				puVar7 = &uStack_5c;
				for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
				uVar3 = pUnit->dwUnitType;
				uStack_5c = 0x21;
				pDStack_58 = pUnit;
				if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
				{
					iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_48 = 0;
				}
				else
				{
					iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar3 = pUnit->dwUnitType;
				if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
				{
					DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
				}
				else
				{
					DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				iStack_2c = a3;
				iStack_40 = iStack_70;
				iStack_4c = iStack_7c;
				iStack_3c = iStack_6c;
				iStack_30 = a2;
				sub_6FB3E070(&uStack_5c);
				pDVar1 = pDStack_64;
				iVar6 = iStack_68 + -1;
				SKILLS_SetParam1(pDStack_64, iVar6);
				if (iVar6 < 1)
				{
					return 1;
				}
				if (pDVar5 == nullptr)
				{
					uVar3 = 0xffffffff;
				}
				else
				{
					uVar3 = pDVar5->dwUnitId;
				}
				pDVar5 = sub_6FABB890(pUnit, 0, 0, iVar2, 3, uVar3, nullptr);
				if (pDVar5 != nullptr)
				{
					uVar3 = pDVar5->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						nY = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
					}
					else if (pDVar5->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
					}
					else
					{
						nY = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
					}
					uVar3 = pDVar5->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						iVar6 = pDVar5->pDynamicPath->dwClientCoordY;
					}
					else if (pDVar5->pDynamicPath == nullptr)
					{
						iVar6 = 0;
					}
					else
					{
						iVar6 = PATH_GetXPosition(pDVar5->pDynamicPath);
					}
					D2Common_10216(pUnit->pDynamicPath, iVar6, (int)nY, 0);
					SKILLS_SetParam2(pDVar1, pDVar5->dwUnitType);
					SKILLS_SetParam3(pDVar1, pDVar5->dwUnitId);
					if ((a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)) &&
					    (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + local_60, iVar6 != 0))
					{
						sub_6FABDAD0((int)pUnit, *(int*)(iVar6 + 0x15c));
						return 1;
					}
					sub_6FABDAD0((int)pUnit, 0);
					return 1;
				}
			}
		}
		return 0;
	}
	return 0;
}
