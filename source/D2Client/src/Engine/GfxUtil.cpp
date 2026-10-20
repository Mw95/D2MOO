#include "Engine/GfxUtil.h"

#include "Core/WinMain.h"
#include "Engine/Gfx.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "UI/Inv.h"
#include "Unit/CUnit.h"

//D2Client.0x6FBC2FB0
uint32_t dword_6FBC2FB0;
//D2Client.0x6FBC2FF0
uint32_t dword_6FBC2FF0;
//D2Client.0x6FBC3030
uint32_t dword_6FBC3030;
//D2Client.0x6FBC3050
uint32_t dword_6FBC3050;
//D2Client.0x6FBC3054
uint8_t byte_6FBC3054;
//D2Client.0x6FBC3058
uint8_t byte_6FBC3058;
//D2Client.0x6FBC3060
uint32_t dword_6FBC3060;

//D2Client.0x6FB5DE40
void __cdecl sub_6FB5DE40()
{
	D2CompositTxt* pDVar1;
	D2PlrModeTypeTxt* pDVar2;
	D2MonModeTxt* pDVar3;
	D2ObjModeTypeTxt* pDVar4;
	D2ArmTypeTxt* pDVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t* puVar8;

	uVar7 = 0;
	puVar8 = &dword_6FBC2FF0;
	for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	do
	{
		pDVar1 = DATATBLS_GetCompositTxtRecord(uVar7);
		D2_ASSERT(pDVar1 != nullptr);
		(&dword_6FBC2FF0)[uVar7] = *(uint32_t*)pDVar1->szToken;
		uVar7 = uVar7 + 1;
	} while (uVar7 < 0x10);
	uVar7 = 0;
	puVar8 = &dword_6FBC3060;
	for (iVar6 = 0x14; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	do
	{
		pDVar2 = DATATBLS_GetPlrModeTypeTxtRecord(uVar7, 1);
		D2_ASSERT(pDVar2 != nullptr);
		(&dword_6FBC3060)[uVar7] = *(uint32_t*)pDVar2->szToken;
		uVar7 = uVar7 + 1;
	} while (uVar7 < 0x14);
	uVar7 = 0;
	puVar8 = &dword_6FBC2FB0;
	for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	do
	{
		pDVar3 = DATATBLS_GetMonModeTxtRecord(uVar7, 1);
		D2_ASSERT(pDVar3 != nullptr);
		(&dword_6FBC2FB0)[uVar7] = pDVar3->dwToken;
		uVar7 = uVar7 + 1;
	} while (uVar7 < 0x10);
	uVar7 = 0;
	puVar8 = &dword_6FBC3030;
	for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	do
	{
		pDVar4 = DATATBLS_GetObjModeTypeTxtRecord(uVar7, 1);
		D2_ASSERT(pDVar4 != nullptr);
		(&dword_6FBC3030)[uVar7] = *(uint32_t*)pDVar4->szToken;
		uVar7 = uVar7 + 1;
	} while (uVar7 < 8);
	uVar7 = 0;
	dword_6FBC3050 = 0;
	byte_6FBC3054 = 0;
	byte_6FBC3058 = 0;
	do
	{
		pDVar5 = DATATBLS_GetArmTypeTxtRecord(uVar7);
		D2_ASSERT(pDVar5 != nullptr);
		(&dword_6FBC3050)[uVar7] = *(uint32_t*)pDVar5->szToken;
		uVar7 = uVar7 + 1;
	} while (uVar7 < 3);
}

//D2Client.0x6FB5DFB0
void __fastcall sub_6FB5DFB0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, int* a4, int* a5)
{
	int iVar1;
	D2CellFileStrc** ppDVar2;
	D2CellFileStrc* local_48[7];
	uint8_t local_2b;

	ppDVar2 = local_48;
	for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*ppDVar2 = nullptr;
		ppDVar2 = ppDVar2 + 1;
	}
	local_48[1] = nullptr;
	local_48[2] = (D2CellFileStrc*)a3;
	local_2b = 1;
	local_48[3] = (D2CellFileStrc*)a2;
	iVar1 = sub_6FB5E370(pUnit, (int)local_48, (D2InventoryStrc**)&a3,
	    (D2InventoryStrc*)0xffffffff);
	if (iVar1 != 0)
	{
		iVar1 = D2CMP_10055((int)local_48, 0, 1);
		if ((iVar1 != 0) && (local_48[0] != nullptr))
		{
			iVar1 = D2CMP_CelGetWidth(local_48[0]);
			*a4 = iVar1;
			iVar1 = D2CMP_CelGetHeight(local_48[0]);
			*a5 = iVar1;
		}
	}
}

//D2Client.0x6FB5E030
bool __fastcall sub_6FB5E030(D2UnitStrc* pUnit, int a2, int a3)
{
	uint8_t bVar1;
	int iVar2;
	int iVar3;
	int* piVar4;
	int iVar5;
	int iVar6;
	D2CellFileStrc** ppDVar7;
	int local_58;
	int local_54;
	int local_50;
	D2InventoryStrc* pDStack_4c;
	D2CellFileStrc* apDStack_48[2];
	int iStack_40;
	uint32_t uStack_3c;
	uint8_t uStack_2b;

	iVar2 = sub_6FAB5890();
	local_54 = a2 - iVar2;
	iVar3 = sub_6FAB58A0();
	piVar4 = sub_6FB5C7D0(pUnit, a2 - iVar2, a3 - iVar3, 0, 0);
	if (piVar4 != nullptr)
	{
		UNITS_GetShiftedFrameMetrics(pUnit, &local_58, &local_50);
		ppDVar7 = apDStack_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*ppDVar7 = nullptr;
			ppDVar7 = ppDVar7 + 1;
		}
		bVar1 = UNITS_GetDirection(pUnit);
		uStack_3c = (uint32_t)bVar1;
		apDStack_48[1] = nullptr;
		iStack_40 = local_58;
		uStack_2b = 1;
		iVar2 = sub_6FB5E370(pUnit, (int)apDStack_48, &pDStack_4c, (D2InventoryStrc*)0xffffffff);
		if (iVar2 != 0)
		{
			iVar2 = D2CMP_10055((int)apDStack_48, 0, 1);
			if ((iVar2 != 0) && (apDStack_48[0] != nullptr))
			{
				iVar2 = D2CMP_CelGetHeight(apDStack_48[0]);
				iVar5 = D2CMP_CelGetOffsetY(apDStack_48[0]);
				iVar5 = iVar5 + (a3 - iVar3);
				iVar3 = D2CMP_CelGetOffsetX(apDStack_48[0]);
				iVar3 = iVar3 + local_54;
				iVar6 = D2CMP_CelGetWidth(apDStack_48[0]);
				if (gnScreenWidth < iVar3)
				{
					return false;
				}
				if (iVar6 + iVar3 < 0)
				{
					return false;
				}
				if (gnScreenHeight < iVar5 - iVar2)
				{
					return false;
				}
				return -1 < iVar5 + iVar2;
			}
		}
	}
	return false;
}

//D2Client.0x6FB5E170
bool __fastcall sub_6FB5E170(D2CellFileStrc* pCellFile, int a2, int a3, int a4)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar1 = D2CMP_CelGetHeight(pCellFile);
	iVar2 = D2CMP_CelGetOffsetY(pCellFile);
	iVar3 = D2CMP_CelGetOffsetX(pCellFile);
	iVar3 = iVar3 + a2;
	iVar4 = D2CMP_CelGetWidth(pCellFile);
	if (a4 != 0)
	{
		iVar3 = iVar3 - iVar1;
		iVar4 = iVar4 + iVar1;
	}
	if (gnScreenWidth < iVar3)
	{
		return false;
	}
	if (iVar4 + iVar3 < 0)
	{
		return false;
	}
	if (gnScreenHeight < (iVar2 + a3) - iVar1)
	{
		return false;
	}
	return -1 < iVar2 + a3 + iVar1;
}

//D2Client.0x6FB5E200
uint32_t __fastcall sub_6FB5E200(D2UnitStrc* pUnit, uint32_t a2)
{
	int iVar1;
	int iVar2;
	D2ObjectsTxt* pDVar3;
	int local_c;
	uint32_t local_8;
	int iStack_4;

	if ((int)a2 < 0x10)
	{
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
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_8, &local_c, &iStack_4,
		    __FILE__, __LINE__);
		switch (local_8)
		{
		case 0:
			switch (a2)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 8:
			case 9:
				return 1;
			}
			break;
		case 1:
			if ((((-1 < local_c) &&
			         (iVar1 = *(int*)((uint8_t*)&sgptDataTables), local_c < *(int*)(iVar1 + 0xa80))) &&
			        (iVar2 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + local_c * 0x1a8), -1 < iVar2)) &&
			    (((iVar2 < *(int*)(iVar1 + 0xa98) &&
			          (iVar1 = *(int*)(iVar1 + 0xa90) + iVar2 * 0x134, iVar1 != 0)) &&
			        ((*(uint8_t*)(((int)a2 >> 3) + 0xe8 + iVar1) &
			             (uint8_t)((uint8_t*)&gdwBitMasks)[(a2 & 7) * 4]) != 0))))
			{
				return 1;
			}
			break;
		case 2:
			pDVar3 = DATATBLS_GetObjectsTxtRecord(local_c);
			if ((pDVar3 != nullptr) && (pDVar3->nMode[a2 + 0x12] == 1))
			{
				return 1;
			}
			break;
		case 4:
			if (a2 == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB5E370
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB5E370(D2UnitStrc* pUnit, int a2, D2InventoryStrc** pInventory2, D2InventoryStrc* pInventory3)
{
	int iVar1;
	bool bVar2;
	uint8_t bVar3;
	D2UnitStrc* pDVar4;
	uint32_t* puVar5;
	uint32_t* puVar6;
	uint8_t* pbVar7;
	D2ObjModeTypeTxt* pDVar8;
	uint32_t uVar9;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	D2InventoryStrc** nItemId;
	D2ItemsTxt* pDVar10;
	int iVar11;
	char* pcVar12;
	D2InventoryStrc* pDVar13;
	uint8_t* pbVar14;
	uint32_t local_1c;
	uint8_t* local_18;
	D2InventoryStrc* pDStack_14;
	D2InventoryStrc* pDStack_10;
	int iStack_c;
	uint8_t abStack_8[8];

	local_1c = 6;
	if (pUnit == nullptr)
	{
		*(uint32_t*)(a2 + 0x20) = 6;
	}
	else
	{
		local_1c = pUnit->dwUnitType;
		local_18 = (uint8_t*)pUnit->dwClassId;
		pDStack_14 = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_1c, (int*)&local_18, (int*)&pDStack_14,
		    __FILE__, __LINE__);
		*(uint8_t**)(a2 + 0x24) = local_18;
		*(uint32_t*)(a2 + 0x20) = local_1c;
		pDVar13 = pInventory3;
		if (pInventory3 == (D2InventoryStrc*)0xffffffff)
		{
			pDVar13 = pDStack_14;
		}
		*(D2InventoryStrc**)(a2 + 0x28) = pDVar13;
		if (6 < local_1c)
		{
			return 0;
		}
	}
	switch (local_1c)
	{
	case 0:
	case 1:
	case 2:
		break;
	case 3:
		if ((((pUnit != nullptr) && (iVar11 = pUnit->dwClassId, -1 < iVar11)) &&
		        (iVar11 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
		    (iVar11 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar11 * 0x1a4, iVar11 != 0))
		{
			*(int*)(a2 + 0x44) = iVar11 + 0x138;
		}
		return 1;
	case 4:
		switch (*(uint32_t*)(a2 + 0x28))
		{
		case 0:
		case 1:
		case 2:
		case 4:
		case 6:
			*(uint32_t*)(a2 + 0x28) = 4;
			break;
		case 3:
		case 5:
			*(uint32_t*)(a2 + 0x28) = 3;
		}
		bVar2 = sub_6FB5BEA0((int)pUnit, 8);
		if (D2C_ZEXT(bVar2) == 0)
		{
			if (pUnit == nullptr)
			{
				nItemId = (D2InventoryStrc**)0xffffffff;
			}
			else
			{
				nItemId = (D2InventoryStrc**)pUnit->dwClassId;
			}
		}
		else
		{
			pDStack_14 = (D2InventoryStrc*)0x6;
			if (pUnit == nullptr)
			{
				pInventory2 = (D2InventoryStrc**)0xffffffff;
			}
			else
			{
				pDStack_14 = (D2InventoryStrc*)pUnit->dwUnitType;
				pInventory2 = (D2InventoryStrc**)pUnit->dwClassId;
			}
			pInventory3 = (D2InventoryStrc*)UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&pDStack_14, (int*)&pInventory2, (int*)&pInventory3,
			    __FILE__, __LINE__);
			nItemId = pInventory2;
		}
		pDVar10 = DATATBLS_GetItemsTxtRecord((int)nItemId);
		if (pDVar10 != nullptr)
		{
			if (*(int*)(a2 + 0x28) == 4)
			{
				bVar3 = ITEMS_GetVarGfxIndex(pUnit);
				local_18 = (uint8_t*)CONCAT31((*(uint8_t*)((uint8_t*)&local_18 + 1)), bVar3);
				iVar11 = ITEMS_CheckItemFlag(pUnit, 0x10, __LINE__, __FILE__);
				if ((iVar11 != 0) && (iVar11 = ITEMS_GetItemQuality(pUnit), iVar11 == 5))
				{
					iVar11 = ITEMS_GetFileIndex(pUnit);
					if (((-1 < iVar11) &&
					        ((iVar11 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc1c) &&
					            (iVar11 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc18) + iVar11 * 0x1b8,
					                iVar11 != 0)))) &&
					    (*(char*)(iVar11 + 0x62) != '\0'))
					{
						*(int*)(a2 + 0x44) = iVar11 + 0x62;
						*(uint8_t*)(a2 + 0x1c) = *(uint8_t*)(a2 + 0x1c) | 0x10;
						return 1;
					}
					if (pDVar10->szSetInvFile[0] != '\0')
					{
						*(char**)(a2 + 0x44) = pDVar10->szSetInvFile;
						*(uint8_t*)(a2 + 0x1c) = *(uint8_t*)(a2 + 0x1c) | 0x10;
						return 1;
					}
				}
				iVar11 = ITEMS_CheckItemFlag(pUnit, 0x10, __LINE__, __FILE__);
				if ((iVar11 != 0) && (iVar11 = ITEMS_GetItemQuality(pUnit), iVar11 == 7))
				{
					iVar11 = ITEMS_GetFileIndex(pUnit);
					if ((0 < iVar11) &&
					    ((iVar11 = sub_6FB5FAE0(iVar11), iVar11 != 0 && (*(char*)(iVar11 + 0x5a) != '\0'))))
					{
						*(int*)(a2 + 0x44) = iVar11 + 0x5a;
						*(uint8_t*)(a2 + 0x1c) = *(uint8_t*)(a2 + 0x1c) | 1;
						return 1;
					}
					if (pDVar10->szUniqueInvFile[0] != '\0')
					{
						*(char**)(a2 + 0x44) = pDVar10->szUniqueInvFile;
						*(uint8_t*)(a2 + 0x1c) = *(uint8_t*)(a2 + 0x1c) | 1;
						return 1;
					}
				}
				bVar3 = ITEMS_GetVarInvGfxCount(pUnit);
				if (bVar3 == 0)
				{
					*(char**)(a2 + 0x44) = pDVar10->szInvFile;
					return 1;
				}
				pcVar12 = ITEMS_GetVarInvGfxString(pUnit, (uint32_t)local_18 & 0xff);
				*(char**)(a2 + 0x44) = pcVar12;
				return 1;
			}
			if (*(int*)(a2 + 0x28) == 3)
			{
				*(D2ItemsTxt**)(a2 + 0x44) = pDVar10;
				iVar11 = ITEMS_GetItemQuality(pUnit);
				if (iVar11 == 7)
				{
					iVar11 = ITEMS_GetFileIndex(pUnit);
					if (iVar11 < 0)
					{
						return 1;
					}
					iVar11 = ITEMS_GetFileIndex(pUnit);
					iVar11 = sub_6FB5FAE0(iVar11);
					if (iVar11 == 0)
					{
						return 1;
					}
					pcVar12 = (char*)(iVar11 + 0x3a);
				}
				else
				{
					iVar11 = ITEMS_GetItemQuality(pUnit);
					if (iVar11 != 5)
					{
						return 1;
					}
					iVar11 = ITEMS_GetFileIndex(pUnit);
					iVar11 = sub_6FAE5C80(iVar11);
					if (iVar11 == 0)
					{
						return 1;
					}
					pcVar12 = (char*)(iVar11 + 0x42);
				}
				if (*pcVar12 != '\0')
				{
					*(char**)(a2 + 0x44) = pcVar12;
				}
			}
		}
		return 1;
	case 5:
		goto LAB_6fb5e53c;
	default:
		iVar11 = *(int*)(a2 + 0x2c);
		*(uint8_t*)(a2 + 0x1c) = *(uint8_t*)(a2 + 0x1c) | 2;
		if (((-1 < iVar11) && (iVar11 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0))) &&
		    (iVar11 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbbc) + iVar11 * 0x84, iVar11 != 0))
		{
			*(int*)(a2 + 0x44) = iVar11 + 2;
		}
		return 1;
	}
	*pInventory2 = (D2InventoryStrc*)0xffffffff;
	if (((pUnit == nullptr) ||
	        (pInventory3 = (D2InventoryStrc*)(pUnit->dwFlagEx >> 3 & 1), pInventory3 == nullptr)) ||
	    ((iVar11 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar11 == 0 ||
	                                                             (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 == nullptr))))
	{
		pInventory3 = pUnit->pInventory;
	}
	else
	{
		pInventory3 = pDVar4->pInventory;
	}
	*(uint32_t*)(a2 + 0x34) = (&dword_6FBC2FF0)[*(uint8_t*)(a2 + 0x1d)];
	iVar11 = COMPOSIT_GetWeaponClassId(pUnit, pInventory3, &iStack_c, *(int*)(a2 + 0x28), 0);
	*(int*)(a2 + 0x40) = iVar11;
	puVar5 = sub_6FB58350(pUnit, iVar11, *(uint32_t**)(a2 + 0x28));
	if ((puVar5 == nullptr) &&
	    (puVar6 = sub_6FB58410(pUnit, *(uint32_t*)(a2 + 0x40), *(D2InventoryStrc**)(a2 + 0x28)), puVar6 == nullptr))
	{
		return 0;
	}
	pbVar7 = (uint8_t*)sub_6FB58320((int)pUnit, *(int*)(a2 + 0x28));
	if (pbVar7 == nullptr)
	{
		return 0;
	}
	iVar11 = sub_6FB28400((int)pUnit);
	if (iVar11 == 0)
	{
		return 0;
	}
	iVar11 = *(int*)(a2 + 0x20);
	iVar1 = *(int*)(a2 + 0x24);
	*(uint32_t*)(a2 + 0x38) = 0x2074696c;
	if (iVar11 == 0)
	{
		pDVar8 = (D2ObjModeTypeTxt*)DATATBLS_GetPlrModeTypeTxtRecord(iVar1, 0);
	LAB_6fb5e508:
		if (pDVar8 != nullptr)
		{
			pDVar8 = *(D2ObjModeTypeTxt**)pDVar8->szToken;
		}
	}
	else if (iVar11 == 1)
	{
		if (((iVar1 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar1)) ||
		    (iVar11 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar1 * 0x1a8, iVar11 == 0))
		{
			pDVar8 = nullptr;
		}
		else
		{
			pDVar8 = *(D2ObjModeTypeTxt**)(iVar11 + 0x10);
		}
	}
	else
	{
		if (iVar11 == 2)
		{
			pDVar8 = DATATBLS_GetObjModeTypeTxtRecord(iVar1, 0);
			goto LAB_6fb5e508;
		}
		pDVar8 = nullptr;
	}
	*(D2ObjModeTypeTxt**)(a2 + 0x30) = pDVar8;
	pbVar14 = pbVar7 + 0x1c;
	iVar11 = 0;
	if (*pbVar7 != 0)
	{
		do
		{
			if (0xf < *pbVar14)
			{
				return 0;
			}
			if (*pbVar14 == *(uint8_t*)(a2 + 0x1d))
			{
				local_18 = pbVar14;
				if (local_1c == 0)
				{
					pDVar4 = CUNIT_GetPlayer();
					uVar9 = local_1c;
					if (pUnit == pDVar4)
					{
						*(uint8_t*)(a2 + 0x1c) = *(uint8_t*)(a2 + 0x1c) | 8;
					}
					if (pInventory3 == nullptr)
					{
						*(uint32_t*)(a2 + 0x38) = 0x2074696c;
						return 0;
					}
					*(uint32_t*)(a2 + 0x3c) = (&dword_6FBC3060)[*(int*)(a2 + 0x28)];
					pDVar4 = INVENTORY_GetItemFromBodyLoc(pInventory3, 3);
					if ((uVar9 == 0) && (iVar11 = ITEMS_CanBeEquipped(pDVar4), iVar11 != 0))
					{
						if (pDVar4 == nullptr)
						{
							iVar11 = -1;
						}
						else
						{
							iVar11 = pDVar4->dwClassId;
						}
						pDVar10 = DATATBLS_GetItemsTxtRecord(iVar11);
						if (pDVar10 != nullptr)
						{
							iVar11 = 0;
							do
							{
								pbVar7 = abStack_8 + iVar11;
								iVar11 = iVar11 + 1;
								*pbVar7 = pbVar7[(int)pDVar10 + (0x116 - (int)abStack_8)];
							} while (iVar11 < 6);
						}
					}
					else
					{
						abStack_8[0] = 0;
						abStack_8[1] = 0;
						abStack_8[2] = 0;
						abStack_8[3] = 0;
						abStack_8[4] = 0;
						abStack_8[5] = 0;
					}
					pInventory3 = (D2InventoryStrc*)
					    INVENTORY_GetCompositItem(pInventory3, (uint32_t) * (uint8_t*)(a2 + 0x1d));
					iVar11 = COMPOSIT_IsArmorComponent((uint32_t) * (uint8_t*)(a2 + 0x1d));
					if (iVar11 == 0)
					{
						bVar3 = *(uint8_t*)(a2 + 0x1d);
						if (bVar3 < 0x10)
						{
							bVar2 = sub_6FB5BEA0((int)pUnit, 8);
							if (((D2C_ZEXT(bVar2) == 0) ||
							        (iVar11 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar11 == 0)) ||
							    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 == nullptr))
							{
								pDVar13 = pUnit->pInventory;
							}
							else
							{
								pDVar13 = pDVar4->pInventory;
							}
							iVar11 = COMPOSIT_GetWeaponClassId(pUnit, pDVar13, (int*)&pDStack_14, -1, 1);
							if (iVar11 == 0x20776278)
							{
								if ((bVar3 == 5) || (bVar3 == 6))
								{
									pDVar4 = INVENTORY_GetCompositItem(pDVar13, 5);
									if (pDVar4 == nullptr)
										goto LAB_6fb5e7f5;
									pDVar10 = DATATBLS_GetItemsTxtRecord(pDVar4->dwClassId);
									if (pDVar10 == nullptr)
									{
										uVar9 = 0x2074696c;
									}
									else
									{
										uVar9 = pDVar10->dwAlternateGfx;
										if (uVar9 == 0)
										{
											uVar9 = pDVar10->dwCode;
										}
									}
								}
								else
								{
								LAB_6fb5e7fc:
									if (((bVar3 == 7) && (iVar11 = STATES_CheckState(pUnit, 0x65), iVar11 != 0)) &&
									    (iVar11 = INVENTORY_GetEquippedShield(pDVar13, nullptr), iVar11 != 0))
									{
										uVar9 = 0x20687368;
									}
									else
									{
										uVar9 = 0;
									}
								}
							}
							else
							{
								if ((iVar11 != 0x20776f62) || (bVar3 != 5))
									goto LAB_6fb5e7fc;
							LAB_6fb5e7f5:
								uVar9 = 0x2074696c;
							}
						}
						else
						{
							uVar9 = 0x2074696c;
						}
						pDVar13 = pInventory3;
						*(uint32_t*)(a2 + 0x38) = uVar9;
						if (((pInventory3 == nullptr) || (uVar9 != 0)) ||
						    (iVar11 = ITEMS_CanBeEquipped((D2UnitStrc*)pInventory3), iVar11 == 0))
						{
							pbVar14 = local_18;
							if (*(int*)(a2 + 0x38) != 0)
								goto LAB_6fb5e863;
							goto LAB_6fb5e84d;
						}
						uVar9 = ITEMS_GetAltGfx((D2UnitStrc*)pDVar13);
						*(uint32_t*)(a2 + 0x38) = uVar9;
					}
					else if ((*(int*)(a2 + 0x28) == 0x11) || (*(int*)(a2 + 0x28) == 0))
					{
					LAB_6fb5e84d:
						*(uint32_t*)(a2 + 0x38) = 0x2074696c;
					}
					else
					{
						uVar9 = COMPOSIT_GetArmorTypeFromComponent((uint32_t) * (uint8_t*)(a2 + 0x1d), abStack_8);
						*(uint32_t*)(a2 + 0x38) = (&dword_6FBC3050)[uVar9];
					}
					pbVar14 = local_18;
					if (*(int*)(a2 + 0x38) == 0)
					{
						return 0;
					}
				}
				else if (local_1c == 1)
				{
					iVar11 = *(int*)(a2 + 0x28);
					*(uint32_t*)(a2 + 0x3c) = (&dword_6FBC2FB0)[iVar11];
					bVar3 = *pbVar14;
					if (((pUnit->dwUnitType == 1) && (bVar3 < 0x10)) &&
					    (pUnit->pPlayerData != nullptr))
					{
						pInventory3 = (D2InventoryStrc*)
						    CONCAT31((*(uint8_t*)((uint8_t*)&pInventory3 + 1)), pUnit->pPlayerData->szName[bVar3 + 4]);
					}
					else
					{
						pInventory3 = (D2InventoryStrc*)((uint32_t)(*(uint8_t*)((uint8_t*)&pInventory3 + 1)) << 8);
					}
					if (((iVar11 != 0) && (iVar11 != 0xc)) ||
					    (((iVar11 = *(int*)(a2 + 0x24), -1 < iVar11 &&
					                                        (((iVar1 = *(int*)((uint8_t*)&sgptDataTables), iVar11 < *(int*)(iVar1 + 0xa80) &&
					                                                                                           (iVar11 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + iVar11 * 0x1a8),
					                                                                                               -1 < iVar11)) &&
					                                            (iVar11 < *(int*)(iVar1 + 0xa98))))) &&
					        ((iVar11 = *(int*)(iVar1 + 0xa90) + iVar11 * 0x134, iVar11 != 0 &&
					                                                                (pDStack_14 = (D2InventoryStrc*)((uint32_t) * (uint8_t*)(iVar11 + 6) & *(uint32_t*)((uint8_t*)&gdwBitMasks)),
					                                                                    pDStack_14 != nullptr))))))
					{
						uVar9 = D2Common_11069(pUnit, (uint32_t)bVar3, (uint32_t)pInventory3 & 0xff);
						*(uint32_t*)(a2 + 0x38) = uVar9;
					}
				}
				else if (local_1c == 2)
				{
					*(uint32_t*)(a2 + 0x3c) = (&dword_6FBC3030)[*(int*)(a2 + 0x28)];
				}
			LAB_6fb5e863:
				bVar3 = pbVar14[5];
				if (bVar3 == 0)
				{
					pInventory3 = (D2InventoryStrc*)0x20202020;
				}
				else if (pbVar14[6] == 0)
				{
					(*(uint16_t*)((uint8_t*)&pInventory3 + 0)) = CONCAT11(0x20, bVar3);
					(*(uint8_t*)((uint8_t*)&pInventory3 + 0)) = CONCAT12(0x20, (*(uint16_t*)((uint8_t*)&pInventory3 + 0)));
					pInventory3 = (D2InventoryStrc*)CONCAT13(0x20, (*(uint8_t*)((uint8_t*)&pInventory3 + 0)));
				}
				else
				{
					(*(uint16_t*)((uint8_t*)&pInventory3 + 0)) = CONCAT11(pbVar14[6], bVar3);
					if (pbVar14[7] == 0)
					{
						(*(uint8_t*)((uint8_t*)&pInventory3 + 0)) = CONCAT12(0x20, (*(uint16_t*)((uint8_t*)&pInventory3 + 0)));
						pInventory3 = (D2InventoryStrc*)CONCAT13(0x20, (*(uint8_t*)((uint8_t*)&pInventory3 + 0)));
					}
					else
					{
						(*(uint8_t*)((uint8_t*)&pInventory3 + 0)) = CONCAT12(pbVar14[7], (*(uint16_t*)((uint8_t*)&pInventory3 + 0)));
						pInventory3 = (D2InventoryStrc*)CONCAT13(0x20, (*(uint8_t*)((uint8_t*)&pInventory3 + 0)));
					}
				}
				*(D2InventoryStrc**)(a2 + 0x40) = pInventory3;
				if (*(int*)(a2 + 0x34) == 0)
				{
					return 0;
				}
				if (*(int*)(a2 + 0x30) == 0)
				{
					return 0;
				}
				if (pInventory3 == nullptr)
				{
					return 0;
				}
				if (*(int*)(a2 + 0x3c) == 0)
				{
					*(uint32_t*)(a2 + 0x3c) = 0x20787878;
				}
				if (*(int*)(a2 + 0x38) == 0)
				{
					*(uint32_t*)(a2 + 0x38) = 0x2074696c;
				}
				pDVar10 = DATATBLS_GetItemRecordFromItemCode(*(uint32_t*)(a2 + 0x38), (int*)&pDStack_10);
				if (pDVar10 == nullptr)
				{
					return 1;
				}
				*pInventory2 = pDStack_10;
				return 1;
			}
			pbVar14 = pbVar14 + 9;
			iVar11 = iVar11 + 1;
		} while (iVar11 < (int)(uint32_t)*pbVar7);
	}
LAB_6fb5e53c:
	return 0;
}

//D2Client.0x6FB5EC80
int32_t __fastcall sub_6FB5EC80(int a1, D2UnitStrc* pUnit, uint32_t a3, D2CellFileStrc* pCellFile, D2CellFileStrc* pCellFile2, D2InventoryStrc** pInventory, uint8_t a7, D2InventoryStrc* pInventory2)
{
	*(uint32_t*)(a1 + 4) = a3;
	*(D2CellFileStrc**)(a1 + 0xc) = pCellFile;
	*(D2CellFileStrc**)(a1 + 8) = pCellFile2;
	*(uint8_t*)(a1 + 0x1d) = a7;
	return sub_6FB5E370(pUnit, a1, pInventory, pInventory2);
}

//D2Client.0x6FB5ECC0
uint32_t __fastcall sub_6FB5ECC0(int a1, uint32_t a2, uint8_t* a3, uint32_t a4, int a5, int dwWClass, int ptCofData, short* a8, int a9, int a10)
{
	uint8_t bVar1;
	uint32_t uVar2;
	uint8_t* pbVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	uint32_t nComponent;
	uint32_t uVar7;

	*(uint8_t**)(a1 + 8) = a3;
	*(uint32_t*)(a1 + 0xc) = a2;
	*(uint8_t*)(a1 + 0x1d) = (uint8_t)a4;
	D2_ASSERT(dwWClass);
	D2_ASSERT(ptCofData);
	nComponent = a4 & 0xff;
	*(int*)(a1 + 0x24) = (int)*a8;
	*(int*)(a1 + 0x28) = a5;
	*(uint32_t*)(a1 + 0x20) = 1;
	uVar2 = (&dword_6FBC2FF0)[nComponent];
	*(int*)(a1 + 0x40) = dwWClass;
	*(uint32_t*)(a1 + 0x34) = uVar2;
	*(uint32_t*)(a1 + 0x38) = 0x2074696c;
	*(uint32_t*)(a1 + 0x30) = *(uint32_t*)(a9 + 0x10);
	pbVar3 = *(uint8_t**)(ptCofData + 0x14);
	D2_ASSERT(pbVar3 != nullptr);
	a3 = pbVar3 + 0x1c;
	uVar7 = 0;
	if (*pbVar3 != 0)
	{
		do
		{
			D2_ASSERT(0xf >= *a3);
			if (*a3 == (uint8_t)a4)
			{
				*(uint32_t*)(a1 + 0x3c) = (&dword_6FBC2FB0)[a5];
				iVar5 = *(int*)(a1 + 0x24);
				bVar1 = *(uint8_t*)(a10 * 0x10 + nComponent + 4 + (int)a8);
				a4 = CONCAT31((*(uint8_t*)((uint8_t*)&a4 + 1)), bVar1);
				if (((a5 != 0) && (a5 != 0xc)) ||
				    (((-1 < iVar5 &&
				          (((iVar4 = *(int*)((uint8_t*)&sgptDataTables), iVar5 < *(int*)(iVar4 + 0xa80) &&
				                                                             (iVar6 = (int)*(short*)(*(int*)(iVar4 + 0xa78) + 0x18 + iVar5 * 0x1a8), -1 < iVar6)) &&
				              (iVar6 < *(int*)(iVar4 + 0xa98))))) &&
				        ((iVar4 = *(int*)(iVar4 + 0xa90) + iVar6 * 0x134, iVar4 != 0 &&
				                                                              (a8 = (short*)((uint32_t) * (uint8_t*)(iVar4 + 6) & *(uint32_t*)((uint8_t*)&gdwBitMasks)),
				                                                                  a8 != nullptr))))))
				{
					iVar5 = D2Common_11070(iVar5, nComponent, (uint32_t)bVar1);
					*(int*)(a1 + 0x38) = iVar5;
				}
				a4 = 0;
				sub_6FB5FA60((char*)(a3 + 5), (char*)&a4);
				*(uint32_t*)(a1 + 0x40) = a4;
				D2_ASSERT(*(int*)(a1 + 0x34));
				D2_ASSERT(*(int*)(a1 + 0x30));
				D2_ASSERT(a4);
				if (*(int*)(a1 + 0x38) == 0)
				{
					*(uint32_t*)(a1 + 0x38) = 0x20787878;
				}
				if (*(int*)(a1 + 0x3c) == 0)
				{
					*(uint32_t*)(a1 + 0x3c) = 0x20787878;
				}
				return 1;
			}
			a3 = a3 + 9;
			uVar7 = uVar7 + 1;
		} while (uVar7 < *pbVar3);
	}
	return 0;
}

//D2Client.0x6FB5EF30
Unicode* __fastcall sub_6FB5EF30(Unicode* pUnicode)
{
	return pUnicode;
}

//D2Client.0x6FB5EF40
uint8_t __fastcall sub_6FB5EF40(uint8_t* a1, uint32_t a2)
{
	uint8_t bVar1;
	uint8_t* pbVar2;
	int iVar3;

	bVar1 = 0;
	if ((a1 != nullptr) && ((int)a2 < 0x10))
	{
		pbVar2 = a1 + 0x1c;
		iVar3 = 0;
		if (*a1 != 0)
		{
			while (*pbVar2 != a2)
			{
				pbVar2 = pbVar2 + 9;
				iVar3 = iVar3 + 1;
				if ((int)(uint32_t)*a1 <= iVar3)
				{
					return 0;
				}
			}
			bVar1 = pbVar2[3];
		}
	}
	return bVar1;
}

//D2Client.0x6FB5EF80
uint8_t __fastcall sub_6FB5EF80(uint8_t* a1, uint32_t a2)
{
	uint8_t bVar1;
	uint8_t* pbVar2;
	int iVar3;

	bVar1 = 0;
	if ((a1 != nullptr) && ((int)a2 < 0x10))
	{
		pbVar2 = a1 + 0x1c;
		iVar3 = 0;
		if (*a1 != 0)
		{
			while (*pbVar2 != a2)
			{
				pbVar2 = pbVar2 + 9;
				iVar3 = iVar3 + 1;
				if ((int)(uint32_t)*a1 <= iVar3)
				{
					return 0;
				}
			}
			bVar1 = pbVar2[1];
		}
	}
	return bVar1;
}

//D2Client.0x6FB5EFC0
uint8_t* __fastcall sub_6FB5EFC0(uint8_t* a1, int a2, int a3)
{
	uint8_t* pbVar1;

	pbVar1 = nullptr;
	if (a1 != nullptr)
	{
		pbVar1 = a1 + ((uint32_t)a1[1] * a2 + 9 + a3) * (uint32_t)*a1 +
		         (uint32_t)a1[1] + 0x1c;
	}
	return pbVar1;
}

//D2Client.0x6FB5EFF0
uint8_t __fastcall sub_6FB5EFF0(uint8_t* a1, uint32_t a2)
{
	int iVar1;
	uint8_t* pbVar2;

	if ((a1 != nullptr) && ((int)a2 < 0x10))
	{
		pbVar2 = a1 + 0x1c;
		iVar1 = 0;
		if (*a1 != 0)
		{
			do
			{
				if (*pbVar2 == a2)
				{
					return pbVar2[4];
				}
				pbVar2 = pbVar2 + 9;
				iVar1 = iVar1 + 1;
			} while (iVar1 < (int)(uint32_t)*a1);
		}
	}
	return 5;
}

//D2Client.0x6FB5F030
uint32_t __fastcall sub_6FB5F030(int* a1)
{
	if (((a1 != nullptr) && (-1 < *a1)) && (*a1 < 3))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FB5F050
uint8_t __fastcall sub_6FB5F050(int a1, int a2)
{
	int iVar1;

	iVar1 = sub_6FB28400(a1);
	if (iVar1 == 0)
	{
		return 0;
	}
	return *(uint8_t*)(iVar1 + a2 * 2);
}

//D2Client.0x6FB5F070
int32_t __fastcall sub_6FB5F070(int a1, int a2, uint8_t a3)
{
	int iVar1;

	iVar1 = sub_6FB28400(a1);
	if (iVar1 != 0)
	{
		*(uint8_t*)(iVar1 + a2 * 2) = a3;
	}
	return 0;
}

//D2Client.0x6FB5F090
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB5F090(D2UnitStrc* pUnit, uint32_t a22, int a3, uint32_t* a4, uint32_t* a5, uint32_t* a6, uint32_t* a7, uint32_t a8, int a9)
{
	uint32_t uVar1;
	uint32_t* puVar2;
	uint32_t* puVar3;
	uint32_t* puVar4;
	uint32_t a2;
	D2UnitStrc* pDVar5;
	int iVar6;
	int iVar7;
	uint32_t extraout_EAX;
	uint32_t uVar8;
	D2DynamicPathStrc* pDynamicPath;

	puVar3 = a5;
	puVar2 = a4;
	if (0x3f < *a5)
	{
		*a7 = 1;
		*a6 = 0;
		return;
	}
	uVar8 = 1;
	if (-1 < (int)a4)
	{
		switch (a22)
		{
		case 0:
			if ((dword_6FBC2FA4 == 0) && (pDVar5 = CUNIT_GetPlayer(), pUnit == pDVar5))
			{
				uVar8 = 0x10;
			}
			else
			{
				uVar8 = 8;
			}
			break;
		case 1:
			if ((((-1 < a3) &&
			         (iVar7 = *(int*)((uint8_t*)&sgptDataTables), a3 < *(int*)(iVar7 + 0xa80))) &&
			        ((iVar6 = (int)*(short*)(*(int*)(iVar7 + 0xa78) + 0x18 + a3 * 0x1a8), -1 < iVar6 &&
			                                                                                  ((iVar6 < *(int*)(iVar7 + 0xa98) &&
			                                                                                      (iVar7 = *(int*)(iVar7 + 0xa90) + iVar6 * 0x134, iVar7 != 0)))))) &&
			    ((uVar8 = (uint32_t) * (uint8_t*)(iVar7 + 0xf4 + (int)a4), uVar8 == 8 &&
			                                                                   ((iVar7 = sub_6FB5DAA0(a3), iVar7 != 0 && (*(int*)(iVar7 + (int)puVar2 * 4) == 0))))))
			{
				uVar8 = 4;
			}
			break;
		case 2:
		case 4:
		switchD_6fb5f0d6_caseD_2:
			uVar8 = 1;
			break;
		case 3:
			if (((-1 < a3) && (a3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
			    (iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a3 * 0x1a4, iVar7 != 0))
			{
				uVar8 = (uint32_t) * (uint8_t*)(iVar7 + 0x1a0);
			}
			break;
		case 6:
			iVar7 = sub_6FB5FAB0(a3);
			if (iVar7 == 0)
				goto switchD_6fb5f0d6_caseD_2;
			uVar8 = (uint32_t) * (uint8_t*)(iVar7 + 0x80);
		}
	}
	a2 = a8;
	puVar4 = a7;
	*a7 = uVar8;
	if (a9 == 0)
		goto LAB_6fb5f2ee;
	if (a8 == 8)
	{
		if (uVar8 == 4)
		{
			iVar7 = D2CMP_10019((*puVar3 << 3) >> 6, 8, 4, 0);
			uVar8 = (uint32_t)(iVar7 << 6) >> 3;
		LAB_6fb5f249:
			*puVar3 = uVar8;
		}
	}
	else if ((a8 == 0x10) && (uVar8 == 8))
	{
		iVar7 = D2CMP_10019((*puVar3 << 4) >> 6, 0x10, 8, 0);
		uVar8 = (uint32_t)(iVar7 << 6) >> 4;
		goto LAB_6fb5f249;
	}
	uVar8 = *puVar4;
	uVar1 = *puVar3;
	if (pUnit == nullptr)
	{
		a7 = (uint32_t*)0x6;
		a5 = (uint32_t*)0xffffffff;
	}
	else
	{
		a7 = (uint32_t*)pUnit->dwUnitType;
		a5 = (uint32_t*)pUnit->dwClassId;
	}
	a3 = UNITS_GetAnimOrSeqMode(pUnit);
	D2COMMON_11013_ConvertMode(pUnit, (int*)&a7, (int*)&a5, &a3,
	    __FILE__, __LINE__);
	if (a7 == nullptr)
	{
		if (((a3 != 0) && (a3 != 0x11)) || (uVar8 == a2))
			goto LAB_6fb5f2ee;
		pDynamicPath = pUnit->pDynamicPath;
	}
	else
	{
		if (((a7 != (uint32_t*)0x1) || ((a3 != 0 && (a3 != 0xc)))) || (uVar8 == a2))
			goto LAB_6fb5f2ee;
		pDynamicPath = pUnit->pDynamicPath;
	}
	PATH_SetDirection(pDynamicPath, (uint8_t)uVar1);
LAB_6fb5f2ee:
	D2CMP_10022(*puVar3, a2);
	*a6 = extraout_EAX;
}

//D2Client.0x6FB5F330
int __fastcall sub_6FB5F330(D2UnitStrc* pUnit, uint8_t* a2, int a3, int* a4, D2CellFileStrc* pCellFile, D2CellFileStrc* pCellFile2)
{
	uint8_t bVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	D2CellFileStrc** ppDVar6;
	int local_54;
	D2InventoryStrc* local_4c;
	D2CellFileStrc* local_48[7];
	uint8_t local_2b;

	iVar5 = 0;
	local_54 = 0;
	if (*a2 != 0)
	{
		do
		{
			bVar1 = *(uint8_t*)(iVar5 + a3);
			D2_ASSERT(0xf >= bVar1);
			ppDVar6 = local_48;
			for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*ppDVar6 = nullptr;
				ppDVar6 = ppDVar6 + 1;
			}
			local_48[1] = nullptr;
			local_48[3] = pCellFile;
			local_48[2] = pCellFile2;
			local_2b = bVar1;
			iVar4 = sub_6FB5E370(pUnit, (int)local_48, &local_4c, (D2InventoryStrc*)0xffffffff);
			if (iVar4 != 0)
			{
				iVar4 = D2CMP_10055((int)local_48, 0, 1);
				if ((iVar4 != 0) && (local_48[0] != nullptr))
				{
					iVar4 = D2CMP_CelGetOffsetY(local_48[0]);
					iVar2 = sub_6FAB58A0();
					iVar3 = UNITS_GetClientCoordY(pUnit);
					iVar3 = (iVar4 - iVar2) + iVar3;
					if (*a4 < iVar3)
					{
						*a4 = iVar3;
					}
					local_54 = local_54 + 1;
				}
			}
			iVar5 = iVar5 + 1;
		} while (iVar5 < (int)(uint32_t)*a2);
	}
	return local_54;
}

//D2Client.0x6FB5F420
uint32_t __fastcall sub_6FB5F420(D2UnitStrc* pUnit, int a2, uint32_t* a3, int a4)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pItem;
	D2ItemsTxt* pDVar3;
	D2InventoryStrc* pInventory;
	uint32_t uVar4;
	uint32_t local_c;
	int iStack_8;
	int local_4;

	if (pUnit == nullptr)
	{
		uVar4 = 6;
	}
	else if ((pUnit->dwFlagEx >> 3 & 1) == 0)
	{
		local_4 = 0;
		uVar4 = pUnit->dwUnitType;
	}
	else
	{
		local_c = pUnit->dwUnitType;
		local_4 = pUnit->dwClassId;
		iStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_4, &iStack_8, __FILE__, __LINE__);
		uVar4 = local_c;
	}
	if (uVar4 == 0)
	{
		iVar1 = STATLIST_UnitGetStatValue(pUnit, 0xb5, 0);
		if (iVar1 != 0)
		{
			*a3 = 1;
			return 1;
		}
	}
	else if ((uVar4 == 1) && (iVar1 = STATLIST_UnitGetStatValue(pUnit, 0xb5, 0), 0 < iVar1))
	{
		if (0xf < iVar1)
		{
			if (pUnit->pInventory == nullptr)
			{
				return 0;
			}
			pDVar2 = INVENTORY_GetFirstItem(pUnit->pInventory);
			while (true)
			{
				if (pDVar2 == nullptr)
				{
					return 0;
				}
				pItem = INVENTORY_UnitIsItem(pDVar2);
				if ((pItem != nullptr) &&
				    (iVar1 = ITEMS_CheckItemFlag(pItem, 0x400000, __LINE__, __FILE__), iVar1 != 0))
					break;
				pDVar2 = INVENTORY_GetNextItem(pDVar2);
			}
			*a3 = 1;
			return 1;
		}
		goto LAB_6fb5f64c;
	}
	if (((a4 != -1) &&
	        (pDVar3 = DATATBLS_GetItemsTxtRecord(a4), pDVar3 != nullptr)) &&
	    (pDVar3->nTransparent != 0))
	{
		*a3 = (uint32_t)pDVar3->nTransTbl;
		return 1;
	}
	if (uVar4 == 0)
	{
		if (((pUnit == nullptr) || ((pUnit->dwFlagEx >> 3 & 1) == 0)) ||
		    ((iVar1 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar1 == 0 ||
		                                                            (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 == nullptr))))
		{
			pInventory = pUnit->pInventory;
		}
		else
		{
			pInventory = pDVar2->pInventory;
		}
		if (pInventory != nullptr)
		{
			if (a2 == 5)
			{
				pDVar2 = INVENTORY_GetCompositItem(pInventory, 5);
				if ((pDVar2 != nullptr) &&
				    (iVar1 = ITEMS_CheckItemFlag(pDVar2, 0x400000, __LINE__, __FILE__), iVar1 != 0))
				{
					*a3 = 1;
					return 1;
				}
			}
			else if (a2 == 6)
			{
				pDVar2 = INVENTORY_GetCompositItem(pInventory, 6);
				if ((pDVar2 != nullptr) &&
				    (iVar1 = ITEMS_CheckItemFlag(pDVar2, 0x400000, __LINE__, __FILE__), iVar1 != 0))
				{
				LAB_6fb5f64c:
					*a3 = 1;
					return 1;
				}
			}
			else if (((a2 == 7) &&
			             (pDVar2 = INVENTORY_GetCompositItem(pInventory, 7), pDVar2 != nullptr)) &&
			         (iVar1 = ITEMS_CheckItemFlag(pDVar2, 0x400000, __LINE__, __FILE__), iVar1 != 0))
			{
				*a3 = 2;
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB5F6B0
int __fastcall sub_6FB5F6B0(D2UnitStrc* pUnit, int a2, int a3)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	uint8_t* pbVar4;
	D2InventoryStrc* pInventory;
	uint8_t bStack_d;
	uint32_t local_c;
	int iStack_8;
	uint32_t local_4;

	if ((a2 < 0x10) && (pUnit != nullptr))
	{
		uVar3 = pUnit->dwUnitType;
		if ((pUnit->dwFlagEx >> 3 & 1) != 0)
		{
			local_4 = pUnit->dwClassId;
			local_c = pUnit->dwUnitType;
			iStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, (int*)&local_4, &iStack_8, __FILE__, __LINE__);
			uVar3 = local_c;
		}
		if (uVar3 == 0)
		{
			local_4 = pUnit->dwFlagEx >> 3 & 1;
			if (((local_4 == 0) || (iVar1 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar1 == 0)) ||
			    (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 == nullptr))
			{
				pInventory = pUnit->pInventory;
			}
			else
			{
				pInventory = pDVar2->pInventory;
			}
			if ((pInventory != nullptr) &&
			    (((pDVar2 = INVENTORY_GetCompositItem(pInventory, a2), pDVar2 != nullptr ||
			                                                               (((a2 != 1 && (iVar1 = COMPOSIT_IsArmorComponent(a2), iVar1 != 0)) &&
			                                                                   (pDVar2 = INVENTORY_GetCompositItem(pInventory, 1), pDVar2 != nullptr)))) &&
			        ((iVar1 = ITEMS_CheckItemFlag(pDVar2, 0x100, __LINE__, __FILE__), iVar1 == 0 &&
			                                                                              (iVar1 = ITEMS_CheckItemFlag(pDVar2, 0x4000, __LINE__, __FILE__), iVar1 == 0))))))
			{
				uVar3 = ITEMS_GetAltGfx(pDVar2);
				if (uVar3 == 0x2074696c)
				{
					return 0;
				}
				pbVar4 = ITEMS_GetColor(pUnit, pDVar2, &bStack_d, 0);
				if (pbVar4 != nullptr)
				{
					return (int)pbVar4;
				}
			}
		}
	}
	return a3;
}

//D2Client.0x6FB5F7F0
uint8_t __fastcall sub_6FB5F7F0(D2UnitStrc* pUnit, uint32_t a2)
{
	uint8_t bVar1;
	int iVar2;
	int nXPos;
	int* piVar3;
	D2UnitStrc* pDVar4;
	D2InventoryStrc* pInventory;
	uint32_t uVar5;
	uint32_t* puVar6;
	uint32_t* puVar7;
	uint8_t* pbVar8;
	uint8_t* pbVar9;
	int nBais;
	int* pXAdjust;
	int local_18;
	int local_14;
	int iStack_10;
	int iStack_c;
	uint32_t uStack_8;
	int iStack_4;

	local_18 = 0;
	local_14 = 0;
	iVar2 = D2GFX_CheckPerspective();
	if (iVar2 == 0)
	{
		iVar2 = UNITS_GetClientCoordX(pUnit);
		local_18 = sub_6FAB5890();
		local_18 = iVar2 - local_18;
		iVar2 = UNITS_GetClientCoordY(pUnit);
		local_14 = sub_6FAB58A0();
		local_14 = iVar2 - local_14;
	}
	else
	{
		piVar3 = &local_14;
		pXAdjust = &local_18;
		nBais = 0;
		iVar2 = UNITS_GetPrecisionY(pUnit);
		nXPos = UNITS_GetPrecisionX(pUnit);
		SCALE_AdjustPerspectivePosition(nXPos, iVar2, nBais, pXAdjust, piVar3);
		iVar2 = sub_6FAB5750();
		if (iVar2 == 1)
		{
			local_18 = local_18 - ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
		}
		else if (iVar2 == 2)
		{
			local_18 = local_18 + ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
		}
	}
	piVar3 = sub_6FB5C7D0(pUnit, local_18, local_14, 0, 0);
	if (piVar3 != nullptr)
	{
		if ((((pUnit == nullptr) || (uStack_8 = pUnit->dwFlagEx >> 3 & 1, uStack_8 == 0)) || (iVar2 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar2 == 0)) ||
		    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 == nullptr))
		{
			pInventory = pUnit->pInventory;
		}
		else
		{
			pInventory = pDVar4->pInventory;
		}
		uVar5 = COMPOSIT_GetWeaponClassId(pUnit, pInventory, &iStack_4, -1, 1);
		puVar6 = sub_6FB58350(pUnit, uVar5, (uint32_t*)0xffffffff);
		if ((puVar6 == nullptr) &&
		    (puVar7 = sub_6FB58410(pUnit, uVar5, (D2InventoryStrc*)0xffffffff), puVar7 == nullptr))
		{
			return 0;
		}
		uStack_8 = pUnit->dwFlagEx >> 3 & 1;
		if (uStack_8 == 0)
		{
			iVar2 = UNITS_GetAnimOrSeqMode(pUnit);
		}
		else
		{
			uStack_8 = pUnit->dwUnitType;
			iStack_c = pUnit->dwClassId;
			iStack_10 = UNITS_GetAnimOrSeqMode(pUnit);
			D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_8, &iStack_c, &iStack_10, __FILE__, __LINE__);
			iVar2 = iStack_10;
		}
		pbVar8 = (uint8_t*)sub_6FB58320((int)pUnit, iVar2);
		bVar1 = 0;
		if ((pbVar8 != nullptr) && ((int)a2 < 0x10))
		{
			pbVar9 = pbVar8 + 0x1c;
			bVar1 = 0;
			iVar2 = 0;
			if (*pbVar8 != 0)
			{
				while (*pbVar9 != a2)
				{
					pbVar9 = pbVar9 + 9;
					iVar2 = iVar2 + 1;
					if ((int)(uint32_t)*pbVar8 <= iVar2)
					{
						return 0;
					}
				}
				bVar1 = pbVar9[2];
			}
		}
		return bVar1;
	}
	return 0;
}

//D2Client.0x6FB5F9D0
int __fastcall sub_6FB5F9D0(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	uint8_t bVar2;
	int iVar3;
	uint32_t* puVar4;
	D2InventoryStrc* pDStack_4c;
	uint32_t local_48[5];
	int iStack_34;
	uint8_t uStack_2b;
	uint32_t local_1c;

	puVar4 = local_48;
	for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar4 = 0;
		puVar4 = puVar4 + 1;
	}
	local_1c = *(uint32_t*)(a2 + 4);
	uVar1 = *(uint32_t*)(a2 + 0x18);
	bVar2 = UNITS_GetDirection(pUnit);
	local_48[3] = (uint32_t)bVar2;
	local_48[1] = 0;
	uStack_2b = 1;
	local_48[2] = uVar1;
	iVar3 = sub_6FB5E370(nullptr, (int)local_48, &pDStack_4c, (D2InventoryStrc*)0xffffffff);
	if (iVar3 == 0)
	{
		return 1;
	}
	iVar3 = D2CMP_10055((int)local_48, 0, 1);
	if (iVar3 == 0)
	{
		return 1;
	}
	return iStack_34 << 8;
}

//D2Client.0x6FB5FA60
void __fastcall sub_6FB5FA60(char* a1, char* a2)
{
	if (*a1 == '\0')
	{
		memcpy(a2, "    ", 4);
		return;
	}
	*a2 = *a1;
	if (a1[1] == '\0')
	{
		a2[1] = ' ';
		a2[2] = ' ';
		a2[3] = ' ';
		return;
	}
	a2[1] = a1[1];
	if (a1[2] == '\0')
	{
		a2[2] = ' ';
		a2[3] = ' ';
		return;
	}
	a2[2] = a1[2];
	a2[3] = ' ';
}

//D2Client.0x6FB5FAB0
int __fastcall sub_6FB5FAB0(int a1)
{
	if ((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0)))
	{
		return *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbbc) + a1 * 0x84;
	}
	return 0;
}

//D2Client.0x6FB5FAE0
int __fastcall sub_6FB5FAE0(int a1)
{
	if ((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc28)))
	{
		return *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc24) + a1 * 0x14c;
	}
	return 0;
}
