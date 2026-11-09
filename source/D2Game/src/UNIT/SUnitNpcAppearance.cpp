#include "UNIT/SUnitNpcAppearance.h"

#include <D2DataTbls.h>
#include <D2Inventory.h>
#include <D2ItemAppearance.h>
#include <D2Items.h>
#include <D2StatList.h>
#include <DataTbls/MonsterIds.h>

#include "GAME/Game.h"
#include "GAME/SCmd.h"
#include "ITEMS/ItemMode.h"
#include "ITEMS/Items.h"
#include "PLAYER/PlrTrade.h"
#include "UNIT/SUnit.h"
#include "UNIT/SUnitNpc.h"


void* gpfnOriginalNpcHandleDialogMessage = nullptr;


BOOL __fastcall NPC_OffersItemAppearance(int32_t nNpcClassId)
{
    switch (nNpcClassId)
    {
    case MONSTER_CHARSI:
    case MONSTER_FARA:
    case MONSTER_HRATLI:
    case MONSTER_HALBU:
    case MONSTER_LARZUK:
        return TRUE;
    default:
        return FALSE;
    }
}

// The way the other anvil services refuse: packet 0x58 action 7 closes the client's panel, and the item that was
// in the slot (on the cursor) is dropped at the player's feet.
static int32_t NPC_RefuseItemAppearance(D2GameStrc* pGame, D2UnitStrc* pPlayer, D2ClientStrc* pClient, int32_t nNpcGUID, int32_t nItemGUID)
{
    D2GSPacketSrv58 packet58 = {};
    packet58.nHeader = 0x58;
    packet58.nUnitId = nNpcGUID;
    packet58.nAction = 7;
    D2GAME_SendPacket0x58_6FC3F520(pClient, &packet58);
    ITEMMODE_DropCursorItem(pGame, pPlayer, nItemGUID);
    return 0;
}

// The base stat list (no state, flag 0x40) is the one ITEMS_SerializeItemComplete writes first.
static void NPC_SetItemAppearanceStat(D2UnitStrc* pItem, int32_t nValue)
{
    D2StatListStrc* pStatList = STATLIST_GetStatListFromUnitStateOrFlag(pItem, 0, 0x40);
    if (!pStatList)
    {
        if (!nValue)
        {
            return;
        }

        pStatList = STATLIST_AllocStatList(pItem->pMemoryPool, 0x40, 0, UNIT_ITEM, pItem->dwUnitId);
        D2COMMON_10475_PostStatToStatList(pItem, pStatList, 1);
    }

    STATLIST_SetStat(pStatList, STAT_ITEM_APPEARANCE, nValue, 0);
}

int32_t __fastcall NPC_HandleItemAppearanceRequest(D2GameStrc* pGame, D2UnitStrc* pPlayer, uint32_t nAction, int32_t nNpcGUID, int32_t nItemGUID)
{
    if (!pPlayer || pPlayer->dwUnitType != UNIT_PLAYER || !pPlayer->pInventory)
    {
        return 3;
    }

    D2UnitStrc* pNpc = SUNIT_GetServerUnit(pGame, UNIT_MONSTER, nNpcGUID);
    if (!pNpc || pNpc->dwUnitType != UNIT_MONSTER || !NPC_OffersItemAppearance(pNpc->dwClassId))
    {
        return 3;
    }

    // The item to change is in the anvil slot, which is the cursor on the server, as for Charsi, Larzuk and Anya.
    D2UnitStrc* pItem = INVENTORY_GetCursorItem(pPlayer->pInventory);
    if (!pItem || pItem->dwUnitId != nItemGUID)
    {
        return 3;
    }

    D2ClientStrc* pClient = SUNIT_GetClientFromPlayer(pPlayer, __FILE__, __LINE__);

    // The donor stays where it is; it must be the player's own: in the inventory, the stash or worn.
    const D2UnitGUID nDonorGUID = ITEMAPPEARANCE_GetDonorGUIDFromAction(nAction);
    D2UnitStrc* pDonor = pItem;
    if (nDonorGUID != pItem->dwUnitId)
    {
        pDonor = SUNIT_GetServerUnit(pGame, UNIT_ITEM, nDonorGUID);
        if (!pDonor || pDonor->dwUnitType != UNIT_ITEM || !INVENTORY_CompareWithItemsParentInventory(pPlayer->pInventory, pDonor))
        {
            return NPC_RefuseItemAppearance(pGame, pPlayer, pClient, nNpcGUID, nItemGUID);
        }
    }

    if (ITEMAPPEARANCE_CanApply(pPlayer, pItem, pDonor) != ITEMAPPEARANCE_OK)
    {
        return NPC_RefuseItemAppearance(pGame, pPlayer, pClient, nNpcGUID, nItemGUID);
    }

    const bool bRestore = pDonor == pItem;
    const int32_t nCost = ITEMAPPEARANCE_GetCost(pItem, bRestore);
    const int32_t nGold = STATLIST_UnitGetStatValue(pPlayer, STAT_GOLD, 0);
    const int32_t nGoldBank = STATLIST_UnitGetStatValue(pPlayer, STAT_GOLDBANK, 0);
    if (nGold + nGoldBank < nCost)
    {
        return NPC_RefuseItemAppearance(pGame, pPlayer, pClient, nNpcGUID, nItemGUID);
    }

    // As for Larzuk's sockets: a copy of the item gets the change, the original leaves the cursor, and the copy goes
    // to the inventory. The copy reaches this client and, once worn, every other one with its stats.
    D2UnitStrc* pOutput = ITEMS_Duplicate(pGame, pItem, pPlayer, 1);
    if (!pOutput)
    {
        return NPC_RefuseItemAppearance(pGame, pPlayer, pClient, nNpcGUID, nItemGUID);
    }

    NPC_SetItemAppearanceStat(pOutput, ITEMAPPEARANCE_GetStatValueForClassId(pOutput, bRestore ? -1 : (int32_t)pDonor->dwClassId));

    if (!D2GAME_RemoveItemIfOnCursor_6FC49760(pGame, pPlayer, pItem))
    {
        return NPC_RefuseItemAppearance(pGame, pPlayer, pClient, nNpcGUID, nItemGUID);
    }

    if (nGold < nCost)
    {
        PLRTRADE_AddGold(pPlayer, STAT_GOLD, -nGold);
        PLRTRADE_AddGold(pPlayer, STAT_GOLDBANK, nGold - nCost);
    }
    else
    {
        PLRTRADE_AddGold(pPlayer, STAT_GOLD, -nCost);
    }

    ITEMS_SetInvPage(pOutput, INVPAGE_INVENTORY);
    if (!D2GAME_PlaceItem_6FC44410(__FILE__, __LINE__, pGame, pPlayer, pOutput->dwUnitId, 0, 0, 1, 1, 0))
    {
        UNITS_ChangeAnimMode(pOutput, IMODE_ONGROUND);
        D2CoordStrc coords = {};
        UNITS_GetCoords(pPlayer, &coords);
        D2CoordStrc returnCoords = {};
        D2ActiveRoomStrc* pRoom = D2GAME_GetFreeSpaceEx_6FC4BF00(UNITS_GetRoom(pPlayer), &coords, &returnCoords, 1);
        D2GAME_DropItem_6FC52260(pGame, 0, pOutput, pRoom, returnCoords.nX, returnCoords.nY);
    }

    D2GSPacketSrv58 packet58 = {};
    packet58.nHeader = 0x58;
    packet58.nUnitId = nNpcGUID;
    packet58.nAction = 6;
    D2GAME_SendPacket0x58_6FC3F520(pClient, &packet58);
    return 0;
}

int32_t __fastcall NPC_HandleDialogMessageWithAppearance(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nType, int32_t nNpcGUID, int32_t nItemGUID)
{
    if (ITEMAPPEARANCE_IsAction((uint32_t)nType))
    {
        return NPC_HandleItemAppearanceRequest(pGame, pPlayer, (uint32_t)nType, nNpcGUID, nItemGUID);
    }

    if (gpfnOriginalNpcHandleDialogMessage)
    {
        using NpcHandleDialogMessageFn = int32_t(__fastcall*)(D2GameStrc*, D2UnitStrc*, int32_t, int32_t, int32_t);
        return reinterpret_cast<NpcHandleDialogMessageFn>(gpfnOriginalNpcHandleDialogMessage)(pGame, pPlayer, nType, nNpcGUID, nItemGUID);
    }

    return NPC_HandleDialogMessage(pGame, pPlayer, nType, nNpcGUID, nItemGUID);
}
