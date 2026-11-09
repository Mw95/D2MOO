#pragma once

#include <Units/Units.h>

struct D2GameStrc;

// Item appearance (transmog) at the blacksmiths, see doc/ItemAppearance.md and D2ItemAppearance.h.

// Filled by the patcher (D2Game.patch.cpp) when D2MOO runs patched into the original D2Game.dll: the original
// NPC_HandleDialogMessage. Null when the D2MOO D2Game runs on its own.
extern void* gpfnOriginalNpcHandleDialogMessage;

// Is this NPC one of the blacksmiths that offer the service?
BOOL __fastcall NPC_OffersItemAppearance(int32_t nNpcClassId);

// Handles client packet 0x38 with an ITEMAPPEARANCE action: the item on the cursor (nItemGUID) gets the look of the
// items.txt row the action carries (its own row restores its own look). Answers with packet 0x58 action 6 (done) or 7 (refused). Return values are
// those of the packet handlers: 0 handled, 3 the request cannot come from a regular client.
int32_t __fastcall NPC_HandleItemAppearanceRequest(D2GameStrc* pGame, D2UnitStrc* pPlayer, uint32_t nAction, int32_t nNpcGUID, int32_t nItemGUID);

// NPC_HandleDialogMessage with the appearance request in front of it. Replaces the original
// NPC_HandleDialogMessage (D2Game.0x6FCC9F40) when patched in; every other request goes on to the original.
int32_t __fastcall NPC_HandleDialogMessageWithAppearance(D2GameStrc* pGame, D2UnitStrc* pPlayer, int32_t nType, int32_t nNpcGUID, int32_t nItemGUID);
