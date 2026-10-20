#include "Unit/Player.h"

#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/RosterPets.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "UI/NpcMenu.h"
#include "UI/SkillDesc.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"
#include "Unit/Missile.h"
#include "Unit/PlrSkills.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB93CF8
uint8_t byte_6FB93CF8[4];
//D2Client.0x6FB93CFC
uint8_t byte_6FB93CFC[4] = {2};
//D2Client.0x6FB93D00
uint8_t byte_6FB93D00[232] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1};
//D2Client.0x6FB93DE8
uint8_t byte_6FB93DE8[36] = {0, 0, 0, 0, 0x15, 0, 0, 0, 0x13, 0, 0, 0, 0x13, 0, 0, 0, 0x13};
//D2Client.0x6FB93E0C
int32_t dword_6FB93E0C = 9;
//D2Client.0x6FBBC234
uint32_t dword_6FBBC234;
//D2Client.0x6FBBC238
int32_t dword_6FBBC238;
//D2Client.0x6FBBC23C
int32_t dword_6FBBC23C;
//D2Client.0x6FBBC240
int32_t dword_6FBBC240;

//D2Client.0x6FB48570
void __fastcall sub_6FB48570(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	int iVar2;
	uint8_t bVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;

	if ((pUnit == nullptr) ||
	    (((uVar6 = pUnit->dwUnitType, uVar6 != 0 && (uVar6 != 1)) ||
	        (uVar1 = pUnit->dwInteractGUID, uVar1 == 0))))
	{
		return;
	}
	if (uVar6 == 0)
	{
		uVar6 = 0xd;
	}
	else
	{
		iVar5 = pUnit->dwClassId;
		if (iVar5 < 0)
		{
			return;
		}
		iVar2 = *(int*)((uint8_t*)&sgptDataTables);
		if (*(int*)(iVar2 + 0xa80) <= iVar5)
		{
			return;
		}
		iVar5 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar5 * 0x1a8);
		if (iVar5 < 0)
		{
			return;
		}
		if (*(int*)(iVar2 + 0xa98) <= iVar5)
		{
			return;
		}
		iVar5 = *(int*)(iVar2 + 0xa90) + iVar5 * 0x134;
		if (iVar5 == 0)
		{
			return;
		}
		bVar3 = MONSTERS_GetMaximalLightRadius(pUnit);
		uVar4 = (uint32_t) * (uint8_t*)(iVar5 + 0x11e);
		uVar6 = (uint32_t)bVar3;
		if (bVar3 < uVar4)
		{
			uVar6 = uVar4;
		}
	}
	iVar5 = uVar6 + a2;
	if (iVar5 < 1)
	{
		iVar5 = 0;
	}
	sub_6FAA43E0(uVar1, iVar5);
}

//D2Client.0x6FB48630
void __fastcall sub_6FB48630(uint32_t a1, D2UnitStrc* pUnit, D2UnitStrc* pUnit2, uint32_t a4, int a5, int a6)
{
	uint32_t nOwnerGUID;
	D2SkillStrc* pSkill;
	D2UnitStrc* pDVar1;
	uint8_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;

	if (pUnit != nullptr)
	{
		uVar4 = a4 >> 0x10;
		switch (uVar4)
		{
		case 0x59:
			sub_6FB48570(pUnit, a6);
			return;
		case 0x5a:
			if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) &&
			    (pUnit->dwInteractGUID != 0))
			{
				uVar2 = 0xff;
				(*(uint8_t*)((uint8_t*)&pUnit2 + 0)) = 0xff;
				(*(uint8_t*)((uint8_t*)&a4 + 0)) = 0xff;
				if (a6 != 0)
				{
					uVar2 = (uint8_t)((uint32_t)a6 >> 0x10);
					(*(uint8_t*)((uint8_t*)&pUnit2 + 0)) = (uint8_t)((uint32_t)a6 >> 8);
					(*(uint8_t*)((uint8_t*)&a4 + 0)) = (uint8_t)a6;
				}
				sub_6FAA4490(pUnit->dwInteractGUID, uVar2, (*(uint8_t*)((uint8_t*)&pUnit2 + 0)), (uint8_t)a4);
				return;
			}
			break;
		case 0x61:
		case 0x6b:
			if (pUnit->dwUnitType == 0)
			{
				uVar3 = a4 & 0xffff;
				pSkill = SKILLS_GetSkillById(pUnit, uVar3, 0xffffffff);
				if (a6 == 0)
				{
					if ((pSkill != nullptr) &&
					    (iVar5 = SKILLS_GetSkillLevel(pUnit, pSkill, 0), iVar5 < 1))
					{
						SKILLS_RemoveSkill(pUnit, uVar3, __FILE__, __LINE__);
						return;
					}
				}
				else if (pSkill == nullptr)
				{
					if ((int)uVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))
					{
						iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + uVar3 * 0x23c;
					}
					else
					{
						iVar5 = 0;
					}
					if ((uVar4 == 0x61) ||
					    ((iVar5 != 0 && ((int)*(char*)(iVar5 + 0xc) == pUnit->dwClassId))))
					{
						SKILLS_AssignSkill(pUnit, uVar3, 0, 0, __FILE__, __LINE__);
						return;
					}
				}
			}
			break;
		case 0xcc:
			if (pUnit->dwUnitType == 0)
			{
				iVar5 = (int)(a4 & 0xffff) >>
				        ((uint8_t) * (uint32_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc6c) & 0x1f);
				uVar3 = *(uint32_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc70) & a4 & 0xffff;
				if (pUnit2 != nullptr)
				{
					nOwnerGUID = pUnit2->dwUnitId;
					uVar4 = STATLIST_UnitGetStatValue(pUnit2, uVar4, (uint16_t)a4);
					if (((uVar4 & 0xff) != 0) &&
					    (pDVar1 = STATLIST_GetOwner(pUnit2, nullptr), pDVar1 == pUnit))
					{
						D2Common_10954(pUnit, nOwnerGUID, iVar5, uVar3, uVar4 & 0xff, 0);
						return;
					}
					D2Common_10954(pUnit, nOwnerGUID, iVar5, uVar3, 0, 1);
				}
			}
		}
	}
}

//D2Client.0x6FB488A0
// TODO: decompilation needs review (stack0x, unaff_)
void __fastcall sub_6FB488A0(D2UnitStrc* pUnit2, D2ActiveRoomStrc* pActiveRoom, int a3, int a4)
{
	uint8_t stack0x00000000[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffffc[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint64_t DVar1;
	D2InventoryStrc* pDVar2;
	D2SkillListStrc* pDVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t* puVar6;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pUnit;
	char nFlags;
	int unaff_ESI;
	uint32_t uVar7;
	uint32_t unaff_retaddr;

	sub_6FB3F2F0((int)pUnit2);
	PATH_AllocDynamicPath(nullptr, pActiveRoom, a3, a4, pUnit2, 1);
	if (pUnit2->pInventory == nullptr)
	{
		pDVar2 = INVENTORY_AllocInventory(nullptr, pUnit2);
		pUnit2->pInventory = pDVar2;
	}
	pDVar3 = SKILLS_AllocSkillList(nullptr);
	pUnit2->pSkills = pDVar3;
	SKILLS_InitSkillList(pUnit2);
	STATLIST_AllocStatListEx(pUnit, nFlags, (StatListValueChangeFunc)(pUnit2), nullptr);
	STATLIST_SetUnitStat(pUnit2, 0x44, 100, 0);
	STATLIST_SetUnitStat(pUnit2, 0x43, 100, 0);
	STATLIST_SetUnitStat(pUnit2, 0x45, 100, 0);
	dword_6FBBC234 = DUNGEON_IsRoomInTown(pActiveRoom);
	UNITS_ChangeAnimMode(pUnit2, 5);
	pUnit2->dwFlags = pUnit2->dwFlags & 0xffffffdf | 0xe;
	if ((pUnit2->dwAnimMode == 0x11) || (pUnit2->dwAnimMode == 0))
	{
		PATH_RemoveCollisionFootprintForUnit(pUnit2, 1);
		PATH_SetUnitCollisionPattern(pUnit2, 5);
		PATH_SetFootprintCollisionMask(pUnit2->pDynamicPath, 0x8000);
	}
	pDVar4 = CUNIT_GetPlayer();
	iVar5 = D2COMMON_10083_Return0(pActiveRoom);
	if (iVar5 == 0)
	{
		if ((pDVar4 == nullptr) || (pUnit2 == pDVar4))
		{
			iVar5 = 0;
		}
		else
		{
			iVar5 = 1;
		}
		puVar6 = sub_6FAA4280(pUnit2, iVar5, 0xd, 0xff, 0xff, 0xff, 0xff);
		if (puVar6 != nullptr)
		{
			pUnit2->dwInteractGUID = (uint32_t)puVar6;
			iVar5 = sub_6FAA4460((int)puVar6);
			sub_6FB29AB0((int)pUnit2, iVar5);
		}
	}
	UNITS_AllocPlayerData(pUnit2);
	if (pUnit2 != pDVar4)
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit2->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit2->pSeed) = DVar1;
		PATH_SetDirection(pUnit2->pDynamicPath, (uint8_t)(*(uint32_t*)((uint8_t*)&DVar1 + 0)) & 0x3f);
	}
	pDVar4 = CUNIT_GetPlayer();
	if ((pDVar4 != nullptr) && (pRoom = CUNIT_GetPlayerRoom(), pRoom != nullptr))
	{
		DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, (D2ActiveRoomStrc***)stack0xfffffffc, (int*)stack0x00000000);
		uVar7 = 0;
		if (unaff_retaddr != 0)
		{
			do
			{
				for (pDVar4 = *(D2UnitStrc**)(*(int*)(unaff_ESI + uVar7 * 4) + 0x2c);
				     pDVar4 != nullptr; pDVar4 = pDVar4->pRoomNext)
				{
					if ((pDVar4->dwUnitType == 1) && (iVar5 = STATES_CheckState(pDVar4, 0x3f), iVar5 != 0))
					{
						sub_6FB5C080(pDVar4);
					}
				}
				uVar7 = uVar7 + 1;
			} while (uVar7 < unaff_retaddr);
		}
	}
}

//D2Client.0x6FB48A60
void __fastcall sub_6FB48A60(D2UnitStrc* pUnit)
{
	void* pvVar1;
	D2UnitStrc* pDVar2;
	D2ActiveRoomStrc* pRoom;
	int iVar3;
	uint32_t uVar4;
	uint32_t uStack_8;
	D2ActiveRoomStrc** ppDStack_4;

	sub_6FB3F310((int)pUnit);
	sub_6FB59320((int)pUnit);
	if (ghAct != nullptr)
	{
		D2Common_10228(pUnit);
		UNITROOM_RemoveUnitFromRoom(pUnit);
	}
	PATH_FreeDynamicPath(nullptr, pUnit->pDynamicPath);
	pUnit->pDynamicPath = nullptr;
	sub_6FB29AE0(pUnit, 0);
	INVENTORY_FreeInventory(pUnit->pInventory);
	pUnit->pInventory = nullptr;
	pvVar1 = D2Common_10958(pUnit, nullptr);
	if (pvVar1 != nullptr)
	{
		sub_6FAA44D0((int)pvVar1);
	}
	sub_6FB296E0((int)pUnit);
	pDVar2 = CUNIT_GetPlayer();
	if (pUnit == pDVar2)
	{
		sub_6FB28390(nullptr);
	}
	UNITS_FreePlayerData(nullptr, pUnit);
	pDVar2 = CUNIT_GetPlayer();
	if ((pDVar2 != nullptr) && (pRoom = CUNIT_GetPlayerRoom(), pRoom != nullptr))
	{
		DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_4, (int*)&uStack_8);
		uVar4 = 0;
		if (uStack_8 != 0)
		{
			do
			{
				for (pDVar2 = ppDStack_4[uVar4]->pUnitFirst; pDVar2 != nullptr;
				     pDVar2 = pDVar2->pRoomNext)
				{
					if ((pDVar2->dwUnitType == 1) && (iVar3 = STATES_CheckState(pDVar2, 0x3f), iVar3 != 0))
					{
						sub_6FB5C080(pDVar2);
					}
				}
				uVar4 = uVar4 + 1;
			} while (uVar4 < uStack_8);
		}
	}
}

//D2Client.0x6FB48B60
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB48B60(D2UnitStrc* pUnit)
{
	uint8_t bVar1;
	D2PlayerDataStrc* pDVar2;
	D2DynamicPathStrc* pDynamicPath;
	bool bVar3;
	uint16_t uVar4;
	uint32_t extraout_var;
	D2UnitStrc* pDVar5;
	int iVar6;
	D2UnitStrc** ppDVar7;
	D2ActiveRoomStrc* pDVar8;
	int iVar9;
	D2SkillStrc* pSkill;
	uint32_t uVar10;
	uint32_t extraout_var_00;
	uint32_t uVar11;
	D2ActiveRoomStrc* pRoom2;
	D2ActiveRoomStrc* pRoom1;
	D2UnitStrc* pDVar12;
	uint32_t* puVar13;
	int local_28;
	D2CoordStrc local_24;
	uint32_t uStack_1c;
	int32_t DStack_18;

	local_24.nX = (int)pUnit->pDynamicPath;
	local_28 = 0;
	if (*(int*)(byte_6FB93CF8 + pUnit->dwAnimMode * 0xc) == 1)
	{
		bVar3 = sub_6FB4E5D0(pUnit);
		local_28 = D2C_ZEXT(bVar3);
		pDVar5 = CUNIT_GetPlayer();
		if (pUnit == pDVar5)
		{
			uVar10 = pUnit->dwUnitType;
			if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
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
			ppDVar7 = sub_6FAB6A90((int*)pUnit);
			pDVar8 = UNITS_GetRoom(pUnit);
			iVar9 = UNITS_IsCurrentRoomInvalid(pUnit);
			DUNGEON_UpdatePops(pDVar8, iVar6, (int)ppDVar7, iVar9);
		}
		sub_6FB4FF80(pUnit);
	}
	if ((*(int*)(byte_6FB93CF8 + pUnit->dwAnimMode * 0xc) == 2) &&
	    (pSkill = UNITS_GetUsedSkill(pUnit), pSkill != nullptr))
	{
		uVar10 = SKILLS_GetFlags(pSkill);
		bVar3 = true;
		if ((uVar10 & 1) != 0)
		{
			bVar3 = sub_6FB4E5D0(pUnit);
			bVar3 = D2C_ZEXT(bVar3) != 0;
			if (bVar3)
			{
				SKILLS_SetFlags(pSkill, uVar10 | 2);
				sub_6FABCA30(pUnit);
			}
			bVar3 = !bVar3;
			pDVar5 = CUNIT_GetPlayer();
			if (pUnit == pDVar5)
			{
				uVar10 = pUnit->dwUnitType;
				if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
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
				ppDVar7 = sub_6FAB6A90((int*)pUnit);
				pDVar8 = UNITS_GetRoom(pUnit);
				iVar9 = UNITS_IsCurrentRoomInvalid(pUnit);
				DUNGEON_UpdatePops(pDVar8, iVar6, (int)ppDVar7, iVar9);
			}
		}
		bVar1 = pUnit->nActionFrame;
		if (((bVar3) && ((pUnit->dwFlags >> 6 & 1) == 0)) &&
		    ((bVar1 == 1 || ((bVar1 == 2 || (bVar1 == 3))))))
		{
			sub_6FABCA30(pUnit);
		}
	}
	switch (*(uint32_t*)(byte_6FB93CFC + pUnit->dwAnimMode * 0xc))
	{
	case 1:
		iVar6 = UNITS_IsAtEndOfFrameCycle(pUnit);
		if (iVar6 == 0)
			goto switchD_6fb48ce6_caseD_0;
		break;
	case 2:
		iVar6 = UNITS_IsAtEndOfFrameCycle(pUnit);
		if (iVar6 != 0)
		{
			pUnit->nSeqCurrentFramePrecise = pUnit->dwFrameCountPrecise + -0x100;
			goto LAB_6fb48d1e;
		}
	case 0:
	switchD_6fb48ce6_caseD_0:
		UNITS_StopSequence(pUnit);
		break;
	case 3:
		pUnit->nSeqCurrentFramePrecise = 0x100;
	LAB_6fb48d1e:
		pUnit->wAnimSpeed = 0;
	}
	if ((pUnit->dwAnimMode == 0x12) && ((pUnit->dwFlags >> 0xe & 1) != 0))
	{
		sub_6FB5C080(pUnit);
	}
	iVar6 = *(int*)(byte_6FB93D00 + pUnit->dwAnimMode * 0xc);
	if (iVar6 != 1)
	{
		if ((iVar6 < 2) || (3 < iVar6))
			goto LAB_6fb48e44;
		local_28 = UNITS_IsAtEndOfFrameCycle(pUnit);
	}
	if (local_28 != 0)
	{
		if (pUnit->dwAnimMode == 0x13)
		{
			puVar13 = &uStack_1c;
			for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1)
			{
				*puVar13 = 0;
				puVar13 = puVar13 + 1;
			}
			uVar10 = pUnit->dwUnitType;
			if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
			{
				uStack_1c = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				uStack_1c = 0;
			}
			else
			{
				uStack_1c = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar10 = pUnit->dwUnitType;
			if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
			{
				DStack_18 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0;
			}
			else
			{
				DStack_18 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iVar6 = local_24.nX;
			PATH_RecacheRoomIfNeeded((D2DynamicPathStrc*)local_24.nX);
			PATH_ResetToPreviousType((D2DynamicPathStrc*)iVar6);
			sub_6FB49090(6, pUnit, (D2SkillStrc*)(&uStack_1c), 1);
		}
		else if (((pUnit->dwUnitType == 0) &&
		             (pDVar2 = pUnit->pPlayerData, pDVar2 != nullptr)) &&
		         (pDVar2->unk0xA8[0x2b] != 0))
		{
			pDVar2->unk0xA8[0x2a] = 1;
		}
		else
		{
			sub_6FB49090(7, pUnit, 0, 1);
		}
	}
LAB_6fb48e44:
	iVar6 = UNITS_IsCurrentRoomInvalid(pUnit);
	if (iVar6 != 0)
	{
		UNITS_SetCurrentRoomInvalid(pUnit, 0);
		pDVar5 = CUNIT_GetPlayer();
		if ((pUnit == pDVar5) && (pDVar8 = UNITS_GetRoom(pUnit), pDVar8 != nullptr))
		{
			iVar6 = DUNGEON_GetLevelIdFromRoom(pDVar8);
			uVar10 = UNITS_GetPlayerPortalFlags(pUnit);
			uVar11 = DUNGEON_GetPortalFlagFromLevelId(iVar6);
			UNITS_SetPlayerPortalFlags(pUnit, uVar10 | uVar11);
			pRoom2 = UNITS_GetRoom(pUnit);
			pRoom1 = PATH_GetNextRoom(pUnit->pDynamicPath);
			DUNGEON_InitRoomTileAnimation(ghAct, pRoom1, pRoom2);
			iVar6 = DUNGEON_IsRoomInTown(pDVar8);
			uVar10 = (uint32_t)(iVar6 != 0);
			if ((dword_6FBBC234 != uVar10) && (uVar10 == 0))
			{
				sub_6FAF7D90(pUnit);
			}
			dword_6FBBC234 = uVar10;
			iVar6 = DUNGEON_CheckLOSDraw(pDVar8);
			sub_6FAA88C0(iVar6);
			sub_6FABA440(pDVar8);
		}
	}
	D2COMMON_10193_PATH_AdjustDirection((D2DynamicPathStrc*)local_24.nX);
	if (((pUnit->dwAnimMode == 3) && (pDVar5 = CUNIT_GetPlayer(), pUnit == pDVar5)) &&
	    (iVar6 = STATLIST_UnitGetStatValue(pUnit, 10, 0), iVar6 == 0))
	{
		puVar13 = &uStack_1c;
		for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar13 = 0;
			puVar13 = puVar13 + 1;
		}
		pDynamicPath = pUnit->pDynamicPath;
		pDVar5 = sub_6FB296A0((int)pUnit);
		pDVar12 = PATH_GetTargetUnit(pDynamicPath);
		if (pDVar12 == nullptr)
		{
			uStack_1c = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
			DStack_18 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
			iVar6 = 1;
		}
		else
		{
			uStack_1c = 6;
			if (pDVar5 == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0xffff;
				(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0xffff;
				iVar6 = 0;
			}
			else
			{
				uStack_1c = pDVar5->dwUnitType;
				DStack_18 = (int32_t)pDVar5->dwUnitId;
				iVar6 = 0;
			}
		}
		sub_6FB49090(iVar6, pUnit, (D2SkillStrc*)(&uStack_1c), 0);
	}
	iVar6 = STATES_CheckStateMaskActiveOnUnit(pUnit);
	if (iVar6 != 0)
	{
		sub_6FABD780(pUnit);
	}
	if ((pUnit->dwAnimMode == 1) || (pUnit->dwAnimMode == 5))
	{
		uVar10 = pUnit->dwUnitType;
		if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
		{
			local_24.nX = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			local_24.nX = 0;
		}
		else
		{
			local_24.nX = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar10 = pUnit->dwUnitType;
		if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
		{
			local_24.nY = *(int*)&pUnit->pDynamicPath->tTargetCoord;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&local_24.nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&local_24.nY + 2)) = 0;
		}
		else
		{
			local_24.nY = PATH_GetYPosition(pUnit->pDynamicPath);
		}
		pDVar8 = UNITS_GetRoom(pUnit);
		if (pDVar8 != nullptr)
		{
			uVar4 = 0xc01;
			iVar6 = PATH_GetUnitCollisionPattern(pUnit);
			uVar4 = COLLISION_CheckMaskWithPattern(pDVar8, local_24.nX, local_24.nY, iVar6, uVar4);
			if (uVar4 != 0)
			{
				iVar9 = 1;
				uVar10 = 0xc01;
				iVar6 = UNITS_GetUnitSizeX(pUnit);
				COLLISION_GetFreeCoordinates(pDVar8, &local_24, iVar6, uVar10, iVar9);
				sub_6FB26DD0(pUnit, (char*)local_24.nX, (char*)local_24.nY, 0);
			}
		}
	}
}

//D2Client.0x6FB49090
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB49090(int a1, D2UnitStrc* pUnit, D2SkillStrc* pSkill, int a4)
{
	D2DynamicPathStrc* pDynamicPath;
	D2SkillsTxt* pDVar1;
	void* pvVar2;
	D2UnitStrc* pDVar3;
	D2SkillStrc* pDVar4;
	uint32_t uVar5;
	D2ActiveRoomStrc* pRoom;
	int iVar6;
	D2SkillsTxt* pDVar7;
	D2UnitStrc** ppDVar8;
	uint16_t extraout_var;
	uint16_t extraout_var_00;
	uint16_t extraout_var_01;
	uint16_t extraout_var_02;
	uint16_t extraout_var_03;
	uint16_t extraout_var_04;
	uint32_t extraout_EDX;
	uint32_t uVar9;
	uint32_t extraout_EDX_00;
	uint16_t extraout_var_05;
	uint16_t extraout_var_06;
	uint32_t uVar10;
	uint16_t extraout_var_07;
	uint16_t extraout_var_08;
	uint16_t extraout_var_09;
	uint16_t uVar12;
	uint16_t extraout_var_10;
	int* piVar13;
	int* piVar14;
	uint16_t uVar11;

	pvVar2 = D2Common_10958(pUnit, nullptr);
	if (pvVar2 != nullptr)
	{
		sub_6FAA44D0((int)pvVar2);
	}
	pDVar3 = CUNIT_GetPlayer();
	if (a1 != 0x13)
	{
		pDVar4 = UNITS_GetUsedSkill(pUnit);
		if (pDVar4 != nullptr)
		{
			uVar5 = SKILLS_GetFlags(pDVar4);
			if ((uVar5 & 1) == 0)
			{
				if ((pUnit == pDVar3) ||
				    ((pUnit != nullptr && ((pUnit->dwFlags >> 6 & 1) != 0))))
					goto LAB_6fb49100;
			}
			else
			{
				SKILLS_SetFlags(pDVar4, uVar5 | 2);
			}
			sub_6FABCA30(pUnit);
		}
	LAB_6fb49100:
		UNITS_SetUsedSkill(pUnit, nullptr);
	}
	pDynamicPath = pUnit->pDynamicPath;
	if (pUnit->dwAnimMode == 0x13)
	{
		if (a4 == 0)
		{
			return 1;
		}
		PATH_RecacheRoomIfNeeded(pDynamicPath);
	}
	PATH_ResetToPreviousType(pDynamicPath);
	pRoom = UNITS_GetRoom(pUnit);
	iVar6 = DUNGEON_IsRoomInTown(pRoom);
	pDVar4 = pSkill;
	if (iVar6 == 0)
	{
		piVar14 = (int*)0x1;
		piVar13 = (int*)0x2;
	}
	else
	{
		piVar14 = (int*)0x5;
		piVar13 = (int*)0x6;
	}
	switch (a1)
	{
	case 0:
		iVar6 = sub_6FB4E580(pUnit, (int)pSkill->pSkillsTxt, (uint32_t)pSkill->pNextSkill);
		if (iVar6 != 0)
		{
			sub_6FB4F410(pUnit, piVar13);
			return 1;
		}
		goto LAB_6fb493bd;
	case 1:
		iVar6 = sub_6FB4DF60(pUnit, (int)(pSkill->pSkillsTxt), (int)(pSkill->pNextSkill));
		if (iVar6 != 0)
		{
			sub_6FB4F410(pUnit, piVar13);
			return 1;
		}
		sub_6FB4F410(pUnit, piVar14);
		pDVar3 = CUNIT_GetPlayer();
		if (pUnit != pDVar3)
		{
			return 0;
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 != 2) && (((int)uVar5 < 4 || (5 < (int)uVar5))))
			goto LAB_6fb493e2;
		iVar6 = pUnit->pDynamicPath->dwClientCoordY;
		goto LAB_6fb491fc;
	case 2:
		sub_6FB4E7E0((uint32_t) * (uint16_t*)&pSkill->pSkillsTxt, (uint32_t)pSkill->pNextSkill);
		return 1;
	default:
		FOG_DisplayAssert("0", __FILE__, __LINE__);
		exit(-1);
	case 6:
		pUnit->dwLastHitClass = pSkill->dwSkillMode;
		sub_6FB4F410(pUnit, (int*)0x4);
		uVar5 = D2C_ZEXT(*(uint16_t*)&pDVar4->pNextSkill);
		uVar10 = extraout_EDX;
		break;
	case 7:
		iVar6 = sub_6FB29550((int*)pUnit);
		sub_6FB294B0((int*)pUnit);
		pUnit->dwFlags = pUnit->dwFlags | 2;
		sub_6FB4F410(pUnit, piVar14);
		if (pSkill == nullptr)
		{
			return 1;
		}
		sub_6FB4E360(pUnit, (uint32_t)pSkill->pSkillsTxt, (uint32_t)pSkill->pNextSkill, iVar6);
		return 1;
	case 8:
		pDVar3 = CUNIT_GetPlayer();
		if (pDVar3 == pUnit)
		{
			sub_6FB23800(1, 0);
		}
		pDVar4 = pSkill;
		pUnit->dwLastHitClass = pSkill->dwSkillMode;
		pDVar3 = sub_6FAB5A20();
		uVar11 = extraout_var_01;
		uVar12 = extraout_var_07;
		if (pDVar3 == pUnit)
		{
			uVar5 = sub_6FAA8B90();
			if (((uVar5 & 8) == 0) && (uVar5 = sub_6FAA8BA0(), (uVar5 & 8) == 0))
			{
				sub_6FAB5D40();
				uVar11 = extraout_var_02;
				uVar12 = extraout_var_08;
			}
			else
			{
				sub_6FAABF30();
				sub_6FAB5A90(nullptr);
				uVar11 = extraout_var_03;
				uVar12 = extraout_var_09;
			}
		}
		sub_6FB4DF90(pUnit, CONCAT22(uVar12, *(uint16_t*)&pDVar4->pSkillsTxt),
		    CONCAT22(uVar11, *(uint16_t*)&pDVar4->pNextSkill), 0, 0, 0);
		sub_6FB4F410(pUnit, nullptr);
		sub_6FB2E680();
		PATH_SetUnitDeadCollision(pUnit, 0);
		sub_6FB29540((int)pUnit);
		pUnit->dwFlags = pUnit->dwFlags & 0xfffffffb;
		iVar6 = STATES_CheckState(pUnit, 7);
		if (iVar6 == 0)
		{
			pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
		}
		sub_6FB59420((int)pUnit);
		sub_6FB5B1D0((int)pUnit, 0);
		STATLIST_SetUnitStat(pUnit, 6, 0, 0);
		if (pUnit->dwUnitType != 0)
		{
			return 1;
		}
		if (pUnit->pPlayerData == nullptr)
		{
			return 1;
		}
		pUnit->pPlayerData->unk0xA8[0x2a] = 0;
		pUnit->pPlayerData->unk0xA8[0x2b] = 0;
		pUnit->pPlayerData->unk0xA8[0x2c] = 0;
		pUnit->pPlayerData->unk0xA8[0x2d] = 0;
		return 1;
	case 9:
		sub_6FB4F410(pUnit, (int*)0x11);
		sub_6FB2E680();
		PATH_SetUnitDeadCollision(pUnit, 0);
		sub_6FB29540((int)pUnit);
		pUnit->dwFlags = pUnit->dwFlags & 0xfffffffb;
		iVar6 = STATES_CheckState(pUnit, 7);
		if (iVar6 == 0)
		{
			pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
		}
		sub_6FB59420((int)pUnit);
		sub_6FB5B1D0((int)pUnit, 0);
		STATLIST_SetUnitStat(pUnit, 6, 0, 0);
		return 1;
	case 0x12:
		pUnit->dwLastHitClass = pSkill->dwSkillMode;
		iVar6 = INVENTORY_GetEquippedShield(pUnit->pInventory, nullptr);
		if ((iVar6 != 0) ||
		    (COMPOSIT_GetWeaponClassId(pUnit, pUnit->pInventory, (int*)&pSkill, -1, 1),
		        uVar11 = extraout_var_05, pSkill == (D2SkillStrc*)0xd))
		{
			sub_6FB4F410(pUnit, (int*)0x9);
			uVar11 = extraout_var_06;
		}
		uVar10 = CONCAT22(uVar11, *(uint16_t*)&pDVar4->pNextSkill);
		uVar5 = uVar10;
		break;
	case 0x13:
		pUnit->dwLastHitClass = pSkill->dwSkillMode;
		sub_6FB4F240(pUnit, 0x13);
		iVar6 = STATES_IsUnitShapeShifted(pUnit);
		piVar13 = (int*)0x3;
		if (iVar6 == 0)
		{
			piVar13 = (int*)0x13;
		}
		sub_6FB50D20(pUnit, piVar13, 1);
		uVar10 = extraout_EDX_00;
		uVar5 = D2C_ZEXT(*(uint16_t*)&pDVar4->pNextSkill);
		break;
	case 0x14:
		pUnit->dwLastHitClass = pSkill->dwSkillMode;
		PATH_RecacheRoomIfNeeded(pDynamicPath);
		PATH_SetType(pDynamicPath, 0xb);
		D2COMMON_10190_PATH_SetDistance(pDynamicPath, 5);
		D2COMMON_10170_PathSetTargetPos(pDynamicPath, (int)pDVar4->pSkillsTxt, (int)pDVar4->pNextSkill);
		D2Common_10142(pDynamicPath, pUnit, 0);
		sub_6FB4F410(pUnit, (int*)0x13);
		return 1;
	case 0x15:
		pSkill = SKILLS_GetSkillById(pUnit, (int)pSkill->pSkillsTxt, (uint32_t)pSkill->pNextSkill);
		if (pSkill == nullptr)
		{
		LAB_6fb49278:
			iVar6 = sub_6FABD400(pUnit, (int*)pDVar4);
			goto LAB_6fb491c3;
		}
		iVar6 = sub_6FB497C0(pUnit, (int*)&pSkill, nullptr);
		if (iVar6 != 0)
		{
			pDVar1 = pDVar4->pSkillsTxt;
			pDVar7 = (D2SkillsTxt*)
			    SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			pDVar4->pSkillsTxt = pDVar7;
			if (pDVar7 != pDVar1)
			{
				pDVar4->pNextSkill = (D2SkillStrc*)0xffffffff;
			}
			goto LAB_6fb49278;
		}
		goto LAB_6fb491cb;
	case 0x16:
		pSkill = SKILLS_GetSkillById(pUnit, (int)pSkill->pSkillsTxt, (uint32_t)pSkill->pNextSkill);
		if (pSkill != nullptr)
		{
			iVar6 = sub_6FB497C0(pUnit, (int*)&pSkill, nullptr);
			if (iVar6 == 0)
				goto LAB_6fb491cb;
			pDVar1 = pDVar4->pSkillsTxt;
			pDVar7 = (D2SkillsTxt*)
			    SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			pDVar4->pSkillsTxt = pDVar7;
			if (pDVar7 != pDVar1)
			{
				pDVar4->pNextSkill = (D2SkillStrc*)0xffffffff;
			}
		}
		iVar6 = sub_6FABD2A0(pUnit, (uint32_t*)pDVar4);
	LAB_6fb491c3:
		if (iVar6 != 0)
		{
			return 1;
		}
	LAB_6fb491cb:
		sub_6FB4F410(pUnit, piVar14);
		pDVar3 = CUNIT_GetPlayer();
		if (pUnit != pDVar3)
		{
			return 0;
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 != 2) && (((int)uVar5 < 4 || (5 < (int)uVar5))))
			goto LAB_6fb493e2;
		iVar6 = pUnit->pDynamicPath->dwClientCoordY;
		goto LAB_6fb491fc;
	case 0x17:
		iVar6 = sub_6FB4DF60(pUnit, (int)(pSkill->pSkillsTxt), (int)(pSkill->pNextSkill));
		if (iVar6 != 0)
		{
			sub_6FB4F410(pUnit, (int*)0x3);
			return 1;
		}
		sub_6FB4F410(pUnit, piVar14);
		pDVar3 = CUNIT_GetPlayer();
		if (pUnit != pDVar3)
		{
			return 0;
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			goto LAB_6fb493fd;
		if (pUnit->pDynamicPath != nullptr)
		{
			iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
			goto LAB_6fb491fc;
		}
		goto LAB_6fb493f6;
	case 0x18:
		iVar6 = sub_6FB4E580(pUnit, (int)pSkill->pSkillsTxt, (uint32_t)pSkill->pNextSkill);
		if (iVar6 != 0)
		{
			sub_6FB4F410(pUnit, (int*)0x3);
			return 1;
		}
	LAB_6fb493bd:
		sub_6FB4F410(pUnit, piVar14);
		pDVar3 = CUNIT_GetPlayer();
		if (pUnit == pDVar3)
		{
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
			LAB_6fb493fd:
				iVar6 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else
			{
			LAB_6fb493e2:
				if (pUnit->pDynamicPath == nullptr)
				{
				LAB_6fb493f6:
					iVar6 = 0;
				}
				else
				{
					iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
			}
		LAB_6fb491fc:
			ppDVar8 = sub_6FAB6A90((int*)pUnit);
			if ((iVar6 != 0) && (ppDVar8 != nullptr))
			{
				sub_6FB4DF90(pUnit, iVar6, (uint32_t)ppDVar8, 0, 0, 0);
			}
		}
		return 0;
	case 0x19:
		sub_6FB4F410(pUnit, (int*)0xd);
		uVar5 = D2C_ZEXT(*(uint16_t*)&pSkill->pNextSkill);
		uVar9 = D2C_ZEXT(*(uint16_t*)&pSkill->pSkillsTxt);
		iVar6 = 0;
		goto LAB_6fb4942f;
	}
	iVar6 = 1;
	uVar9 = CONCAT22((short)(uVar10 >> 0x10), *(uint16_t*)&pDVar4->pSkillsTxt);
LAB_6fb4942f:
	sub_6FB4DF90(pUnit, uVar9, uVar5, iVar6, 0, 0);
	return 1;
}

//D2Client.0x6FB497C0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB497C0(D2UnitStrc* pUnit, int* a2, int* a3)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	D2SkillsTxt* pDVar3;
	D2SkillStrc* pDVar4;
	uint16_t extraout_var;
	uint16_t extraout_var_00;
	uint16_t uVar5;

	pDVar1 = CUNIT_GetPlayer();
	if (pUnit != pDVar1)
	{
		return 1;
	}
	if ((a2 != nullptr) && (*a2 != 0))
	{
		iVar2 = sub_6FB4DA80(pUnit, (D2SkillStrc*)(*a2));
		if (a3 != nullptr)
		{
			*a3 = iVar2;
		}
		pDVar3 = SKILLS_GetSkillsTxtRecordFromSkill((D2SkillStrc*)*a2);
		if (pDVar3 != nullptr)
		{
			uVar5 = extraout_var;
			if ((0 < iVar2) &&
			    (((iVar2 < 3 || (iVar2 == 4)) &&
			        (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)((int)pDVar3->dwFlags + 3)) != 0))))
			{
				pDVar4 = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 0);
				*a2 = (int)pDVar4;
				iVar2 = sub_6FB4DA80(pUnit, pDVar4);
				uVar5 = extraout_var_00;
			}
			if ((iVar2 == 5) || (iVar2 == 0))
			{
				return 1;
			}
			D2_ASSERT(dword_6FB93E0C > iVar2);
			if (*(short*)(byte_6FB93DE8 + iVar2 * 4) != 0)
			{
				sub_6FB514E0(pUnit, CONCAT22(uVar5, *(short*)(byte_6FB93DE8 + iVar2 * 4)));
			}
		}
	}
	return 0;
}

//D2Client.0x6FB498A0
bool __fastcall sub_6FB498A0(D2SkillStrc* pSkill, D2UnitStrc* pUnit2, int* a3, int* a4)
{
	D2UnitStrc* pUnit;
	D2SkillsTxt* pDVar1;
	int iVar2;

	pUnit = CUNIT_GetPlayer();
	if (((pUnit != nullptr) && (pSkill != nullptr)) &&
	    (pUnit2 != nullptr))
	{
		pDVar1 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
		if (pDVar1 != nullptr)
		{
			iVar2 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, pDVar1->dwAuraRangeCalc, (int)pDVar1->nSkillId, iVar2);
			*a3 = iVar2;
			iVar2 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit2);
			*a4 = iVar2;
			return iVar2 <= *a3;
		}
	}
	return false;
}

//D2Client.0x6FB49910
void __cdecl sub_6FB49910()
{
	dword_6FBBC23C = 0;
}

//D2Client.0x6FB49920
// TODO: decompilation needs review (extraout, in_stack)
uint32_t __fastcall sub_6FB49920(uint32_t a1, int a2, int a3, uint8_t a4)
{
	D2DynamicPathStrc* pDynamicPath;
	bool bVar1;
	bool bVar2;
	int iVar3;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	int iVar4;
	uint32_t uVar5;
	D2UnitStrc* pDVar6;
	uint32_t extraout_var_01;
	uint32_t uVar7;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t* puVar8;
	uint32_t in_stack_00000009;
	int local_28;
	int iStack_24;
	uint32_t local_20;
	D2UnitStrc* local_1c;
	D2UnitStrc* local_18;
	int local_14;
	int32_t local_10;
	D2SkillStrc* pDStack_4;

	local_28 = a2;
	iVar3 = sub_6FB23230(9);
	if (iVar3 != 0)
	{
		return 0;
	}
	if ((dword_6FBBC23C != 0) && ((local_28 != 0 || (a3 != 0))))
	{
		return 0;
	}
	dword_6FBBC23C = 1;
	sub_6FAB58B0(&local_28, &a3);
	puVar8 = &local_20;
	for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	local_20 = 0;
	local_1c = CUNIT_GetPlayer();
	local_18 = sub_6FAB5A20();
	local_14 = local_28;
	(*(uint16_t*)((uint8_t*)&local_10 + 0)) = (uint16_t)a3;
	(*(uint16_t*)((uint8_t*)&local_10 + 2)) = (*(uint16_t*)((uint8_t*)&a3 + 2));
	if ((local_18 != nullptr) &&
	    ((uVar5 = local_18->dwUnitType, uVar5 == 2 || (uVar5 == 4))))
	{
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			local_14 = local_18->pDynamicPath->dwClientCoordY;
		}
		else if (local_18->pDynamicPath == nullptr)
		{
			local_14 = 0;
		}
		else
		{
			local_14 = PATH_GetXPosition(local_18->pDynamicPath);
		}
		uVar5 = local_18->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			local_10 = (*(int32_t*)&local_18->pDynamicPath->tTargetCoord);
		}
		else if (local_18->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&local_10 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&local_10 + 2)) = 0;
		}
		else
		{
			local_10 = (int32_t)PATH_GetYPosition(local_18->pDynamicPath);
		}
	}
	uVar5 = (*(uint32_t*)&a4);
	if ((((*(uint32_t*)&a4) & 8) != 0) && (iVar3 = STATLIST_UnitGetStatValue(local_1c, 10, 0), iVar3 != 0))
	{
		local_20 = local_20 | 0x40;
	}
	if ((uVar5 & 4) != 0)
	{
		local_20 = local_20 | 0x20;
	}
	switch (a1)
	{
	case 0:
		if (local_18 == nullptr)
		{
			sub_6FAB5D40();
		}
		else
		{
			sub_6FAB5A90(local_18);
		}
		local_20 = local_20 | 5;
		iVar3 = sub_6FB4B260(&local_20);
		if (iVar3 == 0)
		{
			return 1;
		}
		pDStack_4 = UNITS_GetLeftSkill(local_1c);
		bVar2 = sub_6FB29290(local_1c);
		if (D2C_ZEXT(bVar2) == 0)
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
			pDVar6 = INVENTORY_GetCursorItem(local_1c->pInventory);
			if (pDVar6 == nullptr)
			{
				return 1;
			}
			sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x17), pDVar6->dwUnitId);
			return 0;
		}
		break;
	case 1:
		local_20 = local_20 | 9;
		bVar2 = false;
		iVar3 = sub_6FB4B260(&local_20);
		if (iVar3 == 0)
		{
			return 1;
		}
		pDStack_4 = UNITS_GetLeftSkill(local_1c);
		bVar1 = sub_6FB29290(local_1c);
		if (D2C_ZEXT(bVar1) == 0)
		{
			return 1;
		}
		if (local_1c == nullptr)
		{
			iVar3 = -1;
		}
		else
		{
			iVar3 = local_1c->dwClassId;
		}
		UNITS_GetRunAndWalkSpeedForPlayer((int)local_1c, iVar3, (int*)&a4, &iStack_24);
		(*(uint32_t*)&a4) = (*(uint32_t*)&a4) << 8;
		pDynamicPath = local_1c->pDynamicPath;
		iVar3 = STATLIST_UnitGetStatValue(local_1c, 0x43, 0);
		iVar3 = iVar3 * (*(uint32_t*)&a4);
		iVar4 = PATH_GetVelocity(pDynamicPath);
		if (iVar4 == iVar3 / 100)
		{
			if ((local_20 & 0x40) != 0)
			{
			LAB_6fb49bbb:
				bVar2 = true;
			}
		}
		else if ((local_20 & 0x40) == 0)
			goto LAB_6fb49bbb;
		if (local_18 == nullptr)
		{
			if ((local_20 & 0x20) != 0)
				goto LAB_6fb49d04;
			iVar3 = sub_6FB4B760((int*)local_1c);
			if (iVar3 != 0)
			{
			switchD_6fb49a6a_default:
				return 1;
			}
		}
		else
		{
			pDVar6 = sub_6FB296A0((int)local_1c);
			if ((local_18 == pDVar6) && (!bVar2))
				goto LAB_6fb49d04;
			PATH_SetTargetUnit(pDynamicPath, local_18);
		}
		break;
	case 2:
		sub_6FAB5D40();
		local_20 = local_20 | 0x11;
		sub_6FB4B260(&local_20);
		uVar5 = sub_6FAB1920((int)local_1c, 7, 0);
		if ((uVar5 != 0xffffffff) &&
		    ((pDVar6 = sub_6FB269F0(uVar5, 1), pDVar6 != nullptr &&
		                                           (iVar3 = sub_6FAB18D0(uVar5), *(int*)(iVar3 + 8) == 2))))
		{
			sub_6FAB6430((int)local_1c, (int)pDVar6, 0);
		}
		sub_6FB49D70((int)&local_20);
		return 0;
	case 3:
		if (local_18 == nullptr)
		{
			sub_6FAB5D40();
		}
		else
		{
			sub_6FAB5A90(local_18);
		}
		local_20 = local_20 | 6;
		iVar3 = sub_6FB4B260(&local_20);
		if (iVar3 == 0)
		{
			return 1;
		}
		pDStack_4 = UNITS_GetRightSkill(local_1c);
		bVar2 = sub_6FB29290(local_1c);
		if (D2C_ZEXT(bVar2) == 0)
		{
			return 1;
		}
		iVar3 = SKILLS_GetSkillIdFromSkill(pDStack_4, __FILE__, __LINE__);
		iVar3 = sub_6FB14AE0(iVar3);
		if ((*(char*)(iVar3 + 0x14) != '\x01') || ((local_20 & 0x40) != 0))
			goto LAB_6fb49d04;
		break;
	case 4:
		local_20 = local_20 | 10;
		uVar7 = sub_6FB4B2D0(&local_20);
		return uVar7;
	case 5:
		sub_6FAB5D40();
		local_20 = local_20 | 0x12;
		uVar7 = sub_6FB4B360(&local_20);
		return uVar7;
	default:
		goto switchD_6fb49a6a_default;
	}
	local_20 = local_20 | 0x80;
LAB_6fb49d04:
	sub_6FB49DF0(&local_20);
	return 1;
}

//D2Client.0x6FB49D70
void __fastcall sub_6FB49D70(int a1)
{
	D2UnitStrc* pUnit;
	D2DynamicPathStrc* pDynamicPath;
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;

	pUnit = *(D2UnitStrc**)(a1 + 4);
	if (pUnit == nullptr)
	{
		return;
	}
	if (pUnit->dwUnitType != 0)
	{
		return;
	}
	pDVar1 = sub_6FB296A0((int)pUnit);
	if (pDVar1 != nullptr)
	{
		return;
	}
	uVar4 = pUnit->dwAnimMode;
	if (uVar4 != 2)
	{
		if (uVar4 == 3)
		{
			uVar4 = 3;
			goto LAB_6fb49da2;
		}
		if (uVar4 != 6)
		{
			return;
		}
	}
	uVar4 = 1;
LAB_6fb49da2:
	pDynamicPath = pUnit->pDynamicPath;
	D2COMMON_10170_PathSetTargetPos(pDynamicPath, *(int*)(a1 + 0xc), *(int*)(a1 + 0x10));
	iVar2 = D2Common_10142(pDynamicPath, pUnit, 0);
	if (iVar2 != 0)
	{
		uVar3 = D2COMMON_10177_PATH_GetLastPointX(pDynamicPath);
		iVar2 = D2COMMON_10178_PATH_GetLastPointY(pDynamicPath);
		sub_6FB4EA90(uVar4, pUnit, uVar3, iVar2, 0);
	}
}

//D2Client.0x6FB49DF0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB49DF0(uint32_t* a1)
{
	uint32_t* puVar1;
	uint32_t* puVar2;
	D2UnitStrc* pUnit;
	D2DynamicPathStrc* pDVar3;
	D2SkillStrc* pSkill;
	uint32_t uVar4;
	bool bVar5;
	int iVar6;
	D2SkillsTxt* pDVar7;
	D2ActiveRoomStrc* pDVar8;
	uint32_t uVar9;
	D2UnitStrc* pDVar10;
	uint32_t uVar11;
	int* piVar12;
	uint32_t uVar13;
	D2ObjectsTxt* pDVar14;
	uint32_t uVar15;
	uint32_t extraout_ECX;
	uint32_t uVar16;
	D2SkillsTxt* pDStack_c;
	int iStack_4;

	iVar6 = D2Common_11016((D2UnitStrc*)a1[1], (D2SkillStrc*)a1[7]);
	if ((((D2SkillStrc*)a1[7] != nullptr) && ((*a1 & 2) != 0)) && (iVar6 != 1))
	{
		pDVar7 = SKILLS_GetSkillsTxtRecordFromSkill((D2SkillStrc*)a1[7]);
		if (pDVar7 == nullptr)
		{
			return;
		}
		pDVar8 = UNITS_GetRoom((D2UnitStrc*)a1[1]);
		if ((((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)((int)pDVar7->dwFlags + 1)) == 0) &&
		    (iVar6 = DUNGEON_IsRoomInTown(pDVar8), iVar6 != 0))
		{
			sub_6FB514E0((D2UnitStrc*)a1[1], 0x18);
			return;
		}
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & (uint8_t)pDVar7->dwFlags[0]) != 0)
		{
			return;
		}
	}
	if ((*a1 & 0x40) == 0)
	{
		a1[5] = 1;
		a1[6] = 2;
	}
	else
	{
		a1[5] = 3;
		a1[6] = 4;
	}
	piVar12 = (int*)a1[1];
	if (((piVar12 != nullptr) && (*piVar12 == 0)) &&
	    ((piVar12[5] != 0 && (iVar6 = *(int*)(piVar12[5] + 0x154), iVar6 != 0))))
	{
		if (iVar6 == 0x13)
		{
			iVar6 = sub_6FB4B780(piVar12);
			uVar9 = sub_6FB4B7A0((int*)a1[1]);
			pDVar10 = sub_6FB269F0(uVar9, iVar6);
			if (pDVar10 == nullptr)
				goto LAB_6fb49ed6;
			piVar12 = (int*)a1[1];
		}
		sub_6FAFBB10(piVar12);
	}
LAB_6fb49ed6:
	if (a1[7] == 0)
	{
		return;
	}
	uVar9 = *a1;
	uVar11 = uVar9 >> 5 & 1;
	if (((uVar9 & 2) != 0) && (a1[2] == 0))
	{
		uVar11 = 1;
	}
	puVar1 = a1 + 4;
	puVar2 = a1 + 3;
	piVar12 = sub_6FAB6490((D2SkillStrc*)(a1[7]), (int*)a1[2], (int*)puVar2, (int*)puVar1, (uint8_t)uVar9, uVar11);
	a1[2] = (uint32_t)piVar12;
	iVar6 = sub_6FB57CC0();
	if (iVar6 == 6)
	{
		sub_6FB23A40();
	}
	else
	{
		iVar6 = sub_6FB57CC0();
		if (iVar6 == 8)
		{
			sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4c), 0xffffffff);
		}
	}
	pDVar10 = (D2UnitStrc*)a1[1];
	uVar9 = *a1;
	pUnit = (D2UnitStrc*)a1[2];
	bVar5 = false;
	iStack_4 = D2Common_11016(pDVar10, (D2SkillStrc*)a1[7]);
	pDStack_c = nullptr;
	if ((((D2SkillStrc*)a1[7] != nullptr) &&
	        (pDStack_c = SKILLS_GetSkillsTxtRecordFromSkill((D2SkillStrc*)a1[7]),
	            pDStack_c == nullptr)) ||
	    (pUnit == nullptr))
		goto LAB_6fb49fec;
	if (pDStack_c == nullptr)
	{
	LAB_6fb4a12a:
		uVar11 = pUnit->dwUnitType;
		uVar4 = pUnit->dwUnitId;
		if ((bVar5) ||
		    ((((uVar11 != 2 && (((int)uVar11 < 4 || (5 < (int)uVar11)))) || ((uVar9 & 2) == 0)) ||
		        (iStack_4 == 1))))
		{
			puVar1 = a1 + 7;
			iVar6 = SKILLS_GetSkillModeFromUnit(pDVar10, (D2SkillStrc*)a1[7]);
			if (iVar6 == 0)
			{
				if ((uVar9 & 0x20) != 0)
				{
					return;
				}
			}
			else
			{
				if ((((D2SkillStrc*)*puVar1 != nullptr) &&
				        (pDVar7 = SKILLS_GetSkillsTxtRecordFromSkill((D2SkillStrc*)*puVar1),
				            pDVar7 != nullptr)) &&
				    (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)((int)pDVar7->dwFlags + 3)) != 0))
				{
					iVar6 = sub_6FB497C0((D2UnitStrc*)a1[1], (int*)puVar1, nullptr);
					if (iVar6 == 0)
					{
						return;
					}
					sub_6FB4A570(a1, 1);
					return;
				}
				uVar13 = pUnit->dwFlags >> 2 & 1;
				if (uVar13 != 0)
				{
					uVar16 = (uint32_t) * (uint8_t*)((int)pDStack_c->dwFlags + 3);
					if (((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4) & uVar16) == 0) &&
					    ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 8) & uVar16) == 0))
					{
						uVar13 = sub_6FB29D80(pDVar10, pUnit);
					}
					if (uVar13 != 0)
					{
						if (uVar11 != 2)
						{
							if (uVar11 != 0)
							{
								pDVar8 = UNITS_GetRoom(pUnit);
								iVar6 = DUNGEON_IsRoomInTown(pDVar8);
								if (iVar6 == 0)
								{
									sub_6FB4A710(a1, uVar11, uVar4);
									return;
								}
								if ((D2SkillStrc*)*puVar1 == nullptr)
								{
									return;
								}
								iVar6 = SKILLS_GetSkillIdFromSkill((D2SkillStrc*)*puVar1,
								    __FILE__, __LINE__);
								if ((iVar6 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar6))
								{
									iVar6 = 0;
								}
								else
								{
									iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar6 * 0x23c;
								}
								if (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar6 + 5)) == 0)
								{
									return;
								}
								sub_6FB4A710(a1, uVar11, uVar4);
								return;
							}
							pDVar8 = UNITS_GetRoom(pUnit);
							iVar6 = DUNGEON_IsRoomInTown(pDVar8);
							if (iVar6 != 0)
							{
								pDVar8 = UNITS_GetRoom(pDVar10);
								iVar6 = DUNGEON_IsRoomInTown(pDVar8);
								if (iVar6 != 0)
								{
									uVar9 = D2Common_10399((D2UnitStrc*)a1[2], (D2UnitStrc*)a1[1]);
									if ((uVar9 < 3) &&
									    (iVar6 = UNITS_TestCollisionBetweenInteractingUnits((D2UnitStrc*)a1[2], (D2UnitStrc*)a1[1], 0x804),
									        iVar6 == 0))
									{
										sub_6FB4EA90(0x13, (D2UnitStrc*)a1[1], 0, uVar4, 0);
										return;
									}
									sub_6FB4EA90(a1[6], (D2UnitStrc*)a1[1], 0, uVar4, 0);
									piVar12 = (int*)a1[1];
									if (piVar12 == nullptr)
									{
										return;
									}
									if (*piVar12 != 0)
									{
										return;
									}
									if (piVar12[5] == 0)
									{
										return;
									}
									*(uint32_t*)(piVar12[5] + 0x150) = 1;
									*(uint32_t*)(piVar12[5] + 0x154) = 0x13;
									*(uint32_t*)(piVar12[5] + 0x158) = 0;
									*(uint32_t*)(piVar12[5] + 0x15c) = uVar4;
									return;
								}
							}
							sub_6FB4A710(a1, 0, uVar4);
							return;
						}
						if ((uVar9 & 0x20) != 0)
						{
							return;
						}
						pDVar10 = sub_6FB269F0(uVar4, 2);
						if (pDVar10 == nullptr)
						{
							return;
						}
						pDVar14 = DATATBLS_GetObjectsTxtRecord(pDVar10->dwClassId);
						D2_ASSERT(pDVar14 != nullptr);
						bVar5 = true;
						if (pDVar10->dwClassId == 0x3b)
						{
							iVar6 = 0x66;
							pDVar10 = CUNIT_GetPlayer();
							iVar6 = STATES_CheckState(pDVar10, iVar6);
							if (iVar6 != 0)
							{
								bVar5 = false;
							}
						}
						iVar6 = UNITS_IsObjectInInteractRange((D2UnitStrc*)a1[1], (D2UnitStrc*)a1[2]);
						if ((iVar6 != 0) &&
						    (iVar6 = UNITS_TestCollisionBetweenInteractingUnits((D2UnitStrc*)a1[1], (D2UnitStrc*)a1[2], 0x804),
						        iVar6 == 0))
						{
							if (!bVar5)
							{
								return;
							}
							sub_6FB4EA90(0x13, (D2UnitStrc*)a1[1], 2, uVar4, 0);
							return;
						}
						piVar12 = (int*)a1[2];
						iVar6 = *piVar12;
						if ((iVar6 == 2) || ((3 < iVar6 && (iVar6 < 6))))
						{
							iVar6 = *(int*)(piVar12[0xb] + 0x10);
						}
						else if ((D2DynamicPathStrc*)piVar12[0xb] == nullptr)
						{
							iVar6 = 0;
						}
						else
						{
							iVar6 = PATH_GetYPosition((D2DynamicPathStrc*)piVar12[0xb]);
						}
						uVar15 = sub_6FAB6A60((int*)a1[2]);
						sub_6FB4A6B0(a1[5], (D2UnitStrc*)a1[1], uVar15, iVar6);
						if (!bVar5)
						{
							return;
						}
						sub_6FB4B720(0x13, (int*)a1[1], 2, uVar4);
						return;
					}
				}
				if ((uVar9 & 0x20) != 0)
				{
					iVar6 = sub_6FB497C0((D2UnitStrc*)a1[1], (int*)puVar1, nullptr);
					if (iVar6 == 0)
					{
						return;
					}
					sub_6FB4A570(a1, 0);
					return;
				}
			}
			if (uVar11 != 1)
			{
				sub_6FB4AA50((uint8_t*)a1, uVar11, uVar4);
				return;
			}
			if ((uVar9 & 4) != 0)
			{
				iVar6 = pUnit->dwClassId;
				if ((((-1 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
				        (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar6 * 0x1a8, iVar6 != 0)) &&
				    (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar6 + 0xd)) != 0))
				{
					sub_6FB4AA50((uint8_t*)a1, 1, uVar4);
					return;
				}
				sub_6FB4EA90(a1[6], pDVar10, 1, uVar4, 0);
			}
		}
	}
	else
	{
		if (((*a1 & 2) == 0) || (iStack_4 == 1))
		{
		LAB_6fb49fbd:
			if (((pUnit->dwUnitType != 1) || (iVar6 = sub_6FB29550((int*)pUnit), iVar6 == 0)) ||
			    (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)((int)pDStack_c->dwFlags + 3)) != 0))
				goto LAB_6fb4a12a;
		}
		else
		{
			uVar11 = pUnit->dwUnitType;
			if ((uVar11 == 2) || (uVar11 == 4))
			{
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)((int)pDStack_c->dwFlags + 3)) != 0)
				{
					bVar5 = true;
					goto LAB_6fb49fbd;
				}
			}
			else if (uVar11 != 5)
				goto LAB_6fb49fbd;
		}
	LAB_6fb49fec:
		if (((uVar9 & 0x20) == 0) && (((uVar9 & 2) == 0 || (iStack_4 == 1))))
		{
			iVar6 = sub_6FB4B0A0((int*)a1[1], a1);
			if (iVar6 != 0)
			{
				pDVar3 = pDVar10->pDynamicPath;
				uVar9 = a1[5];
				D2COMMON_10170_PathSetTargetPos(pDVar3, *puVar2, *puVar1);
				iVar6 = D2Common_10142(pDVar3, pDVar10, 0);
				if (iVar6 != 0)
				{
					uVar11 = D2COMMON_10177_PATH_GetLastPointX(pDVar3);
					iVar6 = D2COMMON_10178_PATH_GetLastPointY(pDVar3);
					sub_6FB4EA90(uVar9, pDVar10, uVar11, iVar6, 0);
				}
				sub_6FAB5A90(nullptr);
				return;
			}
		}
		else
		{
			iStack_4 = 0;
			iVar6 = sub_6FB497C0((D2UnitStrc*)a1[1], (int*)(a1 + 7), &iStack_4);
			if (iVar6 != 0)
			{
				pSkill = (D2SkillStrc*)a1[7];
				if ((((pSkill == nullptr) ||
				         (iVar6 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__),
				             iVar6 != 0)) ||
				        (iStack_4 != 1)) ||
				    ((uVar9 & 0x20) != 0))
				{
					sub_6FB4A570(a1, 0);
					sub_6FAB5A90(nullptr);
					return;
				}
				iVar6 = sub_6FB4B0A0((int*)a1[1], a1);
				if (iVar6 != 0)
				{
					pDVar3 = pDVar10->pDynamicPath;
					uVar9 = a1[5];
					D2COMMON_10170_PathSetTargetPos(pDVar3, *puVar2, *puVar1);
					iVar6 = D2Common_10142(pDVar3, pDVar10, 0);
					if (iVar6 != 0)
					{
						uVar11 = D2COMMON_10177_PATH_GetLastPointX(pDVar3);
						iVar6 = D2COMMON_10178_PATH_GetLastPointY(pDVar3);
						sub_6FB4EA90(uVar9, pDVar10, uVar11, iVar6, 0);
					}
					sub_6FAB5A90(nullptr);
					return;
				}
			}
		}
	}
}

//D2Client.0x6FB4A570
void __fastcall sub_6FB4A570(uint32_t* a1, int a2)
{
	uint32_t* puVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;

	iVar3 = sub_6FB24780();
	iVar4 = sub_6FB57BD0();
	if (iVar4 <= iVar3)
	{
		if (a2 == 1)
		{
			puVar1 = (uint32_t*)a1[2];
			uVar7 = 6;
			if (puVar1 == nullptr)
			{
				uVar8 = 0xffffffff;
			}
			else
			{
				uVar7 = *puVar1;
				uVar8 = puVar1[3];
			}
			uVar6 = *a1;
			if ((uVar6 & 1) != 0)
			{
				if ((uVar6 & 0x20) == 0)
				{
					uVar5 = 9;
					if ((uVar6 & 8) == 0)
					{
						uVar5 = 6;
					}
				}
				else if ((uVar6 & 8) == 0)
				{
					uVar5 = 7;
				}
				else
				{
					uVar5 = 10;
				}
				sub_6FB4EA90(uVar5, (D2UnitStrc*)a1[1], uVar7, uVar8, 0);
			}
			uVar6 = *a1;
			if ((uVar6 & 2) != 0)
			{
				pDVar2 = (D2UnitStrc*)a1[1];
				if ((uVar6 & 0x20) == 0)
				{
					if ((uVar6 & 8) != 0)
					{
						sub_6FB4EA90(0x10, pDVar2, uVar7, uVar8, 0);
						return;
					}
					sub_6FB4EA90(0xd, pDVar2, uVar7, uVar8, 0);
					return;
				}
				if ((uVar6 & 8) != 0)
				{
					sub_6FB4EA90(0x11, pDVar2, uVar7, uVar8, 0);
					return;
				}
				sub_6FB4EA90(0xe, pDVar2, uVar7, uVar8, 0);
				return;
			}
		}
		else
		{
			if ((*a1 & 1) != 0)
			{
				if ((*a1 & 8) == 0)
				{
					uVar7 = a1[4];
					uVar8 = a1[3];
					uVar6 = 5;
				}
				else
				{
					uVar7 = a1[4];
					uVar8 = a1[3];
					uVar6 = 8;
				}
				sub_6FB4EA90(uVar6, (D2UnitStrc*)a1[1], uVar8, uVar7, 0);
			}
			if ((*a1 & 2) != 0)
			{
				if ((*a1 & 8) != 0)
				{
					sub_6FB4EA90(0xf, (D2UnitStrc*)a1[1], a1[3], a1[4], 0);
					return;
				}
				sub_6FB4EA90(0xc, (D2UnitStrc*)a1[1], a1[3], a1[4], 0);
			}
		}
	}
}

//D2Client.0x6FB4A6B0
uint32_t __fastcall sub_6FB4A6B0(uint32_t a1, D2UnitStrc* pUnit, int a3, int a4)
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	uint32_t uVar2;

	pDynamicPath = pUnit->pDynamicPath;
	D2COMMON_10170_PathSetTargetPos(pDynamicPath, a3, a4);
	iVar1 = D2Common_10142(pDynamicPath, pUnit, 0);
	if (iVar1 == 0)
	{
		return 0;
	}
	uVar2 = D2COMMON_10177_PATH_GetLastPointX(pDynamicPath);
	iVar1 = D2COMMON_10178_PATH_GetLastPointY(pDynamicPath);
	sub_6FB4EA90(a1, pUnit, uVar2, iVar1, 0);
	return 1;
}

//D2Client.0x6FB4A710
void __fastcall sub_6FB4A710(uint32_t* a1, uint32_t a2, uint32_t a3)
{
	uint32_t* puVar1;
	D2SkillStrc* pSkill;
	int* piVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	D2SkillsTxt* pDVar6;
	D2UnitStrc* pUnit;
	D2UnitStrc** ppDVar7;
	int iVar8;
	D2UnitStrc** ppDVar9;
	int iStack_8;

	puVar1 = a1 + 7;
	iVar3 = sub_6FB497C0((D2UnitStrc*)a1[1], (int*)puVar1, nullptr);
	if (iVar3 != 0)
	{
		iVar3 = D2Common_11016((D2UnitStrc*)a1[1], (D2SkillStrc*)*puVar1);
		pDVar4 = sub_6FB269F0(a3, a2);
		if (pDVar4 != nullptr)
		{
			iVar5 = UNITS_IsInMovingModeEx(pDVar4);
			iVar5 = UNITS_IsInMeleeRange((D2UnitStrc*)a1[1], (D2UnitStrc*)a1[2], iVar5);
			if (iVar5 != 0)
			{
				sub_6FB4A570(a1, 1);
				return;
			}
			if ((D2SkillStrc*)*puVar1 != nullptr)
			{
				pDVar6 = SKILLS_GetSkillsTxtRecordFromSkill((D2SkillStrc*)*puVar1);
				if ((pDVar6 != nullptr) && (pDVar6->wSrvDoFunc == 0x13))
				{
					pDVar4 = (D2UnitStrc*)a1[2];
					iVar3 = 0;
					iStack_8 = 0;
					D2_ASSERT(pDVar4 != nullptr);
					D2_ASSERT(a1[1]);
					if ((*a1 & 0x20) != 0)
					{
						sub_6FB4A570(a1, 1);
						return;
					}
					pSkill = (D2SkillStrc*)*puVar1;
					pUnit = CUNIT_GetPlayer();
					if (((pUnit != nullptr) && (pSkill != nullptr)) &&
					    (pDVar4 != nullptr))
					{
						pDVar6 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
						if (pDVar6 != nullptr)
						{
							iVar3 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
							iStack_8 = SKILLS_EvaluateSkillFormula(pUnit, pDVar6->dwAuraRangeCalc, (int)pDVar6->nSkillId, iVar3);
							iVar3 = UNITS_GetDistanceToOtherUnit(pUnit, pDVar4);
							if (iVar3 <= iStack_8)
							{
								sub_6FB4A570(a1, 1);
								return;
							}
						}
					}
					if ((*a1 & 1) != 0)
					{
						sub_6FB4B720(6, (int*)a1[1], a2, a3);
					}
					if ((*a1 & 2) != 0)
					{
						sub_6FB4B720(0xd, (int*)a1[1], a2, a3);
					}
					iStack_8 = iVar3 - iStack_8;
					D2_ASSERT(iStack_8 >= 1);
					D2_ASSERT(iVar3);
					iVar5 = sub_6FAB6A60((int*)a1[1]);
					ppDVar7 = sub_6FAB6A90((int*)a1[1]);
					iVar8 = sub_6FAB6A60((int*)a1[2]);
					ppDVar9 = sub_6FAB6A90((int*)a1[2]);
					sub_6FB4A6B0(a1[5], (D2UnitStrc*)a1[1],
					    ((iVar8 - iVar5) * iStack_8) / iVar3 + iVar5,
					    (((int)ppDVar9 - (int)ppDVar7) * iStack_8) / iVar3 + (int)ppDVar7);
					return;
				}
			}
			if ((iVar3 != 1) && (iVar3 != 4))
			{
				sub_6FB4A570(a1, 1);
				return;
			}
			if ((*a1 & 0x20) == 0)
			{
				sub_6FB4EA90(a1[6], (D2UnitStrc*)a1[1], a2, a3, 0);
				if (((((*a1 & 1) != 0) && (piVar2 = (int*)a1[1], piVar2 != nullptr)) &&
				        (*piVar2 == 0)) &&
				    (piVar2[5] != 0))
				{
					*(uint32_t*)(piVar2[5] + 0x150) = 1;
					*(uint32_t*)(piVar2[5] + 0x154) = 6;
					*(uint32_t*)(piVar2[5] + 0x158) = a2;
					*(uint32_t*)(piVar2[5] + 0x15c) = a3;
				}
				if ((((*a1 & 2) != 0) && (piVar2 = (int*)a1[1], piVar2 != nullptr)) &&
				    ((*piVar2 == 0 && (piVar2[5] != 0))))
				{
					*(uint32_t*)(piVar2[5] + 0x150) = 1;
					*(uint32_t*)(piVar2[5] + 0x154) = 0xd;
					*(uint32_t*)(piVar2[5] + 0x158) = a2;
					*(uint32_t*)(piVar2[5] + 0x15c) = a3;
					return;
				}
			}
			else
			{
				sub_6FB4A570(a1, 0);
			}
		}
	}
}

//D2Client.0x6FB4AA50
void __fastcall sub_6FB4AA50(uint8_t* a1, uint32_t a2, int a3)
{
	uint8_t* pbVar1;
	D2DynamicPathStrc* pDynamicPath;
	int* piVar2;
	uint32_t* puVar3;
	bool bVar4;
	bool bVar5;
	D2UnitStrc* pUnit;
	D2UnitStrc* pDVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	int iVar9;
	int iVar10;
	uint32_t uVar11;
	uint32_t uVar12;
	int iVar13;
	int iStack_8;

	pUnit = CUNIT_GetPlayer();
	pDVar6 = *(D2UnitStrc**)(a1 + 8);
	if (pDVar6 != nullptr)
	{
		switch (pDVar6->dwUnitType)
		{
		case 0:
			iVar9 = D2Common_10399(pDVar6, *(D2UnitStrc**)(a1 + 4));
			if ((4 < iVar9) ||
			    (iVar9 = UNITS_TestCollisionBetweenInteractingUnits(*(D2UnitStrc**)(a1 + 4), *(D2UnitStrc**)(a1 + 8), 0x804),
			        iVar9 != 0))
			{
				sub_6FB4EA90(*(uint32_t*)(a1 + 0x18), *(D2UnitStrc**)(a1 + 4), a2, a3, 0);
				piVar2 = *(int**)(a1 + 4);
				if (piVar2 == nullptr)
				{
					return;
				}
				if (*piVar2 != 0)
				{
					return;
				}
				if (piVar2[5] == 0)
				{
					return;
				}
				*(uint32_t*)(piVar2[5] + 0x150) = 1;
				*(uint32_t*)(piVar2[5] + 0x154) = 0x13;
				*(uint32_t*)(piVar2[5] + 0x158) = a2;
				*(int*)(piVar2[5] + 0x15c) = a3;
				return;
			}
			goto LAB_6fb4b071;
		case 1:
			if (((pDVar6 == nullptr) || (iVar9 = pDVar6->dwClassId, iVar9 < 0)) ||
			    ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar9 ||
			        ((iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar9 * 0x1a8, iVar9 == 0 ||
			                                                                                           (iVar13 = 2, ((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar9 + 0xd)) == 0))))))
				goto switchD_6fb4aa82_caseD_3;
			goto LAB_6fb4aed8;
		case 2:
			if ((*a1 & 8) != 0)
			{
				return;
			}
			if (pDVar6 == nullptr)
			{
				iVar9 = -1;
			}
			else
			{
				iVar9 = pDVar6->dwClassId;
			}
			DATATBLS_GetObjectsTxtRecord(iVar9);
			bVar4 = true;
			bVar5 = true;
			if (((*(int*)(a1 + 8) != 0) && (*(int*)(*(int*)(a1 + 8) + 4) == 0x3b)) &&
			    (iVar9 = STATES_CheckState(pUnit, 0x66), iVar9 != 0))
			{
				bVar4 = false;
				bVar5 = false;
			}
			iVar9 = UNITS_IsObjectInInteractRange(*(D2UnitStrc**)(a1 + 4), *(D2UnitStrc**)(a1 + 8));
			if ((iVar9 == 0) ||
			    (iVar9 = UNITS_TestCollisionBetweenInteractingUnits(*(D2UnitStrc**)(a1 + 4), *(D2UnitStrc**)(a1 + 8), 0x804),
			        iVar9 != 0))
			{
				pDVar6 = CUNIT_GetPlayer();
				if ((pDVar6 != nullptr) &&
				    (((pDVar6->dwUnitType == 0 && (pDVar6->pPlayerData != nullptr)) &&
				        (pDVar6->pPlayerData->unk0xA8[0x2b] == 0x13))))
				{
					uVar7 = sub_6FB4B780((int*)pDVar6);
					iVar9 = sub_6FB4B7A0((int*)pDVar6);
					if ((uVar7 == a2) && (iVar9 == a3))
					{
						return;
					}
				}
				piVar2 = *(int**)(a1 + 8);
				iVar9 = *piVar2;
				if ((iVar9 == 2) || ((3 < iVar9 && (iVar9 < 6))))
				{
					iStack_8 = *(int*)(piVar2[0xb] + 0x10);
				}
				else if ((D2DynamicPathStrc*)piVar2[0xb] == nullptr)
				{
					iStack_8 = 0;
				}
				else
				{
					iStack_8 = PATH_GetYPosition((D2DynamicPathStrc*)piVar2[0xb]);
				}
				piVar2 = *(int**)(a1 + 8);
				iVar9 = *piVar2;
				if ((iVar9 == 2) || ((3 < iVar9 && (iVar9 < 6))))
				{
					iVar9 = *(int*)(piVar2[0xb] + 0xc);
				}
				else if ((D2DynamicPathStrc*)piVar2[0xb] == nullptr)
				{
					iVar9 = 0;
				}
				else
				{
					iVar9 = PATH_GetXPosition((D2DynamicPathStrc*)piVar2[0xb]);
				}
				pDVar6 = *(D2UnitStrc**)(a1 + 4);
				uVar7 = *(uint32_t*)(a1 + 0x14);
				pDynamicPath = pDVar6->pDynamicPath;
				D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar9, iStack_8);
				iVar9 = D2Common_10142(pDynamicPath, pDVar6, 0);
				if (iVar9 != 0)
				{
					uVar8 = D2COMMON_10177_PATH_GetLastPointX(pDynamicPath);
					iVar9 = D2COMMON_10178_PATH_GetLastPointY(pDynamicPath);
					sub_6FB4EA90(uVar7, pDVar6, uVar8, iVar9, 0);
				}
				if (!bVar5)
				{
					return;
				}
				piVar2 = *(int**)(a1 + 4);
				if (((piVar2 != nullptr) && (*piVar2 == 0)) && (piVar2[5] != 0))
				{
					*(uint32_t*)(piVar2[5] + 0x150) = 1;
					*(uint32_t*)(piVar2[5] + 0x154) = 0x13;
					*(uint32_t*)(piVar2[5] + 0x158) = a2;
					*(int*)(piVar2[5] + 0x15c) = a3;
					sub_6FAA8B80();
					return;
				}
				goto LAB_6fb4aca3;
			}
			if (!bVar4)
			{
				return;
			}
			break;
		default:
			goto switchD_6fb4aa82_caseD_3;
		case 4:
			if ((*a1 & 8) != 0)
			{
				return;
			}
			iVar9 = D2Common_10399(pDVar6, *(D2UnitStrc**)(a1 + 4));
			if ((4 < iVar9) ||
			    (iVar9 = UNITS_TestCollisionBetweenInteractingUnits(*(D2UnitStrc**)(a1 + 4), *(D2UnitStrc**)(a1 + 8), 0x804),
			        iVar9 != 0))
			{
				pDVar6 = CUNIT_GetPlayer();
				if (((pDVar6 != nullptr) &&
				        ((pDVar6->dwUnitType == 0 && (pDVar6->pPlayerData != nullptr)))) &&
				    (pDVar6->pPlayerData->unk0xA8[0x2b] == 0x13))
				{
					uVar7 = sub_6FB4B780((int*)pDVar6);
					iVar9 = sub_6FB4B7A0((int*)pDVar6);
					if ((uVar7 == a2) && (iVar9 == a3))
					{
						return;
					}
				}
				sub_6FB4EA90(*(uint32_t*)(a1 + 0x18), *(D2UnitStrc**)(a1 + 4), a2, a3, 0);
				piVar2 = *(int**)(a1 + 4);
				if (((piVar2 != nullptr) && (*piVar2 == 0)) && (piVar2[5] != 0))
				{
					*(uint32_t*)(piVar2[5] + 0x150) = 1;
					*(uint32_t*)(piVar2[5] + 0x154) = 0x13;
					*(uint32_t*)(piVar2[5] + 0x158) = a2;
					*(int*)(piVar2[5] + 0x15c) = a3;
					sub_6FAA8B80();
					return;
				}
				goto LAB_6fb4aca3;
			}
			break;
		case 5:
			uVar7 = sub_6FAABFA0();
			uVar8 = sub_6FAABF90();
			if (uVar8 < uVar7)
			{
				return;
			}
			iVar9 = D2Common_10399(*(D2UnitStrc**)(a1 + 8), *(D2UnitStrc**)(a1 + 4));
			if (iVar9 < 5)
			{
				sub_6FB4EA90(0x13, *(D2UnitStrc**)(a1 + 4), a2, a3, 0);
			}
			else
			{
				sub_6FB4EA90(*(uint32_t*)(a1 + 0x18), *(D2UnitStrc**)(a1 + 4), a2, a3, 0);
				piVar2 = *(int**)(a1 + 4);
				if (((piVar2 != nullptr) && (*piVar2 == 0)) && (piVar2[5] != 0))
				{
					*(uint32_t*)(piVar2[5] + 0x150) = 1;
					*(uint32_t*)(piVar2[5] + 0x154) = 0x13;
					*(uint32_t*)(piVar2[5] + 0x158) = a2;
					*(int*)(piVar2[5] + 0x15c) = a3;
				}
			}
			iVar9 = sub_6FAABF90();
			sub_6FAABFB0(iVar9 + 500);
			return;
		}
		sub_6FB4EA90(0x13, *(D2UnitStrc**)(a1 + 4), a2, a3, 0);
	LAB_6fb4aca3:
		sub_6FAA8B80();
		return;
	}
switchD_6fb4aa82_caseD_3:
	iVar13 = 5;
LAB_6fb4aed8:
	if (((((pDVar6 != nullptr) && (pDVar6->dwUnitType == 1)) &&
	         (pDVar6 != nullptr)) &&
	        ((iVar9 = pDVar6->dwClassId, -1 < iVar9 &&
	                                         (iVar9 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))))) &&
	    ((iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar9 * 0x1a8, iVar9 != 0 &&
	                                                                                       ((uVar7 = (uint32_t) * (uint8_t*)(iVar9 + 0xd), (*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4) & uVar7) != 0 &&
	                                                                                                                                           ((*(uint32_t*)((uint8_t*)&gdwBitMasks) & uVar7) != 0))))))
	{
		if (pDVar6->pDynamicPath != nullptr)
		{
			D2Common_10153(pDVar6->pDynamicPath);
		}
		piVar2 = *(int**)(a1 + 8);
		iVar9 = *piVar2;
		if ((iVar9 == 2) || ((3 < iVar9 && (iVar9 < 6))))
		{
			iVar9 = *(int*)(piVar2[0xb] + 0x10);
		}
		else if ((D2DynamicPathStrc*)piVar2[0xb] == nullptr)
		{
			iVar9 = 0;
		}
		else
		{
			iVar9 = PATH_GetYPosition((D2DynamicPathStrc*)piVar2[0xb]);
		}
		piVar2 = *(int**)(a1 + 8);
		iVar10 = *piVar2;
		if ((iVar10 == 2) || ((3 < iVar10 && (iVar10 < 6))))
		{
			iVar10 = *(int*)(piVar2[0xb] + 0xc);
		}
		else if ((D2DynamicPathStrc*)piVar2[0xb] == nullptr)
		{
			iVar10 = 0;
		}
		else
		{
			iVar10 = PATH_GetXPosition((D2DynamicPathStrc*)piVar2[0xb]);
		}
		puVar3 = *(uint32_t**)(a1 + 8);
		if (puVar3 == nullptr)
		{
			uVar12 = 0xffffffff;
			uVar11 = 6;
		}
		else
		{
			uVar12 = puVar3[3];
			uVar11 = *puVar3;
		}
		sub_6FAADAA0(CONCAT31((int32_t)((uint32_t)uVar11 >> 8), 0x59), uVar11, uVar12, iVar10, iVar9);
		piVar2 = *(int**)(a1 + 8);
		if (((piVar2 != nullptr) && (*piVar2 == 1)) && (piVar2[5] != 0))
		{
			pbVar1 = (uint8_t*)(piVar2[5] + 0x28);
			*pbVar1 = *pbVar1 | 1;
		}
		sub_6FB4F410(*(D2UnitStrc**)(a1 + 8), (int*)0x1);
	}
	iVar9 = D2Common_10399(*(D2UnitStrc**)(a1 + 8), *(D2UnitStrc**)(a1 + 4));
	if (iVar13 < iVar9)
	{
		sub_6FB4EA90(*(uint32_t*)(a1 + 0x18), *(D2UnitStrc**)(a1 + 4), a2, a3, 0);
		piVar2 = *(int**)(a1 + 4);
		if (piVar2 == nullptr)
		{
			return;
		}
		if (*piVar2 != 0)
		{
			return;
		}
		if (piVar2[5] == 0)
		{
			return;
		}
		*(uint32_t*)(piVar2[5] + 0x150) = 1;
		*(uint32_t*)(piVar2[5] + 0x154) = 0x13;
		*(uint32_t*)(piVar2[5] + 0x158) = a2;
		*(int*)(piVar2[5] + 0x15c) = a3;
		return;
	}
LAB_6fb4b071:
	sub_6FB4EA90(0x13, *(D2UnitStrc**)(a1 + 4), a2, a3, 0);
}

//D2Client.0x6FB4B0A0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB4B0A0(int* a1, uint32_t* a2)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	double extraout_ST0;
	int64_t lVar5;
	uint32_t uStack_18;
	int local_14;
	int iStack_10;
	uint32_t uStack_c;

	iVar2 = *a1;
	if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
	{
		local_14 = *(int*)(a1[0xb] + 0xc);
	}
	else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
	{
		local_14 = 0;
	}
	else
	{
		local_14 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
	}
	iVar2 = *a1;
	if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
	{
		iStack_10 = *(int*)(a1[0xb] + 0x10);
	}
	else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
	{
		iStack_10 = 0;
	}
	else
	{
		iStack_10 = PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
	}
	uVar3 = a2[3] - local_14;
	uVar4 = a2[4] - iStack_10;
	uVar1 = uVar3;
	if ((int)uVar3 < 0)
	{
		uVar1 = -uVar3;
	}
	if ((int)uVar1 < 0x100)
	{
		uVar1 = uVar4;
		if ((int)uVar4 < 0)
		{
			uVar1 = -uVar4;
		}
		if ((int)uVar1 < 0x100)
		{
			uVar1 = uVar3;
			if ((int)uVar3 < 0)
			{
				uVar1 = -uVar3;
			}
			if ((int)uVar1 < 1)
			{
				uVar1 = uVar4;
				if ((int)uVar4 < 0)
				{
					uVar1 = -uVar4;
				}
				if ((int)uVar1 < 1)
				{
					return 0;
				}
			}
			uStack_c = DFLOOR_ApproximateDistance(uVar3, uVar4);
			if ((int)uStack_c < 2)
			{
				uStack_c = 1;
			}
			uVar1 = *a2;
			uStack_18 = 3;
			if (((uVar1 & 4) == 0) || ((uVar1 & 0x40) == 0))
			{
				if ((uVar1 & 8) == 0)
				{
					if ((uVar1 & 0x10) != 0)
					{
						uStack_18 = 0;
					}
				}
				else
				{
					uStack_18 = (uVar1 & 0xff) >> 6 & 1 | 4;
				}
			}
			else
			{
				uStack_18 = 5;
			}
			if ((int)uStack_c < (int)uStack_18)
			{
				lVar5 = (int64_t)((double)(int)uVar3 * ((double)uStack_18 / (double)(int)uStack_c));
				uVar3 = (uint32_t)lVar5;
				lVar5 = (int64_t)((double)(int)uVar4 * extraout_ST0);
				uVar4 = (uint32_t)lVar5;
			}
			a2[3] = local_14 + uVar3;
			a2[4] = iStack_10 + uVar4;
			iVar2 = sub_6FAABF80();
			if ((((*a1 != 0) || ((*a2 & 8) == 0)) || (uVar1 = a1[4], uVar1 < 2)) ||
			    (((3 < uVar1 && (uVar1 != 6)) || (6 < (uint32_t)(iVar2 - dword_6FBBC238)))))
			{
				dword_6FBBC238 = iVar2;
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB4B260
uint32_t __fastcall sub_6FB4B260(uint32_t* a1)
{
	uint32_t uVar1;
	int iVar2;

	uVar1 = *a1;
	if ((uVar1 & 0x10) != 0)
	{
		dword_6FBBC240 = 0;
		return 0;
	}
	if ((uVar1 & 4) == 0)
	{
		if ((uVar1 & 8) != 0)
		{
			if (dword_6FBBC240 == 0)
			{
				return 0;
			}
			if (((int*)a1[2] != nullptr) &&
			    (((iVar2 = *(int*)a1[2], iVar2 < 0 || ((1 < iVar2 && (iVar2 != 5)))) ||
			        ((a1[1] != 0 &&
			            (((iVar2 = *(int*)(a1[1] + 0x10), iVar2 == 2 || (iVar2 == 3)) || (iVar2 == 6))))))))
			{
				return 0;
			}
		}
	}
	else
	{
		dword_6FBBC240 = (a1[2] != 0) + 1;
	}
	return 1;
}

//D2Client.0x6FB4B2D0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB4B2D0(uint32_t* a1)
{
	bool bVar1;
	int iVar2;
	D2SkillStrc* pDVar3;
	uint32_t extraout_var;

	iVar2 = sub_6FB4B260(a1);
	if (iVar2 != 0)
	{
		pDVar3 = UNITS_GetRightSkill((D2UnitStrc*)a1[1]);
		a1[7] = (uint32_t)pDVar3;
		bVar1 = sub_6FB29290((D2UnitStrc*)a1[1]);
		if (D2C_ZEXT(bVar1) != 0)
		{
			iVar2 = SKILLS_GetSkillIdFromSkill((D2SkillStrc*)a1[7], __FILE__, __LINE__);
			if ((iVar2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar2))
			{
				iVar2 = 0;
			}
			else
			{
				iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c;
			}
			if ((*(char*)(iVar2 + 0x14) == '\x01') && ((*a1 & 0x40) == 0))
			{
				*a1 = *a1 | 0x80;
			}
			sub_6FB49DF0(a1);
		}
	}
	return 1;
}

//D2Client.0x6FB4B360
uint32_t __fastcall sub_6FB4B360(uint32_t* a1)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	int iVar3;

	sub_6FB4B260(a1);
	uVar1 = sub_6FAB1920(a1[1], 7, 0);
	if (uVar1 != 0xffffffff)
	{
		pDVar2 = sub_6FB269F0(uVar1, 1);
		if (pDVar2 != nullptr)
		{
			iVar3 = sub_6FAB18D0(uVar1);
			if (*(int*)(iVar3 + 8) == 2)
			{
				sub_6FAB6430(a1[1], (int)pDVar2, 0);
			}
		}
	}
	return 0;
}

//D2Client.0x6FB4B3C0
void __fastcall sub_6FB4B3C0(int a1)
{
	D2DynamicPathStrc* pDynamicPath;
	D2InventoryStrc* pInventory;
	D2InventoryStrc* pInventory_00;
	uint8_t bVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	D2UnitStrc* pDVar3;
	int32_t nDestY;
	uint32_t uVar4;
	D2ActiveRoomStrc* pDestRoom;
	D2UnitStrc* pDVar5;
	D2UnitStrc* pDVar6;
	D2UnitStrc* pItem;
	uint32_t uVar7;
	uint32_t uStack_c;

	if ((*(char*)(a1 + 1) != '\0') &&
	    (pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), 0), pUnit != nullptr))
	{
		iVar2 = sub_6FB29550((int*)pUnit);
		if (iVar2 == 0)
		{
			sub_6FB4F410(pUnit, nullptr);
		}
		pDVar3 = CUNIT_GetPlayer();
		if (pUnit == pDVar3)
		{
			pDVar3 = sub_6FB269F0(*(uint32_t*)(a1 + 6), 0);
			if (pDVar3 == nullptr)
			{
				return;
			}
			pDynamicPath = pDVar3->pDynamicPath;
			PATH_SetMoveTestCollisionMask(pDynamicPath, 0);
			PATH_SetUnitCollisionPattern(pDVar3, 5);
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				nDestY = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&nDestY + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&nDestY + 2)) = 0;
			}
			else
			{
				nDestY = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				uVar4 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				uVar4 = 0;
			}
			else
			{
				uVar4 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			pDestRoom = UNITS_GetRoom(pUnit);
			iVar2 = D2Common_10229(pDynamicPath, pDVar3, pDestRoom, uVar4, (uint32_t)nDestY);
			D2_ASSERT(iVar2);
			bVar1 = PATH_GetDirection(pUnit->pDynamicPath);
			PATH_SetDirection(pDVar3->pDynamicPath, bVar1);
		}
		pInventory = pUnit->pInventory;
		pDVar3 = INVENTORY_GetFirstItem(pInventory);
		while (pDVar5 = pDVar3, pDVar5 != nullptr)
		{
			pDVar3 = INVENTORY_GetNextItem(pDVar5);
			iVar2 = INVENTORY_GetItemNodePage(pDVar5);
			if (iVar2 == 3)
			{
				pDVar5 = INVENTORY_UnitIsItem(pDVar5);
				INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pDVar5);
				bVar1 = ITEMS_GetBodyLocation(pDVar5);
				if ((bVar1 == 5) || (bVar1 == 4))
				{
					pInventory_00 = pUnit->pInventory;
					pDVar6 = INVENTORY_GetItemFromBodyLoc(pInventory_00, 4);
					pItem = INVENTORY_GetItemFromBodyLoc(pInventory_00, 5);
					if (((pDVar6 == nullptr) ||
					        (((pItem == nullptr ||
					              (uVar4 = ITEMS_CheckWeaponIfTwoHanded(pDVar6), uVar4 != 0)) ||
					            (uVar4 = ITEMS_CheckWeaponIfTwoHanded(pItem), uVar4 != 0)))) ||
					    (pDVar6 = INVENTORY_GetLeftHandWeapon(pInventory_00), pDVar5 == pDVar6))
						goto LAB_6fb4b573;
					uStack_c = 6;
				}
				else
				{
				LAB_6fb4b573:
					bVar1 = ITEMS_GetComponent(pDVar5);
					uStack_c = (uint32_t)bVar1;
				}
				sub_6FB5C2E0(pUnit, uStack_c);
				pDVar6 = INVENTORY_RemoveItemFromInventory(pInventory, pDVar5);
				D2_ASSERT(pDVar6 != nullptr);
				D2_ASSERT(pDVar6 == pDVar5);
				sub_6FB2A880(pDVar5, pUnit, 0, 0);
				bVar1 = ITEMS_GetBodyLocation(pDVar5);
				D2COMMON_10254_Return0((int)pInventory, (uint32_t)bVar1);
				sub_6FB5C080(pUnit);
				if (pDVar5 == nullptr)
				{
					uVar4 = 6;
					uVar7 = 0xffffffff;
				}
				else
				{
					uVar4 = pDVar5->dwUnitType;
					uVar7 = pDVar5->dwUnitId;
				}
				sub_6FB26BE0(uVar7, uVar4);
			}
		}
	}
}

//D2Client.0x6FB4B640
void __fastcall sub_6FB4B640(D2UnitStrc* pUnit, D2ActiveRoomStrc* pActiveRoom, uint32_t a3, uint32_t a4)
{
	bool bVar1;
	int iVar2;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;
	uint32_t* puVar5;
	uint32_t local_2c;
	uint32_t local_28;
	D2ActiveRoomStrc* local_24;
	D2DynamicPathStrc* local_20;
	uint32_t auStack_1c[7];

	bVar1 = false;
	uVar3 = pUnit->dwAnimMode;
	local_20 = pUnit->pDynamicPath;
	pDVar4 = nullptr;
	local_2c = 0;
	local_28 = 0;
	local_24 = pActiveRoom;
	if ((1 < (int)uVar3) && (((int)uVar3 < 4 || (uVar3 == 6))))
	{
		bVar1 = true;
		pDVar4 = sub_6FB296A0((int)pUnit);
		if (pDVar4 == nullptr)
		{
			sub_6FABA950(pUnit, (int*)&local_2c, (int*)&local_28);
		}
	}
	D2Common_10230(local_20, (int)pUnit, local_24, a3, (short)a4);
	if (bVar1)
	{
		puVar5 = auStack_1c;
		for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar5 = 0;
			puVar5 = puVar5 + 1;
		}
		if (pDVar4 == nullptr)
		{
			auStack_1c[0] = local_2c;
			auStack_1c[1] = local_28;
			uVar3 = (-(uint32_t)(uVar3 != 3) & 0xffffffea) + 0x17;
		}
		else
		{
			auStack_1c[0] = pDVar4->dwUnitType;
			auStack_1c[1] = pDVar4->dwUnitId;
			uVar3 = (uVar3 != 3) - 1 & 0x18;
		}
		sub_6FB49090(uVar3, pUnit, (D2SkillStrc*)(auStack_1c), 0);
	}
}

//D2Client.0x6FB4B720
void __fastcall sub_6FB4B720(uint32_t a1, int* a2, uint32_t a3, uint32_t a4)
{
	if (((a2 != nullptr) && (*a2 == 0)) && (a2[5] != 0))
	{
		*(uint32_t*)(a2[5] + 0x150) = 1;
		*(uint32_t*)(a2[5] + 0x154) = a1;
		*(uint32_t*)(a2[5] + 0x158) = a3;
		*(uint32_t*)(a2[5] + 0x15c) = a4;
	}
}

//D2Client.0x6FB4B760
uint32_t __fastcall sub_6FB4B760(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 0)) && (a1[5] != 0))
	{
		return *(uint32_t*)(a1[5] + 0x154);
	}
	return 0;
}

//D2Client.0x6FB4B780
uint32_t __fastcall sub_6FB4B780(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 0)) && (a1[5] != 0))
	{
		return *(uint32_t*)(a1[5] + 0x158);
	}
	return 0;
}

//D2Client.0x6FB4B7A0
uint32_t __fastcall sub_6FB4B7A0(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 0)) && (a1[5] != 0))
	{
		return *(uint32_t*)(a1[5] + 0x15c);
	}
	return 0;
}
