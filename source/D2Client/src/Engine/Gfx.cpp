#include "Engine/Gfx.h"

#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Draw/DLightMap.h"
#include "Engine/GfxUtil.h"
#include "Engine/Particle.h"
#include "Game/Game.h"
#include "Game/PalShift.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Player.h"
#include "Unit/UnitGfx.h"

//D2Client.0x6FB96E08
uint32_t dword_6FB96E08 = 5;
//D2Client.0x6FB96E28
uint32_t dword_6FB96E28 = 8;
//D2Client.0x6FB96E2C
uint32_t dword_6FB96E2C = 0xC;
//D2Client.0x6FB96E68
uint32_t dword_6FB96E68 = 0xF;
//D2Client.0x6FB96E6C
uint8_t* gpuint8_t_6FB96E6C = (uint8_t*)"cmncof_a1.d2";
//D2Client.0x6FB96E80
uint32_t dword_6FB96E80 = 0x20206867;
//D2Client.0x6FB96E84
uint32_t dword_6FB96E84 = 0xD;
//D2Client.0x6FB96E88
uint32_t dword_6FB96E88 = 1;
//D2Client.0x6FBC1B08
uint32_t dword_6FBC1B08;
//D2Client.0x6FBC1B0C
uint8_t* ptr_6FBC1B0C;
//D2Client.0x6FBC1B10
int32_t dword_6FBC1B10;
//D2Client.0x6FBC1B14
uint32_t dword_6FBC1B14;
//D2Client.0x6FBC2318
uint32_t dword_6FBC2318;
//D2Client.0x6FBC2368
uint8_t byte_6FBC2368[1040];
//D2Client.0x6FBC2778
uint32_t dword_6FBC2778;
//D2Client.0x6FBC277C
uint8_t* ptr_6FBC277C;
//D2Client.0x6FBC2780
int32_t dword_6FBC2780;
//D2Client.0x6FBC2784
uint32_t dword_6FBC2784;
//D2Client.0x6FBC2F84
int32_t dword_6FBC2F84;
//D2Client.0x6FBC2F88
uint8_t byte_6FBC2F88;
//D2Client.0x6FBC2F89
uint8_t byte_6FBC2F89;
//D2Client.0x6FBC2F8A
uint8_t byte_6FBC2F8A;
//D2Client.0x6FBC2F8B
uint8_t byte_6FBC2F8B;
//D2Client.0x6FBC2F8C
DWORD dword_6FBC2F8C;
//D2Client.0x6FBC2F90
uint32_t dword_6FBC2F90;
//D2Client.0x6FBC2F94
int32_t dword_6FBC2F94;
//D2Client.0x6FBC2F98
uint32_t dword_6FBC2F98;
//D2Client.0x6FBC2F9C
int32_t dword_6FBC2F9C;
//D2Client.0x6FBC2FA0
int32_t dword_6FBC2FA0;
//D2Client.0x6FBC2FA4
int32_t dword_6FBC2FA4;

//D2Client.0x6FB57CD0
uint32_t __fastcall sub_6FB57CD0(int a1, int a2)
{
	int iVar1;

	iVar1 = sub_6FB28400(a1);
	D2_ASSERT(iVar1);
	iVar1 = *(int*)(iVar1 + 0x2c);
	while (true)
	{
		if (iVar1 == 0)
		{
			return 0;
		}
		if (*(int*)(iVar1 + 4) == a2)
			break;
		iVar1 = *(int*)(iVar1 + 0xa4);
	}
	return 1;
}

//D2Client.0x6FB57D20
void __fastcall sub_6FB57D20(D2UnitStrc* pUnit, int a2, int a3, int a4)
{
	int* piVar1;
	int iVar2;
	uint8_t bVar3;
	int iVar4;
	int iVar5;
	D2GfxDataStrc* pDVar6;
	bool bVar7;
	D2CellFileStrc* pDVar8;
	D2InventoryStrc** ppDVar9;
	uint8_t uVar10;
	D2InventoryStrc* pDVar11;
	int local_58;
	D2InventoryStrc* local_4c;
	D2GfxDataStrc local_48;

	iVar4 = sub_6FB28400((int)pUnit);
	if ((iVar4 != 0) && (piVar1 = *(int**)(iVar4 + 0x2c), piVar1 != nullptr))
	{
		local_58 = 0;
		do
		{
			for (; piVar1 != nullptr; piVar1 = (int*)piVar1[0x29])
			{
				bVar7 = true;
				if (((piVar1[0xd] == 0) || (bVar7 = local_58 != 0, piVar1[0xd] == 0)) && (local_58 != 0))
				{
					bVar7 = false;
				}
				if ((*piVar1 == 6) && (piVar1[2] == 0))
				{
					bVar7 = false;
				}
				if ((*piVar1 == 8) && (piVar1[0xf] == 0))
				{
					bVar7 = false;
				}
				iVar4 = piVar1[1];
				if ((iVar4 == a2) && (bVar7))
				{
					iVar2 = piVar1[6];
					if (iVar4 < 0)
					{
						return;
					}
					if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0) <= iVar4)
					{
						return;
					}
					iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbbc) + iVar4 * 0x84;
					if (iVar4 == 0)
					{
						return;
					}
					pDVar11 = (D2InventoryStrc*)0xffffffff;
					ppDVar9 = &local_4c;
					uVar10 = 1;
					pDVar6 = &local_48;
					for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
					{
						pDVar6->pCurrentCell = nullptr;
						pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
					}
					pDVar8 = (D2CellFileStrc*)(iVar2 >> 8);
					local_48.nOverlay = a2;
					bVar3 = UNITS_GetDirection(pUnit);
					iVar5 = sub_6FB5EC80((int)&local_48, nullptr, 0, (D2CellFileStrc*)(uint32_t)bVar3,
					    pDVar8, ppDVar9, uVar10, pDVar11);
					if (iVar5 == 0)
					{
						return;
					}
					if (iVar2 >> 8 < piVar1[7] >> 8)
					{
						TEXTURE_CelDraw(&local_48, piVar1[8] + a3, piVar1[9] + a4, 0xffffff80,
						    (DrawMode)((uint32_t) * (uint8_t*)(iVar4 + 0x7c)), nullptr);
					}
				}
			}
			local_58 = local_58 + 1;
		} while (local_58 < 2);
	}
}

//D2Client.0x6FB57E80
void __fastcall sub_6FB57E80(D2UnitStrc* pUnit)
{
	int* piVar1;
	uint32_t nState;
	int iVar2;
	DWORD DVar3;
	int iVar4;
	bool bVar5;
	int iStack_18;
	int local_14;
	DWORD DStack_10;
	int iStack_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	local_14 = sub_6FB28400((int)pUnit);
	D2_ASSERT(local_14);
	DStack_10 = GetTickCount();
switchD_6fb57f87_default:
	iVar2 = local_14;
	piVar1 = *(int**)(local_14 + 0x2c);
	while (true)
	{
		if (piVar1 == nullptr)
		{
			return;
		}
		if (piVar1[0xb] != DStack_10)
			break;
		piVar1 = (int*)piVar1[0x29];
	}
	piVar1[0xb] = DStack_10;
	switch (*piVar1)
	{
	case 0:
		if ((pUnit == nullptr) || (uStack_4 = pUnit->dwFlagEx >> 3 & 1, uStack_4 == 0))
		{
			iVar2 = UNITS_GetAnimOrSeqMode(pUnit);
			bVar5 = iVar2 == piVar1[2];
		}
		else
		{
			uStack_8 = pUnit->dwUnitType;
			iStack_c = pUnit->dwClassId;
			iStack_18 = UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_8, &iStack_c, &iStack_18, __FILE__, __LINE__);
			bVar5 = iStack_18 == piVar1[2];
		}
		goto LAB_6fb57fa0;
	case 1:
		bVar5 = piVar1[2] != 0;
		piVar1[2] = piVar1[2] + -1;
	LAB_6fb57fa0:
		if (bVar5)
			break;
	LAB_6fb57fa2:
		sub_6FB58270((int)pUnit, piVar1);
		goto switchD_6fb57f87_default;
	case 2:
		if (piVar1[2] != 0)
			break;
		goto LAB_6fb57fa2;
	case 6:
		if (piVar1[2] != 0)
			break;
		DVar3 = GetTickCount();
		if (DVar3 - piVar1[0xc] < (uint32_t)piVar1[10])
			goto switchD_6fb57f87_default;
		piVar1[2] = 1;
		break;
	case 8:
		iVar4 = STATES_CheckState(pUnit, piVar1[0xe]);
		if (iVar4 == 0)
			goto LAB_6fb57fa2;
		if (piVar1[0xf] != 0)
		{
			if (piVar1[2] < 0x32)
			{
				piVar1[2] = piVar1[2] + 1;
			}
			else
			{
				sub_6FB58170(pUnit, iVar2, (int)piVar1);
			}
		}
	}
	iVar2 = piVar1[7];
	iVar4 = piVar1[6] + piVar1[5];
	piVar1[6] = iVar4;
	if (iVar2 <= iVar4)
	{
		switch (*piVar1)
		{
		case 1:
		case 3:
		case 8:
			piVar1[6] = iVar4 - iVar2;
			break;
		case 2:
			piVar1[2] = 0;
			break;
		case 4:
			iVar2 = piVar1[2];
			iVar4 = piVar1[3];
			sub_6FB58270((int)pUnit, piVar1);
			if (iVar2 != -1)
			{
				sub_6FB5BA70(pUnit, iVar2, 3, 0, 0, 0, 0, 0);
			}
			if (iVar4 != -1)
			{
				sub_6FB5BA70(pUnit, iVar4, 3, 0, 0, 0, 0, 0);
			}
			break;
		case 5:
			piVar1[5] = 0;
			piVar1[6] = iVar2 + -1;
			piVar1[2] = 1;
			break;
		case 6:
			piVar1[2] = 0;
			piVar1[6] = iVar4 - iVar2;
			DVar3 = GetTickCount();
			piVar1[0xc] = DVar3;
			break;
		case 7:
			sub_6FB58270((int)pUnit, piVar1);
			sub_6FB5BA70(pUnit, 0x8c, 4, 0, 0x8d, 0x8e, 0, 0);
			break;
		case 9:
			uStack_4 = piVar1[3];
			iVar2 = piVar1[2];
			nState = piVar1[4];
			sub_6FB58270((int)pUnit, piVar1);
			iVar4 = STATES_CheckState(pUnit, nState);
			if (iVar4 != 0)
			{
				if (iVar2 != -1)
				{
					sub_6FB5BA70(pUnit, iVar2, 8, 0, nState, 0, 0, 0);
				}
				if (uStack_4 != 0xffffffff)
				{
					sub_6FB5BA70(pUnit, uStack_4, 8, 0, nState, 0, 0, 0);
				}
			}
		}
	}
	goto switchD_6fb57f87_default;
}

//D2Client.0x6FB58170
void __fastcall sub_6FB58170(D2UnitStrc* pUnit, int a2, int a3)
{
	int nState;
	int* piVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int* piVar5;

	nState = *(int*)(a3 + 0x38);
	iVar2 = STATES_CheckState(pUnit, nState);
	if (iVar2 != 0)
	{
		STATES_ToggleState(pUnit, nState, 0);
	}
	iVar3 = STATES_CheckStateMaskAuraOnUnit(pUnit);
	if (iVar3 == 0)
	{
		*(uint32_t*)(a3 + 8) = 0;
		if (iVar2 != 0)
		{
			STATES_ToggleState(pUnit, nState, 1);
			goto LAB_6fb581c1;
		}
	}
	else
	{
	LAB_6fb581c1:
		if (iVar2 != 0)
		{
			STATES_ToggleState(pUnit, nState, 1);
		}
	}
	for (piVar5 = *(int**)(a2 + 0x2c); piVar5 != nullptr; piVar5 = (int*)piVar5[0x29])
	{
		if ((piVar5[0xe] == nState) && (*piVar5 == 8))
		{
			piVar5[0xf] = 0;
			piVar5[2] = -1;
		}
	}
	piVar1 = *(int**)(a2 + 0x2c);
	iVar2 = 0;
	iVar3 = 0;
	piVar5 = piVar1;
	if (piVar1 != nullptr)
	{
		do
		{
			if (*piVar5 == 8)
			{
				if (((iVar2 == 0) || (iVar4 = piVar5[0xe], iVar4 < iVar2)) &&
				    (iVar4 = piVar5[0xe], nState < iVar4))
				{
					iVar2 = iVar4;
				}
				if ((iVar3 == 0) || (iVar4 < iVar3))
				{
					iVar3 = iVar4;
				}
			}
			piVar5 = (int*)piVar5[0x29];
		} while (piVar5 != nullptr);
		if (iVar2 != 0)
			goto joined_r0x6fb5823a;
	}
	iVar2 = iVar3;
joined_r0x6fb5823a:
	for (; piVar1 != nullptr; piVar1 = (int*)piVar1[0x29])
	{
		if ((piVar1[0xe] == iVar2) && (*piVar1 == 8))
		{
			piVar1[0xf] = 1;
			piVar1[2] = 0;
		}
	}
}

//D2Client.0x6FB58270
void __fastcall sub_6FB58270(int a1, int* a2)
{
	int* piVar1;
	int iVar2;
	int* pFree;
	int* piVar3;

	iVar2 = sub_6FB28400(a1);
	D2_ASSERT(iVar2);
	piVar1 = *(int**)(iVar2 + 0x2c);
	piVar3 = nullptr;
	if (*(int**)(iVar2 + 0x2c) != nullptr)
	{
		while (pFree = piVar1, pFree != a2)
		{
			piVar1 = (int*)pFree[0x29];
			piVar3 = pFree;
			if ((int*)pFree[0x29] == nullptr)
			{
				return;
			}
		}
		if (pFree != nullptr)
		{
			if (pFree[0x10] != 0)
			{
				sub_6FAA44D0(pFree[0x10]);
				pFree[0x10] = 0;
			}
			if (piVar3 == nullptr)
			{
				*(int*)(iVar2 + 0x2c) = pFree[0x29];
			}
			else
			{
				piVar3[0x29] = pFree[0x29];
			}
			if (*pFree == 8)
			{
				sub_6FB58170((D2UnitStrc*)(a1), iVar2, (int)pFree);
			}
			D2_FREE(pFree);
		}
	}
}

//D2Client.0x6FB58320
uint32_t __fastcall sub_6FB58320(int a1, int a2)
{
	int* piVar1;
	int iVar2;

	iVar2 = sub_6FB28400(a1);
	if (iVar2 != 0)
	{
		for (piVar1 = *(int**)(iVar2 + 0x28); piVar1 != nullptr; piVar1 = (int*)piVar1[4])
		{
			if (*piVar1 == a2)
			{
				return *(uint32_t*)(piVar1[2] + 0x14);
			}
		}
	}
	return 0;
}

//D2Client.0x6FB58350
uint32_t* __fastcall sub_6FB58350(D2UnitStrc* pUnit, int a2, uint32_t* a3)
{
	int* piVar1;
	int iVar2;
	int local_8;
	uint32_t local_4;

	iVar2 = sub_6FB28400((int)pUnit);
	D2_ASSERT(iVar2);
	if (a3 == (uint32_t*)0xffffffff)
	{
		if ((pUnit == nullptr) ||
		    (a3 = (uint32_t*)(pUnit->dwFlagEx >> 3 & 1), a3 == nullptr))
		{
			a3 = (uint32_t*)UNITS_GetAnimOrSeqMode(pUnit);
		}
		else
		{
			local_4 = pUnit->dwUnitType;
			local_8 = pUnit->dwClassId;
			a3 = (uint32_t*)UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&local_4, &local_8, (int*)&a3, __FILE__, __LINE__);
		}
	}
	piVar1 = *(int**)(iVar2 + 0x28);
	while (true)
	{
		if (piVar1 == nullptr)
		{
			return nullptr;
		}
		if (((uint32_t*)*piVar1 == a3) && (piVar1[1] == a2))
			break;
		piVar1 = (int*)piVar1[4];
	}
	return (uint32_t*)(piVar1);
}

//D2Client.0x6FB58410
// TODO: decompilation needs review (extraout)
uint32_t* __fastcall sub_6FB58410(D2UnitStrc* pUnit, uint32_t a2, D2InventoryStrc* pInventory)
{
	bool bVar1;
	int iVar2;
	D2InventoryStrc* pDVar3;
	int* piVar4;
	uint32_t extraout_var;
	uint32_t* puVar5;
	int iVar6;
	D2InventoryStrc* pDVar7;
	D2InventoryStrc* pDStack_18;
	D2InventoryStrc* local_14;
	uint32_t uStack_10;
	int local_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	local_14 = (D2InventoryStrc*)0x6;
	if (pUnit == nullptr)
	{
		local_c = -1;
	}
	else
	{
		local_14 = (D2InventoryStrc*)pUnit->dwUnitType;
		local_c = pUnit->dwClassId;
	}
	pDStack_18 = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_14, &local_c, (int*)&pDStack_18,
	    __FILE__, __LINE__);
	pDVar3 = pInventory;
	if (pInventory == (D2InventoryStrc*)0xffffffff)
	{
		pDVar3 = pDStack_18;
	}
	if (local_14 == (D2InventoryStrc*)0x1)
	{
		uStack_8 = 6;
		if (pUnit == nullptr)
		{
			uStack_10 = 0xffffffff;
		}
		else
		{
			uStack_8 = pUnit->dwUnitType;
			uStack_10 = pUnit->dwClassId;
		}
		pInventory = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_8, (int*)&uStack_10, (int*)&pInventory,
		    __FILE__, __LINE__);
		pDVar7 = pDVar3;
		if (pDVar3 == (D2InventoryStrc*)0xe)
		{
			pDVar7 = pInventory;
		}
		iVar2 = sub_6FB247F0(uStack_10);
		if ((iVar2 != 0) &&
		    (uStack_4 = (uint32_t) * (uint8_t*)(((int)pDVar7 >> 3) + 0xf0 + iVar2) &
		                *(uint32_t*)(((uint8_t*)&gdwBitMasks) + ((uint32_t)pDVar7 & 7) * 4),
		        uStack_4 != 0))
		{
			if (pDVar7 == (D2InventoryStrc*)((uint8_t*)0x0c))
			{
				sub_6FB593C0((int)pUnit);
				iVar2 = sub_6FB28400((int)pUnit);
				D2_ASSERT(iVar2);
				iVar6 = 0;
				do
				{
					*(uint8_t*)(iVar2 + iVar6 * 2) = 0;
					iVar6 = iVar6 + 1;
				} while (iVar6 < 0x14);
				pDVar7 = (D2InventoryStrc*)((uint8_t*)0x0c);
			}
			else if (pDVar7 == (D2InventoryStrc*)0xe)
			{
				pDVar7 = pInventory;
			}
			sub_6FB58E40(pUnit, (uint32_t)pDVar7);
		}
		iVar2 = sub_6FB28400((int)pUnit);
		D2_ASSERT(iVar2);
		if (pDVar3 == (D2InventoryStrc*)0xffffffff)
		{
			if ((pUnit == nullptr) ||
			    (pInventory = (D2InventoryStrc*)(pUnit->dwFlagEx >> 3 & 1),
			        pInventory == nullptr))
			{
				pDVar3 = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
			}
			else
			{
				uStack_10 = pUnit->dwUnitType;
				uStack_8 = pUnit->dwClassId;
				pInventory = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
				D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_10, (int*)&uStack_8, (int*)&pInventory,
				    __FILE__, __LINE__);
				pDVar3 = pInventory;
			}
		}
		for (puVar5 = *(uint32_t**)(iVar2 + 0x28); puVar5 != nullptr; puVar5 = (uint32_t*)puVar5[4])
		{
			if (((D2InventoryStrc*)*puVar5 == pDVar3) && (puVar5[1] == a2))
			{
				return puVar5;
			}
		}
	}
	else if (local_14 == nullptr)
	{
		pInventory = local_14;
		piVar4 = sub_6FB58720(pUnit, (int)&pInventory, (int)pDVar3);
		if (piVar4 != nullptr)
		{
			sub_6FB5F070((int)pUnit, (int)pDVar3, 1);
		}
		iVar2 = sub_6FB28400((int)pUnit);
		D2_ASSERT(iVar2);
		bVar1 = sub_6FB5BEA0((int)pUnit, 8);
		if (D2C_ZEXT(bVar1) == 0)
		{
			pInventory = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
		}
		else
		{
			uStack_10 = 6;
			if (pUnit == nullptr)
			{
				uStack_8 = 0xffffffff;
			}
			else
			{
				uStack_10 = pUnit->dwUnitType;
				uStack_8 = pUnit->dwClassId;
			}
			pInventory = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_10, (int*)&uStack_8, (int*)&pInventory,
			    __FILE__, __LINE__);
		}
		puVar5 = *(uint32_t**)(iVar2 + 0x28);
		if (puVar5 != nullptr)
		{
			while (((D2InventoryStrc*)*puVar5 != pInventory || (puVar5[1] != a2)))
			{
				puVar5 = (uint32_t*)puVar5[4];
				if (puVar5 == nullptr)
				{
					return nullptr;
				}
			}
			return puVar5;
		}
	}
	else if (local_14 == (D2InventoryStrc*)0x2)
	{
		sub_6FB58F90(pUnit, (int)pDVar3);
		puVar5 = sub_6FB58350(pUnit, a2, (uint32_t*)0xffffffff);
		return puVar5;
	}
	return nullptr;
}

//D2Client.0x6FB58720
// TODO: decompilation needs review (extraout)
int* __fastcall sub_6FB58720(D2UnitStrc* pUnit, int a2, int a3)
{
	char cVar1;
	uint32_t* puVar2;
	bool bVar3;
	D2UnitStrc* pDVar4;
	D2InventoryStrc* pInventory;
	uint32_t extraout_var;
	uint32_t uVar5;
	int* piVar6;
	uint32_t uVar7;
	uint32_t* puVar8;
	int iVar9;
	uint32_t* puVar10;
	char* pcVar11;
	uint32_t uStack_224;
	uint32_t* local_220;
	uint32_t uStack_21c;
	uint32_t local_218;
	uint32_t local_214;
	int iStack_210;
	uint32_t uStack_20c;
	uint8_t auStack_208[3];
	uint8_t uStack_205;
	int iStack_204;
	char local_104;
	uint32_t local_103;

	local_104 = '\0';
	puVar10 = &local_103;
	for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1)
	{
		*puVar10 = 0;
		puVar10 = puVar10 + 1;
	}
	*(uint16_t*)puVar10 = 0;
	local_218 = 0;
	*(uint8_t*)((int)puVar10 + 2) = 0;
	local_220 = (uint32_t*)a2;
	iVar9 = sub_6FB5F030((int*)pUnit);
	if (iVar9 != 0)
	{
		if ((((pUnit == nullptr) || (local_214 = pUnit->dwFlagEx >> 3 & 1, local_214 == 0)) || (iVar9 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar9 == 0)) ||
		    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 == nullptr))
		{
			pInventory = pUnit->pInventory;
		}
		else
		{
			pInventory = pDVar4->pInventory;
		}
		D2Common_10885_COMPOSIT_unk(pUnit, &local_104, (int*)&local_218, 1, 1, pInventory, a3);
		if ((local_104 != '\0') && (local_214 = sub_6FB28400((int)pUnit), local_214 != 0))
		{
			uStack_21c = local_218;
			iVar9 = sub_6FB28400((int)pUnit);
			D2_ASSERT(iVar9);
			uVar5 = a3;
			if (a3 == -1)
			{
				bVar3 = sub_6FB5BEA0((int)pUnit, 8);
				if (D2C_ZEXT(bVar3) == 0)
				{
					uVar5 = UNITS_GetAnimOrSeqMode(pUnit);
				}
				else
				{
					uStack_20c = pUnit->dwUnitType;
					iStack_210 = pUnit->dwClassId;
					uStack_224 = UNITS_GetAnimOrSeqMode(pUnit);
					D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_20c, &iStack_210, (int*)&uStack_224,
					    __FILE__, __LINE__);
					uVar5 = uStack_224;
				}
			}
			for (puVar2 = *(uint32_t**)(iVar9 + 0x28); puVar2 != nullptr; puVar2 = (uint32_t*)puVar2[4])
			{
				if (*puVar2 == uVar5)
				{
					if (puVar2[1] == uStack_21c)
						goto LAB_6fb58a7a;
					uVar7 = sub_6FB58320((int)pUnit, uVar5);
					*local_220 = uVar7;
					iVar9 = sub_6FB58DC0((int)pUnit, puVar2[2]);
					D2_ASSERT(iVar9);
					break;
				}
			}
			piVar6 = (int*)D2_ALLOC(0x14);
			if (piVar6 == nullptr)
			{
				FOG_DisplayAssert("ptUnitCofNode", __FILE__, __LINE__);
				exit(-1);
			}
			*piVar6 = 0;
			piVar6[1] = 0;
			piVar6[2] = 0;
			piVar6[3] = 0;
			piVar6[4] = 0;
			local_220 = (uint32_t*)(pUnit->dwFlagEx >> 3 & 1);
			uVar5 = pUnit->dwUnitType;
			if (local_220 != nullptr)
			{
				uStack_21c = pUnit->dwClassId;
				uStack_224 = pUnit->dwUnitType;
				local_220 = (uint32_t*)UNITS_GetAnimOrSeqMode(pUnit);
				D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_224, (int*)&uStack_21c, (int*)&local_220,
				    __FILE__, __LINE__);
				uVar5 = uStack_224;
			}
			puVar10 = &dword_6FBC1B08;
			if (uVar5 != 0)
			{
				puVar10 = &dword_6FBC2778;
			}
			(*(uint32_t*)&auStack_208) = (*(uint32_t*)&auStack_208) & 0xffffff00;
			puVar8 = (uint32_t*)((int)auStack_208 + 1);
			for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			*(uint16_t*)puVar8 = 0;
			*(uint8_t*)((int)puVar8 + 2) = 0;
			sub_6FB58AC0(&local_104, (char*)(auStack_208));
			_strlwr((char*)(auStack_208));
			uVar5 = 0xffffffff;
			pcVar11 = (char*)(auStack_208);
			do
			{
				if (uVar5 == 0)
					break;
				uVar5 = uVar5 - 1;
				cVar1 = *pcVar11;
				pcVar11 = pcVar11 + 1;
			} while (cVar1 != '\0');
			D2_ASSERT(7 >= ~uVar5 - 1);
			uVar5 = SStrHash((const char*)(auStack_208), 1, 0);
			for (puVar8 = (uint32_t*)
			         puVar10[(((uVar5 & 0x1ff0000 ^ uVar5 >> 8) >> 8 ^ uVar5 & 0x1ff00) >> 8 ^
			                     uVar5 & 0x1ff) +
			                 3];
			     puVar8 != nullptr;
			     puVar8 = (uint32_t*)*puVar8)
			{
				if (((*(uint32_t*)&auStack_208) == puVar8[3]) && (iStack_204 == puVar8[4]))
					goto LAB_6fb58a52;
			}
			puVar8 = sub_6FB58B10((int)puVar10, &local_104);
			if (puVar8 == nullptr)
			{
				FOG_Trace("Could not add cof file: %s", &local_104);
			}
			else
			{
			LAB_6fb58a52:
				*piVar6 = a3;
				piVar6[2] = (int)puVar8;
				piVar6[1] = local_218;
				piVar6[4] = *(int*)(local_214 + 0x28);
				*(int**)(local_214 + 0x28) = piVar6;
			LAB_6fb58a7a:
				iVar9 = sub_6FB28400((int)pUnit);
				if ((iVar9 != 0) && (piVar6 = *(int**)(iVar9 + 0x28), piVar6 != nullptr))
				{
					do
					{
						if (*piVar6 == a3)
						{
							return *(int**)(piVar6[2] + 0x14);
						}
						piVar6 = (int*)piVar6[4];
					} while (piVar6 != nullptr);
					return piVar6;
				}
			}
		}
	}
	return nullptr;
}

//D2Client.0x6FB58AC0
void __fastcall sub_6FB58AC0(char* a1, char* a2)
{
	char* pcVar1;
	char cVar2;
	char* pcVar3;
	uint32_t uVar4;
	int iVar5;

	uVar4 = 0xffffffff;
	pcVar3 = a1;
	do
	{
		if (uVar4 == 0)
			break;
		uVar4 = uVar4 - 1;
		cVar2 = *pcVar3;
		pcVar3 = pcVar3 + 1;
	} while (cVar2 != '\0');
	pcVar3 = a1 + (~uVar4 - 5);
	if (a1[~uVar4 - 5] == '.')
	{
		iVar5 = 0;
		cVar2 = *pcVar3;
		while (cVar2 != '\\')
		{
			pcVar1 = pcVar3 + -1;
			pcVar3 = pcVar3 + -1;
			iVar5 = iVar5 + 1;
			cVar2 = *pcVar1;
		}
		strncpy(a2, pcVar3 + 1, iVar5 - 1U);
		a2[iVar5 - 1U] = '\0';
	}
}

//D2Client.0x6FB58B10
// TODO: decompilation needs review (stack0x)
uint32_t* __fastcall sub_6FB58B10(int a1, char* a2)
{
	uint8_t stack0xfffffdf3[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	char* pcVar1;
	char cVar2;
	char* pcVar3;
	uint32_t* puVar4;
	HD2ARCHIVE__* pHVar5;
	D2CellFileStrc* pDVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t* puVar9;
	int* piVar10;
	uint32_t uVar11;
	uint32_t local_20c;
	char local_208;
	uint32_t local_207;
	char cStack_105;
	uint8_t local_104[3];
	uint8_t uStack_101;
	int iStack_100;

	local_208 = '\0';
	puVar9 = &local_207;
	for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar9 = 0;
		puVar9 = puVar9 + 1;
	}
	*(uint16_t*)puVar9 = 0;
	*(uint8_t*)((int)puVar9 + 2) = 0;
	uVar8 = 0xffffffff;
	pcVar3 = a2;
	do
	{
		if (uVar8 == 0)
			break;
		uVar8 = uVar8 - 1;
		cVar2 = *pcVar3;
		pcVar3 = pcVar3 + 1;
	} while (cVar2 != '\0');
	pcVar3 = a2 + (~uVar8 - 5);
	local_20c = (uint32_t)(a2);
	if (a2[~uVar8 - 5] == '.')
	{
		iVar7 = 0;
		cVar2 = *pcVar3;
		while (cVar2 != '\\')
		{
			pcVar1 = pcVar3 + -1;
			pcVar3 = pcVar3 + -1;
			iVar7 = iVar7 + 1;
			cVar2 = *pcVar1;
		}
		strncpy(&local_208, pcVar3 + 1, iVar7 - 1);
		*(uint8_t*)((int)&local_20c + iVar7 + 3) = 0;
	}
	_strlwr(&local_208);
	(*(uint32_t*)&local_104) = (*(uint32_t*)&local_104) & 0xffffff00;
	puVar9 = (uint32_t*)((int)local_104 + 1);
	for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar9 = 0;
		puVar9 = puVar9 + 1;
	}
	*(uint16_t*)puVar9 = 0;
	*(uint8_t*)((int)puVar9 + 2) = 0;
	uVar8 = 0xffffffff;
	pcVar3 = &local_208;
	do
	{
		if (uVar8 == 0)
			break;
		uVar8 = uVar8 - 1;
		cVar2 = *pcVar3;
		pcVar3 = pcVar3 + 1;
	} while (cVar2 != '\0');
	pcVar3 = (char*)(stack0xfffffdf3 + ~uVar8);
	if ((stack0xfffffdf3)[~uVar8] == '.')
	{
		iVar7 = 0;
		cVar2 = *pcVar3;
		while (cVar2 != '\\')
		{
			pcVar1 = pcVar3 + -1;
			pcVar3 = pcVar3 + -1;
			iVar7 = iVar7 + 1;
			cVar2 = *pcVar1;
		}
		strncpy((char* __restrict)(local_104), pcVar3 + 1, iVar7 - 1);
		(&cStack_105)[iVar7] = '\0';
	}
	_strlwr((char*)(local_104));
	uVar8 = 0xffffffff;
	pcVar3 = (char*)(local_104);
	do
	{
		if (uVar8 == 0)
			break;
		uVar8 = uVar8 - 1;
		cVar2 = *pcVar3;
		pcVar3 = pcVar3 + 1;
	} while (cVar2 != '\0');
	D2_ASSERT(7 >= ~uVar8 - 1);
	uVar8 = SStrHash((const char*)(local_104), 1, 0);
	for (puVar9 = *(uint32_t**)(a1 + 0xc +
	                            (((uVar8 & 0x1ff0000 ^ uVar8 >> 8) >> 8 ^ uVar8 & 0x1ff00) >> 8 ^ uVar8 & 0x1ff) *
	                                4);
	     puVar9 != nullptr; puVar9 = (uint32_t*)*puVar9)
	{
		if (((*(uint32_t*)&local_104) == puVar9[3]) && (iStack_100 == puVar9[4]))
		{
			return nullptr;
		}
	}
	puVar4 = (uint32_t*)D2_ALLOC(0x1c);
	puVar9 = puVar4;
	for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar9 = 0;
		puVar9 = puVar9 + 1;
	}
	puVar4[1] = puVar4[1] | 1;
	pcVar3 = &local_208;
	do
	{
		cVar2 = *pcVar3;
		pcVar3[(int)puVar4 + (0xc - (int)&local_208)] = cVar2;
		pcVar3 = pcVar3 + 1;
	} while (cVar2 != '\0');
	uVar11 = 0xdf;
	pcVar3 = __FILE__;
	piVar10 = (int*)(puVar4 + 2);
	pHVar5 = D2Win_GetArchive();
	pDVar6 = (D2CellFileStrc*)(ARCHIVE_AllocateBufferAndReadFile((HD2ARCHIVE)((HSFILE__*)pHVar5), (const char*)(local_20c), (size_t*)(piVar10), pcVar3, uVar11));
	puVar4[5] = (uint32_t)(pDVar6);
	if (pDVar6 == nullptr)
	{
		return nullptr;
	}
	D2_ASSERT(0x40 >= *(uint8_t*)((int)&pDVar6->dwVersion + 2));
	uVar8 = 0xffffffff;
	pcVar3 = &local_208;
	do
	{
		if (uVar8 == 0)
			break;
		uVar8 = uVar8 - 1;
		cVar2 = *pcVar3;
		pcVar3 = pcVar3 + 1;
	} while (cVar2 != '\0');
	D2_ASSERT(7 >= ~uVar8 - 1);
	uVar8 = SStrHash(&local_208, 1, 0);
	uVar8 = ((uVar8 & 0x1ff0000 ^ uVar8 >> 8) >> 8 ^ uVar8 & 0x1ff00) >> 8 ^ uVar8 & 0x1ff;
	*puVar4 = *(uint32_t*)(a1 + 0xc + uVar8 * 4);
	*(uint32_t**)(a1 + 0xc + uVar8 * 4) = puVar4;
	dword_6FBC2F94 = dword_6FBC2F94 + 0x1c + puVar4[2];
	return puVar4;
}

//D2Client.0x6FB58DC0
uint32_t __fastcall sub_6FB58DC0(int a1, int a2)
{
	uint32_t uVar1;
	void* pFree;
	void* pvVar2;
	void* pvVar3;
	int iVar4;

	iVar4 = sub_6FB28400(a1);
	D2_ASSERT(iVar4);
	pvVar3 = *(void**)(iVar4 + 0x28);
	pvVar2 = nullptr;
	while (true)
	{
		pFree = pvVar3;
		if (pFree == nullptr)
		{
			return 0;
		}
		if (*(int*)((int)pFree + 8) == a2)
			break;
		pvVar3 = *(void**)((int)pFree + 0x10);
		pvVar2 = pFree;
	}
	uVar1 = *(uint32_t*)((int)pFree + 0x10);
	D2_FREE(pFree);
	if (pvVar2 != nullptr)
	{
		*(uint32_t*)((int)pvVar2 + 0x10) = uVar1;
		return 1;
	}
	*(uint32_t*)(iVar4 + 0x28) = uVar1;
	return 1;
}

//D2Client.0x6FB58E40
uint32_t __fastcall sub_6FB58E40(D2UnitStrc* pUnit, uint32_t a2)
{
	char cVar1;
	int iVar2;
	int* piVar3;
	char* szMsg;
	char* szFile;
	int iVar4;
	int local_114;
	uint32_t local_110;
	int iStack_10c;
	uint32_t uStack_108;
	int iStack_104;
	char acStack_100[256];

	local_110 = 6;
	if (pUnit == nullptr)
	{
		local_114 = -1;
	}
	else
	{
		local_110 = pUnit->dwUnitType;
		local_114 = pUnit->dwClassId;
	}
	iStack_104 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_110, &local_114, &iStack_104,
	    __FILE__, __LINE__);
	if ((((-1 < local_114) &&
	         (iVar4 = *(int*)((uint8_t*)&sgptDataTables), local_114 < *(int*)(iVar4 + 0xa80))) &&
	        (iVar2 = (int)*(short*)(*(int*)(iVar4 + 0xa78) + 0x18 + local_114 * 0x1a8), -1 < iVar2)) &&
	    ((iVar2 < *(int*)(iVar4 + 0xa98) &&
	        (iVar4 = *(int*)(iVar4 + 0xa90) + iVar2 * 0x134, iVar4 != 0))))
	{
		iStack_10c = local_114;
		uStack_108 = *(uint32_t*)(((uint8_t*)&gdwBitMasks) + (a2 & 7) * 4) &
		             (uint32_t) * (uint8_t*)(((int)a2 >> 3) + 0xf0 + iVar4);
		if (uStack_108 != 0)
		{
			cVar1 = sub_6FB5F050((int)pUnit, a2);
			if ((cVar1 == '\0') &&
			    (piVar3 = sub_6FB58720(pUnit, (int)&uStack_108, a2), piVar3 != nullptr))
			{
				sub_6FB5F070((int)pUnit, a2, 1);
				return 1;
			}
			return 0;
		}
	}
	iVar4 = 0x486;
	szFile = __FILE__;
	szMsg = (char*)(FOG_csprintf(acStack_100, "[GFX.CPP] Mode (%i) is not used by monster (%i)", a2, local_114));
	FOG_DisplayHalt(szMsg, szFile, iVar4);
	exit(-1);
}

//D2Client.0x6FB58F90
uint32_t __fastcall sub_6FB58F90(D2UnitStrc* pUnit, int a2)
{
	char cVar1;
	D2ObjectsTxt* pDVar2;
	int* piVar3;
	char* szMsg;
	char* szFile;
	int nLine;
	int local_110;
	uint32_t local_10c;
	int iStack_108;
	uint32_t auStack_104;
	char acStack_100[256];

	local_10c = 6;
	if (pUnit == nullptr)
	{
		local_110 = -1;
	}
	else
	{
		local_10c = pUnit->dwUnitType;
		local_110 = pUnit->dwClassId;
	}
	iStack_108 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_10c, &local_110, &iStack_108,
	    __FILE__, __LINE__);
	pDVar2 = DATATBLS_GetObjectsTxtRecord(local_110);
	D2_ASSERT(pDVar2 != nullptr);
	if (pDVar2->nMode[a2] != 1)
	{
		nLine = 0x4db;
		szFile = __FILE__;
		szMsg = (char*)(FOG_csprintf(acStack_100, "[GFX.CPP] Mode (%i) is not used by object (%i)", a2, local_110));
		FOG_DisplayHalt(szMsg, szFile, nLine);
		exit(-1);
	}
	cVar1 = sub_6FB5F050((int)pUnit, a2);
	if (cVar1 == '\0')
	{
		piVar3 = sub_6FB58720(pUnit, (int)auStack_104, a2);
		if (piVar3 != nullptr)
		{
			sub_6FB5F070((int)pUnit, a2, 1);
			return 1;
		}
		FOG_DisplayAssert("lpbCofData", __FILE__, __LINE__);
		exit(-1);
	}
	return 0;
}

//D2Client.0x6FB590B0
void __fastcall sub_6FB590B0(uint32_t a1)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t* puVar3;

	puVar3 = &dword_6FBC1B08;
	dword_6FBC2F98 = a1;
	for (iVar1 = 0x203; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	puVar3 = &dword_6FBC2778;
	for (iVar1 = 0x203; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	puVar3 = &dword_6FBC2318;
	for (iVar1 = 0x118; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	dword_6FBC2F8C = 0;
	uVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) * 0xa0;
	dword_6FBC2F84 = (int)D2_ALLOC_POOL(nullptr, uVar2);
	puVar3 = (uint32_t*)dword_6FBC2F84;
	for (uVar2 = uVar2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*(uint8_t*)puVar3 = 0;
		puVar3 = (uint32_t*)((int)puVar3 + 1);
	}
	dword_6FBC2FA4 = D2Win_10185();
	sub_6FB5DE40();
}

//D2Client.0x6FB59140
void __fastcall sub_6FB59140()
{
	uint32_t* puVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	uint32_t* puVar5;

	uVar4 = 0;
	do
	{
		puVar5 = *(uint32_t**)((int)&dword_6FBC1B14 + uVar4);
		while (puVar1 = puVar5, puVar1 != nullptr)
		{
			puVar5 = (uint32_t*)*puVar1;
			if ((*(uint8_t*)(puVar1 + 1) & 1) != 0)
			{
				dword_6FBC2F94 = dword_6FBC2F94 + (-0x1c - puVar1[2]);
				D2_FREE((void*)puVar1[5]);
				D2_FREE(puVar1);
			}
		}
		uVar4 = uVar4 + 4;
	} while (uVar4 < 0x800);
	dword_6FBC2F94 = dword_6FBC2F94 - dword_6FBC1B10;
	if (ptr_6FBC1B0C != nullptr)
	{
		D2_FREE(ptr_6FBC1B0C);
	}
	uVar4 = 0;
	puVar5 = &dword_6FBC1B08;
	for (iVar2 = 0x203; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
	do
	{
		puVar5 = *(uint32_t**)((int)&dword_6FBC2784 + uVar4);
		while (puVar1 = puVar5, puVar1 != nullptr)
		{
			puVar5 = (uint32_t*)*puVar1;
			if ((*(uint8_t*)(puVar1 + 1) & 1) != 0)
			{
				dword_6FBC2F94 = dword_6FBC2F94 + (-0x1c - puVar1[2]);
				D2_FREE((void*)puVar1[5]);
				D2_FREE(puVar1);
			}
		}
		uVar4 = uVar4 + 4;
	} while (uVar4 < 0x800);
	dword_6FBC2F94 = dword_6FBC2F94 - dword_6FBC2780;
	if (ptr_6FBC277C != nullptr)
	{
		D2_FREE(ptr_6FBC277C);
	}
	iVar2 = dword_6FBC2F84;
	puVar5 = &dword_6FBC2778;
	for (iVar3 = 0x203; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
	if (iVar2 != 0)
	{
		D2_FREE_POOL(nullptr, (void*)iVar2);
		dword_6FBC2F84 = 0;
	}
}

//D2Client.0x6FB592C0
D2GfxDataStrc* __cdecl sub_6FB592C0()
{
	D2GfxDataStrc* pDVar1;
	int iVar2;
	D2GfxDataStrc* pDVar3;

	pDVar1 = (D2GfxDataStrc*)D2_ALLOC(0x3c);
	D2_ASSERT(pDVar1 != nullptr);
	pDVar3 = pDVar1;
	for (iVar2 = 0xf; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar3->pCurrentCell = nullptr;
		pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
	}
	pDVar1->szComponent[0] = '\x02';
	pDVar1->szComponent[1] = '\0';
	pDVar1->szComponent[2] = '\0';
	pDVar1->szComponent[3] = '\0';
	pDVar1->szArmorType[0] = '\x02';
	pDVar1->szArmorType[1] = '\0';
	pDVar1->szArmorType[2] = '\0';
	pDVar1->szArmorType[3] = '\0';
	return pDVar1;
}

//D2Client.0x6FB59320
void __fastcall sub_6FB59320(int a1)
{
	void* pvVar1;
	void* pvVar2;
	void* pFree;

	pFree = (void*)sub_6FB28400(a1);
	if (pFree != nullptr)
	{
		pvVar2 = *(void**)((int)pFree + 0x28);
		while (pvVar2 != nullptr)
		{
			pvVar1 = *(void**)((int)pvVar2 + 0x10);
			D2_FREE(pvVar2);
			pvVar2 = pvVar1;
		}
		pvVar2 = *(void**)((int)pFree + 0x2c);
		while (pvVar2 != nullptr)
		{
			pvVar1 = *(void**)((int)pvVar2 + 0xa4);
			if (*(int*)((int)pvVar2 + 0x40) != 0)
			{
				sub_6FAA44D0(*(int*)((int)pvVar2 + 0x40));
			}
			D2_FREE(pvVar2);
			pvVar2 = pvVar1;
		}
		D2_FREE(pFree);
		return;
	}
	FOG_DisplayAssert("ptGfxInfo", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB593C0
void __fastcall sub_6FB593C0(int a1)
{
	void* pvVar1;
	void* pFree;
	int iVar2;

	iVar2 = sub_6FB28400(a1);
	D2_ASSERT(iVar2);
	pFree = *(void**)(iVar2 + 0x28);
	while (pFree != nullptr)
	{
		pvVar1 = *(void**)((int)pFree + 0x10);
		D2_FREE(pFree);
		pFree = pvVar1;
	}
	*(uint32_t*)(iVar2 + 0x28) = 0;
}

//D2Client.0x6FB59420
void __fastcall sub_6FB59420(int a1)
{
	int* piVar1;
	int* piVar2;
	int* pFree;
	int iVar3;

	iVar3 = sub_6FB28400(a1);
	if (iVar3 != 0)
	{
		piVar1 = *(int**)(iVar3 + 0x28);
		pFree = nullptr;
		while (piVar2 = pFree, pFree = piVar1, pFree != nullptr)
		{
			piVar1 = (int*)pFree[4];
			if ((*pFree != 0) && (*pFree != 0x11))
			{
				D2_FREE(pFree);
				if (piVar2 == nullptr)
				{
					*(int**)(iVar3 + 0x28) = piVar1;
					pFree = piVar2;
				}
				else
				{
					piVar2[4] = (int)piVar1;
					pFree = piVar2;
				}
			}
		}
		return;
	}
	FOG_DisplayAssert("ptGfxInfo", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB59490
uint32_t __fastcall sub_6FB59490(D2UnitStrc* pUnit)
{
	uint8_t bVar1;
	int iVar2;
	D2ObjectsTxt* pDVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int* piVar7;
	int iVar8;
	D2GfxDataStrc* pDVar9;
	uint32_t uStack_64;
	int iStack_60;
	int iStack_5c;
	uint32_t uStack_58;
	D2CellFileStrc* local_54;
	int iStack_50;
	D2InventoryStrc* pDStack_4c;
	D2GfxDataStrc DStack_48;

	if ((pUnit != nullptr) &&
	    (local_54 = (D2CellFileStrc*)(pUnit->dwFlags >> 5 & 1), local_54 != nullptr))
	{
		return 0;
	}
	iVar2 = STATES_CheckState(pUnit, 0x92);
	if (iVar2 != 0)
	{
		return 0;
	}
	uStack_64 = 6;
	if (pUnit == nullptr)
	{
		iStack_60 = -1;
	}
	else
	{
		uStack_64 = pUnit->dwUnitType;
		iStack_60 = pUnit->dwClassId;
	}
	iStack_5c = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_64, &iStack_60, &iStack_5c,
	    __FILE__, __LINE__);
	uStack_58 = D2GFX_CheckPerspective();
	iVar2 = 0;
	iVar8 = 0;
	if (uStack_64 == 2)
	{
		pDVar3 = DATATBLS_GetObjectsTxtRecord(iStack_60);
		D2_ASSERT(pDVar3 != nullptr);
		if (pDVar3->nDraw == 0)
		{
			return 0;
		}
		if (pDVar3->nBlocksLight[iStack_5c] == 0)
		{
			return 0;
		}
		iVar2 = pDVar3->dwXOffset;
		iVar8 = pDVar3->dwYOffset;
	}
	iVar4 = sub_6FAB5890();
	iVar5 = sub_6FB5FC00((int)pUnit);
	iVar6 = UNITS_GetClientCoordX(pUnit);
	iVar6 = (iVar2 - iVar4) + iVar5 + iVar6;
	iVar2 = sub_6FAB58A0();
	iVar4 = sub_6FB5FC20((int)pUnit);
	iVar5 = UNITS_GetClientCoordY(pUnit);
	iVar5 = (iVar8 - iVar2) + iVar4 + iVar5;
	if (uStack_58 == 0)
		goto LAB_6fb595e5;
	iVar2 = sub_6FAB5750();
	if (iVar2 == 1)
	{
		iVar2 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
	LAB_6fb595e0:
		iVar6 = iVar6 + iVar2;
	}
	else if (iVar2 == 2)
	{
		iVar2 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
		goto LAB_6fb595e0;
	}
	iVar5 = iVar5 + 0x10;
LAB_6fb595e5:
	piVar7 = sub_6FB5C7D0(pUnit, iVar6, iVar5, 0, 1);
	if (piVar7 != nullptr)
	{
		bVar1 = UNITS_GetDirection(pUnit);
		uStack_58 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_58 + 1)), bVar1);
		UNITS_GetShiftedFrameMetrics(pUnit, (int*)&local_54, &iStack_50);
		pDVar9 = &DStack_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar9->pCurrentCell = nullptr;
			pDVar9 = (D2GfxDataStrc*)&pDVar9->pCellFile;
		}
		iVar2 = sub_6FB5EC80((int)&DStack_48, pUnit, 0, (D2CellFileStrc*)(uStack_58 & 0xff), local_54,
		    &pDStack_4c, 1, (D2InventoryStrc*)0xffffffff);
		if (iVar2 != 0)
		{
			TEXTURE_CelDrawShadow(&DStack_48, iVar6, iVar5);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FB59670
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB59670(D2UnitStrc* pUnit)
{
	Unicode* pUVar1;
	uint32_t* puVar2;
	uint8_t bVar3;
	uint8_t bVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	uint8_t* pbVar7;
	int iVar8;
	int iVar9;
	D2ObjectsTxt* pDVar10;
	int* piVar11;
	D2InventoryStrc* pInventory;
	uint32_t uVar12;
	uint32_t uVar13;
	uint32_t* puVar14;
	uint8_t* pbVar15;
	uint32_t extraout_var;
	D2GfxDataStrc* pDVar16;
	uint32_t uStack_98;
	uint8_t* pbStack_94;
	int iStack_90;
	int iStack_8c;
	int iStack_88;
	Unicode* pUStack_84;
	uint32_t* puStack_80;
	int iStack_7c;
	int iStack_78;
	int iStack_74;
	D2CellFileStrc* pDStack_70;
	int iStack_6c;
	D2CellFileStrc* pDStack_68;
	uint32_t uStack_64;
	uint32_t local_60;
	int iStack_5c;
	uint32_t uStack_58;
	int iStack_54;
	D2InventoryStrc* pDStack_50;
	int iStack_4c;
	D2GfxDataStrc DStack_48;

	if ((pUnit != nullptr) && (local_60 = pUnit->dwFlags >> 5 & 1, local_60 != 0))
	{
		return 0;
	}
	iVar5 = STATES_CheckState(pUnit, 0x92);
	if (iVar5 != 0)
	{
		return 0;
	}
	iVar5 = sub_6FB5F030((int*)pUnit);
	if (iVar5 == 0)
	{
		sub_6FB59490(pUnit);
		return 1;
	}
	iStack_88 = 0;
	iStack_78 = D2GFX_CheckUnitPerspective();
	if (((iStack_78 != 0) && (iVar5 = D2GFX_CheckPerspective(), iVar5 != 0)) &&
	    (pDVar6 = CUNIT_GetPlayer(), pUnit == pDVar6))
	{
		if (pUnit == nullptr)
		{
			uVar12 = 6;
		}
		else
		{
			pUStack_84 = (Unicode*)(pUnit->dwFlagEx >> 3 & 1);
			if (pUStack_84 == nullptr)
			{
				uVar12 = pUnit->dwUnitType;
			}
			else
			{
				uStack_98 = pUnit->dwUnitType;
				iStack_7c = pUnit->dwClassId;
				pbStack_94 = (uint8_t*)UNITS_GetAnimOrSeqMode(pUnit);
				D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_98, &iStack_7c, (int*)&pbStack_94,
				    __FILE__, __LINE__);
				uVar12 = uStack_98;
			}
		}
		if (uVar12 == 0)
		{
			D2GFX_SetUnitPerspective(0);
			iStack_88 = 1;
		}
	}
	pbVar7 = (uint8_t*)D2GFX_CheckPerspective();
	pbStack_94 = pbVar7;
	if (pbVar7 == nullptr)
	{
		iVar5 = sub_6FB5FBE0((int)pUnit);
		iStack_8c = UNITS_GetClientCoordX(pUnit);
		iStack_8c = iStack_8c + iVar5 / 2;
		iStack_90 = UNITS_GetClientCoordY(pUnit);
		iStack_90 = iStack_90 + iVar5 / 2;
	}
	else
	{
		iVar5 = sub_6FB5FC60((int)pUnit);
		iVar8 = UNITS_GetPrecisionX(pUnit);
		iVar8 = iVar8 - iVar5 / 2;
		iVar9 = UNITS_GetPrecisionY(pUnit);
		iVar9 = iVar9 - iVar5 / 2;
		iVar5 = SCALE_CheckPerspectivePosition(iVar8, iVar9);
		if (iVar5 == 0)
		{
			if (iStack_88 == 0)
			{
				return 0;
			}
			D2GFX_SetUnitPerspective(iStack_78);
			return 0;
		}
		SCALE_AdjustPerspectivePosition(iVar8, iVar9, 0, &iStack_8c, &iStack_90);
		iVar5 = sub_6FAB5890();
		iStack_8c = iStack_8c + iVar5;
		iVar5 = sub_6FAB58A0();
		iStack_90 = iStack_90 + 0x10 + iVar5;
		pbVar7 = pbStack_94;
	}
	if (iStack_88 != 0)
	{
		iStack_90 = iStack_90 + -8;
	}
	iVar5 = sub_6FB5FBA0((int)pUnit);
	iStack_8c = iStack_8c + iVar5;
	iVar5 = sub_6FB5FBC0((int)pUnit);
	iStack_90 = iStack_90 + iVar5;
	iVar5 = sub_6FAB5890();
	iVar8 = (iStack_8c - iVar5) + -2;
	iStack_74 = iVar8;
	iVar5 = sub_6FAB58A0();
	iVar5 = iStack_90 - iVar5;
	iStack_7c = iVar5;
	if ((pUnit != nullptr) && (pUnit->dwUnitType == 2))
	{
		pDVar10 = DATATBLS_GetObjectsTxtRecord(pUnit->dwClassId);
		iVar8 = iVar8 + pDVar10->dwXOffset;
		iStack_7c = iVar5 + pDVar10->dwYOffset;
		iStack_74 = iVar8;
	}
	iVar5 = iStack_7c;
	if (pbVar7 != nullptr)
	{
		iVar9 = sub_6FAB5750();
		if (iVar9 == 1)
		{
			iVar9 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
		}
		else
		{
			if (iVar9 != 2)
				goto LAB_6fb598b9;
			iVar9 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
		}
		iVar8 = iVar8 + iVar9;
		iStack_74 = iVar8;
	}
LAB_6fb598b9:
	piVar11 = sub_6FB5C7D0(pUnit, iVar8, iVar5, 0, 1);
	if (piVar11 == nullptr)
	{
	LAB_6fb59b23:
		if (iStack_88 != 0)
		{
			D2GFX_SetUnitPerspective(iStack_78);
			return 0;
		}
	}
	else
	{
		uStack_64 = 6;
		if (pUnit == nullptr)
		{
			iStack_6c = -1;
		}
		else
		{
			uStack_64 = pUnit->dwUnitType;
			iStack_6c = pUnit->dwClassId;
		}
		puStack_80 = (uint32_t*)UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_64, &iStack_6c, (int*)&puStack_80,
		    __FILE__, __LINE__);
		UNITS_GetShiftedFrameMetrics(pUnit, (int*)&pDStack_68, &iStack_54);
		if (((pUnit == nullptr) ||
		        (pUStack_84 = (Unicode*)(pUnit->dwFlagEx >> 3 & 1), pUStack_84 == nullptr)) ||
		    ((iVar5 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar5 == 0 ||
		                                                            (pDVar6 = sub_6FB26AD0((int)pUnit), pDVar6 == nullptr))))
		{
			pInventory = pUnit->pInventory;
		}
		else
		{
			pInventory = pDVar6->pInventory;
		}
		uVar12 = COMPOSIT_GetWeaponClassId(pUnit, pInventory, &iStack_4c, (int)puStack_80, 0);
		iVar5 = sub_6FB28400((int)pUnit);
		D2_ASSERT(iVar5);
		pUStack_84 = (Unicode*)(pUnit->dwFlagEx >> 3 & 1);
		if (pUStack_84 == nullptr)
		{
			uVar13 = UNITS_GetAnimOrSeqMode(pUnit);
		}
		else
		{
			pUStack_84 = (Unicode*)pUnit->dwUnitType;
			pbStack_94 = (uint8_t*)pUnit->dwClassId;
			uStack_98 = UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&pUStack_84, (int*)&pbStack_94, (int*)&uStack_98,
			    __FILE__, __LINE__);
			uVar13 = uStack_98;
		}
		for (puVar14 = *(uint32_t**)(iVar5 + 0x28); puVar14 != nullptr; puVar14 = (uint32_t*)puVar14[4])
		{
			if ((*puVar14 == uVar13) && (puVar14[1] == uVar12))
				goto LAB_6fb59a1c;
		}
		puVar14 = sub_6FB58410(pUnit, uVar12, (D2InventoryStrc*)0xffffffff);
		if (puVar14 != nullptr)
		{
		LAB_6fb59a1c:
			puVar2 = puStack_80;
			iVar5 = sub_6FB28400((int)pUnit);
			if (iVar5 != 0)
			{
				for (piVar11 = *(int**)(iVar5 + 0x28); piVar11 != nullptr; piVar11 = (int*)piVar11[4])
				{
					if ((uint32_t*)*piVar11 == puVar2)
					{
						pUVar1 = *(Unicode**)(piVar11[2] + 0x14);
						pUStack_84 = pUVar1;
						if (pUVar1 != nullptr)
						{
							pbVar7 = (uint8_t*)sub_6FB5EF30(pUVar1);
							pbStack_94 = pbVar7;
							bVar3 = UNITS_GetDirection(pUnit);
							pDStack_70 = (D2CellFileStrc*)(uint32_t)bVar3;
							sub_6FB5F090(pUnit, uStack_64, iStack_6c, puStack_80, (uint32_t*)&pDStack_70, (uint32_t*)(&iStack_5c),
							    &uStack_58, (uint32_t)pbVar7[2], 1);
							pbVar15 = sub_6FB5EFC0((uint8_t*)pUVar1, iStack_5c, (int)pDStack_68);
							D2_ASSERT(pbVar15 != nullptr);
							local_60 = 0;
							iVar5 = sub_6FB5F330(pUnit, pbVar7, (int)pbVar15, (int*)&local_60, pDStack_70,
							    pDStack_68);
							if (0 < iVar5)
							{
								uStack_98 = 0;
								if (*pbVar7 != 0)
								{
									do
									{
										bVar3 = pbVar15[uStack_98];
										D2_ASSERT(0xf >= bVar3);
										bVar4 = sub_6FB5EF80((uint8_t*)pUStack_84, (uint32_t)bVar3);
										if (D2C_ZEXT(bVar4) != 0)
										{
											pDVar16 = &DStack_48;
											for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
											{
												pDVar16->pCurrentCell = nullptr;
												pDVar16 = (D2GfxDataStrc*)&pDVar16->pCellFile;
											}
											iVar5 = sub_6FB5EC80((int)&DStack_48, pUnit, 0, pDStack_70, pDStack_68,
											    &pDStack_50, bVar3, (D2InventoryStrc*)0xffffffff);
											pbVar7 = pbStack_94;
											if (iVar5 != 0)
											{
												TEXTURE_CelDrawShadow(&DStack_48, iStack_74, iStack_7c);
												pbVar7 = pbStack_94;
											}
										}
										uStack_98 = uStack_98 + 1;
									} while (uStack_98 < *pbVar7);
								}
								if (iStack_88 != 0)
								{
									D2GFX_SetUnitPerspective(iStack_78);
								}
								return 1;
							}
							goto LAB_6fb59b23;
						}
						break;
					}
				}
			}
			FOG_Trace("Unable to get cof file for unit type:%d  class:%d  mode:%d in file:%s  line:%d", uStack_64, iStack_6c, puStack_80,
			    __FILE__, __LINE__);
		}
	}
	return 0;
}

//D2Client.0x6FB59C10
uint32_t __fastcall sub_6FB59C10(D2UnitStrc* pUnit)
{
	uint8_t uVar1;
	uint8_t bVar2;
	D2ObjectsTxt* pDVar3;
	int iVar4;
	int iVar5;
	int* piVar6;
	int iVar7;
	int iVar8;
	D2GfxDataStrc* pDVar9;
	uint32_t local_68;
	int local_64;
	int iStack_60;
	uint32_t uStack_5c;
	D2CellFileStrc* pDStack_58;
	uint8_t uStack_54;
	uint32_t uStack_53;
	int iStack_50;
	D2InventoryStrc* pDStack_4c;
	D2GfxDataStrc DStack_48;

	local_68 = 6;
	iVar8 = 0;
	iVar7 = 0;
	if (pUnit == nullptr)
	{
		local_64 = -1;
	}
	else
	{
		local_68 = pUnit->dwUnitType;
		local_64 = pUnit->dwClassId;
	}
	iStack_60 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_68, &local_64, &iStack_60,
	    __FILE__, __LINE__);
	uStack_5c = D2GFX_CheckPerspective();
	if (local_68 == 2)
	{
		pDVar3 = DATATBLS_GetObjectsTxtRecord(local_64);
		D2_ASSERT(pDVar3 != nullptr);
		if (pDVar3->nDraw == 0)
		{
			return 0;
		}
		if (pDVar3->nBlocksLight[iStack_60] == 0)
		{
			return 0;
		}
		iVar8 = pDVar3->dwXOffset;
		iVar7 = pDVar3->dwYOffset;
	}
	iVar4 = sub_6FAB5890();
	iVar5 = UNITS_GetClientCoordX(pUnit);
	iVar5 = (iVar8 - iVar4) + iVar5;
	iVar8 = sub_6FAB58A0();
	iVar4 = UNITS_GetClientCoordY(pUnit);
	iVar4 = (iVar7 - iVar8) + iVar4;
	if (uStack_5c != 0)
	{
		iVar8 = sub_6FAB5750();
		if (iVar8 == 1)
		{
			iVar8 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
		}
		else
		{
			if (iVar8 != 2)
				goto LAB_6fb59d25;
			iVar8 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
		}
		iVar5 = iVar5 + iVar8;
	}
LAB_6fb59d25:
	piVar6 = sub_6FB5C7D0(pUnit, iVar5, iVar4, 0, 0);
	if (piVar6 == nullptr)
	{
		return 0;
	}
	uVar1 = sub_6FB59DD0(pUnit);
	(*(uint32_t*)&uStack_54) = CONCAT31(uStack_53, uVar1);
	bVar2 = UNITS_GetDirection(pUnit);
	uStack_5c = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_5c + 1)), bVar2);
	UNITS_GetShiftedFrameMetrics(pUnit, (int*)&pDStack_58, &iStack_50);
	pDVar9 = &DStack_48;
	for (iVar8 = 0x12; iVar8 != 0; iVar8 = iVar8 + -1)
	{
		pDVar9->pCurrentCell = nullptr;
		pDVar9 = (D2GfxDataStrc*)&pDVar9->pCellFile;
	}
	iVar8 = sub_6FB5EC80((int)&DStack_48, pUnit, 0, (D2CellFileStrc*)(uStack_5c & 0xff), pDStack_58,
	    &pDStack_4c, 1, (D2InventoryStrc*)0xffffffff);
	if (iVar8 == 0)
	{
		return 0;
	}
	TEXTURE_CelDrawHilight(&DStack_48, iVar5, iVar4, (uint8_t)(*(uint32_t*)&uStack_54));
	return 1;
}

//D2Client.0x6FB59DD0
uint8_t __fastcall sub_6FB59DD0(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	uint32_t local_c;
	int iStack_8;
	int iStack_4;

	if (dword_6FBC2FA0 == 0)
	{
		byte_6FBC2F88 = D2Win_10034_MixRGB(0, 0xc0, 0);
		byte_6FBC2F89 = D2Win_10034_MixRGB(0xe0, 0xe0, 0);
		byte_6FBC2F8A = D2Win_10034_MixRGB(0xe0, 0, 0);
		byte_6FBC2F8B = D2Win_10034_MixRGB(0, 0, 0xc0);
		dword_6FBC2FA0 = 1;
	}
	local_c = 6;
	if (pUnit == nullptr)
	{
		iStack_8 = -1;
	}
	else
	{
		local_c = pUnit->dwUnitType;
		iStack_8 = pUnit->dwClassId;
	}
	iStack_4 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &iStack_8, &iStack_4, __FILE__, 0x987);
	if (local_c == 1)
	{
		if ((iStack_8 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iStack_8))
		{
			iVar1 = 0;
		}
		else
		{
			iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iStack_8 * 0x1a8;
		}
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar1 + 0xd)) != 0)
		{
			return byte_6FBC2F8B;
		}
		iVar1 = STATLIST_GetMaxLifeFromUnit(pUnit);
		if (iVar1 != 0)
		{
			iVar2 = STATLIST_UnitGetStatValue(pUnit, 6, 0);
			iVar1 = (iVar2 * 100) / iVar1;
			if (iVar1 < 0x21)
			{
				return byte_6FBC2F8A;
			}
			if (iVar1 < 0x42)
			{
				return byte_6FBC2F89;
			}
		}
	}
	return byte_6FBC2F88;
}

//D2Client.0x6FB59F20
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB59F20(D2UnitStrc* pUnit)
{
	Unicode* pUVar1;
	uint32_t* puVar2;
	uint8_t uVar3;
	uint8_t bVar4;
	uint8_t bVar5;
	int iVar6;
	int iVar7;
	int nXPos;
	int* piVar8;
	D2UnitStrc* pDVar9;
	D2InventoryStrc* pInventory;
	uint32_t uVar10;
	uint32_t uVar11;
	uint32_t* puVar12;
	uint8_t* pbVar13;
	uint8_t* pbVar14;
	uint32_t extraout_var;
	D2GfxDataStrc* pDVar15;
	int* pXAdjust;
	int iStack_88;
	int iStack_84;
	uint32_t* puStack_80;
	uint8_t* pbStack_7c;
	uint32_t uStack_78;
	uint32_t uStack_74;
	int iStack_70;
	D2CellFileStrc* pDStack_6c;
	D2CellFileStrc* pDStack_68;
	D2InventoryStrc* pDStack_64;
	int iStack_60;
	int iStack_5c;
	uint8_t uStack_58;
	uint32_t uStack_57;
	int iStack_54;
	uint32_t uStack_50;
	int iStack_4c;
	D2GfxDataStrc DStack_48;

	iVar6 = D2GFX_CheckPerspective();
	if (((pUnit == nullptr) || ((int)pUnit->dwUnitType < 0)) ||
	    (2 < (int)pUnit->dwUnitType))
	{
		sub_6FB59C10(pUnit);
		return 1;
	}
	if (iVar6 == 0)
	{
		iVar6 = UNITS_GetClientCoordX(pUnit);
		iVar7 = sub_6FAB5890();
		iStack_84 = sub_6FB5FBA0((int)pUnit);
		iStack_84 = (iVar6 - iVar7) + iStack_84;
		iVar6 = UNITS_GetClientCoordY(pUnit);
		iVar7 = sub_6FAB58A0();
		iStack_88 = sub_6FB5FBC0((int)pUnit);
		iStack_88 = (iVar6 - iVar7) + iStack_88;
		iVar6 = sub_6FB5FBE0((int)pUnit);
		goto LAB_6fb5a001;
	}
	iVar6 = sub_6FB5FBE0((int)pUnit);
	piVar8 = &iStack_88;
	pXAdjust = &iStack_84;
	iVar7 = UNITS_GetPrecisionY(pUnit);
	nXPos = UNITS_GetPrecisionX(pUnit);
	SCALE_AdjustPerspectivePosition(nXPos, iVar7, iVar6, pXAdjust, piVar8);
	iVar6 = sub_6FAB5750();
	if (iVar6 == 1)
	{
		iVar6 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
	LAB_6fb59f9f:
		iStack_84 = iStack_84 + iVar6;
	}
	else if (iVar6 == 2)
	{
		iVar6 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
		goto LAB_6fb59f9f;
	}
	iStack_88 = iStack_88 + 0x10;
	iVar6 = sub_6FB5FBA0((int)pUnit);
	iStack_84 = iStack_84 + iVar6;
	iVar6 = sub_6FB5FBC0((int)pUnit);
LAB_6fb5a001:
	iStack_88 = iStack_88 + iVar6;
	piVar8 = sub_6FB5C7D0(pUnit, iStack_84, iStack_88, 0, 0);
	if (piVar8 == nullptr)
	{
		return 0;
	}
	uVar3 = sub_6FB59DD0(pUnit);
	(*(uint32_t*)&uStack_58) = CONCAT31(uStack_57, uVar3);
	uStack_74 = pUnit->dwUnitType;
	iStack_70 = pUnit->dwClassId;
	puStack_80 = (uint32_t*)UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_74, &iStack_70, (int*)&puStack_80,
	    __FILE__, __LINE__);
	bVar4 = UNITS_GetDirection(pUnit);
	pDStack_6c = (D2CellFileStrc*)(uint32_t)bVar4;
	UNITS_GetShiftedFrameMetrics(pUnit, (int*)&pDStack_68, &iStack_54);
	pbStack_7c = (uint8_t*)(pUnit->dwFlagEx >> 3 & 1);
	if (((pbStack_7c == nullptr) ||
	        (iVar6 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar6 == 0)) ||
	    (pDVar9 = sub_6FB26AD0((int)pUnit), pDVar9 == nullptr))
	{
		pInventory = pUnit->pInventory;
	}
	else
	{
		pInventory = pDVar9->pInventory;
	}
	uVar10 = COMPOSIT_GetWeaponClassId(pUnit, pInventory, &iStack_4c, (int)puStack_80, 0);
	iVar6 = sub_6FB28400((int)pUnit);
	D2_ASSERT(iVar6);
	pbStack_7c = (uint8_t*)(pUnit->dwFlagEx >> 3 & 1);
	if (pbStack_7c == nullptr)
	{
		uVar11 = UNITS_GetAnimOrSeqMode(pUnit);
	}
	else
	{
		pbStack_7c = (uint8_t*)pUnit->dwUnitType;
		pDStack_64 = (D2InventoryStrc*)pUnit->dwClassId;
		uStack_78 = UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&pbStack_7c, (int*)&pDStack_64, (int*)&uStack_78,
		    __FILE__, __LINE__);
		uVar11 = uStack_78;
	}
	for (puVar12 = *(uint32_t**)(iVar6 + 0x28); puVar12 != nullptr; puVar12 = (uint32_t*)puVar12[4])
	{
		if ((*puVar12 == uVar11) && (puVar12[1] == uVar10))
			goto LAB_6fb5a181;
	}
	puVar12 = sub_6FB58410(pUnit, uVar10, (D2InventoryStrc*)0xffffffff);
	if (puVar12 == nullptr)
	{
		return 0;
	}
LAB_6fb5a181:
	puVar2 = puStack_80;
	iVar6 = sub_6FB28400((int)pUnit);
	if (iVar6 != 0)
	{
		for (piVar8 = *(int**)(iVar6 + 0x28); piVar8 != nullptr; piVar8 = (int*)piVar8[4])
		{
			if ((uint32_t*)*piVar8 == puVar2)
			{
				pUVar1 = *(Unicode**)(piVar8[2] + 0x14);
				if (pUVar1 != nullptr)
				{
					pbVar13 = (uint8_t*)sub_6FB5EF30(pUVar1);
					pbStack_7c = pbVar13;
					sub_6FB5F090(pUnit, uStack_74, iStack_70, puStack_80, (uint32_t*)&pDStack_6c, (uint32_t*)(&iStack_5c),
					    &uStack_50, (uint32_t)pbVar13[2], 1);
					pbVar14 = sub_6FB5EFC0((uint8_t*)pUVar1, iStack_5c, (int)pDStack_68);
					D2_ASSERT(pbVar14 != nullptr);
					iStack_60 = 0;
					iVar6 = sub_6FB5F330(pUnit, pbVar13, (int)pbVar14, &iStack_60, pDStack_6c, pDStack_68);
					if (0 < iVar6)
					{
						uStack_78 = 0;
						if (*pbVar13 == 0)
						{
							return 1;
						}
						do
						{
							bVar4 = pbVar14[uStack_78];
							bVar5 = sub_6FB5F7F0(pUnit, (uint32_t)bVar4);
							if (D2C_ZEXT(bVar5) != 0)
							{
								pDVar15 = &DStack_48;
								for (iVar6 = 0x12; iVar6 != 0; iVar6 = iVar6 + -1)
								{
									pDVar15->pCurrentCell = nullptr;
									pDVar15 = (D2GfxDataStrc*)&pDVar15->pCellFile;
								}
								iVar6 = sub_6FB5EC80((int)&DStack_48, pUnit, 0, pDStack_6c, pDStack_68, &pDStack_64,
								    bVar4, (D2InventoryStrc*)0xffffffff);
								if (iVar6 != 0)
								{
									TEXTURE_CelDrawHilight(&DStack_48, iStack_84, iStack_88, (uint8_t)(*(uint32_t*)&uStack_58));
								}
							}
							uStack_78 = uStack_78 + 1;
						} while (uStack_78 < *pbStack_7c);
						return 1;
					}
					return 0;
				}
				break;
			}
		}
	}
	FOG_Trace("Unable to get cof file for unit type:%d  class:%d  mode:%d in file:%s  line:%d", uStack_74, iStack_70, puStack_80,
	    __FILE__, __LINE__);
	return 0;
}

//D2Client.0x6FB5A320
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB5A320(D2UnitStrc* pUnit, D2CellFileStrc* pCellFile2, int a3)
{
	bool bVar1;
	uint32_t uVar2;
	uint32_t extraout_var;
	uint8_t* pPalette;
	int iVar3;
	D2CellFileStrc* pDVar4;
	DrawMode eDrawMode;
	D2GfxDataStrc* pDVar5;
	uint32_t uVar6;
	uint8_t bStack_51;
	D2CellFileStrc* local_50;
	D2InventoryStrc* pDStack_4c;
	D2GfxDataStrc DStack_48;

	if ((pUnit == nullptr) || (pUnit->dwUnitType != 4))
	{
		return 0;
	}
	pDVar4 = nullptr;
	local_50 = pCellFile2;
	uVar2 = ITEMS_GetItemType(pUnit);
	if (uVar2 == 4)
	{
		uVar2 = STATLIST_UnitGetStatValue(pUnit, 0xe, 0);
		if (99 < uVar2)
		{
			if (uVar2 < 500)
			{
				pDVar4 = (D2CellFileStrc*)0x1;
			}
			else
			{
				pDVar4 = (D2CellFileStrc*)(3 - (uint32_t)(uVar2 < 5000));
			}
		}
	}
	pDVar5 = &DStack_48;
	for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		pDVar5->pCurrentCell = nullptr;
		pDVar5 = (D2GfxDataStrc*)&pDVar5->pCellFile;
	}
	iVar3 = sub_6FB5EC80((int)&DStack_48, pUnit, 0, pDVar4, nullptr, &pDStack_4c, 1,
	    (D2InventoryStrc*)0xffffffff);
	if (iVar3 == 0)
	{
		return 0;
	}
	iVar3 = D2CMP_10055((int)&DStack_48, 0, 1);
	if (iVar3 == 0)
	{
		return 0;
	}
	uVar6 = 0;
	iVar3 = D2CMP_CelGetHeight((D2CellFileStrc*)DStack_48.pCurrentCell);
	bVar1 = sub_6FB5E170((D2CellFileStrc*)(DStack_48.pCurrentCell), (int)pCellFile2, iVar3 + a3, uVar6);
	if (D2C_ZEXT(bVar1) == 0)
	{
		return 0;
	}
	pPalette = ITEMS_GetColor(nullptr, pUnit, &bStack_51, 1);
	eDrawMode = DRAWMODE_NORMAL;
	iVar3 = ITEMS_CheckItemFlag(pUnit, 0x400000, __LINE__, __FILE__);
	if (iVar3 != 0)
	{
		eDrawMode = DRAWMODE_TRANS50;
	}
	uVar2 = 0xffffffff;
	iVar3 = D2CMP_CelGetHeight((D2CellFileStrc*)DStack_48.pCurrentCell);
	pDVar4 = local_50;
	TEXTURE_CelDraw(&DStack_48, (int)local_50, iVar3 + a3, uVar2, eDrawMode, pPalette);
	uVar6 = 0;
	uVar2 = D2CMP_CelGetHeight((D2CellFileStrc*)DStack_48.pCurrentCell);
	iVar3 = (uVar2 >> 1) + a3;
	uVar2 = D2CMP_CelGetWidth((D2CellFileStrc*)DStack_48.pCurrentCell);
	sub_6FB5A490(pUnit, 0xff, 0, (int)&pDVar4->dwVersion + (uVar2 >> 1), iVar3, uVar6);
	return 1;
}

//D2Client.0x6FB5A490
void __fastcall sub_6FB5A490(D2UnitStrc* pUnit, uint32_t a2, int a3, int a4, int a5, int a6)
{
	int iVar1;
	uint8_t bVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int* piVar6;
	D2GfxDataStrc* pDVar7;
	bool bVar8;
	D2CellFileStrc* pDVar9;
	int iVar10;
	D2InventoryStrc** ppDVar11;
	uint8_t uVar12;
	int* pXAdjust;
	int* pYAdjust;
	D2InventoryStrc* pDVar13;
	int iStack_58;
	int iStack_54;
	D2GfxDataStrc DStack_48;

	iVar3 = sub_6FB28400((int)pUnit);
	D2_ASSERT(iVar3);
	iVar4 = D2GFX_CheckPerspective();
	piVar6 = *(int**)(iVar3 + 0x2c);
	if (piVar6 == nullptr)
	{
		return;
	}
	if ((iVar4 == 0) ||
	    (((pUnit != nullptr && (pUnit->dwUnitType == 4)) &&
	        (iVar3 = UNITS_GetAnimOrSeqMode(pUnit), iVar3 != 3))))
	{
		iStack_54 = UNITS_GetClientCoordX(pUnit);
		iVar3 = sub_6FAB5890();
		iStack_54 = iStack_54 - iVar3;
		iStack_58 = UNITS_GetClientCoordY(pUnit);
		iVar3 = sub_6FAB58A0();
		iStack_58 = iStack_58 - iVar3;
		if ((((pUnit == nullptr) || (pUnit->dwUnitType != 4)) || (a4 == -1)) ||
		    (iVar3 = a5, a5 == -1))
			goto LAB_6fb5a59a;
	}
	else
	{
		pYAdjust = &a5;
		pXAdjust = &a4;
		iVar10 = 0;
		iVar3 = UNITS_GetPrecisionY(pUnit);
		iVar4 = UNITS_GetPrecisionX(pUnit);
		SCALE_AdjustPerspectivePosition(iVar4, iVar3, iVar10, pXAdjust, pYAdjust);
		iVar3 = sub_6FAB5750();
		if (iVar3 == 1)
		{
			iVar3 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
		LAB_6fb5a53c:
			a4 = a4 + iVar3;
		}
		else if (iVar3 == 2)
		{
			iVar3 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
			goto LAB_6fb5a53c;
		}
		iVar3 = a5 + 0x10;
	}
	iStack_58 = iVar3;
	iStack_54 = a4;
LAB_6fb5a59a:
	iVar3 = sub_6FB5FBA0((int)pUnit);
	iVar4 = sub_6FB5FBC0((int)pUnit);
	iVar10 = sub_6FB5FBE0((int)pUnit);
	iStack_58 = iStack_58 + iVar4 + iVar10;
	if (a6 != 0)
	{
		iStack_58 = iStack_58 + -8;
	}
	do
	{
		bVar8 = true;
		if (((piVar6[0xd] == 0) || (bVar8 = a3 != 0, piVar6[0xd] == 0)) && (a3 != 0))
		{
			bVar8 = false;
		}
		if ((*piVar6 == 6) && (piVar6[2] == 0))
		{
			bVar8 = false;
		}
		if (((*piVar6 != 8) || (piVar6[0xf] != 0)) && (bVar8))
		{
			iVar4 = piVar6[6];
			iVar10 = piVar6[1];
			if (((iVar10 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0) <= iVar10)) ||
			    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbbc) + iVar10 * 0x84, iVar1 == 0))
			{
				FOG_DisplayAssert("ptStats", __FILE__, __LINE__);
				exit(-1);
			}
			pDVar13 = (D2InventoryStrc*)0xffffffff;
			pDVar7 = &DStack_48;
			for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				pDVar7->pCurrentCell = nullptr;
				pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
			}
			ppDVar11 = (D2InventoryStrc**)&a4;
			uVar12 = 1;
			pDVar9 = (D2CellFileStrc*)(iVar4 >> 8);
			DStack_48.nOverlay = iVar10;
			bVar2 = UNITS_GetDirection(pUnit);
			iVar10 = sub_6FB5EC80((int)&DStack_48, nullptr, 0, (D2CellFileStrc*)(uint32_t)bVar2, pDVar9, ppDVar11, uVar12, pDVar13);
			if (iVar10 == 0)
			{
				return;
			}
			if (iVar4 >> 8 < piVar6[7] >> 8)
			{
				if ((*(char*)(iVar1 + 0x81) != '\0') && (iVar4 = sub_6FAAC020(), iVar4 != 0))
				{
					sub_6FAAE560();
				}
				TEXTURE_CelDraw(&DStack_48, piVar6[8] + iStack_54 + iVar3, piVar6[9] + iStack_58, a2,
				    (DrawMode)((uint32_t) * (uint8_t*)(iVar1 + 0x7c)), nullptr);
			}
		}
		piVar6 = (int*)piVar6[0x29];
		if (piVar6 == nullptr)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FB5A720
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB5A720(D2UnitStrc* pUnit, DrawMode a2, int a3, int a4, int a5, int a6)
{
	Unicode* pUVar1;
	bool bVar2;
	uint8_t bVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	D2ObjectsTxt* pDVar8;
	D2UnitStrc* pDVar9;
	int* piVar10;
	D2InventoryStrc* pInventory;
	uint32_t* puVar11;
	uint32_t* puVar12;
	uint8_t* pbVar13;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	uint32_t extraout_var_02;
	uint8_t* pbVar14;
	D2CellFileStrc* pDVar15;
	D2GfxDataStrc* pDVar16;
	DrawMode DVar17;
	DrawMode local_114;
	DrawMode DStack_110;
	uint8_t* pbStack_10c;
	uint32_t uStack_108;
	uint32_t* puStack_104;
	int iStack_100;
	int iStack_fc;
	int iStack_f8;
	uint32_t uStack_f4;
	int iStack_f0;
	uint8_t* pbStack_ec;
	int iStack_e8;
	uint8_t bStack_e1;
	int iStack_e0;
	uint8_t* pbStack_dc;
	int iStack_d8;
	int iStack_d4;
	int iStack_d0;
	int iStack_cc;
	D2CellFileStrc* pDStack_c8;
	int iStack_c4;
	D2InventoryStrc* pDStack_c0;
	D2CellFileStrc* pDStack_bc;
	Unicode* pUStack_b8;
	D2CellFileStrc* pDStack_b4;
	int iStack_b0;
	int iStack_ac;
	uint8_t* pbStack_a8;
	int iStack_a4;
	int iStack_a0;
	D2InventoryStrc* pDStack_9c;
	uint32_t uStack_98;
	int iStack_94;
	D2GfxDataStrc DStack_90;
	D2GfxDataStrc DStack_48;

	local_114 = a2;
	iStack_cc = D2GFX_CheckPerspective();
	if ((pUnit != nullptr) && (pUnit->dwUnitType == 5))
	{
		return 0;
	}
	uVar4 = sub_6FB29A40(pUnit);
	if (uVar4 != 0)
	{
		sub_6FB59F20(pUnit);
	}
	uStack_f4 = 6;
	if (pUnit == nullptr)
	{
		iStack_c4 = -1;
	}
	else
	{
		uStack_f4 = pUnit->dwUnitType;
		iStack_c4 = pUnit->dwClassId;
	}
	iStack_ac = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_f4, &iStack_c4, &iStack_ac,
	    __FILE__, __LINE__);
	iStack_f8 = 0;
	iStack_fc = 0;
	iVar5 = sub_6FB5FBA0((int)pUnit);
	iVar5 = a3 + iVar5;
	iVar6 = sub_6FB5FBC0((int)pUnit);
	iVar7 = sub_6FB5FBE0((int)pUnit);
	iVar7 = a4 + iVar6 + iVar7;
	if (uStack_f4 == 2)
	{
		pDVar8 = DATATBLS_GetObjectsTxtRecord(iStack_c4);
		D2_ASSERT(pDVar8 != nullptr);
		if (pDVar8->nDraw == 0)
		{
			return 0;
		}
		iStack_f8 = pDVar8->dwXOffset;
		iStack_fc = pDVar8->dwYOffset;
		iVar5 = iVar5 + iStack_f8;
		iVar7 = iVar7 + iStack_fc;
	}
	iVar6 = sub_6FB5F030((int*)pUnit);
	if (iVar6 != 0)
	{
		DStack_110 = local_114;
		uStack_108 = 6;
		if (pUnit == nullptr)
		{
			iStack_e8 = -1;
		}
		else
		{
			uStack_108 = pUnit->dwUnitType;
			iStack_e8 = pUnit->dwClassId;
		}
		puStack_104 = (uint32_t*)UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_108, &iStack_e8, (int*)&puStack_104,
		    __FILE__, __LINE__);
		iVar6 = sub_6FAB5890();
		iVar5 = iVar5 - iVar6;
		iStack_100 = iVar5;
		iStack_f0 = sub_6FAB58A0();
		iStack_f0 = iVar7 - iStack_f0;
		iVar6 = D2GFX_CheckPerspective();
		iStack_d8 = iVar6;
		iStack_fc = sub_6FAB5750();
		if (iVar6 != 0)
		{
			if (iStack_fc == 1)
			{
				iVar7 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
			}
			else
			{
				if (iStack_fc != 2)
					goto LAB_6fb5a908;
				iVar7 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
			}
			iVar5 = iVar5 + iVar7;
			iStack_100 = iVar5;
		}
	LAB_6fb5a908:
		iVar7 = 0;
		pbStack_10c = nullptr;
		iStack_f8 = D2GFX_CheckUnitPerspective();
		if ((((iStack_f8 != 0) && (iVar6 != 0)) && (pDVar9 = CUNIT_GetPlayer(), pUnit == pDVar9)) &&
		    (uStack_108 == 0))
		{
			D2GFX_SetUnitPerspective(0);
			iVar7 = 1;
			pbStack_10c = (uint8_t*)0x1;
			iStack_d8 = 0;
		}
		piVar10 = sub_6FB5C7D0(pUnit, iVar5, iStack_f0, 1, 0);
		if (piVar10 == nullptr)
		{
			if (iVar7 != 0)
			{
				D2GFX_SetUnitPerspective(iStack_f8);
			}
			return 0;
		}
		if (a6 != 0)
		{
			sub_6FB5A490(pUnit, local_114, 1, 0xffffffff, 0xffffffff, iVar7);
		}
		UNITS_GetShiftedFrameMetrics(pUnit, (int*)&pDStack_bc, &iStack_94);
		pbStack_ec = nullptr;
		if (*(int*)&pUnit->nInteract != 0)
		{
			pbStack_ec = D2Win_10175_GetPL2Shift(*(int*)&pUnit->nInteract + -1);
		}
		pbVar14 = pbStack_ec;
		iVar5 = 0;
		piVar10 = &iStack_a4;
		puVar11 = puStack_104;
		pInventory = sub_6FB5DDE0(pUnit, nullptr);
		uVar4 = COMPOSIT_GetWeaponClassId(pUnit, pInventory, piVar10, (int)puVar11, iVar5);
		puVar11 = sub_6FB58350(pUnit, uVar4, (uint32_t*)0xffffffff);
		if ((puVar11 == nullptr) &&
		    (puVar12 = sub_6FB58410(pUnit, uVar4, (D2InventoryStrc*)0xffffffff), puVar12 == nullptr))
		{
			return 0;
		}
		puVar11 = puStack_104;
		iVar5 = sub_6FB28400((int)pUnit);
		if (iVar5 != 0)
		{
			for (piVar10 = *(int**)(iVar5 + 0x28); piVar10 != nullptr; piVar10 = (int*)piVar10[4])
			{
				if ((uint32_t*)*piVar10 == puVar11)
				{
					pUVar1 = *(Unicode**)(piVar10[2] + 0x14);
					pUStack_b8 = pUVar1;
					if (pUVar1 != nullptr)
					{
						pbVar13 = (uint8_t*)sub_6FB5EF30(pUVar1);
						pbStack_dc = pbVar13;
						if (pbVar14 == nullptr)
						{
							pbStack_ec = sub_6FAAE3C0((int*)pUnit);
						}
						bVar2 = sub_6FB286B0(pUnit);
						iStack_cc = D2C_ZEXT(bVar2);
						bVar3 = UNITS_GetDirection(pUnit);
						pDStack_c8 = (D2CellFileStrc*)(uint32_t)bVar3;
						sub_6FB5F090(pUnit, uStack_108, iStack_e8, puStack_104, (uint32_t*)&pDStack_c8, (uint32_t*)(&iStack_b0),
						    &uStack_98, (uint32_t)pbVar13[2], 1);
						pbStack_a8 = sub_6FB5EFC0((uint8_t*)pUVar1, iStack_b0, (int)pDStack_bc);
						D2_ASSERT(pbStack_a8 != nullptr);
						iStack_e0 = 0;
						if ((uStack_108 == 2) &&
						    (pDVar8 = DATATBLS_GetObjectsTxtRecord(pUnit->dwClassId),
						        pDVar8->nOrderFlag[(int)puStack_104] == 1))
						{
							iStack_e0 = 1;
						}
						iStack_d4 = 1;
						iVar5 = STATES_CheckStateMaskGreenOnUnit(pUnit);
						if ((iVar5 != 0) &&
						    ((pDVar9 = CUNIT_GetPlayer(), pUnit != pDVar9 ||
						                                      (bVar2 = WNDPROC_IsHardwareAccelerated(), D2C_ZEXT(bVar2) == 0))))
						{
							iStack_d4 = 0;
						}
						iStack_d0 = 0;
						if (*pbVar13 != 0)
							goto LAB_6fb5ab72;
						goto LAB_6fb5ae0b;
					}
					break;
				}
			}
		}
		FOG_Trace("Unable to get cof file for unit type:%d  class:%d  mode:%d in file:%s  line:%d", uStack_108, iStack_e8, puStack_104,
		    __FILE__, __LINE__);
		return 0;
	}
	bVar3 = UNITS_GetDirection(pUnit);
	pbStack_dc = (uint8_t*)CONCAT31((*(uint8_t*)((uint8_t*)&pbStack_dc + 1)), bVar3);
	UNITS_GetShiftedFrameMetrics(pUnit, (int*)&pDStack_b4, &iStack_a0);
	iVar6 = *(int*)&pUnit->nInteract;
	pbStack_10c = nullptr;
	if ((iVar6 != 0) && (pDVar9 = CUNIT_GetPlayer(), pUnit != pDVar9))
	{
		pbStack_10c = D2Win_10175_GetPL2Shift(iVar6 + -1);
	}
	pDVar15 = (D2CellFileStrc*)((uint32_t)pbStack_dc & 0xff);
	if ((uStack_f4 == 4) && (uVar4 = ITEMS_GetItemType(pUnit), uVar4 == 4))
	{
		uVar4 = STATLIST_UnitGetStatValue(pUnit, 0xe, 0);
		if (uVar4 < 100)
		{
			pDVar15 = nullptr;
		}
		else if (uVar4 < 500)
		{
			pDVar15 = (D2CellFileStrc*)0x1;
		}
		else
		{
			pDVar15 = (D2CellFileStrc*)(3 - (uint32_t)(uVar4 < 5000));
		}
	}
	pDVar16 = &DStack_48;
	for (iVar6 = 0x12; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		pDVar16->pCurrentCell = nullptr;
		pDVar16 = (D2GfxDataStrc*)&pDVar16->pCellFile;
	}
	iVar6 = sub_6FB5EC80((int)&DStack_48, pUnit, 0, pDVar15, pDStack_b4, &pDStack_9c, 1,
	    (D2InventoryStrc*)0xffffffff);
	if (iVar6 == 0)
	{
		return 0;
	}
	iVar6 = D2CMP_10055((int)&DStack_48, 0, 1);
	if (iVar6 == 0)
	{
		return 0;
	}
	iVar6 = sub_6FAB5890();
	iVar6 = (iStack_f8 + iVar5) - iVar6;
	iVar5 = sub_6FAB58A0();
	iVar5 = (iVar7 + iStack_fc) - iVar5;
	if (iStack_cc != 0)
	{
		iVar7 = sub_6FAB5750();
		if (iVar7 == 1)
		{
			iVar7 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
		}
		else
		{
			if (iVar7 != 2)
				goto LAB_6fb5af95;
			iVar7 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
		}
		iVar6 = iVar6 + iVar7;
	}
LAB_6fb5af95:
	pDVar9 = sub_6FAB5A20();
	bVar2 = pDVar9 == pUnit;
	if (bVar2)
	{
		DVar17 = (DrawMode)((local_114 & 0xff) * 2);
		if ((local_114 & 0xff) == 0x20 || DVar17 < 0x40)
		{
			DVar17 = (DrawMode)(0x40);
		}
		else if (0xfe < DVar17)
		{
			DVar17 = (DrawMode)(0xff);
		}
		local_114 = (DrawMode)(local_114 & 0xffffff00 | DVar17);
	}
	if (uStack_f4 != 3)
	{
		DVar17 = DRAWMODE_NORMAL;
		if (bVar2)
		{
			DVar17 = DRAWMODE_HIGHLIGHT;
		}
		if ((uStack_f4 != 4) ||
		    (pbVar14 = ITEMS_GetColor(nullptr, pUnit, &bStack_e1, 0), pbVar14 == nullptr))
		{
			pbVar14 = pbStack_10c;
		}
		TEXTURE_CelDraw(&DStack_48, iVar6, iVar5, local_114, DVar17, pbVar14);
		if (a6 != 0)
		{
			sub_6FB5A490(pUnit, local_114, 0, 0xffffffff, 0xffffffff, 0);
		}
		return 1;
	}
	iVar7 = pUnit->dwClassId;
	if ((iVar7 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar7))
	{
		iVar7 = 0;
	}
	else
	{
		iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar7 * 0x1a4;
	}
	DVar17 = DRAWMODE_NORMAL;
	if (*(char*)(iVar7 + 0x18d) == '\x01')
	{
		DVar17 = DRAWMODE_MODULATE;
	}
	if (*(char*)(iVar7 + 0x18d) == '\x02')
	{
		DVar17 = DRAWMODE_BURN;
	}
	if (bVar2)
	{
		DVar17 = DRAWMODE_HIGHLIGHT;
	}
	pbVar14 = pbStack_10c;
	if ((*(char*)(iVar7 + 0x1a2) != '\0') &&
	    (iVar7 = sub_6FAAC020(), pbVar14 = pbStack_10c, iVar7 != 0))
	{
		pbVar14 = (uint8_t*)sub_6FAAE560();
	}
	TEXTURE_CelDraw(&DStack_48, iVar6, iVar5, local_114, DVar17, pbVar14);
	return 1;
LAB_6fb5ab72:
	bVar3 = pbStack_a8[iStack_d0];
	uVar4 = (uint32_t)bVar3;
	if (uVar4 == 0xf)
	{
		pbVar14 = nullptr;
		if ((((uStack_108 == 1) && (iVar5 = sub_6FB247F0(pUnit->dwClassId), iVar5 != 0)) &&
		        (*(char*)(iVar5 + 0x11c) != '\0')) &&
		    (iVar5 = sub_6FAAC020(), iVar5 != 0))
		{
			pbVar14 = (uint8_t*)sub_6FAAE560();
		}
	LAB_6fb5abbf:
		pDVar16 = &DStack_90;
		for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			pDVar16->pCurrentCell = nullptr;
			pDVar16 = (D2GfxDataStrc*)&pDVar16->pCellFile;
		}
		pDStack_c0 = (D2InventoryStrc*)0xffffffff;
		iVar5 = sub_6FB5EC80((int)&DStack_90, pUnit, 0, pDStack_c8, pDStack_bc, &pDStack_c0, bVar3,
		    (D2InventoryStrc*)0xffffffff);
		if (iVar5 != 0)
		{
			local_114 = DRAWMODE_NORMAL;
			iVar5 = sub_6FB5F420(pUnit, uVar4, (uint32_t*)(&local_114), (int)pDStack_c0);
			if ((iStack_d4 != 0) &&
			    ((uStack_108 != 0 ||
			        ((*(uint16_t*)((uint8_t*)&iVar6 + 0)) = pUnit->nInteract, (*(uint16_t*)((uint8_t*)&iVar6 + 2)) = pUnit->nUpdateType, iVar6 != 0x6c))))
			{
				pbVar14 = (uint8_t*)sub_6FB5F6B0(pUnit, uVar4, (int)pbVar14);
			}
			bVar3 = sub_6FB5EF40((uint8_t*)pUStack_b8, uVar4);
			if (D2C_ZEXT(bVar3) == 0)
			{
				if ((iStack_cc == 0) && (iVar5 == 0))
				{
					if (a5 == 0)
					{
						if ((iStack_d8 != 0) && (iStack_e0 != 0))
						{
							iVar5 = UNITS_GetPrecisionX(pUnit);
							iVar6 = UNITS_GetPrecisionY(pUnit);
							DVar17 = DRAWMODE_NORMAL;
							goto LAB_6fb5ace8;
						}
						DVar17 = DRAWMODE_NORMAL;
					}
					else
					{
					LAB_6fb5ad89:
						local_114 = DRAWMODE_TRANS50;
						DVar17 = local_114;
					}
				}
				else
				{
					if (a5 != 0)
						goto LAB_6fb5ad89;
					DVar17 = local_114;
					if ((iVar5 == 0) && (iStack_cc != 0))
					{
						local_114 = DRAWMODE_HIGHLIGHT;
						DVar17 = (DrawMode)((DStack_110 & 0xff) * 2);
						if ((DStack_110 & 0xff) == 0x20 || DVar17 < 0x40)
						{
							DVar17 = (DrawMode)(0x40);
						}
						else if (0xfe < DVar17)
						{
							DVar17 = (DrawMode)(0xff);
						}
						DStack_110 = (DrawMode)(DStack_110 & 0xffffff00 | DVar17);
						DVar17 = local_114;
					}
				}
			LAB_6fb5aded:
				TEXTURE_CelDraw(&DStack_90, iStack_100, iStack_f0, DStack_110, DVar17, pbVar14);
			}
			else
			{
				if (a5 == 0)
				{
					if (iVar5 == 0)
					{
						bVar3 = sub_6FB5EFF0((uint8_t*)pUStack_b8, uVar4);
						local_114 = (DrawMode)(D2C_ZEXT(bVar3));
					}
				}
				else
				{
					local_114 = DRAWMODE_TRANS50;
				}
				DVar17 = local_114;
				if ((iStack_d8 == 0) || (iStack_e0 == 0))
					goto LAB_6fb5aded;
				iVar5 = UNITS_GetPrecisionX(pUnit);
				iVar6 = UNITS_GetPrecisionY(pUnit);
				DVar17 = local_114;
			LAB_6fb5ace8:
				TEXTURE_CelFlatSpriteDraw(&DStack_90, iVar5, iVar6, DStack_110, DVar17, iStack_fc, pbVar14);
			}
		}
	}
	else
	{
		pbVar14 = pbStack_ec;
		if (uVar4 != 0xe)
			goto LAB_6fb5abbf;
		pDVar9 = sub_6FB26AD0((int)pUnit);
		if ((pDVar9 != nullptr) &&
		    ((pDVar9->dwUnitType == 3 || (iVar5 = STATES_CheckState(pDVar9, 0x8f), iVar5 != 0))))
		{
			sub_6FB4DB40(pDVar9, DStack_110, 1);
		}
	}
	iStack_d0 = iStack_d0 + 1;
	if ((int)(uint32_t)*pbStack_dc <= iStack_d0)
	{
	LAB_6fb5ae0b:
		if (a6 != 0)
		{
			sub_6FB5A490(pUnit, DStack_110, 0, 0xffffffff, 0xffffffff, (int)(pbStack_10c));
		}
		if (pbStack_10c == nullptr)
		{
			return 1;
		}
		D2GFX_SetUnitPerspective(iStack_f8);
		return 1;
	}
	goto LAB_6fb5ab72;
}

//D2Client.0x6FB5B0F0
void __fastcall sub_6FB5B0F0(int a1, int a2, int a3, int a4, uint32_t a5, DrawMode a6)
{
	D2GFX_DrawBox(a1, a2, a3 + a1, a4 + a2, a5, a6);
}

//D2Client.0x6FB5B120
void __fastcall sub_6FB5B120(int a1)
{
	void* pvVar1;
	void* pFree;
	int iVar2;
	int local_4;

	local_4 = 0;
	while (true)
	{
		D2_ASSERT(0xf >= local_4);
		iVar2 = 0;
		do
		{
			sub_6FB5F070(a1, iVar2, 0);
			iVar2 = iVar2 + 1;
		} while (iVar2 < 0x10);
		iVar2 = sub_6FB28400(a1);
		if (iVar2 == 0)
			break;
		pFree = *(void**)(iVar2 + 0x28);
		while (pFree != nullptr)
		{
			pvVar1 = *(void**)((int)pFree + 0x10);
			D2_FREE(pFree);
			pFree = pvVar1;
		}
		*(uint32_t*)(iVar2 + 0x28) = 0;
		local_4 = local_4 + 1;
		if (0xf < local_4)
		{
			return;
		}
	}
	FOG_DisplayAssert("ptGfxInfo", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB5B1D0
void __fastcall sub_6FB5B1D0(int a1, uint8_t a2)
{
	int iVar1;
	int iVar2;

	iVar1 = sub_6FB28400(a1);
	D2_ASSERT(iVar1);
	iVar2 = 0;
	do
	{
		*(uint8_t*)(iVar1 + iVar2 * 2) = a2;
		iVar2 = iVar2 + 1;
	} while (iVar2 < 0x14);
}

//D2Client.0x6FB5B210
void __cdecl sub_6FB5B210()
{
	D2InventoryStrc* pDVar1;
	DWORD DVar2;
	D2UnitStrc* pDVar3;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t uVar7;
	int iStack_38;
	int local_34;
	uint32_t uStack_30;
	uint32_t uStack_2c;
	int iStack_28;
	int iStack_24;
	int iStack_20;
	uint32_t uStack_1c;
	uint32_t uStack_18;
	uint32_t uStack_14;
	D2ActiveRoomStrc** ppDStack_10;
	int iStack_c;
	uint32_t uStack_8;
	int iStack_4;

	if ((dword_6FBC2F9C != 0) || (DVar2 = GetTickCount(), dword_6FBC2F8C + 600 <= DVar2))
	{
		pDVar3 = CUNIT_GetPlayer();
		pRoom = UNITS_GetRoom(pDVar3);
		if (pRoom != nullptr)
		{
			DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_10, (int*)&uStack_14);
			uStack_30 = 0;
			uStack_18 = 0;
			if (uStack_14 != 0)
			{
				do
				{
					uVar7 = uStack_18;
					if (dword_6FBC2F9C == 0)
					{
					LAB_6fb5b2b5:
						uVar4 = D2CMP_10057();
						if (0x1d < uVar4)
							break;
					}
					else
					{
						if (((local_34 == 0) || (dword_6FBC2FA4 != 0)) &&
						    (uVar4 = uStack_30 & 0x1f, uStack_30 = uStack_30 + 1, uVar4 != 0))
						{
							sub_6FB242E0(1);
						}
						if (dword_6FBC2F9C == 0)
							goto LAB_6fb5b2b5;
					}
					pDVar3 = ppDStack_10[uVar7]->pUnitFirst;
					for (; pDVar3 != nullptr; pDVar3 = pDVar3->pRoomNext)
					{
						uStack_2c = 6;
						if (pDVar3 != nullptr)
						{
							uStack_2c = pDVar3->dwUnitType;
							iStack_28 = pDVar3->dwClassId;
						}
						else
						{
							iStack_28 = -1;
						}
						iStack_24 = UNITS_GetAnimOrSeqMode(pDVar3);
						D2COMMON_11013_ConvertMode(pDVar3, (int*)&uStack_2c, &iStack_28, &iStack_24,
						    __FILE__, __LINE__);
						if (uStack_2c == 1)
						{
							if ((iStack_28 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
							    ((iStack_24 != 0xc || (*(int*)(iStack_28 * 0xa0 + 0x30 + dword_6FBC2F84) == 0))))
							{
								if (pDVar3 == nullptr)
								{
									iVar5 = -1;
								}
								else
								{
									uStack_1c = pDVar3->dwFlagEx >> 3 & 1;
									if (uStack_1c == 0)
									{
										iVar5 = pDVar3->dwClassId;
									}
									else
									{
										uStack_8 = pDVar3->dwUnitType;
										iStack_20 = pDVar3->dwClassId;
										iStack_c = UNITS_GetAnimOrSeqMode(pDVar3);
										D2COMMON_11013_ConvertMode(pDVar3, (int*)&uStack_8, &iStack_20, &iStack_c,
										    __FILE__, __LINE__);
										iVar5 = iStack_20;
									}
								}
								if (((-1 < iVar5) && (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
								    ((iVar5 = sub_6FB5CC10((int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) +
								                                                  0xa78) +
								                                          0x18 + iVar5 * 0x1a8)),
								        iVar5 != 0 && (uVar7 = 0, dword_6FB96E68 != 0))))
								{
									do
									{
										pDVar1 = (D2InventoryStrc*)(&dword_6FB96E2C)[uVar7];
										if (((uint8_t)((uint8_t*)&gdwBitMasks)[((uint32_t)pDVar1 & 7) * 4] &
										        *(uint8_t*)(((uint32_t)pDVar1 >> 3) + 0xf0 + iVar5)) != 0)
										{
											sub_6FB5B920(pDVar3, pDVar1, local_34);
										}
										uVar7 = uVar7 + 1;
									} while (uVar7 < dword_6FB96E68);
								}
							}
						}
						else if (uStack_2c == 0)
						{
							if (dword_6FBC2FA4 != 0)
							{
								local_34 = 0;
							}
							uVar7 = 0;
							if (dword_6FB96E28 != 0)
							{
								do
								{
									pDVar1 = (D2InventoryStrc*)(&dword_6FB96E08)[uVar7];
									uStack_1c = 6;
									if (pDVar3 == nullptr)
									{
										iStack_38 = -1;
									}
									else
									{
										uStack_1c = pDVar3->dwUnitType;
										iStack_38 = pDVar3->dwClassId;
									}
									iStack_4 = UNITS_GetAnimOrSeqMode(pDVar3);
									D2COMMON_11013_ConvertMode(pDVar3, (int*)&uStack_1c, &iStack_38, &iStack_4,
									    __FILE__, __LINE__);
									if ((&dword_6FBC2318)[(int)(&pDVar1->dwSignature + iStack_38 * 10)] == 0)
									{
										if (*(int*)(byte_6FBC2368 + (int)(&pDVar1->dwSignature + iStack_38 * 10) * 4) == 0)
										{
											puVar6 = sub_6FB5B5A0(pDVar3, pDVar1, local_34);
											if (puVar6 == (uint32_t*)0x1)
											{
												*(uint32_t*)(byte_6FBC2368 + (int)(&pDVar1->dwSignature + iStack_38 * 10) * 4) = 1;
											}
											else
											{
												*(uint32_t*)(byte_6FBC2368 + (int)(&pDVar1->dwSignature + iStack_38 * 10) * 4) = 0;
												(&dword_6FBC2318)[(int)(&pDVar1->dwSignature + iStack_38 * 10)] = 0;
											}
										}
										else
										{
											iVar5 = D2CMP_10058(uStack_1c, iStack_38 * 5, uStack_1c, (int)pDVar1, iStack_38);
											if (iVar5 == 0)
											{
												(&dword_6FBC2318)[(int)(&pDVar1->dwSignature + iStack_38 * 10)] = 1;
											}
										}
									}
									uVar7 = uVar7 + 1;
								} while (uVar7 < dword_6FB96E28);
							}
						}
						if ((dword_6FBC2F9C == 0) && (uVar7 = D2CMP_10057(), 0x1d < uVar7))
							goto LAB_6fb5b57e;
						uVar7 = uStack_18;
					}
					uStack_18 = uVar7 + 1;
				} while (uStack_18 < uStack_14);
			}
		}
	LAB_6fb5b57e:
		dword_6FBC2F8C = GetTickCount();
	}
}

//D2Client.0x6FB5B5A0
// TODO: decompilation needs review (extraout)
uint32_t* __fastcall sub_6FB5B5A0(D2UnitStrc* pUnit, D2InventoryStrc* pInventory2, int a3)
{
	int* piVar1;
	Unicode* pUVar2;
	bool bVar3;
	uint8_t bVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	uint32_t uVar7;
	uint32_t extraout_var;
	D2InventoryStrc* pDVar8;
	uint32_t* puVar9;
	int iVar10;
	uint8_t* pbVar11;
	int a2;
	uint32_t* puVar12;
	D2CellFileStrc* pDVar13;
	D2InventoryStrc** ppDVar14;
	uint8_t bVar15;
	char* pcVar16;
	uint32_t uVar17;
	D2InventoryStrc* pDVar18;
	D2InventoryStrc* pDStack_178;
	uint8_t* pbStack_174;
	D2InventoryStrc* pDStack_170;
	uint32_t* local_16c;
	uint32_t uStack_168;
	int iStack_164;
	int iStack_160;
	D2InventoryStrc* local_15c;
	uint32_t local_158;
	int iStack_154;
	int local_150;
	uint32_t uStack_14c;
	uint32_t auStack_148[6];
	uint8_t bStack_130;
	char acStack_100[256];

	local_16c = (uint32_t*)0x1;
	local_15c = pInventory2;
	if ((((pUnit == nullptr) || (local_158 = pUnit->dwFlagEx >> 3 & 1, local_158 == 0)) || (iVar5 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar5 == 0)) ||
	    (pDVar6 = sub_6FB26AD0((int)pUnit), pDVar6 == nullptr))
	{
		pDVar8 = pUnit->pInventory;
	}
	else
	{
		pDVar8 = pDVar6->pInventory;
	}
	uVar7 = COMPOSIT_GetWeaponClassId(pUnit, pDVar8, &local_150, (int)pInventory2, 0);
	pDStack_170 = pInventory2;
	iVar5 = sub_6FB28400((int)pUnit);
	D2_ASSERT(iVar5);
	pDVar8 = pDStack_170;
	if (pInventory2 == (D2InventoryStrc*)0xffffffff)
	{
		bVar3 = sub_6FB5BEA0((int)pUnit, 8);
		if (D2C_ZEXT(bVar3) == 0)
		{
			pDVar8 = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
		}
		else
		{
			pDStack_170 = (D2InventoryStrc*)pUnit->dwUnitType;
			pbStack_174 = (uint8_t*)pUnit->dwClassId;
			pDStack_178 = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&pDStack_170, (int*)&pbStack_174, (int*)&pDStack_178,
			    __FILE__, __LINE__);
			pDVar8 = pDStack_178;
		}
	}
	for (puVar9 = *(uint32_t**)(iVar5 + 0x28); puVar9 != nullptr; puVar9 = (uint32_t*)puVar9[4])
	{
		if (((D2InventoryStrc*)*puVar9 == pDVar8) && (puVar9[1] == uVar7))
			goto LAB_6fb5b6fb;
	}
	puVar9 = sub_6FB58410(pUnit, uVar7, pInventory2);
	if (puVar9 == nullptr)
	{
		sprintf(acStack_100, "sAsyncLoadBlock failed on async:%d unittype:%d unitclass:%d unitmode:%d weaponclass:%d wclass:%d\n", a3, pUnit->dwUnitType,
		    pUnit->dwClassId, pInventory2, local_150, uVar7);
		FOG_Trace(acStack_100);
		return nullptr;
	}
LAB_6fb5b6fb:
	iVar5 = sub_6FB28400((int)pUnit);
	if (iVar5 != 0)
	{
		for (piVar1 = *(int**)(iVar5 + 0x28); piVar1 != nullptr; piVar1 = (int*)piVar1[4])
		{
			if ((D2InventoryStrc*)*piVar1 == pInventory2)
			{
				pUVar2 = *(Unicode**)(piVar1[2] + 0x14);
				if (pUVar2 != nullptr)
				{
					pbStack_174 = (uint8_t*)sub_6FB5EF30(pUVar2);
					D2_ASSERT(pbStack_174 != nullptr);
					bVar15 = pbStack_174[2];
					iStack_160 = 0;
					bVar4 = UNITS_GetDirection(pUnit);
					local_158 = (uint32_t)bVar4;
					uStack_168 = pUnit->dwUnitType;
					iStack_164 = pUnit->dwClassId;
					iStack_154 = UNITS_GetAnimOrSeqMode(pUnit);
					D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_168, &iStack_164, &iStack_154,
					    __FILE__, __LINE__);
					pDVar8 = local_15c;
					sub_6FB5F090(pUnit, uStack_168, iStack_164, &local_15c->dwSignature, &local_158, (uint32_t*)(&iStack_160),
					    &uStack_14c, (uint32_t)bVar15, 0);
					pbVar11 = sub_6FB5EFC0((uint8_t*)pUVar2, iStack_160, 0);
					if (pbVar11 != nullptr)
					{
						pDStack_178 = nullptr;
						if (*pbStack_174 != 0)
						{
							do
							{
								bVar15 = pbVar11[(int)pDStack_178];
								D2_ASSERT(0xf >= bVar15);
								ppDVar14 = &local_15c;
								pDVar13 = nullptr;
								puVar12 = auStack_148;
								for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
								{
									*puVar12 = 0;
									puVar12 = puVar12 + 1;
								}
								pDVar18 = pDVar8;
								bVar4 = UNITS_GetDirection(pUnit);
								iVar5 = sub_6FB5EC80((int)auStack_148, pUnit, 0, (D2CellFileStrc*)(uint32_t)bVar4,
								    pDVar13, ppDVar14, bVar15, pDVar18);
								if ((iVar5 != 0) &&
								    (iVar5 = D2CMP_10055((int)auStack_148, a3, a3), iVar5 == 0))
								{
									auStack_148[1] = 0;
									iVar5 = D2CMP_10056((int)auStack_148, a2, (int)auStack_148);
									if (iVar5 == 0)
									{
										return (uint32_t*)0xffffffff;
									}
									if ((bStack_130 & 4) == 0)
									{
										local_16c = nullptr;
									}
								}
								pDStack_178 = (D2InventoryStrc*)((int)&pDStack_178->dwSignature + 1);
							} while ((int)pDStack_178 < (int)(uint32_t)*pbStack_174);
						}
						return local_16c;
					}
					FOG_DisplayAssert("lpbCompByte", __FILE__, __LINE__);
					exit(-1);
				}
				break;
			}
		}
	}
	iVar5 = pUnit->dwClassId;
	uVar7 = pUnit->dwUnitType;
	uVar17 = 0x6b7;
	pcVar16 = __FILE__;
	iVar10 = UNITS_GetAnimOrSeqMode(pUnit);
	FOG_Trace("Unable to get cof file for unit type:%d  class:%d  mode:%d in file:%s  line:%d", uVar7, iVar5, iVar10, pcVar16, uVar17);
	return nullptr;
}

//D2Client.0x6FB5B920
void __fastcall sub_6FB5B920(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, uint32_t a3)
{
	uint32_t* puVar1;
	int iVar2;
	int local_c;
	uint32_t local_8;
	int iStack_4;

	local_8 = 6;
	if (pUnit == nullptr)
	{
		local_c = -1;
	}
	else
	{
		local_8 = pUnit->dwUnitType;
		local_c = pUnit->dwClassId;
	}
	iStack_4 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_8, &local_c, &iStack_4, __FILE__, __LINE__);
	if ((local_c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
	    (*(int*)(dword_6FBC2F84 + (int)(&pInventory->dwSignature + local_c * 10) * 4) == 0))
	{
		if (*(int*)(dword_6FBC2F84 + 0x50 + (int)(&pInventory->dwSignature + local_c * 10) * 4) == 0)
		{
			puVar1 = sub_6FB5B5A0(pUnit, pInventory, a3);
			if (puVar1 == (uint32_t*)0x1)
			{
				*(uint32_t*)(dword_6FBC2F84 + 0x50 + (int)(&pInventory->dwSignature + local_c * 10) * 4) = 1;
				return;
			}
			*(uint32_t*)(dword_6FBC2F84 + 0x50 + (int)(&pInventory->dwSignature + local_c * 10) * 4) = 0;
			*(uint32_t*)(dword_6FBC2F84 + (int)(&pInventory->dwSignature + local_c * 10) * 4) = 0;
			return;
		}
		iVar2 = D2CMP_10058(local_8, dword_6FBC2F84, local_8, (int)pInventory, local_c);
		if (iVar2 == 0)
		{
			*(uint32_t*)(dword_6FBC2F84 + (int)(&pInventory->dwSignature + local_c * 10) * 4) = 1;
		}
	}
}

//D2Client.0x6FB5BA40
uint32_t __fastcall sub_6FB5BA40(int a1)
{
	int iVar1;

	iVar1 = sub_6FB28400(a1);
	if (iVar1 != 0)
	{
		return *(uint32_t*)(iVar1 + 0x30);
	}
	return 0;
}

//D2Client.0x6FB5BA50
void __fastcall sub_6FB5BA50(int a1, uint32_t a2)
{
	int iVar1;

	iVar1 = sub_6FB28400(a1);
	if (iVar1 != 0)
	{
		*(uint32_t*)(iVar1 + 0x30) = a2;
	}
}

//D2Client.0x6FB5BA70
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB5BA70(D2UnitStrc* pUnit, int a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7, int a8)
{
	int iVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	uint32_t* puVar6;
	uint32_t uVar7;
	int iVar8;
	uint32_t uVar9;
	uint32_t* puVar10;
	uint32_t extraout_ECX;
	int extraout_EDX;
	uint32_t* puVar11;

	if (a2 < 0)
	{
		return;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0) <= a2)
	{
		return;
	}
	iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbbc) + a2 * 0x84;
	if (iVar1 == 0)
	{
		return;
	}
	iVar4 = FOG_IsExpansion();
	if ((iVar4 == 0) && (99 < *(short*)(iVar1 + 0x42)))
	{
		return;
	}
	pDVar5 = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		if ((pUnit->dwFlagEx >> 0x12 & 1) != 0)
		{
			return;
		}
		if (((((pUnit->dwUnitType == 1) && (iVar4 = pUnit->dwClassId, -1 < iVar4)) &&
		         (iVar8 = *(int*)((uint8_t*)&sgptDataTables), iVar4 < *(int*)(iVar8 + 0xa80))) &&
		        ((iVar4 = (int)*(short*)(*(int*)(iVar8 + 0xa78) + 0x18 + iVar4 * 0x1a8), -1 < iVar4 &&
		                                                                                     (iVar4 < *(int*)(iVar8 + 0xa98))))) &&
		    ((iVar4 = *(int*)(iVar8 + 0xa90) + iVar4 * 0x134, iVar4 != 0 &&
		                                                          (((uint32_t) * (uint8_t*)(iVar4 + 4) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 8)) != 0))))
		{
			return;
		}
	}
	if (a3 == 8)
	{
		iVar4 = sub_6FB28400((int)pUnit);
		D2_ASSERT(iVar4);
		for (iVar4 = *(int*)(iVar4 + 0x2c); iVar4 != 0; iVar4 = *(int*)(iVar4 + 0xa4))
		{
			if (*(int*)(iVar4 + 4) == a2)
			{
				return;
			}
		}
	}
	if ((a2 < 0x8c) || ((0x8e < a2 && (a2 != 0x9e))))
	{
		sub_6FB5BEC0(pUnit, (uint32_t) * (uint8_t*)(iVar1 + 0x48), a2);
	}
	puVar6 = (uint32_t*)D2_ALLOC(0xa8);
	D2_ASSERT(puVar6 != nullptr);
	puVar11 = puVar6;
	for (iVar4 = 0x2a; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*puVar11 = 0;
		puVar11 = puVar11 + 1;
	}
	puVar6[1] = a2;
	*puVar6 = a3;
	uVar7 = sub_6FB5F9D0(pUnit, (int)puVar6);
	puVar6[7] = uVar7;
	if (a3 == 2)
	{
		puVar6[2] = 1;
	}
	else if (a3 == 6)
	{
		if ((int)uVar7 < 1)
		{
			puVar6[6] = 0;
		}
		else
		{
			uVar9 = (pDVar5->pSeed).nLowSeed;
			uVar3 = (uint64_t)(pDVar5->pSeed).nHighSeed;
			if ((uVar7 & uVar7 - 1) == 0)
			{
				DVar2 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar3);
				(*(uint64_t*)&pDVar5->pSeed) = DVar2;
				puVar6[6] = uVar7 - 1 & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar3);
				(*(uint64_t*)&pDVar5->pSeed) = DVar2;
				puVar6[6] = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar7);
			}
		}
	}
	else
	{
		puVar6[2] = a5;
		puVar6[3] = a6;
		puVar6[4] = a7;
	}
	puVar6[8] = *(uint32_t*)(iVar1 + 0x54);
	puVar6[9] = *(uint32_t*)(iVar1 + 0x58);
	iVar8 = UNITS_GetOverlayHeight(pUnit);
	uVar7 = extraout_ECX;
	iVar4 = extraout_EDX;
	switch (iVar8)
	{
	case 0:
		iVar4 = *(int*)(iVar1 + 0x5c);
		goto LAB_6fb5bcf4;
	case 1:
		uVar7 = puVar6[9] + *(int*)(iVar1 + 0x60);
		puVar6[9] = uVar7;
		goto switchD_6fb5bcc6_default;
	case 2:
		uVar7 = *(uint32_t*)(iVar1 + 100);
		uVar9 = puVar6[9] + uVar7;
		break;
	case 3:
		iVar4 = *(int*)(iVar1 + 0x68);
	LAB_6fb5bcf4:
		uVar9 = puVar6[9] + iVar4;
		break;
	case -1:
		uVar9 = puVar6[9] + 0x4b;
		break;
	default:
		goto switchD_6fb5bcc6_default;
	}
	puVar6[9] = uVar9;
switchD_6fb5bcc6_default:
	if (*(int*)(iVar1 + 0x74) != 0)
	{
		puVar10 = sub_6FAA4280(pUnit, 1, *(int*)(iVar1 + 0x70), 0xff,
		    CONCAT31((int32_t)((uint32_t)iVar4 >> 8), *(uint8_t*)(iVar1 + 0x7d)),
		    D2C_ZEXT(*(uint8_t*)(iVar1 + 0x7e)),
		    CONCAT31((int32_t)((uint32_t) * (int*)(iVar1 + 0x74) >> 8),
		        *(uint8_t*)(iVar1 + 0x7f)));
		puVar6[0x10] = (uint32_t)puVar10;
		if (*(int*)(iVar1 + 0x74) != *(int*)(iVar1 + 0x70))
		{
			sub_6FAA43A0((int)puVar10, *(int*)(iVar1 + 0x74));
		}
	}
	iVar4 = sub_6FB28400((int)pUnit);
	D2_ASSERT(iVar4);
	puVar6[0xd] = (uint32_t) * (uint8_t*)(iVar1 + 0x48);
	puVar6[0x29] = *(uint32_t*)(iVar4 + 0x2c);
	*(uint32_t**)(iVar4 + 0x2c) = puVar6;
	if (*puVar6 == 8)
	{
		puVar6[0xe] = a5;
		for (puVar11 = *(uint32_t**)(iVar4 + 0x2c); puVar11 != nullptr; puVar11 = (uint32_t*)puVar11[0x29])
		{
			if ((*puVar11 == 8) && (puVar11 != puVar6))
			{
				if (puVar11[0xe] == a5)
				{
					puVar6[0xf] = puVar11[0xf];
					puVar6[2] = puVar11[2];
					goto LAB_6fb5bdaf;
				}
				if (puVar11[0xf] != 0)
				{
					puVar6[0xf] = 0;
					goto LAB_6fb5bdaf;
				}
			}
		}
		puVar6[0xf] = 1;
		puVar6[2] = 0;
	}
LAB_6fb5bdaf:
	if (a4 != 0)
	{
		uVar7 = a4 * 0x100;
		if ((int)uVar7 < 1)
		{
			uVar7 = 0;
		}
		else
		{
			uVar3 = (uint64_t)(pDVar5->pSeed).nHighSeed;
			uVar9 = (pDVar5->pSeed).nLowSeed;
			if ((uVar7 & uVar7 - 1) == 0)
			{
				DVar2 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar3);
				(*(uint64_t*)&pDVar5->pSeed) = DVar2;
				uVar7 = uVar7 - 1 & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar3);
				(*(uint64_t*)&pDVar5->pSeed) = DVar2;
				uVar7 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar7);
			}
		}
		puVar6[6] = uVar7;
	}
	puVar6[5] = *(int*)(iVar1 + 0x6c) << 4;
	if (a8 != 0)
	{
		uVar7 = a8 * 0x10;
		if ((int)uVar7 < 1)
		{
			uVar7 = 0;
		}
		else
		{
			uVar9 = (pDVar5->pSeed).nLowSeed;
			uVar3 = (uint64_t)(pDVar5->pSeed).nHighSeed;
			if ((uVar7 & uVar7 - 1) == 0)
			{
				DVar2 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar3);
				(*(uint64_t*)&pDVar5->pSeed) = DVar2;
				uVar7 = uVar7 - 1 & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar3);
				(*(uint64_t*)&pDVar5->pSeed) = DVar2;
				uVar7 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar7);
			}
		}
		puVar6[5] = puVar6[5] + uVar7;
	}
	puVar6[10] = *(uint32_t*)(iVar1 + 0x78);
}

//D2Client.0x6FB5BEA0
bool __fastcall sub_6FB5BEA0(int a1, uint32_t a2)
{
	if (a1 == 0)
	{
		return false;
	}
	return (*(uint32_t*)(a1 + 200) & a2) != 0;
}

//D2Client.0x6FB5BEC0
void __fastcall sub_6FB5BEC0(D2UnitStrc* pUnit, int a2, int a3)
{
	int* piVar1;
	int iVar2;
	int* piVar3;

	if (pUnit != nullptr)
	{
		iVar2 = sub_6FB28400((int)pUnit);
		if (iVar2 != 0)
		{
			if (((a3 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0) <= a3)) ||
			    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbbc) + a3 * 0x84 == 0))
			{
				FOG_DisplayAssert("ptStats", __FILE__, __LINE__);
				exit(-1);
			}
			piVar3 = *(int**)(iVar2 + 0x2c);
			if (*(int**)(iVar2 + 0x2c) != nullptr)
			{
				while ((piVar1 = piVar3 + 0x29, piVar3[1] != a3 &&
				                                    (((*piVar3 != 4 && (*piVar3 != 9)) ||
				                                        ((piVar3[2] != a3 && (piVar3[3] != a3)))))))
				{
					piVar3 = (int*)*piVar1;
					if ((int*)*piVar1 == nullptr)
					{
						return;
					}
				}
				sub_6FB58270((int)pUnit, piVar3);
			}
		}
	}
}

//D2Client.0x6FB5BF70
void __fastcall sub_6FB5BF70(int a1)
{
	int* piVar1;
	int* piVar2;
	int iVar3;

	iVar3 = sub_6FB28400(a1);
	D2_ASSERT(iVar3);
	piVar2 = *(int**)(iVar3 + 0x2c);
	while (piVar2 != nullptr)
	{
		piVar1 = (int*)piVar2[0x29];
		sub_6FB58270(a1, piVar2);
		piVar2 = piVar1;
	}
}

//D2Client.0x6FB5BFC0
void __fastcall sub_6FB5BFC0(int ptInfo, uint32_t a2)
{
	D2_ASSERT(ptInfo);
	*(uint32_t*)(ptInfo + 0x34) = a2;
}

//D2Client.0x6FB5BFF0
uint32_t __fastcall sub_6FB5BFF0(int ptInfo)
{
	D2_ASSERT(ptInfo);
	return *(uint32_t*)(ptInfo + 0x34);
}

//D2Client.0x6FB5C020
void __fastcall sub_6FB5C020(int ptInfo, uint32_t a2)
{
	D2_ASSERT(ptInfo);
	*(uint32_t*)(ptInfo + 0x38) = a2;
}

//D2Client.0x6FB5C050
uint32_t __fastcall sub_6FB5C050(int ptInfo)
{
	D2_ASSERT(ptInfo);
	return *(uint32_t*)(ptInfo + 0x38);
}

//D2Client.0x6FB5C080
D2UnitStrc* __fastcall sub_6FB5C080(D2UnitStrc* pUnit)
{
	void* pvVar1;
	void* pFree;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uStack_1c;
	uint32_t local_18;
	uint32_t uStack_14;
	D2UnitStrc* pDStack_10;
	int local_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	local_18 = 6;
	if (pUnit == nullptr)
	{
		local_c = -1;
	}
	else
	{
		local_18 = pUnit->dwUnitType;
		local_c = pUnit->dwClassId;
	}
	uStack_1c = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_18, &local_c, (int*)&uStack_1c,
	    __FILE__, __LINE__);
	uVar5 = uStack_1c;
	if (local_18 == 0)
	{
		pDVar2 = (D2UnitStrc*)sub_6FB58720(pUnit, (int)&uStack_4, uStack_1c);
		if (pDVar2 != nullptr)
		{
			pDVar2 = (D2UnitStrc*)sub_6FB5F070((int)pUnit, uVar5, 1);
		}
	}
	else
	{
		if (local_18 != 1)
		{
			if (local_18 == 2)
			{
				pDVar2 = (D2UnitStrc*)sub_6FB58F90(pUnit, uStack_1c);
				return pDVar2;
			}
			FOG_DisplayAssert("0", __FILE__, __LINE__);
			exit(-1);
		}
		uStack_8 = 6;
		if (pUnit == nullptr)
		{
			pDStack_10 = (D2UnitStrc*)0xffffffff;
		}
		else
		{
			uStack_8 = pUnit->dwUnitType;
			pDStack_10 = (D2UnitStrc*)pUnit->dwClassId;
		}
		uStack_14 = UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_8, (int*)&pDStack_10, (int*)&uStack_14,
		    __FILE__, __LINE__);
		if (uVar5 == 0xe)
		{
			uVar5 = uStack_14;
		}
		pDVar2 = pDStack_10;
		if ((((-1 < (int)pDStack_10) &&
		         (iVar3 = *(int*)((uint8_t*)&sgptDataTables), (int)pDStack_10 < *(int*)(iVar3 + 0xa80))) &&
		        (pDVar2 = (D2UnitStrc*)(int)*(short*)(*(int*)(iVar3 + 0xa78) + 0x18 + (int)pDStack_10 * 0x1a8),
		            -1 < (int)pDVar2)) &&
		    ((((int)pDVar2 < *(int*)(iVar3 + 0xa98) &&
		          (pDVar2 = (D2UnitStrc*)(*(int*)(iVar3 + 0xa90) + (int)pDVar2 * 0x134),
		              pDVar2 != nullptr)) &&
		        (uStack_4 = (uint32_t) * (uint8_t*)((int)pDVar2->unk0xBC + ((int)uVar5 >> 3) + 0x34) &
		                    *(uint32_t*)(((uint8_t*)&gdwBitMasks) + (uVar5 & 7) * 4),
		            pDVar2 = (D2UnitStrc*)((uint8_t*)&gdwBitMasks), uStack_4 != 0))))
		{
			if (uVar5 != 0xc)
			{
				if (uVar5 == 0xe)
				{
					uVar5 = uStack_14;
				}
				pDVar2 = (D2UnitStrc*)sub_6FB58E40(pUnit, uVar5);
				return pDVar2;
			}
			iVar3 = sub_6FB28400((int)pUnit);
			if (iVar3 != 0)
			{
				pFree = *(void**)(iVar3 + 0x28);
				while (pFree != nullptr)
				{
					pvVar1 = *(void**)((int)pFree + 0x10);
					D2_FREE(pFree);
					pFree = pvVar1;
				}
				*(uint32_t*)(iVar3 + 0x28) = 0;
				iVar3 = sub_6FB28400((int)pUnit);
				if (iVar3 != 0)
				{
					iVar4 = 0;
					do
					{
						*(uint8_t*)(iVar3 + iVar4 * 2) = 0;
						iVar4 = iVar4 + 1;
					} while (iVar4 < 0x14);
					pDVar2 = (D2UnitStrc*)sub_6FB58E40(pUnit, 0xc);
					return pDVar2;
				}
				FOG_DisplayAssert("ptGfxInfo", __FILE__, __LINE__);
				exit(-1);
			}
			FOG_DisplayAssert("ptGfxInfo", __FILE__, __LINE__);
			exit(-1);
		}
	}
	return pDVar2;
}

//D2Client.0x6FB5C2E0
void __fastcall sub_6FB5C2E0(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t local_c;
	int iStack_8;
	int local_4;

	if (a2 < 0x10)
	{
		if (pUnit == nullptr)
		{
			uVar2 = 6;
		}
		else if ((pUnit->dwFlagEx >> 3 & 1) == 0)
		{
			local_4 = 0;
			uVar2 = pUnit->dwUnitType;
		}
		else
		{
			local_c = pUnit->dwUnitType;
			local_4 = pUnit->dwClassId;
			iStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_4, &iStack_8, __FILE__, __LINE__);
			uVar2 = local_c;
		}
		if (uVar2 != 0)
		{
			if (uVar2 == 1)
			{
				iVar1 = 0;
				do
				{
					sub_6FB5F070((int)pUnit, iVar1, 0);
					iVar1 = iVar1 + 1;
				} while (iVar1 < 0x10);
				return;
			}
			D2_ASSERT(uVar2 == 2);
			iVar1 = 0;
			do
			{
				sub_6FB5F070((int)pUnit, iVar1, 0);
				iVar1 = iVar1 + 1;
			} while (iVar1 < 8);
			return;
		}
		uVar2 = 0;
		do
		{
			sub_6FB5F070((int)pUnit, uVar2, 0);
			uVar2 = uVar2 + 1;
		} while (uVar2 < 0x14);
	}
}

//D2Client.0x6FB5C3C0
void __fastcall sub_6FB5C3C0(D2UnitStrc* pUnit, int a2, int* a3, int* a4)
{
	int* piVar1;
	uint8_t bVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t* puVar7;
	uint8_t uVar8;
	D2CellFileStrc* pDVar9;
	D2CellFileStrc** ppDVar10;
	D2InventoryStrc** ppDVar11;
	D2InventoryStrc* pDVar12;
	int iStack_6c;
	int iStack_68;
	int local_64;
	uint32_t local_60;
	int iStack_5c;
	uint32_t uStack_58;
	D2DynamicPathStrc* local_54;
	int iStack_50;
	D2InventoryStrc* pDStack_4c;
	D2CellFileStrc* apDStack_48[18];

	uVar8 = (uint8_t)a2;
	local_54 = pUnit->pDynamicPath;
	local_60 = pUnit->dwUnitType;
	local_64 = pUnit->dwClassId;
	iStack_6c = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_60, &local_64, &iStack_6c,
	    __FILE__, __LINE__);
	uStack_58 = pUnit->dwFlagEx >> 3 & 1;
	if (((uStack_58 == 0) || (iVar3 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar3 == 0)) ||
	    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 == nullptr))
	{
		pDVar12 = pUnit->pInventory;
	}
	else
	{
		pDVar12 = pDVar4->pInventory;
	}
	uVar5 = COMPOSIT_GetWeaponClassId(pUnit, pDVar12, &iStack_50, iStack_6c, 0);
	iVar3 = sub_6FB28400((int)pUnit);
	D2_ASSERT(iVar3);
	uStack_58 = pUnit->dwFlagEx >> 3 & 1;
	if (uStack_58 == 0)
	{
		iVar6 = UNITS_GetAnimOrSeqMode(pUnit);
	}
	else
	{
		uStack_58 = pUnit->dwUnitType;
		iStack_5c = pUnit->dwClassId;
		iStack_68 = UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_58, &iStack_5c, &iStack_68, __FILE__, __LINE__);
		iVar6 = iStack_68;
	}
	for (piVar1 = *(int**)(iVar3 + 0x28); piVar1 != nullptr; piVar1 = (int*)piVar1[4])
	{
		if ((*piVar1 == iVar6) && (piVar1[1] == uVar5))
			goto LAB_6fb5c4f6;
	}
	puVar7 = sub_6FB58410(pUnit, uVar5, (D2InventoryStrc*)0xffffffff);
	if (puVar7 == nullptr)
	{
		return;
	}
LAB_6fb5c4f6:
	iVar3 = iStack_6c;
	iVar6 = sub_6FB28400((int)pUnit);
	if (iVar6 != 0)
	{
		for (piVar1 = *(int**)(iVar6 + 0x28); piVar1 != nullptr; piVar1 = (int*)piVar1[4])
		{
			if (*piVar1 == iVar3)
			{
				if (*(int*)(piVar1[2] + 0x14) != 0)
				{
					iVar3 = pUnit->nSeqCurrentFramePrecise;
					ppDVar10 = apDStack_48;
					for (iVar6 = 0x12; iVar6 != 0; iVar6 = iVar6 + -1)
					{
						*ppDVar10 = nullptr;
						ppDVar10 = ppDVar10 + 1;
					}
					pDVar12 = (D2InventoryStrc*)0xffffffff;
					ppDVar11 = &pDStack_4c;
					pDVar9 = (D2CellFileStrc*)(iVar3 >> 8);
					bVar2 = PATH_GetDirection(local_54);
					iVar3 = sub_6FB5EC80((int)apDStack_48, pUnit, 0, (D2CellFileStrc*)(uint32_t)bVar2, pDVar9,
					    ppDVar11, uVar8, pDVar12);
					if (iVar3 == 0)
					{
						return;
					}
					iVar3 = D2CMP_10055((int)apDStack_48, 0, 1);
					if (iVar3 == 0)
					{
						return;
					}
					if (apDStack_48[0] != nullptr)
					{
						iVar3 = D2CMP_CelGetOffsetX(apDStack_48[0]);
						*a3 = iVar3;
						iVar3 = D2CMP_CelGetOffsetY(apDStack_48[0]);
						*a4 = iVar3;
						return;
					}
					FOG_DisplayAssert("tCelContext.hCel", __FILE__, __LINE__);
					exit(-1);
				}
				break;
			}
		}
	}
	FOG_Trace("Unable to get cof file for unit type:%d  class:%d  mode:%d in file:%s  line:%d", local_60, local_64, iStack_6c,
	    __FILE__, __LINE__);
}

//D2Client.0x6FB5C600
uint32_t __fastcall sub_6FB5C600(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5)
{
	int* piVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	D2InventoryStrc* pInventory;
	uint32_t uVar4;
	int iVar5;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	uint32_t uStack_10;
	int iStack_c;
	uint32_t local_8;
	int local_4;

	if ((((pUnit == nullptr) || (local_8 = pUnit->dwFlagEx >> 3 & 1, local_8 == 0)) ||
	        (iVar2 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar2 == 0)) ||
	    (pDVar3 = sub_6FB26AD0((int)pUnit), pDVar3 == nullptr))
	{
		pInventory = pUnit->pInventory;
	}
	else
	{
		pInventory = pDVar3->pInventory;
	}
	uVar4 = COMPOSIT_GetWeaponClassId(pUnit, pInventory, &local_4, -1, 1);
	iVar2 = sub_6FB28400((int)pUnit);
	D2_ASSERT(iVar2);
	uStack_10 = pUnit->dwFlagEx >> 3 & 1;
	if (uStack_10 == 0)
	{
		iVar5 = UNITS_GetAnimOrSeqMode(pUnit);
	}
	else
	{
		uStack_10 = pUnit->dwUnitType;
		iStack_14 = pUnit->dwClassId;
		iStack_1c = UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_10, &iStack_14, &iStack_1c, __FILE__, __LINE__);
		iVar5 = iStack_1c;
	}
	for (piVar1 = *(int**)(iVar2 + 0x28); piVar1 != nullptr; piVar1 = (int*)piVar1[4])
	{
		if ((*piVar1 == iVar5) && (piVar1[1] == uVar4))
			goto LAB_6fb5c6f2;
	}
	sub_6FB58410(pUnit, uVar4, (D2InventoryStrc*)0xffffffff);
LAB_6fb5c6f2:
	local_8 = pUnit->dwUnitType;
	iStack_c = pUnit->dwClassId;
	iStack_18 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_8, &iStack_c, &iStack_18,
	    __FILE__, __LINE__);
	iVar2 = iStack_18;
	iVar5 = sub_6FB28400((int)pUnit);
	if (iVar5 != 0)
	{
		for (piVar1 = *(int**)(iVar5 + 0x28); piVar1 != nullptr; piVar1 = (int*)piVar1[4])
		{
			if (*piVar1 == iVar2)
			{
				if (*(Unicode**)(piVar1[2] + 0x14) == nullptr)
				{
					return 0;
				}
				iVar2 = (int)(sub_6FB5EF30(*(Unicode**)(piVar1[2] + 0x14)));
				if (iVar2 == 0)
				{
					FOG_DisplayAssert("ptCofHeader", __FILE__, __LINE__);
					exit(-1);
				}
				if (a4 < *(int*)(iVar2 + 8) + -0x10 + a2)
				{
					return 0;
				}
				if (*(int*)(iVar2 + 0xc) + 0x10 + a2 <= a4)
				{
					return 0;
				}
				if (a5 < *(int*)(iVar2 + 0x10) + -0x10 + a3)
				{
					return 0;
				}
				if (*(int*)(iVar2 + 0x14) + 0x10 + a3 <= a5)
				{
					return 0;
				}
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB5C7D0
int* __fastcall sub_6FB5C7D0(D2UnitStrc* pUnit, int a2, int a3, uint32_t a4, int a5)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2InventoryStrc* pInventory;
	uint32_t uVar3;
	int iVar4;
	int* piVar5;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	uint32_t uStack_10;
	int iStack_c;
	uint32_t local_8;
	int local_4;

	if ((((pUnit == nullptr) || (local_8 = pUnit->dwFlagEx >> 3 & 1, local_8 == 0)) ||
	        (iVar1 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar1 == 0)) ||
	    (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 == nullptr))
	{
		pInventory = pUnit->pInventory;
	}
	else
	{
		pInventory = pDVar2->pInventory;
	}
	uVar3 = COMPOSIT_GetWeaponClassId(pUnit, pInventory, &local_4, -1, 1);
	iVar1 = sub_6FB28400((int)pUnit);
	D2_ASSERT(iVar1);
	uStack_10 = pUnit->dwFlagEx >> 3 & 1;
	if (uStack_10 == 0)
	{
		iVar4 = UNITS_GetAnimOrSeqMode(pUnit);
	}
	else
	{
		uStack_10 = pUnit->dwUnitType;
		iStack_14 = pUnit->dwClassId;
		iStack_1c = UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_10, &iStack_14, &iStack_1c, __FILE__, __LINE__);
		iVar4 = iStack_1c;
	}
	for (piVar5 = *(int**)(iVar1 + 0x28); piVar5 != nullptr; piVar5 = (int*)piVar5[4])
	{
		if ((*piVar5 == iVar4) && (piVar5[1] == uVar3))
			goto LAB_6fb5c8c2;
	}
	sub_6FB58410(pUnit, uVar3, (D2InventoryStrc*)0xffffffff);
LAB_6fb5c8c2:
	local_8 = pUnit->dwUnitType;
	iStack_c = pUnit->dwClassId;
	iStack_18 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_8, &iStack_c, &iStack_18,
	    __FILE__, __LINE__);
	iVar1 = iStack_18;
	iVar4 = sub_6FB28400((int)pUnit);
	if ((iVar4 != 0) && (piVar5 = *(int**)(iVar4 + 0x28), piVar5 != nullptr))
	{
		while (*piVar5 != iVar1)
		{
			piVar5 = (int*)piVar5[4];
			if (piVar5 == nullptr)
			{
				return piVar5;
			}
		}
		if (*(Unicode**)(piVar5[2] + 0x14) != nullptr)
		{
			iVar1 = (int)(sub_6FB5EF30(*(Unicode**)(piVar5[2] + 0x14)));
			D2_ASSERT(iVar1);
			iVar4 = *(int*)(iVar1 + 8) + a2;
			if (a5 != 0)
			{
				iVar4 = iVar4 - (*(int*)(iVar1 + 0x14) - *(int*)(iVar1 + 0x10)) / 2;
			}
			if (gnScreenWidth + -1 <= iVar4)
			{
				return nullptr;
			}
			if (*(int*)(iVar1 + 0xc) + a2 < 0)
			{
				return nullptr;
			}
			if (-1 < *(int*)(iVar1 + 0x14) + a3)
			{
				return (int*)(uint32_t)(*(int*)(iVar1 + 0x10) + a3 < gnScreenHeight + -1);
			}
			return nullptr;
		}
	}
	return nullptr;
}

//D2Client.0x6FB5C9E0
void __fastcall sub_6FB5C9E0(uint32_t a1)
{
	int iVar1;
	uint32_t uVar2;
	HD2ARCHIVE__* pHVar3;
	uint32_t uVar4;
	int iVar5;
	D2CellFileStrc* pDVar6;
	uint32_t* puVar7;
	int* piVar8;
	char* pcVar9;
	uint32_t uVar10;
	CHAR local_104[260];

	wsprintfA(local_104, "%s\\%s", "DATA\\GLOBAL",
	    (&gpuint8_t_6FB96E6C)[a1 & 0xff]);
	if (dword_6FBC2778 == 0)
	{
		uVar10 = 0x10d;
		pcVar9 = __FILE__;
		piVar8 = &dword_6FBC2780;
		pHVar3 = D2Win_GetArchive();
		ptr_6FBC277C = (uint8_t*)(ARCHIVE_AllocateBufferAndReadFile((HD2ARCHIVE)((HSFILE__*)pHVar3), local_104, (size_t*)(piVar8), pcVar9, uVar10));
		D2_ASSERT((D2CellFileStrc*)ptr_6FBC277C != nullptr);
		dword_6FBC2F94 = dword_6FBC2F94 + dword_6FBC2780;
		pDVar6 = (D2CellFileStrc*)ptr_6FBC277C;
		for (iVar5 = dword_6FBC2780; iVar5 != 0; iVar5 = iVar5 + (-0x18 - *puVar7))
		{
			(*(uint16_t*)((uint8_t*)&iVar1 + 0)) = pDVar6->dwFlags;
			(*(uint8_t*)((uint8_t*)&iVar1 + 2)) = pDVar6->mylastcol;
			(*(uint8_t*)((uint8_t*)&iVar1 + 3)) = (*((uint8_t*)pDVar6 + 0x7));
			if (iVar1 != 0)
			{
				pDVar6->dwFlags = 0;
				pDVar6->mylastcol = 0;
				(*((uint8_t*)pDVar6 + 0x7)) = 0;
			}
			D2_ASSERT(0x40 >= *(uint8_t*)((int)&pDVar6->pGfxCells + 2));
			uVar4 = 0xffffffff;
			pDVar6->nFrames = (int)&pDVar6->pGfxCells;
			puVar7 = &pDVar6->dwTermination;
			do
			{
				if (uVar4 == 0)
					break;
				uVar4 = uVar4 - 1;
				uVar2 = *puVar7;
				puVar7 = (uint32_t*)((int)puVar7 + 1);
			} while ((char)uVar2 != '\0');
			D2_ASSERT(7 >= ~uVar4 - 1);
			uVar4 = SStrHash((char*)&pDVar6->dwTermination, 1, 0);
			uVar4 = ((uVar4 & 0x1ff0000 ^ uVar4 >> 8) >> 8 ^ uVar4 & 0x1ff00) >> 8 ^ uVar4 & 0x1ff;
			pDVar6->dwVersion = (&dword_6FBC2784)[uVar4];
			(&dword_6FBC2784)[uVar4] = (uint32_t)(pDVar6);
			puVar7 = &pDVar6->eFormat;
			pDVar6 = (D2CellFileStrc*)((int)&pDVar6->pGfxCells + *puVar7);
		}
		dword_6FBC2778 = 1;
	}
}

//D2Client.0x6FB5CB60
void __cdecl sub_6FB5CB60()
{
	uint32_t* pFree;
	int iVar1;
	uint32_t uVar2;
	uint32_t* puVar3;

	uVar2 = 0;
	do
	{
		puVar3 = *(uint32_t**)((int)&dword_6FBC2784 + uVar2);
		while (pFree = puVar3, pFree != nullptr)
		{
			puVar3 = (uint32_t*)*pFree;
			if ((*(uint8_t*)(pFree + 1) & 1) != 0)
			{
				dword_6FBC2F94 = dword_6FBC2F94 + (-0x1c - pFree[2]);
				D2_FREE((void*)pFree[5]);
				D2_FREE(pFree);
			}
		}
		uVar2 = uVar2 + 4;
	} while (uVar2 < 0x800);
	dword_6FBC2F94 = dword_6FBC2F94 - dword_6FBC2780;
	if (ptr_6FBC277C != nullptr)
	{
		D2_FREE(ptr_6FBC277C);
	}
	puVar3 = &dword_6FBC2778;
	for (iVar1 = 0x203; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
}

//D2Client.0x6FB5CC10
int __fastcall sub_6FB5CC10(int a1)
{
	if ((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa98)))
	{
		return *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa90) + a1 * 0x134;
	}
	return 0;
}

//D2Client.0x6FB5CC40
void __fastcall sub_6FB5CC40(int a12, int a22)
{
	int iVar1;
	uint8_t bVar2;
	LPSTR pCVar3;
	Unicode* pUVar4;
	int iVar5;
	uint32_t uVar6;
	uint8_t* pbVar7;
	char* szMsg;
	int iVar8;
	int a1;
	int a2;
	int a2_00;
	short* psVar9;
	uint32_t* puVar10;
	int* piVar11;
	char* szFile;
	uint32_t* local_2f4;
	int local_2e4;
	int local_2e0;
	int local_2dc;
	int local_2d8;
	uint8_t* local_2d4;
	uint8_t* local_2d0;
	short local_2cc;
	uint32_t local_2c9;
	int local_298[18];
	int aiStack_250[18];
	uint8_t local_208[3];
	uint8_t uStack_205;
	int local_204;
	char local_104;
	uint32_t local_103;

	if (((((a12 < 0) || (iVar8 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar8 + 0xa80) <= a12)) || (iVar1 = *(int*)(iVar8 + 0xa78) + a12 * 0x1a8, iVar1 == 0)) ||
	        ((iVar5 = (int)*(short*)(iVar1 + 0x18), iVar5 < 0 || (*(int*)(iVar8 + 0xa98) <= iVar5)))) ||
	    ((local_2d8 = *(int*)(iVar8 + 0xa90) + iVar5 * 0x134, local_2d8 == 0 ||
	                                                              (local_2dc = 0, (int)dword_6FB96E68 < 1))))
	{
		return;
	}
	do
	{
		pCVar3 = (LPSTR)(&dword_6FB96E2C)[local_2dc];
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[((uint32_t)pCVar3 & 7) * 4] &
		        *(uint8_t*)(((int)pCVar3 >> 3) + 0xf0 + local_2d8)) != 0)
		{
			local_104 = '\0';
			psVar9 = &local_2cc;
			for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1)
			{
				psVar9[0] = 0;
				psVar9[1] = 0;
				psVar9 = psVar9 + 2;
			}
			puVar10 = &local_103;
			for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1)
			{
				*puVar10 = 0;
				puVar10 = puVar10 + 1;
			}
			*(uint16_t*)puVar10 = 0;
			*(uint8_t*)((int)puVar10 + 2) = 0;
			local_2cc = (short)a12;
			sub_6FB5D0B0(iVar1, (int)local_2cc, pCVar3, (uint8_t*)(&local_2e0), &local_104);
			(*(uint32_t*)&local_208) = (*(uint32_t*)&local_208) & 0xffffff00;
			puVar10 = (uint32_t*)((int)local_208 + 1);
			for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1)
			{
				*puVar10 = 0;
				puVar10 = puVar10 + 1;
			}
			*(uint16_t*)puVar10 = 0;
			*(uint8_t*)((int)puVar10 + 2) = 0;
			sub_6FB58AC0(&local_104, (char*)(local_208));
			_strlwr((char*)(local_208));
			uVar6 = sub_6FB5D040((char*)(local_208));
			for (local_2f4 = (uint32_t*)(&dword_6FBC2784)[uVar6]; local_2f4 != nullptr;
			     local_2f4 = (uint32_t*)*local_2f4)
			{
				if (((*(uint32_t*)&local_208) == local_2f4[3]) && (local_204 == local_2f4[4]))
					goto LAB_6fb5cdc4;
			}
			local_2f4 = sub_6FB58B10((int)&dword_6FBC2778, &local_104);
			if (local_2f4 == nullptr)
			{
				iVar8 = 0xeb7;
				szFile = __FILE__;
				szMsg = (char*)(FOG_csprintf((char*)(local_208), "Could not add cof file: %s", &local_104));
				FOG_DisplayHalt(szMsg, szFile, iVar8);
				exit(-1);
			}
		LAB_6fb5cdc4:
			pUVar4 = (Unicode*)local_2f4[5];
			D2_ASSERT(pUVar4 != nullptr);
			pbVar7 = (uint8_t*)sub_6FB5EF30(pUVar4);
			local_2d4 = pbVar7;
			D2_ASSERT(pbVar7 != nullptr);
			local_2d0 = sub_6FB5EFC0((uint8_t*)pUVar4, 0, 0);
			D2_ASSERT(local_2d0 != nullptr);
			local_2e4 = 0;
			if (*pbVar7 != 0)
			{
				do
				{
					bVar2 = local_2d0[local_2e4];
					D2_ASSERT(0xf >= bVar2);
					if ((char)local_2c9 == '\0')
					{
						piVar11 = aiStack_250;
						for (iVar8 = 0x12; iVar8 != 0; iVar8 = iVar8 + -1)
						{
							*piVar11 = 0;
							piVar11 = piVar11 + 1;
						}
						iVar8 = sub_6FB5ECC0((int)aiStack_250, 0, nullptr, (uint32_t)bVar2, (int)pCVar3, local_2e0,
						    (int)local_2f4, &local_2cc, iVar1, 0);
						if (iVar8 != 0)
						{
							if (a22 == 0)
							{
								D2CMP_10055((int)aiStack_250, 0, 0);
							}
							else
							{
								iVar8 = D2CMP_10055((int)aiStack_250, 1, 1);
								if (iVar8 == 0)
								{
									aiStack_250[1] = iVar8;
									D2CMP_10056(a1, a2_00, (int)aiStack_250);
								}
							}
						}
					}
					else
					{
						uVar6 = 0;
						if ((char)local_2c9 != '\0')
						{
							do
							{
								piVar11 = local_298;
								for (iVar8 = 0x12; iVar8 != 0; iVar8 = iVar8 + -1)
								{
									*piVar11 = 0;
									piVar11 = piVar11 + 1;
								}
								iVar8 = sub_6FB5ECC0((int)local_298, 0, nullptr, (uint32_t)bVar2, (int)pCVar3, local_2e0,
								    (int)local_2f4, &local_2cc, iVar1, uVar6);
								if (iVar8 != 0)
								{
									if (a22 == 0)
									{
										D2CMP_10055((int)local_298, 0, 0);
									}
									else
									{
										iVar8 = D2CMP_10055((int)local_298, 1, 1);
										if (iVar8 == 0)
										{
											local_298[1] = iVar8;
											D2CMP_10056((int)local_298, a2, (int)local_298);
										}
									}
								}
								uVar6 = uVar6 + 1;
							} while (uVar6 < (local_2c9 & 0xff));
						}
					}
					local_2e4 = local_2e4 + 1;
				} while (local_2e4 < (int)(uint32_t)*local_2d4);
			}
		}
		local_2dc = local_2dc + 1;
		if ((int)dword_6FB96E68 <= local_2dc)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FB5D040
uint32_t __fastcall sub_6FB5D040(char* a1)
{
	char cVar1;
	uint32_t uVar2;
	char* pcVar3;

	uVar2 = 0xffffffff;
	pcVar3 = a1;
	do
	{
		if (uVar2 == 0)
			break;
		uVar2 = uVar2 - 1;
		cVar1 = *pcVar3;
		pcVar3 = pcVar3 + 1;
	} while (cVar1 != '\0');
	D2_ASSERT(7 >= ~uVar2 - 1);
	uVar2 = SStrHash(a1, 1, 0);
	return ((uVar2 & 0x1ff0000 ^ uVar2 >> 8) >> 8 ^ uVar2 & 0x1ff00) >> 8 ^ uVar2 & 0x1ff;
}

//D2Client.0x6FB5D0B0
void __fastcall sub_6FB5D0B0(uint32_t a1, int a2, LPSTR a3, uint8_t* a4, LPSTR a5)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	LPSTR pCVar4;
	uint8_t bVar5;
	uint8_t bVar6;
	int iVar7;
	D2MonModeTxt* pDVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	uint8_t bStack_18;
	uint8_t bStack_17;
	uint8_t bStack_16;
	uint8_t uStack_15;
	uint8_t bStack_14;
	uint8_t bStack_13;
	uint8_t bStack_12;
	uint8_t uStack_11;
	uint8_t uStack_10;
	uint8_t bStack_f;
	uint16_t uStack_e;
	uint8_t local_8;
	uint8_t bStack_7;
	uint16_t uStack_6;

	pCVar4 = a3;
	if (((((-1 < a2) && (iVar2 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar2 + 0xa80))) && (iVar1 = *(int*)(iVar2 + 0xa78) + a2 * 0x1a8, iVar1 != 0)) &&
	        ((iVar7 = (int)*(short*)(iVar1 + 0x18), -1 < iVar7 && (iVar7 < *(int*)(iVar2 + 0xa98))))) &&
	    (iVar2 = *(int*)(iVar2 + 0xa90) + iVar7 * 0x134, iVar2 != 0))
	{
		uVar3 = *(uint32_t*)(iVar1 + 0x10);
		local_8 = (uint8_t)uVar3;
		bVar5 = local_8;
		bStack_7 = (uint8_t)((uint32_t)uVar3 >> 8);
		bVar6 = bStack_7;
		uStack_6 = (uint16_t)((uint32_t)uVar3 >> 0x10);
		pDVar8 = DATATBLS_GetMonModeTxtRecord((int)a3, 1);
		D2_ASSERT(pDVar8 != nullptr);
		uVar10 = pDVar8->dwToken;
		uStack_10 = (uint8_t)uVar10;
		bStack_f = (uint8_t)(uVar10 >> 8);
		uStack_e = (uint16_t)(uVar10 >> 0x10);
		if ((pCVar4 == (LPSTR)0x0) || (pCVar4 == (LPSTR)(((uint8_t*)0x0c))))
		{
			if (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar2 + 6)) == 0)
			{
				a4[0] = 0x68;
				a4[1] = 0x74;
				a4[2] = 0x68;
				a4[3] = 0x20;
			}
			else
			{
				*(uint32_t*)a4 = *(uint32_t*)(iVar2 + 0x10);
			}
		}
		else
		{
			*(uint32_t*)a4 = *(uint32_t*)(iVar2 + 0x10);
		}
		uVar9 = 0;
		if (dword_6FB96E88 != 0)
		{
			do
			{
				if (pCVar4 == (LPSTR)(&dword_6FB96E84)[uVar9 * 2])
				{
					uVar10 = (&dword_6FB96E80)[uVar9 * 2];
				}
				uVar9 = uVar9 + 1;
			} while (uVar9 < dword_6FB96E88);
			uStack_10 = (uint8_t)uVar10;
			bStack_f = (uint8_t)(uVar10 >> 8);
			uStack_e = (uint16_t)(uVar10 >> 0x10);
		}
		uStack_15 = 0;
		bStack_18 = (*a4 == 0x20) - 1U & *a4;
		uStack_11 = 0;
		bStack_17 = (a4[1] == 0x20) - 1U & a4[1];
		bStack_16 = (a4[2] == 0x20) - 1U & a4[2];
		a3 = (LPSTR)(uint32_t)CONCAT12(((uint8_t)uStack_6 == 0x20) - 1U & (uint8_t)uStack_6,
		    CONCAT11((bVar6 == 0x20) - 1U & bStack_7,
		        (bVar5 == 0x20) - 1U & bVar5));
		bStack_14 = ((uint8_t)uVar10 == 0x20) - 1U & (uint8_t)uVar10;
		bStack_13 = ((char)(uVar10 >> 8) == ' ') - 1U & bStack_f;
		bStack_12 = ((uint8_t)uStack_e == 0x20) - 1U & (uint8_t)uStack_e;
		wsprintfA(a5, "%s\\%s\\COF\\%s%s%s.COF", "DATA\\GLOBAL\\MONSTERS", &a3,
		    &a3, &bStack_14, &bStack_18);
	}
}

//D2Client.0x6FB5D290
void __cdecl sub_6FB5D290()
{
	D2InventoryStrc* pDVar1;
	D2ActiveRoomStrc** ppDVar2;
	uint8_t bVar3;
	D2UnitStrc* pDVar4;
	D2ActiveRoomStrc* pDVar5;
	uint32_t uVar6;
	DWORD DVar7;
	uint8_t* puVar8;
	int iVar9;
	uint32_t uVar10;
	uint8_t bVar11;
	uint32_t uStack_20;
	int iStack_1c;
	uint32_t uStack_18;
	uint32_t uStack_14;
	int iStack_10;
	D2ActiveRoomStrc** ppDStack_c;
	D2ActiveRoomStrc** ppDStack_8;
	D2ActiveRoomStrc** ppDStack_4;

	dword_6FBC2F9C = 1;
	pDVar4 = CUNIT_GetPlayer();
	pDVar5 = UNITS_GetRoom(pDVar4);
	if (pDVar5 != nullptr)
	{
		DUNGEON_GetAdjacentRoomsListFromRoom(pDVar5, &ppDStack_8, (int*)&uStack_14);
		bVar11 = 0;
		uVar10 = 0;
		if (uStack_14 != 0)
		{
			do
			{
				if (dword_6FBC2F9C == 0)
				{
				LAB_6fb5d2f9:
					uVar6 = D2CMP_10057();
					if (0x1d < uVar6)
						break;
				}
				else
				{
					bVar3 = bVar11 & 0x1f;
					bVar11 = bVar11 + 1;
					if (bVar3 != 0)
					{
						sub_6FB242E0(1);
					}
					if (dword_6FBC2F9C == 0)
						goto LAB_6fb5d2f9;
				}
				for (pDVar4 = ppDStack_8[uVar10]->pUnitFirst; pDVar4 != nullptr;
				     pDVar4 = pDVar4->pRoomNext)
				{
					uStack_20 = 6;
					if (pDVar4 != nullptr)
					{
						uStack_20 = pDVar4->dwUnitType;
						iStack_1c = pDVar4->dwClassId;
					}
					else
					{
						iStack_1c = -1;
					}
					uStack_18 = UNITS_GetAnimOrSeqMode(pDVar4);
					D2COMMON_11013_ConvertMode(pDVar4, (int*)&uStack_20, &iStack_1c, (int*)&uStack_18,
					    __FILE__, __LINE__);
					if (uStack_20 == 1)
					{
						if ((iStack_1c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
						    ((uStack_18 != 0xc || (*(int*)(iStack_1c * 0xa0 + 0x30 + dword_6FBC2F84) == 0))))
						{
							sub_6FB5D630(pDVar4, 0);
						}
					}
					else if ((uStack_20 == 0) && (uVar6 = 0, dword_6FB96E28 != 0))
					{
						do
						{
							sub_6FB5D830(pDVar4, (D2InventoryStrc*)(&dword_6FB96E08)[uVar6], 0);
							uVar6 = uVar6 + 1;
						} while (uVar6 < dword_6FB96E28);
					}
					if ((dword_6FBC2F9C == 0) && (uVar6 = D2CMP_10057(), 0x1d < uVar6))
						goto LAB_6fb5d3f7;
				}
				uVar10 = uVar10 + 1;
			} while (uVar10 < uStack_14);
		}
	}
LAB_6fb5d3f7:
	dword_6FBC2F8C = GetTickCount();
	if ((dword_6FBC2F9C == 0) && (DVar7 = GetTickCount(), DVar7 < dword_6FBC2F8C + 600))
	{
		dword_6FBC2F9C = 0;
		return;
	}
	uVar10 = 1;
	uStack_20 = 1;
	pDVar4 = CUNIT_GetPlayer();
	pDVar5 = UNITS_GetRoom(pDVar4);
	if (pDVar5 != nullptr)
	{
		DUNGEON_GetAdjacentRoomsListFromRoom(pDVar5, &ppDStack_4, (int*)&ppDStack_8);
		uStack_14 = 0;
		ppDStack_c = nullptr;
		if (ppDStack_8 != nullptr)
		{
			do
			{
				ppDVar2 = ppDStack_c;
				if (dword_6FBC2F9C == 0)
				{
				LAB_6fb5d4a0:
					uVar6 = D2CMP_10057();
					if (0x1d < uVar6)
						break;
				}
				else
				{
					if (((uVar10 == 0) || (dword_6FBC2FA4 != 0)) &&
					    (uVar6 = uStack_14 & 0x1f, uStack_14 = uStack_14 + 1, uVar6 != 0))
					{
						sub_6FB242E0(1);
					}
					if (dword_6FBC2F9C == 0)
						goto LAB_6fb5d4a0;
				}
				pDVar4 = ppDStack_4[(int)ppDVar2]->pUnitFirst;
				for (; pDVar4 != nullptr; pDVar4 = pDVar4->pRoomNext)
				{
					uStack_18 = 6;
					if (pDVar4 != nullptr)
					{
						uStack_18 = pDVar4->dwUnitType;
						iStack_1c = pDVar4->dwClassId;
					}
					else
					{
						iStack_1c = -1;
					}
					iStack_10 = UNITS_GetAnimOrSeqMode(pDVar4);
					D2COMMON_11013_ConvertMode(pDVar4, (int*)&uStack_18, &iStack_1c, &iStack_10,
					    __FILE__, __LINE__);
					if (uStack_18 == 1)
					{
						if ((iStack_1c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
						    ((iStack_10 != 0xc || (*(int*)(iStack_1c * 0xa0 + 0x30 + dword_6FBC2F84) == 0))))
						{
							puVar8 = sub_6FB5DD70(pDVar4);
							iVar9 = sub_6FB247F0((int)puVar8);
							if ((iVar9 != 0) && (uVar6 = 0, dword_6FB96E68 != 0))
							{
								do
								{
									pDVar1 = (D2InventoryStrc*)(&dword_6FB96E2C)[uVar6];
									if (((uint8_t)((uint8_t*)&gdwBitMasks)[((uint32_t)pDVar1 & 7) * 4] &
									        *(uint8_t*)(((uint32_t)pDVar1 >> 3) + 0xf0 + iVar9)) != 0)
									{
										sub_6FB5B920(pDVar4, pDVar1, uStack_20);
									}
									uVar6 = uVar6 + 1;
									uVar10 = uStack_20;
								} while (uVar6 < dword_6FB96E68);
							}
						}
					}
					else if (uStack_18 == 0)
					{
						if (dword_6FBC2FA4 != 0)
						{
							uVar10 = 0;
							uStack_20 = 0;
						}
						sub_6FB5D930(pDVar4, uVar10);
					}
					if ((dword_6FBC2F9C == 0) && (uVar6 = D2CMP_10057(), 0x1d < uVar6))
						goto LAB_6fb5d5f6;
					ppDVar2 = ppDStack_c;
				}
				ppDStack_c = (D2ActiveRoomStrc**)((int)ppDVar2 + 1);
			} while (ppDStack_c < ppDStack_8);
		}
	}
LAB_6fb5d5f6:
	dword_6FBC2F8C = GetTickCount();
	dword_6FBC2F9C = 0;
}

//D2Client.0x6FB5D630
void __fastcall sub_6FB5D630(D2UnitStrc* pUnit, uint32_t a2)
{
	int iVar1;
	D2InventoryStrc* a4;
	int iVar2;
	uint32_t* puVar3;
	uint32_t uVar4;
	int local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint32_t local_4;

	local_4 = a2;
	if (pUnit == nullptr)
	{
		local_10 = -1;
	}
	else if ((pUnit->dwFlagEx >> 3 & 1) == 0)
	{
		local_10 = pUnit->dwClassId;
		local_8 = 0;
	}
	else
	{
		local_8 = pUnit->dwUnitType;
		local_10 = pUnit->dwClassId;
		local_c = UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_8, &local_10, (int*)&local_c, __FILE__, __LINE__);
	}
	if (((((-1 < local_10) &&
	          (iVar1 = *(int*)((uint8_t*)&sgptDataTables), local_10 < *(int*)(iVar1 + 0xa80))) &&
	         (iVar2 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + local_10 * 0x1a8), -1 < iVar2)) &&
	        ((iVar2 < *(int*)(iVar1 + 0xa98) &&
	            (iVar1 = *(int*)(iVar1 + 0xa90) + iVar2 * 0x134, iVar1 != 0)))) &&
	    (uVar4 = 0, dword_6FB96E68 != 0))
	{
		do
		{
			a4 = (D2InventoryStrc*)(&dword_6FB96E2C)[uVar4];
			if (((uint8_t)((uint8_t*)&gdwBitMasks)[((uint32_t)a4 & 7) * 4] & *(uint8_t*)(((uint32_t)a4 >> 3) + 0xf0 + iVar1)) != 0)
			{
				local_c = 6;
				if (pUnit == nullptr)
				{
					local_10 = -1;
				}
				else
				{
					local_c = pUnit->dwUnitType;
					local_10 = pUnit->dwClassId;
				}
				local_8 = UNITS_GetAnimOrSeqMode(pUnit);
				D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_10, (int*)&local_8,
				    __FILE__, __LINE__);
				if ((local_10 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
				    (*(int*)(dword_6FBC2F84 + (int)(&a4->dwSignature + local_10 * 10) * 4) == 0))
				{
					if (*(int*)(dword_6FBC2F84 + 0x50 + (int)(&a4->dwSignature + local_10 * 10) * 4) == 0)
					{
						puVar3 = sub_6FB5B5A0(pUnit, a4, local_4);
						if (puVar3 == (uint32_t*)0x1)
						{
							*(uint32_t*)(dword_6FBC2F84 + 0x50 + (int)(&a4->dwSignature + local_10 * 10) * 4) = 1;
						}
						else
						{
							*(uint32_t*)(dword_6FBC2F84 + 0x50 + (int)(&a4->dwSignature + local_10 * 10) * 4) = 0;
							*(uint32_t*)(dword_6FBC2F84 + (int)(&a4->dwSignature + local_10 * 10) * 4) = 0;
						}
					}
					else
					{
						iVar2 = D2CMP_10058(local_c, dword_6FBC2F84, local_c, (int)a4, local_10);
						if (iVar2 == 0)
						{
							*(uint32_t*)(dword_6FBC2F84 + (int)(&a4->dwSignature + local_10 * 10) * 4) = 1;
						}
					}
				}
			}
			uVar4 = uVar4 + 1;
		} while (uVar4 < dword_6FB96E68);
	}
}

//D2Client.0x6FB5D830
void __fastcall sub_6FB5D830(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, uint32_t a3)
{
	uint32_t* puVar1;
	int iVar2;
	int local_c;
	uint32_t local_8;
	int iStack_4;

	local_8 = 6;
	if (pUnit == nullptr)
	{
		local_c = -1;
	}
	else
	{
		local_8 = pUnit->dwUnitType;
		local_c = pUnit->dwClassId;
	}
	iStack_4 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_8, &local_c, &iStack_4, __FILE__, __LINE__);
	if ((&dword_6FBC2318)[(int)(&pInventory->dwSignature + local_c * 10)] == 0)
	{
		if (*(int*)(byte_6FBC2368 + (int)(&pInventory->dwSignature + local_c * 10) * 4) == 0)
		{
			puVar1 = sub_6FB5B5A0(pUnit, pInventory, a3);
			if (puVar1 == (uint32_t*)0x1)
			{
				*(uint32_t*)(byte_6FBC2368 + (int)(&pInventory->dwSignature + local_c * 10) * 4) = 1;
				return;
			}
			*(uint32_t*)(byte_6FBC2368 + (int)(&pInventory->dwSignature + local_c * 10) * 4) = 0;
			(&dword_6FBC2318)[(int)(&pInventory->dwSignature + local_c * 10)] = 0;
			return;
		}
		iVar2 = D2CMP_10058(local_c, local_8, local_8, (int)pInventory, local_c);
		if (iVar2 == 0)
		{
			(&dword_6FBC2318)[(int)(&pInventory->dwSignature + local_c * 10)] = 1;
		}
	}
}

//D2Client.0x6FB5D930
void __fastcall sub_6FB5D930(D2UnitStrc* pUnit, uint32_t a2)
{
	D2InventoryStrc* a4;
	uint32_t* puVar1;
	int iVar2;
	uint32_t uVar3;
	int local_10;
	uint32_t local_c;
	int iStack_8;
	uint32_t local_4;

	uVar3 = 0;
	local_4 = a2;
	if (dword_6FB96E28 != 0)
	{
		do
		{
			a4 = (D2InventoryStrc*)(&dword_6FB96E08)[uVar3];
			local_c = 6;
			if (pUnit == nullptr)
			{
				local_10 = -1;
			}
			else
			{
				local_c = pUnit->dwUnitType;
				local_10 = pUnit->dwClassId;
			}
			iStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_10, &iStack_8,
			    __FILE__, __LINE__);
			if ((&dword_6FBC2318)[(int)(&a4->dwSignature + local_10 * 10)] == 0)
			{
				if (*(int*)(byte_6FBC2368 + (int)(&a4->dwSignature + local_10 * 10) * 4) == 0)
				{
					puVar1 = sub_6FB5B5A0(pUnit, a4, local_4);
					if (puVar1 == (uint32_t*)0x1)
					{
						*(uint32_t*)(byte_6FBC2368 + (int)(&a4->dwSignature + local_10 * 10) * 4) = 1;
					}
					else
					{
						*(uint32_t*)(byte_6FBC2368 + (int)(&a4->dwSignature + local_10 * 10) * 4) = 0;
						(&dword_6FBC2318)[(int)(&a4->dwSignature + local_10 * 10)] = 0;
					}
				}
				else
				{
					iVar2 = D2CMP_10058(local_10, local_c, local_c, (int)a4, local_10);
					if (iVar2 == 0)
					{
						(&dword_6FBC2318)[(int)(&a4->dwSignature + local_10 * 10)] = 1;
					}
				}
			}
			uVar3 = uVar3 + 1;
		} while (uVar3 < dword_6FB96E28);
	}
}

//D2Client.0x6FB5DA40
void __fastcall sub_6FB5DA40(D2UnitStrc* pUnit)
{
	int iVar1;

	iVar1 = sub_6FB29550((int*)pUnit);
	if (((iVar1 == 0) && (pUnit != nullptr)) && (pUnit->dwUnitType == 0))
	{
		sub_6FB49090(7, pUnit, 0, 1);
	}
}

//D2Client.0x6FB5DA70
int32_t __fastcall sub_6FB5DA70()
{
	return dword_6FBC2F90;
}

//D2Client.0x6FB5DA80
int32_t __fastcall sub_6FB5DA80()
{
	return dword_6FBC2F94;
}

//D2Client.0x6FB5DA90
int32_t __fastcall sub_6FB5DA90()
{
	return dword_6FBC2F98;
}

//D2Client.0x6FB5DAA0
int __fastcall sub_6FB5DAA0(int a1)
{
	return a1 * 0xa0 + dword_6FBC2F84;
}

//D2Client.0x6FB5DAB0
void __fastcall sub_6FB5DAB0(D2UnitStrc* pUnit)
{
	D2InventoryStrc* a4;
	D2ActiveRoomStrc* pDVar1;
	int iVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t uVar5;
	int iStack_1c;
	int local_18;
	int iStack_14;
	uint32_t local_10;
	uint32_t uStack_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	local_10 = 6;
	uVar5 = 0;
	if (pUnit == nullptr)
	{
		local_18 = -1;
	}
	else
	{
		local_10 = pUnit->dwUnitType;
		local_18 = pUnit->dwClassId;
	}
	iStack_14 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_10, &local_18, &iStack_14,
	    __FILE__, __LINE__);
	if ((local_10 == 1) && (local_18 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)))
	{
		uStack_c = 1;
		*(uint32_t*)(dword_6FBC2F84 + (iStack_14 + local_18 * 0x28) * 4) = 0;
		*(uint32_t*)(dword_6FBC2F84 + 0x50 + (iStack_14 + local_18 * 0x28) * 4) = 0;
		pDVar1 = UNITS_GetRoom(pUnit);
		if ((pDVar1 == nullptr) ||
		    ((iVar2 = WINDOW_GetState(), iVar2 != 0 || (iVar2 = sub_6FB24650(), iVar2 != 0))))
		{
			uStack_c = 0;
		}
		if (pUnit == nullptr)
		{
			iStack_1c = -1;
		}
		else if ((pUnit->dwFlagEx >> 3 & 1) == 0)
		{
			iStack_1c = pUnit->dwClassId;
			uStack_4 = 0;
		}
		else
		{
			uStack_4 = pUnit->dwUnitType;
			iStack_1c = pUnit->dwClassId;
			uStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_4, &iStack_1c, (int*)&uStack_8,
			    __FILE__, __LINE__);
		}
		if (((((-1 < iStack_1c) &&
		          (iVar2 = *(int*)((uint8_t*)&sgptDataTables), iStack_1c < *(int*)(iVar2 + 0xa80))) &&
		         (iVar3 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iStack_1c * 0x1a8), -1 < iVar3)) &&
		        ((iVar3 < *(int*)(iVar2 + 0xa98) &&
		            (iVar2 = *(int*)(iVar2 + 0xa90) + iVar3 * 0x134, iVar2 != 0)))) &&
		    (dword_6FB96E68 != 0))
		{
			do
			{
				a4 = (D2InventoryStrc*)(&dword_6FB96E2C)[uVar5];
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[((uint32_t)a4 & 7) * 4] & *(uint8_t*)(((uint32_t)a4 >> 3) + 0xf0 + iVar2)) != 0)
				{
					uStack_8 = 6;
					if (pUnit == nullptr)
					{
						iStack_1c = -1;
					}
					else
					{
						uStack_8 = pUnit->dwUnitType;
						iStack_1c = pUnit->dwClassId;
					}
					uStack_4 = UNITS_GetAnimOrSeqMode(pUnit);
					D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_8, &iStack_1c, (int*)&uStack_4,
					    __FILE__, __LINE__);
					if ((iStack_1c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
					    (*(int*)(dword_6FBC2F84 + (int)(&a4->dwSignature + iStack_1c * 10) * 4) == 0))
					{
						if (*(int*)(dword_6FBC2F84 + 0x50 + (int)(&a4->dwSignature + iStack_1c * 10) * 4) == 0)
						{
							puVar4 = sub_6FB5B5A0(pUnit, a4, uStack_c);
							if (puVar4 == (uint32_t*)0x1)
							{
								*(uint32_t*)(dword_6FBC2F84 + 0x50 + (int)(&a4->dwSignature + iStack_1c * 10) * 4) = 1;
							}
							else
							{
								*(uint32_t*)(dword_6FBC2F84 + 0x50 + (int)(&a4->dwSignature + iStack_1c * 10) * 4) = 0;
								*(uint32_t*)(dword_6FBC2F84 + (int)(&a4->dwSignature + iStack_1c * 10) * 4) = 0;
							}
						}
						else
						{
							iVar3 = D2CMP_10058(uStack_8, dword_6FBC2F84, uStack_8, (int)a4, iStack_1c);
							if (iVar3 == 0)
							{
								*(uint32_t*)(dword_6FBC2F84 + (int)(&a4->dwSignature + iStack_1c * 10) * 4) = 1;
							}
						}
					}
				}
				uVar5 = uVar5 + 1;
			} while (uVar5 < dword_6FB96E68);
		}
	}
}

//D2Client.0x6FB5DD70
uint8_t* __fastcall sub_6FB5DD70(D2UnitStrc* pUnit)
{
	uint8_t* local_c;
	int iStack_8;
	uint32_t local_4;

	if (pUnit == nullptr)
	{
		return (uint8_t*)0xffffffff;
	}
	if ((pUnit->dwFlagEx >> 3 & 1) == 0)
	{
		return (uint8_t*)pUnit->dwClassId;
	}
	local_4 = pUnit->dwUnitType;
	local_c = (uint8_t*)pUnit->dwClassId;
	iStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&local_4, (int*)&local_c, &iStack_8, __FILE__, __LINE__);
	return local_c;
}

//D2Client.0x6FB5DDE0
D2InventoryStrc* __fastcall sub_6FB5DDE0(D2UnitStrc* pUnit, uint32_t* a2)
{
	int iVar1;
	D2UnitStrc* pDVar2;

	if ((pUnit != nullptr) && ((pUnit->dwFlagEx >> 3 & 1) != 0))
	{
		iVar1 = STATES_CheckStateMaskOnUnit(pUnit, 0x25);
		if (iVar1 != 0)
		{
			pDVar2 = sub_6FB26AD0((int)pUnit);
			if (pDVar2 != nullptr)
			{
				if (a2 != nullptr)
				{
					*a2 = 1;
				}
				return pDVar2->pInventory;
			}
		}
	}
	if (a2 != nullptr)
	{
		*a2 = 0;
	}
	return pUnit->pInventory;
}
