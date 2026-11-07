#pragma once

#include <D2BasicTypes.h>

// Mod (not part of the original game): detours of original D2Game.dll functions for safe zones and custom NPCs.
//
// D2MOO runs the original D2Game by default (D2Game.patch.cpp replaces no ordinal). The mod hooks a few original
// functions by address instead (see D2.Detours.patches/1.10f/D2Game.patch.cpp): each wrapper below runs the original
// (through the matching pointer, which D2.Detours fills) and adds the mod's behaviour around it, so everything else
// stays the original code. The data comes from exports only the D2MOO D2Common.dll has, looked up at run time.
//
// 1.10f addresses (image base 0x6FC30000).

struct D2GameStrc;
struct D2UnitStrc;

constexpr uint32_t MODPATCH_ADDR_CASTPORTAL = 0x6FD02C80;				// SKILLITEM_pSpell02_CastPortal
constexpr uint32_t MODPATCH_ADDR_INITIALIZENPCCONTROL = 0x6FCCBA30;		// SUNITPROXY_InitializeNpcControl
constexpr uint32_t MODPATCH_ADDR_HANDLEDIALOGMESSAGE = 0x6FCC9F40;		// NPC_HandleDialogMessage
constexpr uint32_t MODPATCH_ADDR_REPAIR = 0x6FCC95B0;					// D2GAME_NPC_Repair_6FCC95B0
constexpr uint32_t MODPATCH_ADDR_HEAL = 0x6FCCB220;						// D2GAME_NPC_Heal_6FCCB220

// Safe zones: Town Portal can be cast inside a safe zone (see doc/SafeZones.md).
int32_t __fastcall MODPATCH_CastPortal(D2GameStrc* pGame, D2UnitStrc* pUnit, D2UnitStrc* pItem, D2UnitStrc* pTarget, int32_t nX, int32_t nY, int32_t nSkillId);
extern void* gpfnOriginalCastPortal;

// Custom NPCs (see doc/CustomNpcs.md).
void __fastcall MODPATCH_InitializeNpcControl(D2GameStrc* pGame);
extern void* gpfnOriginalInitializeNpcControl;

int32_t __fastcall MODPATCH_HandleDialogMessage(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nType, int32_t nNpcGUID, int32_t nItemGUID);
extern void* gpfnOriginalHandleDialogMessage;

int32_t __fastcall MODPATCH_Repair(D2GameStrc* pGame, D2UnitStrc* pUnit, int32_t nNpcGUID, int32_t nItemGUID, int32_t nUnused, int32_t nRepairFlags);
extern void* gpfnOriginalRepair;

void __fastcall MODPATCH_Heal(D2GameStrc* pGame, D2UnitStrc* pUnit, D2UnitStrc* pNpc);
extern void* gpfnOriginalHeal;
