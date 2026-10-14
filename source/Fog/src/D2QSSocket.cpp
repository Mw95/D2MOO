#include <D2QS.h>
#include <Storm.h>

#include <cstddef>
#include <cstring>

#pragma pack(push, 1)
// Header used when the header is 4 bytes long with the size at offset 2
struct D2QSSrvMsg4Strc						// sizeof 0x04
{
	uint8_t nType;							// 0x00
	uint8_t nCommand;						// 0x01
	uint16_t nSize;							// 0x02
};
#pragma pack(pop)

// 1.10f: 0x6FF511F0 (#10077)
void __stdcall FOG_D2QSSocketSetDispatcher(D2QSSocketStrc* pSocket, D2QSDispatcher pfDispatcher, void* pParam)
{
	if (pSocket)
	{
		pSocket->pfDispatcher = pfDispatcher;
		pSocket->pDispatcherParam = pParam;
	}
}

// Inlined
static BOOL D2QS_IsConnected(D2QSSocketStrc* pSocket)
{
	return pSocket && pSocket->pSafeSock && pSocket->pSafeSock->bConnected;
}

// 1.10f: 0x6FF51210 (#10070)
BOOL __stdcall FOG_D2QSSocketSend(D2QSSocketStrc* pSocket, const uint8_t* pData, uint16_t nSize)
{
	if (!D2QS_IsConnected(pSocket))
	{
		return FALSE;
	}

	uint8_t pBuffer[D2QS_MAX_BUFFER_SIZE];
	int nTotalSize = 0;
	if (pSocket->nHeaderSize == sizeof(D2QSSrvMsg4Strc) && pSocket->nSizeOffset == offsetof(D2QSSrvMsg4Strc, nSize))
	{
		D2_ASSERT(pData != NULL && nSize > 0 && nSize < D2QS_MAX_BUFFER_SIZE - sizeof(D2QSSrvMsg4Strc));

		// The first byte of the data is the command
		// Note: the original copies the data one byte too early, leaving the last byte uninitialized
		memcpy(&pBuffer[sizeof(D2QSSrvMsg4Strc)], &pData[1], nSize - 1);

		D2QSSrvMsg4Strc tHeader;
		tHeader.nType = (uint8_t)pSocket->nMessageType;
		tHeader.nCommand = pData[0];
		tHeader.nSize = nSize + 3;
		memcpy(pBuffer, &tHeader, sizeof(tHeader));
		nTotalSize = nSize + 3;
	}
	else
	{
		const uint16_t nMessageSize = nSize + 2;
		D2_ASSERT(nMessageSize < D2QS_MAX_BUFFER_SIZE);
		memcpy(pBuffer, &nMessageSize, sizeof(nMessageSize));

		const int nDataSize = pData ? nSize : 0;
		nTotalSize = nDataSize + 2;
		if (pData && nTotalSize < D2QS_MAX_BUFFER_SIZE)
		{
			memcpy(&pBuffer[2], pData, nDataSize);
		}
	}

	return FOG_SOCKET_Send(pSocket->pSafeSock, (char*)pBuffer, nTotalSize) == nTotalSize;
}

// 1.10f: 0x6FF51390 (#10071)
BOOL __stdcall FOG_D2QSSocketSendRaw(D2QSSocketStrc* pSocket, const uint8_t* pData, uint16_t nSize)
{
	if (!D2QS_IsConnected(pSocket))
	{
		return FALSE;
	}

	int nSent = 0;
	FOG_SOCKET_Lock(pSocket->pSafeSock);
	if (pData && nSize)
	{
		nSent = FOG_SOCKET_SendNoLock(pSocket->pSafeSock, (char*)pData, nSize);
	}
	FOG_SOCKET_Unlock(pSocket->pSafeSock);
	return nSize == (uint16_t)nSent;
}

// 1.10f: 0x6FF51400 (#10072)
int __stdcall FOG_D2QSSocketReceive(D2QSSocketStrc* pSocket, uint8_t* pBuffer, uint16_t nBufferSize)
{
	if (!pSocket)
	{
		return 0;
	}
	return D2QS_QueuePop(&pSocket->tQueue, pBuffer, nBufferSize);
}

// 1.10f: 0x6FF51430
// Dispatches or queues the complete messages of the buffer, then moves the remaining bytes at its start.
// Returns the number of remaining bytes.
static int __fastcall D2QS_ProcessReceivedData(D2QSSocketStrc* pSocket, uint8_t* pBuffer, int nBytes)
{
	uint8_t* pMessage = pBuffer;
	while (true)
	{
		const int nAvailable = (int)(pBuffer + nBytes - pMessage);
		// Note: the original reads the size before checking that it is available
		if (nAvailable < pSocket->nHeaderSize || nAvailable < pSocket->nSizeOffset + (int)sizeof(uint16_t))
		{
			memmove(pBuffer, pMessage, nAvailable);
			return nAvailable;
		}

		uint16_t nMessageSize = 0;
		memcpy(&nMessageSize, &pMessage[pSocket->nSizeOffset], sizeof(nMessageSize));
		if (nAvailable < nMessageSize)
		{
			memmove(pBuffer, pMessage, nAvailable);
			return nAvailable;
		}

		D2_ASSERTM(nMessageSize < D2QS_MAX_BUFFER_SIZE, "nPacketSize < MAXBUFFERSIZE");
		// Note: the original loops forever on messages smaller than their header
		if (nMessageSize < pSocket->nHeaderSize || nMessageSize == 0)
		{
			return 0;
		}

		const uint8_t* pPayload = &pMessage[pSocket->nHeaderSize];
		const uint16_t nPayloadSize = (uint16_t)(nMessageSize - pSocket->nHeaderSize);
		if (pSocket->pfDispatcher)
		{
			D2_ASSERTM(!IsBadCodePtr((FARPROC)pSocket->pfDispatcher), "pSocket->fpDispatcher");

			// Messages whose size is not at the start of the header are given with their header
			BOOL bHandled = FALSE;
			if (pSocket->nSizeOffset > 0)
			{
				bHandled = pSocket->pfDispatcher(pMessage, nMessageSize, pSocket->pDispatcherParam);
			}
			else
			{
				bHandled = pSocket->pfDispatcher(pPayload, nPayloadSize, pSocket->pDispatcherParam);
			}

			if (!bHandled)
			{
				if (pSocket->nSizeOffset > 0)
				{
					D2QS_QueuePush(&pSocket->tQueue, pMessage, nMessageSize);
				}
				else
				{
					D2QS_QueuePush(&pSocket->tQueue, pPayload, nPayloadSize);
				}
				SetEvent(pSocket->hMessageEvent);
			}
		}
		else
		{
			D2QS_QueuePush(&pSocket->tQueue, pPayload, nPayloadSize);
			SetEvent(pSocket->hMessageEvent);
		}

		pMessage += nMessageSize;
	}
}

// 1.10f: 0x6FF515B0 (#10078)
void __stdcall FOG_D2QSSocketSetHeaderFormat(D2QSSocketStrc* pSocket, int nHeaderSize, int nSizeOffset, int nMessageType)
{
	if (pSocket)
	{
		pSocket->nHeaderSize = nHeaderSize;
		pSocket->nSizeOffset = nSizeOffset;
		pSocket->nMessageType = nMessageType;
	}
}

// Inlined
static void D2QS_CloseSafeSock(D2QSSocketStrc* pSocket)
{
	FSafeSock* pSafeSock = pSocket->pSafeSock;
	if (!pSafeSock || !pSafeSock->bConnected || !pSafeSock->nSocket)
	{
		return;
	}

	EnterCriticalSection(&pSafeSock->tCriticalSection);
	FOG_SOCKET_CloseSocket(pSafeSock->nSocket);
	pSafeSock->nSocket = 0;
	pSafeSock->bConnected = FALSE;
	LeaveCriticalSection(&pSafeSock->tCriticalSection);
}

// 1.10f: 0x6FF515E0
// Receives the data of the socket until it is disconnected
static DWORD WINAPI D2QS_ReceiveThread(LPVOID lpParameter)
{
	D2QSSocketStrc* pSocket = (D2QSSocketStrc*)lpParameter;

	// Wait for the connection
	while (!pSocket->pSafeSock)
	{
		if (pSocket->bStop)
		{
			D2QS_CloseSafeSock(pSocket);
			return 0;
		}
		Sleep(0);
	}

	uint8_t pBuffer[D2QS_MAX_BUFFER_SIZE];
	int nBufferSize = 0;
	while (!pSocket->bStop)
	{
		FSafeSock* pSafeSock = pSocket->pSafeSock;
		if (!pSafeSock || !pSafeSock->bConnected || pSafeSock->bStopping || pSafeSock->nFogErrorCode)
		{
			break;
		}

		const int nSelectResult = FOG_SOCKET_Select(pSafeSock);
		if (!pSocket->pSafeSock || pSocket->pSafeSock->bStopping)
		{
			break;
		}

		if (!nSelectResult)
		{
			continue;
		}

		while (!pSocket->bStop)
		{
			const int nRequested = D2QS_MAX_BUFFER_SIZE - nBufferSize;
			const int nReceived = FOG_SOCKET_Receive(pSocket->pSafeSock, (char*)&pBuffer[nBufferSize], nRequested);

			DWORD dwFogError = 0;
			int nWSAError = 0;
			FOG_SOCKET_GetError(pSocket->pSafeSock, &dwFogError, &nWSAError);
			if (dwFogError || nReceived <= 0)
			{
				D2QS_CloseSafeSock(pSocket);
				return 0;
			}

			nBufferSize = D2QS_ProcessReceivedData(pSocket, pBuffer, nReceived + nBufferSize);
			if (nReceived < nRequested)
			{
				break;
			}
		}
	}

	D2QS_CloseSafeSock(pSocket);
	return 0;
}

// 1.10f: 0x6FF517C0
static DWORD WINAPI D2QS_ConnectThread(LPVOID lpParameter)
{
	D2QSSocketStrc* pSocket = (D2QSSocketStrc*)lpParameter;
	pSocket->pSafeSock = FOG_SOCKET_Connect(pSocket->szHostAddress, (uint16_t)pSocket->nPort, D2QS_ReceiveThread, pSocket, pSocket->szName);
	return TRUE;
}

// Inlined
static BOOL D2QS_StartConnectThread(D2QSSocketStrc* pSocket)
{
	if (!pSocket || pSocket->hConnectThread)
	{
		return FALSE;
	}

	pSocket->bStop = FALSE;
	pSocket->hMessageEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
	pSocket->hConnectThread = CreateThread(nullptr, 0, D2QS_ConnectThread, pSocket, 0, &pSocket->dwConnectThreadId);
	return TRUE;
}

// 1.10f: 0x6FF517F0 (#10073)
void __stdcall FOG_D2QSSocketConnect(D2QSSocketStrc* pSocket)
{
	if (!D2QS_StartConnectThread(pSocket))
	{
		return;
	}

	while (WaitForSingleObject(pSocket->hConnectThread, 0) != WAIT_OBJECT_0)
	{
		Sleep(10);
	}
}

// 1.10f: 0x6FF51860 (#10074)
HANDLE __stdcall FOG_D2QSSocketConnectAsync(D2QSSocketStrc* pSocket)
{
	if (!D2QS_StartConnectThread(pSocket))
	{
		return nullptr;
	}
	return pSocket->hConnectThread;
}

// 1.10f: 0x6FF518C0 (#10075)
void __stdcall FOG_D2QSSocketDisconnect(D2QSSocketStrc* pSocket)
{
	if (!pSocket || !pSocket->pSafeSock || !pSocket->pSafeSock->hThread)
	{
		return;
	}

	pSocket->bStop = TRUE;
	EnterCriticalSection(&pSocket->pSafeSock->tCriticalSection);
	pSocket->pSafeSock->bStopping = TRUE;
	LeaveCriticalSection(&pSocket->pSafeSock->tCriticalSection);
}

// 1.10f: 0x6FF51920 (#10068)
D2QSSocketStrc* __stdcall FOG_D2QSSocketCreate(const char* szHostAddress, int nPort, const char* szName)
{
	D2_ASSERT(szHostAddress);
	D2_ASSERT(strlen(szHostAddress) < MAX_PATH - 1);

	D2QSSocketStrc* pSocket = (D2QSSocketStrc*)FOG_Alloc(sizeof(D2QSSocketStrc), __FILE__, __LINE__, 0);
	if (!pSocket)
	{
		return nullptr;
	}

	memset(pSocket, 0, sizeof(D2QSSocketStrc));
	SStrCopy(pSocket->szHostAddress, szHostAddress, sizeof(pSocket->szHostAddress));
	if (szName)
	{
		// Note: the original uses the size of a pointer, so only 3 characters are kept
		SStrCopy(pSocket->szName, szName, sizeof(szName));
	}
	else
	{
		SStrCopy(pSocket->szName, "UNKNOWN", sizeof(pSocket->szName));
	}
	pSocket->nPort = nPort;
	D2QS_QueueInitialize(&pSocket->tQueue);
	pSocket->nHeaderSize = sizeof(uint16_t);
	pSocket->nSizeOffset = 0;
	return pSocket;
}

// 1.10f: 0x6FF51A10 (#10069)
void __stdcall FOG_D2QSSocketDestroy(D2QSSocketStrc* pSocket)
{
	if (!pSocket)
	{
		return;
	}

	FOG_D2QSSocketDisconnect(pSocket);
	D2QS_QueueDestroy(&pSocket->tQueue);
	if (pSocket->pSafeSock && pSocket->pSafeSock->hThread)
	{
		FOG_SOCKET_Destroy(pSocket->pSafeSock);
		pSocket->pSafeSock = nullptr;
	}
	FOG_Free(pSocket, __FILE__, __LINE__, 0);
}

// 1.10f: 0x6FF51AB0 (#10076)
DWORD __stdcall FOG_D2QSSocketWaitForMessage(D2QSSocketStrc* pSocket, DWORD dwMilliseconds)
{
	if (!pSocket)
	{
		return 0;
	}
	return WaitForSingleObject(pSocket->hMessageEvent, dwMilliseconds);
}

// 1.10f: 0x6FF51AD0 (#10079)
FSafeSock* __stdcall FOG_D2QSSocketGetSafeSock(D2QSSocketStrc* pSocket)
{
	return pSocket ? pSocket->pSafeSock : nullptr;
}

// 1.10f: 0x6FF51AF0 (#10080)
void __stdcall FOG_D2QSSocketSignal(D2QSSocketStrc* pSocket)
{
	if (pSocket)
	{
		SetEvent(pSocket->hMessageEvent);
	}
}
