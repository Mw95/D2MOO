// Made up filename

#include "BnSRP.h"

#include <climits>
#include <cstddef>
#include <cstring>

#include <Storm.h>

#include "BnConnect.h"
#include "BnRecv.h"
#include "BnSend.h"
#include "Grid.h"
#include "SRP/SRP.h"


//Bnclient.0x6FF198D0
static const uint8_t gpBnSRPGenerator[] = { 0x2F };
//Bnclient.0x6FF198D4
static const uint32_t gnBnSRPGeneratorSize = sizeof(gpBnSRPGenerator);
//Bnclient.0x6FF198D8
static const uint8_t gpBnSRPModulus[] =
{
	0x87, 0xC7, 0x23, 0x85, 0x65, 0xF6, 0x16, 0x12, 0xD9, 0x12, 0x32, 0xC7, 0x78, 0x6C, 0x97, 0x7E,
	0x55, 0xB5, 0x92, 0xA0, 0x8C, 0xB6, 0x86, 0x21, 0x03, 0x18, 0x99, 0x61, 0x8B, 0x1A, 0xFF, 0xF8,
};
//Bnclient.0x6FF198F8
static const uint32_t gnBnSRPModulusSize = sizeof(gpBnSRPModulus);

SRP gtBnSRP;
char gszBnSRPAccountName[256];
BOOL gbBnSRPUpgradingLogon;
BnSRPSession gtBnSRPSession;
uint8_t gpBnSRPNewSalt[32];
uint8_t gpBnSRPNewVerifier[32];


//Bnclient.0x6FF08380
void __stdcall BNSRP_Initialize()
{
	gtBnSRP.Initialize(gnBnSRPGeneratorSize, gpBnSRPGenerator, gnBnSRPModulusSize, gpBnSRPModulus);
	gtBnSRP.SeedRandom(GetTickCount());
}

//Bnclient.0x6FF083C0
void __stdcall BNSRP_Reset()
{
	gtBnSRP.Destroy();
}

//Bnclient.0x6FF086C0
BOOL __fastcall BNSRP_Logon(const char* szAccountName, const char* szPassword)
{
#pragma pack(push, 1)
	struct
	{
		uint8_t A[32];
		char szAccountName[256];
	} tPacket;
#pragma pack(pop)

	gbBnSRPUpgradingLogon = FALSE;
	SStrCopy(gszBnSRPAccountName, szAccountName, sizeof(gszBnSRPAccountName));
	SMemZero(&gtBnSRPSession, sizeof(gtBnSRPSession));

	char szUserName[256];
	SStrCopy(szUserName, szAccountName, sizeof(szUserName));
	SStrUpper(szUserName);

	char szUpperPassword[256];
	SStrCopy(szUpperPassword, szPassword, sizeof(szUpperPassword));
	SStrUpper(szUpperPassword);

	gtBnSRP.StartLogon(&gtBnSRPSession, szUserName, szUpperPassword);

	SMemCopy(tPacket.A, gtBnSRPSession.A, sizeof(tPacket.A));
	const size_t nLength = SStrCopy(tPacket.szAccountName, szAccountName, sizeof(tPacket.szAccountName));
	BNET_SendPacket(SID_AUTH_ACCOUNTLOGON, &tPacket, offsetof(decltype(tPacket), szAccountName) + nLength + 1);
	return TRUE;
}

//Bnclient.0x6FF087A0
BOOL __stdcall BNSRP_SendLogon()
{
#pragma pack(push, 1)
	struct
	{
		uint8_t A[32];
		char szAccountName[256];
	} tPacket;
#pragma pack(pop)

	SMemCopy(tPacket.A, gtBnSRPSession.A, sizeof(tPacket.A));
	const size_t nLength = SStrCopy(tPacket.szAccountName, gszBnSRPAccountName, sizeof(tPacket.szAccountName));
	BNET_SendPacket(SID_AUTH_ACCOUNTLOGON, &tPacket, offsetof(decltype(tPacket), szAccountName) + nLength + 1);
	return TRUE;
}

//Bnclient.0x6FF087F0
BOOL __fastcall BNSRP_HandleLogonChallenge(const uint8_t* pSalt, const uint8_t* pB)
{
	const BOOL bResult = gtBnSRP.ProcessChallenge(&gtBnSRPSession, pSalt, pB);
	SMemZero(gtBnSRPSession.szPassword, sizeof(gtBnSRPSession.szPassword));
	if (!bResult)
	{
		return FALSE;
	}

	uint8_t M1[20];
	SMemCopy(M1, gtBnSRPSession.M1, sizeof(M1));
	BNET_SendPacket(SID_AUTH_ACCOUNTLOGONPROOF, M1, sizeof(M1));
	return TRUE;
}

//Bnclient.0x6FF08850
BOOL __fastcall BNSRP_CreateAccount(const char* szAccountName, const char* szPassword)
{
#pragma pack(push, 1)
	struct
	{
		uint8_t pSalt[32];
		uint8_t pVerifier[32];
		char szAccountName[256];
	} tPacket;
#pragma pack(pop)

	char szUserName[256];
	SStrCopy(szUserName, szAccountName, sizeof(szUserName));
	SStrUpper(szUserName);

	char szUpperPassword[256];
	SStrCopy(szUpperPassword, szPassword, sizeof(szUpperPassword));
	SStrUpper(szUpperPassword);

	gtBnSRP.CreateVerifier(szUserName, szUpperPassword, tPacket.pSalt, tPacket.pVerifier);

	const size_t nLength = SStrCopy(tPacket.szAccountName, szAccountName, INT_MAX);
	BNET_SendPacket(SID_AUTH_ACCOUNTCREATE, &tPacket, offsetof(decltype(tPacket), szAccountName) + nLength + 1);
	return TRUE;
}

//Bnclient.0x6FF088F0
BOOL __fastcall BNSRP_ChangePassword(const char* szAccountName, const char* szOldPassword, const char* szNewPassword)
{
#pragma pack(push, 1)
	struct
	{
		uint8_t A[32];
		char szAccountName[256];
	} tPacket;
#pragma pack(pop)

	gbBnSRPUpgradingLogon = FALSE;
	SMemZero(&gtBnSRPSession, sizeof(gtBnSRPSession));

	char szUserName[256];
	SStrCopy(szUserName, szAccountName, sizeof(szUserName));
	SStrUpper(szUserName);

	char szUpperOldPassword[256];
	SStrCopy(szUpperOldPassword, szOldPassword, sizeof(szUpperOldPassword));
	SStrUpper(szUpperOldPassword);

	char szUpperNewPassword[256];
	SStrCopy(szUpperNewPassword, szNewPassword, sizeof(szUpperNewPassword));
	SStrUpper(szUpperNewPassword);

	gtBnSRP.CreateVerifier(szUserName, szUpperNewPassword, gpBnSRPNewSalt, gpBnSRPNewVerifier);
	gtBnSRP.StartLogon(&gtBnSRPSession, szUserName, szUpperOldPassword);

	SMemCopy(tPacket.A, gtBnSRPSession.A, sizeof(tPacket.A));
	const size_t nLength = SStrCopy(tPacket.szAccountName, szAccountName, sizeof(tPacket.szAccountName));
	BNET_SendPacket(SID_AUTH_ACCOUNTCHANGE, &tPacket, offsetof(decltype(tPacket), szAccountName) + nLength + 1);
	return FALSE;
}

//Bnclient.0x6FF08A00
BOOL __fastcall BNSRP_HandleChangeChallenge(const uint8_t* pSalt, const uint8_t* pB)
{
#pragma pack(push, 1)
	struct
	{
		uint8_t M1[20];
		uint8_t pNewSalt[32];
		uint8_t pNewVerifier[32];
	} tPacket;
#pragma pack(pop)

	const BOOL bResult = gtBnSRP.ProcessChallenge(&gtBnSRPSession, pSalt, pB);
	SMemZero(gtBnSRPSession.szPassword, sizeof(gtBnSRPSession.szPassword));
	if (!bResult)
	{
		return FALSE;
	}

	SMemCopy(tPacket.M1, gtBnSRPSession.M1, sizeof(tPacket.M1));
	SMemCopy(tPacket.pNewSalt, gpBnSRPNewSalt, sizeof(tPacket.pNewSalt) + sizeof(tPacket.pNewVerifier));
	SMemZero(gpBnSRPNewSalt, sizeof(gpBnSRPNewSalt) + sizeof(gpBnSRPNewVerifier));
	BNET_SendPacket(SID_AUTH_ACCOUNTCHANGEPROOF, &tPacket, sizeof(tPacket));
	return TRUE;
}

//Bnclient.0x6FF08A80
BOOL __fastcall BNSRP_RequestUpgrade(BOOL bLogon)
{
	if (bLogon && ++gbBnSRPUpgradingLogon > 1)
	{
		return FALSE;
	}

	gtBnSRP.CreateVerifier(gtBnSRPSession.szUserName, gtBnSRPSession.szPassword, gpBnSRPNewSalt, gpBnSRPNewVerifier);
	BNET_SendPacket(SID_AUTH_ACCOUNTUPGRADE, nullptr, 0);
	return TRUE;
}

//Bnclient.0x6FF08AD0
BOOL __fastcall BNSRP_SendUpgradeProof(uint32_t nServerToken)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nClientToken;
		uint32_t nServerToken;
		uint8_t pPasswordHash[20];
	} tHashData;

	struct
	{
		uint32_t nClientToken;
		uint8_t pOldPasswordHash[20];
		uint8_t pNewSalt[32];
		uint8_t pNewVerifier[32];
	} tPacket;
#pragma pack(pop)

	tHashData.nClientToken = GetTickCount();
	tHashData.nServerToken = nServerToken;

	char szLowerPassword[256];
	const size_t nLength = SStrCopy(szLowerPassword, gtBnSRPSession.szPassword, sizeof(szLowerPassword));
	CharLowerBuffA(szLowerPassword, nLength);
	GRID_XSHA(tHashData.pPasswordHash, szLowerPassword, SStrLen(szLowerPassword));

	tPacket.nClientToken = tHashData.nClientToken;
	GRID_XSHA(tPacket.pOldPasswordHash, &tHashData, sizeof(tHashData));
	SMemCopy(tPacket.pNewSalt, gpBnSRPNewSalt, sizeof(tPacket.pNewSalt) + sizeof(tPacket.pNewVerifier));
	SMemZero(gpBnSRPNewSalt, sizeof(gpBnSRPNewSalt) + sizeof(gpBnSRPNewVerifier));
	BNET_SendPacket(SID_AUTH_ACCOUNTUPGRADEPROOF, &tPacket, sizeof(tPacket));
	return FALSE;
}

//Bnclient.0x6FF08B70
BOOL __fastcall BNSRP_VerifyServerProof(const uint8_t* pM2)
{
	return gtBnSRP.VerifyServerProof(&gtBnSRPSession, pM2);
}

//Bnclient.0x6FF08B90
BOOL __stdcall BNSRP_IsUpgradingLogon()
{
	return gbBnSRPUpgradingLogon;
}

//Bnclient.0x6FF08BA0
void __stdcall BNSRP_ClearPasswords()
{
	SMemZero(gtBnSRPSession.szPassword, sizeof(gtBnSRPSession.szPassword));
}
