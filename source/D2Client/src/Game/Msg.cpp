#include "Game/Msg.h"

#include "Core/WinMain.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/SCmd.h"
#include "UI/UI.h"

//D2Client.0x6FBA7968
uint32_t dword_6FBA7968;
//D2Client.0x6FBA7980
uint8_t byte_6FBA7980;
//D2Client.0x6FBA79F8
uint32_t dword_6FBA79F8;
//D2Client.0x6FBA7BF8
DWORD dword_6FBA7BF8;
//D2Client.0x6FBA7BFC
uint32_t dword_6FBA7BFC;
//D2Client.0x6FBA7C00
uint8_t byte_6FBA7C00;
//D2Client.0x6FBA7C04
uint8_t byte_6FBA7C04;
//D2Client.0x6FBA7C08
int32_t dword_6FBA7C08;

//D2Client.0x6FAAD560
void __fastcall sub_6FAAD560(int a1)
{
	uint8_t uVar1;
	void* p1;
	int iVar2;
	uint32_t p2;
	uint8_t* p1_00;
	int iVar3;
	int iVar4;
	uint8_t* puStack_714;
	int iStack_710;
	int iStack_708;
	uint8_t bStack_6fc;
	uint8_t uStack_6fb;
	uint32_t uStack_6fa;
	uint8_t auStack_6f6[258];
	char acStack_5f4[500];
	char local_400[1024];

	D2_ASSERT(gszPlayerName[0] != '\0');
	FOG_GetSavePath(local_400, 0x400);
	sprintf(acStack_5f4, "%s%s.d2s", local_400, gszPlayerName);
	p1 = fopen(acStack_5f4, "rb");
	if (p1 != nullptr)
	{
		iVar2 = fseek((FILE*)(p1), 0, 2);
		if (iVar2 == 0)
		{
			p2 = ftell((FILE*)(p1));
			fseek((FILE*)(p1), 0, 0);
			p1_00 = (uint8_t*)D2_ALLOC(p2);
			fread(p1_00, p2, 1, (FILE* __restrict)(p1));
			fclose((FILE*)(p1));
			if (p1_00 != nullptr)
			{
				if (a1 != 0)
				{
					iVar2 = 8;
					do
					{
						dword_6FBA79F4 = 0;
						sub_6FB242E0(0);
						Sleep(0xfa);
						iVar2 = iVar2 + -1;
					} while (iVar2 != 0);
				}
				iVar2 = (int)p2 / 0xff;
				puStack_714 = p1_00;
				if (0 < iVar2)
				{
					iStack_710 = 0;
					iStack_708 = iVar2;
					do
					{
						bStack_6fc = 0x6b;
						uStack_6fb = 0xff;
						iVar3 = 0;
						do
						{
							uVar1 = *puStack_714;
							puStack_714 = puStack_714 + 1;
							auStack_6f6[iVar3] = uVar1;
							iVar3 = iVar3 + 1;
						} while (iVar3 < 0xff);
						uStack_6fa = p2;
						CLIENT_Send(0, &bStack_6fc, 0x106);
						dword_6FBC1AF4 = dword_6FBC1AF4 + 0x106;
						dword_6FBC1AFC = dword_6FBC1AFC + 1;
						if (a1 != 0)
						{
							iVar4 = 8;
							iVar3 = iStack_710;
							do
							{
								if (iVar2 * 8 == 0)
								{
									dword_6FBA79F4 = 0;
								}
								else
								{
									dword_6FBA79F4 = iVar3 / (iVar2 * 8);
								}
								sub_6FB242E0(0);
								Sleep(0xfa);
								iVar3 = iVar3 + 0x100;
								iVar4 = iVar4 + -1;
							} while (iVar4 != 0);
						}
						iStack_710 = iStack_710 + 0x800;
						iStack_708 = iStack_708 + -1;
					} while (iStack_708 != 0);
				}
				bStack_6fc = 0x6b;
				iVar3 = (int)p2 % 0xff;
				iVar4 = 0;
				uStack_6fb = (uint8_t)iVar3;
				if (0 < iVar3)
				{
					do
					{
						auStack_6f6[iVar4] = *puStack_714;
						puStack_714 = puStack_714 + 1;
						iVar4 = iVar4 + 1;
					} while (iVar4 < iVar3);
				}
				uStack_6fa = p2;
				CLIENT_Send(0, &bStack_6fc, iVar3 + 7);
				dword_6FBC1AF4 = dword_6FBC1AF4 + iVar3 + 7;
				dword_6FBC1AFC = dword_6FBC1AFC + 1;
				D2_FREE(p1_00);
				if (iVar2 != 0)
				{
					dword_6FBA79F4 = (iVar2 * 0x100) / iVar2;
					return;
				}
				dword_6FBA79F4 = iVar2;
				return;
			}
		}
		else
		{
			fclose((FILE*)(p1));
		}
	}
	FOG_DisplayAssert("pbData", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAAD830
// TODO: parameters differ from the decompiled ones, body needs review
void __fastcall CLIENT_SendSimpleMessage(uint8_t nMessage)
{
	char local_1;

	sub_6FAAD850(&local_1, 1);
}

//D2Client.0x6FAAD850
void __fastcall sub_6FAAD850(char* a1, uint32_t a2)
{
	DWORD DVar1;
	int iVar2;
	uint32_t uVar3;
	char* pcVar4;
	char* pcVar5;
	uint8_t* pbVar6;
	bool bVar7;
	uint8_t abStack_200[512];

	D2_ASSERT(0x1ff >= (int)a2);
	DVar1 = GetTickCount();
	switch (*a1)
	{
	case '\x05':
	case '\x06':
	case '\a':
	case '\b':
	case '\t':
	case '\n':
	case '\f':
	case '\r':
	case '\x0e':
	case '\x0f':
	case '\x10':
	case '\x11':
		bVar7 = DVar1 - dword_6FBA7BF8 < 0x32;
		break;
	default:
		bVar7 = DVar1 - dword_6FBA7BF8 < 200;
		break;
	case ':':
		goto switchD_6faad89f_caseD_3a;
	}
	if (bVar7)
	{
		bVar7 = true;
		uVar3 = a2;
		pcVar4 = (char*)&dword_6FBA79F8;
		pcVar5 = a1;
		do
		{
			if (uVar3 == 0)
				break;
			uVar3 = uVar3 - 1;
			bVar7 = *pcVar4 == *pcVar5;
			pcVar4 = pcVar4 + 1;
			pcVar5 = pcVar5 + 1;
		} while (bVar7);
		if (bVar7)
		{
			return;
		}
	}
switchD_6faad89f_caseD_3a:
	pcVar4 = a1;
	pcVar5 = (char*)&dword_6FBA79F8;
	for (uVar3 = a2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*(uint32_t*)pcVar5 = *(uint32_t*)pcVar4;
		pcVar4 = pcVar4 + 4;
		pcVar5 = pcVar5 + 4;
	}
	for (uVar3 = a2 & 3; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*pcVar5 = *pcVar4;
		pcVar4 = pcVar4 + 1;
		pcVar5 = pcVar5 + 1;
	}
	pbVar6 = abStack_200;
	for (uVar3 = a2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*(uint32_t*)pbVar6 = *(uint32_t*)a1;
		a1 = (char*)((uint8_t*)a1 + 4);
		pbVar6 = pbVar6 + 4;
	}
	for (uVar3 = a2 & 3; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*pbVar6 = *a1;
		a1 = (char*)((uint8_t*)a1 + 1);
		pbVar6 = pbVar6 + 1;
	}
	dword_6FBA7BF8 = DVar1;
	iVar2 = CLIENT_Send(1, abStack_200, a2);
	if (iVar2 != 0)
	{
		dword_6FBC1AF4 = dword_6FBC1AF4 + a2;
		dword_6FBC1AFC = dword_6FBC1AFC + 1;
	}
}

//D2Client.0x6FAAD990
void __fastcall sub_6FAAD990(uint32_t a1, uint16_t a2)
{
	char local_4;
	uint16_t local_3;
	uint8_t uStack_1;

	uStack_1 = (uint8_t)((uint32_t)a1 >> 0x18);
	(*(uint32_t*)&local_4) = CONCAT21(a2, (char)a1);
	sub_6FAAD850(&local_4, 3);
}

//D2Client.0x6FAAD9B0
void __fastcall sub_6FAAD9B0(uint32_t a1, uint16_t a2, uint16_t a3)
{
	char local_8;
	uint16_t local_7;
	uint16_t local_5;

	local_5 = a3;
	local_8 = (char)a1;
	local_7 = a2;
	sub_6FAAD850(&local_8, 5);
}

//D2Client.0x6FAAD9E0
void __fastcall sub_6FAAD9E0(uint32_t a1, uint16_t a2, uint16_t a3, uint16_t a4)
{
	char local_8;
	uint16_t local_7;
	uint16_t local_5;
	uint16_t local_3;

	local_3 = a4;
	local_5 = a3;
	local_8 = (char)a1;
	local_7 = a2;
	sub_6FAAD850(&local_8, 7);
}

//D2Client.0x6FAADA20
void __fastcall sub_6FAADA20(uint32_t a1, uint32_t a2)
{
	char local_8;
	uint32_t local_7;

	local_8 = (char)a1;
	local_7 = a2;
	sub_6FAAD850(&local_8, 5);
}

//D2Client.0x6FAADA40
void __fastcall sub_6FAADA40(uint32_t a1, uint32_t a2, uint32_t a3)
{
	char local_c;
	uint32_t local_b;
	uint32_t local_7;

	local_7 = a3;
	local_c = (char)a1;
	local_b = a2;
	sub_6FAAD850(&local_c, 9);
}

//D2Client.0x6FAADA70
void __fastcall sub_6FAADA70(uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4)
{
	char local_10;
	uint32_t local_f;
	uint32_t local_b;
	uint32_t local_7;

	local_7 = a4;
	local_b = a3;
	local_10 = (char)a1;
	local_f = a2;
	sub_6FAAD850(&local_10, 0xd);
}

//D2Client.0x6FAADAA0
void __fastcall sub_6FAADAA0(uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5)
{
	char local_14;
	uint32_t local_13;
	uint32_t local_f;
	uint32_t local_b;
	uint32_t local_7;

	local_b = a4;
	local_7 = a5;
	local_f = a3;
	local_14 = (char)a1;
	local_13 = a2;
	sub_6FAAD850(&local_14, 0x11);
}

//D2Client.0x6FAADAE0
void __fastcall sub_6FAADAE0(uint32_t a1, uint32_t a2, int a3)
{
	char local_8;
	uint8_t uStack_7;
	uint8_t uStack_6;
	uint8_t uStack_5;
	uint16_t local_4;
	uint8_t local_2;

	local_8 = ']';
	uStack_6 = a3 != 0;
	uStack_5 = (uint8_t)a2;
	local_4 = (uint16_t)((uint32_t)a2 >> 8);
	local_2 = (uint8_t)((uint32_t)a2 >> 0x18);
	uStack_7 = (uint8_t)a1;
	sub_6FAAD850(&local_8, 7);
}

//D2Client.0x6FAADB20
void __fastcall sub_6FAADB20(uint32_t a1, uint32_t a2)
{
	char local_8;
	uint8_t uStack_7;
	uint32_t uStack_6;

	local_8 = '^';
	uStack_7 = (uint8_t)a1;
	uStack_6 = a2;
	sub_6FAAD850(&local_8, 6);
}

//D2Client.0x6FAADB50
void __fastcall sub_6FAADB50(int a1)
{
	uint32_t uVar1;
	uint32_t uVar2;
	char* pcVar3;
	char local_204;
	uint8_t local_203;
	uint8_t local_202;
	char local_201;
	char acStack_200[512];

	local_204 = *(char*)a1;
	local_203 = *(uint8_t*)(a1 + 1);
	local_202 = *(uint8_t*)(a1 + 2);
	uVar1 = SStrCopy(&local_201, (char*)(a1 + 3), 0x100);
	if ((char*)(a1 + 0x103) == nullptr)
	{
		acStack_200[uVar1] = '\0';
		pcVar3 = acStack_200 + uVar1 + 1;
	}
	else
	{
		uVar2 = SStrCopy(acStack_200 + uVar1, (char*)(a1 + 0x103), 0x10);
		pcVar3 = acStack_200 + uVar2 + uVar1 + 1;
	}
	*pcVar3 = '\0';
	sub_6FAAD850(&local_204, (uint32_t)(pcVar3 + (1 - (int)&local_204)));
}

//D2Client.0x6FAADBC0
bool __cdecl sub_6FAADBC0(uint32_t a1)
{
	int iVar1;
	DWORD DVar2;
	uint8_t abStack_200[512];

	if ((gnGameType == 0) || (gnGameType == 1))
	{
		iVar1 = WINDOW_GetState();
		if (iVar1 != 0)
			goto LAB_6faadc33;
	}
	DVar2 = GetTickCount();
	if (10000 < DVar2 - byte_6FBA7C00)
	{
		sub_6FAA9850(6);
		dword_6FBA7BFC = 1;
		dword_6FBA7968 = 0;
		return true;
	}
	iVar1 = D2NET_10017();
	if (iVar1 == 0)
	{
		return true;
	}
LAB_6faadc33:
	iVar1 = CLIENT_DequeueSystemPacket(abStack_200, 0x200);
	sub_6FAB1CB0(abStack_200, iVar1);
	return dword_6FBA7968 != 0;
}

//D2Client.0x6FAADC70
void __fastcall sub_6FAADC70()
{
	int iVar1;

	if (dword_6FBA7C08 == 0)
	{
		return 0;
	}
	dword_6FBA7C08 = 0;
	iVar1 = D2Game_10050();
	return iVar1;
}

//D2Client.0x6FAADC90
uint32_t __cdecl sub_6FAADC90()
{
	return dword_6FBA7BFC;
}

//D2Client.0x6FAADCA0
bool __cdecl sub_6FAADCA0(uint32_t a1)
{
	int iVar1;

	if ((gnGameType == 0) || (gnGameType == 1))
	{
		iVar1 = WINDOW_GetState();
		if (iVar1 != 0)
		{
			return false;
		}
	}
	iVar1 = D2NET_10025();
	if (iVar1 == 0)
	{
		sub_6FAA9850(6);
		dword_6FBA7BFC = 1;
		dword_6FBA7968 = 0;
		return true;
	}
	return iVar1 == 2;
}

//D2Client.0x6FAADD00
int32_t __fastcall sub_6FAADD00()
{
	int a1;
	char* szIpAddress;

	dword_6FBA7968 = 0;
	if (gnGameType == 0)
	{
		SERVER_Initialize(1, 1);
		a1 = 1;
	LAB_6faadd33:
		CLIENT_Initialize(a1, nullptr);
		CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAADCA0));
		SERVER_SetHackListEnabled(0);
	}
	else
	{
		if (gnGameType == 1)
		{
			SERVER_Initialize(2, 1);
			a1 = 2;
			goto LAB_6faadd33;
		}
		if (gnGameType == 4)
		{
			szIpAddress = "207.82.87.139";
		LAB_6faadd55:
			CLIENT_Initialize(0, szIpAddress);
			CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAADCA0));
			goto LAB_6faaddc4;
		}
		if ((gnGameType != 6) && (gnGameType != 8))
		{
			szIpAddress = "207.82.87.243";
			goto LAB_6faadd55;
		}
		SERVER_Initialize(0, 1);
		SERVER_SetMaxClientsPerGame(8);
		SERVER_SetHackListEnabled(0);
		CLIENT_Initialize(0, "207.82.87.243");
		CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAADCA0));
	}
	GAME_InitGameDataTable((D2GameDataTableStrc*)&byte_6FBA7828, &byte_6FBA7980);
	dword_6FBA7C08 = 1;
	D2Game_10046();
LAB_6faaddc4:
	byte_6FBA7C00 = GetTickCount();
	dword_6FBA7BFC = 0;
	CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAADBC0));
	CLIENT_PopAppMode();
}

//D2Client.0x6FAADDF0
bool __cdecl sub_6FAADDF0(uint32_t a1)
{
	int iVar1;
	DWORD DVar2;
	uint8_t abStack_200[512];

	WINDOW_GetState();
	if ((gnGameType == 0) || (gnGameType == 1))
	{
		GAME_ProcessNetworkMessages();
	}
	iVar1 = CLIENT_DequeueSystemPacket(abStack_200, 0x200);
	sub_6FAB1CB0(abStack_200, iVar1);
	DVar2 = GetTickCount();
	if (10000 < DVar2 - byte_6FBA7C04)
	{
		return true;
	}
	return dword_6FBA7968 == 0;
}

//D2Client.0x6FAADE60
int32_t __fastcall sub_6FAADE60()
{
	byte_6FBA7C04 = GetTickCount();
	CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FAADDF0));
	CLIENT_Release();
	if ((((gnGameType == 0) || (gnGameType == 1)) || (gnGameType == 6)) || (gnGameType == 8))
	{
		SERVER_Release();
	}
	CLIENT_PopAppMode();
}
