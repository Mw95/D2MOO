#include "MainMenus.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>

#include <D2Lang.h>
#include <D2StrTable.h>
#include <D2Gfx.h>
#include <Fog.h>
#include <Safesock.h>
#include <Storm.h>
#include <D2MCPClient.h>
#include <D2Net.h>
#include <D2Sound.h>
#include <D2WinMain.h>
#include <D2WinPalette.h>
#include <D2WinSmack.h>
#include <D2WinFont.h>
#include <Window.h>
#include <Client.h>

#include "BNet.h"
#include "CharSel.h"
#include "SaveLoad.h"


//D2Launch.0x6FA31470
const char* const gszFeCharPaletteDat = "palette\\fechar\\pal.dat";
//D2Launch.0x6FA31474
const char* const gszFeCharPalettePl2 = "palette\\fechar\\pal.pl2";
//D2Launch.0x6FA31478
const char* const gszSkyPaletteDat = "palette\\sky\\pal.dat";
//D2Launch.0x6FA3147C
const char* const gszSkyPalettePl2 = "palette\\sky\\pal.pl2";

//D2Launch.0x6FA3CA98
D2WinTextBoxStrc* sgpHostIpTextBox;
//D2Launch.0x6FA3CA9C
D2WinTextBoxStrc* sgpExpansionLabelTextBox;
//D2Launch.0x6FA3CAA0
D2WinAnimImageStrc* sgpCharClassAnimImages[CHARCREATE_NUM_CLASSES];
//D2Launch.0x6FA3CABC
D2WinButtonStrc* sgpCharCreateOkButton;
//D2Launch.0x6FA3CAC4
D2WinEditBoxStrc* sgpNewPasswordEditBox;
//D2Launch.0x6FA3CAC8
D2WinTimerStrc* sgpTcpIpTimer;
//D2Launch.0x6FA3CACC
D2WinTextBoxStrc* sgpCharNameLabelTextBox;
//D2Launch.0x6FA3CAD0
D2WinButtonStrc* sgpExpansionCheckBox;
//D2Launch.0x6FA3CAD4
BOOL sgbPatchCancelled;
//D2Launch.0x6FA3CAD8
D2WinControlStrc* sgpChildren[MAX_CHILDREN];
//D2Launch.0x6FA3CBDC
D2RealmListPacketStrc* sgpRealmListPacket;
//D2Launch.0x6FA3CBE0
D2WinButtonStrc* sgpHardcoreCheckBox;
//D2Launch.0x6FA3CBE4
D2WinImageStrc* sgpExpansionCheckBoxDisabledImage;
//D2Launch.0x6FA3CBE8
D2WinButtonStrc* sgpLoginOkButton;
//D2Launch.0x6FA3CBEC
D2PopupCallback gpfPopupCallback;
//D2Launch.0x6FA3CBF0
D2WinControlStrc* sgpSubChildren[MAX_CHILDREN];
//D2Launch.0x6FA3CCF0
BOOL sgbTcpIpConnected;
//D2Launch.0x6FA3CCF4
D2WinTextBoxStrc* sgpHardcoreLabelTextBox;
//D2Launch.0x6FA3CCF8
D2WinImageStrc* sgpCharNameEditBoxImage;
//D2Launch.0x6FA3CCFC
D2WinButtonStrc* sgpTcpIpHostButton;
//D2Launch.0x6FA3CD00
D2WinTextBoxStrc* sgpLadderLabelTextBox;
//D2Launch.0x6FA3CD04
D2WinEditBoxStrc* sgpPasswordEditBox;
//D2Launch.0x6FA3CD08
D2WinButtonStrc* sgpGatewayButton;
//D2Launch.0x6FA3CD0C
D2WinButtonStrc* sgpLadderCheckBox;
//D2Launch.0x6FA3CD10
D2WinEditBoxStrc* sgpCharNameEditBox;
//D2Launch.0x6FA3CD14
char gszOldAccountPassword[24];
//D2Launch.0x6FA3CD2C
D2WinEditBoxStrc* sgpConfirmPasswordEditBox;
//D2Launch.0x6FA3CD30
D2WinEditBoxStrc* sgpAccountNameEditBox;
//D2Launch.0x6FA3CD34
D2WinTextBoxStrc* sgpGatewayListTextBox;
//D2Launch.0x6FA3CD38
D2WinTextBoxStrc* sgpHostIpLabelTextBox;
//D2Launch.0x6FA3CD3C
D2WinButtonStrc* sgpTcpIpJoinButton;
//D2Launch.0x6FA3CD40
D2WinTextBoxStrc* sgpCharCreateRealmInfoTextBox;
//D2Launch.0x6FA3CD44
D2ConfigStrc* gptParams;
//D2Launch.0x6FA3CD48
D2WinTextBoxStrc* sgpCharClassNameTextBox;
//D2Launch.0x6FA3CD4C
D2WinTextBoxStrc* sgpCharClassDescriptionTextBox;
//D2Launch.0x6FA3CD50
D2WinTextBoxStrc* sgpTcpIpHostHelpTextBox;
//D2Launch.0x6FA3CD54
D2WinTextBoxStrc* sgpTcpIpJoinHelpTextBox;
//D2Launch.0x6FA3CD58
int32_t gnNextModule;
//D2Launch.0x6FA3CD5C
int32_t gnGameType;
//D2Launch.0x6FA3CD60
BOOL sgbFeCharPalette;
//D2Launch.0x6FA3CD68
char sgszLastTcpIp[256];
//D2Launch.0x6FA3CE68
BOOL gbBnetConnectionCancelled;

//D2Launch.0x6FA3CE6C
D2CellFileStrc* sgpBliznoCellFile;
//D2Launch.0x6FA3CE70
D2CellFileStrc* sgpTrademarkCellFile;
//D2Launch.0x6FA3CE74
D2CellFileStrc* sgpUnusedCellFile;
//D2Launch.0x6FA3CE78
D2CellFileStrc* sgpDiablo2LogoCellFile;
//D2Launch.0x6FA3CE7C
D2CellFileStrc* sgpD2LogoBlackLeftCellFile;
//D2Launch.0x6FA3CE80
D2CellFileStrc* sgpD2LogoFireLeftCellFile;
//D2Launch.0x6FA3CE84
D2CellFileStrc* sgpD2LogoBlackRightCellFile;
//D2Launch.0x6FA3CE88
D2CellFileStrc* sgpD2LogoFireRightCellFile;
//D2Launch.0x6FA3CE8C
D2CellFileStrc* sgpTitleScreenCellFile;
//D2Launch.0x6FA3CE90
D2CellFileStrc* sgpCursorCellFile;
//D2Launch.0x6FA3CE94
D2CellFileStrc* sgpCreditsBackgroundCellFile;
//D2Launch.0x6FA3CE98
D2CellFileStrc* sgpCharacterCreateCellFile;
//D2Launch.0x6FA3CE9C
D2CellFileStrc* sgpFireCellFile;
//D2Launch.0x6FA3CEA0
D2CellFileStrc* sgpRealmSelectButtonCellFile;
//D2Launch.0x6FA3CEA4
D2CellFileStrc* sgpTallButtonBlankCellFile;
//D2Launch.0x6FA3CEA8
D2CellFileStrc* sgpCharacterSelectScreenExpCellFile;
//D2Launch.0x6FA3CEAC
D2CellFileStrc* sgpWideButtonBlankCellFile;
//D2Launch.0x6FA3CEB0
D2CellFileStrc* sgpMediumButtonBlankCellFile;
//D2Launch.0x6FA3CEB4
D2CellFileStrc* sgpShortButtonBlankCellFile;
//D2Launch.0x6FA3CEB8
D2CellFileStrc* sgpMediumSelButtonBlankCellFile;
//D2Launch.0x6FA3CEBC
D2CellFileStrc* sgpTextBox2CellFile;
//D2Launch.0x6FA3CEC0
D2CellFileStrc* sgp3WideButtonBlankCellFile;
//D2Launch.0x6FA3CEC4
D2CellFileStrc* sgpEditTextBoxWideCellFile;
//D2Launch.0x6FA3CEC8
D2CellFileStrc* sgpWideButtonBlank02CellFile;
//D2Launch.0x6FA3CECC
D2CellFileStrc* sgpNarrowButtonBlankCellFile;
//D2Launch.0x6FA3CED0
D2CellFileStrc* sgpGWListBoxCellFile;
//D2Launch.0x6FA3CED8
D2CellFileStrc* sgpTermsOfUseBackgroundCellFile;
//D2Launch.0x6FA3CEDC
D2CellFileStrc* gpCharSelectBackgroundCellFile;
//D2Launch.0x6FA3CEE0
D2CellFileStrc* sgpDifficultyLevelsCellFile;
//D2Launch.0x6FA3CEE4
D2CellFileStrc* sgpCinematicsSelectionCellFile;
//D2Launch.0x6FA3CEE8
D2CellFileStrc* sgpCinematicsSelectionExpCellFile;
//D2Launch.0x6FA3CEEC
D2CellFileStrc* sgpCharSelectBoxCellFile;
//D2Launch.0x6FA3CEF0
D2CellFileStrc* sgpCharSelectBoxGreyCellFile;
//D2Launch.0x6FA3CEF4
D2CellFileStrc* sgpPopUpOkCancelCellFile;
//D2Launch.0x6FA3CEF8
D2CellFileStrc* sgpPopUpOkCancel2CellFile;
//D2Launch.0x6FA3CEFC
D2CellFileStrc* sgpSelectCharArrowsCellFile;
//D2Launch.0x6FA3CF00
D2CellFileStrc* sgpRealmSelectCellFile;
//D2Launch.0x6FA3CF04
D2CellFileStrc* sgpRealmSelectButtonThinCellFile;
//D2Launch.0x6FA3CF08
D2CellFileStrc* sgpCreateNewCharImageCellFile;
//D2Launch.0x6FA3CF0C
D2CellFileStrc* sgpPopUpOkCellFile;
//D2Launch.0x6FA3CF10
D2CellFileStrc* sgpPopUp340x224CellFile;
//D2Launch.0x6FA3CF14
D2CellFileStrc* sgpPopUpWideCellFile;
//D2Launch.0x6FA3CF18
D2CellFileStrc* sgpPopUpLargestCellFile;
//D2Launch.0x6FA3CF1C
D2CellFileStrc* sgpTileableDialogCellFile;
//D2Launch.0x6FA3CF20
D2CellFileStrc* sgpPopUpOk2CellFile;
//D2Launch.0x6FA3CF24
D2CellFileStrc* sgpOkCancelButtonBlankCellFile;
//D2Launch.0x6FA3CF28
D2CellFileStrc* sgpCancelButtonBlankCellFile;
//D2Launch.0x6FA3CF2C
D2CellFileStrc* sgpPasswordCellFile;
//D2Launch.0x6FA3CF30
D2CellFileStrc* sgpCharCreateTextBoxCellFile;
//D2Launch.0x6FA3CF34
D2CellFileStrc* sgpClickBoxCellFile;
//D2Launch.0x6FA3CF38
D2CellFileStrc* sgpJoinGameClickBoxGreyCellFile;
//D2Launch.0x6FA3CF3C
D2CellFileStrc* sgpRealmBackgroundCellFile;
//D2Launch.0x6FA3CF40
D2CellFileStrc* sgpJoinGameScrollBarsCellFile;
//D2Launch.0x6FA3CF44
D2CellFileStrc* sgpTcpIpBackgroundCellFile;
//D2Launch.0x6FA3CF48
D2CellFileStrc* sgpIpAddressBoxCellFile;
//D2Launch.0x6FA3CF4C
D2CellFileStrc* sgpDownloadPatchBackgroundCellFile;
//D2Launch.0x6FA3CF50
D2CellFileStrc* sgpDownloadPatchBallCellFile;
//D2Launch.0x6FA3CF54
D2CellFileStrc* sgpAssassinAnimCellFiles[5];
//D2Launch.0x6FA3CF68
D2CellFileStrc* sgpDruidAnimCellFiles[5];
//D2Launch.0x6FA3CF7C
D2CellFileStrc* sgpAmazonAnimCellFiles[5];
//D2Launch.0x6FA3CF90
D2CellFileStrc* sgpNecromancerAnimCellFiles[5];
//D2Launch.0x6FA3CFA4
D2CellFileStrc* sgpBarbarianAnimCellFiles[5];
//D2Launch.0x6FA3CFB8
D2CellFileStrc* sgpSorceressAnimCellFiles[5];
//D2Launch.0x6FA3CFCC
D2CellFileStrc* sgpPaladinAnimCellFiles[5];
//D2Launch.0x6FA3CFFC
D2CellFileStrc* sgpNecromancerOverlayCellFiles[3];
//D2Launch.0x6FA3D010
D2CellFileStrc* sgpSorceressOverlayCellFiles[3];
//D2Launch.0x6FA3D024
D2CellFileStrc* sgpBarbarianOverlayCellFile;
//D2Launch.0x6FA3D038
D2CellFileStrc* sgpPaladinOverlayCellFile;

//D2Launch.0x6FA3D044
BOOL sgbDiscPromptCancelled;
//D2Launch.0x6FA3D048
BOOL sgbDiscPromptRetry;
//D2Launch.0x6FA3D04C
decltype(&ARCHIVE_LoadVideoArchives) sgpfLoadVideoArchives;
//D2Launch.0x6FA3D050
decltype(&ARCHIVE_LoadExpansionArchives) sgpfLoadExpansionArchives;
//D2Launch.0x6FA3D054
BOOL sgbDiscPromptForVideo;
//D2Launch.0x6FA3D0B8
int32_t sgnNumChildren;
//D2Launch.0x6FA3D0BC
int32_t sgnNumSubChildren;
//D2Launch.0x6FA3D0C0
D2WinControlStrc* sgpAnimatedLogoLeft;
//D2Launch.0x6FA3D0C4
D2WinControlStrc* sgpAnimatedLogoRight;
//D2Launch.0x6FA3D0C8
BOOL sgbPopupActive;
//D2Launch.0x6FA3D0CC
D2WinEditBoxStrc* sgpTcpIpAddressEditBox;
//D2Launch.0x6FA3D0D0
D2WinTextBoxStrc* sgpCreditsLeftTextBox;
//D2Launch.0x6FA3D0D4
D2WinTextBoxStrc* sgpCreditsRightTextBox;
//D2Launch.0x6FA3D0D8
D2WinTextBoxStrc* sgpCreditsCenterTextBox;
//D2Launch.0x6FA3D0DC
D2WinTimerStrc* sgpCreditsTimer;
//D2Launch.0x6FA3D0E0
int32_t sgnCreditsLineCount;
//D2Launch.0x6FA3D0E4
BOOL sgbPaletteChanged;
//D2Launch.0x6FA3D0E8
BOOL sgbWaitPopupCancelled;
//D2Launch.0x6FA3D0EC
D2WinTextBoxStrc* sgpPatchProgressTextBox;
//D2Launch.0x6FA3D0F0
D2WinImageStrc* sgpPatchProgressImage;
//D2Launch.0x6FA3D0F4
BOOL sgbShowLogonFailedHint;
//D2Launch.0x6FA3D0F8
BOOL sgbCreatedExpansionCharacter;
//D2Launch.0x6FA3D0FC
D2ShardStrc** sgptShardArray;
//D2Launch.0x6FA3D100
int32_t sgnShardListSize;
//D2Launch.0x6FA3D104
DWORD sgdwLastClickTickCount;
//D2Launch.0x6FA3D108
int32_t sgnLastClickX;
//D2Launch.0x6FA3D10C
int32_t sgnLastClickY;
//D2Launch.0x6FA3D110
BOOL sgbTcpIpJoinAccepted;
//D2Launch.0x6FA3D114
BOOL sgbRealmLogonCancelled;

//D2Launch.0x6FA37510
int32_t sgnHoveredClass = -1;
//D2Launch.0x6FA37514
int32_t sgnSelectedClass = -1;

//D2Launch.0x6FA33340
D2MenuFontStrc gaMenuFonts[9] =
{
	{ D2FONT_FONT42, 0 },
	{ D2FONT_FONT30, 0 },
	{ D2FONT_FONT24, 0 },
	{ D2FONT_FONT16, 0 },
	{ D2FONT_FONT8, 4 },
	{ D2FONT_FONTFORMAL10, 1 },
	{ D2FONT_FONTFORMAL12, 0 },
	{ D2FONT_FONTFORMAL10, 0 },
	{ D2FONT_FONTFORMAL11, 0 },
};

//D2Launch.0x6FA33388
D2AnimatedImageDescriptor gaAssassinAnimDescriptors[5] =
{
	{ &sgpAssassinAnimCellFiles[0], nullptr, DRAWMODE_NORMAL, 3 },
	{ &sgpAssassinAnimCellFiles[1], nullptr, DRAWMODE_NORMAL, 3 },
	{ &sgpAssassinAnimCellFiles[2], nullptr, DRAWMODE_NORMAL, 1 },
	{ &sgpAssassinAnimCellFiles[3], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpAssassinAnimCellFiles[4], nullptr, DRAWMODE_NORMAL, 1 },
};

//D2Launch.0x6FA333D8
D2AnimatedImageDescriptor gaDruidAnimDescriptors[5] =
{
	{ &sgpDruidAnimCellFiles[0], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpDruidAnimCellFiles[1], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpDruidAnimCellFiles[2], nullptr, DRAWMODE_NORMAL, 1 },
	{ &sgpDruidAnimCellFiles[3], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpDruidAnimCellFiles[4], nullptr, DRAWMODE_NORMAL, 1 },
};

//D2Launch.0x6FA33428
D2AnimatedImageDescriptor gaAmazonAnimDescriptors[5] =
{
	{ &sgpAmazonAnimCellFiles[0], nullptr, DRAWMODE_NORMAL, 3 },
	{ &sgpAmazonAnimCellFiles[1], nullptr, DRAWMODE_NORMAL, 3 },
	{ &sgpAmazonAnimCellFiles[2], nullptr, DRAWMODE_NORMAL, 1 },
	{ &sgpAmazonAnimCellFiles[3], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpAmazonAnimCellFiles[4], nullptr, DRAWMODE_NORMAL, 1 },
};

//D2Launch.0x6FA33478
D2AnimatedImageDescriptor gaNecromancerAnimDescriptors[5] =
{
	{ &sgpNecromancerAnimCellFiles[0], nullptr, DRAWMODE_NORMAL, 3 },
	{ &sgpNecromancerAnimCellFiles[1], nullptr, DRAWMODE_NORMAL, 3 },
	{ &sgpNecromancerAnimCellFiles[2], &sgpNecromancerOverlayCellFiles[0], DRAWMODE_MODULATE, 1 },
	{ &sgpNecromancerAnimCellFiles[3], &sgpNecromancerOverlayCellFiles[1], DRAWMODE_MODULATE, 2 },
	{ &sgpNecromancerAnimCellFiles[4], &sgpNecromancerOverlayCellFiles[2], DRAWMODE_MODULATE, 1 },
};

//D2Launch.0x6FA334C8
D2AnimatedImageDescriptor gaBarbarianAnimDescriptors[5] =
{
	{ &sgpBarbarianAnimCellFiles[0], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpBarbarianAnimCellFiles[1], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpBarbarianAnimCellFiles[2], &sgpBarbarianOverlayCellFile, DRAWMODE_NORMAL, 1 },
	{ &sgpBarbarianAnimCellFiles[3], nullptr, DRAWMODE_NORMAL, 1 },
	{ &sgpBarbarianAnimCellFiles[4], nullptr, DRAWMODE_NORMAL, 1 },
};

//D2Launch.0x6FA33518
D2AnimatedImageDescriptor gaSorceressAnimDescriptors[5] =
{
	{ &sgpSorceressAnimCellFiles[0], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpSorceressAnimCellFiles[1], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpSorceressAnimCellFiles[2], &sgpSorceressOverlayCellFiles[0], DRAWMODE_MODULATE, 1 },
	{ &sgpSorceressAnimCellFiles[3], &sgpSorceressOverlayCellFiles[1], DRAWMODE_MODULATE, 1 },
	{ &sgpSorceressAnimCellFiles[4], &sgpSorceressOverlayCellFiles[2], DRAWMODE_MODULATE, 1 },
};

//D2Launch.0x6FA33568
D2AnimatedImageDescriptor gaPaladinAnimDescriptors[5] =
{
	{ &sgpPaladinAnimCellFiles[0], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpPaladinAnimCellFiles[1], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpPaladinAnimCellFiles[2], &sgpPaladinOverlayCellFile, DRAWMODE_NORMAL, 1 },
	{ &sgpPaladinAnimCellFiles[3], nullptr, DRAWMODE_NORMAL, 2 },
	{ &sgpPaladinAnimCellFiles[4], nullptr, DRAWMODE_NORMAL, 1 },
};

//D2Launch.0x6FA335B8
D2AnimatedImageDescriptor gaLogoLeftAnimDescriptors[5] =
{
	{ &sgpD2LogoBlackLeftCellFile, &sgpD2LogoFireLeftCellFile, DRAWMODE_MODULATE, 1 },
	{ &sgpD2LogoBlackLeftCellFile, &sgpD2LogoFireLeftCellFile, DRAWMODE_MODULATE, 1 },
	{ &sgpD2LogoBlackLeftCellFile, &sgpD2LogoFireLeftCellFile, DRAWMODE_MODULATE, 1 },
	{ &sgpD2LogoBlackLeftCellFile, &sgpD2LogoFireLeftCellFile, DRAWMODE_MODULATE, 1 },
	{ &sgpD2LogoBlackLeftCellFile, &sgpD2LogoFireLeftCellFile, DRAWMODE_MODULATE, 1 },
};

//D2Launch.0x6FA33608
D2AnimatedImageDescriptor gaLogoRightAnimDescriptors[5] =
{
	{ &sgpD2LogoBlackRightCellFile, &sgpD2LogoFireRightCellFile, DRAWMODE_MODULATE, 1 },
	{ &sgpD2LogoBlackRightCellFile, &sgpD2LogoFireRightCellFile, DRAWMODE_MODULATE, 1 },
	{ &sgpD2LogoBlackRightCellFile, &sgpD2LogoFireRightCellFile, DRAWMODE_MODULATE, 1 },
	{ &sgpD2LogoBlackRightCellFile, &sgpD2LogoFireRightCellFile, DRAWMODE_MODULATE, 1 },
	{ &sgpD2LogoBlackRightCellFile, &sgpD2LogoFireRightCellFile, DRAWMODE_MODULATE, 1 },
};

//D2Launch.0x6FA33658
int32_t gaScrollBarInfos[6][3] =
{
	{ 48, 501, 319 },
	{ 51, 456, 270 },
	{ 681, 467, 323 },
	{ 549, 491, 154 },
	{ 439, 391, 154 },
	{ 585, 457, 363 },
};

//D2Launch.0x6FA336A0
D2WinControlInitStrc gaControlInits[333] =
{
	{ D2WIN_IMAGE, 0, 479, 640, 480, 0, 0, &sgpBliznoCellFile, MENU_SkipLogoCallback, nullptr, nullptr, 0 }, // 0
	{ D2WIN_TIMER, 8, 0, 0, 0, 0, 0, nullptr, MENU_SkipLogoCallback, nullptr, nullptr, 0 }, // 1
	{ D2WIN_IMAGE, 0, 599, 800, 600, 0, 0, &sgpTrademarkCellFile, MENU_BackToMainMenuCallback, nullptr, (void*)MENU_BackToMainMenuCallback, 0 }, // 2
	{ D2WIN_TIMER, 9, 0, 0, 0, 0, 0, nullptr, MENU_BackToMainMenuCallback, nullptr, nullptr, 0 }, // 3
	{ D2WIN_TEXTBOX, 100, 580, 600, 80, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[6], 2 }, // 4
	{ D2WIN_IMAGE, 240, 120, 320, 151, 0, 0, &sgpDiablo2LogoCellFile, nullptr, nullptr, nullptr, 0 }, // 5
	{ D2WIN_ANIMIMAGE, 400, 120, 181, 170, 0, 0, nullptr, nullptr, &gaLogoLeftAnimDescriptors[0], nullptr, 0 }, // 6
	{ D2WIN_ANIMIMAGE, 400, 120, 188, 177, 0, 0, nullptr, nullptr, &gaLogoRightAnimDescriptors[0], nullptr, 0 }, // 7
	{ D2WIN_IMAGE, 0, 599, 800, 600, 0, 0, &sgpTitleScreenCellFile, nullptr, nullptr, nullptr, 0 }, // 8
	{ D2WIN_BUTTON, 264, 224, 272, 35, 0, 5106, &sgpWideButtonBlankCellFile, MENU_SinglePlayerCallback, nullptr, nullptr, 0 }, // 9
	{ D2WIN_BUTTON, 264, 266, 272, 35, 0, 5107, &sgpWideButtonBlank02CellFile, MENU_BattleNetCallback, nullptr, nullptr, 0 }, // 10
	{ D2WIN_BUTTON, 264, 291, 272, 25, 0, 0, &sgpNarrowButtonBlankCellFile, MENU_ShowGatewaySelectionCallback, nullptr, nullptr, 0 }, // 11
	{ D2WIN_BUTTON, 264, 333, 272, 35, 0, 5108, &sgpWideButtonBlankCellFile, MENU_OtherMultiplayerCallback, nullptr, nullptr, 0 }, // 12
	{ D2WIN_BUTTON, 264, 528, 135, 25, 0, 5110, &sgpShortButtonBlankCellFile, MENU_ShowCreditsCallback, nullptr, nullptr, 0 }, // 13
	{ D2WIN_BUTTON, 402, 528, 135, 25, 0, 5111, &sgpShortButtonBlankCellFile, MENU_ShowCinematicsCallback, nullptr, nullptr, 0 }, // 14
	{ D2WIN_BUTTON, 264, 568, 272, 35, VK_ESCAPE, 5109, &sgpWideButtonBlankCellFile, MENU_ExitGameCallback, nullptr, nullptr, 0 }, // 15
	{ D2WIN_BUTTON, 264, 324, 272, 35, 0, 5106, &sgpWideButtonBlankCellFile, MENU_SinglePlayerCallback, nullptr, nullptr, 0 }, // 16
	{ D2WIN_BUTTON, 264, 366, 272, 35, 0, 5107, &sgpWideButtonBlank02CellFile, MENU_BattleNetCallback, nullptr, nullptr, 0 }, // 17
	{ D2WIN_BUTTON, 264, 391, 272, 25, 0, 0, &sgpNarrowButtonBlankCellFile, MENU_ShowGatewaySelectionCallback, nullptr, nullptr, 0 }, // 18
	{ D2WIN_BUTTON, 264, 433, 272, 35, 0, 5108, &sgpWideButtonBlankCellFile, MENU_OtherMultiplayerCallback, nullptr, nullptr, 0 }, // 19
	{ D2WIN_TEXTBOX, 150, 300, 500, 100, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[0], 34 }, // 20
	{ D2WIN_IMAGE, 319, 347, 169, 26, 0, 0, &sgpTextBox2CellFile, nullptr, nullptr, nullptr, 0 }, // 21
	{ D2WIN_IMAGE, 319, 401, 169, 26, 0, 0, &sgpTextBox2CellFile, nullptr, nullptr, nullptr, 0 }, // 22
	{ D2WIN_IMAGE, 319, 455, 169, 26, 0, 0, &sgpTextBox2CellFile, nullptr, nullptr, nullptr, 0 }, // 23
	{ D2WIN_IMAGE, 319, 455, 169, 26, 0, 0, &sgpTextBox2CellFile, nullptr, nullptr, nullptr, 0 }, // 24
	{ D2WIN_IMAGE, 319, 509, 169, 26, 0, 0, &sgpTextBox2CellFile, nullptr, nullptr, nullptr, 0 }, // 25
	{ D2WIN_TEXTBOX, 321, 340, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 26
	{ D2WIN_TEXTBOX, 321, 394, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 27
	{ D2WIN_TEXTBOX, 321, 448, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 28
	{ D2WIN_TEXTBOX, 321, 448, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 29
	{ D2WIN_TEXTBOX, 321, 502, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 30
	{ D2WIN_TEXTBOX, 0, 260, 800, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 31
	{ D2WIN_TEXTBOX, 200, 350, 400, 100, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 32
	{ D2WIN_TEXTBOX, 0, 310, 800, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 33
	{ D2WIN_EDITBOX, 322, 342, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_LoginOkCallback, &gaMenuFonts[6], 0 }, // 34
	{ D2WIN_EDITBOX, 322, 396, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_LoginOkCallback, &gaMenuFonts[6], 33 }, // 35
	{ D2WIN_BUTTON, 264, 572, 272, 35, 0, 5221, &sgpWideButtonBlankCellFile, MENU_CreateNewAccountCallback, nullptr, nullptr, 0 }, // 36
	{ D2WIN_BUTTON, 264, 528, 272, 35, 0, 11108, &sgpWideButtonBlankCellFile, MENU_AccountOptionsCallback, nullptr, nullptr, 0 }, // 37
	{ D2WIN_BUTTON, 264, 484, 272, 35, VK_RETURN, 5288, &sgp3WideButtonBlankCellFile, MENU_LoginOkCallback, nullptr, nullptr, 32 }, // 38
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5101, &sgpMediumButtonBlankCellFile, MENU_BackToMainMenuCallback, nullptr, nullptr, 0 }, // 39
	{ D2WIN_TEXTBOX, 590, 545, 205, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 40
	{ D2WIN_IMAGE, 0, 599, 800, 600, 0, 0, &sgpCreditsBackgroundCellFile, nullptr, nullptr, nullptr, 0 }, // 41
	{ D2WIN_BUTTON, 33, 578, 128, 35, VK_ESCAPE, 5101, &sgpMediumButtonBlankCellFile, MENU_BackToMainMenuCallback, nullptr, nullptr, 0 }, // 42
	{ D2WIN_TEXTBOX, 560, 615, 250, 610, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[5], 144 }, // 43
	{ D2WIN_TEXTBOX, 570, 615, 250, 610, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[5], 128 }, // 44
	{ D2WIN_TEXTBOX, 440, 615, 250, 610, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[5], 130 }, // 45
	{ D2WIN_TIMER, 50, 0, 0, 0, 0, 0, nullptr, MENU_CreditsTimerCallback, nullptr, nullptr, 0 }, // 46
	{ D2WIN_TEXTBOX, 400, 615, 250, 610, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[5], 144 }, // 47
	{ D2WIN_TEXTBOX, 410, 615, 250, 610, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[5], 128 }, // 48
	{ D2WIN_TEXTBOX, 280, 615, 250, 610, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[5], 130 }, // 49
	{ D2WIN_IMAGE, 237, 555, 326, 341, 0, 0, &sgpCinematicsSelectionCellFile, nullptr, nullptr, nullptr, 0 }, // 50
	{ D2WIN_TEXTBOX, 262, 283, 272, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 51
	{ D2WIN_BUTTON, 262, 316, 272, 35, 0, 4137, &sgpWideButtonBlankCellFile, MENU_PlayIntroCinematicCallback, nullptr, nullptr, 0 }, // 52
	{ D2WIN_BUTTON, 262, 359, 272, 35, 0, 4138, &sgpWideButtonBlankCellFile, MENU_PlayAct2CinematicCallback, nullptr, nullptr, 0 }, // 53
	{ D2WIN_BUTTON, 262, 402, 272, 35, 0, 4139, &sgpWideButtonBlankCellFile, MENU_PlayAct3CinematicCallback, nullptr, nullptr, 0 }, // 54
	{ D2WIN_BUTTON, 262, 445, 272, 35, 0, 4140, &sgpWideButtonBlankCellFile, MENU_PlayAct4CinematicCallback, nullptr, nullptr, 0 }, // 55
	{ D2WIN_BUTTON, 262, 488, 272, 35, 0, 5113, &sgpWideButtonBlankCellFile, MENU_PlayAct4EndCinematicCallback, nullptr, nullptr, 0 }, // 56
	{ D2WIN_BUTTON, 334, 538, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, MENU_CinematicsCancelCallback, nullptr, nullptr, 0 }, // 57
	{ D2WIN_BUTTON, 281, 337, 96, 32, VK_ESCAPE, 5103, &sgpCancelButtonBlankCellFile, MENU_InsertVideoDiscCancelCallback, nullptr, nullptr, 2 }, // 58
	{ D2WIN_BUTTON, 421, 337, 96, 32, VK_RETURN, 5102, &sgpCancelButtonBlankCellFile, MENU_InsertVideoDiscRetryCallback, nullptr, nullptr, 2 }, // 59
	{ D2WIN_BUTTON, 351, 337, 96, 32, VK_RETURN, 5102, &sgpCancelButtonBlankCellFile, MENU_InsertPlayDiscRetryCallback, nullptr, nullptr, 2 }, // 60
	{ D2WIN_IMAGE, 237, 505, 326, 427, 0, 0, &sgpCinematicsSelectionExpCellFile, nullptr, nullptr, nullptr, 0 }, // 61
	{ D2WIN_TEXTBOX, 262, 153, 272, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 62
	{ D2WIN_BUTTON, 262, 181, 272, 35, 0, 21797, &sgpWideButtonBlankCellFile, MENU_PlayIntroCinematicCallback, nullptr, nullptr, 0 }, // 63
	{ D2WIN_BUTTON, 262, 224, 272, 35, 0, 21798, &sgpWideButtonBlankCellFile, MENU_PlayAct2CinematicCallback, nullptr, nullptr, 0 }, // 64
	{ D2WIN_BUTTON, 262, 268, 272, 35, 0, 21799, &sgpWideButtonBlankCellFile, MENU_PlayAct3CinematicCallback, nullptr, nullptr, 0 }, // 65
	{ D2WIN_BUTTON, 262, 310, 272, 35, 0, 21800, &sgpWideButtonBlankCellFile, MENU_PlayAct4CinematicCallback, nullptr, nullptr, 0 }, // 66
	{ D2WIN_BUTTON, 262, 353, 272, 35, 0, 21801, &sgpWideButtonBlankCellFile, MENU_PlayAct4EndCinematicCallback, nullptr, nullptr, 0 }, // 67
	{ D2WIN_BUTTON, 262, 396, 272, 35, 0, 21802, &sgpWideButtonBlankCellFile, MENU_PlayExpansionIntroCinematicCallback, nullptr, nullptr, 0 }, // 68
	{ D2WIN_BUTTON, 262, 439, 272, 35, 0, 21803, &sgpWideButtonBlankCellFile, MENU_PlayExpansionOutroCinematicCallback, nullptr, nullptr, 0 }, // 69
	{ D2WIN_BUTTON, 334, 488, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, MENU_CinematicsCancelCallback, nullptr, nullptr, 0 }, // 70
	{ D2WIN_IMAGE, 237, 555, 340, 340, 0, 0, &sgpGWListBoxCellFile, nullptr, nullptr, nullptr, 0 }, // 71
	{ D2WIN_TEXTBOX, 237, 270, 340, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 72
	{ D2WIN_TEXTBOX, 257, 345, 320, 84, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[4], 0 }, // 73
	{ D2WIN_TEXTBOX, 257, 500, 292, 160, 0, 0, &sgpJoinGameScrollBarsCellFile, MENU_GatewayListClickCallback, gaScrollBarInfos[3], &gaMenuFonts[6], 13 }, // 74
	{ D2WIN_BUTTON, 281, 538, 96, 32, VK_RETURN, 5102, &sgpCancelButtonBlankCellFile, MENU_GatewayOkCallback, nullptr, nullptr, 0 }, // 75
	{ D2WIN_BUTTON, 436, 538, 96, 32, VK_ESCAPE, 5103, &sgpCancelButtonBlankCellFile, MENU_GatewayCancelCallback, nullptr, nullptr, 0 }, // 76
	{ D2WIN_IMAGE, 103, 526, 593, 451, 0, 0, &sgpTermsOfUseBackgroundCellFile, nullptr, nullptr, nullptr, 0 }, // 77
	{ D2WIN_TEXTBOX, 120, 467, 560, 318, 0, 0, &sgpJoinGameScrollBarsCellFile, nullptr, gaScrollBarInfos[2], &gaMenuFonts[7], 4 }, // 78
	{ D2WIN_BUTTON, 525, 513, 128, 35, 0, 5181, &sgpMediumButtonBlankCellFile, MENU_AcceptTermsOfServiceCallback, nullptr, nullptr, 0 }, // 79
	{ D2WIN_BUTTON, 133, 513, 128, 35, VK_RETURN, 5182, &sgpMediumButtonBlankCellFile, BNET_AccountOptionsBackCallback, nullptr, nullptr, 0 }, // 80
	{ D2WIN_TEXTBOX, 103, 173, 570, 69, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[0], 2 }, // 81
	{ D2WIN_BUTTON, 900, 900, 128, 35, 38, 0, nullptr, MENU_TermsOfServicePageUpCallback, nullptr, nullptr, 6 }, // 82
	{ D2WIN_BUTTON, 900, 900, 128, 35, 40, 0, nullptr, MENU_TermsOfServicePageDownCallback, nullptr, nullptr, 6 }, // 83
	{ D2WIN_EDITBOX, 322, 342, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_CreateAccountOkCallback, &gaMenuFonts[6], 0 }, // 84
	{ D2WIN_EDITBOX, 322, 396, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_CreateAccountOkCallback, &gaMenuFonts[6], 33 }, // 85
	{ D2WIN_EDITBOX, 322, 450, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_CreateAccountOkCallback, &gaMenuFonts[6], 33 }, // 86
	{ D2WIN_BUTTON, 627, 572, 128, 35, VK_RETURN, 5102, &sgpMediumButtonBlankCellFile, MENU_CreateAccountOkCallback, nullptr, nullptr, 0 }, // 87
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5101, &sgpMediumButtonBlankCellFile, BNET_AccountOptionsBackCallback, nullptr, nullptr, 0 }, // 88
	{ D2WIN_EDITBOX, 322, 342, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_ChangePasswordOkCallback, &gaMenuFonts[6], 0 }, // 89
	{ D2WIN_EDITBOX, 322, 396, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_ChangePasswordOkCallback, &gaMenuFonts[6], 33 }, // 90
	{ D2WIN_EDITBOX, 322, 450, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_ChangePasswordOkCallback, &gaMenuFonts[6], 33 }, // 91
	{ D2WIN_EDITBOX, 322, 504, 162, 19, 8, 4, nullptr, nullptr, (void*)MENU_ChangePasswordOkCallback, &gaMenuFonts[6], 33 }, // 92
	{ D2WIN_BUTTON, 627, 572, 128, 35, VK_RETURN, 5102, &sgpMediumButtonBlankCellFile, MENU_ChangePasswordOkCallback, nullptr, nullptr, 0 }, // 93
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5101, &sgpMediumButtonBlankCellFile, BNET_BackToAccountOptionsCallback, nullptr, nullptr, 0 }, // 94
	{ D2WIN_TEXTBOX, 103, 173, 570, 69, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[0], 2 }, // 95
	{ D2WIN_TEXTBOX, 110, 480, 570, 318, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[6], 2 }, // 96
	{ D2WIN_TEXTBOX, 110, 610, 570, 318, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[6], 2 }, // 97
	{ D2WIN_TEXTBOX, 110, 700, 570, 318, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[6], 2 }, // 98
	{ D2WIN_BUTTON, 525, 513, 128, 35, VK_RETURN, 5102, &sgpMediumButtonBlankCellFile, MENU_CreateAccountInfoOkCallback, nullptr, nullptr, 0 }, // 99
	{ D2WIN_BUTTON, 133, 513, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, MENU_CreateAccountInfoCancelCallback, nullptr, nullptr, 0 }, // 100
	{ D2WIN_IMAGE, 513, 80, 272, 73, 0, 0, &sgpRealmSelectCellFile, nullptr, nullptr, nullptr, 0 }, // 101
	{ D2WIN_TEXTBOX, 559, 33, 183, 18, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 102
	{ D2WIN_BUTTON, 513, 105, 272, 25, 0, 11057, &sgpRealmSelectButtonThinCellFile, CHARSEL_ChangeRealmCallback, nullptr, nullptr, 0 }, // 103
	{ D2WIN_TEXTBOX, 528, 96, 246, 47, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[0], 2 }, // 104
	{ D2WIN_IMAGE, 609, 83, 182, 71, 0, 0, &sgpRealmSelectCellFile, nullptr, nullptr, nullptr, 0 }, // 105
	{ D2WIN_TEXTBOX, 629, 44, 145, 21, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 106
	{ D2WIN_BUTTON, 609, 113, 182, 30, 0, 11057, &sgpRealmSelectButtonThinCellFile, CHARSEL_ChangeRealmCallback, nullptr, nullptr, 0 }, // 107
	{ D2WIN_TEXTBOX, 626, 100, 151, 44, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 108
	{ D2WIN_IMAGE, 451, 455, 340, 340, 0, 0, &sgpGWListBoxCellFile, nullptr, nullptr, nullptr, 0 }, // 109
	{ D2WIN_TEXTBOX, 451, 173, 340, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 110
	{ D2WIN_TEXTBOX, 461, 230, 320, 70, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[4], 0 }, // 111
	{ D2WIN_TEXTBOX, 471, 400, 292, 160, 0, 0, &sgpJoinGameScrollBarsCellFile, CHARSEL_RealmListClickCallback, gaScrollBarInfos[4], &gaMenuFonts[6], 13 }, // 112
	{ D2WIN_BUTTON, 495, 438, 96, 32, VK_RETURN, 5102, &sgpCancelButtonBlankCellFile, CHARSEL_RealmSelectOkCallback, nullptr, nullptr, 0 }, // 113
	{ D2WIN_BUTTON, 650, 438, 96, 32, VK_ESCAPE, 5103, &sgpCancelButtonBlankCellFile, CHARSEL_RealmSelectCancelCallback, nullptr, nullptr, 0 }, // 114
	{ D2WIN_IMAGE, 127, 455, 340, 340, 0, 0, &sgpGWListBoxCellFile, nullptr, nullptr, nullptr, 0 }, // 115
	{ D2WIN_TEXTBOX, 127, 173, 340, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 116
	{ D2WIN_TEXTBOX, 137, 230, 320, 70, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[4], 0 }, // 117
	{ D2WIN_TEXTBOX, 147, 400, 292, 160, 0, 0, &sgpJoinGameScrollBarsCellFile, CHARSEL_RealmListClickCallback, gaScrollBarInfos[4], &gaMenuFonts[6], 13 }, // 118
	{ D2WIN_BUTTON, 171, 438, 96, 32, VK_RETURN, 5102, &sgpCancelButtonBlankCellFile, CHARSEL_RealmSelectOkCallback, nullptr, nullptr, 0 }, // 119
	{ D2WIN_BUTTON, 326, 438, 96, 32, VK_ESCAPE, 5103, &sgpCancelButtonBlankCellFile, CHARSEL_RealmSelectCancelCallback, nullptr, nullptr, 0 }, // 120
	{ D2WIN_TEXTBOX, 33, 530, 448, 120, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[7], 0 }, // 121
	{ D2WIN_TIMER, 50, 0, 0, 0, 0, 0, nullptr, CHARSEL_RealmTimerCallback, nullptr, nullptr, 0 }, // 122
	{ D2WIN_BUTTON, 514, 572, 272, 35, 0, 5273, &sgpWideButtonBlankCellFile, MENU_CreateNewCharacterCallback, nullptr, nullptr, 0 }, // 123
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5101, &sgpMediumButtonBlankCellFile, MENU_CharacterSelectionExitCallback, nullptr, nullptr, 0 }, // 124
	{ D2WIN_BUTTON, 193, 572, 128, 35, 0, 5272, &sgpMediumButtonBlankCellFile, CHARSEL_DeleteCharacterCallback, nullptr, nullptr, 0 }, // 125
	{ D2WIN_BUTTON, 353, 572, 128, 35, VK_RETURN, 5102, &sgpMediumButtonBlankCellFile, CHARSEL_OkCallback, nullptr, nullptr, 0 }, // 126
	{ D2WIN_TEXTBOX, 514, 153, 200, 92, 76, 5, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 127
	{ D2WIN_TEXTBOX, 514, 246, 200, 92, 76, 5, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 128
	{ D2WIN_TEXTBOX, 514, 339, 200, 92, 76, 5, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 129
	{ D2WIN_TEXTBOX, 514, 432, 200, 92, 76, 5, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 130
	{ D2WIN_TEXTBOX, 514, 525, 200, 92, 76, 5, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 131
	{ D2WIN_TEXTBOX, 37, 178, 200, 92, 76, 3, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 132
	{ D2WIN_TEXTBOX, 309, 178, 200, 92, 76, 3, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 133
	{ D2WIN_TEXTBOX, 37, 271, 200, 92, 76, 3, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 134
	{ D2WIN_TEXTBOX, 309, 271, 200, 92, 76, 3, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 135
	{ D2WIN_TEXTBOX, 37, 364, 200, 92, 76, 3, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 136
	{ D2WIN_TEXTBOX, 309, 364, 200, 92, 76, 3, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 137
	{ D2WIN_TEXTBOX, 37, 457, 200, 92, 76, 3, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 138
	{ D2WIN_TEXTBOX, 309, 457, 200, 92, 76, 3, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 139
	{ D2WIN_TEXTBOX, 237, 178, 72, 93, 0, 0, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 140
	{ D2WIN_TEXTBOX, 509, 178, 72, 93, 0, 0, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 141
	{ D2WIN_TEXTBOX, 237, 271, 72, 93, 0, 0, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 142
	{ D2WIN_TEXTBOX, 509, 271, 72, 93, 0, 0, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 143
	{ D2WIN_TEXTBOX, 237, 364, 72, 93, 0, 0, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 144
	{ D2WIN_TEXTBOX, 509, 364, 72, 93, 0, 0, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 145
	{ D2WIN_TEXTBOX, 237, 457, 72, 93, 0, 0, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 146
	{ D2WIN_TEXTBOX, 509, 457, 72, 93, 0, 0, nullptr, CHARSEL_CharacterSlotClickCallback, nullptr, &gaMenuFonts[3], 32 }, // 147
	{ D2WIN_TEXTBOX, 37, 178, 547, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 148
	{ D2WIN_TEXTBOX, 37, 178, 547, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[7], 2 }, // 149
	{ D2WIN_IMAGE, 514, 1000, 272, 93, 0, 0, &sgpCharSelectBoxCellFile, nullptr, nullptr, (void*)CHARSEL_KeyDownCallback, 0 }, // 150
	{ D2WIN_IMAGE, 514, 1000, 272, 93, 0, 0, &sgpCharSelectBoxGreyCellFile, nullptr, nullptr, (void*)CHARSEL_KeyDownCallback, 0 }, // 151
	{ D2WIN_TEXTBOX, 514, 385, 272, 93, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 152
	{ D2WIN_BUTTON, 634, 50, 29, 20, 105, 0, &sgpSelectCharArrowsCellFile, CHARSEL_ScrollUpCallback, nullptr, nullptr, 8 }, // 153
	{ D2WIN_BUTTON, 634, 555, 29, 20, 99, 0, &sgpSelectCharArrowsCellFile, CHARSEL_ScrollDownCallback, (void*)2, nullptr, 16 }, // 154
	{ D2WIN_TEXTBOX, 70, 103, 450, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[0], 34 }, // 155
	{ D2WIN_TEXTBOX, 85, 78, 466, 42, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[0], 34 }, // 156
	{ D2WIN_TEXTBOX, 86, 143, 400, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 157
	{ D2WIN_TEXTBOX, 86, 178, 400, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 158
	{ D2WIN_IMAGE, 512, 150, 84, 86, 0, 0, &sgpCreateNewCharImageCellFile, nullptr, nullptr, (void*)CHARSEL_KeyDownCallback, 0 }, // 159
	{ D2WIN_TEXTBOX, 86, 300, 400, 200, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[8], 2 }, // 160
	{ D2WIN_IMAGE, 0, 599, 800, 600, 0, 0, &sgpCharacterSelectScreenExpCellFile, nullptr, nullptr, nullptr, 0 }, // 161
	{ D2WIN_BUTTON, 627, 572, 128, 35, VK_RETURN, 5102, &sgpMediumButtonBlankCellFile, CHARSEL_OkCallback, nullptr, nullptr, 0 }, // 162
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5101, &sgpMediumButtonBlankCellFile, MENU_CharacterSelectionExitCallback, nullptr, nullptr, 0 }, // 163
	{ D2WIN_BUTTON, 33, 528, 168, 60, 0, 10832, &sgpTallButtonBlankCellFile, MENU_CreateNewCharacterCallback, nullptr, nullptr, 64 }, // 164
	{ D2WIN_BUTTON, 233, 528, 168, 60, 0, 22732, &sgpTallButtonBlankCellFile, CHARSEL_ConvertToExpansionCallback, nullptr, nullptr, 64 }, // 165
	{ D2WIN_BUTTON, 433, 528, 168, 60, 0, 5272, &sgpTallButtonBlankCellFile, CHARSEL_DeleteCharacterCallback, nullptr, nullptr, 64 }, // 166
	{ D2WIN_TEXTBOX, 564, 457, 34, 371, 0, 0, &sgpJoinGameScrollBarsCellFile, CHARSEL_ScrollBarCallback, gaScrollBarInfos[5], &gaMenuFonts[6], 5 }, // 167
	{ D2WIN_BUTTON, 264, 297, 272, 35, 0, 10018, &sgpWideButtonBlankCellFile, CHARSEL_NormalDifficultyCallback, nullptr, nullptr, 0 }, // 168
	{ D2WIN_BUTTON, 264, 340, 272, 35, 0, 10017, &sgpWideButtonBlankCellFile, CHARSEL_NightmareDifficultyCallback, nullptr, nullptr, 0 }, // 169
	{ D2WIN_BUTTON, 264, 383, 272, 35, 0, 10016, &sgpWideButtonBlankCellFile, CHARSEL_HellDifficultyCallback, nullptr, nullptr, 0 }, // 170
	{ D2WIN_TEXTBOX, 264, 260, 272, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 171
	{ D2WIN_IMAGE, 237, 400, 326, 200, 0, 0, &sgpDifficultyLevelsCellFile, nullptr, nullptr, nullptr, 0 }, // 172
	{ D2WIN_BUTTON, 900, 900, 10, 10, VK_ESCAPE, 0, nullptr, MENU_CloseSubChildrenCallback, nullptr, nullptr, 0 }, // 173
	{ D2WIN_TEXTBOX, 0, 80, 800, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 174
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5101, &sgpMediumSelButtonBlankCellFile, MENU_CharacterCreationExitCallback, nullptr, nullptr, 0 }, // 175
	{ D2WIN_BUTTON, 627, 572, 128, 35, VK_RETURN, 5102, &sgpMediumSelButtonBlankCellFile, MENU_CreateCharacterOkCallback, nullptr, nullptr, 0 }, // 176
	{ D2WIN_IMAGE, 0, 599, 800, 600, 0, 0, &sgpCharacterCreateCellFile, nullptr, nullptr, nullptr, 0 }, // 177
	{ D2WIN_ANIMIMAGE, 345, 470, 110, 127, 1, 3, &sgpFireCellFile, nullptr, nullptr, nullptr, 0 }, // 178
	{ D2WIN_ANIMIMAGE, 345, 454, 110, 127, 1, 3, &sgpFireCellFile, nullptr, nullptr, nullptr, 0 }, // 179
	{ D2WIN_ANIMIMAGE, 195, 341, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaAmazonAnimDescriptors[0], (void*)MENU_AmazonHoverCallback, 0 }, // 180
	{ D2WIN_ANIMIMAGE, 301, 333, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaNecromancerAnimDescriptors[0], (void*)MENU_NecromancerHoverCallback, 0 }, // 181
	{ D2WIN_ANIMIMAGE, 400, 330, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaBarbarianAnimDescriptors[0], (void*)MENU_BarbarianHoverCallback, 0 }, // 182
	{ D2WIN_ANIMIMAGE, 521, 344, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaSorceressAnimDescriptors[0], (void*)MENU_SorceressHoverCallback, 0 }, // 183
	{ D2WIN_ANIMIMAGE, 610, 359, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaPaladinAnimDescriptors[0], (void*)MENU_PaladinHoverCallback, 0 }, // 184
	{ D2WIN_ANIMIMAGE, 217, 360, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaNecromancerAnimDescriptors[0], (void*)MENU_NecromancerHoverCallback, 0 }, // 185
	{ D2WIN_ANIMIMAGE, 626, 353, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaSorceressAnimDescriptors[0], (void*)MENU_SorceressHoverCallback, 0 }, // 186
	{ D2WIN_ANIMIMAGE, 521, 339, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaPaladinAnimDescriptors[0], (void*)MENU_PaladinHoverCallback, 0 }, // 187
	{ D2WIN_ANIMIMAGE, 100, 337, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaAmazonAnimDescriptors[0], (void*)MENU_AmazonHoverCallback, 0 }, // 188
	{ D2WIN_TEXTBOX, 339, 581, 100, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 189
	{ D2WIN_BUTTON, 319, 560, 15, 16, 0, 0, &sgpClickBoxCellFile, MENU_HardcoreCheckBoxCallback, nullptr, nullptr, 2 }, // 190
	{ D2WIN_TEXTBOX, 339, 561, 200, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 191
	{ D2WIN_BUTTON, 319, 540, 15, 16, 0, 0, &sgpClickBoxCellFile, MENU_LadderCheckBoxCallback, nullptr, nullptr, 2 }, // 192
	{ D2WIN_TEXTBOX, 339, 581, 200, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 193
	{ D2WIN_BUTTON, 319, 560, 15, 16, 0, 0, &sgpClickBoxCellFile, MENU_LadderCheckBoxCallback, nullptr, nullptr, 2 }, // 194
	{ D2WIN_TEXTBOX, 339, 601, 200, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 195
	{ D2WIN_BUTTON, 319, 580, 15, 16, 0, 0, &sgpClickBoxCellFile, MENU_LadderCheckBoxCallback, nullptr, nullptr, 2 }, // 196
	{ D2WIN_TEXTBOX, 0, 180, 800, 100, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 197
	{ D2WIN_TEXTBOX, 250, 210, 300, 100, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 198
	{ D2WIN_TEXTBOX, 210, 610, 430, 120, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[4], 0 }, // 199
	{ D2WIN_IMAGE, 319, 519, 169, 26, 0, 0, &sgpCharCreateTextBoxCellFile, nullptr, nullptr, nullptr, 0 }, // 200
	{ D2WIN_TEXTBOX, 321, 512, 200, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 201
	{ D2WIN_TEXTBOX, 339, 561, 100, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 202
	{ D2WIN_BUTTON, 319, 540, 15, 16, 0, 0, &sgpClickBoxCellFile, MENU_HardcoreCheckBoxCallback, nullptr, nullptr, 2 }, // 203
	{ D2WIN_EDITBOX, 318, 510, 157, 16, 8, 4, nullptr, nullptr, (void*)MENU_CreateCharacterOkCallback, &gaMenuFonts[6], 0 }, // 204
	{ D2WIN_IMAGE, 268, 350, 264, 176, 0, 0, &sgpPopUpOkCancelCellFile, nullptr, nullptr, nullptr, 0 }, // 205
	{ D2WIN_BUTTON, 281, 337, 96, 32, 0, 5103, &sgpOkCancelButtonBlankCellFile, MENU_CreateCharacterCancelCallback, nullptr, nullptr, 2 }, // 206
	{ D2WIN_BUTTON, 421, 337, 96, 32, 0, 5102, &sgpOkCancelButtonBlankCellFile, MENU_CreateCharacterConfirmCallback, nullptr, nullptr, 2 }, // 207
	{ D2WIN_TEXTBOX, 268, 320, 264, 120, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 208
	{ D2WIN_ANIMIMAGE, 232, 364, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaAssassinAnimDescriptors[0], (void*)MENU_AssassinHoverCallback, 0 }, // 209
	{ D2WIN_ANIMIMAGE, 720, 370, 88, 184, 0, 0, nullptr, MENU_CharClassClickCallback, &gaDruidAnimDescriptors[0], (void*)MENU_DruidHoverCallback, 0 }, // 210
	{ D2WIN_TEXTBOX, 339, 561, 200, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 211
	{ D2WIN_BUTTON, 319, 540, 15, 16, 0, 0, &sgpClickBoxCellFile, MENU_ExpansionCheckBoxCallback, nullptr, nullptr, 2 }, // 212
	{ D2WIN_IMAGE, 319, 540, 15, 16, 0, 0, &sgpJoinGameClickBoxGreyCellFile, nullptr, nullptr, nullptr, 0 }, // 213
	{ D2WIN_IMAGE, 268, 350, 264, 176, 0, 0, &sgpPopUpOkCancel2CellFile, nullptr, nullptr, nullptr, 0 }, // 214
	{ D2WIN_BUTTON, 281, 337, 96, 32, VK_ESCAPE, 5167, &sgpCancelButtonBlankCellFile, CHARSEL_DeleteCharacterCancelCallback, nullptr, nullptr, 2 }, // 215
	{ D2WIN_BUTTON, 421, 337, 96, 32, 0, 5166, &sgpCancelButtonBlankCellFile, CHARSEL_DeleteCharacterConfirmCallback, nullptr, nullptr, 2 }, // 216
	{ D2WIN_TEXTBOX, 268, 320, 264, 120, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 217
	{ D2WIN_IMAGE, 268, 350, 264, 176, 0, 0, &sgpPopUpOkCancel2CellFile, nullptr, nullptr, nullptr, 0 }, // 218
	{ D2WIN_BUTTON, 281, 337, 96, 32, VK_ESCAPE, 5167, &sgpCancelButtonBlankCellFile, CHARSEL_ConvertToExpansionCancelCallback, nullptr, nullptr, 2 }, // 219
	{ D2WIN_BUTTON, 421, 337, 96, 32, 0, 5166, &sgpCancelButtonBlankCellFile, CHARSEL_ConvertToExpansionConfirmCallback, nullptr, nullptr, 2 }, // 220
	{ D2WIN_TEXTBOX, 268, 310, 264, 120, 9, 0, nullptr, nullptr, nullptr, &gaMenuFonts[4], 2 }, // 221
	{ D2WIN_IMAGE, 268, 350, 264, 176, 0, 0, &sgpPopUpOkCellFile, nullptr, nullptr, nullptr, 0 }, // 222
	{ D2WIN_BUTTON, 351, 337, 96, 32, VK_ESCAPE, 5103, &sgpCancelButtonBlankCellFile, MENU_PopupButtonCallback, nullptr, nullptr, 2 }, // 223
	{ D2WIN_TEXTBOX, 268, 300, 264, 100, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 224
	{ D2WIN_BUTTON, 351, 337, 96, 32, VK_RETURN, 5102, &sgpCancelButtonBlankCellFile, MENU_PopupButtonCallback, nullptr, nullptr, 2 }, // 225
	{ D2WIN_IMAGE, 222, 426, 340, 224, 0, 0, &sgpPopUp340x224CellFile, nullptr, nullptr, nullptr, 0 }, // 226
	{ D2WIN_BUTTON, 330, 416, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, MENU_PopupButtonCallback, nullptr, nullptr, 0 }, // 227
	{ D2WIN_TEXTBOX, 222, 280, 340, 60, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 228
	{ D2WIN_TEXTBOX, 222, 360, 340, 70, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 229
	{ D2WIN_TEXTBOX, 222, 370, 340, 20, 10, 4, nullptr, nullptr, nullptr, &gaMenuFonts[6], 2 }, // 230
	{ D2WIN_IMAGE, 195, 422, 410, 245, 0, 0, &sgpPopUpWideCellFile, nullptr, nullptr, nullptr, 0 }, // 231
	{ D2WIN_BUTTON, 335, 412, 128, 35, VK_RETURN, 5102, &sgpMediumButtonBlankCellFile, MENU_PopupButtonCallback, nullptr, nullptr, 0 }, // 232
	{ D2WIN_TEXTBOX, 195, 237, 410, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 233
	{ D2WIN_TEXTBOX, 199, 377, 402, 140, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[2], 0 }, // 234
	{ D2WIN_IMAGE, 158, 460, 485, 290, 0, 0, &sgpPopUpLargestCellFile, nullptr, nullptr, nullptr, 0 }, // 235
	{ D2WIN_BUTTON, 335, 450, 128, 35, VK_RETURN, 5102, &sgpMediumButtonBlankCellFile, MENU_PopupButtonCallback, nullptr, nullptr, 0 }, // 236
	{ D2WIN_TEXTBOX, 158, 220, 485, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 237
	{ D2WIN_TEXTBOX, 162, 420, 477, 200, 10, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 0 }, // 238
	{ D2WIN_TEXTBOX, 162, 320, 477, 100, 10, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 0 }, // 239
	{ D2WIN_TEXTBOX, 162, 420, 477, 100, 10, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 240
	{ D2WIN_IMAGE, 158, 460, 485, 290, 0, 0, &sgpPopUpLargestCellFile, nullptr, nullptr, nullptr, 0 }, // 241
	{ D2WIN_BUTTON, 335, 450, 128, 35, VK_RETURN, 5102, &sgpMediumButtonBlankCellFile, MENU_PopupButtonCallback, nullptr, nullptr, 0 }, // 242
	{ D2WIN_TEXTBOX, 158, 220, 485, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 243
	{ D2WIN_TEXTBOX, 162, 270, 477, 50, 10, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 0 }, // 244
	{ D2WIN_TEXTBOX, 158, 310, 485, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 245
	{ D2WIN_TEXTBOX, 162, 420, 477, 100, 10, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 246
	{ D2WIN_IMAGE, 268, 350, 264, 176, 0, 0, &sgpPopUpOk2CellFile, nullptr, nullptr, nullptr, 0 }, // 247
	{ D2WIN_BUTTON, 351, 337, 96, 32, VK_RETURN, 5102, &sgpOkCancelButtonBlankCellFile, MENU_PopupButtonCallback, nullptr, nullptr, 2 }, // 248
	{ D2WIN_TEXTBOX, 268, 320, 264, 120, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 249
	{ D2WIN_BUTTON, 351, 337, 96, 32, VK_ESCAPE, 5103, &sgpOkCancelButtonBlankCellFile, MENU_PopupButtonCallback, nullptr, nullptr, 2 }, // 250
	{ D2WIN_TIMER, 40, 0, 0, 0, 0, 0, nullptr, MENU_ShowCannotConnectToBattleNetPopup, nullptr, nullptr, 0 }, // 251
	{ D2WIN_BUTTON, 351, 337, 96, 32, VK_ESCAPE, 5103, &sgpCancelButtonBlankCellFile, MENU_CancelPatchCallback, nullptr, nullptr, 2 }, // 252
	{ D2WIN_BUTTON, 351, 337, 96, 32, VK_RETURN, 5102, &sgpCancelButtonBlankCellFile, MENU_CancelPatchCallback, nullptr, nullptr, 2 }, // 253
	{ D2WIN_TEXTBOX, 268, 337, 264, 120, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[2], 2 }, // 254
	{ D2WIN_BUTTON, 264, 310, 272, 35, 0, 5115, &sgpWideButtonBlankCellFile, MENU_OpenBattleNetCallback, nullptr, nullptr, 0 }, // 255
	{ D2WIN_BUTTON, 264, 350, 272, 35, 0, 5116, &sgpWideButtonBlankCellFile, MENU_TcpIpCallback, nullptr, nullptr, 0 }, // 256
	{ D2WIN_BUTTON, 264, 568, 272, 35, VK_ESCAPE, 5103, &sgpWideButtonBlankCellFile, MENU_BackToMainMenuCallback, nullptr, nullptr, 0 }, // 257
	{ D2WIN_IMAGE, 0, 599, 800, 600, 0, 0, &sgpTcpIpBackgroundCellFile, nullptr, nullptr, nullptr, 0 }, // 258
	{ D2WIN_TEXTBOX, 100, 76, 600, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[0], 2 }, // 259
	{ D2WIN_TEXTBOX, 270, 156, 272, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 260
	{ D2WIN_TEXTBOX, 265, 171, 272, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 261
	{ D2WIN_BUTTON, 265, 206, 272, 35, 0, 5118, &sgpWideButtonBlankCellFile, MENU_TcpIpHostGameCallback, nullptr, (void*)MENU_TcpIpHostButtonHoverCallback, 0 }, // 262
	{ D2WIN_BUTTON, 265, 264, 272, 35, 0, 5119, &sgpWideButtonBlankCellFile, MENU_TcpIpJoinGameCallback, nullptr, (void*)MENU_TcpIpJoinButtonHoverCallback, 0 }, // 263
	{ D2WIN_TEXTBOX, 265, 520, 272, 210, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[8], 2 }, // 264
	{ D2WIN_TEXTBOX, 265, 520, 272, 210, 2, 0, nullptr, nullptr, nullptr, &gaMenuFonts[8], 2 }, // 265
	{ D2WIN_BUTTON, 39, 571, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, MENU_OtherMultiplayerCallback, nullptr, nullptr, 0 }, // 266
	{ D2WIN_TIMER, 5000, 0, 0, 0, 0, 0, nullptr, MENU_TcpIpTimerCallback, nullptr, nullptr, 0 }, // 267
	{ D2WIN_TEXTBOX, 300, 250, 200, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 268
	{ D2WIN_EDITBOX, 300, 268, 213, 20, 0, 0, nullptr, nullptr, (void*)MENU_TcpIpJoinGameOkCallback, &gaMenuFonts[6], 0 }, // 269
	{ D2WIN_IMAGE, 291, 270, 218, 26, 0, 0, &sgpIpAddressBoxCellFile, nullptr, nullptr, nullptr, 0 }, // 270
	{ D2WIN_IMAGE, 268, 350, 264, 176, 0, 0, &sgpPopUpOkCancel2CellFile, nullptr, nullptr, nullptr, 0 }, // 271
	{ D2WIN_BUTTON, 281, 337, 96, 32, VK_ESCAPE, 5103, &sgpCancelButtonBlankCellFile, MENU_TcpIpJoinGameCancelCallback, nullptr, nullptr, 0 }, // 272
	{ D2WIN_BUTTON, 421, 337, 96, 32, VK_RETURN, 5102, &sgpCancelButtonBlankCellFile, MENU_TcpIpJoinGameOkCallback, nullptr, nullptr, 0 }, // 273
	{ D2WIN_TEXTBOX, 0, 96, 800, 30, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 274
	{ D2WIN_TEXTBOX, 323, 134, 300, 30, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 16 }, // 275
	{ D2WIN_TEXTBOX, 351, 134, 425, 30, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 0 }, // 276
	{ D2WIN_TEXTBOX, 0, 599, 200, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 277
	{ D2WIN_IMAGE, 0, 599, 800, 600, 0, 0, &sgpDownloadPatchBackgroundCellFile, nullptr, nullptr, nullptr, 0 }, // 278
	{ D2WIN_IMAGE, 400, 300, 207, 172, 0, 0, &sgpDownloadPatchBallCellFile, nullptr, nullptr, nullptr, 0 }, // 279
	{ D2WIN_BUTTON, 336, 540, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, MENU_CancelPatchCallback, nullptr, nullptr, 0 }, // 280
	{ D2WIN_IMAGE2, 195, 422, 410, 245, 4, 4, &sgpTileableDialogCellFile, nullptr, nullptr, nullptr, 0 }, // 281
	{ D2WIN_BUTTON, 335, 412, 128, 35, 0, 0, &sgpMediumButtonBlankCellFile, nullptr, nullptr, nullptr, 0 }, // 282
	{ D2WIN_BUTTON, 415, 412, 128, 35, 0, 0, &sgpMediumButtonBlankCellFile, nullptr, nullptr, nullptr, 0 }, // 283
	{ D2WIN_BUTTON, 255, 412, 128, 35, 0, 0, &sgpMediumButtonBlankCellFile, nullptr, nullptr, nullptr, 0 }, // 284
	{ D2WIN_TEXTBOX, 195, 237, 410, 40, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 285
	{ D2WIN_TEXTBOX, 199, 377, 402, 140, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[2], 0 }, // 286
	{ D2WIN_TEXTBOX, 199, 377, 402, 180, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[2], 0 }, // 287
	{ D2WIN_IMAGE, 250, 347, 300, 26, 0, 0, &sgpEditTextBoxWideCellFile, nullptr, nullptr, nullptr, 0 }, // 288
	{ D2WIN_IMAGE, 250, 401, 300, 26, 0, 0, &sgpEditTextBoxWideCellFile, nullptr, nullptr, nullptr, 0 }, // 289
	{ D2WIN_TEXTBOX, 200, 350, 400, 100, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 290
	{ D2WIN_TEXTBOX, 200, 515, 400, 100, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 291
	{ D2WIN_TEXTBOX, 252, 340, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 292
	{ D2WIN_TEXTBOX, 252, 394, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 293
	{ D2WIN_EDITBOX, 253, 342, 293, 19, 8, 4, nullptr, nullptr, nullptr, &gaMenuFonts[6], 0 }, // 294
	{ D2WIN_EDITBOX, 253, 396, 293, 19, 8, 4, nullptr, nullptr, nullptr, &gaMenuFonts[6], 0 }, // 295
	{ D2WIN_BUTTON, 265, 527, 272, 35, VK_RETURN, 11097, &sgpWideButtonBlankCellFile, BNET_RegisterEmailOkCallback, nullptr, nullptr, 0 }, // 296
	{ D2WIN_BUTTON, 265, 572, 272, 35, 0, 11098, &sgpWideButtonBlankCellFile, BNET_RegisterEmailLaterCallback, nullptr, nullptr, 0 }, // 297
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, BNET_RegisterEmailCancelCallback, nullptr, nullptr, 0 }, // 298
	{ D2WIN_TEXTBOX, 0, 310, 800, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 299
	{ D2WIN_BUTTON, 627, 572, 128, 35, 0, 11062, &sgpMediumButtonBlankCellFile, BNET_ResetPasswordOkCallback, nullptr, nullptr, 0 }, // 300
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, BNET_BackToAccountOptionsCallback, nullptr, nullptr, 0 }, // 301
	{ D2WIN_TEXTBOX, 158, 500, 480, 220, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 302
	{ D2WIN_IMAGE, 248, 427, 300, 26, 0, 0, &sgpEditTextBoxWideCellFile, nullptr, nullptr, nullptr, 0 }, // 303
	{ D2WIN_TEXTBOX, 250, 420, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 304
	{ D2WIN_EDITBOX, 251, 422, 293, 19, 8, 4, nullptr, nullptr, (void*)BNET_ResetPasswordOkCallback, &gaMenuFonts[6], 0 }, // 305
	{ D2WIN_IMAGE, 248, 477, 300, 26, 0, 0, &sgpEditTextBoxWideCellFile, nullptr, nullptr, nullptr, 0 }, // 306
	{ D2WIN_TEXTBOX, 250, 470, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 307
	{ D2WIN_EDITBOX, 251, 472, 293, 19, 8, 4, nullptr, nullptr, (void*)BNET_ResetPasswordOkCallback, &gaMenuFonts[6], 0 }, // 308
	{ D2WIN_TEXTBOX, 0, 285, 800, 35, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 309
	{ D2WIN_TEXTBOX, 0, 300, 800, 16, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 310
	{ D2WIN_TEXTBOX, 0, 385, 800, 16, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 311
	{ D2WIN_TEXTBOX, 0, 470, 800, 16, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 312
	{ D2WIN_BUTTON, 264, 335, 272, 35, 0, 11050, &sgp3WideButtonBlankCellFile, BNET_ChangePasswordCallback, nullptr, nullptr, 0 }, // 313
	{ D2WIN_BUTTON, 264, 420, 272, 35, 0, 11113, &sgp3WideButtonBlankCellFile, BNET_ResetPasswordCallback, nullptr, nullptr, 0 }, // 314
	{ D2WIN_BUTTON, 264, 505, 272, 35, 0, 11115, &sgp3WideButtonBlankCellFile, BNET_ChangeEmailCallback, nullptr, nullptr, 0 }, // 315
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, BNET_AccountOptionsBackCallback, nullptr, nullptr, 0 }, // 316
	{ D2WIN_TEXTBOX, 0, 310, 800, 50, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[1], 2 }, // 317
	{ D2WIN_TEXTBOX, 158, 500, 480, 220, 10, 8, nullptr, nullptr, nullptr, &gaMenuFonts[3], 2 }, // 318
	{ D2WIN_IMAGE, 248, 402, 300, 26, 0, 0, &sgpEditTextBoxWideCellFile, nullptr, nullptr, nullptr, 0 }, // 319
	{ D2WIN_TEXTBOX, 250, 395, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 320
	{ D2WIN_EDITBOX, 251, 397, 293, 19, 8, 4, nullptr, nullptr, (void*)BNET_ChangeEmailOkCallback, &gaMenuFonts[6], 0 }, // 321
	{ D2WIN_IMAGE, 248, 452, 300, 26, 0, 0, &sgpEditTextBoxWideCellFile, nullptr, nullptr, nullptr, 0 }, // 322
	{ D2WIN_TEXTBOX, 250, 445, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 323
	{ D2WIN_EDITBOX, 251, 447, 293, 19, 8, 4, nullptr, nullptr, (void*)BNET_ChangeEmailOkCallback, &gaMenuFonts[6], 0 }, // 324
	{ D2WIN_IMAGE, 248, 502, 300, 26, 0, 0, &sgpEditTextBoxWideCellFile, nullptr, nullptr, nullptr, 0 }, // 325
	{ D2WIN_TEXTBOX, 250, 495, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 326
	{ D2WIN_EDITBOX, 251, 497, 293, 19, 8, 4, nullptr, nullptr, (void*)BNET_ChangeEmailOkCallback, &gaMenuFonts[6], 0 }, // 327
	{ D2WIN_IMAGE, 248, 552, 300, 26, 0, 0, &sgpEditTextBoxWideCellFile, nullptr, nullptr, nullptr, 0 }, // 328
	{ D2WIN_TEXTBOX, 250, 545, 300, 32, 0, 0, nullptr, nullptr, nullptr, &gaMenuFonts[3], 0 }, // 329
	{ D2WIN_EDITBOX, 251, 547, 293, 19, 8, 4, nullptr, nullptr, (void*)BNET_ChangeEmailOkCallback, &gaMenuFonts[6], 0 }, // 330
	{ D2WIN_BUTTON, 627, 572, 128, 35, 0, 11062, &sgpMediumButtonBlankCellFile, BNET_ChangeEmailOkCallback, nullptr, nullptr, 0 }, // 331
	{ D2WIN_BUTTON, 33, 572, 128, 35, VK_ESCAPE, 5103, &sgpMediumButtonBlankCellFile, BNET_BackToAccountOptionsCallback, nullptr, nullptr, 0 }, // 332
};

//D2Launch.0x6FA17750
void __fastcall MENU_SetPopupCallback(D2PopupCallback pfCallback)
{
	gpfPopupCallback = pfCallback;
}

//D2Launch.0x6FA17760
void __fastcall MENU_SetPopupActive(BOOL bUnused)
{
	sgbPopupActive = TRUE;
}

//D2Launch.0x6FA17770
void __stdcall MENU_WaitForCharacterCreationCallback(DWORD dwUnused)
{
	D2MCPCLIENT_10003();
	if (D2MCPCLIENT_10029() || !D2MCPCLIENT_10002() || sgbWaitPopupCancelled)
	{
		D2MCPCLIENT_10028(0);
		D2Win_10009();
	}
}

//D2Launch.0x6FA177B0
void __stdcall MENU_WaitForCharacterLogonCallback(DWORD dwUnused)
{
	D2MCPCLIENT_10003();
	if (D2MCPCLIENT_10031() || !D2MCPCLIENT_10002() || sgbWaitPopupCancelled)
	{
		D2MCPCLIENT_10030(0);
		D2Win_10009();
	}
}

//D2Launch.0x6FA177F0
void __stdcall MENU_WaitForCharacterDeletionCallback(DWORD dwUnused)
{
	D2MCPCLIENT_10003();
	if (D2MCPCLIENT_10033() || !D2MCPCLIENT_10002() || sgbWaitPopupCancelled)
	{
		D2MCPCLIENT_10032(0);
		D2Win_10009();
	}
}

//D2Launch.0x6FA17830
void __stdcall MENU_WaitForCharacterUpgradeCallback(DWORD dwUnused)
{
	D2MCPCLIENT_10003();
	if (D2MCPCLIENT_10061() || !D2MCPCLIENT_10002() || sgbWaitPopupCancelled)
	{
		D2MCPCLIENT_10060(0);
		D2Win_10009();
	}
}

//D2Launch.0x6FA17870
BOOL __fastcall MENU_LoadPalette(const char* szPalDatFileName, const char* szPalPL2FileName)
{
	char szPalPL2Path[260];
	char szPalDatPath[260];

	sgbPaletteChanged = TRUE;
	wsprintfA(szPalDatPath, "%s\\%s", "DATA\\GLOBAL", szPalDatFileName);
	wsprintfA(szPalPL2Path, "%s\\%s", "DATA\\GLOBAL", szPalPL2FileName);
	sgbFeCharPalette = strcmp(szPalDatFileName, gszFeCharPaletteDat) == 0;
	D2Win_10028(szPalDatPath, szPalPL2Path);
	return TRUE;
}

//D2Launch.0x6FA17920
D2WinControlStrc* __fastcall MENU_CreateSubChild(int32_t nIndex)
{
	D2_ASSERT(sgnNumSubChildren < MAX_CHILDREN);

	D2WinControlStrc* pControl = CONTROL_Create(&gaControlInits[nIndex]);
	sgpSubChildren[sgnNumSubChildren] = pControl;
	++sgnNumSubChildren;
	return pControl;
}

//D2Launch.0x6FA17970
void __fastcall MENU_DestroySubChildren()
{
	for (int32_t i = 0; i < sgnNumSubChildren; ++i)
	{
		CONTROL_Destroy(&sgpSubChildren[i]);
	}

	sgnNumSubChildren = 0;
}

//D2Launch.0x6FA179B0
D2WinControlStrc* __fastcall MENU_CreateChild(int32_t nIndex)
{
	D2_ASSERT(sgnNumChildren < MAX_CHILDREN);

	D2WinControlStrc* pControl = CONTROL_Create(&gaControlInits[nIndex]);
	sgpChildren[sgnNumChildren] = pControl;
	++sgnNumChildren;
	return pControl;
}

//D2Launch.0x6FA17A00
void __fastcall MENU_DestroyChildren()
{
	for (int32_t i = 0; i < sgnNumChildren; ++i)
	{
		CONTROL_Destroy(&sgpChildren[i]);
	}

	sgpAnimatedLogoLeft = nullptr;
	sgpAnimatedLogoRight = nullptr;
	sgnNumChildren = 0;

	MENU_DestroySubChildren();
	BACKGROUND_SetCellFile(nullptr);

	if (sgbPaletteChanged)
	{
		MENU_LoadPalette(gszFeCharPaletteDat, gszFeCharPalettePl2);
		sgbPaletteChanged = FALSE;
	}

	CHARSEL_FreeCharacterList();
	CHARSEL_FreeRealmCharListCache();
	D2Win_10029(1);
}

// Helper function, inlined in the original game
static void MENU_CreatePopupSubChild(int32_t nIndex, BOOL bModal)
{
	D2WinControlStrc* pControl = MENU_CreateSubChild(nIndex);
	if (bModal)
	{
		D2Win_10033(pControl, 1);
	}
	D2Win_10030_CONTROL_ToggleFourthFlag(pControl, 1);
}

//D2Launch.0x6FA17B40
void __fastcall MENU_ShowTitledMessage(const Unicode* wszTitle, const Unicode* wszMessage, D2PopupCallback pfCallback)
{
	MENU_DestroySubChildren();

	MENU_CreatePopupSubChild(231, TRUE);
	MENU_CreatePopupSubChild(232, FALSE);

	D2WinTextBoxStrc* pTitle = (D2WinTextBoxStrc*)MENU_CreateSubChild(233);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pTitle->controlHeader, 1);
	MENU_AddTextBoxLines(pTitle, wszTitle, 0, 0);

	D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(234);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	MENU_AddTextBoxLines(pMessage, wszMessage, 0, 0);

	gpfPopupCallback = pfCallback;
}

//D2Launch.0x6FA17D90
void __fastcall MENU_ShowTitledMessage2(const Unicode* wszTitle, const Unicode* wszMessage, const Unicode* wszMessage2, D2PopupCallback pfCallback)
{
	MENU_DestroySubChildren();

	MENU_CreatePopupSubChild(235, TRUE);
	MENU_CreatePopupSubChild(236, FALSE);

	D2WinTextBoxStrc* pTitle = (D2WinTextBoxStrc*)MENU_CreateSubChild(237);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pTitle->controlHeader, 1);
	MENU_AddTextBoxLines(pTitle, wszTitle, 0, 0);

	if (wszMessage2 && wszMessage2[0])
	{
		D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(239);
		D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
		MENU_AddTextBoxLines(pMessage, wszMessage, 0, 0);

		D2WinTextBoxStrc* pMessage2 = (D2WinTextBoxStrc*)MENU_CreateSubChild(240);
		D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage2->controlHeader, 1);
		MENU_AddTextBoxLines(pMessage2, wszMessage2, 4, 0);
	}
	else
	{
		D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(238);
		D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
		MENU_AddTextBoxLines(pMessage, wszMessage, 0, 0);
	}

	gpfPopupCallback = pfCallback;
}

//D2Launch.0x6FA180E0
BOOL __fastcall MENU_AddTextBoxLines(D2WinTextBoxStrc* pTextBox, const Unicode* wszText, int32_t nColor, int32_t nAlign)
{
	Unicode wszBuffer[1024];

	Unicode::strncpy(wszBuffer, wszText, std::size(wszBuffer));

	Unicode* pLineStart = wszBuffer;
	Unicode* pCurrent = wszBuffer;
	if (wszBuffer[0])
	{
		do
		{
			if (*pCurrent == '\n')
			{
				*pCurrent = 0;
				D2Win_10051(pTextBox, pLineStart, nColor, nAlign, 0);
				pLineStart = pCurrent + 1;
			}

			++pCurrent;
		}
		while (*pCurrent);

		if (pLineStart < pCurrent)
		{
			D2Win_10051(pTextBox, pLineStart, nColor, nAlign, 0);
		}
	}

	return TRUE;
}

//D2Launch.0x6FA18180
void __fastcall MENU_ShowTitledMessageWithParam(const Unicode* wszTitle, const Unicode* wszMessage, const Unicode* wszParam, const Unicode* wszMessage2, D2PopupCallback pfCallback)
{
	MENU_DestroySubChildren();

	MENU_CreatePopupSubChild(241, TRUE);
	MENU_CreatePopupSubChild(242, FALSE);

	D2WinTextBoxStrc* pTitle = (D2WinTextBoxStrc*)MENU_CreateSubChild(243);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pTitle->controlHeader, 1);
	MENU_AddTextBoxLines(pTitle, wszTitle, 0, 0);

	D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(244);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	MENU_AddTextBoxLines(pMessage, wszMessage, 0, 0);

	D2WinTextBoxStrc* pParam = (D2WinTextBoxStrc*)MENU_CreateSubChild(245);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pParam->controlHeader, 1);
	MENU_AddTextBoxLines(pParam, wszParam, 0, 0);

	D2WinTextBoxStrc* pMessage2 = (D2WinTextBoxStrc*)MENU_CreateSubChild(246);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage2->controlHeader, 1);
	MENU_AddTextBoxLines(pMessage2, wszMessage2, 4, 0);

	gpfPopupCallback = pfCallback;
}

//D2Launch.0x6FA184B0
void __fastcall MENU_ShowMessageWithButton(const Unicode* wszMessage, D2PopupCallback pfCallback, BOOL bOkButton)
{
	D2WinControlStrc* pBackground = nullptr;
	D2WinControlStrc* pButton = nullptr;
	D2WinTextBoxStrc* pMessage = nullptr;

	MENU_DestroySubChildren();

	if (sgbFeCharPalette)
	{
		pBackground = MENU_CreateSubChild(247);
		D2Win_10033(pBackground, 1);
		pButton = MENU_CreateSubChild(bOkButton ? 248 : 250);
		pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(249);
	}
	else
	{
		pBackground = MENU_CreateSubChild(222);
		D2Win_10033(pBackground, 1);
		pButton = MENU_CreateSubChild(bOkButton ? 225 : 223);
		pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(224);
	}

	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(pButton, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	MENU_AddTextBoxLines(pMessage, wszMessage, 0, 0);

	gpfPopupCallback = pfCallback;
}

//D2Launch.0x6FA18720
void __fastcall MENU_ShowMessage(const Unicode* wszMessage, D2PopupCallback pfCallback)
{
	D2WinControlStrc* pBackground = nullptr;
	D2WinControlStrc* pButton = nullptr;
	D2WinTextBoxStrc* pMessage = nullptr;

	MENU_DestroySubChildren();

	if (sgbFeCharPalette)
	{
		pBackground = MENU_CreateSubChild(247);
		D2Win_10033(pBackground, 1);
		pButton = MENU_CreateSubChild(248);
		pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(249);
	}
	else
	{
		pBackground = MENU_CreateSubChild(222);
		D2Win_10033(pBackground, 1);
		pButton = MENU_CreateSubChild(225);
		pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(224);
	}

	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(pButton, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	MENU_AddTextBoxLines(pMessage, wszMessage, 0, 0);

	gpfPopupCallback = pfCallback;
}

//D2Launch.0x6FA18960
void __fastcall MENU_ShowMessageBox(const Unicode* wszTitle, const Unicode* wszMessage, int32_t nOkStringId, int32_t nCancelStringId, int32_t(__stdcall* pfOk)(SMSGHANDLER_PARAMS*), int32_t(__stdcall* pfCancel)(SMSGHANDLER_PARAMS*), BOOL bOkOnEnter, BOOL bCloseOnEscape)
{
	D2_ASSERTM(nOkStringId, "okButtonString");

	const int32_t nButtons = nCancelStringId ? 2 : 1;

	MENU_DestroySubChildren();

	if (nButtons == 1)
	{
		MENU_CreatePopupSubChild(231, TRUE);

		gaControlInits[282].nStringId = nOkStringId;
		if (bCloseOnEscape)
		{
			gaControlInits[282].field_14 = VK_ESCAPE;
		}
		else
		{
			gaControlInits[282].field_14 = bOkOnEnter ? VK_RETURN : 0;
		}
		gaControlInits[282].field_20 = pfOk;

		MENU_CreatePopupSubChild(282, FALSE);
	}
	else if (nButtons == 2)
	{
		MENU_CreatePopupSubChild(281, TRUE);

		gaControlInits[283].nStringId = nOkStringId;
		gaControlInits[283].field_20 = pfOk;
		gaControlInits[283].field_14 = bOkOnEnter ? VK_RETURN : 0;
		MENU_CreatePopupSubChild(283, FALSE);

		gaControlInits[284].nStringId = nCancelStringId;
		gaControlInits[284].field_20 = pfCancel;
		gaControlInits[284].field_14 = bOkOnEnter ? VK_ESCAPE : 0;
		MENU_CreatePopupSubChild(284, FALSE);
	}

	if (wszTitle)
	{
		D2WinTextBoxStrc* pTitle = (D2WinTextBoxStrc*)MENU_CreateSubChild(285);
		D2Win_10030_CONTROL_ToggleFourthFlag(&pTitle->controlHeader, 1);
		D2Win_10044(pTitle, wszTitle);
	}

	D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(wszTitle ? 286 : 287);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	D2Win_10044(pMessage, wszMessage);
}

//D2Launch.0x6FA18C60
int32_t __stdcall MENU_ClosePopupCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroySubChildren();
	return 1;
}

//D2Launch.0x6FA18CA0
void __fastcall MENU_CancelWaitPopup()
{
	sgbWaitPopupCancelled = TRUE;
}

//D2Launch.0x6FA18CB0
BOOL __fastcall MENU_IsWaitPopupCancelled()
{
	return sgbWaitPopupCancelled;
}

//D2Launch.0x6FA18CC0
void __fastcall MENU_ShowWaitPopup()
{
	D2WinControlStrc* pBackground = nullptr;
	D2WinControlStrc* pButton = nullptr;
	D2WinTextBoxStrc* pMessage = nullptr;

	MENU_DestroySubChildren();

	sgbPopupActive = TRUE;
	sgbWaitPopupCancelled = FALSE;

	if (sgbFeCharPalette)
	{
		pBackground = MENU_CreateSubChild(247);
		D2Win_10033(pBackground, 0);
		pButton = MENU_CreateSubChild(250);
		pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(249);
	}
	else
	{
		pBackground = MENU_CreateSubChild(222);
		D2Win_10033(pBackground, 0);
		pButton = MENU_CreateSubChild(223);
		pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(224);
	}

	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(pButton, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	D2Win_10044(pMessage, D2LANG_GetStringFromTblIndex(5243));

	gpfPopupCallback = MENU_CancelWaitPopup;
}

//D2Launch.0x6FA18EA0
int32_t __stdcall MENU_ShowCannotConnectToBattleNetPopup(SMSGHANDLER_PARAMS* pMsg)
{
	gpfPopupCallback = MENU_CancelWaitPopup;

	MENU_DestroySubChildren();
	MENU_CreatePopupSubChild(222, TRUE);
	MENU_CreatePopupSubChild(253, FALSE);

	D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(254);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	D2Win_10045(pMessage, "Can't connect to Battle.Net. Try again later.");
	return 1;
}

//D2Launch.0x6FA18FC0
void __fastcall MENU_CloseWaitPopup()
{
	for (int32_t i = 0; i < sgnNumSubChildren; ++i)
	{
		CONTROL_Destroy(&sgpSubChildren[i]);
	}

	sgnNumSubChildren = 0;
}

// Helper function, inlined in the original game
static void MENU_UpdatePatchProgressBar(int32_t nProgress)
{
	char szProgress[100];

	IMAGE_SetFrame(sgpPatchProgressImage, IMAGE_GetFrameCount(sgpPatchProgressImage) * nProgress / 100);
	sprintf(szProgress, "%d%%", nProgress);
	if (sgpPatchProgressTextBox)
	{
		D2Win_10046(sgpPatchProgressTextBox, szProgress, 0);
	}
}

//D2Launch.0x6FA19000
void __fastcall MENU_CreatePatchMenu()
{
	MENU_CreateBlankScreen();

	MENU_CreateChild(278);
	sgpPatchProgressImage = (D2WinImageStrc*)MENU_CreateChild(279);
	IMAGE_ForceNormalDrawMode(sgpPatchProgressImage, 3);
	sgpPatchProgressTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(275);

	int32_t nProgress = gptComInt->GetPatchProgress();
	if (nProgress > 100)
	{
		nProgress = 100;
	}

	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(276), D2LANG_GetStringFromTblIndex(5178), 0, 0, 0);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(274), D2LANG_GetStringFromTblIndex(5179), 0, 0, 0);
	MENU_CreateChild(280);

	MENU_UpdatePatchProgressBar(nProgress);
}

//D2Launch.0x6FA19260
void __fastcall MENU_UpdatePatchProgress()
{
	D2Win_10047(sgpPatchProgressTextBox);

	int32_t nProgress = gptComInt->GetPatchProgress();
	if (nProgress > 100)
	{
		nProgress = 100;
	}

	MENU_UpdatePatchProgressBar(nProgress);
}

//D2Launch.0x6FA192E0
void __fastcall MENU_ResetPatchCancelled()
{
	sgbPatchCancelled = FALSE;
}

//D2Launch.0x6FA192F0
BOOL __fastcall MENU_IsPatchCancelled()
{
	return sgbPatchCancelled;
}

//D2Launch.0x6FA19300
int32_t __stdcall MENU_CancelPatchCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gptComInt->CancelPatch();
	sgbPatchCancelled = TRUE;
	MENU_ShowMainMenu();
	return 1;
}

// Helper function, inlined in the original game
static void MENU_PlayMenuMusic()
{
	if (D2SOUND_10069())
	{
		D2SOUND_10034(1);
	}
}

//D2Launch.0x6FA19320
void __fastcall MENU_ShowMainMenu()
{
	char szVersion[32];
	D2WinButtonStrc* pBattleNetButton = nullptr;
	D2WinButtonStrc* pOtherMultiplayerButton = nullptr;

	BNET_Disconnect();
	gptParams->szServerIP[0] = 0;
	MENU_CreateBlankScreen();

	if (FOG_IsExpansion())
	{
		sgpGatewayButton = (D2WinButtonStrc*)MENU_CreateChild(18);
		MENU_UpdateGatewayButton();
		pBattleNetButton = (D2WinButtonStrc*)MENU_CreateChild(17);
		pOtherMultiplayerButton = (D2WinButtonStrc*)MENU_CreateChild(19);
		MENU_CreateChild(16);
	}
	else
	{
		pBattleNetButton = (D2WinButtonStrc*)MENU_CreateChild(10);
		sgpGatewayButton = (D2WinButtonStrc*)MENU_CreateChild(11);
		MENU_UpdateGatewayButton();
		MENU_CreateChild(9);
		pOtherMultiplayerButton = (D2WinButtonStrc*)MENU_CreateChild(12);
	}

	if (D2Win_10185())
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(&pBattleNetButton->controlHeader, 0);
		D2Win_10025_CONTROL_ToggleFirstFlag(&pOtherMultiplayerButton->controlHeader, 0);
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpGatewayButton->controlHeader, 0);
	}

	MENU_CreateChild(13);
	MENU_CreateChild(14);
	MENU_CreateChild(15);

	D2WinTextBoxStrc* pVersionTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(277);

	D2_ASSERT(gptComInt != nullptr);

	const int32_t nVersion = gptComInt->GetVersion();
	if (gptParams->bBuild)
	{
		SStrPrintf(szVersion, sizeof(szVersion), "v %d.%02d %d", nVersion / 100 + 1, nVersion % 100, gptComInt->GetBuild());
	}
	else
	{
		SStrPrintf(szVersion, sizeof(szVersion), "v %d.%02d", nVersion / 100 + 1, nVersion % 100);
	}

	D2Win_10046(pVersionTextBox, szVersion, 0);

	MENU_PlayMenuMusic();
}

//D2Launch.0x6FA19750
void __fastcall MENU_ShowCharacterSelection()
{
	D2SOUND_10042();
	MENU_DestroyChildren();
	CHARSEL_CreateMenu();
}

// Helper function, inlined in the original game
static int32_t MENU_IsValidAccountNameChar(char c)
{
	switch (c)
	{
	case '"':
	case '#':
	case '%':
	case '*':
	case ',':
	case '/':
	case '<':
	case '>':
	case '?':
	case '\\':
		return 0;

	default:
		if (c <= ' ')
		{
			return 0;
		}

		return c < 0x7F;
	}
}

//D2Launch.0x6FA19890
int32_t __stdcall MENU_AccountNameCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar)
{
	return MENU_IsValidAccountNameChar(*pChar);
}

//D2Launch.0x6FA19910
void __fastcall MENU_ShowLoginMenu()
{
	char szLastAccountName[1024];

	sgbPopupActive = TRUE;

	if (gptComInt->IsConnected())
	{
		if (BNET_IsLoggedIn())
		{
			BNET_Disconnect();
			MENU_ShowMainMenu();
			if (!BNET_Connect())
			{
				return;
			}
		}
	}
	else
	{
		MENU_ShowMainMenu();
		if (!BNET_Connect())
		{
			return;
		}
	}

	sgpAccountNameEditBox = nullptr;
	sgpPasswordEditBox = nullptr;
	sgpConfirmPasswordEditBox = nullptr;
	sgpLoginOkButton = nullptr;

	MENU_CreateBlankScreen();

	MENU_CreateChild(21);
	MENU_CreateChild(22);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(26), D2LANG_GetStringFromTblIndex(5224));
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(27), D2LANG_GetStringFromTblIndex(5225));

	if (!FOG_IsExpansion())
	{
		D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(31), D2LANG_GetStringFromTblIndex(5204), 0, 0, 0);
	}

	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(32), D2LANG_GetStringFromTblIndex(5205), 0, 0, 0);

	sgpAccountNameEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(34);
	D2Win_10081(sgpAccountNameEditBox, 16);
	D2Win_10073(sgpAccountNameEditBox, MENU_LoginEditBoxCallback);
	D2Win_10072(sgpAccountNameEditBox, MENU_LoginAccountNameCharFilter);

	sgpPasswordEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(35);
	D2Win_10081(sgpPasswordEditBox, 13);
	D2Win_10073(sgpPasswordEditBox, MENU_LoginEditBoxCallback);
	D2Win_10072(sgpPasswordEditBox, MENU_PasswordCharFilter);

	if (SRegLoadString("Diablo II", "Last BNet", 0, szLastAccountName, sizeof(szLastAccountName)))
	{
		D2Win_10076(sgpAccountNameEditBox, szLastAccountName);
		D2Win_10012(sgpPasswordEditBox);
	}
	else
	{
		D2Win_10012(sgpAccountNameEditBox);
	}

	D2Win_10080_EDITBOX_SetNextEditBox(sgpAccountNameEditBox, sgpPasswordEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpPasswordEditBox, sgpAccountNameEditBox);

	MENU_CreateChild(36);
	MENU_CreateChild(37);
	sgpLoginOkButton = (D2WinButtonStrc*)MENU_CreateChild(38);
	MENU_CreateChild(39);

	MENU_UpdateLoginOkButton();

	if (sgbShowLogonFailedHint)
	{
		D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(40), D2LANG_GetStringFromTblIndex(11106));
	}

	MENU_PlayMenuMusic();
}

//D2Launch.0x6FA19E40
int32_t __stdcall MENU_LoginAccountNameCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar)
{
	return MENU_IsValidAccountNameChar(*pChar);
}

//D2Launch.0x6FA19EC0
int32_t __stdcall MENU_PasswordCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar)
{
	return 1;
}

//D2Launch.0x6FA19ED0
void __fastcall MENU_SetShowLogonFailedHint(BOOL bShow)
{
	sgbShowLogonFailedHint = bShow;
}

// Helper function, inlined in the original game
static void MENU_UpdateHostIpAddress()
{
	const char* szIpAddress = FOG_GetHostIPAddress();
	D2Win_10047(sgpHostIpTextBox);

	if (!strcmp(szIpAddress, "127.0.0.1"))
	{
		D2Win_10044(sgpHostIpTextBox, D2LANG_GetStringFromTblIndex(5124));
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpTcpIpHostButton->controlHeader, 0);
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpTcpIpJoinButton->controlHeader, 0);
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpHostIpLabelTextBox->controlHeader, 0);
	}
	else
	{
		D2Win_10045(sgpHostIpTextBox, szIpAddress);
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpTcpIpHostButton->controlHeader, 1);
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpTcpIpJoinButton->controlHeader, 1);
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpHostIpLabelTextBox->controlHeader, 1);
	}
}

//D2Launch.0x6FA19EE0
int32_t __stdcall MENU_TcpIpTimerCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_UpdateHostIpAddress();
	return 1;
}

//D2Launch.0x6FA19F90
void __fastcall MENU_ShowTcpIpMenu()
{
	sgbPopupActive = TRUE;
	BNET_Disconnect();
	MENU_DestroyChildren();
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);

	MENU_CreateChild(258);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(259), D2LANG_GetStringFromTblIndex(5117));

	sgpHostIpLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(260);
	D2Win_10044(sgpHostIpLabelTextBox, D2LANG_GetStringFromTblIndex(5121));

	sgpTcpIpHostButton = (D2WinButtonStrc*)MENU_CreateChild(262);
	sgpTcpIpJoinButton = (D2WinButtonStrc*)MENU_CreateChild(263);

	sgpTcpIpHostHelpTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(264);
	D2Win_10044(sgpTcpIpHostHelpTextBox, D2LANG_GetStringFromTblIndex(5122));
	sgpTcpIpJoinHelpTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(265);
	D2Win_10044(sgpTcpIpJoinHelpTextBox, D2LANG_GetStringFromTblIndex(5123));
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpTcpIpHostHelpTextBox->controlHeader, 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpTcpIpJoinHelpTextBox->controlHeader, 0);

	D2Win_10031(MENU_CreateChild(266));

	sgpTcpIpTimer = (D2WinTimerStrc*)MENU_CreateChild(267);
	D2Win_10180(sgpTcpIpTimer);
	D2Win_10182(sgpTcpIpTimer);

	sgpHostIpTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(261);

	MENU_UpdateTcpIpMenu();
}

//D2Launch.0x6FA1A430
void __fastcall MENU_UpdateTcpIpMenu()
{
	MENU_UpdateHostIpAddress();
}

//D2Launch.0x6FA1A4E0
int32_t __stdcall MENU_TcpIpHostButtonHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpTcpIpHostHelpTextBox->controlHeader, pMsg->lParam != 0);
	return 1;
}

//D2Launch.0x6FA1A520
int32_t __stdcall MENU_TcpIpJoinButtonHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpTcpIpJoinHelpTextBox->controlHeader, pMsg->lParam != 0);
	return 1;
}

//D2Launch.0x6FA1A560
void __fastcall MENU_ShowCreateAccountMenu()
{
	MENU_CreateBlankScreen();

	MENU_CreateChild(21);
	MENU_CreateChild(22);
	MENU_CreateChild(23);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(26), D2LANG_GetStringFromTblIndex(5224));
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(27), D2LANG_GetStringFromTblIndex(5225));
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(28), D2LANG_GetStringFromTblIndex(10834));

	if (!FOG_IsExpansion())
	{
		D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(31), D2LANG_GetStringFromTblIndex(5222), 0, 0, 0);
	}

	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(32), D2LANG_GetStringFromTblIndex(5223), 0, 0, 0);

	sgpAccountNameEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(84);
	D2Win_10072(sgpAccountNameEditBox, MENU_CreateAccountNameCharFilter);
	D2Win_10081(sgpAccountNameEditBox, 16);
	D2Win_10076(sgpAccountNameEditBox, gptParams->szAccountName);

	sgpPasswordEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(85);
	D2Win_10072(sgpPasswordEditBox, MENU_PasswordCharFilter);
	D2Win_10081(sgpPasswordEditBox, 13);
	D2Win_10076(sgpPasswordEditBox, gptParams->szAccountPassword);

	sgpConfirmPasswordEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(86);
	D2Win_10081(sgpConfirmPasswordEditBox, 13);

	if (!gptParams->szAccountName[0])
	{
		D2Win_10012(sgpAccountNameEditBox);
	}
	else if (!gptParams->szAccountPassword[0])
	{
		D2Win_10012(sgpPasswordEditBox);
	}
	else
	{
		D2Win_10012(sgpConfirmPasswordEditBox);
	}

	D2Win_10080_EDITBOX_SetNextEditBox(sgpAccountNameEditBox, sgpPasswordEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpPasswordEditBox, sgpConfirmPasswordEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpConfirmPasswordEditBox, sgpAccountNameEditBox);

	MENU_CreateChild(87);
	MENU_CreateChild(88);
}

//D2Launch.0x6FA1AA40
int32_t __stdcall MENU_CreateAccountNameCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar)
{
	return MENU_IsValidAccountNameChar(*pChar);
}

//D2Launch.0x6FA1AAC0
BOOL __fastcall MENU_ShowTermsOfService()
{
	char szLanguage[116];
	char szFileName[128];
	Unicode wszLine[200];
	DWORD dwBytesRead = 0;

	sgbPatchCancelled = FALSE;

	MENU_DestroySubChildren();
	sgbPopupActive = TRUE;
	sgbWaitPopupCancelled = FALSE;

	D2WinControlStrc* pBackground = MENU_CreateSubChild(222);
	D2Win_10033(pBackground, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(252), 1);
	D2WinTextBoxStrc* pWaitMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(224);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pWaitMessage->controlHeader, 1);
	MENU_CreateSubChild(251);
	D2Win_10044(pWaitMessage, D2LANG_GetStringFromTblIndex(5243));

	D2LANG_10006(szLanguage, 2);
	SStrCopy(szFileName, "tos-unicode_", sizeof(szFileName));
	SStrNCat(szFileName, szLanguage, sizeof(szFileName));
	SStrNCat(szFileName, ".txt", sizeof(szFileName));
	gptComInt->DownloadFile(szFileName, strlen(szFileName));
	D2Win_10008(MENU_DownloadTermsOfServiceCallback);

	if (sgbPatchCancelled)
	{
		MENU_DestroySubChildren();
		return FALSE;
	}

	if (!gptComInt->IsConnected())
	{
		MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5347), MENU_ShowMainMenu, TRUE);
		return FALSE;
	}

	MENU_DestroySubChildren();
	MENU_DestroyChildren();

	ANIMIMAGE_SetIsRunning((D2WinAnimImageStrc*)MENU_CreateChild(6), 0);
	ANIMIMAGE_SetIsRunning((D2WinAnimImageStrc*)MENU_CreateChild(7), 0);
	MENU_CreateChild(8);
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);

	MENU_CreateChild(77);
	D2WinTextBoxStrc* pTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(78);

	HANDLE hFile = FOG_CreateFileA(szFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5347), MENU_ShowMainMenu, TRUE);
		return FALSE;
	}

	const DWORD dwFileSize = GetFileSize(hFile, nullptr);
	uint8_t* pFileData = (uint8_t*)D2_ALLOC(dwFileSize);
	void* pBufferToFree = pFileData;
	FOG_ReadFile(hFile, pFileData, dwFileSize, &dwBytesRead, nullptr);
	FOG_CloseFile(hFile);
	FOG_DeleteFileA(szFileName);

	Unicode* pText = nullptr;
	uint32_t nLength = 0;
	if (dwFileSize == dwBytesRead && dwFileSize > 2)
	{
		const uint16_t nBom = *(uint16_t*)pFileData;
		if (nBom == 0xFEFF)
		{
			pText = (Unicode*)(pFileData + 2);
			nLength = (dwFileSize - 2) / 2;
		}
		else if (nBom == 0xFFFE)
		{
			pText = (Unicode*)(pFileData + 2);
			nLength = (dwFileSize - 2) / 2;
			for (uint32_t i = 0; i < nLength; ++i)
			{
				const uint16_t nChar = pText[i];
				pText[i] = (uint16_t)((nChar >> 8) | (nChar << 8));
			}
		}
		else
		{
			pText = (Unicode*)D2_ALLOC(2 * dwFileSize + 1);
			Unicode::win2Unicode(pText, (const char*)pFileData, dwFileSize);
			D2_FREE(pFileData);
			pBufferToFree = pText;
			nLength = dwFileSize;
		}
	}

	int32_t nPos = 0;
	int32_t nLineStart = 0;
	while (nLineStart < (int32_t)nLength)
	{
		std::fill(std::begin(wszLine), std::end(wszLine), Unicode(0));

		int32_t nLineLength = 0;
		while (nPos < (int32_t)nLength)
		{
			const Unicode wChar = pText[nPos];
			if (wChar == '\r' || wChar == '\n')
			{
				wszLine[nLineLength] = ' ';
				nLineLength = std::size(wszLine);
				++nPos;
			}
			else if (wChar == '\t')
			{
				++nPos;
				wszLine[nLineLength] = ' ';
				++nLineLength;
			}
			else
			{
				wszLine[nLineLength] = wChar;
				++nLineLength;
				++nPos;
			}

			if (D2Win_10121_GetTextWidth(wszLine) > 540)
			{
				nLineLength = Unicode::strlen(wszLine);
				while (nLineLength > 1 && !Unicode::isLineBreak(&pText[nLineStart], nLineLength))
				{
					--nLineLength;
				}

				wszLine[nLineLength] = 0;
				nPos = nLineLength + nLineStart;
				if (nLineLength && wszLine[nLineLength - 1] == ' ')
				{
					wszLine[nLineLength - 1] = 0;
				}
				break;
			}

			if (nLineLength >= (int32_t)std::size(wszLine))
			{
				break;
			}
		}

		const int32_t nStrLen = Unicode::strlen(wszLine);
		for (int32_t i = 0; i < nStrLen; ++i)
		{
			if (wszLine[i] != ' ')
			{
				D2Win_10051(pTextBox, wszLine, 0, 0, 0);
				break;
			}
		}

		nLineStart = nPos;
	}

	D2_FREE(pBufferToFree);
	D2Win_10053(pTextBox, 0);

	MENU_CreateChild(79);
	MENU_CreateChild(80);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(81), D2LANG_GetStringFromTblIndex(5180), 0, 0, 0);
	MENU_CreateChild(82);
	MENU_CreateChild(83);
	return TRUE;
}

//D2Launch.0x6FA1B170
void __stdcall MENU_DownloadTermsOfServiceCallback(DWORD dwUnused)
{
	if (gptComInt->GetPatchProgress() == BNPATCH_DONE || sgbPatchCancelled)
	{
		D2Win_10009();
	}
}

//D2Launch.0x6FA1B1A0
int32_t __stdcall MENU_AcceptTermsOfServiceCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_ShowCreateAccountMenu();
	return 1;
}

// Helper function, inlined in the original game
static D2WinTextBoxStrc* MENU_GetFirstChildTextBox()
{
	D2WinControlStrc* hChild = nullptr;
	for (int32_t i = 0; i < sgnNumChildren; ++i)
	{
		if (CONTROL_GetType(sgpChildren[i]) == D2WIN_TEXTBOX)
		{
			hChild = sgpChildren[i];
			break;
		}
	}

	D2_ASSERT(hChild != NULL);
	return (D2WinTextBoxStrc*)hChild;
}

//D2Launch.0x6FA1B1B0
int32_t __stdcall MENU_TermsOfServicePageUpCallback(SMSGHANDLER_PARAMS* pMsg)
{
	D2WinTextBoxStrc* pTextBox = MENU_GetFirstChildTextBox();

	const int32_t nLine = D2Win_10054(pTextBox);
	if (nLine > 0)
	{
		D2Win_10053(pTextBox, nLine - 1);
	}

	return 1;
}

//D2Launch.0x6FA1B220
int32_t __stdcall MENU_TermsOfServicePageDownCallback(SMSGHANDLER_PARAMS* pMsg)
{
	D2WinTextBoxStrc* pTextBox = MENU_GetFirstChildTextBox();
	D2Win_10053(pTextBox, D2Win_10054(pTextBox) + 1);
	return 1;
}

// Helper function, inlined in the original game
static void MENU_SetLocalGameArenaFlags()
{
	gptParams->nArenaFlags = 4;
	if (gptParams->unpackedCTemp.nCharacterSaveFlags & LAUNCHSAVEFLAG_HARDCORE)
	{
		gptParams->nArenaFlags = 0x804;
	}

	if (gptParams->unpackedCTemp.nCharacterSaveFlags & LAUNCHSAVEFLAG_EXPANSION)
	{
		gptParams->nArenaFlags |= 0x100000;
	}
}

//D2Launch.0x6FA1B290
int32_t __stdcall MENU_CreateCharacterConfirmCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (gptParams->unpackedCTemp.nCharacterClassId == CHARCLASS_ASSASSIN || gptParams->unpackedCTemp.nCharacterClassId == CHARCLASS_DRUID)
	{
		gptParams->unpackedCTemp.nCharacterSaveFlags |= LAUNCHSAVEFLAG_EXPANSION;
	}

	switch (gnGameType)
	{
	case MODE_OPEN:
		D2MCPClientCloseMCP();
		SAVE_SetRealmCharacter(FALSE);
		SAVE_CreateCharacter(gptParams->szName, gptParams->unpackedCTemp.nCharacterClassId, &gptParams->tCharPreviewInfo, gptParams->unpackedCTemp.nCharacterSaveFlags);
		SAVE_WriteCharacterFile(gptParams->szName);
		gptParams->nLaunchType = LAUNCHTYPE_OPENBNET;
		gnNextModule = 3;
		gptParams->nArenaFlags = 0x804;
		gptParams->szCharacterRealm[0] = 0;
		gptParams->szRealm[0] = 0;
		D2Win_10009();
		break;

	case MODE_LOCAL:
		SAVE_CreateCharacter(gptParams->szName, gptParams->unpackedCTemp.nCharacterClassId, &gptParams->tCharPreviewInfo, gptParams->unpackedCTemp.nCharacterSaveFlags);
		SAVE_WriteCharacterFile(gptParams->szName);
		gptParams->nLaunchType = LAUNCHTYPE_LOCAL;
		gptParams->dwGameType = 0;
		MENU_SetLocalGameArenaFlags();
		gnNextModule = 1;
		D2Win_10009();
		break;

	case MODE_TCPIP:
		SAVE_SetRealmCharacter(FALSE);
		SAVE_CreateCharacter(gptParams->szName, gptParams->unpackedCTemp.nCharacterClassId, &gptParams->tCharPreviewInfo, gptParams->unpackedCTemp.nCharacterSaveFlags);
		SAVE_WriteCharacterFile(gptParams->szName);
		gptParams->nLaunchType = LAUNCHTYPE_TCPIP;
		gnNextModule = 1;
		MENU_SetLocalGameArenaFlags();
		D2Win_10009();
		break;

	case MODE_CLOSED:
		MENU_CreateRealmCharacter();
		break;
	}

	return 1;
}

//D2Launch.0x6FA1B4C0
int32_t __stdcall MENU_CreateCharacterCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroySubChildren();
	MENU_CreateCharacterCreationMenu();
	return 1;
}

//D2Launch.0x6FA1B500
int32_t __stdcall MENU_CreateCharacterOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	char szSavePath[1024];
	Unicode wszMessage[1024];

	if (!D2Win_10024_CONTROL_CheckFirstFlag(&sgpCharCreateOkButton->controlHeader))
	{
		return 1;
	}

	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	for (int32_t i = 0; i < sizeof(szSavePath); ++i)
	{
		if (szSavePath[i] == '\\')
		{
			szSavePath[i + 1] = 0;
			break;
		}
	}

	DWORD dwSectorsPerCluster = 0;
	DWORD dwBytesPerSector = 0;
	DWORD dwNumberOfFreeClusters = 0;
	DWORD dwTotalNumberOfClusters = 0;
	GetDiskFreeSpaceA(szSavePath, &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);
	if (dwNumberOfFreeClusters * dwBytesPerSector * dwSectorsPerCluster >= 5000)
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpCharCreateOkButton->controlHeader, 0);
		MENU_ValidateCharacterCreation();
		return 1;
	}

	const Unicode* wszText = D2LANG_GetStringFromTblIndex(5149);
	MENU_DestroySubChildren();

	D2WinControlStrc* pBackground = MENU_CreateSubChild(247);
	D2Win_10033(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(250), 1);
	D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(249);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	MENU_AddTextBoxLines(pMessage, wszText, 0, 0);

	gpfPopupCallback = MENU_ShowCharacterSelection;
	return 1;
}

//D2Launch.0x6FA1B750
void __fastcall MENU_CreateCharacterCreationMenu()
{
	MENU_LoadCharacterCreationCellFiles();
	MENU_DestroyChildren();

	sgnHoveredClass = -1;
	sgnSelectedClass = -1;
	gptParams->unpackedCTemp.nCharacterSaveFlags = 0;
	MENU_LoadPalette(gszFeCharPaletteDat, gszFeCharPalettePl2);

	MENU_CreateChild(177);
	sgpCharClassNameTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(197);
	sgpCharClassDescriptionTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(198);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(174), D2LANG_GetStringFromTblIndex(5127), 0, 0, 0);

	if (gnGameType == MODE_CLOSED)
	{
		sgpCharCreateRealmInfoTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(199);
		D2Win_10062(sgpCharCreateRealmInfoTextBox, -6, 0);
		D2Win_10051(sgpCharCreateRealmInfoTextBox, D2LANG_GetStringFromTblIndex(5276), 1, 0, 0);
		D2Win_10051(sgpCharCreateRealmInfoTextBox, D2LANG_GetStringFromTblIndex(5277), 1, 0, 0);
	}

	D2Win_10031(MENU_CreateChild(175));

	sgpCharNameEditBoxImage = (D2WinImageStrc*)MENU_CreateChild(200);
	sgpCharNameLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(201);
	D2Win_10051(sgpCharNameLabelTextBox, D2LANG_GetStringFromTblIndex(5125), 4, 0, 0);

	sgpCharNameEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(204);
	D2Win_10081(sgpCharNameEditBox, 16);
	D2Win_10072(sgpCharNameEditBox, MENU_CharacterNameCharFilter);
	D2Win_10073(sgpCharNameEditBox, MENU_CharacterNameEditBoxCallback);

	if (FOG_IsExpansion())
	{
		sgpExpansionLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(211);
		D2Win_10051(sgpExpansionLabelTextBox, D2LANG_GetStringFromTblIndex(22731), 4, 0, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionLabelTextBox->controlHeader, 0);

		sgpExpansionCheckBox = (D2WinButtonStrc*)MENU_CreateChild(212);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionCheckBox->controlHeader, 0);

		sgpExpansionCheckBoxDisabledImage = (D2WinImageStrc*)MENU_CreateChild(213);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionCheckBoxDisabledImage->controlHeader, 0);

		sgpHardcoreLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(189);
		D2Win_10051(sgpHardcoreLabelTextBox, D2LANG_GetStringFromTblIndex(5126), 4, 0, 0);
		sgpHardcoreCheckBox = (D2WinButtonStrc*)MENU_CreateChild(190);

		if (gnGameType == MODE_CLOSED)
		{
			if (gbAllowHardcore)
			{
				sgpLadderLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(195);
				sgpLadderCheckBox = (D2WinButtonStrc*)MENU_CreateChild(196);
			}
			else
			{
				sgpLadderLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(193);
				sgpLadderCheckBox = (D2WinButtonStrc*)MENU_CreateChild(194);
			}
		}
	}
	else
	{
		sgpHardcoreLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(202);
		D2Win_10051(sgpHardcoreLabelTextBox, D2LANG_GetStringFromTblIndex(5126), 4, 0, 0);
		sgpHardcoreCheckBox = (D2WinButtonStrc*)MENU_CreateChild(203);

		if (gnGameType == MODE_CLOSED)
		{
			if (gbAllowHardcore)
			{
				sgpLadderLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(193);
				sgpLadderCheckBox = (D2WinButtonStrc*)MENU_CreateChild(194);
			}
			else
			{
				sgpLadderLabelTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(191);
				sgpLadderCheckBox = (D2WinButtonStrc*)MENU_CreateChild(192);
			}
		}
	}

	if (gnGameType == MODE_CLOSED)
	{
		D2Win_10051(sgpLadderLabelTextBox, D2LANG_GetStringFromTblIndex(10927), 4, 0, 0);
	}

	sgpCharCreateOkButton = (D2WinButtonStrc*)MENU_CreateChild(176);

	if (!gbAllowHardcore)
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpHardcoreCheckBox->controlHeader, 0);
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpHardcoreLabelTextBox->controlHeader, 0);
	}

	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameEditBoxImage->controlHeader, 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameLabelTextBox->controlHeader, 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpHardcoreLabelTextBox->controlHeader, 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpHardcoreCheckBox->controlHeader, 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameEditBox->controlHeader, 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharCreateOkButton->controlHeader, 0);

	if (gnGameType == MODE_CLOSED)
	{
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpLadderLabelTextBox->controlHeader, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpLadderCheckBox->controlHeader, 0);
	}

	sgpCharClassAnimImages[CHARCREATE_BARBARIAN] = (D2WinAnimImageStrc*)MENU_CreateChild(182);
	if (FOG_IsExpansion())
	{
		sgpCharClassAnimImages[CHARCREATE_SORCERESS] = (D2WinAnimImageStrc*)MENU_CreateChild(186);
		sgpCharClassAnimImages[CHARCREATE_PALADIN] = (D2WinAnimImageStrc*)MENU_CreateChild(187);
		sgpCharClassAnimImages[CHARCREATE_NECROMANCER] = (D2WinAnimImageStrc*)MENU_CreateChild(181);
		sgpCharClassAnimImages[CHARCREATE_ASSASSIN] = (D2WinAnimImageStrc*)MENU_CreateChild(209);
		sgpCharClassAnimImages[CHARCREATE_AMAZON] = (D2WinAnimImageStrc*)MENU_CreateChild(188);
		sgpCharClassAnimImages[CHARCREATE_DRUID] = (D2WinAnimImageStrc*)MENU_CreateChild(210);
		MENU_CreateChild(178);
	}
	else
	{
		sgpCharClassAnimImages[CHARCREATE_NECROMANCER] = (D2WinAnimImageStrc*)MENU_CreateChild(181);
		sgpCharClassAnimImages[CHARCREATE_SORCERESS] = (D2WinAnimImageStrc*)MENU_CreateChild(183);
		sgpCharClassAnimImages[CHARCREATE_AMAZON] = (D2WinAnimImageStrc*)MENU_CreateChild(180);
		sgpCharClassAnimImages[CHARCREATE_PALADIN] = (D2WinAnimImageStrc*)MENU_CreateChild(184);
		MENU_CreateChild(179);
	}

	MENU_UpdateCharCreateOkButton();
}

//D2Launch.0x6FA1C0E0
int32_t __stdcall MENU_CharacterNameCharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar)
{
	char szName[32];

	const char c = *pChar;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return 1;
	}

	if ((c == '-' || c == '_') && nPos)
	{
		Unicode::toUtf(szName, D2Win_10077_EDITBOX_GetText(pEditBox), sizeof(szName));
		for (const char* i = szName; *i; ++i)
		{
			if (*i == '-' || *i == '_')
			{
				return 0;
			}
		}

		return 1;
	}

	return 0;
}

// Helper function, inlined in the original game
static BOOL MENU_IsCharacterNameValid()
{
	char szName[32];

	const Unicode* wszName = D2Win_10077_EDITBOX_GetText(sgpCharNameEditBox);
	if (!wszName)
	{
		return FALSE;
	}

	const int32_t nLength = Unicode::strlen(wszName);
	Unicode::toUtf(szName, wszName, sizeof(szName));
	if (nLength < 2 || nLength >= 16)
	{
		return FALSE;
	}

	const char cLast = szName[nLength - 1];
	const char cFirst = szName[0];
	return cLast != '_' && cFirst != '_' && cLast != '-' && cFirst != '-';
}

//D2Launch.0x6FA1C160
void __stdcall MENU_CharacterNameEditBoxCallback(int32_t nUnused)
{
	D2Win_10025_CONTROL_ToggleFirstFlag(&sgpCharCreateOkButton->controlHeader, MENU_IsCharacterNameValid());
}

//D2Launch.0x6FA1C1E0
void __fastcall MENU_UpdateCharCreateOkButton()
{
	D2Win_10025_CONTROL_ToggleFirstFlag(&sgpCharCreateOkButton->controlHeader, MENU_IsCharacterNameValid());
}

// Helper function, inlined in the original game
static BOOL MENU_CanSubmitLogin()
{
	const Unicode* wszAccountName = D2Win_10077_EDITBOX_GetText(sgpAccountNameEditBox);
	const Unicode* wszPassword = D2Win_10077_EDITBOX_GetText(sgpPasswordEditBox);
	if (!wszAccountName || !wszPassword)
	{
		return FALSE;
	}

	const int32_t nAccountNameLength = Unicode::strlen(wszAccountName);
	const int32_t nPasswordLength = Unicode::strlen(wszPassword);
	return nAccountNameLength >= 1 && nAccountNameLength <= 50 && nPasswordLength >= 1 && nPasswordLength <= 13;
}

//D2Launch.0x6FA1C250
void __stdcall MENU_LoginEditBoxCallback(int32_t nUnused)
{
	const BOOL bCanSubmit = MENU_CanSubmitLogin();
	if (sgpLoginOkButton)
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpLoginOkButton->controlHeader, bCanSubmit);
	}
}

//D2Launch.0x6FA1C2C0
void __fastcall MENU_UpdateLoginOkButton()
{
	const BOOL bCanSubmit = MENU_CanSubmitLogin();
	if (sgpLoginOkButton)
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(&sgpLoginOkButton->controlHeader, bCanSubmit);
	}
}

//D2Launch.0x6FA1C330
int32_t __stdcall MENU_HardcoreCheckBoxCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gptParams->unpackedCTemp.nCharacterSaveFlags ^= LAUNCHSAVEFLAG_HARDCORE;
	return 1;
}

//D2Launch.0x6FA1C350
int32_t __stdcall MENU_LadderCheckBoxCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gptParams->unpackedCTemp.nCharacterSaveFlags ^= LAUNCHSAVEFLAG_LADDER;
	return 1;
}

//D2Launch.0x6FA1C370
int32_t __stdcall MENU_ExpansionCheckBoxCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!FOG_IsExpansion())
	{
		return 0;
	}

	gptParams->unpackedCTemp.nCharacterSaveFlags ^= LAUNCHSAVEFLAG_EXPANSION;
	return 1;
}

struct D2CharCreateClassInfoStrc
{
	int32_t nNameStringId;
	int32_t nDescriptionStringId;
	const char* szSelectSound;
	const char* szDeselectSound;
};

// Helper table, the original game used switch statements
static const D2CharCreateClassInfoStrc gaCharCreateClassInfos[] =
{
	{ 4011, 5128, "data\\global\\sfx\\cursor\\intro\\amazon select.wav", "data\\global\\sfx\\cursor\\intro\\amazon deselect.wav" },
	{ 4010, 5131, "data\\global\\sfx\\cursor\\intro\\sorceress select.wav", "data\\global\\sfx\\cursor\\intro\\sorceress deselect.wav" },
	{ 4009, 5129, "data\\global\\sfx\\cursor\\intro\\necromancer select.wav", "data\\global\\sfx\\cursor\\intro\\necromancer deselect.wav" },
	{ 4008, 5132, "data\\global\\sfx\\cursor\\intro\\paladin select.wav", "data\\global\\sfx\\cursor\\intro\\paladin deselect.wav" },
	{ 4007, 5130, "data\\global\\sfx\\cursor\\intro\\barbarian select.wav", "data\\global\\sfx\\cursor\\intro\\barbarian deselect.wav" },
	{ 10097, 22518, "data\\global\\sfx\\cursor\\intro\\druid select.wav", "data\\global\\sfx\\cursor\\intro\\druid deselect.wav" },
	{ 10098, 22519, "data\\global\\sfx\\cursor\\intro\\assassin select.wav", "data\\global\\sfx\\cursor\\intro\\assassin deselect.wav" },
};

// Helper function, inlined in the original game
static void MENU_UpdateClassHover(SMSGHANDLER_PARAMS* pMsg, int32_t nClass)
{
	if (sgnSelectedClass != -1)
	{
		return;
	}

	if (pMsg->lParam)
	{
		D2Win_10047(sgpCharClassNameTextBox);
		D2Win_10051(sgpCharClassNameTextBox, D2LANG_GetStringFromTblIndex(gaCharCreateClassInfos[nClass].nNameStringId), 0, 0, 0);
		D2Win_10047(sgpCharClassDescriptionTextBox);
		D2Win_10051(sgpCharClassDescriptionTextBox, D2LANG_GetStringFromTblIndex(gaCharCreateClassInfos[nClass].nDescriptionStringId), 0, 0, 0);
		sgnHoveredClass = nClass;
	}
	else if (sgnHoveredClass == nClass)
	{
		D2Win_10047(sgpCharClassNameTextBox);
		D2Win_10047(sgpCharClassDescriptionTextBox);
	}
}

//D2Launch.0x6FA1C3A0
int32_t __stdcall MENU_CharClassClickCallback(SMSGHANDLER_PARAMS* pMsg)
{
	D2WinAnimImageStrc* pAnimImage = (D2WinAnimImageStrc*)pMsg->hWindow;
	const int32_t nAnimState = D2Win_10106(pAnimImage);

	const int32_t nAnimImages = FOG_IsExpansion() ? CHARCREATE_NUM_CLASSES : CHARCREATE_NUM_CLASSIC_CLASSES;
	for (int32_t i = 0; i < nAnimImages; ++i)
	{
		if (!D2Win_10104(sgpCharClassAnimImages[i]))
		{
			return 0;
		}
	}

	const int32_t nPreviousClass = sgnSelectedClass;
	sgnSelectedClass = -1;
	if (nPreviousClass != -1)
	{
		D2SOUND_10042();
		if (nPreviousClass >= 0 && nPreviousClass < std::size(gaCharCreateClassInfos))
		{
			D2SOUND_10039(gaCharCreateClassInfos[nPreviousClass].szDeselectSound);
		}
	}

	int32_t nClass = -1;
	if (pAnimImage == sgpCharClassAnimImages[CHARCREATE_BARBARIAN])
	{
		nClass = CHARCLASS_BARBARIAN;
		MENU_UpdateClassHover(pMsg, nClass);
	}
	else if (pAnimImage == sgpCharClassAnimImages[CHARCREATE_NECROMANCER])
	{
		nClass = CHARCLASS_NECROMANCER;
		MENU_UpdateClassHover(pMsg, nClass);
	}
	else if (pAnimImage == sgpCharClassAnimImages[CHARCREATE_AMAZON])
	{
		nClass = CHARCLASS_AMAZON;
		MENU_UpdateClassHover(pMsg, nClass);
	}
	else if (pAnimImage == sgpCharClassAnimImages[CHARCREATE_SORCERESS])
	{
		nClass = CHARCLASS_SORCERESS;
		MENU_UpdateClassHover(pMsg, nClass);
	}
	else if (pAnimImage == sgpCharClassAnimImages[CHARCREATE_PALADIN])
	{
		nClass = CHARCLASS_PALADIN;
		MENU_UpdateClassHover(pMsg, nClass);
	}
	else if (pAnimImage == sgpCharClassAnimImages[CHARCREATE_DRUID])
	{
		nClass = CHARCLASS_DRUID;
		if (FOG_IsExpansion())
		{
			MENU_UpdateClassHover(pMsg, nClass);
		}
	}
	else if (pAnimImage == sgpCharClassAnimImages[CHARCREATE_ASSASSIN])
	{
		nClass = CHARCLASS_ASSASSIN;
		if (FOG_IsExpansion())
		{
			MENU_UpdateClassHover(pMsg, nClass);
		}
	}

	if (nClass != nPreviousClass && nAnimState == 1)
	{
		if (nClass >= 0 && nClass < std::size(gaCharCreateClassInfos))
		{
			D2SOUND_10039(gaCharCreateClassInfos[nClass].szSelectSound);
		}
		sgnSelectedClass = nClass;
	}
	else if (nAnimState != 2 && nAnimState != 3 && nAnimState != 4)
	{
		sgnSelectedClass = nClass;
	}

	MENU_SetCharCreateClass((uint8_t)sgnSelectedClass);

	if (sgnSelectedClass == -1 && nAnimState != 1)
	{
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameEditBoxImage->controlHeader, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameLabelTextBox->controlHeader, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpHardcoreLabelTextBox->controlHeader, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpHardcoreCheckBox->controlHeader, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameEditBox->controlHeader, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharCreateOkButton->controlHeader, 0);

		if (gnGameType == MODE_CLOSED)
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpLadderLabelTextBox->controlHeader, 0);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpLadderCheckBox->controlHeader, 0);
		}

		if (FOG_IsExpansion())
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionLabelTextBox->controlHeader, 0);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionCheckBox->controlHeader, 0);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionCheckBoxDisabledImage->controlHeader, 0);
		}

		D2Win_10012(nullptr);

		if (gnGameType == MODE_CLOSED)
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharCreateRealmInfoTextBox->controlHeader, 1);
		}
	}
	else
	{
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameEditBoxImage->controlHeader, 1);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameLabelTextBox->controlHeader, 1);

		if (gbAllowHardcore)
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpHardcoreLabelTextBox->controlHeader, 1);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpHardcoreCheckBox->controlHeader, 1);
		}

		if (gnGameType == MODE_CLOSED)
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpLadderLabelTextBox->controlHeader, 1);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpLadderCheckBox->controlHeader, 1);
		}

		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharNameEditBox->controlHeader, 1);
		D2Win_10012(sgpCharNameEditBox);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharCreateOkButton->controlHeader, 1);

		if (gnGameType == MODE_CLOSED)
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCharCreateRealmInfoTextBox->controlHeader, 0);
		}
	}

	if (FOG_IsExpansion())
	{
		if (sgnSelectedClass == CHARCLASS_ASSASSIN || sgnSelectedClass == CHARCLASS_DRUID)
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionLabelTextBox->controlHeader, 1);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionCheckBox->controlHeader, 0);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionCheckBoxDisabledImage->controlHeader, 1);
			gptParams->unpackedCTemp.nCharacterSaveFlags |= LAUNCHSAVEFLAG_EXPANSION;
		}
		else if (sgnSelectedClass != -1)
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionLabelTextBox->controlHeader, 1);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionCheckBox->controlHeader, 1);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpExpansionCheckBoxDisabledImage->controlHeader, 0);
			BUTTON_SetIsPressed(sgpExpansionCheckBox, 1);
			gptParams->unpackedCTemp.nCharacterSaveFlags |= LAUNCHSAVEFLAG_EXPANSION;
		}
	}

	if (gnGameType == MODE_CLOSED)
	{
		BUTTON_SetIsPressed(sgpLadderCheckBox, 1);
		gptParams->unpackedCTemp.nCharacterSaveFlags |= LAUNCHSAVEFLAG_LADDER;
	}

	return 1;
}

//D2Launch.0x6FA1CB30
int32_t __stdcall MENU_SorceressHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_UpdateClassHover(pMsg, CHARCLASS_SORCERESS);
	return 1;
}

//D2Launch.0x6FA1CBE0
int32_t __stdcall MENU_AmazonHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_UpdateClassHover(pMsg, CHARCLASS_AMAZON);
	return 1;
}

//D2Launch.0x6FA1CC90
int32_t __stdcall MENU_AssassinHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!FOG_IsExpansion())
	{
		return 0;
	}

	MENU_UpdateClassHover(pMsg, CHARCLASS_ASSASSIN);
	return 1;
}

//D2Launch.0x6FA1CD40
int32_t __stdcall MENU_DruidHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!FOG_IsExpansion())
	{
		return 0;
	}

	MENU_UpdateClassHover(pMsg, CHARCLASS_DRUID);
	return 1;
}

//D2Launch.0x6FA1CDF0
int32_t __stdcall MENU_NecromancerHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_UpdateClassHover(pMsg, CHARCLASS_NECROMANCER);
	return 1;
}

//D2Launch.0x6FA1CEA0
int32_t __stdcall MENU_BarbarianHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_UpdateClassHover(pMsg, CHARCLASS_BARBARIAN);
	return 1;
}

//D2Launch.0x6FA1CF50
int32_t __stdcall MENU_PaladinHoverCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_UpdateClassHover(pMsg, CHARCLASS_PALADIN);
	return 1;
}

//D2Launch.0x6FA1D000
int __cdecl MENU_QuitCallback()
{
	gnNextModule = 0;
	return 0;
}

//D2Launch.0x6FA1D010
BOOL __fastcall MENU_FreeRealmList()
{
	if (sgptShardArray)
	{
		for (int32_t i = 0; i < sgnShardListSize; ++i)
		{
			if (sgptShardArray[i])
			{
				D2_ASSERT(sgptShardArray[i]->pszDescription);
				D2_FREE(sgptShardArray[i]->pszDescription);
				D2_ASSERT(sgptShardArray[i]->pszName);
				D2_FREE(sgptShardArray[i]->pszName);
				D2_FREE(sgptShardArray[i]);
			}
		}

		D2_FREE(sgptShardArray);
		sgptShardArray = nullptr;
	}

	return TRUE;
}

//D2Launch.0x6FA1D0F0
int __cdecl MENU_CompareShards(const void* pLeft, const void* pRight)
{
	return strcmp((*(const D2ShardStrc**)pLeft)->pszName, (*(const D2ShardStrc**)pRight)->pszName);
}

//D2Launch.0x6FA1D140
int32_t __fastcall MENU_GetRealmCount()
{
	return sgnShardListSize;
}

//D2Launch.0x6FA1D150
const char* __fastcall MENU_GetRealmName(int32_t index)
{
	D2_ASSERT(sgptShardArray[index]);
	return sgptShardArray[index]->pszName;
}

//D2Launch.0x6FA1D180
void __fastcall MENU_RequestRealmList()
{
	MENU_ShowWaitPopup();
	D2Win_10008(MENU_RealmListWaitCallback);

	if (gptComInt)
	{
		sgpRealmListPacket = (D2RealmListPacketStrc*)gptComInt->SendRealmList(0);
	}

	MENU_DestroySubChildren();

	if (!sgpRealmListPacket)
	{
		sgnShardListSize = -1;
		return;
	}

	sgnShardListSize = sgpRealmListPacket->nCount;
	D2_ASSERT(sgnShardListSize < 512);

	const char* pData = (const char*)sgpRealmListPacket + offsetof(D2RealmListPacketStrc, pData);
	MENU_FreeRealmList();

	const int32_t nShards = sgnShardListSize;
	if (!nShards)
	{
		return;
	}

	sgptShardArray = (D2ShardStrc**)D2_CALLOC(sizeof(D2ShardStrc*) * nShards);
	for (int32_t i = 0; i < nShards; ++i)
	{
		D2ShardStrc* pShard = D2_ALLOC_STRC(D2ShardStrc);
		pData += sizeof(uint32_t);

		size_t nLength = strlen(pData) + 1;
		pShard->pszName = (char*)D2_ALLOC(nLength);
		SStrCopy(pShard->pszName, pData, nLength);
		pData += nLength;

		nLength = strlen(pData) + 1;
		pShard->pszDescription = (char*)D2_ALLOC(nLength);
		SStrCopy(pShard->pszDescription, pData, nLength);
		pData += nLength;

		D2_ASSERT(sgptShardArray);
		for (int32_t j = 0; j < sgnShardListSize; ++j)
		{
			if (!sgptShardArray[j])
			{
				sgptShardArray[j] = pShard;
				break;
			}
		}
	}

	qsort(sgptShardArray, sgnShardListSize, sizeof(D2ShardStrc*), MENU_CompareShards);
}

//D2Launch.0x6FA1D490
int32_t __fastcall MENU_Run(D2ConfigStrc* pConfig)
{
	gptParams = pConfig;
	D2Win_10015();

	// The original game passed FOG_IsExpansion() to D2Win_GetArchive
	if (!D2LANG_10000(D2Win_GetArchive(), 0))
	{
		D2_ASSERT(0);
	}

	MENU_LoadCellFiles();
	CURSOR_SetCellFile(sgpCursorCellFile);

	gptParams->szCurrentChannelName[0] = 0;
	gptParams->szDefaultChannelName[0] = 0;
	gptParams->szGameName[0] = 0;
	gptParams->szGamePassword[0] = 0;
	if (gnGameType != MODE_TCPIP)
	{
		gptParams->szServerIP[0] = 0;
	}

	D2SOUND_10036();
	D2SOUND_10038("data\\global\\sfx\\cursor\\button.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\amazon select.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\amazon deselect.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\barbarian select.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\barbarian deselect.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\paladin select.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\paladin deselect.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\necromancer select.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\necromancer deselect.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\sorceress select.wav");
	D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\sorceress deselect.wav");
	if (FOG_IsExpansion())
	{
		D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\druid select.wav");
		D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\druid deselect.wav");
		D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\assassin select.wav");
		D2SOUND_10038("data\\global\\sfx\\cursor\\intro\\assassin deselect.wav");
	}

	gptComInt = pConfig->pComInterface;

	switch (gptParams->nLaunchType)
	{
	case LAUNCHTYPE_REALM:
	case LAUNCHTYPE_OPENBNET:
	{
		const BOOL bConnected = gptComInt->IsConnected();
		gnGameType = gptParams->nLaunchType == LAUNCHTYPE_REALM ? MODE_CLOSED : MODE_OPEN;
		D2Win_10005(1);
		if (bConnected)
		{
			CHARSEL_CreateMenu();
		}
		else
		{
			MENU_ShowLoginMenu();
		}
		break;
	}
	case LAUNCHTYPE_TCPIP:
		BNET_LoadBnClient(gptParams);
		gnGameType = MODE_TCPIP;
		D2Win_10005(1);
		MENU_ShowTcpIpMenu();
		break;

	default:
		BNET_LoadBnClient(gptParams);
		if (gptParams->bSkipToBNet)
		{
			DWORD dwSkipToOpen = 0;
			SRegLoadValue("Diablo II", "Skip To Open", 0, &dwSkipToOpen);
			gptParams->bSkipToBNet = 0;
			gptParams->bShownLogo = 1;
			D2Win_10005(1);
			gnGameType = dwSkipToOpen != 0 ? MODE_OPEN : MODE_CLOSED;
			MENU_ShowLoginMenu();
		}
		else
		{
			gnGameType = MODE_LOCAL;
			if (gptParams->bShownLogo)
			{
				D2Win_10005(1);
				MENU_ShowMainMenu();
			}
			else
			{
				D2Win_10005(1);
				D2_ASSERT(!gptParams->bShownLogo);
				D2Win_10029(0);
				MENU_DestroyChildren();
				MENU_PumpMessagesIgnoringInput();

				if (D2Win_10003())
				{
					if (FOG_10191())
					{
						WINDOW_OpenSmackCutscene("Data\\Local\\Video\\New_BLIZ640x240.bik", (D2GameResolutionMode)2, nullptr);
						WINDOW_OpenSmackCutscene("Data\\Local\\Video\\BlizNorth640x240.bik", (D2GameResolutionMode)2, nullptr);
					}
					else
					{
						WINDOW_OpenSmackCutscene("Data\\Local\\Video\\New_BLIZ640x480.bik", (D2GameResolutionMode)0, nullptr);
						WINDOW_OpenSmackCutscene("Data\\Local\\Video\\BlizNorth640x480.bik", (D2GameResolutionMode)0, nullptr);
					}

					char szAuxBattleNet[100];
					if (!SRegLoadString("Diablo II", "Aux Battle.net", 0, szAuxBattleNet, sizeof(szAuxBattleNet)))
					{
						sprintf(szAuxBattleNet, "%d.%d.%d.%d", 216, 148, 246, 34);
						SRegSaveString("Diablo II", "Aux Battle.net", 0, szAuxBattleNet);
						MENU_PumpMessagesIgnoringInput();

						char szResolution[8];
						char szVideoPath[260];
						int32_t nMode = 0;
						if (FOG_10191())
						{
							nMode = 2;
							strcpy(szResolution, "640x146");
						}
						else
						{
							strcpy(szResolution, "640x292");
						}

						MENU_BuildVideoPath(szVideoPath, "%s\\video\\%s\\d2intro%s.bik", szResolution);
						WINDOW_OpenSmackCutscene(szVideoPath, (D2GameResolutionMode)nMode, nullptr);
						MENU_ShowTitleScreen();
					}
					else if (FOG_IsExpansion() && MENU_ShouldPlayExpansionIntro())
					{
						MENU_PlayExpansionIntro();
					}
				}

				D2Win_10004(1);
				MENU_ShowTitleScreen();
				gptParams->bShownLogo = 1;
			}
		}
		break;
	}

	D2Win_10010(MENU_QuitCallback);
	D2Win_10008(BNET_IdleCallback);

	D2SOUND_10042();
	while (D2SOUND_10040())
	{
		Sleep(0);
	}
	D2SOUND_10037();

	MENU_DestroyChildren();
	MENU_FreeCellFiles();
	D2LANG_10001();
	memset(gptParams->szAccountPassword, 0x00, sizeof(gptParams->szAccountPassword));
	D2Win_10016();
	return gnNextModule;
}

// Helper function, inlined in the original game
static D2CellFileStrc* MENU_LoadCellFile(const char* szFormat)
{
	char szPath[260];
	wsprintfA(szPath, szFormat, "DATA\\GLOBAL");
	return ARCHIVE_LoadCellFile(szPath, 0);
}

//D2Launch.0x6FA1DAD0
void __fastcall MENU_LoadCellFiles()
{
	sgpBliznoCellFile = MENU_LoadCellFile("%s\\UI\\FrontEnd\\blizno");
	sgpTrademarkCellFile = MENU_LoadCellFile(FOG_IsExpansion() ? "%s\\UI\\FrontEnd\\trademarkscreenEXP" : "%s\\UI\\FrontEnd\\trademark");
	sgpCursorCellFile = MENU_LoadCellFile("%s\\UI\\CURSOR\\ohand");
	sgpDiablo2LogoCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\Diablo2");
	sgpD2LogoBlackLeftCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\D2logoBlackLeft");
	sgpD2LogoFireLeftCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\D2logoFireLeft");
	sgpD2LogoBlackRightCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\D2logoBlackRight");
	sgpD2LogoFireRightCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\D2logoFireRight");
	sgpTitleScreenCellFile = MENU_LoadCellFile(FOG_IsExpansion() ? "%s\\ui\\FrontEnd\\gameselectscreenEXP" : "%s\\ui\\FrontEnd\\TitleScreen");
	sgpCreditsBackgroundCellFile = MENU_LoadCellFile(FOG_IsExpansion() ? "%s\\ui\\CharSelect\\creditsbckgexpand" : "%s\\ui\\CharSelect\\creditsbckg");
	sgpWideButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\WideButtonBlank");
	sgpWideButtonBlank02CellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\WideButtonBlank02");
	sgpNarrowButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\NarrowButtonBlank");
	sgpGWListBoxCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\GWListBox");

	if (FOG_IsExpansion())
	{
		sgpRealmSelectButtonCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\Realmselectbutton");
		sgpTallButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\TallButtonBlank");
		sgpCharacterSelectScreenExpCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\characterselectscreenEXP");
		sgpCinematicsSelectionExpCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\CinematicsSelectionEXP");
	}

	sgpMediumButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\MediumButtonBlank");
	sgpShortButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\ShortButtonBlank");
	sgpTextBox2CellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\textbox2");
	sgp3WideButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\3WideButtonBlank");
	sgpTermsOfUseBackgroundCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\TermsofUseBckg");
	gpCharSelectBackgroundCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\charselectbckg");
	sgpDifficultyLevelsCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\DifficultyLevels");
	sgpCinematicsSelectionCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\CinematicsSelection");
	sgpCharSelectBoxCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\charselectbox");
	sgpCharSelectBoxGreyCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\charselectboxgrey");
	sgpCreateNewCharImageCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\CreateNewCharImage");
	sgpPopUpOkCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\PopUpOK");
	sgpPopUp340x224CellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\PopUp_340x224");
	sgpPopUpWideCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\PopUpWide");
	sgpPopUpLargestCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\PopUpLargest");
	sgpTileableDialogCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\TileableDialog");
	sgpPopUpOk2CellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\PopUpOK2");
	sgpPopUpOkCancelCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\PopUpOKCancel");
	sgpPopUpOkCancel2CellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\PopUpOKCancel2");
	sgpOkCancelButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\OkCancelButtonBlank");
	sgpCancelButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\CancelButtonBlank");
	sgpSelectCharArrowsCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\selectchararrows");
	sgpRealmSelectCellFile = MENU_LoadCellFile(FOG_IsExpansion() ? "%s\\ui\\CharSelect\\Realmselect" : "%s\\ui\\FrontEnd\\CurRealm");
	sgpRealmSelectButtonThinCellFile = MENU_LoadCellFile(FOG_IsExpansion() ? "%s\\ui\\CharSelect\\RealmSelectbuttonthin" : "%s\\ui\\FrontEnd\\NarrowButtonBlank02");
	sgpPasswordCellFile = MENU_LoadCellFile("%s\\ui\\CharSelect\\password");
	sgpRealmBackgroundCellFile = MENU_LoadCellFile("%s\\UI\\FrontEnd\\realmbckg");
	sgpJoinGameScrollBarsCellFile = MENU_LoadCellFile("%s\\UI\\FRONTEND\\joingamescrollbars");
	sgpTcpIpBackgroundCellFile = MENU_LoadCellFile(FOG_IsExpansion() ? "%s\\UI\\FrontEnd\\tcpipscreen" : "%s\\UI\\FrontEnd\\tcpipbckg");
	sgpIpAddressBoxCellFile = MENU_LoadCellFile("%s\\UI\\FrontEnd\\IPAddressBox");
	sgpDownloadPatchBackgroundCellFile = MENU_LoadCellFile("%s\\UI\\FrontEnd\\downloadpatchbckg");
	sgpDownloadPatchBallCellFile = MENU_LoadCellFile("%s\\UI\\FrontEnd\\downloadpatchball2");
	sgpEditTextBoxWideCellFile = MENU_LoadCellFile("%s\\UI\\FrontEnd\\EditTextBoxWide");
}

//D2Launch.0x6FA1E280
void __fastcall MENU_FreeCellFiles()
{
	ARCHIVE_FreeCellFile(sgpBliznoCellFile);
	ARCHIVE_FreeCellFile(sgpTrademarkCellFile);
	ARCHIVE_FreeCellFile(sgpUnusedCellFile);
	ARCHIVE_FreeCellFile(sgpCursorCellFile);
	ARCHIVE_FreeCellFile(sgpDiablo2LogoCellFile);
	ARCHIVE_FreeCellFile(sgpD2LogoBlackLeftCellFile);
	ARCHIVE_FreeCellFile(sgpD2LogoFireLeftCellFile);
	ARCHIVE_FreeCellFile(sgpD2LogoBlackRightCellFile);
	ARCHIVE_FreeCellFile(sgpD2LogoFireRightCellFile);
	ARCHIVE_FreeCellFile(sgpTitleScreenCellFile);
	ARCHIVE_FreeCellFile(sgpCreditsBackgroundCellFile);
	ARCHIVE_FreeCellFile(sgpWideButtonBlankCellFile);
	ARCHIVE_FreeCellFile(sgpWideButtonBlank02CellFile);
	ARCHIVE_FreeCellFile(sgpNarrowButtonBlankCellFile);
	ARCHIVE_FreeCellFile(sgpGWListBoxCellFile);

	if (FOG_IsExpansion())
	{
		ARCHIVE_FreeCellFile(sgpRealmSelectButtonCellFile);
		ARCHIVE_FreeCellFile(sgpTallButtonBlankCellFile);
		ARCHIVE_FreeCellFile(sgpCharacterSelectScreenExpCellFile);
		ARCHIVE_FreeCellFile(sgpCinematicsSelectionExpCellFile);
	}

	ARCHIVE_FreeCellFile(sgpMediumButtonBlankCellFile);
	ARCHIVE_FreeCellFile(sgpShortButtonBlankCellFile);
	ARCHIVE_FreeCellFile(sgpTextBox2CellFile);
	ARCHIVE_FreeCellFile(sgp3WideButtonBlankCellFile);
	ARCHIVE_FreeCellFile(sgpTermsOfUseBackgroundCellFile);
	ARCHIVE_FreeCellFile(gpCharSelectBackgroundCellFile);
	ARCHIVE_FreeCellFile(sgpDifficultyLevelsCellFile);
	ARCHIVE_FreeCellFile(sgpCinematicsSelectionCellFile);
	ARCHIVE_FreeCellFile(sgpCharSelectBoxCellFile);
	ARCHIVE_FreeCellFile(sgpCharSelectBoxGreyCellFile);
	ARCHIVE_FreeCellFile(sgpPopUpOkCellFile);
	ARCHIVE_FreeCellFile(sgpPopUp340x224CellFile);
	ARCHIVE_FreeCellFile(sgpPopUpWideCellFile);
	ARCHIVE_FreeCellFile(sgpPopUpLargestCellFile);
	ARCHIVE_FreeCellFile(sgpTileableDialogCellFile);
	ARCHIVE_FreeCellFile(sgpPopUpOk2CellFile);
	ARCHIVE_FreeCellFile(sgpPopUpOkCancelCellFile);
	ARCHIVE_FreeCellFile(sgpPopUpOkCancel2CellFile);
	ARCHIVE_FreeCellFile(sgpOkCancelButtonBlankCellFile);
	ARCHIVE_FreeCellFile(sgpCancelButtonBlankCellFile);
	ARCHIVE_FreeCellFile(sgpSelectCharArrowsCellFile);
	ARCHIVE_FreeCellFile(sgpRealmSelectCellFile);
	ARCHIVE_FreeCellFile(sgpRealmSelectButtonThinCellFile);
	ARCHIVE_FreeCellFile(sgpPasswordCellFile);
	ARCHIVE_FreeCellFile(sgpCreateNewCharImageCellFile);

	if (sgpCharacterCreateCellFile)
	{
		ARCHIVE_FreeCellFile(sgpCharacterCreateCellFile);
		ARCHIVE_FreeCellFile(sgpFireCellFile);
		sgpCharacterCreateCellFile = nullptr;
		ARCHIVE_FreeCellFile(sgpMediumSelButtonBlankCellFile);
		ARCHIVE_FreeCellFile(sgpCharCreateTextBoxCellFile);
		ARCHIVE_FreeCellFile(sgpClickBoxCellFile);

		for (D2CellFileStrc* pCellFile : sgpAmazonAnimCellFiles)
		{
			ARCHIVE_FreeCellFile(pCellFile);
		}

		for (D2CellFileStrc* pCellFile : sgpNecromancerAnimCellFiles)
		{
			ARCHIVE_FreeCellFile(pCellFile);
		}

		for (D2CellFileStrc* pCellFile : sgpBarbarianAnimCellFiles)
		{
			ARCHIVE_FreeCellFile(pCellFile);
		}

		for (D2CellFileStrc* pCellFile : sgpSorceressAnimCellFiles)
		{
			ARCHIVE_FreeCellFile(pCellFile);
		}

		for (D2CellFileStrc* pCellFile : sgpPaladinAnimCellFiles)
		{
			ARCHIVE_FreeCellFile(pCellFile);
		}

		for (D2CellFileStrc* pCellFile : sgpSorceressOverlayCellFiles)
		{
			ARCHIVE_FreeCellFile(pCellFile);
		}

		for (D2CellFileStrc* pCellFile : sgpNecromancerOverlayCellFiles)
		{
			ARCHIVE_FreeCellFile(pCellFile);
		}

		ARCHIVE_FreeCellFile(sgpBarbarianOverlayCellFile);
		ARCHIVE_FreeCellFile(sgpPaladinOverlayCellFile);

		if (FOG_IsExpansion())
		{
			for (D2CellFileStrc* pCellFile : sgpAssassinAnimCellFiles)
			{
				ARCHIVE_FreeCellFile(pCellFile);
			}

			for (D2CellFileStrc* pCellFile : sgpDruidAnimCellFiles)
			{
				ARCHIVE_FreeCellFile(pCellFile);
			}

			ARCHIVE_FreeCellFile(sgpJoinGameClickBoxGreyCellFile);
		}
	}

	ARCHIVE_FreeCellFile(sgpRealmBackgroundCellFile);
	ARCHIVE_FreeCellFile(sgpJoinGameScrollBarsCellFile);
	ARCHIVE_FreeCellFile(sgpTcpIpBackgroundCellFile);
	ARCHIVE_FreeCellFile(sgpIpAddressBoxCellFile);
	ARCHIVE_FreeCellFile(sgpDownloadPatchBackgroundCellFile);
	ARCHIVE_FreeCellFile(sgpDownloadPatchBallCellFile);
	ARCHIVE_FreeCellFile(sgpEditTextBoxWideCellFile);
}

// Helper function, inlined in the original game
static uint32_t MENU_GetUnlockedCinematicsFlags(BOOL* pFound)
{
	char szAuxBattleNet[100];
	int32_t nIp[4] = { 0, 0, 0, 0 };

	*pFound = FALSE;
	if (!SRegLoadString("Diablo II", "Aux Battle.net", 0, szAuxBattleNet, sizeof(szAuxBattleNet)))
	{
		return 0;
	}

	nIp[3] = 34;
	sscanf(szAuxBattleNet, "%d.%d.%d.%d", &nIp[0], &nIp[1], &nIp[2], &nIp[3]);
	*pFound = TRUE;
	return (uint8_t)nIp[3];
}

//D2Launch.0x6FA1E600
BOOL __fastcall MENU_ShouldPlayExpansionIntro()
{
	BOOL bFound = FALSE;
	const uint32_t nFlags = MENU_GetUnlockedCinematicsFlags(&bFound);
	if (!bFound || !(nFlags & CINEMATICFLAG_ACT4END))
	{
		return FALSE;
	}

	return !(nFlags & CINEMATICFLAG_EXPANSION_INTRO);
}

//D2Launch.0x6FA1E670
void __fastcall MENU_PlayExpansionIntro()
{
	char szLanguage[8];
	char szResolution[8];
	char szVideoPath[260];
	char szAuxBattleNet[100];
	int32_t nIp[4];

	MENU_PumpMessagesIgnoringInput();

	int32_t nMode = 0;
	if (FOG_10191())
	{
		nMode = 2;
		strcpy(szResolution, "640x146");
	}
	else
	{
		strcpy(szResolution, "640x292");
	}

	D2LANG_10006(szLanguage, 0);
	sprintf(szVideoPath, "%s\\video\\%s\\D2x_Intro_%s.bik", "DATA\\LOCAL", szLanguage, szResolution);

	HANDLE hFile = nullptr;
	if (SFileOpenFileEx(nullptr, szVideoPath, 0, &hFile))
	{
		SFileCloseFile(hFile);
	}
	else
	{
		sprintf(szVideoPath, "%s\\video\\%s\\D2x_Intro%s.bik", "DATA\\LOCAL", "ENG", szResolution);
	}

	WINDOW_OpenSmackCutscene(szVideoPath, (D2GameResolutionMode)nMode, nullptr);

	if (SRegLoadString("Diablo II", "Aux Battle.net", 0, szAuxBattleNet, sizeof(szAuxBattleNet)))
	{
		sscanf(szAuxBattleNet, "%d.%d.%d.%d", &nIp[0], &nIp[1], &nIp[2], &nIp[3]);
	}

	nIp[3] |= CINEMATICFLAG_EXPANSION_INTRO;
	sprintf(szAuxBattleNet, "%d.%d.%d.%d", 216, 148, 246, nIp[3]);
	SRegSaveString("Diablo II", "Aux Battle.net", 0, szAuxBattleNet);
}

//D2Launch.0x6FA1E850
void __fastcall MENU_ShowTitleScreen()
{
	MENU_DestroyChildren();

	MENU_CreateChild(2);
	MENU_CreateChild(3);
	MENU_CreateChild(6);
	MENU_CreateChild(7);
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);

	D2WinTextBoxStrc* pTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(4);
	D2Win_10051(pTextBox, D2LANG_GetStringFromTblIndex(FOG_IsExpansion() ? 21882 : 5104), 4, 0, 0);
	D2Win_10051(pTextBox, D2LANG_GetStringFromTblIndex(5105), 4, 0, 0);
	D2Win_10029(0);

	MENU_PlayMenuMusic();
}

//D2Launch.0x6FA1EB40
void __fastcall MENU_BuildVideoPath(char* szPath, const char* szFormat, const char* szResolution)
{
	char szLanguage[4];

	D2LANG_10006(szLanguage, 0);
	sprintf(szPath, szFormat, "DATA\\LOCAL", szLanguage, szResolution);
	if (MENU_FileExists(0, szPath))
	{
		return;
	}

	if (STRTABLE_GetLanguage())
	{
		sprintf(szPath, szFormat, "DATA\\LOCAL", "ENG", szResolution);
	}
	else
	{
		sprintf(szPath, szFormat, "DATA\\LOCAL", "CHI", szResolution);
	}

	MENU_FileExists(0, szPath);
}

//D2Launch.0x6FA1EC10
int32_t __stdcall MENU_SinglePlayerCallback(SMSGHANDLER_PARAMS* pMsg)
{
	char szSavePath[1024];
	char szSearchPath[1024];
	WIN32_FIND_DATAA findData;

	gnGameType = MODE_LOCAL;
	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	sprintf(szSearchPath, "%s*.d2s", szSavePath);

	HANDLE hFind = FindFirstFileA(szSearchPath, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MENU_CreateCharacterCreationMenu();
		return 1;
	}

	FindClose(hFind);
	MENU_ShowCharacterSelection();
	return 1;
}

//D2Launch.0x6FA1EDC0
int32_t __stdcall MENU_OpenBattleNetCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gnGameType = MODE_OPEN;
	MENU_ShowLoginMenu();
	return 1;
}

//D2Launch.0x6FA1EDE0
int32_t __stdcall MENU_CharacterCreationExitCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_ShowCharacterSelection();
	return 1;
}

//D2Launch.0x6FA1EF30
int32_t __stdcall MENU_OtherMultiplayerCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_CreateBlankScreen();
	MENU_CreateChild(255);
	MENU_CreateChild(256);
	MENU_CreateChild(257);
	return 1;
}

//D2Launch.0x6FA1F010
void __fastcall MENU_BalanceCreditsColumns()
{
	const int32_t nCenterLines = D2Win_10054(sgpCreditsCenterTextBox);
	int32_t nLeftLines = D2Win_10054(sgpCreditsLeftTextBox);
	int32_t nRightLines = D2Win_10054(sgpCreditsRightTextBox);

	while (nLeftLines > nRightLines)
	{
		D2Win_10045(sgpCreditsRightTextBox, gszEmptyString);
		nRightLines = D2Win_10054(sgpCreditsRightTextBox);
	}

	while (nLeftLines < nRightLines)
	{
		D2Win_10045(sgpCreditsLeftTextBox, gszEmptyString);
		nLeftLines = D2Win_10054(sgpCreditsLeftTextBox);
	}

	while (nCenterLines > nLeftLines)
	{
		D2Win_10045(sgpCreditsLeftTextBox, gszEmptyString);
		nLeftLines = D2Win_10054(sgpCreditsLeftTextBox);
		D2Win_10045(sgpCreditsRightTextBox, gszEmptyString);
	}

	if (nCenterLines < nLeftLines)
	{
		do
		{
			D2Win_10045(sgpCreditsCenterTextBox, gszEmptyString);
		}
		while (D2Win_10054(sgpCreditsCenterTextBox) < nLeftLines);
	}

	D2Win_10045(sgpCreditsCenterTextBox, gszEmptyString);
	D2Win_10045(sgpCreditsLeftTextBox, gszEmptyString);
	D2Win_10045(sgpCreditsRightTextBox, gszEmptyString);
}

//D2Launch.0x6FA1F110
BOOL __fastcall MENU_LoadCredits(int32_t nUnused)
{
	char szLanguage[4];
	char szCreditsFileName[12] = "Credits.txt";
	char szExpansionCreditsFileName[21] = "ExpansionCredits.txt";
	char szPath[260];
	Unicode wszLeft[256];
	Unicode wszRight[256];
	Unicode wszBuffer[1024];
	HSFILE hFile = nullptr;

	D2LANG_10006(szLanguage, 0);
	SStrPrintf(szPath, sizeof(szPath), "%s\\UI\\%s\\%s", "DATA\\LOCAL", szLanguage, FOG_IsExpansion() ? szExpansionCreditsFileName : szCreditsFileName);

	int32_t nLength = 0;
	Unicode* pText = nullptr;
	if (FOG_FOpenFile(szPath, &hFile))
	{
		nLength = FOG_FGetFileSize(hFile, nullptr);
		uint8_t* ptFile = (uint8_t*)D2_ALLOC(nLength);
		D2_ASSERT(ptFile);
		memset(ptFile, 0x00, nLength);
		FOG_FReadFile(hFile, ptFile, nLength, nullptr, 0, 0, 0);
		FOG_FCloseFile(hFile);

		if (nLength <= 2)
		{
			nLength = 0;
		}
		else if (*(uint16_t*)ptFile == 0xFEFF)
		{
			nLength = (nLength - 2) / 2;
			pText = (Unicode*)D2_ALLOC(sizeof(Unicode) * nLength);
			memcpy(pText, ptFile + 2, sizeof(Unicode) * nLength);
		}
		else if (*(uint16_t*)ptFile == 0xFFFE)
		{
			nLength = (nLength - 2) / 2;
			pText = (Unicode*)D2_ALLOC(sizeof(Unicode) * nLength);
			memcpy(pText, ptFile + 2, sizeof(Unicode) * nLength);
			MENU_ByteSwapUnicodeString(pText, nLength);
		}
		else
		{
			pText = (Unicode*)D2_ALLOC(2 * nLength + 1);
			Unicode::win2Unicode(pText, (const char*)ptFile, nLength);
		}

		D2_FREE(ptFile);

		for (int32_t i = 0; i < nLength; ++i)
		{
			if (pText[i] == '\n' || pText[i] == '\r')
			{
				pText[i] = 0;
			}
		}
	}

	Unicode* pTextBuffer = pText;
	const Unicode* pCurrent = pText;

	D2_ASSERTM(pTextBuffer, "Credits.txt not found");

	for (int32_t i = 0; i < 50; ++i)
	{
		D2Win_10045(sgpCreditsCenterTextBox, gszEmptyString);
		D2Win_10045(sgpCreditsLeftTextBox, gszEmptyString);
		D2Win_10045(sgpCreditsRightTextBox, gszEmptyString);
	}

	while (nLength)
	{
		if (*pCurrent == '*')
		{
			D2Win_10045(sgpCreditsLeftTextBox, gszEmptyString);
			D2Win_10045(sgpCreditsRightTextBox, gszEmptyString);

			++pCurrent;
			if (Unicode::strcpy(wszBuffer, pCurrent))
			{
				D2Win_10051(sgpCreditsCenterTextBox, wszBuffer, 1, 0, 0);
			}
			else
			{
				nLength = 0;
			}

			const int32_t nLineLength = Unicode::strlen(wszBuffer) + 2;
			nLength -= nLineLength;
			pCurrent += nLineLength;
		}
		else
		{
			while (nLength)
			{
				wszLeft[0] = 0;
				wszRight[0] = 0;

				if (*pCurrent < 0x80 && isalpha((char)*pCurrent) && Unicode::strcpy(wszBuffer, pCurrent))
				{
					Unicode::strcpy(wszLeft, wszBuffer);
					int32_t nLineLength = Unicode::strlen(wszBuffer) + 2;
					nLength -= nLineLength;
					pCurrent += nLineLength;

					if (nLength && *pCurrent != '*')
					{
						if (Unicode::strcpy(wszBuffer, pCurrent))
						{
							Unicode::strcpy(wszRight, wszBuffer);
							nLineLength = Unicode::strlen(wszBuffer) + 2;
							nLength -= nLineLength;
							pCurrent += nLineLength;
						}
						else
						{
							nLength = 0;
						}
					}
				}
				else
				{
					nLength = 0;
				}

				if (wszLeft[0] && wszRight[0])
				{
					D2Win_10044(sgpCreditsLeftTextBox, wszLeft);
					D2Win_10044(sgpCreditsRightTextBox, wszRight);
				}
				else
				{
					D2Win_10044(sgpCreditsCenterTextBox, wszLeft);
				}

				D2Win_10045(sgpCreditsCenterTextBox, gszEmptyString);

				if (*pCurrent == '*')
				{
					break;
				}
			}
		}

		MENU_BalanceCreditsColumns();
	}

	for (int32_t i = 0; i < 50; ++i)
	{
		D2Win_10045(sgpCreditsCenterTextBox, gszEmptyString);
	}

	D2Win_10045(sgpCreditsCenterTextBox, "The End");
	sgnCreditsLineCount = D2Win_10054(sgpCreditsCenterTextBox);
	D2_FREE(pTextBuffer);
	return TRUE;
}

//D2Launch.0x6FA1F5B0
void __fastcall MENU_ByteSwapUnicodeString(Unicode* pString, uint32_t nLength)
{
	for (uint32_t i = 0; i < nLength; ++i)
	{
		const uint16_t nChar = pString[i];
		pString[i] = (uint16_t)((nChar >> 8) | (nChar << 8));
	}
}

//D2Launch.0x6FA1F5E0
int32_t __stdcall MENU_ShowCreditsCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroyChildren();
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);

	MENU_CreateChild(41);
	MENU_CreateChild(42);

	if (FOG_IsExpansion())
	{
		sgpCreditsLeftTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(47);
		sgpCreditsRightTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(48);
		sgpCreditsCenterTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(49);
	}
	else
	{
		sgpCreditsLeftTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(43);
		sgpCreditsRightTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(44);
		sgpCreditsCenterTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(45);
	}

	sgpCreditsTimer = (D2WinTimerStrc*)MENU_CreateChild(46);
	D2Win_10180(sgpCreditsTimer);
	D2Win_10182(sgpCreditsTimer);

	MENU_LoadCredits(0);

	D2Win_10053(sgpCreditsCenterTextBox, 20);
	D2Win_10053(sgpCreditsLeftTextBox, 20);
	D2Win_10053(sgpCreditsRightTextBox, 20);
	return 1;
}

//D2Launch.0x6FA1F9E0
int32_t __stdcall MENU_CreditsTimerCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (sgnCreditsLineCount <= D2Win_10054(sgpCreditsCenterTextBox) + 10)
	{
		MENU_ShowMainMenu();
	}

	return 1;
}

// Helper function, inlined in the original game
static BOOL MENU_ShowInsertDiscPrompt(int32_t nBackgroundIndex, int32_t nRetryButtonIndex, int32_t nCancelButtonIndex, int32_t nMessageStringId)
{
	MENU_DestroySubChildren();

	MENU_CreatePopupSubChild(nBackgroundIndex, TRUE);
	if (nCancelButtonIndex >= 0)
	{
		MENU_CreatePopupSubChild(nCancelButtonIndex, FALSE);
	}
	MENU_CreatePopupSubChild(nRetryButtonIndex, FALSE);

	D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(217);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	D2Win_10051(pMessage, D2LANG_GetStringFromTblIndex(5168), 0, 0, 0);
	D2Win_10051(pMessage, D2LANG_GetStringFromTblIndex(nMessageStringId), 0, 0, 0);

	sgbDiscPromptCancelled = FALSE;
	sgbDiscPromptRetry = FALSE;
	return TRUE;
}

//D2Launch.0x6FA1FA10
BOOL __stdcall MENU_ShowInsertPlayDiscPrompt()
{
	MENU_ShowInsertDiscPrompt(222, 60, -1, 5169);
	sgpfLoadExpansionArchives = ARCHIVE_LoadExpansionArchives;
	sgbDiscPromptForVideo = FALSE;
	D2Win_10008(MENU_DiscPromptWaitCallback);
	MENU_DestroySubChildren();
	return sgbDiscPromptRetry;
}

//D2Launch.0x6FA1FB90
BOOL __stdcall MENU_ShowInsertExpansionDiscPrompt()
{
	MENU_ShowInsertDiscPrompt(222, 60, -1, 21880);
	sgpfLoadExpansionArchives = ARCHIVE_LoadExpansionArchives;
	sgbDiscPromptForVideo = FALSE;
	D2Win_10008(MENU_DiscPromptWaitCallback);
	MENU_DestroySubChildren();
	return sgbDiscPromptRetry;
}

// Helper function, inlined in the original game
static void MENU_DisableCinematicButton(D2WinButtonStrc* pButton, const Unicode* wszEmpty)
{
	D2Win_10025_CONTROL_ToggleFirstFlag(&pButton->controlHeader, 0);
	BUTTON_SetText(pButton, D2FONT_FONTRIDICULOUS, wszEmpty, 0);
}

//D2Launch.0x6FA1FD10
int32_t __stdcall MENU_ShowCinematicsCallback(SMSGHANDLER_PARAMS* pMsg)
{
	D2SOUND_10029(180);
	D2SOUND_10031();
	D2SOUND_10027(255);
	MENU_CreateBlankScreen();

	int32_t nUnlockedCinematics = 1;
	BOOL bFound = FALSE;
	const uint32_t nFlags = MENU_GetUnlockedCinematicsFlags(&bFound);
	if (bFound)
	{
		if (nFlags & CINEMATICFLAG_EXPANSION_OUTRO)
		{
			nUnlockedCinematics = 7;
		}
		else if (nFlags & CINEMATICFLAG_EXPANSION_INTRO)
		{
			nUnlockedCinematics = 6;
		}
		else if (nFlags & CINEMATICFLAG_ACT4END)
		{
			nUnlockedCinematics = 5;
		}
		else if (nFlags & CINEMATICFLAG_ACT4START)
		{
			nUnlockedCinematics = 4;
		}
		else if (nFlags & CINEMATICFLAG_ACT3START)
		{
			nUnlockedCinematics = 3;
		}
		else
		{
			nUnlockedCinematics = (nFlags & CINEMATICFLAG_ACT2START) ? 2 : 1;
		}
	}
	else
	{
		char szAuxBattleNet[100];
		sprintf(szAuxBattleNet, "%d.%d.%d.%d", 216, 148, 246, 34);
		SRegSaveString("Diablo II", "Aux Battle.net", 0, szAuxBattleNet);
	}

	if (FOG_IsExpansion())
	{
		MENU_DestroyChildren();
		MENU_DestroySubChildren();
		MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);

		MENU_CreateChild(8);
		MENU_CreateChild(61);
		D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(62), D2LANG_GetStringFromTblIndex(5114));
		MENU_CreateChild(63);

		D2WinButtonStrc* pButtons[6] = {};
		for (int32_t i = 0; i < std::size(pButtons); ++i)
		{
			pButtons[i] = (D2WinButtonStrc*)MENU_CreateChild(64 + i);
		}
		MENU_CreateChild(70);

		Unicode wszEmpty[1];
		wszEmpty[0] = 0;
		for (int32_t i = std::max(nUnlockedCinematics - 1, 0); i < std::size(pButtons); ++i)
		{
			MENU_DisableCinematicButton(pButtons[i], wszEmpty);
		}
	}
	else
	{
		MENU_CreateChild(50);
		D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(51), D2LANG_GetStringFromTblIndex(5114));
		MENU_CreateChild(52);

		D2WinButtonStrc* pButtons[4] = {};
		for (int32_t i = 0; i < std::size(pButtons); ++i)
		{
			pButtons[i] = (D2WinButtonStrc*)MENU_CreateChild(53 + i);
		}

		for (int32_t i = std::max(nUnlockedCinematics - 1, 0); i < std::size(pButtons); ++i)
		{
			D2Win_10025_CONTROL_ToggleFirstFlag(&pButtons[i]->controlHeader, 0);
		}

		MENU_CreateChild(57);
	}

	return 1;
}

//D2Launch.0x6FA20210
void __fastcall MENU_PumpMessagesIgnoringInput()
{
	MSG msg;
	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
		case WM_QUIT:
		case WM_CHAR:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			break;

		default:
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
			break;
		}
	}
}

// Helper function, inlined in the original game
static int32_t MENU_PlayCinematic(SMSGHANDLER_PARAMS* pMsg, const char* szFormat)
{
	char szResolution[8];
	char szVideoPath[260];

	MENU_DestroyChildren();
	MENU_DestroySubChildren();
	MENU_PumpMessagesIgnoringInput();

	if (D2Win_10003())
	{
		int32_t nMode = 0;
		if (FOG_10191())
		{
			nMode = 2;
			strcpy(szResolution, "640x146");
		}
		else
		{
			strcpy(szResolution, "640x292");
		}

		MENU_BuildVideoPath(szVideoPath, szFormat, szResolution);
		WINDOW_OpenSmackCutscene(szVideoPath, (D2GameResolutionMode)nMode, nullptr);
		D2Win_10004(1);
	}

	MENU_PumpMessagesIgnoringInput();
	MENU_ShowCinematicsCallback(pMsg);
	return 1;
}

// Helper function, inlined in the original game
static int32_t MENU_PlayClassicCinematic(SMSGHANDLER_PARAMS* pMsg, const char* szFormat)
{
	ARCHIVE_UnloadExpansionArchives();
	if (!ARCHIVE_LoadVideoArchives(MENU_ShowInsertVideoDiscPrompt, nullptr, 0))
	{
		ARCHIVE_UnloadExpansionArchives();
		ARCHIVE_LoadExpansionArchives(MENU_ShowInsertPlayDiscPrompt, MENU_ShowInsertExpansionDiscPrompt, nullptr, gptParams);
		return 0;
	}

	return MENU_PlayCinematic(pMsg, szFormat);
}

// Helper function, inlined in the original game
static int32_t MENU_PlayExpansionCinematic(SMSGHANDLER_PARAMS* pMsg, const char* szFormat)
{
	ARCHIVE_UnloadExpansionArchives();
	if (!ARCHIVE_LoadExpansionArchives(MENU_ShowInsertPlayDiscPrompt, MENU_ShowInsertExpansionDiscPrompt, nullptr, gptParams))
	{
		ARCHIVE_LoadExpansionArchives(MENU_ShowInsertPlayDiscPrompt, MENU_ShowInsertExpansionDiscPrompt, nullptr, gptParams);
	}

	return MENU_PlayCinematic(pMsg, szFormat);
}

//D2Launch.0x6FA202B0
int32_t __stdcall MENU_PlayIntroCinematicCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return MENU_PlayClassicCinematic(pMsg, "%s\\video\\%s\\d2intro%s.bik");
}

//D2Launch.0x6FA20680
int32_t __stdcall MENU_PlayAct2CinematicCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return MENU_PlayClassicCinematic(pMsg, "%s\\video\\%s\\Act02start%s.bik");
}

//D2Launch.0x6FA20A50
int32_t __stdcall MENU_PlayAct3CinematicCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return MENU_PlayClassicCinematic(pMsg, "%s\\video\\%s\\Act03start%s.bik");
}

//D2Launch.0x6FA20E20
int32_t __stdcall MENU_PlayAct4CinematicCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return MENU_PlayClassicCinematic(pMsg, "%s\\video\\%s\\Act04start%s.bik");
}

//D2Launch.0x6FA211F0
int32_t __stdcall MENU_PlayAct4EndCinematicCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return MENU_PlayClassicCinematic(pMsg, "%s\\video\\%s\\Act04end%s.bik");
}

//D2Launch.0x6FA215C0
int32_t __stdcall MENU_PlayExpansionIntroCinematicCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return MENU_PlayExpansionCinematic(pMsg, "%s\\video\\%s\\D2x_Intro_%s.bik");
}

//D2Launch.0x6FA21980
int32_t __stdcall MENU_PlayExpansionOutroCinematicCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return MENU_PlayExpansionCinematic(pMsg, "%s\\video\\%s\\D2x_Out_%s.bik");
}

//D2Launch.0x6FA21D40
int32_t __stdcall MENU_CinematicsCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	ARCHIVE_UnloadExpansionArchives();
	ARCHIVE_LoadExpansionArchives(MENU_ShowInsertPlayDiscPrompt, MENU_ShowInsertExpansionDiscPrompt, nullptr, gptParams);
	MENU_PlayMenuMusic();
	MENU_ShowMainMenu();
	return 1;
}

//D2Launch.0x6FA21D80
int32_t __stdcall MENU_InsertPlayDiscRetryCallback(SMSGHANDLER_PARAMS* pMsg)
{
	sgbDiscPromptRetry = TRUE;
	return 1;
}

//D2Launch.0x6FA21D90
int32_t __stdcall MENU_InsertVideoDiscRetryCallback(SMSGHANDLER_PARAMS* pMsg)
{
	sgbDiscPromptRetry = TRUE;
	return 1;
}

//D2Launch.0x6FA21DA0
int32_t __stdcall MENU_InsertVideoDiscCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_ShowCinematicsCallback(pMsg);
	sgbDiscPromptCancelled = TRUE;
	return 1;
}

//D2Launch.0x6FA21DC0
void __stdcall MENU_DiscPromptWaitCallback(DWORD dwUnused)
{
	if (sgbDiscPromptCancelled || sgbDiscPromptRetry)
	{
		D2Win_10009();
	}
}

//D2Launch.0x6FA21DE0
BOOL __stdcall MENU_ShowInsertVideoDiscPrompt()
{
	MENU_ShowInsertDiscPrompt(214, 59, 58, 5170);
	sgpfLoadVideoArchives = ARCHIVE_LoadVideoArchives;
	sgbDiscPromptForVideo = TRUE;
	D2Win_10008(MENU_DiscPromptWaitCallback);
	MENU_DestroySubChildren();
	return sgbDiscPromptRetry;
}

//D2Launch.0x6FA21FB0
int32_t __stdcall MENU_TcpIpCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gnGameType = MODE_TCPIP;
	MENU_ShowTcpIpMenu();
	return 1;
}

//D2Launch.0x6FA21FD0
int32_t __stdcall MENU_BattleNetCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gnGameType = MODE_CLOSED;
	MENU_ShowLoginMenu();
	return 1;
}

//D2Launch.0x6FA21FF0
int32_t __stdcall MENU_ShowGatewaySelectionCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_CreateBlankScreen();

	MENU_CreateChild(71);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(72), D2LANG_GetStringFromTblIndex(11055));
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(73), D2LANG_GetStringFromTblIndex(11056));
	sgpGatewayListTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(74);
	MENU_CreateChild(75);
	MENU_CreateChild(76);

	BNGatewayAccess* pGatewayAccess = gptComInt->GetBnGatewayAccess();
	const int32_t nCurrentGateway = pGatewayAccess->nCurrentGateway;
	for (int32_t i = 1; i <= pGatewayAccess->nGateways; ++i)
	{
		D2Win_10045(sgpGatewayListTextBox, BNGATEWAY_GetName(pGatewayAccess, i));
	}

	const int32_t nTopLine = D2Win_10054(sgpGatewayListTextBox);
	const int32_t nVisibleLines = D2Win_10055(sgpGatewayListTextBox);
	const int32_t nSelectedLine = nCurrentGateway - 1;
	if (nSelectedLine < nTopLine || nSelectedLine - nTopLine > nVisibleLines)
	{
		D2Win_10053(sgpGatewayListTextBox, nSelectedLine);
		D2Win_10050_TEXTBOX_SetLine(sgpGatewayListTextBox, 0);
	}
	else
	{
		D2Win_10050_TEXTBOX_SetLine(sgpGatewayListTextBox, nSelectedLine);
	}

	MENU_UpdateGatewayButton();
	return 1;
}

// Helper function, inlined in the original game
static BOOL MENU_CheckDoubleClick(SMSGHANDLER_PARAMS* pMsg)
{
	POINT pt;

	BOOL bDoubleClick = pMsg->nMessage == WM_LBUTTONDOWN;
	const DWORD dwTickCount = GetTickCount();
	if (dwTickCount - sgdwLastClickTickCount > 300)
	{
		bDoubleClick = FALSE;
	}

	GetCursorPos(&pt);
	if (std::abs(pt.x - sgnLastClickX) + std::abs(pt.y - sgnLastClickY) > 4)
	{
		bDoubleClick = FALSE;
	}

	sgnLastClickY = pt.y;
	sgdwLastClickTickCount = dwTickCount;
	sgnLastClickX = pt.x;
	return bDoubleClick;
}

//D2Launch.0x6FA22240
BOOL __fastcall MENU_IsDoubleClick(SMSGHANDLER_PARAMS* pMsg)
{
	return MENU_CheckDoubleClick(pMsg);
}

// Helper function, inlined in the original game
static void MENU_SelectGateway()
{
	BNGatewayAccess* pGatewayAccess = gptComInt->GetBnGatewayAccess();
	const int32_t nLine = D2Win_10049(sgpGatewayListTextBox);
	if (nLine != -1)
	{
		BNGATEWAY_SetCurGateway(pGatewayAccess, nLine + 1);
		SRegSaveString("Diablo II", "Preferred Realm", 0, BNGATEWAY_GetRealm(pGatewayAccess, nLine + 1));
	}

	MENU_DestroyChildren();
	MENU_ShowMainMenu();
}

//D2Launch.0x6FA222D0
int32_t __stdcall MENU_GatewayListClickCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (MENU_CheckDoubleClick(pMsg))
	{
		MENU_SelectGateway();
	}

	return 1;
}

//D2Launch.0x6FA224E0
int32_t __stdcall MENU_GatewayOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_SelectGateway();
	return 1;
}

//D2Launch.0x6FA22660
int32_t __stdcall MENU_GatewayCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroyChildren();
	MENU_PlayMenuMusic();
	MENU_ShowMainMenu();
	return 1;
}

//D2Launch.0x6FA227C0
void __fastcall MENU_UpdateGatewayButton()
{
	char szGatewayName[256];
	Unicode wszGatewayName[256];
	Unicode wszFormat[256];
	Unicode wszText[256];

	BNGatewayAccess* pGatewayAccess = gptComInt->GetBnGatewayAccess();
	SStrCopy(szGatewayName, BNGATEWAY_GetName(pGatewayAccess, pGatewayAccess->nCurrentGateway), sizeof(szGatewayName));
	Unicode::toUnicode(wszGatewayName, szGatewayName, std::size(wszGatewayName));
	Unicode::strcpy(wszFormat, D2LANG_GetStringFromTblIndex(11049));
	std::fill(std::begin(wszText), std::end(wszText), Unicode(0));
	Unicode::sprintf(std::size(wszText), wszText, wszFormat, wszGatewayName);

	for (int32_t i = 0; i < Unicode::strlen(wszText); ++i)
	{
		wszText[i] = wszText[i].toUpper();
	}

	BUTTON_SetText(sgpGatewayButton, D2FONT_FONTRIDICULOUS, wszText, 0);
}

//D2Launch.0x6FA22900
int32_t __stdcall MENU_ExitGameCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gnNextModule = 0;
	D2SOUND_10029(180);
	D2Win_10009();
	return 1;
}

// Helper function, inlined in the original game
static BOOL MENU_HasLocalCharacters()
{
	char szSavePath[1024];
	char szSearchPath[1024];
	WIN32_FIND_DATAA findData;

	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	sprintf(szSearchPath, "%s*.d2s", szSavePath);

	HANDLE hFind = FindFirstFileA(szSearchPath, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FindClose(hFind);
	return TRUE;
}

//D2Launch.0x6FA22930
int32_t __stdcall MENU_TcpIpHostGameCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gptParams->dwGameType = 8;
	strcpy(gptParams->szServerIP, FOG_GetHostIPAddress());
	gnGameType = MODE_TCPIP;
	gptParams->nArenaFlags = 4;

	if (MENU_HasLocalCharacters())
	{
		MENU_ShowCharacterSelection();
	}
	else
	{
		MENU_CreateCharacterCreationMenu();
	}

	return 1;
}

//D2Launch.0x6FA22B20
void __stdcall MENU_TcpIpJoinWaitCallback(DWORD dwUnused)
{
	uint8_t pPacket[512];

	if (CLIENT_DequeueSystemPacket(pPacket, sizeof(pPacket)) != -1)
	{
		if (pPacket[0] == 0xAE)
		{
			sgbTcpIpJoinAccepted = TRUE;
			D2Win_10009();
			return;
		}

		if (pPacket[0] == 0xAF)
		{
			sgbTcpIpJoinAccepted = FALSE;
		}
	}

	if (sgbTcpIpJoinAccepted || sgbWaitPopupCancelled)
	{
		D2Win_10009();
	}
}

//D2Launch.0x6FA22BA0
void __stdcall MENU_RealmListWaitCallback(DWORD dwUnused)
{
	D2Win_10009();
}

//D2Launch.0x6FA22BB0
int32_t __stdcall MENU_TcpIpJoinGameCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);
	CONTROL_Destroy(&sgpTcpIpTimer);

	D2Win_10033(MENU_CreateSubChild(271), 0);
	MENU_CreateSubChild(270);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateSubChild(268), D2LANG_GetStringFromTblIndex(11039));

	sgpTcpIpAddressEditBox = (D2WinEditBoxStrc*)MENU_CreateSubChild(269);
	if (!sgszLastTcpIp[0])
	{
		SRegLoadString("Diablo II", "LastTcpIp", 0, sgszLastTcpIp, sizeof(sgszLastTcpIp));
	}
	D2Win_10076(sgpTcpIpAddressEditBox, sgszLastTcpIp);
	D2Win_10012(sgpTcpIpAddressEditBox);
	D2Win_10082(sgpTcpIpAddressEditBox);

	D2Win_10031(MENU_CreateSubChild(272));
	MENU_CreateSubChild(273);
	return 1;
}

//D2Launch.0x6FA22E80
int32_t __stdcall MENU_TcpIpJoinGameCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroySubChildren();

	sgpTcpIpTimer = (D2WinTimerStrc*)MENU_CreateChild(267);
	D2Win_10180(sgpTcpIpTimer);
	D2Win_10182(sgpTcpIpTimer);
	return 1;
}

//D2Launch.0x6FA22F20
void __stdcall MENU_TcpIpConnectWaitCallback(DWORD dwUnused)
{
	const int32_t nResult = D2NET_10025();
	if (nResult == 0)
	{
		sgbTcpIpConnected = FALSE;
		D2Win_10009();
	}
	else if (nResult == 2)
	{
		sgbTcpIpConnected = TRUE;
		D2Win_10009();
	}
}

//D2Launch.0x6FA22F60
int32_t __stdcall MENU_TcpIpJoinGameOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	char szAddress[256];
	int32_t nIp[4];

	Unicode::toUtf(szAddress, D2Win_10077_EDITBOX_GetText(sgpTcpIpAddressEditBox), sizeof(szAddress));
	if (!szAddress[0])
	{
		return 1;
	}

	strncpy(sgszLastTcpIp, szAddress, sizeof(sgszLastTcpIp) - 1);
	sgszLastTcpIp[sizeof(sgszLastTcpIp) - 1] = 0;
	SRegSaveString("Diablo II", "LastTcpIp", 0, sgszLastTcpIp);

	if (sscanf(szAddress, "%d.%d.%d.%d", &nIp[0], &nIp[1], &nIp[2], &nIp[3]) != 4)
	{
		const char* szResolvedAddress = FOG_ResolveHostIPAddress(szAddress);
		if (!szResolvedAddress)
		{
			D2Win_10076(sgpTcpIpAddressEditBox, gszEmptyString);
			return 1;
		}

		strcpy(szAddress, szResolvedAddress);
	}

	strcpy(gptParams->szServerIP, szAddress);

	MENU_ShowWaitPopup();
	D2Win_10008(MENU_RealmListWaitCallback);

	sgbTcpIpConnected = FALSE;
	CLIENT_Initialize(0, szAddress);
	D2Win_10008(MENU_TcpIpConnectWaitCallback);
	if (!sgbTcpIpConnected)
	{
		CLIENT_Release();
		MENU_DestroySubChildren();
		MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5211), MENU_ShowTcpIpMenu, TRUE);
		return 1;
	}

	MENU_ShowWaitPopup();
	D2Win_10008(MENU_TcpIpJoinWaitCallback);
	CLIENT_Release();
	MENU_DestroySubChildren();

	if (sgbWaitPopupCancelled)
	{
		return 1;
	}

	gnGameType = MODE_TCPIP;
	gptParams->dwGameType = 9;
	gptParams->wJoinID = 1;
	MENU_ShowCharacterSelection();
	return 1;
}

// Helper function, inlined in the original game
static BOOL MENU_EnsureRealmLogon(const char* szRealmName)
{
	if (!D2MCPCLIENT_10002())
	{
		const int32_t nResult = MENU_LogonRealm(szRealmName, FALSE);
		if (nResult > 0 && nResult <= 2)
		{
			D2MCPClientCloseMCP();
			return FALSE;
		}
	}

	return TRUE;
}

//D2Launch.0x6FA23430
BOOL __fastcall MENU_DeleteRealmCharacter(D2CharSelNodeStrc* pNode, const char* szRealmName)
{
	if (!MENU_EnsureRealmLogon(szRealmName))
	{
		return FALSE;
	}

	MENU_ShowWaitPopup();
	gpfPopupCallback = MENU_CancelWaitPopup;
	D2MCPCLIENT_10021(pNode->szName, 0);
	D2Win_10008(MENU_WaitForCharacterDeletionCallback);
	return TRUE;
}

//D2Launch.0x6FA23660
BOOL __fastcall MENU_ConvertRealmCharacterToExpansion(D2CharSelNodeStrc* pNode, const char* szRealmName)
{
	if (!MENU_EnsureRealmLogon(szRealmName))
	{
		return FALSE;
	}

	MENU_ShowWaitPopup();
	gpfPopupCallback = MENU_CancelWaitPopup;
	D2MCPCLIENT_10062(pNode->szName);
	D2Win_10008(MENU_WaitForCharacterUpgradeCallback);
	return D2MCPCLIENT_10046() == 0;
}

// Helper function, inlined in the original game
static void MENU_SetCharacterArenaFlags(uint16_t nSaveFlags)
{
	gptParams->nArenaFlags = 4;
	if (nSaveFlags & LAUNCHSAVEFLAG_HARDCORE)
	{
		gptParams->nArenaFlags = 0x804;
	}

	if (gptParams->unpackedCTemp.nCharacterSaveFlags & LAUNCHSAVEFLAG_EXPANSION)
	{
		gptParams->nArenaFlags |= 0x100000;
	}
}

//D2Launch.0x6FA23890
BOOL __fastcall MENU_StartGameWithCharacter(D2CharSelNodeStrc* pNode, uint16_t nSaveFlags, uint8_t nClass, const char* szRealmName)
{
	Unicode wszName[256];
	Unicode wszMessage[256];

	const BOOL bRealmCharacter = szRealmName[0] != 0;
	strcpy(gptParams->szName, pNode->szName);
	strcpy(gptParams->szRealm, szRealmName);
	gptParams->unpackedCTemp.nCharacterSaveFlags = nSaveFlags;
	MENU_SetCharCreateClass(nClass);

	if ((gnGameType == MODE_CLOSED || gnGameType == MODE_OPEN) && !gptComInt->IsConnected())
	{
		MENU_CreateBlankScreen();
		if (!BNET_Connect())
		{
			return FALSE;
		}

		if (!BNET_Logon(gptParams, FALSE, FALSE))
		{
			return FALSE;
		}
	}

	if (gnGameType == MODE_LOCAL)
	{
		gptParams->nLaunchType = LAUNCHTYPE_LOCAL;
		gnNextModule = 1;
		gptParams->dwGameType = 0;
		MENU_SetCharacterArenaFlags(nSaveFlags);
		D2Win_10009();
		return TRUE;
	}

	if (gnGameType == MODE_TCPIP)
	{
		gptParams->nLaunchType = LAUNCHTYPE_TCPIP;
		gnNextModule = 1;
		MENU_SetCharacterArenaFlags(nSaveFlags);
		D2Win_10009();
		return TRUE;
	}

	if (bRealmCharacter)
	{
		switch (MENU_LogonRealm(szRealmName, FALSE))
		{
		case 1:
			return FALSE;

		case 2:
			MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5211), MENU_ShowCharacterSelection, TRUE);
			return TRUE;

		default:
			break;
		}

		if (D2MCPCLIENT_10046())
		{
			D2MCPClientCloseMCP();
			MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(D2MCPCLIENT_10046() == 0x47 ? 5212 : 5211), MENU_ShowCharacterSelection, TRUE);
			return TRUE;
		}

		D2MCPCLIENT_10009(gptParams->szName);
		MENU_ShowWaitPopup();
		D2Win_10008(MENU_WaitForCharacterLogonCallback);

		const int32_t nError = D2MCPCLIENT_10046();
		if (nError == 0x46 || !D2MCPCLIENT_10002())
		{
			MENU_DestroySubChildren();
			MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5133), MENU_ShowCharacterSelection, TRUE);
			return FALSE;
		}

		if (nError == 0x7B)
		{
			FOG_Trace("Character '%s' expired", gptParams->szName);
			Unicode::win2Unicode(wszName, gptParams->szName, std::size(wszName));
			D2MCPClientCloseMCP();
			Unicode::sprintf(std::size(wszMessage), wszMessage, D2LANG_GetStringFromTblIndex(10075), wszName);

			void* pPreviousFont = gaControlInits[224].field_28;
			gaControlInits[224].field_28 = &gaMenuFonts[3];
			MENU_ShowMessage(wszMessage, MENU_ShowCharacterSelection);
			gaControlInits[224].field_28 = pPreviousFont;
			return FALSE;
		}

		if (sgbWaitPopupCancelled)
		{
			MENU_DestroySubChildren();
			return FALSE;
		}

		gptParams->nLaunchType = LAUNCHTYPE_REALM;
	}
	else
	{
		gptParams->szCharacterRealm[0] = 0;
		gptParams->szRealm[0] = 0;
		gptParams->nLaunchType = LAUNCHTYPE_OPENBNET;
		MENU_SetCharacterArenaFlags(nSaveFlags);
	}

	gnNextModule = 3;
	MENU_ShowWaitPopup();
	D2Win_10008(MENU_RealmListWaitCallback);
	D2Win_10009();
	return TRUE;
}

//D2Launch.0x6FA24050
int32_t __stdcall MENU_CreateNewCharacterCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_CreateCharacterCreationMenu();
	return 1;
}

//D2Launch.0x6FA24060
int32_t __stdcall MENU_SkipLogoCallback(SMSGHANDLER_PARAMS* pMsg)
{
	char szResolution[8];
	char szVideoPath[260];

	if (D2Win_10003())
	{
		MENU_PumpMessagesIgnoringInput();

		int32_t nMode = 0;
		if (FOG_10191())
		{
			nMode = 2;
			strcpy(szResolution, "640x146");
		}
		else
		{
			strcpy(szResolution, "640x292");
		}

		MENU_BuildVideoPath(szVideoPath, "%s\\video\\%s\\d2intro%s.bik", szResolution);
		WINDOW_OpenSmackCutscene(szVideoPath, (D2GameResolutionMode)nMode, nullptr);
		MENU_ShowTitleScreen();
	}

	D2Win_10004(1);
	MENU_ShowTitleScreen();
	return 1;
}

//D2Launch.0x6FA24410
BOOL __fastcall MENU_FileExists(int32_t nUnused, const char* szPath)
{
	HANDLE hFile = nullptr;
	if (SFileOpenFileEx(nullptr, szPath, 0, &hFile))
	{
		SFileCloseFile(hFile);
		return TRUE;
	}

	return FALSE;
}

//D2Launch.0x6FA24440
int32_t __stdcall MENU_CharacterSelectionExitCallback(SMSGHANDLER_PARAMS* pMsg)
{
	BNET_Disconnect();
	MENU_ShowMainMenu();
	return 1;
}

//D2Launch.0x6FA24460
void __fastcall MENU_SetCharCreateClass(uint8_t nClass)
{
	gptParams->unpackedCTemp.nCharacterClassId = nClass;
	gptParams->bAmazon = 0;
	gptParams->bBarbarian = 0;
	gptParams->bNecromancer = 0;
	gptParams->bPaladin = 0;
	gptParams->bSorceress = 0;
	gptParams->bDruid = 0;
	gptParams->bAssassin = 0;

	switch (nClass)
	{
	case CHARCLASS_AMAZON:
		gptParams->bAmazon = 1;
		break;

	case CHARCLASS_BARBARIAN:
		gptParams->bBarbarian = 1;
		break;

	case CHARCLASS_NECROMANCER:
		gptParams->bNecromancer = 1;
		break;

	case CHARCLASS_PALADIN:
		gptParams->bPaladin = 1;
		break;

	case CHARCLASS_SORCERESS:
		gptParams->bSorceress = 1;
		break;

	case CHARCLASS_DRUID:
		gptParams->bDruid = 1;
		break;

	case CHARCLASS_ASSASSIN:
		gptParams->bAssassin = 1;
		break;

	default:
		break;
	}
}

// Helper function, inlined in the original game
static void MENU_SetOpenCharacterInfo()
{
	static const uint8_t gaDefaultComponents[16] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 };

	gptParams->nCharacterLevel = 1;
	SMemCopy(gptParams->nComponents, gaDefaultComponents, sizeof(gptParams->nComponents));
	SMemZero(gptParams->nComponentsColors, sizeof(gptParams->nComponentsColors));
	gptParams->bLadder = (gptParams->unpackedCTemp.nCharacterSaveFlags >> 6) & 1;
	gptParams->nSaveFlags = gptParams->unpackedCTemp.nCharacterSaveFlags;
}

//D2Launch.0x6FA24550
void __fastcall MENU_ValidateCharacterCreation()
{
	char szSavePath[1024];
	char szName[256];
	char szCharacterName[256];
	char szFileName[260];

	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	Unicode::toUtf(szName, D2Win_10077_EDITBOX_GetText(sgpCharNameEditBox), sizeof(szName));
	sprintf(szCharacterName, "%s", szName);
	sprintf(szFileName, "%s%s.d2s", szSavePath, szCharacterName);

	HANDLE hFile = FOG_CreateFileA(szFileName, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		FOG_CloseFile(hFile);
		if (gnGameType != MODE_CLOSED)
		{
			const Unicode* wszMessage = D2LANG_GetStringFromTblIndex(5165);
			MENU_DestroySubChildren();

			D2WinControlStrc* pBackground = MENU_CreateSubChild(247);
			D2Win_10033(pBackground, 1);
			D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
			D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(250), 1);
			D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(249);
			D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
			MENU_AddTextBoxLines(pMessage, wszMessage, 0, 0);

			gpfPopupCallback = MENU_DestroySubChildren;
			return;
		}
	}

	if (gptParams->unpackedCTemp.nCharacterClassId == CHARCLASS_ASSASSIN || gptParams->unpackedCTemp.nCharacterClassId == CHARCLASS_DRUID)
	{
		gptParams->unpackedCTemp.nCharacterSaveFlags |= LAUNCHSAVEFLAG_EXPANSION;
	}

	Unicode::toUtf(szName, D2Win_10077_EDITBOX_GetText(sgpCharNameEditBox), sizeof(szName));
	sprintf(gptParams->szName, "%s", szName);
	gptParams->szRealm[0] = 0;

	if (gptParams->unpackedCTemp.nCharacterSaveFlags & LAUNCHSAVEFLAG_EXPANSION)
	{
		sgbCreatedExpansionCharacter = TRUE;
	}

	if (gptParams->unpackedCTemp.nCharacterSaveFlags & LAUNCHSAVEFLAG_HARDCORE)
	{
		MENU_DestroySubChildren();
		MENU_CreatePopupSubChild(205, TRUE);
		MENU_CreatePopupSubChild(206, FALSE);
		MENU_CreatePopupSubChild(207, FALSE);
		D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(208);
		D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
		D2Win_10051(pMessage, D2LANG_GetStringFromTblIndex(5303), 0, 0, 0);
		return;
	}

	switch (gnGameType)
	{
	case MODE_LOCAL:
		MENU_DestroyChildren();
		SAVE_CreateCharacter(gptParams->szName, gptParams->unpackedCTemp.nCharacterClassId, &gptParams->tCharPreviewInfo, gptParams->unpackedCTemp.nCharacterSaveFlags);
		SAVE_WriteCharacterFile(gptParams->szName);
		gptParams->nLaunchType = LAUNCHTYPE_LOCAL;
		gptParams->dwGameType = 0;
		gnNextModule = 1;
		break;

	case MODE_TCPIP:
		MENU_DestroyChildren();
		SAVE_SetRealmCharacter(FALSE);
		SAVE_CreateCharacter(gptParams->szName, gptParams->unpackedCTemp.nCharacterClassId, &gptParams->tCharPreviewInfo, gptParams->unpackedCTemp.nCharacterSaveFlags);
		SAVE_WriteCharacterFile(gptParams->szName);
		gptParams->nLaunchType = LAUNCHTYPE_TCPIP;
		gnNextModule = 1;
		break;

	case MODE_OPEN:
		MENU_DestroyChildren();
		D2MCPClientCloseMCP();
		SAVE_SetRealmCharacter(FALSE);
		SAVE_CreateCharacter(gptParams->szName, gptParams->unpackedCTemp.nCharacterClassId, &gptParams->tCharPreviewInfo, gptParams->unpackedCTemp.nCharacterSaveFlags);
		SAVE_WriteCharacterFile(gptParams->szName);
		MENU_SetOpenCharacterInfo();
		gptParams->nLaunchType = LAUNCHTYPE_OPENBNET;
		gptParams->szCharacterRealm[0] = 0;
		gptParams->szRealm[0] = 0;
		gnNextModule = 3;
		break;

	case MODE_CLOSED:
		MENU_CreateRealmCharacter();
		return;

	default:
		return;
	}

	MENU_SetCharacterArenaFlags(gptParams->unpackedCTemp.nCharacterSaveFlags);
	D2Win_10009();
}

// Helper function, inlined in the original game
static void MENU_ShowRealmErrorMessage(int32_t nError)
{
	if (nError == 2)
	{
		MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5211), MENU_ShowCharacterSelection, TRUE);
	}
	else if (nError >= 10 && nError <= 12)
	{
		MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5213), MENU_CreateCharacterCreationMenu, TRUE);
	}
	else
	{
		MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5212), MENU_ShowCharacterSelection, TRUE);
	}
}

//D2Launch.0x6FA24D50
void __fastcall MENU_CreateRealmCharacter()
{
	char szName[100];
	Unicode wszName[256];
	Unicode wszMessage[256];

	const int32_t nResult = MENU_LogonRealm(CHARSEL_GetPreferredRealmName(), FALSE);
	if (nResult > 0 && nResult <= 2)
	{
		MENU_CreateCharacterCreationMenu();
		return;
	}

	if (D2MCPCLIENT_10046() || !D2MCPCLIENT_10002())
	{
		D2MCPClientCloseMCP();
		MENU_ShowRealmErrorMessage(D2MCPCLIENT_10046());
		return;
	}

	FOG_Trace("Authorized by Shard");

	if (!D2MCPCLIENT_10002())
	{
		D2Win_10009();
		return;
	}

	FOG_Trace("Send Create Character to Shard");
	MENU_SetOpenCharacterInfo();
	D2MCPCLIENT_10008(gptParams->szName, gptParams->unpackedCTemp.nCharacterClassId, gptParams->unpackedCTemp.nCharacterSaveFlags);

	MENU_ShowWaitPopup();
	D2Win_10008(MENU_WaitForCharacterCreationCallback);

	if (sgbWaitPopupCancelled)
	{
		MENU_DestroySubChildren();
		return;
	}

	const int32_t nError = D2MCPCLIENT_10046();
	if (!nError)
	{
		FOG_Trace("Created Character '%s'", gptParams->szName);
		SAVE_SetRealmCharacter(TRUE);
		SStrCopy(gptParams->szRealm, CHARSEL_GetPreferredRealmName(), 0x7FFFFFFF);
		gptParams->unpackedCTemp.nCharacterSaveFlags |= LAUNCHSAVEFLAG_NEWBIE_REALM;
		gptParams->nLaunchType = LAUNCHTYPE_REALM;
		gnNextModule = 3;
		D2Win_10009();
		return;
	}

	if (nError == 0x14)
	{
		FOG_Trace("Character '%s' already exists in Realm", gptParams->szName);
		D2MCPClientCloseMCP();
		Unicode::win2Unicode(wszName, gptParams->szName, std::size(wszName));
		Unicode::sprintf(std::size(wszMessage), wszMessage, D2LANG_GetStringFromTblIndex(11059), wszName);
		MENU_ShowMessage(wszMessage, MENU_CreateCharacterCreationMenu);
		return;
	}

	Unicode wszCharacterName[100];
	FOG_Trace("Error from MCP trying to create '%s' (err=%d)", gptParams->szName, D2MCPCLIENT_10046());
	D2MCPClientCloseMCP();

	Unicode wszErrorMessage[255];
	Unicode::strcpy(wszErrorMessage, D2LANG_GetStringFromTblIndex(5214));
	Unicode wszErrorSuffix[255];
	Unicode::strcpy(wszErrorSuffix, D2LANG_GetStringFromTblIndex(5215));
	sprintf(szName, "%s", gptParams->szName);
	Unicode::toUnicode(wszCharacterName, szName, std::size(wszCharacterName));
	Unicode::strcat(wszErrorMessage, wszCharacterName);
	Unicode::strcat(wszErrorMessage, wszErrorSuffix);
	MENU_ShowMessage(wszErrorMessage, MENU_CreateCharacterCreationMenu);
}

//D2Launch.0x6FA25430
int32_t __stdcall MENU_PopupButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (gpfPopupCallback)
	{
		gpfPopupCallback();
	}

	return 1;
}

// Helper function, inlined in the original game
static void MENU_StoreAccountCredentials(D2WinEditBoxStrc* pPasswordEditBox)
{
	if (sgpAccountNameEditBox)
	{
		Unicode::unicode2Win(gptParams->szAccountName, D2Win_10077_EDITBOX_GetText(sgpAccountNameEditBox), 256);
	}

	if (pPasswordEditBox)
	{
		Unicode::unicode2Win(gptParams->szAccountPassword, D2Win_10077_EDITBOX_GetText(pPasswordEditBox), 256);
		gptParams->nAccountPasswordHash = SHashString(gptParams->szAccountPassword);
		gptParams->nAccountPasswordLength = SStrLen(gptParams->szAccountPassword);
	}
}

//D2Launch.0x6FA25450
int32_t __stdcall MENU_CreateNewAccountCallback(SMSGHANDLER_PARAMS* pMsg)
{
	char szSavePath[1024];

	MENU_StoreAccountCredentials(sgpPasswordEditBox);

	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	for (int32_t i = 0; i < sizeof(szSavePath); ++i)
	{
		if (szSavePath[i] == '\\')
		{
			szSavePath[i + 1] = 0;
			break;
		}
	}

	DWORD dwSectorsPerCluster = 0;
	DWORD dwBytesPerSector = 0;
	DWORD dwNumberOfFreeClusters = 0;
	DWORD dwTotalNumberOfClusters = 0;
	GetDiskFreeSpaceA(szSavePath, &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);
	if (dwNumberOfFreeClusters * dwBytesPerSector * dwSectorsPerCluster < 5000)
	{
		MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5149), MENU_ShowCharacterSelection);
		return 1;
	}

	return MENU_ShowTermsOfService();
}

//D2Launch.0x6FA257B0
void __fastcall MENU_CreateChangePasswordMenu()
{
	MENU_CreateBlankScreen();

	MENU_CreateChild(21);
	MENU_CreateChild(22);
	MENU_CreateChild(24);
	MENU_CreateChild(25);
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(26), D2LANG_GetStringFromTblIndex(5224));
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(27), D2LANG_GetStringFromTblIndex(11052));
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(29), D2LANG_GetStringFromTblIndex(11053));
	D2Win_10044((D2WinTextBoxStrc*)MENU_CreateChild(30), D2LANG_GetStringFromTblIndex(11054));
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(FOG_IsExpansion() ? 33 : 31), D2LANG_GetStringFromTblIndex(11051), 0, 0, 0);

	sgpAccountNameEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(89);
	D2Win_10072(sgpAccountNameEditBox, MENU_CreateAccountNameCharFilter);
	D2Win_10081(sgpAccountNameEditBox, 16);
	D2Win_10076(sgpAccountNameEditBox, gptParams->szAccountName);

	sgpPasswordEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(90);
	D2Win_10072(sgpPasswordEditBox, MENU_PasswordCharFilter);
	D2Win_10081(sgpPasswordEditBox, 13);

	sgpNewPasswordEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(91);
	D2Win_10081(sgpNewPasswordEditBox, 13);

	sgpConfirmPasswordEditBox = (D2WinEditBoxStrc*)MENU_CreateChild(92);
	D2Win_10081(sgpConfirmPasswordEditBox, 13);

	if (gptParams->szAccountName[0])
	{
		D2Win_10012(sgpPasswordEditBox);
	}
	else
	{
		D2Win_10012(sgpAccountNameEditBox);
	}

	D2Win_10080_EDITBOX_SetNextEditBox(sgpAccountNameEditBox, sgpPasswordEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpPasswordEditBox, sgpNewPasswordEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpNewPasswordEditBox, sgpConfirmPasswordEditBox);
	D2Win_10080_EDITBOX_SetNextEditBox(sgpConfirmPasswordEditBox, sgpAccountNameEditBox);

	MENU_CreateChild(93);
	MENU_CreateChild(94);
}

//D2Launch.0x6FA25C80
int32_t __stdcall MENU_AccountOptionsCallback(SMSGHANDLER_PARAMS* pMsg)
{
	Unicode::unicode2Win(gptParams->szAccountName, D2Win_10077_EDITBOX_GetText(sgpAccountNameEditBox), 256);
	BNET_CreateAccountOptionsMenu();
	return 1;
}

// Helper function, inlined in the original game
static void MENU_ShowCharacterSelectionOrCreation()
{
	if (MENU_HasLocalCharacters())
	{
		MENU_ShowCharacterSelection();
	}
	else
	{
		MENU_CreateCharacterCreationMenu();
	}
}

//D2Launch.0x6FA25CC0
int32_t __stdcall MENU_LoginOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!pMsg)
	{
		MENU_ShowMainMenu();
		return 1;
	}

	if (!D2Win_10024_CONTROL_CheckFirstFlag(&sgpLoginOkButton->controlHeader))
	{
		return 0;
	}

	MENU_StoreAccountCredentials(sgpPasswordEditBox);

	if (BNET_Logon(gptParams, FALSE, FALSE))
	{
		SRegSaveString("Diablo II", "Last BNet", 0, gptParams->szAccountName);
		if (gnGameType == MODE_CLOSED)
		{
			MENU_ShowCharacterSelection();
		}
		else
		{
			MENU_ShowCharacterSelectionOrCreation();
		}
	}

	return 1;
}

//D2Launch.0x6FA26090
int32_t __stdcall MENU_BackToMainMenuCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_ShowMainMenu();
	return 1;
}

// Helper function, inlined in the original game
static int32_t MENU_GetAccountErrorStringId(const Unicode* wszPassword, const Unicode* wszConfirmPassword)
{
	if (Unicode::stricmp(wszPassword, wszConfirmPassword) != 0)
	{
		return 5218;
	}

	const int32_t nPasswordLength = Unicode::strlen(wszPassword);
	if (nPasswordLength < 2)
	{
		return 5219;
	}

	if (nPasswordLength > 20)
	{
		return 5220;
	}

	return 0;
}

//D2Launch.0x6FA260A0
int32_t __stdcall MENU_CreateAccountOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!pMsg)
	{
		MENU_ShowLoginMenu();
		return 1;
	}

	MENU_StoreAccountCredentials(sgpPasswordEditBox);

	const Unicode* wszAccountName = D2Win_10077_EDITBOX_GetText(sgpAccountNameEditBox);
	const Unicode* wszPassword = D2Win_10077_EDITBOX_GetText(sgpPasswordEditBox);
	const Unicode* wszConfirmPassword = D2Win_10077_EDITBOX_GetText(sgpConfirmPasswordEditBox);

	const int32_t nAccountNameLength = Unicode::strlen(wszAccountName);
	if (nAccountNameLength < 2)
	{
		MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(5216), MENU_ShowCreateAccountMenu, TRUE);
		return 1;
	}

	int32_t nErrorStringId = 0;
	if (nAccountNameLength > 15)
	{
		nErrorStringId = 5217;
	}
	else
	{
		nErrorStringId = MENU_GetAccountErrorStringId(wszPassword, wszConfirmPassword);
	}

	if (nErrorStringId)
	{
		MENU_ShowMessage(D2LANG_GetStringFromTblIndex(nErrorStringId), MENU_ShowCreateAccountMenu);
		return 1;
	}

	MENU_CreateAccountInfoBackground();
	MENU_CreateSubChild(77);
	MENU_CreateSubChild(99);
	MENU_CreateSubChild(100);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateSubChild(95), D2LANG_GetStringFromTblIndex(5227), 0, 0, 0);

	D2WinTextBoxStrc* pTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(96);
	const Font nPreviousFont = D2Win_10127_SetFont(D2FONT_FONTFORMAL12);
	const int32_t nFontHeight = D2Win_10125();
	D2Win_10127_SetFont(nPreviousFont);
	D2Win_10051(pTextBox, D2LANG_GetStringFromTblIndex(5228), 0, 0, 0);
	const int32_t nLineOffset = nFontHeight / -10;
	D2Win_10062(pTextBox, nLineOffset, 0);

	pTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(97);
	D2Win_10051(pTextBox, D2LANG_GetStringFromTblIndex(5229), 0, 0, 0);
	D2Win_10062(pTextBox, nLineOffset, 0);

	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateSubChild(98), D2LANG_GetStringFromTblIndex(11127), 0, 0, 0);
	return 1;
}

//D2Launch.0x6FA26390
void __fastcall MENU_CreateAccountInfoBackground()
{
	MENU_DestroyChildren();

	ANIMIMAGE_SetIsRunning((D2WinAnimImageStrc*)MENU_CreateChild(6), 0);
	ANIMIMAGE_SetIsRunning((D2WinAnimImageStrc*)MENU_CreateChild(7), 0);
	MENU_CreateChild(8);
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);
}

//D2Launch.0x6FA26640
int32_t __stdcall MENU_ChangePasswordOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!pMsg)
	{
		BNET_CreateAccountOptionsMenu();
		return 1;
	}

	MENU_StoreAccountCredentials(sgpNewPasswordEditBox);

	const Unicode* wszAccountName = D2Win_10077_EDITBOX_GetText(sgpAccountNameEditBox);
	const Unicode* wszOldPassword = D2Win_10077_EDITBOX_GetText(sgpPasswordEditBox);
	const Unicode* wszNewPassword = D2Win_10077_EDITBOX_GetText(sgpNewPasswordEditBox);
	const Unicode* wszConfirmPassword = D2Win_10077_EDITBOX_GetText(sgpConfirmPasswordEditBox);
	Unicode::unicode2Win(gszOldAccountPassword, wszOldPassword, 256);

	const int32_t nAccountNameLength = Unicode::strlen(wszAccountName);
	if (nAccountNameLength < 2 || nAccountNameLength > 15)
	{
		MENU_ShowMessageWithButton(D2LANG_GetStringFromTblIndex(nAccountNameLength < 2 ? 5216 : 5217), MENU_CreateChangePasswordMenu, TRUE);
		return 1;
	}

	if (const int32_t nErrorStringId = MENU_GetAccountErrorStringId(wszNewPassword, wszConfirmPassword))
	{
		MENU_ShowMessage(D2LANG_GetStringFromTblIndex(nErrorStringId), MENU_CreateChangePasswordMenu);
		return 1;
	}

	gbBnetConnectionCancelled = FALSE;
	if (!BNET_Logon(gptParams, FALSE, TRUE))
	{
		if (gbBnetConnectionCancelled)
		{
			MENU_CreateChangePasswordMenu();
		}

		return 1;
	}

	SRegSaveString("Diablo II", "Last BNet", 0, gptParams->szAccountName);
	MENU_DestroySubChildren();
	MENU_ShowCharacterSelection();
	return 1;
}

// Helper function, inlined in the original game
static int32_t MENU_GetRealmLogonState()
{
	HANDLE hEvent = D2MCPCLIENT_10055();
	if (!hEvent)
	{
		return 2;
	}

	switch (WaitForSingleObject(D2MCPCLIENT_10055(), 0))
	{
	case WAIT_OBJECT_0:
		return 0;

	case WAIT_TIMEOUT:
		return 3;

	default:
		return 2;
	}
}

//D2Launch.0x6FA26A20
int32_t __fastcall MENU_GetLogonRealmStatus()
{
	if (sgbRealmLogonCancelled)
	{
		return 1;
	}

	return MENU_GetRealmLogonState();
}

//D2Launch.0x6FA26A70
int32_t __fastcall MENU_LogonRealm(const char* szRealmName, BOOL bAsync)
{
	if (szRealmName[0] && gptParams->szCharacterRealm[0] && !strcmp(szRealmName, gptParams->szCharacterRealm) && D2MCPCLIENT_10002())
	{
		return 0;
	}

	if (!bAsync)
	{
		MENU_ShowWaitPopup();
	}

	D2MCPClientCloseMCP();
	sgbRealmLogonCancelled = FALSE;

	if (!szRealmName[0])
	{
		gptParams->szCharacterRealm[0] = 0;
		gptParams->szRealm[0] = 0;
		if (!bAsync)
		{
			MENU_DestroySubChildren();
		}

		return 0;
	}

	RealmLogonInformation* pRealmLogon = nullptr;
	if (gptComInt)
	{
		pRealmLogon = gptComInt->LogonRealm(szRealmName, "password");
	}

	if (!pRealmLogon || pRealmLogon->nSize == 8)
	{
		if (!bAsync)
		{
			MENU_DestroySubChildren();
		}

		return 2;
	}

	SStrCopy(gptParams->szCharacterRealm, szRealmName, 256);
	SStrCopy(gptParams->szRealm, szRealmName, 256);
	D2MCPCLIENT_10000(&pRealmLogon->tPacket);

	int32_t nResult = 3;
	if (!bAsync)
	{
		D2Win_10008(MENU_LogonRealmWaitCallback);
		if (sgbRealmLogonCancelled)
		{
			nResult = 1;
		}
		else
		{
			nResult = MENU_GetRealmLogonState();
		}

		MENU_DestroySubChildren();
	}

	return nResult;
}

//D2Launch.0x6FA26D80
void __stdcall MENU_LogonRealmWaitCallback(DWORD dwUnused)
{
	if (sgbWaitPopupCancelled)
	{
		sgbRealmLogonCancelled = TRUE;
		D2Win_10009();
		return;
	}

	if (!sgbRealmLogonCancelled && D2MCPCLIENT_10055() && MENU_GetRealmLogonState() == 3)
	{
		return;
	}

	D2Win_10009();
}

//D2Launch.0x6FA26DE0
int32_t __stdcall MENU_CreateAccountInfoOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gbBnetConnectionCancelled = FALSE;
	if (!BNET_Logon(gptParams, TRUE, FALSE))
	{
		if (gbBnetConnectionCancelled)
		{
			MENU_ShowLoginMenu();
		}

		return 1;
	}

	SRegSaveString("Diablo II", "Last BNet", 0, gptParams->szAccountName);
	MENU_ShowCharacterSelectionOrCreation();
	return 1;
}

//D2Launch.0x6FA26FE0
int32_t __stdcall MENU_CreateAccountInfoCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroySubChildren();
	MENU_ShowLoginMenu();
	return 1;
}

//D2Launch.0x6FA27020
void __fastcall MENU_LoadCharacterCreationCellFiles()
{
	if (sgpCharacterCreateCellFile)
	{
		return;
	}

	sgpMediumSelButtonBlankCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\MediumSelButtonBlank");
	sgpCharacterCreateCellFile = MENU_LoadCellFile(FOG_IsExpansion() ? "%s\\ui\\FrontEnd\\charactercreationscreenEXP" : "%s\\ui\\FrontEnd\\CharacterCreate");
	sgpFireCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\fire");
	sgpCharCreateTextBoxCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\textbox");
	sgpClickBoxCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\clickbox");

	if (FOG_IsExpansion())
	{
		sgpJoinGameClickBoxGreyCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\joingameclickboxgrey");

		sgpAssassinAnimCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\assassin\\asnu1");
		sgpAssassinAnimCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\assassin\\asnu2");
		sgpAssassinAnimCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\assassin\\asfw");
		sgpAssassinAnimCellFiles[3] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\assassin\\asnu3");
		sgpAssassinAnimCellFiles[4] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\assassin\\asbw");

		sgpDruidAnimCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\druid\\dznu1");
		sgpDruidAnimCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\druid\\dznu2");
		sgpDruidAnimCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\druid\\dzfw");
		sgpDruidAnimCellFiles[3] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\druid\\dznu3");
		sgpDruidAnimCellFiles[4] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\druid\\dzbw");
	}

	sgpAmazonAnimCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\amazon\\amnu1");
	sgpAmazonAnimCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\amazon\\amnu2");
	sgpAmazonAnimCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\amazon\\amfw");
	sgpAmazonAnimCellFiles[3] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\amazon\\amnu3");
	sgpAmazonAnimCellFiles[4] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\amazon\\ambw");

	sgpNecromancerAnimCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\necromancer\\nenu1");
	sgpNecromancerAnimCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\necromancer\\nenu2");
	sgpNecromancerAnimCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\necromancer\\nefw");
	sgpNecromancerAnimCellFiles[3] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\necromancer\\nenu3");
	sgpNecromancerAnimCellFiles[4] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\necromancer\\nebw");

	sgpBarbarianAnimCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\barbarian\\banu1");
	sgpBarbarianAnimCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\barbarian\\banu2");
	sgpBarbarianAnimCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\barbarian\\bafw");
	sgpBarbarianAnimCellFiles[3] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\barbarian\\banu3");
	sgpBarbarianAnimCellFiles[4] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\barbarian\\babw");

	sgpSorceressAnimCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\sorceress\\sonu1");
	sgpSorceressAnimCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\sorceress\\sonu2");
	sgpSorceressAnimCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\sorceress\\sofw");
	sgpSorceressAnimCellFiles[3] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\sorceress\\sonu3");
	sgpSorceressAnimCellFiles[4] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\sorceress\\sobw");

	sgpPaladinAnimCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\paladin\\panu1");
	sgpPaladinAnimCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\paladin\\panu2");
	sgpPaladinAnimCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\paladin\\pafw");
	sgpPaladinAnimCellFiles[3] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\paladin\\panu3");
	sgpPaladinAnimCellFiles[4] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\paladin\\pabw");

	sgpSorceressOverlayCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\sorceress\\sofws");
	sgpSorceressOverlayCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\sorceress\\sonu3s");
	sgpSorceressOverlayCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\sorceress\\sobws");

	sgpNecromancerOverlayCellFiles[0] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\necromancer\\nefws");
	sgpNecromancerOverlayCellFiles[1] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\necromancer\\nenu3s");
	sgpNecromancerOverlayCellFiles[2] = MENU_LoadCellFile("%s\\ui\\FrontEnd\\necromancer\\nebws");

	sgpBarbarianOverlayCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\barbarian\\bafws");
	sgpPaladinOverlayCellFile = MENU_LoadCellFile("%s\\ui\\FrontEnd\\paladin\\pafws");
}

//D2Launch.0x6FA27750
int32_t __stdcall MENU_CloseSubChildrenCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroySubChildren();
	return 1;
}

//D2Launch.0x6FA27790
void __fastcall MENU_ShowClassicMessageWithButton(const Unicode* wszMessage, D2PopupCallback pfCallback, BOOL bOkButton)
{
	MENU_DestroySubChildren();

	D2WinControlStrc* pBackground = MENU_CreateSubChild(222);
	D2Win_10033(pBackground, 1);
	D2WinControlStrc* pButton = MENU_CreateSubChild(bOkButton ? 225 : 223);
	D2WinTextBoxStrc* pMessage = (D2WinTextBoxStrc*)MENU_CreateSubChild(224);

	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(pButton, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pMessage->controlHeader, 1);
	MENU_AddTextBoxLines(pMessage, wszMessage, 0, 0);

	gpfPopupCallback = pfCallback;
}

//D2Launch.0x6FA27940
void __fastcall MENU_ApplyLanguageLayout()
{
	if (STRTABLE_GetLanguage() != LANGUAGE_CHINESETWN)
	{
		return;
	}

	gaControlInits[81].nY = 155;
	gaControlInits[26].nY = 334;
	gaControlInits[27].nY = 388;
	gaControlInits[28].nY = 442;
	gaControlInits[31].nY = 240;
	gaControlInits[32].nY = 344;
	gaControlInits[95].nY = 156;
	gaControlInits[201].nY = 506;
	gaControlInits[202].nY = 555;
	gaControlInits[189].nY = 575;
	gaControlInits[211].nY = 555;
	gaControlInits[191].nY = 555;
	gaControlInits[193].nY = 575;
	gaControlInits[195].nY = 595;
	gaControlInits[259].nY = 70;
	gaControlInits[268].nY = 238;
}

//D2Launch.0x6FA280F0
void __fastcall MENU_CreateBlankScreen()
{
	MENU_DestroyChildren();

	MENU_CreateChild(8);
	MENU_CreateChild(6);
	MENU_CreateChild(7);
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);
	MENU_ApplyLanguageLayout();
}
