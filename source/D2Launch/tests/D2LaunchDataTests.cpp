#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <D2WinAnimImage.h>
#include <D2WinControlHeader.h>

#include <BNet.h>
#include <CharSel.h>
#include <D2Launch.h>
#include <MainMenus.h>

#include "D2LaunchTestFixtures.h"


// Globals referenced by the static tables, not declared in the headers
extern D2CellFileStrc* sgpBliznoCellFile;
extern D2CellFileStrc* sgpTrademarkCellFile;
extern D2CellFileStrc* sgpUnusedCellFile;
extern D2CellFileStrc* sgpDiablo2LogoCellFile;
extern D2CellFileStrc* sgpD2LogoBlackLeftCellFile;
extern D2CellFileStrc* sgpD2LogoFireLeftCellFile;
extern D2CellFileStrc* sgpD2LogoBlackRightCellFile;
extern D2CellFileStrc* sgpD2LogoFireRightCellFile;
extern D2CellFileStrc* sgpTitleScreenCellFile;
extern D2CellFileStrc* sgpCursorCellFile;
extern D2CellFileStrc* sgpCreditsBackgroundCellFile;
extern D2CellFileStrc* sgpCharacterCreateCellFile;
extern D2CellFileStrc* sgpFireCellFile;
extern D2CellFileStrc* sgpRealmSelectButtonCellFile;
extern D2CellFileStrc* sgpTallButtonBlankCellFile;
extern D2CellFileStrc* sgpCharacterSelectScreenExpCellFile;
extern D2CellFileStrc* sgpWideButtonBlankCellFile;
extern D2CellFileStrc* sgpMediumButtonBlankCellFile;
extern D2CellFileStrc* sgpShortButtonBlankCellFile;
extern D2CellFileStrc* sgpMediumSelButtonBlankCellFile;
extern D2CellFileStrc* sgpTextBox2CellFile;
extern D2CellFileStrc* sgp3WideButtonBlankCellFile;
extern D2CellFileStrc* sgpEditTextBoxWideCellFile;
extern D2CellFileStrc* sgpWideButtonBlank02CellFile;
extern D2CellFileStrc* sgpNarrowButtonBlankCellFile;
extern D2CellFileStrc* sgpGWListBoxCellFile;
extern D2CellFileStrc* sgpTermsOfUseBackgroundCellFile;
extern D2CellFileStrc* sgpDifficultyLevelsCellFile;
extern D2CellFileStrc* sgpCinematicsSelectionCellFile;
extern D2CellFileStrc* sgpCinematicsSelectionExpCellFile;
extern D2CellFileStrc* sgpCharSelectBoxCellFile;
extern D2CellFileStrc* sgpCharSelectBoxGreyCellFile;
extern D2CellFileStrc* sgpPopUpOkCancelCellFile;
extern D2CellFileStrc* sgpPopUpOkCancel2CellFile;
extern D2CellFileStrc* sgpSelectCharArrowsCellFile;
extern D2CellFileStrc* sgpRealmSelectCellFile;
extern D2CellFileStrc* sgpRealmSelectButtonThinCellFile;
extern D2CellFileStrc* sgpCreateNewCharImageCellFile;
extern D2CellFileStrc* sgpPopUpOkCellFile;
extern D2CellFileStrc* sgpPopUp340x224CellFile;
extern D2CellFileStrc* sgpPopUpWideCellFile;
extern D2CellFileStrc* sgpPopUpLargestCellFile;
extern D2CellFileStrc* sgpTileableDialogCellFile;
extern D2CellFileStrc* sgpPopUpOk2CellFile;
extern D2CellFileStrc* sgpOkCancelButtonBlankCellFile;
extern D2CellFileStrc* sgpCancelButtonBlankCellFile;
extern D2CellFileStrc* sgpPasswordCellFile;
extern D2CellFileStrc* sgpCharCreateTextBoxCellFile;
extern D2CellFileStrc* sgpClickBoxCellFile;
extern D2CellFileStrc* sgpJoinGameClickBoxGreyCellFile;
extern D2CellFileStrc* sgpRealmBackgroundCellFile;
extern D2CellFileStrc* sgpJoinGameScrollBarsCellFile;
extern D2CellFileStrc* sgpTcpIpBackgroundCellFile;
extern D2CellFileStrc* sgpIpAddressBoxCellFile;
extern D2CellFileStrc* sgpDownloadPatchBackgroundCellFile;
extern D2CellFileStrc* sgpDownloadPatchBallCellFile;
extern D2CellFileStrc* sgpAssassinAnimCellFiles[5];
extern D2CellFileStrc* sgpDruidAnimCellFiles[5];
extern D2CellFileStrc* sgpAmazonAnimCellFiles[5];
extern D2CellFileStrc* sgpNecromancerAnimCellFiles[5];
extern D2CellFileStrc* sgpBarbarianAnimCellFiles[5];
extern D2CellFileStrc* sgpSorceressAnimCellFiles[5];
extern D2CellFileStrc* sgpPaladinAnimCellFiles[5];
extern D2CellFileStrc* sgpNecromancerOverlayCellFiles[3];
extern D2CellFileStrc* sgpSorceressOverlayCellFiles[3];
extern D2CellFileStrc* sgpBarbarianOverlayCellFile;
extern D2CellFileStrc* sgpPaladinOverlayCellFile;
extern D2AnimatedImageDescriptor gaAssassinAnimDescriptors[5];
extern D2AnimatedImageDescriptor gaDruidAnimDescriptors[5];
extern D2AnimatedImageDescriptor gaAmazonAnimDescriptors[5];
extern D2AnimatedImageDescriptor gaNecromancerAnimDescriptors[5];
extern D2AnimatedImageDescriptor gaBarbarianAnimDescriptors[5];
extern D2AnimatedImageDescriptor gaSorceressAnimDescriptors[5];
extern D2AnimatedImageDescriptor gaPaladinAnimDescriptors[5];
extern D2AnimatedImageDescriptor gaLogoLeftAnimDescriptors[5];
extern D2AnimatedImageDescriptor gaLogoRightAnimDescriptors[5];
extern int32_t gaScrollBarInfos[6][3];


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
		{ &sgpBliznoCellFile, sizeof(sgpBliznoCellFile), 0x6FA3CE6C },
		{ &sgpTrademarkCellFile, sizeof(sgpTrademarkCellFile), 0x6FA3CE70 },
		{ &sgpUnusedCellFile, sizeof(sgpUnusedCellFile), 0x6FA3CE74 },
		{ &sgpDiablo2LogoCellFile, sizeof(sgpDiablo2LogoCellFile), 0x6FA3CE78 },
		{ &sgpD2LogoBlackLeftCellFile, sizeof(sgpD2LogoBlackLeftCellFile), 0x6FA3CE7C },
		{ &sgpD2LogoFireLeftCellFile, sizeof(sgpD2LogoFireLeftCellFile), 0x6FA3CE80 },
		{ &sgpD2LogoBlackRightCellFile, sizeof(sgpD2LogoBlackRightCellFile), 0x6FA3CE84 },
		{ &sgpD2LogoFireRightCellFile, sizeof(sgpD2LogoFireRightCellFile), 0x6FA3CE88 },
		{ &sgpTitleScreenCellFile, sizeof(sgpTitleScreenCellFile), 0x6FA3CE8C },
		{ &sgpCursorCellFile, sizeof(sgpCursorCellFile), 0x6FA3CE90 },
		{ &sgpCreditsBackgroundCellFile, sizeof(sgpCreditsBackgroundCellFile), 0x6FA3CE94 },
		{ &sgpCharacterCreateCellFile, sizeof(sgpCharacterCreateCellFile), 0x6FA3CE98 },
		{ &sgpFireCellFile, sizeof(sgpFireCellFile), 0x6FA3CE9C },
		{ &sgpRealmSelectButtonCellFile, sizeof(sgpRealmSelectButtonCellFile), 0x6FA3CEA0 },
		{ &sgpTallButtonBlankCellFile, sizeof(sgpTallButtonBlankCellFile), 0x6FA3CEA4 },
		{ &sgpCharacterSelectScreenExpCellFile, sizeof(sgpCharacterSelectScreenExpCellFile), 0x6FA3CEA8 },
		{ &sgpWideButtonBlankCellFile, sizeof(sgpWideButtonBlankCellFile), 0x6FA3CEAC },
		{ &sgpMediumButtonBlankCellFile, sizeof(sgpMediumButtonBlankCellFile), 0x6FA3CEB0 },
		{ &sgpShortButtonBlankCellFile, sizeof(sgpShortButtonBlankCellFile), 0x6FA3CEB4 },
		{ &sgpMediumSelButtonBlankCellFile, sizeof(sgpMediumSelButtonBlankCellFile), 0x6FA3CEB8 },
		{ &sgpTextBox2CellFile, sizeof(sgpTextBox2CellFile), 0x6FA3CEBC },
		{ &sgp3WideButtonBlankCellFile, sizeof(sgp3WideButtonBlankCellFile), 0x6FA3CEC0 },
		{ &sgpEditTextBoxWideCellFile, sizeof(sgpEditTextBoxWideCellFile), 0x6FA3CEC4 },
		{ &sgpWideButtonBlank02CellFile, sizeof(sgpWideButtonBlank02CellFile), 0x6FA3CEC8 },
		{ &sgpNarrowButtonBlankCellFile, sizeof(sgpNarrowButtonBlankCellFile), 0x6FA3CECC },
		{ &sgpGWListBoxCellFile, sizeof(sgpGWListBoxCellFile), 0x6FA3CED0 },
		{ &sgpTermsOfUseBackgroundCellFile, sizeof(sgpTermsOfUseBackgroundCellFile), 0x6FA3CED8 },
		{ &gpCharSelectBackgroundCellFile, sizeof(gpCharSelectBackgroundCellFile), 0x6FA3CEDC },
		{ &sgpDifficultyLevelsCellFile, sizeof(sgpDifficultyLevelsCellFile), 0x6FA3CEE0 },
		{ &sgpCinematicsSelectionCellFile, sizeof(sgpCinematicsSelectionCellFile), 0x6FA3CEE4 },
		{ &sgpCinematicsSelectionExpCellFile, sizeof(sgpCinematicsSelectionExpCellFile), 0x6FA3CEE8 },
		{ &sgpCharSelectBoxCellFile, sizeof(sgpCharSelectBoxCellFile), 0x6FA3CEEC },
		{ &sgpCharSelectBoxGreyCellFile, sizeof(sgpCharSelectBoxGreyCellFile), 0x6FA3CEF0 },
		{ &sgpPopUpOkCancelCellFile, sizeof(sgpPopUpOkCancelCellFile), 0x6FA3CEF4 },
		{ &sgpPopUpOkCancel2CellFile, sizeof(sgpPopUpOkCancel2CellFile), 0x6FA3CEF8 },
		{ &sgpSelectCharArrowsCellFile, sizeof(sgpSelectCharArrowsCellFile), 0x6FA3CEFC },
		{ &sgpRealmSelectCellFile, sizeof(sgpRealmSelectCellFile), 0x6FA3CF00 },
		{ &sgpRealmSelectButtonThinCellFile, sizeof(sgpRealmSelectButtonThinCellFile), 0x6FA3CF04 },
		{ &sgpCreateNewCharImageCellFile, sizeof(sgpCreateNewCharImageCellFile), 0x6FA3CF08 },
		{ &sgpPopUpOkCellFile, sizeof(sgpPopUpOkCellFile), 0x6FA3CF0C },
		{ &sgpPopUp340x224CellFile, sizeof(sgpPopUp340x224CellFile), 0x6FA3CF10 },
		{ &sgpPopUpWideCellFile, sizeof(sgpPopUpWideCellFile), 0x6FA3CF14 },
		{ &sgpPopUpLargestCellFile, sizeof(sgpPopUpLargestCellFile), 0x6FA3CF18 },
		{ &sgpTileableDialogCellFile, sizeof(sgpTileableDialogCellFile), 0x6FA3CF1C },
		{ &sgpPopUpOk2CellFile, sizeof(sgpPopUpOk2CellFile), 0x6FA3CF20 },
		{ &sgpOkCancelButtonBlankCellFile, sizeof(sgpOkCancelButtonBlankCellFile), 0x6FA3CF24 },
		{ &sgpCancelButtonBlankCellFile, sizeof(sgpCancelButtonBlankCellFile), 0x6FA3CF28 },
		{ &sgpPasswordCellFile, sizeof(sgpPasswordCellFile), 0x6FA3CF2C },
		{ &sgpCharCreateTextBoxCellFile, sizeof(sgpCharCreateTextBoxCellFile), 0x6FA3CF30 },
		{ &sgpClickBoxCellFile, sizeof(sgpClickBoxCellFile), 0x6FA3CF34 },
		{ &sgpJoinGameClickBoxGreyCellFile, sizeof(sgpJoinGameClickBoxGreyCellFile), 0x6FA3CF38 },
		{ &sgpRealmBackgroundCellFile, sizeof(sgpRealmBackgroundCellFile), 0x6FA3CF3C },
		{ &sgpJoinGameScrollBarsCellFile, sizeof(sgpJoinGameScrollBarsCellFile), 0x6FA3CF40 },
		{ &sgpTcpIpBackgroundCellFile, sizeof(sgpTcpIpBackgroundCellFile), 0x6FA3CF44 },
		{ &sgpIpAddressBoxCellFile, sizeof(sgpIpAddressBoxCellFile), 0x6FA3CF48 },
		{ &sgpDownloadPatchBackgroundCellFile, sizeof(sgpDownloadPatchBackgroundCellFile), 0x6FA3CF4C },
		{ &sgpDownloadPatchBallCellFile, sizeof(sgpDownloadPatchBallCellFile), 0x6FA3CF50 },
		{ sgpAssassinAnimCellFiles, sizeof(sgpAssassinAnimCellFiles), 0x6FA3CF54 },
		{ sgpDruidAnimCellFiles, sizeof(sgpDruidAnimCellFiles), 0x6FA3CF68 },
		{ sgpAmazonAnimCellFiles, sizeof(sgpAmazonAnimCellFiles), 0x6FA3CF7C },
		{ sgpNecromancerAnimCellFiles, sizeof(sgpNecromancerAnimCellFiles), 0x6FA3CF90 },
		{ sgpBarbarianAnimCellFiles, sizeof(sgpBarbarianAnimCellFiles), 0x6FA3CFA4 },
		{ sgpSorceressAnimCellFiles, sizeof(sgpSorceressAnimCellFiles), 0x6FA3CFB8 },
		{ sgpPaladinAnimCellFiles, sizeof(sgpPaladinAnimCellFiles), 0x6FA3CFCC },
		{ sgpNecromancerOverlayCellFiles, sizeof(sgpNecromancerOverlayCellFiles), 0x6FA3CFFC },
		{ sgpSorceressOverlayCellFiles, sizeof(sgpSorceressOverlayCellFiles), 0x6FA3D010 },
		{ &sgpBarbarianOverlayCellFile, sizeof(sgpBarbarianOverlayCellFile), 0x6FA3D024 },
		{ &sgpPaladinOverlayCellFile, sizeof(sgpPaladinOverlayCellFile), 0x6FA3D038 },
		{ gaAssassinAnimDescriptors, sizeof(gaAssassinAnimDescriptors), 0x6FA33388 },
		{ gaDruidAnimDescriptors, sizeof(gaDruidAnimDescriptors), 0x6FA333D8 },
		{ gaAmazonAnimDescriptors, sizeof(gaAmazonAnimDescriptors), 0x6FA33428 },
		{ gaNecromancerAnimDescriptors, sizeof(gaNecromancerAnimDescriptors), 0x6FA33478 },
		{ gaBarbarianAnimDescriptors, sizeof(gaBarbarianAnimDescriptors), 0x6FA334C8 },
		{ gaSorceressAnimDescriptors, sizeof(gaSorceressAnimDescriptors), 0x6FA33518 },
		{ gaPaladinAnimDescriptors, sizeof(gaPaladinAnimDescriptors), 0x6FA33568 },
		{ gaLogoLeftAnimDescriptors, sizeof(gaLogoLeftAnimDescriptors), 0x6FA335B8 },
		{ gaLogoRightAnimDescriptors, sizeof(gaLogoRightAnimDescriptors), 0x6FA33608 },
		{ gaMenuFonts, sizeof(gaMenuFonts), 0x6FA33340 },
		{ gaScrollBarInfos, sizeof(gaScrollBarInfos), 0x6FA33658 },
		{ gaControlInits, sizeof(gaControlInits), 0x6FA336A0 },
	};
	return objects;
}

// Functions referenced by the control table, with their address in the original dll
const std::vector<std::pair<const void*, uintptr_t>>& known_functions()
{
	static const std::vector<std::pair<const void*, uintptr_t>> functions = {
		{ reinterpret_cast<const void*>(&BNET_AccountOptionsBackCallback), 0x6FA128A0 },
		{ reinterpret_cast<const void*>(&BNET_BackToAccountOptionsCallback), 0x6FA12770 },
		{ reinterpret_cast<const void*>(&BNET_ChangeEmailCallback), 0x6FA12890 },
		{ reinterpret_cast<const void*>(&BNET_ChangeEmailOkCallback), 0x6FA12DF0 },
		{ reinterpret_cast<const void*>(&BNET_ChangePasswordCallback), 0x6FA12870 },
		{ reinterpret_cast<const void*>(&BNET_RegisterEmailCancelCallback), 0x6FA12160 },
		{ reinterpret_cast<const void*>(&BNET_RegisterEmailLaterCallback), 0x6FA12100 },
		{ reinterpret_cast<const void*>(&BNET_RegisterEmailOkCallback), 0x6FA11FD0 },
		{ reinterpret_cast<const void*>(&BNET_ResetPasswordCallback), 0x6FA12880 },
		{ reinterpret_cast<const void*>(&BNET_ResetPasswordOkCallback), 0x6FA12660 },
		{ reinterpret_cast<const void*>(&CHARSEL_ChangeRealmCallback), 0x6FA13820 },
		{ reinterpret_cast<const void*>(&CHARSEL_CharacterSlotClickCallback), 0x6FA15520 },
		{ reinterpret_cast<const void*>(&CHARSEL_ConvertToExpansionCallback), 0x6FA15B10 },
		{ reinterpret_cast<const void*>(&CHARSEL_ConvertToExpansionCancelCallback), 0x6FA15BD0 },
		{ reinterpret_cast<const void*>(&CHARSEL_ConvertToExpansionConfirmCallback), 0x6FA15BF0 },
		{ reinterpret_cast<const void*>(&CHARSEL_DeleteCharacterCallback), 0x6FA15DD0 },
		{ reinterpret_cast<const void*>(&CHARSEL_DeleteCharacterCancelCallback), 0x6FA15DC0 },
		{ reinterpret_cast<const void*>(&CHARSEL_DeleteCharacterConfirmCallback), 0x6FA15E50 },
		{ reinterpret_cast<const void*>(&CHARSEL_HellDifficultyCallback), 0x6FA15A80 },
		{ reinterpret_cast<const void*>(&CHARSEL_KeyDownCallback), 0x6FA16260 },
		{ reinterpret_cast<const void*>(&CHARSEL_NightmareDifficultyCallback), 0x6FA159F0 },
		{ reinterpret_cast<const void*>(&CHARSEL_NormalDifficultyCallback), 0x6FA15960 },
		{ reinterpret_cast<const void*>(&CHARSEL_OkCallback), 0x6FA156C0 },
		{ reinterpret_cast<const void*>(&CHARSEL_RealmListClickCallback), 0x6FA134B0 },
		{ reinterpret_cast<const void*>(&CHARSEL_RealmSelectCancelCallback), 0x6FA13230 },
		{ reinterpret_cast<const void*>(&CHARSEL_RealmSelectOkCallback), 0x6FA13130 },
		{ reinterpret_cast<const void*>(&CHARSEL_RealmTimerCallback), 0x6FA164F0 },
		{ reinterpret_cast<const void*>(&CHARSEL_ScrollBarCallback), 0x6FA15FC0 },
		{ reinterpret_cast<const void*>(&CHARSEL_ScrollDownCallback), 0x6FA15F70 },
		{ reinterpret_cast<const void*>(&CHARSEL_ScrollUpCallback), 0x6FA15F40 },
		{ reinterpret_cast<const void*>(&MENU_AcceptTermsOfServiceCallback), 0x6FA1B1A0 },
		{ reinterpret_cast<const void*>(&MENU_AccountOptionsCallback), 0x6FA25C80 },
		{ reinterpret_cast<const void*>(&MENU_AmazonHoverCallback), 0x6FA1CBE0 },
		{ reinterpret_cast<const void*>(&MENU_AssassinHoverCallback), 0x6FA1CC90 },
		{ reinterpret_cast<const void*>(&MENU_BackToMainMenuCallback), 0x6FA26090 },
		{ reinterpret_cast<const void*>(&MENU_BarbarianHoverCallback), 0x6FA1CEA0 },
		{ reinterpret_cast<const void*>(&MENU_BattleNetCallback), 0x6FA21FD0 },
		{ reinterpret_cast<const void*>(&MENU_CancelPatchCallback), 0x6FA19300 },
		{ reinterpret_cast<const void*>(&MENU_ChangePasswordOkCallback), 0x6FA26640 },
		{ reinterpret_cast<const void*>(&MENU_CharClassClickCallback), 0x6FA1C3A0 },
		{ reinterpret_cast<const void*>(&MENU_CharacterCreationExitCallback), 0x6FA1EDE0 },
		{ reinterpret_cast<const void*>(&MENU_CharacterSelectionExitCallback), 0x6FA24440 },
		{ reinterpret_cast<const void*>(&MENU_CinematicsCancelCallback), 0x6FA21D40 },
		{ reinterpret_cast<const void*>(&MENU_CloseSubChildrenCallback), 0x6FA27750 },
		{ reinterpret_cast<const void*>(&MENU_CreateAccountInfoCancelCallback), 0x6FA26FE0 },
		{ reinterpret_cast<const void*>(&MENU_CreateAccountInfoOkCallback), 0x6FA26DE0 },
		{ reinterpret_cast<const void*>(&MENU_CreateAccountOkCallback), 0x6FA260A0 },
		{ reinterpret_cast<const void*>(&MENU_CreateCharacterCancelCallback), 0x6FA1B4C0 },
		{ reinterpret_cast<const void*>(&MENU_CreateCharacterConfirmCallback), 0x6FA1B290 },
		{ reinterpret_cast<const void*>(&MENU_CreateCharacterOkCallback), 0x6FA1B500 },
		{ reinterpret_cast<const void*>(&MENU_CreateNewAccountCallback), 0x6FA25450 },
		{ reinterpret_cast<const void*>(&MENU_CreateNewCharacterCallback), 0x6FA24050 },
		{ reinterpret_cast<const void*>(&MENU_CreditsTimerCallback), 0x6FA1F9E0 },
		{ reinterpret_cast<const void*>(&MENU_DruidHoverCallback), 0x6FA1CD40 },
		{ reinterpret_cast<const void*>(&MENU_ExitGameCallback), 0x6FA22900 },
		{ reinterpret_cast<const void*>(&MENU_ExpansionCheckBoxCallback), 0x6FA1C370 },
		{ reinterpret_cast<const void*>(&MENU_GatewayCancelCallback), 0x6FA22660 },
		{ reinterpret_cast<const void*>(&MENU_GatewayListClickCallback), 0x6FA222D0 },
		{ reinterpret_cast<const void*>(&MENU_GatewayOkCallback), 0x6FA224E0 },
		{ reinterpret_cast<const void*>(&MENU_HardcoreCheckBoxCallback), 0x6FA1C330 },
		{ reinterpret_cast<const void*>(&MENU_InsertPlayDiscRetryCallback), 0x6FA21D80 },
		{ reinterpret_cast<const void*>(&MENU_InsertVideoDiscCancelCallback), 0x6FA21DA0 },
		{ reinterpret_cast<const void*>(&MENU_InsertVideoDiscRetryCallback), 0x6FA21D90 },
		{ reinterpret_cast<const void*>(&MENU_LadderCheckBoxCallback), 0x6FA1C350 },
		{ reinterpret_cast<const void*>(&MENU_LoginOkCallback), 0x6FA25CC0 },
		{ reinterpret_cast<const void*>(&MENU_NecromancerHoverCallback), 0x6FA1CDF0 },
		{ reinterpret_cast<const void*>(&MENU_OpenBattleNetCallback), 0x6FA1EDC0 },
		{ reinterpret_cast<const void*>(&MENU_OtherMultiplayerCallback), 0x6FA1EF30 },
		{ reinterpret_cast<const void*>(&MENU_PaladinHoverCallback), 0x6FA1CF50 },
		{ reinterpret_cast<const void*>(&MENU_PlayAct2CinematicCallback), 0x6FA20680 },
		{ reinterpret_cast<const void*>(&MENU_PlayAct3CinematicCallback), 0x6FA20A50 },
		{ reinterpret_cast<const void*>(&MENU_PlayAct4CinematicCallback), 0x6FA20E20 },
		{ reinterpret_cast<const void*>(&MENU_PlayAct4EndCinematicCallback), 0x6FA211F0 },
		{ reinterpret_cast<const void*>(&MENU_PlayExpansionIntroCinematicCallback), 0x6FA215C0 },
		{ reinterpret_cast<const void*>(&MENU_PlayExpansionOutroCinematicCallback), 0x6FA21980 },
		{ reinterpret_cast<const void*>(&MENU_PlayIntroCinematicCallback), 0x6FA202B0 },
		{ reinterpret_cast<const void*>(&MENU_PopupButtonCallback), 0x6FA25430 },
		{ reinterpret_cast<const void*>(&MENU_ShowCannotConnectToBattleNetPopup), 0x6FA18EA0 },
		{ reinterpret_cast<const void*>(&MENU_ShowCinematicsCallback), 0x6FA1FD10 },
		{ reinterpret_cast<const void*>(&MENU_ShowCreditsCallback), 0x6FA1F5E0 },
		{ reinterpret_cast<const void*>(&MENU_ShowGatewaySelectionCallback), 0x6FA21FF0 },
		{ reinterpret_cast<const void*>(&MENU_SinglePlayerCallback), 0x6FA1EC10 },
		{ reinterpret_cast<const void*>(&MENU_SkipLogoCallback), 0x6FA24060 },
		{ reinterpret_cast<const void*>(&MENU_SorceressHoverCallback), 0x6FA1CB30 },
		{ reinterpret_cast<const void*>(&MENU_TcpIpCallback), 0x6FA21FB0 },
		{ reinterpret_cast<const void*>(&MENU_TcpIpHostButtonHoverCallback), 0x6FA1A4E0 },
		{ reinterpret_cast<const void*>(&MENU_TcpIpHostGameCallback), 0x6FA22930 },
		{ reinterpret_cast<const void*>(&MENU_TcpIpJoinButtonHoverCallback), 0x6FA1A520 },
		{ reinterpret_cast<const void*>(&MENU_TcpIpJoinGameCallback), 0x6FA22BB0 },
		{ reinterpret_cast<const void*>(&MENU_TcpIpJoinGameCancelCallback), 0x6FA22E80 },
		{ reinterpret_cast<const void*>(&MENU_TcpIpJoinGameOkCallback), 0x6FA22F60 },
		{ reinterpret_cast<const void*>(&MENU_TcpIpTimerCallback), 0x6FA19EE0 },
		{ reinterpret_cast<const void*>(&MENU_TermsOfServicePageDownCallback), 0x6FA1B220 },
		{ reinterpret_cast<const void*>(&MENU_TermsOfServicePageUpCallback), 0x6FA1B1B0 },
	};
	return functions;
}

// Expected value of a pointer of a D2MOO table in the original dll, or 0 if the pointer is unknown
uintptr_t translate_pointer(const void* pMooPointer)
{
	if (!pMooPointer)
	{
		return 0;
	}

	for (const auto& [pFunction, nAddress] : known_functions())
	{
		if (pFunction == pMooPointer)
		{
			return original_d2launch_address(nAddress);
		}
	}

	const auto nPointer = reinterpret_cast<uintptr_t>(pMooPointer);
	for (const KnownObject& object : known_objects())
	{
		const auto nBegin = reinterpret_cast<uintptr_t>(object.pMooObject);
		if (nPointer >= nBegin && nPointer < nBegin + object.nSize)
		{
			return original_d2launch_address(object.nOriginalAddress) + (nPointer - nBegin);
		}
	}

	return 0;
}

// Checks a pointer of a D2MOO table against the same pointer in the original table
void check_pointer(const void* pMooPointer, uintptr_t nOriginalPointer, const char* szField)
{
	CAPTURE(szField);
	if (!pMooPointer)
	{
		CHECK_EQ(nOriginalPointer, 0);
		return;
	}

	const uintptr_t nExpected = translate_pointer(pMooPointer);
	if (nExpected)
	{
		CHECK_EQ(nOriginalPointer, nExpected);
	}
	else
	{
		// Pointer to something not listed, it must point into the original dll
		const auto nBase = reinterpret_cast<uintptr_t>(get_original_d2launch());
		CHECK_GE(nOriginalPointer, nBase);
		CHECK_LT(nOriginalPointer, nBase + 0x40000);
	}
}
}


TEST_SUITE("D2LaunchDataTests")
{
	TEST_CASE("D2Launch.0x6FA336A0")
	{
		static_assert(sizeof(D2WinControlInitStrc) == 0x30, "");
		const auto pOriginal = original_d2launch_global<D2WinControlInitStrc>(0x6FA336A0);

		for (size_t i = 0; i < std::size(gaControlInits); ++i)
		{
			CAPTURE(i);
			const D2WinControlInitStrc& moo = gaControlInits[i];
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
	}

	TEST_CASE("D2Launch.0x6FA33340")
	{
		CHECK_EQ(std::memcmp(gaMenuFonts, original_d2launch_global<D2MenuFontStrc>(0x6FA33340), sizeof(gaMenuFonts)), 0);
	}

	TEST_CASE("D2Launch.0x6FA33658")
	{
		CHECK_EQ(std::memcmp(gaScrollBarInfos, original_d2launch_global<int32_t>(0x6FA33658), sizeof(gaScrollBarInfos)), 0);
	}

	TEST_CASE("D2Launch animated image descriptors")
	{
		const std::pair<const D2AnimatedImageDescriptor*, uintptr_t> tables[] = {
			{ gaAssassinAnimDescriptors, 0x6FA33388 },
			{ gaDruidAnimDescriptors, 0x6FA333D8 },
			{ gaAmazonAnimDescriptors, 0x6FA33428 },
			{ gaNecromancerAnimDescriptors, 0x6FA33478 },
			{ gaBarbarianAnimDescriptors, 0x6FA334C8 },
			{ gaSorceressAnimDescriptors, 0x6FA33518 },
			{ gaPaladinAnimDescriptors, 0x6FA33568 },
			{ gaLogoLeftAnimDescriptors, 0x6FA335B8 },
			{ gaLogoRightAnimDescriptors, 0x6FA33608 },
		};

		for (const auto& [pMoo, nAddress] : tables)
		{
			CAPTURE(nAddress);
			const auto pOriginal = original_d2launch_global<D2AnimatedImageDescriptor>(nAddress);
			for (int i = 0; i < 5; ++i)
			{
				CAPTURE(i);
				CHECK_EQ(pMoo[i].eDrawMode, pOriginal[i].eDrawMode);
				CHECK_EQ(pMoo[i].nAnimSpeed, pOriginal[i].nAnimSpeed);
				check_pointer(pMoo[i].ppCellFile1, reinterpret_cast<uintptr_t>(pOriginal[i].ppCellFile1), "ppCellFile1");
				check_pointer(pMoo[i].ppCellFile2, reinterpret_cast<uintptr_t>(pOriginal[i].ppCellFile2), "ppCellFile2");
			}
		}
	}

	TEST_CASE("D2Launch.0x6FA17740 (#1)")
	{
		using QueryInterfaceFunction = D2LaunchInterfaceStrc*(__cdecl*)();
		const auto pfOriginalQueryInterface = reinterpret_cast<QueryInterfaceFunction>(GetProcAddress(get_original_d2launch(), MAKEINTRESOURCEA(1)));
		REQUIRE(pfOriginalQueryInterface != nullptr);
		CHECK_EQ(reinterpret_cast<uintptr_t>(pfOriginalQueryInterface), original_d2launch_address(0x6FA17740));

		const auto pOriginal = reinterpret_cast<const uintptr_t*>(pfOriginalQueryInterface());
		CHECK_EQ(reinterpret_cast<uintptr_t>(pOriginal), original_d2launch_address(0x6FA3333C));
		// MENU_Run
		CHECK_EQ(pOriginal[0], original_d2launch_address(0x6FA1D490));
		CHECK_EQ(reinterpret_cast<const void*>(QueryInterface()->pfRun), reinterpret_cast<const void*>(&MENU_Run));
	}
}
