#pragma once

// Item appearance ("transmog"): an equipped item can be given the look of another base item while keeping
// every other property of its own. See doc/ItemAppearance.md.
//
// The look is stored on the item as the stat STAT_ITEM_APPEARANCE (a row appended to ItemStatCost.txt), whose
// value is the chosen look's items.txt row + 1 (0 means "own look", and a stat of value 0 is never saved or sent).
// Because it is an ordinary saved and sent stat:
//  - old saves keep loading, and saves with the stat load in a game without the row only if the row exists,
//  - other clients receive it with the item's bitstream (packets 0x9C/0x9D), as for every stat of an
//    identified item, so everybody sees the same look.
//
// Only the composit graphic is affected: the gfx token of helms, weapons and shields (items.txt alternategfx or
// code), and the six armour components of body armour. The colour (palette transform), the weapon class (COF and
// AnimData, so attack speed and action frames) and everything else still come from the item's own row. That is
// why a look must share the item's weapon class: DCC files only exist for the weapon classes an item can use.
//
// Everything here is inline and only uses D2Common exports that exist in the original 1.10f D2Common.dll, so it
// can be used from any D2MOO module, whether the caller runs patched into the original game or not.

#include <D2BasicTypes.h>
#include <Units/Units.h>
#include <DataTbls/ItemsTbls.h>
#include <D2DataTbls.h>
#include <D2Items.h>
#include <D2StatList.h>
#include <D2Composit.h>

// ItemStatCost.txt row of the stat. 1.10f ends with passive_mag_pierce (358); the row is appended after it.
constexpr int STAT_ITEM_APPEARANCE = 359;

// The base the gold cost is multiplied with: cost = item level * ITEMAPPEARANCE_GOLD_PER_ILVL.
constexpr int ITEMAPPEARANCE_GOLD_PER_ILVL = 100;
// Restoring the item's own look costs this fraction (in percent) of the regular cost.
constexpr int ITEMAPPEARANCE_RESTORE_COST_PERCENT = 50;

// Packet 0x38 (NPC item action) carries the request: nItemGUID is the item to change (on the cursor, as for the
// other anvil services), and nAction is ITEMAPPEARANCE_ACTION_FLAG | the items.txt row of the chosen look. The item's
// own row restores its own look. The vanilla actions are 0..3.
constexpr uint32_t ITEMAPPEARANCE_ACTION_FLAG = 0x80000000u;
constexpr uint32_t ITEMAPPEARANCE_ACTION_LOOK_MASK = 0x0000FFFFu;

inline bool ITEMAPPEARANCE_IsAction(uint32_t nAction)
{
	return (nAction & ITEMAPPEARANCE_ACTION_FLAG) != 0;
}

inline int ITEMAPPEARANCE_GetLookClassIdFromAction(uint32_t nAction)
{
	return (int)(nAction & ITEMAPPEARANCE_ACTION_LOOK_MASK);
}

inline uint32_t ITEMAPPEARANCE_MakeAction(int nLookClassId)
{
	return ITEMAPPEARANCE_ACTION_FLAG | ((uint32_t)nLookClassId & ITEMAPPEARANCE_ACTION_LOOK_MASK);
}

enum D2ItemAppearanceResult
{
	ITEMAPPEARANCE_OK = 0,
	ITEMAPPEARANCE_ERR_INVALID,          // not an item, or no items.txt row
	ITEMAPPEARANCE_ERR_UNIDENTIFIED,     // the item to change is not identified (its stats are not sent to clients)
	ITEMAPPEARANCE_ERR_NO_GRAPHIC,       // the item or look is not drawn on the character (rings, gloves, circlets...)
	ITEMAPPEARANCE_ERR_SLOT_MISMATCH,    // not drawn on the same composit layer
	ITEMAPPEARANCE_ERR_WEAPON_CLASS,     // weapons with a different weapon class (one- or two-handed)
	ITEMAPPEARANCE_ERR_CLASS_RESTRICTED, // the look is class specific and not of the player's class
	ITEMAPPEARANCE_ERR_SAME_LOOK,        // the item already looks like that: nothing would change
	ITEMAPPEARANCE_ERR_EXPANSION,        // an expansion item's look in a classic game (its graphics may not be there)
};

// Is this items.txt row drawn on the character as a composit layer?
inline bool ITEMAPPEARANCE_RecordHasGraphic(const D2ItemsTxt* pRecord)
{
	if (!pRecord || pRecord->nComponent >= NUM_COMPONENTS)
	{
		return false;
	}

	// Circlets have a head component but no head graphic (INVENTORY_GetItemSaveGfxInfo skips them too).
	return !ITEMS_CheckType(pRecord->wType[0], ITEMTYPE_CIRCLET);
}

// Can the row pLook be drawn in place of the row pItem? Shape only: no player or item state is looked at.
inline D2ItemAppearanceResult ITEMAPPEARANCE_CheckRecords(const D2ItemsTxt* pItem, const D2ItemsTxt* pLook)
{
	if (!pItem || !pLook)
	{
		return ITEMAPPEARANCE_ERR_INVALID;
	}

	if (!ITEMAPPEARANCE_RecordHasGraphic(pItem) || !ITEMAPPEARANCE_RecordHasGraphic(pLook))
	{
		return ITEMAPPEARANCE_ERR_NO_GRAPHIC;
	}

	if (pItem->nComponent != pLook->nComponent)
	{
		return ITEMAPPEARANCE_ERR_SLOT_MISMATCH;
	}

	const bool bItemIsWeapon = ITEMS_CheckType(pItem->wType[0], ITEMTYPE_WEAPON) != 0;
	const bool bLookIsWeapon = ITEMS_CheckType(pLook->wType[0], ITEMTYPE_WEAPON) != 0;
	if (bItemIsWeapon != bLookIsWeapon)
	{
		return ITEMAPPEARANCE_ERR_SLOT_MISMATCH;
	}

	// The weapon class picks the COF and the AnimData record; the look's DCCs must exist for it.
	if (bItemIsWeapon && (pItem->dwWeapClass != pLook->dwWeapClass || pItem->dwWeapClass2Hand != pLook->dwWeapClass2Hand))
	{
		return ITEMAPPEARANCE_ERR_WEAPON_CLASS;
	}

	return ITEMAPPEARANCE_OK;
}

// The look row stored on the item, or -1 for none.
inline int ITEMAPPEARANCE_GetStoredClassId(D2UnitStrc* pItem)
{
	if (!pItem || pItem->dwUnitType != UNIT_ITEM)
	{
		return -1;
	}

	D2StatListStrc* pStatList = STATLIST_GetStatListFromUnitStateOrFlag(pItem, 0, 0x40);
	if (!pStatList)
	{
		return -1;
	}

	const int nValue = STATLIST_GetStatValue(pStatList, STAT_ITEM_APPEARANCE, 0);
	return nValue > 0 ? nValue - 1 : -1;
}

// The items.txt row the item is drawn with: the stored look when it is still compatible (the txt files may have
// changed since it was stored), else the item's own.
inline int ITEMAPPEARANCE_GetDisplayClassId(D2UnitStrc* pItem)
{
	if (!pItem || pItem->dwUnitType != UNIT_ITEM)
	{
		return -1;
	}

	const int nLookClassId = ITEMAPPEARANCE_GetStoredClassId(pItem);
	if (nLookClassId >= 0 && nLookClassId != (int)pItem->dwClassId)
	{
		if (ITEMAPPEARANCE_CheckRecords(DATATBLS_GetItemsTxtRecord(pItem->dwClassId), DATATBLS_GetItemsTxtRecord(nLookClassId)) == ITEMAPPEARANCE_OK)
		{
			return nLookClassId;
		}
	}

	return pItem->dwClassId;
}

inline D2ItemsTxt* ITEMAPPEARANCE_GetDisplayRecord(D2UnitStrc* pItem)
{
	const int nClassId = ITEMAPPEARANCE_GetDisplayClassId(pItem);
	return nClassId >= 0 ? DATATBLS_GetItemsTxtRecord(nClassId) : nullptr;
}

// ITEMS_GetAltGfx for the displayed row.
inline uint32_t ITEMAPPEARANCE_GetDisplayAltGfx(D2UnitStrc* pItem)
{
	const D2ItemsTxt* pRecord = ITEMAPPEARANCE_GetDisplayRecord(pItem);
	if (!pRecord)
	{
		return 0;
	}

	return pRecord->dwAlternateGfx ? pRecord->dwAlternateGfx : pRecord->dwCode;
}

// The class a row is reserved for (item type's Class column), or PCLASS_INVALID.
inline int ITEMAPPEARANCE_GetRecordClass(const D2ItemsTxt* pRecord)
{
	if (!pRecord || pRecord->wType[0] < 0 || pRecord->wType[0] >= sgptDataTables->nItemTypesTxtRecordCount)
	{
		return PCLASS_INVALID;
	}

	const int nClass = sgptDataTables->pItemTypesTxt[pRecord->wType[0]].nClass;
	return nClass < NUMBER_OF_PLAYERCLASSES ? nClass : PCLASS_INVALID;
}

// Do two rows draw the same? Body armour is drawn from its six armour components, everything else from its gfx
// token (alternategfx, else code). Many exceptional and elite rows reuse the normal row's graphic.
inline bool ITEMAPPEARANCE_HaveSameGraphic(const D2ItemsTxt* pFirst, const D2ItemsTxt* pSecond)
{
	if (!pFirst || !pSecond)
	{
		return false;
	}

	if (pFirst == pSecond)
	{
		return true;
	}

	if (ITEMS_CheckType(pFirst->wType[0], ITEMTYPE_ARMOR))
	{
		for (int i = 0; i < 6; ++i)
		{
			if (pFirst->nArmorComp[i] != pSecond->nArmorComp[i])
			{
				return false;
			}
		}
		return true;
	}

	const uint32_t dwFirst = pFirst->dwAlternateGfx ? pFirst->dwAlternateGfx : pFirst->dwCode;
	const uint32_t dwSecond = pSecond->dwAlternateGfx ? pSecond->dwAlternateGfx : pSecond->dwCode;
	return dwFirst == dwSecond;
}

// May the row be offered as a look to a player of class nPlayerClass, in a game with or without the expansion?
// Shape only: whether it fits a given item is ITEMAPPEARANCE_CheckRecords.
inline D2ItemAppearanceResult ITEMAPPEARANCE_CheckLookRecord(const D2ItemsTxt* pLook, int nPlayerClass, bool bExpansion)
{
	if (!pLook)
	{
		return ITEMAPPEARANCE_ERR_INVALID;
	}

	if (!ITEMAPPEARANCE_RecordHasGraphic(pLook))
	{
		return ITEMAPPEARANCE_ERR_NO_GRAPHIC;
	}

	if (!bExpansion && pLook->wVersion >= 100)
	{
		return ITEMAPPEARANCE_ERR_EXPANSION;
	}

	// Class specific graphics (barbarian helms, druid pelts, paladin shields, shrunken heads, claws, orbs,
	// amazon weapons) may only exist in their own class' folder.
	const int nLookClass = ITEMAPPEARANCE_GetRecordClass(pLook);
	if (nLookClass != PCLASS_INVALID && nLookClass != nPlayerClass)
	{
		return ITEMAPPEARANCE_ERR_CLASS_RESTRICTED;
	}

	return ITEMAPPEARANCE_OK;
}

// Full check of a request: may pPlayer give pItem the look of the items.txt row nLookClassId? The item's own row
// restores its own look.
inline D2ItemAppearanceResult ITEMAPPEARANCE_CanApplyLook(D2UnitStrc* pPlayer, D2UnitStrc* pItem, int nLookClassId, bool bExpansion)
{
	if (!pPlayer || pPlayer->dwUnitType != UNIT_PLAYER || !pItem || pItem->dwUnitType != UNIT_ITEM)
	{
		return ITEMAPPEARANCE_ERR_INVALID;
	}

	const D2ItemsTxt* pItemRecord = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
	const D2ItemsTxt* pLookRecord = nLookClassId >= 0 ? DATATBLS_GetItemsTxtRecord(nLookClassId) : nullptr;
	if (!pItemRecord || !pLookRecord)
	{
		return ITEMAPPEARANCE_ERR_INVALID;
	}

	if (!ITEMS_CheckItemFlag(pItem, IFLAG_IDENTIFIED, __LINE__, __FILE__))
	{
		return ITEMAPPEARANCE_ERR_UNIDENTIFIED;
	}

	if (nLookClassId == (int)pItem->dwClassId)
	{
		if (!ITEMAPPEARANCE_RecordHasGraphic(pItemRecord))
		{
			return ITEMAPPEARANCE_ERR_NO_GRAPHIC;
		}
		return ITEMAPPEARANCE_GetStoredClassId(pItem) >= 0 ? ITEMAPPEARANCE_OK : ITEMAPPEARANCE_ERR_SAME_LOOK;
	}

	const D2ItemAppearanceResult nLook = ITEMAPPEARANCE_CheckLookRecord(pLookRecord, pPlayer->dwClassId, bExpansion);
	if (nLook != ITEMAPPEARANCE_OK)
	{
		return nLook;
	}

	const D2ItemAppearanceResult nShape = ITEMAPPEARANCE_CheckRecords(pItemRecord, pLookRecord);
	if (nShape != ITEMAPPEARANCE_OK)
	{
		return nShape;
	}

	if (ITEMAPPEARANCE_HaveSameGraphic(ITEMAPPEARANCE_GetDisplayRecord(pItem), pLookRecord))
	{
		return ITEMAPPEARANCE_ERR_SAME_LOOK;
	}

	return ITEMAPPEARANCE_OK;
}

// Gold asked for the request; bRestore for giving the item its own look back.
inline int ITEMAPPEARANCE_GetCost(D2UnitStrc* pItem, bool bRestore)
{
	int nLevel = pItem ? ITEMS_GetItemLevel(pItem) : 1;
	if (nLevel < 1)
	{
		nLevel = 1;
	}

	const int nCost = nLevel * ITEMAPPEARANCE_GOLD_PER_ILVL;
	return bRestore ? nCost * ITEMAPPEARANCE_RESTORE_COST_PERCENT / 100 : nCost;
}

// The value to store for a look row (0 removes the stat).
inline int ITEMAPPEARANCE_GetStatValueForClassId(D2UnitStrc* pItem, int nLookClassId)
{
	if (!pItem || nLookClassId < 0 || nLookClassId == (int)pItem->dwClassId)
	{
		return 0;
	}
	return nLookClassId + 1;
}
