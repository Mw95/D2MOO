#pragma once


#include <cstdint>
#include <filesystem>
#include <stdexcept>

#include <Windows.h>

#include <D2LangStringMocks.h>
#include <FogEncodingMocks.h>
#include <FogMemoryMocks.h>
#include <FunctionPair.h>
#include <ImportHooks.h>
#include <NoOpFixture.h>
#include <StormMocks.h>

#include <D2Multi.h>


inline HMODULE get_original_d2multi()
{
	static const HMODULE module = []()
	{
		const auto module = LoadLibraryA((std::filesystem::current_path() / "D2Multi.dll").string().c_str());
		if (module == nullptr)
		{
			throw std::runtime_error("Cannot load the original D2Multi.dll");
		}
		return module;
	}();
	return module;
}

// Address in the loaded original D2Multi.dll of an address given for the 1.10f image base
inline uintptr_t original_d2multi_address(uintptr_t nAddress)
{
	return reinterpret_cast<uintptr_t>(get_original_d2multi()) + nAddress - D2MultiImageBase;
}

template<typename T>
T* original_d2multi_global(uintptr_t nAddress)
{
	return reinterpret_cast<T*>(original_d2multi_address(nAddress));
}

// Pair of the D2MOO function and the same function in the original D2Multi.dll
template<typename Function>
auto make_d2multi_pair(Function& function, uintptr_t nAddress)
{
	return make_function_pair(function, original_d2multi_address(nAddress));
}

// Replaces the Storm functions, the Fog memory and encoding functions and the string table, which are only stubs in D2MOO
template<class Fixture>
struct D2MultiFixture : Fixture
{
	ImportHooks hooks{ get_original_d2multi() };

	D2MultiFixture()
	{
		hook_storm_mocks(hooks);
		hook_fog_memory_mocks(hooks);
		hook_fog_encoding_mocks(hooks);
		hook_d2lang_string_mocks(hooks);
	}
};
