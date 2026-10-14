#include "BnSend.h"

#include <Winsock2.h>

#include <climits>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <Fog.h>
#include <Storm.h>

#include "BnConnect.h"
#include "BnDownload.h"
#include "BnImports.h"
#include "BnMessQueue.h"
#include "BnRecv.h"
#include "Grid.h"


#define MAXSTRINGLENGTH 256

uint32_t gnBnServerToken;
uint32_t gnBnLogonType;
uint32_t gnBnRealmClientToken;
void* gpBnChannelList;
void* gpBnRealmList;
void* gpBnGameList;
RealmLogonInformation* gpBnRealmLogonInformation;
void* gpBnUserData;
uint8_t* gpBnAdUrl;
uint32_t gnBnClientToken;


static uint32_t BNSEND_GetProductId()
{
	return BNET_IsExpansion() ? 'D2XP' : 'D2DV';
}

// CD key character to value, '0'-'9' and 'A'-'Z'/'a'-'z' without the letters I, L, O, Q, S and U
//Bnclient.0x6FF162D8
static const int8_t gnBnCDKeyCharacterValues[256] =
{
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, 0x00, -1, 0x01, -1, 0x02, 0x03, 0x04, 0x05, -1, -1, -1, -1, -1, -1,
	-1, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, -1, 0x0D, 0x0E, -1, 0x0F, 0x10, -1, 0x11,
	-1, 0x12, -1, 0x13, -1, 0x14, 0x15, 0x16, -1, 0x17, -1, -1, -1, -1, -1, -1,
	-1, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, -1, 0x0D, 0x0E, -1, 0x0F, 0x10, -1, 0x11,
	-1, 0x12, -1, 0x13, -1, 0x14, 0x15, 0x16, -1, 0x17, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

static char BNCDKEY_ToHexDigit(uint32_t nValue)
{
	return nValue < 10 ? (char)('0' + nValue) : (char)('A' - 10 + nValue);
}

//Bnclient.0x6FF06E80
BOOL __fastcall BNCDKEY_Decode(const char* szCDKey, uint32_t* pProductValue, uint32_t* pPublicValue, uint32_t* pPrivateValue)
{
	*pProductValue = 0;
	*pPublicValue = 0;
	*pPrivateValue = 0;

	if (!szCDKey)
	{
		return FALSE;
	}

	char szKey[32];
	SStrCopy(szKey, szCDKey, sizeof(szKey));

	uint32_t nChecksum = 0;
	uint32_t nBit = 1;
	for (int i = 0; i < 16; i += 2)
	{
		uint32_t nValue = 24 * gnBnCDKeyCharacterValues[(uint8_t)szKey[i]] + gnBnCDKeyCharacterValues[(uint8_t)szKey[i + 1]];
		if (nValue >= 256)
		{
			nValue -= 256;
			nChecksum |= nBit;
		}

		szKey[i] = BNCDKEY_ToHexDigit((nValue >> 4) & 0xF);
		szKey[i + 1] = BNCDKEY_ToHexDigit(nValue & 0xF);
		nBit += nBit;
	}

	uint32_t nComputedChecksum = 3;
	for (int i = 0; i < 16; ++i)
	{
		const char c = (char)tolower(szKey[i]);
		const int nDigit = c >= 'a' ? c - 'a' + 10 : c - '0';
		nComputedChecksum += nDigit ^ (2 * nComputedChecksum);
	}

	if ((nComputedChecksum & 0xFF) != nChecksum)
	{
		return FALSE;
	}

	for (int i = 15; i >= 0; --i)
	{
		const int j = (i + 7) & 0xF;
		const char c = szKey[i];
		szKey[i] = szKey[j];
		szKey[j] = c;
	}

	uint32_t nMask = 0x13AC9741;
	for (int i = 15; i >= 0; --i)
	{
		const char c = (char)toupper(szKey[i]);
		szKey[i] = c;
		if (c <= '7')
		{
			szKey[i] = (char)((nMask & 7) ^ c);
			nMask >>= 3;
		}
		else if (c < 'A')
		{
			szKey[i] = (char)((i & 1) ^ c);
		}
	}

	char szProduct[3];
	char szPublic[7];
	char szPrivate[9];
	SStrCopy(szProduct, &szKey[0], sizeof(szProduct));
	SStrCopy(szPublic, &szKey[2], sizeof(szPublic));
	SStrCopy(szPrivate, &szKey[8], sizeof(szPrivate));

	*pProductValue = strtoul(szProduct, nullptr, 16);
	*pPublicValue = strtoul(szPublic, nullptr, 16);
	*pPrivateValue = strtoul(szPrivate, nullptr, 16);
	return TRUE;
}

//Bnclient.0x6FF07070
BOOL __stdcall BNCDKEY_Validate()
{
	uint32_t nProductValue;
	uint32_t nPublicValue;
	uint32_t nPrivateValue;

	GRID_LoadCDKeys();

	BOOL bResult = BNCDKEY_Decode(GRID_GetCDKey(0), &nProductValue, &nPublicValue, &nPrivateValue);
	if (bResult && BNET_IsExpansion())
	{
		bResult = BNCDKEY_Decode(GRID_GetCDKey(1), &nProductValue, &nPublicValue, &nPrivateValue);
	}

	GRID_UnloadCDKeys();
	return bResult;
}

//Bnclient.0x6FF070E0
BOOL __fastcall BNCDKEY_ComputeKeyInfo(BnCDKeyInfo* pKeyInfo, uint32_t nClientToken, int nKeyIndex)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nClientToken;
		uint32_t nServerToken;
		uint32_t nProductValue;
		uint32_t nPublicValue;
		uint32_t nUnknown;
		uint32_t nPrivateValue;
	} tHashData;
#pragma pack(pop)

	const uint32_t nServerToken = BNSEND_GetServerToken();
	const char* szCDKey = GRID_GetCDKey(nKeyIndex);

	tHashData.nClientToken = nClientToken;
	tHashData.nServerToken = nServerToken;
	if (!BNCDKEY_Decode(szCDKey, &tHashData.nProductValue, &tHashData.nPublicValue, &tHashData.nPrivateValue))
	{
		return FALSE;
	}

	tHashData.nUnknown = 0;

	pKeyInfo->nKeyLength = SStrLen(szCDKey);
	pKeyInfo->nProductValue = tHashData.nProductValue;
	pKeyInfo->nPublicValue = tHashData.nPublicValue;
	pKeyInfo->nUnknown = tHashData.nUnknown;
	GRID_XSHA(pKeyInfo->pHash, &tHashData, sizeof(tHashData));
	return TRUE;
}

//Bnclient.0x6FF07180
void __fastcall BNSEND_SetServerToken(uint32_t nServerToken)
{
	gnBnServerToken = nServerToken;
}

//Bnclient.0x6FF07190
uint32_t __stdcall BNSEND_GetServerToken()
{
	return gnBnServerToken;
}

//Bnclient.0x6FF071A0
void __fastcall BNSEND_SetLogonType(uint32_t nLogonType)
{
	gnBnLogonType = nLogonType;
}

//Bnclient.0x6FF071B0
uint32_t __stdcall BNSEND_GetLogonType()
{
	return gnBnLogonType;
}

#pragma pack(push, 1)
struct BnPasswordHashData
{
	uint32_t nClientToken;
	uint32_t nServerToken;
	uint8_t pPasswordHash[20];
};
#pragma pack(pop)

//Bnclient.0x6FF071C0
BOOL __fastcall BNSEND_LogonResponse2(const char* szAccountName, const char* szPassword)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nClientToken;
		uint32_t nServerToken;
		uint8_t pPasswordHash[20];
		char szAccountName[256];
	} tPacket;
#pragma pack(pop)

	BNRECV_ResetMessage(SID_LOGONRESPONSE2);

	char szLowerPassword[256];
	SStrCopy(szLowerPassword, szPassword, sizeof(szLowerPassword));
	const size_t nPasswordLength = SStrLen(szLowerPassword);
	CharLowerBuffA(szLowerPassword, nPasswordLength);

	BnPasswordHashData tHashData;
	tHashData.nClientToken = GetTickCount();
	tHashData.nServerToken = gnBnServerToken;
	GRID_XSHA(tHashData.pPasswordHash, szLowerPassword, nPasswordLength);

	tPacket.nClientToken = tHashData.nClientToken;
	tPacket.nServerToken = tHashData.nServerToken;
	GRID_XSHA(tPacket.pPasswordHash, &tHashData, sizeof(tHashData));

	const size_t nAccountLength = SStrCopy(tPacket.szAccountName, szAccountName, sizeof(tPacket.szAccountName));
	BNET_SendPacket(SID_LOGONRESPONSE2, &tPacket, offsetof(decltype(tPacket), szAccountName) + nAccountLength + 1);
	return TRUE;
}

//Bnclient.0x6FF07280
BOOL __fastcall BNSEND_CreateAccount2(const char* szAccountName, const char* szPassword)
{
#pragma pack(push, 1)
	struct
	{
		uint8_t pPasswordHash[20];
		char szAccountName[256];
	} tPacket;
#pragma pack(pop)

	char szLowerPassword[256];
	SStrCopy(szLowerPassword, szPassword, sizeof(szLowerPassword));
	const size_t nPasswordLength = SStrLen(szLowerPassword);
	CharLowerBuffA(szLowerPassword, nPasswordLength);
	GRID_XSHA(tPacket.pPasswordHash, szLowerPassword, nPasswordLength);

	const size_t nAccountLength = SStrCopy(tPacket.szAccountName, szAccountName, sizeof(tPacket.szAccountName));
	BNET_SendPacket(SID_CREATEACCOUNT2, &tPacket, offsetof(decltype(tPacket), szAccountName) + nAccountLength + 1);
	return TRUE;
}

//Bnclient.0x6FF07300
BOOL __fastcall BNSEND_ChangePassword(const char* szAccountName, const char* szOldPassword, const char* szNewPassword)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nClientToken;
		uint32_t nServerToken;
		uint8_t pOldPasswordHash[20];
		uint8_t pNewPasswordHash[20];
		char szAccountName[256];
	} tPacket;
#pragma pack(pop)

	char szLowerPassword[256];
	SStrCopy(szLowerPassword, szOldPassword, sizeof(szLowerPassword));
	size_t nPasswordLength = SStrLen(szLowerPassword);
	CharLowerBuffA(szLowerPassword, nPasswordLength);

	BnPasswordHashData tHashData;
	tHashData.nClientToken = GetTickCount();
	tHashData.nServerToken = gnBnServerToken;
	GRID_XSHA(tHashData.pPasswordHash, szLowerPassword, nPasswordLength);

	SStrCopy(szLowerPassword, szNewPassword, sizeof(szLowerPassword));
	nPasswordLength = SStrLen(szLowerPassword);
	CharLowerBuffA(szLowerPassword, nPasswordLength);

	tPacket.nClientToken = tHashData.nClientToken;
	tPacket.nServerToken = tHashData.nServerToken;
	GRID_XSHA(tPacket.pOldPasswordHash, &tHashData, sizeof(tHashData));
	GRID_XSHA(tPacket.pNewPasswordHash, szLowerPassword, nPasswordLength);

	const size_t nAccountLength = SStrCopy(tPacket.szAccountName, szAccountName, sizeof(tPacket.szAccountName));
	BNET_SendPacket(SID_CHANGEPASSWORD, &tPacket, offsetof(decltype(tPacket), szAccountName) + nAccountLength + 1);
	return TRUE;
}

//Bnclient.0x6FF073F0
void __fastcall BNSEND_StoreRealmList(const uint8_t* pData, uint32_t nSize)
{
	if (gpBnRealmList)
	{
		FOG_Trace("Freeing Realm List.\n");
		D2_FREE(gpBnRealmList);
	}

	gpBnRealmList = nullptr;
	gpBnRealmList = D2_ALLOC(nSize);
	FOG_Trace("Storing Realm List.\n");
	memcpy(gpBnRealmList, pData, nSize);
}

//Bnclient.0x6FF07470
void __fastcall BNSEND_StoreAdUrl(const uint8_t* pData, uint32_t nSize)
{
	if (gpBnAdUrl)
	{
		SMemFree(gpBnAdUrl, __FILE__, __LINE__, 0);
	}

	gpBnAdUrl = (uint8_t*)SMemAlloc(nSize, __FILE__, __LINE__, 0);
	memcpy(gpBnAdUrl, pData, nSize);
}

//Bnclient.0x6FF074C0
const char* __fastcall BNSEND_QueryAdUrl(uint32_t nAdId)
{
	BNRECV_ResetMessage(SID_QUERYADURL);
	if (!BNET_SendPacket(SID_QUERYADURL, &nAdId, sizeof(nAdId)))
	{
		FOG_Trace("Failed to query ad URL\n");
		return nullptr;
	}

	BNRECV_WaitForMessage(SID_QUERYADURL);
	if (!gpBnAdUrl)
	{
		return nullptr;
	}

	return (const char*)&gpBnAdUrl[4];
}

//Bnclient.0x6FF07510
void* __stdcall BNSEND_QueryRealms()
{
	BNRECV_ResetMessage(SID_QUERYREALMS2);
	if (!BNET_SendPacket(SID_QUERYREALMS2, nullptr, 0))
	{
		FOG_Trace("Failed to send Realm List\n");
		return nullptr;
	}

	BNRECV_WaitForMessage(SID_QUERYREALMS2);
	return gpBnRealmList;
}

//Bnclient.0x6FF07550
void __fastcall BNSEND_StoreChannelList(const uint8_t* pData, uint32_t nSize)
{
	if (gpBnChannelList)
	{
		D2_FREE(gpBnChannelList);
	}

	gpBnChannelList = nullptr;
	gpBnChannelList = D2_ALLOC(nSize);
	memcpy(gpBnChannelList, pData, nSize);
}

//Bnclient.0x6FF075B0
void __stdcall BNSEND_FreeChannelList()
{
	if (gpBnChannelList)
	{
		D2_FREE(gpBnChannelList);
	}

	gpBnChannelList = nullptr;
}

//Bnclient.0x6FF075E0
void* __fastcall BNSEND_GetChannelList(BOOL bClassic)
{
	uint32_t nFlags = 0;
	if (BNET_IsExpansion() && !bClassic)
	{
		nFlags |= 1;
	}

	BNRECV_ResetMessage(SID_GETCHANNELLIST);
	BNET_SendPacket(SID_GETCHANNELLIST, &nFlags, sizeof(nFlags));
	BNRECV_WaitForMessage(SID_GETCHANNELLIST);
	return gpBnChannelList;
}

//Bnclient.0x6FF07630
BOOL __fastcall BNSEND_JoinChannel(const char* szChannel, BOOL bForced, BOOL bClassic)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nFlags;
		char szChannel[256];
	} tPacket;
#pragma pack(pop)

	memset(&tPacket, 0x00, sizeof(tPacket));

	if (szChannel && *szChannel)
	{
		tPacket.nFlags = bForced ? 2 : 0;
		SStrCopy(tPacket.szChannel, szChannel, sizeof(tPacket.szChannel));
	}
	else
	{
		tPacket.nFlags = 1;
		if (BNET_IsExpansion() && !bClassic)
		{
			tPacket.nFlags |= 4;
		}
		SStrCopy(tPacket.szChannel, "Diablo II", sizeof(tPacket.szChannel));
	}

	BNET_SendPacket(SID_JOINCHANNEL, &tPacket, offsetof(decltype(tPacket), szChannel) + strlen(tPacket.szChannel) + 1);
	return TRUE;
}

//Bnclient.0x6FF076D0
BOOL __fastcall BNSEND_EnterChat(const char* szCharacterName, const char* szStatstring, const char* szUnused)
{
	uint32_t nProductId = BNSEND_GetProductId();
	BNET_SendPacket(SID_GETCHANNELLIST, &nProductId, sizeof(nProductId));

	char szBuffer[512] = "";
	SStrCopy(szBuffer, szCharacterName, 256);
	SStrCopy(&szBuffer[strlen(szBuffer) + 1], szStatstring, 256);

	const size_t nCharacterNameLength = strlen(szBuffer);
	const size_t nStatstringLength = strlen(&szBuffer[nCharacterNameLength + 1]);
	return BNET_SendPacket(SID_ENTERCHAT, szBuffer, nCharacterNameLength + nStatstringLength + 2) != 0;
}

//Bnclient.0x6FF077A0
BOOL __stdcall BNSEND_LeaveChat()
{
	return BNET_SendPacket(SID_LEAVECHAT, nullptr, 0) != 0;
}

//Bnclient.0x6FF077C0
BOOL __fastcall BNSEND_ChatCommand(const char* szText)
{
	if (!szText || !strlen(szText))
	{
		return FALSE;
	}

	wchar_t wszText[511];
	int nLength = SUniConvert912(wszText, szText, ARRAYSIZE(wszText));
	if (!nLength)
	{
		return FALSE;
	}
	wszText[nLength] = L'\0';

	char szUtf8Text[511];
	if (SUniConvertUTF16to8(szUtf8Text, sizeof(szUtf8Text), wszText, ARRAYSIZE(wszText), &nLength, 0))
	{
		return FALSE;
	}

	szUtf8Text[nLength] = '\0';
	return BNET_SendPacket(SID_CHATCOMMAND, szUtf8Text, nLength) != 0;
}

//Bnclient.0x6FF07860
BOOL __stdcall BNSEND_CheckAd()
{
	uint32_t aPacket[4];
	aPacket[0] = 'IX86';
	aPacket[1] = BNSEND_GetProductId();
	aPacket[2] = gnBnLastAdId;
	aPacket[3] = (uint32_t)time(nullptr);
	BNET_SendPacket(SID_CHECKAD, aPacket, sizeof(aPacket));
	return TRUE;
}

//Bnclient.0x6FF078B0
BOOL __fastcall BNSEND_DisplayAd(const char* szFileName, const char* szLinkUrl)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nPlatformId;
		uint32_t nProductId;
		uint32_t nAdId;
		char szFileName[1];
		char szLinkUrl[1];
	} tPacket;
#pragma pack(pop)

	tPacket.nPlatformId = 'IX86';
	tPacket.nProductId = BNSEND_GetProductId();
	tPacket.nAdId = gnBnLastAdId;
	tPacket.szFileName[0] = '\0';
	tPacket.szLinkUrl[0] = '\0';
	BNET_SendPacket(SID_DISPLAYAD, &tPacket, sizeof(tPacket));
	return TRUE;
}

//Bnclient.0x6FF07910
BOOL __fastcall BNSEND_StartAdvEx3(const char* szGameName, const char* szPassword, const char* szStatstring, uint32_t nGameType)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nState;
		uint32_t nUptime;
		uint32_t nGameType;
		uint32_t nParameter;
		uint32_t nUnknown;
		char szStrings[256];
	} tPacket;
#pragma pack(pop)

	tPacket.nState = 0;
	tPacket.nUptime = 0;
	tPacket.nGameType = nGameType;
	tPacket.nParameter = 0;
	tPacket.nUnknown = 0;

	if (!szGameName)
	{
		szGameName = "";
	}

	if (!szPassword)
	{
		szPassword = "";
	}

	if (!szStatstring)
	{
		szStatstring = "";
	}

	if (*szPassword)
	{
		tPacket.nState = 1;
	}

	char* pCursor = tPacket.szStrings;
	pCursor += SStrCopy(pCursor, szGameName, 256) + 1;
	pCursor += SStrCopy(pCursor, szPassword, 256) + 1;
	const size_t nStatstringLength = SStrCopy(pCursor, szStatstring, 256);
	BNET_SendPacket(SID_STARTADVEX3, &tPacket, offsetof(decltype(tPacket), szStrings) + (pCursor - tPacket.szStrings) + nStatstringLength + 1);
	return TRUE;
}

//Bnclient.0x6FF079C0
BOOL __stdcall BNSEND_StopAdv()
{
	BNET_SendPacket(SID_STOPADV, nullptr, 0);
	return TRUE;
}

//Bnclient.0x6FF079E0
BOOL __stdcall BNSEND_LeaveGame()
{
	BNET_SendPacket(SID_LEAVEGAME, nullptr, 0);
	return TRUE;
}

//Bnclient.0x6FF07A00
BOOL __fastcall BNSEND_GetCreateGameResult(int32_t* pResult)
{
	*pResult = BNRECV_GetMessageResult(SID_STARTADVEX3);
	return BNRECV_WasMessageReceived(SID_STARTADVEX3);
}

//Bnclient.0x6FF07A20
void __fastcall BNSEND_StoreGameList(const uint8_t* pData, uint32_t nSize)
{
	if (gpBnGameList)
	{
		D2_FREE(gpBnGameList);
	}

	gpBnGameList = nullptr;
	gpBnGameList = D2_ALLOC(nSize);
	memcpy(gpBnGameList, pData, nSize);
}

//Bnclient.0x6FF07A80
void __stdcall BNSEND_FreeGameList()
{
	if (gpBnGameList)
	{
		D2_FREE(gpBnGameList);
	}

	gpBnGameList = nullptr;
}

//Bnclient.0x6FF07AB0
void* __fastcall BNSEND_GetGameList(const char* szGameName, const char* szPassword, uint32_t nUnused1, uint32_t nUnused2)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nGameType;
		uint32_t nUnknown;
		uint32_t nViewingFilter;
		uint32_t nGameCount;
		char szStrings[256];
	} tPacket;
#pragma pack(pop)

	tPacket.nGameType = 0;
	tPacket.nUnknown = 0;
	tPacket.nViewingFilter = 0;
	tPacket.nGameCount = 25;

	char* pCursor = tPacket.szStrings;
	pCursor += SStrCopy(pCursor, szGameName ? szGameName : "", 256) + 1;
	pCursor += SStrCopy(pCursor, szPassword ? szPassword : "", 256) + 1;
	const size_t nStatstringLength = SStrCopy(pCursor, "", 256);

	BNRECV_ResetMessage(SID_GETADVLISTEX);
	BNET_SendPacket(SID_GETADVLISTEX, &tPacket, offsetof(decltype(tPacket), szStrings) + (pCursor - tPacket.szStrings) + nStatstringLength + 1);
	BNRECV_WaitForMessage(SID_GETADVLISTEX);
	return gpBnGameList;
}

//Bnclient.0x6FF07B60
BOOL __fastcall BNSEND_NotifyJoin(const char* szGameName, const char* szPassword)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nProductId;
		uint32_t nVersion;
		char szStrings[512];
	} tPacket;
#pragma pack(pop)

	tPacket.nProductId = BNSEND_GetProductId();
	tPacket.nVersion = 10;

	char* pCursor = tPacket.szStrings;
	pCursor += SStrCopy(pCursor, szGameName, 256) + 1;
	const size_t nPasswordLength = SStrCopy(pCursor, szPassword, 256);
	BNET_SendPacket(SID_NOTIFYJOIN, &tPacket, offsetof(decltype(tPacket), szStrings) + (pCursor - tPacket.szStrings) + nPasswordLength + 1);
	return TRUE;
}

//Bnclient.0x6FF07BD0
void __fastcall BNSEND_StoreRealmLogonInformation(const uint8_t* pData, uint32_t nSize)
{
	if (gpBnRealmLogonInformation)
	{
		D2_FREE(gpBnRealmLogonInformation);
	}

	gpBnRealmLogonInformation = nullptr;
	gpBnRealmLogonInformation = (RealmLogonInformation*)D2_ALLOC(nSize + sizeof(uint32_t));
	gpBnRealmLogonInformation->nSize = nSize;
	memcpy(&gpBnRealmLogonInformation->tPacket, pData, nSize);

	if (nSize != 8 && nSize >= 0x48)
	{
		gpBnRealmLogonInformation->tPacket.MCPPort = ntohs((u_short)gpBnRealmLogonInformation->tPacket.MCPPort);
	}
}

//Bnclient.0x6FF07C60
RealmLogonInformation* __fastcall BNSEND_LogonRealm(const char* szRealmName, const char* szPassword)
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nClientToken;
		uint8_t pPasswordHash[20];
		char szRealmName[256];
	} tPacket;
#pragma pack(pop)

	if (!szRealmName)
	{
		return nullptr;
	}

	++gnBnRealmClientToken;

	BnPasswordHashData tHashData;
	tHashData.nClientToken = gnBnRealmClientToken;
	tHashData.nServerToken = gnBnServerToken;
	GRID_XSHA(tHashData.pPasswordHash, szPassword, strlen(szPassword));

	tPacket.nClientToken = gnBnRealmClientToken;
	GRID_XSHA(tPacket.pPasswordHash, &tHashData, sizeof(tHashData));

	const size_t nRealmNameLength = SStrCopy(tPacket.szRealmName, szRealmName, sizeof(tPacket.szRealmName));
	BNRECV_ResetMessage(SID_LOGONREALMEX);
	if (!BNET_SendPacket(SID_LOGONREALMEX, &tPacket, offsetof(decltype(tPacket), szRealmName) + nRealmNameLength + 1))
	{
		return nullptr;
	}

	BNRECV_WaitForMessage(SID_LOGONREALMEX);
	return gpBnRealmLogonInformation;
}

//Bnclient.0x6FF07D10
BOOL __fastcall BNSEND_ClickAd(uint32_t nAdId, BOOL bClicked)
{
	uint32_t aPacket[2];
	aPacket[0] = nAdId;
	aPacket[1] = bClicked != 0;
	BNET_SendPacket(SID_CLICKAD, aPacket, sizeof(aPacket));
	return TRUE;
}

//Bnclient.0x6FF07D40
int __fastcall BNSEND_WriteUserData(const char* szAccountName, uint32_t nKeys, const char** pKeys, const char** pValues)
{
	uint32_t nSize = SStrLen(szAccountName) + 1;
	for (uint32_t i = 0; i < nKeys; ++i)
	{
		nSize += SStrLen(pKeys[i]) + 1;
		nSize += SStrLen(pValues[i]) + 1;
	}

	uint32_t* pPacket = (uint32_t*)D2_ALLOC(nSize + 2 * sizeof(uint32_t));
	pPacket[0] = 1;
	pPacket[1] = nKeys;

	char* pCursor = (char*)&pPacket[2];
	pCursor += SStrCopy(pCursor, szAccountName, INT_MAX) + 1;
	for (uint32_t i = 0; i < nKeys; ++i)
	{
		pCursor += SStrCopy(pCursor, pKeys[i], INT_MAX) + 1;
	}

	for (uint32_t i = 0; i < nKeys; ++i)
	{
		pCursor += SStrCopy(pCursor, pValues[i], INT_MAX) + 1;
	}

	BNRECV_ResetMessage(SID_WRITEUSERDATA);
	const int nResult = BNET_SendPacket(SID_WRITEUSERDATA, pPacket, pCursor - (char*)pPacket);
	D2_FREE(pPacket);
	return nResult;
}

//Bnclient.0x6FF07E40
void __fastcall BNSEND_StoreUserData(const uint8_t* pData, uint32_t nSize)
{
	if (gpBnUserData)
	{
		D2_FREE(gpBnUserData);
	}

	gpBnUserData = D2_ALLOC(nSize);
	memcpy(gpBnUserData, pData, nSize);
}

//Bnclient.0x6FF07E90
BOOL __fastcall BNSEND_RequestUserData(const char* szAccountName, uint32_t nKeys, uint32_t nRequestId, const char** pKeys)
{
	uint32_t nSize = SStrLen(szAccountName) + 1;
	for (uint32_t i = 0; i < nKeys; ++i)
	{
		nSize += SStrLen(pKeys[i]) + 1;
	}

	uint32_t* pPacket = (uint32_t*)D2_ALLOC(nSize + 3 * sizeof(uint32_t));
	pPacket[0] = 1;
	pPacket[1] = nKeys;
	pPacket[2] = nRequestId;

	char* pCursor = (char*)&pPacket[3];
	pCursor += SStrCopy(pCursor, szAccountName, INT_MAX) + 1;
	for (uint32_t i = 0; i < nKeys; ++i)
	{
		pCursor += SStrCopy(pCursor, pKeys[i], INT_MAX) + 1;
	}

	BNRECV_ResetMessage(SID_READUSERDATA);
	const int nResult = BNET_SendPacket(SID_READUSERDATA, pPacket, pCursor - (char*)pPacket);
	D2_FREE(pPacket);
	return nResult != 0;
}

//Bnclient.0x6FF07F50
BOOL __fastcall BNSEND_GetUserData(uint32_t nKeys, uint32_t nRequestId, char** pValues, const uint32_t* pValueSizes)
{
	if (!BNRECV_WasMessageReceived(SID_READUSERDATA))
	{
		return FALSE;
	}

	const uint32_t* pUserData = (const uint32_t*)gpBnUserData;
	if (!pUserData || pUserData[0] != 1 || pUserData[1] != nKeys || pUserData[2] != nRequestId)
	{
		BNET_DebugTrace("BattleReadUserData: Invalid response from server");
		return FALSE;
	}

	const char* pCursor = (const char*)&pUserData[3];
	for (uint32_t i = 0; i < nKeys; ++i)
	{
		if (*pCursor)
		{
			strncpy(pValues[i], pCursor, pValueSizes[i]);
			pValues[i][pValueSizes[i]] = '\0';
		}
		else
		{
			pValues[i][0] = '\0';
		}

		pCursor += SStrLen(pCursor) + 1;
	}

	return TRUE;
}

//Bnclient.0x6FF07FF0
BOOL __fastcall BNSEND_SetEmail(const char* szEmail)
{
	D2_ASSERT(szEmail);

	const size_t len = SStrLen(szEmail) + 1;
	D2_ASSERT(len <= MAXSTRINGLENGTH);

	return BNET_SendPacket(SID_SETEMAIL, szEmail, len) != 0;
}

//Bnclient.0x6FF08060
BOOL __fastcall BNSEND_ResetPassword(const char* szAccountName, const char* szEmail)
{
	char szPacket[2 * MAXSTRINGLENGTH];

	D2_ASSERT(szAccountName);
	D2_ASSERT(szAccountName[0]);

	if (!szEmail || !*szEmail)
	{
		return FALSE;
	}

	const size_t len = SStrLen(szAccountName) + 1;
	D2_ASSERT(len <= MAXSTRINGLENGTH);
	memcpy(szPacket, szAccountName, len);

	const size_t emailLen = SStrLen(szEmail) + 1;
	D2_ASSERT(emailLen <= MAXSTRINGLENGTH);
	memcpy(&szPacket[len], szEmail, emailLen);

	return BNET_SendPacket(SID_RESETPASSWORD, szPacket, len + emailLen) != 0;
}

//Bnclient.0x6FF08180
BOOL __fastcall BNSEND_ChangeEmail(const char* szAccountName, const char* szOldEmail, const char* szNewEmail)
{
	char szPacket[3 * MAXSTRINGLENGTH];

	D2_ASSERT(szAccountName);
	D2_ASSERT(szAccountName[0]);

	if (!szOldEmail || !*szOldEmail || !szNewEmail || !*szNewEmail)
	{
		return FALSE;
	}

	const size_t len = SStrLen(szAccountName) + 1;
	D2_ASSERT(len <= MAXSTRINGLENGTH);
	memcpy(szPacket, szAccountName, len);

	const size_t oldEmailLen = SStrLen(szOldEmail) + 1;
	D2_ASSERT(oldEmailLen <= MAXSTRINGLENGTH);
	memcpy(&szPacket[len], szOldEmail, oldEmailLen);

	const size_t newEmailLen = SStrLen(szNewEmail) + 1;
	D2_ASSERT(newEmailLen <= MAXSTRINGLENGTH);
	memcpy(&szPacket[len + oldEmailLen], szNewEmail, newEmailLen);

	return BNET_SendPacket(SID_CHANGEEMAIL, szPacket, len + oldEmailLen + newEmailLen) != 0;
}

//Bnclient.0x6FF08310
void __stdcall BNSEND_SystemInfo()
{
	uint32_t nSize = 1500;
	uint8_t pBuffer[1500];
	if (FOG_GetHardwareInfo(pBuffer, &nSize))
	{
		BNET_SendPacket(SID_SYSTEMINFO, pBuffer, nSize);
	}
}

//Bnclient.0x6FF083D0
BOOL __stdcall BNSEND_AuthInfo()
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nProtocolId;
		uint32_t nPlatformId;
		uint32_t nProductId;
		uint32_t nVersion;
		uint32_t nProductLanguage;
		uint32_t nLocalIp;
		uint32_t nTimeZoneBias;
		uint32_t nLocaleId;
		uint32_t nLanguageId;
		char szCountryAbbreviation[4];
		char szCountry[256];
	} tPacket;
#pragma pack(pop)

	memset(&tPacket, 0x00, sizeof(tPacket));
	tPacket.nProtocolId = 0;
	tPacket.nPlatformId = 'IX86';
	tPacket.nProductId = BNSEND_GetProductId();
	tPacket.nVersion = 10;
	D2LANG_GetLanguageCode((char*)&tPacket.nProductLanguage, 3);

	sockaddr_in tLocalAddress;
	int nLocalAddressLength = sizeof(tLocalAddress);
	tPacket.nLocalIp = BNET_GetSockName((sockaddr*)&tLocalAddress, &nLocalAddressLength) ? tLocalAddress.sin_addr.s_addr : 0;

	SYSTEMTIME tSystemTime;
	SYSTEMTIME tLocalTime;
	GetSystemTime(&tSystemTime);
	GetLocalTime(&tLocalTime);

	FILETIME tSystemFileTime;
	FILETIME tLocalFileTime;
	SystemTimeToFileTime(&tSystemTime, &tSystemFileTime);
	SystemTimeToFileTime(&tLocalTime, &tLocalFileTime);

	const int64_t nSystemTime = ((int64_t)tSystemFileTime.dwHighDateTime << 32) | tSystemFileTime.dwLowDateTime;
	const int64_t nLocalTime = ((int64_t)tLocalFileTime.dwHighDateTime << 32) | tLocalFileTime.dwLowDateTime;
	tPacket.nTimeZoneBias = (uint32_t)((nSystemTime - nLocalTime) / 600000000);

	tPacket.nLocaleId = GetUserDefaultLCID();

	using GetSystemDefaultUILanguageFunction = LANGID(WINAPI*)();
	HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
	LANGID nLanguageId;
	if (hKernel32)
	{
		if (GetSystemDefaultUILanguageFunction pfGetSystemDefaultUILanguage = (GetSystemDefaultUILanguageFunction)GetProcAddress(hKernel32, "GetSystemDefaultUILanguage"))
		{
			nLanguageId = pfGetSystemDefaultUILanguage();
			FreeLibrary(hKernel32);
		}
		else
		{
			FreeLibrary(hKernel32);
			nLanguageId = GetSystemDefaultLangID();
		}
	}
	else
	{
		nLanguageId = GetSystemDefaultLangID();
	}
	tPacket.nLanguageId = nLanguageId;

	char szCountryAbbreviation[64];
	GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SABBREVCTRYNAME, szCountryAbbreviation, sizeof(szCountryAbbreviation));
	szCountryAbbreviation[3] = '\0';
	memcpy(tPacket.szCountryAbbreviation, szCountryAbbreviation, sizeof(tPacket.szCountryAbbreviation));
	GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SENGCOUNTRY, tPacket.szCountry, sizeof(tPacket.szCountry));

	BNET_SendPacket(SID_AUTH_INFO, &tPacket, offsetof(decltype(tPacket), szCountry) + SStrLen(tPacket.szCountry) + 1);
	return TRUE;
}

//Bnclient.0x6FF08560
BOOL __stdcall BNSEND_AuthCheck()
{
#pragma pack(push, 1)
	struct
	{
		uint32_t nClientToken;
		uint32_t nExeVersion;
		uint32_t nExeHash;
		uint32_t nKeys;
		uint32_t bSpawn;
		uint8_t pData[2 * sizeof(BnCDKeyInfo) + 512];
	} tPacket;
#pragma pack(pop)

	char szExeInfo[256];

	memset(&tPacket, 0x00, sizeof(tPacket));

	const uint32_t nTime = (uint32_t)time(nullptr);
	gnBnClientToken += GetTickCount() + nTime;
	tPacket.nClientToken = gnBnClientToken;

	while (!BNDOWNLOAD_HasVersionFile())
	{
		if (BNRECV_IsDisconnected())
		{
			return FALSE;
		}

		Sleep(10);
	}

	if (!BNDOWNLOAD_CheckRevision(&tPacket.nExeVersion, &tPacket.nExeHash, szExeInfo))
	{
		BNMESSQUEUE_SetErrorIfNone(1);
		return FALSE;
	}

	tPacket.bSpawn = 0;
	GRID_LoadCDKeys();

	char* pCursor = nullptr;
	char* pEnd = nullptr;
	BnCDKeyInfo* pKeyInfos = (BnCDKeyInfo*)tPacket.pData;
	if (BNET_IsExpansion())
	{
		pCursor = (char*)&pKeyInfos[2];
		pCursor += SStrCopy(pCursor, szExeInfo, 512) + 1;
		tPacket.nKeys = 2;
		BNCDKEY_ComputeKeyInfo(&pKeyInfos[0], gnBnClientToken, 0);
		BNCDKEY_ComputeKeyInfo(&pKeyInfos[1], gnBnClientToken, 1);
		pEnd = (char*)&tPacket + sizeof(tPacket);
	}
	else
	{
		pCursor = (char*)&pKeyInfos[1];
		pCursor += SStrCopy(pCursor, szExeInfo, 512) + 1;
		tPacket.nKeys = 1;
		BNCDKEY_ComputeKeyInfo(&pKeyInfos[0], gnBnClientToken, 0);
		pEnd = (char*)&tPacket + sizeof(tPacket) - sizeof(BnCDKeyInfo);
	}

	SStrCopy(pCursor, GRID_GetCDKeyOwner(), pEnd - pCursor);
	GRID_UnloadCDKeys();

	BNET_SendPacket(SID_AUTH_CHECK, &tPacket, pCursor - (char*)&tPacket + SStrLen(pCursor) + 1);
	return TRUE;
}
