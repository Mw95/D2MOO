#include "Skills/SkillsBar.h"

#include "Draw/DLightMap.h"
#include "Engine/Gfx.h"
#include "Engine/Particle.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Scroll.h"
#include "Game/View.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Skills/SkillsAma.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB6E9C4
uint32_t dword_6FB6E9C4 = 0x1B;
//D2Client.0x6FB6E9C8
uint32_t dword_6FB6E9C8 = 0xFFFFFEF2;
//D2Client.0x6FB6E9CC
uint32_t dword_6FB6E9CC = 0x210E;
//D2Client.0x6FB6E9D0
uint32_t tbl_6FB6E9D0[1] = {0x24};
//D2Client.0x6FB6E9E0
uint8_t byte_6FB6E9E0[32] = {7, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0xFB, 0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 5};
//D2Client.0x6FB6EA00
uint8_t byte_6FB6EA00[36] = {0, 0, 0, 0, 5, 0, 0, 0, 7, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0xFB, 0xFF, 0xFF, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 8};
//D2Client.0x6FB6EA28
uint8_t byte_6FB6EA28[24] = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 1, 0, 0, 0, 2};
//D2Client.0x6FB6EA40
uint32_t dword_6FB6EA40;
//D2Client.0x6FB6EA60
uint32_t dword_6FB6EA60[8] = {1, 0xFFFFFFFF, 0, 0, 1, 0xFFFFFFFF, 1, 0xFFFFFFFF};

//D2Client.0x6FAC1310
uint32_t __fastcall sub_6FAC1310(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2ActiveRoomStrc** ppDVar1;
	D2SkillStrc* pDVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t uVar5;
	int32_t DVar6;
	D2ActiveRoomStrc* pDVar7;
	D2UnitStrc* pDVar8;
	D2CoordStrc* pSpawnPoint;
	uint16_t nMask;
	int bAllowNeighborRooms;
	D2ActiveRoomStrc** ppDStack_1c;
	int32_t DStack_18;
	D2UnitStrc* local_14;
	D2CoordStrc DStack_10;
	D2SkillStrc* pDStack_8;
	uint32_t uStack_4;

	local_14 = pUnit;
	pDVar2 = UNITS_GetUsedSkill(pUnit);
	if (pDVar2 == nullptr)
	{
		return 0;
	}
	pDStack_8 = pDVar2;
	pDVar3 = CUNIT_GetPlayer();
	if (pUnit == pDVar3)
	{
		iVar4 = STATES_CheckState(pUnit, 0x36);
		if (iVar4 != 0)
		{
			return 0;
		}
		iVar4 = SKILLS_GetSkillIdFromSkill(pDVar2, __FILE__, __LINE__);
		if ((iVar4 == a2) && (uVar5 = SKILLS_GetFlags(pDVar2), (uVar5 & 1) != 0))
		{
			return 0;
		}
	}
	uVar5 = 6;
	if (pUnit != nullptr)
	{
		uVar5 = pUnit->dwUnitType;
	}
	uStack_4 = (uint32_t)(uVar5 == 1);
	if (uStack_4 == 0)
	{
		iVar4 = sub_6FABA950(pUnit, (int*)&ppDStack_1c, (int*)&DStack_18);
		DVar6 = DStack_18;
		ppDVar1 = ppDStack_1c;
		if (iVar4 == 0)
		{
			return 0;
		}
		if (((((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
		         (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar4 == 0)) ||
		        ((pDVar7 = UNITS_GetRoom(local_14), pDVar7 == nullptr ||
		                                                (pDVar7 = sub_6FAA6150(pDVar7, (int)ppDVar1, (int)DVar6), pDVar7 == nullptr)))) ||
		    ((((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar4 + 5)) == 0 &&
		        (iVar4 = DUNGEON_IsRoomInTown(pDVar7), iVar4 != 0))))
		{
			return 0;
		}
		iVar4 = sub_6FAC16F0(local_14, a2, a3, (int*)(&ppDStack_1c), &DStack_18);
		if (iVar4 == 0)
		{
			return 0;
		}
	}
	else
	{
		pDVar3 = sub_6FB296A0((int)pUnit);
		if (pDVar3 == nullptr)
		{
			iVar4 = sub_6FABA950(pUnit, (int*)&ppDStack_1c, (int*)&DStack_18);
			if (iVar4 == 0)
			{
				return 0;
			}
			SKILLS_SetParam4(pDVar2, -1);
		}
		else
		{
			uVar5 = pDVar3->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				ppDStack_1c = (D2ActiveRoomStrc**)pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				ppDStack_1c = nullptr;
			}
			else
			{
				ppDStack_1c = (D2ActiveRoomStrc**)PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar5 = pDVar3->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				DStack_18 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0;
			}
			else
			{
				DStack_18 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
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
			ppDStack_1c = (D2ActiveRoomStrc**)((int)ppDStack_1c * 2 - iVar4);
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
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
			DStack_18 = (int32_t)((int)DStack_18 * 2 - (int)DVar6);
		}
		bAllowNeighborRooms = 0;
		uVar5 = 0x3c01;
		DStack_10.nX = (int)ppDStack_1c;
		DStack_10.nY = (int)DStack_18;
		iVar4 = UNITS_GetUnitSizeX(pUnit);
		pSpawnPoint = &DStack_10;
		pDVar7 = UNITS_GetRoom(pUnit);
		pDVar7 = COLLISION_GetFreeCoordinates(pDVar7, pSpawnPoint, iVar4, uVar5, bAllowNeighborRooms);
		if (pDVar7 == nullptr)
		{
			return 0;
		}
		ppDStack_1c = (D2ActiveRoomStrc**)DStack_10.nX;
		(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = (uint16_t)DStack_10.nY;
		(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = (*(uint16_t*)((uint8_t*)&DStack_10.nY + 2));
	}
	DVar6 = DStack_18;
	ppDVar1 = ppDStack_1c;
	pDVar7 = UNITS_GetRoom(local_14);
	if (pDVar7 != nullptr)
	{
		iVar4 = (pDVar7->tCoords).nSubtileX;
		if ((((iVar4 <= (int)ppDVar1) && ((int)ppDVar1 < (pDVar7->tCoords).nSubtileWidth + iVar4)) &&
		        (iVar4 = (pDVar7->tCoords).nSubtileY, iVar4 <= (int)DVar6)) &&
		    ((int)DVar6 < (pDVar7->tCoords).nSubtileHeight + iVar4))
			goto LAB_6fac1659;
		DStack_10.nX = 0;
		a3 = 0;
		DUNGEON_GetAdjacentRoomsListFromRoom(pDVar7, (D2ActiveRoomStrc***)&DStack_10, (int*)&a3);
		uVar5 = 0;
		if (a3 != 0)
		{
			do
			{
				pDVar7 = *(D2ActiveRoomStrc**)(DStack_10.nX + uVar5 * 4);
				if (((pDVar7 != nullptr) &&
				        (iVar4 = (pDVar7->tCoords).nSubtileX, iVar4 <= (int)ppDVar1)) &&
				    (((int)ppDVar1 < (pDVar7->tCoords).nSubtileWidth + iVar4 &&
				        ((iVar4 = (pDVar7->tCoords).nSubtileY, iVar4 <= (int)DVar6 &&
				                                                   ((int)DVar6 < (pDVar7->tCoords).nSubtileHeight + iVar4))))))
				{
					pDVar7 = *(D2ActiveRoomStrc**)(DStack_10.nX + uVar5 * 4);
					goto LAB_6fac1659;
				}
				uVar5 = uVar5 + 1;
			} while (uVar5 < a3);
		}
	}
	pDVar7 = nullptr;
LAB_6fac1659:
	pDVar3 = local_14;
	nMask = 0x80;
	iVar4 = PATH_GetUnitCollisionPattern(local_14);
	COLLISION_SetMaskWithPattern(pDVar7, (int)ppDStack_1c, (int)DStack_18, iVar4, nMask);
	pDVar2 = pDStack_8;
	SKILLS_SetParam1(pDStack_8, (int)ppDStack_1c);
	SKILLS_SetParam2(pDVar2, (int)DStack_18);
	if ((uStack_4 != 0) && (pDVar8 = sub_6FB296A0((int)pDVar3), pDVar8 != nullptr))
	{
		SKILLS_SetParam3(pDVar2, pDVar8->dwUnitType);
		SKILLS_SetParam4(pDVar2, pDVar8->dwUnitId);
	}
	SKILLS_SetFlags(pDVar2, 0x1080);
	sub_6FABDD20(pDVar3);
	return 1;
}

//D2Client.0x6FAC16F0
uint32_t __fastcall sub_6FAC16F0(D2UnitStrc* pUnit, int a2, uint32_t a3, int* a4, int* a5)
{
	int* piVar1;
	int iVar2;
	uint32_t uVar3;
	D2ActiveRoomStrc* pDVar4;
	int iVar5;
	uint16_t nMask;
	int iVar6;
	int32_t DStack_28;
	int local_24;
	int iStack_20;
	int iStack_1c;
	D2ActiveRoomStrc** ppDStack_18;
	D2UnitStrc* local_14;
	int iStack_10;
	int iStack_c;
	D2CoordStrc DStack_8;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 != 0))
	{
		uVar3 = pUnit->dwUnitType;
		local_14 = pUnit;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			local_24 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			local_24 = 0;
		}
		else
		{
			local_24 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar3 = pUnit->dwUnitType;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			DStack_28 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_28 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_28 + 2)) = 0;
		}
		else
		{
			DStack_28 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 100), a2, a3);
		piVar1 = a5;
		iStack_c = iVar2;
		uVar3 = UNITS_GetDistanceToCoordinates(pUnit, *a4, *a5);
		if ((int)uVar3 < 2)
		{
			uVar3 = 1;
		}
		if (iVar2 < (int)uVar3)
		{
			iVar6 = *piVar1;
			*a4 = ((*a4 - local_24) * iVar2) / (int)uVar3 + local_24;
			*piVar1 = ((iVar6 - (int)DStack_28) * iVar2) / (int)uVar3 + (int)DStack_28;
		}
		DStack_8.nY = *piVar1;
		iStack_20 = DStack_8.nY - (int)DStack_28;
		if (iStack_20 < -1)
		{
			iStack_20 = -2;
		}
		else if (1 < iStack_20)
		{
			iStack_20 = 2;
		}
		DStack_8.nX = *a4;
		iStack_1c = local_24 - DStack_8.nX;
		if (iStack_1c < -1)
		{
			iStack_1c = -2;
		}
		else if (1 < iStack_1c)
		{
			iStack_1c = 2;
		}
		iStack_10 = 3;
	LAB_6fac1875:
		do
		{
			iVar6 = DStack_8.nY;
			iVar2 = DStack_8.nX;
			pDVar4 = UNITS_GetRoom(pUnit);
			if (pDVar4 == nullptr)
			{
			LAB_6fac1903:
				pDVar4 = nullptr;
			}
			else
			{
				iVar5 = (pDVar4->tCoords).nSubtileX;
				if ((((iVar2 < iVar5) || ((pDVar4->tCoords).nSubtileWidth + iVar5 <= iVar2)) ||
				        (iVar5 = (pDVar4->tCoords).nSubtileY, iVar6 < iVar5)) ||
				    ((pDVar4->tCoords).nSubtileHeight + iVar5 <= iVar6))
				{
					ppDStack_18 = nullptr;
					a3 = 0;
					DUNGEON_GetAdjacentRoomsListFromRoom(pDVar4, &ppDStack_18, (int*)&a3);
					uVar3 = 0;
					if (a3 != 0)
					{
						do
						{
							pDVar4 = ppDStack_18[uVar3];
							if (((pDVar4 != nullptr) &&
							        (iVar5 = (pDVar4->tCoords).nSubtileX, iVar5 <= iVar2)) &&
							    ((pUnit = local_14, iVar2 < (pDVar4->tCoords).nSubtileWidth + iVar5 &&
							                            ((iVar5 = (pDVar4->tCoords).nSubtileY, iVar5 <= iVar6 &&
							                                                                       (iVar6 < (pDVar4->tCoords).nSubtileHeight + iVar5))))))
							{
								pDVar4 = ppDStack_18[uVar3];
								goto LAB_6fac1905;
							}
							uVar3 = uVar3 + 1;
						} while (uVar3 < a3);
					}
					goto LAB_6fac1903;
				}
			}
		LAB_6fac1905:
			iVar6 = 1;
			uVar3 = 0x1c09;
			iVar2 = UNITS_GetUnitSizeX(pUnit);
			pDVar4 = COLLISION_GetFreeCoordinates(pDVar4, &DStack_8, iVar2, uVar3, iVar6);
			iVar6 = DStack_8.nY;
			iVar2 = DStack_8.nX;
			if (pDVar4 != nullptr)
			{
				nMask = 0x1c09;
				iVar5 = PATH_GetUnitCollisionPattern(pUnit);
				iVar5 = COLLISION_CheckAnyCollisionWithPattern(pDVar4, iVar2, iVar6, iVar5, nMask);
				if (((iVar5 == 0) &&
				        (iVar5 = D2Common_11025(local_24, (int)DStack_28, iVar2, iVar6, pDVar4, 0x804), iVar5 != 0)) &&
				    (uVar3 = UNITS_GetDistanceToCoordinates(pUnit, iVar2, iVar6), (int)uVar3 <= iStack_c))
				{
					*a4 = iVar2;
					*a5 = iVar6;
					return 1;
				}
			}
			iStack_10 = iStack_10 + -1;
			if (iStack_10 == 2)
			{
				DStack_8.nX = *a4 + iStack_20;
				DStack_8.nY = *a5 + iStack_1c;
				goto LAB_6fac1875;
			}
			if (iStack_10 == 1)
			{
				DStack_8.nX = *a4 - iStack_20;
				DStack_8.nY = *a5 - iStack_1c;
				goto LAB_6fac1875;
			}
		} while (iStack_10 != 0);
		if (pUnit->dwUnitType == 0)
		{
			sub_6FB514E0(pUnit, 0x13);
		}
	}
	return 0;
}

//D2Client.0x6FAC1A20
uint32_t __fastcall sub_6FAC1A20(D2UnitStrc* pUnit, D2SkillStrc* pSkill)
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	int nY;
	uint32_t uVar2;

	pDynamicPath = pUnit->pDynamicPath;
	if (pDynamicPath != nullptr)
	{
		iVar1 = SKILLS_GetParam1(pSkill);
		nY = SKILLS_GetParam2(pSkill);
		if ((iVar1 != 0) && (nY != 0))
		{
			SKILLS_SetFlags(pSkill, 0x1101);
			PATH_SetMoveTestCollisionMask(pDynamicPath, 0);
			PATH_SetFootprintCollisionMask(pDynamicPath, 0);
			D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar1, nY);
			PATH_SetType(pDynamicPath, 9);
			iVar1 = pUnit->dwClassId;
			if (pUnit->dwUnitType == 1)
			{
				if (iVar1 < 0)
				{
					return 0;
				}
				if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar1)
				{
					return 0;
				}
				iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar1 * 0x1a8;
				if (iVar1 == 0)
				{
					return 0;
				}
				uVar2 = (uint32_t) * (short*)(iVar1 + 0x34);
			}
			else
			{
				if ((iVar1 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8) <= iVar1))
				{
					iVar1 = 0;
				}
				else
				{
					iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + iVar1 * 0xc4;
				}
				uVar2 = (uint32_t) * (uint8_t*)(iVar1 + 0x41);
			}
			PATH_SetVelocity(pDynamicPath, uVar2 << 8, __FILE__, __LINE__);
			D2Common_10142(pDynamicPath, pUnit, 0);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC1B30
void __fastcall sub_6FAC1B30(D2UnitStrc* pUnit, D2SkillStrc* pSkill)
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	int nY;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int* piVar5;

	if ((pSkill != nullptr) &&
	    (pDynamicPath = pUnit->pDynamicPath, pDynamicPath != nullptr))
	{
		iVar1 = SKILLS_GetParam1(pSkill);
		nY = SKILLS_GetParam2(pSkill);
		iVar2 = PATH_GetVelocity(pDynamicPath);
		if (iVar2 >> 8 != 0)
		{
			uVar3 = UNITS_GetDistanceToCoordinates(pUnit, iVar1, nY);
			if ((int)uVar3 < 1)
			{
				uVar3 = 1;
			}
			uVar4 = (int)(uVar3 << 0x10) / ((iVar2 >> 8) << 0xc);
			if (1 < (int)uVar4)
			{
				uVar4 = uVar4 - 1;
			}
			iVar1 = 0;
			piVar5 = (int*)(&dword_6FB6E9C4);
			do
			{
				if ((int)uVar3 < *piVar5)
					break;
				piVar5 = piVar5 + 3;
				iVar1 = iVar1 + 1;
			} while ((int)piVar5 < (int)&tbl_6FB6E9D0);
			iVar1 = (&dword_6FB6E9C8)[iVar1 * 3] * uVar3 + (&dword_6FB6E9CC)[iVar1 * 3];
			if (iVar1 < 500)
			{
				iVar1 = 500;
			}
			sub_6FB5FB10((int)pUnit);
			sub_6FB5FD00((int)pUnit, 0, 0, -iVar1, 0);
			sub_6FB60080((int)pUnit, 0, uVar4);
		}
	}
}

//D2Client.0x6FAC1C00
void __fastcall sub_6FAC1C00(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	D2SkillStrc* pSkill;
	char* pcVar3;
	int32_t DVar4;
	D2ActiveRoomStrc* pRoom;
	int iVar5;
	char* nX;
	int32_t nY;
	uint16_t nMask;

	iVar2 = PATH_GetFootprintCollisionMask(pUnit->pDynamicPath);
	iVar5 = (-(uint32_t)(pUnit->dwUnitType != 1) & 0xffffff80) + 0x100;
	if (iVar2 != iVar5)
	{
		pSkill = UNITS_GetUsedSkill(pUnit);
		if (pSkill == nullptr)
		{
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				pcVar3 = (char*)pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				pcVar3 = nullptr;
			}
			else
			{
				pcVar3 = (char*)PATH_GetXPosition(pUnit->pDynamicPath);
			}
		}
		else
		{
			pcVar3 = (char*)SKILLS_GetParam1(pSkill);
		}
		if (pSkill == nullptr)
		{
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
		}
		else
		{
			DVar4 = (int32_t)SKILLS_GetParam2(pSkill);
		}
		iVar2 = PATH_GetUnitCollisionPattern(pUnit);
		nMask = (uint16_t)iVar5;
		nX = pcVar3;
		nY = DVar4;
		pRoom = UNITS_GetRoom(pUnit);
		COLLISION_ResetMaskWithPattern(pRoom, (int)nX, (int)nY, iVar2, nMask);
		sub_6FB26DD0(pUnit, pcVar3, (char*)DVar4, 0);
		sub_6FAC1CE0(pUnit, (int)pcVar3, DVar4);
	}
}

//D2Client.0x6FAC1CE0
void __fastcall sub_6FAC1CE0(D2UnitStrc* pUnit, int a2, int a3)
{
	D2DynamicPathStrc* pDynamicPath;
	D2ActiveRoomStrc* pRoom;
	int iVar1;
	uint16_t uVar2;
	uint32_t local_4;

	if (pUnit == nullptr)
	{
		local_4 = 6;
	}
	else
	{
		local_4 = pUnit->dwUnitType;
	}
	pDynamicPath = pUnit->pDynamicPath;
	pRoom = UNITS_GetRoom(pUnit);
	if ((pDynamicPath != nullptr) && (pRoom != nullptr))
	{
		if (local_4 == 1)
		{
			if ((a2 != 0) && (a3 != 0))
			{
				uVar2 = 0x100;
				iVar1 = PATH_GetUnitCollisionPattern(pUnit);
				COLLISION_ResetMaskWithPattern(pRoom, a2, a3, iVar1, uVar2);
			}
			PATH_SetFootprintCollisionMask(pDynamicPath, 0x100);
			PATH_SetMoveTestCollisionMask(pDynamicPath, 0x3c01);
			iVar1 = 2;
		}
		else
		{
			if ((a2 != 0) && (a3 != 0))
			{
				uVar2 = 0x80;
				iVar1 = PATH_GetUnitCollisionPattern(pUnit);
				COLLISION_ResetMaskWithPattern(pRoom, a2, a3, iVar1, uVar2);
			}
			PATH_SetFootprintCollisionMask(pDynamicPath, 0x80);
			PATH_SetMoveTestCollisionMask(pDynamicPath, 0x1c09);
			iVar1 = 7;
		}
		PATH_SetType(pDynamicPath, iVar1);
		iVar1 = sub_6FB29550((int*)pUnit);
		if (iVar1 != 0)
		{
			PATH_SetUnitDeadCollision(pUnit, 0);
		}
	}
}

//D2Client.0x6FAC1DC0
uint32_t __fastcall sub_6FAC1DC0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	uint32_t uVar1;
	int iVar2;

	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2);
	if (pSkill == nullptr)
	{
		return 0;
	}
	uVar1 = SKILLS_GetFlags(pSkill);
	if ((uVar1 & 0x100) != 0)
	{
		iVar2 = sub_6FAC1E40(pUnit, pSkill, 1);
		if (iVar2 == 0)
		{
			return 0;
		}
	}
	if ((char)uVar1 < '\0')
	{
		sub_6FAC1A20(pUnit, pSkill);
		sub_6FAC1B30(pUnit, pSkill);
		return 1;
	}
	if ((pUnit == nullptr) || (pUnit->dwUnitType != 1))
	{
		SKILLS_SetFlags(pSkill, 0x1000);
	}
	return 1;
}

//D2Client.0x6FAC1E40
uint32_t __fastcall sub_6FAC1E40(D2UnitStrc* pUnit, D2SkillStrc* pSkill, int a3)
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	int32_t nY;
	int iVar2;
	int32_t DVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	int32_t DVar6;
	D2ActiveRoomStrc* pDVar7;
	uint32_t uVar8;
	int iVar9;
	bool bVar10;
	float fVar11;
	float fVar12;

	iVar1 = SKILLS_GetParam1(pSkill);
	nY = (int32_t)SKILLS_GetParam2(pSkill);
	iVar2 = sub_6FB5FC40((int)pUnit);
	uVar8 = 6;
	if (pUnit != nullptr)
	{
		uVar8 = pUnit->dwUnitType;
	}
	bVar10 = uVar8 != 1;
	if ((((bVar10) || (pUnit == nullptr)) || (pUnit->dwUnitType != 1)) ||
	    (iVar9 = pUnit->dwClassId, iVar9 < 0))
	{
	LAB_6fac1ed5:
		iVar9 = -1;
	}
	else
	{
		if ((iVar9 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
		    (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar9 * 0x1a8, iVar4 != 0))
		{
			iVar9 = (int)*(short*)(iVar4 + 2);
		}
		if ((iVar9 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar9))
			goto LAB_6fac1ed5;
	}
	if (iVar2 == 0)
	{
	LAB_6fac1fb5:
		sub_6FAC1CE0(pUnit, iVar1, nY);
		sub_6FB5FC80((int)pUnit, 0, 0, 0);
		if (a3 != 0)
		{
			sub_6FB5BA70(pUnit, 0x50, 2, 0, 0, 0, 0, 0);
		}
		iVar2 = 0;
		fVar12 = 0.0;
		fVar11 = 0.0;
		if (bVar10)
		{
			iVar1 = sub_6FB4FCE0(pUnit, 1);
			sub_6FB55820(iVar1, pUnit, fVar11, fVar12, iVar2);
			sub_6FB55820(0x9d5, pUnit, 0.0, 0.0, 0);
		}
		else
		{
			iVar4 = sub_6FB4FCE0(pUnit, 1);
			sub_6FB55820(iVar4, pUnit, fVar11, fVar12, iVar2);
			if ((iVar9 == 0x4e) &&
			    (pDynamicPath = pUnit->pDynamicPath, pDynamicPath != nullptr))
			{
				iVar2 = SKILLS_GetParam3(pSkill);
				uVar8 = SKILLS_GetParam4(pSkill);
				pDVar5 = sub_6FB269F0(uVar8, iVar2);
				if (pDVar5 != nullptr)
				{
					SKILLS_SetFlags(pSkill, 1);
					UNITS_SetAnimationFrame(pUnit, 0xc);
					pUnit->dwFrameCountPrecise = (pUnit->dwFrameCountPrecise & 0xffffff00U) + 0x100;
					D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
					PATH_RecacheRoomIfNeeded(pDynamicPath);
					PATH_SetNewDistance(pDynamicPath, 5);
					PATH_SetStepNum(pDynamicPath, 1);
					PATH_SetTargetUnit(pDynamicPath, nullptr);
					uVar8 = pDVar5->dwUnitType;
					if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
					{
						iVar2 = pDVar5->pDynamicPath->dwClientCoordY;
					}
					else if (pDVar5->pDynamicPath == nullptr)
					{
						iVar2 = 0;
					}
					else
					{
						iVar2 = PATH_GetXPosition(pDVar5->pDynamicPath);
					}
					uVar8 = pDVar5->dwUnitType;
					iVar1 = iVar1 * 3 + iVar2 * -2;
					if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
					{
						DVar6 = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
					}
					else if (pDVar5->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
					}
					else
					{
						DVar6 = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
					}
					iVar9 = (int)nY * 3 + (int)DVar6 * -2;
					iVar2 = iVar9;
					pDVar7 = UNITS_GetRoom(pUnit);
					pDVar7 = sub_6FAA6150(pDVar7, iVar1, iVar2);
					if ((pDVar7 == nullptr) ||
					    (iVar2 = DUNGEON_IsRoomInTown(pDVar7), iVar2 == 0))
					{
						D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar1, iVar9);
						PATH_SetType(pDynamicPath, 0xb);
						D2COMMON_10190_PATH_SetDistance(pDynamicPath, 5);
						D2Common_10142(pDynamicPath, pUnit, 0);
						return 1;
					}
				}
			}
		}
		return 1;
	}
	uVar8 = pUnit->dwUnitType;
	if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
	{
		iVar2 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar2 = 0;
	}
	else
	{
		iVar2 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	if (iVar2 == iVar1)
	{
		uVar8 = pUnit->dwUnitType;
		if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
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
		if (DVar3 == nY)
			goto LAB_6fac1fb5;
	}
	if (bVar10)
	{
		UNITS_SetAnimationFrame(pUnit, 10);
		pUnit->dwFrameCountPrecise = (pUnit->dwFrameCountPrecise & 0xffffff00U) + 0x100;
		return 0;
	}
	iVar2 = 0;
	if (iVar9 == 0x4e)
	{
		iVar2 = 8;
	}
	else if (iVar9 == 0x21c)
	{
		uVar8 = UNITS_GetDistanceToCoordinates(pUnit, iVar1, (int)nY);
		iVar2 = (-(uint32_t)(uVar8 < 2) & 2) + 10;
	}
	UNITS_SetAnimationFrame(pUnit, iVar2);
	pUnit->dwFrameCountPrecise = (pUnit->dwFrameCountPrecise & 0xffffff00U) + 0x100;
	return 0;
}

//D2Client.0x6FAC2180
uint32_t __fastcall sub_6FAC2180(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	D2ActiveRoomStrc* pRoom;
	int iStack_8;
	int iStack_4;

	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2);
	if (pSkill == nullptr)
	{
		return 0;
	}
	pDVar1 = CUNIT_GetPlayer();
	if (pUnit == pDVar1)
	{
		iVar2 = STATES_CheckState(pUnit, 0x36);
		if (iVar2 != 0)
		{
			return 0;
		}
		iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		if (iVar2 == a2)
		{
			uVar3 = SKILLS_GetFlags(pSkill);
			if ((uVar3 & 1) != 0)
			{
				return 0;
			}
		}
	}
	pDVar1 = sub_6FB296A0((int)pUnit);
	iStack_8 = 0;
	iStack_4 = 0;
	iVar2 = SKILLS_CheckIfCanLeapTo(pUnit, pDVar1, &iStack_8, &iStack_4);
	if (iVar2 == 0)
	{
		if (pDVar1 != nullptr)
		{
			iVar2 = UNITS_IsInMeleeRange(pUnit, pDVar1, 0);
			if (iVar2 != 0)
			{
				uVar4 = sub_6FABDA60(pUnit, &pDVar1->dwUnitType);
				return uVar4;
			}
		}
		if ((pUnit == nullptr) || (pUnit->dwUnitType != 1))
		{
			sub_6FB514E0(pUnit, 0x13);
		}
		return 0;
	}
	pRoom = UNITS_GetRoom(pUnit);
	if (pRoom == nullptr)
	{
		return 0;
	}
	iVar2 = PATH_GetUnitCollisionPattern(pUnit);
	COLLISION_SetMaskWithPattern(pRoom, iStack_8, iStack_4, iVar2, 0x80);
	SKILLS_SetParam1(pSkill, iStack_8);
	SKILLS_SetParam2(pSkill, iStack_4);
	if (pDVar1 == nullptr)
	{
		SKILLS_SetParam3(pSkill, 6);
	}
	else
	{
		SKILLS_SetParam3(pSkill, pDVar1->dwUnitType);
		SKILLS_SetParam4(pSkill, pDVar1->dwUnitId);
	}
	SKILLS_SetFlags(pSkill, 0x1080);
	sub_6FABDD20(pUnit);
	return 1;
}

//D2Client.0x6FAC22F0
uint32_t __fastcall sub_6FAC22F0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	uint32_t uVar1;
	int iVar2;
	uint32_t uVar3;
	D2UnitStrc* pTargetUnit;
	uint32_t uVar4;
	float fVar5;
	float fVar6;
	int iVar7;
	char cStack_4;

	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2);
	if (pSkill == nullptr)
	{
		return 0;
	}
	uVar4 = 0;
	uVar1 = SKILLS_GetFlags(pSkill);
	if ((uVar1 & 0x100) == 0)
		goto LAB_6fac23aa;
	iVar2 = sub_6FAC1E40(pUnit, pSkill, 1);
	if (iVar2 == 0)
	{
		return 0;
	}
	iVar2 = SKILLS_GetParam3(pSkill);
	uVar3 = SKILLS_GetParam4(pSkill);
	if (iVar2 == 6)
	{
	LAB_6fac2356:
		pTargetUnit = sub_6FABB890(pUnit, 0, 0, 3, 0, 0xffffffff, nullptr);
		if (pTargetUnit == nullptr)
		{
			pUnit->dwFrameCountPrecise = 0x400;
			goto LAB_6fac23aa;
		}
	}
	else
	{
		pTargetUnit = sub_6FB269F0(uVar3, iVar2);
		if (pTargetUnit == nullptr)
			goto LAB_6fac2356;
	}
	UNITS_SetTargetUnitForDynamicUnit(pUnit, pTargetUnit);
	sub_6FB29010(pUnit, 0);
	iVar7 = 0;
	fVar6 = 0.0;
	fVar5 = 0.0;
	uVar3 = UNITS_GetHitClass(pUnit);
	iVar2 = sub_6FB4F4D0((int)pUnit, uVar3);
	sub_6FB55820(iVar2, pUnit, fVar5, fVar6, iVar7);
	uVar4 = 1;
LAB_6fac23aa:
	cStack_4 = (char)uVar1;
	if (cStack_4 < '\0')
	{
		sub_6FAC1A20(pUnit, pSkill);
		sub_6FAC1B30(pUnit, pSkill);
		return 1;
	}
	SKILLS_SetFlags(pSkill, 0x1000);
	return uVar4;
}

//D2Client.0x6FAC23F0
void __fastcall sub_6FAC23F0(D2UnitStrc* pUnit, uint32_t a2, int a3)
{
	D2DynamicPathStrc* pDynamicPath;
	uint8_t nDirection;
	uint8_t bVar1;
	int iVar2;
	int nXPos;
	int nAngle;
	int* pXAdjust;
	int* pYAdjust;
	int bOrder;
	int iStack_8;
	int iStack_4;

	pDynamicPath = pUnit->pDynamicPath;
	if (pDynamicPath != nullptr)
	{
		nDirection = PATH_GetDirection(pDynamicPath);
		bVar1 = nDirection + 0x15;
		if (a3 == 0)
		{
			bVar1 = nDirection + 0x2a;
		}
		PATH_SetDirection(pDynamicPath, bVar1 & 0x3f);
		iVar2 = D2GFX_CheckPerspective();
		if (iVar2 == 0)
		{
			iStack_4 = UNITS_GetClientCoordX(pUnit);
			iStack_8 = UNITS_GetClientCoordY(pUnit);
		}
		else
		{
			pYAdjust = &iStack_8;
			bOrder = 0;
			pXAdjust = &iStack_4;
			nAngle = 0x60;
			iVar2 = UNITS_GetPrecisionY(pUnit);
			nXPos = UNITS_GetPrecisionX(pUnit);
			SCALE_ScalePerspectivePosition(nXPos, iVar2, nAngle, pXAdjust, pYAdjust, bOrder);
			iVar2 = sub_6FAB5890();
			iStack_4 = iStack_4 + iVar2;
			iVar2 = sub_6FAB58A0();
			iStack_8 = iStack_8 + iVar2;
		}
		sub_6FB5A720(pUnit, (DrawMode)(a2), iStack_4, iStack_8, (uint32_t)(pUnit->dwUnitType == 0), 0);
		PATH_SetDirection(pDynamicPath, nDirection);
	}
}

//D2Client.0x6FAC24C0
uint32_t __fastcall sub_6FAC24C0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	D2DynamicPathStrc* pDynamicPath;
	D2SkillStrc* pDVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	D2ActiveRoomStrc* pRoom;
	uint16_t nMask;
	bool bVar7;
	uint32_t nY;
	uint32_t uStack_14;
	uint32_t uStack_10;
	uint32_t uStack_c;
	D2PathPointStrc* pDStack_8;
	D2SkillStrc* pDStack_4;

	if (pUnit == nullptr)
	{
		return 0;
	}
	if ((pUnit->dwUnitType != 0) && (pUnit->dwUnitType != 1))
	{
		return 0;
	}
	pDVar2 = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2);
	pDynamicPath = pUnit->pDynamicPath;
	if (pDVar2 == nullptr)
	{
		return 0;
	}
	if (pDynamicPath == nullptr)
	{
		return 0;
	}
	pDStack_4 = pDVar2;
	pDVar3 = CUNIT_GetPlayer();
	if (pUnit == pDVar3)
	{
		iVar4 = SKILLS_GetSkillIdFromSkill(pDVar2, __FILE__, __LINE__);
		if ((iVar4 == a2) && (uVar5 = SKILLS_GetFlags(pDVar2), (uVar5 & 1) != 0))
		{
			return 0;
		}
		iVar4 = STATES_CheckState(pUnit, 0x36);
		if (iVar4 != 0)
		{
			return 0;
		}
	}
	iVar4 = sub_6FABA950(pUnit, (int*)&uStack_14, (int*)&uStack_10);
	if (iVar4 == 0)
	{
		return 0;
	}
	pDVar3 = sub_6FB296A0((int)pUnit);
	if ((pDVar3 != nullptr) && (iVar4 = UNITS_IsInMeleeRange(pUnit, pDVar3, 0), iVar4 != 0))
	{
		uVar6 = sub_6FABDA60(pUnit, &pDVar3->dwUnitType);
		return uVar6;
	}
	uStack_c = (uint32_t)(pUnit->dwUnitType == 0);
	bVar7 = uStack_c != 0;
	nMask = (-(uint16_t)(uStack_c != 0) & 0xff80) + 0x100;
	PATH_SetMoveTestCollisionMask(pDynamicPath, 0xc01);
	PATH_SetType(pDynamicPath, 7);
	iVar4 = D2Common_10142(pDynamicPath, pUnit, 0);
	if (iVar4 == 0)
		goto LAB_6fac26e9;
	iVar4 = pUnit->dwClassId;
	if (uStack_c == 0)
	{
		if ((iVar4 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar4))
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar4 * 0x1a8;
		}
		uVar5 = (uint32_t) * (short*)(iVar4 + 0x32);
		iVar4 = 0x48f;
	LAB_6fac2659:
		PATH_SetVelocity(pDynamicPath, uVar5 << __LINE__, __FILE__, iVar4);
	}
	else if (((-1 < iVar4) && (iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8))) &&
	         (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + iVar4 * 0xc4, iVar1 != 0))
	{
		iVar4 = 0x489;
		uVar5 = (uint32_t) * (uint8_t*)(iVar1 + 0x40);
		goto LAB_6fac2659;
	}
	PATH_SetMoveTestCollisionMask(pDynamicPath, 0x401);
	iVar4 = PATH_GetPathPoints(pDynamicPath, &pDStack_8);
	if (iVar4 != 0)
	{
		uStack_14 = (uint32_t)pDStack_8[iVar4 + -1].X;
		uStack_10 = (uint32_t)pDStack_8[iVar4 + -1].Y;
		iVar4 = PATH_GetUnitCollisionPattern(pUnit);
		uVar5 = uStack_14;
		nY = uStack_10;
		pRoom = UNITS_GetRoom(pUnit);
		COLLISION_SetMaskWithPattern(pRoom, uVar5, nY, iVar4, nMask);
		pDVar2 = pDStack_4;
		SKILLS_SetFlags(pDStack_4, 1);
		SKILLS_SetParam1(pDVar2, uStack_14);
		SKILLS_SetParam2(pDVar2, uStack_10);
		sub_6FABDD20(pUnit);
		return 1;
	}
LAB_6fac26e9:
	PATH_SetMoveTestCollisionMask(pDynamicPath, (-(uint32_t)bVar7 & 0xffffe008) + 0x3c01);
	return 0;
}

//D2Client.0x6FAC2700
uint32_t __fastcall sub_6FAC2700(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2DynamicPathStrc* pDynamicPath;
	D2SkillStrc* pSkill;
	int iVar1;
	int nY;
	uint32_t uVar2;
	int nCollisionPattern;
	D2ActiveRoomStrc* pRoom;
	int nCollisionMask;
	bool bVar3;
	uint16_t nMask;
	int iVar4;

	pDynamicPath = pUnit->pDynamicPath;
	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2);
	if ((pSkill != nullptr) && (pDynamicPath != nullptr))
	{
		bVar3 = pUnit->dwUnitType == 0;
		nCollisionMask = (-(uint32_t)bVar3 & 0xffffff80) + 0x100;
		iVar1 = SKILLS_GetParam1(pSkill);
		nY = SKILLS_GetParam2(pSkill);
		uVar2 = SKILLS_GetFlags(pSkill);
		if (((uint8_t)uVar2 & 3) == 3)
		{
			iVar4 = nCollisionMask;
			nCollisionPattern = PATH_GetUnitCollisionPattern(pUnit);
			nMask = (uint16_t)iVar4;
			pRoom = UNITS_GetRoom(pUnit);
			COLLISION_ResetMaskWithPattern(pRoom, iVar1, nY, nCollisionPattern, nMask);
			PATH_SetFootprintCollisionMask(pDynamicPath, nCollisionMask);
			PATH_SetMoveTestCollisionMask(pDynamicPath, (-(uint32_t)bVar3 & 0xffffe008) + 0x3c01);
			SKILLS_SetFlags(pSkill, 0);
			iVar1 = sub_6FB4F990((int)pUnit, 0x9e3);
			sub_6FB556A0(iVar1);
			return 1;
		}
		if ((uVar2 & 1) != 0)
		{
			UNITS_SetAnimationFrame(pUnit, 3);
			pUnit->dwFrameCountPrecise = 0x500;
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC2800
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAC2800(D2UnitStrc* pUnit)
{
	D2SkillStrc* pSkill;
	uint32_t uVar1;
	int iVar2;
	int in_EDX;

	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, in_EDX);
	if (pSkill != nullptr)
	{
		uVar1 = SKILLS_GetFlags(pSkill);
		if ((uVar1 & 1) != 0)
		{
			SKILLS_SetFlags(pSkill, uVar1 | 2);
		}
	}
	iVar2 = sub_6FB4F990((int)pUnit, 0x9e3);
	sub_6FB556A0(iVar2);
}

//D2Client.0x6FAC2840
uint32_t __fastcall sub_6FAC2840(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	short sVar2;
	int iVar3;
	int iVar4;

	if (((((-1 < a2) && (iVar4 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar4 + 0xba0))) && (iVar1 = *(int*)(iVar4 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	        ((sVar2 = *(short*)(iVar1 + 0x80), -1 < sVar2 && ((int)sVar2 < *(int*)(iVar4 + 0xc4))))) &&
	    (-1 < *(short*)(iVar1 + 0x110)))
	{
		iVar3 = (int)*(short*)(iVar1 + 0x110);
		if (iVar3 < *(int*)(iVar4 + 0xbc0))
		{
			if ((-1 < *(short*)(iVar1 + 0x112)) &&
			    ((int)*(short*)(iVar1 + 0x112) < *(int*)(iVar4 + 0xbc0)))
			{
				iVar4 = STATES_CheckState(pUnit, (int)sVar2);
				if (iVar4 != 0)
				{
					iVar3 = (int)*(short*)(iVar1 + 0x112);
				}
			}
			sub_6FB5BA70(pUnit, iVar3, 2, 0, 0, 0, 0, 0);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC2900
uint32_t __fastcall sub_6FAC2900(D2UnitStrc* pUnit, int a2, uint32_t a3, uint32_t a4, uint32_t a5, int a6, int a7, int a8)
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t* puVar4;
	int local_68;
	int local_64;
	int local_60;
	uint32_t local_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	uint32_t uStack_30;
	uint32_t uStack_2c;
	code* pcStack_8;
	int iStack_4;

	iVar2 = sub_6FABA950(pUnit, &local_64, &local_60);
	if (iVar2 == 0)
	{
		return 0;
	}
	local_68 = a2;
	if (a7 != 0)
	{
		local_68 = a2 + -1;
		pDVar3 = sub_6FABABC0(pUnit, a3, a4, a5);
		if (pDVar3 != nullptr)
		{
			if (a8 != 0)
			{
				D2COMMON_10203_PATH_SetRotateFlag(pDVar3->pDynamicPath, 0);
			}
			UNITS_SetAnimationSpeed(pDVar3, a6);
		}
	}
	puVar4 = &local_5c;
	for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar4 = 0;
		puVar4 = puVar4 + 1;
	}
	uVar1 = pUnit->dwUnitType;
	local_5c = 0x21;
	pDStack_58 = pUnit;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
	uStack_30 = a4;
	iStack_40 = local_64;
	iStack_3c = local_60;
	uStack_2c = a5;
	uStack_4c = a3;
	pcStack_8 = (code*)(sub_6FAC9E80);
	if (a8 != 0)
	{
		local_5c = local_5c | 0x2000;
	}
	iVar2 = 0;
	if (0 < local_68)
	{
		do
		{
			iStack_4 = iVar2;
			pDVar3 = sub_6FB3E070(&local_5c);
			if (pDVar3 != nullptr)
			{
				if (a8 != 0)
				{
					D2COMMON_10203_PATH_SetRotateFlag(pDVar3->pDynamicPath, 0);
				}
				UNITS_SetAnimationSpeed(pDVar3, a6);
			}
			iVar2 = iVar2 + 1;
		} while (iVar2 < local_68);
	}
	return 1;
}

//D2Client.0x6FAC2A80
uint32_t __fastcall sub_6FAC2A80(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 != 0))
	{
		iVar1 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 0x138), a2, a3);
			if (0 < iVar2)
			{
				uVar3 = sub_6FAC2900(pUnit, iVar2, iVar1, a2, a3, 0x200, 1, 0);
				return uVar3;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC2B30
uint32_t __fastcall sub_6FAC2B30(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 != 0))
	{
		iVar1 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 0x138), a2, a3);
			if (0 < iVar2)
			{
				uVar3 = sub_6FAC2900(pUnit, iVar2, iVar1, a2, a3, 0x100, 0, 1);
				return uVar3;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC2BE0
uint32_t __fastcall sub_6FAC2BE0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 != 0))
	{
		iVar1 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 0x138), a2, a3);
			if (0 < iVar2)
			{
				uVar3 = sub_6FAC2900(pUnit, iVar2, iVar1, a2, a3, 0x200, 0, 1);
				return uVar3;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC2C90
uint32_t __fastcall sub_6FAC2C90(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	bool bVar2;
	int iVar3;
	D2ActiveRoomStrc* pRoom;
	int iVar4;

	iVar3 = a3;
	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		return 0;
	}
	pRoom = UNITS_GetRoom(pUnit);
	if ((pRoom == nullptr) || (iVar4 = DUNGEON_IsRoomInTown(pRoom), iVar4 != 0))
	{
		bVar2 = true;
	}
	else
	{
		bVar2 = false;
	}
	if (0 < *(short*)(iVar1 + 0x10e))
	{
		iVar4 = sub_6FB4F990((int)pUnit, (int)*(short*)(iVar1 + 0x10e));
		if (!bVar2)
		{
			if (iVar4 == 0)
			{
				sub_6FB55820((int)*(short*)(iVar1 + 0x10e), pUnit, 0.0, 0.0, 0);
			}
			goto LAB_6fac2d31;
		}
		if (iVar4 != 0)
		{
			sub_6FB555C0(iVar4, (int)pUnit, 1);
		}
	}
	if (bVar2)
	{
		return 0;
	}
LAB_6fac2d31:
	a3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x114), a2, a3);
	if (0 < a3)
	{
		do
		{
			sub_6FAC2D90(pUnit, iVar1, a2, iVar3);
			sub_6FAC2D90(pUnit, iVar1, a2, iVar3);
			sub_6FAC2D90(pUnit, iVar1, a2, iVar3);
			a3 = a3 + -1;
		} while (a3 != 0);
	}
	return 1;
}

//D2Client.0x6FAC2D90
void __fastcall sub_6FAC2D90(D2UnitStrc* pUnit, int a2, int a3, int a4)
{
	D2SeedStrc* pDVar1;
	short sVar2;
	int iVar3;
	uint64_t DVar4;
	uint32_t uVar5;
	int32_t DVar6;
	D2UnitStrc* pMissile;
	uint32_t uVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	uint32_t* puVar11;
	int local_74;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_2c;

	pDVar1 = &pUnit->pSeed;
	uVar5 = sub_6FAA88D0(&pDVar1->nLowSeed);
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
	{
		local_74 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_74 = 0;
	}
	else
	{
		local_74 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
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
	iVar8 = *(int*)(byte_6FB6E9E0 + (uVar5 & 7) * 4);
	iVar3 = *(int*)(byte_6FB6EA00 + (uVar5 & 7) * 4);
	iVar9 = local_74 + iVar8;
	local_74 = (int)*(short*)(a2 + 0xea);
	if (local_74 < 0)
	{
		return;
	}
	if (*(short*)(a2 + 0xec) < 0)
		goto LAB_6fac2ebb;
	if (*(short*)(a2 + 0xee) < 0)
	{
		uVar7 = sub_6FAA88D0(&pDVar1->nLowSeed);
		if ((uVar7 & 1) != 0)
			goto LAB_6fac2ebb;
		sVar2 = *(short*)(a2 + 0xec);
	}
	else
	{
		DVar4 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
		*(uint64_t*)pDVar1 = DVar4;
		iVar10 = (int)(((uint64_t)DVar4 & 0xffffffff) % 3);
		if (iVar10 == 0)
		{
			local_74 = (int)*(short*)(a2 + 0xec);
			goto LAB_6fac2ebb;
		}
		if (iVar10 != 1)
			goto LAB_6fac2ebb;
		sVar2 = *(short*)(a2 + 0xee);
	}
	local_74 = (int)sVar2;
LAB_6fac2ebb:
	puVar11 = &uStack_5c;
	for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
	{
		*puVar11 = 0;
		puVar11 = puVar11 + 1;
	}
	iStack_4c = local_74;
	uStack_5c = 3;
	iStack_3c = -iVar8;
	iStack_2c = a4;
	pDStack_58 = pUnit;
	iStack_48 = iVar9;
	iStack_44 = (int)DVar6 + iVar3;
	iStack_40 = iVar3;
	pMissile = sub_6FB3E070(&uStack_5c);
	if (pMissile != nullptr)
	{
		uVar7 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(a2 + 0x118), a3, a4);
		if ((int)uVar7 < 1)
		{
			uVar5 = 0;
		}
		else if ((uVar7 & uVar7 - 1) == 0)
		{
			uVar5 = sub_6FAA88D0(&pDVar1->nLowSeed);
			uVar5 = uVar5 & uVar7 - 1;
		}
		else
		{
			DVar4 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar4;
			uVar5 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar7);
		}
		sub_6FB5FC80((int)pMissile, 0, 0, uVar5);
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			iVar8 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar8 = 0;
		}
		else
		{
			iVar8 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		MISSILE_SetTargetX(pMissile, iVar8);
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 != 2) && (((int)uVar7 < 4 || (5 < (int)uVar7))))
		{
			if (pUnit->pDynamicPath == nullptr)
			{
				MISSILE_SetTargetY(pMissile, 0);
				return;
			}
			iVar8 = PATH_GetYPosition(pUnit->pDynamicPath);
			MISSILE_SetTargetY(pMissile, iVar8);
			return;
		}
		MISSILE_SetTargetY(pMissile, (int)(*(int32_t*)&pUnit->pDynamicPath->tTargetCoord));
	}
}

//D2Client.0x6FAC3010
uint32_t __fastcall sub_6FAC3010(D2UnitStrc* pUnit, uint32_t a2, int a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	uint32_t* puVar7;
	int iStack_68;
	int iStack_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	uint32_t uStack_30;
	int iStack_2c;

	if ((-1 < (int)a2) && ((int)a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)))
	{
		iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c;
		if (iVar4 != 0)
		{
			local_60 = iVar4;
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 100), a2, a3);
			if (iVar2 < 1)
			{
				return 0;
			}
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x114), a2, a3);
			if (iVar2 < 1)
			{
				return 0;
			}
			iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x118), a2, a3);
			if (iVar3 < 1)
			{
				return 0;
			}
			iVar4 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x11c), a2, a3);
			if (iVar4 < 1)
			{
				return 0;
			}
			iVar5 = sub_6FABA950(pUnit, &iStack_68, &iStack_64);
			iVar1 = local_60;
			if (iVar5 == 0)
			{
				return 0;
			}
			puVar7 = &uStack_5c;
			for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar7 = 0;
				puVar7 = puVar7 + 1;
			}
			uStack_5c = 1;
			iStack_48 = iStack_68;
			iStack_44 = iStack_64;
			iStack_2c = a3;
			pDStack_58 = pUnit;
			uStack_30 = a2;
			if (-1 < *(short*)(local_60 + 0xea))
			{
				iStack_4c = (int)*(short*)(local_60 + 0xea);
				pDVar6 = sub_6FB3E070(&uStack_5c);
				if (pDVar6 != nullptr)
				{
					sub_6FB5FC80((int)pDVar6, iVar4 * iVar2, 0, iVar3 * iVar2);
					sub_6FB5FCB0((int)pDVar6, -iVar4, 0, -iVar3, 1);
				}
			}
			if (-1 < *(short*)(iVar1 + 0xec))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0xec);
				pDVar6 = sub_6FB3E070(&uStack_5c);
				if (pDVar6 != nullptr)
				{
					sub_6FB5FC80((int)pDVar6, iVar4 * iVar2, 0, iVar3 * iVar2);
					sub_6FB5FCB0((int)pDVar6, -iVar4, 0, -iVar3, 1);
				}
			}
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC3200
uint32_t __fastcall sub_6FAC3200(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	D2UnitStrc* pMissile;
	int* piVar3;
	int local_64;
	int local_60[2];
	D2UnitStrc* local_58;
	int local_4c;
	int local_48;
	int local_44;
	int local_30;
	uint32_t local_2c;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		iVar2 = sub_6FABA950(pUnit, &local_64, local_60);
		if (iVar2 == 0)
		{
			return 0;
		}
		piVar3 = local_60;
		for (iVar2 = 0x17; piVar3 = piVar3 + 1, iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*piVar3 = 0;
		}
		local_60[1] = 1;
		local_48 = local_64;
		local_44 = local_60[0];
		local_2c = a3;
		local_58 = pUnit;
		local_30 = a2;
		if ((-1 < *(short*)(iVar1 + 0xea)) &&
		    (local_4c = (int)*(short*)(iVar1 + 0xea),
		        local_4c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			sub_6FB3E070((uint32_t*)(local_60 + 1));
		}
		if ((-1 < *(short*)(iVar1 + 0xec)) &&
		    (local_4c = (int)*(short*)(iVar1 + 0xec),
		        local_4c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			pMissile = sub_6FB3E070((uint32_t*)(local_60 + 1));
			if (pMissile != nullptr)
			{
				MISSILE_SetTargetX(pMissile, pUnit->dwInitSeed);
			}
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC3310
uint32_t __fastcall sub_6FAC3310(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	int32_t DVar4;
	D2UnitStrc* pMissile;
	int* piVar5;
	int local_64;
	int local_60[2];
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int local_4c;
	int local_40;
	int iStack_3c;
	int local_30;
	uint32_t local_2c;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0))
	{
		iVar2 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			iVar3 = sub_6FABA950(pUnit, &local_64, local_60);
			if (iVar3 != 0)
			{
				if (pUnit != nullptr)
				{
					pUnit->dwFlags = pUnit->dwFlags | 0x40;
				}
				piVar5 = local_60;
				for (iVar3 = 0x17; piVar5 = piVar5 + 1, iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*piVar5 = 0;
				}
				local_60[1] = 2;
				local_2c = a3;
				uVar1 = pUnit->dwUnitType;
				local_58 = pUnit;
				local_54 = pUnit;
				local_4c = iVar2;
				local_30 = a2;
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
				local_40 = local_64 - local_40;
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
				iStack_3c = local_60[0] - (int)DVar4;
				pMissile = sub_6FB3E070((uint32_t*)(local_60 + 1));
				if (pMissile != nullptr)
				{
					MISSILE_SetTargetX(pMissile, -iStack_3c);
					MISSILE_SetTargetY(pMissile, local_40);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC3480
uint32_t __fastcall sub_6FAC3480(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int64_t lVar2;
	uint64_t DVar3;
	D2UnitStrc* pDVar4;
	int32_t nY;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	uint32_t* puVar9;
	uint32_t local_7c;
	int local_78;
	int local_74;
	int local_70;
	int local_6c;
	uint32_t local_68;
	uint32_t uStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_34;
	int iStack_30;
	int iStack_2c;

	if ((-1 < a2) && (iVar5 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar5 + 0xba0)))
	{
		iVar6 = *(int*)(iVar5 + 0xb98) + a2 * 0x23c;
		if (iVar6 != 0)
		{
			local_68 = (uint32_t) * (short*)(iVar6 + 0xea);
			if (((-1 < (int)local_68) && ((int)local_68 < *(int*)(iVar5 + 0xb6c))) &&
			    (local_6c = *(int*)(iVar5 + 0xb64) + local_68 * 0x1a4, local_6c != 0))
			{
				local_7c = (uint32_t) * (short*)(iVar6 + 0xec);
				if (((int)local_7c < 0) || (*(int*)(iVar5 + 0xb6c) <= (int)local_7c))
				{
					local_7c = 0xffffffff;
				}
				local_70 = iVar6;
				pDVar4 = sub_6FB296A0((int)pUnit);
				if (pDVar4 != nullptr)
				{
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
					D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iVar5, (int)nY);
					sub_6FB29010(pUnit, 1);
					iVar6 = local_70;
				}
				iVar5 = sub_6FABA950(pUnit, &local_78, &local_74);
				if (iVar5 != 0)
				{
					if (pDVar4 == nullptr)
					{
						UNITS_UpdateDirectionAndSpeed(pUnit, local_78, local_74);
					}
					puVar9 = &uStack_5c;
					for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
					{
						*puVar9 = 0;
						puVar9 = puVar9 + 1;
					}
					uVar1 = pUnit->dwUnitType;
					uStack_5c = 0x25;
					pDStack_58 = pUnit;
					if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
					uVar1 = pUnit->dwUnitType;
					if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
					iStack_40 = local_78;
					iStack_3c = local_74;
					iStack_30 = a2;
					iVar6 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar6 + 0x114), a2, a3);
					iVar7 = sub_6FB5FC40((int)pUnit);
					iVar8 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(local_70 + 0x118), a2, a3);
					local_70 = (uint32_t) * (uint8_t*)(local_6c + 0x178) << 8;
					iVar8 = iVar8 + *(int*)(local_6c + 0x3c);
					iVar5 = (iVar6 + iVar7) * -2;
					if (iVar8 != 0)
					{
						local_70 = (int)((int64_t)((uint64_t) * (uint8_t*)(local_6c + 0x178) << 8) /
						                 (int64_t)iVar8);
						iVar5 = iVar5 / iVar8;
					}
					uStack_4c = local_68;
					if (0 < (int)local_7c)
					{
						DVar3 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
						                   (uint64_t)(pUnit->pSeed).nHighSeed);
						local_68 = (*(uint32_t*)((uint8_t*)&DVar3 + 0)) & 1;
						(*(uint64_t*)&pUnit->pSeed) = DVar3;
						if (((uint64_t)DVar3 & 1) != 0)
						{
							uStack_4c = local_7c;
						}
					}
					lVar2 = (uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5;
					uStack_60 = (uint32_t)((uint64_t)lVar2 >> 0x20);
					DVar3 = (uint64_t)(lVar2 + (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar3;
					iStack_34 = (uint32_t) * (uint8_t*)(local_6c + 0x9a) +
					            *(int*)(byte_6FB6EA28 + ((*(uint32_t*)((uint8_t*)&DVar3 + 0)) % 5) * 4);
					pDVar4 = sub_6FB3E070(&uStack_5c);
					if (pDVar4 != nullptr)
					{
						PATH_SetNewDistance(pDVar4->pDynamicPath, (uint8_t)iVar8);
						UNITS_SetAnimationSpeed(pDVar4, local_70);
						MISSILE_SetTotalFrames(pDVar4, iVar8);
						MISSILE_SetCurrentFrame(pDVar4, iVar8);
						sub_6FB5FC80((int)pDVar4, 0, 0, iVar6 + iVar7);
						sub_6FB5FE00((int*)pDVar4);
						sub_6FB5FCB0((int)pDVar4, 0, 0, iVar5, 1);
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC37C0
uint32_t __fastcall sub_6FAC37C0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	D2UnitStrc* pMissile;
	int iVar3;
	int local_8;
	int local_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar3 != 0))
	{
		iVar1 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			iVar2 = sub_6FABA950(pUnit, &local_4, &local_8);
			if (iVar2 != 0)
			{
				if (pUnit != nullptr)
				{
					pUnit->dwFlags = pUnit->dwFlags | 0x40;
				}
				pMissile = sub_6FB3ED40(pUnit, iVar1, a2, a3);
				if (pMissile != nullptr)
				{
					iVar2 = MISSILE_GetTotalFrames(pMissile);
					iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x118), a2, a3);
					iVar1 = sub_6FB5FC40((int)pUnit);
					iVar3 = iVar3 + iVar1;
					if (iVar2 == 0)
					{
						iVar2 = iVar3 / 2;
					}
					else
					{
						iVar2 = iVar3 / iVar2;
					}
					sub_6FB5FC80((int)pMissile, 0, 0, iVar3);
					sub_6FB5FCB0((int)pMissile, 0, 0, -iVar2, 1);
					sub_6FB5FE00((int*)pMissile);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC38E0
uint32_t __fastcall sub_6FAC38E0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	short sVar2;
	int iVar3;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		iVar3 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			sVar2 = *(short*)(iVar1 + 0x10e);
			if (0 < sVar2)
			{
				sub_6FB55820((int)sVar2, nullptr, 0.0, 0.0, 0);
			}
			sub_6FABAD50(pUnit, 0x222, a2, a3);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC3970
uint32_t __fastcall sub_6FAC3970(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int local_1c;
	int local_18;
	int iStack_14;
	int iStack_10;
	int iStack_c;
	int iStack_8;
	int local_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (local_4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, local_4 != 0))
	{
		iVar1 = sub_6FABF670(pUnit, a2);
		if (((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
		    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar3 != 0))
		{
			local_1c = 0;
			local_18 = 0;
			D2Common_11066(pUnit, &local_1c, &local_18);
			if ((local_1c != 0) || (local_18 != 0))
			{
				pDVar2 = sub_6FABAD50(pUnit, iVar1, a2, a3);
				if (pDVar2 != nullptr)
				{
					iVar1 = (int)*(short*)(iVar3 + 0x96);
					if (iVar1 < 1)
					{
						iVar1 = 1;
					}
					iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(local_4 + 0x114), a2, a3);
					iStack_10 = -(iVar1 * local_1c);
					iStack_14 = -(iVar1 * local_18);
					DUNGEON_GameSubtileToClientCoords(&iStack_10, &iStack_14);
					iStack_8 = local_1c;
					iStack_c = local_18;
					DUNGEON_GameSubtileToClientCoords(&iStack_8, &iStack_c);
					sub_6FB5FC80((int)pDVar2, iStack_10, iStack_14, iVar3 * iVar1);
					sub_6FB5FCB0((int)pDVar2, iStack_8, iStack_c, -iVar3, 1);
					sub_6FB5FE00((int*)pDVar2);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC3B00
uint32_t __fastcall sub_6FAC3B00(int* a1, int a2, uint32_t a3)
{
	D2UnitStrc** ppDVar1;
	int iVar2;
	int iVar3;

	if (((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0))) && (iVar3 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar3 != 0))
	{
		iVar3 = (int)*(short*)(iVar3 + 0xea);
		if ((-1 < iVar3) && (iVar3 < *(int*)(iVar2 + 0xb6c)))
		{
			iVar2 = *a1;
			if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
			{
				ppDVar1 = *(D2UnitStrc***)(a1[0xb] + 0x10);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				ppDVar1 = nullptr;
			}
			else
			{
				ppDVar1 = (D2UnitStrc**)PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			iVar2 = *a1;
			if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
			{
				iVar2 = *(int*)(a1[0xb] + 0xc);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iVar2 = 0;
			}
			else
			{
				iVar2 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			sub_6FB3EAF0((int)a1, iVar3, iVar2, ppDVar1, a2, a3);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC3BC0
bool __fastcall sub_6FAC3BC0(int* a1, int a2, uint32_t a3)
{
	D2UnitStrc** ppDVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;

	if (((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0))) && (iVar4 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar4 != 0))
	{
		iVar4 = (int)*(short*)(iVar4 + 0xec);
		if ((-1 < iVar4) && (iVar4 < *(int*)(iVar2 + 0xb6c)))
		{
			iVar2 = *a1;
			if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
			{
				ppDVar1 = *(D2UnitStrc***)(a1[0xb] + 0x10);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				ppDVar1 = nullptr;
			}
			else
			{
				ppDVar1 = (D2UnitStrc**)PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			iVar2 = *a1;
			if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
			{
				iVar2 = *(int*)(a1[0xb] + 0xc);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iVar2 = 0;
			}
			else
			{
				iVar2 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			pDVar3 = sub_6FB3EAF0((int)a1, iVar4, iVar2, ppDVar1, a2, 1);
			return pDVar3 != nullptr;
		}
		return true;
	}
	return false;
}

//D2Client.0x6FAC3C90
uint32_t __fastcall sub_6FAC3C90(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int local_8;
	int local_4;

	if (((-1 < a2) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar1 + 0xba0))) && (iVar4 = *(int*)(iVar1 + 0xb98) + a2 * 0x23c, iVar4 != 0))
	{
		iVar4 = (int)*(short*)(iVar4 + 0xec);
		if ((-1 < iVar4) && (iVar4 < *(int*)(iVar1 + 0xb6c)))
		{
			pDVar2 = sub_6FABAD50(pUnit, iVar4, a2, 1);
			if (pDVar2 == nullptr)
			{
				return 0;
			}
			pDVar3 = sub_6FB296A0((int)pUnit);
			if (pDVar3 != nullptr)
			{
				sub_6FB5FB10((int)pDVar2);
				sub_6FB5C3C0(pDVar3, 0xe, &local_4, &local_8);
				sub_6FB5FC80((int)pDVar2, local_4, 0, -local_8);
			}
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC3D50
uint32_t __fastcall sub_6FAC3D50(D2UnitStrc* pUnit, int a2, int a3)
{
	D2DynamicPathStrc* pDynamicPath;
	uint8_t nDirection;
	int32_t DVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t* puVar8;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	int iStack_2c;
	code* pcStack_8;
	uint32_t uStack_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar4 != 0))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		iVar6 = (int)*(short*)(iVar4 + 0xea);
		if ((-1 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			uVar7 = pUnit->dwUnitType;
			if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
			{
				DVar1 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar1 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar1 + 2)) = 0;
			}
			else
			{
				DVar1 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar7 = pUnit->dwUnitType;
			if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
			{
				iVar2 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar2 = 0;
			}
			else
			{
				iVar2 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			pDVar3 = sub_6FB3EAF0((int)pUnit, iVar6, iVar2, (D2UnitStrc**)DVar1, a2, a3);
			if (pDVar3 != nullptr)
			{
				nDirection = UNITS_GetDirection(pUnit);
				pDynamicPath = pDVar3->pDynamicPath;
				PATH_SetDirection(pDynamicPath, nDirection);
				D2COMMON_10203_PATH_SetRotateFlag(pDynamicPath, 0);
			}
		}
		iVar6 = (int)*(short*)(iVar4 + 0xec);
		if ((-1 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			iVar4 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x114), a2, a3);
			puVar8 = &uStack_5c;
			for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			iStack_2c = a3;
			uStack_5c = 3;
			pcStack_8 = (code*)(sub_6FAC9E80);
			pDStack_58 = pUnit;
			iStack_4c = iVar6;
			iStack_30 = a2;
			iVar6 = sub_6FABA950(pUnit, &iStack_48, &iStack_44);
			if ((iVar6 != 0) && (uVar7 = 0, 0 < iVar4))
			{
				do
				{
					uVar5 = uVar7 & 0x80000007;
					if ((int)uVar5 < 0)
					{
						uVar5 = (uVar5 - 1 | 0xfffffff8) + 1;
					}
					uStack_40 = (&dword_6FB6EA40)[uVar5];
					uStack_3c = dword_6FB6EA60[uVar5];
					uStack_4 = uVar7;
					sub_6FB3E070(&uStack_5c);
					uVar7 = uVar7 + 1;
				} while ((int)uVar7 < iVar4);
			}
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC3F30
uint32_t __fastcall sub_6FAC3F30(uint32_t a1, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		uVar4 = 0;
	}
	else
	{
		uVar4 = *(uint32_t*)(iVar1 + 0x148);
	}
	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		iVar1 = 0;
	}
	else
	{
		iVar1 = *(int*)(iVar1 + 0x14c);
	}
	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 == 0))
	{
		iVar2 = 0;
	}
	else
	{
		iVar2 = *(int*)(iVar2 + 0x150);
	}
	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar3 == 0))
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = *(int*)(iVar3 + 0x154);
	}
	sub_6FAB7E70(uVar4, (iVar1 * 1000) / 0x19, (iVar2 * 1000) / 0x19, (iVar3 * 1000) / 0x19);
	return 1;
}

//D2Client.0x6FAC4070
uint32_t __fastcall sub_6FAC4070(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	uint8_t nDirection;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	int iStack_40;
	int32_t DStack_3c;
	int iStack_38;
	int iStack_34;
	uint32_t uStack_30;
	int iStack_28;
	int iStack_24;
	int local_20;
	int local_1c;
	int local_18;
	int local_14;
	int local_10;
	D2UnitStrc* local_c;
	int iStack_8;
	int iStack_4;

	if (((a2 < 0) || (iVar5 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar5 + 0xba0) <= a2)) || (local_14 = *(int*)(iVar5 + 0xb98) + a2 * 0x23c, local_14 == 0))
	{
		return 0;
	}
	local_10 = (int)*(short*)(local_14 + 0xec);
	if (((-1 < local_10) && (local_10 < *(int*)(iVar5 + 0xb6c))) &&
	    (iVar5 = *(int*)(iVar5 + 0xb64) + local_10 * 0x1a4, iVar5 != 0))
	{
		local_18 = iVar5;
		local_c = pUnit;
		iVar2 = sub_6FABA950(pUnit, &local_20, &local_1c);
		if (iVar2 == 0)
		{
			return 0;
		}
		uStack_30 = UNITS_GetDistanceToCoordinates(pUnit, local_20, local_1c);
		if ((int)uStack_30 < 1)
		{
			uStack_30 = 1;
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_38 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_38 = 0;
		}
		else
		{
			iStack_38 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_3c = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
		}
		else
		{
			DStack_3c = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iStack_34 = *(int*)(iVar5 + 0x38);
		if (iStack_34 < 1)
		{
			iStack_34 = 1;
		}
		iStack_24 = 1;
		if (0 < *(int*)(local_18 + 0x3c))
		{
			iStack_24 = *(int*)(local_18 + 0x3c);
		}
		iStack_28 = 0;
		local_18 = iStack_34;
		if (iStack_34 < (int)uStack_30)
		{
			iStack_40 = 0;
			iVar2 = iStack_34 * (((local_20 - iStack_38) * 100) / (int)uStack_30);
			iVar5 = iStack_34 * (((local_1c - (int)DStack_3c) * 100) / (int)uStack_30);
			iStack_8 = iVar5;
			iStack_4 = iVar2;
			do
			{
				pDVar3 = sub_6FB3EAF0((int)pUnit, local_10, iVar2 / 100 + iStack_38,
				    (D2UnitStrc**)(iVar5 / 100 + (int)DStack_3c), a2, a3);
				if (pDVar3 != nullptr)
				{
					nDirection = UNITS_GetDirection(pUnit);
					D2COMMON_10160_PathUpdateDirection(pDVar3->pDynamicPath, nDirection);
					iVar4 = MISSILE_GetTotalFrames(pDVar3);
					MISSILE_SetTotalFrames(pDVar3, iStack_40 + iVar4);
					MISSILE_SetCurrentFrame(pDVar3, iStack_40 + iVar4);
					MISSILE_SetActivateFrame(pDVar3, iVar4 - iStack_40);
					pDVar3->dwFlagEx = pDVar3->dwFlagEx | 0x40000;
					pUnit = local_c;
				}
				iVar5 = iVar5 + iStack_8;
				iVar2 = iVar2 + iStack_4;
				local_18 = local_18 + iStack_34;
				iStack_40 = iStack_40 + iStack_24;
				iStack_28 = iStack_28 + 1;
			} while (local_18 < (int)uStack_30);
		}
		iVar5 = (int)*(short*)(local_14 + 0xea);
		if ((-1 < iVar5) && (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			pDVar3 = sub_6FABAD50(pUnit, iVar5, a2, a3);
			if (pDVar3 == nullptr)
			{
				return 0;
			}
			iVar5 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(local_14 + 0x138), a2, a3);
			if (0 < iVar5)
			{
				UNITS_SetAnimationSpeed(pDVar3, iVar5);
			}
			iVar2 = MISSILE_GetTotalFrames(pDVar3);
			iVar5 = iStack_28 * iStack_24 + iVar2;
			MISSILE_SetTotalFrames(pDVar3, iVar5);
			MISSILE_SetCurrentFrame(pDVar3, iVar5);
			MISSILE_SetActivateFrame(pDVar3, iVar2 - iStack_28 * iStack_24);
			pDVar3->dwFlagEx = pDVar3->dwFlagEx | 0x40000;
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC43B0
uint32_t __fastcall sub_6FAC43B0(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SkillStrc* pSkill;
	int iVar1;
	int iVar2;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		pSkill = UNITS_GetUsedSkill(pUnit);
		if (pSkill == nullptr)
		{
			return 0;
		}
		iVar1 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x13c), a2, a3);
		if (iVar1 < 1)
		{
			iVar1 = 1;
		}
		iVar2 = sub_6FAABF80();
		SKILLS_SetParam1(pSkill, iVar2 + iVar1);
		iVar1 = STATES_CheckState(pUnit, 0xc);
		if (iVar1 == 0)
		{
			STATES_ToggleState(pUnit, 0xc, 1);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC4450
uint32_t __fastcall sub_6FAC4450(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SkillStrc* pSkill;
	uint32_t uVar1;
	uint32_t uVar2;
	uint32_t* puVar3;
	int iVar4;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar4 == 0))
	{
		return 0;
	}
	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	uVar1 = SKILLS_GetParam1(pSkill);
	uVar2 = sub_6FAABF80();
	if (uVar1 < uVar2)
	{
		STATES_ToggleState(pUnit, 0xc, 0);
		return 0;
	}
	puVar3 = sub_6FACA1D0(pUnit, a2, a3);
	if (puVar3 == nullptr)
	{
		return 0;
	}
	sub_6FB5FB10((int)puVar3);
	iVar4 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x114), a2, a3);
	sub_6FB5FC80((int)puVar3, 0, 0, iVar4);
	sub_6FB60180((int)puVar3, 1);
	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags & 0xffffffbf;
	}
	return 1;
}

//D2Client.0x6FAC4540
uint32_t __fastcall sub_6FAC4540(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	D2SkillStrc* pSkill;
	D2UnitStrc* pDVar2;
	int iVar3;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	pDVar2 = sub_6FB296A0((int)pUnit);
	if (pDVar2 == nullptr)
	{
		return 0;
	}
	uVar1 = pDVar2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar3 = pDVar2->pDynamicPath->dwClientCoordY;
	}
	else if (pDVar2->pDynamicPath == nullptr)
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = PATH_GetXPosition(pDVar2->pDynamicPath);
	}
	SKILLS_SetParam1(pSkill, iVar3);
	uVar1 = pDVar2->dwUnitType;
	if ((uVar1 != 2) && (((int)uVar1 < 4 || (5 < (int)uVar1))))
	{
		if (pDVar2->pDynamicPath != nullptr)
		{
			iVar3 = PATH_GetYPosition(pDVar2->pDynamicPath);
			SKILLS_SetParam2(pSkill, iVar3);
			return 1;
		}
		SKILLS_SetParam2(pSkill, 0);
		return 1;
	}
	SKILLS_SetParam2(pSkill, (int)(*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord));
	return 1;
}

//D2Client.0x6FAC4600
uint32_t __fastcall sub_6FAC4600(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	int iVar1;
	D2UnitStrc** ppDVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;

	if ((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	        (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar5 != 0)) &&
	    (pSkill = UNITS_GetUsedSkill(pUnit), pSkill != nullptr))
	{
		iVar1 = SKILLS_GetParam1(pSkill);
		ppDVar2 = (D2UnitStrc**)SKILLS_GetParam2(pSkill);
		if ((iVar1 != 0) && (ppDVar2 != nullptr))
		{
			iVar4 = (int)*(short*)(iVar5 + 0xea);
			if ((-1 < iVar4) && (iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
			{
				pDVar3 = sub_6FB3EAF0((int)pUnit, iVar4, iVar1, ppDVar2, a2, a3);
				if (pDVar3 == nullptr)
				{
					return 0;
				}
				if (0 < *(short*)(iVar5 + 0x10e))
				{
					sub_6FB55820((int)*(short*)(iVar5 + 0x10e), pDVar3, 0.0, 0.0, 0);
				}
			}
			iVar5 = (int)*(short*)(iVar5 + 0xec);
			if ((-1 < iVar5) && (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
			{
				sub_6FB3EAF0((int)pUnit, iVar5, iVar1, ppDVar2, a2, a3);
			}
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC4710
uint32_t __fastcall sub_6FAC4710(D2UnitStrc* pUnit2, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	D2SkillStrc* pSkill;
	D2UnitStrc* pUnit;
	int iVar2;
	int32_t nPar2;

	pSkill = UNITS_GetUsedSkill(pUnit2);
	if (pSkill != nullptr)
	{
		pUnit = sub_6FB296A0((int)pUnit2);
		if (pUnit != nullptr)
		{
			iVar2 = D2COMMON_11018(pUnit);
			if (iVar2 != 0)
			{
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar2 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar2 = 0;
				}
				else
				{
					iVar2 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				SKILLS_SetParam1(pSkill, iVar2);
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					nPar2 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&nPar2 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&nPar2 + 2)) = 0;
				}
				else
				{
					nPar2 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				SKILLS_SetParam2(pSkill, (int)nPar2);
				SKILLS_SetParam3(pSkill, pUnit->dwClassId);
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC47C0
uint32_t __fastcall sub_6FAC47C0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	int nX;
	D2UnitStrc** nY;
	int iVar1;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		pSkill = UNITS_GetUsedSkill(pUnit);
		if (pSkill != nullptr)
		{
			nX = SKILLS_GetParam1(pSkill);
			nY = (D2UnitStrc**)SKILLS_GetParam2(pSkill);
			if ((nX != 0) && (nY != nullptr))
			{
				D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, nX, (int)nY);
				iVar1 = (int)*(short*)(iVar1 + 0xea);
				if ((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
				{
					sub_6FB3EAF0((int)pUnit, iVar1, nX, nY, a2, a3);
				}
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC4870
uint32_t __fastcall sub_6FAC4870(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pMountUnit;

	pMountUnit = sub_6FB26AD0((int)pUnit);
	if (pMountUnit == nullptr)
	{
		return 0;
	}
	D2Common_10235_PATH_UpdateRiderPath(pUnit, pMountUnit);
	return 1;
}
