#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"

#pragma pack(push, 1)

// Image added to a cel compression list (TCELENTRY)
struct D2CelCompressImageStrc
{
	uint32_t dwFlags;							//0x00 D2GfxCellFlags
	uint32_t dwWidth;							//0x04
	uint32_t dwHeight;							//0x08
	uint32_t dwSize;							//0x0C
	int32_t nXOffset;							//0x10
	int32_t nYOffset;							//0x14
	uint8_t* pData;								//0x18
	D2CelCompressImageStrc* pNext;				//0x1C
};

// Cel compression list (CELLIST)
struct D2CelCompressListStrc
{
	uint32_t hCelList;							//0x00
	uint32_t dwFlags;							//0x04 D2CellFileFlags
	uint32_t eFormat;							//0x08
	uint32_t dwTransparentColor;				//0x0C
	uint32_t nImages;							//0x10
	uint32_t dwNumDirections;					//0x14
	D2CelCompressImageStrc* pFirstImage;		//0x18
	D2CelCompressImageStrc* pLastImage;			//0x1C
	D2CelCompressListStrc* pNext;				//0x20
};

// Cel of a CELFILE_VERSION - 1 cel file
struct D2OldGfxCellStrc
{
	uint32_t unk0x00;							//0x00
	uint32_t dwFlags;							//0x04
	uint32_t unk0x08;							//0x08
	uint32_t dwWidth;							//0x0C
	uint32_t dwHeight;							//0x10
	int32_t nXOffset;							//0x14
	int32_t nYOffset;							//0x18
	uint32_t dwHardwareDataSize;				//0x1C
	uint8_t* pHardwareData;						//0x20
	uint32_t dwLength;							//0x24
	uint8_t pPixels[1];							//0x28
};

// Cel file of version CELFILE_VERSION - 1
struct D2OldCellFileStrc
{
	uint32_t dwVersion;							//0x00
	uint32_t dwFlags;							//0x04
	uint32_t unk0x08[2];						//0x08
	int32_t nDirections;						//0x10
	int32_t nFrames;							//0x14
	uint32_t unk0x18[7];						//0x18
	D2OldGfxCellStrc* pGfxCells[1];				//0x34
};

#pragma pack(pop)

using CelEncodeFunc = void(__fastcall*)(D2CelCompressListStrc* pList, D2CellFileStrc* pCelFile);
using CelDrawFunc = void(__fastcall*)(D2GfxCellStrc* pCel, uint8_t* pDest, int nX, int nClipLeft, int nClipRight, int nStride, int nLinesToSkip, int nLinesToDraw, const uint8_t* pPalette, const uint8_t* pBlendTable, const uint8_t* pPalShift);
using CelConvert24To8Func = void(__fastcall*)(D2CellFileStrc* pSrc, D2CellFileStrc* pDest, uint32_t dwTransparentColor, D2CMPColorConvertCallback pfnConvert);
using CelTransformFunc = void(__fastcall*)(D2GfxCellStrc* pCel, const uint8_t* pTransform);

// Inlined helper (D2CMP.0x6FE00346)
int GetFirstBit(uint32_t nValue);

//D2CMP.0x6FDF1000
void __cdecl CELCMP_InitCelLists();
