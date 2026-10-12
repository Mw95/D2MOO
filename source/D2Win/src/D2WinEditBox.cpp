#include "D2WinEditBox.h"

#include <algorithm>
#include <cstring>

#include <D2Math.h>

#include "D2CMP.h"
#include "D2Gfx.h"
#include "D2Lang.h"
#include "Fog.h"

#include <Texture.h>
#include <Window.h>

#include <D2BitManip.h>

#include "D2WinFont.h"
#include "D2WinMain.h"
#include "D2WinPalette.h"

#pragma warning (disable : 28159)


enum D2EditBoxControlChars
{
	EDITBOX_CTRL_A = 1,
	EDITBOX_CTRL_C = 3,
	EDITBOX_CTRL_V = 22,
	EDITBOX_CTRL_X = 24,
};


//D2Win.0x6F8FD6B0
char gszClipboardText_6F8FD6B0[512];
//D2Win.0x6F8FD8B0
D2WinEditBoxStrc* gpLastClickedEditBox_6F8FD8B0;
//D2Win.0x6F8FD8B4
DWORD gdwLastClickTickCount_6F8FD8B4;
//D2Win.0x6F8FD8B8
HGLOBAL ghClipboardData_6F8FD8B8;


// Helper function, inlined in the original game
static BOOL EDITBOX_HasSelection(D2WinEditBoxStrc* pEditBox)
{
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	return pEditBox->nSelectionStart != -1 && pEditBox->nSelectionStart != pEditBox->nSelectionEnd;
}

// Helper function, inlined in the original game
static BOOL EDITBOX_IsControlChar(char nChar)
{
	return nChar == EDITBOX_CTRL_V || nChar == EDITBOX_CTRL_C || nChar == EDITBOX_CTRL_X || nChar == EDITBOX_CTRL_A;
}

// Helper function, inlined in the original game
static void EDITBOX_FillWithPasswordChars(Unicode* wszText, int32_t nLength)
{
	Unicode wszStar[2];
	Unicode::win2Unicode(wszStar, "*", 2);

	for (int32_t i = 0; i < nLength; ++i)
	{
		wszText[i] = wszStar[0];
	}
}

// Helper function, inlined in the original game. Returns the first index of the selection.
static int32_t EDITBOX_CopySelectionToClipboard(D2WinEditBoxStrc* pEditBox, const Unicode* wszText, char* szBuffer)
{
	const int32_t nSelectionMin = std::min(pEditBox->nSelectionStart, pEditBox->nSelectionEnd);
	const int32_t nSelectionMax = std::max(pEditBox->nSelectionStart, pEditBox->nSelectionEnd);

	Unicode::unicode2Win(szBuffer, &wszText[nSelectionMin], std::max(nSelectionMax - nSelectionMin + 1, 2));

	if (ghClipboardData_6F8FD8B8)
	{
		GlobalFree(ghClipboardData_6F8FD8B8);
		ghClipboardData_6F8FD8B8 = nullptr;
	}

	if (OpenClipboard(WINDOW_GetWindow()))
	{
		EmptyClipboard();

		const size_t nLength = strlen(szBuffer);
		ghClipboardData_6F8FD8B8 = GlobalAlloc(GMEM_DDESHARE, nLength + 1);
		if (ghClipboardData_6F8FD8B8)
		{
			char* pData = (char*)GlobalLock(ghClipboardData_6F8FD8B8);
			memcpy(pData, szBuffer, nLength);
			pData[nLength] = '\0';
			GlobalUnlock(ghClipboardData_6F8FD8B8);
			SetClipboardData(CF_TEXT, ghClipboardData_6F8FD8B8);
		}

		CloseClipboard();
	}

	return nSelectionMin;
}

//D2Win.0x6F8A6C80 (#10070)
D2WinEditBoxStrc* __fastcall D2Win_10070_EDITBOX_Create(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight, int32_t nTextOffsetX, int32_t nTextOffsetY, D2CellFileStrc* pCellFile, EditBoxReturnFunc pfOnReturn, int32_t(__stdcall* pfHandleMouseDown)(SMSGHANDLER_PARAMS*), int32_t nEditBoxFlags, const D2WinEditBoxFontStrc* pFont)
{
	D2WinEditBoxStrc* pEditBox = D2_CALLOC_STRC(D2WinEditBoxStrc);

	pEditBox->controlHeader.nType = D2WIN_EDITBOX;
	pEditBox->controlHeader.dwFlags |= gdwBitMasks[0] | gdwBitMasks[2];
	pEditBox->controlHeader.nImageX = nX;
	pEditBox->controlHeader.nImageY = nY;
	pEditBox->controlHeader.nWidth = nWidth;
	pEditBox->controlHeader.nHeight = nHeight;
	pEditBox->controlHeader.pCellFile = pCellFile;
	pEditBox->nTextOffsetX = nTextOffsetX;
	pEditBox->nTextOffsetY = nTextOffsetY;
	pEditBox->nMaxLength = 256;
	pEditBox->nFirstVisibleChar = 0;
	pEditBox->nLastVisibleChar = 0;
	pEditBox->nSelectionStart = -1;

	if (!(nEditBoxFlags & EDITBOX_MULTILINE))
	{
		pEditBox->controlHeader.pfDraw = sub_6F8A82D0;
		pEditBox->controlHeader.pfHandleMouseDown = sub_6F8A9120;
	}
	else
	{
		pEditBox->controlHeader.pfDraw = sub_6F8A86C0;
		pEditBox->controlHeader.pfHandleMouseDown = sub_6F8A97D0;
	}

	pEditBox->controlHeader.pfHandleMouseUp = EDITBOX_HandleMouseUp;
	pEditBox->pfOnReturn = pfOnReturn;
	pEditBox->controlHeader.pfHandleCharInput = nullptr;
	pEditBox->controlHeader.pfHandleVirtualKeyInput = nullptr;
	pEditBox->pfCharFilter = nullptr;
	pEditBox->controlHeader.field_34 = pfHandleMouseDown;
	pEditBox->controlHeader.pNext = nullptr;
	pEditBox->wszText[0] = 0;
	pEditBox->nCursorPosition = 0;
	pEditBox->dwEditBoxFlags = nEditBoxFlags;

	if (pFont)
	{
		pEditBox->eFont = pFont->eFont;
		pEditBox->nTextColor = pFont->nTextColor;
	}
	else
	{
		pEditBox->eFont = D2FONT_FONT16;
		pEditBox->nTextColor = 0;
	}

	pEditBox->pNext = nullptr;
	pEditBox->pPrevious = nullptr;

	CONTROL_AppendToList(&pEditBox->controlHeader);

	return pEditBox;
}

//D2Win.0x6F8A6DC0 (#10071)
int32_t __fastcall D2Win_10071_EDITBOX_Destroy(D2WinEditBoxStrc* pEditBox)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	return CONTROL_RemoveFromList(&pEditBox->controlHeader);
}

//D2Win.0x6F8A6E10 (#10072)
void __fastcall D2Win_10072(D2WinEditBoxStrc* pEditBox, EditBoxCharFilterFunc pfCharFilter)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	pEditBox->pfCharFilter = pfCharFilter;
}

//D2Win.0x6F8A6E60 (#10073)
void __fastcall D2Win_10073(D2WinEditBoxStrc* pEditBox, EditBoxTextChangedFunc pfOnTextChanged)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	pEditBox->pfOnTextChanged = pfOnTextChanged;
}

//D2Win.0x6F8A6EB0 (#10083)
void __fastcall D2Win_10083(D2WinEditBoxStrc* pEditBox)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	pEditBox->nSelectionStart = -1;
	pEditBox->nSelectionEnd = 0;
}

//D2Win.0x6F8A6F10 (#10082)
int32_t __fastcall D2Win_10082(D2WinEditBoxStrc* pEditBox)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	pEditBox->nSelectionStart = 0;
	pEditBox->nSelectionEnd = Unicode::strlen(pEditBox->wszText);

	return pEditBox->nSelectionEnd;
}

//D2Win.0x6F8A6F70 (#10074)
int32_t __fastcall D2Win_10074(D2WinEditBoxStrc* pEditBox, uint8_t nChar)
{
	// The character filter can modify the character
	char nCurrentChar = nChar;

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	if (!(pEditBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pEditBox->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 0;
	}

	if (nChar == '\t' && (pEditBox->dwEditBoxFlags & 4))
	{
		if (pEditBox->pfCharFilter)
		{
			++dword_6F8FE254;
			pEditBox->pfCharFilter(pEditBox, pEditBox->nCursorPosition, &nCurrentChar);
			--dword_6F8FE254;
		}

		return 0;
	}

	if (!D2Win_10128(nChar)
		&& !((pEditBox->dwEditBoxFlags & 0x20) && nChar == 0xFF)
		&& !((pEditBox->dwEditBoxFlags & EDITBOX_MULTILINE) && nCurrentChar == '\r')
		&& !((pEditBox->dwEditBoxFlags & 0x10) && nCurrentChar == 14)
		&& !EDITBOX_IsControlChar(nCurrentChar))
	{
		return 0;
	}

	if (pEditBox->pfCharFilter && !pEditBox->pfCharFilter(pEditBox, pEditBox->nCursorPosition, &nCurrentChar) && !EDITBOX_IsControlChar(nCurrentChar))
	{
		return 0;
	}

	if (EDITBOX_HasSelection(pEditBox) && nCurrentChar != EDITBOX_CTRL_C && nCurrentChar != EDITBOX_CTRL_X && nCurrentChar != EDITBOX_CTRL_A)
	{
		sub_6F8A7970(pEditBox);
	}

	const int32_t nTextLength = Unicode::strlen(pEditBox->wszText);

	Unicode wszText[512];
	Unicode::strcpy(wszText, pEditBox->wszText);

	Unicode* pCursor = &wszText[pEditBox->nCursorPosition];

	char szText[400] = {};
	switch (nCurrentChar)
	{
	case EDITBOX_CTRL_V:
	{
		static char szEmptyString[] = "";

		char* szClipboardText = szEmptyString;
		if (IsClipboardFormatAvailable(CF_TEXT) && OpenClipboard(WINDOW_GetWindow()))
		{
			HANDLE hData = GetClipboardData(CF_TEXT);
			if (hData)
			{
				const char* pData = (const char*)GlobalLock(hData);
				if (pData)
				{
					strncpy(gszClipboardText_6F8FD6B0, pData, sizeof(gszClipboardText_6F8FD6B0));
					GlobalUnlock(hData);
				}
			}

			CloseClipboard();
			szClipboardText = gszClipboardText_6F8FD6B0;
		}

		if (nTextLength + (int32_t)strlen(szClipboardText) > pEditBox->nMaxLength - 1)
		{
			return 0;
		}

		if (pEditBox->pfCharFilter)
		{
			const int32_t nLength = strlen(szClipboardText);
			for (int32_t i = 0; i < nLength; ++i)
			{
				if (!D2Win_10128(szClipboardText[i]) || !pEditBox->pfCharFilter(pEditBox, pEditBox->nCursorPosition + i, &szClipboardText[i]))
				{
					return 0;
				}
			}
		}

		Unicode wszBefore[256];
		Unicode wszPasted[256];
		Unicode wszAfter[256];

		int32_t nStart = 0;
		int32_t nEnd = 0;
		if (pEditBox->nSelectionStart == -1)
		{
			nStart = pEditBox->nCursorPosition;
			nEnd = pEditBox->nCursorPosition;
		}
		else
		{
			nStart = std::min(pEditBox->nSelectionStart, pEditBox->nSelectionEnd);
			nEnd = std::max(pEditBox->nSelectionStart, pEditBox->nSelectionEnd);
		}

		if (pEditBox->dwEditBoxFlags & EDITBOX_MULTILINE)
		{
			strcpy(szText, szClipboardText);
		}
		else
		{
			char* pDest = szText;
			for (const char* pSrc = szClipboardText; *pSrc; ++pSrc)
			{
				if (*pSrc != '\r' && *pSrc != '\n')
				{
					*pDest = *pSrc;
					++pDest;
				}
			}
			*pDest = '\0';
		}

		Unicode::strncpy(wszBefore, wszText, nStart);
		Unicode::strcpy(wszAfter, &wszText[nEnd]);
		Unicode::win2Unicode(wszPasted, szText, strlen(szText) + 1);
		Unicode::strcpy(wszText, wszBefore);
		Unicode::strcat(wszText, wszPasted);
		Unicode::strcat(wszText, wszAfter);

		D2Win_10083(pEditBox);

		pCursor = &wszText[nStart + strlen(szText)];
		break;
	}
	case EDITBOX_CTRL_C:
		if (EDITBOX_HasSelection(pEditBox))
		{
			EDITBOX_CopySelectionToClipboard(pEditBox, wszText, szText);
		}
		break;

	case EDITBOX_CTRL_X:
		if (EDITBOX_HasSelection(pEditBox))
		{
			const int32_t nSelectionMin = EDITBOX_CopySelectionToClipboard(pEditBox, wszText, szText);

			sub_6F8A7970(pEditBox);
			Unicode::strcpy(wszText, pEditBox->wszText);
			pCursor = &wszText[nSelectionMin];
		}
		break;

	case EDITBOX_CTRL_A:
		D2Win_10082(pEditBox);
		break;

	default:
		if (nTextLength >= pEditBox->nMaxLength - 1)
		{
			return 0;
		}

		if (nTextLength < 255)
		{
			char szBuffer[512];
			if (nCurrentChar == '\r')
			{
				Unicode::unicode2Win(&szBuffer[2], pCursor, 256);
				szBuffer[0] = '\r';
				szBuffer[1] = '\n';
				Unicode::win2Unicode(pCursor, szBuffer, 256);
				pCursor += 2;
			}
			else
			{
				Unicode::unicode2Win(&szBuffer[1], pCursor, 256);
				szBuffer[0] = nCurrentChar;
				Unicode::win2Unicode(pCursor, szBuffer, 256);
				++pCursor;
			}

			D2Win_10083(pEditBox);
		}
		break;
	}

	const int32_t nAvailableHeight = pEditBox->controlHeader.nHeight - 2 * pEditBox->nTextOffsetY;
	if (pEditBox->dwEditBoxFlags & EDITBOX_MULTILINE)
	{
		// Rejects the new text if it doesn't fit in the edit box
		D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);
		D2Win_10127_SetFont(pEditBox->eFont);

		const int32_t nStartY = D2Win_10125() + pEditBox->controlHeader.nImageY - pEditBox->controlHeader.nHeight + pEditBox->nTextOffsetY;

		Unicode wszCursor[2];
		Unicode::win2Unicode(wszCursor, "_", 2);
		const int32_t nCursorWidth = D2Win_10122(wszCursor, 2);

		Unicode wszLine[256];
		char szMultilineText[512];
		Unicode::unicode2Win(szMultilineText, wszText, 256);

		int32_t nY = nStartY;
		const int32_t nLineHeight = D2Win_10125();
		const int32_t nAvailableWidth = pEditBox->controlHeader.nWidth - 2 * pEditBox->nTextOffsetX;

		const char* pLineStart = szMultilineText;
		const char* pCurrent = szMultilineText;
		while (*pCurrent)
		{
			int32_t nIndex = pCurrent - pLineStart;
			BOOL bWrapped = FALSE;

			char szLine[256] = {};
			while (*pCurrent && *pCurrent != '\r' && *pCurrent != '\n')
			{
				szLine[nIndex] = *pCurrent;
				Unicode::win2Unicode(wszLine, szLine, 256);
				if (D2Win_10122(wszLine, nIndex) + nCursorWidth > nAvailableWidth)
				{
					bWrapped = TRUE;
					break;
				}

				++pCurrent;
				++nIndex;
			}

			Unicode::win2Unicode(wszLine, szLine, 256);

			if (bWrapped)
			{
				nY += nLineHeight;
			}

			if (*pCurrent == '\r')
			{
				if (pCurrent[1] == '\n')
				{
					do
					{
						if (pCurrent[1] != '\n')
						{
							break;
						}

						pCurrent += 2;
						nY += nLineHeight;
					}
					while (*pCurrent == '\r');
				}
				else
				{
					do
					{
						++pCurrent;
						nY += nLineHeight;
					}
					while (*pCurrent == '\r');
				}
			}

			pLineStart = pCurrent;
		}

		if (nY - nStartY >= nAvailableHeight)
		{
			return 1;
		}
	}

	Unicode::strcpy(pEditBox->wszText, wszText);
	pEditBox->nCursorPosition = pCursor - wszText;
	sub_6F8A98A0(pEditBox);

	if (pEditBox->pfOnTextChanged)
	{
		pEditBox->pfOnTextChanged(0);
	}

	return 1;
}

//D2Win.0x6F8A7970
void __fastcall sub_6F8A7970(D2WinEditBoxStrc* pEditBox)
{
	Unicode wszBefore[256];
	Unicode wszAfter[256];

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	const int32_t nSelectionMin = std::min(pEditBox->nSelectionStart, pEditBox->nSelectionEnd);
	const int32_t nSelectionMax = std::max(pEditBox->nSelectionStart, pEditBox->nSelectionEnd);

	if (nSelectionMin)
	{
		Unicode::strncpy(wszBefore, pEditBox->wszText, nSelectionMin);
	}
	else
	{
		wszBefore[0] = 0;
	}

	Unicode::strcpy(wszAfter, &pEditBox->wszText[nSelectionMax]);
	Unicode::strcpy(pEditBox->wszText, wszBefore);
	Unicode::strcat(pEditBox->wszText, wszAfter);

	const int32_t nTextLength = Unicode::strlen(pEditBox->wszText);
	pEditBox->nCursorPosition = std::min(nSelectionMin, nTextLength);

	D2Win_10083(pEditBox);
}

//D2Win.0x6F8A7AB0
int32_t __fastcall sub_6F8A7AB0(D2WinEditBoxStrc* pEditBox, char nVirtualKey)
{
	// The character filter can modify the key
	char nCurrentKey = nVirtualKey;

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	if (!(pEditBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pEditBox->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 0;
	}

	BOOL bSelectionDeleted = FALSE;
	BOOL bTextChanged = FALSE;
	Unicode* pCursor = &pEditBox->wszText[pEditBox->nCursorPosition];
	const BOOL bShiftPressed = ((uint16_t)GetKeyState(VK_SHIFT) >> 15) & 1;

	switch (nVirtualKey)
	{
	case VK_BACK:
	case VK_DELETE:
		if (EDITBOX_HasSelection(pEditBox))
		{
			sub_6F8A7970(pEditBox);
			bSelectionDeleted = TRUE;
			bTextChanged = TRUE;
			pCursor = &pEditBox->wszText[pEditBox->nCursorPosition];
		}
		break;

	case VK_END:
	case VK_HOME:
	case VK_LEFT:
	case VK_UP:
	case VK_RIGHT:
	case VK_DOWN:
		if (bShiftPressed)
		{
			if (pEditBox->nSelectionStart == -1)
			{
				pEditBox->nSelectionStart = pEditBox->nCursorPosition;
				pEditBox->nSelectionEnd = pEditBox->nCursorPosition;
			}
		}
		else
		{
			D2Win_10083(pEditBox);
		}
		break;

	default:
		break;
	}

	switch (nVirtualKey)
	{
	case VK_BACK:
		if (pCursor > pEditBox->wszText && !bSelectionDeleted)
		{
			--pCursor;

			const int32_t nSize = sizeof(Unicode) * (Unicode::strlen(pCursor + 1) + 1);
			memmove(pCursor, pCursor + 1, nSize);

			if (pCursor > pEditBox->wszText && pCursor[-1].ch == '\r')
			{
				--pCursor;
				memmove(pCursor, pCursor + 1, nSize);
			}

			bTextChanged = TRUE;
		}
		break;

	case VK_TAB:
	{
		D2WinEditBoxStrc* pTarget = nullptr;
		if (GetKeyState(VK_SHIFT) < 0)
		{
			pTarget = pEditBox->pPrevious;
			if (!pTarget)
			{
				return 1;
			}

			while (pTarget != pEditBox && !((pTarget->controlHeader.dwFlags & gdwBitMasks[2]) && (pTarget->controlHeader.dwFlags & gdwBitMasks[0])))
			{
				pTarget = pTarget->pPrevious;
				if (!pTarget)
				{
					break;
				}
			}
		}
		else
		{
			pTarget = pEditBox->pNext;
			if (!pTarget)
			{
				return 1;
			}

			while (pTarget != pEditBox && !((pTarget->controlHeader.dwFlags & gdwBitMasks[2]) && (pTarget->controlHeader.dwFlags & gdwBitMasks[0])))
			{
				pTarget = pTarget->pNext;
				if (!pTarget)
				{
					break;
				}
			}
		}

		D2Win_10012(pTarget);
		D2Win_10082(pTarget);
		return 1;
	}
	case VK_RETURN:
		if (pEditBox->pfOnReturn)
		{
			const uint32_t bUpdateText = pEditBox->dwEditBoxFlags & 2;

			++dword_6F8FE254;
			pEditBox->pfOnReturn(pEditBox->wszText);
			--dword_6F8FE254;

			if (!bUpdateText)
			{
				return 1;
			}

			pCursor = &pEditBox->wszText[pEditBox->nCursorPosition];
		}
		break;

	case VK_ESCAPE:
		if (pEditBox->pfOnReturn)
		{
			++dword_6F8FE254;
			pEditBox->pfOnReturn(nullptr);
			--dword_6F8FE254;
		}
		return 1;

	case VK_END:
		while (pCursor->ch)
		{
			++pCursor;
		}

		if (bShiftPressed)
		{
			pEditBox->nSelectionEnd = pCursor - pEditBox->wszText;
		}
		break;

	case VK_HOME:
		pCursor = pEditBox->wszText;
		if (bShiftPressed)
		{
			pEditBox->nSelectionEnd = 0;
		}
		break;

	case VK_LEFT:
		--pCursor;
		if (pCursor->ch == '\n')
		{
			--pCursor;
		}

		if (pCursor < pEditBox->wszText)
		{
			pCursor = pEditBox->wszText;
		}
		else if (bShiftPressed && pEditBox->nSelectionStart != -1)
		{
			pEditBox->nSelectionEnd = pCursor - pEditBox->wszText;
		}
		break;

	case VK_UP:
		if (pEditBox->dwEditBoxFlags & EDITBOX_MULTILINE)
		{
			int32_t nX = 0;
			int32_t nY = 0;
			sub_6F8A8D60(pEditBox, &nX, &nY);

			SMSGHANDLER_PARAMS msg = {};
			msg.hWindow = (HWND)pEditBox;
			msg.nMessage = 0;
			sub_6F8A9410(&msg, nX, nY - D2Win_10125());

			pCursor = &pEditBox->wszText[pEditBox->nCursorPosition];
		}
		else
		{
			pCursor = pEditBox->wszText;
			if (bShiftPressed)
			{
				pEditBox->nSelectionEnd = 0;
			}
		}
		break;

	case VK_RIGHT:
		if (pCursor->ch)
		{
			++pCursor;
			if (pCursor->ch && pCursor->ch == '\n')
			{
				++pCursor;
			}

			if (bShiftPressed && pEditBox->nSelectionStart != -1)
			{
				pEditBox->nSelectionEnd = pCursor - pEditBox->wszText;
			}
		}
		break;

	case VK_DOWN:
		if (pEditBox->dwEditBoxFlags & EDITBOX_MULTILINE)
		{
			int32_t nX = 0;
			int32_t nY = 0;
			sub_6F8A8D60(pEditBox, &nX, &nY);

			SMSGHANDLER_PARAMS msg = {};
			msg.hWindow = (HWND)pEditBox;
			msg.nMessage = 0;
			sub_6F8A9410(&msg, nX, nY + D2Win_10125());

			pCursor = &pEditBox->wszText[pEditBox->nCursorPosition];
		}
		else
		{
			while (pCursor->ch)
			{
				++pCursor;
			}

			if (bShiftPressed)
			{
				pEditBox->nSelectionEnd = pCursor - pEditBox->wszText;
			}
		}
		break;

	case VK_DELETE:
		if (pCursor->ch && !bSelectionDeleted)
		{
			const int32_t nCount = Unicode::strlen(pCursor + 1) + 1;
			memmove(pCursor, pCursor + 1, sizeof(Unicode) * nCount);

			if (pCursor->ch && pCursor->ch == '\n')
			{
				memmove(pCursor, pCursor + 1, sizeof(Unicode) * (nCount - 1));
			}

			bTextChanged = TRUE;
		}
		break;

	case VK_F1:
		return 0;

	default:
		break;
	}

	pEditBox->nCursorPosition = pCursor - pEditBox->wszText;
	sub_6F8A98A0(pEditBox);

	if (bTextChanged && pEditBox->pfCharFilter && !pEditBox->pfCharFilter(pEditBox, pEditBox->nCursorPosition, &nCurrentKey) && nCurrentKey != VK_BACK && nCurrentKey != VK_DELETE)
	{
		return 0;
	}

	if (pEditBox->pfOnTextChanged)
	{
		pEditBox->pfOnTextChanged(0);
	}

	return 1;
}

//D2Win.0x6F8A80A0 (#10081)
void __fastcall D2Win_10081(D2WinEditBoxStrc* pEditBox, int32_t nMaxLength)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	pEditBox->nMaxLength = nMaxLength;
}

//D2Win.0x6F8A80F0 (#10076)
int32_t __fastcall D2Win_10076(D2WinEditBoxStrc* pEditBox, const char* szText)
{
	Unicode wszText[256] = {};

	Unicode::win2Unicode(wszText, szText, 256);
	return D2Win_10075(pEditBox, wszText);
}

//D2Win.0x6F8A8140 (#10075)
int32_t __fastcall D2Win_10075(D2WinEditBoxStrc* pEditBox, const Unicode* pText)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	const int32_t nLength = Unicode::strlen(pText);
	if (nLength)
	{
		Unicode::strcpy(pEditBox->wszText, pText);
	}
	else
	{
		pEditBox->wszText[0] = 0;
	}

	pEditBox->nCursorPosition = nLength;
	sub_6F8A98A0(pEditBox);

	if (pEditBox->pfOnTextChanged)
	{
		pEditBox->pfOnTextChanged(0);
	}

	return 1;
}

//D2Win.0x6F8A81E0 (#10077)
const Unicode* __fastcall D2Win_10077_EDITBOX_GetText(D2WinEditBoxStrc* pEditBox)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	return pEditBox->wszText;
}

//D2Win.0x6F8A8230 (#10080)
void __fastcall D2Win_10080_EDITBOX_SetNextEditBox(D2WinEditBoxStrc* pEditBox, D2WinEditBoxStrc* pNext)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	D2_ASSERT(pNext);
	D2_ASSERT(pNext->controlHeader.nType == D2WIN_EDITBOX);

	pEditBox->pNext = pNext;
	pNext->pPrevious = pEditBox;
}

//D2Win.0x6F8A82D0
int32_t __fastcall sub_6F8A82D0(D2WinControlStrc* pControl)
{
	D2WinEditBoxStrc* pEditBox = (D2WinEditBoxStrc*)pControl;

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	if (!(pEditBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pEditBox->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 1;
	}

	if (!D2Win_IsMouseButtonPressed())
	{
		pEditBox->bMouseSelecting = 0;
	}

	if (pEditBox->bMouseSelecting)
	{
		SMSGHANDLER_PARAMS msg = {};
		msg.hWindow = (HWND)pEditBox;
		msg.nMessage = WM_LBUTTONDOWN;
		sub_6F8A9120(&msg);
	}

	Unicode wszVisibleText[300];

	if (pEditBox->controlHeader.pCellFile)
	{
		D2GfxDataStrc gfxData = {};
		gfxData.pCellFile = pEditBox->controlHeader.pCellFile;
		gfxData.nDirection = 0;
		gfxData.nFrame = 0;
		TEXTURE_CelDraw(&gfxData, pEditBox->controlHeader.nImageX, pEditBox->controlHeader.nImageY - 1, -1, DRAWMODE_NORMAL, 0);
	}

	D2Win_10127_SetFont(pEditBox->eFont);

	int32_t nX = pEditBox->controlHeader.nImageX + pEditBox->nTextOffsetX;
	const int32_t nY = pEditBox->nTextOffsetY - pEditBox->controlHeader.nHeight + pEditBox->controlHeader.nImageY + 16;

	Unicode::strncpy(wszVisibleText, &pEditBox->wszText[pEditBox->nFirstVisibleChar], pEditBox->nLastVisibleChar - pEditBox->nFirstVisibleChar + 1);

	const int32_t nVisibleTextLength = Unicode::strlen(wszVisibleText);
	if (pEditBox->dwEditBoxFlags & EDITBOX_PASSWORD)
	{
		EDITBOX_FillWithPasswordChars(wszVisibleText, nVisibleTextLength);
	}

	if (EDITBOX_HasSelection(pEditBox))
	{
		const uint8_t nSelectionColor = D2Win_10034_MixRGB(0x40u, 0x40u, 0x40u);

		Unicode wszBefore[256];
		Unicode wszSelection[256];
		Unicode wszAfter[256];

		const int32_t nBeforeLength = std::max(std::min(pEditBox->nSelectionStart, pEditBox->nSelectionEnd) - pEditBox->nFirstVisibleChar, 0);
		const int32_t nSelectionLength = std::max(std::max(pEditBox->nSelectionStart, pEditBox->nSelectionEnd) - pEditBox->nFirstVisibleChar - nBeforeLength, 0);

		Unicode::strncpy(wszBefore, wszVisibleText, nBeforeLength);
		Unicode::strncpy(wszSelection, &wszVisibleText[nBeforeLength], nSelectionLength);
		Unicode::strcpy(wszAfter, &wszVisibleText[nBeforeLength + nSelectionLength]);

		int32_t nBeforeWidth = 0;
		int32_t nSelectionWidth = 0;
		int32_t nHeight = 0;
		D2Win_10131_GetTextDimensions(wszBefore, &nBeforeWidth, &nHeight);
		D2Win_10131_GetTextDimensions(wszSelection, &nSelectionWidth, &nHeight);
		D2Win_10117_DrawText(wszBefore, nX, nY, pEditBox->nTextColor, 0);
		D2Win_10133(wszSelection, nX + nBeforeWidth, nY, nSelectionColor, DRAWMODE_NORMAL, pEditBox->nTextColor);
		D2Win_10117_DrawText(wszAfter, nX + nBeforeWidth + nSelectionWidth, nY, pEditBox->nTextColor, 0);
	}
	else
	{
		D2Win_10117_DrawText(wszVisibleText, nX, nY, pEditBox->nTextColor, 0);
	}

	if (D2Win_10023() == pEditBox && GetTickCount() / 250 & 1)
	{
		Unicode wszCursor[2];
		Unicode::win2Unicode(wszCursor, "_", 2);

		if (pEditBox->nCursorPosition != pEditBox->nFirstVisibleChar)
		{
			nX += D2Win_10122(wszVisibleText, pEditBox->nCursorPosition - pEditBox->nFirstVisibleChar);
		}

		D2Win_10117_DrawText(wszCursor, nX, nY, pEditBox->nTextColor, 0);
	}

	return 1;
}

//D2Win.0x6F8A86C0
int32_t __fastcall sub_6F8A86C0(D2WinControlStrc* pControl)
{
	D2WinEditBoxStrc* pEditBox = (D2WinEditBoxStrc*)pControl;

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	if (!(pEditBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pEditBox->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 1;
	}

	if (!D2Win_IsMouseButtonPressed())
	{
		pEditBox->bMouseSelecting = 0;
	}

	if (pEditBox->bMouseSelecting)
	{
		SMSGHANDLER_PARAMS msg = {};
		msg.hWindow = (HWND)pEditBox;
		msg.nMessage = WM_LBUTTONDOWN;
		sub_6F8A97D0(&msg);
	}

	Unicode wszText[300];
	D2Win_10127_SetFont(pEditBox->eFont);

	const int32_t nX = pEditBox->controlHeader.nImageX + pEditBox->nTextOffsetX;
	int32_t nY = D2Win_10125() + pEditBox->controlHeader.nImageY - pEditBox->controlHeader.nHeight + pEditBox->nTextOffsetY;
	const int32_t nStartY = nY;

	// Unused
	Unicode::strcpy(wszText, pEditBox->wszText);

	const uint8_t nSelectionColor = D2Win_10034_MixRGB(0x40u, 0x40u, 0x40u);

	Unicode wszCursor[2];
	Unicode::win2Unicode(wszCursor, "_", 2);
	const int32_t nCursorWidth = D2Win_10122(wszCursor, 2);

	const BOOL bDrawCursor = D2Win_10023() == pEditBox && (GetTickCount() / 250 & 1);
	BOOL bCursorDrawn = FALSE;

	Unicode wszLine[256];
	char szText[256];
	Unicode::unicode2Win(szText, pEditBox->wszText, 256);

	const char* pLineStart = szText;
	const char* pCurrent = szText;
	const int32_t nLineHeight = D2Win_10125();
	const int32_t nAvailableWidth = pEditBox->controlHeader.nWidth - 2 * pEditBox->nTextOffsetX;
	const int32_t nAvailableHeight = pEditBox->controlHeader.nHeight - 2 * pEditBox->nTextOffsetY;

	if (!szText[0])
	{
		if (bDrawCursor)
		{
			D2Win_10117_DrawText(wszCursor, nX, nStartY, pEditBox->nTextColor, 0);
		}

		return 1;
	}

	do
	{
		if (nY - nStartY >= nAvailableHeight)
		{
			break;
		}

		int32_t nLength = pCurrent - pLineStart;
		char szLine[256] = {};
		BOOL bWrapped = FALSE;
		while (*pCurrent && *pCurrent != '\r' && *pCurrent != '\n')
		{
			szLine[nLength] = *pCurrent;
			Unicode::win2Unicode(wszLine, szLine, 256);
			if (D2Win_10122(wszLine, nLength) + nCursorWidth > nAvailableWidth)
			{
				bWrapped = TRUE;
				break;
			}

			++pCurrent;
			++nLength;
		}

		if (EDITBOX_HasSelection(pEditBox))
		{
			const int32_t nSelectionMin = std::min(pEditBox->nSelectionStart, pEditBox->nSelectionEnd);
			const int32_t nSelectionMax = std::max(pEditBox->nSelectionStart, pEditBox->nSelectionEnd);
			const int32_t nLineStartIndex = pLineStart - szText;
			const int32_t nLineEndIndex = pCurrent - szText;

			int32_t nTextWidth = 0;
			int32_t nTextHeight = 0;
			if (nSelectionMin < nLineStartIndex && nSelectionMax >= nLineEndIndex)
			{
				// The whole line is selected
				strncpy(szLine, pLineStart, nLength);
				szLine[pCurrent - pLineStart] = '\0';
				Unicode::win2Unicode(wszLine, szLine, 256);
				D2Win_10131_GetTextDimensions(wszLine, &nTextWidth, &nTextHeight);
				D2GFX_DrawBox(nX, nY - nLineHeight, nX + nTextWidth, nY, nSelectionColor, DRAWMODE_NORMAL);
			}
			else if ((nSelectionMin >= nLineStartIndex && nSelectionMin < nLineEndIndex) || (nSelectionMax >= nLineStartIndex && nSelectionMax < nLineEndIndex))
			{
				const int32_t nFrom = std::max(nSelectionMin, nLineStartIndex);
				const int32_t nTo = std::min(nSelectionMax, nLineEndIndex);
				const int32_t nPrefixLength = nFrom - nLineStartIndex;

				int32_t nBoxX = nX;
				if (nPrefixLength)
				{
					strncpy(szLine, pLineStart, nPrefixLength);
					szLine[nPrefixLength] = '\0';
					Unicode::win2Unicode(wszLine, szLine, 256);
					D2Win_10131_GetTextDimensions(wszLine, &nTextWidth, &nTextHeight);
					nBoxX = nTextWidth + nX;
				}

				const int32_t nSelectionLength = nTo - nFrom;
				strncpy(szLine, &pLineStart[nPrefixLength], nSelectionLength);
				szLine[nSelectionLength] = '\0';
				Unicode::win2Unicode(wszLine, szLine, 256);
				D2Win_10131_GetTextDimensions(wszLine, &nTextWidth, &nTextHeight);
				D2GFX_DrawBox(nBoxX, nY - nLineHeight, nBoxX + nTextWidth, nY, nSelectionColor, DRAWMODE_NORMAL);
			}
		}

		strncpy(szLine, pLineStart, nLength);
		szLine[pCurrent - pLineStart] = '\0';
		Unicode::win2Unicode(wszLine, szLine, 256);
		D2Win_10117_DrawText(wszLine, nX, nY, pEditBox->nTextColor, 0);

		if (bDrawCursor && !bCursorDrawn)
		{
			const int32_t nCursorIndex = pEditBox->nCursorPosition - (pLineStart - szText);
			if (nCursorIndex >= 0 && nCursorIndex <= nLength)
			{
				int32_t nCursorX = nX;
				if (nCursorIndex)
				{
					nCursorX = D2Win_10122(wszLine, nCursorIndex) + nX;
				}

				D2Win_10117_DrawText(wszCursor, nCursorX, nY, pEditBox->nTextColor, 0);
				bCursorDrawn = TRUE;
			}
		}

		if (bWrapped)
		{
			nY += nLineHeight;
		}

		if (*pCurrent == '\r')
		{
			int32_t nIndex = pCurrent - szText;
			int32_t nOffsetY = nY - nStartY;
			if (pCurrent[1] == '\n')
			{
				do
				{
					if (pCurrent[1] != '\n')
					{
						break;
					}

					pCurrent += 2;
					nIndex += 2;
					nY += nLineHeight;
					nOffsetY += nLineHeight;

					// The original game doesn't set bCursorDrawn here
					if (bDrawCursor && !bCursorDrawn && pEditBox->nCursorPosition == nIndex && nOffsetY < nAvailableHeight)
					{
						D2Win_10117_DrawText(wszCursor, nX, nY, pEditBox->nTextColor, 0);
					}
				}
				while (*pCurrent == '\r');
			}
			else
			{
				do
				{
					++pCurrent;
					++nIndex;
					nY += nLineHeight;
					nOffsetY += nLineHeight;

					// The original game doesn't set bCursorDrawn here
					if (bDrawCursor && !bCursorDrawn && pEditBox->nCursorPosition == nIndex && nOffsetY < nAvailableHeight)
					{
						D2Win_10117_DrawText(wszCursor, nX, nY, pEditBox->nTextColor, 0);
					}
				}
				while (*pCurrent == '\r');
			}
		}

		pLineStart = pCurrent;
	}
	while (*pCurrent);

	return 1;
}

//D2Win.0x6F8A8D60
void __fastcall sub_6F8A8D60(D2WinEditBoxStrc* pEditBox, int32_t* pX, int32_t* pY)
{
	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	D2Win_10127_SetFont(pEditBox->eFont);

	const int32_t nStartX = pEditBox->controlHeader.nImageX + pEditBox->nTextOffsetX;
	const int32_t nLineHeight = D2Win_10125();
	const int32_t nStartY = pEditBox->nTextOffsetY + pEditBox->controlHeader.nImageY - pEditBox->controlHeader.nHeight + nLineHeight;
	int32_t nY = nStartY;

	Unicode wszCursor[2] = {};
	Unicode::win2Unicode(wszCursor, "_", 2);

	const int32_t nCursorWidth = D2Win_10122(wszCursor, 2);

	char szText[256] = {};
	Unicode::unicode2Win(szText, pEditBox->wszText, ARRAY_SIZE(szText));
	const char* pCurrent = szText;
	const char* pLineStart = szText;
	const int32_t nAvailableWidth = pEditBox->controlHeader.nWidth - 2 * pEditBox->nTextOffsetX;
	const int32_t nAvailableHeight = pEditBox->controlHeader.nHeight - 2 * pEditBox->nTextOffsetY;

	*pX = -1;
	*pY = -1;

	while (*pCurrent)
	{
		if (nY - nStartY >= nAvailableHeight)
		{
			break;
		}

		int32_t nLength = pCurrent - pLineStart;
		char szLine[256] = {};
		Unicode wszLine[256] = {};
		BOOL bWrapped = FALSE;
		while (*pCurrent && *pCurrent != '\r' && *pCurrent != '\n')
		{
			szLine[nLength] = *pCurrent;
			Unicode::win2Unicode(wszLine, szLine, 256);
			if (nCursorWidth + D2Win_10122(wszLine, nLength) > nAvailableWidth)
			{
				bWrapped = TRUE;
				break;
			}

			++pCurrent;
			++nLength;
		}

		const int32_t nCursorIndex = pEditBox->nCursorPosition - (pLineStart - szText);
		if (*pX == -1 && nCursorIndex >= 0 && nCursorIndex <= nLength)
		{
			*pX = nStartX;
			if (nCursorIndex)
			{
				Unicode::win2Unicode(wszLine, szLine, 256);
				*pX += D2Win_10122(wszLine, nCursorIndex);
			}
			*pY = nY;
		}

		if (bWrapped)
		{
			nY += nLineHeight;
		}

		if (*pCurrent == '\r')
		{
			int32_t nIndex = pCurrent - szText;
			int32_t nOffsetY = nY - nStartY;
			if (pCurrent[1] == '\n')
			{
				do
				{
					if (pCurrent[1] != '\n')
					{
						break;
					}

					pCurrent += 2;
					nIndex += 2;
					nY += nLineHeight;
					nOffsetY += nLineHeight;
					if (*pX == -1 && pEditBox->nCursorPosition == nIndex && nOffsetY < nAvailableHeight)
					{
						*pX = nStartX;
						*pY = nY;
					}
				}
				while (*pCurrent == '\r');
			}
			else
			{
				do
				{
					++pCurrent;
					++nIndex;
					nY += nLineHeight;
					nOffsetY += nLineHeight;
					if (*pX == -1 && pEditBox->nCursorPosition == nIndex && nOffsetY < nAvailableHeight)
					{
						*pX = nStartX;
						*pY = nY;
					}
				}
				while (*pCurrent == '\r');
			}
		}

		pLineStart = pCurrent;
	}

	if (*pX != -1)
	{
		*pX = *pX - pEditBox->controlHeader.nImageX - 1;
		*pY += pEditBox->controlHeader.nHeight - pEditBox->controlHeader.nImageY - 1;

		*pX = D2Clamp(*pX, pEditBox->nTextOffsetX, pEditBox->controlHeader.nWidth - pEditBox->nTextOffsetX - 1);
		*pY = D2Clamp(*pY, pEditBox->nTextOffsetY, pEditBox->controlHeader.nHeight - pEditBox->nTextOffsetY - 1);
	}
}

//D2Win.0x6F8A9120
int32_t __stdcall sub_6F8A9120(SMSGHANDLER_PARAMS* pMsg)
{
	D2WinEditBoxStrc* pEditBox = (D2WinEditBoxStrc*)pMsg->hWindow;

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	if (!(pEditBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pEditBox->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 0;
	}

	D2Win_10012(pEditBox);

	const int32_t nX = gMousePosition_6F8FE234.x - pEditBox->nTextOffsetX - pEditBox->controlHeader.nImageX;
	const int32_t nY = pEditBox->controlHeader.nHeight - pEditBox->nTextOffsetY - pEditBox->controlHeader.nImageY + gMousePosition_6F8FE234.y;

	const bool bInside = nX >= -pEditBox->nTextOffsetX && nX < pEditBox->controlHeader.nWidth - pEditBox->nTextOffsetX && nY > -pEditBox->nTextOffsetY && nY < pEditBox->controlHeader.nHeight - pEditBox->nTextOffsetY;
	const uint32_t dwTickCount = GetTickCount();

	if (bInside && !pEditBox->bMouseSelecting && pEditBox == gpLastClickedEditBox_6F8FD8B0 && dwTickCount - gdwLastClickTickCount_6F8FD8B4 < 300)
	{
		// Double click
		D2Win_10082(pEditBox);
	}
	else
	{
		if (pEditBox->bMouseSelecting || bInside)
		{
			D2Win_10127_SetFont(pEditBox->eFont);

			if (pEditBox->bMouseSelecting)
			{
				if (nX < -pEditBox->nTextOffsetX)
				{
					pEditBox->nCursorPosition = std::max(pEditBox->nCursorPosition - 1, 0);
					sub_6F8A98A0(pEditBox);
				}
				else if (nX >= pEditBox->controlHeader.nWidth - pEditBox->nTextOffsetX)
				{
					pEditBox->nCursorPosition = std::min(pEditBox->nCursorPosition + 1, Unicode::strlen(pEditBox->wszText) - 1);
					sub_6F8A98A0(pEditBox);
				}
			}

			int32_t nCounter = 1;
			while (nX > D2Win_10122(&pEditBox->wszText[pEditBox->nFirstVisibleChar], nCounter))
			{
				if (nCounter > Unicode::strlen(&pEditBox->wszText[pEditBox->nFirstVisibleChar]))
				{
					break;
				}
				++nCounter;
			}

			const int32_t nPreviousCursorPosition = pEditBox->nCursorPosition;
			pEditBox->nCursorPosition = pEditBox->nFirstVisibleChar + nCounter - 1;

			if ((GetKeyState(VK_SHIFT) & 0x8000) || pEditBox->bMouseSelecting)
			{
				if (pEditBox->nSelectionStart == -1)
				{
					pEditBox->nSelectionStart = nPreviousCursorPosition;
				}

				pEditBox->nSelectionEnd = pEditBox->nCursorPosition;
			}
			else
			{
				D2Win_10083(pEditBox);
			}
		}

		if (pMsg->nMessage == WM_LBUTTONDOWN)
		{
			pEditBox->bMouseSelecting = 1;
		}
	}

	gpLastClickedEditBox_6F8FD8B0 = pEditBox;
	gdwLastClickTickCount_6F8FD8B4 = dwTickCount;

	if (pEditBox->controlHeader.field_34)
	{
		return pEditBox->controlHeader.field_34(pMsg);
	}

	return 0;
}

//D2Win.0x6F8A93A0
int32_t __stdcall EDITBOX_HandleMouseUp(SMSGHANDLER_PARAMS* pMsg)
{
	D2WinEditBoxStrc* pEditBox = (D2WinEditBoxStrc*)pMsg->hWindow;

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	if (pEditBox->bMouseSelecting)
	{
		pEditBox->bMouseSelecting = 0;
		return 1;
	}

	return 0;
}

//D2Win.0x6F8A9410
int32_t __fastcall sub_6F8A9410(SMSGHANDLER_PARAMS* pMsg, int32_t nX, int32_t nY)
{
	D2WinEditBoxStrc* pEditBox = (D2WinEditBoxStrc*)pMsg->hWindow;

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	if (!(pEditBox->controlHeader.dwFlags & gdwBitMasks[2]) || !(pEditBox->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 0;
	}

	D2Win_10012(pEditBox);

	if (pEditBox->bMouseSelecting)
	{
		nX = D2Clamp(nX, pEditBox->nTextOffsetX, pEditBox->controlHeader.nWidth - pEditBox->nTextOffsetX - 1);
		nY = D2Clamp(nY, pEditBox->nTextOffsetY, pEditBox->controlHeader.nHeight - pEditBox->nTextOffsetY - 1);
	}

	if (nX >= -pEditBox->nTextOffsetX && nX < pEditBox->controlHeader.nWidth - pEditBox->nTextOffsetX && nY >= -pEditBox->nTextOffsetY && nY < pEditBox->controlHeader.nHeight - pEditBox->nTextOffsetY)
	{
		D2Win_10127_SetFont(pEditBox->eFont);

		Unicode wszCursor[2] = {};
		Unicode::win2Unicode(wszCursor, "_", 2);

		const int32_t nCursorWidth = D2Win_10121_GetTextWidth(wszCursor);

		char szText[256] = {};
		Unicode::unicode2Win(szText, pEditBox->wszText, ARRAY_SIZE(szText));
		const char* pLineStart = szText;
		const char* pCurrent = szText;
		int32_t nLineY = 0;
		const int32_t nLineHeight = D2Win_10125();
		BOOL bFound = FALSE;
		int32_t nPreviousCursorPosition = -1;

		while (*pCurrent)
		{
			char szLine[256] = {};
			Unicode wszLine[256] = {};

			BOOL bWrapped = FALSE;
			int32_t nLength = pCurrent - pLineStart;
			while (*pCurrent && *pCurrent != '\r' && *pCurrent != '\n')
			{
				szLine[nLength] = *pCurrent;
				Unicode::win2Unicode(wszLine, szLine, 256);
				if (nCursorWidth + D2Win_10122(wszLine, nLength) > pEditBox->controlHeader.nWidth - 2 * pEditBox->nTextOffsetX)
				{
					bWrapped = TRUE;
					break;
				}
				++pCurrent;
				++nLength;
			}

			if (nY >= nLineY && nY < nLineHeight + nLineY)
			{
				int32_t nCounter = 1;
				Unicode::win2Unicode(wszLine, szLine, 256);
				while (nX > D2Win_10122(wszLine, nCounter))
				{
					if (nCounter > nLength)
					{
						break;
					}
					++nCounter;
				}

				nPreviousCursorPosition = pEditBox->nCursorPosition;
				bFound = TRUE;
				pEditBox->nCursorPosition = (pLineStart - szText) + nCounter - 1;
			}

			if (!bWrapped)
			{
				if (*pCurrent == '\r')
				{
					if (pCurrent[1] == '\n')
					{
						pCurrent += 2;
					}
					else
					{
						++pCurrent;
					}
					nLineY += nLineHeight;
				}
			}
			else
			{
				nLineY += nLineHeight;
			}

			pLineStart = pCurrent;
		}

		if (!bFound)
		{
			nPreviousCursorPosition = pEditBox->nCursorPosition;
			pEditBox->nCursorPosition = Unicode::strlen(pEditBox->wszText);
		}

		if (((GetKeyState(VK_SHIFT) & 0x8000) || pEditBox->bMouseSelecting) && nPreviousCursorPosition != -1)
		{
			if (pEditBox->nSelectionStart == -1)
			{
				pEditBox->nSelectionStart = nPreviousCursorPosition;
			}
			pEditBox->nSelectionEnd = pEditBox->nCursorPosition;
		}
		else
		{
			D2Win_10083(pEditBox);
		}
	}

	if (pMsg->nMessage == WM_LBUTTONDOWN)
	{
		pEditBox->bMouseSelecting = 1;
	}

	if (pEditBox->controlHeader.field_34)
	{
		return pEditBox->controlHeader.field_34(pMsg);
	}

	return 0;
}

//D2Win.0x6F8A97D0
int32_t __stdcall sub_6F8A97D0(SMSGHANDLER_PARAMS* pMsg)
{
	D2WinEditBoxStrc* pEditBox = (D2WinEditBoxStrc*)pMsg->hWindow;

	D2_ASSERT(pEditBox);
	D2_ASSERT(pEditBox->controlHeader.nType == D2WIN_EDITBOX);

	return sub_6F8A9410(pMsg, gMousePosition_6F8FE234.x - pEditBox->nTextOffsetX - pEditBox->controlHeader.nImageX, gMousePosition_6F8FE234.y + pEditBox->controlHeader.nHeight - pEditBox->nTextOffsetY - pEditBox->controlHeader.nImageY);
}

//D2Win.0x6F8A9850 (#10078)
BOOL __stdcall D2Win_10078_IsNumber(D2WinEditBoxStrc* pEditBox, int32_t nPosition, char* szChar)
{
	return *szChar >= '0' && *szChar <= '9';
}

//D2Win.0x6F8A9870 (#10079)
BOOL __stdcall D2Win_10079_IsLetter(D2WinEditBoxStrc* pEditBox, int32_t nPosition, char* szChar)
{
	return (*szChar >= 'a' && *szChar <= 'z') || (*szChar >= 'A' && *szChar <= 'Z');
}

//D2Win.0x6F8A98A0
void __fastcall sub_6F8A98A0(D2WinEditBoxStrc* pEditBox)
{
	D2Win_10127_SetFont(pEditBox->eFont);

	const int32_t nAvailableWidth = pEditBox->controlHeader.nWidth - 2 * pEditBox->nTextOffsetX;
	const int32_t nTextLength = Unicode::strlen(pEditBox->wszText);

	Unicode wszText[300];
	if (pEditBox->dwEditBoxFlags & EDITBOX_PASSWORD)
	{
		EDITBOX_FillWithPasswordChars(wszText, nTextLength);
	}
	else
	{
		Unicode::strcpy(wszText, pEditBox->wszText);
	}

	int32_t nTextWidth = D2Win_10121_GetTextWidth(wszText);

	Unicode wszCursor[2];
	Unicode::win2Unicode(wszCursor, "_", 2);

	const int32_t nCursorWidth = D2Win_10121_GetTextWidth(wszCursor);
	if (pEditBox->nCursorPosition == nTextLength)
	{
		nTextWidth += nCursorWidth;
	}

	if (nTextWidth <= nAvailableWidth)
	{
		pEditBox->nFirstVisibleChar = 0;
		pEditBox->nLastVisibleChar = nTextLength - 1;
		return;
	}

	int32_t nMaxWidth = nAvailableWidth;
	if (pEditBox->nCursorPosition == nTextLength)
	{
		nMaxWidth -= nCursorWidth;
	}

	if (pEditBox->nCursorPosition > pEditBox->nLastVisibleChar)
	{
		pEditBox->nLastVisibleChar = pEditBox->nCursorPosition;
		pEditBox->nFirstVisibleChar = pEditBox->nCursorPosition - 1;
		while (pEditBox->nFirstVisibleChar)
		{
			if (D2Win_10122(&wszText[pEditBox->nFirstVisibleChar], pEditBox->nLastVisibleChar - pEditBox->nFirstVisibleChar + 1) >= nMaxWidth)
			{
				break;
			}

			--pEditBox->nFirstVisibleChar;
		}

		++pEditBox->nFirstVisibleChar;
	}
	else if (pEditBox->nCursorPosition > pEditBox->nFirstVisibleChar + 1)
	{
		if (D2Win_10121_GetTextWidth(&wszText[pEditBox->nFirstVisibleChar]) >= nMaxWidth)
		{
			pEditBox->nLastVisibleChar = pEditBox->nFirstVisibleChar + 1;
			while (pEditBox->nLastVisibleChar < nTextLength)
			{
				if (D2Win_10122(&wszText[pEditBox->nFirstVisibleChar], pEditBox->nLastVisibleChar - pEditBox->nFirstVisibleChar + 1) >= nMaxWidth)
				{
					break;
				}

				++pEditBox->nLastVisibleChar;
			}

			--pEditBox->nLastVisibleChar;
		}
		else
		{
			pEditBox->nLastVisibleChar = nTextLength - 1;
			pEditBox->nFirstVisibleChar = nTextLength - 2;
			while (pEditBox->nFirstVisibleChar)
			{
				if (D2Win_10121_GetTextWidth(&wszText[pEditBox->nFirstVisibleChar]) >= nMaxWidth)
				{
					break;
				}

				--pEditBox->nFirstVisibleChar;
			}

			++pEditBox->nFirstVisibleChar;
		}
	}
	else
	{
		pEditBox->nFirstVisibleChar = std::max(pEditBox->nCursorPosition - 1, 0);
		pEditBox->nLastVisibleChar = pEditBox->nFirstVisibleChar + 1;
		while (pEditBox->nLastVisibleChar < nTextLength)
		{
			if (D2Win_10122(&wszText[pEditBox->nFirstVisibleChar], pEditBox->nLastVisibleChar - pEditBox->nFirstVisibleChar + 1) >= nMaxWidth)
			{
				break;
			}

			++pEditBox->nLastVisibleChar;
		}

		--pEditBox->nLastVisibleChar;
	}
}
