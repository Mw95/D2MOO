#include "Engine/Cursor.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Engine/Gfx.h"
#include "Engine/GfxUtil.h"
#include "Game/Env.h"
#include "Unit/CUnit.h"

//D2Client.0x6FB96B30
uint32_t tbl_6FB96B30[10] = {0, 0x200, (uint32_t)sub_6FB57330, 0, 0xA0, (uint32_t)sub_6FB57450, 0, 0x202, (uint32_t)sub_6FB57500};
//D2Client.0x6FB96B58
uint8_t byte_6FB96B58[4];
//D2Client.0x6FB96B5C
uint8_t byte_6FB96B5C[4];
//D2Client.0x6FB96B60
uint8_t byte_6FB96B60[4] = {1};
//D2Client.0x6FB96B64
uint8_t byte_6FB96B64[4];
//D2Client.0x6FB96B68
uint8_t byte_6FB96B68[4] = {1};
//D2Client.0x6FB96B6C
uint8_t byte_6FB96B6C[4] = {0, 0x77, 0xB5, 0x6F};
//D2Client.0x6FB96B70
uint8_t* ptr_6FB96B70 = (uint8_t*)"Gaunt";
//D2Client.0x6FB96B98
int32_t dword_6FB96B98 = 8;
//D2Client.0x6FB96C1C
int32_t dword_6FB96C1C = 7;
//D2Client.0x6FB96C34
uint32_t tbl_6FB96C34[60] = {0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFC, 0, 0xFFFFFFFD, 0, 0xFFFFFFFD, 1, 0xFFFFFFFD, 2, 0xFFFFFFFE, 2, 0xFFFFFFFF, 2, 0xFFFFFFFF, 1, 0xFFFFFFFF, 0, 0, 0, 1, 0, 1, 0xFFFFFFFF, 1, 0xFFFFFFFE, 2, 0xFFFFFFFE, 3, 0xFFFFFFFE, 3, 0xFFFFFFFF, 3, 0, 4, 0, 3, 0, 3, 1, 2, 1, 2, 2, 1, 2, 1, 1, 0, 1, 0x20};
//D2Client.0x6FB96D24
int32_t dword_6FB96D24 = 1;
//D2Client.0x6FBC1AA4
D2UnitStrc* gpUnit_6FBC1AA4;
//D2Client.0x6FBC1AA8
uint32_t dword_6FBC1AA8;
//D2Client.0x6FBC1AC0
D2CellFileStrc* gpCellFile_6FBC1AC0;
//D2Client.0x6FBC1AC4
uint32_t dword_6FBC1AC4;
//D2Client.0x6FBC1AC8
uint32_t dword_6FBC1AC8;
//D2Client.0x6FBC1ACC
uint8_t byte_6FBC1ACC;
//D2Client.0x6FBC1AD0
DWORD dword_6FBC1AD0;
//D2Client.0x6FBC1AD4
int32_t dword_6FBC1AD4;
//D2Client.0x6FBC1AE0
int32_t dword_6FBC1AE0;
//D2Client.0x6FBC1AE4
int32_t dword_6FBC1AE4;
//D2Client.0x6FBC1AE8
int32_t dword_6FBC1AE8;
//D2Client.0x6FBC1AEC
uint8_t byte_6FBC1AEC;
//D2Client.0x6FBC1B04
uint32_t dword_6FBC1B04;

//D2Client.0x6FB57330
void __cdecl sub_6FB57330(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	dword_6FBC1AE4 = (int)*(uint16_t*)(a1 + 0xc);
	dword_6FBC1AE8 = (int)*(uint16_t*)(a1 + 0xe);
	iVar3 = D2GFX_HardwareAcceleratedRenderMode();
	if ((iVar3 != 0) && (iVar4 = FOG_IsHandlingError(), iVar3 = dword_6FBC1AE4, iVar4 == 0))
	{
		iVar4 = gnScreenWidth + -1;
		if (iVar4 < dword_6FBC1AE4)
		{
			dword_6FBC1AE4 = iVar4;
		}
		iVar1 = dword_6FBC1AE4;
		iVar2 = gnScreenHeight + -1;
		if ((gnScreenHeight + -1 < dword_6FBC1AE8) || (iVar2 = dword_6FBC1AE8, iVar4 < iVar3))
		{
			dword_6FBC1AE8 = iVar2;
			iVar3 = dword_6FBC1AE8;
			SetCursorPos(dword_6FBC1AE4, dword_6FBC1AE8);
			dword_6FBC1AE4 = iVar1;
			dword_6FBC1AE8 = iVar3;
			return;
		}
	}
	WINDOW_ShowCursor(1);
	dword_6FBC1AD0 = GetTickCount();
	if ((dword_6FBC1AD4 == 4) || (dword_6FBC1AD4 == 2))
	{
		dword_6FBC1AD4 = 3;
		dword_6FBC1AC4 = 2;
		dword_6FBC1AC8 = 0;
		D2_ASSERT(dword_6FB96C1C == 7);
		dword_6FBC1AC8 = dword_6FB96B98 * 0x100 + -0x100;
	}
	*(uint32_t*)(a1 + 0x18) = 0;
	*(uint32_t*)(a1 + 0x1c) = 0;
}

//D2Client.0x6FB57450
void __cdecl sub_6FB57450(int a1)
{
	if (*(int*)(a1 + 8) == 2)
	{
		WINDOW_ShowCursor(0);
	}
	*(uint32_t*)(a1 + 0x18) = 0;
	*(uint32_t*)(a1 + 0x1c) = 0;
}

//D2Client.0x6FB57480
void __cdecl sub_6FB57480(int a1)
{
	dword_6FBC1AE4 = (int)*(uint16_t*)(a1 + 0xc);
	dword_6FBC1AE8 = (int)*(uint16_t*)(a1 + 0xe);
	dword_6FBC1AD0 = GetTickCount();
	if (dword_6FBC1AD4 != 5)
	{
		if (*(int*)(byte_6FB96B68 + dword_6FBC1AC4 * 0x1c) != 0)
		{
			dword_6FBC1AD4 = 5;
			dword_6FBC1AC4 = 4;
			dword_6FBC1AC8 = 0;
		}
		*(uint32_t*)(a1 + 0x18) = 0;
		return;
	}
	*(uint32_t*)(a1 + 0x18) = 0;
}

//D2Client.0x6FB57500
void __cdecl sub_6FB57500(int a1)
{
	dword_6FBC1AE4 = (int)*(uint16_t*)(a1 + 0xc);
	dword_6FBC1AE8 = (int)*(uint16_t*)(a1 + 0xe);
	dword_6FBC1AD0 = GetTickCount();
	if (dword_6FBC1AD4 == 5)
	{
		dword_6FBC1AC4 = 5;
		dword_6FBC1AD4 = 1;
		dword_6FBC1AC8 = 0;
		*(uint32_t*)(a1 + 0x18) = 0;
		return;
	}
	*(uint32_t*)(a1 + 0x18) = 0;
}

//D2Client.0x6FB57560
void __fastcall sub_6FB57560(D2UnitStrc* pUnit, uint32_t a2)
{
	gpUnit_6FBC1AA4 = pUnit;
	dword_6FBC1AC4 = 6;
	dword_6FBC1AC8 = a2;
	dword_6FBC1AD4 = 6;
}

//D2Client.0x6FB57580
void __fastcall sub_6FB57580(uint32_t a1, int a2)
{
	gpUnit_6FBC1AA4 = nullptr;
	dword_6FBC1AC4 = 6;
	dword_6FBC1AC8 = a1;
	dword_6FBC1AD4 = (a2 != 0) + 7;
}

//D2Client.0x6FB575B0
void __fastcall sub_6FB575B0(D2UnitStrc* pUnit)
{
	gpUnit_6FBC1AA4 = pUnit;
	dword_6FBC1AC8 = 0;
	dword_6FBC1AC4 = 5;
	dword_6FBC1AD4 = 1;
	if (pUnit != nullptr)
	{
		dword_6FBC1AD4 = 4;
	}
}

//D2Client.0x6FB575E0
D2UnitStrc* __cdecl sub_6FB575E0()
{
	return gpUnit_6FBC1AA4;
}

//D2Client.0x6FB575F0
uint32_t __fastcall sub_6FB575F0(int a1)
{
	HWND__* pHVar1;
	D2CellFileStrc* pDVar2;
	uint8_t** ppuVar3;
	uint32_t* puVar4;
	uint32_t uVar5;
	CHAR aCStack_50[80];

	uVar5 = 3;
	dword_6FBC1AE0 = a1;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB96B30), uVar5);
	puVar4 = &dword_6FBC1AA8;
	ppuVar3 = &ptr_6FB96B70;
	do
	{
		wsprintfA(aCStack_50, "%s\\UI\\CURSOR\\%s", "DATA\\GLOBAL", *ppuVar3);
		pDVar2 = CLIENT_LoadCellFile(aCStack_50, 0);
		*puVar4 = (uint32_t)(pDVar2);
		ppuVar3 = ppuVar3 + 7;
		puVar4 = puVar4 + 1;
	} while ((int)ppuVar3 < (int)&tbl_6FB96C34);
	dword_6FBC1B04 = 1;
	dword_6FBC1AD4 = 1;
	dword_6FBC1AC4 = 5;
	dword_6FBC1AC8 = 0;
	byte_6FBC1ACC = 0;
	dword_6FBC1AD0 = GetTickCount();
	dword_6FBC1AE4 = gnScreenWidth / 2;
	dword_6FBC1AE8 = gnScreenHeight / 2;
	return 1;
}

//D2Client.0x6FB576B0
void __cdecl sub_6FB576B0()
{
	HWND__* pHVar1;
	uint32_t* puVar2;
	uint32_t uVar3;

	uVar3 = 3;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB96B30), uVar3);
	dword_6FBC1B04 = 0;
	puVar2 = &dword_6FBC1AA8;
	do
	{
		if ((D2CellFileStrc*)*puVar2 != nullptr)
		{
			CLIENT_FreeCellFile((D2CellFileStrc*)*puVar2);
			*puVar2 = 0;
		}
		puVar2 = puVar2 + 1;
	} while ((int)puVar2 < (int)&dword_6FBC1AC4);
}

//D2Client.0x6FB57700
void __cdecl sub_6FB57700()
{
	int iVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	DWORD DVar4;
	int iVar5;
	int nXPos;
	int nYPos;
	D2GfxDataStrc* pDVar6;
	D2GfxDataStrc local_48;

	iVar5 = dword_6FBC1AE0 + dword_6FBC1AE4;
	if (dword_6FBC1AE8 < 0)
	{
		nYPos = 0;
	}
	else
	{
		nYPos = dword_6FBC1AE8;
		if (gnScreenHeight + -1 < dword_6FBC1AE8)
		{
			nYPos = gnScreenHeight + -1;
		}
	}
	nXPos = dword_6FBC1AE0;
	if ((dword_6FBC1AE0 <= iVar5) &&
	    (iVar1 = (gnScreenWidth - dword_6FBC1AE0) + -1, nXPos = iVar5, iVar1 < iVar5))
	{
		nXPos = iVar1;
	}
	pDVar6 = &local_48;
	for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		pDVar6->pCurrentCell = nullptr;
		pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
	}
	local_48.pCellFile = (D2CellFileStrc*)(&dword_6FBC1AA8)[dword_6FBC1AC4];
	local_48.nFrame = dword_6FBC1AC8 >> 8;
	local_48.nDirection = 0;
	TEXTURE_CelDraw(&local_48, nXPos, nYPos, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2_ASSERT(dword_6FB96C1C == 7);
	if (6 < dword_6FBC1AC4)
	{
		FOG_DisplayAssert("Type < NUM_CURSORS", __FILE__, __LINE__);
		exit(-1);
	}
	if (*(int*)(byte_6FB96B58 + dword_6FBC1AC4 * 0x1c) != 0)
	{
		if (dword_6FBC1AD4 == 3)
		{
			dword_6FBC1AC8 = dword_6FBC1AC8 + -0x40;
			if (-1 < dword_6FBC1AC8)
			{
				return;
			}
			if (*(int*)(byte_6FB96B5C + dword_6FBC1AC4 * 0x1c) == 0)
			{
			LAB_6fb57944:
				dword_6FBC1AD4 = 1;
				dword_6FBC1AC4 = 5;
				dword_6FBC1AC8 = 0;
				goto LAB_6fb578e6;
			}
		LAB_6fb578d2:
			iVar5 = sub_6FB57A00(dword_6FBC1AC4);
			dword_6FBC1AC8 = dword_6FBC1AC8 - iVar5;
		}
		else
		{
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 != nullptr)
			{
				if (dword_6FBC1AD4 == 1)
				{
					uVar3 = sub_6FAA88D0(&(pDVar2->pSeed).nLowSeed);
					if ((uVar3 & 0x3f) < 0x10)
					{
						dword_6FBC1AC8 = dword_6FBC1AC8 + 0x20;
					}
				}
				else
				{
					dword_6FBC1AC8 = dword_6FBC1AC8 + *(int*)(byte_6FB96B64 + dword_6FBC1AC4 * 0x1c);
				}
				D2_ASSERT(dword_6FB96C1C == 7);
				D2_ASSERT(6 >= dword_6FBC1AC4);
				if (*(int*)(byte_6FB96B60 + dword_6FBC1AC4 * 0x1c) * 0x100 <= dword_6FBC1AC8)
				{
					iVar5 = sub_6FB579A0(dword_6FBC1AC4);
					if (iVar5 != 0)
						goto LAB_6fb578d2;
					if (dword_6FBC1AD4 == 2)
					{
						dword_6FBC1AC4 = 3;
						dword_6FBC1AC8 = 0;
						dword_6FBC1AD4 = 4;
						return;
					}
					D2_ASSERT(dword_6FBC1AD4 == 5);
					goto LAB_6fb57944;
				}
			}
		}
	}
	if (dword_6FBC1AD4 != 1)
	{
		return;
	}
LAB_6fb578e6:
	DVar4 = GetTickCount();
	if (dword_6FBC1AD0 + 5000 < DVar4)
	{
		dword_6FBC1AC8 = 0;
		dword_6FBC1AD4 = 2;
		dword_6FBC1AC4 = 2;
	}
}

//D2Client.0x6FB579A0
uint32_t __fastcall sub_6FB579A0(int a1)
{
	D2_ASSERT(dword_6FB96C1C == 7);
	if (6 < a1)
	{
		FOG_DisplayAssert("Type < NUM_CURSORS", __FILE__, __LINE__);
		exit(-1);
	}
	return *(uint32_t*)(byte_6FB96B5C + a1 * 0x1c);
}

//D2Client.0x6FB57A00
int __fastcall sub_6FB57A00(int a1)
{
	D2_ASSERT(dword_6FB96C1C == 7);
	if (6 < a1)
	{
		FOG_DisplayAssert("Type < NUM_CURSORS", __FILE__, __LINE__);
		exit(-1);
	}
	return *(int*)(byte_6FB96B60 + a1 * 0x1c) << 8;
}

//D2Client.0x6FB57A60
void __cdecl sub_6FB57A60()
{
	D2GfxDataStrc* pDVar1;
	int iVar2;
	D2GfxDataStrc local_48;

	pDVar1 = &local_48;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar1->pCurrentCell = 0;
		pDVar1 = (D2GfxDataStrc*)((int)pDVar1 + 4);
	}
	local_48.pCellFile = gpCellFile_6FBC1AC0;
	local_48.nFrame = dword_6FBC1AC8;
	local_48.nDirection = 0;
	TEXTURE_CelDraw(&local_48, dword_6FBC1AE0 + dword_6FBC1AE4, dword_6FBC1AE8 + 0x21, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FB57AC0
// TODO: decompilation needs review (jumptable)
void __cdecl sub_6FB57AC0()
{
	uint32_t uVar1;
	int iVar2;
	D2CellFileStrc** ppDVar3;
	D2InventoryStrc* local_4c;
	D2CellFileStrc* local_48[18];

	if (dword_6FBC1B04 != 0)
	{
		if ((((gpUnit_6FBC1AA4 == nullptr) || (gpUnit_6FBC1AA4->dwUnitType != 4)) ||
		        (5 < dword_6FBC1AD4)) ||
		    (7 < dword_6FBC1AD4))
		{
			// TODO: Ghidra: Could not recover jumptable
			// TODO: Ghidra: Treating indirect jump
			(**(code**)(byte_6FB96B6C + dword_6FBC1AC4 * 0x1c))();
			return;
		}
		ppDVar3 = local_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*ppDVar3 = nullptr;
			ppDVar3 = ppDVar3 + 1;
		}
		iVar2 = sub_6FB5EC80((int)local_48, gpUnit_6FBC1AA4, 0, nullptr, nullptr,
		    &local_4c, 1, (D2InventoryStrc*)0xffffffff);
		if (iVar2 != 0)
		{
			iVar2 = D2CMP_10055((int)local_48, 0, 1);
			if (iVar2 != 0)
			{
				D2_ASSERT(local_48[0] != nullptr);
				uVar1 = D2CMP_CelGetHeight(local_48[0]);
				iVar2 = dword_6FBC1AE8 - (uVar1 >> 1);
				uVar1 = D2CMP_CelGetWidth(local_48[0]);
				sub_6FB5A320(gpUnit_6FBC1AA4, (D2CellFileStrc*)((dword_6FBC1AE0 - (uVar1 >> 1)) + dword_6FBC1AE4),
				    iVar2);
			}
		}
	}
}

//D2Client.0x6FB57BC0
int __cdecl sub_6FB57BC0()
{
	return dword_6FBC1AE4;
}

//D2Client.0x6FB57BD0
int __cdecl sub_6FB57BD0()
{
	return dword_6FBC1AE8;
}

//D2Client.0x6FB57BE0
void __fastcall sub_6FB57BE0(int a1, int a2)
{
	int iVar1;
	HWND__* hWnd;
	int iVar2;
	tagRECT* lpRect;
	tagRECT tStack_10;

	D2_ASSERT(a1 >= 0);
	D2_ASSERT(a2 >= 0);
	iVar1 = WINDOW_IsFullScreen();
	if (iVar1 == 0)
	{
		lpRect = &tStack_10;
		hWnd = WINDOW_GetWindow();
		GetWindowRect((HWND)hWnd, lpRect);
		iVar1 = GetSystemMetrics(4);
		iVar2 = GetSystemMetrics(7);
		SetCursorPos(iVar2 + tStack_10.left + a1, iVar1 + tStack_10.top + a2);
		dword_6FBC1AE8 = a2;
		dword_6FBC1AE4 = a1;
		return;
	}
	SetCursorPos(a1, a2);
	dword_6FBC1AE8 = a2;
	dword_6FBC1AE4 = a1;
}

//D2Client.0x6FB57CA0
void __cdecl sub_6FB57CA0()
{
	byte_6FBC1AEC = (int)(1000 / (int64_t)dword_6FB96D24);
}

//D2Client.0x6FB57CC0
int __cdecl sub_6FB57CC0()
{
	return dword_6FBC1AD4;
}
