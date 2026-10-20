#include "UI/Automap.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Draw/DFloor.h"
#include "Engine/Cursor.h"
#include "Game/Game.h"
#include "Game/PalShift.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundInst.h"
#include "UI/EditBox.h"
#include "UI/Inv.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"

//D2Client.0x6FB6EE00
uint8_t byte_6FB6EE00;
//D2Client.0x6FB6EE30
uint32_t dword_6FB6EE30;
//D2Client.0x6FB6EE34
uint32_t dword_6FB6EE34 = 0xFFFFFFFF;
//D2Client.0x6FB6EE38
uint32_t dword_6FB6EE38 = 2;
//D2Client.0x6FB6EE3C
uint32_t dword_6FB6EE3C = 0xFFFFFFFE;
//D2Client.0x6FB6EE98
uint8_t* gpuint8_t_6FB6EE98 = (uint8_t*)sub_6FACF990;
//D2Client.0x6FB6EECC
uint8_t* gpuint8_t_6FB6EECC = (uint8_t*)sub_6FACFC20;
//D2Client.0x6FB77A38
uint32_t dword_6FB77A38;
//D2Client.0x6FB77BC0
int32_t dword_6FB77BC0 = 10;
//D2Client.0x6FB77BC8
uint32_t dword_6FB77BC8 = 1;
//D2Client.0x6FB77BCC
uint32_t dword_6FB77BCC = 1;
//D2Client.0x6FB78008
uint8_t byte_6FB78008[2] = {0x10};
//D2Client.0x6FB7800A
uint8_t byte_6FB7800A[6] = {0x49, 0xD, 0xA, 0, 0x2E, 0x10};
//D2Client.0x6FB9A828
char byte_6FB9A828;
//D2Client.0x6FBA7988
uint8_t* ptr_6FBA7988;
//D2Client.0x6FBAF990
uint32_t dword_6FBAF990;
//D2Client.0x6FBB1990
int32_t dword_6FBB1990;
//D2Client.0x6FBB1994
uint16_t* gpuint16_t_6FBB1994;
//D2Client.0x6FBB1998
uint8_t* ptr_6FBB1998;
//D2Client.0x6FBB199C
uint32_t dword_6FBB199C;
//D2Client.0x6FBB19A0
uint8_t* ptr_6FBB19A0;
//D2Client.0x6FBB19A4
int32_t* gpint32_t_6FBB19A4;
//D2Client.0x6FBB19A8
int32_t dword_6FBB19A8;
//D2Client.0x6FBB19AC
int32_t dword_6FBB19AC;
//D2Client.0x6FBB19B0
int32_t dword_6FBB19B0;
//D2Client.0x6FBB19B4
int32_t dword_6FBB19B4;
//D2Client.0x6FBB19B8
int32_t dword_6FBB19B8;
//D2Client.0x6FBB19BC
uint8_t byte_6FBB19BC;
//D2Client.0x6FBB19C0
uint8_t byte_6FBB19C0;
//D2Client.0x6FBB19C4
uint8_t byte_6FBB19C4;
//D2Client.0x6FBB19D0
uint8_t byte_6FBB19D0;
//D2Client.0x6FBB19D4
uint8_t byte_6FBB19D4;
//D2Client.0x6FBB19D8
int32_t dword_6FBB19D8;
//D2Client.0x6FBB19DC
int32_t dword_6FBB19DC;
//D2Client.0x6FBB19E0
int32_t dword_6FBB19E0;
//D2Client.0x6FBB19E4
int32_t dword_6FBB19E4;
//D2Client.0x6FBB19F0
uint8_t byte_6FBB19F0;
//D2Client.0x6FBB19F1
uint8_t byte_6FBB19F1;
//D2Client.0x6FBB19F2
uint8_t byte_6FBB19F2;
//D2Client.0x6FBB19F3
uint8_t byte_6FBB19F3;
//D2Client.0x6FBB19F4
uint8_t byte_6FBB19F4;
//D2Client.0x6FBB19F5
uint8_t byte_6FBB19F5;
//D2Client.0x6FBB19F6
uint8_t byte_6FBB19F6;
//D2Client.0x6FBB19F7
uint8_t byte_6FBB19F7;
//D2Client.0x6FBB19F8
uint8_t byte_6FBB19F8;
//D2Client.0x6FBB19F9
uint8_t byte_6FBB19F9;
//D2Client.0x6FBB19FA
uint8_t byte_6FBB19FA;
//D2Client.0x6FBB19FC
int32_t dword_6FBB19FC;
//D2Client.0x6FBB1A08
int32_t dword_6FBB1A08;
//D2Client.0x6FBB1A0C
int32_t dword_6FBB1A0C;
//D2Client.0x6FBB1A10
int32_t dword_6FBB1A10;
//D2Client.0x6FBB1A14
int32_t dword_6FBB1A14;
//D2Client.0x6FBB1A24
uint32_t dword_6FBB1A24;
//D2Client.0x6FBB1A28
uint32_t dword_6FBB1A28;
//D2Client.0x6FBB1A34
int32_t dword_6FBB1A34;
//D2Client.0x6FBB1A38
int32_t dword_6FBB1A38;
//D2Client.0x6FBB1A3C
int32_t dword_6FBB1A3C;
//D2Client.0x6FBB1A40
uint8_t byte_6FBB1A40;

//D2Client.0x6FACBA40
int32_t __cdecl sub_6FACBA40()
{
	int iVar1;
	uint32_t* puVar2;
	int iVar3;
	uint32_t uVar4;
	uint32_t* puVar5;
	uint32_t* puVar6;

	iVar1 = dword_6FBB199C + ((int)dword_6FBB199C >> 0x1f & 0x1ffU);
	uVar4 = dword_6FBB199C & 0x800001ff;
	if ((int)uVar4 < 0)
	{
		uVar4 = (uVar4 - 1 | 0xfffffe00) + 1;
	}
	iVar3 = 0;
	dword_6FBB199C = dword_6FBB199C + 1;
	puVar5 = nullptr;
	puVar2 = (uint32_t*)ptr_6FBB1998;
	if (ptr_6FBB1998 != nullptr)
	{
		do
		{
			if (iVar1 >> 9 <= iVar3)
			{
				puVar6 = (uint32_t*)ptr_6FBB1998;
				if (puVar2 != nullptr)
					goto LAB_6facbacc;
				break;
			}
			puVar6 = puVar2 + 0xa00;
			iVar3 = iVar3 + 1;
			puVar5 = puVar2;
			puVar2 = (uint32_t*)*puVar6;
		} while ((uint32_t*)*puVar6 != nullptr);
	}
	puVar2 = (uint32_t*)D2_ALLOC(0x2804);
	puVar6 = puVar2;
	for (iVar1 = 0xa01; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	puVar6 = puVar2;
	if (puVar5 != nullptr)
	{
		puVar5[0xa00] = (uint32_t)(puVar2);
		puVar6 = (uint32_t*)ptr_6FBB1998;
	}
LAB_6facbacc:
	ptr_6FBB1998 = (uint8_t*)(puVar6);
	puVar2 = puVar2 + uVar4 * 5;
	*puVar2 = 0;
	puVar2[1] = 0;
	puVar2[2] = 0;
	puVar2[3] = 0;
	puVar2[4] = 0;
	return 0;
}

//D2Client.0x6FACBAF0
void __cdecl sub_6FACBAF0()
{
	uint32_t uVar1;
	void* pvVar2;
	void* pFree;
	D2UnitStrc* pUnit;
	int iVar3;
	D2ActiveRoomStrc* pRoom;
	D2LevelDefBin* pDVar4;
	uint32_t* puVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t* puVar8;
	D2ActiveRoomStrc** ppDStack_8;
	uint32_t uStack_4;

	if (dword_6FBB19E4 != 0)
	{
		dword_6FBB19E4 = dword_6FBB19E4 + -1;
		return;
	}
	pUnit = CUNIT_GetPlayer();
	D2_ASSERT(pUnit != nullptr);
	dword_6FBB1A3C = UNITS_GetClientCoordX(pUnit);
	byte_6FBB1A40 = UNITS_GetClientCoordY(pUnit);
	iVar3 = dword_6FBB1A34 - dword_6FBB1A3C;
	if (iVar3 < 0)
	{
		iVar3 = -iVar3;
	}
	iVar6 = dword_6FBB1A38 - byte_6FBB1A40;
	if (iVar6 < 0)
	{
		iVar6 = -iVar6;
	}
	if (iVar6 < iVar3)
	{
		iVar6 = iVar6 + iVar3 * 2;
	}
	else
	{
		iVar6 = iVar3 + iVar6 * 2;
	}
	if (0x4f < iVar6 / 2)
	{
		dword_6FBB1A34 = dword_6FBB1A3C;
		dword_6FBB1A38 = byte_6FBB1A40;
		pRoom = CUNIT_GetPlayerRoom();
		if (pRoom != nullptr)
		{
			ppDStack_8 = nullptr;
			uStack_4 = 0;
			DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_8, (int*)&uStack_4);
			iVar3 = DUNGEON_GetLevelIdFromRoom(pRoom);
			pDVar4 = DATATBLS_GetLevelDefRecord(iVar3);
			uVar1 = pDVar4->dwLayer;
			for (puVar5 = (uint32_t*)ptr_6FBB19A0; puVar5 != nullptr; puVar5 = (uint32_t*)puVar5[6])
			{
				if (*puVar5 == uVar1)
					goto LAB_6facbc15;
			}
			puVar5 = (uint32_t*)D2_ALLOC(0x1c);
			puVar8 = puVar5;
			for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			*puVar5 = uVar1;
			puVar5[6] = (uint32_t)ptr_6FBB19A0;
			ptr_6FBB19A0 = (uint8_t*)(puVar5);
		LAB_6facbc15:
			if (puVar5 != (uint32_t*)gpint32_t_6FBB19A4)
			{
				sub_6FACBCD0();
				pFree = ptr_6FBB1998;
				if (gpint32_t_6FBB19A4 != nullptr)
				{
					while (pFree != nullptr)
					{
						pvVar2 = *(void**)((int)pFree + 0x2800);
						D2_FREE(pFree);
						pFree = pvVar2;
					}
					ptr_6FBB1998 = nullptr;
					dword_6FBB199C = 0;
					gpint32_t_6FBB19A4[2] = 0;
					gpint32_t_6FBB19A4[3] = 0;
					gpint32_t_6FBB19A4[4] = 0;
					gpint32_t_6FBB19A4[5] = 0;
				}
				gpint32_t_6FBB19A4 = (int*)puVar5;
				sub_6FACC610();
			}
			uVar7 = 0;
			if (uStack_4 != 0)
			{
				do
				{
					iVar3 = DUNGEON_GetLevelIdFromRoom(ppDStack_8[uVar7]);
					pDVar4 = DATATBLS_GetLevelDefRecord(iVar3);
					if (uVar1 == pDVar4->dwLayer)
					{
						sub_6FACD180(ppDStack_8[uVar7], 0, (int)(puVar5));
					}
					uVar7 = uVar7 + 1;
				} while (uVar7 < uStack_4);
			}
		}
	}
}

//D2Client.0x6FACBCD0
void __cdecl sub_6FACBCD0()
{
	int iVar1;
	int* piVar2;
	int local_2c;
	int local_28[4];
	int local_18;
	int local_14;
	uint16_t* puStack_10;
	uint16_t* puStack_c;
	uint16_t* puStack_8;
	uint16_t* puStack_4;

	if (gpint32_t_6FBB19A4 == nullptr)
	{
		return;
	}
	piVar2 = local_28;
	for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*piVar2 = 0;
		piVar2 = piVar2 + 1;
	}
	local_2c = *gpint32_t_6FBB19A4;
	local_28[0] = gpint32_t_6FBB19A4[1];
	local_28[1] = *(uint32_t*)((int)ptr_6FBA7988 + 4);
	piVar2 = (int*)gpint32_t_6FBB19A4[2];
	if (piVar2 != nullptr)
	{
		sub_6FACC580((int*)piVar2[3], local_28 + 2);
		if (*piVar2 == 0)
		{
			local_28[2] = local_28[2] + 6;
		}
		sub_6FACC580((int*)piVar2[4], local_28 + 2);
	}
	piVar2 = (int*)gpint32_t_6FBB19A4[3];
	if (piVar2 != nullptr)
	{
		sub_6FACC580((int*)piVar2[3], local_28 + 3);
		if (*piVar2 == 0)
		{
			local_28[3] = local_28[3] + 6;
		}
		sub_6FACC580((int*)piVar2[4], local_28 + 3);
	}
	piVar2 = (int*)gpint32_t_6FBB19A4[4];
	if (piVar2 != nullptr)
	{
		sub_6FACC580((int*)piVar2[3], &local_18);
		if (*piVar2 == 0)
		{
			local_18 = local_18 + 6;
		}
		sub_6FACC580((int*)piVar2[4], &local_18);
	}
	piVar2 = (int*)gpint32_t_6FBB19A4[5];
	if (piVar2 != nullptr)
	{
		sub_6FACC580((int*)piVar2[3], &local_14);
		if (*piVar2 == 0)
		{
			local_14 = local_14 + 6;
		}
		sub_6FACC580((int*)piVar2[4], &local_14);
	}
	if (local_28[2] == 0)
	{
		if (local_28[3] != 0)
		{
		LAB_6facbe81:
			gpuint16_t_6FBB1994 = (uint16_t*)
			    D2_ALLOC(local_28[3]);
			piVar2 = (int*)gpint32_t_6FBB19A4[3];
			puStack_c = gpuint16_t_6FBB1994;
			if (piVar2 != nullptr)
			{
				sub_6FACC5B0((int*)piVar2[3]);
				if (*piVar2 == 0)
				{
					*gpuint16_t_6FBB1994 = (short)piVar2[1];
					gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
					*gpuint16_t_6FBB1994 = *(uint16_t*)((int)piVar2 + 6);
					gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
					*gpuint16_t_6FBB1994 = (short)piVar2[2];
					gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
				}
				sub_6FACC5B0((int*)piVar2[4]);
			}
			goto LAB_6facbefc;
		}
		if (local_18 != 0)
			goto LAB_6facbf04;
		if (local_14 == 0)
		{
			return;
		}
	}
	else
	{
		gpuint16_t_6FBB1994 = (uint16_t*)
		    D2_ALLOC(local_28[2]);
		piVar2 = (int*)gpint32_t_6FBB19A4[2];
		puStack_10 = gpuint16_t_6FBB1994;
		if (piVar2 != nullptr)
		{
			sub_6FACC5B0((int*)piVar2[3]);
			if (*piVar2 == 0)
			{
				*gpuint16_t_6FBB1994 = (short)piVar2[1];
				gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
				*gpuint16_t_6FBB1994 = *(uint16_t*)((int)piVar2 + 6);
				gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
				*gpuint16_t_6FBB1994 = (short)piVar2[2];
				gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
			}
			sub_6FACC5B0((int*)piVar2[4]);
		}
		if (local_28[3] != 0)
			goto LAB_6facbe81;
	LAB_6facbefc:
		if (local_18 != 0)
		{
		LAB_6facbf04:
			gpuint16_t_6FBB1994 = (uint16_t*)
			    D2_ALLOC(local_18);
			piVar2 = (int*)gpint32_t_6FBB19A4[4];
			puStack_8 = gpuint16_t_6FBB1994;
			if (piVar2 != nullptr)
			{
				sub_6FACC5B0((int*)piVar2[3]);
				if (*piVar2 == 0)
				{
					*gpuint16_t_6FBB1994 = (short)piVar2[1];
					gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
					*gpuint16_t_6FBB1994 = *(uint16_t*)((int)piVar2 + 6);
					gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
					*gpuint16_t_6FBB1994 = (short)piVar2[2];
					gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
				}
				sub_6FACC5B0((int*)piVar2[4]);
			}
		}
		if (local_14 == 0)
			goto LAB_6facc002;
	}
	gpuint16_t_6FBB1994 = (uint16_t*)
	    D2_ALLOC(local_14);
	piVar2 = (int*)gpint32_t_6FBB19A4[5];
	puStack_4 = gpuint16_t_6FBB1994;
	if (piVar2 != nullptr)
	{
		sub_6FACC5B0((int*)piVar2[3]);
		if (*piVar2 == 0)
		{
			*gpuint16_t_6FBB1994 = (short)piVar2[1];
			gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
			*gpuint16_t_6FBB1994 = *(uint16_t*)((int)piVar2 + 6);
			gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
			*gpuint16_t_6FBB1994 = (short)piVar2[2];
			gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
		}
		sub_6FACC5B0((int*)piVar2[4]);
	}
LAB_6facc002:
	sub_6FACC080(&local_2c);
	if (puStack_10 != nullptr)
	{
		D2_FREE(puStack_10);
	}
	if (puStack_c != nullptr)
	{
		D2_FREE(puStack_c);
	}
	if (puStack_8 != nullptr)
	{
		D2_FREE(puStack_8);
	}
	if (puStack_4 != nullptr)
	{
		D2_FREE(puStack_4);
	}
}

//D2Client.0x6FACC080
// TODO: decompilation needs review (stack0x, unaff_)
void __fastcall sub_6FACC080(int* a1)
{
	uint8_t stack0xfffffe4c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffe54[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffe58[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffe5c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffe60[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	void* hFile;
	int iVar1;
	DWORD a2;
	DWORD unaff_EBP;
	int unaff_ESI;
	DWORD* pDVar2;
	DWORD local_19c;
	DWORD aDStack_198[102];

	hFile = (void*)sub_6FACC2B0();
	if (hFile != (void*)0xffffffff)
	{
		aDStack_198[2] = 0;
		pDVar2 = aDStack_198 + 3;
		for (iVar1 = 99; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*pDVar2 = 0;
			pDVar2 = pDVar2 + 1;
		}
		local_19c = 0;
		FOG_10110((int)hFile, (int)(aDStack_198 + 2), 400, (int)&local_19c, 0);
		if (local_19c != 400)
		{
			pDVar2 = aDStack_198 + 2;
			for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				*pDVar2 = 0;
				pDVar2 = pDVar2 + 1;
			}
			FOG_10112((int)hFile, 0);
			FOG_10111((int)hFile, (int)aDStack_198, 400, (int)stack0xfffffe5c, 0);
		}
		a2 = aDStack_198[*a1];
		local_19c = GetFileSize(hFile, (LPDWORD)0x0);
		if (a2 == 0)
		{
			aDStack_198[*a1] = local_19c;
		}
		else
		{
			do
			{
				FOG_10112((int)hFile, a2);
				FOG_10110((int)hFile, (int)stack0xfffffe58, 4, (int)stack0xfffffe54, 0);
				a2 = unaff_EBP;
			} while (unaff_EBP != 0);
			FOG_10112((int)hFile, 0);
			FOG_10111((int)hFile, (int)stack0xfffffe54, 4, (int)stack0xfffffe4c, 0);
		}
		FOG_10112((int)hFile, 0);
		FOG_10111((int)hFile, (int)stack0xfffffe60, 400, (int)stack0xfffffe54, 0);
		FOG_10112((int)hFile, unaff_ESI);
		FOG_10111((int)hFile, (int)stack0xfffffe54, 4, (int)stack0xfffffe4c, 0);
		FOG_10111((int)hFile, (int)a1, 4, (int)stack0xfffffe4c, 0);
		FOG_10111((int)hFile, (int)(a1 + 1), 4, (int)stack0xfffffe4c, 0);
		FOG_10111((int)hFile, (int)(a1 + 2), 4, (int)stack0xfffffe4c, 0);
		FOG_10111((int)hFile, (int)(a1 + 3), 4, (int)stack0xfffffe4c, 0);
		FOG_10111((int)hFile, (int)(a1 + 4), 4, (int)stack0xfffffe4c, 0);
		FOG_10111((int)hFile, (int)(a1 + 5), 4, (int)stack0xfffffe4c, 0);
		FOG_10111((int)hFile, (int)(a1 + 6), 4, (int)stack0xfffffe4c, 0);
		iVar1 = a1[3];
		if (iVar1 != 0)
		{
			FOG_10111((int)hFile, a1[7], iVar1, (int)stack0xfffffe4c, 0);
		}
		iVar1 = a1[4];
		if (iVar1 != 0)
		{
			FOG_10111((int)hFile, a1[8], iVar1, (int)stack0xfffffe4c, 0);
		}
		if (a1[5] != 0)
		{
			FOG_10111((int)hFile, a1[9], a1[5], (int)stack0xfffffe4c, 0);
		}
		if (a1[6] != 0)
		{
			FOG_10111((int)hFile, a1[10], a1[6], (int)stack0xfffffe4c, 0);
		}
		FOG_CloseFile(hFile);
	}
}

//D2Client.0x6FACC2B0
// TODO: decompilation needs review (stack0x)
void* __cdecl sub_6FACC2B0()
{
	uint8_t stack0xfffffcd0[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffcd4[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	void* pvVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t* puVar5;
	int* a4;
	uint32_t uVar6;
	int iStack_328;
	int iStack_324;
	uint32_t uStack_320;
	int aiStack_31c[2];
	char acStack_314[9];
	uint32_t local_30b;
	uint8_t auStack_210[8];
	char local_208;
	uint32_t local_207;
	char local_104;
	uint32_t local_103;

	local_208 = byte_6FB9A828;
	puVar5 = &local_207;
	for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
	*(uint16_t*)puVar5 = 0;
	*(uint8_t*)((int)puVar5 + 2) = 0;
	acStack_314[8] = byte_6FB9A828;
	puVar5 = &local_30b;
	for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
	*(uint16_t*)puVar5 = 0;
	*(uint8_t*)((int)puVar5 + 2) = 0;
	local_104 = byte_6FB9A828;
	puVar5 = &local_103;
	for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
	*(uint16_t*)puVar5 = 0;
	*(uint8_t*)((int)puVar5 + 2) = 0;
	FOG_GetSavePath(&local_208, 0x104);
	if (byte_6FBA77F0 == '\0')
	{
	LAB_6facc45f:
		sprintf(acStack_314 + 8, "%s%s.map", &local_208);
		pvVar1 = FOG_CreateFileA(acStack_314 + 8, 0xc0000000, 0, nullptr, 4, 0x80,
		    nullptr);
		if (pvVar1 == (void*)0xffffffff)
		{
			return (void*)0xffffffff;
		}
	}
	else
	{
		SStrPrintf(&local_104, 0x104, "%s%s\\", &local_208);
		FOG_10114((int)&local_104);
		SStrPrintf(acStack_314 + 8, 0x104, "%s%s.map", &local_104);
		pvVar1 = FOG_CreateFileA(acStack_314 + 8, 0xc0000000, 0, nullptr, 4, 0x80,
		    nullptr);
		if (pvVar1 == (void*)0xffffffff)
			goto LAB_6facc45f;
		SStrCopy(&local_208, &local_104, 0x104);
	}
	uStack_320 = 0;
	a4 = &iStack_328;
	aiStack_31c[0] = 0;
	aiStack_31c[1] = 0;
	iStack_324 = 0;
	acStack_314[0] = '\0';
	acStack_314[1] = '\0';
	acStack_314[2] = '\0';
	acStack_314[3] = '\0';
	uVar6 = 0;
	acStack_314[4] = '\0';
	acStack_314[5] = '\0';
	acStack_314[6] = '\0';
	acStack_314[7] = '\0';
	iStack_328 = 0;
	FOG_10110((int)pvVar1, (int)&iStack_324, 0x18, (int)a4, 0);
	uVar3 = uStack_320;
	if ((iStack_328 == 0x18) && (iStack_324 == 0xc))
	{
		uVar4 = 0;
		do
		{
			if (aiStack_31c[uVar4] == *ptr_6FBA7988)
				break;
			uVar4 = uVar4 + 1;
		} while ((int)uVar4 < 4);
		if (uVar4 != 4)
			goto LAB_6facc531;
		uVar4 = uStack_320 + 1 & 0x80000003;
		if ((int)uVar4 < 0)
		{
			uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
		}
		aiStack_31c[uStack_320] = *ptr_6FBA7988;
		uStack_320 = uVar4;
		sprintf(acStack_314 + 8, "%s%s.ma%d", &local_208, gszPlayerName, uVar3);
		FOG_DeleteFileA(acStack_314 + 8);
	}
	else
	{
		iStack_324 = 0xc;
		uStack_320 = 1;
		iVar2 = 0;
		aiStack_31c[0] = *ptr_6FBA7988;
		do
		{
			sprintf(acStack_314 + 8, "%s%s.ma%d", &local_208, gszPlayerName, iVar2);
			FOG_DeleteFileA(acStack_314 + 8);
			iVar2 = iVar2 + 1;
		} while (iVar2 < 4);
		uVar3 = 0;
	}
	uVar6 = 0;
	a4 = nullptr;
	FOG_10112((int)pvVar1, 0);
	FOG_10111((int)pvVar1, (int)stack0xfffffcd4, 0x18, (int)stack0xfffffcd0, 0);
	uVar4 = uVar3;
LAB_6facc531:
	FOG_CloseFile(pvVar1);
	sprintf(acStack_314, "%s%s.ma%d", auStack_210, gszPlayerName, uVar4, a4, uVar6);
	pvVar1 = FOG_CreateFileA(acStack_314, 0xc0000000, 0, nullptr, 4, 0x80, nullptr);
	return pvVar1;
}

//D2Client.0x6FACC580
void __fastcall sub_6FACC580(int* a1, int* a2)
{
	if (a1 != nullptr)
	{
		do
		{
			sub_6FACC580((int*)a1[3], a2);
			if (*a1 == 0)
			{
				*a2 = *a2 + 6;
			}
			a1 = (int*)a1[4];
		} while (a1 != nullptr);
	}
}

//D2Client.0x6FACC5B0
void __fastcall sub_6FACC5B0(int* a1)
{
	if (a1 != nullptr)
	{
		do
		{
			sub_6FACC5B0((int*)a1[3]);
			if (*a1 == 0)
			{
				*gpuint16_t_6FBB1994 = (short)a1[1];
				gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
				*gpuint16_t_6FBB1994 = *(uint16_t*)((int)a1 + 6);
				gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
				*gpuint16_t_6FBB1994 = (short)a1[2];
				gpuint16_t_6FBB1994 = gpuint16_t_6FBB1994 + 1;
			}
			a1 = (int*)a1[4];
		} while (a1 != nullptr);
	}
}

//D2Client.0x6FACC610
// TODO: decompilation needs review (stack0x, unaff_)
void __cdecl sub_6FACC610()
{
	uint8_t stack0xfffffe10[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffe18[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffe1c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffe20[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffe24[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	short sVar1;
	uint16_t uVar2;
	void* hFILE;
	void* pvVar3;
	uint32_t* puVar4;
	int iVar5;
	int iVar6;
	int* piVar7;
	uint8_t* puVar8;
	uint32_t unaff_EBX;
	uint32_t uVar9;
	uint32_t unaff_ESI;
	uint32_t uVar10;
	uint32_t* puVar11;
	int local_1d4;
	int* piStack_1d0;
	int iStack_1cc;
	int iStack_1c8;
	int iStack_1c4;
	int iStack_1c0;
	uint32_t uStack_1bc;
	uint32_t auStack_1b8[2];
	uint32_t auStack_1b0;
	uint8_t auStack_1ac[4];
	uint8_t auStack_1a8[8];
	int aiStack_1a0[4];
	int local_190;
	int local_18c[99];

	if ((gpint32_t_6FBB19A4 != nullptr) && (hFILE = (void*)sub_6FACC2B0(), hFILE != (void*)0xffffffff))
	{
		local_190 = 0;
		piVar7 = aiStack_1a0 + 5;
		for (iVar5 = 99; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*piVar7 = 0;
			piVar7 = piVar7 + 1;
		}
		local_1d4 = 0;
		FOG_10110((int)hFILE, (int)(aiStack_1a0 + 4), 400, (int)&local_1d4, 0);
		if (local_1d4 == 400)
		{
			iStack_1cc = 0;
			iStack_1c0 = aiStack_1a0[*gpint32_t_6FBB19A4 + 4];
			if (iStack_1c0 != 0)
			{
				while (true)
				{
					iVar5 = iStack_1cc;
					piVar7 = (int*)stack0xfffffe18;
					uStack_1bc = 0;
					puVar11 = auStack_1b8;
					for (iVar6 = 10; iVar6 != 0; iVar6 = iVar6 + -1)
					{
						*puVar11 = 0;
						puVar11 = puVar11 + 1;
					}
					FOG_10112((int)hFILE, iStack_1c0);
					FOG_10110((int)hFILE, (int)&iStack_1c8, 4, (int)stack0xfffffe24, 0);
					FOG_10110((int)hFILE, (int)&iStack_1c4, 4, (int)stack0xfffffe24, 0);
					FOG_10110((int)hFILE, (int)&iStack_1c0, 4, (int)stack0xfffffe24, 0);
					FOG_10110((int)hFILE, (int)&uStack_1bc, 4, (int)stack0xfffffe24, 0);
					FOG_10110((int)hFILE, (int)auStack_1b8, 4, (int)stack0xfffffe24, 0);
					FOG_10110((int)hFILE, (int)(auStack_1b8 + 1), 4, (int)stack0xfffffe24, 0);
					FOG_10110((int)hFILE, (int)auStack_1b0, 4, (int)stack0xfffffe24, 0);
					FOG_10110((int)hFILE, (int)auStack_1ac, 4, (int)stack0xfffffe24, 0);
					if (iStack_1c4 != *gpint32_t_6FBB19A4)
						break;
					if (auStack_1b8[0] != 0)
					{
						pvVar3 = D2_ALLOC(auStack_1b8[0]);
						uVar9 = auStack_1b8[0] >> 1;
						FOG_10110((int)hFILE, (int)pvVar3, auStack_1b8[0], (int)stack0xfffffe24, 0);
						D2_ASSERT(unaff_EBX == auStack_1b8[0]);
						uVar10 = 0;
						if (uVar9 != 0)
						{
							do
							{
								sVar1 = *(short*)((int)pvVar3 + uVar10 * 2);
								if (dword_6FBB19B8 <= sVar1)
								{
									if (local_1d4 == 0)
									{
										aiStack_1a0[*gpint32_t_6FBB19A4 + 2] = 0;
										FOG_10112((int)hFILE, 0);
										piVar7 = aiStack_1a0;
										iVar5 = 400;
									}
									else
									{
										FOG_10112((int)hFILE, local_1d4);
										iVar5 = 4;
										piVar7 = (int*)stack0xfffffe20;
									}
									FOG_10111((int)hFILE, (int)piVar7, iVar5, (int)stack0xfffffe18, 0);
									break;
								}
								uVar2 = *(uint16_t*)((int)pvVar3 + uVar10 * 2 + 2);
								piStack_1d0 = gpint32_t_6FBB19A4 + 2;
								iStack_1cc = CONCAT22((*(uint16_t*)((uint8_t*)&iStack_1cc + 2)), *(uint16_t*)((int)pvVar3 + uVar10 * 2 + 4));
								puVar4 = (uint32_t*)sub_6FACBA40();
								*(short*)(puVar4 + 1) = sVar1;
								*(uint16_t*)((int)puVar4 + 6) = uVar2;
								*(uint16_t*)(puVar4 + 2) = (uint16_t)iStack_1cc;
								*puVar4 = 1;
								sub_6FACCD50((int)puVar4, piStack_1d0);
								uVar10 = uVar10 + 3;
							} while (uVar10 < uVar9);
						}
						D2_FREE(pvVar3);
					}
					if (uStack_1bc != 0)
					{
						pvVar3 = D2_ALLOC(uStack_1bc);
						uVar9 = uStack_1bc >> 1;
						FOG_10110((int)hFILE, (int)pvVar3, uStack_1bc, (int)stack0xfffffe1c, 0);
						D2_ASSERT(unaff_ESI == uStack_1bc);
						uVar10 = 0;
						if (uVar9 != 0)
						{
							do
							{
								sVar1 = *(short*)((int)pvVar3 + uVar10 * 2);
								if (dword_6FBB19B8 <= sVar1)
								{
									if (unaff_EBX == 0)
									{
										aiStack_1a0[*gpint32_t_6FBB19A4] = 0;
										FOG_10112((int)hFILE, 0);
										puVar8 = auStack_1a8;
										iVar5 = 400;
									}
									else
									{
										FOG_10112((int)hFILE, unaff_EBX);
										iVar5 = 4;
										puVar8 = stack0xfffffe10;
									}
									FOG_10111((int)hFILE, (int)puVar8, iVar5, (int)stack0xfffffe18, 0);
									break;
								}
								uVar2 = *(uint16_t*)((int)pvVar3 + uVar10 * 2 + 2);
								piVar7 = gpint32_t_6FBB19A4 + 3;
								local_1d4 = CONCAT22((*(uint16_t*)((uint8_t*)&local_1d4 + 2)), *(uint16_t*)((int)pvVar3 + uVar10 * 2 + 4));
								puVar4 = (uint32_t*)sub_6FACBA40();
								*(short*)(puVar4 + 1) = sVar1;
								*(uint16_t*)((int)puVar4 + 6) = uVar2;
								*(uint16_t*)(puVar4 + 2) = (uint16_t)local_1d4;
								*puVar4 = 1;
								sub_6FACCD50((int)puVar4, piVar7);
								uVar10 = uVar10 + 3;
							} while (uVar10 < uVar9);
						}
						D2_FREE(pvVar3);
					}
					if (auStack_1b8[0] != 0)
					{
						if (iStack_1c4 == *(int*)((int)ptr_6FBA7988 + 4))
						{
							pvVar3 = D2_ALLOC(auStack_1b8[0]);
							uVar9 = auStack_1b8[0] >> 1;
							FOG_10110((int)hFILE, (int)pvVar3, auStack_1b8[0], (int)stack0xfffffe1c, 0);
							D2_ASSERT(unaff_ESI == auStack_1b8[0]);
							uVar10 = 0;
							if (uVar9 != 0)
							{
								do
								{
									sVar1 = *(short*)((int)pvVar3 + uVar10 * 2);
									if (dword_6FBB19B8 <= sVar1)
									{
										if (unaff_EBX == 0)
										{
											aiStack_1a0[*gpint32_t_6FBB19A4] = 0;
											FOG_10112((int)hFILE, 0);
											puVar8 = auStack_1a8;
											iVar5 = 400;
										}
										else
										{
											FOG_10112((int)hFILE, unaff_EBX);
											iVar5 = 4;
											puVar8 = stack0xfffffe10;
										}
										FOG_10111((int)hFILE, (int)puVar8, iVar5, (int)stack0xfffffe18, 0);
										break;
									}
									uVar2 = *(uint16_t*)((int)pvVar3 + uVar10 * 2 + 2);
									piVar7 = gpint32_t_6FBB19A4 + 4;
									local_1d4 = CONCAT22((*(uint16_t*)((uint8_t*)&local_1d4 + 2)), *(uint16_t*)((int)pvVar3 + uVar10 * 2 + 4));
									puVar4 = (uint32_t*)sub_6FACBA40();
									*(short*)(puVar4 + 1) = sVar1;
									*(uint16_t*)((int)puVar4 + 6) = uVar2;
									*(uint16_t*)(puVar4 + 2) = (uint16_t)local_1d4;
									*puVar4 = 1;
									sub_6FACCD50((int)puVar4, piVar7);
									uVar10 = uVar10 + 3;
								} while (uVar10 < uVar9);
							}
							D2_FREE(pvVar3);
						}
						else
						{
							FOG_10112((int)hFILE, auStack_1b8[0]);
						}
					}
					if (auStack_1b8[1] != 0)
					{
						pvVar3 = D2_ALLOC(auStack_1b8[1]);
						uVar9 = auStack_1b8[1] >> 1;
						FOG_10110((int)hFILE, (int)pvVar3, auStack_1b8[1], (int)stack0xfffffe1c, 0);
						D2_ASSERT(unaff_ESI == auStack_1b8[1]);
						uVar10 = 0;
						if (uVar9 != 0)
						{
							do
							{
								sVar1 = *(short*)((int)pvVar3 + uVar10 * 2);
								if ((&dword_6FBB19B8)[iStack_1c8] <= (int)sVar1)
								{
									if (unaff_EBX == 0)
									{
										aiStack_1a0[*gpint32_t_6FBB19A4] = 0;
										FOG_10112((int)hFILE, 0);
										puVar8 = auStack_1a8;
										iVar5 = 400;
									}
									else
									{
										FOG_10112((int)hFILE, unaff_EBX);
										iVar5 = 4;
										puVar8 = stack0xfffffe10;
									}
									FOG_10111((int)hFILE, (int)puVar8, iVar5, (int)stack0xfffffe1c, 0);
									unaff_EBX = 0;
									break;
								}
								uVar2 = *(uint16_t*)((int)pvVar3 + uVar10 * 2 + 2);
								piVar7 = gpint32_t_6FBB19A4 + 5;
								local_1d4 = CONCAT22((*(uint16_t*)((uint8_t*)&local_1d4 + 2)), *(uint16_t*)((int)pvVar3 + uVar10 * 2 + 4));
								puVar4 = (uint32_t*)sub_6FACBA40();
								*(short*)(puVar4 + 1) = sVar1;
								*(uint16_t*)((int)puVar4 + 6) = uVar2;
								*(uint16_t*)(puVar4 + 2) = (uint16_t)local_1d4;
								*puVar4 = 1;
								sub_6FACCD50((int)puVar4, piVar7);
								uVar10 = uVar10 + 3;
							} while (uVar10 < uVar9);
						}
						D2_FREE(pvVar3);
					}
					iStack_1cc = iStack_1c0;
					if (iStack_1c0 == 0)
					{
						FOG_CloseFile(hFILE);
						return;
					}
				}
				local_1d4 = 0;
				if (iVar5 == 0)
				{
					aiStack_1a0[*gpint32_t_6FBB19A4 + 2] = 0;
					FOG_10112((int)hFILE, 0);
					piVar7 = aiStack_1a0;
					iVar5 = 400;
				}
				else
				{
					FOG_10112((int)hFILE, iVar5);
					iVar5 = 4;
				}
				FOG_10111((int)hFILE, (int)piVar7, iVar5, (int)stack0xfffffe24, 0);
			}
		}
		FOG_CloseFile(hFILE);
	}
}

//D2Client.0x6FACCD50
int __fastcall sub_6FACCD50(int a1, int* a2)
{
	short sVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int local_8;
	int* local_4;

	iVar4 = *a2;
	local_4 = a2;
	if (iVar4 == 0)
	{
		*(uint32_t*)(a1 + 0xc) = 0;
		*(uint32_t*)(a1 + 0x10) = 0;
		*(uint16_t*)(a1 + 10) = 0;
		iVar3 = 1;
		goto LAB_6facd0b1;
	}
	iVar3 = (int)*(short*)(a1 + 8) - (int)*(short*)(iVar4 + 8);
	if ((iVar3 == 0) &&
	    (iVar3 = (int)*(short*)(a1 + 6) - (int)*(short*)(iVar4 + 6), iVar3 == 0))
	{
		if (((&dword_6FBAF990)[*(short*)(a1 + 4)] == -1) ||
		    ((&dword_6FBAF990)[*(short*)(a1 + 4)] == (&dword_6FBAF990)[*(short*)(iVar4 + 4)]))
			goto LAB_6faccf42;
		iVar3 = (int)*(short*)(a1 + 4) - (int)*(short*)(iVar4 + 4);
	}
	local_8 = iVar4;
	if (-1 < iVar3)
	{
		if (0 < iVar3)
		{
			iVar3 = sub_6FACCD50(a1, (int*)(iVar4 + 0x10));
			a1 = iVar4;
			if (iVar3 != 0)
			{
				sVar1 = *(short*)(iVar4 + 10);
				if (sVar1 == -1)
					goto LAB_6faccdd5;
				if (sVar1 == 0)
				{
					*(uint16_t*)(iVar4 + 10) = 1;
					*local_4 = iVar4;
					return iVar3;
				}
				if (sVar1 == 1)
				{
					iVar3 = *(int*)(iVar4 + 0x10);
					if (*(short*)(iVar3 + 10) == -1)
					{
						iVar2 = *(int*)(iVar3 + 0xc);
						sVar1 = *(short*)(iVar2 + 10);
						if (sVar1 == -1)
						{
							*(uint16_t*)(iVar4 + 10) = 0;
							*(uint16_t*)(iVar3 + 10) = 1;
						}
						else if (sVar1 == 0)
						{
							*(uint16_t*)(iVar4 + 10) = 0;
							*(uint16_t*)(iVar3 + 10) = 0;
						}
						else if (sVar1 == 1)
						{
							*(uint16_t*)(iVar4 + 10) = 0xffff;
							*(uint16_t*)(iVar3 + 10) = 0;
						}
						*(uint16_t*)(iVar2 + 10) = 0;
						sub_6FACD120((int*)(iVar4 + 0x10));
						sub_6FACD0C0(&local_8);
						*local_4 = local_8;
						return 0;
					}
					D2_ASSERT(*(short*)(iVar3 + 10) == 1);
					*(uint16_t*)(iVar4 + 10) = 0;
					*(uint16_t*)(iVar3 + 10) = 0;
					D2_ASSERT(iVar4);
					iVar3 = *(int*)(iVar4 + 0x10);
					if (iVar3 != 0)
					{
						*(uint32_t*)(iVar4 + 0x10) = *(uint32_t*)(iVar3 + 0xc);
						*(int*)(iVar3 + 0xc) = iVar4;
						*local_4 = iVar3;
						return 0;
					}
					FOG_DisplayAssert("ptRoot->ptMore != NULL",
					    __FILE__, __LINE__);
					exit(-1);
				}
			}
			goto LAB_6facd0b1;
		}
		goto LAB_6faccf42;
	}
	iVar3 = sub_6FACCD50(a1, (int*)(iVar4 + 0xc));
	a1 = iVar4;
	if (iVar3 == 0)
	{
	LAB_6facd0b1:
		*local_4 = a1;
		return iVar3;
	}
	sVar1 = *(short*)(iVar4 + 10);
	if (sVar1 != -1)
	{
		if (sVar1 == 0)
		{
			*(uint16_t*)(iVar4 + 10) = 0xffff;
			*local_4 = iVar4;
			return iVar3;
		}
		if (sVar1 == 1)
		{
		LAB_6faccdd5:
			*(uint16_t*)(iVar4 + 10) = 0;
			*local_4 = iVar4;
			return 0;
		}
		goto LAB_6facd0b1;
	}
	iVar3 = *(int*)(iVar4 + 0xc);
	if (*(short*)(iVar3 + 10) == -1)
	{
		*(uint16_t*)(iVar4 + 10) = 0;
		*(uint16_t*)(iVar3 + 10) = 0;
		if (iVar4 == 0)
		{
			FOG_DisplayAssert("ptRoot != NULL", __FILE__, __LINE__);
			exit(-1);
		}
		iVar3 = *(int*)(iVar4 + 0xc);
		if (iVar3 != 0)
		{
			*(uint32_t*)(iVar4 + 0xc) = *(uint32_t*)(iVar3 + 0x10);
			*(int*)(iVar3 + 0x10) = iVar4;
			*local_4 = iVar3;
			return 0;
		}
		FOG_DisplayAssert("ptRoot->ptLess != NULL", __FILE__, __LINE__);
		exit(-1);
	}
	D2_ASSERT(*(short*)(iVar3 + 10) == 1);
	iVar2 = *(int*)(iVar3 + 0x10);
	sVar1 = *(short*)(iVar2 + 10);
	if (sVar1 == -1)
	{
		*(uint16_t*)(iVar4 + 10) = 1;
	LAB_6faccecf:
		*(uint16_t*)(iVar3 + 10) = 0;
	}
	else
	{
		if (sVar1 == 0)
		{
			*(uint16_t*)(iVar4 + 10) = 0;
			goto LAB_6faccecf;
		}
		if (sVar1 == 1)
		{
			*(uint16_t*)(iVar4 + 10) = 0;
			*(uint16_t*)(iVar3 + 10) = 0xffff;
		}
	}
	*(uint16_t*)(iVar2 + 10) = 0;
	iVar3 = *(int*)(iVar4 + 0xc);
	D2_ASSERT(iVar3);
	iVar2 = *(int*)(iVar3 + 0x10);
	D2_ASSERT(iVar2);
	*(uint32_t*)(iVar3 + 0x10) = *(uint32_t*)(iVar2 + 0xc);
	*(int*)(iVar2 + 0xc) = iVar3;
	*(int*)(iVar4 + 0xc) = iVar2;
	sub_6FACD120(&local_8);
	iVar4 = local_8;
LAB_6faccf42:
	*local_4 = iVar4;
	return 0;
}

//D2Client.0x6FACD0C0
void __fastcall sub_6FACD0C0(int* a1)
{
	int iVar1;
	int iVar2;

	iVar1 = *a1;
	D2_ASSERT(iVar1);
	iVar2 = *(int*)(iVar1 + 0x10);
	D2_ASSERT(iVar2);
	*(uint32_t*)(iVar1 + 0x10) = *(uint32_t*)(iVar2 + 0xc);
	*(int*)(iVar2 + 0xc) = iVar1;
	*a1 = iVar2;
}

//D2Client.0x6FACD120
void __fastcall sub_6FACD120(int* a1)
{
	int iVar1;
	int iVar2;

	iVar1 = *a1;
	D2_ASSERT(iVar1);
	iVar2 = *(int*)(iVar1 + 0xc);
	D2_ASSERT(iVar2);
	*(uint32_t*)(iVar1 + 0xc) = *(uint32_t*)(iVar2 + 0x10);
	*(int*)(iVar2 + 0x10) = iVar1;
	*a1 = iVar2;
}

//D2Client.0x6FACD180
void __fastcall sub_6FACD180(D2ActiveRoomStrc* pActiveRoom, int a2, int a3)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	uint8_t bVar3;
	D2DrlgRoomStrc* pDVar4;
	D2DrlgTileDataStrc* pDVar5;
	D2ObjectsTxt* pDVar6;
	int iVar7;
	uint32_t* puVar8;
	uint32_t uVar9;
	uint32_t local_c;
	D2ActiveRoomStrc* local_8;
	int local_4;

	uVar9 = 0;
	local_c = 0;
	local_8 = pActiveRoom;
	local_4 = a2;
	pDVar4 = DUNGEON_GetRoomExFromRoom(pActiveRoom);
	pDVar5 = DUNGEON_GetFloorTilesFromRoom(pActiveRoom, (int*)&local_c);
	if (local_c != 0)
	{
		puVar8 = &pDVar5->dwFlags;
		do
		{
			if (((*puVar8 & 8) == 0) &&
			    ((((*puVar8 & 0x20000) != 0 || (dword_6FBB19E0 != 0)) || (local_4 != 0))))
			{
				sub_6FACD3C0((int)(puVar8 + -5), (int*)pDVar4, (int*)(a3 + 8));
			}
			uVar9 = uVar9 + 1;
			puVar8 = puVar8 + 0xc;
			pActiveRoom = local_8;
		} while (uVar9 < local_c);
	}
	pDVar5 = DUNGEON_GetWallTilesFromRoom(pActiveRoom, (int*)&local_c);
	uVar9 = 0;
	if (local_c != 0)
	{
		puVar8 = &pDVar5->dwFlags;
		do
		{
			if (((*puVar8 & 8) == 0) &&
			    ((((*puVar8 & 0x20000) != 0 || (dword_6FBB19E0 != 0)) || (local_4 != 0))))
			{
				sub_6FACD3C0((int)(puVar8 + -5), (int*)pDVar4, (int*)(a3 + 0xc));
			}
			uVar9 = uVar9 + 1;
			puVar8 = puVar8 + 0xc;
			pActiveRoom = local_8;
		} while (uVar9 < local_c);
	}
	pDVar1 = pActiveRoom->pUnitFirst;
	do
	{
		if (pDVar1 == nullptr)
		{
			return;
		}
		if (dword_6FBB19E0 == 0)
		{
			if ((pDVar1->dwFlags >> 0x1c & 1) != 0)
			{
				if (pDVar1 == nullptr)
					goto LAB_6facd29e;
				if ((pDVar1->dwFlags >> 0x1d & 1) == 0)
					goto LAB_6facd290;
			}
		}
		else
		{
		LAB_6facd290:
			if (pDVar1 != nullptr)
			{
				pDVar1->dwFlags = pDVar1->dwFlags | 0x20000000;
			}
		LAB_6facd29e:
			if (pDVar1->dwUnitType == 1)
			{
				if (((pDVar1 != nullptr) && (iVar7 = pDVar1->dwClassId, -1 < iVar7)) &&
				    ((iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar7 < *(int*)(iVar2 + 0xa80) &&
				                                                      ((((iVar7 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar7 * 0x1a8), -1 < iVar7 && (iVar7 < *(int*)(iVar2 + 0xa98))) &&
				                                                            (iVar7 = *(int*)(iVar2 + 0xa90) + iVar7 * 0x134, iVar7 != 0)) &&
				                                                          (uVar9 = *(uint32_t*)(iVar7 + 0x118), uVar9 != 0))))))
					goto LAB_6facd395;
			}
			else if (pDVar1->dwUnitType == 2)
			{
				if (pDVar1 == nullptr)
				{
					iVar7 = -1;
				}
				else
				{
					iVar7 = pDVar1->dwClassId;
				}
				pDVar6 = DATATBLS_GetObjectsTxtRecord(iVar7);
				uVar9 = pDVar6->dwAutomap;
				if (uVar9 != 0)
				{
					if (iVar7 == 0x10b)
					{
						iVar7 = DUNGEON_GetLevelIdFromRoom(local_8);
						bVar3 = DRLG_GetActNoFromLevelId(iVar7);
						if ((bVar3 != 2) && (bVar3 != 3))
							goto LAB_6facd39d;
						uVar9 = pDVar6->dwAutomap;
					}
					else if (iVar7 == 0x16e)
					{
						if ((pDVar1 == nullptr) || (pDVar1->dwAnimMode != 2))
							goto LAB_6facd39d;
					}
					else if (iVar7 == 0x192)
					{
						iVar7 = DUNGEON_GetLevelIdFromRoom(local_8);
						if (iVar7 != 0x4a)
							goto LAB_6facd39d;
						uVar9 = pDVar6->dwAutomap;
					}
				LAB_6facd395:
					sub_6FACD560(pDVar1, uVar9, (int*)(a3 + 0x10));
				}
			}
		}
	LAB_6facd39d:
		pDVar1 = pDVar1->pRoomNext;
	} while (true);
}

//D2Client.0x6FACD3C0
void __fastcall sub_6FACD3C0(int a1, int* a2, int* a3)
{
	uint32_t dwAutomapLevelType;
	uint32_t dwAutomapTileType;
	int iVar1;
	int iVar2;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	if ((*(uint32_t*)(a1 + 0x14) & 0x40000) == 0)
	{
		*(uint32_t*)(a1 + 0x14) = *(uint32_t*)(a1 + 0x14) | 0x40000;
		dwAutomapLevelType = DRLG_GetLevelTypeFromLevelId(*(int*)(*a2 + 4));
		dwAutomapTileType = D2CMP_10077_GetTileType(*(D2TileLibraryEntryStrc**)(a1 + 0x18));
		iStack_4 = D2CMP_10078_GetTileStyle(*(D2TileLibraryEntryStrc**)(a1 + 0x18));
		iVar1 = D2CMP_10082_GetTileSequence(*(D2TileLibraryEntryStrc**)(a1 + 0x18));
		iVar1 = DATATBLS_GetAutomapCellId(dwAutomapLevelType, dwAutomapTileType, iStack_4, iVar1);
		if (iVar1 != -1)
		{
			iVar2 = sub_6FACBA40();
			iStack_8 = *(int*)(a1 + 8) + a2[1];
			iStack_c = *(int*)(a1 + 0xc) + a2[2];
			DUNGEON_GameTileToClientCoords(&iStack_8, &iStack_c);
			iStack_8 = iStack_8 / 10;
			iStack_c = iStack_c / 10;
			D2_ASSERT(!((iStack_8 < -0x8000) || (0x7fff < iStack_8)));
			D2_ASSERT(!((iStack_c < -0x8000) || (0x7fff < iStack_c)));
			D2_ASSERT(!((iVar1 < -0x8000) || (0x7fff < iVar1)));
			if (0xf < *(int*)(a1 + 0x1c))
			{
				iStack_c = iStack_c + 0x18;
			}
			*(short*)(iVar2 + 4) = (short)iVar1;
			*(uint16_t*)(iVar2 + 6) = (uint16_t)iStack_8;
			*(uint16_t*)(iVar2 + 8) = (uint16_t)iStack_c;
			sub_6FACCD50(iVar2, a3);
		}
	}
}

//D2Client.0x6FACD560
void __fastcall sub_6FACD560(D2UnitStrc* pUnit, int a2, int* a3)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar1 = sub_6FACBA40();
	iVar2 = UNITS_GetClientCoordX(pUnit);
	iVar2 = iVar2 / 10 + 1;
	iVar3 = UNITS_GetClientCoordY(pUnit);
	iVar3 = iVar3 / 10 + -3;
	D2_ASSERT(!((iVar2 < -0x8000) || (0x7fff < iVar2)));
	if ((-0x8001 < iVar3) && (iVar3 < 0x8000))
	{
		if ((-0x8001 < a2) && (a2 < 0x8000))
		{
			*(short*)(iVar1 + 4) = (short)a2;
			*(short*)(iVar1 + 6) = (short)iVar2;
			*(short*)(iVar1 + 8) = (short)iVar3;
			sub_6FACCD50(iVar1, a3);
			return;
		}
		FOG_DisplayAssert("nCelNum >= SHRT_MIN && nCelNum <= SHRT_MAX",
		    __FILE__, __LINE__);
		exit(-1);
	}
	FOG_DisplayAssert("nPixelY >= SHRT_MIN && nPixelY <= SHRT_MAX",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FACD650
void __cdecl sub_6FACD650()
{
	dword_6FBB19E4 = 2;
}

//D2Client.0x6FACD660
void __cdecl sub_6FACD660(D2ActiveRoomStrc* pActiveRoom)
{
	uint32_t uVar1;
	void* pvVar2;
	void* pvVar3;
	int iVar4;
	D2LevelDefBin* pDVar5;
	uint32_t* puVar6;
	int* piVar7;
	uint32_t* puVar8;
	int* piVar9;
	int iStack_4;

	if (gpint32_t_6FBB19A4 == nullptr)
	{
		iStack_4 = -1;
	}
	else
	{
		iStack_4 = *gpint32_t_6FBB19A4;
	}
	iVar4 = DUNGEON_GetLevelIdFromRoom(pActiveRoom);
	pDVar5 = DATATBLS_GetLevelDefRecord(iVar4);
	uVar1 = pDVar5->dwLayer;
	for (puVar6 = (uint32_t*)ptr_6FBB19A0; puVar6 != nullptr; puVar6 = (uint32_t*)puVar6[6])
	{
		if (*puVar6 == uVar1)
			goto LAB_6facd6de;
	}
	puVar6 = (uint32_t*)D2_ALLOC(0x1c);
	puVar8 = puVar6;
	for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	*puVar6 = uVar1;
	puVar6[6] = (uint32_t)ptr_6FBB19A0;
	ptr_6FBB19A0 = (uint8_t*)(puVar6);
LAB_6facd6de:
	if (puVar6 != (uint32_t*)gpint32_t_6FBB19A4)
	{
		sub_6FACBCD0();
		pvVar3 = ptr_6FBB1998;
		if (gpint32_t_6FBB19A4 != nullptr)
		{
			while (pvVar3 != nullptr)
			{
				pvVar2 = *(void**)((int)pvVar3 + 0x2800);
				D2_FREE(pvVar3);
				pvVar3 = pvVar2;
			}
			ptr_6FBB1998 = nullptr;
			dword_6FBB199C = 0;
			gpint32_t_6FBB19A4[2] = 0;
			gpint32_t_6FBB19A4[3] = 0;
			gpint32_t_6FBB19A4[4] = 0;
			gpint32_t_6FBB19A4[5] = 0;
		}
		gpint32_t_6FBB19A4 = (int*)puVar6;
		sub_6FACC610();
	}
	sub_6FACD180(pActiveRoom, 1, (int)(puVar6));
	piVar7 = (int*)ptr_6FBB19A0;
	if (iStack_4 != -1)
	{
		for (; piVar7 != nullptr; piVar7 = (int*)piVar7[6])
		{
			if (*piVar7 == iStack_4)
				goto LAB_6facd7b7;
		}
		piVar7 = (int*)D2_ALLOC(0x1c);
		piVar9 = piVar7;
		for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*piVar9 = 0;
			piVar9 = piVar9 + 1;
		}
		*piVar7 = iStack_4;
		piVar7[6] = (int)ptr_6FBB19A0;
		ptr_6FBB19A0 = (uint8_t*)(piVar7);
	LAB_6facd7b7:
		if (piVar7 != gpint32_t_6FBB19A4)
		{
			sub_6FACBCD0();
			pvVar3 = ptr_6FBB1998;
			if (gpint32_t_6FBB19A4 != nullptr)
			{
				while (pvVar3 != nullptr)
				{
					pvVar2 = *(void**)((int)pvVar3 + 0x2800);
					D2_FREE(pvVar3);
					pvVar3 = pvVar2;
				}
				ptr_6FBB1998 = nullptr;
				dword_6FBB199C = 0;
				gpint32_t_6FBB19A4[2] = 0;
				gpint32_t_6FBB19A4[3] = 0;
				gpint32_t_6FBB19A4[4] = 0;
				gpint32_t_6FBB19A4[5] = 0;
			}
			gpint32_t_6FBB19A4 = piVar7;
			sub_6FACC610();
		}
	}
}

//D2Client.0x6FACD840
void __cdecl sub_6FACD840(int a1, int a2, int a3, int a4)
{
	uint32_t uVar1;
	void* pvVar2;
	void* pvVar3;
	D2LevelDefBin* pDVar4;
	uint32_t* puVar5;
	int* piVar6;
	int iVar7;
	uint32_t* puVar8;
	uint32_t uVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int* piVar13;
	int iStack_1c;
	int iStack_18;
	uint32_t* puStack_14;
	uint32_t* puStack_10;
	int iStack_c;
	int iStack_8;

	uVar9 = 0;
	if (gpint32_t_6FBB19A4 == nullptr)
	{
		iStack_8 = -1;
	}
	else
	{
		iStack_8 = *gpint32_t_6FBB19A4;
	}
	pDVar4 = DATATBLS_GetLevelDefRecord(a1);
	uVar1 = pDVar4->dwLayer;
	for (puStack_14 = (uint32_t*)ptr_6FBB19A0; puStack_14 != nullptr;
	     puStack_14 = (uint32_t*)puStack_14[6])
	{
		if (*puStack_14 == uVar1)
			goto LAB_6facd8cd;
	}
	puStack_14 = (uint32_t*)D2_ALLOC(0x1c);
	puVar8 = puStack_14;
	for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	*puStack_14 = uVar1;
	puStack_14[6] = (uint32_t)ptr_6FBB19A0;
	ptr_6FBB19A0 = (uint8_t*)(puStack_14);
LAB_6facd8cd:
	if (puStack_14 != (uint32_t*)gpint32_t_6FBB19A4)
	{
		sub_6FACBCD0();
		pvVar3 = ptr_6FBB1998;
		if (gpint32_t_6FBB19A4 != nullptr)
		{
			while (pvVar3 != nullptr)
			{
				pvVar2 = *(void**)((int)pvVar3 + 0x2800);
				D2_FREE(pvVar3);
				pvVar3 = pvVar2;
			}
			ptr_6FBB1998 = nullptr;
			dword_6FBB199C = 0;
			gpint32_t_6FBB19A4[2] = 0;
			gpint32_t_6FBB19A4[3] = 0;
			gpint32_t_6FBB19A4[4] = 0;
			gpint32_t_6FBB19A4[5] = 0;
		}
		gpint32_t_6FBB19A4 = (int*)puStack_14;
		sub_6FACC610();
	}
	if (a1 == 0x28)
	{
		puStack_14[1] = 1;
		puStack_10 = (uint32_t*)&byte_6FB6EE00;
		iStack_1c = 100;
		a1 = 0xa0;
		iVar7 = -0x51;
		iVar11 = 0x35;
		iStack_18 = 4;
		iVar10 = 5;
		uVar9 = -(uint32_t)(a2 != 1) & 0x14;
	}
	else if (a1 == 0x67)
	{
		iVar10 = 2;
		puStack_10 = nullptr;
		puStack_14[1] = 2;
		iStack_1c = 0x5a;
		a1 = 0x88;
		iVar7 = -0x32;
		iVar11 = -3;
		iStack_18 = 2;
	}
	else
	{
		D2_ASSERT(a1 == 0x6d);
		iVar10 = 3;
		puStack_10 = nullptr;
		puStack_14[1] = 3;
		iStack_1c = 0xaa;
		a1 = 0xb4;
		iVar7 = -0x9b;
		iVar11 = -0x14;
		iStack_18 = 2;
	}
	DUNGEON_GameTileToClientCoords(&a3, &a4);
	iStack_c = 0;
	a3 = a3 / 10;
	a4 = a4 / 10;
	iVar7 = (a4 - (uint32_t)(iStack_1c * iStack_18) / 2) - iVar7;
	if (iStack_18 != 0)
	{
		do
		{
			iVar12 = a3 - ((uint32_t)(a1 * iVar10) / 2 + iVar11);
			a2 = 0;
			if (iVar10 != 0)
			{
				do
				{
					puVar8 = puStack_10;
					if (puStack_10 != nullptr)
					{
						for (; *puVar8 != 0xffffffff; puVar8 = puVar8 + 1)
						{
							if (*puVar8 == uVar9)
								goto LAB_6facdb3d;
						}
					}
					D2_ASSERT(!((iVar12 < -0x8000) || (0x7fff < iVar12)));
					D2_ASSERT(!((iVar7 < -0x8000) || (0x7fff < iVar7)));
					D2_ASSERT(!(((int)uVar9 < -0x8000) || (0x7fff < (int)uVar9)));
					puVar5 = (uint32_t*)sub_6FACBA40();
					*puVar5 = 0;
					*(short*)(puVar5 + 1) = (short)uVar9;
					*(short*)((int)puVar5 + 6) = (short)iVar12;
					*(short*)(puVar5 + 2) = (short)iVar7;
					sub_6FACCD50((int)puVar5, (int*)(puStack_14 + 5));
				LAB_6facdb3d:
					uVar9 = uVar9 + 1;
					iVar12 = iVar12 + a1;
					a2 = a2 + 1;
				} while (a2 < iVar10);
			}
			iVar7 = iVar7 + iStack_1c;
			iStack_c = iStack_c + 1;
		} while (iStack_c < iStack_18);
	}
	piVar6 = (int*)ptr_6FBB19A0;
	if (iStack_8 != -1)
	{
		for (; piVar6 != nullptr; piVar6 = (int*)piVar6[6])
		{
			if (*piVar6 == iStack_8)
				goto LAB_6facdbc7;
		}
		piVar6 = (int*)D2_ALLOC(0x1c);
		piVar13 = piVar6;
		for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1)
		{
			*piVar13 = 0;
			piVar13 = piVar13 + 1;
		}
		*piVar6 = iStack_8;
		piVar6[6] = (int)ptr_6FBB19A0;
		ptr_6FBB19A0 = (uint8_t*)(piVar6);
	LAB_6facdbc7:
		if (piVar6 != gpint32_t_6FBB19A4)
		{
			sub_6FACBCD0();
			pvVar3 = ptr_6FBB1998;
			if (gpint32_t_6FBB19A4 != nullptr)
			{
				while (pvVar3 != nullptr)
				{
					pvVar2 = *(void**)((int)pvVar3 + 0x2800);
					D2_FREE(pvVar3);
					pvVar3 = pvVar2;
				}
				ptr_6FBB1998 = nullptr;
				dword_6FBB199C = 0;
				gpint32_t_6FBB19A4[2] = 0;
				gpint32_t_6FBB19A4[3] = 0;
				gpint32_t_6FBB19A4[4] = 0;
				gpint32_t_6FBB19A4[5] = 0;
			}
			gpint32_t_6FBB19A4 = piVar6;
			sub_6FACC610();
		}
	}
}

//D2Client.0x6FACDCB0
void __cdecl sub_6FACDCB0()
{
	D2UnitStrc* pDVar1;
	D2ActiveRoomStrc* pDVar2;
	int iVar3;
	Font nFontSize;
	int iVar4;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	int iStack_10;
	int iStack_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	if (ghAct != nullptr)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 != nullptr)
		{
			pDVar1 = CUNIT_GetPlayer();
			pDVar2 = UNITS_GetRoom(pDVar1);
			if (pDVar2 != nullptr)
			{
				sub_6FACB760();
				if (gpint32_t_6FBB19A4 != nullptr)
				{
					iVar4 = 0;
					iVar3 = sub_6FAB5750();
					if (iVar3 == 1)
					{
						if (dword_6FBB1990 != 1)
						{
							iVar4 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
						}
						if (dword_6FBB1A20 == 0)
						{
							dword_6FBB1A24 = 0;
							dword_6FBB1A20 = 1;
						}
					}
					else if (iVar3 == 2)
					{
						if (dword_6FBB1990 != 1)
						{
							iVar4 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
						}
						if (dword_6FBB1A20 != 0)
						{
							dword_6FBB1A24 = dword_6FBB1A20;
							dword_6FBB1A20 = 0;
						}
					}
					else
					{
						if (dword_6FBB1A20 != dword_6FBB1A24)
						{
							dword_6FBB1A20 = dword_6FBB1A24;
						}
						if (dword_6FBB1A20 != dword_6FBB1A28)
						{
							dword_6FBB1A20 = dword_6FBB1A28;
						}
					}
					iVar3 = sub_6FAB5870();
					iVar4 = (iVar3 / dword_6FB77BC0 - gnViewWidth / 2) - iVar4;
					iVar3 = sub_6FAB5880();
					byte_6FBB19D4 = iVar3 / dword_6FB77BC0 - gnViewHeight / 2;
					dword_6FBB19D8 = dword_6FBB19C8 + 0x28 + iVar4;
					dword_6FBB19DC = dword_6FBB19CC + 0xf + byte_6FBB19D4;
					if (dword_6FBB1990 == 1)
					{
						iStack_10 = dword_6FBB1A18 + -0x10;
						uStack_8 = 4;
						iStack_18 = dword_6FBB1A1C + -8;
						uStack_4 = 8;
						dword_6FB77BC0 = 0x14;
						iStack_14 = gnViewWidth / 3 + 8 + dword_6FBB1A1C;
						iStack_c = gnViewHeight / 3 + 0x10 + dword_6FBB1A18;
					}
					else
					{
						iStack_14 = gnViewWidth + 0x10;
						iStack_c = gnViewHeight + 0x20;
						iStack_18 = -0x10;
						iStack_10 = -0x20;
						uStack_8 = 8;
						uStack_4 = 0x10;
						dword_6FB77BC0 = 10;
					}
					iStack_1c = dword_6FBB19A8;
					byte_6FBB19D0 = iVar4;
					sub_6FACE230(gpint32_t_6FBB19A4[2], &iStack_1c);
					sub_6FACE230(gpint32_t_6FBB19A4[3], &iStack_1c);
					sub_6FACE230(gpint32_t_6FBB19A4[4], &iStack_1c);
					if (dword_6FBB1990 == 1)
					{
						iVar3 = gpint32_t_6FBB19A4[1];
						if (iVar3 == 1)
						{
							iStack_18 = dword_6FBB1A1C + -0xa0;
							iStack_1c = dword_6FBB19AC;
							iStack_10 = dword_6FBB1A18 + -100;
							uStack_8 = 0x50;
							uStack_4 = 0x32;
							iStack_14 = gnViewWidth / 3 + 0xa0 + dword_6FBB1A1C;
							iStack_c = gnViewHeight / 3 + 100 + dword_6FBB1A18;
						}
						else if (iVar3 == 2)
						{
							iStack_18 = dword_6FBB1A1C + -0x88;
							iStack_1c = dword_6FBB19B0;
							iStack_10 = dword_6FBB1A18 + -0x5a;
							uStack_8 = 0x44;
							uStack_4 = 0x2d;
							iStack_14 = gnViewWidth / 3 + 0x88 + dword_6FBB1A1C;
							iStack_c = gnViewHeight / 3 + 0x5a + dword_6FBB1A18;
						}
						else if (iVar3 == 3)
						{
							iStack_18 = dword_6FBB1A1C + -0xb4;
							iStack_1c = dword_6FBB19B4;
							iStack_10 = dword_6FBB1A18 + -0xaa;
							uStack_8 = 0x5a;
							uStack_4 = 0x55;
							iStack_14 = gnViewWidth / 3 + 0xb4 + dword_6FBB1A1C;
							iStack_c = gnViewHeight / 3 + 0xaa + dword_6FBB1A18;
						}
						else
						{
							iStack_18 = dword_6FBB1A1C + -8;
							iStack_1c = dword_6FBB19A8;
							iStack_10 = dword_6FBB1A18 + -0x10;
							uStack_8 = 4;
							uStack_4 = 8;
							iStack_14 = gnViewWidth / 3 + 8 + dword_6FBB1A1C;
							iStack_c = gnViewHeight / 3 + 0x10 + dword_6FBB1A18;
						}
						dword_6FB77BC0 = 0x14;
					}
					else
					{
						iVar3 = gpint32_t_6FBB19A4[1];
						if (iVar3 == 1)
						{
							iStack_14 = gnViewWidth + 0xa0;
							iStack_18 = -0xa0;
							iStack_10 = -100;
							iStack_c = gnViewHeight + 100;
							uStack_8 = 0x50;
							uStack_4 = 0x32;
							iStack_1c = dword_6FBB19AC;
						}
						else if (iVar3 == 2)
						{
							iStack_14 = gnViewWidth + 0x88;
							iStack_18 = -0x88;
							iStack_10 = -0x5a;
							iStack_c = gnViewHeight + 0x5a;
							uStack_8 = 0x44;
							uStack_4 = 0x2d;
							iStack_1c = dword_6FBB19B0;
						}
						else if (iVar3 == 3)
						{
							iStack_14 = gnViewWidth + 0xb4;
							iStack_18 = -0xb4;
							iStack_10 = -0xaa;
							iStack_c = gnViewHeight + 0xaa;
							uStack_8 = 0x5a;
							uStack_4 = 0x55;
							iStack_1c = dword_6FBB19B4;
						}
						else
						{
							iStack_14 = gnViewWidth + 0x10;
							iStack_18 = -0x10;
							iStack_10 = -0x20;
							iStack_c = gnViewHeight + 0x20;
							uStack_8 = 8;
							uStack_4 = 0x10;
							iStack_1c = dword_6FBB19A8;
						}
						dword_6FB77BC0 = 10;
					}
					sub_6FACE230(gpint32_t_6FBB19A4[5], &iStack_1c);
				}
				sub_6FACE510();
				dword_6FBB19FC = 0x18;
				iVar3 = sub_6FAABFF0();
				nFontSize = D2Win_10127_SetFont(D2FONT_FONT16);
				sub_6FACEF10();
				sub_6FACF0D0();
				sub_6FACF120();
				sub_6FACF290();
				if ((iVar3 == 6) || (iVar3 == 8))
				{
					sub_6FACF210();
				}
				iVar3 = sub_6FAAC080();
				if (iVar3 != 0)
				{
					sub_6FACF060();
				}
				D2Win_10127_SetFont(nFontSize);
			}
		}
	}
}

//D2Client.0x6FACE230
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FACE230(int a1, int* a2)
{
	bool bVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t extraout_var;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	int nXPos;
	D2GfxDataStrc* pDVar9;
	DrawMode local_6c;
	int local_68;
	int local_58;
	int local_54;
	int local_50;
	int local_4c;
	D2GfxDataStrc local_48;

	local_68 = a1;
	if (a1 == 0)
	{
		return;
	}
	do
	{
		iVar7 = 0;
		iVar2 = sub_6FAB5750();
		if (iVar2 == 1)
		{
			iVar7 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
		}
		else if (iVar2 == 2)
		{
			iVar7 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
		}
		nXPos = (*(short*)(local_68 + 6) * 10) / dword_6FB77BC0 - dword_6FBB19D8;
		iVar2 = (*(short*)(local_68 + 8) * 10) / dword_6FB77BC0 - dword_6FBB19DC;
		if ((a2[3] <= iVar2) &&
		    (sub_6FACE230(*(int*)(local_68 + 0xc), a2), a2[3] <= iVar2))
		{
			if (a2[4] < iVar2)
			{
				return;
			}
			if ((a2[1] <= nXPos) && (nXPos <= a2[2]))
			{
				local_6c = DRAWMODE_NORMAL;
				pDVar9 = &local_48;
				for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					pDVar9->pCurrentCell = nullptr;
					pDVar9 = (D2GfxDataStrc*)&pDVar9->pCellFile;
				}
				local_48.pCellFile = (D2CellFileStrc*)*a2;
				local_48.nFrame = (uint32_t) * (short*)(local_68 + 4);
				local_48.nDirection = 0;
				if ((dword_6FBB1990 == 1) && (dword_6FBB19E8 == 1))
				{
					dword_6FBB19E8 = (-(uint32_t)(dword_6FBB19EC != 0) & 0xfffffffe) + 2;
				}
				if (dword_6FBB19E8 == 1)
				{
					if ((*a2 == dword_6FBB19A8) && (dword_6FBB1990 == 0))
					{
						iVar6 = a2[5] + nXPos;
						iVar5 = a2[6] + iVar2;
						iVar4 = gnViewWidth / 2;
						iVar8 = gnViewHeight / 2;
						if ((iVar4 + -0x8c + iVar7 <= iVar6) &&
						    (((iVar6 <= iVar4 + 0x8c + iVar7 && (iVar8 + -0x96 <= iVar5)) &&
						        (iVar5 <= iVar8 + 0x82))))
						{
							iVar7 = (iVar4 - iVar6) + iVar7;
							if (iVar7 < 0)
							{
								iVar7 = -iVar7;
							}
							iVar5 = (iVar8 + -10) - iVar5;
							if (iVar5 < 0)
							{
								iVar5 = -iVar5;
							}
							if (iVar5 < iVar7)
							{
								iVar5 = iVar5 + iVar7 * 2;
							}
							else
							{
								iVar5 = iVar7 + iVar5 * 2;
							}
							iVar5 = iVar5 / 2;
							if (((iVar5 < 0x96) && (local_6c = DRAWMODE_TRANS75, iVar5 < 100)) &&
							    (local_6c = DRAWMODE_TRANS50, iVar5 < 0x32))
							{
								local_6c = DRAWMODE_TRANS25;
							}
						}
					}
				}
				else if (dword_6FBB19E8 == 2)
				{
				LAB_6face38f:
					local_6c = DRAWMODE_TRANS50;
				}
				else if (dword_6FBB19E8 == 3)
				{
					pDVar3 = CUNIT_GetPlayer();
					if ((pDVar3->nAct == 0) || (pDVar3->nAct == 2))
					{
						if (dword_6FBB1990 == 1)
							goto LAB_6face38f;
						local_6c = DRAWMODE_TRANS75;
					}
				}
				if (dword_6FBB1990 == 1)
				{
					if (dword_6FBB1A20 == 0)
					{
						local_58 = gnScreenWidth + -0x119;
						local_50 = 0x39;
					}
					else
					{
						local_58 = 0;
						bVar1 = sub_6FADA710();
						local_50 = (-(uint32_t)(D2C_ZEXT(bVar1) != 0) & 0x60) - 0x15;
					}
					local_54 = local_58 + 0x117;
					local_4c = local_50 + 0xe1;
				}
				else
				{
					local_54 = gnScreenWidth + -1;
					local_4c = gnScreenHeight + -1;
					local_58 = 0;
					local_50 = 0;
				}
				TEXTURE_CelDrawClipped(&local_48, nXPos, iVar2, &local_58, local_6c);
			}
		}
		if (a2[4] < iVar2)
		{
			return;
		}
		local_68 = *(int*)(local_68 + 0x10);
		if (local_68 == 0)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FACE510
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FACE510()
{
	short sVar1;
	short sVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	D2ActiveRoomStrc* pRoom;
	int iVar5;
	Unicode* pUVar6;
	D2UnitStrc* pDVar7;
	D2UnitStrc* pDVar8;
	uint16_t extraout_var;
	D2PlayerDataStrc* pDVar9;
	uint32_t uVar10;
	int iVar11;
	int nColor;
	int iVar12;
	int bCentered;
	uint32_t uVar13;
	D2ActiveRoomStrc*** pppRoomList;
	int* pNumRooms;
	uint32_t uStack_28;
	int local_24;
	D2ActiveRoomStrc** local_20;
	Font FStack_1c;
	int iStack_18;
	uint32_t uStack_14;
	int iStack_10;
	uint32_t uStack_c;
	int iStack_8;
	int local_4;

	iVar3 = sub_6FAAF5B0(0);
	local_4 = iVar3;
	pDVar4 = CUNIT_GetPlayer();
	pNumRooms = &local_24;
	pppRoomList = &local_20;
	local_20 = nullptr;
	local_24 = 0;
	pRoom = UNITS_GetRoom(pDVar4);
	DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, pppRoomList, pNumRooms);
	iStack_18 = 0;
	iStack_8 = local_24;
	if (0 < local_24)
	{
		do
		{
			iVar3 = local_4;
			for (pDVar4 = local_20[iStack_18]->pUnitFirst; local_4 = iVar3, pDVar4 != nullptr;
			     pDVar4 = pDVar4->pRoomNext)
			{
				uVar10 = 6;
				if (pDVar4 != nullptr)
				{
					uVar10 = pDVar4->dwUnitType;
				}
				uStack_28 = uStack_28 & 0xffffff00;
				if ((((uVar10 != 0) || (iVar3 = sub_6FB29550((int*)pDVar4), iVar3 == 0)) ||
				        (iVar3 = STATES_CheckState(pDVar4, 7), iVar3 != 0)) &&
				    (iVar3 = sub_6FACE8F0(pDVar4, (uint8_t*)&uStack_28), iVar3 != 0))
				{
					iVar3 = UNITS_GetClientCoordX(pDVar4);
					iVar5 = UNITS_GetClientCoordY(pDVar4);
					iVar11 = (iVar3 / dword_6FB77BC0 - dword_6FBB19D8) + 8;
					iVar3 = iVar5 / dword_6FB77BC0 - dword_6FBB19DC;
					iVar5 = iVar3 + -8;
					if (((dword_6FBB1A08 <= iVar11) && (iVar11 <= dword_6FBB1A10)) &&
					    ((dword_6FBB1A0C <= iVar5 && (iVar5 <= dword_6FBB1A14))))
					{
						if (uVar10 == 0)
						{
							if ((dword_6FB77BC8 != 0) || ((uint8_t)uStack_28 != byte_6FBB19F3))
							{
								sub_6FACECF0(iVar11, iVar5, uStack_28);
							}
							if (((dword_6FB77BCC != 0) && (dword_6FB77BC8 != 0)) &&
							    (pDVar7 = CUNIT_GetPlayer(), pDVar4 != pDVar7))
							{
								pDVar7 = pDVar4;
								if ((uint8_t)uStack_28 == byte_6FBB19F3)
								{
									if (dword_6FB77BC8 == 0)
										goto LAB_6face865;
									uVar13 = 2;
								}
								else
								{
									uVar13 = 1;
								}
							LAB_6face857:
								pDVar9 = UNITS_GetPlayerData(pDVar7);
								sub_6FACEC40(pDVar9, iVar11, iVar5, uVar13);
							}
						}
						else if (uVar10 == 1)
						{
							sub_6FACECF0(iVar11, iVar5, uStack_28);
							if (dword_6FB77BCC != 0)
							{
								if (pDVar4 == nullptr)
								{
									iVar12 = -1;
								}
								else
								{
									iVar12 = pDVar4->dwClassId;
								}
								iVar12 = sub_6FAAE570(iVar12);
								if ((iVar12 != 0) &&
								    (uStack_c = (uint32_t) * (uint8_t*)(iVar12 + 0xd) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4),
								        uStack_c != 0))
								{
									FStack_1c = D2Win_10127_SetFont(D2FONT_FONT6);
									pUVar6 = sub_6FB297F0(pDVar4);
									iVar3 = iVar3 + -0x12;
									bCentered = 0;
									nColor = 4;
									iVar12 = D2Win_10121_GetTextWidth(pUVar6);
									D2Win_10117_DrawText(pUVar6, iVar11 - iVar12 / 2, iVar3, nColor, bCentered);
									D2Win_10127_SetFont(FStack_1c);
								}
								if ((dword_6FB77BCC != 0) && (dword_6FB77BC8 != 0))
								{
									FStack_1c = D2FONT_FONT6;
									if (pDVar4 == nullptr)
									{
										iStack_10 = -1;
										uStack_14 = 0;
									}
									else
									{
										FStack_1c = (Font)(pDVar4->dwUnitType);
										iStack_10 = pDVar4->dwClassId;
										uStack_14 = pDVar4->dwAnimMode;
									}
									D2COMMON_11013_ConvertMode(pDVar4, (int*)&FStack_1c, &iStack_10, (int*)&uStack_14,
									    __FILE__, __LINE__);
									if ((((FStack_1c == D2FONT_FONT8) &&
									         (iVar3 = STATES_CheckStateMaskOnUnit(pDVar4, 0x25), iVar3 != 0)) &&
									        (pDVar7 = sub_6FB26AD0((int)pDVar4), pDVar7 != nullptr)) &&
									    (pDVar7->dwUnitType == 0))
									{
										pDVar8 = CUNIT_GetPlayer();
										sVar1 = sub_6FB2A6E0((int*)pDVar8);
										uStack_c = D2C_ZEXT(sVar1);
										if (sVar1 != -1)
										{
											sVar1 = sub_6FB2A6E0((int*)pDVar4);
											if ((short)uStack_c == sVar1)
												goto LAB_6face865;
										}
										uVar13 = 1;
										goto LAB_6face857;
									}
								}
							}
						}
						else if (uVar10 == 2)
						{
							if (((dword_6FB77BCC == 0) || (pDVar4 == nullptr)) ||
							    (pDVar4->dwClassId != 0x10b))
							{
								sub_6FACECF0(iVar11, iVar5, uStack_28);
							}
							else
							{
								FStack_1c = D2Win_10127_SetFont(D2FONT_FONT6);
								pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xcf3));
								uVar10 = uStack_28 & 0xff;
								iVar12 = 0;
								iVar3 = iVar3 + -0x12;
								iVar5 = D2Win_10121_GetTextWidth(pUVar6);
								D2Win_10117_DrawText(pUVar6, iVar11 - iVar5 / 2, iVar3, uVar10, iVar12);
								D2Win_10127_SetFont(FStack_1c);
							}
						}
					}
				}
			LAB_6face865:
				iVar3 = local_4;
			}
			iStack_18 = iStack_18 + 1;
		} while (iStack_18 < iStack_8);
	}
	sVar1 = sub_6FAAFDA0(iVar3);
	if ((sVar1 != -1) && (dword_6FB77BC8 != 0))
	{
		for (iVar3 = sub_6FAAF5B0(iVar3); iVar3 != 0; iVar3 = sub_6FAAF5B0(iVar3))
		{
			uVar10 = sub_6FAB0870(iVar3);
			pDVar4 = sub_6FB269F0(uVar10, 0);
			if ((pDVar4 == nullptr) && (sVar2 = sub_6FAAFDA0(iVar3), sVar1 == sVar2))
			{
				sub_6FACED50(iVar3);
			}
		}
	}
}

//D2Client.0x6FACE8F0
uint32_t __fastcall sub_6FACE8F0(D2UnitStrc* pUnit, uint8_t* a2)
{
	int iVar1;
	short sVar2;
	short sVar3;
	uint32_t uVar4;
	int iVar5;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar6;
	uint32_t uVar7;
	uint32_t local_c;
	uint32_t local_8;
	int local_4;

	uVar4 = 6;
	if (pUnit != nullptr)
	{
		uVar4 = pUnit->dwUnitType;
	}
	if (uVar4 == 0)
	{
		if ((pUnit != nullptr) && (pUnit->dwAnimMode == 0x11))
		{
			if (pUnit->pInventory == nullptr)
			{
				return 0;
			}
			uVar4 = INVENTORY_GetOwnerId(pUnit->pInventory);
			if (uVar4 != pUnit->dwUnitId)
			{
				return 0;
			}
			*a2 = byte_6FBB19F2;
			return 1;
		}
		pDVar6 = CUNIT_GetPlayer();
		if (pUnit == pDVar6)
		{
			*a2 = byte_6FBB19F0;
			return 1;
		}
		pDVar6 = CUNIT_GetPlayer();
		sVar2 = sub_6FB2A6E0((int*)pDVar6);
		if ((sVar2 != -1) && (sVar3 = sub_6FB2A6E0((int*)pUnit), sVar2 == sVar3))
		{
			*a2 = byte_6FBB19F3;
			return 1;
		}
		*a2 = byte_6FBB19F1;
	}
	else
	{
		if (uVar4 != 1)
		{
			if (uVar4 != 2)
			{
				return 0;
			}
			if (pUnit == nullptr)
			{
				iVar5 = -1;
			}
			else
			{
				iVar5 = pUnit->dwClassId;
			}
			if (iVar5 == 0x3b)
			{
				*a2 = byte_6FBB19F8;
				return 1;
			}
			if (iVar5 != 0x3c)
			{
				if (iVar5 != 0x10b)
				{
					return 0;
				}
				*a2 = 0;
				return 1;
			}
			pRoom = UNITS_GetRoom(pUnit);
			iVar5 = DUNGEON_GetLevelIdFromRoom(pRoom);
			if (iVar5 == 0x7d)
			{
				return 0;
			}
			if (iVar5 == 0x7e)
			{
				return 0;
			}
			if (iVar5 == 0x7f)
			{
				return 0;
			}
			if (iVar5 == 0x6f)
			{
				return 0;
			}
			if (iVar5 == 0x70)
			{
				return 0;
			}
			if (iVar5 == 0x75)
			{
				return 0;
			}
			*a2 = byte_6FBB19F8;
			return 1;
		}
		if (pUnit == nullptr)
		{
			local_c = 6;
		}
		else
		{
			if (pUnit->dwAnimMode == 0xc)
			{
				return 0;
			}
			if ((pUnit->dwFlags >> 0x15 & 1) != 0)
			{
				return 0;
			}
			iVar5 = pUnit->dwClassId;
			if ((((-1 < iVar5) && (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
			        (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar5 * 0x1a8, iVar1 != 0)) &&
			    (((uint32_t) * (uint8_t*)(iVar1 + 0xd) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4)) != 0))
			{
				if (iVar5 == 0x219)
				{
					return 0;
				}
				if (iVar5 == 0x21a)
				{
					return 0;
				}
				if (iVar5 == 0x21b)
				{
					return 0;
				}
				*a2 = byte_6FBB19F6;
				return 1;
			}
			local_c = pUnit->dwUnitType;
		}
		if (pUnit == nullptr)
		{
			local_4 = -1;
			local_8 = 0;
		}
		else
		{
			local_4 = pUnit->dwClassId;
			local_8 = pUnit->dwAnimMode;
		}
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_4, (int*)&local_8,
		    __FILE__, __LINE__);
		if (((local_c == 0) && (iVar5 = STATES_CheckStateMaskOnUnit(pUnit, 0x25), iVar5 != 0)) &&
		    (pDVar6 = sub_6FB26AD0((int)pUnit), pDVar6 != nullptr))
		{
			pDVar6 = CUNIT_GetPlayer();
			sVar2 = sub_6FB2A6E0((int*)pDVar6);
			if ((sVar2 != -1) && (sVar3 = sub_6FB2A6E0((int*)pUnit), sVar2 == sVar3))
			{
				*a2 = byte_6FBB19F4;
				return 1;
			}
			*a2 = byte_6FBB19F1;
			return 1;
		}
		if (pUnit == nullptr)
		{
			uVar4 = 0xffffffff;
		}
		else
		{
			uVar4 = pUnit->dwUnitId;
		}
		uVar7 = sub_6FAB1810(uVar4);
		switch (uVar7)
		{
		case 0:
		case 3:
			return 0;
		case 1:
			if ((pUnit != nullptr) && ((pUnit->dwFlags >> 9 & 1) != 0))
			{
				*a2 = byte_6FBB19F4;
				return 1;
			}
			*a2 = byte_6FBB19F4;
			return 1;
		case 2:
			if (dword_6FB77BC8 == 0)
			{
				return 0;
			}
			*a2 = byte_6FBB19F5;
			return 1;
		}
	}
	return 1;
}

//D2Client.0x6FACEC40
void __fastcall sub_6FACEC40(D2PlayerDataStrc* pPlayerData, int a2, uint32_t a3, uint32_t a4)
{
	char* pcVar1;
	Font nFontSize;
	uint32_t nColor;
	int iVar2;
	int nY;
	Unicode* pUVar3;
	D2PlayerDataStrc* pDVar4;
	int bCentered;
	Unicode aUStack_30[24];

	iVar2 = -1;
	pDVar4 = pPlayerData;
	do
	{
		if (iVar2 == 0)
			break;
		iVar2 = iVar2 + -1;
		pcVar1 = pDVar4->szName;
		pDVar4 = (D2PlayerDataStrc*)(pDVar4->szName + 1);
	} while (*pcVar1 != '\0');
	if (iVar2 != -2)
	{
		if (0xc < (uint8_t)a4)
		{
			(*(uint8_t*)((uint8_t*)&a4 + 0)) = 0;
		}
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
		pUVar3 = aUStack_30;
		for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*(uint32_t*)pUVar3 = 0;
			pUVar3 = pUVar3 + 2;
		}
		pUVar3->ch = 0;
		Unicode::toUnicode(aUStack_30, pPlayerData->szName, 0x17);
		nColor = (uint32_t)(uint8_t)a4;
		bCentered = 0;
		nY = a3 - 10;
		iVar2 = D2Win_10121_GetTextWidth(aUStack_30);
		D2Win_10117_DrawText(aUStack_30, a2 - iVar2 / 2, nY, nColor, bCentered);
		D2Win_10127_SetFont(nFontSize);
	}
}

//D2Client.0x6FACECF0
void __fastcall sub_6FACECF0(int a1, int a2, uint32_t a3)
{
	uint32_t uVar1;

	if (dword_6FBB1990 == 1)
	{
		a1 = a1 + -1;
		a2 = a2 + 5;
	}
	uVar1 = 0;
	do
	{
		D2GFX_DrawLine(a1 + *(int*)((int)&dword_6FB6EE30 + uVar1) * 2,
		    a2 + *(int*)((int)&dword_6FB6EE34 + uVar1) * 2,
		    a1 + *(int*)((int)&dword_6FB6EE38 + uVar1) * 2,
		    a2 + *(int*)((int)&dword_6FB6EE3C + uVar1) * 2, (uint8_t)a3, 0xff);
		uVar1 = uVar1 + 8;
	} while (uVar1 < 0x60);
}

//D2Client.0x6FACED50
void __fastcall sub_6FACED50(int a1)
{
	char cVar1;
	uint8_t bVar2;
	uint8_t bVar3;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int iVar4;
	int iVar5;
	char* a2;
	Font nFontSize;
	uint32_t uVar6;
	Unicode* pUVar7;
	char* pcVar8;
	int nColor;
	int bCentered;
	int local_40;
	int local_3c;
	int iStack_38;
	int iStack_34;
	Unicode aUStack_30[24];

	local_3c = 0;
	local_40 = 0;
	pUnit = CUNIT_GetPlayer();
	pRoom = UNITS_GetRoom(pUnit);
	iVar4 = DUNGEON_GetLevelIdFromRoom(pRoom);
	iVar5 = sub_6FAB0BB0(a1);
	bVar2 = DRLG_GetActNoFromLevelId(iVar5);
	bVar3 = DRLG_GetActNoFromLevelId(iVar4);
	if (bVar3 == bVar2)
	{
		sub_6FAB0B80(a1, (uint32_t*)(&local_3c), (uint32_t*)(&local_40));
		DUNGEON_GameSubtileToClientCoords(&local_3c, &local_40);
		local_3c = (local_3c / dword_6FB77BC0 - dword_6FBB19D8) + 8;
		local_40 = (local_40 / dword_6FB77BC0 - dword_6FBB19DC) + -8;
		if ((((dword_6FBB1A08 <= local_3c) && (local_3c <= dword_6FBB1A10)) && (dword_6FBB1A0C <= local_40)) && (local_40 <= dword_6FBB1A14))
		{
			uVar6 = 0;
			do
			{
				D2GFX_DrawLine(local_3c + *(int*)((int)&dword_6FB6EE30 + uVar6) * 2,
				    local_40 + *(int*)((int)&dword_6FB6EE34 + uVar6) * 2,
				    local_3c + *(int*)((int)&dword_6FB6EE38 + uVar6) * 2,
				    local_40 + *(int*)((int)&dword_6FB6EE3C + uVar6) * 2, byte_6FBB19F3, 0xff);
				uVar6 = uVar6 + 8;
			} while (uVar6 < 0x60);
			if (dword_6FB77BCC != 0)
			{
				iStack_38 = local_40;
				iStack_34 = local_3c;
				a2 = (char*)sub_6FAAF5D0(a1);
				iVar4 = -1;
				pcVar8 = a2;
				do
				{
					if (iVar4 == 0)
						break;
					iVar4 = iVar4 + -1;
					cVar1 = *pcVar8;
					pcVar8 = pcVar8 + 1;
				} while (cVar1 != '\0');
				if (iVar4 != -2)
				{
					nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
					pUVar7 = aUStack_30;
					for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1)
					{
						*(uint32_t*)pUVar7 = 0;
						pUVar7 = pUVar7 + 2;
					}
					pUVar7->ch = 0;
					Unicode::toUnicode(aUStack_30, a2, 0x17);
					bCentered = 0;
					iVar4 = iStack_38 + -10;
					nColor = 2;
					iVar5 = D2Win_10121_GetTextWidth(aUStack_30);
					D2Win_10117_DrawText(aUStack_30, iStack_34 - iVar5 / 2, iVar4, nColor, bCentered);
					D2Win_10127_SetFont(nFontSize);
				}
			}
		}
	}
}

//D2Client.0x6FACEF10
void __cdecl sub_6FACEF10()
{
	char* pcVar1;
	char* pcVar2;
	Unicode* pUVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	char acStack_b4[28];
	Unicode local_98[26];
	Unicode aUStack_64[50];

	pcVar1 = (char*)(CLIENT_GetGameName());
	pcVar2 = (char*)(CLIENT_GetServerIP());
	if (pcVar1 == nullptr)
	{
		if (pcVar2 == nullptr)
		{
			return;
		}
	}
	else
	{
		sprintf(acStack_b4, "%s", pcVar1);
		Unicode::toUnicode(local_98, acStack_b4, 0x19);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1055));
		Unicode::strcpy(aUStack_64, pUVar3);
		Unicode::strcat(aUStack_64, local_98);
		iVar7 = 0;
		iVar6 = 4;
		iVar5 = dword_6FBB19FC;
		iVar4 = D2Win_10121_GetTextWidth(aUStack_64);
		D2Win_10117_DrawText(aUStack_64, (gnViewWidth - iVar4) + -0x10, iVar5, iVar6, iVar7);
		dword_6FBB19FC = dword_6FBB19FC + 0x10;
	}
	pcVar1 = (char*)(CLIENT_GetGamePassword());
	if (pcVar1 != nullptr)
	{
		sprintf(acStack_b4, "%s", pcVar1);
		Unicode::toUnicode(local_98, acStack_b4, 0x19);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1056));
		Unicode::strcpy(aUStack_64, pUVar3);
		Unicode::strcat(aUStack_64, local_98);
		iVar7 = 0;
		iVar6 = 4;
		iVar5 = dword_6FBB19FC;
		iVar4 = D2Win_10121_GetTextWidth(aUStack_64);
		D2Win_10117_DrawText(aUStack_64, (gnViewWidth - iVar4) + -0x10, iVar5, iVar6, iVar7);
		dword_6FBB19FC = dword_6FBB19FC + 0x10;
	}
}

//D2Client.0x6FACF060
void __cdecl sub_6FACF060()
{
	Unicode* pUVar1;
	int iVar2;
	int iVar3;
	int nColor;
	int bCentered;
	Unicode local_64[50];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x58ca));
	Unicode::strcpy(local_64, pUVar1);
	bCentered = 0;
	nColor = 4;
	iVar3 = dword_6FBB19FC;
	iVar2 = D2Win_10121_GetTextWidth(local_64);
	D2Win_10117_DrawText(local_64, (gnViewWidth - iVar2) + -0x10, iVar3, nColor, bCentered);
	dword_6FBB19FC = dword_6FBB19FC + 0x10;
}

//D2Client.0x6FACF0D0
void __cdecl sub_6FACF0D0()
{
	D2ActiveRoomStrc* pRoom;
	int iVar1;
	Unicode* wszText;
	int iVar2;
	int nColor;
	int bCentered;

	pRoom = CUNIT_GetPlayerRoom();
	if (pRoom != nullptr)
	{
		iVar1 = DUNGEON_GetLevelIdFromRoom(pRoom);
		wszText = sub_6FB239F0(iVar1);
		bCentered = 0;
		nColor = 4;
		iVar1 = dword_6FBB19FC;
		iVar2 = D2Win_10121_GetTextWidth(wszText);
		D2Win_10117_DrawText(wszText, (gnViewWidth - iVar2) + -0x10, iVar1, nColor, bCentered);
		dword_6FBB19FC = dword_6FBB19FC + 0x10;
	}
}

//D2Client.0x6FACF120
void __cdecl sub_6FACF120()
{
	char cVar1;
	int iVar2;
	Unicode* pThis;
	int iVar3;
	char acStack_12c[100];
	Unicode local_c8[100];

	iVar3 = sub_6FAAB360();
	if (iVar3 != 0)
	{
		iVar3 = sub_6FAAB360();
		iVar3 = (**(code**)(iVar3 + 0x5c))();
		if (*(char*)(gpConfig + 0x21e) == '\0')
		{
			sprintf(acStack_12c, "v %d.%02d", iVar3 / 100 + 1, iVar3 % 100);
		}
		else
		{
			iVar2 = sub_6FAAB360();
			cVar1 = (**(code**)(iVar2 + 0xb0))();
			sprintf(acStack_12c, "v %d.%02d %d", iVar3 / 100 + 1, iVar3 % 100, (int)cVar1);
		}
		Unicode::toUnicode(local_c8, acStack_12c, 100);
		iVar3 = D2Win_10121_GetTextWidth(local_c8);
		D2Win_10117_DrawText(local_c8, (gnViewWidth - iVar3) + -0x10, dword_6FBB19FC, 4, 0);
	}
	dword_6FBB19FC = dword_6FBB19FC + 0x10;
}

//D2Client.0x6FACF210
void __cdecl sub_6FACF210()
{
	char* a2;
	int iVar1;
	Unicode* pThis;
	int iVar2;
	int nColor;
	int bCentered;
	Unicode local_258[300];

	iVar2 = 300;
	a2 = (char*)(FOG_GetHostIPAddress());
	Unicode::toUnicode(local_258, a2, iVar2);
	bCentered = 0;
	nColor = 4;
	iVar2 = dword_6FBB19FC;
	iVar1 = D2Win_10121_GetTextWidth(local_258);
	D2Win_10117_DrawText(local_258, (gnViewWidth - iVar1) + -0x10, iVar2, nColor, bCentered);
	dword_6FBB19FC = dword_6FBB19FC + 0x10;
}

//D2Client.0x6FACF290
void __cdecl sub_6FACF290()
{
	char cVar1;
	Unicode* pUVar2;
	int iVar3;
	Unicode* a3;
	short index;
	int iVar4;
	int nColor;
	int bCentered;
	Unicode local_258[300];

	cVar1 = sub_6FAAC090();
	if (cVar1 == '\x01')
	{
		index = 0x1423;
	}
	else
	{
		if (cVar1 != '\x02')
		{
			return;
		}
		index = 0x1422;
	}
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	iVar4 = Unicode::strlen(pUVar2);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1057));
	iVar3 = Unicode::strlen(pUVar2);
	if (iVar4 + 3 + iVar3 < 300)
	{
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		a3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1057));
		Unicode::sprintf(300, local_258, a3, pUVar2);
		bCentered = 0;
		nColor = 4;
		iVar4 = dword_6FBB19FC;
		iVar3 = D2Win_10121_GetTextWidth(local_258);
		D2Win_10117_DrawText(local_258, (gnViewWidth - iVar3) + -0x10, iVar4, nColor, bCentered);
		dword_6FBB19FC = dword_6FBB19FC + 0x10;
		return;
	}
	FOG_DisplayAssert("Unicode::strlen(StrGetStringByIndex(strautomapdif)) + Unicode::strlen(StrGetStringByIndex(wStringId)) + 3 < AUTOMAP_LOCAL_BUFFER_MAX",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FACF380
void __cdecl sub_6FACF380()
{
	int* piVar1;
	int* piVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_4;

	local_4 = 0;
	sub_6FACF490();
	puVar4 = &dword_6FBAF990;
	for (iVar3 = 0x800; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar4 = 0xffffffff;
		puVar4 = puVar4 + 1;
	}
	piVar2 = (int*)(&dword_6FB77A38);
	do
	{
		iVar3 = *piVar2;
		piVar1 = piVar2 + 1;
		piVar2 = piVar2 + 2;
		(&dword_6FBAF990)[iVar3] = *piVar1;
	} while ((int)piVar2 < (int)&dword_6FB77BC0);
	local_4 = 0;
	SRegLoadValue("Diablo II", "AutoMapFade", 0, (DWORD*)(&local_4));
	dword_6FBB19E8 = local_4;
	local_4 = 1;
	SRegLoadValue("Diablo II", "AutoMap Centers", 0, (DWORD*)(&local_4));
	dword_6FB77BC4 = local_4;
	local_4 = 1;
	SRegLoadValue("Diablo II", "AutoMap Party", 0, (DWORD*)(&local_4));
	dword_6FB77BC8 = local_4;
	local_4 = 1;
	SRegLoadValue("Diablo II", "AutoMap Party Names", 0, (DWORD*)(&local_4));
	dword_6FB77BCC = local_4;
	local_4 = 1;
	SRegLoadValue("Diablo II", "AutoMap Left", 0, (DWORD*)(&local_4));
	dword_6FBB1A20 = local_4;
	dword_6FBB1A24 = local_4;
	dword_6FBB1A28 = local_4;
}

//D2Client.0x6FACF490
void __cdecl sub_6FACF490()
{
	int iVar1;
	int* piVar2;
	uint32_t* puVar3;
	char* p2;
	char local_104;
	uint32_t local_103;

	local_104 = byte_6FB9A828;
	piVar2 = &dword_6FBB19A8;
	puVar3 = &local_103;
	for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	*(uint16_t*)puVar3 = 0;
	*(uint8_t*)((int)puVar3 + 2) = 0;
	do
	{
		if ((D2CellFileStrc*)*piVar2 != nullptr)
		{
			CLIENT_FreeCellFile((D2CellFileStrc*)*piVar2);
		}
		*piVar2 = 0;
		piVar2 = piVar2 + 1;
	} while ((int)piVar2 < (int)&dword_6FBB19B8);
	if (dword_6FBB1990 == 1)
	{
		sprintf(&local_104, "%s\\UI\\AutoMap\\MaxiMapS", "DATA\\GLOBAL");
		dword_6FBB19A8 = (int)CLIENT_LoadCellFile(&local_104, 0);
		dword_6FBB19B8 = D2CMP_CelFileGetCelsPerDirection((D2CellFileStrc*)dword_6FBB19A8);
		sprintf(&local_104, "%s\\UI\\AutoMap\\Act2MapS", "DATA\\GLOBAL");
		dword_6FBB19AC = (int)CLIENT_LoadCellFile(&local_104, 0);
		byte_6FBB19BC = D2CMP_CelFileGetCelsPerDirection((D2CellFileStrc*)dword_6FBB19AC);
		sprintf(&local_104, "%s\\UI\\AutoMap\\Act4MapS", "DATA\\GLOBAL");
		dword_6FBB19B0 = (int)CLIENT_LoadCellFile(&local_104, 0);
		byte_6FBB19C0 = D2CMP_CelFileGetCelsPerDirection((D2CellFileStrc*)dword_6FBB19B0);
		p2 = "%s\\UI\\AutoMap\\ExTnMapS";
	}
	else
	{
		sprintf(&local_104, "%s\\UI\\AutoMap\\MaxiMap", "DATA\\GLOBAL");
		dword_6FBB19A8 = (int)CLIENT_LoadCellFile(&local_104, 0);
		dword_6FBB19B8 = D2CMP_CelFileGetCelsPerDirection((D2CellFileStrc*)dword_6FBB19A8);
		sprintf(&local_104, "%s\\UI\\AutoMap\\Act2Map", "DATA\\GLOBAL");
		dword_6FBB19AC = (int)CLIENT_LoadCellFile(&local_104, 0);
		byte_6FBB19BC = D2CMP_CelFileGetCelsPerDirection((D2CellFileStrc*)dword_6FBB19AC);
		sprintf(&local_104, "%s\\UI\\AutoMap\\Act4Map", "DATA\\GLOBAL");
		dword_6FBB19B0 = (int)CLIENT_LoadCellFile(&local_104, 0);
		byte_6FBB19C0 = D2CMP_CelFileGetCelsPerDirection((D2CellFileStrc*)dword_6FBB19B0);
		iVar1 = FOG_IsExpansion();
		if (iVar1 == 0)
		{
			dword_6FBB19B4 = 0;
			byte_6FBB19C4 = 0;
			return;
		}
		p2 = "%s\\UI\\AutoMap\\ExTnMap";
	}
	sprintf(&local_104, p2, "DATA\\GLOBAL");
	dword_6FBB19B4 = (int)CLIENT_LoadCellFile(&local_104, 0);
	byte_6FBB19C4 = D2CMP_CelFileGetCelsPerDirection((D2CellFileStrc*)dword_6FBB19B4);
}

//D2Client.0x6FACF670
void __cdecl sub_6FACF670()
{
	void* pvVar1;
	void* pvVar2;
	int* piVar3;

	sub_6FACBCD0();
	pvVar2 = ptr_6FBB1998;
	if (gpint32_t_6FBB19A4 != nullptr)
	{
		while (pvVar2 != nullptr)
		{
			pvVar1 = *(void**)((int)pvVar2 + 0x2800);
			D2_FREE(pvVar2);
			pvVar2 = pvVar1;
		}
		ptr_6FBB1998 = nullptr;
		dword_6FBB199C = 0;
		gpint32_t_6FBB19A4[2] = 0;
		gpint32_t_6FBB19A4[3] = 0;
		gpint32_t_6FBB19A4[4] = 0;
		gpint32_t_6FBB19A4[5] = 0;
	}
	piVar3 = &dword_6FBB19A8;
	do
	{
		if ((D2CellFileStrc*)*piVar3 != nullptr)
		{
			CLIENT_FreeCellFile((D2CellFileStrc*)*piVar3);
		}
		*piVar3 = 0;
		piVar3 = piVar3 + 1;
		pvVar2 = ptr_6FBB19A0;
	} while ((int)piVar3 < (int)&dword_6FBB19B8);
	while (pvVar2 != nullptr)
	{
		pvVar1 = *(void**)((int)pvVar2 + 0x18);
		D2_FREE(pvVar2);
		pvVar2 = pvVar1;
	}
	ptr_6FBB19A0 = nullptr;
	gpint32_t_6FBB19A4 = nullptr;
}

//D2Client.0x6FACF730
void __cdecl sub_6FACF730()
{
	byte_6FBB19F0 = D2Win_10034_MixRGB(0, 0, 0xff);
	byte_6FBB19F1 = D2Win_10034_MixRGB(0xff, 0, 0);
	byte_6FBB19F2 = D2Win_10034_MixRGB(0xff, 0, 0xff);
	byte_6FBB19F3 = D2Win_10034_MixRGB(0, 0xff, 0);
	byte_6FBB19F4 = D2Win_10034_MixRGB(0x44, 0x70, 0x74);
	byte_6FBB19F5 = D2Win_10034_MixRGB(0x48, 0xa0, 0x34);
	byte_6FBB19F6 = D2Win_10034_MixRGB(0xf4, 0xf4, 0xf4);
	byte_6FBB19F7 = D2Win_10034_MixRGB(0x80, 0x80, 0x80);
	byte_6FBB19F8 = D2Win_10034_MixRGB(0xf4, 0xf4, 0);
	byte_6FBB19F9 = D2Win_10034_MixRGB(0, 0, 0xff);
	byte_6FBB19FA = D2Win_10034_MixRGB(0, 0xff, 0);
}

//D2Client.0x6FACF820
int __cdecl sub_6FACF820()
{
	return dword_6FBB1990;
}

//D2Client.0x6FACF830
int __fastcall sub_6FACF830(int a1)
{
	if (a1 != dword_6FBB1990)
	{
		dword_6FB77BC0 = 10;
		if (a1 == 1)
		{
			dword_6FB77BC0 = 0x14;
		}
		dword_6FBB1990 = a1;
		sub_6FACF490();
		sub_6FACB760();
		if (dword_6FBB1990 != 1)
		{
			dword_6FBB19C8 = 0;
			dword_6FBB19CC = 0;
			return 0;
		}
		dword_6FBB19C8 = (gnScreenWidth / 3 - dword_6FBB1A1C) + -0x10;
		a1 = gnScreenHeight * 0x55555556;
		dword_6FBB19CC = (gnScreenHeight / 3 - dword_6FBB1A18) + -0x10;
	}
	return a1;
}

//D2Client.0x6FACF8D0
void* __fastcall sub_6FACF8D0(void* a1, uint32_t a2, uint32_t a3, int a4, int a5, uint32_t a6)
{
	uint16_t uVar1;
	D2CellFileStrc* pCelFile;
	int iVar2;
	D2GfxDataStrc* pDVar3;
	D2GfxDataStrc local_54;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	*(uint8_t***)a1 = &gpuint8_t_6FB6EE98;
	uVar1 = *(uint16_t*)(byte_6FB78008 + a5 * 4);
	*(int*)((int)a1 + 0x32) = a5;
	*(uint16_t*)((int)a1 + 0x30) = uVar1;
	pDVar3 = &local_54;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar3->pCurrentCell = nullptr;
		pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
	}
	local_4 = 0;
	*(uint32_t*)((int)a1 + 0x28) = a6;
	*(uint32_t*)((int)a1 + 0x20) = 0;
	*(uint32_t*)((int)a1 + 0x2c) = 0;
	local_54.pCellFile = sub_6FB24110();
	local_54.nFrame = (uint32_t) * (uint16_t*)((int)a1 + 0x30);
	local_54.nDirection = 0;
	pCelFile = D2CMP_CelGetHandle(&local_54);
	*(uint32_t*)((int)a1 + 8) = a3;
	*(int*)((int)a1 + 0xc) = a4;
	*(uint32_t*)((int)a1 + 0x24) = 0;
	iVar2 = D2CMP_CelGetHeight(pCelFile);
	*(int*)((int)a1 + 0x18) = iVar2;
	iVar2 = D2CMP_CelGetWidth(pCelFile);
	*(int*)((int)a1 + 0x1c) = iVar2;
	return a1;
}

//D2Client.0x6FACF990
void* __fastcall sub_6FACF990(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FACF9C0((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FACF9C0
void __fastcall sub_6FACF9C0(uint32_t* a1)
{
	*a1 = (uint32_t)(&gpuint8_t_6FB6EE98);
	sub_6FAEFD30(a1);
}

//D2Client.0x6FACF9D0
void __fastcall sub_6FACF9D0(int a1)
{
	uint32_t uVar1;
	uint32_t uVar2;
	Font nFontSize;
	Unicode* wszText;
	int iVar3;
	D2GfxDataStrc* pDVar4;
	D2GfxDataStrc local_48;

	pDVar4 = &local_48;
	for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		pDVar4->pCurrentCell = nullptr;
		pDVar4 = (D2GfxDataStrc*)&pDVar4->pCellFile;
	}
	local_48.pCellFile = sub_6FB24110();
	local_48.nFrame = (uint32_t) * (uint16_t*)(a1 + 0x30) + *(int*)(a1 + 0x20);
	local_48.nDirection = 0;
	TEXTURE_CelDraw(&local_48, *(int*)(a1 + 8), *(int*)(a1 + 0xc), 0xffffffff, DRAWMODE_NORMAL, nullptr);
	uVar1 = sub_6FB57BC0();
	uVar2 = sub_6FB57BD0();
	if ((((*(int*)(a1 + 8) <= (int)(uVar1 & 0xffff)) &&
	         ((int)(uVar1 & 0xffff) <= *(int*)(a1 + 0x1c) + *(int*)(a1 + 8))) &&
	        (*(int*)(a1 + 0xc) - *(int*)(a1 + 0x18) <= (int)(uVar2 & 0xffff))) &&
	    ((int)(uVar2 & 0xffff) <= *(int*)(a1 + 0xc)))
	{
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT16);
		wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(byte_6FB7800A + *(int*)(a1 + 0x32) * 4)));
		iVar3 = D2Win_10121_GetTextWidth(wszText);
		D2Win_10117_DrawText(wszText, (*(int*)(a1 + 0x1c) - iVar3) / 2 + *(int*)(a1 + 8),
		    (*(int*)(a1 + 0xc) - *(int*)(a1 + 0x18)) + -5, 0, 0);
		D2Win_10127_SetFont(nFontSize);
	}
}

//D2Client.0x6FACFAD0
uint32_t __fastcall sub_6FACFAD0(void* a1, int a2, int a3)
{
	if ((((*(int*)((int)a1 + 8) <= (int)(uint32_t) * (uint16_t*)(a3 + 0xc)) &&
	         ((int)(uint32_t) * (uint16_t*)(a3 + 0xc) <=
	             *(int*)((int)a1 + 0x1c) + *(int*)((int)a1 + 8))) &&
	        (*(int*)((int)a1 + 0xc) - *(int*)((int)a1 + 0x18) <=
	            (int)(uint32_t) * (uint16_t*)(a3 + 0xe))) &&
	    ((int)(uint32_t) * (uint16_t*)(a3 + 0xe) <= *(int*)((int)a1 + 0xc)))
	{
		*(uint32_t*)((int)a1 + 0x20) = 1;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		return 1;
	}
	return 0;
}

//D2Client.0x6FACFB30
uint32_t __fastcall sub_6FACFB30(void* a1, int a2, int a3)
{
	uint32_t uVar1;

	if (*(int*)((int)a1 + 0x20) != 0)
	{
		if ((((*(int*)((int)a1 + 8) <= (int)(uint32_t) * (uint16_t*)(a3 + 0xc)) &&
		         ((int)(uint32_t) * (uint16_t*)(a3 + 0xc) <=
		             *(int*)((int)a1 + 0x1c) + *(int*)((int)a1 + 8))) &&
		        (*(int*)((int)a1 + 0xc) - *(int*)((int)a1 + 0x18) <=
		            (int)(uint32_t) * (uint16_t*)(a3 + 0xe))) &&
		    ((int)(uint32_t) * (uint16_t*)(a3 + 0xe) <= *(int*)((int)a1 + 0xc)))
		{
			*(uint32_t*)((int)a1 + 0x20) = 0;
			uVar1 = (**(code**)((int)a1 + 0x28))();
			return uVar1;
		}
		*(uint32_t*)((int)a1 + 0x2c) = 0;
		*(uint32_t*)((int)a1 + 0x20) = 0;
	}
	return 0;
}

//D2Client.0x6FACFB90
uint32_t __fastcall sub_6FACFB90(void* a1, int a2, int a3)
{
	uint32_t uVar1;

	if (((*(int*)((int)a1 + 0x24) != 0) && ((*(uint32_t*)(a3 + 0xc) & 0x40000000) == 0)) &&
	    (*(int*)(a3 + 8) == 0xd))
	{
		uVar1 = (**(code**)((int)a1 + 0x28))();
		return uVar1;
	}
	return 0;
}

//D2Client.0x6FACFBC0
void __fastcall sub_6FACFBC0(uint32_t* a1)
{
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6EECC);
	local_4 = 0;
	if ((uint32_t*)a1[2] != nullptr)
	{
		(*(code*)**(uint32_t**)a1[2])(1);
	}
	local_4 = 0xffffffff;
	sub_6FAEFD30(a1);
}

//D2Client.0x6FACFC20
void* __fastcall sub_6FACFC20(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FACFBC0((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FACFC50
uint32_t* __fastcall sub_6FACFC50(uint32_t* a1, uint32_t a2, uint32_t a3, int a4, uint32_t a5, uint32_t a6)
{
	void* pvVar1;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	local_4 = 0;
	*a1 = (uint32_t)(&gpuint8_t_6FB6EECC);
	pvVar1 = SMemAlloc(0x36, "new", -1, 0);
	local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), 1);
	if (pvVar1 == nullptr)
	{
		pvVar1 = nullptr;
	}
	else
	{
		pvVar1 = sub_6FACF8D0(pvVar1, a3, a3, a4, a5, a6);
	}
	a1[2] = (uint32_t)(pvVar1);
	return a1;
}

//D2Client.0x6FACFCD0
void __fastcall sub_6FACFCD0(int a1, int a2, int a3, Unicode* pUnicode, D2SkillsTxt* pSkillsTxtRecord)
{
	int iVar1;
	int iVar2;

	iVar2 = (a3 - a1) + 1;
	iVar1 = D2Win_10121_GetTextWidth(pUnicode);
	if (iVar1 < iVar2)
	{
		a1 = a1 + (iVar2 - iVar1 >> 1);
	}
	D2Win_10117_DrawText(pUnicode, a1, a2, (int)pSkillsTxtRecord, 0);
}

//D2Client.0x6FACFD10
uint32_t __fastcall sub_6FACFD10(short* a1, uint32_t* a2)
{
	short sVar1;
	int iVar2;
	int iVar3;
	short* psVar4;

	*a2 = 0;
	iVar2 = Unicode::strlen((Unicode*)a1);
	sVar1 = *a1;
	iVar3 = 0;
	psVar4 = a1;
	while (true)
	{
		if (sVar1 == 0)
		{
			return 0;
		}
		if (sVar1 == 10)
			break;
		sVar1 = psVar4[1];
		psVar4 = psVar4 + 1;
		iVar3 = iVar3 + 1;
	}
	a1[iVar3] = 0;
	if (iVar2 <= iVar3)
	{
		return 0;
	}
	*a2 = (uint32_t)(psVar4 + 1);
	return 1;
}
