#include <Fog.h>
#include <D2BitManip.h>

#include <cstring>

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

// Note: the original code indexes the table with signed characters, which only works for ASCII characters.
static uint8_t* STRPACK_GetCharacterIndex(FOGStringPack* pStrPack, char nCharacter)
{
	return &pStrPack->pTable[(uint8_t)nCharacter];
}

static uint8_t* STRPACK_GetIndexCharacter(FOGStringPack* pStrPack, int8_t nIndex)
{
	return &pStrPack->pTable[0xFF + nIndex];
}

// 1.10f: 0x6FF53A10 (#10134)
// Builds the character table from the characters of szCharacters, at most (1 << nMaxBits) - 1 different characters may be used.
void __stdcall STRPACK_Initialize(FOGStringPack* pStrPack, int nMaxBits, const char* szCharacters)
{
	D2_ASSERT(pStrPack);
	D2_ASSERTM(szCharacters[0], "Tried to create a StrPack with no characters");

	memset(pStrPack, 0, sizeof(*pStrPack));

	uint8_t nCharactersCount = 0;
	for (const char* pCharacter = szCharacters; *pCharacter; ++pCharacter)
	{
		uint8_t* pIndex = STRPACK_GetCharacterIndex(pStrPack, *pCharacter);
		if (*pIndex == 0)
		{
			++nCharactersCount;
			D2_ASSERTM(nCharactersCount < (1 << nMaxBits), "Tried to create StringPack with illegal size");
			*pIndex = nCharactersCount;
			*STRPACK_GetIndexCharacter(pStrPack, nCharactersCount) = *pCharacter;
		}
	}

	// Note: indices start at 1, so 2 characters would actually need 2 bits. Kept as is for compatibility.
	D2_ASSERTM(nCharactersCount > 0, "Tried to create a StrPack with an illegal size");
	if (nCharactersCount <= 2)
	{
		pStrPack->nPackedBits = 1;
	}
	else if (nCharactersCount <= 4)
	{
		pStrPack->nPackedBits = 2;
	}
	else if (nCharactersCount <= 8)
	{
		pStrPack->nPackedBits = 3;
	}
	else if (nCharactersCount <= 16)
	{
		pStrPack->nPackedBits = 4;
	}
	else if (nCharactersCount <= 32)
	{
		pStrPack->nPackedBits = 5;
	}
	else if (nCharactersCount <= 64)
	{
		pStrPack->nPackedBits = 6;
	}
	else if (nCharactersCount <= 128)
	{
		pStrPack->nPackedBits = 7;
	}
	else
	{
		pStrPack->nPackedBits = 8;
	}
}

// 1.10f: 0x6FF53B80 (#10135)
void __stdcall STRPACK_PackString(FOGStringPack* pStrPack, const char* szString, uint8_t* pbBuffer, int nBufferSize, BOOL bForceTerminator)
{
	D2_ASSERT(pStrPack);
	D2_ASSERT(szString);
	D2_ASSERT(pbBuffer);
	D2_ASSERT(pStrPack->nPackedBits);

	D2BitBufferStrc tBuffer;
	BITMANIP_Initialize(&tBuffer, pbBuffer, nBufferSize);

	const int nPackedBits = pStrPack->nPackedBits;
	int nMaxCharacters = (nPackedBits * nBufferSize + 7) >> 3;
	if (bForceTerminator)
	{
		--nMaxCharacters;
	}

	int nCharacters = 0;
	for (const char* pCharacter = szString; *pCharacter; ++pCharacter)
	{
		++nCharacters;
		if (nCharacters >= nMaxCharacters)
		{
			break;
		}
		BITMANIP_Write(&tBuffer, (int8_t)*STRPACK_GetCharacterIndex(pStrPack, *pCharacter), nPackedBits);
	}

	if (bForceTerminator || nCharacters < nMaxCharacters)
	{
		BITMANIP_Write(&tBuffer, 0, nPackedBits);
	}
}

// 1.10f: 0x6FF53CA0 (#10136)
void __stdcall STRPACK_UnpackString(FOGStringPack* pStrPack, char* szString, uint8_t* pbBuffer, int nBufferSize, int nStringSize)
{
	D2_ASSERT(pStrPack);
	D2_ASSERT(szString);
	D2_ASSERT(pbBuffer);
	D2_ASSERT(pStrPack->nPackedBits);

	int nMaxCharacters = nStringSize - 1;
	const int nBufferCharacters = (8 * nBufferSize + 7) / pStrPack->nPackedBits;
	if (nBufferCharacters < nMaxCharacters)
	{
		nMaxCharacters = nBufferCharacters;
	}

	D2BitBufferStrc tBuffer;
	BITMANIP_Initialize(&tBuffer, pbBuffer, nBufferSize);

	const int nPackedBits = pStrPack->nPackedBits;
	int nCharacters = 0;
	while (nCharacters < nMaxCharacters)
	{
		const int8_t nIndex = (int8_t)BITMANIP_Read(&tBuffer, nPackedBits);
		szString[nCharacters] = (char)*STRPACK_GetIndexCharacter(pStrPack, nIndex);
		++nCharacters;
		if (nIndex == 0)
		{
			// Index 0 maps to the string terminator
			return;
		}
	}
	szString[nCharacters] = '\0';
}
