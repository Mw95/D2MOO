#pragma once

#include <D2Dll.h>
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
	uint32_t dwStringOffset;					//0x07
	uint32_t dwKeyOffset;						//0x0B
	uint16_t nNameLen;							//0x0F
};

#pragma pack()

// Loads the string tables (string.tbl, expansionstring.tbl, patchstring.tbl)
D2FUNC_DLL(D2LANG, 10000, BOOL, __fastcall, (void* hArchive, BOOL bUnused), 0x0000/*TODO*/)					//D2LANG.#10000
// Frees the string tables
D2FUNC_DLL(D2LANG, 10001, void, __fastcall, (), 0x0000/*TODO*/)												//D2LANG.#10001
// Copies the 3 letters code of the current language (such as "ENG") to szLanguage
D2FUNC_DLL(D2LANG, 10006, void, __stdcall, (char* szLanguage, int32_t nType), 0x0000/*TODO*/)					//D2LANG.#10006
D2FUNC_DLL(D2LANG, GetStringByReferenceString, const Unicode*, __fastcall, (char* string), 0x3BC0)			//D2LANG.#10003
//1.14d: Game.0x524A30
D2FUNC_DLL(D2LANG, GetStringFromTblIndex, const Unicode*, __fastcall, (short index), 0x3740)					//D2LANG.#10004
D2FUNC_DLL(D2LANG, GetTblIndex, short, __stdcall, (char* szReference, const Unicode** pUnicode), 0x3960)		//D2LANG.#10013

