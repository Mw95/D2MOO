#include "StormInternal.h"

#include <cstdio>
#include <cstring>
#include <storm/List.hpp>

// Error reporting

struct HANDLER : TSLinkedNode<HANDLER>
{
	SERRHANDLER pfnHandler;
};

struct MESSAGESOURCE
{
	uint16_t nFacility;
	HMODULE hModule;
	MESSAGESOURCE* pNext;
};

// Storm.0x6FFE22D4 : default strings, used if the string table resources of Storm.dll are not available
static const char* const sgszDefaultStrings[] =
{
	"ERROR #%u (0x%08x)",
	"This application has encountered a critical error:\n\n%s\n",
	"Program:\t%s\n",
	"File:\t%s\nLine:\t%d\n",
	"Function:\t%s\n",
	"Object:\t%s\n",
	"Handle:\t%s\n",
	"Expr:\t%s\n\n",
	"\n%s\n\n",
	"Press OK to terminate the application.",
	"Do you wish to terminate the application?",
	"File:\t%s\n",
};

enum SErrString
{
	SERRSTR_UNKNOWN_ERROR,
	SERRSTR_HEADER,
	SERRSTR_PROGRAM,
	SERRSTR_FILELINE,
	SERRSTR_FUNCTION,
	SERRSTR_OBJECT,
	SERRSTR_HANDLE,
	SERRSTR_EXPRESSION,
	SERRSTR_DESCRIPTION,
	SERRSTR_PRESS_OK,
	SERRSTR_TERMINATE,
	SERRSTR_FILE,
};

#define SERR_STRING_RESOURCE_BASE 0x5100

// Storm.0x6FFE6A7C
static volatile LONG sgnCritSectInitCount = -1;
// Storm.0x6FFEA070
static CRITICAL_SECTION sgErrCritSect;
// Storm.0x6FFEA088
static STORM_LIST(HANDLER) sgHandlerList;
// Storm.0x6FFEA094
static const char* sgszFatalFilename;
// Storm.0x6FFEA098
static int32_t sgnFatalLine;
// Storm.0x6FFEA09C
static DWORD sgdwFatalThreadId;
// Storm.0x6FFEA0A0
static BOOL sgbDisplayingError;
// Storm.0x6FFEA0A8
static char sgszStringBuffer[256];
// Storm.0x6FFEA1A8
static MESSAGESOURCE* sgpMessageSources;
// Storm.0x6FFEA1AC
static BOOL sgbDefaultMessageSourcesRegistered;
// Storm.0x6FFEA1B0
static BOOL sgbSuppressErrors;
// Storm.0x6FFEA1B4
static uint32_t sgdwLastError;
// Storm.0x6FFEA1B8
static BOOL sgbDebugMemoryLoaded;
// Storm.0x6FFEA1BC
static DWORD sgbDebugMemory;
// Storm.0x6FFEA1C0
static char sgszEmpty[3];


// Storm.0x6FFC1FD0
void SErrEnterCriticalSection()
{
	// The critical section is lazily initialized by the first thread to reach this point
	if (InterlockedIncrement(&sgnCritSectInitCount) == 0)
	{
		InitializeCriticalSection(&sgErrCritSect);
		EnterCriticalSection(&sgErrCritSect);
	}
	else
	{
		InterlockedDecrement(&sgnCritSectInitCount);
		EnterCriticalSection(&sgErrCritSect);
	}
}

// Storm.0x6FFC2010
void SErrLeaveCriticalSection()
{
	LeaveCriticalSection(&sgErrCritSect);
}

// Storm.0x6FFC2490
static const char* SErrGetString(uint32_t nString)
{
	if (LoadStringA(StormGetInstance(), SERR_STRING_RESOURCE_BASE + nString, sgszStringBuffer, sizeof(sgszStringBuffer)))
	{
		return sgszStringBuffer;
	}
	return sgszDefaultStrings[nString];
}

// Storm.0x6FFC24D0
// Converts a decorated type name such as ".?AUHANDLER@@" to "HANDLER (.?AUHANDLER@@)"
static BOOL SErrUndecorateTypeName(const char* szDecoratedName, char* szBuffer, size_t nBufferSize)
{
	if (SStrLen(szDecoratedName) < 6 || szDecoratedName[0] != '.' || szDecoratedName[3] != 'U')
	{
		return FALSE;
	}

	const char* szName = szDecoratedName + 4;
	if (!strpbrk(szName, "?@"))
	{
		return FALSE;
	}

	SStrCopy(szBuffer, szName, nBufferSize);
	char* pEnd = strpbrk(szBuffer, "?@");
	if (!pEnd)
	{
		return FALSE;
	}

	*pEnd = '\0';
	for (char* pChar = pEnd - 1; pChar >= szBuffer && *pChar == '_'; --pChar)
	{
		*pChar = '\0';
	}

	SStrNCat(szBuffer, " (", nBufferSize);
	SStrNCat(szBuffer, szDecoratedName, nBufferSize);
	SStrNCat(szBuffer, ")", nBufferSize);
	return TRUE;
}

// Storm.0x6FFC26A0
static void SErrAddDefaultMessageSource(uint16_t nFacility)
{
	MESSAGESOURCE** ppLink = &sgpMessageSources;
	while (*ppLink)
	{
		ppLink = &(*ppLink)->pNext;
	}

	MESSAGESOURCE* pSource = (MESSAGESOURCE*)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, sizeof(MESSAGESOURCE));
	*ppLink = pSource;
	pSource->nFacility = nFacility;
	pSource->hModule = StormGetInstance();
	pSource->pNext = nullptr;
}

// Storm.0x6FFC2680
static void SErrRegisterDefaultMessageSources()
{
	SErrAddDefaultMessageSource(0x510);   // Storm
	SErrAddDefaultMessageSource(0x876);   // DirectDraw
	SErrAddDefaultMessageSource(0x878);   // DirectSound
}

// Storm.0x6FFC1EA0
void SErrDestroy()
{
	while (HANDLER* pHandler = sgHandlerList.Head())
	{
		sgHandlerList.UnlinkNode(pHandler);
		SMemFree(pHandler, typeid(HANDLER).name(), SERR_LINECODE_OBJECT, 0);
	}

	sgbDefaultMessageSourcesRegistered = FALSE;
	for (MESSAGESOURCE* pSource = sgpMessageSources; pSource; pSource = sgpMessageSources)
	{
		sgpMessageSources = pSource->pNext;
		HeapFree(GetProcessHeap(), 0, pSource);
	}

	if (sgnCritSectInitCount != -1)
	{
		DeleteCriticalSection(&sgErrCritSect);
		sgnCritSectInitCount = -1;
	}
}

// Storm.#461
int32_t __stdcall SErrDisplayError(uint32_t messageId, const char* filename, int32_t linenumber, const char* description, int32_t recoverable, uint32_t exitcode)
{
	if (sgbSuppressErrors || sgbDisplayingError)
	{
		return FALSE;
	}

	sgbDisplayingError = TRUE;
	SErrEnterCriticalSection();
	SLogFlushAll();

	char szProgramPath[MAX_PATH];
	char szProgramName[MAX_PATH];
	szProgramPath[0] = '\0';
	szProgramName[0] = '\0';
	GetModuleFileNameA(nullptr, szProgramPath, MAX_PATH);

	WIN32_FIND_DATAA findData;
	SMemZero(&findData, sizeof(findData));
	HANDLE hFind = FindFirstFileA(szProgramPath, &findData);
	if (hFind)
	{
		FindClose(hFind);
	}
	SStrCopy(szProgramName, findData.cFileName, MAX_PATH);
	if (SStrChrR(szProgramName, '.'))
	{
		*(char*)SStrChrR(szProgramName, '.') = '\0';
	}

	char szErrorString[256];
	szErrorString[0] = '\0';
	SErrGetErrorStr(messageId, szErrorString, sizeof(szErrorString));
	if (!szErrorString[0])
	{
		wsprintfA(szErrorString, SErrGetString(SERRSTR_UNKNOWN_ERROR), messageId & 0xFFFF, messageId);
	}

	char szUndecoratedName[256];
	if (filename && *filename && (linenumber == SERR_LINECODE_OBJECT || linenumber == SERR_LINECODE_HANDLE))
	{
		if (SErrUndecorateTypeName(filename, szUndecoratedName, sizeof(szUndecoratedName)))
		{
			filename = szUndecoratedName;
		}
	}

	// Message for the debugger
	char szMessage[1024];
	char* pCursor = szMessage;
	if (filename)
	{
		pCursor += SStrCopy(szMessage, filename, STORM_MAX_STR);
	}
	if (linenumber > 0)
	{
		wsprintfA(pCursor, "(%u)", linenumber);
		pCursor += SStrLen(pCursor);
	}
	wsprintfA(pCursor, " : error %u: ", messageId & 0xFFFF);
	pCursor += SStrLen(pCursor);
	SStrCopy(pCursor, szErrorString, STORM_MAX_STR);
	OutputDebugStringA(szMessage);

	// Message for the user
	wsprintfA(szMessage, SErrGetString(SERRSTR_HEADER), szErrorString);
	pCursor = szMessage + SStrLen(szMessage);
	wsprintfA(pCursor, SErrGetString(SERRSTR_PROGRAM), szProgramPath);
	pCursor += SStrLen(pCursor);

	if (filename && *filename)
	{
		switch (linenumber)
		{
		case SERR_LINECODE_FILE:
			wsprintfA(pCursor, SErrGetString(SERRSTR_FILE), filename);
			break;
		case SERR_LINECODE_HANDLE:
			wsprintfA(pCursor, SErrGetString(SERRSTR_HANDLE), filename);
			break;
		case SERR_LINECODE_OBJECT:
			wsprintfA(pCursor, SErrGetString(SERRSTR_OBJECT), filename);
			break;
		case SERR_LINECODE_FUNCTION:
			wsprintfA(pCursor, SErrGetString(SERRSTR_FUNCTION), filename);
			break;
		default:
			wsprintfA(pCursor, SErrGetString(SERRSTR_FILELINE), filename, linenumber);
			break;
		}
		pCursor += SStrLen(pCursor);
	}

	if (messageId == STORM_ERROR_ASSERTION)
	{
		wsprintfA(pCursor, SErrGetString(SERRSTR_EXPRESSION), description ? description : &sgszEmpty[0]);
	}
	else
	{
		wsprintfA(pCursor, SErrGetString(SERRSTR_DESCRIPTION), description ? description : &sgszEmpty[1]);
	}
	pCursor += SStrLen(pCursor);
	SStrCopy(pCursor, SErrGetString(recoverable ? SERRSTR_TERMINATE : SERRSTR_PRESS_OK), STORM_MAX_STR);

	const UINT uType = (recoverable ? MB_YESNOCANCEL : MB_OKCANCEL) | MB_ICONHAND | MB_SYSTEMMODAL | MB_SETFOREGROUND | MB_TOPMOST;
	int nResult = IDNO;
	BOOL bShowMessageBox = TRUE;
	for (HANDLER* pHandler = sgHandlerList.Head(); pHandler; pHandler = pHandler->Next())
	{
		if (!pHandler->pfnHandler(messageId, szErrorString, filename, linenumber, description ? description : &sgszEmpty[2]))
		{
			bShowMessageBox = FALSE;
			break;
		}
	}

	if (bShowMessageBox)
	{
		HWND hWnd = SMsgGetDefaultWindow();
		if (!IsWindow(hWnd) || !IsWindowVisible(hWnd))
		{
			hWnd = nullptr;
		}
		nResult = MessageBoxA(hWnd, szMessage, szProgramName, uType);
	}

	SErrLeaveCriticalSection();

	if (recoverable && nResult == IDNO)
	{
		sgbDisplayingError = FALSE;
		return TRUE;
	}

	if (nResult == IDCANCEL)
	{
		DebugBreak();
	}

	SErrSuppressErrors(TRUE);

	DWORD dwExitCode;
	if ((int32_t)GetVersion() >= 0 // Windows NT
		|| !GetExitCodeProcess(GetCurrentProcess(), &dwExitCode)
		|| dwExitCode == STILL_ACTIVE)
	{
		TerminateProcess(GetCurrentProcess(), exitcode);
	}

	sgbDisplayingError = FALSE;
	return FALSE;
}

// Storm.#462
BOOL __stdcall SErrGetErrorStr(uint32_t dwErrorCode, char* lpBuffer, uint32_t nSize)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(lpBuffer);
	STORM_VALIDATE_ARG(nSize);
	STORM_VALIDATE_END(FALSE);

	SErrEnterCriticalSection();
	if (!sgbDefaultMessageSourcesRegistered)
	{
		sgbDefaultMessageSourcesRegistered = TRUE;
		SErrRegisterDefaultMessageSources();
	}

	HMODULE hModule = nullptr;
	for (MESSAGESOURCE* pSource = sgpMessageSources; pSource; pSource = pSource->pNext)
	{
		if (pSource->nFacility == ((dwErrorCode >> 16) & 0xFFF))
		{
			hModule = pSource->hModule;
			break;
		}
	}
	SErrLeaveCriticalSection();

	*lpBuffer = '\0';
	return FormatMessageA(hModule ? FORMAT_MESSAGE_FROM_HMODULE : FORMAT_MESSAGE_FROM_SYSTEM, hModule, dwErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lpBuffer, nSize, nullptr) != 0;
}

// Storm.#463
uint32_t __cdecl SErrGetLastError()
{
	return sgdwLastError;
}

// Storm.#464
BOOL __stdcall SErrRegisterMessageSource(uint16_t nFacility, HMODULE hModule, uint32_t dwReserved)
{
	SErrEnterCriticalSection();
	MESSAGESOURCE* pSource = (MESSAGESOURCE*)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, sizeof(MESSAGESOURCE));
	pSource->nFacility = nFacility;
	pSource->hModule = hModule;
	pSource->pNext = sgpMessageSources;
	sgpMessageSources = pSource;
	SErrLeaveCriticalSection();
	return TRUE;
}

// Storm.#465
void __stdcall SErrSetLastError(uint32_t dwErrCode)
{
	sgdwLastError = dwErrCode;
	SetLastError(dwErrCode);
}

// Storm.#466
void __stdcall SErrReportNamedResourceLeak(const char* szResourceName, const char* szName)
{
	if (!sgbDebugMemoryLoaded)
	{
		sgbDebugMemoryLoaded = TRUE;
		SRegLoadValue("Internal", "Debug Memory", 0, &sgbDebugMemory);
	}

	if (!sgbDebugMemory)
	{
		return;
	}

	char szResource[256];
	if (szName && *szName)
	{
		SStrPrintf(szResource, sizeof(szResource), "%s (%s)", szResourceName, szName);
	}
	else
	{
		SStrPrintf(szResource, sizeof(szResource), "%s", szResourceName);
	}

	if (!gStormOptionReportHandleLeaksToDebugger)
	{
		SErrDisplayError(STORM_ERROR_HANDLE_NEVER_RELEASED, szResource, SERR_LINECODE_HANDLE, nullptr, TRUE, 1);
	}
	else
	{
		char szMessage[200];
		wsprintfA(szMessage, "Storm Error : handle never released -- %s\n", szResource);
		OutputDebugStringA(szMessage);
	}
}

// Storm.#467
void __stdcall SErrReportResourceLeak(const char* szResourceName)
{
	SErrReportNamedResourceLeak(szResourceName, nullptr);
}

// Storm.#468
void __stdcall SErrSuppressErrors(BOOL suppressErrors)
{
	sgbSuppressErrors = suppressErrors;
}

// Storm.#469
void __stdcall SErrRegisterHandler(SERRHANDLER pfnHandler)
{
	SErrEnterCriticalSection();
	HANDLER* pHandler = sgHandlerList.NewNode(0, 0, SMEM_KEEPONDESTROY);
	sgHandlerList.LinkToHead(pHandler);
	pHandler->pfnHandler = pfnHandler;
	SErrLeaveCriticalSection();
}

// Storm.#470
void __stdcall SErrUnregisterHandler(SERRHANDLER pfnHandler)
{
	SErrEnterCriticalSection();
	for (HANDLER* pHandler = sgHandlerList.Head(); pHandler; )
	{
		if (pHandler->pfnHandler == pfnHandler)
		{
			HANDLER* pNext = pHandler->Next();
			sgHandlerList.UnlinkNode(pHandler);
			SMemFree(pHandler, typeid(HANDLER).name(), SERR_LINECODE_OBJECT, 0);
			pHandler = pNext;
		}
		else
		{
			pHandler = pHandler->Next();
		}
	}
	SErrLeaveCriticalSection();
}

// Storm.#561
void SErrDisplayAppFatal(char* format, ...)
{
	const char* szFilename = nullptr;
	int32_t nLine = 0;

	SErrEnterCriticalSection();
	if (sgdwFatalThreadId == GetCurrentThreadId())
	{
		szFilename = sgszFatalFilename;
		nLine = sgnFatalLine;
		sgszFatalFilename = nullptr;
		sgnFatalLine = 0;
		sgdwFatalThreadId = 0;
	}
	SErrLeaveCriticalSection();

	char szDescription[1024];
	va_list args;
	va_start(args, format);
	vsprintf(szDescription, format, args);
	va_end(args);

	SErrDisplayError(STORM_ERROR_FATAL, szFilename, nLine, szDescription, FALSE, 1);
	ExitProcess(1);
}

// Storm.#562
int32_t __cdecl SErrDisplayErrorFmt(uint32_t messageId, const char* filename, int32_t linenumber, int32_t recoverable, uint32_t exitcode, char* format, ...)
{
	char szDescription[1024];
	va_list args;
	va_start(args, format);
	vsprintf(szDescription, format, args);
	va_end(args);

	return SErrDisplayError(messageId, filename, linenumber, szDescription, recoverable, exitcode);
}

// Storm.#563
BOOL __cdecl SErrIsDisplayingError()
{
	return sgbDisplayingError;
}

// Storm.#564
int32_t __stdcall SErrPrepareAppFatal(const char* filename, int32_t linenumber)
{
	SErrEnterCriticalSection();
	sgszFatalFilename = filename;
	sgnFatalLine = linenumber;
	sgdwFatalThreadId = GetCurrentThreadId();
	SErrLeaveCriticalSection();
	return TRUE;
}
