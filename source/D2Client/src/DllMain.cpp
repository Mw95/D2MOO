#include <Windows.h>

#include "Core/Interface.h"

//D2Client.0x6FAA11A0
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved)
{
	ghD2ClientInstance = hModule;
	return TRUE;
}
