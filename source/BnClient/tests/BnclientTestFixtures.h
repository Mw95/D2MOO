#pragma once


#include <cstdint>
#include <filesystem>
#include <stdexcept>

#include <Windows.h>

#include <FogMemoryMocks.h>
#include <FunctionPair.h>
#include <ImportHooks.h>
#include <NoOpFixture.h>
#include <StormMocks.h>

#include <BnMessQueue.h>


//1.10f Image base: 0x6FF00000
constexpr uintptr_t BnclientImageBase = 0x6FF00000;

inline HMODULE get_original_bnclient()
{
	static const HMODULE module = []()
	{
		const auto module = LoadLibraryA((std::filesystem::current_path() / "Bnclient.dll").string().c_str());
		if (module == nullptr)
		{
			throw std::runtime_error("Cannot load the original Bnclient.dll");
		}
		return module;
	}();
	return module;
}

// Address in the loaded original Bnclient.dll of an address given for the 1.10f image base
inline uintptr_t original_bnclient_address(uintptr_t nAddress)
{
	return reinterpret_cast<uintptr_t>(get_original_bnclient()) + nAddress - BnclientImageBase;
}

template<typename T>
T* original_bnclient_global(uintptr_t nAddress)
{
	return reinterpret_cast<T*>(original_bnclient_address(nAddress));
}

// Pair of the D2MOO function and the same function in the original Bnclient.dll
template<typename Function>
auto make_bnclient_pair(Function& function, uintptr_t nAddress)
{
	return make_function_pair(function, original_bnclient_address(nAddress));
}

// The D2MOO implementation is linked into the test executable, so its DllMain is not called
inline void initialize_moo_bnclient()
{
	static const bool bInitialized = []()
	{
		BNMESSQUEUE_Initialize();
		return true;
	}();
	(void)bInitialized;
}

// Replaces the Storm and Fog memory functions, which are only stubs in D2MOO
template<class Fixture>
struct BnclientStormFixture : Fixture
{
	ImportHooks hooks{ get_original_bnclient() };

	BnclientStormFixture()
	{
		initialize_moo_bnclient();
		hook_storm_mocks(hooks);
		hook_fog_memory_mocks(hooks);
	}
};
