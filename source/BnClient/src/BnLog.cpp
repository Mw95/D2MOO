// Made up filename

#include "BnLog.h"

#include <cstdarg>
#include <cstdint>
#include <cstdio>

#include <Storm.h>


int32_t gnBnLogUnused;
CRITICAL_SECTION gtBnLogLock;
HANDLE ghBnLog;


//Bnclient.0x6FF0AC20
static void __cdecl BNLOG_CloseLog()
{
	SLogClose(ghBnLog);
}

//Bnclient.0x6FF0AC00
static void __cdecl BNLOG_CreateLog()
{
	SLogCreate("BnetLog.txt", 0, &ghBnLog);
	atexit(BNLOG_CloseLog);
}

//Bnclient.0x6FF0AC50
static void __cdecl BNLOG_DeleteLock()
{
	DeleteCriticalSection(&gtBnLogLock);
}

//Bnclient.0x6FF0AC30
static void __cdecl BNLOG_InitializeLock()
{
	InitializeCriticalSection(&gtBnLogLock);
	atexit(BNLOG_DeleteLock);
}

// Static initializers, called by the CRT in this order.
static const struct BnLogStaticInitializer
{
	BnLogStaticInitializer()
	{
		BNLOG_CreateLog();
		BNLOG_InitializeLock();
	}
} gtBnLogStaticInitializer;

//Bnclient.0x6FF0ABF0
void __fastcall BNLOG_SetUnused(int32_t nValue)
{
	gnBnLogUnused = nValue;
}

//Bnclient.0x6FF0AC60
int __cdecl BNLOG_Command(int nCommand, int nValue)
{
	int nResult = 0;

	EnterCriticalSection(&gtBnLogLock);
	if (nCommand == BNLOG_COMMAND_REOPEN)
	{
		SLogClose(ghBnLog);
		SLogCreate("BnetLog.txt", 0, &ghBnLog);
		nResult = 1;
	}
	else if (nCommand == BNLOG_COMMAND_INDENT)
	{
		SLogCriticalLog(ghBnLog, nValue);
	}
	LeaveCriticalSection(&gtBnLogLock);

	return nResult;
}

//Bnclient.0x6FF0ACD0
void __cdecl BNLOG_Printf(const char* szFormat, ...)
{
	char szBuffer[512];

	EnterCriticalSection(&gtBnLogLock);

	va_list va;
	va_start(va, szFormat);
	_vsnprintf(szBuffer, sizeof(szBuffer), szFormat, va);
	va_end(va);
	szBuffer[sizeof(szBuffer) - 1] = '\0';

	SLogWrite(ghBnLog, szBuffer);

	LeaveCriticalSection(&gtBnLogLock);
}
