#include "Skills/SkillsEMon.h"

#include "Game/Select.h"
#include "Quest/QuestsFX.h"
#include "Skills/SkillsAma.h"
#include "Skills/SkillsPal.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"

//D2Client.0x6FB6EA80
uint8_t byte_6FB6EA80[72] = {0x1B, 0xE, 0xF, 3, 0x63, 7, 0x15, 0x16, 0x1F, 0x1A, 0xC, 0xD, 2, 0x63, 6, 0x13, 0x14, 0x1E, 0x19, 0xA, 0xB, 1, 0x63, 5, 0x11, 0x12, 0x1D, 0x18, 8, 9, 0, 0x63, 4, 0xF, 0x10, 0x1C, 0x1F, 0x16, 0x17, 7, 0x63, 3, 0xD, 0xE, 0x1B, 0x1E, 0x14, 7, 6, 0x63, 2, 1, 0xC, 0x1A, 0x1D, 0x12, 0x13, 5, 0x63, 1, 9, 0xA, 0x19, 0x1C, 0x10, 0x11, 4, 0x63, 0, 0x17, 8, 0x18};
//D2Client.0x6FB6EAC8
uint8_t byte_6FB6EAC8[8] = {0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x1F, 0x1E};
//D2Client.0x6FB6EAD0
uint8_t byte_6FB6EAD0[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
//D2Client.0x6FB6EB10
uint8_t byte_6FB6EB10[4] = {0x31, 0x1F, 0x11};
//D2Client.0x6FB6EB14
uint32_t tbl_6FB6EB14[5] = {0xFFFFFFFE, 0xFFFFFFFF, 0, 1, 2};
//D2Client.0x6FB6EB28
uint32_t dword_6FB6EB28;
//D2Client.0x6FB6EB2C
uint32_t dword_6FB6EB2C = 1;
//D2Client.0x6FB6EB68
uint32_t dword_6FB6EB68 = 2;
//D2Client.0x6FB6EB6C
uint32_t dword_6FB6EB6C = 2;
//D2Client.0x6FB6EBA8
uint32_t tbl_6FB6EBA8[6] = {0xFFFFFFFF, 0xFFFFFFFD, 0xFFFFFFFE, 0xFFFFFFFF};

//D2Client.0x6FAC4890
// TODO: decompilation needs review (unaff_)
uint32_t __fastcall sub_6FAC4890(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	int iVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar2;
	bool bVar3;
	uint8_t nDirection;
	D2SkillStrc* pSkill;
	int iVar4;
	int iVar5;
	int iVar6;
	int nX;
	int nY;
	int iVar7;
	uint32_t uVar8;
	int32_t a5;
	void* pCallback;
	D2ActiveRoomStrc* nY_00;
	int32_t nPar3;
	int32_t DVar9;
	D2UnitStrc* pDVar10;
	D2ActiveRoomStrc* pRoom;
	int nX_00;
	int unaff_EBX;
	uint32_t unaff_EBP;
	code* a6;

	if ((pUnit == nullptr) || (pUnit->dwUnitType != 1))
	{
		return 0;
	}
	pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 0x126);
	if (pSkill == nullptr)
	{
		SKILLS_AssignSkill(pUnit, 0x126, 1, 0, __FILE__, __LINE__);
		pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 0x126);
		if (pSkill == nullptr)
		{
			return 0;
		}
	}
	iVar4 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
	iVar5 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
	iVar6 = SKILLS_GetParam1(pSkill);
	SKILLS_SetParam1(pSkill, iVar6 + 1);
	nX = SKILLS_GetParam2(pSkill);
	nY = SKILLS_GetParam3(pSkill);
	if (((-1 < iVar4) && (iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar4 * 0x23c, iVar1 != 0))
	{
		iVar7 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x118), iVar4, iVar5);
		iVar4 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x118), iVar4, iVar5);
		uVar8 = UNITS_GetDistanceToCoordinates(pUnit, nX, nY);
		bVar3 = iVar4 <= (int)uVar8 || iVar7 <= iVar6;
		if (pUnit->dwAnimMode == 1)
		{
			if (bVar3)
			{
				uVar8 = pUnit->dwUnitType;
				if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
				{
					a5 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&a5 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&a5 + 2)) = 0;
				}
				else
				{
					a5 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar8 = pUnit->dwUnitType;
				if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
				{
					pCallback = (void*)pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					pCallback = nullptr;
				}
				else
				{
					pCallback = (void*)PATH_GetXPosition(pUnit->pDynamicPath);
				}
				a6 = (code*)(sub_6FAC4BC0);
				nY_00 = UNITS_GetRoom(pUnit);
				pDVar10 = D2Common_10407(pRoom, nX_00, (int)nY_00, (int(__fastcall*)(D2UnitStrc*, void*))(pCallback), (void*)a5, (int)a6);
				if (pDVar10 != nullptr)
				{
					sub_6FB3DC50(pDVar10, nullptr, 0);
				}
			}
			iVar4 = (int)*(short*)(unaff_EBX + 0xf0);
		}
		else
		{
			if (pUnit->dwAnimMode != 2)
			{
				return 1;
			}
			DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar2;
			iVar4 = (int)*(short*)(iVar1 + 0xee) + ((*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 1);
		}
		if ((bVar3) && (0 < iVar4))
		{
			SKILLS_SetParam1(pSkill, 0);
			uVar8 = pUnit->dwUnitType;
			if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
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
			SKILLS_SetParam2(pSkill, iVar5);
			uVar8 = pUnit->dwUnitType;
			if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
			{
				nPar3 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&nPar3 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&nPar3 + 2)) = 0;
			}
			else
			{
				nPar3 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			SKILLS_SetParam3(pSkill, (int)nPar3);
			uVar8 = pUnit->dwUnitType;
			if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
			{
				DVar9 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar9 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar9 + 2)) = 0;
			}
			else
			{
				DVar9 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar8 = pUnit->dwUnitType;
			if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
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
			pDVar10 = sub_6FB3EAF0((int)pUnit, iVar4, iVar5, (D2UnitStrc**)DVar9, unaff_EBP, nY);
			if (pDVar10 != nullptr)
			{
				nDirection = UNITS_GetDirection(pUnit);
				pDynamicPath = pDVar10->pDynamicPath;
				PATH_SetDirection(pDynamicPath, nDirection);
				D2COMMON_10203_PATH_SetRotateFlag(pDynamicPath, 0);
				sub_6FB29540((int)pDVar10);
			}
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC4BC0
// TODO: decompilation needs review (in_reg)
bool __cdecl sub_6FAC4BC0()
{
	int* in_ECX;

	if ((in_ECX != nullptr) && (*in_ECX == 3))
	{
		return in_ECX[1] == 0x1d4;
	}
	return false;
}

//D2Client.0x6FAC4BE0
uint32_t __fastcall sub_6FAC4BE0(int a1, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int local_4c;
	int local_30;
	uint32_t local_2c;

	if ((((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0))) && (iVar1 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	    ((-1 < *(short*)(iVar1 + 0xec) && ((int)*(short*)(iVar1 + 0xec) < *(int*)(iVar2 + 0xb6c)))))
	{
		local_58 = sub_6FB296A0(a1);
		if (local_58 != nullptr)
		{
			sub_6FB42A70(local_58, 3, 0);
			puVar3 = &local_5c;
			for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*puVar3 = 0;
				puVar3 = puVar3 + 1;
			}
			local_4c = (int)*(short*)(iVar1 + 0xec);
			local_2c = a3;
			local_54 = local_58;
			local_30 = a2;
			sub_6FB3E070(&local_5c);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC4CA0
uint32_t __fastcall sub_6FAC4CA0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	int32_t DVar3;
	D2UnitStrc* pMissile;
	int iVar4;
	uint32_t* puVar5;
	int local_70;
	int local_6c;
	int iStack_68;
	int iStack_64;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	int iStack_2c;
	int iStack_10;

	if (((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	         (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar4 != 0)) &&
	        ((local_60 = sub_6FABF670(pUnit, a2), -1 < local_60 &&
	                                                  (local_60 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))))) &&
	    (iVar2 = sub_6FABA950(pUnit, &local_70, &local_6c), iVar2 != 0))
	{
		iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x138), a2, a3);
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_68 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_68 = 0;
		}
		else
		{
			iStack_68 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		iStack_68 = local_70 - iStack_68;
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
		iStack_64 = local_6c - (int)DVar3;
		sub_6FABAB20(&iStack_68, &iStack_64);
		sub_6FABAB70(&iStack_68, &iStack_64);
		local_70 = local_70 - (iStack_68 * iVar2) / 2;
		local_6c = local_6c - (iStack_64 * iVar2) / 2;
		iStack_10 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x13c), a2, a3);
		puVar5 = &uStack_5c;
		for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*puVar5 = 0;
			puVar5 = puVar5 + 1;
		}
		uStack_5c = 0x20;
		iStack_2c = a3;
		iStack_4c = local_60;
		pDStack_58 = pUnit;
		pDStack_54 = pUnit;
		iStack_30 = a2;
		if (0 < iVar2)
		{
			do
			{
				iStack_40 = local_70;
				iStack_3c = local_6c;
				pMissile = sub_6FB3E070(&uStack_5c);
				if (pMissile != nullptr)
				{
					iVar4 = MISSILE_GetTotalFrames(pMissile);
					sub_6FACA170(pMissile, iVar4);
				}
				local_70 = local_70 + iStack_68;
				local_6c = local_6c + iStack_64;
				iVar2 = iVar2 + -1;
			} while (iVar2 != 0);
		}
		iVar4 = STATES_CheckState(pUnit, 0xc);
		if (iVar4 != 0)
		{
			UNITS_SetAnimationFrame(pUnit, 8);
			pUnit->dwFrameCountPrecise = 0x600;
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC4EC0
uint32_t __fastcall sub_6FAC4EC0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	D2UnitStrc* pMissile;
	int32_t DVar4;
	int local_8;
	int local_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c != 0))
	{
		iVar2 = sub_6FABF670(pUnit, a2);
		if ((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
		{
			iVar3 = sub_6FABA950(pUnit, &local_8, &local_4);
			if (iVar3 != 0)
			{
				pMissile = sub_6FABABC0(pUnit, iVar2, a2, a3);
				if (pMissile != nullptr)
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
					MISSILE_SetTargetX(pMissile, (int)DVar4 - local_4);
					MISSILE_SetTargetY(pMissile, local_8 - iVar2);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC4FE0
// TODO: decompilation needs review (unaff_)
uint32_t __fastcall sub_6FAC4FE0(D2UnitStrc* pUnit, D2UnitStrc** pUnit2, int a3)
{
	uint32_t uVar1;
	uint64_t DVar2;
	int iVar3;
	int32_t pfnUnitTest;
	D2ActiveRoomStrc* nY;
	int32_t DVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	D2UnitFindDataStrc* pUnitFindData;
	uint32_t unaff_EBX;
	D2UnitFindArgStrc* pUnitFindArg;
	D2UnitStrc** ppDVar7;
	D2UnitFindDataStrc DStack_6c;
	int iStack_40;
	D2UnitStrc* apDStack_38[3];
	int iStack_2c;
	int32_t DStack_28;
	D2UnitFindArgStrc* pDStack_24;
	uint32_t uStack_4;

	if ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) < 0x11e) ||
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98), iVar3 == -0x27ccc))
	{
		pUnitFindArg = nullptr;
	}
	else if (a3 < 1)
	{
		pUnitFindArg = nullptr;
	}
	else
	{
		pUnitFindArg = (D2UnitFindArgStrc*)(*(int*)(iVar3 + 0x27e28) * (a3 + -1) + *(int*)(iVar3 + 0x27e24));
	}
	uVar1 = pUnit->dwUnitType;
	DStack_6c.pUnitsArray = pUnit2;
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
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		pfnUnitTest = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&pfnUnitTest + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&pfnUnitTest + 2)) = 0;
	}
	else
	{
		pfnUnitTest = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	ppDVar7 = apDStack_38;
	for (iVar6 = 0xe; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*ppDVar7 = nullptr;
		ppDVar7 = ppDVar7 + 1;
	}
	apDStack_38[0] = (D2UnitStrc*)0x3002;
	apDStack_38[2] = pUnit;
	iStack_2c = iVar3;
	DStack_28 = pfnUnitTest;
	pDStack_24 = pUnitFindArg;
	nY = UNITS_GetRoom(pUnit);
	UNITFINDS_InitializeUnitFindData(&DStack_6c.pRoom, pUnitFindData, nullptr, (int)&DStack_6c.pRoom, (int)nY,
	    iVar3, (UNITFINDTEST)((void*)pfnUnitTest), pUnitFindArg);
	DStack_6c.nFlags = iStack_40;
	UNITFINDS_FindAllMatchingUnitsInNeighboredRooms(&DStack_6c);
	iVar3 = 0;
	if (0 < DStack_6c.nIndex)
	{
		do
		{
			pDVar5 = DStack_6c.pUnitsArray[iVar3];
			uVar1 = pDVar5->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DVar4 = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
			}
			else if (pDVar5->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
			}
			else
			{
				DVar4 = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
			}
			pDVar5 = DStack_6c.pUnitsArray[iVar3];
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
			pDVar5 = sub_6FB3EAF0((int)pUnit, 0x24b, iVar6, (D2UnitStrc**)DVar4, unaff_EBX, uStack_4);
			if (pDVar5 != nullptr)
			{
				iVar6 = MISSILE_GetTotalFrames(pDVar5);
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				iVar6 = iVar6 + -10 + (int)(((uint64_t)DVar2 & 0xffffffff) % 0x14);
				MISSILE_SetTotalFrames(pDVar5, iVar6);
				MISSILE_SetCurrentFrame(pDVar5, iVar6);
			}
			iVar3 = iVar3 + 1;
		} while (iVar3 < DStack_6c.nIndex);
	}
	UNITFINDS_FreeUnitFindData(&DStack_6c);
	return 1;
}

//D2Client.0x6FAC51E0
uint32_t __fastcall sub_6FAC51E0(int a1, uint32_t a2, uint32_t a3)
{
	*(uint32_t*)(a1 + 0x3c) = 0;
	return 1;
}

//D2Client.0x6FAC51F0
uint32_t __fastcall sub_6FAC51F0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	short sVar1;
	uint8_t bVar2;
	D2ActiveRoomStrc* pDVar3;
	int nLevelId;
	int32_t DVar4;
	int iVar5;
	int32_t nY;
	int iVar6;
	D2CoordStrc* pSpawnPoint;
	uint32_t uVar7;
	uint16_t nMask;
	D2CoordStrc DStack_8;

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)) ||
	    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar5 == 0))
	{
		return 0;
	}
	UNITS_SetAnimStartFrame(pUnit);
	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags | 0xe;
	}
	iVar6 = (int)*(short*)(iVar5 + 0xea);
	if ((0 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		pDVar3 = UNITS_GetRoom(pUnit);
		nLevelId = DUNGEON_GetLevelIdFromRoom(pDVar3);
		bVar2 = DRLG_GetActNoFromLevelId(nLevelId);
		if ((bVar2 == 1) &&
		    ((sVar1 = *(short*)(iVar5 + 0xec), 0 < sVar1 &&
		                                           ((int)sVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))))
		{
			iVar6 = (int)sVar1;
		}
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
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
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
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
		sub_6FB3EB50(pUnit, iVar6, iVar5, (D2UnitStrc*)DVar4, a2, a3);
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
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
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
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
	iVar6 = 1;
	uVar7 = 0x1c09;
	iVar5 = UNITS_GetUnitSizeX(pUnit);
	pSpawnPoint = &DStack_8;
	pDVar3 = UNITS_GetRoom(pUnit);
	pDVar3 = COLLISION_GetFreeCoordinates(pDVar3, pSpawnPoint, iVar5, uVar7, iVar6);
	if (pDVar3 == nullptr)
	{
		return 0;
	}
	if (pUnit->pDynamicPath == nullptr)
	{
		return 0;
	}
	iVar5 = D2Common_10231(pUnit->pDynamicPath, pUnit, pDVar3, (uint16_t)DStack_8.nX,
	    (uint16_t)DStack_8.nY);
	if (iVar5 == 0)
	{
		return 0;
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
	{
		nY = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
	}
	else
	{
		nY = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
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
	nMask = 0x1000;
	iVar6 = 1;
	pDVar3 = UNITS_GetRoom(pUnit);
	COLLISION_SetMaskWithPattern(pDVar3, iVar5, (int)nY, iVar6, nMask);
	return 1;
}

//D2Client.0x6FAC5440
uint32_t __fastcall sub_6FAC5440(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	int32_t nY;
	int nX;
	D2ActiveRoomStrc* pRoom;
	int nCollisionPattern;
	uint16_t nMask;

	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags & 0xfffffff1;
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		nY = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
	}
	else
	{
		nY = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		nX = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		nX = 0;
	}
	else
	{
		nX = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	nMask = 0x1000;
	nCollisionPattern = 5;
	pRoom = UNITS_GetRoom(pUnit);
	COLLISION_ResetMaskWithPattern(pRoom, nX, (int)nY, nCollisionPattern, nMask);
	return 1;
}

//D2Client.0x6FAC54D0
uint32_t __fastcall sub_6FAC54D0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	int local_8;
	int local_4;

	UNITS_GetShiftedFrameMetrics(pUnit, &local_8, &local_4);
	pUnit->nActionFrame = 0;
	if (local_8 < 1)
	{
		pUnit->dwSeqSpeed = 0;
	}
	return 1;
}

//D2Client.0x6FAC5510
uint32_t __fastcall sub_6FAC5510(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2SkillStrc* pSkill;
	int iVar3;

	pDVar2 = sub_6FB296A0((int)pUnit);
	if (pDVar2 == nullptr)
	{
		return 0;
	}
	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
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

//D2Client.0x6FAC55C0
uint32_t __fastcall sub_6FAC55C0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint8_t bVar1;
	D2SkillStrc* pSkill;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	int iStack_1c;
	int32_t DStack_18;
	uint32_t uStack_14;
	int iStack_10;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	if (((((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0))) && (iVar3 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar3 != 0)) &&
	        ((iVar3 = (int)*(short*)(iVar3 + 0xea), -1 < iVar3 && (iVar3 < *(int*)(iVar2 + 0xb6c))))) &&
	    (pSkill = UNITS_GetUsedSkill(pUnit), pSkill != nullptr))
	{
		iStack_1c = SKILLS_GetParam1(pSkill);
		DStack_18 = (int32_t)SKILLS_GetParam2(pSkill);
		if (((iStack_1c != 0) && (DStack_18 != (int32_t)0x0)) ||
		    (iVar2 = sub_6FABA950(pUnit, &iStack_1c, (int*)&DStack_18), iVar2 != 0))
		{
			iVar2 = UNITS_GetDirectionToCoords(pUnit, iStack_1c, (int)DStack_18);
			(*(uint8_t*)((uint8_t*)&uStack_14 + 0)) = (uint8_t)iVar2;
			bVar1 = D2Common_11053((uint8_t)iVar2);
			uStack_14 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_14 + 1)), bVar1) & 0xffffff07;
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				iStack_1c = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_1c = 0;
			}
			else
			{
				iStack_1c = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
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
			uVar4 = uStack_14 & 0xff;
			D2Common_11055(byte_6FB6EAC8[uVar4], &iStack_c, &iStack_8);
			iStack_1c = iStack_1c + iStack_c;
			DStack_18 = (int32_t)((int)DStack_18 + iStack_8);
			UNITS_GetShiftedFrameMetrics(pUnit, &iStack_10, &iStack_4);
			iStack_10 = iStack_10 + -4;
			if (iStack_10 < 1)
			{
				iStack_10 = 0;
			}
			else if (7 < iStack_10)
			{
				iStack_10 = 8;
			}
			bVar1 = byte_6FB6EA80[iStack_10 + uVar4 * 9];
			uStack_14 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_14 + 1)), bVar1);
			if (bVar1 != 99)
			{
				D2Common_11055(bVar1, &iStack_c, &iStack_8);
				iStack_1c = iStack_1c + iStack_c;
				DStack_18 = (int32_t)((int)DStack_18 + iStack_8);
			}
			sub_6FB3EB50(pUnit, iVar3, iStack_1c, (D2UnitStrc*)DStack_18, a2, a3);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC57D0
uint32_t __fastcall sub_6FAC57D0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2DynamicPathStrc* pDynamicPath;
	D2UnitStrc* pDVar1;
	D2SkillStrc* pSkill;
	int iVar2;

	pDVar1 = sub_6FB296A0((int)pUnit);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	pDynamicPath = pUnit->pDynamicPath;
	if (pDynamicPath == nullptr)
	{
		return 0;
	}
	PATH_SetNewDistance(pDynamicPath, 5);
	PATH_SetType(pDynamicPath, 2);
	D2Common_10142(pDynamicPath, pUnit, 0);
	iVar2 = PATH_GetNumberOfPathPoints(pDynamicPath);
	if (iVar2 < 1)
	{
		PATH_SetType(pDynamicPath, 1);
		D2Common_10142(pDynamicPath, pUnit, 0);
		iVar2 = PATH_GetNumberOfPathPoints(pDynamicPath);
		if (iVar2 < 1)
		{
			return 0;
		}
	}
	SKILLS_SetFlags(pSkill, 1);
	return 1;
}

//D2Client.0x6FAC5860
uint32_t __fastcall sub_6FAC5860(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SkillStrc* pSkill;
	uint32_t uVar1;
	int iVar2;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar2 != 0))
	{
		pSkill = UNITS_GetUsedSkill(pUnit);
		if (pSkill == nullptr)
		{
			return 0;
		}
		uVar1 = SKILLS_GetFlags(pSkill);
		if ((uVar1 & 2) == 0)
		{
			uVar1 = *(uint32_t*)(iVar2 + 0x138);
		}
		else
		{
			SKILLS_SetFlags(pSkill, 0);
			uVar1 = *(uint32_t*)(iVar2 + 0x13c);
		}
		iVar2 = SKILLS_EvaluateSkillFormula(pUnit, uVar1, a2, a3);
		UNITS_SetAnimationFrame(pUnit, iVar2);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC5900
uint32_t __fastcall sub_6FAC5900(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	int iVar2;
	D2SkillStrc* pSkill;
	int iVar3;
	D2ActiveRoomStrc* pDVar4;
	uint32_t uVar5;
	int iStack_10;
	int iStack_c;
	D2ActiveRoomStrc** ppDStack_8;
	int iStack_4;

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
	iVar3 = MONSTERS_GetSpawnMode_XY(pUnit, 1, a2, a3, &iStack_4, &iStack_c, &iStack_10);
	if (iVar3 < 0)
	{
		return 0;
	}
	SKILLS_SetParam2(pSkill, iStack_c);
	SKILLS_SetParam3(pSkill, iStack_10);
	iVar2 = iStack_c;
	iVar3 = iStack_10;
	pDVar4 = UNITS_GetRoom(pUnit);
	if (pDVar4 != nullptr)
	{
		iVar1 = (pDVar4->tCoords).nSubtileX;
		if (((iVar1 <= iVar2) && (iVar2 < (pDVar4->tCoords).nSubtileWidth + iVar1)) &&
		    ((iVar1 = (pDVar4->tCoords).nSubtileY, iVar1 <= iVar3 &&
		                                               (iVar3 < (pDVar4->tCoords).nSubtileHeight + iVar1))))
			goto LAB_6fac5a22;
		ppDStack_8 = nullptr;
		a3 = 0;
		DUNGEON_GetAdjacentRoomsListFromRoom(pDVar4, &ppDStack_8, (int*)&a3);
		uVar5 = 0;
		if (a3 != 0)
		{
			do
			{
				pDVar4 = ppDStack_8[uVar5];
				if (((pDVar4 != nullptr) &&
				        (iVar1 = (pDVar4->tCoords).nSubtileX, iVar1 <= iVar2)) &&
				    ((iVar2 < (pDVar4->tCoords).nSubtileWidth + iVar1 &&
				        ((iVar1 = (pDVar4->tCoords).nSubtileY, iVar1 <= iVar3 &&
				                                                   (iVar3 < (pDVar4->tCoords).nSubtileHeight + iVar1))))))
				{
					pDVar4 = ppDStack_8[uVar5];
					goto LAB_6fac5a22;
				}
				uVar5 = uVar5 + 1;
			} while (uVar5 < a3);
		}
	}
	pDVar4 = nullptr;
LAB_6fac5a22:
	COLLISION_SetMaskWithPattern(pDVar4, iStack_c, iStack_10, 1, 0x100);
	return 1;
}

//D2Client.0x6FAC5A50
uint32_t __fastcall sub_6FAC5A50(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	int iVar1;
	D2SkillStrc* pSkill;
	int nX;
	int nY;
	D2ActiveRoomStrc* pDVar2;
	uint32_t uVar3;
	uint32_t uStack_8;
	D2ActiveRoomStrc** ppDStack_4;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill != nullptr)
	{
		nX = SKILLS_GetParam2(pSkill);
		nY = SKILLS_GetParam3(pSkill);
		if ((nX != 0) && (nY != 0))
		{
			SKILLS_SetParam2(pSkill, 0);
			SKILLS_SetParam3(pSkill, 0);
			pDVar2 = UNITS_GetRoom(pUnit);
			if (pDVar2 != nullptr)
			{
				iVar1 = (pDVar2->tCoords).nSubtileX;
				if ((((nX < iVar1) || ((pDVar2->tCoords).nSubtileWidth + iVar1 <= nX)) ||
				        (iVar1 = (pDVar2->tCoords).nSubtileY, nY < iVar1)) ||
				    ((pDVar2->tCoords).nSubtileHeight + iVar1 <= nY))
				{
					ppDStack_4 = nullptr;
					uStack_8 = 0;
					DUNGEON_GetAdjacentRoomsListFromRoom(pDVar2, &ppDStack_4, (int*)&uStack_8);
					uVar3 = 0;
					if (uStack_8 != 0)
					{
						do
						{
							pDVar2 = ppDStack_4[uVar3];
							if (((pDVar2 != nullptr) &&
							        (iVar1 = (pDVar2->tCoords).nSubtileX, iVar1 <= nX)) &&
							    ((nX < (pDVar2->tCoords).nSubtileWidth + iVar1 &&
							        ((iVar1 = (pDVar2->tCoords).nSubtileY, iVar1 <= nY &&
							                                                   (nY < (pDVar2->tCoords).nSubtileHeight + iVar1))))))
							{
								pDVar2 = ppDStack_4[uVar3];
								goto LAB_6fac5b26;
							}
							uVar3 = uVar3 + 1;
						} while (uVar3 < uStack_8);
					}
				}
				else
				{
				LAB_6fac5b26:
					if (pDVar2 != nullptr)
					{
						COLLISION_ResetMaskWithPattern(pDVar2, nX, nY, 1, 0x100);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC5B50
uint32_t __fastcall sub_6FAC5B50(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int32_t DVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	int iVar7;
	int32_t nNewY;
	int nNewX;
	uint32_t* puVar8;
	int local_74;
	int iStack_70;
	int32_t DStack_6c;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((-1 < a2) && (iVar4 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar4 + 0xba0))) && (iVar1 = *(int*)(iVar4 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	    ((iVar1 = (int)*(short*)(iVar1 + 0xea), -1 < iVar1 && (iVar1 < *(int*)(iVar4 + 0xb6c)))))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		pDVar2 = sub_6FB296A0((int)pUnit);
		if (pDVar2 != nullptr)
		{
			uVar6 = pDVar2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				local_74 = pDVar2->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar2->pDynamicPath == nullptr)
			{
				local_74 = 0;
			}
			else
			{
				local_74 = PATH_GetXPosition(pDVar2->pDynamicPath);
			}
			uVar6 = pDVar2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DVar3 = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
			}
			else if (pDVar2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
			}
			else
			{
				DVar3 = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
			}
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				iStack_70 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_70 = 0;
			}
			else
			{
				iStack_70 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DStack_6c = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_6c + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_6c + 2)) = 0;
			}
			else
			{
				DStack_6c = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iVar4 = local_74 - iStack_70;
			if (iVar4 < 0)
			{
				iVar4 = -iVar4;
			}
			iVar7 = (int)DVar3 - (int)DStack_6c;
			if (iVar7 < 0)
			{
				iVar7 = -iVar7;
			}
			iVar5 = 4;
			nNewY = DStack_6c;
			nNewX = iStack_70;
			if (iVar4 < iVar7)
			{
				do
				{
					if (local_74 < nNewX)
					{
						nNewX = nNewX + -1;
					}
					else if (nNewX < local_74)
					{
						nNewX = nNewX + 1;
					}
					iVar5 = iVar5 + -1;
					nNewY = DVar3;
				} while (iVar5 != 0);
			}
			else
			{
				do
				{
					if ((int)DVar3 < (int)nNewY)
					{
						nNewY = (int32_t)((int)nNewY + -1);
					}
					else if ((int)nNewY < (int)DVar3)
					{
						nNewY = (int32_t)((int)nNewY + 1);
					}
					iVar5 = iVar5 + -1;
					nNewX = local_74;
				} while (iVar5 != 0);
			}
			puVar8 = &uStack_5c;
			for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			iStack_40 = nNewX - iStack_70;
			iStack_3c = (int)nNewY - (int)DStack_6c;
			uStack_5c = 3;
			iStack_48 = iStack_40 / 6 + -1 + iStack_70;
			iStack_44 = iStack_3c / 6 + -1 + (int)DStack_6c;
			uStack_2c = a3;
			pDStack_58 = pUnit;
			iStack_4c = iVar1;
			iStack_30 = a2;
			uVar6 = UNITS_GetDirectionToCoords(pUnit, nNewX, (int)nNewY);
			PATH_SetDirection(pUnit->pDynamicPath, byte_6FB6EB10[(uint8_t)byte_6FB6EAD0[uVar6 & 0x3f] & 3]);
			sub_6FB3E070(&uStack_5c);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC5DC0
uint32_t __fastcall sub_6FAC5DC0(int a1, uint32_t a2, uint32_t a3)
{
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) & 0xfffffff1;
	}
	return 1;
}

//D2Client.0x6FAC5DE0
uint32_t __fastcall sub_6FAC5DE0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	int local_8;
	int local_4;

	if ((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0)))
	{
		iVar1 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c;
		if (iVar1 != 0)
		{
			iVar4 = (int)*(short*)(iVar1 + 0xea);
			if ((-1 < iVar4) && (iVar4 < *(int*)(iVar2 + 0xb6c)))
			{
				if (pUnit != nullptr)
				{
					pUnit->dwFlags = pUnit->dwFlags | 0x40;
				}
				iVar2 = sub_6FABA950(pUnit, &local_4, &local_8);
				if (iVar2 != 0)
				{
					iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 100), a2, a3);
					iVar2 = iVar2 + -6;
					if (iVar2 < 1)
					{
						iVar2 = 1;
					}
					uVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x114), a2, a3);
					sub_6FB35D10(pUnit, local_4, local_8, iVar2, iVar4, a2, a3, uVar3, 1);
					return 1;
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC5ED0
uint32_t __fastcall sub_6FAC5ED0(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	int iVar1;
	short sVar2;
	uint64_t DVar3;
	int iVar4;
	int iVar5;
	int local_14;
	int local_10;
	int iStack_c;
	int local_8;
	uint32_t uStack_4;

	if ((((-1 < a2) && (iVar4 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar4 + 0xba0))) && (iVar1 = *(int*)(iVar4 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	    ((iVar5 = (int)*(short*)(iVar1 + 0xea), -1 < iVar5 && (iVar5 < *(int*)(iVar4 + 0xb6c)))))
	{
		sVar2 = *(short*)(iVar1 + 0xec);
		local_8 = iVar5;
		iVar4 = sub_6FABA950(pUnit, &local_10, &local_14);
		if (iVar4 != 0)
		{
			D2Common_10216(pUnit->pDynamicPath, local_10, local_14, 0);
			iStack_c = 2;
			do
			{
				if (0 < sVar2)
				{
					DVar3 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					uStack_4 = (*(uint32_t*)((uint8_t*)&DVar3 + 0)) & 1;
					(*(uint64_t*)&pUnit->pSeed) = DVar3;
					if (((uint64_t)DVar3 & 1) != 0)
					{
						iVar5 = (int)sVar2;
					}
				}
				sub_6FAC5FF0(pUnit, iVar5, (int)&tbl_6FB6EB14, local_10, local_14, a2, a3);
				iStack_c = iStack_c + -1;
				iVar5 = local_8;
			} while (iStack_c != 0);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAC5FF0
uint32_t* __fastcall sub_6FAC5FF0(D2UnitStrc* pUnit2, int a2, int a3, uint32_t a4, uint32_t a5, int a6, int a7)
{
	uint32_t uVar1;
	int iVar2;
	uint64_t DVar3;
	D2UnitStrc* pUnit;
	int iVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	int local_4c;
	int local_48;
	int32_t DStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_34;
	int iStack_30;
	int iStack_2c;

	puVar6 = &local_5c;
	for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	DVar3 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
	local_5c = 0x25;
	(*(uint64_t*)&pUnit2->pSeed) = DVar3;
	if (((uint64_t)DVar3 & 3) != 0)
	{
		local_5c = 0x4025;
	}
	uVar1 = pUnit2->dwUnitType;
	local_58 = pUnit2;
	local_4c = a2;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		local_48 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		local_48 = 0;
	}
	else
	{
		local_48 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DStack_44 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
	}
	else
	{
		DStack_44 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	uStack_40 = a4;
	uStack_3c = a5;
	iStack_30 = a6;
	iStack_2c = a7;
	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a2 * 0x1a4, iVar5 != 0))
	{
		DVar3 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit2->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit2->pSeed) = DVar3;
		iStack_34 = (uint32_t) * (uint8_t*)(iVar5 + 0x9a) +
		            *(int*)(a3 + (int)(((uint64_t)DVar3 & 0xffffffff) % 5) * 4);
		pUnit = sub_6FB3E070(&local_5c);
		if (pUnit == nullptr)
		{
			return nullptr;
		}
		if ((((-1 < a6) &&
		         (iVar5 = *(int*)((uint8_t*)&sgptDataTables), a6 < *(int*)(iVar5 + 0xba0))) &&
		        ((iVar4 = *(int*)(iVar5 + 0xb98) + a6 * 0x23c, iVar4 != 0 &&
		                                                           ((iVar2 = pUnit->dwClassId, -1 < iVar2 && (iVar2 < *(int*)(iVar5 + 0xb6c))))))) &&
		    (iVar5 = *(int*)(iVar5 + 0xb64) + iVar2 * 0x1a4, iVar5 != 0))
		{
			iVar4 = SKILLS_EvaluateSkillFormula(pUnit2, *(uint32_t*)(iVar4 + 0x138), a6, a7);
			if (iVar4 < 1)
			{
				iVar4 = *(int*)(iVar5 + 0x3c) + -1 + a7;
			}
			if (iVar4 < 2)
			{
				iVar4 = 1;
			}
			else if (0xfe < iVar4)
			{
				iVar4 = 0xff;
			}
			PATH_SetNewDistance(pUnit->pDynamicPath, (uint8_t)iVar4);
			UNITS_SetAnimationSpeed(pUnit, (int)((int64_t)((uint64_t) * (uint8_t*)(iVar5 + 0x178) << 8) / (int64_t)iVar4));
			MISSILE_SetTotalFrames(pUnit, iVar4);
			MISSILE_SetCurrentFrame(pUnit, iVar4);
		}
		return &pUnit->dwUnitType;
	}
	return nullptr;
}

//D2Client.0x6FAC6240
uint32_t __fastcall sub_6FAC6240(int a1, uint32_t a2, uint32_t a3)
{
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0xe;
	}
	return 1;
}

//D2Client.0x6FAC6260
uint32_t __fastcall sub_6FAC6260(int a1, uint32_t a2, uint32_t a3)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB296A0(a1);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 200) = *(uint32_t*)(a1 + 200) & 0xfffbffff;
	}
	return 1;
}

//D2Client.0x6FAC6290
uint32_t __fastcall sub_6FAC6290(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int local_4c;
	int local_48;
	int32_t DStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_34;
	int iStack_2c;
	int iStack_28;

	if (((((-1 < a2) && (iVar5 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar5 + 0xba0))) && (iVar2 = *(int*)(iVar5 + 0xb98) + a2 * 0x23c, iVar2 != 0)) &&
	        ((iVar4 = (int)*(short*)(iVar2 + 0xea), -1 < iVar4 && (iVar4 < *(int*)(iVar5 + 0xb6c))))) &&
	    (iVar5 = *(int*)(iVar5 + 0xb64) + iVar4 * 0x1a4, iVar5 != 0))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		puVar6 = &local_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar6 = 0;
			puVar6 = puVar6 + 1;
		}
		uVar1 = pUnit->dwUnitType;
		local_5c = 0x1f;
		local_58 = pUnit;
		local_54 = pUnit;
		local_4c = iVar4;
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
		iStack_28 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 0x138), a2, a3);
		iStack_34 = *(int*)(iVar5 + 0x38) << 6;
		iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 0x13c), a2, a3);
		if (iVar2 < 1)
		{
			iVar2 = 1;
		}
		iVar4 = 0;
		do
		{
			uStack_40 = *(uint32_t*)((int)&dword_6FB6EB28 + iVar4);
			uStack_3c = *(uint32_t*)((int)&dword_6FB6EB68 + iVar4);
			sub_6FB3E070(&local_5c);
			iVar4 = iVar4 + 8;
		} while (iVar4 < 0x40);
		iStack_34 = *(int*)(iVar5 + 0x3c) << 6;
		if (1 < iVar2)
		{
			iVar5 = 0;
			do
			{
				uStack_3c = *(uint32_t*)((int)&dword_6FB6EB6C + iVar5);
				uStack_40 = *(uint32_t*)((int)&dword_6FB6EB2C + iVar5);
				sub_6FB3E070(&local_5c);
				iVar5 = iVar5 + iVar2 * 4;
			} while (iVar5 < 0x3c);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC6460
uint32_t __fastcall sub_6FAC6460(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SkillStrc* pSkill;
	int iVar1;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 != 0))
	{
		pSkill = UNITS_GetUsedSkill(pUnit);
		if (pSkill == nullptr)
		{
			return 0;
		}
		iVar1 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x114), a2, a3);
		SKILLS_SetParam1(pSkill, iVar1);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC64E0
uint32_t __fastcall sub_6FAC64E0(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SkillStrc* pSkill;
	int iVar1;
	int iVar2;
	int iStack_10;
	int iStack_c;
	int local_8;
	int local_4;

	if ((-1 < a2) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar1 + 0xba0)))
	{
		iVar2 = *(int*)(iVar1 + 0xb98) + a2 * 0x23c;
		if (iVar2 != 0)
		{
			local_8 = (int)*(short*)(iVar2 + 0xea);
			if ((-1 < local_8) && (local_8 < *(int*)(iVar1 + 0xb6c)))
			{
				local_4 = iVar2;
				pSkill = UNITS_GetUsedSkill(pUnit);
				if (pSkill != nullptr)
				{
					iVar1 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar2 + 0x114), a2, a3);
					iVar2 = SKILLS_GetParam1(pSkill);
					if (iVar2 + 1 < iVar1)
					{
						SKILLS_SetParam1(pSkill, iVar2 + 1);
					}
					else
					{
						SKILLS_SetParam1(pSkill, 0);
						iVar1 = sub_6FABA950(pUnit, &iStack_c, &iStack_10);
						if (iVar1 != 0)
						{
							D2Common_10216(pUnit->pDynamicPath, iStack_c, iStack_10, 0);
							sub_6FAC5FF0(pUnit, local_8, (int)&tbl_6FB6EBA8, iStack_c, iStack_10, a2, a3);
							if (pUnit->dwUnitType == 1)
							{
								iVar1 = pUnit->dwClassId;
								if ((((-1 < iVar1) &&
								         (iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar1 < *(int*)(iVar2 + 0xa80))) &&
								        (iVar1 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar1 * 0x1a8),
								            -1 < iVar1)) &&
								    ((iVar1 < *(int*)(iVar2 + 0xa98) &&
								        (iVar1 = *(int*)(iVar2 + 0xa90) + iVar1 * 0x134, iVar1 != 0))))
								{
									if (*(char*)(local_4 + 0x11) == '\x0e')
									{
										UNITS_SetAnimationFrame(pUnit, *(uint8_t*)(iVar1 + 0x109) - 1);
										pUnit->dwFrameCountPrecise = (*(uint8_t*)(iVar1 + 0x109) + 1) * 0x100;
										return 1;
									}
									pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar1 + 0x109) * 0x100 + -0x100;
									return 1;
								}
							}
							else
							{
								UNITS_SetAnimationFrame(pUnit, 8);
								pUnit->dwFrameCountPrecise = 0x500;
							}
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC66A0
uint32_t __fastcall sub_6FAC66A0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	int32_t nY;
	int32_t DVar4;
	int32_t DVar5;
	int iVar6;
	int iVar7;
	uint32_t* puVar8;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int local_4c;
	int local_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	int iStack_2c;
	int iStack_28;

	if (((((-1 < a2) && (iVar6 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar6 + 0xba0))) && (iVar1 = *(int*)(iVar6 + 0xb98) + a2 * 0x23c, iVar1 != 0)) &&
	        ((iVar7 = (int)*(short*)(iVar1 + 0xea), -1 < iVar7 && (iVar7 < *(int*)(iVar6 + 0xb6c))))) &&
	    (*(int*)(iVar6 + 0xb64) + iVar7 * 0x1a4 != 0))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0x40;
		}
		puVar8 = &local_5c;
		for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar8 = 0;
			puVar8 = puVar8 + 1;
		}
		uVar2 = pUnit->dwUnitType;
		local_5c = 3;
		local_58 = pUnit;
		local_54 = pUnit;
		local_4c = iVar7;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
		iStack_30 = a2;
		iStack_28 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x138), a2, a3);
		pDVar3 = sub_6FB296A0((int)pUnit);
		if (pDVar3 == nullptr)
		{
			iVar6 = D2COMMON_10175_PathGetFirstPointX(pUnit->pDynamicPath);
			iStack_40 = sub_6FAB6A60((int*)pUnit);
			iStack_40 = iVar6 - iStack_40;
			DVar4 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pUnit->pDynamicPath);
			DVar5 = (int32_t)sub_6FAB6A90((int*)pUnit);
		}
		else
		{
			uVar2 = pDVar3->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
			uVar2 = pDVar3->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iVar6 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			D2Common_10216(pUnit->pDynamicPath, iVar6, (int)nY, 0);
			uVar2 = pDVar3->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iStack_40 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iStack_40 = 0;
			}
			else
			{
				iStack_40 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
			iStack_40 = iStack_40 - iVar6;
			uVar2 = pDVar3->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
		}
		iStack_3c = (int)DVar4 - (int)DVar5;
		pDVar3 = sub_6FB3E070(&local_5c);
		if (pDVar3 != nullptr)
		{
			MISSILE_SetTargetX(pDVar3, a3);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAC6960
uint32_t __fastcall sub_6FAC6960(D2UnitStrc* pUnit, int a2, int a3)
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
	int aiStack_3c[4];
	int iStack_2c;
	code* pcStack_8;
	int iStack_4;

	if (((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xba0))) && (iVar3 = *(int*)(iVar2 + 0xb98) + a2 * 0x23c, iVar3 != 0))
	{
		iVar4 = (int)*(short*)(iVar3 + 0xea);
		if ((-1 < iVar4) && (iVar4 < *(int*)(iVar2 + 0xb6c)))
		{
			if (pUnit != nullptr)
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x40;
			}
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x138), a2, a3);
			puVar5 = &uStack_5c;
			for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
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
			pcStack_8 = (code*)(sub_6FAC6AB0);
			iStack_4c = iVar4;
			iVar3 = sub_6FABA950(pUnit, &iStack_40, aiStack_3c);
			if (iVar3 != 0)
			{
				iVar3 = 0;
				if (0 < iVar2)
				{
					do
					{
						iStack_4 = iVar3;
						sub_6FB3E070(&uStack_5c);
						iVar3 = iVar3 + 1;
					} while (iVar3 < iVar2);
				}
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAC6AB0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAC6AB0()
{
	D2SeedStrc* pSeed;
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar1;
	int iVar2;
	D2UnitStrc* in_ECX;
	int in_EDX;
	int iStack_4;

	if (in_ECX != nullptr)
	{
		iStack_4 = MISSILE_GetTotalFrames(in_ECX);
		if (0x4d < iStack_4)
		{
			iStack_4 = 0x4d;
			MISSILE_SetTotalFrames(in_ECX, 0x4d);
			MISSILE_SetCurrentFrame(in_ECX, 0x4d);
		}
		pDynamicPath = in_ECX->pDynamicPath;
		pSeed = &in_ECX->pSeed;
		iVar2 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
		SEED_InitLowSeed(pSeed, iVar2 + in_EDX);
		DVar1 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(in_ECX->pSeed).nHighSeed);
		*(uint64_t*)pSeed = DVar1;
		if (0x13 < (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % 100))
		{
			PATH_SetType(pDynamicPath, 10);
			PATH_SetNewDistance(pDynamicPath, (uint8_t)iStack_4);
			D2Common_10142(pDynamicPath, in_ECX, 0);
		}
	}
}

//D2Client.0x6FAC6B50
uint32_t __fastcall sub_6FAC6B50(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2SkillStrc* pSkill;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return 0;
	}
	SKILLS_SetFlags(pSkill, 0);
	return 1;
}
