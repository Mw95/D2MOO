#pragma once

#include <D2BasicTypes.h>

#include "D2CMP.h"


//D2CMP.0x6FDFE780
int __fastcall TILECACHE_GetProjectHeaderSize(const char* szFileName);
//D2CMP.0x6FDFE7E0
void __fastcall TILECACHE_SetHardwareFreeCallback(TileHardwareFreeCallback pfnCallback);
//D2CMP.0x6FDFE870
void __fastcall TILECACHE_FreeProjectTiles(D2TileLibraryHeaderStrc* ptProject);
