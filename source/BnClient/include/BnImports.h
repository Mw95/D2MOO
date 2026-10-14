#pragma once

#include <Windows.h>

#include <cstdint>

// Imports of Fog.dll and D2Lang.dll ordinals that are not (yet) implemented by D2MOO.
// They are resolved by ordinal at runtime so that BnClient works with both the original and the D2MOO dlls.

HMODULE delayedFOGDllBaseGet();
HMODULE delayedD2LANGDllBaseGet();

//Fog.#10111
BOOL __fastcall FOG_WriteFile(HANDLE hFile, const void* pBuffer, DWORD nNumberOfBytesToWrite, DWORD* pNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
//Fog.#10112
DWORD __fastcall FOG_SetFilePointer(HANDLE hFile, LONG lDistanceToMove, LONG* lpDistanceToMoveHigh, DWORD dwMoveMethod);
//Fog.#10262
BOOL __fastcall FOG_SOCKET_GetSockName(struct FSafeSock* pSafeSock, struct sockaddr* pName, int* pNameLen);
//Fog.#10263
BOOL __fastcall FOG_GetHardwareInfo(void* pBuffer, uint32_t* pSize);
//D2Lang.#10006
void __stdcall D2LANG_GetLanguageCode(char* szBuffer, int nBufferSize);
