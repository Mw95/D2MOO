# Custom NPCs

The original game decides what an NPC offers (trade, repair, heal) by its monster class, in code. This mod lets a
new `MonStats.txt` row trade, repair and heal like the town NPCs, configured in data. It is meant for NPCs standing
in a [safe zone](SafeZones.md), but works anywhere.

## Data

### MonStats.txt

Add a row for the NPC like the game's own town NPCs: `npc=1`, `interact=1`, `inTown=1`, an NPC AI (`Npc`), its
graphics and sounds in `MonStats2.txt`/`MonSounds.txt`. `interact=1` is required: the server only keeps a store and
interaction state for interacting monsters.

Then the three extra columns (read straight from the `.txt`, see `source/D2Common/src/DataTbls/CustomNpcTbls.cpp`).
**All three columns must exist** if one does:

| Column      | Meaning |
|-------------|---------|
| `NpcTrade`  | `hcIdx` of the town NPC whose store to copy: its item lists, its act (which caps item levels in Normal) and its restock rules. `0`/empty: no trade. |
| `NpcRepair` | `1`: repairs. The repair runs as the `NpcTrade` NPC when that one is a smith, else as Charsi, so the repair prices come from that NPC's `npc.txt` row. Repairing happens in the trade screen, so it needs `NpcTrade`. |
| `NpcHeal`   | `1`: heals life, mana and stamina and cures poison, freeze and curses when the player starts talking, exactly as Akara does. |

Optional gossip, four more columns (**all four must exist** if one does):

| Column | Meaning |
|--------|---------|
| `NpcGossip1` .. `NpcGossip4` | `.tbl` keys of what the NPC says when the player picks **Talk**, one per Talk, in turn. With at least one, the NPC's menu has a Talk row; after the line the menu comes back. An NPC with gossip and nothing else is a custom NPC too. |

Town NPC `hcIdx` values: Gheed 147, Akara 148, Charsi 154, Drognan 177, Fara 178, Elzix 199, Lysander 202,
Asheara 252, Hratli 253, Alkor 254, Ormus 255, Halbu 257, Jamella 405, Larzuk 511, Drehya 512, Malah 513,
Nihlathak 514. Smiths: Charsi, Fara, Hratli, Halbu, Larzuk.

### npc.txt

Add a row for the new NPC (its `npc` column is its MonStats `Id`). Buying and selling price with the NPC's own row,
as for every NPC.

## How it works

D2MOO runs the original `D2Game.dll` unless told otherwise, so these are detours of five original functions
(`source/D2Game/src/MOD/ModPatches.cpp`, registered in `D2.Detours.patches/1.10f/D2Game.patch.cpp`). Each runs the
original and adds to it:

| Original (1.10f) | Added |
|------------------|-------|
| `SUNITPROXY_InitializeNpcControl` 0x6FCCBA30 | Copies the `NpcTrade` NPC's store setup into the custom NPC's record. |
| `NPC_HandleDialogMessage` 0x6FCC9F40 | "Trade" with a custom NPC opens its store, as the original does for its traders. |
| `D2GAME_NPC_Repair_6FCC95B0` 0x6FCC95B0 | Runs with the NPC's class set to the repair NPC for the call. |
| `D2GAME_NPC_Heal_6FCCB220` 0x6FCCB220 | Runs with the NPC's class set to Akara for the call. |
| `SKILLITEM_pSpell02_CastPortal` 0x6FD02C80 | (safe zones) Town Portal inside a safe zone. |

The data comes from D2MOO D2Common exports 11313 `DATATBLS_GetCustomNpcRecord(int nMonStatsId)` (a
`D2CustomNpcTxt*`, NULL for other rows), 11314 `DATATBLS_ListCustomNpcs(int* pClassIds, int nMax)` and 11318
`DATATBLS_GetCustomNpcGossip(int nMonStatsId, int nIndex)` (a `.tbl` index, -1 for none), looked up by name at run
time (the loader binds `D2Common.dll` imports to the original DLL).

The client (D2Client) builds the NPC's menu from the same data and plays the gossip lines. Subquests the NPC gives
([SubQuests.md](SubQuests.md)) are spoken when the conversation starts, before the menu opens.

## Not done yet

- Gambling, identifying and hiring; an introduction line (the game's "Introduction" row) and per-class greetings.
