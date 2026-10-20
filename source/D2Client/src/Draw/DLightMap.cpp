#include "Draw/DLightMap.h"

#include "Core/WinMain.h"
#include "Draw/DFloor.h"
#include "Draw/DWall.h"
#include "Game/Game.h"
#include "Game/SCmd.h"
#include "Quest/QuestsFX.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/UnitGfx.h"

//D2Client.0x6FB74C88
int32_t dword_6FB74C88 = 1;
//D2Client.0x6FB9A9D8
int32_t dword_6FB9A9D8;
//D2Client.0x6FB9A9E0
uint32_t dword_6FB9A9E0[64];
//D2Client.0x6FB9E9E0
int32_t dword_6FB9E9E0;
//D2Client.0x6FB9E9E4
int32_t dword_6FB9E9E4;
//D2Client.0x6FB9E9E8
int32_t dword_6FB9E9E8;
//D2Client.0x6FB9E9EC
int32_t dword_6FB9E9EC;
//D2Client.0x6FB9E9F0
int32_t dword_6FB9E9F0;
//D2Client.0x6FB9E9F8
uint32_t dword_6FB9E9F8;
//D2Client.0x6FBA29F4
uint32_t tbl_6FBA29F4[1];
//D2Client.0x6FBA29F8
uint8_t byte_6FBA29F8[4];
//D2Client.0x6FBA2DF8
int32_t dword_6FBA2DF8;
//D2Client.0x6FBA2E00
uint32_t dword_6FBA2E00;
//D2Client.0x6FBA2E04
uint8_t byte_6FBA2E04;
//D2Client.0x6FBA2E05
uint8_t byte_6FBA2E05;
//D2Client.0x6FBA2E06
uint8_t byte_6FBA2E06;
//D2Client.0x6FBA2E07
uint8_t byte_6FBA2E07;
//D2Client.0x6FBA7481
uint8_t tbl_6FBA7481[3];
//D2Client.0x6FBA7600
int32_t dword_6FBA7600;
//D2Client.0x6FBA7604
int32_t dword_6FBA7604;
//D2Client.0x6FBA7608
int32_t dword_6FBA7608;
//D2Client.0x6FBA760C
uint8_t byte_6FBA760C;
//D2Client.0x6FBA7610
int32_t dword_6FBA7610;
//D2Client.0x6FBA7614
int32_t dword_6FBA7614;
//D2Client.0x6FBA7618
DWORD dword_6FBA7618;
//D2Client.0x6FBA761C
uint32_t dword_6FBA761C;
//D2Client.0x6FBA7620
uint8_t byte_6FBA7620;
//D2Client.0x6FBA7621
uint8_t byte_6FBA7621;
//D2Client.0x6FBA7622
uint8_t byte_6FBA7622;
//D2Client.0x6FBA7623
uint8_t byte_6FBA7623;

//D2Client.0x6FAA4280
uint32_t* __fastcall sub_6FAA4280(D2UnitStrc* pUnit, int a2, int a3, uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t uVar3;
	void* pvVar4;

	if (0 < a3)
	{
		if (0x11 < a3)
		{
			a3 = 0x12;
		}
		dword_6FBA7608 = dword_6FBA7608 + 1;
		puVar2 = (uint32_t*)D2_ALLOC(0x34);
		uVar3 = 6;
		if (pUnit != nullptr)
		{
			uVar3 = pUnit->dwUnitType;
		}
		*puVar2 = uVar3;
		if (pUnit == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pUnit->dwUnitId;
		}
		puVar2[1] = uVar3;
		if ((pUnit == nullptr) || ((pUnit->dwFlags >> 0x15 & 1) == 0))
		{
			*(uint8_t*)(puVar2 + 2) = 0;
		}
		else
		{
			*(uint8_t*)(puVar2 + 2) = 1;
		}
		uVar3 = UNITS_GetPrecisionX(pUnit);
		puVar2[4] = (uVar3 >> 0xd) + 4;
		uVar3 = UNITS_GetPrecisionY(pUnit);
		*(uint8_t*)(puVar2 + 9) = (uint8_t)a4;
		puVar2[5] = (uVar3 >> 0xd) + 4;
		*(uint8_t*)((int)puVar2 + 0x25) = (uint8_t)a5;
		puVar2[6] = a3 * 8;
		puVar2[7] = a3 * 8;
		pvVar4 = nullptr;
		puVar2[3] = a2;
		puVar2[8] = 0;
		*(uint8_t*)((int)puVar2 + 0x26) = (uint8_t)a6;
		*(uint8_t*)((int)puVar2 + 0x27) = (uint8_t)a7;
		puVar2[10] = dword_6FBA7604;
		puVar2[0xb] = 0;
		if (a2 == 2)
		{
			iVar1 = a3 * 2 + 1;
			pvVar4 = D2_ALLOC(iVar1 * iVar1 * 4);
		}
		puVar2[0xc] = (uint32_t)pvVar4;
		dword_6FBA7604 = (int)puVar2;
		return puVar2;
	}
	return nullptr;
}

//D2Client.0x6FAA43A0
void __fastcall sub_6FAA43A0(int ptLight, int a2)
{
	if (0 < a2)
	{
		if (0x11 < a2)
		{
			a2 = 0x12;
		}
		D2_ASSERT(ptLight);
		*(int*)(ptLight + 0x1c) = a2 * 8;
	}
}

//D2Client.0x6FAA43E0
void __fastcall sub_6FAA43E0(int ptLight, int a2)
{
	if (0 < a2)
	{
		if (0x11 < a2)
		{
			a2 = 0x12;
		}
		D2_ASSERT(ptLight);
		if (0x11 < a2)
		{
			a2 = 0x12;
		}
		*(int*)(ptLight + 0x18) = a2 * 8;
		*(int*)(ptLight + 0x1c) = a2 * 8;
		if (*(int*)(ptLight + 0xc) == 2)
		{
			*(uint32_t*)(ptLight + 0x2c) = 0;
			if (*(void**)(ptLight + 0x30) != nullptr)
			{
				D2_FREE(*(void**)(ptLight + 0x30));
			}
			*(uint32_t*)(ptLight + 0x30) = 0;
		}
	}
}

//D2Client.0x6FAA4460
int __fastcall sub_6FAA4460(int ptLight)
{
	D2_ASSERT(ptLight);
	return *(int*)(ptLight + 0x18) >> 3;
}

//D2Client.0x6FAA4490
void __fastcall sub_6FAA4490(int ptLight, uint8_t a2, uint8_t a3, uint8_t a4)
{
	D2_ASSERT(ptLight);
	*(uint8_t*)(ptLight + 0x25) = a2;
	*(uint8_t*)(ptLight + 0x26) = a3;
	*(uint8_t*)(ptLight + 0x27) = a4;
}

//D2Client.0x6FAA44D0
void __fastcall sub_6FAA44D0(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;

	if (a1 == 0)
	{
		return;
	}
	iVar1 = dword_6FBA7604;
	iVar3 = 0;
	if (dword_6FBA7604 != 0)
	{
		do
		{
			iVar2 = iVar1;
			if (iVar2 == a1)
			{
				if (iVar2 != 0)
				{
					if (iVar3 == 0)
					{
						dword_6FBA7604 = *(int*)(iVar2 + 0x28);
					}
					else
					{
						*(uint32_t*)(iVar3 + 0x28) = *(uint32_t*)(iVar2 + 0x28);
					}
					if (*(void**)(a1 + 0x30) != nullptr)
					{
						D2_FREE(*(void**)(a1 + 0x30));
					}
					D2_FREE((void*)a1);
					byte_6FBA760C = byte_6FBA760C + 1;
					return;
				}
				break;
			}
			iVar1 = *(int*)(iVar2 + 0x28);
			iVar3 = iVar2;
		} while (*(int*)(iVar2 + 0x28) != 0);
	}
	FOG_DisplayAssert("ptCurr", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAA4560
void __fastcall sub_6FAA4560(int ptLight)
{
	D2_ASSERT(ptLight);
	*(uint32_t*)(ptLight + 0x20) = 1;
	*(uint32_t*)(ptLight + 0x1c) = 0;
	D2_ASSERT(*(int*)(ptLight + 0xc) != 2);
}

//D2Client.0x6FAA45C0
void __fastcall sub_6FAA45C0(D2ActiveRoomStrc* pActiveRoom, uint32_t* a2, uint8_t* a3, uint8_t* a4, uint8_t* a5, uint32_t a6)
{
	uint32_t uVar1;
	uint32_t uStack_4;

	uStack_4 = (uint32_t)((uint16_t)pActiveRoom & 0xff);
	if (a6 != 0)
	{
		uVar1 = sub_6FAB9FE0(pActiveRoom, (uint8_t*)((int)&uStack_4 + 1),
		    (uint8_t*)((int)&uStack_4 + 2), (uint8_t*)((int)&uStack_4 + 3));
		if ((((*(uint8_t*)((uint8_t*)&uStack_4 + 1)) != '\0') || ((*(uint8_t*)((uint8_t*)&uStack_4 + 2)) != '\0')) || ((*(uint8_t*)((uint8_t*)&uStack_4 + 3)) != '\0'))
			goto LAB_6faa466c;
	}
	DUNGEON_GetRGB_IntensityFromRoom(pActiveRoom, (uint8_t*)&a6, (uint8_t*)((int)&uStack_4 + 1), (uint8_t*)((int)&uStack_4 + 2),
	    (uint8_t*)((int)&uStack_4 + 3));
	uVar1 = a6 & 0xff;
	if ((((*(uint8_t*)((uint8_t*)&uStack_4 + 1)) == '\0') && ((*(uint8_t*)((uint8_t*)&uStack_4 + 2)) == '\0')) && ((*(uint8_t*)((uint8_t*)&uStack_4 + 3)) == '\0'))
	{
		ENVIRONMENT_GetLightColorFromAct(ghAct, (uint8_t*)((int)&uStack_4 + 1), (uint8_t*)((int)&uStack_4 + 2),
		    (uint8_t*)((int)&uStack_4 + 3));
		uVar1 = ENVIRONMENT_GetIntensityFromAct(ghAct);
	}
LAB_6faa466c:
	*a2 = uVar1;
	*a3 = (*(uint8_t*)((uint8_t*)&uStack_4 + 1));
	*a4 = (*(uint8_t*)((uint8_t*)&uStack_4 + 2));
	*a5 = (*(uint8_t*)((uint8_t*)&uStack_4 + 3));
}

//D2Client.0x6FAA46A0
void __cdecl sub_6FAA46A0()
{
	sub_6FAA46B0(1);
}

//D2Client.0x6FAA46B0
void __fastcall sub_6FAA46B0(int a1)
{
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pDVar1;
	uint32_t uVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t uVar7;
	int iVar8;
	int iVar9;
	uint32_t* puVar10;
	uint16_t uStack_4a;
	uint32_t uStack_48;
	D2ActiveRoomStrc** ppDStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_38;
	D2ActiveRoomStrc* pDStack_34;
	uint32_t uStack_30;
	uint32_t uStack_2c;
	uint32_t uStack_28;
	uint32_t uStack_24;
	D2DrlgCoordsStrc DStack_20;

	pUnit = CUNIT_GetPlayer();
	if (((pUnit == nullptr) ||
	        (pDVar1 = UNITS_GetRoom(pUnit), pDVar1 == nullptr)) ||
	    (a1 != 0))
	{
		puVar10 = &dword_6FBA2E00;
		do
		{
			iVar8 = 0x30;
			puVar4 = puVar10;
			do
			{
				*puVar4 = 0;
				*(uint8_t*)(puVar4 + 1) = 0;
				*(uint8_t*)((int)puVar4 + 5) = 0;
				*(uint8_t*)((int)puVar4 + 6) = 0;
				*(uint8_t*)((int)puVar4 + 7) = 0;
				puVar4 = puVar4 + 2;
				iVar8 = iVar8 + -1;
			} while (iVar8 != 0);
			puVar10 = puVar10 + 0x60;
		} while ((int)puVar10 < (int)&tbl_6FBA7481);
	}
	else
	{
		pDStack_34 = pDVar1;
		DUNGEON_GetAdjacentRoomsListFromRoom(pDVar1, &ppDStack_44, &iStack_38);
		uStack_48 = uStack_48 & 0xffffff00;
		uStack_4a = 0;
		uVar2 = sub_6FAB9FE0(pDVar1, (uint8_t*)&uStack_48, (uint8_t*)((int)&uStack_4a + 1),
		    (uint8_t*)(&uStack_4a));
		if ((((char)uStack_48 == '\0') && ((*(uint8_t*)((uint8_t*)&uStack_4a + 1)) == '\0')) && ((uint8_t)uStack_4a == 0))
		{
			DUNGEON_GetRGB_IntensityFromRoom(pDVar1, (uint8_t*)&uStack_3c, (uint8_t*)&uStack_48, (uint8_t*)((int)&uStack_4a + 1),
			    (uint8_t*)&uStack_4a);
			uVar2 = uStack_3c & 0xff;
			if ((((char)uStack_48 == '\0') && ((*(uint8_t*)((uint8_t*)&uStack_4a + 1)) == '\0')) && ((uint8_t)uStack_4a == 0))
			{
				ENVIRONMENT_GetLightColorFromAct(ghAct, (uint8_t*)&uStack_48, (uint8_t*)((int)&uStack_4a + 1), (uint8_t*)&uStack_4a);
				uVar2 = ENVIRONMENT_GetIntensityFromAct(ghAct);
			}
		}
		puVar10 = &dword_6FBA2E00;
		uVar5 = ((uint32_t)CONCAT11((uint8_t)uStack_4a, (*(uint8_t*)((uint8_t*)&uStack_4a + 1))) << 8 | uStack_48 & 0xff) << 8 | uVar2;
		do
		{
			iVar8 = 0x30;
			puVar4 = puVar10;
			do
			{
				(*(uint8_t*)((uint8_t*)&uStack_3c + 0)) = (uint8_t)(uVar5 >> 0x10);
				*puVar4 = 0;
				*(uint8_t*)((int)puVar4 + 6) = (uint8_t)uStack_3c;
				(*(uint8_t*)((uint8_t*)&uStack_40 + 0)) = (uint8_t)(uVar5 >> 0x18);
				*(char*)(puVar4 + 1) = (char)uVar2;
				*(char*)((int)puVar4 + 5) = (char)(uVar5 >> 8);
				*(uint8_t*)((int)puVar4 + 7) = (uint8_t)uStack_40;
				puVar4 = puVar4 + 2;
				iVar8 = iVar8 + -1;
			} while (iVar8 != 0);
			puVar10 = puVar10 + 0x60;
		} while ((int)puVar10 < (int)&tbl_6FBA7481);
		uStack_3c = 0;
		uStack_40 = uVar5 >> 0x18;
		if (0 < iStack_38)
		{
			do
			{
				uVar2 = uStack_3c;
				pDVar1 = ppDStack_44[uStack_3c];
				if (pDVar1 != pDStack_34)
				{
					uStack_48 = uStack_48 & 0xffffff00;
					uStack_4a = 0;
					uVar5 = sub_6FAB9FE0(pDVar1, (uint8_t*)&uStack_48, (uint8_t*)&uStack_4a,
					    (uint8_t*)((int)&uStack_4a + 1));
					if ((((char)uStack_48 == '\0') && ((uint8_t)uStack_4a == 0)) && ((*(uint8_t*)((uint8_t*)&uStack_4a + 1)) == '\0'))
					{
						DUNGEON_GetRGB_IntensityFromRoom(pDVar1, (uint8_t*)&uStack_30, (uint8_t*)&uStack_48, (uint8_t*)&uStack_4a,
						    (uint8_t*)((int)&uStack_4a + 1));
						uVar5 = uStack_30 & 0xff;
						if ((((char)uStack_48 == '\0') && ((uint8_t)uStack_4a == 0)) && ((*(uint8_t*)((uint8_t*)&uStack_4a + 1)) == '\0'))
						{
							ENVIRONMENT_GetLightColorFromAct(ghAct, (uint8_t*)&uStack_48, (uint8_t*)&uStack_4a,
							    (uint8_t*)((int)&uStack_4a + 1));
							uVar5 = ENVIRONMENT_GetIntensityFromAct(ghAct);
						}
					}
					uVar7 = ((uint32_t)uStack_4a << 8 | uStack_48 & 0xff) << 8 | uVar5;
					DUNGEON_GetRoomCoordinates(ppDStack_44[uVar2], &DStack_20);
					iVar9 = DStack_20.nSubtileX - dword_6FB9E9E0;
					iVar8 = DStack_20.nSubtileWidth + iVar9;
					if ((iVar9 < 0x31) && (-1 < iVar8))
					{
						iVar3 = DStack_20.nSubtileY - dword_6FB9E9E4;
						iVar6 = DStack_20.nSubtileHeight + iVar3;
						if ((iVar3 < 0x31) && (-1 < iVar6))
						{
							if (iVar9 < 0)
							{
								iVar9 = 0;
							}
							if (0x2f < iVar8)
							{
								iVar8 = 0x2f;
							}
							if (iVar3 < 0)
							{
								iVar3 = 0;
							}
							if (0x2f < iVar6)
							{
								iVar6 = 0x2f;
							}
							if (iVar3 <= iVar6)
							{
								uStack_40 = (iVar6 - iVar3) + 1;
								puVar10 = &dword_6FBA2E00 + (iVar3 * 0x30 + iVar9) * 2;
								do
								{
									if (iVar9 <= iVar8)
									{
										uStack_2c = uVar7 >> 8;
										iVar3 = (iVar8 - iVar9) + 1;
										puVar4 = puVar10;
										do
										{
											*(char*)((int)puVar4 + 5) = (char)(uVar7 >> 8);
											(*(uint8_t*)((uint8_t*)&uStack_28 + 0)) = (uint8_t)(uVar7 >> 0x10);
											*(uint8_t*)((int)puVar4 + 6) = (uint8_t)uStack_28;
											(*(uint8_t*)((uint8_t*)&uStack_24 + 0)) = (uint8_t)(uVar7 >> 0x18);
											*puVar4 = 0;
											*(char*)(puVar4 + 1) = (char)uVar5;
											*(uint8_t*)((int)puVar4 + 7) = (uint8_t)uStack_24;
											puVar4 = puVar4 + 2;
											iVar3 = iVar3 + -1;
											uStack_28 = uVar7 >> 0x10;
											uStack_24 = uVar7 >> 0x18;
										} while (iVar3 != 0);
									}
									puVar10 = puVar10 + 0x60;
									uStack_40 = uStack_40 + -1;
								} while (uStack_40 != 0);
								uStack_40 = 0;
								uVar2 = uStack_3c;
							}
						}
					}
				}
				uStack_3c = uVar2 + 1;
			} while ((int)uStack_3c < iStack_38);
			return;
		}
	}
}

//D2Client.0x6FAA4A30
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAA4A30()
{
	int64_t lVar1;
	D2DrlgActStrc* in_ECX;
	int iVar2;
	void* in_EDX;

	DUNGEON_SetActCallbackFunc(in_ECX, (ACTCALLBACKFN)(in_EDX));
	*(uint32_t*)byte_6FBA29F8 = (uint32_t)0x0;
	iVar2 = 1;
	do
	{
		lVar1 = (int64_t)iVar2;
		iVar2 = iVar2 + 1;
		*(int*)(iVar2 * 4 + (int)&tbl_6FBA29F4) = (int)(0x10000 / lVar1);
	} while (iVar2 < 0x100);
}

//D2Client.0x6FAA4A70
// TODO: decompilation needs review (unaff_)
int __cdecl sub_6FAA4A70()
{
	int iVar1;
	DWORD DVar2;
	int unaff_ESI;
	int iVar3;

	iVar3 = 2;
	iVar1 = D2GFX_CheckLowQuality();
	if (iVar1 == 0)
	{
	LAB_6faa4a8d:
		iVar1 = sub_6FAABFC0();
		if (9 < iVar1)
		{
			if (0xc < iVar1)
			{
				if (0xf < iVar1)
					goto LAB_6faa4ab4;
				if (0 < dword_6FBA7614)
				{
					return unaff_ESI;
				}
			}
			iVar3 = 1;
			goto LAB_6faa4ab4;
		}
	}
	else
	{
		iVar1 = sub_6FB39500();
		if (iVar1 != 0)
		{
			iVar3 = 1;
			goto LAB_6faa4a8d;
		}
	}
	iVar3 = 0;
LAB_6faa4ab4:
	iVar1 = dword_6FBA7614;
	DVar2 = dword_6FBA7618;
	if ((iVar3 != dword_6FBA7614) &&
	    (DVar2 = GetTickCount(), iVar1 = iVar3, DVar2 - dword_6FBA7618 < 0x7d1))
	{
		return unaff_ESI;
	}
	dword_6FBA7618 = DVar2;
	dword_6FBA7614 = iVar1;
	return unaff_ESI;
}

//D2Client.0x6FAA4AF0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAA4AF0()
{
	int iVar1;
	int iVar2;
	int* piVar3;
	int* piVar4;
	uint16_t uVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	int32_t DVar8;
	D2ActiveRoomStrc* pDVar9;
	int extraout_EAX;
	uint32_t uVar10;
	int iVar11;
	int iStack_18;
	uint32_t uStack_14;
	int iStack_10;
	int iStack_c;
	D2ActiveRoomStrc** ppDStack_8;
	D2UnitStrc* pDStack_4;

	pDVar6 = CUNIT_GetPlayer();
	uVar10 = pDVar6->dwUnitType;
	if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
	{
		iVar7 = pDVar6->pDynamicPath->dwClientCoordY;
	}
	else if (pDVar6->pDynamicPath == nullptr)
	{
		iVar7 = 0;
	}
	else
	{
		iVar7 = PATH_GetXPosition(pDVar6->pDynamicPath);
	}
	uVar10 = pDVar6->dwUnitType;
	if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
	{
		DVar8 = (*(int32_t*)&pDVar6->pDynamicPath->tTargetCoord);
	}
	else if (pDVar6->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
	}
	else
	{
		DVar8 = (int32_t)PATH_GetYPosition(pDVar6->pDynamicPath);
	}
	dword_6FB9E9E0 = iVar7 + -0x18;
	dword_6FB9E9E4 = (int)DVar8 + -0x18;
	dword_6FB9E9E8 = iVar7 + 0x18;
	dword_6FB9E9EC = (int)DVar8 + 0x18;
	sub_6FAA46B0(0);
	pDStack_4 = CUNIT_GetPlayer();
	if ((pDStack_4 != nullptr) &&
	    (pDVar9 = UNITS_GetRoom(pDStack_4), pDVar9 != nullptr))
	{
		iStack_18 = 0;
		iStack_c = 0;
		do
		{
			iStack_10 = 0;
			do
			{
				iVar11 = iStack_10;
				iVar7 = dword_6FB9E9E0 + iStack_10;
				iVar1 = dword_6FB9E9E4 + iStack_18;
				if (pDVar9 == nullptr)
				{
				LAB_6faa4c52:
					pDVar9 = UNITS_GetRoom(pDStack_4);
				}
				else
				{
					iVar2 = (pDVar9->tCoords).nSubtileX;
					if ((((iVar7 < iVar2) || ((pDVar9->tCoords).nSubtileWidth + iVar2 <= iVar7)) ||
					        (iVar2 = (pDVar9->tCoords).nSubtileY, iVar1 < iVar2)) ||
					    ((pDVar9->tCoords).nSubtileHeight + iVar2 <= iVar1))
					{
						ppDStack_8 = nullptr;
						uStack_14 = 0;
						DUNGEON_GetAdjacentRoomsListFromRoom(pDVar9, &ppDStack_8, (int*)&uStack_14);
						uVar10 = 0;
						if (uStack_14 != 0)
						{
							do
							{
								pDVar9 = ppDStack_8[uVar10];
								if (((pDVar9 != nullptr) &&
								        (iVar2 = (pDVar9->tCoords).nSubtileX, iVar2 <= iVar7)) &&
								    ((iVar11 = iStack_10, iVar7 < (pDVar9->tCoords).nSubtileWidth + iVar2 &&
								                              ((iVar2 = (pDVar9->tCoords).nSubtileY, iVar2 <= iVar1 &&
								                                                                         (iVar1 < (pDVar9->tCoords).nSubtileHeight + iVar2))))))
								{
									pDVar9 = ppDStack_8[uVar10];
									goto LAB_6faa4c4e;
								}
								uVar10 = uVar10 + 1;
							} while (uVar10 < uStack_14);
						}
						goto LAB_6faa4c52;
					}
				LAB_6faa4c4e:
					iVar11 = iStack_10;
					if (pDVar9 == nullptr)
						goto LAB_6faa4c52;
				}
				uVar5 = COLLISION_CheckMask(pDVar9, dword_6FB9E9E0 + iVar11, dword_6FB9E9E4 + iStack_18, 0x22);
				if (uVar5 != 0)
				{
					(&dword_6FBA2E00)[(iStack_c + iVar11) * 2] = 1;
				}
				iStack_10 = iVar11 + 1;
			} while (iStack_10 < 0x30);
			iStack_c = iStack_c + 0x30;
			iStack_18 = iStack_18 + 1;
		} while (iStack_c < 0x900);
	}
	sub_6FAA4A70();
	dword_6FBA7610 = 0;
	piVar4 = (int*)dword_6FBA7604;
	while (piVar4 != nullptr)
	{
		dword_6FBA7610 = dword_6FBA7610 + 1;
		piVar3 = (int*)piVar4[10];
		sub_6FAA4D00(piVar4, extraout_EAX);
		piVar4 = piVar3;
	}
}

//D2Client.0x6FAA4D00
void __fastcall sub_6FAA4D00(int* a1, int a2)
{
	int iVar1;
	uint8_t bVar2;
	D2UnitStrc* pUnit;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	void* pvVar10;
	uint32_t uVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	int* piVar15;
	int* piVar16;
	uint32_t* puVar17;
	int iVar18;
	int iStack_3c;
	int iStack_38;
	int iStack_34;
	int iStack_30;
	int iStack_2c;
	int iStack_28;
	int iStack_24;
	int iStack_20;
	int iStack_1c;

	if ((a1[8] == 0) && (iVar3 = *a1, iVar3 != 6))
	{
		if ((char)a1[2] == '\0')
		{
			pUnit = sub_6FB269F0(a1[1], iVar3);
		}
		else
		{
			pUnit = sub_6FB26A60(a1[1], iVar3);
		}
		if (pUnit != nullptr)
		{
			iVar3 = UNITS_GetPrecisionX(pUnit);
			iVar4 = UNITS_GetPrecisionY(pUnit);
			a1[4] = (iVar3 >> 0xd) + 4;
			a1[5] = (iVar4 >> 0xd) + 4;
		}
	}
	if (a1[7] != a1[6])
	{
		if (a1[3] == 2)
		{
			a1[0xb] = 0;
			if ((void*)a1[0xc] != nullptr)
			{
				D2_FREE((void*)a1[0xc]);
			}
			a1[0xc] = 0;
		}
		iVar3 = a1[6];
		if (iVar3 < a1[7])
		{
			iVar3 = iVar3 + 8;
		}
		else
		{
			iVar3 = iVar3 + -8;
		}
		a1[6] = iVar3;
	}
	if (0xff < a1[6])
	{
		a1[6] = 0xf8;
	}
	if ((a1[8] != 0) && (a1[6] < 1))
	{
		sub_6FAA44D0((int)a1);
		return;
	}
	if ((a1[3] == 0) && (1 < a2))
	{
		iVar3 = a1[6];
		if ((0 < iVar3) && (iVar3 < 0x100))
		{
			iVar4 = (a1[4] - (a1[4] & 7U)) - iVar3;
			iVar5 = (a1[5] - (a1[5] & 7U)) - iVar3;
			iVar3 = iVar3 * 2 >> 3;
			if ((((iVar4 >> 3 <= dword_6FB9E9E8) && (dword_6FB9E9E0 <= (iVar4 >> 3) + 1 + iVar3)) &&
			        (iVar6 = iVar5 >> 3, iVar6 <= dword_6FB9E9EC)) &&
			    (dword_6FB9E9E4 <= iVar6 + 1 + iVar3))
			{
				puVar17 = &dword_6FB9E9F8;
				for (iVar6 = 0x400; iVar6 != 0; iVar6 = iVar6 + -1)
				{
					*puVar17 = 0;
					puVar17 = puVar17 + 1;
				}
				iVar6 = a1[6];
				iVar13 = a1[4] >> 3;
				iVar7 = a1[5] >> 3;
				sub_6FAA54D0((int)a1);
				iStack_3c = 2;
				if (1 < iVar6 >> 3)
				{
					iStack_28 = iVar13 * 8 + 0x14;
					iVar12 = 0x1e;
					iStack_24 = iVar7 * 8 + 0x14;
					iStack_1c = iVar7 * 8 + -0xc;
					iStack_20 = iVar13 * 8 + -0xc;
					do
					{
						if (iVar12 < 0x21)
						{
							iStack_34 = iVar7 * 8 + 4;
							iStack_38 = iVar13 * 8 + 4;
							iVar14 = 0x20;
							iVar18 = 0x20;
							iStack_30 = iStack_38;
							iStack_2c = iStack_34;
							do
							{
								sub_6FAA55D0(iStack_30, iStack_1c, (int)a1);
								sub_6FAA5680(iVar14, iVar12);
								sub_6FAA55D0(iStack_38, iStack_1c, (int)a1);
								sub_6FAA5680(iVar18, iVar12);
								sub_6FAA55D0(iStack_30, iStack_24, (int)a1);
								sub_6FAA5680(iVar14, iStack_3c + 0x20);
								sub_6FAA55D0(iStack_38, iStack_24, (int)a1);
								sub_6FAA5680(iVar18, iStack_3c + 0x20);
								sub_6FAA55D0(iStack_28, iStack_2c, (int)a1);
								sub_6FAA5680(iStack_3c + 0x20, iVar14);
								sub_6FAA55D0(iStack_28, iStack_34, (int)a1);
								sub_6FAA5680(iStack_3c + 0x20, iVar18);
								sub_6FAA55D0(iStack_20, iStack_2c, (int)a1);
								sub_6FAA5680(iVar12, iVar14);
								sub_6FAA55D0(iStack_20, iStack_34, (int)a1);
								sub_6FAA5680(iVar12, iVar18);
								iStack_38 = iStack_38 + 8;
								iStack_34 = iStack_34 + 8;
								iStack_30 = iStack_30 + -8;
								iStack_2c = iStack_2c + -8;
								iVar14 = iVar14 + -1;
								iVar1 = iVar18 + -0x1f;
								iVar18 = iVar18 + 1;
							} while (iVar1 <= iStack_3c);
						}
						iStack_28 = iStack_28 + 8;
						iStack_24 = iStack_24 + 8;
						iStack_3c = iStack_3c + 1;
						iStack_20 = iStack_20 + -8;
						iStack_1c = iStack_1c + -8;
						iVar12 = iVar12 + -1;
					} while (iStack_3c <= iVar6 >> 3);
				}
				iVar6 = a1[6];
				bVar2 = *(uint8_t*)(a1 + 9);
				if (-1 < iVar3)
				{
					iVar3 = iVar3 + 1;
					piVar15 = (int*)(&dword_6FB9E9F8 + (0x20 - (iVar6 >> 3)) * 0x41);
					iStack_28 = iVar3;
					iStack_1c = iVar5;
					do
					{
						uVar8 = a1[5] - iStack_1c;
						iVar5 = iVar4;
						piVar16 = piVar15;
						iStack_20 = iVar3;
						if ((int)uVar8 < 0)
						{
							uVar8 = -uVar8;
						}
						do
						{
							iVar7 = *piVar16;
							if (iVar7 < 0x10)
							{
								uVar9 = a1[4] - iVar5;
								if ((int)uVar9 < 0)
								{
									uVar9 = -uVar9;
								}
								uVar9 = DFLOOR_ApproximateDistance(uVar9, uVar8);
								iVar13 = 8 - (iVar7 >> 1);
								iVar7 = ((int)((a1[6] - uVar9) * ((int)((uint32_t)bVar2 << 0x10) / iVar6)) >> 0x10) * iVar13 >> 3;
								if (0 < iVar7)
								{
									uVar11 = (uint32_t)(uVar9 >> 8);
									sub_6FAA51D0(iVar5, iStack_1c, iVar7,
									    CONCAT31(uVar11, *(uint8_t*)((int)a1 + 0x25)),
									    CONCAT31((int32_t)((uint32_t)iVar13 >> 8),
									        *(uint8_t*)((int)a1 + 0x26)),
									    CONCAT31(uVar11, *(uint8_t*)((int)a1 + 0x27)));
								}
							}
							iStack_20 = iStack_20 + -1;
							iVar5 = iVar5 + 8;
							piVar16 = piVar16 + 1;
						} while (iStack_20 != 0);
						piVar15 = piVar15 + 0x40;
						iStack_1c = iStack_1c + 8;
						iStack_28 = iStack_28 + -1;
					} while (iStack_28 != 0);
				}
			}
		}
		return;
	}
	if (a1[3] != 2)
	{
		sub_6FAA5300(a1, a2);
		return;
	}
	if (a1[0xb] == 0)
	{
		if (a1[0xc] == 0)
		{
			iVar3 = (a1[6] >> 3) * 2 + 1;
			pvVar10 = D2_ALLOC(iVar3 * iVar3 * 4);
			a1[0xc] = (int)pvVar10;
		}
		sub_6FAA57E0(a1);
	}
	sub_6FAA5BC0((int)a1);
}

//D2Client.0x6FAA51D0
void __fastcall sub_6FAA51D0(int a1, int a2, int a3, uint32_t a4, uint32_t a5, uint32_t a6)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;

	iVar4 = (a1 >> 3) - dword_6FB9E9E0;
	if ((((-1 < iVar4) && (iVar4 < 0x30)) && (iVar2 = (a2 >> 3) - dword_6FB9E9E4, -1 < iVar2)) &&
	    (iVar2 < 0x30))
	{
		iVar4 = iVar2 * 0x30 + iVar4;
		uVar5 = (uint32_t)(uint8_t)(&byte_6FBA2E04)[iVar4 * 8];
		iVar4 = iVar4 * 8;
		iVar2 = uVar5 + a3;
		if (0xfe < iVar2)
		{
			iVar2 = 0xff;
		}
		if (dword_6FB74C88 != 0)
		{
			iVar1 = *(int*)(byte_6FBA29F8 + iVar2 * 4);
			uVar3 = ((uint8_t)(&byte_6FBA2E05)[iVar4] * uVar5 + (a4 & 0xff) * a3) * iVar1 >> 0x10;
			if (0xff < uVar3)
			{
				uVar3 = 0xff;
			}
			uVar6 = ((uint8_t)(&byte_6FBA2E06)[iVar4] * uVar5 + (a5 & 0xff) * a3) * iVar1 >> 0x10;
			if (0xff < uVar6)
			{
				uVar6 = 0xff;
			}
			uVar5 = ((uint8_t)(&byte_6FBA2E07)[iVar4] * uVar5 + (a6 & 0xff) * a3) * iVar1 >> 0x10;
			if (0xff < uVar5)
			{
				uVar5 = 0xff;
			}
			(&byte_6FBA2E05)[iVar4] = (char)uVar3;
			(&byte_6FBA2E04)[iVar4] = (char)iVar2;
			(&byte_6FBA2E06)[iVar4] = (char)uVar6;
			(&byte_6FBA2E07)[iVar4] = (char)uVar5;
			return;
		}
		(&byte_6FBA2E04)[iVar4] = (char)iVar2;
		(&byte_6FBA2E05)[iVar4] = 0;
		(&byte_6FBA2E06)[iVar4] = 0;
		(&byte_6FBA2E07)[iVar4] = 0;
	}
}

//D2Client.0x6FAA5300
void __fastcall sub_6FAA5300(int* a1, int a2)
{
	uint8_t bVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	uint32_t uVar10;
	int iVar11;
	int iVar12;
	int local_18;
	int local_14;
	int local_10;

	iVar11 = a1[6];
	if ((0 < iVar11) && (iVar11 < 0x100))
	{
		if (a2 == 0)
		{
			iVar4 = *a1;
			if (iVar4 == 0)
			{
				pDVar3 = CUNIT_GetPlayer();
				if (pDVar3 == nullptr)
				{
					uVar6 = 0xffffffff;
				}
				else
				{
					uVar6 = pDVar3->dwUnitId;
				}
				if ((a1[1] != uVar6) && (0xf < iVar11))
				{
					iVar11 = 0x10;
				}
			}
			else if (iVar4 == 1)
			{
				iVar11 = 8;
			}
			else if (iVar4 == 3)
			{
				return;
			}
		}
		iVar4 = (a1[4] - (a1[4] & 7U)) - iVar11;
		local_18 = (a1[5] - (a1[5] & 7U)) - iVar11;
		iVar5 = iVar4 >> 3;
		iVar9 = iVar11 * 2 >> 3;
		if ((((iVar5 <= dword_6FB9E9E8) && (dword_6FB9E9E0 <= iVar5 + 1 + iVar9)) &&
		        (local_18 >> 3 <= dword_6FB9E9EC)) &&
		    ((dword_6FB9E9E4 <= (local_18 >> 3) + 1 + iVar9 && (bVar1 = *(uint8_t*)(a1 + 9), -1 < iVar9))))
		{
			local_10 = iVar9 + 1;
			do
			{
				uVar6 = a1[5] - local_18;
				if ((int)uVar6 < 0)
				{
					uVar6 = -uVar6;
				}
				iVar12 = (uVar6 ^ (int)uVar6 >> 0x1f) - ((int)uVar6 >> 0x1f);
				iVar5 = iVar4;
				local_14 = iVar9 + 1;
				do
				{
					uVar6 = a1[4] - iVar5;
					if ((int)uVar6 < 0)
					{
						uVar6 = -uVar6;
					}
					iVar7 = (uVar6 ^ (int)uVar6 >> 0x1f) - ((int)uVar6 >> 0x1f);
					iVar2 = iVar7;
					iVar8 = iVar12;
					if (iVar12 <= iVar7)
					{
						iVar2 = iVar12;
						iVar8 = iVar7;
					}
					uVar6 = iVar8 * 0x3d7 + iVar2 * 0x197;
					iVar8 = (int)((iVar11 - (uVar6 >> 10)) * ((int)((uint32_t)bVar1 << 0x10) / iVar11)) >> 0x10;
					if (0 < iVar8)
					{
						uVar10 = (uint32_t)(uVar6 >> 0x12);
						sub_6FAA51D0(iVar5, local_18, iVar8, CONCAT31(uVar10, *(uint8_t*)((int)a1 + 0x25)),
						    CONCAT31((int32_t)((uint32_t)(iVar2 * 0xcb) >> 8),
						        *(uint8_t*)((int)a1 + 0x26)),
						    CONCAT31(uVar10, *(uint8_t*)((int)a1 + 0x27)));
					}
					iVar5 = iVar5 + 8;
					local_14 = local_14 + -1;
				} while (local_14 != 0);
				local_18 = local_18 + 8;
				local_10 = local_10 + -1;
			} while (local_10 != 0);
		}
	}
}

//D2Client.0x6FAA54D0
void __fastcall sub_6FAA54D0(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int* piVar6;
	int* piVar7;
	int iVar8;
	int iVar9;
	uint32_t local_10;
	int local_c;

	iVar8 = *(int*)(a1 + 0x18);
	iVar1 = (*(uint32_t*)(a1 + 0x10) - (*(uint32_t*)(a1 + 0x10) & 7)) - iVar8;
	iVar2 = (*(uint32_t*)(a1 + 0x14) - (*(uint32_t*)(a1 + 0x14) & 7)) - iVar8;
	iVar5 = iVar8 * 2 >> 3;
	if (-1 < iVar5)
	{
		iVar5 = iVar5 + 1;
		piVar6 = (int*)(dword_6FB9A9E0 + (0x20 - (iVar8 >> 3)) * 0x41);
		iVar8 = iVar1;
		iVar9 = iVar5;
		local_c = iVar5;
		piVar7 = piVar6;
		do
		{
			do
			{
				iVar4 = (iVar8 >> 3) - dword_6FB9E9E0;
				if (iVar4 < 0)
				{
					local_10 = 1;
				}
				else if (iVar4 < 0x30)
				{
					iVar3 = (iVar2 >> 3) - dword_6FB9E9E4;
					if (iVar3 < 0)
					{
						local_10 = 1;
					}
					else if (iVar3 < 0x30)
					{
						local_10 = (uint32_t) * (uint8_t*)(&dword_6FBA2E00 + (iVar3 * 0x30 + iVar4) * 2);
					}
					else
					{
						local_10 = 1;
					}
				}
				else
				{
					local_10 = 1;
				}
				*piVar6 = local_10 << 4;
				iVar9 = iVar9 + -1;
				piVar6 = piVar6 + 1;
				iVar8 = iVar8 + 8;
			} while (iVar9 != 0);
			piVar6 = piVar7 + 0x40;
			iVar2 = iVar2 + 8;
			local_c = local_c + -1;
			iVar8 = iVar1;
			iVar9 = iVar5;
			piVar7 = piVar6;
		} while (local_c != 0);
	}
}

//D2Client.0x6FAA55D0
void __fastcall sub_6FAA55D0(int a1, int a2, int a3)
{
	int iVar1;
	int iVar2;

	iVar2 = *(int*)(a3 + 0x10) - a1;
	iVar1 = *(int*)(a3 + 0x14) - a2;
	if (iVar2 == 0)
	{
		if (iVar1 == 0)
		{
			dword_6FBA7600 = iVar1;
			return;
		}
	}
	else if (iVar2 < 0)
	{
		dword_6FB9E9F0 = -1;
		iVar2 = -iVar2;
		goto LAB_6faa560a;
	}
	dword_6FB9E9F0 = 1;
LAB_6faa560a:
	if (iVar1 < 0)
	{
		dword_6FB9A9D8 = -1;
		iVar1 = -iVar1;
	}
	else
	{
		dword_6FB9A9D8 = 1;
	}
	if (iVar2 == 0)
	{
		dword_6FBA7600 = 4;
		return;
	}
	if (iVar1 == 0)
	{
		dword_6FBA7600 = 1;
		return;
	}
	if (iVar1 <= iVar2)
	{
		dword_6FBA7600 = 2;
		dword_6FBA2DF8 = (iVar1 << 8) / iVar2;
		return;
	}
	dword_6FBA7600 = 3;
	dword_6FBA2DF8 = (iVar2 << 8) / iVar1;
}

//D2Client.0x6FAA5680
void __fastcall sub_6FAA5680(int a1, int a2)
{
	int iVar1;
	int iVar2;
	int iVar3;

	switch (dword_6FBA7600)
	{
	default:
		goto switchD_6faa5691_caseD_0;
	case 1:
		iVar2 = dword_6FB9E9F0 + a2 * 0x40 + a1;
		iVar3 = dword_6FB9A9E0[iVar2];
		if (iVar3 == 0)
		{
			(&dword_6FB9E9F8)[a2 * 0x40 + a1] = (&dword_6FB9E9F8)[iVar2];
			return;
		}
		break;
	case 2:
		iVar2 = a2 * 0x40 + dword_6FB9E9F0 + a1;
		iVar3 = dword_6FB9A9E0[iVar2];
		if (iVar3 == 0)
		{
			iVar3 = (&dword_6FB9E9F8)[iVar2];
		}
		iVar1 = (dword_6FB9A9D8 + a2) * 0x40 + dword_6FB9E9F0 + a1;
		iVar2 = dword_6FB9A9E0[iVar1];
		if (iVar2 == 0)
		{
			iVar2 = (&dword_6FB9E9F8)[iVar1];
		}
		(&dword_6FB9E9F8)[a2 * 0x40 + a1] =
		    (0x100 - dword_6FBA2DF8) * iVar3 + dword_6FBA2DF8 * iVar2 >> 8;
		return;
	case 3:
		iVar1 = (dword_6FB9A9D8 + a2) * 0x40;
		iVar3 = iVar1 + a1;
		iVar2 = dword_6FB9A9E0[iVar3];
		if (iVar2 == 0)
		{
			iVar2 = (&dword_6FB9E9F8)[iVar3];
		}
		iVar1 = iVar1 + dword_6FB9E9F0 + a1;
		iVar3 = dword_6FB9A9E0[iVar1];
		if (iVar3 == 0)
		{
			iVar3 = (&dword_6FB9E9F8)[iVar1];
		}
		(&dword_6FB9E9F8)[a2 * 0x40 + a1] =
		    (0x100 - dword_6FBA2DF8) * iVar2 + dword_6FBA2DF8 * iVar3 >> 8;
		return;
	case 4:
		iVar2 = (dword_6FB9A9D8 + a2) * 0x40 + a1;
		iVar3 = dword_6FB9A9E0[iVar2];
		if (iVar3 == 0)
		{
			iVar3 = (&dword_6FB9E9F8)[iVar2];
		}
	}
	(&dword_6FB9E9F8)[a2 * 0x40 + a1] = iVar3;
switchD_6faa5691_caseD_0:
}

//D2Client.0x6FAA57E0
void __fastcall sub_6FAA57E0(int* a1)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint16_t uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	uint32_t* puVar8;
	int iVar9;
	int iVar10;
	uint32_t* puVar11;
	uint32_t* puVar12;
	int iVar13;
	int iVar14;
	uint32_t* puVar15;
	int iStack_34;
	int iStack_30;
	int iStack_2c;
	int iStack_28;
	int iStack_24;
	int iStack_20;
	int iStack_1c;
	int iStack_18;
	int32_t DStack_14;
	int local_8;

	iVar5 = a1[6];
	if ((0 < iVar5) && (iVar5 < 0x100))
	{
		iVar5 = iVar5 * 2 >> 3;
		puVar11 = &dword_6FB9E9F8;
		for (iVar9 = 0x400; iVar9 != 0; iVar9 = iVar9 + -1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		iVar9 = a1[6];
		iVar13 = *a1;
		iVar6 = a1[4] >> 3;
		iVar7 = a1[5] >> 3;
		if (iVar13 != 6)
		{
			if ((char)a1[2] == '\0')
			{
				pUnit = sub_6FB269F0(a1[1], iVar13);
			}
			else
			{
				pUnit = sub_6FB26A60(a1[1], iVar13);
			}
			if (pUnit != nullptr)
			{
				pRoom = UNITS_GetRoom(pUnit);
				D2_ASSERT(pRoom != nullptr);
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iStack_18 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_18 = 0;
				}
				else
				{
					iStack_18 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DStack_14 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_14 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_14 + 2)) = 0;
				}
				else
				{
					DStack_14 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				iStack_1c = 0;
				puVar11 = dword_6FB9A9E0;
				do
				{
					iVar13 = 0;
					puVar12 = puVar11;
					do
					{
						uVar4 = COLLISION_CheckMask(pRoom, iVar13 + -0x20 + iStack_18,
						    iStack_1c + -0x20 + (int)DStack_14, 0x22);
						puVar11 = puVar12 + 1;
						iVar13 = iVar13 + 1;
						*puVar12 = -(uint32_t)(uVar4 != 0) & 0x10;
						puVar12 = puVar11;
					} while (iVar13 < 0x40);
					iStack_1c = iStack_1c + 1;
				} while ((int)puVar11 < (int)&dword_6FB9E9E0);
				iStack_34 = 2;
				if (1 < iVar9 >> 3)
				{
					iVar13 = 0x1e;
					iStack_1c = iVar7 * 8 + 0x14;
					DStack_14 = (int32_t)(iVar7 * 8 + -0xc);
					iStack_20 = iVar6 * 8 + 0x14;
					iStack_18 = iVar6 * 8 + -0xc;
					do
					{
						if (iVar13 < 0x21)
						{
							iStack_2c = iVar7 * 8 + 4;
							iStack_30 = iVar6 * 8 + 4;
							iVar10 = 0x20;
							iVar14 = 0x20;
							iStack_28 = iStack_30;
							iStack_24 = iStack_2c;
							do
							{
								sub_6FAA55D0(iStack_28, (int)DStack_14, (int)a1);
								sub_6FAA5680(iVar10, iVar13);
								sub_6FAA55D0(iStack_30, (int)DStack_14, (int)a1);
								sub_6FAA5680(iVar14, iVar13);
								sub_6FAA55D0(iStack_28, iStack_1c, (int)a1);
								sub_6FAA5680(iVar10, iStack_34 + 0x20);
								sub_6FAA55D0(iStack_30, iStack_1c, (int)a1);
								sub_6FAA5680(iVar14, iStack_34 + 0x20);
								sub_6FAA55D0(iStack_20, iStack_24, (int)a1);
								sub_6FAA5680(iStack_34 + 0x20, iVar10);
								sub_6FAA55D0(iStack_20, iStack_2c, (int)a1);
								sub_6FAA5680(iStack_34 + 0x20, iVar14);
								sub_6FAA55D0(iStack_18, iStack_24, (int)a1);
								sub_6FAA5680(iVar13, iVar10);
								sub_6FAA55D0(iStack_18, iStack_2c, (int)a1);
								sub_6FAA5680(iVar13, iVar14);
								iStack_30 = iStack_30 + 8;
								iStack_2c = iStack_2c + 8;
								iStack_28 = iStack_28 + -8;
								iStack_24 = iStack_24 + -8;
								iVar10 = iVar10 + -1;
								iVar1 = iVar14 + -0x1f;
								iVar14 = iVar14 + 1;
							} while (iVar1 <= iStack_34);
						}
						iStack_34 = iStack_34 + 1;
						iStack_20 = iStack_20 + 8;
						iStack_1c = iStack_1c + 8;
						iStack_18 = iStack_18 + -8;
						DStack_14 = (int32_t)((int)DStack_14 + -8);
						iVar13 = iVar13 + -1;
					} while (iStack_34 <= iVar9 >> 3);
				}
				D2_ASSERT(!a1[0xb]);
				puVar11 = (uint32_t*)a1[0xc];
				D2_ASSERT(puVar11 != nullptr);
				if (-1 < iVar5)
				{
					iVar5 = iVar5 + 1;
					puVar8 = &dword_6FB9E9F8 + (0x20 - (a1[6] >> 3)) * 0x41;
					iVar9 = iVar5;
					local_8 = iVar5;
					puVar15 = puVar8;
					do
					{
						do
						{
							uVar3 = *puVar8;
							puVar8 = puVar8 + 1;
							*puVar11 = uVar3;
							puVar11 = puVar11 + 1;
							iVar9 = iVar9 + -1;
						} while (iVar9 != 0);
						puVar8 = puVar15 + 0x40;
						local_8 = local_8 + -1;
						iVar9 = iVar5;
						puVar15 = puVar8;
					} while (local_8 != 0);
				}
				a1[0xb] = 1;
			}
		}
	}
}

//D2Client.0x6FAA5BC0
void __fastcall sub_6FAA5BC0(int a1)
{
	uint8_t bVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	uint32_t uVar10;
	int iVar11;
	int iVar12;
	int* local_1c;
	int local_10;

	iVar2 = *(int*)(a1 + 0x18);
	if ((0 < iVar2) && (iVar2 < 0x100))
	{
		iVar3 = (*(uint32_t*)(a1 + 0x10) - (*(uint32_t*)(a1 + 0x10) & 7)) - iVar2;
		iVar4 = (*(uint32_t*)(a1 + 0x14) - (*(uint32_t*)(a1 + 0x14) & 7)) - iVar2;
		iVar8 = iVar2 * 2 >> 3;
		if ((iVar3 >> 3 <= dword_6FB9E9E8) &&
		    (((dword_6FB9E9E0 <= (iVar3 >> 3) + 1 + iVar8 && (iVar4 >> 3 <= dword_6FB9E9EC)) &&
		        (dword_6FB9E9E4 <= (iVar4 >> 3) + 1 + iVar8))))
		{
			local_1c = *(int**)(a1 + 0x30);
			D2_ASSERT(local_1c != nullptr);
			D2_ASSERT(*(int*)(a1 + 0x2c));
			bVar1 = *(uint8_t*)(a1 + 0x24);
			if (-1 < iVar8)
			{
				iVar8 = iVar8 + 1;
				local_10 = iVar8;
				do
				{
					uVar5 = *(int*)(a1 + 0x14) - iVar4;
					iVar11 = iVar8;
					iVar12 = iVar3;
					if ((int)uVar5 < 0)
					{
						uVar5 = -uVar5;
					}
					do
					{
						if (*local_1c < 0x10)
						{
							uVar6 = *(int*)(a1 + 0x10) - iVar12;
							if ((int)uVar6 < 0)
							{
								uVar6 = -uVar6;
							}
							iVar9 = (uVar6 ^ (int)uVar6 >> 0x1f) - ((int)uVar6 >> 0x1f);
							iVar7 = (uVar5 ^ (int)uVar5 >> 0x1f) - ((int)uVar5 >> 0x1f);
							if (iVar9 < iVar7)
							{
								uVar6 = iVar7 * 0x3d7 + iVar9 * 0x197;
							}
							else
							{
								uVar6 = iVar9 * 0x3d7 + iVar7 * 0x197;
							}
							iVar9 = (*(int*)(a1 + 0x18) - (uVar6 >> 10)) *
							        ((int)((uint32_t)bVar1 << 0x10) / iVar2);
							iVar7 = (8 - (*local_1c >> 1)) * (iVar9 >> 0x10) >> 3;
							if (0 < iVar7)
							{
								uVar10 = (uint32_t)(uVar6 >> 0x12);
								sub_6FAA51D0(iVar12, iVar4, iVar7, CONCAT31(uVar10, *(uint8_t*)(a1 + 0x25)),
								    CONCAT31((int32_t)(char)((uint32_t)iVar9 >> 0x18),
								        *(uint8_t*)(a1 + 0x26)),
								    CONCAT31(uVar10, *(uint8_t*)(a1 + 0x27)));
							}
						}
						local_1c = local_1c + 1;
						iVar11 = iVar11 + -1;
						iVar12 = iVar12 + 8;
					} while (iVar11 != 0);
					iVar4 = iVar4 + 8;
					local_10 = local_10 + -1;
				} while (local_10 != 0);
			}
		}
	}
}

//D2Client.0x6FAA5DC0
void __cdecl sub_6FAA5DC0()
{
	void* pvVar1;
	void* pFree;

	pFree = (void*)dword_6FBA7604;
	if (dword_6FBA7604 != 0)
	{
		do
		{
			pvVar1 = *(void**)((int)pFree + 0x28);
			if (*(void**)((int)pFree + 0x30) != nullptr)
			{
				D2_FREE(*(void**)((int)pFree + 0x30));
			}
			D2_FREE(pFree);
			pFree = pvVar1;
		} while (pvVar1 != nullptr);
	}
	dword_6FBA7604 = 0;
}

//D2Client.0x6FAA5E10
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAA5E10()
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pDVar3;
	int32_t DVar4;
	D2ActiveRoomStrc* pDVar5;
	D2ActiveRoomStrc* in_ECX;
	int iVar6;
	D2ActiveRoomStrc** ppDVar7;
	int iVar8;
	int iStack_18;
	int* piStack_10;
	D2ActiveRoomStrc** ppDStack_8;
	D2ActiveRoomStrc** ppDStack_4;

	piStack_10 = (int*)dword_6FBA7604;
	if (dword_6FBA7604 != 0)
	{
		do
		{
			if (piStack_10[3] == 2)
			{
				iVar8 = *piStack_10;
				if (iVar8 == 6)
				{
				LAB_6faa6087:
					FOG_DisplayAssert("hSrcUnit", __FILE__, __LINE__);
					exit(-1);
				}
				if ((char)piStack_10[2] == '\0')
				{
					pUnit = sub_6FB269F0(piStack_10[1], iVar8);
				}
				else
				{
					pUnit = sub_6FB26A60(piStack_10[1], iVar8);
				}
				if (pUnit == nullptr)
					goto LAB_6faa6087;
				pDVar3 = UNITS_GetRoom(pUnit);
				if (pDVar3 == in_ECX)
					goto LAB_6faa605f;
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iStack_18 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_18 = 0;
				}
				else
				{
					iStack_18 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
				}
				else
				{
					DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				iVar6 = piStack_10[6] >> 3;
				iVar8 = iStack_18 + iVar6;
				if (pDVar3 == nullptr)
				{
				LAB_6faa5f75:
					pDVar5 = nullptr;
				}
				else
				{
					iVar2 = (pDVar3->tCoords).nSubtileX;
					if ((((iVar8 < iVar2) || ((pDVar3->tCoords).nSubtileWidth + iVar2 <= iVar8)) ||
					        (iVar2 = (pDVar3->tCoords).nSubtileY, (int)DVar4 < iVar2)) ||
					    (pDVar5 = pDVar3, (pDVar3->tCoords).nSubtileHeight + iVar2 <= (int)DVar4))
					{
						ppDStack_4 = nullptr;
						ppDStack_8 = nullptr;
						DUNGEON_GetAdjacentRoomsListFromRoom(pDVar3, &ppDStack_4, (int*)&ppDStack_8);
						ppDVar7 = nullptr;
						if (ppDStack_8 != nullptr)
						{
							do
							{
								pDVar5 = ppDStack_4[(int)ppDVar7];
								if (((pDVar5 != nullptr) &&
								        (iVar2 = (pDVar5->tCoords).nSubtileX, iVar2 <= iVar8)) &&
								    ((iVar8 < (pDVar5->tCoords).nSubtileWidth + iVar2 &&
								        ((iVar2 = (pDVar5->tCoords).nSubtileY, iVar2 <= (int)DVar4 &&
								                                                   ((int)DVar4 < (pDVar5->tCoords).nSubtileHeight + iVar2))))))
								{
									pDVar5 = ppDStack_4[(int)ppDVar7];
									goto LAB_6faa5f77;
								}
								ppDVar7 = (D2ActiveRoomStrc**)((int)ppDVar7 + 1);
							} while (ppDVar7 < ppDStack_8);
						}
						goto LAB_6faa5f75;
					}
				}
			LAB_6faa5f77:
				if (pDVar5 != in_ECX)
				{
					iVar8 = iStack_18 - iVar6;
					if (pDVar3 == nullptr)
					{
					LAB_6faa6023:
						pDVar5 = nullptr;
					}
					else
					{
						iVar2 = (pDVar3->tCoords).nSubtileX;
						if ((((iVar8 < iVar2) || ((pDVar3->tCoords).nSubtileWidth + iVar2 <= iVar8)) ||
						        (iVar2 = (pDVar3->tCoords).nSubtileY, (int)DVar4 < iVar2)) ||
						    (pDVar5 = pDVar3, (pDVar3->tCoords).nSubtileHeight + iVar2 <= (int)DVar4))
						{
							ppDStack_8 = nullptr;
							ppDStack_4 = nullptr;
							DUNGEON_GetAdjacentRoomsListFromRoom(pDVar3, &ppDStack_8, (int*)&ppDStack_4);
							ppDVar7 = nullptr;
							if (ppDStack_4 != nullptr)
							{
								do
								{
									pDVar5 = ppDStack_8[(int)ppDVar7];
									if (((pDVar5 != nullptr) &&
									        (iVar2 = (pDVar5->tCoords).nSubtileX, iVar2 <= iVar8)) &&
									    ((iVar8 < (pDVar5->tCoords).nSubtileWidth + iVar2 &&
									        ((iVar2 = (pDVar5->tCoords).nSubtileY, iVar2 <= (int)DVar4 &&
									                                                   ((int)DVar4 < (pDVar5->tCoords).nSubtileHeight + iVar2))))))
									{
										pDVar5 = ppDStack_8[(int)ppDVar7];
										goto LAB_6faa6025;
									}
									ppDVar7 = (D2ActiveRoomStrc**)((int)ppDVar7 + 1);
								} while (ppDVar7 < ppDStack_4);
							}
							goto LAB_6faa6023;
						}
					}
				LAB_6faa6025:
					if (((pDVar5 != in_ECX) &&
					        (pDVar5 = sub_6FAA6150(pDVar3, iStack_18, (int)DVar4 + iVar6), pDVar5 != in_ECX)) &&
					    (pDVar3 = sub_6FAA6150(pDVar3, iStack_18, (int)DVar4 - iVar6), pDVar3 != in_ECX))
						goto LAB_6faa605f;
				}
				piStack_10[0xb] = 0;
			}
		LAB_6faa605f:
			piStack_10 = (int*)piStack_10[10];
		} while (piStack_10 != nullptr);
	}
}

//D2Client.0x6FAA60B0
void __fastcall sub_6FAA60B0(int a1, int a2, uint8_t* a3, uint8_t* a4, uint8_t* a5, uint8_t* a6)
{
	int iVar1;
	int iVar2;

	iVar1 = (a1 >> 3) - dword_6FB9E9E0;
	iVar2 = (a2 >> 3) - dword_6FB9E9E4;
	if (iVar1 < 0)
	{
		iVar1 = 0;
	}
	else if (0x2f < iVar1)
	{
		iVar1 = 0x2f;
	}
	if (iVar2 < 0)
	{
		iVar2 = 0;
	}
	else if (0x2f < iVar2)
	{
		iVar2 = 0x2f;
	}
	iVar1 = iVar2 * 0x30 + iVar1;
	*a3 = (&byte_6FBA2E04)[iVar1 * 8];
	iVar1 = iVar1 * 8;
	if (dword_6FB74C88 != 0)
	{
		*a4 = (&byte_6FBA2E05)[iVar1];
		*a5 = (&byte_6FBA2E06)[iVar1];
		*a6 = (&byte_6FBA2E07)[iVar1];
	}
}

//D2Client.0x6FAA6130
void __cdecl sub_6FAA6130()
{
	D2GFX_DebugDraw(&dword_6FB9E9F8, &dword_6FBA2E00, *(int*)(dword_6FBA7604 + 0x10),
	    *(int*)(dword_6FBA7604 + 0x14));
}

//D2Client.0x6FAA6150
D2ActiveRoomStrc* __fastcall sub_6FAA6150(D2ActiveRoomStrc* pActiveRoom, int a2, int a3)
{
	int iVar1;
	D2ActiveRoomStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;
	D2ActiveRoomStrc** local_4;

	iVar3 = a3;
	if (pActiveRoom != nullptr)
	{
		iVar1 = (pActiveRoom->tCoords).nSubtileX;
		if ((((iVar1 <= a2) && (a2 < (pActiveRoom->tCoords).nSubtileWidth + iVar1)) &&
		        (iVar1 = (pActiveRoom->tCoords).nSubtileY, iVar1 <= a3)) &&
		    (a3 < (pActiveRoom->tCoords).nSubtileHeight + iVar1))
		{
			return pActiveRoom;
		}
		local_4 = nullptr;
		a3 = 0;
		DUNGEON_GetAdjacentRoomsListFromRoom(pActiveRoom, &local_4, &a3);
		uVar4 = 0;
		if (a3 != 0)
		{
			do
			{
				pDVar2 = local_4[uVar4];
				if (((pDVar2 != nullptr) &&
				        (iVar1 = (pDVar2->tCoords).nSubtileX, iVar1 <= a2)) &&
				    ((a2 < (pDVar2->tCoords).nSubtileWidth + iVar1 &&
				        ((iVar1 = (pDVar2->tCoords).nSubtileY, iVar1 <= iVar3 &&
				                                                   (iVar3 < (pDVar2->tCoords).nSubtileHeight + iVar1))))))
				{
					return local_4[uVar4];
				}
				uVar4 = uVar4 + 1;
			} while (uVar4 < (uint32_t)a3);
		}
	}
	return nullptr;
}

//D2Client.0x6FAA61F0
void __cdecl sub_6FAA61F0()
{
	DWORD DVar1;

	DVar1 = GetTickCount();
	dword_6FBA761C = DVar1 + 500;
}

//D2Client.0x6FAA6210
void __cdecl sub_6FAA6210()
{
	int nYEnd;
	DWORD DVar1;
	int iVar2;
	int iVar3;
	int nXEnd;
	int nXStart;

	nXStart = 0;
	if (dword_6FBA761C != 0)
	{
		DVar1 = GetTickCount();
		nXEnd = gnScreenWidth;
		if (dword_6FBA761C < DVar1)
		{
			dword_6FBA761C = 0;
			return;
		}
		iVar3 = dword_6FBA761C - DVar1;
		nYEnd = gnScreenHeight + -0x2f;
		iVar2 = sub_6FAB5750();
		if (iVar2 == 1)
		{
			nXEnd = nXEnd - gnScreenWidth / 2;
		}
		else if (iVar2 == 2)
		{
			nXStart = gnScreenWidth / 2;
		}
		D2GFX_DrawBoxAlpha(nXStart, 0, nXEnd, nYEnd, 0, (uint8_t)((iVar3 * 0xff) / 500));
	}
}

//D2Client.0x6FAA62A0
void __fastcall sub_6FAA62A0()
{
	dword_6FBA761C = 0;
}

//D2Client.0x6FAA62B0
void __cdecl sub_6FAA62B0()
{
	int iVar1;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	uint32_t uStack_4;

	ENVIRONMENT_GetLightColorFromAct(ghAct, &byte_6FBA7622, (uint8_t*)&byte_6FBA7620, (uint8_t*)&byte_6FBA7621);
	iVar1 = ENVIRONMENT_GetIntensityFromAct(ghAct);
	byte_6FBA7623 = (uint8_t)iVar1;
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			DUNGEON_GetRGB_IntensityFromRoom(pRoom, (uint8_t*)((int)&uStack_4 + 3), (uint8_t*)&uStack_4, (uint8_t*)((int)&uStack_4 + 2),
			    (uint8_t*)((int)&uStack_4 + 1));
			if ((((uint8_t)uStack_4 != 0) || ((*(uint8_t*)((uint8_t*)&uStack_4 + 2)) != '\0')) || ((*(uint8_t*)((uint8_t*)&uStack_4 + 1)) != '\0'))
			{
				byte_6FBA7623 = (*(uint8_t*)((uint8_t*)&uStack_4 + 3));
				byte_6FBA7622 = (uint8_t)uStack_4;
				byte_6FBA7620 = (*(uint8_t*)((uint8_t*)&uStack_4 + 2));
				byte_6FBA7621 = (*(uint8_t*)((uint8_t*)&uStack_4 + 1));
			}
		}
	}
}

//D2Client.0x6FAA6340
void __fastcall sub_6FAA6340(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint8_t local_a;
	uint8_t local_9;
	uint32_t local_8;
	uint32_t local_4;

	iVar3 = *(int*)(a1 + 0xeaa8);
	for (iVar2 = *(int*)(a1 + 0xeab0) * *(int*)(a1 + 0xeab0); iVar2 != 0;
	     iVar2 = iVar2 + -1)
	{
		if (*(int*)(iVar3 + 0x14) != 0)
		{
			sub_6FAA63E0(iVar3, 0, a1);
		}
		for (iVar1 = *(int*)(iVar3 + 0x18); iVar1 != 0; iVar1 = *(int*)(iVar1 + 0x10))
		{
			sub_6FAA60B0(*(int*)(iVar1 + 4), *(int*)(iVar1 + 8), (uint8_t*)&local_4,
			    (uint8_t*)&local_8, &local_9, &local_a);
			sub_6FB4DB40(*(D2UnitStrc**)(iVar1 + 0xc),
			    ((uint32_t)CONCAT11(local_a, local_9) << 8 | local_8 & 0xff) << 8 | local_4 & 0xff, 0);
		}
		iVar3 = iVar3 + 0x24;
	}
}
