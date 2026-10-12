#pragma once

#include <cstdarg>

#include <Windows.h>

#include <D2Dll.h>
#include <D2BasicTypes.h>

//1.10f Image base: 0x6FDF0000

#ifdef D2_VERSION_110F
constexpr int D2CMPImageBase = 0x6FDF0000;
#endif

#pragma pack(1)

enum D2TileMaterialFlags : uint16_t 
{
	TILE_FLAGS_OTHER = 0x1,
	TILE_FLAGS_WATER = 0x2,
	TILE_FLAGS_WOOD_OBJ = 0x4, // Blocks reverberation
	TILE_FLAGS_ISTONE = 0x8,   // Indoor stone
	TILE_FLAGS_OSTONE = 0x10,  // Outdoor stone
	TILE_FLAGS_DIRT = 0x20,
	TILE_FLAGS_SAND = 0x40,
	TILE_FLAGS_WOOD = 0x80,
	TILE_FLAGS_LAVA = 0x100, // Special case: Always bright + animated
	TILE_FLAGS_SNOW = 0x400,
};

enum D2TileType
{
	TILETYPE_FLOOR = 0,                 // automap code: fl
	TILETYPE_WALL_LEFT = 1,             // automap code: wl
	TILETYPE_WALL_RIGHT = 2,            // automap code: wr
	TILETYPE_WALL_TOP_CORNER_RIGHT = 3, // automap code: wtlr
	TILETYPE_WALL_TOP_CORNER_LEFT = 4,  // automap code: wtll
	TILETYPE_WALL_TOP_RIGHT = 5,        // automap code: wtr
	TILETYPE_WALL_BOTTOM_LEFT = 6,      // automap code: wbl
	TILETYPE_WALL_BOTTOM_RIGHT = 7,     // automap code: wbr
	TILETYPE_WALL_LEFT_DOOR = 8,        // automap code: wld
	TILETYPE_WALL_RIGHT_DOOR = 9,       // automap code: wrd
	TILETYPE_WALL_LEFT_EXIT = 10,       // automap code: wle
	TILETYPE_WALL_RIGHT_EXIT = 11,      // automap code: wre
	TILETYPE_COLUMN = 12,               // automap code: co
	TILETYPE_SHADOW = 13,               // automap code: sh
	TILETYPE_TREE = 14,                 // automap code: tr
	TILETYPE_ROOF = 15,                 // automap code: rf
	TILETYPE_LEFT_WALL_DOWN = 16,       // automap code: ld
	TILETYPE_RIGHT_WALL_DOWN = 17,      // automap code: rd
	TILETYPE_FULL_WALL_DOWN = 18,       // automap code: fd
	TILETYPE_FRONT_WALL_DOWN = 19,      // automap code: fi
};

struct D2TileRecordStrc;
struct D2LRUCacheBlockStrc;

enum D2TileLibraryHeaderFlags : uint32_t
{
	TILEPROJECT_FLAG_24BIT = 0x1,
	TILEPROJECT_FLAG_SERIALIZED = 0x2,	// Pointers are stored as offsets
	TILEPROJECT_FLAG_SINGLEBLOCK = 0x4,	// The whole project was allocated as a single memory block
	TILEPROJECT_FEWBLOCKS = 0x8,
};

enum D2TileLibraryBlockFormat : uint16_t
{
	TILECOMP_HASDATA = 0x1,
	TILECOMP_RLE = 0x4,
	TILECOMP_SUBTILE = 0x1000,			// 32x32 wall block
	TILECOMP_GAMESQUARE = 0x2000,		// Isometric floor block
};

constexpr int TILEPROJECT_VERSION = 7;
constexpr int MAX_TILEPROJECT = 32;
constexpr int TILE_COLLISION_INFO_SIZE = 25;

// Tile block (aka sub tile), matches the .dt1 file format
struct D2TileLibraryBlockStrc
{
	int16_t nPosX;								//0x00
	int16_t nPosY;								//0x02
	int16_t unk0x04;							//0x04
	uint8_t nGridX;								//0x06
	uint8_t nGridY;								//0x07
	uint16_t nFormat;							//0x08 D2TileLibraryBlockFormat
	int32_t nLength;							//0x0A
	int16_t unk0x0E;							//0x0E
	union
	{
		int32_t dwOffset;						//0x10 Relative to the start of the block array when serialized
		uint8_t* dwOffset_pData;				//0x10
	};
};

// Tile, matches the .dt1 file format
struct D2TileLibraryEntryStrc
{
	int32_t nLightDirection;					//0x00
	uint16_t nRoofHeight;						//0x04
	uint16_t nFlags;							//0x06 D2TileMaterialFlags
	int32_t nTotalHeight;						//0x08
	int32_t nWidth;								//0x0C
	int32_t nHeightToBottom;					//0x10
	int32_t nType;								//0x14 aka nOrientation
	int32_t nStyle;								//0x18 aka nIndex
	int32_t nSequence;							//0x1C aka nSubIndex
	int32_t nRarity_Frame;						//0x20 By default this is the rarity of the tile, for animated tiles this is the frame index.
	int32_t transparentColorRGB24;				//0x24
	uint8_t pCollisionInfo[TILE_COLLISION_INFO_SIZE];	//0x28 Collision info of each sub-tile
	uint8_t unk0x41[7];							//0x41
	int32_t dwBlockOffset;						//0x48 Offset of the blocks in the file
	int32_t nBlockDataSize;						//0x4C Size of the blocks + their data
	int32_t nBlocks;							//0x50
	D2TileLibraryBlockStrc* pBlocks;			//0x54
	const char* szLibraryName;					//0x58
	D2LRUCacheBlockStrc* pLRUCacheBlock;		//0x5C
};

// Hash of tiles referenced by (type, style, sequence)
struct D2TileLibraryHashRefStrc
{
	D2TileLibraryEntryStrc* pTile;				//0x00
	D2TileLibraryHashRefStrc* pNext;			//0x04
};

struct D2TileLibraryHashNodeStrc
{
	int32_t nStyle;								//0x00 aka nIndex;
	int32_t nSequence;							//0x04 aka nSubIndex;
	int32_t nType;								//0x08 aka nOrientation;
	D2TileLibraryHashRefStrc* pRef;				//0x0C
	D2TileLibraryHashNodeStrc* pNext;			//0x10
};

constexpr int FIND_TILE_HASH_SIZE = 128;

struct D2TileLibraryHashStrc
{
	D2TileLibraryHashNodeStrc* pNodes[FIND_TILE_HASH_SIZE];	//0x00
};

// Tile project, matches the .dt1 file format header
struct D2TileLibraryHeaderStrc
{
	int32_t dwVersion;							//0x00
	uint32_t dwFlags;							//0x04 D2TileLibraryHeaderFlags
	char szLibraryName[260];					//0x08
	int32_t nTiles;								//0x10C
	union
	{
		int32_t dwTileStart;					//0x110 When serialized
		D2TileLibraryEntryStrc* pTiles;			//0x110
	};
};

struct D2TileRecordStrc
{
	char szLibraryName[260];					//0x00
	D2TileLibraryHeaderStrc* pLibrary;			//0x104
	D2TileLibraryHashStrc* pHashBlock;			//0x108
	D2TileRecordStrc* pNext;					//0x10C
};

enum D2CellFileFlags : uint32_t
{
	CELFILE_SERIALIZED = 0x1,	// Cel pointers are stored as offsets
	CELFILE_HARDWARE = 0x2,		// Normalized, the hardware data was allocated
	CELFILE_24BIT = 0x4,
};

enum D2CellFileFormat : uint32_t
{
	CELFORMAT_DC6 = 0,
	CELFORMAT_UNUSED = 1,
	NUM_CELFORMATS
};

constexpr int CELFILE_VERSION = 6;
constexpr int CELFILE_NUMGAMEDIRECTIONS = 64;

// Hardware (renderer) data of a cel
struct D2GfxCellNodeStrc
{
	uint32_t unk0x00[10];						//0x00
	uint8_t* pData;								//0x28
};

enum D2GfxCellFlags : uint32_t
{
	GFXCELL_FLAG_TOPDOWN = 0x1,					// Rows are stored from top to bottom
};

struct D2GfxCellStrc
{
	uint32_t dwFlags;							//0x00 D2GfxCellFlags
	uint32_t dwWidth;							//0x04
	uint32_t dwHeight;							//0x08
	int32_t nXOffset;							//0x0C
	int32_t nYOffset;							//0x10
	uint32_t dwHardwareDataSize;				//0x14
	union
	{
		D2GfxCellNodeStrc* pCellNode;			//0x18
		int32_t dwCellNodeOffset;				//0x18 When serialized
	};
	uint32_t dwLength;							//0x1C
	uint8_t pPixels[3];							//0x20 Control data (RLE encoded pixels), dwLength bytes
};

struct D2CellFileStrc
{
	uint32_t dwVersion;							//0x00
	uint32_t dwFlags;							//0x04 D2CellFileFlags
	uint32_t eFormat;							//0x08 D2CellFileFormat
	uint32_t dwTermination;						//0x0C Transparent color for 24 bits files
	int32_t nDirections;						//0x10
	int32_t nFrames;							//0x14 Cels per direction
	union
	{
		D2GfxCellStrc* pGfxCells[1];			//0x18 nDirections * nFrames cels
		int32_t dwGfxCellOffsets[1];			//0x18 When serialized
	};
};

struct D2GfxDataStrc
{
	D2GfxCellStrc* pCurrentCell;				//0x00
	D2CellFileStrc* pCellFile;					//0x04
	uint32_t nFrame;							//0x08
	uint32_t nDirection;						//0x0C
	int32_t nMaxDirections;						//0x10
	int32_t nMaxFrames;							//0x14
	uint32_t fFlags;							//0x18
	uint8_t fState;								//0x1C
	union										//0x1D
	{
		uint8_t nComponent;
		uint8_t fItemFlags;
	};
	uint8_t unk0x1E;							//0x1E - padding no doubt
	uint8_t unk0x1F;							//0x1F
	int32_t nUnitType;							//0x20
	int32_t nUnitIndex;							//0x24
	int32_t nMode;								//0x28
	int32_t nOverlay;							//0x2C
	union
	{
		struct
		{
			char szToken[4];					//0x30
			char szComponent[4];				//0x34
			char szArmorType[4];				//0x38 - lit, med, hvy
			char szMode[4];						//0x3C
			char szHitClass[4];					//0x40
		};
		uint32_t dwName[5];						//0x30
	};
	char* pName;								//0x44
};

#pragma pack()

// Helper function
inline bool TileTypeIsAWallWithDoor(int32_t nTileType)
{
	return nTileType == TILETYPE_WALL_RIGHT_DOOR || nTileType == TILETYPE_WALL_LEFT_DOOR;
}

struct D2CMPPaletteStrc;
struct D2OldCellFileStrc;
struct D2TileListStrc;
struct D2TileAddStrc;

// Converts a 24 bits color to a palette index
using D2CMPColorConvertCallback = uint8_t(__stdcall*)(uint8_t nColor0, uint8_t nColor1, uint8_t nColor2);
// Called for each pixel of 24 bits images
using D2CMPPixelCallback = void(__stdcall*)(uint32_t dwColor);
using CelHardwareFreeCallback = void(__fastcall*)(D2GfxCellNodeStrc* pCellNode);
using TileHardwareFreeCallback = void(__fastcall*)(D2TileLibraryEntryStrc* pTile);

D2FUNC_DLL(D2CMP, CreateD2Palette, D2CMPPaletteStrc*, __stdcall, (const PALETTEENTRY* pPal), 0x90E0)	//D2Cmp.#10000
D2FUNC_DLL(D2CMP, CreateD2PaletteByteStream, D2CMPPaletteStrc*, __stdcall, (const PALETTEENTRY* pPal, int* pSize), 0xAAF0)	//D2Cmp.#10001
D2FUNC_DLL(D2CMP, DestroyD2Palette, void, __stdcall, (D2CMPPaletteStrc* pPalette), 0xAB10)	//D2Cmp.#10002
D2FUNC_DLL(D2CMP, UpdateD2TransparencyTable, void, __stdcall, (D2CMPPaletteStrc* pPalette, int nUnused), 0x8F60)	//D2Cmp.#10003
D2FUNC_DLL(D2CMP, GetClosestColor, uint8_t, __stdcall, (const PALETTEENTRY* pPalette, uint32_t nPaletteSize, int nRed, int nGreen, int nBlue), 0xAB20)	//D2Cmp.#10004
D2FUNC_DLL(D2CMP, GetFurthestColor, uint8_t, __stdcall, (const PALETTEENTRY* pPalette, uint32_t nPaletteSize, int nRed, int nGreen, int nBlue), 0xABA0)	//D2Cmp.#10005
D2FUNC_DLL(D2CMP, PaletteInit, BOOL, __stdcall, (const char* pszPalette, int PaletteStartEntry, int PaletteEndEntry), 0xAC50)	//D2Cmp.#10006
D2FUNC_DLL(D2CMP, Palette24BitTo8BitPixel, uint8_t, __stdcall, (uint8_t nBlue, uint8_t nGreen, uint8_t nRed), 0xAFE0)	//D2Cmp.#10007
D2FUNC_DLL(D2CMP, Palette24BitTo8BitImage, BOOL, __stdcall, (const uint8_t* pSrc, uint8_t* pDest, uint32_t nPixels, D2CMPColorConvertCallback pfnConvert), 0xB0D0)	//D2Cmp.#10008
D2FUNC_DLL(D2CMP, PaletteSetTransparency, void, __stdcall, (PALETTEENTRY tColor), 0xAC20)	//D2Cmp.#10009
D2FUNC_DLL(D2CMP, PaletteTestBackground, void, __stdcall, (BOOL bTestBackground), 0xAFD0)	//D2Cmp.#10010
D2FUNC_DLL(D2CMP, PaletteFixBlack, void, __stdcall, (BOOL bFixBlack), 0xB170)	//D2Cmp.#10011
D2FUNC_DLL(D2CMP, PaletteSetMask, void, __stdcall, (const uint8_t* pMask), 0xB180)	//D2Cmp.#10012
D2FUNC_DLL(D2CMP, CelCompressCreate, uint32_t, __stdcall, (uint32_t format, uint32_t dwNumDirections, const uint32_t* pTransparentColor, BOOL b24Bit), 0x14E0)	//D2Cmp.#10013
D2FUNC_DLL(D2CMP, CelCompressDestroy, void, __stdcall, (uint32_t hCelList), 0x17E0)	//D2Cmp.#10014
D2FUNC_DLL(D2CMP, CelCompressAddImage, void, __stdcall, (uint32_t hCelList, const uint8_t* pImage, uint32_t dwImageByteStride, uint32_t dwPixelHeight, uint32_t dwPixelWidth, int nXOffset, int nYOffset, uint32_t dwFlags), 0x1670)	//D2Cmp.#10015
D2FUNC_DLL(D2CMP, CelCompressCreateCelFile, uint32_t, __stdcall, (uint32_t hCelList, D2CellFileStrc** ppCelFile), 0x18D0)	//D2Cmp.#10016
D2FUNC_DLL(D2CMP, CelNormalDirToFileDir, int, __stdcall, (int nDirection, int nDirections), 0x11D0)	//D2Cmp.#10017
D2FUNC_DLL(D2CMP, CelGameDirToFileDir, int, __stdcall, (int nGameDirection, int nDirections), 0x11F0)	//D2Cmp.#10018
D2FUNC_DLL(D2CMP, CelConvertDir, int, __stdcall, (uint32_t nDirection, uint32_t nStartDirs, int nEndDirs, BOOL bShadow), 0x1210)	//D2Cmp.#10019
D2FUNC_DLL(D2CMP, CelConvertBlock, int, __stdcall, (int nStartDirs, int nEndDirs), 0x12B0)	//D2Cmp.#10020
D2FUNC_DLL(D2CMP, CelGameDirToShadowGameDir, int, __stdcall, (uint32_t nGameDirection, uint32_t nLevelOfRotation), 0x1300)	//D2Cmp.#10021
D2FUNC_DLL(D2CMP, CelGameDirToNormalDir, int, __stdcall, (uint32_t nGameDirection, uint32_t nLevelOfRotation), 0x1400)	//D2Cmp.#10022
D2FUNC_DLL(D2CMP, CelFileSerialize, BOOL, __stdcall, (D2CellFileStrc* pFile, void** ppData, int* pSize), 0x1D30)	//D2Cmp.#10023
D2FUNC_DLL(D2CMP, CelFileNormalize, void, __stdcall, (D2CellFileStrc* pFile, D2CellFileStrc** ppOutFile, const char* szFile, int nLine, int nSpecVersion, int nUnused), 0x1EA0)	//D2Cmp.#10024
D2FUNC_DLL(D2CMP, CelFileConvert24To8, BOOL, __stdcall, (D2CellFileStrc* pFile, D2CellFileStrc** ppOutFile, uint32_t dwTransparentColor, D2CMPColorConvertCallback pfnConvert), 0x1A30)	//D2Cmp.#10025
D2FUNC_DLL(D2CMP, CelFileIteratePixels, void, __stdcall, (D2CellFileStrc* pFile, D2CMPPixelCallback pfnCallback), 0x1CC0)	//D2Cmp.#10026
D2FUNC_DLL(D2CMP, CelFileFree, void, __stdcall, (D2CellFileStrc* pCelFile), 0x1FE0)	//D2Cmp.#10027
D2FUNC_DLL(D2CMP, CelFileFreeSerialized, void, __stdcall, (void* pSerializedFile), 0x1FA0)	//D2Cmp.#10028
D2FUNC_DLL(D2CMP, CelFileHalve, void, __stdcall, (D2CellFileStrc* hFile, int nUnused), 0x1A00)	//D2Cmp.#10029
D2FUNC_DLL(D2CMP, CelFileConvertOldToNew, void, __stdcall, (D2OldCellFileStrc* pOldFile, D2CellFileStrc** ppNewFile, int* pSize), 0x1AD0)	//D2Cmp.#10030
D2FUNC_DLL(D2CMP, CelFileTransform, void, __stdcall, (D2CellFileStrc* pCelFile, const uint8_t* pTransform), 0x2030)	//D2Cmp.#10031
D2FUNC_DLL(D2CMP, CelFileFreeHardware, BOOL, __stdcall, (D2CellFileStrc* ptFile), 0x2750)	//D2Cmp.#10032
D2FUNC_DLL(D2CMP, CelDraw, void, __stdcall, (D2GfxDataStrc* pCelContext, int nX, int nY, int nClipLeft, int nClipRight, uint8_t* pDestSurface, int nSurfaceHeight, int nStride, const uint8_t* pPalette, const uint8_t* pBlendTable, const uint8_t* pPalShift), 0x20A0)	//D2Cmp.#10033
D2FUNC_DLL(D2CMP, CelDrawEx, void, __stdcall, (D2GfxDataStrc* pCelContext, int nX, int nY, int nClipLeft, int nClipRight, uint8_t* pDestSurface, int nSurfaceHeight, int nStride, const uint8_t* pPalette, const uint8_t* pBlendTable, int nLinesToSkip, int nLinesToDraw, const uint8_t* pPalShift), 0x22C0)	//D2Cmp.#10034
D2FUNC_DLL(D2CMP, CelDrawShadow, void, __stdcall, (D2GfxDataStrc* pCelContext, int nX, int nY, int nClipLeft, int nClipRight, uint8_t* pDestSurface, int nSurfaceHeight, int nStride, const uint8_t* pBlendTable, uint8_t nShadowColor), 0x2410)	//D2Cmp.#10035
D2FUNC_DLL(D2CMP, CelGetHandle, D2GfxCellStrc*, __stdcall, (D2GfxDataStrc* pCelContext), 0x2540)	//D2Cmp.#10036
D2FUNC_DLL(D2CMP, CelGetWidth, uint32_t, __stdcall, (D2GfxCellStrc* pCel), 0x25E0)	//D2Cmp.#10037
D2FUNC_DLL(D2CMP, CelGetHeight, uint32_t, __stdcall, (D2GfxCellStrc* pCel), 0x2610)	//D2Cmp.#10038
D2FUNC_DLL(D2CMP, CelGetOffsetX, int, __stdcall, (D2GfxCellStrc* pCel), 0x2640)	//D2Cmp.#10039
D2FUNC_DLL(D2CMP, CelGetOffsetY, int, __stdcall, (D2GfxCellStrc* pCel), 0x2670)	//D2Cmp.#10040
D2FUNC_DLL(D2CMP, CelGetControlData, uint8_t*, __stdcall, (D2GfxCellStrc* ptCel), 0x26A0)	//D2Cmp.#10041
D2FUNC_DLL(D2CMP, CelGetRawData, BOOL, __stdcall, (D2CellFileStrc* pCelFile, int nDirection, int nFrame, uint8_t* pBuffer), 0x2210)	//D2Cmp.#10042
D2FUNC_DLL(D2CMP, CelGetHardwareData, D2GfxCellNodeStrc*, __stdcall, (D2GfxCellStrc* ptCel), 0x2820)	//D2Cmp.#10043
D2FUNC_DLL(D2CMP, CelSetHardwareFreeCallback, void, __stdcall, (CelHardwareFreeCallback pfnCallback), 0x2730)	//D2Cmp.#10044
D2FUNC_DLL(D2CMP, CelGetHardwareFreeCallback, CelHardwareFreeCallback, __stdcall, (), 0x2740)	//D2Cmp.#10045
D2FUNC_DLL(D2CMP, CelFileGetCelsPerDirection, int, __stdcall, (D2CellFileStrc* pFile), 0x2700)	//D2Cmp.#10046
D2FUNC_DLL(D2CMP, CelFileGetNumDirections, int, __stdcall, (D2CellFileStrc* pFile), 0x26D0)	//D2Cmp.#10047
D2FUNC_DLL(D2CMP, CmpDoLensEffect, void, __stdcall, (uint8_t* pDest, int nStride), 0x7FB0)	//D2Cmp.#10048
D2FUNC_DLL(D2CMP, ToggleCelDrawMode, void, __stdcall, (), 0x7A80)	//D2Cmp.#10049
D2FUNC_DLL(D2CMP, BuildFileName, void, __stdcall, (char* szFileName, const char* szFormat, va_list args, BOOL bAllowCompressed), 0xB950)	//D2Cmp.#10050
D2FUNC_DLL(D2CMP, GetGfxFileExtension, const char*, __stdcall, (BOOL bAllowCompressed), 0xB930)	//D2Cmp.#10051
D2FUNC_DLL(D2CMP, SpriteCacheInit, void, __stdcall, (void* pMemPool, uint32_t dwSpriteCacheSize, uint32_t dwCelDataCacheSize, uint32_t dwMemoryOverride), 0xB9F0)	//D2Cmp.#10052
D2FUNC_DLL(D2CMP, SpriteCacheDestroy, void, __stdcall, (BOOL bFreeMemory), 0xBBF0)	//D2Cmp.#10053
D2FUNC_DLL(D2CMP, SetNoCompress, void, __stdcall, (BOOL bAllowCompressed), 0xB9C0)	//D2Cmp.#10054
D2FUNC_DLL(D2CMP, SpriteValidate, BOOL, __stdcall, (D2GfxDataStrc* ptCelContext, BOOL bTestOnly, BOOL bAsync), 0xBD40)	//D2Cmp.#10055
D2FUNC_DLL(D2CMP, SpriteRequest, BOOL, __stdcall, (D2GfxDataStrc* ptCelContext), 0xD600)	//D2Cmp.#10056
D2FUNC_DLL(D2CMP, SpriteNumAsyncLoads, int, __stdcall, (), 0xDF10)	//D2Cmp.#10057
D2FUNC_DLL(D2CMP, SpriteFindAsynchSiblings, BOOL, __stdcall, (int nUnitType, int nMode, int nClass), 0xDF70)	//D2Cmp.#10058
D2FUNC_DLL(D2CMP, SpriteCacheDumpHashTableStats, void, __stdcall, (), 0xD7D0)	//D2Cmp.#10059
D2FUNC_DLL(D2CMP, SpriteCacheGetUsedMemory, uint32_t, __stdcall, (), 0xD7E0)	//D2Cmp.#10060
D2FUNC_DLL(D2CMP, SpriteCacheGetMaxMemory, uint32_t, __stdcall, (), 0xD830)	//D2Cmp.#10061
D2FUNC_DLL(D2CMP, CelDataCacheDumpHashTableStats, void, __stdcall, (), 0xD840)	//D2Cmp.#10062
D2FUNC_DLL(D2CMP, CelDataCacheGetUsedMemory, uint32_t, __stdcall, (), 0xD850)	//D2Cmp.#10063
D2FUNC_DLL(D2CMP, CelDataCacheGetMaxMemory, uint32_t, __stdcall, (), 0xD860)	//D2Cmp.#10064
D2FUNC_DLL(D2CMP, TileListCreate, D2TileListStrc*, __stdcall, (BOOL b24Bit, uint32_t dwTransparentColor), 0xE8D0)	//D2Cmp.#10065
D2FUNC_DLL(D2CMP, TileListDestroy, void, __stdcall, (D2TileListStrc* ptList), 0xE930)	//D2Cmp.#10066
D2FUNC_DLL(D2CMP, TileListAddTile, D2TileAddStrc*, __stdcall, (D2TileListStrc* ptList, uint16_t nFlags, uint16_t nRoofHeight, int nType, int nStyle, int nSequence, int nRarity, int nLightDirection, const uint8_t* pCollisionInfo), 0xE9D0)	//D2Cmp.#10067
D2FUNC_DLL(D2CMP, TileAddAddSubTile, void, __stdcall, (D2TileAddStrc* hTileAdd, const uint8_t* ptImage, int nStride, int nOffsetX, int nOffsetY), 0xEAA0)	//D2Cmp.#10068
D2FUNC_DLL(D2CMP, TileAddAddFloorTile, void, __stdcall, (D2TileAddStrc* ptTileAdd, const uint8_t* ptImage), 0xECB0)	//D2Cmp.#10069
D2FUNC_DLL(D2CMP, TileListCreateProject, uint32_t, __stdcall, (D2TileListStrc* ptTileList, D2TileLibraryHeaderStrc** pptProject), 0xEF60)	//D2Cmp.#10070
D2FUNC_DLL(D2CMP, TileProjectSerialize, void, __stdcall, (D2TileLibraryHeaderStrc* ptProject, void** ptptData, int* ptnSize), 0xF380)	//D2Cmp.#10071
D2FUNC_DLL(D2CMP, TileProjectNormalize, void, __stdcall, (D2TileLibraryHeaderStrc* ptProject, D2TileLibraryHeaderStrc** pptOutProject, const char* szName), 0xF670)	//D2Cmp.#10072
D2FUNC_DLL(D2CMP, TileProjectDestroy, void, __stdcall, (D2TileLibraryHeaderStrc* ptProject, BOOL bDoNotFree), 0xF220)	//D2Cmp.#10073
D2FUNC_DLL(D2CMP, TileProjectIteratePixels, void, __stdcall, (D2TileLibraryHeaderStrc* ptProject, D2CMPPixelCallback pfnCallback), 0xF950)	//D2Cmp.#10074
D2FUNC_DLL(D2CMP, TileProjectConvert24To8, void, __stdcall, (D2TileLibraryHeaderStrc* ptProject24, D2TileLibraryHeaderStrc** pptProject8, D2CMPColorConvertCallback pfnConvert), 0xFA60)	//D2Cmp.#10075
D2FUNC_DLL(D2CMP, TileSetHardwareFreeCallback, void, __stdcall, (TileHardwareFreeCallback pfnCallback), 0xFDD0)	//D2Cmp.#10076
D2FUNC_DLL(D2CMP, TileGetType, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0xFF00)	//D2Cmp.#10077
D2FUNC_DLL(D2CMP, TileGetStyle, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0xFF30)	//D2Cmp.#10078
D2FUNC_DLL(D2CMP, TileGetFlags, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0xFF60)	//D2Cmp.#10079
D2FUNC_DLL(D2CMP, TileGetWidth, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0xFF90)	//D2Cmp.#10080
D2FUNC_DLL(D2CMP, TileGetRarity, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0xFFC0)	//D2Cmp.#10081
D2FUNC_DLL(D2CMP, TileGetSequence, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0xFFF0)	//D2Cmp.#10082
D2FUNC_DLL(D2CMP, TileGetTileLight, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0x10020)	//D2Cmp.#10083
D2FUNC_DLL(D2CMP, TileGetTotalHeight, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0x10050)	//D2Cmp.#10084
D2FUNC_DLL(D2CMP, TileGetCollisionInfo, uint8_t*, __stdcall, (D2TileLibraryEntryStrc* hTile), 0x10080)	//D2Cmp.#10085
D2FUNC_DLL(D2CMP, TileGetHeightToBottom, int, __stdcall, (D2TileLibraryEntryStrc* hTile), 0x100B0)	//D2Cmp.#10086
D2FUNC_DLL(D2CMP, TileLibraryAddProject, void, __stdcall, (D2TileLibraryHashStrc** ptTileLibrary, const char* szName), 0xFDE0)	//D2Cmp.#10087
D2FUNC_DLL(D2CMP, TileLibraryGetTiles, int, __stdcall, (D2TileLibraryHashStrc** ptTileLibrary, int nType, int nStyle, int nSequence, D2TileLibraryEntryStrc** pTileList, int nTileListSize), 0xFE70)	//D2Cmp.#10088
D2FUNC_DLL(D2CMP, TileCacheInit, void, __stdcall, (void* pMemPool, uint32_t dwMaxMemory), 0xE600)	//D2Cmp.#10089
D2FUNC_DLL(D2CMP, TileCacheDestroy, void, __stdcall, (BOOL bFreeCache), 0xE640)	//D2Cmp.#10090
D2FUNC_DLL(D2CMP, TileValidate, BOOL, __stdcall, (D2TileLibraryEntryStrc* pTile, int nUnused1, int nUnused2), 0xE6D0)	//D2Cmp.#10091
D2FUNC_DLL(D2CMP, GetTileCacheHits, void, __stdcall, (uint32_t* pMaxMemory, uint32_t* pMisses, uint32_t* pRequests, int* pUsagePercent), 0xE7F0)	//D2Cmp.#10092
D2FUNC_DLL(D2CMP, ResetTileCacheHits, void, __stdcall, (), 0xE850)	//D2Cmp.#10093
D2FUNC_DLL(D2CMP, DestroyTileHeaders, void, __stdcall, (), 0x10140)	//D2Cmp.#10094
D2FUNC_DLL(D2CMP, LoadProjectRecord, D2TileLibraryHeaderStrc*, __stdcall, (D2TileLibraryHashStrc** ppHash, const char* szFileName), 0x101A0)	//D2Cmp.#10095
D2FUNC_DLL(D2CMP, PalShiftInit, void, __stdcall, (), 0xB1B0)	//D2Cmp.#10096
D2FUNC_DLL(D2CMP, PalShiftSetAct, void, __stdcall, (int nAct), 0xB740)	//D2Cmp.#10097
D2FUNC_DLL(D2CMP, PalShiftGetTransform, uint8_t*, __stdcall, (int nPalette, int nTransform), 0xB760)	//D2Cmp.#10098
D2FUNC_DLL(D2CMP, SpriteFreeAsyncLoads, void, __stdcall, (), 0xE000)	//D2Cmp.#10099
D2FUNC_DLL(D2CMP, TileGetRoofHeight, uint16_t, __stdcall, (D2TileLibraryEntryStrc* hTile), 0x100E0)	//D2Cmp.#10100
D2FUNC_DLL(D2CMP, TileGetFilename, const char*, __stdcall, (D2TileLibraryEntryStrc* hTile), 0x10110)	//D2Cmp.#10101
D2FUNC_DLL(D2CMP, TileFreeAsyncLoads, void, __stdcall, (), 0xE860)	//D2Cmp.#10102
D2FUNC_DLL(D2CMP, 10103, void, __stdcall, (), 0x3ED0)	//D2Cmp.#10103
D2FUNC_DLL(D2CMP, 10104, void, __stdcall, (), 0x3ED0)	//D2Cmp.#10104
D2FUNC_DLL(D2CMP, 10105, void, __stdcall, (int nUnused1, int nUnused2), 0xE8C0)	//D2Cmp.#10105
D2FUNC_DLL(D2CMP, 10106, void, __stdcall, (), 0x3ED0)	//D2Cmp.#10106
