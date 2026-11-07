#include "MOD/ModPatches.h"

#include <D2BasicTypes.h>
#include <D2Dungeon.h>
#include <D2Inventory.h>
#include <D2Items.h>
#include <D2Lang.h>
#include <D2QuestRecord.h>
#include <D2StatList.h>
#include <D2Text.h>
#include <D2Unicode.h>
#include <DataTbls/MonsterTbls.h>
#include <DataTbls/SubQuestTbls.h>
#include <Fog.h>
#include <Units/Player.h>
#include <Units/Units.h>
#include <D2PacketDef.h>

#include "GAME/Clients.h"
#include "GAME/Game.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <mutex>
#include <unordered_map>
#include <vector>

// Mod (not part of the original game): subquests given by NPCs. See doc/SubQuests.md.
//
// The definitions are SubQuests.txt (D2Common, exports 11315..11317). A player's progress per difficulty is kept here,
// keyed by the player unit, set up whenever a save is processed into a player (a new character included) and written
// as an extra block at the end of the .d2s. Progress advances from detours of the original quest events: monster
// kills, level changes, item pickups and NPC talks. Each detour runs the original first.

void* gpfnOriginalParseKill = nullptr;
void* gpfnOriginalChangeLevel = nullptr;
void* gpfnOriginalItemPickedUp = nullptr;
void* gpfnOriginalNPCActivate = nullptr;
void* gpfnOriginalCreateSaveFile = nullptr;
void* gpfnOriginalProcessSaveFile = nullptr;
void* gpfnOriginalOperateHandler = nullptr;
void* gpfnOriginalHandleChatMessage = nullptr;

//----------------------------------------------------------------------------------------------------------------------
// Original functions and D2MOO D2Common exports
//----------------------------------------------------------------------------------------------------------------------

static constexpr uint32_t SUBQUEST_ADDR_GETOWNER = 0x6FCBBB70;				// SUNIT_GetOwner
static constexpr uint32_t SUBQUEST_ADDR_GETCLIENTFROMPLAYER = 0x6FCBC2E0;	// SUNIT_GetClientFromPlayer
static constexpr uint32_t SUBQUEST_ADDR_GETPARTYID = 0x6FCBA5F0;			// PARTY_GetPartyIdForUnitOwner
static constexpr uint32_t SUBQUEST_ADDR_GETSUPERUNIQUEID = 0x6FC6AD10;		// MONSTERUNIQUE_GetSuperUniqueBossHcIdx
static constexpr uint32_t SUBQUEST_ADDR_SPAWNSUPERUNIQUE = 0x6FC6F690;		// D2GAME_SpawnSuperUnique_6FC6F690
static constexpr uint32_t SUBQUEST_ADDR_CREATEITEM = 0x6FC95DF0;			// QUESTS_CreateItem
static constexpr uint32_t SUBQUEST_ADDR_DELETEITEM = 0x6FC94A50;			// QUESTS_DeleteItem
static constexpr uint32_t SUBQUEST_ADDR_LEVELUP = 0x6FC7EC00;				// PLAYERSTATS_LevelUp
static constexpr uint32_t SUBQUEST_ADDR_SENDPACKET26 = 0x6FC3DDF0;			// D2GAME_PACKETS_SendPacket0x26_ServerMessage_6FC3DDF0
static constexpr uint32_t SUBQUEST_ADDR_DROPTC = 0x6FC51360;				// D2GAME_DropTC_6FC51360
static constexpr uint32_t SUBQUEST_ADDR_GETSERVERUNIT = 0x6FCBBB00;			// SUNIT_GetServerUnit

using ParseKillFn = void(__fastcall*)(D2GameStrc*, D2UnitStrc*, D2UnitStrc*);
using ChangeLevelFn = void(__fastcall*)(D2GameStrc*, int32_t, int32_t, D2UnitStrc*);
using ItemPickedUpFn = void(__fastcall*)(D2GameStrc*, D2UnitStrc*, D2UnitStrc*);
using NPCActivateFn = void(__fastcall*)(D2ClientStrc*, D2UnitStrc*, D2UnitStrc*, D2TextHeaderStrc*);
using CreateSaveFileFn = int32_t(__fastcall*)(D2GameStrc*, D2UnitStrc*, uint8_t*, uint32_t*, uint32_t, int32_t, int32_t);
using ProcessSaveFileFn = int32_t(__fastcall*)(D2GameStrc*, D2ClientStrc*, uint8_t*, uint32_t, D2UnitStrc**, D2ActiveRoomStrc*, int32_t, int32_t);

using GetOwnerFn = D2UnitStrc*(__fastcall*)(D2GameStrc*, D2UnitStrc*);
using GetClientFromPlayerFn = D2ClientStrc*(__fastcall*)(D2UnitStrc*, const char*, int32_t);
using GetPartyIdFn = int16_t(__fastcall*)(D2GameStrc*, D2UnitStrc*);
using GetSuperUniqueIdFn = int32_t(__fastcall*)(D2GameStrc*, D2UnitStrc*);
using SpawnSuperUniqueFn = D2UnitStrc*(__fastcall*)(D2GameStrc*, D2ActiveRoomStrc*, int32_t, int32_t, int32_t);
using CreateItemFn = D2UnitStrc*(__fastcall*)(D2GameStrc*, D2UnitStrc*, uint32_t, int32_t, uint8_t, int32_t);
using DeleteItemFn = void(__fastcall*)(D2GameStrc*, D2UnitStrc*, uint32_t);
using LevelUpFn = void(__fastcall*)(D2GameStrc*, D2UnitStrc*);
using SendPacket26Fn = void(__fastcall*)(D2ClientStrc*, D2GSPacketSrv26*);
using DropTCFn = void(__fastcall*)(D2GameStrc*, D2UnitStrc*, D2UnitStrc*, D2TCExShortStrc*, int32_t, int32_t, int32_t, D2UnitStrc**, int32_t*, int32_t);
using GetServerUnitFn = D2UnitStrc*(__fastcall*)(D2GameStrc*, int32_t, int32_t);
using OperateHandlerFn = int32_t(__fastcall*)(D2GameStrc*, D2UnitStrc*, int32_t, int32_t, int32_t*);
using ChatMessageFn = int32_t(__fastcall*)(D2GameStrc*, D2UnitStrc*, void*, int32_t);

using GetSubQuestCountFn = int(__stdcall*)();
using GetSubQuestRecordFn = const D2SubQuestTxt*(__stdcall*)(int);
using GetSubQuestRecordByIdFn = const D2SubQuestTxt*(__stdcall*)(uint32_t);

template<typename T>
static T SUBQUEST_Original(uint32_t nAddress)
{
	return (T)MODPATCH_GetOriginalD2GameAddress(nAddress);
}

static int SUBQUEST_GetCount()
{
	static GetSubQuestCountFn pfn = (GetSubQuestCountFn)MODPATCH_FindD2CommonExport("DATATBLS_GetSubQuestCount");
	return pfn ? pfn() : 0;
}

static const D2SubQuestTxt* SUBQUEST_GetRecord(int nIndex)
{
	static GetSubQuestRecordFn pfn = (GetSubQuestRecordFn)MODPATCH_FindD2CommonExport("DATATBLS_GetSubQuestRecord");
	return pfn ? pfn(nIndex) : nullptr;
}

static const D2SubQuestTxt* SUBQUEST_GetRecordById(uint32_t dwId)
{
	static GetSubQuestRecordByIdFn pfn = (GetSubQuestRecordByIdFn)MODPATCH_FindD2CommonExport("DATATBLS_GetSubQuestRecordById");
	return pfn ? pfn(dwId) : nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
// Progress
//----------------------------------------------------------------------------------------------------------------------

enum D2SubQuestState : uint8_t
{
	SUBQUESTSTATE_NONE = 0,			// not given yet
	SUBQUESTSTATE_ACTIVE = 1,		// given, goal not reached
	SUBQUESTSTATE_READY = 2,		// goal reached, to be turned in (item goals: announced, counted again on turn-in)
	SUBQUESTSTATE_DONE = 3,			// turned in and rewarded

	SUBQUESTSTATE_MASK = 0x7F,
	SUBQUESTSTATE_COMPLETED_FLAG = 0x80,	// set once turned in, kept while a Repeatable subquest is under way again
};

struct D2SubQuestProgress
{
	uint8_t nState = SUBQUESTSTATE_NONE;
	uint16_t nCounter = 0;
};

static uint8_t SUBQUEST_StateOf(const D2SubQuestProgress& tProgress)
{
	return tProgress.nState & SUBQUESTSTATE_MASK;
}

// Sets the state and keeps the completed-before flag.
static void SUBQUEST_SetState(D2SubQuestProgress& tProgress, uint8_t nState)
{
	tProgress.nState = (tProgress.nState & SUBQUESTSTATE_COMPLETED_FLAG) | nState;
}

struct D2PlayerSubQuests
{
	std::map<uint16_t, D2SubQuestProgress> tProgress[3];	// per difficulty, by subquest Id
};

static std::unordered_map<D2UnitStrc*, D2PlayerSubQuests> sgPlayerSubQuests;
static std::recursive_mutex sgSubQuestMutex;

static uint8_t SUBQUEST_GetDifficulty(D2GameStrc* pGame)
{
	return pGame->nDifficulty < 3 ? pGame->nDifficulty : 0;
}

static D2SubQuestProgress& SUBQUEST_GetProgress(D2GameStrc* pGame, D2UnitStrc* pPlayer, const D2SubQuestTxt* pRecord)
{
	return sgPlayerSubQuests[pPlayer].tProgress[SUBQUEST_GetDifficulty(pGame)][(uint16_t)pRecord->dwId];
}

static uint8_t SUBQUEST_GetState(D2GameStrc* pGame, D2UnitStrc* pPlayer, const D2SubQuestTxt* pRecord)
{
	auto itPlayer = sgPlayerSubQuests.find(pPlayer);
	if (itPlayer == sgPlayerSubQuests.end())
	{
		return SUBQUESTSTATE_NONE;
	}

	const auto& tProgress = itPlayer->second.tProgress[SUBQUEST_GetDifficulty(pGame)];
	auto it = tProgress.find((uint16_t)pRecord->dwId);
	return it != tProgress.end() ? it->second.nState & SUBQUESTSTATE_MASK : SUBQUESTSTATE_NONE;
}

// Whether the player has turned the subquest in at least once (in this difficulty).
static bool SUBQUEST_HasCompleted(D2GameStrc* pGame, D2UnitStrc* pPlayer, const D2SubQuestTxt* pRecord)
{
	auto itPlayer = sgPlayerSubQuests.find(pPlayer);
	if (itPlayer == sgPlayerSubQuests.end())
	{
		return false;
	}

	const auto& tProgress = itPlayer->second.tProgress[SUBQUEST_GetDifficulty(pGame)];
	auto it = tProgress.find((uint16_t)pRecord->dwId);
	return it != tProgress.end() && ((it->second.nState & SUBQUESTSTATE_COMPLETED_FLAG) || (it->second.nState & SUBQUESTSTATE_MASK) == SUBQUESTSTATE_DONE);
}

// Calls pfnVisit(pRecord, tProgress) for each of the player's subquests in this difficulty that are under way.
template<typename VisitFn>
static void SUBQUEST_ForEachActive(D2GameStrc* pGame, D2UnitStrc* pPlayer, VisitFn pfnVisit)
{
	auto itPlayer = sgPlayerSubQuests.find(pPlayer);
	if (itPlayer == sgPlayerSubQuests.end())
	{
		return;
	}

	for (auto& [nId, tProgress] : itPlayer->second.tProgress[SUBQUEST_GetDifficulty(pGame)])
	{
		const uint8_t nState = SUBQUEST_StateOf(tProgress);
		if (nState == SUBQUESTSTATE_ACTIVE || nState == SUBQUESTSTATE_READY)
		{
			if (const D2SubQuestTxt* pRecord = SUBQUEST_GetRecordById(nId))
			{
				pfnVisit(pRecord, tProgress);
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
// Messages
//----------------------------------------------------------------------------------------------------------------------

// A .tbl string as ANSI text, the fallback when the key is not in the string tables.
static void SUBQUEST_GetText(char* szOut, size_t nSize, int16_t nTblIndex, const char* szFallback)
{
	if (nTblIndex > 0)
	{
		if (const Unicode* pText = D2LANG_GetStringFromTblIndex(nTblIndex))
		{
			Unicode::unicode2Win(szOut, pText, (int)nSize - 1);
			szOut[nSize - 1] = 0;
			return;
		}
	}

	snprintf(szOut, nSize, "%s", szFallback);
}

// The text of a .tbl key a mod may define to translate the messages, else the English default.
static void SUBQUEST_GetKeyedText(char* szOut, size_t nSize, const char* szKey, const char* szDefault)
{
	char szKeyCopy[32] = {};
	strncpy_s(szKeyCopy, szKey, _TRUNCATE);
	const Unicode* pUnused = nullptr;
	const int16_t nIndex = D2LANG_GetTblIndex(szKeyCopy, &pUnused);
	SUBQUEST_GetText(szOut, nSize, nIndex, szDefault);
}

static void SUBQUEST_GetName(char* szOut, size_t nSize, const D2SubQuestTxt* pRecord)
{
	char szFallback[32];
	snprintf(szFallback, sizeof(szFallback), "Subquest %u", pRecord->dwId);
	SUBQUEST_GetText(szOut, nSize, pRecord->nNameTbl, szFallback);
}

// A line in the player's chat log (system message, gold).
static void SUBQUEST_SendMessage(D2UnitStrc* pPlayer, const char* szText)
{
	D2ClientStrc* pClient = SUBQUEST_Original<GetClientFromPlayerFn>(SUBQUEST_ADDR_GETCLIENTFROMPLAYER)(pPlayer, __FILE__, __LINE__);
	if (!pClient)
	{
		return;
	}

	D2GSPacketSrv26 tPacket = {};
	tPacket.nHeader = 0x26;
	tPacket.nMessageType = 4;
	tPacket.nMessageColor = 4;
	strncpy_s(tPacket.szMessage, szText, _TRUNCATE);
	SUBQUEST_Original<SendPacket26Fn>(SUBQUEST_ADDR_SENDPACKET26)(pClient, &tPacket);
}

// "<prefix>: <name>" and, with nCount > 0, " (n/count)".
static void SUBQUEST_SendStatusMessage(D2UnitStrc* pPlayer, const D2SubQuestTxt* pRecord, const char* szPrefixKey, const char* szPrefixDefault, int32_t nCurrent = 0, int32_t nCount = 0)
{
	char szPrefix[128];
	char szName[128];
	char szLine[256];
	SUBQUEST_GetKeyedText(szPrefix, sizeof(szPrefix), szPrefixKey, szPrefixDefault);
	SUBQUEST_GetName(szName, sizeof(szName), pRecord);
	if (nCount > 0)
	{
		snprintf(szLine, sizeof(szLine), "%s: %s (%d/%d)", szPrefix, szName, nCurrent, nCount);
	}
	else
	{
		snprintf(szLine, sizeof(szLine), "%s: %s", szPrefix, szName);
	}
	SUBQUEST_SendMessage(pPlayer, szLine);
}

// The NPC says the text when the player starts talking to it (the client plays the first such node at once).
static void SUBQUEST_Say(D2TextHeaderStrc* pTextControl, int16_t nTblIndex)
{
	if (pTextControl && nTblIndex > 0)
	{
		TEXT_AddNodeToTextList(pTextControl, nTblIndex, 1);
	}
}

//----------------------------------------------------------------------------------------------------------------------
// Goals and rewards
//----------------------------------------------------------------------------------------------------------------------

static void SUBQUEST_SetGoalReached(D2UnitStrc* pPlayer, const D2SubQuestTxt* pRecord, D2SubQuestProgress& tProgress)
{
	SUBQUEST_SetState(tProgress, SUBQUESTSTATE_READY);
	SUBQUEST_SendStatusMessage(pPlayer, pRecord, "SubQuestReady", "Subquest goal reached, return to the quest giver");
}

static int32_t SUBQUEST_CountItems(D2UnitStrc* pPlayer, uint32_t dwCode)
{
	if (!pPlayer->pInventory || !dwCode)
	{
		return 0;
	}

	int32_t nCount = 0;
	D2UnitStrc* pCursorItem = INVENTORY_GetCursorItem(pPlayer->pInventory);
	if (pCursorItem && ITEMS_GetBaseCode(pCursorItem) == dwCode)
	{
		++nCount;
	}

	for (D2UnitStrc* pItem = INVENTORY_GetFirstItem(pPlayer->pInventory); pItem; pItem = INVENTORY_GetNextItem(pItem))
	{
		D2UnitStrc* pInvItem = INVENTORY_UnitIsItem(pItem);
		if (pInvItem && ITEMS_GetBaseCode(pInvItem) == dwCode && ITEMS_GetInvPage(pInvItem) != INVPAGE_EQUIP)
		{
			++nCount;
		}
	}

	return nCount;
}

static void SUBQUEST_GiveExperience(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nExp)
{
	// As the game's own experience rewards (A5Q5): fill the current level, level up, repeat.
	while (nExp > 0 && STATLIST_UnitGetStatValue(pPlayer, STAT_LEVEL, 0) < 99)
	{
		const int32_t nNextExp = STATLIST_GetUnitBaseStat(pPlayer, STAT_NEXTEXP, 0);
		const int32_t nCurrentExp = STATLIST_GetUnitBaseStat(pPlayer, STAT_EXPERIENCE, 0);
		const int32_t nDeltaExp = nNextExp - nCurrentExp;
		if (nDeltaExp <= 0)
		{
			break;
		}

		if (nExp < nDeltaExp)
		{
			STATLIST_SetUnitStat(pPlayer, STAT_EXPERIENCE, nCurrentExp + nExp, 0);
			break;
		}

		STATLIST_SetUnitStat(pPlayer, STAT_EXPERIENCE, nNextExp, 0);
		STATLIST_SetUnitStat(pPlayer, STAT_LASTEXP, nDeltaExp, 0);
		SUBQUEST_Original<LevelUpFn>(SUBQUEST_ADDR_LEVELUP)(pGame, pPlayer);
		nExp -= nDeltaExp;
	}
}

static void SUBQUEST_GiveGold(D2UnitStrc* pPlayer, int32_t nGold)
{
	if (nGold <= 0)
	{
		return;
	}

	// Into the inventory up to its limit, the rest into the stash up to its limit.
	const int32_t nInventoryRoom = (int32_t)UNITS_GetInventoryGoldLimit(pPlayer) - STATLIST_UnitGetStatValue(pPlayer, STAT_GOLD, 0);
	const int32_t nToInventory = std::max(0, std::min(nGold, nInventoryRoom));
	if (nToInventory)
	{
		STATLIST_AddUnitStat(pPlayer, STAT_GOLD, nToInventory, 0);
	}

	const int32_t nRest = nGold - nToInventory;
	const int32_t nStashRoom = (int32_t)UNITS_GetStashGoldLimit(pPlayer) - STATLIST_UnitGetStatValue(pPlayer, STAT_GOLDBANK, 0);
	const int32_t nToStash = std::max(0, std::min(nRest, nStashRoom));
	if (nToStash)
	{
		STATLIST_AddUnitStat(pPlayer, STAT_GOLDBANK, nToStash, 0);
	}
}

static void SUBQUEST_GiveRewards(D2GameStrc* pGame, D2UnitStrc* pPlayer, D2UnitStrc* pNpc, const D2SubQuestTxt* pRecord)
{
	const uint8_t nDifficulty = SUBQUEST_GetDifficulty(pGame);

	SUBQUEST_GiveExperience(pGame, pPlayer, pRecord->nExp[nDifficulty]);
	SUBQUEST_GiveGold(pPlayer, pRecord->nGold[nDifficulty]);

	if (pRecord->nStatPoints > 0)
	{
		STATLIST_AddUnitStat(pPlayer, STAT_STATPTS, pRecord->nStatPoints, 0);
	}

	if (pRecord->nSkillPoints > 0)
	{
		STATLIST_AddUnitStat(pPlayer, STAT_SKILLPTS, pRecord->nSkillPoints, 0);
	}

	if (pRecord->dwRewardItemCode)
	{
		const int32_t nItemLevel = pRecord->nRewardItemLevel > 0 ? pRecord->nRewardItemLevel : STATLIST_UnitGetStatValue(pPlayer, STAT_LEVEL, 0);
		const uint8_t nQuality = (uint8_t)(pRecord->nRewardItemQuality > 0 ? pRecord->nRewardItemQuality : ITEMQUAL_NORMAL);
		SUBQUEST_Original<CreateItemFn>(SUBQUEST_ADDR_CREATEITEM)(pGame, pPlayer, pRecord->dwRewardItemCode, nItemLevel, nQuality, 1);
	}

	// A treasure class drops like a monster's loot, at the giver's feet (the drop needs a unit to drop from), always
	// (its NoDrop is ignored), at the item level of RewardItemLevel or the character's.
	if (pRecord->szRewardTC[0] && pNpc)
	{
		char szTreasureClass[32] = {};
		strncpy_s(szTreasureClass, pRecord->szRewardTC, _TRUNCATE);
		if (D2TCExShortStrc* pTreasureClass = DATATBLS_GetTreasureClassExRecordFromName(szTreasureClass))
		{
			const int32_t nItemLevel = pRecord->nRewardItemLevel > 0 ? pRecord->nRewardItemLevel : STATLIST_UnitGetStatValue(pPlayer, STAT_LEVEL, 0);
			SUBQUEST_Original<DropTCFn>(SUBQUEST_ADDR_DROPTC)(pGame, pNpc, pPlayer, pTreasureClass, 0, nItemLevel, 1, nullptr, nullptr, 0);
		}
		else
		{
			FOG_Trace("Subquest %u: RewardTC '%s' is not in TreasureClassEx.txt", pRecord->dwId, pRecord->szRewardTC);
		}
	}
}

// Whether the player may be given the subquest now.
static bool SUBQUEST_CanOffer(D2GameStrc* pGame, D2UnitStrc* pPlayer, const D2SubQuestTxt* pRecord)
{
	if (pRecord->nReqLevel > 0 && STATLIST_UnitGetStatValue(pPlayer, STAT_LEVEL, 0) < pRecord->nReqLevel)
	{
		return false;
	}

	if (pRecord->nReqQuest > 0)
	{
		D2PlayerDataStrc* pPlayerData = UNITS_GetPlayerData(pPlayer);
		if (!pPlayerData || !QUESTRECORD_GetQuestState(pPlayerData->pQuestData[SUBQUEST_GetDifficulty(pGame)], pRecord->nReqQuest, QFLAG_REWARDGRANTED))
		{
			return false;
		}
	}

	if (pRecord->dwReqSubQuest)
	{
		const D2SubQuestTxt* pRequired = SUBQUEST_GetRecordById(pRecord->dwReqSubQuest);
		if (!pRequired || !SUBQUEST_HasCompleted(pGame, pPlayer, pRequired))
		{
			return false;
		}
	}

	return true;
}

// The giver's part of a talk: turn in, remind, or give the next subquest. One of them per talk.
static void SUBQUEST_TalkToGiver(D2GameStrc* pGame, D2UnitStrc* pPlayer, D2UnitStrc* pNpc, D2TextHeaderStrc* pTextControl)
{
	const int nCount = SUBQUEST_GetCount();

	// Subquests under way first, in the order of the file.
	for (int i = 0; i < nCount; ++i)
	{
		const D2SubQuestTxt* pRecord = SUBQUEST_GetRecord(i);
		if (!pRecord || pRecord->nGiver != (int32_t)pNpc->dwClassId)
		{
			continue;
		}

		const uint8_t nState = SUBQUEST_GetState(pGame, pPlayer, pRecord);
		if (nState != SUBQUESTSTATE_ACTIVE && nState != SUBQUESTSTATE_READY)
		{
			continue;
		}

		D2SubQuestProgress& tProgress = SUBQUEST_GetProgress(pGame, pPlayer, pRecord);
		bool bGoalReached = nState == SUBQUESTSTATE_READY;
		if (pRecord->nGoalType == SUBQUESTGOAL_ITEM)
		{
			bGoalReached = SUBQUEST_CountItems(pPlayer, pRecord->dwGoalItemCode) >= pRecord->nGoalCount;
		}

		if (!bGoalReached)
		{
			SUBQUEST_SetState(tProgress, SUBQUESTSTATE_ACTIVE);
			SUBQUEST_Say(pTextControl, pRecord->nTextProgressTbl);
			return;
		}

		if (pRecord->nGoalType == SUBQUESTGOAL_ITEM && pRecord->dwTakeItems)
		{
			for (int32_t j = 0; j < pRecord->nGoalCount; ++j)
			{
				SUBQUEST_Original<DeleteItemFn>(SUBQUEST_ADDR_DELETEITEM)(pGame, pPlayer, pRecord->dwGoalItemCode);
			}
		}

		SUBQUEST_SetState(tProgress, SUBQUESTSTATE_DONE);
		tProgress.nState |= SUBQUESTSTATE_COMPLETED_FLAG;
		SUBQUEST_GiveRewards(pGame, pPlayer, pNpc, pRecord);
		SUBQUEST_Say(pTextControl, pRecord->nTextDoneTbl);
		SUBQUEST_SendStatusMessage(pPlayer, pRecord, "SubQuestDone", "Subquest completed");
		return;
	}

	// Then the first one the player may start.
	for (int i = 0; i < nCount; ++i)
	{
		const D2SubQuestTxt* pRecord = SUBQUEST_GetRecord(i);
		if (!pRecord || pRecord->nGiver != (int32_t)pNpc->dwClassId || !SUBQUEST_CanOffer(pGame, pPlayer, pRecord))
		{
			continue;
		}

		// New, or turned in and Repeatable.
		const uint8_t nState = SUBQUEST_GetState(pGame, pPlayer, pRecord);
		if (nState != SUBQUESTSTATE_NONE && !(nState == SUBQUESTSTATE_DONE && pRecord->dwRepeatable))
		{
			continue;
		}

		D2SubQuestProgress& tProgress = SUBQUEST_GetProgress(pGame, pPlayer, pRecord);
		SUBQUEST_SetState(tProgress, SUBQUESTSTATE_ACTIVE);
		tProgress.nCounter = 0;
		SUBQUEST_Say(pTextControl, pRecord->nTextOfferTbl);
		SUBQUEST_SendStatusMessage(pPlayer, pRecord, "SubQuestNew", "New subquest");

		// An item goal may already be met.
		if (pRecord->nGoalType == SUBQUESTGOAL_ITEM && SUBQUEST_CountItems(pPlayer, pRecord->dwGoalItemCode) >= pRecord->nGoalCount)
		{
			SUBQUEST_SetGoalReached(pPlayer, pRecord, tProgress);
		}
		return;
	}
}

static int32_t SUBQUEST_GetUnitLevelId(D2UnitStrc* pUnit)
{
	D2ActiveRoomStrc* pRoom = pUnit ? UNITS_GetRoom(pUnit) : nullptr;
	return pRoom ? DUNGEON_GetLevelIdFromRoom(pRoom) : 0;
}

// The kill counts for the killer and for the members of the killer's party in the monster's level.
static void SUBQUEST_OnMonsterKilled(D2GameStrc* pGame, D2UnitStrc* pKiller, D2UnitStrc* pMonster)
{
	const int32_t nLevelId = SUBQUEST_GetUnitLevelId(pMonster);
	const int32_t nSuperUnique = SUBQUEST_Original<GetSuperUniqueIdFn>(SUBQUEST_ADDR_GETSUPERUNIQUEID)(pGame, pMonster);
	GetPartyIdFn pfnGetPartyId = SUBQUEST_Original<GetPartyIdFn>(SUBQUEST_ADDR_GETPARTYID);
	const int16_t nKillerParty = pfnGetPartyId(pGame, pKiller);

	for (D2ClientStrc* pClient = pGame->pClientList; pClient; pClient = pClient->pNext)
	{
		D2UnitStrc* pPlayer = pClient->pPlayer;
		if (!pPlayer)
		{
			continue;
		}

		if (pPlayer != pKiller && (nKillerParty == -1 || pfnGetPartyId(pGame, pPlayer) != nKillerParty || SUBQUEST_GetUnitLevelId(pPlayer) != nLevelId))
		{
			continue;
		}

		SUBQUEST_ForEachActive(pGame, pPlayer, [&](const D2SubQuestTxt* pRecord, D2SubQuestProgress& tProgress)
		{
			if (SUBQUEST_StateOf(tProgress) != SUBQUESTSTATE_ACTIVE)
			{
				return;
			}

			if (pRecord->nGoalType == SUBQUESTGOAL_KILL && pRecord->nGoalMonster == (int32_t)pMonster->dwClassId
				&& (pRecord->nGoalLevel <= 0 || pRecord->nGoalLevel == nLevelId))
			{
				if (tProgress.nCounter < 0xFFFF)
				{
					++tProgress.nCounter;
				}

				if (tProgress.nCounter >= pRecord->nGoalCount)
				{
					SUBQUEST_SetGoalReached(pPlayer, pRecord, tProgress);
				}
				else
				{
					SUBQUEST_SendStatusMessage(pPlayer, pRecord, "SubQuestUpdate", "Subquest", tProgress.nCounter, pRecord->nGoalCount);
				}
			}
			else if (pRecord->nGoalType == SUBQUESTGOAL_BOSS && nSuperUnique >= 0 && pRecord->nGoalSuperUnique == nSuperUnique)
			{
				SUBQUEST_SetGoalReached(pPlayer, pRecord, tProgress);
			}
		});
	}
}

//----------------------------------------------------------------------------------------------------------------------
// Detours
//----------------------------------------------------------------------------------------------------------------------

void __fastcall MODPATCH_ParseKill(D2GameStrc* pGame, D2UnitStrc* pDefender, D2UnitStrc* pAttacker)
{
	((ParseKillFn)gpfnOriginalParseKill)(pGame, pDefender, pAttacker);

	if (!pGame || !pDefender || pDefender->dwUnitType != UNIT_MONSTER || !pAttacker || !SUBQUEST_GetCount())
	{
		return;
	}

	// A kill by a player's hireling, summon or minion counts for the player.
	D2UnitStrc* pKiller = pAttacker;
	if (pKiller->dwUnitType != UNIT_PLAYER)
	{
		pKiller = SUBQUEST_Original<GetOwnerFn>(SUBQUEST_ADDR_GETOWNER)(pGame, pAttacker);
	}

	if (!pKiller || pKiller->dwUnitType != UNIT_PLAYER)
	{
		return;
	}

	std::lock_guard<std::recursive_mutex> lock(sgSubQuestMutex);
	SUBQUEST_OnMonsterKilled(pGame, pKiller, pDefender);
}

void __fastcall MODPATCH_ChangeLevel(D2GameStrc* pGame, int32_t nOldLevelId, int32_t nTargetLevelId, D2UnitStrc* pUnit)
{
	((ChangeLevelFn)gpfnOriginalChangeLevel)(pGame, nOldLevelId, nTargetLevelId, pUnit);

	if (!pGame || !pUnit || pUnit->dwUnitType != UNIT_PLAYER || !SUBQUEST_GetCount())
	{
		return;
	}

	// The game also reports a town portal before the player has moved; act once the player is in the level.
	D2ActiveRoomStrc* pRoom = UNITS_GetRoom(pUnit);
	if (!pRoom || DUNGEON_GetLevelIdFromRoom(pRoom) != nTargetLevelId)
	{
		return;
	}

	std::lock_guard<std::recursive_mutex> lock(sgSubQuestMutex);
	SUBQUEST_ForEachActive(pGame, pUnit, [&](const D2SubQuestTxt* pRecord, D2SubQuestProgress& tProgress)
	{
		if (SUBQUEST_StateOf(tProgress) != SUBQUESTSTATE_ACTIVE || pRecord->nGoalLevel != nTargetLevelId)
		{
			return;
		}

		if (pRecord->nGoalType == SUBQUESTGOAL_LEVEL)
		{
			SUBQUEST_SetGoalReached(pUnit, pRecord, tProgress);
		}
		else if (pRecord->nGoalType == SUBQUESTGOAL_BOSS)
		{
			// The game spawns a superunique without Stacks once per game, so entering again does not spawn another.
			D2CoordStrc tCoords = {};
			UNITS_GetCoords(pUnit, &tCoords);
			SUBQUEST_Original<SpawnSuperUniqueFn>(SUBQUEST_ADDR_SPAWNSUPERUNIQUE)(pGame, pRoom, tCoords.nX, tCoords.nY, pRecord->nGoalSuperUnique);
		}
	});
}

void __fastcall MODPATCH_ItemPickedUp(D2GameStrc* pGame, D2UnitStrc* pPlayer, D2UnitStrc* pItem)
{
	((ItemPickedUpFn)gpfnOriginalItemPickedUp)(pGame, pPlayer, pItem);

	if (!pGame || !pPlayer || pPlayer->dwUnitType != UNIT_PLAYER || !pItem || !SUBQUEST_GetCount())
	{
		return;
	}

	const uint32_t dwCode = ITEMS_GetBaseCode(pItem);

	std::lock_guard<std::recursive_mutex> lock(sgSubQuestMutex);
	SUBQUEST_ForEachActive(pGame, pPlayer, [&](const D2SubQuestTxt* pRecord, D2SubQuestProgress& tProgress)
	{
		if (pRecord->nGoalType != SUBQUESTGOAL_ITEM || pRecord->dwGoalItemCode != dwCode || SUBQUEST_StateOf(tProgress) != SUBQUESTSTATE_ACTIVE)
		{
			return;
		}

		const int32_t nCount = SUBQUEST_CountItems(pPlayer, dwCode);
		if (nCount >= pRecord->nGoalCount)
		{
			SUBQUEST_SetGoalReached(pPlayer, pRecord, tProgress);
		}
		else
		{
			SUBQUEST_SendStatusMessage(pPlayer, pRecord, "SubQuestUpdate", "Subquest", nCount, pRecord->nGoalCount);
		}
	});
}

void __fastcall MODPATCH_NPCActivate(D2ClientStrc* pClient, D2UnitStrc* pPlayer, D2UnitStrc* pTarget, D2TextHeaderStrc* pTextControl)
{
	((NPCActivateFn)gpfnOriginalNPCActivate)(pClient, pPlayer, pTarget, pTextControl);

	if (!pClient || !pClient->pGame || !pPlayer || !pTarget || pTarget->dwUnitType != UNIT_MONSTER || !SUBQUEST_GetCount())
	{
		return;
	}

	D2GameStrc* pGame = pClient->pGame;

	std::lock_guard<std::recursive_mutex> lock(sgSubQuestMutex);

	SUBQUEST_ForEachActive(pGame, pPlayer, [&](const D2SubQuestTxt* pRecord, D2SubQuestProgress& tProgress)
	{
		if (pRecord->nGoalType == SUBQUESTGOAL_TALK && SUBQUEST_StateOf(tProgress) == SUBQUESTSTATE_ACTIVE && pRecord->nGoalMonster == (int32_t)pTarget->dwClassId)
		{
			SUBQUEST_SetGoalReached(pPlayer, pRecord, tProgress);
		}
	});

	SUBQUEST_TalkToGiver(pGame, pPlayer, pTarget, pTextControl);
}

// An object goal: the player operated an object of that class (in that level).
int32_t __fastcall MODPATCH_OperateHandler(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nObjectType, int32_t nObjectGUID, int32_t* pResult)
{
	// The object is looked up before the original runs: operating some objects removes them.
	D2UnitStrc* pObject = pGame ? SUBQUEST_Original<GetServerUnitFn>(SUBQUEST_ADDR_GETSERVERUNIT)(pGame, nObjectType, nObjectGUID) : nullptr;
	const int32_t nObjectClassId = pObject ? (int32_t)pObject->dwClassId : -1;
	const int32_t nObjectLevelId = SUBQUEST_GetUnitLevelId(pObject);

	const int32_t nOperated = ((OperateHandlerFn)gpfnOriginalOperateHandler)(pGame, pPlayer, nObjectType, nObjectGUID, pResult);

	if (!nOperated || nObjectClassId < 0 || !pPlayer || pPlayer->dwUnitType != UNIT_PLAYER || !SUBQUEST_GetCount())
	{
		return nOperated;
	}

	std::lock_guard<std::recursive_mutex> lock(sgSubQuestMutex);
	SUBQUEST_ForEachActive(pGame, pPlayer, [&](const D2SubQuestTxt* pRecord, D2SubQuestProgress& tProgress)
	{
		if (pRecord->nGoalType == SUBQUESTGOAL_OBJECT && SUBQUEST_StateOf(tProgress) == SUBQUESTSTATE_ACTIVE && pRecord->nGoalObject == nObjectClassId
			&& (pRecord->nGoalLevel <= 0 || pRecord->nGoalLevel == nObjectLevelId))
		{
			SUBQUEST_SetGoalReached(pPlayer, pRecord, tProgress);
		}
	});

	return nOperated;
}

// The player's subquests under way in this difficulty, one chat line each.
static void SUBQUEST_SendList(D2GameStrc* pGame, D2UnitStrc* pPlayer)
{
	char szLine[256];
	SUBQUEST_GetKeyedText(szLine, sizeof(szLine), "SubQuestList", "Subquests under way:");
	SUBQUEST_SendMessage(pPlayer, szLine);

	bool bAny = false;
	SUBQUEST_ForEachActive(pGame, pPlayer, [&](const D2SubQuestTxt* pRecord, D2SubQuestProgress& tProgress)
	{
		bAny = true;

		char szName[128];
		char szState[128];
		SUBQUEST_GetName(szName, sizeof(szName), pRecord);

		if (SUBQUEST_StateOf(tProgress) == SUBQUESTSTATE_READY && pRecord->nGoalType != SUBQUESTGOAL_ITEM)
		{
			SUBQUEST_GetKeyedText(szState, sizeof(szState), "SubQuestListReady", "return to the quest giver");
			snprintf(szLine, sizeof(szLine), "  %s: %s", szName, szState);
		}
		else if (pRecord->nGoalType == SUBQUESTGOAL_KILL)
		{
			snprintf(szLine, sizeof(szLine), "  %s: %d/%d", szName, (int32_t)tProgress.nCounter, pRecord->nGoalCount);
		}
		else if (pRecord->nGoalType == SUBQUESTGOAL_ITEM)
		{
			snprintf(szLine, sizeof(szLine), "  %s: %d/%d", szName, std::min(SUBQUEST_CountItems(pPlayer, pRecord->dwGoalItemCode), pRecord->nGoalCount), pRecord->nGoalCount);
		}
		else
		{
			snprintf(szLine, sizeof(szLine), "  %s", szName);
		}
		SUBQUEST_SendMessage(pPlayer, szLine);
	});

	if (!bAny)
	{
		SUBQUEST_GetKeyedText(szLine, sizeof(szLine), "SubQuestListNone", "  none");
		SUBQUEST_SendMessage(pPlayer, szLine);
	}
}

// The chat line ".subquests" (or ".sq") lists the player's subquests instead of being said. Slash commands would not
// do: the client hands those to Battle.net and never sends them.
int32_t __fastcall MODPATCH_HandleChatMessage(D2GameStrc* pGame, D2UnitStrc* pUnit, void* pPacket, int32_t nSize)
{
	if (pGame && pUnit && pUnit->dwUnitType == UNIT_PLAYER && pPacket && nSize > (int32_t)offsetof(D2GSPacketClt15, szMessage) && SUBQUEST_GetCount())
	{
		const D2GSPacketClt15* pChat = (const D2GSPacketClt15*)pPacket;

		char szMessage[32] = {};
		const int32_t nAvailable = std::min<int32_t>(nSize - (int32_t)offsetof(D2GSPacketClt15, szMessage), (int32_t)sizeof(szMessage) - 1);
		memcpy(szMessage, pChat->szMessage, nAvailable);
		szMessage[nAvailable] = 0;
		for (int32_t i = (int32_t)strlen(szMessage) - 1; i >= 0 && (szMessage[i] == ' ' || szMessage[i] == '\t'); --i)
		{
			szMessage[i] = 0;
		}

		if (pChat->nMessageType == 1 && (!_stricmp(szMessage, ".subquests") || !_stricmp(szMessage, ".sq")))
		{
			std::lock_guard<std::recursive_mutex> lock(sgSubQuestMutex);
			SUBQUEST_SendList(pGame, pUnit);
			return 0;
		}
	}

	return ((ChatMessageFn)gpfnOriginalHandleChatMessage)(pGame, pUnit, pPacket, nSize);
}

//----------------------------------------------------------------------------------------------------------------------
// Saving
//----------------------------------------------------------------------------------------------------------------------
//
// An extra block at the very end of the .d2s, after the sections the game writes (the game's reader stops after its
// own last section). Found from the end of the file, so the game's sections never need to be parsed:
//
//   uint8_t  version (1)
//   3 times (Normal, Nightmare, Hell):
//     uint16_t count
//     count times: uint16_t id, uint8_t state, uint16_t counter
//   uint16_t size of the above
//   char[4]  'S','Q','0','1'
//
// The header's file size and checksum are updated to cover it. A save without the block has no subquest progress.

static constexpr char SUBQUEST_SAVE_MAGIC[4] = { 'S', 'Q', '0', '1' };
static constexpr uint8_t SUBQUEST_SAVE_VERSION = 1;
static constexpr size_t SUBQUEST_SAVE_FOOTER_SIZE = sizeof(uint16_t) + sizeof(SUBQUEST_SAVE_MAGIC);

static void SUBQUEST_Write(std::vector<uint8_t>& tData, const void* pData, size_t nSize)
{
	tData.insert(tData.end(), (const uint8_t*)pData, (const uint8_t*)pData + nSize);
}

int32_t __fastcall MODPATCH_CreateSaveFile(D2GameStrc* pGame, D2UnitStrc* pPlayer, uint8_t* pData, uint32_t* pSize, uint32_t nMaxSize, int32_t bUseTradeInventory, int32_t nUnused)
{
	const int32_t nResult = ((CreateSaveFileFn)gpfnOriginalCreateSaveFile)(pGame, pPlayer, pData, pSize, nMaxSize, bUseTradeInventory, nUnused);
	if (nResult || !pPlayer || !pData || !pSize || *pSize < 16)
	{
		return nResult;
	}

	std::vector<uint8_t> tBlock;
	{
		std::lock_guard<std::recursive_mutex> lock(sgSubQuestMutex);
		auto itPlayer = sgPlayerSubQuests.find(pPlayer);
		if (itPlayer == sgPlayerSubQuests.end())
		{
			return nResult;
		}

		bool bAny = false;
		SUBQUEST_Write(tBlock, &SUBQUEST_SAVE_VERSION, 1);
		for (const auto& tProgress : itPlayer->second.tProgress)
		{
			uint16_t nCount = 0;
			for (const auto& [nId, tEntry] : tProgress)
			{
				if (tEntry.nState != SUBQUESTSTATE_NONE)
				{
					++nCount;
				}
			}
			SUBQUEST_Write(tBlock, &nCount, sizeof(nCount));

			for (const auto& [nId, tEntry] : tProgress)
			{
				if (tEntry.nState != SUBQUESTSTATE_NONE)
				{
					SUBQUEST_Write(tBlock, &nId, sizeof(nId));
					SUBQUEST_Write(tBlock, &tEntry.nState, sizeof(tEntry.nState));
					SUBQUEST_Write(tBlock, &tEntry.nCounter, sizeof(tEntry.nCounter));
					bAny = true;
				}
			}
		}

		if (!bAny || tBlock.size() > 0xFFFF)
		{
			return nResult;
		}
	}

	const uint16_t nBlockSize = (uint16_t)tBlock.size();
	SUBQUEST_Write(tBlock, &nBlockSize, sizeof(nBlockSize));
	SUBQUEST_Write(tBlock, SUBQUEST_SAVE_MAGIC, sizeof(SUBQUEST_SAVE_MAGIC));

	// A margin: the realm writer hands the original a buffer 2 bytes shorter than nMaxSize says (&pSaveData[2] of 8192).
	if (*pSize + tBlock.size() + 16 > nMaxSize)
	{
		FOG_Trace("Subquests: no room left in the save of %s, progress not saved", pPlayer->pPlayerData ? pPlayer->pPlayerData->szName : "?");
		return nResult;
	}

	memcpy(&pData[*pSize], tBlock.data(), tBlock.size());
	*pSize += (uint32_t)tBlock.size();

	// The header's size (+8) and checksum (+12, computed with the field at 0), as the game writes them.
	uint32_t* pHeader = (uint32_t*)pData;
	pHeader[2] = *pSize;
	pHeader[3] = 0;
	pHeader[3] = FOG_ComputeChecksum(pData, *pSize);
	return nResult;
}

// Reads the block at the end of a save into tOut. False when the save has none (or a damaged one).
static bool SUBQUEST_ReadSaveBlock(const uint8_t* pSaveFile, uint32_t nSize, D2PlayerSubQuests& tOut)
{
	if (!pSaveFile || nSize < SUBQUEST_SAVE_FOOTER_SIZE + 1 || memcmp(&pSaveFile[nSize - sizeof(SUBQUEST_SAVE_MAGIC)], SUBQUEST_SAVE_MAGIC, sizeof(SUBQUEST_SAVE_MAGIC)))
	{
		return false;
	}

	uint16_t nBlockSize = 0;
	memcpy(&nBlockSize, &pSaveFile[nSize - SUBQUEST_SAVE_FOOTER_SIZE], sizeof(nBlockSize));
	if (nBlockSize < 1 || nBlockSize > nSize - SUBQUEST_SAVE_FOOTER_SIZE)
	{
		return false;
	}

	const uint8_t* pRead = &pSaveFile[nSize - SUBQUEST_SAVE_FOOTER_SIZE - nBlockSize];
	const uint8_t* pEnd = pRead + nBlockSize;
	if (*pRead++ != SUBQUEST_SAVE_VERSION)
	{
		return false;
	}

	for (auto& tProgress : tOut.tProgress)
	{
		uint16_t nCount = 0;
		if (pRead + sizeof(nCount) > pEnd)
		{
			return false;
		}
		memcpy(&nCount, pRead, sizeof(nCount));
		pRead += sizeof(nCount);

		for (uint16_t i = 0; i < nCount; ++i)
		{
			uint16_t nId = 0;
			D2SubQuestProgress tEntry;
			if (pRead + sizeof(nId) + sizeof(tEntry.nState) + sizeof(tEntry.nCounter) > pEnd)
			{
				return false;
			}
			memcpy(&nId, pRead, sizeof(nId));
			pRead += sizeof(nId);
			tEntry.nState = *pRead++;
			memcpy(&tEntry.nCounter, pRead, sizeof(tEntry.nCounter));
			pRead += sizeof(tEntry.nCounter);

			if ((tEntry.nState & SUBQUESTSTATE_MASK) <= SUBQUESTSTATE_DONE)
			{
				tProgress[nId] = tEntry;
			}
		}
	}

	return true;
}

int32_t __fastcall MODPATCH_ProcessSaveFile(D2GameStrc* pGame, D2ClientStrc* pClient, uint8_t* pSaveFile, uint32_t nSize, D2UnitStrc** ppPlayer, D2ActiveRoomStrc* pRoomArg, int32_t nXArg, int32_t nYArg)
{
	// Read before the game does: its header check works on the buffer.
	D2PlayerSubQuests tLoaded;
	SUBQUEST_ReadSaveBlock(pSaveFile, nSize, tLoaded);

	const int32_t nResult = ((ProcessSaveFileFn)gpfnOriginalProcessSaveFile)(pGame, pClient, pSaveFile, nSize, ppPlayer, pRoomArg, nXArg, nYArg);
	if (!nResult && ppPlayer && *ppPlayer)
	{
		// Every player unit is made here, a new character included, so this also clears what a freed unit at the same
		// address had.
		std::lock_guard<std::recursive_mutex> lock(sgSubQuestMutex);
		sgPlayerSubQuests[*ppPlayer] = std::move(tLoaded);
	}

	return nResult;
}
