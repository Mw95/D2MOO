#include <LogManager.h>
#include <Storm.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define LOG_MAX_OPEN_FILES 20
#define LOG_MAX_FILE_SUBNAME 16
#define LOG_MESSAGE_MAX_SIZE 0x1000

enum LogMessageType : int32_t
{
	LOG_TYPE_MESSAGE = 1,
	LOG_TYPE_MEMORY = 2,
};

// Memory dump description, stored after the file sub name of a LOG_TYPE_MEMORY message
struct LogMemoryDump					// sizeof 0x14
{
	const uint8_t* pMemory;				// 0x00
	uint32_t nByteCount;				// 0x04
	BOOL bLogOffset;					// 0x08
	BOOL bNoCopy;						// 0x0C Dump pMemory instead of the copy following the message
	BOOL bShowASCII;					// 0x10
	// Message follows, then the copy of the memory
};

struct LogMessage						// sizeof 0x24 + strings
{
	LogMessage* pNext;					// 0x00 The original code uses a Storm TSList
	LogMessage* pPrevious;				// 0x04
	uint32_t nSize;						// 0x08
	LogMessageType nType;				// 0x0C
	BOOL bWithTime;						// 0x10
	SYSTEMTIME tTime;					// 0x14
	// File sub name follows, then the message (or the LogMemoryDump)
};

struct LogLocks
{
	// Fog.0x6FFA1308
	CRITICAL_SECTION tQueueLock;
	// Fog.0x6FFA1574
	CRITICAL_SECTION tFilesLock;

	LogLocks()
	{
		InitializeCriticalSection(&tQueueLock);
		InitializeCriticalSection(&tFilesLock);
	}

	~LogLocks()
	{
		DeleteCriticalSection(&tFilesLock);
		DeleteCriticalSection(&tQueueLock);
	}

	LogLocks(const LogLocks&) = delete;
	LogLocks& operator=(const LogLocks&) = delete;
};
static LogLocks gtLogLocks;

// Fog.0x6FFA12FC
static LogMessage* gpLogQueueHead;
static LogMessage* gpLogQueueTail;
// Fog.0x6FFA1570
static int32_t gnLogQueueCount;
// Fog.0x6FFA1510
static uint32_t gnLogQueueBytes;
// Fog.0x6FFA1320
static BOOL s_Initialized;
// Fog.0x6FFA1514
static volatile BOOL gbLogThreadStopping;
// Fog.0x6FFA14B8
static HANDLE ghLogThread;
// Fog.0x6FFA1518
static DWORD gdwLogThreadId;
// Fog.0x6FFA158C
static SYSTEMTIME gtStartupTime;

// Fog.0x6FF777E8
static char gszLogPrefix[MAX_PATH] = "D2";

// Fog.0x6FFA1378
static char s_LastFileName[LOG_MAX_OPEN_FILES][LOG_MAX_FILE_SUBNAME];
// Fog.0x6FFA14C0
static FILE* gpLogFiles[LOG_MAX_OPEN_FILES];
// Fog.0x6FFA1328
static DWORD gdwLogFileOpenTime[LOG_MAX_OPEN_FILES];
// Fog.0x6FFA15A0
static DWORD gdwLogFileLastUseTime[LOG_MAX_OPEN_FILES];
// Fog.0x6FFA1520
static BOOL gbLogFileFirstOpen[LOG_MAX_OPEN_FILES];
// Fog.0x6FFA12F8
static DWORD gdwLastLogCleanupTime;

static void LOG_PushMessage(LogMessage* pMessage)
{
	EnterCriticalSection(&gtLogLocks.tQueueLock);
	pMessage->pNext = nullptr;
	pMessage->pPrevious = gpLogQueueTail;
	if (gpLogQueueTail)
	{
		gpLogQueueTail->pNext = pMessage;
	}
	else
	{
		gpLogQueueHead = pMessage;
	}
	gpLogQueueTail = pMessage;
	++gnLogQueueCount;
	gnLogQueueBytes += pMessage->nSize;
	LeaveCriticalSection(&gtLogLocks.tQueueLock);
}

// Must be called with the queue lock held
static LogMessage* LOG_PopMessage()
{
	LogMessage* pMessage = gpLogQueueHead;
	if (!pMessage)
	{
		return nullptr;
	}

	gpLogQueueHead = pMessage->pNext;
	if (gpLogQueueHead)
	{
		gpLogQueueHead->pPrevious = nullptr;
	}
	else
	{
		gpLogQueueTail = nullptr;
	}
	--gnLogQueueCount;
	gnLogQueueBytes -= pMessage->nSize;
	return pMessage;
}

static LogMessage* LOG_AllocMessage(uint32_t nExtraSize, LogMessageType nType, BOOL bWithTime)
{
	LogMessage* pMessage = (LogMessage*)SMemAlloc(sizeof(LogMessage) + nExtraSize, __FILE__, __LINE__, 0);
	pMessage->nSize = sizeof(LogMessage) + nExtraSize;
	pMessage->nType = nType;
	pMessage->bWithTime = bWithTime;
	GetLocalTime(&pMessage->tTime);
	return pMessage;
}

static void LOG_FreeMessage(LogMessage* pMessage)
{
	SMemFree(pMessage, "delete", -1, 0);
}

// 1.10f: 0x6FF625F0
static void LOG_QueueMessage(const char* szFileSubName, BOOL bWithTime, BOOL bAddNewLine, const char* szFormat, va_list args)
{
	if (gbLogThreadStopping || !s_Initialized)
	{
		return;
	}

	char szMessage[LOG_MESSAGE_MAX_SIZE];
	_vsnprintf(szMessage, sizeof(szMessage), szFormat, args);
	szMessage[sizeof(szMessage) - 1] = '\0';
	if (bAddNewLine == TRUE)
	{
		SStrNCat(szMessage, "\n", sizeof(szMessage));
	}

	const uint32_t nSubNameSize = SStrLen(szFileSubName) + 1;
	const uint32_t nStringsSize = nSubNameSize + SStrLen(szMessage) + 1;
	LogMessage* pMessage = LOG_AllocMessage(nStringsSize, LOG_TYPE_MESSAGE, bWithTime == TRUE);
	char* szMessageFileSubName = (char*)&pMessage[1];
	SStrCopy(szMessageFileSubName, szFileSubName, nStringsSize);
	SStrCopy(szMessageFileSubName + SStrLen(szMessageFileSubName) + 1, szMessage, nStringsSize);
	LOG_PushMessage(pMessage);
}

static void LOG_WriteSeparator(FILE* pFile)
{
	fprintf(pFile, "---------------------------------------------------------------\n");
}

// 1.10f: 0x6FF62820
// Returns the log file for this sub name, opening it if needed. Must be called with the files lock held.
static FILE* LOG_GetFile(const char* szFileSubName, int* pFileIndex)
{
	const DWORD dwNow = GetTickCount();
	int nFirstFreeSlot = -1;
	int nFirstClosedSlot = -1;
	int nLeastRecentlyUsedSlot = 1;

	// Slot 0 is reserved to the default log file (empty sub name)
	int nSlot = szFileSubName[0] ? 1 : 0;
	for (; nSlot < LOG_MAX_OPEN_FILES; ++nSlot)
	{
		if (!strcmp(s_LastFileName[nSlot], szFileSubName))
		{
			break;
		}

		if (!s_LastFileName[nSlot][0])
		{
			if (nFirstFreeSlot < 0)
			{
				nFirstFreeSlot = nSlot;
			}
		}
		else if (!gpLogFiles[nSlot])
		{
			// Note: the original code compares the age of the slot with the last use time of the other slot
			if (nFirstClosedSlot < 0 || dwNow - gdwLogFileLastUseTime[nSlot] > gdwLogFileLastUseTime[nFirstClosedSlot])
			{
				nFirstClosedSlot = nSlot;
			}
		}
		else if (dwNow - gdwLogFileLastUseTime[nSlot] > dwNow - gdwLogFileLastUseTime[nLeastRecentlyUsedSlot])
		{
			nLeastRecentlyUsedSlot = nSlot;
		}
	}

	if (nSlot < LOG_MAX_OPEN_FILES)
	{
		if (gpLogFiles[nSlot])
		{
			if (pFileIndex)
			{
				*pFileIndex = nSlot;
			}
			return gpLogFiles[nSlot];
		}
	}
	else if (nFirstFreeSlot >= 0)
	{
		nSlot = nFirstFreeSlot;
	}
	else
	{
		nSlot = nFirstClosedSlot >= 0 ? nFirstClosedSlot : nLeastRecentlyUsedSlot;
		if (gpLogFiles[nSlot])
		{
			fclose(gpLogFiles[nSlot]);
			gpLogFiles[nSlot] = nullptr;
		}
	}

	D2_ASSERT(SStrLen(szFileSubName) < LOG_MAX_FILE_SUBNAME);
	strcpy(s_LastFileName[nSlot], szFileSubName);

	SYSTEMTIME tTime;
	GetLocalTime(&tTime);
	char szFileName[MAX_PATH];
	SStrPrintf(szFileName, sizeof(szFileName), (char*)"%s%s%02d%02d%02d.txt", gszLogPrefix, szFileSubName, tTime.wYear % 100, tTime.wMonth, tTime.wDay);

	BOOL bNewFile = TRUE;
	if (FILE* pExistingFile = fopen(szFileName, "r"))
	{
		fclose(pExistingFile);
		bNewFile = FALSE;
	}

	FILE* pFile = fopen(szFileName, "a");
	gdwLogFileOpenTime[nSlot] = dwNow;
	gdwLogFileLastUseTime[nSlot] = dwNow;
	gpLogFiles[nSlot] = pFile;

	if (pFile && (gbLogFileFirstOpen[nSlot] || bNewFile))
	{
		char szComputerName[64];
		DWORD dwComputerNameSize = sizeof(szComputerName);
		if (!GetComputerNameA(szComputerName, &dwComputerNameSize))
		{
			szComputerName[0] = '\0';
		}

		LOG_WriteSeparator(pFile);
		if (gbLogFileFirstOpen[nSlot])
		{
			fprintf(pFile, "%s Realm startup at %04d-%02d-%02d %02d:%02d:%02d.%03u\n", szComputerName,
				gtStartupTime.wYear, gtStartupTime.wMonth, gtStartupTime.wDay, gtStartupTime.wHour, gtStartupTime.wMinute, gtStartupTime.wSecond, gtStartupTime.wMilliseconds);
			gbLogFileFirstOpen[nSlot] = FALSE;
		}
		else
		{
			fprintf(pFile, "%s %04d-%02d-%02d\n", szComputerName, tTime.wYear, tTime.wMonth, tTime.wDay);
		}
		LOG_WriteSeparator(pFile);
	}

	if (pFile && pFileIndex)
	{
		*pFileIndex = nSlot;
	}
	return pFile;
}

// 1.10f: 0x6FF62770
static void LOG_WriteMessage(LogMessage* pMessage)
{
	D2_ASSERT(pMessage->nType == LOG_TYPE_MESSAGE);
	const char* szFileSubName = (const char*)&pMessage[1];
	const char* szMessage = szFileSubName + SStrLen(szFileSubName) + 1;

	int nFileIndex;
	FILE* pFile = LOG_GetFile(szFileSubName, &nFileIndex);
	if (!pFile)
	{
		return;
	}

	if (pMessage->bWithTime)
	{
		fprintf(pFile, "%02d:%02d:%02d.%03d  ", pMessage->tTime.wHour, pMessage->tTime.wMinute, pMessage->tTime.wSecond, pMessage->tTime.wMilliseconds);
	}
	fwrite(szMessage, SStrLen(szMessage), 1, pFile);
	gdwLogFileLastUseTime[nFileIndex] = GetTickCount();
}

// 1.10f: 0x6FF62C00
static void LOG_WriteMemoryDump(LogMessage* pMessage)
{
	D2_ASSERT(pMessage->nType == LOG_TYPE_MEMORY);
	const char* szFileSubName = (const char*)&pMessage[1];
	const LogMemoryDump* pDump = (const LogMemoryDump*)(szFileSubName + SStrLen(szFileSubName) + 1);
	const char* szMessage = (const char*)&pDump[1];
	const uint8_t* pData = pDump->bNoCopy ? pDump->pMemory : (const uint8_t*)szMessage + SStrLen(szMessage) + 1;

	int nFileIndex;
	FILE* pFile = LOG_GetFile(szFileSubName, &nFileIndex);
	if (!pFile)
	{
		return;
	}

	char szTimePrefix[32];
	SStrPrintf(szTimePrefix, sizeof(szTimePrefix), (char*)"%02d:%02d:%02d.%03d  ", pMessage->tTime.wHour, pMessage->tTime.wMinute, pMessage->tTime.wSecond, pMessage->tTime.wMilliseconds);
	char szBlankPrefix[32];
	SStrCopy(szBlankPrefix, "              ", sizeof(szBlankPrefix));

	BOOL bFirstLine = TRUE;
	const uint8_t* pCurrent = pData;
	uint32_t nRemaining = pDump->nByteCount;
	while (nRemaining)
	{
		const uint32_t nOffset = pCurrent - pData;
		const uint32_t nAddress = pDump->bLogOffset ? nOffset : (uint32_t)(uintptr_t)pDump->pMemory + nOffset;
		fprintf(pFile, pDump->bLogOffset ? "%s%s%04X:" : "%s%s%08X:", bFirstLine ? szTimePrefix : szBlankPrefix, szMessage, nAddress);
		bFirstLine = FALSE;

		const uint32_t nLineSize = nRemaining < 16 ? nRemaining : 16;
		char szLine[256];
		szLine[0] = '\0';
		if (IsBadReadPtr(pCurrent, nLineSize))
		{
			SStrCopy(szLine, "<unreadable>", 0x7FFFFFFF);
		}
		else
		{
			for (uint32_t i = 0; i < nLineSize; ++i)
			{
				const size_t nLength = strlen(szLine);
				SStrPrintf(&szLine[nLength], sizeof(szLine) - nLength, (char*)((i & 3) ? "%02X" : " %02X"), pCurrent[i]);
			}

			if (pDump->bShowASCII)
			{
				// Align the ASCII column
				for (uint32_t nPadding = ((0x90 - 9 * nLineSize) >> 2) + 2; nPadding; --nPadding)
				{
					SStrNCat(szLine, " ", sizeof(szLine));
				}

				size_t nLength = strlen(szLine);
				for (uint32_t i = 0; i < nLineSize; ++i)
				{
					const char nChar = (char)pCurrent[i];
					szLine[nLength++] = (nChar & 0x7F) < ' ' ? '.' : nChar;
				}
				szLine[nLength] = '\0';
			}
		}

		fprintf(pFile, "%s\n", szLine);
		pCurrent += nLineSize;
		nRemaining -= nLineSize;
	}
}

// 1.10f: 0x6FF62E60
// Closes the files that have been open for more than 15 seconds or unused for 5 seconds. Must be called with the files lock held.
static void LOG_CloseIdleFiles()
{
	const DWORD dwNow = GetTickCount();
	for (int i = 0; i < LOG_MAX_OPEN_FILES; ++i)
	{
		if (gpLogFiles[i] && (dwNow - gdwLogFileOpenTime[i] > 15000 || dwNow - gdwLogFileLastUseTime[i] > 5000))
		{
			fclose(gpLogFiles[i]);
			gpLogFiles[i] = nullptr;
		}
	}
}

// 1.10f: 0x6FF63010
// Deletes the log file if its date is older than about 6 days
static void LOG_CleanBackupFile(const FILETIME* pNow, const char* szFilePath)
{
	const int nDateOffset = (int)SStrLen(szFilePath) - 10;
	if (nDateOffset <= 0)
	{
		return;
	}

	int nYear = 0;
	int nMonth = 0;
	int nDay = 0;
	sscanf(&szFilePath[nDateOffset], "%2d%2d%2d", &nYear, &nMonth, &nDay);

	SYSTEMTIME tFileTime = {};
	tFileTime.wYear = (WORD)(nYear > 90 ? nYear + 1900 : nYear + 2000);
	tFileTime.wMonth = (WORD)nMonth;
	tFileTime.wDay = (WORD)nDay;
	FILETIME tFileDate;
	SystemTimeToFileTime(&tFileTime, &tFileDate);

	if (pNow->dwHighDateTime >= tFileDate.dwHighDateTime && pNow->dwHighDateTime - tFileDate.dwHighDateTime >= 0x4B7)
	{
		FOG_TraceF("", "CleanBackupFile: deleting %s", szFilePath);
		DeleteFileA(szFilePath);
	}
}

// 1.10f: 0x6FF62ED0
// Once a day, deletes the old log files. Must be called with the files lock held.
static void LOG_CleanOldLogFiles()
{
	if (gdwLastLogCleanupTime && GetTickCount() - gdwLastLogCleanupTime < 24 * 60 * 60 * 1000)
	{
		return;
	}

	gdwLastLogCleanupTime = GetTickCount();
	LeaveCriticalSection(&gtLogLocks.tFilesLock);
	FOG_FlushLogs();
	EnterCriticalSection(&gtLogLocks.tFilesLock);

	SYSTEMTIME tNow;
	GetLocalTime(&tNow);
	FILETIME tNowFileTime;
	SystemTimeToFileTime(&tNow, &tNowFileTime);

	char szDirectory[MAX_PATH];
	szDirectory[0] = '\0';
	if (LOG_GetModuleDirectory(szDirectory, sizeof(szDirectory)))
	{
		SStrNCat(szDirectory, "\\", sizeof(szDirectory));
		FOG_CreatePathHierarchy(szDirectory);
	}

	char szSearchPattern[MAX_PATH];
	SStrPrintf(szSearchPattern, sizeof(szSearchPattern), (char*)"%sd2*.txt", szDirectory);
	WIN32_FIND_DATAA tFindData;
	const HANDLE hFind = FindFirstFileA(szSearchPattern, &tFindData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		char szFilePath[MAX_PATH];
		SStrPrintf(szFilePath, sizeof(szFilePath), (char*)"%s%s", szDirectory, tFindData.cFileName);
		LOG_CleanBackupFile(&tNowFileTime, szFilePath);
	}
	while (FindNextFileA(hFind, &tFindData));
	FindClose(hFind);
}

// 1.10f: 0x6FF62470
static DWORD WINAPI LOG_ThreadProc(LPVOID lpParameter)
{
	DWORD dwStopTime = 0;
	while (true)
	{
		EnterCriticalSection(&gtLogLocks.tQueueLock);
		LogMessage* pMessage = LOG_PopMessage();
		LeaveCriticalSection(&gtLogLocks.tQueueLock);

		if (gbLogThreadStopping)
		{
			if (!dwStopTime)
			{
				dwStopTime = GetTickCount();
			}

			// Write the remaining messages, for at most 15 seconds
			if (!pMessage || GetTickCount() - dwStopTime >= 15000)
			{
				if (pMessage)
				{
					LOG_FreeMessage(pMessage);
				}
				return TRUE;
			}
		}

		DWORD dwSleepTime = 50;
		if (pMessage)
		{
			dwSleepTime = 0;
			EnterCriticalSection(&gtLogLocks.tFilesLock);
			if (pMessage->nType == LOG_TYPE_MESSAGE)
			{
				LOG_WriteMessage(pMessage);
			}
			else if (pMessage->nType == LOG_TYPE_MEMORY)
			{
				LOG_WriteMemoryDump(pMessage);
			}
			LeaveCriticalSection(&gtLogLocks.tFilesLock);
			LOG_FreeMessage(pMessage);
		}

		if (!gbLogThreadStopping)
		{
			Sleep(dwSleepTime);
			EnterCriticalSection(&gtLogLocks.tFilesLock);
			LOG_CloseIdleFiles();
			LOG_CleanOldLogFiles();
			LeaveCriticalSection(&gtLogLocks.tFilesLock);
		}
	}
}

// 1.10f: 0x6FF61CB0
void LOG_Initialize()
{
	gbLogThreadStopping = FALSE;
	ghLogThread = CreateThread(nullptr, 0, LOG_ThreadProc, nullptr, 0, &gdwLogThreadId);
	s_Initialized = TRUE;
	GetLocalTime(&gtStartupTime);
	for (BOOL& bFirstOpen : gbLogFileFirstOpen)
	{
		bFirstOpen = TRUE;
	}
}

// 1.10f: 0x6FF61D00
void LOG_Shutdown()
{
	gbLogThreadStopping = TRUE;
	WaitForSingleObject(ghLogThread, 30000);
	CloseHandle(ghLogThread);

	EnterCriticalSection(&gtLogLocks.tQueueLock);
	while (LogMessage* pMessage = LOG_PopMessage())
	{
		LOG_FreeMessage(pMessage);
	}
	gnLogQueueCount = 0;
	gnLogQueueBytes = 0;
	ghLogThread = nullptr;
	gdwLogThreadId = 0;
	s_Initialized = FALSE;
	gbLogThreadStopping = FALSE;
	LeaveCriticalSection(&gtLogLocks.tQueueLock);
}

// 1.10f: 0x6FF5FA60
BOOL __fastcall LOG_GetModuleDirectory(char* szPath, size_t nSize)
{
	szPath[0] = '\0';
	if (!GetModuleFileNameA(nullptr, szPath, nSize))
	{
		return FALSE;
	}

	int nIndex = (int)strlen(szPath) - 1;
	while (nIndex > 0 && szPath[nIndex] != '\\' && szPath[nIndex] != '/' && szPath[nIndex] != ':')
	{
		--nIndex;
	}

	if (nIndex <= 0)
	{
		return FALSE;
	}

	// Keep the drive separator
	if (szPath[nIndex] == ':')
	{
		++nIndex;
	}
	szPath[nIndex] = '\0';
	return TRUE;
}

// 1.10f: 0x6FF61D90 (#10021)
// Log files are written in the directory of the executable, prefixed by szLogPrefix
int __fastcall FOG_SetLogPrefix(const char* szLogPrefix)
{
	char szDirectory[MAX_PATH];
	szDirectory[0] = '\0';
	if (LOG_GetModuleDirectory(szDirectory, sizeof(szDirectory)))
	{
		SStrNCat(szDirectory, "\\", sizeof(szDirectory));
		FOG_CreatePathHierarchy(szDirectory);
	}
	return SStrPrintf(gszLogPrefix, sizeof(gszLogPrefix), (char*)"%s%s", szDirectory, szLogPrefix);
}

// 1.10f: 0x6FF620A0 (#10029)
void __cdecl FOG_Trace(const char* szFormat, ...)
{
	D2_ASSERT(szFormat);
	va_list args;
	va_start(args, szFormat);
	LOG_QueueMessage("", TRUE, TRUE, szFormat, args);
	va_end(args);
}

// 1.10f: 0x6FF620E0 (#10030)
void __cdecl FOG_TraceF(const char* pFileSubName, const char* szFormat, ...)
{
	D2_ASSERT(szFormat);
	va_list args;
	va_start(args, szFormat);
	LOG_QueueMessage(pFileSubName ? pFileSubName : "", TRUE, TRUE, szFormat, args);
	va_end(args);
}

// 1.10f: 0x6FF62130
void __cdecl LOG_TraceFNoNewLine(const char* szFileSubName, const char* szFormat, ...)
{
	D2_ASSERT(szFormat);
	va_list args;
	va_start(args, szFormat);
	LOG_QueueMessage(szFileSubName ? szFileSubName : "", TRUE, FALSE, szFormat, args);
	va_end(args);
}

// 1.10f: 0x6FF62180 (#10031)
void __cdecl FOG_TraceAppend(const char* szFormat, ...)
{
	D2_ASSERT(szFormat);
	va_list args;
	va_start(args, szFormat);
	LOG_QueueMessage("", FALSE, FALSE, szFormat, args);
	va_end(args);
}

// 1.10f: 0x6FF621C0 (#10238)
void __cdecl FOG_TraceFAppend(const char* szFileSubName, const char* szFormat, ...)
{
	D2_ASSERT(szFormat);
	va_list args;
	va_start(args, szFormat);
	LOG_QueueMessage(szFileSubName ? szFileSubName : "", FALSE, FALSE, szFormat, args);
	va_end(args);
}

// 1.10f: 0x6FF62210 (#10032)
// Logs an hexadecimal dump of the memory, 16 bytes per line.
// Unless bNoCopy is set, the memory is copied so that it can be logged asynchronously.
void __cdecl FOG_TraceMemory(const char* pFileSubName, const char* szMessage, void* pMemory, size_t nByteCount, BOOL bLogOffset, BOOL bNoCopy, BOOL bNoASCII)
{
	if (gbLogThreadStopping || !s_Initialized)
	{
		return;
	}

	if (!bNoCopy && IsBadReadPtr(pMemory, nByteCount))
	{
		bNoCopy = TRUE;
	}

	const uint32_t nSubNameSize = SStrLen(pFileSubName) + 1;
	const uint32_t nMessageSize = SStrLen(szMessage) + 1;
	const uint32_t nExtraSize = nSubNameSize + sizeof(LogMemoryDump) + nMessageSize + (bNoCopy ? 0 : nByteCount);
	LogMessage* pLogMessage = LOG_AllocMessage(nExtraSize, LOG_TYPE_MEMORY, TRUE);

	char* szMessageFileSubName = (char*)&pLogMessage[1];
	SStrCopy(szMessageFileSubName, pFileSubName, 0x7FFFFFFF);
	LogMemoryDump* pDump = (LogMemoryDump*)(szMessageFileSubName + nSubNameSize);
	pDump->pMemory = (const uint8_t*)pMemory;
	pDump->nByteCount = nByteCount;
	pDump->bLogOffset = bLogOffset;
	pDump->bNoCopy = bNoCopy;
	pDump->bShowASCII = !bNoASCII;

	char* szDumpMessage = (char*)&pDump[1];
	SStrCopy(szDumpMessage, szMessage, 0x7FFFFFFF);
	if (!bNoCopy)
	{
		memcpy(szDumpMessage + nMessageSize, pMemory, nByteCount);
	}
	LOG_PushMessage(pLogMessage);
}

// 1.10f: 0x6FF623A0 (#10040)
void __fastcall FOG_FlushLogs()
{
	D2_ASSERT(s_Initialized);

	const DWORD dwStartTime = GetTickCount();
	while (GetTickCount() - dwStartTime < 1000)
	{
		EnterCriticalSection(&gtLogLocks.tQueueLock);
		const BOOL bHasPendingMessages = gpLogQueueHead != nullptr;
		LeaveCriticalSection(&gtLogLocks.tQueueLock);
		if (!bHasPendingMessages)
		{
			break;
		}
		Sleep(10);
	}

	for (FILE*& pFile : gpLogFiles)
	{
		EnterCriticalSection(&gtLogLocks.tFilesLock);
		if (pFile)
		{
			fclose(pFile);
			pFile = nullptr;
		}
		LeaveCriticalSection(&gtLogLocks.tFilesLock);
	}
}

static void LOG_CloseFileBySubName(const char* szFileSubName)
{
	for (int i = 0; i < LOG_MAX_OPEN_FILES; ++i)
	{
		if (gpLogFiles[i] && !strcmp(s_LastFileName[i], szFileSubName))
		{
			fclose(gpLogFiles[i]);
			gpLogFiles[i] = nullptr;
			return;
		}
	}
}

static FILE* LOG_OpenFileForReading(const char* szFileSubName)
{
	SYSTEMTIME tTime;
	GetLocalTime(&tTime);
	char szFileName[MAX_PATH];
	SStrPrintf(szFileName, sizeof(szFileName), (char*)"%s%s%02d%02d%02d.txt", gszLogPrefix, szFileSubName, tTime.wYear % 100, tTime.wMonth, tTime.wDay);
	return fopen(szFileName, "r");
}

// 1.10f: 0x6FF61E00 (#10234)
int __fastcall FOG_GetLogFileSize(const char* szFileSubName)
{
	int nSize = 0;
	EnterCriticalSection(&gtLogLocks.tFilesLock);
	LOG_CloseFileBySubName(szFileSubName);
	if (FILE* pFile = LOG_OpenFileForReading(szFileSubName))
	{
		fseek(pFile, 0, SEEK_END);
		nSize = ftell(pFile);
		fclose(pFile);
	}
	LeaveCriticalSection(&gtLogLocks.tFilesLock);
	return nSize;
}

// 1.10f: 0x6FF61F20 (#10235)
char* __fastcall FOG_ReadLogFile(const char* szFileSubName, int nStart, int nEnd)
{
	const int nSize = nEnd - nStart;
	char* pBuffer = (char*)FOG_Alloc(nSize + 1, __FILE__, __LINE__, 0);
	memset(pBuffer, 0, nSize + 1);

	EnterCriticalSection(&gtLogLocks.tFilesLock);
	LOG_CloseFileBySubName(szFileSubName);
	if (FILE* pFile = LOG_OpenFileForReading(szFileSubName))
	{
		if (!fseek(pFile, nStart, SEEK_SET))
		{
			fread(pBuffer, 1, nSize, pFile);
		}
		fclose(pFile);
	}
	LeaveCriticalSection(&gtLogLocks.tFilesLock);
	return pBuffer;
}
