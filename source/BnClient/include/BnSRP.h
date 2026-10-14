#pragma once

#include <Windows.h>

#include <cstdint>

void __stdcall BNSRP_Initialize();
void __stdcall BNSRP_Reset();
BOOL __fastcall BNSRP_Logon(const char* szAccountName, const char* szPassword);
BOOL __stdcall BNSRP_SendLogon();
BOOL __fastcall BNSRP_HandleLogonChallenge(const uint8_t* pSalt, const uint8_t* pB);
BOOL __fastcall BNSRP_CreateAccount(const char* szAccountName, const char* szPassword);
BOOL __fastcall BNSRP_ChangePassword(const char* szAccountName, const char* szOldPassword, const char* szNewPassword);
BOOL __fastcall BNSRP_HandleChangeChallenge(const uint8_t* pSalt, const uint8_t* pB);
BOOL __fastcall BNSRP_RequestUpgrade(BOOL bLogon);
BOOL __fastcall BNSRP_SendUpgradeProof(uint32_t nServerToken);
BOOL __fastcall BNSRP_VerifyServerProof(const uint8_t* pM2);
BOOL __stdcall BNSRP_IsUpgradingLogon();
void __stdcall BNSRP_ClearPasswords();
