#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"
#include "CelDataHash.h"
#include "GfxHash.h"

#pragma pack(push, 1)

struct D2DccBitstreamStrc
{
	const uint8_t* pStart;						//0x00
	const uint32_t* pCurrent;					//0x04
	uint32_t nBitSize;							//0x08
	uint32_t nBitOffset;						//0x0C
};

struct D2DccFrameStrc
{
	uint32_t nVariable0;						//0x00
	int32_t nWidth;								//0x04
	int32_t nHeight;							//0x08
	int32_t nXOffset;							//0x0C
	int32_t nYOffset;							//0x10
	uint32_t nOptionalDataSize;					//0x14
	const uint8_t* pOptionalData;				//0x18
	uint32_t nCodedBytes;						//0x1C
	uint8_t* pImage;							//0x20
	int32_t nStride;							//0x24
	BOOL bBottomUp;								//0x28
};

struct D2DccHeaderInfoStrc
{
	uint32_t dwVersion;							//0x00
	uint32_t dwFlags;							//0x04
	uint32_t dwNumDirections;					//0x08
	uint32_t dwFramesPerDirection;				//0x0C
};

struct D2DccDirectionStrc
{
	D2DccHeaderInfoStrc* pHeader;				//0x00
	D2DccFrameStrc* pFrames;					//0x04
	int32_t nMinX;								//0x08
	int32_t nMinY;								//0x0C
	int32_t nWidth;								//0x10
	int32_t nHeight;							//0x14
	int32_t nDirection;							//0x18
	int32_t nFrames;							//0x1C
	int32_t nCellCount;							//0x20
	int32_t nBufferCells;						//0x24
	int32_t nCellsPerRow;						//0x28
};

// Iterates over the 4x4 cells of all the frames of a direction
struct D2DccCellIteratorStrc
{
	int32_t nFrame;								//0x00
	int32_t nFrameWidth;						//0x04
	int32_t nFrameHeight;						//0x08
	int32_t nFrameX;							//0x0C
	int32_t nFrameY;							//0x10
	uint8_t* pFrameImage;						//0x14
	int32_t nFrameStride;						//0x18
	int32_t nRowCell;							//0x1C
	int32_t nCell;								//0x20
	int32_t nX;									//0x24
	int32_t nY;									//0x28
	int32_t nRowOffset;							//0x2C
	int32_t nPixelOffset;						//0x30
	int32_t nCellWidth;							//0x34
	int32_t nCellHeight;						//0x38
};

struct D2DccCellStrc
{
	uint8_t* pPixelValues;						//0x00
	uint8_t* pDest;								//0x04
	int32_t nStride;							//0x08
	int32_t nWidth;								//0x0C
	int32_t nHeight;							//0x10
};

struct D2DccPixelValuesStrc
{
	uint8_t* pData;								//0x00
	uint32_t nCount;							//0x04
};

#pragma pack(pop)

//D2CMP.0x6FDF3EE0
BOOL __fastcall CODEC_EncodeFrame(D2DccFrameStrc* pFrame, D2GfxCellStrc* pCel, uint8_t* pDest);
//D2CMP.0x6FDF4050
BOOL __fastcall CODEC_ReadCelDataHeader(const char* szPath, D2CelDataStrc* ptCelData);
//D2CMP.0x6FDF4160
uint8_t* __fastcall CODEC_DecodeDirections(const uint8_t* pData, void* pMemPool, int nDataLength, D2CelDataStrc* ptCelData, D2GfxBlockStrc* ptGfxBlock, int nFirstDirection, int nDirections, uint32_t* pDecodedSize, const char* szFileName);
//D2CMP.0x6FDF5A10
void __fastcall CODEC_InitLock();
//D2CMP.0x6FDF5A30
void __fastcall CODEC_DestroyLock();
