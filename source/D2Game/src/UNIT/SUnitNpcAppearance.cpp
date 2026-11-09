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
void* gpfnOriginalSendPacket0x9D = nullptr;
void* gpfnOriginalSendGroundToCursor = nullptr;


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

    // The look is an items.txt row the player chose from the client's list; the item's own row restores its look.
    const int32_t nLookClassId = ITEMAPPEARANCE_GetLookClassIdFromAction(nAction);
    if (ITEMAPPEARANCE_CanApplyLook(pPlayer, pItem, nLookClassId, pGame->bExpansion != 0) != ITEMAPPEARANCE_OK)
    {
        return NPC_RefuseItemAppearance(pGame, pPlayer, pClient, nNpcGUID, nItemGUID);
    }

    const bool bRestore = nLookClassId == (int32_t)pItem->dwClassId;
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

    NPC_SetItemAppearanceStat(pOutput, ITEMAPPEARANCE_GetStatValueForClassId(pOutput, bRestore ? -1 : nLookClassId));

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

// One chat packet per non-empty chunk of the collection, of a type the modified client takes for itself and shows
// nobody: "IA<chunk>:<8 hex digits>".
void __fastcall NPC_SendItemAppearanceCollection(D2GameStrc* pGame, D2UnitStrc* pPlayer)
{
    D2ClientStrc* pClient = pPlayer ? SUNIT_GetClientFromPlayer(pPlayer, __FILE__, __LINE__) : nullptr;
    if (!pClient)
    {
        return;
    }

    for (int32_t nChunk = 0; nChunk < ITEMAPPEARANCE_UNLOCK_CHUNKS; ++nChunk)
    {
        const uint32_t dwChunk = ITEMAPPEARANCE_GetUnlockChunk(pPlayer, nChunk);
        if (!dwChunk)
        {
            continue;
        }

        D2GSPacketSrv26 packet26 = {};
        packet26.nHeader = 0x26;
        packet26.nMessageType = ITEMAPPEARANCE_CHAT_MESSAGE_TYPE;
        packet26.nUnitType = UNIT_PLAYER;
        packet26.dwUnitGUID = pPlayer->dwUnitId;
        wsprintfA(packet26.szMessage, "IA%d:%08X", nChunk, dwChunk);
        D2GAME_PACKETS_SendPacket0x26_ServerMessage_6FC3DDF0(pClient, &packet26);
    }
}

// The character holds pItem: its base type joins the collection. Only for the owner's own client, so a broadcast of
// the same item action to the others does not count it again.
void __fastcall NPC_UnlockItemAppearanceFromPacket(D2ClientStrc* pClient, D2UnitStrc* pUnit, D2UnitStrc* pItem)
{
    if (!pClient || !pUnit || pUnit->dwUnitType != UNIT_PLAYER || !pItem || pItem->dwUnitType != UNIT_ITEM)
    {
        return;
    }

    if (SUNIT_GetClientFromPlayer(pUnit, __FILE__, __LINE__) == pClient)
    {
        ITEMAPPEARANCE_UnlockLook(pUnit, pItem->dwClassId);
    }
}

void __fastcall D2GAME_SendPacket0x9D_WithAppearanceUnlock(D2ClientStrc* pClient, D2UnitStrc* pUnit, D2UnitStrc* pItem, char nAction, DWORD dwFlag, int32_t bGamble)
{
    if (gpfnOriginalSendPacket0x9D)
    {
        using SendPacket0x9DFn = void(__fastcall*)(D2ClientStrc*, D2UnitStrc*, D2UnitStrc*, char, DWORD, int32_t);
        reinterpret_cast<SendPacket0x9DFn>(gpfnOriginalSendPacket0x9D)(pClient, pUnit, pItem, nAction, dwFlag, bGamble);
        if (!bGamble)
        {
            NPC_UnlockItemAppearanceFromPacket(pClient, pUnit, pItem);
        }
    }
    else
    {
        // The D2MOO function unlocks by itself.
        D2GAME_SendPacket0x9D_6FC3E6F0(pClient, pUnit, pItem, nAction, dwFlag, bGamble);
    }
}

void __fastcall D2GAME_SendGroundToCursor_WithAppearanceUnlock(D2ClientStrc* pClient, D2UnitStrc* pPlayer, D2UnitStrc* pItem, DWORD dwFlags)
{
    if (gpfnOriginalSendGroundToCursor)
    {
        using SendGroundToCursorFn = void(__fastcall*)(D2ClientStrc*, D2UnitStrc*, D2UnitStrc*, DWORD);
        reinterpret_cast<SendGroundToCursorFn>(gpfnOriginalSendGroundToCursor)(pClient, pPlayer, pItem, dwFlags);
        NPC_UnlockItemAppearanceFromPacket(pClient, pPlayer, pItem);
    }
    else
    {
        // The D2MOO function unlocks by itself.
        D2GAME_SendP0x9C_ItemAction_GroundToCursor_6FC3E870(pClient, pPlayer, pItem, dwFlags);
    }
}

int32_t __fastcall NPC_HandleDialogMessageWithAppearance(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nType, int32_t nNpcGUID, int32_t nItemGUID)
{
    if (ITEMAPPEARANCE_IsSyncAction((uint32_t)nType))
    {
        D2UnitStrc* pNpc = SUNIT_GetServerUnit(pGame, UNIT_MONSTER, nNpcGUID);
        if (!pPlayer || pPlayer->dwUnitType != UNIT_PLAYER || !pNpc || pNpc->dwUnitType != UNIT_MONSTER || !NPC_OffersItemAppearance(pNpc->dwClassId))
        {
            return 3;
        }

        NPC_SendItemAppearanceCollection(pGame, pPlayer);
        return 0;
    }

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
