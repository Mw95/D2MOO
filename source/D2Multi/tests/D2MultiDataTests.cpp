#include <doctest.h>

#include <cstring>
#include <iterator>
#include <vector>

#include <D2WinAnimImage.h>
#include <D2WinControlHeader.h>

#include <ChatDlg.h>
#include <ComCallback.h>
#include <D2Multi.h>
#include <Gate.h>

#include "D2MultiTestFixtures.h"


// Globals referenced by the static tables, not declared in the headers
extern uint8_t gaListData_6F9C2878[16];
extern uint8_t gaListData_6F9C2888[16];
extern D2AnimatedImageDescriptor gaLogoAnimations_6F9BC0E8[5];
extern D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC090[1];
extern D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC09C[1];
extern D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0A8[1];
extern D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0B4[1];
extern D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0C0[1];
extern D2MultiScrollBarInfoStrc gaScrollBarInfo_6F9BC0D8[1];
extern D2MultiTextStyleStrc gaTextStyle_6F9BC068[1];
extern D2MultiTextStyleStrc gaTextStyle_6F9BC078[1];
extern D2MultiTextStyleStrc gaTextStyle_6F9BC080[1];
extern D2MultiTextStyleStrc gaTextStyle_6F9BC088[1];
extern D2MultiTextStyleStrc gaTextStyle_6F9C2898[2];
extern D2CellFileStrc* gpCellFile_AmazonTab_6F9C2790;
extern D2CellFileStrc* gpCellFile_AssassinTab_6F9C27A8;
extern D2CellFileStrc* gpCellFile_BarbarianTab_6F9C27A0;
extern D2CellFileStrc* gpCellFile_BlankBckg2_6F9C2768;
extern D2CellFileStrc* gpCellFile_CancelButtonBlank2_6F9C2788;
extern D2CellFileStrc* gpCellFile_CancelButtonBlank_6F9C2840;
extern D2CellFileStrc* gpCellFile_ChatArrows_6F9C2750;
extern D2CellFileStrc* gpCellFile_ChatLeftButtons1_6F9C2740;
extern D2CellFileStrc* gpCellFile_ChatLeftButtons2_6F9C2744;
extern D2CellFileStrc* gpCellFile_ChatLeftButtons_6F9C273C;
extern D2CellFileStrc* gpCellFile_ChatRightButtons_6F9C2748;
extern D2CellFileStrc* gpCellFile_ChatRightTopButtons_6F9C274C;
extern D2CellFileStrc* gpCellFile_CreateGameBckg_6F9C2820;
extern D2CellFileStrc* gpCellFile_CreateJoinBckg_6F9C27E8;
extern D2CellFileStrc* gpCellFile_D2LogoBlackBnet_6F9C285C;
extern D2CellFileStrc* gpCellFile_D2LogoBnet_6F9C2860;
extern D2CellFileStrc* gpCellFile_DruidTab_6F9C27A4;
extern D2CellFileStrc* gpCellFile_GameButtonBlank_6F9C2770;
extern D2CellFileStrc* gpCellFile_GemButton_6F9C276C;
extern D2CellFileStrc* gpCellFile_GreyLevelBox_6F9C2778;
extern D2CellFileStrc* gpCellFile_HardcoreLadderBckg_6F9C284C;
extern D2CellFileStrc* gpCellFile_HelpBckg_6F9C2858;
extern D2CellFileStrc* gpCellFile_JoinGameBckg_6F9C2764;
extern D2CellFileStrc* gpCellFile_JoinGameClickBox_6F9C2774;
extern D2CellFileStrc* gpCellFile_JoinGameScrollBars_6F9C2734;
extern D2CellFileStrc* gpCellFile_LadderChoiceEXP_6F9C2848;
extern D2CellFileStrc* gpCellFile_MediumButtonBlank2_6F9C2724;
extern D2CellFileStrc* gpCellFile_NecromancerTab_6F9C2798;
extern D2CellFileStrc* gpCellFile_NumberArrows1_6F9C27D4;
extern D2CellFileStrc* gpCellFile_NumberArrows2_6F9C27D8;
extern D2CellFileStrc* gpCellFile_NumberArrows3_6F9C27DC;
extern D2CellFileStrc* gpCellFile_NumberArrows4_6F9C27E0;
extern D2CellFileStrc* gpCellFile_NumberGreyArrows_6F9C27E4;
extern D2CellFileStrc* gpCellFile_OverallTab_6F9C278C;
extern D2CellFileStrc* gpCellFile_PaladinTab_6F9C279C;
extern D2CellFileStrc* gpCellFile_PlayerProfileBckg2_6F9C2850;
extern D2CellFileStrc* gpCellFile_PlayerProfileBckg_6F9C2854;
extern D2CellFileStrc* gpCellFile_PopUpLargest2_6F9C2720;
extern D2CellFileStrc* gpCellFile_PopUpOK_6F9C2784;
extern D2CellFileStrc* gpCellFile_RadioButton_6F9C277C;
extern D2CellFileStrc* gpCellFile_ScrollBar_6F9C2730;
extern D2CellFileStrc* gpCellFile_SorceressTab_6F9C2794;
extern D2CellFileStrc* gpCellFile_WideButtonBlank_6F9C282C;
extern D2CellFileStrc* gpCellFile_YesNoButtonBlank_6F9C2844;
extern D2AnimatedImageDescriptor gaLogoAnimations_6F9BC0E8[5];
extern D2MultiChatEventCallback gapfComCallbacks_6F9BE798[CHATEVENT_COUNT];


namespace
{
// A D2MOO object and its address in the original dll, used to translate the pointers of the static tables
struct KnownObject
{
	const void* pMooObject;
	size_t nSize;
	uintptr_t nOriginalAddress;
};

const std::vector<KnownObject>& known_objects()
{
	static const std::vector<KnownObject> objects = {
		{ gaListData_6F9C2878, sizeof(gaListData_6F9C2878), 0x6F9C2878 },
		{ gaListData_6F9C2888, sizeof(gaListData_6F9C2888), 0x6F9C2888 },
		{ gaLogoAnimations_6F9BC0E8, sizeof(gaLogoAnimations_6F9BC0E8), 0x6F9BC0E8 },
		{ gaScrollBarInfo_6F9BC090, sizeof(gaScrollBarInfo_6F9BC090), 0x6F9BC090 },
		{ gaScrollBarInfo_6F9BC09C, sizeof(gaScrollBarInfo_6F9BC09C), 0x6F9BC09C },
		{ gaScrollBarInfo_6F9BC0A8, sizeof(gaScrollBarInfo_6F9BC0A8), 0x6F9BC0A8 },
		{ gaScrollBarInfo_6F9BC0B4, sizeof(gaScrollBarInfo_6F9BC0B4), 0x6F9BC0B4 },
		{ gaScrollBarInfo_6F9BC0C0, sizeof(gaScrollBarInfo_6F9BC0C0), 0x6F9BC0C0 },
		{ gaScrollBarInfo_6F9BC0D8, sizeof(gaScrollBarInfo_6F9BC0D8), 0x6F9BC0D8 },
		{ gaTextStyle_6F9BC068, sizeof(gaTextStyle_6F9BC068), 0x6F9BC068 },
		{ gaTextStyle_6F9BC078, sizeof(gaTextStyle_6F9BC078), 0x6F9BC078 },
		{ gaTextStyle_6F9BC080, sizeof(gaTextStyle_6F9BC080), 0x6F9BC080 },
		{ gaTextStyle_6F9BC088, sizeof(gaTextStyle_6F9BC088), 0x6F9BC088 },
		{ gaTextStyle_6F9C2898, sizeof(gaTextStyle_6F9C2898), 0x6F9C2898 },
		{ &gpCellFile_AmazonTab_6F9C2790, sizeof(gpCellFile_AmazonTab_6F9C2790), 0x6F9C2790 },
		{ &gpCellFile_AssassinTab_6F9C27A8, sizeof(gpCellFile_AssassinTab_6F9C27A8), 0x6F9C27A8 },
		{ &gpCellFile_BarbarianTab_6F9C27A0, sizeof(gpCellFile_BarbarianTab_6F9C27A0), 0x6F9C27A0 },
		{ &gpCellFile_BlankBckg2_6F9C2768, sizeof(gpCellFile_BlankBckg2_6F9C2768), 0x6F9C2768 },
		{ &gpCellFile_CancelButtonBlank2_6F9C2788, sizeof(gpCellFile_CancelButtonBlank2_6F9C2788), 0x6F9C2788 },
		{ &gpCellFile_CancelButtonBlank_6F9C2840, sizeof(gpCellFile_CancelButtonBlank_6F9C2840), 0x6F9C2840 },
		{ &gpCellFile_ChatArrows_6F9C2750, sizeof(gpCellFile_ChatArrows_6F9C2750), 0x6F9C2750 },
		{ &gpCellFile_ChatLeftButtons1_6F9C2740, sizeof(gpCellFile_ChatLeftButtons1_6F9C2740), 0x6F9C2740 },
		{ &gpCellFile_ChatLeftButtons2_6F9C2744, sizeof(gpCellFile_ChatLeftButtons2_6F9C2744), 0x6F9C2744 },
		{ &gpCellFile_ChatLeftButtons_6F9C273C, sizeof(gpCellFile_ChatLeftButtons_6F9C273C), 0x6F9C273C },
		{ &gpCellFile_ChatRightButtons_6F9C2748, sizeof(gpCellFile_ChatRightButtons_6F9C2748), 0x6F9C2748 },
		{ &gpCellFile_ChatRightTopButtons_6F9C274C, sizeof(gpCellFile_ChatRightTopButtons_6F9C274C), 0x6F9C274C },
		{ &gpCellFile_CreateGameBckg_6F9C2820, sizeof(gpCellFile_CreateGameBckg_6F9C2820), 0x6F9C2820 },
		{ &gpCellFile_CreateJoinBckg_6F9C27E8, sizeof(gpCellFile_CreateJoinBckg_6F9C27E8), 0x6F9C27E8 },
		{ &gpCellFile_D2LogoBlackBnet_6F9C285C, sizeof(gpCellFile_D2LogoBlackBnet_6F9C285C), 0x6F9C285C },
		{ &gpCellFile_D2LogoBnet_6F9C2860, sizeof(gpCellFile_D2LogoBnet_6F9C2860), 0x6F9C2860 },
		{ &gpCellFile_DruidTab_6F9C27A4, sizeof(gpCellFile_DruidTab_6F9C27A4), 0x6F9C27A4 },
		{ &gpCellFile_GameButtonBlank_6F9C2770, sizeof(gpCellFile_GameButtonBlank_6F9C2770), 0x6F9C2770 },
		{ &gpCellFile_GemButton_6F9C276C, sizeof(gpCellFile_GemButton_6F9C276C), 0x6F9C276C },
		{ &gpCellFile_GreyLevelBox_6F9C2778, sizeof(gpCellFile_GreyLevelBox_6F9C2778), 0x6F9C2778 },
		{ &gpCellFile_HardcoreLadderBckg_6F9C284C, sizeof(gpCellFile_HardcoreLadderBckg_6F9C284C), 0x6F9C284C },
		{ &gpCellFile_HelpBckg_6F9C2858, sizeof(gpCellFile_HelpBckg_6F9C2858), 0x6F9C2858 },
		{ &gpCellFile_JoinGameBckg_6F9C2764, sizeof(gpCellFile_JoinGameBckg_6F9C2764), 0x6F9C2764 },
		{ &gpCellFile_JoinGameClickBox_6F9C2774, sizeof(gpCellFile_JoinGameClickBox_6F9C2774), 0x6F9C2774 },
		{ &gpCellFile_JoinGameScrollBars_6F9C2734, sizeof(gpCellFile_JoinGameScrollBars_6F9C2734), 0x6F9C2734 },
		{ &gpCellFile_LadderChoiceEXP_6F9C2848, sizeof(gpCellFile_LadderChoiceEXP_6F9C2848), 0x6F9C2848 },
		{ &gpCellFile_MediumButtonBlank2_6F9C2724, sizeof(gpCellFile_MediumButtonBlank2_6F9C2724), 0x6F9C2724 },
		{ &gpCellFile_NecromancerTab_6F9C2798, sizeof(gpCellFile_NecromancerTab_6F9C2798), 0x6F9C2798 },
		{ &gpCellFile_NumberArrows1_6F9C27D4, sizeof(gpCellFile_NumberArrows1_6F9C27D4), 0x6F9C27D4 },
		{ &gpCellFile_NumberArrows2_6F9C27D8, sizeof(gpCellFile_NumberArrows2_6F9C27D8), 0x6F9C27D8 },
		{ &gpCellFile_NumberArrows3_6F9C27DC, sizeof(gpCellFile_NumberArrows3_6F9C27DC), 0x6F9C27DC },
		{ &gpCellFile_NumberArrows4_6F9C27E0, sizeof(gpCellFile_NumberArrows4_6F9C27E0), 0x6F9C27E0 },
		{ &gpCellFile_NumberGreyArrows_6F9C27E4, sizeof(gpCellFile_NumberGreyArrows_6F9C27E4), 0x6F9C27E4 },
		{ &gpCellFile_OverallTab_6F9C278C, sizeof(gpCellFile_OverallTab_6F9C278C), 0x6F9C278C },
		{ &gpCellFile_PaladinTab_6F9C279C, sizeof(gpCellFile_PaladinTab_6F9C279C), 0x6F9C279C },
		{ &gpCellFile_PlayerProfileBckg2_6F9C2850, sizeof(gpCellFile_PlayerProfileBckg2_6F9C2850), 0x6F9C2850 },
		{ &gpCellFile_PlayerProfileBckg_6F9C2854, sizeof(gpCellFile_PlayerProfileBckg_6F9C2854), 0x6F9C2854 },
		{ &gpCellFile_PopUpLargest2_6F9C2720, sizeof(gpCellFile_PopUpLargest2_6F9C2720), 0x6F9C2720 },
		{ &gpCellFile_PopUpOK_6F9C2784, sizeof(gpCellFile_PopUpOK_6F9C2784), 0x6F9C2784 },
		{ &gpCellFile_RadioButton_6F9C277C, sizeof(gpCellFile_RadioButton_6F9C277C), 0x6F9C277C },
		{ &gpCellFile_ScrollBar_6F9C2730, sizeof(gpCellFile_ScrollBar_6F9C2730), 0x6F9C2730 },
		{ &gpCellFile_SorceressTab_6F9C2794, sizeof(gpCellFile_SorceressTab_6F9C2794), 0x6F9C2794 },
		{ &gpCellFile_WideButtonBlank_6F9C282C, sizeof(gpCellFile_WideButtonBlank_6F9C282C), 0x6F9C282C },
		{ &gpCellFile_YesNoButtonBlank_6F9C2844, sizeof(gpCellFile_YesNoButtonBlank_6F9C2844), 0x6F9C2844 },
		{ gaLogoAnimations_6F9BC0E8, sizeof(gaLogoAnimations_6F9BC0E8), 0x6F9BC0E8 },
		{ gaControlInits_6F9BC138, sizeof(gaControlInits_6F9BC138), 0x6F9BC138 },
	};
	return objects;
}

// Functions referenced by the tables, with their address in the original dll
const std::vector<std::pair<const void*, uintptr_t>>& known_functions()
{
	static const std::vector<std::pair<const void*, uintptr_t>> functions = {
		{ reinterpret_cast<const void*>(&CHATDLG_AdClickCallback), 0x6F9A21A0 },
		{ reinterpret_cast<const void*>(&CHATDLG_ChannelButtonCallback), 0x6F9A2580 },
		{ reinterpret_cast<const void*>(&CHATDLG_ChannelDialogOkCallback), 0x6F9A2C60 },
		{ reinterpret_cast<const void*>(&CHATDLG_ChannelListCallback), 0x6F9A3180 },
		{ reinterpret_cast<const void*>(&CHATDLG_EnterChatButtonCallback), 0x6F9A2E10 },
		{ reinterpret_cast<const void*>(&CHATDLG_GemButtonCallback), 0x6F9AB0D0 },
		{ reinterpret_cast<const void*>(&CHATDLG_HelpOkCallback), 0x6F9AB1D0 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderButtonCallback), 0x6F9A2930 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderCancelCallback), 0x6F9A7910 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderExpansionHardcoreCallback), 0x6F9A9D30 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderExpansionStandardCallback), 0x6F9A9A60 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderHardcoreCallback), 0x6F9A7F60 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderMenuCancelCallback), 0x6F9A7760 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderMenuCloseCallback), 0x6F9A7E50 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderNextCallback), 0x6F9A7E10 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderPreviousCallback), 0x6F9A7DE0 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderStandardCallback), 0x6F9A9790 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTabAmazonCallback), 0x6F9AA230 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTabAssassinCallback), 0x6F9AAC50 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTabBarbarianCallback), 0x6F9AA8F0 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTabDruidCallback), 0x6F9AAAA0 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTabNecromancerCallback), 0x6F9AA590 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTabOverallCallback), 0x6F9AA080 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTabPaladinCallback), 0x6F9AA740 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTabSorceressCallback), 0x6F9AA3E0 },
		{ reinterpret_cast<const void*>(&CHATDLG_LadderTimerCallback), 0x6F9A7C30 },
		{ reinterpret_cast<const void*>(&CHATDLG_PopupButtonCallback), 0x6F9A76A0 },
		{ reinterpret_cast<const void*>(&CHATDLG_QuitButtonCallback), 0x6F9A1FA0 },
		{ reinterpret_cast<const void*>(&CHATDLG_UserListDownCallback), 0x6F9A2180 },
		{ reinterpret_cast<const void*>(&CHATDLG_UserListPageDownCallback), 0x6F9A2150 },
		{ reinterpret_cast<const void*>(&CHATDLG_UserListPageUpCallback), 0x6F9A2130 },
		{ reinterpret_cast<const void*>(&CHATDLG_UserListUpCallback), 0x6F9A2170 },
		{ reinterpret_cast<const void*>(&CHATDLG_WarningCancelCallback), 0x6F9A6AC0 },
		{ reinterpret_cast<const void*>(&CHATDLG_WarningOkCallback), 0x6F9A62D0 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_EmoteButtonCallback), 0x6F9AC050 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_HelpButtonCallback), 0x6F9ABE20 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnChannel), 0x6F9AD680 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnChannelDoesNotExist), 0x6F9AE770 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnChannelFull), 0x6F9AE570 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnChannelRestricted), 0x6F9AE670 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnEmote), 0x6F9AE790 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnError), 0x6F9AE490 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnIgnoredEvent), 0x6F9AF020 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnInfo), 0x6F9AE3B0 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnJoin), 0x6F9ACF10 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnLeave), 0x6F9AD2F0 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnShowUser), 0x6F9AC570 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnTalk), 0x6F9ADFC0 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnUnknownEvent), 0x6F9AC0F0 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnUserFlags), 0x6F9AD800 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnWhisper), 0x6F9AEA10 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_OnWhisperSent), 0x6F9AED90 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_SendButtonCallback), 0x6F9ABB50 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_SquelchButtonCallback), 0x6F9ABC10 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_UnsquelchButtonCallback), 0x6F9ABE40 },
		{ reinterpret_cast<const void*>(&COMCALLBACK_WhisperButtonCallback), 0x6F9ABBB0 },
		{ reinterpret_cast<const void*>(&GATE_ClickBoxCallback), 0x6F9B1D30 },
		{ reinterpret_cast<const void*>(&GATE_CreateButtonCallback), 0x6F9B1CF0 },
		{ reinterpret_cast<const void*>(&GATE_CreateGameCallback), 0x6F9B1390 },
		{ reinterpret_cast<const void*>(&GATE_GameListCallback), 0x6F9AFC80 },
		{ reinterpret_cast<const void*>(&GATE_GameQueueCancelCallback), 0x6F9B1370 },
		{ reinterpret_cast<const void*>(&GATE_GameQueueTimerCallback), 0x6F9B03E0 },
		{ reinterpret_cast<const void*>(&GATE_HellDifficultyCallback), 0x6F9B1DE0 },
		{ reinterpret_cast<const void*>(&GATE_JoinButtonCallback), 0x6F9B1CA0 },
		{ reinterpret_cast<const void*>(&GATE_JoinGameCallback), 0x6F9B1920 },
		{ reinterpret_cast<const void*>(&GATE_LevelDifferenceCheckboxCallback), 0x6F9B0DC0 },
		{ reinterpret_cast<const void*>(&GATE_LevelDifferenceDownCallback), 0x6F9B1030 },
		{ reinterpret_cast<const void*>(&GATE_LevelDifferenceUpCallback), 0x6F9B0FD0 },
		{ reinterpret_cast<const void*>(&GATE_MaxPlayersDownCallback), 0x6F9B0F70 },
		{ reinterpret_cast<const void*>(&GATE_MaxPlayersUpCallback), 0x6F9B0F10 },
		{ reinterpret_cast<const void*>(&GATE_NightmareDifficultyCallback), 0x6F9B1D90 },
		{ reinterpret_cast<const void*>(&GATE_NormalDifficultyCallback), 0x6F9B1D40 },
		{ reinterpret_cast<const void*>(&GATE_ProfileCancelCallback), 0x6F9B2570 },
		{ reinterpret_cast<const void*>(&GATE_ProfileLadderCallback), 0x6F9B2420 },
		{ reinterpret_cast<const void*>(&GATE_ProfileOkCallback), 0x6F9B2660 },
	};
	return functions;
}

// Expected value of a pointer of a D2MOO table in the original dll, or 0 if the pointer is unknown
uintptr_t translate_pointer(const void* pMooPointer)
{
	for (const auto& [pFunction, nAddress] : known_functions())
	{
		if (pFunction == pMooPointer)
		{
			return original_d2multi_address(nAddress);
		}
	}

	const auto nPointer = reinterpret_cast<uintptr_t>(pMooPointer);
	for (const KnownObject& object : known_objects())
	{
		const auto nBegin = reinterpret_cast<uintptr_t>(object.pMooObject);
		if (nPointer >= nBegin && nPointer < nBegin + object.nSize)
		{
			return original_d2multi_address(object.nOriginalAddress) + (nPointer - nBegin);
		}
	}

	return 0;
}

// Checks a pointer of a D2MOO table against the same pointer in the original table.
// Small values are stored in some pointer fields, they are compared as is.
void check_pointer(const void* pMooPointer, uintptr_t nOriginalPointer, const char* szField)
{
	CAPTURE(szField);
	const auto nMooPointer = reinterpret_cast<uintptr_t>(pMooPointer);
	if (nMooPointer < 0x10000)
	{
		CHECK_EQ(nOriginalPointer, nMooPointer);
		return;
	}

	const uintptr_t nExpected = translate_pointer(pMooPointer);
	if (nExpected)
	{
		CHECK_EQ(nOriginalPointer, nExpected);
	}
	else
	{
		const auto nBase = reinterpret_cast<uintptr_t>(get_original_d2multi());
		CHECK_GE(nOriginalPointer, nBase);
		CHECK_LT(nOriginalPointer, nBase + 0x40000);
	}
}
}


TEST_SUITE("D2MultiDataTests")
{
	TEST_CASE("D2Multi.0x6F9BC138")
	{
		const auto pOriginal = original_d2multi_global<D2WinControlInitStrc>(0x6F9BC138);
		for (size_t i = 0; i < CTRLINIT_COUNT; ++i)
		{
			CAPTURE(i);
			const D2WinControlInitStrc& moo = gaControlInits_6F9BC138[i];
			const D2WinControlInitStrc& original = pOriginal[i];
			CHECK_EQ(moo.nType, original.nType);
			CHECK_EQ(moo.nX, original.nX);
			CHECK_EQ(moo.nY, original.nY);
			CHECK_EQ(moo.nWidth, original.nWidth);
			CHECK_EQ(moo.nHeight, original.nHeight);
			CHECK_EQ(moo.field_14, original.field_14);
			CHECK_EQ(moo.nStringId, original.nStringId);
			CHECK_EQ(moo.field_2C, original.field_2C);
			check_pointer(moo.ppCellFile, reinterpret_cast<uintptr_t>(original.ppCellFile), "ppCellFile");
			check_pointer(reinterpret_cast<const void*>(moo.pfCallback), reinterpret_cast<uintptr_t>(original.pfCallback), "pfCallback");
			check_pointer(moo.field_24, reinterpret_cast<uintptr_t>(original.field_24), "field_24");
			check_pointer(moo.field_28, reinterpret_cast<uintptr_t>(original.field_28), "field_28");
		}

		// The table ends where the next global of the original dll (gnLastChannelListClickedLine_6F9BDE78) starts
		CHECK_EQ(sizeof(gaControlInits_6F9BC138), 0x6F9BDE78 - 0x6F9BC138);
	}

	TEST_CASE("D2Multi.0x6F9BC0E8")
	{
		const auto pOriginal = original_d2multi_global<D2AnimatedImageDescriptor>(0x6F9BC0E8);
		for (int i = 0; i < 5; ++i)
		{
			CAPTURE(i);
			CHECK_EQ(gaLogoAnimations_6F9BC0E8[i].eDrawMode, pOriginal[i].eDrawMode);
			CHECK_EQ(gaLogoAnimations_6F9BC0E8[i].nAnimSpeed, pOriginal[i].nAnimSpeed);
			check_pointer(gaLogoAnimations_6F9BC0E8[i].ppCellFile1, reinterpret_cast<uintptr_t>(pOriginal[i].ppCellFile1), "ppCellFile1");
			check_pointer(gaLogoAnimations_6F9BC0E8[i].ppCellFile2, reinterpret_cast<uintptr_t>(pOriginal[i].ppCellFile2), "ppCellFile2");
		}
	}

	TEST_CASE("D2Multi.0x6F9BE798")
	{
		const auto pOriginal = original_d2multi_global<uintptr_t>(0x6F9BE798);
		for (size_t i = 0; i < CHATEVENT_COUNT; ++i)
		{
			CAPTURE(i);
			check_pointer(reinterpret_cast<const void*>(gapfComCallbacks_6F9BE798[i]), pOriginal[i], "callback");
		}
	}

	TEST_CASE("D2Multi.0x6F9AF3B0 (#1)")
	{
		using QueryInterfaceFunction = D2MultiInterfaceStrc*(__cdecl*)();
		const auto pfOriginalQueryInterface = reinterpret_cast<QueryInterfaceFunction>(GetProcAddress(get_original_d2multi(), MAKEINTRESOURCEA(1)));
		REQUIRE(pfOriginalQueryInterface != nullptr);
		CHECK_EQ(reinterpret_cast<uintptr_t>(pfOriginalQueryInterface), original_d2multi_address(0x6F9AF3B0));

		const auto pOriginal = reinterpret_cast<const uintptr_t*>(pfOriginalQueryInterface());
		// CHATDLG_RunModule
		CHECK_EQ(pOriginal[0], original_d2multi_address(0x6F9A6100));
		CHECK_EQ(reinterpret_cast<const void*>(QueryInterface()->pfRunModule), reinterpret_cast<const void*>(&CHATDLG_RunModule));
	}
}
