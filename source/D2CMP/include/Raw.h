#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"

struct D2CelCompressListStrc;

//D2CMP.0x6FDFB7B0
void __fastcall RAW_CreateCels(D2CelCompressListStrc* pList, D2CellFileStrc* pCelFile);
//D2CMP.0x6FDFB8B0
void __fastcall RAW_IteratePixels(D2GfxCellStrc* pCel, D2CMPPixelCallback pfnCallback, uint32_t dwTransparentColor);
