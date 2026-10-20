#include "Unit/PlrSkills.h"

#include "Draw/DLightMap.h"
#include "Engine/Gfx.h"
#include "Engine/Particle.h"
#include "Game/Game.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Skills/SkillsBar.h"
#include "Skills/SkillsNec.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/CUnitEvent.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB93EE0
uint8_t byte_6FB93EE0[128] = {0, 0, 0, 0, 0x40, 0xBB, 0xB4, 0x6F, 0x80, 0xBC, 0xB4, 0x6F, 0x40, 0xBD, 0xB4, 0x6F, 0x20, 0xBE, 0xB4, 0x6F, 0x70, 0xBE, 0xB4, 0x6F, 0xB0, 0xC1, 0xB4, 0x6F, 0x60, 0xC8, 0xB4, 0x6F, 0x60, 0xC5, 0xB4, 0x6F, 0x40, 0xC9, 0xB4, 0x6F, 0x50, 0xC9, 0xB4, 0x6F, 0x10, 0xCC, 0xB4, 0x6F, 0x20, 0xCC, 0xB4, 0x6F, 0x80, 0xCC, 0xB4, 0x6F, 0xD0, 0xCC, 0xB4, 0x6F, 0x70, 0xCD, 0xB4, 0x6F, 0xA0, 0xCD, 0xB4, 0x6F, 0xC0, 0xCF, 0xB4, 0x6F, 0x60, 0xD0, 0xB4, 0x6F, 0x10, 0xD1, 0xB4, 0x6F};
//D2Client.0x6FB93F60
uint8_t byte_6FB93F60[120] = {0, 0, 0, 0, 0, 0xBC, 0xB4, 0x6F, 0x60, 0xBE, 0xB4, 0x6F, 0x60, 0xBF, 0xB4, 0x6F, 0xD0, 0xC8, 0xB4, 0x6F, 0xD0, 0xC3, 0xB4, 0x6F, 0x40, 0xC9, 0xB4, 0x6F, 0x50, 0xCA, 0xB4, 0x6F, 0x50, 0xCC, 0xB4, 0x6F, 0xA0, 0xCC, 0xB4, 0x6F, 0xC0, 0xCC, 0xB4, 0x6F, 0x50, 0xCF, 0xB4, 0x6F, 0x10, 0xD1, 0xB4, 0x6F};

//D2Client.0x6FB4B980
void __fastcall sub_6FB4B980(D2UnitStrc* pUnit, uint32_t a2)
{
	short sVar1;
	D2SkillStrc* pSkill;
	uint32_t uVar2;
	int iVar3;
	bool bVar4;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill != nullptr)
	{
		uVar2 = 6;
		if (pUnit != nullptr)
		{
			uVar2 = pUnit->dwUnitType;
		}
		if (uVar2 == 0)
		{
			if (pUnit == nullptr)
			{
				uVar2 = 0;
			}
			else
			{
				uVar2 = pUnit->dwAnimMode;
			}
			bVar4 = uVar2 == 0x12;
		}
		else
		{
			if (uVar2 != 1)
			{
				return;
			}
			if (pUnit == nullptr)
			{
				bVar4 = false;
			}
			else
			{
				bVar4 = pUnit->dwAnimMode == 0xe;
			}
		}
		if ((((bVar4) &&
		         (iVar3 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__), -1 < iVar3)) &&
		        (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c, iVar3 != 0))
		{
			sVar1 = *(short*)(iVar3 + 0x2e);
			if (sVar1 == 0x43)
			{
				uVar2 = SKILLS_GetFlags(pSkill);
				if ((uVar2 & 1) != 0)
				{
					sub_6FAC9620(pUnit, a2, 1);
				}
			}
			else if (sVar1 == 0x4c)
			{
				sub_6FAC23F0(pUnit, a2, 1);
				return;
			}
		}
	}
}

//D2Client.0x6FB4BA60
void __fastcall sub_6FB4BA60(D2UnitStrc* pUnit, uint32_t a2)
{
	short sVar1;
	D2SkillStrc* pSkill;
	uint32_t uVar2;
	int iVar3;
	bool bVar4;

	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill != nullptr)
	{
		uVar2 = 6;
		if (pUnit != nullptr)
		{
			uVar2 = pUnit->dwUnitType;
		}
		if (uVar2 == 0)
		{
			if (pUnit == nullptr)
			{
				uVar2 = 0;
			}
			else
			{
				uVar2 = pUnit->dwAnimMode;
			}
			bVar4 = uVar2 == 0x12;
		}
		else
		{
			if (uVar2 != 1)
			{
				return;
			}
			if (pUnit == nullptr)
			{
				bVar4 = false;
			}
			else
			{
				bVar4 = pUnit->dwAnimMode == 0xe;
			}
		}
		if ((((bVar4) &&
		         (iVar3 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__), -1 < iVar3)) &&
		        (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c, iVar3 != 0))
		{
			sVar1 = *(short*)(iVar3 + 0x2e);
			if (sVar1 == 0x43)
			{
				uVar2 = SKILLS_GetFlags(pSkill);
				if ((uVar2 & 1) != 0)
				{
					sub_6FAC9620(pUnit, a2, 0);
				}
			}
			else if (sVar1 == 0x4c)
			{
				sub_6FAC23F0(pUnit, a2, 0);
				return;
			}
		}
	}
}

//D2Client.0x6FB4BB40
void __fastcall sub_6FB4BB40(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	int iVar2;

	if (((((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xc4))) && (iVar1 = *(int*)(iVar2 + 0xbc) + a2 * 0x3c, iVar1 != 0)) &&
	        ((((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar1 + 0x10)) != 0 &&
	            (0 < *(short*)(iVar1 + 0xe))))) &&
	    (((int)*(short*)(iVar1 + 0xe) < *(int*)(iVar2 + 0xbc0) &&
	        ((-1 < *(short*)(iVar1 + 0x18) && ((int)*(short*)(iVar1 + 0x18) <= *(int*)(iVar2 + 0xbd4)))))))
	{
		iVar2 = 0;
		do
		{
			sub_6FB5BEC0(pUnit, 0, *(short*)(iVar1 + 0xe) + iVar2);
			iVar2 = iVar2 + 1;
		} while (iVar2 < 3);
		iVar2 = STATLIST_UnitGetStatValue(pUnit, (int)*(short*)(iVar1 + 0x18), 0);
		if ((0 < iVar2) && (iVar2 < 4))
		{
			sub_6FB5BA70(pUnit, *(short*)(iVar1 + 0xe) + -1 + iVar2, 3, 0, 0, 0, 0, 0);
		}
	}
}

//D2Client.0x6FB4BC00
void __fastcall sub_6FB4BC00(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	int iVar2;

	if (((((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xc4))) && (iVar1 = *(int*)(iVar2 + 0xbc) + a2 * 0x3c, iVar1 != 0)) &&
	        ((((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar1 + 0x10)) != 0 &&
	            (0 < *(short*)(iVar1 + 0xe))))) &&
	    (((int)*(short*)(iVar1 + 0xe) < *(int*)(iVar2 + 0xbc0) &&
	        ((-1 < *(short*)(iVar1 + 0x18) && ((int)*(short*)(iVar1 + 0x18) <= *(int*)(iVar2 + 0xbd4)))))))
	{
		iVar2 = 0;
		do
		{
			sub_6FB5BEC0(pUnit, 0, *(short*)(iVar1 + 0xe) + iVar2);
			iVar2 = iVar2 + 1;
		} while (iVar2 < 3);
	}
}

//D2Client.0x6FB4BC80
void __fastcall sub_6FB4BC80(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	D2ActiveRoomStrc* pRoom;
	D2StatListStrc* pStatList;
	int iVar2;
	int iVar3;

	pRoom = UNITS_GetRoom(pUnit);
	if (pRoom != nullptr)
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
		if (pStatList != nullptr)
		{
			iVar2 = STATLIST_GetStatValue(pStatList, 0x15e, 0);
			iVar3 = STATLIST_GetStatValue(pStatList, 0x15f, 0);
			if (((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
			    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar1 != 0))
			{
				iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar1 + 0x60), iVar2, iVar3);
				iVar3 = DUNGEON_GetLevelIdFromRoom(pRoom);
				sub_6FAB8F70(5, (iVar2 * 3) / 5, (iVar2 * 2) / 5, iVar3, 0);
			}
		}
	}
}

//D2Client.0x6FB4BD40
void __fastcall sub_6FB4BD40(D2UnitStrc* pUnit, int a2)
{
	D2UnitStrc* pDVar1;
	D2StatListStrc* pStatList;
	int nSkillId;
	int nSkillLevel;
	D2SkillStrc* pSkill;
	int iVar2;

	pDVar1 = CUNIT_GetPlayer();
	if (pUnit != pDVar1)
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
		if (pStatList != nullptr)
		{
			nSkillId = STATLIST_GetStatValue(pStatList, 0x15e, 0);
			nSkillLevel = STATLIST_GetStatValue(pStatList, 0x15f, 0);
			pSkill = SKILLS_GetSkillById(pUnit, nSkillId, 0xffffffff);
			if (pSkill == nullptr)
			{
				iVar2 = 0;
			}
			else
			{
				iVar2 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
			}
			if (iVar2 != nSkillLevel)
			{
				if (((nSkillId < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= nSkillId)) ||
				    (iVar2 = (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + 300 +
				                            nSkillId * 0x23c),
				        iVar2 < 1))
				{
					iVar2 = 0x14;
				}
				if (iVar2 < nSkillLevel)
				{
					SKILLS_AssignSkill(pUnit, nSkillId, iVar2, 0, __FILE__, __LINE__);
					D2Common_11030(pUnit, nSkillId, nSkillLevel - iVar2);
					return;
				}
				SKILLS_AssignSkill(pUnit, nSkillId, nSkillLevel, 0,
				    __FILE__, __LINE__);
			}
		}
	}
}

//D2Client.0x6FB4BE20
void __fastcall sub_6FB4BE20(D2UnitStrc* pUnit, int a2)
{
	D2StatListStrc* pStatList;
	uint32_t nOwnerType;
	uint32_t nOwnerId;

	pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
	if (pStatList != nullptr)
	{
		nOwnerType = STATLIST_GetStatValue(pStatList, 0x161, 0);
		if (nOwnerType < 6)
		{
			nOwnerId = STATLIST_GetStatValue(pStatList, 0x162, 0);
			UNITS_StoreOwnerTypeAndGUID(pUnit, nOwnerType, nOwnerId);
		}
	}
}

//D2Client.0x6FB4BE60
void __fastcall sub_6FB4BE60(D2UnitStrc* pUnit)
{
	UNITS_StoreOwner(pUnit, nullptr);
}

//D2Client.0x6FB4BE70
void __fastcall sub_6FB4BE70(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	D2StatListStrc* pStatList;
	D2DynamicPathStrc* pDVar2;
	int32_t DVar3;
	int nX;
	int* piVar4;

	if ((pUnit != nullptr) && (pUnit->dwUnitType == 1))
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
		if (pStatList != nullptr)
		{
			pDVar2 = (D2DynamicPathStrc*)STATLIST_GetStatValue(pStatList, 0x163, 0);
			uVar1 = pUnit->dwAnimMode;
			sub_6FB41900(pUnit, pDVar2);
			piVar4 = (int*)0x8;
			if (uVar1 != 8)
			{
				piVar4 = (int*)0x1;
			}
			sub_6FB4F410(pUnit, piVar4);
			if (pDVar2 == (D2DynamicPathStrc*)0x21f)
			{
				uVar1 = pUnit->dwUnitType;
				pDVar2 = pUnit->pDynamicPath;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar3 = (*(int32_t*)&pDVar2->tTargetCoord);
				}
				else if (pDVar2 == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
				}
				else
				{
					DVar3 = (int32_t)PATH_GetYPosition(pDVar2);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 != 2) && (((int)uVar1 < 4 || (5 < (int)uVar1))))
				{
					if (pUnit->pDynamicPath != nullptr)
					{
						nX = PATH_GetXPosition(pUnit->pDynamicPath);
						D2Common_10216(pDVar2, nX, (int)DVar3 + 10, 1);
						return;
					}
					D2Common_10216(pDVar2, 0, (int)DVar3 + 10, 1);
					return;
				}
				D2Common_10216(pDVar2, pUnit->pDynamicPath->dwClientCoordY, (int)DVar3 + 10, 1);
			}
		}
	}
}

//D2Client.0x6FB4BF60
void __fastcall sub_6FB4BF60(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	int nOverlayId;
	int iVar2;
	int local_10;
	int local_c;
	int local_8;
	int local_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar2 != 0))
	{
		if (*(short*)(iVar2 + 10) < 0)
		{
			nOverlayId = -1;
		}
		else
		{
			nOverlayId = (int)*(short*)(iVar2 + 10);
		}
		if (*(short*)(iVar2 + 2) < 0)
		{
			local_10 = -1;
		}
		else
		{
			local_10 = (int)*(short*)(iVar2 + 2);
		}
		if (*(short*)(iVar2 + 4) < 0)
		{
			local_c = -1;
		}
		else
		{
			local_c = (int)*(short*)(iVar2 + 4);
		}
		if (*(short*)(iVar2 + 6) < 0)
		{
			local_8 = -1;
		}
		else
		{
			local_8 = (int)*(short*)(iVar2 + 6);
		}
		if (*(short*)(iVar2 + 8) < 0)
		{
			local_4 = -1;
		}
		else
		{
			local_4 = (int)*(short*)(iVar2 + 8);
		}
		if (nOverlayId != -1)
		{
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(nOverlayId);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + nOverlayId);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(nOverlayId);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + nOverlayId);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(nOverlayId);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + nOverlayId);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
		}
		if (local_10 != -1)
		{
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_10);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + local_10);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_10);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + local_10);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_10);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + local_10);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
		}
		if (local_c != -1)
		{
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_c);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + local_c);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_c);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + local_c);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_c);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + local_c);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
		}
		if (local_8 != -1)
		{
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_8);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + local_8);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
		}
		if (local_4 != -1)
		{
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_4);
			iVar2 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar2 + local_4);
					iVar2 = iVar2 + 1;
				} while (iVar2 < (int)uVar1);
			}
		}
	}
}

//D2Client.0x6FB4C1B0
void __fastcall sub_6FB4C1B0(D2UnitStrc* pUnit, int a2)
{
	D2StatListStrc* pStatList;
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	int nValue;
	uint32_t uStack_20;
	uint32_t uStack_1c;
	uint32_t uStack_14;
	uint32_t uStack_c;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar3 != 0))
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
		if (pStatList != nullptr)
		{
			iVar1 = STATLIST_GetStatValue(pStatList, 0x84, 0);
			iVar2 = STATLIST_GetStatValue(pStatList, 0x85, 0);
			iVar5 = -1;
			if (*(short*)(iVar3 + 10) < 0)
			{
				uStack_c = -1;
			}
			else
			{
				uStack_c = (int)*(short*)(iVar3 + 10);
			}
			if (*(short*)(iVar3 + 2) < 0)
			{
				uStack_20 = 0xffffffff;
			}
			else
			{
				uStack_20 = (uint32_t) * (short*)(iVar3 + 2);
			}
			if (*(short*)(iVar3 + 4) < 0)
			{
				uStack_1c = -1;
			}
			else
			{
				uStack_1c = (int)*(short*)(iVar3 + 4);
			}
			if (*(short*)(iVar3 + 6) < 0)
			{
				uStack_14 = -1;
			}
			else
			{
				uStack_14 = (int)*(short*)(iVar3 + 6);
			}
			if (-1 < *(short*)(iVar3 + 8))
			{
				iVar5 = (int)*(short*)(iVar3 + 8);
			}
			iVar3 = STATLIST_GetStatValue(pStatList, 0x163, 0);
			iVar2 = iVar2 / 3;
			nValue = 3;
			if (iVar1 < iVar2)
			{
				nValue = 2;
			}
			if (SBORROW4(iVar1, iVar2 * 2) != iVar1 + iVar2 * -2 < 0)
			{
				nValue = nValue + -1;
			}
			STATLIST_SetStatIfListIsValid(pStatList, 0x163, nValue, 0);
			if (iVar3 < nValue)
			{
				sub_6FB4BF60(pUnit, a2);
				if ((uStack_14 != -1) && (2 < nValue))
				{
					sub_6FB5BA70(pUnit, uStack_14, 7, 0, 0, 0, 0, 0);
				}
				if ((iVar5 != -1) && (1 < nValue))
				{
					sub_6FB5BA70(pUnit, iVar5, 7, 0, 0, 0, 0, 0);
				}
				if (((uStack_c != -1) && (uStack_20 != 0xffffffff)) && (uStack_1c != -1))
				{
					sub_6FB5BA70(pUnit, uStack_c, 4, 0, uStack_20, uStack_1c, 0, 0);
					return;
				}
			}
			else if (nValue < iVar3)
			{
				iVar3 = iVar3 - nValue;
				do
				{
					if (uStack_20 != 0xffffffff)
					{
						uVar4 = DATATBLS_Get1OfNFromOverlayTxt(uStack_20);
						iVar2 = 0;
						if (0 < (int)uVar4)
						{
							do
							{
								sub_6FB5BEC0(pUnit, 0, iVar2 + uStack_20);
								iVar2 = iVar2 + 1;
							} while (iVar2 < (int)uVar4);
						}
					}
					if (uStack_1c != -1)
					{
						uVar4 = DATATBLS_Get1OfNFromOverlayTxt(uStack_1c);
						iVar2 = 0;
						if (0 < (int)uVar4)
						{
							do
							{
								sub_6FB5BEC0(pUnit, 0, iVar2 + uStack_1c);
								iVar2 = iVar2 + 1;
							} while (iVar2 < (int)uVar4);
						}
					}
					iVar3 = iVar3 + -1;
				} while (iVar3 != 0);
			}
		}
	}
}

//D2Client.0x6FB4C3D0
void __fastcall sub_6FB4C3D0(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	uint32_t local_8;
	uint32_t local_4;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar3 != 0))
	{
		if (*(short*)(iVar3 + 2) < 0)
		{
			iVar2 = -1;
		}
		else
		{
			iVar2 = (int)*(short*)(iVar3 + 2);
		}
		if (*(short*)(iVar3 + 4) < 0)
		{
			local_8 = -1;
		}
		else
		{
			local_8 = (int)*(short*)(iVar3 + 4);
		}
		if (*(short*)(iVar3 + 6) < 0)
		{
			local_4 = -1;
		}
		else
		{
			local_4 = (int)*(short*)(iVar3 + 6);
		}
		if (iVar2 != -1)
		{
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(iVar2);
			iVar3 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar3 + iVar2);
					iVar3 = iVar3 + 1;
				} while (iVar3 < (int)uVar1);
			}
			iVar2 = iVar2 + 1;
			if (iVar2 != -1)
			{
				uVar1 = DATATBLS_Get1OfNFromOverlayTxt(iVar2);
				iVar3 = 0;
				if (0 < (int)uVar1)
				{
					do
					{
						sub_6FB5BEC0(pUnit, 0, iVar3 + iVar2);
						iVar3 = iVar3 + 1;
					} while (iVar3 < (int)uVar1);
				}
			}
		}
		if (local_8 != -1)
		{
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_8);
			iVar3 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar3 + local_8);
					iVar3 = iVar3 + 1;
				} while (iVar3 < (int)uVar1);
			}
			local_8 = local_8 + 1;
			if (local_8 != -1)
			{
				uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_8);
				iVar3 = 0;
				if (0 < (int)uVar1)
				{
					do
					{
						sub_6FB5BEC0(pUnit, 0, iVar3 + local_8);
						iVar3 = iVar3 + 1;
					} while (iVar3 < (int)uVar1);
				}
			}
		}
		if (local_4 != -1)
		{
			uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_4);
			iVar3 = 0;
			if (0 < (int)uVar1)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar3 + local_4);
					iVar3 = iVar3 + 1;
				} while (iVar3 < (int)uVar1);
			}
			local_4 = local_4 + 1;
			if (local_4 != -1)
			{
				uVar1 = DATATBLS_Get1OfNFromOverlayTxt(local_4);
				iVar3 = 0;
				if (0 < (int)uVar1)
				{
					do
					{
						sub_6FB5BEC0(pUnit, 0, iVar3 + local_4);
						iVar3 = iVar3 + 1;
					} while (iVar3 < (int)uVar1);
				}
			}
		}
	}
}

//D2Client.0x6FB4C560
void __fastcall sub_6FB4C560(D2UnitStrc* pUnit, int a2)
{
	D2StatListStrc* pStatList;
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	int nValue;
	int iStack_18;
	int iStack_14;
	int iStack_10;

	if ((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	        (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar5 != 0)) &&
	    (pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2),
	        pStatList != nullptr))
	{
		iVar1 = STATLIST_GetStatValue(pStatList, 0x84, 0);
		iVar2 = STATLIST_GetStatValue(pStatList, 0x85, 0);
		if (*(short*)(iVar5 + 2) < 0)
		{
			iStack_10 = -1;
		}
		else
		{
			iStack_10 = (int)*(short*)(iVar5 + 2);
		}
		if (*(short*)(iVar5 + 4) < 0)
		{
			iStack_14 = -1;
		}
		else
		{
			iStack_14 = (int)*(short*)(iVar5 + 4);
		}
		if (*(short*)(iVar5 + 6) < 0)
		{
			iVar5 = -1;
		}
		else
		{
			iVar5 = (int)*(short*)(iVar5 + 6);
		}
		iVar3 = STATLIST_GetStatValue(pStatList, 0x163, 0);
		iVar2 = iVar2 / 3;
		nValue = 3;
		iStack_18 = 3;
		if (iVar1 < iVar2)
		{
			iStack_18 = 2;
			nValue = 2;
		}
		if (SBORROW4(iVar1, iVar2 * 2) != iVar1 + iVar2 * -2 < 0)
		{
			nValue = nValue + -1;
			iStack_18 = nValue;
		}
		STATLIST_SetStatIfListIsValid(pStatList, 0x163, nValue, 0);
		if (iVar3 < nValue)
		{
			sub_6FB4C3D0(pUnit, a2);
			if ((iVar5 != -1) && (2 < nValue))
			{
				sub_6FB5BA70(pUnit, iVar5, 3, 0, 0, 0, 0, 0);
				sub_6FB5BA70(pUnit, iVar5 + 1, 3, 0, 0, 0, 0, 0);
			}
			if ((iStack_14 != -1) && (1 < nValue))
			{
				sub_6FB5BA70(pUnit, iStack_14, 3, 0, 0, 0, 0, 0);
				sub_6FB5BA70(pUnit, iStack_14 + 1, 3, 0, 0, 0, 0, 0);
			}
			if ((iStack_10 != -1) && (0 < nValue))
			{
				sub_6FB5BA70(pUnit, iStack_10, 3, 0, 0, 0, 0, 0);
				sub_6FB5BA70(pUnit, iStack_10 + 1, 3, 0, 0, 0, 0, 0);
				return;
			}
		}
		else
		{
			if ((iVar5 != 0) && (nValue < 3))
			{
				if (iVar5 != -1)
				{
					uVar4 = DATATBLS_Get1OfNFromOverlayTxt(iVar5);
					iVar2 = 0;
					nValue = iStack_18;
					if (0 < (int)uVar4)
					{
						do
						{
							sub_6FB5BEC0(pUnit, 0, iVar2 + iVar5);
							iVar2 = iVar2 + 1;
						} while (iVar2 < (int)uVar4);
					}
				}
				iVar5 = iVar5 + 1;
				if (iVar5 != -1)
				{
					uVar4 = DATATBLS_Get1OfNFromOverlayTxt(iVar5);
					iVar2 = 0;
					nValue = iStack_18;
					if (0 < (int)uVar4)
					{
						do
						{
							sub_6FB5BEC0(pUnit, 0, iVar2 + iVar5);
							iVar2 = iVar2 + 1;
						} while (iVar2 < (int)uVar4);
					}
				}
			}
			if ((iStack_14 != 0) && (nValue < 2))
			{
				if (iStack_14 != -1)
				{
					uVar4 = DATATBLS_Get1OfNFromOverlayTxt(iStack_14);
					iVar5 = 0;
					if (0 < (int)uVar4)
					{
						do
						{
							sub_6FB5BEC0(pUnit, 0, iVar5 + iStack_14);
							iVar5 = iVar5 + 1;
						} while (iVar5 < (int)uVar4);
					}
				}
				iStack_14 = iStack_14 + 1;
				if (iStack_14 != -1)
				{
					uVar4 = DATATBLS_Get1OfNFromOverlayTxt(iStack_14);
					iVar5 = 0;
					if (0 < (int)uVar4)
					{
						do
						{
							sub_6FB5BEC0(pUnit, 0, iVar5 + iStack_14);
							iVar5 = iVar5 + 1;
						} while (iVar5 < (int)uVar4);
					}
				}
			}
			if ((iStack_10 != 0) && (iStack_10 < 2))
			{
				if (iStack_10 != -1)
				{
					uVar4 = DATATBLS_Get1OfNFromOverlayTxt(iStack_10);
					iVar5 = 0;
					if (0 < (int)uVar4)
					{
						do
						{
							sub_6FB5BEC0(pUnit, 0, iVar5 + iStack_10);
							iVar5 = iVar5 + 1;
						} while (iVar5 < (int)uVar4);
					}
				}
				iStack_10 = iStack_10 + 1;
				if (iStack_10 != -1)
				{
					uVar4 = DATATBLS_Get1OfNFromOverlayTxt(iStack_10);
					iVar5 = 0;
					if (0 < (int)uVar4)
					{
						do
						{
							sub_6FB5BEC0(pUnit, 0, iVar5 + iStack_10);
							iVar5 = iVar5 + 1;
						} while (iVar5 < (int)uVar4);
					}
				}
			}
		}
	}
}

//D2Client.0x6FB4C860
void __fastcall sub_6FB4C860(D2UnitStrc* pUnit, int a2)
{
	short sVar1;
	D2StatListStrc* pStatList;
	int iVar2;

	pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
	if (pStatList != nullptr)
	{
		iVar2 = STATLIST_GetStatValue(pStatList, 0x15e, 0);
		if ((((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		        (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar2 != 0)) &&
		    (sVar1 = *(short*)(iVar2 + 0x10e), 0 < sVar1))
		{
			sub_6FB55820((int)sVar1, pUnit, 0.0, 0.0, 0);
		}
	}
}

//D2Client.0x6FB4C8D0
void __fastcall sub_6FB4C8D0(D2UnitStrc* pUnit, int a2)
{
	short sVar1;
	D2StatListStrc* pStatList;
	int iVar2;

	pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
	if (pStatList != nullptr)
	{
		iVar2 = STATLIST_GetStatValue(pStatList, 0x15e, 0);
		if ((((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		        (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar2 != 0)) &&
		    (sVar1 = *(short*)(iVar2 + 0x10e), 0 < sVar1))
		{
			iVar2 = sub_6FB4F990((int)pUnit, (int)sVar1);
			if (iVar2 != 0)
			{
				sub_6FB555C0(iVar2, (int)pUnit, 1);
			}
		}
	}
}

//D2Client.0x6FB4C940
void __fastcall sub_6FB4C940(D2UnitStrc* pUnit)
{
	SKILLS_RefreshPassiveSkills(pUnit);
}

//D2Client.0x6FB4C950
void __fastcall sub_6FB4C950(int a1, int a2)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_5c[4];
	int local_4c;
	int local_30;
	uint32_t local_2c;

	if ((((-1 < a2) && (iVar3 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar3 + 0xc4))) && (iVar1 = *(int*)(iVar3 + 0xbc) + a2 * 0x3c, iVar1 != 0)) &&
	    (-1 < *(short*)(iVar1 + 0x38)))
	{
		iVar2 = (int)*(short*)(iVar1 + 0x38);
		if ((((iVar2 < *(int*)(iVar3 + 0xba0)) && (-1 < iVar2)) &&
		        ((iVar2 < *(int*)(iVar3 + 0xba0) &&
		            ((iVar2 = *(int*)(iVar3 + 0xb98) + iVar2 * 0x23c, iVar2 != 0 &&
		                                                                  (-1 < *(short*)(iVar2 + 0xea))))))) &&
		    ((int)*(short*)(iVar2 + 0xea) < *(int*)(iVar3 + 0xb6c)))
		{
			puVar4 = local_5c;
			for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar4 = 0;
				puVar4 = puVar4 + 1;
			}
			local_4c = (int)*(short*)(iVar2 + 0xea);
			local_30 = (int)*(short*)(iVar1 + 0x38);
			local_2c = 1;
			local_5c[1] = a1;
			local_5c[2] = a1;
			sub_6FB3E070(local_5c);
			if (a1 != 0)
			{
				*(uint32_t*)(a1 + 200) = *(uint32_t*)(a1 + 200) | 0x40000;
				*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x20;
			}
		}
	}
}

//D2Client.0x6FB4CA50
void __fastcall sub_6FB4CA50(D2UnitStrc* pUnit)
{
	int iVar1;
	D2SkillStrc* pSkill;
	int iVar2;
	int nY;
	D2ActiveRoomStrc* pDVar3;
	uint32_t uVar4;
	uint32_t uStack_c;
	D2ActiveRoomStrc** ppDStack_8;
	D2UnitStrc* local_4;

	if (pUnit == nullptr)
	{
		return;
	}
	if (pUnit->dwUnitType != 1)
	{
		return;
	}
	local_4 = pUnit;
	pSkill = UNITS_GetUsedSkill(pUnit);
	if (pSkill == nullptr)
	{
		return;
	}
	iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
	if (iVar2 != 0xa7)
	{
		return;
	}
	iVar2 = SKILLS_GetParam2(pSkill);
	nY = SKILLS_GetParam3(pSkill);
	if ((iVar2 == 0) && (nY == 0))
	{
		return;
	}
	SKILLS_SetParam2(pSkill, 0);
	SKILLS_SetParam3(pSkill, 0);
	pDVar3 = UNITS_GetRoom(pUnit);
	if (pDVar3 == nullptr)
	{
		return;
	}
	iVar1 = (pDVar3->tCoords).nSubtileX;
	if ((((iVar2 < iVar1) || ((pDVar3->tCoords).nSubtileWidth + iVar1 <= iVar2)) ||
	        (iVar1 = (pDVar3->tCoords).nSubtileY, nY < iVar1)) ||
	    ((pDVar3->tCoords).nSubtileHeight + iVar1 <= nY))
	{
		ppDStack_8 = nullptr;
		uStack_c = 0;
		DUNGEON_GetAdjacentRoomsListFromRoom(pDVar3, &ppDStack_8, (int*)&uStack_c);
		uVar4 = 0;
		if (uStack_c == 0)
		{
			return;
		}
		while (((pDVar3 = ppDStack_8[uVar4], pDVar3 == nullptr ||
		                                         (iVar1 = (pDVar3->tCoords).nSubtileX, iVar2 < iVar1)) ||
		        (((pDVar3->tCoords).nSubtileWidth + iVar1 <= iVar2 ||
		            ((iVar1 = (pDVar3->tCoords).nSubtileY, nY < iVar1 ||
		                                                       ((pDVar3->tCoords).nSubtileHeight + iVar1 <= nY)))))))
		{
			uVar4 = uVar4 + 1;
			if (uStack_c <= uVar4)
			{
				return;
			}
		}
		pDVar3 = ppDStack_8[uVar4];
		pUnit = local_4;
	}
	if (pDVar3 == nullptr)
	{
		return;
	}
	pDVar3 = UNITS_GetRoom(pUnit);
	if (pDVar3 != nullptr)
	{
		iVar1 = (pDVar3->tCoords).nSubtileX;
		if ((((iVar1 <= iVar2) && (iVar2 < (pDVar3->tCoords).nSubtileWidth + iVar1)) &&
		        (iVar1 = (pDVar3->tCoords).nSubtileY, iVar1 <= nY)) &&
		    (nY < (pDVar3->tCoords).nSubtileHeight + iVar1))
			goto LAB_6fb4cbe7;
		ppDStack_8 = nullptr;
		uStack_c = 0;
		DUNGEON_GetAdjacentRoomsListFromRoom(pDVar3, &ppDStack_8, (int*)&uStack_c);
		uVar4 = 0;
		if (uStack_c != 0)
		{
			do
			{
				pDVar3 = ppDStack_8[uVar4];
				if (((pDVar3 != nullptr) &&
				        (iVar1 = (pDVar3->tCoords).nSubtileX, iVar1 <= iVar2)) &&
				    ((iVar2 < (pDVar3->tCoords).nSubtileWidth + iVar1 &&
				        ((iVar1 = (pDVar3->tCoords).nSubtileY, iVar1 <= nY &&
				                                                   (nY < (pDVar3->tCoords).nSubtileHeight + iVar1))))))
				{
					pDVar3 = ppDStack_8[uVar4];
					goto LAB_6fb4cbe7;
				}
				uVar4 = uVar4 + 1;
			} while (uVar4 < uStack_c);
		}
	}
	pDVar3 = nullptr;
LAB_6fb4cbe7:
	COLLISION_ResetMaskWithPattern(pDVar3, iVar2, nY, 1, 0x100);
}

//D2Client.0x6FB4CC10
void __fastcall sub_6FB4CC10(int a1)
{
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 200) = *(uint32_t*)(a1 + 200) | 0x40000;
	}
}

//D2Client.0x6FB4CC20
void __fastcall sub_6FB4CC20(int a1)
{
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 200) = *(uint32_t*)(a1 + 200) | 0x40000;
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x20;
	}
}

//D2Client.0x6FB4CC50
void __fastcall sub_6FB4CC50(int a1)
{
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 200) = *(uint32_t*)(a1 + 200) & 0xfffbffff;
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) & 0xffffffdf;
	}
}

//D2Client.0x6FB4CC80
void __fastcall sub_6FB4CC80(int a1)
{
	sub_6FB5FB10(a1);
	sub_6FB600F0(a1, 1);
}

//D2Client.0x6FB4CCA0
void __fastcall sub_6FB4CCA0(int a1)
{
	sub_6FB600F0(a1, 0);
	sub_6FB5FC80(a1, 0, 0, 0);
}

//D2Client.0x6FB4CCD0
void __fastcall sub_6FB4CCD0(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_1c;
	int32_t DStack_18;

	puVar3 = &local_1c;
	for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		local_1c = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_1c = 0;
	}
	else
	{
		local_1c = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
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
	sub_6FB4EE00(0x19, pUnit, &local_1c, 0);
	D2COMMON_10160_PathUpdateDirection(pUnit->pDynamicPath, 0);
}

//D2Client.0x6FB4CD70
void __fastcall sub_6FB4CD70(D2UnitStrc* pUnit)
{
	sub_6FB4F410(pUnit, (int*)0x1);
	if (pUnit != nullptr)
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x80000000;
	}
	D2Common_10214(pUnit);
}

//D2Client.0x6FB4CDA0
void __fastcall sub_6FB4CDA0(D2UnitStrc* pUnit, int a2)
{
	D2StatListStrc* pStatList;
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iStack_c;

	if ((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	        (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar4 != 0)) &&
	    (pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2),
	        pStatList != nullptr))
	{
		iStack_c = STATLIST_GetStatValue(pStatList, 0xa9, 0);
		iVar1 = STATLIST_GetStatValue(pStatList, 0x15e, 0);
		iVar2 = STATLIST_GetStatValue(pStatList, 0x15f, 0);
		if (((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		    ((iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar1 * 0x23c, iVar6 != 0 &&
		                                                                                       (iVar1 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar6 + 0x13c), iVar1, iVar2),
		                                                                                           0 < iVar1))))
		{
			iVar6 = (int)*(short*)(iVar4 + 2);
			iVar2 = (*(short*)(iVar4 + 4) - iVar6) + 1;
			if (iVar2 <= iVar1)
			{
				iVar1 = iVar2;
			}
			if (iVar2 <= iStack_c)
			{
				iStack_c = iVar2;
			}
			if ((-1 < iVar6) && (iVar6 <= *(short*)(iVar4 + 4)))
			{
				iVar5 = 0;
				if (0 < iVar2)
				{
					do
					{
						if (iVar5 == ((iStack_c + -1) * iVar2) / iVar1)
						{
							iVar3 = sub_6FB57CD0((int)pUnit, iVar6);
							if (iVar3 == 0)
							{
								sub_6FB5BA70(pUnit, iVar6, 3, 0, 0, 0, 0, 0);
							}
						}
						else
						{
							sub_6FB5BEC0(pUnit, 0, iVar6);
						}
						iVar5 = iVar5 + 1;
						iVar6 = iVar6 + 1;
					} while (iVar5 < iVar2);
				}
			}
			iVar2 = (int)*(short*)(iVar4 + 6);
			if ((-1 < iVar2) && (iVar2 <= *(short*)(iVar4 + 8)))
			{
				iVar6 = 0;
				iVar4 = (*(short*)(iVar4 + 8) - iVar2) + 1;
				if (0 < iVar4)
				{
					do
					{
						if (iVar6 == ((iStack_c + -1) * iVar4) / iVar1)
						{
							iVar5 = sub_6FB57CD0((int)pUnit, iVar2);
							if (iVar5 == 0)
							{
								sub_6FB5BA70(pUnit, iVar2, 3, 0, 0, 0, 0, 0);
							}
						}
						else
						{
							sub_6FB5BEC0(pUnit, 0, iVar2);
						}
						iVar6 = iVar6 + 1;
						iVar2 = iVar2 + 1;
					} while (iVar6 < iVar4);
				}
			}
		}
	}
}

//D2Client.0x6FB4CF50
void __fastcall sub_6FB4CF50(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	short sVar2;
	int iVar3;

	if (((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar1 != 0))
	{
		iVar3 = (int)*(short*)(iVar1 + 2);
		sVar2 = *(short*)(iVar1 + 4);
		if (-1 < iVar3)
		{
			for (; iVar3 <= sVar2; iVar3 = iVar3 + 1)
			{
				sub_6FB5BEC0(pUnit, 0, iVar3);
			}
		}
		iVar3 = (int)*(short*)(iVar1 + 6);
		sVar2 = *(short*)(iVar1 + 8);
		if (-1 < iVar3)
		{
			for (; iVar3 <= sVar2; iVar3 = iVar3 + 1)
			{
				sub_6FB5BEC0(pUnit, 0, iVar3);
			}
		}
	}
}

//D2Client.0x6FB4CFC0
void __fastcall sub_6FB4CFC0(uint32_t a1, int a2)
{
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c[4];
	int local_4c;
	int local_30;
	uint32_t local_2c;

	if ((((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xc4))) && (iVar1 = *(int*)(iVar2 + 0xbc) + a2 * 0x3c, iVar1 != 0)) &&
	    ((-1 < *(short*)(iVar1 + 0x3a) && ((int)*(short*)(iVar1 + 0x3a) < *(int*)(iVar2 + 0xb6c)))))
	{
		puVar3 = local_5c;
		for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		local_4c = (int)*(short*)(iVar1 + 0x3a);
		if (*(short*)(iVar1 + 0x38) < 0)
		{
			local_30 = 0;
		}
		else
		{
			local_30 = (int)*(short*)(iVar1 + 0x38);
		}
		local_2c = 1;
		local_5c[1] = a1;
		local_5c[2] = a1;
		sub_6FB3E070(local_5c);
	}
}

//D2Client.0x6FB4D060
void __fastcall sub_6FB4D060(D2UnitStrc* pUnit, int a2)
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

	sub_6FB42A70(pUnit, 5, 0);
	if ((((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xc4))) && (iVar1 = *(int*)(iVar2 + 0xbc) + a2 * 0x3c, iVar1 != 0)) &&
	    ((-1 < *(short*)(iVar1 + 0x3a) && ((int)*(short*)(iVar1 + 0x3a) < *(int*)(iVar2 + 0xb6c)))))
	{
		puVar3 = &local_5c;
		for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		local_4c = (int)*(short*)(iVar1 + 0x3a);
		if (*(short*)(iVar1 + 0x38) < 0)
		{
			local_30 = 0;
		}
		else
		{
			local_30 = (int)*(short*)(iVar1 + 0x38);
		}
		local_2c = 1;
		local_58 = pUnit;
		local_54 = pUnit;
		sub_6FB3E070(&local_5c);
	}
}

//D2Client.0x6FB4D110
void __cdecl sub_6FB4D110()
{
	sub_6FAA9AB0(0);
}

//D2Client.0x6FB4D120
void __fastcall sub_6FB4D120(D2UnitStrc* pUnit, uint32_t a2)
{
	uint64_t DVar1;
	uint64_t uVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	uint32_t nOverlayId;
	uint32_t uVar7;
	int local_8;

	if ((((-1 < (int)a2) && ((int)a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	        (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar6 != 0)) &&
	    (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(iVar6 + 0x14)) == 0))
	{
		if (*(short*)(iVar6 + 10) < 0)
		{
			local_8 = -1;
		}
		else
		{
			local_8 = (int)*(short*)(iVar6 + 10);
		}
		if (*(short*)(iVar6 + 2) < 0)
		{
			nOverlayId = 0xffffffff;
		}
		else
		{
			nOverlayId = (uint32_t) * (short*)(iVar6 + 2);
		}
		if (*(short*)(iVar6 + 4) < 0)
		{
			iVar6 = -1;
		}
		else
		{
			iVar6 = (int)*(short*)(iVar6 + 4);
		}
		iVar3 = STATES_CheckStateMaskAuraByStateId(a2);
		if (local_8 != -1)
		{
			uVar4 = DATATBLS_Get1OfNFromOverlayTxt(local_8);
			if ((int)uVar4 < 1)
			{
				uVar4 = 0;
			}
			else
			{
				uVar7 = (pUnit->pSeed).nLowSeed;
				uVar2 = (uint64_t)(pUnit->pSeed).nHighSeed;
				if ((uVar4 & uVar4 - 1) == 0)
				{
					DVar1 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					uVar4 = uVar4 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
				}
				else
				{
					DVar1 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					uVar4 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar4);
				}
			}
			local_8 = local_8 + uVar4;
		}
		if (nOverlayId != 0xffffffff)
		{
			uVar4 = DATATBLS_Get1OfNFromOverlayTxt(nOverlayId);
			if ((int)uVar4 < 1)
			{
				uVar4 = 0;
			}
			else
			{
				uVar2 = (uint64_t)(pUnit->pSeed).nHighSeed;
				uVar7 = (pUnit->pSeed).nLowSeed;
				if ((uVar4 & uVar4 - 1) == 0)
				{
					DVar1 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					uVar4 = uVar4 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
				}
				else
				{
					DVar1 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					uVar4 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar4);
				}
			}
			nOverlayId = nOverlayId + uVar4;
		}
		if (iVar6 != -1)
		{
			uVar4 = DATATBLS_Get1OfNFromOverlayTxt(iVar6);
			if ((int)uVar4 < 1)
			{
				uVar4 = 0;
			}
			else
			{
				uVar2 = (uint64_t)(pUnit->pSeed).nHighSeed;
				uVar7 = (pUnit->pSeed).nLowSeed;
				if ((uVar4 & uVar4 - 1) == 0)
				{
					DVar1 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					uVar4 = uVar4 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
				}
				else
				{
					DVar1 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					uVar4 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar4);
				}
			}
			iVar6 = iVar6 + uVar4;
		}
		if (iVar3 != 0)
		{
			STATES_ToggleState(pUnit, a2, 0);
			iVar5 = STATES_CheckStateMaskAuraOnUnit(pUnit);
			if (iVar5 != 0)
			{
				local_8 = -1;
			}
			STATES_ToggleState(pUnit, a2, 1);
		}
		if (local_8 != -1)
		{
			if (iVar3 == 0)
			{
				sub_6FB5BA70(pUnit, local_8, 4, 0, nOverlayId, iVar6, 0, 0);
				return;
			}
			sub_6FB5BA70(pUnit, local_8, 9, 0, nOverlayId, iVar6, a2, 0);
			return;
		}
		if (nOverlayId != 0xffffffff)
		{
			if (iVar3 == 0)
			{
				uVar4 = 0;
				uVar7 = 3;
			}
			else
			{
				uVar7 = 8;
				uVar4 = a2;
			}
			sub_6FB5BA70(pUnit, nOverlayId, uVar7, 0, uVar4, 0, 0, 0);
		}
		if (iVar6 != -1)
		{
			if (iVar3 != 0)
			{
				sub_6FB5BA70(pUnit, iVar6, 8, 0, a2, 0, 0, 0);
				return;
			}
			sub_6FB5BA70(pUnit, iVar6, 3, 0, 0, 0, 0, 0);
		}
	}
}

//D2Client.0x6FB4D3A0
void __fastcall sub_6FB4D3A0(D2UnitStrc* pUnit, uint32_t a2)
{
	int iVar1;
	int iVar2;
	D2StatListStrc* pStatList;

	if ((((pUnit != nullptr) && (-1 < (int)a2)) &&
	        ((int)a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar1 != 0))
	{
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x1c] & *(uint8_t*)(iVar1 + 0x14)) != 0)
		{
			if ((pUnit->dwUnitType == 1) && (pUnit->dwAnimMode == 0xc))
			{
				STATES_ToggleState(pUnit, a2, 1);
				return;
			}
			if ((pUnit->dwUnitType == 0) && (pUnit->dwAnimMode == 0x11))
			{
				STATES_ToggleState(pUnit, a2, 1);
				return;
			}
		}
		iVar2 = STATES_CheckState(pUnit, a2);
		if (iVar2 == 0)
		{
			if (-1 < *(short*)(iVar1 + 0x26))
			{
				sub_6FB55820((int)*(short*)(iVar1 + 0x26), pUnit, 0.0, 0.0, 0);
			}
		}
		else
		{
			pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
			if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar1 + 0x14)) == 0)
			{
				STATLIST_RemoveAllStats(pStatList);
			}
		}
		STATES_ToggleState(pUnit, a2, 1);
		if (*(char*)(iVar1 + 0x21) != '\0')
		{
			sub_6FB4D510(pUnit);
		}
		sub_6FB4D120(pUnit, a2);
		iVar2 = sub_6FB29550((int*)pUnit);
		if (iVar2 != 0)
		{
			iVar2 = STATES_CheckStateMaskHideOnUnit(pUnit);
			if (iVar2 != 0)
			{
				pUnit->dwFlagEx = pUnit->dwFlagEx | 0x40000;
				pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd | 0x20;
			}
		}
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(iVar1 + 0x10)) != 0)
		{
			sub_6FB5B120((int)pUnit);
			if ((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1))
			{
				sub_6FB4F410(pUnit, (int*)0x1);
			}
			sub_6FB5C080(pUnit);
			UNITS_SetAnimStartFrame(pUnit);
			pUnit->nSeqCurrentFramePrecise = 0;
			UNITS_SetUsedSkill(pUnit, nullptr);
		}
	}
}

//D2Client.0x6FB4D510
void __fastcall sub_6FB4D510(D2UnitStrc* pUnit)
{
	uint8_t bVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	int nState;
	int iVar6;
	uint8_t local_5;

	iVar6 = *(int*)((uint8_t*)&sgptDataTables);
	iVar4 = -1;
	nState = 0;
	iVar2 = *(int*)(iVar6 + 0xc4);
	local_5 = 0;
	if (0 < iVar2)
	{
		iVar5 = 0;
		do
		{
			if ((((-1 < iVar5) && (nState < iVar2)) &&
			        (iVar6 = *(int*)(iVar6 + 0xbc) + iVar5, iVar6 != 0)) &&
			    ((iVar2 = STATES_CheckState(pUnit, nState), iVar2 != 0 &&
			                                                    (bVar1 = *(uint8_t*)(iVar6 + 0x20), local_5 < bVar1))))
			{
				iVar4 = nState;
				local_5 = bVar1;
			}
			nState = nState + 1;
			iVar5 = iVar5 + 0x3c;
			iVar6 = *(int*)((uint8_t*)&sgptDataTables);
			iVar2 = *(int*)(iVar6 + 0xc4);
		} while (nState < iVar2);
		if (0 < iVar4)
		{
			if (*(int*)(iVar6 + 0xc4) <= iVar4)
			{
				return;
			}
			iVar6 = *(int*)(iVar6 + 0xbc) + iVar4 * 0x3c;
			if (iVar6 == 0)
			{
				return;
			}
			if (((*(char*)(iVar6 + 0x21) == 'h') && (pDVar3 = CUNIT_GetPlayer(), pUnit == pDVar3)) &&
			    (iVar2 = D2GFX_HardwareAcceleratedRenderMode(), iVar2 != 0))
			{
				pUnit->nInteract = 0;
				pUnit->nUpdateType = 0;
			}
			else
			{
				bVar1 = *(uint8_t*)(iVar6 + 0x21);
				pUnit->nInteract = (short)(uint32_t)bVar1;
				pUnit->nUpdateType = (short)((uint32_t)bVar1 >> 0x10);
			}
			pDVar3 = CUNIT_GetPlayer();
			if (pUnit != pDVar3)
			{
				return;
			}
			if (pUnit->dwInteractGUID == 0)
			{
				return;
			}
			sub_6FAA4490(pUnit->dwInteractGUID, *(uint8_t*)(iVar6 + 0x22),
			    *(uint8_t*)(iVar6 + 0x23), *(uint8_t*)(iVar6 + 0x24));
			return;
		}
	}
	pUnit->nInteract = 0;
	pUnit->nUpdateType = 0;
	pDVar3 = CUNIT_GetPlayer();
	if ((pUnit == pDVar3) && (pUnit->dwInteractGUID != 0))
	{
		sub_6FAA4490(pUnit->dwInteractGUID, 0xff, 0xff, 0xff);
	}
}

//D2Client.0x6FB4D640
void __fastcall sub_6FB4D640(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	uint64_t uVar4;
	int iVar5;
	D2StatListStrc* pStatList;
	uint32_t uVar6;
	int iVar7;

	if ((((pUnit != nullptr) && (-1 < a2)) &&
	        (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar1 != 0))
	{
		iVar5 = STATES_CheckState(pUnit, a2);
		if (iVar5 != 0)
		{
			pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
			if ((pStatList != nullptr) &&
			    (iVar5 = STATLIST_GetState(pStatList), a2 == iVar5))
			{
				D2Common_10474(pUnit, pStatList);
				STATLIST_FreeStatList(pStatList);
			}
			if (-1 < *(short*)(iVar1 + 0x28))
			{
				sub_6FB55820((int)*(short*)(iVar1 + 0x28), pUnit, 0.0, 0.0, 0);
			}
		}
		STATES_ToggleState(pUnit, a2, 0);
		if (*(char*)(iVar1 + 0x21) != '\0')
		{
			sub_6FB4D510(pUnit);
		}
		if (-1 < *(short*)(iVar1 + 0xc))
		{
			iVar5 = (int)*(short*)(iVar1 + 0xc);
			if (iVar5 != -1)
			{
				uVar6 = DATATBLS_Get1OfNFromOverlayTxt(iVar5);
				if ((int)uVar6 < 1)
				{
					uVar6 = 0;
				}
				else
				{
					uVar2 = (pUnit->pSeed).nLowSeed;
					uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
					if ((uVar6 & uVar6 - 1) == 0)
					{
						DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
						(*(uint64_t*)&pUnit->pSeed) = DVar3;
						uVar6 = uVar6 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
					}
					else
					{
						DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
						(*(uint64_t*)&pUnit->pSeed) = DVar3;
						uVar6 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar6);
					}
				}
				iVar5 = iVar5 + uVar6;
			}
			sub_6FB5BA70(pUnit, iVar5, 4, 0, 0xffffffff, 0xffffffff, 0, 0);
		}
		if ((-1 < *(short*)(iVar1 + 2)) && (iVar5 = (int)*(short*)(iVar1 + 2), iVar5 != -1))
		{
			uVar6 = DATATBLS_Get1OfNFromOverlayTxt(iVar5);
			iVar7 = 0;
			if (0 < (int)uVar6)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar7 + iVar5);
					iVar7 = iVar7 + 1;
				} while (iVar7 < (int)uVar6);
			}
		}
		if ((-1 < *(short*)(iVar1 + 4)) && (iVar5 = (int)*(short*)(iVar1 + 4), iVar5 != -1))
		{
			uVar6 = DATATBLS_Get1OfNFromOverlayTxt(iVar5);
			iVar7 = 0;
			if (0 < (int)uVar6)
			{
				do
				{
					sub_6FB5BEC0(pUnit, 0, iVar7 + iVar5);
					iVar7 = iVar7 + 1;
				} while (iVar7 < (int)uVar6);
			}
		}
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(iVar1 + 0x10)) != 0)
		{
			sub_6FB5B120((int)pUnit);
			if ((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1))
			{
				sub_6FB4F410(pUnit, (int*)0x1);
			}
			sub_6FB5C080(pUnit);
			UNITS_SetAnimStartFrame(pUnit);
			pUnit->nSeqCurrentFramePrecise = 0;
			UNITS_SetUsedSkill(pUnit, nullptr);
		}
		UNITS_UpdateAnimRateAndVelocity(pUnit, __FILE__, __LINE__);
	}
}

//D2Client.0x6FB4D830
D2StatListStrc* __fastcall sub_6FB4D830(D2UnitStrc* pUnit, D2StatListStrc* pStatList, int a3, int a4, int a5, uint32_t a6)
{
	int iVar1;
	char local_4;

	if (pUnit == nullptr)
	{
		return nullptr;
	}
	local_4 = '\0';
	if (a4 == 0xac)
	{
		local_4 = '\x04';
	}
	if (pStatList == nullptr)
	{
		pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a3);
		if (pStatList == nullptr)
		{
			pStatList = STATLIST_AllocStatList(nullptr, 0, 0, pUnit->dwUnitType, pUnit->dwUnitId);
			STATLIST_SetState(pStatList, a3);
			D2COMMON_10475_PostStatToStatList(pUnit, pStatList, 1);
		}
		else
		{
			iVar1 = STATLIST_GetStatValue(pStatList, a4, (uint16_t)a6);
			local_4 = (char)iVar1;
		}
	}
	STATLIST_SetStatIfListIsValid(pStatList, a4, a5, (uint16_t)a6);
	if (a4 == 0xac)
	{
		sub_6FB27E10(pUnit, local_4, (char)a5);
	}
	else if (a4 < 0)
	{
		return pStatList;
	}
	if (((a4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4)) &&
	        (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) + a4 * 0x144, iVar1 != 0)) &&
	    (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar1 + 5)) != 0))
	{
		UNITS_UpdateAnimRateAndVelocity(pUnit, __FILE__, __LINE__);
	}
	return pStatList;
}

//D2Client.0x6FB4D920
void __fastcall sub_6FB4D920(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	short sVar2;
	D2StatListStrc* pStatList;
	int iVar3;
	int iVar4;

	if (((((pUnit != nullptr) && (-1 < a2)) &&
	         (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	        (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar1 != 0)) &&
	    ((((uint8_t)((uint8_t*)&gdwBitMasks)[0x1c] & *(uint8_t*)(iVar1 + 0x14)) == 0 ||
	        (((pUnit->dwUnitType != 1 || (pUnit->dwAnimMode != 0xc)) &&
	            ((pUnit->dwUnitType != 0 || (pUnit->dwAnimMode != 0x11))))))))
	{
		sVar2 = *(short*)(iVar1 + 0x1a);
		if (((-1 < sVar2) && (sVar2 < 0x1f)) && (*(code**)(byte_6FB93EE0 + sVar2 * 4) != nullptr))
		{
			(**(code**)(byte_6FB93EE0 + sVar2 * 4))();
		}
		if (-1 < *(short*)(iVar1 + 0x30))
		{
			pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
			if (pStatList != nullptr)
			{
				iVar3 = STATLIST_GetStatValue(pStatList, 0x15e, 0);
				iVar4 = STATLIST_GetStatValue(pStatList, 0x15f, 0);
				sub_6FABE260((int)pUnit, (int)*(short*)(iVar1 + 0x30), iVar3, iVar4,
				    (int)*(short*)(iVar1 + 0x32), 1, a2);
			}
		}
	}
}

//D2Client.0x6FB4DA00
void __fastcall sub_6FB4DA00(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	short sVar2;
	D2StatListStrc* pDVar3;

	if ((((pUnit != nullptr) && (-1 < a2)) &&
	        (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc4))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc) + a2 * 0x3c, iVar1 != 0))
	{
		sVar2 = *(short*)(iVar1 + 0x1c);
		if (((-1 < sVar2) && (sVar2 < 0x1e)) && (*(code**)(byte_6FB93F60 + sVar2 * 4) != nullptr))
		{
			(**(code**)(byte_6FB93F60 + sVar2 * 4))();
		}
		if (-1 < *(short*)(iVar1 + 0x30))
		{
			pDVar3 = STATLIST_GetStatListFromUnitAndState(pUnit, a2);
			if (pDVar3 != nullptr)
			{
				sub_6FB2A7C0((int)pUnit, 1, a2);
			}
		}
	}
}

//D2Client.0x6FB4DA80
int __fastcall sub_6FB4DA80(D2UnitStrc* pUnit, D2SkillStrc* pSkill)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	uint32_t uVar4;

	iVar1 = SKILLS_GetUseState(pUnit, pSkill);
	if (iVar1 == 0)
	{
		pDVar2 = CUNIT_GetPlayer();
		if (pUnit == pDVar2)
		{
			uVar3 = sub_6FAA9AC0();
			uVar4 = sub_6FAABF80();
			if (uVar4 < uVar3)
			{
				return 8;
			}
		}
		iVar1 = 0;
	}
	return iVar1;
}
