#include "Game/Scroll.h"

#include "Core/WinMain.h"
#include "Game/Game.h"
#include "Game/Select.h"
#include "UI/NpcMenu.h"
#include "Game/View.h"
#include "Unit/CUnit.h"

//D2Client.0x6FBAB9B8
int32_t dword_6FBAB9B8;
//D2Client.0x6FBAB9BC
int32_t dword_6FBAB9BC;
//D2Client.0x6FBAB9C0
uint8_t byte_6FBAB9C0;
//D2Client.0x6FBAB9C4
uint32_t dword_6FBAB9C4;
//D2Client.0x6FBAB9C8
int32_t dword_6FBAB9C8;

//D2Client.0x6FAB5760
void __fastcall sub_6FAB5760(int32_t a1)
{
	switch (a1)
	{
	case 0:
	case 3:
		dword_6FBAB9C8 = 0;
		break;
	case 1:
		dword_6FBAB9C8 = -(gnScreenWidth / 4);
		break;
	case 2:
		dword_6FBAB9C8 = gnScreenWidth / 4;
		break;
	default:
		FOG_DisplayHalt("Setting scroll window mode", __FILE__, __LINE__);
		exit(-1);
	}

	dword_6FBAB9C4 = a1;
	D2GFX_SetViewMatrixAdjust(dword_6FBAB9C8);

	const int32_t nQuarterWidth = gnViewWidth / 4;
	switch (a1)
	{
	case 0:
		sub_6FAB7100((uint32_t*)dword_6FBA7990, 0, 0, gnViewWidth, gnViewHeight);
		break;
	case 1:
		sub_6FAB7100((uint32_t*)dword_6FBA7990, -nQuarterWidth, 0, gnViewWidth - nQuarterWidth, gnViewHeight);
		break;
	case 2:
		sub_6FAB7100((uint32_t*)dword_6FBA7990, nQuarterWidth, 0, gnViewWidth + nQuarterWidth, gnViewHeight);
		break;
	case 3:
		sub_6FAB7100((uint32_t*)dword_6FBA7990, 0, 0, gnViewWidth, gnViewHeight);
		sub_6FAABF60();
		break;
	}
}

//D2Client.0x6FAB5870
int __cdecl sub_6FAB5870()
{
	return dword_6FBAB9BC;
}

//D2Client.0x6FAB5880
int __cdecl sub_6FAB5880()
{
	return dword_6FBAB9B8;
}

//D2Client.0x6FAB5890
int __cdecl sub_6FAB5890()
{
	return dword_6FBAB9BC - dword_6FBAB9C8;
}

//D2Client.0x6FAB58A0
int __cdecl sub_6FAB58A0()
{
	return dword_6FBAB9B8 + -8;
}

//D2Client.0x6FAB58B0
void __fastcall sub_6FAB58B0(int* a1, int* a2)
{
	int iVar1;
	int local_8;
	int local_4;

	local_8 = *a1;
	local_4 = *a2;
	iVar1 = D2GFX_CheckPerspective();
	if (iVar1 != 0)
	{
		iVar1 = (int)((uint64_t)((int64_t)local_4 * -0x66666667) >> 0x20);
		local_4 = local_4 + ((iVar1 >> 4) - (iVar1 >> 0x1f));
		local_8 = local_8 + ((0x28 - ((int)((local_4 >> 0x1f & 3U) + local_4) >> 2)) *
		                        (local_8 - gnScreenWidth / 2)) /
		                        (gnScreenWidth / 2);
	}
	local_4 = local_4 + dword_6FBAB9B8;
	local_8 = local_8 + (dword_6FBAB9BC - dword_6FBAB9C8);
	DUNGEON_ClientToGameSubtileCoords(&local_8, &local_4);
	*a1 = local_8;
	*a2 = local_4;
}

//D2Client.0x6FAB5960
void __cdecl sub_6FAB5960()
{
	D2UnitStrc* pUnit;
	int iVar1;
	int iVar2;
	int iStack_8;
	int iStack_4;

	byte_6FBAB9C0 = -0xa0;
	if (dword_6FBAB9C4 == 2)
	{
		byte_6FBAB9C0 = gnScreenWidth / 2 + -0xa0;
	}
	else if (dword_6FBAB9C4 == 3)
	{
		byte_6FBAB9C0 = 0;
	}
	pUnit = CUNIT_GetPlayer();
	iVar1 = UNITS_GetClientCoordX(pUnit);
	iVar2 = UNITS_GetClientCoordY(pUnit);
	dword_6FBAB9BC = iVar1 - gnScreenWidth / 2;
	dword_6FBAB9B8 = (iVar2 - gnScreenHeight / 2) + 0x10;
	iVar1 = sub_6FAB7EB0((uint32_t*)(&iStack_8), (uint32_t*)(&iStack_4));
	if (iVar1 != 0)
	{
		dword_6FBAB9BC = dword_6FBAB9BC + iStack_8;
		dword_6FBAB9B8 = dword_6FBAB9B8 + iStack_4;
	}
}

//D2Client.0x6FAB5A20
D2UnitStrc* __cdecl sub_6FAB5A20()
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	if (dword_6FBAB9E8 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBAB9D0, dword_6FBAB9CC);
		if (pDVar1 != nullptr)
		{
			uVar2 = sub_6FB286F0(pDVar1, 0, 0, 0);
			if (uVar2 != 0)
			{
				return pDVar1;
			}
		}
		dword_6FBAB9EC = 0;
		dword_6FBAB9E8 = 0;
	}
	return nullptr;
}

//D2Client.0x6FAB5A70
uint32_t __cdecl sub_6FAB5A70()
{
	return dword_6FB77080;
}

//D2Client.0x6FAB5A80
uint32_t __cdecl sub_6FAB5A80()
{
	return dword_6FB77084;
}

//D2Client.0x6FAB5A90
void __fastcall sub_6FAB5A90(D2UnitStrc* pUnit)
{
	uint32_t uVar1;

	if (pUnit == nullptr)
	{
		dword_6FBAB9E8 = 0;
		dword_6FBAB9EC = 1;
		return;
	}
	uVar1 = sub_6FB286F0(pUnit, 0, 0, 0);
	dword_6FBAB9EC = 0;
	if (uVar1 != 0)
	{
		sub_6FAB5AE0(pUnit);
		dword_6FBAB9EC = 1;
		return;
	}
	dword_6FBAB9E8 = 0;
}
