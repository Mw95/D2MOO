#pragma once

#include <cstdint>
#include <Windows.h>

// Structures that are shared by several D2Client source files.

struct D2DrlgTileDataStrc;
struct D2SeedStrc;

#pragma pack(push, 1)

struct D2ViewTileNodeStrc
{
	uint32_t unk0x00;						//0x00
	int32_t nX;								//0x04
	int32_t nY;								//0x08
	D2DrlgTileDataStrc* pTileData;			//0x0C
	D2ViewTileNodeStrc* pNext;				//0x10
};

struct D2ViewTileGridCellStrc
{
	uint32_t unk0x00[7];					//0x00
	D2ViewTileNodeStrc* pFirstNode;			//0x1C
	uint32_t unk0x20;						//0x20
};

// Game view (camera) used to draw the world
struct D2GameViewStrc
{
	uint32_t unk0x00[5];					//0x00
	RECT tViewRect;							//0x14
	int32_t nViewX;							//0x24
	int32_t nViewY;							//0x28
	uint8_t unk0x2C[0xEAA8 - 0x2C];			//0x2C
	D2ViewTileGridCellStrc* pTileGrid;		//0xEAA8
	uint32_t unk0xEAAC;						//0xEAAC
	int32_t nTileGridSize;					//0xEAB0
};

// Context used while drawing floor tiles
struct D2FloorDrawContextStrc
{
	BOOL bLowQuality;						//0x00
	BOOL bPerspective;						//0x04
	BOOL bSpawnFloorParticles;				//0x08
	BOOL bSpawnFloorSplashes;				//0x0C
	int32_t nFloorParticleChance;			//0x10
	uint32_t dwLastFloorParticleTick;		//0x14
	uint32_t dwLastFloorSplashTick;			//0x18
	D2SeedStrc* pSeed;						//0x1C
	int32_t nScreenPanels;					//0x20
	D2GameViewStrc* pView;					//0x24
	BOOL bDrawEdges;						//0x28
	int32_t nMinX;							//0x2C
	int32_t nMaxX;							//0x30
	int32_t nMinY;							//0x34
	int32_t nMaxY;							//0x38
	int32_t nOffsetX;						//0x3C
	int32_t nOffsetY;						//0x40
};

#pragma pack(pop)
