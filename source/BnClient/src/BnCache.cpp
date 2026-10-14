#include "BnCache.h"

#include <cctype>
#include <cstdlib>
#include <cstring>

#include <Fog.h>
#include <Storm.h>

#include "BnLog.h"


#pragma warning (disable: 28159)


CRITICAL_SECTION gtBnCacheLock;
BnCacheHeader* gpBnCacheHeader;
BnCacheBlockEntry* gpBnCacheBlockTable;
uint32_t* gpBnCacheCryptTable;
BnCacheHashEntry* gpBnCacheHashTable;
BOOL gbBnCacheOpen;
FILETIME gtBnCacheCurrentTime;
uint32_t gnBnCacheCurrentTimeOffset;
DWORD gdwBnCacheCurrentTimeTick;

HANDLE ghBnCacheFile = INVALID_HANDLE_VALUE;


//Bnclient.0x6FF19930
static const struct BnCacheCRC32Table
{
	uint32_t pTable[256];

	constexpr BnCacheCRC32Table() : pTable()
	{
		for (uint32_t i = 0; i < 256; ++i)
		{
			uint32_t nValue = i;
			for (int j = 0; j < 8; ++j)
			{
				nValue = (nValue & 1) ? (nValue >> 1) ^ 0xEDB88320 : nValue >> 1;
			}
			pTable[i] = nValue;
		}
	}
} gtBnCacheCRC32Table;


//Bnclient.0x6FF08BD0
static void __cdecl BNCACHE_DeleteLock()
{
	DeleteCriticalSection(&gtBnCacheLock);
}

//Bnclient.0x6FF08BB0
static void __cdecl BNCACHE_InitializeLock()
{
	InitializeCriticalSection(&gtBnCacheLock);
	atexit(BNCACHE_DeleteLock);
}

static const struct BnCacheStaticInitializer
{
	BnCacheStaticInitializer()
	{
		BNCACHE_InitializeLock();
	}
} gtBnCacheStaticInitializer;

// Inlined helpers

static uint32_t BNCACHE_ComputeCRC(const void* buffer, uint32_t len)
{
	D2_ASSERT(buffer || !len);
	if (!buffer && len)
	{
		SErrSetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}

	uint32_t nCRC = 0xFFFFFFFF;
	const uint8_t* pBytes = (const uint8_t*)buffer;
	for (uint32_t i = 0; i < len; ++i)
	{
		nCRC = gtBnCacheCRC32Table.pTable[(nCRC & 0xFF) ^ pBytes[i]] ^ (nCRC >> 8);
	}
	return ~nCRC;
}

static void BNCACHE_PrepareCryptTable()
{
	uint32_t nSeed = 0x00100001;
	for (uint32_t i = 0; i < 0x100; ++i)
	{
		for (uint32_t j = 0, nIndex = i; j < 5; ++j, nIndex += 0x100)
		{
			nSeed = (nSeed * 125 + 3) % 0x2AAAAB;
			const uint32_t nHigh = (nSeed & 0xFFFF) << 16;
			nSeed = (nSeed * 125 + 3) % 0x2AAAAB;
			const uint32_t nLow = nSeed & 0xFFFF;
			gpBnCacheCryptTable[nIndex] = nHigh | nLow;
		}
	}
}

static void BNCACHE_EncryptBlock(uint32_t* pData, uint32_t nDwords, uint32_t nKey)
{
	uint32_t nSeed = 0xEEEEEEEE;
	for (uint32_t i = 0; i < nDwords; ++i)
	{
		nSeed += gpBnCacheCryptTable[0x400 + (nKey & 0xFF)];
		const uint32_t nPlain = pData[i];
		pData[i] = nPlain ^ (nKey + nSeed);
		nKey = ((~nKey << 21) + 0x11111111) | (nKey >> 11);
		nSeed = nPlain + nSeed + (nSeed << 5) + 3;
	}
}

static void BNCACHE_DecryptBlock(uint32_t* pData, uint32_t nDwords, uint32_t nKey)
{
	uint32_t nSeed = 0xEEEEEEEE;
	for (uint32_t i = 0; i < nDwords; ++i)
	{
		nSeed += gpBnCacheCryptTable[0x400 + (nKey & 0xFF)];
		const uint32_t nPlain = pData[i] ^ (nKey + nSeed);
		pData[i] = nPlain;
		nKey = ((~nKey << 21) + 0x11111111) | (nKey >> 11);
		nSeed = nPlain + nSeed + (nSeed << 5) + 3;
	}
}

static void BNCACHE_GetFilePath(char* szPath)
{
	szPath[0] = '\0';
	GetModuleFileNameA(GetModuleHandleA(nullptr), szPath, MAX_PATH);

	if (char* pSeparator = strchr(szPath, '\\'))
	{
		while (true)
		{
			char* pNext = pSeparator + 1;
			if (!strchr(pNext, '\\'))
			{
				*pSeparator = '\0';
				break;
			}

			pSeparator = strchr(pNext, '\\');
			if (!pSeparator)
			{
				break;
			}
		}
	}

	strcat(szPath, "\\bncache.dat");
}

static void BNCACHE_GetCurrentTime(FILETIME* pTime, uint32_t nOffsetSeconds)
{
	if (nOffsetSeconds != gnBnCacheCurrentTimeOffset || GetTickCount() != gdwBnCacheCurrentTimeTick)
	{
		SYSTEMTIME tSystemTime;
		GetSystemTime(&tSystemTime);
		SystemTimeToFileTime(&tSystemTime, &gtBnCacheCurrentTime);

		if (nOffsetSeconds)
		{
			ULARGE_INTEGER nTime;
			nTime.LowPart = gtBnCacheCurrentTime.dwLowDateTime;
			nTime.HighPart = gtBnCacheCurrentTime.dwHighDateTime;
			nTime.QuadPart += (uint64_t)nOffsetSeconds * 10000000;
			gtBnCacheCurrentTime.dwLowDateTime = nTime.LowPart;
			gtBnCacheCurrentTime.dwHighDateTime = nTime.HighPart;
		}

		gnBnCacheCurrentTimeOffset = nOffsetSeconds;
		gdwBnCacheCurrentTimeTick = GetTickCount();
	}

	*pTime = gtBnCacheCurrentTime;
}

static void BNCACHE_Rebuild()
{
	char szPath[MAX_PATH];

	if (gbBnCacheOpen)
	{
		BNCACHE_Close();
		if (ghBnCacheFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(ghBnCacheFile);
			ghBnCacheFile = INVALID_HANDLE_VALUE;
		}

		BNCACHE_GetFilePath(szPath);
		DeleteFileA(szPath);
	}

	BNCACHE_GetFilePath(szPath);
	DeleteFileA(szPath);
	BNCACHE_Open();
}

//Bnclient.0x6FF08BE0
void __stdcall BNCACHE_Close()
{
	EnterCriticalSection(&gtBnCacheLock);

	gbBnCacheOpen = FALSE;

	if (gpBnCacheBlockTable)
	{
		SMemFree(gpBnCacheBlockTable, __FILE__, __LINE__, 0);
		gpBnCacheBlockTable = nullptr;
	}

	if (gpBnCacheHashTable)
	{
		SMemFree(gpBnCacheHashTable, __FILE__, __LINE__, 0);
		gpBnCacheHashTable = nullptr;
	}

	if (gpBnCacheHeader)
	{
		SMemFree(gpBnCacheHeader, __FILE__, __LINE__, 0);
		gpBnCacheHeader = nullptr;
	}

	if (ghBnCacheFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(ghBnCacheFile);
		ghBnCacheFile = INVALID_HANDLE_VALUE;
	}

	if (gpBnCacheCryptTable)
	{
		SMemFree(gpBnCacheCryptTable, __FILE__, __LINE__, 0);
		gpBnCacheCryptTable = nullptr;
	}

	LeaveCriticalSection(&gtBnCacheLock);
}

//Bnclient.0x6FF08CA0
BOOL __fastcall BNCACHE_FreeFile(void* pBuffer, uint32_t nSize)
{
	if (!pBuffer)
	{
		return FALSE;
	}

	SMemFree(pBuffer, __FILE__, __LINE__, 0);
	return TRUE;
}

//Bnclient.0x6FF08CC0
BOOL __stdcall BNCACHE_Open()
{
	EnterCriticalSection(&gtBnCacheLock);

	if (gbBnCacheOpen)
	{
		BNCACHE_Close();
	}

	char szPath[MAX_PATH];
	BNCACHE_GetFilePath(szPath);

	ghBnCacheFile = CreateFileA(szPath, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (ghBnCacheFile == INVALID_HANDLE_VALUE)
	{
		BNCACHE_Close();
		LeaveCriticalSection(&gtBnCacheLock);
		return FALSE;
	}

	gpBnCacheCryptTable = (uint32_t*)SMemAlloc(0x500 * sizeof(uint32_t), __FILE__, __LINE__, 0);
	if (gpBnCacheCryptTable)
	{
		BNCACHE_PrepareCryptTable();
	}

	gpBnCacheHeader = (BnCacheHeader*)SMemAlloc(sizeof(BnCacheHeader), __FILE__, __LINE__, 8);

	DWORD nBytesRead;
	int nError = 0;
	const DWORD nFileSize = GetFileSize(ghBnCacheFile, nullptr);
	if (nFileSize && nFileSize <= 0xA00000)
	{
		if (nFileSize < sizeof(BnCacheHeader))
		{
			nError = 1;
		}
		else if (ReadFile(ghBnCacheFile, gpBnCacheHeader, sizeof(BnCacheHeader), &nBytesRead, nullptr), nBytesRead < sizeof(BnCacheHeader))
		{
			nError = 2;
		}
		else if (gpBnCacheHeader->nSignature == BNCACHE_SIGNATURE_V2)
		{
			nError = -1;
		}
		else if (gpBnCacheHeader->nSignature != BNCACHE_SIGNATURE_V3)
		{
			nError = 3;
		}
		else
		{
			const uint32_t nHeaderCRC = gpBnCacheHeader->nHeaderCRC;
			gpBnCacheHeader->nHeaderCRC = 0;
			if (nHeaderCRC != BNCACHE_ComputeCRC(gpBnCacheHeader, sizeof(BnCacheHeader)))
			{
				nError = 4;
			}
			else
			{
				gpBnCacheHeader->nHeaderCRC = nHeaderCRC;

				if (!gpBnCacheHeader->nHashTableOffset || !gpBnCacheHeader->nHashTableEntries)
				{
					nError = 5;
				}
				else if (!gpBnCacheHeader->nBlockTableOffset || !gpBnCacheHeader->nBlockTableEntries)
				{
					nError = 6;
				}
				else
				{
					uint32_t nEntries = gpBnCacheHeader->nHashTableEntries;
					if (nEntries < BNCACHE_MIN_TABLE_ENTRIES)
					{
						nEntries = BNCACHE_MIN_TABLE_ENTRIES;
					}

					uint32_t nTableSize = nEntries * sizeof(BnCacheHashEntry);
					if (gpBnCacheHeader->nHashTableOffset + nTableSize > nFileSize)
					{
						nError = 7;
					}
					else
					{
						gpBnCacheHashTable = (BnCacheHashEntry*)SMemAlloc(nTableSize, __FILE__, __LINE__, 8);
						SetFilePointer(ghBnCacheFile, gpBnCacheHeader->nHashTableOffset, nullptr, FILE_BEGIN);
						ReadFile(ghBnCacheFile, gpBnCacheHashTable, nTableSize, &nBytesRead, nullptr);
						if (nBytesRead != nTableSize)
						{
							nError = 8;
						}
						else if (gpBnCacheHeader->nHashTableCRC != BNCACHE_ComputeCRC(gpBnCacheHashTable, nTableSize))
						{
							nError = 9;
						}
						else
						{
							BNCACHE_DecryptBlock((uint32_t*)gpBnCacheHashTable, nTableSize / sizeof(uint32_t), BNCACHE_HashString("(hash table)", 3));

							nEntries = gpBnCacheHeader->nBlockTableEntries;
							if (nEntries < BNCACHE_MIN_TABLE_ENTRIES)
							{
								nEntries = BNCACHE_MIN_TABLE_ENTRIES;
							}

							nTableSize = nEntries * sizeof(BnCacheBlockEntry);
							if (gpBnCacheHeader->nBlockTableOffset + nTableSize > nFileSize)
							{
								nError = 10;
							}
							else
							{
								gpBnCacheBlockTable = (BnCacheBlockEntry*)SMemAlloc(nTableSize, __FILE__, __LINE__, 8);
								SetFilePointer(ghBnCacheFile, gpBnCacheHeader->nBlockTableOffset, nullptr, FILE_BEGIN);
								ReadFile(ghBnCacheFile, gpBnCacheBlockTable, nTableSize, &nBytesRead, nullptr);
								if (nBytesRead != nTableSize)
								{
									nError = 11;
								}
								else if (gpBnCacheHeader->nBlockTableCRC != BNCACHE_ComputeCRC(gpBnCacheBlockTable, nTableSize))
								{
									nError = 12;
								}
								else
								{
									BNCACHE_DecryptBlock((uint32_t*)gpBnCacheBlockTable, nTableSize / sizeof(uint32_t), BNCACHE_HashString("(block table)", 3));
									gbBnCacheOpen = TRUE;
									LeaveCriticalSection(&gtBnCacheLock);
									return TRUE;
								}
							}
						}
					}
				}
			}
		}

		if (nError > 0)
		{
			BNLOG_Printf("WARNING- cache file is invalid. Replacing with new cache file", nError);
		}
	}

	// Create a new cache file
	if (gbBnCacheOpen)
	{
		LeaveCriticalSection(&gtBnCacheLock);
		return TRUE;
	}

	if (gpBnCacheHashTable)
	{
		SMemFree(gpBnCacheHashTable, __FILE__, __LINE__, 0);
	}

	if (gpBnCacheBlockTable)
	{
		SMemFree(gpBnCacheBlockTable, __FILE__, __LINE__, 0);
	}

	if (ghBnCacheFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(ghBnCacheFile);
		ghBnCacheFile = INVALID_HANDLE_VALUE;
	}

	char szDeletedPath[MAX_PATH];
	BNCACHE_GetFilePath(szDeletedPath);
	DeleteFileA(szDeletedPath);

	ghBnCacheFile = CreateFileA(szPath, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (ghBnCacheFile == INVALID_HANDLE_VALUE)
	{
		BNCACHE_Close();
		LeaveCriticalSection(&gtBnCacheLock);
		return FALSE;
	}

	memset(gpBnCacheHeader, 0x00, sizeof(BnCacheHeader));
	gpBnCacheHeader->nSignature = BNCACHE_SIGNATURE_V3;
	gpBnCacheHeader->nHeaderSize = sizeof(BnCacheHeader);

	const uint32_t nTableSize = BNCACHE_MIN_TABLE_ENTRIES * sizeof(BnCacheHashEntry);
	gpBnCacheHashTable = (BnCacheHashEntry*)SMemAlloc(nTableSize, __FILE__, __LINE__, 8);
	gpBnCacheHeader->nHashTableOffset = sizeof(BnCacheHeader);
	gpBnCacheHeader->nHashTableEntries = BNCACHE_MIN_TABLE_ENTRIES;
	if (gpBnCacheHeader->nArchiveSize < gpBnCacheHeader->nHashTableOffset + nTableSize)
	{
		gpBnCacheHeader->nArchiveSize = gpBnCacheHeader->nHashTableOffset + nTableSize;
	}

	for (uint32_t i = 0; i < BNCACHE_MIN_TABLE_ENTRIES; ++i)
	{
		gpBnCacheHashTable[i].nBlockIndex = BNCACHE_HASH_ENTRY_EMPTY;
	}

	gpBnCacheBlockTable = (BnCacheBlockEntry*)SMemAlloc(BNCACHE_MIN_TABLE_ENTRIES * sizeof(BnCacheBlockEntry), __FILE__, __LINE__, 8);
	gpBnCacheHeader->nBlockTableOffset = sizeof(BnCacheHeader) + nTableSize;
	if (gpBnCacheHeader->nArchiveSize < gpBnCacheHeader->nBlockTableOffset + BNCACHE_MIN_TABLE_ENTRIES * sizeof(BnCacheBlockEntry))
	{
		gpBnCacheHeader->nArchiveSize = gpBnCacheHeader->nBlockTableOffset + BNCACHE_MIN_TABLE_ENTRIES * sizeof(BnCacheBlockEntry);
	}

	gbBnCacheOpen = TRUE;
	LeaveCriticalSection(&gtBnCacheLock);
	return TRUE;
}

// Inlined lookup of a file with the neutral locale
static uint32_t BNCACHE_FindNeutralHashEntry(const char* szFileName)
{
	const uint32_t nHashOffset = BNCACHE_HashString(szFileName, 0);
	const uint32_t nHashA = BNCACHE_HashString(szFileName, 1);
	const uint32_t nHashB = BNCACHE_HashString(szFileName, 2);

	const uint32_t nMask = gpBnCacheHeader->nHashTableEntries - 1;
	const uint32_t nStartIndex = nHashOffset & nMask;
	uint32_t nIndex = nStartIndex;
	while (gpBnCacheHashTable[nIndex].nBlockIndex != BNCACHE_HASH_ENTRY_EMPTY)
	{
		const BnCacheHashEntry* pEntry = &gpBnCacheHashTable[nIndex];
		if (pEntry->nHashA == nHashA && pEntry->nHashB == nHashB && pEntry->nBlockIndex != BNCACHE_HASH_ENTRY_DELETED && !pEntry->nLocale)
		{
			return nIndex;
		}

		nIndex = (nIndex + 1) & nMask;
		if (nIndex == nStartIndex)
		{
			break;
		}
	}

	return BNCACHE_HASH_ENTRY_EMPTY;
}

//Bnclient.0x6FF09500
BOOL __fastcall BNCACHE_LoadFile(const char* szFileName, FILETIME* pFileTime, void** ppBuffer, uint32_t* pSize)
{
	if (pFileTime)
	{
		pFileTime->dwLowDateTime = 0;
		pFileTime->dwHighDateTime = 0;
	}

	if (ppBuffer)
	{
		*ppBuffer = nullptr;
	}

	if (pSize)
	{
		*pSize = 0;
	}

	if (!szFileName || !*szFileName || !ppBuffer || !pSize || !gbBnCacheOpen)
	{
		return FALSE;
	}

	int nCorruptionReason = 0;
	int nInvalidFileReason = 0;

	EnterCriticalSection(&gtBnCacheLock);

	const uint32_t nHashIndex = BNCACHE_FindNeutralHashEntry(szFileName);
	if (nHashIndex == BNCACHE_HASH_ENTRY_EMPTY)
	{
		LeaveCriticalSection(&gtBnCacheLock);
		return FALSE;
	}

	const uint32_t nBlockIndex = gpBnCacheHashTable[nHashIndex].nBlockIndex;
	if (nBlockIndex >= gpBnCacheHeader->nBlockTableEntries)
	{
		nCorruptionReason = 1;
	}
	else
	{
		BnCacheFileHeader tFileHeader;
		memset(&tFileHeader, 0x00, sizeof(tFileHeader));

		const BnCacheBlockEntry* pBlock = &gpBnCacheBlockTable[nBlockIndex];
		DWORD nBytesRead;
		if (pBlock->nFlags & BNCACHE_BLOCK_FLAG_EXISTS)
		{
			SetFilePointer(ghBnCacheFile, pBlock->nOffset, nullptr, FILE_BEGIN);
			ReadFile(ghBnCacheFile, &tFileHeader, sizeof(uint32_t), &nBytesRead, nullptr);
			if (nBytesRead != sizeof(uint32_t))
			{
				nCorruptionReason = 2;
			}
			else if (tFileHeader.nHeaderSize != sizeof(BnCacheFileHeader))
			{
				nCorruptionReason = 3;
			}
			else
			{
				ReadFile(ghBnCacheFile, &tFileHeader.unk0x04, sizeof(BnCacheFileHeader) - sizeof(uint32_t), &nBytesRead, nullptr);
				if (nBytesRead != sizeof(BnCacheFileHeader) - sizeof(uint32_t))
				{
					nCorruptionReason = 4;
				}
				else
				{
					const uint32_t nHeaderCRC = tFileHeader.nHeaderCRC;
					tFileHeader.nHeaderCRC = 0;
					if (nHeaderCRC != BNCACHE_ComputeCRC(&tFileHeader, sizeof(tFileHeader)))
					{
						nInvalidFileReason = 1;
					}
					else
					{
						tFileHeader.nHeaderCRC = nHeaderCRC;
					}
				}
			}
		}

		if (!nCorruptionReason && !nInvalidFileReason)
		{
			FILETIME tCurrentTime;
			if (_stricmp(szFileName, tFileHeader.szFileName))
			{
				nInvalidFileReason = 2;
			}
			else if (BNCACHE_GetCurrentTime(&tCurrentTime, 0), CompareFileTime(&tCurrentTime, &tFileHeader.tExpirationTime) > 0)
			{
				nInvalidFileReason = 3;
			}
			else if (pBlock->nFileSize > 0x1000000)
			{
				nCorruptionReason = 5;
			}
			else
			{
				if (pFileTime)
				{
					*pFileTime = tFileHeader.tFileTime;
				}

				BNCACHE_GetCurrentTime(&tFileHeader.tLastAccessTime, 0);

				SetFilePointer(ghBnCacheFile, pBlock->nOffset, nullptr, FILE_BEGIN);
				tFileHeader.nHeaderCRC = 0;
				tFileHeader.nHeaderCRC = BNCACHE_ComputeCRC(&tFileHeader, sizeof(tFileHeader));

				uint32_t nHeaderSize = tFileHeader.nHeaderSize;
				if (nHeaderSize > sizeof(BnCacheFileHeader))
				{
					nHeaderSize = sizeof(BnCacheFileHeader);
				}

				DWORD nBytesWritten;
				WriteFile(ghBnCacheFile, &tFileHeader, nHeaderSize, &nBytesWritten, nullptr);
				if (nBytesWritten != nHeaderSize)
				{
					nCorruptionReason = 6;
				}
				else
				{
					*ppBuffer = SMemAlloc(pBlock->nFileSize, __FILE__, __LINE__, 0);
					SetFilePointer(ghBnCacheFile, pBlock->nOffset + tFileHeader.nHeaderSize, nullptr, FILE_BEGIN);
					ReadFile(ghBnCacheFile, *ppBuffer, pBlock->nFileSize, (DWORD*)pSize, nullptr);
					if (*pSize != pBlock->nFileSize)
					{
						nCorruptionReason = 7;
					}
					else if (tFileHeader.nDataCRC != BNCACHE_ComputeCRC(*ppBuffer, *pSize))
					{
						nInvalidFileReason = 4;
					}
				}
			}
		}
	}

	if (nCorruptionReason)
	{
		BNLOG_Printf("bncache.dat is corrupt (%d) - rebuilding archive", nCorruptionReason);
		BNCACHE_Rebuild();
	}
	else if (nInvalidFileReason)
	{
		BNLOG_Printf("File: '%s' in bncache.dat is corrupt (%d) - deleting from cache", szFileName, nInvalidFileReason);

		uint32_t nIndex;
		while ((nIndex = BNCACHE_FindNeutralHashEntry(szFileName)) != BNCACHE_HASH_ENTRY_EMPTY)
		{
			const uint32_t nBlock = gpBnCacheHashTable[nIndex].nBlockIndex;
			if (nBlock < gpBnCacheHeader->nBlockTableEntries)
			{
				gpBnCacheBlockTable[nBlock].nFileSize = 0;
				gpBnCacheBlockTable[nBlock].nFlags = 0;
			}
			gpBnCacheHashTable[nIndex].nBlockIndex = BNCACHE_HASH_ENTRY_DELETED;
		}
	}

	if (nCorruptionReason || nInvalidFileReason)
	{
		if (*ppBuffer)
		{
			SMemFree(*ppBuffer, __FILE__, __LINE__, 0);
			*ppBuffer = nullptr;
		}
		*pSize = 0;
	}

	LeaveCriticalSection(&gtBnCacheLock);

	return !nInvalidFileReason && !nCorruptionReason;
}

//Bnclient.0x6FF09D40
uint32_t __fastcall BNCACHE_HashString(const char* szString, uint32_t nHashType)
{
	uint32_t nSeed1 = 0x7FED7FED;
	uint32_t nSeed2 = 0xEEEEEEEE;
	if (szString)
	{
		while (*szString)
		{
			const int nChar = (char)toupper(*szString++);
			nSeed1 = gpBnCacheCryptTable[(nHashType << 8) + nChar] ^ (nSeed1 + nSeed2);
			nSeed2 = nChar + nSeed1 + nSeed2 + (nSeed2 << 5) + 3;
		}
	}

	return nSeed1;
}

//Bnclient.0x6FF09DA0
BOOL __fastcall BNCACHE_StoreFile(const char* szFileName, const void* pData, uint32_t nSize, const FILETIME* pFileTime, uint32_t nMinLifetime, uint32_t nMaxLifetime)
{
	if (!szFileName || !*szFileName || !pData || !nSize || !pFileTime || !nMaxLifetime || !gbBnCacheOpen || nSize > 0x1000000)
	{
		return FALSE;
	}

	int nError = 0;

	EnterCriticalSection(&gtBnCacheLock);

	// Remove the previous versions of the file
	uint32_t nHashIndex;
	while ((nHashIndex = BNCACHE_FindHashEntry(szFileName, 0)) != BNCACHE_HASH_ENTRY_EMPTY)
	{
		const uint32_t nBlock = gpBnCacheHashTable[nHashIndex].nBlockIndex;
		if (nBlock < gpBnCacheHeader->nBlockTableEntries)
		{
			gpBnCacheBlockTable[nBlock].nFileSize = 0;
			gpBnCacheBlockTable[nBlock].nFlags = 0;
		}
		gpBnCacheHashTable[nHashIndex].nBlockIndex = BNCACHE_HASH_ENTRY_DELETED;
	}

	// Look for a free block big enough
	const uint32_t nRecordSize = nSize + sizeof(BnCacheFileHeader);
	uint32_t nBlockIndex = 0;
	while (nBlockIndex < gpBnCacheHeader->nBlockTableEntries)
	{
		if (!gpBnCacheBlockTable[nBlockIndex].nFlags && gpBnCacheBlockTable[nBlockIndex].nAllocatedSize >= nRecordSize)
		{
			break;
		}
		++nBlockIndex;
	}

	if (nBlockIndex >= gpBnCacheHeader->nBlockTableEntries)
	{
		// Look for a block big enough that can be replaced
		for (nBlockIndex = 0; nBlockIndex < gpBnCacheHeader->nBlockTableEntries; ++nBlockIndex)
		{
			if (gpBnCacheBlockTable[nBlockIndex].nAllocatedSize < nRecordSize)
			{
				continue;
			}

			SetFilePointer(ghBnCacheFile, gpBnCacheBlockTable[nBlockIndex].nOffset, nullptr, FILE_BEGIN);

			BnCacheFileHeader tFileHeader;
			memset(&tFileHeader, 0x00, sizeof(tFileHeader));

			DWORD nBytesRead;
			ReadFile(ghBnCacheFile, &tFileHeader, sizeof(uint32_t), &nBytesRead, nullptr);
			if (nBytesRead != sizeof(uint32_t) || tFileHeader.nHeaderSize != sizeof(BnCacheFileHeader))
			{
				break;
			}

			ReadFile(ghBnCacheFile, &tFileHeader.unk0x04, sizeof(BnCacheFileHeader) - sizeof(uint32_t), &nBytesRead, nullptr);
			if (nBytesRead != sizeof(BnCacheFileHeader) - sizeof(uint32_t))
			{
				break;
			}

			FILETIME tCurrentTime;
			BNCACHE_GetCurrentTime(&tCurrentTime, 0);
			if (CompareFileTime(&tCurrentTime, &tFileHeader.tReplaceableTime) > 0)
			{
				break;
			}
		}
	}

	if (nBlockIndex < gpBnCacheHeader->nBlockTableEntries)
	{
		for (uint32_t i = 0; i < gpBnCacheHeader->nHashTableEntries; ++i)
		{
			if (gpBnCacheHashTable[i].nBlockIndex == nBlockIndex)
			{
				gpBnCacheHashTable[i].nBlockIndex = BNCACHE_HASH_ENTRY_DELETED;
			}
		}
	}
	else if (nBlockIndex >= BNCACHE_MIN_TABLE_ENTRIES)
	{
		nError = 11;
	}
	else
	{
		gpBnCacheBlockTable[nBlockIndex].nOffset = gpBnCacheHeader->nArchiveSize;
		gpBnCacheBlockTable[nBlockIndex].nAllocatedSize = nRecordSize;
		gpBnCacheHeader->nArchiveSize += nRecordSize;
		gpBnCacheHeader->nBlockTableEntries = nBlockIndex + 1;
	}

	if (!nError)
	{
		const uint32_t nHashOffset = BNCACHE_HashString(szFileName, 0);
		const uint32_t nHashA = BNCACHE_HashString(szFileName, 1);
		const uint32_t nHashB = BNCACHE_HashString(szFileName, 2);

		const uint32_t nMask = gpBnCacheHeader->nHashTableEntries - 1;
		const uint32_t nStartIndex = nHashOffset & nMask;
		uint32_t nIndex = nStartIndex;
		while (gpBnCacheHashTable[nIndex].nBlockIndex != BNCACHE_HASH_ENTRY_EMPTY && gpBnCacheHashTable[nIndex].nBlockIndex != BNCACHE_HASH_ENTRY_DELETED)
		{
			nIndex = (nIndex + 1) & nMask;
			if (nIndex == nStartIndex)
			{
				break;
			}
		}

		if (gpBnCacheHashTable[nIndex].nBlockIndex != BNCACHE_HASH_ENTRY_EMPTY && gpBnCacheHashTable[nIndex].nBlockIndex != BNCACHE_HASH_ENTRY_DELETED)
		{
			nError = 12;
		}
		else
		{
			gpBnCacheHashTable[nIndex].nHashA = nHashA;
			gpBnCacheHashTable[nIndex].nHashB = nHashB;
			gpBnCacheHashTable[nIndex].nLocale = 0;
			gpBnCacheHashTable[nIndex].nBlockIndex = nBlockIndex;

			BnCacheBlockEntry* pBlock = &gpBnCacheBlockTable[nBlockIndex];
			pBlock->nFileSize = nSize;
			pBlock->nFlags = BNCACHE_BLOCK_FLAG_EXISTS;

			BnCacheFileHeader tFileHeader;
			memset(&tFileHeader, 0x00, sizeof(tFileHeader));
			tFileHeader.nHeaderSize = sizeof(BnCacheFileHeader);
			BNCACHE_GetCurrentTime(&tFileHeader.tCreationTime, 0);
			tFileHeader.tFileTime = *pFileTime;
			BNCACHE_GetCurrentTime(&tFileHeader.tReplaceableTime, nMinLifetime);
			BNCACHE_GetCurrentTime(&tFileHeader.tExpirationTime, nMaxLifetime);
			BNCACHE_GetCurrentTime(&tFileHeader.tLastAccessTime, 0);
			strcpy(tFileHeader.szFileName, szFileName);
			tFileHeader.nDataCRC = BNCACHE_ComputeCRC(pData, nSize);
			tFileHeader.nHeaderCRC = BNCACHE_ComputeCRC(&tFileHeader, sizeof(tFileHeader));

			SetFilePointer(ghBnCacheFile, pBlock->nOffset, nullptr, FILE_BEGIN);

			DWORD nBytesWritten;
			WriteFile(ghBnCacheFile, &tFileHeader, sizeof(tFileHeader), &nBytesWritten, nullptr);
			if (nBytesWritten != sizeof(tFileHeader))
			{
				nError = 13;
			}
			else if (WriteFile(ghBnCacheFile, pData, nSize, &nBytesWritten, nullptr), nBytesWritten != nSize)
			{
				nError = 14;
			}
			else
			{
				uint32_t nHashTableEntries = gpBnCacheHeader->nHashTableEntries;
				if (nHashTableEntries < BNCACHE_MIN_TABLE_ENTRIES)
				{
					nHashTableEntries = BNCACHE_MIN_TABLE_ENTRIES;
				}
				const uint32_t nHashTableSize = nHashTableEntries * sizeof(BnCacheHashEntry);

				uint32_t nBlockTableEntries = gpBnCacheHeader->nBlockTableEntries;
				if (nBlockTableEntries < BNCACHE_MIN_TABLE_ENTRIES)
				{
					nBlockTableEntries = BNCACHE_MIN_TABLE_ENTRIES;
				}
				const uint32_t nBlockTableSize = nBlockTableEntries * sizeof(BnCacheBlockEntry);

				uint32_t* pBuffer = (uint32_t*)SMemAlloc(nHashTableSize > nBlockTableSize ? nHashTableSize : nBlockTableSize, __FILE__, __LINE__, 0);

				SetFilePointer(ghBnCacheFile, gpBnCacheHeader->nHashTableOffset, nullptr, FILE_BEGIN);
				memcpy(pBuffer, gpBnCacheHashTable, nHashTableSize);
				BNCACHE_EncryptBlock(pBuffer, nHashTableSize / sizeof(uint32_t), BNCACHE_HashString("(hash table)", 3));
				gpBnCacheHeader->nHashTableCRC = BNCACHE_ComputeCRC(pBuffer, nHashTableSize);
				WriteFile(ghBnCacheFile, pBuffer, nHashTableSize, &nBytesWritten, nullptr);
				if (nBytesWritten != nHashTableSize)
				{
					SMemFree(pBuffer, __FILE__, __LINE__, 0);
					nError = 15;
				}
				else
				{
					SetFilePointer(ghBnCacheFile, gpBnCacheHeader->nBlockTableOffset, nullptr, FILE_BEGIN);
					memcpy(pBuffer, gpBnCacheBlockTable, nBlockTableSize);
					BNCACHE_EncryptBlock(pBuffer, nBlockTableSize / sizeof(uint32_t), BNCACHE_HashString("(block table)", 3));
					gpBnCacheHeader->nBlockTableCRC = BNCACHE_ComputeCRC(pBuffer, nBlockTableSize);
					WriteFile(ghBnCacheFile, pBuffer, nBlockTableSize, &nBytesWritten, nullptr);
					SMemFree(pBuffer, __FILE__, __LINE__, 0);
					if (nBytesWritten != nBlockTableSize)
					{
						nError = 16;
					}
					else
					{
						gpBnCacheHeader->nHeaderCRC = 0;
						gpBnCacheHeader->nHeaderCRC = BNCACHE_ComputeCRC(gpBnCacheHeader, sizeof(BnCacheHeader));
						SetFilePointer(ghBnCacheFile, 0, nullptr, FILE_BEGIN);
						WriteFile(ghBnCacheFile, gpBnCacheHeader, sizeof(BnCacheHeader), &nBytesWritten, nullptr);
						if (nBytesWritten != sizeof(BnCacheHeader))
						{
							nError = 17;
						}
					}
				}
			}
		}
	}

	if (nError)
	{
		BNLOG_Printf("bncache.dat is corrupt (%d) - rebuilding archive", nError);
		BNCACHE_Rebuild();
	}

	LeaveCriticalSection(&gtBnCacheLock);
	return nError == 0;
}

//Bnclient.0x6FF0AA80
uint32_t __fastcall BNCACHE_FindHashEntry(const char* szFileName, uint32_t nLocale)
{
	const uint32_t nHashOffset = BNCACHE_HashString(szFileName, 0);
	const uint32_t nHashA = BNCACHE_HashString(szFileName, 1);
	const uint32_t nHashB = BNCACHE_HashString(szFileName, 2);

	uint32_t nNeutralIndex = BNCACHE_HASH_ENTRY_EMPTY;
	const uint32_t nMask = gpBnCacheHeader->nHashTableEntries - 1;
	const uint32_t nStartIndex = nHashOffset & nMask;
	uint32_t nIndex = nStartIndex;
	while (gpBnCacheHashTable[nIndex].nBlockIndex != BNCACHE_HASH_ENTRY_EMPTY)
	{
		const BnCacheHashEntry* pEntry = &gpBnCacheHashTable[nIndex];
		if (pEntry->nHashA == nHashA && pEntry->nHashB == nHashB && pEntry->nBlockIndex != BNCACHE_HASH_ENTRY_DELETED)
		{
			if (pEntry->nLocale == nLocale)
			{
				return nIndex;
			}

			if (!pEntry->nLocale)
			{
				nNeutralIndex = nIndex;
			}
		}

		nIndex = (nIndex + 1) & nMask;
		if (nIndex == nStartIndex)
		{
			break;
		}
	}

	return nNeutralIndex;
}
