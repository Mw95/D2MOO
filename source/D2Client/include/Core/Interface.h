#pragma once

#include <D2Client.h>


struct D2ClientInterfaceStrc
{
	int32_t(__fastcall* pfEntry)(D2ConfigStrc* pConfig);	//0x00
};


//D2Client.0x6FB9A70C
extern HINSTANCE ghD2ClientInstance;


//D2Client.0x6FAA11C0 (#10004)
extern "C" __declspec(dllexport) D2ClientInterfaceStrc* __cdecl QueryInterface();
//D2Client.0x6FAA11D0
int32_t __fastcall CLIENT_InterfaceEntry(D2ConfigStrc* pConfig);
