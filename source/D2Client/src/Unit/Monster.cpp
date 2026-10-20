#include "Unit/Monster.h"

#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Engine/Gfx.h"
#include "Engine/Particle.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Sound/SoundInst.h"
#include "UI/Chat.h"
#include "UI/Hireables.h"
#include "UI/SkillDesc.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"
#include "Unit/Missile.h"
#include "Unit/MonUnique.h"
#include "Unit/UnitGfx.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB70BA8
uint8_t byte_6FB70BA8[24] = {0x96, 1, 0, 0, 0x9A, 1, 0, 0, 0x9F, 1, 0, 0, 0xA2, 1, 0, 0, 0xA5, 1, 0, 0, 5};
//D2Client.0x6FB70BC0
uint8_t byte_6FB70BC0[32] = {0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1};
//D2Client.0x6FB70BE0
uint8_t byte_6FB70BE0[32] = {2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 1};
//D2Client.0x6FB70C00
uint8_t byte_6FB70C00[4] = {2};
//D2Client.0x6FB70C04
uint8_t byte_6FB70C04[236] = {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0x10, 0, 0, 0, 0, 0, 0, 0, 0x10, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1, 0, 0, 0, 7, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 8, 0, 0, 0, 1, 0, 0, 0, 8, 0, 0, 0, 1, 0, 0, 0, 9, 0, 0, 0, 1, 0, 0, 0, 9, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0x10, 0, 0, 0, 0, 0, 0, 0, 0xD, 0, 0, 0, 0, 0, 0, 0, 0xE, 0, 0, 0, 0, 0, 0, 0, 0xE, 0, 0, 0, 0, 0, 0, 0, 0xF, 0, 0, 0, 0, 0, 0, 0, 0xF, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0xA, 0, 0, 0, 1, 0, 0, 0, 0xA, 0, 0, 0, 1, 0, 0, 0, 0xB, 0, 0, 0, 1, 0, 0, 0, 0xB, 0, 0, 0, 1};
//D2Client.0x6FB70CF0
uint32_t dword_6FB70CF0 = 0x10;
//D2Client.0x6FB70CF4
uint32_t dword_6FB70CF4 = 0xC94;
//D2Client.0x6FB91590
uint8_t byte_6FB91590[192] = {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1};
//D2Client.0x6FB91650
uint8_t byte_6FB91650[72] = {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 4};
//D2Client.0x6FB91698
uint32_t dword_6FB91698 = 2;
//D2Client.0x6FB916A4
uint8_t byte_6FB916A4 = 1;
//D2Client.0x6FBBC22C
uint8_t byte_6FBBC22C;
//D2Client.0x6FBBC230
uint8_t byte_6FBBC230;

//D2Client.0x6FB40D60
// TODO: decompilation needs review (unaff_)
void __fastcall sub_6FB40D60(D2UnitStrc* pUnit2, D2ActiveRoomStrc* pActiveRoom, int a3, int a4, int a5, uint32_t a6)
{
	D2SeedStrc* pDVar1;
	char cVar2;
	D2DynamicPathStrc* pDynamicPath;
	D2PlayerDataStrc* pDVar3;
	uint64_t DVar4;
	uint8_t bVar5;
	int iVar6;
	int iVar8;
	D2InventoryStrc* pDVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	D2SkillListStrc* pDVar12;
	D2DifficultyLevelsTxt* pDVar13;
	D2SkillStrc* pSkill;
	D2UnitStrc* pUnit;
	char nFlags;
	D2ActiveRoomStrc* unaff_EBX;
	short* psVar14;
	int iVar15;
	int unaff_EBP;
	int unaff_retaddr;
	int iStack_4;
	uint32_t uVar7;

	if (a5 < 0)
	{
		return;
	}
	iVar8 = *(int*)((uint8_t*)&sgptDataTables);
	if (*(int*)(iVar8 + 0xa80) <= a5)
	{
		return;
	}
	iVar15 = *(int*)(iVar8 + 0xa78) + a5 * 0x1a8;
	if (iVar15 == 0)
	{
		return;
	}
	iVar6 = (int)*(short*)(iVar15 + 0x18);
	if (iVar6 < 0)
	{
		return;
	}
	if (*(int*)(iVar8 + 0xa98) <= iVar6)
	{
		return;
	}
	if (*(int*)(iVar8 + 0xa90) + iVar6 * 0x134 == 0)
	{
		return;
	}
	bVar5 = sub_6FAAC090();
	uVar7 = (uint32_t)bVar5;
	D2_ASSERT(2 >= uVar7);
	STATLIST_AllocStatListEx(pUnit, nFlags, (StatListValueChangeFunc)(pUnit2), nullptr);
	STATLIST_SetUnitStat(pUnit2, 0xc, (int)*(short*)(iVar15 + 0xaa + uVar7 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x44, 100, 0);
	STATLIST_SetUnitStat(pUnit2, 0x43, 0x4b, 0);
	STATLIST_SetUnitStat(pUnit2, 0x45, 100, 0);
	STATLIST_SetUnitStat(pUnit2, 0x24, (int)*(short*)(iVar15 + 0x144 + uVar7 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x25, (int)*(short*)(iVar15 + 0x14a + uVar7 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x27, (int)*(short*)(iVar15 + 0x150 + uVar7 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x29, (int)*(short*)(iVar15 + 0x156 + uVar7 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x2b, (int)*(short*)(iVar15 + 0x15c + uVar7 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x2d, (int)*(short*)(iVar15 + 0x162 + uVar7 * 2), 0);
	bVar5 = sub_6FAAC090();
	iVar8 = sub_6FAAC080();
	MONSTERS_ApplyClassicScaling(pUnit2, iVar8, bVar5);
	STATLIST_SetUnitStat(pUnit2, 7, 0x6400, 0);
	STATLIST_SetUnitStat(pUnit2, 6, 0x6400, 0);
	PATH_AllocDynamicPath(nullptr, unaff_EBX, iStack_4, unaff_retaddr, pUnit2, 1);
	pDynamicPath = pUnit2->pDynamicPath;
	PATH_SetVelocity(pDynamicPath, (int)*(short*)(iVar15 + 0x32) << 8,
	    __FILE__, __LINE__);
	if ((pUnit2->pInventory == nullptr) &&
	    ((((((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar15 + 0xd)) != 0 || (a3 == 0x123)) ||
	          (a3 == 0x165)) ||
	        ((a3 == 0x1a1 || (a3 == 0x1a2))))))
	{
		pDVar9 = INVENTORY_AllocInventory(nullptr, pUnit2);
		pUnit2->pInventory = pDVar9;
	}
	UNITS_ChangeAnimMode(pUnit2, a4);
	iVar8 = MONSTERS_IsDead(pUnit2);
	if ((iVar8 != 0) && (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(unaff_EBP + 6)) == 0))
	{
		PATH_RemoveCollisionFootprintForUnit(pUnit2, 1);
		PATH_SetUnitCollisionPattern(pUnit2, 5);
		PATH_SetFootprintCollisionMask(pUnit2->pDynamicPath, 0x8000);
	}
	uVar10 = pUnit2->dwFrameCountPrecise;
	pDVar1 = &pUnit2->pSeed;
	if ((int)uVar10 < 1)
	{
		uVar10 = 0;
	}
	else if ((uVar10 & uVar10 - 1) == 0)
	{
		uVar11 = sub_6FAA88D0(&pDVar1->nLowSeed);
		uVar10 = uVar11 & uVar10 - 1;
	}
	else
	{
		DVar4 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
		*(uint64_t*)pDVar1 = DVar4;
		uVar10 = (*(uint32_t*)((uint8_t*)&DVar4 + 0)) % uVar10;
	}
	pUnit2->nSeqCurrentFramePrecise = uVar10;
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(unaff_EBP + 4)) == 0)
	{
		uVar10 = pUnit2->dwFlags & 0xfffffffd;
	}
	else
	{
		uVar10 = pUnit2->dwFlags | 2;
	}
	pUnit2->dwFlags = uVar10;
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x18] & *(uint8_t*)(unaff_EBP + 5)) == 0)
	{
		uVar10 = pUnit2->dwFlags | 0x20;
	}
	else
	{
		uVar10 = pUnit2->dwFlags & 0xffffffdf;
	}
	pUnit2->dwFlags = uVar10;
	pUnit2->dwFlags = uVar10 | 8;
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(unaff_EBP + 5)) == 0)
	{
		uVar10 = uVar10 & 0xfffffffb | 8;
	}
	else
	{
		uVar10 = uVar10 | 0xc;
	}
	pUnit2->dwFlags = uVar10;
	if ((pUnit2->dwUnitType == 1) &&
	    (pDVar3 = pUnit2->pPlayerData, pDVar3 != nullptr))
	{
		*(uint16_t*)&pDVar3->unk0x28 = 0;
		iVar8 = pUnit2->dwClassId;
		if ((iVar8 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar8))
		{
			iVar8 = 0;
		}
		else
		{
			iVar8 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar8 * 0x1a8;
		}
		*(int*)pDVar3->szName = iVar8;
	}
	sub_6FB412D0(pUnit2, a3);
	sub_6FB40B50(pUnit2);
	pDVar12 = SKILLS_AllocSkillList(nullptr);
	pUnit2->pSkills = pDVar12;
	sub_6FB45140((int*)pUnit2);
	pDVar13 = DATATBLS_GetDifficultyLevelsTxtRecord(uVar7);
	uVar7 = pDVar13->dwMonsterSkillBonus;
	iVar8 = 0;
	psVar14 = (short*)(iVar15 + 0x170);
	do
	{
		if ((-1 < *psVar14) && (cVar2 = *(char*)(iVar15 + 0x198 + iVar8), '\0' < cVar2))
		{
			SKILLS_AssignSkill(pUnit2, (int)*psVar14, (int)cVar2 + uVar7, 1,
			    __FILE__, __LINE__);
			iVar6 = (int)*(char*)(iVar15 + 0x180 + iVar8);
			pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit2, (int)*psVar14);
			SKILLS_SetSkillMode(pSkill, iVar6);
		}
		iVar8 = iVar8 + 1;
		psVar14 = psVar14 + 1;
	} while (iVar8 < 8);
	D2COMMON_11062_Return((int)pUnit2, uVar7);
	iVar8 = pUnit2->dwClassId;
	if ((((-1 < iVar8) && (iVar8 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
	        (iVar15 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar8 * 0x1a8, iVar15 != 0)) &&
	    (((uint32_t) * (uint8_t*)(iVar15 + 0xd) & *(uint32_t*)((uint8_t*)&gdwBitMasks)) != 0))
	{
		return;
	}
	bVar5 = 0;
	if (pUnit2->dwUnitType == 1)
	{
		iVar15 = iVar8;
		if (((-1 < iVar8) && (iVar8 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
		    (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar8 * 0x1a8, iVar6 != 0))
		{
			iVar15 = (int)*(short*)(iVar6 + 2);
		}
		if ((iVar15 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar15))
			goto LAB_6fb411d1;
	}
	else
	{
	LAB_6fb411d1:
		iVar15 = -1;
	}
	if ((((-1 < iVar8) && (iVar6 = *(int*)((uint8_t*)&sgptDataTables), iVar8 < *(int*)(iVar6 + 0xa80))) &&
	        (iVar8 = (int)*(short*)(*(int*)(iVar6 + 0xa78) + 0x18 + iVar8 * 0x1a8), -1 < iVar8)) &&
	    (((iVar8 < *(int*)(iVar6 + 0xa98) &&
	          (iVar8 = *(int*)(iVar6 + 0xa90) + iVar8 * 0x134, iVar8 != 0)) &&
	        (((uint32_t) * (uint8_t*)(iVar8 + 0xf0) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 8)) != 0))))
	{
		DVar4 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit2->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit2->pSeed) = DVar4;
		bVar5 = (uint8_t)(*(uint32_t*)((uint8_t*)&DVar4 + 0)) & 0x3f;
	}
	if (iVar15 == 0x60)
	{
		bVar5 = 7;
	}
	else if (iVar15 == 0x12d)
	{
		iVar8 = sub_6FB3F270(pUnit2, 0, 0, (code*)(sub_6FB41690));
		bVar5 = (uint8_t)iVar8;
	}
	if (a3 == 0x15f)
	{
		bVar5 = 0x18;
		goto LAB_6fb412ae;
	}
	if (a3 != 0x160)
	{
		if (a3 == 0x161)
		{
			bVar5 = 0x28;
			goto LAB_6fb412ae;
		}
		if ((a3 != 0x165) && (a3 != 0x158))
			goto LAB_6fb412ae;
	}
	bVar5 = 0;
LAB_6fb412ae:
	PATH_SetDirection(pDynamicPath, bVar5);
}

//D2Client.0x6FB412D0
void __fastcall sub_6FB412D0(D2UnitStrc* pUnit, int a2)
{
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar1;
	uint64_t DVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	D2UnitStrc** ppDVar5;
	uint32_t uVar6;
	int32_t DVar7;
	int32_t DVar8;
	int iVar9;
	uint32_t uVar10;
	uint32_t uVar11;

	if (a2 < 0x159)
	{
		if (a2 == 0x158)
		{
			pDVar3 = CUNIT_GetPlayer();
			DVar2 = (uint64_t)((uint64_t)(pDVar3->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pDVar3->pSeed).nHighSeed);
			(*(uint64_t*)&pDVar3->pSeed) = DVar2;
			pDynamicPath = pUnit->pDynamicPath;
			D2COMMON_10203_PATH_SetRotateFlag(pDynamicPath, 1);
			PATH_SetDirection(pDynamicPath, (uint8_t)(*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 0x3f);
			D2COMMON_10203_PATH_SetRotateFlag(pDynamicPath, 0);
			return;
		}
		switch (a2)
		{
		case 0x96:
			byte_6FBBC22C = (uint8_t)(pUnit);
			return;
		case 0x9d:
		case 0x9e:
		case 0x13f:
			PATH_SetUnitCollisionPattern(pUnit, 5);
			PATH_SetMoveTestCollisionMask(pUnit->pDynamicPath, 0);
			return;
		case 0x14b:
			pDVar3 = CUNIT_GetPlayer();
			if (pDVar3 != nullptr)
			{
				UNITS_SetTargetUnitForDynamicUnit(pUnit, pDVar3);
				sub_6FB29010(pUnit, 0);
				return;
			}
		}
	}
	else
	{
		switch (a2)
		{
		case 0x19d:
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
			}
			else
			{
				DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
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
			pDVar3 = sub_6FB3EAF0((int)pUnit, 0x188, iVar9, (D2UnitStrc**)DVar7, 0, 1);
			if (pDVar3 != nullptr)
			{
				UNITS_StoreOwner(pDVar3, pUnit);
				return;
			}
			break;
		case 0x1f1:
		case 0x1f2:
		case 499:
		case 500:
			uVar4 = sub_6FAA88D0(&(pUnit->pSeed).nLowSeed);
			D2_ASSERT(4 >= uVar4 % 5);
			uVar1 = *(uint32_t*)(byte_6FB70BA8 + (uVar4 % 5) * 4);
			uVar11 = 1;
			uVar10 = 0;
			ppDVar5 = sub_6FAB6A90((int*)pUnit);
			uVar6 = sub_6FAB6A60((int*)pUnit);
			pDVar3 = sub_6FB3EAF0((int)pUnit, uVar1, uVar6, ppDVar5, uVar10, uVar11);
			if (pDVar3 != nullptr)
			{
				UNITS_StoreOwner(pDVar3, pUnit);
				UNITS_StoreOwner(pUnit, pDVar3);
				sub_6FB5FB10((int)pDVar3);
				sub_6FB600F0((int)pDVar3, 1);
				sub_6FB448E0((int)pDVar3, 0x40000, 1);
				return;
			}
			break;
		case 0x23a:
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				DVar8 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
			}
			else
			{
				DVar8 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
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
			sub_6FB3EAF0((int)pUnit, 0x265, iVar9, (D2UnitStrc**)DVar8, 0, 1);
		}
	}
}

//D2Client.0x6FB41690
// TODO: decompilation needs review (in_reg)
uint8_t __cdecl sub_6FB41690(uint32_t a12, uint32_t a2)
{
	uint32_t uVar1;
	uint8_t a1;
	uint8_t bVar2;
	int iVar3;
	int32_t DVar4;
	int iVar5;
	int32_t DVar6;
	D2UnitStrc* in_ECX;
	D2UnitStrc* in_EDX;
	int iStack_10;
	int iStack_c;
	uint8_t abStack_8[8];

	if ((in_EDX != nullptr) && (in_EDX->dwUnitType == 1))
	{
		iVar3 = in_EDX->dwClassId;
		if (-1 < iVar3)
		{
			if ((iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
			    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar3 * 0x1a8, iVar5 != 0))
			{
				iVar3 = (int)*(short*)(iVar5 + 2);
			}
			if (((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
			    (iVar3 == 0x12a))
			{
				iVar3 = UNITS_GetDistanceToOtherUnit(in_ECX, in_EDX);
				if (iVar3 < 2)
				{
					a1 = PATH_GetDirection(in_EDX->pDynamicPath);
					abStack_8[0] = 6;
					abStack_8[1] = 7;
					abStack_8[2] = 0;
					abStack_8[3] = 1;
					abStack_8[4] = 2;
					abStack_8[5] = 3;
					abStack_8[6] = 4;
					abStack_8[7] = 5;
					bVar2 = D2Common_11053(a1);
					D2Common_11055(abStack_8[bVar2], &iStack_10, &iStack_c);
					uVar1 = in_EDX->dwUnitType;
					if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
					{
						iVar3 = in_EDX->pDynamicPath->dwClientCoordY;
					}
					else if (in_EDX->pDynamicPath == nullptr)
					{
						iVar3 = 0;
					}
					else
					{
						iVar3 = PATH_GetXPosition(in_EDX->pDynamicPath);
					}
					uVar1 = in_EDX->dwUnitType;
					if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
					{
						DVar4 = (*(int32_t*)&in_EDX->pDynamicPath->tTargetCoord);
					}
					else if (in_EDX->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
					}
					else
					{
						DVar4 = (int32_t)PATH_GetYPosition(in_EDX->pDynamicPath);
					}
					uVar1 = in_ECX->dwUnitType;
					if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
					{
						iVar5 = in_ECX->pDynamicPath->dwClientCoordY;
					}
					else if (in_ECX->pDynamicPath == nullptr)
					{
						iVar5 = 0;
					}
					else
					{
						iVar5 = PATH_GetXPosition(in_ECX->pDynamicPath);
					}
					if (iVar3 + iStack_10 * 3 == iVar5)
					{
						uVar1 = in_ECX->dwUnitType;
						if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
						{
							DVar6 = (*(int32_t*)&in_ECX->pDynamicPath->tTargetCoord);
						}
						else if (in_ECX->pDynamicPath == nullptr)
						{
							(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
							(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
						}
						else
						{
							DVar6 = (int32_t)PATH_GetYPosition(in_ECX->pDynamicPath);
						}
						if ((int32_t)((int)DVar4 + iStack_c * 3) == DVar6)
						{
							return a1;
						}
					}
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FB41860
void __fastcall sub_6FB41860(D2UnitStrc* pUnit)
{
	D2PlayerDataStrc* pDVar1;
	void* pvVar2;

	if (pUnit != nullptr)
	{
		sub_6FB59320((int)pUnit);
		sub_6FB29AE0(pUnit, 1);
		INVENTORY_FreeInventory(pUnit->pInventory);
		pUnit->pInventory = nullptr;
		if (ghAct != nullptr)
		{
			D2Common_10228(pUnit);
			UNITROOM_RemoveUnitFromRoom(pUnit);
			sub_6FB296E0((int)pUnit);
		}
		PATH_FreeDynamicPath(nullptr, pUnit->pDynamicPath);
		pUnit->pDynamicPath = nullptr;
		pvVar2 = D2Common_10958(pUnit, nullptr);
		if (pvVar2 != nullptr)
		{
			sub_6FAA44D0((int)pvVar2);
		}
		if (((pUnit->dwUnitType == 1) &&
		        (pDVar1 = pUnit->pPlayerData, pDVar1 != nullptr)) &&
		    ((void*)pDVar1->nPortalFlags != nullptr))
		{
			D2_FREE((void*)pDVar1->nPortalFlags);
			pDVar1->nPortalFlags = 0;
		}
	}
}

//D2Client.0x6FB41900
// TODO: decompilation needs review (extraout, unaff_)
void __fastcall sub_6FB41900(D2UnitStrc* pUnit2, D2DynamicPathStrc* pDynamicPath2)
{
	int iVar1;
	D2PlayerDataStrc* pDVar2;
	uint64_t DVar3;
	uint8_t bVar4;
	char cVar5;
	int iVar6;
	void* pvVar7;
	D2InventoryStrc* pDVar8;
	uint32_t uVar9;
	D2SkillListStrc* pDVar10;
	D2UnitStrc* extraout_ECX;
	D2UnitStrc* extraout_ECX_00;
	D2UnitStrc* pUnit;
	uint8_t extraout_DL;
	int unaff_EBX;
	int unaff_EBP;
	short* psVar11;
	int iVar12;
	uint32_t uVar13;

	if ((((((int)pDynamicPath2 < 0) ||
	          (iVar12 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar12 + 0xa80) <= (int)pDynamicPath2)) ||
	         (iVar1 = *(int*)(iVar12 + 0xa78) + (int)pDynamicPath2 * 0x1a8, iVar1 == 0)) ||
	        ((iVar6 = (int)*(short*)(iVar1 + 0x18), iVar6 < 0 || (*(int*)(iVar12 + 0xa98) <= iVar6)))) ||
	    (iVar12 = *(int*)(iVar12 + 0xa90) + iVar6 * 0x134, iVar12 == 0))
	{
		return;
	}
	sub_6FB59320((int)pUnit2);
	sub_6FB29AE0(pUnit2, 0);
	INVENTORY_FreeInventory(pUnit2->pInventory);
	pUnit2->pInventory = nullptr;
	sub_6FB296E0((int)pUnit2);
	pvVar7 = D2Common_10958(pUnit2, nullptr);
	if (pvVar7 != nullptr)
	{
		sub_6FAA44D0((int)pvVar7);
	}
	if (((pUnit2->dwUnitType == 1) &&
	        (pDVar2 = pUnit2->pPlayerData, pDVar2 != nullptr)) &&
	    ((void*)pDVar2->nPortalFlags != nullptr))
	{
		D2_FREE((void*)pDVar2->nPortalFlags);
		pDVar2->nPortalFlags = 0;
	}
	pUnit2->nInteract = 0;
	pUnit2->nUpdateType = 0;
	pUnit2->dwClassId = (int)pDynamicPath2;
	if (pUnit2->pDynamicPath == nullptr)
	{
		return;
	}
	PATH_SetVelocity(pUnit2->pDynamicPath, (int)*(short*)(iVar1 + 0x32) << 8,
	    __FILE__, __LINE__);
	PATH_SetUnitAliveCollision(pUnit2, 0);
	bVar4 = *(uint8_t*)(iVar1 + 0xd);
	pUnit = extraout_ECX;
	if ((((uint8_t)((uint8_t*)&gdwBitMasks)[4] & bVar4) != 0) && (pUnit2->pInventory == nullptr))
	{
		pDVar8 = INVENTORY_AllocInventory(nullptr, pUnit2);
		pUnit2->pInventory = pDVar8;
		pUnit = extraout_ECX_00;
		bVar4 = extraout_DL;
	}
	STATLIST_AllocStatListEx(pUnit, bVar4, (StatListValueChangeFunc)(pUnit2), nullptr);
	STATLIST_SetUnitStat(pUnit2, 0x44, 100, 0);
	STATLIST_SetUnitStat(pUnit2, 0x43, 100, 0);
	STATLIST_SetUnitStat(pUnit2, 0x45, 100, 0);
	bVar4 = sub_6FAAC090();
	uVar13 = (uint32_t)bVar4;
	STATLIST_SetUnitStat(pUnit2, 0x24, (int)*(short*)(iVar1 + 0x144 + uVar13 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x25, (int)*(short*)(iVar1 + 0x14a + uVar13 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x27, (int)*(short*)(iVar1 + 0x150 + uVar13 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x29, (int)*(short*)(iVar1 + 0x156 + uVar13 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x2b, (int)*(short*)(iVar1 + 0x15c + uVar13 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 0x2d, (int)*(short*)(iVar1 + 0x162 + uVar13 * 2), 0);
	STATLIST_SetUnitStat(pUnit2, 7, 0x8000, 0);
	STATLIST_SetUnitStat(pUnit2, 6, 0x8000, 0);
	UNITS_ChangeAnimMode(pUnit2, 1);
	uVar13 = pUnit2->dwFrameCountPrecise;
	if ((int)uVar13 < 1)
	{
		uVar9 = 0;
	}
	else if ((uVar13 & uVar13 - 1) == 0)
	{
		uVar9 = sub_6FAA88D0(&(pUnit2->pSeed).nLowSeed);
		uVar9 = uVar9 & uVar13 - 1;
	}
	else
	{
		DVar3 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit2->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit2->pSeed) = DVar3;
		uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar13);
		iVar12 = unaff_EBX;
	}
	pUnit2->nSeqCurrentFramePrecise = uVar9;
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(iVar12 + 4)) == 0)
	{
		uVar13 = pUnit2->dwFlags & 0xfffffffd;
	}
	else
	{
		uVar13 = pUnit2->dwFlags | 2;
	}
	pUnit2->dwFlags = uVar13;
	pUnit2->dwFlagEx = pUnit2->dwFlagEx & 0xfffbffff;
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x18] & *(uint8_t*)(iVar12 + 5)) == 0)
	{
		uVar13 = pUnit2->dwFlags | 0x20;
	}
	else
	{
		uVar13 = pUnit2->dwFlags & 0xffffffdf;
	}
	pUnit2->dwFlags = uVar13;
	pUnit2->dwFlags = uVar13 | 8;
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar12 + 5)) == 0)
	{
		uVar13 = uVar13 & 0xfffffffb | 8;
	}
	else
	{
		uVar13 = uVar13 | 0xc;
	}
	pUnit2->dwFlags = uVar13;
	if ((pUnit2->dwUnitType == 1) &&
	    (pDVar2 = pUnit2->pPlayerData, pDVar2 != nullptr))
	{
		*(uint16_t*)&pDVar2->unk0x28 = 0;
		iVar12 = pUnit2->dwClassId;
		if ((iVar12 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar12))
		{
			iVar12 = 0;
		}
		else
		{
			iVar12 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar12 * 0x1a8;
		}
		*(int*)pDVar2->szName = iVar12;
	}
	sub_6FB412D0(pUnit2, unaff_EBP);
	sub_6FB40B50(pUnit2);
	sub_6FB45140((int*)pUnit2);
	pDVar10 = SKILLS_AllocSkillList(nullptr);
	pUnit2->pSkills = pDVar10;
	iVar12 = 0;
	psVar11 = (short*)(iVar1 + 0x170);
	do
	{
		if (-1 < *psVar11)
		{
			SKILLS_AssignSkill(pUnit2, (int)*psVar11, (int)*(char*)(iVar12 + 0x198 + iVar1), 0,
			    __FILE__, __LINE__);
		}
		iVar12 = iVar12 + 1;
		psVar11 = psVar11 + 1;
	} while (iVar12 < 8);
	if (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar1 + 0xd)) == 0)
	{
		DVar3 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit2->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit2->pSeed) = DVar3;
		PATH_SetDirection(pDynamicPath2, (uint8_t)(*(uint32_t*)((uint8_t*)&DVar3 + 0)) & 0x3f);
	}
	sub_6FB4DAC0(pUnit2);
	uVar13 = 2;
	if (*(uint8_t*)(iVar1 + 0x4d) < 8)
	{
		uVar13 = *(uint8_t*)(iVar1 + 0x4d) + 2;
	}
	iVar12 = pUnit2->dwClassId;
	if ((iVar12 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar12))
	{
		iVar12 = -1;
	LAB_6fb41ce7:
		if ((iVar12 != 0x9c) && (iVar12 != 0xd3))
			goto LAB_6fb41d3c;
	LAB_6fb41cf3:
		cVar5 = sub_6FAAC090();
		if (cVar5 != '\0')
		{
			if (cVar5 == '\x01')
			{
				uVar13 = 3;
				goto LAB_6fb41d46;
			}
			if (cVar5 == '\x02')
			{
				uVar13 = 4;
				goto LAB_6fb41d46;
			}
			goto LAB_6fb41d3c;
		}
	}
	else
	{
		if (iVar12 < 0xf4)
		{
			if (iVar12 < 0xf2)
				goto LAB_6fb41ce7;
			goto LAB_6fb41cf3;
		}
		if (iVar12 == 0x14d)
		{
			uVar13 = 5;
			goto LAB_6fb41d46;
		}
		if (iVar12 == 0x20f)
		{
			sub_6FB5BA70(pUnit2, 0xe3, 5, 0, 0, 0, 0, 0);
		}
	LAB_6fb41d3c:
		if (uVar13 < 8)
			goto LAB_6fb41d46;
	}
	uVar13 = 2;
LAB_6fb41d46:
	sub_6FB28410((int)pUnit2, uVar13);
	sub_6FB28470((int)pUnit2, uVar13);
}

//D2Client.0x6FB41D70
int __fastcall sub_6FB41D70(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t auStack_1c[7];

	if (pUnit == nullptr)
	{
		return 0;
	}
	if (pUnit->dwUnitType == 1)
	{
		iVar1 = pUnit->dwClassId;
		if (((iVar1 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar1)) ||
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar1 * 0x1a8, iVar1 == 0))
		{
			return 0;
		}
		if (((*(char*)(iVar1 + 0x1a4) == '\x01') && (pUnit->dwAnimMode == 0)) &&
		    (iVar1 = UNITS_IsAtEndOfFrameCycle(pUnit), iVar1 != 0))
		{
			puVar3 = auStack_1c;
			for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				*puVar3 = 0;
				puVar3 = puVar3 + 1;
			}
			sub_6FB42D40(9, pUnit, auStack_1c);
		}
	}
	iVar1 = 0;
	switch (*(uint32_t*)(a2 + 4))
	{
	case 0:
		break;
	case 1:
		iVar1 = UNITS_IsAtEndOfFrameCycle(pUnit);
		if (iVar1 != 0)
		{
			return iVar1;
		}
		break;
	case 2:
		iVar2 = UNITS_IsAtEndOfFrameCycle(pUnit);
		if (iVar2 != 0)
		{
			pUnit->wAnimSpeed = 0;
			pUnit->nSeqCurrentFramePrecise = pUnit->dwFrameCountPrecise + -0x100;
			if (pUnit->dwAnimMode != 0)
			{
				return 0;
			}
			pUnit->dwFlags = pUnit->dwFlags | 0x20;
			return 0;
		}
		break;
	case 3:
		pUnit->nSeqCurrentFramePrecise = 0x100;
		pUnit->wAnimSpeed = 0;
	default:
		return 0;
	}
	UNITS_StopSequence(pUnit);
	return iVar1;
}

//D2Client.0x6FB41E90
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB41E90(D2UnitStrc* pUnit)
{
	uint8_t bVar1;
	short sVar2;
	D2DynamicPathStrc* pDVar3;
	bool bVar4;
	bool bVar5;
	int iVar6;
	D2SkillStrc* pSkill;
	uint32_t uVar7;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	int iVar8;
	uint32_t extraout_var_01;
	D2UnitStrc* pDVar9;
	int32_t nY;
	D2UnitStrc** ppDVar10;
	float fVar11;
	uint32_t uVar12;
	int* piStack_10;
	int iStack_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	if (pUnit == nullptr)
	{
		return;
	}
	if (pUnit->dwUnitType != 1)
	{
		return;
	}
	iVar6 = STATES_CheckState(pUnit, 1);
	if ((iVar6 != 0) && (iVar6 = sub_6FB29550((int*)pUnit), iVar6 == 0))
	{
		return;
	}
	uVar7 = pUnit->dwAnimMode;
	if (0xf < (int)uVar7)
	{
		return;
	}
	if (pUnit->dwUnitType != 1)
	{
		return;
	}
	if (0xf < (int)uVar7)
	{
		return;
	}
	iVar6 = pUnit->dwClassId;
	uStack_8 = uVar7;
	if ((iVar6 == 0xf3) && (uVar7 == 0xb))
	{
		piStack_10 = (int*)(&dword_6FB91698);
	}
	else if ((iVar6 == 0x14d) && (uVar7 == 0xb))
	{
		piStack_10 = (int*)(&dword_6FB91698);
	}
	else if ((iVar6 == 0x21f) && (uVar7 == 10))
	{
		piStack_10 = (int*)&byte_6FB916A4;
	}
	else if ((iVar6 == 0x220) && (uVar7 == 10))
	{
		piStack_10 = (int*)&byte_6FB916A4;
	}
	else if ((iVar6 == 0x23a) && (uVar7 == 10))
	{
		piStack_10 = (int*)&byte_6FB916A4;
	}
	else
	{
		iVar6 = sub_6FB247F0(iVar6);
		if (iVar6 == 0)
		{
			return;
		}
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[(uVar7 & 7) * 4] & *(uint8_t*)(((int)uVar7 >> 3) + 0x104 + iVar6)) ==
		    0)
		{
			if ((uVar7 == 0) && (iVar6 = MONSTERS_IsSandLeaper(pUnit, 0), iVar6 != 0))
			{
				piStack_10 = (int*)byte_6FB91650;
				goto LAB_6fb41fce;
			}
			piStack_10 = (int*)(byte_6FB91590 + pUnit->dwAnimMode * 0xc);
		}
		else
		{
			piStack_10 = (int*)(byte_6FB91650 + uVar7 * 0xc);
		}
		if (piStack_10 == nullptr)
		{
			return;
		}
	}
LAB_6fb41fce:
	if ((pUnit->dwUnitType == 1) &&
	    (pSkill = UNITS_GetUsedSkill(pUnit), pSkill != nullptr))
	{
		iVar6 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		iVar6 = sub_6FB14AE0(iVar6);
		if (iVar6 != 0)
		{
			uVar7 = SKILLS_GetFlags(pSkill);
			bVar5 = true;
			if (((uVar7 & 1) != 0) && (bVar4 = sub_6FB4E5D0(pUnit), D2C_ZEXT(bVar4) != 0))
			{
				if (*(short*)(iVar6 + 0x2e) != 0x43)
				{
					SKILLS_SetFlags(pSkill, uVar7 | 2);
				}
				sub_6FABCA30(pUnit);
				bVar5 = false;
			}
			bVar1 = pUnit->nActionFrame;
			if ((bVar1 == 4) ||
			    (((bVar5 && (bVar5 = sub_6FB448C0((int)pUnit, 0x40), D2C_ZEXT(bVar5) == 0)) && ((bVar1 == 1 || ((bVar1 == 2 || (bVar1 == 3))))))))
			{
				sub_6FABCA30(pUnit);
			}
			else
			{
				sVar2 = *(short*)(iVar6 + 0x2e);
				if (sVar2 == 0x5f)
				{
					iVar6 = sub_6FB247F0(pUnit->dwClassId);
					if ((iVar6 != 0) &&
					    (sub_6FABCA30(pUnit),
					        (int)(uint32_t) * (uint8_t*)(iVar6 + 0x109) < pUnit->nSeqCurrentFramePrecise >> 8))
					{
						pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar6 + 0x10a) << 8;
					}
				}
				else if (sVar2 == 0x7e)
				{
					sub_6FABCA30(pUnit);
					if (0xbff < (int)(pUnit->nSeqCurrentFramePrecise & 0xffffff00U))
					{
						pUnit->nSeqCurrentFramePrecise = 0x800;
					}
				}
				else if (((sVar2 == 0x98) && (iVar6 = sub_6FB247F0(pUnit->dwClassId), iVar6 != 0)) &&
				         (iVar8 = STATES_CheckState(pUnit, 0xc), iVar8 != 0))
				{
					iVar8 = pUnit->nSeqCurrentFramePrecise >> 8;
					if ((int)(uint32_t) * (uint8_t*)(iVar6 + 0x109) <= iVar8)
					{
						sub_6FABCA30(pUnit);
					}
					if ((int)(uint32_t) * (uint8_t*)(iVar6 + 0x10a) <= iVar8)
					{
						uVar7 = sub_6FAA88F0((uint64_t*)&pUnit->pSeed, 4);
						pUnit->nSeqCurrentFramePrecise =
						    ((uVar7 - 4) + (uint32_t) * (uint8_t*)(iVar6 + 0x10a)) * 0x100;
					}
				}
			}
		}
	}
	iStack_c = 0;
	if (*piStack_10 == 1)
	{
		bVar5 = sub_6FB4E5D0(pUnit);
		iStack_c = D2C_ZEXT(bVar5);
	}
	if ((uStack_8 == 1) &&
	    (((pUnit->dwUnitType != 1 || (pUnit->pPlayerData == nullptr)) ||
	        ((pUnit->pPlayerData->unk0x28 & 1) == 0))))
	{
		pDVar3 = pUnit->pDynamicPath;
		if ((pDVar3 != nullptr) &&
		    (pDVar9 = PATH_GetTargetUnit(pDVar3), pDVar9 != nullptr))
		{
			PATH_GetTargetTypeAndGUID(pDVar3, (int*)&uStack_8, &uStack_4);
			pDVar9 = sub_6FB269F0(uStack_4, uStack_8);
			PATH_SetTargetUnit(pDVar3, pDVar9);
			if (pDVar9 == nullptr)
				goto LAB_6fb421de;
		}
		D2Common_10213(pUnit);
	}
LAB_6fb421de:
	iVar6 = pUnit->dwClassId;
	if (((-1 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
	    (iVar8 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar6 * 0x1a8, iVar8 != 0))
	{
		if (((((((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar8 + 0xd)) != 0) &&
		          ((iVar6 = sub_6FB247F0(iVar6), iVar6 == 0 ||
		                                             (uStack_4 = (uint32_t) * (uint8_t*)(iVar6 + 5) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x14),
		                                                 uStack_4 == 0)))) &&
		         (pUnit->dwAnimMode == 1)) &&
		        ((uStack_4 = pUnit->dwFlags >> 9 & 1, uStack_4 == 0 &&
		                                                  (iVar6 = pUnit->dwClassId, iVar6 != 0x219)))) &&
		    (((iVar6 != 0x21a &&
		          ((((iVar6 != 0x21b && (pDVar9 = CUNIT_GetPlayer(), pDVar9 != nullptr)) &&
		                (uVar7 = D2Common_10399(pUnit, pDVar9), uVar7 < 7)) &&
		              ((&pUnit->pSeed != nullptr &&
		                  (uVar7 = sub_6FAA88D0(&(pUnit->pSeed).nLowSeed), uVar7 % 100 < 10)))))) &&
		        (pDVar3 = pUnit->pDynamicPath, pDVar3 != nullptr))))
		{
			uVar7 = pDVar9->dwUnitType;
			if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
			{
				nY = (*(int32_t*)&pDVar9->pDynamicPath->tTargetCoord);
			}
			else if (pDVar9->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
			}
			else
			{
				nY = (int32_t)PATH_GetYPosition(pDVar9->pDynamicPath);
			}
			uVar7 = pDVar9->dwUnitType;
			if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
			{
				iVar6 = pDVar9->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar9->pDynamicPath == nullptr)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = PATH_GetXPosition(pDVar9->pDynamicPath);
			}
			D2Common_10216(pDVar3, iVar6, (int)nY, 0);
		}
		iVar8 = sub_6FB41D70(pUnit, (int)piStack_10);
		iVar6 = 0;
		switch (piStack_10[2])
		{
		case 1:
			iVar6 = iStack_c;
			break;
		case 2:
		case 3:
			iVar6 = iVar8;
			break;
		case 4:
			if ((iStack_c != 0) && (iVar8 = UNITS_IsAtEndOfFrameCycle(pUnit), iVar8 != 0))
			{
				iVar6 = 1;
			}
		}
		sub_6FB42420(pUnit);
		sub_6FB46280(pUnit);
		if (pUnit->pDynamicPath != nullptr)
		{
			D2COMMON_10193_PATH_AdjustDirection(pUnit->pDynamicPath);
		}
		if (iVar6 != 0)
		{
			sub_6FB42750(pUnit);
		}
		if ((pUnit->dwAnimMode == 0) && (pUnit->dwClassId == 0x210))
		{
			uStack_4 = pUnit->dwFlags & 1;
			if (uStack_4 != 0)
			{
				uVar12 = 0;
				uVar7 = 2;
				pUnit->dwFlags = pUnit->dwFlags & 0xfffffffe;
				ppDVar10 = sub_6FAB6A90((int*)pUnit);
				fVar11 = (float)sub_6FAB6A60((int*)pUnit);
				sub_6FB27D50(0x1de, fVar11, (int)ppDVar10, uVar7, uVar12);
			}
		}
		iVar6 = STATES_CheckStateMaskActiveOnUnit(pUnit);
		if (iVar6 != 0)
		{
			sub_6FABD780(pUnit);
		}
		sub_6FB50370(pUnit);
		sub_6FB4FF80(pUnit);
	}
}

//D2Client.0x6FB42420
void __fastcall sub_6FB42420(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar1;
	uint32_t uVar2;
	uint8_t bVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	uint32_t uVar6;
	int32_t DVar7;
	uint32_t uVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	uint32_t* puVar12;
	int iVar13;
	uint32_t uVar14;
	uint32_t uVar15;
	uint64_t DStack_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int32_t DStack_3c;
	uint32_t uStack_34;
	uint32_t uStack_2c;

	if (((pUnit != nullptr) && (pUnit->dwUnitType == 1)) &&
	    (iVar4 = D2Common_11050(pUnit, 1), iVar4 != -1))
	{
		puVar12 = &uStack_5c;
		for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
		{
			*puVar12 = 0;
			puVar12 = puVar12 + 1;
		}
		uStack_5c = 0x20;
		if ((0x3e < iVar4) && (iVar4 < 0x43))
		{
			uStack_5c = 0x34;
			uStack_34 = 2;
		}
		uStack_2c = 1;
		pDStack_58 = pUnit;
		pDStack_54 = pUnit;
		iStack_4c = iVar4;
		pDVar5 = sub_6FB296A0((int)pUnit);
		if (pDVar5 == nullptr)
		{
			pDynamicPath = pUnit->pDynamicPath;
			if (pDynamicPath == nullptr)
			{
				return;
			}
			iStack_40 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
			DStack_3c = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
		}
		else
		{
			uVar6 = pDVar5->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				iStack_40 = pDVar5->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar5->pDynamicPath == nullptr)
			{
				iStack_40 = 0;
			}
			else
			{
				iStack_40 = PATH_GetXPosition(pDVar5->pDynamicPath);
			}
			uVar6 = pDVar5->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DStack_3c = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
			}
			else if (pDVar5->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
			}
			else
			{
				DStack_3c = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
			}
		}
		if ((iVar4 == 0xee) || (iVar4 == 0xef))
		{
			if (pDVar5 != nullptr)
			{
				sub_6FB3EBE0(pUnit, iVar4, 0, 0, 0, 0, 0, 1, 0);
			}
		}
		else if (iVar4 == 0x196)
		{
			pDVar5 = sub_6FB26AD0((int)pUnit);
			if (pDVar5 != nullptr)
			{
				D2_ASSERT(pDVar5->dwUnitType == 3);
				sub_6FB3DC50(pDVar5, nullptr, 0);
			}
			uVar6 = sub_6FAA88D0(&(pUnit->pSeed).nLowSeed);
			D2_ASSERT(4 >= uVar6 % 5);
			uVar1 = pUnit->dwUnitType;
			uVar2 = *(uint32_t*)(byte_6FB70BA8 + (uVar6 % 5) * 4);
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
			}
			else
			{
				DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar15 = 1;
			uVar14 = 0;
			uVar8 = sub_6FAB6A60((int*)pUnit);
			pDVar5 = sub_6FB3EAF0((int)pUnit, uVar2, uVar8, (D2UnitStrc**)DVar7, uVar14, uVar15);
			if (pDVar5 != nullptr)
			{
				UNITS_StoreOwner(pDVar5, pUnit);
				UNITS_StoreOwner(pUnit, pDVar5);
				sub_6FB5FB10((int)pDVar5);
				sub_6FB600F0((int)pDVar5, 1);
				pDVar5->dwFlagEx = pDVar5->dwFlagEx | 0x40000;
			}
		}
		else
		{
			sub_6FB3E070(&uStack_5c);
		}
		DVar7 = DStack_3c;
		iVar10 = iStack_40;
		if (((((pUnit->dwUnitType == 1) && (iVar9 = sub_6FB44910(pUnit->dwClassId), -1 < iVar9)) &&
		         (iVar11 = *(int*)((uint8_t*)&sgptDataTables), iVar9 < *(int*)(iVar11 + 0xa80))) &&
		        ((iVar9 == 0x3f && (iVar9 = pUnit->dwClassId, -1 < iVar9)))) &&
		    ((iVar9 < *(int*)(iVar11 + 0xa80) &&
		        (iVar9 = *(int*)(iVar11 + 0xa78) + iVar9 * 0x1a8, iVar9 != 0))))
		{
			iVar11 = 5;
			iVar13 = 5;
			SEED_InitSeed((D2SeedStrc*)(&DStack_64));
			SEED_InitLowSeed((D2SeedStrc*)(&DStack_64), 0x53454953);
			(*(uint32_t*)((uint8_t*)&DStack_64 + 4)) = pUnit->dwUnitId;
			bVar3 = sub_6FAAC090();
			iVar9 = (int)*(short*)(iVar9 + 0x62 + (uint32_t)bVar3 * 2);
			if (0 < iVar9)
			{
				do
				{
					uVar6 = sub_6FAA88D0(&(*(uint32_t*)((uint8_t*)&DStack_64 + 0)));
					if ((uVar6 & 1) != 0)
					{
						iVar11 = -iVar11;
					}
					uVar6 = sub_6FAA88D0(&(*(uint32_t*)((uint8_t*)&DStack_64 + 0)));
					if ((uVar6 & 1) != 0)
					{
						iVar13 = -iVar13;
					}
					sub_6FB3EB50(pUnit, iVar4, iVar11 + iVar10, (D2UnitStrc*)(iVar13 + (int)DVar7), 0, 1);
					iVar9 = iVar9 + -1;
				} while (iVar9 != 0);
			}
		}
	}
}

//D2Client.0x6FB42750
void __fastcall sub_6FB42750(D2UnitStrc* pUnit)
{
	int iVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar2;
	uint32_t uVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	uint32_t uVar6;
	int32_t DVar7;
	uint32_t uVar8;
	bool bVar9;
	uint32_t uVar10;
	uint32_t uVar11;

	if (pUnit == nullptr)
	{
		return;
	}
	if (pUnit->dwUnitType != 1)
	{
		return;
	}
	if (0xf < pUnit->dwAnimMode)
	{
		return;
	}
	iVar4 = pUnit->dwClassId;
	if (iVar4 < 0)
	{
	LAB_6fb427bd:
		iVar4 = -1;
	}
	else
	{
		if ((iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar4 * 0x1a8, iVar1 != 0))
		{
			iVar4 = (int)*(short*)(iVar1 + 2);
		}
		if ((iVar4 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar4))
			goto LAB_6fb427bd;
	}
	if ((pUnit->dwAnimMode == 0xd) && (iVar4 != 0x4e))
	{
		pDynamicPath = pUnit->pDynamicPath;
		if (pDynamicPath == nullptr)
		{
			return;
		}
		PATH_RecacheRoomIfNeeded(pDynamicPath);
		D2COMMON_10208_PathSetPathingFlag(pDynamicPath, 0);
		PATH_ResetToPreviousType(pDynamicPath);
		sub_6FB4F410(pUnit, (int*)0x3);
		return;
	}
	pDVar5 = sub_6FB296A0((int)pUnit);
	if (pDVar5 != nullptr)
	{
		sub_6FB29010(pUnit, 0);
	}
	if (iVar4 < 0)
	{
		return;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar4)
	{
		return;
	}
	iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar4 * 0x1a8;
	if (iVar1 == 0)
	{
		return;
	}
	if (*(char*)(iVar1 + 0x1a7) == '\0')
		goto switchD_6fb42863_caseD_3;
	switch (pUnit->dwAnimMode)
	{
	case 2:
		if (iVar4 == 0xe7)
		{
			return;
		}
		if (iVar4 == 0x76)
		{
			return;
		}
		break;
	case 4:
		if ((iVar4 != 0x193) && (iVar4 != 0x194))
		{
			if (iVar4 == 0x1f1)
			{
				pDVar5 = sub_6FB26AD0((int)pUnit);
				if (pDVar5 != nullptr)
				{
					D2_ASSERT(pDVar5->dwUnitType == 3);
					sub_6FB3DC50(pDVar5, nullptr, 0);
				}
				uVar6 = sub_6FAA88D0(&(pUnit->pSeed).nLowSeed);
				D2_ASSERT(4 >= uVar6 % 5);
				uVar2 = pUnit->dwUnitType;
				uVar3 = *(uint32_t*)(byte_6FB70BA8 + (uVar6 % 5) * 4);
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
				}
				else
				{
					DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar11 = 1;
				uVar10 = 0;
				uVar8 = sub_6FAB6A60((int*)pUnit);
				pDVar5 = sub_6FB3EAF0((int)pUnit, uVar3, uVar8, (D2UnitStrc**)DVar7, uVar10, uVar11);
				if (pDVar5 != nullptr)
				{
					UNITS_StoreOwner(pDVar5, pUnit);
					UNITS_StoreOwner(pUnit, pDVar5);
					sub_6FB5FB10((int)pDVar5);
					sub_6FB600F0((int)pDVar5, 1);
					pDVar5->dwFlagEx = pDVar5->dwFlagEx | 0x40000;
				}
			}
			break;
		}
		goto LAB_6fb42887;
	case 5:
	case 9:
		goto switchD_6fb42863_caseD_5;
	case 8:
		if (iVar4 == 0x6e)
		{
			return;
		}
		goto switchD_6fb42863_caseD_5;
	case 10:
		if (iVar4 == 0x88)
		{
			sub_6FB4F410(pUnit, (int*)0xb);
			UNITS_SetAnimStartFrame(pUnit);
			return;
		}
		break;
	case 0xb:
		bVar9 = iVar4 == 0x88;
		goto LAB_6fb429f5;
	case 0xc:
		bVar9 = iVar4 == 0x11c;
		goto LAB_6fb429f5;
	case 0xe:
		bVar9 = iVar4 == 0xf7;
	LAB_6fb429f5:
		if (bVar9)
		{
			return;
		}
	}
switchD_6fb42863_caseD_3:
	if (((pUnit->dwFlags >> 0x15 & 1) != 0) || ((pUnit->dwFlagEx >> 0xd & 1) == 0))
	{
		sub_6FB4F410(pUnit, (int*)0x1);
		UNITS_SetAnimStartFrame(pUnit);
	}
	return;
switchD_6fb42863_caseD_5:
	if ((iVar4 == 0x193) || (iVar4 == 0x194))
	{
	LAB_6fb42887:
		sub_6FB4F410(pUnit, (int*)0x8);
		UNITS_SetAnimStartFrame(pUnit);
		return;
	}
	goto switchD_6fb42863_caseD_3;
}

//D2Client.0x6FB42A70
uint32_t __fastcall sub_6FB42A70(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint32_t uVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	uint64_t uVar5;
	uint64_t DVar6;
	uint8_t bVar7;
	uint16_t uVar8;
	uint32_t uVar9;
	int iVar10;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar11;
	int32_t DVar12;
	uint32_t uStack_20;

	if (a3 != 0)
	{
		DVar6 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar6;
		uVar5 = (uint64_t)DVar6 & 0xffffffff;
		if ((int)(uVar5 % 0x19) != 0)
		{
			return (uint32_t)(uVar5 / 0x19);
		}
	}
	if (((pUnit != nullptr) && (pUnit->dwUnitType == 1)) && (pUnit->dwAnimMode == 3))
	{
		DVar6 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar6;
		uVar5 = (uint64_t)DVar6 & 0xffffffff;
		if ((int)(uVar5 % 3) != 0)
		{
			return (uint32_t)(uVar5 / 3);
		}
	}
	uVar9 = STATLIST_UnitGetItemStatOrSkillStatValue(pUnit, 0x8c, 0);
	a3 = a2;
	if (uVar9 != 0)
	{
		a3 = uVar9;
	}
	if (((((pUnit != nullptr) && (uVar9 = pUnit->dwClassId, -1 < (int)uVar9)) &&
	         ((iVar10 = *(int*)((uint8_t*)&sgptDataTables), (int)uVar9 < *(int*)(iVar10 + 0xa80) &&
	                                                            ((uVar9 = (uint32_t) * (short*)(*(int*)(iVar10 + 0xa78) + 0x18 + uVar9 * 0x1a8), -1 < (int)uVar9 && ((int)uVar9 < *(int*)(iVar10 + 0xa98))))))) &&
	        (uVar1 = *(int*)(iVar10 + 0xa90) + uVar9 * 0x134, uVar9 = uVar1, uVar1 != 0)) &&
	    ((*(char*)(uVar1 + 0x11d) != '\0' && (uStack_20 = 0, uVar9 = a3, 0 < (int)a3))))
	{
		do
		{
			iVar10 = PATH_GetVelocity(pUnit->pDynamicPath);
			if (iVar10 == 0)
			{
				DVar6 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				uVar9 = (*(uint32_t*)((uint8_t*)&DVar6 + 0));
				(*(uint64_t*)&pUnit->pSeed) = DVar6;
			}
			else
			{
				bVar7 = UNITS_GetDirection(pUnit);
				DVar6 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar6;
				uVar9 = (int)(((uint64_t)DVar6 & 0xffffffff) % 7) + -3 + (uint32_t)(bVar7 >> 3);
			}
			uVar9 = uVar9 & 7;
			pRoom = UNITS_GetRoom(pUnit);
			uVar11 = uVar9 - 1 & 7;
			if (uVar9 == uVar11)
			{
				return uVar11;
			}
			while (true)
			{
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iVar10 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar10 = 0;
				}
				else
				{
					iVar10 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				iVar3 = *(int*)(byte_6FB70BC0 + uVar9 * 4);
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DVar12 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar12 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar12 + 2)) = 0;
				}
				else
				{
					DVar12 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				iVar4 = *(int*)(byte_6FB70BE0 + uVar9 * 4);
				uVar8 = COLLISION_CheckMask(pRoom, iVar3 + iVar10, iVar4 + (int)DVar12, 1);
				if (uVar8 == 0)
					break;
				uVar9 = uVar9 + 1 & 7;
				if (uVar9 == uVar11)
				{
					return uVar11;
				}
			}
			uVar9 = (uint32_t) * (uint8_t*)(uVar1 + 0x11d) * 2;
			if (*(uint8_t*)(uVar1 + 0x11d) == 0)
			{
				uVar9 = 0;
			}
			else
			{
				uVar11 = (pUnit->pSeed).nLowSeed;
				if ((uVar9 & uVar9 - 1) == 0)
				{
					DVar6 = (uint64_t)((uint64_t)uVar11 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar6;
					uVar9 = uVar9 - 1 & (*(uint32_t*)((uint8_t*)&DVar6 + 0));
				}
				else
				{
					DVar6 = (uint64_t)((uint64_t)uVar11 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar6;
					uVar9 = (*(uint32_t*)((uint8_t*)&DVar6 + 0)) % uVar9;
				}
			}
			sub_6FB3EB50(pUnit, uVar9 + 0x12, iVar3 + iVar10, (D2UnitStrc*)(iVar4 + (int)DVar12), 0, 1);
			uVar9 = uStack_20 + 1;
			uStack_20 = uVar9;
		} while ((int)uVar9 < (int)a3);
	}
	return uVar9;
}

//D2Client.0x6FB42D40
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB42D40(uint32_t a1, D2UnitStrc* pUnit, uint32_t* ptParams)
{
	int iVar1;
	uint8_t bVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	uint32_t uVar5;
	int32_t DVar6;
	int32_t DVar7;
	float fVar8;
	int32_t DVar9;
	int32_t DVar10;
	D2UnitStrc* pDVar11;
	int32_t DVar12;
	int32_t DVar13;
	D2SkillStrc* pDVar14;
	D2AnimSeqTxt* pDVar15;
	uint32_t uVar16;
	int iVar17;
	uint16_t extraout_var;
	int* piVar18;
	uint32_t* puVar19;
	int iVar20;
	bool bVar21;
	D2DynamicPathStrc* pDVar22;
	uint32_t uStack_94;
	uint32_t local_90;
	int* piStack_8c;
	D2DynamicPathStrc* local_88;
	int iStack_84;
	int iStack_80;
	uint32_t auStack_7c[5];
	uint32_t uStack_68;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_2c;

	pDVar22 = pUnit->pDynamicPath;
	local_90 = a1;
	local_88 = pDVar22;
	if (pUnit->dwAnimMode == 0xd)
	{
		PATH_RecacheRoomIfNeeded(pDVar22);
		PATH_ResetToPreviousType(pDVar22);
	}
	iVar3 = sub_6FB29550((int*)pUnit);
	if (iVar3 == 0)
	{
		PATH_AddCollisionFootprintForOptionalUnit(pUnit);
	}
	else if ((a1 != 8) && (a1 != 9))
	{
		PATH_SetUnitAliveCollision(pUnit, 0);
		sub_6FB40B50(pUnit);
		pUnit->dwFlagEx = pUnit->dwFlagEx & 0xfffbffff;
	}
	iStack_84 = 0;
	if ((((a1 != 0x13) && (a1 != 0x16)) && (a1 != 0x15)) && (ptParams != nullptr))
	{
		iStack_84 = 1;
		if ((0 < (int)ptParams[3]) && (PATH_SetType(pDVar22, ptParams[3]), a1 == 0x14))
		{
			PATH_SetNewDistance(pDVar22, (uint8_t)ptParams[5]);
			PATH_SetStepNum(pDVar22, (uint8_t)ptParams[2]);
		}
		UNITS_SetUsedSkill(pUnit, nullptr);
		sub_6FB461B0(pUnit);
	}
	uVar16 = local_90;
	uStack_94 = pUnit->dwClassId;
	if ((int)uStack_94 < 0)
	{
		return;
	}
	iVar3 = *(int*)((uint8_t*)&sgptDataTables);
	iVar20 = *(int*)(iVar3 + 0xa80);
	if (iVar20 <= (int)uStack_94)
	{
		return;
	}
	iVar1 = *(int*)(iVar3 + 0xa78);
	if (iVar1 + uStack_94 * 0x1a8 == 0)
	{
		return;
	}
	if ((int)uStack_94 < 0)
	{
		return;
	}
	if (iVar20 <= (int)uStack_94)
	{
		return;
	}
	iVar17 = (int)*(short*)(iVar1 + 0x18 + uStack_94 * 0x1a8);
	if (iVar17 < 0)
	{
		return;
	}
	if (*(int*)(iVar3 + 0xa98) <= iVar17)
	{
		return;
	}
	piStack_8c = (int*)(*(int*)(iVar3 + 0xa90) + iVar17 * 0x134);
	if (piStack_8c == nullptr)
	{
		return;
	}
	if ((pUnit->dwUnitType == 1) && (-1 < (int)uStack_94))
	{
		if (((int)uStack_94 < iVar20) && (iVar1 = iVar1 + uStack_94 * 0x1a8, iVar1 != 0))
		{
			uStack_94 = (uint32_t) * (short*)(iVar1 + 2);
		}
		if (((int)uStack_94 < 0) || (iVar20 <= (int)uStack_94))
			goto LAB_6fb42ec0;
	}
	else
	{
	LAB_6fb42ec0:
		uStack_94 = 0xffffffff;
	}
	switch (local_90)
	{
	case 0:
	case 0x18:
		D2_ASSERT(ptParams != nullptr);
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 1);
		uVar5 = *ptParams;
		sub_6FB28F90(pUnit, uVar5, ptParams[1]);
		if ((((pUnit->dwUnitType == 1) && (pUnit->pPlayerData != nullptr)) &&
		        ((pUnit->pPlayerData->unk0x28 & 1) != 0)) ||
		    (iVar3 = sub_6FB4E580(pUnit, uVar5, ptParams[1]), iVar3 == 0))
			goto LAB_6fb440d4;
		bVar21 = uVar16 == 0;
	LAB_6fb42fbb:
		if (bVar21)
		{
			piVar18 = (int*)0x2;
		}
		else
		{
			piVar18 = (int*)0xf;
		}
		goto LAB_6fb44101;
	case 1:
	case 0x17:
		D2_ASSERT(ptParams != nullptr);
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 1);
		if ((((pUnit->dwUnitType != 1) || (pUnit->pPlayerData == nullptr)) ||
		        ((pUnit->pPlayerData->unk0x28 & 1) == 0)) &&
		    (iVar3 = sub_6FB4DF60(pUnit, *ptParams, ptParams[1]), iVar3 != 0))
		{
			bVar21 = uVar16 == 1;
			goto LAB_6fb42fbb;
		}
		goto LAB_6fb440d4;
	default:
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		goto LAB_6fb440d4;
	case 4:
	case 0xb:
	case 0xc:
	case 0xe:
	case 0x11:
	case 0x1a:
	case 0x1c:
		D2_ASSERT(ptParams != nullptr);
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		UNITS_SetTargetUnitForDynamicUnit(pUnit, nullptr);
		if ((*ptParams != 0) || (ptParams[1] != 0))
		{
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				uVar5 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				uVar5 = 0;
			}
			else
			{
				uVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			if (*ptParams == uVar5)
			{
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
				if (*(int32_t*)(ptParams + 1) == DVar6)
					goto LAB_6fb43268;
			}
			UNITS_UpdateDirectionAndSpeed(pUnit, *ptParams, ptParams[1]);
		}
	LAB_6fb43268:
		sub_6FB4F410(pUnit, *(int**)(byte_6FB70C00 + uVar16 * 8));
		if ((((*(int*)(byte_6FB70C04 + uVar16 * 8) != 0) &&
		         (uVar5 = *(uint32_t*)(byte_6FB70C00 + uVar16 * 8), (int)uVar5 < 0x10)) &&
		        (iVar3 = pUnit->dwClassId, -1 < iVar3)) &&
		    (((iVar20 = *(int*)((uint8_t*)&sgptDataTables), iVar3 < *(int*)(iVar20 + 0xa80) &&
		                                                        (iVar3 = (int)*(short*)(*(int*)(iVar20 + 0xa78) + 0x18 + iVar3 * 0x1a8), -1 < iVar3)) &&
		        ((iVar3 < *(int*)(iVar20 + 0xa98) &&
		            ((iVar3 = *(int*)(iVar20 + 0xa90) + iVar3 * 0x134, iVar3 != 0 &&
		                                                                   (((uint32_t) * (uint8_t*)(((int)uVar5 >> 3) + 0x104 + iVar3) &
		                                                                        *(uint32_t*)(((uint8_t*)&gdwBitMasks) + (uVar5 & 7) * 4)) != 0))))))))
		{
			sub_6FB4DF60(pUnit, *ptParams, ptParams[1]);
		}
		if (uStack_94 == 0x6e)
		{
			sub_6FB44460(uVar16, pUnit, (uint32_t)(ptParams));
		}
		break;
	case 5:
	case 10:
	case 0xd:
	case 0xf:
	case 0x10:
	case 0x1b:
	case 0x1d:
		D2_ASSERT(ptParams != nullptr);
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		uVar5 = *ptParams;
		if (uStack_94 == 0xe7)
			break;
		sub_6FB28F90(pUnit, uVar5, ptParams[1]);
		if ((uStack_94 == 0x130) && (uVar16 == 10))
		{
			pDVar4 = sub_6FB296A0((int)pUnit);
			sub_6FB29D10(pDVar4, 0xa9, 0);
		}
		sub_6FB29010(pUnit, 0);
		if (uStack_94 == 0x6e)
		{
			sub_6FB44460(uVar16, pUnit, (uint32_t)(ptParams));
		}
		else if ((uStack_94 == 0x9a) && (uVar16 == 0xd))
		{
			D2COMMON_10160_PathUpdateDirection(pUnit->pDynamicPath, 0x38);
		}
		if ((pUnit->dwClassId == 0x195) && (uVar16 == 0xd))
		{
			D2COMMON_10160_PathUpdateDirection(pUnit->pDynamicPath, 0x34);
		}
		if ((pUnit->dwClassId == 0x195) && (uVar16 == 0xf))
		{
			D2COMMON_10160_PathUpdateDirection(pUnit->pDynamicPath, 0x30);
		}
		if (uStack_94 == 0x9b)
		{
			if (uVar16 == 0xd)
			{
				pDVar22 = pUnit->pDynamicPath;
				bVar2 = 0x34;
			LAB_6fb430e6:
				D2COMMON_10160_PathUpdateDirection(pDVar22, bVar2);
			}
		}
		else if ((uStack_94 == 0xb2) && (uVar16 == 0xd))
		{
			pDVar22 = pUnit->pDynamicPath;
			bVar2 = 4;
			goto LAB_6fb430e6;
		}
		sub_6FB4F410(pUnit, *(int**)(byte_6FB70C00 + uVar16 * 8));
		if ((((*(int*)(byte_6FB70C04 + uVar16 * 8) != 0) &&
		         (uVar16 = *(uint32_t*)(byte_6FB70C00 + uVar16 * 8), (int)uVar16 < 0x10)) &&
		        (iVar3 = pUnit->dwClassId, -1 < iVar3)) &&
		    (((iVar20 = *(int*)((uint8_t*)&sgptDataTables), iVar3 < *(int*)(iVar20 + 0xa80) &&
		                                                        (iVar3 = (int)*(short*)(*(int*)(iVar20 + 0xa78) + 0x18 + iVar3 * 0x1a8), -1 < iVar3)) &&
		        ((iVar3 < *(int*)(iVar20 + 0xa98) &&
		            ((iVar3 = *(int*)(iVar20 + 0xa90) + iVar3 * 0x134, iVar3 != 0 &&
		                                                                   ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + (uVar16 & 7) * 4) &
		                                                                        (uint32_t) * (uint8_t*)(((int)uVar16 >> 3) + 0x104 + iVar3)) != 0))))))))
		{
			sub_6FB4E580(pUnit, uVar5, ptParams[1]);
		}
		break;
	case 6:
		if (ptParams != nullptr)
		{
			sub_6FB44A30((int*)pUnit, ptParams[2] & 0x80);
			uVar16 = ptParams[2] & 0x7f;
			ptParams[2] = uVar16;
			if (1 < uVar16)
			{
				ptParams[2] = uVar16 + 1;
			}
			bVar21 = true;
			if (ptParams[2] != 0)
			{
				iVar3 = STATLIST_UnitGetStatValue(pUnit, 6, 0);
				if (iVar3 >> 8 == ptParams[2])
				{
					bVar21 = false;
				}
				else
				{
					STATLIST_SetUnitStat(pUnit, 6, ptParams[2] << 8, 0);
				}
			}
			D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
			pUnit->dwLastHitClass = ptParams[6];
			PATH_RecacheRoomIfNeeded(local_88);
			sub_6FB4F410(pUnit, (int*)0x3);
			if (bVar21)
			{
				sub_6FB42A70(pUnit, 1, 0);
			}
			sub_6FB29A80((int)pUnit);
			sub_6FB46290(pUnit);
		}
		break;
	case 7:
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		if ((ptParams != nullptr) && (ptParams[2] != 0))
		{
			STATLIST_SetUnitStat(pUnit, 6, ptParams[2] << 8, 0);
		}
		uVar16 = pUnit->dwFlags;
		local_90 = uVar16 >> 9 & 1;
		if (local_90 == 0)
		{
			if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(piStack_8c + 1)) == 0)
			{
				uVar16 = uVar16 & 0xfffffffd;
			}
			else
			{
				uVar16 = uVar16 | 2;
			}
		}
		else
		{
			uVar16 = uVar16 | 2;
		}
		pUnit->dwFlags = uVar16;
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x18] & *(uint8_t*)((int)piStack_8c + 5)) == 0)
		{
			uVar16 = pUnit->dwFlags | 0x20;
		}
		else
		{
			uVar16 = pUnit->dwFlags & 0xffffffdf;
		}
		pUnit->dwFlags = uVar16;
		sub_6FB294B0((int*)pUnit);
		if (ptParams != nullptr)
		{
			sub_6FB4DF90(pUnit, D2C_ZEXT((short)*ptParams),
			    D2C_ZEXT((short)ptParams[1]), 0, 0, 0);
			uVar16 = pUnit->dwUnitType;
			if ((uVar16 == 2) || ((3 < (int)uVar16 && ((int)uVar16 < 6))))
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
			iVar3 = iVar3 - *ptParams;
			if (iVar3 < 0)
			{
				iVar3 = -iVar3;
			}
			if (iVar3 < 2)
			{
				uVar16 = pUnit->dwUnitType;
				if ((uVar16 == 2) || ((3 < (int)uVar16 && ((int)uVar16 < 6))))
				{
					DVar13 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar13 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar13 + 2)) = 0;
				}
				else
				{
					DVar13 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				iVar3 = (int)DVar13 - ptParams[1];
				if (iVar3 < 0)
				{
					iVar3 = -iVar3;
				}
				if (iVar3 < 2)
					goto LAB_6fb440d4;
			}
			if ((((((pUnit->dwUnitType != 1) || (pUnit->pPlayerData == nullptr)) ||
			          ((pUnit->pPlayerData->unk0x28 & 1) == 0)) &&
			         ((iVar3 = sub_6FB4DF60(pUnit, *ptParams, ptParams[1]), iVar3 != 0 &&
			                                                                    (iVar3 = STATES_CheckState(pUnit, 0x8f), iVar3 == 0)))) &&
			        (iVar3 = pUnit->dwClassId, -1 < iVar3)) &&
			    (((iVar20 = *(int*)((uint8_t*)&sgptDataTables), iVar3 < *(int*)(iVar20 + 0xa80) &&
			                                                        (iVar3 = (int)*(short*)(*(int*)(iVar20 + 0xa78) + 0x18 + iVar3 * 0x1a8), -1 < iVar3)) &&
			        ((iVar3 < *(int*)(iVar20 + 0xa98) &&
			            ((iVar3 = *(int*)(iVar20 + 0xa90) + iVar3 * 0x134, iVar3 != 0 &&
			                                                                   (local_90 = (uint32_t) * (uint8_t*)(iVar3 + 0xf0) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 8),
			                                                                       local_90 != 0))))))))
			{
				piVar18 = (int*)0x2;
				goto LAB_6fb44101;
			}
		}
	LAB_6fb440d4:
		if (((pUnit->dwUnitType != 1) || (uVar16 = pUnit->dwAnimMode, 0xf < uVar16)) ||
		    ((uVar16 == 0 || (uVar16 == 0xc))))
			break;
		sub_6FB29010(pUnit, 0);
		sub_6FB4DF50((int)pUnit);
		piVar18 = (int*)0x1;
		goto LAB_6fb44101;
	case 8:
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		pUnit->dwLastHitClass = ptParams[6];
		pDVar4 = sub_6FAB5A20();
		if (pDVar4 == pUnit)
		{
			uVar16 = sub_6FAA8B90();
			if (((uVar16 & 8) == 0) && (uVar16 = sub_6FAA8BA0(), (uVar16 & 8) == 0))
			{
				sub_6FAB5D40();
			}
			else
			{
				sub_6FAABF30();
				sub_6FAB5A90(nullptr);
			}
		}
		STATLIST_SetUnitStat(pUnit, 6, 0, 0);
		iVar3 = STATES_CheckStateMaskHideOnUnit(pUnit);
		if (iVar3 != 0)
		{
			pUnit->dwFlagEx = pUnit->dwFlagEx | 0x40000;
			pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd | 0x20;
		}
		iVar3 = STATES_CheckStateMaskShatterOnUnit(pUnit);
		if (iVar3 != 0)
		{
			if (pUnit->dwUnitType == 1)
			{
				iVar3 = pUnit->dwClassId;
				if (((iVar3 < 0) ||
				        (iVar20 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar20 + 0xa80) <= iVar3)) ||
				    ((iVar3 = (int)*(short*)(*(int*)(iVar20 + 0xa78) + 0x18 + iVar3 * 0x1a8), iVar3 < 0 ||
				                                                                                  (*(int*)(iVar20 + 0xa98) <= iVar3))))
				{
					iVar3 = 0;
				}
				else
				{
					iVar3 = *(int*)(iVar20 + 0xa90) + iVar3 * 0x134;
				}
				bVar2 = *(uint8_t*)(iVar3 + 0xb);
				puVar19 = &uStack_5c;
				for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*puVar19 = 0;
					puVar19 = puVar19 + 1;
				}
				uStack_5c = 0x2020;
				uStack_2c = 1;
				pDStack_58 = pUnit;
				pDStack_54 = pUnit;
				iStack_4c = bVar2 + 0x10f;
				sub_6FB3E070(&uStack_5c);
				iStack_4c = 0x113;
				sub_6FB3E070(&uStack_5c);
			}
			pUnit->dwLastHitClass = (uint32_t)((uint8_t)pUnit->dwLastHitClass & 0xf | 0xa0);
		}
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)((int)piStack_8c + 6)) == 0)
		{
			PATH_SetUnitDeadCollision(pUnit, 0);
		}
		uVar16 = pUnit->dwClassId;
		if ((int)uVar16 < 0)
		{
			return;
		}
		iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80);
		if (iVar3 <= (int)uVar16)
		{
			return;
		}
		iVar20 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + uVar16 * 0x1a8;
		if (iVar20 == 0)
		{
			return;
		}
		if (((*(char*)(iVar20 + 0x1a4) == '\x01') && (-1 < *(short*)(iVar20 + 0x26))) &&
		    (*(short*)(iVar20 + 0x26) < iVar3))
		{
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
			}
			else
			{
				DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				fVar8 = (float)pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				fVar8 = 0.0;
			}
			else
			{
				fVar8 = (float)PATH_GetXPosition(pUnit->pDynamicPath);
			}
			pDVar4 = sub_6FB27D50(uVar16, fVar8, (int)DVar7, 1, 0);
			if (pDVar4 != nullptr)
			{
				pDVar4->dwFlags = pDVar4->dwFlags & 0xfffffffd;
			}
			pDVar4->dwLastHitClass = pUnit->dwLastHitClass;
			sub_6FB4F410(pDVar4, nullptr);
			sub_6FB41900(pUnit, (D2DynamicPathStrc*)(int)*(short*)(iVar20 + 0x26));
		}
		pDVar22 = local_88;
		if ((int)uStack_94 < 0x165)
		{
			if (uStack_94 == 0x164)
			{
				sub_6FABABC0(pUnit, 0x148, 0, 1);
				goto switchD_6fb437ef_caseD_6f;
			}
			switch (uStack_94)
			{
			case 0x6e:
				sub_6FB29D10(pUnit, 0x92, 0);
				sub_6FB4F410(pUnit, nullptr);
				iVar3 = sub_6FB5FBE0((int)pUnit);
				if (iVar3 != 0)
				{
					sub_6FB60130((int)pUnit);
					sub_6FB60180((int)pUnit, 0);
					sub_6FB5FCB0((int)pUnit, 0, 0, -0x10, 1);
					sub_6FB5FD50((int)pUnit, 0, 0, 0, 0);
				}
				goto LAB_6fb43b86;
			default:
				goto switchD_6fb437ef_caseD_6f;
			case 0x76:
				iVar3 = 0xb8;
				break;
			case 0x7f:
				iVar3 = 0x4f;
				break;
			case 0xbe:
				piVar18 = nullptr;
				if (pUnit->dwAnimMode == 0xe)
				{
					sub_6FB4F460(pUnit, 0);
					pUnit->nSeqCurrentFramePrecise = 0xe00;
					goto LAB_6fb43b86;
				}
				goto LAB_6fb43b81;
			case 0xd4:
				sub_6FB29D10(pUnit, 0xbc, 0);
				iVar3 = 0xbd;
				break;
			case 0xee:
				iVar3 = 0x4e;
				break;
			case 0xf7:
				iVar3 = 0x52;
				break;
			case 0x102:
			case 0x105:
				iVar3 = 0x9d;
				break;
			case 0x11c:
				puVar19 = auStack_7c;
				for (iVar3 = 7; puVar19 = puVar19 + 1, iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*puVar19 = 0;
				}
				auStack_7c[1] = 0xd8;
				uStack_68 = 1;
				sub_6FB42D40(0x15, pUnit, auStack_7c + 1);
				goto LAB_6fb43b86;
			case 0x136:
			case 0x137:
			case 0x138:
				iVar3 = 0xbb;
				break;
			case 0x15f:
			case 0x160:
			case 0x161:
				sub_6FB5BF70((int)pUnit);
				iVar3 = pUnit->dwClassId + -0xad;
			}
			goto LAB_6fb43b74;
		}
		switch (uStack_94)
		{
		case 0x168:
		case 0x22e:
			iVar3 = 0xb9;
			goto LAB_6fb43b74;
		case 0x1a1:
		case 0x1a2:
			iVar3 = 0x10f;
			goto LAB_6fb43b74;
		case 0x1a9:
		case 0x1aa:
		case 0x1ab:
			uVar16 = pUnit->dwUnitType;
			if ((uVar16 == 2) || ((3 < (int)uVar16 && ((int)uVar16 < 6))))
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
			uVar16 = pUnit->dwUnitType;
			if ((uVar16 == 2) || ((3 < (int)uVar16 && ((int)uVar16 < 6))))
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
			sub_6FB3EAF0((int)pUnit, 0x1d6, iVar3, (D2UnitStrc**)DVar9, 0, 1);
			sub_6FB4F410(pUnit, nullptr);
			sub_6FB55820(0x316, pUnit, 0.0, 0.0, 0);
			goto LAB_6fb43b86;
		case 0x1b9:
			bVar2 = PATH_GetDirection(local_88);
			D2COMMON_10160_PathUpdateDirection(pDVar22, bVar2 + 0x20 & 0x3f);
			break;
		case 0x1c5:
			bVar2 = UNITS_GetDirection(pUnit);
			local_90 = CONCAT31((*(uint8_t*)((uint8_t*)&local_90 + 1)), bVar2);
			bVar2 = D2Common_11053(bVar2);
			switch (bVar2 & 3)
			{
			case 0:
				sub_6FB55820(0x51c, pUnit, 0.0, 0.0, 0);
				break;
			case 1:
				sub_6FB55820(0x51f, pUnit, 0.0, 0.0, 0);
				break;
			case 2:
				sub_6FB55820(0x522, pUnit, 0.0, 0.0, 0);
				break;
			case 3:
				sub_6FB55820(0x525, pUnit, 0.0, 0.0, 0);
			}
			break;
		case 0x1cd:
			sub_6FB29D10(pUnit, 0xcc, 0);
			sub_6FB55820(0x973, pUnit, 0.0, 0.0, 0);
			break;
		case 0x1d5:
		case 0x1da:
			iVar3 = 0xe5;
			goto LAB_6fb43b74;
		case 0x1f1:
			iVar3 = pUnit->dwClassId;
			if (iVar3 != 0x1f1)
			{
				if (iVar3 == 0x1f2)
				{
					iVar3 = 0xe2;
					goto LAB_6fb43b74;
				}
				if (iVar3 != 499)
					break;
			}
			iVar3 = 0xe1;
		LAB_6fb43b74:
			sub_6FB29D10(pUnit, iVar3, 0);
			break;
		case 0x22f:
			goto switchD_6fb43935_caseD_22f;
		case 0x23a:
			uVar16 = pUnit->dwUnitType;
			if ((uVar16 == 2) || ((3 < (int)uVar16 && ((int)uVar16 < 6))))
			{
				DVar10 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar10 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar10 + 2)) = 0;
			}
			else
			{
				DVar10 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar16 = pUnit->dwUnitType;
			if ((uVar16 == 2) || ((3 < (int)uVar16 && ((int)uVar16 < 6))))
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
			sub_6FB3EAF0((int)pUnit, 0x266, iVar3, (D2UnitStrc**)DVar10, 0, 1);
			goto switchD_6fb43935_caseD_22f;
		}
	switchD_6fb437ef_caseD_6f:
		piVar18 = nullptr;
	LAB_6fb43b81:
		sub_6FB4F410(pUnit, piVar18);
	LAB_6fb43b86:
		pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
		sub_6FB296E0((int)pUnit);
		break;
	case 9:
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		pDVar4 = CUNIT_GetPlayer();
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)((int)piStack_8c + 6)) == 0)
		{
			PATH_SetUnitDeadCollision(pUnit, 0);
		}
		STATLIST_SetUnitStat(pUnit, 6, 0, 0);
		pDVar11 = sub_6FB296A0((int)pDVar4);
		if (pDVar11 == pUnit)
		{
			UNITS_SetTargetUnitForDynamicUnit(pDVar4, nullptr);
		}
		uVar16 = uStack_94;
		if ((uStack_94 == 0x11c) && (pUnit->dwAnimMode == 0xe))
		{
			pDVar14 = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 0xd8);
			UNITS_SetUsedSkill(pUnit, pDVar14);
		}
		else
		{
			sub_6FB4F410(pUnit, (int*)((uint8_t*)0x0c));
			sub_6FB29540((int)pUnit);
		}
		if ((((pUnit->dwClassId != 0xd3) && (uVar16 != 0x1f1)) && (uVar16 != 0x1a1)) &&
		    (uVar16 != 0x1a2))
		{
			sub_6FB5BF70((int)pUnit);
		}
		if (uVar16 == 0x1b3)
		{
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				DVar12 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar12 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar12 + 2)) = 0;
			}
			else
			{
				DVar12 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar5 = pUnit->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
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
			pDVar4 = sub_6FB3EAF0((int)pUnit, 0x1a8, iVar3, (D2UnitStrc**)DVar12, 0, 1);
			sub_6FB29540((int)pDVar4);
		}
		if (((uVar16 == 0x158) || (uVar16 == 0x22f)) || (uVar16 == 0x23a))
		{
			pUnit->dwFlagEx = pUnit->dwFlagEx | 0x40000;
		}
		pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd | 0x20;
		iVar3 = STATES_CheckStateMaskHideOnUnit(pUnit);
		if (iVar3 != 0)
		{
			pUnit->dwFlagEx = pUnit->dwFlagEx | 0x40000;
			pUnit->dwFlags = pUnit->dwFlags & 0xfffffffb | 0x20;
		}
		sub_6FB296E0((int)pUnit);
		break;
	case 0x12:
		D2_ASSERT(ptParams != nullptr);
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		PATH_RecacheRoomIfNeeded(local_88);
		sub_6FB28F90(pUnit, *ptParams, ptParams[1]);
		sub_6FB29010(pUnit, 0);
		piVar18 = (int*)0x6;
		goto LAB_6fb44101;
	case 0x13:
		D2_ASSERT(ptParams != nullptr);
		sub_6FB44A30((int*)pUnit, ptParams[1] & 0x80);
		uVar16 = ptParams[1] & 0x7f;
		ptParams[1] = uVar16;
		if (1 < uVar16)
		{
			ptParams[1] = uVar16 + 1;
		}
		if (ptParams[1] != 0)
		{
			STATLIST_SetUnitStat(pUnit, 6, ptParams[1] << 8, 0);
		}
		pUnit->dwLastHitClass = *ptParams;
		sub_6FB42A70(pUnit, 1, 1);
		sub_6FB29A80((int)pUnit);
		sub_6FB4F240(pUnit, 0xd);
		sub_6FB50D20(pUnit, (int*)0xd, 1);
		sub_6FB46290(pUnit);
		break;
	case 0x14:
		D2_ASSERT(ptParams != nullptr);
		if (ptParams[5] != 0)
		{
			STATLIST_SetUnitStat(pUnit, 6, ptParams[5] << 8, 0);
		}
		pUnit->dwLastHitClass = ptParams[6];
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		pDVar22 = local_88;
		PATH_RecacheRoomIfNeeded(local_88);
		PATH_SetType(pDVar22, 0xb);
		D2COMMON_10190_PATH_SetDistance(pDVar22, (uint8_t)ptParams[2]);
		D2COMMON_10170_PathSetTargetPos(pDVar22, (uint32_t)(uint16_t)*ptParams, (uint32_t)(uint16_t)ptParams[1]);
		D2Common_10142(pDVar22, pUnit, 0);
		piVar18 = (int*)0xd;
	LAB_6fb44101:
		sub_6FB4F410(pUnit, piVar18);
		break;
	case 0x15:
		D2_ASSERT(ptParams != nullptr);
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		UNITS_SetTargetUnitForDynamicUnit(pUnit, nullptr);
		uVar16 = *ptParams;
		SKILLS_AssignSkill(pUnit, uVar16, ptParams[4], 0, __FILE__, __LINE__);
		pDVar14 = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, uVar16);
		UNITS_SetUsedSkill(pUnit, pDVar14);
		piStack_8c = (int*)SKILLS_GetSkillModeFromUnit(pUnit, pDVar14);
		if (piStack_8c == (int*)0xe)
		{
			pDVar15 = DATATBLS_GetMonSeqTxtRecordFromUnit(pUnit);
			iVar3 = DATATBLS_GetSeqFramePointsCount(pUnit);
			iVar20 = 0;
			if (0 < iVar3 >> 8)
			{
				do
				{
					DATATBLS_ComputeSequenceAnimation(pDVar15, iVar20 << 8, iVar20 << 8, &local_90, &uStack_94, &iStack_80,
					    (int*)auStack_7c);
					pUnit->dwAnimMode = local_90;
					sub_6FB5C080(pUnit);
					iVar20 = iVar20 + 1;
				} while (iVar20 < iVar3 >> 8);
			}
		}
		ptParams[1] = 0xffffffff;
		sub_6FB4F410(pUnit, piStack_8c);
		sub_6FABD400(pUnit, (int*)ptParams);
		break;
	case 0x16:
		D2_ASSERT(ptParams != nullptr);
		D2COMMON_10212_PATH_SetMoveFlags(pUnit, 0);
		uVar16 = *ptParams;
		SKILLS_AssignSkill(pUnit, uVar16, ptParams[4], 0, __FILE__, __LINE__);
		pDVar14 = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, uVar16);
		UNITS_SetUsedSkill(pUnit, pDVar14);
		piStack_8c = (int*)SKILLS_GetSkillModeFromUnit(pUnit, pDVar14);
		if (piStack_8c == (int*)0xe)
		{
			pDVar15 = DATATBLS_GetMonSeqTxtRecordFromUnit(pUnit);
			iVar3 = DATATBLS_GetSeqFramePointsCount(pUnit);
			iVar20 = 0;
			if (0 < iVar3 >> 8)
			{
				do
				{
					DATATBLS_ComputeSequenceAnimation(pDVar15, iVar20 << 8, iVar20 << 8, &local_90, auStack_7c, &iStack_80,
					    (int*)&uStack_94);
					pUnit->dwAnimMode = local_90;
					sub_6FB5C080(pUnit);
					iVar20 = iVar20 + 1;
				} while (iVar20 < iVar3 >> 8);
			}
		}
		ptParams[1] = 0xffffffff;
		sub_6FB4F410(pUnit, piStack_8c);
		sub_6FABD2A0(pUnit, ptParams);
	}
	if ((((iStack_84 != 0) && (ptParams != nullptr)) && (ptParams[4] != 0)) &&
	    (uVar16 = STATLIST_UnitGetStatValue(pUnit, 0x43, 0), uVar16 != ptParams[4]))
	{
		STATLIST_DeactivateTemporaryStates(pUnit);
		STATLIST_AddUnitStat(pUnit, 0x43, ptParams[4] - uVar16, 0);
		UNITS_UpdateAnimRateAndVelocity(pUnit, __FILE__, __LINE__);
	}
	sub_6FB46270(pUnit);
	if (((pUnit->dwUnitType == 1) && (pUnit->pPlayerData != nullptr)) &&
	    ((pUnit->pPlayerData->unk0x28 & 1) != 0))
	{
		uVar16 = pUnit->dwAnimMode;
		if (((uVar16 != 1) && (uVar16 < 0x10)) && ((uVar16 != 0 && (uVar16 != 0xc))))
		{
			sub_6FB29010(pUnit, 0);
			sub_6FB4DF50((int)pUnit);
			sub_6FB4F410(pUnit, (int*)0x1);
		}
		if (local_88 != nullptr)
		{
			D2Common_10153(local_88);
		}
	}
	return;
switchD_6fb43935_caseD_22f:
	pUnit->dwFlagEx = pUnit->dwFlagEx | 0x40000;
	pUnit->dwFlags = pUnit->dwFlags | 0x20;
	piVar18 = (int*)((uint8_t*)0x0c);
	goto LAB_6fb43b81;
}

//D2Client.0x6FB44460
void __fastcall sub_6FB44460(int a1, D2UnitStrc* pUnit, uint32_t a3)
{
	uint32_t uVar1;
	int32_t nY;
	int iVar2;
	D2ActiveRoomStrc* pDVar3;
	int32_t nY_00;
	int32_t nY_01;
	D2UnitStrc** nY_02;
	uint16_t uVar4;

	if (a1 == 0xc)
	{
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
		uVar4 = 0x1000;
		pDVar3 = UNITS_GetRoom(pUnit);
		COLLISION_ResetMask(pDVar3, iVar2, (int)nY, uVar4);
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nY_00 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY_00 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY_00 + 2)) = 0;
		}
		else
		{
			nY_00 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
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
		uVar4 = 0x100;
		pDVar3 = UNITS_GetRoom(pUnit);
		COLLISION_ResetMask(pDVar3, iVar2, (int)nY_00, uVar4);
		PATH_SetUnitCollisionPattern(pUnit, 5);
		PATH_SetMoveTestCollisionMask(pUnit->pDynamicPath, 0);
		iVar2 = sub_6FB5FBE0((int)pUnit);
		if (iVar2 == 0)
		{
			sub_6FB5FB10((int)pUnit);
			sub_6FB60130((int)pUnit);
			sub_6FB60180((int)pUnit, 1);
			sub_6FB5FCB0((int)pUnit, 0, 0, 2, 1);
			sub_6FB5FD50((int)pUnit, 0, 0, 0xa0, 0);
			return;
		}
	}
	else if ((a1 == 0xe) || (a1 == 10))
	{
		if (pUnit != nullptr)
		{
			pUnit->dwFlags = pUnit->dwFlags | 0xe;
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nY_01 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY_01 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY_01 + 2)) = 0;
		}
		else
		{
			nY_01 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
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
		uVar4 = 0x1000;
		pDVar3 = UNITS_GetRoom(pUnit);
		COLLISION_SetMask(pDVar3, iVar2, (int)nY_01, uVar4);
		uVar4 = 0x100;
		nY_02 = sub_6FAB6A90((int*)pUnit);
		iVar2 = sub_6FAB6A60((int*)pUnit);
		pDVar3 = UNITS_GetRoom(pUnit);
		COLLISION_SetMask(pDVar3, iVar2, (int)nY_02, uVar4);
		PATH_SetUnitCollisionPattern(pUnit, 1);
		PATH_SetMoveTestCollisionMask(pUnit->pDynamicPath, 0x3c01);
		iVar2 = sub_6FB5FBE0((int)pUnit);
		if (iVar2 != 0)
		{
			sub_6FB60130((int)pUnit);
			sub_6FB60180((int)pUnit, 0);
			sub_6FB5FCB0((int)pUnit, 0, 0, -8, 1);
			sub_6FB5FD50((int)pUnit, 0, 0, 0, 0);
		}
	}
}

//D2Client.0x6FB446B0
void __fastcall sub_6FB446B0(D2UnitStrc* pUnit, uint16_t* a2)
{
	uint8_t bVar1;
	int iVar2;
	int iVar3;
	D2UnitStrc* pMonster;
	int iVar5;
	D2HirelingTxt* pDVar6;
	D2SkillStrc* pSkill;
	Unicode* wszName;
	short index;
	uint16_t nNameId;
	D2HirelingInitStrc* pHirelingInit;
	uint32_t* puStack_48;
	int iStack_44;
	D2HirelingInitStrc DStack_3c;
	uint32_t uVar4;

	if ((pUnit != nullptr) && (a2 != nullptr))
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x202;
		nNameId = *a2;
		iVar2 = sub_6FAAC080();
		iVar3 = MONSTERS_GetActFromHirelingTxt(iVar2, 0, nNameId);
		bVar1 = sub_6FAAC090();
		uVar4 = (uint32_t)bVar1;
		iVar2 = *(int*)(a2 + 2);
		pHirelingInit = &DStack_3c;
		pMonster = CUNIT_GetPlayer();
		iVar5 = sub_6FAAC080();
		iVar2 = MONSTERS_HirelingInit(iVar5, pMonster, iVar2, iVar3, uVar4, pHirelingInit);
		if (iVar2 != 0)
		{
			iVar2 = DStack_3c.nLevel;
			iVar3 = sub_6FAAC080();
			pDVar6 = DATATBLS_GetHirelingTxtRecordFromIdAndLevel(iVar3, DStack_3c.nId, iVar2);
			if (pDVar6 != nullptr)
			{
				iStack_44 = DStack_3c.nLevel - pDVar6->nHirelingLevel;
				if (iStack_44 < 0)
				{
					iStack_44 = 0;
				}
				puStack_48 = pDVar6->dwSkill;
				iVar2 = 0;
				do
				{
					uVar4 = *puStack_48;
					if (((int)uVar4 < 1) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= (int)uVar4))
						break;
					iVar3 = ((char)pDVar6->nSLvlPerLvl[iVar2] * iStack_44 >> 5) +
					        (int)(char)pDVar6->nLevel[iVar2];
					if (0x1f < iVar3)
					{
						iVar3 = 0x20;
					}
					iVar5 = (int)(char)pDVar6->nMode[iVar2];
					SKILLS_AssignSkill(pUnit, uVar4, iVar3, 0, __FILE__, __LINE__);
					pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, uVar4);
					SKILLS_SetSkillMode(pSkill, iVar5);
					iVar2 = iVar2 + 1;
					puStack_48 = puStack_48 + 1;
				} while (iVar2 < 6);
				index = *a2;
				if (index == 0x421)
				{
					index = 0x2b0d;
				}
				wszName = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
				MONSTERS_SetMonsterNameInMonsterData(pUnit, wszName);
				sub_6FB2B360(pUnit);
			}
		}
	}
}

//D2Client.0x6FB44820
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB44820(int* a1)
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	uint32_t extraout_var_00;

	if (a1 == nullptr)
	{
		return 0;
	}
	if (*a1 != 1)
	{
		return 0;
	}
	iVar2 = UNITS_CanSwitchAI(a1[1]);
	if (iVar2 == 0)
	{
		return 0;
	}
	if (*a1 == 1)
	{
		bVar1 = sub_6FB449D0(a1, 8);
		if (D2C_ZEXT(bVar1) != 0)
		{
			return 0;
		}
		if (*a1 == 1)
		{
			bVar1 = sub_6FB449D0(a1, 2);
			if (D2C_ZEXT(bVar1) != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

//D2Client.0x6FB44880
void __fastcall sub_6FB44880(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 1), 1);
	if (pDVar1 != nullptr)
	{
		if (*(uint16_t*)(a1 + 5) == 0xffff)
		{
			uVar2 = 0xffffffff;
		}
		else
		{
			uVar2 = (uint32_t) * (uint16_t*)(a1 + 5);
		}
		if ((pDVar1->dwUnitType == 1) && (pDVar1->pPlayerData != nullptr))
		{
			pDVar1->pPlayerData->unk0x3C[1] = uVar2;
		}
	}
}

//D2Client.0x6FB448C0
bool __fastcall sub_6FB448C0(int a1, uint32_t a2)
{
	if (a1 == 0)
	{
		return false;
	}
	return (*(uint32_t*)(a1 + 0xc4) & a2) != 0;
}

//D2Client.0x6FB448E0
void __fastcall sub_6FB448E0(int a1, uint32_t a2, int a3)
{
	if (a1 != 0)
	{
		if (a3 != 0)
		{
			*(uint32_t*)(a1 + 200) = *(uint32_t*)(a1 + 200) | a2;
			return;
		}
		*(uint32_t*)(a1 + 200) = *(uint32_t*)(a1 + 200) & ~a2;
	}
}

//D2Client.0x6FB44910
int __fastcall sub_6FB44910(int a1)
{
	int iVar1;

	if (((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + a1 * 0x1a8, iVar1 != 0))
	{
		a1 = (int)*(short*)(iVar1 + 2);
	}
	return a1;
}

//D2Client.0x6FB44950
int __fastcall sub_6FB44950(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		return a1[5] + 0x1c;
	}
	return 0;
}

//D2Client.0x6FB44970
void __fastcall sub_6FB44970(int* a1, uint16_t a2)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		*(uint16_t*)(a1[5] + 0x14) = a2;
	}
}

//D2Client.0x6FB44990
void __fastcall sub_6FB44990(int* a1, uint16_t a2)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		*(uint16_t*)(a1[5] + 0x26) = a2;
	}
}

//D2Client.0x6FB449B0
uint16_t __fastcall sub_6FB449B0(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		return *(uint16_t*)(a1[5] + 0x26);
	}
	return 0;
}

//D2Client.0x6FB449D0
bool __fastcall sub_6FB449D0(int* a1, uint16_t a2)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		return (*(uint16_t*)(a1[5] + 0x16) & a2) != 0;
	}
	return false;
}

//D2Client.0x6FB44A00
void __fastcall sub_6FB44A00(int* a1, uint16_t a2, int a3)
{
	int iVar1;

	if (((a1 != nullptr) && (*a1 == 1)) && (iVar1 = a1[5], iVar1 != 0))
	{
		if (a3 != 0)
		{
			*(uint16_t*)(iVar1 + 0x16) = *(uint16_t*)(iVar1 + 0x16) | a2;
			return;
		}
		*(uint16_t*)(iVar1 + 0x16) = *(uint16_t*)(iVar1 + 0x16) & ~a2;
	}
}

//D2Client.0x6FB44A30
void __fastcall sub_6FB44A30(int* a1, int a2)
{
	int iVar1;

	if (((a1 != nullptr) && (*a1 == 1)) && (iVar1 = a1[5], iVar1 != 0))
	{
		if (a2 != 0)
		{
			*(uint8_t*)(iVar1 + 0x17) = *(uint8_t*)(iVar1 + 0x17) | 1;
			return;
		}
		*(uint8_t*)(iVar1 + 0x17) = *(uint8_t*)(iVar1 + 0x17) & 0xfe;
	}
}

//D2Client.0x6FB44A50
void __cdecl sub_6FB44A50()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&byte_6FBBC230;
	iVar1 = 2;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FB44A70
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB44A70(D2UnitStrc* pUnit, int a2, int a3)
{
	D2SeedStrc* pSeed;
	char cVar1;
	D2PlayerDataStrc* pDVar2;
	uint64_t DVar3;
	bool bVar4;
	short sVar5;
	D2SuperUniquesTxt* pDVar6;
	uint32_t extraout_var;
	Unicode* pUVar7;
	Unicode* pUVar8;
	Unicode* pUVar9;
	uint16_t index;
	int iVar10;
	int iVar11;
	uint32_t nLowSeed;
	uint16_t uVar12;
	char acStack_260[8];
	Unicode local_258[300];

	if (a3 == 0)
	{
		return;
	}
	iVar10 = 0;
	do
	{
		cVar1 = *(char*)((int)&word_6FB7847C + iVar10);
		acStack_260[iVar10] = cVar1;
		iVar10 = iVar10 + 1;
	} while (cVar1 != '\0');
	Unicode::toUnicode((Unicode*)&byte_6FBBC230, acStack_260, 2);
	pSeed = &pUnit->pSeed;
	if (((pUnit == nullptr) || (pUnit->dwUnitType != 1)) ||
	    (pUnit->pPlayerData == nullptr))
	{
		nLowSeed = 0;
	}
	else
	{
		nLowSeed = (uint32_t) * (uint16_t*)(pUnit->pPlayerData->pQuestData + 1);
	}
	if (pUnit == nullptr)
	{
		iVar10 = -1;
	}
	else
	{
		if (((pUnit->dwUnitType == 1) &&
		        (pDVar2 = pUnit->pPlayerData, pDVar2 != nullptr)) &&
		    ((*(uint8_t*)((int)pDVar2->pQuestData + 6) & 2) != 0))
		{
			if (pDVar2 == nullptr)
			{
				sVar5 = 0;
			}
			else
			{
				sVar5 = *(short*)((int)pDVar2->pWaypointData + 10);
			}
			pDVar6 = DATATBLS_GetSuperUniquesTxtRecord((int)sVar5);
			if (pDVar6 == nullptr)
			{
				return;
			}
			index = pDVar6->wNameStr;
			if (index == 0)
			{
				index = 0x1506;
			}
			goto LAB_6fb44d03;
		}
		iVar10 = pUnit->dwClassId;
	}
	bVar4 = sub_6FB40CC0((int*)pUnit);
	if (D2C_ZEXT(bVar4) != 0)
	{
		iVar11 = 0;
		do
		{
			if ((&dword_6FB70CF0)[iVar11 * 2] == a2)
				break;
			iVar11 = iVar11 + 1;
		} while (iVar11 < 4);
		if ((iVar10 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar10))
		{
			iVar10 = 0;
		}
		else
		{
			iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar10 * 0x1a8;
		}
		uVar12 = 0;
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar10 + 6)));
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(dword_6FB70CF4 + iVar11 * 8)));
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b40));
		sub_6FADCFE0(local_258, (char*)pUVar8, pUVar7, pUVar9, uVar12);
		MONSTERS_SetMonsterNameInMonsterData(pUnit, local_258);
		return;
	}
	SEED_InitLowSeed(pSeed, nLowSeed);
	if (a2 == 0xc)
	{
		index = 0xc27;
		goto LAB_6fb44d03;
	}
	if (iVar10 < 0xf4)
	{
		if (iVar10 != 0xf3)
		{
			if (iVar10 == 0x9c)
			{
				index = 0xbcd;
			}
			else if (iVar10 == 0xd3)
			{
				index = 0xbee;
			}
			else
			{
				if (iVar10 != 0xf2)
					goto LAB_6fb44c58;
				index = 0xbf6;
			}
			goto LAB_6fb44d03;
		}
	}
	else
	{
		if (iVar10 == 0x100)
		{
			index = 0x3f6;
			goto LAB_6fb44d03;
		}
		if (iVar10 != 0x14d)
		{
			if (iVar10 != 0x220)
			{
			LAB_6fb44c58:
				uVar12 = 0;
				pUVar9 = (Unicode*)(DATATBLS_RollRandomUniqueSuffixString(pUnit));
				pUVar7 = (Unicode*)(DATATBLS_RollRandomUniquePrefixString(pUnit));
				pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x6b9));
				sub_6FADCFE0(local_258, (char*)pUVar8, pUVar7, pUVar9, uVar12);
				DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pSeed = DVar3;
				if ((uint32_t)(((uint64_t)DVar3 & 0xffffffff) % 100) < 0x32)
				{
					pUVar9 = (Unicode*)(DATATBLS_RollRandomUniqueAppellationString(pUnit));
					uVar12 = SUB42(pUVar9, 0);
					pUVar9 = (Unicode*)(DATATBLS_RollRandomUniqueSuffixString(pUnit));
					pUVar7 = (Unicode*)(DATATBLS_RollRandomUniquePrefixString(pUnit));
					pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x6ba));
					sub_6FADCFE0(local_258, (char*)pUVar8, pUVar7, pUVar9, uVar12);
				}
				MONSTERS_SetMonsterNameInMonsterData(pUnit, local_258);
				return;
			}
			index = 0xbf5;
			goto LAB_6fb44d03;
		}
	}
	index = 0xbf4;
LAB_6fb44d03:
	pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	MONSTERS_SetMonsterNameInMonsterData(pUnit, pUVar9);
}

//D2Client.0x6FB44D20
void __fastcall sub_6FB44D20(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	uint64_t DVar2;
	uint64_t DVar3;
	uint64_t uVar4;
	uint32_t* puVar5;
	int iVar6;
	uint32_t uVar7;

	if ((a3 != 0) && (sub_6FB296E0((int)pUnit), pUnit != nullptr))
	{
		if ((pUnit->dwUnitType == 1) &&
		    ((pUnit->pPlayerData != nullptr &&
		        ((*(uint8_t*)((int)pUnit->pPlayerData->pQuestData + 6) & 4) != 0))))
		{
			DVar3 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			uVar4 = ((uint64_t)DVar3 & 0xffffffff) * 0x6ac690c5 + ((uint64_t)DVar3 >> 0x20);
			(*(uint64_t*)&pUnit->pSeed) = DVar3;
			(pUnit->pSeed).nLowSeed = (uint32_t)uVar4;
			DVar2 = (uint64_t)((uVar4 & 0xffffffff) * 0x6ac690c5 + (uVar4 >> 0x20));
			(*(uint64_t*)&pUnit->pSeed) = DVar2;
			puVar5 = sub_6FAA4280(pUnit, 0, 7, 0xff, (*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 0xff, (uint32_t)uVar4 & 0xff,
			    (*(uint32_t*)((uint8_t*)&DVar3 + 0)) & 0xff);
		}
		else
		{
			iVar6 = pUnit->dwClassId;
			if (iVar6 < 0)
			{
				return;
			}
			iVar1 = *(int*)((uint8_t*)&sgptDataTables);
			if (*(int*)(iVar1 + 0xa80) <= iVar6)
			{
				return;
			}
			iVar6 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + iVar6 * 0x1a8);
			if (iVar6 < 0)
			{
				return;
			}
			if (*(int*)(iVar1 + 0xa98) <= iVar6)
			{
				return;
			}
			iVar6 = *(int*)(iVar1 + 0xa90) + iVar6 * 0x134;
			if (iVar6 == 0)
			{
				return;
			}
			uVar7 = (uint32_t)((uint32_t)iVar1 >> 8);
			puVar5 = sub_6FAA4280(pUnit, 0, 7, 0xff, CONCAT31(uVar7, *(uint8_t*)(iVar6 + 0x11f)),
			    CONCAT31((int32_t)((uint32_t) * (int*)(iVar1 + 0xa90) >> 8),
			        *(uint8_t*)(iVar6 + 0x120)),
			    CONCAT31(uVar7, *(uint8_t*)(iVar6 + 0x121)));
		}
		pUnit->dwInteractGUID = (uint32_t)puVar5;
		iVar6 = sub_6FAA4460((int)puVar5);
		sub_6FB29AB0((int)pUnit, iVar6);
	}
}

//D2Client.0x6FB44E50
void __fastcall sub_6FB44E50(int* a1, uint32_t a2, uint32_t a3)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		*(uint32_t*)(a1[5] + 0x18) = 0;
	}
}
