# Added equipment slot: Cloak

This build adds one equipment slot to the player that the original game does not have: **body location 13, `BODYLOC_CLOAK`**.
It is meant for a new armor item type (the "cloak", item type code `clok`). It is not shown on the character model and hirelings
cannot use it. Items go in by drag-and-drop, or by right-click equip like any other armor piece.

The code side lives in D2MOO (D2Common + D2Game) and in the D2Client rewrite; both must be the modified builds, on every machine in a
game. D2Common and D2Game must run as full replacements of the original DLLs: in D2.Detours patch mode, functions routed to the
original code still assume 13 body locations.

## Why 13

Body locations 11 and 12 are the weapon-switch slots and are stored in saves, so the new slot is appended after them. The item bitstream
(saves and the item packet) stores the body location in 4 bits and clamps it to 15, so 13 fits without changing either format, and
existing characters load unchanged. At most one more slot (14) would fit the same way.

## Data changes

The `.txt` files are not in this repository; edit your extracted copies (`data/global/excel`). Always **append** rows: inserting rows
shifts indices that the code and other tables refer to.

### bodylocs.txt (required)

A row's index is the body location it names, so the `clok` row must be the 14th data row (index 13). If your file stops at `glov`
(index 10), first add two placeholder rows for the weapon-switch slots:

| Body Location     | Code |
|-------------------|------|
| Right Arm Switch  | rsw  |
| Left Arm Switch   | lsw  |
| Cloak             | clok |

D2Common shows a warning at load time if the `clok` row lands on another index. The table is only read when the game compiles its
tables from `.txt` (`-txt`); the resulting `itemtypes.bin` then holds the index.

### itemtypes.txt (required)

Append one row. Columns not listed: leave empty or 0.

| Column        | Value  | Note                                        |
|---------------|--------|---------------------------------------------|
| ItemType      | Cloak  |                                             |
| Code          | clok   |                                             |
| Equiv1        | armo   | counts as armor (defense, durability, repair) |
| Repair        | 1      |                                             |
| Body          | 1      | equippable                                  |
| BodyLoc1      | clok   |                                             |
| BodyLoc2      | clok   |                                             |
| Magic         | 0      | 1 would make it always magic                |
| Rare          | 1      | allows rare versions                        |
| Normal        | 0      | 1 would make it normal-only                 |
| MaxSock1/25/40 | 0     | or as you like                              |
| TreasureClass | 1      | builds `armo` treasure classes for it       |
| Rarity        | 3      |                                             |
| StorePage     | armo   | sold on the vendors' armor tab              |

### armor.txt (required)

Append one row per cloak (normal/exceptional/elite tiers if you want them). Easiest is to copy a gloves row and change:

* `name`, `code` (a new unique 3-letter code, e.g. `clk`), `namestr` (a string key, see below);
* `type` = `clok`;
* `invwidth` = 2, `invheight` = 2 (the slot is sized like the helm);
* `invfile` (and `flippyfile`, `uniqueinvfile`, `setinvfile` if used) = your new graphics;
* defense, durability, level, requirements as you like.

Keep the values the gloves row has for `component` and the armor-part columns (`rArm`, `lArm`, `Torso`, `Legs`, `rSPad`, `lSPad`),
so nothing is drawn on the character.

### inventory.txt (optional)

Without any change the slot is placed left of the helm, the same size as the helm, separated from it by the same gap as the amulet on
the other side. That placement is computed from each row's `head*` and `neck*` columns, for every class and both resolutions. It has
not been checked against the panel art in-game; if it overlaps something (for example the I/II weapon-swap tabs in the expansion), add
these columns to `inventory.txt` (anywhere, they are matched by name) and fill them on the class rows:

`cloakLeft`, `cloakRight`, `cloakTop`, `cloakBottom` (pixels), `cloakWidth`, `cloakHeight` (same meaning as the other slots' `*Width`/`*Height` columns).

These columns are only read when the tables are compiled from `.txt` (`-txt`): `inventory.bin` keeps the original record layout, so
when the game loads `.bin` files the defaults are used. A row left at 0 also gets the default.

### Strings and graphics

* Add each `namestr` key to a string table (e.g. `patchstring.tbl`).
* Add the inventory graphics (`data/global/items/<invfile>.dc6`), and the flippy/drop graphics if you set them.
* The panel art (`invchar6`) has no frame for the new slot; the client draws a placeholder frame (dark fill, thin outline) under it.

## Behaviour

* Equip, unequip and swap through the cursor, right-click equip, save/load, corpse recovery, stat and set-bonus activation, repair and
  durability all include the slot.
* A melee hit on a player can now also wear down the cloak (weight 2, like gloves, boots and belt). This adds an entry to the durability
  roll, so the odds for the other slots change slightly.
* Hirelings cannot equip it; it is not drawn on the character.

## Where the code is

* `D2Common/include/D2Inventory.h`: `BODYLOC_CLOAK`, `INVENTORY_IsActiveBodyLoc`, `INVENTORY_IsCursorEquipBodyLoc`.
* `D2Common/src/D2Inventory.cpp`: the body-location grid is `NUM_BODYLOC` wide.
* `D2Common/src/DataTbls/InvTbls.cpp`: the cloak rectangles (side table, `INV_COMP_CLOAK`) and their defaults.
* `D2Common/src/DataTbls/DataTbls.cpp`: the `bodylocs.txt` row check.
* `D2Game`: packet checks (`PlrMsg.cpp`), item activation and corpse recovery (`ItemMode.cpp`), death (`PlrModes.cpp`), durability (`SUnitDmg.cpp`).
* D2Client: `D2Client.h` (`BODYLOC_CLOAK`, `NUM_BODYLOC_EXTENDED`, `BODYLOC_NextActive`), `inv.h`/`inv.cpp` (slot rectangle, click, hover,
  drawing, placeholder frame), `Item.cpp` (stat walks).
