#include <D2QS.h>

#include <cstring>

// 1.10f: 0x6FF51030
void __fastcall D2QS_QueueInitialize(D2QSQueueStrc* pQueue)
{
	pQueue->pHead = nullptr;
	pQueue->pTail = nullptr;
	pQueue->bOverflow = FALSE;
	InitializeCriticalSection(&pQueue->tLock);
}

// 1.10f: 0x6FF51050
void __fastcall D2QS_QueueDestroy(D2QSQueueStrc* pQueue)
{
	EnterCriticalSection(&pQueue->tLock);
	while (D2QSQueueMessageStrc* pMessage = pQueue->pHead)
	{
		pQueue->pHead = pMessage->pNext;
		FOG_Free(pMessage, __FILE__, __LINE__, 0);
	}
	pQueue->pTail = nullptr;
	pQueue->pHead = nullptr;
	// Note: the original deletes the critical section without leaving it
	LeaveCriticalSection(&pQueue->tLock);
	DeleteCriticalSection(&pQueue->tLock);
}

// 1.10f: 0x6FF510B0
void __fastcall D2QS_QueuePush(D2QSQueueStrc* pQueue, const uint8_t* pData, uint16_t nSize)
{
	D2_ASSERTM(nSize > 0, "Zero sized Message");

	EnterCriticalSection(&pQueue->tLock);
	D2QSQueueMessageStrc* pMessage = (D2QSQueueMessageStrc*)FOG_Alloc(sizeof(D2QSQueueMessageStrc) + nSize, __FILE__, __LINE__, 0);
	pMessage->nSize = nSize;
	pMessage->pNext = nullptr;
	memcpy(&pMessage[1], pData, nSize);

	if (pQueue->pHead)
	{
		pQueue->pTail->pNext = pMessage;
	}
	else
	{
		pQueue->pHead = pMessage;
	}
	pQueue->pTail = pMessage;
	LeaveCriticalSection(&pQueue->tLock);
}

// 1.10f: 0x6FF51160
uint16_t __fastcall D2QS_QueuePop(D2QSQueueStrc* pQueue, uint8_t* pBuffer, uint16_t nBufferSize)
{
	EnterCriticalSection(&pQueue->tLock);
	D2QSQueueMessageStrc* pMessage = pQueue->pHead;
	if (!pMessage)
	{
		LeaveCriticalSection(&pQueue->tLock);
		return 0;
	}

	uint16_t nSize = 0;
	if (pMessage->nSize > nBufferSize)
	{
		// The message is dropped
		pQueue->bOverflow = TRUE;
	}
	else
	{
		memcpy(pBuffer, &pMessage[1], pMessage->nSize);
		nSize = pMessage->nSize;
	}

	pQueue->pHead = pMessage->pNext;
	FOG_Free(pMessage, __FILE__, __LINE__, 0);
	if (!pQueue->pHead)
	{
		pQueue->pTail = nullptr;
	}
	LeaveCriticalSection(&pQueue->tLock);
	return nSize;
}
