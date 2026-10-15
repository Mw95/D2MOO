#include "ComCallback.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <D2BitManip.h>
#include <D2Lang.h>
#include <D2Unicode.h>
#include <Fog.h>
#include <Storm.h>
#include <D2WinComp.h>
#include <D2WinEditBox.h>
#include <D2WinMain.h>
#include <D2WinSmack.h>
#include <D2WinTextBox.h>

#include "ChatDlg.h"
#include "Gate.h"


// Number of user buttons displayed in the user list
#define COMCALLBACK_VISIBLE_USERS 11

// Flags of the composite units displayed in the user list
enum D2MultiUserUnitFlags
{
	USERUNITFLAG_DEAD = 4,
	USERUNITFLAG_HARDCORE = 5,
	USERUNITFLAG_DIFFICULTY_LOW = 6,
	USERUNITFLAG_DIFFICULTY_HIGH = 7,
	USERUNITFLAG_ALTERNATE_BACKGROUND = 8,
	USERUNITFLAG_SQUELCHED = 9,
	USERUNITFLAG_SELECTED = 10,
	USERUNITFLAG_BLIZZARD = 11,
	USERUNITFLAG_EXPANSION = 12,
	USERUNITFLAG_INCOMPATIBLE = 13,
};

#pragma pack(push, 1)
// Chat event, as read from the Battle.net message queue
struct D2MultiChatEventMessageStrc
{
	uint32_t nEventId;							//0x00 D2MultiChatEvent
	uint32_t nFlags;							//0x04
	uint32_t nPing;								//0x08
	uint32_t unk0x0C[3];						//0x0C
	char szUserName[1];							//0x18 Followed by the text
};

// Ad, as read from the Battle.net message queue
struct D2MultiAdMessageStrc
{
	int32_t nAdId;								//0x00
	uint32_t unk0x04;							//0x04
	char* szFileName;							//0x08
	void* pUnk0x0C;								//0x0C
	void* pData;								//0x10
	DWORD nDataSize;							//0x14
};

// Message read from the Battle.net message queue
struct D2MultiBnMessageStrc
{
	DWORD nType;								//0x00 D2MultiBnMessageType
	DWORD nBytesWritten;						//0x04
	union										//0x08
	{
		D2MultiChatEventMessageStrc tChatEvent;
		D2MultiAdMessageStrc tAd;
		char szUniqueName[1];
		uint8_t pData[0x120];
	};
};
#pragma pack(pop)

enum D2MultiBnMessageType
{
	BNMESSAGE_CHATEVENT = 0,
	BNMESSAGE_UNIQUENAME = 2,
	BNMESSAGE_AD = 3,
};


int32_t gnSelectedUserIndex_6F9BE790 = -1;

D2MultiChatEventCallback gapfComCallbacks_6F9BE798[CHATEVENT_COUNT] =
{
	COMCALLBACK_OnUnknownEvent,
	COMCALLBACK_OnShowUser,					// CHATEVENT_SHOWUSER
	COMCALLBACK_OnJoin,						// CHATEVENT_JOIN
	COMCALLBACK_OnLeave,					// CHATEVENT_LEAVE
	COMCALLBACK_OnWhisper,					// CHATEVENT_WHISPER
	COMCALLBACK_OnTalk,						// CHATEVENT_TALK
	COMCALLBACK_OnInfo,						// CHATEVENT_BROADCAST
	COMCALLBACK_OnChannel,					// CHATEVENT_CHANNEL
	COMCALLBACK_OnIgnoredEvent,
	COMCALLBACK_OnUserFlags,				// CHATEVENT_USERFLAGS
	COMCALLBACK_OnWhisperSent,				// CHATEVENT_WHISPERSENT
	COMCALLBACK_OnIgnoredEvent,
	COMCALLBACK_OnIgnoredEvent,
	COMCALLBACK_OnChannelFull,				// CHATEVENT_CHANNELFULL
	COMCALLBACK_OnChannelDoesNotExist,		// CHATEVENT_CHANNELDOESNOTEXIST
	COMCALLBACK_OnChannelRestricted,		// CHATEVENT_CHANNELRESTRICTED
	COMCALLBACK_OnIgnoredEvent,
	COMCALLBACK_OnIgnoredEvent,
	COMCALLBACK_OnInfo,						// CHATEVENT_INFO
	COMCALLBACK_OnError,					// CHATEVENT_ERROR
	COMCALLBACK_OnIgnoredEvent,
	COMCALLBACK_OnInfo,
	COMCALLBACK_OnInfo,
	COMCALLBACK_OnEmote,					// CHATEVENT_EMOTE
};

D2MultiChannelUserStrc* gpChannelUsers_6F9C2B1C;
D2MultiUserHistoryStrc* gpUserHistory_6F9C2B20;
int32_t gnUserHistoryCount_6F9C2B24;
int32_t gnChannelUserCount_6F9C2B28;
int32_t gnUserListScroll_6F9C2B2C;
D2MultiChannelUserStrc* gptSelectedUnit_6F9C2B30;
DWORD gdwSelectedUserTickCount_6F9C2B34;
DWORD gdwLastSquelchTickCount_6F9C2B38;
BOOL gbRandomSeeded_6F9C2B3C;


//Inlined
static const char* COMCALLBACK_GetAccountName(const char* szUserName)
{
	const char* szSeparator = SStrChr(szUserName, '*');
	if (!szSeparator || !szSeparator[1])
	{
		return szUserName;
	}
	return szSeparator + 1;
}

//Inlined
static const char* COMCALLBACK_SkipCharacterName(const char* szUserName)
{
	const char* szSeparator = strchr(szUserName, '*');
	return szSeparator ? szSeparator + 1 : szUserName;
}

//Inlined
static void COMCALLBACK_DeselectUser()
{
	if (gptSelectedUnit_6F9C2B30)
	{
		D2_ASSERT(gptSelectedUnit_6F9C2B30->pCompositeUnit);

		const uint32_t nUnitFlags = D2Win_10155(gptSelectedUnit_6F9C2B30->pCompositeUnit);
		D2Win_10156(gptSelectedUnit_6F9C2B30->pCompositeUnit, gdwInvBitMasks[USERUNITFLAG_SELECTED] & nUnitFlags);
		gptSelectedUnit_6F9C2B30 = nullptr;
		gnSelectedUserIndex_6F9BE790 = -1;
	}
}

//Inlined
static void COMCALLBACK_DeselectUserAndUpdateButtons()
{
	COMCALLBACK_DeselectUser();
	if (!CHATDLG_IsChatNotCreated())
	{
		COMCALLBACK_UpdateChatButtons();
	}
}

//Inlined
static void COMCALLBACK_UpdateChannelTitle()
{
	char szTitle[256];
	Unicode wszTitle[0x240];
	sprintf(szTitle, "%s (%d)", gszCurrentChannel_6F9C2918, gnChannelUserCount_6F9C2B28);
	Unicode::win2Unicode(wszTitle, szTitle, std::size(wszTitle));
	CHATDLG_SetChannelTitle(wszTitle);
}

//Inlined
static void COMCALLBACK_GetDisplayName(const char* szTitle, const char* szCharacterName, char* szDisplayName)
{
	if (szTitle[0])
	{
		sprintf(szDisplayName, "%s%s", szTitle, szCharacterName);
	}
	else
	{
		strcpy(szDisplayName, szCharacterName);
	}
}

//Inlined
static void COMCALLBACK_GetUserColors(const char* szUserName, int32_t* pNameColor, int32_t* pTextColor)
{
	*pNameColor = 4;
	*pTextColor = 0;
	for (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C; pUser; pUser = pUser->pNext)
	{
		if (!strcmp(pUser->szUserName, szUserName))
		{
			if (pUser->dwChatFlags & CHATUSERFLAG_CHANNELOPERATOR)
			{
				*pNameColor = 0;
			}
			else if ((pUser->dwChatFlags & CHATUSERFLAG_BLIZZARDREPRESENTATIVE) || (pUser->dwChatFlags & CHATUSERFLAG_BATTLENETADMINISTRATOR))
			{
				*pNameColor = 3;
				*pTextColor = 3;
			}
			return;
		}
	}
}

//Inlined
static void COMCALLBACK_AddFormattedMessage(const char* szMessage, int32_t nColor)
{
	Unicode wszMessage[0x240];
	Unicode::utf8ToUnicode(wszMessage, szMessage, std::size(wszMessage));
	COMCALLBACK_RemoveColorCodes(wszMessage);
	CHATDLG_AddChatMessage(wszMessage, nColor);
}

//Inlined
static int32_t COMCALLBACK_GetUserPriority(const D2MultiChannelUserStrc* pUser)
{
	const uint32_t dwChatFlags = pUser->dwChatFlags;
	if (dwChatFlags & CHATUSERFLAG_CHANNELOPERATOR)
	{
		return 4;
	}

	if (dwChatFlags & CHATUSERFLAG_BATTLENETADMINISTRATOR)
	{
		return 3;
	}

	if (dwChatFlags & CHATUSERFLAG_BLIZZARDREPRESENTATIVE)
	{
		return 2;
	}

	return (dwChatFlags & CHATUSERFLAG_SPEAKER) ? 1 : 0;
}

//Inlined
static uint32_t COMCALLBACK_GetDifficultyFlags(uint16_t nCharacterFlags)
{
	const int32_t nProgression = (nCharacterFlags >> 8) & 0x1F;
	if (nCharacterFlags & D2MULTI_SAVEFLAG_EXPANSION)
	{
		if (nProgression >= 15)
		{
			return 3;
		}
		if (nProgression >= 10)
		{
			return 2;
		}
		return nProgression >= 5;
	}

	if (nProgression >= 12)
	{
		return 3;
	}
	if (nProgression >= 8)
	{
		return 2;
	}
	return nProgression >= 4;
}

//Inlined
static uint32_t COMCALLBACK_SetUnitFlag(uint32_t nUnitFlags, int32_t nFlag, BOOL bSet)
{
	return bSet ? (nUnitFlags | gdwBitMasks[nFlag]) : (nUnitFlags & gdwInvBitMasks[nFlag]);
}

//Inlined
static void COMCALLBACK_SetupCompositeUnit(D2MultiChannelUserStrc* pUser, uint8_t nClass)
{
	int32_t nMode = 5;
	if ((pUser->nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE) && !(pUser->nCharacterFlags & D2MULTI_SAVEFLAG_DEAD) && (FOG_IsExpansion() || nClass < 5))
	{
		nMode = 1;
	}

	D2Win_10145(pUser->pCompositeUnit, nClass, nMode, pUser->pComponents, pUser->pComponentColors);
	COMCALLBACK_UpdateUserDescription(pUser);
	COMCALLBACK_UpdateUserList();
}


//D2Multi.0x6F9AB3E0
BOOL __fastcall COMCALLBACK_ProcessMessages()
{
	D2MultiBnMessageStrc tMessage;
	if (!gptComInt_6F9C19BC->BnMessQueue_Read(&tMessage.nType, tMessage.pData))
	{
		return FALSE;
	}

	switch (tMessage.nType)
	{
	case BNMESSAGE_CHATEVENT:
	{
		const D2MultiChatEventMessageStrc* pChatEvent = &tMessage.tChatEvent;
		if (pChatEvent->nEventId < CHATEVENT_COUNT && gapfComCallbacks_6F9BE798[pChatEvent->nEventId])
		{
			const char* szText = &pChatEvent->szUserName[strlen(pChatEvent->szUserName) + 1];
			gapfComCallbacks_6F9BE798[pChatEvent->nEventId](pChatEvent->nFlags, pChatEvent->nPing, pChatEvent->szUserName, szText);
		}
		break;
	}
	case BNMESSAGE_UNIQUENAME:
		SStrCopy(gszUniqueName_6F9C28E0, tMessage.szUniqueName, 50);
		break;

	case BNMESSAGE_AD:
	{
		const D2MultiAdMessageStrc* pAd = &tMessage.tAd;
		SMACK_DeleteFile(gpAdSmack_6F9C2698);

		char szTempPath[MAX_PATH];
		if (!GetTempPathA(std::size(szTempPath), szTempPath))
		{
			strcpy(szTempPath, ".");
		}

		char szTempFileName[MAX_PATH];
		if (GetTempFileNameA(szTempPath, "BNetAd", 0, szTempFileName))
		{
			DeleteFileA(gszAdFileName_6F9C2A18);

			HANDLE hFile = FOG_CreateFileA(szTempFileName, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				FOG_WriteFile(hFile, pAd->pData, pAd->nDataSize, &tMessage.nBytesWritten, nullptr);
				FOG_CloseFile(hFile);
			}

			const char* szExtension = strrchr(pAd->szFileName, '.');
			SMACK_Decode(gpAdSmack_6F9C2698, szTempFileName, tolower(szExtension[1]), 0, 0);
			strcpy(gszAdFileName_6F9C2A18, szTempFileName);
		}

		gnAdId_6F9C1A40 = pAd->nAdId;
		D2_FREE(pAd->szFileName);
		D2_FREE(pAd->pUnk0x0C);
		break;
	}
	default:
		break;
	}

	return TRUE;
}

//D2Multi.0x6F9AB5B0
void __fastcall COMCALLBACK_ScrollUserList(int32_t nDelta)
{
	const int32_t nPreviousScroll = gnUserListScroll_6F9C2B2C;
	BOOL bCanScrollUp = FALSE;
	BOOL bCanScrollDown = FALSE;

	if (gnChannelUserCount_6F9C2B28 <= COMCALLBACK_VISIBLE_USERS)
	{
		gnUserListScroll_6F9C2B2C = 0;
	}
	else
	{
		const int32_t nMaxScroll = gnChannelUserCount_6F9C2B28 - COMCALLBACK_VISIBLE_USERS;
		gnUserListScroll_6F9C2B2C = std::min(std::max(gnUserListScroll_6F9C2B2C + nDelta, 0), nMaxScroll);
		bCanScrollUp = gnUserListScroll_6F9C2B2C > 0;
		bCanScrollDown = gnUserListScroll_6F9C2B2C < nMaxScroll;
	}

	if (gnUserListScroll_6F9C2B2C != nPreviousScroll)
	{
		COMCALLBACK_UpdateUserList();
	}

	D2Win_10025_CONTROL_ToggleFirstFlag(gpUserListPageUp_6F9C2684, bCanScrollUp);
	D2Win_10025_CONTROL_ToggleFirstFlag(gpUserListPageDown_6F9C2688, bCanScrollDown);
	D2Win_10025_CONTROL_ToggleFirstFlag(gpUserListUp_6F9C268C, bCanScrollUp);
	D2Win_10025_CONTROL_ToggleFirstFlag(gpUserListDown_6F9C2690, bCanScrollDown);
}

//D2Multi.0x6F9AB640
int32_t __stdcall COMCALLBACK_UserButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	int32_t nButton = 0;
	while ((D2WinButtonStrc*)pMsg->hWindow != gapUserButtons_6F9C26AC[nButton])
	{
		++nButton;
		if (nButton >= COMCALLBACK_VISIBLE_USERS)
		{
			return 0;
		}
	}

	const int32_t nUserIndex = gnUserListScroll_6F9C2B2C + nButton;
	if (pMsg->nMessage == WM_RBUTTONUP)
	{
		// Show the profile of the user
		D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C;
		for (int32_t i = 0; pUser && i != nUserIndex; ++i)
		{
			pUser = pUser->pNext;
		}

		if (!pUser)
		{
			return 1;
		}

		GATE_CloseProfileDialog();
		if (strcmp(COMCALLBACK_GetAccountName(pUser->szUserName), gpConfig_6F9C26F0->szAccountName))
		{
			GATE_ShowProfile(pUser->szUserName, pUser->szCharacterName, pUser->bHardcore, pUser->bExpansion);
		}
		else
		{
			GATE_ShowOwnProfile(pUser->szCharacterName, pUser->bHardcore, pUser->bExpansion);
		}
		return 1;
	}

	const DWORD dwTickCount = GetTickCount();
	if (nUserIndex == gnSelectedUserIndex_6F9BE790)
	{
		COMCALLBACK_DeselectUserAndUpdateButtons();
		return 1;
	}

	if (nUserIndex >= gnChannelUserCount_6F9C2B28)
	{
		return 1;
	}

	COMCALLBACK_DeselectUserAndUpdateButtons();

	int32_t nIndex = 0;
	for (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C; pUser; pUser = pUser->pNext, ++nIndex)
	{
		if (nIndex == nUserIndex)
		{
			D2_ASSERT(pUser->pCompositeUnit);

			const uint32_t nUnitFlags = D2Win_10155(pUser->pCompositeUnit);
			D2Win_10156(pUser->pCompositeUnit, gdwBitMasks[USERUNITFLAG_SELECTED] | nUnitFlags);
			gnSelectedUserIndex_6F9BE790 = nUserIndex;
			gptSelectedUnit_6F9C2B30 = pUser;
			gdwSelectedUserTickCount_6F9C2B34 = dwTickCount;
			COMCALLBACK_UpdateChatButtons();
		}
	}

	return 1;
}

//D2Multi.0x6F9ABB50
int32_t __stdcall COMCALLBACK_SendButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const Unicode* wszText = D2Win_10077_EDITBOX_GetText(gpChatEditBox_6F9C28A8);
	if (wszText && Unicode::strlen(wszText))
	{
		char szText[256];
		Unicode::unicode2Win(szText, wszText, std::size(szText));
		return CHATDLG_SendChatText(szText, FALSE);
	}
	return 1;
}

//D2Multi.0x6F9ABBB0
int32_t __stdcall COMCALLBACK_WhisperButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const Unicode* wszText = D2Win_10077_EDITBOX_GetText(gpChatEditBox_6F9C28A8);
	if (wszText && Unicode::strlen(wszText))
	{
		char szText[256];
		Unicode::unicode2Win(szText, wszText, std::size(szText));
		return CHATDLG_SendChatText(szText, TRUE);
	}
	return 1;
}

//Inlined
static int32_t COMCALLBACK_SendSquelchCommand(const char* szFormat)
{
	if (!gptSelectedUnit_6F9C2B30)
	{
		return 1;
	}

	char szUserName[256];
	strcpy(szUserName, gptSelectedUnit_6F9C2B30->szUserName);

	const DWORD dwTickCount = GetTickCount();
	if (dwTickCount < gdwLastSquelchTickCount_6F9C2B38 + 1000)
	{
		return 1;
	}
	gdwLastSquelchTickCount_6F9C2B38 = dwTickCount;

	char szCommand[256];
	sprintf(szCommand, szFormat, COMCALLBACK_GetAccountName(szUserName));
	COMCALLBACK_DeselectUserAndUpdateButtons();

	if (!gptComInt_6F9C19BC->field_68())
	{
		CHATDLG_ShowPopup(D2LANG_GetStringFromTblIndex(0x14E7), CHATDLG_ReturnToLauncherCallback);
		return 0;
	}

	gptComInt_6F9C19BC->ChatCommand(szCommand);
	D2Win_10075(gpChatEditBox_6F9C28A8, nullptr);
	return 1;
}

//D2Multi.0x6F9ABC10
int32_t __stdcall COMCALLBACK_SquelchButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return COMCALLBACK_SendSquelchCommand("/squelch *%s");
}

//D2Multi.0x6F9ABE20
int32_t __stdcall COMCALLBACK_HelpButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	GATE_ShowHelp();
	CHATDLG_FocusChatEditBox();
	return 1;
}

//D2Multi.0x6F9ABE40
int32_t __stdcall COMCALLBACK_UnsquelchButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	return COMCALLBACK_SendSquelchCommand("/unsquelch *%s");
}

//D2Multi.0x6F9AC050
int32_t __stdcall COMCALLBACK_EmoteButtonCallback(SMSGHANDLER_PARAMS* pMsg)
{
	const Unicode* wszText = D2Win_10077_EDITBOX_GetText(gpChatEditBox_6F9C28A8);
	if (wszText && Unicode::strlen(wszText))
	{
		char szText[300];
		Unicode::unicode2Win(szText, wszText, std::size(szText));
		if (szText[0] != '/')
		{
			const DWORD dwTickCount = GetTickCount();
			if (dwTickCount >= gdwLastSquelchTickCount_6F9C2B38 + 1000)
			{
				gdwLastSquelchTickCount_6F9C2B38 = dwTickCount;

				char szCommand[300];
				sprintf(szCommand, "/me %s", szText);
				CHATDLG_SendChatText(szCommand, FALSE);
			}
		}
	}
	return 1;
}

//D2Multi.0x6F9AC0E0
char* __fastcall COMCALLBACK_GetChannelName()
{
	return gszCurrentChannel_6F9C2918;
}

//D2Multi.0x6F9AC0F0
int32_t __fastcall COMCALLBACK_OnUnknownEvent(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	return 1;
}

//D2Multi.0x6F9AC100
void __fastcall COMCALLBACK_UpdateUserList()
{
	// Sort the users by priority (insertion sort)
	if (D2MultiChannelUserStrc* pSortedUsers = gpChannelUsers_6F9C2B1C)
	{
		gpChannelUsers_6F9C2B1C = pSortedUsers->pNext;
		pSortedUsers->pNext = nullptr;

		while (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C)
		{
			const int32_t nPriority = COMCALLBACK_GetUserPriority(pUser);

			BOOL bInserted = FALSE;
			D2MultiChannelUserStrc* pPrevious = nullptr;
			for (D2MultiChannelUserStrc* pCurrent = pSortedUsers; pCurrent && !bInserted; )
			{
				if (nPriority > COMCALLBACK_GetUserPriority(pCurrent))
				{
					gpChannelUsers_6F9C2B1C = pUser->pNext;
					pUser->pNext = pCurrent;
					if (pPrevious)
					{
						pPrevious->pNext = pUser;
					}
					else
					{
						pSortedUsers = pUser;
					}
					bInserted = TRUE;
				}
				else
				{
					pPrevious = pCurrent;
					pCurrent = pCurrent->pNext;
				}
			}

			if (!bInserted)
			{
				pPrevious->pNext = pUser;
				gpChannelUsers_6F9C2B1C = gpChannelUsers_6F9C2B1C->pNext;
				pUser->pNext = nullptr;
			}
		}

		gpChannelUsers_6F9C2B1C = pSortedUsers;
	}

	// Update the composite units
	int32_t nY = 70;
	int32_t nIndex = 0;
	for (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C; pUser; pUser = pUser->pNext, ++nIndex)
	{
		const uint16_t nCharacterFlags = pUser->nCharacterFlags;
		uint32_t nUnitFlags = 0;

		if (nIndex >= gnUserListScroll_6F9C2B2C && nIndex < gnUserListScroll_6F9C2B2C + COMCALLBACK_VISIBLE_USERS)
		{
			// Visible user
			D2Win_10152(pUser->pCompositeUnit, nY);

			if (pUser->dwChatFlags & (CHATUSERFLAG_BLIZZARDREPRESENTATIVE | CHATUSERFLAG_BATTLENETADMINISTRATOR))
			{
				nUnitFlags = gdwBitMasks[USERUNITFLAG_BLIZZARD] | 0xF;
			}
			else
			{
				nUnitFlags = gdwInvBitMasks[USERUNITFLAG_BLIZZARD] & 0xF;
			}

			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_DEAD, nCharacterFlags & D2MULTI_SAVEFLAG_DEAD);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_HARDCORE, nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_EXPANSION, nCharacterFlags & D2MULTI_SAVEFLAG_EXPANSION);

			const uint32_t nDifficulty = COMCALLBACK_GetDifficultyFlags(nCharacterFlags);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_DIFFICULTY_LOW, nDifficulty & 1);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_DIFFICULTY_HIGH, nDifficulty & 2);

			if (nIndex & 1)
			{
				nUnitFlags |= gdwBitMasks[USERUNITFLAG_ALTERNATE_BACKGROUND];
			}

			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_SQUELCHED, pUser->dwChatFlags & CHATUSERFLAG_SQUELCHED);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_SELECTED, pUser == gptSelectedUnit_6F9C2B30);
			nY += 60;
		}
		else
		{
			// Hidden user
			if (pUser->dwChatFlags & (CHATUSERFLAG_BLIZZARDREPRESENTATIVE | CHATUSERFLAG_BATTLENETADMINISTRATOR))
			{
				nUnitFlags = gdwBitMasks[USERUNITFLAG_BLIZZARD];
			}

			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_DEAD, nCharacterFlags & D2MULTI_SAVEFLAG_DEAD);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_HARDCORE, nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_EXPANSION, nCharacterFlags & D2MULTI_SAVEFLAG_EXPANSION);

			const uint16_t nOwnFlags = gpConfig_6F9C26F0->unpackedCTemp.nCharacterSaveFlags;
			const BOOL bOwnHardcore = (nOwnFlags & D2MULTI_SAVEFLAG_HARDCORE) != 0;
			const BOOL bOwnExpansion = (nOwnFlags & D2MULTI_SAVEFLAG_EXPANSION) != 0;
			const BOOL bIncompatible = gpConfig_6F9C26F0->bLadder != pUser->nLadder
				|| (bOwnHardcore && !pUser->bHardcore) || (!bOwnHardcore && pUser->bHardcore)
				|| (bOwnExpansion && !pUser->bExpansion) || (!bOwnExpansion && pUser->bExpansion);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_INCOMPATIBLE, bIncompatible);

			const uint32_t nDifficulty = COMCALLBACK_GetDifficultyFlags(nCharacterFlags);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_DIFFICULTY_LOW, nDifficulty & 1);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_DIFFICULTY_HIGH, nDifficulty & 2);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_SQUELCHED, pUser->dwChatFlags & CHATUSERFLAG_SQUELCHED);
			nUnitFlags = COMCALLBACK_SetUnitFlag(nUnitFlags, USERUNITFLAG_SELECTED, pUser == gptSelectedUnit_6F9C2B30);
		}

		D2Win_10156(pUser->pCompositeUnit, nUnitFlags);
	}
}

//D2Multi.0x6F9AC570
int32_t __fastcall COMCALLBACK_OnShowUser(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szStatstring)
{
	COMCALLBACK_AddUser(szUserName, szStatstring, nFlags);
	return 1;
}

//D2Multi.0x6F9AC590
D2MultiChannelUserStrc* __fastcall COMCALLBACK_AddUser(const char* szUserName, const char* szStatstring, uint32_t nFlags)
{
	// Update the user if it's already in the list
	for (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C; pUser; pUser = pUser->pNext)
	{
		if (!strcmp(COMCALLBACK_SkipCharacterName(pUser->szUserName), COMCALLBACK_SkipCharacterName(szUserName)))
		{
			pUser->dwChatFlags = nFlags;
			const uint8_t nClass = COMCALLBACK_ParseStatstring(pUser, szStatstring, nFlags);
			SStrCopy(pUser->szUserName, szUserName, INT_MAX);
			COMCALLBACK_SetupCompositeUnit(pUser, nClass);
			return pUser;
		}
	}

	D2MultiChannelUserStrc* pUser = D2_ALLOC_STRC(D2MultiChannelUserStrc);
	memset(pUser, 0x00, sizeof(D2MultiChannelUserStrc));
	strcpy(pUser->szUserName, szUserName);
	pUser->dwChatFlags = nFlags;

	uint8_t nClass = COMCALLBACK_ParseStatstring(pUser, szStatstring, nFlags);

	int32_t nMode = 5;
	if ((pUser->nCharacterFlags & D2MULTI_SAVEFLAG_HARDCORE) && !(pUser->nCharacterFlags & D2MULTI_SAVEFLAG_DEAD) && !(pUser->dwChatFlags & CHATUSERFLAG_CHANNELOPERATOR) && (FOG_IsExpansion() || nClass < 5))
	{
		nMode = 1;
	}

	pUser->pCompositeUnit = D2Win_10144(nClass, nMode, pUser->pComponents, pUser->pComponentColors);
	if (!pUser->pCompositeUnit)
	{
		// Fallback to the default composite unit
		pUser->nClass = 7;
		for (int32_t i = 0; i < 16; ++i)
		{
			pUser->pComponents[i] = (i == 1) ? 1 : 0;
			pUser->pComponentColors[i] = 0xFF;
		}

		nClass = pUser->nClass;
		pUser->pCompositeUnit = D2Win_10144(nClass, 5, pUser->pComponents, pUser->pComponentColors);
	}

	D2_ASSERT(pUser->pCompositeUnit);

	D2Win_10153(pUser->pCompositeUnit, 571);
	D2Win_10149(pUser->pCompositeUnit, 0);

	if (!gbRandomSeeded_6F9C2B3C)
	{
		srand(GetTickCount());
		gbRandomSeeded_6F9C2B3C = TRUE;
	}

	const int32_t nFrameCount = D2Win_10169(pUser->pCompositeUnit);
	D2Win_10151(pUser->pCompositeUnit, rand() % (nFrameCount << 8));
	COMCALLBACK_UpdateUserDescription(pUser);

	// Append the user to the list
	if (gpChannelUsers_6F9C2B1C)
	{
		D2MultiChannelUserStrc* pLast = gpChannelUsers_6F9C2B1C;
		while (pLast->pNext)
		{
			pLast = pLast->pNext;
		}
		pLast->pNext = pUser;
	}
	else
	{
		gpChannelUsers_6F9C2B1C = pUser;
	}

	COMCALLBACK_AddUserHistory(pUser->szUserName, pUser->szCharacterName);

	++gnChannelUserCount_6F9C2B28;
	COMCALLBACK_UpdateChannelTitle();
	COMCALLBACK_ScrollUserList(0);
	COMCALLBACK_UpdateUserList();
	return pUser;
}

//Inlined
static void COMCALLBACK_ResetComponents(D2MultiChannelUserStrc* pUser)
{
	for (int32_t i = 0; i < 16; ++i)
	{
		pUser->pComponents[i] = (i == 1) ? 1 : 0;
		pUser->pComponentColors[i] = 0xFF;
	}
}

//Inlined
static void COMCALLBACK_SetUnknownProduct(D2MultiChannelUserStrc* pUser)
{
	pUser->dwProduct = 'NKNU';
	strcpy(pUser->szCharacterName, pUser->szUserName);
}

//Inlined
static void COMCALLBACK_FillComponents(uint8_t* pDestination, const char* pSource)
{
	int32_t i = 0;
	for (; i < 11; ++i)
	{
		pDestination[i] = pSource[i];
	}

	for (; i < 16; ++i)
	{
		pDestination[i] = 0xFF;
	}
}

//D2Multi.0x6F9AC970
uint8_t __fastcall COMCALLBACK_ParseStatstring(D2MultiChannelUserStrc* pUser, const char* szStatstring, uint32_t nFlags)
{
	const int32_t nLength = strlen(szStatstring);
	pUser->nCharacterFlags = 0;

	// Icon or character class used for the composite unit
	uint8_t nClass = 7;
	BOOL bRegularUser = FALSE;
	if (nFlags & CHATUSERFLAG_CHANNELOPERATOR)
	{
		nClass = 0x13;
	}
	else if (nFlags & CHATUSERFLAG_BATTLENETADMINISTRATOR)
	{
		nClass = 0x14;
		COMCALLBACK_ResetComponents(pUser);
		return nClass;
	}
	else if (nFlags & CHATUSERFLAG_BLIZZARDREPRESENTATIVE)
	{
		nClass = 0x12;
		COMCALLBACK_ResetComponents(pUser);
		return nClass;
	}
	else if (nFlags & CHATUSERFLAG_SPEAKER)
	{
		nClass = 0x17;
		COMCALLBACK_ResetComponents(pUser);
		return nClass;
	}
	else if (nFlags & 0x101000)
	{
		nClass = 0x15;
		COMCALLBACK_ResetComponents(pUser);
		return nClass;
	}
	else if (nLength < 4)
	{
		COMCALLBACK_ResetComponents(pUser);
		return 7;
	}
	else
	{
		bRegularUser = TRUE;
	}

	if (nLength < 4)
	{
		COMCALLBACK_ResetComponents(pUser);
		return nClass;
	}

	const uint32_t dwProduct = *(const uint32_t*)szStatstring;
	const char* pStatstring = szStatstring + 4;
	pUser->dwProduct = dwProduct;

	switch (dwProduct)
	{
	case 'JSTR':
	case 'SSHR':
	case 'STAR':
		if (bRegularUser)
		{
			nClass = 0x0D;
		}
		break;

	case 'CHAT':
		if (bRegularUser)
		{
			nClass = 0x16;
		}
		break;

	case 'DRTL':
	case 'DSHR':
	case 'DTST':
		if (bRegularUser)
		{
			nClass = 0x0A;
		}
		break;

	case 'W2BN':
		if (bRegularUser)
		{
			nClass = 0x0F;
		}
		break;

	case 'SEXP':
		if (bRegularUser)
		{
			nClass = 0x0E;
		}
		break;

	case 'W3XP':
	case 'WAR3':
		if (bRegularUser)
		{
			nClass = 0x10;
		}
		break;

	case 'D2DV':
	case 'D2ST':
	case 'D2XP':
	{
		if (pStatstring[0] == '\0')
		{
			// Open character
			if (nClass == 7)
			{
				nClass = 0x18;
			}
			COMCALLBACK_SetUnknownProduct(pUser);
			break;
		}

		D2_ASSERT(nLength - 4 > 0);

		// "Realm,CharacterName,Data"
		char* pRealmName = pUser->szRealmName;
		while (*pStatstring != ',')
		{
			*pRealmName++ = *pStatstring++;
		}
		*pRealmName = '\0';
		++pStatstring;

		char* pCharacterName = pUser->szCharacterName;
		while (*pStatstring != ',')
		{
			*pCharacterName++ = *pStatstring++;
		}
		*pCharacterName = '\0';
		++pStatstring;

		const char* pData = pStatstring;
		FOG_Decode14BitsFromString((uint16_t*)pData);
		COMCALLBACK_FillComponents(pUser->pComponents, &pData[2]);

		if (pUser->pComponents[0] == 0)
		{
			if (bRegularUser)
			{
				nClass = 7;
				COMCALLBACK_SetUnknownProduct(pUser);
			}
			break;
		}

		pUser->nClass = pData[13] - 1;
		COMCALLBACK_FillComponents(pUser->pComponentColors, &pData[14]);
		pUser->nLevel = (uint8_t)pData[25];
		pUser->nCharacterFlags = (uint16_t)FOG_Decode14BitsFromString((uint16_t*)&pData[26]);

		const uint16_t nCharacterFlags = pUser->nCharacterFlags;
		pUser->bHardcore = (nCharacterFlags >> 2) & 1;
		pUser->bDead = (nCharacterFlags >> 3) & 1;
		pUser->bExpansion = (nCharacterFlags >> 5) & 1;
		pUser->bLadder = (nCharacterFlags >> 6) & 1;

		if (bRegularUser)
		{
			if (pUser->bHardcore && pUser->bDead)
			{
				// Ghosts
				switch (pUser->nClass)
				{
				case 0:
				case 1:
				case 6:
				case 9:
					nClass = 9;
					break;

				default:
					nClass = 8;
					break;
				}
			}
			else
			{
				nClass = pUser->nClass;
			}
		}

		pUser->nGuildFlags = (uint16_t)FOG_Decode14BitsFromString((uint16_t*)&pData[28]);
		pUser->nLadder = ((uint8_t)pData[30] == 0xFF) ? 0 : pData[30];
		pUser->unk0x95 = ((uint8_t)pData[31] == 0xFF) ? 0 : pData[31];
		pUser->unk0x96 = ((uint8_t)pData[32] == 0xFF) ? 0 : pData[32];

		if (bRegularUser)
		{
			return nClass;
		}
		break;
	}
	default:
		if (bRegularUser)
		{
			nClass = 7;
			COMCALLBACK_SetUnknownProduct(pUser);
		}
		break;
	}

	COMCALLBACK_ResetComponents(pUser);
	return nClass;
}

//D2Multi.0x6F9ACD50
void __fastcall COMCALLBACK_UpdateUserDescription(D2MultiChannelUserStrc* pUser)
{
	Unicode wszUserName[51];
	Unicode wszCharacterName[17];
	Unicode wszUnk[51];
	Unicode wszRealmName[32];

	if (pUser->szUserName[0] == '*')
	{
		Unicode::win2Unicode(wszUserName, pUser->szUserName, 50);
		wszCharacterName[0] = 0;
	}
	else
	{
		char szCharacterName[16];
		CHATDLG_GetCharacterName(pUser->szUserName, szCharacterName);

		Unicode wszAccountName[51];
		Unicode::win2Unicode(wszAccountName, COMCALLBACK_GetAccountName(pUser->szUserName), 50);
		Unicode::win2Unicode(wszUserName, "*", 50);
		Unicode::strncat(wszUserName, wszAccountName, 50);
		Unicode::win2Unicode(wszCharacterName, szCharacterName, 16);
	}

	Unicode::win2Unicode(wszUnk, pUser->szUnk0x97, 50);
	Unicode::win2Unicode(wszRealmName, pUser->szRealmName, 32);

	const uint32_t dwProduct = pUser->dwProduct;
	uint16_t nLevel = 0;
	if (dwProduct == 'D2DV' || dwProduct == 'D2ST' || dwProduct == 'D2XP')
	{
		nLevel = pUser->nLevel;
	}

	D2Win_10154(pUser->pCompositeUnit, wszUserName, wszCharacterName, wszUnk, wszRealmName, nLevel, dwProduct);
}

//D2Multi.0x6F9ACF10
int32_t __fastcall COMCALLBACK_OnJoin(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szStatstring)
{
	D2MultiChannelUserStrc* pUser = COMCALLBACK_AddUser(szUserName, szStatstring, nFlags);
	if (gbShowJoinLeaveNotifications_6F9C2868)
	{
		char szMessage[500];
		sprintf(szMessage, "%s has joined the channel.", strlen(pUser->szCharacterName) ? pUser->szCharacterName : szUserName);
		COMCALLBACK_AddFormattedMessage(szMessage, 5);
	}
	return 1;
}

//D2Multi.0x6F9AD050
void __fastcall COMCALLBACK_ClearUserList()
{
	COMCALLBACK_DeselectUserAndUpdateButtons();

	D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C;
	while (pUser)
	{
		D2MultiChannelUserStrc* pNext = pUser->pNext;
		D2Win_10142_CompUnitDestroy(pUser->pCompositeUnit, 1);
		pUser->pCompositeUnit = nullptr;
		D2_FREE(pUser);
		pUser = pNext;
	}
	gpChannelUsers_6F9C2B1C = nullptr;

	D2MultiUserHistoryStrc* pHistory = gpUserHistory_6F9C2B20;
	while (pHistory)
	{
		D2MultiUserHistoryStrc* pNext = pHistory->pNext;
		D2_FREE(pHistory);
		pHistory = pNext;
	}
	gpUserHistory_6F9C2B20 = nullptr;
	gnUserHistoryCount_6F9C2B24 = 0;

	gnChannelUserCount_6F9C2B28 = 0;
	COMCALLBACK_UpdateChannelTitle();
	COMCALLBACK_ScrollUserList(0);
}

//D2Multi.0x6F9AD2F0
int32_t __fastcall COMCALLBACK_OnLeave(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	D2MultiChannelUserStrc* pPrevious = nullptr;
	for (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C; pUser; pUser = pUser->pNext)
	{
		if (!strcmp(COMCALLBACK_SkipCharacterName(pUser->szUserName), COMCALLBACK_SkipCharacterName(szUserName)))
		{
			if (gbShowJoinLeaveNotifications_6F9C2868)
			{
				char szMessage[500];
				sprintf(szMessage, "%s has left the channel.", strlen(pUser->szCharacterName) ? pUser->szCharacterName : pUser->szUserName);
				COMCALLBACK_AddFormattedMessage(szMessage, 5);
			}

			if (pPrevious)
			{
				pPrevious->pNext = pUser->pNext;
			}
			else
			{
				gpChannelUsers_6F9C2B1C = pUser->pNext;
			}

			if (gptSelectedUnit_6F9C2B30 == pUser)
			{
				COMCALLBACK_DeselectUserAndUpdateButtons();
			}

			D2Win_10142_CompUnitDestroy(pUser->pCompositeUnit, 1);
			pUser->pCompositeUnit = nullptr;
			D2_FREE(pUser);
			break;
		}

		pPrevious = pUser;
	}

	// Note: the count is decremented even if the user wasn't found
	--gnChannelUserCount_6F9C2B28;
	COMCALLBACK_UpdateChannelTitle();
	COMCALLBACK_ScrollUserList(0);
	COMCALLBACK_UpdateUserList();
	return 1;
}

//D2Multi.0x6F9AD5F0
void __fastcall COMCALLBACK_RemoveColorCodes(Unicode* wszText)
{
	D2_ASSERT(Unicode::strlen(wszText) < 500);

	const Unicode* wszColorCode = D2LANG_GetStringFromTblIndex(0xF9A);
	const int32_t nColorCodeLength = Unicode::strlen(wszColorCode);
	Unicode* pColorCode = Unicode::strstr(wszText, wszColorCode);
	while (pColorCode && pColorCode[nColorCodeLength] != 0)
	{
		const int32_t nRemaining = Unicode::strlen(pColorCode);
		memcpy(pColorCode, &pColorCode[nColorCodeLength + 1], sizeof(Unicode) * (nRemaining - nColorCodeLength));
		pColorCode = Unicode::strstr(wszText, wszColorCode);
	}
}

//D2Multi.0x6F9AD680
int32_t __fastcall COMCALLBACK_OnChannel(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szChannelName)
{
	char szMessage[500];
	sprintf(szMessage, "You have joined channel: %s", szChannelName);
	COMCALLBACK_AddFormattedMessage(szMessage, 5);

	strcpy(gszCurrentChannel_6F9C2918, szChannelName);
	strcpy(gpConfig_6F9C26F0->szCurrentChannelName, gszCurrentChannel_6F9C2918);
	if (!gpConfig_6F9C26F0->szDefaultChannelName[0])
	{
		strcpy(gpConfig_6F9C26F0->szDefaultChannelName, gszCurrentChannel_6F9C2918);
	}

	for (D2WinButtonStrc* pButton : gapUserButtons_6F9C26AC)
	{
		D2Win_10025_CONTROL_ToggleFirstFlag((D2WinControlStrc*)pButton, 1);
	}
	D2Win_10027_CONTROL_ToggleThirdFlag(gpUserList_6F9C2758, 0);
	COMCALLBACK_ClearUserList();
	return 1;
}

//D2Multi.0x6F9AD800
int32_t __fastcall COMCALLBACK_OnUserFlags(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szStatstring)
{
	for (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C; pUser; pUser = pUser->pNext)
	{
		if (!strcmp(pUser->szUserName, szUserName))
		{
			pUser->dwChatFlags = nFlags;
			const uint8_t nClass = COMCALLBACK_ParseStatstring(pUser, szStatstring, nFlags);
			SStrCopy(pUser->szUserName, szUserName, INT_MAX);
			COMCALLBACK_SetupCompositeUnit(pUser, nClass);
			return 1;
		}
	}
	return 0;
}

//D2Multi.0x6F9AD8E0
void __fastcall COMCALLBACK_AddOwnMessage(const char* szText)
{
	char szUserName[256];
	SStrCopy(szUserName, (const char*)gptComInt_6F9C19BC->field_18(), INT_MAX);

	int32_t nNameColor = 4;
	int32_t nTextColor = 0;
	for (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C; pUser; pUser = pUser->pNext)
	{
		if (!strcmp(COMCALLBACK_GetAccountName(pUser->szUserName), szUserName))
		{
			SStrCopy(szUserName, pUser->szUserName, INT_MAX);
			if (pUser->dwChatFlags & CHATUSERFLAG_CHANNELOPERATOR)
			{
				nNameColor = 0;
			}
			else if ((pUser->dwChatFlags & CHATUSERFLAG_BLIZZARDREPRESENTATIVE) || (pUser->dwChatFlags & CHATUSERFLAG_BATTLENETADMINISTRATOR))
			{
				nNameColor = 3;
				nTextColor = 3;
			}
			break;
		}
	}

	char szTitle[256];
	char szCharacterName[256];
	COMCALLBACK_GetUserDisplayName(szUserName, szTitle, szCharacterName);

	char szHeader[256];
	if (!strlen(szCharacterName))
	{
		sprintf(szHeader, "<%s> ", szUserName);
	}
	else if (strlen(szTitle))
	{
		sprintf(szHeader, "<%s%s> ", szTitle, szCharacterName);
	}
	else
	{
		sprintf(szHeader, "<%s> ", szCharacterName);
	}

	Unicode wszMessage[0x240];
	Unicode wszText[0x240];
	Unicode::win2Unicode(wszMessage, szHeader, std::size(wszMessage));
	Unicode::win2Unicode(wszText, szText, std::size(wszText));
	COMCALLBACK_RemoveColorCodes(wszMessage);
	COMCALLBACK_RemoveColorCodes(wszText);
	COMCALLBACK_PrependColorCode(wszMessage, nNameColor);
	COMCALLBACK_AppendColorCode(wszMessage, nTextColor);
	Unicode::strcat(wszMessage, wszText);
	CHATDLG_AddChatMessage(wszMessage, nTextColor);
}

//D2Multi.0x6F9ADCE0
void __fastcall COMCALLBACK_AddUserHistory(const char* szUserName, const char* szCharacterName)
{
	const char* szAccountName = COMCALLBACK_GetAccountName(szUserName);

	D2MultiUserHistoryStrc* pLast = nullptr;
	for (D2MultiUserHistoryStrc* pHistory = gpUserHistory_6F9C2B20; pHistory; pHistory = pHistory->pNext)
	{
		if (!strcmp(COMCALLBACK_GetAccountName(pHistory->szUserName), szAccountName))
		{
			strcpy(pHistory->szCharacterName, szCharacterName);
			return;
		}

		pLast = pHistory;
	}

	if (gnUserHistoryCount_6F9C2B24 >= COMCALLBACK_MAX_USER_HISTORY)
	{
		D2MultiUserHistoryStrc* pOldest = gpUserHistory_6F9C2B20;
		gpUserHistory_6F9C2B20 = pOldest->pNext;
		D2_FREE(pOldest);
		--gnUserHistoryCount_6F9C2B24;
	}

	D2MultiUserHistoryStrc* pHistory = D2_ALLOC_STRC(D2MultiUserHistoryStrc);
	strcpy(pHistory->szUserName, szUserName);
	strcpy(pHistory->szCharacterName, szCharacterName);
	pHistory->pNext = nullptr;

	if (pLast)
	{
		pLast->pNext = pHistory;
	}
	else
	{
		gpUserHistory_6F9C2B20 = pHistory;
	}
	++gnUserHistoryCount_6F9C2B24;
}

//D2Multi.0x6F9ADE40
void __fastcall COMCALLBACK_GetUserDisplayName(const char* szUserName, char* szTitle, char* szCharacterName)
{
	szCharacterName[0] = '\0';
	szTitle[0] = '\0';

	if (szUserName[0] == '*')
	{
		SStrCopy(szCharacterName, szUserName, INT_MAX);
		return;
	}

	const char* szAt = SStrChr(szUserName, '@');
	const char* szSeparator = SStrChr(szUserName, '*');
	if (szAt && szSeparator && szAt < szSeparator)
	{
		SStrCopy(szCharacterName, szUserName, INT_MAX);
		*(char*)SStrChr(szCharacterName, '*') = '\0';
		return;
	}

	for (D2MultiUserHistoryStrc* pHistory = gpUserHistory_6F9C2B20; pHistory; pHistory = pHistory->pNext)
	{
		if (!_stricmp(pHistory->szUserName, szUserName))
		{
			for (D2MultiChannelUserStrc* pUser = gpChannelUsers_6F9C2B1C; pUser; pUser = pUser->pNext)
			{
				if (!_stricmp(pUser->szUserName, szUserName))
				{
					const uint32_t nUnitFlags = D2Win_10155(pUser->pCompositeUnit);
					if ((gdwBitMasks[USERUNITFLAG_DIFFICULTY_LOW] & nUnitFlags) || (gdwBitMasks[USERUNITFLAG_DIFFICULTY_HIGH] & nUnitFlags))
					{
						const int32_t nTitle = ((nUnitFlags >> USERUNITFLAG_HARDCORE) & 1) * 3 + ((nUnitFlags >> USERUNITFLAG_DIFFICULTY_HIGH) & 1) * 2 + ((nUnitFlags >> USERUNITFLAG_DIFFICULTY_LOW) & 1);
						SStrCopy(szTitle, D2Win_10160_GetPlayerTitle(pUser->nClass, nTitle, (nUnitFlags >> USERUNITFLAG_EXPANSION) & 1), INT_MAX);
					}
					break;
				}
			}

			SStrCopy(szCharacterName, pHistory->szCharacterName, INT_MAX);
			break;
		}
	}

	if (szSeparator)
	{
		const size_t nLength = szSeparator - szUserName;
		memcpy(szCharacterName, szUserName, nLength);
		szCharacterName[nLength] = '\0';
		return;
	}

	SStrCopy(szCharacterName, szUserName, INT_MAX);
}

//D2Multi.0x6F9ADFC0
int32_t __fastcall COMCALLBACK_OnTalk(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	char szTitle[256];
	char szCharacterName[256];
	COMCALLBACK_GetUserDisplayName(szUserName, szTitle, szCharacterName);

	int32_t nNameColor = 0;
	int32_t nTextColor = 0;
	COMCALLBACK_GetUserColors(szUserName, &nNameColor, &nTextColor);

	char szHeader[256];
	if (!strlen(szCharacterName))
	{
		sprintf(szHeader, "<%s> ", szUserName);
	}
	else
	{
		char szDisplayName[256];
		COMCALLBACK_GetDisplayName(szTitle, szCharacterName, szDisplayName);
		sprintf(szHeader, "<%s> ", szDisplayName);
	}

	Unicode wszMessage[0x240];
	Unicode wszText[0x240];
	Unicode::win2Unicode(wszMessage, szHeader, std::size(wszMessage));
	Unicode::win2Unicode(wszText, szText, std::size(wszText));
	COMCALLBACK_RemoveColorCodes(wszMessage);
	COMCALLBACK_RemoveColorCodes(wszText);
	COMCALLBACK_PrependColorCode(wszMessage, nNameColor);
	COMCALLBACK_AppendColorCode(wszMessage, nTextColor);
	Unicode::strcat(wszMessage, wszText);
	CHATDLG_AddChatMessage(wszMessage, nTextColor);
	return 1;
}

//D2Multi.0x6F9AE3B0
int32_t __fastcall COMCALLBACK_OnInfo(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	COMCALLBACK_AddFormattedMessage(szText, 3);
	return 1;
}

//D2Multi.0x6F9AE490
int32_t __fastcall COMCALLBACK_OnError(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	COMCALLBACK_AddFormattedMessage(szText, 1);
	return 1;
}

//D2Multi.0x6F9AE570
int32_t __fastcall COMCALLBACK_OnChannelFull(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szChannelName)
{
	char szMessage[500];
	sprintf(szMessage, "The channel \"%s\" is full. If you are having problems using Battle.net commands, please click the Help button.", szChannelName);
	COMCALLBACK_AddFormattedMessage(szMessage, 1);
	return 1;
}

//D2Multi.0x6F9AE670
int32_t __fastcall COMCALLBACK_OnChannelRestricted(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szChannelName)
{
	char szMessage[500];
	sprintf(szMessage, "The channel \"%s\" is restricted. If you are having problems using Battle.net commands, please click the Help button.", szChannelName);
	COMCALLBACK_AddFormattedMessage(szMessage, 1);
	return 1;
}

//D2Multi.0x6F9AE770
int32_t __fastcall COMCALLBACK_OnChannelDoesNotExist(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szChannelName)
{
	// Create the channel
	gptComInt_6F9C19BC->JoinChannel((BYTE*)szChannelName, 1, 0);
	CHATDLG_ResetDialogs();
	return 1;
}

//D2Multi.0x6F9AE790
int32_t __fastcall COMCALLBACK_OnEmote(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	char szTitle[256];
	char szCharacterName[256];
	COMCALLBACK_GetUserDisplayName(szUserName, szTitle, szCharacterName);

	char szMessage[500];
	if (!strlen(szCharacterName))
	{
		sprintf(szMessage, "*%s %s*", szUserName, szText);
	}
	else
	{
		char szDisplayName[256];
		COMCALLBACK_GetDisplayName(szTitle, szCharacterName, szDisplayName);
		sprintf(szMessage, "*%s %s*", szDisplayName, szText);
	}

	COMCALLBACK_AddFormattedMessage(szMessage, 5);
	return 1;
}

//D2Multi.0x6F9AEA10
int32_t __fastcall COMCALLBACK_OnWhisper(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	char szTitle[256];
	char szCharacterName[256];
	COMCALLBACK_GetUserDisplayName(szUserName, szTitle, szCharacterName);

	char szDisplayName[256];
	COMCALLBACK_GetDisplayName(szTitle, szCharacterName, szDisplayName);

	// Remember who to answer with /r
	const char* szAccountName = COMCALLBACK_GetAccountName(szUserName);
	strcpy(gszLastWhisperSender_6F9C1898, szAccountName);

	char szMessage[500];
	if (!szDisplayName[0] || (szDisplayName[0] == '*' && !strcmp(COMCALLBACK_GetAccountName(szDisplayName), COMCALLBACK_GetAccountName(szAccountName))))
	{
		sprintf(szMessage, "%s whispers: %s", szDisplayName, szText);
	}
	else
	{
		sprintf(szMessage, "%s (*%s) whispers: %s", szDisplayName, szAccountName, szText);
	}

	COMCALLBACK_AddFormattedMessage(szMessage, 2);
	return 1;
}

//D2Multi.0x6F9AED90
int32_t __fastcall COMCALLBACK_OnWhisperSent(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	char szTitle[256];
	char szCharacterName[256];
	COMCALLBACK_GetUserDisplayName(szUserName, szTitle, szCharacterName);

	char szMessage[500];
	if (!strlen(szCharacterName))
	{
		sprintf(szMessage, "You whisper to %s: %s", COMCALLBACK_GetAccountName(szUserName), szText);
	}
	else
	{
		char szDisplayName[256];
		COMCALLBACK_GetDisplayName(szTitle, szCharacterName, szDisplayName);
		sprintf(szMessage, "You whisper to %s: %s", szDisplayName, szText);
	}

	COMCALLBACK_AddFormattedMessage(szMessage, 2);
	return 1;
}

//D2Multi.0x6F9AF020
int32_t __fastcall COMCALLBACK_OnIgnoredEvent(uint32_t nFlags, uint32_t nPing, const char* szUserName, const char* szText)
{
	return 0;
}

//D2Multi.0x6F9AF030
void __fastcall COMCALLBACK_UpdateChatButtons()
{
	const Unicode* wszText = D2Win_10077_EDITBOX_GetText(gpChatEditBox_6F9C28A8);
	const BOOL bHasText = wszText && Unicode::strlen(wszText);
	D2Win_10025_CONTROL_ToggleFirstFlag(gpEmoteButton_6F9C266C, bHasText);
	D2Win_10025_CONTROL_ToggleFirstFlag(gpSendButton_6F9C2658, bHasText);
	D2Win_10025_CONTROL_ToggleFirstFlag(gpWhisperButton_6F9C265C, gptSelectedUnit_6F9C2B30 && bHasText);

	uint32_t nSquelched = 0;
	if (gptSelectedUnit_6F9C2B30 && gptSelectedUnit_6F9C2B30->pCompositeUnit)
	{
		nSquelched = gdwBitMasks[USERUNITFLAG_SQUELCHED] & D2Win_10155(gptSelectedUnit_6F9C2B30->pCompositeUnit);
	}

	D2Win_10025_CONTROL_ToggleFirstFlag(gpSquelchButton_6F9C2664, gptSelectedUnit_6F9C2B30 && !nSquelched);
	D2Win_10025_CONTROL_ToggleFirstFlag(gpUnsquelchButton_6F9C2668, gptSelectedUnit_6F9C2B30 && nSquelched);
}

//Inlined
static void COMCALLBACK_GetColorCode(Unicode* wszColorCode, int32_t nColor)
{
	Unicode::strcpy(wszColorCode, D2LANG_GetStringFromTblIndex(0xF9A));

	char szColor[4];
	Unicode wszColor[3];
	wsprintfA(szColor, "%d", nColor);
	Unicode::toUnicode(wszColor, szColor, 2);
	Unicode::strcat(wszColorCode, wszColor);
}

//D2Multi.0x6F9AF110
void __fastcall COMCALLBACK_AppendColorCode(Unicode* wszText, int32_t nColor)
{
	Unicode wszColorCode[0x200];
	COMCALLBACK_GetColorCode(wszColorCode, nColor);

	if (!wszText[0])
	{
		Unicode::strcpy(wszText, wszColorCode);
		return;
	}

	D2_ASSERT(Unicode::strlen(wszText) < 500);
	Unicode::strcat(wszText, wszColorCode);
}

//D2Multi.0x6F9AF1F0
void __fastcall COMCALLBACK_PrependColorCode(Unicode* wszText, int32_t nColor)
{
	Unicode wszColorCode[0x200];
	COMCALLBACK_GetColorCode(wszColorCode, nColor);

	if (wszText[0])
	{
		D2_ASSERT(Unicode::strlen(wszText) < 500);
		Unicode::strcat(wszColorCode, wszText);
	}

	Unicode::strcpy(wszText, wszColorCode);
}
