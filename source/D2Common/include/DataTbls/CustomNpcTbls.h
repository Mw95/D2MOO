#pragma once

#include "D2CommonDefinitions.h"

// Mod: new NPC classes that trade, repair and heal like the game's own town NPCs (not part of the original game).
//
// The original game picks what an NPC offers by its monster class, in code. These extra MonStats.txt columns (read
// from the .txt, see DataTbls/ExtraTxtColumns.h) let a new MonStats row (with npc=1, interact=1, inTown=1) say it:
//
//   NpcTrade   MonStats row (hcIdx) of the town NPC whose store to copy (its items, act and restock rules),
//              e.g. 154 for Charsi. 0 or empty: no trade.
//   NpcRepair  1: repairs items, at the prices of the npc.txt row of the NPC named by NpcTrade (Charsi when none).
//   NpcHeal    1: heals life, mana and stamina and cures poison/curses on talk, like Akara.
//
// All three columns must exist when any does. A row with all three empty or 0 (and no gossip) is a regular monster.
//
// Optional, read separately (all four must exist when one does):
//   NpcGossip1 .. NpcGossip4   .tbl keys of what the NPC says when the player picks Talk, in turn.

#pragma pack(1)

struct D2CustomNpcTxt
{
	int32_t nTradeAs;						//0x00 MonStats row whose store is copied, 0 for none
	uint32_t dwRepair;						//0x04
	uint32_t dwHeal;						//0x08
};

#pragma pack()

// The record of a MonStats row that is a custom NPC, nullptr otherwise. Loads the columns on first use. Thread safe.
const D2CustomNpcTxt* __fastcall DATATBLS_GetCustomNpcTxtRecord(int nMonStatsId);

// The .tbl index of the NPC's gossip line nIndex (0-3), -1 when it has none.
int __fastcall DATATBLS_GetCustomNpcGossipTblIndex(int nMonStatsId, int nIndex);

// Fills pClassIds with up to nMax MonStats rows that are custom NPCs and answers how many there are in all.
int __fastcall DATATBLS_GetCustomNpcClassIds(int* pClassIds, int nMax);

// Exports (D2MOO D2Common.dll only, look them up by name; see doc/CustomNpcs.md).
//D2Common.#11313
D2COMMON_DLL_DECL const D2CustomNpcTxt* __stdcall DATATBLS_GetCustomNpcRecord(int nMonStatsId);
//D2Common.#11314
D2COMMON_DLL_DECL int __stdcall DATATBLS_ListCustomNpcs(int* pClassIds, int nMax);
// The .tbl index of gossip line nIndex (0-3) of a custom NPC, -1 when there is none.
//D2Common.#11318
D2COMMON_DLL_DECL int __stdcall DATATBLS_GetCustomNpcGossip(int nMonStatsId, int nIndex);
