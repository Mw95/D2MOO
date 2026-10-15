#include "BNet.h"

#include <cstdio>

#include <D2Lang.h>
#include <D2Unicode.h>
#include <Fog.h>
#include <Storm.h>
#include <D2MCPClient.h>
#include <D2WinMain.h>
#include <D2WinEditBox.h>
#include <D2WinTextBox.h>

#include "CharSel.h"
#include "MainMenus.h"


//D2Launch.0x6FA3B7F0
HMODULE ghBnClient;
//D2Launch.0x6FA3B7F4
BnClientInterface* gptComInt;
//D2Launch.0x6FA3B7F8
char sgszLastFailedLogonAccountName[16];
//D2Launch.0x6FA33040
int32_t sgnFailedLogonAttempts = 1;
//D2Launch.0x6FA3B808
BOOL sgbConnectionCancelled;
//D2Launch.0x6FA3B80C
BOOL sgbLoggedIn;
//D2Launch.0x6FA3B810
BOOL sgfConnecting;
//D2Launch.0x6FA3B838
D2WinControlStrc* sgpChangeEmailOkButton;
//D2Launch.0x6FA3B83C
D2WinEditBoxStrc* sgpChangeEmailAccountEditBox;
//D2Launch.0x6FA3B840
D2WinTextBoxStrc* sgpConnectingStatusTextBox;
//D2Launch.0x6FA3B844
D2WinTextBoxStrc* sgpConnectingProgressTextBox;
//D2Launch.0x6FA3B848
int32_t sgnConnectingStatusStringId;
//D2Launch.0x6FA3B84C
HANDLE sghConnectionThread;
//D2Launch.0x6FA3B850
DWORD sgdwConnectionStartTickCount;
//D2Launch.0x6FA3B854
D2WinEditBoxStrc* sgpChangeEmailOldEmailEditBox;
//D2Launch.0x6FA3B858
D2WinEditBoxStrc* sgpChangeEmailNewEmailEditBox;
//D2Launch.0x6FA3B85C
D2WinEditBoxStrc* sgpChangeEmailConfirmEmailEditBox;
//D2Launch.0x6FA3B860
D2WinEditBoxStrc* sgpRegisterEmailEditBox;
//D2Launch.0x6FA3B864
D2WinEditBoxStrc* sgpRegisterEmailConfirmEditBox;
//D2Launch.0x6FA3B868
D2WinControlStrc* sgpRegisterEmailOkButton;
//D2Launch.0x6FA3B86C
BOOL sgbRegisterEmailCancelled;
//D2Launch.0x6FA3B870
D2WinEditBoxStrc* sgpResetPasswordAccountEditBox;
//D2Launch.0x6FA3B874
D2WinEditBoxStrc* sgpResetPasswordEmailEditBox;
//D2Launch.0x6FA3B878
D2WinControlStrc* sgpResetPasswordOkButton;
//D2Launch.0x6FA3B87C
char gszEmptyString[] = "";


// Helper function, Bnclient.dll exports the BNGatewayAccess member functions by name
template<typename T>
static T BNGATEWAY_GetFunction(const char* szMangledName)
{
	return reinterpret_cast<T>(GetProcAddress(ghBnClient ? ghBnClient : GetModuleHandleA("Bnclient.dll"), szMangledName));
}

void __fastcall BNGATEWAY_SaveAndUnload(BNGatewayAccess* pGatewayAccess)
{
	static const auto pfSaveAndUnload = BNGATEWAY_GetFunction<void(__stdcall*)(BNGatewayAccess*)>("?SaveAndUnload@BNGatewayAccess@@QAGXXZ");
	pfSaveAndUnload(pGatewayAccess);
}

const char* __fastcall BNGATEWAY_GetRealm(BNGatewayAccess* pGatewayAccess, int32_t nGateway)
{
	static const auto pfRealm = BNGATEWAY_GetFunction<char*(__stdcall*)(BNGatewayAccess*, int32_t)>("?Realm@BNGatewayAccess@@QAGPADH@Z");
	return pfRealm(pGatewayAccess, nGateway);
}

const char* __fastcall BNGATEWAY_GetName(BNGatewayAccess* pGatewayAccess, int32_t nGateway)
{
	static const auto pfName = BNGATEWAY_GetFunction<char*(__stdcall*)(BNGatewayAccess*, int32_t)>("?Name@BNGatewayAccess@@QAGPADH@Z");
	return pfName(pGatewayAccess, nGateway);
}

void __fastcall BNGATEWAY_SetCurGateway(BNGatewayAccess* pGatewayAccess, int32_t nGateway)
{
	static const auto pfSetCurGateway = BNGATEWAY_GetFunction<void(__stdcall*)(BNGatewayAccess*, int32_t)>("?SetCurGateway@BNGatewayAccess@@QAGXH@Z");
	pfSetCurGateway(pGatewayAccess, nGateway);
}


// Helper function, inlined in the original game
static BOOL BNET_IsValidEmailAddress(const char* szEmail)
{
	const char* pAt = SStrChr(szEmail, '@');
	if (!pAt)
	{
		return FALSE;
	}

	const char* pDot = SStrChr(pAt, '.');
	if (!pDot || pAt <= szEmail || pDot <= pAt + 1)
	{
		return FALSE;
	}

	return (int32_t)SStrLen(szEmail) > pDot - szEmail + 1;
}

// Helper function, inlined in the original game
static BOOL BNET_IsValidEmailEditBox(D2WinEditBoxStrc* pEditBox)
{
	char szEmail[256];
	Unicode::toUtf(szEmail, D2Win_10077_EDITBOX_GetText(pEditBox), 256);
	return BNET_IsValidEmailAddress(szEmail);
}

// Helper function, inlined in the original game
static void BNET_ShowNotConnectedMessage()
{
	MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5347), MENU_ShowMainMenu);
}

//D2Launch.0x6FA11000
BOOL __fastcall BNET_LoadBnClient(D2ConfigStrc* ptParams)
{
	char szMessage[100];

	D2_ASSERT(ptParams);

	if (ptParams->pComInterface)
	{
		return TRUE;
	}

	ghBnClient = LoadLibraryA("Bnclient.dll");
	if (!ghBnClient)
	{
		sprintf(szMessage, "Cannot load Bnclient.dll: Error %d", GetLastError());
		MessageBoxA(nullptr, szMessage, "D2Multi", MB_ICONSTOP);
		return FALSE;
	}

	BnClientInterface* (__cdecl* pfQueryInterface)() = (BnClientInterface*(__cdecl*)())GetProcAddress(ghBnClient, "QueryInterface");
	if (!pfQueryInterface)
	{
		sprintf(szMessage, "Unable to QueryInterface for Bnclient.dll: Error %d", GetLastError());
		MessageBoxA(nullptr, szMessage, "D2Multi", MB_ICONSTOP);
		return FALSE;
	}

	gptComInt = pfQueryInterface();
	ptParams->pComInterface = gptComInt;
	gptComInt->Initialize(ptParams);
	return TRUE;
}

//D2Launch.0x6FA110E0
void __fastcall BNET_CancelConnection()
{
	sgbConnectionCancelled = TRUE;
}

//D2Launch.0x6FA110F0
void __fastcall BNET_ResetConnectionCancelled()
{
	sgbConnectionCancelled = FALSE;
}

//D2Launch.0x6FA11100
BOOL __fastcall BNET_IsConnectionCancelled()
{
	return sgbConnectionCancelled;
}

//D2Launch.0x6FA11110
BOOL __fastcall BNET_IsLoggedIn()
{
	return sgbLoggedIn;
}

//D2Launch.0x6FA11120
void __stdcall BNET_WaitForPatchCallback(DWORD dwUnused)
{
	if (gptComInt->GetPatchProgress() != BNPATCH_DONE && !MENU_IsPatchCancelled())
	{
		MENU_UpdatePatchProgress();
		return;
	}

	D2Win_10009();
}

//D2Launch.0x6FA11150
void __stdcall BNET_WaitForLogonCallback(DWORD dwUnused)
{
	if (gptComInt->IsLogonDone())
	{
		D2Win_10009();
	}

	if (sgbConnectionCancelled || !gptComInt->IsConnected() || MENU_IsWaitPopupCancelled())
	{
		D2Win_10009();
	}
}

//D2Launch.0x6FA11190
void __stdcall BNET_WaitForCreateAccountCallback(DWORD dwUnused)
{
	int32_t nResult;
	if (gptComInt->GetCreateAccountResult(&nResult))
	{
		D2Win_10009();
	}

	if (sgbConnectionCancelled || !gptComInt->IsConnected() || MENU_IsWaitPopupCancelled())
	{
		gptComInt->CloseBNetConnection();
		D2Win_10009();
	}
}

//D2Launch.0x6FA111E0
void __stdcall BNET_WaitForChangePasswordCallback(DWORD dwUnused)
{
	int32_t nResult;
	if (gptComInt->GetChangePasswordResult(&nResult))
	{
		D2Win_10009();
	}

	if (sgbConnectionCancelled || !gptComInt->IsConnected() || MENU_IsWaitPopupCancelled())
	{
		gptComInt->CloseBNetConnection();
		D2Win_10009();
	}
}

//D2Launch.0x6FA11230
BOOL __fastcall BNET_Connect()
{
	if (!gptComInt)
	{
		return FALSE;
	}

	D2_ASSERT(!sgfConnecting);

	sgfConnecting = TRUE;

	DWORD dwAllowHardcore = 0;
	SRegLoadValue("Diablo II", "AllowHardcore", 0, &dwAllowHardcore);
	gbAllowHardcore = dwAllowHardcore;

	MENU_ResetPatchCancelled();
	OutputDebugStringA("------------------\nConnect to Battle.net\n------------------\n");
	D2MCPClientCloseMCP();

	if (!gptComInt->CloseBNetConnection())
	{
		D2BnetErrorInfoStrc errInfo = {};
		sgfConnecting = FALSE;
		return BNET_ShowError(&errInfo);
	}

	sgbLoggedIn = FALSE;
	BNET_CreateConnectingPopup();
	D2Win_10008(BNET_WaitForConnectionCallback);

	if (sgbConnectionCancelled)
	{
		gbBnetConnectionCancelled = TRUE;
		MENU_CloseWaitPopup();
		gptComInt->CloseBNetConnection();
		sgfConnecting = FALSE;
		return FALSE;
	}

	if (gptComInt->GetPatchProgress() != BNPATCH_NOT_NEEDED)
	{
		MENU_CreatePatchMenu();
		D2Win_10008(BNET_WaitForPatchCallback);

		if (MENU_IsPatchCancelled() || gptComInt->GetPatchProgress() != BNPATCH_DONE)
		{
			gptComInt->CloseBNetConnection();
			sgfConnecting = FALSE;
			MENU_ShowMainMenu();
			return FALSE;
		}

		BOOL bRestartNeeded = FALSE;
		const BOOL bPatchApplied = gptComInt->ApplyPatch(&bRestartNeeded);
		if (bRestartNeeded)
		{
			const BOOL bSkipToOpen = gnGameType == MODE_OPEN;
			SRegSaveValue("Diablo II", "UseCmdLine", 0, TRUE);
			SRegSaveValue("Diablo II", "Skip To Open", 0, bSkipToOpen);
			D2Win_CloseSpriteCache();
			gptComInt->CloseBNetConnection();
			sgfConnecting = FALSE;
			BNGATEWAY_SaveAndUnload(gptComInt->GetBnGatewayAccess());
			TerminateProcess(GetCurrentProcess(), 0);
			return FALSE;
		}

		if (!bPatchApplied)
		{
			D2BnetErrorInfoStrc errInfo = { 18, nullptr };
			sgfConnecting = FALSE;
			return BNET_ShowError(&errInfo);
		}
	}

	MENU_CloseWaitPopup();

	D2BnetErrorInfoStrc errInfo;
	gptComInt->GetLastError(&errInfo);
	sgfConnecting = FALSE;
	if (errInfo.nError)
	{
		return BNET_ShowError(&errInfo);
	}

	return gptComInt->IsConnected() != 0;
}

//D2Launch.0x6FA11460
BOOL __fastcall BNET_Logon(D2ConfigStrc* ptParams, BOOL bCreateAccount, BOOL bChangePassword)
{
	if (!gptComInt->IsConnected())
	{
		BNET_ShowNotConnectedMessage();
		return FALSE;
	}

	if (sgbLoggedIn)
	{
		FOG_Trace("WARNING: Trying to log in when already logged in!.");
		return TRUE;
	}

	MENU_ShowWaitPopup();

	D2BnetErrorInfoStrc errInfo;
	gptComInt->GetLastError(&errInfo);

	if (bCreateAccount && !errInfo.nError)
	{
		gptComInt->CreateAccount(ptParams->szAccountName, ptParams->szAccountPassword);
		D2Win_10008(BNET_WaitForCreateAccountCallback);
		if (sgbConnectionCancelled)
		{
			MENU_CloseWaitPopup();
			return FALSE;
		}

		int32_t nResult;
		gptComInt->GetCreateAccountResult(&nResult);
		if (nResult && gptComInt->IsConnected())
		{
			D2BnetErrorInfoStrc createAccountErrInfo;
			switch (nResult)
			{
			case 2:
				createAccountErrInfo.nError = 20;
				break;
			case 3:
				createAccountErrInfo.nError = 21;
				break;
			case 4:
				createAccountErrInfo.nError = 22;
				break;
			case 5:
				createAccountErrInfo.nError = 23;
				break;
			case 6:
				createAccountErrInfo.nError = 24;
				break;
			case 7:
				createAccountErrInfo.nError = 25;
				break;
			case 8:
				createAccountErrInfo.nError = 26;
				break;
			default:
				createAccountErrInfo.nError = 19;
				break;
			}

			createAccountErrInfo.szParam = nullptr;
			BNET_ShowError(&createAccountErrInfo);
			return FALSE;
		}
	}
	else if (bChangePassword && !errInfo.nError)
	{
		gptComInt->ChangePassword(ptParams->szAccountName, gszOldAccountPassword, ptParams->szAccountPassword);
		D2Win_10008(BNET_WaitForChangePasswordCallback);
		if (sgbConnectionCancelled)
		{
			MENU_CloseWaitPopup();
			return FALSE;
		}

		int32_t nResult;
		gptComInt->GetChangePasswordResult(&nResult);
		if (nResult != 1 && gptComInt->IsConnected())
		{
			D2BnetErrorInfoStrc changePasswordErrInfo = { 14, nullptr };
			BNET_ShowError(&changePasswordErrInfo);
			return FALSE;
		}
	}

	if (gptComInt->IsConnected() && !errInfo.nError)
	{
		gptComInt->Logon(ptParams->szAccountName, ptParams->szAccountPassword);
		memset(ptParams->szAccountPassword, 0x00, sizeof(ptParams->szAccountPassword));

		D2Win_10008(BNET_WaitForLogonCallback);
		if (sgbConnectionCancelled || MENU_IsWaitPopupCancelled())
		{
			MENU_CloseWaitPopup();
			return FALSE;
		}

		gptComInt->GetLastError(&errInfo);
	}
	else
	{
		gptComInt->GetLastError(&errInfo);
	}

	MENU_CloseWaitPopup();

	if (errInfo.nError)
	{
		return BNET_ShowError(&errInfo);
	}

	sgbLoggedIn = TRUE;

	BOOL bConnected = gptComInt->IsConnected();
	if (gptComInt->IsEmailRegistrationRequired())
	{
		BNET_CreateRegisterEmailMenu();
		D2Win_10008(BNET_IdleCallback);
		MENU_CloseWaitPopup();

		if (BNET_IsRegisterEmailCancelled())
		{
			D2MCPClientCloseMCP();
			gptComInt->CloseBNetConnection();
			MENU_ShowMainMenu();
			return FALSE;
		}

		bConnected = gptComInt->IsConnected();
	}

	if (bConnected)
	{
		MENU_SetShowLogonFailedHint(FALSE);
		return TRUE;
	}

	D2BnetErrorInfoStrc notConnectedErrInfo = { 18, nullptr };
	BNET_ShowError(&notConnectedErrInfo);
	return FALSE;
}

//D2Launch.0x6FA11790
BOOL __fastcall BNET_ShowError(D2BnetErrorInfoStrc* errInfo)
{
	Unicode wszMessage[512];
	Unicode wszTitle[512];
	Unicode wszMessage2[512];

	BOOL bDisconnect = TRUE;
	int32_t nMessage2StringId = -1;
	int32_t nTitleStringId = -1;
	int32_t nMessageStringId = -1;
	int32_t nPopupType = 1;
	D2PopupCallback pfCallback = MENU_ShowMainMenu;

	wszTitle[0] = 0;
	wszMessage2[0] = 0;

	switch (errInfo->nError)
	{
	case 1:
		nTitleStringId = 5245;
		nMessageStringId = 5187;
		nMessage2StringId = 5188;
		nPopupType = 2;
		break;

	case 2:
		nTitleStringId = 5246;
		nMessageStringId = 5183;
		nPopupType = 1;
		break;

	case 3:
	case 7:
		nTitleStringId = 5247;
		nMessageStringId = errInfo->nError == 3 ? 5186 : 10912;
		nMessage2StringId = 5194;
		nPopupType = 2;
		break;

	case 4:
	case 8:
		nTitleStringId = 5247;
		nMessageStringId = errInfo->nError == 4 ? 5199 : 10913;
		nPopupType = 1;
		break;

	case 5:
	case 9:
		nTitleStringId = 5247;
		nMessageStringId = 5202;
		nPopupType = 1;
		break;

	case 6:
	case 10:
	{
		Unicode wszParam[512];

		D2_ASSERT(errInfo->szParam != NULL);

		Unicode::win2Unicode(wszParam, errInfo->szParam, 512);
		Unicode::strncpy(wszTitle, D2LANG_GetStringFromTblIndex(5247), 512);
		Unicode::strncpy(wszMessage, D2LANG_GetStringFromTblIndex(errInfo->nError == 6 ? 5200 : 10914), 512);
		Unicode::strncpy(wszMessage2, D2LANG_GetStringFromTblIndex(5201), 512);
		MENU_ShowTitledMessageWithParam(wszTitle, wszMessage, wszParam, wszMessage2, MENU_ShowMainMenu);
		return FALSE;
	}

	case 11:
		nTitleStringId = 5247;
		nMessageStringId = 5356;
		nPopupType = 1;
		break;

	case 12:
		nTitleStringId = 5247;
		nMessageStringId = 5189;
		nMessage2StringId = 5190;
		nPopupType = 2;
		break;

	case 13:
		nTitleStringId = 5244;
		nMessageStringId = 5208;
		nPopupType = 1;
		bDisconnect = FALSE;
		pfCallback = MENU_ShowLoginMenu;
		break;

	case 14:
		if (!SStrCmp(sgszLastFailedLogonAccountName, gptParams->szAccountName, 0x7FFFFFFF))
		{
			++sgnFailedLogonAttempts;
		}
		else
		{
			sgnFailedLogonAttempts = 1;
			SStrCopy(sgszLastFailedLogonAccountName, gptParams->szAccountName, sizeof(sgszLastFailedLogonAccountName));
		}

		nTitleStringId = 5244;
		nPopupType = 1;
		bDisconnect = FALSE;
		pfCallback = MENU_ShowLoginMenu;

		if (sgnFailedLogonAttempts >= 2)
		{
			MENU_SetShowLogonFailedHint(TRUE);
			nMessageStringId = 11107;
		}
		else
		{
			nMessageStringId = 5207;
		}
		break;

	case 15:
		nTitleStringId = 5244;
		nMessageStringId = 5209;
		nPopupType = 1;
		bDisconnect = FALSE;
		pfCallback = MENU_ShowLoginMenu;
		break;

	case 16:
		nTitleStringId = 5248;
		nMessageStringId = 5349;
		nPopupType = 1;
		break;

	case 17:
		nTitleStringId = 5248;
		nMessageStringId = 5354;
		nPopupType = 1;
		break;

	case 18:
		nTitleStringId = 5248;
		nMessageStringId = 5347;
		nPopupType = 1;
		break;

	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	{
		constexpr int32_t nCreateAccountErrorStringIds[] =
		{
			5231, 5232, 5233, 5239, 5234, 5235, 5236, 5237
		};

		nTitleStringId = 5249;
		nMessageStringId = nCreateAccountErrorStringIds[errInfo->nError - 19];
		nPopupType = 1;
		pfCallback = MENU_ShowCreateAccountMenu;
		bDisconnect = FALSE;
		break;
	}

	default:
		nTitleStringId = 5248;
		nMessageStringId = 5189;
		nMessage2StringId = 5190;
		nPopupType = 2;
		break;
	}

	Unicode::strncpy(wszMessage, D2LANG_GetStringFromTblIndex(nMessageStringId), 512);

	if (nMessage2StringId != -1)
	{
		Unicode::strncpy(wszMessage2, D2LANG_GetStringFromTblIndex(nMessage2StringId), 512);
	}

	if (nTitleStringId != -1)
	{
		Unicode::strncpy(wszTitle, D2LANG_GetStringFromTblIndex(nTitleStringId), 512);
	}

	if (nPopupType == 0)
	{
		MENU_ShowMessage(wszMessage, pfCallback);
	}
	else if (nPopupType == 1)
	{
		MENU_ShowTitledMessage(wszTitle, wszMessage, pfCallback);
	}
	else
	{
		MENU_ShowTitledMessage2(wszTitle, wszMessage, wszMessage2, pfCallback);
	}

	if (bDisconnect)
	{
		D2MCPClientCloseMCP();
		gptComInt->CloseBNetConnection();
	}

	return FALSE;
}

//D2Launch.0x6FA11CF0
void __fastcall BNET_Disconnect()
{
	if (!gptComInt)
	{
		return;
	}

	DWORD dwAllowHardcore = 0;
	SRegLoadValue("Diablo II", "AllowHardcore", 0, &dwAllowHardcore);
	gbAllowHardcore = dwAllowHardcore;

	gptParams->szCurrentChannelName[0] = '\0';
	gptParams->szDefaultChannelName[0] = '\0';
	OutputDebugStringA("Disconnect from BNET\n");
	D2MCPClientCloseMCP();
	gptComInt->CloseBNetConnection();
}

//D2Launch.0x6FA11D60
void __stdcall BNET_WaitForConnectionCallback(DWORD dwUnused)
{
	BNET_UpdateConnectingPopup();

	if (!sghConnectionThread)
	{
		sghConnectionThread = gptComInt->OpenBNetConnection();
		if (!sghConnectionThread)
		{
			D2Win_10009();
			return;
		}

		BNET_ResetConnectionCancelled();
	}

	if (WaitForSingleObject(sghConnectionThread, 0) == WAIT_OBJECT_0)
	{
		D2Win_10009();
	}

	if (BNET_IsConnectionCancelled())
	{
		gptComInt->CloseBNetConnection();
		D2Win_10009();
	}
}

//D2Launch.0x6FA11DC0
void __fastcall BNET_CreateConnectingPopup()
{
	sgdwConnectionStartTickCount = GetTickCount();

	MENU_DestroySubChildren();
	MENU_SetPopupActive(TRUE);

	D2WinControlStrc* pBackground = MENU_CreateSubChild(226);
	D2Win_10033(pBackground, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);

	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(227), 1);

	D2WinTextBoxStrc* pTitle = (D2WinTextBoxStrc*)MENU_CreateSubChild(228);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pTitle->controlHeader, 1);
	D2Win_10051(pTitle, D2LANG_GetStringFromTblIndex(5171), 0, 0, 0);

	sgpConnectingStatusTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(229);
	D2Win_10030_CONTROL_ToggleFourthFlag(&sgpConnectingStatusTextBox->controlHeader, 1);

	sgpConnectingProgressTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(230);
	D2Win_10030_CONTROL_ToggleFourthFlag(&sgpConnectingProgressTextBox->controlHeader, 1);

	sgnConnectingStatusStringId = -1;
	sghConnectionThread = nullptr;

	MENU_SetPopupCallback(BNET_CancelConnection);
	BNET_UpdateConnectingPopup();
}

//D2Launch.0x6FA11E90
void __fastcall BNET_UpdateConnectingPopup()
{
	char szProgress[256];

	if (!sgpConnectingStatusTextBox)
	{
		return;
	}

	int32_t nConnectionState;
	gptComInt->GetConnectionState(&nConnectionState);

	switch (nConnectionState)
	{
	case 0:
		sgnConnectingStatusStringId = 5171;
		break;

	case 1:
		sgnConnectingStatusStringId = 5172;
		break;

	case 2:
		sgnConnectingStatusStringId = 5173;
		break;

	case 3:
		sgnConnectingStatusStringId = 5174;
		break;

	case 4:
		sgnConnectingStatusStringId = 5175;
		break;

	case 5:
		sgnConnectingStatusStringId = 5176;
		break;

	case 6:
		sgnConnectingStatusStringId = 5177;
		break;

	default:
		sgnConnectingStatusStringId = -1;
		break;
	}

	D2Win_10047(sgpConnectingStatusTextBox);
	if (sgnConnectingStatusStringId >= 0)
	{
		D2Win_10051(sgpConnectingStatusTextBox, D2LANG_GetStringFromTblIndex(sgnConnectingStatusStringId), 0, 0, 0);
	}

	sprintf(szProgress, "%.*s", (GetTickCount() - sgdwConnectionStartTickCount) / 250 % 20 + 1, "....................");
	D2Win_10047(sgpConnectingProgressTextBox);
	D2Win_10045(sgpConnectingProgressTextBox, szProgress);
}

//D2Launch.0x6FA11FD0
int32_t __stdcall BNET_RegisterEmailOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const Unicode* wszEmail = D2Win_10077_EDITBOX_GetText(sgpRegisterEmailEditBox);
	const Unicode* wszConfirmEmail = D2Win_10077_EDITBOX_GetText(sgpRegisterEmailConfirmEditBox);
	if (Unicode::strcmp(wszEmail, wszConfirmEmail) != 0)
	{
		MENU_ShowMessageBox(nullptr, D2LANG_GetStringFromTblIndex(11099), 5102, 0, MENU_ClosePopupCallback, nullptr, TRUE, FALSE);
		return 1;
	}

	char szEmail[256];
	Unicode::toUtf(szEmail, wszEmail, 256);
	if (!BNET_IsValidEmailAddress(szEmail))
	{
		const Unicode* wszMessage = D2LANG_GetStringFromTblIndex(11101);
		MENU_ShowMessageBox(D2LANG_GetStringFromTblIndex(11100), wszMessage, 5102, 0, MENU_ClosePopupCallback, nullptr, TRUE, FALSE);
		return 1;
	}

	gptComInt->SetEmail(szEmail);
	D2Win_10009();
	return 1;
}

//D2Launch.0x6FA12100
int32_t __stdcall BNET_RegisterEmailLaterCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_ShowMessageBox(nullptr, D2LANG_GetStringFromTblIndex(11102), 11105, 5103, BNET_RegisterEmailLaterConfirmCallback, MENU_ClosePopupCallback, FALSE, TRUE);
	return 1;
}

//D2Launch.0x6FA12140
int32_t __stdcall BNET_RegisterEmailLaterConfirmCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gptComInt->SetEmail(gszEmptyString);
	D2Win_10009();
	return 1;
}

//D2Launch.0x6FA12160
int32_t __stdcall BNET_RegisterEmailCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	sgbRegisterEmailCancelled = TRUE;
	D2Win_10009();
	return 1;
}

//D2Launch.0x6FA12180
void __fastcall BNET_CreateRegisterEmailMenu()
{
	sgbRegisterEmailCancelled = FALSE;

	MENU_CreateBlankScreen();

	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(290), D2LANG_GetStringFromTblIndex(11093), 0, 0, 0);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(291), D2LANG_GetStringFromTblIndex(11094), 0, 0, 0);

	MENU_CreateChild(288);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(292), D2LANG_GetStringFromTblIndex(11095));
	sgpRegisterEmailEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(294);
	D2Win_10073(sgpRegisterEmailEditBox, BNET_RegisterEmailEditBoxCallback);

	MENU_CreateChild(289);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(293), D2LANG_GetStringFromTblIndex(11096));
	sgpRegisterEmailConfirmEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(295);
	D2Win_10073(sgpRegisterEmailConfirmEditBox, BNET_RegisterEmailEditBoxCallback);

	sgpRegisterEmailOkButton = MENU_CreateChild(296);
	MENU_CreateChild(297);
	MENU_CreateChild(298);

	D2Win_10012(sgpRegisterEmailEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpRegisterEmailEditBox, sgpRegisterEmailConfirmEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpRegisterEmailConfirmEditBox, sgpRegisterEmailEditBox);

	const BOOL bHasEmail = Unicode::strlen(D2Win_10077_EDITBOX_GetText(sgpRegisterEmailEditBox)) > 0;
	const BOOL bHasConfirmEmail = Unicode::strlen(D2Win_10077_EDITBOX_GetText(sgpRegisterEmailConfirmEditBox)) > 0;
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpRegisterEmailOkButton, bHasEmail | bHasConfirmEmail);
}

//D2Launch.0x6FA12300
void __stdcall BNET_RegisterEmailEditBoxCallback(int32_t nUnused)
{
	const BOOL bHasEmail = Unicode::strlen(D2Win_10077_EDITBOX_GetText(sgpRegisterEmailEditBox)) > 0;
	const BOOL bHasConfirmEmail = Unicode::strlen(D2Win_10077_EDITBOX_GetText(sgpRegisterEmailConfirmEditBox)) > 0;
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpRegisterEmailOkButton, bHasEmail | bHasConfirmEmail);
}

//D2Launch.0x6FA12360
void __stdcall BNET_IdleCallback(DWORD dwUnused)
{
}

//D2Launch.0x6FA12370
BOOL __fastcall BNET_IsRegisterEmailCancelled()
{
	return sgbRegisterEmailCancelled;
}

// Helper function, inlined in the original game
static BOOL BNET_CanSubmitResetPassword()
{
	return Unicode::strlen(D2Win_10077_EDITBOX_GetText(sgpResetPasswordAccountEditBox)) > 2
		&& BNET_IsValidEmailEditBox(sgpResetPasswordEmailEditBox);
}

//D2Launch.0x6FA12380
void __fastcall BNET_CreateResetPasswordMenu()
{
	if (!gptComInt->IsConnected())
	{
		BNET_ShowNotConnectedMessage();
		return;
	}

	MENU_CreateBlankScreen();

	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(299), D2LANG_GetStringFromTblIndex(11114), 0, 0, 0);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(302), D2LANG_GetStringFromTblIndex(11103), 0, 0, 0);

	MENU_CreateChild(303);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(304), D2LANG_GetStringFromTblIndex(5224));
	sgpResetPasswordAccountEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(305);
	D2Win_10081(sgpResetPasswordAccountEditBox, 16);
	D2Win_10072(sgpResetPasswordAccountEditBox, MENU_AccountNameCharFilter);
	D2Win_10073(sgpResetPasswordAccountEditBox, BNET_ResetPasswordEditBoxCallback);

	MENU_CreateChild(306);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(307), D2LANG_GetStringFromTblIndex(11095));
	sgpResetPasswordEmailEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(308);
	D2Win_10073(sgpResetPasswordEmailEditBox, BNET_ResetPasswordEditBoxCallback);

	D2Win_10076(sgpResetPasswordAccountEditBox, gptParams->szAccountName);
	D2Win_10012(sgpResetPasswordAccountEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpResetPasswordAccountEditBox, sgpResetPasswordEmailEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpResetPasswordEmailEditBox, sgpResetPasswordAccountEditBox);

	sgpResetPasswordOkButton = MENU_CreateChild(300);
	MENU_CreateChild(301);

	D2Win_10025_CONTROL_ToggleFirstFlag(sgpResetPasswordOkButton, BNET_CanSubmitResetPassword());
}

//D2Launch.0x6FA125B0
void __stdcall BNET_ResetPasswordEditBoxCallback(int32_t nUnused)
{
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpResetPasswordOkButton, BNET_CanSubmitResetPassword());
}

//D2Launch.0x6FA12660
int32_t __stdcall BNET_ResetPasswordOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!pMsg)
	{
		BNET_CreateAccountOptionsMenu();
		return 1;
	}

	if (!D2Win_10024_CONTROL_CheckFirstFlag(sgpResetPasswordOkButton))
	{
		return 1;
	}

	char szEmail[256];
	char szAccountName[256];
	const Unicode* wszAccountName = D2Win_10077_EDITBOX_GetText(sgpResetPasswordAccountEditBox);
	const Unicode* wszEmail = D2Win_10077_EDITBOX_GetText(sgpResetPasswordEmailEditBox);
	Unicode::toUtf(szAccountName, wszAccountName, 256);
	Unicode::toUtf(szEmail, wszEmail, 256);

	if (gptComInt->IsConnected() && gptComInt->ResetPassword(szAccountName, szEmail))
	{
		MENU_ShowMessageBox(nullptr, D2LANG_GetStringFromTblIndex(11104), 5102, 0, BNET_ResetPasswordDoneCallback, nullptr, TRUE, FALSE);
		return 1;
	}

	BNET_ShowNotConnectedMessage();
	return 0;
}

//D2Launch.0x6FA12760
int32_t __stdcall BNET_ResetPasswordDoneCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_ShowLoginMenu();
	return 1;
}

//D2Launch.0x6FA12770
int32_t __stdcall BNET_BackToAccountOptionsCallback(SMSGHANDLER_PARAMS* pMsg)
{
	BNET_CreateAccountOptionsMenu();
	return 1;
}

//D2Launch.0x6FA12780
void __fastcall BNET_CreateAccountOptionsMenu()
{
	if (!gptComInt->IsConnected())
	{
		BNET_ShowNotConnectedMessage();
		return;
	}

	MENU_CreateBlankScreen();

	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(309), D2LANG_GetStringFromTblIndex(11109), 0, 0, 0);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(310), D2LANG_GetStringFromTblIndex(11110), 0, 0, 0);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(311), D2LANG_GetStringFromTblIndex(11111), 0, 0, 0);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(312), D2LANG_GetStringFromTblIndex(11112), 0, 0, 0);
	MENU_CreateChild(313);
	MENU_CreateChild(314);
	MENU_CreateChild(315);
	MENU_CreateChild(316);
}

//D2Launch.0x6FA12870
int32_t __stdcall BNET_ChangePasswordCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_CreateChangePasswordMenu();
	return 1;
}

//D2Launch.0x6FA12880
int32_t __stdcall BNET_ResetPasswordCallback(SMSGHANDLER_PARAMS* pMsg)
{
	BNET_CreateResetPasswordMenu();
	return 1;
}

//D2Launch.0x6FA12890
int32_t __stdcall BNET_ChangeEmailCallback(SMSGHANDLER_PARAMS* pMsg)
{
	BNET_CreateChangeEmailMenu();
	return 1;
}

//D2Launch.0x6FA128A0
int32_t __stdcall BNET_AccountOptionsBackCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_ShowLoginMenu();
	return 1;
}

// Helper function, inlined in the original game
static BOOL BNET_CanSubmitChangeEmail()
{
	return Unicode::strlen(D2Win_10077_EDITBOX_GetText(sgpChangeEmailAccountEditBox)) > 2
		&& BNET_IsValidEmailEditBox(sgpChangeEmailOldEmailEditBox)
		&& BNET_IsValidEmailEditBox(sgpChangeEmailNewEmailEditBox)
		&& BNET_IsValidEmailEditBox(sgpChangeEmailConfirmEmailEditBox);
}

//D2Launch.0x6FA128B0
void __fastcall BNET_CreateChangeEmailMenu()
{
	if (!gptComInt->IsConnected())
	{
		BNET_ShowNotConnectedMessage();
		return;
	}

	MENU_CreateBlankScreen();

	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(317), D2LANG_GetStringFromTblIndex(11116), 0, 0, 0);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(318), D2LANG_GetStringFromTblIndex(11120), 0, 0, 0);

	MENU_CreateChild(319);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(320), D2LANG_GetStringFromTblIndex(5224));
	sgpChangeEmailAccountEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(321);
	D2Win_10076(sgpChangeEmailAccountEditBox, gptParams->szAccountName);
	D2Win_10081(sgpChangeEmailAccountEditBox, 16);
	D2Win_10072(sgpChangeEmailAccountEditBox, MENU_AccountNameCharFilter);
	D2Win_10073(sgpChangeEmailAccountEditBox, BNET_ChangeEmailEditBoxCallback);

	MENU_CreateChild(322);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(323), D2LANG_GetStringFromTblIndex(11117));
	sgpChangeEmailOldEmailEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(324);
	D2Win_10073(sgpChangeEmailOldEmailEditBox, BNET_ChangeEmailEditBoxCallback);

	MENU_CreateChild(325);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(326), D2LANG_GetStringFromTblIndex(11118));
	sgpChangeEmailNewEmailEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(327);
	D2Win_10073(sgpChangeEmailNewEmailEditBox, BNET_ChangeEmailEditBoxCallback);

	MENU_CreateChild(328);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(329), D2LANG_GetStringFromTblIndex(11119));
	sgpChangeEmailConfirmEmailEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(330);
	D2Win_10073(sgpChangeEmailConfirmEmailEditBox, BNET_ChangeEmailEditBoxCallback);

	sgpChangeEmailOkButton = MENU_CreateChild(331);
	MENU_CreateChild(332);

	D2Win_10012(sgpChangeEmailAccountEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpChangeEmailAccountEditBox, sgpChangeEmailOldEmailEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpChangeEmailOldEmailEditBox, sgpChangeEmailNewEmailEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpChangeEmailNewEmailEditBox, sgpChangeEmailConfirmEmailEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpChangeEmailConfirmEmailEditBox, sgpChangeEmailAccountEditBox);

	D2Win_10025_CONTROL_ToggleFirstFlag(sgpChangeEmailOkButton, BNET_CanSubmitChangeEmail());
}

//D2Launch.0x6FA12C60
void __stdcall BNET_ChangeEmailEditBoxCallback(int32_t nUnused)
{
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpChangeEmailOkButton, BNET_CanSubmitChangeEmail());
}

//D2Launch.0x6FA12DF0
int32_t __stdcall BNET_ChangeEmailOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!pMsg)
	{
		BNET_CreateAccountOptionsMenu();
		return 1;
	}

	if (!D2Win_10024_CONTROL_CheckFirstFlag(sgpChangeEmailOkButton))
	{
		return 1;
	}

	const Unicode* wszAccountName = D2Win_10077_EDITBOX_GetText(sgpChangeEmailAccountEditBox);
	const Unicode* wszOldEmail = D2Win_10077_EDITBOX_GetText(sgpChangeEmailOldEmailEditBox);
	const Unicode* wszNewEmail = D2Win_10077_EDITBOX_GetText(sgpChangeEmailNewEmailEditBox);
	const Unicode* wszConfirmEmail = D2Win_10077_EDITBOX_GetText(sgpChangeEmailConfirmEmailEditBox);

	if (Unicode::strcmp(wszNewEmail, wszConfirmEmail) != 0)
	{
		MENU_ShowMessageBox(nullptr, D2LANG_GetStringFromTblIndex(11122), 5102, 0, MENU_ClosePopupCallback, nullptr, TRUE, FALSE);
		return 1;
	}

	if (!Unicode::strcmp(wszOldEmail, wszNewEmail))
	{
		MENU_ShowMessageBox(nullptr, D2LANG_GetStringFromTblIndex(11121), 5102, 0, MENU_ClosePopupCallback, nullptr, TRUE, FALSE);
		return 1;
	}

	char szOldEmail[256];
	char szAccountName[256];
	char szNewEmail[256];
	char szConfirmEmail[256];
	Unicode::toUtf(szAccountName, wszAccountName, 256);
	Unicode::toUtf(szOldEmail, wszOldEmail, 256);
	Unicode::toUtf(szNewEmail, wszNewEmail, 256);
	Unicode::toUtf(szConfirmEmail, wszNewEmail, 256);

	if (gptComInt->IsConnected() && gptComInt->ChangeEmail(szAccountName, szOldEmail, szNewEmail))
	{
		MENU_ShowLoginMenu();
		return 1;
	}

	BNET_ShowNotConnectedMessage();
	return 0;
}
