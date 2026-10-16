#include "StormInternal.h"

// Storm.0x6FFDB260
BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		StormProcessAttach(hModule, lpReserved == nullptr);
		break;
	case DLL_PROCESS_DETACH:
		StormProcessDetach();
		break;
	default:
		break;
	}
	return TRUE;
}
