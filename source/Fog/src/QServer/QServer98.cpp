#include <Safesock.h>
#include <QServer/QServer.h>

#include <cstdio>
#include <cstdlib>

// 1.10f: Inlined in 0x6FF57920
// Accepts a connection on the listen socket. The server lock must be held.
static void QSERVER98_AcceptConnection(QServer* pServer)
{
	sockaddr_in tAddress{};
	SOCKET hSocket = INVALID_SOCKET;
	int nTries = 0;
	while (true)
	{
		tAddress = {};
		int nAddressSize = sizeof(tAddress);
		WSASetLastError(0);
		EnterCriticalSection(&pServer->tLock);
		hSocket = accept(pServer->hListenSockets[0], (sockaddr*)&tAddress, &nAddressSize);
		if (hSocket != INVALID_SOCKET)
		{
			break;
		}

		const int nError = WSAGetLastError();
		if (nError != WSAEWOULDBLOCK)
		{
			char szMessage[256];
			sprintf(szMessage, "Accept failed.  Error %d", nError);
			FOG_DisplayHalt(szMessage, __FILE__, __LINE__);
			exit(-1);
		}

		++nTries;
		if (nTries > 100)
		{
			FOG_DisplayHalt("EWOULDBLOCK 100 times", __FILE__, __LINE__);
			exit(-1);
		}
		LeaveCriticalSection(&pServer->tLock);
	}

	const uint32_t nIP = tAddress.sin_addr.s_addr;
	if (QSERVER_IsBanned(pServer, nIP))
	{
		FOG_SOCKET_CloseSocket(hSocket);
	}
	else if (QSERVER_HasTooManyConnections(pServer, &nIP))
	{
		QSERVER_KickClientWithSameIP(pServer, &nIP, __FILE__, __LINE__);
		FOG_SOCKET_CloseSocket(hSocket);
	}
	else if (!QSERVER_CheckReconnections(pServer, &nIP))
	{
		QSERVER_HackListAdd(pServer, __FILE__, nIP, __LINE__);
		FOG_SOCKET_CloseSocket(hSocket);
	}
	else
	{
		D2QSClientStrc* pClient = QSERVER_CreateClient(pServer, hSocket, nIP);
		if (pServer->pfOnConnect)
		{
			pServer->pfOnConnect(pServer, pClient->nClientId, __FILE__, __LINE__);
		}
	}
	LeaveCriticalSection(&pServer->tLock);
}

// 1.10f: Inlined in 0x6FF57920
// Reads the data received by the client. The server lock is taken.
static void QSERVER98_ReadClient(QServer* pServer, SOCKET hSocket)
{
	D2QSClientStrc* pClient = QSERVER_FindClientBySocket(pServer, hSocket);
	EnterCriticalSection(&pServer->tLock);
	if (!pClient)
	{
		uint8_t pBuffer[QSERVER_READ_BUFFER_SIZE];
		const int nResult = recv(hSocket, (char*)pBuffer, sizeof(pBuffer), 0);
		FOG_TraceF("", "[sServeThread]  Socket %d has no connection (recv() = %d)", hSocket, nResult);
		LeaveCriticalSection(&pServer->tLock);
		return;
	}

	int nReceived = 0;
	EnterCriticalSection(&pClient->tLock);
	const int nBufferSize = pClient->nReadBufferSize;
	if (nBufferSize >= 0 && nBufferSize <= QSERVER_READ_BUFFER_SIZE)
	{
		nReceived = recv(hSocket, (char*)&pClient->pReadBuffer[nBufferSize], QSERVER_READ_BUFFER_SIZE - nBufferSize, 0);
	}
	else
	{
		FOG_Trace("FILE:%s  LINE:%d  message buffer size(%d) exceeded bounds.", __FILE__, __LINE__, nBufferSize);
	}
	LeaveCriticalSection(&pClient->tLock);

	if (nReceived == SOCKET_ERROR || nReceived == 0)
	{
		QSERVER_CloseClient(pServer, pClient->nClientId, __FILE__, __LINE__);
	}
	else
	{
		EnterCriticalSection(&pClient->tLock);
		pClient->nReadBufferSize += nReceived;
		LeaveCriticalSection(&pClient->tLock);

		QSERVER_ProcessClientData(pServer, pClient);
		SetEvent(pServer->hDataEvent);
	}
	LeaveCriticalSection(&pServer->tLock);
}

// 1.10f: 0x6FF57920
// Accepts the connections and reads the data of the clients using select
static DWORD WINAPI QSERVER98_ServeThread(LPVOID lpParameter)
{
	QServer* pServer = (QServer*)lpParameter;

	// Only FD_SETSIZE sockets can be polled at once, so the clients are polled in turn
	uint32_t nBucket = 0;
	int nSkip = 0;
	while (true)
	{
		QSERVER_UpdateHackList(pServer);

		fd_set tReadSet;
		fd_set tExceptSet;
		FD_ZERO(&tReadSet);
		FD_ZERO(&tExceptSet);

		EnterCriticalSection(&pServer->tLock);
		FD_SET(pServer->hListenSockets[0], &tReadSet);
		FD_SET(pServer->hListenSockets[0], &tExceptSet);

		// Note: the original resumes from the next bucket instead of the current one
		D2QSClientStrc* pClient = pServer->pClientHash[nBucket];
		for (int i = 0; pClient && i < nSkip; ++i)
		{
			pClient = pClient->pNext;
		}

		for (int nSockets = 1; nSockets <= pServer->nClients && nSockets < FD_SETSIZE; ++nSockets)
		{
			while (!pClient)
			{
				nBucket = (nBucket + 1) % pServer->nClientHashSize2;
				pClient = pServer->pClientHash[nBucket];
				nSkip = 0;
			}

			EnterCriticalSection(&pClient->tLock);
			FD_SET(pClient->hSocket, &tReadSet);
			FD_SET(pClient->hSocket, &tExceptSet);
			D2QSClientStrc* pNext = pClient->pNext;
			LeaveCriticalSection(&pClient->tLock);
			pClient = pNext;
			++nSkip;
		}

		timeval tTimeout;
		tTimeout.tv_sec = 0;
		tTimeout.tv_usec = 100000 / (pServer->nClients / 64 + 1);
		LeaveCriticalSection(&pServer->tLock);

		const int nResult = select(0, &tReadSet, nullptr, &tExceptSet, &tTimeout);
		if (nResult == 0)
		{
			EnterCriticalSection(&pServer->tLock);
			if (pServer->bStopAcceptThreads[0])
			{
				pServer->bStopAcceptThreads[0] = FALSE;
				LeaveCriticalSection(&pServer->tLock);
				OutputDebugStringA("Server thread close #1\n");
				FOG_10082_Noop();
				return 0;
			}
			LeaveCriticalSection(&pServer->tLock);
			continue;
		}

		if (nResult == SOCKET_ERROR)
		{
			continue;
		}

		for (int i = (int)tReadSet.fd_count - 1; i >= 0; --i)
		{
			const SOCKET hSocket = tReadSet.fd_array[i];
			if (hSocket == pServer->hListenSockets[0])
			{
				QSERVER98_AcceptConnection(pServer);
			}
			else
			{
				QSERVER98_ReadClient(pServer, hSocket);
			}
		}
	}
}

// 1.10f: 0x6FF57750
BOOL __fastcall QSERVER98_Initialize(QServer* pServer, int nPort)
{
	pServer->nMaxConnectionsPerIP = 1;

	const SOCKET hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		return FALSE;
	}

	pServer->hListenSockets[0] = hSocket;

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
	pServer->nPortNumbers[0] = (uint16_t)nPort;
	if (bind(hSocket, (const sockaddr*)&tAddress, sizeof(tAddress)) == SOCKET_ERROR)
	{
		// Note: the original keeps the closed socket as the listen socket
		FOG_SOCKET_CloseSocket(hSocket);
		pServer->hListenSockets[0] = INVALID_SOCKET;
		return FALSE;
	}

	if (listen(hSocket, 25) == SOCKET_ERROR)
	{
		// Note: the original continues with the closed socket
		FOG_SOCKET_CloseSocket(hSocket);
	}

	pServer->hDataEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
	pServer->hAcceptThreads[0] = CreateThread(nullptr, 0, QSERVER98_ServeThread, pServer, 0, &pServer->dwAcceptThreadIds[0]);
	return TRUE;
}

// 1.10f: 0x6FF578B0
void __fastcall QSERVER98_Shutdown(QServer* pServer)
{
	EnterCriticalSection(&pServer->tLock);
	pServer->bStopAcceptThreads[0] = TRUE;
	LeaveCriticalSection(&pServer->tLock);
	WaitForSingleObject(pServer->hAcceptThreads[0], 2000);
}

// 1.10f: 0x6FF578F0
BOOL __fastcall QSERVER98_Send(QServer* pServer, D2QSClientStrc* pClient, const uint8_t* pData, int nSize)
{
	D2_MAYBE_UNUSED(pServer);
	if (send(pClient->hSocket, (const char*)pData, nSize, 0) == SOCKET_ERROR)
	{
		WSAGetLastError();
		return FALSE;
	}
	return TRUE;
}
