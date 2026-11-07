#include "MOD/ModPatches.h"

#include <D2BasicTypes.h>
#include <DataTbls/CustomNpcTbls.h>
#include <DataTbls/MonsterIds.h>
#include <Fog.h>
#include <Units/Monster.h>
#include <Units/Units.h>

#include "GAME/Game.h"
#include "UNIT/SUnitNpc.h"

#include <TlHelp32.h>
#include <cstring>
#include <cwchar>
#include <iterator>

// Mod (not part of the original game), see ModPatches.h.

void* gpfnOriginalCastPortal = nullptr;
void* gpfnOriginalInitializeNpcControl = nullptr;
void* gpfnOriginalHandleDialogMessage = nullptr;
void* gpfnOriginalRepair = nullptr;
void* gpfnOriginalHeal = nullptr;

static constexpr uint32_t MODPATCH_D2GAME_IMAGE_BASE = 0x6FC30000;

// Originals that are called but not hooked.
static constexpr uint32_t MODPATCH_ADDR_GETSERVERUNIT = 0x6FCBBB00;				// SUNIT_GetServerUnit
static constexpr uint32_t MODPATCH_ADDR_GETNPCRECORDFROMCLASSID = 0x6FCCB8A0;	// SUNITPROXY_GetNpcRecordFromClassId
static constexpr uint32_t MODPATCH_ADDR_GETINTERACTUNITCOUNT = 0x6FC619F0;		// MONSTERAI_GetInteractUnitCount
static constexpr uint32_t MODPATCH_ADDR_SETINTERACTTRADING = 0x6FC61AF0;		// D2GAME_NPCS_SetInteractTrading_6FC61AF0
static constexpr uint32_t MODPATCH_ADDR_CREATEVENDORCACHE = 0x6FCC74F0;			// D2GAME_STORES_CreateVendorCache_6FCC74F0

using CastPortalFn = int32_t(__fastcall*)(D2GameStrc*, D2UnitStrc*, D2UnitStrc*, D2UnitStrc*, int32_t, int32_t, int32_t);
using InitializeNpcControlFn = void(__fastcall*)(D2GameStrc*);
using HandleDialogMessageFn = int32_t(__fastcall*)(D2GameStrc*, D2UnitStrc*, int32_t, int32_t, int32_t);
using RepairFn = int32_t(__fastcall*)(D2GameStrc*, D2UnitStrc*, int32_t, int32_t, int32_t, int32_t);
using HealFn = void(__fastcall*)(D2GameStrc*, D2UnitStrc*, D2UnitStrc*);
using GetServerUnitFn = D2UnitStrc*(__fastcall*)(D2GameStrc*, int32_t, int32_t);
using GetNpcRecordFromClassIdFn = D2NpcRecordStrc*(__fastcall*)(D2GameStrc*, int32_t, int32_t*);
using GetInteractUnitCountFn = int32_t(__fastcall*)(D2MonsterInteractStrc*);
using SetInteractTradingFn = void(__fastcall*)(D2UnitStrc*, D2UnitStrc*);
using CreateVendorCacheFn = void(__fastcall*)(D2GameStrc*, D2UnitStrc*, D2UnitStrc*, int32_t, int32_t);

using SetSafeZoneTownOverrideFn = void(__stdcall*)(BOOL);
using GetCustomNpcRecordFn = const D2CustomNpcTxt*(__stdcall*)(int);
using ListCustomNpcsFn = int(__stdcall*)(int*, int);

// The first loaded module of that name for which pfnAccept answers true.
template<typename AcceptFn>
static HMODULE MODPATCH_FindModule(const wchar_t* szModuleName, AcceptFn pfnAccept)
{
	HMODULE hResult = nullptr;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return nullptr;
	}

	MODULEENTRY32W tModule = {};
	tModule.dwSize = sizeof(tModule);
	for (BOOL bFound = Module32FirstW(hSnapshot, &tModule); bFound && !hResult; bFound = Module32NextW(hSnapshot, &tModule))
	{
		if (!_wcsicmp(tModule.szModule, szModuleName) && pfnAccept(tModule.hModule))
		{
			hResult = tModule.hModule;
		}
	}

	CloseHandle(hSnapshot);
	return hResult;
}

// An export that only the D2MOO D2Common.dll has. The loader binds the name D2Common.dll to the original, so it is
// looked up among all loaded modules of that name.
static FARPROC MODPATCH_FindD2CommonExport(const char* szExportName)
{
	FARPROC pResult = nullptr;
	MODPATCH_FindModule(L"D2Common.dll", [&](HMODULE hModule)
	{
		pResult = GetProcAddress(hModule, szExportName);
		return pResult != nullptr;
	});
	return pResult;
}

// A function of the original D2Game.dll by its 1.10f address: the loaded D2Game.dll that is not this patch DLL.
template<typename T>
static T MODPATCH_GetOriginalD2GameFunction(uint32_t nAddress)
{
	static HMODULE hOriginalD2Game = nullptr;
	if (!hOriginalD2Game)
	{
		HMODULE hSelf = nullptr;
		GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCWSTR)&MODPATCH_FindD2CommonExport, &hSelf);
		hOriginalD2Game = MODPATCH_FindModule(L"D2Game.dll", [&](HMODULE hModule) { return hModule != hSelf; });
		D2_ASSERT(hOriginalD2Game);
	}

	return (T)((uintptr_t)hOriginalD2Game + (nAddress - MODPATCH_D2GAME_IMAGE_BASE));
}

static const D2CustomNpcTxt* MODPATCH_GetCustomNpc(D2UnitStrc* pUnit)
{
	static GetCustomNpcRecordFn pfnGetCustomNpcRecord = (GetCustomNpcRecordFn)MODPATCH_FindD2CommonExport("DATATBLS_GetCustomNpcRecord");
	if (!pfnGetCustomNpcRecord || !pUnit || pUnit->dwUnitType != UNIT_MONSTER)
	{
		return nullptr;
	}

	return pfnGetCustomNpcRecord(pUnit->dwClassId);
}

// The NPCs whose repair the original accepts (D2GAME_NPC_Repair_6FCC95B0).
static bool MODPATCH_IsRepairNpc(int32_t nClassId)
{
	switch (nClassId)
	{
	case MONSTER_CHARSI:
	case MONSTER_FARA:
	case MONSTER_HRATLI:
	case MONSTER_HALBU:
	case MONSTER_LARZUK:
		return true;
	default:
		return false;
	}
}

// Runs pfnCall with pNpc's class temporarily set to nClassId, for originals that decide by the NPC's class alone.
template<typename CallFn>
static auto MODPATCH_CallAsClass(D2UnitStrc* pNpc, int32_t nClassId, CallFn pfnCall)
{
	const int32_t nOriginalClassId = pNpc->dwClassId;
	pNpc->dwClassId = nClassId;
	auto result = pfnCall();
	pNpc->dwClassId = nOriginalClassId;
	return result;
}

//----------------------------------------------------------------------------------------------------------------------
// Safe zones
//----------------------------------------------------------------------------------------------------------------------

// The original refuses to open a portal in town, and a safe zone is town. It runs here with D2Common's safe zone town
// override held, so for that call a safe zone is not town; real towns still refuse.
int32_t __fastcall MODPATCH_CastPortal(D2GameStrc* pGame, D2UnitStrc* pUnit, D2UnitStrc* pItem, D2UnitStrc* pTarget, int32_t nX, int32_t nY, int32_t nSkillId)
{
	static SetSafeZoneTownOverrideFn pfnSetOverride = (SetSafeZoneTownOverrideFn)MODPATCH_FindD2CommonExport("DUNGEON_SetSafeZoneTownOverride");

	CastPortalFn pfnOriginal = (CastPortalFn)gpfnOriginalCastPortal;
	if (!pfnSetOverride)
	{
		return pfnOriginal(pGame, pUnit, pItem, pTarget, nX, nY, nSkillId);
	}

	pfnSetOverride(TRUE);
	const int32_t nResult = pfnOriginal(pGame, pUnit, pItem, pTarget, nX, nY, nSkillId);
	pfnSetOverride(FALSE);
	return nResult;
}

//----------------------------------------------------------------------------------------------------------------------
// Custom NPCs
//----------------------------------------------------------------------------------------------------------------------

// The original builds an NPC record for every MonStats row with interact=1, but sets up a store only for the town NPCs
// it knows. A custom NPC with NpcTrade gets a copy of that NPC's store setup: act, restock rules and item lists.
void __fastcall MODPATCH_InitializeNpcControl(D2GameStrc* pGame)
{
	((InitializeNpcControlFn)gpfnOriginalInitializeNpcControl)(pGame);

	static ListCustomNpcsFn pfnListCustomNpcs = (ListCustomNpcsFn)MODPATCH_FindD2CommonExport("DATATBLS_ListCustomNpcs");
	static GetCustomNpcRecordFn pfnGetCustomNpcRecord = (GetCustomNpcRecordFn)MODPATCH_FindD2CommonExport("DATATBLS_GetCustomNpcRecord");
	if (!pfnListCustomNpcs || !pfnGetCustomNpcRecord)
	{
		return;
	}

	GetNpcRecordFromClassIdFn pfnGetNpcRecord = MODPATCH_GetOriginalD2GameFunction<GetNpcRecordFromClassIdFn>(MODPATCH_ADDR_GETNPCRECORDFROMCLASSID);

	int pClassIds[64] = {};
	const int nCount = pfnListCustomNpcs(pClassIds, (int)std::size(pClassIds));
	for (int i = 0; i < nCount && i < (int)std::size(pClassIds); ++i)
	{
		const D2CustomNpcTxt* pCustomNpc = pfnGetCustomNpcRecord(pClassIds[i]);
		if (!pCustomNpc || pCustomNpc->nTradeAs <= 0)
		{
			continue;
		}

		int32_t nIndex = 0;
		D2NpcRecordStrc* pRecord = pfnGetNpcRecord(pGame, pClassIds[i], &nIndex);
		D2NpcRecordStrc* pTemplate = pfnGetNpcRecord(pGame, pCustomNpc->nTradeAs, &nIndex);
		if (!pRecord || !pTemplate || pRecord == pTemplate || !pTemplate->npcTrade.bTrader)
		{
			FOG_Trace("Custom NPC %d: no NPC record (interact=1?) or NpcTrade %d is not a trader", pClassIds[i], pCustomNpc->nTradeAs);
			continue;
		}

		D2NpcTradeStrc* pTrade = &pRecord->npcTrade;
		const D2NpcTradeStrc* pTemplateTrade = &pTemplate->npcTrade;
		pTrade->nAct = pTemplateTrade->nAct;
		pTrade->bTrader = pTemplateTrade->bTrader;
		pTrade->bLevelRefresh = pTemplateTrade->bLevelRefresh;
		pTrade->bInited = pTemplateTrade->bInited;
		pTrade->bForceVendor = pTemplateTrade->bForceVendor;
		pTrade->bRefreshInventory = 0;

		// Own copies: SUNITPROXY_FreeNpcControl frees every record's lists from the game's pool.
		const D2UnitProxyStrc* pTemplateProxy = &pTemplateTrade->pProxy;
		D2UnitProxyStrc* pProxy = &pTrade->pProxy;
		if (!pProxy->pItemCache && !pProxy->pPermCache)
		{
			pProxy->nItems = pTemplateProxy->nItems;
			if (pProxy->nItems > 0)
			{
				pProxy->pItemCache = (D2ItemCacheStrc*)D2_ALLOC_POOL(pGame->pMemoryPool, sizeof(D2ItemCacheStrc) * pProxy->nItems);
				memcpy(pProxy->pItemCache, pTemplateProxy->pItemCache, sizeof(D2ItemCacheStrc) * pProxy->nItems);
			}

			pProxy->nPerms = pTemplateProxy->nPerms;
			if (pProxy->nPerms > 0)
			{
				pProxy->pPermCache = (uint32_t*)D2_ALLOC_POOL(pGame->pMemoryPool, sizeof(uint32_t) * pProxy->nPerms);
				memcpy(pProxy->pPermCache, pTemplateProxy->pPermCache, sizeof(uint32_t) * pProxy->nPerms);
			}
		}
	}
}

// "Trade" (nType 1) with a custom NPC opens its store the way the original does for its own traders.
int32_t __fastcall MODPATCH_HandleDialogMessage(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nType, int32_t nNpcGUID, int32_t nItemGUID)
{
	if (nType == 1 && pPlayer)
	{
		D2UnitStrc* pNpc = MODPATCH_GetOriginalD2GameFunction<GetServerUnitFn>(MODPATCH_ADDR_GETSERVERUNIT)(pGame, UNIT_MONSTER, nNpcGUID);
		const D2CustomNpcTxt* pCustomNpc = MODPATCH_GetCustomNpc(pNpc);
		if (pCustomNpc && pCustomNpc->nTradeAs > 0 && pNpc->pMonsterData && pNpc->pMonsterData->pMonInteract)
		{
			const int32_t bRefreshInventory = MODPATCH_GetOriginalD2GameFunction<GetInteractUnitCountFn>(MODPATCH_ADDR_GETINTERACTUNITCOUNT)(pNpc->pMonsterData->pMonInteract) == 1;
			MODPATCH_GetOriginalD2GameFunction<SetInteractTradingFn>(MODPATCH_ADDR_SETINTERACTTRADING)(pNpc, pPlayer);
			MODPATCH_GetOriginalD2GameFunction<CreateVendorCacheFn>(MODPATCH_ADDR_CREATEVENDORCACHE)(pGame, pPlayer, pNpc, bRefreshInventory, 0);
			return 0;
		}
	}

	return ((HandleDialogMessageFn)gpfnOriginalHandleDialogMessage)(pGame, pPlayer, nType, nNpcGUID, nItemGUID);
}

// The original repairs only for its five smiths, by class. A custom NPC with NpcRepair runs it as its NpcTrade NPC when
// that one is a smith, else as Charsi; the prices are that NPC's npc.txt row.
int32_t __fastcall MODPATCH_Repair(D2GameStrc* pGame, D2UnitStrc* pUnit, int32_t nNpcGUID, int32_t nItemGUID, int32_t nUnused, int32_t nRepairFlags)
{
	RepairFn pfnOriginal = (RepairFn)gpfnOriginalRepair;

	D2UnitStrc* pNpc = MODPATCH_GetOriginalD2GameFunction<GetServerUnitFn>(MODPATCH_ADDR_GETSERVERUNIT)(pGame, UNIT_MONSTER, nNpcGUID);
	const D2CustomNpcTxt* pCustomNpc = MODPATCH_GetCustomNpc(pNpc);
	if (!pCustomNpc || !pCustomNpc->dwRepair)
	{
		return pfnOriginal(pGame, pUnit, nNpcGUID, nItemGUID, nUnused, nRepairFlags);
	}

	const int32_t nRepairAs = MODPATCH_IsRepairNpc(pCustomNpc->nTradeAs) ? pCustomNpc->nTradeAs : MONSTER_CHARSI;
	return MODPATCH_CallAsClass(pNpc, nRepairAs, [&]() { return pfnOriginal(pGame, pUnit, nNpcGUID, nItemGUID, nUnused, nRepairFlags); });
}

// The original heals on talk only for its healers, by class. A custom NPC with NpcHeal heals as Akara does.
void __fastcall MODPATCH_Heal(D2GameStrc* pGame, D2UnitStrc* pUnit, D2UnitStrc* pNpc)
{
	HealFn pfnOriginal = (HealFn)gpfnOriginalHeal;

	const D2CustomNpcTxt* pCustomNpc = MODPATCH_GetCustomNpc(pNpc);
	if (!pCustomNpc || !pCustomNpc->dwHeal)
	{
		pfnOriginal(pGame, pUnit, pNpc);
		return;
	}

	MODPATCH_CallAsClass(pNpc, MONSTER_AKARA, [&]() { pfnOriginal(pGame, pUnit, pNpc); return 0; });
}
