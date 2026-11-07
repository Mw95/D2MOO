#include "Drlg/D2DrlgSafeZone.h"

#include "D2DataTbls.h"
#include "DataTbls/ExtraTxtColumns.h"
#include "D2Seed.h"
#include "Drlg/D2DrlgDrlgRoom.h"
#include "Drlg/D2DrlgMaze.h"
#include "Drlg/D2DrlgOutdoors.h"
#include "Drlg/D2DrlgPreset.h"
#include <Archive.h>
#include <D2Lang.h>
#include <DataTbls/LevelsIds.h>
#include <Fog.h>

#include <mutex>

// Town-like safe zones, see D2DrlgSafeZone.h. Not part of the original game.

static D2SafeZonePresetTxt* sgpSafeZonePresets = nullptr;
static int sgnSafeZonePresets = 0;
static D2SafeZoneLevelTxt* sgpSafeZoneLevels = nullptr;
static int sgnSafeZoneLevels = 0;
static bool sgbSafeZonesLoaded = false;
static std::mutex sgSafeZoneMutex;

static void DRLGSAFEZONE_Load()
{
	D2BinFieldStrc pLvlPrestTbl[] =
	{
		{ "SafeZone", TXTFIELD_DWORD, 0, offsetof(D2SafeZonePresetTxt, dwSafeZone), NULL },
		{ "EntryName", TXTFIELD_ASCII, 39, offsetof(D2SafeZonePresetTxt, szEntryName), NULL },
		{ "EntryFile", TXTFIELD_ASCII, 39, offsetof(D2SafeZonePresetTxt, szEntryFile), NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL },
	};

	sgpSafeZonePresets = (D2SafeZonePresetTxt*)DATATBLS_LoadExtraTxtColumns("lvlprest", pLvlPrestTbl, "SafeZone", sizeof(D2SafeZonePresetTxt), &sgnSafeZonePresets);

	for (int i = 0; i < sgnSafeZonePresets; ++i)
	{
		D2SafeZonePresetTxt* pRecord = &sgpSafeZonePresets[i];
		memset(pRecord->wszEntryName, 0x00, sizeof(pRecord->wszEntryName));

		if (pRecord->dwSafeZone && pRecord->szEntryName[0])
		{
			if (const Unicode* pName = D2LANG_GetStringByReferenceString(pRecord->szEntryName))
			{
				Unicode::strncpy(pRecord->wszEntryName, pName, ARRAY_SIZE(pRecord->wszEntryName));
			}
			pRecord->wszEntryName[ARRAY_SIZE(pRecord->wszEntryName) - 1] = 0;
		}

		for (char* pChar = pRecord->szEntryFile; *pChar; ++pChar)
		{
			if (*pChar == '/')
			{
				*pChar = '\\';
			}
		}
	}

	D2BinFieldStrc pLevelsTbl[] =
	{
		{ "SafeZoneChance", TXTFIELD_DWORD, 0, offsetof(D2SafeZoneLevelTxt, dwChance), NULL },
		{ "SafeZonePreset", TXTFIELD_DWORD, 0, offsetof(D2SafeZoneLevelTxt, nPreset), NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL },
	};

	sgpSafeZoneLevels = (D2SafeZoneLevelTxt*)DATATBLS_LoadExtraTxtColumns("levels", pLevelsTbl, "SafeZoneChance", sizeof(D2SafeZoneLevelTxt), &sgnSafeZoneLevels);

	if (sgnSafeZonePresets || sgnSafeZoneLevels)
	{
		FOG_Trace("Safe zones: %d LvlPrest rows, %d Levels rows", sgnSafeZonePresets, sgnSafeZoneLevels);
	}
}

void __fastcall DRLGSAFEZONE_EnsureLoaded()
{
	if (sgbSafeZonesLoaded)
	{
		return;
	}

	std::lock_guard<std::mutex> lock(sgSafeZoneMutex);
	if (!sgbSafeZonesLoaded)
	{
		DRLGSAFEZONE_Load();
		sgbSafeZonesLoaded = true;
	}
}

void __fastcall DRLGSAFEZONE_Unload()
{
	std::lock_guard<std::mutex> lock(sgSafeZoneMutex);

	if (sgpSafeZonePresets)
	{
		D2_FREE_POOL(nullptr, sgpSafeZonePresets);
		sgpSafeZonePresets = nullptr;
	}
	sgnSafeZonePresets = 0;

	if (sgpSafeZoneLevels)
	{
		D2_FREE_POOL(nullptr, sgpSafeZoneLevels);
		sgpSafeZoneLevels = nullptr;
	}
	sgnSafeZoneLevels = 0;

	sgbSafeZonesLoaded = false;
}

const D2SafeZonePresetTxt* __fastcall DRLGSAFEZONE_GetPresetRecord(int nLvlPrestId)
{
	DRLGSAFEZONE_EnsureLoaded();

	if (nLvlPrestId > LVLPREST_NONE && nLvlPrestId < sgnSafeZonePresets)
	{
		return &sgpSafeZonePresets[nLvlPrestId];
	}

	return nullptr;
}

const D2SafeZoneLevelTxt* __fastcall DRLGSAFEZONE_GetLevelRecord(int nLevelId)
{
	DRLGSAFEZONE_EnsureLoaded();

	if (nLevelId > 0 && nLevelId < sgnSafeZoneLevels)
	{
		return &sgpSafeZoneLevels[nLevelId];
	}

	return nullptr;
}

BOOL __fastcall DRLGSAFEZONE_IsSafeZonePreset(int nLvlPrestId)
{
	const D2SafeZonePresetTxt* pRecord = DRLGSAFEZONE_GetPresetRecord(nLvlPrestId);
	return pRecord && pRecord->dwSafeZone;
}

int __fastcall DRLGSAFEZONE_GetSafeZonePresetId(D2DrlgRoomStrc* pDrlgRoom)
{
	if (!pDrlgRoom || pDrlgRoom->nType != DRLGTYPE_PRESET || !pDrlgRoom->pMaze)
	{
		return -1;
	}

	const int nLvlPrestId = pDrlgRoom->pMaze->nLevelPrest;
	return DRLGSAFEZONE_IsSafeZonePreset(nLvlPrestId) ? nLvlPrestId : -1;
}

BOOL __fastcall DRLGSAFEZONE_IsDrlgRoomSafeZone(D2DrlgRoomStrc* pDrlgRoom)
{
	return DRLGSAFEZONE_GetSafeZonePresetId(pDrlgRoom) != -1;
}

static thread_local int sgnTownOverrideDepth = 0;

void __fastcall DRLGSAFEZONE_PushTownOverride()
{
	++sgnTownOverrideDepth;
}

void __fastcall DRLGSAFEZONE_PopTownOverride()
{
	if (sgnTownOverrideDepth > 0)
	{
		--sgnTownOverrideDepth;
	}
}

BOOL __fastcall DRLGSAFEZONE_IsTownOverrideActive()
{
	return sgnTownOverrideDepth > 0;
}

// Answers the preset to place in pLevel, or LVLPREST_NONE. Rolls the level's seed only when the level has a
// safe zone configured, so levels without one are generated exactly as in the original game.
static int DRLGSAFEZONE_RollPreset(D2DrlgLevelStrc* pLevel)
{
	if (DRLG_IsTownLevel(pLevel->nLevelId))
	{
		return LVLPREST_NONE;
	}

	const D2SafeZoneLevelTxt* pLevelRecord = DRLGSAFEZONE_GetLevelRecord(pLevel->nLevelId);
	if (!pLevelRecord || !pLevelRecord->dwChance || pLevelRecord->nPreset <= LVLPREST_NONE)
	{
		return LVLPREST_NONE;
	}

	if (SEED_RollLimitedRandomNumber(&pLevel->pSeed, 100) >= pLevelRecord->dwChance)
	{
		return LVLPREST_NONE;
	}

	return pLevelRecord->nPreset;
}

void __fastcall DRLGSAFEZONE_SpawnOutdoorSafeZone(D2DrlgLevelStrc* pLevel)
{
	if (!pLevel->pOutdoors)
	{
		return;
	}

	const int nLvlPrestId = DRLGSAFEZONE_RollPreset(pLevel);
	if (nLvlPrestId == LVLPREST_NONE)
	{
		return;
	}

	if (!DRLGSAFEZONE_IsSafeZonePreset(nLvlPrestId))
	{
		FOG_Trace("Safe zone: level %d names LvlPrest %d, which has no SafeZone=1", pLevel->nLevelId, nLvlPrestId);
		return;
	}

	const int nSizeX = DRLGPRESET_GetSizeX(nLvlPrestId);
	const int nSizeY = DRLGPRESET_GetSizeY(nLvlPrestId);
	if (nSizeX <= 0 || nSizeY <= 0 || nSizeX % 8 || nSizeY % 8)
	{
		FOG_Trace("Safe zone: LvlPrest %d is %dx%d tiles, outdoor presets must be multiples of 8", nLvlPrestId, nSizeX, nSizeY);
		return;
	}

	// Same placement the game uses for its cottages and camps: a random free grid cell, preferably next to
	// a dirt path. Fails silently when the level has no room left.
	DRLGOUTDOORS_SpawnRandomOutdoorDS1(pLevel, nLvlPrestId, -1);
}

// Maze level types whose room presets are "base + opening bits" (DRLGMAZE_PickRoomPreset), so a room that gets
// an extra opening can be given a matching preset again. The others use remapping tables without every
// combination (harem, basement, spider caves, Nihlathak's temple, Act 5 lava) or are not built from a maze.
static bool DRLGSAFEZONE_CanExtendMaze(D2DrlgLevelStrc* pLevel)
{
	switch (pLevel->nLevelType)
	{
	case LVLTYPE_ACT1_CAVE:
	case LVLTYPE_ACT1_CRYPT:
	case LVLTYPE_ACT1_JAIL:
	case LVLTYPE_ACT1_CATACOMBS:
	case LVLTYPE_ACT2_SEWER:
	case LVLTYPE_ACT2_TOMB:
	case LVLTYPE_ACT2_LAIR:
	case LVLTYPE_ACT3_KURAST:
	case LVLTYPE_ACT3_DUNGEON:
	case LVLTYPE_ACT3_SEWER:
	case LVLTYPE_ACT4_LAVA:
	case LVLTYPE_ACT5_BAAL:
		break;

	case LVLTYPE_ACT5_ICE_CAVES:
		// Single room ice levels have no maze to extend.
		if (pLevel->pMaze && pLevel->pMaze->dwRooms[pLevel->pDrlg->nDifficulty] == 1)
		{
			return false;
		}
		break;

	default:
		return false;
	}

	// These two lay out their rooms with their own coordinates.
	return pLevel->nLevelId != LEVEL_BARRACKS && pLevel->nLevelId != LEVEL_RIVEROFFLAME;
}

void __fastcall DRLGSAFEZONE_SpawnMazeSafeZone(D2DrlgLevelStrc* pLevel)
{
	// The direction DRLGMAZE_LinkMazeRooms takes to attach a dead end that opens to the N, E, S and W,
	// as the game's own dead-end tables pair them (e.g. LVLPREST_ACT1_CAVE_PREV_N with direction 3).
	static const int nDirections[4] = { 3, 0, 1, 2 };

	if (!pLevel->pMaze || !pLevel->nRooms || !DRLGSAFEZONE_CanExtendMaze(pLevel))
	{
		return;
	}

	const int nFirstPreset = DRLGSAFEZONE_RollPreset(pLevel);
	if (nFirstPreset == LVLPREST_NONE)
	{
		return;
	}

	int nAvailable = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (DRLGSAFEZONE_IsSafeZonePreset(nFirstPreset + i))
		{
			++nAvailable;
		}
	}

	if (!nAvailable)
	{
		FOG_Trace("Safe zone: level %d names LvlPrest %d, but none of the 4 rows from there has SafeZone=1", pLevel->nLevelId, nFirstPreset);
		return;
	}

	const int nRoomCount = pLevel->nRooms;
	const int nFirstRoom = (int)SEED_RollLimitedRandomNumber(&pLevel->pSeed, nRoomCount);
	const int nFirstSide = (int)SEED_RollLimitedRandomNumber(&pLevel->pSeed, 4);

	// Rooms added below are appended to the level's list; only the rooms that existed before are candidates.
	D2DrlgRoomStrc* pCandidate = pLevel->pFirstRoomEx;
	for (int i = 0; i < nFirstRoom && pCandidate; ++i)
	{
		pCandidate = pCandidate->pDrlgRoomNext;
	}

	for (int nTried = 0; nTried < nRoomCount; ++nTried)
	{
		if (!pCandidate)
		{
			pCandidate = pLevel->pFirstRoomEx;
		}

		D2DrlgRoomStrc* pParent = pCandidate;
		pCandidate = pCandidate->pDrlgRoomNext;

		if (pParent->nType != DRLGTYPE_PRESET || !pParent->pMaze || DRLGMAZE_HasMapDS1(pParent))
		{
			continue;
		}

		for (int nSide = 0; nSide < 4; ++nSide)
		{
			const int nIndex = (nFirstSide + nSide) % 4;
			const int nLvlPrestId = nFirstPreset + nIndex;
			if (!DRLGSAFEZONE_IsSafeZonePreset(nLvlPrestId))
			{
				continue;
			}

			// Same steps as DRLGMAZE_ScanReplaceSpecialPreset uses to attach a special dead end.
			D2DrlgRoomStrc* pSafeRoom = DRLGROOM_AllocRoomEx(pLevel, DRLGTYPE_PRESET);
			pSafeRoom->nTileWidth = pLevel->pMaze->dwSizeX;
			pSafeRoom->nTileHeight = pLevel->pMaze->dwSizeY;

			if (!DRLGMAZE_LinkMazeRooms(pSafeRoom, pParent, nDirections[nIndex]))
			{
				DRLGROOM_FreeRoomEx(pSafeRoom);
				continue;
			}

			DRLGROOM_AllocDrlgOrthsForRooms(pParent, pSafeRoom, nDirections[nIndex]);
			DRLGROOM_AddRoomExToLevel(pLevel, pSafeRoom);

			// The parent has one more opening now and needs the matching preset.
			DRLGMAZE_PickRoomPreset(pParent, TRUE);

			pSafeRoom->pMaze->nLevelPrest = nLvlPrestId;
			pSafeRoom->pMaze->nPickedFile = -1;
			pSafeRoom->pMaze->dwFlags |= DRLGPRESETROOMFLAG_HAS_MAP_DS1;
			return;
		}
	}

	FOG_Trace("Safe zone: no free spot for a safe zone in level %d", pLevel->nLevelId);
}
