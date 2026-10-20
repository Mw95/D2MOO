#include "Game/View.h"

#include "Core/Archive.h"
#include "Core/MemoryPartitions.h"
#include "Core/StormList.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Draw/DWall.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/SCmd.h"
#include "Game/Wall2.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"

//D2Client.0x6FBAF348
uint32_t unk_6FBAF348[1] = {  };
//D2Client.0x6FBAF37C
uint32_t unk_6FBAF37C[1] = {  };

//D2Client.0x6FB7712C
uint8_t* gpuint8_t_6FB7712C = (uint8_t*)&unk_6FBAF37C;
//D2Client.0x6FB77130
uint8_t* gpuint8_t_6FB77130 = (uint8_t*)&unk_6FBAF348;
//D2Client.0x6FBABA00
uint32_t dword_6FBABA00;
//D2Client.0x6FBABE00
uint32_t dword_6FBABE00;
//D2Client.0x6FBAC200
uint8_t byte_6FBAC200;
//D2Client.0x6FBAC204
uint32_t dword_6FBAC204;
//D2Client.0x6FBAC208
uint32_t dword_6FBAC208;
//D2Client.0x6FBAC20C
int32_t dword_6FBAC20C;
//D2Client.0x6FBAC210
int32_t dword_6FBAC210;
//D2Client.0x6FBAC214
uint8_t byte_6FBAC214;
//D2Client.0x6FBAC218
uint32_t dword_6FBAC218;
//D2Client.0x6FBAC240
uint8_t byte_6FBAC240[12544];
//D2Client.0x6FBAF340
uint8_t byte_6FBAF340;
//D2Client.0x6FBAF344
int32_t dword_6FBAF344;
//D2Client.0x6FBAF350
uint32_t dword_6FBAF350;
//D2Client.0x6FBAF378
DWORD dword_6FBAF378;
//D2Client.0x6FBAF388
uint8_t byte_6FBAF388;
//D2Client.0x6FBAF488
int32_t dword_6FBAF488;
//D2Client.0x6FBAF490
uint32_t dword_6FBAF490;
//D2Client.0x6FBAF890
uint32_t dword_6FBAF890;
//D2Client.0x6FBAF8B8
uint8_t byte_6FBAF8B8[8];
//D2Client.0x6FBAF8C0
uint32_t dword_6FBAF8C0;
//D2Client.0x6FBAF8C4
int32_t dword_6FBAF8C4;
//D2Client.0x6FBAF8C8
int32_t dword_6FBAF8C8;
//D2Client.0x6FBAF8CC
LPVOID sgpGouraudTblX;
//D2Client.0x6FBAF8D0
LPVOID sgpGouraudTblY;
//D2Client.0x6FBAF8D4
LPVOID sgpGouraudTblXVal;
//D2Client.0x6FBAF8DC
LPVOID gpSubtileGouraudTbl;
//D2Client.0x6FBAF8E0
LPVOID glpvoid_6FBAF8E0;
//D2Client.0x6FBAF8E4
D2CellFileStrc* gpCellFile_6FBAF8E4;
//D2Client.0x6FBAF8E8
D2CellFileStrc* gpCellFile_6FBAF8E8;
//D2Client.0x6FBAF8EC
int32_t dword_6FBAF8EC;
//D2Client.0x6FBAF8F0
char byte_6FBAF8F0;
//D2Client.0x6FBAF8F4
uint8_t byte_6FBAF8F4;
//D2Client.0x6FBAF8F8
char byte_6FBAF8F8;
//D2Client.0x6FBAF8FC
int32_t dword_6FBAF8FC;

//D2Client.0x6FAB6AC0
void __cdecl sub_6FAB6AC0()
{
	uint8_t bVar1;
	uint32_t* puVar2;
	uint32_t uVar3;
	int iVar4;
	uint8_t* puVar5;
	uint32_t uVar6;
	uint32_t* puVar7;
	uint32_t uStack_14;
	uint32_t uStack_10;
	int iStack_c;

	D2_ASSERT(sgpGouraudTblX == (LPVOID)0x0);
	D2_ASSERT(sgpGouraudTblY == (LPVOID)0x0);
	if (sgpGouraudTblXVal != (LPVOID)0x0)
	{
		FOG_DisplayAssert("!sgpGouraudTblXVal", __FILE__, __LINE__);
		exit(-1);
	}
	D2_ASSERT(gpSubtileGouraudTbl == (LPVOID)0x0);
	if (glpvoid_6FBAF8E0 != (LPVOID)0x0)
	{
		FOG_DisplayAssert("!gpTileGouraudTbl", __FILE__, __LINE__);
		exit(-1);
	}
	D2Win_10178((D2ShadowLightGammaPaletteStrc*)byte_6FBAC240);
	sgpGouraudTblX = (LPVOID)sub_6FB6BD9A(0x9000);
	uStack_10 = 0;
	uStack_14 = 0;
	puVar2 = (uint32_t*)sgpGouraudTblX;
	do
	{
		iStack_c = 0x20;
		uVar6 = uStack_10;
		do
		{
			iVar4 = 8;
			uVar3 = uStack_14;
			do
			{
				puVar7 = puVar2;
				bVar1 = (uint8_t)(uVar3 + ((int)uVar3 >> 0x1f & 0xffffU) >> 0x10);
				iVar4 = iVar4 + -1;
				*puVar7 = (uint32_t)(byte_6FBAC240 + (uint32_t)bVar1 * 0x100);
				puVar2 = puVar7 + 1;
				uVar3 = uVar3 + ((int)(uVar6 + ((int)uVar6 >> 0x1f & 7U)) >> 3);
			} while (iVar4 != 0);
			puVar2 = puVar7 + 2;
			uVar6 = uVar6 + 0x10000;
			puVar7[1] = (uint32_t)(byte_6FBAC240 + (uint32_t)bVar1 * 0x100);
			iStack_c = iStack_c + -1;
		} while (iStack_c != 0);
		uStack_14 = uStack_14 + 0x10000;
		uStack_10 = uStack_10 + -0x10000;
	} while (uStack_14 < 0x200000);
	sgpGouraudTblY = (LPVOID)sub_6FB6BD9A(0x4003);
	uStack_14 = 0;
	uStack_10 = 0;
	puVar5 = (uint8_t*)sgpGouraudTblY;
	do
	{
		iStack_c = 0x20;
		uVar6 = uStack_14;
		do
		{
			iVar4 = 0x10;
			uVar3 = uStack_10;
			do
			{
				*puVar5 = (char)(uVar3 + ((int)uVar3 >> 0x1f & 0xffffU) >> 0x10);
				puVar5 = puVar5 + 1;
				iVar4 = iVar4 + -1;
				uVar3 = uVar3 + ((int)(uVar6 + ((int)uVar6 >> 0x1f & 0xfU)) >> 4);
			} while (iVar4 != 0);
			uVar6 = uVar6 + 0x10000;
			iStack_c = iStack_c + -1;
		} while (iStack_c != 0);
		uStack_10 = uStack_10 + 0x10000;
		uStack_14 = uStack_14 + -0x10000;
	} while (uStack_10 < 0x200000);
	sgpGouraudTblXVal = (LPVOID)sub_6FB6BD9A(0x8003);
	uStack_14 = 0;
	uStack_10 = 0;
	puVar5 = (uint8_t*)sgpGouraudTblXVal;
	do
	{
		iStack_c = 0x20;
		uVar6 = uStack_14;
		do
		{
			iVar4 = 0x20;
			uVar3 = uStack_10;
			do
			{
				*puVar5 = (char)(uVar3 + ((int)uVar3 >> 0x1f & 0xffffU) >> 0x10);
				puVar5 = puVar5 + 1;
				iVar4 = iVar4 + -1;
				uVar3 = uVar3 + ((int)(uVar6 + ((int)uVar6 >> 0x1f & 0x1fU)) >> 5);
			} while (iVar4 != 0);
			uVar6 = uVar6 + 0x10000;
			iStack_c = iStack_c + -1;
		} while (iStack_c != 0);
		uStack_10 = uStack_10 + 0x10000;
		uStack_14 = uStack_14 + -0x10000;
	} while (uStack_10 < 0x200000);
	gpSubtileGouraudTbl = (LPVOID)sub_6FB6BD9A(0x20000);
	uStack_14 = 0;
	uStack_10 = 0;
	puVar2 = (uint32_t*)gpSubtileGouraudTbl;
	do
	{
		iStack_c = 0x20;
		uVar6 = uStack_14;
		do
		{
			iVar4 = 0x20;
			uVar3 = uStack_10;
			puVar7 = puVar2;
			do
			{
				puVar2 = puVar7 + 1;
				iVar4 = iVar4 + -1;
				*puVar7 = (uint32_t)(byte_6FBAC240 +
				                     ((int)(uVar3 + ((int)uVar3 >> 0x1f & 0xffffU)) >> 0x10 & 0xffU) * 0x100);
				uVar3 = uVar3 + ((int)(uVar6 + ((int)uVar6 >> 0x1f & 0x1fU)) >> 5);
				puVar7 = puVar2;
			} while (iVar4 != 0);
			uVar6 = uVar6 + 0x10000;
			iStack_c = iStack_c + -1;
		} while (iStack_c != 0);
		uStack_10 = uStack_10 + 0x10000;
		uStack_14 = uStack_14 + -0x10000;
	} while (uStack_10 < 0x200000);
	glpvoid_6FBAF8E0 = (LPVOID)sub_6FB6BD9A(0xa003);
	uStack_14 = 0;
	uStack_10 = 0;
	puVar5 = (uint8_t*)glpvoid_6FBAF8E0;
	do
	{
		iStack_c = 0x20;
		uVar6 = uStack_14;
		do
		{
			iVar4 = 0x28;
			uVar3 = uStack_10;
			do
			{
				*puVar5 = (char)(uVar3 + ((int)uVar3 >> 0x1f & 0xffffU) >> 0x10);
				puVar5 = puVar5 + 1;
				iVar4 = iVar4 + -1;
				uVar3 = uVar3 + (int)uVar6 / 0x28;
			} while (iVar4 != 0);
			uVar6 = uVar6 + 0x10000;
			iStack_c = iStack_c + -1;
		} while (iStack_c != 0);
		uStack_10 = uStack_10 + 0x10000;
		uStack_14 = uStack_14 + -0x10000;
	} while (uStack_10 < 0x200000);
}

//D2Client.0x6FAB6EB0
void __cdecl sub_6FAB6EB0()
{
	if (sgpGouraudTblX != (LPVOID)0x0)
	{
		D2_ASSERT(sgpGouraudTblY != (LPVOID)0x0);
		D2_ASSERT(sgpGouraudTblXVal != (LPVOID)0x0);
		D2_ASSERT(gpSubtileGouraudTbl != (LPVOID)0x0);
		if (glpvoid_6FBAF8E0 == (LPVOID)0x0)
		{
			FOG_DisplayAssert("gpTileGouraudTbl", __FILE__, __LINE__);
			exit(-1);
		}
		sub_6FB6BDAB(sgpGouraudTblX);
		if (sgpGouraudTblY != (LPVOID)0x0)
		{
			sub_6FB6BDAB(sgpGouraudTblY);
		}
		if (sgpGouraudTblXVal != (LPVOID)0x0)
		{
			sub_6FB6BDAB(sgpGouraudTblXVal);
		}
		if (gpSubtileGouraudTbl != (LPVOID)0x0)
		{
			sub_6FB6BDAB(gpSubtileGouraudTbl);
		}
		if (glpvoid_6FBAF8E0 != (LPVOID)0x0)
		{
			sub_6FB6BDAB(glpvoid_6FBAF8E0);
		}
		sgpGouraudTblX = (LPVOID)0x0;
		sgpGouraudTblY = (LPVOID)0x0;
		sgpGouraudTblXVal = (LPVOID)0x0;
		gpSubtileGouraudTbl = (LPVOID)0x0;
		glpvoid_6FBAF8E0 = (LPVOID)0x0;
		dword_6FBAC210 = 0;
		if (gpCellFile_6FBAF8E4 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBAF8E4);
			gpCellFile_6FBAF8E4 = nullptr;
		}
		if (gpCellFile_6FBAF8E8 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBAF8E8);
			gpCellFile_6FBAF8E8 = nullptr;
		}
	}
}

//D2Client.0x6FAB6FF0
uint32_t* __cdecl sub_6FAB6FF0()
{
	uint32_t* puVar1;

	D2_ASSERT(sgpGouraudTblX != (LPVOID)0x0);
	D2_ASSERT(sgpGouraudTblY != (LPVOID)0x0);
	if (sgpGouraudTblXVal == (LPVOID)0x0)
	{
		FOG_DisplayAssert("sgpGouraudTblXVal", __FILE__, __LINE__);
		exit(-1);
	}
	puVar1 = (uint32_t*)D2_ALLOC(0xeabc);
	SetRect((LPRECT)(puVar1 + 1), 0, 0, 0, 0);
	*puVar1 = 0;
	puVar1[0xb] = (uint32_t)sgpGouraudTblX;
	puVar1[0xc] = (uint32_t)sgpGouraudTblY;
	puVar1[0xd] = (uint32_t)sgpGouraudTblXVal;
	MEMORY_Nop();
	sub_6FAB7F00((int)puVar1);
	*puVar1 = *puVar1 | 1;
	dword_6FBAF8C0 = 0;
	return puVar1;
}

//D2Client.0x6FAB70D0
void __fastcall sub_6FAB70D0(int a1)
{
	sub_6FAB7F20(a1);
	D2_FREE((void*)a1);
}

//D2Client.0x6FAB70F0
void __fastcall sub_6FAB70F0(uint32_t* a1)
{
	*a1 = *a1 | 1;
}

//D2Client.0x6FAB7100
void __fastcall sub_6FAB7100(uint32_t* a1, int a2, int a3, int a4, int a5)
{
	LPRECT lprc;
	uint32_t uVar1;
	int iVar2;

	if (a1 != nullptr)
	{
		SetRect((LPRECT)(a1 + 1), a2, a3, a4, a5);
		iVar2 = D2GFX_CheckPerspective();
		lprc = (LPRECT)(a1 + 5);
		SetRect(lprc, -0x50, -0x50, gnScreenWidth + 0x50, gnScreenHeight + -0x2f);
		if (iVar2 != 0)
		{
			iVar2 = lprc->left;
			uVar1 = a1[7];
			a1[6] = a1[6] - 0x1e;
			lprc->left = iVar2 + -0x2d;
			a1[7] = uVar1 + 0x1e;
		}
		*a1 = *a1 | 1;
	}
}

//D2Client.0x6FAB7180
void __fastcall sub_6FAB7180(int a1, uint32_t* a2, uint32_t* a3, uint32_t* a4, uint32_t* a5)
{
	*a2 = *(uint32_t*)(a1 + 4);
	*a3 = *(uint32_t*)(a1 + 8);
	*a4 = *(uint32_t*)(a1 + 0xc);
	*a5 = *(uint32_t*)(a1 + 0x10);
}

//D2Client.0x6FAB71B0
void __fastcall sub_6FAB71B0(uint32_t* a1, uint32_t a2, uint32_t a3)
{
	if ((a1[9] != a2) || (a1[10] != a3))
	{
		a1[10] = a3;
		a1[9] = a2;
		*a1 = *a1 | 1;
	}
}

//D2Client.0x6FAB71E0
void __fastcall sub_6FAB71E0(int a1, uint32_t* a2, uint32_t* a3)
{
	*a2 = *(uint32_t*)(a1 + 0x24);
	*a3 = *(uint32_t*)(a1 + 0x28);
}

//D2Client.0x6FAB7200
void __fastcall sub_6FAB7200(uint32_t* hView, uint32_t a2)
{
	int iVar1;

	D2_ASSERT(hView != nullptr);
	if ((hView[3] != 0) || (hView[4] != 0))
	{
		iVar1 = sub_6FAB5750();
		if (iVar1 != 3)
		{
			sub_6FAB7F60((int)hView, a2);
		}
		*hView = *hView & 0xfffffffe;
	}
}

//D2Client.0x6FAB7260
void __fastcall sub_6FAB7260(int a1)
{
	int64_t lVar1;
	DWORD DVar2;
	uint8_t bVar3;
	int iVar4;
	D2UnitStrc* pUnit;
	int iVar5;
	uint32_t uVar6;
	D2ActiveRoomStrc* pRoom;
	DWORD DVar7;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	int local_10;
	uint8_t* puStack_c;
	D2ActiveRoomStrc* pDStack_8;
	D2UnitStrc* pDStack_4;

	if ((*(int*)(a1 + 0xc) == 0) && (*(int*)(a1 + 0x10) == 0))
	{
		return;
	}
	local_10 = a1;
	SCALE_UpdateFactor();
	byte_6FBAC214 = SCALE_GetFactor();
	iVar4 = D2GFX_CheckPerspective();
	if (iVar4 != 0)
	{
		pUnit = CUNIT_GetPlayer();
		iVar4 = UNITS_GetPrecisionX(pUnit);
		iVar5 = UNITS_GetPrecisionY(pUnit);
		iStack_1c = 0;
		iStack_18 = 0;
		if (dword_6FBAF8C4 != 0)
		{
			iStack_1c = dword_6FBAF8C8 << 0x10;
			iStack_18 = dword_6FBAC20C << 0x10;
			DUNGEON_ClientToGameSubtileCoords(&iStack_1c, &iStack_18);
			iVar4 = iVar4 + iStack_1c;
			iVar5 = iVar5 + iStack_18;
		}
		SCALE_SetPerspectiveScale(iVar4, iVar5);
	}
	uVar6 = sub_6FAABF80();
	if (dword_6FBAF8C0 < uVar6)
	{
		dword_6FBAF8C0 = uVar6;
		sub_6FAA4AF0();
	}
	sub_6FAA62B0();
	pDStack_4 = CUNIT_GetPlayer();
	pRoom = UNITS_GetRoom(pDStack_4);
	pDStack_8 = pRoom;
	iVar4 = DUNGEON_GetLevelIdFromRoom(pRoom);
	DVar2 = dword_6FBAF378;
	if (iVar4 == 0x4a)
	{
		if (dword_6FBAF8EC == 0)
		{
			SEED_InitSeed((D2SeedStrc*)gpuint8_t_6FB7712C);
			iVar4 = SEED_GetRandomValue(dword_6FBAF344);
			SEED_InitLowSeed((D2SeedStrc*)gpuint8_t_6FB7712C, iVar4);
			iStack_14 = 0;
			iVar4 = 0;
			do
			{
				iVar5 = iVar4 / 7 + 0x80;
				uVar6 = sub_6FAA88D0((uint32_t*)gpuint8_t_6FB7712C);
				iStack_1c = ((uVar6 & 0x3f) - 0x20) + iVar5;
				if (0xff < iStack_1c)
				{
					iStack_1c = 0xff;
				}
				uVar6 = sub_6FAA88D0((uint32_t*)gpuint8_t_6FB7712C);
				iStack_18 = ((uVar6 & 0x3f) - 0x20) + iVar5;
				if (0xff < iStack_18)
				{
					iStack_18 = 0xff;
				}
				puStack_c = gpuint8_t_6FB7712C;
				lVar1 = (uint64_t) * (uint32_t*)gpuint8_t_6FB7712C * 0x6ac690c5 +
				        (uint64_t) * (uint32_t*)(gpuint8_t_6FB7712C + 4);
				*(int64_t*)gpuint8_t_6FB7712C = lVar1;
				iVar5 = (((uint32_t)lVar1 & 0x3f) - 0x20) + iVar5;
				if (0xff < iVar5)
				{
					iVar5 = 0xff;
				}
				bVar3 = D2Win_10034_MixRGB((uint8_t)iStack_1c, (uint8_t)iStack_18, (uint8_t)iVar5);
				iVar4 = iVar4 + 0x80;
				byte_6FBAF8B8[iStack_14] = bVar3;
				iStack_14 = iStack_14 + 1;
			} while (iVar4 < 0x400);
			iVar4 = 0;
			do
			{
				sub_6FAB7590(iVar4, 0);
				iVar4 = iVar4 + 1;
			} while (iVar4 < 0x100);
			dword_6FBAF8EC = 1;
			pRoom = pDStack_8;
		}
		iVar4 = 0;
		do
		{
			D2GFX_DrawLine((&dword_6FBABE00)[iVar4], (&dword_6FBABA00)[iVar4], (&dword_6FBABE00)[iVar4],
			    (&dword_6FBABA00)[iVar4], (&byte_6FBAF388)[iVar4], 0xff);
			iVar4 = iVar4 + 1;
		} while (iVar4 < 0x100);
		DVar7 = GetTickCount();
		a1 = local_10;
		DVar2 = dword_6FBAF378;
		if (0x28 < DVar7 - dword_6FBAF378)
		{
			iVar4 = 0;
			do
			{
				iVar5 = (&dword_6FBABE00)[iVar4];
				(&dword_6FBABE00)[iVar4] = iVar5 + (&dword_6FBAF490)[iVar4];
				if (iVar5 + (&dword_6FBAF490)[iVar4] < 0)
				{
					sub_6FAB7590(iVar4, 1);
				}
				iVar4 = iVar4 + 1;
				a1 = local_10;
				DVar2 = DVar7;
			} while (iVar4 < 0x100);
		}
	}
	dword_6FBAF378 = DVar2;
	iVar4 = DUNGEON_GetLevelIdFromRoom(pRoom);
	if (iVar4 == 0x78)
	{
		sub_6FAB76F0();
	}
	else
	{
		if (gpCellFile_6FBAF8E4 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBAF8E4);
			gpCellFile_6FBAF8E4 = nullptr;
		}
		if (gpCellFile_6FBAF8E8 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBAF8E8);
			gpCellFile_6FBAF8E8 = nullptr;
		}
	}
	if ((*(uint32_t*)((uint8_t*)&gdwBitMasks) & *(uint32_t*)(a1 + 0x38)) != 0)
	{
		sub_6FAA6670(a1);
	}
	WNDPROC_DrawFloor((D2GameViewStrc*)a1, 0);
	sub_6FAA8830();
	if ((*(uint32_t*)(a1 + 0x38) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0xc)) != 0)
	{
		sub_6FAA6860(a1);
	}
	sub_6FAA6340(a1);
	if ((*(uint32_t*)(a1 + 0x38) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4)) != 0)
	{
		DFLOOR_DrawRoofTiles((D2GameViewStrc*)(a1));
	}
	if (dword_6FBAF8FC != 0)
	{
		sub_6FAA6130();
	}
	SCALE_SetDefaultFactor();
	sub_6FAA8240();
	sub_6FAA6210();
}

//D2Client.0x6FAB7590
void __fastcall sub_6FAB7590(int a1, int a2)
{
	int64_t lVar1;
	uint64_t uVar2;
	uint8_t* puVar3;
	int iVar4;
	uint32_t uVar5;
	uint64_t* puVar6;

	iVar4 = gnViewWidth;
	if (a2 == 0)
	{
		if (gnViewWidth < 1)
		{
			uVar5 = 0;
		}
		else if ((gnViewWidth & gnViewWidth - 1U) == 0)
		{
			lVar1 = (uint64_t) * (uint32_t*)gpuint8_t_6FB7712C * 0x6ac690c5 +
			        (uint64_t) * (uint32_t*)(gpuint8_t_6FB7712C + 4);
			*(int64_t*)gpuint8_t_6FB7712C = lVar1;
			uVar5 = iVar4 - 1U & (uint32_t)lVar1;
		}
		else
		{
			uVar2 = (uint64_t) * (uint32_t*)gpuint8_t_6FB7712C * 0x6ac690c5 +
			        (uint64_t) * (uint32_t*)(gpuint8_t_6FB7712C + 4);
			*(uint64_t*)gpuint8_t_6FB7712C = uVar2;
			uVar5 = (uint32_t)((uVar2 & 0xffffffff) % (uint64_t)(uint32_t)iVar4);
		}
		puVar6 = (uint64_t*)gpuint8_t_6FB7712C;
		(&dword_6FBABE00)[a1] = uVar5;
	}
	else
	{
		lVar1 = (uint64_t) * (uint32_t*)gpuint8_t_6FB7712C * 0x6ac690c5 +
		        (uint64_t) * (uint32_t*)(gpuint8_t_6FB7712C + 4);
		*(int64_t*)gpuint8_t_6FB7712C = lVar1;
		puVar6 = (uint64_t*)gpuint8_t_6FB7712C;
		(&dword_6FBABE00)[a1] = (((uint32_t)lVar1 & 7) - 1) + gnViewWidth;
	}
	iVar4 = gnViewHeight;
	if (gnViewHeight < 1)
	{
		uVar5 = 0;
	}
	else if ((gnViewHeight & gnViewHeight - 1U) == 0)
	{
		uVar2 = (uint64_t)(uint32_t)*puVar6 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)puVar6 + 4);
		*puVar6 = uVar2;
		uVar5 = iVar4 - 1U & (uint32_t)uVar2;
		puVar6 = (uint64_t*)gpuint8_t_6FB7712C;
	}
	else
	{
		uVar2 = (uint64_t)(uint32_t)*puVar6 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)puVar6 + 4);
		*puVar6 = uVar2;
		uVar5 = (uint32_t)((uVar2 & 0xffffffff) % (uint64_t)(uint32_t)iVar4);
		puVar6 = (uint64_t*)gpuint8_t_6FB7712C;
	}
	(&dword_6FBABA00)[a1] = uVar5;
	uVar2 = (uint64_t)(uint32_t)*puVar6 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)puVar6 + 4);
	*puVar6 = uVar2;
	puVar3 = gpuint8_t_6FB7712C;
	(&dword_6FBAF490)[a1] = -1 - (int)((uVar2 & 0xffffffff) % 5);
	lVar1 = (uint64_t) * (uint32_t*)puVar3 * 0x6ac690c5 + (uint64_t) * (uint32_t*)(puVar3 + 4);
	*(int64_t*)puVar3 = lVar1;
	(&byte_6FBAF388)[a1] = byte_6FBAF8B8[(uint32_t)lVar1 & 7];
}

//D2Client.0x6FAB76F0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAB76F0()
{
	char cVar1;
	uint64_t uVar2;
	int64_t lVar3;
	uint8_t* puVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	int iVar8;
	D2GameResolutionMode DVar9;
	DWORD nValue;
	D2UnitStrc* in_ECX;
	int iVar10;
	uint32_t uVar11;
	int iVar12;
	uint32_t uVar13;
	D2GfxDataStrc* pDVar14;
	uint32_t uVar15;
	D2GfxDataStrc DStack_14c;
	char acStack_104[260];

	if (dword_6FBA7970 == 0)
	{
		if ((byte_6FBAF340 & 1) == 0)
		{
			byte_6FBAF340 = byte_6FBAF340 | 1;
			byte_6FBAC200 = UNITS_GetClientCoordX(in_ECX);
		}
		if (byte_6FBAF8F8 == '\0')
		{
			byte_6FBAF8F8 = '\x01';
			byte_6FBAC200 = 0x274f;
		}
		byte_6FBAF8F4 = UNITS_GetClientCoordX(in_ECX);
		byte_6FBAF8F4 = byte_6FBAF8F4 - byte_6FBAC200;
		iVar5 = byte_6FBAF8F4 + (byte_6FBAF8F4 >> 0x1f & 7U);
		uVar6 = iVar5 >> 3;
		uVar13 = uVar6 & 0x800000ff;
		if ((int)uVar13 < 0)
		{
			uVar13 = (uVar13 - 1 | 0xffffff00) + 1;
		}
		uVar6 = (int)(uVar6 + (iVar5 >> 0x1f & 0xffU)) >> 8 & 0x80000003;
		if ((int)uVar6 < 0)
		{
			uVar7 = uVar6 - 1 | 0xfffffffc;
			uVar6 = uVar7 + 1;
			if ((int)uVar6 < 0)
			{
				uVar6 = uVar7 + 5 + (-uVar6 - 1 & 0xfffffffc);
			}
		}
		uVar6 = uVar6 & 0x80000003;
		if ((int)uVar6 < 0)
		{
			uVar6 = (uVar6 - 1 | 0xfffffffc) + 1;
		}
		iVar5 = -uVar13;
		if (gpCellFile_6FBAF8E4 == nullptr)
		{
			iVar8 = 0;
			do
			{
				cVar1 = "data\\global\\ui\\summit01"[iVar8];
				acStack_104[iVar8] = cVar1;
				iVar8 = iVar8 + 1;
			} while (cVar1 != '\0');
			gpCellFile_6FBAF8E4 = CLIENT_LoadCellFile(acStack_104, 0);
		}
		if (gpCellFile_6FBAF8E8 == nullptr)
		{
			iVar8 = 0;
			do
			{
				cVar1 = "data\\global\\ui\\cloud01"[iVar8];
				acStack_104[iVar8] = cVar1;
				iVar8 = iVar8 + 1;
			} while (cVar1 != '\0');
			gpCellFile_6FBAF8E8 = CLIENT_LoadCellFile(acStack_104, 0);
		}
		pDVar14 = &DStack_14c;
		for (iVar8 = 0x12; iVar8 != 0; iVar8 = iVar8 + -1)
		{
			pDVar14->pCurrentCell = nullptr;
			pDVar14 = (D2GfxDataStrc*)&pDVar14->pCellFile;
		}
		if (gpCellFile_6FBAF8E4 != nullptr)
		{
			DStack_14c.pCellFile = gpCellFile_6FBAF8E4;
			DStack_14c.nFrame = uVar6;
			TEXTURE_CelDraw(&DStack_14c, iVar5, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			uVar7 = uVar6 + 1 & 0x80000003;
			if ((int)uVar7 < 0)
			{
				uVar7 = (uVar7 - 1 | 0xfffffffc) + 1;
			}
			DStack_14c.nFrame = uVar7;
			TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x100, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			uVar11 = uVar6 + 2 & 0x80000003;
			if ((int)uVar11 < 0)
			{
				uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
			}
			DStack_14c.nFrame = uVar11;
			TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x200, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			uVar15 = uVar6 + 3 & 0x80000003;
			if ((int)uVar15 < 0)
			{
				uVar15 = (uVar15 - 1 | 0xfffffffc) + 1;
			}
			DStack_14c.nFrame = uVar15;
			TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x300, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			if (iVar5 != 0 && (int)uVar13 < 1)
			{
				DStack_14c.nFrame = uVar15;
				TEXTURE_CelDraw(&DStack_14c, iVar5 + -0x100, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			}
			DStack_14c.nFrame = uVar6 + 4;
			TEXTURE_CelDraw(&DStack_14c, iVar5, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_14c.nFrame = uVar7 + 4;
			TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x100, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_14c.nFrame = uVar11 + 4;
			TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x200, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_14c.nFrame = uVar15 + 4;
			TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x300, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			if (iVar5 != 0 && (int)uVar13 < 1)
			{
				DStack_14c.nFrame = uVar15 + 4;
				TEXTURE_CelDraw(&DStack_14c, iVar5 + -0x100, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			}
			DVar9 = D2GFX_GetResolutionMode();
			if (DVar9 == NUM_GAME_RESOLUTIONS)
			{
				DStack_14c.nFrame = uVar6 + 8;
				TEXTURE_CelDraw(&DStack_14c, iVar5, 0x300, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				DStack_14c.nFrame = uVar7 + 8;
				TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x100, 0x300, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				DStack_14c.nFrame = uVar11 + 8;
				TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x200, 0x300, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				DStack_14c.nFrame = uVar15 + 8;
				TEXTURE_CelDraw(&DStack_14c, iVar5 + 0x300, 0x300, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				if (iVar5 != 0 && (int)uVar13 < 1)
				{
					DStack_14c.nFrame = uVar15 + 8;
					TEXTURE_CelDraw(&DStack_14c, iVar5 + -0x100, 0x300, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				}
			}
		}
		if (gpCellFile_6FBAF8E8 != nullptr)
		{
			if (byte_6FBAF8F0 == '\0')
			{
				SEED_InitSeed((D2SeedStrc*)gpuint8_t_6FB77130);
				nValue = GetTickCount();
				iVar5 = SEED_GetRandomValue(nValue);
				SEED_InitLowSeed((D2SeedStrc*)gpuint8_t_6FB77130, iVar5);
				iVar5 = 0;
				do
				{
					uVar6 = gnViewWidth * 0x10;
					if ((int)uVar6 < 1)
					{
						uVar6 = 0;
					}
					else if ((uVar6 & uVar6 - 1) == 0)
					{
						lVar3 = (uint64_t) * (uint32_t*)gpuint8_t_6FB77130 * 0x6ac690c5 +
						        (uint64_t) * (uint32_t*)(gpuint8_t_6FB77130 + 4);
						*(int64_t*)gpuint8_t_6FB77130 = lVar3;
						uVar6 = uVar6 - 1 & (uint32_t)lVar3;
					}
					else
					{
						uVar2 = (uint64_t) * (uint32_t*)gpuint8_t_6FB77130 * 0x6ac690c5 +
						        (uint64_t) * (uint32_t*)(gpuint8_t_6FB77130 + 4);
						*(uint64_t*)gpuint8_t_6FB77130 = uVar2;
						uVar6 = (uint32_t)((uVar2 & 0xffffffff) % (uint64_t)uVar6);
					}
					puVar4 = gpuint8_t_6FB77130;
					*(uint32_t*)((int)&dword_6FBAC218 + iVar5) = uVar6;
					uVar2 = (uint64_t) * (uint32_t*)puVar4 * 0x6ac690c5 + (uint64_t) * (uint32_t*)(puVar4 + 4);
					*(uint64_t*)puVar4 = uVar2;
					puVar4 = gpuint8_t_6FB77130;
					*(int*)((int)&dword_6FBAF350 + iVar5) = (int)((uVar2 & 0xffffffff) % 0xfa);
					lVar3 = (uint64_t) * (uint32_t*)puVar4 * 0x6ac690c5 + (uint64_t) * (uint32_t*)(puVar4 + 4);
					*(int64_t*)puVar4 = lVar3;
					*(uint32_t*)((int)&dword_6FBAF890 + iVar5) = ((uint32_t)lVar3 & 0xf) + 8;
					iVar5 = iVar5 + 4;
				} while (iVar5 < 0x28);
				byte_6FBAF8F0 = '\x01';
			}
			iVar5 = 0;
			do
			{
				iVar12 = *(int*)((int)&dword_6FBAC218 + iVar5) + *(int*)((int)&dword_6FBAF890 + iVar5);
				iVar8 = gnViewWidth + 0x170;
				iVar10 = iVar8 * 0x10;
				*(int*)((int)&dword_6FBAC218 + iVar5) = iVar12;
				puVar4 = gpuint8_t_6FB77130;
				if (iVar12 != iVar10 && SBORROW4(iVar12, iVar10) == iVar12 + iVar8 * -0x10 < 0)
				{
					*(uint32_t*)((int)&dword_6FBAC218 + iVar5) = 0xffffe900;
					uVar2 = (uint64_t) * (uint32_t*)puVar4 * 0x6ac690c5 + (uint64_t) * (uint32_t*)(puVar4 + 4);
					*(uint64_t*)puVar4 = uVar2;
					*(int*)((int)&dword_6FBAF350 + iVar5) = (int)((uVar2 & 0xffffffff) % 300);
				}
				iVar5 = iVar5 + 4;
			} while (iVar5 < 0x28);
			iVar5 = 0;
			do
			{
				DStack_14c.pCellFile = gpCellFile_6FBAF8E8;
				iVar8 = (int)(*(int*)((int)&dword_6FBAC218 + iVar5) +
				              (*(int*)((int)&dword_6FBAC218 + iVar5) >> 0x1f & 0xfU)) >>
				        4;
				DStack_14c.nFrame = 0;
				TEXTURE_CelDraw(&DStack_14c, iVar8, *(int*)((int)&dword_6FBAF350 + iVar5), 0xdddddddd,
				    DRAWMODE_MODULATE, nullptr);
				DStack_14c.nFrame = 1;
				TEXTURE_CelDraw(&DStack_14c, iVar8 + 0x100, *(int*)((int)&dword_6FBAF350 + iVar5), 0xdddddddd,
				    DRAWMODE_MODULATE, nullptr);
				iVar5 = iVar5 + 4;
			} while (iVar5 < 0x28);
		}
	}
}

//D2Client.0x6FAB7C50
void __fastcall sub_6FAB7C50(int* a1, int* a2)
{
	uint64_t DVar1;
	uint64_t uVar2;
	DWORD DVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	D2UnitStrc* pDVar6;
	D2SeedStrc* pDVar7;
	uint32_t uVar8;
	uint32_t uVar9;

	DVar3 = GetTickCount();
	uVar4 = DVar3 - dword_6FBAF344;
	uVar9 = 0;
	if (dword_6FBAC204 + dword_6FBAF488 + dword_6FBAC208 < uVar4)
	{
		sub_6FAB7DC0(0);
		dword_6FBAF8C4 = 0;
		dword_6FBAF8C8 = 0;
		dword_6FBAC20C = 0;
		return;
	}
	if (uVar4 < dword_6FBAC208)
	{
		if (dword_6FBAC208 == 0)
			goto LAB_6fab7dae;
		uVar5 = (dword_6FBAF8C4 * uVar4) / dword_6FBAC208;
	}
	else
	{
		uVar5 = dword_6FBAF8C4;
		if (dword_6FBAF488 + dword_6FBAC208 <= uVar4)
		{
			if (dword_6FBAC204 == 0)
				goto LAB_6fab7dae;
			uVar5 = (uint32_t)(((int64_t)(int)((dword_6FBAC204 - uVar4) + dword_6FBAF488 + dword_6FBAC208) *
			                           (int64_t)dword_6FBAF8C4 &
			                       0xffffffffU) /
			                   (uint64_t)dword_6FBAC204);
		}
	}
	uVar9 = uVar5;
	if (uVar5 != 0)
	{
		pDVar6 = CUNIT_GetPlayer();
		uVar4 = uVar5 * 2;
		pDVar7 = &pDVar6->pSeed;
		if ((int)uVar4 < 1)
		{
			uVar8 = 0;
		}
		else
		{
			uVar2 = (uint64_t)(pDVar6->pSeed).nHighSeed;
			if ((uVar4 & uVar4 - 1) == 0)
			{
				DVar1 = (uint64_t)((uint64_t)pDVar7->nLowSeed * 0x6ac690c5 + uVar2);
				*(uint64_t*)pDVar7 = DVar1;
				uVar8 = uVar4 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
			}
			else
			{
				DVar1 = (uint64_t)((uint64_t)pDVar7->nLowSeed * 0x6ac690c5 + uVar2);
				*(uint64_t*)pDVar7 = DVar1;
				uVar8 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar4);
			}
		}
		dword_6FBAF8C8 = uVar8 - uVar5;
		if ((int)uVar4 < 1)
		{
			uVar4 = 0;
		}
		else
		{
			uVar2 = (uint64_t)(pDVar6->pSeed).nHighSeed;
			if ((uVar4 & uVar4 - 1) == 0)
			{
				DVar1 = (uint64_t)((uint64_t)pDVar7->nLowSeed * 0x6ac690c5 + uVar2);
				*(uint64_t*)pDVar7 = DVar1;
				uVar4 = uVar4 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
			}
			else
			{
				DVar1 = (uint64_t)((uint64_t)pDVar7->nLowSeed * 0x6ac690c5 + uVar2);
				*(uint64_t*)pDVar7 = DVar1;
				uVar4 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar4);
			}
		}
		dword_6FBAC20C = uVar4 - uVar5;
		*a1 = *a1 + dword_6FBAF8C8;
		*a2 = *a2 + dword_6FBAC20C;
	}
LAB_6fab7dae:
	sub_6FAB7DC0(uVar9);
}

//D2Client.0x6FAB7DC0
void __fastcall sub_6FAB7DC0(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar3 = (a1 * 0xff) / 0x14;
	if (iVar3 < 1)
	{
		iVar3 = 0;
	LAB_6fab7df0:
		if (iVar3 != 0)
			goto LAB_6fab7df4;
	LAB_6fab7e1f:
		if (dword_6FBAC210 == 0)
		{
			return;
		}
	}
	else
	{
		if (iVar3 < 0xff)
			goto LAB_6fab7df0;
		iVar3 = 0xff;
	LAB_6fab7df4:
		if (dword_6FBAC210 == 0)
		{
			dword_6FBAC210 = sub_6FB55820(0x1c4, nullptr, 0.0, 0.0, 0);
			if (dword_6FBAC210 == 0)
			{
				return;
			}
			sub_6FB55BC0(dword_6FBAC210, 0);
			goto LAB_6fab7e1f;
		}
	}
	iVar1 = sub_6FB55B90(dword_6FBAC210);
	if (iVar3 == iVar1)
	{
		return;
	}
	if (iVar1 < iVar3)
	{
		iVar2 = iVar1 + 6;
		if (iVar1 + 6 <= iVar3)
			goto LAB_6fab7e46;
	}
	else
	{
		iVar2 = iVar1 + -6;
		if (iVar3 <= iVar2)
			goto LAB_6fab7e46;
	}
	iVar2 = iVar3;
LAB_6fab7e46:
	if (iVar2 == 0)
	{
		sub_6FB556A0(dword_6FBAC210);
		dword_6FBAC210 = 0;
		return;
	}
	sub_6FB55BC0(dword_6FBAC210, iVar2);
}

//D2Client.0x6FAB7E70
void __fastcall sub_6FAB7E70(int a1, uint32_t a2, int a3, uint32_t a4)
{
	if (a3 != 0)
	{
		dword_6FBAF344 = GetTickCount();
		dword_6FBAF488 = a3;
		dword_6FBAC204 = a4;
		dword_6FBAC208 = a2;
		dword_6FBAF8C4 = a1;
	}
}

//D2Client.0x6FAB7EB0
uint32_t __fastcall sub_6FAB7EB0(uint32_t* a1, uint32_t* a2)
{
	if (dword_6FBAF8C4 == 0)
	{
		return 0;
	}
	*a1 = dword_6FBAF8C8;
	*a2 = dword_6FBAC20C;
	return 1;
}

//D2Client.0x6FAB7EE0
void __cdecl sub_6FAB7EE0()
{
	dword_6FBAF8C4 = 0;
	dword_6FBAF8C8 = 0;
	dword_6FBAC20C = 0;
}

//D2Client.0x6FAB7F00
void __fastcall sub_6FAB7F00(int a1)
{
	*(uint32_t*)(a1 + 0xeab0) = 0;
	*(uint32_t*)(a1 + 0xea9c) = 0;
	*(uint32_t*)(a1 + 0x38) = 0;
	*(uint32_t*)(a1 + 0xeaa8) = 0;
}
