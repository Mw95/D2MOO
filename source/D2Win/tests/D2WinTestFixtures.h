#pragma once


#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <vector>

#include <Windows.h>

#include <FogMemoryMocks.h>
#include <FunctionPair.h>
#include <ImportHooks.h>
#include <NoOpFixture.h>
#include <StormMocks.h>

#include <D2WinControlHeader.h>


// Image base of the 1.10f D2Win.dll, the addresses in the comments of the sources are given for it
constexpr uintptr_t D2WinImageBase = 0x6F8A0000;

inline HMODULE get_original_d2win()
{
	static const HMODULE module = []()
	{
		const auto module = LoadLibraryA((std::filesystem::current_path() / "D2Win.dll").string().c_str());
		if (module == nullptr)
		{
			throw std::runtime_error("Cannot load the original D2Win.dll");
		}
		return module;
	}();
	return module;
}

// Address in the loaded original D2Win.dll of an address given for the 1.10f image base
inline uintptr_t original_d2win_address(uintptr_t nAddress)
{
	return reinterpret_cast<uintptr_t>(get_original_d2win()) + nAddress - D2WinImageBase;
}

template<typename T>
T* original_d2win_global(uintptr_t nAddress)
{
	return reinterpret_cast<T*>(original_d2win_address(nAddress));
}

// Pair of the D2MOO function and the same function in the original D2Win.dll
template<typename Function>
auto make_d2win_pair(Function& function, uintptr_t nAddress)
{
	return make_function_pair(function, original_d2win_address(nAddress));
}

// Replaces the Storm and Fog memory functions, which are only stubs in D2MOO
template<class Fixture>
struct D2WinFixture : Fixture
{
	ImportHooks hooks{ get_original_d2win() };

	D2WinFixture()
	{
		hook_storm_mocks(hooks);
		hook_fog_memory_mocks(hooks);
	}

	template<typename Function>
	void hook(const char* szDll, WORD nOrdinal, Function* pMooTarget, Function* pReplacement)
	{
		hooks.hook(szDll, nOrdinal, reinterpret_cast<void*>(pMooTarget), reinterpret_cast<const void*>(pReplacement), false);
	}
};


// Fake controls of one implementation. The links between them are described by indices, so that both implementations can be compared.
struct FakeControls
{
	std::vector<D2WinControlStrc> controls;

	explicit FakeControls(size_t nCount, int32_t nType = D2WIN_IMAGE)
		: controls(nCount)
	{
		for (D2WinControlStrc& control : controls)
		{
			control = {};
			control.nType = nType;
		}
	}

	D2WinControlStrc* get(int32_t nIndex)
	{
		return nIndex < 0 ? nullptr : &controls[nIndex];
	}

	// Index of a control, -1 for nullptr and -2 for an unknown pointer
	int32_t index(const void* pControl) const
	{
		if (pControl == nullptr)
		{
			return -1;
		}

		for (size_t i = 0; i < controls.size(); ++i)
		{
			if (pControl == &controls[i])
			{
				return (int32_t)i;
			}
		}
		return -2;
	}

	// Indices of the controls of a list, stops after a loop
	std::vector<int32_t> list(const D2WinControlStrc* pFirst) const
	{
		std::vector<int32_t> indices;
		for (const D2WinControlStrc* pControl = pFirst; pControl && indices.size() <= controls.size(); pControl = pControl->pNext)
		{
			indices.push_back(index(pControl));
		}
		return indices;
	}
};
