#include "BnMessQueue.h"

#include <cstring>

#include <Fog.h>
#include <Storm.h>


CRITICAL_SECTION gtBnMessQueueLock;
char* gszBnMessQueueErrorText;
int32_t gnBnMessQueueError;
BnMessQueueEntry* gpBnMessQueueHead;
BnMessQueueEntry* gpBnMessQueueTail;


//Bnclient.0x6FF062D0
BOOL __stdcall BNMESSQUEUE_Initialize()
{
	gpBnMessQueueHead = nullptr;
	gpBnMessQueueTail = nullptr;
	gnBnMessQueueError = 0;
	InitializeCriticalSection(&gtBnMessQueueLock);
	return TRUE;
}

//Bnclient.0x6FF06300
BOOL __stdcall BNMESSQUEUE_Shutdown()
{
	DeleteCriticalSection(&gtBnMessQueueLock);
	return TRUE;
}

//Bnclient.0x6FF06320
BOOL __fastcall BNMESSQUEUE_PushData(int32_t nType, const void* pData, uint32_t nSize)
{
	BnMessQueueEntry* ptNew = (BnMessQueueEntry*)D2_ALLOC(sizeof(BnMessQueueEntry));

	uint32_t nBytes = nSize;
	if (nBytes > sizeof(ptNew->szText))
	{
		nBytes = sizeof(ptNew->szText);
	}

	if (nBytes)
	{
		memcpy(ptNew->szText, pData, nBytes);
	}
	else
	{
		ptNew->szText[0] = '\0';
	}

	ptNew->dwBytes = nBytes;
	ptNew->nType = nType;
	ptNew->pNext = nullptr;

	D2_ASSERT(ptNew->dwBytes <= ARRAYSIZE(ptNew->szText));

	EnterCriticalSection(&gtBnMessQueueLock);
	if (!gpBnMessQueueHead)
	{
		gpBnMessQueueHead = ptNew;
	}
	else
	{
		gpBnMessQueueTail->pNext = ptNew;
	}
	gpBnMessQueueTail = ptNew;
	LeaveCriticalSection(&gtBnMessQueueLock);

	return TRUE;
}

//Bnclient.0x6FF063F0
BOOL __fastcall BNMESSQUEUE_PushString(int32_t nType, const char* szText)
{
	BnMessQueueEntry* ptNew = (BnMessQueueEntry*)D2_ALLOC(sizeof(BnMessQueueEntry));

	SStrCopy(ptNew->szText, szText, sizeof(ptNew->szText));
	ptNew->nType = nType;
	ptNew->dwBytes = strlen(ptNew->szText) + 1;
	ptNew->pNext = nullptr;

	D2_ASSERT(ptNew->dwBytes <= ARRAYSIZE(ptNew->szText));

	EnterCriticalSection(&gtBnMessQueueLock);
	if (!gpBnMessQueueHead)
	{
		gpBnMessQueueHead = ptNew;
	}
	else
	{
		gpBnMessQueueTail->pNext = ptNew;
	}
	gpBnMessQueueTail = ptNew;
	LeaveCriticalSection(&gtBnMessQueueLock);

	return TRUE;
}

//Bnclient.0x6FF064A0
uint32_t __fastcall BNMESSQUEUE_Read(int32_t* pType, void* pBuffer)
{
	EnterCriticalSection(&gtBnMessQueueLock);

	BnMessQueueEntry* pEntry = gpBnMessQueueHead;
	if (!pEntry)
	{
		LeaveCriticalSection(&gtBnMessQueueLock);
		return 0;
	}

	memcpy(pBuffer, pEntry->szText, pEntry->dwBytes);
	*pType = pEntry->nType;

	const uint32_t nBytes = pEntry->dwBytes;
	BnMessQueueEntry* pNext = pEntry->pNext;
	D2_FREE(gpBnMessQueueHead);
	gpBnMessQueueHead = pNext;

	LeaveCriticalSection(&gtBnMessQueueLock);
	return nBytes;
}

//Bnclient.0x6FF06530
BOOL __stdcall BNMESSQUEUE_Clear()
{
	EnterCriticalSection(&gtBnMessQueueLock);

	BnMessQueueEntry* pEntry = gpBnMessQueueHead;
	while (pEntry)
	{
		BnMessQueueEntry* pNext = pEntry->pNext;
		D2_FREE(pEntry);
		pEntry = pNext;
		gpBnMessQueueHead = pEntry;
	}

	LeaveCriticalSection(&gtBnMessQueueLock);
	return TRUE;
}

//Bnclient.0x6FF06580
BOOL __fastcall BNMESSQUEUE_SetErrorIfNone(int32_t nError)
{
	EnterCriticalSection(&gtBnMessQueueLock);
	if (!gnBnMessQueueError)
	{
		gnBnMessQueueError = nError;
	}
	LeaveCriticalSection(&gtBnMessQueueLock);
	return TRUE;
}

//Bnclient.0x6FF065B0
BOOL __fastcall BNMESSQUEUE_SetError(int32_t nError)
{
	EnterCriticalSection(&gtBnMessQueueLock);
	gnBnMessQueueError = nError;
	LeaveCriticalSection(&gtBnMessQueueLock);
	return TRUE;
}

//Bnclient.0x6FF065E0
BOOL __fastcall BNMESSQUEUE_SetErrorText(char* szErrorText)
{
	EnterCriticalSection(&gtBnMessQueueLock);
	gszBnMessQueueErrorText = szErrorText;
	LeaveCriticalSection(&gtBnMessQueueLock);
	return TRUE;
}

//Bnclient.0x6FF06610
BOOL __fastcall BNMESSQUEUE_GetLastError(BnMessQueueErrorInfo* errInfo)
{
	D2_ASSERT(errInfo != NULL);

	EnterCriticalSection(&gtBnMessQueueLock);
	errInfo->nError = gnBnMessQueueError;
	errInfo->szErrorText = gszBnMessQueueErrorText;
	gnBnMessQueueError = 0;
	LeaveCriticalSection(&gtBnMessQueueLock);
	return TRUE;
}

//Bnclient.0x6FF06670
BOOL __fastcall BNMESSQUEUE_PeekLastError(BnMessQueueErrorInfo* errInfo)
{
	EnterCriticalSection(&gtBnMessQueueLock);
	errInfo->nError = gnBnMessQueueError;
	errInfo->szErrorText = gszBnMessQueueErrorText;
	LeaveCriticalSection(&gtBnMessQueueLock);
	return TRUE;
}
