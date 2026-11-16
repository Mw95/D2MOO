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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>

#include <Archive.h>
#include <D2Constants.h>
#include <D2Lang.h>
#include <D2Unicode.h>
#include <D2Crc16.h>
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

// 1.10: D2Lang.0x6FC20CB4, 0x6FC20CD0, 0x6FC20CD4
static D2TblHeaderStrc* sghStringTable;
static D2TblHeaderStrc* sghPatchStringTable;
static D2TblHeaderStrc* sghExpansionStringTable;
// Strings of each table, indexed like the table nodes
// 1.10: D2Lang.0x6FC20CB8, 0x6FC20CBC, 0x6FC20CC0
static Unicode** sgpStrings;
static Unicode** sgpPatchStrings;
static Unicode** sgpExpansionStrings;
// Buffers holding the converted strings of each table
// 1.10: D2Lang.0x6FC20CC4, 0x6FC20CC8, 0x6FC20CCC
static Unicode* sgpStringsBuffer;
static Unicode* sgpPatchStringsBuffer;
static Unicode* sgpExpansionStringsBuffer;
// 1.10: D2Lang.0x6FC20CD8
static int sgnStringTablesRefCount;

struct D2NotTranslatedStringStrc
{
	Unicode* pString;							//0x00
	char* szReference;							//0x04
	D2NotTranslatedStringStrc* pNext;			//0x08
};

// Strings returned by D2LANG_GetTblIndex for unknown references
// 1.10: D2Lang.0x6FC20CB0
static D2NotTranslatedStringStrc* sgpNotTranslatedStrings;

// String indices of the localized suffixes used by STR_GroupUint64DigitsWithSuffix
enum D2StringTableSuffixIds
{
	STR_IDX_THOUSANDS_SUFFIX = 5328,
	STR_IDX_MILLIONS_SUFFIX = 5329,
	STR_IDX_BILLIONS_SUFFIX = 5330,
	STR_IDX_TRILLIONS_SUFFIX = 5331,
};

enum D2StringTableIndexBase
{
	STRING_TABLE_PATCH_BASE_INDEX = 10000,
	STRING_TABLE_EXPANSION_BASE_INDEX = 20000,
};

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

/**
 * 1.10: D2Lang.0x6FC12F50 (#10002)
 */
uint32_t __stdcall D2LANG_GetStringHash(const char* szString, uint32_t nHashTableSize)
{
	uint32_t nHash = 0;
	for (; *szString != '\0'; ++szString)
	{
		nHash = (nHash << 4) + (signed char)*szString;
		const uint32_t nHighBits = nHash & 0xF0000000;
		if (nHighBits != 0)
		{
			nHash = (nHash & 0x0FFFFFFF) ^ (nHighBits >> 24);
		}
	}

	return nHash % nHashTableSize;
}

static D2TblNodeStrc* GetTableNodes(D2TblHeaderStrc* pHeader)
{
	// The nodes come after the header and the array of node indices.
	uint16_t* pNodeIndices = (uint16_t*)(pHeader + 1);
	return (D2TblNodeStrc*)&pNodeIndices[pHeader->nNumElements];
}

/**
 * Loads a .tbl file and checks its integrity.
 *
 * 1.10: D2Lang.0x6FC13640
 */
static D2TblHeaderStrc* LoadStringTableFile(const char* szPath)
{
	D2TblHeaderStrc* pHeader = (D2TblHeaderStrc*)ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(ghArchive, szPath, nullptr);
	// Note: The original does not check if the file could be read.
	if (!pHeader)
	{
		return nullptr;
	}

	unsigned short usCRC;
	CRC16_CalculateChecksum(&usCRC, (const unsigned char*)pHeader, pHeader->dwIndexStart, pHeader->dwFileSize);
	D2_ASSERT(usCRC == pHeader->nCRC);

	D2TblNodeStrc* pNodes = GetTableNodes(pHeader);
	for (int i = 0; i < pHeader->nHashTableSize; ++i)
	{
		D2_ASSERT(pNodes[i].dwKeyOffset < pHeader->dwFileSize);
		D2_ASSERT(pNodes[i].dwStringOffset < pHeader->dwFileSize);
	}

	return pHeader;
}

/**
 * Converts all the strings of a table to Unicode.
 *
 * 1.10: Inline in D2LANG_LoadStrings
 */
static void ConvertStringTable(D2TblHeaderStrc* pHeader, Unicode*** pppStrings, Unicode** ppBuffer)
{
	Unicode** ppStrings = (Unicode**)D2_CALLOC(sizeof(Unicode*) * pHeader->nHashTableSize);
	*pppStrings = ppStrings;

	D2TblNodeStrc* pNodes = GetTableNodes(pHeader);

	int nTotalLength = 0;
	for (int i = 0; i < pHeader->nHashTableSize; ++i)
	{
		nTotalLength += Unicode::unicodeWidth((const char*)pHeader + pNodes[i].dwStringOffset, pNodes[i].nNameLen) + 1;
	}

	Unicode* pBuffer = (Unicode*)D2_ALLOC(sizeof(Unicode) * nTotalLength);
	*ppBuffer = pBuffer;

	for (int i = 0; i < pHeader->nHashTableSize; ++i)
	{
		ppStrings[i] = pBuffer;
		const char* szString = (const char*)pHeader + pNodes[i].dwStringOffset;
		const int nLength = Unicode::unicodeWidth(szString, pNodes[i].nNameLen) + 1;
		Unicode::toUnicode(ppStrings[i], szString, nLength);
		pBuffer += nLength;
	}
}

/**
 * Reads a localized suffix from the string table. The default value is
 * used if the string has more than one character.
 *
 * 1.10: Inline in D2LANG_LoadStrings
 */
static Unicode GetSuffixFromStringTable(short nStringIndex, Unicode wDefault)
{
	char szSuffix[5];
	Unicode::unicode2Win(szSuffix, D2LANG_GetStringFromTblIndex(nStringIndex), sizeof(szSuffix));
	if (strlen(szSuffix) > 1)
	{
		return wDefault;
	}

	return Unicode((signed char)szSuffix[0]);
}

/**
 * 1.10: D2Lang.0x6FC12F90 (#10000)
 */
BOOL __fastcall D2LANG_LoadStrings(HD2ARCHIVE hArchive, const char* szLanguage, BOOL bLoadExpansion)
{
	if (sghStringTable)
	{
		++sgnStringTablesRefCount;
		return TRUE;
	}

	char szLanguageCode[8] = {};
	if (szLanguage)
	{
		strcpy(szLanguageCode, szLanguage);
	}
	else
	{
		STRTABLE_GetLanguageCode(szLanguageCode, LANGUAGE_CODE_DIRECTORY);
	}

	const char* szFont = "LATIN";
	if (_stricmp(szLanguageCode, "JPN") == 0)
	{
		szFont = "JPN";
	}
	else if (_stricmp(szLanguageCode, "KOR") == 0)
	{
		szFont = "KOR";
	}
	else if (_stricmp(szLanguageCode, "POL") == 0)
	{
		szFont = "LATIN2";
	}
	else if (_stricmp(szLanguageCode, "RUS") == 0)
	{
		szFont = "CYR";
	}

	char szPath[MAX_PATH];
	sprintf(szPath, "data\\local\\font\\%s\\default.map", szFont);
	Unicode::loadSysMap(ghArchive, szPath);

	sprintf(szPath, "data\\local\\lng\\%s\\string.tbl", szLanguageCode);
	sghStringTable = LoadStringTableFile(szPath);
	if (!sghStringTable)
	{
		return FALSE;
	}
	ConvertStringTable(sghStringTable, &sgpStrings, &sgpStringsBuffer);
	++sgnStringTablesRefCount;

	sprintf(szPath, "data\\local\\lng\\%s\\patchstring.tbl", szLanguageCode);
	sghPatchStringTable = LoadStringTableFile(szPath);
	D2_ASSERT(sghPatchStringTable != NULL);
	ConvertStringTable(sghPatchStringTable, &sgpPatchStrings, &sgpPatchStringsBuffer);

	if (bLoadExpansion)
	{
		sprintf(szPath, "data\\local\\lng\\%s\\expansionstring.tbl", szLanguageCode);
		sghExpansionStringTable = LoadStringTableFile(szPath);
		D2_ASSERT(sghExpansionStringTable != NULL);
		ConvertStringTable(sghExpansionStringTable, &sgpExpansionStrings, &sgpExpansionStringsBuffer);
	}

	gwThousandsSuffix = GetSuffixFromStringTable(STR_IDX_THOUSANDS_SUFFIX, L'K');
	gwMillionsSuffix = GetSuffixFromStringTable(STR_IDX_MILLIONS_SUFFIX, L'M');
	gwBillionsSuffix = GetSuffixFromStringTable(STR_IDX_BILLIONS_SUFFIX, L'B');
	gwTrillionsSuffix = GetSuffixFromStringTable(STR_IDX_TRILLIONS_SUFFIX, L'T');

	return TRUE;
}

/**
 * 1.10: D2Lang.0x6FC13BE0 (#10001)
 */
void __fastcall D2LANG_FreeStrings()
{
	if (!sghStringTable)
	{
		return;
	}

	--sgnStringTablesRefCount;
	if (sgnStringTablesRefCount != 0)
	{
		return;
	}

	if (sgpStrings)
	{
		D2_FREE(sgpStringsBuffer);
		sgpStringsBuffer = nullptr;
		D2_FREE(sgpStrings);
		sgpStrings = nullptr;
	}
	D2_FREE(sghStringTable);
	sghStringTable = nullptr;

	if (sgpPatchStrings)
	{
		D2_FREE(sgpPatchStrings);
		sgpPatchStrings = nullptr;
	}
	if (sgpPatchStringsBuffer)
	{
		D2_FREE(sgpPatchStringsBuffer);
		sgpPatchStringsBuffer = nullptr;
	}
	if (sghPatchStringTable)
	{
		D2_FREE(sghPatchStringTable);
		sghPatchStringTable = nullptr;
	}

	if (sgpExpansionStrings)
	{
		D2_FREE(sgpExpansionStrings);
		sgpExpansionStrings = nullptr;
	}
	if (sgpExpansionStringsBuffer)
	{
		D2_FREE(sgpExpansionStringsBuffer);
		sgpExpansionStringsBuffer = nullptr;
	}
	if (sghExpansionStringTable)
	{
		D2_FREE(sghExpansionStringTable);
		sghExpansionStringTable = nullptr;
	}

	D2NotTranslatedStringStrc* pNotTranslatedString = sgpNotTranslatedStrings;
	while (pNotTranslatedString)
	{
		D2NotTranslatedStringStrc* pNext = pNotTranslatedString->pNext;
		D2_FREE(pNotTranslatedString->pString);
		D2_FREE(pNotTranslatedString->szReference);
		D2_FREE(pNotTranslatedString);
		pNotTranslatedString = pNext;
	}
	sgpNotTranslatedStrings = nullptr;

	Unicode::unloadSysMap();
}

/**
 * Returns the string of the node at the given index of the table.
 *
 * 1.10: D2Lang.0x6FC12E60
 */
static const Unicode* GetStringFromTable(D2TblHeaderStrc* pHeader, Unicode** ppStrings, unsigned short nIndex)
{
	if (nIndex >= pHeader->nNumElements)
	{
		FOG_Trace("%d string id requested but larger than number of elements:%d", nIndex, pHeader->nNumElements);
		nIndex = 500;
	}

	const uint16_t* pNodeIndices = (const uint16_t*)(pHeader + 1);
	const int nNodeIndex = pNodeIndices[nIndex];
	D2_ASSERT(nNodeIndex < pHeader->nHashTableSize);

	D2TblNodeStrc* pNode = &GetTableNodes(pHeader)[nNodeIndex];
	D2_ASSERT((uint8_t*)pNode < (uint8_t*)pHeader + pHeader->dwFileSize);
	D2_ASSERT(pNode->bUsed == TRUE);
	D2_ASSERT(ppStrings[nNodeIndex] != NULL);

	return ppStrings[nNodeIndex];
}

/**
 * 1.10: D2Lang.0x6FC13740 (#10004)
 */
const Unicode* __fastcall D2LANG_GetStringFromTblIndex(short nIndex)
{
	unsigned short nStringIndex = nIndex;

	if (nStringIndex >= STRING_TABLE_EXPANSION_BASE_INDEX)
	{
		if (!sghExpansionStringTable)
		{
			FOG_Trace("Requested string %d but expansion strings not loaded", nStringIndex);
			nStringIndex = 11078;
		}
		else if (const Unicode* pString = GetStringFromTable(sghExpansionStringTable, sgpExpansionStrings, nStringIndex - STRING_TABLE_EXPANSION_BASE_INDEX))
		{
			return pString;
		}
	}

	if (sghPatchStringTable && nStringIndex >= STRING_TABLE_PATCH_BASE_INDEX)
	{
		if (const Unicode* pString = GetStringFromTable(sghPatchStringTable, sgpPatchStrings, nStringIndex - STRING_TABLE_PATCH_BASE_INDEX))
		{
			return pString;
		}
	}

	D2_ASSERT(sghStringTable != NULL);
	return GetStringFromTable(sghStringTable, sgpStrings, nStringIndex);
}

/**
 * Looks up a string by its reference (key). Returns the index of the
 * string in the table, or -1 if the reference was not found.
 *
 * 1.10: D2Lang.0x6FC13A90
 */
static short FindStringInTable(D2TblHeaderStrc* pHeader, Unicode** ppStrings, const char* szReference, const Unicode** ppUnicode)
{
	D2TblNodeStrc* pNodes = GetTableNodes(pHeader);

	int nNodeIndex = D2LANG_GetStringHash(szReference, pHeader->nHashTableSize);
	for (uint32_t nAttempt = 0; nAttempt < pHeader->dwNumLoops; ++nAttempt)
	{
		D2TblNodeStrc* pNode = &pNodes[nNodeIndex];
		if (pNode->bUsed == TRUE && strcmp((const char*)pHeader + pNode->dwKeyOffset, szReference) == 0)
		{
			D2_ASSERT(ppStrings[nNodeIndex] != NULL);
			*ppUnicode = ppStrings[nNodeIndex];
			return pNode->nIndexNo;
		}

		nNodeIndex = (nNodeIndex + 1) % pHeader->nHashTableSize;
	}

	return -1;
}

/**
 * Returns a string for an unknown reference, "<reference> -not xlated call ken w".
 * The strings are kept until the string tables are freed.
 *
 * Vanilla bug: The last character of the string is lost in the
 * conversion to Unicode.
 *
 * 1.10: D2Lang.0x6FC137F0
 */
static Unicode* GetNotTranslatedString(const char* szReference)
{
	for (D2NotTranslatedStringStrc* pNotTranslatedString = sgpNotTranslatedStrings; pNotTranslatedString; pNotTranslatedString = pNotTranslatedString->pNext)
	{
		if (strcmp(pNotTranslatedString->szReference, szReference) == 0)
		{
			return pNotTranslatedString->pString;
		}
	}

	D2NotTranslatedStringStrc* pNotTranslatedString = (D2NotTranslatedStringStrc*)D2_ALLOC(sizeof(D2NotTranslatedStringStrc));
	pNotTranslatedString->pNext = sgpNotTranslatedStrings;
	sgpNotTranslatedStrings = pNotTranslatedString;

	pNotTranslatedString->szReference = (char*)D2_ALLOC(strlen(szReference) + 1);
	strcpy(pNotTranslatedString->szReference, szReference);

	static const char szNotTranslated[] = " -not xlated call ken w";
	const int nLength = strlen(szNotTranslated) + strlen(szReference);
	char* szString = (char*)D2_ALLOC(nLength + 1);
	strcpy(szString, szReference);
	strcat(szString, szNotTranslated);

	const int nUnicodeLength = Unicode::unicodeWidth(szString, nLength);
	pNotTranslatedString->pString = (Unicode*)D2_ALLOC(sizeof(Unicode) * (nUnicodeLength + 1));
	Unicode::toUnicode(pNotTranslatedString->pString, szString, nUnicodeLength);
	D2_FREE(szString);

	return pNotTranslatedString->pString;
}

/**
 * 1.10: D2Lang.0x6FC13960 (#10013)
 */
short __stdcall D2LANG_GetTblIndex(char* szReference, const Unicode** ppUnicode)
{
	D2_ASSERT(sghStringTable != NULL);
	D2_ASSERT(sghPatchStringTable != NULL);
	D2_ASSERT(szReference);

	if (szReference[0] == '\0')
	{
		static Unicode wEmptyString = 0;
		*ppUnicode = &wEmptyString;
		return 0;
	}

	short nIndex = FindStringInTable(sghPatchStringTable, sgpPatchStrings, szReference, ppUnicode);
	if (nIndex != -1)
	{
		return nIndex + STRING_TABLE_PATCH_BASE_INDEX;
	}

	if (sghExpansionStringTable)
	{
		nIndex = FindStringInTable(sghExpansionStringTable, sgpExpansionStrings, szReference, ppUnicode);
		if (nIndex != -1)
		{
			return nIndex + STRING_TABLE_EXPANSION_BASE_INDEX;
		}
	}

	nIndex = FindStringInTable(sghStringTable, sgpStrings, szReference, ppUnicode);
	if (nIndex == -1)
	{
		*ppUnicode = GetNotTranslatedString(szReference);
		return 0;
	}

	return nIndex;
}

/**
 * 1.10: D2Lang.0x6FC13BC0 (#10003)
 */
const Unicode* __fastcall D2LANG_GetStringByReferenceString(char* szReference)
{
	const Unicode* pUnicode = nullptr;
	D2LANG_GetTblIndex(szReference, &pUnicode);
	return pUnicode;
}
