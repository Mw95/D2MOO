#pragma once

#include "D2WinControlHeader.h"

#include <D2Unicode.h>
#include "Font.h"


enum D2EditBoxFlags
{
	EDITBOX_PASSWORD = 0x00000001,
	EDITBOX_MULTILINE = 0x00000008,
};

struct D2WinEditBoxStrc;

// Returns FALSE if the character should be rejected. The character can be modified by the callback.
using EditBoxCharFilterFunc = BOOL(__stdcall*)(D2WinEditBoxStrc* pEditBox, int32_t nPosition, char* pChar);
// Called with the text when pressing return, or with nullptr when pressing escape
using EditBoxReturnFunc = void(__stdcall*)(const Unicode* wszText);
using EditBoxTextChangedFunc = void(__stdcall*)(int32_t);

#pragma pack(push, 1)
struct D2WinEditBoxStrc
{
	D2WinControlStrc controlHeader;					//0x00
	int32_t nTextOffsetX;							//0x40
	int32_t nTextOffsetY;							//0x44
	int32_t nMaxLength;								//0x48
	int32_t nFirstVisibleChar;						//0x4C
	int32_t nLastVisibleChar;						//0x50
	int32_t nSelectionStart;						//0x54 - -1 when nothing is selected
	int32_t nSelectionEnd;							//0x58
	Unicode wszText[256];							//0x5C
	int32_t nCursorPosition;						//0x25C
	uint32_t dwEditBoxFlags;						//0x260
	EditBoxReturnFunc pfOnReturn;					//0x264
	EditBoxCharFilterFunc pfCharFilter;				//0x268
	EditBoxTextChangedFunc pfOnTextChanged;			//0x26C
	Font eFont;										//0x270
	int32_t nTextColor;								//0x274
	D2WinEditBoxStrc* pNext;						//0x278
	D2WinEditBoxStrc* pPrevious;					//0x27C
	int32_t bMouseSelecting;						//0x280
};

struct D2WinEditBoxFontStrc
{
	Font eFont;										//0x00
	int32_t nTextColor;								//0x04
};
#pragma pack(pop)


//D2Win.0x6F8A6C80
D2WinEditBoxStrc* __fastcall D2Win_10070_EDITBOX_Create(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight, int32_t nTextOffsetX, int32_t nTextOffsetY, D2CellFileStrc* pCellFile, EditBoxReturnFunc pfOnReturn, int32_t(__stdcall* pfHandleMouseDown)(SMSGHANDLER_PARAMS*), int32_t nEditBoxFlags, const D2WinEditBoxFontStrc* pFont);
//D2Win.0x6F8A6DC0
int __fastcall D2Win_10071_EDITBOX_Destroy(D2WinEditBoxStrc* pEditBox);
//D2Win.0x6F8A6E10
void __fastcall D2Win_10072(D2WinEditBoxStrc* pEditBox, EditBoxCharFilterFunc pfCharFilter);
//D2Win.0x6F8A6E60
void __fastcall D2Win_10073(D2WinEditBoxStrc* pEditBox, EditBoxTextChangedFunc pfOnTextChanged);
//D2Win.0x6F8A6EB0
void __fastcall D2Win_10083(D2WinEditBoxStrc* pEditBox);
//D2Win.0x6F8A6F10
int __fastcall D2Win_10082(D2WinEditBoxStrc* pEditBox);
//D2Win.0x6F8A6F70
int32_t __fastcall D2Win_10074(D2WinEditBoxStrc* pEditBox, uint8_t nChar);
//D2Win.0x6F8A7970
void __fastcall sub_6F8A7970(D2WinEditBoxStrc* pEditBox);
//D2Win.0x6F8A7AB0
int32_t __fastcall sub_6F8A7AB0(D2WinEditBoxStrc* pEditBox, char nVirtualKey);
//D2Win.0x6F8A80A0
void __fastcall D2Win_10081(D2WinEditBoxStrc* pEditBox, int32_t nMaxLength);
//D2Win.0x6F8A80F0
int __fastcall D2Win_10076(D2WinEditBoxStrc* pEditBox, const char* szText);
//D2Win.0x6F8A8140
int __fastcall D2Win_10075(D2WinEditBoxStrc* pEditBox, const Unicode* pText);
//D2Win.0x6F8A81E0
const Unicode* __fastcall D2Win_10077_EDITBOX_GetText(D2WinEditBoxStrc* pEditBox);
//D2Win.0x6F8A8230
void __fastcall D2Win_10080_EDITBOX_SetNextEditBox(D2WinEditBoxStrc* pEditBox, D2WinEditBoxStrc* pNext);
//D2Win.0x6F8A82D0
int32_t __fastcall sub_6F8A82D0(D2WinControlStrc* pControl);
//D2Win.0x6F8A86C0
int32_t __fastcall sub_6F8A86C0(D2WinControlStrc* pControl);
//D2Win.0x6F8A8D60
void __fastcall sub_6F8A8D60(D2WinEditBoxStrc* pEditBox, int32_t* pX, int32_t* pY);
//D2Win.0x6F8A9120
int __stdcall sub_6F8A9120(SMSGHANDLER_PARAMS* pMsg);
//D2Win.0x6F8A93A0
int __stdcall EDITBOX_HandleMouseUp(SMSGHANDLER_PARAMS* pMsg);
//D2Win.0x6F8A9410
int32_t __fastcall sub_6F8A9410(SMSGHANDLER_PARAMS* pMsg, int32_t nX, int32_t nY);
//D2Win.0x6F8A97D0
int __stdcall sub_6F8A97D0(SMSGHANDLER_PARAMS* pMsg);
//D2Win.0x6F8A9850
BOOL __stdcall D2Win_10078_IsNumber(D2WinEditBoxStrc* pEditBox, int32_t nPosition, char* szChar);
//D2Win.0x6F8A9870
BOOL __stdcall D2Win_10079_IsLetter(D2WinEditBoxStrc* pEditBox, int32_t nPosition, char* szChar);
//D2Win.0x6F8A98A0
void __fastcall sub_6F8A98A0(D2WinEditBoxStrc* pEditBox);
