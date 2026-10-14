#pragma once

#include <Windows.h>

#include <cstdint>

#define BNCACHE_SIGNATURE_V2 0x1A324E42	// 'BN2\x1A'
#define BNCACHE_SIGNATURE_V3 0x1A334E42	// 'BN3\x1A'
#define BNCACHE_MIN_TABLE_ENTRIES 0x400

#pragma pack(push, 1)
// Header of bncache.dat, a simplified MPQ archive
struct BnCacheHeader
{
	uint32_t nSignature;				//0x00
	uint32_t nHeaderSize;				//0x04
	uint32_t nArchiveSize;				//0x08
	uint32_t nUnused;					//0x0C
	uint32_t nHashTableOffset;			//0x10
	uint32_t nBlockTableOffset;			//0x14
	uint32_t nHashTableEntries;			//0x18
	uint32_t nBlockTableEntries;		//0x1C
	uint32_t nHeaderCRC;				//0x20
	uint32_t nHashTableCRC;				//0x24
	uint32_t nBlockTableCRC;			//0x28
};

struct BnCacheHashEntry
{
	uint32_t nHashA;					//0x00
	uint32_t nHashB;					//0x04
	uint32_t nLocale;					//0x08
	uint32_t nBlockIndex;				//0x0C BNCACHE_HASH_ENTRY_EMPTY, BNCACHE_HASH_ENTRY_DELETED or block index
};

struct BnCacheBlockEntry
{
	uint32_t nOffset;					//0x00
	uint32_t nAllocatedSize;			//0x04
	uint32_t nFileSize;					//0x08
	uint32_t nFlags;					//0x0C
};

// Header of each file stored in the cache
struct BnCacheFileHeader
{
	uint32_t nHeaderSize;				//0x000
	uint32_t unk0x04[2];				//0x004
	uint32_t nHeaderCRC;				//0x00C
	uint32_t nDataCRC;					//0x010
	uint32_t unk0x14;					//0x014
	FILETIME tLastAccessTime;			//0x018
	FILETIME tFileTime;					//0x020
	FILETIME tCreationTime;				//0x028
	FILETIME tReplaceableTime;			//0x030 The file can be replaced by another one after this time
	FILETIME tExpirationTime;			//0x038 The file is invalid after this time
	char szFileName[MAX_PATH];			//0x040
};
#pragma pack(pop)

#define BNCACHE_HASH_ENTRY_EMPTY 0xFFFFFFFF
#define BNCACHE_HASH_ENTRY_DELETED 0xFFFFFFFE
#define BNCACHE_BLOCK_FLAG_EXISTS 0xC0000000

void __stdcall BNCACHE_Close();
BOOL __fastcall BNCACHE_FreeFile(void* pBuffer, uint32_t nSize);
BOOL __stdcall BNCACHE_Open();
BOOL __fastcall BNCACHE_LoadFile(const char* szFileName, FILETIME* pFileTime, void** ppBuffer, uint32_t* pSize);
uint32_t __fastcall BNCACHE_HashString(const char* szString, uint32_t nHashType);
BOOL __fastcall BNCACHE_StoreFile(const char* szFileName, const void* pData, uint32_t nSize, const FILETIME* pFileTime, uint32_t nMinLifetime, uint32_t nMaxLifetime);
uint32_t __fastcall BNCACHE_FindHashEntry(const char* szFileName, uint32_t nLocale);
