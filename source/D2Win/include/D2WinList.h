#pragma once

#include "D2WinControlHeader.h"

#include <D2Unicode.h>
#include "Font.h"


#pragma pack(push, 1)
struct D2WinListDataStrc
{
	Unicode wszText[256];							//0x00
	int32_t nTextWidth;								//0x200
	int32_t(__stdcall* pfOnSelect)(SMSGHANDLER_PARAMS*);	//0x204
	int32_t nLeft;								//0x208
	int32_t nRight;								//0x20C
	int32_t nTop;								//0x210
	int32_t nBottom;								//0x214
	char nHotkeyChar;									//0x218
	char field_219;									//0x219
	char field_21A;									//0x21A
	char field_21B;									//0x21B
	int32_t nHotkeyVirtualKey;								//0x21C
	D2WinListDataStrc* pNext;						//0x220
};

// Entry of the item table given to LIST_Create, terminated by an entry with nStringId == 0
struct D2WinListItemInitStrc
{
	uint32_t nStringId;								//0x00
	char nHotkeyChar;								//0x04
	char pad0x05[3];								//0x05
	int32_t nHotkeyVirtualKey;						//0x08
	int32_t(__stdcall* pfOnSelect)(SMSGHANDLER_PARAMS*);	//0x0C
};

struct D2WinListStrc
{
	D2WinControlStrc controlHeader;					//0x00
	Font eFont;										//0x40
	int32_t nLineHeight;								//0x44
	int32_t nLinePadding;								//0x48
	int32_t nFirstVisibleItem;								//0x4C
	int32_t nItemCount;								//0x50
	int32_t nSelectedIndex;								//0x54
	int32_t nMaxVisibleItemIndex;								//0x58
	int32_t nPentspinFrame;								//0x5C
	int32_t nMaxItemWidth;								//0x60
	D2WinListDataStrc* pDataList;					//0x64
	D2WinListDataStrc* pSelectedDataEntry;			//0x68
};
#pragma pack(pop)


//D2Win.0x6F8AC270
D2WinListStrc* __fastcall LIST_Create(int nX, int nY, int nWidth, int nHeight, void* pItems, Font* pFont);
//D2Win.0x6F8AC490
int __fastcall LIST_Destroy(D2WinListStrc* pList);
//D2Win.0x6F8AC4F0
void __fastcall D2Win_10138(D2WinListStrc* pList, const char* szText, int(__stdcall* pfOnSelect)(SMSGHANDLER_PARAMS*), char nHotkeyChar, int nHotkeyVirtualKey, int bInsertFirst, int bSelect);
//D2Win.0x6F8AC570
void __fastcall D2Win_10137(D2WinListStrc* pList, Unicode* wszText, int(__stdcall* pfOnSelect)(SMSGHANDLER_PARAMS*), char nHotkeyChar, int nHotkeyVirtualKey, int bInsertFirst, int bSelect);
//D2Win.0x6F8AC6D0
int __fastcall LIST_GetSelectedDataIndex(D2WinListStrc* pList);
//D2Win.0x6F8AC720
D2WinListDataStrc* __fastcall LIST_GetDataFromIndex(D2WinListStrc* pList, int32_t nIndex);
//D2Win.0x6F8AC770
int __fastcall D2Win_10141(D2WinListStrc* pList);
//D2Win.0x6F8AC7A0
void __stdcall LIST_LoadPentspinCellfile();
//D2Win.0x6F8AC800
void __stdcall LIST_UnloadPentspinCellfile();
//D2Win.0x6F8AC820
int32_t __fastcall LIST_Draw(D2WinControlStrc* pControl);
//D2Win.0x6F8AC9B0
int __stdcall LIST_HandleMouseDown(SMSGHANDLER_PARAMS* pMsg);
//D2Win.0x6F8ACA70
int __stdcall LIST_HandleCharInput(SMSGHANDLER_PARAMS* pMsg);
//D2Win.0x6F8ACAE0
int __stdcall LIST_HandleVirtualKeyInput(SMSGHANDLER_PARAMS* pMsg);
