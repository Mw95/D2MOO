#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

// Messages are queued and written to the log files by a dedicated thread.
// Log files are named "<prefix><name><YYMMDD>.txt", see FOG_SetLogPrefix.

// 1.10f: 0x6FF61CB0
void LOG_Initialize();
// 1.10f: 0x6FF61D00
void LOG_Shutdown();
// 1.10f: 0x6FF62130
// Same as FOG_TraceF but without adding a new line
void __cdecl LOG_TraceFNoNewLine(const char* szFileSubName, const char* szFormat, ...);
// 1.10f: 0x6FF5FA60
// Directory of the executable, without the trailing separator
BOOL __fastcall LOG_GetModuleDirectory(char* szPath, size_t nSize);

// 1.10f: 0x6FF62460 (#10040)
// Waits up to a second for the queued messages to be written, then closes the log files
FOG_DLL_DECL void __fastcall FOG_FlushLogs();
// 1.10f: 0x6FF61E00 (#10234)
FOG_DLL_DECL int __fastcall FOG_GetLogFileSize(const char* szFileSubName);
// 1.10f: 0x6FF61F20 (#10235)
// Returns a zero terminated buffer allocated with FOG_Alloc containing the bytes [nStart, nEnd] of the log file
FOG_DLL_DECL char* __fastcall FOG_ReadLogFile(const char* szFileSubName, int nStart, int nEnd);
// 1.10f: 0x6FF621C0 (#10238)
// Same as FOG_TraceF but without date nor new line
FOG_DLL_DECL void __cdecl FOG_TraceFAppend(const char* szFileSubName, const char* szFormat, ...);
