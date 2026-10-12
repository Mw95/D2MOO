#pragma once


#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <vector>

#include <Windows.h>

#include <D2Lang.h>
#include <InlineHook.h>


// Replaces D2LANG_GetStringFromTblIndex (D2Lang.#10004) for both the D2MOO implementation and the original D2Common.dll,
// so that no string table needs to be loaded.
// The fake returns a string whose first character is the requested index, so comparing results compares the indices.
// Every call is recorded in `d2lang_string_tbl_calls`, which tests can clear and compare between both implementations.
struct D2LangStringTblMock
{
	static inline uint16_t fake_strings[0x10000][2]{};
	static inline std::vector<short> calls;

	static const Unicode* __fastcall GetStringFromTblIndex(short nIndex)
	{
		calls.push_back(nIndex);

		auto& fake_string = fake_strings[static_cast<uint16_t>(nIndex)];
		fake_string[0] = static_cast<uint16_t>(nIndex);
		fake_string[1] = 0;
		return reinterpret_cast<const Unicode*>(fake_string);
	}
};

template<class Fixture>
struct D2LangStringTblFixture : Fixture
{
	std::vector<short>& d2lang_string_tbl_calls = D2LangStringTblMock::calls;
	std::vector<InlineHook> d2lang_hooks;

	D2LangStringTblFixture()
	{
		constexpr WORD D2LANG_GETSTRINGFROMTBLINDEX_ORDINAL = 10004;

		const auto working_directory = std::filesystem::current_path();
		const auto original_d2common = LoadLibraryA((working_directory / "D2Common.dll").string().c_str());
		if (original_d2common == nullptr)
		{
			throw std::runtime_error("D2LangStringTblFixture: Cannot load original D2Common.dll");
		}

		// Function called by the original D2Common.dll (the original D2Lang.dll, or D2MOO's if it was already loaded)
		void* original_target = find_imported_function_by_ordinal(original_d2common, "D2Lang.dll", D2LANG_GETSTRINGFROMTBLINDEX_ORDINAL);
		// Function called by the D2MOO implementation linked into the test executable
		void* moo_target = reinterpret_cast<void*>(&D2LANG_GetStringFromTblIndex);

		if (original_target == nullptr)
		{
			throw std::runtime_error("D2LangStringTblFixture: Original D2Common.dll does not import D2Lang.#10004");
		}

		// Note: with identical COMDAT folding (/OPT:ICF), the D2MOO stub may be shared with other stubs returning nullptr,
		// which would get redirected too while the fixture is alive.
		d2lang_hooks.reserve(2);
		d2lang_hooks.emplace_back(moo_target, reinterpret_cast<const void*>(&D2LangStringTblMock::GetStringFromTblIndex));
		if (original_target != moo_target)
		{
			d2lang_hooks.emplace_back(original_target, reinterpret_cast<const void*>(&D2LangStringTblMock::GetStringFromTblIndex));
		}

		D2LangStringTblMock::calls.clear();
	}
};
