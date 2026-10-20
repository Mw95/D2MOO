#include "Core/Interface.h"

#include "Core/WinMain.h"


//D2Client.0x6FB74108
static D2ClientInterfaceStrc gClientInterface =
{
	CLIENT_InterfaceEntry,
};

//D2Client.0x6FB9A70C
HINSTANCE ghD2ClientInstance;


//D2Client.0x6FAA1160
void __cdecl operator delete(void* pMemory)
{
	if (pMemory)
	{
		SMemFree(pMemory, "delete", -1, 0);
	}
}

//D2Client.0x6FAA11C0 (#10004)
D2ClientInterfaceStrc* __cdecl QueryInterface()
{
	return &gClientInterface;
}

//D2Client.0x6FAA11D0
int32_t __fastcall CLIENT_InterfaceEntry(D2ConfigStrc* pConfig)
{
	return CLIENT_Main(ghD2ClientInstance, pConfig);
}
