// Made up filename

#include "BnImports.h"


HMODULE delayedFOGDllBaseGet()
{
	static HMODULE DLLBASE_FOG = LoadLibraryA("Fog.dll");
	return DLLBASE_FOG;
}

HMODULE delayedD2LANGDllBaseGet()
{
	static HMODULE DLLBASE_D2LANG = LoadLibraryA("D2Lang.dll");
	return DLLBASE_D2LANG;
}

template<typename FunctionType>
static FunctionType BNIMPORTS_GetOrdinal(HMODULE hModule, int nOrdinal)
{
	return (FunctionType)GetProcAddress(hModule, (LPCSTR)(uintptr_t)nOrdinal);
}

//Fog.#10111
BOOL __fastcall FOG_WriteFile(HANDLE hFile, const void* pBuffer, DWORD nNumberOfBytesToWrite, DWORD* pNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	static const auto pfFunction = BNIMPORTS_GetOrdinal<decltype(&FOG_WriteFile)>(delayedFOGDllBaseGet(), 10111);
	return pfFunction(hFile, pBuffer, nNumberOfBytesToWrite, pNumberOfBytesWritten, lpOverlapped);
}

//Fog.#10112
DWORD __fastcall FOG_SetFilePointer(HANDLE hFile, LONG lDistanceToMove, LONG* lpDistanceToMoveHigh, DWORD dwMoveMethod)
{
	static const auto pfFunction = BNIMPORTS_GetOrdinal<decltype(&FOG_SetFilePointer)>(delayedFOGDllBaseGet(), 10112);
	return pfFunction(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
}

//Fog.#10262
BOOL __fastcall FOG_SOCKET_GetSockName(FSafeSock* pSafeSock, sockaddr* pName, int* pNameLen)
{
	static const auto pfFunction = BNIMPORTS_GetOrdinal<decltype(&FOG_SOCKET_GetSockName)>(delayedFOGDllBaseGet(), 10262);
	return pfFunction(pSafeSock, pName, pNameLen);
}

//Fog.#10263
BOOL __fastcall FOG_GetHardwareInfo(void* pBuffer, uint32_t* pSize)
{
	static const auto pfFunction = BNIMPORTS_GetOrdinal<decltype(&FOG_GetHardwareInfo)>(delayedFOGDllBaseGet(), 10263);
	return pfFunction(pBuffer, pSize);
}

//D2Lang.#10006
void __stdcall D2LANG_GetLanguageCode(char* szBuffer, int nBufferSize)
{
	static const auto pfFunction = BNIMPORTS_GetOrdinal<decltype(&D2LANG_GetLanguageCode)>(delayedD2LANGDllBaseGet(), 10006);
	pfFunction(szBuffer, nBufferSize);
}
