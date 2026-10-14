// Made up filename

#include "BnRecv.h"

#include <Fog.h>
#include <Storm.h>

#include "BnConnect.h"
#include "BnDownload.h"
#include "BnLog.h"
#include "BnMessQueue.h"
#include "BNNews.h"
#include "BnSend.h"
#include "BnSRP.h"


int32_t gnBnChangePasswordResult;
int32_t gaBnMessageResult[BN_MESSAGE_COUNT];
int32_t gnBnCDKeyResult;
int32_t gnBnCreateAccountResult;
int32_t gaBnMessageReceived[BN_MESSAGE_COUNT];
char gszBnCDKeyOwner[256];
BOOL gbBnDisconnected;
uint32_t gnBnLastAdId;

int32_t gnBnLogonResult = 0xFF;


//Bnclient.0x6FF022D0
void __stdcall BNRECV_SetDisconnected()
{
	gbBnDisconnected = TRUE;
}

//Bnclient.0x6FF022E0
BOOL __stdcall BNRECV_IsDisconnected()
{
	return gbBnDisconnected;
}

//Bnclient.0x6FF022F0
int32_t __stdcall BNRECV_GetCreateAccountResult()
{
	return gnBnCreateAccountResult;
}

//Bnclient.0x6FF02300
int32_t __stdcall BNRECV_GetChangePasswordResult()
{
	return gnBnChangePasswordResult;
}

//Bnclient.0x6FF02310
BOOL __stdcall BNRECV_ResetAllMessages()
{
	memset(gaBnMessageResult, 0x00, sizeof(gaBnMessageResult));
	memset(gaBnMessageReceived, 0x00, sizeof(gaBnMessageReceived));
	gnBnLogonResult = 0xFF;
	gbBnDisconnected = FALSE;
	BNMESSQUEUE_SetError(0);
	return TRUE;
}

//Bnclient.0x6FF02350
BOOL __fastcall BNRECV_WaitForMessage(uint8_t nMessageId)
{
	const DWORD dwStartTick = GetTickCount();
	while (!gaBnMessageReceived[nMessageId])
	{
		if (gbBnDisconnected)
		{
			BNMESSQUEUE_SetErrorIfNone(18);
			return FALSE;
		}

		if (GetTickCount() - dwStartTick > 45000)
		{
			BNMESSQUEUE_SetErrorIfNone(17);
			return FALSE;
		}

		Sleep(10);
	}

	return TRUE;
}

//Bnclient.0x6FF023D0
BOOL __fastcall BNRECV_WasMessageReceived(uint8_t nMessageId)
{
	return gaBnMessageReceived[nMessageId];
}

//Bnclient.0x6FF023E0
void __fastcall BNRECV_ResetMessage(uint8_t nMessageId)
{
	gaBnMessageReceived[nMessageId] = 0;
	gaBnMessageResult[nMessageId] = 0;
}

//Bnclient.0x6FF02400
int32_t __fastcall BNRECV_GetMessageResult(uint8_t nMessageId)
{
	return gaBnMessageResult[nMessageId];
}

//Bnclient.0x6FF02410
static BOOL __fastcall BNRECV_IgnoreMessage(const uint8_t* pData, uint32_t nSize)
{
	return TRUE;
}

//Bnclient.0x6FF02420
static BOOL __fastcall BNRECV_CreateAccount(const uint8_t* pData, uint32_t nSize)
{
	gaBnMessageResult[SID_CREATEACCOUNT] = *(const int32_t*)pData;
	return TRUE;
}

//Bnclient.0x6FF02430
static BOOL __fastcall BNRECV_CreateAccount2(const uint8_t* pData, uint32_t nSize)
{
	gnBnCreateAccountResult = *(const int32_t*)pData;
	gaBnMessageResult[SID_CREATEACCOUNT2] = 1;
	return TRUE;
}

//Bnclient.0x6FF02450
static BOOL __fastcall BNRECV_ChangePassword(const uint8_t* pData, uint32_t nSize)
{
	gaBnMessageResult[SID_CHANGEPASSWORD] = 1;
	gnBnChangePasswordResult = *(const int32_t*)pData;
	if (!gnBnChangePasswordResult)
	{
		BNMESSQUEUE_SetErrorIfNone(14);
	}
	return TRUE;
}

//Bnclient.0x6FF02480
static BOOL __fastcall BNRECV_ClientId(const uint8_t* pData, uint32_t nSize)
{
	if (!pData || nSize < 16)
	{
		BNLOG_Printf("ERROR BDClientId: invalid response");
		return FALSE;
	}

	const uint32_t* pValues = (const uint32_t*)pData;
	SRegSaveValue("Configuration", "Registration Version", 2, pValues[0]);
	SRegSaveValue("Configuration", "Registration Authority", 2, pValues[1]);
	SRegSaveValue("Configuration", "Client ID", 2, pValues[2]);
	SRegSaveValue("Configuration", "Client Token", 2, pValues[3]);

	BNLOG_Command(BNLOG_COMMAND_INDENT, 4);
	BNLOG_Printf("client acknowledged");
	BNLOG_Command(BNLOG_COMMAND_INDENT, -4);
	return TRUE;
}

//Bnclient.0x6FF02520
static BOOL __fastcall BNRECV_LogonChallenge(const uint8_t* pData, uint32_t nSize)
{
	BNSEND_SetServerToken(*(const uint32_t*)pData);
	return TRUE;
}

//Bnclient.0x6FF02530
static BOOL __fastcall BNRECV_StartAdvEx3(const uint8_t* pData, uint32_t nSize)
{
	if (*(const int32_t*)pData == 0)
	{
		gaBnMessageResult[SID_STARTADVEX3] = 1;
	}
	return TRUE;
}

//Bnclient.0x6FF02540
static BOOL __fastcall BNRECV_LogonChallengeEx(const uint8_t* pData, uint32_t nSize)
{
	BNSEND_SetServerToken(((const uint32_t*)pData)[1]);

	BNLOG_Command(BNLOG_COMMAND_INDENT, 4);
	BNLOG_Printf("logon acknowledged");
	BNLOG_Command(BNLOG_COMMAND_INDENT, -4);
	return TRUE;
}

//Bnclient.0x6FF02570
static BOOL __fastcall BNRECV_LogonResponse(const uint8_t* pData, uint32_t nSize)
{
	gnBnLogonResult = *(const int32_t*)pData == 0;
	return TRUE;
}

//Bnclient.0x6FF02590
static BOOL __fastcall BNRECV_LogonResponse2(const uint8_t* pData, uint32_t nSize)
{
	gnBnLogonResult = *(const int32_t*)pData;
	switch (gnBnLogonResult)
	{
	case 0:
		return TRUE;

	case 1:
		BNMESSQUEUE_SetErrorIfNone(13);
		return TRUE;

	case 2:
		BNMESSQUEUE_SetErrorIfNone(14);
		return TRUE;

	case 3:
		BNMESSQUEUE_SetErrorIfNone(15);
		return TRUE;

	default:
		BNMESSQUEUE_SetErrorIfNone(18);
		return TRUE;
	}
}

//Bnclient.0x6FF02600
static BOOL __fastcall BNRECV_ReportVersion(const uint8_t* pData, uint32_t nSize)
{
	const uint32_t nResult = *(const uint32_t*)pData;
	if (nResult > 0 && nResult <= 3)
	{
		BNSEND_SystemInfo();
	}

	SRegSaveData("Patch", "Patches", 0x82, (BYTE*)"", 1);

	if (nResult == 1)
	{
		const char* szPatchFile = (const char*)&pData[4];
		const uint32_t nPatchFileSize = nSize - 4;
		BNDOWNLOAD_SetPatchFiles(szPatchFile, nPatchFileSize);
		SRegSaveData("Patch", "Patches", 0x82, (BYTE*)szPatchFile, nPatchFileSize);

		FILETIME tFileTime = {};
		BNDOWNLOAD_RequestFile(BNDOWNLOAD_REQUEST_PATCH, BNDOWNLOAD_FLAG_DISK, 0, 0, &tFileTime, szPatchFile, nullptr);

		gaBnMessageResult[SID_REPORTVERSION] = 0;
		BNLOG_Printf("downloading upgrade");
		return TRUE;
	}

	if (nResult == 2)
	{
		gaBnMessageResult[SID_REPORTVERSION] = 1;
		BNLOG_Printf("user has latest version");
		return TRUE;
	}

	BNMESSQUEUE_SetErrorIfNone(1);
	gaBnMessageResult[SID_REPORTVERSION] = 0;
	if (nResult == 3)
	{
		BNLOG_Printf("User must reinstall and patch");
	}
	else
	{
		BNLOG_Printf("user has unknown version");
	}
	return TRUE;
}

//Bnclient.0x6FF026D0
static BOOL __fastcall BNRECV_StartVersioning(const uint8_t* pData, uint32_t nSize)
{
	const char* szMpqFileName = (const char*)&pData[8];
	if (strlen(szMpqFileName) + 1 + 8 < nSize)
	{
		BNDOWNLOAD_SetVersionFormula(&szMpqFileName[strlen(szMpqFileName) + 1]);
	}

	BNDOWNLOAD_RequestFile(BNDOWNLOAD_REQUEST_VERSIONING, BNDOWNLOAD_FLAG_CACHE | BNDOWNLOAD_FLAG_DISK, 0, 0, (FILETIME*)pData, szMpqFileName, nullptr);
	return TRUE;
}

//Bnclient.0x6FF02720
static BOOL __fastcall BNRECV_Ping(const uint8_t* pData, uint32_t nSize)
{
	BNET_SendPacket(SID_PING, pData, nSize);
	return TRUE;
}

//Bnclient.0x6FF02740
static BOOL __fastcall BNRECV_CDKey3(const uint8_t* pData, uint32_t nSize)
{
	gszBnCDKeyOwner[0] = '\0';
	gnBnCDKeyResult = *(const int32_t*)pData;
	gaBnMessageResult[SID_CDKEY3] = 0;

	switch (gnBnCDKeyResult)
	{
	case 0:
		gaBnMessageResult[SID_CDKEY3] = 1;
		return TRUE;

	case 3:
		BNMESSQUEUE_SetError(3);
		return TRUE;

	case 4:
		BNMESSQUEUE_SetError(6);
		SStrCopy(gszBnCDKeyOwner, (const char*)&pData[4], sizeof(gszBnCDKeyOwner));
		BNMESSQUEUE_SetErrorText(gszBnCDKeyOwner);
		return TRUE;

	case 5:
		BNMESSQUEUE_SetError(4);
		return TRUE;

	case 6:
		BNMESSQUEUE_SetError(5);
		return TRUE;

	default:
		return TRUE;
	}
}

//Bnclient.0x6FF02800
static BOOL __fastcall BNRECV_ServerList(const uint8_t* pData, uint32_t nSize)
{
	SRegSaveString("Configuration", "Server List", 2, (const char*)&pData[4]);
	return TRUE;
}

//Bnclient.0x6FF02820
static BOOL __fastcall BNRECV_GetChannelList(const uint8_t* pData, uint32_t nSize)
{
	BNSEND_StoreChannelList(pData, nSize);
	return TRUE;
}

//Bnclient.0x6FF02830
static BOOL __fastcall BNRECV_GetAdvListEx(const uint8_t* pData, uint32_t nSize)
{
	BNSEND_StoreGameList(pData, nSize);
	return TRUE;
}

//Bnclient.0x6FF02840
static BOOL __fastcall BNRECV_OptionalWorkAlt(const uint8_t* pData, uint32_t nSize)
{
	if (pData && *pData && nSize && nSize != -1)
	{
		BNDOWNLOAD_RequestFileTime((const char*)pData, BNDOWNLOAD_REQUEST_EXTRAWORK);
	}
	return TRUE;
}

//Bnclient.0x6FF02870
static BOOL __fastcall BNRECV_RequiredWorkAlt(const uint8_t* pData, uint32_t nSize)
{
	if (pData && *pData && nSize && nSize != -1)
	{
		BNDOWNLOAD_RequestFileTime((const char*)pData, BNDOWNLOAD_REQUEST_REQUIREDWORK);
	}
	return TRUE;
}

//Bnclient.0x6FF028A0
static BOOL __fastcall BNRECV_EnterChat(const uint8_t* pData, uint32_t nSize)
{
	BNMESSQUEUE_PushString(2, (const char*)pData);
	BNET_SetUniqueName((const char*)pData);
	return TRUE;
}

//Bnclient.0x6FF028C0
static BOOL __fastcall BNRECV_GetFileTime(const uint8_t* pData, uint32_t nSize)
{
#pragma pack(push, 1)
	struct BnGetFileTimeResponse
	{
		uint32_t nRequestId;
		uint32_t nUnknown;
		FILETIME tFileTime;
		char szFileName[1];
	};
#pragma pack(pop)

	const BnGetFileTimeResponse* pResponse = (const BnGetFileTimeResponse*)pData;

	uint32_t nFlags = BNDOWNLOAD_FLAG_MEMORY;
	if (pResponse->nRequestId == BNDOWNLOAD_REQUEST_EXTRAWORK || pResponse->nRequestId == BNDOWNLOAD_REQUEST_REQUIREDWORK)
	{
		nFlags = BNDOWNLOAD_FLAG_DISK;
	}

	BNDOWNLOAD_RequestFile(pResponse->nRequestId, nFlags | BNDOWNLOAD_FLAG_CACHE, 0, 0, (FILETIME*)&pResponse->tFileTime, pResponse->szFileName, nullptr);
	return TRUE;
}

//Bnclient.0x6FF02900
static BOOL __fastcall BNRECV_CheckAd(const uint8_t* pData, uint32_t nSize)
{
#pragma pack(push, 1)
	struct BnCheckAdResponse
	{
		uint32_t nAdId;
		uint32_t nFileExtension;
		FILETIME tFileTime;
		char szFileName[1];
	};
#pragma pack(pop)

	const BnCheckAdResponse* pResponse = (const BnCheckAdResponse*)pData;
	const uint32_t nAdId = pResponse->nAdId;
	if (nSize < 17 || nAdId == gnBnLastAdId)
	{
		return TRUE;
	}

	gnBnLastAdId = nAdId;

	const char* szFileName = pResponse->szFileName;
	const char* szLinkUrl = &szFileName[strlen(szFileName) + 1];
	if (*szFileName && *szLinkUrl)
	{
		BNDOWNLOAD_RequestFile(BNDOWNLOAD_REQUEST_AD, BNDOWNLOAD_FLAG_MEMORY | BNDOWNLOAD_FLAG_CACHE, nAdId, pResponse->nFileExtension, (FILETIME*)&pResponse->tFileTime, szFileName, szLinkUrl);
	}
	return TRUE;
}

//Bnclient.0x6FF02960
static BOOL __fastcall BNRECV_QueryRealms2(const uint8_t* pData, uint32_t nSize)
{
	BNSEND_StoreRealmList(pData, nSize);
	return TRUE;
}

//Bnclient.0x6FF02970
static BOOL __fastcall BNRECV_QueryAdUrl(const uint8_t* pData, uint32_t nSize)
{
	BNSEND_StoreAdUrl(pData, nSize);
	return TRUE;
}

//Bnclient.0x6FF02980
static BOOL __fastcall BNRECV_LogonRealmEx(const uint8_t* pData, uint32_t nSize)
{
	BNSEND_StoreRealmLogonInformation(pData, nSize);
	return TRUE;
}

//Bnclient.0x6FF02990
static BOOL __fastcall BNRECV_ReadUserData(const uint8_t* pData, uint32_t nSize)
{
	BNSEND_StoreUserData(pData, nSize);
	return TRUE;
}

//Bnclient.0x6FF029A0
static BOOL __fastcall BNRECV_NewsInfo(const uint8_t* pData, uint32_t nSize)
{
	return BNNEWS_StoreNewsInfo(pData, nSize);
}

//Bnclient.0x6FF029B0
static BOOL __fastcall BNRECV_AuthInfo(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 22 || pData[nSize - 1] != '\0')
	{
		BNET_DebugTrace("INVALID: AuthInfo");
		return FALSE;
	}

	int nStrings = 0;
	for (uint32_t i = 20; i < nSize - 1; ++i)
	{
		if (pData[i] == '\0')
		{
			++nStrings;
		}
	}

	if (nStrings != 1)
	{
		BNET_DebugTrace("INVALID: AuthInfo");
		return FALSE;
	}

	const uint32_t* pValues = (const uint32_t*)pData;
	FILETIME tFileTime;
	tFileTime.dwLowDateTime = pValues[3];
	tFileTime.dwHighDateTime = pValues[4];

	const uint32_t nServerToken = pValues[1];
	const uint32_t nLogonType = pValues[0];
	const char* szMpqFileName = (const char*)&pData[20];
	const char* szFormula = &szMpqFileName[SStrLen(szMpqFileName) + 1];

	BNSEND_SetServerToken(nServerToken);
	BNSEND_SetLogonType(nLogonType);
	BNDOWNLOAD_SetVersionFormula(szFormula);
	BNDOWNLOAD_SetVersionFile("");
	BNDOWNLOAD_RequestFile(BNDOWNLOAD_REQUEST_VERSIONING, BNDOWNLOAD_FLAG_CACHE | BNDOWNLOAD_FLAG_DISK, 0, 0, &tFileTime, szMpqFileName, nullptr);
	return TRUE;
}

//Bnclient.0x6FF02A60
static BOOL __fastcall BNRECV_AuthCheck(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 5 || pData[nSize - 1] != '\0')
	{
		BNET_DebugTrace("INVALID: AuthCheck");
		return FALSE;
	}

	int nStrings = 0;
	for (uint32_t i = 4; i < nSize - 1; ++i)
	{
		if (pData[i] == '\0')
		{
			++nStrings;
		}
	}

	if (nStrings != 0)
	{
		BNET_DebugTrace("INVALID: AuthCheck");
		return FALSE;
	}

	const uint32_t nResult = *(const uint32_t*)pData;
	const char* szInfo = (const char*)&pData[4];
	const uint32_t nCode = nResult & 0xFF0F;
	if (nCode == 0x000 || nCode == 0x100 || nCode == 0x102)
	{
		BNSEND_SystemInfo();
	}

	gszBnCDKeyOwner[0] = '\0';
	gaBnMessageResult[SID_CDKEY3] = 0;
	SRegSaveData("Patch", "Patches", 0x82, (BYTE*)"", 1);

	const uint32_t nKeyIndex = (nResult >> 4) & 0xF;
	switch (nCode)
	{
	case 0x000:
		gaBnMessageResult[SID_CDKEY3] = 1;
		gaBnMessageResult[SID_AUTH_CHECK] = 1;
		BNET_DebugTrace("User has latest version and a valid cdkey");
		return TRUE;

	case 0x100:
	{
		char szPatchFiles[256];
		FILETIME tFileTime;

		uint32_t nLength = SStrCopy(szPatchFiles, szInfo, sizeof(szPatchFiles) - 2) + 1;
		szPatchFiles[nLength] = '\0';
		++nLength;

		BNDOWNLOAD_SetPatchFiles(szPatchFiles, nLength);
		SRegSaveData("Patch", "Patches", 0x82, (BYTE*)szPatchFiles, nLength);

		tFileTime.dwLowDateTime = 0;
		tFileTime.dwHighDateTime = 0;
		BNDOWNLOAD_RequestFile(BNDOWNLOAD_REQUEST_PATCH, BNDOWNLOAD_FLAG_DISK, 0, 0, &tFileTime, szPatchFiles, nullptr);

		gaBnMessageResult[SID_AUTH_CHECK] = 0;
		BNET_DebugTrace("Downloading Upgrade");
		return TRUE;
	}

	case 0x101:
		BNMESSQUEUE_SetErrorIfNone(1);
		gaBnMessageResult[SID_AUTH_CHECK] = 0;
		BNET_DebugTrace("User has unknown version");
		return TRUE;

	case 0x102:
		BNMESSQUEUE_SetErrorIfNone(1);
		gaBnMessageResult[SID_AUTH_CHECK] = 0;
		BNET_DebugTrace("User must revert to an older version");
		return TRUE;

	case 0x200:
		BNMESSQUEUE_SetError(nKeyIndex != 0 ? 7 : 3);
		BNET_DebugTrace("User has an invalid cdkey (%d)", nKeyIndex);
		return TRUE;

	case 0x201:
		BNMESSQUEUE_SetError(nKeyIndex != 0 ? 10 : 6);
		SStrCopy(gszBnCDKeyOwner, szInfo, sizeof(gszBnCDKeyOwner));
		BNMESSQUEUE_SetErrorText(gszBnCDKeyOwner);
		BNET_DebugTrace("CD Key is in use by %s (%d)", gszBnCDKeyOwner, nKeyIndex);
		return TRUE;

	case 0x202:
		BNMESSQUEUE_SetError(nKeyIndex != 0 ? 8 : 4);
		BNET_DebugTrace("CD Key is disabled (%d)", nKeyIndex);
		return TRUE;

	case 0x203:
		BNMESSQUEUE_SetError(nKeyIndex != 0 ? 9 : 5);
		BNET_DebugTrace("CD Key is for another product (%d)", nKeyIndex);
		return TRUE;

	default:
		return TRUE;
	}
}

//Bnclient.0x6FF02D60
static BOOL __fastcall BNRECV_AuthAccountCreate(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 4)
	{
		BNET_DebugTrace("INVALID: AuthAccountCreate");
		return FALSE;
	}

	switch (*(const uint32_t*)pData)
	{
	case 0:
		gnBnCreateAccountResult = 0;
		BNET_DebugTrace("Account created");
		break;

	case 4:
		gnBnCreateAccountResult = 4;
		BNET_DebugTrace("Create failed: Name is in use");
		break;

	case 7:
		gnBnCreateAccountResult = 1;
		BNET_DebugTrace("Create failed: Name blank");
		break;

	case 8:
		gnBnCreateAccountResult = 2;
		BNET_DebugTrace("Create failed: Name contains bad characters");
		break;

	case 9:
		gnBnCreateAccountResult = 3;
		BNET_DebugTrace("Create failed: Name contains bad words");
		break;

	case 10:
		gnBnCreateAccountResult = 6;
		BNET_DebugTrace("Create failed: Name doesn't have alpha characters");
		break;

	case 11:
		gnBnCreateAccountResult = 7;
		BNET_DebugTrace("Create failed: Name contains adjacent punctuation");
		break;

	case 12:
		gnBnCreateAccountResult = 8;
		BNET_DebugTrace("Create failed: Name contains too much punctuation");
		break;

	default:
		gnBnCreateAccountResult = 4;
		BNET_DebugTrace("Create failed: unknown result");
		break;
	}

	gaBnMessageResult[SID_AUTH_ACCOUNTCREATE] = 1;
	return TRUE;
}

//Bnclient.0x6FF02E60
static BOOL __fastcall BNRECV_AuthAccountLogon(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 68)
	{
		BNET_DebugTrace("INVALID: AuthAccountLogon");
		return FALSE;
	}

	switch (*(const uint32_t*)pData)
	{
	case 0:
		BNET_DebugTrace("Logon requires proof");
		return BNSRP_HandleLogonChallenge(&pData[4], &pData[36]);

	case 1:
		BNET_DebugTrace("Logon failed: Account unknown");
		BNMESSQUEUE_SetErrorIfNone(13);
		gnBnLogonResult = 1;
		return TRUE;

	case 5:
		BNET_DebugTrace("Logon requires upgrade");
		if (!BNSRP_RequestUpgrade(TRUE))
		{
			BNMESSQUEUE_SetErrorIfNone(18);
			return FALSE;
		}
		return TRUE;

	default:
		BNET_DebugTrace("Logon failed: Unknown result");
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;
	}
}

//Bnclient.0x6FF02F10
static BOOL __fastcall BNRECV_AuthAccountLogonProof(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 24)
	{
		BNET_DebugTrace("INVALID: AuthAccountLogonProof");
		return FALSE;
	}

	switch (*(const uint32_t*)pData)
	{
	case 0:
		if (BNSRP_VerifyServerProof(&pData[4]))
		{
			BNET_DebugTrace("Logon Proof success");
			gnBnLogonResult = 0;
			return TRUE;
		}

		BNET_DebugTrace("Logon Proof failed: Server didn't know our password but told us it did!");
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;

	case 2:
		BNET_DebugTrace("Logon Proof failed: Invalid password");
		BNMESSQUEUE_SetErrorIfNone(14);
		gnBnLogonResult = 2;
		return TRUE;

	default:
		BNET_DebugTrace("Logon Proof failed: Unknown result");
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;
	}
}

//Bnclient.0x6FF02FB0
static BOOL __fastcall BNRECV_AuthAccountChange(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 68)
	{
		BNET_DebugTrace("INVALID: AuthAccountChange");
		return FALSE;
	}

	switch (*(const uint32_t*)pData)
	{
	case 0:
		BNET_DebugTrace("Change requires proof");
		return BNSRP_HandleChangeChallenge(&pData[4], &pData[36]);

	case 1:
		BNET_DebugTrace("Change failed: Account unknown");
		BNMESSQUEUE_SetErrorIfNone(13);
		return TRUE;

	case 5:
		BNET_DebugTrace("Change requires upgrade");
		return BNSRP_RequestUpgrade(FALSE);

	default:
		BNET_DebugTrace("Change failed: Unknown result");
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;
	}
}

//Bnclient.0x6FF03040
static BOOL __fastcall BNRECV_AuthAccountChangeProof(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 24)
	{
		BNET_DebugTrace("INVALID: AuthAccountChangeProof");
		return FALSE;
	}

	const uint32_t nResult = *(const uint32_t*)pData;
	BNSRP_ClearPasswords();

	switch (nResult)
	{
	case 0:
		if (BNSRP_VerifyServerProof(&pData[4]))
		{
			BNET_DebugTrace("Change Proof success");
			gaBnMessageResult[SID_AUTH_ACCOUNTCHANGE] = 1;
			return TRUE;
		}

		BNET_DebugTrace("Change Proof failed: Server didn't know our password but told us it did!");
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;

	case 2:
		BNET_DebugTrace("Change Proof failed: Invalid password");
		gaBnMessageResult[SID_AUTH_ACCOUNTCHANGE] = 1;
		BNMESSQUEUE_SetErrorIfNone(14);
		return TRUE;

	default:
		BNET_DebugTrace("Change Proof failed: Unknown result");
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;
	}
}

//Bnclient.0x6FF030F0
static BOOL __fastcall BNRECV_AuthAccountUpgrade(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 8)
	{
		BNET_DebugTrace("INVALID: AuthAccountUpgrade");
		return FALSE;
	}

	const uint32_t* pValues = (const uint32_t*)pData;
	const uint32_t nServerToken = pValues[1];
	if (pValues[0] != 0)
	{
		BNET_DebugTrace("Upgrade Failed: Unknown result");
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;
	}

	BNET_DebugTrace("Upgrade requires proof");
	BNSRP_SendUpgradeProof(nServerToken);
	return TRUE;
}

//Bnclient.0x6FF03150
static BOOL __fastcall BNRECV_AuthAccountUpgradeProof(const uint8_t* pData, uint32_t nSize)
{
	if (nSize < 4)
	{
		BNET_DebugTrace("INVALID: AuthAccountUpgradeProof");
		return FALSE;
	}

	switch (*(const uint32_t*)pData)
	{
	case 0:
		if (BNSRP_IsUpgradingLogon())
		{
			BNET_DebugTrace("Upgrade Proof success, logging in");
			return BNSRP_SendLogon();
		}

		BNET_DebugTrace("Upgrade Proof success, password changed");
		BNSRP_ClearPasswords();
		gnBnChangePasswordResult = 0;
		gaBnMessageResult[SID_AUTH_ACCOUNTCHANGE] = 1;
		return TRUE;

	case 2:
		if (BNSRP_IsUpgradingLogon())
		{
			BNET_DebugTrace("Upgrade Proof Failed: Invalid password during logon");
			BNSRP_ClearPasswords();
			gnBnLogonResult = 2;
			BNMESSQUEUE_SetErrorIfNone(14);
			return TRUE;
		}

		BNET_DebugTrace("Upgrade Proof Failed: Invalid password during change");
		BNSRP_ClearPasswords();
		gnBnChangePasswordResult = 2;
		gaBnMessageResult[SID_AUTH_ACCOUNTCHANGE] = 1;
		BNMESSQUEUE_SetErrorIfNone(14);
		return TRUE;

	default:
		BNET_DebugTrace("Upgrade Proof failed: Unknown Result");
		BNMESSQUEUE_SetErrorIfNone(18);
		return FALSE;
	}
}

//Bnclient.0x6FF03250
static BOOL __fastcall BNRECV_SetEmail(const uint8_t* pData, uint32_t nSize)
{
	BNET_SetEmailRequested(TRUE);
	return TRUE;
}

//Bnclient.0x6FF03260
static BOOL __fastcall BNRECV_OptionalWork(const uint8_t* pData, uint32_t nSize)
{
	if (pData && *pData && nSize)
	{
		BNDOWNLOAD_RequestFileTime((const char*)pData, BNDOWNLOAD_REQUEST_EXTRAWORK);
	}
	return TRUE;
}

//Bnclient.0x6FF03280
static BOOL __fastcall BNRECV_RequiredWork(const uint8_t* pData, uint32_t nSize)
{
	if (pData && *pData && nSize)
	{
		BNDOWNLOAD_RequestFileTime((const char*)pData, BNDOWNLOAD_REQUEST_REQUIREDWORK);
	}
	return TRUE;
}

//Bnclient.0x6FF18358
static const BnMessageHandler gpfBnMessageHandlers[BN_MESSAGE_COUNT + 2] =
{
	BNRECV_IgnoreMessage,				// 0x00 SID_NULL
	nullptr,							// 0x01
	nullptr,							// 0x02
	nullptr,							// 0x03
	BNRECV_ServerList,					// 0x04 SID_SERVERLIST
	BNRECV_ClientId,					// 0x05 SID_CLIENTID
	BNRECV_StartVersioning,				// 0x06 SID_STARTVERSIONING
	BNRECV_ReportVersion,				// 0x07 SID_REPORTVERSION
	nullptr,							// 0x08
	BNRECV_GetAdvListEx,				// 0x09 SID_GETADVLISTEX
	BNRECV_EnterChat,					// 0x0A SID_ENTERCHAT
	BNRECV_GetChannelList,				// 0x0B SID_GETCHANNELLIST
	nullptr,							// 0x0C
	nullptr,							// 0x0D
	nullptr,							// 0x0E
	BNET_HandleChatEvent,				// 0x0F SID_CHATEVENT
	nullptr,							// 0x10
	nullptr,							// 0x11
	nullptr,							// 0x12
	nullptr,							// 0x13
	nullptr,							// 0x14
	BNRECV_CheckAd,						// 0x15 SID_CHECKAD
	nullptr,							// 0x16
	nullptr,							// 0x17
	nullptr,							// 0x18
	nullptr,							// 0x19
	nullptr,							// 0x1A
	nullptr,							// 0x1B
	BNRECV_StartAdvEx3,					// 0x1C SID_STARTADVEX3
	BNRECV_LogonChallengeEx,			// 0x1D SID_LOGONCHALLENGEEX
	nullptr,							// 0x1E
	nullptr,							// 0x1F
	BNRECV_IgnoreMessage,				// 0x20 SID_ANNOUNCEMENT
	nullptr,							// 0x21
	nullptr,							// 0x22
	nullptr,							// 0x23
	nullptr,							// 0x24
	BNRECV_Ping,						// 0x25 SID_PING
	BNRECV_ReadUserData,				// 0x26 SID_READUSERDATA
	nullptr,							// 0x27
	BNRECV_LogonChallenge,				// 0x28 SID_LOGONCHALLENGE
	BNRECV_LogonResponse,				// 0x29 SID_LOGONRESPONSE
	BNRECV_CreateAccount,				// 0x2A SID_CREATEACCOUNT
	nullptr,							// 0x2B
	nullptr,							// 0x2C
	nullptr,							// 0x2D
	nullptr,							// 0x2E
	nullptr,							// 0x2F
	nullptr,							// 0x30
	BNRECV_ChangePassword,				// 0x31 SID_CHANGEPASSWORD
	nullptr,							// 0x32
	BNRECV_GetFileTime,					// 0x33 SID_GETFILETIME
	nullptr,							// 0x34
	nullptr,							// 0x35
	nullptr,							// 0x36
	nullptr,							// 0x37
	nullptr,							// 0x38
	nullptr,							// 0x39
	BNRECV_LogonResponse2,				// 0x3A SID_LOGONRESPONSE2
	nullptr,							// 0x3B
	nullptr,							// 0x3C
	BNRECV_CreateAccount2,				// 0x3D SID_CREATEACCOUNT2
	BNRECV_LogonRealmEx,				// 0x3E SID_LOGONREALMEX
	nullptr,							// 0x3F
	BNRECV_QueryRealms2,				// 0x40 SID_QUERYREALMS2
	BNRECV_QueryAdUrl,					// 0x41 SID_QUERYADURL
	BNRECV_CDKey3,						// 0x42 SID_CDKEY3
	nullptr,							// 0x43
	nullptr,							// 0x44
	nullptr,							// 0x45
	BNRECV_NewsInfo,					// 0x46 SID_NEWS_INFO
	nullptr,							// 0x47
	nullptr,							// 0x48
	nullptr,							// 0x49
	BNRECV_OptionalWork,					// 0x4A SID_OPTIONALWORK
	nullptr,							// 0x4B
	BNRECV_RequiredWork,				// 0x4C SID_REQUIREDWORK
	nullptr,							// 0x4D
	nullptr,							// 0x4E
	nullptr,							// 0x4F
	BNRECV_AuthInfo,					// 0x50 SID_AUTH_INFO
	BNRECV_AuthCheck,					// 0x51 SID_AUTH_CHECK
	BNRECV_AuthAccountCreate,			// 0x52 SID_AUTH_ACCOUNTCREATE
	BNRECV_AuthAccountLogon,			// 0x53 SID_AUTH_ACCOUNTLOGON
	BNRECV_AuthAccountLogonProof,		// 0x54 SID_AUTH_ACCOUNTLOGONPROOF
	BNRECV_AuthAccountChange,			// 0x55 SID_AUTH_ACCOUNTCHANGE
	BNRECV_AuthAccountChangeProof,		// 0x56 SID_AUTH_ACCOUNTCHANGEPROOF
	BNRECV_AuthAccountUpgrade,			// 0x57 SID_AUTH_ACCOUNTUPGRADE
	BNRECV_AuthAccountUpgradeProof,		// 0x58 SID_AUTH_ACCOUNTUPGRADEPROOF
	BNRECV_SetEmail,					// 0x59 SID_SETEMAIL
	nullptr,							// 0x5A
	nullptr,							// 0x5B
	nullptr,							// 0x5C
	nullptr,							// 0x5D
	BNRECV_RequiredWorkAlt,				// 0x5E (unreachable)
	BNRECV_OptionalWorkAlt,				// 0x5F (unreachable)
};

//Bnclient.0x6FF032A0
void __fastcall BNRECV_DispatchMessage(uint8_t nMessageId, const uint8_t* pData, uint32_t nSize)
{
	if (nMessageId >= BN_MESSAGE_COUNT)
	{
		return;
	}

	if (const BnMessageHandler pfHandler = gpfBnMessageHandlers[nMessageId])
	{
		pfHandler(pData, nSize);
	}

	gaBnMessageReceived[nMessageId] = 1;
}
