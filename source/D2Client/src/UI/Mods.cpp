#include "UI/Mods.h"

#include "Draw/DFloor.h"
#include "Game/Msg.h"
#include "Sound/SoundInst.h"
#include "UI/Dialog.h"
#include "UI/Inv.h"
#include "UI/NpcMenu.h"
#include "UI/ShowItems.h"
#include "UI/Text.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/UnitMode.h"

//D2Client.0x6FB6FA30
uint16_t word_6FB6FA30[2] = {0x52F3, 0x52F5};
//D2Client.0x6FB6FA38
uint32_t dword_6FB6FA38 = 0xA5;
//D2Client.0x6FB6FA50
uint8_t byte_6FB6FA50[256] = {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 6};
//D2Client.0x6FB79B48
uint32_t dword_6FB79B48 = 0xFFFFFFFF;
//D2Client.0x6FB7A438
int32_t dword_6FB7A438 = 143;
//D2Client.0x6FB7A440
uint32_t dword_6FB7A440;
//D2Client.0x6FB7A4A0
uint32_t dword_6FB7A4A0 = 6;
//D2Client.0x6FBB5BE5
uint8_t byte_6FBB5BE5;

//D2Client.0x6FAF12C0
void __fastcall sub_6FAF12C0(D2UnitStrc* pUnit, Unicode* pUnicode, uint32_t a3)
{
	Unicode* a2;
	Unicode* a2_00;
	Unicode* a2_01;
	Unicode* a2_02;
	Unicode* pUVar1;
	int iVar2;
	char acStack_120[12];
	Unicode aUStack_114[10];
	Unicode local_100[128];

	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa2));
	a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	a2_01 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2_02 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa1));
	SStrPrintf(acStack_120, 10, "%i", 0x32);
	Unicode::toUnicode(aUStack_114, acStack_120, 9);
	Unicode::strcat(local_100, a2);
	Unicode::strcat(local_100, aUStack_114);
	Unicode::strcat(local_100, a2_02);
	Unicode::strcat(local_100, a2_01);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xde2));
	Unicode::strcat(local_100, pUVar1);
	Unicode::strcat(local_100, a2_00);
	Unicode::strcat(pUnicode, local_100);
}

//D2Client.0x6FAF13C0
size_t __fastcall sub_6FAF13C0(D2UnitStrc* pUnit, uint32_t a2, int a3, int a4, uint32_t a5, uint32_t a6)
{
	D2StatListStrc* pStatList;
	size_t sVar1;
	int iVar2;
	Unicode* pThis;
	Unicode aUStack_800[1024];

	ITEMMODS_AssignProperty(5, nullptr, pUnit, (void*)a2, a3, 0);
	aUStack_800[0].ch = 0;
	sub_6FAF3160(pUnit, aUStack_800, a5, 1, a6);
	Unicode::strcat((Unicode*)a4, aUStack_800);
	pStatList = STATLIST_GetStatListFromUnitStateOrFlag(pUnit, 0, 0x40);
	if (pStatList != nullptr)
	{
		D2Common_10474(pUnit, pStatList);
		STATLIST_FreeStatList(pStatList);
	}
	iVar2 = Unicode::strlen((Unicode*)a4);
	sVar1 = a4 + -2 + iVar2 * 2;
	if (*(short*)(a4 + -2 + iVar2 * 2) == 10)
	{
		sVar1 = Unicode::strlen((Unicode*)a4);
		*(uint16_t*)(a4 + -2 + sVar1 * 2) = 0;
	}
	return sVar1;
}

//D2Client.0x6FAF1480
void __fastcall sub_6FAF1480(D2UnitStrc* pUnit, uint16_t* a2, uint32_t a3)
{
	D2ItemsTxt* pDVar1;
	D2GemsTxt* pDVar2;
	Unicode* pUVar3;
	D2StatListStrc* pDVar4;
	code* pcVar5;
	int iVar6;
	Unicode local_200[256];

	iVar6 = ITEMS_CheckItemTypeId(pUnit, 0x35);
	D2_ASSERT(iVar6);
	if (pUnit == nullptr)
	{
		iVar6 = -1;
	}
	else
	{
		iVar6 = pUnit->dwClassId;
	}
	pDVar1 = DATATBLS_GetItemsTxtRecord(iVar6);
	D2_ASSERT(pDVar1 != nullptr);
	*a2 = 0;
	iVar6 = ITEMS_CheckItemTypeId(pUnit, 0x14);
	if (iVar6 == 0)
	{
		iVar6 = ITEMS_CheckItemTypeId(pUnit, 0x4a);
		if (iVar6 == 0)
		{
			return;
		}
		pDVar2 = DATATBLS_GetGemsTxtRecord(pDVar1->dwGemOffset);
		D2_ASSERT(pDVar2 != nullptr);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		pcVar5 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar3);
		local_200[0].ch = 0;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b42));
		Unicode::strcat(local_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(local_200, pUVar3);
		sub_6FAF13C0(pUnit, (uint32_t)pDVar2, 2, (int)(a2), a3, (uint32_t)(local_200));
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)a2, pUVar3);
		local_200[0].ch = 0;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b41));
		Unicode::strcat(local_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(local_200, pUVar3);
		sub_6FAF13C0(pUnit, (uint32_t)pDVar2, 1, (int)(a2), a3, (uint32_t)(local_200));
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)a2, pUVar3);
		local_200[0].ch = 0;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b44));
		Unicode::strcat(local_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(local_200, pUVar3);
		sub_6FAF13C0(pUnit, (uint32_t)pDVar2, 1, (int)(a2), a3, (uint32_t)(local_200));
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)a2, pUVar3);
		local_200[0].ch = 0;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b43));
		Unicode::strcat(local_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(local_200, pUVar3);
		sub_6FAF13C0(pUnit, (uint32_t)pDVar2, 0, (int)(a2), a3, (uint32_t)(local_200));
	}
	else
	{
		pDVar2 = DATATBLS_GetGemsTxtRecord(pDVar1->dwGemOffset);
		D2_ASSERT(pDVar2 != nullptr);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		pcVar5 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar3);
		local_200[0].ch = 0;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b42));
		Unicode::strcat(local_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(local_200, pUVar3);
		ITEMMODS_AssignProperty(2, nullptr, pUnit, pDVar2, 2, 0);
		sub_6FAF3160(pUnit, (Unicode*)(a2), a3, 0, (int)(local_200));
		pDVar4 = STATLIST_GetStatListFromUnitStateOrFlag(pUnit, 0, 0x40);
		if (pDVar4 != nullptr)
		{
			D2Common_10474(pUnit, pDVar4);
			STATLIST_FreeStatList(pDVar4);
		}
		iVar6 = Unicode::strlen((Unicode*)a2);
		if (a2[iVar6 + -1] == 10)
		{
			iVar6 = Unicode::strlen((Unicode*)a2);
			a2[iVar6 + -1] = 0;
		}
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)a2, pUVar3);
		local_200[0].ch = 0;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b41));
		Unicode::strcat(local_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(local_200, pUVar3);
		ITEMMODS_AssignProperty(2, nullptr, pUnit, pDVar2, 1, 0);
		sub_6FAF3160(pUnit, (Unicode*)(a2), a3, 0, (int)(local_200));
		pDVar4 = STATLIST_GetStatListFromUnitStateOrFlag(pUnit, 0, 0x40);
		if (pDVar4 != nullptr)
		{
			D2Common_10474(pUnit, pDVar4);
			STATLIST_FreeStatList(pDVar4);
		}
		iVar6 = Unicode::strlen((Unicode*)a2);
		if (a2[iVar6 + -1] == 10)
		{
			iVar6 = Unicode::strlen((Unicode*)a2);
			a2[iVar6 + -1] = 0;
		}
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)a2, pUVar3);
		local_200[0].ch = 0;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b44));
		Unicode::strcat(local_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(local_200, pUVar3);
		ITEMMODS_AssignProperty(2, nullptr, pUnit, pDVar2, 1, 0);
		sub_6FAF3160(pUnit, (Unicode*)(a2), a3, 0, (int)(local_200));
		pDVar4 = STATLIST_GetStatListFromUnitStateOrFlag(pUnit, 0, 0x40);
		if (pDVar4 != nullptr)
		{
			D2Common_10474(pUnit, pDVar4);
			STATLIST_FreeStatList(pDVar4);
		}
		iVar6 = Unicode::strlen((Unicode*)a2);
		if (a2[iVar6 + -1] == 10)
		{
			iVar6 = Unicode::strlen((Unicode*)a2);
			a2[iVar6 + -1] = 0;
		}
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)a2, pUVar3);
		local_200[0].ch = 0;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b43));
		Unicode::strcat(local_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(local_200, pUVar3);
		ITEMMODS_AssignProperty(2, nullptr, pUnit, pDVar2, 0, 0);
		sub_6FAF3160(pUnit, (Unicode*)(a2), a3, 0, (int)(local_200));
		pDVar4 = STATLIST_GetStatListFromUnitStateOrFlag(pUnit, 0, 0x40);
		if (pDVar4 != nullptr)
		{
			D2Common_10474(pUnit, pDVar4);
			STATLIST_FreeStatList(pDVar4);
		}
		iVar6 = Unicode::strlen((Unicode*)a2);
		if (a2[iVar6 + -1] == 10)
		{
			iVar6 = Unicode::strlen((Unicode*)a2);
			a2[iVar6 + -1] = 0;
		}
	}
	D2LANG_GetStringFromTblIndex(0xf9e);
	(*pcVar5)();
	D2LANG_GetStringFromTblIndex(0xf9e);
	(*pcVar5)();
}

//D2Client.0x6FAF19C0
// TODO: decompilation needs review (in_stack, stack0x)
void __cdecl sub_6FAF19C0(int* a12, uint32_t a22, int a3, uint32_t a4, uint32_t a5, uint32_t a6)
{
	uint8_t stack0x00000024[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000038[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000044[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000048[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000000ec[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000001ec[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000002ec[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000003ec[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000004ec[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000004f0[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint16_t uVar1;
	bool bVar2;
	uint32_t uVar3;
	Unicode* pUVar4;
	Unicode* pUVar5;
	Unicode* pUVar6;
	int iVar7;
	D2StatListStrc* pDVar8;
	void* pMemPool;
	D2StatListExStrc* pStatListEx;
	D2UnitStrc* pItem;
	D2UnitStrc* pUnit;
	int iVar9;
	int iVar10;
	D2ItemsTxt* pDVar11;
	short index;
	D2UnitStrc* pItem_00;
	uint32_t nUnitType;
	Unicode* a1;
	Unicode* a2;
	int iVar12;
	int* piVar13;
	uint32_t* puVar14;
	Unicode* pUStack0000001c;
	int in_stack_00000044;
	int in_stack_00000048;
	int in_stack_0000005c;
	int in_stack_00000060;
	int in_stack_00000074;
	int in_stack_00000078;
	int in_stack_0000008c;
	int in_stack_00000090;
	int in_stack_000000a4;
	int in_stack_000000a8;
	int in_stack_000000bc;
	int in_stack_000000c0;
	int in_stack_000000c4;
	int in_stack_000000c8;
	int in_stack_000000d4;
	int in_stack_000000d8;
	Unicode UStack000000ec;
	Unicode UStack000001ec;
	int in_stack_000014ec;
	int in_stack_000014f0;
	int in_stack_000014f4;
	int in_stack_000014f8;
	int in_stack_000014fc;

	pUVar4 = (Unicode*)stack0x000002ec;
	iVar12 = 0x80;
	do
	{
		pUVar4 = pUVar4 + 1;
		iVar12 = iVar12 + -1;
	} while (iVar12 != 0);
	pUVar4 = (Unicode*)stack0x000003ec;
	iVar12 = 0x80;
	do
	{
		pUVar4 = pUVar4 + 1;
		iVar12 = iVar12 + -1;
	} while (iVar12 != 0);
	uVar3 = ITEMS_GetItemType(pItem_00);
	if (uVar3 == 0xb)
	{
		pUVar4 = (Unicode*)(stack0x000001ec);
		iVar12 = 0x80;
		do
		{
			pUVar4 = pUVar4 + 1;
			iVar12 = iVar12 + -1;
		} while (iVar12 != 0);
		memset(stack0x000000ec, 0, 2 * (0x80));
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa2));
		pUStack0000001c = (Unicode*)ITEMS_GetFileIndex(pItem_00);
		a22 = 0;
		if (dword_6FB7A4A0 != 0)
		{
			piVar13 = (int*)(&dword_6FB7A440);
			do
			{
				if ((Unicode*)*piVar13 == pUStack0000001c)
				{
					UStack000001ec.ch = 0;
					UStack000000ec.ch = 0;
					iVar7 = STATLIST_UnitGetStatValue(pItem_00, 0x47, 0);
					iVar12 = *piVar13;
					if ((iVar12 == 8) || (iVar12 == 9))
					{
						iVar7 = iVar7 >> 8;
					}
					if ((iVar12 == 6) || (iVar12 == 7))
					{
						iVar7 = iVar7 >> 8;
					}
					if ((iVar12 == 10) || (iVar12 == 0xb))
					{
						iVar7 = iVar7 >> 8;
					}
					a2 = nullptr;
					if (iVar7 < 1)
					{
						if (iVar7 < 0)
						{
							index = *(short*)((int)piVar13 + 10);
							goto LAB_6faf1b0d;
						}
					}
					else
					{
						index = (short)piVar13[2];
					LAB_6faf1b0d:
						a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
					}
					if (iVar7 != 0)
					{
						memset(stack0x00000024, 0, 2 * (10));
						SStrPrintf((char*)(stack0x00000038), 10, "%i");
						Unicode::toUnicode((Unicode*)stack0x00000024, (const char*)(stack0x00000038), 9);
						D2_ASSERT(piVar13[1] == 1);
						if (iVar7 < 1)
						{
							Unicode::strcpy((Unicode*)(stack0x000000ec), (Unicode*)stack0x00000024);
						}
						else
						{
							Unicode::strcpy((Unicode*)(stack0x000000ec), pUVar6);
							Unicode::strcat((Unicode*)(stack0x000000ec), (Unicode*)stack0x00000024);
						}
						D2_ASSERT(piVar13[3] == 2);
						Unicode::strcpy((Unicode*)(stack0x000001ec), a2);
						Unicode::strcat((Unicode*)(stack0x000001ec), pUVar5);
						Unicode::strcat((Unicode*)(stack0x000001ec), (const Unicode*)(stack0x000000ec));
						Unicode::strcat((Unicode*)(stack0x000001ec), pUVar4);
						Unicode::strcat(a1, (const Unicode*)(stack0x000001ec));
					}
				}
				a22 = a22 + 1;
				piVar13 = piVar13 + 4;
				if (dword_6FB7A4A0 <= a22)
				{
					return;
				}
			} while (true);
		}
	}
	else
	{
		pDVar8 = STATLIST_GetStatListFromUnitStateAndFlag(pItem_00, in_stack_000014f0, in_stack_000014f8);
		if (pDVar8 != nullptr)
		{
			if (pItem_00 == nullptr)
			{
				uVar3 = 0xffffffff;
				nUnitType = 6;
				pMemPool = nullptr;
			}
			else
			{
				uVar3 = pItem_00->dwUnitId;
				nUnitType = pItem_00->dwUnitType;
				pMemPool = pItem_00->pMemoryPool;
			}
			pStatListEx = (D2StatListExStrc*)STATLIST_AllocStatList(pMemPool, 0, 0, nUnitType, uVar3);
			STATLIST_MergeBaseStats((D2StatListStrc*)pStatListEx, pDVar8);
			if ((in_stack_000014f4 != 0) &&
			    (pDVar8 = STATLIST_GetStatListFromUnitStateAndFlag(pItem_00, in_stack_000014f4, in_stack_000014f8),
			        pDVar8 != nullptr))
			{
				STATLIST_MergeBaseStats((D2StatListStrc*)pStatListEx, pDVar8);
			}
			if (((pItem_00 != nullptr) && (pItem_00->dwUnitType == 4)) &&
			    (pItem_00->pInventory != nullptr))
			{
				pItem = INVENTORY_GetFirstItem(pItem_00->pInventory);
				while ((pItem != nullptr &&
				        (pUnit = INVENTORY_UnitIsItem(pItem), pUnit != nullptr)))
				{
					pItem = INVENTORY_GetNextItem(pItem);
					pDVar8 = STATLIST_GetStatListFromUnitStateAndFlag(pUnit, in_stack_000014f0, in_stack_000014f8);
					if (pDVar8 != nullptr)
					{
						STATLIST_MergeBaseStats((D2StatListStrc*)pStatListEx, pDVar8);
					}
				}
			}
			pUStack0000001c = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0c));
			if (((in_stack_000014ec != 0) && (iVar12 = ITEMS_CheckItemTypeId(pItem_00, 0x39), iVar12 != 0)) && (iVar12 = STATLIST_UnitGetItemStatOrSkillStatValue(pItem_00, 0x7a, 0), iVar12 == 0))
			{
				sub_6FAF12C0(pItem_00, (Unicode*)(stack0x000003ec), 0x80);
				Unicode::strcat(a1, (Unicode*)stack0x000003ec);
			}
			puVar14 = (uint32_t*)(stack0x00000044);
			for (iVar12 = 0x2a; iVar12 != 0; iVar12 = iVar12 + -1)
			{
				*puVar14 = 0;
				puVar14 = puVar14 + 1;
			}
			iVar12 = 0;
			if (0 < dword_6FB7A438)
			{
				a12 = (int*)(&dword_6FB79B48);
				do
				{
					iVar7 = *a12;
					switch (iVar7)
					{
					case 0x11:
						in_stack_00000060 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x12:
						in_stack_0000005c = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x15:
						in_stack_00000044 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						if (in_stack_00000044 == 0)
						{
							in_stack_00000044 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, 0x17, 0);
						}
						break;
					case 0x16:
						in_stack_00000048 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						if (in_stack_00000048 == 0)
						{
							in_stack_00000048 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, 0x18, 0);
						}
						break;
					case 0x30:
						in_stack_000000a4 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x31:
						in_stack_000000a8 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x32:
						in_stack_0000008c = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x33:
						in_stack_00000090 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x34:
						in_stack_000000d4 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x35:
						in_stack_000000d8 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x36:
						in_stack_00000074 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x37:
						in_stack_00000078 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x39:
						in_stack_000000bc = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x3a:
						in_stack_000000c0 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						break;
					case 0x3b:
						in_stack_000000c4 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar7, 0);
						in_stack_000000c8 = STATLIST_UnitGetStatValue(pItem_00, 0x146, 0);
					}
					iVar12 = iVar12 + 1;
					a12 = a12 + 4;
				} while (iVar12 < dword_6FB7A438);
			}
			piVar13 = (int*)(stack0x00000048);
			iVar12 = 7;
			do
			{
				if ((0 < piVar13[-1]) && (0 < *piVar13))
				{
					piVar13[3] = 1;
				}
				piVar13 = piVar13 + 6;
				iVar12 = iVar12 + -1;
			} while (iVar12 != 0);
			bVar2 = false;
			a3 = 0;
			if (0 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbdc))
			{
				do
				{
					iVar12 = (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd8) + a3 * 2);
					if ((-1 < iVar12) && (iVar12 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4)))
					{
						iVar7 = D2COMMON_11269_CopyStats(pStatListEx, iVar12, (D2StatStrc*)stack0x000004ec, 0x1ff);
						a12 = nullptr;
						if (0 < iVar7)
						{
							do
							{
								iVar10 = *(int*)(stack0x000004f0 + (int)a12 * 8);
								uVar1 = *(uint16_t*)(stack0x000004ec + (int)a12 * 8);
								if (((iVar10 != 0) && (iVar9 = sub_6FAF3460((int*)(stack0x00000044), iVar12, a1), iVar9 == 0)) && (iVar10 = sub_6FAF21C0((Unicode*)pItem_00, (D2StatListStrc*)pStatListEx,
								                                                                                                       iVar12, (uint32_t)uVar1, iVar10, (char*)(stack0x000002ec)),
								                                                                                                      iVar10 != 0))
								{
									if (iVar12 == 0x17)
									{
										iVar10 = 0x15;
									LAB_6faf200b:
										iVar10 = STATLIST_GetStatValue((D2StatListStrc*)pStatListEx, iVar10, 0);
										if (iVar10 != 0)
											goto LAB_6faf206c;
									}
									else if (iVar12 == 0x18)
									{
										iVar10 = 0x16;
										goto LAB_6faf200b;
									}
									if (in_stack_000014fc != 0)
									{
										Unicode::strcat((Unicode*)stack0x000002ec, pUStack0000001c);
									}
									if ((bVar2) && (in_stack_000014fc == 0))
									{
										Unicode::strcat(a1, pUVar5);
										Unicode::strcat(a1, pUVar4);
									}
									bVar2 = true;
									Unicode::strcat(a1, (Unicode*)stack0x000002ec);
								}
							LAB_6faf206c:
								a12 = (int*)((int)a12 + 1);
							} while ((int)a12 < iVar7);
						}
					}
					a3 = a3 + 1;
				} while (a3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbdc));
			}
			if (((pItem_00 != nullptr) && (pItem_00->dwUnitType == 4)) &&
			    ((pDVar11 = DATATBLS_GetItemsTxtRecord(pItem_00->dwClassId), pDVar11->nNoDurability == 0 &&
			                                                                     (((pDVar11->nDurability != 0 &&
			                                                                           (iVar12 = STATLIST_UnitGetStatValue(pItem_00, 0x98, 0), iVar12 < 1)) &&
			                                                                         (iVar12 = STATLIST_GetMaxDurabilityFromUnit(pItem_00), iVar12 == 0))))))
			{
				pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x52f8));
				if ((bVar2) && (in_stack_000014fc == 0))
				{
					Unicode::strcat(a1, pUVar5);
					Unicode::strcat(a1, pUVar4);
				}
				Unicode::strcat(a1, pUVar6);
				if (in_stack_000014fc != 0)
				{
					Unicode::strcat(a1, pUStack0000001c);
				}
			}
			STATLIST_FreeStatList((D2StatListStrc*)pStatListEx);
		}
	}
}

//D2Client.0x6FAF21C0
uint32_t __fastcall sub_6FAF21C0(Unicode* pUnicode, D2StatListStrc* pStatList, int a3, uint32_t a4, int a5, char* a6)
{
	bool bVar1;
	short sVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int iVar6;
	Unicode* pUVar7;
	Unicode* pUVar8;
	Unicode* pUVar9;
	Unicode* a2;
	int iVar10;
	int iVar11;
	uint32_t uVar12;
	D2StatListStrc* pDVar13;
	D2StatListStrc* pDVar14;
	code* pcVar15;
	uint32_t uVar16;
	uint16_t uVar17;
	Unicode* local_24c;
	D2UnitStrc* local_248;
	Unicode* pUStack_244;
	D2StatListStrc* local_240;
	uint32_t local_23c;
	Unicode* pUStack_238;
	Unicode* pUStack_234;
	uint32_t local_230;
	int local_22c;
	Unicode aUStack_228[10];
	int iStack_214;
	Unicode aUStack_210[6];
	Unicode aUStack_204[2];
	D2UnitStrc aDStack_200[2];

	a6[0] = '\0';
	a6[1] = '\0';
	if (a3 < 0)
	{
		return 0;
	}
	local_22c = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4);
	if (local_22c <= a3)
	{
		return 0;
	}
	iVar11 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc);
	iVar10 = iVar11 + a3 * 0x144;
	if (iVar10 == 0)
	{
		return 0;
	}
	local_248 = (D2UnitStrc*)pUnicode;
	local_240 = pStatList;
	if ((*(uint8_t*)(iVar10 + 0x54) < 2) || (5 < *(uint8_t*)(iVar10 + 0x54)))
	{
	LAB_6faf2273:
		pDVar13 = (D2StatListStrc*)(a5 >> (*(uint8_t*)(iVar10 + 0x18) & 0x1f));
		if ((((a3 == 0x7a) && (local_248 != nullptr)) && (local_248->dwUnitType == 4)) &&
		    (iVar11 = ITEMS_CheckItemTypeId(local_248, 0x39), iVar11 != 0))
		{
			pDVar13 = (D2StatListStrc*)((int)&pDVar13->pNextLink + 2);
		}
	}
	else
	{
		uVar12 = (uint32_t) * (uint16_t*)(iVar10 + 0x56);
		if (((int)uVar12 < local_22c) && (iVar11 = iVar11 + uVar12 * 0x144, iVar11 != 0))
		{
			uVar17 = 0;
			pDVar4 = CUNIT_GetPlayer();
			iVar6 = STATLIST_UnitGetStatValue(pDVar4, uVar12, uVar17);
			a5 = (iVar6 >> (*(uint8_t*)(iVar11 + 0x18) & 0x1f)) * a5 >>
			     (*(uint8_t*)(iVar10 + 0x55) & 0x1f);
			goto LAB_6faf2273;
		}
		pDVar13 = nullptr;
	}
	local_230 = 1;
	if (*(short*)(iVar10 + 0x3e) == 0)
	{
	LAB_6faf22ba:
		bVar1 = false;
	}
	else
	{
		iVar11 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4);
		do
		{
			do
			{
				iVar11 = iVar11 + -1;
				if (iVar11 < 0)
				{
					bVar1 = true;
					if (local_230 == 0)
					{
						return 0;
					}
					goto LAB_6faf23e5;
				}
				if ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4) <= iVar11) ||
				    (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) + iVar11 * 0x144, iVar6 == 0))
					goto LAB_6faf22ba;
			} while (*(short*)(iVar10 + 0x3e) != *(short*)(iVar6 + 0x3e));
			local_230 = (uint32_t)(iVar11 == a3);
			iVar3 = STATLIST_GetStatValue(local_240, iVar11, 0);
			if ((*(uint8_t*)(iVar6 + 0x54) < 2) || (5 < *(uint8_t*)(iVar6 + 0x54)))
			{
			LAB_6faf238c:
				pDVar14 = (D2StatListStrc*)(iVar3 >> (*(uint8_t*)(iVar6 + 0x18) & 0x1f));
				if ((((iVar11 == 0x7a) && (local_248 != nullptr)) && (local_248->dwUnitType == 4)) && (iVar6 = ITEMS_CheckItemTypeId(local_248, 0x39), iVar6 != 0))
				{
					pDVar14 = (D2StatListStrc*)((int)&pDVar14->pNextLink + 2);
				}
			}
			else
			{
				uVar12 = (uint32_t) * (uint16_t*)(iVar6 + 0x56);
				if (((int)uVar12 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4)) &&
				    (local_22c = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) + uVar12 * 0x144,
				        local_22c != 0))
				{
					uVar17 = 0;
					pDVar4 = CUNIT_GetPlayer();
					iVar5 = STATLIST_UnitGetStatValue(pDVar4, uVar12, uVar17);
					iVar3 = (iVar5 >> (*(uint8_t*)(local_22c + 0x18) & 0x1f)) * iVar3 >>
					        (*(uint8_t*)(iVar6 + 0x55) & 0x1f);
					goto LAB_6faf238c;
				}
				pDVar14 = nullptr;
			}
		} while (pDVar13 == pDVar14);
		bVar1 = false;
	}
LAB_6faf23e5:
	local_230 = (uint32_t) * (uint8_t*)(iVar10 + 0x36);
	local_23c = (uint32_t) * (uint8_t*)(iVar10 + 0x37);
	local_22c = CONCAT22((*(uint16_t*)((uint8_t*)&local_22c + 2)), *(uint16_t*)(iVar10 + 0x3c));
	if (bVar1)
	{
		local_230 = (uint32_t) * (uint8_t*)(iVar10 + 0x40);
		local_23c = (uint32_t) * (uint8_t*)(iVar10 + 0x41);
		local_22c = CONCAT22((*(uint16_t*)((uint8_t*)&local_22c + 2)), *(uint16_t*)(iVar10 + 0x46));
		if ((int)pDVar13 < 0)
		{
			sVar2 = *(short*)(iVar10 + 0x44);
		}
		else
		{
			sVar2 = *(short*)(iVar10 + 0x42);
		}
	}
	else if ((int)pDVar13 < 0)
	{
		sVar2 = *(short*)(iVar10 + 0x3a);
	}
	else
	{
		sVar2 = *(short*)(iVar10 + 0x38);
	}
	pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
	SStrPrintf((char*)(aUStack_228 + 0xc), 10, "%i", pDVar13);
	pUVar8 = aUStack_228;
	pUStack_244 = (Unicode*)0xa;
	do
	{
		pUVar8 = pUVar8 + 1;
		pUStack_244 = (Unicode*)((int)pUStack_244 + -1);
	} while (pUStack_244 != nullptr);
	Unicode::toUnicode(aUStack_228, (char*)(aUStack_228 + 0xc), 9);
	pUStack_238 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa1));
	pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	pUStack_244 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa2));
	switch (local_230)
	{
	case 1:
	case 6:
	case 0xc:
		local_248 = (D2UnitStrc*)(aUStack_228 + 0x14);
		local_24c = (Unicode*)0x100;
		do
		{
			memset((Unicode*)local_248, 0, sizeof(Unicode));
			local_248 = (D2UnitStrc*)((int)&local_248->dwUnitType + 2);
			local_24c = (Unicode*)((int)local_24c + -1);
		} while (local_24c != nullptr);
		(*(uint16_t*)((uint8_t*)&aDStack_200[0].dwUnitType + 0)) = 0;
		if ((int)pDVar13 < 1)
		{
			Unicode::strcpy(aUStack_228 + 0x14, aUStack_228);
		}
		else if ((local_230 != 0xc) || (1 < (int)pDVar13))
		{
			Unicode::strcpy(aUStack_228 + 0x14, pUStack_244);
			Unicode::strcat(aUStack_228 + 0x14, aUStack_228);
		}
		if (local_23c == 1)
		{
			Unicode::strcpy((Unicode*)a6, aUStack_228 + 0x14);
			Unicode::strcat((Unicode*)a6, pUVar8);
		}
		else
		{
			if (local_23c != 2)
				goto LAB_6faf3065;
			Unicode::strcpy((Unicode*)a6, pUVar7);
			Unicode::strcat((Unicode*)a6, pUVar8);
			pUVar7 = aUStack_228 + 0x14;
		}
		break;
	case 2:
	case 7:
		goto joined_r0x6faf26d7;
	case 3:
	case 9:
		if (local_23c == 1)
		{
			Unicode::strcpy((Unicode*)a6, aUStack_228);
			Unicode::strcat((Unicode*)a6, pUVar8);
			break;
		}
		if (local_23c == 2)
		{
			Unicode::strcpy((Unicode*)a6, pUVar7);
			Unicode::strcat((Unicode*)a6, pUVar8);
			pUVar7 = aUStack_228;
			break;
		}
		goto LAB_6faf2724;
	case 4:
	case 8:
		pDVar14 = pDVar13;
		if (local_23c == 1)
		{
			if ((int)pDVar13 < 0)
			{
			LAB_6faf25b1:
				a6[0] = '\0';
				a6[1] = '\0';
				Unicode::strcat((Unicode*)a6, aUStack_228);
			}
			else
			{
				Unicode::strcpy((Unicode*)a6, pUStack_244);
				Unicode::strcat((Unicode*)a6, aUStack_228);
			}
			goto LAB_6faf26e3;
		}
	LAB_6faf2612:
		if (local_23c != 2)
			goto LAB_6faf2724;
		Unicode::strcpy((Unicode*)a6, pUVar7);
		Unicode::strcat((Unicode*)a6, pUVar8);
		pUVar7 = pUStack_244;
		if (-1 < (int)pDVar14)
			goto LAB_6faf270f;
		goto LAB_6faf2713;
	case 5:
	case 10:
		SStrPrintf((char*)(aUStack_228 + 0xc), 10, "%i",
		    (int)((int)pDVar13 * 100 + ((int)pDVar13 * 100 >> 0x1f & 0x7fU)) >> 7);
		Unicode::toUnicode(aUStack_228, (char*)(aUStack_228 + 0xc), 9);
	joined_r0x6faf26d7:
		if (local_23c == 1)
		{
			Unicode::strcpy((Unicode*)a6, aUStack_228);
		LAB_6faf26e3:
			Unicode::strcat((Unicode*)a6, pUStack_238);
			Unicode::strcat((Unicode*)a6, pUVar8);
		}
		else
		{
			if (local_23c != 2)
			{
			LAB_6faf2724:
				Unicode::strcpy((Unicode*)a6, pUVar7);
				goto LAB_6faf3065;
			}
			Unicode::strcpy((Unicode*)a6, pUVar7);
			pUVar7 = pUVar8;
		LAB_6faf270f:
			Unicode::strcat((Unicode*)a6, pUVar7);
		LAB_6faf2713:
			Unicode::strcat((Unicode*)a6, aUStack_228);
			pUVar7 = pUStack_238;
		}
		break;
	case 0xb:
		if ((int)pDVar13 < 1)
		{
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x52f9));
			uVar16 = 0x19;
		}
		else
		{
			iVar10 = (int)(0x9c4 / (int64_t)(int)pDVar13);
			if (0x1e < iVar10)
			{
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x52fa));
				Unicode::sprintf(0x80, (Unicode*)a6, pUVar7, 1, (iVar10 + 0xc) / 0x19);
				goto LAB_6faf3065;
			}
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x52f9));
			uVar16 = 1;
		}
		Unicode::sprintf(0x80, (Unicode*)a6, pUVar7, uVar16);
		goto LAB_6faf3065;
	case 0xd:
		pUVar7 = aUStack_228 + 0x14;
		local_24c = (Unicode*)0x100;
		do
		{
			pcVar15 = (code*)(((uint8_t*)&Unicode::strcpy));
			pUVar7 = pUVar7 + 1;
			local_24c = (Unicode*)((int)local_24c + -1);
		} while (local_24c != nullptr);
		(*(uint16_t*)((uint8_t*)&aDStack_200[0].dwUnitType + 0)) = 0;
		if ((int)pDVar13 < 1)
		{
			if (-1 < (int)pDVar13)
			{
				return 0;
			}
			Unicode::strcpy(aUStack_228 + 0x14, aUStack_228);
		}
		else
		{
			Unicode::strcpy(aUStack_228 + 0x14, pUStack_244);
			Unicode::strcat(aUStack_228 + 0x14, aUStack_228);
		}
		if ((int)a4 < 0)
		{
			return 0;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8) <= (int)a4)
		{
			return 0;
		}
		iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + a4 * 0xc4;
		if (iVar10 == 0)
		{
			return 0;
		}
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar10 + 0x52)));
		goto LAB_6faf2e16;
	case 0xe:
		iVar10 = (int)a4 >> 3;
		if (iVar10 < 0)
		{
			return 0;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8) <= iVar10)
		{
			return 0;
		}
		iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + iVar10 * 0xc4;
		if (iVar10 == 0)
		{
			return 0;
		}
		if (2 < (a4 & 7))
		{
			return 0;
		}
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar10 + 0x54 + (a4 & 7) * 2)));
		Unicode::sprintf(0x100, (Unicode*)a6, pUVar7, pDVar13);
		Unicode::strcat((Unicode*)a6, pUVar8);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar10 + 0x5a)));
		break;
	case 0xf:
		iVar11 = *(int*)((uint8_t*)&sgptDataTables);
		iVar6 = (int)a4 >> ((uint8_t) * (uint32_t*)(iVar11 + 0xc6c) & 0x1f);
		uVar12 = *(uint32_t*)(iVar11 + 0xc70) & a4;
		if (iVar6 < 1)
		{
			return 0;
		}
		if (*(int*)(iVar11 + 0xba0) <= iVar6)
		{
			return 0;
		}
		sVar2 = sub_6FB0A440(iVar6, 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
		uVar16 = 0;
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar10 + 0x38)));
		Unicode::sprintf(0x100, (Unicode*)a6, pUVar9, pDVar13, uVar16, uVar12, pUVar7);
		goto LAB_6faf3065;
	case 0x10:
		sVar2 = sub_6FB0A440(a4, 0);
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
		if (pUVar9 == nullptr)
		{
			return 0;
		}
		Unicode::sprintf(0x100, (Unicode*)a6, pUVar7, pDVar13, pUVar9);
		goto LAB_6faf3065;
	case 0x11:
	case 0x12:
		local_24c = aUStack_228 + 0x14;
		iStack_214 = 0x100;
		do
		{
			local_24c = local_24c + 1;
			iStack_214 = iStack_214 + -1;
		} while (iStack_214 != 0);
		(*(uint16_t*)((uint8_t*)&aDStack_200[0].dwUnitType + 0)) = 0;
		local_248 = nullptr;
		local_240 = nullptr;
		if (ghAct != nullptr)
		{
			local_248 = (D2UnitStrc*)ENVIRONMENT_GetPeriodOfDayFromAct(ghAct, (int*)&local_240);
		}
		local_24c = (Unicode*)
		    ITEMMODS_GetByTimeAdjustment((int)pDVar13, (int)local_248, (int)local_240, (int*)&local_248,
		        (int*)&pUStack_234, (int*)(aUStack_228 + 0x12));
		if (ghAct == nullptr)
		{
			local_24c = pUStack_234;
		}
		if ((int)local_248 < 1)
		{
			local_248 = nullptr;
		}
		else if (2 < (int)local_248)
		{
			local_248 = (D2UnitStrc*)0x3;
		}
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(word_6FB6FA30[(int)local_248]));
		Unicode::strcat((Unicode*)a6, pUVar9);
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)a6, pUVar9);
		SStrPrintf((char*)(aUStack_228 + 0xc), 10, "%i", local_24c);
		Unicode::toUnicode(aUStack_228, (char*)(aUStack_228 + 0xc), 9);
		if ((int)local_24c < 0)
		{
			if ((int)pDVar13 < 0)
			{
				Unicode::strcpy(aUStack_228 + 0x14, aUStack_228);
			}
		}
		else
		{
			Unicode::strcpy(aUStack_228 + 0x14, pUStack_244);
			Unicode::strcat(aUStack_228 + 0x14, aUStack_228);
		}
		if (local_230 == 0x12)
		{
			Unicode::strcat(aUStack_228 + 0x14, pUStack_238);
		}
		if (local_23c == 1)
		{
			Unicode::strcat((Unicode*)a6, aUStack_228 + 0x14);
			Unicode::strcat((Unicode*)a6, pUVar8);
		}
		else
		{
			if (local_23c != 2)
				goto LAB_6faf3065;
			Unicode::strcat((Unicode*)a6, pUVar7);
			Unicode::strcat((Unicode*)a6, pUVar8);
			pUVar7 = aUStack_228 + 0x14;
		}
		break;
	case 0x13:
		Unicode::sprintf(0x100, (Unicode*)a6, pUVar7, pDVar13);
		goto LAB_6faf3065;
	case 0x14:
	case 0x15:
		pDVar14 = (D2StatListStrc*)-(int)pDVar13;
		SStrPrintf((char*)(aUStack_228 + 0xc), 10, "%i", pDVar14);
		Unicode::toUnicode(aUStack_228, (char*)(aUStack_228 + 0xc), 9);
		if (local_23c != 1)
			goto LAB_6faf2612;
		if (0 < (int)pDVar13)
			goto LAB_6faf25b1;
		Unicode::strcpy((Unicode*)a6, pUStack_244);
		Unicode::strcat((Unicode*)a6, aUStack_228);
		goto LAB_6faf26e3;
	case 0x16:
		if (local_23c == 1)
		{
			if ((int)pDVar13 < 0)
			{
				a6[0] = '\0';
				a6[1] = '\0';
			}
			else
			{
				Unicode::strcpy((Unicode*)a6, pUStack_244);
			}
			Unicode::strcat((Unicode*)a6, aUStack_228);
			Unicode::strcat((Unicode*)a6, pUStack_238);
			Unicode::strcat((Unicode*)a6, pUVar8);
			Unicode::strcat((Unicode*)a6, pUVar7);
		}
		else if (local_23c == 2)
		{
			Unicode::strcpy((Unicode*)a6, pUVar7);
			Unicode::strcat((Unicode*)a6, pUVar8);
			if (-1 < (int)pDVar13)
			{
				Unicode::strcat((Unicode*)a6, pUStack_244);
			}
			Unicode::strcat((Unicode*)a6, aUStack_228);
			Unicode::strcat((Unicode*)a6, pUStack_238);
		}
		else
		{
			Unicode::strcpy((Unicode*)a6, pUVar7);
		}
		if (((int)a4 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc34) <= (int)a4))
		{
			iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc3c);
		}
		else
		{
			iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc3c) + a4 * 0xc;
		}
		if (iVar10 == 0)
			goto LAB_6faf3065;
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat((Unicode*)a6, pUVar7);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat((Unicode*)a6, pUVar7);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar10 + 10)));
		break;
	case 0x17:
		if ((int)a4 < 0)
		{
			return 0;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= (int)a4)
		{
			return 0;
		}
		iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + a4 * 0x1a8;
		if (iVar10 == 0)
		{
			return 0;
		}
		if (local_23c == 1)
		{
			Unicode::strcpy((Unicode*)a6, aUStack_228);
			Unicode::strcat((Unicode*)a6, pUStack_238);
			Unicode::strcat((Unicode*)a6, pUVar8);
			Unicode::strcat((Unicode*)a6, pUVar7);
		}
		else if (local_23c == 2)
		{
			Unicode::strcpy((Unicode*)a6, pUVar7);
			Unicode::strcat((Unicode*)a6, pUVar8);
			Unicode::strcat((Unicode*)a6, aUStack_228);
			Unicode::strcat((Unicode*)a6, pUStack_238);
		}
		else
		{
			Unicode::strcpy((Unicode*)a6, pUVar7);
		}
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat((Unicode*)a6, pUVar7);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar10 + 6)));
		break;
	case 0x18:
		pUStack_234 = (Unicode*)(*(uint32_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc70) & a4);
		iStack_214 = (int)pDVar13 >> 8;
		local_248 = (D2UnitStrc*)((uint32_t)pDVar13 & 0xff);
		sVar2 = sub_6FB0A440((int)a4 >>
		                         ((uint8_t) * (uint32_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc6c) & 0x1f),
		    0);
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
		if (pUVar9 == nullptr)
			goto LAB_6faf3065;
		local_24c = aUStack_228 + 0x14;
		local_240 = (D2StatListStrc*)0x100;
		do
		{
			local_24c = local_24c + 1;
			local_240 = (D2StatListStrc*)((int)&local_240[-1].fpStatRemove + 3);
		} while (local_240 != nullptr);
		(*(uint16_t*)((uint8_t*)&aDStack_200[0].dwUnitType + 0)) = 0;
		a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x5301));
		Unicode::strcat((Unicode*)a6, a2);
		Unicode::strcat((Unicode*)a6, pUVar8);
		SStrPrintf((char*)(aUStack_228 + 0xc), 10, "%i", pUStack_234);
		Unicode::toUnicode(aUStack_228, (char*)(aUStack_228 + 0xc), 9);
		Unicode::strcat((Unicode*)a6, aUStack_228);
		Unicode::strcat((Unicode*)a6, pUVar8);
		Unicode::strcat((Unicode*)a6, pUVar9);
		Unicode::strcat((Unicode*)a6, pUVar8);
		Unicode::sprintf(0x80, aUStack_228 + 0x14, pUVar7, local_248, iStack_214);
		pUVar7 = aUStack_228 + 0x14;
		break;
	case 0x19:
	case 0x1a:
		local_24c = aUStack_228 + 0x14;
		local_240 = (D2StatListStrc*)0x100;
		do
		{
			pcVar15 = (code*)(((uint8_t*)&Unicode::strcpy));
			local_24c = local_24c + 1;
			local_240 = (D2StatListStrc*)((int)&local_240[-1].fpStatRemove + 3);
		} while (local_240 != nullptr);
		(*(uint16_t*)((uint8_t*)&aDStack_200[0].dwUnitType + 0)) = 0;
		if ((int)pDVar13 < 0)
		{
			Unicode::strcpy(aUStack_228 + 0x14, pUStack_244);
			Unicode::strcat(aUStack_228 + 0x14, aUStack_228);
		}
		else
		{
			Unicode::strcpy(aUStack_228 + 0x14, aUStack_228);
		}
	LAB_6faf2e16:
		if (local_23c == 1)
		{
			(*pcVar15)();
			Unicode::strcat((Unicode*)a6, pUVar8);
		}
		else
		{
			if (local_23c != 2)
				goto LAB_6faf3065;
			(*pcVar15)();
			Unicode::strcat((Unicode*)a6, pUVar8);
			pUVar7 = aUStack_228 + 0x14;
		}
		break;
	case 0x1b:
		pUStack_234 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa3));
		if ((pUStack_234 == nullptr) || (pDVar13 == nullptr))
			goto LAB_6faf3065;
		sVar2 = sub_6FB0A440(a4, 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
		if (pUVar7 == nullptr)
			goto LAB_6faf3065;
		if ((int)pDVar13 < 1)
		{
			Unicode::strcpy((Unicode*)a6, aUStack_228);
		}
		else
		{
			Unicode::strcat((Unicode*)a6, pUStack_244);
			Unicode::strcat((Unicode*)a6, aUStack_228);
		}
		Unicode::strcat((Unicode*)a6, pUVar8);
		Unicode::strcat((Unicode*)a6, pUStack_234);
		Unicode::strcat((Unicode*)a6, pUVar8);
		Unicode::strcat((Unicode*)a6, pUVar7);
		Unicode::strcat((Unicode*)a6, pUVar8);
		local_240 = (D2StatListStrc*)0x7;
		iVar10 = SKILLS_IsPlayerClassSkill(a4, (int*)&local_240);
		if ((((iVar10 == 0) || ((int)local_240 < 0)) || (6 < (int)local_240)) ||
		    ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8) <= (int)local_240 ||
		        (iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + (int)local_240 * 0xc4,
		            iVar10 == 0))))
			goto LAB_6faf3065;
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar10 + 0x5a)));
		break;
	case 0x1c:
		local_240 = pDVar13;
		if (((pDVar13 == nullptr) || ((int)a4 < 0)) ||
		    ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= (int)a4 ||
		        (pUStack_234 = (Unicode*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a4 * 0x23c), pUStack_234 == nullptr))))
			goto LAB_6faf3065;
		if ((local_248 == nullptr) || (pDVar4 = local_248, local_248->dwUnitType != 0))
		{
			pDVar4 = CUNIT_GetPlayer();
		}
		if (pDVar4 == nullptr)
		{
			iVar10 = -1;
		}
		else
		{
			iVar10 = pDVar4->dwClassId;
		}
		if (((char)pUStack_234[6].ch == iVar10) && (3 < (int)pDVar13))
		{
			local_240 = (D2StatListStrc*)0x3;
		}
		pUStack_234 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa3));
		if (pUStack_234 == nullptr)
			goto LAB_6faf3065;
		sVar2 = sub_6FB0A440(a4, 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
		pDVar13 = local_240;
		if (pUVar7 == nullptr)
			goto LAB_6faf3065;
		SStrPrintf((char*)(aUStack_228 + 0xc), 10, "%i", local_240);
		Unicode::toUnicode(aUStack_228, (char*)(aUStack_228 + 0xc), 9);
		if ((int)pDVar13 < 1)
		{
			Unicode::strcpy((Unicode*)a6, aUStack_228);
		}
		else
		{
			Unicode::strcpy((Unicode*)a6, pUStack_244);
			Unicode::strcat((Unicode*)a6, aUStack_228);
		}
		Unicode::strcat((Unicode*)a6, pUVar8);
		Unicode::strcat((Unicode*)a6, pUStack_234);
		Unicode::strcat((Unicode*)a6, pUVar8);
		break;
	default:
		return 0;
	}
	Unicode::strcat((Unicode*)a6, pUVar7);
LAB_6faf3065:
	if ((5 < (int)local_230) && (((int)local_230 < 0xb || (local_230 == 0x15))))
	{
		sVar2 = (short)local_22c;
		if (sVar2 != 0x1506)
		{
			Unicode::strcat((Unicode*)a6, pUVar8);
			pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
			Unicode::strcat((Unicode*)a6, pUVar8);
			return 1;
		}
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b53));
		Unicode::strcat((Unicode*)a6, pUVar8);
		Unicode::strcat((Unicode*)a6, pUVar7);
	}
	return 1;
}

//D2Client.0x6FAF3160
void __fastcall sub_6FAF3160(D2UnitStrc* pUnit, Unicode* pUnicode, uint32_t a3, uint32_t a4, int a5)
{
	Unicode* pUVar1;
	Unicode* a2;
	int iVar2;
	uint32_t uStack_804;
	Unicode local_800[1024];

	local_800[0].ch = 0;
	sub_6FAF19C0((int*)(0x400), 1, 0, 0xab, 0x40, a4);
	if (a5 == 0)
	{
		Unicode::strcat(pUnicode, local_800);
		return;
	}
	uStack_804 = Unicode::strlen(local_800);
	if (uStack_804 == 0)
	{
		Unicode::strcat(pUnicode, local_800);
		return;
	}
	iVar2 = uStack_804 + -2;
	do
	{
		if (iVar2 < 1)
		{
		LAB_6faf3217:
			Unicode::strcat(pUnicode, (Unicode*)a5);
			Unicode::strcat(pUnicode, local_800);
			return;
		}
		if (local_800[iVar2].ch == 10)
		{
			if (0 < iVar2)
			{
				pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
				a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0c));
				local_800[iVar2].ch = 0;
				Unicode::strcat(pUnicode, local_800);
				Unicode::strcat(pUnicode, pUVar1);
				Unicode::strcat(pUnicode, (Unicode*)a5);
				if (*(short*)((int)&uStack_804 + uStack_804 * 2 + 2) == 10)
				{
					*(uint16_t*)((int)&uStack_804 + uStack_804 * 2 + 2) = 0;
				}
				Unicode::strcat(pUnicode, local_800 + iVar2 + 1);
				Unicode::strcat(pUnicode, a2);
				Unicode::strcat(pUnicode, pUVar1);
				return;
			}
			goto LAB_6faf3217;
		}
		iVar2 = iVar2 + -1;
	} while (true);
}

//D2Client.0x6FAF32B0
void __fastcall sub_6FAF32B0(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, uint32_t a3, uint32_t a4)
{
	int iVar1;
	D2SetItemsTxt* pDVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;

	if ((((pUnit2 != nullptr) && (pUnit2->dwUnitType == 4)) &&
	        (iVar1 = ITEMS_GetItemQuality(pUnit2), iVar1 == 5)) &&
	    (pDVar2 = ITEMS_GetSetItemsTxtRecordFromItem(pUnit2), pDVar2 != nullptr))
	{
		if (pDVar2->nAddFunc == 1)
		{
			uVar3 = ITEMS_GetSetItemsMask(pUnit, pUnit2, 0);
			iVar1 = ITEMS_GetNoOfSetItemsFromItem(pUnit2);
			iVar5 = 0;
			do
			{
				iVar4 = iVar5 * 4;
				if (iVar5 != iVar1)
				{
					if (iVar1 < iVar5)
					{
						iVar4 = iVar4 + -4;
					}
					if ((uVar3 & 1 << ((uint8_t)iVar5 & 0x1f)) != 0)
					{
						sub_6FAF19C0((int*)(a4), 0, *(uint32_t*)((int)&dword_6FB6FA38 + iVar4), 0, 0, 1);
					}
				}
				iVar5 = iVar5 + 1;
			} while (iVar5 < 6);
		}
		else if (pDVar2->nAddFunc == 2)
		{
			uVar3 = ITEMS_GetSetItemsMask(pUnit, pUnit2, 1);
			if (uVar3 < 0x40)
			{
				iVar1 = *(int*)(byte_6FB6FA50 + uVar3 * 4);
			}
			else
			{
				iVar1 = 0;
			}
			iVar5 = 0;
			if (0 < iVar1 + -1)
			{
				do
				{
					sub_6FAF19C0((int*)(a4), 0, (&dword_6FB6FA38)[iVar5], 0, 0, 1);
					iVar5 = iVar5 + 1;
				} while (iVar5 < iVar1 + -1);
				return;
			}
		}
	}
}

//D2Client.0x6FAF33C0
void __fastcall sub_6FAF33C0(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, uint32_t a3, uint32_t a4)
{
	int iVar1;
	D2StatListStrc* pStatList;
	int iVar2;
	int iVar3;

	iVar1 = ITEMS_GetItemQuality(pUnit2);
	if ((((iVar1 == 5) && (iVar1 = ITEMS_GetFileIndex(pUnit2), -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc1c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc18) + iVar1 * 0x1b8, iVar1 != 0))
	{
		iVar3 = 0;
		while ((pStatList = STATLIST_GetStatListFromUnitAndState(pUnit, (&dword_6FB6FA38)[iVar3]),
		    pStatList == nullptr ||
		        (iVar2 = STATLIST_GetStatValue(pStatList, 0x47, 0), *(short*)(iVar1 + 0x2c) != iVar2)))
		{
			iVar3 = iVar3 + 1;
			if (5 < iVar3)
			{
				return;
			}
		}
		sub_6FAF19C0((int*)(a4), 0, (&dword_6FB6FA38)[iVar3], 0, 0, 1);
		return;
	}
}

//D2Client.0x6FAF3460
int __fastcall sub_6FAF3460(int* a1, uint32_t a22, Unicode* pUnicode)
{
	Unicode* pUVar1;
	Unicode* a2;
	Unicode* a2_00;
	Unicode* a2_01;
	short sVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	char acStack_220[12];
	Unicode aUStack_214[10];
	Unicode local_200[256];

	iVar4 = 0;
	pUVar1 = local_200;
	for (iVar3 = 0x80; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*(uint32_t*)pUVar1 = 0;
		pUVar1 = pUVar1 + 2;
	}
	switch (a22)
	{
	case 0x11:
		return a1[10];
	case 0x12:
		a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa1));
		a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		a2_01 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa2));
		SStrPrintf(acStack_220, 10, "%i", a1[6]);
		Unicode::toUnicode(aUStack_214, acStack_220, 9);
		if (a1[10] == 0)
		{
			return 0;
		}
		Unicode::strcpy(local_200, a2_01);
		Unicode::strcat(local_200, aUStack_214);
		Unicode::strcat(local_200, a2);
		Unicode::strcat(local_200, a2_00);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2727));
		Unicode::strcat(local_200, pUVar1);
		break;
	default:
		goto switchD_6faf34a8_caseD_13;
	case 0x15:
	case 0x16:
	case 0x17:
		if (a1[5] == 0)
		{
			if (a1[4] == 0)
			{
				return 0;
			}
			iVar3 = *a1;
			iVar4 = a1[1];
			if (iVar4 <= iVar3)
			{
				a1[5] = 0;
				a1[4] = 0;
				return 0;
			}
			a1[5] = 1;
			sVar2 = 0xe27;
		LAB_6faf3799:
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
			Unicode::sprintf(0x100, local_200, pUVar1, iVar3, iVar4);
		}
		break;
	case 0x18:
		if (a1[5] != 0)
		{
			return 1;
		}
		return a1[4];
	case 0x30:
		if (a1[0x1c] == 0)
		{
			return 0;
		}
		iVar3 = a1[0x18];
		iVar4 = a1[0x19];
		if (iVar3 < iVar4)
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe1d));
			Unicode::sprintf(0x100, local_200, pUVar1, iVar3, iVar4);
		}
		else
		{
			sVar2 = 0xe1c;
		LAB_6faf3628:
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
			Unicode::sprintf(0x100, local_200, pUVar1);
		}
		break;
	case 0x31:
		return a1[0x1c];
	case 0x32:
		if (a1[0x16] == 0)
		{
			return 0;
		}
		iVar3 = a1[0x12];
		iVar4 = a1[0x13];
		if (iVar3 < iVar4)
		{
			sVar2 = 0xe21;
		LAB_6faf36e8:
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
			Unicode::sprintf(0x100, local_200, pUVar1, iVar3, iVar4);
		}
		else
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe20));
			Unicode::sprintf(0x100, local_200, pUVar1);
		}
		break;
	case 0x33:
		return a1[0x16];
	case 0x34:
		if (a1[0x28] == 0)
		{
			return 0;
		}
		iVar3 = a1[0x24];
		iVar4 = a1[0x25];
		if (iVar4 <= iVar3)
		{
			sVar2 = 0xe22;
			goto LAB_6faf3628;
		}
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe23));
		Unicode::sprintf(0x100, local_200, pUVar1, iVar3, iVar4);
		break;
	case 0x35:
		return a1[0x28];
	case 0x36:
		if (a1[0x10] == 0)
		{
			return 0;
		}
		iVar3 = a1[0xc];
		iVar4 = a1[0xd];
		if (iVar3 < iVar4)
		{
			sVar2 = 0xe1f;
			goto LAB_6faf3799;
		}
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe1e));
		Unicode::sprintf(0x100, local_200, pUVar1, iVar4);
		break;
	case 0x37:
		return a1[0x10];
	case 0x39:
		if (a1[0x22] == 0)
		{
			return 0;
		}
		if (a1[0x21] < 1)
		{
			a1[0x21] = 1;
		}
		iVar3 = a1[0x20] / a1[0x21];
		a1[0x20] = iVar3;
		iVar4 = iVar3 / 0x19;
		iVar5 = a1[0x1e] * iVar3 + 0x80 >> 8;
		iVar3 = a1[0x1f] * iVar3 + 0x80 >> 8;
		a1[0x1e] = iVar5;
		a1[0x1f] = iVar3;
		if (iVar3 <= iVar5)
		{
			sVar2 = 0xe24;
			goto LAB_6faf36e8;
		}
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe25));
		Unicode::sprintf(0x100, local_200, pUVar1, iVar5, iVar3, iVar4);
		break;
	case 0x3a:
	case 0x3b:
		return a1[0x22];
	}
	iVar4 = 1;
	Unicode::strcat(pUnicode, local_200);
switchD_6faf34a8_caseD_13:
	return iVar4;
}

//D2Client.0x6FAF3910
void __cdecl sub_6FAF3910()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&byte_6FBB5BE5;
	iVar1 = 0x28;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FAF3930
D2UnitStrc* __cdecl sub_6FAF3930()
{
	D2UnitStrc* pDVar1;

	if (dword_6FBB5CF9 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
		return pDVar1;
	}
	return nullptr;
}

//D2Client.0x6FAF3950
int __cdecl sub_6FAF3950()
{
	return dword_6FBB5CFD;
}

//D2Client.0x6FAF3960
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAF3960()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
}

//D2Client.0x6FAF3AD0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAF3AD0()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
}

//D2Client.0x6FAF3C40
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF3C40()
{
	bool bVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t extraout_ECX;
	uint32_t* puVar5;

	if (dword_6FBB5CF9 == 0)
	{
	LAB_6faf3c66:
		byte_6FBB5C3B = 0;
		sub_6FAE8F10();
		uVar2 = dword_6FBB5CF5;
		pDVar3 = CUNIT_GetPlayer();
		if (pDVar3 != nullptr)
		{
			pDVar3 = CUNIT_GetPlayer();
			if (((pDVar3 != nullptr) && (pDVar3->dwUnitType == 0)) &&
			    (pDVar3->pPlayerData != nullptr))
			{
				pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
				pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
				pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
				pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
			}
		}
		sub_6FAF7950(uVar2);
		pDVar3 = sub_6FB269F0(uVar2, 1);
		if (pDVar3 != nullptr)
		{
			pDVar3->dwFlags = pDVar3->dwFlags | 2;
		}
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
		sub_6FB1E710();
		sub_6FAF3DC0(0);
		sub_6FB23260(8, 1, 0);
		if (pDVar3 != nullptr)
		{
			sub_6FAFB6E0((int*)pDVar3, 1, 0);
			sub_6FB4F410(pDVar3, (int*)0x1);
		}
		sub_6FB23260(8, 1, 0);
		return 0;
	}
	pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1);
	if (pDVar3 == nullptr)
		goto LAB_6faf3c66;
	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	iVar4 = 0;
	bVar1 = false;
	byte_6FBB5C3B = 1;
	if (0 < dword_6FB7BD6C)
	{
		puVar5 = dword_6FB7B978;
		do
		{
			if (bVar1)
				break;
			if (*puVar5 == dword_6FBB5CFD)
			{
				bVar1 = true;
			}
			else
			{
				iVar4 = iVar4 + 1;
				puVar5 = (uint32_t*)((int)puVar5 + 0x16);
			}
		} while (iVar4 < dword_6FB7BD6C);
		if (bVar1)
			goto LAB_6faf3d8e;
	}
	iVar4 = 0;
LAB_6faf3d8e:
	dword_6FBB5C4D = (int)dword_6FB7B978 + iVar4 * 0x16;
	sub_6FAF3DF0(iVar4);
	return 1;
}

//D2Client.0x6FAF3DC0
void __fastcall sub_6FAF3DC0(int a1)
{
	if (a1 != 0)
	{
		dword_6FBB5CF9 = 1;
		dword_6FBB5CF5 = *(uint32_t*)(a1 + 0xc);
		dword_6FBB5CFD = *(int*)(a1 + 4);
		return;
	}
	dword_6FBB5CF9 = 0;
}
