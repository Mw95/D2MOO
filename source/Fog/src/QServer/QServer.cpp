#include <Safesock.h>
#include <QServer/QServer.h>
#include <System/System.h>
#include <Storm.h>

#include <cstring>

// Fog.0x6FF74EC0
static uint32_t gnQServerClientHashSize = 16;
// Fog.0x6FF74EC4
static uint32_t gnQServerClientHashMask = 15;
// Fog.0x6FF74EC8
static uint32_t gnQServerIPCountHashSize = 17;
// Fog.0x6FF74ECC
static uint32_t gnQServerHackListHashSize = 1;
// Fog.0x6FF7AEE0
static BOOL gbQServerUseReadThreads = FALSE;
// Fog.0x6FF7AEE4
// Time of the last change of the hack list, unused
static DWORD gdwQServerHackListChangeTime;

// Fog.0x6FF74ED0
// Network masks with the given number of bits, in network byte order
static const uint32_t gdwQServerNetworkMasks[33] = {
	0x00000000, 0x00000080, 0x000000C0, 0x000000E0, 0x000000F0, 0x000000F8, 0x000000FC, 0x000000FE,
	0x000000FF, 0x000080FF, 0x0000C0FF, 0x0000E0FF, 0x0000F0FF, 0x0000F8FF, 0x0000FCFF, 0x0000FEFF,
	0x0000FFFF, 0x0080FFFF, 0x00C0FFFF, 0x00E0FFFF, 0x00F0FFFF, 0x00F8FFFF, 0x00FCFFFF, 0x00FEFFFF,
	0x00FFFFFF, 0x80FFFFFF, 0xC0FFFFFF, 0xE0FFFFFF, 0xF0FFFFFF, 0xF8FFFFFF, 0xFCFFFFFF, 0xFEFFFFFF,
	0xFFFFFFFF,
};

// 1.10f: 0x6FF54F20
// Debug log, compiled out
static void QSERVER_Log(const char* szFileSubName, const char* szFormat, ...)
{
	D2_MAYBE_UNUSED(szFileSubName);
	D2_MAYBE_UNUSED(szFormat);
}

// Inlined
static CRITICAL_SECTION* QSERVER_GetClientLock(QServer* pServer, int nClientId)
{
	return &pServer->pClientHashLocks[nClientId & pServer->nClientHashMask];
}

// 1.10f: 0x6FF54120 (#10185)
void __stdcall FOG_QServerSetConfig(const D2QSConfigStrc* pConfig)
{
	gnQServerClientHashSize = pConfig->nClientHashSize;
	gnQServerClientHashMask = pConfig->nClientHashSize - 1;
	gnQServerIPCountHashSize = pConfig->nIPCountHashSize;
	gnQServerHackListHashSize = pConfig->nHackListHashSize;
	gbQServerUseReadThreads = pConfig->bUseReadThreads;
}

// 1.10f: 0x6FF54150 (#10149)
QServer* __stdcall FOG_InitializeServer(int nMode, int nMessageQueues, int nPort, BOOL bDisableNT, void* pfValidatePacket, void* pfOnConnect, void* pfOnDisconnect, void* pfLocalSend)
{
	QServer* pServer = (QServer*)FOG_Alloc(sizeof(QServer), __FILE__, __LINE__, 0);
	memset(pServer, 0, sizeof(QServer));

	pServer->nClientHashSize = gnQServerClientHashSize;
	pServer->nClientHashMask = gnQServerClientHashMask;
	pServer->nIPCountHashSize = gnQServerIPCountHashSize;
	pServer->bUseReadThreads = gbQServerUseReadThreads;

	pServer->nClientHashSize2 = gnQServerClientHashSize;
	pServer->pClientHash = (D2QSClientStrc**)FOG_Alloc(sizeof(D2QSClientStrc*) * gnQServerClientHashSize, __FILE__, __LINE__, 0);
	memset(reinterpret_cast<void*>(pServer->pClientHash), 0, sizeof(D2QSClientStrc*) * gnQServerClientHashSize);

	pServer->pClientHashLocks = (CRITICAL_SECTION*)FOG_Alloc(sizeof(CRITICAL_SECTION) * gnQServerClientHashSize, __FILE__, __LINE__, 0);
	memset(pServer->pClientHashLocks, 0, sizeof(CRITICAL_SECTION) * gnQServerClientHashSize);
	for (uint32_t i = 0; i < gnQServerClientHashSize; ++i)
	{
		InitializeCriticalSection(&pServer->pClientHashLocks[i]);
	}
	pServer->nClientHashLocks = gnQServerClientHashSize;

	pServer->pIPHash = (D2QSClientStrc**)FOG_Alloc(sizeof(D2QSClientStrc*) * gnQServerClientHashSize, __FILE__, __LINE__, 0);
	memset(reinterpret_cast<void*>(pServer->pIPHash), 0, sizeof(D2QSClientStrc*) * gnQServerClientHashSize);
	InitializeCriticalSection(&pServer->tIPHashLock);

	pServer->nIPCountHashSize2 = gnQServerIPCountHashSize;
	pServer->pIPCounts = (D2QSIPCountStrc**)FOG_Alloc(sizeof(D2QSIPCountStrc*) * gnQServerIPCountHashSize, __FILE__, __LINE__, 0);
	memset(reinterpret_cast<void*>(pServer->pIPCounts), 0, sizeof(D2QSIPCountStrc*) * gnQServerIPCountHashSize);

	pServer->nHackListHashSize = gnQServerHackListHashSize;
	pServer->pHackList = (D2QSHackListStrc**)FOG_Alloc(sizeof(D2QSHackListStrc*) * gnQServerHackListHashSize, __FILE__, __LINE__, 0);
	memset(reinterpret_cast<void*>(pServer->pHackList), 0, sizeof(D2QSHackListStrc*) * gnQServerHackListHashSize);

	QSERVER_Log("QSRV", "[QSInit]       Allocated TQSERVER = 0x%08X", pServer);

	pServer->pfOnConnect = (QServerClientCallback)pfOnConnect;
	pServer->pfValidatePacket = (QServerValidatePacketCallback)pfValidatePacket;
	pServer->nClients = 0;
	pServer->pReconnectsHead = nullptr;
	pServer->pReconnectsTail = nullptr;
	pServer->pfOnDisconnect = (QServerClientCallback)pfOnDisconnect;
	pServer->pfLocalSend = (QServerLocalSendCallback)pfLocalSend;
	pServer->dwLastHackListUpdate = (DWORD)-1;
	pServer->nHackListEntries = 0;
	pServer->bHackListEnabled = TRUE;
	InitializeCriticalSection(&pServer->tHackListLock);
	InitializeCriticalSection(&pServer->tStatsLock);

	for (int i = 0; i < QSERVER_MAX_PORTS; ++i)
	{
		pServer->hListenSockets[i] = INVALID_SOCKET;
	}

	pServer->pMessageQueuesHead = (D2QSMessageStrc**)FOG_Alloc(sizeof(D2QSMessageStrc*) * nMessageQueues, __FILE__, __LINE__, 0);
	for (int i = 0; i < nMessageQueues; ++i)
	{
		pServer->pMessageQueuesHead[i] = nullptr;
	}

	pServer->pMessageQueuesTail = (D2QSMessageStrc**)FOG_Alloc(sizeof(D2QSMessageStrc*) * nMessageQueues, __FILE__, __LINE__, 0);
	for (int i = 0; i < nMessageQueues; ++i)
	{
		pServer->pMessageQueuesTail[i] = nullptr;
	}

	pServer->nMessageQueues = nMessageQueues;
	pServer->pFreeMessages = nullptr;
	pServer->pFreeHackListEntries = nullptr;
	InitializeCriticalSection(&pServer->tLock);

	pServer->bUseNT = FOG_IsWindowsNT() && !bDisableNT;
	pServer->nMode = nMode;
	if (nMode == QSMODE_LOCAL || nMode == QSMODE_LOCAL2)
	{
		return pServer;
	}

	WSADATA tWSAData;
	if (WSAStartup(MAKEWORD(1, 1), &tWSAData) != 0)
	{
		return pServer;
	}

	if (pServer->bUseNT)
	{
		QSERVERNT_Initialize(pServer, nPort);
	}
	else
	{
		QSERVER98_Initialize(pServer, nPort);
	}
	return pServer;
}

// 1.10f: 0x6FF54480 (#10150)
SOCKET __stdcall FOG_QServerAddPort(QServer* pServer, int nPort)
{
	D2_ASSERTM(pServer->bUseNT, "!\"QSAddPort only valid for fUseNT\"");
	return QSERVERNT_AddPort(pServer, nPort);
}

// 1.10f: 0x6FF544C0 (#10186)
// Returns the flag of the port, and sets it if nValue is not 0
int __stdcall FOG_10186(QServer* pServer, int nPortIndex, int nValue)
{
	const int nPreviousValue = pServer->nPortFlags[nPortIndex];
	if (nValue)
	{
		pServer->nPortFlags[nPortIndex] = nValue;
	}
	return nPreviousValue;
}

// Inlined
static BOOL QSERVER_SendToClient(QServer* pServer, D2QSClientStrc* pClient, const uint8_t* pData, int nSize)
{
	if (pServer->bUseNT)
	{
		return QSERVERNT_Send(pServer, pClient, pData, nSize);
	}
	return QSERVER98_Send(pServer, pClient, pData, nSize);
}

// 1.10f: 0x6FF549B0 (#10153)
BOOL __stdcall FOG_QServerBroadcast(QServer* pServer, const uint8_t* pData, int nSize)
{
	for (uint32_t i = 0; i < pServer->nClientHashSize; ++i)
	{
		EnterCriticalSection(&pServer->pClientHashLocks[i]);
		for (D2QSClientStrc* pClient = pServer->pClientHash[i]; pClient; pClient = pClient->pNext)
		{
			if (!pClient->bClosing)
			{
				QSERVER_SendToClient(pServer, pClient, pData, nSize);
			}
		}
		LeaveCriticalSection(&pServer->pClientHashLocks[i]);
	}
	return TRUE;
}

// 1.10f: 0x6FF54890 (#10155)
// Frees all the queued messages
BOOL __stdcall FOG_QServerClearMessages(QServer* pServer)
{
	for (int i = 0; i < pServer->nMessageQueues; ++i)
	{
		EnterCriticalSection(&pServer->tLock);
		D2QSMessageStrc* pMessage = pServer->pMessageQueuesHead[i];
		pServer->pMessageQueuesHead[i] = nullptr;
		pServer->pMessageQueuesTail[i] = nullptr;
		LeaveCriticalSection(&pServer->tLock);

		while (pMessage)
		{
			D2QSMessageStrc* pNext = pMessage->pNext;
			FOG_Free(pMessage, __FILE__, __LINE__, 0);
			pMessage = pNext;
		}
	}
	return TRUE;
}

// 1.10f: 0x6FF544F0 (#10152)
// Sends a last message to all the clients, then destroys the server
int __stdcall FOG_10152(QServer* pServer, const uint8_t* pData, int nSize)
{
	if (!pServer)
	{
		return FALSE;
	}

	if (pData)
	{
		FOG_QServerBroadcast(pServer, pData, nSize);
	}

	if (pServer->nMode != QSMODE_LOCAL && pServer->nMode != QSMODE_LOCAL2)
	{
		if (pServer->bUseNT)
		{
			QSERVERNT_Shutdown(pServer);
		}
		else
		{
			QSERVER98_Shutdown(pServer);
		}
	}

	EnterCriticalSection(&pServer->tLock);
	for (D2QSReconnectStrc* pReconnect = pServer->pReconnectsHead; pReconnect; )
	{
		D2QSReconnectStrc* pNext = pReconnect->pNext;
		FOG_Free(pReconnect, __FILE__, __LINE__, 0);
		pReconnect = pNext;
	}
	pServer->pReconnectsHead = nullptr;
	LeaveCriticalSection(&pServer->tLock);

	EnterCriticalSection(&pServer->tHackListLock);
	for (uint32_t i = 0; i < pServer->nHackListHashSize; ++i)
	{
		for (D2QSHackListStrc* pEntry = pServer->pHackList[i]; pEntry; )
		{
			D2QSHackListStrc* pNext = pEntry->pNext;
			FOG_Free(pEntry, __FILE__, __LINE__, 0);
			pEntry = pNext;
		}
		pServer->pHackList[i] = nullptr;
	}
	pServer->nHackListEntries = 0;
	LeaveCriticalSection(&pServer->tHackListLock);

	FOG_QServerClearMessages(pServer);

	for (int i = 0; i < QSERVER_MAX_PORTS; ++i)
	{
		if (pServer->hListenSockets[i] != INVALID_SOCKET)
		{
			FOG_SOCKET_CloseSocket(pServer->hListenSockets[i]);
			pServer->hListenSockets[i] = INVALID_SOCKET;
		}
	}

	WSACleanup();

	EnterCriticalSection(&pServer->tLock);
	DeleteCriticalSection(&pServer->tLock);
	EnterCriticalSection(&pServer->tHackListLock);
	DeleteCriticalSection(&pServer->tHackListLock);
	EnterCriticalSection(&pServer->tStatsLock);
	DeleteCriticalSection(&pServer->tStatsLock);

	for (D2QSMessageStrc* pMessage = pServer->pFreeMessages; pMessage; )
	{
		D2QSMessageStrc* pNext = pMessage->pNext;
		FOG_Free(pMessage, __FILE__, __LINE__, 0);
		pMessage = pNext;
	}
	pServer->pFreeMessages = nullptr;

	for (D2QSHackListStrc* pEntry = pServer->pFreeHackListEntries; pEntry; )
	{
		D2QSHackListStrc* pNext = pEntry->pNext;
		FOG_Free(pEntry, __FILE__, __LINE__, 0);
		pEntry = pNext;
	}
	pServer->pFreeHackListEntries = nullptr;

	FOG_Free(reinterpret_cast<void*>(pServer->pMessageQueuesHead), __FILE__, __LINE__, 0);
	FOG_Free(reinterpret_cast<void*>(pServer->pMessageQueuesTail), __FILE__, __LINE__, 0);
	// Note: the IP count entries and the remaining clients are not freed
	FOG_Free(reinterpret_cast<void*>(pServer->pIPCounts), __FILE__, __LINE__, 0);
	FOG_Free(reinterpret_cast<void*>(pServer->pHackList), __FILE__, __LINE__, 0);
	FOG_Free(reinterpret_cast<void*>(pServer->pIPHash), __FILE__, __LINE__, 0);

	EnterCriticalSection(&pServer->tIPHashLock);
	DeleteCriticalSection(&pServer->tIPHashLock);
	FOG_Free(reinterpret_cast<void*>(pServer->pClientHash), __FILE__, __LINE__, 0);

	for (uint32_t i = 0; i < gnQServerClientHashSize; ++i)
	{
		EnterCriticalSection(&pServer->pClientHashLocks[i]);
		DeleteCriticalSection(&pServer->pClientHashLocks[i]);
	}
	FOG_Free(pServer->pClientHashLocks, __FILE__, __LINE__, 0);
	FOG_Free(pServer, __FILE__, __LINE__, 0);
	return TRUE;
}

// 1.10f: 0x6FF54920 (#10180)
int __stdcall FOG_10180(QServer* pServer)
{
	return pServer ? pServer->nClients : 0;
}

// 1.10f: 0x6FF54940 (#10174)
BOOL __stdcall FOG_QServerIsLocal(QServer* pServer)
{
	return pServer && (pServer->nMode == QSMODE_LOCAL || pServer->nMode == QSMODE_LOCAL2);
}

// 1.10f: 0x6FF54970 (#10151)
// Sets the maximum number of connections from the same IP
int __stdcall FOG_SetMaxClientsPerGame(QServer* pServer, int nMaxClients)
{
	if (pServer)
	{
		if (!nMaxClients)
		{
			nMaxClients = 1;
		}

		EnterCriticalSection(&pServer->tLock);
		pServer->nMaxConnectionsPerIP = nMaxClients;
		LeaveCriticalSection(&pServer->tLock);
	}
	return 0;
}

// 1.10f: 0x6FF54A60 (#10154)
// Waits for messages to be received, only for Windows 98
int __stdcall FOG_WaitForSingleObject(QServer* pServer, int nMilliseconds)
{
	if (pServer->bUseNT)
	{
		return 0;
	}
	return WaitForSingleObject(pServer->hDataEvent, nMilliseconds);
}

// Inlined
static void QSERVER_AddIPCount(QServer* pServer, uint32_t nIP)
{
	D2QSIPCountStrc** ppBucket = &pServer->pIPCounts[nIP % pServer->nIPCountHashSize];
	for (D2QSIPCountStrc* pEntry = *ppBucket; pEntry; pEntry = pEntry->pNext)
	{
		if (pEntry->nIP == nIP)
		{
			++pEntry->nCount;
			return;
		}
	}

	D2QSIPCountStrc* pEntry = (D2QSIPCountStrc*)FOG_Alloc(sizeof(D2QSIPCountStrc), __FILE__, __LINE__, 0);
	pEntry->nIP = nIP;
	pEntry->nCount = 1;
	pEntry->pNext = *ppBucket;
	*ppBucket = pEntry;
}

// 1.10f: 0x6FF573A0
static BOOL __fastcall QSERVER_RemoveIPCount(QServer* pServer, const uint32_t* pIP)
{
	const uint32_t nIP = *pIP;
	D2QSIPCountStrc** ppBucket = &pServer->pIPCounts[nIP % pServer->nIPCountHashSize];
	D2QSIPCountStrc* pPrevious = nullptr;
	for (D2QSIPCountStrc* pEntry = *ppBucket; pEntry; pEntry = pEntry->pNext)
	{
		if (pEntry->nIP == nIP)
		{
			--pEntry->nCount;
			if (pEntry->nCount <= 0)
			{
				if (pPrevious)
				{
					pPrevious->pNext = pEntry->pNext;
				}
				else
				{
					*ppBucket = pEntry->pNext;
				}
				FOG_Free(pEntry, __FILE__, __LINE__, 0);
			}
			return TRUE;
		}
		pPrevious = pEntry;
	}
	return FALSE;
}

// 1.10f: 0x6FF54A80
D2QSClientStrc* __fastcall QSERVER_CreateClient(QServer* pServer, SOCKET hSocket, uint32_t nIP)
{
	D2QSClientStrc* pClient = (D2QSClientStrc*)FOG_Alloc(sizeof(D2QSClientStrc), __FILE__, __LINE__, 0);
	memset(pClient, 0, sizeof(D2QSClientStrc));

	EnterCriticalSection(&pServer->tLock);
	const int nClientId = ++pServer->nLastClientId;
	LeaveCriticalSection(&pServer->tLock);

	pClient->nClientId = nClientId;
	pClient->tRead.nTag = QSOVERLAPPED_READ;
	pClient->hSocket = hSocket;
	pClient->nIP = nIP;
	pClient->dwLastFloodUpdate = 0;
	pClient->nFloodCost = 0;
	pClient->pWriteHead = nullptr;
	pClient->tWrite.nTag = QSOVERLAPPED_WRITE;
	const int32_t nTime = FOG_10055_GetSyncTime();
	pClient->nConnectTime = nTime;
	pClient->nLastReceiveTime = nTime;
	pClient->nLastSendTime = nTime;
	pClient->nUnknownTime = nTime;
	InitializeCriticalSection(&pClient->tLock);

	CRITICAL_SECTION* pBucketLock = QSERVER_GetClientLock(pServer, nClientId);
	EnterCriticalSection(pBucketLock);
	D2QSClientStrc** ppBucket = &pServer->pClientHash[nClientId & pServer->nClientHashMask];
	pClient->pNext = *ppBucket;
	*ppBucket = pClient;
	LeaveCriticalSection(pBucketLock);

	EnterCriticalSection(&pServer->tIPHashLock);
	D2QSClientStrc** ppIPBucket = &pServer->pIPHash[nIP & pServer->nClientHashMask];
	pClient->pNextInIPHash = *ppIPBucket;
	*ppIPBucket = pClient;
	LeaveCriticalSection(&pServer->tIPHashLock);

	EnterCriticalSection(&pServer->tLock);
	QSERVER_AddIPCount(pServer, nIP);
	InterlockedIncrement(&pClient->nRefCount);
	++pServer->nClients;
	LeaveCriticalSection(&pServer->tLock);
	return pClient;
}

// 1.10f: 0x6FF54F30
D2QSClientStrc* __fastcall QSERVER_FindClient(QServer* pServer, int nClientId)
{
	if (!pServer)
	{
		return nullptr;
	}

	CRITICAL_SECTION* pBucketLock = QSERVER_GetClientLock(pServer, nClientId);
	EnterCriticalSection(pBucketLock);
	D2QSClientStrc* pClient = pServer->pClientHash[nClientId & pServer->nClientHashMask];
	while (pClient && pClient->nClientId != nClientId)
	{
		pClient = pClient->pNext;
	}
	LeaveCriticalSection(pBucketLock);
	return pClient;
}

// 1.10f: 0x6FF54F90
D2QSClientStrc* __fastcall QSERVER_FindClientBySocket(QServer* pServer, SOCKET hSocket)
{
	for (uint32_t i = 0; i < pServer->nClientHashSize; ++i)
	{
		EnterCriticalSection(&pServer->pClientHashLocks[i]);
		for (D2QSClientStrc* pClient = pServer->pClientHash[i]; pClient; pClient = pClient->pNext)
		{
			if (pClient->hSocket == hSocket)
			{
				LeaveCriticalSection(&pServer->pClientHashLocks[i]);
				return pClient;
			}
		}
		LeaveCriticalSection(&pServer->pClientHashLocks[i]);
	}
	return nullptr;
}

// Inlined
static D2QSClientStrc* QSERVER_FindClientByIP(QServer* pServer, uint32_t nIP)
{
	EnterCriticalSection(&pServer->tIPHashLock);
	D2QSClientStrc* pClient = pServer->pIPHash[nIP & pServer->nClientHashMask];
	while (pClient && pClient->nIP != nIP)
	{
		pClient = pClient->pNextInIPHash;
	}
	LeaveCriticalSection(&pServer->tIPHashLock);
	return pClient;
}

// 1.10f: 0x6FF55010
void __fastcall QSERVER_AddRef(QServer* pServer, D2QSClientStrc* pClient)
{
	D2_MAYBE_UNUSED(pServer);
	InterlockedIncrement(&pClient->nRefCount);
}

// 1.10f: 0x6FF56680
static void __fastcall QSERVER_FreeClient(D2QSClientStrc* pClient)
{
	EnterCriticalSection(&pClient->tLock);
	for (D2QSWriteBufferStrc* pBuffer = pClient->pWriteHead; pBuffer; )
	{
		D2QSWriteBufferStrc* pNext = pBuffer->pNext;
		FOG_Free(pBuffer, __FILE__, __LINE__, 0);
		pBuffer = pNext;
	}
	pClient->pWriteHead = nullptr;
	// Note: the original deletes the critical section without leaving it
	LeaveCriticalSection(&pClient->tLock);
	DeleteCriticalSection(&pClient->tLock);
	FOG_Free(pClient, __FILE__, __LINE__, 0);
}

// 1.10f: Inlined in 0x6FF55020
static void QSERVER_RemoveClient(QServer* pServer, D2QSClientStrc* pClient)
{
	const int nClientId = pClient->nClientId;
	CRITICAL_SECTION* pBucketLock = QSERVER_GetClientLock(pServer, nClientId);
	EnterCriticalSection(pBucketLock);

	D2QSClientStrc** ppBucket = &pServer->pClientHash[nClientId & pServer->nClientHashMask];
	D2QSClientStrc* pPrevious = nullptr;
	D2QSClientStrc* pEntry = *ppBucket;
	while (pEntry && pEntry->nClientId != nClientId)
	{
		pPrevious = pEntry;
		pEntry = pEntry->pNext;
	}

	if (!pEntry)
	{
		QSERVER_Log("", "[sRemoveClient]  Couldn't remove TCLIENT id = %d", nClientId);
		LeaveCriticalSection(pBucketLock);
		QSERVER_FreeClient(pClient);
		return;
	}

	EnterCriticalSection(&pServer->tLock);
	--pServer->nClients;
	LeaveCriticalSection(&pServer->tLock);

	if (pPrevious)
	{
		pPrevious->pNext = pEntry->pNext;
	}
	else
	{
		*ppBucket = pEntry->pNext;
	}
	pEntry->pNext = nullptr;
	LeaveCriticalSection(pBucketLock);

	D2_ASSERT(nClientId == pEntry->nClientId);

	EnterCriticalSection(&pServer->tIPHashLock);
	D2QSClientStrc** ppIPBucket = &pServer->pIPHash[pEntry->nIP & pServer->nClientHashMask];
	D2QSClientStrc* pPreviousInIPHash = nullptr;
	D2QSClientStrc* pIPEntry = *ppIPBucket;
	while (pIPEntry && pIPEntry->nClientId != nClientId)
	{
		pPreviousInIPHash = pIPEntry;
		pIPEntry = pIPEntry->pNextInIPHash;
	}

	if (pIPEntry)
	{
		if (pPreviousInIPHash)
		{
			pPreviousInIPHash->pNextInIPHash = pIPEntry->pNextInIPHash;
		}
		else
		{
			*ppIPBucket = pIPEntry->pNextInIPHash;
		}
	}
	else
	{
		QSERVER_Log("", "[sRemoveClient]  Couldn't remove TCLIENT %d %s from IP-hash", nClientId, "");
	}
	LeaveCriticalSection(&pServer->tIPHashLock);

	EnterCriticalSection(&pServer->tLock);
	QSERVER_RemoveIPCount(pServer, &pEntry->nIP);
	LeaveCriticalSection(&pServer->tLock);

	QSERVER_FreeClient(pClient);
}

// 1.10f: 0x6FF55020
void __fastcall QSERVER_Release(QServer* pServer, D2QSClientStrc* pClient)
{
	if (InterlockedDecrement(&pClient->nRefCount))
	{
		return;
	}

	if (pServer->pfOnDisconnect)
	{
		pServer->pfOnDisconnect(pServer, pClient->nClientId, __FILE__, __LINE__);
	}

	QSERVER_RemoveClient(pServer, pClient);
}

// 1.10f: 0x6FF54C20
void __fastcall QSERVER_CloseClient(QServer* pServer, int nClientId, const char* szFile, int nLine)
{
	D2_MAYBE_UNUSED(szFile);
	D2_MAYBE_UNUSED(nLine);

	D2QSClientStrc* pClient = QSERVER_FindClient(pServer, nClientId);
	if (!pClient || pClient->bClosing)
	{
		return;
	}

	pClient->bClosing = TRUE;
	const int nResult = FOG_SOCKET_CloseSocket(pClient->hSocket);
	pClient->hSocket = INVALID_SOCKET;
	if (nResult)
	{
		FOG_TraceF("", "[QSrvCloseRemoteConnection] *** closesocket() err = %d ***", WSAGetLastError());
	}

	QSERVER_Release(pServer, pClient);
}

// Inlined
static BOOL QSERVER_IsInWhitelist(QServer* pServer, uint32_t nIP)
{
	for (int i = 0; i < pServer->nWhitelist; ++i)
	{
		if ((nIP & gdwQServerNetworkMasks[pServer->tWhitelist[i].nMaskBits]) == pServer->tWhitelist[i].nAddress)
		{
			return TRUE;
		}
	}
	return FALSE;
}

// 1.10f: 0x6FF55290
// Decreases the remaining times every second, and removes the expired entries
void __fastcall QSERVER_UpdateHackList(QServer* pServer)
{
	if (pServer->dwLastHackListUpdate == (DWORD)-1)
	{
		pServer->dwLastHackListUpdate = GetTickCount();
	}

	const DWORD dwNow = GetTickCount();
	const DWORD dwElapsed = dwNow - pServer->dwLastHackListUpdate;
	if (dwElapsed < 1000)
	{
		return;
	}

	const uint32_t nSeconds = dwElapsed / 1000;
	BOOL bChanged = FALSE;
	EnterCriticalSection(&pServer->tHackListLock);
	pServer->dwLastHackListUpdate = dwNow;
	for (uint32_t i = 0; i < pServer->nHackListHashSize; ++i)
	{
		D2QSHackListStrc* pPrevious = nullptr;
		D2QSHackListStrc* pEntry = pServer->pHackList[i];
		while (pEntry)
		{
			D2QSHackListStrc* pNext = pEntry->pNext;
			if (pEntry->nBanTime)
			{
				if (pEntry->nBanTime > nSeconds)
				{
					pEntry->nBanTime -= nSeconds;
				}
				else
				{
					pEntry->nBanTime = 0;
					pEntry->nLifeTime = nSeconds < QSERVER_HACKLIST_TIME ? QSERVER_HACKLIST_TIME : nSeconds;
				}
			}

			if (pEntry->nLifeTime)
			{
				if (pEntry->nLifeTime > nSeconds)
				{
					pEntry->nLifeTime -= nSeconds;
					pPrevious = pEntry;
				}
				else
				{
					if (pPrevious)
					{
						pPrevious->pNext = pNext;
					}
					else
					{
						pServer->pHackList[i] = pNext;
					}
					pEntry->pNext = pServer->pFreeHackListEntries;
					pServer->pFreeHackListEntries = pEntry;
					--pServer->nHackListEntries;
					bChanged = TRUE;
				}
			}
			else
			{
				pPrevious = pEntry;
			}
			pEntry = pNext;
		}
	}
	LeaveCriticalSection(&pServer->tHackListLock);

	if (bChanged)
	{
		const DWORD dwTime = GetTickCount();
		if (dwTime - gdwQServerHackListChangeTime > 2000)
		{
			gdwQServerHackListChangeTime = dwTime;
		}
	}
}

// 1.10f: 0x6FF55410
// Adds the IP to the hack list for QSERVER_HACKLIST_TIME seconds. An IP added again while in the list gets banned.
void __fastcall QSERVER_HackListAdd(QServer* pServer, const char* szFile, uint32_t nIP, int nLine)
{
	if (!pServer->bHackListEnabled || QSERVER_IsInWhitelist(pServer, nIP))
	{
		return;
	}

	if (pServer->pfHackList)
	{
		pServer->pfHackList(nIP, szFile, nLine);
	}

	EnterCriticalSection(&pServer->tHackListLock);
	D2QSHackListStrc** ppBucket = &pServer->pHackList[nIP % pServer->nHackListHashSize];
	for (D2QSHackListStrc* pEntry = *ppBucket; pEntry; pEntry = pEntry->pNext)
	{
		if (pEntry->nIP == nIP)
		{
			pEntry->nBanTime = QSERVER_HACKLIST_TIME;
			LeaveCriticalSection(&pServer->tHackListLock);
			return;
		}
	}

	D2QSHackListStrc* pEntry = pServer->pFreeHackListEntries;
	if (pEntry)
	{
		pServer->pFreeHackListEntries = pEntry->pNext;
	}
	else
	{
		pEntry = (D2QSHackListStrc*)FOG_Alloc(sizeof(D2QSHackListStrc), __FILE__, __LINE__, 0);
	}

	pEntry->nIP = nIP;
	pEntry->nLifeTime = QSERVER_HACKLIST_TIME;
	pEntry->nBanTime = 0;
	pEntry->pNext = *ppBucket;
	*ppBucket = pEntry;
	++pServer->nHackListEntries;
	LeaveCriticalSection(&pServer->tHackListLock);

	const DWORD dwTime = GetTickCount();
	if (dwTime - gdwQServerHackListChangeTime > 2000)
	{
		gdwQServerHackListChangeTime = dwTime;
	}
}

// 1.10f: 0x6FF55550
static void __fastcall QSERVER_HackListRemove(QServer* pServer, int nUnused1, uint32_t nIP, int nUnused2)
{
	D2_MAYBE_UNUSED(nUnused1);
	D2_MAYBE_UNUSED(nUnused2);

	if (!pServer->bHackListEnabled)
	{
		return;
	}

	EnterCriticalSection(&pServer->tHackListLock);
	D2QSHackListStrc** ppBucket = &pServer->pHackList[nIP % pServer->nHackListHashSize];
	D2QSHackListStrc* pPrevious = nullptr;
	D2QSHackListStrc* pEntry = *ppBucket;
	while (pEntry)
	{
		D2QSHackListStrc* pNext = pEntry->pNext;
		if (pEntry->nIP == nIP)
		{
			if (pPrevious)
			{
				pPrevious->pNext = pNext;
			}
			else
			{
				*ppBucket = pNext;
			}
			FOG_Free(pEntry, __FILE__, __LINE__, 0);
			--pServer->nHackListEntries;
		}
		else
		{
			pPrevious = pEntry;
		}
		pEntry = pNext;
	}
	LeaveCriticalSection(&pServer->tHackListLock);

	const DWORD dwTime = GetTickCount();
	if (dwTime - gdwQServerHackListChangeTime > 2000)
	{
		gdwQServerHackListChangeTime = dwTime;
	}
}

// 1.10f: 0x6FF55630
// Connecting while banned restarts the ban
BOOL __fastcall QSERVER_IsBanned(QServer* pServer, uint32_t nIP)
{
	EnterCriticalSection(&pServer->tHackListLock);
	for (D2QSHackListStrc* pEntry = pServer->pHackList[nIP % pServer->nHackListHashSize]; pEntry; pEntry = pEntry->pNext)
	{
		if (pEntry->nIP == nIP)
		{
			if (pEntry->nBanTime)
			{
				pEntry->nBanTime = QSERVER_HACKLIST_TIME;
				LeaveCriticalSection(&pServer->tHackListLock);
				return TRUE;
			}
			break;
		}
	}
	LeaveCriticalSection(&pServer->tHackListLock);
	return FALSE;
}

// 1.10f: 0x6FF556A0
BOOL __fastcall QSERVER_HasTooManyConnections(QServer* pServer, const uint32_t* pIP)
{
	if (pServer->nMaxConnectionsPerIP < 0)
	{
		return FALSE;
	}

	const uint32_t nIP = *pIP;
	EnterCriticalSection(&pServer->tLock);
	for (D2QSIPCountStrc* pEntry = pServer->pIPCounts[nIP % pServer->nIPCountHashSize]; pEntry; pEntry = pEntry->pNext)
	{
		if (pEntry->nIP == nIP)
		{
			const int nCount = pEntry->nCount;
			LeaveCriticalSection(&pServer->tLock);
			return nCount >= pServer->nMaxConnectionsPerIP;
		}
	}
	LeaveCriticalSection(&pServer->tLock);
	return FALSE;
}

// 1.10f: 0x6FF55710
BOOL __fastcall QSERVER_CheckReconnections(QServer* pServer, const uint32_t* pIP)
{
	if (pServer->nMaxConnectionsPerIP < 1)
	{
		return TRUE;
	}

	const uint32_t nIP = *pIP;
	const DWORD dwTime = GetTickCount();
	const uint32_t nMaxReconnections = 2 * pServer->nMaxConnectionsPerIP + 3;
	const DWORD dwNow = GetTickCount();

	// Remove the old entries
	EnterCriticalSection(&pServer->tLock);
	while (pServer->pReconnectsHead && dwNow - pServer->pReconnectsHead->dwTime > QSERVER_RECONNECT_DELAY)
	{
		D2QSReconnectStrc* pNext = pServer->pReconnectsHead->pNext;
		FOG_Free(pServer->pReconnectsHead, __FILE__, __LINE__, 0);
		pServer->pReconnectsHead = pNext;
	}

	if (D2QSReconnectStrc* pPrevious = pServer->pReconnectsHead)
	{
		while (D2QSReconnectStrc* pEntry = pPrevious->pNext)
		{
			if (dwNow - pEntry->dwTime > QSERVER_RECONNECT_DELAY)
			{
				pPrevious->pNext = pEntry->pNext;
				// Note: the original does not update the tail, which may point to the freed entry
				if (pServer->pReconnectsTail == pEntry)
				{
					pServer->pReconnectsTail = pPrevious;
				}
				FOG_Free(pEntry, __FILE__, __LINE__, 0);
			}
			else
			{
				pPrevious = pEntry;
			}
		}
	}
	LeaveCriticalSection(&pServer->tLock);

	EnterCriticalSection(&pServer->tLock);
	for (D2QSReconnectStrc* pEntry = pServer->pReconnectsHead; pEntry; pEntry = pEntry->pNext)
	{
		if (pEntry->nIP == nIP)
		{
			if (dwTime - pEntry->dwTime < QSERVER_RECONNECT_DELAY)
			{
				++pEntry->nCount;
				if (pEntry->nCount > nMaxReconnections)
				{
					LeaveCriticalSection(&pServer->tLock);
					return FALSE;
				}
			}
			else
			{
				pEntry->dwTime = dwTime;
				pEntry->nCount = 1;
			}
		}
	}

	// Note: the original always adds a new entry, even when the IP was already present
	D2QSReconnectStrc* pEntry = (D2QSReconnectStrc*)FOG_Alloc(sizeof(D2QSReconnectStrc), __FILE__, __LINE__, 0);
	pEntry->dwTime = dwTime;
	pEntry->nCount = 1;
	pEntry->pNext = nullptr;
	pEntry->nIP = nIP;
	if (pServer->pReconnectsHead)
	{
		pServer->pReconnectsTail->pNext = pEntry;
	}
	else
	{
		pServer->pReconnectsHead = pEntry;
	}
	pServer->pReconnectsTail = pEntry;
	LeaveCriticalSection(&pServer->tLock);
	return TRUE;
}

// 1.10f: 0x6FF570B0
static void __fastcall QSERVER_KickAndBanClient(QServer* pServer, int nClientId, const char* szFile, int nLine)
{
	if (!pServer->bHackListEnabled)
	{
		return;
	}

	uint32_t nIP = 0;
	CRITICAL_SECTION* pBucketLock = QSERVER_GetClientLock(pServer, nClientId);
	EnterCriticalSection(pBucketLock);
	for (D2QSClientStrc* pClient = pServer->pClientHash[nClientId & pServer->nClientHashMask]; pClient; pClient = pClient->pNext)
	{
		if (pClient->nClientId == nClientId)
		{
			nIP = pClient->nIP;
			break;
		}
	}
	LeaveCriticalSection(pBucketLock);

	QSERVER_CloseClient(pServer, nClientId, szFile, nLine);

	if (nIP)
	{
		QSERVER_HackListAdd(pServer, szFile, nIP, nLine);
	}
}

// 1.10f: 0x6FF558C0
BOOL __fastcall QSERVER_KickClientWithSameIP(QServer* pServer, const uint32_t* pIP, const char* szFile, int nLine)
{
	D2_MAYBE_UNUSED(szFile);
	D2_MAYBE_UNUSED(nLine);

	D2QSClientStrc* pClient = QSERVER_FindClientByIP(pServer, *pIP);
	if (pClient && !QSERVER_IsInWhitelist(pServer, pClient->nIP))
	{
		QSERVER_KickAndBanClient(pServer, pClient->nClientId, __FILE__, __LINE__);
	}
	return TRUE;
}

// 1.10f: 0x6FF55970 (#10184)
int __stdcall FOG_QServerGetMessageCount(QServer* pServer, int nMessageType)
{
	if (nMessageType >= pServer->nMessageQueues)
	{
		return -1;
	}

	int nCount = 0;
	EnterCriticalSection(&pServer->tLock);
	for (D2QSMessageStrc* pMessage = pServer->pMessageQueuesHead[nMessageType]; pMessage; pMessage = pMessage->pNext)
	{
		++nCount;
	}
	LeaveCriticalSection(&pServer->tLock);
	return nCount;
}

// 1.10f: 0x6FF559D0 (#10156)
// Pops a message of the queue. pBuffer receives the client id followed by the message, the size of the message is returned.
int __stdcall FOG_10156(QServer* pServer, int nMessageType, uint8_t* pBuffer, int nBufferSize)
{
	if (!pServer || nMessageType >= pServer->nMessageQueues)
	{
		return -1;
	}

	if (nBufferSize > QSERVER_READ_BUFFER_SIZE)
	{
		nBufferSize = QSERVER_READ_BUFFER_SIZE;
	}

	EnterCriticalSection(&pServer->tLock);
	D2QSMessageStrc* pMessage = pServer->pMessageQueuesHead[nMessageType];
	if (!pMessage)
	{
		LeaveCriticalSection(&pServer->tLock);
		return -1;
	}

	pServer->pMessageQueuesHead[nMessageType] = pMessage->pNext;
	if (pServer->pMessageQueuesTail[nMessageType] == pMessage)
	{
		pServer->pMessageQueuesTail[nMessageType] = nullptr;
	}
	LeaveCriticalSection(&pServer->tLock);

	int nCopySize = pMessage->nSize + (int)sizeof(pMessage->nClientId);
	if (nCopySize > nBufferSize)
	{
		nCopySize = nBufferSize;
	}
	memcpy(pBuffer, pMessage, nCopySize);

	const int nSize = pMessage->nSize;
	memset(pMessage, 0, sizeof(D2QSMessageStrc));

	EnterCriticalSection(&pServer->tLock);
	pMessage->pNext = pServer->pFreeMessages;
	pServer->pFreeMessages = pMessage;
	LeaveCriticalSection(&pServer->tLock);
	return nSize;
}

// Inlined
static D2QSMessageStrc* QSERVER_AllocMessage(QServer* pServer)
{
	if (pServer->pFreeMessages)
	{
		EnterCriticalSection(&pServer->tLock);
		D2QSMessageStrc* pMessage = pServer->pFreeMessages;
		if (pMessage)
		{
			pServer->pFreeMessages = pMessage->pNext;
		}
		else
		{
			pMessage = (D2QSMessageStrc*)FOG_Alloc(sizeof(D2QSMessageStrc), __FILE__, __LINE__, 0);
		}
		LeaveCriticalSection(&pServer->tLock);
		return pMessage;
	}

	return (D2QSMessageStrc*)FOG_Alloc(sizeof(D2QSMessageStrc), __FILE__, __LINE__, 0);
}

// Inlined
static void QSERVER_QueueMessage(QServer* pServer, D2QSMessageStrc* pMessage, int nMessageType)
{
	EnterCriticalSection(&pServer->tLock);
	if (pServer->pMessageQueuesTail[nMessageType])
	{
		pServer->pMessageQueuesTail[nMessageType]->pNext = pMessage;
	}
	else
	{
		pServer->pMessageQueuesHead[nMessageType] = pMessage;
	}
	pServer->pMessageQueuesTail[nMessageType] = pMessage;
	LeaveCriticalSection(&pServer->tLock);
}

// Inlined
static int QSERVER_GetMessageDataSize(int nSize)
{
	// Note: the original copies up to the size of the read buffer, overwriting the size of the message which is set afterwards
	return nSize < (int)sizeof(D2QSMessageStrc::pData) ? nSize : (int)sizeof(D2QSMessageStrc::pData);
}

// 1.10f: 0x6FF55AD0
void __fastcall QSERVER_ProcessClientData(QServer* pServer, D2QSClientStrc* pClient)
{
	while (pServer->pfValidatePacket)
	{
		int nPacketSize = 0;
		int nHeaderSize = 0;
		int nMessageType = 0;
		int nCost = 0;

		EnterCriticalSection(&pClient->tLock);
		const int nBufferSize = pClient->nReadBufferSize;
		LeaveCriticalSection(&pClient->tLock);

		const int nStatus = pServer->pfValidatePacket(pClient->pReadBuffer, nBufferSize, &nPacketSize, &nHeaderSize, &nMessageType, &nCost, pClient->nClientId, pClient->nUserData);
		switch (nStatus)
		{
		case QSPACKET_INCOMPLETE:
			return;

		case QSPACKET_INVALID:
			QSERVER_KickAndBanClient(pServer, pClient->nClientId, __FILE__, __LINE__);
			return;

		case QSPACKET_SKIP:
			break;

		case QSPACKET_QUEUE_LIMITED:
			if (pServer->bHackListEnabled)
			{
				const DWORD dwNow = GetTickCount();
				EnterCriticalSection(&pClient->tLock);
				pClient->nFloodCost += nCost;
				LeaveCriticalSection(&pClient->tLock);

				if (pClient->nFloodCost > QSERVER_FLOOD_MAX_COST)
				{
					if (!QSERVER_IsInWhitelist(pServer, pClient->nIP))
					{
						QSERVER_KickAndBanClient(pServer, pClient->nClientId, __FILE__, __LINE__);
						return;
					}
				}
				else if (dwNow - pClient->dwLastFloodUpdate > 1000)
				{
					EnterCriticalSection(&pClient->tLock);
					pClient->dwLastFloodUpdate = dwNow;
					pClient->nFloodCost = pClient->nFloodCost >= 200 ? pClient->nFloodCost - 200 : 0;
					LeaveCriticalSection(&pClient->tLock);
				}
			}
			// fallthrough
		default:
		{
			D2QSMessageStrc* pMessage = QSERVER_AllocMessage(pServer);
			const int nDataSize = nPacketSize - nHeaderSize;
			if (nDataSize > 0)
			{
				EnterCriticalSection(&pClient->tLock);
				memcpy(pMessage->pData, &pClient->pReadBuffer[nHeaderSize], QSERVER_GetMessageDataSize(nDataSize));
				LeaveCriticalSection(&pClient->tLock);
			}

			pMessage->nSize = nDataSize;
			pMessage->dwTime = GetTickCount();
			pMessage->pNext = nullptr;
			pMessage->nClientId = pClient->nClientId;

			D2_ASSERT(nMessageType < pServer->nMessageQueues);
			QSERVER_QueueMessage(pServer, pMessage, nMessageType);
			break;
		}
		}

		EnterCriticalSection(&pClient->tLock);
		pClient->nReadBufferSize -= nPacketSize;
		D2_ASSERT(nPacketSize + pClient->nReadBufferSize <= QSERVER_READ_BUFFER_SIZE);
		memmove(pClient->pReadBuffer, &pClient->pReadBuffer[nPacketSize], pClient->nReadBufferSize);
		LeaveCriticalSection(&pClient->tLock);
	}
}

// 1.10f: 0x6FF55E60 (#10177)
// Waits for messages to be received
int __stdcall FOG_10177(QServer* pServer, int nMilliseconds)
{
	if (pServer->bUseNT)
	{
		return QSERVERNT_WaitForData(pServer, nMilliseconds);
	}
	return WaitForSingleObject(pServer->hDataEvent, nMilliseconds) == WAIT_OBJECT_0;
}

// 1.10f: 0x6FF55EA0 (#10157)
int __stdcall FOG_10157(QServer* pServer, int nClientId, const uint8_t* pData, int nSize)
{
	if (!pServer)
	{
		return FALSE;
	}

	if ((pServer->nMode == QSMODE_LOCAL || pServer->nMode == QSMODE_LOCAL2) && pServer->pfLocalSend)
	{
		return pServer->pfLocalSend(pServer, pData, nSize);
	}

	D2QSClientStrc* pClient = QSERVER_FindClient(pServer, nClientId);
	if (!pClient || pClient->bClosing)
	{
		return FALSE;
	}
	return QSERVER_SendToClient(pServer, pClient, pData, nSize);
}

// 1.10f: 0x6FF56180 (#10159)
int __stdcall FOG_10159(QServer* pServer, int nClientId, char* szBuffer, int nBufferSize)
{
	CRITICAL_SECTION* pBucketLock = QSERVER_GetClientLock(pServer, nClientId);
	EnterCriticalSection(pBucketLock);
	for (D2QSClientStrc* pClient = pServer->pClientHash[nClientId & pServer->nClientHashMask]; pClient; pClient = pClient->pNext)
	{
		if (pClient->nClientId == nClientId)
		{
			in_addr tAddress;
			tAddress.s_addr = pClient->nIP;
			SStrCopy(szBuffer, inet_ntoa(tAddress), nBufferSize);
			LeaveCriticalSection(pBucketLock);
			return 0;
		}
	}
	LeaveCriticalSection(pBucketLock);
	szBuffer[0] = '\0';
	return 0;
}

// 1.10f: 0x6FF56210 (#10158)
int __stdcall FOG_10158(QServer* pServer, int nClientId)
{
	CRITICAL_SECTION* pBucketLock = QSERVER_GetClientLock(pServer, nClientId);
	EnterCriticalSection(pBucketLock);
	for (D2QSClientStrc* pClient = pServer->pClientHash[nClientId & pServer->nClientHashMask]; pClient; pClient = pClient->pNext)
	{
		if (pClient->nClientId == nClientId)
		{
			const uint32_t nIP = pClient->nIP;
			LeaveCriticalSection(pBucketLock);
			return (int)nIP;
		}
	}
	LeaveCriticalSection(pBucketLock);
	return 0;
}

// 1.10f: 0x6FF56280 (#10160)
uint32_t __stdcall FOG_QServerGetClientPeerIP(QServer* pServer, int nClientId)
{
	CRITICAL_SECTION* pBucketLock = QSERVER_GetClientLock(pServer, nClientId);
	EnterCriticalSection(pBucketLock);
	for (D2QSClientStrc* pClient = pServer->pClientHash[nClientId & pServer->nClientHashMask]; pClient; pClient = pClient->pNext)
	{
		if (pClient->nClientId == nClientId)
		{
			const SOCKET hSocket = pClient->hSocket;
			LeaveCriticalSection(pBucketLock);

			sockaddr_in tAddress{};
			int nAddressSize = sizeof(tAddress);
			getpeername(hSocket, (sockaddr*)&tAddress, &nAddressSize);
			return tAddress.sin_addr.s_addr;
		}
	}
	LeaveCriticalSection(pBucketLock);
	return 0;
}

// 1.10f: 0x6FF56310 (#10161)
int __stdcall FOG_10161(QServer* pServer, int nClientId)
{
	CRITICAL_SECTION* pBucketLock = QSERVER_GetClientLock(pServer, nClientId);
	EnterCriticalSection(pBucketLock);
	for (D2QSClientStrc* pClient = pServer->pClientHash[nClientId & pServer->nClientHashMask]; pClient; pClient = pClient->pNext)
	{
		if (pClient->nClientId == nClientId)
		{
			const SOCKET hSocket = pClient->hSocket;
			LeaveCriticalSection(pBucketLock);
			return (int)hSocket;
		}
	}
	LeaveCriticalSection(pBucketLock);
	return -1;
}

// 1.10f: 0x6FF56380 (#10162)
// Disconnects the client and bans its IP
int __stdcall FOG_10162(QServer* pServer, int nClientId, const char* szFile, int nLine)
{
	if (!pServer->bHackListEnabled)
	{
		return 0;
	}

	D2QSClientStrc* pClient = QSERVER_FindClient(pServer, nClientId);
	if (!pClient)
	{
		return 0;
	}

	const uint32_t nIP = pClient->nIP;
	QSERVER_CloseClient(pServer, nClientId, szFile, nLine);
	QSERVER_HackListAdd(pServer, szFile, nIP, nLine);
	return 0;
}

// 1.10f: 0x6FF566E0 (#10163)
// Bans the IP, and disconnects the client using it
int __stdcall FOG_10163(QServer* pServer, int nIP, const char* szFile, int nLine)
{
	if (!pServer->bHackListEnabled)
	{
		return 0;
	}

	if (D2QSClientStrc* pClient = QSERVER_FindClientByIP(pServer, nIP))
	{
		QSERVER_CloseClient(pServer, pClient->nClientId, szFile, nLine);
	}

	QSERVER_HackListAdd(pServer, szFile, nIP, nLine);
	return 0;
}

// 1.10f: 0x6FF569D0 (#10164)
// Removes the IP from the hack list
int __stdcall FOG_10164(QServer* pServer, int nIP, int a3, int a4)
{
	if (pServer->bHackListEnabled)
	{
		QSERVER_HackListRemove(pServer, a3, nIP, a4);
	}
	return TRUE;
}

// 1.10f: 0x6FF56A10 (#10165)
// Disconnects the client
int __stdcall FOG_10165(QServer* pServer, int nClientId, const char* szFile, int nLine)
{
	if (pServer)
	{
		QSERVER_CloseClient(pServer, nClientId, szFile, nLine);
	}
	return 0;
}

// 1.10f: 0x6FF56C90 (#10166)
// Disconnects the client using the IP
int __stdcall FOG_10166(QServer* pServer, int nIP, int a3, int a4)
{
	D2_MAYBE_UNUSED(a3);
	D2_MAYBE_UNUSED(a4);

	if (D2QSClientStrc* pClient = QSERVER_FindClientByIP(pServer, nIP))
	{
		QSERVER_CloseClient(pServer, pClient->nClientId, __FILE__, __LINE__);
	}
	// Note: the original returns a pointer to the string representation of the IP
	return TRUE;
}

// 1.10f: 0x6FF56F70 (#10170)
int __stdcall FOG_10170(QServer* pServer, int pfHackListCallback)
{
	D2_ASSERT(pServer != NULL);
	pServer->pfHackList = (QServerHackListCallback)(intptr_t)pfHackListCallback;
	return 0;
}

// 1.10f: 0x6FF56FB0 (#10171)
int __stdcall FOG_10171(QServer* pServer, void* pfCallback)
{
	pServer->pfUnknownCallback = pfCallback;
	return 0;
}

// 1.10f: 0x6FF56FD0 (#10172)
int __stdcall FOG_10172(QServer* pServer, int nClientId, int nUserData)
{
	if (!nClientId || !pServer)
	{
		return 0;
	}

	if (D2QSClientStrc* pClient = QSERVER_FindClient(pServer, nClientId))
	{
		pClient->nUserData = nUserData;
	}
	return 0;
}

// 1.10f: 0x6FF57040 (#10173)
int __stdcall FOG_10173(QServer* pServer, int nClientId)
{
	if (!nClientId || !pServer)
	{
		return 0;
	}

	D2QSClientStrc* pClient = QSERVER_FindClient(pServer, nClientId);
	return pClient ? pClient->nUserData : 0;
}

// 1.10f: 0x6FF57420 (#10175)
// Queues a message as if it was received from the client
int __stdcall FOG_10175(QServer* pServer, const uint8_t* pData, int nSize, int nClientId)
{
	int nPacketSize = 0;
	int nHeaderSize = 0;
	int nMessageType = 0;
	int nCost = 0;
	const int nStatus = pServer->pfValidatePacket((uint8_t*)pData, nSize, &nPacketSize, &nHeaderSize, &nMessageType, &nCost, 0, 0);
	if (nStatus != QSPACKET_QUEUE && nStatus != QSPACKET_QUEUE_LIMITED)
	{
		return FALSE;
	}

	D2QSMessageStrc* pMessage = QSERVER_AllocMessage(pServer);
	const int nDataSize = nPacketSize - nHeaderSize;
	// Note: the original does not check the size
	if (nDataSize > 0)
	{
		memcpy(pMessage->pData, &pData[nHeaderSize], QSERVER_GetMessageDataSize(nDataSize));
	}
	pMessage->nSize = nDataSize;
	pMessage->dwTime = GetTickCount();
	pMessage->pNext = nullptr;
	pMessage->nClientId = nClientId;

	if (nMessageType < pServer->nMessageQueues)
	{
		QSERVER_QueueMessage(pServer, pMessage, nMessageType);
	}
	else
	{
		// Note: the original leaks the message
		FOG_Free(pMessage, __FILE__, __LINE__, 0);
	}
	return TRUE;
}

// 1.10f: 0x6FF575A0 (#10178)
int __stdcall FOG_SetHackListEnabled(QServer* pServer, BOOL bHackListEnabled)
{
	pServer->bHackListEnabled = bHackListEnabled;
	return 0;
}

// 1.10f: 0x6FF575C0 (#10181)
// Returns the number of queued messages
int __stdcall FOG_10181(QServer* pServer)
{
	if (!pServer)
	{
		return 0;
	}

	int nCount = 0;
	EnterCriticalSection(&pServer->tLock);
	for (int i = 0; i < pServer->nMessageQueues; ++i)
	{
		for (D2QSMessageStrc* pMessage = pServer->pMessageQueuesHead[i]; pMessage; pMessage = pMessage->pNext)
		{
			++nCount;
		}
	}
	LeaveCriticalSection(&pServer->tLock);
	return nCount;
}

// 1.10f: 0x6FF57630 (#10187)
// Adds a network to the whitelist, nAddress is in network byte order
int __fastcall FOG_10187(QServer* pServer, int nMaskBits, int nAddress)
{
	if (pServer->nWhitelist >= QSERVER_MAX_WHITELIST)
	{
		return 0;
	}

	for (int i = 0; i < pServer->nWhitelist; ++i)
	{
		if (pServer->tWhitelist[i].nAddress == (uint32_t)nAddress)
		{
			return 0;
		}
	}

	// Note: the original does not check the number of bits
	if (nMaskBits < 0 || nMaskBits > 32)
	{
		return 0;
	}

	pServer->tWhitelist[pServer->nWhitelist].nAddress = nAddress;
	pServer->tWhitelist[pServer->nWhitelist].nMaskBits = nMaskBits;
	++pServer->nWhitelist;
	return 0;
}

// 1.10f: 0x6FF57680 (#10188)
BOOL __fastcall FOG_QServerIsWhitelisted(QServer* pServer, uint32_t nIP)
{
	return QSERVER_IsInWhitelist(pServer, nIP);
}
