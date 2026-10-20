#include "Game/Game.h"

#include "Core/Archive.h"
#include "Core/MemoryPartitions.h"
#include "Core/Video.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Draw/DWall.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Msg.h"
#include "Game/PalShift.h"
#include "Game/Record.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "Game/View.h"
#include "Quest/QuestsFX.h"
#include "Sound/SoundChan.h"
#include "Sound/SoundHdr.h"
#include "UI/Automap.h"
#include "UI/Chat.h"
#include "UI/CmdTbl.h"
#include "UI/Hireables.h"
#include "UI/NpcMenu.h"
#include "UI/Restart.h"
#include "UI/SkillsTree.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/Player.h"
#include "Unit/UnitMode.h"

//D2Client.0x6FB6E23C
uint8_t* gpuint8_t_6FB6E23C = (uint8_t*)sub_6FAAC450;
//D2Client.0x6FB6E24C
uint8_t* gpuint8_t_6FB6E24C = (uint8_t*)sub_6FAAC450;
//D2Client.0x6FB6E25C
uint8_t* gpuint8_t_6FB6E25C = (uint8_t*)sub_6FAAC450;
//D2Client.0x6FB6E26C
uint8_t* gpuint8_t_6FB6E26C = (uint8_t*)sub_6FAAC450;
//D2Client.0x6FB75450
uint8_t* gpuint8_t_6FB75450[3] = {(uint8_t*)sub_6FAA9640, (uint8_t*)sub_6FADC180, (uint8_t*)sub_6FADC970};
//D2Client.0x6FB7545C
int32_t dword_6FB7545C = 5;
//D2Client.0x6FB75460
uint32_t dword_6FB75460 = 0x28;
//D2Client.0x6FB75780
uint32_t dword_6FB75780;
//D2Client.0x6FB75784
uint32_t dword_6FB75784;
//D2Client.0x6FB75788
uint8_t byte_6FB75788;
//D2Client.0x6FB75789
uint8_t* ptr_6FB75789 = (uint8_t*)"screen01";
//D2Client.0x6FB75804
uint32_t dword_6FB75804 = 0xA;
//D2Client.0x6FB75818
uint32_t tbl_6FB75818[1];
//D2Client.0x6FB7581C
int32_t dword_6FB7581C = 513;
//D2Client.0x6FB75890
uint32_t tbl_6FB75890[3] = {0, 0x20A, (uint32_t)sub_6FAA8F20};
//D2Client.0x6FB7589C
uint32_t tbl_6FB7589C[6] = {0, 0x208, (uint32_t)sub_6FAA8F90, 0, 0x207, (uint32_t)sub_6FAA8FC0};
//D2Client.0x6FB758B4
uint32_t tbl_6FB758B4[6] = {0, 0x20B, (uint32_t)sub_6FAA8FF0, 0, 0x20C, (uint32_t)sub_6FAA9040};
//D2Client.0x6FB758CC
uint32_t tbl_6FB758CC[1];
//D2Client.0x6FB758D0
uint8_t byte_6FB758D0;
//D2Client.0x6FB758D8
uint32_t dword_6FB758D8 = 0xFFFFFFFF;
//D2Client.0x6FB758DC
uint32_t dword_6FB758DC = 0xFFFFFFFF;
//D2Client.0x6FB758E0
uint8_t byte_6FB758E0 = 0xF5;
//D2Client.0x6FB7591C
int32_t dword_6FB7591C = 4;
//D2Client.0x6FB75920
uint32_t tbl_6FB75920[22] = {0, 0x201, (uint32_t)sub_6FAAA500, 0, 0x204, (uint32_t)sub_6FAAA500, 0, 0x100, (uint32_t)sub_6FAAA530, 0, 0x1C, (uint32_t)sub_6FAA9100, 3, 0x5B, (uint32_t)sub_6FAA90E0, 3, 0x5C, (uint32_t)sub_6FAA90E0, 3, 0x5D, (uint32_t)sub_6FAA90E0};
//D2Client.0x6FB75978
uint32_t tbl_6FB75978[27] = {0, 0x201, (uint32_t)sub_6FAAA7D0, 0, 0x204, (uint32_t)sub_6FAAA7D0, 0, 0x202, (uint32_t)sub_6FAAA880, 0, 0x205, (uint32_t)sub_6FAAA880, 0, 0x100, (uint32_t)sub_6FAAA920, 0, 0x1C, (uint32_t)sub_6FAA9100, 3, 0x5B, (uint32_t)sub_6FAA90E0, 3, 0x5C, (uint32_t)sub_6FAA90E0, 3, 0x5D, (uint32_t)sub_6FAA90E0};
//D2Client.0x6FB759E4
uint32_t dword_6FB759E4 = 1;
//D2Client.0x6FB759E8
uint8_t* ptr_6FB759E8 = (uint8_t*)sub_6FAABD30;
//D2Client.0x6FB75B28
char str_6FB75B28[16] = ".?AUSGAMEDATA@@";
//D2Client.0x6FB75B40
char str_6FB75B40[56] = ".?AV?$TSHashObjectChunk@USGAMEDATA@@VHASHKEY_NONE@@@@";
//D2Client.0x6FB75EA0
char str_6FB75EA0[48] = ".?AV?$TSExplicitList@USGAMEDATA@@$0?CCCCCCCD@@@";
//D2Client.0x6FBA7748
uint8_t byte_6FBA7748;
//D2Client.0x6FBA774C
uint8_t byte_6FBA774C;
//D2Client.0x6FBA7750
uint32_t dword_6FBA7750;
//D2Client.0x6FBA7754
uint8_t* gpuint8_t_6FBA7754;
//D2Client.0x6FBA7758
uint8_t* ptr_6FBA7758;
//D2Client.0x6FBA775C
uint32_t dword_6FBA775C;
//D2Client.0x6FBA7760
uint32_t dword_6FBA7760;
//D2Client.0x6FBA7764
uint32_t dword_6FBA7764;
//D2Client.0x6FBA7768
uint32_t dword_6FBA7768;
//D2Client.0x6FBA776C
uint32_t dword_6FBA776C;
//D2Client.0x6FBA7770
int32_t dword_6FBA7770;
//D2Client.0x6FBA7774
int32_t dword_6FBA7774;
//D2Client.0x6FBA7778
uint32_t dword_6FBA7778;
//D2Client.0x6FBA777C
uint32_t dword_6FBA777C;
//D2Client.0x6FBA7780
uint32_t dword_6FBA7780;
//D2Client.0x6FBA7784
uint32_t dword_6FBA7784;
//D2Client.0x6FBA7788
uint32_t dword_6FBA7788;
//D2Client.0x6FBA778C
uint32_t dword_6FBA778C;
//D2Client.0x6FBA7794
uint32_t dword_6FBA7794;
//D2Client.0x6FBA7798
uint32_t dword_6FBA7798;
//D2Client.0x6FBA779C
uint32_t dword_6FBA779C;
//D2Client.0x6FBA77A0
uint32_t dword_6FBA77A0;
//D2Client.0x6FBA77A4
uint32_t dword_6FBA77A4;
//D2Client.0x6FBA77B4
uint8_t byte_6FBA77B4;
//D2Client.0x6FBA77C4
uint32_t dword_6FBA77C4;
//D2Client.0x6FBA77C8
uint32_t dword_6FBA77C8;
//D2Client.0x6FBA77CC
uint32_t dword_6FBA77CC;
//D2Client.0x6FBA77D0
DWORD dword_6FBA77D0;
//D2Client.0x6FBA77D4
uint8_t byte_6FBA77D4;
//D2Client.0x6FBA77EC
int32_t dword_6FBA77EC;
//D2Client.0x6FBA77F0
uint8_t byte_6FBA77F0;
//D2Client.0x6FBA7810
char gszPlayerName[16];
//D2Client.0x6FBA7814
uint8_t byte_6FBA7814;
//D2Client.0x6FBA7818
uint8_t byte_6FBA7818;
//D2Client.0x6FBA781C
uint8_t byte_6FBA781C;
//D2Client.0x6FBA7824
HANDLE ghandle_6FBA7824;
//D2Client.0x6FBA7890
uint32_t dword_6FBA7890;
//D2Client.0x6FBA7898
uint8_t byte_6FBA7898;
//D2Client.0x6FBA78B0
uint8_t byte_6FBA78B0;
//D2Client.0x6FBA78B4
int32_t dword_6FBA78B4;
//D2Client.0x6FBA78B8
int32_t dword_6FBA78B8;
//D2Client.0x6FBA78C0
int32_t dword_6FBA78C0;
//D2Client.0x6FBA7944
int32_t dword_6FBA7944;
//D2Client.0x6FBA7948
uint8_t byte_6FBA7948;
//D2Client.0x6FBA794C
int32_t dword_6FBA794C;
//D2Client.0x6FBA7950
int32_t dword_6FBA7950;
//D2Client.0x6FBA7954
int32_t dword_6FBA7954;
//D2Client.0x6FBA7958
uint32_t dword_6FBA7958;
//D2Client.0x6FBA795C
uint8_t byte_6FBA795C;
//D2Client.0x6FBA7960
int32_t gnGameType;
//D2Client.0x6FBA7970
uint32_t dword_6FBA7970;
//D2Client.0x6FBA7974
uint32_t dword_6FBA7974;
//D2Client.0x6FBA7978
uint32_t dword_6FBA7978;
//D2Client.0x6FBA797C
int32_t dword_6FBA797C;
//D2Client.0x6FBA7994
uint8_t byte_6FBA7994;
//D2Client.0x6FBA7998
int32_t dword_6FBA7998;
//D2Client.0x6FBA799C
int32_t dword_6FBA799C;
//D2Client.0x6FBA79A0
int32_t dword_6FBA79A0;
//D2Client.0x6FBA79A4
int32_t dword_6FBA79A4;
//D2Client.0x6FBA79A8
uint32_t dword_6FBA79A8;
//D2Client.0x6FBA79AC
uint32_t dword_6FBA79AC;
//D2Client.0x6FBA79C4
uint32_t dword_6FBA79C4;
//D2Client.0x6FBA79C8
uint8_t byte_6FBA79C8;
//D2Client.0x6FBA79E0
uint32_t dword_6FBA79E0;
//D2Client.0x6FBA79E4
uint32_t dword_6FBA79E4;
//D2Client.0x6FBA79E8
uint32_t dword_6FBA79E8;
//D2Client.0x6FBA79EC
uint32_t dword_6FBA79EC;
//D2Client.0x6FBA79F0
DWORD dword_6FBA79F0;
//D2Client.0x6FBA79F4
int32_t dword_6FBA79F4;
//D2Client.0x6FBC1AF4
int32_t dword_6FBC1AF4;
//D2Client.0x6FBC1AFC
int32_t dword_6FBC1AFC;

//D2Client.0x6FAA9450
void __cdecl sub_6FAA9450()
{
	int iVar1;
	uint32_t* puVar2;
	char cStack_5;
	HSFILE__* pHStack_4;

	puVar2 = &dword_6FBA7750;
	for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	dword_6FBA799C = 0;
	dword_6FBA797C = 0;
	dword_6FBA7978 = 0;
	dword_6FBA7958 = 0;
	dword_6FBA7974 = 0;
	dword_6FBA79BC = 0;
	FOG_CreateNewPoolSystem((void**)(&ptr_6FBA7758), "Client Pool System", 0x40000, 0x1000);
	sub_6FB28390(nullptr);
	if (dword_6FBA794C == 0)
	{
		iVar1 = ARCHIVE_OpenFile(0, "Data\\Local\\Color.txt", &pHStack_4, 1);
		if (iVar1 != 0)
		{
			ARCHIVE_ReadFileToBuffer(nullptr, pHStack_4, (D2CellFileStrc*)&cStack_5, 1);
			ARCHIVE_CloseFile(0, pHStack_4);
			if (cStack_5 == '1')
			{
				dword_6FBA794C = 1;
			}
		}
	}
	if (dword_6FBA7990 == 0)
	{
		dword_6FBA7990 = (int)sub_6FAB6FF0();
	}
	sub_6FB09C90();
	sub_6FB241A0();
	sub_6FB242E0(1);
	if ((((gnGameType == 7) || (gnGameType == 9)) || (gnGameType == 6)) || (gnGameType == 8))
	{
		sub_6FAAD560(1);
	}
	FaultSetAssertHandler((FaultAssertHandler)(sub_6FAA9420));
	sub_6FAADEA0();
	D2CMP_10096();
	MEMORY_InitializePartitions(ptr_6FBA7758, 1);
	iVar1 = sub_6FAADC90();
	dword_6FBA7970 = (uint32_t)(iVar1 != 0);
	dword_6FBA77D0 = GetTickCount();
	byte_6FBA7948 = GetTickCount();
	gpuint8_t_6FBA7754 = (uint8_t*)(sub_6FAA9640);
	dword_6FBA7768 = 0;
	dword_6FBA7764 = 0;
	sub_6FAB71B0((uint32_t*)dword_6FBA7990, 0, 0);
	sub_6FAB5760(0);
	dword_6FBA77CC = 0;
	sub_6FB3F330();
	MEMORY_Nop();
	sub_6FABA580();
	ptr_6FBA7988 = (uint8_t*)(D2_ALLOC(8));
	sub_6FB28020();
	sub_6FAA46A0();
	sub_6FAA6A10();
	sub_6FAD2F60();
	dword_6FBA79D4 = 0;
	dword_6FBA796C = 0;
}

//D2Client.0x6FAA9620
void __fastcall sub_6FAA9620(int a1)
{
	dword_6FBA7750 = a1;
	gpuint8_t_6FBA7754 = gpuint8_t_6FB75450[a1];
}

//D2Client.0x6FAA9640
void __fastcall sub_6FAA9640(int a1)
{
	int iVar1;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	D2LevelsTxt* pDVar2;
	uint32_t uStack_24;
	uint32_t uStack_20;
	uint8_t abStack_1c[4];
	uint8_t abStack_18[4];
	uint8_t abStack_14[4];
	int iStack_10;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	sub_6FB245C0();
	iVar1 = WINDOW_GetState();
	if (iVar1 == 0)
	{
		pUnit = CUNIT_GetPlayer();
		sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_10), (uint32_t*)(&iStack_c), (uint32_t*)(&iStack_8), (uint32_t*)(&iStack_4));
		iVar1 = UNITS_GetClientCoordX(pUnit);
		uStack_24 = iVar1 - (iStack_8 - iStack_10) / 2;
		iVar1 = UNITS_GetClientCoordY(pUnit);
		uStack_20 = iVar1 - (iStack_4 - iStack_c) / 2;
		sub_6FAB7C50((int*)&uStack_24, (int*)&uStack_20);
		if ((dword_6FB758D8 != 0xffffffff) || (dword_6FB758DC != 0xffffffff))
		{
			dword_6FBA79D8 = uStack_24 - dword_6FB758D8;
			dword_6FBA79DC = uStack_20 - dword_6FB758DC;
		}
		dword_6FB758D8 = uStack_24;
		dword_6FB758DC = uStack_20;
		sub_6FAB71B0((uint32_t*)dword_6FBA7990, uStack_24, uStack_20);
		sub_6FAB7200((uint32_t*)dword_6FBA7990, 0);
		sub_6FAA7940();
		ENVIRONMENT_GetLightColorFromAct(ghAct, abStack_14, abStack_18, abStack_1c);
		D2GFX_SetAmbientColor(abStack_14[0], abStack_18[0], abStack_1c[0]);
		pRoom = CUNIT_GetPlayerRoom();
		if (pRoom != nullptr)
		{
			iVar1 = DUNGEON_GetLevelIdFromRoom(pRoom);
			pDVar2 = DATATBLS_GetLevelsTxtRecord(iVar1);
			D2_ASSERT(pDVar2 != nullptr);
			pRoom = (D2ActiveRoomStrc*)pDVar2->dwBlankScreen;
		}
		iVar1 = D2GFX_StartDraw((int)pRoom, 0, 0, 0);
		if (iVar1 != 0)
		{
			D2Win_10179();
			sub_6FAB5960();
			iVar1 = sub_6FAB5750();
			if (iVar1 != 3)
			{
				sub_6FAB7260(dword_6FBA7990);
			}
			sub_6FB21B70();
			D2Win_10019();
			MEMORY_Nop();
			if (a1 == 0)
			{
				sub_6FB57AC0();
			}
			WNDPROC_DrawDebugInfo();
			if (dword_6FB75814 != 0)
			{
				D2GFX_ClearScreen(0);
				dword_6FB75814 = dword_6FB75814 + -1;
				if (dword_6FB75814 < 0)
				{
					dword_6FB75814 = 0;
					FOG_Trace("global static overwrite error at line %d of file %s\n", __LINE__, __FILE__);
				}
			}
			D2GFX_EndScene();
			return;
		}
	}
}

//D2Client.0x6FAA9850
void __fastcall sub_6FAA9850(int a1)
{
	if (((dword_6FBA799C == 0) && (dword_6FBA7954 == 0)) && (dword_6FBA797C == 0))
	{
		dword_6FBA77EC = a1;
		if (0x1c < a1)
		{
			dword_6FBA77EC = 9;
		}
		sub_6FB23800(1, 0);
		dword_6FBA799C = 600;
		dword_6FBA7970 = 1;
		dword_6FBA796C = 0;
		dword_6FBA7968 = 0;
		CLIENT_SetExitToMenu(0);
		return;
	}
}

//D2Client.0x6FAA98C0
uint32_t __cdecl sub_6FAA98C0(uint32_t a1)
{
	int iVar1;
	Unicode* wszText;
	D2SplittedTextStrc* pSplitText;
	int iVar2;
	short index;
	uint32_t uVar3;
	D2SplittedTextStrc* pDVar4;
	int nColor;
	int bCentered;
	uint32_t uStack_4;

	if (dword_6FBA799C == 0)
	{
		return 0;
	}
	iVar1 = WINDOW_GetState();
	if ((iVar1 != 0) || (iVar1 = D2GFX_StartDraw(1, 0, 0, 0), iVar1 == 0))
		goto LAB_6faa99e6;
	D2GFX_ClearScreen(0);
	D2Win_10127_SetFont(D2FONT_FONT42);
	wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(&byte_6FB758E0 + dword_6FBA77EC * 2)));
	if ((*(uint8_t*)(gpConfig + 0x1ea) & 0x20) != 0)
	{
		if (dword_6FBA77EC == 0x14)
		{
			index = 0x5522;
		}
		else
		{
			if (dword_6FBA77EC != 0x15)
				goto LAB_6faa9944;
			index = 0x5521;
		}
		wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	}
LAB_6faa9944:
	iVar1 = D2Win_10121_GetTextWidth(wszText);
	if (iVar1 < gnViewWidth + -0x28)
	{
		D2Win_10117_DrawText(wszText, gnViewWidth - iVar1 >> 1, 200, 0, 0);
	}
	else
	{
		D2Win_10127_SetFont(D2FONT_FONT30);
		pSplitText = D2Win_10199(wszText, (int*)&uStack_4, 600);
		uVar3 = 0;
		pDVar4 = pSplitText;
		if (uStack_4 != 0)
		{
			do
			{
				iVar1 = D2Win_10121_GetTextWidth(pDVar4->wszLine);
				bCentered = 0;
				iVar1 = gnViewWidth - iVar1;
				nColor = 0;
				iVar2 = D2Win_10125();
				D2Win_10117_DrawText(pDVar4->wszLine, iVar1 >> 1, iVar2 * uVar3 * 2 + 200, nColor, bCentered);
				pDVar4 = pDVar4->pNextLine;
				uVar3 = uVar3 + 1;
			} while (uVar3 < uStack_4);
		}
		D2Win_10200(pSplitText);
	}
	D2Win_10019();
	D2GFX_EndScene();
LAB_6faa99e6:
	dword_6FBA799C = dword_6FBA799C + -1;
	if (dword_6FBA799C != 0)
	{
		return 0;
	}
	sub_6FB245C0();
	return 1;
}

//D2Client.0x6FAA9A10
void __cdecl sub_6FAA9A10()
{
	DWORD DVar1;

	DVar1 = GetTickCount();
	if (dword_6FBA776C < DVar1)
	{
		sub_6FAAD3B0();
		dword_6FBA776C = DVar1 + 5000;
		dword_6FBA7770 = DVar1;
	}
}

//D2Client.0x6FAA9A50
void __fastcall sub_6FAA9A50(int a1)
{
	uint32_t uVar1;
	uint32_t* puVar2;
	DWORD DVar3;
	uint32_t* puVar4;
	int iVar5;

	puVar2 = &dword_6FBA77A4;
	puVar4 = (uint32_t*)(a1 + 1);
	do
	{
		uVar1 = *puVar4;
		puVar4 = puVar4 + 1;
		*puVar2 = uVar1;
		puVar2 = puVar2 + 1;
	} while ((int)puVar2 < (int)&dword_6FBA77C4);
	byte_6FBA77B4 = GetTickCount();
	DVar3 = GetTickCount();
	dword_6FBA7774 = DVar3 - dword_6FBA7770;
	if (dword_6FBA779C < 10)
	{
		iVar5 = dword_6FBA77A0 * dword_6FBA779C;
		dword_6FBA779C = dword_6FBA779C + 1;
		dword_6FBA77A0 = ((DVar3 - dword_6FBA7770) + iVar5) / dword_6FBA779C;
	}
}

//D2Client.0x6FAA9AB0
void __fastcall sub_6FAA9AB0(uint32_t a1)
{
	dword_6FBA77CC = a1;
}

//D2Client.0x6FAA9AC0
uint32_t __cdecl sub_6FAA9AC0()
{
	return dword_6FBA77CC;
}

//D2Client.0x6FAA9AD0
int32_t __fastcall sub_6FAA9AD0()
{
	return dword_6FBA7774;
}

//D2Client.0x6FAA9AE0
uint32_t __cdecl sub_6FAA9AE0()
{
	return dword_6FBA77A0;
}

//D2Client.0x6FAA9AF0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAA9AF0(uint32_t a1)
{
	bool bVar1;
	bool bVar2;
	bool bVar3;
	SHORT SVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	D2ActiveRoomStrc* pDVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	uint32_t extraout_var;
	uint32_t uVar10;
	uint32_t extraout_var_00;
	DWORD DVar11;
	D2DrlgStrc* pDVar12;
	uint32_t uVar13;
	bool bVar14;
	uint8_t bVar15;
	int iStack_20c;
	uint8_t abStack_200[512];

	bVar1 = false;
	bVar2 = false;
	pDVar5 = CUNIT_GetPlayer();
	if ((gnGameType == 0) || (gnGameType == 1))
	{
		iVar6 = WINDOW_GetState();
		if (iVar6 != 0)
		{
			dword_6FBA7760 = GetTickCount();
			return 0;
		}
		iVar6 = sub_6FB23860(9);
		if ((((iVar6 != 0) || (iVar6 = sub_6FB23860(0xb), iVar6 != 0)) && (pDVar5 != nullptr)) && (pDVar7 = CUNIT_GetPlayerRoom(), pDVar7 != nullptr))
		{
			dword_6FBA7760 = GetTickCount();
			(*(code*)gpuint8_t_6FBA7754)();
			sub_6FB54C60();
			return 0;
		}
	}
	sub_6FAAEB40();
	if (((dword_6FBA79A8 != 0) && (dword_6FB7580C = 8, dword_6FBA796C != 0)) && (dword_6FBA79B0 == 0))
	{
		dword_6FBA79C4 = 1;
		pDVar8 = CUNIT_GetPlayer();
		bVar15 = 0;
		if (dword_6FBA79B4 != 0)
		{
			bVar15 = 8;
		}
		if (dword_6FBA79B8 != 0)
		{
			bVar15 = 8;
		}
		if (dword_6FBA79BC != 0)
		{
			bVar15 = bVar15 | 4;
		}
		if ((pDVar8 != nullptr) && (pDVar8->dwUnitType == 0))
		{
			iVar6 = sub_6FB57BD0();
			iVar9 = sub_6FB57BC0();
			sub_6FB49920(1, iVar9, iVar6, bVar15);
		}
	}
	if ((dword_6FBA79AC != 0) && (dword_6FB75810 = 8, dword_6FBA796C != 0))
	{
		byte_6FBA79C8 = 1;
		pDVar8 = CUNIT_GetPlayer();
		bVar15 = 0;
		if (dword_6FBA79B4 != 0)
		{
			bVar15 = 8;
		}
		if (dword_6FBA79B8 != 0)
		{
			bVar15 = 8;
		}
		if (dword_6FBA79BC != 0)
		{
			bVar15 = bVar15 | 4;
		}
		if ((pDVar8 != nullptr) && (pDVar8->dwUnitType == 0))
		{
			iVar6 = sub_6FB57BD0();
			iVar9 = sub_6FB57BC0();
			sub_6FB49920(4, iVar9, iVar6, bVar15);
		}
	}
	bVar3 = sub_6FAD4F00(0x24, 1);
	if (((D2C_ZEXT(bVar3) == 0) || (uVar10 = sub_6FAD4B60(0x24, 1), (short)uVar10 == -1)) || (SVar4 = GetAsyncKeyState(uVar10 & 0xffff), -1 < SVar4))
	{
		bVar3 = sub_6FAD4F00(0x24, 0);
		if ((D2C_ZEXT(bVar3) != 0) &&
		    (uVar10 = sub_6FAD4B60(0x24, 0), (short)uVar10 != -1))
		{
			SVar4 = GetAsyncKeyState(uVar10 & 0xffff);
			dword_6FBA79BC = 1;
			if (SVar4 < 0)
				goto LAB_6faa9ce1;
		}
		dword_6FBA79BC = 0;
	}
	else
	{
		dword_6FBA79BC = 1;
	}
LAB_6faa9ce1:
	DVar11 = GetTickCount();
	if (dword_6FBA776C < DVar11)
	{
		sub_6FAAD3B0();
		dword_6FBA776C = DVar11 + 5000;
		dword_6FBA7770 = DVar11;
	}
	dword_6FBA775C = GetTickCount();
	if (dword_6FBA7760 == 0)
	{
		dword_6FBA7760 = dword_6FBA775C - dword_6FB75460;
	}
	if (3000 < dword_6FBA775C - dword_6FBA7788)
	{
		dword_6FBA7778 = dword_6FBA777C / 3;
		dword_6FBA7780 = dword_6FBA7784 / 3;
		dword_6FBA777C = 0;
		dword_6FBA7784 = 0;
		dword_6FBA7788 = dword_6FBA775C;
	}
	uVar10 = dword_6FBA775C - dword_6FBA7760;
	if (dword_6FB75460 <= uVar10)
	{
		bVar1 = true;
		dword_6FBA7760 = dword_6FBA775C;
		if (dword_6FBA775C < dword_6FBA778C)
		{
			iVar6 = dword_6FB75460 - 1;
			if ((int)(uVar10 - dword_6FB75460) < (int)(dword_6FB75460 - 1))
			{
				iVar6 = uVar10 - dword_6FB75460;
			}
			dword_6FBA79E0 = 0;
			dword_6FBA7760 = dword_6FBA775C - iVar6;
			dword_6FBA7778 = 0x19;
			dword_6FBA7780 = 0;
			dword_6FBA777C = 0;
			dword_6FBA7784 = 0;
			uVar10 = dword_6FB75460;
			dword_6FBA7788 = dword_6FBA775C;
		}
		if (dword_6FBA796C != 0)
		{
			sub_6FB4EE70(pDVar5);
		}
	}
	iStack_20c = 0;
	if (gnGameType == 0)
	{
		GAME_ProcessNetworkMessages();
		iStack_20c = GAME_UpdateGamesProgress(1);
		if (iStack_20c != 0)
		{
			iVar6 = 1;
		LAB_6faa9e41:
			GAME_UpdateClients(iVar6, 0);
		}
	}
	else if (gnGameType == 1)
	{
		GAME_ProcessNetworkMessages();
		iStack_20c = GAME_UpdateGamesProgress(1);
		iVar6 = 0;
		goto LAB_6faa9e41;
	}
	do
	{
		iVar6 = CLIENT_DequeueSystemPacket(abStack_200, 0x200);
		sub_6FAB1CB0(abStack_200, iVar6);
		Sleep(0);
	} while (iVar6 != -1);
	do
	{
		iVar6 = CLIENT_DequeueGamePacket(abStack_200, 0x200);
		sub_6FAB50B0((D2PacketBufferStrc*)abStack_200, iVar6);
		Sleep(0);
	} while (iVar6 != -1);
	sub_6FAD2FB0();
	D2MCPCLIENT_10003();
	if ((gnGameType == 0) || (gnGameType == 1))
	{
	LAB_6faaa017:
		if (dword_6FBA796C != 0)
		{
		LAB_6faaa024:
			if ((gnGameType == 0) || (gnGameType == 1))
			{
				if (iStack_20c != 0)
				{
					dword_6FBA775C = GetTickCount();
					for (pDVar7 = DUNGEON_GetRoomFromAct(ghAct); pDVar7 != nullptr;
					     pDVar7 = pDVar7->pRoomNext)
					{
						if ((pDVar7->dwFlags & 1) == 0)
						{
							sub_6FB3EFB0(pDVar7);
							sub_6FB27E70(pDVar7);
							sub_6FABA0D0(pDVar7);
							pDVar7->dwFlags = pDVar7->dwFlags | 1;
						}
					}
					sub_6FB280F0();
					pDVar7 = CUNIT_GetPlayerRoom();
					DUNGEON_AnimateTiles(pDVar7);
					sub_6FABA270();
					sub_6FB5B210();
					pDVar7 = CUNIT_GetPlayerRoom();
					iVar6 = ENVIRONMENT_UpdatePeriodOfDay(ghAct, pDVar7);
					if (iVar6 != 0)
					{
						sub_6FB29390();
					}
					pDVar12 = DUNGEON_GetDrlgFromAct(ghAct);
					DRLGACTIVATE_Update(pDVar12);
					sub_6FACBAF0();
					dword_6FBA7768 = dword_6FBA7768 + 1;
					if (dword_6FBA7768 % 0xd == 0)
					{
						DUNGEON_UpdateAndFreeInactiveRooms(ghAct);
					}
					bVar2 = true;
					if (dword_6FB75460 < uVar10)
					{
						if (uVar10 < dword_6FB75460 * 2)
						{
							dword_6FBA7760 = dword_6FBA7760 + (dword_6FB75460 - uVar10);
							dword_6FBA79E0 = 0;
						}
						else
						{
							dword_6FBA79E0 = (uint32_t)((int)dword_6FBA79E0 < 2);
							dword_6FBA7760 = dword_6FBA7760 + (1 - dword_6FB75460);
						}
					}
					else
					{
						dword_6FBA79E0 = 0;
					}
				}
			}
			else
			{
				if (bVar1)
				{
					dword_6FBA775C = GetTickCount();
					for (pDVar7 = DUNGEON_GetRoomFromAct(ghAct); pDVar7 != nullptr;
					     pDVar7 = pDVar7->pRoomNext)
					{
						if ((pDVar7->dwFlags & 1) == 0)
						{
							sub_6FB3EFB0(pDVar7);
							sub_6FB27E70(pDVar7);
							sub_6FABA0D0(pDVar7);
							pDVar7->dwFlags = pDVar7->dwFlags | 1;
						}
					}
					sub_6FB280F0();
					pDVar7 = CUNIT_GetPlayerRoom();
					DUNGEON_AnimateTiles(pDVar7);
					sub_6FABA270();
					sub_6FB5B210();
					pDVar7 = CUNIT_GetPlayerRoom();
					iVar6 = ENVIRONMENT_UpdatePeriodOfDay(ghAct, pDVar7);
					if (iVar6 != 0)
					{
						sub_6FB29390();
					}
					pDVar12 = DUNGEON_GetDrlgFromAct(ghAct);
					DRLGACTIVATE_Update(pDVar12);
					sub_6FACBAF0();
					dword_6FBA7768 = dword_6FBA7768 + 1;
					if (dword_6FBA7768 % 0xd == 0)
					{
						DUNGEON_UpdateAndFreeInactiveRooms(ghAct);
					}
					bVar2 = true;
					dword_6FBA7760 = dword_6FBA7760 + (dword_6FB75460 - uVar10);
					uVar10 = uVar10 / dword_6FB75460;
					uVar13 = (uint32_t)(dword_6FBA7778 < 7);
					if (1 < (int)uVar10)
					{
						uVar13 = uVar13 + 1;
					}
					if (9 < (int)uVar10)
					{
						uVar13 = uVar13 + 1;
					}
					if (0x13 < (int)uVar10)
					{
						uVar13 = uVar13 + 1;
					}
					if (0x1d < (int)uVar10)
					{
						uVar13 = uVar13 + 1;
					}
					if (0x1c < dword_6FBA7778)
					{
						uVar13 = 0;
					}
					bVar14 = SBORROW4(dword_6FBA79E0, uVar13);
					iVar6 = dword_6FBA79E0 - uVar13;
					bVar3 = dword_6FBA79E0 == uVar13;
				}
				else
				{
					bVar14 = SBORROW4(dword_6FBA7778, 0x16);
					iVar6 = dword_6FBA7778 + -0x16;
					bVar3 = iVar6 == 0;
				}
				if (!bVar3 && bVar14 == iVar6 < 0)
				{
					dword_6FBA79E0 = 0;
				}
			}
			if (dword_6FBA796C != 0)
			{
				sub_6FB49910();
				sub_6FAB5D60();
				iVar6 = D2SOUND_10032();
				if (iVar6 != 0)
				{
					D2SOUND_10029(0xb4);
					D2SOUND_10031();
					D2SOUND_10027(0xff);
				}
				if (dword_6FBA79E0 == 0)
				{
					pDVar7 = CUNIT_GetPlayerRoom();
					if (pDVar7 != nullptr)
					{
						(*(code*)gpuint8_t_6FBA7754)();
						dword_6FBA7764 = dword_6FBA7764 + 1;
						dword_6FBA777C = dword_6FBA777C + 1;
					}
				}
				else if (bVar1)
				{
					dword_6FBA7784 = dword_6FBA7784 + 1;
				}
				if (bVar2)
				{
					sub_6FB54C60();
				}
				dword_6FBA79E0 = dword_6FBA79E0 + 1;
				goto LAB_6faaa320;
			}
		}
	}
	else
	{
		DVar11 = GetTickCount();
		iVar6 = D2NET_10017();
		if (((iVar6 == 0) && (((dword_6FBA7970 == 0 && (dword_6FBA796C != 0)) && (dword_6FBA799C == 0)))) &&
		    ((dword_6FBA7954 == 0 && (dword_6FBA797C == 0))))
		{
			dword_6FBA77EC = 7;
			sub_6FB23800(1, 0);
			dword_6FBA799C = 600;
			dword_6FBA7970 = 1;
			dword_6FBA796C = 0;
			dword_6FBA7968 = 0;
			CLIENT_SetExitToMenu(0);
		}
		if (((dword_6FBA7974 != 0) && (180000 < DVar11 - dword_6FBA77D0)) &&
		    ((dword_6FBA799C == 0 && ((dword_6FBA7954 == 0 && (dword_6FBA797C == 0))))))
		{
			dword_6FBA77EC = 7;
			sub_6FB23800(1, 0);
			dword_6FBA799C = 600;
			dword_6FBA7970 = 1;
			dword_6FBA796C = 0;
			dword_6FBA7968 = 0;
			CLIENT_SetExitToMenu(0);
		}
		if ((((30000 < DVar11 - byte_6FBA7948) && (dword_6FBA796C == 0)) && (dword_6FBA7970 == 0)) &&
		    (dword_6FBA7974 == 0))
		{
			sub_6FAA9850(6);
		}
		if (dword_6FBA7968 != 0)
			goto LAB_6faaa017;
		if (dword_6FBA796C != 0)
			goto LAB_6faaa024;
		if (((dword_6FBA7970 == 0) && (dword_6FBA7974 == 0)) && ((gnGameType == 9 || (gnGameType == 7))))
		{
			sub_6FAA9850(6);
			goto LAB_6faaa017;
		}
	}
	WINDOW_GetState();
LAB_6faaa320:
	if (dword_6FBA7970 == 0)
	{
		return 0;
	}
	D2Win_10177(0);
	sub_6FB23800(1, 0);
	if ((gnGameType == 0) || (gnGameType == 1))
	{
		GAME_CloseAllGames();
	}
	if ((gnGameType == 6) || (gnGameType == 8))
	{
		EnterCriticalSection((LPCRITICAL_SECTION)&byte_6FBA77D4);
		dword_6FBA79A0 = 1;
		LeaveCriticalSection((LPCRITICAL_SECTION)&byte_6FBA77D4);
		WaitForSingleObject(ghandle_6FBA7824, 10000);
		ghandle_6FBA7824 = (HANDLE)0x0;
	}
	return 1;
}

//D2Client.0x6FAAA3B0
uint32_t __cdecl sub_6FAAA3B0(uint32_t a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint8_t bVar5;

	iVar4 = 0;
	iVar3 = 0;
	do
	{
		while (true)
		{
			EnterCriticalSection((LPCRITICAL_SECTION)&byte_6FBA77D4);
			iVar2 = dword_6FBA79A4;
			iVar1 = dword_6FBA79A0;
			LeaveCriticalSection((LPCRITICAL_SECTION)&byte_6FBA77D4);
			if (iVar1 != 0)
			{
				GAME_CloseAllGames();
				GAME_UpdateClients(0, 1);
				DeleteCriticalSection((LPCRITICAL_SECTION)&byte_6FBA77D4);
				OutputDebugStringA("Open server thread shut down\n");
				return 1;
			}
			if (iVar2 == 0)
				break;
			GAME_ProcessNetworkMessages();
			iVar4 = GAME_UpdateGamesProgress(1);
			if (iVar4 != 0)
			{
				GAME_UpdateClients(0, 0);
				break;
			}
		LAB_6faaa498:
			Sleep(10);
		}
		if (iVar4 == 0)
			goto LAB_6faaa498;
		Sleep(0x1e);
		iVar1 = (int)(CLIENT_GetComInterface());
		if ((iVar1 != 0) && (iVar2 = GAME_GetPlayerUnitsCount(1), iVar2 != iVar3))
		{
			if (iVar3 < dword_6FB7591C)
			{
				iVar3 = iVar2;
				if (dword_6FB7591C <= iVar2)
				{
					(**(code**)(iVar1 + 0x90))();
				}
			}
			else
			{
				iVar3 = iVar2;
				if (iVar2 < dword_6FB7591C)
				{
					bVar5 = *(char*)(gpConfig + 0x20b) == '\x01';
					if (*(char*)(gpConfig + 0x20b) == '\x02')
					{
						bVar5 = bVar5 | 2;
					}
					if ((*(uint16_t*)(gpConfig + 0x1ea) & 4) != 0)
					{
						bVar5 = bVar5 | 4;
					}
					if ((*(uint16_t*)(gpConfig + 0x1ea) & 0x20) != 0)
					{
						bVar5 = bVar5 | 8;
					}
					(**(code**)(iVar1 + 0x34))(gpConfig + 599, bVar5);
				}
			}
		}
	} while (true);
}

//D2Client.0x6FAAA4E0
int32_t __fastcall sub_6FAAA4E0()
{
	if (dword_6FB7545C == 5)
	{
		CLIENT_PushAppMode(2);
	}
	return dword_6FB7545C;
}

//D2Client.0x6FAAA500
void __cdecl sub_6FAAA500(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	byte_6FBA7994 = byte_6FBA7994 + '\x01';
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAAA530
void __cdecl sub_6FAAA530(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
	{
		byte_6FBA7994 = byte_6FBA7994 + '\x01';
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAAA560
uint32_t __cdecl sub_6FAAA560(uint32_t a1)
{
	int iVar1;
	D2CellFileStrc* pDVar2;
	DWORD DVar3;
	int iVar4;
	uint8_t bVar5;
	uint32_t uVar6;
	uint32_t* puVar7;
	D2GfxDataStrc* pDVar8;
	D2GfxDataStrc DStack_14c;
	CHAR aCStack_104[260];

	iVar1 = WINDOW_GetState();
	if (iVar1 == 0)
	{
		iVar1 = D2GFX_StartDraw(1, 0, 0, 0);
		if (iVar1 == 0)
		{
			return 0;
		}
		if ((int)(byte_6FBA7994 & 0xff) < dword_6FB75804)
		{
			iVar1 = (byte_6FBA7994 & 0xff) * 0xd;
			if (*(int*)((int)&dword_6FB75784 + iVar1) == 0)
			{
				wsprintfA(aCStack_104, "%s\\ui\\betascreens\\%s", "DATA\\GLOBAL",
				    *(uint32_t*)((int)&ptr_6FB75789 + iVar1));
				pDVar2 = CLIENT_LoadCellFile(aCStack_104, 0);
				uVar6 = byte_6FBA7994 & 0xff;
				*(D2CellFileStrc**)((int)&dword_6FB75784 + (byte_6FBA7994 & 0xff) * 0xd) = pDVar2;
				iVar1 = uVar6 * 0xd;
				DVar3 = GetTickCount();
				*(DWORD*)((int)&dword_6FB75780 + iVar1) = DVar3;
				D2Win_10177((&byte_6FB75788)[iVar1]);
			}
			pDVar8 = &DStack_14c;
			for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				pDVar8->pCurrentCell = nullptr;
				pDVar8 = (D2GfxDataStrc*)&pDVar8->pCellFile;
			}
			DStack_14c.pCellFile = *(D2CellFileStrc**)((int)&dword_6FB75784 + (byte_6FBA7994 & 0xff) * 0xd);
			DStack_14c.nDirection = 0;
			DStack_14c.nFrame = 0;
			TEXTURE_CelDraw(&DStack_14c, 0, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_14c.nFrame = 1;
			TEXTURE_CelDraw(&DStack_14c, 0x100, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_14c.nFrame = 2;
			TEXTURE_CelDraw(&DStack_14c, 0x200, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_14c.nFrame = 3;
			TEXTURE_CelDraw(&DStack_14c, 0, 0x1e0, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_14c.nFrame = 4;
			TEXTURE_CelDraw(&DStack_14c, 0x100, 0x1e0, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_14c.nFrame = 5;
			TEXTURE_CelDraw(&DStack_14c, 0x200, 0x1e0, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		}
		D2GFX_EndScene();
	}
	if ((dword_6FB75804 <= (int)(byte_6FBA7994 & 0xff)) ||
	    (DVar3 = GetTickCount(),
	        *(int*)((int)&dword_6FB75780 + (byte_6FBA7994 & 0xff) * 0xd) + 10000U < DVar3))
	{
		bVar5 = byte_6FBA7994 + 1;
		byte_6FBA7994 = bVar5;
		if (dword_6FB75804 <= (int)(uint32_t)bVar5)
		{
			iVar1 = 0;
			if (0 < dword_6FB75804)
			{
				puVar7 = &dword_6FB75784;
				iVar4 = dword_6FB75804;
				do
				{
					if ((D2CellFileStrc*)*puVar7 != nullptr)
					{
						CLIENT_FreeCellFile((D2CellFileStrc*)*puVar7);
						iVar4 = dword_6FB75804;
						*puVar7 = 0;
						puVar7[-1] = 0;
					}
					iVar1 = iVar1 + 1;
					puVar7 = (uint32_t*)((int)puVar7 + 0xd);
				} while (iVar1 < iVar4);
			}
			DVar3 = GetTickCount();
			FOG_Trace("slide show end %d\n", DVar3);
			CLIENT_SetExitToMenu(0);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAAA7D0
void __cdecl sub_6FAAA7D0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;

	iVar2 = gnScreenHeight;
	iVar1 = gnScreenHeight + -0x50;
	iVar5 = gnScreenWidth / 2;
	iVar3 = sub_6FB57BC0();
	iVar4 = sub_6FB57BD0();
	if ((((iVar5 + -0x30 <= iVar3) && (iVar3 <= iVar5 + 0x30)) && (iVar2 + -0x70 <= iVar4)) &&
	    (iVar4 <= iVar1))
	{
		dword_6FBA79E4 = 1;
		dword_6FBA79A8 = 0;
		dword_6FBA79AC = 0;
		dword_6FBA79C4 = 0;
		byte_6FBA79C8 = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	dword_6FBA79A8 = 0;
	dword_6FBA79AC = 0;
	dword_6FBA79C4 = 0;
	byte_6FBA79C8 = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAAA880
void __cdecl sub_6FAAA880(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;

	iVar2 = gnScreenHeight;
	iVar1 = gnScreenHeight + -0x50;
	iVar5 = gnScreenWidth / 2;
	dword_6FBA79E4 = 0;
	iVar3 = sub_6FB57BC0();
	iVar4 = sub_6FB57BD0();
	if ((((iVar5 + -0x30 <= iVar3) && (iVar3 <= iVar5 + 0x30)) && (iVar2 + -0x70 <= iVar4)) &&
	    (iVar4 <= iVar1))
	{
		dword_6FBA7958 = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	dword_6FBA79A8 = 0;
	dword_6FBA79AC = 0;
	dword_6FBA79C4 = 0;
	byte_6FBA79C8 = 0;
	pSMSGHANDLER_PARAMS->lResult = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAAA920
void __cdecl sub_6FAAA920(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
	{
		dword_6FBA7958 = 1;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAAA950
void __cdecl sub_6FAAA950(uint32_t a1, uint32_t a2, int a3, uint8_t* a4)
{
	if (-1 < a3 + -1)
	{
		do
		{
			(*(code*)a4)();
			a3 = a3 + -1;
		} while (a3 != 0);
	}
}

//D2Client.0x6FAAA980
uint32_t __cdecl sub_6FAAA980(uint32_t a1)
{
	char cVar1;
	uint16_t uVar2;
	uint8_t bVar3;
	int iVar4;
	int iVar5;
	Unicode* pUVar6;
	int iVar7;
	char* pcVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	char* pcVar11;
	char* pcVar12;
	D2GfxDataStrc* pDVar13;
	int iVar14;
	int iVar15;
	int bCentered;
	int iStack_524;
	D2GfxDataStrc DStack_520;
	Unicode aUStack_4d8[130];
	char acStack_3d4[100];
	char acStack_370[100];
	Unicode aUStack_30c[130];
	char acStack_208[260];
	char acStack_104[260];

	iVar4 = WINDOW_GetState();
	if (iVar4 != 0)
		goto LAB_6faab193;
	iVar4 = D2GFX_StartDraw(1, 0, 0, 0);
	if (iVar4 == 0)
	{
		return 0;
	}
	if (dword_6FBA79E8 == 0)
	{
		if (dword_6FBA77C4 == 0)
		{
			iVar4 = 0;
			do
			{
				cVar1 = "endgame"[iVar4];
				*(char*)((int)&aUStack_4d8[0].ch + iVar4) = cVar1;
				iVar4 = iVar4 + 1;
			} while (cVar1 != '\0');
		}
		else
		{
			iVar4 = 0;
			do
			{
				cVar1 = "endgame2"[iVar4];
				*(char*)((int)&aUStack_4d8[0].ch + iVar4) = cVar1;
				iVar4 = iVar4 + 1;
			} while (cVar1 != '\0');
		}
		sprintf((char*)aUStack_30c, "%s\\ui\\menu\\%s", "DATA\\GLOBAL", aUStack_4d8);
		dword_6FBA79E8 = (uint32_t)(CLIENT_LoadCellFile((char*)aUStack_30c, 0));
		sprintf(acStack_208, "%s\\Palette\\%s\\pal.dat", "DATA\\GLOBAL", aUStack_4d8);
		sprintf(acStack_104, "%s\\Palette\\%s\\pal.pl2", "DATA\\GLOBAL", aUStack_4d8);
		D2Win_10028(acStack_208, acStack_104);
	}
	if (dword_6FBA79EC == 0)
	{
		sprintf(acStack_208, "%s\\ui\\menu\\endgameok", "DATA\\GLOBAL");
		dword_6FBA79EC = (uint32_t)(CLIENT_LoadCellFile(acStack_208, 0));
	}
	pDVar13 = &DStack_520;
	for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		pDVar13->pCurrentCell = nullptr;
		pDVar13 = (D2GfxDataStrc*)&pDVar13->pCellFile;
	}
	DStack_520.nDirection = 0;
	DStack_520.pCellFile = (D2CellFileStrc*)(dword_6FBA79E8);
	D2Win_10179();
	DStack_520.nFrame = 0;
	if (dword_6FBA77C4 == 0)
	{
		TEXTURE_CelDraw(&DStack_520, 0, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 1;
		TEXTURE_CelDraw(&DStack_520, 0x100, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 2;
		TEXTURE_CelDraw(&DStack_520, 0, gnScreenHeight + -1, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 3;
		TEXTURE_CelDraw(&DStack_520, 0x100, gnScreenHeight + -1, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 4;
		TEXTURE_CelDraw(&DStack_520, gnScreenWidth / 2, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 5;
		TEXTURE_CelDraw(&DStack_520, gnScreenWidth / 2 + 0x100, 0x100, 0xffffffff, DRAWMODE_NORMAL,
		    nullptr);
		DStack_520.nFrame = 6;
		TEXTURE_CelDraw(&DStack_520, gnScreenWidth / 2, gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 7;
		iVar5 = gnScreenWidth / 2 + 0x100;
		iVar4 = gnScreenHeight;
	}
	else
	{
		TEXTURE_CelDraw(&DStack_520, 0, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 1;
		TEXTURE_CelDraw(&DStack_520, 0x100, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 2;
		TEXTURE_CelDraw(&DStack_520, 0x200, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 3;
		TEXTURE_CelDraw(&DStack_520, 0x300, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 4;
		TEXTURE_CelDraw(&DStack_520, 0, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 5;
		TEXTURE_CelDraw(&DStack_520, 0x100, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 6;
		TEXTURE_CelDraw(&DStack_520, 0x200, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 7;
		TEXTURE_CelDraw(&DStack_520, 0x300, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 8;
		TEXTURE_CelDraw(&DStack_520, 0, 600, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 9;
		TEXTURE_CelDraw(&DStack_520, 0x100, 600, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_520.nFrame = 10;
		TEXTURE_CelDraw(&DStack_520, 0x200, 600, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		iVar4 = 600;
		DStack_520.nFrame = 0xb;
		iVar5 = 0x300;
	}
	TEXTURE_CelDraw(&DStack_520, iVar5, iVar4, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2Win_10127_SetFont(D2FONT_FONT42);
	pUVar6 = aUStack_4d8;
	iVar4 = 100;
	iVar5 = gnScreenWidth / 2;
	do
	{
		pUVar6 = pUVar6 + 1;
		iVar4 = iVar4 + -1;
	} while (iVar4 != 0);
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ea));
	Unicode::strcpy(aUStack_4d8, pUVar6);
	iVar4 = D2Win_10121_GetTextWidth(aUStack_4d8);
	iVar7 = 0x3e;
	if (dword_6FBA77C4 != 0)
	{
		iVar7 = 100;
	}
	iVar15 = 0;
	iVar14 = 4;
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ea));
	D2Win_10117_DrawText(pUVar6, iVar5 - iVar4 / 2, iVar7, iVar14, iVar15);
	if (dword_6FBA77C4 == 0)
	{
		pUVar6 = aUStack_4d8;
		iVar4 = 100;
		iVar5 = gnScreenWidth / 2;
		do
		{
			pUVar6 = pUVar6 + 1;
			iVar4 = iVar4 + -1;
		} while (iVar4 != 0);
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13eb));
		Unicode::strcpy(aUStack_4d8, pUVar6);
		iVar4 = D2Win_10121_GetTextWidth(aUStack_4d8);
		iVar15 = 0;
		iVar14 = 4;
		iVar7 = 0x6b;
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13eb));
		D2Win_10117_DrawText(pUVar6, iVar5 - iVar4 / 2, iVar7, iVar14, iVar15);
	}
	iVar4 = 0xe8;
	if (dword_6FBA77C4 != 0)
	{
		iVar4 = 0x110;
	}
	pUVar6 = aUStack_4d8;
	iVar5 = 100;
	iVar7 = gnScreenWidth / 2;
	do
	{
		pUVar6 = pUVar6 + 1;
		iVar5 = iVar5 + -1;
	} while (iVar5 != 0);
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ec));
	Unicode::strcpy(aUStack_4d8, pUVar6);
	iVar5 = D2Win_10121_GetTextWidth(aUStack_4d8);
	iVar15 = 0;
	iVar14 = 4;
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ec));
	D2Win_10117_DrawText(pUVar6, iVar7 - iVar5 / 2, iVar4, iVar14, iVar15);
	iVar4 = (int)(CLIENT_GetConfig());
	pcVar8 = (char*)(iVar4 + 0xb8);
	iVar5 = -(int)pcVar8;
	do
	{
		cVar1 = *pcVar8;
		pcVar8[(int)(acStack_370 + iVar5)] = cVar1;
		pcVar8 = pcVar8 + 1;
	} while (cVar1 != '\0');
	Unicode::toUnicode(aUStack_30c, acStack_370, 0x40);
	iVar5 = D2Win_10121_GetTextWidth(aUStack_30c);
	D2Win_10117_DrawText(aUStack_30c, gnScreenWidth / 2 - iVar5 / 2, 0xbb, 4, 0);
	bVar3 = byte_6FBA7894;
	uVar9 = byte_6FBA795C & 0xff;
	uVar2 = *(uint16_t*)(iVar4 + 0x1ea);
	pUVar6 = aUStack_4d8;
	uVar10 = uVar2 & 4;
	iStack_524 = 100;
	do
	{
		pUVar6 = pUVar6 + 1;
		iStack_524 = iStack_524 + -1;
	} while (iStack_524 != 0);
	if (uVar9 == 0)
	{
		iVar4 = ((uVar2 & 0x20) != 0) + 4;
		if ((uVar2 & 4) == 0)
		{
			uVar10 = 0;
		}
	LAB_6faab006:
		pcVar8 = (char*)D2Win_10161((uint32_t)bVar3, iVar4, uVar10, uVar2 & 0x20);
		if (pcVar8 != nullptr)
		{
			iVar4 = -(int)pcVar8;
			do
			{
				cVar1 = *pcVar8;
				pcVar8[(int)(acStack_3d4 + iVar4)] = cVar1;
				pcVar8 = pcVar8 + 1;
			} while (cVar1 != '\0');
			uVar9 = 0xffffffff;
			pcVar8 = acStack_370;
			do
			{
				pcVar12 = pcVar8;
				if (uVar9 == 0)
					break;
				uVar9 = uVar9 - 1;
				pcVar12 = pcVar8 + 1;
				cVar1 = *pcVar8;
				pcVar8 = pcVar12;
			} while (cVar1 != '\0');
			uVar9 = ~uVar9;
			iVar4 = -1;
			pcVar8 = acStack_3d4;
			do
			{
				pcVar11 = pcVar8;
				if (iVar4 == 0)
					break;
				iVar4 = iVar4 + -1;
				pcVar11 = pcVar8 + 1;
				cVar1 = *pcVar8;
				pcVar8 = pcVar11;
			} while (cVar1 != '\0');
			pcVar8 = pcVar12 + -uVar9;
			pcVar12 = pcVar11 + -1;
			for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1)
			{
				*(uint32_t*)pcVar12 = *(uint32_t*)pcVar8;
				pcVar8 = pcVar8 + 4;
				pcVar12 = pcVar12 + 4;
			}
			for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1)
			{
				*pcVar12 = *pcVar8;
				pcVar8 = pcVar8 + 1;
				pcVar12 = pcVar12 + 1;
			}
			Unicode::toUnicode(aUStack_4d8, acStack_3d4, 0x40);
			iVar4 = D2Win_10121_GetTextWidth(aUStack_4d8);
			iVar5 = 0x115;
			if (dword_6FBA77C4 != 0)
			{
				iVar5 = 0x165;
			}
			D2Win_10117_DrawText(aUStack_4d8, gnScreenWidth / 2 - iVar4 / 2, iVar5, 4, 0);
		}
	}
	else
	{
		if (uVar9 == 1)
		{
			iVar4 = (uint32_t)((uVar2 & 0x20) != 0) * 2 + 8;
			if ((uVar2 & 4) == 0)
			{
				uVar10 = 0;
			}
			goto LAB_6faab006;
		}
		if (uVar9 == 2)
		{
			iVar4 = (-(uint32_t)((uVar2 & 0x20) != 0) & 3) + 0xc;
			if ((uVar2 & 4) == 0)
			{
				uVar10 = 0;
			}
			goto LAB_6faab006;
		}
	}
	D2Win_10127_SetFont(D2FONT_FONT16);
	pDVar13 = &DStack_520;
	for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		pDVar13->pCurrentCell = nullptr;
		pDVar13 = (D2GfxDataStrc*)&pDVar13->pCellFile;
	}
	DStack_520.nFrame = (uint32_t)(dword_6FBA79E4 != 0);
	DStack_520.pCellFile = (D2CellFileStrc*)(dword_6FBA79EC);
	DStack_520.nDirection = 0;
	TEXTURE_CelDraw(&DStack_520, gnScreenWidth / 2 + -0x30, gnScreenHeight + -0x50, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	pUVar6 = aUStack_4d8;
	iVar4 = 100;
	iVar5 = gnScreenWidth / 2;
	do
	{
		pUVar6 = pUVar6 + 1;
		iVar4 = iVar4 + -1;
	} while (iVar4 != 0);
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ee));
	Unicode::strcpy(aUStack_4d8, pUVar6);
	iVar4 = D2Win_10121_GetTextWidth(aUStack_4d8);
	iVar7 = 0;
	if (dword_6FBA79E4 != 0)
	{
		iVar7 = 2;
	}
	bCentered = 0;
	iVar15 = 0;
	iVar14 = gnScreenHeight + -0x58 + iVar7;
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ee));
	D2Win_10117_DrawText(pUVar6, (iVar5 - iVar4 / 2) - iVar7, iVar14, iVar15, bCentered);
	sub_6FB57AC0();
	D2GFX_EndScene();
LAB_6faab193:
	if (dword_6FBA7958 == 0)
	{
		return 0;
	}
	if (dword_6FBA79E8 != 0)
	{
		CLIENT_FreeCellFile((D2CellFileStrc*)(dword_6FBA79E8));
		dword_6FBA79E8 = (uint32_t)(nullptr);
	}
	if (dword_6FBA79EC != 0)
	{
		CLIENT_FreeCellFile((D2CellFileStrc*)(dword_6FBA79EC));
		dword_6FBA79EC = (uint32_t)(nullptr);
	}
	CLIENT_SetExitToMenu(0);
	return 1;
}

//D2Client.0x6FAAB1F0
void __cdecl sub_6FAAB1F0()
{
	dword_6FBA7954 = 1;
	*(uint16_t*)(gpConfig + 0x1ea) =
	    (byte_6FBA795C + 1) * 0x400 | *(uint16_t*)(gpConfig + 0x1ea) & 0xe0ff;
}

//D2Client.0x6FAAB230
void __fastcall sub_6FAAB230()
{
	dword_6FBA797C = 1;
}

//D2Client.0x6FAAB240
void __cdecl sub_6FAAB240()
{
	dword_6FBA7970 = 1;
}

//D2Client.0x6FAAB250
bool __cdecl sub_6FAAB250()
{
	int iVar1;

	iVar1 = GetSystemMetrics(0x4b);
	if (((iVar1 != 0) && (dword_6FBA7998 != 0)) && (dword_6FBA78C0 == 1))
	{
		return dword_6FBA78B8 == 0;
	}
	return false;
}

//D2Client.0x6FAAB290
bool __cdecl sub_6FAAB290()
{
	int iVar1;

	iVar1 = GetSystemMetrics(0x4b);
	if ((iVar1 != 0) && (dword_6FBA7998 != 0))
	{
		if (dword_6FBA78C0 == 1)
		{
			return dword_6FBA78B8 != 0;
		}
		if ((dword_6FBA78C0 == 2) && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))
		{
			return true;
		}
	}
	return false;
}

//D2Client.0x6FAAB2E0
uint32_t __cdecl sub_6FAAB2E0()
{
	if (dword_6FBA7998 != 0)
	{
		if (dword_6FBA78C0 == 1)
		{
			return 1;
		}
		if (dword_6FBA78C0 == 2)
		{
			if (dword_6FBA78B4 == 4)
			{
				return 1;
			}
			if (dword_6FBA78B4 == 5)
			{
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAAB320
uint32_t __cdecl sub_6FAAB320()
{
	if ((((dword_6FBA7998 != 0) && (dword_6FBA78C0 != 1)) && (dword_6FBA78C0 == 2)) &&
	    ((dword_6FBA78B4 != 4 && (dword_6FBA78B4 == 5))))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FAAB350
void __fastcall sub_6FAAB350(int32_t a1)
{
	dword_6FBA7978 = a1;
}

//D2Client.0x6FAAB360
int __cdecl sub_6FAAB360()
{
	return dword_6FBA7944;
}

//D2Client.0x6FAAB370
// TODO: decompilation needs review (extraout)
int32_t __fastcall sub_6FAAB370()
{
	bool bVar1;
	bool bVar2;
	DWORD DVar3;
	BOOL BVar4;
	HWND__* pHVar5;
	int iVar6;
	DWORD DVar7;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	uint32_t extraout_var_02;
	uint8_t bVar8;
	uint32_t* puVar9;
	uint32_t uVar10;
	tagMSG tStack_1c;

	if (dword_6FBA799C == 0)
	{
		CLIENT_SetExitToMenu(1);
	}
	DVar3 = GetTickCount();
	FOG_Trace("[D2CLIENT]  Start entering at %d\n", DVar3);
	byte_6FBA78B0 = 0x94;
	BVar4 = GetVersionExA((LPOSVERSIONINFOA)&byte_6FBA78B0);
	if (BVar4 != 0)
	{
		dword_6FBA7998 = 1;
	}
	sub_6FAB6AC0();
	VIDEO_Initialize();
	WNDPROC_PushRegisterState();
	sub_6FB575F0(0);
	uVar10 = 10;
	pHVar5 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75818), uVar10);
	sub_6FAAC1B0();
	if (((gnGameType == 3) || (gnGameType == 7)) || (gnGameType == 9))
	{
		sub_6FAAD4B0(byte_6FBA7748, dword_6FBA7890);
	}
	else
	{
		sub_6FAA69A0();
		sub_6FAAD260();
		if ((gnGameType == 6) || (gnGameType == 8))
		{
			dword_6FBA79A0 = 0;
			dword_6FBA79A4 = 0;
			InitializeCriticalSection((LPCRITICAL_SECTION)&byte_6FBA77D4);
			ghandle_6FBA7824 =
			    CreateThread((LPSECURITY_ATTRIBUTES)0x0, 0, (LPTHREAD_START_ROUTINE)(sub_6FAAA3B0), (LPVOID)0x0, 0,
			        (LPDWORD)&byte_6FBA774C);
		}
	}
	sub_6FB53D90();
	sub_6FAA9450();
	iVar6 = sub_6FAAEAA0();
	if ((iVar6 != 0) || (iVar6 = sub_6FAAEB00(), iVar6 != 0))
	{
		do
		{
			BVar4 = PeekMessageA(&tStack_1c, (HWND)0x0, 0, 0, 1);
		} while (BVar4 != 0);
		iVar6 = sub_6FAAEB00();
		if (iVar6 == 0)
		{
			iVar6 = sub_6FAAEAA0();
			if (iVar6 != 0)
			{
				sub_6FAAEAD0();
			}
		}
		else
		{
			sub_6FAAEAF0();
		}
	}
	FOG_SetMemoryPoolSystemMode(nullptr, 0);
	if ((gnGameType == 6) || (gnGameType == 8))
	{
		EnterCriticalSection((LPCRITICAL_SECTION)&byte_6FBA77D4);
		dword_6FBA79A4 = 1;
		LeaveCriticalSection((LPCRITICAL_SECTION)&byte_6FBA77D4);
	}
	DVar7 = GetTickCount();
	iVar6 = DVar7 - DVar3;
	DVar3 = GetTickCount();
	FOG_Trace("[D2CLIENT]  Finish entering at %d.  Elapsed: %d\n", DVar3, iVar6);
	CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAA9AF0));
	DVar3 = GetTickCount();
	FOG_Trace("[D2CLIENT]  Start closing at %d.\n", DVar3);
	D2SOUND_10029(0xb4);
	sub_6FB54CB0();
	if (((dword_6FBA799C != 0) && (dword_6FBA7954 == 0)) && (dword_6FBA797C == 0))
	{
		CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAA98C0));
	}
	iVar6 = sub_6FAAEAA0();
	if (iVar6 != 0)
	{
		sub_6FAAE810();
	}
	if (dword_6FBA7950 == 0)
	{
		if (dword_6FBA7954 == 0)
		{
			if (dword_6FBA7978 != 0)
			{
				VIDEO_Play(7);
				dword_6FBA797C = 1;
			}
		}
		else
		{
			VIDEO_Play(5);
			uVar10 = 10;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75818), uVar10);
			iVar6 = GetSystemMetrics(0x4b);
			if ((iVar6 != 0) && (dword_6FBA7998 != 0))
			{
				if (dword_6FBA78C0 == 1)
				{
					if (dword_6FBA78B8 != 0)
						goto LAB_6faab6c5;
				}
				else if ((dword_6FBA78C0 == 2) && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))
				{
				LAB_6faab6c5:
					uVar10 = 1;
					pHVar5 = WINDOW_GetWindow();
					WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75890), uVar10);
				}
			}
			iVar6 = sub_6FAAB2E0();
			if (iVar6 != 0)
			{
				uVar10 = 2;
				pHVar5 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7589C), uVar10);
			}
			iVar6 = sub_6FAAB320();
			if (iVar6 != 0)
			{
				uVar10 = 2;
				pHVar5 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758B4), uVar10);
			}
			bVar1 = sub_6FAAB250();
			if ((D2C_ZEXT(bVar1) != 0) && (dword_6FB7581C != 0))
			{
				uVar10 = 1;
				pHVar5 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758CC), uVar10);
			}
			CLIENT_SetResolution(0);
			uVar10 = 9;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75978), uVar10);
			CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAAA980));
		}
	}
	else
	{
		DVar7 = GetTickCount();
		FOG_Trace("slide show start %d\n", DVar7);
		uVar10 = 10;
		pHVar5 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75818), uVar10);
		iVar6 = GetSystemMetrics(0x4b);
		if ((iVar6 != 0) && (dword_6FBA7998 != 0))
		{
			if (dword_6FBA78C0 == 1)
			{
				if (dword_6FBA78B8 != 0)
					goto LAB_6faab5d3;
			}
			else if ((dword_6FBA78C0 == 2) && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))
			{
			LAB_6faab5d3:
				uVar10 = 1;
				pHVar5 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75890), uVar10);
			}
		}
		iVar6 = sub_6FAAB2E0();
		if (iVar6 != 0)
		{
			uVar10 = 2;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7589C), uVar10);
		}
		iVar6 = sub_6FAAB320();
		if (iVar6 != 0)
		{
			uVar10 = 2;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758B4), uVar10);
		}
		bVar1 = sub_6FAAB250();
		if ((D2C_ZEXT(bVar1) != 0) && (dword_6FB7581C != 0))
		{
			uVar10 = 1;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758CC), uVar10);
		}
		uVar10 = 7;
		pHVar5 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75920), uVar10);
		CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAAA560));
	}
	bVar1 = true;
	if (dword_6FBA797C != 0)
	{
		uVar10 = byte_6FBA795C & 0xff;
		bVar8 = *(uint8_t*)(gpConfig + 0x1eb) & 0x1f;
		if (uVar10 == 0)
		{
			if (bVar8 != 8)
				goto LAB_6faab7b1;
		LAB_6faab7b6:
			bVar1 = false;
		}
		else if (uVar10 == 1)
		{
		LAB_6faab7b1:
			if (bVar8 == 0xc)
				goto LAB_6faab7b6;
		}
		*(uint16_t*)(gpConfig + 0x1ea) =
		    (short)(uVar10 << 10) + 0x500U | *(uint16_t*)(gpConfig + 0x1ea) & 0xe0ff;
		if (bVar1)
		{
			uVar10 = 10;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75818), uVar10);
			iVar6 = GetSystemMetrics(0x4b);
			if (iVar6 == 0)
				goto LAB_6faab83a;
			if (dword_6FBA7998 != 0)
			{
				if (dword_6FBA78C0 == 1)
				{
					if (dword_6FBA78B8 != 0)
						goto LAB_6faab827;
				}
				else if ((dword_6FBA78C0 == 2) && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))
				{
				LAB_6faab827:
					uVar10 = 1;
					pHVar5 = WINDOW_GetWindow();
					WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75890), uVar10);
				}
			LAB_6faab83a:
				if ((dword_6FBA7998 != 0) &&
				    ((dword_6FBA78C0 == 1 ||
				        ((dword_6FBA78C0 == 2 && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))))))
				{
					uVar10 = 2;
					pHVar5 = WINDOW_GetWindow();
					WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7589C), uVar10);
				}
			}
			iVar6 = sub_6FAAB320();
			if (iVar6 != 0)
			{
				uVar10 = 2;
				pHVar5 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758B4), uVar10);
			}
			bVar2 = sub_6FAAB250();
			if ((D2C_ZEXT(bVar2) != 0) && (dword_6FB7581C != 0))
			{
				uVar10 = 1;
				pHVar5 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758CC), uVar10);
			}
			CLIENT_SetResolution(2);
			uVar10 = 9;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75978), uVar10);
			CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAAA980));
		}
	}
	DVar7 = GetTickCount();
	FOG_Trace("game close start %d\n", DVar7);
	sub_6FAA7440();
	sub_6FAADFB0();
	sub_6FB28040();
	if (ghAct != nullptr)
	{
		DUNGEON_FreeAct(ghAct);
	}
	ghAct = nullptr;
	D2CMP_SpriteFreeAsyncLoads();
	D2CMP_TileFreeAsyncLoads();
	MEMORY_FreePartitions(0);
	sub_6FAB70D0(dword_6FBA7990);
	dword_6FBA7990 = 0;
	sub_6FB202C0();
	MEMORY_Nop();
	sub_6FAA5DC0();
	sub_6FAA6AB0();
	FOG_DestroyMemoryPoolSystem(ptr_6FBA7758);
	puVar9 = &dword_6FBA7750;
	for (iVar6 = 0x20; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*puVar9 = 0;
		puVar9 = puVar9 + 1;
	}
	D2_FREE(ptr_6FBA7988);
	DVar7 = GetTickCount();
	FOG_Trace("game close end %d\n", DVar7);
	sub_6FB54860();
	sub_6FAB6EB0();
	sub_6FB576B0();
	D2Win_10006_ClearDrawCaches();
	CLIENT_PushAppMode(4);
	if (dword_6FBA7950 != 0)
	{
		uVar10 = 7;
		pHVar5 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75920), uVar10);
		dword_6FBA7950 = 0;
		goto LAB_6faabaf4;
	}
	if (dword_6FBA7954 != 0)
	{
		uVar10 = 9;
		pHVar5 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75978), uVar10);
		dword_6FBA7954 = 0;
		goto LAB_6faabaf4;
	}
	if ((bVar1) && (dword_6FBA797C != 0))
	{
		uVar10 = 9;
		pHVar5 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75978), uVar10);
		dword_6FBA797C = 0;
		goto LAB_6faabaf4;
	}
	uVar10 = 10;
	pHVar5 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75818), uVar10);
	iVar6 = GetSystemMetrics(0x4b);
	if (iVar6 == 0)
		goto LAB_6faaba7f;
	if (dword_6FBA7998 != 0)
	{
		if (dword_6FBA78C0 == 1)
		{
			if (dword_6FBA78B8 != 0)
				goto LAB_6faaba6c;
		}
		else if ((dword_6FBA78C0 == 2) && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))
		{
		LAB_6faaba6c:
			uVar10 = 1;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75890), uVar10);
		}
	LAB_6faaba7f:
		if ((dword_6FBA7998 != 0) &&
		    ((dword_6FBA78C0 == 1 || ((dword_6FBA78C0 == 2 && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))))))
		{
			uVar10 = 2;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7589C), uVar10);
		}
	}
	iVar6 = sub_6FAAB320();
	if (iVar6 != 0)
	{
		uVar10 = 2;
		pHVar5 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758B4), uVar10);
	}
	bVar1 = sub_6FAAB250();
	if ((D2C_ZEXT(bVar1) != 0) && (dword_6FB7581C != 0))
	{
		uVar10 = 1;
		pHVar5 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758CC), uVar10);
	}
LAB_6faabaf4:
	DVar7 = GetTickCount();
	iVar6 = DVar7 - DVar3;
	DVar3 = GetTickCount();
	FOG_Trace("[D2CLIENT]  Finish closing at %d.  Elapsed: %d\n", DVar3, iVar6);
	if (((((gnGameType == 2) || (gnGameType == 6)) || (gnGameType == 3)) || (gnGameType == 7)) && (dword_6FBA7944 != 0))
	{
		(**(code**)(dword_6FBA7944 + 0xc4))();
	}
	return 6;
}

//D2Client.0x6FAABB40
int32_t __fastcall sub_6FAABB40()
{
	sub_6FAB6EB0();
	sub_6FB576B0();
	sub_6FAAE910();
	sub_6FAAF4E0();
	sub_6FAB14C0();
	WNDPROC_PopRegisterState();
	return 1;
}

//D2Client.0x6FAABB70
void __fastcall sub_6FAABB70(int a1)
{
	if (*(char*)(a1 + 0x214) != '\0')
	{
		D2GAME_10036_PLRSAVE_EnableSaveFileWriting(0);
		return;
	}
}

//D2Client.0x6FAABB90
void __fastcall sub_6FAABB90(int a1)
{
	int iVar1;

	iVar1 = *(int*)(a1 + 0x1fa);
	if (iVar1 != 0)
	{
		D2_ASSERT(5 >= iVar1);
		D2_ASSERT(iVar1 >= 1);
		GAME_SetGlobalAct(iVar1 + -1);
	}
}

//D2Client.0x6FAABBF0
void __fastcall sub_6FAABBF0(int a1)
{
	int iVar1;
	LPCSTR pCVar2;
	char* pcVar3;
	bool bVar4;

	iVar1 = 2;
	bVar4 = true;
	pCVar2 = (LPCSTR)(a1 + 0x32);
	pcVar3 = "0";
	do
	{
		if (iVar1 == 0)
			break;
		iVar1 = iVar1 + -1;
		bVar4 = *pCVar2 == *pcVar3;
		pCVar2 = pCVar2 + 1;
		pcVar3 = pcVar3 + 1;
	} while (bVar4);
	if (!bVar4)
	{
		lstrcpyA("207.82.87.243", (LPCSTR)(a1 + 0x32));
	}
	lstrcpyA((LPSTR)(&byte_6FBA7898), (LPCSTR)(a1 + 0x1a));
	gnGameType = *(int*)(a1 + 0x14);
	byte_6FBA7748 = *(uint16_t*)(a1 + 0x18);
	dword_6FBA7890 = *(uint32_t*)(a1 + 0x223);
}

//D2Client.0x6FAABC50
void __fastcall sub_6FAABC50(int a1)
{
	int iVar1;
	char* pcVar2;
	char* pcVar3;
	bool bVar4;

	iVar1 = 2;
	bVar4 = true;
	pcVar2 = (char*)(a1 + 0x4a);
	pcVar3 = "0";
	do
	{
		if (iVar1 == 0)
			break;
		iVar1 = iVar1 + -1;
		bVar4 = *pcVar2 == *pcVar3;
		pcVar2 = pcVar2 + 1;
		pcVar3 = pcVar3 + 1;
	} while (bVar4);
	if (!bVar4)
	{
		lstrcpyA("207.82.87.139", (LPCSTR)(a1 + 0x32));
	}
}

//D2Client.0x6FAABC80
void __fastcall sub_6FAABC80(int a1)
{
	int iVar1;
	LPCSTR pCVar2;
	char* pcVar3;
	bool bVar4;

	iVar1 = 2;
	bVar4 = true;
	pCVar2 = (LPCSTR)(a1 + 0x62);
	pcVar3 = "0";
	do
	{
		if (iVar1 == 0)
			break;
		iVar1 = iVar1 + -1;
		bVar4 = *pCVar2 == *pcVar3;
		pCVar2 = pCVar2 + 1;
		pcVar3 = pcVar3 + 1;
	} while (bVar4);
	if (!bVar4)
	{
		lstrcpyA("207.82.87.133", (LPCSTR)(a1 + 0x62));
	}
}

//D2Client.0x6FAABCB0
void __fastcall sub_6FAABCB0(int a1)
{
	if (*(char*)(a1 + 0x80) != '\0')
	{
		byte_6FBA7894 = 0;
	}
	if (*(char*)(a1 + 0x81) != '\0')
	{
		byte_6FBA7894 = 3;
	}
	if (*(char*)(a1 + 0x82) != '\0')
	{
		byte_6FBA7894 = 1;
	}
	if (*(char*)(a1 + 0x83) != '\0')
	{
		byte_6FBA7894 = 2;
	}
	if (*(char*)(a1 + 0x84) != '\0')
	{
		byte_6FBA7894 = 4;
	}
	if (*(char*)(a1 + 0x85) != '\0')
	{
		byte_6FBA7894 = 5;
	}
	if (*(char*)(a1 + 0x86) != '\0')
	{
		byte_6FBA7894 = 6;
	}
}

//D2Client.0x6FAABD30
void __fastcall sub_6FAABD30(int a1)
{
	if (*(char*)(a1 + 4) != '\0')
	{
		WNDPROC_SetDisplayTypeGDI();
		return;
	}
}

//D2Client.0x6FAABD40
void __fastcall sub_6FAABD40(int a1)
{
	if (*(char*)(a1 + 5) != '\0')
	{
		WNDPROC_SetDisplayTypeGlide();
		return;
	}
}

//D2Client.0x6FAABD50
void __fastcall sub_6FAABD50(int a1)
{
	if (*(char*)(a1 + 6) != '\0')
	{
		WNDPROC_SetDisplayTypeOpenGL();
		return;
	}
}

//D2Client.0x6FAABD60
void __fastcall sub_6FAABD60(int a1)
{
	if (*(char*)(a1 + 8) != '\0')
	{
		WNDPROC_SetDisplayTypeDirect3D();
		return;
	}
}

//D2Client.0x6FAABD70
void __fastcall sub_6FAABD70(int a1)
{
	if (*(char*)(a1 + 7) != '\0')
	{
		WNDPROC_SetDisplayTypeRave();
		return;
	}
}

//D2Client.0x6FAABD80
void __fastcall sub_6FAABD80(int a1)
{
	if (*(int*)(a1 + 0xb) != 0)
	{
		WNDPROC_SetGamma(*(int*)(a1 + 0xb));
		return;
	}
}

//D2Client.0x6FAABD90
void __fastcall sub_6FAABD90(int a1)
{
	if (*(char*)(a1 + 0xf) != '\0')
	{
		D2GFX_EnableVSync();
		return;
	}
}

//D2Client.0x6FAABDA0
void __fastcall sub_6FAABDA0(int a1)
{
	if (*(char*)(a1 + 0x211) != '\0')
	{
		LOG_11102((void*)0x1);
		return;
	}
}

//D2Client.0x6FAABDC0
void __fastcall sub_6FAABDC0(int a1)
{
	if (*(int*)(a1 + 0x215) != 0)
	{
		GAME_SetInitSeed(*(int*)(a1 + 0x215));
	}
}

//D2Client.0x6FAABDE0
void __fastcall sub_6FAABDE0(int a1)
{
	char* _Source;
	char cVar1;
	int iVar2;
	uint32_t uVar3;
	size_t _Count;
	char* pcVar4;
	char* pcVar5;
	bool bVar6;

	_Source = (char*)(a1 + 0xb8);
	iVar2 = 2;
	bVar6 = true;
	pcVar4 = _Source;
	pcVar5 = "0";
	do
	{
		if (iVar2 == 0)
			break;
		iVar2 = iVar2 + -1;
		bVar6 = *pcVar4 == *pcVar5;
		pcVar4 = pcVar4 + 1;
		pcVar5 = pcVar5 + 1;
	} while (bVar6);
	if (!bVar6)
	{
		uVar3 = 0xffffffff;
		pcVar4 = _Source;
		do
		{
			if (uVar3 == 0)
				break;
			uVar3 = uVar3 - 1;
			cVar1 = *pcVar4;
			pcVar4 = pcVar4 + 1;
		} while (cVar1 != '\0');
		gszPlayerName[0] = 0;
		_Count = ~uVar3;
		byte_6FBA7814 = 0;
		byte_6FBA7818 = 0;
		byte_6FBA781C = 0;
		if (0x10 < (int)_Count)
		{
			_Count = 0x10;
		}
		strncpy(gszPlayerName, _Source, _Count);
	}
}

//D2Client.0x6FAABE40
void __fastcall sub_6FAABE40(int a1)
{
	SStrCopy((char*)(&byte_6FBA77F0), (char*)(a1 + 0xd0), 0x20);
}

//D2Client.0x6FAABE60
void __cdecl sub_6FAABE60()
{
	sub_6FAA69C0(0);
}

//D2Client.0x6FAABE70
void __fastcall sub_6FAABE70(int a1)
{
	sub_6FAA69E0((uint32_t) * (uint8_t*)(a1 + 0x1e8));
}

//D2Client.0x6FAABE80
void __fastcall sub_6FAABE80(int a1)
{
	if (*(int*)(a1 + 0x21f) != 0)
	{
		dword_6FBA7944 = *(int*)(a1 + 0x21f);
	}
}

//D2Client.0x6FAABE90
void __cdecl sub_6FAABE90()
{
	return;
}

//D2Client.0x6FAABEA0
void __fastcall sub_6FAABEA0(int a1)
{
	if (*(uint8_t*)(a1 + 0x201) != 0)
	{
		D2CMP_SetCompressedDataMode((uint32_t) * (uint8_t*)(a1 + 0x201));
	}
}

//D2Client.0x6FAABEC0
void __fastcall sub_6FAABEC0(int a1)
{
	DATATBLS_ToggleCompileTxtFlag((uint32_t)(*(char*)(a1 + 0x210) == '\0'));
}

//D2Client.0x6FAABEE0
// TODO: parameters differ from the decompiled ones, body needs review
BOOL __fastcall CONFIG_Apply(D2ConfigStrc* pConfig)
{
	uint32_t uVar1;

	dword_6FB759E4 = 1;
	uVar1 = 0;
	do
	{
		if (*(code**)((int)&ptr_6FB759E8 + uVar1) != nullptr)
		{
			(**(code**)((int)&ptr_6FB759E8 + uVar1))();
		}
		uVar1 = uVar1 + 4;
	} while (uVar1 < 0xc0);
	return dword_6FB759E4;
}

//D2Client.0x6FAABF20
uint32_t __cdecl sub_6FAABF20()
{
	return dword_6FBA7970;
}

//D2Client.0x6FAABF30
void __cdecl sub_6FAABF30()
{
	dword_6FB75810 = 0x10;
	dword_6FB7580C = 0x10;
	dword_6FBA79A8 = 0;
	dword_6FBA79AC = 0;
	dword_6FBA79C4 = 0;
	byte_6FBA79C8 = 0;
	sub_6FAB5D40();
}

//D2Client.0x6FAABF60
void __cdecl sub_6FAABF60()
{
	dword_6FBA79A8 = 0;
	dword_6FBA79AC = 0;
	dword_6FBA79C4 = 0;
	byte_6FBA79C8 = 0;
}

//D2Client.0x6FAABF80
uint32_t __fastcall sub_6FAABF80()
{
	return dword_6FBA7768;
}

//D2Client.0x6FAABF90
uint32_t __cdecl sub_6FAABF90()
{
	return dword_6FBA775C;
}

//D2Client.0x6FAABFA0
uint32_t __cdecl sub_6FAABFA0()
{
	return dword_6FBA7798;
}

//D2Client.0x6FAABFB0
void __fastcall sub_6FAABFB0(uint32_t a1)
{
	dword_6FBA7798 = a1;
}

//D2Client.0x6FAABFC0
uint32_t __cdecl sub_6FAABFC0()
{
	return dword_6FBA7778;
}

//D2Client.0x6FAABFD0
int32_t __fastcall sub_6FAABFD0()
{
	return dword_6FBA7780;
}

//D2Client.0x6FAABFE0
uint32_t __cdecl sub_6FAABFE0()
{
	return dword_6FBA7794;
}

//D2Client.0x6FAABFF0
int __cdecl sub_6FAABFF0()
{
	return gnGameType;
}

//D2Client.0x6FAAC000
void __fastcall sub_6FAAC000(int a1)
{
	DWORD DVar1;

	DVar1 = GetTickCount();
	if (dword_6FBA778C < DVar1 + a1)
	{
		dword_6FBA778C = DVar1 + a1;
	}
}

//D2Client.0x6FAAC020
int __cdecl sub_6FAAC020()
{
	return dword_6FBA794C;
}

//D2Client.0x6FAAC030
void __fastcall sub_6FAAC030(uint8_t a1)
{
	byte_6FBA795C = a1;
}

//D2Client.0x6FAAC040
void __fastcall sub_6FAAC040(uint32_t a1)
{
	dword_6FBA77C4 = a1 & 0xff;
}

//D2Client.0x6FAAC050
void __fastcall sub_6FAAC050(uint32_t a1)
{
	dword_6FBA77C8 = a1;
}

//D2Client.0x6FAAC060
uint32_t __cdecl sub_6FAAC060()
{
	uint32_t uVar1;

	if ((gnGameType < 2) || (uVar1 = dword_6FBA77C8, 3 < gnGameType))
	{
		uVar1 = 1;
	}
	return uVar1;
}

//D2Client.0x6FAAC080
uint32_t __cdecl sub_6FAAC080()
{
	return dword_6FBA77C4;
}

//D2Client.0x6FAAC090
uint8_t __cdecl sub_6FAAC090()
{
	return byte_6FBA795C;
}

//D2Client.0x6FAAC0A0
int __cdecl sub_6FAAC0A0()
{
	int iVar1;
	HWND__* pHVar2;
	uint32_t uVar3;

	iVar1 = GetSystemMetrics(0x4b);
	if (iVar1 == 0)
		goto LAB_6faac0f4;
	if (dword_6FBA7998 == 0)
		goto LAB_6faac160;
	if (dword_6FBA78C0 == 1)
	{
		if (dword_6FBA78B8 != 0)
			goto LAB_6faac0e1;
	}
	else if ((dword_6FBA78C0 == 2) && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))
	{
	LAB_6faac0e1:
		uVar3 = 1;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75890), uVar3);
	}
LAB_6faac0f4:
	if (dword_6FBA7998 != 0)
	{
		if ((dword_6FBA78C0 == 1) || ((dword_6FBA78C0 == 2 && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))))
		{
			uVar3 = 2;
			pHVar2 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7589C), uVar3);
		}
		if ((((dword_6FBA7998 != 0) && (dword_6FBA78C0 != 1)) && (dword_6FBA78C0 == 2)) &&
		    ((dword_6FBA78B4 != 4 && (dword_6FBA78B4 == 5))))
		{
			uVar3 = 2;
			pHVar2 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758B4), uVar3);
		}
	}
LAB_6faac160:
	iVar1 = GetSystemMetrics(0x4b);
	if ((iVar1 != 0) && (iVar1 = dword_6FBA7998, dword_6FBA7998 != 0))
	{
		if (dword_6FBA78C0 == 1)
		{
			iVar1 = dword_6FBA78B8;
			if ((dword_6FBA78B8 == 0) && (iVar1 = dword_6FB7581C, dword_6FB7581C != 0))
			{
				uVar3 = 1;
				pHVar2 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758CC), uVar3);
			}
		}
		else
		{
			iVar1 = dword_6FBA78C0 + -2;
			if (iVar1 == 0)
			{
				return dword_6FBA78B4;
			}
		}
	}
	return iVar1;
}

//D2Client.0x6FAAC1B0
HWND __cdecl sub_6FAAC1B0()
{
	int iVar1;
	HWND__* pHVar2;
	HWND hWnd;
	UINT Msg;
	uint32_t uVar3;

	iVar1 = GetSystemMetrics(0x4b);
	if (iVar1 == 0)
		goto LAB_6faac204;
	if (dword_6FBA7998 == 0)
		goto LAB_6faac270;
	if (dword_6FBA78C0 == 1)
	{
		if (dword_6FBA78B8 != 0)
			goto LAB_6faac1f1;
	}
	else if ((dword_6FBA78C0 == 2) && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))
	{
	LAB_6faac1f1:
		uVar3 = 1;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB75890), uVar3);
	}
LAB_6faac204:
	if (dword_6FBA7998 != 0)
	{
		if ((dword_6FBA78C0 == 1) || ((dword_6FBA78C0 == 2 && ((dword_6FBA78B4 == 4 || (dword_6FBA78B4 == 5))))))
		{
			uVar3 = 2;
			pHVar2 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7589C), uVar3);
		}
		if ((((dword_6FBA7998 != 0) && (dword_6FBA78C0 != 1)) && (dword_6FBA78C0 == 2)) &&
		    ((dword_6FBA78B4 != 4 && (dword_6FBA78B4 == 5))))
		{
			uVar3 = 2;
			pHVar2 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758B4), uVar3);
		}
	}
LAB_6faac270:
	hWnd = (HWND)GetSystemMetrics(0x4b);
	if ((hWnd != (HWND)0x0) && (hWnd = (HWND)dword_6FBA7998, dword_6FBA7998 != 0))
	{
		if (dword_6FBA78C0 == 1)
		{
			hWnd = (HWND)dword_6FBA78B8;
			if (dword_6FBA78B8 == 0)
			{
				Msg = RegisterWindowMessageA("MSH_WHEELSUPPORT_MSG");
				hWnd = FindWindowA("MouseZ", "Magellan MSWHEEL");
				if (((hWnd != (HWND)0x0) && (Msg != 0)) &&
				    (hWnd = (HWND)SendMessageA(hWnd, Msg, 0, 0), hWnd != (HWND)0x0))
				{
					uVar3 = 1;
					byte_6FB758D0 = Msg;
					pHVar2 = WINDOW_GetWindow();
					WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB758CC), uVar3);
				}
			}
		}
		else
		{
			hWnd = (HWND)(dword_6FBA78C0 + -2);
			if (hWnd == (HWND)0x0)
			{
				return (HWND)dword_6FBA78B4;
			}
		}
	}
	return hWnd;
}

//D2Client.0x6FAAC2F0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAAC2F0()
{
	uint32_t extraout_ECX;

	CLIENT_SetExitToMenu(0);
	dword_6FBA79D4 = 1;
	sub_6FAAD420((int32_t)extraout_ECX);
	dword_6FBA7970 = 1;
}

//D2Client.0x6FAAC320
// TODO: decompilation needs review (extraout)
uint32_t* __fastcall sub_6FAAC320(uint32_t* a1)
{
	uint32_t* puVar1;
	uint32_t* puVar2;
	int extraout_EDX;
	uint32_t extraout_EDX_00;
	int extraout_EDX_01;
	int iVar3;
	int extraout_EDX_02;
	int extraout_EDX_03;
	int iVar4;
	uint32_t uVar5;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	local_4 = 0xffffffff;
	sub_6FAACF90(a1 + 1);
	local_4 = 0;
	sub_6FAAD060(a1 + 5);
	local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), 1);
	*a1 = (uint32_t)(&gpuint8_t_6FB6E23C);
	a1[4] = 0;
	sub_6FAACFB0(a1 + 1, extraout_EDX, 0xc);
	a1[9] = 3;
	sub_6FAAD090(a1 + 5, extraout_EDX_00, 4);
	uVar5 = 0;
	iVar4 = 0;
	iVar3 = extraout_EDX_01;
	do
	{
		sub_6FAACFB0((void*)(a1[7] + iVar4), iVar3, 4);
		uVar5 = uVar5 + 1;
		iVar4 = iVar4 + 0xc;
		iVar3 = extraout_EDX_02;
	} while (uVar5 <= (uint32_t)a1[9]);
	puVar1 = a1 + 10;
	local_4 = 2;
	sub_6FAAD070(puVar1);
	(*(uint8_t*)((uint8_t*)&local_4 + 0)) = 3;
	*puVar1 = 0xdddddddd;
	sub_6FAAD200((int)puVar1);
	puVar2 = a1 + 0xe;
	(*(uint8_t*)((uint8_t*)&local_4 + 0)) = 4;
	sub_6FAAD070(puVar2);
	(*(uint8_t*)((uint8_t*)&local_4 + 0)) = 5;
	*puVar2 = 0x10;
	sub_6FAAD200((int)puVar2);
	local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), 6);
	*a1 = (uint32_t)(&gpuint8_t_6FB6E24C);
	a1[0xd] = 0x10;
	sub_6FAACFB0(puVar1, extraout_EDX_03, 4);
	*a1 = (uint32_t)(&gpuint8_t_6FB6E26C);
	a1[0x12] = ~(uint32_t)a1 & 0xfffffff;
	a1[0x13] = 0;
	InitializeCriticalSection((LPCRITICAL_SECTION)(a1 + 0x14));
	*a1 = (uint32_t)(&gpuint8_t_6FB6E25C);
	return a1;
}

//D2Client.0x6FAAC450
void __cdecl sub_6FAAC450(int a1)
{
	sub_6FAACA80(a1);
	SMemFree((void*)a1, str_6FB75B28, -2, 0);
}

//D2Client.0x6FAAC470
void __fastcall sub_6FAAC470(uint32_t* a1)
{
	int iVar1;
	void* pvVar2;
	uint32_t uVar3;
	int iVar4;

	a1[4] = 0;
	while (0 < (int)a1[3])
	{
		sub_6FAAD010((int*)(a1[1] + a1[3]));
	}
	uVar3 = 0;
	if (a1[6] != 0)
	{
		iVar4 = 0;
		do
		{
			while (iVar1 = *(int*)(iVar4 + a1[7] + 8), 0 < iVar1)
			{
				(**(code**)*a1)(iVar1);
			}
			uVar3 = uVar3 + 1;
			iVar4 = iVar4 + 0xc;
		} while (uVar3 < (uint32_t)a1[6]);
	}
	while (pvVar2 = (void*)a1[0x10], 0 < (int)pvVar2)
	{
		sub_6FAACEE0((int)pvVar2);
		SMemFree(pvVar2, str_6FB75B40, -2, 0);
	}
	while (pvVar2 = (void*)a1[0xc], 0 < (int)pvVar2)
	{
		sub_6FAACA80((int)pvVar2);
		SMemFree(pvVar2, str_6FB75B28, -2, 0);
	}
}

//D2Client.0x6FAAC500
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAAC500(void* a1, int a2, uint32_t a3)
{
	uint32_t in_EDX;

	sub_6FAACAF0(a1, in_EDX, 1, a2, a3);
}

//D2Client.0x6FAAC520
// TODO: decompilation needs review (extraout, in_reg)
void __fastcall sub_6FAAC520(uint32_t* a1)
{
	int iVar1;
	uint32_t uVar2;
	int* piVar3;
	int* piVar4;
	int in_EDX;
	int extraout_EDX;
	int* piVar5;
	int extraout_EDX_00;
	int extraout_EDX_01;
	uint32_t uVar6;
	int iVar7;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6E23C);
	local_4 = 1;
	a1[4] = 0;
	while (true)
	{
		if ((int)a1[3] < 1)
			break;
		piVar3 = (int*)sub_6FAACE40(a1 + 1, in_EDX, a1[3]);
		sub_6FAAD010(piVar3);
		in_EDX = extraout_EDX;
	}
	uVar6 = 0;
	if (a1[6] != 0)
	{
		iVar7 = 0;
		do
		{
			while (true)
			{
				iVar1 = *(int*)(a1[7] + 8 + iVar7);
				if (iVar1 < 1)
					break;
				piVar3 = (int*)(*(int*)(a1[7] + iVar7) + iVar1);
				iVar1 = *piVar3;
				if (iVar1 != 0)
				{
					uVar2 = piVar3[1];
					if ((int)uVar2 < 0)
					{
						piVar5 = (int*)~uVar2;
					}
					else
					{
						piVar5 = (int*)((int)piVar3 + (uVar2 - *(int*)(iVar1 + 4)));
					}
					*piVar5 = iVar1;
					in_EDX = *piVar3;
					*(int*)(in_EDX + 4) = piVar3[1];
					*piVar3 = 0;
					piVar3[1] = 0;
				}
			}
			uVar6 = uVar6 + 1;
			iVar7 = iVar7 + 0xc;
		} while (uVar6 < (uint32_t)a1[6]);
	}
	uVar6 = 0;
	local_4 = local_4 & 0xffffff00;
	if (a1[6] != 0)
	{
		iVar7 = 0;
		do
		{
			sub_6FAACC00((int*)(a1[7] + iVar7));
			uVar6 = uVar6 + 1;
			iVar7 = iVar7 + 0xc;
			in_EDX = extraout_EDX_00;
		} while (uVar6 < (uint32_t)a1[6]);
	}
	if ((void*)a1[7] != nullptr)
	{
		SMemFree((void*)a1[7], str_6FB75EA0, -2, 0);
		in_EDX = extraout_EDX_01;
	}
	local_4 = 2;
	piVar3 = (int*)(a1 + 2);
	while (0 < (int)a1[3])
	{
		piVar5 = (int*)(a1[1] + a1[3]);
		if (*piVar5 != 0)
		{
			piVar4 = (int*)sub_6FAACE10(piVar5, in_EDX, 0xffffffff);
			in_EDX = *piVar5;
			*piVar4 = in_EDX;
			*(int*)(*piVar5 + 4) = piVar5[1];
			*piVar5 = 0;
			piVar5[1] = 0;
		}
	}
	iVar7 = *piVar3;
	if (iVar7 != 0)
	{
		uVar6 = a1[3];
		if ((int)uVar6 < 0)
		{
			piVar5 = (int*)~uVar6;
		}
		else
		{
			piVar5 = (int*)((int)piVar3 + (uVar6 - *(int*)(iVar7 + 4)));
		}
		*piVar5 = iVar7;
		*(uint32_t*)(*piVar3 + 4) = a1[3];
		*piVar3 = 0;
		a1[3] = 0;
	}
}

//D2Client.0x6FAAC6A0
// TODO: decompilation needs review (extraout, in_reg)
void __fastcall sub_6FAAC6A0(int a1)
{
	int iVar1;
	int* piVar2;
	int in_EDX;
	int extraout_EDX;
	int extraout_EDX_00;
	int iVar3;
	uint32_t uVar4;
	uint32_t local_4;

	*(uint32_t*)(a1 + 0x10) = 0;
	while (0 < *(int*)(a1 + 0xc))
	{
		sub_6FAAD010((int*)(*(int*)(a1 + 4) + *(int*)(a1 + 0xc)));
		in_EDX = extraout_EDX;
	}
	local_4 = 0;
	if (*(int*)(a1 + 0x18) != 0)
	{
		iVar3 = 0;
		do
		{
			while (true)
			{
				piVar2 = (int*)(*(int*)(a1 + 0x1c) + iVar3);
				iVar1 = piVar2[2];
				if (iVar1 < 1)
					break;
				piVar2 = (int*)(*piVar2 + iVar1);
				iVar1 = *piVar2;
				if (iVar1 != 0)
				{
					uVar4 = piVar2[1];
					if ((int)uVar4 < 0)
					{
						*(int*)~uVar4 = iVar1;
						in_EDX = piVar2[1];
						*(int*)(*piVar2 + 4) = in_EDX;
						*piVar2 = 0;
						piVar2[1] = 0;
					}
					else
					{
						*(int*)((int)piVar2 + (uVar4 - *(int*)(iVar1 + 4))) = iVar1;
						in_EDX = piVar2[1];
						*(int*)(*piVar2 + 4) = in_EDX;
						*piVar2 = 0;
						piVar2[1] = 0;
					}
				}
			}
			local_4 = local_4 + 1;
			iVar3 = iVar3 + 0xc;
		} while (local_4 < *(uint32_t*)(a1 + 0x18));
	}
	*(uint32_t*)(a1 + 0x10) = 0;
	*(uint32_t*)(a1 + 0x24) = 0;
	uVar4 = 0;
	if (*(int*)(a1 + 0x18) != 0)
	{
		iVar3 = 0;
		do
		{
			sub_6FAACEB0((void*)(*(int*)(a1 + 0x1c) + iVar3), in_EDX, 0);
			uVar4 = uVar4 + 1;
			iVar3 = iVar3 + 0xc;
			in_EDX = extraout_EDX_00;
		} while (uVar4 < *(uint32_t*)(a1 + 0x18));
	}
	if (*(void**)(a1 + 0x1c) != nullptr)
	{
		SMemFree(*(void**)(a1 + 0x1c), str_6FB75EA0, -2, 0);
	}
	*(uint32_t*)(a1 + 0x14) = 0;
	*(uint32_t*)(a1 + 0x18) = 0;
	*(uint32_t*)(a1 + 0x1c) = 0;
}

//D2Client.0x6FAAC780
void* __fastcall sub_6FAAC780(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAA8970((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAAC7B0
void* __fastcall sub_6FAAC7B0(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAACA80((int)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAAC7E0
void* __fastcall sub_6FAAC7E0(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAAC810((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAAC810
// TODO: decompilation needs review (extraout, in_reg)
void __fastcall sub_6FAAC810(uint32_t* a1)
{
	void* pvVar1;
	int iVar2;
	int* piVar3;
	int* piVar4;
	int in_EDX;
	int extraout_EDX;
	int extraout_EDX_00;
	int extraout_EDX_01;
	int extraout_EDX_02;
	int extraout_EDX_03;
	int iVar5;
	int extraout_EDX_04;
	uint32_t uVar6;
	int iVar7;
	void* pvStack_c;
	code* pcStack_8;
	int local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6E24C);
	local_4 = 2;
	while (pvVar1 = (void*)a1[0x10], 0 < (int)pvVar1)
	{
		sub_6FAACEE0((int)pvVar1);
		SMemFree(pvVar1, str_6FB75B40, -2, 0);
		in_EDX = extraout_EDX;
	}
	while (pvVar1 = (void*)a1[0xc], 0 < (int)pvVar1)
	{
		sub_6FAACA80((int)pvVar1);
		SMemFree(pvVar1, str_6FB75B28, -2, 0);
		in_EDX = extraout_EDX_00;
	}
	(*(uint8_t*)((uint8_t*)&local_4 + 0)) = 3;
	piVar4 = (int*)(a1 + 0xf);
	while (0 < (int)a1[0x10])
	{
		sub_6FAAD010((int*)(a1[0xe] + a1[0x10]));
		in_EDX = extraout_EDX_01;
	}
	(*(uint8_t*)((uint8_t*)&local_4 + 0)) = 1;
	if (*piVar4 != 0)
	{
		piVar3 = (int*)sub_6FAACE10(piVar4, in_EDX, 0xffffffff);
		*piVar3 = *piVar4;
		in_EDX = *piVar4;
		*(uint32_t*)(in_EDX + 4) = a1[0x10];
		*piVar4 = 0;
		a1[0x10] = 0;
	}
	(*(uint8_t*)((uint8_t*)&local_4 + 0)) = 4;
	piVar4 = (int*)(a1 + 0xb);
	while (0 < (int)a1[0xc])
	{
		sub_6FAAD010((int*)(a1[10] + a1[0xc]));
		in_EDX = extraout_EDX_02;
	}
	local_4 = (uint32_t)(*(uint8_t*)((uint8_t*)&local_4 + 1)) << 8;
	if (*piVar4 != 0)
	{
		piVar3 = (int*)sub_6FAACE10(piVar4, in_EDX, 0xffffffff);
		*piVar3 = *piVar4;
		*(uint32_t*)(*piVar4 + 4) = a1[0xc];
		*piVar4 = 0;
		a1[0xc] = 0;
	}
	*a1 = (uint32_t)(&gpuint8_t_6FB6E23C);
	a1[4] = 0;
	local_4 = 6;
	sub_6FAACE60((int*)(a1 + 1));
	uVar6 = 0;
	if (a1[6] != 0)
	{
		iVar7 = 0;
		iVar5 = extraout_EDX_03;
		do
		{
			while (true)
			{
				iVar2 = *(int*)(a1[7] + iVar7 + 8);
				if (iVar2 < 1)
					break;
				piVar4 = (int*)sub_6FAACE40((void*)(a1[7] + iVar7), iVar5, iVar2);
				sub_6FAAD010(piVar4);
				iVar5 = extraout_EDX_04;
			}
			uVar6 = uVar6 + 1;
			iVar7 = iVar7 + 0xc;
		} while (uVar6 < (uint32_t)a1[6]);
	}
	local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), 5);
	sub_6FAACBC0((int)(a1 + 5));
	local_4 = 7;
	sub_6FAACE60((int*)(a1 + 1));
	local_4 = 0xffffffff;
	sub_6FAAD010((int*)(a1 + 2));
}

//D2Client.0x6FAAC9A0
void* __fastcall sub_6FAAC9A0(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAAC520((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAAC9D0
void __fastcall sub_6FAAC9D0(int a1)
{
	void** ppvVar1;
	int* piVar2;
	int iVar3;
	int* piVar4;
	uint32_t local_14;
	void* local_c;
	code* pcStack_8;
	uint32_t local_4;

	local_4 = 0xffffffff;
	iVar3 = 0;
	local_14 = 0;
	ppvVar1 = &local_c;
	if (*(int*)(a1 + 4) != 0)
	{
		do
		{
			piVar4 = (int*)(*(int*)(a1 + 8) + iVar3);
			local_4 = 0;
			while (0 < piVar4[2])
			{
				piVar2 = (int*)sub_6FAAD050(piVar4[2], *piVar4);
				sub_6FAAD010(piVar2);
			}
			local_4 = 0xffffffff;
			sub_6FAAD010(piVar4 + 1);
			local_14 = local_14 + 1;
			iVar3 = iVar3 + 0xc;
		} while (local_14 < *(uint32_t*)(a1 + 4));
	}
	if (*(void**)(a1 + 8) != nullptr)
	{
		SMemFree(*(void**)(a1 + 8), str_6FB75EA0, -2, 0);
	}
}

//D2Client.0x6FAACA80
void __fastcall sub_6FAACA80(int a1)
{
	int* piVar1;
	int iVar2;
	uint32_t uVar3;
	int* piVar4;

	piVar1 = (int*)(a1 + 0xc);
	iVar2 = *piVar1;
	if (iVar2 != 0)
	{
		uVar3 = *(uint32_t*)(a1 + 0x10);
		if ((int)uVar3 < 0)
		{
			piVar4 = (int*)~uVar3;
		}
		else
		{
			piVar4 = (int*)((int)piVar1 + (uVar3 - *(int*)(iVar2 + 4)));
		}
		*piVar4 = iVar2;
		*(uint32_t*)(*piVar1 + 4) = *(uint32_t*)(a1 + 0x10);
		*piVar1 = 0;
		*(uint32_t*)(a1 + 0x10) = 0;
	}
	iVar2 = *(int*)(a1 + 4);
	piVar1 = (int*)(a1 + 4);
	if (iVar2 != 0)
	{
		uVar3 = *(uint32_t*)(a1 + 8);
		if ((int)uVar3 < 0)
		{
			piVar4 = (int*)~uVar3;
		}
		else
		{
			piVar4 = (int*)((int)piVar1 + (uVar3 - *(int*)(iVar2 + 4)));
		}
		*piVar4 = iVar2;
		*(uint32_t*)(*piVar1 + 4) = *(uint32_t*)(a1 + 8);
		*piVar1 = 0;
		*(uint32_t*)(a1 + 8) = 0;
	}
}

//D2Client.0x6FAACAF0
void __fastcall sub_6FAACAF0(void* a1, uint32_t a2, int a3, uint32_t a4, uint32_t a5)
{
	uint32_t uVar1;
	void* pvVar2;
	int* piVar3;
	int* piVar4;
	int iVar5;

	pvVar2 = SMemAlloc(a4 + 0x1de8, str_6FB75B28, -2, a5 | 8);
	if (pvVar2 == nullptr)
	{
		pvVar2 = nullptr;
	}
	else
	{
		*(uint32_t*)((int)pvVar2 + 4) = 0;
		*(uint32_t*)((int)pvVar2 + 8) = 0;
		*(uint32_t*)((int)pvVar2 + 0xc) = 0;
		*(uint32_t*)((int)pvVar2 + 0x10) = 0;
	}
	if (a3 != 0)
	{
		if (pvVar2 == nullptr)
		{
			piVar3 = (int*)((int)a1 + 4);
		}
		else
		{
			piVar3 = (int*)(*(uint32_t*)(a1) + (int)pvVar2);
		}
		iVar5 = *piVar3;
		if (iVar5 != 0)
		{
			uVar1 = piVar3[1];
			if ((int)uVar1 < 0)
			{
				piVar4 = (int*)~uVar1;
			}
			else
			{
				piVar4 = (int*)((int)piVar3 + (uVar1 - *(int*)(iVar5 + 4)));
			}
			*piVar4 = iVar5;
			*(int*)(*piVar3 + 4) = piVar3[1];
			*piVar3 = 0;
			piVar3[1] = 0;
		}
		piVar4 = (int*)((int)a1 + 4);
		if (a3 != 1)
		{
			iVar5 = *piVar4;
			*piVar3 = iVar5;
			piVar3[1] = *(int*)(iVar5 + 4);
			*(void**)(iVar5 + 4) = pvVar2;
			*piVar4 = (int)piVar3;
			return;
		}
		*piVar3 = (int)piVar4;
		piVar3[1] = *(int*)((int)a1 + 8);
		uVar1 = *(uint32_t*)((int)a1 + 8);
		iVar5 = *(uint32_t*)(a1);
		if ((int)uVar1 < 0)
		{
			*(int**)~uVar1 = piVar3;
			*(void**)((int)a1 + 8) = pvVar2;
			return;
		}
		if (iVar5 < 0)
		{
			iVar5 = (int)piVar4 - *(int*)(*piVar4 + 4);
		}
		*(int**)(uVar1 + iVar5) = piVar3;
		*(void**)((int)a1 + 8) = pvVar2;
	}
}

//D2Client.0x6FAACBC0
void __fastcall sub_6FAACBC0(int a1)
{
	int iVar1;
	uint32_t uVar2;

	uVar2 = 0;
	if (*(int*)(a1 + 4) != 0)
	{
		iVar1 = 0;
		do
		{
			sub_6FAACC00((int*)(*(int*)(a1 + 8) + iVar1));
			uVar2 = uVar2 + 1;
			iVar1 = iVar1 + 0xc;
		} while (uVar2 < *(uint32_t*)(a1 + 4));
	}
	if (*(void**)(a1 + 8) != nullptr)
	{
		SMemFree(*(void**)(a1 + 8), str_6FB75EA0, -2, 0);
	}
}

//D2Client.0x6FAACC00
void __fastcall sub_6FAACC00(int* a1)
{
	int* piVar1;
	int iVar2;
	uint32_t uVar3;
	int* piVar4;
	int* piVar5;

	piVar1 = a1 + 1;
	while (0 < a1[2])
	{
		piVar4 = (int*)(*a1 + a1[2]);
		iVar2 = *piVar4;
		if (iVar2 != 0)
		{
			uVar3 = piVar4[1];
			if ((int)uVar3 < 0)
			{
				piVar5 = (int*)~uVar3;
			}
			else
			{
				piVar5 = (int*)((int)piVar4 + (uVar3 - *(int*)(iVar2 + 4)));
			}
			*piVar5 = iVar2;
			*(int*)(*piVar4 + 4) = piVar4[1];
			*piVar4 = 0;
			piVar4[1] = 0;
		}
	}
	iVar2 = *piVar1;
	if (iVar2 != 0)
	{
		uVar3 = a1[2];
		if ((int)uVar3 < 0)
		{
			piVar4 = (int*)~uVar3;
		}
		else
		{
			piVar4 = (int*)((int)piVar1 + (uVar3 - *(int*)(iVar2 + 4)));
		}
		*piVar4 = iVar2;
		*(int*)(*piVar1 + 4) = a1[2];
		*piVar1 = 0;
		a1[2] = 0;
	}
}

//D2Client.0x6FAACC80
void* __fastcall sub_6FAACC80(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAACCB0((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAACCB0
// TODO: decompilation needs review (extraout, in_reg)
void __fastcall sub_6FAACCB0(uint32_t* a1)
{
	void* pvVar1;
	int iVar2;
	int* piVar3;
	int* piVar4;
	int in_EDX;
	int extraout_EDX;
	int extraout_EDX_00;
	int extraout_EDX_01;
	int extraout_EDX_02;
	int extraout_EDX_03;
	int iVar5;
	int extraout_EDX_04;
	uint32_t uVar6;
	int iVar7;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6E24C);
	local_4 = 2;
	while (true)
	{
		pvVar1 = (void*)a1[0x10];
		uVar6 = 0;
		if ((int)pvVar1 < 1)
			break;
		sub_6FAACEE0((int)pvVar1);
		SMemFree(pvVar1, str_6FB75B40, -2, 0);
		in_EDX = extraout_EDX;
	}
	while (pvVar1 = (void*)a1[0xc], 0 < (int)pvVar1)
	{
		sub_6FAAC7B0(pvVar1, in_EDX, 0);
		SMemFree(pvVar1, str_6FB75B28, -2, 0);
		in_EDX = extraout_EDX_00;
	}
	local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), 1);
	piVar4 = (int*)(a1 + 0xf);
	while (0 < (int)a1[0x10])
	{
		sub_6FAAD010((int*)(a1[0xe] + a1[0x10]));
		in_EDX = extraout_EDX_01;
	}
	if (*piVar4 != 0)
	{
		piVar3 = (int*)sub_6FAACE10(piVar4, in_EDX, 0xffffffff);
		*piVar3 = *piVar4;
		in_EDX = *piVar4;
		*(uint32_t*)(in_EDX + 4) = a1[0x10];
		*piVar4 = 0;
		a1[0x10] = 0;
	}
	local_4 = local_4 & 0xffffff00;
	piVar4 = (int*)(a1 + 0xb);
	while (0 < (int)a1[0xc])
	{
		sub_6FAAD010((int*)(a1[10] + a1[0xc]));
		in_EDX = extraout_EDX_02;
	}
	if (*piVar4 != 0)
	{
		piVar3 = (int*)sub_6FAACE10(piVar4, in_EDX, 0xffffffff);
		*piVar3 = *piVar4;
		*(uint32_t*)(*piVar4 + 4) = a1[0xc];
		*piVar4 = 0;
		a1[0xc] = 0;
	}
	*a1 = (uint32_t)(&gpuint8_t_6FB6E23C);
	local_4 = 4;
	a1[4] = 0;
	sub_6FAACE60((int*)(a1 + 1));
	if (a1[6] != 0)
	{
		iVar7 = 0;
		iVar5 = extraout_EDX_03;
		do
		{
			while (true)
			{
				iVar2 = *(int*)(a1[7] + iVar7 + 8);
				if (iVar2 < 1)
					break;
				piVar4 = (int*)sub_6FAACE40((void*)(a1[7] + iVar7), iVar5, iVar2);
				sub_6FAAD010(piVar4);
				iVar5 = extraout_EDX_04;
			}
			uVar6 = uVar6 + 1;
			iVar7 = iVar7 + 0xc;
		} while (uVar6 < (uint32_t)a1[6]);
	}
	sub_6FAACBC0((int)(a1 + 5));
	local_4 = 0xffffffff;
	sub_6FAACE60((int*)(a1 + 1));
	sub_6FAAD010((int*)(a1 + 2));
}

//D2Client.0x6FAACE10
uint32_t __fastcall sub_6FAACE10(void* a1, int a2, int a3)
{
	uint32_t uVar1;

	uVar1 = *(uint32_t*)((int)a1 + 4);
	if ((int)uVar1 < 0)
	{
		return ~uVar1;
	}
	if (a3 < 0)
	{
		a3 = (int)a1 - *(int*)(*(uint32_t*)(a1) + 4);
	}
	return uVar1 + a3;
}

//D2Client.0x6FAACE40
int __fastcall sub_6FAACE40(void* a1, int a2, int a3)
{
	if (a3 != 0)
	{
		return *(uint32_t*)(a1) + a3;
	}
	return (int)a1 + 4;
}

//D2Client.0x6FAACE60
void __fastcall sub_6FAACE60(int* a1)
{
	int iVar1;
	uint32_t uVar2;
	int* piVar3;
	int* piVar4;

	while (0 < a1[2])
	{
		piVar3 = (int*)(*a1 + a1[2]);
		iVar1 = *piVar3;
		if (iVar1 != 0)
		{
			uVar2 = piVar3[1];
			if ((int)uVar2 < 0)
			{
				piVar4 = (int*)~uVar2;
			}
			else
			{
				piVar4 = (int*)((int)piVar3 + (uVar2 - *(int*)(iVar1 + 4)));
			}
			*piVar4 = iVar1;
			*(int*)(*piVar3 + 4) = piVar3[1];
			*piVar3 = 0;
			piVar3[1] = 0;
		}
	}
}

//D2Client.0x6FAACEB0
void* __fastcall sub_6FAACEB0(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAACC00((int*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAACEE0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAACEE0(int a1)
{
	int iVar1;
	uint32_t uVar2;
	int* piVar3;
	int extraout_EDX;
	int iVar4;
	int iVar5;
	int* piVar6;
	uint32_t local_4;

	iVar1 = *(int*)(a1 + 0x10);
	piVar6 = (int*)(a1 + 0x10);
	iVar4 = 0;
	if (iVar1 != 0)
	{
		uVar2 = *(uint32_t*)(a1 + 0x14);
		if ((int)uVar2 < 0)
		{
			piVar3 = (int*)~uVar2;
		}
		else
		{
			piVar3 = (int*)((int)piVar6 + (uVar2 - *(int*)(iVar1 + 4)));
		}
		*piVar3 = iVar1;
		*(uint32_t*)(*piVar6 + 4) = *(uint32_t*)(a1 + 0x14);
		*piVar6 = 0;
		*(uint32_t*)(a1 + 0x14) = 0;
	}
	local_4 = 0;
	if (*(int*)(a1 + 4) != 0)
	{
		do
		{
			iVar5 = *(int*)(a1 + 8) + iVar4;
			sub_6FAAD010((int*)(iVar5 + 0xc));
			iVar1 = *(int*)(iVar5 + 4);
			piVar6 = (int*)(iVar5 + 4);
			if (iVar1 != 0)
			{
				piVar3 = (int*)sub_6FAACE10(piVar6, extraout_EDX, 0xffffffff);
				*piVar3 = iVar1;
				*(uint32_t*)(*piVar6 + 4) = *(uint32_t*)(iVar5 + 8);
				*piVar6 = 0;
				*(uint32_t*)(iVar5 + 8) = 0;
			}
			local_4 = local_4 + 1;
			iVar4 = iVar4 + 0x1de8;
		} while (local_4 < *(uint32_t*)(a1 + 4));
	}
	if (*(void**)(a1 + 8) != nullptr)
	{
		SMemFree(*(void**)(a1 + 8), str_6FB75B28, -2, 0);
	}
}

//D2Client.0x6FAACF90
void __fastcall sub_6FAACF90(uint32_t* a1)
{
	uint32_t* puVar1;

	puVar1 = a1 + 1;
	*puVar1 = 0;
	a1[2] = 0;
	*puVar1 = (uint32_t)(puVar1);
	*a1 = 0xdddddddd;
	a1[2] = ~(uint32_t)puVar1;
}

//D2Client.0x6FAACFB0
void __fastcall sub_6FAACFB0(void* a1, int a2, int a3)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t uVar3;
	int* piVar4;
	int* piVar5;

	if (a3 != *(uint32_t*)(a1))
	{
		uVar1 = (int)a1 + 4;
		while (0 < *(int*)((int)a1 + 8))
		{
			piVar4 = (int*)(*(uint32_t*)(a1) + *(int*)((int)a1 + 8));
			iVar2 = *piVar4;
			if (iVar2 != 0)
			{
				uVar3 = piVar4[1];
				if ((int)uVar3 < 0)
				{
					piVar5 = (int*)~uVar3;
				}
				else
				{
					piVar5 = (int*)((int)piVar4 + (uVar3 - *(int*)(iVar2 + 4)));
				}
				*piVar5 = iVar2;
				*(int*)(*piVar4 + 4) = piVar4[1];
				*piVar4 = 0;
				piVar4[1] = 0;
			}
		}
		*(uint32_t*)uVar1 = uVar1;
		*(uint32_t*)((int)a1 + 8) = ~uVar1;
		*(int*)a1 = a3;
	}
}

//D2Client.0x6FAAD010
void __fastcall sub_6FAAD010(int* a1)
{
	int iVar1;
	uint32_t uVar2;
	int* piVar3;

	iVar1 = *a1;
	if (iVar1 != 0)
	{
		uVar2 = a1[1];
		if ((int)uVar2 < 0)
		{
			piVar3 = (int*)~uVar2;
		}
		else
		{
			piVar3 = (int*)((int)a1 + (uVar2 - *(int*)(iVar1 + 4)));
		}
		*piVar3 = iVar1;
		*(int*)(*a1 + 4) = a1[1];
		*a1 = 0;
		a1[1] = 0;
	}
}

//D2Client.0x6FAAD050
int __fastcall sub_6FAAD050(int a1, int a2)
{
	return a1 + a2;
}

//D2Client.0x6FAAD060
void __fastcall sub_6FAAD060(uint32_t* a1)
{
	*a1 = 0;
	a1[1] = 0;
	a1[2] = 0;
	a1[3] = 0;
}

//D2Client.0x6FAAD070
void __fastcall sub_6FAAD070(uint32_t* a1)
{
	uint32_t* puVar1;

	puVar1 = a1 + 1;
	*puVar1 = 0;
	a1[2] = 0;
	*puVar1 = (uint32_t)(puVar1);
	*a1 = 0;
	a1[2] = ~(uint32_t)puVar1;
}

//D2Client.0x6FAAD090
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAAD090(void* a1, uint32_t a2, uint32_t a3)
{
	uint32_t* location;
	void* pvVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t* puVar5;
	int iVar6;
	int iVar7;

	if (*(uint32_t*)((int)a1 + 4) < a3)
	{
		if (*(uint32_t*)(a1) < a3)
		{
			uVar2 = *(uint32_t*)((int)a1 + 0xc);
			if (uVar2 == 0)
			{
				if (a3 < 0x15)
				{
					uVar4 = a3 - 1 & a3;
					uVar2 = a3;
					while (uVar3 = uVar4, uVar3 != 0)
					{
						uVar2 = uVar3;
						uVar4 = uVar3 - 1 & uVar3;
					}
					if (uVar2 == 0)
					{
						uVar2 = 1;
					}
				}
				else
				{
					*(uint32_t*)((int)a1 + 0xc) = 0x15;
					uVar2 = 0x15;
				}
			}
			uVar4 = a3 % uVar2;
			uVar3 = a3;
			if (uVar4 != 0)
			{
				uVar3 = (uVar2 - uVar4) + a3;
			}
			location = *(uint32_t**)((int)a1 + 8);
			if (uVar3 < *(uint32_t*)((int)a1 + 4))
			{
				puVar5 = location + uVar3 * 3;
				uVar2 = uVar3;
				do
				{
					sub_6FAACEB0(puVar5, uVar4, 0);
					uVar2 = uVar2 + 1;
					puVar5 = puVar5 + 3;
					uVar4 = extraout_EDX;
				} while (uVar2 < *(uint32_t*)((int)a1 + 4));
			}
			*(uint32_t*)a1 = uVar3;
			pvVar1 = SMemReAlloc(location, uVar3 * 0xc, str_6FB75EA0, -2, 0x10);
			*(void**)((int)a1 + 8) = pvVar1;
			if (pvVar1 == nullptr)
			{
				pvVar1 = SMemAlloc(uVar3 * 0xc, str_6FB75EA0, -2, 0);
				*(void**)((int)a1 + 8) = pvVar1;
				if (location != nullptr)
				{
					uVar2 = *(uint32_t*)((int)a1 + 4);
					if (uVar3 < *(uint32_t*)((int)a1 + 4))
					{
						uVar2 = uVar3;
					}
					if (uVar2 != 0)
					{
						iVar6 = 0;
						puVar5 = location;
						do
						{
							sub_6FAAD240((uint32_t*)(*(int*)((int)a1 + 8) + iVar6), puVar5);
							sub_6FAACEB0(puVar5, extraout_EDX_00, 0);
							iVar6 = iVar6 + 0xc;
							puVar5 = puVar5 + 3;
							uVar2 = uVar2 - 1;
						} while (uVar2 != 0);
					}
					SMemFree(location, str_6FB75EA0, -2, 0);
				}
			}
		}
		uVar2 = *(uint32_t*)((int)a1 + 4);
		if (uVar2 < a3)
		{
			iVar7 = uVar2 * 0xc;
			iVar6 = a3 - uVar2;
			do
			{
				sub_6FAAD210((uint32_t*)(*(int*)((int)a1 + 8) + iVar7));
				iVar7 = iVar7 + 0xc;
				iVar6 = iVar6 + -1;
			} while (iVar6 != 0);
			*(uint32_t*)((int)a1 + 4) = a3;
			return;
		}
	}
	else if (a3 < *(uint32_t*)((int)a1 + 4))
	{
		iVar6 = a3 * 0xc;
		uVar2 = a3;
		do
		{
			sub_6FAACC00((int*)(*(int*)((int)a1 + 8) + iVar6));
			uVar2 = uVar2 + 1;
			iVar6 = iVar6 + 0xc;
		} while (uVar2 < *(uint32_t*)((int)a1 + 4));
	}
	*(uint32_t*)((int)a1 + 4) = a3;
}

//D2Client.0x6FAAD200
void __fastcall sub_6FAAD200(int a1)
{
	uint32_t uVar1;

	uVar1 = a1 + 4;
	*(uint32_t*)uVar1 = uVar1;
	*(uint32_t*)(a1 + 8) = ~uVar1;
}

//D2Client.0x6FAAD210
void __fastcall sub_6FAAD210(uint32_t* a1)
{
	uint32_t* puVar1;

	if (a1 != nullptr)
	{
		puVar1 = a1 + 1;
		*puVar1 = 0;
		a1[2] = 0;
		*puVar1 = (uint32_t)(puVar1);
		*a1 = 0xdddddddd;
		a1[2] = ~(uint32_t)puVar1;
	}
}

//D2Client.0x6FAAD240
void __fastcall sub_6FAAD240(uint32_t* a1, uint32_t* a2)
{
	uint32_t* puVar1;
	uint32_t uVar2;

	if (a1 != nullptr)
	{
		puVar1 = a1 + 1;
		*puVar1 = 0;
		a1[2] = 0;
		uVar2 = *a2;
		*puVar1 = (uint32_t)(puVar1);
		*a1 = uVar2;
		a1[2] = ~(uint32_t)puVar1;
	}
}

//D2Client.0x6FAAD260
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAAD260()
{
	uint32_t uVar1;
	uint32_t uVar2;
	D2C_Language DVar3;
	char* in_ECX;
	uint8_t local_30;
	char local_2f[16];
	uint8_t uStack_1f;
	uint8_t bStack_1e;
	uint8_t uStack_1d;
	uint8_t uStack_1c;
	char acStack_1b[16];
	uint16_t uStack_b;
	uint32_t uStack_9;
	uint8_t uStack_5;
	uint8_t uStack_4;
	uint8_t uStack_3;

	local_30 = 0x66;
	SStrCopy(local_2f, in_ECX, 0x7fffffff);
	if (gnGameType == 0)
	{
		uStack_1f = 3;
	}
	else if (gnGameType == 6)
	{
		uStack_1f = 1;
	}
	else if (gnGameType == 8)
	{
		uStack_1f = 2;
	}
	else
	{
		uStack_1f = 0;
	}
	uVar1 = sub_6FAA6A00();
	if (uVar1 == 0)
	{
		bStack_1e = byte_6FBA7894;
	}
	else
	{
		uVar2 = sub_6FAA69F0();
		bStack_1e = (uint8_t)uVar2;
	}
	DVar3 = STRTABLE_GetLanguage();
	uStack_3 = (uint8_t)DVar3;
	if (*(int*)(gpConfig + 0x204) == 0)
	{
		*(uint32_t*)(gpConfig + 0x204) = 4;
		*(uint32_t*)(gpConfig + 0x204) = *(uint32_t*)(gpConfig + 0x204) | 0x100000;
	}
	uStack_b = *(uint16_t*)(gpConfig + 0x202);
	uStack_9 = *(uint32_t*)(gpConfig + 0x204);
	uStack_1d = *(uint8_t*)(gpConfig + 0x208);
	uStack_5 = *(uint8_t*)(gpConfig + 0x209);
	uStack_4 = *(uint8_t*)(gpConfig + 0x20a);
	uStack_1c = *(uint8_t*)(gpConfig + 0x20b);
	SStrCopy(acStack_1b, gszPlayerName, 0x7fffffff);
	CLIENT_Send(0, &local_30, 0x2e);
	dword_6FBC1AF4 = dword_6FBC1AF4 + 0x2e;
	dword_6FBC1AFC = dword_6FBC1AFC + 1;
}

//D2Client.0x6FAAD380
void __fastcall sub_6FAAD380(uint32_t a1)
{
	uint8_t local_1;

	CLIENT_Send(0, &local_1, 1);
	dword_6FBC1AF4 = dword_6FBC1AF4 + 1;
	dword_6FBC1AFC = dword_6FBC1AFC + 1;
}

//D2Client.0x6FAAD3B0
void __cdecl sub_6FAAD3B0()
{
	DWORD DVar1;
	uint8_t local_c;
	DWORD local_b;
	uint32_t local_7;

	DVar1 = GetTickCount();
	if (4999 < DVar1 - dword_6FBA79F0)
	{
		local_c = 0x6c;
		dword_6FBA79F0 = DVar1;
		local_b = GetTickCount();
		local_7 = sub_6FAA9AE0();
		local_7 = local_7 >> 1;
		CLIENT_Send(0, &local_c, 9);
		dword_6FBC1AF4 = dword_6FBC1AF4 + 9;
		dword_6FBC1AFC = dword_6FBC1AFC + 1;
	}
}

//D2Client.0x6FAAD420
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAAD420(uint32_t a1)
{
	int iVar1;
	uint8_t local_1;

	CLIENT_Send(0, &local_1, 1);
	dword_6FBC1AF4 = dword_6FBC1AF4 + 1;
	dword_6FBC1AFC = dword_6FBC1AFC + 1;
	if ((gnGameType != 0) && (gnGameType != 1))
	{
		if (gnGameType == 6)
			goto LAB_6faad496;
		if (((gnGameType != 7) && (gnGameType != 8)) && (gnGameType != 9))
		{
			dword_6FBA7970 = 1;
			dword_6FBA796C = 0;
			dword_6FBA7968 = 0;
		}
	}
	if ((gnGameType != 6) && (gnGameType != 7))
	{
		return;
	}
LAB_6faad496:
	iVar1 = (int)(CLIENT_GetComInterface());
	if (iVar1 == 0)
	{
		return;
	}
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(iVar1 + 0x90))();
}

//D2Client.0x6FAAD4B0
void __fastcall sub_6FAAD4B0(uint32_t a1, uint32_t a2)
{
	int iVar1;
	D2C_Language DVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint8_t local_20;
	uint32_t local_1f;
	uint16_t local_1b;
	uint8_t bStack_19;
	uint32_t uStack_18;
	uint8_t uStack_14;
	char acStack_13[19];

	local_20 = 0x67;
	local_1f = a2;
	local_1b = (uint16_t)a1;
	iVar1 = sub_6FAAB360();
	uStack_18 = (**(code**)(iVar1 + 0x5c))();
	DVar2 = STRTABLE_GetLanguage();
	uStack_14 = (uint8_t)DVar2;
	uVar3 = sub_6FAA6A00();
	bStack_19 = byte_6FBA7894;
	if (uVar3 != 0)
	{
		uVar4 = sub_6FAA69F0();
		bStack_19 = (uint8_t)uVar4;
	}
	SStrCopy(acStack_13, gszPlayerName, 0x7fffffff);
	CLIENT_Send(0, &local_20, 0x1d);
	dword_6FBC1AF4 = dword_6FBC1AF4 + 0x1d;
	dword_6FBC1AFC = dword_6FBC1AFC + 1;
}

//D2Client.0x6FAAD530
void __fastcall sub_6FAAD530(int a1, int a2)
{
	if (a2 == 0)
	{
		dword_6FBA79F4 = a2;
		return;
	}
	dword_6FBA79F4 = (a1 << 8) / a2;
}

//D2Client.0x6FAAD550
int __cdecl sub_6FAAD550()
{
	return dword_6FBA79F4;
}
