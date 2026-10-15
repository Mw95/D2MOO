#pragma once
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

struct BnClientInterface
{
	int(__stdcall* field0x00)();
	HANDLE(__stdcall* OpenBNetConnection)();
	int(__fastcall* Logon)(int a1, int a2);
	int(__stdcall* GetLogonInfo)();
	int(__stdcall* CloseBNetConnection)();
	BOOL(__thiscall* ChatCommand)(const char* _this);
	void* (__stdcall* field_18)();
	int(__fastcall* JoinChannel)(BYTE* a1, int a2, int a3);
	const char*(__fastcall* GetChannelList)();									// Returns a list of null-terminated channel names, terminated by an empty string
	int(__fastcall* BnMessQueue_Read)(DWORD* a1, void* a2);
	int(__thiscall* BnMessageQueueGetLastError)(DWORD* errInfo);
	int(__fastcall* field_2C)(int a1, int a2);
	int(__stdcall* CheckAd)();
	int(__fastcall* RefreshGame)(char *szGameName, char *szPassword, const char *szStatstring, int nGameType);
	void*(__fastcall* GetGamesList)(const char* szGameName, const char* szGamePassword, uint32_t nFlags, uint32_t nFilter);
	int(__fastcall* NotifyJoinedGame)(const char* szGameName, const char* szGamePassword);
	int(__stdcall* SendRealmList)();
	struct RealmLogonInformation* (__fastcall* LogonRealm)(const char *szRealmName, const char *szRealmPassword);
	int(__thiscall* PatchUnk)(DWORD* _this);
	int(__stdcall* field_4C)();
	uintptr_t(__fastcall* PatchUnk0x4C)(BYTE* source, size_t size);
	int(__fastcall* EnterChat)(const char* szCharacterName, const char* szRealmAndCharacterName, int a3, const char* szChannelName, BOOL bExpansion);
	int(__stdcall* LeaveChat)();
	int(__stdcall* GetVersion)();
	int(__fastcall* CreateAccount)(int a1, int a2);
	int(__thiscall* GetCreateAccountResult)(DWORD* _this);
	int(__stdcall* field_68)();
	int(__fastcall* OnAdClick)(int a1, int a2);
	int(__stdcall* UnkSet)();
	int(__fastcall* BattleWriteUserData)(const char* szAccountName, uint32_t nKeys, const char** ppKeys, const char** ppValues);
	BOOL(__fastcall* BattleRequestReadUserData)(const char* szAccountName, uint32_t nKeys, uint32_t nAccounts, const char** ppKeys);
	int(__fastcall* GetBattleReadUserData)(uint32_t nKeys, uint32_t nAccounts, char** ppValues, uint32_t* pValueSizes);
	int(__thiscall* GetConnectionState)(DWORD* pState);
	void (*LOG_Write)(char* Format, ...);
	int(__cdecl* StartLogging)(int a1, int a2);
	int(__thiscall* GetCreateGameResult)(int* _this);
	int(__stdcall* SendKeepAlivePacket)();
	int(__stdcall* field_94)();
	struct BNGatewayAccess* (__stdcall* GetBnGatewayAccess)();
	int(__fastcall* ChangePassword)(int ecx0, int a2, int a1);
	int(__thiscall* GetChangePasswordResult)(int* _this);
	const char*(__fastcall* QueryAdUrl)(int nAdId);
	int(__fastcall* LoadBNetNews)(int(__fastcall* pfNewsCallback)(uint32_t nTimeStamp, const char* szNews), int(__fastcall* pfNewsDoneCallback)());
	int(__stdcall* FreeBNetNews)();
	char(__stdcall* GetBuild)();
	int(__stdcall* field_B4)();
	BOOL(__thiscall* SetEmail)(const void* szEmail);
	BOOL(__fastcall* ResetPassword)(BYTE* szAccountName, BYTE* szEmailAddress);
	BOOL(__fastcall* ChangeEmail)(BYTE* a1, BYTE* a2, BYTE* a3);
	int(__stdcall* LeaveGame)();
};
#pragma pack(pop)
