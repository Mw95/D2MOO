#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Config.h>
#include <BnClient.h>

struct SMSGHANDLER_PARAMS;

extern HMODULE ghBnClient;
extern BnClientInterface* gptComInt;
extern char gszEmptyString[];

// Wrappers around the member functions of BNGatewayAccess exported by Bnclient.dll
void __fastcall BNGATEWAY_SaveAndUnload(BNGatewayAccess* pGatewayAccess);
const char* __fastcall BNGATEWAY_GetRealm(BNGatewayAccess* pGatewayAccess, int32_t nGateway);
const char* __fastcall BNGATEWAY_GetName(BNGatewayAccess* pGatewayAccess, int32_t nGateway);
void __fastcall BNGATEWAY_SetCurGateway(BNGatewayAccess* pGatewayAccess, int32_t nGateway);

//D2Launch.0x6FA11000
BOOL __fastcall BNET_LoadBnClient(D2ConfigStrc* ptParams);
//D2Launch.0x6FA110E0
void __fastcall BNET_CancelConnection();
//D2Launch.0x6FA110F0
void __fastcall BNET_ResetConnectionCancelled();
//D2Launch.0x6FA11100
BOOL __fastcall BNET_IsConnectionCancelled();
//D2Launch.0x6FA11110
BOOL __fastcall BNET_IsLoggedIn();
//D2Launch.0x6FA11120
void __stdcall BNET_WaitForPatchCallback(DWORD dwUnused);
//D2Launch.0x6FA11150
void __stdcall BNET_WaitForLogonCallback(DWORD dwUnused);
//D2Launch.0x6FA11190
void __stdcall BNET_WaitForCreateAccountCallback(DWORD dwUnused);
//D2Launch.0x6FA111E0
void __stdcall BNET_WaitForChangePasswordCallback(DWORD dwUnused);
//D2Launch.0x6FA11230
BOOL __fastcall BNET_Connect();
//D2Launch.0x6FA11460
BOOL __fastcall BNET_Logon(D2ConfigStrc* ptParams, BOOL bCreateAccount, BOOL bChangePassword);
//D2Launch.0x6FA11790
BOOL __fastcall BNET_ShowError(D2BnetErrorInfoStrc* errInfo);
//D2Launch.0x6FA11CF0
void __fastcall BNET_Disconnect();
//D2Launch.0x6FA11D60
void __stdcall BNET_WaitForConnectionCallback(DWORD dwUnused);
//D2Launch.0x6FA11DC0
void __fastcall BNET_CreateConnectingPopup();
//D2Launch.0x6FA11E90
void __fastcall BNET_UpdateConnectingPopup();
//D2Launch.0x6FA11FD0
int32_t __stdcall BNET_RegisterEmailOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12100
int32_t __stdcall BNET_RegisterEmailLaterCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12140
int32_t __stdcall BNET_RegisterEmailLaterConfirmCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12160
int32_t __stdcall BNET_RegisterEmailCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12180
void __fastcall BNET_CreateRegisterEmailMenu();
//D2Launch.0x6FA12300
void __stdcall BNET_RegisterEmailEditBoxCallback(int32_t nUnused);
//D2Launch.0x6FA12360
void __stdcall BNET_IdleCallback(DWORD dwUnused);
//D2Launch.0x6FA12370
BOOL __fastcall BNET_IsRegisterEmailCancelled();
//D2Launch.0x6FA12380
void __fastcall BNET_CreateResetPasswordMenu();
//D2Launch.0x6FA125B0
void __stdcall BNET_ResetPasswordEditBoxCallback(int32_t nUnused);
//D2Launch.0x6FA12660
int32_t __stdcall BNET_ResetPasswordOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12760
int32_t __stdcall BNET_ResetPasswordDoneCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12770
int32_t __stdcall BNET_BackToAccountOptionsCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12780
void __fastcall BNET_CreateAccountOptionsMenu();
//D2Launch.0x6FA12870
int32_t __stdcall BNET_ChangePasswordCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12880
int32_t __stdcall BNET_ResetPasswordCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA12890
int32_t __stdcall BNET_ChangeEmailCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA128A0
int32_t __stdcall BNET_AccountOptionsBackCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA128B0
void __fastcall BNET_CreateChangeEmailMenu();
//D2Launch.0x6FA12C60
void __stdcall BNET_ChangeEmailEditBoxCallback(int32_t nUnused);
//D2Launch.0x6FA12DF0
int32_t __stdcall BNET_ChangeEmailOkCallback(SMSGHANDLER_PARAMS* pMsg);
