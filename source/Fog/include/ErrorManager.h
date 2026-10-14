#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

enum D2ErrorCategory
{
	ERRCATEGORY_NONE = 0,
	ERRCATEGORY_UNKNOWN = 1,
	ERRCATEGORY_OUT_OF_MEMORY = 2,
	ERRCATEGORY_FILE_READ = 3,
	ERRCATEGORY_FILE_WRITE = 4,
	ERRCATEGORY_ASSERT = 5,
	ERRCATEGORY_HALT = 6,
	ERRCATEGORY_WARNING = 7,
	ERRCATEGORY_MISSING_DLL = 8,
	ERRCATEGORY_REGISTRY = 9,
	ERRCATEGORY_DEADLOCK = 10,	// The file parameter of FOG_10028 is the handle of the deadlocked thread
	NUM_ERRCATEGORIES
};

enum D2OSType
{
	OSTYPE_UNKNOWN = 0,
	OSTYPE_WIN95 = 1,
	OSTYPE_WIN98 = 2,
	OSTYPE_WINME = 3,
	OSTYPE_WINNT = 4,
	OSTYPE_WIN2000 = 5,
	OSTYPE_WINXP = 6,
	OSTYPE_WINDOTNET = 7,
	OSTYPE_MACOS = 8,
	OSTYPE_MACOSX = 9,
};

// Flags of FOG_10036
enum D2DebugMessageFlags
{
	DEBUGMSG_LOG = 0x1,				// Also append the message to the "LOG" log file
	DEBUGMSG_NO_DEBUGGER = 0x2,		// Do not send the message to OutputDebugString
	DEBUGMSG_TIME = 0x4,			// Prefix the message with the time
};

#pragma pack(push, 1)
// Returned by FOG_GetSystemInfo
struct D2SystemInfoStrc					// sizeof 0x38
{
	BOOL bValid;						// 0x00
	int32_t nOSType;					// 0x04 D2OSType
	float fOSVersion;					// 0x08
	uint32_t nTotalPhysicalMemory;		// 0x0C
	uint32_t unk0x10;					// 0x10
	SYSTEM_INFO tSystemInfo;			// 0x14
};
#pragma pack(pop)

// Receives the lines printed by FOG_10226
typedef void(__fastcall* D2ErrorHeaderPrinter)(void* pContext, const char* szLine);

// Internal

// Name of the program as given to FOG_InitErrorMgr
const char* ERRMGR_GetProgramName();
// Callback given to FOG_InitErrorMgr, may be nullptr
D2ExceptionCallback ERRMGR_GetExceptionCallback();
// Sets the flag returned by FOG_IsHandlingError
void ERRMGR_SetHandlingError();
// 1.10f: 0x6FF5E6A0
// D2ErrorHeaderPrinter writing the lines to the default log file
void __fastcall ERRMGR_TraceLine(void* pContext, const char* szLine);
// 1.10f: 0x6FF5DF30
// Logs the system information (OS, CPU, memory, ...)
void ERRMGR_LogSystemInfo();

// Exported

// 1.10f: 0x6FF5E440 (#10020)
// Installs FOG_10052 as the unhandled exception filter
FOG_DLL_DECL void __cdecl FOG_10020();
// 1.10f: 0x6FF5EDC0 (#10027)
FOG_DLL_DECL void __cdecl FOG_DisplayDeadlock(HANDLE hThread, int nTicks);
// 1.10f: 0x6FF5DDB0 (#10035)
// Sends the message to the debugger
FOG_DLL_DECL void __cdecl FOG_10035(const char* szFormat, ...);
// 1.10f: 0x6FF5DEE0 (#10036)
// nFlags is a combination of D2DebugMessageFlags
FOG_DLL_DECL void __cdecl FOG_10036(int nFlags, const char* szFormat, ...);
// 1.10f: 0x6FF5DEC0 (#10037)
// Sends the message to the debugger if caps lock is toggled on
FOG_DLL_DECL void __cdecl FOG_10037(const char* szFormat, ...);
// 1.10f: 0x6FF5DF00 (#10038)
// Sends the message to the debugger and appends it to the "LOG" log file
FOG_DLL_DECL void __cdecl FOG_10038(const char* szFormat, ...);
// 1.10f: 0x6FF5CED0 (#10190)
// Logs the CPU vendor, version and speed
FOG_DLL_DECL void __cdecl FOG_LogCPUInfo();
// 1.10f: 0x6FF5D5C0 (#10191)
// Returns TRUE for CPUs older than the Pentium II / K6-2
FOG_DLL_DECL BOOL __cdecl FOG_IsSlowCPU();
// 1.10f: 0x6FF5E4A0 (#10226)
// Prints the program, computer, user and time lines. A null pPrinter appends the lines to the string pContext.
FOG_DLL_DECL void __fastcall FOG_PrintErrorHeader(void* pContext, D2ErrorHeaderPrinter pPrinter);
