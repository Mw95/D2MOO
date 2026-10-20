#include "Game/SCmd.h"

#include "Core/MemoryPartitions.h"
#include "Core/WinMain.h"
#include "Draw/DFloor.h"
#include "Draw/DWall.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/PalShift.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/Scroll.h"
#include "Game/Wall2.h"
#include "Quest/Quests.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Skills/SkillsBar.h"
#include "Skills/SkillsPal.h"
#include "UI/Inv.h"
#include "UI/NpcMenu.h"
#include "UI/QuestLog.h"
#include "UI/Restart.h"
#include "UI/SkillDesc.h"
#include "UI/SpellSel.h"
#include "UI/Text.h"
#include "UI/Trade.h"
#include "UI/UseItem.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"
#include "Unit/Missile.h"
#include "Unit/MonUnique.h"
#include "Unit/Monster.h"
#include "Unit/Object.h"
#include "Unit/Player.h"
#include "Unit/PlrSkills.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB76270
uint8_t* ptr_6FB76270 = (uint8_t*)sub_6FAABE90;
//D2Client.0x6FB76274
uint32_t dword_6FB76274 = 1;
//D2Client.0x6FB76278
uint32_t dword_6FB76278[2] = {0, (uint32_t)sub_6FAB2130};
//D2Client.0x6FBAB9A4
int32_t* gpint32_t_6FBAB9A4;
//D2Client.0x6FBAB9A8
uint32_t dword_6FBAB9A8;
//D2Client.0x6FBAB9B0
int32_t dword_6FBAB9B0;
//D2Client.0x6FBAB9B4
uint8_t byte_6FBAB9B4;
//D2Client.0x6FBBC244
uint32_t dword_6FBBC244;
//D2Client.0x6FBBC248
uint32_t dword_6FBBC248;
//D2Client.0x6FBC1AF0
int32_t dword_6FBC1AF0;
//D2Client.0x6FBC1AF8
uint8_t byte_6FBC1AF8;
//D2Client.0x6FBC1B00
uint8_t byte_6FBC1B00;

//D2Client.0x6FAB1CB0
void __fastcall sub_6FAB1CB0(uint8_t* a1, int a2)
{
	uint8_t* puVar1;
	void* p4;
	uint8_t* puVar2;
	int iVar3;
	char acStack_5f4[500];
	char acStack_400[1024];

	if (a2 == -1)
	{
		return;
	}
	switch (*a1)
	{
	case 0xae:
		dword_6FBA7968 = 1;
		return;
	case 0xaf:
		dword_6FBA7968 = 0;
		return;
	case 0xb2:
		if (gpint32_t_6FBAB9A4 == nullptr)
		{
		LAB_6fab1d2f:
			gpint32_t_6FBAB9A4 = (int*)D2_ALLOC(*(int*)(a1 + 3));
		}
		else if (a1[2] != '\0')
		{
			D2_FREE(gpint32_t_6FBAB9A4);
			gpint32_t_6FBAB9A4 = nullptr;
			dword_6FBAB9A8 = 0;
			goto LAB_6fab1d2f;
		}
		iVar3 = 0;
		puVar1 = (uint8_t*)((int)gpint32_t_6FBAB9A4 + dword_6FBAB9A8);
		puVar2 = a1 + 7;
		if (a1[1] != '\0')
		{
			do
			{
				*puVar1 = *puVar2;
				puVar1 = puVar1 + 1;
				puVar2 = puVar2 + 1;
				iVar3 = iVar3 + 1;
			} while (iVar3 < (int)(uint32_t)(uint8_t)a1[1]);
		}
		dword_6FBAB9A8 = dword_6FBAB9A8 + (uint8_t)a1[1];
		if (*(uint32_t*)(a1 + 3) == dword_6FBAB9A8)
		{
			D2_ASSERT(gszPlayerName[0] != '\0');
			if ((7 < dword_6FBAB9A8) && (*gpint32_t_6FBAB9A4 == -0x55aa55ab))
			{
				if ((uint32_t)gpint32_t_6FBAB9A4[1] < 0x5c)
				{
					if (dword_6FBAB9A8 < 0x82)
						goto LAB_6fab1e72;
					*(short*)(gpConfig + 0x1ea) = (short)gpint32_t_6FBAB9A4[6];
				}
				else
				{
					if (dword_6FBAB9A8 < 0x14f)
						goto LAB_6fab1e72;
					*(short*)(gpConfig + 0x1ea) = (short)gpint32_t_6FBAB9A4[9];
				}
				FOG_GetSavePath(acStack_400, 0x400);
				sprintf(acStack_5f4, "%s%s.d2s", acStack_400, gszPlayerName);
				p4 = fopen(acStack_5f4, "wb");
				if (p4 != nullptr)
				{
					fwrite(gpint32_t_6FBAB9A4, dword_6FBAB9A8, 1, (FILE* __restrict)(p4));
					fclose((FILE*)(p4));
				}
			}
		LAB_6fab1e72:
			D2_FREE(gpint32_t_6FBAB9A4);
			gpint32_t_6FBAB9A4 = nullptr;
			dword_6FBAB9A8 = 0;
			return;
		}
		break;
	case 0xb3:
		switch (*(uint32_t*)(a1 + 1))
		{
		case 1:
			sub_6FAA9850(0);
			return;
		case 2:
			sub_6FAA9850(1);
			return;
		case 3:
			sub_6FAA9850(2);
			return;
		case 4:
			sub_6FAA9850(3);
			return;
		case 5:
			sub_6FAA9850(4);
			return;
		case 6:
			sub_6FAA9850(5);
			return;
		case 7:
			sub_6FAA9850(10);
			return;
		case 8:
			sub_6FAA9850(0xb);
			return;
		case 9:
			sub_6FAA9850(0xc);
			return;
		case 10:
			sub_6FAA9850(0xd);
			return;
		case 0xb:
			sub_6FAA9850(0xe);
			return;
		case 0xc:
			sub_6FAA9850(0xf);
			return;
		case 0xd:
			sub_6FAA9850(0x10);
			return;
		case 0xe:
			sub_6FAA9850(0x11);
			return;
		case 0xf:
			sub_6FAA9850(0x12);
			return;
		case 0x10:
			sub_6FAA9850(0x13);
			return;
		case 0x11:
			sub_6FAA9850(0x14);
			return;
		case 0x12:
			sub_6FAA9850(0x15);
			return;
		case 0x13:
			sub_6FAA9850(0x16);
			return;
		case 0x14:
			sub_6FAA9850(0x17);
			return;
		case 0x15:
			sub_6FAA9850(0x18);
			return;
		default:
			sub_6FAA9850(9);
			break;
		case 0x17:
			sub_6FAA9850(0x19);
			return;
		case 0x18:
			sub_6FAA9850(0x1a);
			return;
		case 0x19:
			sub_6FAA9850(0x1b);
			return;
		case 0x1a:
			sub_6FAA9850(0x1c);
			return;
		}
	}
}

//D2Client.0x6FAB2130
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAB2130(int a1)
{
	uint32_t uVar1;
	uint32_t extraout_ECX;

	uVar1 = *(uint32_t*)(a1 + 2);
	sub_6FAAC030(*(uint8_t*)(a1 + 1));
	sub_6FAAC040(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), *(uint8_t*)(a1 + 6)));
	sub_6FAAC050((uint32_t) * (uint8_t*)(a1 + 7));
	sub_6FAA69B0(uVar1);
	sub_6FB20160();
}

//D2Client.0x6FAB2160
void __fastcall sub_6FAB2160(int a1)
{
	sub_6FAA9290(CONCAT31((int32_t)((uint32_t)a1 >> 8), *(uint8_t*)(a1 + 1)),
	    *(uint32_t*)(a1 + 2), *(uint32_t*)(a1 + 8),
	    (uint32_t) * (uint16_t*)(a1 + 6));
}

//D2Client.0x6FAB2190
void __cdecl sub_6FAB2190()
{
	D2ActiveRoomStrc* pRoom;
	int nLevelId;
	D2UnitStrc* pDVar1;

	dword_6FBA796C = 1;
	dword_6FBA7974 = 0;
	pRoom = CUNIT_GetPlayerRoom();
	if (pRoom != nullptr)
	{
		nLevelId = DUNGEON_GetLevelIdFromRoom(pRoom);
		DRLG_GetActNoFromLevelId(nLevelId);
		sub_6FB5D290();
		pDVar1 = CUNIT_GetPlayer();
		if (((pDVar1 != nullptr) && (pDVar1->dwUnitType == 0)) &&
		    (pDVar1->pPlayerData != nullptr))
		{
			pDVar1->pPlayerData->unk0xA8[0x2a] = 0;
			pDVar1->pPlayerData->unk0xA8[0x2b] = 0;
			pDVar1->pPlayerData->unk0xA8[0x2c] = 0;
			pDVar1->pPlayerData->unk0xA8[0x2d] = 0;
		}
		return;
	}
	FOG_DisplayHalt("Could not get act!", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAB2220
void __cdecl sub_6FAB2220()
{
	sub_6FAA7440();
	FOG_10144(0);
	dword_6FBA796C = 0;
	dword_6FBA7974 = 1;
	dword_6FBA77D0 = GetTickCount();
}

//D2Client.0x6FAB2250
void __cdecl sub_6FAB2250()
{
	int iVar1;

	if (((gnGameType == 7) || (gnGameType == 9)) && (iVar1 = sub_6FAA9440(), iVar1 == 0))
	{
		sub_6FAA9850(8);
	}
	if (((gnGameType == 2) || (gnGameType == 3)) && (dword_6FBA796C != 0))
	{
		sub_6FAA9850(7);
	}
	dword_6FBA7970 = 1;
}

//D2Client.0x6FAB22A0
void __fastcall sub_6FAB22A0(int a1)
{
	uint16_t uVar1;
	uint16_t uVar2;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;

	uVar1 = *(uint16_t*)(a1 + 1);
	uVar2 = *(uint16_t*)(a1 + 3);
	D2_ASSERT(ghAct != nullptr);
	pUnit = CUNIT_GetPlayer();
	if (pUnit == nullptr)
	{
		pRoom = nullptr;
	}
	else
	{
		pRoom = UNITS_GetRoom(pUnit);
	}
	DUNGEON_SetClientIsInSight(ghAct, (uint32_t) * (uint8_t*)(a1 + 5), (uint32_t)uVar1, (uint32_t)uVar2, pRoom);
}

//D2Client.0x6FAB2310
void __fastcall sub_6FAB2310(int a1)
{
	uint16_t uVar1;
	uint16_t uVar2;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;

	uVar1 = *(uint16_t*)(a1 + 1);
	uVar2 = *(uint16_t*)(a1 + 3);
	D2_ASSERT(ghAct != nullptr);
	pUnit = CUNIT_GetPlayer();
	if (pUnit == nullptr)
	{
		pRoom = nullptr;
	}
	else
	{
		pRoom = UNITS_GetRoom(pUnit);
	}
	DUNGEON_UnsetClientIsInSight(ghAct, (uint32_t) * (uint8_t*)(a1 + 5), (uint32_t)uVar1, (uint32_t)uVar2, pRoom);
}

//D2Client.0x6FAB2380
void __fastcall sub_6FAB2380(int a1)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB27040(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 6),
	    (uint32_t) * (uint16_t*)(a1 + 7), (uint32_t) * (uint16_t*)(a1 + 9),
	    (uint32_t) * (uint8_t*)(a1 + 1), 0);
	if ((pDVar1 != nullptr) && (pDVar1->dwUnitType == 1))
	{
		sub_6FB5DAB0(pDVar1);
		return;
	}
}

//D2Client.0x6FAB23D0
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAB23D0(int a1)
{
	uint32_t in_EAX;
	uint32_t in_EDX;

	sub_6FB275C0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint16_t*)(a1 + 6), (uint32_t) * (uint16_t*)(a1 + 8),
	    (uint32_t) * (uint16_t*)(a1 + 10), (uint32_t) * (uint8_t*)(a1 + 1), 0,
	    CONCAT31((int32_t)((uint32_t)in_EDX >> 8), *(uint8_t*)(a1 + 0xc)),
	    CONCAT31((int32_t)((uint32_t)in_EAX >> 8), *(uint8_t*)(a1 + 0xd)));
}

//D2Client.0x6FAB2410
void __fastcall sub_6FAB2410(int a1)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	int iVar4;

	uVar1 = *(uint32_t*)(a1 + 2);
	if (*(char*)(a1 + 1) == '\x01')
	{
		iVar4 = 1;
		pDVar2 = CUNIT_GetPlayer();
		uVar3 = sub_6FAB1920((int)pDVar2, 7, iVar4);
		if (uVar1 == uVar3)
		{
			return;
		}
	}
	sub_6FB26BE0(uVar1, (uint32_t) * (uint8_t*)(a1 + 1));
}

//D2Client.0x6FAB2450
void __fastcall sub_6FAB2450(int a1)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar1 != nullptr)
	{
		sub_6FB28390(pDVar1);
	}
	MEMORY_Nop();
}

//D2Client.0x6FAB2470
void __fastcall sub_6FAB2470(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_1c[7];

	puVar2 = local_1c;
	for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	local_1c[0] = (uint32_t) * (uint8_t*)(a2 + 7);
	local_1c[1] = (uint32_t) * (uint8_t*)(a2 + 8);
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 6), pUnit, local_1c, 1);
}

//D2Client.0x6FAB24B0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAB24B0(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	uint32_t extraout_EDX;
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;

	local_1c = (uint32_t) * (uint16_t*)(a2 + 7);
	local_18 = (uint32_t) * (uint16_t*)(a2 + 9);
	local_14 = (uint32_t) * (uint8_t*)(a2 + 0xb);
	iVar1 = *(int*)(a2 + 2);
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 6), pUnit, &local_1c, 1);
	if (*(char*)(a2 + 1) == '\0')
	{
		sub_6FAB1420(iVar1, CONCAT31((int32_t)((uint32_t)extraout_EDX >> 8), *(uint8_t*)(a2 + 0xc)));
	}
}

//D2Client.0x6FAB2510
void __fastcall sub_6FAB2510(D2UnitStrc* pUnit, int a2)
{
	uint32_t local_1c;
	uint32_t local_18;

	local_1c = (uint32_t) * (uint8_t*)(a2 + 7);
	local_18 = *(uint32_t*)(a2 + 8);
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 6), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB2540
void __fastcall sub_6FAB2540(D2UnitStrc* pUnit, int a2)
{
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;

	local_1c = (uint32_t) * (uint16_t*)(a2 + 7);
	local_18 = (uint32_t) * (uint16_t*)(a2 + 9);
	local_14 = (uint32_t) * (uint8_t*)(a2 + 0xb);
	sub_6FB4DF90(pUnit, (uint32_t) * (uint16_t*)(a2 + 0xc), (uint32_t) * (uint16_t*)(a2 + 0xe), 0, 0, 0);
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 6), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB25A0
void __fastcall sub_6FAB25A0(D2UnitStrc* pUnit, int a2)
{
	uint16_t uVar1;
	uint32_t local_1c;
	uint32_t local_18;

	local_18 = *(uint32_t*)(a2 + 8);
	uVar1 = (uint16_t)((uint32_t)a2 >> 0x10);
	local_1c = (uint32_t) * (uint8_t*)(a2 + 7);
	sub_6FB4DF90(pUnit, CONCAT22(uVar1, *(uint16_t*)(a2 + 0xc)),
	    CONCAT22(uVar1, *(uint16_t*)(a2 + 0xe)), 0, 0, 0);
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 6), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB25F0
void __fastcall sub_6FAB25F0(D2UnitStrc* pUnit, int a2)
{
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;
	uint32_t local_10;
	int local_c;
	uint32_t local_8;
	uint32_t local_4;

	local_1c = (uint32_t) * (uint16_t*)(a2 + 6);
	local_18 = (uint32_t) * (uint16_t*)(a2 + 8);
	local_14 = (uint32_t) * (uint8_t*)(a2 + 10);
	local_10 = (uint32_t) * (uint8_t*)(a2 + 0xc);
	local_c = (int)*(short*)(a2 + 0xd);
	local_8 = (uint32_t) * (uint8_t*)(a2 + 0xf);
	local_4 = (uint32_t) * (uint8_t*)(a2 + 0xb);
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 5), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB2650
void __fastcall sub_6FAB2650(D2UnitStrc* pUnit, int a2)
{
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;
	uint32_t local_10;
	int local_c;
	uint32_t local_8;
	uint32_t local_4;

	local_1c = (uint32_t) * (uint8_t*)(a2 + 10);
	local_18 = *(uint32_t*)(a2 + 0xb);
	local_14 = (uint32_t) * (uint8_t*)(a2 + 0xf);
	local_c = (int)*(short*)(a2 + 0x12);
	local_10 = (uint32_t) * (uint8_t*)(a2 + 0x11);
	local_8 = (uint32_t) * (uint8_t*)(a2 + 0x14);
	local_4 = (uint32_t) * (uint8_t*)(a2 + 0x10);
	sub_6FB4DF90(pUnit, (uint32_t) * (uint16_t*)(a2 + 6),
	    CONCAT22(*(short*)(a2 + 0x12) >> 0xf, *(uint16_t*)(a2 + 8)), 0, 0, 0);
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 5), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB26D0
void __fastcall sub_6FAB26D0(D2UnitStrc* pUnit, int a2)
{
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint32_t local_4;

	local_1c = (uint32_t) * (uint16_t*)(a2 + 6);
	local_18 = (uint32_t) * (uint16_t*)(a2 + 8);
	local_14 = (uint32_t) * (uint8_t*)(a2 + 10);
	local_10 = 2;
	local_4 = (uint32_t) * (uint8_t*)(a2 + 0xb);
	local_c = 0;
	local_8 = 4;
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 5), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB2730
void __fastcall sub_6FAB2730(D2UnitStrc* pUnit, int a2)
{
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;

	local_1c = (uint32_t) * (uint8_t*)(a2 + 6);
	local_18 = *(uint32_t*)(a2 + 7);
	local_14 = (uint32_t) * (uint8_t*)(a2 + 0xb);
	local_10 = 2;
	local_c = 0;
	local_8 = 4;
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 5), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB2790
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAB2790(D2UnitStrc* pUnit, int a2)
{
	uint32_t in_EAX;
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint32_t local_4;

	sub_6FB4DF90(pUnit, CONCAT22((short)((uint32_t)a2 >> 0x10), *(uint16_t*)(a2 + 0xc)),
	    CONCAT22((short)((uint32_t)in_EAX >> 0x10), *(uint16_t*)(a2 + 0xe)), 0, 0, 0);
	local_1c = (uint32_t) * (uint16_t*)(a2 + 6);
	local_18 = (uint32_t) * (uint16_t*)(a2 + 8);
	local_4 = (uint32_t) * (uint8_t*)(a2 + 0xb);
	local_14 = (uint32_t) * (uint8_t*)(a2 + 10);
	local_10 = 2;
	local_c = 0;
	local_8 = 4;
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 5), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB2810
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAB2810(D2UnitStrc* pUnit, int a2)
{
	uint32_t in_EAX;
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;

	sub_6FB4DF90(pUnit, CONCAT22((short)((uint32_t)a2 >> 0x10), *(uint16_t*)(a2 + 0xc)),
	    CONCAT22((short)((uint32_t)in_EAX >> 0x10), *(uint16_t*)(a2 + 0xe)), 0, 0, 0);
	local_18 = *(uint32_t*)(a2 + 7);
	local_1c = (uint32_t) * (uint8_t*)(a2 + 6);
	local_14 = (uint32_t) * (uint8_t*)(a2 + 0xb);
	local_10 = 2;
	local_c = 0;
	local_8 = 4;
	sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 5), pUnit, &local_1c, 1);
}

//D2Client.0x6FAB2880
// TODO: decompilation needs review (unaff_)
void __fastcall sub_6FAB2880(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	uint32_t unaff_EDI;
	uint16_t nLayer;
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint32_t local_4;

	if ((pUnit != nullptr) && (a2 != 0))
	{
		local_1c = (uint32_t) * (uint16_t*)(a2 + 5);
		local_18 = (uint32_t) * (uint16_t*)(a2 + 7);
		local_14 = (uint32_t) * (uint8_t*)(a2 + 9);
		local_10 = 2;
		local_c = 0;
		local_8 = 4;
		local_4 = 0;
		sub_6FB4DF90(pUnit, CONCAT22((short)((uint32_t)a2 >> 0x10), *(uint16_t*)(a2 + 5)),
		    CONCAT22((short)((uint32_t)unaff_EDI >> 0x10), *(uint16_t*)(a2 + 7)), 0, 0, 0);
		nLayer = 0;
		iVar1 = STATLIST_GetUnitBaseStat(pUnit, 0x148, 0);
		STATLIST_SetUnitStat(pUnit, 0x148, iVar1 + 1, nLayer);
		sub_6FB4EE00(7, pUnit, &local_1c, 1);
	}
}

//D2Client.0x6FAB2930
void __fastcall sub_6FAB2930(int a1)
{
	uint16_t uVar1;
	D2UnitStrc* pDVar2;

	uVar1 = *(uint16_t*)(a1 + 6);
	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if ((pDVar2 != nullptr) &&
	    ((int)(uint32_t)uVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0)))
	{
		sub_6FB29D10(pDVar2, (uint32_t)uVar1, 0);
	}
}

//D2Client.0x6FAB2970
void __fastcall sub_6FAB2970(int a1)
{
	uint16_t uVar1;
	uint16_t uVar2;
	uint8_t bVar3;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pDVar4;
	int iVar5;
	D2UnitStrc* pDVar6;

	uVar1 = *(uint16_t*)(a1 + 6);
	uVar2 = *(uint16_t*)(a1 + 8);
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pUnit != nullptr)
	{
		sub_6FB26DD0(pUnit, (char*)(uint32_t)uVar1, (char*)(uint32_t)uVar2, (uint32_t) * (uint8_t*)(a1 + 10));
		pDVar4 = UNITS_GetRoom(pUnit);
		if (pDVar4 == nullptr)
		{
			FOG_DisplayHalt("Could not get act!", __FILE__, __LINE__);
			exit(-1);
		}
		iVar5 = DUNGEON_GetLevelIdFromRoom(pDVar4);
		bVar3 = DRLG_GetActNoFromLevelId(iVar5);
		pUnit->nAct = bVar3;
		pUnit->pDrlgAct = ghAct;
		if (pUnit->pDynamicPath != nullptr)
		{
			if (pUnit->dwUnitType == 0)
			{
				D2Common_10214(pUnit);
				PATH_SetMoveTestCollisionMask(pUnit->pDynamicPath, 0x1c09);
			}
			else if (pUnit->dwUnitType == 1)
			{
				iVar5 = MONSTERS_IsDead(pUnit);
				if (iVar5 == 0)
				{
					PATH_SetFootprintCollisionMask(pUnit->pDynamicPath, 0x100);
				}
			}
		}
		pDVar6 = CUNIT_GetPlayer();
		if (pUnit == pDVar6)
		{
			pDVar4 = UNITS_GetRoom(pUnit);
			iVar5 = D2COMMON_10083_Return0(pDVar4);
			if (iVar5 != 0)
			{
				FOG_DisplayHalt("Illegal packet in sSCmd_UnitWarpXY",
				    __FILE__, __LINE__);
				exit(-1);
			}
			sub_6FAAC000(3000);
			return;
		}
	}
}

//D2Client.0x6FAB2A80
void __fastcall sub_6FAB2A80(D2UnitStrc* hUnit, int a2)
{
	D2UnitStrc* pDVar1;
	uint16_t local_20;
	uint16_t local_1e;
	uint32_t local_1c;
	uint16_t* local_18;

	pDVar1 = CUNIT_GetPlayer();
	if (hUnit != pDVar1)
	{
		D2_ASSERT(hUnit != nullptr);
		local_20 = *(uint16_t*)(uint32_t) * (uint16_t*)(a2 + 8);
		local_1e = *(uint16_t*)(uint32_t) * (uint16_t*)(a2 + 10);
		local_18 = &local_20;
		local_1c = (uint32_t)(*(uint8_t*)(a2 + 6) >> 1);
		sub_6FB4EE00((uint32_t) * (uint8_t*)(a2 + 7), hUnit, &local_1c, 1);
	}
}

//D2Client.0x6FAB2B00
// TODO: decompilation needs review (unaff_)
void __fastcall sub_6FAB2B00(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t unaff_EBX;
	int iVar2;
	uint8_t* pbVar3;
	uint32_t unaff_EDI;

	if (*(char*)(a1 + 3) != '\0')
	{
		iVar2 = 0;
		pbVar3 = (uint8_t*)(a1 + 4);
		if (*(char*)(a1 + 3) != '\0')
		{
			do
			{
				unaff_EDI = CONCAT22((short)((uint32_t)unaff_EDI >> 0x10), *(uint16_t*)(pbVar3 + 5));
				unaff_EBX = CONCAT22((short)(unaff_EBX >> 0x10), *(uint16_t*)(pbVar3 + 7));
				pDVar1 = sub_6FB269F0(*(uint32_t*)(pbVar3 + 1), (uint32_t)*pbVar3);
				if (pDVar1 != nullptr)
				{
					sub_6FB4DF90(pDVar1, unaff_EDI, unaff_EBX, 0, 0, 0);
				}
				pbVar3 = pbVar3 + 9;
				iVar2 = iVar2 + 1;
			} while (iVar2 < (int)(uint32_t) * (uint8_t*)(a1 + 3));
		}
		return;
	}
	FOG_DisplayAssert("ptCmd->bNumUpdates != 0", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAB2B80
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAB2B80(int a1)
{
	uint32_t in_EAX;

	sub_6FAF8250(*(uint8_t*)(a1 + 1), *(uint32_t*)(a1 + 2), (uint8_t*)(a1 + 7),
	    CONCAT31((int32_t)((uint32_t)in_EAX >> 8), *(uint8_t*)(a1 + 6)));
}

//D2Client.0x6FAB2BA0
void __fastcall sub_6FAB2BA0(int a1)
{
	sub_6FAF8000(*(uint8_t*)(a1 + 1), *(uint32_t*)(a1 + 2));
}

//D2Client.0x6FAB2BB0
void __fastcall sub_6FAB2BB0(int a1)
{
	sub_6FAF7FE0((uint8_t*)(a1 + 1));
}

//D2Client.0x6FAB2BC0
void __fastcall sub_6FAB2BC0(D2UnitStrc* pUnit2)
{
	D2SkillStrc* pDVar1;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pUnit;
	int iStack_c;
	int local_8;
	int local_4;

	if ((pUnit2 != nullptr) && (pUnit2->pInventory != nullptr))
	{
		pDVar1 = pUnit2->pSkills->pLeftSkill;
		if (pDVar1 == nullptr)
		{
			local_8 = 0;
		}
		else
		{
			local_8 = (int)pDVar1->pSkillsTxt->nSkillId;
		}
		pDVar1 = pUnit2->pSkills->pRightSkill;
		if (pDVar1 == nullptr)
		{
			local_4 = 0;
		}
		else
		{
			local_4 = (int)pDVar1->pSkillsTxt->nSkillId;
		}
		pItem = INVENTORY_GetFirstItem(pUnit2->pInventory);
		while (pItem != nullptr)
		{
			pDVar2 = INVENTORY_GetNextItem(pItem);
			pUnit = INVENTORY_UnitIsItem(pItem);
			iStack_c = 0;
			pItem = pDVar2;
			if (((pUnit != nullptr) && (pUnit->dwUnitType == 4)) &&
			    (pDVar2 = STATLIST_GetOwner(pUnit, &iStack_c), pDVar2 != nullptr))
			{
				STATLIST_ExpireUnitStatlist(pUnit2, pUnit);
				STATLIST_MergeStatLists(pUnit2, pUnit, iStack_c);
			}
		}
		SKILLS_SetLeftActiveSkill(pUnit2, local_8, 0xffffffff);
		SKILLS_SetRightActiveSkill(pUnit2, local_4, 0xffffffff);
	}
}

//D2Client.0x6FAB2C90
void __fastcall sub_6FAB2C90(uint8_t* a1)
{
	uint8_t bVar1;
	bool bVar2;
	D2UnitStrc* pUnit;
	uint32_t nValue;
	uint32_t nStatId;
	uint8_t local_c;
	uint8_t local_b;
	uint32_t local_9;

	bVar2 = false;
	switch (*a1)
	{
	case 0x9e:
		nValue = (uint32_t)(uint8_t)a1[6];
		break;
	case 0xa0:
		nValue = *(uint32_t*)(a1 + 6);
		bVar1 = a1[1];
		goto LAB_6fab2ceb;
	case 0xa1:
		nValue = (uint32_t)(uint8_t)a1[6];
		bVar2 = true;
		break;
	case 0xa2:
		bVar2 = true;
	case 0x9f:
		nValue = (uint32_t) * (uint16_t*)(a1 + 6);
		break;
	default:
		goto switchD_6fab2cab_default;
	}
	bVar1 = a1[1];
LAB_6fab2ceb:
	nStatId = (uint32_t)bVar1;
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), 1);
	if (pUnit != nullptr)
	{
		if (nStatId == 0xc)
		{
			local_b = (uint8_t)pUnit->dwUnitType;
			local_9 = pUnit->dwUnitId;
			local_c = 0x47;
			sub_6FB2C2B0((int)&local_c);
		}
		if (bVar2)
		{
			STATLIST_AddUnitStat(pUnit, nStatId, nValue, 0);
			return;
		}
		STATLIST_SetUnitStat(pUnit, nStatId, nValue, 0);
	}
switchD_6fab2cab_default:
}

//D2Client.0x6FAB2D60
void __fastcall sub_6FAB2D60(int a1)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	int iVar4;

	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 7), (uint32_t) * (uint8_t*)(a1 + 6));
	if (pDVar2 != nullptr)
	{
		pDVar3 = sub_6FB269F0(*(uint32_t*)(a1 + 0xc), (uint32_t) * (uint8_t*)(a1 + 0xb));
		iVar4 = (int)*(short*)(a1 + 2);
		if (((-1 < iVar4) && (iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar4 * 0x23c, iVar1 != 0))
		{
			if (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar1 + 4)) != 0)
			{
				sub_6FABCD70(pDVar2, pDVar3, iVar4, (int)*(short*)(a1 + 4), *(int*)(a1 + 0x10),
				    *(int*)(a1 + 0x14), (uint32_t) * (uint8_t*)(a1 + 1));
				return;
			}
			sub_6FABCA70(pDVar2, pDVar3, iVar4, (int)*(short*)(a1 + 4), *(int*)(a1 + 0x10),
			    *(int*)(a1 + 0x14),
			    CONCAT31((int32_t)((uint32_t)iVar1 >> 8), *(uint8_t*)(a1 + 1)));
		}
	}
}

//D2Client.0x6FAB2E20
void __fastcall sub_6FAB2E20(int a1)
{
	int iVar1;
	uint16_t uVar2;
	D2UnitStrc* pUnit;

	uVar2 = *(uint16_t*)(a1 + 6);
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (((pUnit != nullptr) &&
	        ((int)(uint32_t)uVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + (uint32_t)uVar2 * 0x23c, iVar1 != 0))
	{
		switch (*(uint16_t*)(iVar1 + 0x2e))
		{
		case 0x43:
			sub_6FAC9E50(pUnit);
			STATES_ToggleState(pUnit, 0x12, 0);
			return;
		case 0x4c:
			sub_6FAC2800(pUnit);
			break;
		case 0x4d:
		case 0x4e:
			sub_6FAC1C00(pUnit);
			STATES_ToggleState(pUnit, 0x12, 0);
			return;
		}
		STATES_ToggleState(pUnit, 0x12, 0);
	}
}

//D2Client.0x6FAB2EE0
void __fastcall sub_6FAB2EE0(int a1)
{
	if ((int)(uint32_t) * (uint16_t*)(a1 + 1) < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))
	{
		sub_6FB5CC40((uint32_t) * (uint16_t*)(a1 + 1), 0);
		return;
	}
}

//D2Client.0x6FAB2F10
void __fastcall sub_6FAB2F10(uint8_t* a1)
{
	uint8_t uVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	uint32_t nStatId;
	uint32_t nValue;

	nValue = 0;
	nStatId = 0xffffffff;
	uVar1 = *a1;
	pUnit = CUNIT_GetPlayer();
	D2_ASSERT(pUnit != nullptr);
	switch (uVar1)
	{
	case 0x19:
		nStatId = 0xe;
		iVar2 = STATLIST_UnitGetStatValue(pUnit, 0xe, 0);
		nValue = iVar2 + (uint32_t)(uint8_t)a1[1];
		break;
	case 0x1a:
		nStatId = 0xd;
		iVar2 = STATLIST_UnitGetStatValue(pUnit, 0xd, 0);
		nValue = iVar2 + (uint32_t)(uint8_t)a1[1];
		break;
	case 0x1b:
		nStatId = 0xd;
		iVar2 = STATLIST_UnitGetStatValue(pUnit, 0xd, 0);
		nValue = iVar2 + (uint32_t) * (uint16_t*)(a1 + 1);
		break;
	case 0x1c:
		nValue = *(uint32_t*)(a1 + 1);
		nStatId = 0xd;
		break;
	case 0x1d:
		nValue = (uint32_t)(uint8_t)a1[2];
		goto LAB_6fab2fd6;
	case 0x1e:
		nValue = (uint32_t) * (uint16_t*)(a1 + 2);
		goto LAB_6fab2fd6;
	case 0x1f:
		nValue = *(uint32_t*)(a1 + 2);
	LAB_6fab2fd6:
		nStatId = (uint32_t)(uint8_t)a1[1];
	}
	STATLIST_SetUnitStat(pUnit, nStatId, nValue, 0);
	if (0xc < nStatId)
	{
		return;
	}
	switch (nStatId)
	{
	case STAT_STRENGTH:
	case STAT_DEXTERITY:
		sub_6FB2B360(pUnit);
		break;
	case STAT_HITPOINTS:
		if (nValue != 0 && pUnit->dwAnimMode == PLRMODE_DEATH)
		{
			sub_6FB4F410(pUnit, (int*)0x5);
			sub_6FB294B0((int*)pUnit);
		}
		break;
	case STAT_LEVEL:
		if (D2UnitStrc* pPlayer = CUNIT_GetPlayer())
		{
			uint8_t pPacket[7] = {};
			pPacket[0] = 0x47;
			pPacket[1] = (uint8_t)pPlayer->dwUnitType;
			*(uint32_t*)&pPacket[3] = pPlayer->dwUnitId;
			sub_6FB2C2B0((int)pPacket);
		}
		if (pUnit == CUNIT_GetPlayer())
		{
			sub_6FAB2BC0(pUnit);
			sub_6FB2B360(pUnit);
		}
		break;
	}
}

//D2Client.0x6FAB30A0
void __fastcall sub_6FAB30A0(int a1)
{
	uint8_t bVar1;
	int nValue;
	D2UnitStrc* pUnit;
	D2UnitStrc* pDVar2;
	uint8_t uStack_c;
	uint8_t uStack_b;
	uint32_t uStack_9;

	nValue = *(int*)(a1 + 6);
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 1), 0);
	if (pUnit != nullptr)
	{
		bVar1 = *(uint8_t*)(a1 + 5);
		STATLIST_SetUnitStat(pUnit, (uint32_t)bVar1, nValue, 0);
		switch ((uint32_t)bVar1)
		{
		case 6:
			if ((nValue != 0) && (pUnit->dwAnimMode == 0x11))
			{
				sub_6FB4F410(pUnit, (int*)0x5);
				sub_6FB294B0((int*)pUnit);
				return;
			}
			break;
		case 0xc:
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 != nullptr)
			{
				uStack_9 = pDVar2->dwUnitId;
				uStack_b = (uint8_t)pDVar2->dwUnitType;
				uStack_c = 0x47;
				sub_6FB2C2B0((int)&uStack_c);
			}
			pDVar2 = CUNIT_GetPlayer();
			if (pUnit != pDVar2)
			{
				return;
			}
			sub_6FAB2BC0(pUnit);
		case 0:
		case 2:
			sub_6FB2B360(pUnit);
		}
	}
}

//D2Client.0x6FAB3170
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAB3170()
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	D2UnitStrc* pUnit;
	uint8_t* in_ECX;
	uint8_t uStack_1d;
	uint8_t uStack_1c;
	D2BitBufferStrc local_14;

	BITMANIP_Initialize(&local_14, in_ECX, 0xf);
	BITMANIP_Read(&local_14, 8);
	uVar2 = BITMANIP_Read(&local_14, 0xf);
	uVar3 = BITMANIP_Read(&local_14, 0xf);
	uVar4 = BITMANIP_Read(&local_14, 0xf);
	uVar5 = BITMANIP_Read(&local_14, 7);
	uVar6 = BITMANIP_Read(&local_14, 7);
	uVar7 = BITMANIP_Read(&local_14, 0x10);
	uVar8 = BITMANIP_Read(&local_14, 0x10);
	uStack_1d = (uint8_t)uVar8;
	uStack_1c = (uint8_t)(uVar8 >> 8);
	uVar9 = BITMANIP_Read(&local_14, 8);
	uVar10 = BITMANIP_Read(&local_14, 8);
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		STATLIST_SetUnitStat(pUnit, 6, (uVar2 & 0xffff) << 8, 0);
		STATLIST_SetUnitStat(pUnit, 8, (uVar3 & 0xffff) << 8, 0);
		STATLIST_SetUnitStat(pUnit, 10, (CONCAT12((char)uVar5, (short)uVar4) & 0xffff) << 8, 0);
		STATLIST_SetUnitStat(pUnit, 0x4a, CONCAT11((char)uVar6, (char)uVar5) & 0xff, 0);
		STATLIST_SetUnitStat(pUnit, 0x1a, CONCAT21((short)uVar7, (char)uVar6) & 0xff, 0);
		uVar3 = uVar10 & 0xff;
		uVar4 = CONCAT11((char)uVar10, (char)uVar9) & 0xff;
		if (0x80 < uVar4)
		{
			uVar4 = uVar4 - 0x100;
		}
		if (0x80 < uVar3)
		{
			uVar3 = uVar3 - 0x100;
		}
		uVar5 = CONCAT13((char)uVar10, CONCAT12((char)uVar9, (short)uVar8));
		iVar1 = CONCAT13(uStack_1c, CONCAT12(uStack_1d, (short)uVar7));
		sub_6FB4DF90(pUnit, iVar1, uVar5, 0, uVar4 + iVar1 & 0xffff, uVar3 + uVar5 & 0xffff);
		if (((uVar2 & 0xffff) != 0) && (pUnit->dwAnimMode == 0x11))
		{
			sub_6FB4F410(pUnit, (int*)0x5);
			sub_6FB294B0((int*)pUnit);
		}
	}
}

//D2Client.0x6FAB3320
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAB3320()
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	D2UnitStrc* pUnit;
	uint8_t* in_ECX;
	D2BitBufferStrc local_14;

	BITMANIP_Initialize(&local_14, in_ECX, 0xd);
	BITMANIP_Read(&local_14, 8);
	uVar2 = BITMANIP_Read(&local_14, 0xf);
	uVar3 = BITMANIP_Read(&local_14, 0xf);
	uVar4 = BITMANIP_Read(&local_14, 0xf);
	uVar5 = BITMANIP_Read(&local_14, 0x10);
	uVar6 = BITMANIP_Read(&local_14, 0x10);
	uVar7 = BITMANIP_Read(&local_14, 8);
	uVar8 = BITMANIP_Read(&local_14, 8);
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		STATLIST_SetUnitStat(pUnit, 6, (uVar2 & 0xffff) << 8, 0);
		STATLIST_SetUnitStat(pUnit, 8, (uVar3 & 0xffff) << 8, 0);
		STATLIST_SetUnitStat(pUnit, 10, (uVar4 & 0xffff) << 8, 0);
		uVar3 = uVar8 & 0xff;
		uVar4 = CONCAT11((char)uVar8, (char)uVar7) & 0xff;
		if (0x80 < uVar4)
		{
			uVar4 = uVar4 - 0x100;
		}
		if (0x80 < uVar3)
		{
			uVar3 = uVar3 - 0x100;
		}
		uVar7 = CONCAT13((char)uVar8, CONCAT12((char)uVar7, (short)uVar6));
		iVar1 = CONCAT22((short)uVar6, (short)uVar5);
		sub_6FB4DF90(pUnit, iVar1, uVar7, 0, uVar4 + iVar1 & 0xffff, uVar3 + uVar7 & 0xffff);
		if (((uVar2 & 0xffff) != 0) && (pUnit->dwAnimMode == 0x11))
		{
			sub_6FB4F410(pUnit, (int*)0x5);
			sub_6FB294B0((int*)pUnit);
		}
	}
}

//D2Client.0x6FAB3480
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAB3480()
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	D2UnitStrc* pUnit;
	uint32_t uVar7;
	uint8_t* in_ECX;
	D2BitBufferStrc local_14;

	BITMANIP_Initialize(&local_14, in_ECX, 9);
	BITMANIP_Read(&local_14, 8);
	uVar2 = BITMANIP_Read(&local_14, 0xf);
	uVar3 = BITMANIP_Read(&local_14, 0x10);
	uVar4 = BITMANIP_Read(&local_14, 0x10);
	uVar5 = BITMANIP_Read(&local_14, 8);
	uVar6 = BITMANIP_Read(&local_14, 8);
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		STATLIST_SetUnitStat(pUnit, 10, (uVar2 & 0xffff) << 8, 0);
		uVar2 = uVar6 & 0xff;
		uVar7 = CONCAT11((char)uVar6, (char)uVar5) & 0xff;
		if (0x80 < uVar7)
		{
			uVar7 = uVar7 - 0x100;
		}
		if (0x80 < uVar2)
		{
			uVar2 = uVar2 - 0x100;
		}
		iVar1 = CONCAT22((short)uVar4, (short)uVar3);
		uVar3 = CONCAT13((char)uVar6, CONCAT12((char)uVar5, (short)uVar4));
		sub_6FB4DF90(pUnit, iVar1, uVar3, 0, uVar7 + iVar1 & 0xffff, uVar2 + uVar3 & 0xffff);
	}
}

//D2Client.0x6FAB3570
void __fastcall sub_6FAB3570(int a1)
{
	uint16_t uVar1;
	D2UnitStrc* pUnit;

	uVar1 = *(uint16_t*)(a1 + 7);
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 3), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pUnit != nullptr)
	{
		SKILLS_AssignSkill(pUnit, (uint32_t)uVar1, (uint32_t) * (uint8_t*)(a1 + 9), (uint32_t) * (uint8_t*)(a1 + 2),
		    __FILE__, __LINE__);
		sub_6FB16300();
		return;
	}
}

//D2Client.0x6FAB35C0
void __fastcall sub_6FAB35C0(int a1)
{
	uint8_t bVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	uint32_t local_4;

	uVar3 = (uint32_t) * (uint8_t*)(a1 + 5);
	if (0x80 < uVar3)
	{
		uVar3 = uVar3 - 0x100;
	}
	bVar1 = *(uint8_t*)(a1 + 6);
	local_4 = CONCAT31((int32_t)((uint32_t)a1 >> 8), *(uint8_t*)(a1 + 7));
	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 1), 0);
	if (pDVar2 != nullptr)
	{
		sub_6FABDE30(pDVar2, uVar3, (uint32_t)bVar1, local_4);
	}
}

//D2Client.0x6FAB3610
void __fastcall sub_6FAB3610(int a1)
{
	uint8_t bVar1;
	D2UnitStrc* pUnit;
	uint32_t uVar2;
	uint16_t* puVar3;

	bVar1 = *(uint8_t*)(a1 + 1);
	puVar3 = (uint16_t*)(a1 + 6);
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), 0);
	if ((pUnit != nullptr) && (uVar2 = (uint32_t)bVar1, bVar1 != 0))
	{
		do
		{
			SKILLS_AssignSkill(pUnit, (uint32_t)*puVar3, (uint32_t)(uint8_t)puVar3[1], 0,
			    __FILE__, __LINE__);
			puVar3 = (uint16_t*)((int)puVar3 + 3);
			uVar2 = uVar2 - 1;
		} while (uVar2 != 0);
	}
}

//D2Client.0x6FAB3670
void __fastcall sub_6FAB3670(int a1)
{
	uint16_t uVar1;
	D2UnitStrc* pUnit;
	D2SkillStrc* pSkill;

	if (*(char*)(a1 + 0xb) == '\0')
	{
		uVar1 = *(uint16_t*)(a1 + 7);
		pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 3), 0);
		if (pUnit != nullptr)
		{
			pSkill = SKILLS_GetSkillById(pUnit, (uint32_t)uVar1, 0xffffffff);
			D2_ASSERT(pSkill != nullptr);
			SKILLS_SetQuantity(pSkill, (uint32_t) * (uint8_t*)(a1 + 9));
		}
	}
}

//D2Client.0x6FAB36D0
void __fastcall sub_6FAB36D0(int a1)
{
	uint16_t uVar1;
	uint32_t nOwnerGUID;
	D2UnitStrc* pUnit;

	uVar1 = *(uint16_t*)(a1 + 7);
	nOwnerGUID = *(uint32_t*)(a1 + 9);
	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), 0);
	if (pUnit != nullptr)
	{
		if (*(char*)(a1 + 6) != '\0')
		{
			SKILLS_SetLeftActiveSkill(pUnit, (uint32_t)uVar1, nOwnerGUID);
			return;
		}
		SKILLS_SetRightActiveSkill(pUnit, (uint32_t)uVar1, nOwnerGUID);
	}
}

//D2Client.0x6FAB3710
void __fastcall sub_6FAB3710(uint32_t* a1)
{
	uint32_t local_8;
	uint16_t local_4;
	uint8_t local_2;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	local_2 = *(uint8_t*)((int)a1 + 6);
	sub_6FB44880((int)&local_8);
}

//D2Client.0x6FAB3740
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAB3740(int a1)
{
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	uint16_t extraout_var;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar1 != nullptr)
	{
		pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 10), (uint32_t) * (uint8_t*)(a1 + 9));
		if (pDVar2 != nullptr)
		{
			sub_6FABA7F0(pDVar1, (uint32_t) * (uint16_t*)(a1 + 6), (uint32_t) * (uint8_t*)(a1 + 8), (int)pDVar2,
			    D2C_ZEXT(*(uint16_t*)(a1 + 0xe)));
		}
	}
}

//D2Client.0x6FAB3790
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAB3790(int a1)
{
	D2UnitStrc* pDVar1;
	uint16_t extraout_var;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar1 != nullptr)
	{
		sub_6FABA820(pDVar1, (uint32_t) * (uint16_t*)(a1 + 6), (uint32_t) * (uint8_t*)(a1 + 10),
		    (uint32_t) * (uint16_t*)(a1 + 0xb), (uint32_t) * (uint16_t*)(a1 + 0xd),
		    D2C_ZEXT(*(uint16_t*)(a1 + 0xf)));
	}
}

//D2Client.0x6FAB37D0
void __fastcall sub_6FAB37D0(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_1c[4];
	uint32_t local_c;

	if (pUnit != nullptr)
	{
		puVar2 = local_1c;
		for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar2 = 0;
			puVar2 = puVar2 + 1;
		}
		local_1c[0] = (uint32_t) * (uint16_t*)(a2 + 6);
		local_1c[2] = (uint32_t) * (uint8_t*)(a2 + 9);
		local_1c[3] = *(uint32_t*)(a2 + 10);
		local_c = (uint32_t) * (uint8_t*)(a2 + 8);
		local_1c[1] = 0xffffffff;
		sub_6FB4EE00(0x16, pUnit, local_1c, 1);
	}
}

//D2Client.0x6FAB3830
void __fastcall sub_6FAB3830(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_1c[4];
	uint32_t local_c;

	if (pUnit != nullptr)
	{
		puVar2 = local_1c;
		for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar2 = 0;
			puVar2 = puVar2 + 1;
		}
		local_1c[0] = *(uint32_t*)(a2 + 6);
		local_1c[2] = (uint32_t) * (uint16_t*)(a2 + 0xb);
		local_1c[3] = (uint32_t) * (uint16_t*)(a2 + 0xd);
		local_c = (uint32_t) * (uint8_t*)(a2 + 10);
		local_1c[1] = 0xffffffff;
		sub_6FB4EE00(0x15, pUnit, local_1c, 1);
	}
}

//D2Client.0x6FAB3890
void __fastcall sub_6FAB3890(int a1)
{
	uint32_t uVar1;
	uint8_t local_11c;
	uint8_t local_11b;
	uint8_t local_11a;
	uint8_t local_119;
	uint32_t local_118;
	uint8_t local_114;
	uint8_t local_113;
	char local_112[16];
	char acStack_102[258];

	local_11c = *(uint8_t*)a1;
	local_11b = *(uint8_t*)(a1 + 1);
	local_11a = *(uint8_t*)(a1 + 2);
	local_119 = *(uint8_t*)(a1 + 3);
	local_118 = *(uint32_t*)(a1 + 4);
	local_114 = *(uint8_t*)(a1 + 8);
	local_113 = *(uint8_t*)(a1 + 9);
	SStrCopy(local_112, (char*)(a1 + 10), 0x10);
	uVar1 = SStrLen((char*)(a1 + 10));
	SStrCopy(acStack_102, (char*)(a1 + 0xb + uVar1), 0x100);
	sub_6FB1E120((int)&local_11c);
}

//D2Client.0x6FAB3910
void __fastcall sub_6FAB3910(uint32_t* a1)
{
	uint32_t local_8;
	uint16_t local_4;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	sub_6FB1E670((int)&local_8);
}

//D2Client.0x6FAB3930
void __fastcall sub_6FAB3930(uint32_t* a1)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_28[10];

	puVar2 = local_28;
	for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = *a1;
		a1 = a1 + 1;
		puVar2 = puVar2 + 1;
	}
	sub_6FB1D3C0((int)local_28);
}

//D2Client.0x6FAB3960
void __fastcall sub_6FAB3960(uint32_t* a1)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_28[10];

	puVar2 = local_28;
	for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = *a1;
		a1 = a1 + 1;
		puVar2 = puVar2 + 1;
	}
	sub_6FB1DE10((int)local_28);
}

//D2Client.0x6FAB3990
void __fastcall sub_6FAB3990(uint32_t* a1)
{
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint16_t local_4;
	uint8_t local_2;

	local_10 = *a1;
	local_c = a1[1];
	local_8 = a1[2];
	local_4 = *(uint16_t*)(a1 + 3);
	local_2 = *(uint8_t*)((int)a1 + 0xe);
	sub_6FAF5880(&local_10);
}

//D2Client.0x6FAB39D0
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAB39D0(int a1, uint32_t a2)
{
	uint32_t in_EAX;

	sub_6FB51920(*(uint32_t*)(a1 + 2),
	    CONCAT31((int32_t)((uint32_t)a2 >> 8), *(uint8_t*)(a1 + 1)),
	    CONCAT22((short)((uint32_t)in_EAX >> 0x10), *(uint16_t*)(a1 + 6)));
}

//D2Client.0x6FAB39F0
void __fastcall sub_6FAB39F0(int a1)
{
	uint32_t uVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	D2BitBufferStrc local_14;

	BITMANIP_Initialize(&local_14, (uint8_t*)(a1 + 2), *(uint8_t*)(a1 + 1) - 2);
	uVar1 = BITMANIP_Read(&local_14, 1);
	if (uVar1 == 0)
	{
		iVar6 = 8;
	}
	else
	{
		uVar1 = BITMANIP_Read(&local_14, 1);
		if (uVar1 == 0)
		{
			iVar6 = 0x10;
		}
		else
		{
			iVar6 = 0x20;
		}
	}
	uVar1 = BITMANIP_Read(&local_14, iVar6);
	uVar2 = BITMANIP_Read(&local_14, 1);
	uVar3 = BITMANIP_Read(&local_14, 9);
	uVar4 = BITMANIP_Read(&local_14, 1);
	if (uVar4 == 0)
	{
		iVar6 = 8;
	}
	else
	{
		uVar4 = BITMANIP_Read(&local_14, 1);
		if (uVar4 == 0)
		{
			iVar6 = 0x10;
		}
		else
		{
			iVar6 = 0x20;
		}
	}
	uVar4 = BITMANIP_Read(&local_14, iVar6);
	uVar5 = BITMANIP_Read(&local_14, 1);
	if (uVar5 == 0)
	{
		iVar6 = 8;
	}
	else
	{
		iVar6 = 0x10;
	}
	uVar5 = BITMANIP_Read(&local_14, iVar6);
	sub_6FB2E780(uVar1, (char)uVar2, uVar3, uVar4, uVar5);
}

//D2Client.0x6FAB3AE0
void __fastcall sub_6FAB3AE0(uint32_t* a1)
{
	uint32_t local_8;
	uint32_t local_4;

	local_8 = *a1;
	local_4 = a1[1];
	sub_6FB2E880((int)&local_8);
}

//D2Client.0x6FAB3B00
void __fastcall sub_6FAB3B00(uint32_t* a1)
{
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint8_t local_4;

	local_10 = *a1;
	local_c = a1[1];
	local_8 = a1[2];
	local_4 = *(uint8_t*)(a1 + 3);
	sub_6FB2E9D0((int)&local_10);
}

//D2Client.0x6FAB3B30
void __fastcall sub_6FAB3B30(uint32_t* a1)
{
	uint32_t local_8;
	uint16_t local_4;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	sub_6FB2EDA0((int)&local_8);
}

//D2Client.0x6FAB3B50
void __fastcall sub_6FAB3B50(uint32_t* a1)
{
	uint32_t local_c;
	uint32_t local_8;
	uint16_t local_4;
	uint8_t local_2;

	local_c = *a1;
	local_8 = a1[1];
	local_4 = *(uint16_t*)(a1 + 2);
	local_2 = *(uint8_t*)((int)a1 + 10);
	sub_6FB2C2B0((int)&local_c);
}

//D2Client.0x6FAB3B90
void __fastcall sub_6FAB3B90(uint32_t* a1)
{
	uint32_t local_c;
	uint32_t local_8;
	uint16_t local_4;
	uint8_t local_2;

	local_c = *a1;
	local_8 = a1[1];
	local_4 = *(uint16_t*)(a1 + 2);
	local_2 = *(uint8_t*)((int)a1 + 10);
	sub_6FB2C2D0((int)&local_c);
}

//D2Client.0x6FAB3BC0
void __fastcall sub_6FAB3BC0(int a1)
{
	D2UnitStrc* pDVar1;
	D2ActiveRoomStrc* pRoom;
	uint32_t bEclipse;
	int nIndex;
	int nTicks;
	uint8_t uStack_c;
	uint8_t uStack_b;
	uint32_t uStack_9;

	nIndex = *(int*)(a1 + 1);
	nTicks = *(int*)(a1 + 5);
	pDVar1 = CUNIT_GetPlayer();
	if (ghAct == pDVar1->pDrlgAct)
	{
		bEclipse = (uint32_t) * (uint8_t*)(a1 + 9);
		pRoom = CUNIT_GetPlayerRoom();
		ENVIRONMENT_InitializeEnvironment(ghAct, pRoom, nIndex, nTicks, bEclipse);
		sub_6FB29390();
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 != nullptr)
		{
			uStack_9 = pDVar1->dwUnitId;
			uStack_b = (uint8_t)pDVar1->dwUnitType;
			uStack_c = 0x47;
			sub_6FB2C2B0((int)&uStack_c);
		}
	}
}

//D2Client.0x6FAB3C30
void __fastcall sub_6FAB3C30(uint32_t* a1)
{
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint16_t local_4;
	uint8_t local_2;

	local_10 = *a1;
	local_c = a1[1];
	local_8 = a1[2];
	local_4 = *(uint16_t*)(a1 + 3);
	local_2 = *(uint8_t*)((int)a1 + 0xe);
	sub_6FAB8E00((int)&local_10);
}

//D2Client.0x6FAB3C90
void __fastcall sub_6FAB3C90(uint32_t* a1)
{
	uint32_t local_8;
	uint16_t local_4;
	uint8_t local_2;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	local_2 = *(uint8_t*)((int)a1 + 6);
	sub_6FAFBCC0((int)&local_8);
}

//D2Client.0x6FAB3CC0
void __fastcall sub_6FAB3CC0(int a1)
{
	uint16_t uVar1;
	uint16_t uVar2;
	short sVar3;
	uint16_t uVar4;
	D2UnitStrc* pDVar5;
	uint8_t* puVar6;
	uint8_t local_4;

	uVar1 = *(uint16_t*)(a1 + 10);
	uVar2 = *(uint16_t*)(a1 + 8);
	sVar3 = *(short*)(a1 + 0xc);
	uVar4 = *(uint16_t*)(a1 + 6);
	if (*(char*)(a1 + 5) == '\x01')
	{
		pDVar5 = sub_6FB269F0(*(uint32_t*)(a1 + 1), 1);
		if (pDVar5 != nullptr)
		{
			sub_6FB44970((int*)pDVar5, uVar4);
			puVar6 = (uint8_t*)sub_6FB44950((int*)pDVar5);
			local_4 = (uint8_t)uVar1;
			*puVar6 = (char)uVar2;
			puVar6[1] = (char)((uint16_t)uVar2 >> 8);
			puVar6[2] = local_4;
			if (sVar3 != 0)
			{
				sub_6FB44A00((int*)pDVar5, 4, 1);
			}
			sub_6FB44A00((int*)pDVar5, 8, 1);
			sub_6FB45140((int*)pDVar5);
			return;
		}
	}
}

//D2Client.0x6FAB3D50
void __fastcall sub_6FAB3D50(uint32_t* a1)
{
	uint32_t local_8;
	uint16_t local_4;
	uint8_t local_2;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	local_2 = *(uint8_t*)((int)a1 + 6);
	sub_6FB257B0((int)&local_8);
}

//D2Client.0x6FAB3D80
void __fastcall sub_6FAB3D80(int a1)
{
	sub_6FB27570(*(uint32_t*)(a1 + 1), (uint32_t) * (uint8_t*)(a1 + 5), (uint32_t) * (uint16_t*)(a1 + 0x16), (uint32_t) * (uint16_t*)(a1 + 0x18), (char*)(a1 + 6));
}

//D2Client.0x6FAB3DA0
void __fastcall sub_6FAB3DA0(int a1)
{
	char* pcVar1;
	char cVar2;
	uint32_t uVar3;
	char* pcVar4;

	uVar3 = 0xffffffff;
	pcVar1 = (char*)(a1 + 0x22);
	pcVar4 = pcVar1;
	do
	{
		if (uVar3 == 0)
			break;
		uVar3 = uVar3 - 1;
		cVar2 = *pcVar4;
		pcVar4 = pcVar4 + 1;
	} while (cVar2 != '\0');
	sub_6FAAEC80(*(int*)(a1 + 3), (uint32_t) * (uint8_t*)(a1 + 7), (uint8_t*)(a1 + 8),
	    *(uint16_t*)(a1 + 0x18), *(uint16_t*)(a1 + 0x1a),
	    CONCAT22((short)((uint32_t)(pcVar1 + ~uVar3) >> 0x10), *(uint16_t*)(a1 + 0x1c)),
	    (uint32_t) * (uint16_t*)(a1 + 0x1e), *(uint16_t*)(a1 + 0x20), pcVar1,
	    pcVar1 + ~uVar3);
}

//D2Client.0x6FAB3DF0
void __fastcall sub_6FAB3DF0(int a1)
{
	sub_6FAAF260(*(int*)(a1 + 1));
}

//D2Client.0x6FAB3E00
void __fastcall sub_6FAB3E00(uint32_t* a1)
{
	uint32_t local_8;
	uint16_t local_4;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	sub_6FB06900(1, (int)&local_8);
}

//D2Client.0x6FAB3E40
void __fastcall sub_6FAB3E40(uint32_t* a1)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_1c[7];

	puVar2 = local_1c;
	for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = *a1;
		a1 = a1 + 1;
		puVar2 = puVar2 + 1;
	}
	*(uint16_t*)puVar2 = *(uint16_t*)a1;
	sub_6FAFC140((int)local_1c);
}

//D2Client.0x6FAB3E70
void __fastcall sub_6FAB3E70(int a1)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar1 != nullptr)
	{
		sub_6FB2FDA0(pDVar1);
		return;
	}
}

//D2Client.0x6FAB3E90
void __fastcall sub_6FAB3E90(int a1)
{
	int nPortalFlags;
	D2UnitStrc* pUnit;

	nPortalFlags = *(int*)(a1 + 1);
	pUnit = CUNIT_GetPlayer();
	D2_ASSERT(pUnit != nullptr);
	UNITS_SetPlayerPortalFlags(pUnit, nPortalFlags);
}

//D2Client.0x6FAB3ED0
void __fastcall sub_6FAB3ED0(uint32_t* a1)
{
	D2UnitStrc* pDVar1;
	uint32_t local_8;
	uint16_t local_4;
	uint8_t local_2;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	local_2 = *(uint8_t*)((int)a1 + 6);
	pDVar1 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar1 != nullptr);
	sub_6FB48480((int)&local_8);
}

//D2Client.0x6FAB3F20
void __fastcall sub_6FAB3F20(int a1)
{
	sub_6FAB8F50(a1);
	sub_6FB09C90();
}

//D2Client.0x6FAB3F30
void __fastcall sub_6FAB3F30(uint32_t* a1)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_18[6];

	puVar2 = local_18;
	for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = *a1;
		a1 = a1 + 1;
		puVar2 = puVar2 + 1;
	}
	*(uint8_t*)puVar2 = *(uint8_t*)a1;
	sub_6FB26320((int)local_18);
}

//D2Client.0x6FAB3F60
void __fastcall sub_6FAB3F60(int a1, uint32_t a2)
{
	sub_6FAAFB20(*(int*)(a1 + 1),
	    CONCAT22((short)((uint32_t)a2 >> 0x10), *(uint16_t*)(a1 + 5)));
}

//D2Client.0x6FAB3F70
// TODO: decompilation needs review (extraout)
uint32_t* __fastcall sub_6FAB3F70(int a1)
{
	uint16_t uVar1;
	uint16_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	uint32_t uVar7;
	uint64_t uVar8;
	uint64_t DVar9;
	D2UnitStrc* pDVar10;
	D2UnitStrc* pUnit;
	uint32_t* extraout_EAX;
	int iVar11;
	uint32_t uVar12;
	uint32_t* puVar13;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	uint32_t local_4c;
	uint32_t local_48;
	uint32_t local_44;
	int local_40;
	int local_3c;
	uint32_t local_2c;

	uVar3 = *(uint32_t*)(a1 + 7);
	uVar4 = *(uint32_t*)(a1 + 0xb);
	iVar5 = *(int*)(a1 + 0x13);
	iVar6 = *(int*)(a1 + 0xf);
	uVar1 = *(uint16_t*)(a1 + 5);
	uVar2 = *(uint16_t*)(a1 + 0x17);
	uVar12 = *(uint32_t*)(a1 + 0x1a);
	pDVar10 = CUNIT_GetPlayer();
	puVar13 = &local_5c;
	for (iVar11 = 0x17; iVar11 != 0; iVar11 = iVar11 + -1)
	{
		*puVar13 = 0;
		puVar13 = puVar13 + 1;
	}
	local_2c = (uint32_t) * (uint8_t*)(a1 + 0x1e);
	local_5c = 0x40000001;
	if ((iVar6 != 0) && (iVar5 != 0))
	{
		local_5c = 0x40000021;
		local_40 = iVar6;
		local_3c = iVar5;
	}
	local_58 = pDVar10;
	local_4c = (uint32_t)uVar1;
	local_48 = uVar3;
	local_44 = uVar4;
	pUnit = sub_6FB3E070(&local_5c);
	pDVar10 = pUnit;
	if (pUnit != nullptr)
	{
		UNITS_StoreOwnerTypeAndGUID(pUnit, (uint32_t) * (uint8_t*)(a1 + 0x19), uVar12);
		if (*(uint8_t*)(a1 + 0x1f) != 0)
		{
			STATLIST_SetUnitStat(pUnit, 0x148, (uint32_t) * (uint8_t*)(a1 + 0x1f), 0);
		}
		MISSILE_SetCurrentFrame(pUnit, (uint32_t)uVar2);
		uVar12 = pUnit->dwFrameCountPrecise >> 8;
		if ((int)uVar12 < 1)
		{
			pUnit->nSeqCurrentFramePrecise = 0;
			return extraout_EAX;
		}
		uVar7 = (pUnit->pSeed).nLowSeed;
		uVar8 = (uint64_t)(pUnit->pSeed).nHighSeed;
		if ((uVar12 & uVar12 - 1) != 0)
		{
			DVar9 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar8);
			(*(uint64_t*)&pUnit->pSeed) = DVar9;
			uVar8 = (uint64_t)DVar9 & 0xffffffff;
			pUnit->nSeqCurrentFramePrecise = (int)(uVar8 % (uint64_t)uVar12) << 8;
			return (uint32_t*)(uVar8 / uVar12);
		}
		DVar9 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar8);
		pDVar10 = (D2UnitStrc*)(*(uint32_t*)((uint8_t*)&DVar9 + 0));
		(*(uint64_t*)&pUnit->pSeed) = DVar9;
		pUnit->nSeqCurrentFramePrecise = (uVar12 - 1 & (uint32_t)pDVar10) << 8;
	}
	return &pDVar10->dwUnitType;
}

//D2Client.0x6FAB40C0
void __fastcall sub_6FAB40C0(uint32_t* a1)
{
	uint32_t local_c;
	uint32_t local_8;
	uint16_t local_4;

	local_c = *a1;
	local_8 = a1[1];
	local_4 = *(uint16_t*)(a1 + 2);
	sub_6FB4B3C0((int)&local_c);
}

//D2Client.0x6FAB40F0
void __fastcall sub_6FAB40F0(int a1, uint32_t a2)
{
	sub_6FAAF070(*(int*)(a1 + 1), *(uint16_t*)(a1 + 5), *(uint16_t*)(a1 + 7),
	    CONCAT22((short)((uint32_t)a2 >> 0x10), *(uint16_t*)(a1 + 9)),
	    (uint32_t) * (uint16_t*)(a1 + 0xb));
}

//D2Client.0x6FAB4120
void __fastcall sub_6FAB4120(uint32_t* a1)
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_18[6];

	puVar2 = local_18;
	for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = *a1;
		a1 = a1 + 1;
		puVar2 = puVar2 + 1;
	}
	*(uint8_t*)puVar2 = *(uint8_t*)a1;
	sub_6FB1FE70((int)local_18);
}

//D2Client.0x6FAB4150
void __fastcall sub_6FAB4150(int a1)
{
	sub_6FB1FF20(*(uint32_t*)(a1 + 2), *(char*)(a1 + 1));
}

//D2Client.0x6FAB4160
void __fastcall sub_6FAB4160(int a1)
{
	if (*(char*)(a1 + 1) != '\0')
	{
		sub_6FAB14F0(*(int*)(a1 + 9), *(int*)(a1 + 5), (uint32_t) * (uint8_t*)(a1 + 2),
		    (uint32_t) * (uint16_t*)(a1 + 3));
		return;
	}
	sub_6FAB17A0(*(int*)(a1 + 9));
}

//D2Client.0x6FAB4190
void __fastcall sub_6FAB4190(int a1)
{
	int local_c;
	uint32_t local_8;
	uint32_t local_4;

	local_c = *(int*)(a1 + 0xc);
	local_8 = *(uint32_t*)(a1 + 0x10);
	local_4 = 0;
	sub_6FAB15D0(*(uint32_t*)(a1 + 8), *(int*)(a1 + 4), (uint32_t) * (uint8_t*)(a1 + 1),
	    (uint32_t) * (uint16_t*)(a1 + 2), &local_c);
}

//D2Client.0x6FAB41D0
void __fastcall sub_6FAB41D0(int a1)
{
	uint32_t uVar1;

	uVar1 = *(uint16_t*)(a1 + 2) & 0xfff;
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) < (int)uVar1)
	{
		uVar1 = 0xffffffff;
	}
	sub_6FB1A200((uint32_t) * (uint8_t*)(a1 + 1), uVar1, (uint32_t)((*(uint16_t*)(a1 + 2) & 0x8000) != 0),
	    *(uint32_t*)(a1 + 4));
}

//D2Client.0x6FAB4220
void __fastcall sub_6FAB4220(uint32_t* a1)
{
	uint32_t local_8;
	uint16_t local_4;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	sub_6FB2FA80((int)&local_8);
}

//D2Client.0x6FAB4240
void __fastcall sub_6FAB4240(uint32_t* a1)
{
	uint32_t local_14;
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint16_t local_4;

	local_14 = *a1;
	local_10 = a1[1];
	local_c = a1[2];
	local_8 = a1[3];
	local_4 = *(uint16_t*)(a1 + 4);
	sub_6FB2FBC0((int)&local_14);
}

//D2Client.0x6FAB4280
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAB4280()
{
	uint8_t bVar1;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int nLevelId;
	uint32_t extraout_ECX;

	pUnit = CUNIT_GetPlayer();
	pRoom = UNITS_GetRoom(pUnit);
	nLevelId = DUNGEON_GetLevelIdFromRoom(pRoom);
	bVar1 = DRLG_GetActNoFromLevelId(nLevelId);
	sub_6FB5C9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), bVar1));
}

//D2Client.0x6FAB42A0
// TODO: decompilation needs review (unaff_)
void __fastcall sub_6FAB42A0(int a1)
{
	uint32_t unaff_ESI;
	uint32_t uVar1;

	uVar1 = CONCAT22((short)((uint32_t)unaff_ESI >> 0x10), *(uint16_t*)(a1 + 8));
	if (*(char*)(a1 + 1) != '\0')
	{
		sub_6FAB0880(*(uint32_t*)(a1 + 4), (uint32_t) * (uint16_t*)(a1 + 2), uVar1);
		return;
	}
	sub_6FAB1A40(*(uint32_t*)(a1 + 4), (uint32_t) * (uint16_t*)(a1 + 2), uVar1);
}

//D2Client.0x6FAB42D0
void __fastcall sub_6FAB42D0(int a1)
{
	sub_6FAB0A90(*(int*)(a1 + 1), *(uint32_t*)(a1 + 5), *(uint32_t*)(a1 + 9));
}

//D2Client.0x6FAB42E0
void __fastcall sub_6FAB42E0(int a1)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;

	uVar1 = *(uint32_t*)(a1 + 0x15);
	iVar2 = *(int*)(a1 + 1);
	uVar3 = *(uint32_t*)(a1 + 0x19);
	pDVar4 = sub_6FB269F0(uVar1, 2);
	if (pDVar4 != nullptr)
	{
		sub_6FB48560((int)pDVar4, (char*)(a1 + 5));
	}
	if (uVar3 != 0xffffffff)
	{
		pDVar4 = sub_6FB269F0(uVar3, 2);
		if (pDVar4 != nullptr)
		{
			sub_6FB48560((int)pDVar4, (char*)(a1 + 5));
		}
		sub_6FAB0CB0(iVar2, uVar1, uVar3);
	}
}

//D2Client.0x6FAB4350
void __fastcall sub_6FAB4350(uint32_t* a1)
{
	uint32_t local_8;
	uint16_t local_4;

	local_8 = *a1;
	local_4 = *(uint16_t*)(a1 + 1);
	sub_6FAFBE70((int)&local_8);
}

//D2Client.0x6FAB4370
void __fastcall sub_6FAB4370(int a1, uint32_t a2)
{
	sub_6FAB0FB0(*(int*)(a1 + 1),
	    CONCAT31((int32_t)((uint32_t)a2 >> 8), *(uint8_t*)(a1 + 5)));
}

//D2Client.0x6FAB4380
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAB4380(int a1)
{
	uint32_t in_EAX;

	sub_6FAB1000(*(int*)(a1 + 1), *(int*)(a1 + 5),
	    CONCAT22((short)((uint32_t)in_EAX >> 0x10), *(uint16_t*)(a1 + 9)));
}

//D2Client.0x6FAB43A0
void __fastcall sub_6FAB43A0(int a1)
{
	sub_6FAB0DC0(*(int*)(a1 + 1), *(uint16_t*)(a1 + 5));
}

//D2Client.0x6FAB43B0
void __fastcall sub_6FAB43B0(int a1)
{
	if (*(char*)(a1 + 1) != '\0')
	{
		sub_6FAB1080(*(int*)(a1 + 2), *(int*)(a1 + 6));
		return;
	}
	sub_6FAB1180(*(int*)(a1 + 2), *(int*)(a1 + 6));
}

//D2Client.0x6FAB43D0
void __fastcall sub_6FAB43D0(int a1)
{
	sub_6FAFC190(*(short*)(a1 + 1), (uint32_t) * (uint16_t*)(a1 + 3));
}

//D2Client.0x6FAB43E0
void __fastcall sub_6FAB43E0(char* a1)
{
	D2_ASSERT(*a1 == -0x69);
	sub_6FAED280();
}

//D2Client.0x6FAB4420
void __fastcall sub_6FAB4420(uint32_t* a1)
{
	int iVar1;
	uint32_t* puVar2;
	uint8_t local_fc[252];

	puVar2 = (uint32_t*)local_fc;
	for (iVar1 = 0x3f; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = *a1;
		a1 = a1 + 1;
		puVar2 = puVar2 + 1;
	}
	switch ((*(uint32_t*)((uint8_t*)&local_fc + 1)) & 0xff)
	{
	case 0:
		sub_6FB2AD50((int)local_fc);
		return;
	case 1:
		sub_6FB2AF40((int)local_fc);
		return;
	case 2:
		sub_6FB2B030((int)local_fc);
		return;
	case 3:
		sub_6FB2B190((int)local_fc);
		return;
	case 4:
		sub_6FB2BAF0((int)local_fc);
		return;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 0x11:
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
		FOG_DisplayWarning("These should be scmd_itemunitex messages!",
		    __FILE__, __LINE__);
		return;
	case 10:
		sub_6FB2D650((int)local_fc);
		return;
	case 0xb:
	case 0xc:
		sub_6FB2D760((int)local_fc);
		break;
	case 0xd:
		sub_6FB2DAC0((int)local_fc);
		return;
	case 0xe:
		sub_6FB2DF10((int)local_fc);
		return;
	case 0xf:
		sub_6FB2E100((int)local_fc);
		return;
	case 0x10:
		sub_6FB2E2E0((int)local_fc);
		return;
	case 0x12:
		sub_6FB2EE00((int)local_fc);
		return;
	}
}

//D2Client.0x6FAB4590
void __fastcall sub_6FAB4590(uint32_t* a1)
{
	int iVar1;
	uint32_t* puVar2;
	uint8_t local_104[260];

	puVar2 = (uint32_t*)local_104;
	for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = *a1;
		a1 = a1 + 1;
		puVar2 = puVar2 + 1;
	}
	*(uint8_t*)puVar2 = *(uint8_t*)a1;
	switch ((*(uint32_t*)((uint8_t*)&local_104 + 1)) & 0xff)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 10:
	case 0xb:
	case 0xc:
	case 0xd:
	case 0xe:
	case 0xf:
	case 0x10:
	case 0x12:
		FOG_DisplayWarning("These should be scmd_itemex messages!",
		    __FILE__, __LINE__);
		return;
	case 5:
		sub_6FB2BEF0((int)local_104);
		return;
	case 6:
		sub_6FB2C300((uint32_t*)local_104);
		return;
	case 7:
		sub_6FB2C660((int)local_104);
		return;
	case 8:
		sub_6FB2CB10((int)local_104);
		return;
	case 9:
		sub_6FB2CDF0((int)local_104);
		return;
	case 0x11:
		sub_6FB2EA00((int)local_104);
		return;
	case 0x13:
		sub_6FB2EEC0((int)local_104);
		return;
	case 0x14:
		sub_6FB2F050((int)local_104);
		return;
	case 0x15:
		sub_6FB2F300((int)local_104);
		return;
	case 0x16:
		sub_6FB2FD00((int)local_104);
		break;
	case 0x17:
		sub_6FB2D300((uint32_t*)local_104);
		return;
	}
}

//D2Client.0x6FAB46E0
void __fastcall sub_6FAB46E0(int a1)
{
	if (*(char*)(a1 + 1) == '\0')
	{
		DATATBLS_AddOrChangeRunesTxtRecord((uint32_t) * (uint16_t*)(a1 + 4), (D2RunesTxt*)(a1 + 6));
	}
}

//D2Client.0x6FAB4700
void __fastcall sub_6FAB4700(int a1)
{
	uint8_t bVar1;
	D2UnitStrc* pDVar2;

	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar2 == nullptr)
	{
		FOG_Trace("WARNING: sSCmd_UnitStateOnEx, Attempt to change state on a unit the client doesn't have!  Type: %d, Id: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
		    *(uint32_t*)(a1 + 2));
		return;
	}
	bVar1 = *(uint8_t*)(a1 + 6);
	sub_6FB4D3A0(pDVar2, (uint32_t)bVar1);
	sub_6FB4D920(pDVar2, (uint32_t)bVar1);
}

//D2Client.0x6FAB4750
void __fastcall sub_6FAB4750(int a1)
{
	int iVar1;
	uint8_t bVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	D2StatListStrc* pDVar8;
	D2BitBufferStrc local_14;

	pDVar3 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar3 == nullptr)
	{
		FOG_Trace("WARNING: sSCmd_UnitStateOnValEx, Attempt to change state on a unit the client doesn't have!  Type: %d, Id: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
		    *(uint32_t*)(a1 + 2));
		return;
	}
	uVar6 = (uint32_t) * (uint8_t*)(a1 + 7);
	sub_6FB4D3A0(pDVar3, uVar6);
	BITMANIP_Initialize(&local_14, (uint8_t*)(a1 + 8), *(uint8_t*)(a1 + 6) - 8);
	pDVar8 = nullptr;
	uVar4 = BITMANIP_Read(&local_14, 9);
	while (true)
	{
		if (0x1fe < (int)uVar4)
		{
			sub_6FB4D920(pDVar3, uVar6);
			return;
		}
		if ((((int)uVar4 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4) <= (int)uVar4)) ||
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) + uVar4 * 0x144, iVar1 == 0))
			break;
		if (*(char*)(iVar1 + 8) == '\0')
		{
			FOG_Trace("WARNING: sSCmd_UnitStateOnValEx, Attempt to set an invalid stat!  Type: %d, Id: %d, Stat: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
			    *(uint32_t*)(a1 + 2), uVar4);
			return;
		}
		iVar7 = 0;
		if (*(uint8_t*)(iVar1 + 9) != 0)
		{
			iVar7 = BITMANIP_ReadSigned(&local_14, (uint32_t) * (uint8_t*)(iVar1 + 9));
		}
		bVar2 = *(uint8_t*)(iVar1 + 8);
		if ((bVar2 < 0x20) && (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar1 + 4)) != 0))
		{
			uVar5 = BITMANIP_ReadSigned(&local_14, (uint32_t)bVar2);
		}
		else
		{
			uVar5 = BITMANIP_Read(&local_14, (uint32_t)bVar2);
		}
		pDVar8 = sub_6FB4D830(pDVar3, pDVar8, uVar6, uVar4, uVar5, iVar7);
		uVar4 = BITMANIP_Read(&local_14, 9);
	}
	FOG_Trace("WARNING: sSCmd_UnitStateOnValEx, Attempt to set an invalid stat!  Type: %d, Id: %d, Stat: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
	    *(uint32_t*)(a1 + 2), uVar4);
}

//D2Client.0x6FAB4900
void __fastcall sub_6FAB4900(int a1)
{
	uint8_t bVar1;
	D2UnitStrc* pDVar2;

	pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar2 == nullptr)
	{
		FOG_Trace("WARNING: sSCmd_UnitStateOffEx, Attempt to change state on a unit the client doesn't have!  Type: %d, Id: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
		    *(uint32_t*)(a1 + 2));
		return;
	}
	bVar1 = *(uint8_t*)(a1 + 6);
	sub_6FB4DA00(pDVar2, (uint32_t)bVar1);
	sub_6FB4D640(pDVar2, (uint32_t)bVar1);
}

//D2Client.0x6FAB4950
void __fastcall sub_6FAB4950(int a1)
{
	int iVar1;
	uint8_t bVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	D2StatListStrc* pDVar8;
	D2BitBufferStrc local_14;

	pDVar3 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar3 == nullptr)
	{
		FOG_Trace("WARNING: sSCmd_UnitStateAllEx, Attempt to change state on a unit the client doesn't have!  Type: %d, Id: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
		    *(uint32_t*)(a1 + 2));
		return;
	}
	BITMANIP_Initialize(&local_14, (uint8_t*)(a1 + 7), *(uint8_t*)(a1 + 6) - 7);
	uVar4 = BITMANIP_Read(&local_14, 8);
	do
	{
		if (0xfe < (int)uVar4)
		{
			return;
		}
		sub_6FB4D3A0(pDVar3, uVar4);
		uVar5 = BITMANIP_Read(&local_14, 1);
		if (uVar5 != 0)
		{
			pDVar8 = nullptr;
			uVar5 = BITMANIP_Read(&local_14, 9);
			while ((int)uVar5 < 0x1ff)
			{
				if ((((int)uVar5 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4) <= (int)uVar5)) ||
				    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) + uVar5 * 0x144, iVar1 == 0))
				{
					FOG_Trace("WARNING: sSCmd_UnitStateAllEx, Attempt to set an invalid stat!  Type: %d, Id: %d, Stat: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
					    *(uint32_t*)(a1 + 2), uVar5);
					return;
				}
				if (*(char*)(iVar1 + 8) == '\0')
				{
					FOG_Trace("WARNING: sSCmd_UnitStateOnValEx, Attempt to set an invalid stat!  Type: %d, Id: %d, Stat: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
					    *(uint32_t*)(a1 + 2), uVar5);
					return;
				}
				iVar7 = 0;
				if (*(uint8_t*)(iVar1 + 9) != 0)
				{
					iVar7 = BITMANIP_ReadSigned(&local_14, (uint32_t) * (uint8_t*)(iVar1 + 9));
				}
				bVar2 = *(uint8_t*)(iVar1 + 8);
				if ((bVar2 < 0x20) && (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar1 + 4)) != 0))
				{
					uVar6 = BITMANIP_ReadSigned(&local_14, (uint32_t)bVar2);
				}
				else
				{
					uVar6 = BITMANIP_Read(&local_14, (uint32_t)bVar2);
				}
				pDVar8 = sub_6FB4D830(pDVar3, pDVar8, uVar4, uVar5, uVar6, iVar7);
				uVar5 = BITMANIP_Read(&local_14, 9);
			}
		}
		sub_6FB4D920(pDVar3, uVar4);
		uVar4 = BITMANIP_Read(&local_14, 8);
	} while (true);
}

//D2Client.0x6FAB4B40
void __fastcall sub_6FAB4B40(int a1)
{
	D2UnitStrc* pUnit;
	D2UnitStrc* pDVar1;

	pUnit = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pUnit == nullptr)
	{
		FOG_Trace("WARNING: sSCmd_HealthUpdate, Attempt to update health on a unit the client doesn't have!  Type: %d, Id: %d\n", (uint32_t) * (uint8_t*)(a1 + 1),
		    *(uint32_t*)(a1 + 2));
	}
	else
	{
		pDVar1 = CUNIT_GetPlayer();
		if ((pUnit != pDVar1) && ((pUnit->dwFlags >> 9 & 1) == 0))
		{
			if (pUnit->dwUnitType == 1)
			{
				STATLIST_SetUnitStat(pUnit, 6, (uint32_t) * (uint8_t*)(a1 + 6) << 8, 0);
				return;
			}
			sub_6FAB1420(*(int*)(a1 + 2), (int)((uint32_t) * (uint8_t*)(a1 + 6) * 100) >> 7);
			return;
		}
	}
}

//D2Client.0x6FAB4BD0
void __fastcall sub_6FAB4BD0(int a1)
{
	uint8_t bVar1;
	uint16_t uVar2;
	uint16_t uVar3;
	short sVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	D2UnitStrc* pHireling;
	D2UnitStrc* pDVar12;
	int iVar13;
	uint32_t uVar14;
	uint32_t* puVar15;
	int iVar16;
	int* piVar17;
	D2StatListStrc* pStatList;
	uint32_t uStack_74;
	int iStack_70;
	uint32_t* puStack_6c;
	uint8_t* puStack_68;
	uint32_t local_60;
	uint32_t local_5c;
	uint32_t uStack_4c;
	uint32_t uStack_48;
	uint8_t uStack_44;
	uint8_t auStack_40[16];
	D2BitBufferStrc local_30;
	int aiStack_1c[4];
	uint32_t uStack_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	iVar13 = *(int*)(a1 + 1);
	uVar2 = *(uint16_t*)(a1 + 7);
	uVar3 = *(uint16_t*)(a1 + 9);
	sVar4 = *(short*)(a1 + 5);
	local_5c = (uint32_t)uVar2;
	local_60 = (uint32_t)uVar3;
	BITMANIP_Initialize(&local_30, (uint8_t*)(a1 + 0xd), *(uint8_t*)(a1 + 0xc) - 0xd);
	uVar5 = BITMANIP_Read(&local_30, 4);
	uVar14 = 0;
	puStack_68 = nullptr;
	uVar6 = BITMANIP_Read(&local_30, 1);
	if (uVar6 != 0)
	{
		iVar7 = (int)sVar4;
		if (iVar7 < 0)
		{
			return;
		}
		iVar16 = *(int*)((uint8_t*)&sgptDataTables);
		if (*(int*)(iVar16 + 0xa80) <= iVar7)
		{
			return;
		}
		iVar7 = (int)*(short*)(*(int*)(iVar16 + 0xa78) + 0x18 + iVar7 * 0x1a8);
		if (iVar7 < 0)
		{
			return;
		}
		if (*(int*)(iVar16 + 0xa98) <= iVar7)
		{
			return;
		}
		iVar7 = *(int*)(iVar16 + 0xa90) + iVar7 * 0x134;
		if (iVar7 == 0)
		{
			return;
		}
		puStack_68 = auStack_40;
		iVar16 = 0;
		do
		{
			bVar1 = *(uint8_t*)(iVar7 + 0x15 + iVar16);
			if (bVar1 < 3)
			{
				iVar8 = 1;
			}
			else
			{
				uVar6 = bVar1 - 1;
				if (uVar6 == 0)
				{
					iVar8 = 0;
				}
				else
				{
					iVar8 = 0x1f;
					if (uVar6 != 0)
					{
						for (; uVar6 >> iVar8 == 0; iVar8 = iVar8 + -1)
						{
						}
					}
					iVar8 = iVar8 + 1;
				}
			}
			uVar6 = BITMANIP_Read(&local_30, iVar8);
			auStack_40[iVar16] = (char)uVar6;
			iVar16 = iVar16 + 1;
		} while (iVar16 < 0x10);
	}
	puStack_6c = nullptr;
	puVar15 = nullptr;
	uStack_74 = 0xffffffff;
	iStack_70 = 0;
	uVar6 = BITMANIP_Read(&local_30, 1);
	if (uVar6 != 0)
	{
		uVar6 = BITMANIP_Read(&local_30, 1);
		uVar14 = BITMANIP_Read(&local_30, 1);
		uVar9 = BITMANIP_Read(&local_30, 1);
		uVar9 = -(uint32_t)(uVar9 != 0) & 2;
		uVar10 = BITMANIP_Read(&local_30, 1);
		uVar11 = BITMANIP_Read(&local_30, 1);
		uVar14 = -(uint32_t)(uVar6 != 0) & 4 | -(uint32_t)(uVar14 != 0) & 8 | uVar9 |
		         -(uint32_t)(uVar10 != 0) & 0x10 | -(uint32_t)(uVar11 != 0) & 0x40;
		if (uVar9 != 0)
		{
			iStack_70 = BITMANIP_ReadSigned(&local_30, 0x10);
		}
		uStack_4c = 0;
		puStack_6c = &uStack_4c;
		uStack_48 = 0;
		uStack_44 = 0;
		uVar6 = BITMANIP_Read(&local_30, 8);
		if ((char)uVar6 != '\0')
		{
			puVar15 = &uStack_4c;
			do
			{
				*(char*)puVar15 = (char)uVar6;
				puVar15 = (uint32_t*)((int)puVar15 + 1);
				uVar6 = BITMANIP_Read(&local_30, 8);
			} while ((char)uVar6 != '\0');
		}
		uVar6 = BITMANIP_Read(&local_30, 0x10);
		puVar15 = (uint32_t*)CONCAT22((short)((uint32_t)puVar15 >> 0x10), (uint16_t)(uint8_t)uVar6);
		uVar6 = BITMANIP_Read(&local_30, 1);
		if (uVar6 != 0)
		{
			uStack_74 = BITMANIP_Read(&local_30, 0x20);
		}
	}
	piVar17 = aiStack_1c;
	for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*piVar17 = 0;
		piVar17 = piVar17 + 1;
	}
	aiStack_1c[1] = (int)sVar4;
	aiStack_1c[3] = (int)uVar3;
	aiStack_1c[2] = (int)uVar2;
	uStack_4 = uVar5 & 0xff;
	uStack_8 = uStack_74;
	aiStack_1c[0] = iVar13;
	uStack_c = uVar14;
	sub_6FAAE030(aiStack_1c[1]);
	pHireling = sub_6FB27630(aiStack_1c, (uint32_t*)(puStack_68), (int)puStack_6c, (uint32_t)(puVar15), iStack_70, 0);
	if (pHireling == nullptr)
	{
		return;
	}
	sub_6FB5DAB0(pHireling);
	iVar7 = MONSTERS_GetHirelingTypeId(pHireling);
	if (iVar7 != 0)
	{
		iVar7 = 1;
		pDVar12 = CUNIT_GetPlayer();
		iVar7 = sub_6FAB1920((int)pDVar12, 7, iVar7);
		if (iVar13 == iVar7)
			goto LAB_6fab4eca;
	}
	STATLIST_SetUnitStat(pHireling, 7, 0x8000, 0);
	STATLIST_SetUnitStat(pHireling, 6, (uint32_t) * (uint8_t*)(a1 + 0xb) << 8, 0);
LAB_6fab4eca:
	iVar13 = MONSTERS_GetHirelingTypeId(pHireling);
	if ((iVar13 != 0) && ((char)uVar5 == '\x01'))
	{
		pHireling->dwFlagEx = pHireling->dwFlagEx & 0xfffbffff;
	}
	STATLIST_SetUnitStat(pHireling, 0x148, local_60 + local_5c & 0xffff, 0);
	uVar5 = BITMANIP_Read(&local_30, 1);
	if (uVar5 != 0)
	{
		uVar5 = BITMANIP_Read(&local_30, 0x1f);
		UNITS_StoreOwnerTypeAndGUID(pHireling, 0, uVar5);
	}
	uVar5 = BITMANIP_Read(&local_30, 1);
	if (uVar5 != 0)
	{
		pStatList = nullptr;
		uVar5 = BITMANIP_Read(&local_30, 9);
		if ((int)uVar5 < 0x1ff)
		{
			while (((-1 < (int)uVar5 && ((int)uVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4))) &&
			        (iVar13 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) + uVar5 * 0x144, iVar13 != 0)))
			{
				if (*(char*)(iVar13 + 8) == '\0')
				{
					sVar4 = *(short*)(a1 + 5);
					goto LAB_6fab5070;
				}
				(*(uint16_t*)((uint8_t*)&local_5c + 0)) = 0;
				if (*(uint8_t*)(iVar13 + 9) != 0)
				{
					iVar7 = BITMANIP_ReadSigned(&local_30, (uint32_t) * (uint8_t*)(iVar13 + 9));
					(*(uint16_t*)((uint8_t*)&local_5c + 0)) = (uint16_t)iVar7;
				}
				bVar1 = *(uint8_t*)(iVar13 + 8);
				if ((bVar1 < 0x20) && (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar13 + 4)) != 0))
				{
					uVar6 = BITMANIP_ReadSigned(&local_30, (uint32_t)bVar1);
				}
				else
				{
					uVar6 = BITMANIP_Read(&local_30, (uint32_t)bVar1);
				}
				if ((pStatList == nullptr) &&
				    (pStatList = STATLIST_GetStatListFromUnitStateAndFlag(pHireling, 0, 0x40),
				        pStatList == nullptr))
				{
					pStatList = STATLIST_AllocStatList(nullptr, 0x40, 0, pHireling->dwUnitType, pHireling->dwUnitId);
					STATLIST_SetState(pStatList, 0);
					D2COMMON_10475_PostStatToStatList(pHireling, pStatList, 1);
					if (pStatList != nullptr)
						goto LAB_6fab502b;
				}
				else
				{
				LAB_6fab502b:
					STATLIST_SetStatIfListIsValid(pStatList, uVar5, uVar6, (uint16_t)local_5c);
				}
				uVar5 = BITMANIP_Read(&local_30, 9);
				if (0x1fe < (int)uVar5)
				{
					return;
				}
			}
			sVar4 = *(short*)(a1 + 5);
		LAB_6fab5070:
			FOG_Trace("WARNING: sSCmd_NewMonsterEx, Attempt to set an invalid stat!  Class: %d, Stat: %d\n", (int)sVar4, uVar5);
		}
	}
}

//D2Client.0x6FAB5090
void __fastcall sub_6FAB5090(int a1)
{
	dword_6FBBC244 = *(uint32_t*)(a1 + 1);
	dword_6FBBC248 = *(uint32_t*)(a1 + 5);
}

//D2Client.0x6FAB50B0
void __fastcall sub_6FAB50B0(D2PacketBufferStrc* pPacketBuffer, int a2)
{
	uint8_t bVar1;
	uint32_t uVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int* piVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	D2PacketBufferStrc* pDVar9;
	uint8_t** ppuVar10;
	uint8_t* pbVar11;
	int local_48;
	uint32_t uStack_44;
	uint8_t** ppuStack_40;
	D2BitBufferStrc DStack_3c;
	D2BitBufferStrc DStack_28;
	D2BitBufferStrc DStack_14;

	if (a2 != -1)
	{
		GetTickCount();
		if (500 < a2)
		{
			byte_6FBC1B00 = byte_6FBC1B00 + 1;
		}
		local_48 = a2;
		if (0 < a2)
		{
			do
			{
				bVar1 = pPacketBuffer->data[0];
				iVar3 = SERVER_GetServerPacketSize(pPacketBuffer, a2, (int*)&uStack_44);
				uVar6 = uStack_44;
				if (iVar3 == 0)
				{
					return;
				}
				D2_ASSERT(0xad >= bVar1);
				uVar2 = (uint32_t)bVar1;
				uVar7 = (&dword_6FB76274)[uVar2 * 3];
				ppuVar10 = &ptr_6FB76270 + uVar2 * 3;
				ppuStack_40 = ppuVar10;
				if (uVar7 == 0xffffffff)
				{
				LAB_6fab515d:
					if (dword_6FB76278[uVar2 * 3] != 0)
					{
						if ((bVar1 < 0x67) || (0x6d < bVar1))
						{
							uVar7 = *(uint32_t*)(pPacketBuffer->data + 2);
							uVar8 = (uint32_t)pPacketBuffer->data[1];
						}
						else
						{
							uVar7 = *(uint32_t*)(pPacketBuffer->data + 1);
							uVar8 = 1;
						}
						pDVar4 = sub_6FB269F0(uVar7, uVar8);
						if (pDVar4 != nullptr)
						{
							piVar5 = (int*)sub_6FB29450((int)pDVar4);
							if ((piVar5 == nullptr) || (piVar5[1] + 1 == *piVar5))
							{
								piVar5 = sub_6FAB54C0((int)pDVar4);
							}
							D2_ASSERT(dword_6FBAB9B0 >= (int)(uVar6 & 0xffff));
							pDVar9 = pPacketBuffer;
							pbVar11 = (uint8_t*)(piVar5[1] * dword_6FBAB9B0 + piVar5[3]);
							for (uVar7 = (uVar6 & 0xffff) >> 2; uVar7 != 0; uVar7 = uVar7 - 1)
							{
								*(uint32_t*)pbVar11 = *(uint32_t*)pDVar9->data;
								pDVar9 = (D2PacketBufferStrc*)(pDVar9->data + 4);
								pbVar11 = pbVar11 + 4;
							}
							for (uVar7 = uVar6 & 3; uVar7 != 0; uVar7 = uVar7 - 1)
							{
								*pbVar11 = pDVar9->data[0];
								pDVar9 = (D2PacketBufferStrc*)(pDVar9->data + 1);
								pbVar11 = pbVar11 + 1;
							}
							piVar5[1] = piVar5[1] + 1;
							ppuVar10 = ppuStack_40;
						}
					}
					switch (uVar2)
					{
					case 0xd:
						if (pPacketBuffer->data[1] == 1)
						{
							sub_6FB269F0(*(uint32_t*)(pPacketBuffer->data + 2), 1);
						}
						break;
					case 0x18:
						BITMANIP_Initialize(&DStack_3c, pPacketBuffer->data, 0xf);
						BITMANIP_Read(&DStack_3c, 8);
						BITMANIP_Read(&DStack_3c, 0xf);
						BITMANIP_Read(&DStack_3c, 0xf);
						BITMANIP_Read(&DStack_3c, 0xf);
						BITMANIP_Read(&DStack_3c, 7);
						BITMANIP_Read(&DStack_3c, 7);
						BITMANIP_Read(&DStack_3c, 0x10);
						BITMANIP_Read(&DStack_3c, 0x10);
						BITMANIP_Read(&DStack_3c, 8);
						BITMANIP_Read(&DStack_3c, 8);
						break;
					case 0x95:
						BITMANIP_Initialize(&DStack_28, pPacketBuffer->data, 0xd);
						BITMANIP_Read(&DStack_28, 8);
						BITMANIP_Read(&DStack_28, 0xf);
						BITMANIP_Read(&DStack_28, 0xf);
						BITMANIP_Read(&DStack_28, 0xf);
						BITMANIP_Read(&DStack_28, 0x10);
						BITMANIP_Read(&DStack_28, 0x10);
						BITMANIP_Read(&DStack_28, 8);
						BITMANIP_Read(&DStack_28, 8);
						break;
					case 0x96:
						BITMANIP_Initialize(&DStack_14, pPacketBuffer->data, 9);
						BITMANIP_Read(&DStack_14, 8);
						BITMANIP_Read(&DStack_14, 0xf);
						BITMANIP_Read(&DStack_14, 0x10);
						BITMANIP_Read(&DStack_14, 0x10);
						BITMANIP_Read(&DStack_14, 8);
						BITMANIP_Read(&DStack_14, 8);
					}
					if ((code*)*ppuVar10 != nullptr)
					{
						(*(code*)*ppuVar10)();
					}
				}
				else
				{
					D2_ASSERT((uStack_44 & 0xffff) == uVar7);
					if ((uVar7 == 0xffffffff) || ((uStack_44 & 0xffff) == uVar7))
						goto LAB_6fab515d;
				}
				uVar6 = uVar6 & 0xffff;
				local_48 = local_48 - uVar6;
				dword_6FBC1AF0 = dword_6FBC1AF0 + uVar6;
				pPacketBuffer = (D2PacketBufferStrc*)(pPacketBuffer->data + uVar6);
				byte_6FBAB9B4 = bVar1;
			} while (0 < local_48);
		}
		byte_6FBC1AF8 = byte_6FBC1AF8 + 1;
	}
}

//D2Client.0x6FAB54C0
int* __fastcall sub_6FAB54C0(int a1)
{
	int* piVar1;
	uint32_t* puVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t* puVar7;

	if (dword_6FBAB9B0 == 0)
	{
		piVar1 = (int*)(&dword_6FB76274);
		iVar5 = 0;
		do
		{
			if ((piVar1[1] != 0) && (iVar5 < *piVar1))
			{
				iVar5 = *piVar1;
			}
			piVar1 = piVar1 + 3;
		} while ((int)piVar1 < (int)__FILE__);
		dword_6FBAB9B0 = iVar5 + 5;
	}
	piVar1 = (int*)sub_6FB29450(a1);
	if (piVar1 == nullptr)
	{
		piVar1 = (int*)D2_ALLOC(0x10);
		*piVar1 = 0;
		piVar1[1] = 0;
		piVar1[2] = 0;
		piVar1[3] = 0;
		sub_6FB29480(a1, (uint32_t)(piVar1));
	}
	iVar5 = *piVar1 + 5;
	puVar2 = (uint32_t*)
	    D2_ALLOC(dword_6FBAB9B0 * iVar5);
	uVar3 = dword_6FBAB9B0 * iVar5;
	puVar6 = puVar2;
	for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*(uint8_t*)puVar6 = 0;
		puVar6 = (uint32_t*)((int)puVar6 + 1);
	}
	if ((uint32_t*)piVar1[3] != nullptr)
	{
		uVar3 = *piVar1 * dword_6FBAB9B0;
		puVar6 = (uint32_t*)piVar1[3];
		puVar7 = puVar2;
		for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1)
		{
			*puVar7 = *puVar6;
			puVar6 = puVar6 + 1;
			puVar7 = puVar7 + 1;
		}
		for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1)
		{
			*(uint8_t*)puVar7 = *(uint8_t*)puVar6;
			puVar6 = (uint32_t*)((int)puVar6 + 1);
			puVar7 = (uint32_t*)((int)puVar7 + 1);
		}
		D2_FREE((void*)piVar1[3]);
	}
	*piVar1 = iVar5;
	piVar1[3] = (int)puVar2;
	return piVar1;
}

//D2Client.0x6FAB55C0
void __fastcall sub_6FAB55C0(int a1)
{
	void* pFree;

	pFree = (void*)sub_6FB29450(a1);
	if (pFree != nullptr)
	{
		D2_FREE(*(void**)((int)pFree + 0xc));
		D2_FREE(pFree);
		sub_6FB29480(a1, 0);
		return;
	}
}

//D2Client.0x6FAB5610
void __fastcall sub_6FAB5610(int a1)
{
	uint8_t bVar1;
	int* piVar2;
	int iVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	D2PacketBufferStrc* pBuffer;
	int iVar6;
	uint32_t* puVar7;
	uint32_t local_4;

	piVar2 = (int*)sub_6FB29450(a1);
	if (piVar2 != nullptr)
	{
		D2_ASSERT(*piVar2 >= piVar2[1]);
		iVar6 = 0;
		if (0 < piVar2[1])
		{
			do
			{
				pBuffer = (D2PacketBufferStrc*)(dword_6FBAB9B0 * iVar6 + piVar2[3]);
				iVar3 = SERVER_GetServerPacketSize(pBuffer, dword_6FBAB9B0, (int*)&local_4);
				if (iVar3 == 0)
				{
					return;
				}
				bVar1 = pBuffer->data[0];
				D2_ASSERT(0xad >= bVar1);
				if (((&dword_6FB76274)[(uint32_t)bVar1 * 3] != 0xffffffff) &&
				    ((local_4 & 0xffff) != (&dword_6FB76274)[(uint32_t)bVar1 * 3]))
				{
					FOG_DisplayAssert("(ptMsgStruct->nCmdSize == -1) || (packetSize == ptMsgStruct->nCmdSize)",
					    __FILE__, __LINE__);
					exit(-1);
				}
				D2_ASSERT((code*)dword_6FB76278[(uint32_t)bVar1 * 3] != nullptr);
				(*(code*)dword_6FB76278[(uint32_t)bVar1 * 3])();
				iVar6 = iVar6 + 1;
			} while (iVar6 < piVar2[1]);
		}
		if (piVar2[1] != 0)
		{
			uVar4 = piVar2[1] * dword_6FBAB9B0;
			puVar7 = (uint32_t*)piVar2[3];
			for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
			{
				*puVar7 = 0;
				puVar7 = puVar7 + 1;
			}
			for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
			{
				*(uint8_t*)puVar7 = 0;
				puVar7 = (uint32_t*)((int)puVar7 + 1);
			}
		}
		piVar2[1] = 0;
	}
}

//D2Client.0x6FAB5750
int32_t __fastcall sub_6FAB5750()
{
	return dword_6FBAB9C4;
}
