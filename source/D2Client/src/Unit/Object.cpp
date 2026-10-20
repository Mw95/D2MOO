#include "Unit/Object.h"

#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Engine/Gfx.h"
#include "Sound/SoundInst.h"
#include "UI/NpcMenu.h"
#include "UI/QuestLog.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB70D30
uint8_t byte_6FB70D30[4];
//D2Client.0x6FB70D34
uint8_t byte_6FB70D34[4];
//D2Client.0x6FB70D38
uint8_t byte_6FB70D38[4] = {0xFF, 0xFF, 0xFF, 0xFF};
//D2Client.0x6FB70D3C
uint8_t byte_6FB70D3C[4] = {0xFF, 0xFF, 0xFF, 0xFF};
//D2Client.0x6FB70D40
uint8_t byte_6FB70D40[444] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x71, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x71, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x70, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6A, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6A, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x3B, 0, 0, 0, 0x39, 0, 0, 0, 0x68, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x3C, 0, 0, 0, 0x39, 0, 0, 0, 0x69, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x3E, 0, 0, 0, 0x39, 0, 0, 0, 0x73, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x3F, 0, 0, 0, 0x3A, 0, 0, 0, 0x72, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x3D, 0, 0, 0, 0x3A, 0, 0, 0, 0x74, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x40, 0, 0, 0, 0x3A, 0, 0, 0, 0x75, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x41, 0, 0, 0, 0x39, 0, 0, 0, 0x77, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x42, 0, 0, 0, 0x3A, 0, 0, 0, 0x70, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x43, 0, 0, 0, 0x3A, 0, 0, 0, 0x70, 0xA, 0, 0, 0x20, 0x75, 0xB4, 0x6F, 0, 0, 0, 0, 0x44, 0, 0, 0, 0x39, 0, 0, 0, 0x6B, 0xA, 0, 0, 0, 0, 0, 0, 0xD0, 0x70, 0xB4, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x76, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6F, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6D, 0xA, 0, 0, 0, 0, 0, 0, 0, 0x71, 0xB4, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x78, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6F, 0xA, 0, 0, 0, 0, 0, 0, 0x80, 0x72, 0xB4, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6C, 0xA, 0, 0, 0, 0, 0, 0, 0xD0, 0x73, 0xB4, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x6E, 0xA};
//D2Client.0x6FB93AC0
int32_t dword_6FB93AC0 = 23;

//D2Client.0x6FB467E0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB467E0(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t extraout_EAX;
	uint32_t extraout_ECX;
	uint32_t uVar4;
	uint32_t extraout_ECX_00;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t uVar5;
	uint32_t extraout_EDX_01;
	uint32_t uVar6;

	iVar1 = *(int*)pUnit->pPlayerData->szName;
	if (*(char*)(iVar1 + 0x139) == '\0')
	{
		return 0;
	}
	iVar2 = ENVIRONMENT_GetPeriodOfDayFromAct(ghAct, nullptr);
	if (iVar2 != 0)
	{
		if ((0 < iVar2) && (iVar2 < 4))
		{
			uVar3 = pUnit->dwAnimMode;
			uVar4 = extraout_ECX;
			uVar5 = extraout_EDX;
			if (uVar3 == 0)
			{
				pUnit->dwAnimMode = 1;
				if (a2 == 0)
				{
					sub_6FB5C080(pUnit);
				}
				UNITS_SetAnimStartFrame(pUnit);
				uVar3 = pUnit->dwAnimMode;
				if (*(char*)(uVar3 + 0xc4 + iVar1) == '\0')
				{
					uVar4 = pUnit->dwFlags & 0xfffffffd;
				}
				else
				{
					uVar4 = pUnit->dwFlags | 2;
				}
				pUnit->dwFlags = uVar4;
				uVar5 = extraout_EDX_00;
			}
			uVar6 = (uint32_t)((uint32_t)uVar5 >> 8);
			sub_6FB46930(pUnit, CONCAT22((short)((uint32_t)uVar5 >> 0x10), (uint16_t) * (uint8_t*)(uVar3 + 0x110 + iVar1)),
			    CONCAT31(uVar6, *(uint8_t*)(iVar1 + 0x164)),
			    D2C_ZEXT(*(uint8_t*)(iVar1 + 0x165)),
			    CONCAT31(uVar6, *(uint8_t*)(iVar1 + 0x166)));
			return 1;
		}
		FOG_DisplayWarning("0", __FILE__, __LINE__);
		return 0;
	}
	if ((pUnit->dwAnimMode != 2) && (pUnit->dwAnimMode != 1))
	{
		return 0;
	}
	pUnit->dwAnimMode = 0;
	if (a2 == 0)
	{
		sub_6FB5C080(pUnit);
	}
	UNITS_SetAnimStartFrame(pUnit);
	sub_6FB46930(pUnit, CONCAT22((short)((uint32_t)extraout_EDX_01 >> 0x10), (uint16_t) * (uint8_t*)(iVar1 + 0x110 + pUnit->dwAnimMode)),
	    CONCAT31((int32_t)((uint32_t)extraout_EDX_01 >> 8), *(uint8_t*)(iVar1 + 0x164)),
	    CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), *(uint8_t*)(iVar1 + 0x165)),
	    CONCAT31((int32_t)((uint32_t)extraout_EAX >> 8), *(uint8_t*)(iVar1 + 0x166)));
	if (*(char*)(iVar1 + 0xc4 + pUnit->dwAnimMode) != '\0')
	{
		pUnit->dwFlags = pUnit->dwFlags | 2;
		return 1;
	}
	pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
	return 1;
}

//D2Client.0x6FB46930
void __fastcall sub_6FB46930(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)pUnit->dwInteractGUID;
	if ((uint16_t)a2 == 0)
	{
		if (puVar1 != nullptr)
		{
			if (pUnit->dwClassId != 0x25)
			{
				if (pUnit->dwClassId == 0x1d)
				{
					FOG_Trace("removed light source for brazier\n");
				}
				sub_6FB296E0((int)pUnit);
				return;
			}
			FOG_Trace("removed light source for tiki torch\n");
			sub_6FB296E0((int)pUnit);
			return;
		}
	}
	else
	{
		if (puVar1 == nullptr)
		{
			puVar1 = sub_6FAA4280(pUnit, 2, (uint32_t)((uint16_t)a2 >> 1), 0xff, a3, a4, a5);
			pUnit->dwInteractGUID = (uint32_t)puVar1;
			if (puVar1 == nullptr)
			{
				return;
			}
		}
		sub_6FAA43A0((int)puVar1, (uint32_t)((uint16_t)a2 >> 1));
	}
}

//D2Client.0x6FB469D0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB469D0(D2UnitStrc* pUnit, D2ActiveRoomStrc* pActiveRoom, int a3, int a4, int a5, uint32_t a6)
{
	uint8_t nAct;
	D2PlayerDataStrc* pDVar1;
	D2ObjectsTxt* pDVar2;
	uint32_t uVar3;
	int iVar4;
	uint32_t extraout_ECX;
	uint32_t extraout_EDX;

	pUnit->dwInteractGUID = 0;
	pUnit->dwAnimMode = a6 & 0xff;
	pDVar1 = (D2PlayerDataStrc*)D2_ALLOC(0x38);
	pUnit->pPlayerData = pDVar1;
	for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		pDVar1->szName[0] = '\0';
		pDVar1->szName[1] = '\0';
		pDVar1->szName[2] = '\0';
		pDVar1->szName[3] = '\0';
		pDVar1 = (D2PlayerDataStrc*)(pDVar1->szName + 4);
	}
	pUnit->pPlayerData->pQuestData[0] = nullptr;
	pUnit->pPlayerData->pQuestData[1] = nullptr;
	pDVar2 = DATATBLS_GetObjectsTxtRecord(a5);
	if (pDVar2->nSelectable[pUnit->dwAnimMode] == 0)
	{
		uVar3 = pUnit->dwFlags & 0xfffffffd;
	}
	else
	{
		uVar3 = pUnit->dwFlags | 2;
	}
	pUnit->dwFlags = uVar3;
	*(D2ObjectsTxt**)pUnit->pPlayerData->szName = pDVar2;
	UNITS_InitializeStaticPath(pUnit, pActiveRoom, a3, a4);
	if (pDVar2->nHasCollision[pUnit->dwAnimMode] != 0)
	{
		UNITS_BlockCollisionPath(pUnit, pActiveRoom, a3, a4);
	}
	if (pDVar2->nIsAttackable0 == 0)
	{
		uVar3 = pUnit->dwFlags & 0xfffffffb;
	}
	else
	{
		uVar3 = pUnit->dwFlags | 4;
	}
	pUnit->dwFlags = uVar3;
	UNITROOM_AddUnitToRoom(pUnit, pActiveRoom);
	pUnit->dwFlags = pUnit->dwFlags & 0xfffffff7;
	UNITS_SetAnimStartFrame(pUnit);
	if (pDVar2->nBlocksLight[pUnit->dwAnimMode] == 0)
	{
		uVar3 = pUnit->dwFlags | 0x20;
	}
	else
	{
		uVar3 = pUnit->dwFlags & 0xffffffdf;
	}
	pUnit->dwFlags = uVar3;
	if (pDVar2->nOrderFlag[pUnit->dwAnimMode] == 1)
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x100000;
	}
	if (pUnit->dwClassId == 0x3b)
	{
		iVar4 = DUNGEON_GetLevelIdFromRoom(pActiveRoom);
		nAct = DRLG_GetActNoFromLevelId(iVar4);
		iVar4 = DUNGEON_GetTownLevelIdFromActNo(nAct);
		if (0xff < iVar4)
		{
			FOG_DisplayAssert("eLevelId <= 255", __FILE__, __LINE__);
			exit(-1);
		}
		pUnit->pPlayerData->szName[4] = (char)iVar4;
	}
	else if (pUnit->dwClassId == 0x3c)
	{
		iVar4 = DUNGEON_GetLevelIdFromRoom(pActiveRoom);
		if (iVar4 == 0x26)
		{
			pUnit->pPlayerData->szName[4] = '\x04';
		}
		else if (iVar4 == 4)
		{
			pUnit->pPlayerData->szName[4] = '&';
		}
	}
	iVar4 = sub_6FB467E0(pUnit, 1);
	if (iVar4 == 0)
	{
		sub_6FB46930(pUnit, CONCAT22((short)(pUnit->dwAnimMode >> 0x10), (uint16_t)pDVar2->nLit[pUnit->dwAnimMode]),
		    CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), pDVar2->nRed), (uint32_t)pDVar2->nGreen,
		    CONCAT31((int32_t)((uint32_t)extraout_EDX >> 8), pDVar2->nBlue));
	}
}

//D2Client.0x6FB46BA0
void __fastcall sub_6FB46BA0(D2UnitStrc* pUnit)
{
	uint32_t uVar1;

	if (*(char*)(*(int*)pUnit->pPlayerData->szName + 0x1b5) == '\0')
	{
		return;
	}
	uVar1 = pUnit->dwClassId;
	if (uVar1 < 0x18e)
	{
		if (uVar1 != 0x18d)
		{
			switch (uVar1)
			{
			case 0x95:
				if (pUnit->dwAnimMode != 1)
				{
					return;
				}
			case 0x98:
				sub_6FB5BA70(pUnit, 0xb6, 3, 0, 0, 0, 0, 0);
				return;
			default:
				return;
			case 0x162:
			case 0x163:
			case 0x164:
				break;
			}
		}
	}
	else
	{
		if (uVar1 < 0x195)
		{
			return;
		}
		if ((0x197 < uVar1) && (uVar1 != 0x1c7))
		{
			return;
		}
	}
	if (pUnit->dwAnimMode == 0)
	{
		sub_6FB5BA70(pUnit, 0x47, 3, 0, 0, 0, 0, 0);
	}
}

//D2Client.0x6FB46D10
void __fastcall sub_6FB46D10(D2UnitStrc* pUnit)
{
	sub_6FB59320((int)pUnit);
	if (ghAct != nullptr)
	{
		UNITS_FreeCollisionPath(pUnit);
		UNITROOM_RemoveUnitFromRoom(pUnit);
		sub_6FB296E0((int)pUnit);
	}
	D2_FREE(pUnit->pPlayerData);
}

//D2Client.0x6FB46D50
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB46D50(D2UnitStrc* pUnit)
{
	char cVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t extraout_ECX;
	int iVar4;
	int iVar5;
	int iVar6;
	uint64_t uVar7;

	iVar5 = *(int*)pUnit->pPlayerData->szName;
	uVar2 = pUnit->dwAnimMode;
	iVar4 = *(int*)(iVar5 + 0xd8 + uVar2 * 4);
	if (iVar4 == 0x100)
		goto LAB_6fb46f82;
	cVar1 = *(char*)(uVar2 + 0x108 + iVar5);
	if (cVar1 == '\0')
	{
		if (*(char*)(iVar5 + 0x13a) != '\0')
		{
			sub_6FB46FB0(pUnit);
			goto LAB_6fb46f82;
		}
		if (iVar4 + -0x100 <= pUnit->nSeqCurrentFramePrecise)
		{
			if ((pUnit->dwClassId == 0xbd) && ((uVar2 == 2 || (uVar2 == 3))))
			{
				pUnit->dwAnimMode = uVar2 + 1;
				pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(uVar2 + 0x12a + iVar5) << 8;
				sub_6FB5C080(pUnit);
				UNITS_SetAnimStartFrame(pUnit);
			}
			else if (uVar2 == 1)
			{
				pUnit->dwAnimMode = 2;
				if (*(char*)(iVar5 + 0x133) == '\x01')
				{
					pUnit->dwFlags = pUnit->dwFlags | 0x100000;
				}
				if (*(int*)(iVar5 + 0x194) != 0)
				{
					iVar4 = 0x153;
					if (*(int*)(iVar5 + 0x194) != 0xff)
					{
						iVar4 = 0x97;
					}
					sub_6FB3EDF0(pUnit, iVar4, 4);
				}
				pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar5 + 299) << 8;
				sub_6FB5C080(pUnit);
				UNITS_SetAnimStartFrame(pUnit);
				if ((*(char*)(iVar5 + 0x1b5) != '\0') &&
				    (((((iVar4 = pUnit->dwClassId, iVar4 == 0x162 || (iVar4 == 0x163)) || (iVar4 == 0x18d)) || ((iVar4 == 0x195 || (iVar4 == 0x197)))) || ((iVar4 == 0x196 || (iVar4 == 0x164))))))
				{
					sub_6FB5BEC0(pUnit, 0, 0x47);
				}
				uVar7 = sub_6FAFA230((int)pUnit, 2, (uint32_t) * (uint8_t*)(pUnit->dwAnimMode + 0xc4 + iVar5));
				sub_6FB46930(pUnit, CONCAT22((short)((uint64_t)uVar7 >> 0x30), (uint16_t) * (uint8_t*)(iVar5 + 0x112)),
				    CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), *(uint8_t*)(iVar5 + 0x164)),
				    CONCAT31((int32_t)((uint64_t)uVar7 >> 8), *(uint8_t*)(iVar5 + 0x165)),
				    CONCAT31((int32_t)((uint64_t)uVar7 >> 0x28), *(uint8_t*)(iVar5 + 0x166)));
				if ((*(char*)(pUnit->dwAnimMode + 0x120 + iVar5) == '\0') &&
				    (*(char*)(iVar5 + 0x121) != '\0'))
				{
					UNITS_FreeCollisionPath(pUnit);
				}
			}
			goto LAB_6fb46f82;
		}
	}
	if (pUnit->dwClassId == 0xc)
	{
		iVar5 = pUnit->nSeqCurrentFramePrecise - (int)pUnit->wAnimSpeed;
		pUnit->nSeqCurrentFramePrecise = iVar5;
		if (iVar5 < 0)
		{
			pUnit->nSeqCurrentFramePrecise = iVar5 + iVar4;
		}
	}
	else if ((pUnit->dwClassId == 0xbd) && (uVar2 == 3))
	{
		iVar4 = pUnit->nSeqCurrentFramePrecise - (int)pUnit->wAnimSpeed;
		pUnit->nSeqCurrentFramePrecise = iVar4;
		if (iVar4 < 0)
		{
			pUnit->dwAnimMode = 4;
			pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar5 + 0x12d) << 8;
			sub_6FB5C080(pUnit);
			UNITS_SetAnimStartFrame(pUnit);
		}
	}
	else
	{
		iVar6 = pUnit->nSeqCurrentFramePrecise + (int)pUnit->wAnimSpeed;
		pUnit->nSeqCurrentFramePrecise = iVar6;
		if (iVar4 <= iVar6)
		{
			if (cVar1 == '\0')
			{
				pUnit->nSeqCurrentFramePrecise = iVar4 + -0x100;
			}
			else
			{
				pUnit->nSeqCurrentFramePrecise =
				    ((uint32_t) * (uint8_t*)(uVar2 + 0x129 + iVar5) * 0x100 - iVar4) + iVar6;
			}
		}
	}
LAB_6fb46f82:
	if (3 < *(uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x1b4))
	{
		uVar3 = sub_6FB48430(pUnit);
		if ((char)uVar3 == '\0')
		{
			return;
		}
	}
	sub_6FB50370(pUnit);
}

//D2Client.0x6FB46FB0
void __fastcall sub_6FB46FB0(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;

	uVar2 = pUnit->dwAnimMode;
	if (uVar2 == 1)
	{
		iVar1 = *(int*)(*(int*)pUnit->pPlayerData->szName + 0xd8 + uVar2 * 4) + -0x100;
		if (pUnit->nSeqCurrentFramePrecise == iVar1)
		{
			sub_6FB47030(pUnit);
			return;
		}
		iVar3 = pUnit->nSeqCurrentFramePrecise + (int)pUnit->wAnimSpeed;
		pUnit->nSeqCurrentFramePrecise = iVar3;
		if (iVar1 < iVar3)
		{
			pUnit->nSeqCurrentFramePrecise = iVar1;
			return;
		}
	}
	else
	{
		if (uVar2 == 3)
		{
			iVar1 = pUnit->nSeqCurrentFramePrecise;
			if (iVar1 < 1)
			{
				sub_6FB47030(pUnit);
				return;
			}
			if (iVar1 < pUnit->wAnimSpeed)
			{
				pUnit->nSeqCurrentFramePrecise = 0;
				return;
			}
			pUnit->nSeqCurrentFramePrecise = iVar1 - pUnit->wAnimSpeed;
			return;
		}
		FOG_DisplayWarning("0", __FILE__, __LINE__);
	}
}

//D2Client.0x6FB47030
void __fastcall sub_6FB47030(D2UnitStrc* pUnit)
{
	uint8_t bVar1;

	if (pUnit->dwAnimMode == 3)
	{
		pUnit->dwAnimMode = 0;
		bVar1 = *(uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x129);
	}
	else
	{
		if (pUnit->dwAnimMode != 1)
		{
			FOG_DisplayWarning("0", __FILE__, __LINE__);
			goto LAB_6fb4709b;
		}
		UNITS_FreeCollisionPath(pUnit);
		pUnit->dwAnimMode = 2;
		bVar1 = *(uint8_t*)(*(int*)pUnit->pPlayerData->szName + 299);
	}
	pUnit->nSeqCurrentFramePrecise = (uint32_t)bVar1;
	sub_6FB5C080(pUnit);
	UNITS_SetAnimStartFrame(pUnit);
LAB_6fb4709b:
	if (*(char*)(*(int*)pUnit->pPlayerData->szName + 0xc4 + pUnit->dwAnimMode) != '\0')
	{
		pUnit->dwFlags = pUnit->dwFlags | 2;
		return;
	}
	pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
}

//D2Client.0x6FB470D0
void __fastcall sub_6FB470D0(uint32_t a1, D2UnitStrc* pUnit, uint32_t a3)
{
	D2PlayerDataStrc* _Str;
	char* _Source;
	size_t _Count;

	_Str = UNITS_GetPlayerData(pUnit);
	if (_Str != nullptr)
	{
		_Count = 0x10;
		_Source = _strrev(_Str->szName);
		strncpy(_Str->szName, _Source, _Count);
	}
}

//D2Client.0x6FB47100
void __fastcall sub_6FB47100(int* a1, D2UnitStrc* pUnit, uint32_t a3)
{
	int iVar1;
	bool bVar2;
	int iVar3;
	bool bVar4;
	uint32_t* puVar5;
	int local_70;
	int local_68;
	int local_64;
	uint32_t local_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int local_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_2c;

	bVar2 = true;
	local_64 = -5;
	local_68 = 5;
	do
	{
		bVar4 = true;
		local_70 = -5;
		iVar3 = 5;
		do
		{
			puVar5 = &local_5c;
			for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				*puVar5 = 0;
				puVar5 = puVar5 + 1;
			}
			iVar1 = *a1;
			local_5c = 3;
			if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
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
			iVar1 = *a1;
			if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
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
			if (bVar2)
			{
				iStack_40 = local_68;
			}
			else
			{
				iStack_40 = local_64;
			}
			iStack_3c = iVar3;
			if (!bVar4)
			{
				iStack_3c = local_70;
			}
			uStack_4c = 0x3e;
			pDStack_58 = pUnit;
			iStack_2c = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
			iStack_2c = iStack_2c / 5;
			if (iStack_2c < 1)
			{
				iStack_2c = 1;
			}
			else if (8 < iStack_2c)
			{
				iStack_2c = 8;
			}
			sub_6FB3E070(&local_5c);
			iVar3 = iVar3 + 5;
			bVar4 = (bool)(bVar4 ^ 1);
			local_70 = local_70 + -5;
		} while (iVar3 < 0x19);
		local_68 = local_68 + 5;
		bVar2 = (bool)(bVar2 ^ 1);
		local_64 = local_64 + -5;
	} while (local_68 < 0x19);
}

//D2Client.0x6FB47280
void __fastcall sub_6FB47280(int* a1, D2UnitStrc* pUnit, uint32_t a3)
{
	int iVar1;
	int iVar2;
	int* piVar3;
	int local_8c[13];
	D2UnitStrc* pDStack_58;
	int* piStack_54;
	uint32_t uStack_4c;
	int local_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	uint32_t uStack_38;
	int iStack_2c;

	iVar2 = 0;
	local_8c[6] = 0xfffffffa;
	local_8c[7] = 0xfffffffa;
	local_8c[8] = 0;
	local_8c[9] = 0;
	local_8c[10] = 6;
	local_8c[0xb] = 6;
	local_8c[0] = 6;
	local_8c[1] = 0xfffffffa;
	local_8c[2] = 6;
	local_8c[3] = 0xfffffffa;
	local_8c[4] = 6;
	local_8c[5] = 0xfffffffa;
	do
	{
		piVar3 = local_8c + 0xc;
		for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*piVar3 = 0;
			piVar3 = piVar3 + 1;
		}
		iVar1 = *a1;
		local_8c[0xc] = 0x520;
		if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
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
		iVar1 = *a1;
		if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
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
		iStack_40 = *(int*)((int)local_8c + iVar2 + 0x18) + local_48;
		iStack_3c = *(int*)((int)local_8c + iVar2) + iStack_44;
		uStack_38 = 1;
		uStack_4c = 0x2d;
		pDStack_58 = pUnit;
		piStack_54 = a1;
		iStack_2c = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
		iStack_2c = iStack_2c / 5;
		if (iStack_2c < 1)
		{
			iStack_2c = 1;
		}
		else if (8 < iStack_2c)
		{
			iStack_2c = 8;
		}
		sub_6FB3E070((uint32_t*)(local_8c + 0xc));
		iVar2 = iVar2 + 4;
	} while (iVar2 < 0x18);
}

//D2Client.0x6FB473D0
void __fastcall sub_6FB473D0(int* a1, D2UnitStrc* pUnit, uint32_t a3)
{
	int iVar1;
	int iVar2;
	int* piVar3;
	int local_8c[13];
	D2UnitStrc* pDStack_58;
	int* piStack_54;
	uint32_t uStack_4c;
	int local_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	uint32_t uStack_38;
	int iStack_2c;

	iVar2 = 0;
	local_8c[6] = 0xfffffffa;
	local_8c[7] = 0xfffffffa;
	local_8c[8] = 0;
	local_8c[9] = 0;
	local_8c[10] = 6;
	local_8c[0xb] = 6;
	local_8c[0] = 6;
	local_8c[1] = 0xfffffffa;
	local_8c[2] = 6;
	local_8c[3] = 0xfffffffa;
	local_8c[4] = 6;
	local_8c[5] = 0xfffffffa;
	do
	{
		piVar3 = local_8c + 0xc;
		for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*piVar3 = 0;
			piVar3 = piVar3 + 1;
		}
		iVar1 = *a1;
		local_8c[0xc] = 0x520;
		if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
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
		iVar1 = *a1;
		if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
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
		iStack_40 = *(int*)((int)local_8c + iVar2 + 0x18) + local_48;
		iStack_3c = *(int*)((int)local_8c + iVar2) + iStack_44;
		uStack_38 = 1;
		uStack_4c = 0x30;
		pDStack_58 = pUnit;
		piStack_54 = a1;
		iStack_2c = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
		iStack_2c = iStack_2c / 5;
		if (iStack_2c < 1)
		{
			iStack_2c = 1;
		}
		else if (8 < iStack_2c)
		{
			iStack_2c = 8;
		}
		sub_6FB3E070((uint32_t*)(local_8c + 0xc));
		iVar2 = iVar2 + 4;
	} while (iVar2 < 0x18);
}

//D2Client.0x6FB47520
void __fastcall sub_6FB47520(D2UnitStrc* pUnit, uint8_t* a2)
{
	int iVar1;
	uint32_t uVar2;

	uVar2 = (uint32_t)*a2;
	D2_ASSERT(dword_6FB93AC0 > (int)uVar2);
	iVar1 = uVar2 * 0x14;
	if (*(int*)(byte_6FB70D38 + uVar2 * 0x14) != -1)
	{
		sub_6FB5BEC0(pUnit, 0, *(int*)(byte_6FB70D38 + uVar2 * 0x14));
		if ((pUnit == nullptr) || (pUnit->dwAnimMode == 0))
		{
			sub_6FB5BA70(pUnit, *(int*)(byte_6FB70D38 + iVar1), 3, 0, 0, 0, 0, 0);
		}
	}
	if (*(int*)(byte_6FB70D3C + iVar1) != -1)
	{
		sub_6FB5BEC0(pUnit, 0, *(int*)(byte_6FB70D3C + iVar1));
		if ((pUnit == nullptr) || (pUnit->dwAnimMode == 0))
		{
			sub_6FB5BA70(pUnit, *(int*)(byte_6FB70D3C + iVar1), 3, 0, 0, 0, 0, 0);
		}
	}
}

//D2Client.0x6FB475D0
void __fastcall sub_6FB475D0(D2UnitStrc* pUnit)
{
	D2ShrinesTxt* pDVar1;

	pDVar1 = DATATBLS_GetShrinesTxtRecord((uint32_t)(uint8_t)pUnit->pPlayerData->szName[4]);
	UNITS_SetShrineTxtRecordInObjectData(pUnit, pDVar1);
	pDVar1 = UNITS_GetShrineTxtRecordFromObject(pUnit);
	D2_ASSERT(pDVar1 != nullptr);
	D2_ASSERT(dword_6FB93AC0 > (int)(uint32_t)pDVar1->nCode);
	if (*(code**)(byte_6FB70D30 + (uint32_t)pDVar1->nCode * 0x14) != nullptr)
	{
		(**(code**)(byte_6FB70D30 + (uint32_t)pDVar1->nCode * 0x14))();
	}
}

//D2Client.0x6FB47660
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB47660(int a1, D2UnitStrc* pUnit, int* a3)
{
	uint8_t bVar1;
	int iVar2;
	D2ObjectsTxt* pDVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int extraout_EAX;
	uint32_t uVar6;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t extraout_EDX_01;
	uint32_t uVar7;
	D2ShrinesTxt* pDVar8;

	if (a1 == 3)
	{
		iVar2 = *(int*)pUnit->pPlayerData->szName;
		if (*(char*)(iVar2 + 0x13a) == '\0')
		{
			UNITS_ChangeAnimMode(pUnit, a3[1]);
			sub_6FB5C080(pUnit);
			uVar7 = extraout_EDX;
			if ((*(char*)(iVar2 + 0x1b5) != '\0') &&
			    ((((((iVar5 = pUnit->dwClassId, iVar5 == 0x162 || (iVar5 == 0x163)) || (iVar5 == 0x18d)) || ((iVar5 == 0x195 || (iVar5 == 0x197)))) || ((iVar5 == 0x196 || (iVar5 == 0x164)))) &&
			        (pUnit->dwAnimMode == 0))))
			{
				sub_6FB5BA70(pUnit, 0x47, 3, 0, 0, 0, 0, 0);
				uVar7 = extraout_EDX_00;
			}
			iVar5 = pUnit->dwAnimMode + iVar2;
			if (*(char*)(iVar5 + 0xc4) == '\0')
			{
				uVar6 = pUnit->dwFlags & 0xfffffffd;
			}
			else
			{
				uVar6 = pUnit->dwFlags | 2;
			}
			pUnit->dwFlags = uVar6;
			if (*(char*)(iVar5 + 0x120) == '\0')
			{
				UNITS_FreeCollisionPath(pUnit);
				iVar5 = extraout_EAX;
				uVar7 = extraout_EDX_01;
			}
			if (*(char*)(pUnit->dwAnimMode + 0x131 + iVar2) == '\x01')
			{
				pUnit->dwFlags = pUnit->dwFlags | 0x100000;
			}
			sub_6FB46930(pUnit, CONCAT22((short)((uint32_t)a3[1] >> 0x10), (uint16_t) * (uint8_t*)(a3[1] + 0x110 + iVar2)),
			    CONCAT31((int32_t)(pUnit->dwAnimMode >> 8), *(uint8_t*)(iVar2 + 0x164)),
			    CONCAT31((int32_t)((uint32_t)iVar5 >> 8), *(uint8_t*)(iVar2 + 0x165)),
			    CONCAT31((int32_t)((uint32_t)uVar7 >> 8), *(uint8_t*)(iVar2 + 0x166)));
		}
		else
		{
			sub_6FB478D0(pUnit, *a3, a3[1]);
		}
		sub_6FB50370(pUnit);
		UNITS_SetAnimStartFrame(pUnit);
		if (*(char*)(pUnit->dwAnimMode + 0x118 + iVar2) == '\0')
		{
			uVar6 = pUnit->dwFlags | 0x20;
		}
		else
		{
			uVar6 = pUnit->dwFlags & 0xffffffdf;
		}
		pUnit->dwFlags = uVar6;
		iVar2 = UNITS_IsShrine(pUnit);
		if (iVar2 != 0)
		{
			pDVar8 = UNITS_GetShrineTxtRecordFromObject(pUnit);
			if (pDVar8 == nullptr)
			{
				FOG_DisplayAssert("ptShrineData", __FILE__, __LINE__);
				exit(-1);
			}
			D2_ASSERT(dword_6FB93AC0 > (int)(uint32_t)pDVar8->nCode);
			if (*(code**)(byte_6FB70D30 + (uint32_t)pDVar8->nCode * 0x14) != nullptr)
			{
				(**(code**)(byte_6FB70D30 + (uint32_t)pDVar8->nCode * 0x14))();
			}
		}
	}
	else
	{
		if (a1 != 0x15)
		{
			FOG_DisplayWarning("0", __FILE__, __LINE__);
			return;
		}
		pDVar8 = nullptr;
		iVar2 = UNITS_IsShrine(pUnit);
		if (iVar2 == 0)
		{
			if (pUnit == nullptr)
			{
				iVar2 = -1;
			}
			else
			{
				iVar2 = pUnit->dwClassId;
			}
			pDVar3 = DATATBLS_GetObjectsTxtRecord(iVar2);
			bVar1 = pDVar3->nShrineFunction;
		}
		else
		{
			pDVar8 = UNITS_GetShrineTxtRecordFromObject(pUnit);
			bVar1 = pDVar8->nCode;
		}
		pDVar4 = sub_6FB269F0(*a3, 0);
		if (pDVar4 != nullptr)
		{
			if (((bVar1 != 0) && ((int)(uint32_t)bVar1 < dword_6FB93AC0)) &&
			    (*(code**)(byte_6FB70D34 + (uint32_t)bVar1 * 0x14) != nullptr))
			{
				(**(code**)(byte_6FB70D34 + (uint32_t)bVar1 * 0x14))(pDVar8);
			}
			sub_6FB47B70(pUnit, pDVar4);
			return;
		}
	}
}

//D2Client.0x6FB478D0
void __fastcall sub_6FB478D0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	int32_t nY;
	int iVar2;
	D2ActiveRoomStrc* pDVar3;
	uint32_t uVar4;
	int32_t nY_00;

	iVar1 = *(int*)pUnit->pPlayerData->szName;
	D2_ASSERT(7 >= a3);
	if (a3 == 0)
	{
		if ((pUnit->dwAnimMode == 2) && (*(int*)(iVar1 + 0xe4) != 0x100))
		{
			pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar1 + 0x129);
			UNITS_ChangeAnimMode(pUnit, 3);
			sub_6FB5C080(pUnit);
			uVar4 = pUnit->dwUnitType;
			pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
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
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				iVar2 = pUnit->pDynamicPath->dwClientCoordY;
				pDVar3 = UNITS_GetRoom(pUnit);
				UNITS_BlockCollisionPath(pUnit, pDVar3, iVar2, (int)nY);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar2 = 0;
				pDVar3 = UNITS_GetRoom(pUnit);
				UNITS_BlockCollisionPath(pUnit, pDVar3, iVar2, (int)nY);
			}
			else
			{
				iVar2 = PATH_GetXPosition(pUnit->pDynamicPath);
				pDVar3 = UNITS_GetRoom(pUnit);
				UNITS_BlockCollisionPath(pUnit, pDVar3, iVar2, (int)nY);
			}
			goto LAB_6fb47b31;
		}
	}
	else if (((a3 == 2) && (pUnit->dwAnimMode == 0)) && (*(int*)(iVar1 + 0xdc) != 0x100))
	{
		UNITS_ChangeAnimMode(pUnit, 1);
		sub_6FB5C080(pUnit);
		pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
		pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 299);
		goto LAB_6fb47b31;
	}
	if (a2 == 0)
	{
		uVar4 = pUnit->dwFlags & 0xfffffffd;
	}
	else
	{
		uVar4 = pUnit->dwFlags | 2;
	}
	pUnit->dwFlags = uVar4;
	uVar4 = pUnit->dwAnimMode;
	if (a3 != uVar4)
	{
		if (((a3 == 4) || (a3 == 2)) || (a3 == 5))
		{
			if (((uVar4 != 5) && (uVar4 != 2)) && (uVar4 != 4))
			{
				UNITS_FreeCollisionPath(pUnit);
			}
		}
		else if ((a3 == 0) && (uVar4 != 0))
		{
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
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
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				iVar2 = pUnit->pDynamicPath->dwClientCoordY;
				pDVar3 = UNITS_GetRoom(pUnit);
				UNITS_BlockCollisionPath(pUnit, pDVar3, iVar2, (int)nY_00);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar2 = 0;
				pDVar3 = UNITS_GetRoom(pUnit);
				UNITS_BlockCollisionPath(pUnit, pDVar3, iVar2, (int)nY_00);
			}
			else
			{
				iVar2 = PATH_GetXPosition(pUnit->pDynamicPath);
				pDVar3 = UNITS_GetRoom(pUnit);
				UNITS_BlockCollisionPath(pUnit, pDVar3, iVar2, (int)nY_00);
			}
		}
		UNITS_ChangeAnimMode(pUnit, a3);
		sub_6FB5C080(pUnit);
	}
	pUnit->nSeqCurrentFramePrecise =
	    (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x129 + a3);
LAB_6fb47b31:
	if (*(char*)(pUnit->dwAnimMode + 0x118 + iVar1) == '\0')
	{
		pUnit->dwFlags = pUnit->dwFlags | 0x20;
		return;
	}
	pUnit->dwFlags = pUnit->dwFlags & 0xffffffdf;
}

//D2Client.0x6FB47B70
uint8_t* __fastcall sub_6FB47B70(D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	D2ShrinesTxt* pDVar1;
	uint8_t* puVar2;
	uint32_t uVar3;

	pDVar1 = UNITS_GetShrineTxtRecordFromObject(pUnit);
	D2_ASSERT(pDVar1 != nullptr);
	uVar3 = (uint32_t)pDVar1->nCode;
	D2_ASSERT(dword_6FB93AC0 > (int)uVar3);
	puVar2 = byte_6FB70D30 + uVar3 * 0x14;
	if (*(int*)(byte_6FB70D40 + uVar3 * 0x14) != 0)
	{
		puVar2 = (uint8_t*)sub_6FB55820(*(int*)(byte_6FB70D40 + uVar3 * 0x14), pUnit2, 0.0, 0.0, 0);
	}
	return puVar2;
}

//D2Client.0x6FB47BF0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB47BF0(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	uint32_t extraout_EAX;
	uint32_t uVar2;

	if (pUnit->dwFlagEx == 0)
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		pUnit->dwTickCount = (*(uint32_t*)((uint8_t*)&DVar1 + 0)) & 0x3f;
		pUnit->dwFlagEx = 1;
	}
	if (((pUnit->dwTickCount & 0x3f) == 0) && (pUnit->dwAnimMode != 1))
	{
		pUnit->dwAnimMode = 1;
		UNITS_SetAnimStartFrame(pUnit);
	}
	uVar2 = pUnit->dwAnimMode;
	pUnit->dwTickCount = pUnit->dwTickCount + 1;
	if (uVar2 == 2)
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		pUnit->dwAnimMode = 0;
		pUnit->dwTickCount = pUnit->dwTickCount + ((*(uint32_t*)((uint8_t*)&DVar1 + 0)) & 0x3f);
		UNITS_SetAnimStartFrame(pUnit);
		uVar2 = extraout_EAX;
	}
	return D2C_ZEXT(1);
}

//D2Client.0x6FB47CA0
uint32_t __fastcall sub_6FB47CA0(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	uint32_t uVar2;

	if (pUnit->dwFlagEx == 0)
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		pUnit->dwTickCount = (*(uint32_t*)((uint8_t*)&DVar1 + 0)) & 0x3f;
		pUnit->dwFlagEx = 1;
	}
	if (((pUnit->dwTickCount & 0x3f) == 0) && (pUnit->dwAnimMode != 1))
	{
		pUnit->dwAnimMode = 1;
		UNITS_SetAnimStartFrame(pUnit);
	}
	pUnit->dwTickCount = pUnit->dwTickCount + 1;
	if (pUnit->dwAnimMode == 2)
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		pUnit->dwAnimMode = 0;
		pUnit->dwTickCount = pUnit->dwTickCount + ((*(uint32_t*)((uint8_t*)&DVar1 + 0)) & 0x3f);
		UNITS_SetAnimStartFrame(pUnit);
	}
	uVar2 = sub_6FB50370(pUnit);
	return CONCAT31((int32_t)((uint32_t)uVar2 >> 8), 1);
}

//D2Client.0x6FB47D50
uint32_t __fastcall sub_6FB47D50(D2UnitStrc* pUnit)
{
	int iVar1;
	uint64_t DVar2;
	DWORD DVar3;
	uint32_t uVar4;

	DVar3 = GetTickCount();
	if (pUnit->dwTickCount < DVar3)
	{
		DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar2;
		pUnit->dwTickCount = (int)(((uint64_t)DVar2 & 0xffffffff) % 5000) + 7000 + DVar3;
		pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12e);
		UNITS_ChangeAnimMode(pUnit, 3);
		sub_6FB5C080(pUnit);
	}
	if ((pUnit->dwAnimMode == 3) &&
	    (iVar1 = *(int*)pUnit->pPlayerData->szName,
	        *(int*)(iVar1 + 0xe4) + -0x100 <= pUnit->nSeqCurrentFramePrecise))
	{
		pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar1 + 0x129);
		UNITS_ChangeAnimMode(pUnit, 0);
		sub_6FB5C080(pUnit);
	}
	uVar4 = sub_6FB50370(pUnit);
	return uVar4 & 0xffffff00;
}

//D2Client.0x6FB47E00
uint32_t __fastcall sub_6FB47E00(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	DWORD DVar2;
	uint32_t uVar3;
	int iVar4;

	DVar2 = GetTickCount();
	if (pUnit->dwTickCount < DVar2)
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		pUnit->dwTickCount = (int)(((uint64_t)DVar1 & 0xffffffff) % 10000) + 23000 + DVar2;
		pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12e);
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		if (((uint64_t)DVar1 & 1) == 0)
		{
			iVar4 = 4;
		}
		else
		{
			iVar4 = 3;
		}
		UNITS_ChangeAnimMode(pUnit, iVar4);
		sub_6FB5C080(pUnit);
	}
	uVar3 = pUnit->dwAnimMode;
	if (((uVar3 == 3) || (uVar3 == 4)) &&
	    (iVar4 = *(int*)pUnit->pPlayerData->szName,
	        *(int*)(iVar4 + 0xd8 + uVar3 * 4) + -0x100 <= pUnit->nSeqCurrentFramePrecise))
	{
		pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar4 + 0x129);
		UNITS_ChangeAnimMode(pUnit, 0);
		sub_6FB5C080(pUnit);
	}
	uVar3 = sub_6FB50370(pUnit);
	return uVar3 & 0xffffff00;
}

//D2Client.0x6FB47EE0
uint32_t __fastcall sub_6FB47EE0(D2UnitStrc* pUnit)
{
	int iVar1;
	uint64_t DVar2;
	DWORD DVar3;
	uint32_t uVar4;

	DVar3 = GetTickCount();
	if (pUnit->dwTickCount < DVar3)
	{
		DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar2;
		pUnit->dwTickCount = (int)(((uint64_t)DVar2 & 0xffffffff) % 10000) + 20000 + DVar3;
		pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12e);
		UNITS_ChangeAnimMode(pUnit, 3);
		sub_6FB5C080(pUnit);
	}
	if ((2 < pUnit->dwAnimMode) &&
	    (iVar1 = *(int*)pUnit->pPlayerData->szName,
	        pUnit->nSeqCurrentFramePrecise == *(int*)(iVar1 + 0xd8 + pUnit->dwAnimMode * 4) + -0x100))
	{
		pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar1 + 0x129);
		UNITS_ChangeAnimMode(pUnit, 0);
		sub_6FB5C080(pUnit);
	}
	uVar4 = sub_6FB50370(pUnit);
	return uVar4 & 0xffffff00;
}

//D2Client.0x6FB47FA0
uint32_t __fastcall sub_6FB47FA0(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	DWORD DVar2;
	D2UnitStrc* pDVar3;

	DVar2 = GetTickCount();
	pDVar3 = (D2UnitStrc*)pUnit->dwAnimMode;
	if (pDVar3 == nullptr)
	{
		if (pUnit->dwTickCount < DVar2)
		{
			pUnit->dwTickCount = DVar2 + 10000;
			pUnit->nSeqCurrentFramePrecise =
			    (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12a);
			UNITS_ChangeAnimMode(pUnit, 1);
			pDVar3 = sub_6FB5C080(pUnit);
			return CONCAT31((int32_t)((uint32_t)pDVar3 >> 8), 1);
		}
	}
	else if ((pDVar3 != nullptr) && (pUnit->dwTickCount < DVar2))
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		pUnit->dwTickCount = (int)(((uint64_t)DVar1 & 0xffffffff) % 3000) + 0x1194 + DVar2;
		UNITS_ChangeAnimMode(pUnit, 0);
		pDVar3 = sub_6FB5C080(pUnit);
	}
	return CONCAT31((int32_t)((uint32_t)pDVar3 >> 8), 1);
}

//D2Client.0x6FB48050
uint32_t __fastcall sub_6FB48050(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	DWORD DVar2;
	D2UnitStrc* pDVar3;

	DVar2 = GetTickCount();
	pDVar3 = (D2UnitStrc*)pUnit->dwAnimMode;
	if (pDVar3 == nullptr)
	{
		if (pUnit->dwTickCount < DVar2)
		{
			pUnit->dwTickCount = DVar2 + 3000;
			pUnit->nSeqCurrentFramePrecise =
			    (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12a);
			UNITS_ChangeAnimMode(pUnit, 1);
			pDVar3 = sub_6FB5C080(pUnit);
			return CONCAT31((int32_t)((uint32_t)pDVar3 >> 8), 1);
		}
	}
	else if ((pDVar3 != nullptr) && (pUnit->dwTickCount < DVar2))
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		pUnit->dwTickCount = (int)(((uint64_t)DVar1 & 0xffffffff) % 5000) + 0x9c4 + DVar2;
		UNITS_ChangeAnimMode(pUnit, 0);
		pDVar3 = sub_6FB5C080(pUnit);
	}
	return CONCAT31((int32_t)((uint32_t)pDVar3 >> 8), 1);
}

//D2Client.0x6FB48100
uint8_t __cdecl sub_6FB48100()
{
	return 1;
}

//D2Client.0x6FB48110
uint32_t __fastcall sub_6FB48110(D2UnitStrc* pUnit)
{
	DWORD DVar1;
	D2UnitStrc* pUnit2;
	uint32_t uVar2;

	DVar1 = GetTickCount();
	uVar2 = pUnit->dwTickCount;
	if (uVar2 != 0)
	{
		if (DVar1 - uVar2 < 0x3e9)
			goto LAB_6fb4815b;
		pUnit2 = CUNIT_GetPlayer();
		uVar2 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit2);
		if (0x19 < (int)uVar2)
		{
			uVar2 = sub_6FB26C70(pUnit->dwUnitId, 2);
			return uVar2 & 0xffffff00;
		}
	}
	pUnit->dwTickCount = DVar1;
LAB_6fb4815b:
	return D2C_ZEXT(1);
}

//D2Client.0x6FB48160
// TODO: decompilation needs review (in_reg)
uint32_t __fastcall sub_6FB48160(int a1)
{
	int in_EAX;

	if ((a1 != 0) && (in_EAX = *(int*)(a1 + 0x10), in_EAX != 0))
	{
		in_EAX = sub_6FB06E90();
	}
	return CONCAT31((int32_t)((uint32_t)in_EAX >> 8), 1);
}

//D2Client.0x6FB48180
uint32_t __fastcall sub_6FB48180(D2UnitStrc* pUnit)
{
	D2UnitStrc* pDVar1;
	D2BitBufferStrc* pDVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;

	if ((pUnit == nullptr) ||
	    (pDVar3 = (D2UnitStrc*)pUnit->dwAnimMode,
	        (D2UnitStrc*)pUnit->dwAnimMode == nullptr))
	{
		pDVar1 = CUNIT_GetPlayer();
		pDVar3 = pDVar1;
		if (pDVar1 != nullptr)
		{
			iVar5 = 0;
			iVar4 = 0x27;
			pDVar2 = sub_6FAFBD20();
			pDVar3 = (D2UnitStrc*)QUESTRECORD_GetQuestState(pDVar2, iVar4, iVar5);
			if (pDVar3 != nullptr)
			{
				iVar5 = 4;
				iVar4 = 0x27;
				pDVar2 = sub_6FAFBD20();
				pDVar3 = (D2UnitStrc*)QUESTRECORD_GetQuestState(pDVar2, iVar4, iVar5);
				if (pDVar3 == nullptr)
				{
					pDVar3 = CUNIT_GetPlayer();
					pDVar3 = (D2UnitStrc*)UNITS_GetDistanceToOtherUnit(pUnit, pDVar3);
					if ((int)pDVar3 < 0x19)
					{
						if (pDVar1->pDynamicPath != nullptr)
						{
							D2Common_10153(pDVar1->pDynamicPath);
						}
						sub_6FB4EA90(0x13, pDVar1, 2, pUnit->dwUnitId, 0);
						UNITS_ChangeAnimMode(pUnit, 2);
						pDVar3 = sub_6FB5C080(pUnit);
					}
				}
			}
		}
	}
	return CONCAT31((int32_t)((uint32_t)pDVar3 >> 8), 1);
}

//D2Client.0x6FB48210
// TODO: decompilation needs review (in_reg)
uint32_t __fastcall sub_6FB48210(int a1)
{
	int in_EAX;

	if ((a1 != 0) && (in_EAX = *(int*)(a1 + 0x10), in_EAX != 0))
	{
		in_EAX = sub_6FB06E70();
	}
	return CONCAT31((int32_t)((uint32_t)in_EAX >> 8), 1);
}

//D2Client.0x6FB48230
uint32_t __fastcall sub_6FB48230(D2UnitStrc* pUnit)
{
	DWORD DVar1;

	DVar1 = GetTickCount();
	if (pUnit->dwTickCount < DVar1)
	{
		sub_6FB467E0(pUnit, 0);
		DVar1 = GetTickCount();
		DVar1 = DVar1 + 500;
		pUnit->dwTickCount = DVar1;
	}
	return D2C_ZEXT(1);
}

//D2Client.0x6FB48260
uint32_t __fastcall sub_6FB48260(D2UnitStrc* pUnit)
{
	DWORD DVar1;

	DVar1 = GetTickCount();
	if (pUnit->dwTickCount < DVar1)
	{
		if (pUnit->dwAnimMode == 0)
		{
			sub_6FB5BA70(pUnit, 0x48, 3, 0, 0, 0, 0, 0);
			DVar1 = GetTickCount();
			pUnit->dwTickCount = DVar1 + 500;
			return CONCAT31((int32_t)(DVar1 + 500 >> 8), 1);
		}
		sub_6FB5BEC0(pUnit, 0, 0x48);
		DVar1 = GetTickCount();
		DVar1 = DVar1 + 500;
		pUnit->dwTickCount = DVar1;
	}
	return D2C_ZEXT(1);
}

//D2Client.0x6FB482C0
uint32_t __fastcall sub_6FB482C0(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	DWORD DVar2;

	DVar2 = GetTickCount();
	if (pUnit->dwTickCount < DVar2)
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		if ((uint32_t)(((uint64_t)DVar1 & 0xffffffff) % 100) < 10)
		{
			sub_6FB55820(0x9c9, pUnit, 0.0, 0.0, 0);
		}
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		DVar2 = GetTickCount();
		DVar2 = DVar2 + (int)(((uint64_t)DVar1 & 0xffffffff) % 0x3c) * 1000;
		pUnit->dwTickCount = DVar2;
	}
	return D2C_ZEXT(1);
}

//D2Client.0x6FB48350
// TODO: decompilation needs review (extraout, in_reg)
uint32_t __fastcall sub_6FB48350(D2UnitStrc* pUnit)
{
	int in_EAX;
	int extraout_EAX;

	if ((pUnit->dwAnimMode == 1) &&
	    (in_EAX = pUnit->nSeqCurrentFramePrecise,
	        in_EAX == (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12a) * 0x100))
	{
		pUnit->dwAnimMode = 2;
		pUnit->nSeqCurrentFramePrecise = 0;
		sub_6FB5C080(pUnit);
		UNITS_SetAnimStartFrame(pUnit);
		in_EAX = extraout_EAX;
	}
	return CONCAT31((int32_t)((uint32_t)in_EAX >> 8), 1);
}

//D2Client.0x6FB48390
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB48390(int* a1)
{
	char cVar1;
	uint32_t extraout_var;
	uint32_t uVar2;
	int iVar3;
	int iVar4;

	cVar1 = sub_6FB06EE0();
	uVar2 = D2C_ZEXT(cVar1);
	if (cVar1 != '\0')
	{
		uVar2 = sub_6FB06EF0();
		if ((char)uVar2 == '\0')
		{
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
			iVar4 = *a1;
			if ((iVar4 != 2) && ((iVar4 < 4 || (5 < iVar4))))
			{
				if ((D2DynamicPathStrc*)a1[0xb] != nullptr)
				{
					iVar4 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
					uVar2 = sub_6FB06F20(iVar4, iVar3);
					return D2C_ZEXT(1);
				}
				uVar2 = sub_6FB06F20(0, iVar3);
				return D2C_ZEXT(1);
			}
			uVar2 = sub_6FB06F20(*(int*)(a1[0xb] + 0xc), iVar3);
		}
	}
	return D2C_ZEXT(1);
}

//D2Client.0x6FB48430
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB48430(D2UnitStrc* pUnit)
{
	uint8_t bVar1;
	uint64_t DVar2;
	char cVar3;
	uint32_t extraout_EAX;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	D2BitBufferStrc* pDVar6;
	D2UnitStrc* pDVar7;
	DWORD DVar8;
	uint32_t extraout_EAX_00;
	uint32_t extraout_var;
	uint32_t uVar9;
	int32_t DVar10;
	int iVar11;
	D2ObjectsTxt* pDVar12;
	int iVar13;

	pDVar12 = DATATBLS_GetObjectsTxtRecord(pUnit->dwClassId);
	bVar1 = pDVar12->nClientFn;
	D2_ASSERT(0x12 >= bVar1);
	if (bVar1 != 0)
	{
		uVar9 = (uint32_t)bVar1;
		switch (uVar9)
		{
		default:
			return 1;
		case 2:
			if (pUnit->dwFlagEx == 0)
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwTickCount = (*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 0x3f;
				pUnit->dwFlagEx = 1;
			}
			if (((pUnit->dwTickCount & 0x3f) == 0) && (pUnit->dwAnimMode != 1))
			{
				pUnit->dwAnimMode = 1;
				UNITS_SetAnimStartFrame(pUnit);
			}
			uVar9 = pUnit->dwAnimMode;
			pUnit->dwTickCount = pUnit->dwTickCount + 1;
			if (uVar9 == 2)
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwAnimMode = 0;
				pUnit->dwTickCount = pUnit->dwTickCount + ((*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 0x3f);
				UNITS_SetAnimStartFrame(pUnit);
				uVar9 = extraout_EAX;
			}
			return D2C_ZEXT(1);
		case 3:
			if (pUnit->dwFlagEx == 0)
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwTickCount = (*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 0x3f;
				pUnit->dwFlagEx = 1;
			}
			if (((pUnit->dwTickCount & 0x3f) == 0) && (pUnit->dwAnimMode != 1))
			{
				pUnit->dwAnimMode = 1;
				UNITS_SetAnimStartFrame(pUnit);
			}
			pUnit->dwTickCount = pUnit->dwTickCount + 1;
			if (pUnit->dwAnimMode == 2)
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwAnimMode = 0;
				pUnit->dwTickCount = pUnit->dwTickCount + ((*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 0x3f);
				UNITS_SetAnimStartFrame(pUnit);
			}
			uVar4 = sub_6FB50370(pUnit);
			return CONCAT31((int32_t)((uint32_t)uVar4 >> 8), 1);
		case 4:
			DVar8 = GetTickCount();
			if (pUnit->dwTickCount < DVar8)
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwTickCount = (int)(((uint64_t)DVar2 & 0xffffffff) % 5000) + 7000 + DVar8;
				pUnit->nSeqCurrentFramePrecise =
				    (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12e);
				UNITS_ChangeAnimMode(pUnit, 3);
				sub_6FB5C080(pUnit);
			}
			if ((pUnit->dwAnimMode == 3) &&
			    (iVar11 = *(int*)pUnit->pPlayerData->szName,
			        *(int*)(iVar11 + 0xe4) + -0x100 <= pUnit->nSeqCurrentFramePrecise))
			{
				pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar11 + 0x129);
				UNITS_ChangeAnimMode(pUnit, 0);
				sub_6FB5C080(pUnit);
			}
			uVar9 = sub_6FB50370(pUnit);
			return uVar9 & 0xffffff00;
		case 5:
			DVar8 = GetTickCount();
			if (pUnit->dwTickCount < DVar8)
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwTickCount = (int)(((uint64_t)DVar2 & 0xffffffff) % 10000) + 23000 + DVar8;
				pUnit->nSeqCurrentFramePrecise =
				    (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12e);
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				if (((uint64_t)DVar2 & 1) == 0)
				{
					iVar11 = 4;
				}
				else
				{
					iVar11 = 3;
				}
				UNITS_ChangeAnimMode(pUnit, iVar11);
				sub_6FB5C080(pUnit);
			}
			uVar9 = pUnit->dwAnimMode;
			if (((uVar9 == 3) || (uVar9 == 4)) &&
			    (iVar11 = *(int*)pUnit->pPlayerData->szName,
			        *(int*)(iVar11 + 0xd8 + uVar9 * 4) + -0x100 <= pUnit->nSeqCurrentFramePrecise))
			{
				pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar11 + 0x129);
				UNITS_ChangeAnimMode(pUnit, 0);
				sub_6FB5C080(pUnit);
			}
			uVar9 = sub_6FB50370(pUnit);
			return uVar9 & 0xffffff00;
		case 6:
			DVar8 = GetTickCount();
			if (pUnit->dwTickCount < DVar8)
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwTickCount = (int)(((uint64_t)DVar2 & 0xffffffff) % 10000) + 20000 + DVar8;
				pUnit->nSeqCurrentFramePrecise =
				    (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12e);
				UNITS_ChangeAnimMode(pUnit, 3);
				sub_6FB5C080(pUnit);
			}
			if ((2 < pUnit->dwAnimMode) &&
			    (iVar11 = *(int*)pUnit->pPlayerData->szName,
			        pUnit->nSeqCurrentFramePrecise ==
			            *(int*)(iVar11 + 0xd8 + pUnit->dwAnimMode * 4) + -0x100))
			{
				pUnit->nSeqCurrentFramePrecise = (uint32_t) * (uint8_t*)(iVar11 + 0x129);
				UNITS_ChangeAnimMode(pUnit, 0);
				sub_6FB5C080(pUnit);
			}
			uVar9 = sub_6FB50370(pUnit);
			return uVar9 & 0xffffff00;
		case 7:
			DVar8 = GetTickCount();
			pDVar7 = (D2UnitStrc*)pUnit->dwAnimMode;
			if (pDVar7 == nullptr)
			{
				if (pUnit->dwTickCount < DVar8)
				{
					pUnit->dwTickCount = DVar8 + 10000;
					pUnit->nSeqCurrentFramePrecise =
					    (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12a);
					UNITS_ChangeAnimMode(pUnit, 1);
					pDVar7 = sub_6FB5C080(pUnit);
					return CONCAT31((int32_t)((uint32_t)pDVar7 >> 8), 1);
				}
			}
			else if ((pDVar7 != nullptr) && (pUnit->dwTickCount < DVar8))
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwTickCount = (int)(((uint64_t)DVar2 & 0xffffffff) % 3000) + 0x1194 + DVar8;
				UNITS_ChangeAnimMode(pUnit, 0);
				pDVar7 = sub_6FB5C080(pUnit);
			}
			return CONCAT31((int32_t)((uint32_t)pDVar7 >> 8), 1);
		case 8:
			if ((pUnit != nullptr) && (uVar9 = pUnit->dwAnimMode, uVar9 != 0))
			{
				uVar9 = sub_6FB06E70();
			}
			return D2C_ZEXT(1);
		case 9:
			goto switchD_6fb48470_caseD_9;
		case 10:
			DVar8 = GetTickCount();
			pDVar7 = (D2UnitStrc*)pUnit->dwAnimMode;
			if (pDVar7 == nullptr)
			{
				if (pUnit->dwTickCount < DVar8)
				{
					pUnit->dwTickCount = DVar8 + 3000;
					pUnit->nSeqCurrentFramePrecise =
					    (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12a);
					UNITS_ChangeAnimMode(pUnit, 1);
					pDVar7 = sub_6FB5C080(pUnit);
					return CONCAT31((int32_t)((uint32_t)pDVar7 >> 8), 1);
				}
			}
			else if ((pDVar7 != nullptr) && (pUnit->dwTickCount < DVar8))
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				pUnit->dwTickCount = (int)(((uint64_t)DVar2 & 0xffffffff) % 5000) + 0x9c4 + DVar8;
				UNITS_ChangeAnimMode(pUnit, 0);
				pDVar7 = sub_6FB5C080(pUnit);
			}
			return CONCAT31((int32_t)((uint32_t)pDVar7 >> 8), 1);
		case 0xc:
			if ((pUnit != nullptr) && (uVar9 = pUnit->dwAnimMode, uVar9 != 0))
			{
				uVar9 = sub_6FB06E90();
			}
			return D2C_ZEXT(1);
		case 0xd:
			if ((pUnit == nullptr) ||
			    (pDVar7 = (D2UnitStrc*)pUnit->dwAnimMode,
			        (D2UnitStrc*)pUnit->dwAnimMode == nullptr))
			{
				pDVar5 = CUNIT_GetPlayer();
				pDVar7 = pDVar5;
				if (pDVar5 != nullptr)
				{
					iVar13 = 0;
					iVar11 = 0x27;
					pDVar6 = sub_6FAFBD20();
					pDVar7 = (D2UnitStrc*)QUESTRECORD_GetQuestState(pDVar6, iVar11, iVar13);
					if (pDVar7 != nullptr)
					{
						iVar13 = 4;
						iVar11 = 0x27;
						pDVar6 = sub_6FAFBD20();
						pDVar7 = (D2UnitStrc*)QUESTRECORD_GetQuestState(pDVar6, iVar11, iVar13);
						if (pDVar7 == nullptr)
						{
							pDVar7 = CUNIT_GetPlayer();
							pDVar7 = (D2UnitStrc*)UNITS_GetDistanceToOtherUnit(pUnit, pDVar7);
							if ((int)pDVar7 < 0x19)
							{
								if (pDVar5->pDynamicPath != nullptr)
								{
									D2Common_10153(pDVar5->pDynamicPath);
								}
								sub_6FB4EA90(0x13, pDVar5, 2, pUnit->dwUnitId, 0);
								UNITS_ChangeAnimMode(pUnit, 2);
								pDVar7 = sub_6FB5C080(pUnit);
							}
						}
					}
				}
			}
			return CONCAT31((int32_t)((uint32_t)pDVar7 >> 8), 1);
		case 0xe:
			DVar8 = GetTickCount();
			if (pUnit->dwTickCount < DVar8)
			{
				sub_6FB467E0(pUnit, 0);
				DVar8 = GetTickCount();
				DVar8 = DVar8 + 500;
				pUnit->dwTickCount = DVar8;
			}
			return D2C_ZEXT(1);
		case 0xf:
			DVar8 = GetTickCount();
			if (pUnit->dwTickCount < DVar8)
			{
				if (pUnit->dwAnimMode == 0)
				{
					sub_6FB5BA70(pUnit, 0x48, 3, 0, 0, 0, 0, 0);
					DVar8 = GetTickCount();
					pUnit->dwTickCount = DVar8 + 500;
					return CONCAT31((int32_t)(DVar8 + 500 >> 8), 1);
				}
				sub_6FB5BEC0(pUnit, 0, 0x48);
				DVar8 = GetTickCount();
				DVar8 = DVar8 + 500;
				pUnit->dwTickCount = DVar8;
			}
			return D2C_ZEXT(1);
		case 0x10:
			if ((pUnit->dwAnimMode == 1) &&
			    (uVar9 = pUnit->nSeqCurrentFramePrecise,
			        uVar9 == (uint32_t) * (uint8_t*)(*(int*)pUnit->pPlayerData->szName + 0x12a) * 0x100))
			{
				pUnit->dwAnimMode = 2;
				pUnit->nSeqCurrentFramePrecise = 0;
				sub_6FB5C080(pUnit);
				UNITS_SetAnimStartFrame(pUnit);
				uVar9 = extraout_EAX_00;
			}
			return D2C_ZEXT(1);
		case 0x11:
			cVar3 = sub_6FB06EE0();
			uVar9 = D2C_ZEXT(cVar3);
			if (cVar3 != '\0')
			{
				uVar9 = sub_6FB06EF0();
				if ((char)uVar9 == '\0')
				{
					uVar9 = pUnit->dwUnitType;
					if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
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
					uVar9 = pUnit->dwUnitType;
					if ((uVar9 != 2) && (((int)uVar9 < 4 || (5 < (int)uVar9))))
					{
						if (pUnit->pDynamicPath != nullptr)
						{
							iVar11 = PATH_GetXPosition(pUnit->pDynamicPath);
							uVar9 = sub_6FB06F20(iVar11, (int)DVar10);
							return D2C_ZEXT(1);
						}
						uVar9 = sub_6FB06F20(0, (int)DVar10);
						return D2C_ZEXT(1);
					}
					uVar9 = sub_6FB06F20(pUnit->pDynamicPath->dwClientCoordY, (int)DVar10);
				}
			}
			return D2C_ZEXT(1);
		case 0x12:
			DVar8 = GetTickCount();
			if (pUnit->dwTickCount < DVar8)
			{
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				if ((uint32_t)(((uint64_t)DVar2 & 0xffffffff) % 100) < 10)
				{
					sub_6FB55820(0x9c9, pUnit, 0.0, 0.0, 0);
				}
				DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar2;
				DVar8 = GetTickCount();
				DVar8 = DVar8 + (int)(((uint64_t)DVar2 & 0xffffffff) % 0x3c) * 1000;
				pUnit->dwTickCount = DVar8;
			}
			return D2C_ZEXT(1);
		}
	}
	return CONCAT31((int32_t)((uint32_t)pDVar12 >> 8), 1);
switchD_6fb48470_caseD_9:
	DVar8 = GetTickCount();
	uVar9 = pUnit->dwTickCount;
	if (uVar9 != 0)
	{
		if (DVar8 - uVar9 < 0x3e9)
			goto LAB_6fb4815b;
		pDVar7 = CUNIT_GetPlayer();
		uVar9 = UNITS_GetDistanceToOtherUnit(pUnit, pDVar7);
		if (0x19 < (int)uVar9)
		{
			uVar9 = sub_6FB26C70(pUnit->dwUnitId, 2);
			return uVar9 & 0xffffff00;
		}
	}
	pUnit->dwTickCount = DVar8;
LAB_6fb4815b:
	return D2C_ZEXT(1);
}

//D2Client.0x6FB48480
void __fastcall sub_6FB48480(int ptCmd)
{
	uint8_t nPortalFlag;
	D2UnitStrc* pUnit;

	D2_ASSERT(ptCmd);
	pUnit = sub_6FB269F0(*(uint32_t*)(ptCmd + 3), 2);
	if (pUnit != nullptr)
	{
		D2_ASSERT(!((pUnit->dwClassId != 0x3b) && (pUnit->dwClassId != 0x3c)));
		pUnit->pPlayerData->szName[4] = *(char*)(ptCmd + 2);
		nPortalFlag = UNITS_GetObjectPortalFlags(pUnit);
		if ((*(uint8_t*)(ptCmd + 1) & 2) != 0)
		{
			nPortalFlag = nPortalFlag | 2;
		}
		if ((*(uint8_t*)(ptCmd + 1) & 1) != 0)
		{
			nPortalFlag = nPortalFlag | 1;
		}
		UNITS_SetObjectPortalFlags(pUnit, nPortalFlag);
	}
}

//D2Client.0x6FB48550
int __fastcall sub_6FB48550(int a1)
{
	return *(int*)(a1 + 0x14) + 0x28;
}

//D2Client.0x6FB48560
void __fastcall sub_6FB48560(int a1, char* a2)
{
	SStrCopy((char*)(*(int*)(a1 + 0x14) + 0x28), a2, 0x10);
}
