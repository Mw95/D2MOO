#include "DataTbls/SubQuestTbls.h"

#include "DataTbls/ExtraTxtColumns.h"
#include <D2Lang.h>
#include <Fog.h>

#include <cctype>
#include <cstring>
#include <mutex>

// Mod: subquests, see SubQuestTbls.h. Not part of the original game.

static D2SubQuestTxt* sgpSubQuests = nullptr;
static int sgnSubQuests = 0;
static bool sgbSubQuestsLoaded = false;
static std::mutex sgSubQuestsMutex;

// An item code as ITEMS_GetBaseCode answers it: the four characters, little endian, padded with spaces. 0 when empty.
static uint32_t DATATBLS_PackItemCode(const char* szCode)
{
	if (!szCode[0])
	{
		return 0;
	}

	uint32_t dwCode = 0;
	for (int i = 0; i < 4; ++i)
	{
		const char c = szCode[i] ? szCode[i] : ' ';
		dwCode |= (uint32_t)(uint8_t)c << (8 * i);
		if (!szCode[i])
		{
			for (int j = i + 1; j < 4; ++j)
			{
				dwCode |= (uint32_t)(uint8_t)' ' << (8 * j);
			}
			break;
		}
	}

	return dwCode;
}

static int16_t DATATBLS_GetTblIndexOrNone(char* szKey)
{
	if (!szKey[0])
	{
		return -1;
	}

	const Unicode* pUnused = nullptr;
	const int16_t nIndex = D2LANG_GetTblIndex(szKey, &pUnused);
	return nIndex > 0 ? nIndex : -1;
}

static uint8_t DATATBLS_ParseSubQuestGoal(const char* szGoal)
{
	static const struct { const char* szName; uint8_t nType; } tGoals[] =
	{
		{ "kill", SUBQUESTGOAL_KILL },
		{ "boss", SUBQUESTGOAL_BOSS },
		{ "item", SUBQUESTGOAL_ITEM },
		{ "level", SUBQUESTGOAL_LEVEL },
		{ "talk", SUBQUESTGOAL_TALK },
		{ "object", SUBQUESTGOAL_OBJECT },
	};

	for (const auto& tGoal : tGoals)
	{
		if (!_stricmp(szGoal, tGoal.szName))
		{
			return tGoal.nType;
		}
	}

	return SUBQUESTGOAL_NONE;
}

static void DATATBLS_EnsureSubQuestsLoaded()
{
	if (sgbSubQuestsLoaded)
	{
		return;
	}

	std::lock_guard<std::mutex> lock(sgSubQuestsMutex);
	if (sgbSubQuestsLoaded)
	{
		return;
	}

	D2BinFieldStrc pTbl[] =
	{
		{ "Id", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, dwId), NULL },
		{ "Giver", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGiver), NULL },
		{ "ReqQuest", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nReqQuest), NULL },
		{ "ReqSubQuest", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, dwReqSubQuest), NULL },
		{ "ReqLevel", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nReqLevel), NULL },
		{ "Goal", TXTFIELD_ASCII, 7, offsetof(D2SubQuestTxt, szGoal), NULL },
		{ "GoalMonster", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGoalMonster), NULL },
		{ "GoalSuperUnique", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGoalSuperUnique), NULL },
		{ "GoalLevel", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGoalLevel), NULL },
		{ "GoalItem", TXTFIELD_ASCII, 4, offsetof(D2SubQuestTxt, szGoalItem), NULL },
		{ "GoalCount", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGoalCount), NULL },
		{ "TakeItems", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, dwTakeItems), NULL },
		{ "Name", TXTFIELD_ASCII, 31, offsetof(D2SubQuestTxt, szName), NULL },
		{ "TextOffer", TXTFIELD_ASCII, 31, offsetof(D2SubQuestTxt, szTextOffer), NULL },
		{ "TextProgress", TXTFIELD_ASCII, 31, offsetof(D2SubQuestTxt, szTextProgress), NULL },
		{ "TextDone", TXTFIELD_ASCII, 31, offsetof(D2SubQuestTxt, szTextDone), NULL },
		{ "ExpNormal", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nExp[0]), NULL },
		{ "ExpNightmare", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nExp[1]), NULL },
		{ "ExpHell", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nExp[2]), NULL },
		{ "GoldNormal", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGold[0]), NULL },
		{ "GoldNightmare", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGold[1]), NULL },
		{ "GoldHell", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGold[2]), NULL },
		{ "RewardItem", TXTFIELD_ASCII, 4, offsetof(D2SubQuestTxt, szRewardItem), NULL },
		{ "RewardItemQuality", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nRewardItemQuality), NULL },
		{ "RewardItemLevel", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nRewardItemLevel), NULL },
		{ "StatPoints", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nStatPoints), NULL },
		{ "SkillPoints", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nSkillPoints), NULL },
		{ "Repeatable", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, dwRepeatable), NULL },
		{ "RewardTC", TXTFIELD_ASCII, 31, offsetof(D2SubQuestTxt, szRewardTC), NULL },
		{ "GoalObject", TXTFIELD_DWORD, 0, offsetof(D2SubQuestTxt, nGoalObject), NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL },
	};

	sgpSubQuests = (D2SubQuestTxt*)DATATBLS_LoadExtraTxtColumns("subquests", pTbl, "Id", sizeof(D2SubQuestTxt), &sgnSubQuests);

	for (int i = 0; i < sgnSubQuests; ++i)
	{
		D2SubQuestTxt* pRecord = &sgpSubQuests[i];
		if (pRecord->dwId > 0xFFFF)
		{
			FOG_Trace("SubQuests.txt row %d: Id %u is above 65535, row ignored", i, pRecord->dwId);
			pRecord->dwId = 0;
		}

		pRecord->nGoalType = DATATBLS_ParseSubQuestGoal(pRecord->szGoal);
		if (pRecord->dwId && pRecord->nGoalType == SUBQUESTGOAL_NONE)
		{
			FOG_Trace("SubQuests.txt Id %u: unknown Goal '%s', row ignored", pRecord->dwId, pRecord->szGoal);
			pRecord->dwId = 0;
		}

		if (pRecord->nGoalCount <= 0)
		{
			pRecord->nGoalCount = 1;
		}

		pRecord->dwGoalItemCode = DATATBLS_PackItemCode(pRecord->szGoalItem);
		pRecord->dwRewardItemCode = DATATBLS_PackItemCode(pRecord->szRewardItem);
		pRecord->nNameTbl = DATATBLS_GetTblIndexOrNone(pRecord->szName);
		pRecord->nTextOfferTbl = DATATBLS_GetTblIndexOrNone(pRecord->szTextOffer);
		pRecord->nTextProgressTbl = DATATBLS_GetTblIndexOrNone(pRecord->szTextProgress);
		pRecord->nTextDoneTbl = DATATBLS_GetTblIndexOrNone(pRecord->szTextDone);

		for (int j = 0; j < i; ++j)
		{
			if (pRecord->dwId && sgpSubQuests[j].dwId == pRecord->dwId)
			{
				FOG_Trace("SubQuests.txt: Id %u is used twice, the second row is ignored", pRecord->dwId);
				pRecord->dwId = 0;
				break;
			}
		}
	}

	sgbSubQuestsLoaded = true;
}

int __fastcall DATATBLS_GetSubQuestTxtCount()
{
	DATATBLS_EnsureSubQuestsLoaded();
	return sgnSubQuests;
}

const D2SubQuestTxt* __fastcall DATATBLS_GetSubQuestTxtRecord(int nIndex)
{
	DATATBLS_EnsureSubQuestsLoaded();

	if (nIndex < 0 || nIndex >= sgnSubQuests || !sgpSubQuests[nIndex].dwId)
	{
		return nullptr;
	}

	return &sgpSubQuests[nIndex];
}

const D2SubQuestTxt* __fastcall DATATBLS_GetSubQuestTxtRecordById(uint32_t dwId)
{
	DATATBLS_EnsureSubQuestsLoaded();

	for (int i = 0; dwId && i < sgnSubQuests; ++i)
	{
		if (sgpSubQuests[i].dwId == dwId)
		{
			return &sgpSubQuests[i];
		}
	}

	return nullptr;
}

//D2Common.#11315
int __stdcall DATATBLS_GetSubQuestCount()
{
	return DATATBLS_GetSubQuestTxtCount();
}

//D2Common.#11316
const D2SubQuestTxt* __stdcall DATATBLS_GetSubQuestRecord(int nIndex)
{
	return DATATBLS_GetSubQuestTxtRecord(nIndex);
}

//D2Common.#11317
const D2SubQuestTxt* __stdcall DATATBLS_GetSubQuestRecordById(uint32_t dwId)
{
	return DATATBLS_GetSubQuestTxtRecordById(dwId);
}
