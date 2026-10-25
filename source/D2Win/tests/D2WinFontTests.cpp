#include <D2WinTestDefines.h>

#ifdef FONT_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <cwchar>
#include <filesystem>
#include <string>
#include <vector>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinFont.h>


// Font globals of the D2MOO implementation that are not declared in the fixtures
extern char byte_6F8FD9D8[20];
extern int gnFramedText_X_6F8FE1F0;
extern int gnFramedText_Y_6F8FE1F4;
extern int gnFramedText_TextColor_6F8FE1F8;
extern int gnFramedText_Align_6F8FE1FC;
extern int gnFramedText_RectangleColor_6F8FE200;


TEST_SUITE("D2WinFontTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Texts with line breaks, color codes (\xFFc followed by the color), monster indicators (\xFFm followed by the indicator) and non-latin characters
	const wchar_t* const gTestTexts[] =
	{
		L"",
		L"Hello",
		L"Two\nlines",
		L"\xFF" L"c1Red text\xFF" L"c0 and white text",
		L"\xFF" L"c",
		L"\xFF" L"c9Invalid color",
		L"\xFF" L"mAMonster indicator",
		L"\n\nEmpty lines\n",
		L"Non-latin \x0410\x0411\x0412 characters",
		L"A long text that is wider than most of the boxes of the user interface, with multiple words and spaces",
	};

	// Framed text state of both implementations
	struct FramedTextState
	{
		int& nX;
		int& nY;
		int& nTextColor;
		int& nAlign;
		int& nRectangleColor;
		Unicode* wszBuffer;

		void set(const wchar_t* wszText, int nNewX, int nNewY, int nNewTextColor, int nNewAlign, int nNewRectangleColor)
		{
			std::wcscpy(reinterpret_cast<wchar_t*>(wszBuffer), wszText);
			nX = nNewX;
			nY = nNewY;
			nTextColor = nNewTextColor;
			nAlign = nNewAlign;
			nRectangleColor = nNewRectangleColor;
		}
	};

	struct FramedTextFixture : D2WinFixture<NoopFixture>
	{
		FramedTextState moo_framed_text = { gnFramedText_X_6F8FE1F0, gnFramedText_Y_6F8FE1F4, gnFramedText_TextColor_6F8FE1F8, gnFramedText_Align_6F8FE1FC, gnFramedText_RectangleColor_6F8FE200, gszFramedText_Buffer_6F8FD9F0 };
		FramedTextState original_framed_text = {
			original_d2win_global<int>(0x6F8FE1F0),
			original_d2win_global<int>(0x6F8FE1F4),
			original_d2win_global<int>(0x6F8FE1F8),
			original_d2win_global<int>(0x6F8FE1FC),
			original_d2win_global<int>(0x6F8FE200),
			&original_d2win_global<Unicode>(0x6F8FD9F0),
		};

		void check_framed_texts_eq()
		{
			CHECK_EQ(moo_framed_text.nX, original_framed_text.nX);
			CHECK_EQ(moo_framed_text.nY, original_framed_text.nY);
			CHECK_EQ(moo_framed_text.nTextColor, original_framed_text.nTextColor);
			CHECK_EQ(moo_framed_text.nAlign, original_framed_text.nAlign);
			CHECK_EQ(moo_framed_text.nRectangleColor, original_framed_text.nRectangleColor);
			CHECK_EQ(std::memcmp(moo_framed_text.wszBuffer, original_framed_text.wszBuffer, 1024 * sizeof(Unicode)), 0);
		}
	};

	// Runs a drawing function on both implementations and compares the recorded calls
	template<typename Function, typename... Args>
	void compare_font_function(Function* sut, Function* original, D2WinFontState& moo_font_state, D2WinFontState& original_font_state, Args... args)
	{
		D2WinCallLog::clear();
		if constexpr (std::is_void_v<decltype(sut(args...))>)
		{
			sut(args...);
			const auto moo_calls = D2WinCallLog::take();
			original(args...);
			const auto original_calls = D2WinCallLog::take();
			CHECK_EQ(moo_calls, original_calls);
		}
		else
		{
			const auto moo_result = sut(args...);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(args...);
			const auto original_calls = D2WinCallLog::take();
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);
		}

		CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
	}


	TEST_CASE_FIXTURE(FramedTextFixture, "D2Win.0x6F8A9B00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_ClearFramedText, dll_base + 0x00009B00);

		SUBCASE("")
		{
			moo_framed_text.set(L"Framed text", 1, 2, 3, 4, 5);
			original_framed_text.set(L"Framed text", 1, 2, 3, 4, 5);

			// Call both implementations
			sut();
			original();

			// Compare the modified globals
			check_framed_texts_eq();
			CHECK_EQ(moo_framed_text.wszBuffer[0].ch, 0);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A9B20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_ClearColorCodeChar, dll_base + 0x00009B20);

		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();

			// Compare the modified globals
			CHECK_EQ(std::memcmp(moo_font_state.wszColorCode, original_font_state.wszColorCode, 2 * sizeof(Unicode)), 0);
			CHECK_EQ(moo_font_state.wszColorCode[0].ch, 0);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A9B40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_ClearMonsterIndicatorChar, dll_base + 0x00009B40);

		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();

			// Compare the modified globals
			CHECK_EQ(std::memcmp(moo_font_state.wszMonsterIndicatorCode, original_font_state.wszMonsterIndicatorCode, 2 * sizeof(Unicode)), 0);
			CHECK_EQ(moo_font_state.wszMonsterIndicatorCode[0].ch, 0);
		}
	}

	TEST_CASE_FIXTURE(FramedTextFixture, "D2Win.0x6F8A9B60 (#10115)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10115_FONT, dll_base + 0x00009B60);

		// NOTE: The fonts of the fixture are already loaded, so nothing is loaded from the archives
		SUBCASE("")
		{
			char* original_szFontFolder = &original_d2win_global<char>(0x6F8FD9D8);
			moo_framed_text.set(L"Framed text", 1, 2, 3, 4, 5);
			original_framed_text.set(L"Framed text", 1, 2, 3, 4, 5);
			moo_font_state.wszColorCode[0] = 0;
			original_font_state.wszColorCode[0] = 0;
			moo_font_state.wszMonsterIndicatorCode[0] = 0;
			original_font_state.wszMonsterIndicatorCode[0] = 0;

			// Call both implementations
			D2WinCallLog::clear();
			sut();
			const auto moo_calls = D2WinCallLog::take();
			original();
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			check_framed_texts_eq();
			CHECK_EQ(std::string(byte_6F8FD9D8), std::string(original_szFontFolder));
			CHECK_EQ(moo_font_state.nLineSpacing, original_font_state.nLineSpacing);
			CHECK_EQ(moo_font_state.nTextHeightScale, original_font_state.nTextHeightScale);
			CHECK_EQ(moo_font_state.nTextBaselineScale, original_font_state.nTextBaselineScale);
			CHECK_EQ(moo_font_state.bKoreanEnglish, original_font_state.bKoreanEnglish);
			CHECK_EQ(std::memcmp(moo_font_state.wszColorCode, original_font_state.wszColorCode, 2 * sizeof(Unicode)), 0);
			CHECK_EQ(std::memcmp(moo_font_state.wszMonsterIndicatorCode, original_font_state.wszMonsterIndicatorCode, 2 * sizeof(Unicode)), 0);
			// Both implementations use their own version of the same function to find characters
			CHECK_EQ(moo_font_state.pfGetCharInfo == &FONT_GetCharInfoDirect, reinterpret_cast<uintptr_t>(original_font_state.pfGetCharInfo) == dll_base + 0x0000A100);
			CHECK_EQ(moo_font_state.pfGetCharInfo == &FONT_GetCharInfoSearch, reinterpret_cast<uintptr_t>(original_font_state.pfGetCharInfo) == dll_base + 0x0000A140);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A9DC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetCellFilePath, dll_base + 0x00009DC0);

		// Input data
		const int nFont = GENERATE(0, 1, 9, 12, 13);
		const bool bKoreanEnglish = GENERATE(false, true);
		const char* szFontFolder = GENERATE("Latin\\", "KOR\\");
		CAPTURE(nFont);
		CAPTURE(bKoreanEnglish);
		CAPTURE(szFontFolder);

		char* original_szFontFolder = &original_d2win_global<char>(0x6F8FD9D8);
		strcpy_s(byte_6F8FD9D8, szFontFolder);
		strcpy_s(original_szFontFolder, 20, szFontFolder);
		moo_font_state.bKoreanEnglish = bKoreanEnglish;
		original_font_state.bKoreanEnglish = bKoreanEnglish;

		char moo_pBuffer[80] = {};
		char original_pBuffer[80] = {};

		// Call both implementations
		sut(nFont, moo_pBuffer, 79);
		original(nFont, original_pBuffer, 79);

		// Compare potentially modified input data
		CHECK_EQ(std::string(moo_pBuffer), std::string(original_pBuffer));
		CHECK_EQ(std::memcmp(moo_pBuffer, original_pBuffer, sizeof(moo_pBuffer)), 0);
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9E90" * doctest::skip("Needs MPQ archives to load the font table from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_LoadFontTable, dll_base + 0x00009E90);

		SUBCASE("")
		{
			int nFont = 1;

			// Call both implementations
			sut(nFont);
			original(nFont);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A9F90 (#10116)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10116, dll_base + 0x00009F90);

		SUBCASE("")
		{
			// The fonts are freed with Fog.dll, so they are allocated with it. Some fonts are not loaded.
			for (D2WinFontState* pFontState : { &moo_font_state, &original_font_state })
			{
				for (int i = 0; i < NUM_FONTS; ++i)
				{
					D2FontCacheStrc& fontCache = pFontState->pFontCaches[i];
					fontCache = {};
					if (i % 3 != 2)
					{
						fontCache.pCellFile = static_cast<D2CellFileStrc*>(D2_ALLOC(16));
						D2WinCallLog::name_pointer(fontCache.pCellFile, "font cell file " + std::to_string(i));
					}

					if (i % 4 != 3)
					{
						fontCache.pFontInfo[0] = static_cast<D2FontStrc*>(D2_ALLOC(sizeof(D2FontStrc)));
						fontCache.pFontInfo[1] = fontCache.pFontInfo[0];
						fontCache.pCharInfo = fontCache.pFontInfo[0]->pChars;
					}
				}

				pFontState->pMonsterIndicatorsCellFile = static_cast<D2CellFileStrc*>(D2_ALLOC(16));
				D2WinCallLog::name_pointer(pFontState->pMonsterIndicatorsCellFile, "monster indicators cell file");
			}

			// Call both implementations
			D2WinCallLog::clear();
			sut();
			const auto moo_calls = D2WinCallLog::take();
			original();
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			for (int i = 0; i < NUM_FONTS; ++i)
			{
				CAPTURE(i);
				CHECK_EQ(moo_font_state.pFontCaches[i].pCellFile, nullptr);
				CHECK_EQ(original_font_state.pFontCaches[i].pCellFile, nullptr);
				CHECK_EQ(moo_font_state.pFontCaches[i].pFontInfo[0], nullptr);
				CHECK_EQ(original_font_state.pFontCaches[i].pFontInfo[0], nullptr);
				// The second pointer to the font table is not reset
				CHECK_EQ(moo_font_state.pFontCaches[i].pFontInfo[1] != nullptr, original_font_state.pFontCaches[i].pFontInfo[1] != nullptr);
			}

			CHECK_EQ(moo_font_state.pMonsterIndicatorsCellFile, nullptr);
			CHECK_EQ(original_font_state.pMonsterIndicatorsCellFile, nullptr);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A9FF0 (#10127)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10127_SetFont, dll_base + 0x00009FF0);

		// NOTE: All fonts of the fixture are loaded, so the fonts are never loaded from the archives
		// and fonts are only unloaded after 600 * 1024 milliseconds, which the tests don't wait for.

		// Input data
		const Font eCurrentFont = GENERATE(D2FONT_FONT8, D2FONT_FONT16, D2FONT_FONTINGAMECHAT);
		const Font nFontSize = GENERATE(D2FONT_FONT8, D2FONT_FONT16, D2FONT_FONTEXOCET10, D2FONT_FONTINGAMECHAT);
		const bool bKoreanEnglish = GENERATE(false, true);
		CAPTURE(eCurrentFont);
		CAPTURE(nFontSize);
		CAPTURE(bKoreanEnglish);

		moo_font_state.eFontSize = eCurrentFont;
		original_font_state.eFontSize = eCurrentFont;
		moo_font_state.bKoreanEnglish = bKoreanEnglish;
		original_font_state.bKoreanEnglish = bKoreanEnglish;

		// Call both implementations
		const auto moo_result = sut(nFontSize);
		const auto original_result = original(nFontSize);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare the modified globals
		CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		CHECK_EQ(moo_font_state.pfGetCharInfo == &FONT_GetCharInfoDirect, reinterpret_cast<uintptr_t>(original_font_state.pfGetCharInfo) == dll_base + 0x0000A100);
		CHECK_EQ(moo_font_state.pfGetCharInfo == &FONT_GetCharInfoSearch, reinterpret_cast<uintptr_t>(original_font_state.pfGetCharInfo) == dll_base + 0x0000A140);
		for (int i = 0; i < NUM_FONTS; ++i)
		{
			CAPTURE(i);
			CHECK_EQ(moo_font_state.pFontCaches[i].pCellFile, original_font_state.pFontCaches[i].pCellFile);
		}

		// The current font cache can't be accessed directly in the original .dll, but it is used for drawing
		compare_font_function(D2Win_10117_DrawText, original_d2win_function<decltype(D2Win_10117_DrawText)>(0x6F8AAD40), moo_font_state, original_font_state, D2_USTR(L"Text"), 10, 20, 0, FALSE);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA100")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetCharInfoDirect, dll_base + 0x0000A100);

		// Both implementations use the same font table of the fixture, so they return the same pointers
		for (const wchar_t wChar : { L'\0', L'a', L'Z', L'\xFF', L'\x100', L'\x0410', L'\xFFFF' })
		{
			CAPTURE(static_cast<int>(wChar));

			// Call both implementations
			const D2CharStrc* moo_result = sut(wChar);
			const D2CharStrc* original_result = original(wChar);

			// Compare return values
			CHECK_EQ(moo_result, original_result);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA140")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetCharInfoSearch, dll_base + 0x0000A140);

		// Input data
		// The search uses the number of characters of the font table, only the first characters are used in some subcases
		const WORD wNumChars = GENERATE(256, 100, 1);
		CAPTURE(wNumChars);
		font.wNumChars = wNumChars;

		// Both implementations use the same font table of the fixture, so they return the same pointers
		for (const wchar_t wChar : { L'\0', L'a', L'Z', L'\xFF', L'\x100', L'\x0410', L'\xFFFF' })
		{
			CAPTURE(static_cast<int>(wChar));

			// Call both implementations
			const D2CharStrc* moo_result = sut(wChar);
			const D2CharStrc* original_result = original(wChar);

			// Compare return values
			CHECK_EQ(moo_result, original_result);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA1D0 (#10123)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10123, dll_base + 0x0000A1D0);

		for (const wchar_t* wszText : gTestTexts)
		{
			for (const int nTextLength : { 0, 1, 3, 4, 10, 1000 })
			{
				CAPTURE(nTextLength);
				compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), nTextLength);
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA260 (#10122)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10122, dll_base + 0x0000A260);

		for (const wchar_t* wszText : gTestTexts)
		{
			for (const int nTextLength : { 0, 1, 3, 4, 10, 1000 })
			{
				CAPTURE(nTextLength);
				compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), nTextLength);
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA2A0 (#10121)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10121_GetTextWidth, dll_base + 0x0000A2A0);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText));
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA2F0 (#10125)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10125, dll_base + 0x0000A2F0);

		SUBCASE("")
		{
			font.nHeight = static_cast<BYTE>(random_unsigned_integer(1, 50));

			compare_font_function(sut, original, moo_font_state, original_font_state);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA310 (#10119)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10119_DrawCroppedText, dll_base + 0x0000A310);

		// Input data
		const int32_t nCropOffset = GENERATE(-1, 0, 4);
		const int32_t nCropHeight = GENERATE(2, 20);
		const DisplayType eDisplayType = GENERATE(DISPLAYTYPE_GDI, DISPLAYTYPE_DIRECT3D);
		CAPTURE(nCropOffset);
		CAPTURE(nCropHeight);
		CAPTURE(eDisplayType);
		D2WinMock::eDisplayType = eDisplayType;

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), 100, 200, 0, nCropOffset, nCropHeight, 0);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA510")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_DrawScrollingText, dll_base + 0x0000A510);

		// Input data
		const int32_t nScrollOffset = GENERATE(-50, 0, 30);
		const int32_t nMaxWidth = GENERATE(20, 300);
		CAPTURE(nScrollOffset);
		CAPTURE(nMaxWidth);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), 100, 200, 3, nScrollOffset, nMaxWidth);
		}
	}

	TEST_CASE_FIXTURE(FramedTextFixture, "D2Win.0x6F8AA6E0 (#10124)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10124, dll_base + 0x0000A6E0);

		// Input data
		const int nAlign = GENERATE(0, 1);
		const int nRectangleColor = GENERATE(0, 64, 128);
		const int32_t nScreenHeight = GENERATE(600, 30);
		const Font eFont = GENERATE(D2FONT_FONT8, D2FONT_FONT16, D2FONT_FONT30);
		const int nX = GENERATE(-50, 300, 790);
		CAPTURE(nAlign);
		CAPTURE(nRectangleColor);
		CAPTURE(nScreenHeight);
		CAPTURE(eFont);
		CAPTURE(nX);

		D2WinMock::nScreenHeight = nScreenHeight;
		moo_font_state.pfSetFont(eFont);
		original_font_state.pfSetFont(eFont);

		for (const wchar_t* wszText : gTestTexts)
		{
			moo_framed_text.set(wszText, nX, 100, 2, nAlign, nRectangleColor);
			original_framed_text.set(wszText, nX, 100, 2, nAlign, nRectangleColor);
			moo_font_state.nFramedTextProgressColor = 0;
			original_font_state.nFramedTextProgressColor = 0;

			compare_font_function(sut, original, moo_font_state, original_font_state);
			check_framed_texts_eq();
			CHECK_EQ(moo_font_state.nFramedTextProgressColor, original_font_state.nFramedTextProgressColor);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA910")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetMaxLineWidth, dll_base + 0x0000A910);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText));
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AA9E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_DrawTextEx, dll_base + 0x0000A9E0);

		// Input data
		const int32_t nBoxWidth = GENERATE(0, 100, 400);
		const int32_t bCentered = GENERATE(0, 1);
		CAPTURE(nBoxWidth);
		CAPTURE(bCentered);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), 100, 200, nBoxWidth, 4, bCentered);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AABB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_GetFirstLineWidth, dll_base + 0x0000ABB0);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText));
		}
	}

	TEST_CASE_FIXTURE(FramedTextFixture, "D2Win.0x6F8AAC60 (#10129)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10129_DrawFramedText, dll_base + 0x0000AC60);

		// Input data
		const int nAlign = GENERATE(0, 1);
		CAPTURE(nAlign);

		std::vector<wchar_t> longText(1100, L'a');
		longText.back() = L'\0';

		for (const wchar_t* wszText : { gTestTexts[0], gTestTexts[3], gTestTexts[9], static_cast<const wchar_t*>(longText.data()), static_cast<const wchar_t*>(nullptr) })
		{
			moo_framed_text.set(L"Previous text", 1, 2, 3, 4, 5);
			original_framed_text.set(L"Previous text", 1, 2, 3, 4, 5);

			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), 100, 200, 3, nAlign);
			check_framed_texts_eq();
		}
	}

	TEST_CASE_FIXTURE(FramedTextFixture, "D2Win.0x6F8AACD0 (#10130)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10130_DrawFramedTextEx, dll_base + 0x0000ACD0);

		// Input data
		const int nAlign = GENERATE(0, 1);
		const int nRectangleColor = GENERATE(0, 100);
		CAPTURE(nAlign);
		CAPTURE(nRectangleColor);

		std::vector<wchar_t> longText(1100, L'a');
		longText.back() = L'\0';

		for (const wchar_t* wszText : { gTestTexts[0], gTestTexts[3], gTestTexts[9], static_cast<const wchar_t*>(longText.data()), static_cast<const wchar_t*>(nullptr) })
		{
			moo_framed_text.set(L"Previous text", 1, 2, 3, 4, 5);
			original_framed_text.set(L"Previous text", 1, 2, 3, 4, 5);

			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), 100, 200, 3, nAlign, nRectangleColor);
			check_framed_texts_eq();
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AAD40 (#10117)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10117_DrawText, dll_base + 0x0000AD40);

		// Input data
		const BOOL bCentered = GENERATE(0, 1);
		const int nColor = GENERATE(0, 5);
		CAPTURE(bCentered);
		CAPTURE(nColor);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), 100, 200, nColor, bCentered);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AAD80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10118_DrawBlendedText, dll_base + 0x0000AD80);

		// Input data
		const int32_t bCentered = GENERATE(0, 1);
		const DrawMode eDrawMode = GENERATE(DRAWMODE_NORMAL, DRAWMODE_BURN);
		CAPTURE(bCentered);
		CAPTURE(eDrawMode);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), 100, 200, 3, bCentered, eDrawMode);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AAF80 (#10126)" * doctest::skip("Loops until it reads out of bounds, the end of the text is never checked"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10126_DrawTextFromCache, dll_base + 0x0000AF80);

		SUBCASE("")
		{
			// Call both implementations
			sut(D2_USTR(L"Text"), 100, 200);
			original(D2_USTR(L"Text"), 100, 200);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AB080 (#10132)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10132, dll_base + 0x0000B080);

		// Input data
		const int nX = GENERATE(-20, 100, 790);
		const int nY = GENERATE(0, 200, 590);
		CAPTURE(nX);
		CAPTURE(nY);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), nX, nY, 0x40u, DRAWMODE_TRANS50, 2);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AB1B0 (#10133)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10133, dll_base + 0x0000B1B0);

		// Input data
		const int nX = GENERATE(-20, 100, 790);
		const int nY = GENERATE(0, 5, 200, 590);
		CAPTURE(nX);
		CAPTURE(nY);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), nX, nY, 0x40u, DRAWMODE_TRANS50, 2);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AB260 (#10131)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10131_GetTextDimensions, dll_base + 0x0000B260);

		for (const wchar_t* wszText : gTestTexts)
		{
			int moo_pWidth = 1234;
			int moo_pHeight = 1234;
			int original_pWidth = 1234;
			int original_pHeight = 1234;

			// Call both implementations
			sut(D2_USTR(wszText), &moo_pWidth, &moo_pHeight);
			original(D2_USTR(wszText), &original_pWidth, &original_pHeight);

			// Compare potentially modified input data
			CHECK_EQ(moo_pWidth, original_pWidth);
			CHECK_EQ(moo_pHeight, original_pHeight);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB2F0 (#10128)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10128, dll_base + 0x0000B2F0);

		for (int nChar = 0; nChar < 256; ++nChar)
		{
			CAPTURE(nChar);

			// Call both implementations
			const auto moo_result = sut(static_cast<uint8_t>(nChar));
			const auto original_result = original(static_cast<uint8_t>(nChar));

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AB360")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FONT_DrawTextWithBox, dll_base + 0x0000B360);

		// Input data
		const int nX = GENERATE(-20, 100, 790);
		const int nY = GENERATE(0, 5, 200, 590);
		const int nBoxWidth = GENERATE(0, 150);
		CAPTURE(nX);
		CAPTURE(nY);
		CAPTURE(nBoxWidth);

		for (const wchar_t* wszText : gTestTexts)
		{
			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), nX, nY, nBoxWidth, 0x40u, DRAWMODE_TRANS50, 2);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AB480 (#10134)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10134_DrawCellFile, dll_base + 0x0000B480);

		// Input data
		const int32_t nFrames = GENERATE(0, 1, 4);
		const int nDiv = GENERATE(0, 1, 2, 3);
		const int nColor = GENERATE(-1, 0, 7);
		CAPTURE(nFrames);
		CAPTURE(nDiv);
		CAPTURE(nColor);

		D2WinFakeCellFile cellFile("cellfile", nFrames, 100, 50);

		compare_font_function(sut, original, moo_font_state, original_font_state, cellFile.get(), 300, 200, nDiv, DRAWMODE_TRANS25, nColor);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AB560 (#10120)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10120, dll_base + 0x0000B560);

		// Input data
		const int nX = GENERATE(-20, 100, 790);
		const int nY = GENERATE(0, 200, 590);
		const int nAlign = GENERATE(0, 1);
		const int nProgress = GENERATE(0, 64, 128);
		CAPTURE(nX);
		CAPTURE(nY);
		CAPTURE(nAlign);
		CAPTURE(nProgress);

		for (const wchar_t* wszText : gTestTexts)
		{
			moo_font_state.nFramedTextProgressColor = 0;
			original_font_state.nFramedTextProgressColor = 0;

			compare_font_function(sut, original, moo_font_state, original_font_state, D2_USTR(wszText), nX, nY, 3, nAlign, nProgress);
			CHECK_EQ(moo_font_state.nFramedTextProgressColor, original_font_state.nFramedTextProgressColor);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AB730 (#10200)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10200, dll_base + 0x0000B730);

		// The lines are allocated with Fog.dll, they are freed by the tested function
		const auto create_split_text = [](int32_t nLines)
		{
			D2SplittedTextStrc* pFirstLine = nullptr;
			for (int32_t i = 0; i < nLines; ++i)
			{
				D2SplittedTextStrc* pLine = d2win_calloc<D2SplittedTextStrc>();
				pLine->wszLine = d2win_alloc_string(L"Line");
				pLine->pNextLine = pFirstLine;
				pFirstLine = pLine;
			}

			return pFirstLine;
		};

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 1, 5);

			// Call both implementations
			sut(create_split_text(nLines));
			original(create_split_text(nLines));
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AB770 (#10199)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10199, dll_base + 0x0000B770);

		const auto get_lines = [](const D2SplittedTextStrc* pSplitText)
		{
			std::vector<std::wstring> lines;
			for (const D2SplittedTextStrc* pLine = pSplitText; pLine; pLine = pLine->pNextLine)
			{
				lines.emplace_back(reinterpret_cast<const wchar_t*>(pLine->wszLine));
			}

			return lines;
		};

		// Input data
		const int nMaxLength = GENERATE(20, 100, 500);
		CAPTURE(nMaxLength);

		for (const wchar_t* wszText : gTestTexts)
		{
			int moo_pLines = 1234;
			int original_pLines = 1234;

			// Call both implementations
			D2SplittedTextStrc* moo_result = sut(D2_USTR(wszText), &moo_pLines, nMaxLength);
			D2SplittedTextStrc* original_result = original(D2_USTR(wszText), &original_pLines, nMaxLength);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK(get_lines(moo_result) == get_lines(original_result));

			// Compare potentially modified input data
			CHECK_EQ(moo_pLines, original_pLines);

			D2Win_10200(moo_result);
			original_d2win_function<decltype(D2Win_10200)>(0x6F8AB730)(original_result);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ABA70 (#10206)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10206, dll_base + 0x0000BA70);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values, which are the functions of the respective implementation
			CHECK_EQ(moo_result, &D2Win_10129_DrawFramedText);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result), dll_base + 0x0000AC60);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ABA80 (#10207)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10207, dll_base + 0x0000BA80);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values, which are the functions of the respective implementation
			CHECK_EQ(moo_result, &D2Win_10131_GetTextDimensions);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result), dll_base + 0x0000B260);
		}
	}
}

#endif
