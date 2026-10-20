#include "UI/QuestLog.h"
#include "Quest/Quests.h"

#include "Core/Archive.h"
#include "Core/Video.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/SCmd.h"
#include "Game/View.h"
#include "Quest/QuestsFX.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundChan.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/Inv.h"
#include "UI/NpcMenu.h"
#include "UI/Party.h"
#include "UI/Restart.h"
#include "UI/Text.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/MonUnique.h"

//D2Client.0x6FB7DC9C
uint32_t unk_6FB7DC9C[2] = { 0x31713161 };

//D2Client.0x6FB7D0E0
uint8_t byte_6FB7D0E0[4] = {0x28};
//D2Client.0x6FB7D0E4
uint8_t byte_6FB7D0E4[4] = {0x4B};
//D2Client.0x6FB7D0E8
uint8_t byte_6FB7D0E8[4];
//D2Client.0x6FB7D0EC
uint8_t byte_6FB7D0EC[4];
//D2Client.0x6FB7D130
uint8_t* gpuint8_t_6FB7D130 = (uint8_t*)&unk_6FB7DC9C;
//D2Client.0x6FB7D45C
uint8_t byte_6FB7D45C = 0xA0;
//D2Client.0x6FB7D472
uint32_t dword_6FB7D472 = 0x12E03C5;
//D2Client.0x6FB7D474
uint32_t dword_6FB7D474 = 0x3C6012E;
//D2Client.0x6FB7D476
uint32_t dword_6FB7D476 = 0x1BA03C6;
//D2Client.0x6FB7D478
uint32_t dword_6FB7D478 = 0x3C101BA;
//D2Client.0x6FB7D47A
uint32_t dword_6FB7D47A = 0x18C03C1;
//D2Client.0x6FB7D47C
uint32_t dword_6FB7D47C = 0xE91018C;
//D2Client.0x6FB7D65C
uint8_t byte_6FB7D65C = 0xA9;
//D2Client.0x6FB7D71C
uint8_t byte_6FB7D71C = 0x5A;
//D2Client.0x6FB7D8A0
uint8_t byte_6FB7D8A0[4] = {0x1A};
//D2Client.0x6FB7D8A4
uint8_t byte_6FB7D8A4[4] = {0x79};
//D2Client.0x6FB7D900
uint8_t byte_6FB7D900[4];
//D2Client.0x6FB7D904
uint8_t byte_6FB7D904[36] = {5, 0, 0, 0, 6, 0, 0, 0, 0xB, 0, 0, 0, 0xC, 0, 0, 0, 0x11, 0, 0, 0, 0x12, 0, 0, 0, 0x14, 0, 0, 0, 0x15, 0, 0, 0, 0x1A};
//D2Client.0x6FB7D929
uint8_t byte_6FB7D929;
//D2Client.0x6FB7D92A
uint8_t byte_6FB7D92A;
//D2Client.0x6FB7D92B
uint8_t byte_6FB7D92B[5];
//D2Client.0x6FB7D934
uint32_t dword_6FB7D934;
//D2Client.0x6FB7DBB8
int32_t dword_6FB7DBB8 = -1;
//D2Client.0x6FB7DBBC
int32_t dword_6FB7DBBC = -1;
//D2Client.0x6FB7DBBF
uint8_t tbl_6FB7DBBF[1] = {0xFF};
//D2Client.0x6FB7DBC0
int32_t dword_6FB7DBC0 = 16;
//D2Client.0x6FB7DBC3
uint8_t tbl_6FB7DBC3[1];
//D2Client.0x6FB7DBC4
int32_t dword_6FB7DBC4 = 248;
//D2Client.0x6FB7DBC8
int32_t dword_6FB7DBC8 = 270;
//D2Client.0x6FB7DE70
uint32_t dword_6FB7DE70;
//D2Client.0x6FBB5F40
uint8_t byte_6FBB5F40[4];
//D2Client.0x6FBB5F44
uint8_t byte_6FBB5F44;
//D2Client.0x6FBB5F48
uint8_t byte_6FBB5F48;
//D2Client.0x6FBB5F4C
uint8_t byte_6FBB5F4C;
//D2Client.0x6FBB5F50
uint8_t byte_6FBB5F50;
//D2Client.0x6FBB5F58
int32_t dword_6FBB5F58;
//D2Client.0x6FBB5F60
uint32_t dword_6FBB5F60;
//D2Client.0x6FBB5F64
int32_t dword_6FBB5F64;
//D2Client.0x6FBB5F68
uint32_t dword_6FBB5F68;
//D2Client.0x6FBB5F6C
int32_t dword_6FBB5F6C;
//D2Client.0x6FBB5F70
uint8_t byte_6FBB5F70;
//D2Client.0x6FBB5F71
uint8_t byte_6FBB5F71;
//D2Client.0x6FBB5F72
char byte_6FBB5F72;
//D2Client.0x6FBB5F73
char byte_6FBB5F73;
//D2Client.0x6FBB5F74
char byte_6FBB5F74;
//D2Client.0x6FBB5F75
uint32_t dword_6FBB5F75;
//D2Client.0x6FBB5F79
uint32_t dword_6FBB5F79;
//D2Client.0x6FBB5F7D
uint8_t byte_6FBB5F7D[4];
//D2Client.0x6FBB5F91
D2CellFileStrc* gpCellFile_6FBB5F91;
//D2Client.0x6FBB5F95
D2CellFileStrc* gpCellFile_6FBB5F95;
//D2Client.0x6FBB5F99
D2CellFileStrc* gpCellFile_6FBB5F99;
//D2Client.0x6FBB5F9D
D2CellFileStrc* gpCellFile_6FBB5F9D;
//D2Client.0x6FBB5FA1
uint32_t dword_6FBB5FA1;
//D2Client.0x6FBB600D
D2CellFileStrc* gpCellFile_6FBB600D;
//D2Client.0x6FBB6011
D2CellFileStrc* gpCellFile_6FBB6011;
//D2Client.0x6FBB6015
uint8_t byte_6FBB6015;
//D2Client.0x6FBB6016
uint8_t byte_6FBB6016;
//D2Client.0x6FBB6040
uint8_t byte_6FBB6040;
//D2Client.0x6FBB6069
uint32_t dword_6FBB6069;
//D2Client.0x6FBB606D
uint32_t dword_6FBB606D;
//D2Client.0x6FBB62C8
uint8_t tbl_6FBB62C8[2];
//D2Client.0x6FBB62CA
uint8_t byte_6FBB62CA;
//D2Client.0x6FBB62CD
uint8_t byte_6FBB62CD;
//D2Client.0x6FBB62CE
uint8_t byte_6FBB62CE;
//D2Client.0x6FBB62CF
uint32_t dword_6FBB62CF;
//D2Client.0x6FBB6EE5
uint32_t dword_6FBB6EE5;
//D2Client.0x6FBB6EFD
uint32_t dword_6FBB6EFD;
//D2Client.0x6FBB6F15
uint32_t dword_6FBB6F15;
//D2Client.0x6FBB6F19
uint8_t byte_6FBB6F19;
//D2Client.0x6FBB6F1D
uint8_t byte_6FBB6F1D;
//D2Client.0x6FBB6F1E
uint8_t byte_6FBB6F1E;
//D2Client.0x6FBB6F1F
uint8_t byte_6FBB6F1F;
//D2Client.0x6FBB6F20
uint8_t byte_6FBB6F20;
//D2Client.0x6FBB6F21
uint32_t dword_6FBB6F21;
//D2Client.0x6FBB6F25
uint8_t byte_6FBB6F25;
//D2Client.0x6FBB6F2C
int32_t dword_6FBB6F2C;
//D2Client.0x6FBB6F30
int32_t dword_6FBB6F30;
//D2Client.0x6FBB6FD8
int32_t dword_6FBB6FD8;
//D2Client.0x6FBB6FE0
int32_t dword_6FBB6FE0;
//D2Client.0x6FBB6FE8
int32_t dword_6FBB6FE8;
//D2Client.0x6FBB6FEC
int32_t dword_6FBB6FEC;

//D2Client.0x6FB04220
void __cdecl sub_6FB04220()
{
	uint32_t* puVar1;

	if (gpCellFile_6FBB5F95 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F95);
		gpCellFile_6FBB5F95 = nullptr;
	}
	if (gpCellFile_6FBB5F99 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F99);
		gpCellFile_6FBB5F99 = nullptr;
	}
	if (gpCellFile_6FBB600D != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB600D);
		gpCellFile_6FBB600D = nullptr;
	}
	if (gpCellFile_6FBB5F91 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F91);
		gpCellFile_6FBB5F91 = nullptr;
	}
	if (gpCellFile_6FBB5F9D != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F9D);
		gpCellFile_6FBB5F9D = nullptr;
	}
	if (gpCellFile_6FBB6011 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB6011);
		gpCellFile_6FBB6011 = nullptr;
	}
	puVar1 = &dword_6FBB5FA1;
	do
	{
		if ((D2CellFileStrc*)*puVar1 != nullptr)
		{
			CLIENT_FreeCellFile((D2CellFileStrc*)*puVar1);
			*puVar1 = 0;
		}
		puVar1 = puVar1 + 1;
	} while ((int)puVar1 < (int)&gpCellFile_6FBB600D);
}

//D2Client.0x6FB042D0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB042D0()
{
	short index;
	D2SplittedTextStrc* pDVar1;
	bool bVar2;
	bool bVar3;
	char cVar4;
	uint32_t extraout_var;
	int iVar5;
	D2BitBufferStrc* pDVar6;
	DWORD DVar7;
	D2SplittedTextStrc* pFree;
	Unicode* pUVar8;
	int iVar9;
	uint32_t extraout_ECX;
	uint32_t uVar10;
	uint8_t* pbVar11;
	D2GfxDataStrc* pDVar12;
	int iVar13;
	uint32_t* puVar14;
	uint32_t uVar15;
	int nColor;
	int bCentered;
	int iStack_60;
	int aiStack_5c[5];
	D2GfxDataStrc local_48;

	pDVar12 = &local_48;
	for (iVar9 = 0x12; iVar9 != 0; iVar9 = iVar9 + -1)
	{
		pDVar12->pCurrentCell = nullptr;
		pDVar12 = (D2GfxDataStrc*)&pDVar12->pCellFile;
	}
	local_48.nDirection = 0;
	bVar3 = sub_6FB283E0();
	if (D2C_ZEXT(bVar3) != 0)
	{
		if (dword_6FBB5F58 == 2)
		{
			dword_6FBB5F58 = 0;
			byte_6FBB5F70 = 0;
			byte_6FBB5F73 = '\0';
		}
		sub_6FB04220();
		sub_6FB23260(0xf, 1, 0);
		return;
	}
	iVar9 = sub_6FB23230(0x12);
	if (iVar9 != 0)
	{
		if (dword_6FBB5F58 == 2)
		{
			dword_6FBB5F58 = 0;
			byte_6FBB5F70 = 0;
			byte_6FBB5F73 = '\0';
		}
		sub_6FB04220();
		sub_6FB23260(0xf, 1, 0);
		return;
	}
	cVar4 = VIDEO_IsInVideoSequence();
	if (cVar4 != '\0')
	{
		if (dword_6FBB5F58 == 2)
		{
			dword_6FBB5F58 = 0;
			byte_6FBB5F70 = 0;
			byte_6FBB5F73 = '\0';
		}
		sub_6FB04220();
		sub_6FB23260(0xf, 1, 0);
		return;
	}
	if (gpCellFile_6FBB5F95 == nullptr)
	{
		sub_6FB058D0();
		sub_6FB056D0(0, 1);
		if (gpCellFile_6FBB5F95 == nullptr)
			goto LAB_6fb044a1;
	}
	local_48.pCellFile = gpCellFile_6FBB5F95;
	local_48.nFrame = 0;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 1;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 2;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 3;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
LAB_6fb044a1:
	if (gpCellFile_6FBB5F99 != nullptr)
	{
		local_48.pCellFile = gpCellFile_6FBB5F99;
		uVar10 = 0;
		do
		{
			iVar13 = 0;
			iVar9 = FOG_IsExpansion();
			if ((iVar9 == 0) || (iVar9 = sub_6FAAC080(), iVar9 == 0))
			{
				aiStack_5c[0] = 5;
				aiStack_5c[1] = 0x52;
				aiStack_5c[2] = 0x9f;
				aiStack_5c[3] = 0xec;
				if (3 < (int)uVar10)
					break;
			}
			else
			{
				iVar13 = 1;
				aiStack_5c[0] = 5;
				aiStack_5c[1] = 0x43;
				aiStack_5c[2] = 0x81;
				aiStack_5c[3] = 0xbf;
				aiStack_5c[4] = 0xfd;
			}
			aiStack_5c[0] = 5;
			if (uVar10 == dword_6FBB6F15)
			{
				local_48.nFrame = uVar10 * 2;
				iVar9 = dword_6FBBA74C + gnScreenHeight;
				iVar5 = aiStack_5c[uVar10] + dword_6FBBA748;
			LAB_6fb045ef:
				TEXTURE_CelDraw(&local_48, iVar5, iVar9 + -0x1c0 + iVar13, 0xffffffff, DRAWMODE_NORMAL,
				    nullptr);
			}
			else
			{
				switch (uVar10)
				{
				case 1:
					iVar9 = 7;
					break;
				case 2:
					iVar9 = 0xf;
					break;
				case 3:
					iVar9 = 0x17;
					break;
				case 4:
					iVar5 = 0;
					iVar9 = 0x1a;
					pDVar6 = sub_6FAFBD20();
					iVar5 = QUESTRECORD_GetQuestState(pDVar6, iVar9, iVar5);
					iVar9 = FOG_IsExpansion();
					if ((iVar9 != 0) && (iVar9 = sub_6FAAC080(), iVar9 != 0))
						goto joined_r0x6fb045b8;
					goto LAB_6fb045f4;
				default:
					goto switchD_6fb04567_default;
				}
				iVar5 = 0;
				pDVar6 = sub_6FAFBD20();
				iVar5 = QUESTRECORD_GetQuestState(pDVar6, iVar9, iVar5);
			joined_r0x6fb045b8:
				if (iVar5 != 0)
				{
				switchD_6fb04567_default:
					local_48.nFrame = uVar10 * 2 + 1;
					iVar9 = dword_6FBBA74C + gnScreenHeight;
					iVar5 = aiStack_5c[uVar10] + dword_6FBBA748;
					goto LAB_6fb045ef;
				}
			}
		LAB_6fb045f4:
			uVar10 = uVar10 + 1;
		} while ((int)uVar10 < 5);
	}
	iVar9 = 6;
	do
	{
		iVar9 = iVar9 + -1;
		puVar14 = &dword_6FBB6069;
		for (iVar13 = 0x39f; iVar13 != 0; iVar13 = iVar13 + -1)
		{
			*puVar14 = 0;
			puVar14 = puVar14 + 1;
		}
	} while (iVar9 != 0);
	bVar3 = false;
	if ((int)dword_6FBB6F15 < 5)
	{
		uVar10 = 0;
		dword_6FBB5F60 = 0;
		iStack_60 = 0;
		bVar2 = false;
		pbVar11 = &byte_6FB7D92A;
		do
		{
			uVar15 = 0xffffffff;
			if ((((pbVar11[1] != dword_6FBB6F15) || (pbVar11[-2] == 0)) || (0x1a < pbVar11[-1])) ||
			    (((&dword_6FBB5FA1)[pbVar11[-1]] == 0 || (5 < (int)uVar10))))
				goto LAB_6fb049e8;
			*(uint32_t*)((int)&dword_6FBB6069 + uVar10 * 0x26a + 1) = *(uint32_t*)(pbVar11 + 10);
			sub_6FB04D50((int)&dword_6FBB6069 + dword_6FBB5F60 * 0x26a);
			iVar9 = dword_6FBB5F60 * 0x26a;
			switch (*(uint32_t*)((int)&dword_6FBB62CF + dword_6FBB5F60 * 0x26a))
			{
			case 0:
				*(uint8_t*)((int)&dword_6FBB6069 + iVar9) = 1;
				uVar10 = (&dword_6FBB6EE5)[dword_6FBB5F60];
				if (0x18 < (int)uVar10)
				{
					uVar10 = 0x18;
					pDVar6 = sub_6FAFBD20();
					QUESTRECORD_SetQuestState(pDVar6, *(int*)(pbVar11 + 10), 0xc);
					sub_6FAAD990(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x58), *(uint16_t*)(pbVar11 + 10));
				}
				local_48.pCellFile = (D2CellFileStrc*)(&dword_6FBB5FA1)[pbVar11[-1]];
				local_48.nFrame = uVar10;
				TEXTURE_CelDraw(&local_48, *(int*)(byte_6FB7D8A0 + (uint32_t)*pbVar11 * 0x10) + dword_6FBBA748,
				    *(int*)(byte_6FB7D8A4 + (uint32_t)*pbVar11 * 0x10) - dword_6FBBA74C, 0xffffffff,
				    DRAWMODE_NORMAL, nullptr);
				DVar7 = GetTickCount();
				if ((&dword_6FBB6EFD)[dword_6FBB5F60] == 0)
				{
					(&dword_6FBB6EFD)[dword_6FBB5F60] = DVar7;
				}
				if (100 < DVar7 - (&dword_6FBB6EFD)[dword_6FBB5F60])
				{
					(&dword_6FBB6EFD)[dword_6FBB5F60] = DVar7;
					(&dword_6FBB6EE5)[dword_6FBB5F60] = (&dword_6FBB6EE5)[dword_6FBB5F60] + 1;
					if (((&dword_6FBB6EE5)[dword_6FBB5F60] == 1) && (iVar9 = FOG_IsExpansion(), iVar9 != 0))
					{
						sub_6FB55820(0xe, nullptr, 0.0, 0.0, 0);
					}
				}
				goto LAB_6fb04962;
			case 1:
				*(uint8_t*)((int)&dword_6FBB6069 + iVar9) = 1;
				uVar10 = (uint32_t)*pbVar11;
				if (dword_6FBB5F75 == uVar10)
				{
					local_48.pCellFile = gpCellFile_6FBB5F9D;
					local_48.nFrame = (uint32_t)pbVar11[-1];
					iVar13 = (*(int*)(byte_6FB7D8A4 + uVar10 * 0x10) - dword_6FBBA74C) + dword_6FB7DBB8;
					iVar9 = *(int*)(byte_6FB7D8A0 + uVar10 * 0x10) + dword_6FBB6F2C;
				}
				else
				{
					local_48.nFrame = 0x18;
					local_48.pCellFile = (D2CellFileStrc*)(&dword_6FBB5FA1)[pbVar11[-1]];
					iVar9 = *(int*)(byte_6FB7D8A0 + uVar10 * 0x10);
					iVar13 = *(int*)(byte_6FB7D8A4 + uVar10 * 0x10) - dword_6FBBA74C;
				}
				TEXTURE_CelDraw(&local_48, iVar9 + dword_6FBBA748, iVar13, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				uVar15 = (uint32_t)*pbVar11;
				break;
			case 2:
				*(uint8_t*)((int)&dword_6FBB6069 + iVar9) = 1;
				local_48.pCellFile = (D2CellFileStrc*)(&dword_6FBB5FA1)[pbVar11[-1]];
				local_48.nFrame = 0x1a;
				TEXTURE_CelDraw(&local_48, *(int*)(byte_6FB7D8A0 + (uint32_t)*pbVar11 * 0x10) + dword_6FBBA748,
				    *(int*)(byte_6FB7D8A4 + (uint32_t)*pbVar11 * 0x10) - dword_6FBBA74C, 0xffffffff,
				    DRAWMODE_NORMAL, nullptr);
				uVar15 = (uint32_t)*pbVar11;
				break;
			case 3:
				if ((*(short*)((int)&dword_6FBB606D + iVar9 + 1) == 0x3a0) &&
				    ((&byte_6FBB62CE)[iVar9] == '\a'))
				{
					bVar3 = true;
				}
				*(uint8_t*)((int)&dword_6FBB6069 + iVar9) = 1;
				local_48.pCellFile = (D2CellFileStrc*)(&dword_6FBB5FA1)[pbVar11[-1]];
				local_48.nFrame = (dword_6FBB5F75 != *pbVar11) - 1 & 0x19;
				iVar9 = (uint32_t)*pbVar11 * 0x10;
				TEXTURE_CelDraw(&local_48, *(int*)(byte_6FB7D8A0 + iVar9) + dword_6FBBA748,
				    *(int*)(byte_6FB7D8A4 + iVar9) - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL,
				    nullptr);
			LAB_6fb04962:
				uVar15 = (uint32_t)*pbVar11;
				break;
			default:
				goto switchD_6fb046e4_default;
			}
			dword_6FBB5F60 = dword_6FBB5F60 + 1;
		switchD_6fb046e4_default:
			local_48.pCellFile = gpCellFile_6FBB5F91;
			if (uVar15 != dword_6FBB5F79)
			{
				iVar13 = (uint32_t)*pbVar11 * 0x10;
				iVar5 = *(int*)(byte_6FB7D8A4 + iVar13) - dword_6FBBA74C;
				iVar9 = dword_6FBB6F30;
			}
			else
			{
				iVar13 = (uint32_t)*pbVar11 * 0x10;
				iVar5 = *(int*)(byte_6FB7D8A4 + iVar13) - dword_6FBBA74C;
				iVar9 = dword_6FB7DBBC;
			}
			local_48.nFrame = (uint32_t)(uVar15 == dword_6FBB5F79);
			TEXTURE_CelDraw(&local_48, *(int*)(byte_6FB7D8A0 + iVar13) + -4 + dword_6FBBA748,
			    iVar5 + 5 + iVar9, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			uVar10 = dword_6FBB5F60;
		LAB_6fb049e8:
			iStack_60 = iStack_60 + 1;
			if ((0x29 < iStack_60) || (5 < (int)uVar10))
			{
				bVar2 = true;
			}
			pbVar11 = pbVar11 + 0x10;
		} while (!bVar2);
		if ((bVar3) && (dword_6FBB5F79 == 5))
		{
			local_48.pCellFile = gpCellFile_6FBB6011;
			local_48.nFrame = dword_6FBB5F68;
			if (((int)dword_6FBB5F68 < 0) || (6 < (int)dword_6FBB5F68))
			{
				local_48.nFrame = 0;
			}
			TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x6e, dword_6FBBA74C + -0x6e + gnScreenHeight, 0xffffffff,
			    DRAWMODE_MODULATE, nullptr);
		}
	}
	D2Win_10127_SetFont(D2FONT_FONTFORMAL11);
	if ((((dword_6FBB5F79 != 0xffffffff) && ((int)dword_6FBB5F79 < 6)) &&
	        ((int)dword_6FBB5F79 < (int)dword_6FBB5F60)) &&
	    (iVar9 = 0, 0 < (int)dword_6FBB5F60))
	{
		pbVar11 = &byte_6FBB62CA;
		do
		{
			if (*pbVar11 == dword_6FBB5F79)
			{
				if ((iVar9 != -1) &&
				    (iVar13 = iVar9 * 0x26a, *(char*)((int)&dword_6FBB6069 + iVar9 * 0x26a) != '\0'))
				{
					index = *(short*)((int)&dword_6FBB606D + iVar13 + 1);
					if (index != 0xe8c)
					{
						pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
						bCentered = 0;
						iVar9 = dword_6FB7DBC4 - dword_6FBBA74C;
						nColor = 0;
						iVar5 = D2Win_10121_GetTextWidth(pUVar8);
						D2Win_10117_DrawText(pUVar8, (dword_6FBBA748 - iVar5 / 2) + 0xa0, iVar9, nColor, bCentered);
					}
					if (((byte_6FBB5F73 == '\0') && (*(short*)((int)&dword_6FBB606D + iVar13 + 3) != 0)) &&
					    (pFree = D2Win_10199((Unicode*)((int)&dword_6FBB606D + iVar13 + 3), &iStack_60, 0x10e),
					        pFree != nullptr))
					{
						iVar9 = 0;
						do
						{
							D2Win_10117_DrawText(pFree->wszLine, dword_6FBBA748 + dword_6FB7DBC0,
							    (iVar9 - dword_6FBBA74C) + dword_6FB7DBC8, 0, 0);
							pDVar1 = pFree->pNextLine;
							D2_FREE(pFree->wszLine);
							D2_FREE(pFree);
							iVar9 = iVar9 + 0x14;
							pFree = pDVar1;
						} while (pDVar1 != nullptr);
					}
				}
				break;
			}
			iVar9 = iVar9 + 1;
			pbVar11 = pbVar11 + 0x26a;
		} while (iVar9 < (int)dword_6FBB5F60);
	}
	local_48.pCellFile = sub_6FB24110();
	local_48.nFrame = (byte_6FBB5F72 != '\0') + 10;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x116, dword_6FBBA74C + -0x3a + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	iVar9 = sub_6FB57BC0();
	iVar13 = sub_6FB57BD0();
	iVar9 = iVar9 - dword_6FBBA748;
	iVar13 = iVar13 + dword_6FBBA74C;
	if ((((0x115 < iVar9) && (iVar9 < 0x13a)) && (0x187 < iVar13)) && (iVar13 < 0x1aa))
	{
		D2Win_10127_SetFont(D2FONT_FONTEXOCET10);
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
		D2Win_10129_DrawFramedText(pUVar8, dword_6FBBA748 + 0x128, dword_6FBBA74C + -0x5f + gnScreenHeight, 0, 1);
	}
	local_48.pCellFile = gpCellFile_6FBB600D;
	local_48.nFrame = (uint32_t)(byte_6FBB5F74 != '\0');
	TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0xe2, dword_6FBBA74C + -0x3a + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	if (((0xe5 < iVar9) && (iVar9 < 0x104)) && ((0x186 < iVar13 && (iVar13 < 0x1a8))))
	{
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe88));
		D2Win_10127_SetFont(D2FONT_FONTEXOCET10);
		D2Win_10129_DrawFramedText(pUVar8, dword_6FBBA748 + 0xf1, dword_6FBBA74C + -0x5f + gnScreenHeight, 0, 1);
	}
}

//D2Client.0x6FB04D50
void __fastcall sub_6FB04D50(int a1)
{
	short* psVar1;
	uint8_t uVar2;
	uint8_t bVar3;
	int* piVar4;
	D2BitBufferStrc* pQuestRecord;
	D2BitBufferStrc* pQuestRecord_00;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	uint32_t uVar9;
	Unicode* pUVar10;
	short sVar11;
	uint16_t uVar12;
	int iVar13;
	int iVar14;
	uint8_t local_34;
	Unicode* pUStack_24;
	int local_20;
	char acStack_1c[8];
	Unicode aUStack_14[10];

	iVar14 = 0;
	*(uint16_t*)(a1 + 5) = 0xe8c;
	*(uint16_t*)(a1 + 0x25f) = 0xe8c;
	*(uint16_t*)(a1 + 7) = 0;
	*(uint8_t*)(a1 + 0x263) = 0;
	*(uint8_t*)(a1 + 0x264) = 0;
	piVar4 = (int*)(&dword_6FB7D934);
	while (*piVar4 != *(int*)(a1 + 1))
	{
		piVar4 = piVar4 + 4;
		iVar14 = iVar14 + 1;
		if ((int)&tbl_6FB7DBC3 < (int)piVar4)
		{
		LAB_6fb04d9e:
			*(uint32_t*)(a1 + 0x266) = 2;
			return;
		}
	}
	if (iVar14 == -1)
		goto LAB_6fb04d9e;
	iVar13 = iVar14 * 0x10;
	*(uint8_t*)(a1 + 0x261) = (&byte_6FB7D92A)[iVar13];
	*(uint8_t*)(a1 + 0x262) = (&byte_6FB7D929)[iVar13];
	pQuestRecord = sub_6FAFBD20();
	pQuestRecord_00 = sub_6FAFBD30();
	bVar3 = (&byte_6FBB6016)[iVar14];
	*(uint8_t*)(a1 + 0x265) = bVar3;
	if (*(int*)(byte_6FB7D92B + iVar13 + 1) == 0)
		goto LAB_6fb04d9e;
	iVar5 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 0);
	iVar6 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 0xd);
	iVar7 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 1);
	psVar1 = *(short**)(byte_6FB7D92B + iVar13 + 1);
	if ((psVar1 == (short*)&byte_6FB7D71C) && (iVar7 != 0))
	{
		if (bVar3 == 0)
		{
			bVar3 = 4;
		}
	}
	else
	{
		if ((psVar1 != (short*)&byte_6FB7D45C) || (iVar5 != 0))
		{
			if (iVar6 == 0)
			{
				if (iVar5 == 0)
					goto LAB_6fb0510e;
				sVar11 = 0xe90;
				local_34 = 0xb;
			}
			else
			{
				if (iVar5 == 0)
					goto LAB_6fb04fba;
				sVar11 = 0xe8e;
				local_34 = 0xd;
			}
			*(uint8_t*)(a1 + 0x265) = local_34;
			if (psVar1 != nullptr)
			{
				iVar13 = 300;
				*(short*)(a1 + 5) = *psVar1;
				pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
				Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar13);
				*(uint16_t*)(a1 + 0x25d) = 0;
				*(short*)(a1 + 0x25f) = psVar1[1];
				(&byte_6FBB6040)[iVar14] = local_34;
				*(uint8_t*)(a1 + 0x264) = 1;
				iVar14 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 0xc);
				if (iVar14 != 0)
				{
					*(uint32_t*)(a1 + 0x266) = 1;
					return;
				}
				*(uint32_t*)(a1 + 0x266) = 0;
				return;
			}
			goto LAB_6fb04d9e;
		}
		if (iVar6 == 0)
		{
			iVar8 = QUESTRECORD_GetQuestState(pQuestRecord, 0xc, 0);
			if (((iVar8 != 0) || (iVar8 = QUESTRECORD_GetQuestState(pQuestRecord, 0xc, 0xd), iVar8 != 0)) &&
			    (bVar3 == 1))
			{
				iVar13 = 300;
				*(uint16_t*)(a1 + 5) = byte_6FB7D45C;
				pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(dword_6FB7D47A));
				Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar13);
				uVar2 = 7;
				*(uint16_t*)(a1 + 0x25d) = 0;
				(&byte_6FBB6040)[iVar14] = 7;
				uVar12 = dword_6FB7D47C;
			LAB_6fb04f7c:
				*(uint16_t*)(a1 + 0x25f) = uVar12;
				*(uint32_t*)(a1 + 0x266) = 3;
				*(uint8_t*)(a1 + 0x264) = 1;
				*(uint8_t*)(a1 + 0x265) = uVar2;
				return;
			}
			iVar8 = QUESTRECORD_GetQuestState(pQuestRecord, 0xe, 3);
			if (iVar8 == 1)
			{
				iVar13 = 300;
				*(uint16_t*)(a1 + 5) = byte_6FB7D45C;
				pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(dword_6FB7D472));
				Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar13);
				uVar2 = 5;
				*(uint16_t*)(a1 + 0x25d) = 0;
				(&byte_6FBB6040)[iVar14] = 5;
				uVar12 = dword_6FB7D474;
				goto LAB_6fb04f7c;
			}
			iVar8 = QUESTRECORD_GetQuestState(pQuestRecord, 0xe, 4);
			if (iVar8 == 1)
			{
				iVar13 = 300;
				*(uint16_t*)(a1 + 5) = byte_6FB7D45C;
				pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(dword_6FB7D476));
				Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar13);
				uVar2 = 6;
				*(uint16_t*)(a1 + 0x25d) = 0;
				(&byte_6FBB6040)[iVar14] = 6;
				uVar12 = dword_6FB7D478;
				goto LAB_6fb04f7c;
			}
		LAB_6fb0510e:
			if ((iVar7 != 0) &&
			    (iVar7 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 0xf),
			        iVar7 != 0))
			{
				bVar3 = 10;
				if (*(int*)(a1 + 1) == 0x25)
				{
					iVar13 = QUESTRECORD_GetQuestState(pQuestRecord, 0x25, 8);
					if ((iVar13 == 0) ||
					    (iVar13 = QUESTRECORD_GetQuestState(pQuestRecord, 0x25, 9), iVar13 != 0))
					{
						iVar13 = QUESTRECORD_GetQuestState(pQuestRecord, 0x25, 8);
						if (iVar13 == 0)
						{
							bVar3 = 5;
						}
					}
					else
					{
						bVar3 = 6;
					}
				}
				if (*(int*)(a1 + 1) == 0x22)
				{
					iVar13 = QUESTRECORD_GetQuestState(pQuestRecord, 0x26, 4);
					bVar3 = (iVar13 != 0) + 4;
				}
				*(uint8_t*)(a1 + 0x265) = bVar3;
				if ((psVar1 != nullptr) && (uVar9 = (uint32_t)bVar3, psVar1[uVar9 * 2 + 1] != 0xe8d))
				{
					iVar13 = 300;
					*(short*)(a1 + 5) = *psVar1;
					pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(psVar1[uVar9 * 2 + 1]));
					Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar13);
					*(uint16_t*)(a1 + 0x25d) = 0;
					*(short*)(a1 + 0x25f) = psVar1[uVar9 * 2 + 2];
					(&byte_6FBB6040)[iVar14] = bVar3;
					if (*(int*)(a1 + 1) == 0x1b)
					{
						*(uint32_t*)(a1 + 0x266) = 1;
						*(uint8_t*)(a1 + 0x264) = 1;
						return;
					}
					*(uint32_t*)(a1 + 0x266) = 3;
					*(uint8_t*)(a1 + 0x264) = 1;
					return;
				}
				goto LAB_6fb04d9e;
			}
		}
		else
		{
		LAB_6fb04fba:
			if (psVar1[2] == -1)
				goto LAB_6fb0510e;
			if (iVar7 != 0)
			{
				if (psVar1 != (short*)&byte_6FB7D65C)
				{
					bVar3 = (char)psVar1[2] + 1;
					*(short*)(a1 + 5) = *psVar1;
					iVar13 = 300;
					pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(psVar1[(uint32_t)bVar3 * 2 + 1]));
					Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar13);
					*(uint16_t*)(a1 + 0x25d) = 0;
					*(bool*)(a1 + 0x263) = bVar3 != (&byte_6FBB6040)[iVar14];
					sVar11 = psVar1[(uint32_t)bVar3 * 2 + 2];
					(&byte_6FBB6040)[iVar14] = bVar3;
					*(short*)(a1 + 0x25f) = sVar11;
					*(uint32_t*)(a1 + 0x266) = 3;
					*(uint8_t*)(a1 + 0x264) = 1;
					*(uint8_t*)(a1 + 0x265) = bVar3;
					return;
				}
				goto LAB_6fb0510e;
			}
		}
		if (bVar3 == 0)
		{
			iVar13 = QUESTRECORD_GetQuestState(pQuestRecord_00, (&dword_6FB7D934)[iVar14 * 4], 0xd);
			if (iVar13 == 0)
			{
				iVar13 = QUESTRECORD_GetQuestState(pQuestRecord_00, (&dword_6FB7D934)[iVar14 * 4], 0xf);
				if (((iVar13 == 0) || (iVar6 != 0)) ||
				    (iVar14 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 1),
				        iVar14 != 0))
					goto LAB_6fb04d9e;
				sVar11 = 0xe92;
				if (gnGameType == 0)
				{
					sVar11 = 0xe91;
				}
			}
			else
			{
				if (((*(int*)(a1 + 1) != 0x15) ||
				        (iVar13 = QUESTRECORD_GetQuestState(pQuestRecord, 0x15, 0), iVar13 != 0)) ||
				    (iVar13 = QUESTRECORD_GetQuestState(pQuestRecord, 0x15, 4), iVar13 != 1))
				{
					if ((iVar6 == 0) &&
					    (iVar14 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 1),
					        iVar14 == 0))
					{
						sVar11 = 0xe92;
						if (gnGameType == 0)
						{
							sVar11 = 0xe91;
						}
						iVar14 = 300;
						pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
						Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar14);
						*(uint16_t*)(a1 + 0x25d) = 0;
						*(uint16_t*)(a1 + 0x25f) = 0xe8d;
						*(uint8_t*)(a1 + 0x264) = 1;
						*(uint32_t*)(a1 + 0x266) = 3;
						return;
					}
					goto LAB_6fb04d9e;
				}
				sVar11 = 0x3dd;
			}
			iVar14 = 300;
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar14);
			*(uint16_t*)(a1 + 0x25d) = 0;
			*(uint16_t*)(a1 + 0x25f) = 0xe8d;
			*(uint8_t*)(a1 + 0x264) = 1;
			*(uint32_t*)(a1 + 0x266) = 3;
			return;
		}
	}
	if (*(int*)(byte_6FB7D92B + iVar13 + 1) != 0)
	{
		if (*psVar1 != 0xe82)
		{
			*(short*)(a1 + 5) = *psVar1;
			if ((((((iVar5 == 0) && (iVar6 == 0)) &&
			          (iVar5 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 1),
			              iVar5 == 0)) &&
			         ((pQuestRecord_00 != nullptr &&
			             (iVar5 = QUESTRECORD_GetQuestState(pQuestRecord_00, (&dword_6FB7D934)[iVar14 * 4], 0xd),
			                 iVar5 != 0)))) &&
			        (*(int*)(a1 + 1) != 0x13)) ||
			    (iVar5 = QUESTRECORD_GetQuestState(pQuestRecord, (&dword_6FB7D934)[iVar14 * 4], 0xe),
			        iVar5 != 0))
			{
				sVar11 = (gnGameType != 0) + 0xe91;
			}
			else
			{
				sVar11 = psVar1[(uint32_t)bVar3 * 2 + 1];
				if ((sVar11 == 0xe8f) && (gnGameType == 0))
				{
					sVar11 = 0xe91;
				}
			}
			iVar5 = 300;
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar5);
			if ((*psVar1 == 0x585e) && (sVar11 == 0x5860))
			{
				if (dword_6FBB5F6C == 0)
				{
					iVar5 = 300;
					pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe91));
					Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, iVar5);
				}
				else
				{
					iVar5 = dword_6FBB5F6C;
					pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x5860));
					Unicode::sprintf(300, (Unicode*)(a1 + 7), pUVar10, iVar5);
				}
			}
			*(uint16_t*)(a1 + 0x25d) = 0;
			*(uint8_t*)(a1 + 0x263) = 0;
			if ((bVar3 != (&byte_6FBB6040)[iVar14]) && (*(int*)(byte_6FB7D92B + iVar13 + 1) != 0))
			{
				*(uint8_t*)(a1 + 0x263) = 1;
			}
			sVar11 = psVar1[(uint32_t)bVar3 * 2 + 2];
			(&byte_6FBB6040)[iVar14] = bVar3;
			*(short*)(a1 + 0x25f) = sVar11;
			*(uint32_t*)(a1 + 0x266) = 3;
			*(uint8_t*)(a1 + 0x264) = 1;
			if (bVar3 != 0xd)
			{
				return;
			}
			iVar14 = (&dword_6FB7D934)[iVar14 * 4];
			goto LAB_6fb0555e;
		}
		uVar9 = (uint32_t)bVar3;
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(psVar1[uVar9 * 2 + 1]));
		if ((uVar9 == 3) || (uVar9 == 4))
		{
			if ((*psVar1 == 0xe82) && (1 < dword_6FBB5F64))
			{
				sprintf(acStack_1c, "%d", (*psVar1 != 0xe82) - 1 & dword_6FBB5F64);
				Unicode::toUnicode(aUStack_14, acStack_1c, 9);
				Unicode::strcpy((Unicode*)(a1 + 7), pUVar10);
				iVar13 = Unicode::strlen(pUVar10);
				D2_ASSERT(0x117 >= iVar13);
				Unicode::strcat((Unicode*)(a1 + 7), aUStack_14);
			LAB_6fb0537e:
				*(short*)(a1 + 5) = *psVar1;
				*(uint8_t*)(a1 + 0x263) = 0;
				if (bVar3 != (&byte_6FBB6040)[iVar14])
				{
					*(uint8_t*)(a1 + 0x263) = 1;
				}
				(&byte_6FBB6040)[iVar14] = bVar3;
				sVar11 = psVar1[uVar9 * 2 + 2];
				*(uint32_t*)(a1 + 0x266) = 3;
				*(short*)(a1 + 0x25f) = sVar11;
				*(uint8_t*)(a1 + 0x264) = 1;
				*(uint8_t*)(a1 + 0x265) = bVar3;
				if (bVar3 != 0xd)
				{
					return;
				}
				iVar14 = (&dword_6FB7D934)[iVar14 * 4];
			LAB_6fb0555e:
				iVar14 = QUESTRECORD_GetQuestState(pQuestRecord, iVar14, 0xc);
				*(uint32_t*)(a1 + 0x266) = (uint32_t)(iVar14 != 0);
				return;
			}
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe9b));
		}
		Unicode::strncpy((Unicode*)(a1 + 7), pUVar10, 300);
		*(uint16_t*)(a1 + 0x25d) = 0;
		goto LAB_6fb0537e;
	}
	goto LAB_6fb04d9e;
}

//D2Client.0x6FB056D0
void __fastcall sub_6FB056D0(uint32_t a1, int a2)
{
	uint32_t uVar1;
	int iVar2;
	D2CellFileStrc* pDVar3;
	uint32_t uVar4;
	uint8_t* pbVar5;
	int iVar6;
	Unicode* pThis;
	int local_380;
	uint32_t local_37c;
	uint8_t uStack_370;
	uint32_t uStack_36f;
	Unicode aUStack_369[301];
	uint32_t uStack_10f;
	int iStack_10a;
	char acStack_104[260];

	iVar6 = 0;
	local_380 = 0;
	local_37c = 0xffffffff;
	dword_6FBB5F79 = 0xffffffff;
	iVar2 = FOG_IsExpansion();
	if (((iVar2 == 0) || (iVar2 = sub_6FAAC080(), iVar2 == 0)) && (a1 == 4))
	{
		return;
	}
	iVar2 = *(int*)(byte_6FB7D900 + a1 * 8);
	if (iVar2 <= *(int*)(byte_6FB7D904 + a1 * 8))
	{
		do
		{
			if ((&dword_6FBB5FA1)[iVar2] == 0)
			{
				sprintf(acStack_104, "%s\\ui\\menu\\%s", "DATA\\GLOBAL",
				    (&gpuint8_t_6FB7D130)[iVar2]);
				pDVar3 = CLIENT_LoadCellFile(acStack_104, 0);
				(&dword_6FBB5FA1)[iVar2] = (uint32_t)(pDVar3);
			}
			iVar2 = iVar2 + 1;
		} while (iVar2 <= *(int*)(byte_6FB7D904 + a1 * 8));
	}
	uVar1 = *(uint32_t*)(byte_6FBB5F40 + a1 * 4);
	if (*(uint32_t*)(byte_6FBB5F40 + a1 * 4) == 0xffffffff)
	{
		pbVar5 = &byte_6FB7D929;
		uVar4 = dword_6FBB5F79;
		do
		{
			if (((pbVar5[2] == a1) && (pbVar5[-1] != 0)) &&
			    ((*pbVar5 < 0x1b && ((&dword_6FBB5FA1)[*pbVar5] != 0))))
			{
				uStack_36f = *(uint32_t*)(pbVar5 + 0xb);
				sub_6FB04D50((int)&uStack_370);
				if (((*(uint8_t*)((uint8_t*)&uStack_10f + 2)) != '\0') || (iStack_10a == 0))
				{
					iVar6 = 0x29;
					dword_6FBB5F79 = uStack_10f & 0xff;
				}
				uVar4 = dword_6FBB5F79;
				if (iStack_10a == 1)
				{
				LAB_6fb0583a:
					if (((iStack_10a != 2) && (iStack_10a != 1)) && (local_37c == 0xffffffff))
					{
						local_37c = uStack_10f & 0xff;
					}
				}
				else if (iStack_10a != 2)
				{
					if (iStack_10a != 3)
						goto LAB_6fb0585d;
					goto LAB_6fb0583a;
				}
				local_380 = local_380 + 1;
			}
		LAB_6fb0585d:
			iVar6 = iVar6 + 1;
			if (0x28 < iVar6)
				goto LAB_6fb0586b;
			pbVar5 = pbVar5 + 0x10;
		} while (true);
	}
LAB_6fb05896:
	dword_6FBB5F79 = uVar1;
	if (a2 != 0)
	{
		*(uint32_t*)byte_6FBB5F40 = (uint32_t)0xffffffff;
		byte_6FBB5F44 = 0xffffffff;
		byte_6FBB5F48 = 0xffffffff;
		byte_6FBB5F4C = 0xffffffff;
		byte_6FBB5F50 = 0xffffffff;
	}
	return;
LAB_6fb0586b:
	uVar1 = dword_6FBB5F79;
	if (((local_380 != 0) && (uVar4 == 0xffffffff)) &&
	    ((uVar4 = *(uint32_t*)(byte_6FBB5F7D + a1 * 4),
	        *(uint32_t*)(byte_6FBB5F7D + a1 * 4) != 0xffffffff ||
	            (uVar4 = local_37c, local_37c != 0xffffffff))))
	{
		uVar1 = uVar4;
	}
	goto LAB_6fb05896;
}

//D2Client.0x6FB058D0
void __cdecl sub_6FB058D0()
{
	char cVar1;
	int iVar2;
	char* p2;
	char local_104[260];

	cVar1 = VIDEO_IsInVideoSequence();
	if (cVar1 == '\0')
	{
		if (gpCellFile_6FBB5F95 == nullptr)
		{
			sprintf(local_104, "%s\\ui\\menu\\questbackground", "DATA\\GLOBAL");
			gpCellFile_6FBB5F95 = CLIENT_LoadCellFile(local_104, 0);
		}
		if (gpCellFile_6FBB5F99 == nullptr)
		{
			iVar2 = FOG_IsExpansion();
			if ((iVar2 == 0) || (iVar2 = sub_6FAAC080(), iVar2 == 0))
			{
				p2 = "%s\\ui\\menu\\questtabs";
			}
			else
			{
				p2 = "%s\\ui\\menu\\expquesttabs";
			}
			sprintf(local_104, p2, "DATA\\GLOBAL");
			gpCellFile_6FBB5F99 = CLIENT_LoadCellFile(local_104, 0);
		}
		if (gpCellFile_6FBB5F91 == nullptr)
		{
			sprintf(local_104, "%s\\ui\\menu\\questsockets", "DATA\\GLOBAL");
			gpCellFile_6FBB5F91 = CLIENT_LoadCellFile(local_104, 0);
		}
		if (gpCellFile_6FBB5F9D == nullptr)
		{
			sprintf(local_104, "%s\\ui\\menu\\questdone", "DATA\\GLOBAL");
			gpCellFile_6FBB5F9D = CLIENT_LoadCellFile(local_104, 0);
		}
		if (gpCellFile_6FBB6011 == nullptr)
		{
			sprintf(local_104, "%s\\ui\\menu\\invps", "DATA\\GLOBAL");
			gpCellFile_6FBB6011 = CLIENT_LoadCellFile(local_104, 0);
		}
		if (gpCellFile_6FBB600D == nullptr)
		{
			sprintf(local_104, "%s\\ui\\menu\\questlast", "DATA\\GLOBAL");
			gpCellFile_6FBB600D = CLIENT_LoadCellFile(local_104, 0);
		}
		return;
	}
}

//D2Client.0x6FB05A30
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB05A30(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	char cVar1;
	D2GameResolutionMode DVar2;
	int iVar3;
	int iVar4;
	D2BitBufferStrc* pQuestRecord;
	int* piVar5;
	uint32_t uVar6;
	uint32_t extraout_ECX;
	uint32_t uVar7;
	int iVar8;
	char* pcVar9;

	uVar7 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar6 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	cVar1 = VIDEO_IsInVideoSequence();
	if (cVar1 != '\0')
	{
		return;
	}
	if (gnScreenWidth / 2 < (int)uVar7)
	{
		return;
	}
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		iVar3 = gnScreenHeight + -0x2f;
	}
	else
	{
		iVar3 = gnScreenHeight + -0x31;
	}
	if (iVar3 < (int)uVar6)
	{
		return;
	}
	iVar8 = uVar7 - dword_6FBBA748;
	iVar3 = uVar6 + dword_6FBBA74C;
	if (byte_6FBB5F73 != '\0')
		goto LAB_6fb05c13;
	if ((((-1 < iVar3) && (iVar3 < 0x1c)) && (-1 < iVar8)) && (iVar8 < 0x140))
	{
		iVar4 = FOG_IsExpansion();
		if ((iVar4 == 0) || (iVar4 = sub_6FAAC080(), iVar4 == 0))
		{
			uVar6 = 0;
			iVar4 = 0;
			do
			{
				if ((iVar4 <= iVar8) && (iVar8 <= iVar4 + 0x50))
					goto LAB_6fb05b1c;
				iVar4 = iVar4 + 0x50;
				uVar6 = uVar6 + 1;
			} while (iVar4 < 0x140);
		}
		else
		{
			uVar6 = 0;
			iVar4 = 0;
			do
			{
				if ((iVar4 <= iVar8) && (iVar8 <= iVar4 + 0x40))
					goto LAB_6fb05b1c;
				iVar4 = iVar4 + 0x40;
				uVar6 = uVar6 + 1;
			} while (iVar4 < 0x140);
		}
	}
LAB_6fb05c32:
	D2_ASSERT(6 >= dword_6FBB5F60);
	uVar6 = 0;
	if (0 < (int)dword_6FBB5F60)
	{
		piVar5 = (int*)("A");
		do
		{
			if ((((piVar5[-1] <= iVar8) && (iVar8 < piVar5[-1] + 0x38)) && (*piVar5 <= iVar3)) &&
			    (iVar3 < *piVar5 + 0x34))
			{
				if ((uVar6 != 0xffffffff) && ((int)uVar6 < (int)dword_6FBB5F60))
				{
					iVar3 = 0;
					pcVar9 = (char*)(&byte_6FBB62CD);
					uVar7 = dword_6FBB5F60;
					do
					{
						if ((uVar6 == (uint8_t)pcVar9[-3]) && (*pcVar9 != '\0'))
						{
							byte_6FBB5F71 = 1;
							dword_6FBB5F75 = uVar6;
							sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
							uVar7 = dword_6FBB5F60;
						}
						iVar3 = iVar3 + 1;
						pcVar9 = pcVar9 + 0x26a;
					} while (iVar3 < (int)uVar7);
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					return;
				}
				break;
			}
			uVar6 = uVar6 + 1;
			piVar5 = piVar5 + 4;
		} while ((int)uVar6 < (int)dword_6FBB5F60);
	}
	if ((((iVar8 < 0x116) || (0x139 < iVar8)) || (iVar3 < 0x188)) || (0x1a9 < iVar3))
	{
		if (((iVar8 < 0xe6) || (0x103 < iVar8)) || ((iVar3 < 0x187 || (0x1a7 < iVar3))))
			goto LAB_6fb05c13;
		byte_6FBB5F74 = '\x01';
	}
	else
	{
		byte_6FBB5F72 = '\x01';
	}
	sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
LAB_6fb05c13:
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	return;
LAB_6fb05b1c:
	if (uVar6 != 0xffffffff)
	{
		if (((int)uVar6 < 5) && (uVar6 != dword_6FBB6F15))
		{
			iVar3 = FOG_IsExpansion();
			if (((iVar3 == 0) || (iVar3 = sub_6FAAC080(), iVar3 == 0)) && (uVar6 == 4))
			{
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			iVar3 = 0;
			if (0 < (int)dword_6FBB5F60)
			{
				piVar5 = (int*)((int)&dword_6FBB6069 + 1);
				do
				{
					if (*(int*)((int)piVar5 + 0x265) == 0)
					{
						pQuestRecord = sub_6FAFBD20();
						QUESTRECORD_SetQuestState(pQuestRecord, *piVar5, 0xc);
						sub_6FAAD990(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x58), (short)*piVar5);
					}
					iVar3 = iVar3 + 1;
					piVar5 = (int*)((int)piVar5 + 0x26a);
				} while (iVar3 < (int)dword_6FBB5F60);
			}
			sub_6FB05D80(uVar6);
			sub_6FB056D0(dword_6FBB6F15, 1);
			byte_6FBB5F71 = 0;
			byte_6FBB5F72 = '\0';
			byte_6FBB5F70 = 0;
			dword_6FBB5F75 = 0xffffffff;
			byte_6FBB5F74 = '\0';
			byte_6FBB6F1D = 0;
			byte_6FBB6F1E = 0;
			byte_6FBB6F1F = 0;
			byte_6FBB6F20 = 0;
		}
		goto LAB_6fb05c13;
	}
	goto LAB_6fb05c32;
}

//D2Client.0x6FB05D80
void __fastcall sub_6FB05D80(int a1)
{
	D2BitBufferStrc* pDVar1;
	uint32_t* puVar2;
	int iVar3;
	int iVar4;

	if (4 < a1)
	{
		a1 = 0;
	}
	switch (a1)
	{
	case 4:
		iVar4 = 0;
		iVar3 = 0x1a;
		pDVar1 = sub_6FAFBD20();
		iVar3 = QUESTRECORD_GetQuestState(pDVar1, iVar3, iVar4);
		if (iVar3 == 0)
		{
			a1 = 3;
		}
	case 3:
		iVar4 = 0;
		iVar3 = 0x17;
		pDVar1 = sub_6FAFBD20();
		iVar3 = QUESTRECORD_GetQuestState(pDVar1, iVar3, iVar4);
		if (iVar3 == 0)
		{
			a1 = 2;
		}
	case 2:
		iVar4 = 0;
		iVar3 = 0xf;
		pDVar1 = sub_6FAFBD20();
		iVar3 = QUESTRECORD_GetQuestState(pDVar1, iVar3, iVar4);
		if (iVar3 == 0)
		{
			a1 = 1;
		}
	case 1:
		iVar4 = 0;
		iVar3 = 7;
		pDVar1 = sub_6FAFBD20();
		iVar3 = QUESTRECORD_GetQuestState(pDVar1, iVar3, iVar4);
		if (iVar3 == 0)
		{
			a1 = 0;
		}
	default:
		dword_6FBB5F79 = 0xffffffff;
		puVar2 = &dword_6FBB6EFD;
		dword_6FBB6F15 = a1;
		do
		{
			puVar2[-6] = 0;
			*puVar2 = 0;
			puVar2 = puVar2 + 1;
		} while ((int)puVar2 < (int)&dword_6FBB6F15);
		dword_6FBB5F75 = 0xffffffff;
		return;
	}
}

//D2Client.0x6FB05E40
void __cdecl sub_6FB05E40(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	short sVar1;
	int iVar2;
	D2GameResolutionMode DVar3;
	uint32_t uVar4;
	int* piVar5;
	uint8_t* pbVar6;
	uint32_t uVar7;
	int iVar8;
	bool bVar9;
	bool bVar10;

	iVar2 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam - dword_6FBBA748;
	iVar8 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2) + dword_6FBBA74C;
	if (byte_6FBB5F72 == '\0')
	{
		if (byte_6FBB5F73 == '\0')
		{
			if (dword_6FBB5F75 == 0xffffffff)
			{
				if ((((byte_6FBB5F74 == '\x01') && (0xe5 < iVar2)) && (iVar2 < 0x104)) &&
				    (((0x186 < iVar8 && (iVar8 < 0x1a8)) &&
				        ((dword_6FBB5F79 != 0xffffffff && (iVar2 = 0, 0 < (int)dword_6FBB5F60))))))
				{
					pbVar6 = &byte_6FBB62CA;
					do
					{
						if (*pbVar6 == dword_6FBB5F79)
						{
							if (iVar2 != -1)
							{
								sVar1 = *(short*)(iVar2 * 0x26a + (int)&tbl_6FBB62C8);
								if ((sVar1 != 0xe8c) && (sVar1 != 0xe8d))
								{
									sub_6FB1D110(CONCAT22((short)((uint32_t)(iVar2 * 0x135) >> 0x10), sVar1), 1, 0);
									sub_6FB1CBD0((uint8_t*)(sub_6FB060A0), 0);
									byte_6FBB5F73 = '\x01';
								}
							}
							break;
						}
						iVar2 = iVar2 + 1;
						pbVar6 = pbVar6 + 0x26a;
					} while (iVar2 < (int)dword_6FBB5F60);
				}
			}
			else
			{
				D2_ASSERT(6 >= dword_6FBB5F60);
				uVar4 = 0;
				if (0 < (int)dword_6FBB5F60)
				{
					piVar5 = (int*)("A");
					do
					{
						if ((((piVar5[-1] <= iVar2) && (iVar2 < piVar5[-1] + 0x38)) && (*piVar5 <= iVar8)) &&
						    (iVar8 < *piVar5 + 0x34))
							goto LAB_6fb05f19;
						uVar4 = uVar4 + 1;
						piVar5 = piVar5 + 4;
					} while ((int)uVar4 < (int)dword_6FBB5F60);
				}
				uVar4 = 0xffffffff;
			LAB_6fb05f19:
				if (uVar4 == dword_6FBB5F75)
				{
					*(uint32_t*)(byte_6FBB5F7D + dword_6FBB6F15 * 4) = uVar4;
					dword_6FBB5F79 = uVar4;
				}
			}
		}
	}
	else if (((0x115 < iVar2) && (iVar2 < 0x13a)) && ((0x187 < iVar8 && (iVar8 < 0x1aa))))
	{
		sub_6FB06120(0);
	}
	byte_6FBB5F71 = 0;
	byte_6FBB5F72 = '\0';
	byte_6FBB5F70 = 0;
	dword_6FBB5F75 = 0xffffffff;
	byte_6FBB5F74 = '\0';
	byte_6FBB6F1D = 0;
	byte_6FBB6F1E = 0;
	byte_6FBB6F1F = 0;
	byte_6FBB6F20 = 0;
	if ((int)(uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam <= gnScreenWidth / 2)
	{
		DVar3 = D2GFX_GetResolutionMode();
		if (DVar3 == NUM_GAME_RESOLUTIONS)
		{
			uVar4 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
			uVar7 = gnScreenHeight - 0x2f;
			bVar10 = SBORROW4(uVar4, uVar7);
			iVar2 = uVar4 - uVar7;
			bVar9 = uVar4 == uVar7;
		}
		else
		{
			uVar7 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
			uVar4 = gnScreenHeight - 0x31;
			bVar10 = SBORROW4(uVar7, uVar4);
			iVar2 = uVar7 - uVar4;
			bVar9 = uVar7 == uVar4;
		}
		if (bVar9 || bVar10 != iVar2 < 0)
		{
			sub_6FAABF60();
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
	}
}

//D2Client.0x6FB060A0
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FB060A0(uint32_t a1)
{
	uint32_t in_ECX;

	byte_6FBB5F73 = '\0';
	sub_6FB1CBD0(0, in_ECX);
	return 0;
}

//D2Client.0x6FB060C0
void __cdecl sub_6FB060C0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	if (dword_6FBB5F58 == 2)
	{
		dword_6FBB5F58 = 0;
		byte_6FBB5F70 = 0;
		byte_6FBB5F73 = '\0';
	}
	sub_6FB04220();
	sub_6FB23260(0xf, 1, 1);
	byte_6FBB6F19 = GetTickCount();
}

//D2Client.0x6FB06120
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB06120(int a1)
{
	bool bVar1;
	char cVar2;
	uint8_t bVar3;
	DWORD DVar4;
	uint32_t extraout_var;
	int iVar5;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar6;

	if (dword_6FBB5F58 == 0)
	{
		DVar4 = GetTickCount();
		if (DVar4 - byte_6FBB6F19 < 0xfa)
		{
			return;
		}
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) != 0)
		{
			return;
		}
	}
	else
	{
		if (dword_6FBB5F58 != 1)
		{
			if (dword_6FBB5F58 == 2)
			{
				dword_6FBB5F58 = 0;
				byte_6FBB5F70 = 0;
				byte_6FBB5F73 = '\0';
			}
			sub_6FB04220();
			sub_6FB23260(0xf, 1, a1);
			byte_6FBB6F19 = GetTickCount();
			sub_6FB1AE00();
			return;
		}
		dword_6FBB5F58 = 0;
	}
	cVar2 = VIDEO_IsInVideoSequence();
	if (cVar2 != '\0')
	{
		return;
	}
	iVar5 = sub_6FB23260(0xf, 0, a1);
	if (iVar5 == 1)
	{
		sub_6FB058D0();
		dword_6FBB5F58 = 2;
		pUnit = CUNIT_GetPlayer();
		if (((pUnit == nullptr) ||
		        (pRoom = UNITS_GetRoom(pUnit), pRoom == nullptr)) ||
		    (iVar5 = DUNGEON_GetLevelIdFromRoom(pRoom), iVar5 == 0))
		{
			uVar6 = 0;
		}
		else
		{
			bVar3 = DRLG_GetActNoFromLevelId(iVar5);
			uVar6 = (uint32_t)bVar3;
		}
		sub_6FB05D80(uVar6);
		sub_6FB056D0(dword_6FBB6F15, 0);
		CLIENT_SendSimpleMessage(0x40);
		return;
	}
}

//D2Client.0x6FB06230
void __fastcall sub_6FB06230(uint32_t* a1)
{
	char cVar1;
	int iVar2;
	uint32_t* puVar3;

	puVar3 = (uint32_t*)&byte_6FBB6015;
	for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = *a1;
		a1 = a1 + 1;
		puVar3 = puVar3 + 1;
	}
	*(uint16_t*)puVar3 = *(uint16_t*)a1;
	byte_6FBB5F70 = 0;
	cVar1 = VIDEO_IsInVideoSequence();
	if (cVar1 == '\0')
	{
		if (dword_6FBB5F58 == 2)
		{
			sub_6FB058D0();
		}
		sub_6FB056D0(dword_6FBB6F15, 1);
		return;
	}
}

//D2Client.0x6FB06280
void __fastcall sub_6FB06280(int a1)
{
	if (*(short*)(a1 + 1) == 1)
	{
		dword_6FBB5F64 = (int)*(uint16_t*)(a1 + 3);
		dword_6FBB5F68 = (uint32_t) * (uint16_t*)(a1 + 5);
		dword_6FBB5F6C = (int)*(uint16_t*)(a1 + 7);
	}
}

//D2Client.0x6FB062B0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB062B0()
{
	D2BitBufferStrc* pQuestRecord;
	uint32_t extraout_ECX;
	int* piVar1;
	int iVar2;

	if (((int)dword_6FBB6F15 < 5) && (iVar2 = 0, 0 < (int)dword_6FBB5F60))
	{
		piVar1 = (int*)((int)&dword_6FBB6069 + 1);
		do
		{
			if (*(int*)((int)piVar1 + 0x265) == 0)
			{
				pQuestRecord = sub_6FAFBD20();
				QUESTRECORD_SetQuestState(pQuestRecord, *piVar1, 0xc);
				sub_6FAAD990(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x58), (short)*piVar1);
			}
			iVar2 = iVar2 + 1;
			piVar1 = (int*)((int)piVar1 + 0x26a);
		} while (iVar2 < (int)dword_6FBB5F60);
	}
	byte_6FBB5F70 = 0;
	dword_6FBB5F58 = 0;
	byte_6FBB5F73 = '\0';
	sub_6FB04220();
}

//D2Client.0x6FB06320
void __cdecl sub_6FB06320(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	D2GameResolutionMode DVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;

	uVar7 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar6 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	iVar1 = sub_6FAB5750();
	iVar2 = sub_6FB23230(6);
	if (iVar2 == 0)
	{
	LAB_6fb063c6:
		DVar3 = D2GFX_GetResolutionMode();
		if (iVar1 == 2)
		{
			if (DVar3 == NUM_GAME_RESOLUTIONS)
			{
			LAB_6fb063e4:
				uVar4 = 1;
			}
			else
			{
				iVar2 = sub_6FB23230(2);
				uVar4 = 3;
				if (iVar2 != 0)
					goto LAB_6fb063e4;
			}
			iVar2 = (gnScreenWidth + -0x280) / 2;
			goto LAB_6fb0638b;
		}
	}
	else
	{
		iVar2 = sub_6FB23230(2);
		if (iVar2 != 0)
			goto LAB_6fb063c6;
		DVar3 = D2GFX_GetResolutionMode();
		if (iVar1 == 2)
		{
			uVar4 = (uint32_t)(DVar3 != NUM_GAME_RESOLUTIONS) * 2 + 1;
			iVar2 = (gnScreenWidth + -0x280) / 2;
			goto LAB_6fb0638b;
		}
	}
	uVar4 = -(uint32_t)(DVar3 != NUM_GAME_RESOLUTIONS) & 2;
	iVar2 = 0;
LAB_6fb0638b:
	iVar5 = uVar4 * 0x14;
	if (iVar1 == 2)
	{
		iVar1 = (gnScreenWidth + -0x280) / 2;
	}
	else
	{
		iVar1 = 0;
	}
	if ((((*(int*)(byte_6FB7D0E0 + iVar5) + iVar2 < (int)uVar7) &&
	         ((int)uVar7 < *(int*)(byte_6FB7D0E4 + iVar5) + iVar1)) &&
	        (*(int*)(byte_6FB7D0E8 + iVar5) + -0x1e0 + gnScreenHeight < (int)uVar6)) &&
	    ((int)uVar6 < *(int*)(byte_6FB7D0EC + iVar5) + -0x1e0 + gnScreenHeight))
	{
		byte_6FBB5F70 = 1;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	byte_6FBB5F70 = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FB06480
void __cdecl sub_6FB06480(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	D2GameResolutionMode DVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;

	uVar7 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar6 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	iVar1 = sub_6FAB5750();
	iVar2 = sub_6FB23230(6);
	if (iVar2 == 0)
	{
	LAB_6fb06526:
		DVar3 = D2GFX_GetResolutionMode();
		if (iVar1 == 2)
		{
			if (DVar3 == NUM_GAME_RESOLUTIONS)
			{
			LAB_6fb06544:
				uVar4 = 1;
			}
			else
			{
				iVar2 = sub_6FB23230(2);
				uVar4 = 3;
				if (iVar2 != 0)
					goto LAB_6fb06544;
			}
			iVar2 = (gnScreenWidth + -0x280) / 2;
			goto LAB_6fb064eb;
		}
	}
	else
	{
		iVar2 = sub_6FB23230(2);
		if (iVar2 != 0)
			goto LAB_6fb06526;
		DVar3 = D2GFX_GetResolutionMode();
		if (iVar1 == 2)
		{
			uVar4 = (uint32_t)(DVar3 != NUM_GAME_RESOLUTIONS) * 2 + 1;
			iVar2 = (gnScreenWidth + -0x280) / 2;
			goto LAB_6fb064eb;
		}
	}
	uVar4 = -(uint32_t)(DVar3 != NUM_GAME_RESOLUTIONS) & 2;
	iVar2 = 0;
LAB_6fb064eb:
	iVar5 = uVar4 * 0x14;
	if (iVar1 == 2)
	{
		iVar1 = (gnScreenWidth + -0x280) / 2;
	}
	else
	{
		iVar1 = 0;
	}
	if ((((*(int*)(byte_6FB7D0E0 + iVar5) + iVar2 < (int)uVar7) &&
	         ((int)uVar7 < *(int*)(byte_6FB7D0E4 + iVar5) + iVar1)) &&
	        (*(int*)(byte_6FB7D0E8 + iVar5) + -0x1e0 + gnScreenHeight < (int)uVar6)) &&
	    (((int)uVar6 < *(int*)(byte_6FB7D0EC + iVar5) + -0x1e0 + gnScreenHeight &&
	        (byte_6FBB5F70 != '\0'))))
	{
		sub_6FB23260(0x11, 1, 0);
		sub_6FB06120(0);
		byte_6FBB5F70 = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	byte_6FBB5F70 = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FB065F0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB065F0()
{
	bool bVar1;
	uint32_t extraout_var;
	int iVar2;
	int iVar3;
	D2GameResolutionMode DVar4;
	D2CellFileStrc* pCelFile;
	Unicode* pUVar5;
	int iVar6;
	int iVar7;
	uint32_t uVar8;
	int iVar9;
	int iVar10;
	D2GfxDataStrc* pDVar11;
	int iVar12;
	D2GfxDataStrc local_48;

	bVar1 = sub_6FB283E0();
	if (D2C_ZEXT(bVar1) != 0)
	{
		sub_6FB23260(0x11, 1, 0);
		if (dword_6FBB5F58 != 1)
		{
			return;
		}
		byte_6FBB5F70 = 0;
		dword_6FBB5F58 = 0;
		return;
	}
	iVar2 = sub_6FAB5750();
	if (iVar2 == 3)
	{
		return;
	}
	iVar3 = sub_6FB23230(0xf);
	if (iVar3 != 0)
	{
		return;
	}
	pDVar11 = &local_48;
	for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		pDVar11->pCurrentCell = nullptr;
		pDVar11 = (D2GfxDataStrc*)&pDVar11->pCellFile;
	}
	local_48.nDirection = 0;
	local_48.pCellFile = gpCellFile_6FBB5BB8;
	local_48.nFrame = 0;
	iVar3 = sub_6FB23230(6);
	if ((iVar3 == 0) || (iVar3 = sub_6FB23230(2), iVar3 != 0))
	{
		DVar4 = D2GFX_GetResolutionMode();
		if (iVar2 != 2)
			goto LAB_6fb066d0;
		if ((DVar4 == NUM_GAME_RESOLUTIONS) || (iVar2 = sub_6FB23230(2), iVar2 != 0))
		{
			uVar8 = 1;
		}
		else
		{
			uVar8 = 3;
		}
	}
	else
	{
		DVar4 = D2GFX_GetResolutionMode();
		if (iVar2 == 2)
		{
			uVar8 = (uint32_t)(DVar4 != NUM_GAME_RESOLUTIONS) * 2 + 1;
		}
		else
		{
		LAB_6fb066d0:
			uVar8 = -(uint32_t)(DVar4 != NUM_GAME_RESOLUTIONS) & 2;
		}
	}
	pCelFile = D2CMP_CelGetHandle(&local_48);
	iVar2 = D2CMP_CelGetWidth(pCelFile);
	pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf58));
	iVar3 = D2Win_10121_GetTextWidth(pUVar5);
	iVar10 = uVar8 * 0x14;
	iVar2 = (iVar2 / 2 - iVar3 / 2) + 1 + *(int*)(byte_6FB7D0E0 + iVar10);
	iVar3 = *(int*)(byte_6FB7D0F0 + iVar10) + -0x1e0 + gnScreenHeight;
	iVar6 = sub_6FAB5750();
	if (iVar6 == 2)
	{
		iVar2 = iVar2 + (gnScreenWidth + -0x280) / 2;
	}
	iVar12 = 0;
	iVar6 = 0;
	pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf58));
	D2Win_10117_DrawText(pUVar5, iVar2, iVar3, iVar6, iVar12);
	iVar3 = *(int*)(byte_6FB7D0E0 + iVar10);
	iVar2 = *(int*)(byte_6FB7D0EC + iVar10) + -0x1e0 + gnScreenHeight;
	iVar6 = sub_6FAB5750();
	if (iVar6 == 2)
	{
		iVar3 = iVar3 + (gnScreenWidth + -0x280) / 2;
	}
	TEXTURE_CelDraw(&local_48, iVar3, iVar2, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.pCellFile = gpCellFile_6FBB5BB4;
	if (byte_6FBB5F70 != '\0')
	{
		iVar6 = sub_6FB57BD0();
		iVar10 = sub_6FB57BC0();
		iVar12 = sub_6FAB5750();
		iVar7 = sub_6FB23230(6);
		if ((iVar7 == 0) || (iVar7 = sub_6FB23230(2), iVar7 != 0))
		{
			DVar4 = D2GFX_GetResolutionMode();
			if (iVar12 != 2)
				goto LAB_6fb0681b;
			if (DVar4 != NUM_GAME_RESOLUTIONS)
			{
				iVar7 = sub_6FB23230(2);
				uVar8 = 3;
				if (iVar7 == 0)
					goto LAB_6fb06885;
			}
			uVar8 = 1;
		LAB_6fb06885:
			iVar7 = (gnScreenWidth + -0x280) / 2;
		}
		else
		{
			DVar4 = D2GFX_GetResolutionMode();
			if (iVar12 == 2)
			{
				uVar8 = (uint32_t)(DVar4 != NUM_GAME_RESOLUTIONS) * 2 + 1;
				goto LAB_6fb06885;
			}
		LAB_6fb0681b:
			uVar8 = -(uint32_t)(DVar4 != NUM_GAME_RESOLUTIONS) & 2;
			iVar7 = 0;
		}
		iVar9 = uVar8 * 0x14;
		if (iVar12 == 2)
		{
			iVar12 = (gnScreenWidth + -0x280) / 2;
		}
		else
		{
			iVar12 = 0;
		}
		if ((((*(int*)(byte_6FB7D0E0 + iVar9) + iVar7 < iVar10) &&
		         (iVar10 < *(int*)(byte_6FB7D0E4 + iVar9) + iVar12)) &&
		        (*(int*)(byte_6FB7D0E8 + iVar9) + -0x1e0 + gnScreenHeight < iVar6)) &&
		    (local_48.nFrame = 1, iVar6 < *(int*)(byte_6FB7D0EC + iVar9) + -0x1e0 + gnScreenHeight))
			goto LAB_6fb068d7;
	}
	local_48.nFrame = 0;
LAB_6fb068d7:
	TEXTURE_CelDraw(&local_48, iVar3 + 3, iVar2 + -4, 0xffffffff, DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FB06900
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB06900(uint32_t a1, int a2)
{
	uint8_t bVar1;
	Unicode* pUVar2;
	int iVar3;
	uint32_t* puVar4;
	D2BitBufferStrc* pQuestRecord;
	int* piVar5;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;

	iVar3 = dword_6FBB5F64;
	if (a2 != 0)
	{
		bVar1 = *(uint8_t*)(a2 + 2);
		if ((bVar1 & 1) != 0)
		{
			switch (*(uint8_t*)(a2 + 1))
			{
			case 3:
				pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe7c));
				sub_6FB1C600(pUVar2, extraout_EDX & 0xffffff00);
				return;
			case 4:
				sub_6FB29750((uint8_t*)(sub_6FB06CE0));
				return;
			default:
				return;
			case 10:
				sub_6FAA9260();
				return;
			case 0xd:
				sub_6FB5CC40(0xd3, 1);
				return;
			case 0xf:
				pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe7e));
				sub_6FB1C600(pUVar2, extraout_EDX_00 & 0xffffff00);
				return;
			case 0x17:
				sub_6FAAB240();
				return;
			case 0x21:
				sub_6FB55820(0xed, nullptr, 0.0, 0.0, 0);
				return;
			}
		}
		if ((bVar1 & 2) != 0)
		{
			switch (*(uint8_t*)(a2 + 1))
			{
			case 4:
				sub_6FB55820(0xf1, nullptr, 0.0, 0.0, 0);
				return;
			default:
				return;
			case 8:
			case 0xf:
			case 0x12:
			case 0x16:
			case 0x23:
				sub_6FB55820(7, nullptr, 0.0, 0.0, 0);
				return;
			case 0x17:
				goto switchD_6fb069c2_caseD_17;
			case 0x20:
				sub_6FB55820(0xd9, nullptr, 0.0, 0.0, 0);
				return;
			case 0x21:
				sub_6FB55820(0xf3, nullptr, 0.0, 0.0, 0);
				return;
			case 0x24:
				sub_6FAAB350(1);
				return;
			}
		}
		if (bVar1 == 0x10)
		{
			if (*(char*)(a2 + 1) == '\n')
			{
				sub_6FB55820(0x998, nullptr, 0.0, 0.0, 0);
				sub_6FB55820(0x9aa, nullptr, 0.0, 0.0, 0);
				return;
			}
			if (*(char*)(a2 + 1) != '!')
			{
				return;
			}
			sub_6FB55820((int)*(short*)(a2 + 4), nullptr, 0.0, 0.0, 0);
			return;
		}
		if ((bVar1 & 0x20) != 0)
		{
			if (*(char*)(a2 + 1) != ' ')
			{
				if (*(char*)(a2 + 1) == '!')
				{
					sub_6FB29750((uint8_t*)(sub_6FB06D00));
					return;
				}
				pQuestRecord = sub_6FAFBD20();
				if ((pQuestRecord != nullptr) &&
				    (iVar3 = QUESTRECORD_GetQuestState(pQuestRecord, 1, 0), iVar3 != 0))
				{
					return;
				}
				iVar3 = QUESTRECORD_GetQuestState(pQuestRecord, 1, 1);
				if (iVar3 != 0)
				{
					return;
				}
				dword_6FBB5F64 = (int)*(short*)(a2 + 4);
				if ((dword_6FBB5F64 < 6) && (-1 < dword_6FBB5F64))
				{
					if (dword_6FBB5F64 == 5)
					{
						iVar3 = 5;
						if (*(char*)(a2 + 1) == '\x17')
						{
							iVar3 = 1;
							if (0 < *(short*)(a2 + 4))
							{
								iVar3 = (int)*(short*)(a2 + 4);
							}
							sub_6FABA5C0(iVar3);
							return;
						}
						goto LAB_6fb06aa7;
					}
				}
				else
				{
					dword_6FBB5F64 = 0x29a;
				}
				iVar3 = 0;
				piVar5 = (int*)("%");
				do
				{
					if (*piVar5 == 1)
						goto LAB_6fb06b73;
					piVar5 = piVar5 + 4;
					iVar3 = iVar3 + 1;
				} while ((int)piVar5 < (int)&dword_6FB7DBC0);
				iVar3 = -1;
			LAB_6fb06b73:
				(&byte_6FBB6016)[iVar3] = *(uint8_t*)(a2 + 3);
				return;
			}
			dword_6FBB5F6C = (int)*(short*)(a2 + 4);
		}
	}
LAB_6fb06aa7:
	dword_6FBB5F64 = iVar3;
	if (dword_6FBB5F58 == 0)
	{
		iVar3 = sub_6FB23260(0x11, 0, 0);
		if (iVar3 == 1)
		{
			iVar3 = 0;
			puVar4 = (uint32_t*)("%");
			do
			{
				if (*puVar4 == (uint32_t) * (uint8_t*)(a2 + 1))
				{
					if (iVar3 != -1)
					{
						*(uint32_t*)(byte_6FBB5F40 + (uint32_t)(uint8_t)byte_6FB7D92B[iVar3 * 0x10] * 4) =
						    (uint32_t)(uint8_t)(&byte_6FB7D92A)[iVar3 * 0x10];
					}
					dword_6FBB5F58 = 1;
					return;
				}
				puVar4 = puVar4 + 4;
				iVar3 = iVar3 + 1;
			} while ((int)puVar4 < (int)&dword_6FB7DBC0);
			dword_6FBB5F58 = 1;
			return;
		}
	}
	else
	{
		iVar3 = sub_6FB23230(0xf);
		if (iVar3 != 0)
		{
			iVar3 = 0;
			puVar4 = (uint32_t*)("%");
			while (*puVar4 != (uint32_t) * (uint8_t*)(a2 + 1))
			{
				puVar4 = puVar4 + 4;
				iVar3 = iVar3 + 1;
				if ((int)&tbl_6FB7DBBF < (int)puVar4)
				{
					return;
				}
			}
			if (iVar3 != -1)
			{
				if (0xd < *(uint8_t*)(a2 + 3))
				{
					FOG_Trace("Bad ptCmd->bNewStatus = %d for %d alert %d\n", (uint32_t) * (uint8_t*)(a2 + 3),
					    (uint32_t) * (uint8_t*)(a2 + 1), (uint32_t) * (uint8_t*)(a2 + 2));
				}
				(&byte_6FBB6016)[iVar3] = *(uint8_t*)(a2 + 3);
				if ((byte_6FBB5F73 == '\0') &&
				    ((uint8_t)byte_6FB7D92B[iVar3 * 0x10] == dword_6FBB6F15))
				{
					dword_6FBB5F79 = (uint32_t)(uint8_t)(&byte_6FB7D92A)[iVar3 * 0x10];
				}
			}
		}
	}
	return;
switchD_6fb069c2_caseD_17:
	iVar3 = sub_6FAAC080();
	if (iVar3 != 0)
	{
		VIDEO_SetChainExpansionIntro();
		return;
	}
	sub_6FAAB1F0();
	VIDEO_SetReplayedFromQuestLog();
}

//D2Client.0x6FB06CE0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB06CE0()
{
	int in_ECX;

	if ((in_ECX != 0) && (*(int*)(in_ECX + 4) == 0x92))
	{
		*(uint32_t*)(in_ECX + 0xc4) = *(uint32_t*)(in_ECX + 0xc4) & 0xfffffffd;
	}
}

//D2Client.0x6FB06D00
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB06D00()
{
	int in_ECX;

	if ((in_ECX != 0) && (*(int*)(in_ECX + 4) == 0x20f))
	{
		*(uint32_t*)(in_ECX + 0xc4) = *(uint32_t*)(in_ECX + 0xc4) & 0xfffffffd;
	}
}

//D2Client.0x6FB06D20
void __cdecl sub_6FB06D20()
{
	if (dword_6FBB5F58 == 1)
	{
		dword_6FBB5F58 = 0;
	}
}

//D2Client.0x6FB06D40
void __cdecl sub_6FB06D40()
{
	int iVar1;

	iVar1 = 0;
	do
	{
		(&byte_6FBB6016)[iVar1] = 0;
		(&byte_6FBB6040)[iVar1] = 0;
		iVar1 = iVar1 + 1;
	} while (iVar1 < 0x29);
}

//D2Client.0x6FB06D60
void __cdecl sub_6FB06D60()
{
	*(uint32_t*)byte_6FBB5F40 = (uint32_t)0xffffffff;
	byte_6FBB5F44 = 0xffffffff;
	byte_6FBB5F48 = 0xffffffff;
	byte_6FBB5F4C = 0xffffffff;
	byte_6FBB5F50 = 0xffffffff;
}

//D2Client.0x6FB06D80
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB06D80(int a1)
{
	int iVar1;
	uint8_t uVar2;
	uint32_t extraout_var;
	uint32_t uVar3;
	D2BitBufferStrc* pDVar4;
	int iVar5;
	int* piVar6;
	Unicode* pThis;
	int iVar7;
	uint8_t uStack_26c;
	int iStack_26b;
	Unicode aUStack_265[303];
	uint8_t bStack_7;

	uVar2 = D2Client_10002(0, a1);
	if (D2C_ZEXT(uVar2) != 0)
	{
		uVar3 = 0;
		piVar6 = (int*)("%");
		do
		{
			if (*piVar6 == a1)
			{
				iVar1 = (&dword_6FB7D934)[uVar3 * 4];
				if (iVar1 == 0x29)
				{
					return 0;
				}
				pDVar4 = sub_6FAFBD30();
				if (pDVar4 == nullptr)
				{
					return 0;
				}
				iVar7 = 0xd;
				iVar5 = iVar1;
				pDVar4 = sub_6FAFBD30();
				iVar5 = QUESTRECORD_GetQuestState(pDVar4, iVar5, iVar7);
				if (iVar5 != 0)
				{
					return 0;
				}
				pDVar4 = sub_6FAFBD20();
				if (pDVar4 == nullptr)
				{
					return 0;
				}
				iVar7 = 1;
				iVar5 = iVar1;
				pDVar4 = sub_6FAFBD20();
				iVar5 = QUESTRECORD_GetQuestState(pDVar4, iVar5, iVar7);
				if (iVar5 != 0)
				{
					return 0;
				}
				iVar7 = iVar1;
				pDVar4 = sub_6FAFBD20();
				iVar5 = QUESTRECORD_GetQuestState(pDVar4, iVar7, iVar5);
				if (iVar5 != 0)
				{
					return 0;
				}
				iVar7 = 0xe;
				iVar5 = iVar1;
				pDVar4 = sub_6FAFBD20();
				iVar5 = QUESTRECORD_GetQuestState(pDVar4, iVar5, iVar7);
				if (iVar5 != 0)
				{
					return 0;
				}
				if (a1 == 1)
				{
					iStack_26b = iVar1;
					sub_6FB04D50((int)&uStack_26c);
					if (4 < bStack_7)
					{
						return 0;
					}
				}
				return 1;
			}
			uVar3 = uVar3 + 1;
			piVar6 = piVar6 + 4;
		} while (uVar3 < 0x29);
	}
	return 0;
}

//D2Client.0x6FB06E70
int32_t __cdecl sub_6FB06E70()
{
	if (byte_6FBB6F1D == '\0')
	{
		byte_6FBB6F1D = 1;
		sub_6FB5CC40(0xd3, 1);
		return 0;
	}
	return 0;
}

//D2Client.0x6FB06E90
int32_t __cdecl sub_6FB06E90()
{
	if (byte_6FBB6F1E == '\0')
	{
		byte_6FBB6F1E = 1;
		sub_6FB5CC40(0x219, 0);
		sub_6FB5CC40(0x21a, 0);
		sub_6FB5CC40(0x21b, 0);
		return 0;
	}
	return 0;
}

//D2Client.0x6FB06ED0
void __fastcall sub_6FB06ED0(uint32_t a1)
{
	byte_6FBB6F1F = 1;
	byte_6FBB6F25 = a1;
}

//D2Client.0x6FB06EE0
uint8_t __cdecl sub_6FB06EE0()
{
	return byte_6FBB6F1F;
}

//D2Client.0x6FB06EF0
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FB06EF0()
{
	uint32_t in_EAX;
	D2UnitStrc* pDVar1;

	pDVar1 = (D2UnitStrc*)CONCAT31((int32_t)((uint32_t)in_EAX >> 8), byte_6FBB6F20);
	if (byte_6FBB6F20 != '\0')
	{
		pDVar1 = sub_6FB26A60(dword_6FBB6F21, 1);
		if (pDVar1 != nullptr)
		{
			return CONCAT31((int32_t)((uint32_t)pDVar1 >> 8), 1);
		}
	}
	return (uint32_t)pDVar1 & 0xffffff00;
}

//D2Client.0x6FB06F20
// TODO: decompilation needs review (in_reg)
uint32_t __fastcall sub_6FB06F20(int a1, int a2)
{
	uint64_t uVar1;
	uint64_t DVar2;
	uint32_t in_EAX;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;

	uVar4 = CONCAT31((int32_t)((uint32_t)in_EAX >> 8), byte_6FBB6F1F);
	if (byte_6FBB6F1F != '\0')
	{
		pDVar3 = CUNIT_GetPlayer();
		DVar2 = (uint64_t)((uint64_t)(pDVar3->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar3->pSeed).nHighSeed);
		(*(uint64_t*)&pDVar3->pSeed) = DVar2;
		uVar6 = 0;
		uVar1 = (uint64_t)DVar2 & 0xffffffff;
		uVar4 = (uint32_t)(uVar1 / 3);
		iVar5 = (int)(uVar1 % 3);
		if (iVar5 != -2)
		{
			do
			{
				uVar4 = uVar6 & 0x80000001;
				if ((int)uVar4 < 0)
				{
					uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
				}
				pDVar3 = sub_6FB27D50(0x95, (float)(uVar4 + a1), uVar4 + a2, 1, 1);
				if (pDVar3 == nullptr)
				{
					uVar4 = 0xffffffff;
				}
				else
				{
					uVar4 = pDVar3->dwUnitId;
				}
				uVar6 = uVar6 + 1;
				byte_6FBB6F20 = 1;
				dword_6FBB6F21 = uVar4;
			} while ((int)uVar6 < iVar5 + 2);
		}
	}
	return uVar4;
}

//D2Client.0x6FB06FB0
void __cdecl sub_6FB06FB0()
{
	sub_6FB08700(0, 1);
}

//D2Client.0x6FB06FC0
void __fastcall sub_6FB06FC0(uint32_t a1, uint32_t* a2)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;

	CLIENT_SetExitToMenu(0);
	SendMessageA((HWND)*a2, 0x10, 0, 0);
	sub_6FAA9430(1);
	iVar1 = sub_6FB23230(9);
	if (iVar1 != 0)
	{
		sub_6FB23260(9, 1, 0);
	}
	uVar3 = 0;
	uVar2 = 0;
	do
	{
		if (*(int*)((int)&dword_6FB7DE70 + uVar2) != 0)
		{
			sub_6FB23260(uVar3, 0, 0);
		}
		uVar2 = uVar2 + 0xc;
		uVar3 = uVar3 + 1;
	} while (uVar2 < 0x1c8);
}

//D2Client.0x6FB07030
void __cdecl sub_6FB07030()
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;

	iVar1 = sub_6FB23230(9);
	if (iVar1 != 0)
	{
		sub_6FB23260(9, 1, 0);
	}
	uVar3 = 0;
	uVar2 = 0;
	do
	{
		if (*(int*)((int)&dword_6FB7DE70 + uVar2) != 0)
		{
			sub_6FB23260(uVar3, 0, 0);
		}
		uVar2 = uVar2 + 0xc;
		uVar3 = uVar3 + 1;
	} while (uVar2 < 0x1c8);
}

//D2Client.0x6FB07090
void __cdecl sub_6FB07090()
{
	sub_6FB08700(0, 2);
}

//D2Client.0x6FB070A0
void __cdecl sub_6FB070A0()
{
	sub_6FB08700(0, 3);
}

//D2Client.0x6FB070B0
void __cdecl sub_6FB070B0()
{
	sub_6FB08700(0, 4);
}

//D2Client.0x6FB070C0
void __cdecl sub_6FB070C0()
{
	int iVar1;

	iVar1 = sub_6FB23230(9);
	if (iVar1 != 0)
	{
		sub_6FB23260(9, 1, 0);
	}
	sub_6FB23260(0xb, 0, 0);
}

//D2Client.0x6FB070F0
void __fastcall sub_6FB070F0(int a1)
{
	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	const int32_t nValue = *(int32_t*)(a1 + 0x124);
	D2SOUND_10047((int32_t)(100.0f / (double)nMax * nValue));
}

//D2Client.0x6FB07130
void __fastcall sub_6FB07130(int a1)
{
	const int32_t nVolume = D2SOUND_10046();
	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	*(int32_t*)(a1 + 0x124) = (int32_t)((double)nMax * (nVolume + 1) * 0.01f);
}

//D2Client.0x6FB07180
void __fastcall sub_6FB07180(int a1)
{
	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	const int32_t nValue = *(int32_t*)(a1 + 0x124);
	D2SOUND_10049((void*)(int32_t)(100.0f / (double)nMax * nValue));
}

//D2Client.0x6FB071C0
void __fastcall sub_6FB071C0(int a1)
{
	const int32_t nVolume = (int32_t)D2SOUND_10048();
	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	*(int32_t*)(a1 + 0x124) = (int32_t)((double)nMax * (nVolume + 1) * 0.01f);
}

//D2Client.0x6FB07230
void __fastcall sub_6FB07230(int a1)
{
	uint32_t uVar1;

	uVar1 = sub_6FB53250();
	*(uint32_t*)(a1 + 0x124) = uVar1;
}

//D2Client.0x6FB07250
void __fastcall sub_6FB07250(int a1)
{
	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	const int32_t nValue = *(int32_t*)(a1 + 0x124);
	D2SOUND_10051((int32_t)(100.0f / (double)nMax * nValue));
}

//D2Client.0x6FB07290
void __fastcall sub_6FB07290(int a1)
{
	const int32_t nVolume = D2SOUND_10050();
	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	*(int32_t*)(a1 + 0x124) = (int32_t)((double)nMax * (nVolume + 1) * 0.01f);
}

//D2Client.0x6FB07300
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB07300(int a1)
{
	bool bVar1;
	uint32_t extraout_var;

	bVar1 = sub_6FB53280();
	*(uint32_t*)(a1 + 0x124) = D2C_ZEXT(bVar1);
}

//D2Client.0x6FB07310
// TODO: decompilation needs review (in_reg, unaff_)
void __fastcall sub_6FB07310(int a1)
{
	int iVar1;
	int in_EDX;
	int unaff_ESI;

	D2SOUND_10053(*(int*)(a1 + 0x124), in_EDX, unaff_ESI);
	iVar1 = *(int*)(a1 + 0x124);
	if (iVar1 == 0)
	{
		sub_6FB467D0(1);
		sub_6FB1AB80(0);
		return;
	}
	if (iVar1 != 1)
	{
		if (iVar1 == 2)
		{
			sub_6FB467D0(1);
			sub_6FB1AB80(1);
			return;
		}
		return;
	}
	sub_6FB467D0(0);
	sub_6FB1AB80(1);
}

//D2Client.0x6FB07370
// TODO: decompilation needs review (unaff_)
void __fastcall sub_6FB07370(int a1)
{
	int iVar1;
	int a2;
	int unaff_ESI;
	int unaff_retaddr;

	iVar1 = D2SOUND_10052(unaff_ESI);
	*(int*)(a1 + 0x124) = iVar1;
	iVar1 = sub_6FB52D00();
	if (iVar1 != 0)
	{
		D2SOUND_10053(*(int*)(a1 + 0x124), a2, unaff_retaddr);
		iVar1 = *(int*)(a1 + 0x124);
		if (iVar1 == 0)
		{
			sub_6FB467D0(1);
			sub_6FB1AB80(0);
			return;
		}
		if (iVar1 == 1)
		{
			sub_6FB467D0(0);
			sub_6FB1AB80(1);
			return;
		}
		if (iVar1 == 2)
		{
			sub_6FB467D0(1);
			sub_6FB1AB80(1);
			return;
		}
	}
}

//D2Client.0x6FB073E0
void __fastcall sub_6FB073E0(int a1)
{
	int iVar1;

	SRegSaveValue("Diablo II", "Light Quality", 0, *(uint32_t*)(a1 + 0x124));
	iVar1 = *(int*)(a1 + 0x124);
	if (iVar1 == 0)
	{
		D2GFX_SetLowQuality(1);
		sub_6FB394F0(0);
		return;
	}
	if (iVar1 != 1)
	{
		if (iVar1 == 2)
		{
			D2GFX_SetLowQuality(0);
			sub_6FB394F0(1);
			return;
		}
		return;
	}
	D2GFX_SetLowQuality(0);
	sub_6FB394F0(0);
}

//D2Client.0x6FB07440
void __fastcall sub_6FB07440(int a1)
{
	uint32_t uVar1;

	SRegLoadValue("Diablo II", "Light Quality", 0, (DWORD*)((uint32_t*)(a1 + 0x124)));
	uVar1 = *(uint32_t*)(a1 + 0x124);
	if (uVar1 == 0)
	{
		D2GFX_SetLowQuality(1);
		sub_6FB394F0(0);
		return;
	}
	if (uVar1 != 1)
	{
		if (uVar1 == 2)
		{
			D2GFX_SetLowQuality(0);
			sub_6FB394F0(1);
			return;
		}
		return;
	}
	D2GFX_SetLowQuality(0);
	sub_6FB394F0(0);
}

//D2Client.0x6FB074A0
void __fastcall sub_6FB074A0(int a1)
{
	SRegSaveValue("Diablo II", "Blended Shadows", 0, *(uint32_t*)(a1 + 0x124));
	D2GFX_SetBlendShadows(*(int*)(a1 + 0x124));
}

//D2Client.0x6FB074D0
void __fastcall sub_6FB074D0(int a1)
{
	SRegLoadValue("Diablo II", "Blended Shadows", 0, (DWORD*)((uint32_t*)(a1 + 0x124)));
	D2GFX_SetBlendShadows(*(uint32_t*)(a1 + 0x124));
}

//D2Client.0x6FB07500
void __fastcall sub_6FB07500(int a1)
{
	int iVar1;

	SRegSaveValue("Diablo II", "Resolution", 0, *(uint32_t*)(a1 + 0x124));
	iVar1 = 0;
	if (*(int*)(a1 + 0x124) == 1)
	{
		iVar1 = 2;
	}
	CLIENT_SetResolution(iVar1);
}

//D2Client.0x6FB07540
void __fastcall sub_6FB07540(int a1)
{
	int iVar1;

	SRegLoadValue("Diablo II", "Resolution", 0, (DWORD*)((uint32_t*)(a1 + 0x124)));
	iVar1 = 0;
	if (*(uint32_t*)(a1 + 0x124) == 1)
	{
		iVar1 = 2;
	}
	CLIENT_SetResolution(iVar1);
}

//D2Client.0x6FB07580
void __fastcall sub_6FB07580(int a1)
{
	SRegSaveValue("Diablo II", "Perspective", 0, *(uint32_t*)(a1 + 0x124));
	D2GFX_SetPerspective(*(int*)(a1 + 0x124));
	sub_6FAB7100((uint32_t*)dword_6FBA7990, 0, 0, gnViewWidth, gnViewHeight);
}

//D2Client.0x6FB075D0
void __fastcall sub_6FB075D0(int a1)
{
	uint32_t* value;
	int iVar1;

	value = (uint32_t*)(a1 + 0x124);
	SRegLoadValue("Diablo II", "Perspective", 0, (DWORD*)(value));
	iVar1 = D2GFX_CheckUnitPerspective();
	if (iVar1 != 0)
	{
		SRegSaveValue("Diablo II", "Perspective", 0, *value);
		D2GFX_SetPerspective(*value);
		sub_6FAB7100((uint32_t*)dword_6FBA7990, 0, 0, gnViewWidth, gnViewHeight);
		return;
	}
	*value = 0;
}

//D2Client.0x6FB07650
void __fastcall sub_6FB07650(int a1)
{
	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	const int32_t nValue = *(int32_t*)(a1 + 0x124);
	const uint32_t nGamma = (uint32_t)(int32_t)(200.0f / (double)nMax * nValue + 55.0f);
	SRegSaveValue("Diablo II", "Gamma", 0, nGamma);
	WNDPROC_SetGamma(nGamma);
}

//D2Client.0x6FB076C0
void __fastcall sub_6FB076C0(int a1)
{
	DWORD nGamma = 155;
	SRegLoadValue("Diablo II", "Gamma", 0, &nGamma);

	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	*(int32_t*)(a1 + 0x124) = (int32_t)((double)nMax * (int32_t)(nGamma - 54) * 0.005f);

	if (D2GFX_GammaCanBeControlled())
	{
		const int32_t nValue = *(int32_t*)(a1 + 0x124);
		const uint32_t nNewGamma = (uint32_t)(int32_t)(200.0f / (double)nMax * nValue + 55.0f);
		SRegSaveValue("Diablo II", "Gamma", 0, nNewGamma);
		WNDPROC_SetGamma(nNewGamma);
	}
}

//D2Client.0x6FB07780
void __fastcall sub_6FB07780(int a1)
{
	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	const int32_t nValue = *(int32_t*)(a1 + 0x124);
	SRegSaveValue("Diablo II", "Contrast", 0, (uint32_t)(int32_t)(100.0f / (double)nMax * nValue));
	D2GFX_SetOption(11, *(int32_t*)(a1 + 0x124));
	D2GFX_SetGamma(0);
}

//D2Client.0x6FB077F0
void __fastcall sub_6FB077F0(int a1)
{
	DWORD nContrast = D2GFX_GetDisplayType() != DISPLAYTYPE_GLIDE ? 100 : 0;
	SRegLoadValue("Diablo II", "Contrast", 0, &nContrast);

	const uint32_t nMax = *(uint32_t*)(a1 + 0x120) - 1;
	const int32_t nValue = (int32_t)((double)(uint32_t)(nContrast + 1) * (double)nMax * 0.01f);
	*(int32_t*)(a1 + 0x124) = nValue;

	SRegSaveValue("Diablo II", "Contrast", 0, (uint32_t)(int32_t)(100.0f / (double)nMax * nValue));
	D2GFX_SetOption(11, *(int32_t*)(a1 + 0x124));
	D2GFX_SetGamma(0);
}

//D2Client.0x6FB078B0
void __fastcall sub_6FB078B0(int a1)
{
	if (2 < *(uint32_t*)(a1 + 0x124))
	{
		*(uint32_t*)(a1 + 0x124) = 0;
	}
	sub_6FACF830(*(int*)(a1 + 0x124));
	SRegSaveValue("Diablo II", "AutoMapMode", 0, *(uint32_t*)(a1 + 0x124));
}

//D2Client.0x6FB078F0
void __fastcall sub_6FB078F0(int a1)
{
	uint32_t uVar1;
	uint32_t local_4;

	local_4 = a1;
	SRegLoadValue("Diablo II", "AutoMapMode", 0, (DWORD*)(&local_4));
	if (2 < local_4)
	{
		local_4 = 0;
	}
	sub_6FACF830(local_4);
	uVar1 = sub_6FACF820();
	*(uint32_t*)(a1 + 0x124) = uVar1;
}

//D2Client.0x6FB07930
void __fastcall sub_6FB07930(int a1)
{
	if (4 < *(uint32_t*)(a1 + 0x124))
	{
		*(uint32_t*)(a1 + 0x124) = 0;
	}
	sub_6FACB920(*(int*)(a1 + 0x124));
	SRegSaveValue("Diablo II", "AutoMapFade", 0, *(uint32_t*)(a1 + 0x124));
}

//D2Client.0x6FB07970
void __fastcall sub_6FB07970(int a1)
{
	uint32_t uVar1;
	uint32_t local_4;

	local_4 = a1;
	SRegLoadValue("Diablo II", "AutoMapFade", 0, (DWORD*)(&local_4));
	if (4 < local_4)
	{
		local_4 = 0;
		sub_6FACB920(0);
	}
	uVar1 = sub_6FACB8F0();
	*(uint32_t*)(a1 + 0x124) = uVar1;
}

//D2Client.0x6FB079B0
void __fastcall sub_6FB079B0(int a1)
{
	sub_6FACB980(*(uint32_t*)(a1 + 0x124));
}

//D2Client.0x6FB079C0
void __fastcall sub_6FB079C0(int a1)
{
	uint32_t uVar1;

	uVar1 = sub_6FACB970();
	*(uint32_t*)(a1 + 0x124) = uVar1;
}

//D2Client.0x6FB079D0
void __fastcall sub_6FB079D0(int a1)
{
	sub_6FACB9F0(*(uint32_t*)(a1 + 0x124));
}

//D2Client.0x6FB079E0
void __fastcall sub_6FB079E0(int a1)
{
	uint32_t uVar1;

	uVar1 = sub_6FACB9E0();
	*(uint32_t*)(a1 + 0x124) = uVar1;
}

//D2Client.0x6FB07A00
void __fastcall sub_6FB07A00(int a1)
{
	sub_6FACBA20(*(uint32_t*)(a1 + 0x124));
}

//D2Client.0x6FB07A10
void __fastcall sub_6FB07A10(int a1)
{
	int iVar1;

	iVar1 = sub_6FACB9E0();
	if (iVar1 != 0)
	{
		iVar1 = sub_6FACBA10();
		if (iVar1 != 0)
		{
			*(uint32_t*)(a1 + 0x124) = 1;
			return;
		}
	}
	*(uint32_t*)(a1 + 0x124) = 0;
}

//D2Client.0x6FB07A40
void __cdecl sub_6FB07A40()
{
	sub_6FB08700(0, 0);
}

//D2Client.0x6FB07A50
void __cdecl sub_6FB07A50(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;

	uVar3 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	iVar1 = pSMSGHANDLER_PARAMS->lParam;
	iVar2 = sub_6FB07AA0(uVar3);
	if (iVar2 != -1)
	{
		dword_6FBB6FD8 = iVar2;
	}
	sub_6FB07B30((uint32_t)(uint16_t)iVar1, uVar3);
	dword_6FBB6FE8 = 1;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB07AA0
int __fastcall sub_6FB07AA0(int a1)
{
	code* pcVar1;
	int iVar2;
	int* piVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	iVar4 = *sgptMenuInfo;
	iVar5 = -1;
	iVar2 = (gnScreenHeight + -0x50) / 2;
	iVar6 = (sgptMenuInfo[1] * iVar4) / 2;
	if (((iVar2 - iVar6 < a1) && (a1 < iVar2 + iVar6)) && (iVar2 = 0, 0 < iVar4))
	{
		piVar3 = (int*)(dword_6FBB6FE0 + 8);
		do
		{
			if ((*piVar3 != 0) && (*piVar3 + iVar4 <= a1))
			{
				iVar5 = iVar2;
			}
			iVar2 = iVar2 + 1;
			piVar3 = piVar3 + 0x154;
		} while (iVar2 < iVar4);
		if (-1 < iVar5)
		{
			piVar3 = (int*)(iVar5 * 0x550 + dword_6FBB6FE0);
			if (*piVar3 != -1)
			{
				pcVar1 = (code*)piVar3[0x44];
				if (pcVar1 == nullptr)
				{
					return iVar5;
				}
				iVar4 = (*pcVar1)();
				if (iVar4 != 0)
				{
					return iVar5;
				}
			}
			iVar5 = -1;
		}
	}
	return iVar5;
}

//D2Client.0x6FB07B30
void __fastcall sub_6FB07B30(int a1, int a2)
{
	code* pcVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int64_t lVar7;

	if ((dword_6FBB6FEC != 0) || (iVar2 = sub_6FB07AA0(a2), iVar2 == dword_6FBB6FD8))
	{
		iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0;
		iVar2 = *(int*)(iVar3 + 0x124);
		pcVar1 = *(code**)(iVar3 + 0x110);
		if (((pcVar1 == nullptr) || (iVar3 = (*pcVar1)(), iVar3 != 0)) &&
		    (iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0,
		        *(int*)(dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0) == 2))
		{
			iVar4 = gnScreenWidth / 2;
			iVar5 = iVar4 + -0x3b;
			iVar6 = iVar4 + -0x3c;
			if (*(int*)(iVar3 + 0x53c) == 0)
			{
				iVar5 = iVar4 + -0x90;
				iVar6 = iVar4 + -0x91;
			}
			if ((dword_6FBB6FEC != 0) || ((iVar5 < a1 && (a1 < iVar5 + 0x121))))
			{
				if (a1 < iVar6 + 0xc)
				{
					*(uint32_t*)(iVar3 + 0x124) = 0;
				}
				else if (iVar6 + 0x115 < a1)
				{
					*(int*)(iVar3 + 0x124) = *(int*)(iVar3 + 0x120) + -1;
				}
				else
				{
					lVar7 = (int64_t)((double)(a1 - (iVar6 + 0xc)) /
					                      ((double)132.5 / (double)(*(int*)(iVar3 + 0x120) - 1)) +
					                  (double)1.0);
					*(int*)(iVar3 + 0x124) = (int)lVar7 / 2;
				}
				dword_6FBB6FEC = 1;
			}
		}
		iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0;
		if (iVar2 != *(int*)(iVar3 + 0x124))
		{
			pcVar1 = *(code**)(iVar3 + 0x114);
			if (pcVar1 != nullptr)
			{
				(*pcVar1)();
			}
			sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
		}
	}
}

//D2Client.0x6FB07CC0
void __cdecl sub_6FB07CC0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;

	if (dword_6FBB6FE8 != 0)
	{
		iVar1 = sub_6FB07AA0((uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2));
		if (iVar1 == dword_6FBB6FD8)
		{
			sub_6FB07D20();
		}
	}
	sub_6FAABF30();
	dword_6FBB6FE8 = 0;
	dword_6FBB6FEC = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB07D20
void __cdecl sub_6FB07D20()
{
	code* pcVar1;
	int iVar2;
	int* piVar3;

	pcVar1 = *(code**)(dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0 + 0x110);
	if ((pcVar1 == nullptr) || (iVar2 = (*pcVar1)(), iVar2 != 0))
	{
		piVar3 = (int*)(dword_6FBB6FE0 + dword_6FBB6FD8 * 0x550);
		if (*piVar3 == 0)
		{
			if ((code*)piVar3[0x45] != nullptr)
			{
				(*(code*)piVar3[0x45])();
				sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
			}
		}
		else if (*piVar3 == 1)
		{
			piVar3[0x49] = piVar3[0x49] + 1;
			iVar2 = dword_6FBB6FE0 + dword_6FBB6FD8 * 0x550;
			if (*(int*)(iVar2 + 0x120) - 1U < *(uint32_t*)(iVar2 + 0x124))
			{
				*(uint32_t*)(iVar2 + 0x124) = 0;
			}
			pcVar1 = *(code**)(dword_6FBB6FE0 + dword_6FBB6FD8 * 0x550 + 0x114);
			if (pcVar1 != nullptr)
			{
				(*pcVar1)();
			}
			sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
			return;
		}
	}
}

//D2Client.0x6FB07E20
void __cdecl sub_6FB07E20(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	code* pcVar1;
	int* piVar2;
	int iVar3;

	do
	{
		dword_6FBB6FD8 = dword_6FBB6FD8 + 1;
		if (*sgptMenuInfo + -1 < dword_6FBB6FD8)
		{
			dword_6FBB6FD8 = 0;
		}
		piVar2 = (int*)(dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0);
	} while ((*piVar2 == -1) ||
	         ((pcVar1 = (code*)piVar2[0x44], pcVar1 != nullptr &&
	                                             (iVar3 = (*pcVar1)(), iVar3 == 0))));
	sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB07EA0
void __cdecl sub_6FB07EA0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	code* pcVar1;
	int* piVar2;
	int iVar3;

	do
	{
		dword_6FBB6FD8 = dword_6FBB6FD8 + -1;
		if (dword_6FBB6FD8 < 0)
		{
			dword_6FBB6FD8 = *sgptMenuInfo + -1;
		}
		piVar2 = (int*)(dword_6FBB6FE0 + dword_6FBB6FD8 * 0x550);
	} while ((*piVar2 == -1) ||
	         ((pcVar1 = (code*)piVar2[0x44], pcVar1 != nullptr &&
	                                             (iVar3 = (*pcVar1)(), iVar3 == 0))));
	sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB07F20
void __cdecl sub_6FB07F20(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	code* pcVar2;
	int iVar3;
	int* piVar4;
	uint32_t uVar5;

	iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0;
	iVar1 = *(int*)(iVar3 + 0x124);
	pcVar2 = *(code**)(iVar3 + 0x110);
	if ((pcVar2 == nullptr) || (iVar3 = (*pcVar2)(), iVar3 != 0))
	{
		piVar4 = (int*)(dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0);
		if (*piVar4 == 1)
		{
			piVar4[0x49] = piVar4[0x49] + -1;
			iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0;
			uVar5 = *(int*)(iVar3 + 0x120) - 1;
			if (uVar5 < *(uint32_t*)(iVar3 + 0x124))
			{
				*(uint32_t*)(iVar3 + 0x124) = uVar5;
			}
		}
		else if (*piVar4 == 2)
		{
			piVar4[0x49] = piVar4[0x49] + -1;
			iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0;
			if (*(int*)(iVar3 + 0x120) - 1U < *(uint32_t*)(iVar3 + 0x124))
			{
				*(uint32_t*)(iVar3 + 0x124) = 0;
			}
		}
	}
	iVar3 = dword_6FBB6FE0 + dword_6FBB6FD8 * 0x550;
	if (iVar1 != *(int*)(iVar3 + 0x124))
	{
		pcVar2 = *(code**)(iVar3 + 0x114);
		if (pcVar2 != nullptr)
		{
			(*pcVar2)();
		}
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB08060
void __cdecl sub_6FB08060(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	code* pcVar2;
	int iVar3;
	int* piVar4;
	uint32_t uVar5;

	iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0;
	iVar1 = *(int*)(iVar3 + 0x124);
	pcVar2 = *(code**)(iVar3 + 0x110);
	if ((pcVar2 == nullptr) || (iVar3 = (*pcVar2)(), iVar3 != 0))
	{
		piVar4 = (int*)(dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0);
		if (*piVar4 == 1)
		{
			piVar4[0x49] = piVar4[0x49] + 1;
			iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0;
			if (*(int*)(iVar3 + 0x120) - 1U < *(uint32_t*)(iVar3 + 0x124))
			{
				*(uint32_t*)(iVar3 + 0x124) = 0;
			}
		}
		else if (*piVar4 == 2)
		{
			piVar4[0x49] = piVar4[0x49] + 1;
			iVar3 = dword_6FBB6FD8 * 0x550 + dword_6FBB6FE0;
			uVar5 = *(int*)(iVar3 + 0x120) - 1;
			if (uVar5 < *(uint32_t*)(iVar3 + 0x124))
			{
				*(uint32_t*)(iVar3 + 0x124) = uVar5;
			}
		}
	}
	iVar3 = dword_6FBB6FE0 + dword_6FBB6FD8 * 0x550;
	if (iVar1 != *(int*)(iVar3 + 0x124))
	{
		pcVar2 = *(code**)(iVar3 + 0x114);
		if (pcVar2 != nullptr)
		{
			(*pcVar2)();
		}
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB081A0
void __cdecl sub_6FB081A0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	sub_6FB07D20();
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}
