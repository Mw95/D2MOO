#include <D2Saturate.h>

// Compile-time checks for the saturating life and damage arithmetic (doc/OverflowFixes.md).

// Plain conversions.
static_assert(D2SaturateToInt32(static_cast<int64_t>(D2_INT32_MAX) + 1) == D2_INT32_MAX, "saturates up");
static_assert(D2SaturateToInt32(static_cast<int64_t>(D2_INT32_MIN) - 1) == D2_INT32_MIN, "saturates down");
static_assert(D2SaturateToInt32(-12345) == -12345, "in range is unchanged");
static_assert(D2SatAdd(D2_INT32_MAX, 1) == D2_INT32_MAX && D2SatAdd(-5, 3) == -2, "add");
static_assert(D2SatSub(D2_INT32_MIN, 1) == D2_INT32_MIN && D2SatSub(0, D2_INT32_MIN) == D2_INT32_MAX, "sub");
static_assert(D2SatMul(65536, 65536) == D2_INT32_MAX && D2SatMul(-65536, 65536) == D2_INT32_MIN, "mul");

// 24.8 fixed point: 8,388,607 life is the largest that fits, one more saturates instead of turning negative.
static_assert(D2SatShl(8388607, 8) == 8388607 * 256, "largest 24.8 life");
static_assert(D2SatShl(8388608, 8) == D2_INT32_MAX, "one more saturates");
static_assert(D2SatShl(-3, 8) == -768, "negative values shift as the original does");

// The source-damage scaling (x * nSrcDam / 128) truncates toward zero like the int division it replaces.
static_assert(D2SatMulDiv(-1000, 100, 128) == -781, "truncation toward zero");
static_assert(D2SatMulDiv(D2_INT32_MAX, 255, 128) == D2_INT32_MAX, "saturated");
static_assert(D2SatMulDiv(1, 1, 0) == 0, "division by zero is 0, as in the ratio function");

// The ratio function keeps the original's rounding (the 2nd and 3rd branches divide first).
static_assert(D2ApplyRatioSaturated(30, 0x20000, 7) == 30 * (0x20000 / 7), "divide-first branch kept");
static_assert(D2ApplyRatioSaturated(0x200000, 50, 100) == 50 * (0x200000 / 100), "large value branch kept");
static_assert(D2ApplyRatioSaturated(1000, 150, 100) == 1500, "plain percentage");
// ... and no longer wraps: 4096 life (24.8) times 65536 used to overflow the 'both small' branch.
static_assert(D2ApplyRatioSaturated(0x100000, 0x10000, 100) == static_cast<int32_t>(static_cast<int64_t>(0x100000) * 0x10000 / 100), "first branch in 64 bits");
static_assert(D2ApplyRatioSaturated(D2_INT32_MAX, 1000, 100) == D2_INT32_MAX, "saturated percentage");
static_assert(D2ApplyRatioSaturated(-2000000000, 300, 100) == D2_INT32_MIN, "saturated negative");

// The 64-bit chain used by life leech, and its own saturation.
static_assert(D2ApplyRatio64(D2_INT32_MAX, 6400, 100) == static_cast<int64_t>(6400) * (D2_INT32_MAX / 100), "leech chain stays exact past int32");
static_assert(D2SatMul64((std::numeric_limits<int64_t>::min)(), -1) == (std::numeric_limits<int64_t>::max)(), "int64 saturation");
