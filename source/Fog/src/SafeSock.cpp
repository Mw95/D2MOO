#include "Safesock.h"
#include <Fog.h>
#include <Storm.h>

#include <stdio.h>

#define SAFESOCK_DEFAULT_NAME "UNKNOWN"

enum FSafeSockErrors : DWORD
{
	SAFESOCK_ERROR_NONE = 0,
	SAFESOCK_ERROR_WSASTARTUP = 1,
	SAFESOCK_ERROR_SOCKET = 2,
	SAFESOCK_ERROR_CONNECT = 3,
	SAFESOCK_ERROR_COMMUNICATION = 4,
	SAFESOCK_ERROR_CLOSESOCKET = 5,
};

// Fog.0x6FFA15F0
static char gszHostIPAddress[256];
// Fog.0x6FFA16F0
static char gszInetNtoaBuffer[32];

static void SAFESOCK_SetError(FSafeSock* pSafeSock, DWORD nFogErrorCode)
{
	pSafeSock->nWSALastError = WSAGetLastError();
	pSafeSock->nFogErrorCode = nFogErrorCode;
}

// 1.10f: 0x6FF63280 (#10000)
int __fastcall FOG_SOCKET_CloseSocket(SOCKET nSocket)
{
	return closesocket(nSocket);
}

// 1.10f: 0x6FF63290 (#10001)
BOOL __fastcall FOG_SOCKET_WSAStartup()
{
	WSADATA tWSAData;
	return WSAStartup(MAKEWORD(1, 1), &tWSAData) == 0;
}

// 1.10f: 0x6FF632C0 (#10002)
int __fastcall FOG_SOCKET_WSACleanup()
{
	return WSACleanup();
}

// 1.10f: 0x6FF632D0 (#10003)
FSafeSock* __fastcall FOG_SOCKET_Connect(char* szHostAddress, uint16_t nPortNumber, LPTHREAD_START_ROUTINE pThreadProc, LPVOID lpParameter, const char* szName)
{
	return FOG_SOCKET_ConnectEx(szHostAddress, nPortNumber, pThreadProc, lpParameter, szName, FALSE);
}

// 1.10f: 0x6FF632F0 (#10004)
// Connects a TCP socket to the given IPv4 address, and starts a thread with pThreadProc if not null.
FSafeSock* __fastcall FOG_SOCKET_ConnectEx(char* szHostAddress, uint16_t nPortNumber, LPTHREAD_START_ROUTINE pThreadProc, LPVOID lpParameter, const char* szName, BOOL bNonBlocking)
{
	FSafeSock* pSafeSock = (FSafeSock*)FOG_Alloc(sizeof(FSafeSock), __FILE__, __LINE__, 0);
	memset(pSafeSock, 0, sizeof(FSafeSock));
	SStrCopy(pSafeSock->szName, szName ? szName : SAFESOCK_DEFAULT_NAME, sizeof(pSafeSock->szName));
	InitializeCriticalSection(&pSafeSock->tCriticalSection);

	WSADATA tWSAData;
	if (const int nWSAStartupError = WSAStartup(MAKEWORD(1, 1), &tWSAData))
	{
		pSafeSock->nWSALastError = nWSAStartupError;
		pSafeSock->nFogErrorCode = SAFESOCK_ERROR_WSASTARTUP;
		DeleteCriticalSection(&pSafeSock->tCriticalSection);
		FOG_Free(pSafeSock, __FILE__, __LINE__, 0);
		return nullptr;
	}

	const SOCKET nSocket = socket(AF_INET, SOCK_STREAM, 0);
	pSafeSock->nSocket = nSocket;
	if (nSocket == INVALID_SOCKET)
	{
		SAFESOCK_SetError(pSafeSock, SAFESOCK_ERROR_SOCKET);
		DeleteCriticalSection(&pSafeSock->tCriticalSection);
		FOG_Free(pSafeSock, __FILE__, __LINE__, 0);
		return nullptr;
	}

	BOOL bNoDelay = TRUE;
	setsockopt(nSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&bNoDelay, sizeof(bNoDelay));
	BOOL bKeepAlive = TRUE;
	setsockopt(nSocket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&bKeepAlive, sizeof(bKeepAlive));
	DWORD dwSendTimeout = 3000;
	setsockopt(nSocket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&dwSendTimeout, sizeof(dwSendTimeout));

	bNonBlocking &= 1;
	if (bNonBlocking)
	{
		u_long nNonBlockingMode = 1;
		ioctlsocket(nSocket, FIONBIO, &nNonBlockingMode);
	}

	pSafeSock->bConnecting = TRUE;

	sockaddr_in tHostAddress{};
	tHostAddress.sin_family = AF_INET;
	tHostAddress.sin_port = htons(nPortNumber);
	tHostAddress.sin_addr.s_addr = inet_addr(szHostAddress);
	if (connect(nSocket, (const sockaddr*)&tHostAddress, sizeof(tHostAddress)) == SOCKET_ERROR)
	{
		const int nWSAError = WSAGetLastError();
		if (!bNonBlocking || nWSAError != WSAEWOULDBLOCK)
		{
			pSafeSock->nWSALastError = nWSAError;
			pSafeSock->nFogErrorCode = SAFESOCK_ERROR_CONNECT;
			DeleteCriticalSection(&pSafeSock->tCriticalSection);
			FOG_Free(pSafeSock, __FILE__, __LINE__, 0);
			return nullptr;
		}
	}

	if (!bNonBlocking)
	{
		pSafeSock->bConnected = TRUE;
		pSafeSock->bConnecting = FALSE;
	}

	// Cache our own IP address as seen by the socket
	if (!gszHostIPAddress[0] || inet_addr(gszHostIPAddress) == 0)
	{
		sockaddr_in tLocalAddress;
		int nLocalAddressSize = sizeof(tLocalAddress);
		if (getsockname(nSocket, (sockaddr*)&tLocalAddress, &nLocalAddressSize) != SOCKET_ERROR)
		{
			strcpy(gszHostIPAddress, inet_ntoa(tLocalAddress.sin_addr));
		}
	}

	if (pThreadProc)
	{
		pSafeSock->hThread = CreateThread(nullptr, 0, pThreadProc, lpParameter, 0, &pSafeSock->nThreadId);
	}

	return pSafeSock;
}

// 1.10f: 0x6FF63590 (#10005)
void __fastcall FOG_SOCKET_Destroy(FSafeSock* pSafeSock)
{
	D2_LOCK(&pSafeSock->tCriticalSection);
	pSafeSock->bStopping = TRUE;
	D2_UNLOCK(&pSafeSock->tCriticalSection);

	if (pSafeSock->hThread)
	{
		WaitForSingleObject(pSafeSock->hThread, 5000);
	}

	// Note: the critical section is never released, it is destroyed right after
	D2_LOCK(&pSafeSock->tCriticalSection);
	if (pSafeSock->hThread)
	{
		CloseHandle(pSafeSock->hThread);
		pSafeSock->hThread = nullptr;
	}

	const SOCKET nSocket = pSafeSock->nSocket;
	pSafeSock->nSocket = 0;
	pSafeSock->bConnected = FALSE;
	if (closesocket(nSocket) == SOCKET_ERROR)
	{
		SAFESOCK_SetError(pSafeSock, SAFESOCK_ERROR_CLOSESOCKET);
	}

	DeleteCriticalSection(&pSafeSock->tCriticalSection);
	FOG_Free(pSafeSock, __FILE__, __LINE__, 0);
}

// 1.10f: 0x6FF63630 (#10006)
int __fastcall FOG_SOCKET_Receive(FSafeSock* pSafeSock, char* pBuffer, int nBufferLength)
{
	if (!pSafeSock || pSafeSock->bStopping)
	{
		return 0;
	}

	D2_LOCK(&pSafeSock->tCriticalSection);
	const int nReceivedBytes = recv(pSafeSock->nSocket, pBuffer, nBufferLength, 0);
	D2_UNLOCK(&pSafeSock->tCriticalSection);

	if (nReceivedBytes <= 0)
	{
		SAFESOCK_SetError(pSafeSock, SAFESOCK_ERROR_COMMUNICATION);
	}
	return nReceivedBytes;
}

// 1.10f: 0x6FF63690 (#10007)
// Returns the number of bytes sent, or 0 if the whole buffer could not be sent.
int __fastcall FOG_SOCKET_Send(FSafeSock* pSafeSock, char* pBuffer, int nBufferLength)
{
	if (!pSafeSock || pSafeSock->bStopping)
	{
		return 0;
	}

	D2_LOCK(&pSafeSock->tCriticalSection);
	int nSentBytes = send(pSafeSock->nSocket, pBuffer, nBufferLength, 0);
	if (nSentBytes != nBufferLength)
	{
		SAFESOCK_SetError(pSafeSock, SAFESOCK_ERROR_COMMUNICATION);
		nSentBytes = 0;
	}
	D2_UNLOCK(&pSafeSock->tCriticalSection);
	return nSentBytes;
}

// 1.10f: 0x6FF63770 (#10008)
// Waits up to 100ms for data to read. Returns TRUE if there is data to read or an error occurred.
int __fastcall FOG_SOCKET_Select(FSafeSock* pSafeSock)
{
	if (!pSafeSock || pSafeSock->bStopping || !pSafeSock->bConnected)
	{
		return FALSE;
	}

	fd_set tReadFds;
	tReadFds.fd_count = 1;
	tReadFds.fd_array[0] = pSafeSock->nSocket;
	fd_set tExceptFds;
	tExceptFds.fd_count = 1;
	tExceptFds.fd_array[0] = pSafeSock->nSocket;
	timeval tTimeout;
	tTimeout.tv_sec = 0;
	tTimeout.tv_usec = 100000;

	const int nResult = select(0, &tReadFds, nullptr, &tExceptFds, &tTimeout);
	if (pSafeSock->bStopping || !pSafeSock->bConnected || nResult == 0)
	{
		return FALSE;
	}

	if (nResult == SOCKET_ERROR)
	{
		SAFESOCK_SetError(pSafeSock, SAFESOCK_ERROR_COMMUNICATION);
		return TRUE;
	}

	if (FD_ISSET(pSafeSock->nSocket, &tExceptFds))
	{
		return FALSE;
	}

	return FD_ISSET(pSafeSock->nSocket, &tReadFds) ? TRUE : FALSE;
}

// 1.10f: 0x6FF63700 (#10009)
// Must be called between FOG_SOCKET_Lock and FOG_SOCKET_Unlock.
int __fastcall FOG_SOCKET_SendNoLock(FSafeSock* pSafeSock, char* pBuffer, int nBufferLength)
{
	int nSentBytes = send(pSafeSock->nSocket, pBuffer, nBufferLength, 0);
	if (WSAGetLastError() == WSAETIMEDOUT)
	{
		nSentBytes = 0;
		FOG_Trace("ERROR: Disconnecting socket due to WSAETIMEDOUT\n");
		closesocket(pSafeSock->nSocket);
	}
	return nSentBytes;
}

// 1.10f: 0x6FF63750 (#10010)
void __fastcall FOG_SOCKET_Lock(FSafeSock* pSafeSock)
{
	FOG_10050_EnterCriticalSection(&pSafeSock->tCriticalSection, __LINE__);
}

// 1.10f: 0x6FF63760 (#10011)
void __fastcall FOG_SOCKET_Unlock(FSafeSock* pSafeSock)
{
	LeaveCriticalSection(&pSafeSock->tCriticalSection);
}

// 1.10f: 0x6FF63860 (#10012)
BOOL __fastcall FOG_SOCKET_GetPeerName(FSafeSock* pSafeSock, struct sockaddr* name, int* namelen)
{
	D2_LOCK(&pSafeSock->tCriticalSection);
	const int nResult = getpeername(pSafeSock->nSocket, name, namelen);
	D2_UNLOCK(&pSafeSock->tCriticalSection);
	return nResult != SOCKET_ERROR;
}

// 1.10f: 0x6FF638A0 (#10262)
BOOL __fastcall FOG_SOCKET_GetSockName(FSafeSock* pSafeSock, struct sockaddr* name, int* namelen)
{
	D2_LOCK(&pSafeSock->tCriticalSection);
	const int nResult = getsockname(pSafeSock->nSocket, name, namelen);
	D2_UNLOCK(&pSafeSock->tCriticalSection);
	return nResult != SOCKET_ERROR;
}

// 1.10f: 0x6FF638E0 (#10013)
// Returns the IP address of this host. If it can not be resolved from the host name,
// uses the address of the network interface that would be used to reach the internet.
const char* __fastcall FOG_GetHostIPAddress()
{
	WSADATA tWSAData;
	WSAStartup(MAKEWORD(1, 1), &tWSAData);

	sockaddr_in tLocalAddress{};
	char szHostName[256];
	if (gethostname(szHostName, sizeof(szHostName)) != SOCKET_ERROR)
	{
		if (const hostent* pHostEntry = gethostbyname(szHostName))
		{
			tLocalAddress.sin_addr.s_addr = *(const u_long*)pHostEntry->h_addr_list[0];
		}
	}

	if (tLocalAddress.sin_addr.s_addr == 0)
	{
		const SOCKET nSocket = socket(AF_INET, SOCK_DGRAM, 0);
		if (nSocket != INVALID_SOCKET)
		{
			// No data is sent, connecting an UDP socket only selects the network interface to use
			sockaddr_in tRemoteAddress;
			tRemoteAddress.sin_family = AF_INET;
			tRemoteAddress.sin_port = htons(7);
			tRemoteAddress.sin_addr.s_addr = inet_addr("209.67.136.168");
			if (connect(nSocket, (const sockaddr*)&tRemoteAddress, sizeof(tRemoteAddress)) != SOCKET_ERROR)
			{
				int nLocalAddressSize = sizeof(tLocalAddress);
				getsockname(nSocket, (sockaddr*)&tLocalAddress, &nLocalAddressSize);
			}
			closesocket(nSocket);
		}
	}

	const uint8_t* pAddressBytes = (const uint8_t*)&tLocalAddress.sin_addr.s_addr;
	sprintf(gszHostIPAddress, "%d.%d.%d.%d", pAddressBytes[0], pAddressBytes[1], pAddressBytes[2], pAddressBytes[3]);
	WSACleanup();
	return gszHostIPAddress;
}

// 1.10f: 0x6FF63A00 (#10014)
const char* __fastcall FOG_inet_ntoa(ULONG inaddr_S_addr)
{
	in_addr tAddress;
	tAddress.s_addr = inaddr_S_addr;
	strcpy(gszInetNtoaBuffer, inet_ntoa(tAddress));
	return gszInetNtoaBuffer;
}

// 1.10f: 0x6FF63A40 (#10015)
// Returns szHostName if it is already an IPv4 address, or the resolved IPv4 address. Returns nullptr on failure.
const char* __fastcall FOG_ResolveHostIPAddress(const char* szHostName)
{
	int nAddressParts[4];
	if (sscanf(szHostName, "%d.%d.%d.%d", &nAddressParts[0], &nAddressParts[1], &nAddressParts[2], &nAddressParts[3]) == 4)
	{
		return szHostName;
	}

	BOOL bInitializedWinsock = FALSE;
	const hostent* pHostEntry = gethostbyname(szHostName);
	if (!pHostEntry || !pHostEntry->h_addr_list || !pHostEntry->h_addr_list[0])
	{
		if (WSAGetLastError() != WSANOTINITIALISED)
		{
			return nullptr;
		}

		WSADATA tWSAData;
		if (WSAStartup(MAKEWORD(1, 1), &tWSAData) != 0)
		{
			return nullptr;
		}

		pHostEntry = gethostbyname(szHostName);
		if (!pHostEntry || !pHostEntry->h_addr_list || !pHostEntry->h_addr_list[0])
		{
			WSACleanup();
			return nullptr;
		}
		bInitializedWinsock = TRUE;
	}

	strcpy(gszHostIPAddress, inet_ntoa(*(const in_addr*)pHostEntry->h_addr_list[0]));
	if (bInitializedWinsock)
	{
		WSACleanup();
	}
	return gszHostIPAddress;
}

// 1.10f: 0x6FF63A20 (#10016)
BOOL __fastcall FOG_SOCKET_GetError(FSafeSock* pSafeSock, DWORD* pFogError, int* pWSALastError)
{
	*pFogError = pSafeSock->nFogErrorCode;
	*pWSALastError = pSafeSock->nWSALastError;
	return TRUE;
}

// 1.10f: 0x6FF63B20 (#10017)
BOOL __fastcall FOG_SOCKET_SetBlockingMode(FSafeSock* pSafeSock, BOOL bNonBlocking)
{
	u_long nNonBlockingMode = bNonBlocking;
	ioctlsocket(pSafeSock->nSocket, FIONBIO, &nNonBlockingMode);
	return TRUE;
}
