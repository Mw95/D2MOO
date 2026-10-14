#include "BnConnect.h"

#include <climits>
#include <cstdlib>
#include <cstring>

#include <Fog.h>
#include <Safesock.h>
#include <Storm.h>

#include "BNetGW.h"
#include "BnCache.h"
#include "BnDownload.h"
#include "BnImports.h"
#include "BnLog.h"
#include "BnMessQueue.h"
#include "BNNews.h"
#include "BnRecv.h"
#include "BnSend.h"
#include "BnSRP.h"


#pragma warning (disable: 28159)


char gszBnUniqueName[256];
char gszBnGatewayHost[256];
u_long gnBnHostAddress;
int32_t gnBnConnectionState;
hostent gtBnHostEnt;
char* gapBnHostAddressList[2];
BnServerListThreadParams gtBnServerListThreadParams;
char gszBnServerList[512];
FSafeSock* gpBnSafeSock;
volatile LONG gnBnRecvThreads;
BOOL gbBnServerConnected;
BOOL gbBnStopConnection;
volatile LONG gnBnConnectThreads;
BOOL gbBnEmailRequested;


//Bnclient.0x6FF01000
BOOL __fastcall BNET_SetUniqueName(const char* szUniqueName)
{
	SStrCopy(gszBnUniqueName, szUniqueName, sizeof(gszBnUniqueName));
	return TRUE;
}

//Bnclient.0x6FF01020
const char* __stdcall BNET_GetUniqueName()
{
	return gszBnUniqueName;
}

//Bnclient.0x6FF01030
BOOL __fastcall BNET_HandleChatEvent(const uint8_t* pData, uint32_t nSize)
{
	BNMESSQUEUE_PushData(0, pData, nSize);
	return TRUE;
}

//Bnclient.0x6FF01050
void __cdecl operator delete(void* pMemory) noexcept
{
	if (pMemory)
	{
		SMemFree(pMemory, "delete", -1, 0);
	}
}

//Bnclient.0x6FF01070
BOOL __cdecl BNET_IsExpansion()
{
	return FOG_IsExpansion();
}

//Bnclient.0x6FF01080
static BOOL __stdcall sFastestConnect(char* szServerList)
{
	BNET_DebugTrace("sFastestConnect()");

	BnServerConnection aConnections[32];
	memset(aConnections, 0x00, sizeof(aConnections));

	BNDOWNLOAD_SetStatus(BNDOWNLOADSTATUS_IDLE);

	if (!szServerList)
	{
		return TRUE;
	}

	gbBnServerConnected = FALSE;
	gnBnConnectionState = BNCONNECTIONSTATE_SEARCHING_FASTEST_SERVER;
	Sleep(10);
	BNLOG_Printf("searching for the fastest server");

	char* szHost = strtok(szServerList, " ,;");
	int nConnections = 0;
	DWORD dwLastConnectTick = GetTickCount() - 5000;
	int nTimeouts = 0;
	timeval tTimeout = { 1, 0 };

	if (!gpBnSafeSock)
	{
		BnServerConnection* pNextConnection = aConnections;
		while (!gbBnStopConnection)
		{
			if (GetTickCount() - dwLastConnectTick >= 5000)
			{
				dwLastConnectTick = GetTickCount();
				if (szHost && *szHost && nConnections < ARRAYSIZE(aConnections))
				{
					BNET_DebugTrace("  Try to connect to %s", szHost);
					strcpy(pNextConnection->szHost, szHost);
					pNextConnection->pSafeSock = FOG_SOCKET_ConnectEx(pNextConnection->szHost, 6112, BNET_ReceiveThread, nullptr, "Client->BNet", TRUE);
					++nConnections;
					++pNextConnection;
					szHost = strtok(nullptr, " ,;");
				}
			}

			fd_set tWriteFds;
			fd_set tExceptFds;
			FD_ZERO(&tWriteFds);
			FD_ZERO(&tExceptFds);

			int nPendingConnections = 0;
			for (int i = 0; i < nConnections; ++i)
			{
				if (FSafeSock* pSafeSock = aConnections[i].pSafeSock)
				{
					FD_SET(pSafeSock->nSocket, &tWriteFds);
					FD_SET(pSafeSock->nSocket, &tExceptFds);
					++nPendingConnections;
				}
			}

			if (!nPendingConnections)
			{
				if (!szHost || !*szHost)
				{
					break;
				}

				Sleep(10);
			}
			else
			{
				const int nResult = select(0, nullptr, &tWriteFds, &tExceptFds, &tTimeout);
				if (nResult == 0)
				{
					if (nTimeouts++ > 60)
					{
						break;
					}
				}
				else if (nResult == SOCKET_ERROR)
				{
					WSAGetLastError();
				}
				else
				{
					while (tExceptFds.fd_count)
					{
						--tExceptFds.fd_count;
						const SOCKET nSocket = tExceptFds.fd_array[tExceptFds.fd_count];
						for (int i = 0; i < nConnections; ++i)
						{
							if (aConnections[i].pSafeSock && aConnections[i].pSafeSock->nSocket == nSocket)
							{
								FOG_SOCKET_Destroy(aConnections[i].pSafeSock);
								aConnections[i].pSafeSock = nullptr;
								break;
							}
						}
					}

					while (tWriteFds.fd_count)
					{
						--tWriteFds.fd_count;
						const SOCKET nSocket = tWriteFds.fd_array[tWriteFds.fd_count];
						for (int i = 0; i < nConnections; ++i)
						{
							if (aConnections[i].pSafeSock && aConnections[i].pSafeSock->nSocket == nSocket)
							{
								gpBnSafeSock = aConnections[i].pSafeSock;
								gpBnSafeSock->bConnected = TRUE;
								gpBnSafeSock->bConnecting = FALSE;
								break;
							}
						}
					}
				}
			}

			if (gpBnSafeSock)
			{
				break;
			}
		}
	}

	for (int i = 0; i < nConnections; ++i)
	{
		if (aConnections[i].pSafeSock && aConnections[i].pSafeSock != gpBnSafeSock)
		{
			FOG_SOCKET_Destroy(aConnections[i].pSafeSock);
			aConnections[i].pSafeSock = nullptr;
		}
	}

	if (!gpBnSafeSock)
	{
		BNLOG_Printf("no servers found");
		return FALSE;
	}

	gbBnServerConnected = TRUE;

	BnMessQueueErrorInfo tErrorInfo = {};
	BNMESSQUEUE_PeekLastError(&tErrorInfo);
	if (BNRECV_IsDisconnected() || tErrorInfo.nError || !gpBnSafeSock)
	{
		BNET_DebugTrace("  Error, not connected.");
		return FALSE;
	}

	sockaddr_in tPeerAddress = {};
	int nPeerAddressLength = sizeof(tPeerAddress);
	if (FOG_SOCKET_GetPeerName(gpBnSafeSock, (sockaddr*)&tPeerAddress, &nPeerAddressLength))
	{
		BNLOG_Printf("Connected to server %d.%d.%d.%d",
			tPeerAddress.sin_addr.S_un.S_un_b.s_b1,
			tPeerAddress.sin_addr.S_un.S_un_b.s_b2,
			tPeerAddress.sin_addr.S_un.S_un_b.s_b3,
			tPeerAddress.sin_addr.S_un.S_un_b.s_b4);
	}

	gnBnConnectionState = BNCONNECTIONSTATE_ACCESSING_ACCOUNTS;
	Sleep(10);
	BNLOG_Printf("accessing accounts");

	FOG_SOCKET_SetBlockingMode(gpBnSafeSock, FALSE);

	char nProtocolId = 1;
	if (FOG_SOCKET_Send(gpBnSafeSock, &nProtocolId, sizeof(nProtocolId)) <= 0)
	{
		BNET_DebugTrace("  Failed send.");
		return FALSE;
	}

	BNRECV_ResetMessage(SID_AUTH_INFO);
	BNSEND_AuthInfo();
	if (!BNRECV_WaitForMessage(SID_AUTH_INFO))
	{
		BNMESSQUEUE_PeekLastError(&tErrorInfo);
		if (BNRECV_IsDisconnected() || tErrorInfo.nError || !gpBnSafeSock)
		{
			FOG_SOCKET_Destroy(gpBnSafeSock);
			gpBnSafeSock = nullptr;
			return FALSE;
		}
	}

	if (BNRECV_IsDisconnected())
	{
		BNMESSQUEUE_SetError(11);
		return TRUE;
	}

	gnBnConnectionState = BNCONNECTIONSTATE_CHECKING_VERSION;
	Sleep(10);
	BNLOG_Printf("Checking for the latest version");
	BNDOWNLOAD_SetStatus(BNDOWNLOADSTATUS_IDLE);

	BNRECV_ResetMessage(SID_AUTH_CHECK);
	if (!BNSEND_AuthCheck())
	{
		return FALSE;
	}

	if (!BNRECV_WaitForMessage(SID_AUTH_CHECK))
	{
		return FALSE;
	}

	BnMessQueueErrorInfo tAuthCheckErrorInfo = {};
	BNMESSQUEUE_PeekLastError(&tAuthCheckErrorInfo);
	if (!tAuthCheckErrorInfo.nError && BNRECV_GetMessageResult(SID_AUTH_CHECK))
	{
		BNDOWNLOAD_RequestFileTime("bnserver-D2DV.ini", BNDOWNLOAD_REQUEST_BNSERVER_INI);
		BNLOG_Printf("Connected to Battle.net");
	}

	return TRUE;
}

//Bnclient.0x6FF01620
DWORD __stdcall BNET_GetServersListThread(void* pParam)
{
	BnServerListThreadParams* pParams = (BnServerListThreadParams*)pParam;
	char* szServerList = pParams->szServerList;
	const char* szGatewayHost = pParams->szGatewayHost;

	hostent* pHostEnt = nullptr;
	if (isdigit(szGatewayHost[0]))
	{
		const u_long nAddress = inet_addr(szGatewayHost);
		if (nAddress == INADDR_NONE)
		{
			BNLOG_Printf("ERROR GetServersList: inet_addr failed to convert IP (%d)", WSAGetLastError());
			return FALSE;
		}

		gtBnHostEnt.h_addr_list = gapBnHostAddressList;
		gapBnHostAddressList[0] = (char*)&gnBnHostAddress;
		gapBnHostAddressList[1] = nullptr;
		pHostEnt = &gtBnHostEnt;
		gnBnHostAddress = nAddress;
	}
	else
	{
		pHostEnt = gethostbyname(szGatewayHost);
		if (!pHostEnt)
		{
			BNLOG_Printf("ERROR GetServersList: gethostbyname failed to get server list (%d)", WSAGetLastError());
			return FALSE;
		}
	}

	char** ppAddressList = pHostEnt->h_addr_list;

	BNET_DebugTrace("");
	BNET_DebugTrace("Original servlist:");

	int nAddresses = 0;
	for (const uint8_t* pAddress = (const uint8_t*)ppAddressList[0]; pAddress; pAddress = (const uint8_t*)ppAddressList[++nAddresses])
	{
		BNET_DebugTrace("%d --> %d.%d.%d.%d", nAddresses, pAddress[0], pAddress[1], pAddress[2], pAddress[3]);
	}

	BNET_DebugTrace("");
	BNET_DebugTrace("Scrambled servlist:");

	srand(GetTickCount());

	const int nLastAddress = nAddresses - 1;
	for (int swapA = 0; swapA < nLastAddress; ++swapA)
	{
		const int swapB = swapA + rand() * (nLastAddress - swapA) / 32768;
		D2_ASSERT(swapA <= swapB);

		BNET_DebugTrace("%d <-> %d SWAP", swapA, swapB);

		const uint32_t nAddress = *(uint32_t*)ppAddressList[swapA];
		*(uint32_t*)ppAddressList[swapA] = *(uint32_t*)ppAddressList[swapB];
		*(uint32_t*)ppAddressList[swapB] = nAddress;
	}

	BNET_DebugTrace("");

	char* pOutput = szServerList;
	for (char** ppAddress = pHostEnt->h_addr_list; *ppAddress; ++ppAddress)
	{
		pOutput += SStrCopy(pOutput, inet_ntoa(*(in_addr*)*ppAddress), INT_MAX);
		pOutput += SStrCopy(pOutput, ";", INT_MAX);
	}

	if (pOutput > szServerList)
	{
		pOutput[-1] = '\0';
	}

	return TRUE;
}

//Bnclient.0x6FF01830
void __fastcall BNET_GetServersList(char* szServerList, const char* szGatewayHost)
{
	gnBnConnectionState = BNCONNECTIONSTATE_GETTING_SERVER_LIST;
	Sleep(10);

	*szServerList = '\0';
	gtBnServerListThreadParams.szServerList = szServerList;
	gtBnServerListThreadParams.szGatewayHost = szGatewayHost;

	DWORD dwThreadId = 0;
	HANDLE hThread = CreateThread(nullptr, 0, BNET_GetServersListThread, &gtBnServerListThreadParams, 0, &dwThreadId);
	while (!gbBnStopConnection && WaitForSingleObject(hThread, 0) != WAIT_OBJECT_0)
	{
		Sleep(10);
	}
}

//Bnclient.0x6FF018B0
BNGatewayAccess* __stdcall BNET_GetBnGatewayAccess()
{
	gtBnGatewayAccess.Load();
	return &gtBnGatewayAccess;
}

//Bnclient.0x6FF018C0
void __fastcall BNET_GetGatewayHost(char* szHost, int nSize)
{
	*szHost = '\0';

	gtBnGatewayAccess.Load();
	SStrCopy(szHost, gtBnGatewayAccess.DNS(gtBnGatewayAccess.m_nCurrentGateway), nSize);

	char szOverride[256];
	if (SRegLoadString("Diablo II", "BNETIP", 0, szOverride, sizeof(szOverride)))
	{
		SStrCopy(szHost, szOverride, nSize);
	}
}

//Bnclient.0x6FF01930
static DWORD __stdcall BattleConnectFastest(void* pParam)
{
	BNET_DebugTrace("BattleConnectFastest()");

	if (InterlockedIncrement(&gnBnConnectThreads) > 1)
	{
		InterlockedDecrement(&gnBnConnectThreads);
		return FALSE;
	}

	BNDOWNLOAD_SetStatus(BNDOWNLOADSTATUS_IDLE);
	BNET_GetGatewayHost(gszBnGatewayHost, sizeof(gszBnGatewayHost));

	BNET_DebugTrace("   connect to: %s", gszBnGatewayHost);
	BNLOG_Command(BNLOG_COMMAND_INDENT, 4);
	BNLOG_Printf("querying gateway %s", gszBnGatewayHost);

	gszBnServerList[0] = '\0';
	if (FOG_SOCKET_WSAStartup())
	{
		BNET_GetServersList(gszBnServerList, gszBnGatewayHost);
	}

	if (!gszBnServerList[0])
	{
		InterlockedDecrement(&gnBnConnectThreads);
		BNMESSQUEUE_SetError(12);
		BNET_DebugTrace("   failed to get server list");
		BNLOG_Command(BNLOG_COMMAND_INDENT, -4);
		return FALSE;
	}

	BNMESSQUEUE_SetError(0);
	sFastestConnect(gszBnServerList);
	BNLOG_Command(BNLOG_COMMAND_INDENT, -4);

	if (!gpBnSafeSock && !gbBnStopConnection)
	{
		BNMESSQUEUE_SetError(12);
	}

	InterlockedDecrement(&gnBnConnectThreads);
	return TRUE;
}

// Stops all the pending connections and waits for the threads to exit, inlined in the original code
static BOOL BNET_StopConnection()
{
	BNSEND_FreeChannelList();
	BNSEND_FreeGameList();
	BNCACHE_Close();
	BNMESSQUEUE_Clear();
	BNSRP_Reset();

	gbBnStopConnection = TRUE;
	while (gnBnRecvThreads)
	{
		Sleep(10);
	}

	if (gpBnSafeSock)
	{
		BNRECV_SetDisconnected();
		while (gnBnConnectThreads)
		{
			Sleep(10);
		}

		if (gpBnSafeSock)
		{
			FOG_SOCKET_Destroy(gpBnSafeSock);
			gpBnSafeSock = nullptr;
		}
	}

	BNDOWNLOAD_CancelAll();
	while (BNDOWNLOAD_IsActive())
	{
		Sleep(10);
	}

	for (int nWaitTime = 0; gnBnConnectThreads; )
	{
		Sleep(10);
		nWaitTime += 100;
		if (nWaitTime > 60)
		{
			return FALSE;
		}
	}

	return TRUE;
}

//Bnclient.0x6FF01B20
HANDLE __stdcall BNET_OpenBNetConnection()
{
	BNLOG_Printf("Connecting to Battle.net...");

	if (gpBnSafeSock)
	{
		BNET_DebugTrace("   already connected");
		return nullptr;
	}

	if (!BNET_StopConnection())
	{
		return nullptr;
	}

	gbBnStopConnection = FALSE;
	gnBnConnectionState = BNCONNECTIONSTATE_IDLE;
	Sleep(10);

	BNCACHE_Open();
	BNRECV_ResetAllMessages();
	BNSRP_Initialize();
	gbBnEmailRequested = FALSE;

	DWORD dwThreadId;
	return CreateThread(nullptr, 0, BattleConnectFastest, nullptr, 0, &dwThreadId);
}

//Bnclient.0x6FF01C40
BOOL __fastcall BNET_GetConnectionState(int32_t* pState)
{
	D2_ASSERT(pState != NULL);

	*pState = gnBnConnectionState;
	return TRUE;
}

//Bnclient.0x6FF01C70
BOOL __fastcall BNET_Logon(const char* szAccountName, const char* szPassword)
{
	switch (BNSEND_GetLogonType())
	{
	case BNLOGONTYPE_OLS:
		BNRECV_ResetMessage(SID_LOGONRESPONSE2);
		BNSEND_LogonResponse2(szAccountName, szPassword);
		return TRUE;

	case BNLOGONTYPE_NLS:
		BNRECV_ResetMessage(SID_AUTH_ACCOUNTLOGONPROOF);
		return BNSRP_Logon(szAccountName, szPassword);

	default:
		return FALSE;
	}
}

//Bnclient.0x6FF01CC0
BOOL __stdcall BNET_GetLogonInfo()
{
	if (BNRECV_IsDisconnected())
	{
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;
	}

	switch (BNSEND_GetLogonType())
	{
	case BNLOGONTYPE_OLS:
		return BNRECV_WasMessageReceived(SID_LOGONRESPONSE2);

	case BNLOGONTYPE_NLS:
		return BNRECV_WasMessageReceived(SID_AUTH_ACCOUNTLOGONPROOF);

	default:
		return FALSE;
	}
}

//Bnclient.0x6FF01D00
BOOL __fastcall BNET_CreateAccount(const char* szAccountName, const char* szPassword)
{
	switch (BNSEND_GetLogonType())
	{
	case BNLOGONTYPE_OLS:
		BNRECV_ResetMessage(SID_CREATEACCOUNT2);
		BNSEND_CreateAccount2(szAccountName, szPassword);
		return TRUE;

	case BNLOGONTYPE_NLS:
		BNRECV_ResetMessage(SID_AUTH_ACCOUNTCREATE);
		return BNSRP_CreateAccount(szAccountName, szPassword);

	default:
		return FALSE;
	}
}

//Bnclient.0x6FF01D50
BOOL __fastcall BNET_GetCreateAccountResult(int32_t* pResult)
{
	*pResult = BNRECV_GetCreateAccountResult();

	switch (BNSEND_GetLogonType())
	{
	case BNLOGONTYPE_OLS:
		return BNRECV_WasMessageReceived(SID_CREATEACCOUNT2);

	case BNLOGONTYPE_NLS:
		return BNRECV_WasMessageReceived(SID_AUTH_ACCOUNTCREATE);

	default:
		return FALSE;
	}
}

//Bnclient.0x6FF01D80
BOOL __fastcall BNET_ChangePassword(const char* szAccountName, const char* szOldPassword, const char* szNewPassword)
{
	switch (BNSEND_GetLogonType())
	{
	case BNLOGONTYPE_OLS:
		BNRECV_ResetMessage(SID_CHANGEPASSWORD);
		BNSEND_ChangePassword(szAccountName, szOldPassword, szNewPassword);
		return TRUE;

	case BNLOGONTYPE_NLS:
		BNRECV_ResetMessage(SID_AUTH_ACCOUNTCHANGEPROOF);
		return BNSRP_ChangePassword(szAccountName, szOldPassword, szNewPassword);

	default:
		return FALSE;
	}
}

//Bnclient.0x6FF01DE0
BOOL __fastcall BNET_GetChangePasswordResult(int32_t* pResult)
{
	*pResult = BNRECV_GetChangePasswordResult();

	switch (BNSEND_GetLogonType())
	{
	case BNLOGONTYPE_OLS:
		return BNRECV_WasMessageReceived(SID_CHANGEPASSWORD);

	case BNLOGONTYPE_NLS:
		return BNRECV_WasMessageReceived(SID_AUTH_ACCOUNTCHANGEPROOF);

	default:
		return FALSE;
	}
}

//Bnclient.0x6FF01E10
BOOL __fastcall BNET_EnterChat(const char* szCharacterName, const char* szStatstring, const char* szAccountName, const char* szChannel, uint32_t nFlags)
{
	const BOOL bClassic = nFlags & 1;

	BNNEWS_SetProduct(bClassic);

	BNRECV_ResetMessage(SID_ENTERCHAT);
	BNSEND_EnterChat(szCharacterName, szStatstring, szAccountName);

	if (nFlags & 2)
	{
		BNSEND_JoinChannel(szChannel, TRUE, bClassic);
	}

	BNRECV_WaitForMessage(SID_ENTERCHAT);

	if (BNRECV_IsDisconnected())
	{
		BNMESSQUEUE_SetErrorIfNone(14);
		return TRUE;
	}

	BNMESSQUEUE_SetError(0);
	return TRUE;
}

//Bnclient.0x6FF01E90
BOOL __stdcall BNET_LeaveChat()
{
	BNSEND_LeaveChat();
	return TRUE;
}

//Bnclient.0x6FF01EA0
BOOL __stdcall BNET_CloseBNetConnection()
{
	return BNET_StopConnection();
}

//Bnclient.0x6FF01F70
int __fastcall BNET_SendPacket(uint8_t nMessageId, const void* pData, uint32_t nSize)
{
#pragma pack(push, 1)
	struct BnPacketHeader
	{
		uint8_t nMagic;
		uint8_t nMessageId;
		uint16_t nSize;
	};
#pragma pack(pop)

	BnPacketHeader tHeader;
	uint8_t aBuffer[0x2000];

	tHeader.nMagic = 0xFF;
	tHeader.nMessageId = nMessageId;
	tHeader.nSize = (uint16_t)(nSize + sizeof(tHeader));

	if (!gpBnSafeSock || gbBnStopConnection)
	{
		BNRECV_SetDisconnected();
		return 0;
	}

	if (!pData)
	{
		nSize = 0;
	}

	const uint32_t nPacketSize = nSize + sizeof(tHeader);
	SMemCopy(aBuffer, &tHeader, sizeof(tHeader));
	if (pData && nPacketSize < sizeof(aBuffer))
	{
		SMemCopy(&aBuffer[sizeof(tHeader)], pData, nSize);
	}

	return FOG_SOCKET_Send(gpBnSafeSock, (char*)aBuffer, nPacketSize);
}

//Bnclient.0x6FF02010
int __fastcall BNET_ProcessReceiveBuffer(uint8_t* pBuffer, int nSize)
{
	uint8_t* pPacket = pBuffer;
	while (true)
	{
		while (*pPacket != 0xFF && pPacket - pBuffer < nSize)
		{
			++pPacket;
		}

		const uint16_t nPacketSize = *(uint16_t*)&pPacket[2];
		const int nRemaining = pBuffer + nSize - pPacket;
		if ((uint32_t)nRemaining < 4 || nRemaining < nPacketSize)
		{
			break;
		}

		BNRECV_DispatchMessage(pPacket[1], &pPacket[4], nPacketSize - 4);
		pPacket += nPacketSize;
	}

	const int nRemaining = pBuffer + nSize - pPacket;
	for (int i = 0; i < nRemaining; ++i)
	{
		pBuffer[i] = pPacket[i];
	}

	return nRemaining;
}

//Bnclient.0x6FF02080
DWORD __stdcall BNET_ReceiveThread(void* pParam)
{
	uint8_t aBuffer[0x2000];
	BOOL bResult = TRUE;

	if (gnBnRecvThreads)
	{
		return TRUE;
	}

	InterlockedIncrement(&gnBnRecvThreads);

	while (!gbBnStopConnection && !gbBnServerConnected)
	{
		Sleep(10);
	}

	DWORD dwLastKeepAliveTick = GetTickCount();
	int nBufferedBytes = 0;
	while (gpBnSafeSock && !gbBnStopConnection && !gpBnSafeSock->bStopping)
	{
		const int nSelectResult = FOG_SOCKET_Select(gpBnSafeSock);
		if (!gpBnSafeSock || gbBnStopConnection || gpBnSafeSock->bStopping)
		{
			break;
		}

		if (nSelectResult)
		{
			const int nReceived = FOG_SOCKET_Receive(gpBnSafeSock, (char*)&aBuffer[nBufferedBytes], sizeof(aBuffer) - nBufferedBytes);
			if (nReceived <= 0)
			{
				BNRECV_SetDisconnected();
				bResult = FALSE;
				break;
			}

			nBufferedBytes = BNET_ProcessReceiveBuffer(aBuffer, nReceived + nBufferedBytes);
		}

		const DWORD dwTickCount = GetTickCount();
		if (dwTickCount - dwLastKeepAliveTick >= 180000)
		{
			BNET_SendPacket(SID_NULL, nullptr, 0);
			dwLastKeepAliveTick = dwTickCount;
		}
	}

	InterlockedDecrement(&gnBnRecvThreads);
	return bResult;
}

//Bnclient.0x6FF02200
BOOL __fastcall BNET_GetPeerName(sockaddr* pName, int* pNameLen)
{
	if (gpBnSafeSock)
	{
		return FOG_SOCKET_GetPeerName(gpBnSafeSock, pName, pNameLen);
	}

	return FALSE;
}

//Bnclient.0x6FF02220
BOOL __fastcall BNET_GetSockName(sockaddr* pName, int* pNameLen)
{
	if (gpBnSafeSock)
	{
		return FOG_SOCKET_GetSockName(gpBnSafeSock, pName, pNameLen);
	}

	return FALSE;
}

//Bnclient.0x6FF02240
int __stdcall BNET_GetVersion()
{
	return 10;
}

//Bnclient.0x6FF02250
uint8_t __stdcall BNET_GetBuild()
{
	return 39;
}

//Bnclient.0x6FF02260
BOOL __stdcall BNET_IsConnected()
{
	BnMessQueueErrorInfo tErrorInfo;
	BNMESSQUEUE_PeekLastError(&tErrorInfo);
	return !BNRECV_IsDisconnected() && !tErrorInfo.nError && gpBnSafeSock;
}

//Bnclient.0x6FF022A0
BOOL __stdcall BNET_IsEmailRequested()
{
	return gbBnEmailRequested;
}

//Bnclient.0x6FF022B0
void __fastcall BNET_SetEmailRequested(BOOL bRequested)
{
	gbBnEmailRequested = bRequested;
}

//Bnclient.0x6FF022C0
void __cdecl BNET_DebugTrace(const char* szFormat, ...)
{
}
