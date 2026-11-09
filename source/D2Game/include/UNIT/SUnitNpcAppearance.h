#pragma once

#include <Units/Units.h>

struct D2GameStrc;
struct D2ClientStrc;

// Item appearance (transmog) at the blacksmiths, see doc/ItemAppearance.md and D2ItemAppearance.h.

// Filled by the patcher (D2Game.patch.cpp) when D2MOO runs patched into the original D2Game.dll: the original
// NPC_HandleDialogMessage. Null when the D2MOO D2Game runs on its own.
extern void* gpfnOriginalNpcHandleDialogMessage;
// The same for the two item packets that tell the owner it holds an item (see the unlock wrappers below).
extern void* gpfnOriginalSendPacket0x9D;
extern void* gpfnOriginalSendGroundToCursor;

// Is this NPC one of the blacksmiths that offer the service?
BOOL __fastcall NPC_OffersItemAppearance(int32_t nNpcClassId);

// Handles client packet 0x38 with an ITEMAPPEARANCE action: the item on the cursor (nItemGUID) gets the look of the
// items.txt row the action carries (its own row restores its own look). Answers with packet 0x58 action 6 (done) or 7 (refused). Return values are
// those of the packet handlers: 0 handled, 3 the request cannot come from a regular client.
int32_t __fastcall NPC_HandleItemAppearanceRequest(D2GameStrc* pGame, D2UnitStrc* pPlayer, uint32_t nAction, int32_t nNpcGUID, int32_t nItemGUID);

// NPC_HandleDialogMessage with the appearance request in front of it. Replaces the original
// NPC_HandleDialogMessage (D2Game.0x6FCC9F40) when patched in; every other request goes on to the original.
int32_t __fastcall NPC_HandleDialogMessageWithAppearance(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nType, int32_t nNpcGUID, int32_t nItemGUID);

// Sends the player's collection of looks (ITEMAPPEARANCE_ACTION_SYNC) as chat packets of ITEMAPPEARANCE_CHAT_MESSAGE_TYPE.
void __fastcall NPC_SendItemAppearanceCollection(D2GameStrc* pGame, D2UnitStrc* pPlayer);

// D2GAME_SendPacket0x9D_6FC3E6F0 and D2GAME_SendP0x9C_ItemAction_GroundToCursor_6FC3E870 with the collection in
// front: an item action sent to its owner's client means the character holds the item, so its base type is unlocked.
// That covers picking up, buying, gambling, rewards, cube and NPC outputs, trades and the items loaded with the save.
// They replace the originals when patched in.
// The character holds pItem (an item action sent to pUnit's own client): its base type joins the collection.
void __fastcall NPC_UnlockItemAppearanceFromPacket(D2ClientStrc* pClient, D2UnitStrc* pUnit, D2UnitStrc* pItem);
void __fastcall D2GAME_SendPacket0x9D_WithAppearanceUnlock(D2ClientStrc* pClient, D2UnitStrc* pUnit, D2UnitStrc* pItem, char nAction, DWORD dwFlag, int32_t bGamble);
void __fastcall D2GAME_SendGroundToCursor_WithAppearanceUnlock(D2ClientStrc* pClient, D2UnitStrc* pPlayer, D2UnitStrc* pItem, DWORD dwFlags);
