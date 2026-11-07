#pragma once


#include <cstdlib>

#include <Fog.h>

#include "ImportHooks.h"


// FOG_Alloc / FOG_Free are only stubs in D2MOO's Fog.dll. Memory may be allocated by one implementation and freed by the other.
struct FogMemoryMock
{
	// Fog.#10042
	static void* __fastcall Alloc(int nSize, const char* szFile, int nLine, int n0)
	{
		return std::malloc(nSize);
	}

	// Fog.#10043
	static void __fastcall Free(void* pMemory, const char* szFile, int nLine, int n0)
	{
		std::free(pMemory);
	}
};

inline void hook_fog_memory_mocks(ImportHooks& hooks)
{
	hooks.hook("Fog.dll", 10042, reinterpret_cast<void*>(&FOG_Alloc), reinterpret_cast<const void*>(&FogMemoryMock::Alloc), false);
	hooks.hook("Fog.dll", 10043, reinterpret_cast<void*>(&FOG_Free), reinterpret_cast<const void*>(&FogMemoryMock::Free), false);
}
