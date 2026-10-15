#include "ChatDlg.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include <D2BitManip.h>
#include <D2Lang.h>
#include <D2StrTable.h>
#include <D2Unicode.h>
#include <D2Sound.h>
#include <D2MCPClient.h>
#include <Fog.h>
#include <Storm.h>
#include <D2WinAnimImage.h>
#include <D2WinArchive.h>
#include <D2WinButton.h>
#include <D2WinComp.h>
#include <D2WinEditBox.h>
#include <D2WinMain.h>
#include <D2WinSmack.h>
#include <D2WinTextBox.h>
#include <D2WinTimer.h>

#include "ComCallback.h"
#include "Gate.h"

#define CHATDLG_ARCHIVE_DIR "DATA\\GLOBAL"


#pragma pack(push, 1)
// Index of the font used by a text control (and an unused padding)
struct D2MultiTextStyleStrc
{
	int32_t nFont;
	int32_t nUnused;
};

// Position of the scrollbar attached to a text box
struct D2MultiScrollBarInfoStrc
{
	int32_t nX;
	int32_t nY;
	int32_t nHeight;
};
#pragma pack(pop)

const char* gaszProfileKeys_6F9BC030[3] =
{
	"profile\\sex",
	"profile\\location",
	"profile\\description",
};

uint16_t gnMCPRequestId_6F9BC03C = 1;
int32_t gnLadderLastRequestedPosition_6F9BC040 = -1;
int32_t gnLadderCharacterPosition_6F9BC044 = -1;
BOOL gbLadderNeedsRefresh_6F9BC048 = TRUE;
BOOL gbLadderIsExpansion_6F9BC04C = TRUE;
int32_t gnChatHistoryIndex_6F9BC050 = -1;
int32_t dword_6F9BC054 = -1;
uint8_t gnLadderType_6F9BC058 = 0xFF;
int32_t gnLadderPosition_6F9BC05C = -1;
uint8_t gnLadderRequestedType_6F9BC060 = 0xFF;
int32_t gnLadderRequestedPosition_6F9BC064 = -1;

D2MultiTextStyleStrc gaTextStyle_6F9BC068[1] = { { 4, 0 } };
D2MultiTextStyleStrc gaTextStyle_6F9BC070[1] = { { 3, 0 } };
D2MultiTextStyleStrc gaTextStyle_6F9BC078[1] = { { 2, 0 } };
D2MultiTextStyleStrc gaTextStyle_6F9BC080[1] = { { 1, 0 } };
D2MultiTextStyleStrc gaTextStyle_6F9BC088[1] = { { 7, 0 } };

D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC090[1] = { { 400, 390, 314 } };
D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC09C[1] = { { 592, 393, 173 } };
D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0A8[1] = { { 753, 394, 196 } };
D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0B4[1] = { { 753, 393, 197 } };
D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0C0[1] = { { 756, 391, 238 } };
D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0CC[1] = { { 756, 391, 266 } };
D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0D8[1] = { { 753, 391, 266 } };

D2CellFileStrc* gpCellFile_Bnet_6F9C2718;
D2CellFileStrc* gpCellFile_WaitingRoomBkgd_6F9C271C;
D2CellFileStrc* gpCellFile_PopUpLargest2_6F9C2720;
D2CellFileStrc* gpCellFile_MediumButtonBlank2_6F9C2724;
D2CellFileStrc* gpCellFile_CursorOHand_6F9C2728;
D2CellFileStrc* gpCellFile_CursorLRotate_6F9C272C;
D2CellFileStrc* gpCellFile_ScrollBar_6F9C2730;
D2CellFileStrc* gpCellFile_JoinGameScrollBars_6F9C2734;
D2CellFileStrc* gpCellFile_Unused_6F9C2738;
D2CellFileStrc* gpCellFile_ChatLeftButtons_6F9C273C;
D2CellFileStrc* gpCellFile_ChatLeftButtons1_6F9C2740;
D2CellFileStrc* gpCellFile_ChatLeftButtons2_6F9C2744;
D2CellFileStrc* gpCellFile_ChatRightButtons_6F9C2748;
D2CellFileStrc* gpCellFile_ChatRightTopButtons_6F9C274C;
D2CellFileStrc* gpCellFile_ChatArrows_6F9C2750;
D2CellFileStrc* gpCellFile_JoinGameBckg_6F9C2764;
D2CellFileStrc* gpCellFile_BlankBckg2_6F9C2768;
D2CellFileStrc* gpCellFile_GemButton_6F9C276C;
D2CellFileStrc* gpCellFile_GameButtonBlank_6F9C2770;
D2CellFileStrc* gpCellFile_JoinGameClickBox_6F9C2774;
D2CellFileStrc* gpCellFile_GreyLevelBox_6F9C2778;
D2CellFileStrc* gpCellFile_RadioButton_6F9C277C;
D2CellFileStrc* gpCellFile_RadioButtonGrey_6F9C2780;
D2CellFileStrc* gpCellFile_PopUpOK_6F9C2784;
D2CellFileStrc* gpCellFile_CancelButtonBlank2_6F9C2788;
D2CellFileStrc* gpCellFile_OverallTab_6F9C278C;
D2CellFileStrc* gpCellFile_AmazonTab_6F9C2790;
D2CellFileStrc* gpCellFile_SorceressTab_6F9C2794;
D2CellFileStrc* gpCellFile_NecromancerTab_6F9C2798;
D2CellFileStrc* gpCellFile_PaladinTab_6F9C279C;
D2CellFileStrc* gpCellFile_BarbarianTab_6F9C27A0;
D2CellFileStrc* gpCellFile_DruidTab_6F9C27A4;
D2CellFileStrc* gpCellFile_AssassinTab_6F9C27A8;
D2CellFileStrc* gpCellFile_SquelchAura_6F9C27CC;
D2CellFileStrc* gpCellFile_SelectAura_6F9C27D0;
D2CellFileStrc* gpCellFile_NumberArrows1_6F9C27D4;
D2CellFileStrc* gpCellFile_NumberArrows2_6F9C27D8;
D2CellFileStrc* gpCellFile_NumberArrows3_6F9C27DC;
D2CellFileStrc* gpCellFile_NumberArrows4_6F9C27E0;
D2CellFileStrc* gpCellFile_NumberGreyArrows_6F9C27E4;
D2CellFileStrc* gpCellFile_CreateJoinBckg_6F9C27E8;
D2CellFileStrc* gpCellFile_OkayButton_6F9C27EC;
D2CellFileStrc* gpCellFile_CreateGameBckg_6F9C2820;
D2CellFileStrc* gpCellFile_CreateGameButton_6F9C2824;
D2CellFileStrc* gpCellFile_WideButtonBlank_6F9C282C;
D2CellFileStrc* gpCellFile_CancelButtonBlank_6F9C2840;
D2CellFileStrc* gpCellFile_YesNoButtonBlank_6F9C2844;
D2CellFileStrc* gpCellFile_LadderChoiceEXP_6F9C2848;
D2CellFileStrc* gpCellFile_HardcoreLadderBckg_6F9C284C;
D2CellFileStrc* gpCellFile_PlayerProfileBckg2_6F9C2850;
D2CellFileStrc* gpCellFile_PlayerProfileBckg_6F9C2854;
D2CellFileStrc* gpCellFile_HelpBckg_6F9C2858;
D2CellFileStrc* gpCellFile_D2LogoBlackBnet_6F9C285C;
D2CellFileStrc* gpCellFile_D2LogoBnet_6F9C2860;

D2AnimatedImageDescriptor gaLogoAnimations_6F9BC0E8[5] =
{
	{ &gpCellFile_D2LogoBlackBnet_6F9C285C, &gpCellFile_D2LogoBnet_6F9C2860, DRAWMODE_MODULATE, 1 },
	{ &gpCellFile_D2LogoBlackBnet_6F9C285C, &gpCellFile_D2LogoBnet_6F9C2860, DRAWMODE_MODULATE, 1 },
	{ &gpCellFile_D2LogoBlackBnet_6F9C285C, &gpCellFile_D2LogoBnet_6F9C2860, DRAWMODE_MODULATE, 1 },
	{ &gpCellFile_D2LogoBlackBnet_6F9C285C, &gpCellFile_D2LogoBnet_6F9C2860, DRAWMODE_MODULATE, 1 },
	{ &gpCellFile_D2LogoBlackBnet_6F9C285C, &gpCellFile_D2LogoBnet_6F9C2860, DRAWMODE_MODULATE, 1 },
};

uint8_t gaListData_6F9C2878[16];
uint8_t gaListData_6F9C2888[16];
D2MultiTextStyleStrc gaTextStyle_6F9C2898[2];

D2WinControlInitStrc gaControlInits_6F9BC138[CTRLINIT_COUNT] =
{
	{ D2WIN_BUTTON, 27, 470, 80, 20, 0, 5305, &gpCellFile_ChatLeftButtons_6F9C273C, COMCALLBACK_SendButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CHAT_SEND
	{ D2WIN_BUTTON, 107, 470, 80, 20, 0, 5306, &gpCellFile_ChatLeftButtons_6F9C273C, COMCALLBACK_WhisperButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CHAT_WHISPER
	{ D2WIN_BUTTON, 187, 470, 80, 20, 0, 5308, &gpCellFile_ChatLeftButtons_6F9C273C, COMCALLBACK_HelpButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CHAT_HELP
	{ D2WIN_BUTTON, 27, 490, 72, 20, 0, 5307, &gpCellFile_ChatLeftButtons1_6F9C2740, COMCALLBACK_SquelchButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CHAT_SQUELCH
	{ D2WIN_BUTTON, 99, 490, 96, 20, 0, 5310, &gpCellFile_ChatLeftButtons2_6F9C2744, COMCALLBACK_UnsquelchButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CHAT_UNSQUELCH
	{ D2WIN_BUTTON, 195, 490, 72, 20, 0, 5309, &gpCellFile_ChatLeftButtons1_6F9C2740, COMCALLBACK_EmoteButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CHAT_EMOTE
	{ D2WIN_BUTTON, 533, 469, 120, 20, 0, 5312, &gpCellFile_ChatRightTopButtons_6F9C274C, GATE_CreateButtonCallback, nullptr, nullptr, (void*)1 },	// CTRLINIT_CREATE
	{ D2WIN_BUTTON, 535, 490, 80, 20, 0, 5314, &gpCellFile_ChatRightButtons_6F9C2748, CHATDLG_ChannelButtonCallback, nullptr, nullptr, (void*)1 },	// CTRLINIT_CHANNEL
	{ D2WIN_BUTTON, 652, 469, 120, 20, 0, 5313, &gpCellFile_ChatRightTopButtons_6F9C274C, GATE_JoinButtonCallback, nullptr, nullptr, (void*)1 },	// CTRLINIT_JOIN
	{ D2WIN_BUTTON, 614, 490, 80, 20, 0, 5315, &gpCellFile_ChatRightButtons_6F9C2748, CHATDLG_LadderButtonCallback, nullptr, nullptr, (void*)1 },	// CTRLINIT_LADDER
	{ D2WIN_BUTTON, 693, 490, 80, 20, 0, 5316, &gpCellFile_ChatRightButtons_6F9C2748, CHATDLG_QuitButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_QUIT
	{ D2WIN_BUTTON, 725, 583, 25, 30, 0, 0, &gpCellFile_ChatArrows_6F9C2750, CHATDLG_UserListPageUpCallback, nullptr, nullptr, nullptr },	// CTRLINIT_USERLIST_PAGEUP
	{ D2WIN_BUTTON, 751, 583, 25, 30, 0, 0, &gpCellFile_ChatArrows_6F9C2750, CHATDLG_UserListPageDownCallback, (void*)2, nullptr, nullptr },	// CTRLINIT_USERLIST_PAGEDOWN
	{ D2WIN_BUTTON, 725, 528, 25, 30, 0, 0, &gpCellFile_ChatArrows_6F9C2750, CHATDLG_UserListUpCallback, (void*)4, nullptr, nullptr },	// CTRLINIT_USERLIST_UP
	{ D2WIN_BUTTON, 751, 528, 25, 30, 0, 0, &gpCellFile_ChatArrows_6F9C2750, CHATDLG_UserListDownCallback, (void*)6, nullptr, nullptr },	// CTRLINIT_USERLIST_DOWN
	{ D2WIN_IMAGE, 145, 69, 510, 60, 0, 0, nullptr, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_AD_IMAGE
	{ D2WIN_SMACK, 145, 69, 510, 60, 0, 0, nullptr, CHATDLG_AdClickCallback, nullptr, nullptr, nullptr },	// CTRLINIT_AD_SMACK
	{ D2WIN_BUTTON, 27, 480, 120, 20, 0, 11126, &gpCellFile_ChatRightTopButtons_6F9C274C, CHATDLG_EnterChatButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_NEWS_ENTERCHAT
	{ D2WIN_BUTTON, 146, 480, 120, 20, 0, 5308, &gpCellFile_ChatRightTopButtons_6F9C274C, COMCALLBACK_HelpButtonCallback, nullptr, nullptr, nullptr },	// CTRLINIT_NEWS_HELP
	{ D2WIN_TEXTBOX, 143, 588, 230, 87, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_PLAYERINFO
	{ D2WIN_ACCOUNTLIST, 40, 591, 720, 75, 0, 0, nullptr, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_USERLIST
	{ D2WIN_TEXTBOX, 28, 410, 354, 298, 0, 0, &gpCellFile_ScrollBar_6F9C2730, nullptr, (void*)gaScrollBarInfo_6F9BC090, (void*)gaTextStyle_6F9BC068, (void*)4 },	// CTRLINIT_CHAT_TEXTBOX
	{ D2WIN_EDITBOX, 28, 450, 335, 32, 0, 0, nullptr, nullptr, (void*)CHATDLG_ChatEditBoxEnterCallback, (void*)gaTextStyle_6F9BC068, (void*)22 },	// CTRLINIT_CHAT_EDITBOX
	{ D2WIN_TEXTBOX, 28, 138, 354, 60, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, (void*)2 },	// CTRLINIT_CHANNEL_TITLE
	{ D2WIN_ANIMIMAGE, 84, 52, 147, 68, 0, 0, nullptr, nullptr, (void*)gaLogoAnimations_6F9BC0E8, nullptr, nullptr },	// CTRLINIT_LOGO_LEFT
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_BlankBckg2_6F9C2768, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_NEWS_BACKGROUND
	{ D2WIN_TEXTBOX, 447, 398, 290, 269, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, (void*)2 },	// CTRLINIT_NEWS_TEXTBOX
	{ D2WIN_ANIMIMAGE, 726, 52, 147, 68, 0, 0, nullptr, nullptr, (void*)gaLogoAnimations_6F9BC0E8, nullptr, nullptr },	// CTRLINIT_LOGO_RIGHT
	{ D2WIN_BUTTON, 398, 474, 12, 13, 0, 0, &gpCellFile_GemButton_6F9C276C, CHATDLG_GemButtonCallback, nullptr, nullptr, (void*)4 },	// CTRLINIT_GEM
	{ D2WIN_TEXTBOX, 438, 300, 326, 150, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_MESSAGEBOX
	{ D2WIN_LIST, 438, 240, 326, 50, 0, 0, nullptr, nullptr, (void*)gaListData_6F9C2878, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_30
	{ D2WIN_TEXTBOX, 438, 200, 326, 50, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_31
	{ D2WIN_LIST, 438, 240, 326, 50, 0, 0, nullptr, nullptr, (void*)gaListData_6F9C2888, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_32
	{ D2WIN_IMAGE, 268, 350, 264, 176, 0, 0, &gpCellFile_PopUpOK_6F9C2784, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_POPUP_BACKGROUND
	{ D2WIN_BUTTON, 351, 337, 96, 32, 13, 5102, &gpCellFile_CancelButtonBlank2_6F9C2788, CHATDLG_PopupButtonCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_POPUP_OK
	{ D2WIN_BUTTON, 351, 337, 96, 32, 13, 5103, &gpCellFile_CancelButtonBlank2_6F9C2788, CHATDLG_PopupButtonCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_POPUP_CANCEL
	{ D2WIN_TEXTBOX, 268, 320, 264, 120, 10, 8, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC088, (void*)2 },	// CTRLINIT_POPUP_TEXT
	{ D2WIN_IMAGE, 158, 460, 485, 290, 0, 0, &gpCellFile_PopUpLargest2_6F9C2720, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_WARNING_BACKGROUND
	{ D2WIN_BUTTON, 205, 440, 128, 35, 13, 5103, &gpCellFile_MediumButtonBlank2_6F9C2724, CHATDLG_WarningCancelCallback, nullptr, nullptr, nullptr },	// CTRLINIT_WARNING_CANCEL
	{ D2WIN_BUTTON, 336, 454, 128, 35, 0, 5102, &gpCellFile_MediumButtonBlank2_6F9C2724, CHATDLG_WarningOkCallback, nullptr, nullptr, nullptr },	// CTRLINIT_WARNING_OK
	{ D2WIN_TEXTBOX, 158, 240, 485, 40, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_WARNING_TITLE
	{ D2WIN_TEXTBOX, 172, 420, 457, 180, 10, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC088, nullptr },	// CTRLINIT_WARNING_TEXT
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_JoinGameBckg_6F9C2764, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_JOIN_BACKGROUND
	{ D2WIN_TEXTBOX, 496, 106, 200, 22, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_JOIN_TITLE
	{ D2WIN_TEXTBOX, 428, 121, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_JOIN_NAME_LABEL
	{ D2WIN_TEXTBOX, 602, 121, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_JOIN_PASSWORD_LABEL
	{ D2WIN_TEXTBOX, 431, 212, 200, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_JOIN_GAMELIST_LABEL
	{ D2WIN_EDITBOX, 432, 148, 155, 20, 0, 0, nullptr, nullptr, (void*)GATE_JoinGameCallback, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_JOIN_NAME
	{ D2WIN_EDITBOX, 606, 148, 155, 20, 0, 0, nullptr, nullptr, (void*)GATE_JoinGameCallback, (void*)gaTextStyle_6F9BC068, (void*)1 },	// CTRLINIT_JOIN_PASSWORD
	{ D2WIN_TEXTBOX, 432, 393, 160, 173, 0, 0, &gpCellFile_JoinGameScrollBars_6F9C2734, GATE_GameListCallback, (void*)gaScrollBarInfo_6F9BC09C, (void*)gaTextStyle_6F9BC068, (void*)5 },	// CTRLINIT_JOIN_GAMELIST
	{ D2WIN_BUTTON, 594, 433, 172, 32, 13, 5151, &gpCellFile_GameButtonBlank_6F9C2770, GATE_JoinGameCallback, nullptr, nullptr, nullptr },	// CTRLINIT_JOIN_OK
	{ D2WIN_BUTTON, 471, 185, 15, 16, 0, 0, &gpCellFile_JoinGameClickBox_6F9C2774, GATE_ClickBoxCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_JOIN_CLICKBOX1
	{ D2WIN_BUTTON, 554, 185, 15, 16, 0, 0, &gpCellFile_JoinGameClickBox_6F9C2774, GATE_ClickBoxCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_JOIN_CLICKBOX2
	{ D2WIN_BUTTON, 622, 185, 15, 16, 0, 0, &gpCellFile_JoinGameClickBox_6F9C2774, GATE_ClickBoxCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_JOIN_CLICKBOX3
	{ D2WIN_BUTTON, 713, 185, 15, 16, 0, 0, &gpCellFile_JoinGameClickBox_6F9C2774, GATE_ClickBoxCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_JOIN_CLICKBOX4
	{ D2WIN_TEXTBOX, 609, 393, 143, 194, 0, 0, &gpCellFile_JoinGameScrollBars_6F9C2734, nullptr, (void*)gaScrollBarInfo_6F9BC0A8, (void*)gaTextStyle_6F9C2898, (void*)6 },	// CTRLINIT_JOIN_GAMEINFO
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_CreateJoinBckg_6F9C27E8, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_CHANNELDLG_BACKGROUND
	{ D2WIN_TEXTBOX, 496, 114, 200, 22, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_CHANNELDLG_TITLE
	{ D2WIN_TEXTBOX, 427, 135, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CHANNELDLG_NAME_LABEL
	{ D2WIN_TEXTBOX, 427, 187, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CHANNELDLG_LIST_LABEL
	{ D2WIN_EDITBOX, 432, 162, 155, 20, 0, 0, nullptr, nullptr, (void*)CHATDLG_ChannelDialogOkCallback, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_CHANNELDLG_NAME
	{ D2WIN_EDITBOX, 606, 162, 158, 20, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_61
	{ D2WIN_TEXTBOX, 432, 397, 321, 200, 0, 0, &gpCellFile_JoinGameScrollBars_6F9C2734, CHATDLG_ChannelListCallback, (void*)gaScrollBarInfo_6F9BC0B4, (void*)gaTextStyle_6F9BC068, (void*)5 },	// CTRLINIT_CHANNELDLG_LIST
	{ D2WIN_BUTTON, 671, 433, 96, 32, 13, 5102, &gpCellFile_CancelButtonBlank_6F9C2840, CHATDLG_ChannelDialogOkCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CHANNELDLG_OK
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_CreateGameBckg_6F9C2820, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_BACKGROUND
	{ D2WIN_TEXTBOX, 496, 111, 200, 22, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_CREATE_TITLE
	{ D2WIN_TEXTBOX, 427, 134, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CREATE_NAME_LABEL
	{ D2WIN_TEXTBOX, 427, 188, 300, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CREATE_PASSWORD_LABEL
	{ D2WIN_TEXTBOX, 427, 243, 300, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CREATE_DESCRIPTION_LABEL
	{ D2WIN_TEXTBOX, 632, 306, 300, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, (void*)16 },	// CTRLINIT_CREATE_MAXPLAYERS_LABEL
	{ D2WIN_TEXTBOX, 632, 342, 300, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, (void*)16 },	// CTRLINIT_CREATE_LEVELDIFF_LABEL
	{ D2WIN_TEXTBOX, 705, 342, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CREATE_LEVELDIFF_SUFFIX
	{ D2WIN_EDITBOX, 432, 162, 158, 20, 0, 0, nullptr, nullptr, (void*)GATE_CreateGameCallback, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_CREATE_NAME
	{ D2WIN_EDITBOX, 432, 217, 158, 20, 0, 0, nullptr, nullptr, (void*)GATE_CreateGameCallback, (void*)gaTextStyle_6F9BC068, (void*)1 },	// CTRLINIT_CREATE_PASSWORD
	{ D2WIN_EDITBOX, 432, 268, 333, 20, 0, 0, nullptr, nullptr, (void*)GATE_CreateGameCallback, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_CREATE_DESCRIPTION
	{ D2WIN_EDITBOX, 657, 308, 27, 20, 0, 0, nullptr, nullptr, (void*)GATE_CreateGameCallback, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_CREATE_MAXPLAYERS
	{ D2WIN_EDITBOX, 657, 342, 27, 20, 0, 0, nullptr, nullptr, (void*)GATE_CreateGameCallback, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_CREATE_LEVELDIFF
	{ D2WIN_BUTTON, 594, 433, 172, 32, 13, 5150, &gpCellFile_GameButtonBlank_6F9C2770, GATE_CreateGameCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_OK
	{ D2WIN_BUTTON, 431, 341, 15, 16, 0, 0, &gpCellFile_JoinGameClickBox_6F9C2774, GATE_LevelDifferenceCheckboxCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_CREATE_LEVELDIFF_CHECKBOX
	{ D2WIN_IMAGE, 647, 346, 33, 26, 0, 0, &gpCellFile_GreyLevelBox_6F9C2778, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_LEVELDIFF_GREYBOX
	{ D2WIN_BUTTON, 430, 381, 16, 16, 0, 0, &gpCellFile_RadioButton_6F9C277C, GATE_NormalDifficultyCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_CREATE_NORMAL
	{ D2WIN_BUTTON, 555, 381, 16, 16, 0, 0, &gpCellFile_RadioButton_6F9C277C, GATE_NightmareDifficultyCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_CREATE_NIGHTMARE
	{ D2WIN_BUTTON, 698, 381, 16, 16, 0, 0, &gpCellFile_RadioButton_6F9C277C, GATE_HellDifficultyCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_CREATE_HELL
	{ D2WIN_TEXTBOX, 459, 380, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CREATE_NORMAL_LABEL
	{ D2WIN_TEXTBOX, 579, 380, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CREATE_NIGHTMARE_LABEL
	{ D2WIN_TEXTBOX, 723, 380, 150, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_CREATE_HELL_LABEL
	{ D2WIN_BUTTON, 681, 296, 15, 12, 0, 0, &gpCellFile_NumberArrows3_6F9C27DC, GATE_MaxPlayersUpCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_MAXPLAYERS_UP
	{ D2WIN_BUTTON, 681, 310, 15, 12, 0, 0, &gpCellFile_NumberArrows4_6F9C27E0, GATE_MaxPlayersDownCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_MAXPLAYERS_DOWN
	{ D2WIN_BUTTON, 681, 332, 15, 12, 0, 0, &gpCellFile_NumberArrows1_6F9C27D4, GATE_LevelDifferenceUpCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_LEVELDIFF_UP
	{ D2WIN_BUTTON, 681, 346, 15, 12, 0, 0, &gpCellFile_NumberArrows2_6F9C27D8, GATE_LevelDifferenceDownCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_LEVELDIFF_DOWN
	{ D2WIN_BUTTON, 681, 346, 15, 26, 0, 0, &gpCellFile_NumberGreyArrows_6F9C27E4, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_LEVELDIFF_GREYARROWS
	{ D2WIN_IMAGE, 647, 311, 33, 26, 0, 0, &gpCellFile_GreyLevelBox_6F9C2778, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_MAXPLAYERS_GREYBOX
	{ D2WIN_BUTTON, 681, 311, 15, 26, 0, 0, &gpCellFile_NumberGreyArrows_6F9C27E4, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_CREATE_MAXPLAYERS_GREYARROWS
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_LadderChoiceEXP_6F9C2848, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_LADDERMENU_BACKGROUND
	{ D2WIN_TEXTBOX, 496, 112, 200, 22, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_LADDERMENU_TITLE
	{ D2WIN_BUTTON, 463, 238, 272, 32, 0, 5318, &gpCellFile_WideButtonBlank_6F9C282C, CHATDLG_LadderHardcoreCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDERMENU_HARDCORE
	{ D2WIN_BUTTON, 463, 238, 272, 35, 0, 1656, &gpCellFile_WideButtonBlank_6F9C282C, CHATDLG_LadderMenuCloseCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDERMENU_96
	{ D2WIN_BUTTON, 463, 188, 272, 32, 0, 5317, &gpCellFile_WideButtonBlank_6F9C282C, CHATDLG_LadderStandardCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDERMENU_STANDARD
	{ D2WIN_BUTTON, 463, 338, 272, 32, 0, 10091, &gpCellFile_WideButtonBlank_6F9C282C, CHATDLG_LadderExpansionHardcoreCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDERMENU_EXPANSION_HARDCORE
	{ D2WIN_BUTTON, 463, 288, 272, 32, 0, 10090, &gpCellFile_WideButtonBlank_6F9C282C, CHATDLG_LadderExpansionStandardCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDERMENU_EXPANSION_STANDARD
	{ D2WIN_BUTTON, 433, 433, 96, 32, 0, 5103, &gpCellFile_CancelButtonBlank_6F9C2840, CHATDLG_LadderMenuCancelCallback, nullptr, nullptr, nullptr },	// CTRLINIT_CANCEL
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_HardcoreLadderBckg_6F9C284C, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_LADDER_BACKGROUND
	{ D2WIN_TEXTBOX, 421, 136, 350, 50, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC088, (void*)2 },	// CTRLINIT_LADDER_TITLE
	{ D2WIN_TEXTBOX, 434, 162, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_LADDER_RANK_HEADER
	{ D2WIN_TEXTBOX, 468, 162, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_LADDER_NAME_HEADER
	{ D2WIN_TEXTBOX, 596, 162, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_LADDER_CLASS_HEADER
	{ D2WIN_TEXTBOX, 640, 162, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_LADDER_LEVEL_HEADER
	{ D2WIN_TEXTBOX, 703, 162, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_LADDER_EXPERIENCE_HEADER
	{ D2WIN_TEXTBOX, 434, 391, 313, 218, 0, 0, &gpCellFile_JoinGameScrollBars_6F9C2734, nullptr, (void*)gaScrollBarInfo_6F9BC0C0, (void*)gaTextStyle_6F9BC068, (void*)4 },	// CTRLINIT_LADDER_LIST
	{ D2WIN_BUTTON, 433, 433, 96, 32, 0, 5103, &gpCellFile_CancelButtonBlank_6F9C2840, CHATDLG_LadderCancelCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDER_CANCEL
	{ D2WIN_BUTTON, 427, 149, 85, 29, 0, 0, &gpCellFile_OverallTab_6F9C278C, CHATDLG_LadderTabOverallCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_LADDER_TAB_OVERALL
	{ D2WIN_BUTTON, 513, 149, 36, 29, 0, 0, &gpCellFile_AmazonTab_6F9C2790, CHATDLG_LadderTabAmazonCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_LADDER_TAB_AMAZON
	{ D2WIN_BUTTON, 550, 149, 36, 29, 0, 0, &gpCellFile_SorceressTab_6F9C2794, CHATDLG_LadderTabSorceressCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_LADDER_TAB_SORCERESS
	{ D2WIN_BUTTON, 587, 149, 36, 29, 0, 0, &gpCellFile_NecromancerTab_6F9C2798, CHATDLG_LadderTabNecromancerCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_LADDER_TAB_NECROMANCER
	{ D2WIN_BUTTON, 624, 149, 36, 29, 0, 0, &gpCellFile_PaladinTab_6F9C279C, CHATDLG_LadderTabPaladinCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_LADDER_TAB_PALADIN
	{ D2WIN_BUTTON, 661, 149, 36, 29, 0, 0, &gpCellFile_BarbarianTab_6F9C27A0, CHATDLG_LadderTabBarbarianCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_LADDER_TAB_BARBARIAN
	{ D2WIN_BUTTON, 698, 149, 36, 29, 0, 0, &gpCellFile_DruidTab_6F9C27A4, CHATDLG_LadderTabDruidCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_LADDER_TAB_DRUID
	{ D2WIN_BUTTON, 735, 149, 36, 29, 0, 0, &gpCellFile_AssassinTab_6F9C27A8, CHATDLG_LadderTabAssassinCallback, nullptr, nullptr, (void*)2 },	// CTRLINIT_LADDER_TAB_ASSASSIN
	{ D2WIN_TEXTBOX, 427, 157, 85, 29, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9C2898, (void*)2 },	// CTRLINIT_LADDER_TABLABEL_OVERALL
	{ D2WIN_TEXTBOX, 513, 157, 36, 29, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9C2898, (void*)2 },	// CTRLINIT_LADDER_TABLABEL_AMAZON
	{ D2WIN_TEXTBOX, 550, 157, 36, 29, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9C2898, (void*)2 },	// CTRLINIT_LADDER_TABLABEL_SORCERESS
	{ D2WIN_TEXTBOX, 587, 157, 36, 29, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9C2898, (void*)2 },	// CTRLINIT_LADDER_TABLABEL_NECROMANCER
	{ D2WIN_TEXTBOX, 624, 157, 36, 29, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9C2898, (void*)2 },	// CTRLINIT_LADDER_TABLABEL_PALADIN
	{ D2WIN_TEXTBOX, 661, 157, 36, 29, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9C2898, (void*)2 },	// CTRLINIT_LADDER_TABLABEL_BARBARIAN
	{ D2WIN_TEXTBOX, 698, 157, 36, 29, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9C2898, (void*)2 },	// CTRLINIT_LADDER_TABLABEL_DRUID
	{ D2WIN_TEXTBOX, 735, 157, 36, 29, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9C2898, (void*)2 },	// CTRLINIT_LADDER_TABLABEL_ASSASSIN
	{ D2WIN_BUTTON, 631, 433, 70, 32, 0, 0, &gpCellFile_YesNoButtonBlank_6F9C2844, CHATDLG_LadderPreviousCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDER_PREVIOUS
	{ D2WIN_BUTTON, 701, 433, 70, 32, 0, 0, &gpCellFile_YesNoButtonBlank_6F9C2844, CHATDLG_LadderNextCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDER_NEXT
	{ D2WIN_TIMER, 100, 0, 0, 0, 0, 0, nullptr, CHATDLG_LadderTimerCallback, nullptr, nullptr, nullptr },	// CTRLINIT_LADDER_TIMER
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_PlayerProfileBckg_6F9C2854, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_PROFILEEDIT_BACKGROUND
	{ D2WIN_TEXTBOX, 432, 147, 155, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_PROFILEEDIT_NAME
	{ D2WIN_EDITBOX, 707, 155, 55, 20, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_PROFILEEDIT_SEX
	{ D2WIN_EDITBOX, 432, 207, 259, 20, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_PROFILEEDIT_LOCATION
	{ D2WIN_EDITBOX, 432, 387, 327, 150, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, (void*)8 },	// CTRLINIT_PROFILEEDIT_DESCRIPTION
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_PlayerProfileBckg2_6F9C2850, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_PROFILEVIEW_BACKGROUND
	{ D2WIN_TEXTBOX, 432, 147, 155, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_PROFILEVIEW_NAME
	{ D2WIN_TEXTBOX, 707, 147, 55, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, (void*)34 },	// CTRLINIT_PROFILEVIEW_SEX
	{ D2WIN_TEXTBOX, 432, 199, 259, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, (void*)32 },	// CTRLINIT_PROFILEVIEW_LOCATION
	{ D2WIN_TEXTBOX, 432, 387, 327, 150, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC068, nullptr },	// CTRLINIT_PROFILEVIEW_DESCRIPTION
	{ D2WIN_TEXTBOX, 425, 129, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_PROFILE_NAME_LABEL
	{ D2WIN_TEXTBOX, 700, 129, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_PROFILE_SEX_LABEL
	{ D2WIN_TEXTBOX, 425, 180, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_PROFILE_LOCATION_LABEL
	{ D2WIN_TEXTBOX, 425, 230, 217, 12, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_PROFILE_DESCRIPTION_LABEL
	{ D2WIN_BUTTON, 433, 433, 96, 32, 0, 5103, &gpCellFile_CancelButtonBlank_6F9C2840, GATE_ProfileCancelCallback, nullptr, nullptr, nullptr },	// CTRLINIT_PROFILE_CANCEL
	{ D2WIN_BUTTON, 671, 433, 96, 32, 0, 5102, &gpCellFile_CancelButtonBlank_6F9C2840, GATE_ProfileOkCallback, nullptr, nullptr, nullptr },	// CTRLINIT_PROFILE_OK
	{ D2WIN_BUTTON, 552, 433, 96, 32, 0, 5315, &gpCellFile_CancelButtonBlank_6F9C2840, GATE_ProfileLadderCallback, nullptr, nullptr, nullptr },	// CTRLINIT_PROFILE_LADDER
	{ D2WIN_TEXTBOX, 400, 112, 400, 22, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_PROFILE_TITLE
	{ D2WIN_IMAGE, 415, 447, 373, 373, 0, 0, &gpCellFile_HelpBckg_6F9C2858, nullptr, nullptr, nullptr, nullptr },	// CTRLINIT_HELP_BACKGROUND
	{ D2WIN_TEXTBOX, 400, 112, 400, 22, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_HELP_TITLE
	{ D2WIN_TEXTBOX, 447, 398, 290, 269, 0, 0, &gpCellFile_JoinGameScrollBars_6F9C2734, nullptr, (void*)gaScrollBarInfo_6F9BC0D8, (void*)gaTextStyle_6F9BC068, (void*)4 },	// CTRLINIT_HELP_TEXT
	{ D2WIN_BUTTON, 671, 433, 96, 32, 13, 5102, &gpCellFile_CancelButtonBlank_6F9C2840, CHATDLG_HelpOkCallback, nullptr, nullptr, nullptr },	// CTRLINIT_HELP_OK
	{ D2WIN_TEXTBOX, 496, 121, 200, 22, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC078, (void*)2 },	// CTRLINIT_GAMEQUEUE_TITLE
	{ D2WIN_TEXTBOX, 427, 234, 300, 100, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_GAMEQUEUE_TEXT
	{ D2WIN_TEXTBOX, 427, 243, 300, 70, 0, 0, nullptr, nullptr, nullptr, (void*)gaTextStyle_6F9BC080, nullptr },	// CTRLINIT_153
	{ D2WIN_BUTTON, 433, 433, 96, 32, 13, 5103, &gpCellFile_CancelButtonBlank_6F9C2840, GATE_GameQueueCancelCallback, nullptr, nullptr, nullptr },	// CTRLINIT_GAMEQUEUE_CANCEL
	{ D2WIN_TIMER, 2, 0, 0, 0, 0, 0, nullptr, GATE_GameQueueTimerCallback, nullptr, nullptr, nullptr },	// CTRLINIT_GAMEQUEUE_TIMER
};

int32_t gnLastChannelListClickedLine_6F9BDE78 = -2;

int32_t gnLadderPageSize_6F9C1880;
char* gapszProfileReadBuffers_6F9C1884[3];
uint8_t byte_6F9C1890;
char gszLastWhisperSender_6F9C1898[256];
int32_t gnLadderMaxPosition_6F9C1998;
uint8_t byte_6F9C199C;
BOOL gbProfileReadCancelled_6F9C19B8;
BnClientInterface* gptComInt_6F9C19BC;
D2WinControlStrc* sgpSubChildren_6F9C19C0[CHATDLG_MAX_SUBCHILDREN];
int32_t gnAdId_6F9C1A40;
char gszChatHistory_6F9C1A48[CHATDLG_MAX_CHAT_HISTORY][256];
D2WinControlStrc* gapNewsButtons_6F9C2448[2];
int32_t gnLadderEntryCount_6F9C2450;
char gszPendingChatText_6F9C2458[512];

D2WinControlStrc* gpSendButton_6F9C2658;
D2WinControlStrc* gpWhisperButton_6F9C265C;
D2WinControlStrc* gpHelpButton_6F9C2660;
D2WinControlStrc* gpSquelchButton_6F9C2664;
D2WinControlStrc* gpUnsquelchButton_6F9C2668;
D2WinControlStrc* gpEmoteButton_6F9C266C;
D2WinButtonStrc* gpCreateButton_6F9C2670;
D2WinButtonStrc* gpChannelButton_6F9C2674;
D2WinButtonStrc* gpJoinButton_6F9C2678;
D2WinButtonStrc* gpLadderButton_6F9C267C;
D2WinControlStrc* gpQuitButton_6F9C2680;
D2WinControlStrc* gpUserListPageUp_6F9C2684;
D2WinControlStrc* gpUserListPageDown_6F9C2688;
D2WinControlStrc* gpUserListUp_6F9C268C;
D2WinControlStrc* gpUserListDown_6F9C2690;
D2WinControlStrc* gpAdImage_6F9C2694;
D2WinSmackStrc* gpAdSmack_6F9C2698;
char gszLadderCharacterName_6F9C269C[16];
D2WinButtonStrc* gapUserButtons_6F9C26AC[11];
CRITICAL_SECTION gMessageQueueLock_6F9C26D8;
D2ConfigStrc* gpConfig_6F9C26F0;
uint16_t gnMCPPendingRequestIds_6F9C26F4[2];
int32_t gnMCPState_6F9C26F8;
int32_t sgnNumSubChildren_6F9C26FC;
BOOL gbGemActivated_6F9C2700;
DWORD gdwPopupTickCount_6F9C2704;
int32_t gnLadderDisplayedPosition_6F9C2708;
BOOL gbChatNotCreated_6F9C270C;
D2CompositeUnitStrc* gpPlayerCompositeUnit_6F9C2710;
D2WinTextBoxStrc* gpPlayerInfoTextBox_6F9C2754;
D2WinControlStrc* gpUserList_6F9C2758;
D2WinButtonStrc* gpGemButton_6F9C275C;
D2WinTextBoxStrc* gpNewsTextBox_6F9C2760;
D2WinButtonStrc* gpLadderTabOverall_6F9C27AC;
D2WinButtonStrc* gpLadderTabAmazon_6F9C27B0;
D2WinButtonStrc* gpLadderTabSorceress_6F9C27B4;
D2WinButtonStrc* gpLadderTabNecromancer_6F9C27B8;
D2WinButtonStrc* gpLadderTabPaladin_6F9C27BC;
D2WinButtonStrc* gpLadderTabBarbarian_6F9C27C0;
D2WinButtonStrc* gpLadderTabDruid_6F9C27C4;
D2WinButtonStrc* gpLadderTabAssassin_6F9C27C8;
D2WinControlStrc* gpChannelDialogBackground_6F9C27F0;
D2WinTextBoxStrc* gpChannelDialogTitle_6F9C27F4;
D2WinTextBoxStrc* gpChannelDialogNameLabel_6F9C27F8;
D2WinTextBoxStrc* gpChannelDialogListLabel_6F9C27FC;
D2WinControlStrc* gpChannelDialogOk_6F9C2800;
D2WinControlStrc* gpChannelDialogCancel_6F9C2804;
D2WinEditBoxStrc* gpChannelDialogName_6F9C2808;
D2WinTextBoxStrc* gpChannelDialogList_6F9C2810;
D2WinTextBoxStrc* gpLadderList_6F9C2814;
D2WinControlStrc* gpNewsBackground_6F9C281C;
int32_t gnChatHistoryCount_6F9C2864;
BOOL gbShowJoinLeaveNotifications_6F9C2868;
BOOL gbIsOpenBattleNet_6F9C286C;
DWORD gdwLadderNextRequestTickCount_6F9C2870;
BOOL gbRealmConnectionCancelled_6F9C2874;
D2WinTextBoxStrc* gpChatTextBox_6F9C28A0;
D2WinControlStrc* gpPopup_6F9C28A4;
D2WinEditBoxStrc* gpChatEditBox_6F9C28A8;
D2WinTextBoxStrc* gpChannelTitle_6F9C28AC;
D2WinTextBoxStrc* gpMessageBox_6F9C28B0;
int32_t gnModuleReturnCode_6F9C28B4;
int32_t(__stdcall* gpfPopupCallback_6F9C28B8)(SMSGHANDLER_PARAMS*);
DWORD gdwLastChannelListClickTickCount_6F9C28BC;
DWORD gdwLastAdCheckTickCount_6F9C28C0;
DWORD gdwLastGameListTickCount_6F9C28C4;
DWORD gdwLastGameInfoTickCount_6F9C28C8;
D2MultiMessageStrc* gpMessageQueueHead_6F9C28CC;
D2MultiMessageStrc* gpMessageQueueTail_6F9C28D0;
D2MultiMotdStrc* gpMotdList_6F9C28D4;
char gszEmpty_6F9C28D8[8];
char gszUniqueName_6F9C28E0[56];
char gszCurrentChannel_6F9C2918[256];
char gszAdFileName_6F9C2A18[260];


// Helpers that were inlined in the original binary

//Inlined
static void CHATDLG_ResetButtonStates()
{
	BUTTON_SetIsPressed(gpChannelButton_6F9C2674, 0);
	BUTTON_SetIsPressed(gpCreateButton_6F9C2670, 0);
	BUTTON_SetIsPressed(gpJoinButton_6F9C2678, 0);
	BUTTON_SetIsPressed(gpLadderButton_6F9C267C, 0);
}

//Inlined
static void CHATDLG_SetPopupCallback(int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*))
{
	D2_ASSERT(pfCallback);
	gpfPopupCallback_6F9C28B8 = pfCallback;
}

//Inlined
static void CHATDLG_ShowMessageBoxEx(const Unicode* wszMessage, int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*))
{
	if (gpNewsTextBox_6F9C2760)
	{
		D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpNewsTextBox_6F9C2760, 0);
	}

	CHATDLG_ResetButtonStates();
	gpMessageBox_6F9C28B0 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_MESSAGEBOX]);
	D2Win_10044(gpMessageBox_6F9C28B0, wszMessage);
	gpfPopupCallback_6F9C28B8 = pfCallback;
}

//Inlined
static BOOL CHATDLG_IsEditBoxEmpty(D2WinEditBoxStrc* pEditBox, int32_t nMaxLength)
{
	const Unicode* wszText = D2Win_10077_EDITBOX_GetText(pEditBox);
	if (wszText)
	{
		char szText[256];
		Unicode::unicode2Win(szText, wszText, nMaxLength);
		if (strlen(szText) != 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}

//Inlined
static void CHATDLG_QueueMessage(const char* szText, int32_t nColor, BOOL bClear)
{
	D2MultiMessageStrc* pMessage = D2_CALLOC_STRC(D2MultiMessageStrc);
	if (pMessage)
	{
		pMessage->szText = nullptr;
		if (szText)
		{
			pMessage->szText = (char*)D2_ALLOC(SStrLen(szText) + 1);
			if (pMessage->szText)
			{
				SStrCopy(pMessage->szText, szText, INT_MAX);
			}
		}
		pMessage->nColor = nColor;
		pMessage->bClear = bClear;

		EnterCriticalSection(&gMessageQueueLock_6F9C26D8);
		if (gpMessageQueueHead_6F9C28CC)
		{
			gpMessageQueueTail_6F9C28D0->pNext = pMessage;
		}
		else
		{
			gpMessageQueueHead_6F9C28CC = pMessage;
		}
		gpMessageQueueTail_6F9C28D0 = pMessage;
		LeaveCriticalSection(&gMessageQueueLock_6F9C26D8);
	}
}

//Inlined
static void CHATDLG_UpdateMotdText()
{
	char szMotd[512];
	szMotd[0] = '\0';

	int32_t nLength = 0;
	for (D2MultiMotdStrc* pMotd = gpMotdList_6F9C28D4; pMotd && nLength < 512; pMotd = pMotd->pNext)
	{
		strncat(szMotd, pMotd->szText, 512 - nLength);
		nLength = strlen(szMotd);
	}

	D2Win_10027_CONTROL_ToggleThirdFlag(gpNewsBackground_6F9C281C, szMotd[0] == '\0');

	Unicode wszMotd[512];
	Unicode::utf8ToUnicode(wszMotd, szMotd, std::size(wszMotd));
	D2Win_10051(gpNewsTextBox_6F9C2760, wszMotd, 1, 0, 0);
}

//Inlined
static BOOL CHATDLG_CompareCommandWord(const char* szText, const char* szCommand)
{
	const size_t nCommandLength = strlen(szCommand);
	if (strlen(szText) < nCommandLength)
	{
		return FALSE;
	}

	for (size_t i = 0; i < nCommandLength; ++i)
	{
		if (toupper(szText[i]) != toupper(szCommand[i]))
		{
			return FALSE;
		}
	}

	return szText[nCommandLength] == ' ' || szText[nCommandLength] == '\0';
}

//Inlined
static void CHATDLG_ToggleJoinLeaveNotifications()
{
	gbShowJoinLeaveNotifications_6F9C2868 = !gbShowJoinLeaveNotifications_6F9C2868;

	char szMessage[256];
	if (gbShowJoinLeaveNotifications_6F9C2868)
	{
		strcpy(szMessage, "Player entering/leaving notifications are enabled.");
	}
	else
	{
		strcpy(szMessage, "Player entering/leaving notifications are disabled.");
	}

	Unicode wszMessage[256];
	Unicode::toUnicode(wszMessage, szMessage, 512);
	if (gpChatTextBox_6F9C28A0)
	{
		D2Win_10051(gpChatTextBox_6F9C28A0, wszMessage, 3, 0, 1);
	}
}

//Inlined
static void CHATDLG_AddToChatHistory(const char* szText)
{
	memcpy(gszChatHistory_6F9C1A48[1], gszChatHistory_6F9C1A48[0], sizeof(gszChatHistory_6F9C1A48[0]) * (CHATDLG_MAX_CHAT_HISTORY - 1));
	strcpy(gszChatHistory_6F9C1A48[0], szText);

	++gnChatHistoryCount_6F9C2864;
	if (gnChatHistoryCount_6F9C2864 > CHATDLG_MAX_CHAT_HISTORY - 1)
	{
		gnChatHistoryCount_6F9C2864 = CHATDLG_MAX_CHAT_HISTORY;
	}
}

//Inlined
static void CHATDLG_ScrollChatToBottom()
{
	const int32_t nVisibleLines = D2Win_10055(gpChatTextBox_6F9C28A0);
	const int32_t nNumLines = D2Win_10052_TEXTBOX_GetNumLines(gpChatTextBox_6F9C28A0);
	if (nVisibleLines < nNumLines)
	{
		D2Win_10053(gpChatTextBox_6F9C28A0, nNumLines - nVisibleLines);
	}
}

//Inlined
static void CHATDLG_ResetLadderTabs()
{
	BUTTON_SetIsPressed(gpLadderTabOverall_6F9C27AC, 0);
	BUTTON_SetIsPressed(gpLadderTabAmazon_6F9C27B0, 0);
	BUTTON_SetIsPressed(gpLadderTabSorceress_6F9C27B4, 0);
	BUTTON_SetIsPressed(gpLadderTabNecromancer_6F9C27B8, 0);
	BUTTON_SetIsPressed(gpLadderTabPaladin_6F9C27BC, 0);
	BUTTON_SetIsPressed(gpLadderTabBarbarian_6F9C27C0, 0);
	if (gbLadderIsExpansion_6F9BC04C)
	{
		BUTTON_SetIsPressed(gpLadderTabDruid_6F9C27C4, 0);
		BUTTON_SetIsPressed(gpLadderTabAssassin_6F9C27C8, 0);
	}
}

//Inlined
static void CHATDLG_ResetLadderControls(BOOL bExpansion)
{
	gbLadderIsExpansion_6F9BC04C = bExpansion;
	gpLadderTabOverall_6F9C27AC = nullptr;
	gpLadderTabAmazon_6F9C27B0 = nullptr;
	gpLadderTabSorceress_6F9C27B4 = nullptr;
	gpLadderTabNecromancer_6F9C27B8 = nullptr;
	gpLadderTabPaladin_6F9C27BC = nullptr;
	gpLadderTabBarbarian_6F9C27C0 = nullptr;
	gpLadderTabDruid_6F9C27C4 = nullptr;
	gpLadderTabAssassin_6F9C27C8 = nullptr;
	gpLadderList_6F9C2814 = nullptr;
	gnLadderEntryCount_6F9C2450 = 1000;
}


static const uint8_t gaCDKeyCharacterValues_6F9BA3C0[256] =
{
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0xFF, 0x0D, 0x0E, 0xFF, 0x0F, 0x10, 0xFF,
	0x11, 0xFF, 0x12, 0xFF, 0x13, 0xFF, 0x14, 0x15, 0x16, 0xFF, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0xFF, 0x0D, 0x0E, 0xFF, 0x0F, 0x10, 0xFF,
	0x11, 0xFF, 0x12, 0xFF, 0x13, 0xFF, 0x14, 0x15, 0x16, 0xFF, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

//D2Multi.0x6F9A1000
BOOL __fastcall CHATDLG_DecodeCDKey(const char* szKey, uint32_t* pProductValue, uint32_t* pPublicValue)
{
	*pProductValue = 0;
	*pPublicValue = 0;

	char szDecodedKey[20];
	strcpy(szDecodedKey, szKey);

	for (const char* pChar = szDecodedKey; *pChar; ++pChar)
	{
		if (gaCDKeyCharacterValues_6F9BA3C0[(uint8_t)*pChar] > 23)
		{
			return FALSE;
		}
	}

	uint32_t nChecksum = 0;
	uint32_t nChecksumBit = 1;
	for (int32_t i = 0; i < 16; i += 2)
	{
		uint32_t nValue = gaCDKeyCharacterValues_6F9BA3C0[(uint8_t)szDecodedKey[i + 1]] + 24 * gaCDKeyCharacterValues_6F9BA3C0[(uint8_t)szDecodedKey[i]];
		if (nValue > 255)
		{
			nValue -= 256;
			nChecksum |= nChecksumBit;
		}

		const uint32_t nHigh = (nValue >> 4) & 0xF;
		szDecodedKey[i] = (char)(nHigh < 10 ? nHigh + '0' : nHigh + '7');
		const uint32_t nLow = nValue & 0xF;
		szDecodedKey[i + 1] = (char)(nLow < 10 ? nLow + '0' : nLow + '7');
		nChecksumBit *= 2;
	}

	uint32_t nComputedChecksum = 3;
	for (int32_t i = 0; i < 16; ++i)
	{
		const char nChar = (char)tolower(szDecodedKey[i]);
		nComputedChecksum += (2 * nComputedChecksum) ^ (nChar + (nChar < 'a' ? -'0' : -('a' - 10)));
	}

	if ((nComputedChecksum & 0xFF) != nChecksum)
	{
		return FALSE;
	}

	for (int32_t i = 15; i >= 0; --i)
	{
		const int32_t nSwapIndex = (i + 7) & 0xF;
		const char nChar = szDecodedKey[i];
		szDecodedKey[i] = szDecodedKey[nSwapIndex];
		szDecodedKey[nSwapIndex] = nChar;
	}

	uint32_t nMagic = 0x13AC9741;
	for (int32_t i = 15; i >= 0; --i)
	{
		const char nChar = (char)toupper(szDecodedKey[i]);
		szDecodedKey[i] = nChar;
		if (nChar < '8')
		{
			szDecodedKey[i] = (nMagic & 7) ^ nChar;
			nMagic >>= 3;
		}
		else if (nChar < 'A')
		{
			szDecodedKey[i] = (i & 1) ^ nChar;
		}
	}

	char szProduct[4];
	char szPublic[8];
	lstrcpynA(szProduct, szDecodedKey, 3);
	lstrcpynA(szPublic, &szDecodedKey[2], 7);
	*pProductValue = strtoul(szProduct, nullptr, 16);
	*pPublicValue = strtoul(szPublic, nullptr, 16);
	return TRUE;
}

//D2Multi.0x6F9A11F0
void __fastcall CHATDLG_CloseDialogs()
{
	GATE_CloseCreateDialog();
	GATE_CloseJoinDialog();
	CHATDLG_CloseChannelDialog();
	CHATDLG_DestroySubChildren();
	GATE_CloseProfileDialog();
	gpLadderList_6F9C2814 = nullptr;
	CONTROL_Destroy(&gpMessageBox_6F9C28B0);
	CONTROL_Destroy(&gpPopup_6F9C28A4);

	if (gbHelpOpened_6F9DFA40 == TRUE)
	{
		GATE_CloseHelp();
	}

	if (gnMCPState_6F9C26F8 == D2MULTI_MCPSTATE_GAMELIST)
	{
		gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
	}

	if (gpNewsTextBox_6F9C2760)
	{
		D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpNewsTextBox_6F9C2760, 1);
	}
}

//D2Multi.0x6F9A1300
void __fastcall CHATDLG_LoadCellFiles()
{
	char szPath[260];

	sprintf(szPath, "%s\\UI\\FrontEnd\\PopUpLargest2", CHATDLG_ARCHIVE_DIR);
	gpCellFile_PopUpLargest2_6F9C2720 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\FrontEnd\\MediumButtonBlank2", CHATDLG_ARCHIVE_DIR);
	gpCellFile_MediumButtonBlank2_6F9C2724 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\bnet", CHATDLG_ARCHIVE_DIR);
	gpCellFile_Bnet_6F9C2718 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\waitingroombkgd", CHATDLG_ARCHIVE_DIR);
	gpCellFile_WaitingRoomBkgd_6F9C271C = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\CURSOR\\ohand", CHATDLG_ARCHIVE_DIR);
	gpCellFile_CursorOHand_6F9C2728 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\CURSOR\\lrotate", CHATDLG_ARCHIVE_DIR);
	gpCellFile_CursorLRotate_6F9C272C = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\scrollbar", CHATDLG_ARCHIVE_DIR);
	gpCellFile_ScrollBar_6F9C2730 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\FRONTEND\\joingamescrollbars", CHATDLG_ARCHIVE_DIR);
	gpCellFile_JoinGameScrollBars_6F9C2734 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\chatleftbuttons", CHATDLG_ARCHIVE_DIR);
	gpCellFile_ChatLeftButtons_6F9C273C = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\chatleftbuttons1", CHATDLG_ARCHIVE_DIR);
	gpCellFile_ChatLeftButtons1_6F9C2740 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\chatleftbuttons2", CHATDLG_ARCHIVE_DIR);
	gpCellFile_ChatLeftButtons2_6F9C2744 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\chatrightbuttons", CHATDLG_ARCHIVE_DIR);
	gpCellFile_ChatRightButtons_6F9C2748 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\chatrighttopbuttons", CHATDLG_ARCHIVE_DIR);
	gpCellFile_ChatRightTopButtons_6F9C274C = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\chatarrows", CHATDLG_ARCHIVE_DIR);
	gpCellFile_ChatArrows_6F9C2750 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\joingamebckg", CHATDLG_ARCHIVE_DIR);
	gpCellFile_JoinGameBckg_6F9C2764 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\GameButtonBlank", CHATDLG_ARCHIVE_DIR);
	gpCellFile_GameButtonBlank_6F9C2770 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\joingameclickbox", CHATDLG_ARCHIVE_DIR);
	gpCellFile_JoinGameClickBox_6F9C2774 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\numberarrows", CHATDLG_ARCHIVE_DIR);
	gpCellFile_NumberArrows1_6F9C27D4 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\numberarrows", CHATDLG_ARCHIVE_DIR);
	gpCellFile_NumberArrows2_6F9C27D8 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\numberarrows", CHATDLG_ARCHIVE_DIR);
	gpCellFile_NumberArrows3_6F9C27DC = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\numberarrows", CHATDLG_ARCHIVE_DIR);
	gpCellFile_NumberArrows4_6F9C27E0 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\numbergreyarrows", CHATDLG_ARCHIVE_DIR);
	gpCellFile_NumberGreyArrows_6F9C27E4 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\GreyLevelBox", CHATDLG_ARCHIVE_DIR);
	gpCellFile_GreyLevelBox_6F9C2778 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\createjoinbckg", CHATDLG_ARCHIVE_DIR);
	gpCellFile_CreateJoinBckg_6F9C27E8 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\okaybutton", CHATDLG_ARCHIVE_DIR);
	gpCellFile_OkayButton_6F9C27EC = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\creategamebckg", CHATDLG_ARCHIVE_DIR);
	gpCellFile_CreateGameBckg_6F9C2820 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\creategamebutton", CHATDLG_ARCHIVE_DIR);
	gpCellFile_CreateGameButton_6F9C2824 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\widebuttonblank", CHATDLG_ARCHIVE_DIR);
	gpCellFile_WideButtonBlank_6F9C282C = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\CancelButtonBlank", CHATDLG_ARCHIVE_DIR);
	gpCellFile_CancelButtonBlank_6F9C2840 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\yesnobuttonblank", CHATDLG_ARCHIVE_DIR);
	gpCellFile_YesNoButtonBlank_6F9C2844 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\D2logoBlackBnet", CHATDLG_ARCHIVE_DIR);
	gpCellFile_D2LogoBlackBnet_6F9C285C = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\D2logoBnet", CHATDLG_ARCHIVE_DIR);
	gpCellFile_D2LogoBnet_6F9C2860 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\blankbckg2", CHATDLG_ARCHIVE_DIR);
	gpCellFile_BlankBckg2_6F9C2768 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\gembutton", CHATDLG_ARCHIVE_DIR);
	gpCellFile_GemButton_6F9C276C = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\LadderChoiceEXP", CHATDLG_ARCHIVE_DIR);
	gpCellFile_LadderChoiceEXP_6F9C2848 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\HardcoreLadderBckg", CHATDLG_ARCHIVE_DIR);
	gpCellFile_HardcoreLadderBckg_6F9C284C = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\PlayerProfileBckg", CHATDLG_ARCHIVE_DIR);
	gpCellFile_PlayerProfileBckg_6F9C2854 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\PlayerProfileBckg", CHATDLG_ARCHIVE_DIR);
	gpCellFile_PlayerProfileBckg2_6F9C2850 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\HelpBckg", CHATDLG_ARCHIVE_DIR);
	gpCellFile_HelpBckg_6F9C2858 = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\radiobutton", CHATDLG_ARCHIVE_DIR);
	gpCellFile_RadioButton_6F9C277C = ARCHIVE_LoadCellFile(szPath, 0);
	sprintf(szPath, "%s\\UI\\BIGMENU\\radiobuttonGrey", CHATDLG_ARCHIVE_DIR);
	gpCellFile_RadioButtonGrey_6F9C2780 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\PopUpOK", CHATDLG_ARCHIVE_DIR);
	gpCellFile_PopUpOK_6F9C2784 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\CancelButtonBlank", CHATDLG_ARCHIVE_DIR);
	gpCellFile_CancelButtonBlank2_6F9C2788 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\overalltab", CHATDLG_ARCHIVE_DIR);
	gpCellFile_OverallTab_6F9C278C = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\amazontab", CHATDLG_ARCHIVE_DIR);
	gpCellFile_AmazonTab_6F9C2790 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\sorceresstab", CHATDLG_ARCHIVE_DIR);
	gpCellFile_SorceressTab_6F9C2794 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\necromancertab", CHATDLG_ARCHIVE_DIR);
	gpCellFile_NecromancerTab_6F9C2798 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\paladintab", CHATDLG_ARCHIVE_DIR);
	gpCellFile_PaladinTab_6F9C279C = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\barbariantab", CHATDLG_ARCHIVE_DIR);
	gpCellFile_BarbarianTab_6F9C27A0 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\druidtab", CHATDLG_ARCHIVE_DIR);
	gpCellFile_DruidTab_6F9C27A4 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\ui\\BIGMENU\\assassintab", CHATDLG_ARCHIVE_DIR);
	gpCellFile_AssassinTab_6F9C27A8 = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\UncompOverlays\\SquelchAura", CHATDLG_ARCHIVE_DIR);
	gpCellFile_SquelchAura_6F9C27CC = ARCHIVE_LoadCellFile(szPath, 0);
	wsprintfA(szPath, "%s\\UncompOverlays\\SelectAura", CHATDLG_ARCHIVE_DIR);
	gpCellFile_SelectAura_6F9C27D0 = ARCHIVE_LoadCellFile(szPath, 0);

	D2Win_10159(gpCellFile_SquelchAura_6F9C27CC, gpCellFile_SelectAura_6F9C27D0);
}

//Inlined
static void CHATDLG_FreeCellFile(D2CellFileStrc** ppCellFile)
{
	if (*ppCellFile)
	{
		ARCHIVE_FreeCellFile(*ppCellFile);
		*ppCellFile = nullptr;
	}
}

//D2Multi.0x6F9A1B10
void __fastcall CHATDLG_FreeCellFiles()
{
	CHATDLG_FreeCellFile(&gpCellFile_PopUpLargest2_6F9C2720);
	CHATDLG_FreeCellFile(&gpCellFile_MediumButtonBlank2_6F9C2724);
	CHATDLG_FreeCellFile(&gpCellFile_Bnet_6F9C2718);
	CHATDLG_FreeCellFile(&gpCellFile_WaitingRoomBkgd_6F9C271C);
	CHATDLG_FreeCellFile(&gpCellFile_CursorOHand_6F9C2728);
	CHATDLG_FreeCellFile(&gpCellFile_CursorLRotate_6F9C272C);
	CHATDLG_FreeCellFile(&gpCellFile_ScrollBar_6F9C2730);
	CHATDLG_FreeCellFile(&gpCellFile_JoinGameScrollBars_6F9C2734);
	CHATDLG_FreeCellFile(&gpCellFile_ChatLeftButtons_6F9C273C);
	CHATDLG_FreeCellFile(&gpCellFile_ChatLeftButtons1_6F9C2740);
	CHATDLG_FreeCellFile(&gpCellFile_ChatLeftButtons2_6F9C2744);
	CHATDLG_FreeCellFile(&gpCellFile_ChatRightButtons_6F9C2748);
	CHATDLG_FreeCellFile(&gpCellFile_ChatRightTopButtons_6F9C274C);
	CHATDLG_FreeCellFile(&gpCellFile_ChatArrows_6F9C2750);
	CHATDLG_FreeCellFile(&gpCellFile_JoinGameBckg_6F9C2764);
	CHATDLG_FreeCellFile(&gpCellFile_GameButtonBlank_6F9C2770);
	CHATDLG_FreeCellFile(&gpCellFile_JoinGameClickBox_6F9C2774);
	CHATDLG_FreeCellFile(&gpCellFile_NumberArrows1_6F9C27D4);
	CHATDLG_FreeCellFile(&gpCellFile_NumberArrows2_6F9C27D8);
	CHATDLG_FreeCellFile(&gpCellFile_NumberArrows3_6F9C27DC);
	CHATDLG_FreeCellFile(&gpCellFile_NumberArrows4_6F9C27E0);
	CHATDLG_FreeCellFile(&gpCellFile_NumberGreyArrows_6F9C27E4);
	CHATDLG_FreeCellFile(&gpCellFile_GreyLevelBox_6F9C2778);
	CHATDLG_FreeCellFile(&gpCellFile_CreateJoinBckg_6F9C27E8);
	CHATDLG_FreeCellFile(&gpCellFile_OkayButton_6F9C27EC);
	CHATDLG_FreeCellFile(&gpCellFile_CreateGameBckg_6F9C2820);
	CHATDLG_FreeCellFile(&gpCellFile_CreateGameButton_6F9C2824);
	CHATDLG_FreeCellFile(&gpCellFile_Unused_6F9C2738);
	CHATDLG_FreeCellFile(&gpCellFile_WideButtonBlank_6F9C282C);
	CHATDLG_FreeCellFile(&gpCellFile_CancelButtonBlank_6F9C2840);
	CHATDLG_FreeCellFile(&gpCellFile_YesNoButtonBlank_6F9C2844);
	CHATDLG_FreeCellFile(&gpCellFile_D2LogoBlackBnet_6F9C285C);
	CHATDLG_FreeCellFile(&gpCellFile_D2LogoBnet_6F9C2860);
	CHATDLG_FreeCellFile(&gpCellFile_BlankBckg2_6F9C2768);
	CHATDLG_FreeCellFile(&gpCellFile_GemButton_6F9C276C);
	CHATDLG_FreeCellFile(&gpCellFile_LadderChoiceEXP_6F9C2848);
	CHATDLG_FreeCellFile(&gpCellFile_HardcoreLadderBckg_6F9C284C);
	CHATDLG_FreeCellFile(&gpCellFile_PlayerProfileBckg2_6F9C2850);
	CHATDLG_FreeCellFile(&gpCellFile_HelpBckg_6F9C2858);
	CHATDLG_FreeCellFile(&gpCellFile_PlayerProfileBckg_6F9C2854);
	CHATDLG_FreeCellFile(&gpCellFile_RadioButton_6F9C277C);

	if (gpCellFile_RadioButtonGrey_6F9C2780)
	{
		ARCHIVE_FreeCellFile(gpCellFile_RadioButtonGrey_6F9C2780);
		// Note: the original game resets the wrong pointer here
		gpCellFile_RadioButton_6F9C277C = nullptr;
	}

	CHATDLG_FreeCellFile(&gpCellFile_PopUpOK_6F9C2784);
	CHATDLG_FreeCellFile(&gpCellFile_CancelButtonBlank2_6F9C2788);
	CHATDLG_FreeCellFile(&gpCellFile_OverallTab_6F9C278C);
	CHATDLG_FreeCellFile(&gpCellFile_AmazonTab_6F9C2790);
	CHATDLG_FreeCellFile(&gpCellFile_SorceressTab_6F9C2794);
	CHATDLG_FreeCellFile(&gpCellFile_NecromancerTab_6F9C2798);
	CHATDLG_FreeCellFile(&gpCellFile_PaladinTab_6F9C279C);
	CHATDLG_FreeCellFile(&gpCellFile_BarbarianTab_6F9C27A0);
	CHATDLG_FreeCellFile(&gpCellFile_DruidTab_6F9C27A4);
	CHATDLG_FreeCellFile(&gpCellFile_AssassinTab_6F9C27A8);
	CHATDLG_FreeCellFile(&gpCellFile_SquelchAura_6F9C27CC);
	CHATDLG_FreeCellFile(&gpCellFile_SelectAura_6F9C27D0);
}

//D2Multi.0x6F9A1F90
void __fastcall CHATDLG_FocusChatEditBox()
{
	if (gpChatEditBox_6F9C28A8)
	{
		D2Win_10012(gpChatEditBox_6F9C28A8);
	}
}

//D2Multi.0x6F9A1FA0
int32_t __stdcall CHATDLG_QuitButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const Unicode* wszMessage = D2LANG_GetStringFromTblIndex(5243);

	CHATDLG_DestroySubChildren();

	D2WinControlStrc* pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_BACKGROUND);
	D2Win_10033(pControl, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_CANCEL);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_TEXT);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	D2Win_10051((D2WinTextBoxStrc*)pControl, wszMessage, 0, 0, 0);
	gpfPopupCallback_6F9C28B8 = CHATDLG_ClosePopupCallback;

	gdwPopupTickCount_6F9C2704 = GetTickCount();
	gnModuleReturnCode_6F9C28B4 = D2MULTI_RETURN_LAUNCHER;
	D2Win_10009();
	return 1;
}

//D2Multi.0x6F9A2130
int32_t __stdcall CHATDLG_UserListPageUpCallback(SMSGHANDLER_PARAMS* pMsg)
{
	COMCALLBACK_ScrollUserList(-10);
	return 1;
}

//D2Multi.0x6F9A2150
int32_t __stdcall CHATDLG_UserListPageDownCallback(SMSGHANDLER_PARAMS* pMsg)
{
	COMCALLBACK_ScrollUserList(10);
	return 1;
}

//D2Multi.0x6F9A2170
int32_t __stdcall CHATDLG_UserListUpCallback(SMSGHANDLER_PARAMS* pMsg)
{
	COMCALLBACK_ScrollUserList(-1);
	return 1;
}

//D2Multi.0x6F9A2180
int32_t __stdcall CHATDLG_UserListDownCallback(SMSGHANDLER_PARAMS* pMsg)
{
	COMCALLBACK_ScrollUserList(1);
	return 1;
}

//Inlined
static void CHATDLG_ShowErrorPopup(const Unicode* wszMessage)
{
	CHATDLG_DestroySubChildren();

	D2WinControlStrc* pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_BACKGROUND);
	D2Win_10033(pControl, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_OK);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_TEXT);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	D2Win_10051((D2WinTextBoxStrc*)pControl, wszMessage, 0, 0, 0);
}

//D2Multi.0x6F9A21A0
int32_t __stdcall CHATDLG_AdClickCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const char* szUrl = gptComInt_6F9C19BC->QueryAdUrl(gnAdId_6F9C1A40);
	if (!szUrl)
	{
		return 1;
	}

	char szHtmlClass[0x800] = "";
	BOOL bSuccess = FALSE;

	SetForegroundWindow(GetDesktopWindow());

	char szKey[0x400];
	sprintf(szKey, "%s\\.html", "SOFTWARE\\Classes");

	HKEY hKey = nullptr;
	DWORD dwType = 0;
	DWORD dwSize = 0;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, szKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		dwSize = 0x400;
		if (RegQueryValueExA(hKey, nullptr, nullptr, &dwType, (LPBYTE)szHtmlClass, &dwSize) != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
		}
		else if (RegCloseKey(hKey) == ERROR_SUCCESS)
		{
			char szCommandKey[0x400];
			sprintf(szCommandKey, "%s\\%s\\shell\\open\\command", "SOFTWARE\\Classes", szHtmlClass);

			char szCommandLine[0x400] = "";
			dwSize = 0;
			if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, szCommandKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
			{
				dwSize = 0x400;
				if (RegQueryValueExA(hKey, nullptr, nullptr, &dwType, (LPBYTE)szCommandLine, &dwSize) != ERROR_SUCCESS)
				{
					RegCloseKey(hKey);
				}
				else if (RegCloseKey(hKey) == ERROR_SUCCESS)
				{
					strcat(szCommandLine, " ");
					strcat(szCommandLine, szUrl);

					STARTUPINFOA startupInfo;
					PROCESS_INFORMATION processInfo;
					SMemZero(&startupInfo, sizeof(startupInfo));
					startupInfo.cb = sizeof(startupInfo);
					if (CreateProcessA(nullptr, szCommandLine, nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS, nullptr, nullptr, &startupInfo, &processInfo))
					{
						CloseHandle(processInfo.hThread);
						CloseHandle(processInfo.hProcess);
						bSuccess = TRUE;
					}
				}
			}
		}
	}

	if (!bSuccess)
	{
		CHATDLG_ShowErrorPopup(D2LANG_GetStringFromTblIndex(5340));
		gpfPopupCallback_6F9C28B8 = CHATDLG_ClosePopupCallback;
	}

	gptComInt_6F9C19BC->OnAdClick(gnAdId_6F9C1A40, bSuccess == FALSE);
	return 1;
}

//D2Multi.0x6F9A2560
void __fastcall CHATDLG_ShowNews(BOOL bShow)
{
	D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpNewsTextBox_6F9C2760, bShow);
}

//D2Multi.0x6F9A2580
int32_t __stdcall CHATDLG_ChannelButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	BUTTON_SetIsPressed(gpJoinButton_6F9C2678, 0);
	BUTTON_SetIsPressed(gpLadderButton_6F9C267C, 0);
	BUTTON_SetIsPressed(gpCreateButton_6F9C2670, 0);

	CHATDLG_CloseDialogs();

	gpChannelDialogBackground_6F9C27F0 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNELDLG_BACKGROUND]);
	gpChannelDialogTitle_6F9C27F4 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNELDLG_TITLE]);
	D2Win_10044(gpChannelDialogTitle_6F9C27F4, D2LANG_GetStringFromTblIndex(5261));
	gpChannelDialogNameLabel_6F9C27F8 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNELDLG_NAME_LABEL]);
	D2Win_10044(gpChannelDialogNameLabel_6F9C27F8, D2LANG_GetStringFromTblIndex(5262));
	gpChannelDialogListLabel_6F9C27FC = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNELDLG_LIST_LABEL]);
	D2Win_10044(gpChannelDialogListLabel_6F9C27FC, D2LANG_GetStringFromTblIndex(5263));
	gpChannelDialogOk_6F9C2800 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNELDLG_OK]);
	gpChannelDialogCancel_6F9C2804 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CANCEL]);
	D2Win_10031(gpChannelDialogCancel_6F9C2804);
	gpChannelDialogName_6F9C2808 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNELDLG_NAME]);
	D2Win_10081(gpChannelDialogName_6F9C2808, 32);
	D2Win_10072(gpChannelDialogName_6F9C2808, (int32_t)CHATDLG_ChannelEditBoxInputCallback);
	D2Win_10073(gpChannelDialogName_6F9C2808, CHATDLG_ChannelEditBoxChangeCallback);
	gpChannelDialogList_6F9C2810 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNELDLG_LIST]);

	const char* szChannels = gptComInt_6F9C19BC->GetChannelList();

	if (gpConfig_6F9C26F0->szDefaultChannelName[0])
	{
		D2Win_10045(gpChannelDialogList_6F9C2810, gpConfig_6F9C26F0->szDefaultChannelName);
	}

	if (gpConfig_6F9C26F0->szCurrentChannelName[0] && strcmp(gpConfig_6F9C26F0->szDefaultChannelName, gpConfig_6F9C26F0->szCurrentChannelName))
	{
		D2Win_10045(gpChannelDialogList_6F9C2810, gpConfig_6F9C26F0->szCurrentChannelName);
	}

	while (*szChannels)
	{
		if (!gpConfig_6F9C26F0->szCurrentChannelName[0] || strcmp(szChannels, gpConfig_6F9C26F0->szCurrentChannelName))
		{
			D2Win_10045(gpChannelDialogList_6F9C2810, szChannels);
		}

		while (*szChannels)
		{
			++szChannels;
		}
		++szChannels;
	}

	D2Win_10076(gpChannelDialogName_6F9C2808, COMCALLBACK_GetChannelName());
	D2Win_10012(gpChannelDialogName_6F9C2808);
	D2Win_10082(gpChannelDialogName_6F9C2808);
	D2Win_10053(gpChannelDialogList_6F9C2810, 0);
	D2Win_10025_CONTROL_ToggleFirstFlag(gpChannelDialogOk_6F9C2800, !CHATDLG_IsEditBoxEmpty(gpChannelDialogName_6F9C2808, 31));
	return 1;
}

//D2Multi.0x6F9A2930
int32_t __stdcall CHATDLG_LadderButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	BUTTON_SetIsPressed(gpChannelButton_6F9C2674, 0);
	BUTTON_SetIsPressed(gpJoinButton_6F9C2678, 0);
	BUTTON_SetIsPressed(gpCreateButton_6F9C2670, 0);

	CHATDLG_CloseDialogs();

	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_BACKGROUND);
	D2WinControlStrc* pTitle = CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_TITLE);
	D2Win_10044((D2WinTextBoxStrc*)pTitle, D2LANG_GetStringFromTblIndex(5317));
	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_HARDCORE);
	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_STANDARD);
	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_EXPANSION_HARDCORE);
	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_EXPANSION_STANDARD);
	D2WinControlStrc* pCancel = CHATDLG_AddSubChild(CTRLINIT_CANCEL);
	D2Win_10031(pCancel);
	return 1;
}

//D2Multi.0x6F9A2C50
BOOL __fastcall CHATDLG_IsChatNotCreated()
{
	return gbChatNotCreated_6F9C270C;
}

//D2Multi.0x6F9A2C60
int32_t __stdcall CHATDLG_ChannelDialogOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!D2Win_10024_CONTROL_CheckFirstFlag(gpChannelDialogOk_6F9C2800))
	{
		return 0;
	}

	const Unicode* wszChannel = D2Win_10077_EDITBOX_GetText(gpChannelDialogName_6F9C2808);
	if (wszChannel)
	{
		char szChannel[256];
		Unicode::unicode2Win(szChannel, wszChannel, std::size(szChannel));
		gptComInt_6F9C19BC->JoinChannel((BYTE*)szChannel, 0, 0);

		CHATDLG_CloseDialogs();
		CHATDLG_ResetButtonStates();
		gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
	}

	return 1;
}

//D2Multi.0x6F9A2E10
int32_t __stdcall CHATDLG_EnterChatButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (gptComInt_6F9C19BC->field_68())
	{
		gptComInt_6F9C19BC->FreeBNetNews();
		CHATDLG_QueueMessage(nullptr, 0, TRUE);
		CHATDLG_CreateChatControls();
		gptComInt_6F9C19BC->JoinChannel((BYTE*)gszEmpty_6F9C28D8, 0, 0);

		CHATDLG_CloseDialogs();
		CHATDLG_ResetButtonStates();
		gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
		return 1;
	}

	CHATDLG_ShowPopup(D2LANG_GetStringFromTblIndex(5351), CHATDLG_ReturnToLauncherCallback);
	return 1;
}

//D2Multi.0x6F9A3180
int32_t __stdcall CHATDLG_ChannelListCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const int32_t nLine = D2Win_10049(gpChannelDialogList_6F9C2810);
	if (nLine == -1)
	{
		return 0;
	}

	int32_t nClickedLine = gnLastChannelListClickedLine_6F9BDE78;
	DWORD dwTickCount = gdwLastChannelListClickTickCount_6F9C28BC;
	if (pMsg->nMessage == WM_LBUTTONDOWN)
	{
		dwTickCount = GetTickCount();
		nClickedLine = nLine;
		if (nLine == gnLastChannelListClickedLine_6F9BDE78 && dwTickCount - gdwLastChannelListClickTickCount_6F9C28BC <= 500)
		{
			// Double click: join the channel
			const Unicode* wszChannel = D2Win_10077_EDITBOX_GetText(gpChannelDialogName_6F9C2808);
			if (wszChannel)
			{
				char szChannel[256];
				Unicode::unicode2Win(szChannel, wszChannel, std::size(szChannel));
				gptComInt_6F9C19BC->JoinChannel((BYTE*)szChannel, 0, 0);

				CHATDLG_CloseDialogs();
				CHATDLG_ResetButtonStates();
				gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
			}
			return 0;
		}
	}

	gdwLastChannelListClickTickCount_6F9C28BC = dwTickCount;
	gnLastChannelListClickedLine_6F9BDE78 = nClickedLine;

	const Unicode* wszSelectedChannel = D2Win_10048(gpChannelDialogList_6F9C2810);
	if (wszSelectedChannel)
	{
		D2Win_10075(gpChannelDialogName_6F9C2808, wszSelectedChannel);
		D2Win_10012(nullptr);
	}

	return 0;
}

//D2Multi.0x6F9A33C0
int32_t __stdcall CHATDLG_ChannelEditBoxInputCallback(int32_t a1, int32_t a2, const char* pKey)
{
	D2Win_10050_TEXTBOX_SetLine(gpChannelDialogList_6F9C2810, -1);
	return 1;
}

//D2Multi.0x6F9A33E0
int32_t __fastcall CHATDLG_ShowMessageBox(const Unicode* wszMessage, int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*))
{
	CHATDLG_CloseDialogs();
	CHATDLG_ShowMessageBoxEx(wszMessage, pfCallback);
	return 1;
}

//D2Multi.0x6F9A3560
void __fastcall CHATDLG_ResetDialogs()
{
	CHATDLG_CloseDialogs();
	CHATDLG_ResetButtonStates();
	gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
}

//Inlined
static void CHATDLG_ShowMCPError(uint16_t nStringId)
{
	gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
	CHATDLG_ShowMessageBox(D2LANG_GetStringFromTblIndex(nStringId), CHATDLG_MessageBoxCloseCallback);
}

//D2Multi.0x6F9A36B0
void __stdcall CHATDLG_MainLoopCallback(DWORD dwCounter)
{
	RECT tAdRect;
	SetRect(&tAdRect, 145, 11, 655, 71);
	CURSOR_SetCellFile(CONTROL_MouseInsideRect(&tAdRect) ? gpCellFile_CursorLRotate_6F9C272C : gpCellFile_CursorOHand_6F9C2728);

	if (gnMCPState_6F9C26F8 == D2MULTI_MCPSTATE_JOINGAME && gdwPopupTickCount_6F9C2704 && GetTickCount() - gdwPopupTickCount_6F9C2704 > 30000)
	{
		gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
		const Unicode* wszMessage = D2LANG_GetStringFromTblIndex(0x1415);
		CHATDLG_CloseDialogs();
		CHATDLG_ShowMessageBoxEx(wszMessage, nullptr);
		gdwPopupTickCount_6F9C2704 = 0;
	}

	BOOL bComMessages = FALSE;
	BOOL bMCPMessages = FALSE;
	do
	{
		bComMessages = COMCALLBACK_ProcessMessages();
		bMCPMessages = D2MCPCLIENT_10003();

		if (gnMCPState_6F9C26F8 == D2MULTI_MCPSTATE_CREATEGAME)
		{
			if (D2MCPCLIENT_10002())
			{
				const uint16_t nRequestId = D2MCPCLIENT_10016();
				if (nRequestId && nRequestId == gnMCPPendingRequestIds_6F9C26F4[0])
				{
					uint16_t nStringId = 0;
					switch (D2MCPCLIENT_10046())
					{
					case 0:
						gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_JOINGAME;
						do
						{
							++gnMCPRequestId_6F9BC03C;
						}
						while (!gnMCPRequestId_6F9BC03C);
						D2MCPCLIENT_10005(gpConfig_6F9C26F0->szGameName, gpConfig_6F9C26F0->szGamePassword, gnMCPRequestId_6F9BC03C);
						gnMCPPendingRequestIds_6F9C26F4[0] = gnMCPRequestId_6F9BC03C;
						gptComInt_6F9C19BC->RefreshGame(gpConfig_6F9C26F0->szGameName, gpConfig_6F9C26F0->szGamePassword, gszEmpty_6F9C28D8, 0);
						break;

					case 0x1E:
						nStringId = 0x1411;
						break;

					case 0x1F:
						nStringId = 0x1412;
						break;

					case 0x20:
						nStringId = 0x1413;
						break;

					default:
						nStringId = 0x1414;
						break;
					}

					if (nStringId)
					{
						CHATDLG_ShowMCPError(nStringId);
					}
				}
			}
		}
		else if (gnMCPState_6F9C26F8 == D2MULTI_MCPSTATE_JOINGAME)
		{
			if (D2MCPCLIENT_10002())
			{
				const uint16_t nRequestId = D2MCPCLIENT_10016();
				if (nRequestId && nRequestId == gnMCPPendingRequestIds_6F9C26F4[0])
				{
					Unicode wszBuffer[512];
					uint16_t nStringId = 0;
					switch (D2MCPCLIENT_10046())
					{
					case 0:
						gpConfig_6F9C26F0->dwGameType = 3;
						gpConfig_6F9C26F0->wJoinID = D2MCPCLIENT_10017();
						gpConfig_6F9C26F0->nTokenId = D2MCPCLIENT_10018();
						strcpy(gpConfig_6F9C26F0->szServerIP, D2MCPCLIENT_10015());
						gnModuleReturnCode_6F9C28B4 = D2MULTI_RETURN_CLIENT;
						gptComInt_6F9C19BC->NotifyJoinedGame(gpConfig_6F9C26F0->szGameName, gpConfig_6F9C26F0->szGamePassword);
						CURSOR_SetCellFile(nullptr);
						D2Win_10009();
						return;

					case 0x29:
						nStringId = 0x1428;
						break;

					case 0x2A:
						nStringId = 0x1427;
						break;

					case 0x2B:
						nStringId = 0x1429;
						break;

					case 0x2C:
						nStringId = 0x142A;
						break;

					case 0x71:
						nStringId = 0x1426;
						break;

					case 0x73:
						nStringId = (gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags & D2MULTI_SAVEFLAG_EXPANSION) ? 0x5522 : 0x14F4;
						break;

					case 0x74:
						nStringId = (gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags & D2MULTI_SAVEFLAG_EXPANSION) ? 0x5521 : 0x14F3;
						break;

					case 0x78:
						nStringId = 0x2775;
						break;

					case 0x79:
						nStringId = 0x2776;
						break;

					case 0x7D:
						nStringId = gpConfig_6F9C26F0->nComponentsColors[15] ? 0x2AB1 : 0x2AB2;
						break;

					default:
						nStringId = 0x1415;
						break;
					}

					CHATDLG_ShowMCPError(nStringId);
				}
			}
		}
		else if (gnMCPState_6F9C26F8 == D2MULTI_MCPSTATE_GAMELIST)
		{
			if (D2MCPCLIENT_10002())
			{
				D2MultiMCPGameListStrc* pGame = (D2MultiMCPGameListStrc*)D2MCPCLIENT_10019();
				const uint16_t nRequestId = pGame->nRequestId;
				if (nRequestId)
				{
					if (nRequestId == gnMCPPendingRequestIds_6F9C26F4[0])
					{
						const int32_t nResult = D2MCPCLIENT_10046();
						if (nResult == 0x33)
						{
							GATE_UpdateGameList();
						}
						else if (nResult == 0x32)
						{
							GATE_CloseJoinDialog();
							CHATDLG_UpdateGameButtons(TRUE);
						}
						else if (pGame->nType == 0)
						{
							GATE_AddMCPGame(pGame);
						}
						else
						{
							GATE_UpdateGameList();
						}
					}
					else if (nRequestId == gnMCPPendingRequestIds_6F9C26F4[1])
					{
						GATE_ShowGameInfo((D2MultiMCPGameInfoStrc*)pGame);
					}

					D2MCPCLIENT_10020();
				}
			}
		}

		BOOL bHasTimedEvents = FALSE;

		DWORD dwTickCount = GetTickCount();
		if (dwTickCount - gdwLastAdCheckTickCount_6F9C28C0 >= 15000)
		{
			gdwLastAdCheckTickCount_6F9C28C0 += dwTickCount - gdwLastAdCheckTickCount_6F9C28C0;
			bHasTimedEvents = TRUE;
			gptComInt_6F9C19BC->CheckAd();

			const uint16_t nFlags = gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags;
			if (!(nFlags & D2MULTI_SAVEFLAG_DEAD) || !(nFlags & D2MULTI_SAVEFLAG_HARDCORE))
			{
				BOOL bCheckRealmConnection = FALSE;
				if (gpConfig_6F9C26F0->szCharacterRealm[0] && !D2MCPCLIENT_10002())
				{
					bCheckRealmConnection = TRUE;
				}
				CHATDLG_UpdateGameButtons(bCheckRealmConnection);
			}
		}

		if (gnMCPState_6F9C26F8 == D2MULTI_MCPSTATE_GAMELIST)
		{
			dwTickCount = GetTickCount();
			if (dwTickCount - gdwLastGameListTickCount_6F9C28C4 >= 15000)
			{
				bHasTimedEvents = TRUE;
				gdwLastGameListTickCount_6F9C28C4 += dwTickCount - gdwLastGameListTickCount_6F9C28C4;
				GATE_RequestGameList();
			}
		}

		dwTickCount = GetTickCount();
		if (dwTickCount - gdwLastGameInfoTickCount_6F9C28C8 >= 1000)
		{
			bHasTimedEvents = TRUE;
			gdwLastGameInfoTickCount_6F9C28C8 += dwTickCount - gdwLastGameInfoTickCount_6F9C28C8;
			GATE_RequestSelectedGameInfo();
		}

		CHATDLG_ProcessMessageQueue();

		if (!bHasTimedEvents)
		{
			return;
		}
	}
	while (bComMessages || bMCPMessages);
}

//D2Multi.0x6F9A3DD0
int32_t __stdcall CHATDLG_MessageBoxCloseCallback(SMSGHANDLER_PARAMS* pMsg)
{
	D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpNewsTextBox_6F9C2760, 1);
	return 1;
}

//D2Multi.0x6F9A3DF0
void __fastcall CHATDLG_CloseChannelDialog()
{
	CONTROL_Destroy(&gpChannelDialogBackground_6F9C27F0);
	CONTROL_Destroy(&gpChannelDialogTitle_6F9C27F4);
	CONTROL_Destroy(&gpChannelDialogNameLabel_6F9C27F8);
	CONTROL_Destroy(&gpChannelDialogListLabel_6F9C27FC);
	CONTROL_Destroy(&gpChannelDialogOk_6F9C2800);
	CONTROL_Destroy(&gpChannelDialogCancel_6F9C2804);
	CONTROL_Destroy(&gpChannelDialogName_6F9C2808);
	CONTROL_Destroy(&gpChannelDialogList_6F9C2810);
	D2Win_10031(gpQuitButton_6F9C2680);
	CHATDLG_FocusChatEditBox();
}

//D2Multi.0x6F9A3E60
void __fastcall CHATDLG_UpdateGameButtons(BOOL bCheckRealmConnection)
{
	if (!bCheckRealmConnection)
	{
		if (gnMCPState_6F9C26F8 == D2MULTI_MCPSTATE_NONE && gpMessageBox_6F9C28B0)
		{
			CHATDLG_CloseDialogs();
		}

		const uint16_t nFlags = gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags;
		if (!(nFlags & D2MULTI_SAVEFLAG_DEAD) || !(nFlags & D2MULTI_SAVEFLAG_HARDCORE))
		{
			D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateButton_6F9C2670, 1);
			D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpJoinButton_6F9C2678, 1);
		}

		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpLadderButton_6F9C267C, gbIsOpenBattleNet_6F9C286C == FALSE);

		if (gpNewsTextBox_6F9C2760)
		{
			D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpNewsTextBox_6F9C2760, 1);
		}
		return;
	}

	if (!D2MCPCLIENT_10002())
	{
		CHATDLG_ShowPopup(D2LANG_GetStringFromTblIndex(0x14E7), CHATDLG_ReturnToLauncherCallback);
		return;
	}

	gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
	CHATDLG_ShowMessageBox(D2LANG_GetStringFromTblIndex(0x2B0C), CHATDLG_MessageBoxCloseCallback);
	if (gpNewsTextBox_6F9C2760)
	{
		D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpNewsTextBox_6F9C2760, 0);
	}
}

//D2Multi.0x6F9A4300
void __stdcall CHATDLG_WaitRealmConnectionCallback(DWORD dwCounter)
{
	if (WaitForSingleObject(D2MCPCLIENT_10055(), 0) == WAIT_OBJECT_0 || gbRealmConnectionCancelled_6F9C2874)
	{
		D2Win_10009();
	}
}

//D2Multi.0x6F9A4330
void __stdcall CHATDLG_WaitCharacterLogonCallback(DWORD dwCounter)
{
	D2MCPCLIENT_10003();
	if (!D2MCPCLIENT_10031() && D2MCPCLIENT_10002() && !gbRealmConnectionCancelled_6F9C2874)
	{
		return;
	}

	D2MCPCLIENT_10030(0);
	D2Win_10009();
}

//D2Multi.0x6F9A4370
BOOL __fastcall CHATDLG_ConnectToRealm()
{
	if (!gpConfig_6F9C26F0->szCharacterRealm[0])
	{
		return TRUE;
	}

	if (!gptComInt_6F9C19BC || !gptComInt_6F9C19BC->field_68())
	{
		return FALSE;
	}

	if (D2MCPCLIENT_10002())
	{
		return TRUE;
	}

	gbRealmConnectionCancelled_6F9C2874 = FALSE;

	const Unicode* wszMessage = D2LANG_GetStringFromTblIndex(0x147B);
	CHATDLG_DestroySubChildren();
	D2WinControlStrc* pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_BACKGROUND);
	D2Win_10033(pControl, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_CANCEL);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_TEXT);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	D2Win_10051((D2WinTextBoxStrc*)pControl, wszMessage, 0, 0, 0);
	gpfPopupCallback_6F9C28B8 = CHATDLG_CancelRealmConnectionCallback;
	gdwPopupTickCount_6F9C2704 = GetTickCount();

	RealmLogonInformation* pLogonInfo = gptComInt_6F9C19BC->LogonRealm(gpConfig_6F9C26F0->szCharacterRealm, "password");
	if (pLogonInfo && pLogonInfo->nSize > 8)
	{
		D2MCPCLIENT_10000(&pLogonInfo->tPacket);
		D2Win_10008(CHATDLG_WaitRealmConnectionCallback);
		CHATDLG_DestroySubChildren();

		if (!gbRealmConnectionCancelled_6F9C2874 && D2MCPCLIENT_10002() && !D2MCPCLIENT_10046())
		{
			D2MCPCLIENT_10009(gpConfig_6F9C26F0->szName);
			D2Win_10008(CHATDLG_WaitCharacterLogonCallback);
			CHATDLG_DestroySubChildren();
			return D2MCPCLIENT_10046() == 0;
		}

		CHATDLG_DestroySubChildren();
	}

	return FALSE;
}

//D2Multi.0x6F9A4630
int32_t __stdcall CHATDLG_CancelRealmConnectionCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gbRealmConnectionCancelled_6F9C2874 = TRUE;
	return 1;
}

//D2Multi.0x6F9A4640
int32_t __fastcall CHATDLG_CheckRealmConnection()
{
	if (gpConfig_6F9C26F0->szCharacterRealm[0] && !D2MCPCLIENT_10002())
	{
		return -1;
	}

	return 0;
}

//D2Multi.0x6F9A4660
void __fastcall CHATDLG_CreateChatControls()
{
	if (!gbChatNotCreated_6F9C270C)
	{
		return;
	}

	gbChatNotCreated_6F9C270C = FALSE;

	char szRealmAndCharacterName[256];
	sprintf(szRealmAndCharacterName, "%s,%s", gpConfig_6F9C26F0->szCharacterRealm, gpConfig_6F9C26F0->szName);

	for (D2WinControlStrc*& pButton : gapNewsButtons_6F9C2448)
	{
		if (pButton)
		{
			CONTROL_Destroy(&pButton);
			pButton = nullptr;
		}
	}

	if (gpPlayerInfoTextBox_6F9C2754)
	{
		CONTROL_Destroy(&gpPlayerInfoTextBox_6F9C2754);
		gpPlayerInfoTextBox_6F9C2754 = nullptr;
	}

	if (gpPlayerCompositeUnit_6F9C2710)
	{
		D2Win_10142_CompUnitDestroy(gpPlayerCompositeUnit_6F9C2710, 1);
	}
	gpPlayerCompositeUnit_6F9C2710 = nullptr;

	BACKGROUND_SetCellFile(gpCellFile_Bnet_6F9C2718);

	gpSendButton_6F9C2658 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHAT_SEND]);
	gpWhisperButton_6F9C265C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHAT_WHISPER]);
	gpHelpButton_6F9C2660 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHAT_HELP]);
	gpSquelchButton_6F9C2664 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHAT_SQUELCH]);
	gpUnsquelchButton_6F9C2668 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHAT_UNSQUELCH]);
	gpEmoteButton_6F9C266C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHAT_EMOTE]);
	gpUserListPageUp_6F9C2684 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_USERLIST_PAGEUP]);
	gpUserListPageDown_6F9C2688 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_USERLIST_PAGEDOWN]);
	gpUserListUp_6F9C268C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_USERLIST_UP]);
	gpUserListDown_6F9C2690 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_USERLIST_DOWN]);
	D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpChannelButton_6F9C2674, 1);

	gpChatEditBox_6F9C28A8 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHAT_EDITBOX]);
	D2Win_10072(gpChatEditBox_6F9C28A8, (int32_t)CHATDLG_ChatEditBoxInputCallback);
	D2Win_10073(gpChatEditBox_6F9C28A8, CHATDLG_ChatEditBoxChangeCallback);
	D2Win_10012(gpChatEditBox_6F9C28A8);
	D2Win_10081(gpChatEditBox_6F9C28A8, 200);
	COMCALLBACK_UpdateChatButtons();

	D2Win_10030_CONTROL_ToggleFourthFlag(gpUserListPageUp_6F9C2684, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(gpUserListPageDown_6F9C2688, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(gpUserListUp_6F9C268C, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(gpUserListDown_6F9C2690, 1);

	D2WinButtonStrc** ppUserButton = gapUserButtons_6F9C26AC;
	for (int32_t nX = 40; nX < 700; nX += 60)
	{
		*ppUserButton = BUTTON_Create(nX, 591, 60, 100, nullptr, COMCALLBACK_UserButtonCallback, 0, 0, 4, 0, nullptr);
		++ppUserButton;
	}

	gpUserList_6F9C2758 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_USERLIST]);
	D2Win_10027_CONTROL_ToggleThirdFlag(gpUserList_6F9C2758, 0);

	gpGemButton_6F9C275C = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_GEM]);
	if (gbGemActivated_6F9C2700)
	{
		BUTTON_SetBaseFrame(gpGemButton_6F9C275C, 2);
	}
}

//D2Multi.0x6F9A48C0
int32_t __stdcall CHATDLG_ChatEditBoxInputCallback(int32_t a1, int32_t nCursorPosition, const char* pKey)
{
	if (*pKey != '\x0E')
	{
		if (*pKey == '\t')
		{
			if (gnChatHistoryCount_6F9C2864)
			{
				++gnChatHistoryIndex_6F9BC050;
				if (gnChatHistoryIndex_6F9BC050 >= gnChatHistoryCount_6F9C2864)
				{
					gnChatHistoryIndex_6F9BC050 = 0;
				}
				D2Win_10076(gpChatEditBox_6F9C28A8, gszChatHistory_6F9C1A48[gnChatHistoryIndex_6F9BC050]);
			}
			return 0;
		}
		return 1;
	}

	// Insert the name of the selected user at the cursor position
	const Unicode* wszText = D2Win_10077_EDITBOX_GetText(gpChatEditBox_6F9C28A8);
	if (wszText && gptSelectedUnit_6F9C2B30)
	{
		char szCharacterName[256];
		CHATDLG_GetCharacterName(gptSelectedUnit_6F9C2B30->szUserName, szCharacterName);

		Unicode wszNewText[256];
		char szText[256];
		Unicode::unicode2Win(szText, wszText, std::size(szText));

		const size_t nTextLength = strlen(szText);
		if ((int32_t)(strlen(szCharacterName) + nTextLength) > 255)
		{
			return 0;
		}

		char szBefore[255];
		char szAfter[257];
		strncpy(szBefore, szText, nCursorPosition);
		szBefore[nCursorPosition] = '\0';
		const size_t nAfterLength = nTextLength - nCursorPosition;
		strncpy(szAfter, &szText[nCursorPosition], nAfterLength);
		szAfter[nAfterLength] = '\0';

		sprintf(szText, "%s%s%s", szBefore, szCharacterName, szAfter);
		Unicode::win2Unicode(wszNewText, szText, std::size(wszNewText));
		D2Win_10075(gpChatEditBox_6F9C28A8, wszNewText);
	}

	return 0;
}

//D2Multi.0x6F9A4A70
void __stdcall CHATDLG_ChatEditBoxChangeCallback(int32_t a1)
{
	COMCALLBACK_UpdateChatButtons();
}

//D2Multi.0x6F9A4A80
void __fastcall CHATDLG_ProcessMessageQueue()
{
	while (true)
	{
		EnterCriticalSection(&gMessageQueueLock_6F9C26D8);
		D2MultiMessageStrc* pMessage = gpMessageQueueHead_6F9C28CC;
		if (pMessage)
		{
			gpMessageQueueHead_6F9C28CC = pMessage->pNext;
		}
		LeaveCriticalSection(&gMessageQueueLock_6F9C26D8);

		if (!pMessage)
		{
			return;
		}

		if (pMessage->bClear)
		{
			D2Win_10047(gpChatTextBox_6F9C28A0);
		}

		D2WinTextBoxStrc* pTextBox = gpChatTextBox_6F9C28A0;
		char* szText = pMessage->szText;
		if (szText)
		{
			if (strlen(szText) == 0)
			{
				D2Win_10046(pTextBox, gszEmpty_6F9C28D8, pMessage->nColor);
			}
			else
			{
				while (*szText)
				{
					char* pLineEnd = nullptr;
					char* pChar = szText;
					while (*pChar && *pChar != '\n')
					{
						++pChar;
					}

					char* pNextLine = pChar;
					if (*pChar == '\n')
					{
						*pChar = '\0';
						pLineEnd = pChar;
						pNextLine = pChar + 1;
					}

					D2Win_10046(pTextBox, szText, pMessage->nColor);

					if (pLineEnd)
					{
						*pLineEnd = '\n';
					}

					szText = pNextLine;
				}
			}

			if (pMessage->szText)
			{
				D2_FREE(pMessage->szText);
			}
		}

		D2_FREE(pMessage);
		D2Win_10053(gpChatTextBox_6F9C28A0, 0);
	}
}

//D2Multi.0x6F9A4B90
int32_t __fastcall CHATDLG_Run(D2ConfigStrc* pConfig)
{
	DWORD dwTickCount = GetTickCount();
	FOG_Trace("[D2MULTI]  Start entering at %d\n", dwTickCount);

	const BOOL bExpansion = FOG_IsExpansion();
	if (!D2LANG_10000(D2Win_GetArchive(), 0, bExpansion))
	{
		return 1;
	}

	gbChatNotCreated_6F9C270C = TRUE;
	gnModuleReturnCode_6F9C28B4 = D2MULTI_RETURN_NONE;
	gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
	gptComInt_6F9C19BC = pConfig->pComInterface;
	D2_ASSERT(gptComInt_6F9C19BC);

	if (!gptComInt_6F9C19BC->field_68())
	{
		gnModuleReturnCode_6F9C28B4 = D2MULTI_RETURN_LAUNCHER;
	}
	else
	{
		CHATDLG_LoadCellFiles();
		CURSOR_SetCellFile(gpCellFile_CursorOHand_6F9C2728);
		gpChatTextBox_6F9C28A0 = nullptr;
		BACKGROUND_SetCellFile(gpCellFile_WaitingRoomBkgd_6F9C271C);

		gpSendButton_6F9C2658 = nullptr;
		gpWhisperButton_6F9C265C = nullptr;
		gpHelpButton_6F9C2660 = nullptr;
		gpSquelchButton_6F9C2664 = nullptr;
		gpUnsquelchButton_6F9C2668 = nullptr;
		gpEmoteButton_6F9C266C = nullptr;
		gpCreateButton_6F9C2670 = nullptr;
		gpChannelButton_6F9C2674 = nullptr;
		gpJoinButton_6F9C2678 = nullptr;
		gpLadderButton_6F9C267C = nullptr;
		gpQuitButton_6F9C2680 = nullptr;
		gpUserListPageUp_6F9C2684 = nullptr;
		gpUserListPageDown_6F9C2688 = nullptr;
		gpUserListUp_6F9C268C = nullptr;
		gpUserListDown_6F9C2690 = nullptr;
		gpAdImage_6F9C2694 = nullptr;
		gpAdSmack_6F9C2698 = nullptr;

		gpCreateButton_6F9C2670 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE]);
		gpChannelButton_6F9C2674 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNEL]);
		gpJoinButton_6F9C2678 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN]);
		gpLadderButton_6F9C267C = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_LADDER]);
		gpQuitButton_6F9C2680 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_QUIT]);
		gpAdImage_6F9C2694 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_AD_IMAGE]);
		gpAdSmack_6F9C2698 = (D2WinSmackStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_AD_SMACK]);
		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpChannelButton_6F9C2674, 0);

		for (int32_t i = 0; i < std::size(gapNewsButtons_6F9C2448); ++i)
		{
			gapNewsButtons_6F9C2448[i] = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_NEWS_ENTERCHAT + i]);
		}

		gpPlayerInfoTextBox_6F9C2754 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PLAYERINFO]);

		Unicode wszClassName[100];
		char szPlayerName[100];
		szPlayerName[0] = '\0';
		const uint16_t nCharacterFlags = gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags;
		const char* szTitle = D2Win_10161(gpConfig_6F9C26F0->unpackedCTemp.nCharacterClassId, (nCharacterFlags >> 8) & 0x1F, nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE, nCharacterFlags & D2MULTI_SAVEFLAG_EXPANSION);
		if (szTitle)
		{
			strcat(szPlayerName, szTitle);
		}
		strcat(szPlayerName, gpConfig_6F9C26F0->szName);
		D2Win_10046(gpPlayerInfoTextBox_6F9C2754, szPlayerName, (gpConfig_6F9C26F0->nSaveFlags & D2MULTI_SAVEFLAG_HARDCORE) >> 2);

		CHATDLG_GetClassName(wszClassName, gpConfig_6F9C26F0->unpackedCTemp.nCharacterClassId);

		Unicode wszLevelAndClass[100];
		Unicode wszLevel[10];
		char szLevel[100];
		sprintf(szLevel, " %d ", gpConfig_6F9C26F0->nCharacterLevel ? gpConfig_6F9C26F0->nCharacterLevel : 1);
		Unicode::win2Unicode(wszLevel, szLevel, 9);
		Unicode::strcpy(wszLevelAndClass, D2LANG_GetStringFromTblIndex(0xFD9));
		Unicode::strcat(wszLevelAndClass, wszLevel);
		Unicode::strcat(wszLevelAndClass, wszClassName);
		D2Win_10051(gpPlayerInfoTextBox_6F9C2754, wszLevelAndClass, 0, 0, 0);
		D2Win_10051(gpPlayerInfoTextBox_6F9C2754, D2LANG_GetStringFromTblIndex(0x2B74), 0, 0, 0);

		const int32_t nActsPerDifficulty = ((nCharacterFlags & D2MULTI_SAVEFLAG_EXPANSION) | 0x80) >> 5;
		const int32_t nDifficulty = (int32_t)(((nCharacterFlags >> 8) & 0x1F) / nActsPerDifficulty);
		uint16_t nDifficultyStringId = 0;
		if (nDifficulty == 0)
		{
			nDifficultyStringId = 0x2B75;
		}
		else if (nDifficulty == 1)
		{
			nDifficultyStringId = 0x1424;
		}
		else if (nDifficulty == 2)
		{
			nDifficultyStringId = 0x1423;
		}
		else
		{
			nDifficultyStringId = 0x1422;
		}
		D2Win_10051(gpPlayerInfoTextBox_6F9C2754, D2LANG_GetStringFromTblIndex(nDifficultyStringId), 0, 0, 0);

		gpChannelTitle_6F9C28AC = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHANNEL_TITLE]);
		if (gpChannelTitle_6F9C28AC)
		{
			D2Win_10051(gpChannelTitle_6F9C28AC, D2LANG_GetStringFromTblIndex(0x2B73), 3, 0, 0);
		}

		int32_t nMode = 5;
		if ((pConfig->nSaveFlags & D2MULTI_SAVEFLAG_HARDCORE) && !(pConfig->nSaveFlags & D2MULTI_SAVEFLAG_DEAD) && (!FOG_IsExpansion() || pConfig->unpackedCTemp.nCharacterClassId < 5))
		{
			nMode = 1;
		}

		gpPlayerCompositeUnit_6F9C2710 = D2Win_10144(pConfig->unpackedCTemp.nCharacterClassId, nMode, pConfig->nComponents, pConfig->nComponentsColors);
		if (gpPlayerCompositeUnit_6F9C2710)
		{
			D2Win_10152(gpPlayerCompositeUnit_6F9C2710, 66);
			D2Win_10153(gpPlayerCompositeUnit_6F9C2710, 571);
			D2Win_10149(gpPlayerCompositeUnit_6F9C2710, 0);
			D2Win_10151(gpPlayerCompositeUnit_6F9C2710, 0);
		}

		gpChatTextBox_6F9C28A0 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CHAT_TEXTBOX]);

		for (char* szHistory : gszChatHistory_6F9C1A48)
		{
			szHistory[0] = '\0';
		}
		gnChatHistoryIndex_6F9BC050 = -1;
		gnChatHistoryCount_6F9C2864 = 0;

		CHATDLG_CloseDialogs();
		CHATDLG_ResetButtonStates();
		gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;

		D2WinControlStrc* pLeftLogo = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_LOGO_LEFT]);
		gpNewsBackground_6F9C281C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_NEWS_BACKGROUND]);
		gpNewsTextBox_6F9C2760 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_NEWS_TEXTBOX]);
		D2MCPCLIENT_10048(CHATDLG_MotdCallback);
		D2MCPCLIENT_10049();

		if (gpNewsTextBox_6F9C2760)
		{
			CHATDLG_UpdateMotdText();
		}

		D2WinControlStrc* pRightLogo = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_LOGO_RIGHT]);

		if ((nCharacterFlags & D2MULTI_SAVEFLAG_DEAD) && (nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE))
		{
			D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateButton_6F9C2670, 0);
			D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpJoinButton_6F9C2678, 0);
		}

		D2Win_10031(gpQuitButton_6F9C2680);
		byte_6F9C1890 = 0;
		byte_6F9C199C = 0;

		D2SOUND_10036();
		D2SOUND_10038("data\\global\\sfx\\cursor\\button.wav");
		if (D2SOUND_10069())
		{
			D2SOUND_10034(1);
		}

		gbIsOpenBattleNet_6F9C286C = gpConfig_6F9C26F0->nLaunchType == LAUNCHTYPE_OPENBNET;
		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpLadderButton_6F9C267C, gbIsOpenBattleNet_6F9C286C == FALSE);

		if (!CHATDLG_ConnectToRealm())
		{
			FOG_Trace("[D2MULTI]  Could not restore MCP connection.");
			gptComInt_6F9C19BC->CloseBNetConnection();
		}
		else
		{
			char szRealmAndCharacterName[512];
			sprintf(szRealmAndCharacterName, "%s,%s", pConfig->szCharacterRealm, pConfig->szName);
			gptComInt_6F9C19BC->EnterChat(pConfig->szName, szRealmAndCharacterName, 0x25, pConfig->szCurrentChannelName, (pConfig->unpackedCTemp.nCharacterSaveFlags & D2MULTI_SAVEFLAG_EXPANSION) != 0);

			const int32_t nElapsed = GetTickCount() - dwTickCount;
			FOG_Trace("[D2MULTI]  Finish entering at %d.  Elapsed: %d\n", GetTickCount(), nElapsed);
		}

		if (!gptComInt_6F9C19BC->field_68())
		{
			gnModuleReturnCode_6F9C28B4 = D2MULTI_RETURN_LAUNCHER;
		}
		else
		{
			D2MCPCLIENT_10053(FALSE);
			InitializeCriticalSection(&gMessageQueueLock_6F9C26D8);
			gptComInt_6F9C19BC->LoadBNetNews(CHATDLG_NewsCallback, CHATDLG_NewsDoneCallback);
			D2Win_10008(CHATDLG_MainLoopCallback);

			if (D2MCPCLIENT_10052())
			{
				D2MCPCLIENT_10054();
				D2MCPCLIENT_10053(FALSE);
			}

			gptComInt_6F9C19BC->FreeBNetNews();
			DeleteCriticalSection(&gMessageQueueLock_6F9C26D8);
			gptComInt_6F9C19BC->LeaveChat();

			if (gnModuleReturnCode_6F9C28B4 != D2MULTI_RETURN_LAUNCHER)
			{
				D2MCPClientCloseMCP();
			}
		}

		dwTickCount = GetTickCount();
		FOG_Trace("[D2MULTI]  Start closing at %d\n", dwTickCount);
		D2SOUND_10037();
		COMCALLBACK_ClearUserList();
		D2Win_10146();
		CHATDLG_CloseDialogs();

		D2MultiMotdStrc* pMotd = gpMotdList_6F9C28D4;
		while (pMotd)
		{
			D2MultiMotdStrc* pNext = pMotd->pNext;
			D2_FREE(pMotd);
			pMotd = pNext;
		}
		gpMotdList_6F9C28D4 = nullptr;

		CONTROL_Destroy(&gpChatTextBox_6F9C28A0);
		if (gpChannelTitle_6F9C28AC)
		{
			CONTROL_Destroy(&gpChannelTitle_6F9C28AC);
		}
		CONTROL_Destroy(&pLeftLogo);
		CONTROL_Destroy(&pRightLogo);
		CONTROL_Destroy(&gpNewsBackground_6F9C281C);
		CONTROL_Destroy(&gpNewsTextBox_6F9C2760);

		if (gpGemButton_6F9C275C)
		{
			CONTROL_Destroy(&gpGemButton_6F9C275C);
		}

		if (gpChatEditBox_6F9C28A8)
		{
			CONTROL_Destroy(&gpChatEditBox_6F9C28A8);
		}

		for (D2WinButtonStrc*& pUserButton : gapUserButtons_6F9C26AC)
		{
			if (pUserButton)
			{
				CONTROL_Destroy(&pUserButton);
			}
			pUserButton = nullptr;
		}

		CONTROL_Destroy(&gpUserList_6F9C2758);

		void** ppMainControls[] =
		{
			(void**)&gpSendButton_6F9C2658, (void**)&gpWhisperButton_6F9C265C, (void**)&gpHelpButton_6F9C2660, (void**)&gpSquelchButton_6F9C2664,
			(void**)&gpUnsquelchButton_6F9C2668, (void**)&gpEmoteButton_6F9C266C, (void**)&gpCreateButton_6F9C2670, (void**)&gpChannelButton_6F9C2674,
			(void**)&gpJoinButton_6F9C2678, (void**)&gpLadderButton_6F9C267C, (void**)&gpQuitButton_6F9C2680, (void**)&gpUserListPageUp_6F9C2684,
			(void**)&gpUserListPageDown_6F9C2688, (void**)&gpUserListUp_6F9C268C, (void**)&gpUserListDown_6F9C2690, (void**)&gpAdImage_6F9C2694,
			(void**)&gpAdSmack_6F9C2698,
		};
		for (void** ppControl : ppMainControls)
		{
			if (*ppControl)
			{
				CONTROL_Destroy(ppControl);
			}
			*ppControl = nullptr;
		}

		for (D2WinControlStrc*& pButton : gapNewsButtons_6F9C2448)
		{
			if (pButton)
			{
				CONTROL_Destroy(&pButton);
				pButton = nullptr;
			}
		}

		if (gpPlayerInfoTextBox_6F9C2754)
		{
			CONTROL_Destroy(&gpPlayerInfoTextBox_6F9C2754);
			gpPlayerInfoTextBox_6F9C2754 = nullptr;
		}

		BACKGROUND_SetCellFile(nullptr);
		CURSOR_SetCellFile(nullptr);
		CHATDLG_FreeCellFiles();
	}

	D2LANG_10001();
	const int32_t nElapsed = GetTickCount() - dwTickCount;
	FOG_Trace("[D2MULTI]  Finish closing at %d.  Elapsed: %d\n", GetTickCount(), nElapsed);
	return 1;
}

//D2Multi.0x6F9A5580
void __fastcall CHATDLG_GetClassName(Unicode* wszClassName, int32_t nClass)
{
	switch (nClass)
	{
	case 0:
		Unicode::strcpy(wszClassName, D2LANG_GetStringFromTblIndex(0xFAB));
		return;
	case 1:
		Unicode::strcpy(wszClassName, D2LANG_GetStringFromTblIndex(0xFAA));
		return;
	case 2:
		Unicode::strcpy(wszClassName, D2LANG_GetStringFromTblIndex(0xFA9));
		return;
	case 3:
		Unicode::strcpy(wszClassName, D2LANG_GetStringFromTblIndex(0xFA8));
		return;
	case 4:
		Unicode::strcpy(wszClassName, D2LANG_GetStringFromTblIndex(0xFA7));
		return;
	case 5:
		Unicode::strcpy(wszClassName, D2LANG_GetStringFromTblIndex(0x2771));
		return;
	case 6:
		Unicode::strcpy(wszClassName, D2LANG_GetStringFromTblIndex(0x2772));
		return;
	default:
		Unicode::strcpy(wszClassName, D2LANG_GetStringFromTblIndex(0x1507));
		return;
	}
}

//D2Multi.0x6F9A5660
int32_t __fastcall CHATDLG_NewsCallback(uint32_t nTimeStamp, const char* szNews)
{
	D2_ASSERT(szNews);

	if (nTimeStamp)
	{
		// Convert the unix timestamp to a FILETIME
		ULARGE_INTEGER nFileTime;
		nFileTime.QuadPart = ((uint64_t)nTimeStamp + 11644473600ull) * 10000000ull;

		FILETIME tFileTime;
		tFileTime.dwLowDateTime = nFileTime.LowPart;
		tFileTime.dwHighDateTime = nFileTime.HighPart;

		FILETIME tLocalFileTime;
		FileTimeToLocalFileTime(&tFileTime, &tLocalFileTime);

		Unicode wszDate[256];
		SYSTEMTIME tSystemTime;
		FileTimeToSystemTime(&tLocalFileTime, &tSystemTime);

		char szDate[64];
		GetDateFormatA(LOCALE_USER_DEFAULT, DATE_LONGDATE, &tSystemTime, nullptr, szDate, std::size(szDate));
		MultiByteToWideChar(GetACP(), MB_PRECOMPOSED, szDate, -1, (LPWSTR)wszDate, std::size(wszDate));
		Unicode::toUtf(szDate, wszDate, std::size(szDate));

		CHATDLG_QueueMessage(szDate, 0, FALSE);
		CHATDLG_QueueMessage(szNews, 4, FALSE);
		CHATDLG_QueueMessage(gszEmpty_6F9C28D8, 0, FALSE);
	}

	return 1;
}

//D2Multi.0x6F9A5910
int32_t __fastcall CHATDLG_NewsDoneCallback()
{
	CHATDLG_QueueMessage(nullptr, 0, TRUE);
	return 1;
}

//D2Multi.0x6F9A5990
BOOL __fastcall CHATDLG_CreateGame(D2MultiCreateGameStrc* pCreateGame, const char* szServerIp)
{
	CHATDLG_CloseDialogs();
	CHATDLG_SetPopupCallback(CHATDLG_MessageBoxCloseCallback);

	strcpy(gpConfig_6F9C26F0->szGameName, pCreateGame->szGameName);
	strcpy(gpConfig_6F9C26F0->szGamePassword, pCreateGame->szGamePassword);
	strcpy(gpConfig_6F9C26F0->szGameStatstring, pCreateGame->szGameDescription);
	gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_CREATEGAME;

	if (gpConfig_6F9C26F0->szCharacterRealm[0])
	{
		if (D2MCPCLIENT_10002())
		{
			gpConfig_6F9C26F0->dwGameType = 2;
			do
			{
				++gnMCPRequestId_6F9BC03C;
			}
			while (!gnMCPRequestId_6F9BC03C);

			D2MCPCLIENT_10053(FALSE);
			D2MCPCLIENT_10004(pCreateGame, gnMCPRequestId_6F9BC03C);
			gnMCPPendingRequestIds_6F9C26F4[0] = gnMCPRequestId_6F9BC03C;
			return TRUE;
		}

		gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
		CHATDLG_ShowMessageBox(D2LANG_GetStringFromTblIndex(0x2B0C), CHATDLG_MessageBoxCloseCallback);
		return FALSE;
	}

	gpConfig_6F9C26F0->dwGameType = 6;
	strcpy(gpConfig_6F9C26F0->szServerIP, szServerIp);
	gnModuleReturnCode_6F9C28B4 = D2MULTI_RETURN_CLIENT;
	CURSOR_SetCellFile(nullptr);
	D2Win_10009();
	return TRUE;
}

//D2Multi.0x6F9A5D40
BOOL __fastcall CHATDLG_JoinGame(uint16_t nGameToken, const char* szGameName, const char* szGamePassword, const char* szServerIp)
{
	gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_JOINGAME;
	CHATDLG_CloseDialogs();
	CHATDLG_SetPopupCallback(CHATDLG_MessageBoxCloseCallback);

	gpConfig_6F9C26F0->wJoinID = nGameToken;
	strcpy(gpConfig_6F9C26F0->szGameName, szGameName);
	strcpy(gpConfig_6F9C26F0->szGamePassword, szGamePassword);

	if (gpConfig_6F9C26F0->szCharacterRealm[0])
	{
		if (D2MCPCLIENT_10002())
		{
			gpConfig_6F9C26F0->dwGameType = 3;
			do
			{
				++gnMCPRequestId_6F9BC03C;
			}
			while (!gnMCPRequestId_6F9BC03C);

			D2MCPCLIENT_10005(szGameName, szGamePassword, gnMCPRequestId_6F9BC03C);
			gnMCPPendingRequestIds_6F9C26F4[0] = gnMCPRequestId_6F9BC03C;
			D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpNewsTextBox_6F9C2760, 1);
			return TRUE;
		}

		gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_NONE;
		CHATDLG_ShowMessageBox(D2LANG_GetStringFromTblIndex(0x1413), CHATDLG_MessageBoxCloseCallback);
		return FALSE;
	}

	gpConfig_6F9C26F0->dwGameType = 7;
	strcpy(gpConfig_6F9C26F0->szServerIP, szServerIp);
	gnModuleReturnCode_6F9C28B4 = D2MULTI_RETURN_CLIENT;
	CURSOR_SetCellFile(nullptr);
	D2Win_10009();
	return TRUE;
}

//D2Multi.0x6F9A6100
int32_t __fastcall CHATDLG_RunModule(D2ConfigStrc* pConfig)
{
	gpConfig_6F9C26F0 = pConfig;
	D2Win_10015();
	D2Win_10005(D2GAMERES_800x600);
	CHATDLG_Run(pConfig);
	D2Win_10016();
	return gnModuleReturnCode_6F9C28B4;
}

//D2Multi.0x6F9A6130
BOOL __fastcall CHATDLG_AddChatMessage(const Unicode* wszMessage, int32_t nColor)
{
	if (gpChatTextBox_6F9C28A0)
	{
		D2Win_10051(gpChatTextBox_6F9C28A0, wszMessage, nColor, 0, 1);
	}
	return TRUE;
}

//D2Multi.0x6F9A6150
BOOL __fastcall CHATDLG_SetChannelTitle(const Unicode* wszTitle)
{
	if (gpChannelTitle_6F9C28AC)
	{
		D2Win_10047(gpChannelTitle_6F9C28AC);
		D2Win_10051(gpChannelTitle_6F9C28AC, wszTitle, 3, 0, 0);
	}
	return TRUE;
}

//D2Multi.0x6F9A6180
void __stdcall CHATDLG_ChannelEditBoxChangeCallback(int32_t a1)
{
	D2Win_10025_CONTROL_ToggleFirstFlag(gpChannelDialogOk_6F9C2800, !CHATDLG_IsEditBoxEmpty(gpChannelDialogName_6F9C2808, 31));
}

//D2Multi.0x6F9A61E0
int32_t __stdcall CHATDLG_ReturnToLauncherCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gnModuleReturnCode_6F9C28B4 = D2MULTI_RETURN_LAUNCHER;
	D2Win_10009();
	return 1;
}

//D2Multi.0x6F9A6200
int32_t __stdcall CHATDLG_ChatEditBoxEnterCallback(const Unicode* wszText)
{
	gnChatHistoryIndex_6F9BC050 = -1;

	if (!Unicode::strlen(wszText))
	{
		return 0;
	}

	D2_ASSERT(gptComInt_6F9C19BC);

	char szText[256];
	Unicode::unicode2Win(szText, wszText, std::size(szText));

	char szTokens[260];
	strcpy(szTokens, szText);
	if (!strtok(szTokens, " "))
	{
		D2Win_10075(gpChatEditBox_6F9C28A8, nullptr);
		return 1;
	}

	return CHATDLG_SendChatText(szText, FALSE);
}

//Inlined
static void CHATDLG_ShowConnectionLostPopup()
{
	CHATDLG_ShowPopup(D2LANG_GetStringFromTblIndex(0x14E7), CHATDLG_ReturnToLauncherCallback);
}

//D2Multi.0x6F9A62D0
int32_t __stdcall CHATDLG_WarningOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (gszPendingChatText_6F9C2458[0] == '/')
	{
		CHATDLG_AddToChatHistory(gszPendingChatText_6F9C2458);

		if (!CHATDLG_HandleReplyCommand(gszPendingChatText_6F9C2458, "/r")
			&& !CHATDLG_HandleReplyCommand(gszPendingChatText_6F9C2458, "/reply")
			&& !CHATDLG_HandleNotifyCommand(gszPendingChatText_6F9C2458, "/d2notify"))
		{
			if (!gptComInt_6F9C19BC->field_68())
			{
				CHATDLG_ShowConnectionLostPopup();
			}
			else
			{
				gptComInt_6F9C19BC->ChatCommand(gszPendingChatText_6F9C2458);
			}
		}
	}
	else
	{
		if (!gptComInt_6F9C19BC->field_68())
		{
			CHATDLG_ShowPopup(D2LANG_GetStringFromTblIndex(0x14E7), CHATDLG_ReturnToLauncherCallback);
			CHATDLG_DestroySubChildren();
			return 1;
		}

		gptComInt_6F9C19BC->ChatCommand(gszPendingChatText_6F9C2458);
		COMCALLBACK_AddOwnMessage(gszPendingChatText_6F9C2458);
	}

	D2Win_10075(gpChatEditBox_6F9C28A8, nullptr);
	CHATDLG_ScrollChatToBottom();
	CHATDLG_DestroySubChildren();
	return 1;
}

//D2Multi.0x6F9A6550
BOOL __fastcall CHATDLG_HandleNotifyCommand(const char* szText, const char* szCommand)
{
	if (!CHATDLG_CompareCommandWord(szText, szCommand))
	{
		return FALSE;
	}

	CHATDLG_ToggleJoinLeaveNotifications();
	return TRUE;
}

//D2Multi.0x6F9A66F0
BOOL __fastcall CHATDLG_HandleReplyCommand(const char* szText, const char* szCommand)
{
	if (!CHATDLG_CompareCommandWord(szText, szCommand))
	{
		return FALSE;
	}

	Unicode wszMessage[256];
	char szMessage[256];
	if (strlen(gszLastWhisperSender_6F9C1898) == 0)
	{
		sprintf(szMessage, "Nobody to reply to!");
		Unicode::toUnicode(wszMessage, szMessage, std::size(wszMessage));
	}
	else
	{
		char szCommandWithSpace[256];
		sprintf(szCommandWithSpace, "%s ", szCommand);

		char szTokens[256];
		strcpy(szTokens, szText);

		int32_t nToken = 0;
		for (char* szToken = strtok(szTokens, " "); szToken; szToken = strtok(nullptr, " "))
		{
			++nToken;
			if (nToken == 2)
			{
				if (!gptComInt_6F9C19BC->field_68())
				{
					CHATDLG_ShowPopup(D2LANG_GetStringFromTblIndex(0x14E7), CHATDLG_ReturnToLauncherCallback);
					return TRUE;
				}

				sprintf(szMessage, "/w *%s %s", gszLastWhisperSender_6F9C1898, &szText[szToken - szTokens]);
				gptComInt_6F9C19BC->ChatCommand(szMessage);
				return TRUE;
			}
		}

		sprintf(szMessage, "Correct usage is: %s (message)", szCommand);
		Unicode::toUnicode(wszMessage, szMessage, std::size(wszMessage));
	}

	if (gpChatTextBox_6F9C28A0)
	{
		D2Win_10051(gpChatTextBox_6F9C28A0, wszMessage, 1, 0, 1);
	}
	return TRUE;
}

//D2Multi.0x6F9A6AC0
int32_t __stdcall CHATDLG_WarningCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	D2Win_10075(gpChatEditBox_6F9C28A8, nullptr);
	CHATDLG_DestroySubChildren();
	return 1;
}

//Inlined
static void CHATDLG_ShowSendWarning(int32_t nBackgroundControlInit, const Unicode* wszTitle, const Unicode* wszMessage)
{
	CHATDLG_DestroySubChildren();

	D2WinControlStrc* pControl = CHATDLG_AddSubChild(nBackgroundControlInit);
	D2Win_10033(pControl, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_WARNING_OK);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_WARNING_TITLE);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	D2Win_10051((D2WinTextBoxStrc*)pControl, wszTitle, 0, 0, 0);
	pControl = CHATDLG_AddSubChild(CTRLINIT_WARNING_TEXT);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	D2Win_10051((D2WinTextBoxStrc*)pControl, wszMessage, 0, 0, 0);

	gszPendingChatText_6F9C2458[0] = '\0';
}

//D2Multi.0x6F9A6B20
BOOL __fastcall CHATDLG_SendChatText(const char* szText, BOOL bWhisper)
{
	if (!bWhisper || szText[0] == '/' || !gptSelectedUnit_6F9C2B30)
	{
		strcpy(gszPendingChatText_6F9C2458, szText);
	}
	else
	{
		sprintf(gszPendingChatText_6F9C2458, "/whisper *%s %s", CHATDLG_GetAccountName(gptSelectedUnit_6F9C2B30->szUserName), szText);
	}

	// Warn the user if the account password is typed in the chat
	const uint32_t nPasswordLength = gpConfig_6F9C26F0->nAccountPasswordLength;
	const uint32_t nPasswordHash = gpConfig_6F9C26F0->nAccountPasswordHash;
	if (nPasswordLength)
	{
		char* szModifiableText = (char*)szText;
		const int32_t nLastIndex = SStrLen(szText) - nPasswordLength;
		for (int32_t i = 0; i <= nLastIndex; ++i)
		{
			if ((i < 1 || !isalnum(szText[i - 1])) && (i >= nLastIndex || !isalnum(szText[i + nPasswordLength])))
			{
				char* pEnd = &szModifiableText[i + nPasswordLength];
				const char nChar = *pEnd;
				*pEnd = '\0';
				const uint32_t nHash = SHashString(&szText[i]);
				*pEnd = nChar;

				if (nHash == nPasswordHash)
				{
					CHATDLG_ShowSendWarning(CTRLINIT_WARNING_BACKGROUND, D2LANG_GetStringFromTblIndex(0x2B37), D2LANG_GetStringFromTblIndex(0x2B38));
					return FALSE;
				}
			}
		}
	}

	// Warn the user if a CD-Key is typed in the chat
	char szCDKey[20];
	int32_t nCDKeyLength = 0;
	const int32_t nTextLength = SStrLen(szText);
	int32_t nRemainingChars = nTextLength;
	for (int32_t i = 0; i < nTextLength; ++i, --nRemainingChars)
	{
		if (nRemainingChars < 16 - nCDKeyLength)
		{
			break;
		}

		const char nChar = szText[i];
		if ((nChar >= 'A' && nChar <= 'Z') || (nChar >= 'a' && nChar <= 'z') || (nChar >= '0' && nChar <= '9'))
		{
			szCDKey[nCDKeyLength] = nChar;
			++nCDKeyLength;
		}
		else if (nChar != '-')
		{
			nCDKeyLength = 0;
			continue;
		}

		if (nCDKeyLength == 16)
		{
			szCDKey[16] = '\0';

			uint32_t nProductValue = 0;
			uint32_t nPublicValue = 0;
			if (CHATDLG_DecodeCDKey(szCDKey, &nProductValue, &nPublicValue) && (nProductValue == 6 || nProductValue == 7 || nProductValue == 10 || nProductValue == 12))
			{
				CHATDLG_ShowSendWarning(CTRLINIT_WARNING_BACKGROUND, D2LANG_GetStringFromTblIndex(0x2B7A), D2LANG_GetStringFromTblIndex(0x2B7B));
				return FALSE;
			}

			nCDKeyLength = 0;
		}
	}

	if (gszPendingChatText_6F9C2458[0] == '/')
	{
		CHATDLG_AddToChatHistory(gszPendingChatText_6F9C2458);

		if (!CHATDLG_HandleReplyCommand(gszPendingChatText_6F9C2458, "/r") && !CHATDLG_HandleReplyCommand(gszPendingChatText_6F9C2458, "/reply"))
		{
			const size_t nCommandLength = strlen("/d2notify");
			if (!CHATDLG_CompareCommand(gszPendingChatText_6F9C2458, "/d2notify") && (gszPendingChatText_6F9C2458[nCommandLength] == ' ' || gszPendingChatText_6F9C2458[nCommandLength] == '\0'))
			{
				if (!CHATDLG_CompareCommand(gszPendingChatText_6F9C2458, "/d2notify"))
				{
					CHATDLG_ToggleJoinLeaveNotifications();
				}
			}
			else if (!gptComInt_6F9C19BC->field_68())
			{
				const Unicode* wszMessage = D2LANG_GetStringFromTblIndex(0x14E7);
				CHATDLG_DestroySubChildren();
				D2WinControlStrc* pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_BACKGROUND);
				D2Win_10033(pControl, 0);
				D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
				pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_OK);
				D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
				pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_TEXT);
				D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
				D2Win_10051((D2WinTextBoxStrc*)pControl, wszMessage, 0, 0, 0);
				gpfPopupCallback_6F9C28B8 = CHATDLG_ReturnToLauncherCallback;
			}
			else
			{
				gptComInt_6F9C19BC->ChatCommand(gszPendingChatText_6F9C2458);
			}
		}
	}
	else
	{
		if (!gptComInt_6F9C19BC->field_68())
		{
			CHATDLG_ShowPopup(D2LANG_GetStringFromTblIndex(0x14E7), CHATDLG_ReturnToLauncherCallback);
			return TRUE;
		}

		gptComInt_6F9C19BC->ChatCommand(gszPendingChatText_6F9C2458);
		COMCALLBACK_AddOwnMessage(gszPendingChatText_6F9C2458);
	}

	D2Win_10075(gpChatEditBox_6F9C28A8, nullptr);
	CHATDLG_ScrollChatToBottom();
	return TRUE;
}

//D2Multi.0x6F9A7250
int32_t __fastcall CHATDLG_CompareCommand(const char* szText, const char* szCommand)
{
	if (strlen(szText) < strlen(szCommand))
	{
		return -1;
	}

	for (size_t nRemaining = strlen(szCommand); nRemaining; --nRemaining)
	{
		const int32_t nTextChar = toupper(*szText);
		const int32_t nCommandChar = toupper(*szCommand);
		if (nTextChar != nCommandChar)
		{
			return nTextChar - nCommandChar > 0 ? 1 : -1;
		}

		++szText;
		++szCommand;
	}

	return 0;
}

//D2Multi.0x6F9A72D0
D2WinControlStrc* __fastcall CHATDLG_AddSubChild(int32_t nControlInit)
{
	D2_ASSERT(sgnNumSubChildren_6F9C26FC < CHATDLG_MAX_SUBCHILDREN);

	D2WinControlStrc* pControl = CONTROL_Create(&gaControlInits_6F9BC138[nControlInit]);
	sgpSubChildren_6F9C19C0[sgnNumSubChildren_6F9C26FC] = pControl;
	++sgnNumSubChildren_6F9C26FC;
	return pControl;
}

//D2Multi.0x6F9A7320
void __fastcall CHATDLG_DestroySubChildren()
{
	for (int32_t i = 0; i < sgnNumSubChildren_6F9C26FC; ++i)
	{
		CONTROL_Destroy(&sgpSubChildren_6F9C19C0[i]);
	}

	sgnNumSubChildren_6F9C26FC = 0;
	D2Win_10031(gpQuitButton_6F9C2680);
	gdwPopupTickCount_6F9C2704 = 0;
}

//Inlined
static void CHATDLG_CreatePopup(const Unicode* wszMessage, int32_t nButtonControlInit, int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*))
{
	CHATDLG_DestroySubChildren();

	D2WinControlStrc* pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_BACKGROUND);
	D2Win_10033(pControl, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(nButtonControlInit);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	pControl = CHATDLG_AddSubChild(CTRLINIT_POPUP_TEXT);
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
	D2Win_10051((D2WinTextBoxStrc*)pControl, wszMessage, 0, 0, 0);

	gpfPopupCallback_6F9C28B8 = pfCallback ? pfCallback : CHATDLG_ClosePopupCallback;
}

//D2Multi.0x6F9A7370
void __fastcall CHATDLG_ShowPopup(const Unicode* wszMessage, int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*))
{
	CHATDLG_CreatePopup(wszMessage, CTRLINIT_POPUP_OK, pfCallback);
}

//D2Multi.0x6F9A74E0
void __fastcall CHATDLG_ShowWaitPopup(const Unicode* wszMessage, int32_t(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*))
{
	CHATDLG_CreatePopup(wszMessage, CTRLINIT_POPUP_CANCEL, pfCallback);
	gdwPopupTickCount_6F9C2704 = GetTickCount();
}

//D2Multi.0x6F9A7650
int32_t __stdcall CHATDLG_ClosePopupCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_DestroySubChildren();
	return 1;
}

//D2Multi.0x6F9A76A0
int32_t __stdcall CHATDLG_PopupButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (gpfPopupCallback_6F9C28B8)
	{
		gpfPopupCallback_6F9C28B8(pMsg);
	}
	return 1;
}

//D2Multi.0x6F9A76C0
int32_t __fastcall CHATDLG_ResetMainButtons()
{
	CHATDLG_ResetButtonStates();

	const uint16_t nCharacterFlags = gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags;
	if (!(nCharacterFlags & D2MULTI_SAVEFLAG_DEAD) || !(nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE))
	{
		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateButton_6F9C2670, 1);
		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpJoinButton_6F9C2678, 1);
	}

	D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpChannelButton_6F9C2674, gbChatNotCreated_6F9C270C == FALSE);
	D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpLadderButton_6F9C267C, gbIsOpenBattleNet_6F9C286C == FALSE);
	return 1;
}

//D2Multi.0x6F9A7760
int32_t __stdcall CHATDLG_LadderMenuCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_ResetMainButtons();
	CHATDLG_CloseDialogs();
	return 1;
}

//D2Multi.0x6F9A7910
int32_t __stdcall CHATDLG_LadderCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	// Go back to the ladder menu
	BUTTON_SetIsPressed(gpChannelButton_6F9C2674, 0);
	BUTTON_SetIsPressed(gpCreateButton_6F9C2670, 0);
	BUTTON_SetIsPressed(gpJoinButton_6F9C2678, 0);
	CHATDLG_CloseDialogs();

	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_BACKGROUND);
	D2WinControlStrc* pTitle = CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_TITLE);
	D2Win_10044((D2WinTextBoxStrc*)pTitle, D2LANG_GetStringFromTblIndex(0x14C5));
	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_HARDCORE);
	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_STANDARD);
	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_EXPANSION_HARDCORE);
	CHATDLG_AddSubChild(CTRLINIT_LADDERMENU_EXPANSION_STANDARD);
	D2Win_10031(CHATDLG_AddSubChild(CTRLINIT_CANCEL));
	return 1;
}

//D2Multi.0x6F9A7C30
int32_t __stdcall CHATDLG_LadderTimerCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (GetTickCount() <= gdwLadderNextRequestTickCount_6F9C2870 || !gpLadderList_6F9C2814)
	{
		return 1;
	}

	// Look for the first visible line that hasn't been received yet
	BOOL bRequest = gbLadderNeedsRefresh_6F9BC048;
	int32_t nLine = D2Win_10054(gpLadderList_6F9C2814);
	int32_t nLastLine = D2Win_10055(gpLadderList_6F9C2814) + nLine;
	if (nLastLine >= gnLadderEntryCount_6F9C2450)
	{
		nLastLine = gnLadderEntryCount_6F9C2450;
	}

	for (; nLine < nLastLine; ++nLine)
	{
		char szLine[256];
		Unicode::unicode2Win(szLine, D2Win_10196(gpLadderList_6F9C2814, nLine, 0), std::size(szLine));
		if (!strcmp(szLine, CHATDLG_LADDER_EMPTY_LINE))
		{
			gnLadderCharacterPosition_6F9BC044 = 16 * (nLine / 16);
			gnLadderPosition_6F9BC05C = gnLadderCharacterPosition_6F9BC044;
			bRequest = TRUE;
			break;
		}
	}

	if (bRequest && (gnLadderDisplayedPosition_6F9C2708 != gnLadderPosition_6F9BC05C || gnLadderCharacterPosition_6F9BC044 != gnLadderLastRequestedPosition_6F9BC040))
	{
		gnLadderRequestedType_6F9BC060 = gnLadderType_6F9BC058;
		gnLadderRequestedPosition_6F9BC064 = gnLadderPosition_6F9BC05C;
		D2MCPCLIENT_10027(gnLadderType_6F9BC058, gnLadderCharacterPosition_6F9BC044);
		gdwLadderNextRequestTickCount_6F9C2870 = GetTickCount() + 1000;
		gnLadderDisplayedPosition_6F9C2708 = gnLadderRequestedPosition_6F9BC064;
		gnLadderLastRequestedPosition_6F9BC040 = gnLadderCharacterPosition_6F9BC044;
	}

	return 1;
}

//D2Multi.0x6F9A7D60
void __fastcall CHATDLG_RequestCharacterLadder(const char* szCharacterName, BOOL bHardcore, BOOL bExpansion)
{
	if (!gpLadderList_6F9C2814)
	{
		return;
	}

	SStrCopy(gszLadderCharacterName_6F9C269C, szCharacterName, INT_MAX);
	if (bExpansion)
	{
		gnLadderType_6F9BC058 = bHardcore ? D2MULTI_LADDER_EXPANSION_HARDCORE : D2MULTI_LADDER_EXPANSION_STANDARD;
	}
	else
	{
		gnLadderType_6F9BC058 = bHardcore ? D2MULTI_LADDER_CLASSIC_HARDCORE : D2MULTI_LADDER_CLASSIC_STANDARD;
	}

	gnLadderPosition_6F9BC05C = -1;
	gnLadderRequestedPosition_6F9BC064 = -1;
	gnLadderRequestedType_6F9BC060 = gnLadderType_6F9BC058;
	D2MCPCLIENT_10059(szCharacterName, bHardcore, bExpansion);
	gdwLadderNextRequestTickCount_6F9C2870 = GetTickCount() + 1000;
}

//D2Multi.0x6F9A7DE0
int32_t __stdcall CHATDLG_LadderPreviousCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gnLadderType_6F9BC058 = gnLadderRequestedType_6F9BC060;
	gnLadderPosition_6F9BC05C = std::max(gnLadderPosition_6F9BC05C - gnLadderPageSize_6F9C1880, 0);
	return 1;
}

//D2Multi.0x6F9A7E10
int32_t __stdcall CHATDLG_LadderNextCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gnLadderPosition_6F9BC05C = std::min(gnLadderPageSize_6F9C1880 + gnLadderPosition_6F9BC05C, gnLadderMaxPosition_6F9C1998 - gnLadderPageSize_6F9C1880);
	gnLadderType_6F9BC058 = gnLadderRequestedType_6F9BC060;
	return 1;
}

//D2Multi.0x6F9A7E50
int32_t __stdcall CHATDLG_LadderMenuCloseCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_CloseDialogs();
	return 1;
}

//Inlined
static BOOL CHATDLG_OpenLadder(BOOL bExpansion, uint16_t nTitleStringId, uint8_t nLadderType)
{
	CHATDLG_ResetLadderControls(bExpansion);

	if (gpConfig_6F9C26F0->szCharacterRealm[0] && !D2MCPCLIENT_10002())
	{
		CHATDLG_ShowMessageBox(D2LANG_GetStringFromTblIndex(0x1413), nullptr);
		gnLadderType_6F9BC058 = nLadderType;
		gnLadderPosition_6F9BC05C = 0;
		return FALSE;
	}

	CHATDLG_AddSubChild(CTRLINIT_LADDER_BACKGROUND);
	D2WinControlStrc* pTitle = CHATDLG_AddSubChild(CTRLINIT_LADDER_TITLE);
	D2Win_10044((D2WinTextBoxStrc*)pTitle, D2LANG_GetStringFromTblIndex(nTitleStringId));
	CHATDLG_CreateLadderControls();
	gnLadderDisplayedPosition_6F9C2708 = -2;
	gnLadderRequestedType_6F9BC060 = 0x23;
	gnLadderPageSize_6F9C1880 = 16;
	gnLadderMaxPosition_6F9C1998 = 1000;
	D2MCPCLIENT_10012(CHATDLG_LadderDataCallback, CHATDLG_EmptyCallback);
	return TRUE;
}

//Inlined
static void CHATDLG_ShowLadder(BOOL bExpansion, uint16_t nTitleStringId, uint8_t nLadderType)
{
	CHATDLG_CloseDialogs();
	if (CHATDLG_OpenLadder(bExpansion, nTitleStringId, nLadderType))
	{
		gnLadderPosition_6F9BC05C = 0;
		gnLadderType_6F9BC058 = nLadderType;
	}
}

//D2Multi.0x6F9A7F60
int32_t __stdcall CHATDLG_LadderHardcoreCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_ShowLadder(FALSE, 0x14C6, D2MULTI_LADDER_CLASSIC_HARDCORE);
	return 1;
}

//D2Multi.0x6F9A8230
void __stdcall CHATDLG_EmptyCallback()
{
}

//D2Multi.0x6F9A8240
void __fastcall CHATDLG_LadderDataCallback(int32_t nStart, int32_t nCount, int32_t nNameSize, uint8_t nLadderType, void* pEntries)
{
	if (!gpLadderList_6F9C2814)
	{
		return;
	}

	if (nCount == 0)
	{
		char szCharacterName[256];
		Unicode wszFormat[256];
		Unicode wszCharacterName[256];
		Unicode wszMessage[256];

		GATE_GetProfileCharacterName(szCharacterName);
		Unicode::win2Unicode(wszFormat, "Player '%s' is not on the ladder.", std::size(wszFormat));
		Unicode::win2Unicode(wszCharacterName, szCharacterName, std::size(wszCharacterName));
		Unicode::sprintf(std::size(wszMessage), wszMessage, wszFormat, wszCharacterName);
		CHATDLG_ShowMessageBox(wszMessage, nullptr);
		return;
	}

	if (nLadderType != gnLadderType_6F9BC058)
	{
		return;
	}

	if (gnLadderPosition_6F9BC05C == -1)
	{
		D2Win_10053(gpLadderList_6F9C2814, nStart);
		gnLadderPosition_6F9BC05C = nStart;
		gnLadderRequestedPosition_6F9BC064 = nStart;
		gnLadderDisplayedPosition_6F9C2708 = nStart;
	}

	const char* aszClassNames[] = { "ama", "sor", "nec", "pal", "bar", "dru", "asn" };

	const int32_t nEnd = std::min(nStart + nCount, gnLadderEntryCount_6F9C2450);
	uint8_t* pEntry = (uint8_t*)pEntries;
	for (int32_t nLine = nStart; nLine < nEnd; ++nLine, pEntry += nNameSize + offsetof(D2MultiLadderEntryStrc, szName))
	{
		const D2MultiLadderEntryStrc* pLadderEntry = (const D2MultiLadderEntryStrc*)pEntry;
		const uint32_t dwFlags = pLadderEntry->dwFlags;
		const uint32_t nClass = dwFlags & 0xF;

		// Highlight the requested character
		const int32_t nColor = strcmp(pLadderEntry->szName, gszLadderCharacterName_6F9C269C) ? ((dwFlags & D2MULTI_LADDERFLAG_DEAD) | 0x40) >> 4 : 0;
		D2Win_10197(gpLadderList_6F9C2814, nLine);
		D2Win_10188(gpLadderList_6F9C2814, nLine, nColor);

		char szText[256];
		_itoa(nLine + 1, szText, 10);
		D2Win_10057(gpLadderList_6F9C2814, szText, nLine, 0);

		char szName[244];
		szName[0] = '\0';
		const char* szTitle = D2Win_10161(nClass, (dwFlags >> 8) & 0x1F, dwFlags & D2MULTI_LADDERFLAG_HARDCORE, dwFlags & D2MULTI_LADDERFLAG_EXPANSION);
		if (szTitle)
		{
			strcat(szName, szTitle);
		}
		strcat(szName, pLadderEntry->szName);
		D2Win_10057(gpLadderList_6F9C2814, szName, nLine, 1);
		D2Win_10057(gpLadderList_6F9C2814, aszClassNames[nClass], nLine, 2);

		_itoa((dwFlags >> 16) & 0xFF, szText, 10);
		D2Win_10057(gpLadderList_6F9C2814, szText, nLine, 3);

		Unicode wszExperience[256];
		D2LANG_10012(wszExperience, pLadderEntry->nExperienceLow, pLadderEntry->nExperienceHigh, 0xFF);
		D2Win_10058_0(gpLadderList_6F9C2814, wszExperience, nLine, 4);
	}
}

//D2Multi.0x6F9A8720
void __fastcall CHATDLG_CreateLadderControls()
{
	Unicode wszAmazon[16];
	Unicode wszSorceress[16];
	Unicode wszNecromancer[16];
	Unicode wszPaladin[16];
	Unicode wszBarbarian[16];
	Unicode wszDruid[16];
	Unicode wszAssassin[16];
	Unicode::win2Unicode(wszAmazon, "AMA", std::size(wszAmazon));
	Unicode::win2Unicode(wszSorceress, "SOR", std::size(wszSorceress));
	Unicode::win2Unicode(wszNecromancer, "NEC", std::size(wszNecromancer));
	Unicode::win2Unicode(wszPaladin, "PAL", std::size(wszPaladin));
	Unicode::win2Unicode(wszBarbarian, "BAR", std::size(wszBarbarian));
	Unicode::win2Unicode(wszDruid, "DRU", std::size(wszDruid));
	Unicode::win2Unicode(wszAssassin, "ASN", std::size(wszAssassin));

	gpLadderTabOverall_6F9C27AC = (D2WinButtonStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TAB_OVERALL);
	BUTTON_SetIsPressed(gpLadderTabOverall_6F9C27AC, 1);
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TABLABEL_OVERALL), D2LANG_GetStringFromTblIndex(0x14CE));
	gpLadderTabAmazon_6F9C27B0 = (D2WinButtonStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TAB_AMAZON);
	BUTTON_SetIsPressed(gpLadderTabAmazon_6F9C27B0, 0);
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TABLABEL_AMAZON), wszAmazon);
	gpLadderTabSorceress_6F9C27B4 = (D2WinButtonStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TAB_SORCERESS);
	BUTTON_SetIsPressed(gpLadderTabSorceress_6F9C27B4, 0);
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TABLABEL_SORCERESS), wszSorceress);
	gpLadderTabNecromancer_6F9C27B8 = (D2WinButtonStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TAB_NECROMANCER);
	BUTTON_SetIsPressed(gpLadderTabNecromancer_6F9C27B8, 0);
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TABLABEL_NECROMANCER), wszNecromancer);
	gpLadderTabPaladin_6F9C27BC = (D2WinButtonStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TAB_PALADIN);
	BUTTON_SetIsPressed(gpLadderTabPaladin_6F9C27BC, 0);
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TABLABEL_PALADIN), wszPaladin);
	gpLadderTabBarbarian_6F9C27C0 = (D2WinButtonStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TAB_BARBARIAN);
	BUTTON_SetIsPressed(gpLadderTabBarbarian_6F9C27C0, 0);
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TABLABEL_BARBARIAN), wszBarbarian);
	if (gbLadderIsExpansion_6F9BC04C)
	{
		gpLadderTabDruid_6F9C27C4 = (D2WinButtonStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TAB_DRUID);
		BUTTON_SetIsPressed(gpLadderTabDruid_6F9C27C4, 0);
		D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TABLABEL_DRUID), wszDruid);
		gpLadderTabAssassin_6F9C27C8 = (D2WinButtonStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TAB_ASSASSIN);
		BUTTON_SetIsPressed(gpLadderTabAssassin_6F9C27C8, 0);
		D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TABLABEL_ASSASSIN), wszAssassin);
	}

	D2Win_10031(CHATDLG_AddSubChild(CTRLINIT_LADDER_CANCEL));
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_RANK_HEADER), D2LANG_GetStringFromTblIndex(STRTABLE_GetLanguage() == LANGUAGE_FRENCH ? 0x2B54 : 0x14C8));
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_NAME_HEADER), D2LANG_GetStringFromTblIndex(0x14C9));
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_CLASS_HEADER), D2LANG_GetStringFromTblIndex(0x14CA));
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_EXPERIENCE_HEADER), D2LANG_GetStringFromTblIndex(0x14CC));
	D2Win_10044((D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_LEVEL_HEADER), D2LANG_GetStringFromTblIndex(0xFD9));

	gpLadderList_6F9C2814 = (D2WinTextBoxStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_LIST);
	D2Win_10204(gpLadderList_6F9C2814, 16);
	D2Win_10056(gpLadderList_6F9C2814, 5);
	D2Win_10062(gpLadderList_6F9C2814, 0, -6);
	D2Win_10059(gpLadderList_6F9C2814, 0, 0);
	D2Win_10060(gpLadderList_6F9C2814, 0, 16);
	D2Win_10059(gpLadderList_6F9C2814, 1, 35);
	D2Win_10059(gpLadderList_6F9C2814, 2, 165);
	D2Win_10059(gpLadderList_6F9C2814, 3, 195);
	D2Win_10060(gpLadderList_6F9C2814, 3, 16);
	D2Win_10059(gpLadderList_6F9C2814, 4, 220);
	D2Win_10060(gpLadderList_6F9C2814, 4, 16);
	CHATDLG_ClearLadderList();

	D2WinTimerStrc* pTimer = (D2WinTimerStrc*)CHATDLG_AddSubChild(CTRLINIT_LADDER_TIMER);
	D2Win_10180(pTimer);
	D2Win_10182(pTimer);
	gszLadderCharacterName_6F9C269C[0] = '\0';
}

//Inlined
static void CHATDLG_ShowCharacterLadder(BOOL bExpansion, uint16_t nTitleStringId)
{
	CHATDLG_ResetLadderControls(bExpansion);

	if (gpConfig_6F9C26F0->szCharacterRealm[0] && !D2MCPCLIENT_10002())
	{
		CHATDLG_ShowMessageBox(D2LANG_GetStringFromTblIndex(0x1413), nullptr);
		return;
	}

	CHATDLG_AddSubChild(CTRLINIT_LADDER_BACKGROUND);
	D2WinControlStrc* pTitle = CHATDLG_AddSubChild(CTRLINIT_LADDER_TITLE);
	D2Win_10044((D2WinTextBoxStrc*)pTitle, D2LANG_GetStringFromTblIndex(nTitleStringId));
	CHATDLG_CreateLadderControls();
	gnLadderMaxPosition_6F9C1998 = 1000;
	gnLadderDisplayedPosition_6F9C2708 = -2;
	gnLadderRequestedType_6F9BC060 = 0x23;
	gnLadderPageSize_6F9C1880 = 16;
	D2MCPCLIENT_10012(CHATDLG_LadderDataCallback, CHATDLG_EmptyCallback);
}

//D2Multi.0x6F9A8C90
void __fastcall CHATDLG_ShowStandardCharacterLadder()
{
	CHATDLG_ShowCharacterLadder(FALSE, 0x14C5);
}

//D2Multi.0x6F9A8F50
void __fastcall CHATDLG_ShowHardcoreCharacterLadder()
{
	CHATDLG_ShowCharacterLadder(FALSE, 0x14C6);
}

//D2Multi.0x6F9A9210
void __fastcall CHATDLG_ShowExpansionStandardCharacterLadder()
{
	CHATDLG_ShowCharacterLadder(TRUE, 0x276A);
}

//D2Multi.0x6F9A94D0
void __fastcall CHATDLG_ShowExpansionHardcoreCharacterLadder()
{
	CHATDLG_ShowCharacterLadder(TRUE, 0x276B);
}

//D2Multi.0x6F9A9790
int32_t __stdcall CHATDLG_LadderStandardCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_ShowLadder(FALSE, 0x14C5, D2MULTI_LADDER_CLASSIC_STANDARD);
	return 1;
}

//D2Multi.0x6F9A9A60
int32_t __stdcall CHATDLG_LadderExpansionStandardCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_ShowLadder(TRUE, 0x276A, D2MULTI_LADDER_EXPANSION_STANDARD);
	return 1;
}

//D2Multi.0x6F9A9D30
int32_t __stdcall CHATDLG_LadderExpansionHardcoreCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_ShowLadder(TRUE, 0x276B, D2MULTI_LADDER_EXPANSION_HARDCORE);
	return 1;
}

//D2Multi.0x6F9AA000
void __fastcall CHATDLG_ClearLadderList()
{
	D2Win_10047(gpLadderList_6F9C2814);

	char szEmptyLine[2];
	Unicode wszEmptyLine[2];
	sprintf(szEmptyLine, CHATDLG_LADDER_EMPTY_LINE);
	Unicode::win2Unicode(wszEmptyLine, szEmptyLine, std::size(wszEmptyLine));
	D2Win_10198(gpLadderList_6F9C2814, wszEmptyLine, gnLadderEntryCount_6F9C2450, 4, 0);
	D2Win_10053(gpLadderList_6F9C2814, 0);
	gnLadderDisplayedPosition_6F9C2708 = -2;
}

//Inlined
static void CHATDLG_SelectLadderTab(D2WinButtonStrc* pTab, int32_t nClassOffset)
{
	CHATDLG_ResetLadderTabs();
	BUTTON_SetIsPressed(pTab, 1);

	if (gnLadderType_6F9BC058 == D2MULTI_LADDER_CLASSIC_STANDARD + nClassOffset || gnLadderType_6F9BC058 == D2MULTI_LADDER_CLASSIC_HARDCORE + nClassOffset)
	{
		return;
	}

	gnLadderEntryCount_6F9C2450 = nClassOffset ? 200 : 1000;
	CHATDLG_ClearLadderList();
	gbLadderNeedsRefresh_6F9BC048 = TRUE;

	// Get the overall ladder of the current ladder type
	const int32_t nLadderType = gnLadderType_6F9BC058;
	uint8_t nBaseLadderType = 0;
	if (nLadderType >= D2MULTI_LADDER_CLASSIC_STANDARD && nLadderType <= D2MULTI_LADDER_CLASSIC_STANDARD + 7)
	{
		nBaseLadderType = D2MULTI_LADDER_CLASSIC_STANDARD;
	}
	else if (nLadderType >= D2MULTI_LADDER_CLASSIC_HARDCORE && nLadderType <= D2MULTI_LADDER_CLASSIC_HARDCORE + 7)
	{
		nBaseLadderType = D2MULTI_LADDER_CLASSIC_HARDCORE;
	}
	else if (nLadderType >= D2MULTI_LADDER_EXPANSION_HARDCORE && nLadderType <= D2MULTI_LADDER_EXPANSION_HARDCORE + 7)
	{
		nBaseLadderType = D2MULTI_LADDER_EXPANSION_HARDCORE;
	}
	else if (nLadderType >= D2MULTI_LADDER_EXPANSION_STANDARD && nLadderType <= D2MULTI_LADDER_EXPANSION_STANDARD + 7)
	{
		nBaseLadderType = D2MULTI_LADDER_EXPANSION_STANDARD;
	}
	else
	{
		D2_UNREACHABLE;
	}

	gnLadderType_6F9BC058 = nBaseLadderType + nClassOffset;
	gnLadderPosition_6F9BC05C = 0;
}

//D2Multi.0x6F9AA080
int32_t __stdcall CHATDLG_LadderTabOverallCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_SelectLadderTab(gpLadderTabOverall_6F9C27AC, 0);
	return 1;
}

//D2Multi.0x6F9AA230
int32_t __stdcall CHATDLG_LadderTabAmazonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_SelectLadderTab(gpLadderTabAmazon_6F9C27B0, 1);
	return 1;
}

//D2Multi.0x6F9AA3E0
int32_t __stdcall CHATDLG_LadderTabSorceressCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_SelectLadderTab(gpLadderTabSorceress_6F9C27B4, 2);
	return 1;
}

//D2Multi.0x6F9AA590
int32_t __stdcall CHATDLG_LadderTabNecromancerCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_SelectLadderTab(gpLadderTabNecromancer_6F9C27B8, 3);
	return 1;
}

//D2Multi.0x6F9AA740
int32_t __stdcall CHATDLG_LadderTabPaladinCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_SelectLadderTab(gpLadderTabPaladin_6F9C27BC, 4);
	return 1;
}

//D2Multi.0x6F9AA8F0
int32_t __stdcall CHATDLG_LadderTabBarbarianCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_SelectLadderTab(gpLadderTabBarbarian_6F9C27C0, 5);
	return 1;
}

//D2Multi.0x6F9AAAA0
int32_t __stdcall CHATDLG_LadderTabDruidCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_SelectLadderTab(gpLadderTabDruid_6F9C27C4, 6);
	return 1;
}

//D2Multi.0x6F9AAC50
int32_t __stdcall CHATDLG_LadderTabAssassinCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_SelectLadderTab(gpLadderTabAssassin_6F9C27C8, 7);
	return 1;
}

//D2Multi.0x6F9AAE00
void __fastcall CHATDLG_DisableRadioButton(D2WinControlStrc* pButton)
{
	CONTROL_SetCellFile(pButton, gpCellFile_RadioButtonGrey_6F9C2780);
	D2Win_10025_CONTROL_ToggleFirstFlag(pButton, 0);
}

//D2Multi.0x6F9AAE20
void __stdcall CHATDLG_WaitProfileCallback(DWORD dwCounter)
{
	uint32_t nSizes[] = { 8, 40, 200 };
	if (gptComInt_6F9C19BC->GetBattleReadUserData(3, 1, gapszProfileReadBuffers_6F9C1884, nSizes) || gbProfileReadCancelled_6F9C19B8)
	{
		D2Win_10009();
	}
}

//D2Multi.0x6F9AAE80
BOOL __fastcall CHATDLG_ReadProfile(const char* szAccountName, char* szSex, char* szLocation, char* szDescription)
{
	gapszProfileReadBuffers_6F9C1884[0] = szSex;
	gapszProfileReadBuffers_6F9C1884[1] = szLocation;
	gapszProfileReadBuffers_6F9C1884[2] = szDescription;
	gptComInt_6F9C19BC->BattleRequestReadUserData(szAccountName, 3, 1, gaszProfileKeys_6F9BC030);
	gbProfileReadCancelled_6F9C19B8 = FALSE;
	CHATDLG_ShowWaitPopup(D2LANG_GetStringFromTblIndex(0x147B), CHATDLG_CancelProfileCallback);
	D2Win_10008(CHATDLG_WaitProfileCallback);
	CHATDLG_DestroySubChildren();
	return gbProfileReadCancelled_6F9C19B8 == FALSE;
}

//D2Multi.0x6F9AB080
int32_t __stdcall CHATDLG_CancelProfileCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gbProfileReadCancelled_6F9C19B8 = TRUE;
	return 1;
}

//D2Multi.0x6F9AB090
BOOL __fastcall CHATDLG_WriteProfile(const char* szAccountName, char* szSex, char* szLocation, char* szDescription)
{
	const char* pValues[] = { szSex, szLocation, szDescription };
	gptComInt_6F9C19BC->BattleWriteUserData(szAccountName, 3, gaszProfileKeys_6F9BC030, pValues);
	return TRUE;
}

//D2Multi.0x6F9AB0D0
int32_t __stdcall CHATDLG_GemButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	uint16_t nStringId = 0;
	if (!gbGemActivated_6F9C2700)
	{
		BUTTON_SetBaseFrame(gpGemButton_6F9C275C, 2);
		gbGemActivated_6F9C2700 = TRUE;

		if (rand() % 1000 == 0)
		{
			nStringId = 0x14D8;
		}
		else if (rand() % 1000 == 0 && rand() % 1000 == 0)
		{
			Unicode wszMessage[20];
			Unicode::toUnicode(wszMessage, "Moooooooo!", 12);
			if (gpChatTextBox_6F9C28A0)
			{
				D2Win_10051(gpChatTextBox_6F9C28A0, wszMessage, 9, 0, 1);
			}
			return 1;
		}
		else
		{
			nStringId = 0x14D6;
		}
	}
	else
	{
		BUTTON_SetBaseFrame(gpGemButton_6F9C275C, 0);
		gbGemActivated_6F9C2700 = FALSE;
		nStringId = 0x14D7;
	}

	const Unicode* wszMessage = D2LANG_GetStringFromTblIndex(nStringId);
	if (gpChatTextBox_6F9C28A0)
	{
		D2Win_10051(gpChatTextBox_6F9C28A0, wszMessage, 11, 0, 1);
	}
	return 1;
}

//D2Multi.0x6F9AB1D0
int32_t __stdcall CHATDLG_HelpOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_CloseHelp();
	return 1;
}

//D2Multi.0x6F9AB1E0
void __fastcall CHATDLG_MotdCallback(int32_t nId, int32_t a2, const char* szText)
{
	D2MultiMotdStrc* pMotd = gpMotdList_6F9C28D4;
	while (pMotd && pMotd->nId != nId)
	{
		pMotd = pMotd->pNext;
	}

	if (!pMotd)
	{
		// Insert the new message, sorted by id
		pMotd = (D2MultiMotdStrc*)D2_ALLOC(sizeof(D2MultiMotdStrc));
		pMotd->nId = nId;
		if (!gpMotdList_6F9C28D4 || nId < gpMotdList_6F9C28D4->nId)
		{
			pMotd->pNext = gpMotdList_6F9C28D4;
			gpMotdList_6F9C28D4 = pMotd;
		}
		else
		{
			D2MultiMotdStrc* pPrevious = gpMotdList_6F9C28D4;
			D2MultiMotdStrc* pCurrent = gpMotdList_6F9C28D4;
			while (pCurrent && nId > pCurrent->nId)
			{
				pPrevious = pCurrent;
				pCurrent = pCurrent->pNext;
			}
			pMotd->pNext = pCurrent;
			pPrevious->pNext = pMotd;
		}
	}

	strncpy(pMotd->szText, szText, std::size(pMotd->szText));
	// Note: the original game terminates the string one byte too far, clearing the low byte of nId
	reinterpret_cast<char*>(pMotd)[sizeof(pMotd->szText)] = '\0';

	if (gpNewsTextBox_6F9C2760)
	{
		CHATDLG_UpdateMotdText();
	}
}

//D2Multi.0x6F9AB350
int32_t __fastcall CHATDLG_CancelGameQueue()
{
	D2MCPCLIENT_10054();
	D2MCPCLIENT_10053(FALSE);
	return 1;
}

//D2Multi.0x6F9AB370
const char* __fastcall CHATDLG_GetAccountName(const char* szUserName)
{
	const char* szAccountName = SStrChr(szUserName, '*');
	if (!szAccountName || !szAccountName[1])
	{
		return szUserName;
	}
	return szAccountName + 1;
}

//D2Multi.0x6F9AB390
void __fastcall CHATDLG_GetCharacterName(const char* szUserName, char* szCharacterName)
{
	if (szUserName[0] != '*')
	{
		const char* szSeparator = SStrChr(szUserName, '*');
		if (szSeparator)
		{
			const size_t nLength = szSeparator - szUserName;
			memcpy(szCharacterName, szUserName, nLength);
			szCharacterName[nLength] = '\0';
			return;
		}
	}

	SStrCopy(szCharacterName, szUserName, INT_MAX);
}
