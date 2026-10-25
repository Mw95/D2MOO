#include <D2WinTestDefines.h>

#ifdef ACCOUNTLIST_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinAccountList.h>


TEST_SUITE("D2WinAccountListTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Account list at x = [100, 820], y = [100, 300]
	void setup_account_list(D2WinAccountListStrc& pAccountList, int32_t nEntries, int32_t nSelectedEntry = -1)
	{
		d2win_init_control(pAccountList.controlHeader, D2WIN_ACCOUNTLIST, 100, 300, 720, 200);
		pAccountList.eFont = D2FONT_FONT16;

		D2WinAccountListDataStrc* pLast = nullptr;
		for (int32_t i = 0; i < nEntries; ++i)
		{
			D2WinAccountListDataStrc* pData = d2win_calloc<D2WinAccountListDataStrc>();
			std::snprintf(pData->szText, sizeof(pData->szText), "Account%02d", i);
			if (pLast)
			{
				pLast->pNext = pData;
			}
			else
			{
				pAccountList.pDataList = pData;
			}

			if (i == nSelectedEntry)
			{
				pAccountList.pSelectedDataEntry = pData;
			}

			pLast = pData;
		}
	}

	std::vector<std::string> get_entries(const D2WinAccountListStrc& pAccountList)
	{
		std::vector<std::string> entries;
		for (const D2WinAccountListDataStrc* pData = pAccountList.pDataList; pData; pData = pData->pNext)
		{
			entries.emplace_back(pData->szText);
		}

		return entries;
	}

	int32_t get_selected_index(const D2WinAccountListStrc& pAccountList)
	{
		int32_t nIndex = 0;
		for (const D2WinAccountListDataStrc* pData = pAccountList.pDataList; pData; pData = pData->pNext)
		{
			if (pData == pAccountList.pSelectedDataEntry)
			{
				return nIndex;
			}

			++nIndex;
		}

		return pAccountList.pSelectedDataEntry ? -2 : -1;
	}

	// The text of the entries is compared separately, their remaining bytes are not initialized
	void check_account_lists_eq(D2WinAccountListStrc& moo_pAccountList, D2WinAccountListStrc& original_pAccountList)
	{
		MOO_CHECK_EQ(moo_pAccountList, original_pAccountList, "Comparing pAccountList");
		CHECK_EQ(get_entries(moo_pAccountList), get_entries(original_pAccountList));
		CHECK_EQ(get_selected_index(moo_pAccountList), get_selected_index(original_pAccountList));
	}


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A4E90 (#10162)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_Create, dll_base + 0x00004E90);

		SUBCASE("")
		{
			// Input data
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = random_unsigned_integer(1, 800);
			const int32_t nHeight = random_unsigned_integer(1, 600);
			const int32_t nUnused = random_unsigned_integer();
			D2WinEditBoxFontStrc font = { D2FONT_FONTEXOCET10, 7 };
			void* pFont = GENERATE(true, false) ? &font : nullptr;

			// Call both implementations
			D2WinAccountListStrc* moo_result = sut(nX, nY, nWidth, nHeight, nUnused, pFont);
			D2WinAccountListStrc* original_result = original(nX, nY, nWidth, nHeight, nUnused, pFont);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &ACCOUNTLIST_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &ACCOUNTLIST_HandleMouseDown);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x00005180);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x000052E0);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A4F70 (#10163)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_Destroy, dll_base + 0x00004F70);

		SUBCASE("")
		{
			// Input data
			const int32_t nEntries = GENERATE(0, 1, 5);
			D2WinAccountListStrc* moo_pAccountList = d2win_calloc<D2WinAccountListStrc>();
			D2WinAccountListStrc* original_pAccountList = d2win_calloc<D2WinAccountListStrc>();
			setup_account_list(*moo_pAccountList, nEntries);
			setup_account_list(*original_pAccountList, nEntries);
			moo_state.pControlList = &moo_pAccountList->controlHeader;
			original_state.pControlList = &original_pAccountList->controlHeader;

			// Call both implementations
			const auto moo_result = sut(moo_pAccountList);
			const auto original_result = original(original_pAccountList);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// The entries have been freed, but the list still points to them
			CHECK_EQ(moo_pAccountList->pDataList != nullptr, original_pAccountList->pDataList != nullptr);
			moo_pAccountList->pDataList = nullptr;
			original_pAccountList->pDataList = nullptr;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAccountList, original_pAccountList, "Comparing pAccountList");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4FC0 (#10164)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_FreeData, dll_base + 0x00004FC0);

		SUBCASE("")
		{
			// Input data
			const int32_t nEntries = GENERATE(0, 1, 5);
			D2WinAccountListStrc moo_pAccountList{};
			D2WinAccountListStrc original_pAccountList{};
			setup_account_list(moo_pAccountList, nEntries, nEntries - 1);
			setup_account_list(original_pAccountList, nEntries, nEntries - 1);
			D2WinAccountListDataStrc* moo_pDataList = moo_pAccountList.pDataList;
			D2WinAccountListDataStrc* original_pDataList = original_pAccountList.pDataList;

			// Call both implementations
			sut(&moo_pAccountList);
			original(&original_pAccountList);

			// The entries have been freed, but the list still points to them
			CHECK_EQ(moo_pAccountList.pDataList, moo_pDataList);
			CHECK_EQ(original_pAccountList.pDataList, original_pDataList);
			CHECK_EQ(moo_pAccountList.pSelectedDataEntry != nullptr, original_pAccountList.pSelectedDataEntry != nullptr);
			moo_pAccountList.pDataList = nullptr;
			original_pAccountList.pDataList = nullptr;
			moo_pAccountList.pSelectedDataEntry = nullptr;
			original_pAccountList.pSelectedDataEntry = nullptr;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAccountList, original_pAccountList, "Comparing pAccountList");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5010 (#10165)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_AllocData, dll_base + 0x00005010);

		SUBCASE("")
		{
			// Input data
			// NOTE: The text is copied with a maximum length that doesn't leave room for the terminator, longer texts are not tested
			const int32_t nEntries = GENERATE(0, 1, 3);
			const char* szText = GENERATE("", "NewAccount", "AnAccountNameWith48CharactersAAAAAAAAAAAAAAAAAAA");
			D2WinAccountListStrc moo_pAccountList{};
			D2WinAccountListStrc original_pAccountList{};
			setup_account_list(moo_pAccountList, nEntries);
			setup_account_list(original_pAccountList, nEntries);

			// Call both implementations
			sut(&moo_pAccountList, szText);
			original(&original_pAccountList, szText);

			// Compare potentially modified input data
			check_account_lists_eq(moo_pAccountList, original_pAccountList);

			// Check specific values
			REQUIRE(moo_pAccountList.pDataList != nullptr);
			CHECK_EQ(std::string(moo_pAccountList.pDataList->szText), szText);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5080 (#10166)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_RemoveEntry, dll_base + 0x00005080);

		SUBCASE("")
		{
			// Input data
			const int32_t nEntries = GENERATE(0, 1, 4);
			const int32_t nSelectedEntry = GENERATE(-1, 0, 2);
			const char* szText = GENERATE("Account00", "Account02", "Account03", "Unknown");
			D2WinAccountListStrc moo_pAccountList{};
			D2WinAccountListStrc original_pAccountList{};
			setup_account_list(moo_pAccountList, nEntries, nSelectedEntry);
			setup_account_list(original_pAccountList, nEntries, nSelectedEntry);

			// Call both implementations
			const auto moo_result = sut(&moo_pAccountList, szText);
			const auto original_result = original(&original_pAccountList, szText);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			check_account_lists_eq(moo_pAccountList, original_pAccountList);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5140 (#10167)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_GetTextFromSelectedEntry, dll_base + 0x00005140);

		SUBCASE("")
		{
			// Input data
			const int32_t nSelectedEntry = GENERATE(-1, 0, 2);
			D2WinAccountListStrc moo_pAccountList{};
			D2WinAccountListStrc original_pAccountList{};
			char moo_szBuffer[50] = "Unchanged";
			char original_szBuffer[50] = "Unchanged";
			setup_account_list(moo_pAccountList, 3, nSelectedEntry);
			setup_account_list(original_pAccountList, 3, nSelectedEntry);

			// Call both implementations
			const auto moo_result = sut(&moo_pAccountList, moo_szBuffer);
			const auto original_result = original(&original_pAccountList, original_szBuffer);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			check_account_lists_eq(moo_pAccountList, original_pAccountList);
			CHECK_EQ(std::string(moo_szBuffer), std::string(original_szBuffer));
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A5180")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_Draw, dll_base + 0x00005180);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const int32_t nEntries = GENERATE(0, 1, 30);
		const int32_t nFirstVisibleEntry = GENERATE(0, 7);
		const int32_t nSelectedEntry = GENERATE(-1, 0, 10, 29);
		CAPTURE(dwFlags);
		CAPTURE(nEntries);
		CAPTURE(nFirstVisibleEntry);
		CAPTURE(nSelectedEntry);

		D2WinAccountListStrc moo_pAccountList{};
		D2WinAccountListStrc original_pAccountList{};

		const auto setup_data = [&](
			D2WinAccountListStrc& pAccountList
		) {
			setup_account_list(pAccountList, nEntries, nSelectedEntry);
			pAccountList.controlHeader.dwFlags = dwFlags;
			pAccountList.nFirstVisibleEntry = nFirstVisibleEntry;
		};

		setup_data(moo_pAccountList);
		setup_data(original_pAccountList);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pAccountList.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pAccountList.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		check_account_lists_eq(moo_pAccountList, original_pAccountList);
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A52E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_HandleMouseDown, dll_base + 0x000052E0);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const int32_t nEntries = GENERATE(0, 1, 30);
		const int32_t nMouseX = GENERATE(100, 230, 700, 819);
		const int32_t nMouseY = GENERATE(96, 100, 125, 190, 299);
		CAPTURE(dwFlags);
		CAPTURE(nEntries);
		CAPTURE(nMouseX);
		CAPTURE(nMouseY);

		D2WinAccountListStrc moo_pAccountList{};
		D2WinAccountListStrc original_pAccountList{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinAccountListStrc& pAccountList,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_account_list(pAccountList, nEntries, nEntries > 2 ? 2 : -1);
			pAccountList.controlHeader.dwFlags = dwFlags;
			pMsg.hWindow = reinterpret_cast<HWND>(&pAccountList);
			pMsg.nMessage = WM_LBUTTONDOWN;
		};

		setup_data(moo_pAccountList, moo_pMsg);
		setup_data(original_pAccountList, original_pMsg);
		set_mouse_position(nMouseX, nMouseY);

		// Call both implementations
		const auto moo_result = sut(&moo_pMsg);
		const auto original_result = original(&original_pMsg);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		check_account_lists_eq(moo_pAccountList, original_pAccountList);
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}
}

#endif
