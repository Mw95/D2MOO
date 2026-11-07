#pragma once

#include <Windows.h>

#include <cstdint>

// Imports of Fog.dll ordinals that are not (yet) declared by D2MOO.
// They are resolved by ordinal at runtime so that BnClient works with both the original and the D2MOO dlls.

HMODULE delayedFOGDllBaseGet();

//Fog.#10262
BOOL __fastcall FOG_SOCKET_GetSockName(struct FSafeSock* pSafeSock, struct sockaddr* pName, int* pNameLen);
//Fog.#10263
BOOL __fastcall FOG_GetHardwareInfo(void* pBuffer, uint32_t* pSize);
