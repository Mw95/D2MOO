// Safesock.h includes Winsock2.h, which must be included before Windows.h
#include <Safesock.h>

#include "Gate.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <D2Lang.h>
#include <D2Unicode.h>
#include <D2MCPClient.h>
#include <Fog.h>
#include <Storm.h>
#include <D2WinButton.h>
#include <D2WinEditBox.h>
#include <D2WinMain.h>
#include <D2WinTextBox.h>

#include "ChatDlg.h"


#define GATE_REGISTRY_KEY "Diablo II"
#define GATE_REGISTRY_LEVEL_RESTRICTION "LVL_REST"
#define GATE_REGISTRY_MAX_PLAYERS "MAX_PLAYER"
#define GATE_REGISTRY_DIFFICULTY "DIFF_LEVEL"

// Value saved in the registry when the level difference isn't restricted
#define GATE_NO_LEVEL_RESTRICTION 666

// Marker used to add an empty line to the help text
#define HELP_BLANK_LINE 0xFFFF

enum D2MultiProfileMode
{
	PROFILEMODE_NONE = 0,
	PROFILEMODE_VIEW = 1,
	PROFILEMODE_EDIT = 2,
};

#pragma pack(push, 1)
// Game list request sent to the MCP
struct D2MultiGameListFilterStrc
{
	uint32_t unk0x00[5];						//0x00
	uint32_t dwFlags;							//0x14
};

// Game, as returned by BnClient's GetGamesList
struct D2MultiBnGameStrc
{
	uint32_t unk0x00[3];						//0x00
	uint32_t nIpAddress;						//0x0C
	uint32_t unk0x10[4];						//0x10
	char szGameName[1];							//0x20 Followed by the game password and statstring (difficulty character followed by the description)
};
#pragma pack(pop)


// Help text, shown only when entering the chat
static const uint16_t gaHelpChatStringIds[] =
{
	0x2AF, 0x2B0, HELP_BLANK_LINE, 0x2B1, HELP_BLANK_LINE, 0x2B2, HELP_BLANK_LINE, 0x2B3,
	HELP_BLANK_LINE, 0x2B4, HELP_BLANK_LINE, 0x2B5, HELP_BLANK_LINE, 0x2B6, 0x2B7, HELP_BLANK_LINE,
	0x2B8, 0x2B34, 0x2B9, 0x2BA, 0x2BB, 0x2B35, 0x2BD, HELP_BLANK_LINE,
};

// Help text, always shown
static const uint16_t gaHelpCommonStringIds[] =
{
	0x2BE, 0x2BF, HELP_BLANK_LINE, 0x2C0, 0x2C1, HELP_BLANK_LINE, 0x2C2, HELP_BLANK_LINE,
	0x2C3, HELP_BLANK_LINE, 0x2C4, HELP_BLANK_LINE, 0x2C5, HELP_BLANK_LINE, 0x2C6, 0x2C7,
	HELP_BLANK_LINE, 0x2C8, HELP_BLANK_LINE, 0x2C9, 0x2CA, 0x2CB, HELP_BLANK_LINE, 0x2CC,
	0x2CD, 0x2CE, HELP_BLANK_LINE, 0x2CF, 0x2D0, HELP_BLANK_LINE, 0x2D1, HELP_BLANK_LINE,
	0x2D2, HELP_BLANK_LINE, 0x276C, HELP_BLANK_LINE, 0x276D, HELP_BLANK_LINE, 0x2D3, HELP_BLANK_LINE,
};

// Help text of the chat commands, shown only when entering the chat
static const uint16_t gaHelpCommandsStringIds[] =
{
	0x2D4, 0x2B26, HELP_BLANK_LINE, 0x2B27, HELP_BLANK_LINE, 0x2B28, HELP_BLANK_LINE, 0x2714,
	0x2715, 0x2DA, HELP_BLANK_LINE, 0x2B21, 0x2B22, HELP_BLANK_LINE, 0x2DB, 0x2DC,
	HELP_BLANK_LINE, 0x2716, 0x2717, 0x2DF, HELP_BLANK_LINE, 0x2718, 0x2719, 0x2E2,
	HELP_BLANK_LINE, 0x2E3, 0x2E4, HELP_BLANK_LINE, 0x2E5, 0x2E6, HELP_BLANK_LINE, 0x2E7,
	0x2E8, HELP_BLANK_LINE, 0x2E9, 0x2EA, HELP_BLANK_LINE, 0x271A, 0x2EC, HELP_BLANK_LINE,
	0x2ED, 0x2EE, HELP_BLANK_LINE, 0x271B, 0x2F0, HELP_BLANK_LINE, 0x271C, 0x2F2,
	HELP_BLANK_LINE, 0x2F3, 0x2F4, HELP_BLANK_LINE, 0x271D, 0x271E, 0x2F7, HELP_BLANK_LINE,
	0x2F8, 0x2F9, HELP_BLANK_LINE, 0x2FA, 0x2FB, HELP_BLANK_LINE, 0x2FC, 0x2FD,
	HELP_BLANK_LINE, 0x2FE, 0x2FF, HELP_BLANK_LINE, 0x300, 0x301, HELP_BLANK_LINE, 0x271F,
	0x303, HELP_BLANK_LINE, 0x304, HELP_BLANK_LINE, 0x305, HELP_BLANK_LINE, 0x306, HELP_BLANK_LINE,
	0x307, 0x2B23, 0x309, 0x30A, 0x30B, 0x30C, 0x30D, 0x30E,
	0x30F, 0x310, 0x311, 0x312, 0x313, HELP_BLANK_LINE,
};

// Note: the original game only allocates 2 bytes for each of these strings
char gszLevelDifference_6F9BEA90[4] = "4";
char gszMaxPlayers_6F9BEA92[4] = "4";
int32_t gnGameInfoRequestId_6F9BEA94 = -1;
int32_t gnLastGameListClickedLine_6F9BEA98 = -2;

D2MultiGameListEntryStrc gaDisplayedGames_6F9C2B48[GATE_MAX_GAMES];
D2MultiGameListEntryStrc gaGameList_6F9D11C0[GATE_MAX_GAMES];
char gszGameInfoName_6F9DF838[256];

D2WinTextBoxStrc* gpJoinGameList_6F9DF940;
D2WinTextBoxStrc* gpJoinGameInfo_6F9DF944;
D2WinControlStrc* gpJoinBackground_6F9DF948;
D2WinControlStrc* gpJoinOk_6F9DF94C;
D2WinControlStrc* gpJoinCancel_6F9DF950;
D2WinEditBoxStrc* gpJoinName_6F9DF954;
D2WinEditBoxStrc* gpJoinPassword_6F9DF958;
D2WinTextBoxStrc* gpJoinTitle_6F9DF95C;
D2WinTextBoxStrc* gpJoinNameLabel_6F9DF960;
D2WinTextBoxStrc* gpJoinPasswordLabel_6F9DF964;
D2WinTextBoxStrc* gpJoinGameListLabel_6F9DF968;

D2WinControlStrc* gpCreateBackground_6F9DF96C;
D2WinTextBoxStrc* gpCreateTitle_6F9DF970;
D2WinTextBoxStrc* gpCreateNameLabel_6F9DF974;
D2WinTextBoxStrc* gpCreatePasswordLabel_6F9DF978;
D2WinTextBoxStrc* gpCreateDescriptionLabel_6F9DF97C;
D2WinTextBoxStrc* gpCreateMaxPlayersLabel_6F9DF980;
D2WinTextBoxStrc* gpCreateLevelDifferenceLabel_6F9DF984;
D2WinTextBoxStrc* gpCreateLevelDifferenceSuffix_6F9DF988;
D2WinControlStrc* gpCreateMaxPlayersGreyBox_6F9DF98C;
D2WinControlStrc* gpCreateMaxPlayersGreyArrows_6F9DF990;
D2WinButtonStrc* gpCreateMaxPlayersUp_6F9DF994;
D2WinButtonStrc* gpCreateMaxPlayersDown_6F9DF998;
D2WinButtonStrc* gpCreateLevelDifferenceUp_6F9DF99C;
D2WinButtonStrc* gpCreateLevelDifferenceDown_6F9DF9A0;
D2WinControlStrc* gpCreateLevelDifferenceGreyArrows_6F9DF9A4;
D2WinControlStrc* gpCreateOk_6F9DF9A8;
D2WinEditBoxStrc* gpCreateName_6F9DF9AC;
D2WinEditBoxStrc* gpCreatePassword_6F9DF9B0;
D2WinEditBoxStrc* gpCreateDescription_6F9DF9B4;
D2WinEditBoxStrc* gpCreateMaxPlayers_6F9DF9B8;
D2WinEditBoxStrc* gpCreateLevelDifference_6F9DF9BC;
D2WinButtonStrc* gpCreateLevelDifferenceCheckbox_6F9DF9C0;
D2WinControlStrc* gpCreateLevelDifferenceGreyBox_6F9DF9C4;
D2WinControlStrc* gpCreateCancel_6F9DF9C8;
D2WinButtonStrc* gpCreateNormal_6F9DF9CC;
D2WinButtonStrc* gpCreateNightmare_6F9DF9D0;
D2WinButtonStrc* gpCreateHell_6F9DF9D4;
D2WinTextBoxStrc* gpCreateNormalLabel_6F9DF9D8;
D2WinTextBoxStrc* gpCreateNightmareLabel_6F9DF9DC;
D2WinTextBoxStrc* gpCreateHellLabel_6F9DF9E0;

D2WinControlStrc* gpProfileViewBackground_6F9DF9E4;
D2WinTextBoxStrc* gpProfileViewName_6F9DF9E8;
D2WinTextBoxStrc* gpProfileViewSex_6F9DF9EC;
D2WinTextBoxStrc* gpProfileViewLocation_6F9DF9F0;
D2WinTextBoxStrc* gpProfileViewDescription_6F9DF9F4;
D2WinControlStrc* gpProfileEditBackground_6F9DF9F8;
D2WinTextBoxStrc* gpProfileEditName_6F9DF9FC;
D2WinEditBoxStrc* gpProfileEditSex_6F9DFA00;
D2WinEditBoxStrc* gpProfileEditLocation_6F9DFA04;
D2WinEditBoxStrc* gpProfileEditDescription_6F9DFA08;
D2WinControlStrc* gpProfileCancel_6F9DFA0C;
D2WinTextBoxStrc* gpProfileNameLabel_6F9DFA10;
D2WinTextBoxStrc* gpProfileSexLabel_6F9DFA14;
D2WinTextBoxStrc* gpProfileLocationLabel_6F9DFA18;
D2WinTextBoxStrc* gpProfileDescriptionLabel_6F9DFA1C;
D2WinControlStrc* gpProfileOk_6F9DFA20;
D2WinControlStrc* gpProfileLadder_6F9DFA24;
D2WinTextBoxStrc* gpProfileTitle_6F9DFA28;
int32_t gnProfileMode_6F9DFA2C;

D2WinTextBoxStrc* gpHelpTitle_6F9DFA30;
D2WinTextBoxStrc* gpHelpText_6F9DFA34;
D2WinControlStrc* gpHelpOk_6F9DFA38;
D2WinControlStrc* gpHelpBackground_6F9DFA3C;
BOOL gbHelpOpened_6F9DFA40;

BOOL gbGameCreationCancelled_6F9DFA44;
int32_t gnDisplayedGameCount_6F9DFA48;
int32_t gnGameListCount_6F9DFA4C;
int32_t gnSelectedDifficulty_6F9DFA50;
char gszProfileCharacterName_6F9DFA54[16];
BOOL gbProfileHardcore_6F9DFA64;
BOOL gbProfileExpansion_6F9DFA68;
DWORD gdwLastGameListRequestTickCount_6F9DFA6C;
DWORD gdwLastGameListClickTickCount_6F9DFA70;


//Inlined
static void GATE_ResetButtonStates()
{
	BUTTON_SetIsPressed(gpChannelButton_6F9C2674, 0);
	BUTTON_SetIsPressed(gpCreateButton_6F9C2670, 0);
	BUTTON_SetIsPressed(gpJoinButton_6F9C2678, 0);
	BUTTON_SetIsPressed(gpLadderButton_6F9C267C, 0);
}

//Inlined
static const char* GATE_SkipString(const char* pszStr)
{
	D2_ASSERT(pszStr);

	while (*pszStr)
	{
		++pszStr;
	}
	return pszStr + 1;
}

//Inlined
static void GATE_GetGameListFlags(uint32_t* pFlags, uint32_t* pFilter)
{
	const uint16_t nCharacterFlags = gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags;
	const uint16_t nProgression = nCharacterFlags & 0x1F00;

	uint32_t nFlags = 0;
	uint32_t nFilter = 0;
	if (nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE)
	{
		nFlags = 4;
		nFilter = 4;
	}

	BOOL bHellNotReached = FALSE;
	if (nCharacterFlags & D2MULTI_SAVEFLAG_EXPANSION)
	{
		nFlags |= 8;
		nFilter |= 8;
		bHellNotReached = nProgression < 0xA00;
	}
	else
	{
		bHellNotReached = nProgression < 0x800;
	}

	if (bHellNotReached)
	{
		const BOOL bNightmareNotReached = (nCharacterFlags & D2MULTI_SAVEFLAG_EXPANSION) ? nProgression < 0x500 : nProgression < 0x400;
		nFilter |= bNightmareNotReached ? 3 : 2;
	}

	*pFlags = nFlags;
	*pFilter = nFilter;
}

//Inlined
static BOOL GATE_CanJoinDifficulty(char nDifficulty)
{
	const int32_t nMaxDifficulty = ((gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags >> 8) & 0x1F) / 5 + 1;
	if (!(gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags & D2MULTI_SAVEFLAG_HARDCORE))
	{
		return nDifficulty - '0' <= nMaxDifficulty;
	}

	return nDifficulty - '3' <= nMaxDifficulty && nDifficulty >= '3';
}

//Inlined
static BOOL GATE_IsEditBoxEmpty(D2WinEditBoxStrc* pEditBox)
{
	const Unicode* wszText = D2Win_10077_EDITBOX_GetText(pEditBox);
	if (wszText)
	{
		char szText[256];
		Unicode::unicode2Win(szText, wszText, 255);
		if (strlen(szText))
		{
			return FALSE;
		}
	}
	return TRUE;
}

//Inlined
static void GATE_ShowHelpLines(const uint16_t* pStringIds, size_t nCount)
{
	for (size_t i = 0; i < nCount; ++i)
	{
		if (pStringIds[i] == HELP_BLANK_LINE)
		{
			D2Win_10046(gpHelpText_6F9DFA34, " ", 0);
		}
		else
		{
			D2Win_10044(gpHelpText_6F9DFA34, D2LANG_GetStringFromTblIndex(pStringIds[i]));
		}
	}
}

//Inlined
static void GATE_CreateProfileLabels()
{
	gpProfileNameLabel_6F9DFA10 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_NAME_LABEL]);
	D2Win_10044(gpProfileNameLabel_6F9DFA10, D2LANG_GetStringFromTblIndex(0x1493));
	gpProfileSexLabel_6F9DFA14 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_SEX_LABEL]);
	D2Win_10044(gpProfileSexLabel_6F9DFA14, D2LANG_GetStringFromTblIndex(0x1494));
	gpProfileLocationLabel_6F9DFA18 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_LOCATION_LABEL]);
	D2Win_10044(gpProfileLocationLabel_6F9DFA18, D2LANG_GetStringFromTblIndex(0x1496));
	gpProfileDescriptionLabel_6F9DFA1C = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_DESCRIPTION_LABEL]);
	D2Win_10044(gpProfileDescriptionLabel_6F9DFA1C, D2LANG_GetStringFromTblIndex(0x1497));
	gpProfileTitle_6F9DFA28 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_TITLE]);
	D2Win_10044(gpProfileTitle_6F9DFA28, D2LANG_GetStringFromTblIndex(0x1492));
}

//Inlined
static void GATE_SetLevelDifferenceEnabled(BOOL bEnabled)
{
	D2Win_10027_CONTROL_ToggleThirdFlag(gpCreateLevelDifferenceGreyBox_6F9DF9C4, !bEnabled);
	D2Win_10027_CONTROL_ToggleThirdFlag(gpCreateLevelDifferenceGreyArrows_6F9DF9A4, !bEnabled);
	D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpCreateLevelDifferenceUp_6F9DF99C, bEnabled);
	D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpCreateLevelDifferenceDown_6F9DF9A0, bEnabled);
	D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateLevelDifference_6F9DF9BC, bEnabled);
	D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateLevelDifferenceUp_6F9DF99C, bEnabled);
	D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateLevelDifferenceDown_6F9DF9A0, bEnabled);

	const int32_t nColor = bEnabled ? 4 : 5;
	D2Win_10051(gpCreateLevelDifferenceLabel_6F9DF984, D2LANG_GetStringFromTblIndex(0x148B), nColor, 0, 0);
	D2Win_10051(gpCreateLevelDifferenceSuffix_6F9DF988, D2LANG_GetStringFromTblIndex(0x148C), nColor, 0, 0);
	GATE_UpdateCreateButton();
}

//Inlined
static void GATE_IncrementEditBoxValue(D2WinEditBoxStrc* pEditBox, char* szValue, int32_t nDelta, int32_t nMin, int32_t nMax)
{
	char szText[8];
	Unicode::toUtf(szText, D2Win_10077_EDITBOX_GetText(pEditBox), 5);

	int32_t nValue = atoi(szText);
	if (nDelta > 0 && nValue < nMax)
	{
		++nValue;
	}
	else if (nDelta < 0 && nValue > nMin)
	{
		--nValue;
	}

	sprintf(szValue, "%d", nValue);
	D2Win_10076(pEditBox, szValue);
}

//Inlined
static BOOL GATE_IsValidGameNameCharacter(char nChar)
{
	switch (nChar)
	{
	case ' ':
	case '\'':
	case '-':
	case '_':
		return TRUE;

	default:
		return (nChar >= '0' && nChar <= '9') || (nChar >= 'A' && nChar <= 'Z') || (nChar >= 'a' && nChar <= 'z');
	}
}

//Inlined
static void GATE_CloseProfileControls()
{
	if (gnProfileMode_6F9DFA2C != PROFILEMODE_NONE)
	{
		if (gnProfileMode_6F9DFA2C == PROFILEMODE_VIEW)
		{
			CONTROL_Destroy(&gpProfileViewBackground_6F9DF9E4);
			CONTROL_Destroy(&gpProfileViewName_6F9DF9E8);
			CONTROL_Destroy(&gpProfileViewSex_6F9DF9EC);
			CONTROL_Destroy(&gpProfileViewLocation_6F9DF9F0);
			CONTROL_Destroy(&gpProfileViewDescription_6F9DF9F4);
		}
		else
		{
			CONTROL_Destroy(&gpProfileEditBackground_6F9DF9F8);
			CONTROL_Destroy(&gpProfileEditName_6F9DF9FC);
			CONTROL_Destroy(&gpProfileEditSex_6F9DFA00);
			CONTROL_Destroy(&gpProfileEditLocation_6F9DFA04);
			CONTROL_Destroy(&gpProfileEditDescription_6F9DFA08);
			CONTROL_Destroy(&gpProfileCancel_6F9DFA0C);
		}

		gnProfileMode_6F9DFA2C = PROFILEMODE_NONE;
		CONTROL_Destroy(&gpProfileNameLabel_6F9DFA10);
		CONTROL_Destroy(&gpProfileSexLabel_6F9DFA14);
		CONTROL_Destroy(&gpProfileLocationLabel_6F9DFA18);
		CONTROL_Destroy(&gpProfileDescriptionLabel_6F9DFA1C);
		CONTROL_Destroy(&gpProfileOk_6F9DFA20);
		CONTROL_Destroy(&gpProfileLadder_6F9DFA24);
		CONTROL_Destroy(&gpProfileTitle_6F9DFA28);
	}

	D2Win_10031(gpQuitButton_6F9C2680);
	CHATDLG_FocusChatEditBox();
}

//Inlined
static void GATE_RequestMCPGameList()
{
	D2MultiGameListFilterStrc tFilter = {};
	if (gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags & D2MULTI_SAVEFLAG_HARDCORE)
	{
		tFilter.dwFlags |= 0x800;
	}

	do
	{
		++gnMCPRequestId_6F9BC03C;
	}
	while (!gnMCPRequestId_6F9BC03C);

	D2MCPCLIENT_10006(&tFilter, gnMCPRequestId_6F9BC03C);
	gnMCPPendingRequestIds_6F9C26F4[0] = gnMCPRequestId_6F9BC03C;
}


//D2Multi.0x6F9AF3C0
void __fastcall GATE_RequestBattleNetGameList()
{
	uint32_t nFlags = 0;
	uint32_t nFilter = 0;
	GATE_GetGameListFlags(&nFlags, &nFilter);

	const int32_t* pGameList = (const int32_t*)gptComInt_6F9C19BC->GetGamesList(nullptr, nullptr, nFlags, nFilter);
	if (pGameList)
	{
		gnGameListCount_6F9DFA4C = pGameList[0];
		const D2MultiBnGameStrc* pBnGame = (const D2MultiBnGameStrc*)&pGameList[1];

		int32_t nGameIndex = 0;
		while (nGameIndex < gnGameListCount_6F9DFA4C)
		{
			D2MultiGameListEntryStrc* pGame = &gaGameList_6F9D11C0[nGameIndex];
			pGame->nGameToken = 1;
			pGame->nIpAddress = pBnGame->nIpAddress;
			strcpy(pGame->szGameName, pBnGame->szGameName);

			if (gpJoinGameList_6F9DF940)
			{
				D2Win_10045(gpJoinGameList_6F9DF940, pBnGame->szGameName);
			}

			const char* szGamePassword = GATE_SkipString(pBnGame->szGameName);
			const char* szStatstring = GATE_SkipString(szGamePassword);
			if (GATE_CanJoinDifficulty(szStatstring[0]))
			{
				strcpy(pGame->szGameDescription, &szStatstring[1]);
				++nGameIndex;
			}
			else
			{
				--gnGameListCount_6F9DFA4C;
			}

			pBnGame = (const D2MultiBnGameStrc*)(GATE_SkipString(szStatstring) - offsetof(D2MultiBnGameStrc, szGameName));
		}
	}

	GATE_UpdateGameList();
}

//D2Multi.0x6F9AF5D0
void __fastcall GATE_AddMCPGame(D2MultiMCPGameListStrc* pGame)
{
	for (int32_t i = 0; i < gnGameListCount_6F9DFA4C; ++i)
	{
		if (gaGameList_6F9D11C0[i].nGameToken == pGame->nGameToken)
		{
			return;
		}
	}

	D2MultiGameListEntryStrc* pEntry = &gaGameList_6F9D11C0[gnGameListCount_6F9DFA4C];
	pEntry->nGameToken = pGame->nGameToken;
	pEntry->nIpAddress = 0;
	pEntry->nPlayers = pGame->nPlayers;
	strcpy(pEntry->szGameName, pGame->szGameName);
	strcpy(pEntry->szGameDescription, pGame->szGameDescription);
	++gnGameListCount_6F9DFA4C;
}

//D2Multi.0x6F9AF660
void __fastcall GATE_CreateJoinDialog()
{
	if (CHATDLG_CheckRealmConnection() == -1)
	{
		CHATDLG_ShowMessageBox(D2LANG_GetStringFromTblIndex(0x1413), nullptr);
		return;
	}

	gpJoinBackground_6F9DF948 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_BACKGROUND]);
	gpJoinTitle_6F9DF95C = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_TITLE]);
	D2Win_10044(gpJoinTitle_6F9DF95C, D2LANG_GetStringFromTblIndex(0x141F));
	gpJoinNameLabel_6F9DF960 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_NAME_LABEL]);
	D2Win_10044(gpJoinNameLabel_6F9DF960, D2LANG_GetStringFromTblIndex(0x149A));
	gpJoinPasswordLabel_6F9DF964 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_PASSWORD_LABEL]);
	D2Win_10044(gpJoinPasswordLabel_6F9DF964, D2LANG_GetStringFromTblIndex(0x1469));
	gpJoinGameListLabel_6F9DF968 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_GAMELIST_LABEL]);
	D2Win_10044(gpJoinGameListLabel_6F9DF968, D2LANG_GetStringFromTblIndex(0x149B));

	gpJoinOk_6F9DF94C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_OK]);
	gpJoinCancel_6F9DF950 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CANCEL]);
	D2Win_10031(gpJoinCancel_6F9DF950);

	gpJoinName_6F9DF954 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_NAME]);
	D2Win_10081(gpJoinName_6F9DF954, 16);
	D2Win_10072(gpJoinName_6F9DF954, (int32_t)GATE_JoinNameInputCallback);
	D2Win_10073(gpJoinName_6F9DF954, GATE_JoinNameChangeCallback);
	gpJoinPassword_6F9DF958 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_PASSWORD]);
	D2Win_10081(gpJoinPassword_6F9DF958, 16);
	D2Win_10072(gpJoinPassword_6F9DF958, (int32_t)GATE_TextInputCallback);
	D2Win_10080_EDITBOX_SetNextEditBox(gpJoinName_6F9DF954, gpJoinPassword_6F9DF958);
	D2Win_10080_EDITBOX_SetNextEditBox(gpJoinPassword_6F9DF958, gpJoinName_6F9DF954);

	gpJoinGameList_6F9DF940 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_GAMELIST]);
	if (D2MCPCLIENT_10002())
	{
		// Add the player count column
		D2Win_10056(gpJoinGameList_6F9DF940, 2);
		D2Win_10059(gpJoinGameList_6F9DF940, 1, 135);
	}

	gpJoinGameInfo_6F9DF944 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_JOIN_GAMEINFO]);

	const DWORD dwTickCount = GetTickCount();
	if (dwTickCount - gdwLastGameListRequestTickCount_6F9DFA6C >= 5000)
	{
		gdwLastGameListRequestTickCount_6F9DFA6C = dwTickCount;
		GATE_RequestGameList();
	}

	D2Win_10012(gpJoinName_6F9DF954);
	gnDisplayedGameCount_6F9DFA48 = 0;
	gnGameListCount_6F9DFA4C = 0;
	D2Win_10025_CONTROL_ToggleFirstFlag(gpJoinOk_6F9DF94C, !GATE_IsEditBoxEmpty(gpJoinName_6F9DF954));
}

//D2Multi.0x6F9AF920
void __fastcall GATE_RequestGameList()
{
	gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_GAMELIST;
	gnGameListCount_6F9DFA4C = 0;
	if (gpConfig_6F9C26F0->nLaunchType == LAUNCHTYPE_REALM)
	{
		GATE_RequestMCPGameList();
	}
	else
	{
		GATE_RequestBattleNetGameList();
	}
}

//D2Multi.0x6F9AF9A0
void __fastcall GATE_UpdateGameList()
{
	if (!gpJoinGameList_6F9DF940)
	{
		return;
	}

	char szSelectedGame[256];
	const Unicode* wszSelectedGame = D2Win_10048(gpJoinGameList_6F9DF940);
	if (wszSelectedGame)
	{
		Unicode::unicode2Win(szSelectedGame, wszSelectedGame, std::size(szSelectedGame));
	}

	int32_t nTopLine = D2Win_10054(gpJoinGameList_6F9DF940);
	D2Win_10047(gpJoinGameList_6F9DF940);
	D2Win_10047(gpJoinGameInfo_6F9DF944);

	gnDisplayedGameCount_6F9DFA48 = gnGameListCount_6F9DFA4C;
	if (!gnGameListCount_6F9DFA4C)
	{
		return;
	}

	const BOOL bShowPlayers = D2MCPCLIENT_10002();
	memcpy(gaDisplayedGames_6F9C2B48, gaGameList_6F9D11C0, gnGameListCount_6F9DFA4C * sizeof(D2MultiGameListEntryStrc));

	for (int32_t i = 0; i < gnDisplayedGameCount_6F9DFA48; ++i)
	{
		D2Win_10045(gpJoinGameList_6F9DF940, gaDisplayedGames_6F9C2B48[i].szGameName);
		const int32_t nLine = D2Win_10061(gpJoinGameList_6F9DF940);
		if (bShowPlayers)
		{
			char szPlayers[16];
			_itoa(gaDisplayedGames_6F9C2B48[i].nPlayers, szPlayers, 10);
			D2Win_10057(gpJoinGameList_6F9DF940, szPlayers, nLine, 1);
		}
	}

	if (wszSelectedGame)
	{
		// Keep the previous selection
		for (int32_t i = 0; i < gnDisplayedGameCount_6F9DFA48; ++i)
		{
			if (!strcmp(szSelectedGame, gaDisplayedGames_6F9C2B48[i].szGameName))
			{
				D2Win_10050_TEXTBOX_SetLine(gpJoinGameList_6F9DF940, i);
				break;
			}
		}
	}
	else
	{
		nTopLine = 0;
	}

	D2Win_10053(gpJoinGameList_6F9DF940, nTopLine);
}

//D2Multi.0x6F9AFB40
int32_t __stdcall GATE_JoinNameInputCallback(int32_t a1, int32_t a2, const char* pKey)
{
	D2Win_10050_TEXTBOX_SetLine(gpJoinGameList_6F9DF940, -1);
	return GATE_IsValidGameNameCharacter(*pKey);
}

//D2Multi.0x6F9AFBF0
void __stdcall GATE_JoinNameChangeCallback(int32_t a1)
{
	D2Win_10025_CONTROL_ToggleFirstFlag(gpJoinOk_6F9DF94C, !GATE_IsEditBoxEmpty(gpJoinName_6F9DF954));
}

//D2Multi.0x6F9AFC50
void __fastcall GATE_RequestSelectedGameInfo()
{
	if (gnGameInfoRequestId_6F9BEA94 != -1)
	{
		D2MCPCLIENT_10007(gszGameInfoName_6F9DF838, gnGameInfoRequestId_6F9BEA94);
		gnMCPPendingRequestIds_6F9C26F4[1] = gnGameInfoRequestId_6F9BEA94;
		gnGameInfoRequestId_6F9BEA94 = -1;
	}
}

//D2Multi.0x6F9AFC80
int32_t __stdcall GATE_GameListCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const int32_t nLine = D2Win_10049(gpJoinGameList_6F9DF940);
	D2Win_10047(gpJoinGameInfo_6F9DF944);
	if (nLine == -1)
	{
		return 0;
	}

	if (pMsg->nMessage == WM_LBUTTONDOWN)
	{
		// Join the game on double click
		const DWORD dwTickCount = GetTickCount();
		if (nLine == gnLastGameListClickedLine_6F9BEA98 && dwTickCount - gdwLastGameListClickTickCount_6F9DFA70 <= 500)
		{
			GATE_JoinGameCallback(nullptr);
			return 0;
		}

		gnLastGameListClickedLine_6F9BEA98 = nLine;
		gdwLastGameListClickTickCount_6F9DFA70 = dwTickCount;
	}

	if (D2MCPCLIENT_10002())
	{
		const Unicode* wszGameName = D2Win_10048(gpJoinGameList_6F9DF940);
		if (wszGameName)
		{
			char szGameName[256];
			Unicode::unicode2Win(szGameName, wszGameName, std::size(szGameName));

			// The game info is requested later by the main loop
			do
			{
				++gnMCPRequestId_6F9BC03C;
			}
			while (!gnMCPRequestId_6F9BC03C);

			strncpy(gszGameInfoName_6F9DF838, szGameName, std::size(gszGameInfoName_6F9DF838));
			gnGameInfoRequestId_6F9BEA94 = gnMCPRequestId_6F9BC03C;
			D2Win_10075(gpJoinName_6F9DF954, wszGameName);
			D2Win_10012(nullptr);
		}
		return 0;
	}

	if (gpJoinGameInfo_6F9DF944)
	{
		const D2MultiGameListEntryStrc* pGame = &gaGameList_6F9D11C0[nLine];
		D2Win_10047(gpJoinGameInfo_6F9DF944);
		if (strlen(pGame->szGameDescription))
		{
			D2Win_10045(gpJoinGameInfo_6F9DF944, pGame->szGameDescription);
			D2Win_10045(gpJoinGameInfo_6F9DF944, gszEmpty_6F9C28D8);
		}
		D2Win_10053(gpJoinGameInfo_6F9DF944, 0);

		D2Win_10076(gpJoinName_6F9DF954, pGame->szGameName);
		D2Win_10012(nullptr);
	}

	return 0;
}

//D2Multi.0x6F9AFE10
void __fastcall GATE_ShowGameInfo(D2MultiMCPGameInfoStrc* pGameInfo)
{
	if (!gpJoinGameInfo_6F9DF944)
	{
		return;
	}

	D2Win_10047(gpJoinGameInfo_6F9DF944);
	if (strlen(pGameInfo->szGameDescription))
	{
		D2Win_10045(gpJoinGameInfo_6F9DF944, pGameInfo->szGameDescription);
		D2Win_10045(gpJoinGameInfo_6F9DF944, gszEmpty_6F9C28D8);
	}

	char szText[256];
	const uint32_t nUptime = pGameInfo->nUptime;
	sprintf(szText, "Elapsed Time: %d:%02d:%02d", nUptime / 3600, (nUptime % 3600) / 60, nUptime % 60);
	D2Win_10045(gpJoinGameInfo_6F9DF944, szText);

	const uint8_t nLevelDifference = pGameInfo->nLevelDifference;
	if (nLevelDifference < 100)
	{
		if (nLevelDifference == 0)
		{
			sprintf(szText, "Level %d", pGameInfo->nLevel);
		}
		else
		{
			const int32_t nMinLevel = std::max((int32_t)pGameInfo->nLevel - (int32_t)nLevelDifference, 1);
			const int32_t nMaxLevel = std::min((int32_t)pGameInfo->nLevel + (int32_t)nLevelDifference, 99);
			sprintf(szText, "Level %d to %d", nMinLevel, nMaxLevel);
		}
		D2Win_10045(gpJoinGameInfo_6F9DF944, szText);
	}

	if (pGameInfo->nMaxPlayers != 0 && pGameInfo->nMaxPlayers < 8)
	{
		sprintf(szText, "Up to %d Players", pGameInfo->nMaxPlayers);
		D2Win_10045(gpJoinGameInfo_6F9DF944, szText);
	}

	D2Win_10045(gpJoinGameInfo_6F9DF944, gszEmpty_6F9C28D8);

	for (int32_t i = 0; i < pGameInfo->nPlayers; ++i)
	{
		if (pGameInfo->szCharacterNames[i][0])
		{
			D2Win_10045(gpJoinGameInfo_6F9DF944, pGameInfo->szCharacterNames[i]);

			const char* szFormat = nullptr;
			switch (pGameInfo->nClasses[i])
			{
			case 0:
				szFormat = "Level %d Amazon";
				break;
			case 1:
				szFormat = "Level %d Sorceress";
				break;
			case 2:
				szFormat = "Level %d Necromancer";
				break;
			case 3:
				szFormat = "Level %d Paladin";
				break;
			case 4:
				szFormat = "Level %d Barbarian";
				break;
			case 5:
				szFormat = "Level %d Druid";
				break;
			case 6:
				szFormat = "Level %d Assassin";
				break;
			default:
				szFormat = "Level %d";
				break;
			}

			sprintf(szText, szFormat, pGameInfo->nLevels[i]);
			D2Win_10046(gpJoinGameInfo_6F9DF944, szText, 5);
		}
	}

	D2Win_10053(gpJoinGameInfo_6F9DF944, 0);
}

//D2Multi.0x6F9B0080
void __fastcall GATE_CloseJoinDialog()
{
	CONTROL_Destroy(&gpJoinBackground_6F9DF948);
	CONTROL_Destroy(&gpJoinName_6F9DF954);
	CONTROL_Destroy(&gpJoinPassword_6F9DF958);
	CONTROL_Destroy(&gpJoinGameList_6F9DF940);
	CONTROL_Destroy(&gpJoinGameInfo_6F9DF944);
	CONTROL_Destroy(&gpJoinOk_6F9DF94C);
	CONTROL_Destroy(&gpJoinCancel_6F9DF950);
	CONTROL_Destroy(&gpJoinTitle_6F9DF95C);
	CONTROL_Destroy(&gpJoinNameLabel_6F9DF960);
	CONTROL_Destroy(&gpJoinPasswordLabel_6F9DF964);
	CONTROL_Destroy(&gpJoinGameListLabel_6F9DF968);
	D2Win_10031(gpQuitButton_6F9C2680);
}

//D2Multi.0x6F9B0100
void __fastcall GATE_UpdateLevelDifferenceControls()
{
	GATE_SetLevelDifferenceEnabled(BUTTON_IsPressed(gpCreateLevelDifferenceCheckbox_6F9DF9C0));
}

//D2Multi.0x6F9B0240
void __fastcall GATE_ShowGameQueue()
{
	gpCreateBackground_6F9DF96C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_NEWS_BACKGROUND]);
	gpCreateTitle_6F9DF970 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_GAMEQUEUE_TITLE]);
	D2Win_10044(gpCreateTitle_6F9DF970, D2LANG_GetStringFromTblIndex(0x141E));
	gpCreateNameLabel_6F9DF974 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_GAMEQUEUE_TEXT]);
	D2Win_10044(gpCreateNameLabel_6F9DF974, D2LANG_GetStringFromTblIndex(0x2B0F));
	D2Win_10046(gpCreateNameLabel_6F9DF974, " ", 0);

	// "Position in line: <position>"
	char szPosition[100];
	Unicode wszPosition[100];
	sprintf(szPosition, "%d ", D2MCPCLIENT_10050());
	Unicode::toUnicode(wszPosition, szPosition, 50);

	Unicode wszText[200];
	Unicode::strcpy(wszText, D2LANG_GetStringFromTblIndex(0x2B12));
	Unicode::strcat(wszText, D2LANG_GetStringFromTblIndex(0xF9A));

	char szColor[4];
	Unicode wszColor[3];
	wsprintfA(szColor, "%d", 0);
	Unicode::win2Unicode(wszColor, szColor, 2);
	Unicode::strcat(wszText, wszColor);
	Unicode::strcat(wszText, wszPosition);
	D2Win_10044(gpCreateNameLabel_6F9DF974, wszText);

	gpCreateCancel_6F9DF9C8 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_GAMEQUEUE_CANCEL]);
	D2Win_10031(gpCreateCancel_6F9DF9C8);
	gpCreateOk_6F9DF9A8 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_GAMEQUEUE_TIMER]);
	CHATDLG_ShowNews(FALSE);
}

//D2Multi.0x6F9B03E0
int32_t __stdcall GATE_GameQueueTimerCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_CloseDialogs();
	GATE_ShowGameQueue();
	return 1;
}

//D2Multi.0x6F9B0400
void __fastcall GATE_CreateCreateDialog()
{
	if (CHATDLG_CheckRealmConnection() == -1)
	{
		CHATDLG_ShowMessageBox(D2LANG_GetStringFromTblIndex(0x1413), nullptr);
		return;
	}

	if (D2MCPCLIENT_10052())
	{
		// Already waiting in the game creation queue
		GATE_ShowGameQueue();
		return;
	}

	gpConfig_6F9C26F0->nArenaDifficulty = 0;

	gpCreateBackground_6F9DF96C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_BACKGROUND]);
	gpCreateTitle_6F9DF970 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_TITLE]);
	D2Win_10044(gpCreateTitle_6F9DF970, D2LANG_GetStringFromTblIndex(0x141E));
	gpCreateNameLabel_6F9DF974 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_NAME_LABEL]);
	D2Win_10044(gpCreateNameLabel_6F9DF974, D2LANG_GetStringFromTblIndex(0x149A));
	gpCreatePasswordLabel_6F9DF978 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_PASSWORD_LABEL]);
	D2Win_10044(gpCreatePasswordLabel_6F9DF978, D2LANG_GetStringFromTblIndex(0x1488));
	gpCreateDescriptionLabel_6F9DF97C = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_DESCRIPTION_LABEL]);
	D2Win_10044(gpCreateDescriptionLabel_6F9DF97C, D2LANG_GetStringFromTblIndex(0x1489));
	if (D2MCPCLIENT_10002())
	{
		gpCreateMaxPlayersLabel_6F9DF980 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_MAXPLAYERS_LABEL]);
		D2Win_10044(gpCreateMaxPlayersLabel_6F9DF980, D2LANG_GetStringFromTblIndex(0x148A));
	}

	gpCreateOk_6F9DF9A8 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_OK]);
	gpCreateCancel_6F9DF9C8 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CANCEL]);
	D2Win_10031(gpCreateCancel_6F9DF9C8);

	gpCreateName_6F9DF9AC = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_NAME]);
	D2Win_10081(gpCreateName_6F9DF9AC, 16);
	D2Win_10072(gpCreateName_6F9DF9AC, (int32_t)GATE_GameNameInputCallback);
	D2Win_10073(gpCreateName_6F9DF9AC, GATE_GameNameChangeCallback);
	gpCreatePassword_6F9DF9B0 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_PASSWORD]);
	D2Win_10081(gpCreatePassword_6F9DF9B0, 16);
	D2Win_10072(gpCreatePassword_6F9DF9B0, (int32_t)GATE_TextInputCallback);
	gpCreateDescription_6F9DF9B4 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_DESCRIPTION]);
	D2Win_10081(gpCreateDescription_6F9DF9B4, 32);
	D2Win_10072(gpCreateDescription_6F9DF9B4, (int32_t)GATE_TextInputCallback);

	sprintf(gszLevelDifference_6F9BEA90, "%d", 4);
	sprintf(gszMaxPlayers_6F9BEA92, "%d", 4);

	if (!D2MCPCLIENT_10002())
	{
		// Max players and level difference are only available on realms
		D2Win_10080_EDITBOX_SetNextEditBox(gpCreateName_6F9DF9AC, gpCreatePassword_6F9DF9B0);
		D2Win_10080_EDITBOX_SetNextEditBox(gpCreatePassword_6F9DF9B0, gpCreateDescription_6F9DF9B4);
		D2Win_10080_EDITBOX_SetNextEditBox(gpCreateDescription_6F9DF9B4, gpCreateName_6F9DF9AC);

		gpCreateMaxPlayersLabel_6F9DF980 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_MAXPLAYERS_LABEL]);
		D2Win_10051(gpCreateMaxPlayersLabel_6F9DF980, D2LANG_GetStringFromTblIndex(0x148A), 5, 0, 0);
		gpCreateLevelDifferenceLabel_6F9DF984 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_LABEL]);
		D2Win_10051(gpCreateLevelDifferenceLabel_6F9DF984, D2LANG_GetStringFromTblIndex(0x148B), 5, 0, 0);
		gpCreateLevelDifferenceSuffix_6F9DF988 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_SUFFIX]);
		D2Win_10051(gpCreateLevelDifferenceSuffix_6F9DF988, D2LANG_GetStringFromTblIndex(0x148C), 5, 0, 0);

		gpCreateLevelDifferenceGreyBox_6F9DF9C4 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_GREYBOX]);
		D2Win_10027_CONTROL_ToggleThirdFlag(gpCreateLevelDifferenceGreyBox_6F9DF9C4, 1);
		gpCreateLevelDifferenceGreyArrows_6F9DF9A4 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_GREYARROWS]);
		D2Win_10027_CONTROL_ToggleThirdFlag(gpCreateLevelDifferenceGreyArrows_6F9DF9A4, 1);
		D2Win_10025_CONTROL_ToggleFirstFlag(gpCreateLevelDifferenceGreyArrows_6F9DF9A4, 0);
		gpCreateMaxPlayersGreyBox_6F9DF98C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_MAXPLAYERS_GREYBOX]);
		D2Win_10027_CONTROL_ToggleThirdFlag(gpCreateMaxPlayersGreyBox_6F9DF98C, 1);
		gpCreateMaxPlayersGreyArrows_6F9DF990 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_MAXPLAYERS_GREYARROWS]);
		D2Win_10027_CONTROL_ToggleThirdFlag(gpCreateMaxPlayersGreyArrows_6F9DF990, 1);
		D2Win_10025_CONTROL_ToggleFirstFlag(gpCreateMaxPlayersGreyArrows_6F9DF990, 0);
	}
	else
	{
		gpCreateMaxPlayers_6F9DF9B8 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_MAXPLAYERS]);
		D2Win_10076(gpCreateMaxPlayers_6F9DF9B8, gszMaxPlayers_6F9BEA92);
		D2Win_10081(gpCreateMaxPlayers_6F9DF9B8, 3);
		D2Win_10072(gpCreateMaxPlayers_6F9DF9B8, (int32_t)D2Win_10078_IsNumber);
		D2Win_10073(gpCreateMaxPlayers_6F9DF9B8, GATE_MaxPlayersChangeCallback);

		gpCreateLevelDifferenceCheckbox_6F9DF9C0 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_CHECKBOX]);
		BUTTON_SetIsPressed(gpCreateLevelDifferenceCheckbox_6F9DF9C0, 1);
		gpCreateLevelDifferenceGreyBox_6F9DF9C4 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_GREYBOX]);

		gpCreateLevelDifference_6F9DF9BC = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF]);
		D2Win_10076(gpCreateLevelDifference_6F9DF9BC, gszLevelDifference_6F9BEA90);
		D2Win_10081(gpCreateLevelDifference_6F9DF9BC, 3);
		D2Win_10072(gpCreateLevelDifference_6F9DF9BC, (int32_t)D2Win_10078_IsNumber);
		D2Win_10073(gpCreateLevelDifference_6F9DF9BC, GATE_LevelDifferenceChangeCallback);
		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateLevelDifference_6F9DF9BC, 0);

		gpCreateLevelDifferenceLabel_6F9DF984 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_LABEL]);
		D2Win_10051(gpCreateLevelDifferenceLabel_6F9DF984, D2LANG_GetStringFromTblIndex(0x148B), 5, 0, 0);
		gpCreateLevelDifferenceSuffix_6F9DF988 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_SUFFIX]);
		D2Win_10051(gpCreateLevelDifferenceSuffix_6F9DF988, D2LANG_GetStringFromTblIndex(0x148C), 5, 0, 0);

		gpCreateMaxPlayersUp_6F9DF994 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_MAXPLAYERS_UP]);
		gpCreateMaxPlayersDown_6F9DF998 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_MAXPLAYERS_DOWN]);
		gpCreateLevelDifferenceUp_6F9DF99C = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_UP]);
		gpCreateLevelDifferenceDown_6F9DF9A0 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_DOWN]);
		gpCreateLevelDifferenceGreyArrows_6F9DF9A4 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_LEVELDIFF_GREYARROWS]);
		BUTTON_SetBaseFrame(gpCreateMaxPlayersDown_6F9DF998, 2);
		BUTTON_SetBaseFrame(gpCreateLevelDifferenceDown_6F9DF9A0, 2);
		D2Win_10027_CONTROL_ToggleThirdFlag(gpCreateLevelDifferenceGreyArrows_6F9DF9A4, 1);
		D2Win_10025_CONTROL_ToggleFirstFlag(gpCreateLevelDifferenceGreyArrows_6F9DF9A4, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpCreateLevelDifferenceUp_6F9DF99C, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag((D2WinControlStrc*)gpCreateLevelDifferenceDown_6F9DF9A0, 0);
		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateLevelDifferenceUp_6F9DF99C, 0);
		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)gpCreateLevelDifferenceDown_6F9DF9A0, 0);

		D2Win_10080_EDITBOX_SetNextEditBox(gpCreateName_6F9DF9AC, gpCreatePassword_6F9DF9B0);
		D2Win_10080_EDITBOX_SetNextEditBox(gpCreatePassword_6F9DF9B0, gpCreateDescription_6F9DF9B4);
		D2Win_10080_EDITBOX_SetNextEditBox(gpCreateDescription_6F9DF9B4, gpCreateMaxPlayers_6F9DF9B8);
		D2Win_10080_EDITBOX_SetNextEditBox(gpCreateMaxPlayers_6F9DF9B8, gpCreateLevelDifference_6F9DF9BC);
		D2Win_10080_EDITBOX_SetNextEditBox(gpCreateLevelDifference_6F9DF9BC, gpCreateName_6F9DF9AC);

		// Restore the previous settings
		DWORD dwLevelRestriction = 4;
		if (!SRegLoadValue(GATE_REGISTRY_KEY, GATE_REGISTRY_LEVEL_RESTRICTION, 0, &dwLevelRestriction))
		{
			SRegSaveValue(GATE_REGISTRY_KEY, GATE_REGISTRY_LEVEL_RESTRICTION, 0, dwLevelRestriction);
		}
		else
		{
			char szLevelRestriction[4] = "4";
			const BOOL bRestricted = dwLevelRestriction != GATE_NO_LEVEL_RESTRICTION;
			if (bRestricted)
			{
				SStrPrintf(szLevelRestriction, std::size(szLevelRestriction), (char*)"%d", (int32_t)dwLevelRestriction);
				D2Win_10076(gpCreateLevelDifference_6F9DF9BC, szLevelRestriction);
			}
			BUTTON_SetIsPressed(gpCreateLevelDifferenceCheckbox_6F9DF9C0, bRestricted);
			GATE_UpdateLevelDifferenceControls();
		}

		DWORD dwMaxPlayers = 4;
		if (!SRegLoadValue(GATE_REGISTRY_KEY, GATE_REGISTRY_MAX_PLAYERS, 0, &dwMaxPlayers))
		{
			SRegSaveValue(GATE_REGISTRY_KEY, GATE_REGISTRY_MAX_PLAYERS, 0, dwMaxPlayers);
		}

		char szMaxPlayers[4] = "4";
		if ((int32_t)dwMaxPlayers < 9 && (int32_t)dwMaxPlayers > 0)
		{
			sprintf(szMaxPlayers, "%d", (int32_t)dwMaxPlayers);
			D2Win_10076(gpCreateMaxPlayers_6F9DF9B8, szMaxPlayers);
		}
	}

	DWORD dwDifficulty = 0;
	if (!SRegLoadValue(GATE_REGISTRY_KEY, GATE_REGISTRY_DIFFICULTY, 0, &dwDifficulty))
	{
		SRegSaveValue(GATE_REGISTRY_KEY, GATE_REGISTRY_DIFFICULTY, 0, 0);
	}

	BOOL bDifficultySelected = FALSE;
	const uint8_t nProgression = (gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags >> 8) & 0x1F;
	const BOOL bExpansion = (gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags & D2MULTI_SAVEFLAG_EXPANSION) != 0;
	gpCreateHell_6F9DF9D4 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_HELL]);
	gpCreateHellLabel_6F9DF9E0 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_HELL_LABEL]);
	gpCreateNightmare_6F9DF9D0 = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_NIGHTMARE]);
	gpCreateNightmareLabel_6F9DF9DC = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_NIGHTMARE_LABEL]);

	if ((!bExpansion && nProgression > 7) || nProgression > 9)
	{
		D2Win_10051(gpCreateHellLabel_6F9DF9E0, D2LANG_GetStringFromTblIndex(0x2720), 4, 0, 0);
		if (dwDifficulty == 2)
		{
			BUTTON_SetIsPressed(gpCreateHell_6F9DF9D4, 1);
			gnSelectedDifficulty_6F9DFA50 = 2;
			bDifficultySelected = TRUE;
			gpConfig_6F9C26F0->nArenaDifficulty = 2;
		}
	}
	else
	{
		D2Win_10051(gpCreateHellLabel_6F9DF9E0, D2LANG_GetStringFromTblIndex(0x2720), 5, 0, 0);
		CHATDLG_DisableRadioButton((D2WinControlStrc*)gpCreateHell_6F9DF9D4);
	}

	if ((!bExpansion && nProgression > 3) || nProgression > 4)
	{
		D2Win_10051(gpCreateNightmareLabel_6F9DF9DC, D2LANG_GetStringFromTblIndex(0x2721), 4, 0, 0);
		if (dwDifficulty == 1)
		{
			BUTTON_SetIsPressed(gpCreateNightmare_6F9DF9D0, 1);
			gnSelectedDifficulty_6F9DFA50 = 1;
			bDifficultySelected = TRUE;
			gpConfig_6F9C26F0->nArenaDifficulty = 1;
		}
	}
	else
	{
		D2Win_10051(gpCreateNightmareLabel_6F9DF9DC, D2LANG_GetStringFromTblIndex(0x2721), 5, 0, 0);
		CHATDLG_DisableRadioButton((D2WinControlStrc*)gpCreateNightmare_6F9DF9D0);
	}

	gpCreateNormalLabel_6F9DF9D8 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_NORMAL_LABEL]);
	D2Win_10051(gpCreateNormalLabel_6F9DF9D8, D2LANG_GetStringFromTblIndex(0x2722), 4, 0, 0);
	gpCreateNormal_6F9DF9CC = (D2WinButtonStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_CREATE_NORMAL]);
	if (!bDifficultySelected)
	{
		BUTTON_SetIsPressed(gpCreateNormal_6F9DF9CC, 1);
		gnSelectedDifficulty_6F9DFA50 = 0;
	}

	D2Win_10012(gpCreateName_6F9DF9AC);
	if (D2MCPCLIENT_10002())
	{
		GATE_LevelDifferenceCheckboxCallback(nullptr);
	}
}

//D2Multi.0x6F9B0C80
void __fastcall GATE_CloseCreateDialog()
{
	CONTROL_Destroy(&gpCreateBackground_6F9DF96C);
	CONTROL_Destroy(&gpCreateTitle_6F9DF970);
	CONTROL_Destroy(&gpCreateNameLabel_6F9DF974);
	CONTROL_Destroy(&gpCreatePasswordLabel_6F9DF978);
	CONTROL_Destroy(&gpCreateDescriptionLabel_6F9DF97C);
	CONTROL_Destroy(&gpCreateMaxPlayersLabel_6F9DF980);
	CONTROL_Destroy(&gpCreateLevelDifferenceLabel_6F9DF984);
	CONTROL_Destroy(&gpCreateLevelDifferenceSuffix_6F9DF988);
	CONTROL_Destroy(&gpCreateName_6F9DF9AC);
	CONTROL_Destroy(&gpCreatePassword_6F9DF9B0);
	CONTROL_Destroy(&gpCreateDescription_6F9DF9B4);
	CONTROL_Destroy(&gpCreateMaxPlayers_6F9DF9B8);
	CONTROL_Destroy(&gpCreateLevelDifference_6F9DF9BC);
	CONTROL_Destroy(&gpCreateOk_6F9DF9A8);
	CONTROL_Destroy(&gpCreateCancel_6F9DF9C8);
	CONTROL_Destroy(&gpCreateLevelDifferenceCheckbox_6F9DF9C0);
	CONTROL_Destroy(&gpCreateNormal_6F9DF9CC);
	CONTROL_Destroy(&gpCreateNightmare_6F9DF9D0);
	CONTROL_Destroy(&gpCreateHell_6F9DF9D4);
	CONTROL_Destroy(&gpCreateNormalLabel_6F9DF9D8);
	CONTROL_Destroy(&gpCreateNightmareLabel_6F9DF9DC);
	CONTROL_Destroy(&gpCreateHellLabel_6F9DF9E0);
	CONTROL_Destroy(&gpCreateLevelDifferenceGreyBox_6F9DF9C4);
	CONTROL_Destroy(&gpCreateMaxPlayersUp_6F9DF994);
	CONTROL_Destroy(&gpCreateMaxPlayersDown_6F9DF998);
	CONTROL_Destroy(&gpCreateLevelDifferenceUp_6F9DF99C);
	CONTROL_Destroy(&gpCreateLevelDifferenceDown_6F9DF9A0);
	CONTROL_Destroy(&gpCreateLevelDifferenceGreyArrows_6F9DF9A4);
	CONTROL_Destroy(&gpCreateMaxPlayersGreyBox_6F9DF98C);
	CONTROL_Destroy(&gpCreateMaxPlayersGreyArrows_6F9DF990);
	D2Win_10031(gpQuitButton_6F9C2680);
	CHATDLG_FocusChatEditBox();
}

//D2Multi.0x6F9B0DC0
int32_t __stdcall GATE_LevelDifferenceCheckboxCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_SetLevelDifferenceEnabled(BUTTON_IsPressed(gpCreateLevelDifferenceCheckbox_6F9DF9C0));
	return 1;
}

//D2Multi.0x6F9B0F10
int32_t __stdcall GATE_MaxPlayersUpCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_IncrementEditBoxValue(gpCreateMaxPlayers_6F9DF9B8, gszMaxPlayers_6F9BEA92, 1, 1, 8);
	return 1;
}

//D2Multi.0x6F9B0F70
int32_t __stdcall GATE_MaxPlayersDownCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_IncrementEditBoxValue(gpCreateMaxPlayers_6F9DF9B8, gszMaxPlayers_6F9BEA92, -1, 1, 8);
	return 1;
}

//D2Multi.0x6F9B0FD0
int32_t __stdcall GATE_LevelDifferenceUpCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_IncrementEditBoxValue(gpCreateLevelDifference_6F9DF9BC, gszLevelDifference_6F9BEA90, 1, 0, 99);
	return 1;
}

//D2Multi.0x6F9B1030
int32_t __stdcall GATE_LevelDifferenceDownCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_IncrementEditBoxValue(gpCreateLevelDifference_6F9DF9BC, gszLevelDifference_6F9BEA90, -1, 0, 99);
	return 1;
}

//D2Multi.0x6F9B1090
int32_t __stdcall GATE_GameNameInputCallback(int32_t a1, int32_t a2, const char* pKey)
{
	return GATE_IsValidGameNameCharacter(*pKey);
}

//D2Multi.0x6F9B1130
int32_t __stdcall GATE_TextInputCallback(int32_t a1, int32_t a2, const char* pKey)
{
	// Only printable ASCII characters (char is signed, so extended characters are negative)
	return *pKey >= ' ';
}

//D2Multi.0x6F9B1160
void __stdcall GATE_GameNameChangeCallback(int32_t a1)
{
	GATE_UpdateCreateButton();
}

//D2Multi.0x6F9B1170
void __stdcall GATE_MaxPlayersChangeCallback(int32_t a1)
{
	GATE_UpdateCreateButton();
}

//D2Multi.0x6F9B1180
void __stdcall GATE_LevelDifferenceChangeCallback(int32_t a1)
{
	GATE_UpdateCreateButton();
}

//D2Multi.0x6F9B1190
void __fastcall GATE_UpdateCreateButton()
{
	char szText[256];

	// The game name can't start or end with a space
	BOOL bGameNameValid = FALSE;
	const Unicode* wszGameName = D2Win_10077_EDITBOX_GetText(gpCreateName_6F9DF9AC);
	if (wszGameName)
	{
		Unicode::unicode2Win(szText, wszGameName, 16);
		const int32_t nLength = strlen(szText);
		if (szText[0] != ' ' && nLength > 0 && szText[nLength - 1] != ' ')
		{
			bGameNameValid = TRUE;
		}
	}

	BOOL bMaxPlayersValid = FALSE;
	BOOL bLevelDifferenceValid = FALSE;
	if (!D2MCPCLIENT_10002())
	{
		bMaxPlayersValid = TRUE;
		bLevelDifferenceValid = TRUE;
	}
	else
	{
		const Unicode* wszMaxPlayers = D2Win_10077_EDITBOX_GetText(gpCreateMaxPlayers_6F9DF9B8);
		if (wszMaxPlayers)
		{
			Unicode::unicode2Win(szText, wszMaxPlayers, 3);
			if (strlen(szText))
			{
				bMaxPlayersValid = TRUE;

				const int32_t nMaxPlayers = atoi(szText);
				if (nMaxPlayers < 1 || nMaxPlayers > 8)
				{
					sprintf(szText, "%d", std::clamp(nMaxPlayers, 1, 8));
					D2Win_10076(gpCreateMaxPlayers_6F9DF9B8, szText);
				}
			}
		}

		bLevelDifferenceValid = TRUE;
		if (BUTTON_IsPressed(gpCreateLevelDifferenceCheckbox_6F9DF9C0))
		{
			Unicode::unicode2Win(szText, D2Win_10077_EDITBOX_GetText(gpCreateLevelDifference_6F9DF9BC), 3);
			if (!strlen(szText) || atoi(szText) < 0)
			{
				bLevelDifferenceValid = FALSE;
			}
		}
	}

	D2Win_10025_CONTROL_ToggleFirstFlag(gpCreateOk_6F9DF9A8, bGameNameValid && bMaxPlayersValid && bLevelDifferenceValid);
}

//D2Multi.0x6F9B1300
void __stdcall GATE_WaitCreateGameResultCallback(DWORD dwCounter)
{
	int32_t nResult = dwCounter;
	if (gptComInt_6F9C19BC->GetCreateGameResult(&nResult))
	{
		D2Win_10009();
	}
}

//D2Multi.0x6F9B1330
void __stdcall GATE_WaitGameQueueCallback(DWORD dwCounter)
{
	D2MCPCLIENT_10003();
	if (D2MCPCLIENT_10052() || D2MCPCLIENT_10017() || D2MCPCLIENT_10046() || gbGameCreationCancelled_6F9DFA44)
	{
		D2Win_10009();
	}
}

//D2Multi.0x6F9B1370
int32_t __stdcall GATE_GameQueueCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_ResetMainButtons();
	CHATDLG_CancelGameQueue();
	GATE_CloseCreateDialog();
	return 1;
}

//D2Multi.0x6F9B1390
int32_t __stdcall GATE_CreateGameCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!D2Win_10024_CONTROL_CheckFirstFlag(gpCreateOk_6F9DF9A8))
	{
		return 0;
	}

	const Unicode* wszGameName = D2Win_10077_EDITBOX_GetText(gpCreateName_6F9DF9AC);
	if (!wszGameName)
	{
		return 1;
	}

	char szText[256];
	Unicode::unicode2Win(szText, wszGameName, 255);
	if (!strlen(szText))
	{
		return 0;
	}

	const Unicode* wszGamePassword = D2Win_10077_EDITBOX_GetText(gpCreatePassword_6F9DF9B0);
	const Unicode* wszGameDescription = D2Win_10077_EDITBOX_GetText(gpCreateDescription_6F9DF9B4);

	D2MultiCreateGameStrc tCreateGame;
	char szNumber[8];
	if (D2MCPCLIENT_10002())
	{
		const Unicode* wszMaxPlayers = D2Win_10077_EDITBOX_GetText(gpCreateMaxPlayers_6F9DF9B8);
		tCreateGame.nUnk0x44 = 1;
		if (BUTTON_IsPressed(gpCreateLevelDifferenceCheckbox_6F9DF9C0))
		{
			Unicode::unicode2Win(szNumber, D2Win_10077_EDITBOX_GetText(gpCreateLevelDifference_6F9DF9BC), 3);
			tCreateGame.nLevelDifference = (uint8_t)atoi(szNumber);
		}
		else
		{
			tCreateGame.nLevelDifference = 0xFF;
		}

		Unicode::unicode2Win(szNumber, wszMaxPlayers, 3);
		tCreateGame.nMaxPlayers = (uint8_t)atoi(szNumber);
	}

	Unicode::unicode2Win(tCreateGame.szGameName, wszGameName, std::size(tCreateGame.szGameName));
	Unicode::unicode2Win(tCreateGame.szGamePassword, wszGamePassword, std::size(tCreateGame.szGamePassword));
	Unicode::unicode2Win(tCreateGame.szGameDescription, wszGameDescription, std::size(tCreateGame.szGameDescription));
	tCreateGame.dwFlags = 0;
	FOG_10138(tCreateGame.szGameName);
	FOG_10138(tCreateGame.szGamePassword);
	tCreateGame.dwFlags = (tCreateGame.dwFlags & ~0x7000) | (gnSelectedDifficulty_6F9DFA50 << 12);

	if (!strlen(tCreateGame.szGameName))
	{
		return 0;
	}

	if (!D2MCPCLIENT_10002())
	{
		// Create the game on Battle.net
		const uint16_t nCharacterFlags = gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags;
		if (nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE)
		{
			gpConfig_6F9C26F0->nArenaFlags |= 0x800;
		}
		if (nCharacterFlags & D2MULTI_SAVEFLAG_EXPANSION)
		{
			gpConfig_6F9C26F0->nArenaFlags |= 0x100000;
		}

		char szStatstring[512];
		szStatstring[0] = ((nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE) ? 3 : 0) + gnSelectedDifficulty_6F9DFA50 + '1';
		SStrCopy(&szStatstring[1], tCreateGame.szGameDescription, INT_MAX);

		uint32_t nGameFlags = gpConfig_6F9C26F0->nArenaDifficulty == 1;
		if (gpConfig_6F9C26F0->nArenaDifficulty == 2)
		{
			nGameFlags |= 2;
		}
		if (gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags & D2MULTI_SAVEFLAG_HARDCORE)
		{
			nGameFlags |= 4;
		}
		if (gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags & D2MULTI_SAVEFLAG_EXPANSION)
		{
			nGameFlags |= 8;
		}

		gptComInt_6F9C19BC->RefreshGame(tCreateGame.szGameName, tCreateGame.szGamePassword, szStatstring, nGameFlags);
		CHATDLG_ShowWaitPopup(D2LANG_GetStringFromTblIndex(0x147B), nullptr);
		D2Win_10008(GATE_WaitCreateGameResultCallback);
		CHATDLG_DestroySubChildren();

		int32_t nResult = 0;
		gptComInt_6F9C19BC->GetCreateGameResult(&nResult);
		if (!nResult)
		{
			CHATDLG_ShowWaitPopup(D2LANG_GetStringFromTblIndex(0x1412), nullptr);
			return 1;
		}
	}
	else
	{
		// Remember the settings
		char szValue[8];
		Unicode::toUtf(szValue, D2Win_10077_EDITBOX_GetText(gpCreateMaxPlayers_6F9DF9B8), 5);
		SRegSaveValue(GATE_REGISTRY_KEY, GATE_REGISTRY_MAX_PLAYERS, 0, atoi(szValue));
		SRegSaveValue(GATE_REGISTRY_KEY, GATE_REGISTRY_DIFFICULTY, 0, gnSelectedDifficulty_6F9DFA50);

		int32_t nLevelRestriction = GATE_NO_LEVEL_RESTRICTION;
		if (BUTTON_IsPressed(gpCreateLevelDifferenceCheckbox_6F9DF9C0))
		{
			Unicode::toUtf(szValue, D2Win_10077_EDITBOX_GetText(gpCreateLevelDifference_6F9DF9BC), 5);
			nLevelRestriction = atoi(szValue);
		}
		SRegSaveValue(GATE_REGISTRY_KEY, GATE_REGISTRY_LEVEL_RESTRICTION, 0, nLevelRestriction);
	}

	CHATDLG_CreateGame(&tCreateGame, FOG_GetHostIPAddress());

	if (!D2MCPCLIENT_10002())
	{
		CHATDLG_ShowWaitPopup(D2LANG_GetStringFromTblIndex(0x147B), nullptr);
		GATE_CloseCreateDialog();
		return 1;
	}

	gbGameCreationCancelled_6F9DFA44 = FALSE;
	CHATDLG_ShowWaitPopup(D2LANG_GetStringFromTblIndex(0x147B), GATE_CancelGameCreationCallback);
	D2Win_10008(GATE_WaitGameQueueCallback);
	CHATDLG_DestroySubChildren();
	if (gbGameCreationCancelled_6F9DFA44)
	{
		CHATDLG_CancelGameQueue();
	}

	GATE_CloseCreateDialog();
	if (D2MCPCLIENT_10052())
	{
		GATE_ShowGameQueue();
	}
	return 1;
}

//D2Multi.0x6F9B1760
int32_t __stdcall GATE_CancelGameCreationCallback(SMSGHANDLER_PARAMS* pMsg)
{
	gbGameCreationCancelled_6F9DFA44 = TRUE;
	return 1;
}

//D2Multi.0x6F9B1770
int32_t __fastcall GATE_FindBattleNetGame(const char* szGameName, const char* szGamePassword, D2MultiGameListEntryStrc* pGame)
{
	uint32_t nFlags = 0;
	uint32_t nFilter = 0;
	GATE_GetGameListFlags(&nFlags, &nFilter);

	const int32_t* pGameList = (const int32_t*)gptComInt_6F9C19BC->GetGamesList(szGameName, szGamePassword, nFlags, nFilter);
	if (!pGameList || pGameList[0] <= 0)
	{
		return 0;
	}

	const D2MultiBnGameStrc* pBnGame = (const D2MultiBnGameStrc*)&pGameList[1];
	pGame->nGameToken = 1;
	pGame->nIpAddress = pBnGame->nIpAddress;
	strcpy(pGame->szGameName, pBnGame->szGameName);

	const char* szStatstring = GATE_SkipString(GATE_SkipString(pBnGame->szGameName));
	if (!GATE_CanJoinDifficulty(szStatstring[0]))
	{
		return 0;
	}

	// Note: unlike GATE_RequestBattleNetGameList, the difficulty character is kept in the description
	strcpy(pGame->szGameDescription, szStatstring);
	return pGameList[0];
}

//Inlined
static void GATE_JoinGame(uint16_t nGameToken, const char* szGameName, const char* szGamePassword, const char* szServerIp)
{
	CHATDLG_JoinGame(nGameToken, szGameName, szGamePassword, szServerIp);
	GATE_CloseJoinDialog();
	CHATDLG_ShowWaitPopup(D2LANG_GetStringFromTblIndex(0x147B), nullptr);
}

//D2Multi.0x6F9B1920
int32_t __stdcall GATE_JoinGameCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!D2Win_10024_CONTROL_CheckFirstFlag(gpJoinOk_6F9DF94C))
	{
		return 0;
	}

	const Unicode* wszGameName = D2Win_10077_EDITBOX_GetText(gpJoinName_6F9DF954);
	const Unicode* wszGamePassword = D2Win_10077_EDITBOX_GetText(gpJoinPassword_6F9DF958);
	if (!wszGameName)
	{
		return 0;
	}

	char szGameName[256];
	char szGamePassword[256];
	Unicode::unicode2Win(szGameName, wszGameName, std::size(szGameName));
	Unicode::unicode2Win(szGamePassword, wszGamePassword, std::size(szGamePassword));
	FOG_10138(szGameName);
	FOG_10138(szGamePassword);

	if (D2MCPCLIENT_10002())
	{
		GATE_JoinGame(0, szGameName, szGamePassword, nullptr);
		return 1;
	}

	for (int32_t i = 0; i < gnGameListCount_6F9DFA4C; ++i)
	{
		const D2MultiGameListEntryStrc* pGame = &gaDisplayedGames_6F9C2B48[i];
		if (!strcmp(pGame->szGameName, szGameName))
		{
			GATE_JoinGame(pGame->nGameToken, szGameName, szGamePassword, FOG_inet_ntoa(pGame->nIpAddress));
			return 1;
		}
	}

	// The game isn't in the list, look for it on Battle.net
	D2MultiGameListEntryStrc tGame;
	if (!GATE_FindBattleNetGame(szGameName, szGamePassword, &tGame))
	{
		CHATDLG_ShowPopup(D2LANG_GetStringFromTblIndex(0x1411), nullptr);
		return 0;
	}

	if (!strcmp(tGame.szGameName, szGameName))
	{
		GATE_JoinGame(tGame.nGameToken, szGameName, szGamePassword, FOG_inet_ntoa(tGame.nIpAddress));
		return 1;
	}

	return 0;
}

//D2Multi.0x6F9B1CA0
int32_t __stdcall GATE_JoinButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_CloseDialogs();
	gnMCPState_6F9C26F8 = D2MULTI_MCPSTATE_GAMELIST;
	GATE_CreateJoinDialog();
	BUTTON_SetIsPressed(gpChannelButton_6F9C2674, 0);
	BUTTON_SetIsPressed(gpCreateButton_6F9C2670, 0);
	BUTTON_SetIsPressed(gpLadderButton_6F9C267C, 0);
	return 1;
}

//D2Multi.0x6F9B1CF0
int32_t __stdcall GATE_CreateButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHATDLG_CloseDialogs();
	GATE_CreateCreateDialog();
	BUTTON_SetIsPressed(gpChannelButton_6F9C2674, 0);
	BUTTON_SetIsPressed(gpJoinButton_6F9C2678, 0);
	BUTTON_SetIsPressed(gpLadderButton_6F9C267C, 0);
	return 1;
}

//D2Multi.0x6F9B1D30
int32_t __stdcall GATE_ClickBoxCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return 1;
}

//Inlined
static void GATE_SelectDifficulty(int32_t nDifficulty)
{
	BUTTON_SetIsPressed(gpCreateNormal_6F9DF9CC, nDifficulty == 0);
	BUTTON_SetIsPressed(gpCreateNightmare_6F9DF9D0, nDifficulty == 1);
	BUTTON_SetIsPressed(gpCreateHell_6F9DF9D4, nDifficulty == 2);
	gnSelectedDifficulty_6F9DFA50 = nDifficulty;
	gpConfig_6F9C26F0->nArenaDifficulty = nDifficulty;
}

//D2Multi.0x6F9B1D40
int32_t __stdcall GATE_NormalDifficultyCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_SelectDifficulty(0);
	return 1;
}

//D2Multi.0x6F9B1D90
int32_t __stdcall GATE_NightmareDifficultyCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_SelectDifficulty(1);
	return 1;
}

//D2Multi.0x6F9B1DE0
int32_t __stdcall GATE_HellDifficultyCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_SelectDifficulty(2);
	return 1;
}

//D2Multi.0x6F9B1E30
void __fastcall GATE_ShowOwnProfile(const char* szCharacterName, BOOL bHardcore, BOOL bExpansion)
{
	char szSex[12];
	char szLocation[44];
	char szDescription[204];
	const char* szAccountName = gpConfig_6F9C26F0->szAccountName;

	GATE_ResetButtonStates();
	if (!CHATDLG_ReadProfile(szAccountName, szSex, szLocation, szDescription))
	{
		return;
	}

	CHATDLG_CloseDialogs();
	gnProfileMode_6F9DFA2C = PROFILEMODE_EDIT;
	gpProfileEditBackground_6F9DF9F8 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEEDIT_BACKGROUND]);
	gpProfileEditName_6F9DF9FC = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEEDIT_NAME]);
	D2Win_10045(gpProfileEditName_6F9DF9FC, szAccountName);
	gpProfileEditSex_6F9DFA00 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEEDIT_SEX]);
	D2Win_10076(gpProfileEditSex_6F9DFA00, szSex);
	D2Win_10081(gpProfileEditSex_6F9DFA00, 8);
	gpProfileEditLocation_6F9DFA04 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEEDIT_LOCATION]);
	D2Win_10076(gpProfileEditLocation_6F9DFA04, szLocation);
	D2Win_10081(gpProfileEditLocation_6F9DFA04, 40);
	gpProfileEditDescription_6F9DFA08 = (D2WinEditBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEEDIT_DESCRIPTION]);
	D2Win_10076(gpProfileEditDescription_6F9DFA08, szDescription);
	D2Win_10081(gpProfileEditDescription_6F9DFA08, 200);

	gpProfileCancel_6F9DFA0C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_CANCEL]);
	D2Win_10031(gpProfileCancel_6F9DFA0C);
	gpProfileOk_6F9DFA20 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_OK]);
	if (!gbIsOpenBattleNet_6F9C286C)
	{
		gpProfileLadder_6F9DFA24 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_LADDER]);
	}

	GATE_CreateProfileLabels();

	D2Win_10080_EDITBOX_SetNextEditBox(gpProfileEditDescription_6F9DFA08, gpProfileEditSex_6F9DFA00);
	D2Win_10080_EDITBOX_SetNextEditBox(gpProfileEditSex_6F9DFA00, gpProfileEditLocation_6F9DFA04);
	D2Win_10080_EDITBOX_SetNextEditBox(gpProfileEditLocation_6F9DFA04, gpProfileEditDescription_6F9DFA08);

	if (!szSex[0] && !szLocation[0] && !szDescription[0])
	{
		D2Win_10012(gpProfileEditSex_6F9DFA00);
	}
	else
	{
		D2Win_10012(gpProfileEditDescription_6F9DFA08);
		D2Win_10082(gpProfileEditDescription_6F9DFA08);
	}

	strcpy(gszProfileCharacterName_6F9DFA54, szCharacterName);
	gbProfileExpansion_6F9DFA68 = bExpansion;
	gbProfileHardcore_6F9DFA64 = bHardcore;
}

//D2Multi.0x6F9B20F0
void __fastcall GATE_ShowProfile(const char* szUserName, const char* szCharacterName, BOOL bHardcore, BOOL bExpansion)
{
	char szSex[12];
	char szLocation[44];
	char szDescription[204];
	const char* szAccountName = CHATDLG_GetAccountName(szUserName);

	GATE_ResetButtonStates();
	if (!CHATDLG_ReadProfile(szAccountName, szSex, szLocation, szDescription))
	{
		return;
	}

	CHATDLG_CloseDialogs();
	gnProfileMode_6F9DFA2C = PROFILEMODE_VIEW;
	gpProfileViewBackground_6F9DF9E4 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEVIEW_BACKGROUND]);
	gpProfileViewName_6F9DF9E8 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEVIEW_NAME]);
	D2Win_10045(gpProfileViewName_6F9DF9E8, szAccountName);
	gpProfileViewSex_6F9DF9EC = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEVIEW_SEX]);
	D2Win_10045(gpProfileViewSex_6F9DF9EC, szSex);
	gpProfileViewLocation_6F9DF9F0 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEVIEW_LOCATION]);
	D2Win_10045(gpProfileViewLocation_6F9DF9F0, szLocation);
	gpProfileViewDescription_6F9DF9F4 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILEVIEW_DESCRIPTION]);
	for (const char* szLine = strtok(szDescription, "\r\n"); szLine; szLine = strtok(nullptr, "\r\n"))
	{
		D2Win_10045(gpProfileViewDescription_6F9DF9F4, szLine);
	}

	gpProfileOk_6F9DFA20 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_OK]);
	D2Win_10031(gpProfileOk_6F9DFA20);
	if (!gbIsOpenBattleNet_6F9C286C)
	{
		gpProfileLadder_6F9DFA24 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_PROFILE_LADDER]);
	}

	GATE_CreateProfileLabels();
	CHATDLG_FocusChatEditBox();

	strcpy(gszProfileCharacterName_6F9DFA54, szCharacterName);
	gbProfileHardcore_6F9DFA64 = bHardcore;
	gbProfileExpansion_6F9DFA68 = bExpansion;
}

//D2Multi.0x6F9B2340
void __fastcall GATE_CloseProfileDialog()
{
	GATE_CloseProfileControls();
}

//D2Multi.0x6F9B2420
int32_t __stdcall GATE_ProfileLadderCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_CloseProfileControls();

	if (gbProfileExpansion_6F9DFA68)
	{
		if (gbProfileHardcore_6F9DFA64)
		{
			CHATDLG_ShowExpansionHardcoreCharacterLadder();
		}
		else
		{
			CHATDLG_ShowExpansionStandardCharacterLadder();
		}
	}
	else
	{
		if (gbProfileHardcore_6F9DFA64)
		{
			CHATDLG_ShowHardcoreCharacterLadder();
		}
		else
		{
			CHATDLG_ShowStandardCharacterLadder();
		}
	}

	CHATDLG_RequestCharacterLadder(gszProfileCharacterName_6F9DFA54, gbProfileHardcore_6F9DFA64, gbProfileExpansion_6F9DFA68);
	return 1;
}

//D2Multi.0x6F9B2550
void __fastcall GATE_GetProfileCharacterName(char* szCharacterName)
{
	SStrCopy(szCharacterName, gszProfileCharacterName_6F9DFA54, INT_MAX);
}

//D2Multi.0x6F9B2570
int32_t __stdcall GATE_ProfileCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_CloseProfileControls();
	return 1;
}

//D2Multi.0x6F9B2660
int32_t __stdcall GATE_ProfileOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (gnProfileMode_6F9DFA2C == PROFILEMODE_EDIT)
	{
		const Unicode* wszSex = D2Win_10077_EDITBOX_GetText(gpProfileEditSex_6F9DFA00);
		const Unicode* wszLocation = D2Win_10077_EDITBOX_GetText(gpProfileEditLocation_6F9DFA04);
		const Unicode* wszDescription = D2Win_10077_EDITBOX_GetText(gpProfileEditDescription_6F9DFA08);

		char szSex[12];
		char szLocation[44];
		char szDescription[204];
		Unicode::unicode2Win(szSex, wszSex, 8);
		Unicode::unicode2Win(szLocation, wszLocation, 40);
		Unicode::unicode2Win(szDescription, wszDescription, 200);
		if (!CHATDLG_WriteProfile(gpConfig_6F9C26F0->szAccountName, szSex, szLocation, szDescription))
		{
			return 1;
		}
	}

	GATE_CloseProfileControls();
	return 1;
}

//D2Multi.0x6F9B27E0
void __fastcall GATE_ShowHelp()
{
	CHATDLG_CloseDialogs();
	const BOOL bChatNotCreated = CHATDLG_IsChatNotCreated();
	GATE_ResetButtonStates();

	gpHelpBackground_6F9DFA3C = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_HELP_BACKGROUND]);
	gpHelpTitle_6F9DFA30 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_HELP_TITLE]);
	D2Win_10044(gpHelpTitle_6F9DFA30, D2LANG_GetStringFromTblIndex(bChatNotCreated ? 0x14BC : 0x2AE));
	gpHelpText_6F9DFA34 = (D2WinTextBoxStrc*)CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_HELP_TEXT]);

	if (!bChatNotCreated)
	{
		GATE_ShowHelpLines(gaHelpChatStringIds, std::size(gaHelpChatStringIds));
	}

	GATE_ShowHelpLines(gaHelpCommonStringIds, std::size(gaHelpCommonStringIds));

	if (!bChatNotCreated)
	{
		GATE_ShowHelpLines(gaHelpCommandsStringIds, std::size(gaHelpCommandsStringIds));
	}

	gpHelpOk_6F9DFA38 = CONTROL_Create(&gaControlInits_6F9BC138[CTRLINIT_HELP_OK]);
	D2Win_10031(gpHelpOk_6F9DFA38);
	gbHelpOpened_6F9DFA40 = TRUE;
	D2Win_10053(gpHelpText_6F9DFA34, 0);
}

//D2Multi.0x6F9B35E0
int32_t __fastcall GATE_CloseHelp()
{
	CONTROL_Destroy(&gpHelpBackground_6F9DFA3C);
	CONTROL_Destroy(&gpHelpTitle_6F9DFA30);
	CONTROL_Destroy(&gpHelpText_6F9DFA34);
	CONTROL_Destroy(&gpHelpOk_6F9DFA38);
	gbHelpOpened_6F9DFA40 = FALSE;
	D2Win_10031(gpQuitButton_6F9C2680);
	return 1;
}
