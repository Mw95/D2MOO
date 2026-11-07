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
struct D2ClientStrc;
struct D2ActiveRoomStrc;
struct D2TextHeaderStrc;

// A function of the original D2Game.dll by its 1.10f address (the loaded D2Game.dll that is not this patch DLL).
void* __fastcall MODPATCH_GetOriginalD2GameAddress(uint32_t nAddress);
// An export that only the D2MOO D2Common.dll has, looked up among the loaded modules named D2Common.dll; nullptr without it.
FARPROC __fastcall MODPATCH_FindD2CommonExport(const char* szExportName);

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

// Subquests (see doc/SubQuests.md, source/D2Game/src/MOD/SubQuests.cpp).
constexpr uint32_t MODPATCH_ADDR_PARSEKILL = 0x6FC940B0;				// QUESTS_ParseKill
constexpr uint32_t MODPATCH_ADDR_CHANGELEVEL = 0x6FC94290;				// QUESTS_ChangeLevel
constexpr uint32_t MODPATCH_ADDR_ITEMPICKEDUP = 0x6FC94520;				// QUESTS_ItemPickedUp
constexpr uint32_t MODPATCH_ADDR_NPCACTIVATE = 0x6FC944B0;				// QUESTS_NPCActivate
constexpr uint32_t MODPATCH_ADDR_CREATESAVEFILE = 0x6FC8D940;			// PLRSAVE2_CreateSaveFile
constexpr uint32_t MODPATCH_ADDR_PROCESSSAVEFILE = 0x6FC8EF20;			// PLRSAVE2_ProcessSaveFile

void __fastcall MODPATCH_ParseKill(D2GameStrc* pGame, D2UnitStrc* pDefender, D2UnitStrc* pAttacker);
extern void* gpfnOriginalParseKill;

void __fastcall MODPATCH_ChangeLevel(D2GameStrc* pGame, int32_t nOldLevelId, int32_t nTargetLevelId, D2UnitStrc* pUnit);
extern void* gpfnOriginalChangeLevel;

void __fastcall MODPATCH_ItemPickedUp(D2GameStrc* pGame, D2UnitStrc* pPlayer, D2UnitStrc* pItem);
extern void* gpfnOriginalItemPickedUp;

void __fastcall MODPATCH_NPCActivate(D2ClientStrc* pClient, D2UnitStrc* pPlayer, D2UnitStrc* pTarget, D2TextHeaderStrc* pTextControl);
extern void* gpfnOriginalNPCActivate;

int32_t __fastcall MODPATCH_CreateSaveFile(D2GameStrc* pGame, D2UnitStrc* pPlayer, uint8_t* pData, uint32_t* pSize, uint32_t nMaxSize, int32_t bUseTradeInventory, int32_t nUnused);
extern void* gpfnOriginalCreateSaveFile;

int32_t __fastcall MODPATCH_ProcessSaveFile(D2GameStrc* pGame, D2ClientStrc* pClient, uint8_t* pSaveFile, uint32_t nSize, D2UnitStrc** ppPlayer, D2ActiveRoomStrc* pRoomArg, int32_t nXArg, int32_t nYArg);
extern void* gpfnOriginalProcessSaveFile;

constexpr uint32_t MODPATCH_ADDR_OPERATEHANDLER = 0x6FC789C0;			// OBJECTS_OperateHandler
constexpr uint32_t MODPATCH_ADDR_HANDLECHATMESSAGE = 0x6FC84950;		// D2GAME_PACKETCALLBACK_Rcv0x15_HandleChatMessage_6FC84950

int32_t __fastcall MODPATCH_OperateHandler(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nObjectType, int32_t nObjectGUID, int32_t* pResult);
extern void* gpfnOriginalOperateHandler;

int32_t __fastcall MODPATCH_HandleChatMessage(D2GameStrc* pGame, D2UnitStrc* pUnit, void* pPacket, int32_t nSize);
extern void* gpfnOriginalHandleChatMessage;
