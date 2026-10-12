#include "D2WinTextBox.h"

#include <algorithm>

#include <D2Math.h>

#include <D2CMP.h>
#include <D2Lang.h>
#include <D2StrTable.h>
#include <Storm.h>

#include <D2Gfx.h>
#include <Texture.h>

#include <Fog.h>
#include <D2BitManip.h>

#include "D2WinFont.h"
#include "D2WinMain.h"
#include "D2WinPalette.h"
#include "D2WinScrollBar.h"
#include "D2WinTimer.h"


int32_t dword_6F8BE238;
extern int32_t dword_6F96A8DC;


//D2Win.0x6F8AFAA0 (#10042)
D2WinTextBoxStrc* __fastcall D2Win_10042_TEXTBOX_Create(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight, int32_t nTextOffsetX, int32_t nTextOffsetY, D2CellFileStrc* pCellFile, int32_t(__stdcall* pfOnSelect)(SMSGHANDLER_PARAMS*), uint32_t dwTextBoxFlags, int32_t pFont, int32_t pScrollBarRect)
{
	D2WinTextBoxStrc* pTextBox = D2_CALLOC_STRC(D2WinTextBoxStrc);

	if (dwTextBoxFlags & 4 && !pScrollBarRect)
	{
		nWidth -= 26;
	}

	if (dwTextBoxFlags & 1)
	{
		dwTextBoxFlags |= 0x20;
	}

	pTextBox->controlHeader.nType = D2WIN_TEXTBOX;
	pTextBox->controlHeader.dwFlags |= gdwBitMasks[0] | gdwBitMasks[2];
	pTextBox->controlHeader.pCellFile = pCellFile;
	pTextBox->controlHeader.nImageX = nX;
	pTextBox->controlHeader.nImageY = nY;
	pTextBox->controlHeader.nWidth = nWidth;
	pTextBox->controlHeader.nHeight = nHeight;
	pTextBox->dwTextBoxFlags = dwTextBoxFlags;
	pTextBox->nTextOffsetX = nTextOffsetX;
	pTextBox->nTextOffsetY = nTextOffsetY;
	pTextBox->controlHeader.pfDraw = TEXTBOX_Draw;
	pTextBox->controlHeader.pfHandleMouseDown = TEXTBOX_HandleMouseDown;

	if (dwTextBoxFlags & 1)
	{
		pTextBox->controlHeader.pfHandleVirtualKeyInput = TEXTBOX_HandleVirtualKeyInput;
	}

	pTextBox->controlHeader.field_34 = pfOnSelect;
	pTextBox->nCurrentLine = -1;
	pTextBox->nNumColumns = 1;

	if (pFont)
	{
		pTextBox->eFont = *(Font*)pFont;
		pTextBox->nTextColor = *(DWORD*)(pFont + 4);
	}
	else
	{
		pTextBox->eFont = D2FONT_FONT16;
		pTextBox->nTextColor = 0;
	}

	TEXTBOX_UpdateLineSpacing(pTextBox->eFont);

	pTextBox->nExtraLineSpacing = dword_6F8BE238;

	if (dwTextBoxFlags & 4)
	{
		pTextBox->controlHeader.pCellFile = nullptr;

		if (pScrollBarRect)
		{
			pTextBox->pScrollBar = SCROLLBAR_Create(*(DWORD*)pScrollBarRect, *(DWORD*)(pScrollBarRect + 4), 10, *(DWORD*)(pScrollBarRect + 8), pCellFile, nullptr);
		}
		else
		{
			pTextBox->pScrollBar = SCROLLBAR_Create(nX + nWidth + 8, nY - 2, 10, nHeight - 16, pCellFile, nullptr);
		}

		SCROLLBAR_SetTextBox(pTextBox->pScrollBar, pTextBox);

		D2Win_10127_SetFont(pTextBox->eFont);
		TEXTBOX_UpdateLineSpacing(pTextBox->eFont);

		const int32_t nTextHeight = D2Win_10125();
		const int32_t nPosition = std::max((pTextBox->controlHeader.nHeight - 2 * pTextBox->nTextOffsetY - (pTextBox->nExtraLineSpacing + nTextHeight)) / (pTextBox->nExtraLineSpacing + nTextHeight + pTextBox->nLineSpacing), 1);

		D2Win_10202(pTextBox->pScrollBar, nPosition);
	}

	CONTROL_AppendToList(&pTextBox->controlHeader);

	return pTextBox;
}

//D2Win.0x6F8AFCC0
void __fastcall TEXTBOX_UpdateLineSpacing(Font nFontSize)
{
	switch (STRTABLE_GetLanguage())
	{
	case LANGUAGE_JAPANESE:
	case LANGUAGE_POLISH:
	{
		dword_6F8BE238 = dword_6F96A8DC != 0 ? 0 : 4;
		break;
	}
	case LANGUAGE_KOREAN:
	{
		const Font nOldFont = D2Win_10127_SetFont(nFontSize);
		if (D2Win_10125() <= 13)
		{
			dword_6F8BE238 = (D2Win_10125() > 7) + 6;
		}
		else
		{
			dword_6F8BE238 = 8;
		}
		D2Win_10127_SetFont(nOldFont);
		break;
	}
	case LANGUAGE_CHINESETWN:
	{
		const Font nOldFont = D2Win_10127_SetFont(nFontSize);
		if (D2Win_10125() <= 13)
		{
			dword_6F8BE238 = (D2Win_10125() > 7) + 6;
		}
		else
		{
			dword_6F8BE238 = 8;
		}

		if (dword_6F96A8DC)
		{
			dword_6F8BE238 = 3;
		}

		D2Win_10127_SetFont(nOldFont);
		break;
	}
	default:
	{
		dword_6F8BE238 = 4;
		break;
	}
	}
}

//1.10f:D2Win.0x6F8AFDC0 (#10043)
//1.13c:D2Win.0x? (#10178)
int32_t __fastcall D2Win_10043_TEXTBOX_Destroy(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	D2WinScrollBarStrc* pScrollBar = pTextBox->pScrollBar;
	if (pScrollBar)
	{
		SCROLLBAR_Destroy(&pScrollBar->controlHeader);
	}

	D2Win_10047(pTextBox);

	return CONTROL_RemoveFromList(&pTextBox->controlHeader);
}

//D2Win.0x6F8AFE30 (#10047)
int32_t __fastcall D2Win_10047(D2WinTextBoxStrc* pTextBox)
{
	if (!pTextBox)
	{
		return 0;
	}

	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	D2WinTextBoxLineStrc* pNext = nullptr;
	for (D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine; pLine; pLine = pNext)
	{
		pNext = pLine->pNext;

		for (int32_t i = 0; i < std::size(pLine->pColumns); ++i)
		{
			if (pLine->pColumns[i])
			{
				D2_FREE(pLine->pColumns[i]);
			}
		}

		D2_FREE(pLine);
	}

	pTextBox->pCurrentLine = nullptr;
	pTextBox->pFirstLine = nullptr;
	pTextBox->pLastLine = nullptr;
	pTextBox->nNumLines = 0;
	pTextBox->nLine = 0;
	return 1;
}

//D2Win.0x6F8AFED0 (#10062)
int32_t __fastcall D2Win_10062(D2WinTextBoxStrc* pTextBox, int32_t nContinuedLineSpacing, int32_t nLineSpacing)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	pTextBox->nContinuedLineSpacing = nContinuedLineSpacing;
	pTextBox->nLineSpacing = nLineSpacing;
	return 1;
}

//D2Win.0x6F8AFF30 (#10045)
void __fastcall D2Win_10045(D2WinTextBoxStrc* pTextBox, const char* szText)
{
	Unicode wszText[1024] = {};

	D2_ASSERT(pTextBox);

	Unicode::win2Unicode(wszText, szText, std::size(wszText));
	D2Win_10051(pTextBox, wszText, 4, 0, 0);
}

//D2Win.0x6F8AFFB0 (#10046)
int32_t __fastcall D2Win_10046(D2WinTextBoxStrc* pTextBox, const char* szText, int32_t nColor)
{
	Unicode wszText[1024] = {};

	D2_ASSERT(pTextBox);

	Unicode::utf8ToUnicode(wszText, szText, std::size(wszText));
	return D2Win_10051(pTextBox, wszText, nColor, 0, 0);
}

//D2Win.0x6F8B0030 (#10044)
int32_t __fastcall D2Win_10044(D2WinTextBoxStrc* pTextBox, const Unicode* wszText)
{
	return D2Win_10051(pTextBox, wszText, 4, 0, 0);
}

int32_t __fastcall TEXTBOX_AppendLine(D2WinTextBoxStrc* pTextBox, const Unicode* wszText, int32_t nColor, char bContinued, int32_t nIndentMode)
{
	D2WinTextBoxLineStrc* pLine = D2_ALLOC_STRC(D2WinTextBoxLineStrc);
	Unicode* wszDestination = nullptr;
	if (nIndentMode == 2)
	{
		pLine->pColumns[0] = (Unicode*)D2_ALLOC(sizeof(Unicode) * (Unicode::strlen(wszText) + 6));
		pLine->pColumns[0][4] = ' ';
		pLine->pColumns[0][3] = pLine->pColumns[0][4];
		pLine->pColumns[0][2] = pLine->pColumns[0][3];
		pLine->pColumns[0][1] = pLine->pColumns[0][2];
		pLine->pColumns[0][0] = pLine->pColumns[0][1];

		wszDestination = (Unicode*)(pLine->pColumns[0] + 5);
	}
	else
	{
		pLine->pColumns[0] = (Unicode*)D2_ALLOC(sizeof(Unicode) * (Unicode::strlen(wszText) + 1));

		wszDestination = pLine->pColumns[0];
	}
	Unicode::strcpy(wszDestination, wszText);

	int32_t bAutoScrolled = 0;

	pLine->pColumns[1] = nullptr;
	pLine->pColumns[2] = nullptr;
	pLine->pColumns[3] = nullptr;
	pLine->pColumns[4] = nullptr;
	pLine->nColor = nColor;
	pLine->bContinued = bContinued;
	pLine->pNext = nullptr;

	if (pTextBox->pFirstLine)
	{
		pTextBox->pLastLine->pNext = pLine;
		pTextBox->pLastLine = pLine;
		++pTextBox->nNumLines;

		D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

		D2WinTextBoxLineStrc* pVisibleLine = pTextBox->pCurrentLine;
		int32_t nVisibleLines = 0;
		while (pVisibleLine)
		{
			pVisibleLine = pVisibleLine->pNext;
			++nVisibleLines;
		}

		D2Win_10127_SetFont(pTextBox->eFont);

		const int32_t nAvailableHeight = pTextBox->controlHeader.nHeight - 2 * pTextBox->nTextOffsetY;
		TEXTBOX_UpdateLineSpacing(pTextBox->eFont);

		const int32_t nFontHeight = D2Win_10125();
		if (nVisibleLines > (nAvailableHeight - (pTextBox->nExtraLineSpacing + nFontHeight)) / (pTextBox->nExtraLineSpacing + nFontHeight + pTextBox->nLineSpacing) + 1)
		{
			D2WinScrollBarStrc* pScrollBar = pTextBox->pScrollBar;
			if (!pScrollBar || SCROLLBAR_GetCurrentStep(pScrollBar) == SCROLLBAR_GetMaxSteps(pTextBox->pScrollBar))
			{
				bAutoScrolled = 1;
				++pTextBox->nLine;
				pTextBox->pCurrentLine = pTextBox->pCurrentLine->pNext;
			}
		}
	}
	else
	{
		pTextBox->pFirstLine = pLine;
		pTextBox->pLastLine = pLine;
		pTextBox->pCurrentLine = pLine;
		++pTextBox->nNumLines;
	}

	D2WinScrollBarStrc* pScrollBar = pTextBox->pScrollBar;
	if (pScrollBar)
	{
		const int32_t nPreviousStep = SCROLLBAR_GetCurrentStep(pScrollBar);

		D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

		D2Win_10127_SetFont(pTextBox->eFont);

		const int32_t nAvailableHeight = pTextBox->controlHeader.nHeight - 2 * pTextBox->nTextOffsetY;
		TEXTBOX_UpdateLineSpacing(pTextBox->eFont);

		const int32_t nFontHeight = D2Win_10125();
		SCROLLBAR_SetMaxSteps(pTextBox->pScrollBar, pTextBox->nNumLines - (nAvailableHeight - (pTextBox->nExtraLineSpacing + nFontHeight)) / (pTextBox->nExtraLineSpacing + nFontHeight + pTextBox->nLineSpacing) - 1);

		if (bAutoScrolled)
		{
			SCROLLBAR_SetCurrentStep(pTextBox->pScrollBar, pTextBox->nLine);
		}
		else
		{
			SCROLLBAR_SetCurrentStep(pTextBox->pScrollBar, nPreviousStep);
		}
	}

	return 1;
}

//D2Win.0x6F8B0040 (#10051)
// Adds a line of text, wrapping it on multiple lines if it does not fit in the text box.
// nIndentMode: 0 = no indentation, 1 = indent wrapped lines, 2 = indent this line
int32_t __fastcall D2Win_10051(D2WinTextBoxStrc* pTextBox, const Unicode* wszText, int32_t nColor, char bContinued, int32_t nIndentMode)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	Unicode wszBuffer[1024] = {};
	Unicode::strcpy(wszBuffer, wszText);

	// Skip leading whitespaces
	const Unicode* wszTrimmedText = wszBuffer;
	while (*wszTrimmedText)
	{
		if (*wszTrimmedText >= 0x100u || !isspace(*wszTrimmedText))
		{
			break;
		}
		++wszTrimmedText;
	}

	D2Win_10127_SetFont(pTextBox->eFont);

	if (pTextBox->dwTextBoxFlags & 0x20)
	{
		return TEXTBOX_AppendLine(pTextBox, wszTrimmedText, nColor, bContinued, nIndentMode);
	}

	int32_t nAvailableWidth = pTextBox->controlHeader.nWidth - 2 * pTextBox->nTextOffsetX;
	if (nIndentMode == 2)
	{
		nAvailableWidth -= D2Win_10121_GetTextWidth((const Unicode*)L"     ");
	}

	if (D2Win_10122(wszTrimmedText, 255) < nAvailableWidth)
	{
		return TEXTBOX_AppendLine(pTextBox, wszTrimmedText, nColor, bContinued, nIndentMode);
	}

	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	Unicode* wszCopy = (Unicode*)SMemAlloc(2048, __FILE__, __LINE__, 0);
	Unicode::strcpy(wszCopy, wszTrimmedText);

	// Find the position where the text must be split, preferably on the last space that fits
	const int32_t nTextLength = Unicode::strlen(wszCopy);
	int32_t nSplitIndex = 0;
	const Unicode* pSplitPosition = wszCopy;
	const Unicode* pLastSpace = nullptr;
	while (nSplitIndex < nTextLength)
	{
		if (*pSplitPosition == ' ')
		{
			pLastSpace = pSplitPosition;
		}

		if (D2Win_10122(wszTrimmedText, nSplitIndex + 1) >= nAvailableWidth)
		{
			if (pLastSpace)
			{
				pSplitPosition = pLastSpace;
				nSplitIndex = pLastSpace - wszCopy;
			}
			break;
		}

		++nSplitIndex;
		++pSplitPosition;
	}

	Unicode* wszFirstPart = (Unicode*)SMemAlloc(2048, __FILE__, __LINE__, 0);
	Unicode* wszSecondPart = (Unicode*)SMemAlloc(2048, __FILE__, __LINE__, 0);
	Unicode::strncpy(wszFirstPart, wszCopy, nSplitIndex);
	wszFirstPart[nSplitIndex] = 0;

	const int32_t nRemainingLength = nTextLength - nSplitIndex;
	Unicode::strncpy(wszSecondPart, pSplitPosition, nRemainingLength);
	wszSecondPart[nRemainingLength] = 0;

	SMemFree(wszCopy, __FILE__, __LINE__, 0);

	D2Win_10051(pTextBox, wszFirstPart, nColor, 1, nIndentMode);
	D2Win_10051(pTextBox, wszSecondPart, nColor, 0, nIndentMode == 1 ? 2 : nIndentMode);

	SMemFree(wszFirstPart, __FILE__, __LINE__, 0);
	SMemFree(wszSecondPart, __FILE__, __LINE__, 0);
	return 1;
}

//D2Win.0x6F8B05E0 (#10198)
int32_t __fastcall D2Win_10198(D2WinTextBoxStrc* pTextBox, const Unicode* pText, int32_t nCount, int32_t nColor, char bContinued)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	for (int32_t i = 0; i < nCount; ++i)
	{
		D2WinTextBoxLineStrc* pLine = D2_CALLOC_STRC(D2WinTextBoxLineStrc);
		pLine->pColumns[0] = (Unicode*)D2_ALLOC(sizeof(Unicode) * (Unicode::strlen(pText) + 1));
		Unicode::strcpy(pLine->pColumns[0], pText);
		pLine->pColumns[1] = nullptr;
		pLine->pColumns[2] = nullptr;
		pLine->pColumns[3] = nullptr;
		pLine->pColumns[4] = nullptr;
		pLine->nColor = nColor;
		pLine->bContinued = bContinued;
		pLine->pNext = nullptr;

		if (pTextBox->pFirstLine)
		{
			pTextBox->pLastLine->pNext = pLine;
		}
		else
		{
			pTextBox->pFirstLine = pLine;
		}

		pTextBox->pLastLine = pLine;
		++pTextBox->nNumLines;
	}

	if (pTextBox->pScrollBar)
	{
		D2Win_10127_SetFont(pTextBox->eFont);
		TEXTBOX_UpdateLineSpacing(pTextBox->eFont);
		const int32_t nTextHeight = D2Win_10125();
		SCROLLBAR_SetMaxSteps(pTextBox->pScrollBar, pTextBox->nNumLines - (pTextBox->controlHeader.nHeight - 2 * pTextBox->nTextOffsetY - (pTextBox->nExtraLineSpacing + nTextHeight)) / (pTextBox->nExtraLineSpacing + nTextHeight + pTextBox->nLineSpacing) - 1);
	}

	return 1;
}

//D2Win.0x6F8B0750 (#10057)
int32_t __fastcall D2Win_10057(D2WinTextBoxStrc* pTextBox, const char* szText, int32_t nLine, int32_t nColumn)
{
	Unicode wszText[1024] = {};

	Unicode::win2Unicode(wszText, szText, std::size(wszText));
	return D2Win_10058_0(pTextBox, wszText, nLine, nColumn);
}

//D2Win.0x6F8B07C0 (#10058)
int32_t __fastcall D2Win_10058_0(D2WinTextBoxStrc* pTextBox, const Unicode* pText, int32_t nLine, int32_t nColumn)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);
	D2_ASSERT(pTextBox->nNumColumns > nColumn);

	Unicode wszText[1024] = {};

	Unicode::strcpy(wszText, pText);

	D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine;
	
	for (int32_t i = 0; i < nLine; ++i)
	{
		if (!pLine)
		{
			return 1;
		}

		pLine = pLine->pNext;	
	}

	if (pLine)
	{
		D2_ASSERT(pLine->pColumns[nColumn] == nullptr);

		pLine->pColumns[nColumn] = (Unicode*)D2_ALLOC(sizeof(Unicode) * (Unicode::strlen(wszText) + 1));
		Unicode::strcpy(pLine->pColumns[nColumn], wszText);
	}

	return 1;
}

//D2Win.0x6F8B08F0 (#10197)
void __fastcall D2Win_10197(D2WinTextBoxStrc* pTextBox, int32_t nLineNum)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);
	D2_ASSERT(nLineNum <= pTextBox->nNumLines);

	D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine;
	int32_t i = 0;
	while (i < nLineNum)
	{
		if (!pLine->pNext)
		{
			break;
		}
		pLine = pLine->pNext;
		++i;
	}

	D2_ASSERT(pLine);
	D2_ASSERT(i == nLineNum);

	for (int32_t j = 0; j < std::size(pLine->pColumns); ++j)
	{
		if (pLine->pColumns[j])
		{
			D2_FREE(pLine->pColumns[j]);
			pLine->pColumns[j] = nullptr;
		}
	}
}

//D2Win.0x6F8B09E0 (#10052)
int32_t __fastcall D2Win_10052_TEXTBOX_GetNumLines(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return pTextBox->nNumLines;
}

//D2Win.0x6F8B0A30 (#10054)
int32_t __fastcall D2Win_10054(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return pTextBox->nLine;
}

//D2Win.0x6F8B0A80 (#10049)
int32_t __fastcall D2Win_10049(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return pTextBox->nCurrentLine;
}

//D2Win.0x6F8B0AD0 (#10050)
void __fastcall D2Win_10050_TEXTBOX_SetLine(D2WinTextBoxStrc* pTextBox, int32_t nLine)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	pTextBox->nCurrentLine = D2Clamp(nLine, -1, pTextBox->nNumLines - 1);
}

//D2Win.0x6F8B0B30 (#10053)
int32_t __fastcall D2Win_10053(D2WinTextBoxStrc* pTextBox, int32_t nLine)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	nLine = std::min(nLine, pTextBox->nNumLines);

	D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine;
	for (int32_t i = 0; i < nLine; ++i)
	{
		if (!pLine->pNext)
		{
			break;
		}

		pLine = pLine->pNext;
	}

	if (pLine)
	{
		pTextBox->pCurrentLine = pLine;
		pTextBox->nLine = nLine;
	}

	if (pTextBox->pScrollBar)
	{
		SCROLLBAR_SetCurrentStep(pTextBox->pScrollBar, nLine);
	}

	return 1;
}

//D2Win.0x6F8B0BC0 (#10055)
int32_t __fastcall D2Win_10055(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	D2Win_10127_SetFont(pTextBox->eFont);
	TEXTBOX_UpdateLineSpacing(pTextBox->eFont);

	const int32_t nTextHeight = D2Win_10125();
	return (pTextBox->controlHeader.nHeight - 2 * pTextBox->nTextOffsetY - (pTextBox->nExtraLineSpacing + nTextHeight)) / (pTextBox->nExtraLineSpacing + nTextHeight + pTextBox->nLineSpacing) + 1;
}

//D2Win.0x6F8B0C50 (#10048)
Unicode* __fastcall D2Win_10048(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	if (pTextBox->nCurrentLine == -1 || !(pTextBox->dwTextBoxFlags & 1))
	{
		return 0;
	}

	int32_t nLine = 0;
	for (D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine; pLine; pLine = pLine->pNext)
	{
		if (pTextBox->nCurrentLine == nLine)
		{
			return pLine->pColumns[0];
		}

		++nLine;
	}

	return 0;
}

//D2Win.0x6F8B0CC0 (#10196)
Unicode* __fastcall D2Win_10196(D2WinTextBoxStrc* pTextBox, int32_t nLineNum, int32_t nColumnNum)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);
	D2_ASSERT(nLineNum <= pTextBox->nNumLines);
	D2_ASSERT(nColumnNum < std::size(pTextBox->nColumnOffsets));

	D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine;
	int32_t i = 0;
	while (i < nLineNum)
	{
		if (!pLine->pNext)
		{
			break;
		}

		pLine = pLine->pNext;
		++i;
	}

	D2_ASSERT(pLine);
	D2_ASSERT(i == nLineNum);

	return pLine->pColumns[nColumnNum];
}

//D2Win.0x6F8B0DC0 (#10056)
void __fastcall D2Win_10056(D2WinTextBoxStrc* pTextBox, int32_t nNumColumns)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);
	D2_ASSERT((nNumColumns > 0) && (nNumColumns <= std::size(pTextBox->nColumnOffsets)));
	D2_ASSERT(pTextBox->nNumColumns <= nNumColumns);

	pTextBox->nNumColumns = nNumColumns;

	if (nNumColumns > 1)
	{
		pTextBox->dwTextBoxFlags |= 0x20;
	}
}

//D2Win.0x6F8B0E60 (#10059)
void __fastcall D2Win_10059(D2WinTextBoxStrc* pTextBox, int32_t nColumn, int32_t nOffset)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);
	D2_ASSERT((nColumn >= 0) && (nColumn < pTextBox->nNumColumns));

	pTextBox->nColumnOffsets[nColumn] = nOffset;
}

//D2Win.0x6F8B0EE0 (#10060)
void __fastcall D2Win_10060(D2WinTextBoxStrc* pTextBox, int32_t nColumn, int32_t nFlags)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);
	D2_ASSERT(nColumn >= 0);
	
	pTextBox->nColumnFlags[nColumn] = nFlags;
}

//D2Win.0x6F8B0F60 (#10061)
int32_t __fastcall D2Win_10061(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	int32_t nLineCount = 0;
	D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine;
	while (pLine)
	{
		pLine = pLine->pNext;
		if (!pLine)
		{
			return nLineCount;
		}

		++nLineCount;
	}

	return nLineCount;
}

//D2Win.0x6F8B0FC0 (#10187)
void __fastcall D2Win_10187(D2WinTextBoxStrc* pTextBox, int32_t bSet)
{
	D2Win_10027_CONTROL_ToggleThirdFlag(&pTextBox->controlHeader, bSet);

	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	if (pTextBox->pScrollBar)
	{
		D2Win_10027_CONTROL_ToggleThirdFlag(&pTextBox->pScrollBar->controlHeader, bSet);
	}
}

//D2Win.0x6F8B1030 (#10188)
int __fastcall D2Win_10188(D2WinTextBoxStrc* pTextBox, int32_t nLineNum, int32_t nColor)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	if (nLineNum != -1)
	{
		D2_ASSERT(nLineNum <= pTextBox->nNumLines);

		D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine;
		int32_t i = 0;
		while (i < nLineNum)
		{
			if (!pLine->pNext)
			{
				break;
			}

			pLine = pLine->pNext;
			++i;
		}

		D2_ASSERT(pLine);
		D2_ASSERT(i == nLineNum);

		pLine->nColor = nColor;
		return 1;
	}

	for (D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine; pLine; pLine = pLine->pNext)
	{
		pLine->nColor = nColor;
	}

	return 1;
}

//D2Win.0x6F8B1130
int32_t __fastcall TEXTBOX_Draw(D2WinControlStrc* pControl)
{
	D2WinTextBoxStrc* pTextBox = (D2WinTextBoxStrc*)pControl;

	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	if (!(pTextBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pTextBox->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 0;
	}

	const uint8_t nSelectionColor = D2Win_10034_MixRGB(0x40u, 0x40u, 0x40u);

	D2CellFileStrc* pCellFile = pTextBox->controlHeader.pCellFile;
	if (pCellFile)
	{
		D2GfxDataStrc gfxData = {};
		gfxData.pCellFile = pCellFile;
		gfxData.nDirection = 0;
		gfxData.nFrame = 0;
		TEXTURE_CelDraw(&gfxData, pTextBox->controlHeader.nImageX, pTextBox->controlHeader.nImageY - 1, -1u, DRAWMODE_NORMAL, 0);
	}

	TEXTBOX_UpdateLineSpacing(pTextBox->eFont);
	D2Win_10127_SetFont(pTextBox->eFont);

	const int32_t nStartX = pTextBox->nTextOffsetX + pTextBox->controlHeader.nImageX;
	int32_t nY = pTextBox->nTextOffsetY + pTextBox->controlHeader.nImageY - pTextBox->controlHeader.nHeight + D2Win_10125();

	TEXTBOX_UpdateLineSpacing(pTextBox->eFont);

	const int32_t nLineHeight = pTextBox->nExtraLineSpacing + D2Win_10125();
	int32_t nRemainingHeight = pTextBox->controlHeader.nHeight - 2 * pTextBox->nTextOffsetY;
	
	const int32_t nBoxWidth = pTextBox->controlHeader.nWidth - 2 * pTextBox->nTextOffsetX;

	if (pTextBox->dwTextBoxFlags & 0x40)
	{
		D2WinTextBoxLineStrc* pCurrentLine = pTextBox->pCurrentLine;
		if (pCurrentLine)
		{
			pTextBox->nScrollOffset -= 2;

			if (pTextBox->nScrollOffset < -D2Win_10121_GetTextWidth(pCurrentLine->pColumns[0]))
			{
				pTextBox->nScrollOffset = nBoxWidth;
			}
		}
	}

	if (pTextBox->dwTextBoxFlags & 0x80)
	{
		D2WinTextBoxLineStrc* pCurrentLine = pTextBox->pCurrentLine;
		if (pCurrentLine)
		{
			pTextBox->nScrollOffset -= 2;

			if (pTextBox->nScrollOffset < -nLineHeight)
			{
				pTextBox->nScrollOffset = 0;
				pTextBox->pCurrentLine = pCurrentLine->pNext;
			}
		}
	}

	int32_t nCounter = 0;
	for (D2WinTextBoxLineStrc* pCurrentLine = pTextBox->pCurrentLine; pCurrentLine; pCurrentLine = pCurrentLine->pNext)
	{
		for (int32_t i = 0; i < pTextBox->nNumColumns; ++i)
		{
			const Unicode* wszColumn = pCurrentLine->pColumns[i];
			if (!wszColumn)
			{
				break;
			}

			int32_t nColumnWidth = pTextBox->controlHeader.nWidth;
			if (i < pTextBox->nNumColumns - 1)
			{
				nColumnWidth = pTextBox->nColumnOffsets[i + 1];
			}

			const int32_t nColumnOffset = pTextBox->nColumnOffsets[i];
			int32_t nX = 0;
			if (nColumnOffset)
			{
				nX = nColumnOffset + nStartX;

				int32_t nColumnSpace = 0;
				if (i + 1 >= pTextBox->nNumColumns)
				{
					nColumnSpace = pTextBox->controlHeader.nWidth - nColumnOffset;
					nColumnWidth = pTextBox->controlHeader.nWidth - nColumnOffset;
				}
				else
				{
					nColumnSpace = pTextBox->nColumnOffsets[i + 1] - nColumnOffset;
					nColumnWidth = pTextBox->nColumnOffsets[i + 1] - nColumnOffset;
				}

				if (pTextBox->nColumnFlags[i] & 2)
				{
					nX += std::max((nColumnSpace - D2Win_10121_GetTextWidth(wszColumn)) / 2, 0);
				}
				else if (pTextBox->nColumnFlags[i] & 0x10)
				{
					nX += nColumnWidth - std::max(D2Win_10121_GetTextWidth(wszColumn), 0);
				}
			}
			else
			{
				if (pTextBox->dwTextBoxFlags & 2)
				{
					nX = pTextBox->controlHeader.nImageX + std::max((pTextBox->controlHeader.nWidth - D2Win_10121_GetTextWidth(pCurrentLine->pColumns[0])) / 2, 0);
				}
				else if (pTextBox->dwTextBoxFlags & 0x10)
				{
					nX = pTextBox->controlHeader.nImageX - std::max(D2Win_10121_GetTextWidth(pCurrentLine->pColumns[0]), 0);
				}
				else
				{
					nX = nStartX;
				}
			}

			Unicode wszText[1024] = {};
			Unicode::strcpy(wszText, pCurrentLine->pColumns[i]);

			int32_t j = 0;
			while (j < Unicode::strlen(wszText))
			{
				if (D2Win_10122(wszText, j + 1) >= nColumnWidth)
				{
					break;
				}
				++j;
			}
			wszText[j] = L'\0';

			if (pTextBox->nCurrentLine == nCounter + pTextBox->nLine && pTextBox->dwTextBoxFlags & 1)
			{
				if (i)
				{
					D2Win_10117_DrawText(wszText, nX, nY, pCurrentLine->nColor != 4 ? pCurrentLine->nColor : 0, 0);
				}
				else
				{
					FONT_DrawTextWithBox(wszText, nX, nY, nBoxWidth, nSelectionColor, DRAWMODE_NORMAL, pCurrentLine->nColor != 4 ? pCurrentLine->nColor : 0);
				}
			}
			else if (pTextBox->dwTextBoxFlags & 0x40)
			{
				FONT_DrawScrollingText(pCurrentLine->pColumns[i], nX, nY, pCurrentLine->nColor, pTextBox->nScrollOffset, nBoxWidth);
			}
			else if (pTextBox->dwTextBoxFlags & 0x80)
			{
				D2Win_10117_DrawText(wszText, nX, nY + pTextBox->nScrollOffset, pCurrentLine->nColor, 0);
			}
			else
			{
				D2Win_10117_DrawText(wszText, nX, nY, pCurrentLine->nColor, 0);
			}
		}

		const int32_t nLineAdvance = nLineHeight + (pCurrentLine->bContinued ? pTextBox->nContinuedLineSpacing : pTextBox->nLineSpacing);
		nY += nLineAdvance;
		nRemainingHeight -= nLineAdvance;

		++nCounter;

		// Stop when the remaining height can't fit the next line
		D2WinTextBoxLineStrc* pNextLine = pCurrentLine->pNext;
		if (pNextLine && nRemainingHeight < nLineHeight + (pNextLine->bContinued ? pTextBox->nContinuedLineSpacing : pTextBox->nLineSpacing))
		{
			break;
		}
	}

	D2Win_10127_SetFont(D2FONT_FONT16);
	return 1;
}

//D2Win.0x6F8B15A0
int32_t __stdcall TEXTBOX_HandleMouseDown(SMSGHANDLER_PARAMS* pMsg)
{
	D2WinTextBoxStrc* pTextBox = (D2WinTextBoxStrc*)pMsg->hWindow;

	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	if (!(pTextBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pTextBox->controlHeader.dwFlags & gdwBitMasks[0]) || pTextBox->nNumLines < 1)
	{
		return 0;
	}

	if (pTextBox->dwTextBoxFlags & 1)
	{
		D2Win_10127_SetFont(pTextBox->eFont);
		TEXTBOX_UpdateLineSpacing(pTextBox->eFont);

		pTextBox->nCurrentLine = (gMousePosition_6F8FE234.y + pTextBox->controlHeader.nHeight - pTextBox->controlHeader.nImageY - pTextBox->nTextOffsetY) / (pTextBox->nExtraLineSpacing + D2Win_10125()) + pTextBox->nLine;

		if (pTextBox->dwTextBoxFlags & 8)
		{
			pTextBox->nCurrentLine = D2Clamp(pTextBox->nCurrentLine, 0, pTextBox->nNumLines - 1);
		}
		else if (pTextBox->nCurrentLine < 0 || pTextBox->nCurrentLine >= pTextBox->nNumLines)
		{
			pTextBox->nCurrentLine = -1;
		}
	}

	if (pTextBox->controlHeader.field_34)
	{
		return pTextBox->controlHeader.field_34(pMsg);
	}

	return 0;
}

//D2Win.0x6F8B16B0
int32_t __stdcall TEXTBOX_HandleVirtualKeyInput(SMSGHANDLER_PARAMS* pMsg)
{
	D2WinTextBoxStrc* pTextBox = (D2WinTextBoxStrc*)pMsg->hWindow;

	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	if (!(pTextBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pTextBox->controlHeader.dwFlags & gdwBitMasks[0]) || pTextBox->nNumLines < 1 || pTextBox->nCurrentLine == -1 || D2Win_10023())
	{
		return 0;
	}

	int32_t nFirstVisibleLine = pTextBox->nLine;
	int32_t nSelectedLine = pTextBox->nCurrentLine;

	const int32_t nNumLines = pTextBox->nNumLines;
	const int32_t nVisibleLines = D2Win_10055(pTextBox);

	switch (pMsg->wParam)
	{
	case VK_PRIOR:
	{
		if (nSelectedLine > nFirstVisibleLine)
		{
			nSelectedLine = nFirstVisibleLine;
		}
		else if (nFirstVisibleLine > 0)
		{
			nFirstVisibleLine = std::max(nFirstVisibleLine - nVisibleLines + 1, 0);
			nSelectedLine = nFirstVisibleLine;
		}
		break;
	}
	case VK_NEXT:
	{
		const int32_t nLastVisibleLine = nVisibleLines + nFirstVisibleLine - 1;
		if (nSelectedLine < nLastVisibleLine)
		{
			nSelectedLine = std::min(nNumLines - 1, nLastVisibleLine);
		}
		else if (nFirstVisibleLine < nNumLines - nVisibleLines)
		{
			nFirstVisibleLine = std::min(nLastVisibleLine, nNumLines - nVisibleLines);
			nSelectedLine = std::min(nVisibleLines + nFirstVisibleLine - 1, nNumLines - 1);
		}
		break;
	}
	case VK_UP:
	{
		if (nSelectedLine > 0)
		{
			--nSelectedLine;

			nFirstVisibleLine = D2Clamp(nFirstVisibleLine, nSelectedLine - nVisibleLines + 1, nSelectedLine);
		}
		break;
	}
	case VK_DOWN:
	{
		if (nSelectedLine < nNumLines - 1)
		{
			++nSelectedLine;

			nFirstVisibleLine = D2Clamp(nFirstVisibleLine, nSelectedLine - nVisibleLines + 1, nSelectedLine);
		}
		break;
	}
	case VK_HOME:
	{
		nSelectedLine = 0;
		nFirstVisibleLine = 0;
		break;
	}
	case VK_END:
	{
		nSelectedLine = nNumLines - 1;
		nFirstVisibleLine = nNumLines - nVisibleLines;
		break;
	}
	default:
	{
		break;
	}
	}

	const bool hasChanged = nSelectedLine != pTextBox->nCurrentLine;
	pTextBox->nCurrentLine = nSelectedLine;

	if (nNumLines > nVisibleLines && nFirstVisibleLine != pTextBox->nLine)
	{
		D2Win_10053(pTextBox, nFirstVisibleLine);
	}

	if (hasChanged && pTextBox->controlHeader.field_34)
	{
		pTextBox->controlHeader.field_34(pMsg);
	}

	return 0;
}

//D2Win.0x6F8B18F0 (#10190)
int32_t __fastcall D2Win_10190(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return SCROLLBAR_GetMaxSteps(pTextBox->pScrollBar);
}

//D2Win.0x6F8B1940 (#10191)
int32_t __fastcall D2Win_10191(D2WinTextBoxStrc* pTextBox, int32_t nMaxSteps)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return SCROLLBAR_SetMaxSteps(pTextBox->pScrollBar, nMaxSteps);
}

//D2Win.0x6F8B1990 (#10192)
int32_t __fastcall D2Win_10192(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return SCROLLBAR_GetCurrentStep(pTextBox->pScrollBar);
}

//D2Win.0x6F8B19E0 (#10193)
int32_t __fastcall D2Win_10193(D2WinTextBoxStrc* pTextBox, int32_t nStep)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return SCROLLBAR_SetCurrentStep(pTextBox->pScrollBar, nStep);
}

//D2Win.0x6F8B1A30 (#10194)
int32_t __fastcall D2Win_10194(D2WinTextBoxStrc* pTextBox, D2WinTextBoxStrc* pTargetTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return SCROLLBAR_SetTextBox(pTextBox->pScrollBar, pTargetTextBox);
}

//D2Win.0x6F8B1A80 (#10195)
int32_t __fastcall D2Win_10195(D2WinTextBoxStrc* pTextBox, void(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*))
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return SCROLLBAR_SetCallback(pTextBox->pScrollBar, pfCallback);
}

//D2Win.0x6F8B1AD0 (#10204)
void __fastcall D2Win_10204(D2WinTextBoxStrc* pTextBox, int32_t nPageSize)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	D2Win_10202(pTextBox->pScrollBar, nPageSize);
}

//D2Win.0x6F8B1B20 (#10203)
int32_t __fastcall D2Win_10203_TEXTBOX(D2WinTextBoxStrc* pTextBox)
{
	D2_ASSERT(pTextBox);
	D2_ASSERT(pTextBox->controlHeader.nType == D2WIN_TEXTBOX);

	return D2Win_10201(pTextBox->pScrollBar);
}
