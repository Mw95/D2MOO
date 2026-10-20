#include "Unit/MonUnique.h"

#include "Draw/DFloor.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundHdr.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"

//D2Client.0x6FB70D1C
uint32_t dword_6FB70D1C = 1;
//D2Client.0x6FB70D2C
uint32_t tbl_6FB70D2C[1];
//D2Client.0x6FB917A8
uint8_t byte_6FB917A8[4];
//D2Client.0x6FB91858
uint8_t byte_6FB91858[16];
//D2Client.0x6FB91868
uint8_t byte_6FB91868[848] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x53, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x56, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x58, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10, 0x59, 0xB4, 0x6F, 0x20, 0x5B, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x56, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x60, 0x5B, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xA0, 0x54, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10, 0x59, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0, 0x5B, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x51, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10, 0x5E, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0, 0x5E, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10, 0x61, 0xB4, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x56, 0xB4, 0x6F};
//D2Client.0x6FB91BB8
uint8_t byte_6FB91BB8[88] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x85, 0xC, 0x86, 0xC, 0x87, 0xC, 0x88, 0xC, 0x89, 0xC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x8B, 0xC, 0x8A, 0xC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x91, 0xC, 0x8C, 0xC, 0x8E, 0xC, 0x8D, 0xC, 0x8F, 0xC, 0x90, 0xC, 0x92, 0xC};
//D2Client.0x6FB91C50
int32_t dword_6FB91C50 = 1;
//D2Client.0x6FB91C54
uint8_t byte_6FB91C54 = 0x98;
//D2Client.0x6FB91C6C
uint8_t byte_6FB91C6C = 0xC3;
//D2Client.0x6FB91C84
uint8_t byte_6FB91C84 = 0xF3;
//D2Client.0x6FB91C9C
uint8_t byte_6FB91C9C = 0x1D;
//D2Client.0x6FB91CB4
uint8_t byte_6FB91CB4 = 0x3C;
//D2Client.0x6FB91CCC
uint8_t byte_6FB91CCC = 0x99;
//D2Client.0x6FB91CE4
uint8_t byte_6FB91CE4 = 0xC0;
//D2Client.0x6FB91CFC
uint8_t byte_6FB91CFC = 0xE3;
//D2Client.0x6FB91D14
uint8_t byte_6FB91D14 = 4;
//D2Client.0x6FB91D2C
uint8_t byte_6FB91D2C = 0x25;
//D2Client.0x6FB91D44
uint8_t byte_6FB91D44 = 0x46;
//D2Client.0x6FB91D5C
uint8_t byte_6FB91D5C = 0x6D;
//D2Client.0x6FB91D74
uint8_t byte_6FB91D74 = 0x95;
//D2Client.0x6FB91D8C
uint8_t byte_6FB91D8C = 0x98;
//D2Client.0x6FB91DA4
uint8_t byte_6FB91DA4 = 0xCB;
//D2Client.0x6FB91DD4
uint8_t byte_6FB91DD4 = 0xD1;
//D2Client.0x6FB91DEC
uint8_t byte_6FB91DEC = 0xED;
//D2Client.0x6FB91E04
uint8_t byte_6FB91E04 = 0x16;
//D2Client.0x6FB91E1C
uint8_t byte_6FB91E1C = 0x36;
//D2Client.0x6FB91E34
uint8_t byte_6FB91E34 = 0x79;
//D2Client.0x6FB91E4C
uint8_t byte_6FB91E4C = 0x98;
//D2Client.0x6FB91E64
uint8_t byte_6FB91E64 = 0xCF;
//D2Client.0x6FB91E7C
uint32_t dword_6FB91E7C;
//D2Client.0x6FB91E94
uint8_t byte_6FB91E94;
//D2Client.0x6FB91EAC
uint8_t byte_6FB91EAC;
//D2Client.0x6FB91EC4
uint8_t byte_6FB91EC4;
//D2Client.0x6FB91EDC
uint8_t byte_6FB91EDC;
//D2Client.0x6FB91EF4
uint8_t byte_6FB91EF4;
//D2Client.0x6FB91F10
uint32_t dword_6FB91F10 = 0xDA0;

//D2Client.0x6FB44E70
void __fastcall sub_6FB44E70(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SkillStrc* pSkill;
	int nSkillMode;

	if (a3 != 0)
	{
		SKILLS_AssignSkill(pUnit, 0xb8, 1, 1, __FILE__, __LINE__);
		nSkillMode = 4;
		pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 0xb8);
		SKILLS_SetSkillMode(pSkill, nSkillMode);
	}
}

//D2Client.0x6FB44EB0
void __fastcall sub_6FB44EB0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	if (a3 != 0)
	{
		if (a2 == 0x1c)
		{
			iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x1f, 0);
			STATLIST_SetUnitStat(pUnit, 0x1f, iVar1 * 2, 0);
		}
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0x27, 0);
		iVar2 = STATLIST_UnitGetStatValue(pUnit, 0x29, 0);
		iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x2b, 0);
		iVar4 = STATLIST_UnitGetStatValue(pUnit, 0x2d, 0);
		iVar5 = STATLIST_UnitGetStatValue(pUnit, 0x24, 0);
		iVar6 = STATLIST_UnitGetStatValue(pUnit, 0x25, 0);
		a3 = (int)(99 < iVar1);
		if (99 < iVar2)
		{
			a3 = a3 + 1;
		}
		if (99 < iVar3)
		{
			a3 = a3 + 1;
		}
		if (99 < iVar4)
		{
			a3 = a3 + 1;
		}
		if (99 < iVar5)
		{
			a3 = a3 + 1;
		}
		if (99 < iVar6)
		{
			a3 = a3 + 1;
		}
		if ((uint32_t)a3 < 2)
		{
			if (a2 == 8)
			{
				if ((iVar3 < 100) && (STATLIST_SetUnitStat(pUnit, 0x2b, iVar3 + 0x28, 0), 99 < iVar3 + 0x28))
				{
					a3 = a3 + 1;
				}
				if ((uint32_t)a3 < 2)
				{
					if ((iVar1 < 100) &&
					    (STATLIST_SetUnitStat(pUnit, 0x27, iVar1 + 0x28, 0), 99 < iVar1 + 0x28))
					{
						a3 = a3 + 1;
					}
					if ((((uint32_t)a3 < 2) && (iVar2 < 100)) &&
					    (STATLIST_SetUnitStat(pUnit, 0x29, iVar2 + 0x28, 0), 99 < iVar2 + 0x28))
					{
						return;
					}
				}
			}
			else
			{
				if (a2 == 9)
				{
					STATLIST_SetUnitStat(pUnit, 0x27, iVar1 + 0x4b, 0);
					return;
				}
				if (a2 == 0x12)
				{
					STATLIST_SetUnitStat(pUnit, 0x2b, iVar3 + 0x4b, 0);
					return;
				}
				if (a2 == 0x11)
				{
					STATLIST_SetUnitStat(pUnit, 0x29, iVar2 + 0x4b, 0);
					return;
				}
				if (a2 == 0x17)
				{
					STATLIST_SetUnitStat(pUnit, 0x2d, iVar4 + 0x4b, 0);
					return;
				}
				if (a2 == 0x19)
				{
					STATLIST_SetUnitStat(pUnit, 0x25, iVar6 + 0x14, 0);
					return;
				}
				if (a2 == 0x1b)
				{
					if ((iVar3 < 0x4b) &&
					    (STATLIST_SetUnitStat(pUnit, 0x2b, iVar3 + 0x14, 0), 99 < iVar3 + 0x14))
					{
						a3 = a3 + 1;
					}
					if ((uint32_t)a3 < 2)
					{
						if ((iVar1 < 0x4b) &&
						    (STATLIST_SetUnitStat(pUnit, 0x27, iVar1 + 0x14, 0), 99 < iVar1 + 0x14))
						{
							a3 = a3 + 1;
						}
						if ((((uint32_t)a3 < 2) && (iVar2 < 0x4b)) &&
						    (STATLIST_SetUnitStat(pUnit, 0x29, iVar2 + 0x14, 0), 99 < iVar2 + 0x14))
						{
							return;
						}
					}
				}
				else if (a2 == 0x1c)
				{
					STATLIST_SetUnitStat(pUnit, 0x24, iVar5 + 0x32, 0);
				}
			}
		}
	}
}

//D2Client.0x6FB45140
void __fastcall sub_6FB45140(int* a1)
{
	char* pcVar1;
	int* piVar2;
	int iVar3;
	uint8_t bVar4;

	if ((((a1 != nullptr) && (*a1 == 1)) && (iVar3 = a1[5], iVar3 != 0)) &&
	    ((pcVar1 = (char*)(iVar3 + 0x1c), pcVar1 != nullptr && (*pcVar1 != '\0'))))
	{
		if (iVar3 == 0)
		{
			bVar4 = 0;
		}
		else
		{
			bVar4 = *(uint8_t*)(iVar3 + 0x16) >> 3 & 1;
		}
		piVar2 = (int*)(&dword_6FB70D1C);
		do
		{
			if (*(code**)(byte_6FB917A8 + *piVar2 * 4) != nullptr)
			{
				(**(code**)(byte_6FB917A8 + *piVar2 * 4))(bVar4);
			}
			piVar2 = piVar2 + 1;
		} while ((int)piVar2 < (int)&tbl_6FB70D2C);
		iVar3 = 0;
		do
		{
			if (*(code**)(byte_6FB917A8 + (uint32_t)(uint8_t)pcVar1[iVar3] * 4) != nullptr)
			{
				(**(code**)(byte_6FB917A8 + (uint32_t)(uint8_t)pcVar1[iVar3] * 4))(bVar4);
			}
			iVar3 = iVar3 + 1;
		} while (iVar3 < 9);
	}
}

//D2Client.0x6FB451D0
void __fastcall sub_6FB451D0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int32_t DVar2;
	int local_8;
	int local_4;

	if ((a3 != 0) &&
	    (((UNITS_GetShiftedFrameMetrics(pUnit, &local_8, &local_4), pUnit == nullptr ||
	                                                                    (pUnit->dwAnimMode == 0)) &&
	        (local_8 == 4))))
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar2 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar2 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar2 + 2)) = 0;
		}
		else
		{
			DVar2 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		sub_6FB3EAF0((int)pUnit, 0x52, a3, (D2UnitStrc**)DVar2, 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, a3 + 1, (D2UnitStrc**)((int)DVar2 + 1), 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, a3 + 1, (D2UnitStrc**)((int)DVar2 + -1), 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, a3 + -1, (D2UnitStrc**)((int)DVar2 + 1), 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, a3 + -1, (D2UnitStrc**)((int)DVar2 + -1), 0, 1);
		sub_6FB55820(0x99a, pUnit, 0.0, 0.0, 0);
	}
}

//D2Client.0x6FB45300
void __fastcall sub_6FB45300(D2UnitStrc* pUnit, int a2, D2UnitStrc** pUnit2)
{
	D2UnitStrc** ppDVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	D2UnitStrc** ppDVar5;
	int iStack_10;
	int local_8;
	int local_4;

	if ((pUnit2 != nullptr) &&
	    (((UNITS_GetShiftedFrameMetrics(pUnit, &local_8, &local_4), pUnit == nullptr ||
	                                                                    (pUnit->dwAnimMode == 0)) &&
	        (local_8 == 4))))
	{
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			iStack_10 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_10 = 0;
		}
		else
		{
			iStack_10 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			pUnit2 = *(D2UnitStrc***)&pUnit->pDynamicPath->tTargetCoord;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			pUnit2 = nullptr;
		}
		else
		{
			pUnit2 = (D2UnitStrc**)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		sub_6FB3EAF0((int)pUnit, 0x75, iStack_10, pUnit2, 0, 1);
		ppDVar1 = (D2UnitStrc**)((int)pUnit2 + 1);
		iVar4 = iStack_10 + 1;
		sub_6FB3EAF0((int)pUnit, 0x75, iVar4, ppDVar1, 0, 1);
		ppDVar5 = (D2UnitStrc**)((int)pUnit2 + -1);
		sub_6FB3EAF0((int)pUnit, 0x75, iVar4, ppDVar5, 0, 1);
		iVar3 = iStack_10 + -1;
		sub_6FB3EAF0((int)pUnit, 0x75, iVar3, ppDVar1, 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x75, iVar3, ppDVar5, 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, iStack_10, pUnit2, 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, iVar4, ppDVar1, 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, iVar4, ppDVar5, 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, iVar3, ppDVar1, 0, 1);
		sub_6FB3EAF0((int)pUnit, 0x52, iVar3, ppDVar5, 0, 1);
		sub_6FB55820(0x99a, pUnit, 0.0, 0.0, 0);
	}
}

//D2Client.0x6FB454A0
void __fastcall sub_6FB454A0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;

	if (pUnit != nullptr)
	{
		uVar1 = pUnit->dwClassId;
		if (uVar1 < 0x101)
		{
			if (uVar1 == 0x100)
			{
				if (pUnit->dwAnimMode == 0)
				{
					sub_6FAB9E00();
					return;
				}
			}
			else
			{
				switch (uVar1)
				{
				case 0x2d:
					if (pUnit->dwAnimMode == 0)
					{
						sub_6FAB9900(pUnit);
						return;
					}
					break;
				case 0x9c:
					if (pUnit->dwAnimMode == 0)
					{
						sub_6FAB9C40();
						return;
					}
					break;
				case 0xd3:
					if (pUnit->dwAnimMode == 0)
					{
						sub_6FAB9D80((int*)pUnit);
						return;
					}
					break;
				case 0xe5:
					if (pUnit->dwAnimMode == 0)
					{
						sub_6FAB9C80((int*)pUnit);
						return;
					}
					break;
				case 0xf2:
					if (pUnit->dwAnimMode == 0)
					{
						sub_6FAB9B90();
						return;
					}
					break;
				case 0xf3:
					if (pUnit->dwAnimMode == 0)
					{
						sub_6FAB9E60((int)pUnit);
						return;
					}
				}
			}
		}
		else if (uVar1 < 0x1e0)
		{
			if (uVar1 == 0x1df)
			{
				if (pUnit->dwAnimMode == 0)
				{
					sub_6FAB94F0((int*)pUnit);
					return;
				}
			}
			else if (uVar1 == 0x10b)
			{
				if (pUnit->dwAnimMode == 0)
				{
					sub_6FAB9870();
					return;
				}
			}
			else if (uVar1 == 0x11c)
			{
				if (pUnit->dwAnimMode == 0xe)
				{
					sub_6FAB9D00((int*)pUnit);
					return;
				}
			}
			else if ((uVar1 == 0x16e) && (pUnit->dwAnimMode == 0))
			{
				sub_6FAB9A40(pUnit);
				return;
			}
		}
		else if (0x21b < uVar1)
		{
			if (uVar1 < 0x21f)
			{
				if (pUnit->dwAnimMode == 0)
				{
					sub_6FAB9700(pUnit);
				}
			}
			else if ((uVar1 == 0x220) && (pUnit->dwAnimMode == 0))
			{
				sub_6FAB9E80();
				return;
			}
		}
	}
}

//D2Client.0x6FB456D0
void __fastcall sub_6FB456D0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	int32_t DVar4;
	D2UnitStrc* local_4;

	if ((a3 != 0) || (a2 != 0x12))
	{
		local_4 = pUnit;
		if ((a2 == 0x2a) && ((pUnit == nullptr || (pUnit->dwAnimMode == 0))))
		{
			iVar2 = DATATBLS_GetMissileVelocityFromMissilesTxt(0x5a, 0);
			iVar3 = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
			sub_6FABD4D0(pUnit, (int*)pUnit, 0x5a, -1, 0, iVar3, iVar2);
		}
		UNITS_GetShiftedFrameMetrics(pUnit, &a3, (int*)&local_4);
		if (((pUnit == nullptr) || (pUnit->dwAnimMode == 0)) && (a3 == 4))
		{
			if (a2 == 10)
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
				iVar3 = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
				sub_6FB3EB50(pUnit, 0x9b, iVar2, (D2UnitStrc*)DVar4, 0, iVar3);
				return;
			}
			if (a2 == 0x12)
			{
				iVar2 = DATATBLS_GetMissileVelocityFromMissilesTxt(0x77, 0);
				iVar3 = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
				sub_6FABD4D0(pUnit, (int*)pUnit, 0xc2, -1, 0, iVar3, iVar2);
			}
		}
	}
}

//D2Client.0x6FB45800
void __fastcall sub_6FB45800(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	D2PlayerDataStrc* pDVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	int local_8;
	int local_4;

	if (((pUnit != nullptr) && (pUnit->dwUnitType == 1)) &&
	    (pDVar1 = pUnit->pPlayerData, pDVar1 != nullptr))
	{
		if (pUnit->dwAnimMode == 0)
		{
			UNITS_GetShiftedFrameMetrics(pUnit, &local_8, &local_4);
			if (local_8 == 0xd)
			{
				sub_6FB5BF70((int)pUnit);
				sub_6FB5BA70(pUnit, 0x34, 5, 0, 0, 0, 0, 0);
				sub_6FB5BA70(pUnit, 0x9c, 5, 0, 0, 0, 0, 0);
				pUnit->nActionFrame = 0;
				return;
			}
		}
		else if (pUnit->dwAnimMode == 0xc)
		{
			DVar3 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar3;
			if (((int)(((uint64_t)DVar3 & 0xffffffff) % 100) == 0) && ((int)pDVar1->pQuestData[2] < 100))
			{
				uVar2 = pUnit->dwUnitType;
				if (((uVar2 != 2) && (((int)uVar2 < 4 || (5 < (int)uVar2)))) &&
				    (pUnit->pDynamicPath != nullptr))
				{
					PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 != 2) &&
				    ((((int)uVar2 < 4 || (5 < (int)uVar2)) &&
				        (pUnit->pDynamicPath != nullptr))))
				{
					PATH_GetYPosition(pUnit->pDynamicPath);
				}
				sub_6FB3EDF0(pUnit, 0xe3, 4);
				pDVar1->pQuestData[2] = (D2BitBufferStrc*)&pDVar1->pQuestData[2]->nBits;
			}
		}
	}
}

//D2Client.0x6FB45910
void __fastcall sub_6FB45910(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	D2UnitStrc* local_4;

	if (a3 != 0)
	{
		local_4 = pUnit;
		UNITS_GetShiftedFrameMetrics(pUnit, &a3, (int*)&local_4);
		if (((pUnit != nullptr) && (pUnit->dwAnimMode == 3)) && (a3 == 2))
		{
			iVar1 = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
			sub_6FB45960((int*)pUnit, 0xc3, iVar1 >> 1);
		}
	}
}

//D2Client.0x6FB45960
void __fastcall sub_6FB45960(int* a1, int a2, int a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int* piVar6;
	int iStack_80;
	int aiStack_7c[9];
	int* local_58;
	int iStack_4c;
	int local_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	uint32_t uStack_30;
	int iStack_2c;
	code* pcStack_8;
	int iStack_4;

	if (a3 == 0)
	{
		a3 = 1;
	}
	if ((a2 != 0xc3) ||
	    ((((a1 != nullptr && (*a1 == 1)) && (a1[5] != 0)) &&
	        ((*(uint8_t*)(a1[5] + 0x17) & 1) != 0))))
	{
		piVar6 = aiStack_7c + 8;
		for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*piVar6 = 0;
			piVar6 = piVar6 + 1;
		}
		iVar4 = *a1;
		aiStack_7c[8] = 0x21;
		local_58 = a1;
		if ((iVar4 == 2) || ((3 < iVar4 && (iVar4 < 6))))
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
		iVar4 = *a1;
		if ((iVar4 == 2) || ((3 < iVar4 && (iVar4 < 6))))
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
		uStack_30 = 0;
		iStack_2c = a3;
		iStack_4c = a2;
		if (a2 != 0x141)
		{
			pcStack_8 = (code*)(sub_6FAC9E80);
		}
		aiStack_7c[0] = 0;
		aiStack_7c[1] = 1;
		aiStack_7c[2] = 0;
		aiStack_7c[3] = 0xffffffff;
		aiStack_7c[4] = 0xffffffff;
		aiStack_7c[5] = 0;
		aiStack_7c[6] = 1;
		aiStack_7c[7] = 0;
		iStack_80 = 0;
		do
		{
			iVar4 = *a1;
			if ((iVar4 == 2) || ((3 < iVar4 && (iVar4 < 6))))
			{
				iVar4 = *(int*)(a1[0xb] + 0xc);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iVar4 = 0;
			}
			else
			{
				iVar4 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			iVar3 = *a1;
			if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
			{
				iVar3 = *(int*)(a1[0xb] + 0x10);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iVar3 = 0;
			}
			else
			{
				iVar3 = PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			iVar1 = *(int*)((int)aiStack_7c + iStack_80);
			iVar2 = *(int*)((int)aiStack_7c + iStack_80 + 0x10);
			iVar5 = 0;
			do
			{
				iStack_40 = iVar1 + iVar4;
				iStack_3c = iVar2 + iVar3;
				iStack_4 = iVar5;
				sub_6FB3E070((uint32_t*)(aiStack_7c + 8));
				iVar5 = iVar5 + 1;
			} while (iVar5 < 2);
			iStack_80 = iStack_80 + 4;
		} while (iStack_80 < 0x10);
	}
}

//D2Client.0x6FB45B20
void __fastcall sub_6FB45B20(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;

	if ((a3 != 0) && ((pUnit == nullptr || (pUnit->dwAnimMode != 3))))
	{
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
		sub_6FB45960((int*)pUnit, 0xc3, iVar1 >> 1);
	}
}

//D2Client.0x6FB45B60
void __fastcall sub_6FB45B60(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	int iVar1;
	int local_8;
	int local_4;

	UNITS_GetShiftedFrameMetrics(pUnit, &local_8, &local_4);
	if ((((pUnit == nullptr) || (pUnit->dwAnimMode == 3)) || (pUnit->dwAnimMode == 0)) && (local_8 == 2))
	{
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
		sub_6FB45960((int*)pUnit, 0xe1, iVar1);
	}
}

//D2Client.0x6FB45BB0
void __fastcall sub_6FB45BB0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint8_t* pbVar1;
	int iVar2;
	D2DynamicPathStrc* pDynamicPath;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	int32_t DVar5;
	int iVar6;
	int32_t DVar7;
	int iVar8;
	uint32_t uVar9;
	int iVar10;
	uint64_t DStack_8;

	if (((a3 != 0) && (pUnit != nullptr)) && (pUnit->dwUnitType == 3))
	{
		iVar2 = pUnit->dwClassId;
		pDVar3 = sub_6FB26AD0((int)pUnit);
		if ((((pDVar3 != nullptr) && (-1 < iVar2)) &&
		        ((iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) &&
		            ((iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar6 != 0 &&
		                                                                                               (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar6 + 5)) == 0)))))) &&
		    ((pDVar3->dwUnitType != 1 ||
		        ((pDVar3->pPlayerData == nullptr ||
		            (-1 < *(char*)((int)pDVar3->pPlayerData->pQuestData + 6)))))))
		{
			pDynamicPath = pUnit->pDynamicPath;
			pDVar4 = sub_6FB296A0((int)pDVar3);
			if (pDVar4 == nullptr)
			{
				a3 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
				DVar5 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
			}
			else
			{
				uVar9 = pDVar4->dwUnitType;
				if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
				{
					a3 = pDVar4->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar4->pDynamicPath == nullptr)
				{
					a3 = 0;
				}
				else
				{
					a3 = PATH_GetXPosition(pDVar4->pDynamicPath);
				}
				uVar9 = pDVar4->dwUnitType;
				if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
				{
					DVar5 = (*(int32_t*)&pDVar4->pDynamicPath->tTargetCoord);
				}
				else if (pDVar4->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
				}
				else
				{
					DVar5 = (int32_t)PATH_GetYPosition(pDVar4->pDynamicPath);
				}
			}
			SEED_InitSeed((D2SeedStrc*)(&DStack_8));
			SEED_InitLowSeed((D2SeedStrc*)(&DStack_8), 0x53454953);
			(*(uint32_t*)((uint8_t*)&DStack_8 + 4)) = pDVar3->dwUnitId;
			uVar9 = pDVar3->dwUnitType;
			if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
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
			iVar6 = iVar6 - a3;
			uVar9 = pDVar3->dwUnitType;
			if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
			{
				DVar7 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
			}
			else
			{
				DVar7 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
			iVar8 = (int)DVar7 - (int)DVar5;
			if (iVar6 < 0)
			{
				iVar6 = -1;
			}
			else if (0 < iVar6)
			{
				iVar6 = 1;
			}
			if (iVar8 < 0)
			{
				iVar8 = -1;
			}
			else if (0 < iVar8)
			{
				iVar8 = 1;
			}
			if ((0x3e < iVar2) && (iVar2 < 0x43))
			{
				iVar8 = 0;
				iVar6 = 0;
			}
			if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
			{
				pbVar1 = (uint8_t*)((int)pDVar3->pPlayerData->pQuestData + 6);
				*pbVar1 = *pbVar1 | 0x80;
			}
			uVar9 = MISSILE_GetLevel(pUnit);
			iVar10 = MISSILE_GetSkill(pUnit);
			sub_6FB3EB50(pDVar3, iVar2, a3 - iVar8, (D2UnitStrc*)((int)DVar5 + iVar6), iVar10, uVar9);
			uVar9 = MISSILE_GetLevel(pUnit);
			iVar10 = MISSILE_GetSkill(pUnit);
			sub_6FB3EB50(pDVar3, iVar2, iVar8 + a3, (D2UnitStrc*)((int)DVar5 - iVar6), iVar10, uVar9);
			if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
			{
				pbVar1 = (uint8_t*)((int)pDVar3->pPlayerData->pQuestData + 6);
				*pbVar1 = *pbVar1 & 0x7f;
			}
		}
	}
}

//D2Client.0x6FB45E10
void __fastcall sub_6FB45E10(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	int32_t DVar2;
	int iVar3;
	int local_8;
	int local_4;

	UNITS_GetShiftedFrameMetrics(pUnit, &local_8, &local_4);
	if (((pUnit == nullptr) || (pUnit->dwAnimMode == 0)) && (local_8 == 4))
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar2 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar2 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar2 + 2)) = 0;
		}
		else
		{
			DVar2 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
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
		sub_6FB3EB50(pUnit, 0x2a, iVar3, (D2UnitStrc*)DVar2, 0, 1);
	}
}

//D2Client.0x6FB45EB0
void __fastcall sub_6FB45EB0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	short sVar1;
	uint32_t uVar2;
	uint8_t bVar3;
	int32_t DVar4;
	int iVar5;
	int32_t DVar6;
	uint32_t uVar7;
	int local_8;
	int local_4;

	if (((pUnit == nullptr) || (iVar5 = pUnit->dwClassId, iVar5 < 0)) ||
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar5))
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar5 * 0x1a8;
	}
	bVar3 = sub_6FAAC090();
	sVar1 = *(short*)(iVar5 + 0x56 + (uint32_t)bVar3 * 2);
	UNITS_GetShiftedFrameMetrics(pUnit, &local_8, &local_4);
	if ((pUnit != nullptr) && (pUnit->dwAnimMode != 0))
	{
		return;
	}
	if (local_8 != 4)
	{
		return;
	}
	if (sVar1 == 1)
	{
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			uVar7 = 0x1ab;
			iVar5 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar5 = 0;
			uVar7 = 0x1ab;
		}
		else
		{
			iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
			uVar7 = 0x1ab;
		}
	}
	else
	{
		if (sVar1 < 2)
			goto LAB_6fb45ffb;
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
		uVar7 = 0x1ac;
	}
	sub_6FB3EB50(pUnit, uVar7, iVar5, (D2UnitStrc*)DVar4, 0, 1);
LAB_6fb45ffb:
	uVar2 = pUnit->dwUnitType;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
	uVar2 = pUnit->dwUnitType;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
	sub_6FB3EB50(pUnit, 0x1aa, iVar5, (D2UnitStrc*)DVar6, 0, 1);
}

//D2Client.0x6FB46070
void __fastcall sub_6FB46070(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	int32_t DVar3;

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
	sub_6FB3EAF0((int)pUnit, 0x75, iVar2, (D2UnitStrc**)DVar3, 0, 1);
	sub_6FB3EAF0((int)pUnit, 0x221, iVar2, (D2UnitStrc**)DVar3, 0, 1);
	sub_6FB55820(0x99a, pUnit, 0.0, 0.0, 0);
}

//D2Client.0x6FB46110
void __fastcall sub_6FB46110(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;
	int iVar2;
	int32_t DVar3;

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
	sub_6FB3EAF0((int)pUnit, 0x75, iVar2, (D2UnitStrc**)DVar3, 0, 1);
	sub_6FB3EAF0((int)pUnit, 0x221, iVar2, (D2UnitStrc**)DVar3, 0, 1);
	sub_6FB55820(0x99a, pUnit, 0.0, 0.0, 0);
}

//D2Client.0x6FB461B0
void __fastcall sub_6FB461B0(D2UnitStrc* pUnit)
{
	sub_6FB461C0(pUnit, 0, 0);
}

//D2Client.0x6FB461C0
void __fastcall sub_6FB461C0(D2UnitStrc* pUnit, int a2, int a3)
{
	D2WaypointDataStrc** ppDVar1;
	D2PlayerDataStrc* pDVar2;
	int iVar3;
	uint8_t bVar4;

	if ((((pUnit != nullptr) && (pUnit->dwUnitType == 1)) &&
	        (pDVar2 = pUnit->pPlayerData, pDVar2 != nullptr)) &&
	    (ppDVar1 = pDVar2->pWaypointData, ppDVar1 != nullptr))
	{
		if (pDVar2 == nullptr)
		{
			bVar4 = 0;
		}
		else
		{
			bVar4 = *(uint8_t*)((int)pDVar2->pQuestData + 6) >> 3 & 1;
		}
		iVar3 = 0;
		if (a3 != 4)
		{
			do
			{
				if (*(code**)(byte_6FB91858 + (a3 + (uint32_t) * (uint8_t*)(iVar3 + (int)ppDVar1) * 5) * 4) != nullptr)
				{
					(**(code**)(byte_6FB91858 + (a3 + (uint32_t) * (uint8_t*)(iVar3 + (int)ppDVar1) * 5) * 4))(bVar4);
				}
				iVar3 = iVar3 + 1;
			} while (iVar3 < 9);
			return;
		}
		do
		{
			if (*(code**)(byte_6FB91868 + (uint32_t) * (uint8_t*)(iVar3 + (int)ppDVar1) * 0x14) != nullptr)
			{
				(**(code**)(byte_6FB91868 + (uint32_t) * (uint8_t*)(iVar3 + (int)ppDVar1) * 0x14))(bVar4);
			}
			iVar3 = iVar3 + 1;
		} while (iVar3 < 9);
	}
}

//D2Client.0x6FB46270
void __fastcall sub_6FB46270(D2UnitStrc* pUnit)
{
	sub_6FB461C0(pUnit, 0, 1);
}

//D2Client.0x6FB46280
void __fastcall sub_6FB46280(D2UnitStrc* pUnit)
{
	sub_6FB461C0(pUnit, 0, 2);
}

//D2Client.0x6FB46290
void __fastcall sub_6FB46290(D2UnitStrc* pUnit)
{
	sub_6FB461C0(pUnit, 0, 3);
}

//D2Client.0x6FB462A0
void __fastcall sub_6FB462A0(D2UnitStrc* pUnit, int a2)
{
	if (((pUnit != nullptr) && (a2 != 0)) && (pUnit->dwUnitType == 1))
	{
		sub_6FB461C0(pUnit, a2, 4);
	}
}

//D2Client.0x6FB462C0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB462C0(int* a1, uint16_t* a2, int a3, short a4)
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	Unicode* pUVar3;
	Font nFontSize;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	uint32_t uStack_14;

	iVar6 = 0;
	*a2 = 0;
	if ((((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0)) &&
	    (iVar2 = a1[5] + 0x1c, iVar2 != 0))
	{
		bVar1 = sub_6FB40D20(a1);
		if (D2C_ZEXT(bVar1) != 0)
		{
			if (a4 == 0)
			{
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xc95));
				Unicode::strcpy((Unicode*)a2, pUVar3);
				return;
			}
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(a4));
			Unicode::strcpy((Unicode*)a2, pUVar3);
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
			Unicode::strcat((Unicode*)a2, pUVar3);
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xc95));
			Unicode::strcat((Unicode*)a2, pUVar3);
			return;
		}
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
		iVar7 = 0;
		if (a4 != 0)
		{
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(a4));
			Unicode::strcat((Unicode*)a2, pUVar3);
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(a4));
			iVar7 = Unicode::strlen(pUVar3);
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(a4));
			iVar6 = D2Win_10121_GetTextWidth(pUVar3);
		}
		uStack_14 = (uint32_t)(a4 != 0);
		(*(uint32_t*)&a4) = 0;
		do
		{
			uVar4 = (uint32_t) * (uint8_t*)((*(uint32_t*)&a4) + iVar2);
			if (*(short*)(byte_6FB91BB8 + uVar4 * 2) != 0)
			{
				if ((uStack_14 != 0) && (iVar7 + 1 < a3 + -1))
				{
					Unicode::strcat((Unicode*)a2, (Unicode*)&byte_6FBBC230);
					iVar5 = D2Win_10121_GetTextWidth((Unicode*)&byte_6FBBC230);
					iVar6 = iVar6 + iVar5;
					iVar7 = iVar7 + 1;
				}
				if (iVar7 < a3 + -1)
				{
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(byte_6FB91BB8 + uVar4 * 2)));
					iVar5 = Unicode::strlen(pUVar3);
					if (iVar5 + iVar7 < a3 + -1)
					{
						iVar5 = Unicode::strlen(pUVar3);
						iVar7 = iVar7 + iVar5;
						iVar5 = D2Win_10121_GetTextWidth(pUVar3);
						iVar6 = iVar6 + iVar5;
						Unicode::strcat((Unicode*)a2, pUVar3);
						uStack_14 = uStack_14 + 1;
					}
				}
				if (0x1e0 < iVar6)
					break;
			}
			(*(uint32_t*)&a4) = (*(uint32_t*)&a4) + 1;
		} while ((*(uint32_t*)&a4) < 9);
		D2Win_10127_SetFont(nFontSize);
	}
}

//D2Client.0x6FB464A0
int __fastcall sub_6FB464A0(int a1, int a2)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	int* piVar5;

	if (a1 == 0)
	{
	switchD_6fb464c6_caseD_95:
		return 0;
	}
	uVar4 = *(uint32_t*)(a1 + 4);
	if (0xaf < uVar4)
	{
		if (uVar4 < 0xff)
		{
			if (uVar4 == 0xfe)
			{
				piVar5 = (int*)&byte_6FB91C6C;
				goto LAB_6fb464d2;
			}
			switch (uVar4)
			{
			case 0xb0:
				piVar5 = (int*)&byte_6FB91C9C;
				break;
			case 0xb1:
				piVar5 = (int*)&byte_6FB91CE4;
				break;
			case 0xb2:
				piVar5 = (int*)&byte_6FB91D14;
				break;
			default:
				goto switchD_6fb464c6_caseD_95;
			case 0xc6:
				piVar5 = (int*)&byte_6FB91D5C;
				break;
			case 199:
				piVar5 = (int*)&byte_6FB91CFC;
				break;
			case 200:
				piVar5 = (int*)&byte_6FB91D2C;
				break;
			case 0xc9:
				piVar5 = (int*)&byte_6FB91DD4;
				break;
			case 0xca:
				piVar5 = (int*)&byte_6FB91E04;
				break;
			case 0xd2:
				piVar5 = (int*)&byte_6FB91E1C;
				break;
			case 0xf4:
			case 0xf5:
			case 0xf6:
				goto switchD_6fb464c6_caseD_92;
			case 0xfb:
				goto switchD_6fb46520_caseD_fb;
			case 0xfc:
				piVar5 = (int*)&byte_6FB91C84;
				break;
			case 0xfd:
				piVar5 = (int*)&byte_6FB91D8C;
			}
			goto LAB_6fb464d2;
		}
		if (uVar4 < 0x201)
		{
			if (uVar4 == 0x200)
			{
				piVar5 = (int*)&byte_6FB91E94;
				goto LAB_6fb464d2;
			}
			if (0x129 < uVar4)
			{
				if (uVar4 == 0x195)
				{
					piVar5 = (int*)&byte_6FB91DA4;
				}
				else
				{
					if (uVar4 != 0x1ff)
					{
						return 0;
					}
					piVar5 = (int*)&byte_6FB91EDC;
				}
				goto LAB_6fb464d2;
			}
			if (uVar4 == 0x129)
			{
				piVar5 = (int*)&byte_6FB91E34;
				goto LAB_6fb464d2;
			}
			if (uVar4 == 0xff)
			{
				piVar5 = (int*)&byte_6FB91E4C;
				goto LAB_6fb464d2;
			}
			if (uVar4 == 0x101)
			{
				piVar5 = (int*)&byte_6FB91D74;
				goto LAB_6fb464d2;
			}
			if (uVar4 != 0x109)
			{
				return 0;
			}
		switchD_6fb464c6_caseD_92:
			piVar5 = (int*)&byte_6FB91CB4;
		}
		else
		{
			switch (uVar4)
			{
			case 0x201:
				piVar5 = (int*)&byte_6FB91EC4;
				break;
			case 0x202:
				piVar5 = (int*)&byte_6FB91EF4;
				break;
			case 0x203:
				piVar5 = (int*)&byte_6FB91EAC;
				break;
			default:
				goto switchD_6fb464c6_caseD_95;
			case 0x208:
				goto switchD_6fb464c6_caseD_92;
			case 0x209:
			switchD_6fb46520_caseD_fb:
				piVar5 = (int*)&byte_6FB91E64;
			}
		}
		goto LAB_6fb464d2;
	}
	if (uVar4 == 0xaf)
	{
	switchD_6fb464c6_caseD_9b:
		piVar5 = (int*)(&dword_6FB91E7C);
	}
	else
	{
		switch (uVar4)
		{
		case 0x92:
			goto switchD_6fb464c6_caseD_92;
		case 0x93:
			piVar5 = (int*)&byte_6FB91D44;
			break;
		case 0x94:
			piVar5 = (int*)&byte_6FB91C54;
			break;
		default:
			goto switchD_6fb464c6_caseD_95;
		case 0x96:
			piVar5 = (int*)&byte_6FB91DEC;
			break;
		case 0x9a:
			piVar5 = (int*)&byte_6FB91CCC;
			break;
		case 0x9b:
			goto switchD_6fb464c6_caseD_9b;
		}
	}
LAB_6fb464d2:
	if (a2 != 2)
	{
		uVar4 = 0;
		do
		{
			iVar2 = *piVar5;
			if (((a2 == 0) && (piVar5[1] != 0)) && (uVar1 = sub_6FB57150(2), uVar1 == 0))
			{
				iVar2 = piVar5[1];
			}
			if ((piVar5[2] != 0) && ((iVar2 == 0 || (uVar1 = sub_6FB57150(3), uVar1 == 0))))
			{
				iVar2 = ENVIRONMENT_GetCycleIndexFromAct(ghAct);
				if (iVar2 == 1)
				{
					iVar2 = piVar5[2];
				}
				else if ((iVar2 < 2) || (3 < iVar2))
				{
					iVar2 = piVar5[2] + 2;
				}
				else
				{
					iVar2 = piVar5[2] + 1;
				}
			}
			iVar2 = sub_6FB55310(iVar2);
		} while ((iVar2 == piVar5[4]) && (uVar4 = uVar4 + 1, uVar4 < 0x14));
		piVar5[4] = iVar2;
		iVar3 = sub_6FAABF80();
		piVar5[5] = iVar3;
		return iVar2;
	}
	return piVar5[3];
}

//D2Client.0x6FB467A0
int __fastcall sub_6FB467A0(short a1)
{
	int* piVar1;

	if (dword_6FB91C50 != 0)
	{
		piVar1 = (int*)(&dword_6FB91F10);
		do
		{
			if (*piVar1 == 0)
			{
				return 0;
			}
			if ((short)piVar1[1] == a1)
			{
				return *piVar1;
			}
			piVar1 = piVar1 + 2;
		} while (piVar1 != nullptr);
	}
	return 0;
}

//D2Client.0x6FB467D0
void __fastcall sub_6FB467D0(int a1)
{
	dword_6FB91C50 = a1;
}
