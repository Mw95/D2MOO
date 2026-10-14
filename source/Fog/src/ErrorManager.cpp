#include <Safesock.h>
#include <ErrorManager.h>
#include <Exceptions.h>
#include <LogManager.h>
#include <Mem/Mem.h>
#include <D2BitManip.h>
#include <System/System.h>
#include <Storm.h>

#include <intrin.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define ERRMGR_SEPARATOR "------------------------------------------------------"

// Fog.0x6FF76328
static char gszProgramName[MAX_PATH] = "Diablo II";
// Fog.0x6FFA0148
static char gszProgramVersion[MAX_PATH];
// Fog.0x6FFA010C
static D2SystemInfoStrc gtSystemInfo;
// Fog.0x6FFA024C
static CRITICAL_SECTION gtErrorManagerLock;
// Fog.0x6FF9FE24
static CRITICAL_SECTION gtErrorManagerLock2;
// Fog.0x6FFA0264
static D2ExceptionCallback gpfExceptionCallback;
// Fog.0x6FFA0268
static BOOL gbHandlingError;
// Fog.0x6FFA026C
static BOOL gbIsWindowsNT;
// Fog.0x6FFA0270
static BOOL gbErrorManagerInitialized;
// Fog.0x6FFA0274
static size_t gnSourceRootPathLength;
// Fog.0x6FF9FE40
static CONTEXT gtErrorContext;
// Fog.0x6FF7AEF8
// Read from the registry, unused
static DWORD gdwTraceUnfreedMemory;

// Fog.0x6FF762C8
static const char* gszErrorCategoryNames[NUM_ERRCATEGORIES] = {
	"No Error",
	"Unknown Error",
	"Out of Memory Error",
	"File Read Error",
	"File Write Error",
	"Assertion Failure",
	"Halt",
	"Warning",
	"Missing Dll",
	"Registry Error",
	"Deadlock",
};

const char* ERRMGR_GetProgramName()
{
	return gszProgramName;
}

D2ExceptionCallback ERRMGR_GetExceptionCallback()
{
	return gpfExceptionCallback;
}

void ERRMGR_SetHandlingError()
{
	gbHandlingError = TRUE;
}

// 1.10f: 0x6FF5DD90 (#10018)
// sprintf returning the destination buffer
const char* __cdecl FOG_csprintf(char* szDest, const char* szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);
	vsprintf(szDest, szFormat, args);
	va_end(args);
	return szDest;
}

// 1.10f: 0x6FF5F2B0 (#10231)
// Removes the root directory of the source tree from a source file path (such as __FILE__).
// The root directory length is deduced from the path of this file.
const char* __fastcall FOG_GetShortSourceFilePath(const char* szFilePath)
{
	if (!gnSourceRootPathLength)
	{
		const int nRootLength = (int)SStrLen(__FILE__) - (int)SStrLen("Fog\\src\\ErrorManager.cpp");
		gnSourceRootPathLength = nRootLength > 0 ? nRootLength : 0;
	}

	if (SStrLen(szFilePath) > gnSourceRootPathLength)
	{
		return szFilePath + gnSourceRootPathLength;
	}
	return szFilePath;
}

// 1.10f: 0x6FF5DDD0
static void ERRMGR_OutputDebugMessage(int nFlags, const char* szFormat, va_list args)
{
	char szMessage[0x1000];
	szMessage[0] = '\0';
	if (nFlags & DEBUGMSG_TIME)
	{
		SYSTEMTIME tTime;
		GetLocalTime(&tTime);
		_snprintf(szMessage, sizeof(szMessage), "%02d:%02d:%02d.%03d    ", tTime.wHour, tTime.wMinute, tTime.wSecond, tTime.wMilliseconds);
	}

	const size_t nPrefixLength = strlen(szMessage);
	_vsnprintf(&szMessage[nPrefixLength], sizeof(szMessage) - nPrefixLength, szFormat, args);
	szMessage[sizeof(szMessage) - 1] = '\0';

	if (!(nFlags & DEBUGMSG_NO_DEBUGGER))
	{
		OutputDebugStringA(szMessage);
	}

	if (nFlags & DEBUGMSG_LOG)
	{
		FOG_TraceFAppend("LOG", "%s", szMessage);
	}

	// Note: the original also calls GetKeyState(VK_CAPITAL) when flags 0x18 are set, and ignores the result
}

// 1.10f: 0x6FF5DDB0 (#10035)
void __cdecl FOG_10035(const char* szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);
	ERRMGR_OutputDebugMessage(0, szFormat, args);
	va_end(args);
}

// 1.10f: 0x6FF5DEE0 (#10036)
void __cdecl FOG_10036(int nFlags, const char* szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);
	ERRMGR_OutputDebugMessage(nFlags, szFormat, args);
	va_end(args);
}

// 1.10f: 0x6FF5DEC0 (#10037)
void __cdecl FOG_10037(const char* szFormat, ...)
{
	if (GetAsyncKeyState(VK_CAPITAL) & 1)
	{
		va_list args;
		va_start(args, szFormat);
		ERRMGR_OutputDebugMessage(0, szFormat, args);
		va_end(args);
	}
}

// 1.10f: 0x6FF5DF00 (#10038)
void __cdecl FOG_10038(const char* szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);
	ERRMGR_OutputDebugMessage(DEBUGMSG_LOG, szFormat, args);
	va_end(args);
}

// 1.10f: 0x6FF5DF20 (#10022)
void* __cdecl FOG_GetSystemInfo()
{
	return gtSystemInfo.bValid ? &gtSystemInfo : nullptr;
}

enum D2CPUVendor
{
	CPUVENDOR_UNKNOWN = 0,
	CPUVENDOR_INTEL = 1,
	CPUVENDOR_AMD = 2,
	CPUVENDOR_CYRIX = 3,
};

// Fog.0x6FF75FA8
static const char* gszCPUVendorNames[] = { "Unknown", "Intel", "AMD", "Cyrix" };

// Inlined
static D2CPUVendor ERRMGR_GetCPUVendor()
{
	int nRegisters[4];
	__cpuid(nRegisters, 0);

	// EBX, EDX, ECX
	char szVendor[16] = {};
	memcpy(&szVendor[0], &nRegisters[1], 4);
	memcpy(&szVendor[4], &nRegisters[3], 4);
	memcpy(&szVendor[8], &nRegisters[2], 4);

	if (!strcmp(szVendor, "GenuineIntel"))
	{
		return CPUVENDOR_INTEL;
	}
	if (!strcmp(szVendor, "AuthenticAMD"))
	{
		return CPUVENDOR_AMD;
	}
	if (!strcmp(szVendor, "CyrixInstead"))
	{
		return CPUVENDOR_CYRIX;
	}
	return CPUVENDOR_UNKNOWN;
}

// Inlined
static uint32_t ERRMGR_GetCPUSignature()
{
	int nRegisters[4];
	__cpuid(nRegisters, 1);
	return (uint32_t)nRegisters[0];
}

// 1.10f: 0x6FF5D1E0
static const char* __fastcall ERRMGR_GetCPUName(D2CPUVendor nVendor, uint32_t nType, uint32_t nFamily, uint32_t nModel, uint32_t nBrand)
{
	switch (nVendor)
	{
	case CPUVENDOR_INTEL:
		switch (nBrand)
		{
		case 1: return "Celeron";
		case 2: return "Pentium III";
		case 3: return "Pentium III Xeon";
		case 4: return "Pentium III";
		case 8: return "Pentium 4";
		case 14: return "Xeon";
		default: break;
		}

		if (nType == 0)
		{
			if (nFamily == 5)
			{
				return nModel < 4 ? "Pentium" : "Pentium MMX";
			}
			if (nFamily == 6)
			{
				if (nModel < 3) return "Pentium Pro";
				if (nModel < 5) return "Pentium II";
				if (nModel == 5) return "Pentium II or Celeron";
				if (nModel == 6) return "Celeron";
				if (nModel == 7) return "Pentium III";
				return "Pentium III (no brand)";
			}
			if (nFamily == 15)
			{
				return "Pentium 4 (no brand)";
			}
		}
		else if (nType == 1)
		{
			// OverDrive processors
			if (nFamily == 5)
			{
				if (nModel < 3) return "Pentium OD586";
				if (nModel == 3) return "Pentium OD486";
				return "Pentium MMX OD586";
			}
			if (nFamily == 6)
			{
				return "Pentium II OD";
			}
		}
		break;

	case CPUVENDOR_AMD:
		if (nFamily == 4)
		{
			return "Am486DX4 or Am5x86";
		}
		if (nFamily == 5)
		{
			if (nModel < 6) return "K5";
			if (nModel < 8) return "K6";
			if (nModel == 8) return "K6-II";
			return "K6-III";
		}
		if (nFamily == 6)
		{
			if (nModel < 3) return "Athlon";
			if (nModel == 3) return "Duron";
			if (nModel < 6) return "Athlon";
			if (nModel == 6) return "Athlon MP, XP, or Mobile";
			if (nModel == 7) return "Duron Mobile";
		}
		break;

	case CPUVENDOR_CYRIX:
		if (nType == 0)
		{
			if (nFamily == 4) return "MediaGX";
			if (nFamily == 5) return nModel < 4 ? "6x86" : "GXm";
			if (nFamily == 6) return "6x86MX";
		}
		break;

	default:
		break;
	}

	return "{Unknown}";
}

// 1.10f: 0x6FF5CED0 (#10190)
void __cdecl FOG_LogCPUInfo()
{
	if (gtSystemInfo.tSystemInfo.wProcessorLevel == 3)
	{
		FOG_Trace("Intel 386");
		return;
	}

	if (gtSystemInfo.tSystemInfo.wProcessorLevel == 4)
	{
		FOG_Trace("Intel 486");
		return;
	}

	const D2CPUVendor nVendor = ERRMGR_GetCPUVendor();
	const uint32_t nSignature = ERRMGR_GetCPUSignature();
	const uint32_t nStepping = nSignature & 0xF;
	const uint32_t nModel = (nSignature >> 4) & 0xF;
	const uint32_t nFamily = (nSignature >> 8) & 0xF;
	const uint32_t nType = (nSignature >> 12) & 3;

	// The brand index is only available on Pentium III (Coppermine) and later
	uint32_t nBrand = 0;
	if (nVendor == CPUVENDOR_INTEL && (nFamily >= 7 || (nFamily == 6 && nModel >= 8)))
	{
		int nRegisters[4];
		__cpuid(nRegisters, 1);
		nBrand = nRegisters[1] & 0xFF;
	}

	const char* szCPUName = ERRMGR_GetCPUName(nVendor, nType, nFamily, nModel, nBrand);
	FOG_Trace("Vendor:  %s", gszCPUVendorNames[nVendor]);
	FOG_Trace("Version: %s (Type %X, Family %X, Model %X, Stepping %X, Brand %X)", szCPUName, nType, nFamily, nModel, nStepping, nBrand);

	// Measure the time stamp counter frequency over (at least) 10 ms
	// Note: the original sets the thread priority to its current value, which has no effect
	const DWORD dwStartTicks = GetTickCount();
	LARGE_INTEGER nStartCounter;
	QueryPerformanceCounter(&nStartCounter);
	const uint64_t nStartCycles = __rdtsc();
	while (GetTickCount() - dwStartTicks < 10)
	{
		Sleep(0);
	}
	LARGE_INTEGER nEndCounter;
	QueryPerformanceCounter(&nEndCounter);
	const uint64_t nEndCycles = __rdtsc();

	LARGE_INTEGER nFrequency;
	QueryPerformanceFrequency(&nFrequency);

	// Note: the original divides by zero if the performance counter is not available
	const int64_t nElapsedCounter = nEndCounter.QuadPart - nStartCounter.QuadPart;
	const int64_t nCyclesPerSecond = nElapsedCounter ? (int64_t)(nEndCycles - nStartCycles) * nFrequency.QuadPart / nElapsedCounter : 0;
	FOG_Trace("Speed: Approx. %d MHz", (int)(nCyclesPerSecond / 1000000));
}

// 1.10f: 0x6FF5D5C0 (#10191)
BOOL __cdecl FOG_IsSlowCPU()
{
	if (gtSystemInfo.tSystemInfo.wProcessorLevel < 5)
	{
		return TRUE;
	}

	const D2CPUVendor nVendor = ERRMGR_GetCPUVendor();
	const uint32_t nSignature = ERRMGR_GetCPUSignature();
	const uint32_t nModel = (nSignature >> 4) & 0xF;
	const uint32_t nFamily = (nSignature >> 8) & 0xF;
	const uint32_t nType = (nSignature >> 12) & 3;

	switch (nVendor)
	{
	case CPUVENDOR_INTEL:
		// Pentium, Pentium MMX, Pentium Pro and their OverDrive versions
		if (nFamily == 5 && (nType == 0 || nType == 1))
		{
			return TRUE;
		}
		return nType == 0 && nFamily == 6 && nModel < 3;

	case CPUVENDOR_AMD:
		// Am486, K5 and K6
		return nFamily == 4 || (nFamily == 5 && nModel < 8);

	case CPUVENDOR_CYRIX:
		return TRUE;

	default:
		return FALSE;
	}
}

// 1.10f: 0x6FF5DF30
void ERRMGR_LogSystemInfo()
{
	FOG_Trace(ERRMGR_SEPARATOR);

	SYSTEMTIME tTime;
	GetLocalTime(&tTime);
	FOG_Trace("%04d-%02d-%02d %02d:%02d:%02d", tTime.wYear, tTime.wMonth, tTime.wDay, tTime.wHour, tTime.wMinute, tTime.wSecond);

	const char* szOSName = "unknown";
	switch (gtSystemInfo.nOSType)
	{
	case OSTYPE_WIN95: szOSName = "Windows 95"; break;
	case OSTYPE_WIN98: szOSName = "Windows 98"; break;
	case OSTYPE_WINME: szOSName = "Windows ME"; break;
	case OSTYPE_WINNT: szOSName = "Windows NT"; break;
	case OSTYPE_WIN2000: szOSName = "Windows 2000"; break;
	case OSTYPE_WINXP: szOSName = "Windows XP"; break;
	case OSTYPE_WINDOTNET: szOSName = "Windows .Net"; break;
	case OSTYPE_MACOS: szOSName = "MacOS"; break;
	case OSTYPE_MACOSX: szOSName = "MacOS X"; break;
	default: break;
	}
	FOG_Trace("%s running under %s (Version %.3f)", gszProgramName, szOSName, (double)gtSystemInfo.fOSVersion);

	FOG_LogCPUInfo();

	FOG_Trace("Total Physical Memory: %.2fMB", (double)gtSystemInfo.nTotalPhysicalMemory * (1.0 / (1024.0 * 1024.0)));

	char szApplicationPath[MAX_PATH];
	if (LOG_GetModuleDirectory(szApplicationPath, sizeof(szApplicationPath)))
	{
		FOG_Trace("Application Path: %s", szApplicationPath);
	}

	FOG_Trace("Local IP: %s", FOG_GetHostIPAddress());

	char szComputerName[64];
	DWORD nComputerNameSize = sizeof(szComputerName);
	if (!GetComputerNameA(szComputerName, &nComputerNameSize))
	{
		szComputerName[0] = '\0';
	}
	FOG_Trace("Computer name: %s", szComputerName);
	FOG_Trace(ERRMGR_SEPARATOR);
	FOG_Trace("");
}

// 1.10f: Inlined in 0x6FF5E1B0
static void ERRMGR_DetectOS()
{
	OSVERSIONINFOA tVersionInfo{};
	tVersionInfo.dwOSVersionInfoSize = sizeof(tVersionInfo);
	if (!GetVersionExA(&tVersionInfo))
	{
		return;
	}

	// Note: the minor version is scaled down to [0, 1] then divided by 100. Windows 98 (4.10) is reported as 4.01.
	float fMinorVersion = (float)tVersionInfo.dwMinorVersion;
	while (fMinorVersion > 1.0f)
	{
		fMinorVersion *= 0.1f;
	}
	gtSystemInfo.fOSVersion = fMinorVersion * 0.01f + (float)tVersionInfo.dwMajorVersion;

	switch (tVersionInfo.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		gtSystemInfo.nOSType = OSTYPE_WIN95;
		if (tVersionInfo.dwMinorVersion >= 90)
		{
			gtSystemInfo.nOSType = OSTYPE_WINME;
		}
		else if (tVersionInfo.dwMinorVersion >= 10)
		{
			gtSystemInfo.nOSType = OSTYPE_WIN98;
		}
		break;

	case VER_PLATFORM_WIN32_NT:
		gtSystemInfo.nOSType = OSTYPE_WINNT;
		if (tVersionInfo.dwMajorVersion >= 5)
		{
			if (tVersionInfo.dwMinorVersion >= 2)
			{
				gtSystemInfo.nOSType = OSTYPE_WINDOTNET;
			}
			else if (tVersionInfo.dwMinorVersion == 1)
			{
				gtSystemInfo.nOSType = OSTYPE_WINXP;
			}
			else
			{
				gtSystemInfo.nOSType = OSTYPE_WIN2000;
			}
		}
		break;

	default:
		gtSystemInfo.nOSType = OSTYPE_UNKNOWN;
		break;
	}
}

// 1.10f: 0x6FF5E450
static void __cdecl ERRMGR_Shutdown()
{
	if (!gbErrorManagerInitialized)
	{
		return;
	}

	FOG_AsyncDataDestroy();
	FOG_DestroyMemoryPoolSystem(nullptr);
	gpfExceptionCallback = nullptr;
	EXCEPTION_UnloadImageHlp();
	FOG_FlushLogs();
	LOG_Shutdown();
	gbErrorManagerInitialized = FALSE;
	DeleteCriticalSection(&gtErrorManagerLock);
	DeleteCriticalSection(&gtErrorManagerLock2);
}

// 1.10f: 0x6FF5E1B0 (#10019)
void __fastcall FOG_InitErrorMgr(const char* szProgramName, D2ExceptionCallback pExceptionCallback, const char* szVersion, BOOL bLogToFile)
{
	SStrCopy(gszProgramName, szProgramName, sizeof(gszProgramName));
	if (szVersion)
	{
		SStrCopy(gszProgramVersion, szVersion, sizeof(gszProgramVersion));
	}

	if (gbErrorManagerInitialized)
	{
		if (bLogToFile)
		{
			ERRMGR_LogSystemInfo();
		}
		return;
	}

	gbIsWindowsNT = FOG_IsWindowsNT();
	InitializeCriticalSection(&gtErrorManagerLock);
	InitializeCriticalSection(&gtErrorManagerLock2);
	gbErrorManagerInitialized = TRUE;

	SYSTEM_InitializeSyncTime();

	DWORD dwTraceUnfreedMemory = 0;
	SRegLoadValue("Diablo II", "TraceUnfreedMemory", 0, &dwTraceUnfreedMemory);
	gdwTraceUnfreedMemory = dwTraceUnfreedMemory;

	FOG_CreateNewPoolSystem(nullptr, "Global Pool System", 0x40000, 0x8000);
	SetUnhandledExceptionFilter(FOG_UnhandledExceptionFilter);

	SYSTEM_InitializePerformanceCounters();

	for (int i = 0; i < 32; ++i)
	{
		if (gdwBitMasks[i] != (1u << i))
		{
			WSACleanup();
			FOG_10028(ERRCATEGORY_ASSERT, __FILE__, __LINE__, "gdwBitMasks[i] == (DWORD)(1 << i)");
			FOG_FlushLogs();
			exit(-1);
		}
		if (gdwInvBitMasks[i] != ~(1u << i))
		{
			WSACleanup();
			FOG_10028(ERRCATEGORY_ASSERT, __FILE__, __LINE__, "gdwInvBitMasks[i] == ~(DWORD)(1 << i)");
			FOG_FlushLogs();
			exit(-1);
		}
	}

	ERRMGR_DetectOS();

	MEMORYSTATUS tMemoryStatus;
	GlobalMemoryStatus(&tMemoryStatus);
	gtSystemInfo.nTotalPhysicalMemory = tMemoryStatus.dwTotalPhys;
	GetSystemInfo(&gtSystemInfo.tSystemInfo);
	gtSystemInfo.bValid = TRUE;

	LOG_Initialize();
	if (bLogToFile)
	{
		ERRMGR_LogSystemInfo();
	}

	atexit(ERRMGR_Shutdown);
	gpfExceptionCallback = pExceptionCallback;
	EXCEPTION_LoadImageHlp();
}

// 1.10f: 0x6FF5E440 (#10020)
void __cdecl FOG_10020()
{
	SetUnhandledExceptionFilter(FOG_UnhandledExceptionFilter);
}

// 1.10f: 0x6FF5E670
static void __fastcall ERRMGR_AppendLine(void* pContext, const char* szLine)
{
	char* szText = (char*)pContext;
	SStrNCat(szText, szLine, 0x7FFFFFFF);
	SStrNCat(szText, "\r\n", 0x7FFFFFFF);
}

// 1.10f: 0x6FF5E6A0
void __fastcall ERRMGR_TraceLine(void* pContext, const char* szLine)
{
	D2_MAYBE_UNUSED(pContext);
	FOG_TraceF("", "%s", szLine);
}

// 1.10f: 0x6FF5E4A0 (#10226)
void __fastcall FOG_PrintErrorHeader(void* pContext, D2ErrorHeaderPrinter pPrinter)
{
	if (!pPrinter)
	{
		pPrinter = ERRMGR_AppendLine;
	}

	SYSTEMTIME tTime;
	GetLocalTime(&tTime);

	char szUserName[64];
	DWORD nUserNameSize = sizeof(szUserName);
	if (!GetUserNameA(szUserName, &nUserNameSize))
	{
		szUserName[0] = '\0';
	}

	char szComputerName[64];
	DWORD nComputerNameSize = sizeof(szComputerName);
	if (!GetComputerNameA(szComputerName, &nComputerNameSize))
	{
		szComputerName[0] = '\0';
	}

	char szProgram[MAX_PATH];
	if (gszProgramVersion[0])
	{
		SStrPrintf(szProgram, sizeof(szProgram), (char*)"%s %s", gszProgramName, gszProgramVersion);
	}
	else
	{
		SStrCopy(szProgram, gszProgramName, sizeof(szProgram));
	}

	char szLine[512];
	SStrPrintf(szLine, sizeof(szLine), (char*)"PROGRAM:       %s", szProgram);
	pPrinter(pContext, szLine);
	SStrPrintf(szLine, sizeof(szLine), (char*)"COMPUTER NAME: %s", szComputerName);
	pPrinter(pContext, szLine);
	SStrPrintf(szLine, sizeof(szLine), (char*)"USER NAME:     %s", szUserName);
	pPrinter(pContext, szLine);
	SStrPrintf(szLine, sizeof(szLine), (char*)"TIME:          %04u-%02u-%02u %02u:%02u:%02u.%03u",
		tTime.wYear, tTime.wMonth, tTime.wDay, tTime.wHour, tTime.wMinute, tTime.wSecond, tTime.wMilliseconds);
	pPrinter(pContext, szLine);
	SStrPrintf(szLine, sizeof(szLine), (char*)"");
	pPrinter(pContext, szLine);
}

// 1.10f: 0x6FF5EE20
// Returns TRUE if an error is already being handled
static BOOL __fastcall ERRMGR_CheckErrorDuringErrorHandling(const char* szFile, int nLine, const char* szFormat)
{
	if (!gbHandlingError)
	{
		return FALSE;
	}

	FOG_TraceF("", "\n***** ENCOUNTERED ERROR DURING ERROR HANDLING!!!\n%s,%d\n%s\n*****", FOG_GetShortSourceFilePath(szFile), nLine, szFormat);
	return TRUE;
}

// 1.10f: 0x6FF5EEA0
// Logs the error and displays it in a message box
static void __fastcall ERRMGR_DisplayErrorMessage(int nCategory, const char* szFile, int nLine, const char* szFormat, va_list args)
{
	FOG_TraceF("", "");
	FOG_TraceF("", "");
	FOG_TraceF("", ERRMGR_SEPARATOR);
	FOG_PrintErrorHeader(nullptr, ERRMGR_TraceLine);

	if (szFile)
	{
		char szLocation[0x1000];
		SStrPrintf(szLocation, sizeof(szLocation), (char*)"--------  FILE: %s    LINE: %d  --------\n\n", FOG_GetShortSourceFilePath(szFile), nLine);
		LOG_TraceFNoNewLine("", "%s", szLocation);
	}

	if (!szFormat)
	{
		WSACleanup();
		FOG_10028(ERRCATEGORY_ASSERT, __FILE__, __LINE__, "szFormat != NULL");
		FOG_FlushLogs();
		exit(-1);
	}

	char szExpression[0x1000];
	_vsnprintf(szExpression, sizeof(szExpression), szFormat, args);
	szExpression[sizeof(szExpression) - 1] = '\0';

	// Note: the original does not check the category bounds
	const char* szCategoryName = (nCategory >= 0 && nCategory < NUM_ERRCATEGORIES) ? gszErrorCategoryNames[nCategory] : gszErrorCategoryNames[ERRCATEGORY_UNKNOWN];

	char szMessage[0x1000];
	if (szFile)
	{
		SStrPrintf(szMessage, sizeof(szMessage), (char*)"%s\nLocation : %s, line #%d\nExpression : %s", szCategoryName, FOG_GetShortSourceFilePath(szFile), nLine, szExpression);
	}
	else
	{
		SStrCopy(szMessage, szExpression, sizeof(szMessage));
	}

	char szCaption[0x100];
	SStrPrintf(szCaption, sizeof(szCaption), (char*)"%s Error", gszProgramName);

	char szBoxMessage[0x1000];
	SStrCopy(szBoxMessage, szMessage, sizeof(szBoxMessage));

	// Note: the original appends the new line without checking the buffer size
	SStrNCat(szMessage, "\n", sizeof(szMessage));
	FOG_TraceFAppend("", "%s", szMessage);
	FOG_FlushLogs();

	MessageBoxA(nullptr, szBoxMessage, szCaption, MB_ICONEXCLAMATION);
}

// 1.10f: 0x6FF5F100 (#10028)
// Logs and displays the error, then dumps the stack of the faulty thread.
// For ERRCATEGORY_DEADLOCK, szFile is the handle of the deadlocked thread.
void __cdecl FOG_10028(int nCategory, const char* szFile, int nLine, const char* szFormat, ...)
{
	HANDLE hThread = nullptr;
	if (nCategory == ERRCATEGORY_DEADLOCK)
	{
		hThread = (HANDLE)szFile;
		szFile = __FILE__;
	}

	if (ERRMGR_CheckErrorDuringErrorHandling(szFile, nLine, szFormat))
	{
		return;
	}

	gbHandlingError = TRUE;

	if (!szFormat)
	{
		szFormat = "<no reason given>";
	}

	va_list args;
	va_start(args, szFormat);
	ERRMGR_DisplayErrorMessage(nCategory, szFile, nLine, szFormat, args);
	va_end(args);

	memset(&gtErrorContext, 0, sizeof(gtErrorContext));
	gtErrorContext.ContextFlags = CONTEXT_FULL;
	if (hThread)
	{
		GetThreadContext(hThread, &gtErrorContext);
	}
	else
	{
		// The original only captures EIP, ESP and EBP
		RtlCaptureContext(&gtErrorContext);
		hThread = GetCurrentThread();
	}

	if (nCategory == ERRCATEGORY_ASSERT || nCategory == ERRCATEGORY_HALT || nCategory == ERRCATEGORY_WARNING
		|| nCategory == ERRCATEGORY_DEADLOCK || nCategory == ERRCATEGORY_OUT_OF_MEMORY)
	{
		void* pCode = (void*)gtErrorContext.Eip;
		void* pStack = (void*)gtErrorContext.Esp;
		FOG_TraceF("", "Stack bytes:");
		FOG_TraceMemory("", "", pStack, 0x1000, FALSE, TRUE, FALSE);
		FOG_TraceF("", "Code bytes:");
		FOG_TraceMemory("", "", pCode, 0x20, FALSE, TRUE, FALSE);
		FOG_FlushLogs();
		EXCEPTION_StackCrawl(hThread, &gtErrorContext);
	}

	if (gpfExceptionCallback)
	{
		gpfExceptionCallback();
	}

	FOG_TraceFAppend("", "%s", "---finished error callback---\n");
	FOG_FlushLogs();

	// Fatal errors keep the flag set, any error happening while exiting is only logged
	if (nCategory != ERRCATEGORY_ASSERT && nCategory != ERRCATEGORY_HALT && nCategory != ERRCATEGORY_OUT_OF_MEMORY)
	{
		gbHandlingError = FALSE;
	}
}

// 1.10f: 0x6FF5ED30 (#10023)
void __cdecl FOG_DisplayAssert(const char* szMsg, const char* szFile, int nLine)
{
	WSACleanup();
	// Note: the message is used as the format string
	FOG_10028(ERRCATEGORY_ASSERT, szFile, nLine, szMsg);
	FOG_FlushLogs();
}

// 1.10f: 0x6FF5ED60 (#10024)
void __cdecl FOG_DisplayHalt(const char* szMsg, const char* szFile, int nLine)
{
	WSACleanup();
	FOG_10028(ERRCATEGORY_HALT, szFile, nLine, szMsg);
	FOG_FlushLogs();
}

// 1.10f: 0x6FF5ED90 (#10025)
void __cdecl FOG_DisplayWarning(const char* szMsg, const char* szFile, int nLine)
{
	WSACleanup();
	FOG_10028(ERRCATEGORY_WARNING, szFile, nLine, szMsg);
	FOG_FlushLogs();
}

// 1.10f: 0x6FF5EDC0 (#10027)
void __cdecl FOG_DisplayDeadlock(HANDLE hThread, int nTicks)
{
	WSACleanup();
	FOG_10028(ERRCATEGORY_DEADLOCK, (const char*)hThread, __LINE__, "Deadlocked in thread %X for %d ticks", hThread, nTicks);
	FOG_FlushLogs();
}

// 1.10f: 0x6FF5EDF0 (#10026)
void __cdecl FOG_DisplayError(int nCategory, const char* szMsg, const char* szFile, int nLine)
{
	WSACleanup();
	FOG_10028(nCategory, szFile, nLine, szMsg);
	FOG_FlushLogs();
}

// 1.10f: 0x6FF5F2A0 (#10039)
BOOL __cdecl FOG_IsHandlingError()
{
	return gbHandlingError;
}
