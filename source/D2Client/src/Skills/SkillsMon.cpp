#include "Skills/SkillsMon.h"

#include "Draw/DLightMap.h"
#include "Engine/Particle.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Skills/SkillsAma.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/UnitMode.h"

//D2Client.0x6FB6EBC0
uint32_t dword_6FB6EBC0 = 0x1E;
//D2Client.0x6FB6ECC0
uint32_t dword_6FB6ECC0;

//D2Client.0x6FAC6B70
uint32_t __fastcall sub_6FAC6B70(D2UnitStrc* pUnit, int a2, int a3)
{
	D2DynamicPathStrc* pDynamicPath;
	D2SkillStrc* pSkill;
	D2UnitStrc* pUnit1;
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	uint64_t uVar4;
	int iStack_8;
	int iStack_4;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar3 == 0))
	{
		return 0;
	}
	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	UNITS_GetShiftedFrameMetrics(pUnit, &iStack_8, &iStack_4);
	if (iStack_8 <= *(int*)(iVar3 + 0x154))
	{
		pDynamicPath = pUnit->pDynamicPath;
		if (pDynamicPath == nullptr)
		{
			return 0;
		}
		pUnit1 = PATH_GetTargetUnit(pDynamicPath);
		if ((pUnit1 == nullptr) || (iVar1 = D2Common_10399(pUnit1, pUnit), 1 < iVar1))
		{
			uVar2 = SKILLS_GetFlags(pSkill);
			if ((uVar2 & 2) == 0)
			{
				if (iStack_8 == *(int*)(iVar3 + 0x150))
				{
					iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x138), a2, a3);
					iVar3 = iVar3 * 0x100;
					if (iVar3 < 0x101)
					{
						iVar3 = 0x100;
					}
					uVar2 = STATLIST_UnitGetStatValue(pUnit, 0x43, 0);
					if (iVar3 < 0x100001)
					{
						if ((int)uVar2 < 0x10001)
						{
							iVar3 = (int)(uVar2 * iVar3) / 100;
						}
						else if ((int)(uVar2 & 0xfffffff0) < 0x640)
						{
							uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar2 * (int64_t)iVar3),
							    (uint32_t)((uint64_t)((int64_t)(int)uVar2 * (int64_t)iVar3) >> 0x20),
							    100, 0);
							iVar3 = (int)uVar4;
						}
						else
						{
							iVar3 = ((int)uVar2 / 100) * iVar3;
						}
					}
					else if (iVar3 < 0x640)
					{
						uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar2 * (int64_t)iVar3),
						    (uint32_t)((uint64_t)((int64_t)(int)uVar2 * (int64_t)iVar3) >> 0x20), 100, 0);
						iVar3 = (int)uVar4;
					}
					else
					{
						iVar3 = (iVar3 / 100) * uVar2;
					}
					PATH_SetVelocity(pDynamicPath, iVar3, __FILE__, __LINE__);
					PATH_SetType(pDynamicPath, 1);
					D2Common_10142(pDynamicPath, pUnit, 0);
					SKILLS_SetFlags(pSkill, 1);
					return 1;
				}
				if (iStack_8 != *(int*)(iVar3 + 0x154))
				{
					return 1;
				}
				pUnit->dwFrameCountPrecise = *(int*)(iVar3 + 0x158) << 8;
				iVar3 = *(int*)(iVar3 + 0x15c);
			}
			else
			{
				SKILLS_SetFlags(pSkill, 0);
				pUnit->dwFrameCountPrecise = *(int*)(iVar3 + 0x148) << 8;
				iVar3 = *(int*)(iVar3 + 0x14c);
			}
		}
		else
		{
			SKILLS_SetFlags(pSkill, 0);
			pUnit->dwFrameCountPrecise = *(int*)(iVar3 + 0x148) << 8;
			iVar3 = *(int*)(iVar3 + 0x14c);
		}
		UNITS_SetAnimationFrame(pUnit, iVar3);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC6DB0
uint32_t __fastcall sub_6FAC6DB0(D2UnitStrc* pUnit, uint32_t a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	int iStack_80;
	int local_7c;
	int32_t DStack_78;
	int local_74;
	int local_70;
	uint32_t local_6c;
	int local_68;
	D2UnitStrc* local_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_2c;

	iVar5 = 0;
	if (((((int)a2 < 0) ||
	         (iVar2 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar2 + 0xba0) <= (int)a2)) ||
	        (local_68 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, local_68 == 0)) ||
	    ((local_60 = (int)*(short*)(local_68 + 0xea), local_60 < 0 ||
	                                                      (*(int*)(iVar2 + 0xb6c) <= local_60))))
	{
		return 0;
	}
	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x40;
	}
	local_6c = a2;
	local_64 = pUnit;
	iVar2 = sub_6FABA950(pUnit, &local_74, &local_70);
	if (iVar2 == 0)
	{
		return 0;
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		local_7c = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_7c = 0;
	}
	else
	{
		local_7c = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DStack_78 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_78 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_78 + 2)) = 0;
	}
	else
	{
		DStack_78 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	iVar2 = local_74 - local_7c;
	iVar6 = local_70 - (int)DStack_78;
	if ((iVar2 == 0) && (iVar6 == 0))
	{
		return 0;
	}
	iStack_80 = 0;
	if ((iVar2 < 0) && (iVar6 < 0))
	{
		iStack_80 = 2;
	}
	else
	{
		if ((iVar2 == 0) && (iVar6 < 0))
		{
			iStack_80 = 2;
			goto LAB_6fac6f52;
		}
		if (0 < iVar2)
		{
			if (iVar6 < 0)
			{
				iVar5 = 2;
				iStack_80 = 2;
				goto LAB_6fac6f52;
			}
			if (iVar6 == 0)
			{
				iVar5 = 2;
				goto LAB_6fac6f52;
			}
			if (0 < iVar6)
			{
				iStack_80 = -2;
				iVar5 = 2;
				goto LAB_6fac6f52;
			}
		}
		if ((iVar2 == 0) && (0 < iVar6))
		{
			iStack_80 = -2;
			goto LAB_6fac6f52;
		}
		if (-1 < iVar2)
			goto LAB_6fac6f52;
		if (0 < iVar6)
		{
			iVar5 = -2;
			iStack_80 = -2;
			goto LAB_6fac6f52;
		}
		if (iVar6 != 0)
			goto LAB_6fac6f52;
	}
	iVar5 = -2;
LAB_6fac6f52:
	iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(local_68 + 0x138), local_6c, a3);
	iVar2 = iVar2 - (iVar3 / 2) * iStack_80;
	iVar6 = iVar6 - (iVar3 / 2) * iVar5;
	puVar7 = &uStack_5c;
	for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*puVar7 = 0;
		puVar7 = puVar7 + 1;
	}
	uStack_5c = 3;
	local_68 = iVar3;
	if (0 < iVar3)
	{
		do
		{
			pDStack_58 = local_64;
			iStack_48 = iVar2 / 6 + local_7c;
			iStack_44 = iVar6 / 6 + (int)DStack_78;
			iStack_2c = a3;
			iStack_4c = local_60;
			iStack_40 = iVar2;
			iStack_3c = iVar6;
			sub_6FB3E070(&uStack_5c);
			iVar6 = iVar6 + iVar5;
			iVar2 = iVar2 + iStack_80;
			iVar3 = iVar3 + -1;
		} while (iVar3 != 0);
	}
	return 1;
}

//D2Client.0x6FAC7030
uint32_t __fastcall sub_6FAC7030(int* a1, int a2, int a3)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint32_t* puVar5;
	uint32_t uStack_5c;
	int* piStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_34;
	int iStack_30;
	int iStack_2c;

	if ((((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0))) && (iVar4 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar4 != 0)) &&
	    ((iVar4 = (int)*(short*)(iVar4 + 0xea), -1 < iVar4 && (iVar4 < *(int*)(iVar2 + 0xb6c)))))
	{
		if (a1 != nullptr)
		{
			a1[0x31] = a1[0x31] | 0x40;
		}
		pDVar1 = sub_6FB296A0((int)a1);
		if (pDVar1 != nullptr)
		{
			iVar2 = DATATBLS_GetMissileVelocityFromMissilesTxt(iVar4, a3);
			puVar5 = &uStack_5c;
			for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar5 = 0;
				puVar5 = puVar5 + 1;
			}
			iVar3 = *a1;
			uStack_5c = 3;
			if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
			{
				iStack_48 = *(int*)(a1[0xb] + 0xc);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iStack_48 = 0;
			}
			else
			{
				iStack_48 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			iVar3 = *a1;
			if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
			{
				iStack_44 = *(int*)(a1[0xb] + 0x10);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iStack_44 = 0;
			}
			else
			{
				iStack_44 = PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			uStack_5c = uStack_5c | 4;
			iStack_2c = a3;
			iVar3 = 0;
			piStack_58 = a1;
			iStack_4c = iVar4;
			iStack_34 = iVar2;
			iStack_30 = a2;
			do
			{
				uStack_3c = *(uint32_t*)((int)&dword_6FB6ECC0 + iVar3);
				uStack_40 = *(uint32_t*)((int)&dword_6FB6EBC0 + iVar3);
				pDVar1 = sub_6FB3E070(&uStack_5c);
				if (pDVar1 != nullptr)
				{
					sub_6FB60130((int)pDVar1);
					sub_6FB60180((int)pDVar1, 0);
					sub_6FB5FCB0((int)pDVar1, 0, 0, -6, 1);
					sub_6FB5FD50((int)pDVar1, 0, 0, 0, 0);
					sub_6FB5FC80((int)pDVar1, 0, 0, 0x78);
				}
				iVar3 = iVar3 + 4;
			} while (iVar3 < 0x100);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC71E0
uint32_t __fastcall sub_6FAC71E0(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SkillStrc* pSkill;
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	uint64_t DStack_8;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar3 == 0))
	{
		return 0;
	}
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
	SEED_InitSeed((D2SeedStrc*)(&DStack_8));
	if (pUnit == nullptr)
	{
		uVar4 = 0xffffffff;
	}
	else
	{
		uVar4 = pUnit->dwUnitId;
	}
	SEED_InitLowSeed((D2SeedStrc*)(&DStack_8), pDVar1->dwUnitId + uVar4);
	iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x138), a2, a3);
	iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x13c), a2, a3);
	uVar4 = iVar3 - iVar2;
	if ((int)uVar4 < 1)
	{
		uVar4 = 0;
	}
	else if ((uVar4 & uVar4 - 1) == 0)
	{
		DStack_8 = (uint64_t)(((uint64_t)DStack_8 & 0xffffffff) * 0x6ac690c5 + ((uint64_t)DStack_8 >> 0x20));
		uVar4 = uVar4 - 1 & (*(uint32_t*)((uint8_t*)&DStack_8 + 0));
	}
	else
	{
		DStack_8 = (uint64_t)(((uint64_t)DStack_8 & 0xffffffff) * 0x6ac690c5 + ((uint64_t)DStack_8 >> 0x20));
		uVar4 = (uint32_t)(((uint64_t)DStack_8 & 0xffffffff) % (uint64_t)uVar4);
	}
	iVar2 = uVar4 + iVar2;
	if (iVar2 < 1)
	{
		iVar2 = 1;
	}
	SKILLS_SetParam1(pSkill, iVar2);
	SKILLS_SetParam2(pSkill, pDVar1->dwUnitId);
	SKILLS_SetParam3(pSkill, pDVar1->dwUnitType);
	return 1;
}

//D2Client.0x6FAC7330
uint32_t __fastcall sub_6FAC7330(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	D2SkillStrc* pSkill;
	int iVar2;
	uint32_t uVar3;
	D2UnitStrc* pUnit2;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		return 0;
	}
	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	iVar2 = SKILLS_GetParam3(pSkill);
	uVar3 = SKILLS_GetParam2(pSkill);
	pUnit2 = sub_6FB269F0(uVar3, iVar2);
	if (pUnit2 == nullptr)
	{
		SKILLS_SetParam1(pSkill, 0);
		return 0;
	}
	iVar2 = UNITS_IsInMeleeRange(pUnit, pUnit2, 0);
	if (iVar2 == 0)
	{
		return 0;
	}
	iVar2 = SKILLS_GetParam1(pSkill);
	if (iVar2 + -1 < 1)
	{
		return 0;
	}
	SKILLS_SetParam1(pSkill, iVar2 + -1);
	UNITS_SetAnimationFrame(pUnit, *(int*)(iVar1 + 0x148));
	pUnit->dwFrameCountPrecise = (pUnit->dwFrameCountPrecise & 0xffffff00U) + 0x100;
	return 1;
}

//D2Client.0x6FAC7400
uint32_t __fastcall sub_6FAC7400(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;

	if ((((-1 < a2) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar1 + 0xba0))) && (iVar2 = *(int*)(iVar1 + 0xb98) + a2 * 0x23c, iVar2 != 0)) &&
	    ((iVar2 = (int)*(short*)(iVar2 + 0xea), -1 < iVar2 && (iVar2 < *(int*)(iVar1 + 0xb6c)))))
	{
		sub_6FABABC0(pUnit, iVar2, a2, a3);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC7460
uint32_t __fastcall sub_6FAC7460(int* a1, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_5c;
	int* local_58;
	int* local_54;
	int iStack_4c;
	int local_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if (((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0))) && (iVar1 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		iVar3 = (int)*(short*)(iVar1 + 0xea);
		if ((-1 < iVar3) && (iVar3 < *(int*)(iVar2 + 0xb6c)))
		{
			if (a1 != nullptr)
			{
				a1[0x31] = a1[0x31] | 0x40;
			}
			puVar4 = &local_5c;
			for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*puVar4 = 0;
				puVar4 = puVar4 + 1;
			}
			iVar2 = *a1;
			local_5c = 0x2021;
			local_58 = a1;
			local_54 = a1;
			if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
			{
				local_48 = *(int*)(a1[0xb] + 0xc);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				local_48 = 0;
			}
			else
			{
				local_48 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			iVar2 = *a1;
			if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
			{
				iStack_44 = *(int*)(a1[0xb] + 0x10);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iStack_44 = 0;
			}
			else
			{
				iStack_44 = PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			uStack_2c = a3;
			iStack_4c = iVar3;
			iStack_30 = a2;
			sub_6FABD8A0((int)a1, &local_5c, 2, 1);
			iStack_4c = (int)*(short*)(iVar1 + 0xec);
			if ((-1 < iStack_4c) && (iStack_4c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
			{
				sub_6FABD8A0((int)a1, &local_5c, 4, 5);
			}
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC75C0
uint32_t __fastcall sub_6FAC75C0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	int iVar1;
	int iVar2;

	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2);
	iVar1 = SKILLS_GetParam1(pSkill);
	iVar2 = pUnit->nSeqCurrentFramePrecise >> 8;
	if (iVar2 == 6)
	{
		UNITS_SetAnimationFrame(pUnit, 7);
		pUnit->dwFrameCountPrecise = 0x3200;
	}
	else
	{
		if (iVar2 == 0x16)
		{
			if (3 < iVar1)
			{
				UNITS_SetAnimationFrame(pUnit, 0x28);
				pUnit->dwFrameCountPrecise = 0x1100;
				return 1;
			}
			SKILLS_SetParam1(pSkill, iVar1 + 1);
			return 1;
		}
		if (iVar2 == 0x1e)
		{
			sub_6FB4F410(pUnit, (int*)((uint8_t*)0x0c));
			sub_6FB29540((int)pUnit);
			return 1;
		}
	}
	return 1;
}

//D2Client.0x6FAC7650
uint32_t __fastcall sub_6FAC7650(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	D2UnitStrc* pMissile;
	int iVar2;
	uint32_t* puVar3;
	int local_68;
	int local_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	int iStack_2c;

	if (((-1 < a2) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar1 + 0xba0))) && (iVar2 = *(int*)(iVar1 + 0xb98) + a2 * 0x23c, iVar2 != 0))
	{
		local_60 = (int)*(short*)(iVar2 + 0xec);
		if ((-1 < local_60) && (local_60 < *(int*)(iVar1 + 0xb6c)))
		{
			iVar1 = sub_6FABA950(pUnit, &local_68, &local_64);
			if (iVar1 != 0)
			{
				if (pUnit != nullptr)
				{
					pUnit->dwFlags = pUnit->dwFlags | 0x40;
				}
				iVar1 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 100), a2, a3);
				puVar3 = &uStack_5c;
				for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
				{
					*puVar3 = 0;
					puVar3 = puVar3 + 1;
				}
				uStack_5c = 1;
				iStack_48 = local_68;
				iStack_44 = local_64;
				iStack_2c = a3;
				uStack_4c = 0xbf;
				pDStack_58 = pUnit;
				iStack_30 = a2;
				pMissile = sub_6FB3E070(&uStack_5c);
				if (pMissile != nullptr)
				{
					MISSILE_SetStreamMissile(pMissile, (uint16_t)local_60);
					MISSILE_SetStreamRange(pMissile, (short)iVar1);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC7770
uint32_t __fastcall sub_6FAC7770(D2UnitStrc* pUnit2, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	int32_t DVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	int32_t DVar7;
	D2UnitStrc* pDVar8;
	int32_t DVar9;
	D2UnitStrc* pUnit;
	int32_t DVar10;
	D2UnitStrc* pUnit_00;

	pDVar2 = sub_6FABAD50(pUnit2, 0x150, a2, a3);
	pDVar3 = sub_6FABAD50(pUnit2, 0x151, a2, a3);
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar4 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
	}
	else
	{
		DVar4 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar5 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	pDVar6 = sub_6FB3EAF0((int)pUnit2, 0x14f, iVar5, (D2UnitStrc**)DVar4, a2, a3);
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar7 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
	}
	else
	{
		DVar7 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar5 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	pDVar8 = sub_6FB3EAF0((int)pUnit2, 0x151, iVar5, (D2UnitStrc**)DVar7, a2, a3);
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar9 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar9 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar9 + 2)) = 0;
	}
	else
	{
		DVar9 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar5 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	pUnit = sub_6FB3EAF0((int)pUnit2, 0x14e, iVar5, (D2UnitStrc**)DVar9, a2, a3);
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar10 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar10 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar10 + 2)) = 0;
	}
	else
	{
		DVar10 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar5 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	pUnit_00 = sub_6FB3EAF0((int)pUnit2, 0x14d, iVar5, (D2UnitStrc**)DVar10, a2, a3);
	if (pDVar6 != nullptr)
	{
		sub_6FB5FCB0((int)pDVar6, 0, 0, 0xf, 1);
	}
	if (pDVar8 != nullptr)
	{
		sub_6FB5FCB0((int)pDVar8, 0, 0, 0xf, 1);
	}
	if (pDVar2 != nullptr)
	{
		sub_6FB5FC80((int)pDVar2, 0, 0, 0x15f9);
		sub_6FB5FCB0((int)pDVar2, 0, 0, -0x19, 1);
	}
	if (pDVar3 != nullptr)
	{
		sub_6FB5FC80((int)pDVar3, 0, 0, 0x15f9);
		sub_6FB5FCB0((int)pDVar3, 0, 0, -0x19, 1);
	}
	if (pUnit != nullptr)
	{
		UNITS_SetAnimationSpeed(pUnit_00, 0x80);
		UNITS_SetAnimationSpeed(pUnit, 0x80);
	}
	return 1;
}

//D2Client.0x6FAC79F0
uint32_t __fastcall sub_6FAC79F0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t local_8;

	if ((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0)))
	{
		iVar1 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c;
		if ((iVar1 != 0) &&
		    ((iVar3 = (int)*(short*)(iVar1 + 0xea), -1 < iVar3 && (iVar3 < *(int*)(iVar2 + 0xb6c)))))
		{
			if ((pUnit == nullptr) ||
			    ((pUnit->dwUnitType != 1 || (pUnit->pPlayerData == nullptr))))
			{
				local_8 = 0;
			}
			else
			{
				local_8 = (uint32_t)(uint8_t)pUnit->pPlayerData->szName[0xe];
			}
			iVar3 = iVar3 + local_8;
			if (((iVar3 < *(int*)(iVar2 + 0xb6c)) && (-1 < iVar3)) &&
			    (*(int*)(iVar2 + 0xb64) + iVar3 * 0x1a4 != 0))
			{
				if (pUnit != nullptr)
				{
					pUnit->dwFlags = pUnit->dwFlags | 0x40;
				}
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar1 + 4)) != 0)
				{
					sub_6FB3EBE0(pUnit, iVar3, 0, 0, 0, 0, a2, a3, 0);
					return 1;
				}
				sub_6FABABC0(pUnit, iVar3, a2, a3);
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC7B10
uint32_t __fastcall sub_6FAC7B10(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t local_8;

	if ((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0)))
	{
		iVar1 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c;
		if ((iVar1 != 0) &&
		    ((iVar3 = (int)*(short*)(iVar1 + 0xea), -1 < iVar3 && (iVar3 < *(int*)(iVar2 + 0xb6c)))))
		{
			if ((pUnit == nullptr) ||
			    ((pUnit->dwUnitType != 1 || (pUnit->pPlayerData == nullptr))))
			{
				local_8 = 0;
			}
			else
			{
				local_8 = (uint32_t)(uint8_t)pUnit->pPlayerData->szName[0xf];
			}
			iVar3 = iVar3 + local_8;
			if (((iVar3 < *(int*)(iVar2 + 0xb6c)) && (-1 < iVar3)) &&
			    (*(int*)(iVar2 + 0xb64) + iVar3 * 0x1a4 != 0))
			{
				if (pUnit != nullptr)
				{
					pUnit->dwFlags = pUnit->dwFlags | 0x40;
				}
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar1 + 4)) != 0)
				{
					sub_6FB3EBE0(pUnit, iVar3, 0, 0, 0, 0, a2, a3, 0);
					return 1;
				}
				sub_6FABABC0(pUnit, iVar3, a2, a3);
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC7C30
uint32_t __fastcall sub_6FAC7C30(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		iVar2 = D2COMMON_11039_CheckWeaponIsMissileBased(pUnit, (int*)(&a3));
		if ((iVar2 == 0) || (iVar2 == 0x1f))
		{
			iVar2 = (int)*(short*)(iVar1 + 0xea);
			if ((-1 < iVar2) &&
			    ((iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) &&
			        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4 != 0))))
			{
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar1 + 4)) != 0)
				{
					sub_6FB3EBE0(pUnit, iVar2, 0, 0, 0, 0, a2, a3, 0);
					return 1;
				}
				goto LAB_6fac7ccf;
			}
		}
		else if (((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
		         (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4 != 0))
		{
		LAB_6fac7ccf:
			sub_6FABABC0(pUnit, iVar2, a2, a3);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC7D60
uint32_t* __fastcall sub_6FAC7D60(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	D2UnitStrc* pDVar1;
	uint8_t bVar2;
	int iVar3;
	D2SkillStrc* pSkill;
	D2ActiveRoomStrc* pDVar4;
	int32_t DVar5;
	int iVar6;
	D2UnitStrc* pDVar7;
	uint32_t uVar8;
	int iVar9;
	uint32_t* puVar10;
	uint32_t uStack_78;
	D2ActiveRoomStrc** ppDStack_74;
	uint8_t uStack_70;
	uint8_t uStack_6f;
	uint8_t uStack_6e;
	uint8_t uStack_6d;
	int iStack_6c;
	int iStack_68;
	D2UnitStrc* local_64;
	int iStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	uint32_t uStack_34;
	int iStack_2c;

	pDynamicPath = pUnit->pDynamicPath;
	if ((pDynamicPath == nullptr) ||
	    (local_64 = pUnit, iVar3 = D2Common_10234(pDynamicPath), iVar3 == 0))
	{
		return nullptr;
	}
	iVar3 = 1;
	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 0xad);
	iStack_60 = SKILLS_GetSkillLevel(pUnit, pSkill, iVar3);
	pDVar4 = UNITS_GetRoom(pUnit);
	uVar8 = pUnit->dwUnitType;
	if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
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
	uVar8 = pUnit->dwUnitType;
	if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
	{
		DVar5 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
	}
	else
	{
		DVar5 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	ppDStack_74 = (D2ActiveRoomStrc**)0x1416080a;
	uStack_70 = 0x12;
	uStack_6f = 0x10;
	uStack_6e = 0xe;
	uStack_6d = 0xc;
	bVar2 = PATH_GetNewDirection(pDynamicPath);
	bVar2 = D2Common_11053(bVar2);
	ppDStack_74 = (D2ActiveRoomStrc**)
	    CONCAT31((*(uint8_t*)((uint8_t*)&ppDStack_74 + 1)), *(uint8_t*)((int)&ppDStack_74 + (uint32_t)bVar2));
	D2Common_11055(*(uint8_t*)((int)&ppDStack_74 + (uint32_t)bVar2), &iStack_6c, &iStack_68);
	iVar3 = iVar3 + iStack_6c;
	iVar9 = (int)DVar5 + iStack_68;
	if (pDVar4 != nullptr)
	{
		iVar6 = (pDVar4->tCoords).nSubtileX;
		if ((((iVar6 <= iVar3) && (iVar3 < (pDVar4->tCoords).nSubtileWidth + iVar6)) &&
		        (iVar6 = (pDVar4->tCoords).nSubtileY, iVar6 <= iVar9)) &&
		    (iVar9 < (pDVar4->tCoords).nSubtileHeight + iVar6))
			goto LAB_6fac7ee2;
		ppDStack_74 = nullptr;
		uStack_78 = 0;
		DUNGEON_GetAdjacentRoomsListFromRoom(pDVar4, &ppDStack_74, (int*)&uStack_78);
		uVar8 = 0;
		if (uStack_78 != 0)
		{
			do
			{
				pDVar4 = ppDStack_74[uVar8];
				if (((pDVar4 != nullptr) &&
				        (iVar6 = (pDVar4->tCoords).nSubtileX, iVar6 <= iVar3)) &&
				    ((iVar3 < (pDVar4->tCoords).nSubtileWidth + iVar6 &&
				        ((iVar6 = (pDVar4->tCoords).nSubtileY, iVar6 <= iVar9 &&
				                                                   (iVar9 < (pDVar4->tCoords).nSubtileHeight + iVar6))))))
				{
					pDVar4 = ppDStack_74[uVar8];
					goto LAB_6fac7ee2;
				}
				uVar8 = uVar8 + 1;
			} while (uVar8 < uStack_78);
		}
	}
	pDVar4 = nullptr;
LAB_6fac7ee2:
	iVar6 = DUNGEON_IsRoomInTown(pDVar4);
	pDVar1 = local_64;
	if (iVar6 != 0)
	{
		return nullptr;
	}
	puVar10 = &uStack_5c;
	for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*puVar10 = 0;
		puVar10 = puVar10 + 1;
	}
	uStack_5c = 0x25;
	iStack_40 = iVar3 + iStack_6c * 2;
	iStack_3c = iVar9 + iStack_68 * 2;
	pDStack_58 = local_64;
	uStack_34 = 3;
	iStack_2c = iStack_60;
	uStack_4c = 0x8f;
	iStack_48 = iVar3;
	iStack_44 = iVar9;
	pDVar7 = sub_6FB3E070(&uStack_5c);
	sub_6FB55820(0x726, pDVar1, 0.0, 0.0, 0);
	return &pDVar7->dwUnitType;
}

//D2Client.0x6FAC7F90
uint32_t __fastcall sub_6FAC7F90(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;

	if (((-1 < a2) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar1 + 0xba0))) && (iVar2 = *(int*)(iVar1 + 0xb98) + a2 * 0x23c, iVar2 != 0))
	{
		iVar2 = (int)*(short*)(iVar2 + 0xee);
		if ((-1 < iVar2) && (iVar2 < *(int*)(iVar1 + 0xb6c)))
		{
			sub_6FABABC0(pUnit, iVar2, a2, a3);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC7FF0
uint32_t __fastcall sub_6FAC7FF0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	D2UnitStrc* pMissile;
	uint32_t* puVar2;
	int iVar3;
	uint32_t* puVar4;
	int local_68;
	int local_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	int iStack_2c;

	if (((-1 < a2) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar1 + 0xba0))) && (iVar3 = *(int*)(iVar1 + 0xb98) + a2 * 0x23c, iVar3 != 0))
	{
		local_60 = (int)*(short*)(iVar3 + 0xea);
		if ((-1 < local_60) && (local_60 < *(int*)(iVar1 + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			iVar1 = sub_6FABA950(pUnit, &local_68, &local_64);
			if (iVar1 != 0)
			{
				iVar1 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 100), a2, a3);
				iVar1 = iVar1 + -3;
				if (iVar1 < 2)
				{
					iVar1 = 2;
				}
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
				uStack_4c = 0xbf;
				pDStack_58 = pUnit;
				iStack_30 = a2;
				pMissile = sub_6FB3E070(&uStack_5c);
				if (pMissile != nullptr)
				{
					sub_6FB296E0((int)pMissile);
					puVar2 = sub_6FAA4280(pMissile, 1, 1, 0xff, 0xff, 0, 0);
					if (puVar2 != nullptr)
					{
						sub_6FAA43A0((int)puVar2, iVar1);
						pMissile->dwInteractGUID = (uint32_t)puVar2;
					}
					MISSILE_SetStreamMissile(pMissile, (uint16_t)local_60);
					MISSILE_SetStreamRange(pMissile, (short)iVar1);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC8150
uint32_t __fastcall sub_6FAC8150(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint32_t uVar1;
	int iVar2;
	int32_t DVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	int iVar7;
	uint32_t* puVar8;
	uint32_t uStack_78;
	int32_t DStack_74;
	int local_70;
	int local_6c;
	int local_68;
	int local_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((a2 < 0) || (iVar2 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar2 + 0xba0) <= a2)) || (iVar7 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar7 == 0)) ||
	    ((local_68 = (int)*(short*)(iVar7 + 0xee), local_68 < 0 ||
	                                                   (*(int*)(iVar2 + 0xb6c) <= local_68))))
	{
		return 0;
	}
	local_64 = a2;
	iVar2 = sub_6FABA950(pUnit, &local_70, &local_6c);
	if (iVar2 == 0)
	{
		return 0;
	}
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
	iVar2 = local_70 - iVar2;
	uVar1 = pUnit->dwUnitType;
	local_60 = iVar2;
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
	iVar7 = local_6c - (int)DVar3;
	uStack_78 = UNITS_GetDistanceToCoordinates(pUnit, local_70, local_6c);
	if ((int)uStack_78 < 2)
	{
		uStack_78 = 1;
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
		DStack_74 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_74 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_74 + 2)) = 0;
	}
	else
	{
		DStack_74 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	puVar8 = &uStack_5c;
	for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	iStack_30 = local_64;
	uStack_2c = a3;
	iStack_3c = iVar7 * 5;
	iStack_4c = local_68;
	uStack_5c = 3;
	iStack_44 = (iVar7 * 2) / (int)uStack_78 + (int)DStack_74;
	iStack_40 = local_60 * 5;
	pDStack_58 = pUnit;
	iStack_48 = (iVar2 * 2) / (int)uStack_78 + iVar4;
	pDVar5 = sub_6FB3E070(&uStack_5c);
	if (pDVar5 != nullptr)
	{
		iVar2 = UNITS_GetDirectionToCoords(pUnit, local_70, local_6c);
		D2COMMON_10160_PathUpdateDirection(pDVar5->pDynamicPath, (uint8_t)iVar2);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC8370
uint32_t __fastcall sub_6FAC8370(D2UnitStrc* pUnit2, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	D2SkillStrc* pSkill;
	D2UnitStrc* pUnit;
	int iVar2;

	pSkill = UNITS_GetUsedSkill(pUnit2);
	if (pSkill == nullptr)
	{
		return 0;
	}
	pUnit = sub_6FB296A0((int)pUnit2);
	if (pUnit == nullptr)
	{
		return 0;
	}
	iVar2 = D2COMMON_11017_CheckUnitIfConsumeable(pUnit, 0);
	if (iVar2 == 0)
	{
		return 0;
	}
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
	if ((uVar1 != 2) && (((int)uVar1 < 4 || (5 < (int)uVar1))))
	{
		if (pUnit->pDynamicPath != nullptr)
		{
			iVar2 = PATH_GetYPosition(pUnit->pDynamicPath);
			SKILLS_SetParam2(pSkill, iVar2);
			return 1;
		}
		SKILLS_SetParam2(pSkill, 0);
		return 1;
	}
	SKILLS_SetParam2(pSkill, (int)(*(int32_t*)&pUnit->pDynamicPath->tTargetCoord));
	return 1;
}

//D2Client.0x6FAC8440
uint32_t __fastcall sub_6FAC8440(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	D2SkillStrc* pSkill;
	int iVar2;
	uint32_t* puVar3;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0)) &&
	    (((iVar1 = sub_6FABF670(pUnit, a2), -1 < iVar1 &&
	                                            (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	        (pSkill = UNITS_GetUsedSkill(pUnit), pSkill != nullptr))))
	{
		puVar3 = &uStack_5c;
		for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		uStack_5c = 0x2001;
		uStack_2c = a3;
		pDStack_58 = pUnit;
		iStack_4c = iVar1;
		iStack_30 = a2;
		iStack_48 = SKILLS_GetParam1(pSkill);
		iStack_44 = SKILLS_GetParam2(pSkill);
		sub_6FB3E070(&uStack_5c);
		SKILLS_SetParam1(pSkill, 0);
		SKILLS_SetParam2(pSkill, 0);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC8530
uint32_t __fastcall sub_6FAC8530(D2UnitStrc* pUnit2, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	D2SkillStrc* pSkill;
	D2UnitStrc* pUnit;
	D2UnitStrc* pDVar2;
	int iVar3;
	int32_t nPar2;

	pSkill = UNITS_GetUsedSkill(pUnit2);
	if (pSkill == nullptr)
	{
		return 0;
	}
	pUnit = sub_6FB296A0((int)pUnit2);
	if (pUnit == nullptr)
	{
		return 0;
	}
	pDVar2 = CUNIT_GetPlayer();
	if (pUnit2 == pDVar2)
	{
		iVar3 = D2COMMON_11021(pUnit);
		if (iVar3 == 0)
		{
			return 0;
		}
	}
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
	SKILLS_SetParam1(pSkill, iVar3);
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

//D2Client.0x6FAC85F0
uint32_t __fastcall sub_6FAC85F0(int a1, int a2, uint32_t a3, int a4, int a5, int a6)
{
	int iVar1;
	short sVar2;
	uint64_t uVar3;
	int iVar4;
	uint32_t uVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	uint32_t* puVar8;
	D2UnitStrc* pDVar9;
	int iVar10;
	uint32_t local_5c[4];
	int local_4c;
	int local_48;
	int local_44;
	int local_40;
	int local_3c;
	int local_30;
	uint32_t local_2c;

	if ((((((a2 < 0) ||
	           (iVar10 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar10 + 0xba0) <= a2)) ||
	          (iVar1 = *(int*)(iVar10 + 0xb98) + a2 * 0x23c, iVar1 == 0)) ||
	         (((iVar7 = (int)*(short*)(iVar1 + 0xea), iVar7 < 0 || (*(int*)(iVar10 + 0xb6c) <= iVar7)) || ((a4 == 0 || ((a5 == 0 || (a6 < 0)))))))) ||
	        (*(int*)(iVar10 + 0xa80) <= a6)) ||
	    (((iVar4 = (int)*(short*)(*(int*)(iVar10 + 0xa78) + 0x18 + a6 * 0x1a8), iVar4 < 0 ||
	                                                                                (*(int*)(iVar10 + 0xa98) <= iVar4)) ||
	        (iVar10 = *(int*)(iVar10 + 0xa90) + iVar4 * 0x134, iVar10 == 0))))
	{
		return 0;
	}
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x40;
	}
	puVar8 = local_5c;
	for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	uVar3 = (uint64_t) * (uint32_t*)(a1 + 0x20) * 0x6ac690c5 + (uint64_t) * (uint32_t*)(a1 + 0x24);
	*(uint64_t*)(a1 + 0x20) = uVar3;
	local_5c[0] = 0x2021;
	local_40 = (int)((uVar3 & 0xffffffff) % 3) + -1 + a4;
	uVar3 = (uint64_t) * (uint32_t*)(a1 + 0x20) * 0x6ac690c5 + (uint64_t) * (uint32_t*)(a1 + 0x24);
	*(uint64_t*)(a1 + 0x20) = uVar3;
	local_48 = a4;
	local_44 = a5;
	local_3c = (int)((uVar3 & 0xffffffff) % 3) + -1 + a5;
	local_2c = a3;
	uVar5 = (uint32_t) * (uint8_t*)(iVar10 + 5);
	local_5c[1] = a1;
	local_5c[2] = a1;
	local_4c = iVar7;
	local_30 = a2;
	if ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 8) & uVar5) == 0)
	{
		if ((uVar5 & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0xc)) == 0)
		{
			sub_6FABD8A0(a1, local_5c, 2, 2);
			iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c);
			if (iVar7 < iVar10)
			{
				iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar7 * 0x1a4;
			}
			else
			{
				iVar7 = 0;
			}
			sVar2 = *(short*)(iVar7 + 0x1a);
			if ((sVar2 < 1) || (iVar10 <= sVar2))
				goto LAB_6fac883e;
			iVar7 = 3;
			iVar10 = 1;
			local_4c = (int)sVar2;
		}
		else
		{
			sub_6FABD8A0(a1, local_5c, 3, 3);
			iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c);
			if (iVar7 < iVar10)
			{
				iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar7 * 0x1a4;
			}
			else
			{
				iVar7 = 0;
			}
			sVar2 = *(short*)(iVar7 + 0x18);
			if ((sVar2 < 1) || (iVar10 <= sVar2))
				goto LAB_6fac883e;
			iVar7 = 4;
			iVar10 = 2;
			local_4c = (int)sVar2;
		}
	}
	else
	{
		iVar7 = 1;
		iVar10 = 0;
	}
	sub_6FABD8A0(a1, local_5c, iVar10, iVar7);
LAB_6fac883e:
	local_48 = a4;
	local_44 = a5;
	iVar10 = (int)*(short*)(iVar1 + 0xec);
	pDVar9 = nullptr;
	if ((0 < iVar10) && (iVar10 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		local_4c = iVar10;
		pDVar9 = sub_6FB3E070(local_5c);
	}
	iVar10 = (int)*(short*)(iVar1 + 0xee);
	if ((0 < iVar10) && (iVar10 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		local_2c = 2;
		local_4c = iVar10;
		sub_6FB3E070(local_5c);
	}
	pDVar6 = sub_6FB296A0(a1);
	if (((pDVar6 == nullptr) && (pDVar9 != nullptr)) &&
	    (0 < *(short*)(iVar1 + 0x10a)))
	{
		sub_6FB55820((int)*(short*)(iVar1 + 0x10a), pDVar9, 0.0, 0.0, 0);
	}
	return 1;
}

//D2Client.0x6FAC88F0
void __fastcall sub_6FAC88F0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	int iVar1;
	int iVar2;
	int iVar3;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return;
	}
	iVar1 = SKILLS_GetParam1(pSkill);
	iVar2 = SKILLS_GetParam2(pSkill);
	iVar3 = SKILLS_GetParam3(pSkill);
	sub_6FAC85F0((int)pUnit, a2, a3, iVar1, iVar2, iVar3);
}

//D2Client.0x6FAC8940
uint32_t __fastcall sub_6FAC8940(int a1, int a2, uint32_t a3, int a4, int a5, int a6)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t local_5c[4];
	int local_4c;
	int local_48;
	int local_44;
	int local_30;
	uint32_t local_2c;

	if ((((((-1 < a2) &&
	           (iVar4 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar4 + 0xba0))) &&
	          (iVar1 = *(int*)(iVar4 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	         ((iVar5 = (int)*(short*)(iVar1 + 0xea), -1 < iVar5 && (iVar5 < *(int*)(iVar4 + 0xb6c))))) &&
	        ((-1 < a6 &&
	            ((a6 < *(int*)(iVar4 + 0xa80) && (*(int*)(iVar4 + 0xa78) + a6 * 0x1a8 != 0)))))) &&
	    ((a4 != 0 && (a5 != 0))))
	{
		if (a1 != 0)
		{
			*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x40;
		}
		puVar6 = local_5c;
		for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*puVar6 = 0;
			puVar6 = puVar6 + 1;
		}
		local_48 = a4;
		local_5c[0] = 0x2001;
		local_44 = a5;
		local_2c = a3;
		local_5c[1] = a1;
		local_4c = iVar5;
		local_30 = a2;
		pDVar2 = sub_6FB3E070(local_5c);
		iVar4 = (int)*(short*)(iVar1 + 0xee);
		if ((0 < iVar4) && (iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			local_2c = 2;
			local_4c = iVar4;
			sub_6FB3E070(local_5c);
		}
		iVar4 = (int)*(short*)(iVar1 + 0xec);
		if (pDVar2 != nullptr)
		{
			if ((0 < iVar4) && (iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
			{
				sub_6FB35FD0(pDVar2, iVar4, 0, 2, 0);
			}
			pDVar3 = sub_6FB296A0(a1);
			if ((pDVar3 == nullptr) && (0 < *(short*)(iVar1 + 0x10a)))
			{
				sub_6FB55820((int)*(short*)(iVar1 + 0x10a), pDVar2, 0.0, 0.0, 0);
			}
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC8AE0
void __fastcall sub_6FAC8AE0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	int iVar1;
	int iVar2;
	int iVar3;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return;
	}
	iVar1 = SKILLS_GetParam1(pSkill);
	iVar2 = SKILLS_GetParam2(pSkill);
	iVar3 = SKILLS_GetParam3(pSkill);
	sub_6FAC8940((int)pUnit, a2, a3, iVar1, iVar2, iVar3);
}

//D2Client.0x6FAC8B30
uint32_t __fastcall sub_6FAC8B30(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2ActiveRoomStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uStack_14;
	D2ActiveRoomStrc** ppDStack_10;
	int iStack_c;
	int iStack_8;
	int local_4;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (local_4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, local_4 == 0))
	{
		return 0;
	}
	pDVar1 = UNITS_GetRoom(pUnit);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	iVar2 = sub_6FABA950(pUnit, &iStack_8, &iStack_c);
	if (iVar2 != 0)
	{
		iVar2 = (pDVar1->tCoords).nSubtileX;
		if (((iStack_8 < iVar2) || ((pDVar1->tCoords).nSubtileWidth + iVar2 <= iStack_8)) ||
		    ((iVar2 = (pDVar1->tCoords).nSubtileY, iStack_c < iVar2 ||
		                                               ((pDVar1->tCoords).nSubtileHeight + iVar2 <= iStack_c))))
		{
			ppDStack_10 = nullptr;
			uStack_14 = 0;
			DUNGEON_GetAdjacentRoomsListFromRoom(pDVar1, &ppDStack_10, (int*)&uStack_14);
			uVar3 = 0;
			if (uStack_14 == 0)
			{
				return 0;
			}
			while (((pDVar1 = ppDStack_10[uVar3], pDVar1 == nullptr ||
			                                          (iVar2 = (pDVar1->tCoords).nSubtileX, iStack_8 < iVar2)) ||
			        (((pDVar1->tCoords).nSubtileWidth + iVar2 <= iStack_8 ||
			            ((iVar2 = (pDVar1->tCoords).nSubtileY, iStack_c < iVar2 ||
			                                                       ((pDVar1->tCoords).nSubtileHeight + iVar2 <= iStack_c)))))))
			{
				uVar3 = uVar3 + 1;
				if (uStack_14 <= uVar3)
				{
					return 0;
				}
			}
			pDVar1 = ppDStack_10[uVar3];
		}
		if (pDVar1 == nullptr)
		{
			return 0;
		}
		if ((((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(local_4 + 5)) == 0) &&
		    (iVar2 = DUNGEON_IsRoomInTown(pDVar1), iVar2 != 0))
		{
			return 0;
		}
		return 1;
	}
	return 0;
}
