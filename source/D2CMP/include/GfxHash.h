#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"
#include "CelDataHash.h"

struct AsyncData;
struct D2GfxCacheBlockStrc;

#pragma pack(push, 1)

// Unit type of a cel context (D2GfxDataStrc::nUnitType)
enum D2GfxUnitType
{
	GFXUNIT_PLAYER = 0,
	GFXUNIT_MONSTER = 1,
	GFXUNIT_OBJECT = 2,
	GFXUNIT_MISSILE = 3,
	GFXUNIT_ITEM = 4,
	GFXUNIT_TILE = 5,
	GFXUNIT_OVERLAY = 6,
};

enum D2GfxBlockFlags : uint8_t
{
	GFXBLOCK_FLAG_NOFILE = 0x1,
	GFXBLOCK_FLAG_ASYNC = 0x2,
	GFXBLOCK_FLAG_DECODING = 0x4,
};

// Loaded direction(s) of a sprite file
struct D2GfxBlockStrc
{
	uint8_t bFlags;								//0x00 D2GfxBlockFlags
	uint8_t bNumDirections;						//0x01 Number of directions in the block
	uint8_t bFirstDirection;					//0x02
	uint8_t bNumOffsets;						//0x03 Number of directions in the file + 1
	uint8_t bNumCelsPerDir;						//0x04
	uint8_t unk0x05[3];							//0x05
	BOOL fHardwareCelData;						//0x08
	int32_t nOffsets[MAX_DIROFFSETS];			//0x0C Offset of each direction in the block data
	AsyncData* lpAsyncData;						//0x90
	D2GfxCacheBlockStrc* pCacheBlock;			//0x94
};

struct D2GfxNodeStrc
{
	int32_t nUnitType;							//0x00
	int32_t nMode;								//0x04
	int32_t nClass;								//0x08
	uint32_t dwName[5];							//0x0C
	D2GfxBlockStrc tGfxBlock;					//0x20
};

static_assert(sizeof(D2GfxNodeStrc) == 0xB8, "D2GfxNodeStrc size mismatch");

struct D2GfxHashElementStrc
{
	uint32_t nKey;								//0x00
	int32_t nIndex;								//0x04 Class or overlay
	uint32_t dwName[5];							//0x08
	uint32_t dwDirBlock;						//0x1C
	D2GfxNodeStrc* ptGfxNode;					//0x20
	D2GfxCacheBlockStrc* pCacheBlock;			//0x24
	D2GfxHashElementStrc* pPrev;				//0x28
	D2GfxHashElementStrc* pNext;				//0x2C
};

constexpr int GFX_HASH_SIZE = 8192;

struct D2GfxHashStrc
{
	uint32_t unk0x0000[GFX_HASH_SIZE];			//0x0000
	D2GfxHashElementStrc* pBuckets[GFX_HASH_SIZE];	//0x8000
};

#pragma pack(pop)

//D2CMP.0x6FDF8690
void __fastcall GFXHASH_Init(D2GfxHashStrc* pHash);
//D2CMP.0x6FDF86A0
D2GfxHashElementStrc* __fastcall GFXHASH_Find(D2GfxHashStrc* pHash, D2GfxDataStrc* ptCelContext, uint32_t* pDirBlock, uint32_t* pDirBlockSize, D2CelDataStrc* ptCelData);
//D2CMP.0x6FDF8780
uint32_t __fastcall GFXHASH_GetKey(D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData, uint32_t* pDirBlock, uint32_t* pDirBlockSize);
//D2CMP.0x6FDF8830
D2GfxHashElementStrc* __fastcall GFXHASH_Add(void* pMemPool, D2GfxHashStrc* pHash, D2GfxNodeStrc* ptGfxNode, D2GfxDataStrc* ptCelContext, D2CelDataStrc* ptCelData);
//D2CMP.0x6FDF88F0
void __fastcall GFXHASH_Remove(void* pMemPool, D2GfxHashStrc* pHash, D2GfxHashElementStrc* ptElement);
//D2CMP.0x6FDF8A60
uint32_t __fastcall GFXHASH_GetDirBlock(D2GfxDataStrc* ptCelContext, uint32_t* pDirBlockSize, D2CelDataStrc* ptCelData);
