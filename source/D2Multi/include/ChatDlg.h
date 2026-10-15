#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Config.h>
#include <BnClient.h>
#include <D2Unicode.h>

struct D2CellFileStrc;
struct D2CompositeUnitStrc;
struct D2WinControlStrc;
struct D2WinControlInitStrc;
struct D2WinButtonStrc;
struct D2WinEditBoxStrc;
struct D2WinTextBoxStrc;
struct D2WinSmackStrc;
struct SMSGHANDLER_PARAMS;

#define CHATDLG_MAX_SUBCHILDREN 32
#define CHATDLG_MAX_CHAT_HISTORY 10

// Values returned to Game.exe by the module entry point (see D2_MODULES in Game/include/Main.h)
enum D2MultiReturnCode
{
	D2MULTI_RETURN_NONE = 0,
	D2MULTI_RETURN_CLIENT = 1,
	D2MULTI_RETURN_LAUNCHER = 4,
};

// State of the request currently waiting for an MCP answer
enum D2MultiMCPState
{
	D2MULTI_MCPSTATE_NONE = 0,
	D2MULTI_MCPSTATE_CREATEGAME = 1,
	D2MULTI_MCPSTATE_JOINGAME = 2,
	D2MULTI_MCPSTATE_GAMELIST = 3,
};

// Character save flags (see D2ClientSaveFlags in D2Game)
enum D2MultiSaveFlags
{
	D2MULTI_SAVEFLAG_HARDCORE = 0x04,
	D2MULTI_SAVEFLAG_DEAD = 0x08,
	D2MULTI_SAVEFLAG_EXPANSION = 0x20,
	D2MULTI_SAVEFLAG_LADDER = 0x40,
};

// Ladder types requested to the MCP. The class ladders follow the overall ladder (+1 for amazon, ..., +7 for assassin).
enum D2MultiLadderType
{
	D2MULTI_LADDER_CLASSIC_HARDCORE = 0x00,
	D2MULTI_LADDER_CLASSIC_STANDARD = 0x09,
	D2MULTI_LADDER_EXPANSION_HARDCORE = 0x13,
	D2MULTI_LADDER_EXPANSION_STANDARD = 0x1B,
};

// Flags of D2MultiLadderEntryStrc::dwFlags
enum D2MultiLadderFlags
{
	D2MULTI_LADDERFLAG_CLASSMASK = 0x0F,
	D2MULTI_LADDERFLAG_DEAD = 0x10,
	D2MULTI_LADDERFLAG_HARDCORE = 0x20,
	D2MULTI_LADDERFLAG_EXPANSION = 0x40,
};

// Placeholder for the ladder lines that weren't received yet
#define CHATDLG_LADDER_EMPTY_LINE "-"

// Indices in gaControlInits_6F9BC138
enum D2MultiControlInit
{
	CTRLINIT_CHAT_SEND = 0,
	CTRLINIT_CHAT_WHISPER = 1,
	CTRLINIT_CHAT_HELP = 2,
	CTRLINIT_CHAT_SQUELCH = 3,
	CTRLINIT_CHAT_UNSQUELCH = 4,
	CTRLINIT_CHAT_EMOTE = 5,
	CTRLINIT_CREATE = 6,
	CTRLINIT_CHANNEL = 7,
	CTRLINIT_JOIN = 8,
	CTRLINIT_LADDER = 9,
	CTRLINIT_QUIT = 10,
	CTRLINIT_USERLIST_PAGEUP = 11,
	CTRLINIT_USERLIST_PAGEDOWN = 12,
	CTRLINIT_USERLIST_UP = 13,
	CTRLINIT_USERLIST_DOWN = 14,
	CTRLINIT_AD_IMAGE = 15,
	CTRLINIT_AD_SMACK = 16,
	CTRLINIT_NEWS_ENTERCHAT = 17,
	CTRLINIT_NEWS_HELP = 18,
	CTRLINIT_PLAYERINFO = 19,
	CTRLINIT_USERLIST = 20,
	CTRLINIT_CHAT_TEXTBOX = 21,
	CTRLINIT_CHAT_EDITBOX = 22,
	CTRLINIT_CHANNEL_TITLE = 23,
	CTRLINIT_LOGO_LEFT = 24,
	CTRLINIT_NEWS_BACKGROUND = 25,
	CTRLINIT_NEWS_TEXTBOX = 26,
	CTRLINIT_LOGO_RIGHT = 27,
	CTRLINIT_GEM = 28,
	CTRLINIT_MESSAGEBOX = 29,
	CTRLINIT_30 = 30,
	CTRLINIT_31 = 31,
	CTRLINIT_32 = 32,
	CTRLINIT_POPUP_BACKGROUND = 33,
	CTRLINIT_POPUP_OK = 34,
	CTRLINIT_POPUP_CANCEL = 35,
	CTRLINIT_POPUP_TEXT = 36,
	CTRLINIT_WARNING_BACKGROUND = 37,
	CTRLINIT_WARNING_CANCEL = 38,
	CTRLINIT_WARNING_OK = 39,
	CTRLINIT_WARNING_TITLE = 40,
	CTRLINIT_WARNING_TEXT = 41,
	CTRLINIT_JOIN_BACKGROUND = 42,
	CTRLINIT_JOIN_TITLE = 43,
	CTRLINIT_JOIN_NAME_LABEL = 44,
	CTRLINIT_JOIN_PASSWORD_LABEL = 45,
	CTRLINIT_JOIN_GAMELIST_LABEL = 46,
	CTRLINIT_JOIN_NAME = 47,
	CTRLINIT_JOIN_PASSWORD = 48,
	CTRLINIT_JOIN_GAMELIST = 49,
	CTRLINIT_JOIN_OK = 50,
	CTRLINIT_JOIN_CLICKBOX1 = 51,
	CTRLINIT_JOIN_CLICKBOX2 = 52,
	CTRLINIT_JOIN_CLICKBOX3 = 53,
	CTRLINIT_JOIN_CLICKBOX4 = 54,
	CTRLINIT_JOIN_GAMEINFO = 55,
	CTRLINIT_CHANNELDLG_BACKGROUND = 56,
	CTRLINIT_CHANNELDLG_TITLE = 57,
	CTRLINIT_CHANNELDLG_NAME_LABEL = 58,
	CTRLINIT_CHANNELDLG_LIST_LABEL = 59,
	CTRLINIT_CHANNELDLG_NAME = 60,
	CTRLINIT_61 = 61,
	CTRLINIT_CHANNELDLG_LIST = 62,
	CTRLINIT_CHANNELDLG_OK = 63,
	CTRLINIT_CREATE_BACKGROUND = 64,
	CTRLINIT_CREATE_TITLE = 65,
	CTRLINIT_CREATE_NAME_LABEL = 66,
	CTRLINIT_CREATE_PASSWORD_LABEL = 67,
	CTRLINIT_CREATE_DESCRIPTION_LABEL = 68,
	CTRLINIT_CREATE_MAXPLAYERS_LABEL = 69,
	CTRLINIT_CREATE_LEVELDIFF_LABEL = 70,
	CTRLINIT_CREATE_LEVELDIFF_SUFFIX = 71,
	CTRLINIT_CREATE_NAME = 72,
	CTRLINIT_CREATE_PASSWORD = 73,
	CTRLINIT_CREATE_DESCRIPTION = 74,
	CTRLINIT_CREATE_MAXPLAYERS = 75,
	CTRLINIT_CREATE_LEVELDIFF = 76,
	CTRLINIT_CREATE_OK = 77,
	CTRLINIT_CREATE_LEVELDIFF_CHECKBOX = 78,
	CTRLINIT_CREATE_LEVELDIFF_GREYBOX = 79,
	CTRLINIT_CREATE_NORMAL = 80,
	CTRLINIT_CREATE_NIGHTMARE = 81,
	CTRLINIT_CREATE_HELL = 82,
	CTRLINIT_CREATE_NORMAL_LABEL = 83,
	CTRLINIT_CREATE_NIGHTMARE_LABEL = 84,
	CTRLINIT_CREATE_HELL_LABEL = 85,
	CTRLINIT_CREATE_MAXPLAYERS_UP = 86,
	CTRLINIT_CREATE_MAXPLAYERS_DOWN = 87,
	CTRLINIT_CREATE_LEVELDIFF_UP = 88,
	CTRLINIT_CREATE_LEVELDIFF_DOWN = 89,
	CTRLINIT_CREATE_LEVELDIFF_GREYARROWS = 90,
	CTRLINIT_CREATE_MAXPLAYERS_GREYBOX = 91,
	CTRLINIT_CREATE_MAXPLAYERS_GREYARROWS = 92,
	CTRLINIT_LADDERMENU_BACKGROUND = 93,
	CTRLINIT_LADDERMENU_TITLE = 94,
	CTRLINIT_LADDERMENU_HARDCORE = 95,
	CTRLINIT_LADDERMENU_96 = 96,
	CTRLINIT_LADDERMENU_STANDARD = 97,
	CTRLINIT_LADDERMENU_EXPANSION_HARDCORE = 98,
	CTRLINIT_LADDERMENU_EXPANSION_STANDARD = 99,
	CTRLINIT_CANCEL = 100,
	CTRLINIT_LADDER_BACKGROUND = 101,
	CTRLINIT_LADDER_TITLE = 102,
	CTRLINIT_LADDER_RANK_HEADER = 103,
	CTRLINIT_LADDER_NAME_HEADER = 104,
	CTRLINIT_LADDER_CLASS_HEADER = 105,
	CTRLINIT_LADDER_LEVEL_HEADER = 106,
	CTRLINIT_LADDER_EXPERIENCE_HEADER = 107,
	CTRLINIT_LADDER_LIST = 108,
	CTRLINIT_LADDER_CANCEL = 109,
	CTRLINIT_LADDER_TAB_OVERALL = 110,
	CTRLINIT_LADDER_TAB_AMAZON = 111,
	CTRLINIT_LADDER_TAB_SORCERESS = 112,
	CTRLINIT_LADDER_TAB_NECROMANCER = 113,
	CTRLINIT_LADDER_TAB_PALADIN = 114,
	CTRLINIT_LADDER_TAB_BARBARIAN = 115,
	CTRLINIT_LADDER_TAB_DRUID = 116,
	CTRLINIT_LADDER_TAB_ASSASSIN = 117,
	CTRLINIT_LADDER_TABLABEL_OVERALL = 118,
	CTRLINIT_LADDER_TABLABEL_AMAZON = 119,
	CTRLINIT_LADDER_TABLABEL_SORCERESS = 120,
	CTRLINIT_LADDER_TABLABEL_NECROMANCER = 121,
	CTRLINIT_LADDER_TABLABEL_PALADIN = 122,
	CTRLINIT_LADDER_TABLABEL_BARBARIAN = 123,
	CTRLINIT_LADDER_TABLABEL_DRUID = 124,
	CTRLINIT_LADDER_TABLABEL_ASSASSIN = 125,
	CTRLINIT_LADDER_PREVIOUS = 126,
	CTRLINIT_LADDER_NEXT = 127,
	CTRLINIT_LADDER_TIMER = 128,
	CTRLINIT_PROFILEEDIT_BACKGROUND = 129,
	CTRLINIT_PROFILEEDIT_NAME = 130,
	CTRLINIT_PROFILEEDIT_SEX = 131,
	CTRLINIT_PROFILEEDIT_LOCATION = 132,
	CTRLINIT_PROFILEEDIT_DESCRIPTION = 133,
	CTRLINIT_PROFILEVIEW_BACKGROUND = 134,
	CTRLINIT_PROFILEVIEW_NAME = 135,
	CTRLINIT_PROFILEVIEW_SEX = 136,
	CTRLINIT_PROFILEVIEW_LOCATION = 137,
	CTRLINIT_PROFILEVIEW_DESCRIPTION = 138,
	CTRLINIT_PROFILE_NAME_LABEL = 139,
	CTRLINIT_PROFILE_SEX_LABEL = 140,
	CTRLINIT_PROFILE_LOCATION_LABEL = 141,
	CTRLINIT_PROFILE_DESCRIPTION_LABEL = 142,
	CTRLINIT_PROFILE_CANCEL = 143,
	CTRLINIT_PROFILE_OK = 144,
	CTRLINIT_PROFILE_LADDER = 145,
	CTRLINIT_PROFILE_TITLE = 146,
	CTRLINIT_HELP_BACKGROUND = 147,
	CTRLINIT_HELP_TITLE = 148,
	CTRLINIT_HELP_TEXT = 149,
	CTRLINIT_HELP_OK = 150,
	CTRLINIT_GAMEQUEUE_TITLE = 151,
	CTRLINIT_GAMEQUEUE_TEXT = 152,
	CTRLINIT_153 = 153,
	CTRLINIT_GAMEQUEUE_CANCEL = 154,
	CTRLINIT_GAMEQUEUE_TIMER = 155,
	CTRLINIT_COUNT
};

#pragma pack(push, 1)
// Message queued for the chat text box. Filled from the Battle.net threads, emptied by the main loop.
struct D2MultiMessageStrc
{
	char* szText;						//0x00
	int32_t nColor;						//0x04
	BOOL bClear;						//0x08
	D2MultiMessageStrc* pNext;			//0x0C
};

// Message of the day sent by the realm, sorted by id
struct D2MultiMotdStrc
{
	char szText[0x200];					//0x000
	int32_t nId;						//0x200
	D2MultiMotdStrc* pNext;				//0x204
};

// Entry sent by the MCP for each character of a ladder
struct D2MultiLadderEntryStrc
{
	uint32_t nExperienceLow;			//0x00
	uint32_t nExperienceHigh;			//0x04
	uint32_t dwFlags;					//0x08 Class in the first 4 bits, then hardcore/dead/expansion flags, progression in bits 8-12 and level in bits 16-23
	char szName[1];						//0x0C variable length
};

// Parameters of a game creation request
struct D2MultiCreateGameStrc
{
	char szGameName[16];				//0x00
	char szGamePassword[16];			//0x10
	char szGameDescription[32];			//0x20
	uint32_t dwFlags;					//0x40
	uint8_t nUnk0x44;					//0x44
	uint8_t nLevelDifference;			//0x45 0xFF if not restricted
	uint8_t nMaxPlayers;				//0x46
};
#pragma pack(pop)

extern D2ConfigStrc* gpConfig_6F9C26F0;
extern BnClientInterface* gptComInt_6F9C19BC;
extern D2WinControlInitStrc gaControlInits_6F9BC138[CTRLINIT_COUNT];

extern uint16_t gnMCPRequestId_6F9BC03C;
extern uint16_t gnMCPPendingRequestIds_6F9C26F4[2];
extern int32_t gnMCPState_6F9C26F8;
extern int32_t gnModuleReturnCode_6F9C28B4;
extern char gszEmpty_6F9C28D8[8];
extern char gszCurrentChannel_6F9C2918[256];
extern char gszLastWhisperSender_6F9C1898[256];
extern BOOL gbShowJoinLeaveNotifications_6F9C2868;
extern BOOL gbIsOpenBattleNet_6F9C286C;
extern BOOL gbChatNotCreated_6F9C270C;
extern int32_t gnAdId_6F9C1A40;
extern char gszAdFileName_6F9C2A18[260];
extern char gszUniqueName_6F9C28E0[56];

extern D2CellFileStrc* gpCellFile_RadioButtonGrey_6F9C2780;

extern D2WinButtonStrc* gpCreateButton_6F9C2670;
extern D2WinButtonStrc* gpChannelButton_6F9C2674;
extern D2WinButtonStrc* gpJoinButton_6F9C2678;
extern D2WinButtonStrc* gpLadderButton_6F9C267C;
extern D2WinControlStrc* gpQuitButton_6F9C2680;
extern D2WinControlStrc* gpUserListPageUp_6F9C2684;
extern D2WinControlStrc* gpUserListPageDown_6F9C2688;
extern D2WinControlStrc* gpUserListUp_6F9C268C;
extern D2WinControlStrc* gpUserListDown_6F9C2690;
extern D2WinSmackStrc* gpAdSmack_6F9C2698;
extern D2WinControlStrc* gpSendButton_6F9C2658;
extern D2WinControlStrc* gpWhisperButton_6F9C265C;
extern D2WinControlStrc* gpSquelchButton_6F9C2664;
extern D2WinControlStrc* gpUnsquelchButton_6F9C2668;
extern D2WinControlStrc* gpEmoteButton_6F9C266C;
extern D2WinButtonStrc* gapUserButtons_6F9C26AC[11];
extern D2WinControlStrc* gpUserList_6F9C2758;
extern D2WinTextBoxStrc* gpNewsTextBox_6F9C2760;
extern D2WinEditBoxStrc* gpChatEditBox_6F9C28A8;
extern D2WinTextBoxStrc* gpChatTextBox_6F9C28A0;

//D2Multi.0x6F9A1000
BOOL __fastcall CHATDLG_DecodeCDKey(const char* szKey, uint32_t* pProductValue, uint32_t* pPublicValue);
//D2Multi.0x6F9A11F0
void __fastcall CHATDLG_CloseDialogs();
//D2Multi.0x6F9A1300
void __fastcall CHATDLG_LoadCellFiles();
//D2Multi.0x6F9A1B10
void __fastcall CHATDLG_FreeCellFiles();
//D2Multi.0x6F9A1F90
void __fastcall CHATDLG_FocusChatEditBox();
//D2Multi.0x6F9A1FA0
int32_t __stdcall CHATDLG_QuitButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A2130
int32_t __stdcall CHATDLG_UserListPageUpCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A2150
int32_t __stdcall CHATDLG_UserListPageDownCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A2170
int32_t __stdcall CHATDLG_UserListUpCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A2180
int32_t __stdcall CHATDLG_UserListDownCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A21A0
int32_t __stdcall CHATDLG_AdClickCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A2560
void __fastcall CHATDLG_ShowNews(BOOL bShow);
//D2Multi.0x6F9A2580
int32_t __stdcall CHATDLG_ChannelButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A2930
int32_t __stdcall CHATDLG_LadderButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A2C50
BOOL __fastcall CHATDLG_IsChatNotCreated();
//D2Multi.0x6F9A2C60
int32_t __stdcall CHATDLG_ChannelDialogOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A2E10
int32_t __stdcall CHATDLG_EnterChatButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A3180
int32_t __stdcall CHATDLG_ChannelListCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A33C0
int32_t __stdcall CHATDLG_ChannelEditBoxInputCallback(int32_t a1, int32_t a2, const char* pKey);
//D2Multi.0x6F9A33E0
int32_t __fastcall CHATDLG_ShowMessageBox(const Unicode* wszMessage, int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*));
//D2Multi.0x6F9A3560
void __fastcall CHATDLG_ResetDialogs();
//D2Multi.0x6F9A36B0
void __stdcall CHATDLG_MainLoopCallback(DWORD dwCounter);
//D2Multi.0x6F9A3DD0
int32_t __stdcall CHATDLG_MessageBoxCloseCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A3DF0
void __fastcall CHATDLG_CloseChannelDialog();
//D2Multi.0x6F9A3E60
void __fastcall CHATDLG_UpdateGameButtons(BOOL bCheckRealmConnection);
//D2Multi.0x6F9A4300
void __stdcall CHATDLG_WaitRealmConnectionCallback(DWORD dwCounter);
//D2Multi.0x6F9A4330
void __stdcall CHATDLG_WaitCharacterLogonCallback(DWORD dwCounter);
//D2Multi.0x6F9A4370
BOOL __fastcall CHATDLG_ConnectToRealm();
//D2Multi.0x6F9A4630
int32_t __stdcall CHATDLG_CancelRealmConnectionCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A4640
int32_t __fastcall CHATDLG_CheckRealmConnection();
//D2Multi.0x6F9A4660
void __fastcall CHATDLG_CreateChatControls();
//D2Multi.0x6F9A48C0
int32_t __stdcall CHATDLG_ChatEditBoxInputCallback(int32_t a1, int32_t nCursorPosition, const char* pKey);
//D2Multi.0x6F9A4A70
void __stdcall CHATDLG_ChatEditBoxChangeCallback(int32_t a1);
//D2Multi.0x6F9A4A80
void __fastcall CHATDLG_ProcessMessageQueue();
//D2Multi.0x6F9A4B90
int32_t __fastcall CHATDLG_Run(D2ConfigStrc* pConfig);
//D2Multi.0x6F9A5580
void __fastcall CHATDLG_GetClassName(Unicode* wszClassName, int32_t nClass);
//D2Multi.0x6F9A5660
int32_t __fastcall CHATDLG_NewsCallback(uint32_t nTimeStamp, const char* szNews);
//D2Multi.0x6F9A5910
int32_t __fastcall CHATDLG_NewsDoneCallback();
//D2Multi.0x6F9A5990
BOOL __fastcall CHATDLG_CreateGame(D2MultiCreateGameStrc* pCreateGame, const char* szServerIp);
//D2Multi.0x6F9A5D40
BOOL __fastcall CHATDLG_JoinGame(uint16_t nGameToken, const char* szGameName, const char* szGamePassword, const char* szServerIp);
//D2Multi.0x6F9A6100
int32_t __fastcall CHATDLG_RunModule(D2ConfigStrc* pConfig);
//D2Multi.0x6F9A6130
BOOL __fastcall CHATDLG_AddChatMessage(const Unicode* wszMessage, int32_t nColor);
//D2Multi.0x6F9A6150
BOOL __fastcall CHATDLG_SetChannelTitle(const Unicode* wszTitle);
//D2Multi.0x6F9A6180
void __stdcall CHATDLG_ChannelEditBoxChangeCallback(int32_t a1);
//D2Multi.0x6F9A61E0
int32_t __stdcall CHATDLG_ReturnToLauncherCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A6200
int32_t __stdcall CHATDLG_ChatEditBoxEnterCallback(const Unicode* wszText);
//D2Multi.0x6F9A62D0
int32_t __stdcall CHATDLG_WarningOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A6550
BOOL __fastcall CHATDLG_HandleNotifyCommand(const char* szText, const char* szCommand);
//D2Multi.0x6F9A66F0
BOOL __fastcall CHATDLG_HandleReplyCommand(const char* szText, const char* szCommand);
//D2Multi.0x6F9A6AC0
int32_t __stdcall CHATDLG_WarningCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A6B20
BOOL __fastcall CHATDLG_SendChatText(const char* szText, BOOL bWhisper);
//D2Multi.0x6F9A7250
int32_t __fastcall CHATDLG_CompareCommand(const char* szText, const char* szCommand);
//D2Multi.0x6F9A72D0
D2WinControlStrc* __fastcall CHATDLG_AddSubChild(int32_t nControlInit);
//D2Multi.0x6F9A7320
void __fastcall CHATDLG_DestroySubChildren();
//D2Multi.0x6F9A7370
void __fastcall CHATDLG_ShowPopup(const Unicode* wszMessage, int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*));
//D2Multi.0x6F9A74E0
void __fastcall CHATDLG_ShowWaitPopup(const Unicode* wszMessage, int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*));
//D2Multi.0x6F9A7650
int32_t __stdcall CHATDLG_ClosePopupCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A76A0
int32_t __stdcall CHATDLG_PopupButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A76C0
int32_t __fastcall CHATDLG_ResetMainButtons();
//D2Multi.0x6F9A7760
int32_t __stdcall CHATDLG_LadderMenuCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A7910
int32_t __stdcall CHATDLG_LadderCancelCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A7C30
int32_t __stdcall CHATDLG_LadderTimerCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A7D60
void __fastcall CHATDLG_RequestCharacterLadder(const char* szCharacterName, BOOL bHardcore, BOOL bExpansion);
//D2Multi.0x6F9A7DE0
int32_t __stdcall CHATDLG_LadderPreviousCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A7E10
int32_t __stdcall CHATDLG_LadderNextCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A7E50
int32_t __stdcall CHATDLG_LadderMenuCloseCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A7F60
int32_t __stdcall CHATDLG_LadderHardcoreCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A8230
void __stdcall CHATDLG_EmptyCallback();
//D2Multi.0x6F9A8240
void __fastcall CHATDLG_LadderDataCallback(int32_t nStart, int32_t nCount, int32_t nNameSize, uint8_t nLadderType, void* pEntries);
//D2Multi.0x6F9A8720
void __fastcall CHATDLG_CreateLadderControls();
//D2Multi.0x6F9A8C90
void __fastcall CHATDLG_ShowStandardCharacterLadder();
//D2Multi.0x6F9A8F50
void __fastcall CHATDLG_ShowHardcoreCharacterLadder();
//D2Multi.0x6F9A9210
void __fastcall CHATDLG_ShowExpansionStandardCharacterLadder();
//D2Multi.0x6F9A94D0
void __fastcall CHATDLG_ShowExpansionHardcoreCharacterLadder();
//D2Multi.0x6F9A9790
int32_t __stdcall CHATDLG_LadderStandardCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A9A60
int32_t __stdcall CHATDLG_LadderExpansionStandardCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9A9D30
int32_t __stdcall CHATDLG_LadderExpansionHardcoreCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AA000
void __fastcall CHATDLG_ClearLadderList();
//D2Multi.0x6F9AA080
int32_t __stdcall CHATDLG_LadderTabOverallCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AA230
int32_t __stdcall CHATDLG_LadderTabAmazonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AA3E0
int32_t __stdcall CHATDLG_LadderTabSorceressCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AA590
int32_t __stdcall CHATDLG_LadderTabNecromancerCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AA740
int32_t __stdcall CHATDLG_LadderTabPaladinCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AA8F0
int32_t __stdcall CHATDLG_LadderTabBarbarianCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AAAA0
int32_t __stdcall CHATDLG_LadderTabDruidCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AAC50
int32_t __stdcall CHATDLG_LadderTabAssassinCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AAE00
void __fastcall CHATDLG_DisableRadioButton(D2WinControlStrc* pButton);
//D2Multi.0x6F9AAE20
void __stdcall CHATDLG_WaitProfileCallback(DWORD dwCounter);
//D2Multi.0x6F9AAE80
BOOL __fastcall CHATDLG_ReadProfile(const char* szAccountName, char* szSex, char* szLocation, char* szDescription);
//D2Multi.0x6F9AB080
int32_t __stdcall CHATDLG_CancelProfileCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AB090
BOOL __fastcall CHATDLG_WriteProfile(const char* szAccountName, char* szSex, char* szLocation, char* szDescription);
//D2Multi.0x6F9AB0D0
int32_t __stdcall CHATDLG_GemButtonCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AB1D0
int32_t __stdcall CHATDLG_HelpOkCallback(SMSGHANDLER_PARAMS* pMsg);
//D2Multi.0x6F9AB1E0
void __fastcall CHATDLG_MotdCallback(int32_t nId, int32_t a2, const char* szText);
//D2Multi.0x6F9AB350
int32_t __fastcall CHATDLG_CancelGameQueue();
//D2Multi.0x6F9AB370
const char* __fastcall CHATDLG_GetAccountName(const char* szUserName);
//D2Multi.0x6F9AB390
void __fastcall CHATDLG_GetCharacterName(const char* szUserName, char* szCharacterName);
