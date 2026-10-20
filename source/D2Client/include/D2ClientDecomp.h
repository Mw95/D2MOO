#pragma once

#include <cstdint>
#include <cstring>

// Helpers for constructs that do not have a direct C++ equivalent yet.
// They mostly come from partial register accesses in the original binary and should disappear as the code gets cleaned up.

// Unknown function pointer type (indirect calls through tables or structure members)
typedef int32_t __cdecl code(...);

template <typename T, typename U>
inline uint64_t D2C_CONCAT(T hi, U lo, int loBytes)
{
	return ((uint64_t)hi << (loBytes * 8)) | ((uint64_t)lo & ((loBytes >= 8) ? ~0ull : ((1ull << (loBytes * 8)) - 1)));
}

#define CONCAT11(a, b) ((uint16_t)D2C_CONCAT((a), (b), 1))
#define CONCAT12(a, b) ((uint32_t)D2C_CONCAT((a), (b), 2))
#define CONCAT13(a, b) ((uint32_t)D2C_CONCAT((a), (b), 3))
#define CONCAT21(a, b) ((uint32_t)D2C_CONCAT((a), (b), 1))
#define CONCAT22(a, b) ((uint32_t)D2C_CONCAT((a), (b), 2))
#define CONCAT31(a, b) ((uint32_t)D2C_CONCAT((a), (b), 1))
#define CONCAT44(a, b) ((uint64_t)D2C_CONCAT((a), (b), 4))

#define SUB41(x, off) ((uint8_t)((uint32_t)(x) >> ((off) * 8)))
#define SUB42(x, off) ((uint16_t)((uint32_t)(x) >> ((off) * 8)))
#define SUB84(x, off) ((uint32_t)((uint64_t)(x) >> ((off) * 8)))

#define CARRY1(a, b) ((uint8_t)((uint8_t)(a) + (uint8_t)(b)) < (uint8_t)(a))
#define CARRY4(a, b) ((uint32_t)((uint32_t)(a) + (uint32_t)(b)) < (uint32_t)(a))
#define SCARRY4(a, b) ((((int32_t)(a) ^ (int32_t)(b)) >= 0) && ((((int32_t)(a) + (int32_t)(b)) ^ (int32_t)(a)) < 0))
#define SBORROW4(a, b) ((((int32_t)(a) ^ (int32_t)(b)) < 0) && ((((int32_t)(a) - (int32_t)(b)) ^ (int32_t)(a)) < 0))

inline int32_t D2C_POPCOUNT(uint32_t v)
{
	int32_t n = 0;
	for (; v; v &= v - 1)
	{
		++n;
	}
	return n;
}
#define POPCOUNT(x) D2C_POPCOUNT((uint32_t)(x))

#define D2C_ZEXT(x) ((uint32_t)(x))

inline int64_t D2C_alldiv(uint32_t nLo, uint32_t nHi, uint32_t nDivLo, uint32_t nDivHi)
{
	return (int64_t)(((uint64_t)nHi << 32) | nLo) / (int64_t)(((uint64_t)nDivHi << 32) | nDivLo);
}

inline int64_t D2C_allmul(uint32_t nLo, uint32_t nHi, uint32_t nMulLo, uint32_t nMulHi)
{
	return (int64_t)((((uint64_t)nHi << 32) | nLo) * (((uint64_t)nMulHi << 32) | nMulLo));
}

inline uint64_t D2C_aulldiv(uint32_t nLo, uint32_t nHi, uint32_t nDivLo, uint32_t nDivHi)
{
	return (((uint64_t)nHi << 32) | nLo) / (((uint64_t)nDivHi << 32) | nDivLo);
}

inline uint64_t D2C_aullrem(uint32_t nLo, uint32_t nHi, uint32_t nDivLo, uint32_t nDivHi)
{
	return (((uint64_t)nHi << 32) | nLo) % (((uint64_t)nDivHi << 32) | nDivLo);
}
