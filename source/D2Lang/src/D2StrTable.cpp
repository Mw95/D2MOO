/**
 * D2MOO
 * Copyright (c) 2020-2022  The Phrozen Keep community
 *
 * This file belongs to D2MOO.
 * File authors: Mir Drualga
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "D2StrTable.h"

#include <stdlib.h>
#include <string.h>

#include <Windows.h>

#include <Archive.h>
#include <D2Constants.h>
#include <D2Lang.h>
#include <D2Unicode.h>
#include <Fog.h>

/**
 * This variable is never set.
 *
 * 1.00: D2Lang.0x100175EC
 * 1.10: D2Lang.0x6FC20CDC
 * 1.13c: D2Lang.0x6FC10A8C
 * 1.14c: Game.0x00879A64
 */
static HD2ARCHIVE ghArchive = nullptr;

/**
 * 1.00: D2Lang.0x100175F4
 * 1.10: D2Lang.0x6FC20CE8
 * 1.13c: D2Lang.0x6FC10A20
 * 1.14c: Game.0x00879A78
 */
static bool gbTableLanguageInitialized = false;

/**
 * 1.00: D2Lang.0x100175F8
 * 1.10: D2Lang.0x6FC20CEC
 * 1.13c: D2Lang.0x6FC10A1C
 * 1.14c: Game.0x00879A74
 */
static D2C_Language gnTableLanguage = LANGUAGE_ENGLISH;

struct D2LocaleStrc
{
	const char* szWindowsLanguage;		// Language code used by Windows (sLanguage)
	const char* szLanguage;				// Directory of the language files (e.g. data\local\lng\ENG)
	const char* szAlternateLanguage;
	const char* szRegion;
	uint32_t dwLocale;					// Locale as a four character code
	D2C_Language eLanguage;
};

/**
 * Note: The last entry is never matched by STRTABLE_GetSystemLanguage,
 * since its Windows language is the same as the first entry.
 *
 * 1.10: D2Lang.[0x6FC1D9F0 to 0x6FC1DB28)
 */
static const D2LocaleStrc sgLocaleTable[NUM_LANGUAGES] = {
	{ "ENU", "ENG", "ENG", "USA", 'enUS', LANGUAGE_ENGLISH },
	{ "ESP", "ESP", "ESP", "ESP", 'esES', LANGUAGE_SPANISH },
	{ "DEU", "DEU", "DEU", "DEU", 'deDE', LANGUAGE_GERMAN },
	{ "FRA", "FRA", "FRA", "FRA", 'frFR', LANGUAGE_FRENCH },
	{ "POR", "POR", "POR", "BRA", 'ptBR', LANGUAGE_PORTUGUESE },
	{ "ITA", "ITA", "ITA", "ITA", 'itIT', LANGUAGE_ITALIAN },
	{ "JPN", "JPN", "ENG", "JPN", 'jaJA', LANGUAGE_JAPANESE },
	{ "KOR", "KOR", "ENG", "HAN", 'koKR', LANGUAGE_KOREAN },
	{ "SIN", "SIN", "ENG", "SIN", 'zhCN', LANGUAGE_CHINESESIN },
	{ "CHI", "CHI", "ENG", "CHI", 'zhTW', LANGUAGE_CHINESETWN },
	{ "POL", "POL", "POL", "POL", 'plPL', LANGUAGE_POLISH },
	{ "RUS", "RUS", "RUS", "RUS", 'ruRU', LANGUAGE_RUSSIAN },
	{ "ENU", "ENG", "ENG", "HAN", 'koKR', LANGUAGE_ENGLISHKOR },
};

/**
 * Localized suffixes for thousands, millions, billions and trillions,
 * used by STR_GroupUint64DigitsWithSuffix. They are read from the
 * string table when it is loaded.
 *
 * 1.10: D2Lang.0x6FC20CA6, 0x6FC20CAA, 0x6FC20CA8, 0x6FC20CA4
 */
static Unicode gwThousandsSuffix = L'K';
static Unicode gwMillionsSuffix = L'M';
static Unicode gwBillionsSuffix = L'B';
static Unicode gwTrillionsSuffix = L'T';

inline static void WriteDigitsOverflow(Unicode* pUnicode)
{
	Unicode asteriskStr[2];
	Unicode::toUnicode(asteriskStr, "*", 2);
	Unicode::strcpy(pUnicode, asteriskStr);
}

inline static void GroupCStrDigits(Unicode* pUnicode, const char* pcSrc, int nMaxLength)
{
	int nBufferLength = strlen(pcSrc);

	int nUnicodeLength = ((nBufferLength - 1) / 3) + nBufferLength;
	if (nBufferLength == 0 || nUnicodeLength <= 0 || nUnicodeLength >= nMaxLength - 1)
	{
		WriteDigitsOverflow(pUnicode);
		return;
	}

	pUnicode[nUnicodeLength] = '\0';
	int nDistanceToComma = 0;
	// Like C++ reverse iterators, i and j point to the index after the
	// insertion index.
	// i = destination index (naming is to preserve accurate assert msg)
	// j = source index
	for (int i = nUnicodeLength, j = nBufferLength; j > 0; --i, --j)
	{
		D2_ASSERT(i);

		pUnicode[i - 1] = pcSrc[j - 1];
		++nDistanceToComma;
		if (nDistanceToComma < 3)
		{
			continue;
		}

		// Inefficient: Calls strlen again.
		if (strlen(pcSrc) <= 3 || i - 1 <= 0)
		{
			continue;
		}

		nDistanceToComma = 0;
		pUnicode[i - 2] = L',';
		--i;
	}
}

/**
 * 1.00: D2Lang.0x100010B9 (#10007)
 * 1.10: D2Lang.0x6FC13DF0 (#10007)
 * 1.13c: D2Lang.0x6FC09290 (#10009)
 * 1.14c: Game.0x00522610
 */
D2C_Language STRTABLE_GetLanguage()
{
	if (gbTableLanguageInitialized)
	{
		return gnTableLanguage;
	}
	gbTableLanguageInitialized = true;
	// Read locale from file.
	unsigned char* pBuffer = (unsigned char*) ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(ghArchive, "data\\local\\use", nullptr);
	gnTableLanguage = static_cast<D2C_Language>(*pBuffer);
	D2_FREE(pBuffer);

	if (gnTableLanguage >= NUM_LANGUAGES)
	{
		gnTableLanguage = LANGUAGE_ENGLISH;
	}

	return gnTableLanguage;
}

/**
 * 1.00: D2Lang.0x100010AF (#10009)
 * 1.10: D2Lang.0x6FC140E0 (#10009)
 * 1.13c: D2Lang.0x6FC09BC0 (#10002)
 * 1.14c: Game.0x00523510
 */
void __stdcall STR_GroupIntDigits(Unicode* pUnicode, int nValue, int nMaxLength)
{
	D2_ASSERT(nMaxLength > 2);

	if (nValue < 0)
	{
		pUnicode[0] = L'-';
		++pUnicode;
		nMaxLength -= 1;
		nValue = -nValue;
	}

	char chBuffer[64];
	_itoa(nValue, chBuffer, 10);

	GroupCStrDigits(pUnicode, chBuffer, nMaxLength);
}

/**
 * 1.00: D2Lang.0x100010DC (#10010)
 * 1.10: D2Lang.0x6FC14210 (#10010)
 * 1.13c: D2Lang.0x6FC09A80 (#10006)
 * 1.14c: Game.0x005228A0
 */
void __stdcall STR_GroupUintDigits(Unicode* pUnicode, unsigned int dwValue, int nMaxLength)
{
	D2_ASSERT(nMaxLength > 2);

	char chBuffer[64];
	_ultoa(dwValue, chBuffer, 10);

	GroupCStrDigits(pUnicode, chBuffer, nMaxLength);
}

/**
 * 1.10: D2Lang.0x6FC13FB0 (#10006)
 */
void __stdcall STRTABLE_GetLanguageCode(char* szDest, D2C_LanguageCodeType eType)
{
	const D2C_Language eLanguage = STRTABLE_GetLanguage();

	D2_ASSERT(sgLocaleTable[0].eLanguage == LANGUAGE_ENGLISH);

	int nIndex = 0;
	if (eLanguage < NUM_LANGUAGES)
	{
		while (nIndex < NUM_LANGUAGES && sgLocaleTable[nIndex].eLanguage != eLanguage)
		{
			++nIndex;
		}

		if (nIndex >= NUM_LANGUAGES)
		{
			nIndex = 0;
		}
	}

	switch (eType)
	{
	case LANGUAGE_CODE_ALTERNATE:
		strcpy(szDest, sgLocaleTable[nIndex].szAlternateLanguage);
		break;

	case LANGUAGE_CODE_REGION:
		strcpy(szDest, sgLocaleTable[nIndex].szRegion);
		break;

	case LANGUAGE_CODE_LOCALE:
		// Note: not null-terminated
		memcpy(szDest, &sgLocaleTable[nIndex].dwLocale, sizeof(sgLocaleTable[nIndex].dwLocale));
		break;

	default:
		strcpy(szDest, sgLocaleTable[nIndex].szLanguage);
		break;
	}
}

static D2C_Language GetLanguageFromWindowsLanguage(const char* szWindowsLanguage)
{
	for (int i = 0; i < NUM_LANGUAGES; ++i)
	{
		if (_stricmp(szWindowsLanguage, sgLocaleTable[i].szWindowsLanguage) == 0)
		{
			return sgLocaleTable[i].eLanguage;
		}
	}

	return LANGUAGE_ENGLISH;
}

/**
 * 1.10: D2Lang.0x6FC13E60 (#10008)
 */
D2C_Language STRTABLE_GetSystemLanguage()
{
	OSVERSIONINFOA versionInfo;
	versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);
	if (!GetVersionExA(&versionInfo))
	{
		return LANGUAGE_ENGLISH;
	}

	if (versionInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		char szLanguage[4];
		GetProfileStringA("Intl", "sLanguage", "ENG", szLanguage, sizeof(szLanguage));
		return GetLanguageFromWindowsLanguage(szLanguage);
	}

	if (versionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		HKEY hKey;
		if (RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\International", 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			return LANGUAGE_ENGLISH;
		}

		char szLanguage[256];
		DWORD dwType;
		// Vanilla bug: The size of the data was not initialized.
		DWORD dwSize = sizeof(szLanguage) - 1;
		const LSTATUS nResult = RegQueryValueExA(hKey, "sLanguage", nullptr, &dwType, (LPBYTE)szLanguage, &dwSize);
		if (nResult != ERROR_SUCCESS)
		{
			// Vanilla bug: The key is not closed.
			return LANGUAGE_ENGLISH;
		}
		szLanguage[dwSize] = '\0';

		const size_t nLength = strlen(szLanguage);
		if (nLength == 0 || nLength >= 4)
		{
			// Vanilla bug: The key is not closed.
			return LANGUAGE_ENGLISH;
		}

		RegCloseKey(hKey);
		return GetLanguageFromWindowsLanguage(szLanguage);
	}

	return LANGUAGE_ENGLISH;
}

/**
 * 1.10: D2Lang.0x6FC14330 (#10011)
 */
void __stdcall STR_GroupInt64Digits(Unicode* pUnicode, int64_t nValue, int nMaxLength)
{
	D2_ASSERT(nMaxLength > 2);

	if (nValue < 0)
	{
		pUnicode[0] = L'-';
		++pUnicode;
		nMaxLength -= 1;
		nValue = -nValue;
	}

	char chBuffer[64];
	_i64toa(nValue, chBuffer, 10);

	GroupCStrDigits(pUnicode, chBuffer, nMaxLength);
}

/**
 * 1.10: D2Lang.0x6FC14450 (#10012)
 */
void __stdcall STR_GroupUint64DigitsWithSuffix(Unicode* pUnicode, uint64_t nValue, int nMaxLength)
{
	D2_ASSERT(nMaxLength > 2);

	char chBuffer[64];
	_ui64toa(nValue, chBuffer, 10);

	int nBufferLength = strlen(chBuffer);
	if (nBufferLength == 0)
	{
		WriteDigitsOverflow(pUnicode);
		return;
	}

	// Number of groups of 3 digits to remove, keeping at least 4 digits.
	int nRemovedGroups = (nBufferLength - 1) / 3 - 1;
	if (nRemovedGroups >= 4)
	{
		nRemovedGroups = 4;
	}
	else if (nRemovedGroups < 0)
	{
		nRemovedGroups = 0;
	}

	nBufferLength -= 3 * nRemovedGroups;

	int nUnicodeLength = ((nBufferLength - 1) / 3) + nBufferLength;
	if (nUnicodeLength < 1 || nUnicodeLength >= nMaxLength - 2)
	{
		WriteDigitsOverflow(pUnicode);
		return;
	}

	pUnicode[nUnicodeLength + 1] = L'\0';
	switch (nRemovedGroups)
	{
	case 0:
		pUnicode[nUnicodeLength] = L'\0';
		break;
	case 1:
		pUnicode[nUnicodeLength] = gwThousandsSuffix;
		break;
	case 2:
		pUnicode[nUnicodeLength] = gwMillionsSuffix;
		break;
	case 3:
		pUnicode[nUnicodeLength] = gwBillionsSuffix;
		break;
	case 4:
		pUnicode[nUnicodeLength] = gwTrillionsSuffix;
		break;
	}

	int nDistanceToComma = 0;
	for (int i = nUnicodeLength, j = nBufferLength; j > 0;)
	{
		D2_ASSERT(i);

		pUnicode[--i] = chBuffer[--j];
		++nDistanceToComma;
		if (nDistanceToComma >= 3)
		{
			nDistanceToComma = 0;
			if (i > 0)
			{
				pUnicode[--i] = L',';
			}
		}
	}
}
