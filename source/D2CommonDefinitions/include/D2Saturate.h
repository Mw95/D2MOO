#pragma once

// Saturating integer arithmetic for life and damage.
//
// The game keeps life, mana, stamina and damage as signed 32-bit integers, most of them in 24.8 fixed point
// (the value << 8). The original computes with them in plain 32-bit arithmetic, so a large enough value wraps:
// life past 8,388,607 turns negative, a big percentage bonus flips the sign of the damage, and so on.
//
// These helpers do the same computations in 64-bit and clamp the result to the int32 range. For every input whose
// original result did not wrap, they return exactly what the original returns (same truncation, same rounding);
// they differ only where the original wrapped. See doc/OverflowFixes.md.

#include <cstdint>
#include <limits>

constexpr int32_t D2_INT32_MAX = (std::numeric_limits<int32_t>::max)();
constexpr int32_t D2_INT32_MIN = (std::numeric_limits<int32_t>::min)();

// Clamps a 64-bit value into the int32 range.
inline constexpr int32_t D2SaturateToInt32(int64_t nValue)
{
	return nValue > D2_INT32_MAX ? D2_INT32_MAX : (nValue < D2_INT32_MIN ? D2_INT32_MIN : static_cast<int32_t>(nValue));
}

// Clamps a 64-bit value into [0, INT32_MAX], for quantities that cannot be negative (a damage, a life total).
inline constexpr int32_t D2SaturateToPositiveInt32(int64_t nValue)
{
	return nValue < 0 ? 0 : D2SaturateToInt32(nValue);
}

// a + b
inline constexpr int32_t D2SatAdd(int32_t a, int32_t b)
{
	return D2SaturateToInt32(static_cast<int64_t>(a) + b);
}

// a - b
inline constexpr int32_t D2SatSub(int32_t a, int32_t b)
{
	return D2SaturateToInt32(static_cast<int64_t>(a) - b);
}

// a * b
inline constexpr int32_t D2SatMul(int32_t a, int32_t b)
{
	return D2SaturateToInt32(static_cast<int64_t>(a) * b);
}

// nValue << nShift, for converting a whole value to fixed point (nShift is 8 for 24.8). Negative values are
// multiplied, which is what the shift of a negative value does on every compiler the game was built with.
inline constexpr int32_t D2SatShl(int32_t nValue, int32_t nShift)
{
	return D2SaturateToInt32(static_cast<int64_t>(nValue) * (static_cast<int64_t>(1) << nShift));
}

// nValue * nMultiplier / nDivisor, truncated toward zero like the int division it replaces. 0 when nDivisor is 0.
inline constexpr int32_t D2SatMulDiv(int32_t nValue, int32_t nMultiplier, int32_t nDivisor)
{
	return nDivisor ? D2SaturateToInt32(static_cast<int64_t>(nValue) * nMultiplier / nDivisor) : 0;
}

// The game's ratio function (D2Common's DATATBLS_ApplyRatio, D2Game's MONSTERUNIQUE_CalculatePercentage, both
// 0x00483360 in 1.14d), with each of its four branches computed in 64 bits and saturated.
//
// The original picks a branch by size to dodge 32-bit overflow and gets it wrong: its first branch multiplies up to
// 0x100000 * 0x10000 = 2^36 in 32 bits, and its last computes in 64 bits but truncates the quotient to 32. The
// branches round differently (the second and third divide before they multiply), so the branch structure is kept:
// a ratio that did not overflow gives the same answer it always gave.
//
// D2ApplyRatio64 takes and returns 64-bit values, for a chain of ratios whose intermediate result may leave the int32
// range (life leech: damage * leech% / 100 * drain% / 100 / 64). Its products saturate at the int64 range.
inline constexpr int64_t D2SatMul64(int64_t a, int64_t b)
{
	constexpr int64_t nMax = (std::numeric_limits<int64_t>::max)();
	constexpr int64_t nMin = (std::numeric_limits<int64_t>::min)();
	if (a == 0 || b == 0)
	{
		return 0;
	}
	const bool bNegative = (a < 0) != (b < 0);
	// Magnitudes as unsigned, which also holds the magnitude of INT64_MIN.
	const uint64_t nA = a < 0 ? 0 - static_cast<uint64_t>(a) : static_cast<uint64_t>(a);
	const uint64_t nB = b < 0 ? 0 - static_cast<uint64_t>(b) : static_cast<uint64_t>(b);
	const uint64_t nLimit = bNegative ? static_cast<uint64_t>(nMax) + 1 : static_cast<uint64_t>(nMax);
	if (nA > nLimit / nB)
	{
		return bNegative ? nMin : nMax;
	}
	const uint64_t nProduct = nA * nB;
	return bNegative ? static_cast<int64_t>(0 - nProduct) : static_cast<int64_t>(nProduct);
}

inline constexpr int64_t D2ApplyRatio64(int64_t nValue, int32_t nMultiplier, int32_t nDivisor)
{
	if (!nDivisor)
	{
		return 0;
	}

	if (nValue <= 0x100000)
	{
		if (nMultiplier <= 0x10000)
		{
			return D2SatMul64(nMultiplier, nValue) / nDivisor;
		}

		if (nDivisor <= (nMultiplier >> 4))
		{
			return D2SatMul64(nValue, nMultiplier / nDivisor);
		}
	}
	else if (nDivisor <= (nValue >> 4))
	{
		return D2SatMul64(nMultiplier, nValue / nDivisor);
	}

	return D2SatMul64(nMultiplier, nValue) / nDivisor;
}

inline constexpr int32_t D2ApplyRatioSaturated(int32_t nValue, int32_t nMultiplier, int32_t nDivisor)
{
	return D2SaturateToInt32(D2ApplyRatio64(nValue, nMultiplier, nDivisor));
}
