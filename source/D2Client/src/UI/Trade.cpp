#include "UI/Trade.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/CmdTbl.h"
#include "UI/Dialog.h"
#include "UI/EditBox.h"
#include "UI/Hireables.h"
#include "UI/Inv.h"
#include "UI/NpcMenu.h"
#include "UI/Panel.h"
#include "UI/Party.h"
#include "UI/QuestLog.h"
#include "UI/Restart.h"
#include "UI/SkillsTree.h"
#include "UI/Text.h"
#include "UI/UI.h"
#include "UI/UseItem.h"
#include "Unit/CUnit.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FBB9F80
uint8_t byte_6FBB9F80;
//D2Client.0x6FBB9FA0
DWORD dword_6FBB9FA0;
//D2Client.0x6FBB9FA4
uint32_t dword_6FBB9FA4;
//D2Client.0x6FBB9FAC
uint8_t byte_6FBB9FAC;
//D2Client.0x6FBB9FAE
uint16_t word_6FBB9FAE;
//D2Client.0x6FBB9FB0
uint32_t dword_6FBB9FB0;
//D2Client.0x6FBB9FB4
int32_t dword_6FBB9FB4;
//D2Client.0x6FBB9FB8
int32_t dword_6FBB9FB8;
//D2Client.0x6FBBA1E4
D2CellFileStrc* gpCellFile_6FBBA1E4;
//D2Client.0x6FBBA768
D2CellFileStrc* gpCellFile_6FBBA768;
//D2Client.0x6FBBA76C
D2CellFileStrc* gpCellFile_6FBBA76C;
//D2Client.0x6FBBA770
D2CellFileStrc* gpCellFile_6FBBA770;

//D2Client.0x6FB1F6E0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB1F6E0(int a1)
{
	D2UnitStrc* pDVar1;
	Unicode* pUVar2;
	int iVar3;
	uint32_t uVar4;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t extraout_ECX_03;
	uint32_t extraout_ECX_04;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	code* pcVar9;
	int iVar10;

	uVar4 = (uint32_t)((uint32_t)a1 >> 8);
	switch (*(uint8_t*)(a1 + 1))
	{
	case 0:
		if (dword_6FBB9FB8 != 0)
		{
			sub_6FAAD9E0(CONCAT31(uVar4, 0x4f), 2, 0, 0);
			if (dword_6FBB9FB8 != 7)
			{
				byte_6FBB9FA8 = 1;
				dword_6FBB9FA0 = GetTickCount();
				dword_6FBB9FB8 = 7;
			}
			FOG_Trace("waiting for query response mode:%d at line %d of file %s\n", dword_6FBB9FB8, __LINE__, __FILE__);
			return;
		}
		iVar3 = sub_6FB23230(0x17);
		if (iVar3 != 0)
		{
		LAB_6fb1f770:
			dword_6FBB9FB8 = 1;
			if (dword_6FBB9F7C == 0)
			{
				dword_6FBB9F7C = (int)sub_6FAD6BE0(0x140, 100, 0x6fb1fe10, 0x6fb1fe10, 0, 1, 1, 0, 0, 0, 1);
				sub_6FAD7150(dword_6FBB9F7C, 1);
				iVar10 = 0;
				uVar8 = 0;
				uVar7 = 1;
				iVar3 = 0;
				uVar6 = 0;
				uVar5 = 0xf;
				pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfcb));
				sub_6FAD7180(dword_6FBB9F7C, pUVar2, uVar5, uVar6, iVar3, uVar7, uVar8, iVar10);
				iVar10 = 1;
				pcVar9 = (code*)(sub_6FB1FE10);
				uVar7 = 1;
				iVar3 = 0;
				uVar6 = 0;
				uVar5 = 0xf;
				pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd48));
				sub_6FAD7180(dword_6FBB9F7C, pUVar2, uVar5, uVar6, iVar3, uVar7, (int)(pcVar9), iVar10);
				sub_6FAD7090(dword_6FBB9F7C, -1);
				sub_6FAEB100(0);
				return;
			}
			FOG_DisplayAssert("sghDialogWaitingForOther == NULL",
			    __FILE__, __LINE__);
			exit(-1);
		}
		iVar3 = sub_6FB23260(0x17, 0, 0);
		uVar5 = extraout_ECX;
		if (iVar3 != 0)
		{
			sub_6FAED270();
			dword_6FBB9FA0 = 0xffffffff;
			goto LAB_6fb1f770;
		}
		goto LAB_6fb1f9ed;
	case 1:
		if (dword_6FBB9FB8 != 0)
		{
			sub_6FAAD9E0(CONCAT31(uVar4, 0x4f), 2, 0, 0);
			if (dword_6FBB9FB8 != 7)
			{
				byte_6FBB9FA8 = 1;
				dword_6FBB9FA0 = GetTickCount();
				dword_6FBB9FB8 = 7;
			}
			FOG_Trace(" mode:%d at line %d of file %s\n", dword_6FBB9FB8, __LINE__, __FILE__);
			return;
		}
		pDVar1 = CUNIT_GetPlayer();
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		uVar5 = extraout_ECX_00;
		if (((pDVar1 != nullptr) ||
		        (iVar3 = sub_6FAD7530(), uVar5 = extraout_ECX_01, iVar3 != 0)) ||
		    (dword_6FBB9FB4 != 0))
		{
		LAB_6fb1f9bc:
			sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)uVar5 >> 8), 0x4f), 2, 0, 0);
			return;
		}
		dword_6FBB9FB4 = (int)sub_6FAD6BE0(0x140, 100, 0x6fb1fdb0, 0x6fb1fdb0, 0, 1, 1, 0, 0, 0, 1);
		sub_6FAD7150(dword_6FBB9FB4, 1);
		iVar10 = 0;
		uVar8 = 0;
		uVar7 = 1;
		iVar3 = 0;
		uVar6 = 0;
		uVar5 = 0xf;
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfca));
		sub_6FAD7180(dword_6FBB9FB4, pUVar2, uVar5, uVar6, iVar3, uVar7, uVar8, iVar10);
		iVar10 = 1;
		pcVar9 = (code*)(sub_6FB1FD60);
		uVar7 = 1;
		iVar3 = 0;
		uVar6 = 0;
		uVar5 = 0xf;
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd49));
		sub_6FAD7180(dword_6FBB9FB4, pUVar2, uVar5, uVar6, iVar3, uVar7, (int)(pcVar9), iVar10);
		iVar10 = 1;
		pcVar9 = (code*)(sub_6FB1FDB0);
		uVar7 = 1;
		iVar3 = 0;
		uVar6 = 0;
		uVar5 = 0xf;
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd48));
		sub_6FAD7180(dword_6FBB9FB4, pUVar2, uVar5, uVar6, iVar3, uVar7, (int)(pcVar9), iVar10);
		sub_6FAD7090(dword_6FBB9FB4, -1);
		iVar3 = sub_6FB23230(5);
		uVar5 = extraout_ECX_02;
		if (iVar3 != 0)
			goto LAB_6fb1f9bc;
		iVar3 = sub_6FB23230(0x17);
		if (iVar3 != 0)
		{
		LAB_6fb1fa32:
			dword_6FBB9FB8 = 2;
			sub_6FAEB100(0);
			return;
		}
		iVar3 = sub_6FB23260(0x17, 0, 0);
		uVar5 = extraout_ECX_03;
		if (iVar3 != 0)
		{
			dword_6FBB9FA0 = 0xffffffff;
			goto LAB_6fb1fa32;
		}
	LAB_6fb1f9ed:
		sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)uVar5 >> 8), 0x4f), 2, 0, 0);
		if (dword_6FBB9FB8 != 7)
		{
			byte_6FBB9FA8 = 1;
			dword_6FBB9FA0 = GetTickCount();
			dword_6FBB9FB8 = 7;
			return;
		}
		break;
	case 2:
		sub_6FAEB8B0(0, 0);
		sub_6FB1F5B0(0);
		return;
	case 5:
		iVar3 = sub_6FB23860(0x17);
		if (iVar3 != 0)
		{
			dword_6FBB9FA0 = 0xffffffff;
			sub_6FAEB100(1);
			switch (dword_6FBB9FB8)
			{
			case 3:
				dword_6FBB9FB8 = 5;
				sub_6FAEB8B0(0, 1);
				return;
			case 4:
				dword_6FBB9FB8 = 6;
				sub_6FAEB8B0(1, 1);
				return;
			case 5:
				sub_6FAEB8B0(0, 1);
				FOG_Trace("other ready mode %d recvd%d at line %d of file %s\n", dword_6FBB9FB8,
				    (uint32_t) * (uint8_t*)(a1 + 1), __LINE__, __FILE__);
				return;
			case 6:
				FOG_Trace("other ready mode %d recvd %d at line %d of file %s\n", dword_6FBB9FB8,
				    (uint32_t) * (uint8_t*)(a1 + 1), __LINE__, __FILE__);
				break;
			case 7:
				break;
			default:
				sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)dword_6FBB9FB8 >> 8), 0x4f), 2, 0, 0);
				if (dword_6FBB9FB8 != 7)
				{
					byte_6FBB9FA8 = 1;
					dword_6FBB9FA0 = GetTickCount();
					dword_6FBB9FB8 = 7;
				}
				FOG_Trace("other ready mode %d recvd %d at line %d of file %s\n", dword_6FBB9FB8,
				    (uint32_t) * (uint8_t*)(a1 + 1), __LINE__, __FILE__);
				return;
			}
		}
		break;
	case 6:
		iVar3 = sub_6FB23860(0x17);
		if (iVar3 != 0)
		{
			sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX_04 >> 8), 0x4f), 8, word_6FBB9FAE, byte_6FBB9FAC);
			dword_6FBB9FA0 = 0xffffffff;
			sub_6FAEB100(1);
			switch (dword_6FBB9FB8)
			{
			case 1:
				goto switchD_6fb1fc05_caseD_1;
			default:
				sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)dword_6FBB9FB8 >> 8), 0x4f), 2, 0, 0);
				if (dword_6FBB9FB8 != 7)
				{
					byte_6FBB9FA8 = 1;
					dword_6FBB9FA0 = GetTickCount();
					dword_6FBB9FB8 = 7;
				}
				FOG_Trace("other not ready state %d recvd %d at line %d of file %s\n", dword_6FBB9FB8,
				    (uint32_t) * (uint8_t*)(a1 + 1), __LINE__, __FILE__);
				return;
			case 4:
			case 5:
			case 6:
				sub_6FAEB8B0(0, 0);
				dword_6FBB9FB8 = 3;
				return;
			case 7:
				dword_6FBB9FB8 = 3;
			case 3:
				sub_6FAEB8B0(0, 0);
				return;
			}
		}
		break;
	case 9:
		pDVar1 = CUNIT_GetPlayer();
		sub_6FB514E0(pDVar1, 0x17);
		return;
	case 10:
		pDVar1 = sub_6FB269F0(dword_6FBB9FB0, 0);
		if (pDVar1 != nullptr)
		{
			sub_6FB514E0(pDVar1, 0x17);
			return;
		}
		break;
	case 0xc:
		dword_6FBB9FB8 = 0;
		sub_6FB1F5B0(0);
		return;
	case 0xd:
		dword_6FBB9FB8 = 0;
		sub_6FB1F5B0(1);
		return;
	case 0xe:
		sub_6FAED260();
		return;
	case 0xf:
		sub_6FAED270();
		return;
	case 0x10:
		sub_6FAEC510();
		return;
	case 0x11:
		sub_6FAEC6C0();
		return;
	case 0x15:
		sub_6FAECF90();
		return;
	}
	return;
switchD_6fb1fc05_caseD_1:
	dword_6FBB9FA4 = 0;
	sub_6FAEB8B0(0, 0);
	dword_6FBB9FB8 = 3;
	if (dword_6FBB9F7C == 0)
	{
		dword_6FBB9FB8 = 3;
		return;
	}
	sub_6FAD6DC0();
	dword_6FBB9F7C = 0;
}

//D2Client.0x6FB1FD60
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FB1FD60()
{
	uint32_t extraout_ECX;

	sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
	sub_6FAD6DC0();
	dword_6FBB9FB4 = 0;
	dword_6FBB9FB8 = 3;
	sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 3, 0, 0);
	return 1;
}

//D2Client.0x6FB1FDB0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FB1FDB0()
{
	uint32_t extraout_ECX;

	sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
	sub_6FAD6DC0();
	dword_6FBB9FB4 = 0;
	dword_6FBB9FB8 = 7;
	sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 2, 0, 0);
	dword_6FBB9FA0 = GetTickCount();
	return 1;
}

//D2Client.0x6FB1FE10
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FB1FE10()
{
	uint32_t extraout_ECX;

	sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
	sub_6FAD6DC0();
	dword_6FBB9F7C = 0;
	dword_6FBB9FB8 = 7;
	dword_6FBB9FA0 = GetTickCount();
	sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 2, 0, 0);
	return 1;
}

//D2Client.0x6FB1FE70
void __fastcall sub_6FB1FE70(int a1)
{
	uint32_t local_10;
	uint32_t local_c;
	uint32_t local_8;
	uint32_t local_4;

	local_10 = *(uint32_t*)(a1 + 1);
	local_c = *(uint32_t*)(a1 + 5);
	local_8 = *(uint32_t*)(a1 + 9);
	local_4 = *(uint32_t*)(a1 + 0xd) & 0xffffff;
	Unicode::win2Unicode((Unicode*)&byte_6FBB9F80, (char*)&local_10, 0x10);
	dword_6FBB9FB0 = *(uint32_t*)(a1 + 0x11);
}

//D2Client.0x6FB1FEC0
uint8_t* __cdecl sub_6FB1FEC0()
{
	return &byte_6FBB9F80;
}

//D2Client.0x6FB1FED0
void __fastcall sub_6FB1FED0(uint32_t a1)
{
	dword_6FBB9FB8 = 7;
	sub_6FAAD9E0(CONCAT31((int32_t)(CONCAT22((short)((uint32_t)a1 >> 0x10), word_6FBB9FAE) >> 8), 0x4f), 4,
	    word_6FBB9FAE, byte_6FBB9FAC);
	dword_6FBB9FA0 = 0xffffffff;
}

//D2Client.0x6FB1FF00
void __fastcall sub_6FB1FF00(uint32_t a1)
{
	sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x4f), 7, 0, 0);
	dword_6FBB9FB8 = 3;
}

//D2Client.0x6FB1FF20
void __fastcall sub_6FB1FF20(uint32_t a1, char a2)
{
	if (a2 != '\0')
	{
		byte_6FBB9FAC = a1;
		return;
	}
	dword_6FBB9FA4 = a1;
}

//D2Client.0x6FB1FF40
uint32_t __cdecl sub_6FB1FF40()
{
	return dword_6FBB9FA4;
}

//D2Client.0x6FB1FF50
uint32_t __cdecl sub_6FB1FF50()
{
	return byte_6FBB9FAC;
}

//D2Client.0x6FB1FF60
void __fastcall sub_6FB1FF60(uint32_t a1)
{
	D2UnitStrc* pUnit;
	uint32_t uVar1;
	int nStatId;
	uint16_t nLayer;
	uint16_t uStack_e;
	uint16_t uStack_c;
	uint16_t uStack_6;

	uStack_e = (uint16_t)(a1 >> 0x10);
	uVar1 = (uint32_t)(a1 >> 8);
	if (((dword_6FBB9FB8 != 4) && (dword_6FBB9FB8 != 5)) && (dword_6FBB9FB8 != 6))
	{
		nLayer = 0;
		nStatId = 0xe;
		pUnit = CUNIT_GetPlayer();
		byte_6FBB9FAC = STATLIST_UnitGetStatValue(pUnit, nStatId, nLayer);
		uStack_6 = (uint16_t)(byte_6FBB9FAC >> 0x10);
		if (byte_6FBB9FAC <= a1)
		{
			sub_6FAAD9E0(CONCAT31(uVar1, 0x4f), 8, uStack_6, (short)byte_6FBB9FAC);
			return;
		}
		byte_6FBB9FAC = a1;
		sub_6FAAD9E0(CONCAT31((int32_t)(CONCAT22(uStack_c, uStack_e) >> 8), 0x4f), 8, uStack_e, (short)a1);
		return;
	}
	sub_6FAAD9E0(CONCAT31(uVar1, 0x4f), 7, 0, 0);
	dword_6FBB9FB8 = 3;
}

//D2Client.0x6FB1FFF0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FB1FFF0()
{
	DWORD DVar1;
	uint32_t extraout_ECX;

	if (dword_6FBB9FB8 == 7)
	{
		if (dword_6FBB9FA0 != 0xffffffff)
		{
			DVar1 = GetTickCount();
			if (dword_6FBB9FA0 + 30000 < DVar1)
			{
				sub_6FAED220();
				dword_6FBB9FB8 = 0;
				sub_6FB1F5B0(0);
				sub_6FAAD420((int32_t)extraout_ECX);
				CLIENT_SetExitToMenu(0);
				sub_6FAA9430(1);
				sub_6FAAB240();
			}
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FB20060
void __cdecl sub_6FB20060()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&dword_6FBBA1F0;
	iVar1 = 0x50;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FB20080
void __cdecl sub_6FB20080()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&word_6FBB9FE0;
	iVar1 = 0x100;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FB200A0
void __cdecl sub_6FB200A0()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&byte_6FBBA4A0;
	iVar1 = 0x100;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FB200C0
void __cdecl sub_6FB200C0()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&word_6FBBA2A0;
	iVar1 = 0x100;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FB200E0
void __cdecl sub_6FB200E0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	sub_6FB1F1A0();
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB20100
D2CellFileStrc* __fastcall sub_6FB20100(char* a1)
{
	char* pcVar1;
	uint32_t uVar2;
	char* pcVar3;
	D2CellFileStrc* pDVar4;
	char cVar5;
	CHAR local_104[260];

	wsprintfA(local_104, "%s\\UI\\", "DATA\\GLOBAL");
	uVar2 = SStrLen(local_104);
	cVar5 = *a1;
	pcVar1 = local_104 + uVar2;
	pcVar3 = pcVar1;
	if (cVar5 != '\0')
	{
		do
		{
			*pcVar3 = cVar5;
			cVar5 = pcVar3[(int)(a1 + (1 - (int)pcVar1))];
			pcVar3 = pcVar3 + 1;
		} while (cVar5 != '\0');
	}
	*pcVar3 = '\0';
	pDVar4 = CLIENT_LoadCellFile(local_104, 0);
	return pDVar4;
}

//D2Client.0x6FB20160
void __cdecl sub_6FB20160()
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_108;
	CHAR aCStack_104[260];

	sub_6FAFE370();
	sub_6FB09B80();
	sub_6FB1A820();
	sub_6FAEEBA0();
	sub_6FADA720();
	sub_6FAF7BD0();
	sub_6FACF380();
	sub_6FB25BC0();
	sub_6FB1F370();
	dword_6FBB9FC4 = 0;
	gpuint32_t_6FBB9FC8 = nullptr;
	gpint32_t_6FBB9FCC = nullptr;
	gpuint32_t_6FBB9FD4 = nullptr;
	gpint32_t_6FBB9FD0 = nullptr;
	dword_6FBB9FD8 = 0;
	sub_6FADE8A0();
	puVar2 = &dword_6FBBA6A8;
	for (iVar1 = 0x26; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	sub_6FB23260(0, 0, 0);
	iVar1 = SRegLoadValue("Diablo II", "Mini Panel", 1, (DWORD*)(&local_108));
	if ((iVar1 == 0) || (local_108 == 0))
	{
		sub_6FB23260(0x15, 2, 0);
	}
	sub_6FB23260(0x22, 0, 0);
	wsprintfA(aCStack_104, "%s\\UI\\CURSOR\\Pentspin", "DATA\\GLOBAL");
	gpCellFile_6FBBA768 = CLIENT_LoadCellFile(aCStack_104, 0);
	wsprintfA(aCStack_104, "%s\\UI\\CURSOR\\focus16", "DATA\\GLOBAL");
	gpCellFile_6FBBA770 = CLIENT_LoadCellFile(aCStack_104, 0);
	wsprintfA(aCStack_104, "%s\\UI\\menu\\boxpieces", "DATA\\GLOBAL");
	gpCellFile_6FBBA1E4 = CLIENT_LoadCellFile(aCStack_104, 0);
	sub_6FB24840();
	sub_6FAD6860();
	sub_6FAEAFD0();
	sub_6FAEFA40();
	sub_6FB04140();
	sub_6FAD41E0();
	sub_6FB083C0();
	sub_6FAFC2C0();
}

//D2Client.0x6FB202C0
void __cdecl sub_6FB202C0()
{
	D2UnitStrc* pDVar1;

	sub_6FB23260(0, 1, 0);
	sub_6FAFE4D0();
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 != nullptr)
	{
		sub_6FB18680();
		sub_6FB16370();
	}
	D2Win_10116();
	sub_6FB1A870();
	sub_6FB09BF0();
	sub_6FADA140();
	sub_6FAEEBC0();
	sub_6FADA8F0();
	sub_6FAF7C90();
	sub_6FACF670();
	sub_6FB25BE0();
	sub_6FB1F380();
	sub_6FB23A60();
	sub_6FADE970();
	sub_6FB248A0();
	sub_6FB04220();
	sub_6FAEB090();
	sub_6FAD6870();
	sub_6FAEFA80();
	if (gpCellFile_6FBBA768 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA768);
		gpCellFile_6FBBA768 = nullptr;
	}
	if (gpCellFile_6FBBA770 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA770);
		gpCellFile_6FBBA770 = nullptr;
	}
	if (gpCellFile_6FBBA1E4 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA1E4);
		gpCellFile_6FBBA1E4 = nullptr;
	}
	if (gpCellFile_6FBBA76C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA76C);
		gpCellFile_6FBBA76C = nullptr;
	}
	if (gpCellFile_6FBBA1E8 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA1E8);
		gpCellFile_6FBBA1E8 = nullptr;
	}
	sub_6FAD49D0();
	sub_6FB08640();
	sub_6FAFC590();
}

//D2Client.0x6FB203C0
void __cdecl sub_6FB203C0()
{
	sub_6FADD2F0();
	sub_6FB01C30();
	sub_6FB01C50();
	sub_6FB16BE0();
	sub_6FAFE930();
	sub_6FAFE950();
	sub_6FAFE990();
	sub_6FAFE970();
}

//D2Client.0x6FB203F0
void __fastcall sub_6FB203F0(int a1)
{
	int iVar1;
	uint16_t uVar2;
	int iVar3;

	if (a1 != 0)
	{
		iVar1 = Unicode::strlen((Unicode*)a1);
		iVar3 = 0;
		if (0 < iVar1)
		{
			do
			{
				uVar2 = *(uint16_t*)(a1 + iVar3 * 2);
				if (uVar2 < 0x100)
				{
					uVar2 = Unicode((unsigned short)((uint32_t)uVar2)).toUpper().ch;
				}
				*(uint16_t*)(a1 + iVar3 * 2) = uVar2;
				iVar3 = iVar3 + 1;
			} while (iVar3 < iVar1);
		}
	}
}

//D2Client.0x6FB20430
short* __fastcall sub_6FB20430(short* a1, char a2)
{
	Unicode* pUVar1;
	int iVar2;
	CHAR aCStack_80c[4];
	Unicode aUStack_808[4];
	Unicode local_800;
	Unicode local_7fe[1023];

	if (*a1 != 0)
	{
		local_800.ch = 0;
		pUVar1 = local_7fe;
		for (iVar2 = 0x1ff; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*(uint32_t*)pUVar1 = 0;
			pUVar1 = pUVar1 + 2;
		}
		pUVar1->ch = 0;
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9a));
		Unicode::strcpy(&local_800, pUVar1);
		wsprintfA(aCStack_80c, "%c", (int)(char)(a2 + '0'));
		Unicode::win2Unicode(aUStack_808, aCStack_80c, 2);
		Unicode::strcat(&local_800, aUStack_808);
		Unicode::strcat(&local_800, (Unicode*)a1);
		Unicode::strcpy((Unicode*)a1, &local_800);
	}
	return a1;
}
