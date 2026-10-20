#include "Unit/UnitMode.h"

#include "Core/MemoryPartitions.h"
#include "Draw/DFloor.h"
#include "Engine/Gfx.h"
#include "Engine/GfxUtil.h"
#include "Engine/Particle.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Roster.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Skills/Skills.h"
#include "Skills/SkillsMon.h"
#include "Skills/SkillsPal.h"
#include "UI/SkillDesc.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"
#include "Unit/Object.h"
#include "Unit/Player.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB70F38
uint8_t byte_6FB70F38 = 0xFF;
//D2Client.0x6FBBC250
uint32_t dword_6FBBC250;
//D2Client.0x6FBBD25C
int32_t dword_6FBBD25C;
//D2Client.0x6FBBD260
int32_t dword_6FBBD260;
//D2Client.0x6FBBD470
uint32_t dword_6FBBD470;

//D2Client.0x6FB4DEC0
void __fastcall sub_6FB4DEC0(int hUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iStack_8;
	uint32_t uStack_4;

	D2_ASSERT(hUnit);
	pDynamicPath = *(D2DynamicPathStrc**)(hUnit + 0x2c);
	D2_ASSERT(pDynamicPath != nullptr);
	pDVar1 = PATH_GetTargetUnit(pDynamicPath);
	if (pDVar1 != nullptr)
	{
		PATH_GetTargetTypeAndGUID(pDynamicPath, &iStack_8, &uStack_4);
		pDVar1 = sub_6FB269F0(uStack_4, iStack_8);
		pDVar2 = PATH_GetTargetUnit(pDynamicPath);
		if (pDVar1 != pDVar2)
		{
			PATH_SetTargetUnit(pDynamicPath, nullptr);
		}
	}
}

//D2Client.0x6FB4DF50
void __fastcall sub_6FB4DF50(int a1)
{
	PATH_RecacheRoomIfNeeded(*(D2DynamicPathStrc**)(a1 + 0x2c));
}

//D2Client.0x6FB4DF60
int32_t __fastcall sub_6FB4DF60(D2UnitStrc* pUnit, int a2, int a3)
{
	D2DynamicPathStrc* pDynamicPath;

	pDynamicPath = pUnit->pDynamicPath;
	D2COMMON_10170_PathSetTargetPos(pDynamicPath, a2, a3);
	return D2Common_10142(pDynamicPath, pUnit, pUnit->dwFlags >> 0x15 & 1);
}

//D2Client.0x6FB4DF90
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB4DF90(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, int a4, int a5, int a6)
{
	int* piVar1;
	bool bVar2;
	bool bVar3;
	int iVar4;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar5;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t uVar6;
	uint32_t extraout_ECX_01;
	uint32_t uVar7;
	int iVar8;
	uint32_t uVar9;
	uint16_t uVar10;
	int32_t nY2;
	int32_t DStack_c;

	uVar7 = a3;
	iVar8 = 0;
	if ((uint16_t)a2 == 0)
	{
		return;
	}
	uVar10 = (uint16_t)a3;
	if (uVar10 == 0)
	{
		return;
	}
	iVar4 = sub_6FB29550((int*)pUnit);
	if (iVar4 != 0)
	{
		return;
	}
	pUnit->nLastClickX = (uint16_t)a2;
	pUnit->nLastClickY = uVar10;
	pRoom = UNITS_GetRoom(pUnit);
	uVar9 = pUnit->dwUnitType;
	if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
	{
		a3 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		a3 = 0;
	}
	else
	{
		a3 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar9 = pUnit->dwUnitType;
	if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
	{
		DStack_c = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_c + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_c + 2)) = 0;
	}
	else
	{
		DStack_c = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	if (a4 == 1)
	{
		iVar8 = 10;
	}
	else if (a4 != 2)
	{
		pDVar5 = CUNIT_GetPlayer();
		if (pUnit == pDVar5)
		{
			if (pUnit->dwAnimMode == 1)
			{
				iVar8 = sub_6FAA9AD0();
				iVar8 = (iVar8 + 0x32U >> 7) + 3;
			}
			else if (pUnit->dwAnimMode == 3)
			{
				iVar8 = sub_6FAA9AD0();
				iVar8 = (iVar8 + 0x32U >> 7) + 7;
			}
			else
			{
				iVar8 = sub_6FAA9AD0();
				iVar8 = (iVar8 + 0x32U >> 7) + 5;
			}
		}
		else
		{
			iVar8 = 0xf;
			if (pUnit->dwUnitType == 1)
			{
				switch (pUnit->dwAnimMode)
				{
				case 3:
				case 4:
				case 5:
					iVar8 = 5;
					break;
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 0xb:
					iVar8 = 7;
				}
			}
		}
	}
	uVar9 = (uint32_t)(uint16_t)a2;
	iVar4 = uVar9 - a3;
	if (iVar4 < 0)
	{
		iVar4 = -iVar4;
	}
	bVar2 = iVar8 < iVar4;
	nY2 = (int32_t)(uVar7 & 0xffff);
	iVar4 = (int)nY2 - (int)DStack_c;
	if (iVar4 < 0)
	{
		iVar4 = -iVar4;
	}
	if ((iVar8 < iVar4) || (bVar2))
	{
		if ((a4 == 0) &&
		    (((0 < a5 &&
		          (iVar8 = PATH_ComputeSquaredDistance(a3, (int)DStack_c, uVar9, (int)nY2), iVar8 < 100)) &&
		        (iVar4 = PATH_ComputeSquaredDistance(a3, (int)DStack_c, a5, a6),
		            iVar4 < iVar8))))
		{
			bVar2 = false;
			goto LAB_6fb4e16c;
		}
	}
	else
	{
	LAB_6fb4e16c:
		iVar8 = UNITS_GetClientCoordX(pUnit);
		a6 = UNITS_GetClientCoordY(pUnit);
		a4 = (int)nY2;
		a5 = uVar9;
		DUNGEON_GameSubtileToClientCoords(&a5, &a4);
		if ((((uVar9 == a3) || (nY2 == DStack_c)) ||
		        ((bVar3 = sub_6FB5E030(pUnit, iVar8, a6), D2C_ZEXT(bVar3) != 0 ||
		                                                      (bVar3 = sub_6FB5E030(pUnit, a5, a4), D2C_ZEXT(bVar3) != 0)))) &&
		    (!bVar2))
		{
			return;
		}
	}
	if (pRoom != nullptr)
	{
		iVar8 = (pRoom->tCoords).nSubtileX;
		if ((((int)uVar9 < iVar8) || ((pRoom->tCoords).nSubtileWidth + iVar8 <= (int)uVar9)) ||
		    ((iVar8 = (pRoom->tCoords).nSubtileY, (int)nY2 < iVar8 ||
		                                              ((pRoom->tCoords).nSubtileHeight + iVar8 <= (int)nY2))))
		{
			a5 = 0;
			a4 = 0;
			DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, (D2ActiveRoomStrc***)&a5, &a4);
			uVar7 = 0;
			if (a4 != 0)
			{
				do
				{
					piVar1 = *(int**)(a5 + uVar7 * 4);
					if ((((piVar1 != nullptr) && (*piVar1 <= (int)uVar9)) &&
					        ((int)uVar9 < piVar1[2] + *piVar1)) &&
					    ((piVar1[1] <= (int)nY2 && ((int)nY2 < piVar1[3] + piVar1[1]))))
					{
						pRoom = *(D2ActiveRoomStrc**)(a5 + uVar7 * 4);
						goto LAB_6fb4e25e;
					}
					uVar7 = uVar7 + 1;
				} while (uVar7 < (uint32_t)a4);
			}
		}
		else
		{
		LAB_6fb4e25e:
			if (pRoom != nullptr)
				goto LAB_6fb4e27a;
		}
	}
	pRoom = DUNGEON_FindRoomBySubtileCoordinates(ghAct, uVar9, (int)nY2);
	if (pRoom == nullptr)
	{
		return;
	}
LAB_6fb4e27a:
	pDVar5 = CUNIT_GetPlayer();
	uVar7 = pUnit->dwUnitType;
	if (pUnit != pDVar5)
	{
		if (uVar7 != 0)
		{
			D2Common_10230(pUnit->pDynamicPath, (int)pUnit, pRoom, uVar9, uVar10);
			return;
		}
		sub_6FB4B640(pUnit, pRoom, uVar9, nY2);
		return;
	}
	uVar6 = extraout_ECX;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
	{
		uVar10 = (pUnit->pDynamicPath->tTargetCoord).X;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		uVar10 = 0;
	}
	else
	{
		iVar8 = PATH_GetYPosition(pUnit->pDynamicPath);
		uVar10 = (uint16_t)iVar8;
		uVar6 = extraout_ECX_00;
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 != 2) && (((int)uVar7 < 4 || (5 < (int)uVar7))))
	{
		if (pUnit->pDynamicPath == nullptr)
		{
			sub_6FAAD9B0(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x5f), 0, uVar10);
			return;
		}
		iVar8 = PATH_GetXPosition(pUnit->pDynamicPath);
		sub_6FAAD9B0(CONCAT31((int32_t)((uint32_t)extraout_ECX_01 >> 8), 0x5f), (short)iVar8, uVar10);
		return;
	}
	sub_6FAAD9B0(CONCAT31((int32_t)((uint32_t)pUnit->pDynamicPath >> 8), 0x5f),
	    (short)pUnit->pDynamicPath->dwClientCoordY, uVar10);
}

//D2Client.0x6FB4E360
void __fastcall sub_6FB4E360(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, int a4)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	int32_t DVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uStack_1c;
	uint32_t uStack_18;
	uint32_t uStack_10;
	uint32_t uStack_c;
	uint32_t uStack_8;

	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar3 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	iVar3 = a2 - iVar3;
	if (iVar3 < 0)
	{
		iVar3 = -iVar3;
	}
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
	iVar7 = a3 - (int)DVar4;
	if (iVar7 < 0)
	{
		iVar7 = -iVar7;
	}
	uVar1 = pUnit->dwUnitType;
	if (((uVar1 == 1) &&
	        ((((iVar5 = pUnit->dwClassId, iVar5 < 0 ||
	                                          (iVar2 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar2 + 0xa80) <= iVar5)) ||
	              (iVar5 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar5 * 0x1a8), iVar5 < 0)) ||
	            (((*(int*)(iVar2 + 0xa98) <= iVar5 ||
	                  (iVar5 = *(int*)(iVar2 + 0xa90) + iVar5 * 0x134, iVar5 == 0)) ||
	                (((uint32_t) * (uint8_t*)(iVar5 + 0xf0) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 8)) == 0)))))) ||
	    (iVar7 < 2 && iVar3 < 2))
	{
		D2COMMON_10208_PathSetPathingFlag(pUnit->pDynamicPath, 0);
	}
	else
	{
		uStack_18 = a3;
		uVar8 = 1;
		uStack_1c = a2;
		if (uVar1 == 0)
		{
			pDVar6 = CUNIT_GetPlayer();
			if (pUnit != pDVar6)
			{
				if (a4 != 0)
				{
					sub_6FB4DF90(pUnit, a2, a3, 2, 0, 0);
					return;
				}
				uVar8 = 0x17;
			}
		}
		else if (uVar1 == 1)
		{
			uStack_10 = 1;
		}
		uStack_c = 100;
		uStack_8 = 0xf;
		switch (pUnit->dwUnitType)
		{
		case 0:
			sub_6FB49090(uVar8, pUnit, (D2SkillStrc*)(&uStack_1c), 0);
			return;
		case 1:
			sub_6FB42D40(uVar8, pUnit, &uStack_1c);
			return;
		case 2:
			sub_6FB47660(uVar8, pUnit, (int*)&uStack_1c);
			return;
		case 4:
			sub_6FB2AD10(uVar8, pUnit, uStack_1c, uStack_18);
			return;
		}
	}
}

//D2Client.0x6FB4E580
uint32_t __fastcall sub_6FB4E580(D2UnitStrc* pUnit2, int a2, uint32_t a3)
{
	D2DynamicPathStrc* pDynamicPath;
	D2UnitStrc* pUnit;
	int iVar1;

	pDynamicPath = pUnit2->pDynamicPath;
	pUnit = sub_6FB269F0(a3, a2);
	dword_6FBBD470 = dword_6FBBD470 | a3;
	PATH_SetTargetUnit(pDynamicPath, pUnit);
	if (pUnit == nullptr)
	{
		return 0;
	}
	iVar1 = D2Common_10142(pDynamicPath, pUnit2, 0);
	return iVar1;
}

//D2Client.0x6FB4E5D0
bool __fastcall sub_6FB4E5D0(D2UnitStrc* hUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iStack_8;
	uint32_t uStack_4;

	D2_ASSERT(hUnit != nullptr);
	pDynamicPath = hUnit->pDynamicPath;
	D2_ASSERT(pDynamicPath != nullptr);
	pDVar1 = PATH_GetTargetUnit(pDynamicPath);
	if (pDVar1 != nullptr)
	{
		PATH_GetTargetTypeAndGUID(pDynamicPath, &iStack_8, &uStack_4);
		pDVar1 = sub_6FB269F0(uStack_4, iStack_8);
		pDVar2 = PATH_GetTargetUnit(pDynamicPath);
		if (pDVar1 != pDVar2)
		{
			PATH_SetTargetUnit(pDynamicPath, nullptr);
		}
	}
	iVar3 = STATES_CheckState(hUnit, 0xd);
	if (iVar3 != 0)
	{
		sub_6FACAE70(hUnit);
	}
	iVar3 = STATES_CheckState(hUnit, 0x16);
	if (iVar3 != 0)
	{
		sub_6FAC7D60(hUnit);
	}
	iVar3 = sub_6FAABFE0();
	iVar3 = D2Common_10226(hUnit, iVar3);
	return (bool)('\x01' - (iVar3 != 0));
}

//D2Client.0x6FB4E6A0
void __fastcall sub_6FB4E6A0(D2UnitStrc* pUnit)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;

	pDVar1 = CUNIT_GetPlayer();
	if (((pDVar1 == pUnit) || (pUnit == nullptr)) ||
	    ((pUnit->dwFlags >> 0x17 & 1) == 0))
	{
		STATLIST_UpdateStatListsExpiration(pUnit, 0);
		sub_6FB5FE00((int*)pUnit);
		if (pUnit == nullptr)
		{
			uVar3 = 0xffffffff;
			uVar2 = 6;
			uVar4 = 0;
		}
		else
		{
			uVar3 = pUnit->dwUnitId;
			uVar2 = pUnit->dwUnitType;
			uVar4 = pUnit->dwFlags >> 0x15 & 1;
		}
		sub_6FB57E80(pUnit);
		switch (pUnit->dwUnitType)
		{
		case 0:
			sub_6FB48B60(pUnit);
			break;
		case 1:
			sub_6FB41E90(pUnit);
			break;
		case 2:
			sub_6FB46D50(pUnit);
			break;
		case 3:
			sub_6FB3D6D0(pUnit);
			break;
		case 4:
			sub_6FB2AC30(pUnit);
		}
		if (uVar4 == 0)
		{
			pDVar1 = sub_6FB269F0(uVar3, uVar2);
		}
		else
		{
			pDVar1 = sub_6FB26A60(uVar3, uVar2);
		}
		if (pDVar1 != nullptr)
		{
			sub_6FAB5610((int)pDVar1);
			return;
		}
	}
	else
	{
		if ((pUnit->dwFlagEx >> 5 & 1) != 0)
		{
			sub_6FAADA40(0x4b, pUnit->dwUnitType, pUnit->dwUnitId);
			pUnit->dwFlags = pUnit->dwFlags & 0xff7fffff;
			pUnit->dwFlagEx = pUnit->dwFlagEx & 0xffffffdf;
		}
		if ((pUnit->dwFlags >> 0x15 & 1) != 0)
		{
			sub_6FB26C70(pUnit->dwUnitId, pUnit->dwUnitType);
			return;
		}
	}
}

//D2Client.0x6FB4E7E0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB4E7E0(uint32_t a1, uint32_t a2)
{
	D2UnitStrc* pUnit;
	D2UnitStrc* pDVar1;
	int32_t nY;
	int iVar2;
	D2SkillStrc* pDVar3;
	DWORD DVar4;
	int32_t nY_00;
	uint32_t extraout_ECX;
	uint32_t uVar5;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t extraout_ECX_03;
	uint32_t extraout_ECX_04;
	uint32_t uVar6;
	uint32_t* puVar7;
	char* pcVar8;
	int nLine;
	uint32_t auStack_1c[7];

	pUnit = CUNIT_GetPlayer();
	uVar6 = a1 & 0xffff;
	pDVar1 = sub_6FB269F0(a2, uVar6);
	if (pDVar1 == nullptr)
	{
		return;
	}
	uVar5 = extraout_ECX;
	switch (uVar6)
	{
	case 0:
		uVar5 = pDVar1->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			nY_00 = (*(int32_t*)&pDVar1->pDynamicPath->tTargetCoord);
		}
		else if (pDVar1->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY_00 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY_00 + 2)) = 0;
		}
		else
		{
			nY_00 = (int32_t)PATH_GetYPosition(pDVar1->pDynamicPath);
		}
		uVar5 = pDVar1->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			iVar2 = pDVar1->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar1->pDynamicPath == nullptr)
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = PATH_GetXPosition(pDVar1->pDynamicPath);
		}
		UNITS_UpdateDirectionAndSpeed(pUnit, iVar2, (int)nY_00);
		uVar5 = extraout_ECX_03;
		break;
	case 1:
		DVar4 = GetTickCount();
		if (DVar4 - pDVar1->dwTickCount < 200)
		{
			return;
		}
		pDVar1->dwTickCount = DVar4;
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_02 >> 8), 0x13), uVar6, a2);
		return;
	case 2:
		PATH_SetTargetUnit(pUnit->pDynamicPath, nullptr);
		uVar5 = pDVar1->dwFlags >> 2 & 1;
		if (uVar5 == 0)
			break;
		uVar5 = pDVar1->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			nY = (*(int32_t*)&pDVar1->pDynamicPath->tTargetCoord);
		}
		else if (pDVar1->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
		}
		else
		{
			nY = (int32_t)PATH_GetYPosition(pDVar1->pDynamicPath);
		}
		uVar5 = pDVar1->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			iVar2 = pDVar1->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar1->pDynamicPath == nullptr)
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = PATH_GetXPosition(pDVar1->pDynamicPath);
		}
		UNITS_UpdateDirectionAndSpeed(pUnit, iVar2, (int)nY);
		nLine = 0x213;
		puVar7 = auStack_1c;
		for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar7 = 0;
			puVar7 = puVar7 + 1;
		}
		pcVar8 = __FILE__;
		pDVar3 = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 1);
		auStack_1c[0] = SKILLS_GetSkillIdFromSkill(pDVar3, pcVar8, nLine);
		if (pDVar1->dwClassId == 0x194)
		{
			if (pDVar1->dwAnimMode == 0)
			{
				pDVar1 = INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
				if ((pDVar1 == nullptr) ||
				    (uVar5 = ITEMS_GetBaseCode(pDVar1), uVar5 != 0x20326671))
				{
				LAB_6fb4e997:
					sub_6FB514E0(pUnit, 0x13);
					return;
				}
				iVar2 = 0x21e;
			LAB_6fb4e905:
				pcVar8 = __FILE__;
				pDVar3 = SKILLS_GetSkillById(pUnit, 0, 0xffffffff);
				auStack_1c[0] = SKILLS_GetSkillIdFromSkill(pDVar3, pcVar8, iVar2);
			}
		}
		else if (pDVar1->dwClassId == 0x178)
		{
			if (pDVar1->dwAnimMode == 0)
			{
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x13), 2, a2);
				return;
			}
			if (pDVar1->dwAnimMode == 2)
			{
				pDVar1 = INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
				if ((pDVar1 == nullptr) ||
				    (uVar5 = ITEMS_GetBaseCode(pDVar1), uVar5 != 0x20686668))
					goto LAB_6fb4e997;
				iVar2 = 0x234;
				goto LAB_6fb4e905;
			}
		}
		auStack_1c[1] = 0xffffffff;
		auStack_1c[2] = 2;
		auStack_1c[3] = a2;
		sub_6FABD2A0(pUnit, auStack_1c);
		uVar5 = extraout_ECX_01;
		break;
	case 4:
		uVar6 = sub_6FB23230(1);
		sub_6FAADA70(CONCAT31((int32_t)((uint32_t)extraout_ECX_04 >> 8), 0x16), 4, a2, uVar6 & 0xff);
		return;
	}
	sub_6FAADA40(D2C_ZEXT(0x13), uVar6, a2);
}

//D2Client.0x6FB4EA90
void __fastcall sub_6FB4EA90(uint32_t a1, D2UnitStrc* pUnit, uint32_t a3, uint32_t a4, uint32_t a5)
{
	D2SkillStrc* pDVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	uint32_t* puVar5;
	char* pcVar6;
	uint16_t nLayer;
	uint32_t auStack_1c[7];

	pDVar1 = UNITS_GetUsedSkill(pUnit);
	if ((((pDVar1 != nullptr) &&
	         (iVar2 = SKILLS_GetSkillIdFromSkill(pDVar1, __FILE__, __LINE__), -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    ((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar2 != 0 &&
	                                                                                       (((uint8_t)((uint8_t*)&gdwBitMasks)[0x1c] & *(uint8_t*)(iVar2 + 7)) == 0))))
	{
		if (pUnit == nullptr)
		{
			return;
		}
		if ((pUnit->dwAnimMode != 1) && (pUnit->dwAnimMode != 5))
		{
			return;
		}
	}
	puVar5 = auStack_1c;
	for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
	auStack_1c[0] = a3;
	auStack_1c[1] = a4;
	switch (a1)
	{
	case 1:
		uVar4 = 1;
		goto LAB_6fb4eb42;
	case 2:
		uVar4 = 0;
		break;
	case 3:
		uVar4 = 0x17;
	LAB_6fb4eb42:
		if (((pUnit != nullptr) && (pUnit->dwUnitType == 0)) &&
		    ((pUnit->pPlayerData != nullptr &&
		        (pUnit->pPlayerData->unk0xA8[0x2b] == 0x13))))
		{
			return;
		}
		break;
	case 4:
		uVar4 = 0x18;
		break;
	case 5:
	case 8:
		iVar2 = 0x371;
		pcVar6 = __FILE__;
		pDVar1 = UNITS_GetLeftSkill(pUnit);
		auStack_1c[0] = SKILLS_GetSkillIdFromSkill(pDVar1, pcVar6, iVar2);
		pDVar1 = UNITS_GetLeftSkill(pUnit);
		goto LAB_6fb4ec19;
	case 6:
	case 7:
	case 9:
	case 10:
		iVar2 = 0x37b;
		pcVar6 = __FILE__;
		pDVar1 = UNITS_GetLeftSkill(pUnit);
		auStack_1c[0] = SKILLS_GetSkillIdFromSkill(pDVar1, pcVar6, iVar2);
		pDVar1 = UNITS_GetLeftSkill(pUnit);
		goto LAB_6fb4ec55;
	default:
		FOG_DisplayAssert("0", __FILE__, __LINE__);
		exit(-1);
	case 0xc:
	case 0xf:
		iVar2 = 899;
		pcVar6 = __FILE__;
		pDVar1 = UNITS_GetRightSkill(pUnit);
		auStack_1c[0] = SKILLS_GetSkillIdFromSkill(pDVar1, pcVar6, iVar2);
		pDVar1 = UNITS_GetRightSkill(pUnit);
	LAB_6fb4ec19:
		auStack_1c[1] = SKILLS_GetOwnerGUIDFromSkill(pDVar1);
		auStack_1c[2] = a3;
		auStack_1c[3] = a4;
		uVar4 = 0x15;
		break;
	case 0xd:
	case 0xe:
	case 0x10:
	case 0x11:
		iVar2 = 0x38d;
		pcVar6 = __FILE__;
		pDVar1 = UNITS_GetRightSkill(pUnit);
		auStack_1c[0] = SKILLS_GetSkillIdFromSkill(pDVar1, pcVar6, iVar2);
		pDVar1 = UNITS_GetRightSkill(pUnit);
	LAB_6fb4ec55:
		auStack_1c[1] = SKILLS_GetOwnerGUIDFromSkill(pDVar1);
		uVar4 = 0x16;
		auStack_1c[2] = a3;
		auStack_1c[3] = a4;
		break;
	case 0x13:
		if ((((a3 == 4) && (pDVar3 = sub_6FB269F0(a4, 4), pDVar3 != nullptr)) &&
		        (pDVar3->dwUnitType == 4)) &&
		    ((pDVar3->dwFlags >> 1 & 1) == 0))
		{
			return;
		}
		uVar4 = 2;
	}
	switch (pUnit->dwUnitType)
	{
	case 0:
		iVar2 = sub_6FB49090(uVar4, pUnit, (D2SkillStrc*)(auStack_1c), 0);
		if (iVar2 == 0)
			goto LAB_6fb4ed3a;
		break;
	case 1:
		sub_6FB42D40(uVar4, pUnit, auStack_1c);
		break;
	case 2:
		sub_6FB47660(uVar4, pUnit, (int*)auStack_1c);
		break;
	case 4:
		sub_6FB2AD10(uVar4, pUnit, auStack_1c[0], auStack_1c[1]);
	}
	switch (a1)
	{
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 0xc:
	case 0xd:
	case 0xe:
	case 0xf:
	case 0x10:
	case 0x11:
		nLayer = 0;
		iVar2 = STATLIST_GetUnitBaseStat(pUnit, 0x148, 0);
		STATLIST_SetUnitStat(pUnit, 0x148, iVar2 + 1, nLayer);
	}
	if (a1 != 0x13)
	{
		switch (a1)
		{
		default:
			sub_6FAAD9B0(a1, (short)a3, (short)a4);
			break;
		case 2:
		case 4:
		case 6:
		case 7:
		case 9:
		case 10:
		case 0xd:
		case 0xe:
		case 0x10:
		case 0x11:
			sub_6FAADA40(a1, a3, a4);
		}
	}
LAB_6fb4ed3a:
	if ((pUnit->dwUnitType == 0) && (pUnit->pPlayerData != nullptr))
	{
		pUnit->pPlayerData->unk0xA8[0x2a] = 0;
		pUnit->pPlayerData->unk0xA8[0x2b] = 0;
		pUnit->pPlayerData->unk0xA8[0x2c] = 0;
		pUnit->pPlayerData->unk0xA8[0x2d] = 0;
	}
}

//D2Client.0x6FB4EE00
uint32_t __fastcall sub_6FB4EE00(uint32_t a1, D2UnitStrc* pUnit, uint32_t* a3, uint32_t a4)
{
	uint32_t uVar1;

	switch (pUnit->dwUnitType)
	{
	case 0:
		uVar1 = sub_6FB49090(a1, pUnit, (D2SkillStrc*)(a3), a4);
		return uVar1;
	case 1:
		sub_6FB42D40(a1, pUnit, a3);
		return 1;
	case 2:
		sub_6FB47660(a1, pUnit, (int*)a3);
		return 1;
	case 4:
		sub_6FB2AD10(a1, pUnit, *a3, a3[1]);
	}
	return 1;
}

//D2Client.0x6FB4EE70
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB4EE70(D2UnitStrc* pUnit)
{
	D2PlayerDataStrc* pDVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	bool bVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	D2SkillStrc* pSkill;
	uint32_t extraout_var_02;
	uint32_t extraout_var_03;

	if ((((pUnit != nullptr) && (pUnit->dwUnitType == 0)) &&
	        (pDVar1 = pUnit->pPlayerData, pDVar1 != nullptr)) &&
	    (pDVar1->unk0xA8[0x2a] != 0))
	{
		uVar2 = pDVar1->unk0xA8[0x2b];
		uVar3 = pDVar1->unk0xA8[0x2c];
		uVar4 = pDVar1->unk0xA8[0x2d];
		pDVar6 = sub_6FB269F0(uVar4, uVar3);
		if ((pUnit->dwUnitType == 0) && (pUnit->pPlayerData != nullptr))
		{
			pUnit->pPlayerData->unk0xA8[0x2a] = 0;
			pUnit->pPlayerData->unk0xA8[0x2b] = 0;
			pUnit->pPlayerData->unk0xA8[0x2c] = 0;
			pUnit->pPlayerData->unk0xA8[0x2d] = 0;
		}
		if ((uVar2 == 0x13) && (uVar3 == 5))
		{
			iVar7 = sub_6FAABF90();
			sub_6FAABFB0(iVar7 + 500);
		}
		if (pDVar6 == nullptr)
		{
			return;
		}
		if (uVar2 == 0)
		{
			return;
		}
		if (uVar3 == 0)
		{
			iVar7 = sub_6FB29550((int*)pDVar6);
			if (iVar7 != 0)
			{
				iVar7 = sub_6FAB1200(pUnit->dwUnitId, uVar4);
				if (iVar7 != 0)
				{
					sub_6FB4EA90(uVar2, pUnit, 0, uVar4, 0);
					return;
				}
			LAB_6fb4f0b4:
				sub_6FAB5A90(nullptr);
				return;
			}
			if ((pDVar6->dwFlags >> 1 & 1) == 0)
				goto LAB_6fb4f0b4;
			bVar5 = sub_6FB4F120(pUnit, pDVar6, uVar2);
			if (D2C_ZEXT(bVar5) != 0)
			{
				sub_6FB4F1D0(pUnit, uVar2, 0, uVar4);
				return;
			}
		}
		else if (uVar3 == 1)
		{
			iVar7 = sub_6FB29550((int*)pDVar6);
			if (iVar7 == 0)
			{
				if ((pDVar6->dwFlags >> 1 & 1) == 0)
				{
					sub_6FAB5A90(nullptr);
					return;
				}
			}
			else
			{
				switch (uVar2)
				{
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 0xb:
					pSkill = UNITS_GetLeftSkill(pUnit);
					break;
				case 0xc:
				case 0xd:
				case 0xe:
				case 0xf:
				case 0x10:
				case 0x11:
				case 0x12:
					pSkill = UNITS_GetRightSkill(pUnit);
					break;
				default:
					goto switchD_6fb4efc7_default;
				}
				if (pSkill == nullptr)
				{
				switchD_6fb4efc7_default:
					sub_6FAB5A90(nullptr);
					return;
				}
				iVar7 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
				iVar7 = sub_6FB14AE0(iVar7);
				if (iVar7 == 0)
				{
					sub_6FAB5A90(nullptr);
					return;
				}
				if (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar7 + 7)) == 0)
				{
					sub_6FAB5A90(nullptr);
					return;
				}
			}
			bVar5 = sub_6FB4F120(pUnit, pDVar6, uVar2);
			if (D2C_ZEXT(bVar5) != 0)
			{
				sub_6FB4F1D0(pUnit, uVar2, 1, uVar4);
				return;
			}
		}
		else if (uVar3 == 2)
		{
			bVar5 = sub_6FB448C0((int)pDVar6, 2);
			if (D2C_ZEXT(bVar5) == 0)
			{
				sub_6FAB5A90(nullptr);
				return;
			}
			bVar5 = sub_6FB4F120(pUnit, pDVar6, uVar2);
			if (D2C_ZEXT(bVar5) != 0)
			{
				sub_6FB4F1D0(pUnit, uVar2, 2, uVar4);
				return;
			}
		}
		else
		{
			bVar5 = sub_6FB448C0((int)pDVar6, 2);
			if (D2C_ZEXT(bVar5) == 0)
			{
				sub_6FAB5A90(nullptr);
				return;
			}
		}
		sub_6FB4EA90(uVar2, pUnit, uVar3, uVar4, 0);
	}
}

//D2Client.0x6FB4F120
// TODO: decompilation needs review (extraout)
bool __fastcall sub_6FB4F120(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3)
{
	bool bVar1;
	D2SkillStrc* pSkill;
	D2SkillsTxt* pDVar2;
	uint32_t extraout_var;
	int iVar3;
	D2UnitStrc* pDStack_4;

	pDStack_4 = pUnit;
	if (a3 == 6)
	{
		pSkill = UNITS_GetLeftSkill(pUnit);
	}
	else
	{
		if (a3 != 0xd)
			goto LAB_6fb4f17c;
		pSkill = UNITS_GetRightSkill(pUnit);
	}
	if (pSkill != nullptr)
	{
		pDVar2 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
		if ((pDVar2 != nullptr) && (pDVar2->wSrvDoFunc == 0x13))
		{
			bVar1 = sub_6FB498A0(pSkill, pUnit2, (int*)(&pDStack_4), &a3);
			return D2C_ZEXT(bVar1) != 0;
		}
	}
LAB_6fb4f17c:
	if ((pUnit2 != nullptr) && (pUnit2->dwUnitType == 2))
	{
		iVar3 = UNITS_IsObjectInInteractRange(pUnit, pUnit2);
		if (iVar3 != 0)
		{
			iVar3 = UNITS_TestCollisionBetweenInteractingUnits(pUnit, pUnit2, 0x804);
			if (iVar3 == 0)
			{
				return false;
			}
		}
		return true;
	}
	iVar3 = UNITS_IsInMovingModeEx(pUnit2);
	iVar3 = UNITS_IsInMeleeRange(pUnit, pUnit2, iVar3);
	return (bool)('\x01' - (iVar3 != 0));
}

//D2Client.0x6FB4F1D0
void __fastcall sub_6FB4F1D0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, uint32_t a4)
{
	uint32_t uVar1;
	uint32_t uVar2;

	uVar1 = sub_6FAA8B50();
	uVar2 = 4;
	if ((uVar1 & 8) == 0)
	{
		uVar2 = 2;
	}
	sub_6FB4EA90(uVar2, pUnit, a3, a4, 0);
	if (((pUnit != nullptr) && (pUnit->dwUnitType == 0)) &&
	    (pUnit->pPlayerData != nullptr))
	{
		pUnit->pPlayerData->unk0xA8[0x2a] = 1;
		pUnit->pPlayerData->unk0xA8[0x2b] = a2;
		pUnit->pPlayerData->unk0xA8[0x2c] = a3;
		pUnit->pPlayerData->unk0xA8[0x2d] = a4;
	}
}

//D2Client.0x6FB4F240
void __fastcall sub_6FB4F240(D2UnitStrc* pUnit, int a2)
{
	bool bVar1;
	uint32_t uVar2;
	int* piVar3;
	int iVar4;
	bool bVar5;

	uVar2 = 6;
	if (pUnit != nullptr)
	{
		uVar2 = pUnit->dwUnitType;
	}
	bVar1 = false;
	if (uVar2 == 0)
	{
		if ((a2 != 0) && (a2 != 4))
		{
			bVar5 = a2 == 0x13;
		LAB_6fb4f274:
			if (!bVar5)
				goto LAB_6fb4f27b;
		}
	}
	else
	{
		if (uVar2 != 1)
			goto LAB_6fb4f27b;
		if ((a2 != 0) && (a2 != 3))
		{
			bVar5 = a2 == 0xd;
			goto LAB_6fb4f274;
		}
	}
	bVar1 = true;
LAB_6fb4f27b:
	sub_6FB4F2D0();
	if (bVar1)
	{
		uVar2 = pUnit->dwLastHitClass & 0xf0;
		if ((uVar2 != 0) && ((pUnit->dwLastHitClass & 0xf) != 0))
		{
			iVar4 = -1;
			piVar3 = (int*)("Q");
			do
			{
				if (piVar3[-1] == uVar2)
				{
					iVar4 = *piVar3;
				}
				piVar3 = piVar3 + 2;
			} while ((int)piVar3 < (int)&byte_6FB70F38);
			if (iVar4 != -1)
			{
				sub_6FB5BA70(pUnit, iVar4, 2, 0, 0, 0, 0, 0);
			}
		}
	}
}

//D2Client.0x6FB4F2D0
void __cdecl sub_6FB4F2D0()
{
	uint32_t* puVar1;
	uint32_t uVar2;
	uint32_t* puVar3;
	uint32_t uVar4;
	void* local_14;
	uint32_t uStack_10;
	uint8_t* puStack_c;
	uint32_t local_8;

	puStack_c = &byte_6FB70F38;
	uStack_10 = 0x6fb61938;
	if ((dword_6FBBC244 != 0) || (dword_6FBBC248 != 0))
	{
		puVar1 = (uint32_t*)((dword_6FBBC244 >> 0x10 ^ dword_6FBBC244 & 0xffff) << 0x10 |
		                     dword_6FBBC244 & 0xffff);
		puVar3 = (uint32_t*)((dword_6FBBC248 >> 0x10 ^ dword_6FBBC248 & 0xffff) << 0x10 |
		                     dword_6FBBC248 & 0xffff);
		dword_6FBBC244 = 0;
		dword_6FBBC248 = 0;
		if ((gnGameType == 2) || (gnGameType == 3))
		{
			if (puVar1 == nullptr)
			{
				uVar2 = 0;
			}
			else
			{
				uVar2 = *puVar1;
			}
			if (puVar3 == nullptr)
			{
				uVar4 = 0;
			}
			else
			{
				uVar4 = *puVar3;
			}
			local_8 = 0xffffffff;
			uVar4 = (uVar4 >> 0x10 ^ uVar4 & 0xffff) << 0x10 | uVar4 & 0xffff;
			sub_6FAADA40(D2C_ZEXT(100),
			    (uVar2 >> 0x10 ^ uVar2 & 0xffff) << 0x10 | uVar2 & 0xffff, uVar4);
		}
	}
}

//D2Client.0x6FB4F410
void __fastcall sub_6FB4F410(D2UnitStrc* pUnit, int* a2)
{
	int iVar1;

	MEMORY_Nop();
	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags & 0xffffffbf;
	}
	iVar1 = UNITS_ChangeAnimMode(pUnit, (int)a2);
	if (iVar1 != 0)
	{
		sub_6FB5C080(pUnit);
		sub_6FB4F240(pUnit, (int)a2);
		sub_6FB50D20(pUnit, a2, 0);
	}
}

//D2Client.0x6FB4F460
void __fastcall sub_6FB4F460(D2UnitStrc* pUnit, int a2)
{
	int iVar1;

	MEMORY_Nop();
	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags & 0xffffffbf;
	}
	iVar1 = UNITS_ChangeAnimMode(pUnit, a2);
	if (iVar1 != 0)
	{
		sub_6FB5C080(pUnit);
		return;
	}
}

//D2Client.0x6FB4F4A0
void __cdecl sub_6FB4F4A0()
{
	int iVar1;
	uint32_t* puVar2;

	puVar2 = &dword_6FBBC250;
	for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	dword_6FBBD250 = 0;
	byte_6FBBD254 = 0;
	dword_6FBBD258 = 0x5a;
	dword_6FBBD25C = 0;
	dword_6FBBD260 = 0;
}
