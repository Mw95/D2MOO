#pragma once


#include <cstdint>

#include <Fog.h>

#include "ImportHooks.h"


// FOG_Encode14BitsToString / FOG_Decode14BitsFromString are only stubs in D2MOO's Fog.dll.
// 14 bits are stored in two bytes, 7 bits each with the high bit set.
struct FogEncodingMock
{
	// Fog.#10086
	static void __stdcall Encode14BitsToString(uint16_t* p2Characters, uint32_t value)
	{
		uint8_t* pBytes = reinterpret_cast<uint8_t*>(p2Characters);
		pBytes[0] = (uint8_t)((value & 0x7F) | 0x80);
		pBytes[1] = (uint8_t)(((value >> 7) & 0x7F) | 0x80);
	}

	// Fog.#10085
	static unsigned __stdcall Decode14BitsFromString(uint16_t* p2Characters)
	{
		const uint8_t* pBytes = reinterpret_cast<const uint8_t*>(p2Characters);
		return (pBytes[0] & 0x7F) | ((pBytes[1] & 0x7F) << 7);
	}
};

inline void hook_fog_encoding_mocks(ImportHooks& hooks)
{
	hooks.hook("Fog.dll", 10086, reinterpret_cast<void*>(&FOG_Encode14BitsToString), reinterpret_cast<const void*>(&FogEncodingMock::Encode14BitsToString), false);
	hooks.hook("Fog.dll", 10085, reinterpret_cast<void*>(&FOG_Decode14BitsFromString), reinterpret_cast<const void*>(&FogEncodingMock::Decode14BitsFromString), false);
}
