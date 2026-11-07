#pragma once

#include "D2CommonDefinitions.h"

// Mod: subquests given by NPCs (not part of the original game). See doc/SubQuests.md.
//
// DATA\GLOBAL\EXCEL\SubQuests.txt, one row per subquest, read from the .txt on first use (see DataTbls/ExtraTxtColumns.h).
// The game logic is in D2Game (source/D2Game/src/MOD/SubQuests.cpp); D2Common only holds the table.

enum D2SubQuestGoalType : uint8_t
{
	SUBQUESTGOAL_NONE = 0,
	SUBQUESTGOAL_KILL = 1,		// "kill":  kill GoalCount monsters of MonStats row GoalMonster, in GoalLevel when set
	SUBQUESTGOAL_BOSS = 2,		// "boss":  kill SuperUniques.txt row GoalSuperUnique, spawned when the player enters GoalLevel
	SUBQUESTGOAL_ITEM = 3,		// "item":  bring GoalCount items of code GoalItem to the giver (taken away with TakeItems=1)
	SUBQUESTGOAL_LEVEL = 4,		// "level": enter GoalLevel
	SUBQUESTGOAL_TALK = 5,		// "talk":  talk to the NPC of MonStats row GoalMonster
	SUBQUESTGOAL_OBJECT = 6,	// "object": operate an object of Objects.txt row GoalObject, in GoalLevel when set
};

#pragma pack(1)

struct D2SubQuestTxt
{
	// Columns
	uint32_t dwId;							// Id: 1-65535, unique and never reused (it is what saves store)
	int32_t nGiver;							// Giver: MonStats row (hcIdx) of the NPC that gives and takes the subquest
	int32_t nReqQuest;						// ReqQuest: vanilla quest (D2Quests id) that must be completed first, 0 for none
	uint32_t dwReqSubQuest;					// ReqSubQuest: Id of a subquest that must be completed first, 0 for none
	int32_t nReqLevel;						// ReqLevel: minimum character level
	char szGoal[8];							// Goal: kill, boss, item, level, talk or object
	int32_t nGoalMonster;					// GoalMonster
	int32_t nGoalSuperUnique;				// GoalSuperUnique
	int32_t nGoalLevel;						// GoalLevel
	char szGoalItem[8];						// GoalItem: item code
	int32_t nGoalCount;						// GoalCount: 0 is read as 1
	uint32_t dwTakeItems;					// TakeItems
	char szName[32];						// Name: .tbl key of the subquest's name (messages)
	char szTextOffer[32];					// TextOffer: .tbl key the giver says when the subquest is given
	char szTextProgress[32];				// TextProgress: .tbl key the giver says while it is under way
	char szTextDone[32];					// TextDone: .tbl key the giver says when it is turned in
	int32_t nExp[3];						// ExpNormal, ExpNightmare, ExpHell
	int32_t nGold[3];						// GoldNormal, GoldNightmare, GoldHell
	char szRewardItem[8];					// RewardItem: item code, empty for none
	int32_t nRewardItemQuality;				// RewardItemQuality: D2C_ItemQualities (2 normal ... 7 unique), 0 is read as normal
	int32_t nRewardItemLevel;				// RewardItemLevel: 0 for the character's level
	int32_t nStatPoints;					// StatPoints
	int32_t nSkillPoints;					// SkillPoints
	uint32_t dwRepeatable;					// Repeatable: 1 lets the giver offer it again once turned in
	char szRewardTC[32];					// RewardTC: TreasureClassEx.txt row dropped at the giver's feet, empty for none
	int32_t nGoalObject;					// GoalObject: Objects.txt row (object goal)

	// Resolved after loading
	uint8_t nGoalType;						// D2SubQuestGoalType
	uint8_t pad[3];
	uint32_t dwGoalItemCode;				// GoalItem as ITEMS_GetBaseCode answers it
	uint32_t dwRewardItemCode;				// RewardItem as ITEMS_GetBaseCode answers it, 0 for none
	int16_t nNameTbl;						// the .tbl indices of the texts, -1 when not found
	int16_t nTextOfferTbl;
	int16_t nTextProgressTbl;
	int16_t nTextDoneTbl;
};

#pragma pack()

// Number of rows of SubQuests.txt (0 without the file). Loads it on first use. Thread safe.
int __fastcall DATATBLS_GetSubQuestTxtCount();
// The row, nullptr when out of range.
const D2SubQuestTxt* __fastcall DATATBLS_GetSubQuestTxtRecord(int nIndex);
// The row with that Id, nullptr when there is none.
const D2SubQuestTxt* __fastcall DATATBLS_GetSubQuestTxtRecordById(uint32_t dwId);

// Exports (D2MOO D2Common.dll only, look them up by name).
//D2Common.#11315
D2COMMON_DLL_DECL int __stdcall DATATBLS_GetSubQuestCount();
//D2Common.#11316
D2COMMON_DLL_DECL const D2SubQuestTxt* __stdcall DATATBLS_GetSubQuestRecord(int nIndex);
//D2Common.#11317
D2COMMON_DLL_DECL const D2SubQuestTxt* __stdcall DATATBLS_GetSubQuestRecordById(uint32_t dwId);
