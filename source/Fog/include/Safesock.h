#pragma once

#pragma warning(push)
#pragma warning(disable:4820 4121)
#include <Winsock2.h>
#pragma warning(pop)

#include <D2BasicTypes.h>
#include <Fog.h>

#pragma pack(1)

struct FSafeSock
{
	BOOL bConnected;
	BOOL bConnecting;
	SOCKET nSocket;
	CRITICAL_SECTION tCriticalSection;
	HANDLE hThread;
	DWORD nThreadId;
	BOOL bStopping;
	DWORD nFogErrorCode;
	DWORD nWSALastError;
	char szName[64];
};

#pragma pack()

FOG_DLL_DECL int __fastcall FOG_SOCKET_CloseSocket(SOCKET); // 1.10f: 0x6FF63280 (#10000)
FOG_DLL_DECL BOOL __fastcall FOG_SOCKET_WSAStartup(); // 1.10f: 0x6FF63290 (#10001)
FOG_DLL_DECL int __fastcall FOG_SOCKET_WSACleanup(); // 1.10f: 0x6FF632C0 (#10002)
FOG_DLL_DECL FSafeSock* __fastcall FOG_SOCKET_Connect(char* szHostAddress, uint16_t nPortNumber, LPTHREAD_START_ROUTINE pThreadProc, LPVOID lpParameter, const char* szName); // 1.10f: 0x6FF632D0 (#10003)
FOG_DLL_DECL FSafeSock* __fastcall FOG_SOCKET_ConnectEx(char* szHostAddress, uint16_t nPortNumber, LPTHREAD_START_ROUTINE pThreadProc, LPVOID lpParameter, const char* szName, BOOL bNonBlocking); // 1.10f: 0x6FF632F0 (#10004)
FOG_DLL_DECL void __fastcall FOG_SOCKET_Destroy(FSafeSock* pSafeSock); // 1.10f: 0x6FF63590 (#10005)
FOG_DLL_DECL int __fastcall FOG_SOCKET_Receive(FSafeSock* pSafeSock, char* pBuffer, int nBufferLength); // 1.10f: 0x6FF63630 (#10006)
FOG_DLL_DECL int __fastcall FOG_SOCKET_Send(FSafeSock* pSafeSock, char* pBuffer, int nBufferLength); // 1.10f: 0x6FF63690 (#10007)
FOG_DLL_DECL int __fastcall FOG_SOCKET_Select(FSafeSock* pSafeSock); // 1.10f: 0x6FF63770 (#10008)
FOG_DLL_DECL int __fastcall FOG_SOCKET_SendNoLock(FSafeSock* pSafeSock, char* pBuffer, int nBufferLength); // 1.10f: 0x6FF63700 (#10009)
FOG_DLL_DECL void __fastcall FOG_SOCKET_Lock(FSafeSock* pSafeSock); // 1.10f: 0x6FF63750 (#10010)
FOG_DLL_DECL void __fastcall FOG_SOCKET_Unlock(FSafeSock* pSafeSock); // 1.10f: 0x6FF63760 (#10011)
FOG_DLL_DECL BOOL __fastcall FOG_SOCKET_GetPeerName(FSafeSock* pSafeSock, struct sockaddr* name, int* namelen); // 1.10f: 0x6FF63860 (#10012)
FOG_DLL_DECL const char* __fastcall FOG_GetHostIPAddress(); // 1.10f: 0x6FF638E0 (#10013)
FOG_DLL_DECL const char* __fastcall FOG_inet_ntoa(/*IN_ADDR, but cant due to callconv*/ULONG inaddr_S_addr); // 1.10f: 0x6FF63A00 (#10014)
FOG_DLL_DECL const char* __fastcall FOG_ResolveHostIPAddress(const char* szHostName); // 1.10f: 0x6FF63A40 (#10015)
FOG_DLL_DECL BOOL __fastcall FOG_SOCKET_GetError(FSafeSock* pSafeSock, DWORD* pFogError, int* pWSALastError); // 1.10f: 0x6FF63A20 (#10016)
FOG_DLL_DECL BOOL __fastcall FOG_SOCKET_GetSockName(FSafeSock* pSafeSock, struct sockaddr* name, int* namelen); // 1.10f: 0x6FF638A0 (#10262)
FOG_DLL_DECL BOOL __fastcall FOG_SOCKET_SetBlockingMode(FSafeSock* pSafeSock, BOOL bNonBlocking); // 1.10f: 0x6FF63B20 (#10017)
