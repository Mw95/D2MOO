#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

// Version stored in the records of the Crashdump file
#define CRASHDUMP_VERSION 0x10A0027
#define CRASHDUMP_MAX_PARAMETERS 8

// Internal

// 1.10f: 0x6FF5F520
// Loads imagehlp.dll and starts the stack walk thread
BOOL EXCEPTION_LoadImageHlp();
// 1.10f: 0x6FF5F790
BOOL EXCEPTION_UnloadImageHlp();
// 1.10f: 0x6FF60940
// Logs an annotated dump of the stack of the thread, then its call stack
BOOL __fastcall EXCEPTION_StackCrawl(HANDLE hThread, const CONTEXT* pContext);

// Exported

// 1.10f: 0x6FF5E6B0 (#10052)
// Logs the exception and the state of the thread, then displays a message box
FOG_DLL_DECL LONG __stdcall FOG_UnhandledExceptionFilter(EXCEPTION_POINTERS* pExceptionInfo);
// 1.10f: 0x6FF5FAC0 (#10237)
// Logs the call stack of the current thread (up to 16 frames) to the given log file
FOG_DLL_DECL BOOL __fastcall FOG_QuickStackWalk(const char* szFileSubName);
// 1.10f: 0x6FF61370 (#10263)
// Reads and deletes the Crashdump file, and writes a summary of the different crashes in pBuffer:
// a count byte, then for each crash {uint16_t nCount, uint32_t nVersion, uint32_t nCode, uint32_t nAddress, uint8_t nParameters, uint32_t aParameters[nParameters]}.
// pSize contains the size of pBuffer, and receives the size of the summary.
FOG_DLL_DECL BOOL __fastcall FOG_ReadCrashDumpSummary(uint8_t* pBuffer, int* pSize);
