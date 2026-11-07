#pragma once


#include <cstdint>
#include <string>
#include <vector>

#include <D2Lang.h>
#include <D2Unicode.h>

#include "ImportHooks.h"


// D2LANG_GetStringFromTblIndex (D2Lang.#10004) returning "#<index>", so that no string table needs to be loaded.
// Every requested index is recorded in `calls`.
struct D2LangStringMock
{
	static inline Unicode wszStrings[0x10000][8];
	static inline std::vector<short> calls;

	static const Unicode* __fastcall GetStringFromTblIndex(short nIndex)
	{
		calls.push_back(nIndex);
		Unicode* wszString = wszStrings[(uint16_t)nIndex];
		const std::string szString = "#" + std::to_string((uint16_t)nIndex);
		for (size_t i = 0; i <= szString.size(); ++i)
		{
			wszString[i] = (Unicode)(uint16_t)(uint8_t)szString.c_str()[i];
		}
		return wszString;
	}

	static std::vector<Unicode> expected(short nIndex)
	{
		const Unicode* wszString = GetStringFromTblIndex(nIndex);
		calls.pop_back();
		std::vector<Unicode> result;
		for (; *wszString != 0; ++wszString)
		{
			result.push_back(*wszString);
		}
		result.push_back(0);
		return result;
	}
};

inline void hook_d2lang_string_mocks(ImportHooks& hooks)
{
	hooks.hook("D2Lang.dll", 10004, reinterpret_cast<void*>(&D2LANG_GetStringFromTblIndex), reinterpret_cast<const void*>(&D2LangStringMock::GetStringFromTblIndex), false);
	D2LangStringMock::calls.clear();
}
