#pragma once


#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

#include <Windows.h>

#include <Storm.h>

#include "BigUnsigned.h"
#include "ImportHooks.h"


// Replacements of Storm's SBig functions, with numbers stored in little-endian order like Storm does.
// The number of live numbers is counted, so that tests can compare leaks.
struct StormBigMock
{
	static inline int nLiveNumbers = 0;

	static BigUnsigned& big(const void* pBig)
	{
		return *static_cast<BigUnsigned*>(const_cast<void*>(pBig));
	}

	// Storm.#624
	static int __stdcall SBigNew(void** ppBig)
	{
		*ppBig = new BigUnsigned();
		++nLiveNumbers;
		return 1;
	}

	// Storm.#606
	static int __stdcall SBigDel(void* pBig)
	{
		if (pBig)
		{
			delete static_cast<BigUnsigned*>(pBig);
			--nLiveNumbers;
		}
		return 1;
	}

	// Storm.#612
	static int __stdcall SBigFromUnsigned(void* pBig, unsigned int nValue)
	{
		big(pBig) = BigUnsigned(nValue);
		return 1;
	}

	// Storm.#609
	static int __stdcall SBigFromBinary(void* pBig, const void* pData, size_t nSize)
	{
		big(pBig) = BigUnsigned::from_bytes(static_cast<const uint8_t*>(pData), nSize);
		return 1;
	}

	// Storm.#638, writes at most nOutputSize bytes and the number of bytes written
	static int __stdcall SBigToBinaryBuffer(void* pBig, void* pOutput, uint32_t nOutputSize, uint32_t* pBytesWritten)
	{
		const std::vector<uint8_t> bytes = big(pBig).to_bytes();
		const uint32_t nSize = (uint32_t)std::min<size_t>(bytes.size(), nOutputSize);
		if (nSize)
		{
			std::memcpy(pOutput, bytes.data(), nSize);
		}
		if (pBytesWritten)
		{
			*pBytesWritten = nSize;
		}
		return 1;
	}

	// Storm.#603
	static int __stdcall SBigCompare(const void* pBigA, const void* pBigB)
	{
		return BigUnsigned::compare(big(pBigA), big(pBigB));
	}

	// Storm.#601
	static int __stdcall SBigAdd(void* pResult, const void* pBigA, const void* pBigB)
	{
		big(pResult) = BigUnsigned::add(big(pBigA), big(pBigB));
		return 1;
	}

	// Storm.#636
	static int __stdcall SBigSub(void* pResult, const void* pBigA, const void* pBigB)
	{
		big(pResult) = BigUnsigned::sub(big(pBigA), big(pBigB));
		return 1;
	}

	// Storm.#622
	static int __stdcall SBigMul(void* pResult, const void* pBigA, const void* pBigB)
	{
		big(pResult) = BigUnsigned::mul(big(pBigA), big(pBigB));
		return 1;
	}

	// Storm.#628
	static int __stdcall SBigPowMod(void* pResult, const void* pBase, const void* pExponent, const void* pModulus)
	{
		big(pResult) = BigUnsigned::pow_mod(big(pBase), big(pExponent), big(pModulus));
		return 1;
	}
};

// Functions the original dll does not import are only replaced for D2MOO
inline void hook_storm_big_mocks(ImportHooks& hooks)
{
	hooks.hook("Storm.dll", 601, reinterpret_cast<void*>(&::SBigAdd), reinterpret_cast<const void*>(&StormBigMock::SBigAdd), false);
	hooks.hook("Storm.dll", 603, reinterpret_cast<void*>(&::SBigCompare), reinterpret_cast<const void*>(&StormBigMock::SBigCompare), false);
	hooks.hook("Storm.dll", 606, reinterpret_cast<void*>(&::SBigDel), reinterpret_cast<const void*>(&StormBigMock::SBigDel), false);
	hooks.hook("Storm.dll", 609, reinterpret_cast<void*>(&::SBigFromBinary), reinterpret_cast<const void*>(&StormBigMock::SBigFromBinary), false);
	hooks.hook("Storm.dll", 612, reinterpret_cast<void*>(&::SBigFromUnsigned), reinterpret_cast<const void*>(&StormBigMock::SBigFromUnsigned), false);
	hooks.hook("Storm.dll", 622, reinterpret_cast<void*>(&::SBigMul), reinterpret_cast<const void*>(&StormBigMock::SBigMul), false);
	hooks.hook("Storm.dll", 624, reinterpret_cast<void*>(&::SBigNew), reinterpret_cast<const void*>(&StormBigMock::SBigNew), false);
	hooks.hook("Storm.dll", 628, reinterpret_cast<void*>(&::SBigPowMod), reinterpret_cast<const void*>(&StormBigMock::SBigPowMod), false);
	hooks.hook("Storm.dll", 636, reinterpret_cast<void*>(&::SBigSub), reinterpret_cast<const void*>(&StormBigMock::SBigSub), false);
	hooks.hook("Storm.dll", 638, reinterpret_cast<void*>(&::SBigToBinaryBuffer), reinterpret_cast<const void*>(&StormBigMock::SBigToBinaryBuffer), false);
}
