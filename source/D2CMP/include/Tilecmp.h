#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"

#pragma pack(push, 1)

// Sub tile being added to a tile, before it gets compiled into a D2TileLibraryBlockStrc
struct D2TileAddCompStrc
{
	int16_t nPosX;									//0x00
	int16_t nPosY;									//0x02
	uint8_t nGridX;									//0x04
	uint8_t nGridY;									//0x05
	uint16_t wFlags;								//0x06 D2TileLibraryBlockFormat
	uint16_t wSize;									//0x08
	uint16_t unk0x0A;								//0x0A
	uint8_t* ptData;								//0x0C
	D2TileAddCompStrc* pNext;						//0x10
};

enum D2TileAddFlags : uint8_t
{
	TILEADD_FLAG_8BIT = 0x1,
	TILEADD_FLAG_24BIT = 0x2,
};

// Tile being added to a tile list
struct D2TileAddStrc
{
	int32_t nMinX;									//0x00
	int32_t nMaxY;									//0x04
	int32_t nMaxX;									//0x08
	int32_t nMinY;									//0x0C
	int32_t nLightDirection;						//0x10
	uint16_t nRoofHeight;							//0x14
	uint16_t nFlags;								//0x16
	int32_t unk0x18[3];								//0x18
	int32_t nType;									//0x24
	int32_t nStyle;									//0x28
	int32_t nSequence;								//0x2C
	int32_t nRarity;								//0x30
	uint32_t dwTransparentColor;					//0x34
	uint8_t pCollisionInfo[TILE_COLLISION_INFO_SIZE];	//0x38
	uint8_t nAddFlags;								//0x51 D2TileAddFlags
	uint16_t unk0x52;								//0x52
	int32_t nCompCount;								//0x54
	D2TileAddCompStrc* ptCompList;					//0x58
	D2TileAddStrc* pNext;							//0x5C
};

struct D2TileListStrc
{
	BOOL b24Bit;									//0x00
	uint32_t dwTransparentColor;					//0x04
	int32_t nNumTiles;								//0x08
	D2TileAddStrc* ptFirstTile;						//0x0C
};

#pragma pack(pop)

//D2CMP.0x6FDFF780
void __stdcall TILECMP_NormalizeHeaderOnly(D2TileLibraryHeaderStrc* ptProject, D2TileLibraryHeaderStrc** pptOutProject, const char* szName);
//D2CMP.0x6FDFF860
D2TileLibraryHashStrc* __fastcall TILECMP_CreateFindTileHash(D2TileLibraryHeaderStrc* ptProject);
//D2CMP.0x6FDFF8F0
void __stdcall TILECMP_FixupBlockPointers(D2TileLibraryEntryStrc* ptTile);
