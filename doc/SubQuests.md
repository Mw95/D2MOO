# Subquests

Small quests that NPCs give and take back, defined in data. They sit beside the game's own quests and never change
them. Typically the giver is a [custom NPC](CustomNpcs.md) in a [safe zone](SafeZones.md), but any NPC can give them.

## How it plays

- **Talking to the giver accepts.** When the player talks to an NPC that gives subquests, the NPC says the first
  subquest's `TextOffer` the player may start (prerequisites met, not done before in this difficulty), and the
  subquest is under way. A chat line says "New subquest: <name>".
- **Progress** is reported in the chat log ("Subquest: <name> (3/10)", "Subquest goal reached, return to the quest
  giver: <name>").
- **Talking again** turns it in when the goal is reached: items are taken if `TakeItems=1`, the rewards are given,
  the NPC says `TextDone` and the chat says "Subquest completed: <name>". Otherwise the NPC says `TextProgress`.
  One subquest is handled per talk; the next talk offers the next one.
- Each subquest can be done **once per difficulty**. Several can be under way at once.
- **Kills** count for the killer (its hireling, summons and minions included) and for the killer's party members
  in the monster's level who have the subquest under way.
- **Quest bosses** (`boss` goal) spawn next to the player when a player with the subquest under way enters
  `GoalLevel`. A superunique without `Stacks` spawns once per game.

The chat lines can be translated: define the `.tbl` keys `SubQuestNew`, `SubQuestUpdate`, `SubQuestReady` and
`SubQuestDone`; without them the English texts above are used.

## SubQuests.txt

`data\global\excel\SubQuests.txt`, tab separated, first line the column names. Read from the `.txt` on first use
(there is no `.bin`). Without the file there are no subquests and none of the hooks does anything.

| Column | Meaning |
|--------|---------|
| `Id` | 1-65535. Unique, and **never change or reuse it**: saves store progress by Id. Rows with Id 0/empty are ignored. |
| `Giver` | MonStats row (`hcIdx`) of the NPC that gives and takes it. |
| `ReqQuest` | Game quest that must be completed first (reward granted), as quest record index: 1 Den of Evil, 2 Sisters' Burial Grounds, 3 Tools of the Trade, 4 The Search for Cain, 5 The Forgotten Tower, 6 Sisters to the Slaughter, 9 Radament's Lair, ... (`D2QuestStateFlagIds` in `source/D2Game/include/QUESTS/Quests.h`). 0/empty: none. |
| `ReqSubQuest` | Id of a subquest that must be completed first. 0/empty: none. |
| `ReqLevel` | Minimum character level. |
| `Goal` | `kill`, `boss`, `item`, `level` or `talk`. |
| `GoalMonster` | `kill`: MonStats row of the monsters. `talk`: MonStats row of the NPC to talk to. |
| `GoalSuperUnique` | `boss`: `SuperUniques.txt` row. |
| `GoalLevel` | `kill`: only kills in this level count (0: anywhere). `boss`: the level it spawns in. `level`: the level to reach. |
| `GoalItem` | `item`: item code (e.g. `hp1`). Counted in the inventory, stash, cube, belt and cursor, equipped items excluded. |
| `GoalCount` | `kill`, `item`: how many (0/empty: 1). |
| `TakeItems` | `item`: 1 takes the items away on turn-in. |
| `Name` | `.tbl` key of the subquest's name, for the chat lines. |
| `TextOffer`, `TextProgress`, `TextDone` | `.tbl` keys of what the giver says. |
| `ExpNormal`, `ExpNightmare`, `ExpHell` | Experience reward per difficulty (levels up as needed). |
| `GoldNormal`, `GoldNightmare`, `GoldHell` | Gold reward: into the inventory up to its limit, the rest into the stash up to its limit. |
| `RewardItem` | Item code given on turn-in (dropped at the player's feet when there is no room), empty for none. |
| `RewardItemQuality` | 1 inferior, 2 normal, 3 superior, 4 magic, 5 set, 6 rare, 7 unique (0/empty: normal). |
| `RewardItemLevel` | Item level, 0/empty: the character's level. |
| `StatPoints`, `SkillPoints` | Points to spend. |

### Example

Columns in this order: `Id Giver ReqQuest ReqSubQuest ReqLevel Goal GoalMonster GoalSuperUnique GoalLevel GoalItem
GoalCount TakeItems Name TextOffer TextProgress TextDone ExpNormal ExpNightmare ExpHell GoldNormal GoldNightmare
GoldHell RewardItem RewardItemQuality RewardItemLevel StatPoints SkillPoints`, with `NPC` standing for the custom
NPC's `hcIdx`:

```
1  NPC  0  0  1  kill  19  0   2  .    10  0  sqFallen sqFallenOffer sqFallenProgress sqFallenDone   500  5000  20000  200  2000  10000  .    0  0  0  0
2  NPC  0  1  5  boss  0   0   3  .    1   0  sqBoss   sqBossOffer   sqBossProgress   sqBossDone   2000 20000 80000  1000 5000  20000  rin  4  0  0  1
3  NPC  1  2  8  item  0   0   0  hp1  5   1  sqPots   sqPotsOffer   sqPotsProgress   sqPotsDone   0    0     0      500  2000  5000   .    0  0  5  0
```

(`.` stands for an empty cell.) Row 1 asks for 10 Fallen (MonStats row 19) killed in the Blood Moor, row 2 for
Bishibosh (SuperUniques row 0) spawned in the Cold Plains, row 3 for five Minor Healing Potions, after the Den
of Evil.

## Saves

Progress is stored in an extra block at the very end of the `.d2s`, after the game's own sections, found from the
end of the file (`'SQ01'` magic): per difficulty a list of `{Id, state, counter}`. The header's file size and
checksum cover it. A save without the block has no subquest progress; a character without any progress gets no
block, so its save stays exactly as the game writes it. The game's own reader stops after its last section, so the
game reads these saves. Tools that expect the file to end there may not.

## How it works

D2Game hooks (`source/D2Game/src/MOD/SubQuests.cpp`, registered in `D2.Detours.patches/1.10f/D2Game.patch.cpp`).
Each runs the original first:

| Original (1.10f) | Added |
|------------------|-------|
| `QUESTS_ParseKill` 0x6FC940B0 | kill and boss goals |
| `QUESTS_ChangeLevel` 0x6FC94290 | level goals, quest boss spawns |
| `QUESTS_ItemPickedUp` 0x6FC94520 | item goal progress messages |
| `QUESTS_NPCActivate` 0x6FC944B0 | talk goals; the giver offers, reminds or takes back |
| `PLRSAVE2_CreateSaveFile` 0x6FC8D940 | writes the block |
| `PLRSAVE2_ProcessSaveFile` 0x6FC8EF20 | reads it into the player |

The table is in D2Common (`source/D2Common/src/DataTbls/SubQuestTbls.cpp`, exports 11315-11317).

## Not done yet

- Treasure-class rewards, and repeatable subquests.
- A list of the subquests under way (there is no UI besides the NPC's speech and the chat lines).
- Object goals (operate a shrine, a chest, ...).
