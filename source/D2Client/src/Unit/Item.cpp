#include "Unit/Item.h"

#include "Core/WinMain.h"
#include "Draw/DFloor.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Select.h"
#include "Sound/SoundInst.h"
#include "UI/Inv.h"
#include "UI/NpcMenu.h"
#include "UI/Panel.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Monster.h"
#include "Unit/PlrSkills.h"

//D2Client.0x6FB90C28
uint32_t dword_6FB90C28;
//D2Client.0x6FB90C30
uint32_t dword_6FB90C30 = 2;
//D2Client.0x6FBBC208
uint8_t byte_6FBBC208;
//D2Client.0x6FBBC20A
uint8_t byte_6FBBC20A;

//D2Client.0x6FB2A880
void __fastcall sub_6FB2A880(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3, int a4)
{
	int iVar1;

	if (pUnit2 != nullptr)
	{
		if (pUnit2->dwUnitType == 0)
		{
			INVENTORY_GetLeftHandWeapon(pUnit2->pInventory);
		}
		iVar1 = ITEMS_CheckItemFlag(pUnit, 0x100, __LINE__, __FILE__);
		if ((iVar1 == 0) || (a3 != 0))
		{
			STATLIST_ExpireUnitStatlist(pUnit2, pUnit);
		}
		if (a4 != 0)
		{
			STATLIST_ClampStaminaManaHP(pUnit2);
		}
	}
}

//D2Client.0x6FB2A8E0
void __fastcall sub_6FB2A8E0(D2UnitStrc* pUnit2, D2ActiveRoomStrc* pActiveRoom, float a3, float a4, int a5, int a6)
{
	float nY;
	D2StatListStrc* pStatList;
	int iVar1;
	D2UnitStrc* pUnit;
	char nFlags;

	iVar1 = a5;
	if (a5 < 7)
	{
		if ((((pUnit2->dwAnimMode == 5) || (pUnit2->dwAnimMode == 3)) && (a5 != 5)) &&
		    (a5 != 3))
		{
			UNITS_FreeCollisionPath(pUnit2);
		}
		pUnit2->dwAnimMode = iVar1;
		UNITROOM_UpdatePath(pUnit2);
		nY = a4;
		switch (pUnit2->dwAnimMode)
		{
		case 3:
			UNITS_InitializeStaticPath(pUnit2, pActiveRoom, (int)a3, (int)a4);
			UNITS_BlockCollisionPath(pUnit2, pActiveRoom, (int)a3, (int)nY);
			UNITROOM_AddUnitToRoom(pUnit2, pActiveRoom);
			pUnit2->dwFlags = pUnit2->dwFlags | 2;
			UNITS_SetAnimStartFrame(pUnit2);
			break;
		case 4:
			sub_6FB55820(0xeb, nullptr, 0.0, 0.0, 0);
		case 0:
		case 1:
		case 2:
		case 6:
			pUnit2->dwFlags = pUnit2->dwFlags & 0xfffffffd;
			break;
		case 5:
			UNITS_InitializeStaticPath(pUnit2, pActiveRoom, (int)a3, (int)a4);
			UNITS_BlockCollisionPath(pUnit2, pActiveRoom, (int)a3, (int)nY);
			UNITROOM_AddUnitToRoom(pUnit2, pActiveRoom);
			pUnit2->dwFlags = pUnit2->dwFlags & 0xfffffffd;
			UNITS_SetAnimStartFrame(pUnit2);
			a4 = 1.68156e-44;
			iVar1 = sub_6FB2AA90(pUnit2, (uint32_t*)&a4);
			sub_6FB55820(0xd8, pUnit2, 0.0, 0.0, 0);
			if ((0 < iVar1) && (iVar1 = sub_6FB55820(iVar1, pUnit2, a4, 0.0, 0), iVar1 != 0))
			{
				sub_6FB55BC0(iVar1, 0xb4);
			}
			break;
		default:
			goto switchD_6fb2a927_default;
		}
		pUnit2->dwFlags = pUnit2->dwFlags & 0xfffffff3 | 0x20;
		if (a6 != 0)
		{
			ITEMS_SetItemFlag(pUnit2, 0x10, 1);
			STATLIST_AllocStatListEx(pUnit, nFlags, (StatListValueChangeFunc)(pUnit2), nullptr);
			pStatList = STATLIST_AllocStatList(nullptr, 0x40, 0, 4, pUnit2->dwUnitId);
			D2COMMON_10475_PostStatToStatList(pUnit2, pStatList, 1);
			iVar1 = ITEMS_CheckIfSocketable(pUnit2);
			if ((iVar1 != 0) && (pUnit2->pInventory == nullptr))
			{
				INVENTORY_AllocInventory(nullptr, pUnit2);
			}
		}
	}
switchD_6fb2a927_default:
}

//D2Client.0x6FB2AA90
int __fastcall sub_6FB2AA90(D2UnitStrc* pUnit, uint32_t* a2)
{
	int iVar1;
	D2ItemsTxt* pDVar2;
	int iVar3;

	iVar3 = 0;
	if (a2 != nullptr)
	{
		*a2 = 0xc;
	}
	if (pUnit == nullptr)
	{
		iVar1 = -1;
	}
	else
	{
		iVar1 = pUnit->dwClassId;
	}
	pDVar2 = DATATBLS_GetItemsTxtRecord(iVar1);
	if ((pDVar2 != nullptr) && (0 < (short)pDVar2->wDropSound))
	{
		if ((a2 != nullptr) && (pDVar2->nDropSfxFrame != 0))
		{
			*a2 = (uint32_t)pDVar2->nDropSfxFrame;
		}
		iVar3 = (int)(short)pDVar2->wDropSound;
	}
	iVar1 = ITEMS_GetItemQuality(pUnit);
	if (iVar1 == 7)
	{
		iVar1 = ITEMS_GetFileIndex(pUnit);
		if (-1 < iVar1)
		{
			iVar1 = ITEMS_GetFileIndex(pUnit);
			if (((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc28))) &&
			    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc24) + iVar1 * 0x14c, iVar1 != 0 &&
			                                                                                       (0 < *(short*)(iVar1 + 0x84)))))
			{
				if ((a2 != nullptr) && (*(uint8_t*)(iVar1 + 0x88) != 0))
				{
					*a2 = (uint32_t) * (uint8_t*)(iVar1 + 0x88);
				}
				return (int)*(short*)(iVar1 + 0x84);
			}
		}
	}
	else
	{
		iVar1 = ITEMS_GetItemQuality(pUnit);
		if (iVar1 == 5)
		{
			iVar1 = ITEMS_GetFileIndex(pUnit);
			if ((((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc1c))) &&
			        (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc18) + iVar1 * 0x1b8, iVar1 != 0)) &&
			    (0 < *(short*)(iVar1 + 0x82)))
			{
				if ((a2 != nullptr) && (*(uint8_t*)(iVar1 + 0x86) != 0))
				{
					*a2 = (uint32_t) * (uint8_t*)(iVar1 + 0x86);
				}
				iVar3 = (int)*(short*)(iVar1 + 0x82);
			}
		}
	}
	return iVar3;
}

//D2Client.0x6FB2ABD0
void __fastcall sub_6FB2ABD0(D2UnitStrc* pUnit)
{
	int iVar1;
	D2ActiveRoomStrc* pRoom;

	sub_6FB59320((int)pUnit);
	iVar1 = ITEMS_CheckIfSocketable(pUnit);
	if (iVar1 != 0)
	{
		sub_6FB29AE0(pUnit, 0);
		INVENTORY_FreeInventory(pUnit->pInventory);
		pUnit->pInventory = nullptr;
	}
	if (ghAct != nullptr)
	{
		UNITS_FreeCollisionPath(pUnit);
		pRoom = UNITS_GetRoom(pUnit);
		iVar1 = UNITROOM_IsUnitInRoom(pRoom, pUnit);
		if (iVar1 != 0)
		{
			UNITROOM_RemoveUnitFromRoom(pUnit);
		}
	}
}

//D2Client.0x6FB2AC30
void __fastcall sub_6FB2AC30(D2UnitStrc* ptUnit)
{
	int iVar1;

	D2_ASSERT(ptUnit != nullptr);
	switch (ptUnit->dwAnimMode)
	{
	case 0:
	case 1:
	case 2:
	case 4:
	case 6:
		ptUnit->dwFlags = ptUnit->dwFlags & 0xfffffffd;
		return;
	case 3:
		ptUnit->dwFlags = ptUnit->dwFlags | 2;
		iVar1 = sub_6FB57CD0((int)ptUnit, 0x46);
		if (iVar1 != 0)
		{
			return;
		}
		break;
	case 5:
		iVar1 = UNITS_IsAtEndOfFrameCycle(ptUnit);
		if (iVar1 == 0)
		{
			UNITS_UpdateFrame(ptUnit);
			return;
		}
		ptUnit->dwAnimMode = 3;
		break;
	default:
		FOG_DisplayAssert("0", __FILE__, __LINE__);
		exit(-1);
	}
	sub_6FB5BA70(ptUnit, 0x46, 6, 8, 0, 0, 8, 0);
}

//D2Client.0x6FB2AD10
void __fastcall sub_6FB2AD10(int a1, D2UnitStrc* pUnit, int a3, int a4)
{
	if (a1 == 2)
	{
		UNITS_ChangeAnimMode(pUnit, a4);
		if (pUnit != nullptr)
		{
			if (a3 != 0)
			{
				pUnit->dwFlags = pUnit->dwFlags | 2;
				return;
			}
			pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
		}
	}
}

//D2Client.0x6FB2AD50
void __fastcall sub_6FB2AD50(int a1)
{
	D2UnitStrc* pUnit;
	D2StatListStrc* pStatList;
	int iVar1;
	float fStack_1c;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pUnit = sub_6FB2AE60(a1, &local_18, CONCAT22(local_18.nY, local_18.nX),
	    CONCAT22((*(uint16_t*)((uint8_t*)&local_18 + 8)), local_18.nY), 0);
	D2_ASSERT(pUnit != nullptr);
	pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, 0x36);
	if (pStatList != nullptr)
	{
		STATES_ToggleState(pUnit, 0x36, 0);
		D2Common_10474(pUnit, pStatList);
		STATLIST_FreeStatList(pStatList);
		UNITS_UpdateAnimRateAndVelocity(pUnit, __FILE__, __LINE__);
	}
	if (pUnit->dwAnimMode == 3)
	{
		iVar1 = ITEMS_CheckItemFlag(pUnit, 0x2000, __LINE__, __FILE__);
		if (iVar1 != 0)
		{
			UNITS_ChangeAnimMode(pUnit, 5);
			fStack_1c = 1.68156e-44;
			iVar1 = sub_6FB2AA90(pUnit, (uint32_t*)&fStack_1c);
			sub_6FB55820(0xd8, pUnit, 0.0, 0.0, 0);
			if (0 < iVar1)
			{
				iVar1 = sub_6FB55820(iVar1, pUnit, fStack_1c, 0.0, 0);
				if (iVar1 != 0)
				{
					sub_6FB55BC0(iVar1, 0xb4);
				}
			}
		}
	}
}

//D2Client.0x6FB2AE60
// TODO: decompilation needs review (extraout)
D2UnitStrc* __fastcall sub_6FB2AE60(int a1, D2ItemSaveStrc* pItemSave, uint32_t a3, uint32_t a4, int a5)
{
	D2UnitStrc* pItem;
	int iVar1;
	uint32_t extraout_ECX;
	uint32_t nSize;
	int iStack_1c;
	D2ItemSaveStrc local_18;

	nSize = *(uint8_t*)(a1 + 2) - 8;
	if (pItemSave == nullptr)
	{
		ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), nSize, 0, &local_18);
		pItemSave = &local_18;
	}
	pItem = sub_6FB27040(*(uint32_t*)(a1 + 4), pItemSave->nClassId, a3 & 0xffff, a4 & 0xffff, 4,
	    (uint32_t)pItemSave->nAnimMode);
	ITEMS_DecodeItemFromBitstream(pItem, (uint8_t*)(a1 + 8), nSize, 0, nullptr, 0x60, &iStack_1c);
	if (iStack_1c != 0)
	{
		sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
		return nullptr;
	}
	iVar1 = ITEMS_CheckIfFlagIsSet(pItemSave->dwFlags, 2);
	if (iVar1 != 0)
	{
		ITEMS_SetItemFlag(pItem, 2, 0);
		if (a5 != 0)
		{
			iVar1 = ITEMS_CheckItemFlag(pItem, 0x10, __LINE__, __FILE__);
			if (iVar1 == 0)
			{
				sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x37), *(uint32_t*)(a1 + 4));
			}
		}
	}
	return pItem;
}

//D2Client.0x6FB2AF40
void __fastcall sub_6FB2AF40(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	D2StatListStrc* pStatList;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pDVar1 = CUNIT_GetPlayer();
	pInventory = pDVar1->pInventory;
	if (local_18.nAnimMode == 4)
	{
		pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
		D2_ASSERT(pDVar1 == nullptr);
		pDVar1 = sub_6FB2AE60(a1, &local_18, 0, 0, 0);
		D2_ASSERT(pDVar1 != nullptr);
		INVENTORY_SetCursorItem(pInventory, pDVar1);
		pDVar2 = INVENTORY_GetCursorItem(pInventory);
		sub_6FB575B0(pDVar2);
		pStatList = STATLIST_GetStatListFromUnitAndState(pDVar1, 0x36);
		if (pStatList != nullptr)
		{
			STATES_ToggleState(pDVar1, 0x36, 0);
			D2Common_10474(pDVar1, pStatList);
			STATLIST_FreeStatList(pStatList);
			UNITS_UpdateAnimRateAndVelocity(pDVar1, __FILE__, __LINE__);
		}
	}
}

//D2Client.0x6FB2B030
void __fastcall sub_6FB2B030(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	D2StatListStrc* pStatList;
	D2ActiveRoomStrc* pDVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pDVar1 = CUNIT_GetPlayer();
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	if (pUnit == nullptr)
	{
		uVar5 = CONCAT22((*(uint16_t*)((uint8_t*)&local_18 + 8)), local_18.nY);
		uVar4 = CONCAT22(local_18.nY, local_18.nX);
	}
	else
	{
		pInventory = pDVar1->pInventory;
		pDVar1 = INVENTORY_GetCursorItem(pInventory);
		if ((pDVar1 != nullptr) && (pDVar1 == pUnit))
		{
			INVENTORY_SetCursorItem(pInventory, nullptr);
			pDVar1 = INVENTORY_GetCursorItem(pInventory);
			sub_6FB575B0(pDVar1);
		}
		iVar2 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
		if (iVar2 == 0)
			goto LAB_6fb2b0d5;
		sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
		uVar5 = CONCAT22((*(uint16_t*)((uint8_t*)&local_18 + 8)), local_18.nY);
		uVar4 = CONCAT22(local_18.nY, local_18.nX);
	}
	pUnit = sub_6FB2AE60(a1, &local_18, uVar4, uVar5, 0);
LAB_6fb2b0d5:
	D2_ASSERT(pUnit != nullptr);
	pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, 0x36);
	if (pStatList != nullptr)
	{
		STATES_ToggleState(pUnit, 0x36, 0);
		D2Common_10474(pUnit, pStatList);
		STATLIST_FreeStatList(pStatList);
		UNITS_UpdateAnimRateAndVelocity(pUnit, __FILE__, __LINE__);
	}
	pDVar3 = nullptr;
	if ((local_18.nX != 0) || (local_18.nY != 0))
	{
		pDVar3 = sub_6FB26C90((uint32_t)local_18.nX, (uint32_t)local_18.nY);
	}
	sub_6FB2A8E0(pUnit, pDVar3, (float)(uint32_t)local_18.nX, (uint32_t)local_18.nY, 5, 0);
	ITEMS_SetInvPage(pUnit, local_18.nStorePage);
}

//D2Client.0x6FB2B190
void __fastcall sub_6FB2B190(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pUnit;
	uint8_t bVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	D2StatListStrc* pStatList;
	D2UnitStrc* pDStack_20;
	D2UnitStrc* pDStack_1c;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pDStack_20 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	if (pDStack_20 != nullptr)
	{
		if (pDStack_20->dwAnimMode == 0)
		{
			FOG_DisplayHalt("[UnitItemPlaceItemGroundEx] This should never happen!\n",
			    __FILE__, __LINE__);
			exit(-1);
		}
		if (pDStack_20->dwAnimMode == 1)
		{
			pDVar2 = CUNIT_GetPlayer();
			D2_ASSERT(pDVar2 != nullptr);
			pInventory = pDVar2->pInventory;
			sub_6FB5DA40(pDVar2);
			INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pDStack_20);
			bVar1 = UNITS_GetItemComponentId(pDVar2, pDStack_20);
			sub_6FB5C2E0(pDVar2, (uint32_t)bVar1);
			bVar1 = ITEMS_GetBodyLocation(pDStack_20);
			INVENTORY_GetSecondWieldingWeapon(pDVar2, pInventory, &pDStack_20, (uint32_t)bVar1);
			pDStack_1c = INVENTORY_RemoveItemFromInventory(pInventory, pDStack_20);
			if (pDStack_1c != nullptr)
			{
				D2COMMON_10254_Return0((int)pInventory, (uint32_t)bVar1);
				if (pDVar2->dwUnitType == 0)
				{
					INVENTORY_GetLeftHandWeapon(pDVar2->pInventory);
				}
				pUnit = pDStack_1c;
				iVar3 = ITEMS_CheckItemFlag(pDStack_1c, 0x100, __LINE__, __FILE__);
				if (iVar3 == 0)
				{
					STATLIST_ExpireUnitStatlist(pDVar2, pUnit);
				}
			}
			sub_6FB2B360(pDVar2);
			sub_6FB5C080(pDVar2);
		}
		sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
	}
	pDVar2 = sub_6FB2AE60(a1, &local_18, CONCAT22(local_18.nY, local_18.nX),
	    CONCAT22((*(uint16_t*)((uint8_t*)&local_18 + 8)), local_18.nY), 0);
	pDStack_20 = pDVar2;
	D2_ASSERT(pDVar2 != nullptr);
	pStatList = STATLIST_GetStatListFromUnitAndState(pDVar2, 0x36);
	if (pStatList != nullptr)
	{
		STATES_ToggleState(pDVar2, 0x36, 0);
		D2Common_10474(pDVar2, pStatList);
		STATLIST_FreeStatList(pStatList);
		UNITS_UpdateAnimRateAndVelocity(pDVar2, __FILE__, __LINE__);
	}
}

//D2Client.0x6FB2B360
void __fastcall sub_6FB2B360(D2UnitStrc* pUnit)
{
	D2InventoryStrc* pInventory;
	D2InventoryStrc* pDVar1;
	uint32_t uVar2;
	bool bVar3;
	uint8_t bVar4;
	uint8_t bVar5;
	D2SkillStrc* pDVar6;
	D2UnitStrc* pDVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	D2UnitStrc* pDVar10;
	int iVar11;
	D2SkillStrc* pDVar12;
	bool bVar13;
	int iStack_28;
	int local_20;
	int iStack_10;
	int iStack_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	if ((pUnit != nullptr) &&
	    (((pUnit->dwUnitType == 0 || ((pUnit->dwFlags >> 9 & 1) != 0)) &&
	        (pInventory = pUnit->pInventory, pInventory != nullptr))))
	{
		bVar3 = false;
		STATLIST_UnitGetStatValue(pUnit, 6, 0);
		STATLIST_UnitGetStatValue(pUnit, 8, 0);
		STATLIST_UnitGetStatValue(pUnit, 10, 0);
		pDVar6 = UNITS_GetLeftSkill(pUnit);
		if (pDVar6 == nullptr)
		{
			uStack_4 = 0xffffffff;
			iStack_c = 0;
		}
		else
		{
			uStack_4 = SKILLS_GetOwnerGUIDFromSkill(pDVar6);
			iStack_c = SKILLS_GetSkillIdFromSkill(pDVar6, __FILE__, __LINE__);
		}
		pDVar6 = UNITS_GetRightSkill(pUnit);
		if (pDVar6 == nullptr)
		{
			uStack_8 = 0xffffffff;
			iStack_10 = 0;
		}
		else
		{
			uStack_8 = SKILLS_GetOwnerGUIDFromSkill(pDVar6);
			iStack_10 = SKILLS_GetSkillIdFromSkill(pDVar6, __FILE__, __LINE__);
		}
		for (pDVar7 = INVENTORY_GetFirstItem(pInventory); pDVar7 != nullptr;
		     pDVar7 = INVENTORY_GetNextItem(pDVar7))
		{
			pDVar8 = INVENTORY_UnitIsItem(pDVar7);
			if (((pDVar8 != nullptr) && (iVar9 = INVENTORY_GetItemNodePage(pDVar7), iVar9 == 1)) && ((iVar9 = ITEMS_IsCharmUsable(pDVar8, pUnit), iVar9 != 0 &&
			                                                                                                                                          ((pDVar10 = STATLIST_GetOwner(pDVar8, nullptr), pDVar10 == nullptr &&
			                                                                                                                                                                                              (iVar9 = ITEMS_CheckRequirements(pDVar8, pUnit, 0, nullptr, nullptr, nullptr),
			                                                                                                                                                                                                  iVar9 != 0))))))
			{
				iVar9 = ITEMS_GetQuiverType(pDVar8);
				if (iVar9 == 0)
				{
				LAB_6fb2b4bc:
					ITEMS_SetItemFlag(pDVar8, 0x4000, 0);
					sub_6FB2B8E0(pDVar8, pUnit, 0, 0);
				}
				else
				{
					pDVar1 = pUnit->pInventory;
					pDVar10 = INVENTORY_GetItemFromBodyLoc(pDVar1, 4);
					if (pDVar10 == pDVar8)
					{
						pDVar10 = INVENTORY_GetItemFromBodyLoc(pDVar1, 5);
					}
					if (pDVar10 != nullptr)
					{
						iVar9 = ITEMS_GetQuiverType(pDVar8);
						iVar9 = ITEMS_CheckItemTypeId(pDVar10, iVar9);
						if (iVar9 != 0)
							goto LAB_6fb2b4bc;
					}
				}
			}
		}
		iStack_28 = 0;
		do
		{
			pDVar7 = INVENTORY_GetItemFromBodyLoc(pInventory, iStack_28);
			if (((pDVar7 != nullptr) &&
			        ((iVar9 = ITEMS_CheckItemFlag(pDVar7, 0x100, __LINE__, __FILE__), iVar9 == 0 ||
			                                                                              (pDVar8 = STATLIST_GetOwner(pDVar7, nullptr), pDVar8 != nullptr)))) &&
			    ((iVar9 = ITEMS_CheckItemFlag(pDVar7, 0x4000, __LINE__, __FILE__), iVar9 == 0 ||
			                                                                           (pDVar8 = STATLIST_GetOwner(pDVar7, nullptr), pDVar8 != nullptr))))
			{
				iVar9 = ITEMS_CheckRequirements(pDVar7, pUnit, 0, nullptr, nullptr, nullptr);
				if (iVar9 != 0)
				{
					iVar9 = ITEMS_GetQuiverType(pDVar7);
					if (iVar9 == 0)
						goto LAB_6fb2b616;
					pDVar1 = pUnit->pInventory;
					pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar1, 4);
					if (pDVar8 == pDVar7)
					{
						pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar1, 5);
					}
					if (pDVar8 != nullptr)
					{
						iVar9 = ITEMS_GetQuiverType(pDVar7);
						iVar9 = ITEMS_CheckItemTypeId(pDVar8, iVar9);
						if (iVar9 != 0)
							goto LAB_6fb2b616;
					}
				}
				ITEMS_SetItemFlag(pDVar7, 0x4000, 1);
				bVar4 = UNITS_GetItemComponentId(pUnit, pDVar7);
				if (pUnit->pInventory != nullptr)
				{
					INVENTORY_UpdateWeaponGUIDOnRemoval(pUnit->pInventory, pDVar7);
					if (pUnit->dwUnitType == 0)
					{
						INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
					}
					ITEMS_CheckItemFlag(pDVar7, 0x100, __LINE__, __FILE__);
					STATLIST_ExpireUnitStatlist(pUnit, pDVar7);
					sub_6FB5C2E0(pUnit, (uint32_t)bVar4);
				}
				bVar3 = true;
			}
		LAB_6fb2b616:
			iStack_28 = iStack_28 + 1;
		} while (iStack_28 < 0xb);
		local_20 = 100;
		do
		{
			bVar13 = false;
			iStack_28 = 0;
			do
			{
				pDVar7 = INVENTORY_GetItemFromBodyLoc(pInventory, iStack_28);
				if (((pDVar7 != nullptr) &&
				        (iVar9 = ITEMS_CheckItemFlag(pDVar7, 0x100, __LINE__, __FILE__), iVar9 == 0)) &&
				    (((iVar9 = ITEMS_CheckItemFlag(pDVar7, 0x4000, __LINE__, __FILE__),
				          iVar9 != 0 ||
				              (pDVar8 = STATLIST_GetOwner(pDVar7, nullptr), pDVar8 == nullptr)) &&
				        (iVar9 = ITEMS_CheckRequirements(pDVar7, pUnit, 0, nullptr, nullptr, nullptr),
				            iVar9 != 0))))
				{
					iVar9 = ITEMS_GetQuiverType(pDVar7);
					if (iVar9 == 0)
					{
					LAB_6fb2b6e9:
						ITEMS_SetItemFlag(pDVar7, 0x4000, 0);
						bVar4 = UNITS_GetItemComponentId(pUnit, pDVar7);
						pDVar1 = pUnit->pInventory;
						uVar2 = pDVar7->dwAnimMode;
						if (((pDVar1 != nullptr) &&
						        (bVar5 = ITEMS_GetBodyLocation(pDVar7), bVar5 != 0xb)) &&
						    (bVar5 != 0xc))
						{
							INVENTORY_UpdateWeaponGUIDOnRemoval(pDVar1, pDVar7);
							sub_6FB5C2E0(pUnit, (uint32_t)bVar4);
							if ((uVar2 == 1) &&
							    (pDVar8 = STATLIST_GetOwner(pDVar7, nullptr), pDVar8 == nullptr))
							{
								sub_6FB2B8E0(pDVar7, pUnit, 0, 1);
							}
							INVENTORY_UpdateWeaponGUIDOnInsert(pDVar1, pDVar7);
						}
						bVar13 = true;
						bVar3 = true;
					}
					else
					{
						pDVar1 = pUnit->pInventory;
						pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar1, 4);
						if (pDVar8 == pDVar7)
						{
							pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar1, 5);
						}
						if (pDVar8 != nullptr)
						{
							iVar9 = ITEMS_GetQuiverType(pDVar7);
							iVar9 = ITEMS_CheckItemTypeId(pDVar8, iVar9);
							if (iVar9 != 0)
								goto LAB_6fb2b6e9;
						}
					}
				}
				iStack_28 = iStack_28 + 1;
			} while (iStack_28 < 0xb);
		} while ((bVar13) && (bVar13 = local_20 != 0, local_20 = local_20 + -1, bVar13));
		iVar9 = 0;
		do
		{
			pDVar7 = INVENTORY_GetItemFromBodyLoc(pInventory, iVar9);
			if ((((pDVar7 != nullptr) && (iVar11 = ITEMS_GetItemQuality(pDVar7), iVar11 == 5)) && (iVar11 = ITEMS_CheckItemFlag(pDVar7, 0x100, __LINE__, __FILE__), iVar11 == 0)) && (iVar11 = ITEMS_CheckItemFlag(pDVar7, 0x4000, __LINE__, __FILE__),
			                                                                                                                                                                             iVar11 == 0))
			{
				if (pUnit->dwUnitType == 0)
				{
					INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
				}
				ITEMS_CheckItemFlag(pDVar7, 0x100, __LINE__, __FILE__);
				STATLIST_ExpireUnitStatlist(pUnit, pDVar7);
				sub_6FB2B8E0(pDVar7, pUnit, 1, 0);
			}
			iVar9 = iVar9 + 1;
		} while (iVar9 < 0xb);
		if (((iStack_c != 0) &&
		        (pDVar6 = SKILLS_GetSkillById(pUnit, iStack_c, uStack_4), pDVar6 != nullptr)) &&
		    ((pDVar12 = UNITS_GetLeftSkill(pUnit), pDVar6 != pDVar12 &&
		                                               ((iVar9 = sub_6FB4DA80(pUnit, pDVar6), iVar9 != 2 && (iVar9 != 7))))))
		{
			SKILLS_SetLeftActiveSkill(pUnit, iStack_c, uStack_4);
		}
		if ((((iStack_10 != 0) &&
		         (pDVar6 = SKILLS_GetSkillById(pUnit, iStack_10, uStack_8), pDVar6 != nullptr)) &&
		        (pDVar12 = UNITS_GetRightSkill(pUnit), pDVar6 != pDVar12)) &&
		    ((iVar9 = sub_6FB4DA80(pUnit, pDVar6), iVar9 != 2 && (iVar9 != 7))))
		{
			SKILLS_SetRightActiveSkill(pUnit, iStack_10, uStack_8);
		}
		if (bVar3)
		{
			if (pUnit->dwUnitType == 0)
			{
				sub_6FB5DA40(pUnit);
				sub_6FB5C080(pUnit);
				return;
			}
			sub_6FB42D40(7, pUnit, nullptr);
		}
	}
}

//D2Client.0x6FB2B8E0
void __fastcall sub_6FB2B8E0(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, uint32_t a3, int a4)
{
	int iVar1;
	D2ItemsTxt* pDVar2;
	D2GemsTxt* pDVar3;
	D2UnitStrc* pDVar4;
	int iVar5;

	if (pUnit2 != nullptr)
	{
		iVar1 = ITEMS_CheckItemTypeId(pUnit, 0x14);
		if (iVar1 == 0)
		{
			iVar1 = ITEMS_CheckItemTypeId(pUnit, 0x4a);
			if (iVar1 == 0)
			{
				ITEMS_UpdateSets(pUnit2, pUnit, 0, 0);
			}
			else
			{
				D2_ASSERT(pUnit2->dwUnitType == 4);
				if (pUnit == nullptr)
				{
					iVar1 = -1;
				}
				else
				{
					iVar1 = pUnit->dwClassId;
				}
				pDVar2 = DATATBLS_GetItemsTxtRecord(iVar1);
				if (pDVar2 == nullptr)
				{
					FOG_DisplayAssert("ptItemStats", __FILE__, __LINE__);
					exit(-1);
				}
				pDVar3 = DATATBLS_GetGemsTxtRecord(pDVar2->dwGemOffset);
				D2_ASSERT(pDVar3 != nullptr);
				iVar5 = 0;
				iVar1 = ITEMS_GetGemApplyType(pUnit2);
				ITEMMODS_AssignProperty(5, pUnit2, pUnit, pDVar3, iVar1, iVar5);
			}
		}
		else
		{
			D2_ASSERT(pUnit2->dwUnitType == 4);
			if (pUnit == nullptr)
			{
				iVar1 = -1;
			}
			else
			{
				iVar1 = pUnit->dwClassId;
			}
			pDVar2 = DATATBLS_GetItemsTxtRecord(iVar1);
			D2_ASSERT(pDVar2 != nullptr);
			pDVar3 = DATATBLS_GetGemsTxtRecord(pDVar2->dwGemOffset);
			D2_ASSERT(pDVar3 != nullptr);
			iVar5 = 0;
			iVar1 = ITEMS_GetGemApplyType(pUnit2);
			ITEMMODS_AssignProperty(2, nullptr, pUnit, pDVar3, iVar1, iVar5);
		}
		iVar1 = ITEMS_CheckItemFlag(pUnit, 0x4000, __LINE__, __FILE__);
		if (iVar1 == 0)
		{
			if (pUnit2->dwUnitType == 0)
			{
				pDVar4 = INVENTORY_GetLeftHandWeapon(pUnit2->pInventory);
				iVar1 = UNITS_CanDualWield(pUnit2);
				if (iVar1 != 0)
				{
					iVar1 = 1;
					if (((pDVar4 != nullptr) && (pUnit != pDVar4)) &&
					    (iVar5 = ITEMS_CheckItemTypeId(pUnit, 0x2d), iVar5 != 0))
					{
						iVar1 = 0;
					}
					iVar5 = ITEMS_CheckItemFlag(pUnit, 0x100, __LINE__, __FILE__);
					if ((iVar5 != 0) && (a4 == 0))
					{
						return;
					}
					STATLIST_MergeStatLists(pUnit2, pUnit, iVar1);
					return;
				}
			}
			iVar1 = ITEMS_CheckItemFlag(pUnit, 0x100, __LINE__, __FILE__);
			if ((iVar1 == 0) || (a4 != 0))
			{
				STATLIST_MergeStatLists(pUnit2, pUnit, 1);
			}
		}
	}
}

//D2Client.0x6FB2BAF0
void __fastcall sub_6FB2BAF0(int a1)
{
	uint32_t uVar1;
	uint8_t bVar2;
	D2UnitStrc* pUnit;
	D2UnitStrc* pItem;
	int iVar3;
	D2UnitStrc* pDVar4;
	int32_t nY;
	int nX;
	D2StatListStrc* pStatList;
	int iStack_20;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pUnit = CUNIT_GetPlayer();
	pItem = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	if (pItem == nullptr)
	{
		pItem = sub_6FB2AE60(a1, &local_18, 0, 0, 1);
	}
	else
	{
		iVar3 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
		if (iVar3 == 0)
		{
			bVar2 = local_18.nStorePage;
			sub_6FB2A8E0(pItem, 0, (float)(uint32_t)local_18.nX, (uint32_t)local_18.nY, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff,
			    0);
			ITEMS_SetInvPage(pItem, bVar2);
			ITEMS_SetItemFlag(pItem, 0xffffffff, 0);
			ITEMS_SetItemFlag(pItem, local_18.dwFlags, 1);
		}
		else
		{
			pDVar4 = INVENTORY_RemoveItemFromInventory(pUnit->pInventory, pItem);
			if (pDVar4 != nullptr)
			{
				bVar2 = ITEMS_GetInvPage(pItem);
				iStack_20 = CONCAT31((*(uint8_t*)((uint8_t*)&iStack_20 + 1)), bVar2);
				iVar3 = sub_6FAAC080();
				iVar3 = UNITS_GetInventoryRecordId(pUnit, iStack_20, iVar3);
				uVar1 = pItem->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					nY = (*(int32_t*)&pItem->pDynamicPath->tTargetCoord);
				}
				else if (pItem->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
				}
				else
				{
					nY = (int32_t)PATH_GetYPosition(pItem->pDynamicPath);
				}
				uVar1 = pItem->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					nX = pItem->pDynamicPath->dwClientCoordY;
				}
				else if (pItem->pDynamicPath == nullptr)
				{
					nX = 0;
				}
				else
				{
					nX = PATH_GetXPosition(pItem->pDynamicPath);
				}
				INVENTORY_Return(__FILE__, __LINE__, pUnit->pInventory, nX,
				    (int)nY, iVar3, 1, bVar2);
				sub_6FAE8F10();
				if (pUnit->dwUnitType == 0)
				{
					INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
				}
				iVar3 = ITEMS_CheckItemFlag(pItem, 0x100, __LINE__, __FILE__);
				if (iVar3 == 0)
				{
					STATLIST_ExpireUnitStatlist(pUnit, pItem);
				}
			}
			sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
			pItem = sub_6FB2AE60(a1, &local_18, 0, 0, 0);
			if (pItem == nullptr)
			{
				return;
			}
		}
	}
	if (local_18.nStorePage == 0xff)
	{
		FOG_Trace(" Invalid page %d at line %d of file %s\n", 0xff, __LINE__, __FILE__);
		return;
	}
	sub_6FB2BD70(CONCAT22(local_18.nY, local_18.nX), CONCAT22((*(uint16_t*)((uint8_t*)&local_18 + 8)), local_18.nY),
	    (*(uint32_t*)((uint8_t*)&local_18 + 16)), pUnit, pItem);
	iVar3 = ITEMS_IsCharmUsable(pItem, pUnit);
	if (iVar3 != 0)
	{
		sub_6FB2B8E0(pItem, pUnit, 0, 0);
	}
	sub_6FB238D0();
	if (pItem != nullptr)
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pItem, 0x36);
		if (pStatList != nullptr)
		{
			STATES_ToggleState(pItem, 0x36, 0);
			D2Common_10474(pItem, pStatList);
			STATLIST_FreeStatList(pStatList);
			UNITS_UpdateAnimRateAndVelocity(pItem, __FILE__, __LINE__);
		}
		sub_6FAFAE20(pItem->dwUnitId);
		return;
	}
	FOG_DisplayAssert("hItem", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB2BD70
void __fastcall sub_6FB2BD70(uint32_t a1, uint32_t a2, int a3, D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	D2InventoryStrc* pInventory;
	uint32_t uVar1;
	D2UnitStrc* pItem;
	int iVar2;
	int bLoD;
	D2UnitStrc* pDVar3;
	D2ItemsTxt* pDVar4;
	int iVar5;
	float fVar6;
	int bUnused;
	float fVar7;
	uint8_t nPage;

	pItem = pUnit2;
	UNITS_SetXForStaticUnit(pUnit2, a1 & 0xffff);
	UNITS_SetYForStaticUnit(pUnit2, a2 & 0xffff);
	iVar5 = 0;
	pInventory = pUnit->pInventory;
	D2_ASSERT(pInventory != nullptr);
	iVar2 = INVENTORY_PlaceItemInSocket(pInventory, pUnit2, 1);
	if (iVar2 != 0)
	{
		uVar1 = pUnit2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			pUnit2 = *(D2UnitStrc**)&pUnit2->pDynamicPath->tTargetCoord;
		}
		else if (pUnit2->pDynamicPath == nullptr)
		{
			pUnit2 = nullptr;
		}
		else
		{
			pUnit2 = (D2UnitStrc*)PATH_GetYPosition(pUnit2->pDynamicPath);
		}
		uVar1 = pItem->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar5 = pItem->pDynamicPath->dwClientCoordY;
		}
		else if (pItem->pDynamicPath != nullptr)
		{
			iVar5 = PATH_GetXPosition(pItem->pDynamicPath);
		}
		bUnused = 1;
		iVar2 = a3;
		bLoD = sub_6FAAC080();
		nPage = (uint8_t)iVar2;
		iVar2 = UNITS_GetInventoryRecordId(pUnit, a3, bLoD);
		iVar5 = INVENTORY_PlaceItemAtInventoryPage(pInventory, pItem, iVar5, (int)pUnit2, iVar2, bUnused, nPage);
		if (iVar5 == 0)
		{
			FOG_Trace("sUnitItemInsertItemInvGridBase failed at %d in %s\n", __LINE__, __FILE__);
			return;
		}
		pDVar3 = CUNIT_GetPlayer();
		if (pUnit == pDVar3)
		{
			iVar5 = 0;
			if ((char)a3 == '\x01')
			{
				fVar7 = 0.0;
				fVar6 = 0.0;
				iVar2 = sub_6FB2AA90(pItem, nullptr);
				sub_6FB55820(iVar2, nullptr, fVar6, fVar7, iVar5);
			}
			else
			{
				INVENTORY_SetCursorItem(pInventory, nullptr);
				pDVar3 = INVENTORY_GetCursorItem(pInventory);
				sub_6FB575B0(pDVar3);
			}
		}
		pDVar3 = CUNIT_GetPlayer();
		if ((pUnit == pDVar3) && ((char)a3 == '\x03'))
		{
			pDVar4 = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
			uVar1 = pDVar4->dwCode;
			if ((uVar1 == 0x20747368) || (uVar1 == 0x20326671))
			{
				sub_6FAED0D0(uVar1);
			}
		}
	}
}

//D2Client.0x6FB2BEF0
void __fastcall sub_6FB2BEF0(int a1)
{
	D2InventoryStrc* pInventory;
	uint8_t bVar1;
	D2UnitStrc* pUnit;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar2;
	char* pcVar3;
	int iVar4;
	int iVar5;
	D2StatListStrc* pStatList;
	D2ItemSaveStrc local_21c;
	int iStack_204;
	char acStack_200[512];

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_21c);
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pUnit != nullptr)
	{
		pItem = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
		if (pItem == nullptr)
		{
			if (local_21c.nStorePage == 1)
			{
				CUNIT_GetPlayer();
			}
			FOG_Trace("UnitItemRemoveItemInvGrid failed at line %d in file %s\n", __LINE__, __FILE__);
			return;
		}
		pInventory = pUnit->pInventory;
		D2_ASSERT(pInventory != nullptr);
		pDVar2 = INVENTORY_RemoveItemFromInventory(pInventory, pItem);
		if (pDVar2 == nullptr)
		{
			if ((local_21c.nStorePage == 2) && (pDVar2 = CUNIT_GetPlayer(), pUnit == pDVar2))
			{
				return;
			}
			pcVar3 = DATATBLS_GetUnitNameFromUnit(pItem, acStack_200);
			FOG_Trace("UnitItemRemoveItemInvGrid failed at line %d in file %s for item %s\n", __LINE__, __FILE__, pcVar3);
			return;
		}
		D2_ASSERT(pDVar2 == pItem);
		bVar1 = ITEMS_GetInvPage(pItem);
		iStack_204 = CONCAT31((*(uint8_t*)((uint8_t*)&iStack_204 + 1)), bVar1);
		iVar4 = sub_6FAAC080();
		iVar5 = iStack_204;
		iVar4 = UNITS_GetInventoryRecordId(pUnit, iStack_204, iVar4);
		INVENTORY_Return(__FILE__, __LINE__, pInventory, (uint32_t)local_21c.nX, (uint32_t)local_21c.nY, iVar4, 1, (uint8_t)iVar5);
		sub_6FAE8F10();
		if (pUnit->dwUnitType == 0)
		{
			INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
		}
		iVar5 = ITEMS_CheckItemFlag(pItem, 0x100, __LINE__, __FILE__);
		if (iVar5 == 0)
		{
			STATLIST_ExpireUnitStatlist(pUnit, pItem);
		}
		iVar5 = ITEMS_CheckIfFlagIsSet(local_21c.dwFlags, 0x20);
		if (iVar5 == 0)
		{
			iVar5 = ITEMS_CheckIfFlagIsSet(local_21c.dwFlags, 1);
			if (iVar5 == 0)
			{
				sub_6FB2A8E0(pItem, 0, (float)(uint32_t)local_21c.nX, (uint32_t)local_21c.nX,
				    (uint16_t)(*(uint16_t*)((uint8_t*)&local_21c + 8)) & 0xff, 0);
				ITEMS_SetInvPage(pItem, local_21c.nStorePage);
			}
			else
			{
				sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
				pItem = sub_6FB2C1D0(a1, &local_21c, 0, 0, 0);
				D2_ASSERT(pItem != nullptr);
			}
			ITEMS_SetInvPage(pItem, 0xff);
			INVENTORY_SetCursorItem(pInventory, pItem);
			pDVar2 = INVENTORY_GetCursorItem(pInventory);
			sub_6FB575B0(pDVar2);
			pStatList = STATLIST_GetStatListFromUnitAndState(pItem, 0x36);
			if (pStatList != nullptr)
			{
				STATES_ToggleState(pItem, 0x36, 0);
				D2Common_10474(pItem, pStatList);
				STATLIST_FreeStatList(pStatList);
				UNITS_UpdateAnimRateAndVelocity(pItem, __FILE__, __LINE__);
			}
		}
		else
		{
			sub_6FB26BE0(pItem->dwUnitId, 4);
			pDVar2 = CUNIT_GetPlayer();
			if (pUnit == pDVar2)
			{
				if (local_21c.nStorePage == 1)
				{
					sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				}
				else
				{
					sub_6FB575B0(nullptr);
				}
			}
		}
		pDVar2 = CUNIT_GetPlayer();
		if (pUnit == pDVar2)
		{
			sub_6FAFAB80(pItem->dwUnitId);
		}
	}
}

//D2Client.0x6FB2C1D0
// TODO: decompilation needs review (extraout)
D2UnitStrc* __fastcall sub_6FB2C1D0(int a1, D2ItemSaveStrc* pItemSave, uint32_t a3, uint32_t a4, int a5)
{
	D2UnitStrc* pItem;
	int iVar1;
	uint32_t extraout_ECX;
	uint32_t nSize;
	int iStack_1c;
	D2ItemSaveStrc local_18;

	nSize = *(uint8_t*)(a1 + 2) - 0xd;
	if (pItemSave == nullptr)
	{
		ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), nSize, 0, &local_18);
		pItemSave = &local_18;
	}
	pItem = sub_6FB27040(*(uint32_t*)(a1 + 4), pItemSave->nClassId, a3 & 0xffff, a4 & 0xffff, 4,
	    (uint32_t)pItemSave->nAnimMode);
	ITEMS_DecodeItemFromBitstream(pItem, (uint8_t*)(a1 + 0xd), nSize, 0, nullptr, 0x60, &iStack_1c);
	if (iStack_1c != 0)
	{
		sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
		return nullptr;
	}
	iVar1 = ITEMS_CheckIfFlagIsSet(pItemSave->dwFlags, 2);
	if (iVar1 != 0)
	{
		ITEMS_SetItemFlag(pItem, 2, 0);
		if (a5 != 0)
		{
			iVar1 = ITEMS_CheckItemFlag(pItem, 0x10, __LINE__, __FILE__);
			if (iVar1 == 0)
			{
				sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x37), *(uint32_t*)(a1 + 4));
			}
		}
	}
	return pItem;
}

//D2Client.0x6FB2C2B0
void __fastcall sub_6FB2C2B0(int a1)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 3), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar1 != nullptr)
	{
		sub_6FB2B360(pDVar1);
		return;
	}
}

//D2Client.0x6FB2C2D0
void __fastcall sub_6FB2C2D0(int a1)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 3), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar1 != nullptr)
	{
		sub_6FB2B360(pDVar1);
		return;
	}
}

//D2Client.0x6FB2C300
void __fastcall sub_6FB2C300(uint32_t* a1)
{
	D2InventoryStrc* pInventory;
	uint16_t uVar1;
	uint8_t bVar2;
	uint16_t uVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pUnit;
	D2UnitStrc* pItem;
	int iVar5;
	int iVar6;
	D2StatListStrc* pStatList;
	uint32_t uVar7;
	D2UnitStrc* pDStack_24;
	uint32_t* local_20;
	D2UnitStrc* pDStack_1c;
	D2ItemSaveStrc local_18;

	local_20 = a1;
	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)((int)a1 + 0xd), *(uint8_t*)((int)a1 + 2) - 0xd, 0, &local_18);
	pDVar4 = CUNIT_GetPlayer();
	if (pDVar4 == nullptr)
	{
		return;
	}
	pDStack_1c = pDVar4;
	pUnit = sub_6FB269F0(*(uint32_t*)((int)a1 + 9), (uint32_t)(uint8_t)a1[2]);
	if (pUnit == nullptr)
	{
		FOG_Trace("UnitItemInsertItemBodyEx() invalid unit type:%d  id:%d", (uint32_t)(uint8_t)a1[2],
		    *(uint32_t*)((int)a1 + 9));
		return;
	}
	pItem = sub_6FB269F0(a1[1], 4);
	if (pItem == nullptr)
	{
		uVar7 = (uint32_t)(pUnit == pDVar4);
	}
	else
	{
		iVar5 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
		if (iVar5 == 0)
		{
			pDStack_24 = (D2UnitStrc*)CONCAT31((*(uint8_t*)((uint8_t*)&pDStack_24 + 1)), local_18.nStorePage);
			sub_6FB2A8E0(pItem, 0, 0.0, 0, (*(uint32_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
			ITEMS_SetInvPage(pItem, (uint8_t)pDStack_24);
			goto LAB_6fb2c47b;
		}
		pInventory = pUnit->pInventory;
		pDStack_24 = pItem;
		bVar2 = ITEMS_GetBodyLocation(pItem);
		uVar7 = (uint32_t)bVar2;
		if ((uVar7 == 4) || (uVar7 == 5))
		{
			INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pDStack_24);
			bVar2 = UNITS_GetItemComponentId(pUnit, pDStack_24);
			sub_6FB5C2E0(pUnit, (uint32_t)bVar2);
			INVENTORY_GetSecondWieldingWeapon(pUnit, pInventory, &pDStack_24, uVar7);
			a1 = local_20;
		}
		pDVar4 = INVENTORY_RemoveItemFromInventory(pInventory, pDStack_24);
		if (pDVar4 != nullptr)
		{
			sub_6FB2A880(pDVar4, pUnit, 0, 0);
			D2COMMON_10254_Return0((int)pInventory, uVar7);
		}
		if (pDStack_24 == nullptr)
		{
			sub_6FB26BE0(0xffffffff, 6);
			uVar7 = 0;
		}
		else
		{
			sub_6FB26BE0(pDStack_24->dwUnitId, pDStack_24->dwUnitType);
			uVar7 = 0;
		}
	}
	pItem = sub_6FB2C1D0((int)a1, &local_18, 0, 0, uVar7);
LAB_6fb2c47b:
	if (pItem != nullptr)
	{
		ITEMS_SetBodyLocation(pItem, local_18.nBodyloc);
	}
	pDStack_24 = (D2UnitStrc*)pUnit->pInventory;
	if (pDStack_24 != nullptr)
	{
		iVar5 = 3;
		if ((local_18.nBodyloc == 0xb) || (local_18.nBodyloc == 0xc))
		{
			iVar5 = 4;
		}
		iVar6 = INVENTORY_PlaceItemInSocket((D2InventoryStrc*)pDStack_24, pItem, iVar5);
		if (iVar6 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Trying to add a NULL item!\n");
			return;
		}
		uVar7 = (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff;
		if (pItem == nullptr)
		{
			FOG_Trace("[INVENTORY ERROR] Trying to insert null item into unit's body location!");
			return;
		}
		pDVar4 = INVENTORY_GetItemFromBodyLoc((D2InventoryStrc*)pDStack_24, uVar7);
		if (pDVar4 != nullptr)
		{
			D2COMMON_10254_Return0((int)pDStack_24, uVar7);
			FOG_Trace("[INVENTORY ERROR] Forced an item into unit's body location!");
		}
		pDVar4 = pDStack_24;
		iVar6 = INVENTORY_PlaceItemInBodyLoc((D2InventoryStrc*)pDStack_24, pItem, uVar7);
		if (iVar6 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Unable to insert item into unit's body location!");
			return;
		}
		sub_6FB5DA40(pUnit);
		if (iVar5 == 3)
		{
			INVENTORY_UpdateWeaponGUIDOnInsert((D2InventoryStrc*)pDVar4, pItem);
		}
		sub_6FB5B1D0((int)pUnit, 0);
		if ((-1 < (int)pUnit->dwUnitType) && ((int)pUnit->dwUnitType < 2))
		{
			bVar2 = *(uint8_t*)((int)local_20 + 3);
			if ((bVar2 == 0) || (bVar2 == 1))
			{
				sub_6FB5C2E0(pUnit, (uint32_t)bVar2);
			}
			sub_6FB5C080(pUnit);
			bVar2 = local_18.nBodyloc;
			if (pUnit == pDStack_1c)
			{
				uVar3 = ITEMS_GetWeaponClassId(pItem);
				uVar1 = uVar3;
				if ((bVar2 != 4) && (uVar1 = byte_6FBBC208, bVar2 == 5))
				{
					byte_6FBBC20A = uVar3;
				}
				byte_6FBBC208 = uVar1;
				iVar5 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 8);
				pDVar4 = pDStack_24;
				if (iVar5 == 0)
				{
					INVENTORY_SetCursorItem((D2InventoryStrc*)pDStack_24, nullptr);
					pDVar4 = INVENTORY_GetCursorItem((D2InventoryStrc*)pDVar4);
					sub_6FB575B0(pDVar4);
				}
			}
			if (local_18.nBodyloc < 0xb)
			{
				sub_6FB2B8E0(pItem, pUnit, 0, 0);
			}
			sub_6FB2B360(pUnit);
			sub_6FB2B360(pUnit);
			sub_6FB238D0();
			pStatList = STATLIST_GetStatListFromUnitAndState(pItem, 0x36);
			if (pStatList != nullptr)
			{
				STATES_ToggleState(pItem, 0x36, 0);
				D2Common_10474(pItem, pStatList);
				STATLIST_FreeStatList(pStatList);
				UNITS_UpdateAnimRateAndVelocity(pItem, __FILE__, __LINE__);
			}
			sub_6FAFAD40(pItem->dwUnitId);
		}
	}
}

//D2Client.0x6FB2C660
void __fastcall sub_6FB2C660(int a1)
{
	D2InventoryStrc* pInventory;
	uint16_t uVar1;
	uint8_t bVar2;
	uint16_t uVar3;
	D2UnitStrc* pUnit;
	D2UnitStrc* pDVar4;
	int iVar5;
	D2StatListStrc* pDVar6;
	D2UnitStrc* pDVar7;
	uint32_t nBodyLoc;
	int iVar8;
	D2UnitStrc* pDStack_24;
	int local_20;
	D2UnitStrc* pDStack_1c;
	D2ItemSaveStrc local_18;

	local_20 = a1;
	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_18);
	pDStack_1c = CUNIT_GetPlayer();
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pUnit != nullptr)
	{
		sub_6FB5DA40(pUnit);
		switch ((*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff)
		{
		case 4:
		case 0xb:
			iVar8 = 5;
			break;
		case 5:
		case 0xc:
			iVar8 = 4;
			break;
		default:
			goto switchD_6fb2c6c2_caseD_6;
		}
		pInventory = pUnit->pInventory;
		pDStack_24 = INVENTORY_GetItemFromBodyLoc(pInventory, iVar8);
		D2_ASSERT(pDStack_24 != nullptr);
		INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pDStack_24);
		bVar2 = UNITS_GetItemComponentId(pUnit, pDStack_24);
		sub_6FB5C2E0(pUnit, (uint32_t)bVar2);
		INVENTORY_GetSecondWieldingWeapon(pUnit, pInventory, &pDStack_24, iVar8);
		pDVar4 = INVENTORY_RemoveItemFromInventory(pInventory, pDStack_24);
		D2_ASSERT(!((pDVar4 == nullptr) || (pDVar4 != pDStack_24)));
		if (pUnit->dwUnitType == 0)
		{
			INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
		}
		iVar5 = ITEMS_CheckItemFlag(pDVar4, 0x100, __LINE__, __FILE__);
		if (iVar5 == 0)
		{
			STATLIST_ExpireUnitStatlist(pUnit, pDVar4);
		}
		D2COMMON_10254_Return0((int)pInventory, iVar8);
		sub_6FB5C080(pUnit);
		if (pUnit == pDStack_1c)
		{
			sub_6FAE8F10();
			pDVar4 = pDStack_24;
			if (local_18.nBodyloc == 4)
			{
				byte_6FBBC208 = 0;
			}
			else if (local_18.nBodyloc == 5)
			{
				byte_6FBBC20A = 0;
			}
			pDStack_1c = (D2UnitStrc*)CONCAT31((*(uint8_t*)((uint8_t*)&pDStack_1c + 1)), local_18.nStorePage);
			D2_ASSERT(pDStack_24 != nullptr);
			sub_6FB2A8E0(pDStack_24, 0, 0.0, 0, 4, 0);
			ITEMS_SetInvPage(pDVar4, (uint8_t)pDStack_1c);
			ITEMS_SetBodyLocation(pDStack_24, 0);
			INVENTORY_SetCursorItem(pInventory, pDStack_24);
			pDVar4 = INVENTORY_GetCursorItem(pInventory);
			sub_6FB575B0(pDVar4);
		}
		pDVar4 = pDStack_24;
		D2_ASSERT(pDStack_24 != nullptr);
		pDVar6 = STATLIST_GetStatListFromUnitAndState(pDStack_24, 0x36);
		if (pDVar6 != nullptr)
		{
			STATES_ToggleState(pDVar4, 0x36, 0);
			D2Common_10474(pDVar4, pDVar6);
			STATLIST_FreeStatList(pDVar6);
			UNITS_UpdateAnimRateAndVelocity(pDVar4, __FILE__, __LINE__);
		}
		iVar8 = local_20;
		pDVar4 = sub_6FB269F0(*(uint32_t*)(local_20 + 4), 4);
		if (pDVar4 == nullptr)
		{
			pDVar4 = sub_6FB2C1D0(iVar8, &local_18, 0, 0, 0);
		}
		else
		{
			iVar5 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
			if (iVar5 == 0)
			{
				pDStack_1c = (D2UnitStrc*)CONCAT31((*(uint8_t*)((uint8_t*)&pDStack_1c + 1)), local_18.nStorePage);
				sub_6FB2A8E0(pDVar4, 0, 0.0, 0, (*(uint32_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
				ITEMS_SetInvPage(pDVar4, (uint8_t)pDStack_1c);
			}
			else
			{
				sub_6FB26BE0(*(uint32_t*)(iVar8 + 4), 4);
				pDVar4 = sub_6FB2C1D0(iVar8, &local_18, 0, 0, 0);
				D2_ASSERT(pDVar4 != nullptr);
			}
		}
		ITEMS_SetBodyLocation(pDVar4, local_18.nBodyloc);
		iVar8 = 3;
		if ((local_18.nBodyloc == 0xb) || (local_18.nBodyloc == 0xc))
		{
			iVar8 = 4;
		}
		iVar8 = INVENTORY_PlaceItemInSocket(pInventory, pDVar4, iVar8);
		if (iVar8 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Trying to add a NULL item!\n");
			return;
		}
		nBodyLoc = (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff;
		if (pDVar4 == nullptr)
		{
			FOG_Trace("[INVENTORY ERROR] Trying to insert null item into unit's body location!");
			return;
		}
		pDVar7 = INVENTORY_GetItemFromBodyLoc(pInventory, nBodyLoc);
		if (pDVar7 != nullptr)
		{
			D2COMMON_10254_Return0((int)pInventory, nBodyLoc);
			FOG_Trace("[INVENTORY ERROR] Forced an item into unit's body location!");
		}
		iVar8 = INVENTORY_PlaceItemInBodyLoc(pInventory, pDVar4, nBodyLoc);
		if (iVar8 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Unable to insert item into unit's body location!");
			return;
		}
		INVENTORY_UpdateWeaponGUIDOnInsert(pInventory, pDVar4);
		sub_6FB5B1D0((int)pUnit, 0);
		D2_ASSERT(!(((int)pUnit->dwUnitType < 0) || (1 < (int)pUnit->dwUnitType)));
		bVar2 = *(uint8_t*)(local_20 + 3);
		if ((bVar2 == 0) || (bVar2 == 1))
		{
			sub_6FB5C2E0(pUnit, (uint32_t)bVar2);
		}
		sub_6FB5C080(pUnit);
		uVar3 = ITEMS_GetWeaponClassId(pDVar4);
		uVar1 = uVar3;
		if ((local_18.nBodyloc != 4) && (uVar1 = byte_6FBBC208, local_18.nBodyloc == 5))
		{
			byte_6FBBC20A = uVar3;
		}
		byte_6FBBC208 = uVar1;
		sub_6FB2B8E0(pDVar4, pUnit, 0, 0);
		sub_6FB2B360(pUnit);
		sub_6FB2B360(pUnit);
		sub_6FB238D0();
		pDVar6 = STATLIST_GetStatListFromUnitAndState(pDVar4, 0x36);
		if (pDVar6 != nullptr)
		{
			STATES_ToggleState(pDVar4, 0x36, 0);
			D2Common_10474(pDVar4, pDVar6);
			STATLIST_FreeStatList(pDVar6);
			UNITS_UpdateAnimRateAndVelocity(pDVar4, __FILE__, __LINE__);
		}
	}
switchD_6fb2c6c2_caseD_6:
}

//D2Client.0x6FB2CB10
void __fastcall sub_6FB2CB10(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	D2StatListStrc* pStatList;
	uint32_t uVar4;
	D2UnitStrc* pDStack_20;
	D2UnitStrc* pDStack_1c;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_18);
	pDStack_1c = CUNIT_GetPlayer();
	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pDVar1 != nullptr)
	{
		pInventory = pDVar1->pInventory;
		D2_ASSERT(pInventory != nullptr);
		pDStack_20 = INVENTORY_GetItemFromBodyLoc(pInventory, (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff);
		if (pDStack_20 != nullptr)
		{
			sub_6FB5DA40(pDVar1);
			INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pDStack_20);
			sub_6FB5C2E0(pDVar1, (uint32_t) * (uint8_t*)(a1 + 3));
			INVENTORY_GetSecondWieldingWeapon(pDVar1, pInventory, &pDStack_20, (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff);
			pDVar2 = INVENTORY_RemoveItemFromInventory(pInventory, pDStack_20);
			D2COMMON_10254_Return0((int)pInventory, (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff);
			ITEMS_UpdateSets(pDVar1, pDVar2, 1, 1);
			if (pDVar1->dwUnitType == 0)
			{
				INVENTORY_GetLeftHandWeapon(pDVar1->pInventory);
			}
			iVar3 = ITEMS_CheckItemFlag(pDVar2, 0x100, __LINE__, __FILE__);
			if (iVar3 == 0)
			{
				STATLIST_ExpireUnitStatlist(pDVar1, pDVar2);
			}
			sub_6FB2B360(pDVar1);
			sub_6FB5C080(pDVar1);
			if (pDVar1 == pDStack_1c)
			{
				if (pDStack_20 == nullptr)
				{
					uVar4 = 0xffffffff;
				}
				else
				{
					uVar4 = pDStack_20->dwUnitId;
				}
				sub_6FAFAC60(uVar4);
				sub_6FAE8F10();
				if (local_18.nBodyloc == 4)
				{
					byte_6FBBC208 = 0;
				}
				else if (local_18.nBodyloc == 5)
				{
					byte_6FBBC20A = 0;
				}
				iVar3 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 0x20);
				if (iVar3 != 0)
				{
				LAB_6fb2cdd8:
					sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
					return;
				}
				iVar3 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
				pDVar2 = pDStack_20;
				if (iVar3 == 0)
				{
					pDStack_1c = (D2UnitStrc*)CONCAT31((*(uint8_t*)((uint8_t*)&pDStack_1c + 1)), local_18.nStorePage);
					D2_ASSERT(pDStack_20 != nullptr);
					sub_6FB2A8E0(pDStack_20, 0, 0.0, 0, (*(uint32_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
					ITEMS_SetInvPage(pDVar2, (uint8_t)pDStack_1c);
				}
				else
				{
					sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
					pDStack_20 = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
					D2_ASSERT(pDStack_20 != nullptr);
				}
				ITEMS_SetBodyLocation(pDStack_20, 0);
				INVENTORY_SetCursorItem(pInventory, pDStack_20);
				pDVar2 = INVENTORY_GetCursorItem(pInventory);
				sub_6FB575B0(pDVar2);
				sub_6FB2B360(pDVar1);
				sub_6FB2B360(pDVar1);
				pDVar1 = pDStack_20;
				if (pDStack_20 != nullptr)
				{
					pStatList = STATLIST_GetStatListFromUnitAndState(pDStack_20, 0x36);
					if (pStatList != nullptr)
					{
						STATES_ToggleState(pDVar1, 0x36, 0);
						D2Common_10474(pDVar1, pStatList);
						STATLIST_FreeStatList(pStatList);
						UNITS_UpdateAnimRateAndVelocity(pDVar1, __FILE__, __LINE__);
					}
					iVar3 = ITEMS_CheckItemFlag(pDStack_20, 0x4000, __LINE__, __FILE__);
					if (iVar3 != 0)
					{
						ITEMS_SetItemFlag(pDStack_20, 0x4000, 0);
					}
				}
			}
			else
			{
				pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
				if (pDVar1 != nullptr)
					goto LAB_6fb2cdd8;
			}
		}
	}
}

//D2Client.0x6FB2CDF0
void __fastcall sub_6FB2CDF0(int a1)
{
	D2InventoryStrc* pInventory;
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar3;
	uint32_t nBodyLoc;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_18);
	iVar1 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 0x40);
	if (iVar1 == 0)
	{
		iVar1 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 0x80);
		if (iVar1 != 0)
		{
			sub_6FB2D070(a1, &local_18);
		}
	}
	else
	{
		pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
		if (pDVar2 != nullptr)
		{
			D2_ASSERT(!pDVar2->dwUnitType);
			pItem = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
			iVar1 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
			if (iVar1 == 0)
			{
				D2_ASSERT(pItem != nullptr);
				sub_6FB2A8E0(pItem, 0, 0.0, 0, (*(uint32_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
				ITEMS_SetInvPage(pItem, local_18.nStorePage);
			}
			else
			{
				sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
				pItem = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
				D2_ASSERT(pItem != nullptr);
			}
			ITEMS_SetBodyLocation(pItem, local_18.nBodyloc);
			pInventory = pDVar2->pInventory;
			D2_ASSERT(pInventory != nullptr);
			iVar1 = 3;
			if ((local_18.nBodyloc == 0xb) || (local_18.nBodyloc == 0xc))
			{
				iVar1 = 4;
			}
			iVar1 = INVENTORY_PlaceItemInSocket(pInventory, pItem, iVar1);
			if (iVar1 == 0)
			{
				FOG_Trace("[INVENTORY ERROR] Trying to add a NULL item!\n");
				return;
			}
			nBodyLoc = (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff;
			pDVar3 = INVENTORY_GetItemFromBodyLoc(pInventory, nBodyLoc);
			if (pDVar3 != nullptr)
			{
				D2COMMON_10254_Return0((int)pInventory, nBodyLoc);
				FOG_Trace("[INVENTORY ERROR] Forced an item into unit's body location!");
			}
			iVar1 = INVENTORY_PlaceItemInBodyLoc(pInventory, pItem, nBodyLoc);
			if (iVar1 == 0)
			{
				FOG_Trace("[INVENTORY ERROR] Unable to insert item into unit's body location!");
				return;
			}
			sub_6FB5DA40(pDVar2);
			INVENTORY_UpdateWeaponGUIDOnInsert(pInventory, pItem);
			sub_6FB5B1D0((int)pDVar2, 0);
			sub_6FB2B8E0(pItem, pDVar2, 0, 0);
			sub_6FB2B360(pDVar2);
			sub_6FB2B360(pDVar2);
			sub_6FB2D040(pItem, local_18.nBodyloc);
			sub_6FB5C080(pDVar2);
			sub_6FB238D0();
			sub_6FB2FAD0(pItem);
			return;
		}
	}
}

//D2Client.0x6FB2D040
void __fastcall sub_6FB2D040(D2UnitStrc* pUnit, char a2)
{
	uint16_t uVar1;

	uVar1 = ITEMS_GetWeaponClassId(pUnit);
	if (a2 == '\x04')
	{
		byte_6FBBC208 = uVar1;
		return;
	}
	if (a2 == '\x05')
	{
		byte_6FBBC20A = uVar1;
	}
}

//D2Client.0x6FB2D070
void __fastcall sub_6FB2D070(int a1, D2ItemSaveStrc* pItemSave)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	D2StatListStrc* pStatList;
	D2UnitStrc* pDStack_8;
	int local_4;

	local_4 = a1;
	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pDVar1 != nullptr)
	{
		D2_ASSERT(!pDVar1->dwUnitType);
		pInventory = pDVar1->pInventory;
		D2_ASSERT(pInventory != nullptr);
		pDStack_8 = INVENTORY_GetItemFromBodyLoc(pInventory, (uint32_t)pItemSave->nBodyloc);
		sub_6FB5DA40(pDVar1);
		INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pDStack_8);
		sub_6FB5C2E0(pDVar1, (uint32_t) * (uint8_t*)(a1 + 3));
		INVENTORY_GetSecondWieldingWeapon(pDVar1, pInventory, &pDStack_8, (uint32_t)pItemSave->nBodyloc);
		pDVar2 = INVENTORY_RemoveItemFromInventory(pInventory, pDStack_8);
		D2_ASSERT(pDVar2 != nullptr);
		D2_ASSERT(pDVar2 == pDStack_8);
		if (pDVar1->dwUnitType == 0)
		{
			INVENTORY_GetLeftHandWeapon(pDVar1->pInventory);
		}
		iVar3 = ITEMS_CheckItemFlag(pDVar2, 0x100, __LINE__, __FILE__);
		if (iVar3 == 0)
		{
			STATLIST_ExpireUnitStatlist(pDVar1, pDVar2);
		}
		ITEMS_UpdateSets(pDVar1, pDVar2, 1, 1);
		D2COMMON_10254_Return0((int)pInventory, (uint32_t)pItemSave->nBodyloc);
		iVar4 = ITEMS_CheckIfFlagIsSet(pItemSave->dwFlags, 1);
		iVar3 = local_4;
		pDVar2 = pDStack_8;
		if (iVar4 == 0)
		{
			local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), pItemSave->nStorePage);
			D2_ASSERT(pDStack_8 != nullptr);
			sub_6FB2A8E0(pDStack_8, 0, 0.0, 0, (uint32_t)pItemSave->nAnimMode, 0);
			ITEMS_SetInvPage(pDVar2, (uint8_t)local_4);
		}
		else
		{
			sub_6FB26BE0(*(uint32_t*)(local_4 + 4), 4);
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar1 == pDVar2)
			{
				pDStack_8 = sub_6FB2C1D0(iVar3, pItemSave, 0, 0, 0);
				D2_ASSERT(pDStack_8 != nullptr);
			}
		}
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar1 == pDVar2)
		{
			sub_6FAE8F10();
			ITEMS_SetBodyLocation(pDStack_8, 0);
			INVENTORY_SetCursorItem(pInventory, pDStack_8);
			pDVar1 = INVENTORY_GetCursorItem(pInventory);
			sub_6FB575B0(pDVar1);
			pDVar1 = pDStack_8;
			D2_ASSERT(pDStack_8 != nullptr);
			pStatList = STATLIST_GetStatListFromUnitAndState(pDStack_8, 0x36);
			if (pStatList != nullptr)
			{
				STATES_ToggleState(pDVar1, 0x36, 0);
				D2Common_10474(pDVar1, pStatList);
				STATLIST_FreeStatList(pStatList);
				UNITS_UpdateAnimRateAndVelocity(pDVar1, __FILE__, __LINE__);
			}
		}
	}
}

//D2Client.0x6FB2D300
void __fastcall sub_6FB2D300(uint32_t* a1)
{
	uint16_t uVar1;
	uint8_t bVar2;
	uint16_t uVar3;
	D2UnitStrc* pUnit;
	int iVar4;
	D2UnitStrc* pDVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	D2InventoryStrc* pDVar8;
	D2UnitStrc* pDStack_24;
	uint32_t* local_20;
	D2InventoryStrc* pDStack_1c;
	D2ItemSaveStrc local_18;

	local_20 = a1;
	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)((int)a1 + 0xd), *(uint8_t*)((int)a1 + 2) - 0xd, 0, &local_18);
	pUnit = sub_6FB269F0(*(uint32_t*)((int)a1 + 9), (uint32_t)(uint8_t)a1[2]);
	if (pUnit != nullptr)
	{
		D2_ASSERT(!pUnit->dwUnitType);
		pDVar8 = pUnit->pInventory;
		pDStack_1c = pDVar8;
		D2_ASSERT(pDVar8 != nullptr);
		iVar4 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
		D2_ASSERT(iVar4);
		sub_6FB5DA40(pUnit);
		pDVar5 = sub_6FB269F0(a1[1], 4);
		if (pDVar5 != nullptr)
		{
			pDVar8 = pUnit->pInventory;
			pDStack_24 = pDVar5;
			bVar2 = ITEMS_GetBodyLocation(pDVar5);
			uVar7 = (uint32_t)bVar2;
			if ((uVar7 == 4) || (uVar7 == 5))
			{
				INVENTORY_UpdateWeaponGUIDOnRemoval(pDVar8, pDStack_24);
				bVar2 = UNITS_GetItemComponentId(pUnit, pDStack_24);
				sub_6FB5C2E0(pUnit, (uint32_t)bVar2);
				INVENTORY_GetSecondWieldingWeapon(pUnit, pDVar8, &pDStack_24, uVar7);
				a1 = local_20;
			}
			pDVar5 = INVENTORY_RemoveItemFromInventory(pDVar8, pDStack_24);
			if (pDVar5 != nullptr)
			{
				sub_6FB2A880(pDVar5, pUnit, 0, 0);
				D2COMMON_10254_Return0((int)pDVar8, uVar7);
			}
			if (pDStack_24 == nullptr)
			{
				uVar7 = 6;
				uVar6 = 0xffffffff;
			}
			else
			{
				uVar7 = pDStack_24->dwUnitType;
				uVar6 = pDStack_24->dwUnitId;
			}
			sub_6FB26BE0(uVar6, uVar7);
			pDVar8 = pDStack_1c;
		}
		pDVar5 = INVENTORY_GetItemFromBodyLoc(pDVar8, (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff);
		if (pDVar5 != nullptr)
		{
			pDVar8 = pUnit->pInventory;
			pDStack_24 = pDVar5;
			bVar2 = ITEMS_GetBodyLocation(pDVar5);
			uVar7 = (uint32_t)bVar2;
			if ((uVar7 == 4) || (uVar7 == 5))
			{
				INVENTORY_UpdateWeaponGUIDOnRemoval(pDVar8, pDStack_24);
				bVar2 = UNITS_GetItemComponentId(pUnit, pDStack_24);
				sub_6FB5C2E0(pUnit, (uint32_t)bVar2);
				INVENTORY_GetSecondWieldingWeapon(pUnit, pDVar8, &pDStack_24, uVar7);
				a1 = local_20;
			}
			pDVar5 = INVENTORY_RemoveItemFromInventory(pDVar8, pDStack_24);
			if (pDVar5 != nullptr)
			{
				sub_6FB2A880(pDVar5, pUnit, 0, 0);
				D2COMMON_10254_Return0((int)pDVar8, uVar7);
			}
			if (pDStack_24 == nullptr)
			{
				uVar7 = 6;
				uVar6 = 0xffffffff;
			}
			else
			{
				uVar7 = pDStack_24->dwUnitType;
				uVar6 = pDStack_24->dwUnitId;
			}
			sub_6FB26BE0(uVar6, uVar7);
			pDVar8 = pDStack_1c;
		}
		pDVar5 = sub_6FB2C1D0((int)a1, &local_18, 0, 0, 0);
		D2_ASSERT(pDVar5 != nullptr);
		ITEMS_SetBodyLocation(pDVar5, local_18.nBodyloc);
		iVar4 = 3;
		if ((local_18.nBodyloc == 0xb) || (local_18.nBodyloc == 0xc))
		{
			iVar4 = 4;
		}
		iVar4 = INVENTORY_PlaceItemInSocket(pDVar8, pDVar5, iVar4);
		if (iVar4 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Trying to add a NULL item!\n");
			return;
		}
		iVar4 = INVENTORY_PlaceItemInBodyLoc(pDVar8, pDVar5, (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff);
		if (iVar4 != 0)
		{
			if ((local_18.nBodyloc != 4) && (local_18.nBodyloc != 5))
			{
				sub_6FB2B360(pUnit);
				sub_6FB2B360(pUnit);
				sub_6FB238D0();
				sub_6FB2FAD0(pDVar5);
				return;
			}
			INVENTORY_UpdateWeaponGUIDOnInsert(pDVar8, pDVar5);
			sub_6FB5B1D0((int)pUnit, 0);
			sub_6FB2B8E0(pDVar5, pUnit, 0, 0);
			sub_6FB2B360(pUnit);
			sub_6FB2B360(pUnit);
			uVar3 = ITEMS_GetWeaponClassId(pDVar5);
			uVar1 = uVar3;
			if ((local_18.nBodyloc != 4) && (uVar1 = byte_6FBBC208, local_18.nBodyloc == 5))
			{
				byte_6FBBC20A = uVar3;
			}
			byte_6FBBC208 = uVar1;
			sub_6FB5C080(pUnit);
			sub_6FB238D0();
			sub_6FB2FAD0(pDVar5);
		}
	}
}

//D2Client.0x6FB2D650
void __fastcall sub_6FB2D650(int a1)
{
	uint8_t bVar1;
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	uint32_t nFlags;
	D2StatListStrc* pStatList;
	int iVar4;
	int local_4;

	bVar1 = *(uint8_t*)(a1 + 2);
	local_4 = a1;
	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	ITEMS_DecodeItemFromBitstream(pDVar2, (uint8_t*)(a1 + 8), bVar1 - 8, 0, nullptr, 0x60, &local_4);
	if (local_4 != 0)
	{
		sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
		return;
	}
	pDVar3 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar3 != nullptr);
	pInventory = pDVar3->pInventory;
	D2_ASSERT(pInventory != nullptr);
	iVar4 = 8;
	nFlags = ITEMS_GetItemFlags(pDVar2);
	iVar4 = ITEMS_CheckIfFlagIsSet(nFlags, iVar4);
	if (iVar4 == 0)
	{
		INVENTORY_SetCursorItem(pInventory, nullptr);
		pDVar2 = INVENTORY_GetCursorItem(pInventory);
		sub_6FB575B0(pDVar2);
	}
	pDVar2 = INVENTORY_GetCursorItem(pInventory);
	if (pDVar2 != nullptr)
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pDVar2, 0x36);
		if (pStatList != nullptr)
		{
			STATES_ToggleState(pDVar2, 0x36, 0);
			D2Common_10474(pDVar2, pStatList);
			STATLIST_FreeStatList(pStatList);
			UNITS_UpdateAnimRateAndVelocity(pDVar2, __FILE__, __LINE__);
		}
	}
}

//D2Client.0x6FB2D760
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB2D760(int a1)
{
	D2InventoryStrc* pInventory;
	bool bVar1;
	uint8_t bVar2;
	int iVar3;
	D2UnitStrc* pUnit;
	D2UnitStrc* pItem;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;
	int iVar5;
	D2StatListStrc* pStatList;
	D2UnitStrc** ppExchangeItem;
	uint32_t uVar6;
	uint32_t* pHoveredItems;
	char* pcVar7;
	uint32_t uVar8;
	uint32_t uStack_28;
	uint32_t uStack_24;
	uint32_t uStack_20;
	D2UnitStrc* pDStack_1c;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	if (local_18.nStorePage == 0xff)
	{
		FOG_Trace("Invalid bpage in file %s\n", __FILE__);
		return;
	}
	iVar3 = sub_6FAFBB50(&uStack_24);
	if (iVar3 == 0)
	{
		return;
	}
	pUnit = sub_6FB269F0(uStack_24, 1);
	if (pUnit == nullptr)
	{
		return;
	}
	pInventory = pUnit->pInventory;
	if (pInventory == nullptr)
	{
		FOG_Trace("NULL inventory Error at line %d of file %s\n", __LINE__, __FILE__);
		return;
	}
	pItem = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	if (*(char*)(a1 + 1) == '\f')
	{
		if (pItem == nullptr)
		{
			return;
		}
		bVar1 = sub_6FAFB6D0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			FOG_Trace("got delete while no menu active at line %d of file %s\n", __LINE__, __FILE__);
		}
		else
		{
			sub_6FAE8F10();
		}
		pDVar4 = INVENTORY_RemoveItemFromInventory(pInventory, pItem);
		if (pDVar4 == nullptr)
		{
			FOG_Trace("NULL hRemove Error of item %x at line %d of file %s\n", pItem, __LINE__, __FILE__);
			return;
		}
		bVar2 = ITEMS_GetInvPage(pItem);
		uStack_28 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_28 + 1)), bVar2);
		if (bVar2 != 0xff)
		{
			iVar3 = sub_6FAAC080();
			iVar3 = UNITS_GetInventoryRecordId(pUnit, uStack_28, iVar3);
			INVENTORY_Return(__FILE__, __LINE__, pInventory,
			    (uint32_t)local_18.nX, (uint32_t)local_18.nY, iVar3, 1, bVar2);
			sub_6FB238D0();
			sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
			sub_6FAFAFE0(*(uint32_t*)(a1 + 4));
			return;
		}
		uVar6 = 0x7f6;
	LAB_6fb2d87e:
		FOG_Trace(" Invalid page %d at line %d of file %s\n", 0xff, uVar6,
		    __FILE__);
		return;
	}
	if (local_18.nStorePage == 0xff)
	{
		uVar6 = 0x803;
		goto LAB_6fb2d87e;
	}
	if (pItem == nullptr)
	{
		pItem = sub_6FB2AE60(a1, &local_18, 0, 0, 0);
		uStack_28 = (*(uint32_t*)((uint8_t*)&local_18 + 16));
	}
	else
	{
		iVar3 = INVENTORY_CompareWithItemsParentInventory(pInventory, pItem);
		iVar5 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
		if (iVar5 != 0)
		{
			sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
			pItem = sub_6FB2AE60(a1, &local_18, 0, 0, 0);
			if (pItem == nullptr)
			{
				FOG_Trace("NULL Error %d at line %d of file %s\n", iVar3, __LINE__, __FILE__);
				return;
			}
			bVar2 = ITEMS_GetInvPage(pItem);
			if (local_18.nStorePage != bVar2)
			{
				pcVar7 = __FILE__;
				uVar6 = 0x81e;
				bVar2 = ITEMS_GetInvPage(pItem);
				FOG_Trace(" Add Error page conflict %d:%d  %dat line %d of file %s\n", (*(uint32_t*)((uint8_t*)&local_18 + 16)) & 0xff, (uint32_t)bVar2,
				    iVar3, uVar6, pcVar7);
				return;
			}
			goto LAB_6fb2d9f8;
		}
		uStack_28 = (*(uint32_t*)((uint8_t*)&local_18 + 16)) & 0xff;
		sub_6FB2A8E0(pItem, 0, 0.0, 0, 0, 0);
	}
	ITEMS_SetInvPage(pItem, (uint8_t)uStack_28);
LAB_6fb2d9f8:
	ITEMS_SetInvPage(pItem, local_18.nStorePage);
	pHoveredItems = &uStack_20;
	ppExchangeItem = &pDStack_1c;
	uVar8 = (*(uint32_t*)((uint8_t*)&local_18 + 16));
	iVar3 = sub_6FAAC080();
	bVar2 = (uint8_t)uVar8;
	iVar3 = UNITS_GetInventoryRecordId(pUnit, (*(uint32_t*)((uint8_t*)&local_18 + 16)), iVar3);
	iVar3 = INVENTORY_CanItemBePlaced(pInventory, pItem, (uint32_t)local_18.nX, (uint32_t)local_18.nY, iVar3, ppExchangeItem,
	    pHoveredItems, bVar2);
	if (iVar3 != 0)
	{
		sub_6FB2BD70(CONCAT22(local_18.nY, local_18.nX), CONCAT22((*(uint16_t*)((uint8_t*)&local_18 + 8)), local_18.nY),
		    (*(uint32_t*)((uint8_t*)&local_18 + 16)), pUnit, pItem);
		sub_6FAE94D0();
		D2_ASSERT(pItem != nullptr);
		pStatList = STATLIST_GetStatListFromUnitAndState(pItem, 0x36);
		if (pStatList != nullptr)
		{
			STATES_ToggleState(pItem, 0x36, 0);
			D2Common_10474(pItem, pStatList);
			STATLIST_FreeStatList(pStatList);
			UNITS_UpdateAnimRateAndVelocity(pItem, __FILE__, __LINE__);
		}
	}
}

//D2Client.0x6FB2DAC0
void __fastcall sub_6FB2DAC0(int a1)
{
	D2InventoryStrc* pDVar1;
	uint8_t bVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	D2UnitStrc** nYPos;
	int bUnused;
	int iStack_1c;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pDVar3 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	if (pDVar3 != nullptr)
	{
		if (pDVar3->dwAnimMode == 0)
		{
			pDVar3 = CUNIT_GetPlayer();
			D2_ASSERT(pDVar3 != nullptr);
			pDVar4 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
			bVar2 = ITEMS_GetInvPage(pDVar4);
			pDVar1 = pDVar3->pInventory;
			iStack_1c = CONCAT31((*(uint8_t*)((uint8_t*)&iStack_1c + 1)), bVar2);
			D2_ASSERT(pDVar1 != nullptr);
			if (pDVar3->dwUnitType == 0)
			{
				INVENTORY_GetLeftHandWeapon(pDVar1);
			}
			iVar5 = ITEMS_CheckItemFlag(pDVar4, 0x100, __LINE__, __FILE__);
			if (iVar5 == 0)
			{
				STATLIST_ExpireUnitStatlist(pDVar3, pDVar4);
			}
			pDVar6 = INVENTORY_RemoveItemFromInventory(pDVar1, pDVar4);
			D2_ASSERT(pDVar6 != nullptr);
			D2_ASSERT(pDVar6 == pDVar4);
			iVar5 = sub_6FAAC080();
			iVar5 = UNITS_GetInventoryRecordId(pDVar3, iStack_1c, iVar5);
			INVENTORY_Return(__FILE__, __LINE__, pDVar1, (uint32_t)local_18.nX,
			    (uint32_t)local_18.nY, iVar5, 1, bVar2);
			sub_6FAE8F10();
			iVar5 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
			if (iVar5 == 0)
			{
				sub_6FB2DE80(pDVar4, 0, 0, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0, (*(uint32_t*)((uint8_t*)&local_18 + 16)));
			}
			else
			{
				sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
				pDVar4 = sub_6FB2AE60(a1, &local_18, 0, 0, 0);
				D2_ASSERT(pDVar4 != nullptr);
			}
			INVENTORY_SetCursorItem(pDVar1, pDVar4);
			pDVar3 = INVENTORY_GetCursorItem(pDVar1);
			sub_6FB575B0(pDVar3);
			sub_6FB2FAD0(pDVar4);
			return;
		}
		if (pDVar3->dwAnimMode == 4)
		{
			pDVar3 = CUNIT_GetPlayer();
			D2_ASSERT(pDVar3 != nullptr);
			pDVar4 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
			iVar5 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
			if (iVar5 == 0)
			{
				sub_6FB2DE80(pDVar4, 0, 0, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0, (*(uint32_t*)((uint8_t*)&local_18 + 16)));
			}
			else
			{
				sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
				pDVar4 = sub_6FB2AE60(a1, &local_18, 0, 0, 0);
				D2_ASSERT(pDVar4 != nullptr);
			}
			pDVar1 = pDVar3->pInventory;
			D2_ASSERT(pDVar1 != nullptr);
			UNITS_SetXForStaticUnit(pDVar4, (uint32_t)local_18.nX);
			UNITS_SetYForStaticUnit(pDVar4, (uint32_t)local_18.nY);
			iVar5 = INVENTORY_PlaceItemInSocket(pDVar1, pDVar4, 1);
			if (iVar5 == 0)
			{
				FOG_Trace("[INVENTORY ERROR] Trying to add a NULL item!\n");
				return;
			}
			bVar2 = ITEMS_GetInvPage(pDVar4);
			iStack_1c = CONCAT31((*(uint8_t*)((uint8_t*)&iStack_1c + 1)), bVar2);
			if (local_18.nStorePage == 0xff)
			{
				FOG_Trace(" Invalid page %d at line %d of file %s\n", 0xff, __LINE__, __FILE__);
				return;
			}
			bUnused = 1;
			iVar5 = iStack_1c;
			iVar7 = sub_6FAAC080();
			bVar2 = (uint8_t)iVar5;
			iVar5 = UNITS_GetInventoryRecordId(pDVar3, iStack_1c, iVar7);
			nYPos = sub_6FAB6A90((int*)pDVar4);
			iVar7 = sub_6FAB6A60((int*)pDVar4);
			iVar5 = INVENTORY_PlaceItemAtInventoryPage(pDVar1, pDVar4, iVar7, (int)nYPos, iVar5, bUnused, bVar2);
			D2_ASSERT(iVar5);
			iVar5 = ITEMS_IsCharmUsable(pDVar4, pDVar3);
			if (iVar5 != 0)
			{
				sub_6FB2B8E0(pDVar4, pDVar3, 0, 0);
			}
			sub_6FB238D0();
			sub_6FB2FAD0(pDVar4);
		}
	}
}

//D2Client.0x6FB2DE80
void __fastcall sub_6FB2DE80(D2UnitStrc* ptItem, uint16_t a2, uint16_t a3, int a4, int a5, uint32_t a6)
{
	D2ActiveRoomStrc* pDVar1;

	D2_ASSERT(ptItem != nullptr);
	pDVar1 = nullptr;
	if ((a5 != 0) && ((a2 != 0 || (a3 != 0))))
	{
		pDVar1 = sub_6FB26C90((uint32_t)a2, (uint32_t)a3);
	}
	sub_6FB2A8E0(ptItem, pDVar1, (float)(uint32_t)a2, (uint32_t)a3, a4, 0);
	ITEMS_SetInvPage(ptItem, (uint8_t)a6);
}

//D2Client.0x6FB2DF10
void __fastcall sub_6FB2DF10(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pItem;
	int iVar2;
	uint32_t uVar3;
	D2StatListStrc* pStatList;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pDVar1 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar1 != nullptr);
	pItem = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	if (pItem == nullptr)
	{
		pItem = sub_6FB2AE60(a1, &local_18, 0, 0, 1);
	}
	else
	{
		sub_6FB2A8E0(pItem, 0, 0.0, 0, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
		ITEMS_SetInvPage(pItem, local_18.nStorePage);
	}
	UNITS_SetXForStaticUnit(pItem, (uint32_t)local_18.nX);
	UNITS_SetYForStaticUnit(pItem, (uint32_t)local_18.nY);
	pInventory = pDVar1->pInventory;
	D2_ASSERT(pInventory != nullptr);
	iVar2 = INVENTORY_PlaceItemInSocket(pInventory, pItem, 2);
	if (iVar2 != 0)
	{
		uVar3 = pItem->dwUnitType;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			iVar2 = pItem->pDynamicPath->dwClientCoordY;
		}
		else if (pItem->pDynamicPath == nullptr)
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = PATH_GetXPosition(pItem->pDynamicPath);
		}
		INVENTORY_PlaceItemInBeltSlot(pInventory, pItem, iVar2);
	}
	iVar2 = ITEMS_IsCharmUsable(pItem, pDVar1);
	if (iVar2 != 0)
	{
		sub_6FB2B8E0(pItem, pDVar1, 0, 0);
	}
	if ((local_18.dwFlags & 0x400) != 0)
	{
		ITEMS_SetItemFlag(pItem, 0x400, 1);
	}
	INVENTORY_SetCursorItem(pInventory, nullptr);
	pDVar1 = INVENTORY_GetCursorItem(pInventory);
	sub_6FB575B0(pDVar1);
	uVar3 = pItem->dwUnitType;
	if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
	{
		uVar3 = pItem->pDynamicPath->dwClientCoordY;
	}
	else if (pItem->pDynamicPath == nullptr)
	{
		uVar3 = 0;
	}
	else
	{
		uVar3 = PATH_GetXPosition(pItem->pDynamicPath);
	}
	sub_6FB01B10(uVar3, 1);
	sub_6FB238D0();
	pStatList = STATLIST_GetStatListFromUnitAndState(pItem, 0x36);
	if (pStatList != nullptr)
	{
		STATES_ToggleState(pItem, 0x36, 0);
		D2Common_10474(pItem, pStatList);
		STATLIST_FreeStatList(pStatList);
		UNITS_UpdateAnimRateAndVelocity(pItem, __FILE__, __LINE__);
	}
	sub_6FAFAF00(pItem->dwUnitId);
}

//D2Client.0x6FB2E100
void __fastcall sub_6FB2E100(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar2;
	int iVar3;
	D2StatListStrc* pStatList;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pDVar1 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar1 != nullptr);
	pItem = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	pInventory = pDVar1->pInventory;
	D2_ASSERT(pInventory != nullptr);
	pDVar2 = INVENTORY_RemoveItemFromInventory(pInventory, pItem);
	if (pDVar2 != nullptr)
	{
		D2_ASSERT(pDVar2 == pItem);
		D2COMMON_10267_Return((int)pInventory, (*(uint32_t*)((uint8_t*)&local_18 + 4)) & 0xffff);
		sub_6FB01B20();
		sub_6FB01B10((*(uint32_t*)((uint8_t*)&local_18 + 4)) & 0xffff, 0);
		if (pDVar1->dwUnitType == 0)
		{
			INVENTORY_GetLeftHandWeapon(pDVar1->pInventory);
		}
		iVar3 = ITEMS_CheckItemFlag(pItem, 0x100, __LINE__, __FILE__);
		if (iVar3 == 0)
		{
			STATLIST_ExpireUnitStatlist(pDVar1, pItem);
		}
		iVar3 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 0x20);
		if (iVar3 == 0)
		{
			D2_ASSERT(pItem != nullptr);
			sub_6FB2A8E0(pItem, 0, 0.0, 0, (*(uint32_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
			ITEMS_SetInvPage(pItem, local_18.nStorePage);
			INVENTORY_SetCursorItem(pInventory, pItem);
			pDVar1 = INVENTORY_GetCursorItem(pInventory);
			sub_6FB575B0(pDVar1);
			pStatList = STATLIST_GetStatListFromUnitAndState(pItem, 0x36);
			if (pStatList != nullptr)
			{
				STATES_ToggleState(pItem, 0x36, 0);
				D2Common_10474(pItem, pStatList);
				STATLIST_FreeStatList(pStatList);
				UNITS_UpdateAnimRateAndVelocity(pItem, __FILE__, __LINE__);
				return;
			}
		}
		else
		{
			sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
			sub_6FB575B0(nullptr);
		}
	}
}

//D2Client.0x6FB2E2E0
void __fastcall sub_6FB2E2E0(int a1)
{
	D2InventoryStrc* pDVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	D2StatListStrc* pStatList;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	if (pDVar2 != nullptr)
	{
		if (pDVar2->dwAnimMode == 2)
		{
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 != nullptr)
			{
				pDVar3 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
				if (pDVar3 != nullptr)
				{
					pDVar1 = pDVar2->pInventory;
					D2_ASSERT(pDVar1 != nullptr);
					pDVar4 = INVENTORY_RemoveItemFromInventory(pDVar1, pDVar3);
					D2_ASSERT(pDVar4 != nullptr);
					D2_ASSERT(pDVar4 == pDVar3);
					if (pDVar2->dwUnitType == 0)
					{
						INVENTORY_GetLeftHandWeapon(pDVar2->pInventory);
					}
					iVar5 = ITEMS_CheckItemFlag(pDVar3, 0x100, __LINE__, __FILE__);
					if (iVar5 == 0)
					{
						STATLIST_ExpireUnitStatlist(pDVar2, pDVar3);
					}
					D2COMMON_10267_Return((int)pDVar1, (uint32_t)local_18.nX);
					sub_6FB2DE80(pDVar3, 0, 0, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0, (*(uint32_t*)((uint8_t*)&local_18 + 16)));
					INVENTORY_SetCursorItem(pDVar1, pDVar3);
					pDVar2 = INVENTORY_GetCursorItem(pDVar1);
					sub_6FB575B0(pDVar2);
					pStatList = STATLIST_GetStatListFromUnitAndState(pDVar3, 0x36);
					if (pStatList != nullptr)
					{
						STATES_ToggleState(pDVar3, 0x36, 0);
						D2Common_10474(pDVar3, pStatList);
						STATLIST_FreeStatList(pStatList);
						UNITS_UpdateAnimRateAndVelocity(pDVar3, __FILE__, __LINE__);
						return;
					}
				}
			}
		}
		else if (pDVar2->dwAnimMode == 4)
		{
			pDVar2 = CUNIT_GetPlayer();
			D2_ASSERT(pDVar2 != nullptr);
			pDVar3 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
			if (pDVar3 != nullptr)
			{
				sub_6FB2A8E0(pDVar3, 0, 0.0, 0, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
				ITEMS_SetInvPage(pDVar3, local_18.nStorePage);
				pDVar1 = pDVar2->pInventory;
				if (pDVar1 == nullptr)
				{
					FOG_DisplayAssert("hInventory", __FILE__, __LINE__);
					exit(-1);
				}
				UNITS_SetXForStaticUnit(pDVar3, (uint32_t)local_18.nX);
				UNITS_SetYForStaticUnit(pDVar3, (uint32_t)local_18.nY);
				iVar5 = ITEMS_CheckItemTypeId(pDVar3, 0xd);
				if (iVar5 != 0)
				{
					sub_6FB2B8E0(pDVar3, pDVar2, 0, 0);
				}
				iVar5 = INVENTORY_PlaceItemInSocket(pDVar1, pDVar3, 2);
				if (iVar5 != 0)
				{
					iVar5 = sub_6FAB6A60((int*)pDVar3);
					iVar5 = INVENTORY_PlaceItemInBeltSlot(pDVar1, pDVar3, iVar5);
					D2_ASSERT(iVar5);
				}
				sub_6FB238D0();
				sub_6FB2FAD0(pDVar3);
			}
		}
	}
}

//D2Client.0x6FB2E590
int32_t __fastcall sub_6FB2E590(D2UnitStrc* pUnit)
{
	return sub_6FB2AA90(pUnit, nullptr);
}

//D2Client.0x6FB2E5A0
int __fastcall sub_6FB2E5A0(D2UnitStrc* pUnit)
{
	int iVar1;
	D2ItemsTxt* pDVar2;
	int iVar3;

	iVar3 = 0;
	if (pUnit == nullptr)
	{
		iVar1 = -1;
	}
	else
	{
		iVar1 = pUnit->dwClassId;
	}
	pDVar2 = DATATBLS_GetItemsTxtRecord(iVar1);
	if ((pDVar2 != nullptr) && (0 < (short)pDVar2->wDropSound))
	{
		iVar3 = (int)(short)pDVar2->wUseSound;
	}
	iVar1 = ITEMS_GetItemQuality(pUnit);
	if (iVar1 == 7)
	{
		iVar1 = ITEMS_GetFileIndex(pUnit);
		if (((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc28))) &&
		    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc24) + iVar1 * 0x14c, iVar1 != 0 &&
		                                                                                       (0 < *(short*)(iVar1 + 0x84)))))
		{
			return (int)*(short*)(iVar1 + 0x86);
		}
	}
	else
	{
		iVar1 = ITEMS_GetItemQuality(pUnit);
		if (iVar1 == 5)
		{
			iVar1 = ITEMS_GetFileIndex(pUnit);
			if ((((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc1c))) &&
			        (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc18) + iVar1 * 0x1b8, iVar1 != 0)) &&
			    (0 < *(short*)(iVar1 + 0x82)))
			{
				iVar3 = (int)*(short*)(iVar1 + 0x84);
			}
		}
	}
	return iVar3;
}

//D2Client.0x6FB2E680
void __cdecl sub_6FB2E680()
{
	byte_6FBBC208 = 0;
	byte_6FBBC20A = 0;
}

//D2Client.0x6FB2E690
uint32_t __fastcall sub_6FB2E690(D2UnitStrc* pUnit, int a2, uint32_t a3, uint32_t a4)
{
	D2StatListStrc* pStatList;
	int iVar1;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint16_t nLayer;

	nLayer = (short)(a2 << ((uint8_t) * (uint32_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc6c) & 0x1f)) + ((uint16_t) * (uint32_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc70) & (uint16_t)a3);
	pStatList = STATLIST_GetStatListFromUnitAndFlag(pUnit, 0x40);
	while (true)
	{
		if (pStatList == nullptr)
		{
			if ((pUnit->pInventory != nullptr) &&
			    (pItem = INVENTORY_GetFirstItem(pUnit->pInventory), pItem != nullptr))
			{
				do
				{
					pDVar2 = INVENTORY_UnitIsItem(pItem);
					iVar1 = sub_6FB2E690(pDVar2, a2, a3, a4);
					if (iVar1 != 0)
					{
						return 1;
					}
					pItem = INVENTORY_GetNextItem(pItem);
				} while (pItem != nullptr);
				return 0;
			}
			return 0;
		}
		iVar1 = STATLIST_GetStatValue(pStatList, 0xcc, nLayer);
		if (iVar1 != 0)
			break;
		pStatList = STATLIST_GetStatListFromFlag(pStatList, 0x40);
	}
	uVar3 = iVar1 >> 8;
	if ((int)uVar3 < 1)
	{
		return 0;
	}
	if ((int)uVar3 < 0x100)
	{
		uVar4 = a4 & ((int)a4 < 1) - 1;
		if ((int)uVar3 <= (int)uVar4)
		{
			uVar4 = uVar3;
		}
		STATLIST_SetBaseStat2(pStatList, 0xcc, uVar3 * 0x100 + (uVar4 & 0xff), nLayer, pUnit);
		return 1;
	}
	return 0;
}

//D2Client.0x6FB2E780
void __fastcall sub_6FB2E780(uint32_t a1, char a2, int a3, int a4, uint32_t a5)
{
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;

	pDVar1 = sub_6FB269F0(a1, 4);
	if (pDVar1 != nullptr)
	{
		if (a3 == 0xcc)
		{
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 != nullptr)
			{
				sub_6FB2E690(pDVar1, (a5 & 0xffff) >> (*(uint8_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc6c) & 0x1f),
				    *(uint32_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc70) & a5 & 0xffff,
				    a4 & 0xff);
				return;
			}
		}
		else
		{
			if (a2 == '\x01')
			{
				STATLIST_SetUnitStat(pDVar1, a3, a4, 0);
			}
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 != nullptr)
			{
				if (a3 != 0x46)
				{
					pDVar1 = CUNIT_GetPlayer();
					sub_6FB2B360(pDVar1);
					return;
				}
				if (0 < a4)
				{
					iVar3 = ITEMS_CheckItemFlag(pDVar1, 4, __LINE__, __FILE__);
					if (iVar3 != 0)
					{
						ITEMS_SetItemFlag(pDVar1, 4, 0);
					}
					iVar3 = ITEMS_CheckItemFlag(pDVar1, 0x4000, __LINE__, __FILE__);
					if (iVar3 != 0)
					{
						ITEMS_SetItemFlag(pDVar1, 0x4000, 0);
					}
				}
			}
		}
	}
}

//D2Client.0x6FB2E880
void __fastcall sub_6FB2E880(int a1)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2StatListStrc* pStatList;
	uint32_t uVar3;

	if (*(short*)(a1 + 6) == -1)
	{
		if (*(char*)(a1 + 1) == -1)
		{
			pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), 4);
			if (pDVar2 != nullptr)
			{
				ITEMS_SetItemFlag(pDVar2, 4, 0);
				pStatList = STATLIST_GetStatListFromUnitAndState(pDVar2, 0x36);
				if (pStatList != nullptr)
				{
					STATES_ToggleState(pDVar2, 0x36, 0);
					D2Common_10474(pDVar2, pStatList);
					STATLIST_FreeStatList(pStatList);
					UNITS_UpdateAnimRateAndVelocity(pDVar2, __FILE__, __LINE__);
				}
			}
			sub_6FB575B0(nullptr);
			return;
		}
		uVar3 = 0;
		if (dword_6FB90C30 != 0)
		{
			do
			{
				if (((uint32_t) * (uint8_t*)(a1 + 1) == (&dword_6FB90C28)[uVar3]) &&
				    (iVar1 = sub_6FB23860(1), iVar1 == 0))
				{
					sub_6FB23260(1, 0, 0);
				}
				uVar3 = uVar3 + 1;
			} while (uVar3 < dword_6FB90C30);
		}
		pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), 4);
		if (pDVar2 != nullptr)
		{
			ITEMS_SetItemFlag(pDVar2, 4, 1);
			sub_6FB57560(pDVar2, (uint32_t) * (uint8_t*)(a1 + 1));
			return;
		}
	}
	else
	{
		uVar3 = 0;
		if (dword_6FB90C30 != 0)
		{
			do
			{
				if (((uint32_t) * (uint8_t*)(a1 + 1) == (&dword_6FB90C28)[uVar3]) &&
				    (iVar1 = sub_6FB23860(1), iVar1 == 0))
				{
					sub_6FB23260(1, 0, 0);
					break;
				}
				uVar3 = uVar3 + 1;
			} while (uVar3 < dword_6FB90C30);
		}
		pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), 4);
		if (pDVar2 != nullptr)
		{
			sub_6FB57560(pDVar2, (uint32_t) * (uint8_t*)(a1 + 1));
			return;
		}
	}
}

//D2Client.0x6FB2E9D0
void __fastcall sub_6FB2E9D0(int a1)
{
	D2UnitStrc* pItem;

	pItem = sub_6FB269F0(*(uint32_t*)(a1 + 1), 4);
	if (pItem != nullptr)
	{
		ITEMS_SetItemFlag(pItem, *(uint32_t*)(a1 + 5), *(int*)(a1 + 9));
	}
}

//D2Client.0x6FB2EA00
void __fastcall sub_6FB2EA00(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	D2StatListStrc* pDVar4;
	int iVar5;
	D2UnitStrc* pDStack_24;
	int local_20;
	int iStack_1c;
	D2ItemSaveStrc local_18;

	local_20 = a1;
	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_18);
	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pDVar1 != nullptr)
	{
		iVar2 = sub_6FAAC080();
		iStack_1c = UNITS_GetInventoryRecordId(pDVar1, 0, iVar2);
		pInventory = pDVar1->pInventory;
		D2_ASSERT(pInventory != nullptr);
		pDStack_24 = INVENTORY_GetItemFromBodyLoc(pInventory, (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff);
		D2_ASSERT(pDStack_24 != nullptr);
		sub_6FB5DA40(pDVar1);
		INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pDStack_24);
		sub_6FB5C2E0(pDVar1, (uint32_t) * (uint8_t*)(a1 + 3));
		INVENTORY_GetSecondWieldingWeapon(pDVar1, pInventory, &pDStack_24, (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff);
		pDVar3 = INVENTORY_RemoveItemFromInventory(pInventory, pDStack_24);
		D2_ASSERT(pDVar3 != nullptr);
		D2_ASSERT(pDVar3 == pDStack_24);
		if (pDVar1->dwUnitType == 0)
		{
			INVENTORY_GetLeftHandWeapon(pDVar1->pInventory);
		}
		iVar2 = ITEMS_CheckItemFlag(pDVar3, 0x100, __LINE__, __FILE__);
		if (iVar2 == 0)
		{
			STATLIST_ExpireUnitStatlist(pDVar1, pDVar3);
		}
		ITEMS_UpdateSets(pDVar1, pDVar3, 1, 1);
		pDVar4 = STATLIST_GetStatListFromUnitAndState(pDVar3, 0x36);
		if (pDVar4 != nullptr)
		{
			STATES_ToggleState(pDVar3, 0x36, 0);
			D2Common_10474(pDVar3, pDVar4);
			STATLIST_FreeStatList(pDVar4);
			UNITS_UpdateAnimRateAndVelocity(pDVar3, __FILE__, __LINE__);
		}
		D2COMMON_10254_Return0((int)pInventory, (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff);
		sub_6FB5C080(pDVar1);
		iVar5 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
		iVar2 = local_20;
		pDVar3 = pDStack_24;
		if (iVar5 == 0)
		{
			local_20 = CONCAT31((*(uint8_t*)((uint8_t*)&local_20 + 1)), local_18.nStorePage);
			D2_ASSERT(pDStack_24 != nullptr);
			sub_6FB2A8E0(pDStack_24, 0, 0.0, 0, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
			ITEMS_SetInvPage(pDVar3, (uint8_t)local_20);
		}
		else
		{
			sub_6FB26BE0(*(uint32_t*)(local_20 + 4), 4);
			pDVar3 = CUNIT_GetPlayer();
			if (pDVar1 == pDVar3)
			{
				pDStack_24 = sub_6FB2C1D0(iVar2, &local_18, 0, 0, 0);
				D2_ASSERT(pDStack_24 != nullptr);
			}
		}
		pDVar3 = CUNIT_GetPlayer();
		if (pDVar1 == pDVar3)
		{
			sub_6FAE8F10();
			if (local_18.nBodyloc == 4)
			{
				byte_6FBBC208 = 0;
			}
			else if (local_18.nBodyloc == 5)
			{
				byte_6FBBC20A = 0;
			}
			iVar2 = INVENTORY_PlaceItemAtInventoryPage(pInventory, pDStack_24, (uint32_t)local_18.nX, (uint32_t)local_18.nY, iStack_1c, 1, 0);
			if (iVar2 == 0)
			{
				FOG_DisplayWarning("Unable to insert item in grid",
				    __FILE__, __LINE__);
			}
			else
			{
				iVar2 = INVENTORY_PlaceItemInSocket(pInventory, pDStack_24, 1);
				if (iVar2 == 0)
				{
					FOG_Trace("[INVENTORY ERROR] Trying to add a NULL item!\n");
					return;
				}
				ITEMS_SetBodyLocation(pDStack_24, 0);
				INVENTORY_SetCursorItem(pInventory, nullptr);
				pDVar3 = INVENTORY_GetCursorItem(pInventory);
				sub_6FB575B0(pDVar3);
			}
			sub_6FB2B360(pDVar1);
			sub_6FB2B360(pDVar1);
			pDVar1 = pDStack_24;
			D2_ASSERT(pDStack_24 != nullptr);
			pDVar4 = STATLIST_GetStatListFromUnitAndState(pDStack_24, 0x36);
			if (pDVar4 != nullptr)
			{
				STATES_ToggleState(pDVar1, 0x36, 0);
				D2Common_10474(pDVar1, pDVar4);
				STATLIST_FreeStatList(pDVar4);
				UNITS_UpdateAnimRateAndVelocity(pDVar1, __FILE__, __LINE__);
			}
		}
	}
}

//D2Client.0x6FB2EDA0
void __fastcall sub_6FB2EDA0(int a1)
{
	D2InventoryStrc* pInventory;
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;

	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar2 != nullptr)
	{
		pDVar3 = CUNIT_GetPlayer();
		if (pDVar2 == pDVar3)
		{
			pInventory = pDVar2->pInventory;
			pDVar2 = INVENTORY_GetCursorItem(pInventory);
			if (pDVar2 != nullptr)
			{
				uVar1 = pDVar2->dwUnitId;
				INVENTORY_SetCursorItem(pInventory, nullptr);
				pDVar3 = INVENTORY_GetCursorItem(pInventory);
				sub_6FB575B0(pDVar3);
				sub_6FB26BE0(uVar1, pDVar2->dwUnitType);
				sub_6FAFAAA0(uVar1);
				return;
			}
		}
	}
}

//D2Client.0x6FB2EE00
void __fastcall sub_6FB2EE00(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 2) - 8, 0, &local_18);
	pDVar1 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar1 != nullptr);
	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
	if (pDVar2 != nullptr)
	{
		sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
	}
	pDVar2 = sub_6FB2AE60(a1, &local_18, 0, 0, 0);
	pInventory = pDVar1->pInventory;
	D2_ASSERT(pInventory != nullptr);
	INVENTORY_SetCursorItem(pInventory, pDVar2);
	pDVar1 = INVENTORY_GetCursorItem(pInventory);
	sub_6FB575B0(pDVar1);
}

//D2Client.0x6FB2EEC0
void __fastcall sub_6FB2EEC0(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pItem;
	int iVar2;
	D2UnitStrc* pDVar3;
	D2StatListStrc* pStatList;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_18);
	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pDVar1 != nullptr)
	{
		pItem = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
		if (pItem == nullptr)
		{
			pItem = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
		}
		else
		{
			sub_6FB2A8E0(pItem, 0, (float)(uint32_t)local_18.nX, (uint32_t)local_18.nY, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff,
			    0);
			ITEMS_SetInvPage(pItem, local_18.nStorePage);
		}
		D2_ASSERT(pDVar1->pInventory != nullptr);
		iVar2 = INVENTORY_PlaceItemInSocket(pDVar1->pInventory, pItem, 1);
		if (iVar2 != 0)
		{
			iVar2 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 8);
			if (iVar2 == 0)
			{
				pDVar3 = CUNIT_GetPlayer();
				pInventory = pDVar3->pInventory;
				D2_ASSERT(pInventory != nullptr);
				INVENTORY_SetCursorItem(pInventory, nullptr);
				pDVar3 = INVENTORY_GetCursorItem(pInventory);
				sub_6FB575B0(pDVar3);
			}
			sub_6FB2B8E0(pItem, pDVar1, 1, 0);
		}
		D2_ASSERT(pItem != nullptr);
		pStatList = STATLIST_GetStatListFromUnitAndState(pItem, 0x36);
		if (pStatList != nullptr)
		{
			STATES_ToggleState(pItem, 0x36, 0);
			D2Common_10474(pItem, pStatList);
			STATLIST_FreeStatList(pStatList);
			UNITS_UpdateAnimRateAndVelocity(pItem, __FILE__, __LINE__);
		}
	}
}

//D2Client.0x6FB2F050
void __fastcall sub_6FB2F050(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	D2StatListStrc* pStatList;
	uint32_t nBodyLoc;
	D2UnitStrc* pItem;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_18);
	pDVar1 = CUNIT_GetPlayer();
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pUnit != nullptr)
	{
		pInventory = pUnit->pInventory;
		D2_ASSERT(pInventory != nullptr);
		pItem = nullptr;
		if (pUnit == pDVar1)
		{
			pItem = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
			if (pItem == nullptr)
			{
				return;
			}
			pDVar1 = INVENTORY_RemoveItemFromInventory(pInventory, pItem);
			D2_ASSERT(pItem == pDVar1);
			iVar2 = sub_6FAAC080();
			iVar2 = UNITS_GetInventoryRecordId(pUnit, 0, iVar2);
			INVENTORY_Return(__FILE__, __LINE__, pInventory,
			    (uint32_t)local_18.nX, (uint32_t)local_18.nY, iVar2, 1, 0);
			sub_6FAE8F10();
			sub_6FB238D0();
		}
		iVar2 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 1);
		if (iVar2 == 0)
		{
			if (pItem == nullptr)
			{
				pItem = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
				D2_ASSERT(pItem != nullptr);
			}
			else
			{
				sub_6FB2A8E0(pItem, 0, 0.0, 0, (uint16_t)(*(uint16_t*)((uint8_t*)&local_18 + 8)) & 0xff, 0);
				ITEMS_SetInvPage(pItem, local_18.nStorePage);
			}
		}
		else
		{
			sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
			pItem = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
			D2_ASSERT(pItem != nullptr);
		}
		ITEMS_SetBodyLocation(pItem, local_18.nBodyloc);
		iVar2 = 3;
		if ((local_18.nBodyloc == 0xb) || (local_18.nBodyloc == 0xc))
		{
			iVar2 = 4;
		}
		iVar2 = INVENTORY_PlaceItemInSocket(pInventory, pItem, iVar2);
		if (iVar2 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Trying to add a NULL item!\n");
			return;
		}
		nBodyLoc = (*(uint32_t*)((uint8_t*)&local_18 + 17)) & 0xff;
		pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, nBodyLoc);
		if (pDVar1 != nullptr)
		{
			D2COMMON_10254_Return0((int)pInventory, nBodyLoc);
			FOG_Trace("[INVENTORY ERROR] Forced an item into unit's body location!");
		}
		iVar2 = INVENTORY_PlaceItemInBodyLoc(pInventory, pItem, nBodyLoc);
		if (iVar2 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Unable to insert item into unit's body location!");
			return;
		}
		sub_6FB5DA40(pUnit);
		INVENTORY_UpdateWeaponGUIDOnInsert(pInventory, pItem);
		sub_6FB5C080(pUnit);
		sub_6FB2B8E0(pItem, pUnit, 0, 0);
		sub_6FB2B360(pUnit);
		sub_6FB2B360(pUnit);
		pStatList = STATLIST_GetStatListFromUnitAndState(pItem, 0x36);
		if (pStatList != nullptr)
		{
			STATES_ToggleState(pItem, 0x36, 0);
			D2Common_10474(pItem, pStatList);
			STATLIST_FreeStatList(pStatList);
			UNITS_UpdateAnimRateAndVelocity(pItem, __FILE__, __LINE__);
		}
	}
}

//D2Client.0x6FB2F300
// TODO: decompilation needs review (extraout)
int* __fastcall sub_6FB2F300(int a1)
{
	uint8_t bVar1;
	D2InventoryStrc* pDVar2;
	uint16_t uVar3;
	uint16_t uVar4;
	D2UnitStrc* pDVar5;
	D2UnitStrc* pDVar6;
	D2UnitStrc* pDVar7;
	int iVar8;
	uint32_t uVar9;
	D2StatListStrc* pStatList;
	uint32_t extraout_ECX;
	uint32_t uVar10;
	D2UnitStrc* pDStack_28;
	D2UnitStrc* pDStack_24;
	int local_20;
	D2InventoryStrc* pDStack_1c;
	D2ItemSaveStrc local_18;

	local_20 = a1;
	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_18);
	pDStack_24 = CUNIT_GetPlayer();
	pDVar5 = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pDVar5 == nullptr)
	{
		return nullptr;
	}
	pDVar2 = pDVar5->pInventory;
	if (pDVar2 == nullptr)
	{
		return nullptr;
	}
	if (pDVar5->dwUnitType != 0)
	{
		return nullptr;
	}
	pDStack_1c = pDVar2;
	if ((pDVar5 == pDStack_24) && (local_18.nAnimMode == 0))
	{
		pDVar6 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
		if (pDVar6 != nullptr)
		{
			pDVar7 = INVENTORY_RemoveItemFromInventory(pDVar2, pDVar6);
			D2_ASSERT(pDVar7 == pDVar6);
			if (pDVar5->dwUnitType == 0)
			{
				INVENTORY_GetLeftHandWeapon(pDVar5->pInventory);
			}
			iVar8 = ITEMS_CheckItemFlag(pDVar7, 0x100, __LINE__, __FILE__);
			if (iVar8 == 0)
			{
				STATLIST_ExpireUnitStatlist(pDVar5, pDVar7);
			}
			sub_6FB26BE0(pDVar6->dwUnitId, pDVar6->dwUnitType);
			a1 = local_20;
		}
		sub_6FAE8F10();
		iVar8 = sub_6FAAC080();
		iVar8 = UNITS_GetInventoryRecordId(pDVar5, CONCAT22(local_18.pad0x12, CONCAT11(local_18.nBodyloc, local_18.nStorePage)), iVar8);
		INVENTORY_Return(__FILE__, __LINE__, pDVar2, (uint32_t)local_18.nX,
		    CONCAT12(local_18.nAnimMode, local_18.nY) & 0xffff, iVar8, 1, local_18.nStorePage);
		if (local_18.nStorePage == 0xff)
		{
			FOG_Trace(" Invalid page %d at line %d of file %s\n", 0xff, __LINE__, __FILE__);
			return nullptr;
		}
		pDVar6 = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
		sub_6FB2BD70(CONCAT22(local_18.nY, local_18.nX),
		    CONCAT13(local_18.pad0x09[0], CONCAT12(local_18.nAnimMode, local_18.nY)),
		    CONCAT22(local_18.pad0x12, CONCAT11(local_18.nBodyloc, local_18.nStorePage)), pDVar5,
		    pDVar6);
		iVar8 = ITEMS_IsCharmUsable(pDVar6, pDVar5);
		if (iVar8 != 0)
		{
			sub_6FB2B8E0(pDVar6, pDVar5, 0, 0);
		}
	}
	else if (local_18.nAnimMode == 1)
	{
		pDStack_28 = INVENTORY_GetItemFromBodyLoc(pDVar2, CONCAT21(local_18.pad0x12, local_18.nBodyloc) & 0xff);
		sub_6FB5DA40(pDVar5);
		if (pDStack_28 == nullptr)
		{
			return (int*)pDStack_28;
		}
		INVENTORY_UpdateWeaponGUIDOnRemoval(pDVar2, pDStack_28);
		sub_6FB5C2E0(pDVar5, (uint32_t) * (uint8_t*)(a1 + 3));
		INVENTORY_GetSecondWieldingWeapon(pDVar5, pDVar2, &pDStack_28, (uint32_t)local_18.nBodyloc);
		pDVar6 = INVENTORY_RemoveItemFromInventory(pDVar2, pDStack_28);
		D2_ASSERT(pDVar6 == pDStack_28);
		if (pDVar5->dwUnitType == 0)
		{
			INVENTORY_GetLeftHandWeapon(pDVar5->pInventory);
		}
		iVar8 = ITEMS_CheckItemFlag(pDVar6, 0x100, __LINE__, __FILE__);
		if (iVar8 == 0)
		{
			STATLIST_ExpireUnitStatlist(pDVar5, pDVar6);
		}
		ITEMS_UpdateSets(pDVar5, pDVar6, 1, 1);
		D2COMMON_10254_Return0((int)pDVar2, (uint32_t)local_18.nBodyloc);
		sub_6FB5C080(pDVar5);
		if (pDStack_28 == nullptr)
		{
			uVar10 = 6;
			uVar9 = 0xffffffff;
		}
		else
		{
			uVar10 = pDStack_28->dwUnitType;
			uVar9 = pDStack_28->dwUnitId;
		}
		sub_6FB26BE0(uVar9, uVar10);
		pDStack_28 = nullptr;
		if (pDVar5 == pDStack_24)
		{
			sub_6FAE8F10();
			if (local_18.nBodyloc == 4)
			{
				byte_6FBBC208 = 0;
			}
			else if (local_18.nBodyloc == 5)
			{
				byte_6FBBC20A = 0;
			}
		}
		pDVar6 = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
		ITEMS_SetBodyLocation(pDVar6, local_18.nBodyloc);
		iVar8 = 3;
		if ((local_18.nBodyloc == 0xb) || (local_18.nBodyloc == 0xc))
		{
			iVar8 = 4;
		}
		iVar8 = INVENTORY_PlaceItemInSocket(pDVar2, pDVar6, iVar8);
		if (iVar8 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Trying to add a NULL item!\n");
			return nullptr;
		}
		uVar10 = (uint32_t)local_18.nBodyloc;
		if (pDVar6 == nullptr)
		{
			FOG_Trace("[INVENTORY ERROR] Trying to insert null item into unit's body location!");
			return nullptr;
		}
		pDVar7 = INVENTORY_GetItemFromBodyLoc(pDVar2, uVar10);
		if (pDVar7 != nullptr)
		{
			D2COMMON_10254_Return0((int)pDVar2, uVar10);
			FOG_Trace("[INVENTORY ERROR] Forced an item into unit's body location!");
		}
		iVar8 = INVENTORY_PlaceItemInBodyLoc(pDVar2, pDVar6, uVar10);
		if (iVar8 == 0)
		{
			FOG_Trace("[INVENTORY ERROR] Unable to insert item into unit's body location!");
			return nullptr;
		}
		INVENTORY_UpdateWeaponGUIDOnInsert(pDVar2, pDVar6);
		sub_6FB5B1D0((int)pDVar5, 0);
		bVar1 = *(uint8_t*)(local_20 + 3);
		if ((bVar1 == 0) || (bVar1 == 1))
		{
			sub_6FB5C2E0(pDVar5, (uint32_t)bVar1);
		}
		sub_6FB5C080(pDVar5);
		if (pDVar5 == pDStack_24)
		{
			uVar4 = ITEMS_GetWeaponClassId(pDVar6);
			uVar3 = uVar4;
			if ((local_18.nBodyloc != 4) && (uVar3 = byte_6FBBC208, local_18.nBodyloc == 5))
			{
				byte_6FBBC20A = uVar4;
			}
			byte_6FBBC208 = uVar3;
			iVar8 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 8);
			pDVar2 = pDStack_1c;
			if (iVar8 == 0)
			{
				INVENTORY_SetCursorItem(pDStack_1c, nullptr);
				pDVar7 = INVENTORY_GetCursorItem(pDVar2);
				sub_6FB575B0(pDVar7);
			}
		}
		sub_6FB2B8E0(pDVar6, pDVar5, 0, 0);
		sub_6FB2B360(pDVar5);
		sub_6FB2B360(pDVar5);
	}
	else
	{
		if (pDVar5 != pDStack_24)
		{
			return nullptr;
		}
		if (local_18.nAnimMode == 2)
		{
			pDVar6 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
			if (pDVar6 != nullptr)
			{
				pDVar7 = INVENTORY_RemoveItemFromInventory(pDVar2, pDVar6);
				D2_ASSERT(pDVar7 == pDVar6);
				uVar10 = pDVar6->dwUnitType;
				if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
				{
					iVar8 = pDVar6->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar6->pDynamicPath == nullptr)
				{
					iVar8 = 0;
				}
				else
				{
					iVar8 = PATH_GetXPosition(pDVar6->pDynamicPath);
				}
				D2COMMON_10267_Return((int)pDVar2, iVar8);
				uVar10 = pDVar6->dwUnitType;
				if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
				{
					uVar10 = pDVar6->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar6->pDynamicPath == nullptr)
				{
					uVar10 = 0;
				}
				else
				{
					uVar10 = PATH_GetXPosition(pDVar6->pDynamicPath);
				}
				sub_6FB01B10(uVar10, 0);
				if (pDVar5->dwUnitType == 0)
				{
					INVENTORY_GetLeftHandWeapon(pDVar5->pInventory);
				}
				iVar8 = ITEMS_CheckItemFlag(pDVar6, 0x100, __LINE__, __FILE__);
				if (iVar8 == 0)
				{
					STATLIST_ExpireUnitStatlist(pDVar5, pDVar6);
				}
				sub_6FB26BE0(pDVar6->dwUnitId, pDVar6->dwUnitType);
			}
			sub_6FB01B20();
			pDVar6 = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
			D2_ASSERT(local_18.nAnimMode == 2);
			UNITS_SetXForStaticUnit(pDVar6, (uint32_t)local_18.nX);
			UNITS_SetYForStaticUnit(pDVar6, (uint32_t)local_18.nY);
			iVar8 = INVENTORY_PlaceItemInSocket(pDVar2, pDVar6, 2);
			if (iVar8 == 0)
			{
				FOG_DisplayHalt("[RECREATE ITEM BELT] Could not add to inventory!",
				    __FILE__, __LINE__);
				exit(-1);
			}
			uVar10 = pDVar6->dwUnitType;
			if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
			{
				iVar8 = pDVar6->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar6->pDynamicPath == nullptr)
			{
				iVar8 = 0;
			}
			else
			{
				iVar8 = PATH_GetXPosition(pDVar6->pDynamicPath);
			}
			iVar8 = INVENTORY_PlaceItemInBeltSlot(pDVar2, pDVar6, iVar8);
			if (iVar8 == 0)
			{
				sub_6FAAD420((int32_t)extraout_ECX);
				CLIENT_SetExitToMenu(0);
				sub_6FAA9430(1);
				sub_6FAAB240();
				FOG_Trace("Unable to insert item in belt at %d in %s.  Quitting game", __LINE__, __FILE__);
			}
			iVar8 = ITEMS_IsCharmUsable(pDVar6, pDVar5);
			if (iVar8 != 0)
			{
				sub_6FB2B8E0(pDVar6, pDVar5, 0, 0);
			}
			uVar10 = pDVar6->dwUnitType;
			if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
			{
				uVar10 = pDVar6->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar6->pDynamicPath == nullptr)
			{
				uVar10 = 0;
			}
			else
			{
				uVar10 = PATH_GetXPosition(pDVar6->pDynamicPath);
			}
			sub_6FB01B10(uVar10, 1);
			sub_6FB238D0();
			iVar8 = ITEMS_CheckIfFlagIsSet(local_18.dwFlags, 0x400);
			if (iVar8 != 0)
			{
				sub_6FB5BA70(pDVar6, 0x46, 2, 0, 0, 0, 0, 0);
			}
			goto LAB_6fb2fa32;
		}
		if (local_18.nAnimMode != 4)
		{
			return nullptr;
		}
		sub_6FB01B20();
		pDVar5 = sub_6FB269F0(*(uint32_t*)(a1 + 4), 4);
		if (pDVar5 != nullptr)
		{
			sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
		}
		pDVar6 = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
		UNITS_SetXForStaticUnit(pDVar6, (uint32_t)local_18.nX);
		UNITS_SetYForStaticUnit(pDVar6, (uint32_t)local_18.nY);
		INVENTORY_SetCursorItem(pDVar2, pDVar6);
		pDVar5 = INVENTORY_GetCursorItem(pDVar2);
		sub_6FB575B0(pDVar5);
	}
	sub_6FB238D0();
LAB_6fb2fa32:
	if ((pDVar6 != nullptr) &&
	    (pStatList = STATLIST_GetStatListFromUnitAndState(pDVar6, 0x36),
	        pStatList != nullptr))
	{
		STATES_ToggleState(pDVar6, 0x36, 0);
		D2Common_10474(pDVar6, pStatList);
		STATLIST_FreeStatList(pStatList);
		UNITS_UpdateAnimRateAndVelocity(pDVar6, __FILE__, __LINE__);
	}
	return (int*)pDVar6;
}

//D2Client.0x6FB2FA80
void __fastcall sub_6FB2FA80(int a1)
{
	D2UnitStrc* pUnit;
	D2StatListStrc* pStatList;

	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pUnit != nullptr)
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, 0x36);
		if (pStatList != nullptr)
		{
			STATES_ToggleState(pUnit, 0x36, 0);
			D2Common_10474(pUnit, pStatList);
			STATLIST_FreeStatList(pStatList);
			UNITS_UpdateAnimRateAndVelocity(pUnit, __FILE__, __LINE__);
		}
	}
}

//D2Client.0x6FB2FAD0
void __fastcall sub_6FB2FAD0(D2UnitStrc* hItem)
{
	D2StatListStrc* pStatList;

	D2_ASSERT(hItem != nullptr);
	pStatList = STATLIST_GetStatListFromUnitAndState(hItem, 0x36);
	if (pStatList != nullptr)
	{
		STATES_ToggleState(hItem, 0x36, 0);
		D2Common_10474(hItem, pStatList);
		STATLIST_FreeStatList(pStatList);
		UNITS_UpdateAnimRateAndVelocity(hItem, __FILE__, __LINE__);
	}
}

//D2Client.0x6FB2FB30
void __fastcall sub_6FB2FB30(D2UnitStrc* pUnit)
{
	D2StatListStrc* pDVar1;
	uint32_t nUnitGUID;
	D2StatListStrc* pStatList;
	void* pfStatRemove;
	uint32_t nUnitType;

	pDVar1 = STATLIST_GetStatListFromUnitAndState(pUnit, 0x36);
	if (pDVar1 == nullptr)
	{
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
		pDVar1 = STATLIST_AllocStatList(nullptr, 2, 0xc, nUnitType, nUnitGUID);
		STATLIST_SetState(pDVar1, 0x36);
		STATLIST_SetStatRemoveCallback(pStatList, (StatListRemoveCallback)(pfStatRemove));
		return;
	}
	STATLIST_SetState(pDVar1, 0x36);
}

//D2Client.0x6FB2FB80
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB2FB80(uint32_t a1)
{
	D2UnitStrc* in_ECX;
	int in_EDX;

	STATES_ToggleState(in_ECX, in_EDX, 0);
}

//D2Client.0x6FB2FB90
uint32_t __fastcall sub_6FB2FB90(D2UnitStrc* pUnit2)
{
	D2StatListStrc* pDVar1;
	D2UnitStrc* pUnit;
	int iVar2;

	pDVar1 = STATLIST_GetStatListFromUnitAndFlag(pUnit2, 2);
	if (pDVar1 != nullptr)
	{
		return 1;
	}
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		iVar2 = STATES_CheckState(pUnit, 0x36);
		if (iVar2 != 0)
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FB2FBC0
void __fastcall sub_6FB2FBC0(int a1)
{
	uint32_t uVar1;
	D2InventoryStrc* pInventory;
	uint8_t bVar2;
	uint8_t bVar3;
	D2UnitStrc* pItem;
	D2UnitStrc* pUnit;
	D2UnitStrc* pDVar4;
	int a3;
	int a4;

	pItem = sub_6FB269F0(*(uint32_t*)(a1 + 6), 4);
	if ((pItem != nullptr) &&
	    (pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1)),
	        pUnit != nullptr))
	{
		bVar2 = UNITS_GetItemComponentId(pUnit, pItem);
		uVar1 = pItem->dwAnimMode;
		if (*(int*)(a1 + 10) == 0x100)
		{
			ITEMS_SetItemFlag(pItem, 0x100, *(int*)(a1 + 0xe));
			sub_6FB5DA40(pUnit);
			if (pUnit->pInventory != nullptr)
			{
				INVENTORY_UpdateWeaponGUIDOnRemoval(pUnit->pInventory, pItem);
				if (pUnit->dwUnitType == 0)
				{
					INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
				}
				ITEMS_CheckItemFlag(pItem, 0x100, __LINE__, __FILE__);
				STATLIST_ExpireUnitStatlist(pUnit, pItem);
				sub_6FB5C2E0(pUnit, (uint32_t)bVar2);
			}
			sub_6FB5C080(pUnit);
			a4 = 1;
			a3 = 1;
		}
		else
		{
			if (*(int*)(a1 + 10) != 0x200)
			{
				return;
			}
			ITEMS_SetItemFlag(pItem, 0x100, 0);
			pInventory = pUnit->pInventory;
			if (((pInventory != nullptr) &&
			        (bVar3 = ITEMS_GetBodyLocation(pItem), bVar3 != 0xb)) &&
			    (bVar3 != 0xc))
			{
				INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pItem);
				sub_6FB5C2E0(pUnit, (uint32_t)bVar2);
				if ((uVar1 == 1) &&
				    (pDVar4 = STATLIST_GetOwner(pItem, nullptr), pDVar4 == nullptr))
				{
					sub_6FB2B8E0(pItem, pUnit, 0, 1);
				}
				INVENTORY_UpdateWeaponGUIDOnInsert(pInventory, pItem);
			}
			a4 = 0;
			a3 = 0;
		}
		ITEMS_UpdateSets(pUnit, pItem, a3, a4);
		sub_6FB2B360(pUnit);
		return;
	}
}

//D2Client.0x6FB2FD00
void __fastcall sub_6FB2FD00(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pUnit;
	D2ItemSaveStrc local_18;

	ITEMS_GetCompactItemDataFromBitstream((uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 2) - 0xd, 0, &local_18);
	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 8));
	if (pDVar1 != nullptr)
	{
		sub_6FB26BE0(*(uint32_t*)(a1 + 4), 4);
		pUnit = sub_6FB2C1D0(a1, &local_18, 0, 0, 0);
		D2_ASSERT(pUnit != nullptr);
		STATLIST_SetUnitStat(pUnit, 0x46, 1, 0);
		pInventory = pDVar1->pInventory;
		INVENTORY_SetCursorItem(pInventory, pUnit);
		pDVar1 = INVENTORY_GetCursorItem(pInventory);
		sub_6FB575B0(pDVar1);
	}
}

//D2Client.0x6FB2FDA0
void __fastcall sub_6FB2FDA0(D2UnitStrc* pUnit)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pItem_00;
	int iVar2;
	D2UnitStrc* pItem_01;

	if ((pUnit != nullptr) &&
	    (pInventory = pUnit->pInventory, pInventory != nullptr))
	{
		pDVar1 = INVENTORY_GetFirstItem(pInventory);
		while (pItem = pDVar1, pItem != nullptr)
		{
			pDVar1 = INVENTORY_GetNextItem(pItem);
			pItem_00 = INVENTORY_UnitIsItem(pItem);
			D2_ASSERT(pItem_00 != nullptr);
			iVar2 = INVENTORY_GetItemNodePage(pItem);
			if ((iVar2 == 3) ||
			    ((iVar2 = INVENTORY_GetItemNodePage(pItem), iVar2 == 1 &&
			                                                    (iVar2 = ITEMS_IsCharmUsable(pItem_00, pUnit), iVar2 != 0))))
			{
				sub_6FB5DA40(pUnit);
				INVENTORY_UpdateWeaponGUIDOnRemoval(pInventory, pItem_00);
				pItem_01 = INVENTORY_RemoveItemFromInventory(pInventory, pItem_00);
				D2_ASSERT(pItem_01 != nullptr);
				D2_ASSERT(pItem_01 == pItem_00);
				iVar2 = INVENTORY_GetItemNodePage(pItem);
				if (iVar2 == 3)
				{
					iVar2 = INVENTORY_GetBodyLocFromEquippedItem(pInventory, pItem_00);
					D2COMMON_10254_Return0((int)pInventory, iVar2);
				}
				ITEMS_UpdateSets(pUnit, pItem_01, 1, 1);
				if (pUnit->dwUnitType == 0)
				{
					INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
				}
				iVar2 = ITEMS_CheckItemFlag(pItem_01, 0x100, __LINE__, __FILE__);
				if (iVar2 == 0)
				{
					STATLIST_ExpireUnitStatlist(pUnit, pItem_01);
				}
				sub_6FB2B360(pUnit);
			}
		}
		INVENTORY_RemoveAllItems(pInventory);
	}
}
