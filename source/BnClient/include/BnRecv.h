#pragma once

#include <Windows.h>

#include <cstdint>

// Battle.net message ids (SID_*) used by Diablo II
enum BnMessageId : uint8_t
{
	SID_NULL = 0x00,
	SID_STOPADV = 0x02,
	SID_CLIENTID = 0x05,
	SID_STARTVERSIONING = 0x06,
	SID_REPORTVERSION = 0x07,
	SID_GETADVLISTEX = 0x09,
	SID_ENTERCHAT = 0x0A,
	SID_GETCHANNELLIST = 0x0B,
	SID_JOINCHANNEL = 0x0C,
	SID_CHATCOMMAND = 0x0E,
	SID_CHATEVENT = 0x0F,
	SID_LEAVECHAT = 0x10,
	SID_LOCALEINFO = 0x12,
	SID_CHECKAD = 0x15,
	SID_CLICKAD = 0x16,
	SID_STARTADVEX3 = 0x1C,
	SID_LOGONCHALLENGEEX = 0x1D,
	SID_LEAVEGAME = 0x1F,
	SID_ANNOUNCEMENT = 0x20,
	SID_DISPLAYAD = 0x21,
	SID_NOTIFYJOIN = 0x22,
	SID_PING = 0x25,
	SID_READUSERDATA = 0x26,
	SID_WRITEUSERDATA = 0x27,
	SID_LOGONCHALLENGE = 0x28,
	SID_LOGONRESPONSE = 0x29,
	SID_CREATEACCOUNT = 0x2A,
	SID_CHANGEPASSWORD = 0x31,
	SID_GETFILETIME = 0x33,
	SID_LOGONRESPONSE2 = 0x3A,
	SID_CREATEACCOUNT2 = 0x3D,
	SID_LOGONREALMEX = 0x3E,
	SID_QUERYREALMS2 = 0x40,
	SID_QUERYADURL = 0x41,
	SID_CDKEY3 = 0x42,
	SID_NEWS_INFO = 0x46,
	SID_OPTIONALWORK = 0x4A,
	SID_EXTRAWORK = 0x4B,
	SID_REQUIREDWORK = 0x4C,
	SID_AUTH_INFO = 0x50,
	SID_AUTH_CHECK = 0x51,
	SID_AUTH_ACCOUNTCREATE = 0x52,
	SID_AUTH_ACCOUNTLOGON = 0x53,
	SID_AUTH_ACCOUNTLOGONPROOF = 0x54,
	SID_AUTH_ACCOUNTCHANGE = 0x55,
	SID_AUTH_ACCOUNTCHANGEPROOF = 0x56,
	SID_AUTH_ACCOUNTUPGRADE = 0x57,
	SID_AUTH_ACCOUNTUPGRADEPROOF = 0x58,
	SID_SETEMAIL = 0x59,
	SID_RESETPASSWORD = 0x5A,
	SID_CHANGEEMAIL = 0x5B,
	SID_SWITCHPRODUCT = 0x5C,
	SID_SYSTEMINFO = 0x5D,

	BN_MESSAGE_COUNT = 0x5E,
};

using BnMessageHandler = BOOL(__fastcall*)(const uint8_t* pData, uint32_t nSize);

extern int32_t gnBnLogonResult;
extern int32_t gnBnChangePasswordResult;
extern int32_t gnBnCreateAccountResult;
extern int32_t gnBnCDKeyResult;
extern int32_t gaBnMessageResult[BN_MESSAGE_COUNT];
extern int32_t gaBnMessageReceived[BN_MESSAGE_COUNT];
extern char gszBnCDKeyOwner[256];
extern BOOL gbBnDisconnected;

void __fastcall BNRECV_DispatchMessage(uint8_t nMessageId, const uint8_t* pData, uint32_t nSize);
void __stdcall BNRECV_SetDisconnected();
BOOL __stdcall BNRECV_IsDisconnected();
int32_t __stdcall BNRECV_GetCreateAccountResult();
int32_t __stdcall BNRECV_GetChangePasswordResult();
BOOL __stdcall BNRECV_ResetAllMessages();
BOOL __fastcall BNRECV_WaitForMessage(uint8_t nMessageId);
BOOL __fastcall BNRECV_WasMessageReceived(uint8_t nMessageId);
void __fastcall BNRECV_ResetMessage(uint8_t nMessageId);
int32_t __fastcall BNRECV_GetMessageResult(uint8_t nMessageId);
