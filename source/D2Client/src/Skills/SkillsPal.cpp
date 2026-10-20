#include "Skills/SkillsPal.h"

#include "Core/WinMain.h"
#include "Engine/Gfx.h"
#include "Engine/Particle.h"
#include "Game/Env.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Skills/SkillsAma.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/EditBox.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB77BC4
uint32_t dword_6FB77BC4 = 1;
//D2Client.0x6FBB19C8
int32_t dword_6FBB19C8;
//D2Client.0x6FBB19CC
int32_t dword_6FBB19CC;
//D2Client.0x6FBB19E8
uint32_t dword_6FBB19E8;
//D2Client.0x6FBB19EC
int32_t dword_6FBB19EC;
//D2Client.0x6FBB1A00
uint8_t byte_6FBB1A00;
//D2Client.0x6FBB1A04
uint8_t byte_6FBB1A04;
//D2Client.0x6FBB1A18
int32_t dword_6FBB1A18;
//D2Client.0x6FBB1A1C
int32_t dword_6FBB1A1C;
//D2Client.0x6FBB1A20
int32_t dword_6FBB1A20;
//D2Client.0x6FBB1A2C
int32_t dword_6FBB1A2C;
//D2Client.0x6FBB1A30
int32_t dword_6FBB1A30;

//D2Client.0x6FAC9820
uint32_t __fastcall sub_6FAC9820(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	short sVar1;
	D2DynamicPathStrc* pDynamicPath;
	D2SkillStrc* pSkill;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	uint64_t uVar7;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	if ((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2))
	{
		return 0;
	}
	iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c;
	if (iVar6 == 0)
	{
		return 0;
	}
	iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
	if (((iVar2 == a2) && (pDVar3 = CUNIT_GetPlayer(), pUnit == pDVar3)) &&
	    (uVar4 = SKILLS_GetFlags(pSkill), (uVar4 & 1) != 0))
	{
		return 0;
	}
	pDynamicPath = pUnit->pDynamicPath;
	if (pDynamicPath == nullptr)
	{
		return (uint32_t)pDynamicPath;
	}
	pDVar3 = sub_6FB296A0((int)pUnit);
	if (((pUnit->dwUnitType == 0) && (pDVar3 != nullptr)) &&
	    (iVar2 = UNITS_IsInMeleeRange(pUnit, pDVar3, 0), iVar2 != 0))
	{
		uVar4 = sub_6FABDA60(pUnit, &pDVar3->dwUnitType);
		return uVar4;
	}
	if (pUnit->dwUnitType == 0)
	{
		sVar1 = *(short*)(iVar6 + 0x102);
		if (sVar1 < 1)
			goto LAB_6fac9936;
		uVar4 = (uint32_t)sVar1;
	}
	else if ((pUnit->dwUnitType != 1) ||
	         (uVar4 = sub_6FB409E0((int)pUnit, a2), (int)uVar4 < 1))
		goto LAB_6fac9936;
	sub_6FB55820(uVar4, pUnit, 0.0, 0.0, 0);
LAB_6fac9936:
	if ((pDVar3 == nullptr) || (iVar6 = STATES_CheckState(pDVar3, 0x36), iVar6 != 0))
	{
		SKILLS_SetParam1(pSkill, 6);
		uVar4 = 0;
	}
	else
	{
		SKILLS_SetParam1(pSkill, pDVar3->dwUnitType);
		uVar4 = pDVar3->dwUnitId;
	}
	SKILLS_SetParam2(pSkill, uVar4);
	iVar2 = 0x100;
	SKILLS_SetParam4(pSkill, 7);
	iVar6 = pUnit->dwClassId;
	if (pUnit->dwUnitType == 0)
	{
		if (((-1 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8))) &&
		    (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + iVar6 * 0xc4, iVar6 != 0))
		{
			iVar2 = (uint32_t) * (uint8_t*)(iVar6 + 0x41) << 8;
		}
	}
	else if (((-1 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
	         (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar6 * 0x1a8, iVar5 != 0))
	{
		iVar2 = (int)*(short*)(iVar5 + 0x34) << 8;
		if (iVar6 == 0xd3)
		{
			SKILLS_SetParam4(pSkill, 0xf);
		}
		PATH_SetNewDistance(pDynamicPath, 0x1e);
	}
	iVar6 = STATLIST_UnitGetStatValue(pUnit, 0x43, 0);
	if (iVar6 < 0x33)
	{
		iVar6 = 0x32;
	}
	if ((a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)) &&
	    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar5 != 0))
	{
		iVar5 = *(int*)(iVar5 + 0x148);
	}
	else
	{
		iVar5 = 0;
	}
	uVar4 = iVar6 + iVar5;
	if (iVar2 < 0x100001)
	{
		if ((int)uVar4 < 0x10001)
		{
			iVar2 = (int)(uVar4 * iVar2) / 100;
		}
		else if ((int)(uVar4 & 0xfffffff0) < 0x640)
		{
			uVar7 = D2C_alldiv((uint32_t)((int64_t)(int)uVar4 * (int64_t)iVar2),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar4 * (int64_t)iVar2) >> 0x20), 100, 0);
			iVar2 = (int)uVar7;
		}
		else
		{
			iVar2 = ((int)uVar4 / 100) * iVar2;
		}
	}
	else if (iVar2 < 0x640)
	{
		uVar7 = D2C_alldiv((uint32_t)((int64_t)(int)uVar4 * (int64_t)iVar2),
		    (uint32_t)((uint64_t)((int64_t)(int)uVar4 * (int64_t)iVar2) >> 0x20), 100, 0);
		iVar2 = (int)uVar7;
	}
	else
	{
		iVar2 = (iVar2 / 100) * uVar4;
	}
	PATH_SetVelocity(pDynamicPath, iVar2, __FILE__, __LINE__);
	D2Common_10142(pDynamicPath, pUnit, 0);
	if (pDVar3 != nullptr)
	{
		sub_6FB29010(pUnit, 1);
	}
	SKILLS_SetFlags(pSkill, 0x1001);
	SKILLS_SetParam3(pSkill, 0);
	sub_6FABDD20(pUnit);
	return 1;
}

//D2Client.0x6FAC9B50
uint32_t __fastcall sub_6FAC9B50(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2SkillStrc* pSkill;
	uint32_t uVar1;
	D2AnimSeqTxt* pDVar2;
	int iVar3;
	uint32_t uVar4;
	int32_t nY;
	int iVar5;
	D2UnitStrc* pDVar6;
	int iStack_10;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	uVar1 = SKILLS_GetFlags(pSkill);
	iVar5 = 0xf;
	pDVar2 = DATATBLS_GetMonSeqTxtRecordFromUnit(pUnit);
	if (pDVar2 != nullptr)
	{
		iVar5 = DATATBLS_GetSeqFrameCount(pUnit);
	}
	pDVar2 = DATATBLS_GetMonSeqTxtRecordFromUnit(pUnit);
	if (pDVar2 != nullptr)
	{
		iVar3 = DATATBLS_GetSeqFrameCount(pUnit);
		iStack_10 = 0;
		if (0 < iVar3)
		{
			do
			{
				if (pDVar2->nEvent == ANIMSEQ_EVENT_NONE)
				{
					iStack_10 = iStack_10 + -1;
					goto LAB_6fac9bba;
				}
				iStack_10 = iStack_10 + 1;
			} while (iStack_10 < iVar3);
		}
	}
	iStack_10 = 7;
LAB_6fac9bba:
	if ((pUnit != nullptr) &&
	    (((pUnit->dwUnitType == 0 || (pUnit->dwUnitType == 1)) && (pUnit->nActionFrame == 3))))
	{
		sub_6FB50A30(pUnit, pUnit->dwAnimMode, 0);
		return 0;
	}
	pDVar6 = nullptr;
	iVar3 = SKILLS_GetParam1(pSkill);
	uVar4 = SKILLS_GetParam2(pSkill);
	if (iVar3 != 6)
	{
		pDVar6 = sub_6FB269F0(uVar4, iVar3);
	}
	if ((uVar1 & 1) == 0)
	{
		SKILLS_SetFlags(pSkill, 0);
		SKILLS_SetParam1(pSkill, 0);
		SKILLS_SetParam2(pSkill, 0);
		pUnit->dwFrameCountPrecise = (iVar5 - (pUnit->dwSeqFrame >> 8)) * 0x100;
		if ((pDVar6 == nullptr) &&
		    (pDVar6 = sub_6FABB890(pUnit, 0, 0, 3, 3, 0xffffffff, nullptr),
		        pDVar6 == nullptr))
		{
			return 0;
		}
		uVar1 = pDVar6->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
		uVar1 = pDVar6->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar5 = pDVar6->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar6->pDynamicPath == nullptr)
		{
			iVar5 = 0;
		}
		else
		{
			iVar5 = PATH_GetXPosition(pDVar6->pDynamicPath);
		}
		D2Common_10216(pUnit->pDynamicPath, iVar5, (int)nY, 0);
		return 1;
	}
	if ((pDVar6 != nullptr) && (iVar3 = UNITS_IsInMeleeRange(pUnit, pDVar6, 0), iVar3 != 0))
	{
		SKILLS_SetFlags(pSkill, 0);
		UNITS_SetAnimationFrame(pUnit, iStack_10 + 1);
		pUnit->dwFrameCountPrecise = iVar5 << 8;
		return 1;
	}
	if ((uVar1 & 2) == 0)
	{
		if (iStack_10 <= pUnit->dwSeqFrame >> 8)
		{
			UNITS_SetAnimationFrame(pUnit, 0);
			pUnit->dwFrameCountPrecise = iVar5 << 8;
			SKILLS_SetFlags(pSkill, 1);
		}
		pUnit->dwFlags = pUnit->dwFlags & 0xffffffbf;
		iVar5 = SKILLS_GetParam3(pSkill);
		if (iVar5 < 2)
		{
			iVar5 = iVar5 + 1;
		}
		SKILLS_SetParam3(pSkill, iVar5);
		return 1;
	}
	pDVar6 = sub_6FABB890(pUnit, 0, 0, 3, 3, uVar4, nullptr);
	if ((pDVar6 != nullptr) && (iVar5 = UNITS_IsInMeleeRange(pUnit, pDVar6, 0), iVar5 != 0))
	{
		SKILLS_SetFlags(pSkill, 0);
		SKILLS_SetParam1(pSkill, pDVar6->dwUnitType);
		SKILLS_SetParam2(pSkill, pDVar6->dwUnitId);
		return 1;
	}
	SKILLS_SetFlags(pSkill, 0);
	if ((pUnit == nullptr) || (pUnit->dwUnitType != 1))
		goto LAB_6fac9d23;
	iVar5 = pUnit->dwClassId;
	if (iVar5 < 0)
	{
	LAB_6fac9d0c:
		iVar5 = -1;
	}
	else
	{
		if ((iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
		    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar5 * 0x1a8, iVar3 != 0))
		{
			iVar5 = (int)*(short*)(iVar3 + 2);
		}
		if ((iVar5 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar5))
			goto LAB_6fac9d0c;
	}
	if ((iVar5 == 0x1b4) || (iVar5 == 0x1b9))
	{
		return 1;
	}
LAB_6fac9d23:
	pUnit->dwFrameCountPrecise = 0x100;
	return 1;
}

//D2Client.0x6FAC9E50
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAC9E50(D2UnitStrc* pUnit)
{
	D2SkillStrc* pSkill;
	uint32_t uVar1;
	int in_EDX;

	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, in_EDX);
	uVar1 = SKILLS_GetFlags(pSkill);
	if ((uVar1 & 1) != 0)
	{
		SKILLS_SetFlags(pSkill, uVar1 | 2);
	}
	STATES_ToggleState(pUnit, 0x36, 0);
}

//D2Client.0x6FAC9E80
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAC9E80(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	int iVar2;
	int in_EDX;

	if (pUnit != nullptr)
	{
		iVar1 = MISSILE_GetTotalFrames(pUnit);
		if (0x4d < iVar1)
		{
			iVar1 = 0x4d;
			MISSILE_SetTotalFrames(pUnit, 0x4d);
			MISSILE_SetCurrentFrame(pUnit, 0x4d);
		}
		pDynamicPath = pUnit->pDynamicPath;
		iVar2 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
		SEED_InitLowSeed(&pUnit->pSeed, iVar2 + in_EDX);
		PATH_SetType(pDynamicPath, 10);
		PATH_SetNewDistance(pDynamicPath, (uint8_t)iVar1);
		D2Common_10142(pDynamicPath, pUnit, 0);
	}
}

//D2Client.0x6FAC9EE0
uint32_t __fastcall sub_6FAC9EE0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint32_t* puVar5;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int aiStack_3c[3];
	int iStack_30;
	int iStack_2c;
	code* pcStack_8;
	int iStack_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar3 != 0))
	{
		iVar2 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x138), a2, a3);
			puVar5 = &uStack_5c;
			for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar5 = 0;
				puVar5 = puVar5 + 1;
			}
			uVar1 = pUnit->dwUnitType;
			uStack_5c = 0x21;
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
			pcStack_8 = (code*)(sub_6FAC9E80);
			iStack_4c = iVar2;
			iStack_30 = a2;
			iVar2 = sub_6FABA950(pUnit, &iStack_40, aiStack_3c);
			if (iVar2 != 0)
			{
				iVar2 = 0;
				if (0 < iVar3)
				{
					do
					{
						iStack_4 = iVar2;
						sub_6FB3E070(&uStack_5c);
						iVar2 = iVar2 + 1;
					} while (iVar2 < iVar3);
				}
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FACA050
uint32_t __fastcall sub_6FACA050(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	short sVar2;
	int iVar3;
	D2StatListStrc* pDVar4;
	uint32_t nUnitType;
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
		pDVar4 = STATLIST_AllocStatList(nullptr, 2, 0x15, nUnitType, nUnitGUID);
		if (pDVar4 == nullptr)
		{
			return 0;
		}
		D2COMMON_10475_PostStatToStatList(pUnit, pDVar4, 1);
		STATLIST_SetStatRemoveCallback(pStatList, (StatListRemoveCallback)(pfStatRemove));
		STATLIST_SetState(pDVar4, 0xc);
		STATES_ToggleState(pUnit, 0xc, 1);
		return 1;
	}
	UNITS_SetAnimationFrame(pUnit, 8);
	pUnit->dwFrameCountPrecise = 0x500;
	D2COMMON_10476(pDVar4, 7);
	return 1;
}

//D2Client.0x6FACA170
void __fastcall sub_6FACA170(D2UnitStrc* pUnit, int a2)
{
	int iVar1;

	if ((((pUnit != nullptr) && (pUnit->dwUnitType == 3)) && (a2 != 0)) &&
	    (((iVar1 = pUnit->dwClassId, -1 < iVar1 &&
	                                     (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	        (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))))
	{
		UNITS_SetAnimationSpeed(pUnit, (int)((int64_t)((uint64_t) * (uint8_t*)(iVar1 + 0x178) << 8) /
		                                     (int64_t)a2));
	}
}

//D2Client.0x6FACA1D0
uint32_t* __fastcall sub_6FACA1D0(D2UnitStrc* pUnit2, int a2, int a3)
{
	uint64_t DVar1;
	int iVar2;
	D2UnitStrc* pUnit;
	int iVar3;
	uint32_t* puVar4;
	int local_70;
	int local_6c;
	int local_68;
	int local_64;
	uint32_t local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	int iStack_2c;
	int iStack_10;

	if (((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0))) && (iVar3 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar3 != 0))
	{
		local_6c = (int)*(short*)(iVar3 + 0xea);
		if ((-1 < local_6c) && (local_6c < *(int*)(iVar2 + 0xb6c)))
		{
			local_70 = (int)*(short*)(iVar3 + 0xec);
			if ((local_70 < 0) || (*(int*)(iVar2 + 0xb6c) <= local_70))
			{
				local_70 = -1;
			}
			iVar2 = sub_6FABA950(pUnit2, &local_68, &local_64);
			if (iVar2 != 0)
			{
				if (-1 < local_70)
				{
					DVar1 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit2->pSeed).nHighSeed);
					local_60 = (*(uint32_t*)((uint8_t*)&DVar1 + 0)) & 1;
					(*(uint64_t*)&pUnit2->pSeed) = DVar1;
					if (((uint64_t)DVar1 & 1) != 0)
					{
						local_6c = local_70;
					}
				}
				iVar2 = SKILLS_EvaluateSkillFormula(pUnit2, *(uint32_t*)(iVar3 + 0x138), a2, a3);
				if (iVar2 < 1)
				{
					iVar2 = 1;
				}
				puVar4 = &uStack_5c;
				for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*puVar4 = 0;
					puVar4 = puVar4 + 1;
				}
				iStack_4c = local_6c;
				iStack_40 = local_68;
				uStack_5c = 0x8020;
				iStack_2c = a3;
				iStack_3c = local_64;
				pDStack_58 = pUnit2;
				pDStack_54 = pUnit2;
				iStack_30 = a2;
				iStack_10 = iVar2;
				pUnit = sub_6FB3E070(&uStack_5c);
				if (((pUnit != nullptr) && (pUnit->dwUnitType == 3)) &&
				    ((iVar2 != 0 &&
				        (((iVar3 = pUnit->dwClassId, -1 < iVar3 &&
				                                         (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
				            (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar3 * 0x1a4, iVar3 != 0))))))
				{
					UNITS_SetAnimationSpeed(pUnit, (int)((int64_t)((uint64_t) * (uint8_t*)(iVar3 + 0x178) << 8) /
					                                     (int64_t)iVar2));
				}
				iVar2 = STATES_CheckState(pUnit2, 0xc);
				if (iVar2 != 0)
				{
					if (pUnit2->pAnimSeq != nullptr)
					{
						UNITS_SetAnimationFrame(pUnit2, 8);
						pUnit2->dwFrameCountPrecise = 0x500;
						return &pUnit->dwUnitType;
					}
					pUnit2->nSeqCurrentFramePrecise =
					    (pUnit2->nSeqCurrentFramePrecise & 0xffffff00U) - 0x200;
				}
				return &pUnit->dwUnitType;
			}
		}
	}
	return nullptr;
}

//D2Client.0x6FACA3B0
bool __fastcall sub_6FACA3B0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint32_t* puVar1;

	puVar1 = sub_6FACA1D0(pUnit, a2, a3);
	return puVar1 != nullptr;
}

//D2Client.0x6FACA3D0
uint32_t __fastcall sub_6FACA3D0(D2UnitStrc* pUnit2, int a2, int32_t a3)
{
	D2UnitStrc* pUnit;
	int iVar1;
	int32_t nY1;
	int iVar2;
	D2ActiveRoomStrc* pDVar3;
	uint32_t uVar4;
	int iStack_4;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		return 0;
	}
	pUnit = sub_6FB296A0((int)pUnit2);
	if (pUnit == nullptr)
	{
		return 0;
	}
	iVar1 = SKILLS_EvaluateSkillFormula(pUnit2, *(uint32_t*)(iVar1 + 100), a2, (int)a3);
	uVar4 = pUnit->dwUnitType;
	if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
	{
		a3 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&a3 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&a3 + 2)) = 0;
	}
	else
	{
		a3 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	uVar4 = pUnit->dwUnitType;
	if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
	{
		iStack_4 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iStack_4 = 0;
	}
	else
	{
		iStack_4 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar4 = pUnit2->dwUnitType;
	if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
	{
		nY1 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&nY1 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&nY1 + 2)) = 0;
	}
	else
	{
		nY1 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	uVar4 = pUnit2->dwUnitType;
	if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
	{
		iVar2 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		iVar2 = 0;
	}
	else
	{
		iVar2 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	iVar2 = PATH_ComputeSquaredDistance(iVar2, (int)nY1, iStack_4, (int)a3);
	if (iVar2 <= iVar1 * iVar1)
	{
		if (((-1 < (int)pUnit->dwUnitType) && ((int)pUnit->dwUnitType < 2)) &&
		    (((pDVar3 = UNITS_GetRoom(pUnit2), pDVar3 == nullptr ||
		                                           (((iVar1 = DUNGEON_IsRoomInTown(pDVar3), iVar1 != 0 ||
		                                                                                        (pDVar3 = UNITS_GetRoom(pUnit), pDVar3 == nullptr)) ||
		                                               (iVar1 = DUNGEON_IsRoomInTown(pDVar3), iVar1 != 0)))) ||
		        (uVar4 = sub_6FB29D80(pUnit2, pUnit), uVar4 == 0))))
		{
			return 0;
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FACA570
uint32_t __fastcall sub_6FACA570(D2UnitStrc* pUnit, int a2, int a3)
{
	int nMissileId;
	int iVar1;
	int iVar2;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 != 0))
	{
		nMissileId = sub_6FABF670(pUnit, a2);
		if ((-1 < nMissileId) && (nMissileId < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			iVar1 = DATATBLS_GetMissileVelocityFromMissilesTxt(nMissileId, a3);
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 0x114), a2, a3);
			sub_6FABD4D0(pUnit, (int*)pUnit, nMissileId, -1, a2, a3, iVar1 + iVar2);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FACA630
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FACA630(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	bool bVar3;
	int iVar4;
	uint32_t extraout_var;
	D2ActiveRoomStrc* pDVar5;
	int32_t DVar6;
	uint32_t uVar7;
	int iVar8;
	uint32_t* puVar9;
	int local_80;
	int local_7c;
	D2UnitStrc* local_78;
	uint32_t uStack_74;
	D2ActiveRoomStrc** ppDStack_70;
	int local_6c;
	int local_68;
	int local_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((((((-1 < a2) &&
	            (iVar4 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar4 + 0xba0))) &&
	           (local_68 = *(int*)(iVar4 + 0xb98) + a2 * 0x23c, local_68 != 0)) &&
	          ((iVar8 = (int)*(short*)(local_68 + 0xea), -1 < iVar8 && (iVar8 < *(int*)(iVar4 + 0xb6c))))) &&
	         ((iVar1 = *(int*)(iVar4 + 0xb64) + iVar8 * 0x1a4, iVar1 != 0 &&
	                                                               ((local_60 = (int)*(short*)(iVar1 + 0x18), -1 < local_60 &&
	                                                                                                              (local_60 < *(int*)(iVar4 + 0xb6c))))))) &&
	        (local_78 = pUnit, local_6c = iVar8, local_64 = a2,
	            iVar4 = sub_6FABA950(pUnit, &local_80, &local_7c), iVar4 != 0)) &&
	    ((bVar3 = sub_6FABDFF0(pUnit), D2C_ZEXT(bVar3) != 0 &&
	                                       (pDVar5 = UNITS_GetRoom(pUnit), iVar1 = local_7c, iVar4 = local_80,
	                                           pDVar5 != nullptr))))
	{
		iVar2 = (pDVar5->tCoords).nSubtileX;
		if ((local_80 < iVar2) ||
		    (((pUnit = local_78, (pDVar5->tCoords).nSubtileWidth + iVar2 <= local_80 ||
		                             (iVar2 = (pDVar5->tCoords).nSubtileY, local_7c < iVar2)) ||
		        ((pDVar5->tCoords).nSubtileHeight + iVar2 <= local_7c))))
		{
			ppDStack_70 = nullptr;
			uStack_74 = 0;
			DUNGEON_GetAdjacentRoomsListFromRoom(pDVar5, &ppDStack_70, (int*)&uStack_74);
			uVar7 = 0;
			if (uStack_74 != 0)
			{
				do
				{
					pDVar5 = ppDStack_70[uVar7];
					pUnit = local_78;
					if (((pDVar5 != nullptr) &&
					        (iVar2 = (pDVar5->tCoords).nSubtileX, iVar2 <= iVar4)) &&
					    ((iVar8 = local_6c, iVar4 < (pDVar5->tCoords).nSubtileWidth + iVar2 &&
					                            ((iVar2 = (pDVar5->tCoords).nSubtileY, iVar2 <= iVar1 &&
					                                                                       (iVar1 < (pDVar5->tCoords).nSubtileHeight + iVar2))))))
					{
						pDVar5 = ppDStack_70[uVar7];
						goto LAB_6faca7b3;
					}
					uVar7 = uVar7 + 1;
				} while (uVar7 < uStack_74);
			}
			pDVar5 = nullptr;
		}
	LAB_6faca7b3:
		if ((((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(local_68 + 5)) != 0) ||
		    (iVar4 = DUNGEON_IsRoomInTown(pDVar5), iVar4 == 0))
		{
			puVar9 = &uStack_5c;
			for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar9 = 0;
				puVar9 = puVar9 + 1;
			}
			iStack_44 = local_7c;
			uStack_2c = a3;
			uVar7 = pUnit->dwUnitType;
			uStack_5c = 0x21;
			iStack_30 = local_64;
			pDStack_58 = pUnit;
			iStack_4c = iVar8;
			if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
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
			iVar4 = iVar4 - local_80;
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
			iVar8 = (int)DVar6 - local_7c;
			iStack_3c = local_7c + iVar4;
			iStack_40 = local_80 - iVar8;
			sub_6FB3E070(&uStack_5c);
			iStack_40 = iVar8 + local_80;
			iStack_3c = local_7c - iVar4;
			sub_6FB3E070(&uStack_5c);
			iStack_4c = local_60;
			iStack_40 = 0;
			iStack_3c = 0;
			uStack_5c = 1;
			sub_6FB3E070(&uStack_5c);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FACA900
uint32_t __fastcall sub_6FACA900(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	D2UnitStrc* pMissile;

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
			pMissile = sub_6FABABC0(pUnit, iVar1, a2, a3);
			if (pMissile != nullptr)
			{
				MISSILE_SetTargetX(pMissile, iVar2);
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FACA9C0
uint32_t __fastcall sub_6FACA9C0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	int nTargetX;
	D2UnitStrc* pDVar3;
	int32_t DVar4;
	int32_t DVar5;
	int32_t DVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	uint32_t* puVar10;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int aiStack_3c[3];
	int iStack_30;
	int iStack_2c;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar9 != 0))
	{
		iVar2 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			nTargetX = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 0x138), a2, a3);
			iVar9 = 0;
			iVar8 = 0;
			pDVar3 = sub_6FB296A0((int)pUnit);
			if (pDVar3 != nullptr)
			{
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar9 = pDVar3->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					iVar9 = 0;
				}
				else
				{
					iVar9 = PATH_GetXPosition(pDVar3->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
				iVar9 = iVar9 - iVar8;
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
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
				iVar8 = (int)DVar4 - (int)DVar5;
			}
			puVar10 = &uStack_5c;
			for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
			{
				*puVar10 = 0;
				puVar10 = puVar10 + 1;
			}
			uVar1 = pUnit->dwUnitType;
			uStack_5c = 0x21;
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
			iStack_48 = iStack_48 + iVar9;
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
			iStack_44 = (int)DVar6 + iVar8;
			iStack_2c = a3;
			iStack_4c = iVar2;
			iStack_30 = a2;
			iVar9 = sub_6FABA950(pUnit, &iStack_40, aiStack_3c);
			if (((iVar9 != 0) && (iStack_40 != 0)) && (aiStack_3c[0] != 0))
			{
				pDVar3 = sub_6FB3E070(&uStack_5c);
				if (pDVar3 != nullptr)
				{
					MISSILE_SetTargetX(pDVar3, nTargetX);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FACAC10
// TODO: decompilation needs review (extraout)
bool __fastcall sub_6FACAC10(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	D2UnitStrc* pDVar3;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0))
	{
		iVar2 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			bVar1 = sub_6FABDFF0(pUnit);
			if (D2C_ZEXT(bVar1) != 0)
			{
				pDVar3 = sub_6FABAD50(pUnit, iVar2, a2, a3);
				return pDVar3 != nullptr;
			}
		}
	}
	return false;
}

//D2Client.0x6FACACA0
uint32_t __fastcall sub_6FACACA0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2ActiveRoomStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uStack_14;
	D2ActiveRoomStrc** ppDStack_10;
	int local_c;
	int iStack_8;
	int iStack_4;

	local_c = a2;
	pDVar1 = UNITS_GetRoom(pUnit);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	iVar2 = sub_6FABA950(pUnit, &iStack_4, &iStack_8);
	if (iVar2 == 0)
	{
		return 0;
	}
	iVar2 = (pDVar1->tCoords).nSubtileX;
	if ((((iStack_4 < iVar2) || ((pDVar1->tCoords).nSubtileWidth + iVar2 <= iStack_4)) ||
	        (iVar2 = (pDVar1->tCoords).nSubtileY, iStack_8 < iVar2)) ||
	    ((pDVar1->tCoords).nSubtileHeight + iVar2 <= iStack_8))
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
		                                          (iVar2 = (pDVar1->tCoords).nSubtileX, iStack_4 < iVar2)) ||
		        (((pDVar1->tCoords).nSubtileWidth + iVar2 <= iStack_4 ||
		            ((iVar2 = (pDVar1->tCoords).nSubtileY, iStack_8 < iVar2 ||
		                                                       ((pDVar1->tCoords).nSubtileHeight + iVar2 <= iStack_8)))))))
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
	if (((-1 < local_c) && (local_c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + local_c * 0x23c, iVar2 != 0))
	{
		if ((((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar2 + 5)) == 0) &&
		    (iVar2 = DUNGEON_IsRoomInTown(pDVar1), iVar2 != 0))
		{
			return 0;
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FACADF0
bool __fastcall sub_6FACADF0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	D2UnitStrc* pDVar2;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0))
	{
		iVar1 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			pDVar2 = sub_6FABABC0(pUnit, iVar1, a2, a3);
			return pDVar2 != nullptr;
		}
	}
	return false;
}

//D2Client.0x6FACAE70
void __fastcall sub_6FACAE70(D2UnitStrc* pUnit)
{
	int iVar1;
	short sVar2;
	uint32_t uVar3;
	int64_t lVar4;
	uint64_t DVar5;
	int iVar6;
	D2StatListStrc* pStatList;
	D2ActiveRoomStrc* pRoom;
	int iVar7;
	uint32_t* puVar8;
	int iStack_64;
	int iStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	int iStack_2c;

	if (pUnit->pDynamicPath == nullptr)
	{
		return;
	}
	iVar6 = D2Common_10234(pUnit->pDynamicPath);
	if (iVar6 == 0)
	{
		return;
	}
	pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, 0xd);
	if (pStatList == nullptr)
	{
		return;
	}
	iVar6 = STATLIST_GetStatValue(pStatList, 0x15e, 0);
	iStack_60 = STATLIST_GetStatValue(pStatList, 0x15f, 0);
	if (iVar6 < 1)
	{
		return;
	}
	iVar7 = *(int*)((uint8_t*)&sgptDataTables);
	if (*(int*)(iVar7 + 0xba0) <= iVar6)
	{
		return;
	}
	if (iStack_60 < 0)
	{
		iStack_60 = 1;
	}
	iVar1 = *(int*)(iVar7 + 0xb98) + iVar6 * 0x23c;
	if (iVar1 == 0)
	{
		return;
	}
	if (*(short*)(iVar1 + 0xea) < 0)
	{
		return;
	}
	if (*(int*)(iVar7 + 0xb6c) <= (int)*(short*)(iVar1 + 0xea))
	{
		return;
	}
	pRoom = UNITS_GetRoom(pUnit);
	iVar7 = DUNGEON_IsRoomInTown(pRoom);
	if (iVar7 != 0)
	{
		return;
	}
	uVar3 = pUnit->dwUnitType;
	if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
	{
		iStack_64 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iStack_64 = 0;
	}
	else
	{
		iStack_64 = PATH_GetXPosition(pUnit->pDynamicPath);
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
	puVar8 = &uStack_5c;
	for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	uStack_5c = 0x21;
	iStack_48 = iStack_64;
	iStack_2c = iStack_60;
	iStack_4c = (int)*(short*)(iVar1 + 0xea);
	pDStack_58 = pUnit;
	iStack_30 = iVar6;
	if (-1 < *(short*)(iVar1 + 0xec))
	{
		lVar4 = (uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5;
		uVar3 = (pUnit->pSeed).nHighSeed;
		if (*(short*)(iVar1 + 0xee) < 0)
		{
			DVar5 = (uint64_t)(lVar4 + (uint64_t)uVar3);
			(*(uint64_t*)&pUnit->pSeed) = DVar5;
			if (((uint64_t)DVar5 & 1) != 0)
				goto LAB_6facb053;
			sVar2 = *(short*)(iVar1 + 0xec);
		}
		else
		{
			DVar5 = (uint64_t)(lVar4 + (uint64_t)uVar3);
			(*(uint64_t*)&pUnit->pSeed) = DVar5;
			iVar6 = (int)(((uint64_t)DVar5 & 0xffffffff) % 3);
			if (iVar6 == 0)
			{
				iStack_4c = (int)*(short*)(iVar1 + 0xec);
				sub_6FB3E070(&uStack_5c);
				return;
			}
			if (iVar6 != 1)
				goto LAB_6facb053;
			sVar2 = *(short*)(iVar1 + 0xee);
		}
		iStack_4c = (int)sVar2;
	}
LAB_6facb053:
	sub_6FB3E070(&uStack_5c);
}

//D2Client.0x6FACB070
uint32_t __fastcall sub_6FACB070(int a1, int a2, uint32_t a3)
{
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	uint32_t local_5c[4];
	int iStack_4c;
	int local_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if (((((-1 < a2) && (iVar6 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar6 + 0xba0))) && (iVar1 = *(int*)(iVar6 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	        ((iVar5 = (int)*(short*)(iVar1 + 0xea), -1 < iVar5 && (iVar5 < *(int*)(iVar6 + 0xb6c))))) &&
	    ((pDVar3 = sub_6FB296A0(a1), pDVar3 != nullptr && (a1 != 0))))
	{
		puVar7 = local_5c;
		for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar7 = 0;
			puVar7 = puVar7 + 1;
		}
		local_5c[0] = 1;
		uVar2 = pDVar3->dwUnitType;
		local_5c[1] = a1;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
		uVar2 = pDVar3->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
		iStack_4c = iVar5;
		iStack_30 = a2;
		pDVar4 = sub_6FB3E070(local_5c);
		if (pDVar4 != nullptr)
		{
			sub_6FB5FC80((int)pDVar4, 0, 0, 0x118);
			sub_6FB5FCB0((int)pDVar4, 0, 0, -0x28, 1);
		}
		sub_6FAA74C0(0);
		if (0 < *(short*)(iVar1 + 0x10c))
		{
			sub_6FB5BA70(pDVar3, (int)*(short*)(iVar1 + 0x10c), 2, 0, 0, 0, 0, 0);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FACB1F0
uint32_t __fastcall sub_6FACB1F0(int a1, D2UnitStrc* pUnit, int a3, uint32_t a4, int a5, uint32_t a6)
{
	int iVar1;
	short sVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int local_4c;
	int local_40;
	int32_t DStack_3c;
	int local_30;
	uint32_t local_2c;

	if (((a1 == 0) && (pUnit != nullptr)) && (a3 != 0))
	{
		pDVar3 = sub_6FB26AD0(a3);
		if (pDVar3 != nullptr)
		{
			uVar4 = sub_6FB29D80(pUnit, pDVar3);
			if (uVar4 != 0)
			{
				iVar5 = *(int*)(a3 + 4);
				if ((iVar5 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar5))
				{
					iVar5 = 0;
				}
				else
				{
					iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4;
				}
				if (((((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar5 + 5)) != 0) && (-1 < a5)) &&
				    ((iVar5 = *(int*)((uint8_t*)&sgptDataTables), a5 < *(int*)(iVar5 + 0xba0) &&
				                                                      (((iVar1 = *(int*)(iVar5 + 0xb98) + a5 * 0x23c, iVar1 != 0 &&
				                                                                                                          (iVar6 = (int)*(short*)(iVar1 + 0xea), -1 < iVar6)) &&
				                                                          (iVar6 < *(int*)(iVar5 + 0xb6c)))))))
				{
					puVar7 = &local_5c;
					for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
					{
						*puVar7 = 0;
						puVar7 = puVar7 + 1;
					}
					local_30 = a5;
					local_5c = 0x20;
					local_2c = a6;
					uVar4 = pDVar3->dwUnitType;
					local_58 = pUnit;
					local_54 = pUnit;
					local_4c = iVar6;
					if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
					{
						local_40 = pDVar3->pDynamicPath->dwClientCoordY;
					}
					else if (pDVar3->pDynamicPath == nullptr)
					{
						local_40 = 0;
					}
					else
					{
						local_40 = PATH_GetXPosition(pDVar3->pDynamicPath);
					}
					uVar4 = pDVar3->dwUnitType;
					if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
					{
						DStack_3c = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
					}
					else if (pDVar3->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
					}
					else
					{
						DStack_3c = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
					}
					sub_6FB3E070(&local_5c);
					sVar2 = *(short*)(iVar1 + 0x110);
					if ((-1 < sVar2) && ((int)sVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0)))
					{
						sub_6FB5BA70(pUnit, (int)sVar2, 2, 0, 0, 0, 0, 0);
					}
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FACB3C0
uint32_t __fastcall sub_6FACB3C0(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SeedStrc* pDVar1;
	uint32_t uVar2;
	int64_t lVar3;
	uint64_t DVar4;
	int iVar5;
	D2SkillStrc* pSkill;
	int iVar6;
	int iVar7;
	uint32_t uVar8;
	int iVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	int32_t DStack_18;

	if ((((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	          (iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar9 != 0)) &&
	         ((iVar5 = sub_6FABF670(pUnit, a2), -1 < iVar5 &&
	                                                (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))))) &&
	        ((pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, a2),
	            pSkill != nullptr &&
	                ((iVar6 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 0x114), a2, a3),
	                    0 < iVar6 &&
	                        (iVar7 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 0x118), a2, a3),
	                            0 < iVar7)))))) &&
	    (uVar8 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 0x11c), a2, a3),
	        0 < (int)uVar8))
	{
		iVar9 = SKILLS_GetParam1(pSkill);
		SKILLS_SetParam1(pSkill, iVar9 + 1);
		if (iVar9 % iVar6 != 0)
		{
			return 1;
		}
		pDVar1 = &pUnit->pSeed;
		if (pDVar1 != nullptr)
		{
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				DStack_18 = (int32_t)pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0;
			}
			else
			{
				DStack_18 = (int32_t)PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar11 = iVar7 * 2;
			uVar2 = uVar11 + 1;
			if ((int)uVar2 < 1)
			{
				uVar10 = 0;
			}
			else
			{
				lVar3 = (uint64_t)pDVar1->nLowSeed * 0x6ac690c5;
				uVar10 = (pUnit->pSeed).nHighSeed;
				if ((uVar2 & uVar11) == 0)
				{
					DVar4 = (uint64_t)(lVar3 + (uint64_t)uVar10);
					*(uint64_t*)pDVar1 = DVar4;
					uVar10 = uVar11 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
				}
				else
				{
					DVar4 = (uint64_t)(lVar3 + (uint64_t)uVar10);
					*(uint64_t*)pDVar1 = DVar4;
					uVar10 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar2);
				}
			}
			iVar9 = (uVar10 - iVar7) + (int)DStack_18;
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
			if ((int)uVar2 < 1)
			{
				uVar11 = 0;
			}
			else
			{
				lVar3 = (uint64_t)pDVar1->nLowSeed * 0x6ac690c5;
				uVar10 = (pUnit->pSeed).nHighSeed;
				if ((uVar2 & uVar11) == 0)
				{
					DVar4 = (uint64_t)(lVar3 + (uint64_t)uVar10);
					*(uint64_t*)pDVar1 = DVar4;
					uVar11 = uVar11 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
				}
				else
				{
					DVar4 = (uint64_t)(lVar3 + (uint64_t)uVar10);
					*(uint64_t*)pDVar1 = DVar4;
					uVar11 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar2);
				}
			}
			if ((uVar8 & uVar8 - 1) == 0)
			{
				DVar4 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pDVar1 = DVar4;
				uVar8 = uVar8 - 1 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
			}
			else
			{
				DVar4 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pDVar1 = DVar4;
				uVar8 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar8);
			}
			sub_6FB3EBE0(pUnit, iVar5, 0, 0, iVar9, (uVar11 - iVar7) + (int)DStack_18, a2, a3, uVar8);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FACB670
void __cdecl sub_6FACB670(uint32_t* a1)
{
	SendMessageA((HWND)*a1, 0x10, 0, 0);
	a1[6] = 0;
	a1[7] = 0;
}

//D2Client.0x6FACB6A0
void __cdecl sub_6FACB6A0(uint32_t a1)
{
	dword_6FBB19CC = dword_6FBB19CC + 0x10;
}

//D2Client.0x6FACB6B0
void __cdecl sub_6FACB6B0(uint32_t a1)
{
	dword_6FBB19CC = dword_6FBB19CC + -0x10;
}

//D2Client.0x6FACB6C0
void __cdecl sub_6FACB6C0(uint32_t a1)
{
	dword_6FBB19C8 = dword_6FBB19C8 + -0x10;
}

//D2Client.0x6FACB6D0
void __cdecl sub_6FACB6D0(uint32_t a1)
{
	dword_6FBB19C8 = dword_6FBB19C8 + 0x10;
}

//D2Client.0x6FACB6E0
void __fastcall sub_6FACB6E0(int32_t a1)
{
	int iVar1;

	if ((dword_6FB77BC4 != 0) || (iVar1 = 0, a1 != 0))
	{
		sub_6FACB760();
		if (dword_6FBB1990 + -1 != 0)
		{
			dword_6FBB19C8 = 0;
			dword_6FBB19CC = 0;
			return dword_6FBB1990 + -1;
		}
		dword_6FBB19C8 = (gnScreenWidth / 3 - dword_6FBB1A1C) + -0x10;
		iVar1 = gnScreenHeight * 0x55555556;
		dword_6FBB19CC = (gnScreenHeight / 3 - dword_6FBB1A18) + -0x10;
	}
	return iVar1;
}

//D2Client.0x6FACB760
// TODO: decompilation needs review (extraout)
int __cdecl sub_6FACB760()
{
	bool bVar1;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;

	bVar1 = sub_6FADA710();
	if ((dword_6FBB1A2C == D2C_ZEXT(bVar1)) || (dword_6FBB1990 != 1))
	{
		if ((dword_6FBB1A30 == dword_6FBB1A20) || (dword_6FBB1990 != 1))
		{
			if (dword_6FBB1A20 == 0)
			{
				dword_6FBB1A1C = (gnScreenWidth * 2) / 3;
				dword_6FBB1A18 = 0x4e;
			}
			else
			{
				dword_6FBB1A1C = 0;
				bVar1 = sub_6FADA710();
				dword_6FBB1A18 = -(uint32_t)(D2C_ZEXT(bVar1) != 0) & 0x60;
			}
			byte_6FBB1A00 = dword_6FBB1A1C;
			byte_6FBB1A04 = dword_6FBB1A18;
			if (dword_6FBB1990 != 1)
			{
				dword_6FBB1A10 = gnScreenWidth;
				dword_6FBB1A08 = -0x10;
				dword_6FBB1A0C = -0x10;
				dword_6FBB1A14 = gnScreenHeight;
				return -0x10;
			}
			dword_6FBB1A08 = dword_6FBB1A1C + -8;
			dword_6FBB1A10 = gnScreenWidth / 3 + dword_6FBB1A1C;
			dword_6FBB1A0C = dword_6FBB1A18;
			dword_6FBB1A14 = gnScreenHeight / 3 + dword_6FBB1A18;
			return -(gnScreenHeight >> 0x1f);
		}
		dword_6FBB1A30 = dword_6FBB1A20;
	}
	else
	{
		bVar1 = sub_6FADA710();
		dword_6FBB1A2C = D2C_ZEXT(bVar1);
	}
	sub_6FACB760();
	if (dword_6FBB1990 + -1 != 0)
	{
		dword_6FBB19C8 = 0;
		dword_6FBB19CC = 0;
		return dword_6FBB1990 + -1;
	}
	dword_6FBB19C8 = (gnScreenWidth / 3 - dword_6FBB1A1C) + -0x10;
	dword_6FBB19CC = (gnScreenHeight / 3 - dword_6FBB1A18) + -0x10;
	return gnScreenHeight * 0x55555556;
}

//D2Client.0x6FACB8F0
int32_t __cdecl sub_6FACB8F0()
{
	if ((dword_6FBB1990 == 1) && (dword_6FBB19E8 == 1))
	{
		dword_6FBB19E8 = (-(uint32_t)(dword_6FBB19EC != 0) & 0xfffffffe) + 2;
	}
	return 0;
}

//D2Client.0x6FACB920
int __fastcall sub_6FACB920(int a1)
{
	if ((dword_6FBB1990 == 1) && (a1 == 1))
	{
		dword_6FBB19E8 = 1;
		a1 = (-(uint32_t)(dword_6FBB19EC != 0) & 0xfffffffe) + 2;
	}
	SRegSaveValue("Diablo II", "AutoMapFade", 0, a1);
	dword_6FBB19EC = a1;
	dword_6FBB19E8 = a1;
	return a1;
}

//D2Client.0x6FACB970
uint32_t __cdecl sub_6FACB970()
{
	return dword_6FB77BC4;
}

//D2Client.0x6FACB980
uint32_t __fastcall sub_6FACB980(uint32_t a1)
{
	SRegSaveValue("Diablo II", "AutoMap Centers", 0, a1);
	dword_6FB77BC4 = a1;
	return a1;
}

//D2Client.0x6FACB9A0
int __cdecl sub_6FACB9A0()
{
	return dword_6FBB1A20;
}

//D2Client.0x6FACB9B0
uint32_t __fastcall sub_6FACB9B0(uint32_t a1)
{
	SRegSaveValue("Diablo II", "AutoMap Left", 0, a1);
	dword_6FBB1A24 = a1;
	dword_6FBB1A28 = a1;
	dword_6FBB1A20 = a1;
	return a1;
}

//D2Client.0x6FACB9E0
uint32_t __cdecl sub_6FACB9E0()
{
	return dword_6FB77BC8;
}

//D2Client.0x6FACB9F0
uint32_t __fastcall sub_6FACB9F0(uint32_t a1)
{
	SRegSaveValue("Diablo II", "AutoMap Party", 0, a1);
	dword_6FB77BC8 = a1;
	return a1;
}

//D2Client.0x6FACBA10
uint32_t __cdecl sub_6FACBA10()
{
	return dword_6FB77BCC;
}

//D2Client.0x6FACBA20
uint32_t __fastcall sub_6FACBA20(uint32_t a1)
{
	SRegSaveValue("Diablo II", "AutoMap Party Names", 0, a1);
	dword_6FB77BCC = a1;
	return a1;
}
