#include "Draw/DWall.h"

#include "Core/WndProc.h"
#include "Draw/DLightMap.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/SCmd.h"
#include "Unit/UnitGfx.h"

//D2Client.0x6FB6E160
uint8_t byte_6FB6E160[41] = {0, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0x50};
//D2Client.0x6FB74D60
uint8_t byte_6FB74D60;
//D2Client.0x6FB74F40
uint8_t byte_6FB74F40;
//D2Client.0x6FB751B4
uint32_t dword_6FB751B4 = 4;
//D2Client.0x6FB751B8
uint32_t dword_6FB751B8 = 1;
//D2Client.0x6FBA76B4
uint8_t byte_6FBA76B4;
//D2Client.0x6FBA76F8
uint8_t byte_6FBA76F8;
//D2Client.0x6FBA770C
uint32_t dword_6FBA770C;

//D2Client.0x6FAA63E0
void __fastcall sub_6FAA63E0(int a1, uint32_t a2, int a3)
{
	int* piVar1;
	uint8_t* puVar2;
	int iVar3;
	uint8_t bVar4;
	int nYPos;
	char cVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint8_t uStack_46;
	uint8_t uStack_45;
	int iStack_44;
	uint32_t uStack_40;
	int local_3c;
	DWORD DStack_38;
	uint32_t uStack_34;
	uint32_t local_30;
	uint32_t uStack_2c;
	int iStack_28;
	uint32_t uStack_24;
	D2GfxLightStrc aDStack_20[8];

	local_30 = a2;
	local_3c = sub_6FAB5750();
	iStack_28 = D2GFX_CheckPerspective();
	iVar3 = WNDPROC_GetDisplayType();
	DStack_38 = GetTickCount();
	uStack_34 = (uint32_t)(3 < iVar3);
	D2_ASSERT(!((a2 != 0) && (a2 != 1)));
	iStack_44 = *(int*)(a1 + 0x14);
	uVar6 = DStack_38;
	while (true)
	{
		if (iStack_44 == 0)
		{
			return;
		}
		piVar1 = *(int**)(iStack_44 + 0xc);
		if (piVar1[7] == 0xf)
			break;
		if ((piVar1[9] & 2U) != 0)
		{
			if ((uStack_34 == 0) || ((uint32_t)piVar1[0xb] <= uVar6))
			{
				cVar5 = *(char*)((int)piVar1 + 0x2a);
				piVar1[9] = piVar1[9] & 0xfffffffd;
			}
			else
			{
				iVar3 = ((uint32_t) * (uint8_t*)((int)piVar1 + 0x2a) - (uint32_t) * (uint8_t*)((int)piVar1 + 0x29)) *
				        ((uVar6 - piVar1[0xb]) + 500);
				cVar5 = (((char)(iVar3 / 500) + (char)(iVar3 >> 0x1f)) -
				            (char)((int64_t)iVar3 * 0x10624dd3 >> 0x3f)) +
				        *(uint8_t*)((int)piVar1 + 0x29);
			}
			*(char*)(piVar1 + 10) = cVar5;
			if (cVar5 == '\0')
			{
				uVar7 = piVar1[5] | 0x400;
			}
			else
			{
				uVar7 = piVar1[5] & 0xfffffbff;
			}
			piVar1[5] = uVar7;
		}
		if (((piVar1[9] & 4U) != 0) && ((uint32_t)piVar1[0xb] <= uVar6))
		{
			piVar1[9] = piVar1[9] & 0xfffffffb;
			piVar1[5] = piVar1[5] | 8;
		}
		if (((piVar1[5] & 0x408U) == 0) && (local_30 != ((piVar1[5] & 0x1c000U) != 0)))
		{
			iVar3 = *(int*)piVar1[6];
			uVar6 = *(uint32_t*)(byte_6FB6E160 + iVar3 * 4);
			if ((*(uint8_t*)(piVar1 + 9) & 1) == 0)
			{
				puVar2 = &byte_6FB74D60;
			}
			else
			{
				puVar2 = &byte_6FB74F40;
			}
			uVar7 = 0;
			if (uVar6 != 0)
			{
				do
				{
					sub_6FAA60B0(*(int*)(iStack_44 + 4) + *(int*)(puVar2 + iVar3 * 0x30 + uVar7 * 8) * 8,
					    *(int*)(iStack_44 + 8) + *(int*)(puVar2 + iVar3 * 0x30 + uVar7 * 8 + 4) * 8, (uint8_t*)&uStack_40, (uint8_t*)&uStack_2c, &uStack_45, &uStack_46);
					bVar4 = ((uStack_40 & 0xff) == 0) - 1U & (uint8_t)uStack_40;
					uStack_40 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_40 + 1)), bVar4);
					*(uint32_t*)&aDStack_20[uVar7] = (((uint32_t)CONCAT11(uStack_46, uStack_45) << 8 | uStack_2c & 0xff) << 8 | (uint32_t)bVar4);
					uVar7 = uVar7 + 1;
				} while (uVar7 < uVar6);
			}
			bVar4 = *(uint8_t*)(piVar1 + 10);
			uStack_24 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_24 + 1)), bVar4);
			if (iStack_28 == 0)
			{
				iVar3 = (*(int*)(a3 + 4) - *(int*)(a3 + 0x24)) + *piVar1;
				nYPos = (piVar1[1] - *(int*)(a3 + 0x28)) + *(int*)(a3 + 8);
			}
			else
			{
				iVar3 = *(int*)(iStack_44 + 4);
				nYPos = *(int*)(iStack_44 + 8);
			}
			if (bVar4 == 0xff)
			{
				iVar3 = TILE_TileDrawLit((D2TileLibraryEntryStrc*)piVar1[6], iVar3, nYPos, aDStack_20, local_3c);
			}
			else
			{
				iVar3 = TILE_TileDrawTrans((D2TileLibraryEntryStrc*)piVar1[6], iVar3, nYPos, aDStack_20,
				    local_3c, bVar4);
			}
			uVar6 = DStack_38;
			if (iVar3 != 0)
			{
				piVar1[5] = piVar1[5] | 0x20000;
			}
		}
		iStack_44 = *(int*)(iStack_44 + 0x10);
	}
	FOG_DisplayAssert("ptTile->eTileType!= BASE_ROOF",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAA6670
void __fastcall sub_6FAA6670(int a1)
{
	int iVar1;
	uint8_t* puVar2;
	int iVar3;
	int nYPos;
	uint8_t bVar4;
	uint32_t uVar5;
	int* piVar6;
	uint8_t uStack_4a;
	uint8_t uStack_49;
	uint32_t uStack_48;
	int local_44;
	int* local_40;
	int local_3c;
	uint32_t uStack_38;
	uint32_t uStack_34;
	uint32_t uStack_30;
	int iStack_2c;
	int local_28;
	uint32_t uStack_24;
	D2GfxLightStrc aDStack_20[8];

	local_3c = *(int*)(a1 + 0xeab0) * *(int*)(a1 + 0xeab0);
	if (local_3c != 0)
	{
		piVar6 = (int*)(*(int*)(a1 + 0xeaa8) + 0x20);
		local_28 = a1;
		do
		{
			if (*piVar6 != 0)
			{
				local_40 = piVar6;
				local_44 = sub_6FAB5750();
				iStack_2c = D2GFX_CheckPerspective();
				uStack_38 = GetTickCount();
				iVar1 = *piVar6;
				for (; iVar1 != 0; iVar1 = *(int*)(iVar1 + 0x10))
				{
					piVar6 = *(int**)(iVar1 + 0xc);
					if (((piVar6[9] & 4U) != 0) && ((uint32_t)piVar6[0xb] <= uStack_38))
					{
						piVar6[9] = piVar6[9] & 0xfffffffb;
						piVar6[5] = piVar6[5] | 8;
					}
					if (((piVar6[5] & 0x408U) == 0) && ((piVar6[5] & 0x1c000U) != 0))
					{
						iVar3 = *(int*)piVar6[6];
						uStack_30 = *(uint32_t*)(byte_6FB6E160 + iVar3 * 4);
						if ((*(uint8_t*)(piVar6 + 9) & 1) == 0)
						{
							puVar2 = &byte_6FB74D60;
						}
						else
						{
							puVar2 = &byte_6FB74F40;
						}
						uVar5 = 0;
						if (uStack_30 != 0)
						{
							do
							{
								sub_6FAA60B0(*(int*)(iVar1 + 4) + *(int*)(puVar2 + iVar3 * 0x30 + uVar5 * 8) * 8,
								    *(int*)(iVar1 + 8) +
								        *(int*)(puVar2 + iVar3 * 0x30 + uVar5 * 8 + 4) * 8,
								    (uint8_t*)&uStack_48, (uint8_t*)&uStack_34, &uStack_49, &uStack_4a);
								bVar4 = ((uStack_48 & 0xff) == 0) - 1U & (uint8_t)uStack_48;
								uStack_48 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_48 + 1)), bVar4);
								*(uint32_t*)&aDStack_20[uVar5] = (((uint32_t)CONCAT11(uStack_4a, uStack_49) << 8 | uStack_34 & 0xff) << 8 |
								                     (uint32_t)bVar4);
								uVar5 = uVar5 + 1;
							} while (uVar5 < uStack_30);
						}
						bVar4 = *(uint8_t*)(piVar6 + 10);
						uStack_24 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_24 + 1)), bVar4);
						if (iStack_2c == 0)
						{
							iVar3 = (*(int*)(local_28 + 4) - *(int*)(local_28 + 0x24)) + *piVar6;
							nYPos = (piVar6[1] - *(int*)(local_28 + 0x28)) + *(int*)(local_28 + 8);
						}
						else
						{
							iVar3 = *(int*)(iVar1 + 4);
							nYPos = *(int*)(iVar1 + 8);
						}
						if (bVar4 == 0xff)
						{
							iVar3 = TILE_TileDrawLit((D2TileLibraryEntryStrc*)piVar6[6], iVar3, nYPos, aDStack_20,
							    local_44);
						}
						else
						{
							iVar3 = TILE_TileDrawTrans((D2TileLibraryEntryStrc*)piVar6[6], iVar3, nYPos, aDStack_20,
							    local_44, bVar4);
						}
						if (iVar3 != 0)
						{
							piVar6[5] = piVar6[5] | 0x20000;
						}
					}
					piVar6 = local_40;
				}
			}
			piVar6 = piVar6 + 9;
			local_3c = local_3c + -1;
		} while (local_3c != 0);
	}
}

//D2Client.0x6FAA6860
void __fastcall sub_6FAA6860(int a1)
{
	uint32_t* puVar1;
	int* piVar2;
	int nScreenPanels;
	int iVar3;
	int iVar4;
	uint8_t local_e;
	uint8_t local_d;
	int local_c;
	uint32_t local_8;
	uint32_t local_4;

	iVar3 = *(int*)(a1 + 0xeab0);
	iVar4 = *(int*)(a1 + 0xeaa8);
	nScreenPanels = sub_6FAB5750();
	for (local_c = iVar3 * iVar3; local_c != 0; local_c = local_c + -1)
	{
		for (puVar1 = *(uint32_t**)(iVar4 + 0x10); puVar1 != nullptr; puVar1 = (uint32_t*)puVar1[4])
		{
			if ((*puVar1 & 3) == 0)
			{
				sub_6FAA60B0(puVar1[1], puVar1[2], (uint8_t*)&local_4, (uint8_t*)&local_8, &local_d,
				    &local_e);
				sub_6FB4DB40((D2UnitStrc*)puVar1[3],
				    ((uint32_t)CONCAT11(local_e, local_d) << 8 | local_8 & 0xff) << 8 | local_4 & 0xff, 0);
			}
			else
			{
				iVar3 = D2GFX_CheckPerspective();
				if ((*puVar1 & 1) == 0)
				{
					if ((*puVar1 & 2) != 0)
					{
						sub_6FB59670((D2UnitStrc*)puVar1[3]);
					}
				}
				else
				{
					piVar2 = (int*)puVar1[3];
					if (iVar3 == 0)
					{
						TILE_ShadowTileDraw((D2TileLibraryEntryStrc*)piVar2[6],
						    (*(int*)(a1 + 4) - *(int*)(a1 + 0x24)) + *piVar2,
						    (piVar2[1] - *(int*)(a1 + 0x28)) + *(int*)(a1 + 8), 4,
						    nScreenPanels);
					}
					else
					{
						TILE_ShadowTileDraw((D2TileLibraryEntryStrc*)piVar2[6], puVar1[1], puVar1[2], 4,
						    nScreenPanels);
					}
				}
			}
		}
		if (*(int*)(iVar4 + 0x14) != 0)
		{
			sub_6FAA63E0(iVar4, 1, a1);
		}
		iVar4 = iVar4 + 0x24;
	}
}

//D2Client.0x6FAA6990
uint32_t __cdecl sub_6FAA6990()
{
	return (dword_6FB751B4 & 0xff) >> 1 & 1;
}

//D2Client.0x6FAA69A0
uint32_t __cdecl sub_6FAA69A0()
{
	return dword_6FB751B4;
}

//D2Client.0x6FAA69B0
void __fastcall sub_6FAA69B0(uint32_t a1)
{
	dword_6FB751B4 = a1;
}

//D2Client.0x6FAA69C0
void __fastcall sub_6FAA69C0(int a1)
{
	if (a1 != 0)
	{
		dword_6FB751B4 = dword_6FB751B4 & 0xfffffffe;
		return;
	}
	dword_6FB751B4 = dword_6FB751B4 | 1;
}

//D2Client.0x6FAA69E0
void __fastcall sub_6FAA69E0(uint32_t a1)
{
	dword_6FB751B8 = a1;
}

//D2Client.0x6FAA69F0
uint32_t __cdecl sub_6FAA69F0()
{
	return dword_6FB751B8;
}

//D2Client.0x6FAA6A00
uint32_t __cdecl sub_6FAA6A00()
{
	return dword_6FB751B4 >> 8 & 1;
}

//D2Client.0x6FAA6A10
void __cdecl sub_6FAA6A10()
{
	dword_6FBA7704 = FOG_10060((int)"Environment Particles", 0x100, 0x28);
	FOG_10062(dword_6FBA7704);
	dword_6FBA7658 = 0;
	dword_6FBA76FC = FOG_10060((int)"Environment Splashes", 0x200, 0x18);
	FOG_10062(dword_6FBA76FC);
	dword_6FBA7700 = FOG_10060((int)"Environment Bubbles", 0x80, 0x18);
	FOG_10062(dword_6FBA7700);
	dword_6FBA76AC = 0;
	byte_6FBA76B4 = 0x2a;
	dword_6FBA76B0 = 0x2a;
	dword_6FBA7708 = 0;
	dword_6FBA770C = 0;
	byte_6FBA76F8 = 0xaa;
	dword_6FBA76F4 = 0xaa;
}

//D2Client.0x6FAA6AB0
void __cdecl sub_6FAA6AB0()
{
	FOG_10061(dword_6FBA7704);
	FOG_10061(dword_6FBA76FC);
	FOG_10061(dword_6FBA7700);
}
