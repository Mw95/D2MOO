#include <Windows.h>

#include <D2Launch.h>

// NOLINTBEGIN(bugprone-branch-clone)
//D2Launch.0x6FA17720
BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	ghD2LaunchInstance = hinstDLL;
	return TRUE;
}
// NOLINTEND(bugprone-branch-clone)
