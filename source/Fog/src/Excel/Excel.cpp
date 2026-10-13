#include <Fog.h>
#include <D2BitManip.h>
#include <Storm.h>

#include <climits>
#include <cstring>

#define EXCEL_MAX_CELLS 0x118
#define EXCEL_INVALID_COLUMN 0x7FFF
#define EXCEL_LINK_TABLE_GROWTH 0x40

// Fog.0x6FF75AD0
// Returned when a link index could not be found
static char gszUnknownLinkText[] = "???";

struct ExcelFieldHashEntry		// sizeof 0x0C
{
	ExcelFieldHashEntry* pNext;	// 0x00
	uint32_t dwHash;			// 0x04 Set to 0 once the field was found in the file
	D2BinFieldStrc* pField;		// 0x08
};

using ExcelKeyToWordCallback = uint16_t(__fastcall*)(char* szText);
using ExcelCustomLinkCallback = void(__fastcall*)(char* szText, void* pRecord, int nOffset, int nLength, int nRow, int nColumn);

static void EXCEL_SkipString(const char*& pData)
{
	pData += strlen(pData) + 1;
}

// Converts a code to a string, spaces are converted to null characters
static void EXCEL_CodeToString(uint32_t dwCode, char szString[5])
{
	for (int i = 0; i < 4; ++i)
	{
		const char nChar = (char)(dwCode >> (8 * i));
		szString[i] = nChar == ' ' ? '\0' : nChar;
	}
	szString[4] = '\0';
}

// Reads up to 4 characters of the current string as a code, padded with spaces.
static uint32_t EXCEL_ReadCode(const char*& pData)
{
	char szCode[4] = {};
	for (int i = 0; i < 4 && *pData; ++i)
	{
		szCode[i] = *pData++;
	}
	EXCEL_SkipString(pData);

	char szPaddedCode[4] = { ' ', ' ', ' ', ' ' };
	for (int i = 0; i < 4 && szCode[i]; ++i)
	{
		szPaddedCode[i] = szCode[i];
	}

	uint32_t dwCode;
	memcpy(&dwCode, szPaddedCode, sizeof(dwCode));
	return dwCode;
}

// Copies at most nMaxLength characters of the current string, the rest of it is skipped.
static void EXCEL_ReadString(const char*& pData, char* szDest, int nMaxLength)
{
	char* pDest = szDest;
	while (*pData && pDest < szDest + nMaxLength)
	{
		*pDest++ = *pData++;
	}
	*pDest = '\0';
	EXCEL_SkipString(pData);
}

// 1.10f: 0x6FF5AA60 (#10207)
// Compiles the records of a txt file into pTxt, using the column names to find the fields description.
void __stdcall FOG_10207(D2BinFileStrc* pBinFile, D2BinFieldStrc* pBinField, void* pTxt, int nRecordCount, int nRecordSize)
{
	D2_ASSERT(nRecordCount > 0);
	D2_ASSERT(nRecordSize > 0);

	// Note: the original code mixes the length of the current and next field in this check
	for (D2BinFieldStrc* pField = pBinField; pField->nFieldType != TXTFIELD_NONE; ++pField)
	{
		if (pField->nFieldType == TXTFIELD_UNKNOWN1)
		{
			for (int i = 1; i < pField->nFieldLength; ++i)
			{
				D2_ASSERTM(pField[1].nFieldType == TXTFIELD_UNKNOWN1, "ptData->nType == EXCEL_TYPE_BYTE_OR");
				++pField;
			}
		}
	}

	// Hash the field names
	ExcelFieldHashEntry* pHashTable[256] = {};
	ExcelFieldHashEntry tHashEntries[EXCEL_MAX_CELLS];
	uint32_t nFieldsCount = 0;
	for (D2BinFieldStrc* pField = pBinField; pField->nFieldType != TXTFIELD_NONE; ++pField)
	{
		D2_ASSERTM(nFieldsCount < EXCEL_MAX_CELLS, "nameCount < EXCELMAXCELLS");
		ExcelFieldHashEntry* pEntry = &tHashEntries[nFieldsCount++];
		const uint32_t dwHash = SStrHash(pField->szFieldName, 0, 0);
		pEntry->dwHash = dwHash;
		pEntry->pField = pField;

		const uint32_t nBucket = (((((dwHash & 0xFF0000) ^ (dwHash >> 8)) >> 8) ^ (dwHash & 0xFF00)) >> 8) ^ (dwHash & 0xFF);
		pEntry->pNext = pHashTable[nBucket];
		pHashTable[nBucket] = pEntry;
	}

	// Map each column of the file to a field, then append the fields not present in the file
	uint16_t nColumnFields[EXCEL_MAX_CELLS * 2];
	int nMappedColumns = 0;
	const char* szColumnName = (const char*)pBinFile->pDataBuffer;
	for (int nColumn = 0; nColumn < pBinFile->nCellCount; ++nColumn)
	{
		const uint32_t dwHash = SStrHash(szColumnName, 0, 0);
		const uint32_t nBucket = (((((dwHash & 0xFF0000) ^ (dwHash >> 8)) >> 8) ^ (dwHash & 0xFF00)) >> 8) ^ (dwHash & 0xFF);
		uint16_t nFieldIndex = EXCEL_INVALID_COLUMN;
		for (ExcelFieldHashEntry* pEntry = pHashTable[nBucket]; pEntry; pEntry = pEntry->pNext)
		{
			if (pEntry->dwHash == dwHash && !SStrCmpI(szColumnName, pEntry->pField->szFieldName, 0x7FFFFFFF))
			{
				pEntry->dwHash = 0;
				nFieldIndex = (uint16_t)(pEntry->pField - pBinField);
				break;
			}
		}
		nColumnFields[nMappedColumns++] = nFieldIndex;
		EXCEL_SkipString(szColumnName);
	}

	for (uint32_t i = 0; i < nFieldsCount; ++i)
	{
		if (tHashEntries[i].dwHash)
		{
			nColumnFields[nMappedColumns++] = (uint16_t)(tHashEntries[i].pField - pBinField);
		}
	}

	// Fields building indices must be processed for all records first, as other fields of the same file may reference them
	BOOL bNeedsIndexPass = FALSE;
	for (int nColumn = 0; nColumn < pBinFile->nCellCount; ++nColumn)
	{
		if (nColumnFields[nColumn] != EXCEL_INVALID_COLUMN)
		{
			switch (pBinField[nColumnFields[nColumn]].nFieldType)
			{
			case TXTFIELD_ASCIITOCODE:
			case TXTFIELD_UNKNOWN4:
			case TXTFIELD_UNKNOWN5:
			case TXTFIELD_UNKNOWN6:
			case TXTFIELD_NAMETOINDEX:
			case TXTFIELD_NAMETOINDEX2:
				bNeedsIndexPass = TRUE;
				break;
			default:
				break;
			}
		}
	}

	if (bNeedsIndexPass)
	{
		const char* pData = (const char*)pBinFile->pData;
		uint8_t* pRecord = (uint8_t*)pTxt;
		for (int nRow = 0; nRow < pBinFile->nRecordCount; ++nRow)
		{
			for (int nColumn = 0; nColumn < pBinFile->nCellCount; ++nColumn)
			{
				if (nColumnFields[nColumn] == EXCEL_INVALID_COLUMN)
				{
					EXCEL_SkipString(pData);
					continue;
				}

				D2BinFieldStrc* pField = &pBinField[nColumnFields[nColumn]];
				uint8_t* pFieldData = pRecord + pField->nFieldOffset;
				switch (pField->nFieldType)
				{
				case TXTFIELD_ASCIITOCODE:
				case TXTFIELD_UNKNOWN4:
				case TXTFIELD_UNKNOWN5:
				{
					const uint32_t dwCode = EXCEL_ReadCode(pData);
					const int nIndex = FOG_10215(*(D2TxtLinkStrc**)pField->pLinkField, dwCode);
					// Note: the code itself is stored, the index is only checked
					if (pField->nFieldType == TXTFIELD_ASCIITOCODE)
					{
						*(uint32_t*)pFieldData = dwCode;
					}
					else if (pField->nFieldType == TXTFIELD_UNKNOWN4)
					{
						D2_ASSERTM(nIndex <= UCHAR_MAX, "nIndex <= UCHAR_MAX");
						*pFieldData = (uint8_t)dwCode;
					}
					else
					{
						D2_ASSERTM(nIndex <= USHRT_MAX, "nIndex <= USHRT_MAX");
						*(uint16_t*)pFieldData = (uint16_t)dwCode;
					}
					break;
				}
				case TXTFIELD_UNKNOWN6:
					EXCEL_ReadString(pData, (char*)pFieldData, pField->nFieldLength - 1);
					FOG_10216_AddRecordToLinkingTable(*(D2TxtLinkStrc**)pField->pLinkField, (const char*)pFieldData);
					break;
				case TXTFIELD_NAMETOINDEX:
				case TXTFIELD_NAMETOINDEX2:
				{
					char szName[32];
					EXCEL_ReadString(pData, szName, sizeof(szName) - 1);
					D2TxtLinkStrc* pLink = *(D2TxtLinkStrc**)pField->pLinkField;
					D2_ASSERT(pLink);
					D2_ASSERT(!pLink->pTbl);
					int nIndex = FOG_GetRowFromTxt(pLink, szName, 0);
					if (nIndex < 0)
					{
						nIndex = FOG_10216_AddRecordToLinkingTable(pLink, szName);
					}

					if (pField->nFieldType == TXTFIELD_NAMETOINDEX)
					{
						*(uint16_t*)pFieldData = (uint16_t)nIndex;
					}
					else
					{
						*(uint32_t*)pFieldData = nIndex;
					}
					break;
				}
				default:
					EXCEL_SkipString(pData);
					break;
				}
			}

			D2_ASSERTM(*pData == '\n', "*data == SYM_EOL");
			++pData;
			pRecord += nRecordSize;
		}
	}

	const char* pData = (const char*)pBinFile->pData;
	uint8_t* pRecord = (uint8_t*)pTxt;
	for (int nRow = 0; nRow < pBinFile->nRecordCount; ++nRow)
	{
		int nColumn = 0;
		for (; nColumn < pBinFile->nCellCount; ++nColumn)
		{
			if (nColumnFields[nColumn] == EXCEL_INVALID_COLUMN)
			{
				EXCEL_SkipString(pData);
				continue;
			}

			D2BinFieldStrc* pField = &pBinField[nColumnFields[nColumn]];
			uint8_t* pFieldData = pRecord + pField->nFieldOffset;
			const char* szValue = pData;
			switch (pField->nFieldType)
			{
			case TXTFIELD_ASCII:
			case TXTFIELD_BYTE2:
				// Note: the null terminator is written after nFieldLength characters if the string is too long
				EXCEL_ReadString(pData, (char*)pFieldData, pField->nFieldLength);
				break;

			case TXTFIELD_DWORD:
			case TXTFIELD_WORD:
			case TXTFIELD_BYTE:
			case TXTFIELD_UNKNOWN1:
			case TXTFIELD_UNKNOWN2:
			case TXTFIELD_DWORD2:
			case TXTFIELD_BIT:
			{
				// Note: there is no validation of the characters
				if (*pData == '-')
				{
					++pData;
				}
				uint32_t nUnsignedValue = 0;
				while (*pData)
				{
					nUnsignedValue = nUnsignedValue * 10 + *pData - '0';
					++pData;
				}
				if (*szValue == '-')
				{
					nUnsignedValue = 0 - nUnsignedValue;
				}
				const int32_t nValue = (int32_t)nUnsignedValue;
				++pData;

				switch (pField->nFieldType)
				{
				case TXTFIELD_DWORD:
				case TXTFIELD_DWORD2:
					*(int32_t*)pFieldData = nValue;
					break;
				case TXTFIELD_WORD:
					*(uint16_t*)pFieldData = (uint16_t)nValue;
					break;
				case TXTFIELD_BYTE:
				case TXTFIELD_UNKNOWN2:
					*pFieldData = (uint8_t)nValue;
					break;
				case TXTFIELD_UNKNOWN1:
					// Empty values are ignored
					if (szValue + 1 != pData)
					{
						*pFieldData = (uint8_t)nValue;
					}
					break;
				case TXTFIELD_BIT:
					// The field length is the bit to set
					if (nValue)
					{
						BITMANIP_SetBitState(pFieldData, pField->nFieldLength);
					}
					else
					{
						BITMANIP_MaskBitstate(pFieldData, pField->nFieldLength);
					}
					break;
				default:
					break;
				}
				break;
			}

			case TXTFIELD_RAW:
			{
				const uint32_t dwCode = EXCEL_ReadCode(pData);
				memcpy(pFieldData, &dwCode, sizeof(dwCode));
				break;
			}

			case TXTFIELD_UNKNOWN3:
			case TXTFIELD_CODETOBYTE:
			case TXTFIELD_CODETOWORD:
			{
				const uint32_t dwCode = EXCEL_ReadCode(pData);
				const int nIndex = FOG_GetLinkIndex(*(D2TxtLinkStrc**)pField->pLinkField, dwCode, TRUE);
				if (pField->nFieldType == TXTFIELD_UNKNOWN3)
				{
					*(int32_t*)pFieldData = nIndex;
				}
				else if (pField->nFieldType == TXTFIELD_CODETOBYTE)
				{
					*pFieldData = (uint8_t)nIndex;
				}
				else
				{
					*(uint16_t*)pFieldData = (uint16_t)nIndex;
				}
				break;
			}

			case TXTFIELD_NAMETODWORD:
			case TXTFIELD_NAMETOWORD:
			case TXTFIELD_NAMETOWORD2:
			{
				char szName[32];
				EXCEL_ReadString(pData, szName, sizeof(szName) - 1);
				const int nIndex = FOG_GetRowFromTxt(*(D2TxtLinkStrc**)pField->pLinkField, szName, TRUE);
				if (pField->nFieldType == TXTFIELD_NAMETODWORD)
				{
					*(int32_t*)pFieldData = nIndex;
				}
				else if (pField->nFieldType == TXTFIELD_NAMETOWORD)
				{
					*(uint16_t*)pFieldData = (uint16_t)nIndex;
				}
				else
				{
					*pFieldData = (uint8_t)nIndex;
				}
				break;
			}

			case TXTFIELD_KEYTOWORD:
			{
				char szKey[257];
				EXCEL_ReadString(pData, szKey, 256);
				if (ExcelKeyToWordCallback pCallback = (ExcelKeyToWordCallback)pField->pLinkField)
				{
					*(uint16_t*)pFieldData = pCallback(szKey);
				}
				break;
			}

			case TXTFIELD_CUSTOMLINK:
			case TXTFIELD_UNKNOWN7:
			case TXTFIELD_CALCTODWORD:
			{
				char szText[257];
				EXCEL_ReadString(pData, szText, 256);
				if (ExcelCustomLinkCallback pCallback = (ExcelCustomLinkCallback)pField->pLinkField)
				{
					pCallback(szText, pRecord, pField->nFieldOffset, pField->nFieldLength, nRow, nColumn);
				}
				break;
			}

			default:
				// Already handled by the index pass
				EXCEL_SkipString(pData);
				break;
			}
		}

		// Default values for the fields that are not in the file
		for (; nColumn < nMappedColumns; ++nColumn)
		{
			D2BinFieldStrc* pField = &pBinField[nColumnFields[nColumn]];
			uint8_t* pFieldData = pRecord + pField->nFieldOffset;
			switch (pField->nFieldType)
			{
			case TXTFIELD_ASCII:
			case TXTFIELD_BYTE:
			case TXTFIELD_UNKNOWN1:
			case TXTFIELD_UNKNOWN2:
			case TXTFIELD_BYTE2:
			case TXTFIELD_UNKNOWN4:
			case TXTFIELD_UNKNOWN6:
				*pFieldData = 0;
				break;
			case TXTFIELD_DWORD:
			case TXTFIELD_DWORD2:
			case TXTFIELD_RAW:
			case TXTFIELD_ASCIITOCODE:
			case TXTFIELD_NAMETOINDEX2:
				*(uint32_t*)pFieldData = 0;
				break;
			case TXTFIELD_WORD:
			case TXTFIELD_UNKNOWN5:
			case TXTFIELD_NAMETOINDEX:
			case TXTFIELD_KEYTOWORD:
				*(uint16_t*)pFieldData = 0;
				break;
			case TXTFIELD_UNKNOWN3:
			case TXTFIELD_NAMETODWORD:
				*(uint32_t*)pFieldData = 0xFFFFFFFF;
				break;
			case TXTFIELD_CODETOBYTE:
			case TXTFIELD_NAMETOWORD2:
				*pFieldData = 0xFF;
				break;
			case TXTFIELD_CODETOWORD:
			case TXTFIELD_NAMETOWORD:
				*(uint16_t*)pFieldData = 0xFFFF;
				break;
			case TXTFIELD_CUSTOMLINK:
			case TXTFIELD_UNKNOWN7:
			case TXTFIELD_CALCTODWORD:
				if (ExcelCustomLinkCallback pCallback = (ExcelCustomLinkCallback)pField->pLinkField)
				{
					pCallback(nullptr, pRecord, pField->nFieldOffset, pField->nFieldLength, nRow, nColumn);
				}
				break;
			default:
				break;
			}
		}

		D2_ASSERTM(*pData == '\n', "*data == SYM_EOL");
		++pData;
		pRecord += nRecordSize;
	}
}

// 1.10f: 0x6FF5A8B0 (#10208)
// Parses a tab separated file in place. Rows starting with "Expansion" are removed.
// Returns nullptr and frees pDataBuffer if the file has no records.
D2BinFileStrc* __stdcall FOG_CreateBinFile(void* pDataBuffer, int nBufferSize)
{
	D2BinFileStrc* pBinFile = (D2BinFileStrc*)FOG_AllocPool(nullptr, sizeof(D2BinFileStrc), __FILE__, __LINE__, 0);
	char* pData = (char*)pDataBuffer;
	char* pEnd = pData + nBufferSize;
	pBinFile->pDataBuffer = (uint8_t*)pDataBuffer;
	pBinFile->pData = nullptr;
	pBinFile->nRecordCount = 0;
	pBinFile->nCellCount = 0;

	// Header
	BOOL bHasRecords = FALSE;
	while (pData < pEnd)
	{
		const char nChar = *pData++;
		if (nChar == '\t')
		{
			pData[-1] = '\0';
			++pBinFile->nCellCount;
		}
		else if (nChar == '\r')
		{
			pData[-1] = '\0';
			D2_ASSERTM(*pData == '\n', "*data == SYM_EOL");
			++pData;
			++pBinFile->nCellCount;
			bHasRecords = pData < pEnd;
			break;
		}
	}

	if (!bHasRecords)
	{
		FOG_Free(pBinFile->pDataBuffer, __FILE__, __LINE__, 0);
		FOG_FreePool(nullptr, pBinFile, __FILE__, __LINE__, 0);
		return nullptr;
	}

	D2_ASSERTM(pBinFile->nCellCount <= EXCEL_MAX_CELLS, "file->nCellCount <= EXCELMAXCELLS");

	// Records
	pBinFile->pData = (uint8_t*)pData;
	do
	{
		char* pRecordStart = pData;
		while (pData < pEnd)
		{
			const char nChar = *pData++;
			if (nChar == '\t')
			{
				pData[-1] = '\0';
			}
			else if (nChar == '\r')
			{
				pData[-1] = '\0';
				D2_ASSERTM(*pData == '\n', "*data == SYM_EOL");
				++pData;
				++pBinFile->nRecordCount;
				break;
			}
		}

		if (!SStrCmp(pRecordStart, "Expansion", 10))
		{
			// Remove the separator row
			--pBinFile->nRecordCount;
			SMemCopy(pRecordStart, pData, pEnd - pData);
			pEnd -= pData - pRecordStart;
			pData = pRecordStart;
		}
	}
	while (pData < pEnd);

	return pBinFile;
}

// 1.10f: 0x6FF5AA10 (#10209)
void __stdcall FOG_FreeBinFile(D2BinFileStrc* pBinFile)
{
	FOG_Free(pBinFile->pDataBuffer, __FILE__, __LINE__, 0);
	FOG_FreePool(nullptr, pBinFile, __FILE__, __LINE__, 0);
}

// 1.10f: 0x6FF5AA50 (#10210)
int __stdcall FOG_GetRecordCountFromBinFile(D2BinFileStrc* pBinFile)
{
	return pBinFile->nRecordCount;
}

// 1.10f: 0x6FF5B720 (#10211)
void* __stdcall FOG_AllocLinker(const char* szFile, int nLine)
{
	D2TxtLinkStrc* pLink = (D2TxtLinkStrc*)FOG_AllocPool(nullptr, sizeof(D2TxtLinkStrc), szFile, nLine, 0);
	pLink->nRecords = 0;
	pLink->nAllocatedCells = 0;
	pLink->pTbl = nullptr;
	pLink->pFirstNode = nullptr;
	return pLink;
}

// 1.10f: 0x6FF5B7D0
static void EXCEL_FreeLinkNode(D2TxtLinkNodeStrc* pNode)
{
	if (pNode->pLeft)
	{
		EXCEL_FreeLinkNode(pNode->pLeft);
	}
	if (pNode->pRight)
	{
		EXCEL_FreeLinkNode(pNode->pRight);
	}
	FOG_FreePool(nullptr, pNode, __FILE__, __LINE__, 0);
}

// 1.10f: 0x6FF5B750 (#10212)
void __stdcall FOG_FreeLinker(void* pLinker)
{
	D2TxtLinkStrc* pLink = (D2TxtLinkStrc*)pLinker;
	if (!pLink)
	{
		return;
	}

	if (pLink->pFirstNode)
	{
		EXCEL_FreeLinkNode(pLink->pFirstNode);
	}

	if (pLink->pTbl)
	{
		FOG_FreePool(nullptr, pLink->pTbl, __FILE__, __LINE__, 0);
	}

	FOG_FreePool(nullptr, pLink, __FILE__, __LINE__, 0);
}

// 1.10f: 0x6FF5B810 (#10213)
// Returns the index of the code, or -1 if not found.
int __stdcall FOG_GetLinkIndex(void* pLinker, uint32_t dwCode, BOOL bLogError)
{
	D2TxtLinkStrc* pLink = (D2TxtLinkStrc*)pLinker;
	int nHigh = pLink->nRecords;
	D2TxtLinkTblStrc* pTbl = pLink->pTbl;
	if (!nHigh || !pTbl)
	{
		FOG_Trace("Invalid index for linked field");
	}

	int nLow = 0;
	while (nLow < nHigh)
	{
		const int nMiddle = nLow + (nHigh - nLow) / 2;
		if (dwCode > pTbl[nMiddle].dwCode)
		{
			nLow = nMiddle + 1;
		}
		else if (dwCode < pTbl[nMiddle].dwCode)
		{
			nHigh = nMiddle;
		}
		else
		{
			return pTbl[nMiddle].nLinkIndex;
		}
	}

	// Codes made of spaces only are considered empty
	if (bLogError && dwCode > 0x202020A0)
	{
		char szCode[5];
		EXCEL_CodeToString(dwCode, szCode);
		FOG_Trace("Failed to find code '%s' in index", szCode);
	}
	return -1;
}

// 1.10f: 0x6FF5B8F0 (#10214)
// Copies the code of the index into szString (5 characters). Returns whether the index was found.
int __stdcall FOG_GetStringFromLinkIndex(void* pLinker, int nIndex, char* szString)
{
	D2TxtLinkStrc* pLink = (D2TxtLinkStrc*)pLinker;
	if (!pLink->pTbl || nIndex < 0 || nIndex >= pLink->nRecords)
	{
		return FALSE;
	}

	for (int i = 0; i < pLink->nRecords; ++i)
	{
		if (pLink->pTbl[i].nLinkIndex == nIndex)
		{
			EXCEL_CodeToString(pLink->pTbl[i].dwCode, szString);
			return TRUE;
		}
	}
	return FALSE;
}

// 1.10f: 0x6FF5B990 (#10215)
// Adds a code to the code index and returns its index.
// If the code already exists, the next code value is used instead.
int __stdcall FOG_10215(void* pBin, int a2)
{
	D2TxtLinkStrc* pLink = (D2TxtLinkStrc*)pBin;
	const uint32_t dwRequestedCode = (uint32_t)a2;
	D2_ASSERTM(pLink, "hIndex");
	D2_ASSERTM(!pLink->pFirstNode, "!ptIndex->pStrTbl");

	if (pLink->nAllocatedCells <= pLink->nRecords)
	{
		const int nNewAllocatedCells = pLink->nAllocatedCells + EXCEL_LINK_TABLE_GROWTH;
		pLink->pTbl = (D2TxtLinkTblStrc*)FOG_ReallocPool(nullptr, pLink->pTbl, nNewAllocatedCells * sizeof(D2TxtLinkTblStrc), __FILE__, __LINE__, 0);
		memset(&pLink->pTbl[pLink->nAllocatedCells], 0, EXCEL_LINK_TABLE_GROWTH * sizeof(D2TxtLinkTblStrc));
		pLink->nAllocatedCells = nNewAllocatedCells;
	}

	uint32_t dwCode = dwRequestedCode;
	int nLow = 0;
	int nHigh = pLink->nRecords;
	while (nLow < nHigh)
	{
		const int nMiddle = nLow + (nHigh - nLow) / 2;
		if (dwCode > pLink->pTbl[nMiddle].dwCode)
		{
			nLow = nMiddle + 1;
		}
		else if (dwCode < pLink->pTbl[nMiddle].dwCode)
		{
			nHigh = nMiddle;
		}
		else
		{
			if (dwCode == dwRequestedCode && dwCode > 0x202020A0)
			{
				char szCode[5];
				EXCEL_CodeToString(dwCode, szCode);
				FOG_Trace("Duplicate code index '%s'", szCode);
			}
			// Try again with the next code
			++dwCode;
			nLow = 0;
			nHigh = pLink->nRecords;
		}
	}

	if (nLow < pLink->nRecords)
	{
		memmove(&pLink->pTbl[nLow + 1], &pLink->pTbl[nLow], (pLink->nRecords - nLow) * sizeof(D2TxtLinkTblStrc));
	}

	pLink->pTbl[nLow].dwCode = dwCode;
	pLink->pTbl[nLow].nLinkIndex = pLink->nRecords;
	++pLink->nRecords;
	return pLink->pTbl[nLow].nLinkIndex;
}

// 1.10f: 0x6FF5BD00
// Inserts the node in the tree, or frees it if a node with the same text exists.
static void EXCEL_InsertLinkNode(D2TxtLinkNodeStrc** ppRoot, D2TxtLinkNodeStrc* pNewNode)
{
	D2TxtLinkNodeStrc** ppNode = ppRoot;
	while (D2TxtLinkNodeStrc* pNode = *ppNode)
	{
		const int nComparison = strcmp(pNewNode->szText, pNode->szText);
		if (nComparison < 0)
		{
			ppNode = &pNode->pLeft;
		}
		else if (nComparison > 0)
		{
			ppNode = &pNode->pRight;
		}
		else
		{
			FOG_Trace("Duplicate string index '%s'", pNewNode->szText);
			FOG_FreePool(nullptr, pNewNode, __FILE__, __LINE__, 0);
			return;
		}
	}
	*ppNode = pNewNode;
}

// 1.10f: 0x6FF5BD80 (#10216)
// Adds a string to the string index (case insensitive), and returns its index.
// Note: the record count is incremented even if the string already exists.
int __stdcall FOG_10216_AddRecordToLinkingTable(void* pBin, const char* a2)
{
	D2TxtLinkStrc* pLink = (D2TxtLinkStrc*)pBin;
	D2_ASSERTM(pLink, "hIndex");
	D2_ASSERTM(!pLink->pTbl, "!ptIndex->pTbl");

	D2TxtLinkNodeStrc* pNode = (D2TxtLinkNodeStrc*)FOG_AllocPool(nullptr, sizeof(D2TxtLinkNodeStrc), __FILE__, __LINE__, 0);
	memset(pNode, 0, sizeof(*pNode));
	SStrCopy(pNode->szText, a2, sizeof(pNode->szText));
	FOG_ToLowerASCII(pNode->szText, sizeof(pNode->szText));
	pNode->nLinkIndex = pLink->nRecords;
	EXCEL_InsertLinkNode(&pLink->pFirstNode, pNode);
	return pLink->nRecords++;
}

// 1.10f: 0x6FF5BC20 (#10217)
// Returns the index of the string (case insensitive), or -1 if not found.
int __stdcall FOG_GetRowFromTxt(void* pBin, char* szText, int nColumn)
{
	D2TxtLinkStrc* pLink = (D2TxtLinkStrc*)pBin;
	const BOOL bLogError = nColumn;

	char szLowerText[32];
	SStrCopy(szLowerText, szText, sizeof(szLowerText));
	FOG_ToLowerASCII(szLowerText, sizeof(szLowerText));

	D2TxtLinkNodeStrc* pNode = pLink->pFirstNode;
	D2_ASSERTM(!pLink->nRecords || pNode, "!ptIndex->nSize || pNode");
	while (pNode)
	{
		const int nComparison = strcmp(szLowerText, pNode->szText);
		if (nComparison == 0)
		{
			return pNode->nLinkIndex;
		}
		pNode = nComparison < 0 ? pNode->pLeft : pNode->pRight;
	}

	if (bLogError && szText[0] && szText[0] != '*')
	{
		FOG_Trace("Failed to find string '%s' in index", szText);
	}
	return -1;
}

// 1.10f: 0x6FF5BBD0
static D2TxtLinkNodeStrc* EXCEL_FindLinkNodeByIndex(D2TxtLinkNodeStrc* pNode, int nIndex)
{
	if (!pNode)
	{
		return (D2TxtLinkNodeStrc*)gszUnknownLinkText;
	}

	if (pNode->nLinkIndex == nIndex)
	{
		return pNode;
	}

	if (pNode->pLeft)
	{
		D2TxtLinkNodeStrc* pFound = EXCEL_FindLinkNodeByIndex(pNode->pLeft, nIndex);
		if (pFound != (D2TxtLinkNodeStrc*)gszUnknownLinkText)
		{
			return pFound;
		}
	}

	if (pNode->pRight)
	{
		D2TxtLinkNodeStrc* pFound = EXCEL_FindLinkNodeByIndex(pNode->pRight, nIndex);
		if (pFound != (D2TxtLinkNodeStrc*)gszUnknownLinkText)
		{
			return pFound;
		}
	}

	return (D2TxtLinkNodeStrc*)gszUnknownLinkText;
}

// 1.10f: 0x6FF5BB20 (#10255)
// Returns the string of the index, or "???" if not found.
char* __stdcall FOG_10255(void* pLinker, int nId, int a3)
{
	D2TxtLinkStrc* pLink = (D2TxtLinkStrc*)pLinker;
	const BOOL bLogError = a3;
	if (!pLink)
	{
		if (bLogError)
		{
			FOG_Trace("null index");
		}
		return gszUnknownLinkText;
	}

	if (nId >= 0 && nId < pLink->nRecords)
	{
		char* szText = (char*)EXCEL_FindLinkNodeByIndex(pLink->pFirstNode, nId);
		if (szText != gszUnknownLinkText)
		{
			return szText;
		}

		if (!bLogError)
		{
			return szText;
		}
	}

	if (bLogError)
	{
		FOG_Trace("index out of bounds");
	}
	return gszUnknownLinkText;
}
