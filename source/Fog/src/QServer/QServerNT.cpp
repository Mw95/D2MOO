#include <Safesock.h>
#include <QServer/QServer.h>
#include <System/System.h>

#include <cstddef>
#include <cstdlib>
#include <cstring>

// Parameter of the accept and read threads
struct D2QSThreadParamStrc						// sizeof 0x08
{
	QServer* pServer;							// 0x00
	int32_t nPortIndex;							// 0x04
};

// 1.10f: Inlined
static void QSERVERNT_QueueWrite(D2QSClientStrc* pClient, const uint8_t* pData, int nSize)
{
	D2QSWriteBufferStrc* pBuffer = (D2QSWriteBufferStrc*)FOG_Alloc(sizeof(D2QSWriteBufferStrc) + nSize, __FILE__, __LINE__, 0);
	memcpy(&pBuffer[1], pData, nSize);
	pBuffer->nSize = nSize;
	pBuffer->pNext = nullptr;

	if (!pClient->pWriteHead)
	{
		pClient->pWriteHead = pBuffer;
		return;
	}

	D2QSWriteBufferStrc* pTail = pClient->pWriteHead;
	while (pTail->pNext)
	{
		pTail = pTail->pNext;
	}
	pTail->pNext = pBuffer;
}

// 1.10f: 0x6FF58E80
// Starts writing the first queued buffer. The client lock must be held.
static BOOL __fastcall QSERVERNT_PostWrite(QServer* pServer, D2QSClientStrc* pClient)
{
	D2QSWriteBufferStrc* pBuffer = pClient->pWriteHead;
	if (!pBuffer)
	{
		return TRUE;
	}

	QSERVER_AddRef(pServer, pClient);
	D2_ASSERT(pClient->hSocket != INVALID_SOCKET);

	DWORD dwBytesWritten = 0;
	const BOOL bResult = WriteFile((HANDLE)pClient->hSocket, &pBuffer[1], pBuffer->nSize, &dwBytesWritten, &pClient->tWrite.tOverlapped);
	const DWORD dwError = GetLastError();
	if (bResult)
	{
		return TRUE;
	}

	if (dwError != ERROR_IO_PENDING)
	{
		const int nClientId = pClient->nClientId;
		QSERVER_Release(pServer, pClient);
		QSERVER_CloseClient(pServer, nClientId, __FILE__, __LINE__);
		return FALSE;
	}

	if (pClient->tWrite.nTag & QSOVERLAPPED_PENDING)
	{
		FOG_TraceF("", "[sQSNTWriteFromQueue] Two writes in progress at the same time");
	}
	pClient->tWrite.nTag |= QSOVERLAPPED_PENDING;
	return TRUE;
}

// 1.10f: 0x6FF58D20
// Starts reading into the free part of the read buffer of the client
static BOOL __fastcall QSERVERNT_PostRead(QServer* pServer, D2QSClientStrc* pClient, BOOL bFirstRead)
{
	D2_MAYBE_UNUSED(bFirstRead);

	EnterCriticalSection(&pClient->tLock);
	const int nFreeSize = QSERVER_READ_BUFFER_SIZE - pClient->nReadBufferSize;
	uint8_t* pBuffer = &pClient->pReadBuffer[pClient->nReadBufferSize];
	if (!nFreeSize)
	{
		QSERVER_CloseClient(pServer, pClient->nClientId, __FILE__, __LINE__);
		LeaveCriticalSection(&pClient->tLock);
		return FALSE;
	}

	D2_ASSERT((pClient->tRead.nTag & QSOVERLAPPED_PENDING) == 0);
	pClient->tRead.nTag |= QSOVERLAPPED_PENDING;
	D2_ASSERT(!pClient->tRead.tOverlapped.hEvent);

	const int nClientId = pClient->nClientId;
	if (pClient->hSocket == INVALID_SOCKET)
	{
		LeaveCriticalSection(&pClient->tLock);
		QSERVER_CloseClient(pServer, nClientId, __FILE__, __LINE__);
		// Note: releases a reference that was not taken
		QSERVER_Release(pServer, pClient);
		return FALSE;
	}

	QSERVER_AddRef(pServer, pClient);
	if (!ReadFile((HANDLE)pClient->hSocket, pBuffer, nFreeSize, &pClient->dwBytesRead, &pClient->tRead.tOverlapped))
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			// Note: the original does not leave the critical section
			LeaveCriticalSection(&pClient->tLock);
			QSERVER_Release(pServer, pClient);
			QSERVER_CloseClient(pServer, nClientId, __FILE__, __LINE__);
			return FALSE;
		}
	}

	LeaveCriticalSection(&pClient->tLock);
	return TRUE;
}

// 1.10f: 0x6FF58760
BOOL __fastcall QSERVERNT_Send(QServer* pServer, D2QSClientStrc* pClient, const uint8_t* pData, int nSize)
{
	EnterCriticalSection(&pClient->tLock);
	pClient->nLastSendTime = FOG_10055_GetSyncTime();

	// Keep the order of the messages if writes are pending
	if (pClient->pWriteHead)
	{
		QSERVERNT_QueueWrite(pClient, pData, nSize);
		LeaveCriticalSection(&pClient->tLock);
		return TRUE;
	}

	const int nClientId = pClient->nClientId;
	if (pClient->hSocket == INVALID_SOCKET)
	{
		LeaveCriticalSection(&pClient->tLock);
		QSERVER_CloseClient(pServer, nClientId, __FILE__, __LINE__);
		// Note: releases a reference that was not taken
		QSERVER_Release(pServer, pClient);
		return FALSE;
	}

	int nSent = send(pClient->hSocket, (const char*)pData, nSize, 0);
	if (nSent == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			LeaveCriticalSection(&pClient->tLock);
			QSERVER_CloseClient(pServer, nClientId, __FILE__, __LINE__);
			return FALSE;
		}
		nSent = 0;
	}

	if (nSent < nSize)
	{
		QSERVERNT_QueueWrite(pClient, &pData[nSent], nSize - nSent);
		QSERVERNT_PostWrite(pServer, pClient);
	}

	LeaveCriticalSection(&pClient->tLock);
	return TRUE;
}

// 1.10f: Inlined in 0x6FF58200
static void QSERVERNT_Accept(QServer* pServer, int nPortIndex)
{
	sockaddr_in tAddress{};
	int nAddressSize = sizeof(tAddress);
	const SOCKET hSocket = accept(pServer->hListenSockets[nPortIndex], (sockaddr*)&tAddress, &nAddressSize);
	if (hSocket == INVALID_SOCKET)
	{
		WSAGetLastError();
		return;
	}

	const uint32_t nIP = tAddress.sin_addr.s_addr;
	BOOL bRejected = FALSE;
	if (QSERVER_IsBanned(pServer, nIP))
	{
		// "user on hack list"
		bRejected = TRUE;
	}
	else if (QSERVER_HasTooManyConnections(pServer, &nIP))
	{
		// "user logged on twice"
		QSERVER_KickClientWithSameIP(pServer, &nIP, __FILE__, __LINE__);
		bRejected = TRUE;
	}
	else if (!QSERVER_CheckReconnections(pServer, &nIP) && !FOG_QServerIsWhitelisted(pServer, nIP))
	{
		// "user spamming with reconnects"
		QSERVER_HackListAdd(pServer, __FILE__, nIP, __LINE__);
		bRejected = TRUE;
	}

	if (bRejected)
	{
		FOG_SOCKET_CloseSocket(hSocket);
		return;
	}

	D2QSClientStrc* pClient = QSERVER_CreateClient(pServer, hSocket, nIP);
	pClient->nPortIndex = nPortIndex;

	u_long nNonBlocking = 1;
	ioctlsocket(hSocket, FIONBIO, &nNonBlocking);

	nAddressSize = sizeof(pClient->tPeerAddress);
	getpeername(hSocket, (sockaddr*)&pClient->tPeerAddress, &nAddressSize);
	memset(pClient->tPeerAddress.sin_zero, 0, sizeof(pClient->tPeerAddress.sin_zero));
	nAddressSize = sizeof(pClient->tLocalAddress);
	getsockname(hSocket, (sockaddr*)&pClient->tLocalAddress, &nAddressSize);
	memset(pClient->tLocalAddress.sin_zero, 0, sizeof(pClient->tLocalAddress.sin_zero));

	D2_ASSERT(pClient->hSocket == hSocket);
	CreateIoCompletionPort((HANDLE)hSocket, pServer->hCompletionPorts[nPortIndex], (ULONG_PTR)pClient->nClientId, 0);

	if (QSERVERNT_PostRead(pServer, pClient, TRUE) && pServer->pfOnConnect)
	{
		pServer->pfOnConnect(pServer, pClient->nClientId, __FILE__, __LINE__);
	}
}

// 1.10f: 0x6FF58200
// Accepts the connections on a port, at most one every 8 ms
static DWORD WINAPI QSERVERNT_AcceptThread(LPVOID lpParameter)
{
	const D2QSThreadParamStrc* pParam = (const D2QSThreadParamStrc*)lpParameter;
	QServer* pServer = pParam->pServer;
	const int nPortIndex = pParam->nPortIndex;
	FOG_Free((void*)pParam, __FILE__, __LINE__, 0);

	FOG_Trace("Started sAcceptThread:conn=%d socket=%d", nPortIndex, pServer->hListenSockets[nPortIndex]);

	DWORD dwNextAcceptTime = GetTickCount();
	while (!pServer->bStopAcceptThreads[nPortIndex])
	{
		const DWORD dwNow = GetTickCount();
		if (abs((int)(dwNextAcceptTime - dwNow)) > 2000)
		{
			dwNextAcceptTime = dwNow;
		}

		if ((int)(dwNextAcceptTime - dwNow) > 0)
		{
			Sleep(10);
			continue;
		}

		QSERVER_UpdateHackList(pServer);
		if (nPortIndex == 0)
		{
			FOG_10082_Noop();
		}

		fd_set tReadSet;
		FD_ZERO(&tReadSet);
		FD_SET(pServer->hListenSockets[nPortIndex], &tReadSet);
		timeval tTimeout = { 0, 0 };
		const int nResult = select(0, &tReadSet, nullptr, nullptr, &tTimeout);
		if (nResult == SOCKET_ERROR)
		{
			FOG_10082_Noop();
			return TRUE;
		}

		if (nResult == 0)
		{
			Sleep(20);
			continue;
		}

		// Note: the original also measures the time spent in each step, the results are never used
		QSERVERNT_Accept(pServer, nPortIndex);
		Sleep(0);
		dwNextAcceptTime += 8;
	}

	EnterCriticalSection(&pServer->tLock);
	pServer->bStopAcceptThreads[nPortIndex] = FALSE;
	LeaveCriticalSection(&pServer->tLock);
	FOG_10082_Noop();
	return TRUE;
}

// 1.10f: 0x6FF58A00
// Handles the completed reads and writes of a port. Returns TRUE if data was received.
static BOOL __fastcall QSERVERNT_ProcessCompletions(QServer* pServer, int nPortIndex, DWORD dwMilliseconds)
{
	BOOL bReceived = FALSE;
	const DWORD dwStartTime = GetTickCount();
	// Note: the original computes the elapsed time as dwStartTime - GetTickCount(), so it stops as soon as the tick count changes
	while (dwStartTime - GetTickCount() <= 100)
	{
		DWORD dwBytes = 0;
		ULONG_PTR nKey = 0;
		OVERLAPPED* pOverlapped = nullptr;
		const BOOL bResult = GetQueuedCompletionStatus(pServer->hCompletionPorts[nPortIndex], &dwBytes, &nKey, &pOverlapped, dwMilliseconds);

		D2QSClientStrc* pClient = nullptr;
		BOOL bRead = FALSE;
		BOOL bWrite = FALSE;
		if (bResult || pOverlapped)
		{
			pClient = QSERVER_FindClient(pServer, (int)nKey);
			if (!pClient)
			{
				continue;
			}

			// Note: the original does not check the overlapped structure
			if (pOverlapped)
			{
				const int nTag = ((D2QSOverlappedStrc*)pOverlapped)->nTag;
				bRead = (nTag & QSOVERLAPPED_READ) != 0;
				bWrite = (nTag & (QSOVERLAPPED_READ | QSOVERLAPPED_WRITE)) == QSOVERLAPPED_WRITE;
			}
		}

		const DWORD dwError = GetLastError();
		if (bResult)
		{
			if (!dwBytes)
			{
				// Connection closed
				if (pClient->hSocket != INVALID_SOCKET)
				{
					QSERVER_CloseClient(pServer, pClient->nClientId, __FILE__, __LINE__);
				}
				QSERVER_Release(pServer, pClient);
			}
			else if (bWrite)
			{
				EnterCriticalSection(&pClient->tLock);
				D2QSWriteBufferStrc* pBuffer = pClient->pWriteHead;
				if (pBuffer)
				{
					pClient->pWriteHead = pBuffer->pNext;
				}
				else
				{
					FOG_TraceF("", "[sQSNTRemoveFromQueue] ptClient->ptWriteHead is NULL!");
				}
				pClient->tWrite.nTag &= ~QSOVERLAPPED_PENDING;
				LeaveCriticalSection(&pClient->tLock);

				if (pBuffer)
				{
					FOG_Free(pBuffer, __FILE__, __LINE__, 0);
				}

				EnterCriticalSection(&pClient->tLock);
				if (!pClient->bClosing)
				{
					QSERVERNT_PostWrite(pServer, pClient);
				}
				LeaveCriticalSection(&pClient->tLock);
				QSERVER_Release(pServer, pClient);
			}
			else if (bRead)
			{
				EnterCriticalSection(&pClient->tLock);
				pClient->tRead.nTag &= ~QSOVERLAPPED_PENDING;
				pClient->nReadBufferSize += dwBytes;
				pClient->nLastReceiveTime = FOG_10055_GetSyncTime();
				LeaveCriticalSection(&pClient->tLock);

				QSERVER_ProcessClientData(pServer, pClient);
				bReceived = TRUE;
				if (!pClient->bClosing)
				{
					QSERVERNT_PostRead(pServer, pClient, FALSE);
				}
				QSERVER_Release(pServer, pClient);
			}
			else
			{
				FOG_Trace("WARNING: IO Completion on unknown overlapped structure.");
				FOG_Trace("  IOCP = 0x%08X/0x%08X, ptClient = 0x%08X/0x%08X.", (uint8_t*)pOverlapped - offsetof(D2QSClientStrc, tRead), pOverlapped, pClient, &pClient->tRead);
			}
			continue;
		}

		if (pOverlapped && pClient)
		{
			// The I/O failed
			QSERVER_CloseClient(pServer, pClient->nClientId, __FILE__, __LINE__);
			QSERVER_Release(pServer, pClient);
			continue;
		}

		D2_ASSERT(dwError == WAIT_TIMEOUT);
		break;
	}
	return bReceived;
}

// 1.10f: 0x6FF58910
static DWORD WINAPI QSERVERNT_ReadThread(LPVOID lpParameter)
{
	const D2QSThreadParamStrc* pParam = (const D2QSThreadParamStrc*)lpParameter;
	QServer* pServer = pParam->pServer;
	const int nPortIndex = pParam->nPortIndex;
	FOG_Free((void*)pParam, __FILE__, __LINE__, 0);

	D2_ASSERT(pServer->bUseReadThreads);
	FOG_Trace("Started sReadThread:conn=%d", nPortIndex);

	while (!pServer->bStopReadThreads[nPortIndex])
	{
		QSERVERNT_ProcessCompletions(pServer, nPortIndex, 50);
	}

	EnterCriticalSection(&pServer->tLock);
	pServer->bStopReadThreads[nPortIndex] = FALSE;
	LeaveCriticalSection(&pServer->tLock);
	FOG_10082_Noop();
	return TRUE;
}

// 1.10f: 0x6FF589C0
BOOL __fastcall QSERVERNT_WaitForData(QServer* pServer, DWORD dwMilliseconds)
{
	if (!pServer->bUseReadThreads)
	{
		for (int i = 0; i < QSERVER_MAX_PORTS; ++i)
		{
			if (pServer->hListenSockets[i] != INVALID_SOCKET)
			{
				QSERVERNT_ProcessCompletions(pServer, i, dwMilliseconds);
			}
		}
	}
	return TRUE;
}

// 1.10f: 0x6FF57EE0
SOCKET __fastcall QSERVERNT_AddPort(QServer* pServer, int nPort)
{
	HANDLE hPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
	D2_ASSERT(hPort);

	const SOCKET hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		FOG_Trace("[SERVER]  QSNTInit failed on socket() - err=%d", WSAGetLastError());
		return 0;
	}

	int nValue = 1;
	setsockopt(hSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&nValue, sizeof(nValue));
	nValue = 1;
	setsockopt(hSocket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&nValue, sizeof(nValue));
	nValue = 1;
	setsockopt(hSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&nValue, sizeof(nValue));
	u_long nNonBlocking = 1;
	ioctlsocket(hSocket, FIONBIO, &nNonBlocking);

	sockaddr_in tAddress{};
	tAddress.sin_family = AF_INET;
	tAddress.sin_port = htons((u_short)nPort);
	if (bind(hSocket, (const sockaddr*)&tAddress, sizeof(tAddress)) == SOCKET_ERROR)
	{
		FOG_Trace("[SERVER]  QSNTInit failed on bind() - err=%d", WSAGetLastError());
		FOG_SOCKET_CloseSocket(hSocket);
		return 0;
	}

	if (listen(hSocket, 250) == SOCKET_ERROR)
	{
		FOG_Trace("[SERVER]  QSNTInit failed on listen() - err=%d", WSAGetLastError());
		FOG_SOCKET_CloseSocket(hSocket);
		return 0;
	}

	// Note: the original does not check the number of ports
	const int nPortIndex = pServer->nPorts;
	if (nPortIndex >= QSERVER_MAX_PORTS)
	{
		FOG_SOCKET_CloseSocket(hSocket);
		return 0;
	}

	++pServer->nPorts;
	pServer->hCompletionPorts[nPortIndex] = hPort;
	pServer->nPortNumbers[nPortIndex] = (uint16_t)nPort;
	pServer->hListenSockets[nPortIndex] = hSocket;
	pServer->nPortFlags[nPortIndex] = 1;

	D2QSThreadParamStrc* pAcceptParam = (D2QSThreadParamStrc*)FOG_Alloc(sizeof(D2QSThreadParamStrc), __FILE__, __LINE__, 0);
	pAcceptParam->pServer = pServer;
	pAcceptParam->nPortIndex = nPortIndex;
	pServer->hAcceptThreads[nPortIndex] = CreateThread(nullptr, 0, QSERVERNT_AcceptThread, pAcceptParam, 0, &pServer->dwAcceptThreadIds[nPortIndex]);
	FOG_Trace("Created Thread ID: %04x for NetServer", pServer->dwAcceptThreadIds[nPortIndex]);

	if (pServer->bUseReadThreads)
	{
		D2QSThreadParamStrc* pReadParam = (D2QSThreadParamStrc*)FOG_Alloc(sizeof(D2QSThreadParamStrc), __FILE__, __LINE__, 0);
		pReadParam->pServer = pServer;
		pReadParam->nPortIndex = nPortIndex;
		pServer->hReadThreads[nPortIndex] = CreateThread(nullptr, 0, QSERVERNT_ReadThread, pReadParam, 0, &pServer->dwReadThreadIds[nPortIndex]);
		FOG_Trace("Created Thread ID: %04x for Read", pServer->dwReadThreadIds[nPortIndex]);
	}

	return hSocket;
}

// 1.10f: 0x6FF57E90
BOOL __fastcall QSERVERNT_Initialize(QServer* pServer, int nPort)
{
	pServer->nMaxConnectionsPerIP = 1;

	WSADATA tWSAData;
	if (WSAStartup(MAKEWORD(1, 1), &tWSAData) != 0)
	{
		return FALSE;
	}
	return QSERVERNT_AddPort(pServer, nPort) != 0;
}

// 1.10f: 0x6FF58130
void __fastcall QSERVERNT_Shutdown(QServer* pServer)
{
	HANDLE hThreads[2 * QSERVER_MAX_PORTS];
	DWORD nThreads = 0;

	EnterCriticalSection(&pServer->tLock);
	for (int i = 0; i < QSERVER_MAX_PORTS; ++i)
	{
		if (pServer->hAcceptThreads[i])
		{
			hThreads[nThreads++] = pServer->hAcceptThreads[i];
		}
		pServer->bStopAcceptThreads[i] = TRUE;

		if (pServer->bUseReadThreads && pServer->hReadThreads[i])
		{
			hThreads[nThreads++] = pServer->hReadThreads[i];
		}
		pServer->bStopReadThreads[i] = TRUE;
	}
	LeaveCriticalSection(&pServer->tLock);

	if (nThreads > 0)
	{
		WaitForMultipleObjects(nThreads, hThreads, TRUE, 1000);
	}

	for (int i = 0; i < QSERVER_MAX_PORTS; ++i)
	{
		if (pServer->hAcceptThreads[i])
		{
			CloseHandle(pServer->hAcceptThreads[i]);
			pServer->hAcceptThreads[i] = nullptr;
			pServer->dwAcceptThreadIds[i] = 0;
		}

		if (pServer->bUseReadThreads && pServer->hReadThreads[i])
		{
			CloseHandle(pServer->hReadThreads[i]);
			pServer->hReadThreads[i] = nullptr;
			pServer->dwReadThreadIds[i] = 0;
		}
	}
}
