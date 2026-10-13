#include <Fog.h>

// Values are packed into characters that never contain a null byte, so that they can be embedded in strings.

// 1.10f: 0x6FF51B20 (#10085)
unsigned __stdcall FOG_Decode14BitsFromString(uint16_t* p2Characters)
{
	const uint8_t* pCharacters = (const uint8_t*)p2Characters;
	return ((pCharacters[1] & 0x7F) << 7) + (pCharacters[0] & 0x7F);
}

// 1.10f: 0x6FF51B40 (#10086)
void __stdcall FOG_Encode14BitsToString(uint16_t* p2Characters, uint32_t value)
{
	uint8_t* pCharacters = (uint8_t*)p2Characters;
	pCharacters[0] = (uint8_t)value | 0x80;
	pCharacters[1] = (uint8_t)(value >> 7) | 0x80;
}

// 1.10f: 0x6FF51B60 (#10087)
// Each character holds a base 255 digit, offset by 1.
unsigned __stdcall FOG_Decode32BitsFromString(uint32_t* p4Characters)
{
	const uint8_t* pCharacters = (const uint8_t*)p4Characters;
	// 0xFE0200 == 1 + 255 + 255^2 + 255^3, removes the +1 offset of each digit
	return ((pCharacters[3] * 255u + pCharacters[2]) * 255u + pCharacters[1]) * 255u + pCharacters[0] - 0xFE0200;
}

// 1.10f: 0x6FF51BA0 (#10088)
void __stdcall FOG_Encode32BitsToString(uint32_t* p4Characters, uint32_t value)
{
	uint8_t* pCharacters = (uint8_t*)p4Characters;
	pCharacters[0] = (uint8_t)(value % 255 + 1);
	pCharacters[1] = (uint8_t)(value / 255 % 255 + 1);
	pCharacters[2] = (uint8_t)(value / (255 * 255) % 255 + 1);
	pCharacters[3] = (uint8_t)(value / (255 * 255 * 255) % 255 + 1);
}
