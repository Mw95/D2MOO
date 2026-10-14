// Made up filename

#include <BnClient.h>

#include "BNetGW.h"
#include "BnConnect.h"
#include "BnDownload.h"
#include "BnLog.h"
#include "BnMessQueue.h"
#include "BNNews.h"
#include "BnSend.h"


extern "C" BNCLIENT_DLL_DECL BnClientInterface* __cdecl QueryInterface();

//Bnclient.0x6FF19E70
static BnClientInterface gtBnClientInterface =
{
	BNLOG_SetUnused,
	BNET_OpenBNetConnection,
	BNET_Logon,
	BNET_GetLogonInfo,
	BNET_CloseBNetConnection,
	BNSEND_ChatCommand,
	BNET_GetUniqueName,
	BNSEND_JoinChannel,
	BNSEND_GetChannelList,
	BNMESSQUEUE_Read,
	BNMESSQUEUE_GetLastError,
	BNDOWNLOAD_RequestFileTime,
	BNSEND_CheckAd,
	BNSEND_StartAdvEx3,
	BNSEND_GetGameList,
	BNSEND_NotifyJoin,
	BNSEND_QueryRealms,
	BNSEND_LogonRealm,
	BNDOWNLOAD_RunUpgrade,
	BNDOWNLOAD_GetStatus,
	BNDOWNLOAD_StartPatch,
	BNET_EnterChat,
	BNET_LeaveChat,
	BNET_GetVersion,
	BNET_CreateAccount,
	BNET_GetCreateAccountResult,
	BNET_IsConnected,
	BNSEND_ClickAd,
	BNDOWNLOAD_CancelAll,
	BNSEND_WriteUserData,
	BNSEND_RequestUserData,
	BNSEND_GetUserData,
	BNET_GetConnectionState,
	BNLOG_Printf,
	BNLOG_Command,
	BNSEND_GetCreateGameResult,
	BNSEND_StopAdv,
	BNCDKEY_Validate,
	BNET_GetBnGatewayAccess,
	BNET_ChangePassword,
	BNET_GetChangePasswordResult,
	BNSEND_QueryAdUrl,
	BNNEWS_LoadBNetNews,
	BNNEWS_FreeBNetNews,
	BNET_GetBuild,
	BNET_IsEmailRequested,
	BNSEND_SetEmail,
	BNSEND_ResetPassword,
	BNSEND_ChangeEmail,
	BNSEND_LeaveGame,
};

//Bnclient.0x6FF0AD80 (#23)
BnClientInterface* __cdecl QueryInterface()
{
	return &gtBnClientInterface;
}
