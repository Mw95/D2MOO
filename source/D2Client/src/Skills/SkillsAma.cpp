#include "Skills/SkillsAma.h"

#include "Engine/Gfx.h"
#include "Engine/Particle.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB6E578
uint32_t dword_6FB6E578[64] = {0x1E, 0x1D, 0x1D, 0x1C, 0x1B, 0x1A, 0x18, 0x17, 0x15, 0x13, 0x10, 0xE, 0xB, 8, 5, 2, 0, 0xFFFFFFFE, 0xFFFFFFFB, 0xFFFFFFF8, 0xFFFFFFF5, 0xFFFFFFF2, 0xFFFFFFF0, 0xFFFFFFED, 0xFFFFFFEB, 0xFFFFFFE9, 0xFFFFFFE8, 0xFFFFFFE6, 0xFFFFFFE5, 0xFFFFFFE4, 0xFFFFFFE3, 0xFFFFFFE3, 0xFFFFFFE2, 0xFFFFFFE3, 0xFFFFFFE3, 0xFFFFFFE4, 0xFFFFFFE5, 0xFFFFFFE6, 0xFFFFFFE8, 0xFFFFFFE9, 0xFFFFFFEB, 0xFFFFFFED, 0xFFFFFFF0, 0xFFFFFFF2, 0xFFFFFFF5, 0xFFFFFFF8, 0xFFFFFFFB, 0xFFFFFFFE, 0, 2, 5, 8, 0xB, 0xE, 0x10, 0x13, 0x15, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1D};
//D2Client.0x6FB6E678
uint32_t dword_6FB6E678[65] = {0, 2, 5, 8, 0xB, 0xE, 0x10, 0x13, 0x15, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1D, 0x1E, 0x1D, 0x1D, 0x1C, 0x1B, 0x1A, 0x18, 0x17, 0x15, 0x13, 0x10, 0xE, 0xB, 8, 5, 2, 0, 0xFFFFFFFE, 0xFFFFFFFB, 0xFFFFFFF8, 0xFFFFFFF5, 0xFFFFFFF2, 0xFFFFFFF0, 0xFFFFFFED, 0xFFFFFFEB, 0xFFFFFFE9, 0xFFFFFFE8, 0xFFFFFFE6, 0xFFFFFFE5, 0xFFFFFFE4, 0xFFFFFFE3, 0xFFFFFFE3, 0xFFFFFFE2, 0xFFFFFFE3, 0xFFFFFFE3, 0xFFFFFFE4, 0xFFFFFFE5, 0xFFFFFFE6, 0xFFFFFFE8, 0xFFFFFFE9, 0xFFFFFFEB, 0xFFFFFFED, 0xFFFFFFF0, 0xFFFFFFF2, 0xFFFFFFF5, 0xFFFFFFF8, 0xFFFFFFFB, 0xFFFFFFFE, 0x40};
//D2Client.0x6FB6E77C
uint8_t byte_6FB6E77C = 2;
//D2Client.0x6FB6E79C
uint8_t byte_6FB6E79C;
//D2Client.0x6FB6E7C0
uint32_t dword_6FB6E7C0[64] = {0x1E, 0x1D, 0x1D, 0x1C, 0x1B, 0x1A, 0x18, 0x17, 0x15, 0x13, 0x10, 0xE, 0xB, 8, 5, 2, 0, 0xFFFFFFFE, 0xFFFFFFFB, 0xFFFFFFF8, 0xFFFFFFF5, 0xFFFFFFF2, 0xFFFFFFF0, 0xFFFFFFED, 0xFFFFFFEB, 0xFFFFFFE9, 0xFFFFFFE8, 0xFFFFFFE6, 0xFFFFFFE5, 0xFFFFFFE4, 0xFFFFFFE3, 0xFFFFFFE3, 0xFFFFFFE2, 0xFFFFFFE3, 0xFFFFFFE3, 0xFFFFFFE4, 0xFFFFFFE5, 0xFFFFFFE6, 0xFFFFFFE8, 0xFFFFFFE9, 0xFFFFFFEB, 0xFFFFFFED, 0xFFFFFFF0, 0xFFFFFFF2, 0xFFFFFFF5, 0xFFFFFFF8, 0xFFFFFFFB, 0xFFFFFFFE, 0, 2, 5, 8, 0xB, 0xE, 0x10, 0x13, 0x15, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1D};
//D2Client.0x6FB6E8C0
uint32_t dword_6FB6E8C0[65] = {0, 2, 5, 8, 0xB, 0xE, 0x10, 0x13, 0x15, 0x17, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1D, 0x1E, 0x1D, 0x1D, 0x1C, 0x1B, 0x1A, 0x18, 0x17, 0x15, 0x13, 0x10, 0xE, 0xB, 8, 5, 2, 0, 0xFFFFFFFE, 0xFFFFFFFB, 0xFFFFFFF8, 0xFFFFFFF5, 0xFFFFFFF2, 0xFFFFFFF0, 0xFFFFFFED, 0xFFFFFFEB, 0xFFFFFFE9, 0xFFFFFFE8, 0xFFFFFFE6, 0xFFFFFFE5, 0xFFFFFFE4, 0xFFFFFFE3, 0xFFFFFFE3, 0xFFFFFFE2, 0xFFFFFFE3, 0xFFFFFFE3, 0xFFFFFFE4, 0xFFFFFFE5, 0xFFFFFFE6, 0xFFFFFFE8, 0xFFFFFFE9, 0xFFFFFFEB, 0xFFFFFFED, 0xFFFFFFF0, 0xFFFFFFF2, 0xFFFFFFF5, 0xFFFFFFF8, 0xFFFFFFFB, 0xFFFFFFFE, 0x40};
//D2Client.0x6FB778BC
uint32_t dword_6FB778BC = 0xF;
//D2Client.0x6FB778C0
uint32_t dword_6FB778C0 = 2;

//D2Client.0x6FABF0C0
uint32_t __fastcall sub_6FABF0C0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t nY;
	float fVar5;
	float fVar6;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c == 0))
	{
		return 0;
	}
	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	uVar1 = SKILLS_GetParam3(pSkill);
	iVar2 = SKILLS_GetParam2(pSkill);
	pDVar3 = sub_6FB269F0(uVar1, iVar2);
	iVar2 = sub_6FABE1F0(pUnit);
	if (pDVar3 != nullptr)
	{
		iVar4 = UNITS_IsInMeleeRange(pUnit, pDVar3, 0);
		if (iVar4 != 0)
			goto LAB_6fabf168;
	}
	pDVar3 = sub_6FABB890(pUnit, 0, 0, iVar2, 0x20003, uVar1, nullptr);
	if (pDVar3 == nullptr)
	{
		return 0;
	}
LAB_6fabf168:
	iVar4 = SKILLS_GetParam1(pSkill);
	SKILLS_SetParam1(pSkill, iVar4 + -1);
	if (0 < iVar4 + -1)
	{
		if (pDVar3 == nullptr)
		{
			uVar1 = 0xffffffff;
		}
		else
		{
			uVar1 = pDVar3->dwUnitId;
		}
		pDVar3 = sub_6FABB890(pUnit, 0, 0, iVar2, 0x20003, uVar1, nullptr);
		if (pDVar3 == nullptr)
		{
			return 0;
		}
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
		iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		if (((iVar2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar2)) ||
		    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar2 == 0))
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = *(int*)(iVar2 + 0x14c);
		}
		sub_6FABDAD0((int)pUnit, iVar2);
		uVar1 = UNITS_GetHitClass(pUnit);
		iVar4 = 0;
		fVar6 = 0.0;
		fVar5 = 0.0;
		iVar2 = sub_6FB4F4D0((int)pUnit, uVar1);
		sub_6FB55820(iVar2, pUnit, fVar5, fVar6, iVar4);
	}
	return 1;
}

//D2Client.0x6FABF2A0
uint32_t __fastcall sub_6FABF2A0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	uint32_t uVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int32_t DVar6;
	int iVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	uint32_t* puVar10;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int32_t DStack_3c;
	int iStack_30;
	int iStack_2c;

	if ((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)))
	{
		iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c;
		if (iVar9 != 0)
		{
			iVar3 = sub_6FABF670(pUnit, a2);
			if ((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
			{
				pDVar4 = sub_6FB296A0((int)pUnit);
				if (pDVar4 != nullptr)
				{
					iVar5 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 0x138), a2, a3);
					uVar1 = pDVar4->dwUnitId;
					uVar2 = pDVar4->dwUnitType;
					if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
					{
						DVar6 = (*(int32_t*)&pDVar4->pDynamicPath->tTargetCoord);
					}
					else if (pDVar4->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
					}
					else
					{
						DVar6 = (int32_t)PATH_GetYPosition(pDVar4->pDynamicPath);
					}
					uVar2 = pDVar4->dwUnitType;
					if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
					{
						iVar7 = pDVar4->pDynamicPath->dwClientCoordY;
					}
					else if (pDVar4->pDynamicPath == nullptr)
					{
						iVar7 = 0;
					}
					else
					{
						iVar7 = PATH_GetXPosition(pDVar4->pDynamicPath);
					}
					pDVar8 = sub_6FABB890(pUnit, iVar7, DVar6, iVar5, 3, uVar1, nullptr);
					if (pDVar8 != nullptr)
					{
						iVar9 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 0x13c), a2, a3);
						puVar10 = &uStack_5c;
						for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
						{
							*puVar10 = 0;
							puVar10 = puVar10 + 1;
						}
						uStack_5c = 0x20;
						iStack_2c = a3;
						uVar1 = pDVar8->dwUnitType;
						pDStack_58 = pUnit;
						pDStack_54 = pDVar4;
						iStack_4c = iVar3;
						iStack_30 = a2;
						if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
						{
							iStack_40 = pDVar8->pDynamicPath->dwClientCoordY;
						}
						else if (pDVar8->pDynamicPath == nullptr)
						{
							iStack_40 = 0;
						}
						else
						{
							iStack_40 = PATH_GetXPosition(pDVar8->pDynamicPath);
						}
						uVar1 = pDVar8->dwUnitType;
						if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
						{
							DStack_3c = (*(int32_t*)&pDVar8->pDynamicPath->tTargetCoord);
						}
						else if (pDVar8->pDynamicPath == nullptr)
						{
							(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
							(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
						}
						else
						{
							DStack_3c = (int32_t)PATH_GetYPosition(pDVar8->pDynamicPath);
						}
						pDVar4 = sub_6FB3E070(&uStack_5c);
						if (pDVar4 != nullptr)
						{
							MISSILE_SetTargetX(pDVar4, iVar9);
						}
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FABF4B0
bool __fastcall sub_6FABF4B0(D2UnitStrc* pUnit2, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;

	pUnit = sub_6FB296A0((int)pUnit2);
	if (pUnit != nullptr)
	{
		pDVar1 = UNITS_GetRoom(pUnit2);
		iVar2 = DUNGEON_IsRoomInTown(pDVar1);
		if (iVar2 == 0)
		{
			pDVar1 = UNITS_GetRoom(pUnit);
			iVar2 = DUNGEON_IsRoomInTown(pDVar1);
			if (((iVar2 == 0) && (-1 < (int)pUnit->dwUnitType)) && ((int)pUnit->dwUnitType < 2))
			{
				uVar3 = sub_6FB29D80(pUnit2, pUnit);
				return uVar3 != 0;
			}
		}
	}
	return false;
}

//D2Client.0x6FABF510
uint32_t __fastcall sub_6FABF510(D2UnitStrc* pUnit2, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;

	pUnit = sub_6FB296A0((int)pUnit2);
	if (pUnit != nullptr)
	{
		pDVar1 = UNITS_GetRoom(pUnit2);
		iVar2 = DUNGEON_IsRoomInTown(pDVar1);
		if (iVar2 == 0)
		{
			pDVar1 = UNITS_GetRoom(pUnit);
			iVar2 = DUNGEON_IsRoomInTown(pDVar1);
			if (((iVar2 == 0) && (-1 < (int)pUnit->dwUnitType)) && ((int)pUnit->dwUnitType < 2))
			{
				uVar3 = sub_6FB29D80(pUnit2, pUnit);
				if (uVar3 != 0)
				{
					if (pUnit2 != nullptr)
					{
						pUnit2->dwFlags = pUnit2->dwFlags | 0x40;
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FABF580
uint32_t __fastcall sub_6FABF580(D2UnitStrc* pUnit, int a2, int a3)
{
	D2UnitStrc* pDVar1;
	D2SkillStrc* pSkill;
	int iVar2;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 == 0))
	{
		return 0;
	}
	pDVar1 = sub_6FB296A0((int)pUnit);
	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	if (pDVar1 == nullptr)
	{
		SKILLS_SetParam1(pSkill, 0);
		return 1;
	}
	iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 0x138), a2, a3);
	SKILLS_SetParam1(pSkill, iVar2);
	return 1;
}

//D2Client.0x6FABF620
uint32_t __fastcall sub_6FABF620(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	D2UnitStrc* pDVar1;
	int iVar2;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	pDVar1 = sub_6FB296A0((int)pUnit);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	iVar2 = SKILLS_GetParam1(pSkill);
	if (0 < iVar2 + -1)
	{
		SKILLS_SetParam1(pSkill, iVar2 + -1);
		sub_6FABDAD0((int)pUnit, 100);
	}
	return 1;
}

//D2Client.0x6FABF670
int __fastcall sub_6FABF670(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	short sVar2;
	D2StatListStrc* pStatList;
	int iVar3;

	if (((-1 < a2) && (iVar3 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar3 + 0xba0))) && (iVar1 = *(int*)(iVar3 + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		if (((((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar1 + 4)) != 0) &&
		        (sVar2 = *(short*)(iVar1 + 0x80), -1 < sVar2)) &&
		    (((int)sVar2 < *(int*)(iVar3 + 0xc4) &&
		        ((-1 < *(short*)(iVar1 + 0x54) && ((int)*(short*)(iVar1 + 0x54) < *(int*)(iVar3 + 0xbd4)))))))
		{
			pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, (int)sVar2);
			if (pStatList != nullptr)
			{
				iVar3 = STATLIST_GetStatValue(pStatList, (int)*(short*)(iVar1 + 0x54), 0);
				if (iVar3 < 2)
				{
					return (int)*(short*)(iVar1 + 0xea);
				}
				if (2 < iVar3)
				{
					iVar3 = 3;
				}
				return (int)*(short*)(iVar1 + 0xe8 + iVar3 * 2);
			}
		}
		return (int)*(short*)(iVar1 + 0xea);
	}
	return -1;
}

//D2Client.0x6FABF730
uint32_t __fastcall sub_6FABF730(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	short sVar2;
	D2StatListStrc* pStatList;
	int iVar3;

	if (((a2 < 0) || (iVar3 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar3 + 0xba0) <= a2)) || (iVar1 = *(int*)(iVar3 + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		return 0;
	}
	if (((((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar1 + 4)) != 0) &&
	        (sVar2 = *(short*)(iVar1 + 0x80), -1 < sVar2)) &&
	    ((int)sVar2 < *(int*)(iVar3 + 0xc4)))
	{
		if ((*(short*)(iVar1 + 0x54) < 0) || (*(int*)(iVar3 + 0xbd4) <= (int)*(short*)(iVar1 + 0x54)))
		{
			iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x38), a2, a3);
			return iVar3;
		}
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, (int)sVar2);
		if (pStatList == nullptr)
		{
			iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x38), a2, a3);
			return iVar3;
		}
		iVar3 = STATLIST_GetStatValue(pStatList, (int)*(short*)(iVar1 + 0x54), 0);
		if (iVar3 < 2)
		{
			iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x38), a2, a3);
			return iVar3;
		}
		if (2 < iVar3)
		{
			iVar3 = 3;
		}
		iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x34 + iVar3 * 4), a2, a3);
		return iVar3;
	}
	iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x38), a2, a3);
	return iVar3;
}

//D2Client.0x6FABF850
uint32_t __fastcall sub_6FABF850(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	int iVar3;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar3 == 0))
	{
		return 0;
	}
	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x40;
	}
	iVar1 = sub_6FABF670(pUnit, a2);
	if (iVar1 < 0)
	{
		return 0;
	}
	iVar2 = sub_6FABF730(pUnit, a2, a3);
	if (iVar2 < 1)
	{
		return 0;
	}
	iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 100), a2, a3);
	sub_6FABDB00(pUnit, iVar1, iVar2, iVar3, a2, a3);
	return 1;
}

//D2Client.0x6FABF910
bool __fastcall sub_6FABF910(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	short sVar2;
	int iVar3;

	if ((((-1 < a2) && (iVar3 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar3 + 0xba0))) && (iVar1 = *(int*)(iVar3 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	    ((sVar2 = *(short*)(iVar1 + 0x80), -1 < sVar2 && ((int)sVar2 < *(int*)(iVar3 + 0xc4)))))
	{
		iVar3 = STATES_CheckState(pUnit, (int)sVar2);
		return (bool)('\x01' - (iVar3 != 0));
	}
	return false;
}

//D2Client.0x6FABF970
uint32_t __fastcall sub_6FABF970(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	short sVar2;
	int iVar3;
	D2StatListStrc* pDVar4;
	uint32_t nUnitType;
	D2SkillStrc* pSkill;
	uint32_t nUnitGUID;
	D2StatListStrc* pStatList;
	void* pfStatRemove;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		return 0;
	}
	iVar3 = STATES_CheckState(pUnit, 0xc);
	if (iVar3 == 0)
	{
		sVar2 = *(short*)(iVar1 + 0x10c);
		if ((0 < sVar2) && ((int)sVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0)))
		{
			sub_6FB5BA70(pUnit, (int)sVar2, 2, 0, 0, 0, 0, 0);
		}
		if (0 < *(short*)(iVar1 + 0x10e))
		{
			sub_6FB55820((int)*(short*)(iVar1 + 0x10e), nullptr, 0.0, 0.0, 0);
		}
	}
	pDVar4 = STATLIST_GetStatListFromUnitAndState(pUnit, 0xc);
	if (pDVar4 == nullptr)
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
		pDVar4 = STATLIST_AllocStatList(nullptr, 2, 0x14, nUnitType, nUnitGUID);
		if (pDVar4 == nullptr)
		{
			return 0;
		}
		pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2);
		if (pSkill == nullptr)
		{
			return 0;
		}
		SKILLS_SetParam1(pSkill, 0);
		D2COMMON_10475_PostStatToStatList(pUnit, pDVar4, 1);
		STATLIST_SetStatRemoveCallback(pStatList, (StatListRemoveCallback)(pfStatRemove));
		STATLIST_SetState(pDVar4, 0xc);
		STATES_ToggleState(pUnit, 0xc, 1);
		return 1;
	}
	UNITS_SetAnimationFrame(pUnit, *(uint8_t*)(iVar1 + 0x16) - 1);
	pUnit->dwFrameCountPrecise = 0x800;
	D2COMMON_10476(pDVar4, 7);
	return 1;
}

//D2Client.0x6FABFAD0
uint32_t __fastcall sub_6FABFAD0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	D2SkillStrc* pSkill;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t* puVar4;
	int iStack_70;
	int iStack_6c;
	int iStack_68;
	D2SkillStrc* pDStack_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (local_60 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, local_60 == 0))
	{
		return 0;
	}
	iVar1 = sub_6FABF670(pUnit, a2);
	if (iVar1 < 0)
	{
		return 0;
	}
	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2);
	if (pSkill != nullptr)
	{
		pDStack_64 = pSkill;
		iStack_68 = sub_6FABF730(pUnit, a2, a3);
		if (iStack_68 < 1)
		{
			return 0;
		}
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags & 0xffffffbf;
		}
		iVar2 = sub_6FABA950(pUnit, &iStack_70, &iStack_6c);
		if (iVar2 != 0)
		{
			iVar2 = SKILLS_GetParam1(pSkill);
			if (iVar2 < 1)
			{
				puVar4 = &uStack_5c;
				for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
				{
					*puVar4 = 0;
					puVar4 = puVar4 + 1;
				}
				uStack_5c = 0x20;
				uStack_2c = a3;
				iStack_40 = iStack_70;
				iStack_3c = iStack_6c;
				pDStack_58 = pUnit;
				pDStack_54 = pUnit;
				iStack_4c = iVar1;
				iStack_30 = a2;
				pDVar3 = sub_6FB3E070(&uStack_5c);
				pSkill = pDStack_64;
				iVar1 = iStack_68;
				if (pDVar3 != nullptr)
				{
					sub_6FB5FC80((int)pDVar3, 0, 0, 0xf);
					pSkill = pDStack_64;
					iVar1 = iStack_68;
				}
			}
			else
			{
				iVar1 = iVar2 + -1;
			}
			SKILLS_SetParam1(pSkill, iVar1);
			iVar1 = STATES_CheckState(pUnit, 0xc);
			if (iVar1 != 0)
			{
				UNITS_SetAnimationFrame(pUnit, *(uint8_t*)(local_60 + 0x16) - 1);
				pUnit->dwFrameCountPrecise = 0x800;
			}
			return 1;
		}
		return 0;
	}
	return 0;
}

//D2Client.0x6FABFC50
uint32_t __fastcall sub_6FABFC50(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		sub_6FABE200(pUnit, *(uint32_t*)(iVar1 + 0x154));
		return 1;
	}
	sub_6FABE200(pUnit, 0);
	return 1;
}

//D2Client.0x6FABFCB0
uint32_t __fastcall sub_6FABFCB0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2UnitStrc* pDVar1;
	int iVar2;

	pDVar1 = sub_6FB296A0((int)pUnit);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0))
	{
		iVar2 = sub_6FABF670(pUnit, a2);
		if (iVar2 < 0)
		{
			return 0;
		}
		sub_6FABAD50(pUnit, iVar2, a2, a3);
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FABFD40
uint32_t __fastcall sub_6FABFD40(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	D2UnitStrc* pMissile;
	int iVar3;
	uint32_t* puVar4;
	int local_68;
	int local_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	int iStack_2c;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		return 0;
	}
	iVar2 = sub_6FABA950(pUnit, &local_68, &local_64);
	if (iVar2 == 0)
	{
		return 0;
	}
	local_60 = (int)*(short*)(iVar1 + 0xea);
	if (local_60 < 0)
	{
		return 0;
	}
	if (*(short*)(iVar1 + 0xec) < 0)
	{
		return 0;
	}
	iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 100), a2, a3);
	puVar4 = &uStack_5c;
	for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar4 = 0;
		puVar4 = puVar4 + 1;
	}
	iStack_44 = local_64;
	uStack_5c = 1;
	iStack_48 = local_68;
	iStack_2c = a3;
	iStack_4c = local_60;
	pDStack_58 = pUnit;
	iStack_30 = a2;
	pMissile = sub_6FB3E070(&uStack_5c);
	if (pMissile != nullptr)
	{
		MISSILE_SetStreamMissile(pMissile, *(uint16_t*)(iVar1 + 0xec));
		MISSILE_SetStreamRange(pMissile, (short)iVar2);
	}
	return 1;
}

//D2Client.0x6FABFE60
uint32_t __fastcall sub_6FABFE60(int a1, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB296A0(a1);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	if ((pDVar1->dwUnitType != 1) && (pDVar1->dwUnitType != 0))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FABFE90
void __fastcall sub_6FABFE90(D2UnitStrc* pUnit, int a2, int a3, int a4, uint32_t a5, int a6, uint32_t a7, int a8)
{
	int iVar1;
	int* piVar2;
	uint64_t DVar3;
	D2ActiveRoomStrc* pRoom;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	D2ActiveRoomStrc* pDVar8;
	int iVar9;
	uint32_t* puVar10;
	int iStack_6c;
	uint64_t local_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	uint32_t uStack_30;
	int iStack_2c;

	SEED_InitLowSeed((D2SeedStrc*)(&local_64), a2);
	iVar9 = a6 * a6;
	puVar10 = &uStack_5c;
	for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		*puVar10 = 0;
		puVar10 = puVar10 + 1;
	}
	uStack_5c = 1;
	uStack_30 = a7;
	iStack_2c = a8;
	iStack_4c = a3;
	pDStack_58 = pUnit;
	pRoom = UNITS_GetRoom(pUnit);
	(*(uint32_t*)((uint8_t*)&DVar3 + 4)) = (*(uint32_t*)((uint8_t*)&local_64 + 4));
	(*(uint32_t*)((uint8_t*)&DVar3 + 0)) = (*(uint32_t*)((uint8_t*)&local_64 + 0));
	iStack_6c = iVar9;
	if (0 < iVar9)
	{
		do
		{
			(*(uint32_t*)((uint8_t*)&local_64 + 4)) = (*(uint32_t*)((uint8_t*)&DVar3 + 4));
			(*(uint32_t*)((uint8_t*)&local_64 + 0)) = (*(uint32_t*)((uint8_t*)&DVar3 + 0));
			uVar7 = a6 * 2;
			if ((int)uVar7 < 1)
			{
				uVar6 = 0;
			}
			else
			{
				if ((uVar7 & uVar7 - 1) == 0)
				{
					DVar3 = (uint64_t)(((uint64_t)DVar3 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&local_64 + 4)));
					uVar6 = uVar7 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
				}
				else
				{
					DVar3 = (uint64_t)(((uint64_t)DVar3 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&local_64 + 4)));
					uVar6 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar7);
				}
				(*(uint32_t*)((uint8_t*)&local_64 + 0)) = (*(uint32_t*)((uint8_t*)&DVar3 + 0));
			}
			(*(uint32_t*)((uint8_t*)&local_64 + 4)) = (*(uint32_t*)((uint8_t*)&DVar3 + 4));
			iVar5 = a6 - uVar6;
			if ((int)uVar7 < 1)
			{
				uVar7 = 0;
			}
			else if ((uVar7 & uVar7 - 1) == 0)
			{
				local_64 = (uint64_t)(((uint64_t)DVar3 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&local_64 + 4)));
				uVar7 = uVar7 - 1 & (*(uint32_t*)((uint8_t*)&local_64 + 0));
			}
			else
			{
				local_64 = (uint64_t)(((uint64_t)DVar3 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&local_64 + 4)));
				uVar7 = (*(uint32_t*)((uint8_t*)&local_64 + 0)) % uVar7;
			}
			iVar4 = a6 - uVar7;
			if (iVar4 * iVar4 + iVar5 * iVar5 <= iVar9)
			{
				iVar5 = iVar5 + a4;
				iVar4 = iVar4 + a5;
				if (pRoom != nullptr)
				{
					iVar1 = (pRoom->tCoords).nSubtileX;
					iStack_48 = iVar5;
					iStack_44 = iVar4;
					if ((((iVar5 < iVar1) || ((pRoom->tCoords).nSubtileWidth + iVar1 <= iVar5)) ||
					        (iVar1 = (pRoom->tCoords).nSubtileY, iVar4 < iVar1)) ||
					    (pDVar8 = pRoom, (pRoom->tCoords).nSubtileHeight + iVar1 <= iVar4))
					{
						a8 = 0;
						a7 = 0;
						DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, (D2ActiveRoomStrc***)&a8, (int*)&a7);
						uVar7 = 0;
						if (a7 != 0)
						{
							do
							{
								piVar2 = *(int**)(a8 + uVar7 * 4);
								if (((piVar2 != nullptr) && (*piVar2 <= iVar5)) &&
								    ((iVar5 < piVar2[2] + *piVar2 &&
								        ((piVar2[1] <= iVar4 && (iVar4 < piVar2[3] + piVar2[1]))))))
								{
									pDVar8 = *(D2ActiveRoomStrc**)(a8 + uVar7 * 4);
									goto LAB_6fac0089;
								}
								uVar7 = uVar7 + 1;
							} while (uVar7 < a7);
						}
					}
					else
					{
					LAB_6fac0089:
						if (pDVar8 != nullptr)
						{
							sub_6FB3E070(&uStack_5c);
						}
					}
				}
			}
			iStack_6c = iStack_6c + -1;
			DVar3 = local_64;
		} while (iStack_6c != 0);
	}
}

//D2Client.0x6FAC00B0
uint32_t __fastcall sub_6FAC00B0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t DStack_c;
	int iStack_8;
	int local_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar4 != 0))
	{
		local_4 = sub_6FABF670(pUnit, a2);
		if (local_4 < 0)
		{
			return 0;
		}
		iVar2 = sub_6FABF730(pUnit, a2, a3);
		if (iVar2 < 1)
		{
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 100), a2, a3);
		}
		pDVar3 = sub_6FB296A0((int)pUnit);
		if (pDVar3 == nullptr)
		{
			iVar4 = sub_6FABA950(pUnit, &iStack_8, (int*)&DStack_c);
			if (iVar4 == 0)
			{
				return 0;
			}
		}
		else
		{
			uVar1 = pDVar3->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iStack_8 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iStack_8 = 0;
			}
			else
			{
				iStack_8 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar1 = pDVar3->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DStack_c = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_c + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_c + 2)) = 0;
			}
			else
			{
				DStack_c = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
		}
		sub_6FABFE90(pUnit, iStack_8, local_4, iStack_8, (uint32_t)DStack_c, iVar2, a2, a3);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC01F0
uint32_t __fastcall sub_6FAC01F0(D2UnitStrc* pUnit, int a2, int a3)
{
	int nMissileId;
	D2UnitStrc* pDVar1;
	int iVar2;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c == 0))
	{
		return 0;
	}
	nMissileId = sub_6FABF670(pUnit, a2);
	if (nMissileId < 0)
	{
		return 0;
	}
	pDVar1 = sub_6FB296A0((int)pUnit);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	iVar2 = DATATBLS_GetMissileVelocityFromMissilesTxt(nMissileId, a3);
	sub_6FABD4D0(pUnit, (int*)pDVar1, nMissileId, -1, a2, a3, iVar2);
	return 1;
}

//D2Client.0x6FAC0280
uint32_t __fastcall sub_6FAC0280(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	uint32_t nLowSeed;
	int iVar2;
	D2UnitStrc* pDVar3;
	int32_t DVar4;
	int iVar5;
	uint32_t* puVar6;
	int iStack_74;
	int local_70;
	uint64_t DStack_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	int iStack_2c;
	code* pcStack_8;
	uint32_t uStack_4;

	if ((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)))
	{
		iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c;
		if (iVar5 != 0)
		{
			iVar2 = sub_6FABF670(pUnit, a2);
			if (iVar2 < 0)
			{
				return 0;
			}
			pDVar3 = sub_6FB296A0((int)pUnit);
			if (pDVar3 == nullptr)
			{
				return 0;
			}
			local_70 = sub_6FABF730(pUnit, a2, a3);
			if (local_70 < 1)
			{
				local_70 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar5 + 100), a2, a3);
			}
			uVar1 = pDVar3->dwUnitType;
			nLowSeed = pUnit->dwInitSeed;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iStack_74 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iStack_74 = 0;
			}
			else
			{
				iStack_74 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar1 = pDVar3->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DVar4 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
			}
			else
			{
				DVar4 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
			SEED_InitLowSeed((D2SeedStrc*)(&DStack_64), nLowSeed);
			puVar6 = &uStack_5c;
			for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar6 = 0;
				puVar6 = puVar6 + 1;
			}
			iStack_48 = iStack_74;
			uStack_5c = 3;
			iStack_2c = a3;
			pcStack_8 = (code*)(sub_6FAC0480);
			iVar5 = 0;
			pDStack_58 = pUnit;
			iStack_4c = iVar2;
			DStack_44 = DVar4;
			iStack_30 = a2;
			do
			{
				uStack_3c = *(uint32_t*)((int)dword_6FB6E678 + iVar5);
				uStack_40 = *(uint32_t*)((int)dword_6FB6E578 + iVar5);
				DStack_64 = (uint64_t)(((uint64_t)DStack_64 & 0xffffffff) * 0x6ac690c5 +
				                       ((uint64_t)DStack_64 >> 0x20));
				uStack_4 = (*(uint32_t*)((uint8_t*)&DStack_64 + 0));
				pDVar3 = sub_6FB3E070(&uStack_5c);
				if ((a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)) &&
				    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 != 0))
				{
					iVar2 = *(int*)(iVar2 + 0x14c);
				}
				else
				{
					iVar2 = 0;
				}
				MISSILE_SetTargetX(pDVar3, iVar2 + 1);
				iVar5 = iVar5 + local_70 * 4;
			} while (iVar5 < 0x100);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC0480
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAC0480()
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	D2UnitStrc* in_ECX;
	int in_EDX;

	if (in_ECX != nullptr)
	{
		iVar1 = MISSILE_GetTotalFrames(in_ECX);
		if (0x4d < iVar1)
		{
			iVar1 = 0x4d;
			MISSILE_SetTotalFrames(in_ECX, 0x4d);
			MISSILE_SetCurrentFrame(in_ECX, 0x4d);
		}
		pDynamicPath = in_ECX->pDynamicPath;
		SEED_InitLowSeed(&in_ECX->pSeed, in_EDX);
		PATH_SetType(pDynamicPath, 10);
		PATH_SetNewDistance(pDynamicPath, (uint8_t)iVar1);
		D2Common_10142(pDynamicPath, in_ECX, 0);
	}
}

//D2Client.0x6FAC04E0
uint32_t __fastcall sub_6FAC04E0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	uint32_t nLowSeed;
	int iVar2;
	D2UnitStrc* pDVar3;
	int32_t DVar4;
	int iVar5;
	uint32_t* puVar6;
	int iStack_74;
	int local_70;
	uint64_t DStack_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	int iStack_2c;
	code* pcStack_8;
	uint32_t uStack_4;

	if ((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)))
	{
		iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c;
		if (iVar5 != 0)
		{
			iVar2 = sub_6FABF670(pUnit, a2);
			if (iVar2 < 0)
			{
				return 0;
			}
			pDVar3 = sub_6FB296A0((int)pUnit);
			if (pDVar3 == nullptr)
			{
				return 0;
			}
			local_70 = sub_6FABF730(pUnit, a2, a3);
			if (local_70 < 1)
			{
				local_70 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar5 + 100), a2, a3);
			}
			uVar1 = pDVar3->dwUnitType;
			nLowSeed = pUnit->dwInitSeed;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iStack_74 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iStack_74 = 0;
			}
			else
			{
				iStack_74 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar1 = pDVar3->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DVar4 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
			}
			else
			{
				DVar4 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
			SEED_InitLowSeed((D2SeedStrc*)(&DStack_64), nLowSeed);
			puVar6 = &uStack_5c;
			for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar6 = 0;
				puVar6 = puVar6 + 1;
			}
			iStack_48 = iStack_74;
			uStack_5c = 3;
			iStack_2c = a3;
			pcStack_8 = (code*)(sub_6FAC06E0);
			iVar5 = 0;
			pDStack_58 = pUnit;
			iStack_4c = iVar2;
			DStack_44 = DVar4;
			iStack_30 = a2;
			do
			{
				uStack_3c = *(uint32_t*)((int)dword_6FB6E8C0 + iVar5);
				uStack_40 = *(uint32_t*)((int)dword_6FB6E7C0 + iVar5);
				DStack_64 = (uint64_t)(((uint64_t)DStack_64 & 0xffffffff) * 0x6ac690c5 +
				                       ((uint64_t)DStack_64 >> 0x20));
				uStack_4 = (*(uint32_t*)((uint8_t*)&DStack_64 + 0));
				pDVar3 = sub_6FB3E070(&uStack_5c);
				if ((a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)) &&
				    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 != 0))
				{
					iVar2 = *(int*)(iVar2 + 0x14c);
				}
				else
				{
					iVar2 = 0;
				}
				MISSILE_SetTargetX(pDVar3, iVar2 + 1);
				iVar5 = iVar5 + local_70 * 4;
			} while (iVar5 < 0x100);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC06E0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAC06E0()
{
	D2SeedStrc* pSeed;
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar1;
	uint64_t uVar2;
	uint8_t bVar3;
	int iVar4;
	int iVar5;
	int nNewX;
	uint32_t uVar6;
	D2UnitStrc* in_ECX;
	int in_EDX;
	int iStack_20;
	int iStack_1c;
	int32_t DStack_18;
	D2PathPointStrc* pDStack_14;
	int iStack_10;
	int iStack_c;
	uint32_t uStack_8;
	D2DynamicPathStrc* pDStack_4;

	if (in_ECX != nullptr)
	{
		iStack_10 = in_EDX;
		iVar4 = MISSILE_GetTotalFrames(in_ECX);
		iStack_c = iVar4;
		if (0x4d < iVar4)
		{
			iVar4 = 0x4d;
			iStack_c = 0x4d;
			MISSILE_SetTotalFrames(in_ECX, 0x4d);
			MISSILE_SetCurrentFrame(in_ECX, 0x4d);
		}
		pDynamicPath = in_ECX->pDynamicPath;
		pSeed = &in_ECX->pSeed;
		pDStack_4 = pDynamicPath;
		SEED_InitLowSeed(pSeed, iStack_10);
		PATH_SetType(pDynamicPath, 10);
		PATH_SetNewDistance(pDynamicPath, (uint8_t)iVar4);
		PATH_GetPathPoints(pDynamicPath, &pDStack_14);
		uVar6 = in_ECX->dwUnitType;
		if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
		{
			iStack_1c = in_ECX->pDynamicPath->dwClientCoordY;
		}
		else if (in_ECX->pDynamicPath == nullptr)
		{
			iStack_1c = 0;
		}
		else
		{
			iStack_1c = PATH_GetXPosition(in_ECX->pDynamicPath);
		}
		uVar6 = in_ECX->dwUnitType;
		if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
		{
			DStack_18 = (*(int32_t*)&in_ECX->pDynamicPath->tTargetCoord);
		}
		else if (in_ECX->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0;
		}
		else
		{
			DStack_18 = (int32_t)PATH_GetYPosition(in_ECX->pDynamicPath);
		}
		iVar5 = D2COMMON_10176_PathGetFirstPointY(in_ECX->pDynamicPath);
		nNewX = D2COMMON_10175_PathGetFirstPointX(in_ECX->pDynamicPath);
		uVar6 = UNITS_GetDirectionToCoords(in_ECX, nNewX, iVar5);
		uVar6 = uVar6 & 0xff;
		uVar2 = (uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(in_ECX->pSeed).nHighSeed;
		pSeed->nLowSeed = (uint32_t)uVar2;
		uStack_8 = (uint32_t)uVar2 & 1;
		iStack_20 = (uint32_t)((uVar2 & 1) != 0) * 2 + -1;
		DVar1 = (uint64_t)((uVar2 & 0xffffffff) * 0x6ac690c5 + (uVar2 >> 0x20));
		*(uint64_t*)pSeed = DVar1;
		iVar5 = 0;
		iStack_10 = (int)(((uint64_t)DVar1 & 0xffffffff) % 3) + dword_6FB778C0;
		if (0 < iVar4)
		{
			do
			{
				uVar6 = uVar6 + iStack_10 * iStack_20;
				bVar3 = D2Common_11053((uint8_t)uVar6 & 0x3f);
				uStack_8 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_8 + 1)), bVar3);
				iVar4 = *(int*)(&byte_6FB6E79C + (uint32_t)bVar3 * 4);
				iStack_1c = iStack_1c + *(int*)(&byte_6FB6E77C + (uint32_t)bVar3 * 4);
				pDStack_14[iVar5].X = (uint16_t)iStack_1c;
				DStack_18 = (int32_t)((int)DStack_18 + iVar4);
				pDStack_14[iVar5].Y = (*(uint16_t*)((uint8_t*)&DStack_18 + 0));
				if (iVar5 % dword_6FB778BC == 0)
				{
					iStack_20 = -iStack_20;
					DVar1 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(in_ECX->pSeed).nHighSeed);
					*(uint64_t*)pSeed = DVar1;
					iStack_10 = (int)(((uint64_t)DVar1 & 0xffffffff) % 3) + dword_6FB778C0;
				}
				iVar5 = iVar5 + 1;
				iVar4 = iStack_c;
			} while (iVar5 < iStack_c);
		}
		PATH_SetNumberOfPathPoints(pDStack_4, iVar4);
	}
}

//D2Client.0x6FAC08E0
uint32_t __fastcall sub_6FAC08E0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	short sVar1;
	D2UnitStrc* pDVar2;
	D2StatListStrc* pStatList;
	int iVar3;
	int iVar4;
	int iVar5;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar5 == 0))
	{
		return 0;
	}
	pDVar2 = sub_6FB296A0((int)pUnit);
	if (pDVar2 == nullptr)
	{
		return 0;
	}
	if ((((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar5 + 4)) != 0) &&
	    (sVar1 = *(short*)(iVar5 + 0x80), -1 < sVar1))
	{
		if (((int)sVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4)) &&
		    ((-1 < *(short*)(iVar5 + 0x54) &&
		        ((int)*(short*)(iVar5 + 0x54) < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4)))))
		{
			pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, (int)sVar1);
			if (pStatList != nullptr)
			{
				iVar3 = STATLIST_GetStatValue(pStatList, (int)*(short*)(iVar5 + 0x54), 0);
				if (iVar3 < 2)
				{
					iVar3 = 1;
				}
				else if (2 < iVar3)
				{
					iVar3 = 3;
				}
				iVar4 = (int)*(short*)(iVar5 + 0x10c) + iVar3 + -1;
				iVar5 = (int)*(short*)(iVar5 + 0x10e) + iVar3 + -1;
				goto LAB_6fac09be;
			}
		}
	}
	iVar4 = (int)*(short*)(iVar5 + 0x10c);
	iVar5 = (int)*(short*)(iVar5 + 0x10e);
LAB_6fac09be:
	sub_6FB5BA70(pDVar2, iVar4, 2, 0, 0, 0, 0, 0);
	sub_6FB55820(iVar5, pUnit, 0.0, 0.0, 0);
	return 1;
}

//D2Client.0x6FAC09F0
uint32_t __fastcall sub_6FAC09F0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	short sVar1;
	D2StatListStrc* pStatList;
	int iVar2;
	int iVar3;
	int iVar4;

	if (((a2 < 0) || (iVar3 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar3 + 0xba0) <= a2)) || (iVar4 = *(int*)(iVar3 + 0xb98) + a2 * 0x23c, iVar4 == 0))
	{
		return 0;
	}
	if (((((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar4 + 4)) != 0) &&
	        (sVar1 = *(short*)(iVar4 + 0x80), -1 < sVar1)) &&
	    (((int)sVar1 < *(int*)(iVar3 + 0xc4) &&
	        ((-1 < *(short*)(iVar4 + 0x54) && ((int)*(short*)(iVar4 + 0x54) < *(int*)(iVar3 + 0xbd4)))))))
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, (int)sVar1);
		if (pStatList != nullptr)
		{
			iVar2 = STATLIST_GetStatValue(pStatList, (int)*(short*)(iVar4 + 0x54), 0);
			if (iVar2 < 2)
			{
				iVar2 = 1;
			}
			else if (2 < iVar2)
			{
				iVar2 = 3;
			}
			iVar3 = (int)*(short*)(iVar4 + 0x10c) + iVar2 + -1;
			iVar4 = (int)*(short*)(iVar4 + 0x10e) + iVar2 + -1;
			goto LAB_6fac0ab0;
		}
	}
	iVar3 = (int)*(short*)(iVar4 + 0x10c);
	iVar4 = (int)*(short*)(iVar4 + 0x10e);
LAB_6fac0ab0:
	sub_6FB5BA70(pUnit, iVar3, 2, 0, 0, 0, 0, 0);
	sub_6FB55820(iVar4, pUnit, 0.0, 0.0, 0);
	return 1;
}

//D2Client.0x6FAC0AE0
uint32_t __fastcall sub_6FAC0AE0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	int local_8;
	int local_4;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c == 0))
	{
		return 0;
	}
	iVar1 = sub_6FABF670(pUnit, a2);
	if (iVar1 < 0)
	{
		return 0;
	}
	iVar2 = sub_6FABA950(pUnit, &local_4, &local_8);
	if (iVar2 == 0)
	{
		return 0;
	}
	sub_6FABAD50(pUnit, iVar1, a2, a3);
	return 1;
}

//D2Client.0x6FAC0B80
uint32_t __fastcall sub_6FAC0B80(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint64_t uVar1;
	int iVar2;
	D2UnitStrc* pMissile;
	uint32_t nTargetX;
	int iVar3;
	uint32_t* puVar4;
	int local_78;
	int local_74;
	int local_70;
	int local_6c;
	int local_68;
	uint64_t local_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	uint32_t uStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c == 0))
	{
		return 0;
	}
	local_68 = sub_6FABF670(pUnit, a2);
	if (local_68 < 0)
	{
		return 0;
	}
	iVar2 = sub_6FABA950(pUnit, &local_74, &local_78);
	if (iVar2 != 0)
	{
		iVar2 = sub_6FABF730(pUnit, a2, a3);
		if (iVar2 != 0)
		{
			local_6c = local_78;
			local_70 = local_74;
			SEED_InitLowSeed((D2SeedStrc*)(&local_64), local_74);
			puVar4 = &uStack_5c;
			for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar4 = 0;
				puVar4 = puVar4 + 1;
			}
			iStack_48 = local_70;
			uStack_5c = 3;
			iStack_44 = local_6c;
			iStack_4c = local_68;
			uStack_2c = a3;
			pDStack_58 = pUnit;
			iStack_30 = a2;
			if (0 < iVar2)
			{
				do
				{
					uVar1 = ((uint64_t)local_64 & 0xffffffff) * 0x6ac690c5 + ((uint64_t)local_64 >> 0x20);
					uStack_40 = (int)((uVar1 & 0xffffffff) % 0x28) - 0x14;
					local_64 = (uint64_t)((uVar1 & 0xffffffff) * 0x6ac690c5 + (uVar1 >> 0x20));
					iStack_3c = (int)(((uint64_t)local_64 & 0xffffffff) % 0x28) + -0x14;
					if ((uStack_40 == 0) && (iStack_3c == 0))
					{
						uStack_40 = 0x14;
					}
					pMissile = sub_6FB3E070(&uStack_5c);
					if (pMissile != nullptr)
					{
						nTargetX = SEED_GetLowSeed((D2SeedStrc*)(&local_64));
						MISSILE_SetTargetX(pMissile, nTargetX);
						MISSILE_SetTargetY(pMissile, iStack_3c * 0x10000 + (uStack_40 & 0xffff));
					}
					iVar2 = iVar2 + -1;
				} while (iVar2 != 0);
			}
			return 1;
		}
		return 0;
	}
	return 0;
}

//D2Client.0x6FAC0D30
bool __fastcall sub_6FAC0D30(int a1, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pUnit;
	int iVar1;

	pUnit = sub_6FB296A0(a1);
	if (pUnit == nullptr)
	{
		return false;
	}
	iVar1 = D2COMMON_11018(pUnit);
	return iVar1 != 0;
}

//D2Client.0x6FAC0D50
uint32_t __fastcall sub_6FAC0D50(int a1, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB296A0(a1);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x40;
	}
	sub_6FB42A70(pDVar1, 5, 0);
	return 1;
}

//D2Client.0x6FAC0D90
uint32_t __fastcall sub_6FAC0D90(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		iVar1 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x114), a2, a3);
		sub_6FABE200(pUnit, iVar1);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC0DF0
uint32_t __fastcall sub_6FAC0DF0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int32_t nY;
	float fVar4;
	float fVar5;
	int iVar6;

	if ((int)(pUnit->dwSeqFrame & 0xffffff00U) < 0x600)
	{
		iVar6 = 0;
		fVar5 = 0.0;
		fVar4 = 5.60519e-45;
		uVar1 = UNITS_GetHitClass(pUnit);
		iVar2 = sub_6FB4F4D0((int)pUnit, uVar1);
		sub_6FB55820(iVar2, pUnit, fVar4, fVar5, iVar6);
		pDVar3 = sub_6FB296A0((int)pUnit);
		if (pDVar3 == nullptr)
		{
			return 1;
		}
		if (pUnit->pDynamicPath == nullptr)
		{
			return 1;
		}
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
		LAB_6fac0f16:
			iVar2 = pDVar3->pDynamicPath->dwClientCoordY;
			goto LAB_6fac0f1c;
		}
		if (pDVar3->pDynamicPath != nullptr)
		{
			iVar2 = PATH_GetXPosition(pDVar3->pDynamicPath);
			goto LAB_6fac0f1c;
		}
	}
	else
	{
		pDVar3 = sub_6FB296A0((int)pUnit);
		uVar1 = 0xffffffff;
		if (pDVar3 != nullptr)
		{
			uVar1 = pDVar3->dwUnitId;
		}
		pDVar3 = sub_6FABB890(pUnit, 0, 0, 3, 0, uVar1, nullptr);
		if (pDVar3 == nullptr)
		{
			return 1;
		}
		if (pUnit->pDynamicPath == nullptr)
		{
			return 1;
		}
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
			goto LAB_6fac0f16;
		if (pDVar3->pDynamicPath != nullptr)
		{
			iVar2 = PATH_GetXPosition(pDVar3->pDynamicPath);
			goto LAB_6fac0f1c;
		}
	}
	iVar2 = 0;
LAB_6fac0f1c:
	D2Common_10216(pUnit->pDynamicPath, iVar2, (int)nY, 0);
	return 1;
}

//D2Client.0x6FAC0F40
uint32_t __fastcall sub_6FAC0F40(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pItem;
	int iVar1;
	int iVar2;
	uint32_t* puVar3;

	pItem = D2Common_10434(pUnit, 1);
	if (pItem != nullptr)
	{
		ITEMS_CheckIfThrowable(pItem);
		if (0x8ff < (int)(pUnit->dwSeqFrame & 0xffffff00U))
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		iVar1 = ITEMS_CheckIfThrowable(pItem);
		if ((iVar1 == 0) && (iVar1 = STATLIST_UnitGetItemStatOrSkillStatValue(pItem, 0x7d, 0), iVar1 != 0))
		{
			return 0;
		}
		iVar1 = ITEMS_GetMissileType(pItem);
		if ((0 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			iVar2 = ITEMS_CheckItemTypeId(pItem, 0x26);
			if (iVar2 == 0)
			{
				sub_6FABABC0(pUnit, iVar1, a2, a3);
			}
			else
			{
				puVar3 = sub_6FB3EBE0(pUnit, iVar1, 0, 0, 0, 0, a2, a3, 0);
				if (puVar3 == nullptr)
				{
					return 0;
				}
			}
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC1000
bool __fastcall sub_6FAC1000(int a1, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pUnit;
	int iVar1;

	pUnit = sub_6FB296A0(a1);
	if (pUnit == nullptr)
	{
		return false;
	}
	iVar1 = D2COMMON_11019(pUnit);
	return iVar1 != 0;
}

//D2Client.0x6FAC1020
uint32_t __fastcall sub_6FAC1020(int a1, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pUnit;
	int iVar1;

	pUnit = sub_6FB296A0(a1);
	if (pUnit == nullptr)
	{
		return 0;
	}
	iVar1 = UNITS_IsSoftMonster(pUnit);
	if (iVar1 == 0)
	{
		return 0;
	}
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x40;
	}
	sub_6FB42A70(pUnit, 5, 0);
	return 1;
}

//D2Client.0x6FAC1070
uint32_t __fastcall sub_6FAC1070(int a1, int a2, uint32_t a3)
{
	int iVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	D2ActiveRoomStrc* pDVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t* puVar7;
	uint32_t uStack_7c;
	D2ActiveRoomStrc** ppDStack_78;
	int local_74;
	D2UnitStrc* local_70;
	int local_6c;
	int local_68;
	D2CoordStrc DStack_64;
	uint32_t auStack_5c[4];
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	        (local_74 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, local_74 != 0)) &&
	    ((local_6c = a1, local_68 = a2, pUnit = sub_6FB296A0(a1),
	        pUnit != nullptr &&
	            (local_70 = pUnit, iVar2 = UNITS_IsSoftMonster(pUnit), iVar2 != 0))))
	{
		if (a1 != 0)
		{
			*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x40;
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_64.nX = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			DStack_64.nX = 0;
		}
		else
		{
			DStack_64.nX = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_64.nY = *(int*)&pUnit->pDynamicPath->tTargetCoord;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_64.nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_64.nY + 2)) = 0;
		}
		else
		{
			DStack_64.nY = PATH_GetYPosition(pUnit->pDynamicPath);
		}
		pDVar3 = UNITS_GetRoom(pUnit);
		iVar4 = DStack_64.nY;
		iVar2 = DStack_64.nX;
		if (pDVar3 != nullptr)
		{
			iVar6 = (pDVar3->tCoords).nSubtileX;
			if ((((DStack_64.nX < iVar6) || ((pDVar3->tCoords).nSubtileWidth + iVar6 <= DStack_64.nX)) ||
			        (iVar6 = (pDVar3->tCoords).nSubtileY, DStack_64.nY < iVar6)) ||
			    ((pDVar3->tCoords).nSubtileHeight + iVar6 <= DStack_64.nY))
			{
				ppDStack_78 = nullptr;
				uStack_7c = 0;
				DUNGEON_GetAdjacentRoomsListFromRoom(pDVar3, &ppDStack_78, (int*)&uStack_7c);
				uVar5 = 0;
				if (uStack_7c != 0)
				{
					do
					{
						pDVar3 = ppDStack_78[uVar5];
						if (((pDVar3 != nullptr) &&
						        (iVar6 = (pDVar3->tCoords).nSubtileX, iVar6 <= iVar2)) &&
						    ((iVar2 < (pDVar3->tCoords).nSubtileWidth + iVar6 &&
						        ((iVar6 = (pDVar3->tCoords).nSubtileY, iVar6 <= iVar4 &&
						                                                   (iVar4 < (pDVar3->tCoords).nSubtileHeight + iVar6))))))
						{
							pDVar3 = ppDStack_78[uVar5];
							pUnit = local_70;
							goto LAB_6fac11e5;
						}
						uVar5 = uVar5 + 1;
					} while (uVar5 < uStack_7c);
				}
			}
			else
			{
			LAB_6fac11e5:
				iVar2 = local_74;
				if (((pDVar3 != nullptr) &&
				        (pDVar3 = COLLISION_GetFreeCoordinates(pDVar3, &DStack_64, 2, 0x1000, 1),
				            pDVar3 != nullptr)) &&
				    (pUnit->dwUnitType == 1))
				{
					iVar4 = pUnit->dwClassId;
					iVar6 = (int)*(short*)(iVar2 + 0xea);
					if (((-1 < iVar4) &&
					        (iVar1 = *(int*)((uint8_t*)&sgptDataTables), iVar4 < *(int*)(iVar1 + 0xa80))) &&
					    ((iVar4 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + iVar4 * 0x1a8), -1 < iVar4 && ((iVar4 < *(int*)(iVar1 + 0xa98) &&
					                                                                                               (iVar4 = *(int*)(iVar1 + 0xa90) + iVar4 * 0x134, iVar4 != 0))))))
					{
						uVar5 = (uint32_t) * (uint8_t*)(iVar4 + 5);
						if ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0xc) & uVar5) == 0)
						{
							if ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 8) & uVar5) != 0)
							{
								iVar6 = (int)*(short*)(iVar2 + 0xec);
							}
						}
						else
						{
							iVar6 = (int)*(short*)(iVar2 + 0xee);
						}
						if ((-1 < iVar6) && (iVar6 < *(int*)(iVar1 + 0xb6c)))
						{
							puVar7 = auStack_5c;
							for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
							{
								*puVar7 = 0;
								puVar7 = puVar7 + 1;
							}
							auStack_5c[1] = local_6c;
							iStack_30 = local_68;
							uStack_2c = a3;
							auStack_5c[0] = 0x2001;
							iStack_48 = DStack_64.nX;
							(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = (uint16_t)DStack_64.nY;
							(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = (*(uint16_t*)((uint8_t*)&DStack_64.nY + 2));
							iStack_4c = iVar6;
							sub_6FB3E070(auStack_5c);
							iStack_4c = 0x73;
							sub_6FB3E070(auStack_5c);
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}
