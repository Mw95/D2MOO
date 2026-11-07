#include "DataTbls/ExtraTxtColumns.h"

#include <Archive.h>
#include <Fog.h>

// Mod: extra .txt columns read outside the regular table loading. Not part of the original game.

// True when the header line (first line) of a tab separated .txt holds a column named szColumn.
static bool DATATBLS_TxtHasColumn(const char* pData, size_t nSize, const char* szColumn)
{
	const size_t nColumnLength = strlen(szColumn);
	size_t nStart = 0;
	for (size_t i = 0; i <= nSize; ++i)
	{
		const char c = i < nSize ? pData[i] : '\n';
		if (c == '\t' || c == '\r' || c == '\n')
		{
			if (i - nStart == nColumnLength && !_strnicmp(&pData[nStart], szColumn, nColumnLength))
			{
				return true;
			}

			if (c != '\t')
			{
				return false;
			}

			nStart = i + 1;
		}
	}

	return false;
}

// See ExtraTxtColumns.h. Parses the given columns of DATA\GLOBAL\EXCEL\<szName>.txt into a new array of nRecordSize sized records.
// Answers nullptr (and leaves *pRecordCount at 0) when the file or szRequiredColumn is missing.
void* __fastcall DATATBLS_LoadExtraTxtColumns(const char* szName, D2BinFieldStrc* pTbl, const char* szRequiredColumn, size_t nRecordSize, int* pRecordCount)
{
	*pRecordCount = 0;

	char szFilePath[MAX_PATH] = {};
	wsprintfA(szFilePath, "%s\\%s%s", "DATA\\GLOBAL\\EXCEL", szName, ".txt");

	size_t nDataSize = 0;
	void* pData = ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(nullptr, szFilePath, &nDataSize);
	if (!pData)
	{
		return nullptr;
	}

	if (!DATATBLS_TxtHasColumn((const char*)pData, nDataSize, szRequiredColumn))
	{
		D2_FREE(pData);
		return nullptr;
	}

	// Same sequence as DATATBLS_CompileTxt uses for .txt files.
	D2BinFileStrc* pBinFile = FOG_CreateBinFile(pData, nDataSize);
	const int nRecordCount = FOG_GetRecordCountFromBinFile(pBinFile);
	void* pRecords = nullptr;
	if (nRecordCount > 0)
	{
		pRecords = D2_CALLOC_POOL(nullptr, nRecordSize * nRecordCount);
		FOG_10207(pBinFile, pTbl, pRecords, nRecordCount, nRecordSize);
		*pRecordCount = nRecordCount;
	}
	FOG_FreeBinFile(pBinFile);

	return pRecords;
}
