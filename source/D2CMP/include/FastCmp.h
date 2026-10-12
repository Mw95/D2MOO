#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"

struct D2CelCompressListStrc;

// DC6 RLE format: each row is a list of codes
//  - 0x80: end of row
//  - 0x80 | n: skip n transparent pixels
//  - n: n pixels follow
constexpr uint8_t DC6_END_OF_LINE = 0x80;
constexpr uint8_t DC6_SKIP_FLAG = 0x80;
constexpr int DC6_MAX_RUN = 0x7F;

//D2CMP.0x6FDF5C10
void __fastcall FASTCMP_EncodeCelList(D2CelCompressListStrc* pList, D2CellFileStrc* pCelFile);
//D2CMP.0x6FDF5D60
void __fastcall FASTCMP_EncodeImage(const uint8_t* pPixels, uint32_t nWidth, uint32_t nHeight, uint32_t dwFlags, uint8_t** ppData, uint32_t* pSize);
//D2CMP.0x6FDF5E60
void __fastcall FASTCMP_TransformCel(D2GfxCellStrc* pCel, const uint8_t* pTransform);
//D2CMP.0x6FDF5EA0
void __fastcall FASTCMP_ConvertCelFile24To8(D2CellFileStrc* pSrc, D2CellFileStrc* pDest, uint32_t dwTransparentColor, D2CMPColorConvertCallback pfnConvert);
//D2CMP.0x6FDF7AA0
void __fastcall FASTCMP_DrawCel(D2GfxCellStrc* pCel, uint8_t* pDest, int nX, int nClipLeft, int nClipRight, int nStride, int nLinesToSkip, int nLinesToDraw, const uint8_t* pPalette, const uint8_t* pBlendTable, const uint8_t* pPalShift);
//D2CMP.0x6FDF8100
void __fastcall FASTCMP_DrawCelShadow(D2GfxCellStrc* pCel, uint8_t* pDest, int nX, int nClipLeft, int nClipRight, int nStride, int nLinesToSkip, int nLinesToDraw, const uint8_t* pBlendTable, uint8_t nShadowColor);
