#include <doctest.h>

#include <cstdint>
#include <string>
#include <vector>

#include <D2WinFont.h>

#include "D2WinFontFixtures.h"


namespace
{
// Calls a measurement function of both implementations on every test text, with both character lookups
template<typename Function, typename Call>
void compare_on_texts(D2WinFontFixture<NoOpFixture>& fixture, Function* sut, Function* original, Call&& call)
{
	for (bool bFindCharInfo : { false, true })
	{
		for (Font nFont : { D2FONT_FONT16, D2FONT_FONT8 })
		{
			fixture.install_fonts(bFindCharInfo, nFont);
			for (const std::vector<Unicode>& text : font_test_texts())
			{
				CAPTURE(bFindCharInfo);
				CAPTURE(nFont);
				CAPTURE(narrow_unicode(text.data()));
				CHECK_EQ(call(sut, text.data()), call(original, text.data()));
			}
		}
	}
}
}


TEST_SUITE("D2WinFontTests")
{
	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AA100")
	{
		const auto [sut, original] = make_d2win_pair(FONT_GetCharInfoByIndex, 0x6F8AA100);

		install_fonts(false);
		for (uint32_t nChar : { 0u, 1u, (uint32_t)'a', 0xFEu, 0xFFu, 0x100u, 0x4E2Du, 0xFFFFu })
		{
			CAPTURE(nChar);
			CHECK_EQ(sut((Unicode)(uint16_t)nChar), original((Unicode)(uint16_t)nChar));
		}
	}

	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AA140")
	{
		const auto [sut, original] = make_d2win_pair(FONT_FindCharInfo, 0x6F8AA140);

		// The second font holds the multiples of 37, the first one all the characters below 0x100
		for (Font nFont : { D2FONT_FONT16, D2FONT_FONT8 })
		{
			for (int nCount : { 256, 100, 1, 0 })
			{
				install_fonts(true, nFont);
				fonts[0].font.unk0x08 = (WORD)nCount;
				fonts[1].font.unk0x08 = (WORD)nCount;
				for (uint32_t nChar : { 0u, 1u, 36u, 37u, 74u, (uint32_t)'a', 0xFFu, 0x100u, 37u * 99, 37u * 100, 37u * 255, 37u * 255 + 1, 0xFFFFu })
				{
					CAPTURE(nFont);
					CAPTURE(nCount);
					CAPTURE(nChar);
					CHECK_EQ(sut((Unicode)(uint16_t)nChar), original((Unicode)(uint16_t)nChar));
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AA2A0 (#10121)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10121_GetTextWidth, 0x6F8AA2A0);
		compare_on_texts(*this, sut, original, [](auto pFunction, const Unicode* wszText) { return pFunction(wszText); });
	}

	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AA260 (#10122)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10122, 0x6F8AA260);
		for (int nLength : { 0, 1, 3, 7, 255 })
		{
			CAPTURE(nLength);
			compare_on_texts(*this, sut, original, [nLength](auto pFunction, const Unicode* wszText) { return pFunction(wszText, nLength); });
		}
	}

	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AA1D0 (#10123)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10123, 0x6F8AA1D0);
		for (int nLength : { 0, 1, 2, 3, 4, 7, 255 })
		{
			CAPTURE(nLength);
			compare_on_texts(*this, sut, original, [nLength](auto pFunction, const Unicode* wszText) { return pFunction(wszText, nLength); });
		}
	}

	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AA910")
	{
		const auto [sut, original] = make_d2win_pair(FONT_GetMaxLineWidth, 0x6F8AA910);
		compare_on_texts(*this, sut, original, [](auto pFunction, const Unicode* wszText) { return pFunction(wszText); });
	}

	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AABB0")
	{
		const auto [sut, original] = make_d2win_pair(FONT_GetFirstLineWidth, 0x6F8AABB0);
		compare_on_texts(*this, sut, original, [](auto pFunction, const Unicode* wszText) { return pFunction(wszText); });
	}

	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AB260 (#10131)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10131_GetTextDimensions, 0x6F8AB260);
		const auto [height, original_height] = make_d2win_pair(D2Win_10125, 0x6F8AA2F0);

		for (int nLineHeightPercent : { 16, 13, 10 })
		{
			CAPTURE(nLineHeightPercent);
			compare_on_texts(*this, sut, original, [nLineHeightPercent](auto pFunction, const Unicode* wszText)
			{
				for (int i = 0; i < 2; ++i)
				{
					*font_globals(i).pLineHeightPercent = nLineHeightPercent;
				}
				int nWidth = -1;
				int nHeight = -1;
				pFunction(wszText, &nWidth, &nHeight);
				return std::to_string(nWidth) + "x" + std::to_string(nHeight);
			});
		}

		for (Font nFont : { D2FONT_FONT16, D2FONT_FONT8 })
		{
			install_fonts(false, nFont);
			CHECK_EQ(height(), original_height());
		}
	}

	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AB2F0 (#10128)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10128, 0x6F8AB2F0);
		for (int nChar = 0; nChar < 256; ++nChar)
		{
			CAPTURE(nChar);
			CHECK_EQ(sut((uint8_t)nChar), original((uint8_t)nChar));
		}
	}

	// Switching between loaded fonts, with the lookup switch of the Korean English version
	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8A9FF0 (#10127)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10127_SetFont, 0x6F8A9FF0);

		const Font sequence[] = { D2FONT_FONT16, D2FONT_FONT8, D2FONT_FONT8, D2FONT_FONTINGAMECHAT, D2FONT_FONT42, D2FONT_FONTINGAMECHAT, D2FONT_FONT16 };
		for (uint8_t bSwitch : { 0, 1 })
		{
			for (bool bFindCharInfo : { false, true })
			{
				std::vector<std::string> states[2];
				for (int i = 0; i < 2; ++i)
				{
					TickCountMock::dwTickCount = 5000 << 10;
					install_fonts(bFindCharInfo);
					const FontGlobals& globals = font_globals(i);
					*globals.pbSwitchCharInfoLookup = bSwitch;
					DWORD dwTick = 5000 << 10;
					for (Font nFont : sequence)
					{
						// Advances by 50 shifted ticks, the fonts are only unloaded after 600 (the fake fonts can't be freed)
						dwTick += 50 << 10;
						TickCountMock::dwTickCount = dwTick;
						const Font nOld = (i == 0 ? sut : original)(nFont);

						std::string szState = std::to_string(nOld) + " -> " + std::to_string(*globals.pFont);
						szState += (*globals.ppfGetCharInfo == globals.pfFindCharInfo) ? " find" : (*globals.ppfGetCharInfo == globals.pfGetCharInfoByIndex) ? " index" : " other";
						for (int nFontIndex = 0; nFontIndex < 14; ++nFontIndex)
						{
							szState += " " + std::to_string(globals.pFontCaches[nFontIndex].dwShiftedTickCount);
						}
						szState += " last " + std::to_string(*globals.pLastShiftedTickCount);
						states[i].push_back(szState);
					}
				}

				CAPTURE(bSwitch);
				CAPTURE(bFindCharInfo);
				CHECK_EQ(states[0], states[1]);
			}
		}
	}

	// Splitting texts in lines that fit in a width
	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AB770 (#10199)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10199, 0x6F8AB770);
		const auto [free_text, original_free_text] = make_d2win_pair(D2Win_10200, 0x6F8AB730);

		for (int nMaxLength : { 1, 20, 60, 150, 1000 })
		{
			CAPTURE(nMaxLength);
			compare_on_texts(*this, sut, original, [nMaxLength, free_text = free_text, original_free_text = original_free_text](auto pFunction, const Unicode* wszText)
			{
				const bool bMoo = pFunction == &D2Win_10199;
				int nLines = -1;
				D2SplittedTextStrc* pSplitText = pFunction(wszText, &nLines, nMaxLength);
				std::string szLines = std::to_string(nLines) + ":";
				int nCount = 0;
				for (D2SplittedTextStrc* pLine = pSplitText; pLine && nCount < 1000; pLine = pLine->pNextLine, ++nCount)
				{
					szLines += " [" + narrow_unicode(pLine->wszLine) + "]";
				}
				(bMoo ? free_text : original_free_text)(pSplitText);
				return szLines;
			});
		}
	}
}
