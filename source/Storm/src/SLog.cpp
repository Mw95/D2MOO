#include "StormInternal.h"

#include <cstdio>
#include <cstdarg>

// Log files

#define SLOG_BUCKETS          4
#define SLOG_BUFFER_SIZE      0x10000
#define SLOG_FLUSH_THRESHOLD  0xC000
#define SLOG_MAX_INDENT       128

struct LOG
{
	HSLOG hLog;                     // 0x00
	LOG* pNext;                     // 0x04
	HANDLE hFile;                   // 0x08
	uint32_t nBufferUsed;           // 0x0C
	uint32_t nBufferCommitted;      // 0x10 Data before this offset was written with SLogWrite (vs. SLogPend)
	int32_t nIndent;                // 0x14
	BOOL bTimestamps;               // 0x18
	char szBuffer[SLOG_BUFFER_SIZE];// 0x1C
};

#define SLOG_LOCK_NONE ((uint32_t)-1)

// Storm.0x6FFEA3D0
static CRITICAL_SECTION sgLogCritSects[SLOG_BUCKETS];
// Storm.0x6FFEA430
static char sgszTimestamp[64];
// Storm.0x6FFEA470
static LOG* sgpLogBuckets[SLOG_BUCKETS];
// Storm.0x6FFEA480
static uint32_t sgnLastLogId;
// Storm.0x6FFEA484
static uint32_t sgnTimestampLength;
// Storm.0x6FFEA488
static DWORD sgdwTimestampTick;


// Storm.0x6FFCA960
// Returns the log, with its bucket locked
static LOG* SLogLock(HSLOG hLog, uint32_t* pLockedBucket, BOOL bCreate)
{
	if (hLog)
	{
		const uint32_t nBucket = (uint32_t)(uintptr_t)hLog & (SLOG_BUCKETS - 1);
		EnterCriticalSection(&sgLogCritSects[nBucket]);
		*pLockedBucket = nBucket;

		LOG** ppLink = &sgpLogBuckets[nBucket];
		for (LOG* pLog = *ppLink; pLog; pLog = pLog->pNext)
		{
			if (pLog->hLog == hLog)
			{
				return pLog;
			}
			ppLink = &pLog->pNext;
		}

		if (bCreate)
		{
			LOG* pLog = (LOG*)VirtualAlloc(nullptr, sizeof(LOG), MEM_COMMIT, PAGE_READWRITE);
			*ppLink = pLog;
			if (pLog)
			{
				pLog->hLog = hLog;
				pLog->pNext = nullptr;
				pLog->hFile = INVALID_HANDLE_VALUE;
				pLog->nBufferUsed = 0;
				pLog->nBufferCommitted = 0;
				return pLog;
			}
		}

		LeaveCriticalSection(&sgLogCritSects[nBucket]);
	}

	*pLockedBucket = SLOG_LOCK_NONE;
	return nullptr;
}

// Storm.0x6FFCAB10
static void SLogUnlock(uint32_t nBucket)
{
	LeaveCriticalSection(&sgLogCritSects[nBucket]);
}

// Storm.0x6FFCAA00
// Releases the log, and unlocks its bucket
static void SLogDelete(LOG* pLog, uint32_t nBucket)
{
	LOG** ppLink = &sgpLogBuckets[nBucket];
	for (LOG* pCurrent = *ppLink; pCurrent; pCurrent = pCurrent->pNext)
	{
		if (pCurrent == pLog)
		{
			*ppLink = pCurrent->pNext;
			VirtualFree(pCurrent, 0, MEM_RELEASE);
			break;
		}
		ppLink = &pCurrent->pNext;
	}
	LeaveCriticalSection(&sgLogCritSects[nBucket]);
}

// Storm.0x6FFCA920
static void SLogFlushBuffer(LOG* pLog)
{
	if (pLog->nBufferUsed)
	{
		DWORD dwWritten;
		WriteFile(pLog->hFile, pLog->szBuffer, pLog->nBufferUsed, &dwWritten, nullptr);
		FlushFileBuffers(pLog->hFile);
		pLog->nBufferUsed = 0;
		pLog->nBufferCommitted = 0;
	}
}

// Storm.0x6FFCAD80
static void SLogEndLine(LOG* pLog)
{
	SMemCopy(&pLog->szBuffer[pLog->nBufferUsed], "\r\n", sizeof("\r\n"));
	pLog->nBufferUsed += 2;
}

// Storm.0x6FFCAEA0
static void SLogWriteIndent(LOG* pLog)
{
	int32_t nIndent = pLog->nIndent;
	if (nIndent <= 0)
	{
		return;
	}

	if (nIndent >= SLOG_MAX_INDENT)
	{
		nIndent = SLOG_MAX_INDENT;
	}

	SMemFill(&pLog->szBuffer[pLog->nBufferUsed], nIndent, ' ');
	pLog->szBuffer[pLog->nBufferUsed + nIndent] = '\0';
	pLog->nBufferUsed += nIndent;
}

// Storm.0x6FFCADB0
static void SLogWriteLinePrefix(LOG* pLog, BOOL bWriteTimestamp)
{
	if (!pLog->bTimestamps)
	{
		return;
	}

	const DWORD dwTick = GetTickCount();
	if (dwTick != sgdwTimestampTick)
	{
		sgdwTimestampTick = dwTick;

		SYSTEMTIME localTime;
		GetLocalTime(&localTime);
		wsprintfA(sgszTimestamp, "%u/%u %02u:%02u:%02u.%03u  ",
			localTime.wMonth,
			localTime.wDay,
			localTime.wHour,
			localTime.wMinute,
			localTime.wSecond,
			localTime.wMilliseconds);
		sgnTimestampLength = SStrLen(sgszTimestamp);
	}

	if (bWriteTimestamp)
	{
		SMemCopy(&pLog->szBuffer[pLog->nBufferUsed], sgszTimestamp, sgnTimestampLength + 1);
	}
	else
	{
		SMemFill(&pLog->szBuffer[pLog->nBufferUsed], sgnTimestampLength, ' ');
		pLog->szBuffer[pLog->nBufferUsed + sgnTimestampLength] = '\0';
	}
	pLog->nBufferUsed += sgnTimestampLength;

	SLogWriteIndent(pLog);
}

// Commits the pending lines, flushing the buffer if needed
static void SLogCommit(LOG* pLog)
{
	if (gStormOptionWriteLogsToDebugger)
	{
		OutputDebugStringA(&pLog->szBuffer[pLog->nBufferCommitted]);
	}

	pLog->nBufferCommitted = pLog->nBufferUsed;
	if (pLog->nBufferUsed >= SLOG_FLUSH_THRESHOLD)
	{
		SLogFlushBuffer(pLog);
	}
}

// Storm.0x6FFCAF70
void SLogInitialize()
{
	for (CRITICAL_SECTION& critSect : sgLogCritSects)
	{
		InitializeCriticalSection(&critSect);
	}
}

// Storm.0x6FFCAB30
void SLogDestroy()
{
	SLogFlushAll();

	for (uint32_t nBucket = 0; nBucket < SLOG_BUCKETS; ++nBucket)
	{
		EnterCriticalSection(&sgLogCritSects[nBucket]);
		while (sgpLogBuckets[nBucket])
		{
			SLogClose(sgpLogBuckets[nBucket]->hLog);
			SErrReportResourceLeak("HSLOG");
		}
		LeaveCriticalSection(&sgLogCritSects[nBucket]);
	}

	for (CRITICAL_SECTION& critSect : sgLogCritSects)
	{
		DeleteCriticalSection(&critSect);
	}
}

// Storm.#541
void __stdcall SLogClose(HSLOG hLog)
{
	uint32_t nBucket;
	LOG* pLog = SLogLock(hLog, &nBucket, FALSE);
	if (pLog)
	{
		SLogFlushBuffer(pLog);
		CloseHandle(pLog->hFile);
		SLogDelete(pLog, nBucket);
	}
}

// Storm.#542
BOOL __stdcall SLogCreate(const char* filename, uint32_t flags, HSLOG* phLog)
{
	const char cFirstChar = *filename;
	if (phLog)
	{
		*phLog = nullptr;
		if (filename && cFirstChar)
		{
			HANDLE hFile = CreateFileA(filename, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return FALSE;
			}

			*phLog = (HSLOG)(uintptr_t)++sgnLastLogId;

			uint32_t nBucket;
			LOG* pLog = SLogLock(*phLog, &nBucket, TRUE);
			if (pLog)
			{
				pLog->hFile = hFile;
				pLog->bTimestamps = TRUE;
				pLog->nIndent = 0;
				SLogUnlock(nBucket);
				return TRUE;
			}

			*phLog = nullptr;
			return FALSE;
		}
	}

	SErrSetLastError(ERROR_INVALID_PARAMETER);
	return FALSE;
}

// Storm.#543
void __stdcall SLogSetTimestamps(HSLOG hLog, BOOL bEnable)
{
	uint32_t nBucket;
	LOG* pLog = SLogLock(hLog, &nBucket, FALSE);
	if (pLog)
	{
		pLog->bTimestamps = bEnable;
		SLogUnlock(nBucket);
	}
}

// Storm.#544
void __stdcall SLogDump(HSLOG hLog, const void* data, uint32_t size)
{
	uint32_t nBucket;
	LOG* pLog = SLogLock(hLog, &nBucket, FALSE);
	if (!pLog)
	{
		return;
	}

	const uint8_t* pData = (const uint8_t*)data;
	for (uint32_t nLineStart = 0; nLineStart < size; nLineStart += 8)
	{
		const uint32_t nLineEnd = nLineStart + 8;

		SLogWriteLinePrefix(pLog, FALSE);
		wsprintfA(&pLog->szBuffer[pLog->nBufferUsed], "%04x: ", nLineStart);
		pLog->nBufferUsed += SStrLen(&pLog->szBuffer[pLog->nBufferUsed]);

		// Hexadecimal values
		for (uint32_t i = nLineStart; i < nLineEnd; ++i)
		{
			if (i < size)
			{
				wsprintfA(&pLog->szBuffer[pLog->nBufferUsed], "%02x ", pData[i]);
				pLog->nBufferUsed += SStrLen(&pLog->szBuffer[pLog->nBufferUsed]);
			}
			else
			{
				pLog->nBufferUsed += SStrCopy(&pLog->szBuffer[pLog->nBufferUsed], "   ", STORM_MAX_STR);
			}

			if ((i & 3) == 3)
			{
				pLog->nBufferUsed += SStrCopy(&pLog->szBuffer[pLog->nBufferUsed], "  ", STORM_MAX_STR);
			}
		}

		// Characters
		for (uint32_t i = nLineStart; i < nLineEnd; ++i)
		{
			const char c = i < size ? (char)pData[i] : '\0';
			if (i < size && c >= ' ' && c <= '~')
			{
				wsprintfA(&pLog->szBuffer[pLog->nBufferUsed], "%c", c);
				pLog->nBufferUsed += SStrLen(&pLog->szBuffer[pLog->nBufferUsed]);
			}
			else
			{
				pLog->nBufferUsed += SStrCopy(&pLog->szBuffer[pLog->nBufferUsed], c ? "." : " ", STORM_MAX_STR);
			}

			if ((i & 7) == 3)
			{
				pLog->nBufferUsed += SStrCopy(&pLog->szBuffer[pLog->nBufferUsed], " ", STORM_MAX_STR);
			}
		}

		SLogEndLine(pLog);
	}

	SLogCommit(pLog);
	SLogUnlock(nBucket);
}

// Storm.#545
void __stdcall SLogFlush(HSLOG hLog)
{
	uint32_t nBucket;
	LOG* pLog = SLogLock(hLog, &nBucket, FALSE);
	if (pLog)
	{
		SLogFlushBuffer(pLog);
		SLogUnlock(nBucket);
	}
}

// Storm.#546
void __cdecl SLogFlushAll()
{
	for (uint32_t nBucket = 0; nBucket < SLOG_BUCKETS; ++nBucket)
	{
		EnterCriticalSection(&sgLogCritSects[nBucket]);
		for (LOG* pLog = sgpLogBuckets[nBucket]; pLog; pLog = pLog->pNext)
		{
			SLogFlushBuffer(pLog);
		}
		LeaveCriticalSection(&sgLogCritSects[nBucket]);
	}
}

// Storm.#547
// Writes a line that will be replaced by the next SLogPend or kept by SLogWrite
void __cdecl SLogPend(HSLOG hLog, const char* format, ...)
{
	uint32_t nBucket;
	LOG* pLog = SLogLock(hLog, &nBucket, FALSE);
	if (!pLog)
	{
		return;
	}

	pLog->nBufferUsed = pLog->nBufferCommitted;
	SLogWriteLinePrefix(pLog, TRUE);

	va_list args;
	va_start(args, format);
	vsprintf(&pLog->szBuffer[pLog->nBufferUsed], format, args);
	va_end(args);

	pLog->nBufferUsed += SStrLen(&pLog->szBuffer[pLog->nBufferUsed]);
	SLogEndLine(pLog);
	SLogUnlock(nBucket);
}

// Storm.#548
void __cdecl SLogWrite(HSLOG hLog, const char* format, ...)
{
	uint32_t nBucket;
	LOG* pLog = SLogLock(hLog, &nBucket, FALSE);
	if (!pLog)
	{
		return;
	}

	SLogWriteLinePrefix(pLog, TRUE);

	va_list args;
	va_start(args, format);
	vsprintf(&pLog->szBuffer[pLog->nBufferUsed], format, args);
	va_end(args);

	pLog->nBufferUsed += SStrLen(&pLog->szBuffer[pLog->nBufferUsed]);
	SLogEndLine(pLog);
	SLogCommit(pLog);
	SLogUnlock(nBucket);
}

// Storm.#549
int32_t __stdcall SLogSetIndent(HSLOG hLog, int32_t nIndent)
{
	uint32_t nBucket;
	LOG* pLog = SLogLock(hLog, &nBucket, FALSE);
	if (!pLog)
	{
		return 0;
	}

	const int32_t nPreviousIndent = pLog->nIndent;
	pLog->nIndent = nIndent;
	SLogUnlock(nBucket);
	return nPreviousIndent;
}

// Storm.#550
int32_t __stdcall SLogAdjustIndent(HSLOG hLog, int32_t nDelta)
{
	uint32_t nBucket;
	LOG* pLog = SLogLock(hLog, &nBucket, FALSE);
	if (!pLog)
	{
		return 0;
	}

	const int32_t nPreviousIndent = pLog->nIndent;
	pLog->nIndent = nPreviousIndent + nDelta;
	SLogUnlock(nBucket);
	return nPreviousIndent;
}
