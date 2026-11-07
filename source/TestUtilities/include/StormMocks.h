#pragma once


#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <Windows.h>

#include <Storm.h>

#include "ImportHooks.h"


// Working replacements of the Storm.dll functions that are only stubs in D2MOO's Storm.dll.
// Use hook_storm_mocks() to install them for both the D2MOO implementation and an original dll.
struct StormMock
{
	// Storm.#401, flag 8 clears the memory
	static void* __stdcall SMemAlloc(int amount, const char* logfilename, int logline, uint32_t flags)
	{
		return (flags & 8) ? std::calloc(1, amount) : std::malloc(amount);
	}

	// Storm.#403
	static BOOL __stdcall SMemFree(void* location, const char* logfilename, int logline, uint32_t flags)
	{
		std::free(location);
		return TRUE;
	}

	// Storm.#491
	static int __stdcall SMemCopy(void* dest, const void* source, size_t size)
	{
		std::memmove(dest, source, size);
		return 1;
	}

	// Storm.#492
	static int __stdcall SMemFill(void* location, size_t length, char fillWith)
	{
		std::memset(location, fillWith, length);
		return 1;
	}

	// Storm.#494
	static int __stdcall SMemZero(void* location, size_t length)
	{
		std::memset(location, 0, length);
		return 1;
	}

	// Storm.#501, copies at most destsize - 1 characters and returns the number of copied characters
	static size_t __stdcall SStrCopy(char* dest, const char* source, size_t destsize)
	{
		if (destsize == 0)
		{
			return 0;
		}

		size_t length = 0;
		while (length + 1 < destsize && source[length])
		{
			dest[length] = source[length];
			++length;
		}
		dest[length] = '\0';
		return length;
	}

	// Storm.#503, max_length being the size of the base buffer
	static int __stdcall SStrNCat(char* base, const char* append, int max_length)
	{
		const size_t base_length = std::strlen(base);
		if ((int)base_length >= max_length)
		{
			return (int)base_length;
		}
		return (int)(base_length + SStrCopy(base + base_length, append, max_length - base_length));
	}

	// Storm.#506
	static size_t __stdcall SStrLen(const char* string)
	{
		return string ? std::strlen(string) : 0;
	}

	// Storm.#508
	static int32_t __stdcall SStrCmp(const char* Str1, const char* Str2, size_t MaxCount)
	{
		return std::strncmp(Str1, Str2, MaxCount);
	}

	// Storm.#509
	static int32_t __stdcall SStrCmpI(const char* Str1, const char* Str2, size_t MaxCount)
	{
		return _strnicmp(Str1, Str2, MaxCount);
	}

	// Storm.#510
	static char* __stdcall SStrUpper(char* Str)
	{
		for (char* pChar = Str; *pChar; ++pChar)
		{
			*pChar = (char)std::toupper((unsigned char)*pChar);
		}
		return Str;
	}

	// Storm.#578
	static int __cdecl SStrPrintf(char* DstBuf, size_t MaxCount, char* Format, ...)
	{
		va_list args;
		va_start(args, Format);
		const int nResult = std::vsnprintf(DstBuf, MaxCount, Format, args);
		va_end(args);
		if (MaxCount)
		{
			DstBuf[MaxCount - 1] = '\0';
		}
		return nResult < 0 ? (int)MaxCount - 1 : std::min(nResult, (int)MaxCount - 1);
	}

	// Storm.#571
	static const char* __stdcall SStrChr(const char* string, char c)
	{
		return std::strchr(string, c);
	}

	// Storm.#572
	static const char* __stdcall SStrChrR(const char* string, char c)
	{
		return std::strrchr(string, c);
	}
};

// Installs the Storm mocks. Functions the original dll does not import are only replaced for D2MOO.
inline void hook_storm_mocks(ImportHooks& hooks)
{
	hooks.hook("Storm.dll", 401, reinterpret_cast<void*>(&::SMemAlloc), reinterpret_cast<const void*>(&StormMock::SMemAlloc), false);
	hooks.hook("Storm.dll", 403, reinterpret_cast<void*>(&::SMemFree), reinterpret_cast<const void*>(&StormMock::SMemFree), false);
	hooks.hook("Storm.dll", 491, reinterpret_cast<void*>(&::SMemCopy), reinterpret_cast<const void*>(&StormMock::SMemCopy), false);
	hooks.hook("Storm.dll", 492, reinterpret_cast<void*>(&::SMemFill), reinterpret_cast<const void*>(&StormMock::SMemFill), false);
	hooks.hook("Storm.dll", 494, reinterpret_cast<void*>(&::SMemZero), reinterpret_cast<const void*>(&StormMock::SMemZero), false);
	hooks.hook("Storm.dll", 501, reinterpret_cast<void*>(&::SStrCopy), reinterpret_cast<const void*>(&StormMock::SStrCopy), false);
	hooks.hook("Storm.dll", 503, reinterpret_cast<void*>(&::SStrNCat), reinterpret_cast<const void*>(&StormMock::SStrNCat), false);
	hooks.hook("Storm.dll", 506, reinterpret_cast<void*>(&::SStrLen), reinterpret_cast<const void*>(&StormMock::SStrLen), false);
	hooks.hook("Storm.dll", 508, reinterpret_cast<void*>(&::SStrCmp), reinterpret_cast<const void*>(&StormMock::SStrCmp), false);
	hooks.hook("Storm.dll", 509, reinterpret_cast<void*>(&::SStrCmpI), reinterpret_cast<const void*>(&StormMock::SStrCmpI), false);
	hooks.hook("Storm.dll", 510, reinterpret_cast<void*>(&::SStrUpper), reinterpret_cast<const void*>(&StormMock::SStrUpper), false);
	hooks.hook("Storm.dll", 578, reinterpret_cast<void*>(&::SStrPrintf), reinterpret_cast<const void*>(&StormMock::SStrPrintf), false);
	hooks.hook("Storm.dll", 571, reinterpret_cast<void*>(&::SStrChr), reinterpret_cast<const void*>(&StormMock::SStrChr), false);
	hooks.hook("Storm.dll", 572, reinterpret_cast<void*>(&::SStrChrR), reinterpret_cast<const void*>(&StormMock::SStrChrR), false);
}
