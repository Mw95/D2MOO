#pragma once

#include <D2Client.h>


//D2Client.0x6FAA1000
D2CellFileStrc* __fastcall CLIENT_LoadCellFile(const char* szFile, int32_t nType);
//D2Client.0x6FAA10A0
D2CellFileStrc* __fastcall CLIENT_LoadCellFileWithFileSize(const char* szFile, size_t* pFileSize, int32_t nType);
//D2Client.0x6FAA1140
void __fastcall CLIENT_FreeCellFile(D2CellFileStrc* pCellFile);
