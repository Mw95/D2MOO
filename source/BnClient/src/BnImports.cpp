// Made up filename

#include "BnImports.h"


HMODULE delayedFOGDllBaseGet()
{
	static HMODULE DLLBASE_FOG = LoadLibraryA("Fog.dll");
	return DLLBASE_FOG;
}

template<typename FunctionType>
static FunctionType BNIMPORTS_GetOrdinal(HMODULE hModule, int nOrdinal)
{
	return (FunctionType)GetProcAddress(hModule, (LPCSTR)(uintptr_t)nOrdinal);
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
