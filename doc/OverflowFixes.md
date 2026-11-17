# Life and damage overflow fixes

D2MOO otherwise reproduces the original game's bugs (see the [README](../README.md)). Overflows in life and damage
arithmetic are the one deliberate exception: they are **fixed**, unconditionally, in D2Common and D2Game. The matching
display fixes in the D2Client rewrite are listed in that repository's `OVERFLOW_FIXES.md`.

## The problem

Life, mana, stamina and most damages are signed 32-bit integers in **24.8 fixed point** (the whole value `<< 8`).
The original does its arithmetic on them in 32 bits, so it wraps long before the stored value runs out:

| computation | wraps from |
|---|---|
| a stat converted to fixed point (`stat << 8`) | 8,388,608 |
| a percentage of a fixed-point value (`value * pct / 100`) | 83,887 life/damage at 100%; less with bigger percentages |
| `damage * nSrcDam / 128` (missiles, skills) | 65,536 damage at srcdam 128 |
| leech (`damage * (leech% << 6) / 100`) | a few thousand damage with a high leech% |
| the sum of the six damage types | when their total passes 8,388,607 |
| a stat list's total (base + items + skills + `op` bonuses) | when the sum passes the int32 range |
| the ratio helper `DATATBLS_ApplyRatio` / `MONSTERUNIQUE_CalculatePercentage` | its "safe" branch multiplies up to 2^36 in 32 bits |

A wrapped damage turns negative and heals, or becomes a tiny hit. A wrapped life kills a healthy unit or makes it
unkillable.

## The approach: saturate, don't widen

All fixes keep the 32-bit storage and do the arithmetic in 64 bits, then **saturate** (clamp) the result to the int32
range. This keeps every structure, export, save file and network packet unchanged, so D2MOO's DLLs still mix with the
original ones. The consequences:

* **Nothing that did not wrap changes.** Every helper reproduces the original's truncation and rounding exactly. For the
  ratio function this was checked on 30 million random inputs: of the 20 million where the original did not wrap, none
  differs. The ratio function keeps its four branches because two of them divide before they multiply, and some game
  numbers depend on that rounding.
* **The ceiling is 8,388,607.996 life (and damage per hit) in 24.8.** A value past it saturates to the maximum instead
  of wrapping. Raising that would mean widening the stat values to 64 bits: a different save format, a different
  protocol and new D2Common exports.

The helpers are in [`D2CommonDefinitions/include/D2Saturate.h`](../source/D2CommonDefinitions/include/D2Saturate.h):
`D2SaturateToInt32`, `D2SatAdd`, `D2SatSub`, `D2SatMul`, `D2SatShl` (fixed-point conversion), `D2SatMulDiv`,
`D2ApplyRatioSaturated` and the 64-bit `D2ApplyRatio64` / `D2SatMul64` used for chained ratios. Compile-time checks
are in `D2Common/statictests/D2Saturate_staticchecks.cpp` (built with `D2MOO_WITH_STATIC_TESTS`).

Each fixed site carries a `Fixed:` comment, or uses one of the helpers where a comment would only repeat the line.

## What was changed

### D2Common

* **Stat engine** (`D2StatList.cpp`): the total of a stat (`sub_6FDB5830`: base, child lists and every `op` bonus)
  is summed in 64 bits and saturated, with each `op` product taken in 64 bits. The cached totals that
  `sub_6FDB6C10` moves by a delta saturate too. A saturated cached total no longer equals the sum of its parts, so when
  a delta would leave the int32 range, or the cached total already sits at a bound, the total is **recomputed** from its
  parts instead of being moved. Every caller links a list before adding its stats and unlinks it before subtracting
  them, so the recomputation sees the right lists. `STATLIST_AddStat` saturates the base value and passes on only the
  change it actually took. `STATLIST_SetBaseStat`'s difference and `D2Common_11274/11275`'s negation are 64-bit.
  `STATLIST_GetUnitStatBonus` saturates.
* **Ratio** (`DATATBLS_ApplyRatio`): every branch is 64-bit and saturated.
* **Skill damage** (`D2Skills.cpp`): `SKILLS_CalculateDamageBonusByLevel` (64-bit), `SKILLS_Get{Min,Max}{Phys,Elem}Damage`
  (srcdam scaling, percentage bonuses, the `nToHitShift`), kick damage (`SKILLS_CalculateKickDamage`, the kick paths
  of the physical damage functions).
* **Missile damage** (`Missile.cpp`): `MISSILE_CalculateDamageData`, `MISSILE_AddStatsToDamage`,
  `MISSILE_CalculateFinalDamage`, `MISSILE_Get{Min,Max}[Elem]Damage`.
* **Item mods** (`ItemMods.cpp`, `Items.cpp`): life, mana and stamina properties converted to 24.8 with `D2SatShl`.
* **Healing cost** (`UNITS_GetHealingCost`): 64-bit, capped at the unsigned 32-bit result.

### D2Game

* **Hit pipeline** (`SUnitDmg.cpp`): `SUNITDMG_ApplyDamageBonuses`, `SUNITDMG_FillDamageValues` (fixed-point
  conversions, elemental rolls, srcdam scaling, critical/deadly strike doubling, leech/drain, conversion),
  `SUNITDMG_RollDamageValueInRange`, `SUNITDMG_CalculateTotalDamage` (the damage total is a 64-bit sum),
  `SUNITDMG_ApplyResistancesAndAbsorb` (resistance minus pierce, damage reduction, absorb), `SUNITDMG_ExecuteEvents`
  (life, mana and stamina subtraction; absorbed life).
* **Leech**: life and mana leech are computed in 64 bits up to the final `/ 64`. For a monster's drain, the original
  shifted left by 6 and back right by 6, wrapping any drain of 131,072 life or more; the drain values are now kept and
  restored instead. `SUNITDMG_AddLeechedLife` and `SUNITDMG_AddLeechedMana` saturate.
* **Percent helper** `MONSTERUNIQUE_CalculatePercentage`: as `DATATBLS_ApplyRatio`. Every `x += percentage of x` in
  D2Game and D2Common uses `D2SatAdd`.
* **Life changes**: player and monster regeneration, level-up life/mana/stamina, shrines (health, exchange, storm),
  obelisk life bonus, heal-after-kill, crushing blow, hireling life, monster life from monstats/player count, blood
  golem, conversion, redemption, corpse explosion, damage reflection, healing vortex and the other skill and missile damage
  functions under `SKILLS/` and `MISSILES/MissMode.cpp`.

### The 15-bit life packets (D2Game, `PlrMsg.cpp`)

Packets 0x18, 0x95 and 0x96 carry the player's life, mana and stamina in **15-bit fields**, so the client receives
them modulo 32,768: from 32,768 life the orb and the character screen showed a wrapped number. The packet layout
cannot change without breaking the original client, so the server now **follows such a packet with the exact 24.8 value
in a stat packet (0x1D/0x1E/0x1F)** whenever a value does not fit in 15 bits. Both the original client and the D2Client
rewrite apply that stat after the 15-bit value. The difference against the last life sent, kept in 16 bits, is taken
modulo 65,536, so above 65,535 life the server no longer resends on every call. The potion-prediction percentages are
computed in 64 bits and capped before they are narrowed to a byte.

## Limits that remain

* **The 24.8 ceiling** (see above): life, mana, stamina and per-hit damage stop at 8,388,607.
* **Character save files** store a stat with ItemStatCost.txt's `CSvBits`. With the stock table, base life and mana are
  21-bit 24.8 values, so a **base** (unequipped, unbuffed) life above 8,191 is clamped on save. The original already
  clamped rather than wrapped (`PLRSAVE2` writes the minimum/maximum), so this is a data limit, not an overflow; raise
  `CSvBits` in the table to lift it.
* **Display in the original D2Client**: with an original client, the life value is now correct, but that client's own
  display arithmetic still wraps (for example, the life globe from 104,858 life). The D2Client rewrite fixes those.
* **Patch tables**: in `D2.Detours.patches/1.10f`, most of D2Common's stat functions and D2Game's exports are still
  `FunctionReplacePatchByOriginal`, so the original code runs for them unless they are switched to D2MOO's. The fixes
  take effect wherever D2MOO's code runs.
* Experience, gold, attack rating and item levels are not life or damage and were not changed.

## Verification

* The ratio helpers were compared with the original algorithm on 30,000,000 random inputs: no difference on the 20 million
  where the original did not wrap.
* Static checks in `D2Saturate_staticchecks.cpp` pin the helpers' edge cases (largest 24.8 life, truncation toward zero,
  the divide-first branches, saturation).
* Every changed `.cpp` was type-checked with Clang against stub Windows headers and compared with the unchanged sources:
  no new diagnostics. The project was **not** built with MSVC here and the game was not run, so the fixes are untested
  in play.
