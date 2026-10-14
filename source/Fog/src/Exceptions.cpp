#include <Exceptions.h>
#include <ErrorManager.h>
#include <LogManager.h>
#include <Storm.h>

#include <imagehlp.h>
#include <tlhelp32.h>
#include <psapi.h>
#ifdef _MSC_VER
#include <eh.h>
#endif

#include <cstddef>
#include <cstdio>
#include <cstring>

#define EXCEPTION_SYMBOL_NAME_LENGTH 0x100
#define EXCEPTION_SYMBOL_PATH_SIZE 0x1000
#define EXCEPTION_MAX_PSAPI_MODULES 0x100

// Loaded module, kept in a list sorted by base address
struct D2ExceptionModuleStrc			// sizeof 0x210
{
	char szPath[MAX_PATH];				// 0x000
	char szName[0x100];					// 0x104
	uint32_t nBase;						// 0x204
	uint32_t nSize;						// 0x208
	D2ExceptionModuleStrc* pNext;		// 0x20C
};

// IMAGEHLP_SYMBOL followed by the storage for its name
struct D2ExceptionSymbolStrc
{
	IMAGEHLP_SYMBOL tSymbol;
	char szNameBuffer[EXCEPTION_SYMBOL_NAME_LENGTH];
};

using SymCleanupFunc = BOOL(WINAPI*)(HANDLE hProcess);
using SymGetLineFromAddrFunc = BOOL(WINAPI*)(HANDLE hProcess, DWORD dwAddr, PDWORD pdwDisplacement, PIMAGEHLP_LINE Line);
using SymGetModuleInfoFunc = BOOL(WINAPI*)(HANDLE hProcess, DWORD dwAddr, PIMAGEHLP_MODULE ModuleInfo);
using SymGetOptionsFunc = DWORD(WINAPI*)();
using SymGetSymFromAddrFunc = BOOL(WINAPI*)(HANDLE hProcess, DWORD dwAddr, PDWORD pdwDisplacement, PIMAGEHLP_SYMBOL Symbol);
using SymInitializeFunc = BOOL(WINAPI*)(HANDLE hProcess, PCSTR UserSearchPath, BOOL fInvadeProcess);
using SymLoadModuleFunc = DWORD(WINAPI*)(HANDLE hProcess, HANDLE hFile, PCSTR ImageName, PCSTR ModuleName, DWORD BaseOfDll, DWORD SizeOfDll);
using SymSetOptionsFunc = DWORD(WINAPI*)(DWORD SymOptions);
using SymUnloadModuleFunc = BOOL(WINAPI*)(HANDLE hProcess, DWORD BaseOfDll);
using StackWalkFunc = BOOL(WINAPI*)(DWORD MachineType, HANDLE hProcess, HANDLE hThread, LPSTACKFRAME StackFrame, PVOID ContextRecord,
	PREAD_PROCESS_MEMORY_ROUTINE ReadMemoryRoutine, PFUNCTION_TABLE_ACCESS_ROUTINE FunctionTableAccessRoutine,
	PGET_MODULE_BASE_ROUTINE GetModuleBaseRoutine, PTRANSLATE_ADDRESS_ROUTINE TranslateAddress);
using UnDecorateSymbolNameFunc = DWORD(WINAPI*)(PCSTR DecoratedName, PSTR UnDecoratedName, DWORD UndecoratedLength, DWORD Flags);
using SplitSymbolsFunc = BOOL(WINAPI*)(PSTR ImageName, PSTR SymbolsPath, PSTR SymbolFilePath, DWORD Flags);

using CreateToolhelp32SnapshotFunc = HANDLE(WINAPI*)(DWORD dwFlags, DWORD th32ProcessID);
using Module32FirstFunc = BOOL(WINAPI*)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
using Module32NextFunc = BOOL(WINAPI*)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);

using EnumProcessModulesFunc = BOOL(WINAPI*)(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded);
using GetModuleFileNameExAFunc = DWORD(WINAPI*)(HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize);
using GetModuleBaseNameAFunc = DWORD(WINAPI*)(HANDLE hProcess, HMODULE hModule, LPSTR lpBaseName, DWORD nSize);
using GetModuleInformationFunc = BOOL(WINAPI*)(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb);

// Fog.0x6FFA1278
static HMODULE ghImageHlp;
// Fog.0x6FFA127C
static int gnQuickStackWalkDepth;
// Fog.0x6FFA1280
// Never set, disables the symbols loading logs
static BOOL gbQuietSymbolsLoading;
// Fog.0x6FFA1284
static int gnSymbolsRefCount;
// Fog.0x6FFA1288
static CRITICAL_SECTION gtSymbolsLock;
// Fog.0x6FFA12A0
static SymCleanupFunc gpfSymCleanup;
// Fog.0x6FFA12A4
static PFUNCTION_TABLE_ACCESS_ROUTINE gpfSymFunctionTableAccess;
// Fog.0x6FFA12A8
static SymGetLineFromAddrFunc gpfSymGetLineFromAddr;
// Fog.0x6FFA12AC
static PGET_MODULE_BASE_ROUTINE gpfSymGetModuleBase;
// Fog.0x6FFA12B0
static SymGetModuleInfoFunc gpfSymGetModuleInfo;
// Fog.0x6FFA12B4
static SymGetOptionsFunc gpfSymGetOptions;
// Fog.0x6FFA12B8
static SymGetSymFromAddrFunc gpfSymGetSymFromAddr;
// Fog.0x6FFA12BC
static SymInitializeFunc gpfSymInitialize;
// Fog.0x6FFA12C0
static SymLoadModuleFunc gpfSymLoadModule;
// Fog.0x6FFA12C4
static SymUnloadModuleFunc gpfSymUnloadModule;
// Fog.0x6FFA12C8
static SymSetOptionsFunc gpfSymSetOptions;
// Fog.0x6FFA12CC
static StackWalkFunc gpfStackWalk;
// Fog.0x6FFA12D0
static UnDecorateSymbolNameFunc gpfUnDecorateSymbolName;
// Fog.0x6FFA12D4
static SplitSymbolsFunc gpfSplitSymbols;
// Fog.0x6FFA12D8
static BOOL gbImageHlpLoaded;
// Fog.0x6FFA12DC
static HANDLE ghStackWalkThread;
// Fog.0x6FFA12E0
static HANDLE ghStackWalkRequestEvent;
// Fog.0x6FFA12E4
static HANDLE ghStackWalkDoneEvent;
// Fog.0x6FFA12E8
static HANDLE ghThreadToStackWalk;
// Fog.0x6FFA0278
static char gszQuickStackWalkSymbolPath[EXCEPTION_SYMBOL_PATH_SIZE];
// Fog.0x6FF76534
static volatile LONG gnUnhandledExceptionCounter = -1;

// Inlined
static BOOL EXCEPTION_IsStackDumpDisabled()
{
	DWORD dwNoStackDump = 0;
	SRegLoadValue("Diablo II", "NoStackDump", 0, &dwNoStackDump);
	return dwNoStackDump != 0;
}

// Inlined
static const D2ExceptionModuleStrc* EXCEPTION_FindModule(const D2ExceptionModuleStrc* pModules, uint32_t nAddress)
{
	for (const D2ExceptionModuleStrc* pModule = pModules; pModule; pModule = pModule->pNext)
	{
		if (nAddress >= pModule->nBase && nAddress < pModule->nBase + pModule->nSize)
		{
			return pModule;
		}
	}
	return nullptr;
}

// Inlined
static void EXCEPTION_FreeModules(D2ExceptionModuleStrc* pModules)
{
	while (pModules)
	{
		D2ExceptionModuleStrc* pNext = pModules->pNext;
		FOG_Free(pModules, __FILE__, __LINE__, 0);
		pModules = pNext;
	}
}

// Inlined
static D2ExceptionModuleStrc* EXCEPTION_AddModule(D2ExceptionModuleStrc* pModules, const char* szPath, const char* szName, uint32_t nBase, uint32_t nSize)
{
	D2ExceptionModuleStrc* pModule = (D2ExceptionModuleStrc*)FOG_Alloc(sizeof(D2ExceptionModuleStrc), __FILE__, __LINE__, 0);
	memset(pModule, 0, sizeof(*pModule));
	SStrCopy(pModule->szPath, szPath, sizeof(pModule->szPath));
	SStrCopy(pModule->szName, szName, sizeof(pModule->szName));
	pModule->nBase = nBase;
	pModule->nSize = nSize;

	// Keep the list sorted by base address
	D2ExceptionModuleStrc** ppInsert = &pModules;
	while (*ppInsert && (*ppInsert)->nBase < nBase)
	{
		ppInsert = &(*ppInsert)->pNext;
	}
	pModule->pNext = *ppInsert;
	*ppInsert = pModule;
	return pModules;
}

// Inlined
// Returns the file name of the module containing the address, and the 1-based index of its section with the offset in this section
static void EXCEPTION_GetLogicalAddress(const void* pAddress, char* szModule, size_t nModuleSize, uint32_t* pSectionIndex, uint32_t* pOffset)
{
	*pSectionIndex = 0;
	*pOffset = 0;
	SStrCopy(szModule, "*unknown*", nModuleSize);

	MEMORY_BASIC_INFORMATION tMemoryInfo;
	if (!VirtualQuery(pAddress, &tMemoryInfo, sizeof(tMemoryInfo)))
	{
		return;
	}

	HMODULE hModule = (HMODULE)tMemoryInfo.AllocationBase;
	if (!hModule)
	{
		hModule = GetModuleHandleA(nullptr);
	}

	if (!GetModuleFileNameA(hModule, szModule, nModuleSize))
	{
		SStrCopy(szModule, "*unknown*", nModuleSize);
		return;
	}

	const IMAGE_DOS_HEADER* pDosHeader = (const IMAGE_DOS_HEADER*)hModule;
	if (!pDosHeader || pDosHeader->e_magic != IMAGE_DOS_SIGNATURE || !pDosHeader->e_lfanew)
	{
		return;
	}

	const IMAGE_NT_HEADERS* pNtHeaders = (const IMAGE_NT_HEADERS*)((const uint8_t*)hModule + pDosHeader->e_lfanew);
	if (pNtHeaders->Signature != IMAGE_NT_SIGNATURE)
	{
		return;
	}

	const uint32_t nRVA = (uint32_t)((const uint8_t*)pAddress - (const uint8_t*)hModule);
	const IMAGE_SECTION_HEADER* pSection = IMAGE_FIRST_SECTION(pNtHeaders);
	for (uint32_t i = 0; i < pNtHeaders->FileHeader.NumberOfSections; ++i, ++pSection)
	{
		const uint32_t nSectionSize = pSection->Misc.VirtualSize > pSection->SizeOfRawData ? pSection->Misc.VirtualSize : pSection->SizeOfRawData;
		if (nRVA >= pSection->VirtualAddress && nRVA <= pSection->VirtualAddress + nSectionSize)
		{
			*pSectionIndex = i + 1;
			*pOffset = nRVA - pSection->VirtualAddress;
			return;
		}
	}
}

// Inlined
// Gets the symbol name and the source line of the address. Returns FALSE if the symbol was not found.
static BOOL EXCEPTION_GetSymbol(HANDLE hProcess, uint32_t nAddress, D2ExceptionSymbolStrc* pSymbol, DWORD* pDisplacement, IMAGEHLP_LINE* pLine)
{
	memset(pLine, 0, sizeof(*pLine));
	*pDisplacement = 0;
	if (!gpfSymGetSymFromAddr(hProcess, nAddress, pDisplacement, &pSymbol->tSymbol))
	{
		return FALSE;
	}

	if (gpfSymGetLineFromAddr)
	{
		pLine->SizeOfStruct = sizeof(*pLine);
		DWORD dwLineDisplacement = *pDisplacement;
		// The line information may not start at the exact address, search backwards
		for (int i = 0; i < 100; ++i)
		{
			if (gpfSymGetLineFromAddr(hProcess, nAddress - i, &dwLineDisplacement, pLine))
			{
				return TRUE;
			}
		}
	}

	pLine->LineNumber = 0;
	return TRUE;
}

// Inlined
static void EXCEPTION_InitSymbol(D2ExceptionSymbolStrc* pSymbol)
{
	memset(pSymbol, 0, sizeof(*pSymbol));
	pSymbol->tSymbol.SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
	pSymbol->tSymbol.MaxNameLength = EXCEPTION_SYMBOL_NAME_LENGTH;
}

// Inlined
static void EXCEPTION_InitStackFrame(STACKFRAME* pStackFrame, const CONTEXT* pContext)
{
	memset(pStackFrame, 0, sizeof(*pStackFrame));
	pStackFrame->AddrPC.Offset = pContext->Eip;
	pStackFrame->AddrPC.Mode = AddrModeFlat;
	pStackFrame->AddrStack.Offset = pContext->Esp;
	pStackFrame->AddrStack.Mode = AddrModeFlat;
	pStackFrame->AddrFrame.Offset = pContext->Ebp;
	pStackFrame->AddrFrame.Mode = AddrModeFlat;
}

// Inlined
static void EXCEPTION_AppendSymbolPath(char* szPath, const char* szDirectory)
{
	SStrNCat(szPath, szDirectory, EXCEPTION_SYMBOL_PATH_SIZE);
	SStrNCat(szPath, ";", EXCEPTION_SYMBOL_PATH_SIZE);
}

// 1.10f: 0x6FF606D0
// Builds the symbols search path: executable directory, current directory, _NT_SYMBOL_PATH, _NT_ALTERNATE_SYMBOL_PATH and SYSTEMROOT.
// szPath must be EXCEPTION_SYMBOL_PATH_SIZE bytes long. Returns nullptr if the path is empty.
// Note: the original concatenates without checking the size of the buffer.
static const char* __fastcall EXCEPTION_BuildSymbolPath(char* szPath)
{
	szPath[0] = '\0';

	char szModuleDirectory[0x200];
	szModuleDirectory[0] = '\0';
	if (GetModuleFileNameA(nullptr, szModuleDirectory, sizeof(szModuleDirectory)))
	{
		int nIndex = (int)strlen(szModuleDirectory) - 1;
		while (nIndex > 0 && szModuleDirectory[nIndex] != '\\' && szModuleDirectory[nIndex] != '/' && szModuleDirectory[nIndex] != ':')
		{
			--nIndex;
		}

		if (nIndex > 0)
		{
			if (szModuleDirectory[nIndex] == ':')
			{
				++nIndex;
			}
			szModuleDirectory[nIndex] = '\0';
			EXCEPTION_AppendSymbolPath(szPath, szModuleDirectory);
		}
		else
		{
			szModuleDirectory[0] = '\0';
		}
	}

	char szBuffer[0x200];
	if (GetCurrentDirectoryA(sizeof(szBuffer), szBuffer) && (!szModuleDirectory[0] || _stricmp(szModuleDirectory, szBuffer) != 0))
	{
		EXCEPTION_AppendSymbolPath(szPath, szBuffer);
	}

	if (GetEnvironmentVariableA("_NT_SYMBOL_PATH", szBuffer, sizeof(szBuffer)))
	{
		EXCEPTION_AppendSymbolPath(szPath, szBuffer);
	}

	if (GetEnvironmentVariableA("_NT_ALTERNATE_SYMBOL_PATH", szBuffer, sizeof(szBuffer)))
	{
		EXCEPTION_AppendSymbolPath(szPath, szBuffer);
	}

	if (GetEnvironmentVariableA("SYSTEMROOT", szBuffer, sizeof(szBuffer)))
	{
		EXCEPTION_AppendSymbolPath(szPath, szBuffer);
	}

	const size_t nLength = strlen(szPath);
	if (nLength)
	{
		// Remove the last separator
		szPath[nLength - 1] = '\0';
		FOG_TraceF("", "User defined symbols path: %s", szPath);
	}
	else
	{
		FOG_TraceF("", "Unable to generate symbols search path");
	}

	return szPath[0] ? szPath : nullptr;
}

// 1.10f: 0x6FF603E0
static D2ExceptionModuleStrc* EXCEPTION_EnumerateModulesWithPSAPI(HANDLE hProcess)
{
	HMODULE hPSAPI = LoadLibraryA("psapi.dll");
	if (!hPSAPI)
	{
		return nullptr;
	}

	EnumProcessModulesFunc pfEnumProcessModules = (EnumProcessModulesFunc)GetProcAddress(hPSAPI, "EnumProcessModules");
	GetModuleFileNameExAFunc pfGetModuleFileNameExA = (GetModuleFileNameExAFunc)GetProcAddress(hPSAPI, "GetModuleFileNameExA");
	GetModuleBaseNameAFunc pfGetModuleBaseNameA = (GetModuleBaseNameAFunc)GetProcAddress(hPSAPI, "GetModuleBaseNameA");
	GetModuleInformationFunc pfGetModuleInformation = (GetModuleInformationFunc)GetProcAddress(hPSAPI, "GetModuleInformation");

	D2ExceptionModuleStrc* pModules = nullptr;
	if (!pfEnumProcessModules || !pfGetModuleFileNameExA || !pfGetModuleBaseNameA || !pfGetModuleInformation)
	{
		FOG_TraceF("", "Unable to load psapi library");
		FreeLibrary(hPSAPI);
		return nullptr;
	}

	HMODULE hModules[EXCEPTION_MAX_PSAPI_MODULES];
	DWORD dwBytesNeeded = 0;
	if (!pfEnumProcessModules(hProcess, hModules, sizeof(hModules), &dwBytesNeeded))
	{
		FOG_TraceF("", "Error enumerating modules using PSAPI:  error(%d)", GetLastError());
		FreeLibrary(hPSAPI);
		return nullptr;
	}

	const int nModules = (int)(dwBytesNeeded / sizeof(HMODULE));
	if (nModules > EXCEPTION_MAX_PSAPI_MODULES)
	{
		FOG_TraceF("", "PSAPI EnumProcessModules returned invalid number of modules");
		FreeLibrary(hPSAPI);
		return nullptr;
	}

	FOG_TraceF("", "\nEnumerate modules...");
	for (int i = 0; i < nModules; ++i)
	{
		MODULEINFO tModuleInfo;
		char szPath[MAX_PATH];
		char szName[0x100];
		if (!pfGetModuleInformation(hProcess, hModules[i], &tModuleInfo, sizeof(tModuleInfo)))
		{
			FOG_TraceF("", "ERROR: PSAPI GetModuleInformation (%d)", GetLastError());
			EXCEPTION_FreeModules(pModules);
			FreeLibrary(hPSAPI);
			return nullptr;
		}

		if (!pfGetModuleFileNameExA(hProcess, hModules[i], szPath, sizeof(szPath)))
		{
			FOG_TraceF("", "ERROR: PSAPI GetModuleFileNameExA (%d)", GetLastError());
			EXCEPTION_FreeModules(pModules);
			FreeLibrary(hPSAPI);
			return nullptr;
		}

		if (!pfGetModuleBaseNameA(hProcess, hModules[i], szName, sizeof(szName) - 1))
		{
			FOG_TraceF("", "ERROR: PSAPI GetModuleBaseNameA (%d)", GetLastError());
			EXCEPTION_FreeModules(pModules);
			FreeLibrary(hPSAPI);
			return nullptr;
		}
		szName[sizeof(szName) - 1] = '\0';

		pModules = EXCEPTION_AddModule(pModules, szPath, szName, (uint32_t)tModuleInfo.lpBaseOfDll, tModuleInfo.SizeOfImage);
	}

	FreeLibrary(hPSAPI);
	return pModules;
}

// 1.10f: 0x6FF600B0
// Lists the modules of the process and loads their symbols
static D2ExceptionModuleStrc* __fastcall EXCEPTION_LoadModulesSymbols(HANDLE hProcess, DWORD dwProcessId)
{
	D2ExceptionModuleStrc* pModules = nullptr;

	CreateToolhelp32SnapshotFunc pfCreateToolhelp32Snapshot = nullptr;
	Module32FirstFunc pfModule32First = nullptr;
	Module32NextFunc pfModule32Next = nullptr;
	HMODULE hToolhelp = nullptr;
	const char* szToolhelpLibraries[] = { "kernel32.dll", "tlhelp32.dll" };
	for (const char* szLibrary : szToolhelpLibraries)
	{
		hToolhelp = LoadLibraryA(szLibrary);
		if (!hToolhelp)
		{
			continue;
		}

		pfCreateToolhelp32Snapshot = (CreateToolhelp32SnapshotFunc)GetProcAddress(hToolhelp, "CreateToolhelp32Snapshot");
		pfModule32First = (Module32FirstFunc)GetProcAddress(hToolhelp, "Module32First");
		pfModule32Next = (Module32NextFunc)GetProcAddress(hToolhelp, "Module32Next");
		if (pfCreateToolhelp32Snapshot && pfModule32First && pfModule32Next)
		{
			break;
		}

		FreeLibrary(hToolhelp);
		hToolhelp = nullptr;
	}

	if (!hToolhelp)
	{
		FOG_TraceF("", "Unable to load toolhelp library");
	}
	else
	{
		HANDLE hSnapshot = pfCreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
		if (hSnapshot == INVALID_HANDLE_VALUE)
		{
			FOG_TraceF("", "Unable to get toolhelp snapshot");
			// Note: the original does not free the library in this case
			FreeLibrary(hToolhelp);
		}
		else
		{
			FOG_TraceF("", "Enumerate modules...");

			MODULEENTRY32 tModuleEntry;
			memset(&tModuleEntry, 0, sizeof(tModuleEntry));
			// Note: the original does not initialize the structure size, which makes Module32First fail on most systems
			tModuleEntry.dwSize = sizeof(tModuleEntry);
			if (pfModule32First(hSnapshot, &tModuleEntry))
			{
				do
				{
					pModules = EXCEPTION_AddModule(pModules, tModuleEntry.szExePath, tModuleEntry.szModule, (uint32_t)tModuleEntry.modBaseAddr, tModuleEntry.modBaseSize);
				}
				while (pfModule32Next(hSnapshot, &tModuleEntry));
			}

			CloseHandle(hSnapshot);
			FreeLibrary(hToolhelp);
		}
	}

	if (!pModules)
	{
		pModules = EXCEPTION_EnumerateModulesWithPSAPI(hProcess);
	}

	for (const D2ExceptionModuleStrc* pModule = pModules; pModule; pModule = pModule->pNext)
	{
		FOG_TraceF("", "    Base:%08lXh  Size:%7lXh  Name:%-15.15s  Path:%s", pModule->nBase, pModule->nSize, pModule->szName, pModule->szPath);
	}

	FOG_TraceF("", "");
	FOG_TraceF("", "Load symbols...");

	for (const D2ExceptionModuleStrc* pModule = pModules; pModule; pModule = pModule->pNext)
	{
		char szPath[MAX_PATH];
		char szName[0x100];
		SStrCopy(szPath, pModule->szPath, sizeof(szPath));
		SStrCopy(szName, pModule->szName, sizeof(szName));
		const DWORD dwBase = gpfSymLoadModule(hProcess, nullptr, szPath, szName, pModule->nBase, pModule->nSize);
		if (!gbQuietSymbolsLoading)
		{
			if (dwBase)
			{
				FOG_TraceF("", "Symbols Loaded for '%s'", szName);
			}
			else
			{
				FOG_TraceF("", "Error (%d) loading symbols for '%s'", GetLastError(), szName);
			}
		}
	}

	return pModules;
}

// 1.10f: 0x6FF60940
BOOL __fastcall EXCEPTION_StackCrawl(HANDLE hThread, const CONTEXT* pContext)
{
	if (EXCEPTION_IsStackDumpDisabled())
	{
		FOG_TraceF("", "sShowStack: Stack dump turned off in registry");
		return FALSE;
	}

	if (!gbImageHlpLoaded)
	{
		FOG_TraceF("", "sShowStack: imagehlp.dll not loaded");
		return FALSE;
	}

	HANDLE hProcess = nullptr;
	DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(), &hProcess, 0, FALSE, DUPLICATE_SAME_ACCESS);

	char szSymbolPath[EXCEPTION_SYMBOL_PATH_SIZE];
	if (!gpfSymInitialize(hProcess, EXCEPTION_BuildSymbolPath(szSymbolPath), FALSE))
	{
		FOG_TraceF("", "SymInitialize(): gle = %lu", GetLastError());
		gpfSymCleanup(hProcess);
		CloseHandle(hProcess);
		return FALSE;
	}

	gpfSymSetOptions(gpfSymGetOptions() | SYMOPT_LOAD_LINES);
	D2ExceptionModuleStrc* pModules = EXCEPTION_LoadModulesSymbols(hProcess, GetCurrentProcessId());

	D2ExceptionSymbolStrc tSymbol;
	EXCEPTION_InitSymbol(&tSymbol);

	FOG_TraceF("", "");
	FOG_TraceF("", "Annotated stack dump");

	// Annotated dump of the stack: 16 bytes per line, followed by the symbol of the values pointing in a module
	const uint32_t nEip = pContext->Eip;
	const D2ExceptionModuleStrc* pEipModule = EXCEPTION_FindModule(pModules, nEip);
	DWORD dwDisplacement = 0;
	const BOOL bEipSymbolFound = gpfSymGetSymFromAddr(hProcess, nEip, &dwDisplacement, &tSymbol.tSymbol);
	FOG_TraceFAppend("", "\n                     // EIP = 0x%08X - %s - %s+%04X\n\n", nEip, pEipModule ? pEipModule->szName : "unknown", bEipSymbolFound ? tSymbol.tSymbol.Name : "unknown", dwDisplacement);

	const uint8_t* pStack = (const uint8_t*)pContext->Esp;
	int nRemainingBytes = 0x1000;
	int nLines = 0;
	while (nLines < 400)
	{
		FOG_TraceFAppend("", "              %08X:", pStack);

		const int nLineSize = nRemainingBytes < 16 ? nRemainingBytes : 16;
		char szLine[0x100];
		szLine[0] = '\0';
		if (IsBadReadPtr(pStack, nLineSize))
		{
			// Note: the original only writes this in its buffer
			SStrCopy(szLine, "<unreadable>", sizeof(szLine));
			FOG_TraceFAppend("", "%s\n", szLine);
			break;
		}

		// A line stops after the first value pointing in a module
		BOOL bPointsInModule = FALSE;
		int nBytes = 0;
		while (nBytes < nLineSize)
		{
			const size_t nLength = strlen(szLine);
			SStrPrintf(&szLine[nLength], sizeof(szLine) - nLength, (char*)" %02X%02X%02X%02X", pStack[nBytes], pStack[nBytes + 1], pStack[nBytes + 2], pStack[nBytes + 3]);
			const uint32_t nValue = *(const uint32_t*)&pStack[nBytes];
			nBytes += 4;
			if (EXCEPTION_FindModule(pModules, nValue))
			{
				bPointsInModule = TRUE;
				break;
			}
		}

		for (int nPadding = ((0x90 - 9 * nBytes) >> 2) + 2; nPadding > 0; --nPadding)
		{
			SStrNCat(szLine, " ", sizeof(szLine));
		}

		size_t nLength = strlen(szLine);
		for (int i = 0; i < nBytes && nLength < sizeof(szLine) - 1; ++i)
		{
			szLine[nLength++] = (pStack[i] & 0x7F) < ' ' ? '.' : (char)pStack[i];
		}
		szLine[nLength] = '\0';
		FOG_TraceFAppend("", "%s\n", szLine);

		if (bPointsInModule)
		{
			const uint32_t nValue = *(const uint32_t*)&pStack[nBytes - 4];
			const D2ExceptionModuleStrc* pModule = EXCEPTION_FindModule(pModules, nValue);
			D2_ASSERT(pModule);

			DWORD dwValueDisplacement = 0;
			const char* szSymbolName = gpfSymGetSymFromAddr(hProcess, nValue, &dwValueDisplacement, &tSymbol.tSymbol) ? tSymbol.tSymbol.Name : "unknown";
			if (!_stricmp(szSymbolName, "`string'") && !dwValueDisplacement)
			{
				char szString[0x50];
				FOG_EscapeString(szString, (const char*)(uintptr_t)nValue, sizeof(szString), 0);
				FOG_TraceFAppend("", "\n                           // 0x%08X - %s - %s='%s'\n\n", nValue, pModule->szName, szSymbolName, szString);
			}
			else
			{
				FOG_TraceFAppend("", "\n                           // 0x%08X - %s - %s+%04X\n\n", nValue, pModule->szName, szSymbolName, dwValueDisplacement);
			}
			nLines += 3;
		}

		pStack += nBytes;
		nRemainingBytes -= nBytes;
		++nLines;
		if (nRemainingBytes <= 0)
		{
			break;
		}
	}

	EXCEPTION_FreeModules(pModules);
	FOG_FlushLogs();

	// Call stack
	FOG_TraceF("", "");
	FOG_TraceF("", "Stack Crawl:");
	FOG_TraceF("", "Address  Frame    Module       Return    Stack");

	CONTEXT tContext = *pContext;
	STACKFRAME tStackFrame;
	EXCEPTION_InitStackFrame(&tStackFrame, pContext);

	int nFrames = 0;
	int nMissingSymbols = 0;
	while (nMissingSymbols < 3 && nFrames < 64)
	{
		if (!gpfStackWalk(IMAGE_FILE_MACHINE_I386, hProcess, hThread, &tStackFrame, &tContext, nullptr, gpfSymFunctionTableAccess, gpfSymGetModuleBase, nullptr))
		{
			FOG_TraceF("", "Stack walk error: %d", GetLastError());
			break;
		}

		DWORD dwFrameDisplacement = 0;
		IMAGEHLP_LINE tLine;
		const char* szSymbolName = tSymbol.tSymbol.Name;
		if (!EXCEPTION_GetSymbol(hProcess, tStackFrame.AddrPC.Offset, &tSymbol, &dwFrameDisplacement, &tLine))
		{
			szSymbolName = "unknown";
			++nMissingSymbols;
		}

		char szModulePath[MAX_PATH];
		uint32_t nSection = 0;
		uint32_t nOffset = 0;
		EXCEPTION_GetLogicalAddress((const void*)tStackFrame.AddrPC.Offset, szModulePath, sizeof(szModulePath), &nSection, &nOffset);
		const char* szModuleFileName = strrchr(szModulePath, '\\');
		szModuleFileName = szModuleFileName ? szModuleFileName + 1 : szModulePath;

		LOG_TraceFNoNewLine("", "%08x %08x %-12s ", tStackFrame.AddrPC.Offset, tStackFrame.AddrFrame.Offset, szModuleFileName);

		IMAGEHLP_MODULE tModuleInfo;
		memset(&tModuleInfo, 0, sizeof(tModuleInfo));
		tModuleInfo.SizeOfStruct = sizeof(tModuleInfo);
		if (gpfSymGetModuleInfo(hProcess, tStackFrame.AddrPC.Offset, &tModuleInfo))
		{
			FOG_TraceFAppend("", "%s!", tModuleInfo.ModuleName);
		}

		FOG_TraceFAppend("", "%s+%04X ", szSymbolName, dwFrameDisplacement);

		if (tSymbol.tSymbol.Flags & 3)
		{
			FOG_TraceFAppend("", "[omap] ");
		}

		if (const FPO_DATA* pFpoData = (const FPO_DATA*)tStackFrame.FuncTableEntry)
		{
			switch (pFpoData->cbFrame)
			{
			case FRAME_FPO:
				if (pFpoData->fHasSEH)
				{
					FOG_TraceFAppend("", "(FPO: [SEH])");
				}
				else
				{
					FOG_TraceFAppend("", " (FPO:");
					if (pFpoData->fUseBP)
					{
						FOG_TraceFAppend("", " [EBP 0x%08x]", tStackFrame.Reserved[0]);
					}
					FOG_TraceFAppend("", " [%d, %d, %d])", pFpoData->cdwParams, pFpoData->cdwLocals, pFpoData->cbRegs);
				}
				break;

			case FRAME_NONFPO:
				FOG_TraceFAppend("", "(FPO: Non-FPO [%d, %d, %d])", pFpoData->cdwParams, pFpoData->cdwLocals, pFpoData->cbRegs);
				break;

			default:
				FOG_TraceFAppend("", "(UNKNOWN FPO TYPE)");
				break;
			}
		}

		if (tLine.LineNumber)
		{
			const char* szFileName = strrchr(tLine.FileName, '\\');
			szFileName = szFileName ? szFileName + 1 : tLine.FileName;
			int nPadding = 0x18 - (int)SStrLen(szSymbolName);
			if (nPadding < 1)
			{
				nPadding = 1;
			}
			FOG_TraceFAppend("", "%*s %s, %d", nPadding, " ", szFileName, tLine.LineNumber);
		}

		FOG_TraceFAppend("", "\n");
		++nFrames;
	}

	FOG_TraceF("", "%d frames dumped", nFrames);
	FOG_FlushLogs();
	gpfSymCleanup(hProcess);
	CloseHandle(hProcess);
	return TRUE;
}

// 1.10f: 0x6FF5F350
// Dumps the stack of structured exceptions converted to C++ exceptions
static void __cdecl EXCEPTION_SETranslator(unsigned int nCode, EXCEPTION_POINTERS* pExceptionInfo)
{
	D2_MAYBE_UNUSED(nCode);
	if (!gbImageHlpLoaded)
	{
		FOG_TraceF("", "ExceptionHandler: imagehlp.dll not loaded");
		return;
	}

	HANDLE hThread = nullptr;
	DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);
	EXCEPTION_StackCrawl(hThread, pExceptionInfo->ContextRecord);
	CloseHandle(hThread);
}

// 1.10f: 0x6FF5F3C0
// Walks the stack of ghThreadToStackWalk when ghStackWalkRequestEvent is set, the thread must be suspended by another thread
static DWORD WINAPI EXCEPTION_StackWalkThread(LPVOID lpParameter)
{
	D2_MAYBE_UNUSED(lpParameter);
	while (WaitForSingleObject(ghStackWalkRequestEvent, INFINITE) == WAIT_OBJECT_0)
	{
		D2_ASSERT(ghThreadToStackWalk != ghStackWalkThread);

		if (SuspendThread(ghThreadToStackWalk) == (DWORD)-1)
		{
			FOG_TraceF("", "[StackWalkThread]: SuspendThread() err = %lu", GetLastError());
		}
		else
		{
			FOG_TraceF("", "Suspended Victim Thread...");
			CONTEXT tContext;
			memset(&tContext, 0, sizeof(tContext));
			tContext.ContextFlags = CONTEXT_FULL;
			if (GetThreadContext(ghThreadToStackWalk, &tContext))
			{
				EXCEPTION_StackCrawl(ghThreadToStackWalk, &tContext);
			}
			else
			{
				FOG_TraceF("", "[StackWalkThread]: GetThreadContext() err = %lu", GetLastError());
			}
			ResumeThread(ghThreadToStackWalk);
		}

		CloseHandle(ghThreadToStackWalk);
		ghThreadToStackWalk = nullptr;
		SetEvent(ghStackWalkDoneEvent);
	}

	if (ghStackWalkRequestEvent)
	{
		CloseHandle(ghStackWalkRequestEvent);
		ghStackWalkRequestEvent = nullptr;
	}
	if (ghStackWalkDoneEvent)
	{
		CloseHandle(ghStackWalkDoneEvent);
		ghStackWalkDoneEvent = nullptr;
	}
	if (ghStackWalkThread)
	{
		CloseHandle(ghStackWalkThread);
		ghStackWalkThread = nullptr;
	}
	return 0;
}

// 1.10f: 0x6FF5F520
BOOL EXCEPTION_LoadImageHlp()
{
	if (gbImageHlpLoaded)
	{
		return TRUE;
	}

	InitializeCriticalSection(&gtSymbolsLock);
#ifdef _MSC_VER
	_set_se_translator(EXCEPTION_SETranslator);
#else
	// _set_se_translator is only available with the Microsoft runtime
	D2_MAYBE_UNUSED(EXCEPTION_SETranslator);
#endif

	ghImageHlp = LoadLibraryA("imagehlp.dll");
	if (!ghImageHlp)
	{
		FOG_Trace("Missing imagehlp.dll.  Can't generate better stack crawls!");
		return FALSE;
	}

	gpfSymCleanup = (SymCleanupFunc)GetProcAddress(ghImageHlp, "SymCleanup");
	gpfSymFunctionTableAccess = (PFUNCTION_TABLE_ACCESS_ROUTINE)GetProcAddress(ghImageHlp, "SymFunctionTableAccess");
	gpfSymGetLineFromAddr = (SymGetLineFromAddrFunc)GetProcAddress(ghImageHlp, "SymGetLineFromAddr");
	gpfSymGetModuleBase = (PGET_MODULE_BASE_ROUTINE)GetProcAddress(ghImageHlp, "SymGetModuleBase");
	gpfSymGetModuleInfo = (SymGetModuleInfoFunc)GetProcAddress(ghImageHlp, "SymGetModuleInfo");
	gpfSymGetOptions = (SymGetOptionsFunc)GetProcAddress(ghImageHlp, "SymGetOptions");
	gpfSymGetSymFromAddr = (SymGetSymFromAddrFunc)GetProcAddress(ghImageHlp, "SymGetSymFromAddr");
	gpfSymInitialize = (SymInitializeFunc)GetProcAddress(ghImageHlp, "SymInitialize");
	gpfSymSetOptions = (SymSetOptionsFunc)GetProcAddress(ghImageHlp, "SymSetOptions");
	gpfSymLoadModule = (SymLoadModuleFunc)GetProcAddress(ghImageHlp, "SymLoadModule");
	gpfSymUnloadModule = (SymUnloadModuleFunc)GetProcAddress(ghImageHlp, "SymUnloadModule");
	gpfStackWalk = (StackWalkFunc)GetProcAddress(ghImageHlp, "StackWalk");
	gpfUnDecorateSymbolName = (UnDecorateSymbolNameFunc)GetProcAddress(ghImageHlp, "UnDecorateSymbolName");
	gpfSplitSymbols = (SplitSymbolsFunc)GetProcAddress(ghImageHlp, "SplitSymbols");

	// SymGetLineFromAddr is optional
	if (!gpfSymCleanup || !gpfSymFunctionTableAccess || !gpfSymGetModuleBase || !gpfSymGetModuleInfo || !gpfSymGetOptions
		|| !gpfSymGetSymFromAddr || !gpfSymInitialize || !gpfSymSetOptions || !gpfStackWalk || !gpfUnDecorateSymbolName
		|| !gpfSymLoadModule || !gpfSymUnloadModule || !gpfSplitSymbols)
	{
		FOG_Trace("Missing functions in imagehlp.dll.  Can't generate better stack crawls!");
		return FALSE;
	}

	gbImageHlpLoaded = TRUE;
	FOG_Trace("imagehlp.dll loaded for better stack crawls.");

	ghStackWalkRequestEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
	ghStackWalkDoneEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
	DWORD dwThreadId = 0;
	ghStackWalkThread = CreateThread(nullptr, 0, EXCEPTION_StackWalkThread, nullptr, 0, &dwThreadId);
	return TRUE;
}

// 1.10f: 0x6FF5F790
BOOL EXCEPTION_UnloadImageHlp()
{
	if (ghStackWalkThread)
	{
		// The thread stops waiting once its event is closed
		if (ghStackWalkRequestEvent)
		{
			CloseHandle(ghStackWalkRequestEvent);
			ghStackWalkRequestEvent = nullptr;
		}
		WaitForSingleObject(ghStackWalkThread, 100);
	}

	gbImageHlpLoaded = FALSE;
	if (ghImageHlp)
	{
		FreeLibrary(ghImageHlp);
		ghImageHlp = nullptr;
	}

	DeleteCriticalSection(&gtSymbolsLock);
	return TRUE;
}

// 1.10f: 0x6FF5F800
// Dumps the stack of the thread from the stack walk thread, so that the thread can be suspended
static void __fastcall EXCEPTION_DumpStack(HANDLE hThread)
{
	if (EXCEPTION_IsStackDumpDisabled())
	{
		FOG_TraceF("", "sDumpStack: Stack dump turned off in registry");
		return;
	}

	if (!gbImageHlpLoaded)
	{
		FOG_TraceF("", "sDumpStack: imagehlp.dll not loaded");
		return;
	}

	if (!ghStackWalkRequestEvent)
	{
		FOG_TraceF("", "No event to trigger stack walk thread");
		return;
	}

	if (!ghStackWalkThread)
	{
		// Note: the original continues and waits forever for the stack walk
		FOG_TraceF("", "No stack walk thread");
		return;
	}

	FOG_TraceF("", "");
	FOG_TraceF("", "ImageHelp Stack Crawl:");

	if (!hThread)
	{
		hThread = GetCurrentThread();
	}

	DuplicateHandle(GetCurrentProcess(), hThread, GetCurrentProcess(), &ghThreadToStackWalk, 0, FALSE, DUPLICATE_SAME_ACCESS);
	SetEvent(ghStackWalkRequestEvent);

	// Lower the priority of the thread to make sure the stack walk thread suspends it
	int nPriority = GetThreadPriority(ghThreadToStackWalk);
	if (nPriority == THREAD_PRIORITY_ERROR_RETURN)
	{
		nPriority = THREAD_PRIORITY_NORMAL;
	}
	SetThreadPriority(ghThreadToStackWalk, THREAD_PRIORITY_IDLE);
	WaitForSingleObject(ghStackWalkDoneEvent, INFINITE);
	// Note: the original restores the priority through ghThreadToStackWalk, which the stack walk thread already closed and reset,
	// so the thread kept the idle priority
	SetThreadPriority(hThread, nPriority);
}

// 1.10f: 0x6FF5FA10 (#10033)
void __fastcall FOG_CrashDeadlockDetected(HANDLE hThreadToWalk)
{
	FOG_TraceF("", "Dumping stack for thread handle: %08x", hThreadToWalk);
	FOG_10028(ERRCATEGORY_UNKNOWN, __FILE__, __LINE__, "Deadlock Detected");
	EXCEPTION_DumpStack(hThreadToWalk);
	FOG_FlushLogs();
}

// 1.10f: 0x6FF5F950 (#10034)
void __fastcall FOG_CrashDumpThread(HANDLE hThreadToWalk)
{
	FOG_TraceF("", "Dumping stack for thread handle: %08x", hThreadToWalk);

	CONTEXT tContext;
	memset(&tContext, 0, sizeof(tContext));
	tContext.ContextFlags = CONTEXT_FULL;
	GetThreadContext(hThreadToWalk, &tContext);

	FOG_TraceFAppend("", "Stack bytes:\n");
	FOG_TraceMemory("ERR", "", (void*)tContext.Esp, 0x1000, FALSE, TRUE, FALSE);
	FOG_TraceFAppend("", "Code bytes:\n");
	FOG_TraceMemory("ERR", "", (void*)tContext.Eip, 0x20, FALSE, TRUE, FALSE);
	EXCEPTION_DumpStack(hThreadToWalk);
	FOG_FlushLogs();
}

// 1.10f: Inlined
// Releases one reference to the symbols, or all of them
static void EXCEPTION_ReleaseSymbols(BOOL bAll)
{
	if (!gbImageHlpLoaded)
	{
		return;
	}

	EnterCriticalSection(&gtSymbolsLock);
	while (gnSymbolsRefCount > 0)
	{
		--gnSymbolsRefCount;
		if (!gnSymbolsRefCount)
		{
			gpfSymCleanup(GetCurrentProcess());
		}

		if (!bAll)
		{
			break;
		}
	}
	LeaveCriticalSection(&gtSymbolsLock);
}

// 1.10f: 0x6FF5F300 (#10233)
void __fastcall FOG_10233(const char* szModuleName, BOOL bLoad)
{
	D2_MAYBE_UNUSED(szModuleName);
	D2_MAYBE_UNUSED(bLoad);
	EXCEPTION_ReleaseSymbols(TRUE);
}

// 1.10f: 0x6FF5FB30
static BOOL __fastcall EXCEPTION_QuickStackWalk(const char* szFileSubName, HANDLE hThread, const CONTEXT* pContext)
{
	if (gnQuickStackWalkDepth > 0)
	{
		return FALSE;
	}

	++gnQuickStackWalkDepth;
	HANDLE hProcess = GetCurrentProcess();

	// The symbols are initialized on first use, and kept until FOG_10233 is called
	BOOL bSymbolsReady = FALSE;
	EnterCriticalSection(&gtSymbolsLock);
	if (gbImageHlpLoaded)
	{
		bSymbolsReady = TRUE;
		if (gnSymbolsRefCount++ <= 0)
		{
			if (!gszQuickStackWalkSymbolPath[0])
			{
				EXCEPTION_BuildSymbolPath(gszQuickStackWalkSymbolPath);
			}

			if (gpfSymInitialize(hProcess, gszQuickStackWalkSymbolPath, FALSE))
			{
				++gnSymbolsRefCount;
				gpfSymSetOptions(gpfSymGetOptions() | SYMOPT_LOAD_LINES);
				EXCEPTION_FreeModules(EXCEPTION_LoadModulesSymbols(hProcess, GetCurrentProcessId()));
			}
			else
			{
				FOG_TraceF("", "s_DoSymInitialize(): err = %lu", GetLastError());
				gpfSymCleanup(hProcess);
				gnSymbolsRefCount = 0;
				bSymbolsReady = FALSE;
			}
		}
	}
	LeaveCriticalSection(&gtSymbolsLock);

	if (!bSymbolsReady)
	{
		--gnQuickStackWalkDepth;
		return FALSE;
	}

	D2ExceptionSymbolStrc tSymbol;
	EXCEPTION_InitSymbol(&tSymbol);

	CONTEXT tContext = *pContext;
	STACKFRAME tStackFrame;
	EXCEPTION_InitStackFrame(&tStackFrame, pContext);

	int nMissingSymbols = 0;
	int nFrame = 0;
	for (; nFrame < 16 && nMissingSymbols < 3; ++nFrame)
	{
		if (!gpfStackWalk(IMAGE_FILE_MACHINE_I386, hProcess, hThread, &tStackFrame, &tContext, nullptr, gpfSymFunctionTableAccess, gpfSymGetModuleBase, nullptr))
		{
			break;
		}

		// Skip the frame of the caller
		if (nFrame < 1)
		{
			continue;
		}

		const uint32_t nAddress = tStackFrame.AddrPC.Offset;
		DWORD dwDisplacement = 0;
		IMAGEHLP_LINE tLine;
		const char* szSymbolName = tSymbol.tSymbol.Name;
		if (!EXCEPTION_GetSymbol(hProcess, nAddress, &tSymbol, &dwDisplacement, &tLine))
		{
			szSymbolName = "unknown";
			++nMissingSymbols;
		}

		IMAGEHLP_MODULE tModuleInfo;
		memset(&tModuleInfo, 0, sizeof(tModuleInfo));
		tModuleInfo.SizeOfStruct = sizeof(tModuleInfo);
		if (!gpfSymGetModuleInfo(hProcess, nAddress, &tModuleInfo))
		{
			tModuleInfo.ModuleName[0] = '\0';
		}

		if (tLine.LineNumber)
		{
			int nPadding = 0x28 - (int)SStrLen(tModuleInfo.ModuleName) - (int)SStrLen(szSymbolName);
			if (nPadding < 1)
			{
				nPadding = 1;
			}
			FOG_TraceF(szFileSubName, "    %08X  %s!%s+%04X  %*s%s,%d", nAddress, tModuleInfo.ModuleName, szSymbolName, dwDisplacement,
				nPadding, " ", FOG_GetShortSourceFilePath(tLine.FileName), tLine.LineNumber);
		}
		else
		{
			FOG_TraceF(szFileSubName, "    %08X  %s!%s+%04X", nAddress, tModuleInfo.ModuleName, szSymbolName, dwDisplacement);
		}
	}

	EXCEPTION_ReleaseSymbols(FALSE);

	// Note: the profiling code was compiled out of the original, and its counters are always 0
	FOG_TraceF(szFileSubName, "QuickStackWalk: %d entries, %I64d+%I64d+%I64d+%I64d cycles, %I64d avg", nFrame, 0LL, 0LL, 0LL, 0LL, 0LL);

	--gnQuickStackWalkDepth;
	return TRUE;
}

// 1.10f: 0x6FF5FAC0 (#10237)
BOOL __fastcall FOG_QuickStackWalk(const char* szFileSubName)
{
	CONTEXT tContext;
	memset(&tContext, 0, sizeof(tContext));
	tContext.ContextFlags = CONTEXT_FULL;
	// The original only captures EIP, ESP and EBP
	RtlCaptureContext(&tContext);
	return EXCEPTION_QuickStackWalk(szFileSubName, GetCurrentThread(), &tContext);
}

// 1.10f: 0x6FF62BD0
static void EXCEPTION_GetCrashDumpPath(char* szPath, size_t nSize)
{
	szPath[0] = '\0';
	if (LOG_GetModuleDirectory(szPath, nSize))
	{
		SStrNCat(szPath, "\\", nSize);
		FOG_CreatePathHierarchy(szPath);
	}
	SStrNCat(szPath, "Crashdump", nSize);
}

#pragma pack(push, 1)
struct D2CrashDumpRecordStrc			// sizeof 0x10 + 4 * nParameters
{
	uint32_t nVersion;					// 0x00
	uint32_t nCode;						// 0x04
	uint32_t nAddress;					// 0x08
	uint32_t nParameters;				// 0x0C
	uint32_t aParameters[CRASHDUMP_MAX_PARAMETERS];	// 0x10
};

struct D2CrashDumpSummaryEntryStrc		// sizeof 0xF + 4 * nParameters
{
	uint16_t nCount;					// 0x00
	uint32_t nVersion;					// 0x02
	uint32_t nCode;						// 0x06
	uint32_t nAddress;					// 0x0A
	uint8_t nParameters;				// 0x0E
	// uint32_t aParameters[nParameters]
};
#pragma pack(pop)

// 1.10f: 0x6FF612C0
// Appends a record to the Crashdump file
static void __fastcall EXCEPTION_WriteCrashDump(uint32_t nVersion, uint32_t nCode, uint32_t nAddress, uint32_t nParameters, const uint32_t* pParameters)
{
	char szPath[MAX_PATH];
	EXCEPTION_GetCrashDumpPath(szPath, sizeof(szPath));
	FILE* pFile = fopen(szPath, "ab");
	if (!pFile)
	{
		return;
	}

	// Note: the original does not check the number of parameters
	if (nParameters > CRASHDUMP_MAX_PARAMETERS)
	{
		nParameters = CRASHDUMP_MAX_PARAMETERS;
	}

	D2CrashDumpRecordStrc tRecord;
	tRecord.nVersion = nVersion;
	tRecord.nCode = nCode;
	tRecord.nAddress = nAddress;
	tRecord.nParameters = nParameters;
	if (nParameters)
	{
		memcpy(tRecord.aParameters, pParameters, nParameters * sizeof(uint32_t));
	}
	fwrite(&tRecord, offsetof(D2CrashDumpRecordStrc, aParameters) + nParameters * sizeof(uint32_t), 1, pFile);
	fclose(pFile);
}

// 1.10f: 0x6FF61370 (#10263)
BOOL __fastcall FOG_ReadCrashDumpSummary(uint8_t* pBuffer, int* pSize)
{
	char szPath[MAX_PATH];
	EXCEPTION_GetCrashDumpPath(szPath, sizeof(szPath));
	if (GetFileAttributesA(szPath) == INVALID_FILE_ATTRIBUTES)
	{
		return FALSE;
	}

	const int nBufferSize = *pSize;
	FILE* pFile = fopen(szPath, "rb");
	if (!pFile)
	{
		return FALSE;
	}

	if (fseek(pFile, 0, SEEK_END))
	{
		fclose(pFile);
		return FALSE;
	}

	const int nFileSize = (int)ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	uint8_t* pFileData = (uint8_t*)FOG_Alloc(nFileSize, __FILE__, __LINE__, 0);
	const int nReadSize = (int)fread(pFileData, 1, nFileSize, pFile);
	fclose(pFile);
	DeleteFileA(szPath);

	*pSize = 1;
	int nEntries = 0;
	const uint8_t* pBufferEnd = pBuffer + nBufferSize;
	const uint8_t* pRead = pFileData;
	const uint8_t* pFileEnd = pFileData + nReadSize;
	while (pRead + offsetof(D2CrashDumpRecordStrc, aParameters) <= pFileEnd)
	{
		D2CrashDumpRecordStrc tRecord;
		memcpy(&tRecord, pRead, offsetof(D2CrashDumpRecordStrc, aParameters));
		pRead += offsetof(D2CrashDumpRecordStrc, aParameters);

		// Note: the original does not check the number of parameters
		const uint32_t nRecordParameters = tRecord.nParameters;
		const uint32_t nParameters = nRecordParameters < CRASHDUMP_MAX_PARAMETERS ? nRecordParameters : CRASHDUMP_MAX_PARAMETERS;
		if (pRead + nRecordParameters * sizeof(uint32_t) > pFileEnd)
		{
			break;
		}
		memcpy(tRecord.aParameters, pRead, nParameters * sizeof(uint32_t));
		pRead += nRecordParameters * sizeof(uint32_t);
		const uint32_t nParametersSize = nParameters * sizeof(uint32_t);

		// Look for an identical crash
		uint8_t* pEntry = pBuffer + 1;
		int nEntry = 0;
		for (; nEntry < nEntries; ++nEntry)
		{
			D2CrashDumpSummaryEntryStrc* pSummaryEntry = (D2CrashDumpSummaryEntryStrc*)pEntry;
			if (pSummaryEntry->nVersion == tRecord.nVersion && pSummaryEntry->nCode == tRecord.nCode && pSummaryEntry->nAddress == tRecord.nAddress
				&& pSummaryEntry->nParameters == (uint8_t)nParameters && !memcmp(&pSummaryEntry[1], tRecord.aParameters, nParametersSize))
			{
				++pSummaryEntry->nCount;
				break;
			}

			// Note: the original skips the entries using the parameters count of the current record
			pEntry += sizeof(D2CrashDumpSummaryEntryStrc) + pSummaryEntry->nParameters * sizeof(uint32_t);
		}

		if (nEntry != nEntries)
		{
			continue;
		}

		// The original requires enough room for an entry with the maximum number of parameters
		if (pEntry + sizeof(D2CrashDumpSummaryEntryStrc) + sizeof(tRecord.aParameters) >= pBufferEnd)
		{
			break;
		}

		D2CrashDumpSummaryEntryStrc* pSummaryEntry = (D2CrashDumpSummaryEntryStrc*)pEntry;
		pSummaryEntry->nCount = 1;
		pSummaryEntry->nVersion = tRecord.nVersion;
		pSummaryEntry->nCode = tRecord.nCode;
		pSummaryEntry->nAddress = tRecord.nAddress;
		pSummaryEntry->nParameters = (uint8_t)nParameters;
		memcpy(&pSummaryEntry[1], tRecord.aParameters, nParametersSize);
		*pSize += sizeof(D2CrashDumpSummaryEntryStrc) + nParametersSize;
		++nEntries;
	}

	// Note: the original never frees the content of the file
	FOG_Free(pFileData, __FILE__, __LINE__, 0);

	pBuffer[0] = (uint8_t)nEntries;
	return TRUE;
}

// Inlined
static const char* EXCEPTION_GetExceptionName(DWORD dwCode)
{
	switch (dwCode)
	{
	case EXCEPTION_GUARD_PAGE: return "GUARD_PAGE";
	case EXCEPTION_DATATYPE_MISALIGNMENT: return "DATATYPE_MISALIGNMENT";
	case EXCEPTION_BREAKPOINT: return "BREAKPOINT";
	case EXCEPTION_SINGLE_STEP: return "SINGLE_STEP";
	case EXCEPTION_ACCESS_VIOLATION: return "ACCESS_VIOLATION";
	case EXCEPTION_IN_PAGE_ERROR: return "IN_PAGE_ERROR";
	case EXCEPTION_INVALID_HANDLE: return "INVALID_HANDLE";
	case EXCEPTION_ILLEGAL_INSTRUCTION: return "ILLEGAL_INSTRUCTION";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "NONCONTINUABLE_EXCEPTION";
	case EXCEPTION_INVALID_DISPOSITION: return "INVALID_DISPOSITION";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "ARRAY_BOUNDS_EXCEEDED";
	case EXCEPTION_FLT_DENORMAL_OPERAND: return "FLT_DENORMAL_OPERAND";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "FLT_DIVIDE_BY_ZERO";
	case EXCEPTION_FLT_INEXACT_RESULT: return "FLT_INEXACT_RESULT";
	case EXCEPTION_FLT_INVALID_OPERATION: return "FLT_INVALID_OPERATION";
	case EXCEPTION_FLT_OVERFLOW: return "FLT_OVERFLOW";
	case EXCEPTION_FLT_STACK_CHECK: return "FLT_STACK_CHECK";
	case EXCEPTION_FLT_UNDERFLOW: return "FLT_UNDERFLOW";
	case EXCEPTION_INT_DIVIDE_BY_ZERO: return "INT_DIVIDE_BY_ZERO";
	case EXCEPTION_INT_OVERFLOW: return "INT_OVERFLOW";
	case EXCEPTION_PRIV_INSTRUCTION: return "PRIV_INSTRUCTION";
	case EXCEPTION_STACK_OVERFLOW: return "STACK_OVERFLOW";
	default: return nullptr;
	}
}

// 1.10f: 0x6FF5E6B0 (#10052)
LONG __stdcall FOG_UnhandledExceptionFilter(EXCEPTION_POINTERS* pExceptionInfo)
{
	// Only handle the first exception
	if (InterlockedIncrement(&gnUnhandledExceptionCounter) != 0)
	{
		InterlockedDecrement(&gnUnhandledExceptionCounter);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	ERRMGR_SetHandlingError();

	FOG_TraceF("", "");
	FOG_TraceF("", "");
	FOG_TraceF("", "------------------------------------------------------");
	FOG_PrintErrorHeader(nullptr, ERRMGR_TraceLine);

	const EXCEPTION_RECORD* pRecord = pExceptionInfo->ExceptionRecord;
	char szExceptionName[0x100];
	if (const char* szKnownName = EXCEPTION_GetExceptionName(pRecord->ExceptionCode))
	{
		strncpy(szExceptionName, szKnownName, sizeof(szExceptionName));
	}
	else if (!FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS, GetModuleHandleA("NTDLL.DLL"), pRecord->ExceptionCode, 0, szExceptionName, sizeof(szExceptionName), nullptr))
	{
		strncpy(szExceptionName, "Unknown Exception", sizeof(szExceptionName));
	}
	szExceptionName[sizeof(szExceptionName) - 1] = '\0';

	FOG_TraceF("", "***** UNHANDLED EXCEPTION: %s (%08x)", szExceptionName, pRecord->ExceptionCode);

	char szModule[MAX_PATH];
	uint32_t nSection = 0;
	uint32_t nOffset = 0;
	EXCEPTION_GetLogicalAddress(pRecord->ExceptionAddress, szModule, sizeof(szModule), &nSection, &nOffset);
	FOG_TraceF("", "Fault address:  %08X %02X:%08X %s", pRecord->ExceptionAddress, nSection, nOffset, szModule);

	const CONTEXT* pContext = pExceptionInfo->ContextRecord;
	FOG_TraceF("", "eax:%08x ebx:%08x ecx:%08x edx:%08x esi:%08x", pContext->Eax, pContext->Ebx, pContext->Ecx, pContext->Edx, pContext->Esi);
	FOG_TraceF("", "edi:%08x ebp:%08x esp:%08x eip:%08x flg:%08x", pContext->Edi, pContext->Ebp, pContext->Esp, pContext->Eip, pContext->EFlags);
	FOG_TraceF("", "cs:%04x ds:%04x es:%04x ss:%04x fs:%04x gs:%04x", pContext->SegCs, pContext->SegDs, pContext->SegEs, pContext->SegSs, pContext->SegFs, pContext->SegGs);

	FOG_TraceF("", "Stack bytes:");
	FOG_TraceMemory("", "", (void*)pContext->Esp, 0x1000, FALSE, TRUE, FALSE);
	FOG_TraceF("", "Code bytes:");
	FOG_TraceMemory("", "", (void*)pContext->Eip, 0x20, FALSE, TRUE, FALSE);
	FOG_FlushLogs();

	HANDLE hThread = nullptr;
	DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);
	EXCEPTION_StackCrawl(hThread, pContext);
	CloseHandle(hThread);

	EXCEPTION_WriteCrashDump(CRASHDUMP_VERSION, pRecord->ExceptionCode, (uint32_t)pRecord->ExceptionAddress, 0, nullptr);

	if (D2ExceptionCallback pfCallback = ERRMGR_GetExceptionCallback())
	{
		pfCallback();
	}

	char szCaption[0x100];
	SStrPrintf(szCaption, sizeof(szCaption), (char*)"%s Exception", ERRMGR_GetProgramName());
	char szMessage[0x1000];
	SStrPrintf(szMessage, sizeof(szMessage), (char*)"UNHANDLED EXCEPTION:\n%s (%08x)", szExceptionName, pRecord->ExceptionCode);
	MessageBoxA(nullptr, szMessage, szCaption, MB_ICONEXCLAMATION);

	InterlockedDecrement(&gnUnhandledExceptionCounter);
	return EXCEPTION_EXECUTE_HANDLER;
}
