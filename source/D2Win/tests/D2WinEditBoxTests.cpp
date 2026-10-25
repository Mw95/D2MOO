#include <D2WinTestDefines.h>

#ifdef EDITBOX_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cwchar>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinEditBox.h>


// Edit box clicked last and time of that click, used to detect double clicks
extern D2WinEditBoxStrc* gpLastClickedEditBox_6F8FD8B0;
extern DWORD gdwLastClickTickCount_6F8FD8B4;


// NOTE: The clipboard functions (Ctrl+C, Ctrl+X and Ctrl+V) are not tested, since they modify the clipboard of the system.
// NOTE: The tests assume that the shift key is not pressed while they run.
// NOTE: The blinking cursor is only drawn for the active edit box, which depends on GetTickCount(). The tests don't draw an active edit box.
TEST_SUITE("D2WinEditBoxTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Edit box at x = [100, 250], y = [170, 200] (or y = [100, 200] for multiline edit boxes)
	void setup_editbox(D2WinEditBoxStrc& pEditBox, const wchar_t* wszText, uint32_t dwEditBoxFlags = 0)
	{
		const bool bMultiline = dwEditBoxFlags & EDITBOX_MULTILINE;
		d2win_init_control(pEditBox.controlHeader, D2WIN_EDITBOX, 100, 200, 150, bMultiline ? 100 : 30);
		pEditBox.nTextOffsetX = 5;
		pEditBox.nTextOffsetY = 3;
		pEditBox.nMaxLength = 256;
		pEditBox.nSelectionStart = -1;
		pEditBox.dwEditBoxFlags = dwEditBoxFlags;
		pEditBox.eFont = D2FONT_FONT16;
		pEditBox.nTextColor = 2;
		pEditBox.pfOnTextChanged = D2WinCallbacks::OnTextChanged;
		std::wcscpy(reinterpret_cast<wchar_t*>(pEditBox.wszText), wszText);
		const int32_t nLength = static_cast<int32_t>(std::wcslen(wszText));
		pEditBox.nCursorPosition = nLength;
		pEditBox.nFirstVisibleChar = 0;
		pEditBox.nLastVisibleChar = nLength - 1;
	}

	struct EditBoxFixture : D2WinFixture<NoopFixture>
	{
		D2WinEditBoxStrc*& original_pLastClickedEditBox = original_d2win_global<D2WinEditBoxStrc*>(0x6F8FD8B0);
		DWORD& original_dwLastClickTickCount = original_d2win_global<DWORD>(0x6F8FD8B4);

		EditBoxFixture()
		{
			gpLastClickedEditBox_6F8FD8B0 = nullptr;
			original_pLastClickedEditBox = nullptr;
		}

		~EditBoxFixture()
		{
			gpLastClickedEditBox_6F8FD8B0 = nullptr;
			original_pLastClickedEditBox = nullptr;
		}

		// The edit boxes of both implementations are different objects, so only check whether they are the focused/active ones
		void check_focus_eq(const D2WinEditBoxStrc& moo_pEditBox, const D2WinEditBoxStrc& original_pEditBox)
		{
			CHECK_EQ(moo_state.pFocusedEditBox == &moo_pEditBox, original_state.pFocusedEditBox == &original_pEditBox);
			CHECK_EQ(moo_state.pFocusedEditBox == nullptr, original_state.pFocusedEditBox == nullptr);
			CHECK_EQ(gpLastClickedEditBox_6F8FD8B0 == &moo_pEditBox, original_pLastClickedEditBox == &original_pEditBox);
		}

		// Runs a function taking an edit box on both implementations and compares the results
		template<typename Function, typename... Args>
		void compare_editbox_function(Function* sut, Function* original, D2WinEditBoxStrc& moo_pEditBox, D2WinEditBoxStrc& original_pEditBox, Args... args)
		{
			D2WinCallLog::name_pointer(&moo_pEditBox, "pEditBox");
			D2WinCallLog::name_pointer(&original_pEditBox, "pEditBox");

			D2WinCallLog::clear();
			if constexpr (std::is_void_v<decltype(sut(&moo_pEditBox, args...))>)
			{
				sut(&moo_pEditBox, args...);
				const auto moo_calls = D2WinCallLog::take();
				original(&original_pEditBox, args...);
				const auto original_calls = D2WinCallLog::take();
				CHECK_EQ(moo_calls, original_calls);
			}
			else
			{
				const auto moo_result = sut(&moo_pEditBox, args...);
				const auto moo_calls = D2WinCallLog::take();
				const auto original_result = original(&original_pEditBox, args...);
				const auto original_calls = D2WinCallLog::take();
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(moo_calls, original_calls);
			}

			MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
			check_focus_eq(moo_pEditBox, original_pEditBox);
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		}

		// Runs a message handler on both implementations and compares the results
		template<typename Function>
		void compare_editbox_handler(Function* sut, Function* original, D2WinEditBoxStrc& moo_pEditBox, D2WinEditBoxStrc& original_pEditBox, UINT nMessage)
		{
			D2WinCallLog::name_pointer(&moo_pEditBox, "pEditBox");
			D2WinCallLog::name_pointer(&original_pEditBox, "pEditBox");

			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};
			moo_pMsg.hWindow = reinterpret_cast<HWND>(&moo_pEditBox);
			original_pMsg.hWindow = reinterpret_cast<HWND>(&original_pEditBox);
			moo_pMsg.nMessage = nMessage;
			original_pMsg.nMessage = nMessage;

			D2WinCallLog::clear();
			const auto moo_result = sut(&moo_pMsg);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(&original_pMsg);
			const auto original_calls = D2WinCallLog::take();

			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);
			MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
			MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
			check_focus_eq(moo_pEditBox, original_pEditBox);
		}
	};


	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A6C80 (#10070)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10070_EDITBOX_Create, dll_base + 0x00006C80);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("editbox", 1);
			D2WinEditBoxFontStrc font = { D2FONT_FONTFORMAL10, 4 };
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = random_unsigned_integer(1, 800);
			const int32_t nHeight = random_unsigned_integer(1, 600);
			const int32_t nTextOffsetX = random_unsigned_integer(0, 10);
			const int32_t nTextOffsetY = random_unsigned_integer(0, 10);
			const int32_t nEditBoxFlags = GENERATE(0, EDITBOX_PASSWORD, EDITBOX_MULTILINE, 0x3F);
			const D2WinEditBoxFontStrc* pFont = GENERATE(true, false) ? &font : nullptr;

			// Call both implementations
			D2WinEditBoxStrc* moo_result = sut(nX, nY, nWidth, nHeight, nTextOffsetX, nTextOffsetY, cellFile.get(), D2WinCallbacks::OnReturn, D2WinCallbacks::Callback, nEditBoxFlags, pFont);
			D2WinEditBoxStrc* original_result = original(nX, nY, nWidth, nHeight, nTextOffsetX, nTextOffsetY, cellFile.get(), D2WinCallbacks::OnReturn, D2WinCallbacks::Callback, nEditBoxFlags, pFont);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			const bool bMultiline = nEditBoxFlags & EDITBOX_MULTILINE;
			CHECK_EQ(moo_result->controlHeader.pfDraw, bMultiline ? &EDITBOX_DrawMultiline : &EDITBOX_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, bMultiline ? &EDITBOX_HandleMouseDownMultiline : &EDITBOX_HandleMouseDown);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseUp, &EDITBOX_HandleMouseUp);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + (bMultiline ? 0x000086C0 : 0x000082D0));
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + (bMultiline ? 0x000097D0 : 0x00009120));
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseUp), dll_base + 0x000093A0);
			CHECK_EQ(moo_result->controlHeader.pfHandleCharInput, original_result->controlHeader.pfHandleCharInput);
			CHECK_EQ(moo_result->controlHeader.pfHandleVirtualKeyInput, original_result->controlHeader.pfHandleVirtualKeyInput);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A6DC0 (#10071)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10071_EDITBOX_Destroy, dll_base + 0x00006DC0);

		// Input data
		const int nState = GENERATE(0, 1, 2);
		CAPTURE(nState);

		D2WinEditBoxStrc* moo_pEditBox = d2win_calloc<D2WinEditBoxStrc>();
		D2WinEditBoxStrc* original_pEditBox = d2win_calloc<D2WinEditBoxStrc>();
		setup_editbox(*moo_pEditBox, L"Text");
		setup_editbox(*original_pEditBox, L"Text");
		moo_state.pControlList = &moo_pEditBox->controlHeader;
		original_state.pControlList = &original_pEditBox->controlHeader;

		// The focused and active edit boxes are reset when they are destroyed
		if (nState >= 1)
		{
			moo_state.pFocusedEditBox = moo_pEditBox;
			original_state.pFocusedEditBox = original_pEditBox;
		}

		if (nState >= 2)
		{
			moo_state.pActiveEditBox = moo_pEditBox;
			original_state.pActiveEditBox = original_pEditBox;
		}

		compare_editbox_function(sut, original, *moo_pEditBox, *original_pEditBox);
		MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
		MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		CHECK_EQ(moo_state.pActiveEditBox == nullptr, original_state.pActiveEditBox == nullptr);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A6E10 (#10072)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10072, dll_base + 0x00006E10);

		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, L"Text");
			setup_editbox(original_pEditBox, L"Text");
			const EditBoxCharFilterFunc pfCharFilter = GENERATE(D2WinCallbacks::CharFilter, D2Win_10078_IsNumber, nullptr);

			compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox, pfCharFilter);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A6E60 (#10073)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10073, dll_base + 0x00006E60);

		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, L"Text");
			setup_editbox(original_pEditBox, L"Text");
			const EditBoxTextChangedFunc pfOnTextChanged = GENERATE(D2WinCallbacks::OnTextChanged, nullptr);

			compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox, pfOnTextChanged);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A6EB0 (#10083)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10083, dll_base + 0x00006EB0);

		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, L"Some text");
			setup_editbox(original_pEditBox, L"Some text");
			moo_pEditBox.nSelectionStart = 2;
			original_pEditBox.nSelectionStart = 2;
			moo_pEditBox.nSelectionEnd = 6;
			original_pEditBox.nSelectionEnd = 6;

			compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A6F10 (#10082)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10082, dll_base + 0x00006F10);

		SUBCASE("")
		{
			// Input data
			const wchar_t* wszText = GENERATE(L"", L"Some text");
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, wszText);
			setup_editbox(original_pEditBox, wszText);

			compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A6F70 (#10074)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10074, dll_base + 0x00006F70);

		// Input data
		// Ctrl+A (1), tabulation, carriage return, 14, printable characters and the color code character
		const uint8_t nChar = GENERATE(1, '\t', '\r', 14, 'a', '5', ' ', 0xE9, 0xFF, 0x7F);
		const uint32_t dwEditBoxFlags = GENERATE(0u, 4u | 0x10u | 0x20u, EDITBOX_MULTILINE, EDITBOX_PASSWORD);
		const wchar_t* wszText = GENERATE(L"", L"Some text", L"A long text which doesn't fit in the edit box");
		const int nSelection = GENERATE(0, 1, 2);
		const int nFilter = GENERATE(0, 1, 2);
		const int32_t nMaxLength = GENERATE(256, 10);
		const uint32_t dwFlags = GENERATE(5u, 1u);
		CAPTURE(static_cast<int>(nChar));
		CAPTURE(dwEditBoxFlags);
		CAPTURE(nSelection);
		CAPTURE(nFilter);
		CAPTURE(nMaxLength);
		CAPTURE(dwFlags);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};

		const auto setup_data = [&](
			D2WinEditBoxStrc& pEditBox
		) {
			setup_editbox(pEditBox, wszText, dwEditBoxFlags);
			pEditBox.controlHeader.dwFlags = dwFlags;
			pEditBox.nMaxLength = nMaxLength;
			pEditBox.nCursorPosition = std::min<int32_t>(3, static_cast<int32_t>(std::wcslen(wszText)));
			if (nSelection == 1)
			{
				pEditBox.nSelectionStart = 0;
				pEditBox.nSelectionEnd = pEditBox.nCursorPosition;
			}
			else if (nSelection == 2)
			{
				// Empty selection
				pEditBox.nSelectionStart = pEditBox.nCursorPosition;
				pEditBox.nSelectionEnd = pEditBox.nCursorPosition;
			}

			pEditBox.pfCharFilter = nFilter ? D2WinCallbacks::CharFilter : nullptr;
		};

		setup_data(moo_pEditBox);
		setup_data(original_pEditBox);
		D2WinCallbacks::bCharFilterResult = nFilter != 2;
		D2WinCallbacks::nCharFilterReplacement = nFilter == 1 ? 'X' : 0;

		compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox, nChar);
		CHECK_EQ(moo_state.nRemovedControlsLocked, original_state.nRemovedControlsLocked);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A7970")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_DeleteSelection, dll_base + 0x00007970);

		SUBCASE("")
		{
			// Input data
			const int32_t nSelectionStart = GENERATE(0, 2, 9);
			const int32_t nSelectionEnd = GENERATE(0, 4, 9);
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, L"Some text");
			setup_editbox(original_pEditBox, L"Some text");
			moo_pEditBox.nSelectionStart = nSelectionStart;
			original_pEditBox.nSelectionStart = nSelectionStart;
			moo_pEditBox.nSelectionEnd = nSelectionEnd;
			original_pEditBox.nSelectionEnd = nSelectionEnd;

			compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A7AB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleVirtualKey, dll_base + 0x00007AB0);

		// Input data
		const char nVirtualKey = GENERATE(VK_BACK, VK_DELETE, VK_END, VK_HOME, VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN, VK_RETURN, VK_ESCAPE, VK_F1, 'A');
		const uint32_t dwEditBoxFlags = GENERATE(0u, 2u, EDITBOX_MULTILINE);
		const wchar_t* wszText = GENERATE(L"", L"Some text", L"First line\r\nSecond line");
		const int32_t nCursorPosition = GENERATE(0, 3, 100);
		const bool bSelection = GENERATE(false, true);
		const int nFilter = GENERATE(0, 1, 2);
		const uint32_t dwFlags = GENERATE(5u, 1u);
		CAPTURE(static_cast<int>(nVirtualKey));
		CAPTURE(dwEditBoxFlags);
		CAPTURE(nCursorPosition);
		CAPTURE(bSelection);
		CAPTURE(nFilter);
		CAPTURE(dwFlags);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};

		const auto setup_data = [&](
			D2WinEditBoxStrc& pEditBox
		) {
			setup_editbox(pEditBox, wszText, dwEditBoxFlags);
			pEditBox.controlHeader.dwFlags = dwFlags;
			pEditBox.nCursorPosition = std::min<int32_t>(nCursorPosition, static_cast<int32_t>(std::wcslen(wszText)));
			pEditBox.pfOnReturn = D2WinCallbacks::OnReturn;
			pEditBox.pfCharFilter = nFilter ? D2WinCallbacks::CharFilter : nullptr;
			if (bSelection)
			{
				pEditBox.nSelectionStart = 1;
				pEditBox.nSelectionEnd = std::min<int32_t>(5, static_cast<int32_t>(std::wcslen(wszText)));
			}
		};

		setup_data(moo_pEditBox);
		setup_data(original_pEditBox);
		D2WinCallbacks::bCharFilterResult = nFilter != 2;

		compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox, nVirtualKey);
		CHECK_EQ(moo_state.nRemovedControlsLocked, original_state.nRemovedControlsLocked);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A7AB0 - Tabulation")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleVirtualKey, dll_base + 0x00007AB0);

		// Input data
		// The next edit box is disabled, the tabulation skips to the following one
		const bool bHasNext = GENERATE(false, true);
		const uint32_t dwNextFlags = GENERATE(5u, 1u);
		CAPTURE(bHasNext);
		CAPTURE(dwNextFlags);

		D2WinEditBoxStrc moo_pEditBoxes[3]{};
		D2WinEditBoxStrc original_pEditBoxes[3]{};
		for (D2WinEditBoxStrc* pEditBoxes : { moo_pEditBoxes, original_pEditBoxes })
		{
			for (int i = 0; i < 3; ++i)
			{
				setup_editbox(pEditBoxes[i], i == 2 ? L"Last" : L"Text");
				pEditBoxes[i].pNext = bHasNext && i < 2 ? &pEditBoxes[i + 1] : nullptr;
				pEditBoxes[i].pPrevious = i > 0 ? &pEditBoxes[i - 1] : nullptr;
			}

			pEditBoxes[1].controlHeader.dwFlags = dwNextFlags;
		}

		compare_editbox_function(sut, original, moo_pEditBoxes[0], original_pEditBoxes[0], static_cast<char>(VK_TAB));
		for (int i = 1; i < 3; ++i)
		{
			MOO_CHECK_EQ(moo_pEditBoxes[i], original_pEditBoxes[i], "Comparing next edit boxes");
			CHECK_EQ(moo_state.pFocusedEditBox == &moo_pEditBoxes[i], original_state.pFocusedEditBox == &original_pEditBoxes[i]);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A80A0 (#10081)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10081, dll_base + 0x000080A0);

		SUBCASE("")
		{
			// Input data
			const int32_t nMaxLength = GENERATE(0, 16, 256);
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, L"Text");
			setup_editbox(original_pEditBox, L"Text");

			compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox, nMaxLength);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A80F0 (#10076)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10076, dll_base + 0x000080F0);

		SUBCASE("")
		{
			// Input data
			const char* szText = GENERATE("", "New text", "A long text which doesn't fit in the edit box at all");
			const uint32_t dwEditBoxFlags = GENERATE(0u, EDITBOX_PASSWORD);
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, L"Previous text", dwEditBoxFlags);
			setup_editbox(original_pEditBox, L"Previous text", dwEditBoxFlags);

			compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox, szText);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A8140 (#10075)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10075, dll_base + 0x00008140);

		SUBCASE("")
		{
			// Input data
			const wchar_t* wszText = GENERATE(L"", L"New text", L"A long text which doesn't fit in the edit box at all");
			const uint32_t dwEditBoxFlags = GENERATE(0u, EDITBOX_PASSWORD);
			const bool bHasCallback = GENERATE(true, false);
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, L"Previous text", dwEditBoxFlags);
			setup_editbox(original_pEditBox, L"Previous text", dwEditBoxFlags);
			if (!bHasCallback)
			{
				moo_pEditBox.pfOnTextChanged = nullptr;
				original_pEditBox.pfOnTextChanged = nullptr;
			}

			compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox, D2_USTR(wszText));
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A81E0 (#10077)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10077_EDITBOX_GetText, dll_base + 0x000081E0);

		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			setup_editbox(moo_pEditBox, L"Text");
			setup_editbox(original_pEditBox, L"Text");

			// Call both implementations
			const Unicode* moo_result = sut(&moo_pEditBox);
			const Unicode* original_result = original(&original_pEditBox);

			// Compare return values, which point into the respective edit box
			CHECK_EQ(moo_result, moo_pEditBox.wszText);
			CHECK_EQ(original_result, original_pEditBox.wszText);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A8230 (#10080)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10080_EDITBOX_SetNextEditBox, dll_base + 0x00008230);

		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc moo_pEditBox{};
			D2WinEditBoxStrc original_pEditBox{};
			D2WinEditBoxStrc moo_pNext{};
			D2WinEditBoxStrc original_pNext{};
			setup_editbox(moo_pEditBox, L"First");
			setup_editbox(original_pEditBox, L"First");
			setup_editbox(moo_pNext, L"Second");
			setup_editbox(original_pNext, L"Second");

			// Call both implementations
			sut(&moo_pEditBox, &moo_pNext);
			original(&original_pEditBox, &original_pNext);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
			MOO_CHECK_EQ(moo_pNext, original_pNext, "Comparing pNext");
			CHECK_EQ(moo_pEditBox.pNext, &moo_pNext);
			CHECK_EQ(moo_pNext.pPrevious, &moo_pEditBox);
			CHECK_EQ(original_pEditBox.pNext, &original_pNext);
			CHECK_EQ(original_pNext.pPrevious, &original_pEditBox);
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A82D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_Draw, dll_base + 0x000082D0);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 1u);
		const uint32_t dwEditBoxFlags = GENERATE(0u, EDITBOX_PASSWORD);
		const wchar_t* wszText = GENERATE(L"", L"Some text", L"A long text which doesn't fit in the edit box");
		const int nSelection = GENERATE(0, 1, 2);
		const int32_t nFirstVisibleChar = GENERATE(0, 3);
		const bool bHasCellFile = GENERATE(false, true);
		CAPTURE(dwFlags);
		CAPTURE(dwEditBoxFlags);
		CAPTURE(nSelection);
		CAPTURE(nFirstVisibleChar);
		CAPTURE(bHasCellFile);

		D2WinFakeCellFile cellFile("editbox", 1);
		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};

		const auto setup_data = [&](
			D2WinEditBoxStrc& pEditBox
		) {
			setup_editbox(pEditBox, wszText, dwEditBoxFlags);
			const int32_t nLength = static_cast<int32_t>(std::wcslen(wszText));
			pEditBox.controlHeader.dwFlags = dwFlags;
			pEditBox.controlHeader.pCellFile = bHasCellFile ? cellFile.get() : nullptr;
			pEditBox.nFirstVisibleChar = std::min(nFirstVisibleChar, nLength);
			pEditBox.nLastVisibleChar = std::max(std::min(nLength - 1, 20), pEditBox.nFirstVisibleChar);
			if (nSelection == 1)
			{
				pEditBox.nSelectionStart = std::min(nLength, 2);
				pEditBox.nSelectionEnd = std::min(nLength, 6);
			}
			else if (nSelection == 2)
			{
				pEditBox.nSelectionStart = std::min(nLength, 7);
				pEditBox.nSelectionEnd = 0;
			}

			// The mouse button is not pressed, so the mouse selection stops
			pEditBox.bMouseSelecting = 1;
		};

		setup_data(moo_pEditBox);
		setup_data(original_pEditBox);

		compare_editbox_function(reinterpret_cast<int32_t(__fastcall*)(D2WinEditBoxStrc*)>(sut), reinterpret_cast<int32_t(__fastcall*)(D2WinEditBoxStrc*)>(original), moo_pEditBox, original_pEditBox);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A86C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_DrawMultiline, dll_base + 0x000086C0);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 1u);
		const wchar_t* wszText = GENERATE(L"", L"Some text", L"First line\r\nSecond line\r\n\r\nFourth line", L"A long line that has to be wrapped since it doesn't fit\rAnother line");
		const int nSelection = GENERATE(0, 1, 2);
		const int32_t nHeight = GENERATE(20, 100);
		CAPTURE(dwFlags);
		CAPTURE(nSelection);
		CAPTURE(nHeight);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};

		const auto setup_data = [&](
			D2WinEditBoxStrc& pEditBox
		) {
			setup_editbox(pEditBox, wszText, EDITBOX_MULTILINE);
			const int32_t nLength = static_cast<int32_t>(std::wcslen(wszText));
			pEditBox.controlHeader.dwFlags = dwFlags;
			pEditBox.controlHeader.nHeight = nHeight;
			if (nSelection == 1)
			{
				pEditBox.nSelectionStart = std::min(nLength, 2);
				pEditBox.nSelectionEnd = std::min(nLength, 25);
			}
			else if (nSelection == 2)
			{
				pEditBox.nSelectionStart = nLength;
				pEditBox.nSelectionEnd = std::min(nLength, 12);
			}

			pEditBox.bMouseSelecting = 1;
		};

		setup_data(moo_pEditBox);
		setup_data(original_pEditBox);

		compare_editbox_function(reinterpret_cast<int32_t(__fastcall*)(D2WinEditBoxStrc*)>(sut), reinterpret_cast<int32_t(__fastcall*)(D2WinEditBoxStrc*)>(original), moo_pEditBox, original_pEditBox);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A8D60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_GetCursorOffset, dll_base + 0x00008D60);

		// Input data
		const wchar_t* wszText = GENERATE(L"", L"Some text", L"First line\r\nSecond line\r\n\r\nFourth line", L"A long line that has to be wrapped since it doesn't fit\rAnother line");
		const int32_t nCursorPosition = GENERATE(0, 5, 11, 12, 26, 60);
		const int32_t nHeight = GENERATE(20, 100);
		CAPTURE(nCursorPosition);
		CAPTURE(nHeight);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};

		const auto setup_data = [&](
			D2WinEditBoxStrc& pEditBox
		) {
			setup_editbox(pEditBox, wszText, EDITBOX_MULTILINE);
			pEditBox.controlHeader.nHeight = nHeight;
			pEditBox.nCursorPosition = std::min<int32_t>(nCursorPosition, static_cast<int32_t>(std::wcslen(wszText)));
		};

		setup_data(moo_pEditBox);
		setup_data(original_pEditBox);

		int32_t moo_pX = 1234;
		int32_t moo_pY = 1234;
		int32_t original_pX = 1234;
		int32_t original_pY = 1234;

		// Call both implementations
		sut(&moo_pEditBox, &moo_pX, &moo_pY);
		original(&original_pEditBox, &original_pX, &original_pY);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		CHECK_EQ(moo_pX, original_pX);
		CHECK_EQ(moo_pY, original_pY);
		CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A9120")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleMouseDown, dll_base + 0x00009120);

		// Input data
		const UINT nMessage = GENERATE(WM_LBUTTONDOWN, WM_RBUTTONDOWN);
		const uint32_t dwFlags = GENERATE(5u, 1u);
		const wchar_t* wszText = GENERATE(L"", L"Some text", L"A long text which doesn't fit in the edit box");
		const int32_t nMouseX = GENERATE(90, 100, 110, 140, 249, 260);
		const int32_t nMouseY = GENERATE(160, 185, 205);
		const int nClickState = GENERATE(0, 1, 2);
		const bool bHasCallback = GENERATE(true, false);
		CAPTURE(nMessage);
		CAPTURE(dwFlags);
		CAPTURE(nMouseX);
		CAPTURE(nMouseY);
		CAPTURE(nClickState);
		CAPTURE(bHasCallback);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};

		const auto setup_data = [&](
			D2WinEditBoxStrc& pEditBox
		) {
			setup_editbox(pEditBox, wszText);
			const int32_t nLength = static_cast<int32_t>(std::wcslen(wszText));
			pEditBox.controlHeader.dwFlags = dwFlags;
			pEditBox.controlHeader.pfCallback = bHasCallback ? D2WinCallbacks::Callback : nullptr;
			pEditBox.nCursorPosition = std::min(nLength, 4);
			pEditBox.nLastVisibleChar = std::min(nLength - 1, 20);
			// 1: Second click on the same edit box (double click), 2: Click while selecting with the mouse
			pEditBox.bMouseSelecting = nClickState == 2;
		};

		setup_data(moo_pEditBox);
		setup_data(original_pEditBox);
		set_mouse_position(nMouseX, nMouseY);
		if (nClickState == 1)
		{
			gpLastClickedEditBox_6F8FD8B0 = &moo_pEditBox;
			original_pLastClickedEditBox = &original_pEditBox;
			gdwLastClickTickCount_6F8FD8B4 = GetTickCount();
			original_dwLastClickTickCount = gdwLastClickTickCount_6F8FD8B4;
		}

		compare_editbox_handler(sut, original, moo_pEditBox, original_pEditBox, nMessage);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A93A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleMouseUp, dll_base + 0x000093A0);

		// Input data
		const int32_t bMouseSelecting = GENERATE(0, 1);
		CAPTURE(bMouseSelecting);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};
		setup_editbox(moo_pEditBox, L"Text");
		setup_editbox(original_pEditBox, L"Text");
		moo_pEditBox.bMouseSelecting = bMouseSelecting;
		original_pEditBox.bMouseSelecting = bMouseSelecting;

		compare_editbox_handler(sut, original, moo_pEditBox, original_pEditBox, WM_LBUTTONUP);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A9410")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_SetCursorFromOffset, dll_base + 0x00009410);

		// Input data
		const UINT nMessage = GENERATE(0u, static_cast<UINT>(WM_LBUTTONDOWN));
		const uint32_t dwFlags = GENERATE(5u, 1u);
		const wchar_t* wszText = GENERATE(L"", L"Some text", L"First line\r\nSecond line\r\n\r\nFourth line", L"A long line that has to be wrapped since it doesn't fit\rAnother line");
		const int32_t nX = GENERATE(-10, 0, 30, 149, 200);
		const int32_t nY = GENERATE(-10, 0, 13, 30, 50, 120);
		const int32_t bMouseSelecting = GENERATE(0, 1);
		CAPTURE(nMessage);
		CAPTURE(dwFlags);
		CAPTURE(nX);
		CAPTURE(nY);
		CAPTURE(bMouseSelecting);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinEditBoxStrc& pEditBox,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_editbox(pEditBox, wszText, EDITBOX_MULTILINE);
			pEditBox.controlHeader.dwFlags = dwFlags;
			pEditBox.controlHeader.pfCallback = D2WinCallbacks::Callback;
			pEditBox.bMouseSelecting = bMouseSelecting;
			pEditBox.nCursorPosition = 2;
			pMsg.hWindow = reinterpret_cast<HWND>(&pEditBox);
			pMsg.nMessage = nMessage;
		};

		setup_data(moo_pEditBox, moo_pMsg);
		setup_data(original_pEditBox, original_pMsg);
		D2WinCallLog::name_pointer(&moo_pEditBox, "pEditBox");
		D2WinCallLog::name_pointer(&original_pEditBox, "pEditBox");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pMsg, nX, nY);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pMsg, nX, nY);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		check_focus_eq(moo_pEditBox, original_pEditBox);
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A97D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_HandleMouseDownMultiline, dll_base + 0x000097D0);

		// Input data
		const int32_t nMouseX = GENERATE(90, 105, 140, 249);
		const int32_t nMouseY = GENERATE(95, 103, 120, 150, 199);
		CAPTURE(nMouseX);
		CAPTURE(nMouseY);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};
		setup_editbox(moo_pEditBox, L"First line\r\nSecond line\r\nThird line", EDITBOX_MULTILINE);
		setup_editbox(original_pEditBox, L"First line\r\nSecond line\r\nThird line", EDITBOX_MULTILINE);
		set_mouse_position(nMouseX, nMouseY);

		compare_editbox_handler(sut, original, moo_pEditBox, original_pEditBox, WM_LBUTTONDOWN);
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9850 (#10078)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10078_IsNumber, dll_base + 0x00009850);

		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc pEditBox{};
			for (int nChar = -128; nChar < 128; ++nChar)
			{
				char moo_szChar = static_cast<char>(nChar);
				char original_szChar = static_cast<char>(nChar);

				// Call both implementations
				const auto moo_result = sut(&pEditBox, 0, &moo_szChar);
				const auto original_result = original(&pEditBox, 0, &original_szChar);

				// Compare return values
				CAPTURE(nChar);
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				CHECK_EQ(moo_szChar, original_szChar);
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A9870 (#10079)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10079_IsLetter, dll_base + 0x00009870);

		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc pEditBox{};
			for (int nChar = -128; nChar < 128; ++nChar)
			{
				char moo_szChar = static_cast<char>(nChar);
				char original_szChar = static_cast<char>(nChar);

				// Call both implementations
				const auto moo_result = sut(&pEditBox, 0, &moo_szChar);
				const auto original_result = original(&pEditBox, 0, &original_szChar);

				// Compare return values
				CAPTURE(nChar);
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				CHECK_EQ(moo_szChar, original_szChar);
			}
		}
	}

	TEST_CASE_FIXTURE(EditBoxFixture, "D2Win.0x6F8A98A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EDITBOX_UpdateVisibleRange, dll_base + 0x000098A0);

		// Input data
		const wchar_t* wszText = GENERATE(L"", L"Some text", L"A long text which doesn't fit in the edit box", L"A very long text which really doesn't fit in the edit box at all, not even close");
		const uint32_t dwEditBoxFlags = GENERATE(0u, EDITBOX_PASSWORD);
		const int32_t nCursorPosition = GENERATE(0, 1, 10, 30, 1000);
		const int32_t nFirstVisibleChar = GENERATE(0, 8, 25);
		const int32_t nLastVisibleChar = GENERATE(5, 20, 40);
		CAPTURE(dwEditBoxFlags);
		CAPTURE(nCursorPosition);
		CAPTURE(nFirstVisibleChar);
		CAPTURE(nLastVisibleChar);

		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};

		const auto setup_data = [&](
			D2WinEditBoxStrc& pEditBox
		) {
			setup_editbox(pEditBox, wszText, dwEditBoxFlags);
			const int32_t nLength = static_cast<int32_t>(std::wcslen(wszText));
			pEditBox.nCursorPosition = std::min(nCursorPosition, nLength);
			pEditBox.nFirstVisibleChar = std::min(nFirstVisibleChar, std::max(nLength - 1, 0));
			pEditBox.nLastVisibleChar = std::min(nLastVisibleChar, std::max(nLength - 1, 0));
		};

		setup_data(moo_pEditBox);
		setup_data(original_pEditBox);

		compare_editbox_function(sut, original, moo_pEditBox, original_pEditBox);
	}
}

#endif
