# Safe zones (town-like areas inside regular levels)

A *safe zone* is a preset room inside a normal level that the game treats like a town room:
`DUNGEON_IsRoomInTown` (D2Common #10082) answers `TRUE` for it. Every caller of that function, in D2Common,
D2Game and D2Client (original or rewritten), therefore applies the town rules there:

- Monsters do not spawn in the zone, and monsters that may not enter towns do not path into it.
- Monster AI does not chase players standing in the zone.
- Town damage and missile rules apply, and skills without `InTown` cannot be used.
- The stash works (the server requires both the player and the stash to be in a town room).
- Items dropped there are item level 1, as in towns.

The level itself stays a normal level: its music, its warps and its automap stay what they are, and
`DUNGEON_IsTownLevelId` / `DRLG_IsTownLevel` still answer by level id only.

The code is in `source/D2Common/src/Drlg/DrlgSafeZone.cpp`.

## Data

The data comes from extra columns of `LvlPrest.txt` and `Levels.txt`. They are read **from the `.txt` files**
(`data\global\excel\*.txt`) on first use, separately from the regular table loading, so the original record
layouts and `.bin` files are not changed. If a file or its first column is missing, there are no safe zones and
maps are generated exactly as in the original game.

### LvlPrest.txt

| Column      | Meaning |
|-------------|---------|
| `SafeZone`  | `1` marks the preset as a safe zone. |
| `EntryName` | `.tbl` key of the zone's name, shown by the client when the player walks in and on the automap. |
| `EntryFile` | Optional title image, looked up like `Levels.txt`'s `EntryFile` (`data\local\UI\<lang>\ACT<n>\<EntryFile>`). |

Set `Populate` to `0` as well; it is not required (safe zones are never populated) but keeps the data honest.

### Levels.txt

| Column           | Meaning |
|------------------|---------|
| `SafeZoneChance` | 0-100: chance for the level to get a safe zone when it is generated. `0` or empty: never, and no random number is rolled. |
| `SafeZonePreset` | `Def` of the `LvlPrest.txt` row to place (see below). |

The chance is rolled with the level's own seed, so the server and the client build the same map.
Towns never get one.

### Outdoor levels

`SafeZonePreset` names one preset whose `SizeX`/`SizeY` are multiples of 8 tiles. An 8x8 preset is exactly one
room of the level's grid. It is placed after the act's own presets, the way cottages and camps are placed (a free
grid cell, preferably next to a dirt path). If there is no free cell, the level simply has no safe zone.

### Maze levels (caves, crypts, sewers, ...)

`SafeZonePreset` names the **first of four consecutive** `LvlPrest.txt` rows: dead-end rooms opening to the
north, east, south and west, in that order (the order the game's own dead-end presets use, e.g.
`Act 1 - Cave Prev N/E/S/W`). Each must be the size of the level's maze rooms (`LvlMaze.txt` `SizeX`/`SizeY`).
Rows without `SafeZone=1` are skipped, so a single direction is enough to try the feature.

The zone is attached as an extra dead end to a random room of the maze, whose own preset is re-picked for the new
opening. Supported level types (`LvlTypes.txt`): `ACT1_CAVE`, `ACT1_CRYPT`, `ACT1_JAIL`, `ACT1_CATACOMBS`,
`ACT2_SEWER`, `ACT2_TOMB`, `ACT2_LAIR`, `ACT3_KURAST` (maze levels), `ACT3_DUNGEON`, `ACT3_SEWER`, `ACT4_LAVA`,
`ACT5_ICE_CAVES` (multi-room levels only) and `ACT5_BAAL`. These are the types whose room presets are picked as
"base preset + opening bits", so the parent room can get a matching preset again. Not supported: the Barracks,
the River of Flame, the Arcane Sanctuary, the harem, palace cellars, spider caves, Nihlathak's temple and the
Act 5 lava levels.

## Exports

These exist only in the D2MOO `D2Common.dll` (they are not in the original's export table), by name and ordinal:

| Ordinal | Function |
|---------|----------|
| 11308 | `BOOL __stdcall DUNGEON_IsRoomSafeZone(D2ActiveRoomStrc* pRoom)` |
| 11309 | `int __stdcall DUNGEON_GetSafeZonePresetIdFromRoom(D2ActiveRoomStrc* pRoom)` (-1 if none) |
| 11310 | `const Unicode* __stdcall DUNGEON_GetSafeZoneEntryName(int nLvlPrestId)` (NULL if none) |
| 11311 | `const char* __stdcall DUNGEON_GetSafeZoneEntryFile(int nLvlPrestId)` (NULL if none) |

## Known limits

- Monster ranged attacks fired from outside still reach players inside, as in towns. Walls in the `.ds1` are
  what keep monsters from walking through the zone; the town rule only stops them from targeting points inside it.
- Town Portal cannot be cast inside the zone yet (it is a town room, and the skill has no `InTown`).
