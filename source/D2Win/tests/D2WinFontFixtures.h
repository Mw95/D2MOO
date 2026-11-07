#pragma once


#include <cstdint>
#include <string>
#include <vector>

#include <Windows.h>

#include <D2StrTable.h>
#include <D2Unicode.h>

#include <D2WinFont.h>

#include "D2WinTestFixtures.h"


extern D2FontCacheStrc stru_6F8FD8C0[14];
extern Font gnFontSize_6F8BDB24;
extern int dword_6F8BDB2C;
extern Unicode gMonsterIndicatorCodeUnicodeChar_6F8FE204[2];
extern Unicode gColorCodeUnicodeChar_6F8FE208[2];
extern D2CharStrc* (__fastcall* dword_6F8FE20C)(Unicode);
extern DWORD gdwLastShiftedTickCount_6F8FE214;
extern bool byte_6F8FE21A;


// The font globals of one implementation
struct FontGlobals
{
	D2FontCacheStrc* pFontCaches;							// 0x6F8FD8C0
	Font* pFont;											// 0x6F8BDB24
	int* pLineHeightPercent;								// 0x6F8BDB2C, the line height in tenths of the font height
	Unicode* wszMonsterIndicatorCode;						// 0x6F8FE204
	Unicode* wszColorCode;									// 0x6F8FE208
	D2CharStrc* (__fastcall** ppfGetCharInfo)(Unicode);		// 0x6F8FE20C
	DWORD* pLastShiftedTickCount;							// 0x6F8FE214
	uint8_t* pbSwitchCharInfoLookup;						// 0x6F8FE21A
	D2CharStrc* (__fastcall* pfGetCharInfoByIndex)(Unicode);
	D2CharStrc* (__fastcall* pfFindCharInfo)(Unicode);
};

inline const FontGlobals& font_globals(int nImplementation)
{
	static const FontGlobals moo = {
		stru_6F8FD8C0, &gnFontSize_6F8BDB24, &dword_6F8BDB2C, gMonsterIndicatorCodeUnicodeChar_6F8FE204, gColorCodeUnicodeChar_6F8FE208,
		&dword_6F8FE20C, &gdwLastShiftedTickCount_6F8FE214, reinterpret_cast<uint8_t*>(&byte_6F8FE21A), &FONT_GetCharInfoByIndex, &FONT_FindCharInfo,
	};
	static const FontGlobals original = {
		original_d2win_global<D2FontCacheStrc>(0x6F8FD8C0),
		original_d2win_global<Font>(0x6F8BDB24),
		original_d2win_global<int>(0x6F8BDB2C),
		original_d2win_global<Unicode>(0x6F8FE204),
		original_d2win_global<Unicode>(0x6F8FE208),
		original_d2win_global<D2CharStrc* (__fastcall*)(Unicode)>(0x6F8FE20C),
		original_d2win_global<DWORD>(0x6F8FE214),
		original_d2win_global<uint8_t>(0x6F8FE21A),
		reinterpret_cast<D2CharStrc* (__fastcall*)(Unicode)>(original_d2win_address(0x6F8AA100)),
		reinterpret_cast<D2CharStrc* (__fastcall*)(Unicode)>(original_d2win_address(0x6F8AA140)),
	};
	return nImplementation == 0 ? moo : original;
}

// A font whose glyph widths depend on the character, shared by both implementations
struct FakeFont
{
	D2FontStrc font = {};
	// Indexed by character for FONT_GetCharInfoByIndex, sorted by character for FONT_FindCharInfo
	D2CharStrc chars[256] = {};
	int32_t cellFile[4] = {};

	explicit FakeFont(uint8_t nHeight, bool bSparse)
	{
		font.dwHeader = 'Woo!';
		font.nHeight = nHeight;
		font.nWidth = 20;
		font.unk0x08 = 256;
		for (int i = 0; i < 256; ++i)
		{
			// Sparse fonts hold characters above 0xFF, as the Asian fonts do
			chars[i].wChar = (WORD)(bSparse ? i * 37 : i);
			chars[i].nWidth = (BYTE)(3 + (i * 7) % 11);
			chars[i].nHeight = nHeight;
			chars[i].nImageIndex = (WORD)i;
		}
	}
};

// Font functions of D2Lang
struct FontLanguageMock
{
	static inline D2C_Language nLanguage = LANGUAGE_ENGLISH;

	// D2Lang.#10007
	static D2C_Language GetLanguage()
	{
		return nLanguage;
	}
};

// Installs fake fonts in both implementations, restores the font globals at the end of the test
template<class Fixture>
struct D2WinFontFixture : D2WinFixture<Fixture>
{
	ImportTablePatch tickPatches;
	FakeFont fonts[2] = { FakeFont(12, false), FakeFont(15, true) };

	struct Saved
	{
		D2FontCacheStrc fontCaches[14];
		Font nFont;
		int nLineHeightPercent;
		Unicode wszMonsterIndicatorCode[2];
		Unicode wszColorCode[2];
		D2CharStrc* (__fastcall* pfGetCharInfo)(Unicode);
		DWORD dwLastShiftedTickCount;
		uint8_t bSwitchCharInfoLookup;
	};
	Saved saved[2];

	D2WinFontFixture()
	{
		this->hook("D2Lang.dll", 10007, &STRTABLE_GetLanguage, &FontLanguageMock::GetLanguage);
		FontLanguageMock::nLanguage = LANGUAGE_ENGLISH;
		tickPatches.patch_both(get_original_d2win(), "KERNEL32.dll", "GetTickCount", reinterpret_cast<const void*>(&TickCountMock::GetTickCount));
		TickCountMock::dwTickCount = 5000 << 10;

		for (int i = 0; i < 2; ++i)
		{
			const FontGlobals& globals = font_globals(i);
			Saved& save = saved[i];
			std::memcpy(save.fontCaches, globals.pFontCaches, sizeof(save.fontCaches));
			save.nFont = *globals.pFont;
			save.nLineHeightPercent = *globals.pLineHeightPercent;
			std::memcpy(save.wszMonsterIndicatorCode, globals.wszMonsterIndicatorCode, sizeof(save.wszMonsterIndicatorCode));
			std::memcpy(save.wszColorCode, globals.wszColorCode, sizeof(save.wszColorCode));
			save.pfGetCharInfo = *globals.ppfGetCharInfo;
			save.dwLastShiftedTickCount = *globals.pLastShiftedTickCount;
			save.bSwitchCharInfoLookup = *globals.pbSwitchCharInfoLookup;
		}

		install_fonts(false);
	}

	~D2WinFontFixture()
	{
		for (int i = 0; i < 2; ++i)
		{
			const FontGlobals& globals = font_globals(i);
			const Saved& save = saved[i];
			std::memcpy(globals.pFontCaches, save.fontCaches, sizeof(save.fontCaches));
			*globals.pFont = save.nFont;
			*globals.pLineHeightPercent = save.nLineHeightPercent;
			std::memcpy(globals.wszMonsterIndicatorCode, save.wszMonsterIndicatorCode, sizeof(save.wszMonsterIndicatorCode));
			std::memcpy(globals.wszColorCode, save.wszColorCode, sizeof(save.wszColorCode));
			*globals.ppfGetCharInfo = save.pfGetCharInfo;
			*globals.pLastShiftedTickCount = save.dwLastShiftedTickCount;
			*globals.pbSwitchCharInfoLookup = save.bSwitchCharInfoLookup;
		}
	}

	// All the fonts are loaded, even fonts use the first fake font and odd fonts the second one
	void install_fonts(bool bFindCharInfo, Font nFont = D2FONT_FONT16)
	{
		for (int i = 0; i < 2; ++i)
		{
			const FontGlobals& globals = font_globals(i);
			for (int nFontIndex = 0; nFontIndex < 14; ++nFontIndex)
			{
				FakeFont& font = fonts[nFontIndex & 1];
				D2FontCacheStrc& cache = globals.pFontCaches[nFontIndex];
				cache.pCellFile = reinterpret_cast<D2CellFileStrc*>(font.cellFile);
				cache.pFontInfo[0] = &font.font;
				cache.pFontInfo[1] = &font.font;
				cache.pCharInfo = font.chars;
				cache.dwShiftedTickCount = TickCountMock::dwTickCount >> 10;
			}
			*globals.pFont = nFont;
			*globals.pLineHeightPercent = 16;
			globals.wszMonsterIndicatorCode[0] = 'm';
			globals.wszMonsterIndicatorCode[1] = 0;
			globals.wszColorCode[0] = 'c';
			globals.wszColorCode[1] = 0;
			*globals.ppfGetCharInfo = bFindCharInfo ? globals.pfFindCharInfo : globals.pfGetCharInfoByIndex;
			*globals.pLastShiftedTickCount = TickCountMock::dwTickCount >> 10;
			*globals.pbSwitchCharInfoLookup = 0;
		}
	}
};

// Converts an ASCII string with escapes, '\xFF' and '\n' included, to a Unicode string
inline std::vector<Unicode> to_unicode(const std::string& szText)
{
	std::vector<Unicode> wszText;
	for (char c : szText)
	{
		wszText.push_back((Unicode)(uint16_t)(uint8_t)c);
	}
	wszText.push_back(0);
	return wszText;
}

inline std::string narrow_unicode(const Unicode* wszText)
{
	std::string szText;
	for (; wszText && *wszText; ++wszText)
	{
		const uint16_t c = (uint16_t)*wszText;
		if (c >= 0x20 && c < 0x7F)
		{
			szText += (char)c;
		}
		else
		{
			char szCode[8];
			sprintf_s(szCode, "\\x%X", c);
			szText += szCode;
		}
	}
	return szText;
}

// Texts measured by the tests
inline std::vector<std::vector<Unicode>> font_test_texts()
{
	std::vector<std::vector<Unicode>> texts;
	for (const char* szText : {
		"", "a", "Hello world", "Line 1\nLonger line 2\n3", "\n\n", "trailing\n",
		"\xFF" "c1Red\xFF" "c0White", "\xFF" "c7Not a color", "\xFF" "c", "ab\xFF" "c", "\xFF" "m!x", "\xFF" "M!y", "x\xFF",
		"The quick brown fox jumps over the lazy dog, again and again and again until the line is too long",
		"tab\tand  spaces   here", "~!@#$%^&*()_+{}|:<>?", })
	{
		texts.push_back(to_unicode(szText));
	}

	// Characters above 0xFF
	std::vector<Unicode> wide = to_unicode("w");
	wide.insert(wide.begin(), { (Unicode)0x100, (Unicode)0x4E2D, (Unicode)0xFFFF, (Unicode)0x1FF });
	texts.push_back(wide);
	return texts;
}
