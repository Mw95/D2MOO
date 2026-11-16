#pragma once

#include <D2Dll.h>
#include <D2BasicTypes.h>
#include <cstdint>

#pragma pack(1)

struct D2LANG_DLL_DECL Unicode;

struct D2TblHeaderStrc
{
	uint16_t nCRC;								//0x00
	uint16_t nNumElements;						//0x02
	int32_t nHashTableSize;						//0x04
	uint8_t nVersion;							//0x08
	uint32_t dwIndexStart;						//0x09
	uint32_t dwNumLoops;						//0x0D
	uint32_t dwFileSize;						//0x11
};

struct D2TblNodeStrc
{
	uint8_t bUsed;								//0x00
	uint16_t nIndexNo;							//0x01
	uint32_t dwHashValue;						//0x03
	uint32_t dwKeyOffset;						//0x07 offset of the key string, compared by the find-by-key lookup
	uint32_t dwStringOffset;					//0x0B offset of the localized string (nNameLen bytes)
	uint16_t nNameLen;							//0x0F
};

#pragma pack()

struct HD2ARCHIVE__;

// Loads the string tables (string.tbl, patchstring.tbl and, if bLoadExpansion is set, expansionstring.tbl) of the given
// language (e.g. "ENG"), or of the language from STRTABLE_GetLanguage if szLanguage is NULL. hArchive is unused.
// Calls are reference counted, see D2LANG_FreeStrings.
D2FUNC_DLL(D2LANG, LoadStrings, BOOL, __fastcall, (struct HD2ARCHIVE__* hArchive, const char* szLanguage, BOOL bLoadExpansion), 0x2F90)	//D2LANG.#10000
D2FUNC_DLL(D2LANG, FreeStrings, void, __fastcall, (), 0x3BE0)																					//D2LANG.#10001
// Hash function of the string tables keys
D2FUNC_DLL(D2LANG, GetStringHash, uint32_t, __stdcall, (const char* szString, uint32_t nHashTableSize), 0x2F50)								//D2LANG.#10002
D2FUNC_DLL(D2LANG, GetStringByReferenceString, const Unicode*, __fastcall, (char* string), 0x3BC0)			//D2LANG.#10003
//1.14d: Game.0x524A30
D2FUNC_DLL(D2LANG, GetStringFromTblIndex, const Unicode*, __fastcall, (short index), 0x3740)					//D2LANG.#10004
D2FUNC_DLL(D2LANG, GetTblIndex, short, __stdcall, (char* szReference, const Unicode** pUnicode), 0x3960)		//D2LANG.#10013
