#pragma once

#include <Windows.h>

#include <cstdint>

#include <BnClient.h>

enum BnLogonType
{
	BNLOGONTYPE_OLS = 0,	// Old logon system (broken SHA-1)
	BNLOGONTYPE_NLS = 1,	// New logon system (SRP)
};

#pragma pack(push, 1)
// CD key block of SID_AUTH_CHECK
struct BnCDKeyInfo
{
	uint32_t nKeyLength;				//0x00
	uint32_t nProductValue;				//0x04
	uint32_t nPublicValue;				//0x08
	uint32_t nUnknown;					//0x0C
	uint8_t pHash[20];					//0x10
};

#pragma pack(pop)

extern uint32_t gnBnClientToken;
extern uint32_t gnBnLastAdId;

BOOL __fastcall BNCDKEY_Decode(const char* szCDKey, uint32_t* pProductValue, uint32_t* pPublicValue, uint32_t* pPrivateValue);
BOOL __stdcall BNCDKEY_Validate();
BOOL __fastcall BNCDKEY_ComputeKeyInfo(BnCDKeyInfo* pKeyInfo, uint32_t nClientToken, int nKeyIndex);

void __fastcall BNSEND_SetServerToken(uint32_t nServerToken);
uint32_t __stdcall BNSEND_GetServerToken();
void __fastcall BNSEND_SetLogonType(uint32_t nLogonType);
uint32_t __stdcall BNSEND_GetLogonType();
BOOL __fastcall BNSEND_LogonResponse2(const char* szAccountName, const char* szPassword);
BOOL __fastcall BNSEND_CreateAccount2(const char* szAccountName, const char* szPassword);
BOOL __fastcall BNSEND_ChangePassword(const char* szAccountName, const char* szOldPassword, const char* szNewPassword);
void __fastcall BNSEND_StoreRealmList(const uint8_t* pData, uint32_t nSize);
void __fastcall BNSEND_StoreAdUrl(const uint8_t* pData, uint32_t nSize);
const char* __fastcall BNSEND_QueryAdUrl(uint32_t nAdId);
void* __stdcall BNSEND_QueryRealms();
void __fastcall BNSEND_StoreChannelList(const uint8_t* pData, uint32_t nSize);
void __stdcall BNSEND_FreeChannelList();
void* __fastcall BNSEND_GetChannelList(BOOL bClassic);
BOOL __fastcall BNSEND_JoinChannel(const char* szChannel, BOOL bForced, BOOL bClassic);
BOOL __fastcall BNSEND_EnterChat(const char* szCharacterName, const char* szStatstring, const char* szUnused);
BOOL __stdcall BNSEND_LeaveChat();
BOOL __fastcall BNSEND_ChatCommand(const char* szText);
BOOL __stdcall BNSEND_CheckAd();
BOOL __fastcall BNSEND_DisplayAd(const char* szFileName, const char* szLinkUrl);
BOOL __fastcall BNSEND_StartAdvEx3(const char* szGameName, const char* szPassword, const char* szStatstring, uint32_t nGameType);
BOOL __stdcall BNSEND_StopAdv();
BOOL __stdcall BNSEND_LeaveGame();
BOOL __fastcall BNSEND_GetCreateGameResult(int32_t* pResult);
void __fastcall BNSEND_StoreGameList(const uint8_t* pData, uint32_t nSize);
void __stdcall BNSEND_FreeGameList();
void* __fastcall BNSEND_GetGameList(const char* szGameName, const char* szPassword, uint32_t nUnused1, uint32_t nUnused2);
BOOL __fastcall BNSEND_NotifyJoin(const char* szGameName, const char* szPassword);
void __fastcall BNSEND_StoreRealmLogonInformation(const uint8_t* pData, uint32_t nSize);
RealmLogonInformation* __fastcall BNSEND_LogonRealm(const char* szRealmName, const char* szPassword);
BOOL __fastcall BNSEND_ClickAd(uint32_t nAdId, BOOL bClicked);
int __fastcall BNSEND_WriteUserData(const char* szAccountName, uint32_t nKeys, const char** pKeys, const char** pValues);
void __fastcall BNSEND_StoreUserData(const uint8_t* pData, uint32_t nSize);
BOOL __fastcall BNSEND_RequestUserData(const char* szAccountName, uint32_t nKeys, uint32_t nRequestId, const char** pKeys);
BOOL __fastcall BNSEND_GetUserData(uint32_t nKeys, uint32_t nRequestId, char** pValues, const uint32_t* pValueSizes);
BOOL __fastcall BNSEND_SetEmail(const char* szEmail);
BOOL __fastcall BNSEND_ResetPassword(const char* szAccountName, const char* szEmail);
BOOL __fastcall BNSEND_ChangeEmail(const char* szAccountName, const char* szOldEmail, const char* szNewEmail);
void __stdcall BNSEND_SystemInfo();
BOOL __stdcall BNSEND_AuthInfo();
BOOL __stdcall BNSEND_AuthCheck();
