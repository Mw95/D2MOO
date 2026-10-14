#pragma once

#include <Windows.h>

#include <cstdint>

struct FSafeSock;
struct sockaddr;

#pragma pack(push, 1)
struct BnServerListThreadParams
{
	char* szServerList;					//0x00
	const char* szGatewayHost;			//0x04
};

struct BnServerConnection
{
	char szHost[256];					//0x000
	FSafeSock* pSafeSock;				//0x100
	int32_t unk0x104;					//0x104
};
#pragma pack(pop)

enum BnConnectionState
{
	BNCONNECTIONSTATE_IDLE = 0,
	BNCONNECTIONSTATE_GETTING_SERVER_LIST = 1,
	BNCONNECTIONSTATE_SEARCHING_FASTEST_SERVER = 2,
	BNCONNECTIONSTATE_ACCESSING_ACCOUNTS = 3,
	BNCONNECTIONSTATE_CHECKING_VERSION = 4,
};

extern FSafeSock* gpBnSafeSock;
extern volatile LONG gnBnRecvThreads;
extern volatile LONG gnBnConnectThreads;
extern BOOL gbBnServerConnected;
extern BOOL gbBnStopConnection;
extern BOOL gbBnEmailRequested;
extern int32_t gnBnConnectionState;

BOOL __fastcall BNET_SetUniqueName(const char* szUniqueName);
const char* __stdcall BNET_GetUniqueName();
BOOL __fastcall BNET_HandleChatEvent(const uint8_t* pData, uint32_t nSize);
BOOL __cdecl BNET_IsExpansion();
DWORD __stdcall BNET_GetServersListThread(void* pParam);
void __fastcall BNET_GetServersList(char* szServerList, const char* szGatewayHost);
class BNGatewayAccess* __stdcall BNET_GetBnGatewayAccess();
void __fastcall BNET_GetGatewayHost(char* szHost, int nSize);
HANDLE __stdcall BNET_OpenBNetConnection();
BOOL __fastcall BNET_GetConnectionState(int32_t* pState);
BOOL __fastcall BNET_Logon(const char* szAccountName, const char* szPassword);
BOOL __stdcall BNET_GetLogonInfo();
BOOL __fastcall BNET_CreateAccount(const char* szAccountName, const char* szPassword);
BOOL __fastcall BNET_GetCreateAccountResult(int32_t* pResult);
BOOL __fastcall BNET_ChangePassword(const char* szAccountName, const char* szOldPassword, const char* szNewPassword);
BOOL __fastcall BNET_GetChangePasswordResult(int32_t* pResult);
BOOL __fastcall BNET_EnterChat(const char* szCharacterName, const char* szStatstring, const char* szAccountName, const char* szChannel, uint32_t nFlags);
BOOL __stdcall BNET_LeaveChat();
BOOL __stdcall BNET_CloseBNetConnection();
int __fastcall BNET_SendPacket(uint8_t nMessageId, const void* pData, uint32_t nSize);
int __fastcall BNET_ProcessReceiveBuffer(uint8_t* pBuffer, int nSize);
DWORD __stdcall BNET_ReceiveThread(void* pParam);
BOOL __fastcall BNET_GetPeerName(sockaddr* pName, int* pNameLen);
BOOL __fastcall BNET_GetSockName(sockaddr* pName, int* pNameLen);
int __stdcall BNET_GetVersion();
uint8_t __stdcall BNET_GetBuild();
BOOL __stdcall BNET_IsConnected();
BOOL __stdcall BNET_IsEmailRequested();
void __fastcall BNET_SetEmailRequested(BOOL bRequested);
void __cdecl BNET_DebugTrace(const char* szFormat, ...);
