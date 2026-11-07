#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

// Mod: extra columns of the game's .txt files, read outside the regular table loading (not part of the original game).
//
// Parses the columns listed in pTbl (a regular field table, "end" terminated) of DATA\GLOBAL\EXCEL\<szName>.txt into a
// new array of nRecordSize sized records, one per row, in row order. The .txt is always read, never the .bin, so the
// original records and .bin files keep their layout.
// Answers nullptr and sets *pRecordCount to 0 when the file is missing or has no column named szRequiredColumn.
// Free the array with D2_FREE_POOL(nullptr, ...).
void* __fastcall DATATBLS_LoadExtraTxtColumns(const char* szName, D2BinFieldStrc* pTbl, const char* szRequiredColumn, size_t nRecordSize, int* pRecordCount);
