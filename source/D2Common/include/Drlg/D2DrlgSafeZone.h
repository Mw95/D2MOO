#pragma once

#include "D2CommonDefinitions.h"
#include "D2DrlgDrlg.h"
#include <D2Unicode.h>

// Town-like safe zones inside regular levels (mod, not part of the original game).
//
// A safe zone is a preset room (a LvlPrest.txt row) that the game treats exactly like a town room:
// DUNGEON_IsRoomInTown answers TRUE for it, so monsters do not spawn in it or path into it, town skill
// rules apply, damage and missiles follow the town rules and the stash works.
//
// The data comes from extra columns of the regular .txt files. They are read straight from the .txt
// (never from the .bin), so the original record layouts, the .bin files and the tests stay untouched:
//
// LvlPrest.txt
//   SafeZone    1 marks the preset as a safe zone.
//   EntryName   .tbl key of the name shown when entering the zone (title and automap).
//   EntryFile   optional title image (data\local\UI\<lang>\ACT<n>\<EntryFile>), like Levels.txt's EntryFile.
//
// Levels.txt
//   SafeZoneChance  0-100, chance for the level to get a safe zone (0 or missing: never; the map is then
//                   generated exactly like the original, no extra random number is rolled).
//   SafeZonePreset  LvlPrest Def of the preset to place.
//                   Outdoor levels: one preset whose size is a multiple of 8 tiles (8x8 for a single room).
//                   Maze levels:    the first of four consecutive LvlPrest rows: dead ends opening to the
//                                   N, E, S and W, in that order (the order the game's own dead-end presets
//                                   use), each the size of the level's maze rooms (LvlMaze.txt SizeX/SizeY).
//                                   Rows without SafeZone=1 are skipped.

#pragma pack(1)

struct D2SafeZonePresetTxt
{
	uint32_t dwSafeZone;					//0x00
	char szEntryName[40];					//0x04
	char szEntryFile[40];					//0x2C
	Unicode wszEntryName[40];				//0x54 resolved from szEntryName after loading
};

struct D2SafeZoneLevelTxt
{
	uint32_t dwChance;						//0x00
	int32_t nPreset;						//0x04
};

#pragma pack()

// Loads the extra columns on first use. Thread safe.
void __fastcall DRLGSAFEZONE_EnsureLoaded();
// Frees the loaded tables. They are reloaded on the next use.
void __fastcall DRLGSAFEZONE_Unload();

const D2SafeZonePresetTxt* __fastcall DRLGSAFEZONE_GetPresetRecord(int nLvlPrestId);
const D2SafeZoneLevelTxt* __fastcall DRLGSAFEZONE_GetLevelRecord(int nLevelId);

BOOL __fastcall DRLGSAFEZONE_IsSafeZonePreset(int nLvlPrestId);
// Returns the safe zone's LvlPrest id, or -1 if the room is not a safe zone.
int __fastcall DRLGSAFEZONE_GetSafeZonePresetId(D2DrlgRoomStrc* pDrlgRoom);
BOOL __fastcall DRLGSAFEZONE_IsDrlgRoomSafeZone(D2DrlgRoomStrc* pDrlgRoom);

// While the calling thread holds an override (DRLGSAFEZONE_PushTownOverride), safe zones do not count as town for
// DUNGEON_IsRoomInTown. Used to let Town Portal be cast inside a safe zone. Calls nest.
void __fastcall DRLGSAFEZONE_PushTownOverride();
void __fastcall DRLGSAFEZONE_PopTownOverride();
BOOL __fastcall DRLGSAFEZONE_IsTownOverrideActive();

// Called by DRLGOUTDOORS_GenerateLevel once the act specific presets have been placed.
void __fastcall DRLGSAFEZONE_SpawnOutdoorSafeZone(D2DrlgLevelStrc* pLevel);
// Called by DRLGMAZE_GenerateLevel once the maze layout and its special rooms are in place.
void __fastcall DRLGSAFEZONE_SpawnMazeSafeZone(D2DrlgLevelStrc* pLevel);
