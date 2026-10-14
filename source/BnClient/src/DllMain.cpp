#include <Windows.h>

#include "BnMessQueue.h"


HINSTANCE ghBnClientInstance;


//Bnclient.0x6FF0AD30
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		BNMESSQUEUE_Initialize();
		break;

	case DLL_PROCESS_DETACH:
		BNMESSQUEUE_Shutdown();
		break;

	default:
		break;
	}

	ghBnClientInstance = hinstDLL;
	return TRUE;
}
