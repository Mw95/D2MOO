#include <D2WinTestDefines.h>

#ifdef TEXTBOX_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cwchar>
#include <filesystem>
#include <string>
#include <vector>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinScrollBar.h>
#include <D2WinTextBox.h>


// Line spacing of the text boxes, depends on the language
extern int32_t dword_6F8BE238;
// Whether the text boxes use a reduced line spacing
extern int32_t dword_6F96A8DC;


TEST_SUITE("D2WinTextBoxTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Text box at x = [100, 400], y = [200, 400]. The lines are allocated with Fog.dll, so that they can be freed by the tested functions.
	void setup_textbox(D2WinTextBoxStrc& pTextBox, int32_t nLines, int32_t nColumns = 1)
	{
		d2win_init_control(pTextBox.controlHeader, D2WIN_TEXTBOX, 100, 400, 300, 200);
		pTextBox.eFont = D2FONT_FONT16;
		pTextBox.nNumColumns = nColumns;
		pTextBox.nCurrentLine = -1;
		pTextBox.nExtraLineSpacing = 4;
		pTextBox.nLineSpacing = 2;
		pTextBox.nContinuedLineSpacing = 1;
		pTextBox.nTextOffsetX = 5;
		pTextBox.nTextOffsetY = 3;

		for (int32_t i = 0; i < nLines; ++i)
		{
			D2WinTextBoxLineStrc* pLine = d2win_calloc<D2WinTextBoxLineStrc>();
			wchar_t wszText[64] = {};
			std::swprintf(wszText, std::size(wszText), L"Line %d of the text box", i);
			pLine->pColumns[0] = d2win_alloc_string(wszText);
			if (nColumns > 1)
			{
				std::swprintf(wszText, std::size(wszText), L"Column %d", i);
				pLine->pColumns[1] = d2win_alloc_string(wszText);
			}

			pLine->nColor = i % 5;
			pLine->bContinued = i % 3 == 0;

			if (pTextBox.pLastLine)
			{
				pTextBox.pLastLine->pNext = pLine;
			}
			else
			{
				pTextBox.pFirstLine = pLine;
				pTextBox.pCurrentLine = pLine;
			}

			pTextBox.pLastLine = pLine;
			++pTextBox.nNumLines;
		}
	}

	void setup_scrollbar(D2WinScrollBarStrc& pScrollBar, D2WinTextBoxStrc& pTextBox, int32_t nMaxSteps = 10)
	{
		d2win_init_control(pScrollBar.controlHeader, D2WIN_SCROLLBAR, 408, 398, 10, 184);
		pScrollBar.nMaxSteps = nMaxSteps;
		pScrollBar.pTextBox = &pTextBox;
		pTextBox.pScrollBar = &pScrollBar;
	}

	std::vector<std::vector<std::wstring>> get_columns(const D2WinTextBoxStrc& pTextBox)
	{
		std::vector<std::vector<std::wstring>> lines;
		for (const D2WinTextBoxLineStrc* pLine = pTextBox.pFirstLine; pLine; pLine = pLine->pNext)
		{
			std::vector<std::wstring> columns;
			for (const Unicode* wszColumn : pLine->pColumns)
			{
				columns.emplace_back(wszColumn ? reinterpret_cast<const wchar_t*>(wszColumn) : L"<null>");
			}

			lines.push_back(columns);
		}

		return lines;
	}

	// The visitor only compares the first character of the columns, the strings are compared separately
	void check_textboxes_eq(D2WinTextBoxStrc& moo_pTextBox, D2WinTextBoxStrc& original_pTextBox)
	{
		MOO_CHECK_EQ(moo_pTextBox, original_pTextBox, "Comparing pTextBox");
		CHECK(get_columns(moo_pTextBox) == get_columns(original_pTextBox));
	}

	// Runs a function taking a text box on both implementations and compares the results
	template<typename Function, typename... Args>
	void compare_textbox_function(Function* sut, Function* original, D2WinTextBoxStrc& moo_pTextBox, D2WinTextBoxStrc& original_pTextBox, Args... args)
	{
		D2WinCallLog::clear();
		if constexpr (std::is_void_v<decltype(sut(&moo_pTextBox, args...))>)
		{
			sut(&moo_pTextBox, args...);
			const auto moo_calls = D2WinCallLog::take();
			original(&original_pTextBox, args...);
			const auto original_calls = D2WinCallLog::take();
			CHECK_EQ(moo_calls, original_calls);
		}
		else
		{
			const auto moo_result = sut(&moo_pTextBox, args...);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(&original_pTextBox, args...);
			const auto original_calls = D2WinCallLog::take();
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);
		}

		check_textboxes_eq(moo_pTextBox, original_pTextBox);
	}


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AFAA0 (#10042)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10042_TEXTBOX_Create, dll_base + 0x0000FAA0);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("textbox", 6);
			D2WinEditBoxFontStrc font = { D2FONT_FONT8, 3 };
			int32_t scrollBarRect[3] = { 50, 60, 70 };
			const int nX = random_unsigned_integer(0, 800);
			const int nY = random_unsigned_integer(0, 600);
			const int nWidth = random_unsigned_integer(30, 800);
			const int nHeight = random_unsigned_integer(40, 600);
			const int nTextOffsetX = random_unsigned_integer(0, 10);
			const int nTextOffsetY = random_unsigned_integer(0, 10);
			const unsigned int dwTextBoxFlags = GENERATE(0u, 1u, 2u, 4u, 5u, 0x40u);
			const int pFont = GENERATE(true, false) ? reinterpret_cast<int>(&font) : 0;
			const int pScrollBarRect = GENERATE(true, false) ? reinterpret_cast<int>(scrollBarRect) : 0;

			// Call both implementations
			D2WinTextBoxStrc* moo_result = sut(nX, nY, nWidth, nHeight, nTextOffsetX, nTextOffsetY, cellFile.get(), D2WinCallbacks::Callback, dwTextBoxFlags, pFont, pScrollBarRect);
			D2WinTextBoxStrc* original_result = original(nX, nY, nWidth, nHeight, nTextOffsetX, nTextOffsetY, cellFile.get(), D2WinCallbacks::Callback, dwTextBoxFlags, pFont, pScrollBarRect);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &TEXTBOX_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &TEXTBOX_HandleMouseDown);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x00011130);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x000115A0);
			CHECK_EQ(moo_result->controlHeader.pfHandleVirtualKeyInput != nullptr, original_result->controlHeader.pfHandleVirtualKeyInput != nullptr);
			CHECK_EQ(dword_6F8BE238, original_d2win_global<int32_t>(0x6F8BE238));
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AFCC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TEXTBOX_UpdateLineSpacing, dll_base + 0x0000FCC0);

		SUBCASE("")
		{
			// Input data
			const Font nFontSize = GENERATE(D2FONT_FONT6, D2FONT_FONT16, D2FONT_FONT42);
			const int32_t bReducedLineSpacing = GENERATE(0, 1);
			int32_t& original_bReducedLineSpacing = original_d2win_global<int32_t>(0x6F96A8DC);
			int32_t& original_nLineSpacing = original_d2win_global<int32_t>(0x6F8BE238);
			dword_6F96A8DC = bReducedLineSpacing;
			original_bReducedLineSpacing = bReducedLineSpacing;
			dword_6F8BE238 = -1;
			original_nLineSpacing = -1;

			// Call both implementations
			sut(nFontSize);
			original(nFontSize);

			// Compare the modified globals
			CHECK_EQ(dword_6F8BE238, original_nLineSpacing);
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);

			dword_6F96A8DC = 0;
			original_bReducedLineSpacing = 0;
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AFDC0 (#10043)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10043_TEXTBOX_Destroy, dll_base + 0x0000FDC0);

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 3);
			const bool bWithScrollBar = GENERATE(false, true);
			D2WinTextBoxStrc* moo_pTextBox = d2win_calloc<D2WinTextBoxStrc>();
			D2WinTextBoxStrc* original_pTextBox = d2win_calloc<D2WinTextBoxStrc>();
			D2WinScrollBarStrc* moo_pScrollBar = d2win_calloc<D2WinScrollBarStrc>();
			D2WinScrollBarStrc* original_pScrollBar = d2win_calloc<D2WinScrollBarStrc>();
			setup_textbox(*moo_pTextBox, nLines, 2);
			setup_textbox(*original_pTextBox, nLines, 2);
			if (bWithScrollBar)
			{
				setup_scrollbar(*moo_pScrollBar, *moo_pTextBox);
				setup_scrollbar(*original_pScrollBar, *original_pTextBox);
				moo_pScrollBar->controlHeader.pNext = &moo_pTextBox->controlHeader;
				original_pScrollBar->controlHeader.pNext = &original_pTextBox->controlHeader;
				moo_state.pControlList = &moo_pScrollBar->controlHeader;
				original_state.pControlList = &original_pScrollBar->controlHeader;
			}
			else
			{
				moo_state.pControlList = &moo_pTextBox->controlHeader;
				original_state.pControlList = &original_pTextBox->controlHeader;
			}

			// Call both implementations
			const auto moo_result = sut(moo_pTextBox);
			const auto original_result = original(original_pTextBox);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			check_textboxes_eq(*moo_pTextBox, *original_pTextBox);
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AFE30 (#10047)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10047, dll_base + 0x0000FE30);

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 1, 5);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, nLines, 2);
			setup_textbox(original_pTextBox, nLines, 2);
			moo_pTextBox.nLine = 2;
			original_pTextBox.nLine = 2;

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}

		SUBCASE("Null text box")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFED0 (#10062)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10062, dll_base + 0x0000FED0);

		SUBCASE("")
		{
			// Input data
			const int nContinuedLineSpacing = random_unsigned_integer(0, 20);
			const int nLineSpacing = random_unsigned_integer(0, 20);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nContinuedLineSpacing, nLineSpacing);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AFF30 (#10045)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10045, dll_base + 0x0000FF30);

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 3, 15);
			const char* szText = GENERATE("", "Short text", "   Leading spaces", "A text that is much too long to fit on a single line of the text box and has to be wrapped");
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, nLines);
			setup_textbox(original_pTextBox, nLines);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, szText);
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AFFB0 (#10046)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10046, dll_base + 0x0000FFB0);

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 3);
			const char* szText = GENERATE("", "Short text", "UTF-8 \xC3\xA9\xC3\xA0 characters", "A text that is much too long to fit on a single line of the text box and has to be wrapped");
			const int nColor = GENERATE(0, 4, 9);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, nLines);
			setup_textbox(original_pTextBox, nLines);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, szText, nColor);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B0030 (#10044)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10044, dll_base + 0x00010030);

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 3);
			const wchar_t* wszText = GENERATE(L"", L"Short text", L"A text that is much too long to fit on a single line of the text box and has to be wrapped");
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, nLines);
			setup_textbox(original_pTextBox, nLines);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, D2_USTR(wszText));
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B0040 (#10051)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10051, dll_base + 0x00010040);

		// Input data
		const int32_t nLines = GENERATE(0, 3, 15);
		const wchar_t* wszText = GENERATE(L"", L"Short text", L"  \t Leading whitespaces", L"A text that is much too long to fit on a single line of the text box and has to be wrapped", L"Averyveryverylongwordwithoutanyspacethatdoesnotfitonasinglelineofthetextbox");
		const int nColor = GENERATE(0, 4);
		const char bContinued = GENERATE(0, 1);
		const int nIndentMode = GENERATE(0, 1, 2);
		const int dwTextBoxFlags = GENERATE(0, 0x20);
		const bool bWithScrollBar = GENERATE(false, true);
		CAPTURE(nLines);
		CAPTURE(nColor);
		CAPTURE(static_cast<int>(bContinued));
		CAPTURE(nIndentMode);
		CAPTURE(dwTextBoxFlags);
		CAPTURE(bWithScrollBar);

		D2WinTextBoxStrc moo_pTextBox{};
		D2WinTextBoxStrc original_pTextBox{};
		D2WinScrollBarStrc moo_pScrollBar{};
		D2WinScrollBarStrc original_pScrollBar{};
		setup_textbox(moo_pTextBox, nLines);
		setup_textbox(original_pTextBox, nLines);
		moo_pTextBox.dwTextBoxFlags = dwTextBoxFlags;
		original_pTextBox.dwTextBoxFlags = dwTextBoxFlags;
		if (bWithScrollBar)
		{
			setup_scrollbar(moo_pScrollBar, moo_pTextBox, 4);
			setup_scrollbar(original_pScrollBar, original_pTextBox, 4);
		}

		compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, D2_USTR(wszText), nColor, bContinued, nIndentMode);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B05E0 (#10198)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10198, dll_base + 0x000105E0);

		// Input data
		const int32_t nLines = GENERATE(0, 3);
		const int nCount = GENERATE(0, 1, 20);
		const char bContinued = GENERATE(0, 1);
		const bool bWithScrollBar = GENERATE(false, true);
		CAPTURE(nLines);
		CAPTURE(nCount);
		CAPTURE(static_cast<int>(bContinued));
		CAPTURE(bWithScrollBar);

		D2WinTextBoxStrc moo_pTextBox{};
		D2WinTextBoxStrc original_pTextBox{};
		D2WinScrollBarStrc moo_pScrollBar{};
		D2WinScrollBarStrc original_pScrollBar{};
		setup_textbox(moo_pTextBox, nLines);
		setup_textbox(original_pTextBox, nLines);
		if (bWithScrollBar)
		{
			setup_scrollbar(moo_pScrollBar, moo_pTextBox);
			setup_scrollbar(original_pScrollBar, original_pTextBox);
		}

		compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, D2_USTR(L"Repeated line"), nCount, 7, bContinued);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B0750 (#10057)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10057, dll_base + 0x00010750);

		SUBCASE("")
		{
			// Input data
			// NOTE: The column must be smaller than the number of columns and still be empty
			const int nLine = GENERATE(0, 2, 3, 10);
			const int nColumn = GENERATE(2, 3);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 3, 4);
			setup_textbox(original_pTextBox, 3, 4);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, "Column text", nLine, nColumn);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B07C0 (#10058)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10058_0, dll_base + 0x000107C0);

		SUBCASE("")
		{
			// Input data
			const int nLine = GENERATE(0, 2, 3, 10);
			const int nColumn = GENERATE(2, 3);
			const wchar_t* wszText = GENERATE(L"", L"Column text");
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 3, 4);
			setup_textbox(original_pTextBox, 3, 4);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, D2_USTR(wszText), nLine, nColumn);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B08F0 (#10197)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10197, dll_base + 0x000108F0);

		SUBCASE("")
		{
			// Input data
			// NOTE: The line must exist, the function asserts otherwise
			const int nLineNum = GENERATE(0, 1, 3);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 4, 2);
			setup_textbox(original_pTextBox, 4, 2);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nLineNum);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B09E0 (#10052)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10052_TEXTBOX_GetNumLines, dll_base + 0x000109E0);

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 1, 7);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, nLines);
			setup_textbox(original_pTextBox, nLines);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0A30 (#10054)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10054, dll_base + 0x00010A30);

		SUBCASE("")
		{
			// Input data
			const int32_t nLine = random_unsigned_integer(0, 10);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			moo_pTextBox.nLine = nLine;
			original_pTextBox.nLine = nLine;

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0A80 (#10049)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10049, dll_base + 0x00010A80);

		SUBCASE("")
		{
			// Input data
			const int32_t nCurrentLine = GENERATE(-1, 0, 5);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			moo_pTextBox.nCurrentLine = nCurrentLine;
			original_pTextBox.nCurrentLine = nCurrentLine;

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0AD0 (#10050)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10050_TEXTBOX_SetLine, dll_base + 0x00010AD0);

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 5);
			const int nLine = GENERATE(-5, -1, 0, 3, 4, 5, 100);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, nLines);
			setup_textbox(original_pTextBox, nLines);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nLine);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0B30 (#10053)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10053, dll_base + 0x00010B30);

		SUBCASE("")
		{
			// Input data
			// NOTE: Negative lines are not tested, they would be stored without moving to a valid line
			const int32_t nLines = GENERATE(0, 5);
			const int nLine = GENERATE(0, 3, 4, 5, 100);
			const bool bWithScrollBar = GENERATE(false, true);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, nLines);
			setup_textbox(original_pTextBox, nLines);
			if (bWithScrollBar)
			{
				setup_scrollbar(moo_pScrollBar, moo_pTextBox, 3);
				setup_scrollbar(original_pScrollBar, original_pTextBox, 3);
			}

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nLine);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B0BC0 (#10055)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10055, dll_base + 0x00010BC0);

		SUBCASE("")
		{
			// Input data
			const int32_t nHeight = GENERATE(10, 100, 500);
			const int32_t nLineSpacing = GENERATE(0, 5);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			moo_pTextBox.controlHeader.nHeight = nHeight;
			original_pTextBox.controlHeader.nHeight = nHeight;
			moo_pTextBox.nLineSpacing = nLineSpacing;
			original_pTextBox.nLineSpacing = nLineSpacing;

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0C50 (#10048)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10048, dll_base + 0x00010C50);

		SUBCASE("")
		{
			// Input data
			const int32_t nCurrentLine = GENERATE(-1, 0, 2, 5);
			const int dwTextBoxFlags = GENERATE(0, 1);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 3);
			setup_textbox(original_pTextBox, 3);
			moo_pTextBox.nCurrentLine = nCurrentLine;
			original_pTextBox.nCurrentLine = nCurrentLine;
			moo_pTextBox.dwTextBoxFlags = dwTextBoxFlags;
			original_pTextBox.dwTextBoxFlags = dwTextBoxFlags;

			// Call both implementations
			const Unicode* moo_result = sut(&moo_pTextBox);
			const Unicode* original_result = original(&original_pTextBox);

			// Compare return values, which point to the lines of the respective text box
			CHECK_EQ(moo_result != nullptr, original_result != nullptr);
			if (moo_result && original_result)
			{
				CHECK(unicode_equals(moo_result, original_result));
			}

			// Compare potentially modified input data
			check_textboxes_eq(moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0CC0 (#10196)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10196, dll_base + 0x00010CC0);

		SUBCASE("")
		{
			// Input data
			// NOTE: The line must exist, the function asserts otherwise
			const int nLineNum = GENERATE(0, 2);
			const int nColumnNum = GENERATE(0, 1, 4);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 3, 2);
			setup_textbox(original_pTextBox, 3, 2);

			// Call both implementations
			const Unicode* moo_result = sut(&moo_pTextBox, nLineNum, nColumnNum);
			const Unicode* original_result = original(&original_pTextBox, nLineNum, nColumnNum);

			// Compare return values, which point to the lines of the respective text box
			CHECK_EQ(moo_result != nullptr, original_result != nullptr);
			if (moo_result && original_result)
			{
				CHECK(unicode_equals(moo_result, original_result));
			}

			// Compare potentially modified input data
			check_textboxes_eq(moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0DC0 (#10056)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10056, dll_base + 0x00010DC0);

		SUBCASE("")
		{
			// Input data
			// NOTE: The number of columns can't decrease and must be between 1 and 5
			const int nNumColumns = GENERATE(1, 2, 5);
			const int dwTextBoxFlags = GENERATE(0, 1, 0x20);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			moo_pTextBox.dwTextBoxFlags = dwTextBoxFlags;
			original_pTextBox.dwTextBoxFlags = dwTextBoxFlags;

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nNumColumns);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0E60 (#10059)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10059, dll_base + 0x00010E60);

		SUBCASE("")
		{
			// Input data
			const int nColumn = GENERATE(0, 1, 2);
			const int nOffset = random_unsigned_integer(0, 300);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 2, 3);
			setup_textbox(original_pTextBox, 2, 3);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nColumn, nOffset);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0EE0 (#10060)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10060, dll_base + 0x00010EE0);

		SUBCASE("")
		{
			// Input data
			const int nColumn = GENERATE(0, 1, 4);
			const int nFlags = GENERATE(0, 2, 0x10);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 2, 2);
			setup_textbox(original_pTextBox, 2, 2);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nColumn, nFlags);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0F60 (#10061)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10061, dll_base + 0x00010F60);

		SUBCASE("")
		{
			// Input data
			const int32_t nLines = GENERATE(0, 1, 2, 9);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, nLines);
			setup_textbox(original_pTextBox, nLines);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B0FC0 (#10187)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10187, dll_base + 0x00010FC0);

		SUBCASE("")
		{
			// Input data
			const int bSet = GENERATE(0, 1);
			const bool bWithScrollBar = GENERATE(false, true);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			if (bWithScrollBar)
			{
				setup_scrollbar(moo_pScrollBar, moo_pTextBox);
				setup_scrollbar(original_pScrollBar, original_pTextBox);
			}

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, bSet);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1030 (#10188)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10188, dll_base + 0x00011030);

		SUBCASE("")
		{
			// Input data
			// NOTE: The line must exist, the function asserts otherwise
			const int nLineNum = GENERATE(-1, 0, 3);
			const int nColor = random_unsigned_integer(0, 12);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			setup_textbox(moo_pTextBox, 4);
			setup_textbox(original_pTextBox, 4);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nLineNum, nColor);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1130")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TEXTBOX_Draw, dll_base + 0x00011130);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const int dwTextBoxFlags = GENERATE(0, 1, 2, 0x10, 0x40, 0x80);
		const int32_t nLines = GENERATE(0, 3, 20);
		const int32_t nColumns = GENERATE(1, 2);
		const int32_t nCurrentLine = GENERATE(-1, 1);
		const int32_t nScrollOffset = GENERATE(0, -20, -500);
		const bool bHasCellFile = GENERATE(false, true);
		CAPTURE(dwFlags);
		CAPTURE(dwTextBoxFlags);
		CAPTURE(nLines);
		CAPTURE(nColumns);
		CAPTURE(nCurrentLine);
		CAPTURE(nScrollOffset);
		CAPTURE(bHasCellFile);

		D2WinFakeCellFile cellFile("textbox", 1);
		D2WinTextBoxStrc moo_pTextBox{};
		D2WinTextBoxStrc original_pTextBox{};

		const auto setup_data = [&](
			D2WinTextBoxStrc& pTextBox
		) {
			setup_textbox(pTextBox, nLines, nColumns);
			pTextBox.controlHeader.dwFlags = dwFlags;
			pTextBox.controlHeader.pCellFile = bHasCellFile ? cellFile.get() : nullptr;
			pTextBox.dwTextBoxFlags = dwTextBoxFlags;
			pTextBox.nCurrentLine = nCurrentLine;
			pTextBox.nScrollOffset = nScrollOffset;
			if (nColumns > 1)
			{
				pTextBox.nColumnOffsets[1] = 150;
				pTextBox.nColumnFlags[1] = nCurrentLine == 1 ? 2 : 0x10;
			}
		};

		setup_data(moo_pTextBox);
		setup_data(original_pTextBox);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pTextBox.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pTextBox.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		check_textboxes_eq(moo_pTextBox, original_pTextBox);
		CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B15A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TEXTBOX_HandleMouseDown, dll_base + 0x000115A0);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const int dwTextBoxFlags = GENERATE(0, 1, 9);
		const int32_t nLines = GENERATE(0, 3, 30);
		const int32_t nMouseY = GENERATE(150, 205, 250, 399);
		const bool bHasCallback = GENERATE(true, false);
		CAPTURE(dwFlags);
		CAPTURE(dwTextBoxFlags);
		CAPTURE(nLines);
		CAPTURE(nMouseY);
		CAPTURE(bHasCallback);

		D2WinTextBoxStrc moo_pTextBox{};
		D2WinTextBoxStrc original_pTextBox{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinTextBoxStrc& pTextBox,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_textbox(pTextBox, nLines);
			pTextBox.controlHeader.dwFlags = dwFlags;
			pTextBox.controlHeader.pfCallback = bHasCallback ? D2WinCallbacks::Callback : nullptr;
			pTextBox.dwTextBoxFlags = dwTextBoxFlags;
			pTextBox.nLine = nLines > 10 ? 5 : 0;
			pMsg.hWindow = reinterpret_cast<HWND>(&pTextBox);
			pMsg.nMessage = WM_LBUTTONDOWN;
		};

		setup_data(moo_pTextBox, moo_pMsg);
		setup_data(original_pTextBox, original_pMsg);
		set_mouse_position(200, nMouseY);
		D2WinCallLog::name_pointer(&moo_pTextBox, "pTextBox");
		D2WinCallLog::name_pointer(&original_pTextBox, "pTextBox");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pMsg);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pMsg);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		check_textboxes_eq(moo_pTextBox, original_pTextBox);
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B16B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TEXTBOX_HandleVirtualKeyInput, dll_base + 0x000116B0);

		// Input data
		const WPARAM wParam = GENERATE(VK_PRIOR, VK_NEXT, VK_UP, VK_DOWN, VK_HOME, VK_END, VK_RETURN);
		const int32_t nLines = GENERATE(0, 5, 30);
		const int32_t nCurrentLine = GENERATE(-1, 0, 4, 12, 29);
		const int32_t nLine = GENERATE(0, 3, 19);
		const bool bWithScrollBar = GENERATE(false, true);
		const bool bActiveEditBox = GENERATE(false, true);
		CAPTURE(wParam);
		CAPTURE(nLines);
		CAPTURE(nCurrentLine);
		CAPTURE(nLine);
		CAPTURE(bWithScrollBar);
		CAPTURE(bActiveEditBox);

		if (nLine >= nLines && nLines > 0)
		{
			return;
		}

		D2WinTextBoxStrc moo_pTextBox{};
		D2WinTextBoxStrc original_pTextBox{};
		D2WinScrollBarStrc moo_pScrollBar{};
		D2WinScrollBarStrc original_pScrollBar{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		D2WinEditBoxStrc editBox{};

		const auto setup_data = [&](
			D2WinTextBoxStrc& pTextBox,
			D2WinScrollBarStrc& pScrollBar,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_textbox(pTextBox, nLines);
			pTextBox.controlHeader.pfCallback = D2WinCallbacks::Callback;
			pTextBox.dwTextBoxFlags = 1;
			pTextBox.nCurrentLine = nCurrentLine;
			pTextBox.nLine = nLine;
			for (int32_t i = 0; i < nLine && pTextBox.pCurrentLine; ++i)
			{
				pTextBox.pCurrentLine = pTextBox.pCurrentLine->pNext;
			}

			if (bWithScrollBar)
			{
				setup_scrollbar(pScrollBar, pTextBox, std::max(nLines - 11, 0));
			}

			pMsg.hWindow = reinterpret_cast<HWND>(&pTextBox);
			pMsg.nMessage = WM_KEYDOWN;
			pMsg.wParam = wParam;
		};

		setup_data(moo_pTextBox, moo_pScrollBar, moo_pMsg);
		setup_data(original_pTextBox, original_pScrollBar, original_pMsg);
		if (bActiveEditBox)
		{
			d2win_init_control(editBox.controlHeader, D2WIN_EDITBOX);
			moo_state.pActiveEditBox = &editBox;
			original_state.pActiveEditBox = &editBox;
		}

		D2WinCallLog::name_pointer(&moo_pTextBox, "pTextBox");
		D2WinCallLog::name_pointer(&original_pTextBox, "pTextBox");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pMsg);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pMsg);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		check_textboxes_eq(moo_pTextBox, original_pTextBox);
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}

	// The following functions forward to the scroll bar of the text box

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B18F0 (#10190)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10190, dll_base + 0x000118F0);

		SUBCASE("")
		{
			// Input data
			const int32_t nMaxSteps = random_unsigned_integer(0, 100);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			setup_scrollbar(moo_pScrollBar, moo_pTextBox, nMaxSteps);
			setup_scrollbar(original_pScrollBar, original_pTextBox, nMaxSteps);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1940 (#10191)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10191, dll_base + 0x00011940);

		SUBCASE("")
		{
			// Input data
			const int nMaxSteps = GENERATE(-3, 0, 15);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			setup_scrollbar(moo_pScrollBar, moo_pTextBox);
			setup_scrollbar(original_pScrollBar, original_pTextBox);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nMaxSteps);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1990 (#10192)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10192, dll_base + 0x00011990);

		SUBCASE("")
		{
			// Input data
			const int32_t nCurrentStep = random_unsigned_integer(0, 10);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			setup_scrollbar(moo_pScrollBar, moo_pTextBox);
			setup_scrollbar(original_pScrollBar, original_pTextBox);
			moo_pScrollBar.nCurrentStep = nCurrentStep;
			original_pScrollBar.nCurrentStep = nCurrentStep;

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B19E0 (#10193)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10193, dll_base + 0x000119E0);

		SUBCASE("")
		{
			// Input data
			const int nStep = GENERATE(-1, 0, 5, 10, 11);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			setup_scrollbar(moo_pScrollBar, moo_pTextBox);
			setup_scrollbar(original_pScrollBar, original_pTextBox);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nStep);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1A30 (#10194)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10194, dll_base + 0x00011A30);

		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinTextBoxStrc moo_pTargetTextBox{};
			D2WinTextBoxStrc original_pTargetTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			setup_textbox(moo_pTargetTextBox, 5);
			setup_textbox(original_pTargetTextBox, 5);
			setup_scrollbar(moo_pScrollBar, moo_pTextBox);
			setup_scrollbar(original_pScrollBar, original_pTextBox);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, GENERATE(true, false) ? &moo_pTargetTextBox : nullptr);

			// Check specific values
			CHECK_EQ(moo_pScrollBar.pTextBox == &moo_pTargetTextBox, original_pScrollBar.pTextBox == &original_pTargetTextBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1A80 (#10195)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10195, dll_base + 0x00011A80);

		SUBCASE("")
		{
			// Input data
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			setup_scrollbar(moo_pScrollBar, moo_pTextBox);
			setup_scrollbar(original_pScrollBar, original_pTextBox);
			void(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*) = GENERATE(D2WinCallbacks::VoidCallback, nullptr);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, pfCallback);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1AD0 (#10204)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10204, dll_base + 0x00011AD0);

		SUBCASE("")
		{
			// Input data
			const int nPageSize = random_unsigned_integer(0, 20);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			setup_scrollbar(moo_pScrollBar, moo_pTextBox);
			setup_scrollbar(original_pScrollBar, original_pTextBox);

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox, nPageSize);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8B1B20 (#10203)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10203_TEXTBOX, dll_base + 0x00011B20);

		SUBCASE("")
		{
			// Input data
			const int32_t nPageSize = random_unsigned_integer(0, 20);
			D2WinTextBoxStrc moo_pTextBox{};
			D2WinTextBoxStrc original_pTextBox{};
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_textbox(moo_pTextBox, 2);
			setup_textbox(original_pTextBox, 2);
			setup_scrollbar(moo_pScrollBar, moo_pTextBox);
			setup_scrollbar(original_pScrollBar, original_pTextBox);
			moo_pScrollBar.nPageSize = nPageSize;
			original_pScrollBar.nPageSize = nPageSize;

			compare_textbox_function(sut, original, moo_pTextBox, original_pTextBox);
		}
	}
}

#endif
