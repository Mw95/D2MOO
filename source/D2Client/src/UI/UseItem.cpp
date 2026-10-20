#include "UI/UseItem.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Engine/GfxUtil.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Select.h"
#include "Sound/SoundInst.h"
#include "UI/Dialog.h"
#include "UI/Inv.h"
#include "UI/Mods.h"
#include "UI/NpcMenu.h"
#include "UI/Restart.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"

//D2Client.0x6FB90676
uint32_t dword_6FB90676 = 0x9A;
//D2Client.0x6FB90682
uint32_t dword_6FB90682 = 0x10;
//D2Client.0x6FB90778
uint8_t byte_6FB90778;
//D2Client.0x6FB90779
uint8_t byte_6FB90779[4] = {1};
//D2Client.0x6FB9077D
uint8_t byte_6FB9077D[4] = {0x26};
//D2Client.0x6FB90781
uint8_t byte_6FB90781 = 0xFF;
//D2Client.0x6FB90782
uint8_t byte_6FB90782[46] = {0, 0, 0x28, 0, 0, 0, 0x4A, 0, 0, 0, 0xFF, 0, 0, 0x4B, 0, 0, 0, 0x66, 0, 0, 0, 0xFF, 0, 0, 0x67, 0, 0, 0, 0x6B, 0, 0, 0, 0xFF, 0, 0, 0x6D, 0, 0, 0, 0x84, 0, 0, 0, 0xFF};
//D2Client.0x6FB907B0
int32_t dword_6FB907B0 = 5;
//D2Client.0x6FB907B8
uint32_t dword_6FB907B8 = 0x11;
//D2Client.0x6FBBA978
int32_t dword_6FBBA978;
//D2Client.0x6FBBA988
uint32_t dword_6FBBA988;
//D2Client.0x6FBBA98C
int32_t dword_6FBBA98C;
//D2Client.0x6FBBA990
uint8_t byte_6FBBA990;
//D2Client.0x6FBBA9A4
char byte_6FBBA9A4;
//D2Client.0x6FBBA9A5
int32_t dword_6FBBA9A5;
//D2Client.0x6FBBA9A9
D2CellFileStrc* gpCellFile_6FBBA9A9;
//D2Client.0x6FBBA9AD
D2CellFileStrc* gpCellFile_6FBBA9AD;
//D2Client.0x6FBBA9B1
D2CellFileStrc* gpCellFile_6FBBA9B1;
//D2Client.0x6FBBA9B5
uint32_t dword_6FBBA9B5;
//D2Client.0x6FBBA9B9
D2WaypointDataStrc* gpWaypointData_6FBBA9B9;
//D2Client.0x6FBBA9BD
char byte_6FBBA9BD;
//D2Client.0x6FBBA9BE
int32_t dword_6FBBA9BE;
//D2Client.0x6FBBA9C2
int32_t dword_6FBBA9C2;
//D2Client.0x6FBBA9C6
int32_t dword_6FBBA9C6;
//D2Client.0x6FBBA9CC
uint32_t dword_6FBBA9CC;
//D2Client.0x6FBBA9D0
uint8_t byte_6FBBA9D0;
//D2Client.0x6FBBA9FD
uint8_t tbl_6FBBA9FD[3];

//D2Client.0x6FB24F80
void __fastcall sub_6FB24F80(int a1, int a2)
{
	uint8_t* puVar1;
	int iVar2;
	int iVar3;
	int* piVar4;

	iVar3 = dword_6FB906B0;
	if (0 < dword_6FB906B0)
	{
		puVar1 = &byte_6FB90686;
		iVar2 = dword_6FB906B0;
		do
		{
			puVar1[1] = 0;
			*puVar1 = 0;
			puVar1 = puVar1 + 0x28;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
	}
	iVar2 = 0;
	if (0 < iVar3)
	{
		piVar4 = (int*)(&dword_6FB90676);
		do
		{
			if ((((piVar4[-1] <= a1) && (a1 <= *piVar4)) && (piVar4[1] <= a2)) &&
			    (a2 <= piVar4[2]))
			{
				sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				iVar3 = dword_6FB906B0;
				*(uint8_t*)((int)piVar4 + 0x11) = 1;
				*(uint8_t*)(piVar4 + 4) = 1;
			}
			iVar2 = iVar2 + 1;
			piVar4 = piVar4 + 10;
		} while (iVar2 < iVar3);
	}
}

//D2Client.0x6FB25000
void __cdecl sub_6FB25000(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	uint16_t uVar2;
	DWORD DVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	D2ItemsTxt* pDVar6;
	float fVar7;
	float fVar8;
	int iVar9;

	uVar1 = (uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar2 = *(uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	DVar3 = GetTickCount();
	if (DVar3 - byte_6FBBA990 < 400)
	{
		return;
	}
	byte_6FBBA990 = GetTickCount();
	if (dword_6FBBA97C == 1)
	{
		iVar4 = sub_6FAEAE00(pSMSGHANDLER_PARAMS);
	LAB_6fb25066:
		if (iVar4 != 0)
		{
			return;
		}
		sub_6FB24F80((uint32_t)uVar1, (uint32_t)uVar2);
	}
	else if (dword_6FBBA97C == 2)
	{
		iVar4 = sub_6FAEAF40(pSMSGHANDLER_PARAMS);
		goto LAB_6fb25066;
	}
	pDVar5 = CUNIT_GetPlayer();
	if (pDVar5 == nullptr)
	{
		return;
	}
	pDVar5 = INVENTORY_GetCursorItem(pDVar5->pInventory);
	if (pDVar5 == nullptr)
	{
		return;
	}
	if (uVar1 < 0x7b)
	{
		return;
	}
	if (uVar1 != 0xd3 && 0xd2 < uVar1)
	{
		return;
	}
	if (uVar2 < 0x6a)
	{
		return;
	}
	if (uVar2 != 0xdc && 0xdb < uVar2)
	{
		return;
	}
	pDVar6 = DATATBLS_GetItemsTxtRecord(pDVar5->dwClassId);
	if (pDVar6 == nullptr)
	{
		return;
	}
	iVar4 = ITEMS_CheckItemFlag(pDVar5, 0x10, __LINE__, __FILE__);
	if (iVar4 != 0)
	{
		if (dword_6FBBA978 == 1)
		{
			iVar4 = sub_6FAF3950();
			if ((((iVar4 == 0x9a) && (iVar4 = ITEMS_IsImbueable(pDVar5), iVar4 != 0)) ||
			        ((iVar4 = sub_6FAF3950(), iVar4 == 0x1ff &&
			                                      (iVar4 = ITEMS_IsSocketable(pDVar5), iVar4 != 0)))) ||
			    ((iVar4 = sub_6FAF3950(), iVar4 == 0x200 &&
			                                  (iVar4 = ITEMS_IsPersonalizable(pDVar5), iVar4 != 0))))
			{
			LAB_6fb2515b:
				if (dword_6FBBA97C == 1)
				{
					dword_6FBBA97C = 2;
					sub_6FB575B0(nullptr);
					dword_6FBBA988 = pDVar5->dwUnitId;
					iVar9 = 0;
					fVar8 = 0.0;
					fVar7 = 0.0;
					iVar4 = sub_6FB2E590(pDVar5);
					sub_6FB55820(iVar4, nullptr, fVar7, fVar8, iVar9);
					return;
				}
				if (dword_6FBBA97C != 2)
				{
					return;
				}
				dword_6FBBA97C = 1;
				dword_6FBBA988 = 0;
				sub_6FB575B0(pDVar5);
				sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				return;
			}
		}
		else if ((dword_6FBBA978 == 0) && (pDVar6->dwCode == 0x20747368))
			goto LAB_6fb2515b;
	}
	sub_6FB55820(3, nullptr, 0.0, 0.0, 0);
}

//D2Client.0x6FB251E0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB251E0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_ECX;
	uint32_t uVar4;
	float fVar5;
	float fVar6;
	int iVar7;

	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	if (dword_6FBBA97C != 1)
	{
		if (dword_6FBBA97C != 2)
		{
			return;
		}
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			pDVar1 = nullptr;
		}
		else
		{
			pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		}
		sub_6FB575B0(pDVar1);
	}
	if (dword_6FBBA978 == 0)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar4 = 0xffffffff;
		}
		else
		{
			uVar4 = pDVar1->dwUnitId;
		}
		sub_6FAADAA0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x44), uVar4, dword_6FBBA984, 0, 2);
	}
	else
	{
		sub_6FAF3AD0();
	}
	dword_6FBBA97C = 0;
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 == nullptr)
	{
		pDVar1 = nullptr;
	}
	else
	{
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
	}
	if (dword_6FBBA97C == 1)
	{
		dword_6FBBA97C = 2;
		sub_6FB575B0(nullptr);
		if (pDVar1 == nullptr)
			goto LAB_6fb252da;
		dword_6FBBA988 = pDVar1->dwUnitId;
		iVar7 = 0;
		fVar6 = 0.0;
		fVar5 = 0.0;
		iVar2 = sub_6FB2E590(pDVar1);
	}
	else
	{
		if (dword_6FBBA97C != 2)
			goto LAB_6fb252da;
		dword_6FBBA97C = 1;
		dword_6FBBA988 = 0;
		if (pDVar1 != nullptr)
		{
			sub_6FB575B0(pDVar1);
		}
		iVar7 = 0;
		fVar6 = 0.0;
		fVar5 = 0.0;
		iVar2 = 1;
	}
	sub_6FB55820(iVar2, nullptr, fVar5, fVar6, iVar7);
LAB_6fb252da:
	uVar4 = 8;
	pHVar3 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar4);
	if (dword_6FBBA98C != 0)
	{
		sub_6FAD6DC0();
		dword_6FBBA98C = 0;
	}
	sub_6FB23260(0xe, 1, 0);
	sub_6FAB6450(nullptr);
}

//D2Client.0x6FB25320
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB25320()
{
	bool bVar1;
	uint32_t extraout_var;
	D2UnitStrc* pDVar2;
	int iVar3;
	HWND__* pHVar4;
	int* piVar5;
	float fVar6;
	float fVar7;
	int iVar8;
	uint32_t uVar9;
	uint32_t uStack_54;
	uint32_t uStack_50;
	D2InventoryStrc* local_4c;
	int local_48[18];

	D2_ASSERT(dword_6FBBA97C);
	bVar1 = sub_6FB283E0();
	if (D2C_ZEXT(bVar1) == 0)
	{
		sub_6FB25500();
		if (dword_6FBBA97C != 2)
		{
			return;
		}
		pDVar2 = sub_6FB269F0(dword_6FBBA988, 4);
		if (pDVar2 == nullptr)
		{
			return;
		}
		piVar5 = local_48;
		for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*piVar5 = 0;
			piVar5 = piVar5 + 1;
		}
		iVar3 = sub_6FB5EC80((int)local_48, pDVar2, 0, nullptr, nullptr,
		    &local_4c, 1, (D2InventoryStrc*)0xffffffff);
		if (iVar3 == 0)
		{
			return;
		}
		iVar3 = D2CMP_10055((int)local_48, 0, 1);
		if (iVar3 == 0)
		{
			return;
		}
		if (local_48[0] == 0)
		{
			return;
		}
		sub_6FB5DFB0(pDVar2, 0, 0, (int*)(&uStack_50), (int*)(&uStack_54));
		UNITS_ChangeAnimMode(pDVar2, 0);
		uVar9 = 0;
		if (uStack_54 < 0x70)
		{
			uVar9 = 0x72 - uStack_54 >> 1;
		}
		sub_6FB5A320(pDVar2, (D2CellFileStrc*)(0xa7 - (uStack_50 >> 1)), uVar9 + 0x6a);
		UNITS_ChangeAnimMode(pDVar2, 4);
		return;
	}
	dword_6FBBA97C = 0;
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 == nullptr)
	{
		pDVar2 = nullptr;
	}
	else
	{
		pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
	}
	if (dword_6FBBA97C == 1)
	{
		dword_6FBBA97C = 2;
		sub_6FB575B0(nullptr);
		if (pDVar2 == nullptr)
			goto LAB_6fb253ce;
		dword_6FBBA988 = pDVar2->dwUnitId;
		iVar8 = 0;
		fVar7 = 0.0;
		fVar6 = 0.0;
		iVar3 = sub_6FB2E590(pDVar2);
	}
	else
	{
		if (dword_6FBBA97C != 2)
			goto LAB_6fb253ce;
		dword_6FBBA97C = 1;
		dword_6FBBA988 = 0;
		if (pDVar2 != nullptr)
		{
			sub_6FB575B0(pDVar2);
		}
		iVar8 = 0;
		fVar7 = 0.0;
		fVar6 = 0.0;
		iVar3 = 1;
	}
	sub_6FB55820(iVar3, nullptr, fVar6, fVar7, iVar8);
LAB_6fb253ce:
	uVar9 = 8;
	pHVar4 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar9);
	if (dword_6FBBA98C != 0)
	{
		sub_6FAD6DC0();
		dword_6FBBA98C = 0;
	}
	sub_6FB23260(0xe, 1, 0);
	sub_6FAB6450(nullptr);
}

//D2Client.0x6FB25500
void __cdecl sub_6FB25500()
{
	D2SplittedTextStrc* pDVar1;
	int iVar2;
	Unicode* pUVar3;
	int iVar4;
	int iVar5;
	D2SplittedTextStrc* pFree;
	int iVar6;
	int iVar7;
	int* piVar8;
	short sVar9;
	D2GfxDataStrc* pDVar10;
	uint32_t uVar11;
	uint32_t uVar12;
	int iStack_58;
	int iStack_50;
	Font FStack_4c;
	D2GfxDataStrc DStack_48;

	FStack_4c = D2Win_10127_SetFont(D2FONT_FONT16);
	if ((dword_6FBBA978 == 1) || (dword_6FBBA978 == 0))
	{
		pDVar10 = &DStack_48;
		for (iVar6 = 0x12; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			pDVar10->pCurrentCell = nullptr;
			pDVar10 = (D2GfxDataStrc*)&pDVar10->pCellFile;
		}
		DStack_48.nDirection = 0;
		if (dword_6FBBA978 == 0)
		{
			DStack_48.pCellFile = gpCellFile_6FBBA9A0;
		}
		else
		{
			DStack_48.pCellFile = gpCellFile_6FBBA99C;
		}
		DStack_48.nFrame = 0;
		TEXTURE_CelDraw(&DStack_48, 0x69, 0x10e, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_48.pCellFile = sub_6FB24110();
		iVar6 = 0;
		if (0 < dword_6FB906B0)
		{
			piVar8 = (int*)(&dword_6FB90682);
			do
			{
				DStack_48.nFrame = (uint32_t)((char)piVar8[1] != '\0') + *piVar8;
				TEXTURE_CelDraw(&DStack_48, piVar8[-6], piVar8[-5], 0xffffffff, DRAWMODE_NORMAL, nullptr);
				iVar6 = iVar6 + 1;
				piVar8 = piVar8 + 10;
			} while (iVar6 < dword_6FB906B0);
		}
		iVar2 = sub_6FB57BC0();
		iVar6 = sub_6FB57BD0();
		iStack_50 = iVar6;
		if (((iVar2 < 0x140) && (iVar6 < gnScreenHeight + -0x30)) && (iStack_58 = 0, 0 < dword_6FB906B0))
		{
			piVar8 = (int*)(&dword_6FB90676);
			do
			{
				if (((piVar8[-1] <= iVar2) && (iVar2 <= *piVar8)) &&
				    ((piVar8[1] <= iVar6 && (iVar6 <= piVar8[2]))))
				{
					sVar9 = *(short*)((int)piVar8 + -0x16);
					if (sVar9 == 0xfb1)
					{
						if (dword_6FBBA978 == 0)
						{
							sVar9 = 0xd49;
						}
						iVar6 = sub_6FAF3950();
						if (iVar6 == 0x1ff)
						{
							sVar9 = 0x58dc;
						}
						else
						{
							iVar6 = sub_6FAF3950();
							if (iVar6 == 0x200)
							{
								sVar9 = 0x58dd;
							}
						}
					}
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar9));
					iVar6 = D2Win_10121_GetTextWidth(pUVar3);
					uVar12 = 2;
					uVar11 = 0;
					iVar4 = D2Win_10125();
					iVar4 = iVar4 + 6;
					iVar7 = iVar6 + 0xc;
					iVar5 = D2Win_10125();
					sub_6FB5B0F0((piVar8[-5] - iVar6 / 2) + 10, (piVar8[-4] - iVar5) + -0x2a, iVar7, iVar4, uVar11, (DrawMode)(uVar12));
					D2Win_10117_DrawText(pUVar3, (piVar8[-5] - iVar6 / 2) + 0x10, piVar8[-4] + -0x26, 0, 0);
					iVar6 = iStack_50;
				}
				iStack_58 = iStack_58 + 1;
				piVar8 = piVar8 + 10;
			} while (iStack_58 < dword_6FB906B0);
		}
		if (dword_6FBBA978 == 1)
		{
			sVar9 = 0x275c;
			iVar6 = sub_6FAF3950();
			if (iVar6 == 0x1ff)
			{
				sVar9 = 0x58de;
			}
			else
			{
				iVar6 = sub_6FAF3950();
				if (iVar6 == 0x200)
				{
					sVar9 = 0x58db;
				}
			}
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar9));
			pFree = D2Win_10199(pUVar3, &iStack_50, 300);
			if (pFree != nullptr)
			{
				iVar6 = 0x1e;
				do
				{
					iVar2 = D2Win_10121_GetTextWidth(pFree->wszLine);
					D2Win_10117_DrawText(pFree->wszLine, 0xa0 - iVar2 / 2, iVar6, 4, 0);
					pDVar1 = pFree->pNextLine;
					D2_FREE(pFree->wszLine);
					D2_FREE(pFree);
					iVar6 = iVar6 + 0x14;
					pFree = pDVar1;
				} while (pDVar1 != nullptr);
			}
		}
	}
	if (dword_6FBBA98C != 0)
	{
		sub_6FAD6EB0(dword_6FBBA98C);
	}
	D2Win_10127_SetFont(FStack_4c);
}

//D2Client.0x6FB257B0
// TODO: decompilation needs review (extraout, stack0x)
void __fastcall sub_6FB257B0(int a1)
{
	uint8_t stack0xfffffff0[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	D2UnitStrc* pDVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_ECX;
	float fVar4;
	float fVar5;
	int iVar6;
	uint32_t uVar7;

	switch (*(uint8_t*)(a1 + 5))
	{
	case 0:
		dword_6FBBA978 = 0;
		dword_6FBBA984 = *(uint32_t*)(a1 + 1);
		sub_6FB23800(0, 0);
		dword_6FBBA97C = 1;
		byte_6FBBA990 = GetTickCount();
		uVar7 = 8;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar7);
		sub_6FAE94E0();
		iVar2 = sub_6FB23260(0xe, 0, 0);
		if (iVar2 != 0)
		{
			sub_6FAABF30();
			sub_6FAB6450((uint32_t*)stack0xfffffff0);
			return;
		}
		if (dword_6FBBA978 == 0)
		{
			pDVar1 = CUNIT_GetPlayer();
			if (pDVar1 == nullptr)
			{
				uVar7 = 0xffffffff;
			}
			else
			{
				uVar7 = pDVar1->dwUnitId;
			}
			sub_6FAADAA0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x44), uVar7, dword_6FBBA984, 0, 2);
		}
		else
		{
			sub_6FAF3AD0();
		}
		dword_6FBBA97C = 0;
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			pDVar1 = nullptr;
		}
		else
		{
			pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		}
		if (dword_6FBBA97C == 1)
		{
			dword_6FBBA97C = 2;
			sub_6FB575B0(nullptr);
			if (pDVar1 == nullptr)
				goto LAB_6fb25b22;
			dword_6FBBA988 = pDVar1->dwUnitId;
			iVar6 = 0;
			fVar5 = 0.0;
			fVar4 = 0.0;
			iVar2 = sub_6FB2E590(pDVar1);
		}
		else
		{
			if (dword_6FBBA97C != 2)
				goto LAB_6fb25b22;
			dword_6FBBA97C = 1;
			dword_6FBBA988 = 0;
			if (pDVar1 != nullptr)
			{
				sub_6FB575B0(pDVar1);
			}
			iVar6 = 0;
			fVar5 = 0.0;
			fVar4 = 0.0;
			iVar2 = 1;
		}
		sub_6FB55820(iVar2, nullptr, fVar4, fVar5, iVar6);
	LAB_6fb25b22:
		uVar7 = 8;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar7);
		if (dword_6FBBA98C != 0)
		{
			sub_6FAD6DC0();
			dword_6FBBA98C = 0;
		}
		sub_6FB23260(0xe, 1, 0);
		sub_6FAB6450(nullptr);
		return;
	case 1:
		break;
	default:
		FOG_DisplayAssert("0", __FILE__, __LINE__);
		exit(-1);
	case 4:
		dword_6FBBA97C = 2;
		if (dword_6FBBA98C != 0)
		{
			sub_6FAD6DC0();
			dword_6FBBA98C = 0;
		}
		return;
	case 5:
		pDVar1 = CUNIT_GetPlayer();
		INVENTORY_SetCursorItem(pDVar1->pInventory, nullptr);
		iVar2 = 5;
		if (*(char*)(a1 + 6) == '\0')
		{
			iVar2 = 3;
		}
		sub_6FB55820(iVar2, nullptr, 0.0, 0.0, 0);
		break;
	case 6:
	case 7:
		dword_6FBBA97C = 0;
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			pDVar1 = nullptr;
		}
		else
		{
			pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		}
		if (dword_6FBBA97C == 1)
		{
			dword_6FBBA97C = 2;
			sub_6FB575B0(nullptr);
			if (pDVar1 == nullptr)
				goto LAB_6fb2597d;
			dword_6FBBA988 = pDVar1->dwUnitId;
			iVar6 = 0;
			fVar5 = 0.0;
			fVar4 = 0.0;
			iVar2 = sub_6FB2E590(pDVar1);
		}
		else
		{
			if (dword_6FBBA97C != 2)
				goto LAB_6fb2597d;
			dword_6FBBA97C = 1;
			dword_6FBBA988 = 0;
			if (pDVar1 != nullptr)
			{
				sub_6FB575B0(pDVar1);
			}
			iVar6 = 0;
			fVar5 = 0.0;
			fVar4 = 0.0;
			iVar2 = 1;
		}
		sub_6FB55820(iVar2, nullptr, fVar4, fVar5, iVar6);
	LAB_6fb2597d:
		uVar7 = 8;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar7);
		if (dword_6FBBA98C != 0)
		{
			sub_6FAD6DC0();
			dword_6FBBA98C = 0;
		}
		sub_6FB23260(0xe, 1, 0);
		sub_6FAB6450(nullptr);
		sub_6FAF3960();
		return;
	}
	dword_6FBBA97C = 0;
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 == nullptr)
	{
		pDVar1 = nullptr;
	}
	else
	{
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
	}
	if (dword_6FBBA97C == 1)
	{
		dword_6FBBA97C = 2;
		sub_6FB575B0(nullptr);
		if (pDVar1 == nullptr)
			goto LAB_6fb258b8;
		dword_6FBBA988 = pDVar1->dwUnitId;
		iVar6 = 0;
		fVar5 = 0.0;
		fVar4 = 0.0;
		iVar2 = sub_6FB2E590(pDVar1);
	}
	else
	{
		if (dword_6FBBA97C != 2)
			goto LAB_6fb258b8;
		dword_6FBBA97C = 1;
		dword_6FBBA988 = 0;
		if (pDVar1 != nullptr)
		{
			sub_6FB575B0(pDVar1);
		}
		iVar6 = 0;
		fVar5 = 0.0;
		iVar2 = 1;
		fVar4 = 0.0;
	}
	sub_6FB55820(iVar2, nullptr, fVar4, fVar5, iVar6);
LAB_6fb258b8:
	uVar7 = 8;
	pHVar3 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar7);
	if (dword_6FBBA98C != 0)
	{
		sub_6FAD6DC0();
		dword_6FBBA98C = 0;
	}
	sub_6FB23260(0xe, 1, 0);
	sub_6FAB6450(nullptr);
}

//D2Client.0x6FB25BA0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB25BA0(uint32_t a1)
{
	HWND__* pHVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t extraout_ECX;
	float fVar4;
	float fVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uStack_10;
	uint32_t uStack_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	dword_6FBBA978 = 1;
	byte_6FBBA980 = a1;
	sub_6FB23800(0, 0);
	dword_6FBBA97C = 1;
	byte_6FBBA990 = GetTickCount();
	uVar7 = 8;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar7);
	sub_6FAE94E0();
	iVar2 = sub_6FB23260(0xe, 0, 0);
	if (iVar2 != 0)
	{
		sub_6FAABF30();
		uStack_c = 0x5b;
		uStack_10 = 0x6b;
		uStack_4 = 0x116;
		uStack_8 = 0xde;
		sub_6FAB6450(&uStack_10);
		return;
	}
	if (dword_6FBBA978 == 0)
	{
		pDVar3 = CUNIT_GetPlayer();
		if (pDVar3 == nullptr)
		{
			uVar7 = 0xffffffff;
		}
		else
		{
			uVar7 = pDVar3->dwUnitId;
		}
		sub_6FAADAA0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x44), uVar7, dword_6FBBA984, 0, 2);
	}
	else
	{
		sub_6FAF3AD0();
	}
	dword_6FBBA97C = 0;
	pDVar3 = CUNIT_GetPlayer();
	if (pDVar3 == nullptr)
	{
		pDVar3 = nullptr;
	}
	else
	{
		pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
	}
	if (dword_6FBBA97C == 1)
	{
		dword_6FBBA97C = 2;
		sub_6FB575B0(nullptr);
		if (pDVar3 == nullptr)
			goto LAB_6fb25b22;
		dword_6FBBA988 = pDVar3->dwUnitId;
		iVar6 = 0;
		fVar5 = 0.0;
		fVar4 = 0.0;
		iVar2 = sub_6FB2E590(pDVar3);
	}
	else
	{
		if (dword_6FBBA97C != 2)
			goto LAB_6fb25b22;
		dword_6FBBA97C = 1;
		dword_6FBBA988 = 0;
		if (pDVar3 != nullptr)
		{
			sub_6FB575B0(pDVar3);
		}
		iVar6 = 0;
		fVar5 = 0.0;
		fVar4 = 0.0;
		iVar2 = 1;
	}
	sub_6FB55820(iVar2, nullptr, fVar4, fVar5, iVar6);
LAB_6fb25b22:
	uVar7 = 8;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar7);
	if (dword_6FBBA98C != 0)
	{
		sub_6FAD6DC0();
		dword_6FBBA98C = 0;
	}
	sub_6FB23260(0xe, 1, 0);
	sub_6FAB6450(nullptr);
}

//D2Client.0x6FB25BC0
void __cdecl sub_6FB25BC0()
{
	gpWaypointData_6FBBA9B9 = WAYPOINTS_AllocWaypointData(nullptr);
	byte_6FBBA9BD = '\0';
}

//D2Client.0x6FB25BE0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB25BE0()
{
	D2UnitStrc* pDVar1;
	D2ActiveRoomStrc* pDVar2;
	uint32_t extraout_ECX;

	if (byte_6FBBA9BD == '\0')
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 != nullptr)
		{
			pDVar1 = CUNIT_GetPlayer();
			pDVar2 = UNITS_GetRoom(pDVar1);
			if (pDVar2 != nullptr)
			{
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x49), dword_6FBBA9B5, 0);
				byte_6FBBA9BD = '\x01';
			}
		}
	}
	if (gpWaypointData_6FBBA9B9 != nullptr)
	{
		WAYPOINTS_FreeWaypointData(nullptr, gpWaypointData_6FBBA9B9);
	}
	gpWaypointData_6FBBA9B9 = nullptr;
	if (gpCellFile_6FBBA9A9 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA9A9);
		gpCellFile_6FBBA9A9 = nullptr;
	}
	if (gpCellFile_6FBBA9AD != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA9AD);
		gpCellFile_6FBBA9AD = nullptr;
	}
	if (gpCellFile_6FBBA9B1 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA9B1);
		gpCellFile_6FBBA9B1 = nullptr;
	}
}

//D2Client.0x6FB25C70
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB25C70()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	D2UnitStrc* pDVar3;
	D2ActiveRoomStrc* pDVar4;
	D2BitBufferStrc* pDVar5;
	int iVar6;
	Unicode* pUVar7;
	uint32_t extraout_ECX;
	int* piVar8;
	int iVar9;
	int* piVar10;
	D2GfxDataStrc* pDVar11;
	int iVar12;
	int iVar13;
	char* p2;
	int bCentered;
	int aiStack_168[6];
	int iStack_150;
	D2GfxDataStrc DStack_14c;
	char local_104[260];

	if (gpCellFile_6FBBA9A9 == nullptr)
	{
		sprintf(local_104, "%s\\ui\\menu\\waygatebackground", "DATA\\GLOBAL");
		gpCellFile_6FBBA9A9 = CLIENT_LoadCellFile(local_104, 0);
	}
	if (gpCellFile_6FBBA9AD == nullptr)
	{
		iVar2 = FOG_IsExpansion();
		if ((iVar2 == 0) || (iVar2 = sub_6FAAC080(), iVar2 == 0))
		{
			p2 = "%s\\ui\\menu\\waygatetabs";
		}
		else
		{
			p2 = "%s\\ui\\menu\\expwaygatetabs";
		}
		sprintf(local_104, p2, "DATA\\GLOBAL");
		gpCellFile_6FBBA9AD = CLIENT_LoadCellFile(local_104, 0);
	}
	if (gpCellFile_6FBBA9B1 == nullptr)
	{
		sprintf(local_104, "%s\\ui\\menu\\waygateicons", "DATA\\GLOBAL");
		gpCellFile_6FBBA9B1 = CLIENT_LoadCellFile(local_104, 0);
	}
	bVar1 = sub_6FB283E0();
	if (((D2C_ZEXT(bVar1) != 0) && (sub_6FB23260(0x14, 1, 0), byte_6FBBA9BD == '\0')) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr))
	{
		pDVar3 = CUNIT_GetPlayer();
		pDVar4 = UNITS_GetRoom(pDVar3);
		if (pDVar4 != nullptr)
		{
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x49), dword_6FBBA9B5, 0);
			byte_6FBBA9BD = '\x01';
		}
	}
	iVar9 = 1;
	D2Win_10127_SetFont(D2FONT_FONT16);
	pDVar11 = &DStack_14c;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar11->pCurrentCell = nullptr;
		pDVar11 = (D2GfxDataStrc*)&pDVar11->pCellFile;
	}
	DStack_14c.pCellFile = gpCellFile_6FBBA9A9;
	DStack_14c.nDirection = 0;
	DStack_14c.nFrame = 0;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	DStack_14c.nFrame = 1;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	DStack_14c.nFrame = 2;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	DStack_14c.nFrame = 3;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	iVar2 = sub_6FB57BC0();
	aiStack_168[5] = sub_6FB57BD0();
	iStack_150 = iVar2 - dword_6FBBA748;
	aiStack_168[5] = aiStack_168[5] + dword_6FBBA74C;
	DStack_14c.pCellFile = gpCellFile_6FBBA9AD;
	iVar12 = 5;
	iVar2 = FOG_IsExpansion();
	if ((iVar2 == 0) || (iVar2 = sub_6FAAC080(), iVar2 == 0))
	{
		iVar9 = 0;
		iVar12 = 4;
		aiStack_168[0] = 3;
		aiStack_168[1] = 0x51;
		aiStack_168[2] = 0x9f;
		aiStack_168[3] = 0xed;
	}
	else
	{
		aiStack_168[0] = 5;
		aiStack_168[1] = 0x43;
		aiStack_168[2] = 0x81;
		aiStack_168[3] = 0xbf;
		aiStack_168[4] = 0xfd;
	}
	iVar2 = 0;
	if (iVar12 != 0)
	{
		do
		{
			if (iVar2 == dword_6FBBA9BE)
			{
				DStack_14c.nFrame = iVar2 * 2;
			LAB_6fb25f6f:
				TEXTURE_CelDraw(&DStack_14c, aiStack_168[iVar2] + dword_6FBBA748, (iVar9 - dword_6FBBA74C) + 0x21,
				    0xffffffff, DRAWMODE_NORMAL, nullptr);
			}
			else
			{
				switch (iVar2)
				{
				case 1:
					iVar6 = 7;
					break;
				case 2:
					iVar6 = 0xf;
					break;
				case 3:
					iVar6 = 0x17;
					break;
				case 4:
					iVar13 = 0;
					iVar6 = 0x1a;
					pDVar5 = sub_6FAFBD20();
					iVar13 = QUESTRECORD_GetQuestState(pDVar5, iVar6, iVar13);
					iVar6 = FOG_IsExpansion();
					if ((iVar6 != 0) && (iVar6 = sub_6FAAC080(), iVar6 != 0))
						goto joined_r0x6fb25f69;
					goto LAB_6fb25f9e;
				default:
					goto switchD_6fb25f18_default;
				}
				iVar13 = 0;
				pDVar5 = sub_6FAFBD20();
				iVar13 = QUESTRECORD_GetQuestState(pDVar5, iVar6, iVar13);
			joined_r0x6fb25f69:
				if (iVar13 != 0)
				{
				switchD_6fb25f18_default:
					DStack_14c.nFrame = iVar2 * 2 + 1;
					goto LAB_6fb25f6f;
				}
			}
		LAB_6fb25f9e:
			iVar2 = iVar2 + 1;
		} while (iVar2 < iVar12);
	}
	DStack_14c.pCellFile = sub_6FB24110();
	DStack_14c.nFrame = (byte_6FBBA9A4 != '\0') + 10;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748 + 0x111, 0x1a1 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL,
	    nullptr);
	pDVar3 = CUNIT_GetPlayer();
	pDVar4 = UNITS_GetRoom(pDVar3);
	iVar2 = DUNGEON_GetLevelIdFromRoom(pDVar4);
	iVar9 = 0;
	DStack_14c.pCellFile = gpCellFile_6FBBA9B1;
	if (0 < dword_6FBBA9C2)
	{
		piVar8 = (int*)(&dword_6FBBA9CC);
		piVar10 = (int*)(&dword_6FB907B8);
		do
		{
			if ((char)piVar8[1] == '\0')
			{
				iVar12 = 5;
			}
			else
			{
				if (*piVar8 == iVar2)
				{
					DStack_14c.nFrame = (uint32_t)(dword_6FBBA9A5 == iVar9);
				}
				else
				{
					DStack_14c.nFrame = (dword_6FBBA9A5 == iVar9) + 3;
				}
				TEXTURE_CelDraw(&DStack_14c, *piVar10 + dword_6FBBA748, piVar10[1] - dword_6FBBA74C, 0xffffffff,
				    DRAWMODE_NORMAL, nullptr);
				iVar12 = 0;
			}
			if (((byte_6FBBA9A4 == '\0') && (dword_6FBBA9A5 != -1)) && (iVar9 == dword_6FBBA9A5))
			{
				iVar12 = 3;
			}
			if (*piVar8 == iVar2)
			{
				iVar12 = 3;
				DStack_14c.nFrame = 0;
				TEXTURE_CelDraw(&DStack_14c, *piVar10 + dword_6FBBA748, piVar10[1] - dword_6FBBA74C, 0xffffffff,
				    DRAWMODE_NORMAL, nullptr);
			}
			bCentered = 0;
			iVar6 = piVar10[3] - dword_6FBBA74C;
			iVar13 = piVar10[2] + dword_6FBBA748;
			pUVar7 = sub_6FB239F0(*piVar8);
			D2Win_10117_DrawText(pUVar7, iVar13, iVar6, iVar12, bCentered);
			iVar9 = iVar9 + 1;
			piVar10 = piVar10 + 6;
			piVar8 = (int*)((int)piVar8 + 5);
		} while (iVar9 < dword_6FBBA9C2);
	}
	if (((0x110 < iStack_150) && (iStack_150 < 0x135)) &&
	    ((0x182 < aiStack_168[5] && (aiStack_168[5] < 0x1a5))))
	{
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1022));
		iVar2 = D2Win_10121_GetTextWidth(pUVar7);
		iVar2 = iVar2 / 2;
		D2GFX_DrawBox((dword_6FBBA748 - iVar2) + 0x11f, 0x172 - dword_6FBBA74C, iVar2 + 0x126 + dword_6FBBA748,
		    0x183 - dword_6FBBA74C, 0, DRAWMODE_TRANS75);
		D2Win_10117_DrawText(pUVar7, (dword_6FBBA748 - iVar2) + 0x124, 0x181 - dword_6FBBA74C, 0, 0);
	}
	if (dword_6FBBA9C6 == 0)
	{
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf97));
		iVar2 = D2Win_10121_GetTextWidth(pUVar7);
	}
	else
	{
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf96));
		iVar2 = D2Win_10121_GetTextWidth(pUVar7);
	}
	D2Win_10117_DrawText(pUVar7, (dword_6FBBA748 - iVar2 / 2) + 0xa0, 0x30 - dword_6FBBA74C, 0, 0);
}

//D2Client.0x6FB26250
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB26250(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pDVar1;
	D2ActiveRoomStrc* pDVar2;
	uint32_t extraout_ECX;

	if (((pSMSGHANDLER_PARAMS->nMessage != 0x102) || (pSMSGHANDLER_PARAMS->wParam != 9)) &&
	    ((pSMSGHANDLER_PARAMS->nMessage != 0x104 || (pSMSGHANDLER_PARAMS->wParam != 0x73))))
	{
		if (byte_6FBBA9BD == '\0')
		{
			pDVar1 = CUNIT_GetPlayer();
			if (pDVar1 != nullptr)
			{
				pDVar1 = CUNIT_GetPlayer();
				pDVar2 = UNITS_GetRoom(pDVar1);
				if (pDVar2 != nullptr)
				{
					sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x49), dword_6FBBA9B5, 0);
					byte_6FBBA9BD = '\x01';
				}
			}
		}
		sub_6FB23260(0x14, 1, 1);
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FB262E0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB262E0()
{
	D2UnitStrc* pDVar1;
	D2ActiveRoomStrc* pDVar2;
	uint32_t extraout_ECX;

	if (byte_6FBBA9BD == '\0')
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 != nullptr)
		{
			pDVar1 = CUNIT_GetPlayer();
			pDVar2 = UNITS_GetRoom(pDVar1);
			if (pDVar2 != nullptr)
			{
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x49), dword_6FBBA9B5, 0);
				byte_6FBBA9BD = '\x01';
			}
		}
	}
}

//D2Client.0x6FB26320
void __fastcall sub_6FB26320(int a1)
{
	uint8_t bVar1;
	int iVar2;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar3;

	iVar2 = sub_6FB23260(0x14, 0, 1);
	if (iVar2 != 1)
	{
		return;
	}
	sub_6FAABF30();
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			iVar2 = DUNGEON_GetLevelIdFromRoom(pRoom);
			if (iVar2 != 0)
			{
				bVar1 = DRLG_GetActNoFromLevelId(iVar2);
				uVar3 = (uint32_t)bVar1;
				goto LAB_6fb2636a;
			}
		}
	}
	uVar3 = 0;
LAB_6fb2636a:
	sub_6FB263A0(uVar3);
	sub_6FB26440();
	dword_6FBBA9B5 = *(uint32_t*)(a1 + 1);
	WAYPOINTS_CopyAndValidateWaypointData(gpWaypointData_6FBBA9B9, (D2WaypointDataStrc*)(a1 + 5));
	byte_6FBBA9BD = '\0';
	sub_6FB26440();
}

//D2Client.0x6FB263A0
void __fastcall sub_6FB263A0(int a1)
{
	D2BitBufferStrc* pDVar1;
	int iVar2;
	int iVar3;

	if (dword_6FB907B0 <= a1)
	{
		a1 = 0;
	}
	switch (a1)
	{
	case 1:
		goto switchD_6fb263b6_caseD_1;
	case 2:
		break;
	case 4:
		iVar3 = 0;
		iVar2 = 0x1c;
		pDVar1 = sub_6FAFBD20();
		iVar2 = QUESTRECORD_GetQuestState(pDVar1, iVar2, iVar3);
		if (iVar2 == 0)
		{
			a1 = 3;
		}
	case 3:
		iVar3 = 0;
		iVar2 = 0x17;
		pDVar1 = sub_6FAFBD20();
		iVar2 = QUESTRECORD_GetQuestState(pDVar1, iVar2, iVar3);
		if (iVar2 == 0)
		{
			a1 = 2;
		}
		break;
	default:
		dword_6FBBA9BE = a1;
		return;
	}
	iVar3 = 0;
	iVar2 = 0xf;
	pDVar1 = sub_6FAFBD20();
	iVar2 = QUESTRECORD_GetQuestState(pDVar1, iVar2, iVar3);
	if (iVar2 == 0)
	{
		a1 = 1;
	}
switchD_6fb263b6_caseD_1:
	iVar3 = 0;
	iVar2 = 7;
	pDVar1 = sub_6FAFBD20();
	iVar2 = QUESTRECORD_GetQuestState(pDVar1, iVar2, iVar3);
	if (iVar2 != 0)
	{
		dword_6FBBA9BE = a1;
		return;
	}
	dword_6FBBA9BE = 0;
}

//D2Client.0x6FB26440
void __cdecl sub_6FB26440()
{
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int iVar1;
	uint8_t* puVar2;
	int iVar3;
	int iVar4;
	uint8_t bVar5;
	uint32_t uVar6;
	int nLevelId;
	uint16_t wField;
	int iStack_8;
	int iStack_4;

	dword_6FBBA9C2 = 0;
	dword_6FBBA9C6 = 0;
	pUnit = CUNIT_GetPlayer();
	pRoom = UNITS_GetRoom(pUnit);
	iVar1 = DUNGEON_GetLevelIdFromRoom(pRoom);
	puVar2 = &byte_6FBBA9D0;
	do
	{
		*(uint32_t*)(puVar2 + -4) = 0;
		*puVar2 = 0;
		iVar4 = dword_6FBBA9BE;
		puVar2 = puVar2 + 5;
	} while ((int)puVar2 < (int)&tbl_6FBBA9FD);
	if (5 < (uint32_t)dword_6FBBA9BE)
	{
		byte_6FBBA9BD = '\0';
		return;
	}
	iVar3 = dword_6FBBA9BE * 0xb;
	if ((&byte_6FB90778)[iVar3] == '\0')
	{
		(&byte_6FB90778)[iVar3] = 1;
		nLevelId = *(int*)(byte_6FB90779 + iVar3);
		if (nLevelId <= *(int*)(byte_6FB9077D + iVar3))
		{
			do
			{
				iVar3 = WAYPOINTS_GetWaypointNoFromLevelId(nLevelId, (short*)&iStack_8);
				iVar4 = dword_6FBBA9BE;
				if (iVar3 != 0)
				{
					iVar3 = dword_6FBBA9BE * 0xb;
					if ((&byte_6FB90781)[iVar3] == -1)
					{
						(&byte_6FB90781)[iVar3] = (uint8_t)iStack_8;
					}
					bVar5 = byte_6FB90782[iVar3];
					if ((uint8_t)byte_6FB90782[iVar3] < (uint8_t)iStack_8)
					{
						bVar5 = (uint8_t)iStack_8;
					}
					byte_6FB90782[iVar3] = bVar5;
				}
				nLevelId = nLevelId + 1;
			} while (nLevelId <= *(int*)(byte_6FB9077D + iVar4 * 0xb));
		}
	}
	uVar6 = (uint32_t)(uint8_t)(&byte_6FB90781)[iVar4 * 0xb];
	if (uVar6 <= (uint8_t)byte_6FB90782[iVar4 * 0xb])
	{
		do
		{
			wField = (uint16_t)uVar6;
			iVar4 = WAYPOINTS_IsActivated(gpWaypointData_6FBBA9B9, wField);
			if (iVar4 == 0)
			{
				iVar4 = WAYPOINTS_GetLevelIdFromWaypointNo(wField, &iStack_4);
				if (iVar4 != 0)
				{
					*(int*)((int)&dword_6FBBA9CC + dword_6FBBA9C2 * 5) = iStack_4;
				LAB_6fb2658f:
					(&byte_6FBBA9D0)[dword_6FBBA9C2 * 5] = 0;
					goto LAB_6fb26597;
				}
			}
			else
			{
				iVar4 = WAYPOINTS_GetLevelIdFromWaypointNo(wField, &iStack_8);
				if (iVar4 != 0)
				{
					*(int*)((int)&dword_6FBBA9CC + dword_6FBBA9C2 * 5) = iStack_8;
					if (iVar1 == iStack_8)
						goto LAB_6fb2658f;
					(&byte_6FBBA9D0)[dword_6FBBA9C2 * 5] = 1;
					dword_6FBBA9C6 = dword_6FBBA9C6 + 1;
				LAB_6fb26597:
					dword_6FBBA9C2 = dword_6FBBA9C2 + 1;
				}
			}
			uVar6 = uVar6 + 1;
		} while ((int)uVar6 <= (int)(uint32_t)(uint8_t)byte_6FB90782[dword_6FBBA9BE * 0xb]);
	}
}

//D2Client.0x6FB265C0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB265C0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	D2ActiveRoomStrc* pDVar4;
	char* pcVar5;
	uint32_t extraout_ECX;
	int* piVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	int iVar10;

	uVar8 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar9 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	iVar2 = sub_6FB09CC0();
	if (iVar2 == 0)
	{
		if (((int)uVar8 <= gnScreenWidth) && ((int)uVar9 <= gnScreenHeight + -0x31))
		{
			iVar2 = uVar8 - dword_6FBBA748;
			iVar10 = uVar9 + dword_6FBBA74C;
			if (byte_6FBBA9A4 == '\0')
			{
				if (dword_6FBBA9A5 != -1)
				{
					iVar7 = 0;
					piVar6 = (int*)("<");
					pcVar5 = (char*)(&byte_6FBBA9D0);
					do
					{
						if ((((*pcVar5 != '\0') && (piVar6[-1] < iVar2)) && (iVar2 < piVar6[-1] + 0x118)) &&
						    ((*piVar6 < iVar10 && (iVar10 < *piVar6 + 0x1e))))
							goto LAB_6fb266fb;
						pcVar5 = pcVar5 + 5;
						iVar7 = iVar7 + 1;
						piVar6 = piVar6 + 6;
					} while ((int)pcVar5 < (int)&tbl_6FBBA9FD);
					iVar7 = -1;
				LAB_6fb266fb:
					if (dword_6FBBA9A5 == iVar7)
					{
						pSMSGHANDLER_PARAMS->bUseResult = 1;
						pSMSGHANDLER_PARAMS->lResult = 0;
						SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
						uVar1 = *(uint32_t*)((int)&dword_6FBBA9CC + dword_6FBBA9A5 * 5);
						sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar1 >> 8), 0x49), dword_6FBBA9B5, uVar1);
						byte_6FBBA9BD = '\x01';
						byte_6FBBA9A4 = '\0';
						dword_6FBBA9A5 = -1;
						sub_6FB23260(0x14, 1, 0);
						sub_6FB55820(0x8b7, nullptr, 0.0, 0.0, 0);
						pSMSGHANDLER_PARAMS->bUseResult = 1;
						pSMSGHANDLER_PARAMS->lResult = 0;
						SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
						return;
					}
				}
			}
			else if (((0x110 < iVar2) && (iVar2 < 0x135)) &&
			         ((0x182 < iVar10 &&
			             (((iVar10 < 0x1a5 && (sub_6FB23260(0x14, 1, 0), byte_6FBBA9BD == '\0')) &&
			                 (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr))))))
			{
				pDVar3 = CUNIT_GetPlayer();
				pDVar4 = UNITS_GetRoom(pDVar3);
				if (pDVar4 != nullptr)
				{
					sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x49), dword_6FBBA9B5, 0);
					byte_6FBBA9BD = '\x01';
				}
			}
			byte_6FBBA9A4 = '\0';
			dword_6FBBA9A5 = -1;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
		byte_6FBBA9A4 = '\0';
		dword_6FBBA9A5 = -1;
	}
}

//D2Client.0x6FB267A0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB267A0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	char* pcVar2;
	D2UnitStrc* pDVar3;
	D2ActiveRoomStrc* pDVar4;
	int* piVar5;
	uint32_t extraout_ECX;
	uint32_t uVar6;
	int iVar7;
	uint32_t uVar8;
	int iVar9;

	uVar8 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar6 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	iVar1 = sub_6FB09CC0();
	if (iVar1 != 0)
	{
		return;
	}
	if ((gnScreenWidth / 2 < (int)uVar8) || (gnScreenHeight + -0x31 < (int)uVar6))
	{
		if ((byte_6FBBA9BD == '\0') && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr))
		{
			pDVar3 = CUNIT_GetPlayer();
			pDVar4 = UNITS_GetRoom(pDVar3);
			if (pDVar4 != nullptr)
			{
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x49), dword_6FBBA9B5, 0);
				byte_6FBBA9BD = '\x01';
			}
		}
		sub_6FB23260(0x14, 1, 1);
		return;
	}
	iVar7 = uVar6 + dword_6FBBA74C;
	iVar9 = uVar8 - dword_6FBBA748;
	iVar1 = FOG_IsExpansion();
	if ((iVar1 == 0) || (iVar1 = sub_6FAAC080(), iVar1 == 0))
	{
		if ((iVar7 < 0x1f) && (iVar9 < 0x141))
		{
			if (iVar9 < 0x50)
			{
				iVar1 = 0;
			}
			else if (iVar9 < 0xa0)
			{
				iVar1 = 1;
			}
			else
			{
				iVar1 = (0xef < iVar9) + 2;
			}
			goto LAB_6fb26888;
		}
	}
	else if ((iVar7 < 0x1f) && (iVar9 < 0x141))
	{
		if (iVar9 < 0x40)
		{
			iVar1 = 0;
		}
		else if (iVar9 < 0x80)
		{
			iVar1 = 1;
		}
		else if (iVar9 < 0xc0)
		{
			iVar1 = 2;
		}
		else
		{
			iVar1 = (0xff < iVar9) + 3;
		}
	LAB_6fb26888:
		if (iVar1 != dword_6FBBA9BE)
		{
			sub_6FB55820(6, nullptr, 0.0, 0.0, 0);
		}
		sub_6FB263A0(iVar1);
		sub_6FB26440();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
	dword_6FBBA9A5 = -1;
	if ((((iVar9 < 0x111) || (0x134 < iVar9)) || (iVar7 < 0x183)) || (0x1a4 < iVar7))
	{
		dword_6FBBA9A5 = 0;
		piVar5 = (int*)("<");
		pcVar2 = (char*)(&byte_6FBBA9D0);
		do
		{
			if (((*pcVar2 != '\0') && (piVar5[-1] < iVar9)) &&
			    ((iVar9 < piVar5[-1] + 0x118 && ((*piVar5 < iVar7 && (iVar7 < *piVar5 + 0x1e))))))
				goto LAB_6fb26935;
			pcVar2 = pcVar2 + 5;
			dword_6FBBA9A5 = dword_6FBBA9A5 + 1;
			piVar5 = piVar5 + 6;
		} while ((int)pcVar2 < (int)&tbl_6FBBA9FD);
		dword_6FBBA9A5 = -1;
	LAB_6fb26935:
		if (dword_6FBBA9A5 == -1)
			goto LAB_6fb26950;
	}
	else
	{
		byte_6FBBA9A4 = '\x01';
	}
	sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
LAB_6fb26950:
	if (((int)(uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam <= gnScreenWidth) &&
	    ((int)(uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2) <= gnScreenHeight + -0x31))
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}
