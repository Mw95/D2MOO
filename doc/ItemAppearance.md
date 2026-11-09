# Item appearance (transmog)

A player can give an equipped item the look of another base item at a blacksmith (Charsi, Fara, Hratli,
Halbu, Larzuk). Only the graphic changes. The item keeps all its other properties: stats, requirements,
damage, attack speed, weapon class, colour, name and inventory graphic.

The rules and storage are in [`D2ItemAppearance.h`](../source/D2Common/include/D2ItemAppearance.h). The client part
(drawing, tooltip and the blacksmith UI) is in the D2Client rewrite.

## Data: the `item_appearance` stat

The look is stored as a stat on the item, so no save-file or network format changes. Append this row to
`ItemStatCost.txt` after `passive_mag_pierce` (id 358):

| Column      | Value             | Why |
|-------------|-------------------|-----|
| Stat        | `item_appearance` | |
| ID          | `359`             | `STAT_ITEM_APPEARANCE` in `D2ItemAppearance.h` |
| Save Bits   | `10`              | value is the donor's items.txt row + 1. With 10 bits, up to 1022 rows (1.10f has about 650). Use more bits if your mod has more rows. |
| Save Add    | `0`               | |
| Send Bits   | `10`              | |
| descpriority, descfunc, descstrpos... | empty | the tooltip line is drawn by the client itself |

Leave every other column empty or `0`. Without this row the stat cannot be saved or sent, so the feature does nothing.

Item stats only go to clients for identified items. That is why only identified items can be changed.

## Rules

* The item to change must be identified.
* The item and the donor must both be drawn on the character, on the same composit layer: head, body armour,
  right or left hand, or shield. Circlets, rings, amulets, gloves, boots and belts have no character graphic.
* Weapons need the same `wclass` **and** `2handedwclass`. The weapon class picks the COF and the AnimData record,
  which decide attack speed and action frames. DCC files only exist for the classes an item can use.
  So attack speed, breakpoints and animations never change.
* Body armour copies the donor's six armour components (`rArm`, `lArm`, `Torso`, `Legs`, `rSPad`, `lSPad`).
* Class-specific donors (barbarian helms, druid pelts, paladin shields, shrunken heads, claws, orbs, amazon
  weapons) are only allowed for their own class, since their graphics may only exist in that class' folder.
* The donor must be one of the player's own items: in the inventory or the stash, or worn. It cannot be in the
  Horadric Cube. It is **kept**.
* Cost: `item level * 100` gold (from inventory gold, then the stash). Restoring the item's own look costs
  half of that.

## Protocol

The request uses client packet `0x38` (NPC item action, 13 bytes), the same packet as Charsi's imbue and
Larzuk's sockets:

* `nItemGUID`: the item to change. It is on the cursor while it is in the anvil slot.
* `nAction`: `0x80000000 | donor GUID` (`ITEMAPPEARANCE_MakeAction`). The vanilla actions are 0 to 3.
  A donor GUID equal to the item's own GUID restores its own look.

The server answers like the other anvil services. It removes the item from the cursor and places a copy with
the new stat in the inventory, then sends `0x58` action 6 (done) or 7 (refused).

## Runtime

D2MOO normally runs its D2Game code patched into the original `D2Game.dll`, with every function using the
original. `D2Game.patch.cpp` replaces only `NPC_HandleDialogMessage` (`0x6FCC9F40`) with
`NPC_HandleDialogMessageWithAppearance` (`source/D2Game/src/UNIT/SUnitNpcAppearance.cpp`). That wrapper handles
the appearance request and passes every other request to the original function. The D2Game helpers the handler
calls (finding units, sending packet 0x58, duplicating and placing the item, taking the gold) are redirected to
the original's code, so they work on the original's state. When the D2MOO D2Game runs on its own, packet 0x38
goes through the same wrapper. The character-select preview needs D2Common `#10298`
(`INVENTORY_GetItemSaveGfxInfo`) to be patched in as well.
