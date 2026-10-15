#include "CharSel.h"

#include <cstdio>
#include <cstring>
#include <ctime>
#include <iterator>

#include <D2BitManip.h>
#include <D2Lang.h>
#include <D2StrTable.h>
#include <Fog.h>
#include <Storm.h>
#include <D2MCPClient.h>
#include <D2Sound.h>
#include <D2WinMain.h>
#include <D2WinButton.h>
#include <D2WinImage.h>
#include <D2WinTextBox.h>
#include <D2WinTimer.h>
#include <D2WinSmack.h>

#include "BNet.h"
#include "MainMenus.h"
#include "SaveLoad.h"


constexpr int32_t CHARSEL_MAX_VISIBLE_SLOTS = 8;

//D2Launch.0x6FA3B880
D2WinControlStrc* sgpRealmSelectOkButton;
//D2Launch.0x6FA3B884
D2WinImageStrc* sgpCreateNewCharacterDisabledImage;
//D2Launch.0x6FA3B888
D2WinButtonStrc* sgpScrollUpButton;
//D2Launch.0x6FA3B88C
D2WinTextBoxStrc* sgpRealmNameTextBox;
//D2Launch.0x6FA3B890
D2WinTextBoxStrc* sgpRealmListTextBox;
//D2Launch.0x6FA3B894
int32_t sganCharacterSlotY[CHARSEL_MAX_VISIBLE_SLOTS];
//D2Launch.0x6FA3B8B4
D2WinTextBoxStrc* sgpSelectedCharacterNameTextBox;
//D2Launch.0x6FA3B8B8
D2WinImageStrc* sgpSelectionImage;
//D2Launch.0x6FA3B8BC
D2WinControlStrc* sgpRealmSelectBackground;
//D2Launch.0x6FA3B8C0
D2WinControlStrc* sgpOkButton;
//D2Launch.0x6FA3B8C8
char sgszSelectedRealmName[256];
//D2Launch.0x6FA3B9C8
D2WinTextBoxStrc* sgpSelectedCharacterClassTextBox;
//D2Launch.0x6FA3B9CC
D2WinTextBoxStrc* sgpScrollBarTextBox;
//D2Launch.0x6FA3B9D0
D2WinTextBoxStrc* sgpSelectedCharacterRealmTextBox;
//D2Launch.0x6FA3B9D4
D2WinButtonStrc* sgpScrollDownButton;
//D2Launch.0x6FA3B9D8
Unicode sgawszTestRealmNames[7][256];
//D2Launch.0x6FA3C7D8
char sgszPreferredRealmName[256];
//D2Launch.0x6FA3C8D8
D2WinControlStrc* sgpDeleteButton;
//D2Launch.0x6FA3C8DC
D2WinControlStrc* sgpExitButton;
//D2Launch.0x6FA3C8E0
D2WinControlStrc* sgpRealmSelectCancelButton;
//D2Launch.0x6FA3C8E4
D2WinTextBoxStrc* sgpCharacterSlotClickTextBoxes[CHARSEL_MAX_VISIBLE_SLOTS];
//D2Launch.0x6FA3C904
D2WinTextBoxStrc* sgpRealmSelectTitleTextBox;
//D2Launch.0x6FA3C908
BOOL sgbRealmSelectionOpen;
//D2Launch.0x6FA3C90C
D2WinControlStrc* sgpCreateNewCharacterButton;
//D2Launch.0x6FA3C910
D2WinTextBoxStrc* sgpCharacterSlotTextBoxes[CHARSEL_MAX_VISIBLE_SLOTS];
//D2Launch.0x6FA3C930
D2WinTextBoxStrc* sgpRealmSelectDescriptionTextBox;
//D2Launch.0x6FA3C938
char sgszSaveFileName[256];
//D2Launch.0x6FA3CA38
D2WinControlStrc* sgpConvertToExpansionButton;
//D2Launch.0x6FA3CA3C
D2WinControlStrc* sgpChangeRealmButton;
//D2Launch.0x6FA3CA40
BOOL sgbOperationInProgress;
//D2Launch.0x6FA3CA44
BOOL gbAllowHardcore;
//D2Launch.0x6FA3CA48
uint8_t sgbTestRealmNamesInitialized;
//D2Launch.0x6FA3CA4C
int32_t sgnRealmState;
//D2Launch.0x6FA3CA50
const char* sgszRealmToLoad;
//D2Launch.0x6FA3CA54
DWORD sgdwRealmStateTickCount;
//D2Launch.0x6FA3CA58
BOOL sgbCreateNewCharacterDisabled;
//D2Launch.0x6FA3CA5C
D2CharSelNodeStrc* sgptCharacterList;
//D2Launch.0x6FA3CA60
D2CharSelNodeStrc* sgptSelected;
//D2Launch.0x6FA3CA64
int32_t sgnCharacterCount;
//D2Launch.0x6FA3CA68
int32_t sgnScrollOffset;
//D2Launch.0x6FA3CA6C
int32_t sgnScrollBarPosition;
//D2Launch.0x6FA3CA70
D2WinTextBoxStrc* sgpRealmStatusTextBox;
//D2Launch.0x6FA3CA74
D2WinTextBoxStrc* sgpMessageTextBox;
//D2Launch.0x6FA3CA78
BOOL sgbCharacterListFull;
//D2Launch.0x6FA3CA7C
int32_t sgnCharactersToCreate;
//D2Launch.0x6FA3CA80
int32_t sgnLocalSaveFileCount;
//D2Launch.0x6FA3CA88
D2RealmCharListCacheStrc* sgpRealmCharListCache;
//D2Launch.0x6FA3CA8C
DWORD sgdwLastClickTickCount;

//D2Launch.0x6FA33218
int32_t sgnSelectedIndex = -1;
//D2Launch.0x6FA3321C
int32_t sgnCreateNewCharacterIndex = -999;
//D2Launch.0x6FA33220
int32_t sgnMoreCharactersIndex = -999;
//D2Launch.0x6FA33224
int32_t sgnVisibleSlotCount = 5;


// Helper function, inlined in the original game
static D2CharSelNodeStrc* CHARSEL_GetNodeFromIndex(int32_t nIndex)
{
	int32_t nCurrentIndex = 0;
	for (D2CharSelNodeStrc* pNode = sgptCharacterList; pNode; pNode = pNode->pNext)
	{
		if (nIndex == nCurrentIndex)
		{
			return pNode;
		}

		++nCurrentIndex;
	}

	return nullptr;
}

// Helper function, inlined in the original game
static uint8_t CHARSEL_GetDisplayClass(const D2CharSelNodeStrc* pNode, int32_t* pMode)
{
	uint8_t nClass = pNode->nClass;
	*pMode = 5;

	if (pNode->nFlags & 4)
	{
		if (pNode->nFlags & 8)
		{
			BOOL bGhostVariant = TRUE;
			switch (nClass)
			{
			case 0:
			case 1:
			case 6:
			case 9:
				bGhostVariant = FALSE;
				break;

			default:
				break;
			}

			nClass = (bGhostVariant != 0) + 8;
			*pMode = 5;
		}
		else if (FOG_IsExpansion() || pNode->nClass < 5)
		{
			*pMode = 1;
		}
	}

	return nClass;
}

// Helper function, inlined in the original game
static D2CompositeUnitStrc* CHARSEL_CreateCompositeUnit(D2CharSelNodeStrc* pNode)
{
	int32_t nMode = 5;
	const uint8_t nClass = CHARSEL_GetDisplayClass(pNode, &nMode);

	D2CompositeUnitStrc* hUnit = D2Win_10144(nClass, nMode, pNode->pComponents, pNode->pComponentColors);
	if (!hUnit)
	{
		for (int32_t i = 0; i < 16; ++i)
		{
			pNode->pComponents[i] = 0;
			pNode->pComponentColors[i] = 0xFF;
		}

		pNode->pComponents[1] = 1;
		hUnit = D2Win_10144(7, 5, pNode->pComponents, pNode->pComponentColors);
	}

	return hUnit;
}

// Helper function, inlined in the original game
static int32_t CHARSEL_GetCompositeUnitFlags(uint16_t nSaveFlags, int32_t nFlags)
{
	if (nSaveFlags & 8)
	{
		nFlags |= gdwBitMasks[4];
	}
	else
	{
		nFlags &= gdwInvBitMasks[4];
	}

	if (nSaveFlags & 4)
	{
		nFlags |= gdwBitMasks[5];
	}
	else
	{
		nFlags &= gdwInvBitMasks[5];
	}

	return nFlags;
}

// Helper function, inlined in the original game
static void CHARSEL_EnableButtons()
{
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpDeleteButton, sgnCharacterCount > 0 && sgnSelectedIndex > sgnCreateNewCharacterIndex);
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpOkButton, sgnCharacterCount > 0);
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpExitButton, 1);
	D2Win_10025_CONTROL_ToggleFirstFlag(&sgpScrollUpButton->controlHeader, 1);
	D2Win_10025_CONTROL_ToggleFirstFlag(&sgpScrollDownButton->controlHeader, 1);

	if (FOG_IsExpansion())
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(sgpConvertToExpansionButton, 1);
		D2Win_10025_CONTROL_ToggleFirstFlag(sgpCreateNewCharacterButton, sgbCreateNewCharacterDisabled == 0);
	}
}

// Helper function, inlined in the original game
static void CHARSEL_DisableButtons()
{
	D2Win_10047(sgpSelectedCharacterNameTextBox);
	D2Win_10047(sgpSelectedCharacterClassTextBox);
	D2Win_10047(sgpSelectedCharacterRealmTextBox);
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpDeleteButton, 0);
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpOkButton, 0);
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpExitButton, 0);
	D2Win_10025_CONTROL_ToggleFirstFlag(&sgpScrollUpButton->controlHeader, 0);
	D2Win_10025_CONTROL_ToggleFirstFlag(&sgpScrollDownButton->controlHeader, 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpSelectionImage->controlHeader, 0);

	if (FOG_IsExpansion())
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(sgpConvertToExpansionButton, 0);
		D2Win_10025_CONTROL_ToggleFirstFlag(sgpCreateNewCharacterButton, 0);
	}
	else
	{
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCreateNewCharacterDisabledImage->controlHeader, 0);
	}
}

// Helper function, inlined in the original game
static void CHARSEL_SaveSelectedRealmAsPreferred()
{
	SStrCopy(sgszPreferredRealmName, sgszSelectedRealmName, 0x7FFFFFFF);
	SRegSaveString("Diablo II", "Preferred Realm", 0, sgszPreferredRealmName);

	if (gnGameType == MODE_CLOSED)
	{
		MENU_DestroySubChildren();
		CHARSEL_EnableButtons();
		sgnSelectedIndex = 0;
		CHARSEL_UpdateSelection();
	}

	sgbRealmSelectionOpen = FALSE;
}

// Helper function, inlined in the original game
static void CHARSEL_AddCreateNewCharacterNode()
{
	const Unicode* wszName = D2LANG_GetStringFromTblIndex(5145);
	const Unicode* wszText = D2LANG_GetStringFromTblIndex(gnGameType == MODE_CLOSED ? 5147 : 5146);
	sgnCreateNewCharacterIndex = sgnCharacterCount;
	CHARSEL_AddSpecialNode(wszName, wszText, CHARSELNODE_CREATE_NEW, 12);
}

// Helper function, inlined in the original game
static void CHARSEL_LoadCharacters(const char* szRealmName)
{
	if (gnGameType == MODE_CLOSED)
	{
		D2Win_10047(sgpRealmNameTextBox);
		D2Win_10046(sgpRealmNameTextBox, szRealmName, 0);

		CHARSEL_FreeCharacterList();

		sgbCreateNewCharacterDisabled = FALSE;
		D2Win_10025_CONTROL_ToggleFirstFlag(sgpCreateNewCharacterButton, 1);

		if (const uint8_t* pPacket = CHARSEL_GetCachedRealmCharList(szRealmName))
		{
			CHARSEL_LoadRealmCharacters(szRealmName, pPacket, FALSE);
		}
		else if (!gptComInt->IsConnected())
		{
			MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5347), MENU_ShowMainMenu);
		}
		else
		{
			sgnRealmState = 1;
			sgszRealmToLoad = szRealmName;
		}
	}
	else if (gnGameType == MODE_LOCAL || gnGameType == MODE_OPEN || gnGameType == MODE_TCPIP)
	{
		CHARSEL_FreeCharacterList();

		if (!FOG_IsExpansion())
		{
			CHARSEL_AddCreateNewCharacterNode();
		}

		CHARSEL_LoadLocalCharacters();
	}
}

// Helper function, inlined in the original game
static void CHARSEL_SelectPreferredRealm()
{
	if (SRegLoadString("Diablo II", "Preferred Realm", 0, sgszPreferredRealmName, sizeof(sgszPreferredRealmName)))
	{
		for (int32_t i = 0; i < MENU_GetRealmCount(); ++i)
		{
			const char* szRealmName = MENU_GetRealmName(i);
			if (!szRealmName)
			{
				break;
			}

			if (!SStrCmpI(sgszPreferredRealmName, szRealmName, 0x7FFFFFFF))
			{
				return;
			}
		}
	}

	BNGatewayAccess* pGatewayAccess = gptComInt->GetBnGatewayAccess();
	SStrCopy(sgszPreferredRealmName, BNGATEWAY_GetRealm(pGatewayAccess, pGatewayAccess->nCurrentGateway), 0x7FFFFFFF);
	SRegSaveString("Diablo II", "Preferred Realm", 0, sgszPreferredRealmName);

	for (int32_t i = 0; i < MENU_GetRealmCount(); ++i)
	{
		const char* szRealmName = MENU_GetRealmName(i);
		if (!szRealmName)
		{
			break;
		}

		if (!SStrCmpI(sgszPreferredRealmName, szRealmName, 0x7FFFFFFF))
		{
			return;
		}
	}

	SStrCopy(sgszPreferredRealmName, MENU_GetRealmCount() > 0 ? MENU_GetRealmName(0) : nullptr, 0x7FFFFFFF);
	SRegSaveString("Diablo II", "Preferred Realm", 0, sgszPreferredRealmName);
}

//D2Launch.0x6FA12FC0
uint8_t* __fastcall CHARSEL_GetCachedRealmCharList(const char* szRealmName)
{
	const uint32_t dwHash = SStrHash(szRealmName, 0, 0);
	const int32_t nTickCount = GetTickCount();

	for (D2RealmCharListCacheStrc* pCache = sgpRealmCharListCache; pCache; pCache = pCache->pNext)
	{
		if (pCache->dwRealmNameHash == dwHash && nTickCount <= (int32_t)pCache->dwExpirationTickCount)
		{
			return pCache->pCharListPacket;
		}
	}

	return nullptr;
}

//D2Launch.0x6FA13000
void __fastcall CHARSEL_CacheRealmCharList(const char* szRealmName, const uint8_t* pPacket, size_t nPacketSize)
{
	const uint32_t dwHash = SStrHash(szRealmName, 0, 0);

	for (D2RealmCharListCacheStrc* pCache = sgpRealmCharListCache; pCache; pCache = pCache->pNext)
	{
		if (pCache->dwRealmNameHash == dwHash)
		{
			SMemFree(pCache->pCharListPacket, __FILE__, __LINE__, 0);
			pCache->pCharListPacket = (uint8_t*)SMemAlloc(nPacketSize, __FILE__, __LINE__, 0);
			memcpy(pCache->pCharListPacket, pPacket, nPacketSize);
			pCache->dwExpirationTickCount = GetTickCount() + 300000;
			return;
		}
	}

	D2RealmCharListCacheStrc* pCache = (D2RealmCharListCacheStrc*)SMemAlloc(sizeof(D2RealmCharListCacheStrc), __FILE__, __LINE__, 0);
	pCache->dwRealmNameHash = dwHash;
	pCache->pCharListPacket = (uint8_t*)SMemAlloc(nPacketSize, __FILE__, __LINE__, 0);
	memcpy(pCache->pCharListPacket, pPacket, nPacketSize);
	pCache->dwExpirationTickCount = GetTickCount() + 300000;
	pCache->pNext = sgpRealmCharListCache;
	sgpRealmCharListCache = pCache;
}

//D2Launch.0x6FA130E0
void __fastcall CHARSEL_FreeRealmCharListCache()
{
	D2RealmCharListCacheStrc* pCache = sgpRealmCharListCache;
	while (pCache)
	{
		D2RealmCharListCacheStrc* pNext = pCache->pNext;
		SMemFree(pCache->pCharListPacket, __FILE__, __LINE__, 0);
		SMemFree(pCache, __FILE__, __LINE__, 0);
		pCache = pNext;
	}

	sgpRealmCharListCache = nullptr;
	MENU_FreeRealmList();
}

//D2Launch.0x6FA13130
int32_t __stdcall CHARSEL_RealmSelectOkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	CHARSEL_SaveSelectedRealmAsPreferred();
	return 1;
}

//D2Launch.0x6FA13230
int32_t __stdcall CHARSEL_RealmSelectCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	sgbCharacterListFull = FALSE;

	CHARSEL_LoadCharacters(sgszPreferredRealmName);
	CHARSEL_UpdateSelection();
	CHARSEL_UpdateCharacterList();

	if (gnGameType == MODE_CLOSED)
	{
		MENU_DestroySubChildren();
		CHARSEL_EnableButtons();
		sgnSelectedIndex = 0;
		CHARSEL_UpdateSelection();
	}

	sgbRealmSelectionOpen = FALSE;
	return 1;
}

//D2Launch.0x6FA134B0
int32_t __stdcall CHARSEL_RealmListClickCallback(SMSGHANDLER_PARAMS* pMsg)
{
	Unicode::toUtf(sgszSelectedRealmName, D2Win_10048(sgpRealmListTextBox), sizeof(sgszSelectedRealmName));

	sgbCharacterListFull = FALSE;

	CHARSEL_LoadCharacters(sgszSelectedRealmName);
	CHARSEL_UpdateSelection();
	CHARSEL_UpdateCharacterList();
	CHARSEL_FreeSelectedCharacter();
	CHARSEL_DisableButtons();

	if (MENU_IsDoubleClick(pMsg))
	{
		CHARSEL_SaveSelectedRealmAsPreferred();
	}

	return 1;
}

//D2Launch.0x6FA13820
int32_t __stdcall CHARSEL_ChangeRealmCallback(SMSGHANDLER_PARAMS* pMsg)
{
	SStrCopy(sgszSelectedRealmName, sgszPreferredRealmName, 0x7FFFFFFF);

	if (gnGameType != MODE_CLOSED)
	{
		sgbRealmSelectionOpen = TRUE;
		return 1;
	}

	if (FOG_IsExpansion())
	{
		sgpRealmSelectBackground = MENU_CreateSubChild(109);
		D2Win_10033(sgpRealmSelectBackground, 1);
		D2Win_10030_CONTROL_ToggleFourthFlag(sgpRealmSelectBackground, 1);
		sgpRealmSelectTitleTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(110);
		D2Win_10030_CONTROL_ToggleFourthFlag(&sgpRealmSelectTitleTextBox->controlHeader, 1);
		sgpRealmSelectDescriptionTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(111);
		D2Win_10030_CONTROL_ToggleFourthFlag(&sgpRealmSelectDescriptionTextBox->controlHeader, 1);
		sgpRealmListTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(112);
		D2Win_10030_CONTROL_ToggleFourthFlag(&sgpRealmListTextBox->controlHeader, 1);
		sgpRealmSelectOkButton = MENU_CreateSubChild(113);
		D2Win_10030_CONTROL_ToggleFourthFlag(sgpRealmSelectOkButton, 1);
		sgpRealmSelectCancelButton = MENU_CreateSubChild(114);
	}
	else
	{
		sgpRealmSelectBackground = MENU_CreateSubChild(115);
		D2Win_10033(sgpRealmSelectBackground, 1);
		D2Win_10030_CONTROL_ToggleFourthFlag(sgpRealmSelectBackground, 1);
		sgpRealmSelectTitleTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(116);
		D2Win_10030_CONTROL_ToggleFourthFlag(&sgpRealmSelectTitleTextBox->controlHeader, 1);
		sgpRealmSelectDescriptionTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(117);
		D2Win_10030_CONTROL_ToggleFourthFlag(&sgpRealmSelectDescriptionTextBox->controlHeader, 1);
		sgpRealmListTextBox = (D2WinTextBoxStrc*)MENU_CreateSubChild(118);
		D2Win_10030_CONTROL_ToggleFourthFlag(&sgpRealmListTextBox->controlHeader, 1);
		sgpRealmSelectOkButton = MENU_CreateSubChild(119);
		D2Win_10030_CONTROL_ToggleFourthFlag(sgpRealmSelectOkButton, 1);
		sgpRealmSelectCancelButton = MENU_CreateSubChild(120);
	}
	D2Win_10030_CONTROL_ToggleFourthFlag(sgpRealmSelectCancelButton, 1);

	D2Win_10051(sgpRealmSelectTitleTextBox, D2LANG_GetStringFromTblIndex(11057), 0, 0, 0);
	D2Win_10062(sgpRealmSelectDescriptionTextBox, -6, 0);

	for (int32_t i = 0; i < MENU_GetRealmCount(); ++i)
	{
		const char* szRealmName = MENU_GetRealmName(i);
		if (!szRealmName)
		{
			break;
		}

		D2Win_10045(sgpRealmListTextBox, szRealmName);
		if (!SStrCmpI(sgszPreferredRealmName, szRealmName, 0x7FFFFFFF))
		{
			D2Win_10050_TEXTBOX_SetLine(sgpRealmListTextBox, i);
		}
	}

	CHARSEL_FreeSelectedCharacter();
	CHARSEL_DisableButtons();

	sgbRealmSelectionOpen = TRUE;
	return 1;
}

//D2Launch.0x6FA13AE0
const char* __fastcall CHARSEL_GetPreferredRealmName()
{
	return sgszPreferredRealmName;
}

//D2Launch.0x6FA13AF0
void __fastcall CHARSEL_FreeSelectedCharacter()
{
	if (sgptSelected)
	{
		if (sgptSelected->eType == CHARSELNODE_CHARACTER)
		{
			D2Win_10142_CompUnitDestroy(sgptSelected->hUnit, 1);
		}

		D2_FREE(sgptSelected);
		sgptSelected = nullptr;
	}
}

//D2Launch.0x6FA13B40
void __fastcall CHARSEL_UpdateCharacterList()
{
	Unicode wszLevel[10];
	char szText[100];
	Unicode wszLine[100];
	Unicode wszClassName[100];

	D2CharSelNodeStrc* pNode = sgptCharacterList;

	if (FOG_IsExpansion())
	{
		int32_t nY = sganCharacterSlotY[0] - 13;
		int32_t nX = 37;
		int32_t nIndex = 0;

		for (int32_t i = 0; i < sgnVisibleSlotCount; ++i)
		{
			D2Win_10047(sgpCharacterSlotTextBoxes[i]);

			switch (STRTABLE_GetLanguage())
			{
			case LANGUAGE_JAPANESE:
			case LANGUAGE_CHINESETWN:
			case LANGUAGE_POLISH:
				D2Win_10062(sgpCharacterSlotTextBoxes[i], -1, -2);
				break;

			case LANGUAGE_KOREAN:
				D2Win_10062(sgpCharacterSlotTextBoxes[i], -1, -7);
				break;

			default:
				break;
			}
		}

		if (sgpRealmStatusTextBox)
		{
			D2Win_10047(sgpRealmStatusTextBox);
		}

		if (gnGameType == MODE_CLOSED && sgnRealmState)
		{
			return;
		}

		for (; pNode; pNode = pNode->pNext, ++nIndex)
		{
			if (nIndex < sgnScrollOffset || nIndex >= sgnScrollOffset + sgnVisibleSlotCount)
			{
				D2Win_10156(pNode->hUnit, 0);
				continue;
			}

			const int32_t nSlot = nIndex - sgnScrollOffset;
			D2Win_10152(pNode->hUnit, nX + 30);
			D2Win_10153(pNode->hUnit, nY);
			D2Win_10156(pNode->hUnit, CHARSEL_GetCompositeUnitFlags(pNode->nFlags, 1));

			if (pNode->eType == CHARSELNODE_MORE_CHARACTERS)
			{
				D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(11067), 1, 0, 0);
			}
			else if (pNode->eType == CHARSELNODE_CHARACTER)
			{
				const BOOL bHardcore = pNode->nFlags & 4;
				const int32_t nColor = bHardcore ? 1 : 4;

				szText[0] = '\0';
				if (const char* szPlayerTitle = D2Win_10161(pNode->nClass, (pNode->nFlags >> 8) & 0x1F, bHardcore, pNode->nFlags & 0x20))
				{
					D2Win_10046(sgpCharacterSlotTextBoxes[nSlot], szPlayerTitle, nColor);
				}

				strcat(szText, pNode->szName); // NOLINT(clang-diagnostic-deprecated-declarations)
				if (strlen(pNode->szGuildTag))
				{
					sprintf(&szText[strlen(szText)], " {%s}", pNode->szGuildTag);
				}
				D2Win_10046(sgpCharacterSlotTextBoxes[nSlot], szText, nColor);

				CHARSEL_GetClassName(wszClassName, pNode->nClass);

				sprintf(szText, " %d ", pNode->nLevel);
				Unicode::win2Unicode(wszLevel, szText, 9);
				Unicode::strcpy(wszLine, D2LANG_GetStringFromTblIndex(4057));
				Unicode::strcat(wszLine, wszLevel);
				Unicode::strcat(wszLine, wszClassName);
				D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], wszLine, 0, 0, 0);

				if (pNode->nFlags & 0x20)
				{
					D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(22731), 2, 0, 0);
				}

				if (pNode->bLadder)
				{
					D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(10927), 4, 0, 0);
				}

				const uint32_t nDays = CHARSEL_GetDaysBeforeExpiration(pNode->dwExpirationTime);
				if (gnGameType == MODE_CLOSED && nDays <= 60)
				{
					int32_t nExpirationColor = 1;
					int16_t nStringId = 0;
					if (nDays == 0)
					{
						nStringId = 11134;
					}
					else if (nDays < 2)
					{
						nStringId = 11132;
					}
					else
					{
						nStringId = 11133;
						if (nDays >= 15)
						{
							nExpirationColor = 0;
						}
					}

					Unicode::sprintf(100, wszLine, D2LANG_GetStringFromTblIndex(nStringId), nDays);
					D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], wszLine, nExpirationColor, 0, 0);
				}
			}

			if (nX == 37)
			{
				nX = 309;
			}
			else
			{
				nX = 37;
				nY += 93;
			}
		}

		return;
	}

	int32_t nY = sganCharacterSlotY[0] - 13;
	int32_t nIndex = 0;

	D2Win_10027_CONTROL_ToggleThirdFlag(sgpCreateNewCharacterButton, 0);

	for (int32_t i = 0; i < sgnVisibleSlotCount; ++i)
	{
		D2Win_10047(sgpCharacterSlotTextBoxes[i]);
		if (STRTABLE_GetLanguage() == LANGUAGE_KOREAN)
		{
			D2Win_10062(sgpCharacterSlotTextBoxes[i], -1, -5);
		}
	}

	if (sgpRealmStatusTextBox)
	{
		D2Win_10047(sgpRealmStatusTextBox);
	}

	if (gnGameType == MODE_CLOSED && sgnRealmState)
	{
		return;
	}

	for (; pNode; pNode = pNode->pNext, ++nIndex)
	{
		if (nIndex < sgnScrollOffset || nIndex >= sgnScrollOffset + sgnVisibleSlotCount)
		{
			D2Win_10156(pNode->hUnit, 0);
			continue;
		}

		const int32_t nSlot = nIndex - sgnScrollOffset;
		D2Win_10152(pNode->hUnit, 545);
		D2Win_10153(pNode->hUnit, nY);

		if (pNode->eType == CHARSELNODE_CREATE_NEW)
		{
			D2Win_10156(pNode->hUnit, 0);
			IMAGE_SetCoordinates((D2WinImageStrc*)sgpCreateNewCharacterButton, 512, sganCharacterSlotY[nSlot] - 3);
			D2Win_10027_CONTROL_ToggleThirdFlag(sgpCreateNewCharacterButton, 1);
			D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(5145), 1, 0, 0);

			if (gnGameType == MODE_CLOSED && sgbCharacterListFull)
			{
				D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(5142), 0, 0, 0);
				D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(5143), 0, 0, 0);
			}
			else
			{
				D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(5144), 0, 0, 0);
				D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], pNode->wszRealm, 0, 0, 0);
			}
		}
		else
		{
			D2Win_10156(pNode->hUnit, CHARSEL_GetCompositeUnitFlags(pNode->nFlags, 1));

			if (pNode->eType == CHARSELNODE_MORE_CHARACTERS)
			{
				D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(11067), 1, 0, 0);
			}
			else
			{
				D2_ASSERT(pNode->eType == CHARSELNODE_CHARACTER);

				const BOOL bHardcore = pNode->nFlags & 4;
				szText[0] = '\0';
				if (const char* szPlayerTitle = D2Win_10161(pNode->nClass, (pNode->nFlags >> 8) & 0x1F, bHardcore, pNode->nFlags & 0x20))
				{
					strcpy(szText, szPlayerTitle); // NOLINT(clang-diagnostic-deprecated-declarations)
				}

				strcat(szText, pNode->szName); // NOLINT(clang-diagnostic-deprecated-declarations)
				if (strlen(pNode->szGuildTag))
				{
					sprintf(&szText[strlen(szText)], " {%s}", pNode->szGuildTag);
				}
				D2Win_10046(sgpCharacterSlotTextBoxes[nSlot], szText, bHardcore ? 1 : 4);

				CHARSEL_GetClassName(wszClassName, pNode->nClass);

				sprintf(szText, " %d ", pNode->nLevel);
				Unicode::win2Unicode(wszLevel, szText, 9);
				Unicode::strcpy(wszLine, D2LANG_GetStringFromTblIndex(4057));
				Unicode::strcat(wszLine, wszLevel);
				Unicode::strcat(wszLine, wszClassName);
				D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], wszLine, 0, 0, 0);

				if (pNode->nFlags & 0x20)
				{
					D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(11077), 2, 0, 0);
				}

				if (pNode->bLadder)
				{
					D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], D2LANG_GetStringFromTblIndex(10927), 4, 0, 0);
				}

				const uint32_t nDays = CHARSEL_GetDaysBeforeExpiration(pNode->dwExpirationTime);
				if (gnGameType == MODE_CLOSED && nDays <= 60)
				{
					int32_t nExpirationColor = 1;
					int16_t nStringId = 0;
					if (nDays == 0)
					{
						nStringId = 11134;
					}
					else if (nDays < 2)
					{
						nStringId = 11132;
					}
					else
					{
						nStringId = 11133;
						if (nDays >= 15)
						{
							nExpirationColor = 0;
						}
					}

					Unicode::sprintf(100, wszLine, D2LANG_GetStringFromTblIndex(nStringId), nDays);
					D2Win_10051(sgpCharacterSlotTextBoxes[nSlot], wszLine, nExpirationColor, 0, 0);
				}
			}
		}

		nY += 93;
	}
}

//D2Launch.0x6FA14520
Unicode* __fastcall CHARSEL_GetClassName(Unicode* wszBuffer, uint8_t nClass)
{
	switch (nClass)
	{
	case 0:
		return Unicode::strcpy(wszBuffer, D2LANG_GetStringFromTblIndex(4011));

	case 1:
		return Unicode::strcpy(wszBuffer, D2LANG_GetStringFromTblIndex(4010));

	case 2:
		return Unicode::strcpy(wszBuffer, D2LANG_GetStringFromTblIndex(4009));

	case 3:
		return Unicode::strcpy(wszBuffer, D2LANG_GetStringFromTblIndex(4008));

	case 4:
		return Unicode::strcpy(wszBuffer, D2LANG_GetStringFromTblIndex(4007));

	case 5:
		return Unicode::strcpy(wszBuffer, D2LANG_GetStringFromTblIndex(10097));

	case 6:
		return Unicode::strcpy(wszBuffer, D2LANG_GetStringFromTblIndex(10098));

	default:
		return Unicode::strcpy(wszBuffer, D2LANG_GetStringFromTblIndex(5383));
	}
}

//D2Launch.0x6FA14600
uint32_t __fastcall CHARSEL_GetDaysBeforeExpiration(uint32_t dwExpirationTime)
{
	time_t nCurrentTime;
	const uint32_t dwCurrentTime = (uint32_t)time(&nCurrentTime);
	if (dwExpirationTime <= dwCurrentTime)
	{
		return 0;
	}

	return (dwExpirationTime - dwCurrentTime) / 86400;
}

//D2Launch.0x6FA14630
void __fastcall CHARSEL_FreeCharacterList()
{
	D2CharSelNodeStrc* pNode = sgptCharacterList;
	while (pNode)
	{
		D2CharSelNodeStrc* pNext = pNode->pNext;
		D2Win_10142_CompUnitDestroy(pNode->hUnit, 1);
		D2_FREE(pNode);
		pNode = pNext;
	}

	sgptCharacterList = nullptr;
	sgnCharacterCount = 0;
	sgnScrollOffset = 0;
	sgbCharacterListFull = FALSE;

	CHARSEL_FreeSelectedCharacter();
}

//D2Launch.0x6FA146D0
BOOL __fastcall CHARSEL_LoadLocalCharacters()
{
	char szSavePath[1024];
	char szSearchPath[1024];
	uint8_t pStatString[256];
	WIN32_FIND_DATAA findData;

	sgnLocalSaveFileCount = 0;

	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	sprintf(szSearchPath, "%s*.d2s", szSavePath);

	HANDLE hFind = FindFirstFileA(szSearchPath, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return TRUE;
	}

	do
	{
		char* pDest = sgszSaveFileName;
		for (const char* pSrc = findData.cFileName; *pSrc && *pSrc != '.'; ++pSrc)
		{
			*pDest = *pSrc;
			++pDest;
		}
		*pDest = '\0';

		const int32_t nLength = strlen(sgszSaveFileName);
		if (nLength >= 2 && nLength < 16 && sgszSaveFileName[nLength - 1] != '-' && sgszSaveFileName[0] != '_')
		{
			if (SAVE_ReadCharacterPreview(sgszSaveFileName, pStatString))
			{
				CHARSEL_AddCharacter(sgszSaveFileName, nullptr, pStatString, 0, findData.ftLastWriteTime.dwLowDateTime, findData.ftLastWriteTime.dwHighDateTime);
				++sgnLocalSaveFileCount;
			}
		}
	}
	while (FindNextFileA(hFind, &findData));

	FindClose(hFind);
	return TRUE;
}

//D2Launch.0x6FA147F0
BOOL __fastcall CHARSEL_AddCharacter(const char* szName, const char* szRealmName, const uint8_t* pStatString, uint32_t dwExpirationTime, uint32_t dwLastWriteTimeLow, uint32_t dwLastWriteTimeHigh)
{
	D2CharSelNodeStrc* pNode = (D2CharSelNodeStrc*)D2_ALLOC(sizeof(D2CharSelNodeStrc));
	pNode->dwLastWriteTimeLow = dwLastWriteTimeLow;
	pNode->dwLastWriteTimeHigh = dwLastWriteTimeHigh;
	pNode->dwExpirationTime = dwExpirationTime;
	SStrCopy(pNode->szName, szName, 0x7FFFFFFF);

	if (szRealmName)
	{
		Unicode::win2Unicode(pNode->wszRealm, szRealmName, 255);
	}
	else
	{
		pNode->wszRealm[0] = 0;
	}

	pNode->nVersion = FOG_Decode14BitsFromString((uint16_t*)pStatString);
	const uint8_t* pData = pStatString + 2;

	if (!sgbTestRealmNamesInitialized)
	{
		char szTestRealmName[256];

		sgbTestRealmNamesInitialized = 1;

		strcpy(szTestRealmName, "Testv104"); // NOLINT(clang-diagnostic-deprecated-declarations)
		Unicode::win2Unicode(sgawszTestRealmNames[0], szTestRealmName, 255);
		strcpy(szTestRealmName, "FatRealm"); // NOLINT(clang-diagnostic-deprecated-declarations)
		Unicode::win2Unicode(sgawszTestRealmNames[1], szTestRealmName, 255);
		strcpy(szTestRealmName, "BetaWest"); // NOLINT(clang-diagnostic-deprecated-declarations)
		Unicode::win2Unicode(sgawszTestRealmNames[2], szTestRealmName, 255);
		strcpy(szTestRealmName, "BetaEurope"); // NOLINT(clang-diagnostic-deprecated-declarations)
		Unicode::win2Unicode(sgawszTestRealmNames[3], szTestRealmName, 255);
		strcpy(szTestRealmName, "BetaUSWest"); // NOLINT(clang-diagnostic-deprecated-declarations)
		Unicode::win2Unicode(sgawszTestRealmNames[4], szTestRealmName, 255);
		strcpy(szTestRealmName, "BetaUSEast"); // NOLINT(clang-diagnostic-deprecated-declarations)
		Unicode::win2Unicode(sgawszTestRealmNames[5], szTestRealmName, 255);
		strcpy(szTestRealmName, "BetaAsia"); // NOLINT(clang-diagnostic-deprecated-declarations)
		Unicode::win2Unicode(sgawszTestRealmNames[6], szTestRealmName, 255);
	}

	for (int32_t i = 0; i < std::size(sgawszTestRealmNames); ++i)
	{
		if (!Unicode::strcmp(pNode->wszRealm, sgawszTestRealmNames[i]))
		{
			char szCharacterRealmName[256];
			Unicode::unicode2Win(szCharacterRealmName, pNode->wszRealm, 255);
			SAVE_DeleteCharacter(pNode->szName, szCharacterRealmName);
			return FALSE;
		}
	}

	int32_t nComponent = 0;
	for (; nComponent < 11; ++nComponent)
	{
		pNode->pComponents[nComponent] = *pData;
		++pData;
	}
	memset(&pNode->pComponents[nComponent], 0xFF, sizeof(pNode->pComponents) - nComponent);

	pNode->nClass = *pData - 1;
	++pData;

	int32_t nComponentColor = 0;
	for (; nComponentColor < 11; ++nComponentColor)
	{
		pNode->pComponentColors[nComponentColor] = *pData;
		++pData;
	}
	memset(&pNode->pComponentColors[nComponentColor], 0xFF, sizeof(pNode->pComponentColors) - nComponentColor);

	pNode->pNext = nullptr;
	pNode->nLevel = *pData;
	++pData;
	pNode->nFlags = FOG_Decode14BitsFromString((uint16_t*)pData);
	pData += 2;
	pNode->nGuildFlags = FOG_Decode14BitsFromString((uint16_t*)pData);
	pData += 2;

	pNode->bLadder = *pData == 0xFF ? 0 : *pData;
	++pData;
	pNode->unk0x32F = *pData == 0xFF ? 0 : *pData;
	++pData;
	pNode->unk0x330 = *pData == 0xFF ? 0 : *pData;
	++pData;
	strncpy(pNode->szGuildTag, (const char*)pData, 3); // NOLINT(bugprone-not-null-terminated-result)

	pNode->hUnit = CHARSEL_CreateCompositeUnit(pNode);
	D2_ASSERT(pNode->hUnit);

	pNode->eType = CHARSELNODE_CHARACTER;
	D2Win_10149(pNode->hUnit, 0);
	D2Win_10151(pNode->hUnit, 0);
	D2Win_10143(pNode->hUnit, 5);

	if (D2CharSelNodeStrc* pCurrent = sgptCharacterList)
	{
		if (FOG_IsExpansion())
		{
			// Sort by last write time, most recent first
			D2CharSelNodeStrc* pPrevious = nullptr;
			for (; pCurrent; pCurrent = pCurrent->pNext)
			{
				if (dwLastWriteTimeHigh > pCurrent->dwLastWriteTimeHigh || (dwLastWriteTimeHigh == pCurrent->dwLastWriteTimeHigh && dwLastWriteTimeLow > pCurrent->dwLastWriteTimeLow))
				{
					break;
				}

				pPrevious = pCurrent;
			}

			if (pPrevious)
			{
				pNode->pNext = pPrevious->pNext;
				pPrevious->pNext = pNode;
			}
			else
			{
				pNode->pNext = sgptCharacterList;
				sgptCharacterList = pNode;
			}
		}
		else
		{
			while (pCurrent->pNext)
			{
				pCurrent = pCurrent->pNext;
			}

			pCurrent->pNext = pNode;
		}
	}
	else
	{
		pNode->pNext = sgptCharacterList;
		sgptCharacterList = pNode;
	}

	++sgnCharacterCount;
	CHARSEL_UpdateCharacterList();

	const uint8_t nProgression = (pNode->nFlags >> 8) & 0x1F;
	if ((nProgression >= 4 && !(pNode->nFlags & 0x20)) || nProgression >= 5 || (pNode->nFlags & 4))
	{
		if (!gbAllowHardcore)
		{
			SRegSaveValue("Diablo II", "AllowHardcore", 0, 1);
		}

		gbAllowHardcore = TRUE;
	}

	return TRUE;
}

//D2Launch.0x6FA14D30
BOOL __fastcall CHARSEL_UpdateSelection()
{
	Unicode wszLevel[10];
	Unicode wszClassName[100];
	char szText[100];
	Unicode wszLine[100];

	if (FOG_IsExpansion())
	{
		if (!sgnCharacterCount)
		{
			sgnSelectedIndex = 0;
		}

		const int32_t nSlot = sgnSelectedIndex - sgnScrollOffset;
		if (nSlot >= 0 && nSlot < sgnVisibleSlotCount)
		{
			IMAGE_SetCoordinates(sgpSelectionImage, (nSlot % 2) ? 309 : 37, sganCharacterSlotY[nSlot]);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpSelectionImage->controlHeader, 1);
		}
		else
		{
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpSelectionImage->controlHeader, 0);
		}

		D2CharSelNodeStrc* pNode = CHARSEL_GetNodeFromIndex(sgnSelectedIndex);

		D2Win_10025_CONTROL_ToggleFirstFlag(sgpDeleteButton, 1);
		D2Win_10025_CONTROL_ToggleFirstFlag(sgpOkButton, 1);

		if (!pNode)
		{
			D2Win_10025_CONTROL_ToggleFirstFlag(sgpConvertToExpansionButton, 0);
			D2Win_10025_CONTROL_ToggleFirstFlag(sgpDeleteButton, 0);
			D2Win_10025_CONTROL_ToggleFirstFlag(sgpOkButton, 0);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpSelectionImage->controlHeader, 0);
			return TRUE;
		}

		D2Win_10025_CONTROL_ToggleFirstFlag(sgpConvertToExpansionButton, 1);
		if (pNode->nFlags & 0x20)
		{
			D2Win_10025_CONTROL_ToggleFirstFlag(sgpConvertToExpansionButton, 0);
		}

		D2Win_10025_CONTROL_ToggleFirstFlag(sgpCreateNewCharacterButton, sgbCreateNewCharacterDisabled == 0);
		if (gnGameType == MODE_CLOSED && sgbCharacterListFull)
		{
			D2Win_10025_CONTROL_ToggleFirstFlag(sgpCreateNewCharacterButton, 0);
		}

		D2Win_10047(sgpSelectedCharacterNameTextBox);
		D2Win_10046(sgpSelectedCharacterNameTextBox, pNode->szName, 0);
		return TRUE;
	}

	if (!sgnCharacterCount)
	{
		sgnSelectedIndex = 0;
	}

	const int32_t nSlot = sgnSelectedIndex - sgnScrollOffset;
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpDeleteButton, sgnCharacterCount > 0 && sgnSelectedIndex > sgnCreateNewCharacterIndex && sgnSelectedIndex != sgnMoreCharactersIndex);
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpOkButton, 1);

	if (nSlot >= 0 && nSlot < sgnVisibleSlotCount)
	{
		if (sgnSelectedIndex == sgnCreateNewCharacterIndex && sgbCharacterListFull)
		{
			IMAGE_SetCoordinates(sgpCreateNewCharacterDisabledImage, 514, sganCharacterSlotY[nSlot]);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCreateNewCharacterDisabledImage->controlHeader, 1);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpSelectionImage->controlHeader, 0);
		}
		else
		{
			IMAGE_SetCoordinates(sgpSelectionImage, 514, sganCharacterSlotY[nSlot]);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpSelectionImage->controlHeader, 1);
			D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCreateNewCharacterDisabledImage->controlHeader, 0);
		}
	}
	else
	{
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpSelectionImage->controlHeader, 0);
		D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCreateNewCharacterDisabledImage->controlHeader, 0);
	}

	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpScrollUpButton->controlHeader, sgnScrollOffset > 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpScrollDownButton->controlHeader, sgnScrollOffset + sgnVisibleSlotCount < sgnCharacterCount);

	D2CharSelNodeStrc* pNode = CHARSEL_GetNodeFromIndex(sgnSelectedIndex);
	if (!pNode)
	{
		return TRUE;
	}

	if (sgptSelected)
	{
		if (sgptSelected->eType == CHARSELNODE_CHARACTER)
		{
			D2Win_10142_CompUnitDestroy(sgptSelected->hUnit, 1);
		}

		D2_FREE(sgptSelected);
		sgptSelected = nullptr;
	}

	sgptSelected = (D2CharSelNodeStrc*)D2_ALLOC(sizeof(D2CharSelNodeStrc));
	SMemCopy(sgptSelected, pNode, sizeof(D2CharSelNodeStrc));
	sgptSelected->pNext = nullptr;

	if (pNode->eType == CHARSELNODE_CREATE_NEW)
	{
		D2Win_10047(sgpSelectedCharacterNameTextBox);
		D2Win_10051(sgpSelectedCharacterNameTextBox, D2LANG_GetStringFromTblIndex(5145), 1, 0, 0);
		D2Win_10047(sgpSelectedCharacterClassTextBox);
		D2Win_10047(sgpSelectedCharacterRealmTextBox);
		return TRUE;
	}

	if (pNode->eType == CHARSELNODE_MORE_CHARACTERS)
	{
		D2Win_10047(sgpSelectedCharacterNameTextBox);
		D2Win_10051(sgpSelectedCharacterNameTextBox, D2LANG_GetStringFromTblIndex(11067), 1, 0, 0);
		D2Win_10047(sgpSelectedCharacterClassTextBox);
		D2Win_10047(sgpSelectedCharacterRealmTextBox);
		return TRUE;
	}

	sgptSelected->hUnit = CHARSEL_CreateCompositeUnit(sgptSelected);
	D2_ASSERT(sgptSelected->hUnit);

	D2Win_10149(sgptSelected->hUnit, 0);
	D2Win_10151(sgptSelected->hUnit, 0);
	D2Win_10143(sgptSelected->hUnit, 5);
	D2Win_10152(sgptSelected->hUnit, 280);
	D2Win_10153(sgptSelected->hUnit, 370);

	int32_t nFlags = CHARSEL_GetCompositeUnitFlags(sgptSelected->nFlags, 5);
	if (sgptSelected->nFlags & 0x20)
	{
		nFlags |= gdwBitMasks[12];
	}
	else
	{
		nFlags &= gdwInvBitMasks[12];
	}
	D2Win_10156(sgptSelected->hUnit, nFlags);

	D2Win_10047(sgpSelectedCharacterNameTextBox);

	const char* szName = sgptSelected->szName;
	if (strlen(sgptSelected->szGuildTag))
	{
		sprintf(szText, "%s {%s}", sgptSelected->szName, sgptSelected->szGuildTag);
		szName = szText;
	}
	D2Win_10046(sgpSelectedCharacterNameTextBox, szName, 0);

	D2Win_10047(sgpSelectedCharacterClassTextBox);
	CHARSEL_GetClassName(wszClassName, sgptSelected->nClass);

	sprintf(szText, " %d ", pNode->nLevel);
	Unicode::win2Unicode(wszLevel, szText, 9);
	Unicode::strcpy(wszLine, D2LANG_GetStringFromTblIndex(4057));
	Unicode::strcat(wszLine, wszLevel);
	Unicode::strcat(wszLine, wszClassName);
	D2Win_10051(sgpSelectedCharacterClassTextBox, wszLine, 0, 0, 0);

	D2Win_10047(sgpSelectedCharacterRealmTextBox);
	D2Win_10051(sgpSelectedCharacterRealmTextBox, sgptSelected->wszRealm[0] ? sgptSelected->wszRealm : D2LANG_GetStringFromTblIndex(5164), 0, 0, 0);

	if (pNode->nFlags & 0x20)
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(sgpOkButton, 0);
	}

	return TRUE;
}

//D2Launch.0x6FA15520
int32_t __stdcall CHARSEL_CharacterSlotClickCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (sgbRealmSelectionOpen)
	{
		return 1;
	}

	const int32_t nPreviousSelectedIndex = sgnSelectedIndex;
	D2WinTextBoxStrc* pClickedTextBox = (D2WinTextBoxStrc*)pMsg->hWindow;

	int32_t nSlot = 0;
	for (; nSlot < sgnVisibleSlotCount; ++nSlot)
	{
		if (FOG_IsExpansion() && pClickedTextBox == sgpCharacterSlotClickTextBoxes[nSlot])
		{
			break;
		}

		if (pClickedTextBox == sgpCharacterSlotTextBoxes[nSlot])
		{
			break;
		}
	}

	const int32_t nIndex = sgnScrollOffset + nSlot;
	if (sgnCharacterCount < nIndex)
	{
		return 0;
	}

	sgnSelectedIndex = nIndex;
	if (sgnCharacterCount <= 0)
	{
		sgnSelectedIndex = -1;
	}

	if (pMsg->nMessage == WM_LBUTTONDOWN)
	{
		const DWORD dwTickCount = GetTickCount();
		if (sgnSelectedIndex != -1 && sgnSelectedIndex == nPreviousSelectedIndex && dwTickCount - sgdwLastClickTickCount < 500)
		{
			return CHARSEL_OkCallback(pMsg);
		}

		sgdwLastClickTickCount = dwTickCount;
	}

	return CHARSEL_UpdateSelection();
}

//D2Launch.0x6FA15600
void __fastcall CHARSEL_ShowDifficultySelection(int32_t nProgression, BOOL bExpansion)
{
	MENU_DestroySubChildren();

	D2WinControlStrc* pBackground = MENU_CreateSubChild(172);
	D2Win_10033(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);

	D2WinTextBoxStrc* pTitle = (D2WinTextBoxStrc*)MENU_CreateSubChild(171);
	D2Win_10051(pTitle, D2LANG_GetStringFromTblIndex(10019), 7, 0, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pTitle->controlHeader, 1);

	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(168), 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(169), 1);

	D2WinControlStrc* pHellButton = MENU_CreateSubChild(170);
	D2Win_10025_CONTROL_ToggleFirstFlag(pHellButton, 0);
	D2Win_10030_CONTROL_ToggleFourthFlag(pHellButton, 1);

	if ((!bExpansion && nProgression >= 8) || nProgression >= 10)
	{
		D2Win_10025_CONTROL_ToggleFirstFlag(pHellButton, 1);
	}

	MENU_CreateSubChild(173);
}

//D2Launch.0x6FA156C0
int32_t __stdcall CHARSEL_OkCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (sgbOperationInProgress)
	{
		return 1;
	}

	gptParams->nArenaDifficulty = 0;

	if (sgnSelectedIndex == sgnCreateNewCharacterIndex)
	{
		if (gnGameType == MODE_CLOSED && sgbCharacterListFull)
		{
			return 1;
		}

		MENU_CreateNewCharacterCallback(pMsg);

		--sgnCharactersToCreate;
		if (sgnCharactersToCreate <= 0)
		{
			sgbCharacterListFull = TRUE;
		}

		return 1;
	}

	if (sgnSelectedIndex == sgnMoreCharactersIndex)
	{
		D2Win_10047(sgpMessageTextBox);
		D2Win_10051(sgpMessageTextBox, D2LANG_GetStringFromTblIndex(11068), 0, 0, 0);
		D2Win_10051(sgpMessageTextBox, D2LANG_GetStringFromTblIndex(11069), 0, 0, 0);
		return 1;
	}

	if (sgnSelectedIndex == -1)
	{
		return 1;
	}

	D2CharSelNodeStrc* pNode = CHARSEL_GetNodeFromIndex(sgnSelectedIndex);
	if (!pNode)
	{
		return 1;
	}

	if (gnGameType == MODE_CLOSED || gnGameType == MODE_OPEN)
	{
		memcpy(gptParams->nComponents, pNode->pComponents, sizeof(gptParams->nComponents));
		memcpy(gptParams->nComponentsColors, pNode->pComponentColors, sizeof(gptParams->nComponentsColors));
		gptParams->nCharacterLevel = (uint8_t)pNode->nLevel;
		gptParams->bLadder = pNode->bLadder;
		gptParams->nSaveFlags = pNode->nFlags;
	}

	if (pNode->nFlags & 0x20)
	{
		if (!FOG_IsExpansion())
		{
			return 0;
		}
	}

	if ((pNode->nFlags & 4) && (pNode->nFlags & 8) && (gnGameType == MODE_LOCAL || gnGameType == MODE_TCPIP))
	{
		MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5304), MENU_DestroySubChildren);
		return 1;
	}

	if (gnGameType == MODE_LOCAL || (gnGameType == MODE_TCPIP && gptParams->dwGameType == 8))
	{
		const int32_t nProgression = (pNode->nFlags >> 8) & 0x1F;
		if ((!(pNode->nFlags & 0x20) && nProgression >= 4) || nProgression >= 5)
		{
			CHARSEL_ShowDifficultySelection(nProgression, pNode->nFlags & 0x20);
			return 1;
		}
	}

	char szRealmName[256];
	Unicode::unicode2Win(szRealmName, pNode->wszRealm, 255);
	MENU_StartGameWithCharacter(pNode, pNode->nFlags, pNode->nClass, szRealmName);
	return 1;
}

// Helper function, inlined in the original game
static int32_t CHARSEL_StartGameWithDifficulty(uint8_t nDifficulty)
{
	if (sgnSelectedIndex == -1)
	{
		return 1;
	}

	if (D2CharSelNodeStrc* pNode = CHARSEL_GetNodeFromIndex(sgnSelectedIndex))
	{
		char szRealmName[256];

		gptParams->nArenaDifficulty = nDifficulty;
		MENU_DestroySubChildren();
		Unicode::unicode2Win(szRealmName, pNode->wszRealm, 255);
		MENU_StartGameWithCharacter(pNode, pNode->nFlags, pNode->nClass, szRealmName);
	}

	return 1;
}

//D2Launch.0x6FA15960
int32_t __stdcall CHARSEL_NormalDifficultyCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return CHARSEL_StartGameWithDifficulty(0);
}

//D2Launch.0x6FA159F0
int32_t __stdcall CHARSEL_NightmareDifficultyCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return CHARSEL_StartGameWithDifficulty(1);
}

//D2Launch.0x6FA15A80
int32_t __stdcall CHARSEL_HellDifficultyCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return CHARSEL_StartGameWithDifficulty(2);
}

//D2Launch.0x6FA15B10
int32_t __stdcall CHARSEL_ConvertToExpansionCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!FOG_IsExpansion())
	{
		return 1;
	}

	MENU_DestroySubChildren();

	D2WinControlStrc* pBackground = MENU_CreateSubChild(218);
	D2Win_10033(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(219), 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(220), 1);

	D2WinTextBoxStrc* pText = (D2WinTextBoxStrc*)MENU_CreateSubChild(221);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pText->controlHeader, 1);
	D2Win_10051(pText, D2LANG_GetStringFromTblIndex(22734), 0, 0, 0);
	D2Win_10051(pText, D2LANG_GetStringFromTblIndex(22735), 0, 0, 0);
	D2Win_10051(pText, D2LANG_GetStringFromTblIndex(22736), 0, 0, 0);
	return 1;
}

//D2Launch.0x6FA15BD0
int32_t __stdcall CHARSEL_ConvertToExpansionCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (FOG_IsExpansion())
	{
		MENU_DestroySubChildren();
	}

	return 1;
}

//D2Launch.0x6FA15BF0
int32_t __stdcall CHARSEL_ConvertToExpansionConfirmCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (!FOG_IsExpansion())
	{
		return 1;
	}

	D2CharSelNodeStrc* pNode = CHARSEL_GetNodeFromIndex(sgnSelectedIndex);
	if (pNode)
	{
		if (pNode->nFlags & 0x20)
		{
			return 1;
		}

		BOOL bConverted = FALSE;
		if (pNode->wszRealm[0])
		{
			char szRealmName[256];
			Unicode::unicode2Win(szRealmName, pNode->wszRealm, 255);
			if (MENU_ConvertRealmCharacterToExpansion(pNode, szRealmName))
			{
				bConverted = TRUE;
			}
			else
			{
				if (D2MCPCLIENT_10046() != 123)
				{
					MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5211), CHARSEL_CreateMenu);
					sgbOperationInProgress = FALSE;
					return 1;
				}

				Unicode wszMessage[256];
				Unicode wszName[256];
				Unicode::win2Unicode(wszName, pNode->szName, 256);
				Unicode::sprintf(256, wszMessage, D2LANG_GetStringFromTblIndex(10075), wszName);
				MENU_ShowMessage(wszMessage, CHARSEL_CreateMenu);
				sgbOperationInProgress = FALSE;
				return 1;
			}
		}
		else if (SAVE_ConvertCharacterToExpansion(pNode->szName))
		{
			bConverted = TRUE;
		}
		else
		{
			MENU_ShowClassicMessageWithButton(D2LANG_GetStringFromTblIndex(21872), CHARSEL_CreateMenu, TRUE);
		}

		if (bConverted)
		{
			pNode->nFlags |= 0x20;
			CHARSEL_UpdateCharacterList();
			MENU_DestroySubChildren();
		}
	}

	D2Win_10025_CONTROL_ToggleFirstFlag(sgpConvertToExpansionButton, 0);
	return 1;
}

//D2Launch.0x6FA15DC0
int32_t __stdcall CHARSEL_DeleteCharacterCancelCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroySubChildren();
	return 1;
}

//D2Launch.0x6FA15DD0
int32_t __stdcall CHARSEL_DeleteCharacterCallback(SMSGHANDLER_PARAMS* pMsg)
{
	MENU_DestroySubChildren();

	D2WinControlStrc* pBackground = MENU_CreateSubChild(214);
	D2Win_10033(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(pBackground, 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(215), 1);
	D2Win_10030_CONTROL_ToggleFourthFlag(MENU_CreateSubChild(216), 1);

	D2WinTextBoxStrc* pText = (D2WinTextBoxStrc*)MENU_CreateSubChild(217);
	D2Win_10030_CONTROL_ToggleFourthFlag(&pText->controlHeader, 1);
	D2Win_10051(pText, D2LANG_GetStringFromTblIndex(5163), 0, 0, 0);
	return 1;
}

//D2Launch.0x6FA15E50
int32_t __stdcall CHARSEL_DeleteCharacterConfirmCallback(SMSGHANDLER_PARAMS* pMsg)
{
	char szRealmName[256];

	D2CharSelNodeStrc* pNode = CHARSEL_GetNodeFromIndex(sgnSelectedIndex);
	if (!pNode)
	{
		return 0;
	}

	sgbOperationInProgress = TRUE;

	const char* szCharacterRealmName = gszEmptyString;
	if (pNode->wszRealm[0])
	{
		Unicode::unicode2Win(szRealmName, pNode->wszRealm, 255);
		if (!MENU_DeleteRealmCharacter(pNode, szRealmName))
		{
			MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5211), CHARSEL_CreateMenu);
			sgbOperationInProgress = FALSE;
			return 1;
		}

		sgbCharacterListFull = FALSE;
		++sgnCharactersToCreate;
		szCharacterRealmName = szRealmName;
	}

	SAVE_DeleteCharacter(pNode->szName, szCharacterRealmName);
	CHARSEL_CreateMenu();
	sgbOperationInProgress = FALSE;
	return 1;
}

//D2Launch.0x6FA15F40
int32_t __stdcall CHARSEL_ScrollUpCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (sgnScrollOffset > 0)
	{
		--sgnScrollOffset;
	}

	if (sgnSelectedIndex > 0)
	{
		--sgnSelectedIndex;
	}

	CHARSEL_UpdateCharacterList();
	CHARSEL_UpdateSelection();
	return 1;
}

//D2Launch.0x6FA15F70
int32_t __stdcall CHARSEL_ScrollDownCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (sgnVisibleSlotCount + sgnScrollOffset < sgnCharacterCount)
	{
		if (sgnSelectedIndex < sgnCharacterCount - 1)
		{
			++sgnSelectedIndex;
		}

		++sgnScrollOffset;
		CHARSEL_UpdateCharacterList();
		CHARSEL_UpdateSelection();
	}

	return 1;
}

//D2Launch.0x6FA15FC0
int32_t __stdcall CHARSEL_ScrollBarCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const int32_t nPosition = D2Win_10192(sgpScrollBarTextBox);
	if (sgnScrollBarPosition == nPosition)
	{
		return 0;
	}

	sgnScrollOffset += 2 * (nPosition - sgnScrollBarPosition);
	if (sgnScrollOffset < 0)
	{
		sgnScrollOffset = 0;
	}

	if (sgnScrollOffset >= sgnCharacterCount)
	{
		sgnScrollOffset = sgnCharacterCount - 1;
	}

	sgnScrollBarPosition = nPosition;
	CHARSEL_UpdateCharacterList();
	CHARSEL_UpdateSelection();
	return 1;
}

//D2Launch.0x6FA16030
int32_t __stdcall CHARSEL_ExpansionKeyDownCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (pMsg->nMessage == WM_CHAR)
	{
		return 0;
	}

	switch (pMsg->wParam)
	{
	case VK_DOWN:
		if (sgnSelectedIndex < sgnCharacterCount - 1)
		{
			sgnSelectedIndex += 2;
			if (sgnSelectedIndex > sgnCharacterCount - 1)
			{
				sgnSelectedIndex -= 2;
			}
			else if (sgnSelectedIndex < sgnScrollOffset)
			{
				sgnScrollOffset = sgnSelectedIndex;
				CHARSEL_UpdateCharacterList();
				CHARSEL_UpdateSelection();
				return 1;
			}
			else if (sgnSelectedIndex > sgnScrollOffset + sgnVisibleSlotCount - 1)
			{
				if (sgnSelectedIndex % 2)
				{
					sgnScrollOffset = sgnSelectedIndex - sgnVisibleSlotCount + 1;
				}
				else
				{
					sgnScrollOffset = sgnSelectedIndex - sgnVisibleSlotCount + 2;
				}

				D2Win_10193(sgpScrollBarTextBox, D2Win_10192(sgpScrollBarTextBox) + 1);
				CHARSEL_UpdateCharacterList();
				CHARSEL_UpdateSelection();
				return 1;
			}
		}
		break;

	case VK_UP:
		if (sgnSelectedIndex > 0)
		{
			sgnSelectedIndex -= 2;
			if (sgnSelectedIndex < 0)
			{
				sgnSelectedIndex += 2;
			}
			else if (sgnSelectedIndex < sgnScrollOffset)
			{
				sgnScrollOffset = (sgnSelectedIndex % 2) ? sgnSelectedIndex - 1 : sgnSelectedIndex;
				D2Win_10193(sgpScrollBarTextBox, D2Win_10192(sgpScrollBarTextBox) - 1);
				CHARSEL_UpdateCharacterList();
				CHARSEL_UpdateSelection();
				return 1;
			}
			else if (sgnSelectedIndex > sgnScrollOffset + sgnVisibleSlotCount - 1)
			{
				sgnScrollOffset = sgnSelectedIndex - sgnVisibleSlotCount + 2;
				CHARSEL_UpdateCharacterList();
				CHARSEL_UpdateSelection();
				return 1;
			}
		}
		break;

	case VK_RIGHT:
	case VK_LEFT:
		if (pMsg->wParam == VK_RIGHT)
		{
			if (sgnSelectedIndex >= sgnCharacterCount - 1 || sgnSelectedIndex % 2)
			{
				break;
			}

			++sgnSelectedIndex;
		}
		else
		{
			if (sgnSelectedIndex <= 0 || !(sgnSelectedIndex % 2))
			{
				break;
			}

			--sgnSelectedIndex;
		}

		if (sgnSelectedIndex < sgnScrollOffset)
		{
			sgnScrollOffset = sgnSelectedIndex;
			CHARSEL_UpdateCharacterList();
			CHARSEL_UpdateSelection();
			return 1;
		}

		if (sgnSelectedIndex > sgnScrollOffset + sgnVisibleSlotCount - 1)
		{
			sgnScrollOffset = sgnSelectedIndex - sgnVisibleSlotCount + 1;
			CHARSEL_UpdateCharacterList();
			CHARSEL_UpdateSelection();
			return 1;
		}
		break;

	case VK_HOME:
		sgnScrollOffset = 0;
		sgnSelectedIndex = 0;
		break;

	case VK_END:
		if (sgnCharacterCount > sgnVisibleSlotCount)
		{
			sgnScrollOffset = sgnCharacterCount - sgnVisibleSlotCount;
		}

		sgnSelectedIndex = sgnCharacterCount - 1;
		break;

	default:
		break;
	}

	CHARSEL_UpdateCharacterList();
	CHARSEL_UpdateSelection();
	return 1;
}

//D2Launch.0x6FA16260
int32_t __stdcall CHARSEL_KeyDownCallback(SMSGHANDLER_PARAMS* pMsg)
{
	if (FOG_IsExpansion())
	{
		return CHARSEL_ExpansionKeyDownCallback(pMsg);
	}

	if (pMsg->nMessage == WM_CHAR)
	{
		return 0;
	}

	switch (pMsg->wParam)
	{
	case VK_DOWN:
	case VK_UP:
		if (pMsg->wParam == VK_DOWN)
		{
			if (sgnSelectedIndex >= sgnCharacterCount - 1)
			{
				break;
			}

			++sgnSelectedIndex;
		}
		else
		{
			if (sgnSelectedIndex <= 0)
			{
				break;
			}

			--sgnSelectedIndex;
		}

		if (sgnSelectedIndex < sgnScrollOffset)
		{
			sgnScrollOffset = sgnSelectedIndex;
			CHARSEL_UpdateCharacterList();
			CHARSEL_UpdateSelection();
			return 1;
		}

		if (sgnSelectedIndex > sgnScrollOffset + sgnVisibleSlotCount - 1)
		{
			sgnScrollOffset = sgnSelectedIndex - sgnVisibleSlotCount + 1;
			CHARSEL_UpdateCharacterList();
			CHARSEL_UpdateSelection();
			return 1;
		}
		break;

	case VK_HOME:
		sgnScrollOffset = 0;
		sgnSelectedIndex = 0;
		break;

	case VK_END:
		if (sgnCharacterCount > sgnVisibleSlotCount)
		{
			sgnScrollOffset = sgnCharacterCount - sgnVisibleSlotCount;
		}

		sgnSelectedIndex = sgnCharacterCount - 1;
		break;

	default:
		break;
	}

	CHARSEL_UpdateCharacterList();
	CHARSEL_UpdateSelection();
	return 1;
}

//D2Launch.0x6FA16350
void __fastcall CHARSEL_LoadRealmCharacters(const char* szRealmName, const uint8_t* pPacket, BOOL bCache)
{
	const uint8_t nPacketId = pPacket[0];
	int32_t nReturnedCount = *(const uint16_t*)&pPacket[7];
	const uint8_t* pData = &pPacket[9];

	if (!FOG_IsExpansion())
	{
		CHARSEL_AddCreateNewCharacterNode();
	}

	uint32_t nCount = *(const uint16_t*)&pPacket[3];
	if (nReturnedCount < (int32_t)nCount)
	{
		nCount = nReturnedCount;
	}

	for (; nCount; --nCount)
	{
		uint32_t dwExpirationTime = 0;
		if (nPacketId == 0x19)
		{
			dwExpirationTime = *(const uint32_t*)pData;
			pData += sizeof(uint32_t);
		}

		const char* szName = (const char*)pData;
		const uint8_t* pStatString = pData + strlen(szName) + 1;
		pData = pStatString + strlen((const char*)pStatString) + 1;

		if (!CHARSEL_AddCharacter(szName, szRealmName, pStatString, dwExpirationTime, 0, 0))
		{
			--nReturnedCount;

			D2RealmCharListCacheStrc* pCache = sgpRealmCharListCache;
			while (pCache)
			{
				D2RealmCharListCacheStrc* pNext = pCache->pNext;
				SMemFree(pCache->pCharListPacket, __FILE__, __LINE__, 0);
				SMemFree(pCache, __FILE__, __LINE__, 0);
				pCache = pNext;
			}

			sgpRealmCharListCache = nullptr;
			MENU_FreeRealmList();
			bCache = FALSE;
		}
	}

	if (bCache)
	{
		CHARSEL_CacheRealmCharList(szRealmName, pPacket, pData - pPacket);
	}

	if (nReturnedCount >= *(const uint16_t*)&pPacket[1])
	{
		sgbCharacterListFull = TRUE;
	}

	if (*(const uint16_t*)&pPacket[3] > *(const uint16_t*)&pPacket[7])
	{
		Unicode wszEmpty[1];
		const Unicode* wszName = D2LANG_GetStringFromTblIndex(11067);
		sgnMoreCharactersIndex = sgnCharacterCount;
		wszEmpty[0] = 0;
		CHARSEL_AddSpecialNode(wszName, wszEmpty, CHARSELNODE_MORE_CHARACTERS, 18);
	}

	CHARSEL_UpdateSelection();
}

//D2Launch.0x6FA164F0
int32_t __stdcall CHARSEL_RealmTimerCallback(SMSGHANDLER_PARAMS* pMsg)
{
	switch (sgnRealmState)
	{
	case 1:
	{
		if (sgbRealmSelectionOpen)
		{
			D2Win_10188(sgpRealmListTextBox, -1, 4);
		}

		const char* szRealmName = sgszRealmToLoad;
		if (sgbRealmSelectionOpen)
		{
			for (int32_t i = 0; i < MENU_GetRealmCount(); ++i)
			{
				const char* szCurrentRealmName = MENU_GetRealmName(i);
				if (!szCurrentRealmName)
				{
					break;
				}

				if (!SStrCmpI(szRealmName, szCurrentRealmName, 0x7FFFFFFF))
				{
					D2Win_10188(sgpRealmListTextBox, i, 1);
				}
			}
		}

		MENU_LogonRealm(sgszRealmToLoad, TRUE);
		sgnRealmState = 2;
		sgdwRealmStateTickCount = GetTickCount();
		break;
	}

	case 2:
	{
		D2Win_10047(sgpRealmStatusTextBox);
		if (GetTickCount() - sgdwRealmStateTickCount > 1000)
		{
			D2Win_10051(sgpRealmStatusTextBox, D2LANG_GetStringFromTblIndex(11065), 4, 0, 0);
		}

		BOOL bFailed = FALSE;
		switch (MENU_GetLogonRealmStatus())
		{
		case 0:
			D2MCPCLIENT_10058(0, 0);
			sgnRealmState = 3;
			bFailed = D2MCPCLIENT_10056() == 0;
			break;

		case 2:
			bFailed = TRUE;
			break;

		default:
			break;
		}

		if (bFailed)
		{
			sgbCreateNewCharacterDisabled = TRUE;
			sgnRealmState = 0;
			D2Win_10047(sgpRealmStatusTextBox);
			D2Win_10051(sgpRealmStatusTextBox, D2LANG_GetStringFromTblIndex(11066), 4, 0, 0);
			D2Win_10025_CONTROL_ToggleFirstFlag(sgpCreateNewCharacterButton, 0);
			if (sgbRealmSelectionOpen)
			{
				D2Win_10188(sgpRealmListTextBox, -1, 4);
			}
		}
		break;
	}

	case 3:
	{
		D2Win_10047(sgpRealmStatusTextBox);
		if (GetTickCount() - sgdwRealmStateTickCount > 1000)
		{
			D2Win_10051(sgpRealmStatusTextBox, D2LANG_GetStringFromTblIndex(11065), 4, 0, 0);
		}

		D2MCPCLIENT_10003();
		if (const uint8_t* pPacket = D2MCPCLIENT_10057())
		{
			sgnRealmState = 0;
			if (sgbRealmSelectionOpen)
			{
				D2Win_10188(sgpRealmListTextBox, -1, 4);
			}

			CHARSEL_LoadRealmCharacters(sgszRealmToLoad, pPacket, TRUE);
		}
		break;
	}

	default:
		break;
	}

	return 1;
}

//D2Launch.0x6FA16710
BOOL __fastcall CHARSEL_InitializeRealmSelection()
{
	sgnRealmState = 0;

	if (gnGameType != MODE_CLOSED)
	{
		return TRUE;
	}

	MENU_RequestRealmList();

	const int32_t nRealmCount = MENU_GetRealmCount();
	if (nRealmCount == -1)
	{
		BNET_Disconnect();
		MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5347), MENU_ShowMainMenu);
		return FALSE;
	}

	if (nRealmCount == 0)
	{
		BNET_Disconnect();
		MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5290), MENU_ShowMainMenu);
		return FALSE;
	}

	D2WinTimerStrc* pTimer = (D2WinTimerStrc*)MENU_CreateChild(122);
	D2Win_10180(pTimer);
	D2Win_10182(pTimer);

	sgpRealmStatusTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(148);
	sgpMessageTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(149);
	MENU_CreateChild(105);
	sgpChangeRealmButton = MENU_CreateChild(107);
	sgpRealmNameTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(108);

	const Unicode* wszCurrentRealm = D2LANG_GetStringFromTblIndex(11058);
	D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(106), wszCurrentRealm, 4, 0, 0);

	CHARSEL_SelectPreferredRealm();
	return TRUE;
}

//D2Launch.0x6FA168F0
void __fastcall CHARSEL_CreateExpansionMenu()
{
	MENU_DestroyChildren();
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);

	DWORD dwAllowHardcore = 0;
	sgnCharacterCount = 0;
	sgnScrollOffset = 0;
	sgnSelectedIndex = 0;
	SRegLoadValue("Diablo II", "AllowHardcore", 0, &dwAllowHardcore);

	sgbRealmSelectionOpen = FALSE;
	sgpMessageTextBox = nullptr;
	gbAllowHardcore = dwAllowHardcore;
	sgpRealmStatusTextBox = nullptr;
	sgnScrollBarPosition = 0;
	gptParams->nArenaDifficulty = 0;

	MENU_CreateChild(161);
	sgpOkButton = MENU_CreateChild(162);
	sgpExitButton = MENU_CreateChild(163);
	sgpCreateNewCharacterButton = MENU_CreateChild(164);
	sgpConvertToExpansionButton = MENU_CreateChild(165);
	sgpDeleteButton = MENU_CreateChild(166);
	sgpSelectedCharacterNameTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(156);
	BUTTON_SetStringId((D2WinButtonStrc*)sgpCreateNewCharacterButton, 21796);
	BUTTON_SetStringId((D2WinButtonStrc*)sgpConvertToExpansionButton, 22730);
	BUTTON_SetStringId((D2WinButtonStrc*)sgpDeleteButton, 21796);

	sgpScrollBarTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(167);
	D2Win_10194(sgpScrollBarTextBox, nullptr);
	D2Win_10195(sgpScrollBarTextBox, (void(__stdcall*)(SMSGHANDLER_PARAMS*))CHARSEL_ScrollBarCallback);

	sgnVisibleSlotCount = 8;
	memset(sgpCharacterSlotTextBoxes, 0x00, sizeof(sgpCharacterSlotTextBoxes));

	for (int32_t i = 0; i < sgnVisibleSlotCount; ++i)
	{
		if (FOG_IsExpansion())
		{
			sgpCharacterSlotClickTextBoxes[i] = (D2WinTextBoxStrc*)MENU_CreateChild(i + 140);
			D2Win_10045(sgpCharacterSlotClickTextBoxes[i], " ");
		}

		D2Win_10208(1);
		sgpCharacterSlotTextBoxes[i] = (D2WinTextBoxStrc*)MENU_CreateChild(i + 132);
		D2Win_10208(0);
		sganCharacterSlotY[i] = 93 * (i / 2) + 178;
	}

	sgpSelectionImage = (D2WinImageStrc*)MENU_CreateChild(150);

	if (!CHARSEL_InitializeRealmSelection())
	{
		return;
	}

	D2Win_10025_CONTROL_ToggleFirstFlag(sgpExitButton, 0);
	sgbCharacterListFull = FALSE;
	CHARSEL_LoadCharacters(sgszPreferredRealmName);

	CHARSEL_UpdateSelection();
	CHARSEL_UpdateCharacterList();

	const int32_t nHiddenCharacters = sgnCharacterCount - sgnVisibleSlotCount;
	if (nHiddenCharacters > 0)
	{
		D2Win_10191(sgpScrollBarTextBox, nHiddenCharacters / 2 + (nHiddenCharacters % 2 != 0));
	}

	if (D2SOUND_10069())
	{
		D2SOUND_10034(1);
	}

	D2Win_10025_CONTROL_ToggleFirstFlag(sgpExitButton, 1);
}

//D2Launch.0x6FA16E50
void __fastcall CHARSEL_CreateMenu()
{
	if (FOG_IsExpansion())
	{
		CHARSEL_CreateExpansionMenu();
		return;
	}

	MENU_DestroyChildren();
	BACKGROUND_SetCellFile(gpCharSelectBackgroundCellFile);
	MENU_LoadPalette(gszSkyPaletteDat, gszSkyPalettePl2);

	if (gnGameType == MODE_CLOSED)
	{
		MENU_RequestRealmList();

		const int32_t nRealmCount = MENU_GetRealmCount();
		if (nRealmCount == -1)
		{
			BNET_Disconnect();
			MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5347), MENU_ShowMainMenu);
			return;
		}

		if (nRealmCount == 0)
		{
			BNET_Disconnect();
			MENU_ShowMessage(D2LANG_GetStringFromTblIndex(5290), MENU_ShowMainMenu);
			return;
		}
	}

	DWORD dwAllowHardcore = 0;
	SRegLoadValue("Diablo II", "AllowHardcore", 0, &dwAllowHardcore);

	sgnCharacterCount = 0;
	sgnScrollOffset = 0;
	gbAllowHardcore = dwAllowHardcore;
	sgnSelectedIndex = 0;
	sgbRealmSelectionOpen = FALSE;
	sgpMessageTextBox = nullptr;
	sgpRealmStatusTextBox = nullptr;
	sgnRealmState = 0;

	D2WinTimerStrc* pTimer = (D2WinTimerStrc*)MENU_CreateChild(122);
	D2Win_10180(pTimer);
	D2Win_10182(pTimer);

	gptParams->nArenaDifficulty = 0;

	sgpExitButton = MENU_CreateChild(124);
	sgpDeleteButton = MENU_CreateChild(125);
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpDeleteButton, 0);
	sgpOkButton = MENU_CreateChild(126);
	sgpScrollUpButton = (D2WinButtonStrc*)MENU_CreateChild(153);
	sgpScrollDownButton = (D2WinButtonStrc*)MENU_CreateChild(154);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpScrollUpButton->controlHeader, 0);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpScrollDownButton->controlHeader, 0);
	sgpSelectedCharacterNameTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(155);
	sgpSelectedCharacterClassTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(157);
	sgpSelectedCharacterRealmTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(158);
	sgpCreateNewCharacterButton = MENU_CreateChild(159);

	memset(sgpCharacterSlotTextBoxes, 0x00, sizeof(sgpCharacterSlotTextBoxes));

	if (gnGameType == MODE_CLOSED)
	{
		sgnVisibleSlotCount = 4;

		int32_t nY = 246;
		for (int32_t i = 0; i < sgnVisibleSlotCount; ++i)
		{
			D2Win_10208(1);
			sgpCharacterSlotTextBoxes[i] = (D2WinTextBoxStrc*)MENU_CreateChild(i + 128);
			D2Win_10208(0);
			sganCharacterSlotY[i] = nY;
			nY += 93;
		}

		sgpRealmStatusTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(152);
		sgpMessageTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(121);
		BUTTON_SetCoordinates(sgpScrollUpButton, 634, 143, 29, 20);
		MENU_CreateChild(101);
		sgpChangeRealmButton = MENU_CreateChild(103);
		sgpRealmNameTextBox = (D2WinTextBoxStrc*)MENU_CreateChild(104);

		const Unicode* wszCurrentRealm = D2LANG_GetStringFromTblIndex(11058);
		D2Win_10051((D2WinTextBoxStrc*)MENU_CreateChild(102), wszCurrentRealm, 4, 0, 0);

		CHARSEL_SelectPreferredRealm();
	}
	else
	{
		sgnVisibleSlotCount = 5;

		int32_t nY = 153;
		for (int32_t i = 0; i < sgnVisibleSlotCount; ++i)
		{
			D2Win_10208(1);
			sgpCharacterSlotTextBoxes[i] = (D2WinTextBoxStrc*)MENU_CreateChild(i + 127);
			D2Win_10208(0);
			sganCharacterSlotY[i] = nY;
			nY += 93;
		}

		BUTTON_SetCoordinates(sgpScrollUpButton, 634, 50, 29, 20);
	}

	sgpSelectionImage = (D2WinImageStrc*)MENU_CreateChild(150);
	sgpCreateNewCharacterDisabledImage = (D2WinImageStrc*)MENU_CreateChild(151);
	D2Win_10027_CONTROL_ToggleThirdFlag(&sgpCreateNewCharacterDisabledImage->controlHeader, 0);
	D2Win_10025_CONTROL_ToggleFirstFlag(sgpExitButton, 0);

	sgbCharacterListFull = FALSE;
	CHARSEL_LoadCharacters(sgszPreferredRealmName);

	CHARSEL_UpdateSelection();
	CHARSEL_UpdateCharacterList();

	if (D2SOUND_10069())
	{
		D2SOUND_10034(1);
	}

	D2Win_10025_CONTROL_ToggleFirstFlag(sgpExitButton, 1);
}

//D2Launch.0x6FA175C0
BOOL __fastcall CHARSEL_AddSpecialNode(const Unicode* wszName, const Unicode* wszText, int32_t eType, uint8_t nClass)
{
	D2CharSelNodeStrc* pNode = (D2CharSelNodeStrc*)D2_ALLOC(sizeof(D2CharSelNodeStrc));
	Unicode::toUtf(pNode->szName, wszName, 256);
	Unicode::strcpy(pNode->wszRealm, wszText);

	memset(pNode->pComponents, 0x00, sizeof(pNode->pComponents));
	memset(pNode->pComponentColors, 0x00, sizeof(pNode->pComponentColors));
	pNode->nClass = nClass;
	pNode->nLevel = 0;
	pNode->nFlags = 0;
	pNode->nVersion = 0;
	pNode->nGuildFlags = 0;
	pNode->bLadder = 0;
	pNode->unk0x32F = 0;
	pNode->unk0x330 = 0;
	pNode->hUnit = nullptr;
	pNode->pNext = nullptr;

	for (int32_t i = 0; i < 16; ++i)
	{
		pNode->pComponents[i] = 0;
		pNode->pComponentColors[i] = 0xFF;
	}

	pNode->pComponents[1] = 1;
	pNode->hUnit = D2Win_10144(pNode->nClass, 5, pNode->pComponents, pNode->pComponentColors);
	pNode->eType = eType;
	D2Win_10149(pNode->hUnit, 0);
	D2Win_10151(pNode->hUnit, 0);
	D2Win_10143(pNode->hUnit, 5);

	if (D2CharSelNodeStrc* pCurrent = sgptCharacterList)
	{
		while (pCurrent->pNext)
		{
			pCurrent = pCurrent->pNext;
		}

		pCurrent->pNext = pNode;
	}
	else
	{
		sgptCharacterList = pNode;
	}

	++sgnCharacterCount;
	CHARSEL_UpdateCharacterList();
	return TRUE;
}
