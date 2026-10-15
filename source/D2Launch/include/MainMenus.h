#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Config.h>
#include <D2Constants.h>
#include <D2Unicode.h>
#include <D2WinControlHeader.h>
#include <D2WinAnimImage.h>
#include <D2WinButton.h>
#include <D2WinEditBox.h>
#include <D2WinImage.h>
#include <D2WinTextBox.h>
#include <D2WinTimer.h>
#include <D2WinArchive.h>
#include <Font.h>

#include "CharSel.h"

struct SMSGHANDLER_PARAMS;

constexpr int32_t MAX_CHILDREN = 64;

// Called when the button of a popup is pressed
typedef void(__fastcall* D2PopupCallback)();

enum D2LaunchCharacterClass
{
	CHARCLASS_AMAZON = 0,
	CHARCLASS_SORCERESS = 1,
	CHARCLASS_NECROMANCER = 2,
	CHARCLASS_PALADIN = 3,
	CHARCLASS_BARBARIAN = 4,
	CHARCLASS_DRUID = 5,
	CHARCLASS_ASSASSIN = 6,
};

// Indices of the animated images of the character creation screen
enum D2CharCreateAnimImage
{
	CHARCREATE_BARBARIAN = 0,
	CHARCREATE_NECROMANCER = 1,
	CHARCREATE_AMAZON = 2,
	CHARCREATE_SORCERESS = 3,
	CHARCREATE_PALADIN = 4,
	CHARCREATE_NUM_CLASSIC_CLASSES = 5,
	CHARCREATE_DRUID = 5,
	CHARCREATE_ASSASSIN = 6,
	CHARCREATE_NUM_CLASSES = 7,
};

// D2ClientSaveFlags
enum D2LaunchSaveFlags : uint16_t
{
	LAUNCHSAVEFLAG_NEWBIE = 0x01,
	LAUNCHSAVEFLAG_NEWBIE_REALM = 0x02,
	LAUNCHSAVEFLAG_HARDCORE = 0x04,
	LAUNCHSAVEFLAG_DEAD = 0x08,
	LAUNCHSAVEFLAG_EXPANSION = 0x20,
	LAUNCHSAVEFLAG_LADDER = 0x40,
};

// Unlocked cinematics are stored in the last byte of the "Aux Battle.net" registry value
enum D2LaunchCinematicFlags : uint32_t
{
	CINEMATICFLAG_EXPANSION_OUTRO = 0x01,
	CINEMATICFLAG_ACT2START = 0x04,
	CINEMATICFLAG_ACT4START = 0x08,
	CINEMATICFLAG_ACT4END = 0x10,
	CINEMATICFLAG_ACT3START = 0x40,
	CINEMATICFLAG_EXPANSION_INTRO = 0x80,
};

#pragma pack(push, 1)
struct D2MenuFontStrc
{
	Font eFont;									//0x00
	int32_t nColor;								//0x04
};

struct D2ShardStrc
{
	char* pszName;								//0x00
	char* pszDescription;						//0x04
};

// Returned by BnClientInterface::SendRealmList
struct D2RealmListPacketStrc
{
	uint32_t unk0x00;							//0x00
	uint32_t nCount;							//0x04
	uint8_t pData[1];							//0x08 For each realm: uint32_t unk, char szName[], char szDescription[]
};
#pragma pack(pop)

extern D2ConfigStrc* gptParams;
extern int32_t gnGameType;
extern int32_t gnNextModule;
extern BOOL gbBnetConnectionCancelled;
extern char gszOldAccountPassword[24];
extern D2PopupCallback gpfPopupCallback;
extern D2CellFileStrc* gpCharSelectBackgroundCellFile;
extern D2WinControlInitStrc gaControlInits[333];
extern D2MenuFontStrc gaMenuFonts[9];
extern const char* const gszFeCharPaletteDat;
extern const char* const gszFeCharPalettePl2;
extern const char* const gszSkyPaletteDat;
extern const char* const gszSkyPalettePl2;

//D2Launch.0x6FA17750
void __fastcall MENU_SetPopupCallback(D2PopupCallback pfCallback);
//D2Launch.0x6FA17760
void __fastcall MENU_SetPopupActive(BOOL bUnused);
//D2Launch.0x6FA17770
void __stdcall MENU_WaitForCharacterCreationCallback(DWORD dwUnused);
//D2Launch.0x6FA177B0
void __stdcall MENU_WaitForCharacterLogonCallback(DWORD dwUnused);
//D2Launch.0x6FA177F0
void __stdcall MENU_WaitForCharacterDeletionCallback(DWORD dwUnused);
//D2Launch.0x6FA17830
void __stdcall MENU_WaitForCharacterUpgradeCallback(DWORD dwUnused);
//D2Launch.0x6FA17870
BOOL __fastcall MENU_LoadPalette(const char* szPalDatFileName, const char* szPalPL2FileName);
//D2Launch.0x6FA17920
D2WinControlStrc* __fastcall MENU_CreateSubChild(int32_t nIndex);
//D2Launch.0x6FA17970
void __fastcall MENU_DestroySubChildren();
//D2Launch.0x6FA179B0
D2WinControlStrc* __fastcall MENU_CreateChild(int32_t nIndex);
//D2Launch.0x6FA17A00
void __fastcall MENU_DestroyChildren();
//D2Launch.0x6FA17B40
void __fastcall MENU_ShowTitledMessage(const Unicode* wszTitle, const Unicode* wszMessage, D2PopupCallback pfCallback);
//D2Launch.0x6FA17D90
void __fastcall MENU_ShowTitledMessage2(const Unicode* wszTitle, const Unicode* wszMessage, const Unicode* wszMessage2, D2PopupCallback pfCallback);
//D2Launch.0x6FA180E0
BOOL __fastcall MENU_AddTextBoxLines(D2WinTextBoxStrc* pTextBox, const Unicode* wszText, int32_t nColor, int32_t nAlign);
//D2Launch.0x6FA18180
void __fastcall MENU_ShowTitledMessageWithParam(const Unicode* wszTitle, const Unicode* wszMessage, const Unicode* wszParam, const Unicode* wszMessage2, D2PopupCallback pfCallback);
//D2Launch.0x6FA184B0
void __fastcall MENU_ShowMessageWithButton(const Unicode* wszMessage, D2PopupCallback pfCallback, BOOL bOkButton);
//D2Launch.0x6FA18720
void __fastcall MENU_ShowMessage(const Unicode* wszMessage, D2PopupCallback pfCallback);
//D2Launch.0x6FA18960
void __fastcall MENU_ShowMessageBox(const Unicode* wszTitle, const Unicode* wszMessage, int32_t nOkStringId, int32_t nCancelStringId, int32_t(__stdcall* pfOk)(SMSGHANDLER_PARAMS*), int32_t(__stdcall* pfCancel)(SMSGHANDLER_PARAMS*), BOOL bOkOnEnter, BOOL bCloseOnEscape);
//D2Launch.0x6FA18C60
int32_t __stdcall MENU_ClosePopupCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA18CA0
void __fastcall MENU_CancelWaitPopup();
//D2Launch.0x6FA18CB0
BOOL __fastcall MENU_IsWaitPopupCancelled();
//D2Launch.0x6FA18CC0
void __fastcall MENU_ShowWaitPopup();
//D2Launch.0x6FA18EA0
int32_t __stdcall MENU_ShowCannotConnectToBattleNetPopup(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA18FC0
void __fastcall MENU_CloseWaitPopup();
//D2Launch.0x6FA19000
void __fastcall MENU_CreatePatchMenu();
//D2Launch.0x6FA19260
void __fastcall MENU_UpdatePatchProgress();
//D2Launch.0x6FA192E0
void __fastcall MENU_ResetPatchCancelled();
//D2Launch.0x6FA192F0
BOOL __fastcall MENU_IsPatchCancelled();
//D2Launch.0x6FA19300
int32_t __stdcall MENU_CancelPatchCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA19320
void __fastcall MENU_ShowMainMenu();
//D2Launch.0x6FA19750
void __fastcall MENU_ShowCharacterSelection();
//D2Launch.0x6FA19890
int32_t __stdcall MENU_AccountNameCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar);
//D2Launch.0x6FA19910
void __fastcall MENU_ShowLoginMenu();
//D2Launch.0x6FA19E40
int32_t __stdcall MENU_LoginAccountNameCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar);
//D2Launch.0x6FA19EC0
int32_t __stdcall MENU_PasswordCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar);
//D2Launch.0x6FA19ED0
void __fastcall MENU_SetShowLogonFailedHint(BOOL bShow);
//D2Launch.0x6FA19EE0
int32_t __stdcall MENU_TcpIpTimerCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA19F90
void __fastcall MENU_ShowTcpIpMenu();
//D2Launch.0x6FA1A430
void __fastcall MENU_UpdateTcpIpMenu();
//D2Launch.0x6FA1A4E0
int32_t __stdcall MENU_TcpIpHostButtonHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1A520
int32_t __stdcall MENU_TcpIpJoinButtonHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1A560
void __fastcall MENU_ShowCreateAccountMenu();
//D2Launch.0x6FA1AA40
int32_t __stdcall MENU_CreateAccountNameCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar);
//D2Launch.0x6FA1AAC0
BOOL __fastcall MENU_ShowTermsOfService();
//D2Launch.0x6FA1B170
void __stdcall MENU_DownloadTermsOfServiceCallback(DWORD dwUnused);
//D2Launch.0x6FA1B1A0
int32_t __stdcall MENU_AcceptTermsOfServiceCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1B1B0
int32_t __stdcall MENU_TermsOfServicePageUpCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1B220
int32_t __stdcall MENU_TermsOfServicePageDownCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1B290
int32_t __stdcall MENU_CreateCharacterConfirmCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1B4C0
int32_t __stdcall MENU_CreateCharacterCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1B500
int32_t __stdcall MENU_CreateCharacterOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1B750
void __fastcall MENU_CreateCharacterCreationMenu();
//D2Launch.0x6FA1C0E0
int32_t __stdcall MENU_CharacterNameCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar);
//D2Launch.0x6FA1C160
void __stdcall MENU_CharacterNameEditBoxCallback(int32_t nUnused);
//D2Launch.0x6FA1C1E0
void __fastcall MENU_UpdateCharCreateOkButton();
//D2Launch.0x6FA1C250
void __stdcall MENU_LoginEditBoxCallback(int32_t nUnused);
//D2Launch.0x6FA1C2C0
void __fastcall MENU_UpdateLoginOkButton();
//D2Launch.0x6FA1C330
int32_t __stdcall MENU_HardcoreCheckBoxCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1C350
int32_t __stdcall MENU_LadderCheckBoxCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1C370
int32_t __stdcall MENU_ExpansionCheckBoxCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1C3A0
int32_t __stdcall MENU_CharClassClickCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1CB30
int32_t __stdcall MENU_SorceressHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1CBE0
int32_t __stdcall MENU_AmazonHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1CC90
int32_t __stdcall MENU_AssassinHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1CD40
int32_t __stdcall MENU_DruidHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1CDF0
int32_t __stdcall MENU_NecromancerHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1CEA0
int32_t __stdcall MENU_BarbarianHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1CF50
int32_t __stdcall MENU_PaladinHoverCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1D000
int __cdecl MENU_QuitCallback();
//D2Launch.0x6FA1D010
BOOL __fastcall MENU_FreeRealmList();
//D2Launch.0x6FA1D0F0
int __cdecl MENU_CompareShards(const void* pLeft, const void* pRight);
//D2Launch.0x6FA1D140
int32_t __fastcall MENU_GetRealmCount();
//D2Launch.0x6FA1D150
const char* __fastcall MENU_GetRealmName(int32_t index);
//D2Launch.0x6FA1D180
void __fastcall MENU_RequestRealmList();
//D2Launch.0x6FA1D490
int32_t __fastcall MENU_Run(D2ConfigStrc* pConfig);
//D2Launch.0x6FA1DAD0
void __fastcall MENU_LoadCellFiles();
//D2Launch.0x6FA1E280
void __fastcall MENU_FreeCellFiles();
//D2Launch.0x6FA1E600
BOOL __fastcall MENU_ShouldPlayExpansionIntro();
//D2Launch.0x6FA1E670
void __fastcall MENU_PlayExpansionIntro();
//D2Launch.0x6FA1E850
void __fastcall MENU_ShowTitleScreen();
//D2Launch.0x6FA1EB40
void __fastcall MENU_BuildVideoPath(char* szPath, const char* szFormat, const char* szResolution);
//D2Launch.0x6FA1EC10
int32_t __stdcall MENU_SinglePlayerCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1EDC0
int32_t __stdcall MENU_OpenBattleNetCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1EDE0
int32_t __stdcall MENU_CharacterCreationExitCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1EF30
int32_t __stdcall MENU_OtherMultiplayerCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1F010
void __fastcall MENU_BalanceCreditsColumns();
//D2Launch.0x6FA1F110
BOOL __fastcall MENU_LoadCredits(int32_t nUnused);
//D2Launch.0x6FA1F5B0
void __fastcall MENU_ByteSwapUnicodeString(Unicode* pString, uint32_t nLength);
//D2Launch.0x6FA1F5E0
int32_t __stdcall MENU_ShowCreditsCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1F9E0
int32_t __stdcall MENU_CreditsTimerCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA1FA10
BOOL __stdcall MENU_ShowInsertPlayDiscPrompt();
//D2Launch.0x6FA1FB90
BOOL __stdcall MENU_ShowInsertExpansionDiscPrompt();
//D2Launch.0x6FA1FD10
int32_t __stdcall MENU_ShowCinematicsCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA20210
void __fastcall MENU_PumpMessagesIgnoringInput();
//D2Launch.0x6FA202B0
int32_t __stdcall MENU_PlayIntroCinematicCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA20680
int32_t __stdcall MENU_PlayAct2CinematicCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA20A50
int32_t __stdcall MENU_PlayAct3CinematicCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA20E20
int32_t __stdcall MENU_PlayAct4CinematicCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA211F0
int32_t __stdcall MENU_PlayAct4EndCinematicCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA215C0
int32_t __stdcall MENU_PlayExpansionIntroCinematicCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA21980
int32_t __stdcall MENU_PlayExpansionOutroCinematicCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA21D40
int32_t __stdcall MENU_CinematicsCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA21D80
int32_t __stdcall MENU_InsertPlayDiscRetryCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA21D90
int32_t __stdcall MENU_InsertVideoDiscRetryCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA21DA0
int32_t __stdcall MENU_InsertVideoDiscCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA21DC0
void __stdcall MENU_DiscPromptWaitCallback(DWORD dwUnused);
//D2Launch.0x6FA21DE0
BOOL __stdcall MENU_ShowInsertVideoDiscPrompt();
//D2Launch.0x6FA21FB0
int32_t __stdcall MENU_TcpIpCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA21FD0
int32_t __stdcall MENU_BattleNetCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA21FF0
int32_t __stdcall MENU_ShowGatewaySelectionCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA22240
BOOL __fastcall MENU_IsDoubleClick(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA222D0
int32_t __stdcall MENU_GatewayListClickCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA224E0
int32_t __stdcall MENU_GatewayOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA22660
int32_t __stdcall MENU_GatewayCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA227C0
void __fastcall MENU_UpdateGatewayButton();
//D2Launch.0x6FA22900
int32_t __stdcall MENU_ExitGameCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA22930
int32_t __stdcall MENU_TcpIpHostGameCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA22B20
void __stdcall MENU_TcpIpJoinWaitCallback(DWORD dwUnused);
//D2Launch.0x6FA22BA0
void __stdcall MENU_RealmListWaitCallback(DWORD dwUnused);
//D2Launch.0x6FA22BB0
int32_t __stdcall MENU_TcpIpJoinGameCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA22E80
int32_t __stdcall MENU_TcpIpJoinGameCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA22F20
void __stdcall MENU_TcpIpConnectWaitCallback(DWORD dwUnused);
//D2Launch.0x6FA22F60
int32_t __stdcall MENU_TcpIpJoinGameOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA23430
BOOL __fastcall MENU_DeleteRealmCharacter(D2CharSelNodeStrc* pNode, const char* szRealmName);
//D2Launch.0x6FA23660
BOOL __fastcall MENU_ConvertRealmCharacterToExpansion(D2CharSelNodeStrc* pNode, const char* szRealmName);
//D2Launch.0x6FA23890
BOOL __fastcall MENU_StartGameWithCharacter(D2CharSelNodeStrc* pNode, uint16_t nSaveFlags, uint8_t nClass, const char* szRealmName);
//D2Launch.0x6FA24050
int32_t __stdcall MENU_CreateNewCharacterCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA24060
int32_t __stdcall MENU_SkipLogoCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA24410
BOOL __fastcall MENU_FileExists(int32_t nUnused, const char* szPath);
//D2Launch.0x6FA24440
int32_t __stdcall MENU_CharacterSelectionExitCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA24460
void __fastcall MENU_SetCharCreateClass(uint8_t nClass);
//D2Launch.0x6FA24550
void __fastcall MENU_ValidateCharacterCreation();
//D2Launch.0x6FA24D50
void __fastcall MENU_CreateRealmCharacter();
//D2Launch.0x6FA25430
int32_t __stdcall MENU_PopupButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA25450
int32_t __stdcall MENU_CreateNewAccountCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA257B0
void __fastcall MENU_CreateChangePasswordMenu();
//D2Launch.0x6FA25C80
int32_t __stdcall MENU_AccountOptionsCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA25CC0
int32_t __stdcall MENU_LoginOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA26090
int32_t __stdcall MENU_BackToMainMenuCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA260A0
int32_t __stdcall MENU_CreateAccountOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA26390
void __fastcall MENU_CreateAccountInfoBackground();
//D2Launch.0x6FA26640
int32_t __stdcall MENU_ChangePasswordOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA26A20
int32_t __fastcall MENU_GetLogonRealmStatus();
//D2Launch.0x6FA26A70
int32_t __fastcall MENU_LogonRealm(const char* szRealmName, BOOL bAsync);
//D2Launch.0x6FA26D80
void __stdcall MENU_LogonRealmWaitCallback(DWORD dwUnused);
//D2Launch.0x6FA26DE0
int32_t __stdcall MENU_CreateAccountInfoOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA26FE0
int32_t __stdcall MENU_CreateAccountInfoCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA27020
void __fastcall MENU_LoadCharacterCreationCellFiles();
//D2Launch.0x6FA27750
int32_t __stdcall MENU_CloseSubChildrenCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Launch.0x6FA27790
void __fastcall MENU_ShowClassicMessageWithButton(const Unicode* wszMessage, D2PopupCallback pfCallback, BOOL bOkButton);
//D2Launch.0x6FA27940
void __fastcall MENU_ApplyLanguageLayout();
//D2Launch.0x6FA280F0
void __fastcall MENU_CreateBlankScreen();
