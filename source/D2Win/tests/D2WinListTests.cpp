#include <D2WinTestDefines.h>

#ifdef LIST_TESTS

#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cstdarg>
#include <cwchar>
#include <filesystem>
#include <string>
#include <vector>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinList.h>


// Time of the previous click on a list
extern uint32_t dword_6F8FE220;


TEST_SUITE("D2WinListTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// List at x = [100, 400], y = [100, 400]. Entries with an even index have a selection callback.
	void setup_list(D2WinListStrc& pList, int32_t nItems, int32_t nSelectedItem = -1)
	{
		d2win_init_control(pList.controlHeader, D2WIN_LIST, 100, 400, 300, 300);
		pList.eFont = D2FONT_FONT16;
		pList.nLineHeight = 16;
		pList.nLinePadding = 4;
		pList.nSelectedIndex = nSelectedItem;
		pList.nMaxVisibleItemIndex = 300 / 24 - 1;
		pList.nItemCount = nItems;

		D2WinListDataStrc* pLast = nullptr;
		for (int32_t i = 0; i < nItems; ++i)
		{
			D2WinListDataStrc* pData = d2win_calloc<D2WinListDataStrc>();
			std::swprintf(reinterpret_cast<wchar_t*>(pData->wszText), std::size(pData->wszText), L"Item %d", i);
			pData->nTextWidth = 50 + i;
			pData->pfOnSelect = i % 2 == 0 ? D2WinCallbacks::Callback2 : nullptr;
			pData->nHotkeyChar = static_cast<char>('a' + i);
			pData->nHotkeyVirtualKey = 'A' + i;
			pList.nMaxItemWidth = std::max(pList.nMaxItemWidth, pData->nTextWidth);

			if (pLast)
			{
				pLast->pNext = pData;
			}
			else
			{
				pList.pDataList = pData;
			}

			if (i == nSelectedItem)
			{
				pList.pSelectedDataEntry = pData;
			}

			pLast = pData;
		}
	}

	std::vector<std::wstring> get_items(const D2WinListStrc& pList)
	{
		std::vector<std::wstring> items;
		for (const D2WinListDataStrc* pData = pList.pDataList; pData; pData = pData->pNext)
		{
			items.emplace_back(reinterpret_cast<const wchar_t*>(pData->wszText));
		}

		return items;
	}

	int32_t get_index(const D2WinListStrc& pList, const D2WinListDataStrc* pEntry)
	{
		int32_t nIndex = 0;
		for (const D2WinListDataStrc* pData = pList.pDataList; pData; pData = pData->pNext)
		{
			if (pData == pEntry)
			{
				return nIndex;
			}

			++nIndex;
		}

		return pEntry ? -2 : -1;
	}

	// The text of the entries is compared separately, their remaining bytes are not initialized
	void check_lists_eq(D2WinListStrc& moo_pList, D2WinListStrc& original_pList)
	{
		MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		CHECK(get_items(moo_pList) == get_items(original_pList));
		CHECK_EQ(get_index(moo_pList, moo_pList.pSelectedDataEntry), get_index(original_pList, original_pList.pSelectedDataEntry));
	}


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AC270 (#10135)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_Create, dll_base + 0x0000C270);

		SUBCASE("")
		{
			// Input data
			// The fake string table returns a string made of the string index
			D2WinListItemInitStrc items[] =
			{
				{ 'A', 'a', {}, 'A', D2WinCallbacks::Callback2 },
				{ 0x2000, 'b', {}, 'B', nullptr },
				{ 'C', 'c', {}, VK_RETURN, D2WinCallbacks::Callback2 },
				{ 0, 0, {}, 0, nullptr },
			};
			const int32_t nItems = GENERATE(0, 1, 3);
			items[nItems].nStringId = 0;
			Font eFont = GENERATE(D2FONT_FONT8, D2FONT_FONT16, D2FONT_FONT30, D2FONT_FONT42);
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = random_unsigned_integer(1, 800);
			const int32_t nHeight = random_unsigned_integer(1, 600);

			// Call both implementations
			D2WinListStrc* moo_result = sut(nX, nY, nWidth, nHeight, items, &eFont);
			D2WinListStrc* original_result = original(nX, nY, nWidth, nHeight, items, &eFont);

			// Compare return values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			check_lists_eq(*moo_result, *original_result);

			// Check specific values
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &LIST_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &LIST_HandleMouseDown);
			CHECK_EQ(moo_result->controlHeader.pfHandleCharInput, &LIST_HandleCharInput);
			CHECK_EQ(moo_result->controlHeader.pfHandleVirtualKeyInput, &LIST_HandleVirtualKeyInput);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x0000C820);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x0000C9B0);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleCharInput), dll_base + 0x0000CA70);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleVirtualKeyInput), dll_base + 0x0000CAE0);
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AC490 (#10136)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_Destroy, dll_base + 0x0000C490);

		SUBCASE("")
		{
			// Input data
			const int32_t nItems = GENERATE(0, 1, 4);
			D2WinListStrc* moo_pList = d2win_calloc<D2WinListStrc>();
			D2WinListStrc* original_pList = d2win_calloc<D2WinListStrc>();
			setup_list(*moo_pList, nItems);
			setup_list(*original_pList, nItems);
			moo_state.pControlList = &moo_pList->controlHeader;
			original_state.pControlList = &original_pList->controlHeader;

			// Call both implementations
			const auto moo_result = sut(moo_pList);
			const auto original_result = original(original_pList);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// The entries have been freed, but the list still points to them
			CHECK_EQ(moo_pList->pDataList != nullptr, original_pList->pDataList != nullptr);
			moo_pList->pDataList = nullptr;
			original_pList->pDataList = nullptr;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AC4F0 (#10138)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10138, dll_base + 0x0000C4F0);

		SUBCASE("")
		{
			// Input data
			const int32_t nItems = GENERATE(0, 3);
			const char* szText = GENERATE("", "New item");
			const int bInsertFirst = GENERATE(0, 1);
			const int bSelect = GENERATE(0, 1);
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};
			setup_list(moo_pList, nItems, nItems - 1);
			setup_list(original_pList, nItems, nItems - 1);
			moo_pList.eFont = D2FONT_FONT30;
			original_pList.eFont = D2FONT_FONT30;

			// Call both implementations
			sut(&moo_pList, szText, D2WinCallbacks::Callback, 'x', 'X', bInsertFirst, bSelect);
			original(&original_pList, szText, D2WinCallbacks::Callback, 'x', 'X', bInsertFirst, bSelect);

			// Compare potentially modified input data
			check_lists_eq(moo_pList, original_pList);
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AC570 (#10137)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10137, dll_base + 0x0000C570);

		SUBCASE("")
		{
			// Input data
			const int32_t nItems = GENERATE(0, 3);
			const wchar_t* wszText = GENERATE(L"", L"New item", L"A much longer item than the others");
			const int bInsertFirst = GENERATE(0, 1);
			const int bSelect = GENERATE(0, 1);
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};
			setup_list(moo_pList, nItems, nItems - 1);
			setup_list(original_pList, nItems, nItems - 1);
			Unicode wszBuffer[256] = {};
			std::wcscpy(reinterpret_cast<wchar_t*>(wszBuffer), wszText);

			// Call both implementations
			sut(&moo_pList, wszBuffer, D2WinCallbacks::Callback, 'x', 'X', bInsertFirst, bSelect);
			original(&original_pList, wszBuffer, D2WinCallbacks::Callback, 'x', 'X', bInsertFirst, bSelect);

			// Compare potentially modified input data
			check_lists_eq(moo_pList, original_pList);
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC6D0 (#10139)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_GetSelectedDataIndex, dll_base + 0x0000C6D0);

		SUBCASE("")
		{
			// Input data
			const int32_t nSelectedItem = GENERATE(-1, 0, 3);
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};
			setup_list(moo_pList, 4, nSelectedItem);
			setup_list(original_pList, 4, nSelectedItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pList);
			const auto original_result = original(&original_pList);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			check_lists_eq(moo_pList, original_pList);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC720 (#10140)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_GetDataFromIndex, dll_base + 0x0000C720);

		SUBCASE("")
		{
			// Input data
			const int32_t nIndex = GENERATE(-1, 0, 2, 3, 4);
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};
			setup_list(moo_pList, 4);
			setup_list(original_pList, 4);

			// Call both implementations
			D2WinListDataStrc* moo_result = sut(&moo_pList, nIndex);
			D2WinListDataStrc* original_result = original(&original_pList, nIndex);

			// Compare return values
			CHECK_EQ(get_index(moo_pList, moo_result), get_index(original_pList, original_result));

			// Compare potentially modified input data
			check_lists_eq(moo_pList, original_pList);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC770 (#10141)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10141, dll_base + 0x0000C770);

		SUBCASE("")
		{
			// Input data
			const int32_t nItems = GENERATE(0, 1, 6);
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};
			setup_list(moo_pList, nItems);
			setup_list(original_pList, nItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pList);
			const auto original_result = original(&original_pList);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			check_lists_eq(moo_pList, original_pList);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC7A0" * doctest::skip("Loads the cell file from the MPQ archives and asserts that it was not loaded yet"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_LoadPentspinCellfile, dll_base + 0x0000C7A0);

		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AC800")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_UnloadPentspinCellfile, dll_base + 0x0000C800);

		// NOTE: The tests never load the pentagram cell file, so this only frees the hardware cell of a null cell file
		SUBCASE("")
		{
			// Call both implementations
			D2WinCallLog::clear();
			sut();
			const auto moo_calls = D2WinCallLog::take();
			original();
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AC820")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_Draw, dll_base + 0x0000C820);

		// Input data
		const int32_t nItems = GENERATE(0, 1, 20);
		const int32_t nSelectedItem = GENERATE(-1, 0, 5);
		const int32_t nFirstVisibleItem = GENERATE(0, 3, 25);
		const Font eFont = GENERATE(D2FONT_FONT16, D2FONT_FONT30);
		const int32_t nPentspinFrame = GENERATE(0, 7);
		CAPTURE(nItems);
		CAPTURE(nSelectedItem);
		CAPTURE(nFirstVisibleItem);
		CAPTURE(eFont);
		CAPTURE(nPentspinFrame);

		D2WinListStrc moo_pList{};
		D2WinListStrc original_pList{};

		const auto setup_data = [&](
			D2WinListStrc& pList
		) {
			setup_list(pList, nItems, nSelectedItem);
			pList.nFirstVisibleItem = nFirstVisibleItem;
			pList.eFont = eFont;
			pList.nPentspinFrame = nPentspinFrame;
		};

		setup_data(moo_pList);
		setup_data(original_pList);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pList.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pList.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		check_lists_eq(moo_pList, original_pList);
		CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AC9B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_HandleMouseDown, dll_base + 0x0000C9B0);

		// Input data
		const int32_t nSelectedItem = GENERATE(-1, 1, 2);
		const int32_t nMouseY = GENERATE(110, 130, 152, 500);
		const bool bDoubleClick = GENERATE(false, true);
		const bool bHasCallback = GENERATE(true, false);
		CAPTURE(nSelectedItem);
		CAPTURE(nMouseY);
		CAPTURE(bDoubleClick);
		CAPTURE(bHasCallback);

		D2WinListStrc moo_pList{};
		D2WinListStrc original_pList{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinListStrc& pList,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_list(pList, 4, nSelectedItem);
			pList.controlHeader.pfCallback = bHasCallback ? D2WinCallbacks::Callback : nullptr;

			// Hit boxes of the entries, as computed when drawing
			int32_t nTop = 100;
			for (D2WinListDataStrc* pData = pList.pDataList; pData; pData = pData->pNext)
			{
				pData->nLeft = 100;
				pData->nRight = 400;
				pData->nTop = nTop;
				pData->nBottom = nTop + 24;
				nTop += 24;
			}

			pMsg.hWindow = reinterpret_cast<HWND>(&pList);
			pMsg.nMessage = WM_LBUTTONDOWN;
		};

		setup_data(moo_pList, moo_pMsg);
		setup_data(original_pList, original_pMsg);
		set_mouse_position(200, nMouseY);

		// Time of the previous click, used to detect double clicks
		const uint32_t dwLastClickTickCount = GetTickCount() - (bDoubleClick ? 0 : 1000);
		dword_6F8FE220 = dwLastClickTickCount;
		original_d2win_global<uint32_t>(0x6F8FE220) = dwLastClickTickCount;

		D2WinCallLog::name_pointer(&moo_pList, "pList");
		D2WinCallLog::name_pointer(&original_pList, "pList");

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
		check_lists_eq(moo_pList, original_pList);
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8ACA70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_HandleCharInput, dll_base + 0x0000CA70);

		// Input data
		const WPARAM wParam = GENERATE('a', 'b', 'c', 'z', 0x161);
		CAPTURE(wParam);

		D2WinListStrc moo_pList{};
		D2WinListStrc original_pList{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinListStrc& pList,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_list(pList, 3, 0);
			pMsg.hWindow = reinterpret_cast<HWND>(&pList);
			pMsg.nMessage = WM_CHAR;
			pMsg.wParam = wParam;
		};

		setup_data(moo_pList, moo_pMsg);
		setup_data(original_pList, original_pMsg);
		D2WinCallLog::name_pointer(&moo_pList, "pList");
		D2WinCallLog::name_pointer(&original_pList, "pList");

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
		check_lists_eq(moo_pList, original_pList);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8ACAE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_HandleVirtualKeyInput, dll_base + 0x0000CAE0);

		// Input data
		// NOTE: VK_RETURN, VK_UP and VK_DOWN need a selected entry
		const UINT nMessage = GENERATE(WM_KEYDOWN, WM_CHAR);
		const WPARAM wParam = GENERATE(VK_RETURN, VK_UP, VK_DOWN, 'A', 'B', 'Q');
		const int32_t nItems = GENERATE(1, 3, 20);
		const int32_t nSelectedItem = GENERATE(0, 1, 2);
		const int32_t nFirstVisibleItem = GENERATE(0, 2, 10);
		CAPTURE(nMessage);
		CAPTURE(wParam);
		CAPTURE(nItems);
		CAPTURE(nSelectedItem);
		CAPTURE(nFirstVisibleItem);

		if (nSelectedItem >= nItems)
		{
			return;
		}

		D2WinListStrc moo_pList{};
		D2WinListStrc original_pList{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		D2WinEditBoxStrc focusedEditBox{};
		d2win_init_control(focusedEditBox.controlHeader, D2WIN_EDITBOX);

		const auto setup_data = [&](
			D2WinListStrc& pList,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_list(pList, nItems, nSelectedItem);
			pList.nFirstVisibleItem = nFirstVisibleItem;
			pMsg.hWindow = reinterpret_cast<HWND>(&pList);
			pMsg.nMessage = nMessage;
			pMsg.wParam = wParam;
		};

		setup_data(moo_pList, moo_pMsg);
		setup_data(original_pList, original_pMsg);
		moo_state.pFocusedEditBox = &focusedEditBox;
		original_state.pFocusedEditBox = &focusedEditBox;
		D2WinCallLog::name_pointer(&moo_pList, "pList");
		D2WinCallLog::name_pointer(&original_pList, "pList");

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
		check_lists_eq(moo_pList, original_pList);
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		CHECK_EQ(moo_state.pFocusedEditBox, original_state.pFocusedEditBox);
	}
}

#endif
