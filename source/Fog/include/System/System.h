#pragma once

#include <D2BasicTypes.h>


#include <Fog.h>

#pragma pack(1)
#pragma pack()

// 1.10f: Inlined in 0x6FF5A5C0
void SYSTEM_InitializeSyncTime();

// 1.10f: 0x6FF5DC40 (#10051)
FOG_DLL_DECL void __fastcall FOG_LeaveCriticalSection(CRITICAL_SECTION* pCriticalSection, int nLine);
// 1.10f: 0x6FF5A760 (#10056)
FOG_DLL_DECL uint64_t __stdcall FOG_GetSaveDiskFreeSpace();
// 1.10f: 0x6FF5A840 (#10057)
FOG_DLL_DECL void __cdecl FOG_GetGlobalMemoryStatus(MEMORYSTATUS* pMemoryStatus);
// 1.10f: 0x6FF5A5B0 (#10059)
FOG_DLL_DECL DWORD __stdcall FOG_GetTickCount();
// 1.10f: 0x6FF616D0 (#10110)
FOG_DLL_DECL BOOL __fastcall FOG_ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
// 1.10f: 0x6FF616F0 (#10111)
FOG_DLL_DECL BOOL __fastcall FOG_WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
// 1.10f: 0x6FF61710 (#10112)
FOG_DLL_DECL DWORD __fastcall FOG_SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
// 1.10f: 0x6FF61800 (#10113)
FOG_DLL_DECL void __fastcall FOG_AppendBackslash(char* szPath, size_t nBufferSize);
// 1.10f: 0x6FF5A860 (#10176)
FOG_DLL_DECL BOOL __stdcall FOG_IsWindowsNT();
// 1.10f: 0x6FF61840 (#10239)
FOG_DLL_DECL void __fastcall FOG_GetModuleDirectory(char* pPathBuffer, size_t nBufferSize);
