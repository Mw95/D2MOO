#pragma once

#include <D2BasicTypes.h>

struct D2LRUCacheBlockStrc;

#pragma pack(push, 1)

enum D2CelDataFlags : uint8_t
{
	CELDATAFLAG_NOFILE = 0x1,
	CELDATAFLAG_DCC = 0x2,
};

constexpr int MAX_DIROFFSETS = 33;
constexpr int CELDATA_NAME_LENGTH = 32;

// Header of a sprite file (.dc6 or .dcc), cached so that the file does not need to be opened again
struct D2CelDataStrc
{
	uint8_t bFlags;								//0x00 D2CelDataFlags
	uint8_t unk0x01[3];							//0x01
	struct
	{
		uint32_t dwVersion;						//0x04
		uint32_t dwFlags;						//0x08
		uint32_t eFormat;						//0x0C
		uint32_t dwTermination;					//0x10
		uint32_t dwNumDirections;				//0x14
		uint32_t dwFramesPerDirection;			//0x18
	} tHeader;
	int32_t nOffsets[MAX_DIROFFSETS];			//0x1C Offset of each direction in the file, last one being the file size
	char szName[CELDATA_NAME_LENGTH];			//0xA0
};

static_assert(sizeof(D2CelDataStrc) == 0xC0, "D2CelDataStrc size mismatch");

struct D2CelDataHashElementStrc
{
	uint32_t nKey;								//0x00
	char szName[CELDATA_NAME_LENGTH];			//0x04
	D2LRUCacheBlockStrc* pBlock;				//0x24
	D2CelDataHashElementStrc* pPrev;			//0x28
	D2CelDataHashElementStrc* pNext;			//0x2C
};

constexpr int CELDATA_HASH_SIZE = 512;

struct D2CelDataHashStrc
{
	uint32_t unk0x000[CELDATA_HASH_SIZE];		//0x000
	D2CelDataHashElementStrc* pBuckets[CELDATA_HASH_SIZE];	//0x800
};

#pragma pack(pop)

//D2CMP.0x6FDF3D10
void __fastcall CELDATAHASH_Init(D2CelDataHashStrc* pHash);
//D2CMP.0x6FDF3D20
D2CelDataHashElementStrc* __fastcall CELDATAHASH_Find(D2CelDataHashStrc* pHash, const char* szName);
//D2CMP.0x6FDF3DC0
D2CelDataHashElementStrc* __fastcall CELDATAHASH_Add(void* pMemPool, D2CelDataHashStrc* pHash, D2LRUCacheBlockStrc* pBlock, const char* szName);
//D2CMP.0x6FDF3E60
void __fastcall CELDATAHASH_Remove(void* pMemPool, D2CelDataHashStrc* pHash, D2CelDataHashElementStrc* ptElement);
