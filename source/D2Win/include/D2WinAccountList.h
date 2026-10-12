#pragma once

#include "D2WinControlHeader.h"

#include "Font.h"


#pragma pack(push, 1)
struct D2WinAccountListDataStrc
{
	char szText[50];								//0x00
	uint8_t pad0x32[2];								//0x32
	D2WinAccountListDataStrc* pNext;				//0x34
};

struct D2WinAccountListStrc
{
	D2WinControlStrc controlHeader;					//0x00
	D2WinAccountListDataStrc* pDataList;			//0x40
	D2WinAccountListDataStrc* pSelectedDataEntry;	//0x44
	int32_t nFirstVisibleEntry;						//0x48
	int32_t nUnused;								//0x4C - Set at creation, never read
	Font eFont;										//0x50
	int32_t nTextColor;							//0x54
};
#pragma pack(pop)


//D2Win.0x6F8A4E90
D2WinAccountListStrc* __fastcall ACCOUNTLIST_Create(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight, int32_t nUnused, void* pFont);
//D2Win.0x6F8A4F70
int __fastcall ACCOUNTLIST_Destroy(D2WinAccountListStrc* pAccountList);
//D2Win.0x6F8A4FC0
void __fastcall ACCOUNTLIST_FreeData(D2WinAccountListStrc* pAccountList);
//D2Win.0x6F8A5010
void __fastcall ACCOUNTLIST_AllocData(D2WinAccountListStrc* pAccountList, const char* szText);
//D2Win.0x6F8A5080
int __fastcall ACCOUNTLIST_RemoveEntry(D2WinAccountListStrc* pAccountList, const char* szText);
//D2Win.0x6F8A5140
int __fastcall ACCOUNTLIST_GetTextFromSelectedEntry(D2WinAccountListStrc* pAccountList, char* szBuffer);
//D2Win.0x6F8A5180
int32_t __fastcall ACCOUNTLIST_Draw(D2WinControlStrc* pControl);
//D2Win.0x6F8A52E0
int __stdcall ACCOUNTLIST_HandleMouseDown(SMSGHANDLER_PARAMS* pMsg);
