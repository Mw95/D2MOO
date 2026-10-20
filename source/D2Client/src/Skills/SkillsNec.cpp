#include "Skills/SkillsNec.h"

#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Scroll.h"
#include "Quest/QuestsFX.h"
#include "Skills/SkillsAma.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"

//D2Client.0x6FB6EDC0
uint8_t byte_6FB6EDC0[32] = {0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1};
//D2Client.0x6FB6EDE0
uint8_t byte_6FB6EDE0[32] = {2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 1};

//D2Client.0x6FAC8C80
bool __fastcall sub_6FAC8C80(int a1, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	D2ActiveRoomStrc* pDVar3;

	pDVar1 = sub_6FB296A0(a1);
	if (pDVar1 == nullptr)
	{
		return false;
	}
	if (pDVar1->dwUnitType != 4)
	{
		return false;
	}
	iVar2 = ITEMS_IsMetalItem(pDVar1->dwClassId);
	if (iVar2 == 0)
	{
		return false;
	}
	if (pDVar1->dwAnimMode != 3)
	{
		return false;
	}
	iVar2 = ITEMS_CheckItemFlag(pDVar1, 0x10, __LINE__, __FILE__);
	if (iVar2 == 0)
	{
		return false;
	}
	pDVar3 = UNITS_GetRoom(pDVar1);
	if (pDVar3 == nullptr)
	{
		return false;
	}
	pDVar1 = STATLIST_GetOwner(pDVar1, nullptr);
	return (bool)('\x01' - (pDVar1 != nullptr));
}

//D2Client.0x6FAC8D00
bool __fastcall sub_6FAC8D00(uint32_t a1, int a2, uint32_t a3)
{
	char cVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t auStack_5c[2];
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar5 != 0))
	{
		pDVar3 = sub_6FB296A0(a1);
		if ((((pDVar3 != nullptr) && (pDVar3->dwUnitType == 1)) &&
		        ((iVar4 = pDVar3->dwClassId, -1 < iVar4 &&
		                                         ((iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar4 < *(int*)(iVar2 + 0xa80) &&
		                                                                                           (iVar4 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar4 * 0x1a8), -1 < iVar4)))))) &&
		    ((iVar4 < *(int*)(iVar2 + 0xa98) &&
		        ((iVar4 = *(int*)(iVar2 + 0xa90) + iVar4 * 0x134, iVar4 != 0 &&
		                                                              (((uint32_t) * (uint8_t*)(iVar4 + 5) & *(uint32_t*)((uint8_t*)&gdwBitMasks)) != 0))))))
		{
			iVar4 = D2COMMON_11017_CheckUnitIfConsumeable(pDVar3, 0);
			if (iVar4 != 0)
			{
				iVar4 = sub_6FB44820((int*)pDVar3);
				if (((((iVar4 != 0) && (iVar4 = pDVar3->dwClassId, -1 < iVar4)) &&
				         (iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar4 < *(int*)(iVar2 + 0xa80))) &&
				        ((iVar4 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar4 * 0x1a8), -1 < iVar4 &&
				                                                                                     (iVar4 < *(int*)(iVar2 + 0xa98))))) &&
				    (iVar4 = *(int*)(iVar2 + 0xa90) + iVar4 * 0x134, iVar4 != 0))
				{
					iStack_4c = (int)*(short*)(iVar5 + 0xea);
					cVar1 = *(char*)(iVar4 + 0xc);
					if (cVar1 == '\x01')
					{
						iStack_4c = (int)*(short*)(iVar5 + 0xec);
					}
					else if (cVar1 == '\x03')
					{
						iStack_4c = (int)*(short*)(iVar5 + 0xee);
					}
					if ((-1 < iStack_4c) && (iStack_4c < *(int*)(iVar2 + 0xb6c)))
					{
						puVar6 = auStack_5c;
						for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
						{
							*puVar6 = 0;
							puVar6 = puVar6 + 1;
						}
						uStack_2c = a3;
						auStack_5c[0] = 0x2000;
						auStack_5c[1] = a1;
						pDStack_54 = pDVar3;
						iStack_30 = a2;
						pDVar3 = sub_6FB3E070(auStack_5c);
						return pDVar3 != nullptr;
					}
				}
			}
		}
	}
	return false;
}

//D2Client.0x6FAC8EE0
uint32_t __fastcall sub_6FAC8EE0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	uint64_t DVar5;
	uint64_t uVar6;
	uint8_t bVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	uint32_t uVar10;
	int32_t DVar11;
	int local_10;

	if ((((-1 < a2) && (iVar9 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar9 + 0xba0))) && (iVar1 = *(int*)(iVar9 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	    ((local_10 = (int)*(short*)(iVar1 + 0xea), -1 < local_10 &&
	                                                   (local_10 < *(int*)(iVar9 + 0xb6c)))))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		pDVar8 = sub_6FB296A0((int)pUnit);
		if ((pDVar8 != nullptr) && (pUnit->pDynamicPath != nullptr))
		{
			iVar9 = PATH_GetVelocity(pUnit->pDynamicPath);
			if (iVar9 == 0)
			{
				DVar5 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar5;
				uVar10 = (*(uint32_t*)((uint8_t*)&DVar5 + 0)) & 7;
			}
			else
			{
				bVar7 = UNITS_GetDirection(pUnit);
				uVar10 = (uint32_t)(bVar7 >> 3);
			}
			DVar5 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar5;
			uVar2 = pUnit->dwUnitType;
			uVar10 = (int)(((uint64_t)DVar5 & 0xffffffff) % 3) + -1 + (uVar10 + 4 & 0x80000007) & 7;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iVar9 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar9 = 0;
			}
			else
			{
				iVar9 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			iVar3 = *(int*)(byte_6FB6EDC0 + uVar10 * 4);
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				DVar11 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar11 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar11 + 2)) = 0;
			}
			else
			{
				DVar11 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iVar4 = *(int*)(byte_6FB6EDE0 + uVar10 * 4);
			uVar10 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x114), a2, a3);
			if (0 < (int)uVar10)
			{
				uVar2 = (pUnit->pSeed).nLowSeed;
				uVar6 = (uint64_t)(pUnit->pSeed).nHighSeed;
				if ((uVar10 & uVar10 - 1) == 0)
				{
					DVar5 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar6);
					(*(uint64_t*)&pUnit->pSeed) = DVar5;
					uVar10 = uVar10 - 1 & (*(uint32_t*)((uint8_t*)&DVar5 + 0));
				}
				else
				{
					DVar5 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar6);
					(*(uint64_t*)&pUnit->pSeed) = DVar5;
					uVar10 = (uint32_t)(((uint64_t)DVar5 & 0xffffffff) % (uint64_t)uVar10);
				}
				local_10 = local_10 + uVar10;
			}
			sub_6FB3EB50(pUnit, local_10, iVar3 + iVar9, (D2UnitStrc*)(iVar4 + (int)DVar11), a2,
			    a3);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC90E0
uint32_t __fastcall sub_6FAC90E0(D2UnitStrc* pUnit2, int a2, uint32_t a3)
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	int iVar2;
	D2UnitStrc* pUnit;
	int* piVar3;
	int local_64;
	int local_60[2];
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int local_4c;
	int local_40;
	int local_3c;
	int local_30;
	uint32_t local_2c;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0))
	{
		iVar1 = sub_6FABF670(pUnit2, a2);
		if ((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit2 != nullptr)
			{
				pUnit2->dwFlags = pUnit2->dwFlags | 0x40;
			}
			iVar2 = sub_6FABA950(pUnit2, &local_64, local_60);
			if (iVar2 != 0)
			{
				piVar3 = local_60;
				for (iVar2 = 0x17; piVar3 = piVar3 + 1, iVar2 != 0; iVar2 = iVar2 + -1)
				{
					*piVar3 = 0;
				}
				local_3c = local_60[0];
				local_60[1] = 0x20;
				local_40 = local_64;
				local_2c = a3;
				local_58 = pUnit2;
				local_54 = pUnit2;
				local_4c = iVar1;
				local_30 = a2;
				pUnit = sub_6FB3E070((uint32_t*)(local_60 + 1));
				if ((pUnit != nullptr) &&
				    (pDynamicPath = pUnit->pDynamicPath, pDynamicPath != nullptr))
				{
					PATH_SetType(pDynamicPath, 0xe);
					D2Common_10142(pDynamicPath, pUnit, 0);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC91F0
uint32_t __fastcall sub_6FAC91F0(int a1, int a2, uint32_t a3)
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pMissile;
	int iVar4;
	uint32_t* puVar5;
	uint32_t local_5c[4];
	int iStack_4c;
	int local_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0)) &&
	    ((iVar2 = sub_6FABF670((D2UnitStrc*)(a1), a2), -1 < iVar2 &&
	                                                       (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))))
	{
		if (a1 != 0)
		{
			*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x40;
		}
		pDVar3 = sub_6FB296A0(a1);
		if (pDVar3 != nullptr)
		{
			puVar5 = local_5c;
			for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar5 = 0;
				puVar5 = puVar5 + 1;
			}
			local_5c[0] = 1;
			uVar1 = pDVar3->dwUnitType;
			local_5c[1] = a1;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				local_48 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				local_48 = 0;
			}
			else
			{
				local_48 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar1 = pDVar3->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DStack_44 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
			}
			else
			{
				DStack_44 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
			uStack_2c = a3;
			iStack_4c = iVar2;
			iStack_30 = a2;
			pMissile = sub_6FB3E070(local_5c);
			if (pMissile != nullptr)
			{
				MISSILE_SetTargetX(pMissile, pDVar3->dwUnitType);
				MISSILE_SetTargetY(pMissile, pDVar3->dwUnitId);
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC9350
uint32_t __fastcall sub_6FAC9350(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SeedStrc* pDVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	uint64_t uVar4;
	uint32_t uVar5;
	D2ActiveRoomStrc* pRoom;
	int iVar6;
	int iVar7;
	int iVar8;
	uint32_t uVar9;
	D2UnitStrc* pDVar10;
	uint32_t* puVar11;
	int iStack_78;
	int iStack_74;
	int32_t DStack_70;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	int iStack_2c;

	pRoom = UNITS_GetRoom(pUnit);
	if ((((((pRoom != nullptr) && (iVar6 = DUNGEON_IsRoomInTown(pRoom), iVar6 == 0)) && (-1 < a2)) &&
	         ((a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) &&
	             (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar6 != 0)))) &&
	        ((iVar7 = sub_6FABF670(pUnit, a2), -1 < iVar7 &&
	                                               ((iVar7 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) &&
	                                                   (iVar8 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar6 + 100), a2, a3),
	                                                       0 < iVar8)))))) &&
	    (iVar6 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar6 + 100), a2, 1), 0 < iVar6))
	{
		uVar5 = iVar8 * 2;
		uVar2 = uVar5 + 1;
		pDVar1 = &pUnit->pSeed;
		DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
		*(uint64_t*)pDVar1 = DVar3;
		iStack_78 = ((iVar8 * iVar8) / (iVar6 * iVar6)) /
		            ((int)(((uint64_t)DVar3 & 0xffffffff) % 0x12) + 1);
		uVar9 = pUnit->dwUnitType;
		if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
		{
			iStack_74 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_74 = 0;
		}
		else
		{
			iStack_74 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar9 = pUnit->dwUnitType;
		if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
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
		puVar11 = &uStack_5c;
		for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		uStack_5c = 0x2001;
		iStack_2c = a3;
		pDStack_58 = pUnit;
		iStack_4c = iVar7;
		iStack_30 = a2;
		if (0 < iStack_78)
		{
			do
			{
				if ((int)uVar2 < 1)
				{
					uVar9 = 0;
				}
				else if ((uVar2 & uVar5) == 0)
				{
					uVar9 = sub_6FAA88D0(&pDVar1->nLowSeed);
					uVar9 = uVar9 & uVar5;
				}
				else
				{
					DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
					*(uint64_t*)pDVar1 = DVar3;
					uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar2);
				}
				iVar6 = uVar9 - iVar8;
				if ((int)uVar2 < 1)
				{
					uVar9 = 0;
				}
				else
				{
					uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
					if ((uVar2 & uVar5) == 0)
					{
						DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + uVar4);
						*(uint64_t*)pDVar1 = DVar3;
						uVar9 = uVar5 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
					}
					else
					{
						DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + uVar4);
						*(uint64_t*)pDVar1 = DVar3;
						uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar2);
					}
				}
				iVar7 = uVar9 - iVar8;
				if (iVar7 * iVar7 + iVar6 * iVar6 < iVar8 * iVar8)
				{
					iStack_48 = iStack_74 + 2 + iVar6;
					iStack_44 = (int)DStack_70 + 2 + iVar7;
					pDVar10 = sub_6FB3E070(&uStack_5c);
					if (pDVar10 != nullptr)
					{
						DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 +
						                   (uint64_t)(pUnit->pSeed).nHighSeed);
						*(uint64_t*)pDVar1 = DVar3;
						PATH_SetDirection(pDVar10->pDynamicPath, (uint8_t)(*(uint32_t*)((uint8_t*)&DVar3 + 0)) & 0x3f);
					}
				}
				iStack_78 = iStack_78 + -1;
			} while (iStack_78 != 0);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC9620
void __fastcall sub_6FAC9620(D2UnitStrc* pUnit, uint32_t a2, int a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int nAngle;
	int* pXAdjust;
	int* pYAdjust;
	int bOrder;
	int iStack_40;
	int iStack_3c;
	int iStack_38;
	int iStack_34;
	int iStack_30;
	int iStack_2c;
	int iStack_28;
	int iStack_24;
	D2SkillStrc* pDStack_20;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	uint32_t local_10;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	local_10 = a2;
	pDStack_20 = UNITS_GetUsedSkill(pUnit);
	if (pDStack_20 != nullptr)
	{
		iStack_18 = UNITS_GetClientCoordX(pUnit);
		iStack_14 = UNITS_GetClientCoordY(pUnit);
		iStack_24 = 0;
		iStack_34 = 0;
		PATH_GetClientCoordsVelocity(pUnit, &iStack_24, &iStack_34);
		if (a3 == 0)
		{
			if (-1 < iStack_34)
			{
				return;
			}
		}
		else if (iStack_34 < 0)
		{
			return;
		}
		iVar4 = iStack_24;
		if (iStack_24 < 0)
		{
			iVar4 = -iStack_24;
		}
		iVar1 = iStack_34;
		if (iStack_34 < 0)
		{
			iVar1 = -iStack_34;
		}
		if (iVar1 < iVar4)
		{
			iVar1 = iVar1 + iVar4 * 2;
		}
		else
		{
			iVar1 = iVar4 + iVar1 * 2;
		}
		iVar1 = iVar1 / 2;
		if (iVar1 == 0)
		{
			iVar1 = 1;
		}
		iVar2 = (iStack_24 * 0xf) / iVar1;
		iVar1 = (iStack_34 * 0xf) / iVar1;
		iStack_1c = D2GFX_CheckPerspective();
		iVar4 = pUnit->nSeqCurrentFramePrecise >> 8;
		iStack_3c = iVar4;
		iStack_4 = iVar4;
		pDStack_20 = (D2SkillStrc*)SKILLS_GetParam3(pDStack_20);
		if (0 < (int)pDStack_20)
		{
			iStack_8 = -iVar1;
			iStack_c = -iVar2;
			iStack_28 = (int)pDStack_20 * iVar1;
			iVar5 = (int)pDStack_20 * iVar2;
			iStack_30 = iVar2;
			iStack_2c = iVar1;
			do
			{
				iStack_40 = 0;
				iStack_38 = 0;
				iVar4 = iStack_3c + -1;
				if (iStack_3c + -1 < 0)
				{
					iVar4 = iStack_3c + 7;
				}
				iStack_3c = iVar4;
				pUnit->nSeqCurrentFramePrecise = iStack_3c << 8;
				iVar4 = iStack_18;
				iVar3 = iStack_14;
				if (iStack_1c != 0)
				{
					bOrder = 0;
					pYAdjust = &iStack_38;
					pXAdjust = &iStack_40;
					nAngle = 0x60;
					iVar4 = UNITS_GetPrecisionY(pUnit);
					iVar3 = UNITS_GetPrecisionX(pUnit);
					SCALE_ScalePerspectivePosition(iVar3, iVar4, nAngle, pXAdjust, pYAdjust, bOrder);
					iVar4 = sub_6FAB5890();
					iStack_40 = iStack_40 + iVar4;
					iVar3 = sub_6FAB58A0();
					iVar4 = iStack_40;
					iVar3 = iStack_38 + iVar3;
				}
				iStack_38 = iStack_2c;
				iStack_40 = iStack_30;
				if (a3 != 0)
				{
					iStack_38 = iStack_28;
					iStack_40 = iVar5;
				}
				iStack_40 = iVar4 - iStack_40;
				iStack_38 = iVar3 - iStack_38;
				sub_6FB5A720(pUnit, (DrawMode)(local_10), iStack_40, iStack_38, 1, 0);
				iStack_30 = iStack_30 + iVar2;
				iStack_2c = iStack_2c + iVar1;
				iVar5 = iVar5 + iStack_c;
				iStack_28 = iStack_28 + iStack_8;
				pDStack_20 = (D2SkillStrc*)((int)pDStack_20 + -1);
				iVar4 = iStack_4;
			} while (pDStack_20 != nullptr);
		}
		pUnit->nSeqCurrentFramePrecise = iVar4 << 8;
	}
}
