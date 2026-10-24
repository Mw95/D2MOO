#pragma once

#include "D2WinControlHeader.h"


#pragma pack(push, 1)
// Context given to the renderer to decode and play a Smacker video
struct D2WinSmackerContextStrc
{
	void* pRendererData[2];							//0x00 - Filled by the renderer when decoding
	int32_t nX;										//0x08
	int32_t nY;										//0x0C
};

struct D2WinSmackStrc
{
	D2WinControlStrc controlHeader;					//0x00
	char szFileName[256];							//0x40
	D2WinSmackerContextStrc smackerContext;		//0x140
};
#pragma pack(pop)


//D2Win.0x6F8AF710
D2WinSmackStrc* __fastcall SMACK_Create(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight, int32_t(__stdcall* pfOnClick)(SMSGHANDLER_PARAMS*));
//D2Win.0x6F8AF7E0
int __stdcall SMACK_Decode(D2WinSmackStrc* pSmack, const char* szFileName, int nVersion, int nUnused, int nUnused2);
//D2Win.0x6F8AF860
int __stdcall SMACK_DeleteFile(D2WinSmackStrc* pSmack);
//D2Win.0x6F8AF8B0
int __stdcall SMACK_SetCoordinates(D2WinSmackStrc* pSmack, int nX, int nY);
//D2Win.0x6F8AF900
int __fastcall SMACK_Destroy(D2WinSmackStrc* pSmack);
//D2Win.0x6F8AF950
void __stdcall D2Win_10184();
//D2Win.0x6F8AF960
int32_t __fastcall SMACK_Draw(D2WinControlStrc* pControl);
//D2Win.0x6F8AFA40
int __stdcall SMACK_HandleMouseDown(SMSGHANDLER_PARAMS* pMsg);
//D2Win.0x6F8AFA90
void __fastcall D2Win_10208(int bReducedLineSpacing);
