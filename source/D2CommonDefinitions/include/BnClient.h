#pragma once

#include <Windows.h>

#include <cstdint>

#pragma pack(push, 1)

struct S2C_Packet_SID_LOGONREALMEX
{
	uint32_t MCPCookie;
	uint32_t MCPStatus;
	uint32_t MCPChunk1[2];
	uint32_t MCPIP;
	uint32_t MCPPort;
	uint32_t MCPChunk2[12];
	char BattleNetUniqueName[];
};

struct RealmLogonInformation
{
	uint32_t nSize;
	S2C_Packet_SID_LOGONREALMEX tPacket;
};

struct BnMessQueueErrorInfo
{
	int32_t nError;						//0x00
	char* szErrorText;					//0x04
};

class BNGatewayAccess;

using BnNewsItemCallback = void(__fastcall*)(uint32_t nTimestamp, const char* szText);
using BnNewsDoneCallback = void(__cdecl*)();

// Returned by BnClient.dll's QueryInterface()
struct BnClientInterface
{
	void(__fastcall* SetUnused)(int32_t nValue);																					//0x00
	HANDLE(__stdcall* OpenBNetConnection)();																						//0x04
	BOOL(__fastcall* Logon)(const char* szAccountName, const char* szPassword);														//0x08
	BOOL(__stdcall* GetLogonInfo)();																								//0x0C
	BOOL(__stdcall* CloseBNetConnection)();																							//0x10
	BOOL(__fastcall* ChatCommand)(const char* szText);																				//0x14
	const char*(__stdcall* GetUniqueName)();																						//0x18
	BOOL(__fastcall* JoinChannel)(const char* szChannel, BOOL bForced, BOOL bClassic);												//0x1C
	void*(__fastcall* GetChannelList)(BOOL bClassic);																				//0x20
	uint32_t(__fastcall* BnMessQueue_Read)(int32_t* pType, void* pBuffer);															//0x24
	BOOL(__fastcall* BnMessQueue_GetLastError)(BnMessQueueErrorInfo* errInfo);														//0x28
	BOOL(__fastcall* RequestFileTime)(const char* szFileName, uint32_t nRequestId);													//0x2C
	BOOL(__stdcall* CheckAd)();																										//0x30
	BOOL(__fastcall* RefreshGame)(const char* szGameName, const char* szPassword, const char* szStatstring, uint32_t nGameType);		//0x34
	void*(__fastcall* GetGamesList)(const char* szGameName, const char* szPassword, uint32_t nUnused1, uint32_t nUnused2);			//0x38
	BOOL(__fastcall* NotifyJoinedGame)(const char* szGameName, const char* szPassword);												//0x3C
	void*(__stdcall* SendRealmList)();																								//0x40
	RealmLogonInformation*(__fastcall* LogonRealm)(const char* szRealmName, const char* szRealmPassword);							//0x44
	BOOL(__fastcall* RunUpgrade)(BOOL* pbQuit);																						//0x48
	int32_t(__stdcall* GetDownloadStatus)();																						//0x4C
	BOOL(__fastcall* StartPatch)(const char* szPatchFiles, uint32_t nSize);															//0x50
	BOOL(__fastcall* EnterChat)(const char* szCharacterName, const char* szStatstring, const char* szAccountName, const char* szChannel, uint32_t nFlags);	//0x54
	BOOL(__stdcall* LeaveChat)();																									//0x58
	int(__stdcall* GetVersion)();																									//0x5C
	BOOL(__fastcall* CreateAccount)(const char* szAccountName, const char* szPassword);												//0x60
	BOOL(__fastcall* GetCreateAccountResult)(int32_t* pResult);																		//0x64
	BOOL(__stdcall* IsConnected)();																									//0x68
	BOOL(__fastcall* OnAdClick)(uint32_t nAdId, BOOL bClicked);																		//0x6C
	void(__stdcall* CancelDownloads)();																								//0x70
	int(__fastcall* BattleWriteUserData)(const char* szAccountName, uint32_t nKeys, const char** pKeys, const char** pValues);		//0x74
	BOOL(__fastcall* BattleRequestReadUserData)(const char* szAccountName, uint32_t nKeys, uint32_t nRequestId, const char** pKeys);	//0x78
	BOOL(__fastcall* GetBattleReadUserData)(uint32_t nKeys, uint32_t nRequestId, char** pValues, const uint32_t* pValueSizes);		//0x7C
	BOOL(__fastcall* GetConnectionState)(int32_t* pState);																			//0x80
	void(__cdecl* LOG_Write)(const char* szFormat, ...);																			//0x84
	int(__cdecl* LOG_Command)(int nCommand, int nValue);																			//0x88
	BOOL(__fastcall* GetCreateGameResult)(int32_t* pResult);																		//0x8C
	BOOL(__stdcall* SendKeepAlivePacket)();																							//0x90
	BOOL(__stdcall* ValidateCDKeys)();																								//0x94
	BNGatewayAccess*(__stdcall* GetBnGatewayAccess)();																				//0x98
	BOOL(__fastcall* ChangePassword)(const char* szAccountName, const char* szOldPassword, const char* szNewPassword);				//0x9C
	BOOL(__fastcall* GetChangePasswordResult)(int32_t* pResult);																	//0xA0
	const char*(__fastcall* QueryAdUrl)(uint32_t nAdId);																			//0xA4
	BOOL(__fastcall* LoadBNetNews)(BnNewsItemCallback pfItemCallback, BnNewsDoneCallback pfDoneCallback);							//0xA8
	BOOL(__stdcall* FreeBNetNews)();																								//0xAC
	uint8_t(__stdcall* GetBuild)();																									//0xB0
	BOOL(__stdcall* IsEmailRequested)();																							//0xB4
	BOOL(__fastcall* SetEmail)(const char* szEmail);																				//0xB8
	BOOL(__fastcall* ResetPassword)(const char* szAccountName, const char* szEmail);												//0xBC
	BOOL(__fastcall* ChangeEmail)(const char* szAccountName, const char* szOldEmail, const char* szNewEmail);						//0xC0
	BOOL(__stdcall* LeaveGame)();																									//0xC4
};
#pragma pack(pop)
