#include "D2WinFont.h"

#include <algorithm>

#include <D2Math.h>

#include <D2CMP.h>
#include <Archive.h>
#include <D2Lang.h>
#include <D2Unicode.h>
#include <D2StrTable.h>
#include <Fog.h>

#include <DisplayType.h>
#include <D2Gfx.h>
#include <Texture.h>
#include <Window.h>

#include "D2WinArchive.h"
#include "D2WinPalette.h"


#pragma warning (disable : 28159)


constexpr const char* gszFontNames_6F8BA534[NUM_FONTS] =
{
	"Font8",
	"Font16",
	"Font30",
	"Font42",
	"FontFormal10",
	"FontFormal12",
	"Font6",
	"Font24",
	"FontFormal11",
	"FontExocet10",
	"FontRidiculous",
	"FontExocet8",
	"ReallyTheLastSucker",
	"FontInGameChat"
};

D2FontCacheStrc stru_6F8FD8C0[14];
char byte_6F8FD9D8[20];
D2CellFileStrc* ghCellfileFontMonsterIndicators_6F8FD9EC;
Unicode gszFramedText_Buffer_6F8FD9F0[1024];
Font gnFontSize_6F8BDB24;
int dword_6F8BDB28;
int dword_6F8BDB2C;
int dword_6F8BDB30;
int gnFramedText_X_6F8FE1F0;
int gnFramedText_Y_6F8FE1F4;
int gnFramedText_TextColor_6F8FE1F8;
int gnFramedText_Align_6F8FE1FC;
int gnFramedText_RectangleColor_6F8FE200;
Unicode gMonsterIndicatorCodeUnicodeChar_6F8FE204[2]; // Contains L"m"
Unicode gColorCodeUnicodeChar_6F8FE208[2]; // Contains L"c"
D2CharStrc* (__fastcall* dword_6F8FE20C)(Unicode);
D2FontCacheStrc* gpFontCache;
DWORD gdwLastShiftedTickCount_6F8FE214;
BYTE byte_6F8FE218;
bool byte_6F8FE21A;


//D2Win.0x6F8A9B00
void __stdcall FONT_ClearFramedText()
{
	memset(gszFramedText_Buffer_6F8FD9F0, 0, sizeof(gszFramedText_Buffer_6F8FD9F0));
}

//D2Win.0x6F8A9B20
void __stdcall FONT_ClearColorCodeChar()
{
	memset(gColorCodeUnicodeChar_6F8FE208, 0, sizeof(gColorCodeUnicodeChar_6F8FE208));
}

//D2Win.0x6F8A9B40
void __stdcall FONT_ClearMonsterIndicatorChar()
{
	memset(gMonsterIndicatorCodeUnicodeChar_6F8FE204, 0, sizeof(gMonsterIndicatorCodeUnicodeChar_6F8FE204));
}

//D2Win.0x6F8A9B60 (#10115)
void __fastcall D2Win_10115_FONT()
{
	byte_6F8FE21A = 0;
	dword_6F8BDB28 = 16;
	dword_6F8BDB2C = 17;
	dword_6F8BDB30 = 3;

	switch (STRTABLE_GetLanguage())
	{
	case LANGUAGE_ENGLISH:
	case LANGUAGE_SPANISH:
	case LANGUAGE_GERMAN:
	case LANGUAGE_FRENCH:
	case LANGUAGE_PORTUGUESE:
	case LANGUAGE_ITALIAN:
		strcpy_s(byte_6F8FD9D8, "Latin\\");
		dword_6F8BDB2C = 16;
		dword_6F8FE20C = FONT_GetCharInfoDirect;
		break;

	case LANGUAGE_JAPANESE:
		dword_6F8BDB28 = 14;
		dword_6F8BDB2C = 15;
		dword_6F8BDB30 = 5;
		strcpy_s(byte_6F8FD9D8, "JPN\\");
		dword_6F8FE20C = FONT_GetCharInfoSearch;
		break;

	case LANGUAGE_KOREAN:
		dword_6F8BDB30 = 5;
		strcpy_s(byte_6F8FD9D8, "KOR\\");
		dword_6F8FE20C = FONT_GetCharInfoSearch;
		break;

	case LANGUAGE_CHINESESIN:
	case LANGUAGE_CHINESETWN:
		dword_6F8BDB30 = 2;
		dword_6F8BDB28 = 14;
		dword_6F8BDB2C = 14;
		strcpy_s(byte_6F8FD9D8, "CHI\\");
		dword_6F8FE20C = FONT_GetCharInfoSearch;
		break;

	case LANGUAGE_POLISH:
		dword_6F8BDB28 = 13;
		dword_6F8BDB2C = 13;
		strcpy_s(byte_6F8FD9D8, "LATIN2\\");
		dword_6F8FE20C = FONT_GetCharInfoSearch;
		break;

	case LANGUAGE_RUSSIAN:
		strcpy_s(byte_6F8FD9D8, "CYR\\");
		dword_6F8FE20C = FONT_GetCharInfoSearch;
		break;

	case LANGUAGE_ENGLISHKOR:
		byte_6F8FE21A = 1;
		strcpy_s(byte_6F8FD9D8, "LATIN\\");
		dword_6F8FE20C = FONT_GetCharInfoDirect;
		break;

	default:
		strcpy_s(byte_6F8FD9D8, "Latin\\");
		dword_6F8FE20C = FONT_GetCharInfoSearch;
		break;
	}

	if (!stru_6F8FD8C0[1].pCellFile)
	{
		char szFile[80] = {};

		FONT_GetCellFilePath(1, szFile, 79);
		stru_6F8FD8C0[1].pCellFile = ARCHIVE_LoadCellFile(szFile, 0);
		FONT_LoadFontTable(1);
	}

	if (!ghCellfileFontMonsterIndicators_6F8FD9EC)
	{
		char szPath[260] = {};

		wsprintfA(szPath, "%s\\UI\\Font\\MonsterIndicators", "DATA\\GLOBAL");
		ghCellfileFontMonsterIndicators_6F8FD9EC = ARCHIVE_LoadCellFile(szPath, 0);
	}

	memset(gszFramedText_Buffer_6F8FD9F0, 0, sizeof(gszFramedText_Buffer_6F8FD9F0));

	gpFontCache = &stru_6F8FD8C0[1];

	Unicode::toUnicode(gColorCodeUnicodeChar_6F8FE208, "c", 2);
	Unicode::toUnicode(gMonsterIndicatorCodeUnicodeChar_6F8FE204, "m", 2);
}

//D2Win.0x6F8A9DC0
void __fastcall FONT_GetCellFilePath(int nFont, char* pBuffer, int nLength)
{
	char szFileName[260] = {};

	wsprintfA(szFileName, "%s\\%s\\", "DATA\\LOCAL", "Font");

	D2_ASSERT(nLength > (int)strlen(szFileName) + 20);

	if (byte_6F8FE21A)
	{
		if (nFont == D2FONT_FONTINGAMECHAT)
		{
			wsprintfA(pBuffer, "%s%s%s", szFileName, "KOR\\", gszFontNames_6F8BA534[D2FONT_FONTINGAMECHAT]);
		}
		else
		{
			wsprintfA(pBuffer, "%s%s%s", szFileName, byte_6F8FD9D8, gszFontNames_6F8BA534[nFont]);
		}
	}
	else
	{
		wsprintfA(pBuffer, "%s%s%s", szFileName, byte_6F8FD9D8, gszFontNames_6F8BA534[nFont]);
	}
}

//D2Win.0x6F8A9E90
void __fastcall FONT_LoadFontTable(int nFont)
{
	char szFilename[80] = {};
	char szPath[260] = {};

	wsprintfA(szPath, "%s\\%s\\", "DATA\\LOCAL", "Font");

	D2_ASSERT((int)strlen(szPath) + 20 < 79);

	if (byte_6F8FE21A && nFont == 13)
	{
		wsprintfA(szFilename, "%s%s%s.tbl", szPath, "KOR\\", "FontInGameChat");
	}
	else
	{
		wsprintfA(szFilename, "%s%s%s.tbl", szPath, byte_6F8FD9D8, gszFontNames_6F8BA534[nFont]);
	}

	if (stru_6F8FD8C0[nFont].pFontInfo[0])
	{
		D2_FREE(stru_6F8FD8C0[nFont].pFontInfo[0]);
	}

	D2FontStrc* pFont = (D2FontStrc*)ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(D2Win_GetArchive(), szFilename, nullptr);	stru_6F8FD8C0[nFont].pFontInfo[0] = pFont;
	stru_6F8FD8C0[nFont].pFontInfo[1] = pFont;
	stru_6F8FD8C0[nFont].pCharInfo = pFont->pChars;
}

//D2Win.0x6F8A9F90 (#10116)
void __stdcall D2Win_10116()
{
	for (int i = 0; i < NUM_FONTS; ++i)
	{
		D2FontCacheStrc* pFont = &stru_6F8FD8C0[i];

		if (pFont->pCellFile)
		{
			ARCHIVE_FreeCellFile(pFont->pCellFile);
			pFont->pCellFile = nullptr;
		}

		if (pFont->pFontInfo[0])
		{
			D2_FREE(pFont->pFontInfo[0]);
			pFont->pFontInfo[0] = nullptr;
		}
	}

	ARCHIVE_FreeCellFile(ghCellfileFontMonsterIndicators_6F8FD9EC);
	ghCellfileFontMonsterIndicators_6F8FD9EC = nullptr;
}

//D2Win.0x6F8A9FF0 (#10127)
Font __fastcall D2Win_10127_SetFont(Font nFontSize)
{
	const Font nOldFont = gnFontSize_6F8BDB24;

	const DWORD dwShiftedTickCount = GetTickCount() >> 10;

	if (gnFontSize_6F8BDB24 == nFontSize)
	{
		stru_6F8FD8C0[nFontSize].dwShiftedTickCount = dwShiftedTickCount;
	}
	else
	{
		gnFontSize_6F8BDB24 = nFontSize;

		if (!stru_6F8FD8C0[nFontSize].pCellFile)
		{
			char szFile[80] = {};

			FONT_GetCellFilePath(nFontSize, szFile, 79);
			stru_6F8FD8C0[nFontSize].pCellFile = ARCHIVE_LoadCellFile(szFile, 0);
			FONT_LoadFontTable(nFontSize);
			stru_6F8FD8C0[nFontSize].dwShiftedTickCount = dwShiftedTickCount;
		}

		if (dwShiftedTickCount - gdwLastShiftedTickCount_6F8FE214 > 600)
		{
			gdwLastShiftedTickCount_6F8FE214 = dwShiftedTickCount;

			for (int i = 0; i < NUM_FONTS; ++i)
			{
				D2FontCacheStrc* pFont = &stru_6F8FD8C0[i];
				if (i != nFontSize && dwShiftedTickCount - pFont->dwShiftedTickCount > 240 && pFont->pCellFile)
				{
					ARCHIVE_FreeCellFile(pFont->pCellFile);
					pFont->pCellFile = nullptr;
				}
			}
		}

		gpFontCache = &stru_6F8FD8C0[nFontSize];

		if (byte_6F8FE21A)
		{
			if (nFontSize != D2FONT_FONTINGAMECHAT)
			{
				dword_6F8FE20C = FONT_GetCharInfoDirect;
			}
			else
			{
				dword_6F8FE20C = FONT_GetCharInfoSearch;
			}
		}
	}

	return nOldFont;
}

//D2Win.0x6F8AA100
D2CharStrc* __fastcall FONT_GetCharInfoDirect(Unicode wChar)
{
	if (wChar <= 0xFF)
	{
		return &stru_6F8FD8C0[gnFontSize_6F8BDB24].pCharInfo[wChar];
	}
	else
	{
		return stru_6F8FD8C0[gnFontSize_6F8BDB24].pCharInfo;
	}
}

//D2Win.0x6F8AA140
D2CharStrc* __fastcall FONT_GetCharInfoSearch(Unicode wChar)
{
	D2FontCacheStrc* pFontCache = &stru_6F8FD8C0[gnFontSize_6F8BDB24];

	int nMin = 0;
	int nMax = pFontCache->pFontInfo[1]->wNumChars - 1;

	for (int i = 0; i <= 1000 && nMin <= nMax; ++i)
	{
		int nMidpoint = (nMax + nMin) / 2;
		if (wChar == pFontCache->pCharInfo[nMidpoint].wChar)
		{
			return &pFontCache->pCharInfo[nMidpoint];
		}

		if (wChar >= pFontCache->pCharInfo[nMidpoint].wChar)
		{
			nMin = nMidpoint + 1;
		}
		else
		{
			nMax = nMidpoint - 1;
		}
	}

	return pFontCache->pCharInfo + 31;
}

//D2Win.0x6F8AA1D0 (#10123)
int __fastcall D2Win_10123(const Unicode* wszText, int nTextLength)
{
	const Unicode* pCurrent = wszText;
	int nIndex = 0;
	int nWidth = 0;
	int nColorCodeEnd = 3;
	while (*pCurrent)
	{
		if (nIndex >= nTextLength)
		{
			return nWidth;
		}

		if (*pCurrent != '\n')
		{
			if (nColorCodeEnd < nTextLength && *pCurrent < 0x100u && *pCurrent == 0xFF && pCurrent[1] == 'c' && pCurrent[2] >= '0' && pCurrent[2] < '7')
			{
				// Skip color codes
				pCurrent += 3;
				nIndex += 3;
				nColorCodeEnd += 3;
				continue;
			}

			nWidth += dword_6F8FE20C(*pCurrent)->nWidth;
		}

		++pCurrent;
		++nIndex;
		++nColorCodeEnd;
	}

	return nWidth;
}

//D2Win.0x6F8AA260 (#10122)
int __fastcall D2Win_10122(const Unicode* wszText, int nTextLength)
{
	int nIndex = 0;
	int nWidth = 0;
	for (const Unicode* i = wszText; *i; ++i)
	{
		if (nIndex >= nTextLength)
		{
			break;
		}

		if (*i != '\n')
		{
			nWidth += dword_6F8FE20C(*i)->nWidth;
		}

		++nIndex;
	}

	return nWidth;
}

//D2Win.0x6F8AA2A0 (#10121)
int __fastcall D2Win_10121_GetTextWidth(const Unicode* wszText)
{
	return D2Win_10122(wszText, Unicode::strlen(wszText));
}

//D2Win.0x6F8AA2F0 (#10125)
int __stdcall D2Win_10125()
{
	return stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight;
}

//D2Win.0x6F8AA310 (#10119)
void __fastcall D2Win_10119_DrawCroppedText(const Unicode* wszText, int32_t nX, int32_t nY, int32_t nUnused, int32_t nCropOffset, int32_t nCropHeight, int32_t nUnused2)
{
	if (nCropOffset < 0)
	{
		return;
	}

	const int32_t nDisplayType = D2GFX_GetDisplayType();

	D2GfxDataStrc gfxData = {};
	gfxData.nDirection = 0;
		
	const int32_t nLineStartX = nX;
	const int32_t nTextLength = Unicode::strlen(wszText);

	int32_t nCharIdx = 0;
	while(nCharIdx < nTextLength)
	{
		const Unicode currentChar = wszText[nCharIdx];
		++nCharIdx;

		if (/*currentChar < 256 && */ currentChar == 0xFF) // currentChar is ASCII and equal ÿ
		{
			const Unicode wCode = wszText[nCharIdx];
			++nCharIdx;

			if (0 == Unicode::strncmp(&wCode, gColorCodeUnicodeChar_6F8FE208, 1)) // If equal L"c" it is color code, skip
			{
				++nCharIdx;
			}
			else if (0 == Unicode::strncmp(&wCode, gMonsterIndicatorCodeUnicodeChar_6F8FE204, 1)) // If equal L"m" draw monster indicator
			{
				const Unicode wIndicatorChar = wszText[nCharIdx];
				++nCharIdx;

				D2CharStrc* pIndicatorCharInfo = dword_6F8FE20C(wIndicatorChar);
				gfxData.pCellFile = ghCellfileFontMonsterIndicators_6F8FD9EC;
				gfxData.nFrame = pIndicatorCharInfo->nImageIndex;
				TEXTURE_CelDraw(&gfxData, nX, nY, -1u, DRAWMODE_NORMAL, 0);

				nY += 16 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;
			}
		}
		else
		{
			if (currentChar == '\n') // newline
			{
				nX = nLineStartX;
				nY -= 16 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;
			}
			else
			{
				D2CharStrc* pCharInfo = dword_6F8FE20C(currentChar);
				if (nDisplayType != DISPLAYTYPE_DIRECT3D)
				{
					gfxData.pCellFile = gpFontCache->pCellFile;
					gfxData.nFrame = pCharInfo->nImageIndex;

					const int32_t nCelHeight = D2CMP_CelGetHeight(D2CMP_CelGetHandle(&gfxData));
					if (nCropHeight + nCropOffset > nCelHeight)
					{
						TEXTURE_CelDrawEx(&gfxData, nX, nY, 0, nCelHeight, DRAWMODE_NORMAL);
					}
					else
					{
						TEXTURE_CelDrawEx(&gfxData, nX, nY, nCropOffset, nCropHeight, DRAWMODE_NORMAL);
					}
				}

				nX += pCharInfo->nWidth;
			}
		}
	}
}

//D2Win.0x6F8AA510
void __fastcall FONT_DrawScrollingText(const Unicode* wszText, int32_t nX, int32_t nY, int32_t nColor, int32_t nScrollOffset, int32_t nMaxWidth)
{
	D2GfxDataStrc gfxData = {};
	gfxData.pCellFile = gpFontCache->pCellFile;
	gfxData.nDirection = 0;

	const Unicode* pCurrent = wszText;
	
	int32_t nCurrentX = nX + nScrollOffset;
	int32_t nCurrentColor = nColor;

	const int32_t nMaxX = nMaxWidth + nX;
	const int32_t nTextLength = Unicode::strlen(wszText);
	int32_t nIndex = 0;
	while (nIndex < nTextLength)
	{
		if (nCurrentX > nMaxX)
		{
			break;
		}

		const Unicode wChar = *pCurrent;
		++pCurrent;
		++nIndex;

		if (wChar >= 0x100u || wChar != 0xFF)
		{
			if (wChar == '\n')
			{
				nCurrentX = nX;
				nY += -16 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;
			}
			else
			{
				D2CharStrc* pCharInfo = dword_6F8FE20C(wChar);
				gfxData.nFrame = pCharInfo->nImageIndex;
				if (nCurrentX > nX)
				{
					TEXTURE_CelDrawColor(&gfxData, nCurrentX, nY, -1u, DRAWMODE_NORMAL, nCurrentColor);
				}

				nCurrentX += pCharInfo->nWidth;
			}
		}
		else
		{
			const Unicode wCode = *pCurrent;
			++nIndex;
			++pCurrent;

			if (Unicode::strncmp(&wCode, gColorCodeUnicodeChar_6F8FE208, 1) != 0)
			{
				--nIndex;
				--pCurrent;

				D2CharStrc* pCharInfo = dword_6F8FE20C(wChar);
				gfxData.nFrame = pCharInfo->nImageIndex;
				if (nCurrentX > nX)
				{
					TEXTURE_CelDrawColor(&gfxData, nCurrentX, nY, -1u, DRAWMODE_NORMAL, nCurrentColor);
				}

				nCurrentX += pCharInfo->nWidth;
			}
			else
			{
				nCurrentColor = 0;
				if (nIndex < nTextLength)
				{
					const Unicode wColorDigit = *pCurrent;
					++nIndex;
					++pCurrent;
					
					nCurrentColor = wColorDigit - '0';
					if (nCurrentColor >= '\r')
					{
						nCurrentColor = 0;
					}
				}
			}
		}
	}
}

//D2Win.0x6F8AA6E0 (#10124)
void __stdcall D2Win_10124()
{
	Font nOriginalFont = gnFontSize_6F8BDB24;
	Font nCurrentFont = gnFontSize_6F8BDB24;

	if (!Unicode::strlen(gszFramedText_Buffer_6F8FD9F0))
	{
		return;
	}

	int32_t nBoxWidth = FONT_GetMaxLineWidth(gszFramedText_Buffer_6F8FD9F0) + 8;

	int32_t nScreenWidth = 0;
	int32_t nScreenHeight = 0;

	int32_t nBoxHeight = 0;
	int32_t nBoxX = 0;
	int32_t nBoxY = 0;
	while (1)
	{
		int32_t nLines = 1;
		int32_t nRemaining = Unicode::strlen(gszFramedText_Buffer_6F8FD9F0);
		const Unicode* pCurrent = gszFramedText_Buffer_6F8FD9F0;
		if (nRemaining > 0)
		{
			do
			{
				if (*pCurrent == '\n')
				{
					++nLines;
				}
				++pCurrent;
				--nRemaining;
			}
			while (nRemaining);
		}

		nBoxHeight = nLines * dword_6F8BDB2C * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;

		nBoxX = gnFramedText_X_6F8FE1F0;
		if (gnFramedText_Align_6F8FE1FC == 1)
		{
			nBoxX = gnFramedText_X_6F8FE1F0 - (nBoxWidth >> 1);
		}

		nBoxY = gnFramedText_Y_6F8FE1F4 + 2;
		WINDOW_GetDimensions(&nScreenWidth, &nScreenHeight);

		if (nBoxHeight <= nScreenHeight - 10)
		{
			break;
		}

		if (nCurrentFont == D2FONT_FONT16)
		{
			D2Win_10127_SetFont(D2FONT_FONT8);
			nCurrentFont = D2FONT_FONT8;
		}
		else
		{
			if (gnFontSize_6F8BDB24)
			{
				break;
			}

			D2Win_10127_SetFont(D2FONT_FONT6);
			nCurrentFont = D2FONT_FONT6;
		}

		nBoxWidth = FONT_GetMaxLineWidth(gszFramedText_Buffer_6F8FD9F0) + 8;
	}

	const int32_t nClampedX = std::min(std::max(nBoxX, 0), nScreenWidth - nBoxWidth);
	const int32_t nClampedY = std::min(std::max(nBoxY, nBoxHeight - 5), nScreenHeight - 5);

	if (gnFramedText_RectangleColor_6F8FE200)
	{
		if (!byte_6F8FE218)
		{
			byte_6F8FE218 = D2Win_10034_MixRGB(0x50u, 0, 0);
		}

		const int32_t nProgressWidth = nBoxWidth * gnFramedText_RectangleColor_6F8FE200 >> 7;
		D2GFX_DrawBox(nClampedX, nClampedY - nBoxHeight, nProgressWidth + nClampedX, nClampedY, byte_6F8FE218, DRAWMODE_TRANS50);

		if (nBoxWidth != nProgressWidth)
		{
			D2GFX_DrawBox(nClampedX + nProgressWidth, nClampedY - nBoxHeight, nClampedX + nBoxWidth, nClampedY, 0, DRAWMODE_TRANS75);
		}
	}
	else
	{
		D2GFX_DrawBox(nClampedX, nClampedY - nBoxHeight, nClampedX + nBoxWidth, nClampedY, 0, DRAWMODE_TRANS75);
	}

	FONT_DrawTextEx(
		gszFramedText_Buffer_6F8FD9F0,
		nClampedX,
		nClampedY - dword_6F8BDB30 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10,
		nBoxWidth,
		gnFramedText_TextColor_6F8FE1F8,
		1);

	if (nCurrentFont != nOriginalFont)
	{
		D2Win_10127_SetFont(nOriginalFont);
	}
}

//D2Win.0x6F8AA910
int __fastcall FONT_GetMaxLineWidth(const Unicode* pStr)
{
	D2_ASSERT(pStr);

	const int nTextLength = Unicode::strlen(pStr);
	if (nTextLength <= 0)
	{
		return 0;
	}

	int nLineWidth = 0;
	int nMaxWidth = 0;
	int nIndex = 0;
	const Unicode* pCurrent = pStr;

	while (*pCurrent && nIndex < nTextLength)
	{
		if (*pCurrent == '\n')
		{
			if (nLineWidth > nMaxWidth)
			{
				nMaxWidth = nLineWidth;
			}

			nLineWidth = 0;
			++pCurrent;
		}
		else
		{
			if (*pCurrent < 0x100u && *pCurrent == 0xFF)
			{
				if (!Unicode::strnicmp(pCurrent + 1, gMonsterIndicatorCodeUnicodeChar_6F8FE204, 1))
				{
					nLineWidth += dword_6F8FE20C(gMonsterIndicatorCodeUnicodeChar_6F8FE204[0])->nWidth;
				}

				pCurrent += 3;
				nIndex += 2;
			}
			else
			{
				nLineWidth += dword_6F8FE20C(*pCurrent)->nWidth;
				++pCurrent;
			}
		}

		++nIndex;
	}

	if (nMaxWidth > nLineWidth)
	{
		nLineWidth = nMaxWidth;
	}

	return nLineWidth;
}

//D2Win.0x6F8AA9E0
void __fastcall FONT_DrawTextEx(const Unicode* wszText, int32_t nX, int32_t nY, int32_t nBoxWidth, int32_t nGlobalPaletteShift, int32_t bCentered)
{
	int32_t nCurrentX = nX;
	if (bCentered)
	{
		nCurrentX += (nBoxWidth - FONT_GetFirstLineWidth(wszText)) >> 1;
	}

	D2GfxDataStrc gfxData = {};
	gfxData.nDirection = 0;
	gfxData.pCellFile = gpFontCache->pCellFile;

	const Unicode* pCurrent = wszText;
	int32_t nCurrentColor = nGlobalPaletteShift;

	int32_t nIndex = 0;
	const int32_t nTextLength = Unicode::strlen(wszText);
	while (nIndex < nTextLength)
	{
		const Unicode wChar = *pCurrent;
		++pCurrent;
		++nIndex;

		if (wChar >= 0x100u || wChar != 0xFF)
		{
			if (wChar == '\n')
			{
				nCurrentX = nX;
				if (bCentered)
				{
					nCurrentX += ((nBoxWidth - FONT_GetFirstLineWidth(pCurrent)) >> 1);
				}

				nY += dword_6F8BDB28 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / -10;
			}
			else
			{
				D2CharStrc* pCharInfo = dword_6F8FE20C(wChar);
				gfxData.nFrame = pCharInfo->nImageIndex;
				TEXTURE_CelDrawColor(&gfxData, nCurrentX, nY, -1u, DRAWMODE_NORMAL, nCurrentColor);

				nCurrentX += pCharInfo->nWidth;
			}
		}
		else
		{
			const Unicode wCode = *pCurrent;

			++nIndex;
			++pCurrent;

			if (Unicode::strncmp(&wCode, gColorCodeUnicodeChar_6F8FE208, 1) != 0)
			{
				--nIndex;
				--pCurrent;
				
				D2CharStrc* pCharInfo = dword_6F8FE20C(wChar);
				gfxData.nFrame = pCharInfo->nImageIndex;
				TEXTURE_CelDrawColor(&gfxData, nCurrentX, nY, -1u, DRAWMODE_NORMAL, nCurrentColor);

				nCurrentX += pCharInfo->nWidth;
			}
			else
			{
				nCurrentColor = 0;
				if (nIndex < nTextLength)
				{
					const Unicode wColorDigit = *pCurrent;

					++nIndex;
					++pCurrent;

					nCurrentColor = wColorDigit - '0';
					if (nCurrentColor >= '\r')
					{
						nCurrentColor = 0;
					}
				}
			}
		}
	}
}

//D2Win.0x6F8AABB0
int __fastcall FONT_GetFirstLineWidth(const Unicode* pStr)
{
	D2_ASSERT(pStr);

	const int nTextLength = Unicode::strlen(pStr);
	int nWidth = 0;
	int nIndex = 0;
	const Unicode* pCurrent = pStr;
	while (nIndex < nTextLength)
	{
		if (*pCurrent == '\n')
		{
			break;
		}

		if (*pCurrent >= 0x100u || *pCurrent != 0xFF)
		{
			nWidth += dword_6F8FE20C(*pCurrent)->nWidth;
			++pCurrent;
		}
		else
		{
			if (!Unicode::strnicmp(pCurrent + 1, gMonsterIndicatorCodeUnicodeChar_6F8FE204, 1))
			{
				nWidth += dword_6F8FE20C(gMonsterIndicatorCodeUnicodeChar_6F8FE204[0])->nWidth;
			}

			nIndex += 2;
			pCurrent += 3;
		}

		++nIndex;
	}

	return nWidth;
}

//D2Win.0x6F8AAC60 (#10129)
void __fastcall D2Win_10129_DrawFramedText(const Unicode* wszText, int nX, int nY, int nTextColor, int nAlign)
{
	D2Win_10130_DrawFramedTextEx(wszText, nX, nY, nTextColor, nAlign, 0);
}

//D2Win.0x6F8AACD0 (#10130)
void __fastcall D2Win_10130_DrawFramedTextEx(const Unicode* wszText, int nX, int nY, int nTextColor, int nAlign, int nRectangleColor)
{
	if (wszText && Unicode::strlen(wszText) < 1024)
	{
		Unicode::strcpy(gszFramedText_Buffer_6F8FD9F0, wszText);
	}
	else
	{
		memset(gszFramedText_Buffer_6F8FD9F0, 0, sizeof(gszFramedText_Buffer_6F8FD9F0));
	}

	gnFramedText_X_6F8FE1F0 = nX;
	gnFramedText_Y_6F8FE1F4 = nY;
	gnFramedText_TextColor_6F8FE1F8 = nTextColor;
	gnFramedText_Align_6F8FE1FC = nAlign;
	gnFramedText_RectangleColor_6F8FE200 = nRectangleColor;
}

//D2Win.0x6F8AAD40 (#10117)
void __fastcall D2Win_10117_DrawText(const Unicode* wszText, int nX, int nY, int nColor, BOOL bCentered)
{
	if (bCentered)
	{
		FONT_DrawTextEx(wszText, nX, nY, FONT_GetMaxLineWidth(wszText) + 8, nColor, bCentered);
	}
	else
	{
		FONT_DrawTextEx(wszText, nX, nY, 0, nColor, bCentered);
	}
}

//D2Win.0x6F8AAD80
void __fastcall D2Win_10118_DrawBlendedText(const Unicode* wszText, int32_t nX, int32_t nY, int32_t nColor, int32_t bCentered, DrawMode eDrawMode)
{
	int32_t nBoxWidth = 0;
	if (bCentered)
	{
		nBoxWidth = FONT_GetMaxLineWidth(wszText) + 8;
	}

	int32_t nCurrentX = nX;
	if (bCentered)
	{
		nCurrentX += ((nBoxWidth - FONT_GetFirstLineWidth(wszText)) >> 1);
	}

	D2GfxDataStrc gfxData = {};
	gfxData.nDirection = 0;
	gfxData.pCellFile = gpFontCache->pCellFile;

	const Unicode* pCurrent = wszText;

	int32_t nCurrentColor = nColor;

	const int32_t nTextLength = Unicode::strlen(wszText);
	int32_t nIndex = 0;
	while (nIndex < nTextLength)
	{
		const Unicode wChar = *pCurrent;

		++pCurrent;
		++nIndex;

		if (wChar >= 0x100u || wChar != 0xFF)
		{
			if (wChar == '\n')
			{
				nCurrentX = nX;
				if (bCentered)
				{
					nCurrentX += ((nBoxWidth - FONT_GetFirstLineWidth(pCurrent)) >> 1);
				}

				nY += -16 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;
			}
			else
			{
				D2CharStrc* pCharInfo = dword_6F8FE20C(wChar);
				gfxData.nFrame = pCharInfo->nImageIndex;
				TEXTURE_CelDrawColor(&gfxData, nCurrentX, nY, -1u, eDrawMode, nCurrentColor);

				nCurrentX += pCharInfo->nWidth;
			}
		}
		else
		{
			const Unicode wCode = *pCurrent;

			++nIndex;
			++pCurrent;

			if (Unicode::strncmp(&wCode, gColorCodeUnicodeChar_6F8FE208, 1) != 0)
			{
				--nIndex;
				--pCurrent;

				D2CharStrc* pCharInfo = dword_6F8FE20C(wChar);
				gfxData.nFrame = pCharInfo->nImageIndex;
				TEXTURE_CelDrawColor(&gfxData, nCurrentX, nY, -1u, eDrawMode, nCurrentColor);

				nCurrentX += pCharInfo->nWidth;
			}
			else
			{
				nCurrentColor = 0;
				if (nIndex < nTextLength)
				{
					const Unicode wColorDigit = *pCurrent;

					++nIndex;
					++pCurrent;

					nCurrentColor = wColorDigit - '0';
					if (nCurrentColor >= '\r')
					{
						nCurrentColor = 0;
					}
				}
			}
		}
	}
}

//D2Win.0x6F8AAF80 (#10126)
void __fastcall D2Win_10126_DrawTextFromCache(const Unicode* pText, int nX, int nY)
{
	D2GfxDataStrc gfxData = {};
	gfxData.pCellFile = gpFontCache->pCellFile;
	gfxData.nDirection = 0;

	const Unicode* wszText = pText;
	int nImageX = nX;
	int nImageY = nY;

	if (Unicode::strlen(pText) <= 0)
	{
		return;
	}

	while (1)
	{
		if (*wszText < 0x100u && *wszText == 0xFF)
		{
			wszText += 3;
		}
		else
		{
			if (*wszText == '\n')
			{
				nImageX = nX;
				nImageY += -15 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;
			}
			else
			{
				D2CharStrc* pFont = dword_6F8FE20C(*wszText);

				gfxData.nFrame = pFont->nImageIndex;
				TEXTURE_CelDraw(&gfxData, nImageX, nImageY, -1, DRAWMODE_NORMAL, 0);

				nImageX += pFont->nWidth;
			}

			++wszText;
		}
	}
}

//D2Win.0x6F8AB080 (#10132)
void __fastcall D2Win_10132(const Unicode* wszText, int nX, int nY, DWORD dwColor, DrawMode eDrawMode, int nColor)
{
	int nTextWidth = 0;
	int nTextHeight = 0;
	D2Win_10131_GetTextDimensions(wszText, &nTextWidth, &nTextHeight);
	nTextWidth += 8;

	nY += 2;

	int nScreenWidth = 0;
	int nScreenHeight = 0;
	WINDOW_GetDimensions(&nScreenWidth, &nScreenHeight);

	if (nX < 0)
	{
		nX = 0;
	}

	if (nX >= nScreenWidth - nTextWidth)
	{
		nX = nScreenWidth - nTextWidth;
	}

	if (nY <= nTextHeight)
	{
		nY = nTextHeight;
	}

	if (nY >= nScreenHeight - 31)
	{
		nY = nScreenHeight - 31;
	}

	D2GFX_DrawBox(nX, nY - nTextHeight, nX + nTextWidth, nY, dwColor, eDrawMode);
	FONT_DrawTextEx(wszText, nX, nY - 3 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10, nTextWidth, nColor, 1);
}

//D2Win.0x6F8AB1B0 (#10133)
void __fastcall D2Win_10133(const Unicode* pText, int nX, int nY, DWORD dwColor, DrawMode eDrawMode, int nPaletteShift)
{
	nY += 2;

	int nRectWidth = FONT_GetMaxLineWidth(pText);
	int nRectHeight = stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight;

	int nScreenWidth = 0;
	int nScreenHeight = 0;
	WINDOW_GetDimensions(&nScreenWidth, &nScreenHeight);

	if (nX > nScreenWidth - nRectWidth)
	{
		nX = nScreenWidth - nRectWidth;
	}

	if (nY > nScreenHeight - 31)
	{
		nY = nScreenHeight - 31;
	}

	if (nY < nRectHeight)
	{
		nY *= 2;
	}

	D2GFX_DrawBox(nX, nY - nRectHeight, nX + nRectWidth, nY, dwColor, eDrawMode);
	FONT_DrawTextEx(pText, nX, nY - 2, nRectWidth, nPaletteShift, 1);
}

//D2Win.0x6F8AB260 (#1031)
void __fastcall D2Win_10131_GetTextDimensions(const Unicode* pText, int* pWidth, int* pHeight)
{
	*pWidth = FONT_GetMaxLineWidth(pText);

	D2_ASSERT(pText);

	int nLines = 1;
	const int nTextLength = Unicode::strlen(pText);
	for (int i = 0; i < nTextLength; ++i)
	{
		if (pText[i] == '\n')
		{
			++nLines;
		}
	}

	*pHeight = nLines * dword_6F8BDB2C * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;
}

//D2Win.0x6F8AB2F0 (#10128)
unsigned int __fastcall D2Win_10128(uint8_t nChar)
{
	unsigned int dwPrintableCharMask[] =
	{
		0, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF, 0x00060000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	if (nChar != 0xFF)
	{
		const uint32_t dwOffset = nChar >> 5;

		D2_ASSERT(dwOffset < 8);

		uint8_t nBit = nChar & 0x1F;
		if (nBit & 0x80)
		{
			nBit = ((nBit - 1) | 0xE0) + 1;
		}

		return (dwPrintableCharMask[dwOffset] >> nBit) & 1;
	}

	return 0;
}

//D2Win.0x6F8AB360
void __fastcall FONT_DrawTextWithBox(const Unicode* pStr, int nX, int nY, int nBoxWidth, DWORD dwColor, DrawMode eDrawMode, int nPaletteShift)
{
	D2_ASSERT(pStr);

	int nLines = 1;
	for (int i = 0; i < Unicode::strlen(pStr); ++i)
	{
		if (pStr[i] == '\n')
		{
			++nLines;
		}
	}

	const int nBoxHeight = nLines * dword_6F8BDB2C * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;
	int nBottomY = nY + 2;
	int nTopPadding = 4 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10;

	int nScreenWidth = 0;
	int nScreenHeight = 0;
	WINDOW_GetDimensions(&nScreenWidth, &nScreenHeight);

	if (nX > nScreenWidth - nBoxWidth)
	{
		nX = nScreenWidth - nBoxWidth;
	}

	if (nBottomY > nScreenHeight - 31)
	{
		nBottomY = nScreenHeight - 31;
	}

	if (nBottomY < nBoxHeight)
	{
		nBottomY *= 2;
	}

	D2GFX_DrawBox(nX - 4, nBottomY + nTopPadding - nBoxHeight, nX - 4 + nBoxWidth, nBottomY, dwColor, eDrawMode);
	FONT_DrawTextEx(pStr, nX, nBottomY - 2, 0, nPaletteShift, 0);
}

//D2Win.0x6F8AB480 (#10134)
void __fastcall D2Win_10134_DrawCellFile(D2CellFileStrc* pCellFile, int nX, int nY, int nDiv, DrawMode eDrawMode, int nColor)
{
	D2GfxDataStrc gfxData = {};

	gfxData.pCellFile = pCellFile;
	gfxData.nDirection = 0;

	const int nFramesPerDirection = D2CMP_CelFileGetCelsPerDirection(pCellFile);
	
	if (nDiv == 1 || nDiv == 2)
	{
		int nAccumulatedWidth = 0;
		for (int nFrame = 0; nFrame < nFramesPerDirection; ++nFrame)
		{
			gfxData.nFrame = nFrame;
			nAccumulatedWidth += D2CMP_CelGetWidth(D2CMP_CelGetHandle(&gfxData));
		}

		if (nDiv == 1)
		{
			nX += -1 - (nAccumulatedWidth >> 1);
		}
		else
		{
			nX -= nAccumulatedWidth;
		}
	}

	for (int nFrame = 0; nFrame < nFramesPerDirection; ++nFrame)
	{
		gfxData.nFrame = nFrame;
		if (nColor == -1)
		{
			TEXTURE_CelDraw(&gfxData, nX + 256 * nFrame, nY, -1, eDrawMode, 0);
		}
		else
		{
			TEXTURE_CelDrawColor(&gfxData, nX + 256 * nFrame, nY, -1, eDrawMode, nColor);
		}
	}
}

//D2Win.0x6F8AB560 (#10120)
void __fastcall D2Win_10120(const Unicode* wszText, int nX, int nY, int nColor, int nAlign, int nProgress)
{
	if (Unicode::strlen(wszText))
	{
		int nTextWidth = 0;
		int nTextHeight = 0;
		D2Win_10131_GetTextDimensions(wszText, &nTextWidth, &nTextHeight);

		const int nBoxWidth = nTextWidth + 8;

		int nBoxX = nX;
		if (nAlign == 1)
		{
			nBoxX = nX - (nBoxWidth >> 1);
		}

		int nBoxY = nY + 2;

		int nScreenWidth = 0;
		int nScreenHeight = 0;
		WINDOW_GetDimensions(&nScreenWidth, &nScreenHeight);

		if (nBoxX < 0)
		{
			nBoxX = 0;
		}

		if (nBoxX >= nScreenWidth - nBoxWidth)
		{
			nBoxX = nScreenWidth - nBoxWidth;
		}

		if (nBoxY <= nTextHeight)
		{
			nBoxY = nTextHeight;
		}

		if (nBoxY >= nScreenHeight - 31)
		{
			nBoxY = nScreenHeight - 31;
		}

		if (nProgress)
		{
			if (!byte_6F8FE218)
			{
				byte_6F8FE218 = D2Win_10034_MixRGB(0x50u, 0, 0);
			}

			const int nProgressWidth = nProgress * nBoxWidth >> 7;
			D2GFX_DrawBox(nBoxX, nBoxY - nTextHeight, nProgressWidth + nBoxX, nBoxY, byte_6F8FE218, DRAWMODE_TRANS50);

			if (nBoxWidth != nProgressWidth)
			{
				D2GFX_DrawBox(nProgressWidth + nBoxX, nBoxY - nTextHeight, nProgressWidth + nBoxX + nBoxWidth - nProgressWidth, nBoxY, 0, DRAWMODE_TRANS75);
			}
		}
		else
		{
			D2GFX_DrawBox(nBoxX, nBoxY - nTextHeight, nBoxWidth + nBoxX, nBoxY, 0, DRAWMODE_TRANS75);
		}

		FONT_DrawTextEx(wszText, nBoxX, nBoxY - 3 * stru_6F8FD8C0[gnFontSize_6F8BDB24].pFontInfo[1]->nHeight / 10, nBoxWidth, nColor, 1);
	}
}

//D2Win.0x6F8AB730 (#10200)
void __fastcall D2Win_10200(D2SplittedTextStrc* pSplitText)
{
	D2SplittedTextStrc* pNext = nullptr;
	for (D2SplittedTextStrc* i = pSplitText; i; i = pNext)
	{
		pNext = i->pNextLine;
		D2_FREE(i->wszLine);
		D2_FREE(i);
	}
}

// Helper function
D2SplittedTextStrc* __fastcall FONT_AllocateSplitLine(const Unicode* wszText, int nLength)
{
	D2SplittedTextStrc* pSplitText = (D2SplittedTextStrc*)FOG_Alloc(sizeof(D2SplittedTextStrc), __FILE__, __LINE__, 0);
	pSplitText->wszLine = (Unicode*)FOG_Alloc(sizeof(Unicode) * (nLength + 1), __FILE__, __LINE__, 0);
	pSplitText->pNextLine = nullptr;
	Unicode::strncpy(pSplitText->wszLine, wszText, nLength);
	pSplitText->wszLine[nLength] = L'\0';

	return pSplitText;
}

// Helper function
int __fastcall FONT_FindSplitPosition(const Unicode* wszText, int nTextLength, int nMaxLength, int nLineStart, int* pLineWidth)
{
	*pLineWidth = 0;

	int i = nTextLength;

	if (nTextLength > nLineStart)
	{
		while (i > nLineStart)
		{
			*pLineWidth = D2Win_10123(&wszText[nLineStart], 1 - nLineStart + i);
			if (*pLineWidth <= nMaxLength)
			{
				break;
			}

			--i;
		}

		while (i > nLineStart)
		{
			if (i == nTextLength || Unicode::isLineBreak(&wszText[nLineStart], i - nLineStart + 1))
			{
				break;
			}

			--i;
		}
	}

	return i;
}

// Helper function
int __fastcall FONT_AppendSplitLine(const Unicode* wszText, int* pLines, D2SplittedTextStrc** ppLastLine, D2SplittedTextStrc** ppFirstLine, int nLineEnd, int nLineStart)
{
	int nLength = nLineEnd - nLineStart + 1;
	const Unicode* pLineText = &wszText[nLineStart];
	if (*pLineText < 0x100u && isspace(*pLineText))
	{
		--nLength;
		++pLineText;
	}

	D2SplittedTextStrc* pLine = FONT_AllocateSplitLine(pLineText, nLength);
	++*pLines;

	if (*ppLastLine)
	{
		(*ppLastLine)->pNextLine = pLine;
	}

	*ppLastLine = pLine;
	if (!*ppFirstLine)
	{
		*ppFirstLine = pLine;
	}

	// Start of the next line
	return nLineEnd + 1;
}

//D2Win.0x6F8AB770 (#10199)
D2SplittedTextStrc* __fastcall D2Win_10199(const Unicode* wszText, int* pLines, int nMaxLength)
{
	const int nTextLength = Unicode::strlen(wszText);

	*pLines = 0;

	if (D2Win_10123(wszText, nTextLength) <= nMaxLength)
	{
		*pLines = 1;
		return FONT_AllocateSplitLine(wszText, nTextLength + 1);
	}

	D2SplittedTextStrc* pFirstLine = nullptr;
	D2SplittedTextStrc* pLastLine = nullptr;

	int nLineStart = 0;
	do
	{
		int nLineWidth = 0;
		int i = FONT_FindSplitPosition(wszText, nTextLength, nMaxLength, nLineStart, &nLineWidth);
		if (i == nLineStart)
		{
			for (i = nTextLength; i > nLineStart; --i)
			{
				if (D2Win_10123(&wszText[nLineStart], 1 - nLineStart + i) <= nMaxLength)
				{
					break;
				}
			}

			nLineStart = FONT_AppendSplitLine(wszText, pLines, &pLastLine, &pFirstLine, i, nLineStart);
		}
		else if (nLineWidth <= nMaxLength)
		{
			nLineStart = FONT_AppendSplitLine(wszText, pLines, &pLastLine, &pFirstLine, i, nLineStart);
		}
		else
		{
			int nTemp = 0;
			int j = FONT_FindSplitPosition(wszText, nTextLength, nMaxLength, nLineStart, &nTemp);
			if (j == nLineStart)
			{
				for (j = nTextLength; j > nLineStart; --j)
				{
					if (D2Win_10123(&wszText[nLineStart], j + 1 - nLineStart) <= nMaxLength)
					{
						break;
					}
				}
			}

			nLineStart = FONT_AppendSplitLine(wszText, pLines, &pLastLine, &pFirstLine, j, nLineStart);
		}
	}
	while (nLineStart <= nTextLength);

	return pFirstLine;
}

//D2Win.0x6F8ABA70 (#10206)
DrawFramedTextPtr __stdcall D2Win_10206()
{
	return D2Win_10129_DrawFramedText;
}

//D2Win.0x6F8ABA80 (#10207)
GetTextDimensionsPtr __stdcall D2Win_10207()
{
	return D2Win_10131_GetTextDimensions;
}
