#include "Unit/UnitGfx.h"

#include "Engine/Gfx.h"
#include "Game/Scroll.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"
#include "Unit/PlrSkills.h"

//D2Client.0x6FB4DAC0
void __fastcall sub_6FB4DAC0(D2UnitStrc* pUnit)
{
	D2GfxDataStrc* pDVar1;

	pDVar1 = sub_6FB592C0();
	pUnit->pGfxData = pDVar1;
	if (pDVar1 != nullptr)
	{
		switch (pUnit->dwUnitType)
		{
		case 0:
		case 2:
			sub_6FB5C080(pUnit);
			return;
		case 1:
			sub_6FB5C080(pUnit);
			return;
		case 3:
		case 4:
			return;
		default:
			FOG_DisplayHalt("[UnitInitGFX] Invalid unit type!\n",
			    __FILE__, __LINE__);
			exit(-1);
		}
	}
	FOG_DisplayAssert("ptUnit->uGfx.hGFX", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB4DB40
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB4DB40(D2UnitStrc* pUnit2, uint32_t a2, int a3)
{
	int iVar1;
	int iVar2;
	D2ObjectsTxt* pDVar3;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	uint32_t extraout_var;
	uint32_t uVar4;
	bool bVar5;
	int iStack_14;
	int iStack_10;
	int iStack_c;
	int iStack_8;
	uint32_t local_4;

	iVar2 = a3;
	local_4 = a2;
	if (a3 == 0)
	{
		if (pUnit2 != nullptr)
		{
			a3 = pUnit2->dwFlagEx >> 0x12 & 1;
			if (a3 != 0)
			{
				return;
			}
			goto LAB_6fb4db71;
		}
	}
	else
	{
	LAB_6fb4db71:
		if ((((pUnit2 != nullptr) && (pUnit2->dwUnitType == 0)) &&
		        (pUnit2->dwAnimMode == 0x11)) &&
		    (iVar1 = STATES_CheckState(pUnit2, 7), iVar1 == 0))
		{
			return;
		}
		if (((iVar2 == 0) && (pUnit2 != nullptr)) &&
		    ((0 < (int)pUnit2->dwUnitType && ((int)pUnit2->dwUnitType < 3))))
		{
			iVar2 = STATES_CheckState(pUnit2, 0x8f);
			if (iVar2 != 0)
			{
				return;
			}
			iVar2 = STATES_CheckState(pUnit2, 0x92);
			if (iVar2 != 0)
			{
				return;
			}
		}
	}
	iVar2 = D2GFX_CheckPerspective();
	iStack_10 = iVar2;
	iVar1 = UNITS_GetPrecisionX(pUnit2);
	iStack_8 = iVar1;
	iStack_c = UNITS_GetPrecisionY(pUnit2);
	if ((iVar2 != 0) && (iVar2 = SCALE_CheckPerspectivePosition(iVar1, iStack_c), iVar2 == 0))
	{
		return;
	}
	if (pUnit2 == nullptr)
		goto switchD_6fb4dc08_caseD_2;
	switch (pUnit2->dwUnitType)
	{
	case 0:
		pUnit = CUNIT_GetPlayer();
		if (pUnit != pUnit2)
		{
			if ((pUnit2->dwAnimMode == 0) || (pUnit2->dwAnimMode == 0x11))
				goto switchD_6fb4dc08_caseD_2;
			goto LAB_6fb4dcdb;
		}
		pUnit2->dwFlagEx = pUnit2->dwFlagEx | 0x80;
		break;
	case 1:
		if ((pUnit2->dwAnimMode != 0) && (pUnit2->dwAnimMode != 0xc))
			goto switchD_6fb4dc08_caseD_3;
	default:
	switchD_6fb4dc08_caseD_2:
	LAB_6fb4dc41:
		sub_6FB448E0((int)pUnit2, 0x80, 1);
		break;
	case 3:
	case 4:
	switchD_6fb4dc08_caseD_3:
		pUnit = CUNIT_GetPlayer();
	LAB_6fb4dcdb:
		if (pUnit == nullptr)
			goto switchD_6fb4dc08_caseD_2;
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			iVar2 = DUNGEON_GetLevelIdFromRoom(pRoom);
			iVar2 = DRLG_GetLOSDrawFromLevelId(iVar2);
			if (iVar2 == 0)
				goto switchD_6fb4dc08_caseD_2;
		}
		iVar2 = UNITS_TestCollisionWithUnit(pUnit, pUnit2, 2);
		if (iVar2 != 0)
		{
			sub_6FB448E0((int)pUnit2, 0x80, 0);
			return;
		}
		goto LAB_6fb4dc41;
	}
	uVar4 = 6;
	if (pUnit2 != nullptr)
	{
		uVar4 = pUnit2->dwUnitType;
	}
	if (iStack_10 == 0)
	{
		a3 = UNITS_GetClientCoordX(pUnit2);
		iStack_14 = UNITS_GetClientCoordY(pUnit2);
	}
	else
	{
		iVar2 = 0;
		if ((pUnit2 != nullptr) && (pUnit2->dwUnitType == 2))
		{
			pDVar3 = DATATBLS_GetObjectsTxtRecord(pUnit2->dwClassId);
			iVar1 = UNITS_GetAnimOrSeqMode(pUnit2);
			if (pDVar3->nOrderFlag[iVar1] == 2)
			{
				iVar2 = 1;
			}
		}
		SCALE_ScalePerspectivePosition(iStack_8, iStack_c, 0x60, &a3, &iStack_14, iVar2);
		iVar2 = sub_6FAB5890();
		a3 = a3 + iVar2;
		iVar2 = sub_6FAB58A0();
		iStack_14 = iStack_14 + iVar2;
		a2 = local_4;
	}
	if (uVar4 == 0)
	{
		sub_6FB4B980(pUnit2, a2);
		iVar2 = sub_6FB5A720(pUnit2, (DrawMode)(a2), a3, iStack_14, 0, 1);
		if ((iVar2 != 0) && (pUnit2 != nullptr))
		{
			pUnit2->dwFlags = pUnit2->dwFlags | 0x10000000;
		}
		sub_6FB4BA60(pUnit2, a2);
	}
	else if (uVar4 == 1)
	{
		bVar5 = sub_6FB40CE0((int*)pUnit2);
		sub_6FB4B980(pUnit2, a2);
		iVar2 = sub_6FB5A720(pUnit2, (DrawMode)(a2), a3, iStack_14, (uint32_t)(D2C_ZEXT(bVar5) != 0), 1);
		if ((iVar2 != 0) && (pUnit2 != nullptr))
		{
			pUnit2->dwFlags = pUnit2->dwFlags | 0x10000000;
		}
		sub_6FB4BA60(pUnit2, a2);
	}
	else
	{
		if (uVar4 == 3)
		{
			if ((((pUnit2 == nullptr) || (iVar2 = pUnit2->dwClassId, iVar2 < 0)) ||
			        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar2)) ||
			    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 == 0))
				goto LAB_6fb4de8b;
			iVar2 = sub_6FB5A720(pUnit2, (DrawMode)(a2), *(short*)(iVar2 + 0xa2) + a3,
			    (int)*(short*)(iVar2 + 0xa4) + iStack_14 + *(short*)(iVar2 + 0xa6), 0, 1);
			bVar5 = iVar2 == 0;
		}
		else
		{
			iVar2 = sub_6FB5A720(pUnit2, (DrawMode)(a2), a3, iStack_14, 0, 1);
			if (iVar2 == 0)
				goto LAB_6fb4de8b;
			bVar5 = pUnit2 == nullptr;
		}
		if (!bVar5)
		{
			pUnit2->dwFlags = pUnit2->dwFlags | 0x10000000;
		}
	}
LAB_6fb4de8b:
	if (iStack_10 != 0)
	{
		SCALE_SetDefaultFactorPerspectiveFactor();
	}
}
