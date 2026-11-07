# Plan: adding a sixth act (D2MOO + D2Client 1.10f)

Status: **investigation / plan only**. Nothing here is implemented.

This plan covers both rewrites in this workspace:

* **D2MOO** (`D2Common`, `D2Game`, `D2Win`, ...), built with `D2MOO_ORDINALS_VERSION=1.10f`.
* **D2Client** (the 1.10 `D2Client.dll` rewrite).

"Act VI" below means a new act after Act V (Harrogath / Baal), expansion only.

---

## 0. The constraints that drive everything

1. **Structure layouts and the original DLLs.** D2MOO patches the original game. Any DLL that is still the
   original binary uses the original struct layouts and the 5-act assumptions. Growing `D2GameStrc::pAct[5]`,
   `D2ClientStrc::aLastWarpAttemptsFrame[5]`, `D2DataTablesStrc::pMonPresetTxtActSections[5]` etc. means
   **D2Common, D2Game, D2Win and D2Client must all be the rewritten versions**, with nothing left patched in from the
   original (check `D2.Detours.patches` and the patch config so no original function that touches these structs
   stays active). D2Launch and D2Multi are not in either repo. They still assume 5 acts (character-select titles,
   the "Act N" label), so plan for cosmetic glitches there, or for rewriting the parts involved.
2. **The save file and the network protocol change.** Characters, games and clients made with the 5-act build
   will not work with the 6-act build. Choose one save-format version for the new build and either refuse old
   saves or migrate them (see §3).
3. **Levels are mapped to acts by level-id order, not by data.** `DRLG_GetActNoFromLevelId`
   (`D2Common/src/Drlg/DrlgDrlg.cpp:875`) walks a hard-coded list of town ids. Act VI levels therefore **must be
   appended at the end of Levels.txt**, with the Act VI town as the first new id. 1.10f ends at 132
   (`LEVEL_THEWORLDSTONECHAMBER`). 1.11+ uses 133–136 for the Pandemonium (uber) levels (`D2MOO_WITH_UBERS`).
   **Recommendation: start Act VI at 137** so it never clashes with the uber build. Several packets carry the level
   id as a `uint8_t` (`D2GSPacketSrv07/08/60`, ...), so all level ids must stay **≤ 254**.
4. **The D2Client headers are generated.** `D2Constants.h` (`D2C_Acts::NUM_ACTS = 5`, the `D2C_Levels` enum) and
   `D2Structs.h` are "generated from the reverse-engineering database, not edited by hand". Either regenerate them
   with the new values or add a hand-written override header for mod constants. Decide this before writing code.

---

## 1. Data / asset work (no code, but the biggest effort)

| Asset | What is needed |
|---|---|
| `Levels.txt` | New rows, ids 137+, `Act = 5` (0-based), town first. Set `Waypoint` numbers to the next free values (1.10 uses 0–38; the bitfield has 112 slots). Set LevelType, LevelPrest links, Vis/Warp links, monster lists. Add the Act V → Act VI link if it is walkable rather than a portal. |
| `LvlTypes.txt` | New level types with `Act = 6` (`DATATBLS_CheckActInLevelTypesTxt`, used by `GAME_PreloadActData`). |
| `LvlPrest.txt`, `LvlMaze.txt`, `LvlSub.txt`, `LvlWarp.txt` | Presets, mazes, substitutions and warps for the new levels. |
| DS1 / DT1 | New tiles under `data\global\tiles\act6\...` and DS1 maps. DS1 files store their act. `DRLGPRESET` clamps it to `ACT_V` (see §2.1). |
| `MonPreset.txt` | An Act 6 section (today the loader keeps exactly 5 sections). |
| `MonStats/MonStats2`, `SuperUniques`, `TreasureClassEx`, `Npc.txt`, `Hireling.txt` | New monsters, the boss, town NPCs, Act 6 treasure classes, the Act 6 hireling (`Hireling.txt` has an Act column). |
| `Objects.txt`, `ObjGroup.txt`, `ObjPreset` | The town portal/waypoint objects of the act, the quest objects, and the portal from Act V to Act VI. |
| Palette | `data\global\palette\act6\pal.dat` and `pal.pl2` (see the D2Win clamp in §2.5). |
| COF cache | One more `cmncof_*.d2` (Act V already uses `cmncof_a6.d2`, so name it e.g. `cmncof_a7.d2`). |
| UI art (DC6) | `expquesttabs` and `expwaygatetabs` with a 6th tab (2 cels per tab); quest icons for the new act (quest log); the loading screen frame for the act; automap town icons if the town needs its own cel file. |
| Strings (`.tbl`) | Level names, NPC dialogue, quest log text, the act title ("ACT6"/expansion stem), the "travel to ..." menu entries. |
| Sound / music | Town and area music, ambience (LvlTypes/levels entries and client-side tables, see §4). |
| Cinematics (optional) | Intro/outro video for the act. |

---

## 2. D2Common (D2MOO `source/D2Common`)

### 2.1 Act count and level → act mapping
* `D2CommonDefinitions/include/D2Constants.h:88` – add `ACT_VI` before `NUM_ACTS` (`NUM_ACTS` becomes 6).
* `D2Common/include/DataTbls/LevelsIds.h` – add the new `LEVEL_*` ids (and new `LVLTYPE_ACT6_*` before `NUM_LVLTPYES`).
* `Drlg/DrlgDrlg.cpp:875` `DRLG_GetActNoFromLevelId` – add the Act VI town to `gnTownIds` and use `NUM_ACTS`
  instead of the literal `5`. (Better: look the act up from `Levels.txt` as the `IMPROVEMENT` comment suggests.
  The level-order rule still has to hold for the client, see §4.)
* `Drlg/DrlgPreset.cpp:148-156` – the DS1 act is clamped to `ACT_V`. Raise the clamp to `ACT_VI`.
* `D2Dungeon.cpp:1098` – `gnTownLevelIds[]` lists the five towns (it backs the town check). Add the new town.
* `Drlg/DrlgRoomTile.cpp:279` – a per-town tile table (`{ LEVEL_HARROGATH, 23, 24 }`). Add a row for the new town.

### 2.2 Act generation (DRLG)
* `Drlg/DrlgDrlg.cpp:47` `DRLG_AllocDrlg` – a per-act `switch` loads a town DT1 and seeds the act's random choices.
  Add an `ACT_VI` case if the act needs one.
* `Drlg/DrlgOutdoors.cpp:771` – the outdoor generator is chosen per act (`InitAct1..5OutdoorLevel`). Either reuse an
  existing generator for the new outdoor level types or write `DRLGOUT*_InitAct6OutdoorLevel` (a large job if the
  outdoor layout is procedural, like the Act II desert or the Act V siege). The `dwDt1Mask` switch on `nLevelType`
  directly below also needs entries for the new level types.
* `Drlg/DrlgOutPlace.cpp:752, 840-899, 1499-1556, 1907` – level connections, border tiles and outdoor placement per act.
* `Drlg/DrlgMaze.cpp:3024`, `Drlg/DrlgDrlgAnim.cpp:25` – act-specific maze and animated-tile rules.
* `DrlgOutDesr.cpp` / `DrlgPreset.cpp:70` (`dword_6FDE1180[5][150]`) – per-act preset tables. Add a 6th row.

### 2.3 Data tables
* `include/D2DataTbls.h:373-374` – `pMonPresetTxtActSections[5]`, `nMonPresetTxtActRecordCounts[5]` → `[NUM_ACTS]`
  (**changes the layout of `D2DataTablesStrc`**, see constraint 1).
* `DataTbls/MonsterTbls.cpp:2611` – `nAct < 5` → `NUM_ACTS`. The MonPreset loader must split 6 sections.
* `Monsters/Monsters.cpp:436` – `dword_6FDE4E18[5]` is a table of item codes (not per act). No change needed.

### 2.4 Environment, waypoints, quest record
* `D2Environment.cpp:57, 102, 175, 252-277` – day/night cycle, light and weather per act (Act IV has no day, for
  example). Decide how Act VI behaves.
* `D2Waypoints.cpp` – `gnNumberOfWaypoints = 7*8*sizeof(short)` = 112 slots, so the bitfield has room. Only the new
  `Levels.txt` waypoint numbers are needed. No format change.
* `D2QuestRecord.h:7` `NUM_QUEST_WORDS 48` (96 bytes per difficulty). Words 0–41 are in use
  (`QUESTSTATEFLAG_RESPEC = 41`), so **only words 42–47 (6) are free**. An act with an intro word, a "completed"
  word and N quests needs N + 2 words, and Act V also needs an `A5COMPLETED` word (it does not have one today).
  * **Option A (no format change):** at most 3 quests + Act V completed + Act VI intro + Act VI completed = 6 words.
  * **Option B (recommended if the act has 4–6 quests):** grow the record (e.g. 64 words = 128 bytes). This
    changes the save file (`'Woo!'` section: `PLRSAVE2` writes `298 = 10 + 3*96` bytes,
    `D2Game/src/PLAYER/PlrSave2.cpp:540-551`, and the reader at `:1643`) and the quest packets
    (`D2PacketDef.h:1086, 1092` carry `pData[96]`). See §3.

### 2.5 D2Win
* `D2Win/src/D2WinPalette.cpp:58` `D2Win_10177` – clamps the act to 1..5 and falls back to the Act 1 palette.
  Allow 6.

---

## 3. D2Game (D2MOO `source/D2Game`)

### 3.1 Game and client structures (layout changes)
* `include/GAME/Game.h:217-219` – `pAct[5]`, `pInactiveUnitList[5]` → `[NUM_ACTS]`.
* `include/GAME/Clients.h:213` – `aLastWarpAttemptsFrame[5]` → `[NUM_ACTS]`.
* Loops that already use `NUM_ACTS` (`GAME/Game.cpp:1901`, `GAME/Level.cpp:127, 399`, `Debug.cpp:65`,
  `Clients.cpp:1185`, `PlayerStats.cpp:29`, `PlrSave2.cpp:817`, `Quests.cpp:1135`) scale on their own. Check each one.
* Hard-coded `5`s to replace: `PLAYER/PlrSave.cpp:903` (`nAct >= 5`), `OBJECTS/ObjMode.cpp:3384` (`nAct < 5`).

### 3.2 Save file and character progression
* `PlrSave.cpp:901` – the save header stores the act in the low 4 bits of byte 88, so 0–5 fits. Only the bound
  changes.
* `Clients.h:68-88` – `nProgression` is 5 bits (0–31). `CLIENTS_UpdateCharacterProgression` (`Clients.cpp:1281`)
  computes `act + difficulty * actsPerDifficulty`, so with 6 acts the expansion maximum becomes 18, which still fits.
  **But the meaning of existing values changes**, and the difficulty unlock checks hard-code the old numbers:
  * `PlrSave.cpp:857-870` – `< 8` (Hell), `< NUM_ACTS` (Nightmare in the expansion), `< 4` (classic). Rewrite these
    in terms of "acts per difficulty" for classic and expansion separately.
  * Decide whether Nightmare and Hell unlock after Baal (Act V), as now, or after the Act VI boss. If they unlock
    after the new boss, `A5Q6.cpp:133, 583, 724` stop being the "difficulty finished" point.
  * D2Launch, which is not rewritten, computes the character titles (Slayer, Champion, ...) from this field. Expect
    the titles to be wrong unless D2Launch is patched too.
* Save versioning: if the quest record grows (Option B), bump the `'Woo!'` section version (`= 6` at
  `PlrSave2.cpp:544`) and the save version, and either migrate old saves on load (pad the quest words with zeroes)
  or refuse them.

### 3.3 Quests
* `include/QUESTS/Quests.h` – add `QUESTSTATEFLAG_A5COMPLETED`, `QUESTSTATEFLAG_A6Q0..A6Qn`,
  `QUESTSTATEFLAG_A6COMPLETED` (words 42+), and `QUEST_A6Q*` ids after `QUEST_A5Q6_BAAL = 36`.
* `src/QUESTS/Quests.cpp:~100-155` `gpQuestInitTable` – add rows for the Act VI quests and an `ACT6Intro` row,
  like `ACT5Intro_InitQuestData`.
* New files `src/QUESTS/ACT6/A6Q*.cpp` plus headers: one module per quest (init, callbacks, status filters, boss
  kill handling), modelled on the ACT5 modules. **This is the largest code item.**
* `Quests.cpp:2095-2140` – NPC intro flags per act (`gpAct3_NPCIds`, `gpAct5_NPCIds`, packet 0x91). Add an
  `ACT_VI` case and `gpAct6_NPCIds`.
* `Quests.cpp:2146` `QUESTS_ActChange_HirelingChangeAct` and the act-completion block (`:2160-2345`, which sets
  `A1..A4COMPLETED`) – add Act V → VI completion and set `A5COMPLETED`.
* `QUESTS/ACT5/A5Q6.cpp:240-262` – Baal's end portal (`OBJECT_LAST_PORTAL`). Point it at the Act VI town, or
  add a new portal object, instead of ending the difficulty there.
* `Quests.cpp:1800` and `:2938` – level-id special cases (`nLevelId >= 113`, `LEVEL_THEWORLDSTONECHAMBER`) assume
  Act V is the last act. Check that they do not catch Act VI levels (ids ≥ 137). `>= 113` **will** catch them.

### 3.4 Moving between acts, NPCs, vendors
* `UNIT/SUnitNpc.cpp:2060-2120` – the "travel to" handlers (Warriv, Meshif, Tyrael...). Add Harrogath ↔ Act VI
  travel through a chosen NPC, including `D2GAME_PlayerChangeAct_6FC867C0` and the hireling move.
* `UNIT/SUnitProxy.cpp:140-160` – the per-act NPC table (vendors, gamble, heal, ...). Add the Act VI NPCs.
  `:445-500` `SUNITPROXY_UpdateNpcsOnActChange` and `:610` – add the town's case and `UpdateVendorInventory(..., ACT_VI)`.
* `UNIT/SUnit.cpp:390` – special destination levels for warps. Check whether a new boss level needs to be listed.
* `OBJECTS/Objects.cpp:786-789` and `OBJECTS/ObjMode.cpp:3181-3191` – portal objects with fixed destinations
  (Hell portal, Act IV → V). Add the Act V → VI portal.
* `AI/AiBaal.cpp:214, 658` – check that nothing depends on Baal being the last boss.
* New monster AI for the Act VI boss or uniques (`src/AI/`), plus `MonStats` AI hooks, if they do not reuse an
  existing AI.

### 3.5 Hirelings
* `Hireling.txt` rows with `Act = 6`, client hireling item rules (§4), and the act-change hireling code
  (`QUESTS_ActChange_HirelingChangeAct`).

---

## 4. D2Client (`D2Client/`)

### 4.1 Constants and act loading
* `D2Constants.h:363-370` – `ACT_VI`, `NUM_ACTS = 6`, and the new `D2C_Levels` values (regenerate or override, see
  constraint 4).
* `Game.cpp:2437-2456` – the `static_assert(NUM_ACTS + 1 == 6)` and the start-act parameter bound.
* `Game.cpp:626-673` `GAME_PreloadActData` – act allocation, `UI_SetLoadScreenAct`, `GFX_LoadActCofData`.
* `Gfx.h:34` – `gActCofDataFiles[5]` (+ its `static_assert(sizeof == 20)`) → 6 entries. `Gfx.cpp:3480` already
  notes that act ≥ 5 reads out of bounds.
* The loading screen frame per act (`UI_SetLoadScreenAct`) needs a new frame.

### 4.2 Quest log (`QuestLog.cpp`)
* The tab strip is 5 × 64 px = 320 px (`:325-356`, `iActTab < 5`). Six tabs need a new tab width (~53 px) or a
  wider panel, and new `expquesttabs` art.
* `gQuestLogActIconRange[5][2]`, `gnQuestLogSelectedPerAct[5]`, `gnQuestLogLastClickedPerAct[5]` → `[NUM_ACTS]`.
* `:359`, `:1041` – the `nAct == 4` "expansion only" checks become `nAct >= ACT_V`.
* `:674` – the `nAct >= 5` clamp.
* Map the quest-log entries and icons of the new act to the new `QUESTSTATEFLAG_A6*` words.

### 4.3 Waypoint panel (`waypoint.cpp`)
* Tab X positions `5, 67, 129, 191, 253` (5 tabs, `:113-245`). Add a 6th position (narrower tabs) and the
  `expwaygatetabs` art.
* The unlock gates (`:236` switch, `:464-507` `WAYPOINT_ClampActTab`) are a hand-written fall-through chain on quest
  words 7, 15, 23, 28. Add `case 5` gated on the new `A5COMPLETED` word.
* `gWaypointActTable[5]` (`:562-586`) → `[NUM_ACTS]`, with the first/last level ids of Act VI.
  `gnWaypointActCount` must be 6 in expansion games.
* `gWaypointList` holds 9 rows (the most waypoints any act has). Keep Act VI at ≤ 9 waypoints or grow the list and
  `gWaypointCoords`.

### 4.4 Other per-act or per-level client code
* `ui_panels.cpp:225` – the level-entry title uses `"ACT%d"` only for levels `< LEVEL_HARROGATH` and the expansion
  stem otherwise. Act VI levels would show the Act V title.
* `npcmenu.cpp:938` – the "travel to Harrogath" menu command is hard-coded (`MSG_SendCmdUnitParam(0x38, ...,
  LEVEL_HARROGATH)`). Add an entry for the Act VI town and NPC menu records (`gNpcMenuEntries`) for the new NPCs.
* `automap.cpp:368-421` (town icon cel files), `:1060` (the town-callback level list), `:1284`, `:2995` (per-act
  draw modes).
* `Env.cpp:66, 141, 279` – weather (snow, wind) per level id. Add the Act VI levels if they have weather.
* `Hireables.cpp:~1000` – which items each act's hireling can use. Add the Act VI hireling class.
* `Quests.cpp`, `Quest.cpp`, `QuestsFX.cpp` – client-side quest effects and NPC lines keyed by quest or level id.
  Add the new quests' effects (screen shakes, fades, boss-kill effects).
* `SoundEnv.cpp` / `SoundSong.cpp` – check for per-act or per-level music and ambience tables.
* `Video.cpp` – optional act cinematics.

---

## 5. Suggested order of work

1. **Decide:** level ids (137+), the quest-record option (A: ≤ 3 quests, no format change; B: grow to 64 words),
   where the difficulty unlocks, how to edit the generated client headers, and how old saves are handled.
2. **Constants and arrays:** `NUM_ACTS = 6` everywhere, every literal `5` / `[5]` listed above, the save and
   progression checks. Build both repos and run D2MOO's tests (`source/TestDefinitions`, `TestUtilities`).
   The 5 existing acts should play exactly as before.
3. **Empty act:** a minimal Act VI with a town level, one outdoor preset level, a waypoint and the
   Harrogath ↔ town travel NPC (reusing Act V tiles, palette and COF). This exercises DRLG, act loading on server
   and client, the waypoint tab and act changes, without new art.
4. **UI:** the 6-tab quest log and waypoint panel, the act title, the automap and the loading screen.
5. **Content:** real tiles and DS1s, monsters, treasure classes, NPCs, vendors, the hireling.
6. **Quests:** the `A6Q*` modules, the boss and AI, the Act V → VI handoff, the act completion and progression
   update.
7. **Saves and compatibility:** the save-version bump and migration, tests for loading old characters,
   multiplayer join checks (`PlrSave.cpp:857-870`).
8. **Polish:** music, weather, cinematics, D2Launch titles.

## 6. Risks

* **Mixing original and rewritten DLLs.** Any original function still patched in that touches a grown struct will
  corrupt memory. Every module involved has to be the rewritten one.
* **The D2Client rewrite reproduces the original's bugs on purpose** (`BUG:` / `DIFFERENCE:` markers, `BUGS.md`).
  Several of them become reachable with a 6th act (for example `Gfx.cpp:3480`, the waypoint bound at
  `waypoint.cpp:520`). Each change here is a deliberate departure from 1.10 behaviour and should be marked as one.
* **Procedural outdoor generation** for a new act is the hardest DRLG work. Use presets or reuse an existing
  generator first.
* **The 6 free quest words** are a hard ceiling unless the save format changes.
