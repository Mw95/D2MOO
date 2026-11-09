#pragma once

// Item appearance ("transmog"): an equipped item can be given the look of another base item while keeping
// every other property of its own. See doc/ItemAppearance.md.
//
// The look is stored on the item as the stat STAT_ITEM_APPEARANCE (a row appended to ItemStatCost.txt), whose
// value is the donor's items.txt row + 1 (0 means "own look", and a stat of value 0 is never saved or sent).
// Because it is an ordinary saved and sent stat:
//  - old saves keep loading, and saves with the stat load in a game without the row only if the row exists,
//  - other clients receive it with the item's bitstream (packets 0x9C/0x9D), as for every stat of an
//    identified item, so everybody sees the same look.
//
// Only the composit graphic is affected: the gfx token of helms, weapons and shields (items.txt alternategfx or
// code), and the six armour components of body armour. The colour (palette transform), the weapon class (COF and
// AnimData, so attack speed and action frames) and everything else still come from the item's own row. That is
// why a donor must share the item's weapon class: DCC files only exist for the weapon classes an item can use.
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
// other anvil services), and nAction is ITEMAPPEARANCE_ACTION_FLAG | the donor's GUID. A donor GUID equal to the
// item's own GUID restores the item's own look. The vanilla actions are 0..3, and item GUIDs never reach bit 31.
constexpr uint32_t ITEMAPPEARANCE_ACTION_FLAG = 0x80000000u;
constexpr uint32_t ITEMAPPEARANCE_ACTION_GUID_MASK = 0x7FFFFFFFu;

inline bool ITEMAPPEARANCE_IsAction(uint32_t nAction)
{
	return (nAction & ITEMAPPEARANCE_ACTION_FLAG) != 0;
}

inline D2UnitGUID ITEMAPPEARANCE_GetDonorGUIDFromAction(uint32_t nAction)
{
	return (D2UnitGUID)(nAction & ITEMAPPEARANCE_ACTION_GUID_MASK);
}

inline uint32_t ITEMAPPEARANCE_MakeAction(D2UnitGUID nDonorGUID)
{
	return ITEMAPPEARANCE_ACTION_FLAG | ((uint32_t)nDonorGUID & ITEMAPPEARANCE_ACTION_GUID_MASK);
}

enum D2ItemAppearanceResult
{
	ITEMAPPEARANCE_OK = 0,
	ITEMAPPEARANCE_ERR_INVALID,          // not an item, or no items.txt row
	ITEMAPPEARANCE_ERR_UNIDENTIFIED,     // the item to change is not identified (its stats are not sent to clients)
	ITEMAPPEARANCE_ERR_NO_GRAPHIC,       // the item or donor is not drawn on the character (rings, gloves, circlets...)
	ITEMAPPEARANCE_ERR_SLOT_MISMATCH,    // not drawn on the same composit layer
	ITEMAPPEARANCE_ERR_WEAPON_CLASS,     // weapons with a different weapon class (one- or two-handed)
	ITEMAPPEARANCE_ERR_CLASS_RESTRICTED, // the donor is class specific and not of the player's class
	ITEMAPPEARANCE_ERR_SAME_LOOK,        // the donor already looks like the item: nothing would change
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

// Can the row pDonor be drawn in place of the row pItem? Shape only: no player or item state is looked at.
inline D2ItemAppearanceResult ITEMAPPEARANCE_CheckRecords(const D2ItemsTxt* pItem, const D2ItemsTxt* pDonor)
{
	if (!pItem || !pDonor)
	{
		return ITEMAPPEARANCE_ERR_INVALID;
	}

	if (!ITEMAPPEARANCE_RecordHasGraphic(pItem) || !ITEMAPPEARANCE_RecordHasGraphic(pDonor))
	{
		return ITEMAPPEARANCE_ERR_NO_GRAPHIC;
	}

	if (pItem->nComponent != pDonor->nComponent)
	{
		return ITEMAPPEARANCE_ERR_SLOT_MISMATCH;
	}

	const bool bItemIsWeapon = ITEMS_CheckType(pItem->wType[0], ITEMTYPE_WEAPON) != 0;
	const bool bDonorIsWeapon = ITEMS_CheckType(pDonor->wType[0], ITEMTYPE_WEAPON) != 0;
	if (bItemIsWeapon != bDonorIsWeapon)
	{
		return ITEMAPPEARANCE_ERR_SLOT_MISMATCH;
	}

	// The weapon class picks the COF and the AnimData record; the donor's DCCs must exist for it.
	if (bItemIsWeapon && (pItem->dwWeapClass != pDonor->dwWeapClass || pItem->dwWeapClass2Hand != pDonor->dwWeapClass2Hand))
	{
		return ITEMAPPEARANCE_ERR_WEAPON_CLASS;
	}

	return ITEMAPPEARANCE_OK;
}

// The donor row stored on the item, or -1 for none.
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

// The items.txt row the item is drawn with: the stored donor when it is still compatible (the txt files may have
// changed since it was stored), else the item's own.
inline int ITEMAPPEARANCE_GetDisplayClassId(D2UnitStrc* pItem)
{
	if (!pItem || pItem->dwUnitType != UNIT_ITEM)
	{
		return -1;
	}

	const int nDonorClassId = ITEMAPPEARANCE_GetStoredClassId(pItem);
	if (nDonorClassId >= 0 && nDonorClassId != (int)pItem->dwClassId)
	{
		if (ITEMAPPEARANCE_CheckRecords(DATATBLS_GetItemsTxtRecord(pItem->dwClassId), DATATBLS_GetItemsTxtRecord(nDonorClassId)) == ITEMAPPEARANCE_OK)
		{
			return nDonorClassId;
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

// Full check of a request: may pPlayer give pItem the look of pDonor? pDonor == pItem restores the own look.
inline D2ItemAppearanceResult ITEMAPPEARANCE_CanApply(D2UnitStrc* pPlayer, D2UnitStrc* pItem, D2UnitStrc* pDonor)
{
	if (!pItem || pItem->dwUnitType != UNIT_ITEM || !pDonor || pDonor->dwUnitType != UNIT_ITEM)
	{
		return ITEMAPPEARANCE_ERR_INVALID;
	}

	const D2ItemsTxt* pItemRecord = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
	const D2ItemsTxt* pDonorRecord = DATATBLS_GetItemsTxtRecord(pDonor->dwClassId);
	if (!pItemRecord || !pDonorRecord)
	{
		return ITEMAPPEARANCE_ERR_INVALID;
	}

	if (!ITEMS_CheckItemFlag(pItem, IFLAG_IDENTIFIED, __LINE__, __FILE__))
	{
		return ITEMAPPEARANCE_ERR_UNIDENTIFIED;
	}

	if (pItem == pDonor)
	{
		if (!ITEMAPPEARANCE_RecordHasGraphic(pItemRecord))
		{
			return ITEMAPPEARANCE_ERR_NO_GRAPHIC;
		}
		return ITEMAPPEARANCE_GetStoredClassId(pItem) >= 0 ? ITEMAPPEARANCE_OK : ITEMAPPEARANCE_ERR_SAME_LOOK;
	}

	const D2ItemAppearanceResult nShape = ITEMAPPEARANCE_CheckRecords(pItemRecord, pDonorRecord);
	if (nShape != ITEMAPPEARANCE_OK)
	{
		return nShape;
	}

	// Class specific graphics (barbarian helms, druid pelts, paladin shields, shrunken heads, claws, orbs,
	// amazon weapons) may only exist in their own class' folder.
	const int nDonorClass = ITEMS_GetClassOfClassSpecificItem(pDonor);
	if (nDonorClass != PCLASS_INVALID && (!pPlayer || pPlayer->dwUnitType != UNIT_PLAYER || nDonorClass != (int)pPlayer->dwClassId))
	{
		return ITEMAPPEARANCE_ERR_CLASS_RESTRICTED;
	}

	if (ITEMAPPEARANCE_GetDisplayClassId(pItem) == (int)pDonor->dwClassId)
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

// The value to store for a donor row (0 removes the stat).
inline int ITEMAPPEARANCE_GetStatValueForClassId(D2UnitStrc* pItem, int nDonorClassId)
{
	if (!pItem || nDonorClassId < 0 || nDonorClassId == (int)pItem->dwClassId)
	{
		return 0;
	}
	return nDonorClassId + 1;
}
