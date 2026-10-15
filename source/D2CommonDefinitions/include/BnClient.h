#pragma once

#include <Windows.h>
#include <cstdint>

#pragma pack(push, 1)

struct D2ConfigStrc;

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
	uint32_t nSize;								// Equal to 8 if the logon failed
	S2C_Packet_SID_LOGONREALMEX tPacket;
};

enum BnClientPatchProgress
{
	BNPATCH_DONE = 101,
	BNPATCH_NOT_NEEDED = 102,
};

struct D2BnetErrorInfoStrc
{
	int32_t nError;								//0x00
	const char* szParam;						//0x04
};

// Gateways (realms) configured in the registry. Its member functions are exported by name by Bnclient.dll
struct BNGatewayAccess
{
	uint32_t unk0x00;							//0x00
	uint32_t unk0x04;							//0x04
	int32_t nGateways;							//0x08
	int32_t nCurrentGateway;					//0x0C 1-based index
};

struct BnClientInterface
{
	BOOL(__fastcall* Initialize)(D2ConfigStrc* pConfig);															//0x00
	HANDLE(__stdcall* OpenBNetConnection)();																		//0x04
	BOOL(__fastcall* Logon)(const char* szAccountName, const char* szPassword);										//0x08
	BOOL(__stdcall* IsLogonDone)();																					//0x0C
	BOOL(__stdcall* CloseBNetConnection)();																			//0x10
	BOOL(__thiscall* ChatCommand)(const char* _this);																//0x14
	void* (__stdcall* field_18)();																					//0x18
	int(__fastcall* JoinChannel)(BYTE* a1, int a2, int a3);															//0x1C
	int(__thiscall* GetChannelList)(void* _this);																	//0x20
	int(__fastcall* BnMessQueue_Read)(DWORD* a1, void* a2);															//0x24
	BOOL(__thiscall* GetLastError)(D2BnetErrorInfoStrc* pErrorInfo);												//0x28
	int(__fastcall* field_2C)(int a1, int a2);																		//0x2C
	int(__stdcall* CheckAd)();																						//0x30
	int(__fastcall* RefreshGame)(char *szGameName, char *szPassword, const char *szStatstring, int nGameType);		//0x34
	int(__fastcall* GetGamesList)(int a1, int a2, int a3, int a4);													//0x38
	int(__fastcall* NotifyJoinedGame)(int a1, int a2);																//0x3C
	void* (__fastcall* SendRealmList)(int32_t nUnused);																//0x40 Returns the realm list packet
	RealmLogonInformation* (__fastcall* LogonRealm)(const char *szRealmName, const char *szRealmPassword);			//0x44
	BOOL(__thiscall* ApplyPatch)(BOOL* pRestartNeeded);																//0x48
	int32_t(__stdcall* GetPatchProgress)();																			//0x4C See BnClientPatchProgress
	BOOL(__fastcall* DownloadFile)(const char* szFileName, size_t nFileNameLength);									//0x50
	int(__fastcall* EnterChat)(int ecx0, int a2, int a3, BYTE* a1, char a5);										//0x54
	int(__stdcall* LeaveChat)();																					//0x58
	int32_t(__stdcall* GetVersion)();																				//0x5C
	BOOL(__fastcall* CreateAccount)(const char* szAccountName, const char* szPassword);								//0x60
	BOOL(__thiscall* GetCreateAccountResult)(int32_t* pResult);														//0x64
	BOOL(__stdcall* IsConnected)();																					//0x68
	int(__fastcall* OnAdClick)(int a1, int a2);																		//0x6C
	void(__stdcall* CancelPatch)();																					//0x70
	int(__fastcall* BattleWriteUserData)(int a1, unsigned int a2, int a3, int a4);									//0x74
	BOOL(__fastcall* BattleRequestReadUserData)(int a1, unsigned int a2, int a3, int a4);							//0x78
	int(__fastcall* GetBattleReadUserData)(int a1, int a2, int a3, int a4);											//0x7C
	BOOL(__thiscall* GetConnectionState)(int32_t* pState);															//0x80
	void (*LOG_Write)(char* Format, ...);																			//0x84
	int(__cdecl* StartLogging)(int a1, int a2);																		//0x88
	int(__thiscall* GetCreateGameResult)(int* _this);																//0x8C
	int(__stdcall* SendKeepAlivePacket)();																			//0x90
	int(__stdcall* field_94)();																						//0x94
	BNGatewayAccess* (__stdcall* GetBnGatewayAccess)();																//0x98
	BOOL(__fastcall* ChangePassword)(const char* szAccountName, const char* szOldPassword, const char* szNewPassword);	//0x9C
	BOOL(__thiscall* GetChangePasswordResult)(int32_t* pResult);													//0xA0
	int(__thiscall* QueryAdUrl)(void* _this);																		//0xA4
	int(__fastcall* LoadBNetNews)(int(__fastcall* a1)(DWORD, DWORD), int (*a2)(void));								//0xA8
	int(__stdcall* FreeBNetNews)();																					//0xAC
	char(__stdcall* GetBuild)();																					//0xB0
	BOOL(__stdcall* IsEmailRegistrationRequired)();																	//0xB4
	BOOL(__thiscall* SetEmail)(const char* szEmail);																//0xB8
	BOOL(__fastcall* ResetPassword)(const char* szAccountName, const char* szEmailAddress);							//0xBC
	BOOL(__fastcall* ChangeEmail)(const char* szAccountName, const char* szOldEmailAddress, const char* szNewEmailAddress);	//0xC0
	int(__stdcall* LeaveGame)();																					//0xC4
};
#pragma pack(pop)
