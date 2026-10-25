#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinList.h>


TEST_SUITE("D2WinListTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC270 (#10135)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_Create, dll_base + 0x0000C270);
		
		SUBCASE("")
		{
			// Input data
			Font moo_pFont{};
			Font original_pFont{};
			int nX{};
			int nY{};
			int nWidth{};
			int nHeight{};
			void* moo_pItems = nullptr;
			void* original_pItems = nullptr;

			const auto setup_data = [](
				Font& pFont
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pFont);
			setup_data(original_pFont);

			// Call both implementations
			const auto moo_result = sut(nX, nY, nWidth, nHeight, moo_pItems, &moo_pFont);
			const auto original_result = original(nX, nY, nWidth, nHeight, original_pItems, &original_pFont);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItems, original_pItems, "Comparing pItems");
			SKIP_MOO_CHECK_EQ(moo_pFont, original_pFont, "Comparing pFont");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC490 (#10136)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_Destroy, dll_base + 0x0000C490);
		
		SUBCASE("")
		{
			// Input data
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};

			const auto setup_data = [](
				D2WinListStrc& pList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList);
			setup_data(original_pList);

			// Call both implementations
			const auto moo_result = sut(&moo_pList);
			const auto original_result = original(&original_pList);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC4F0 (#10138)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10138, dll_base + 0x0000C4F0);
		
		SUBCASE("")
		{
			// Input data
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};
			char szText{};
			char nHotkeyChar{};
			int nHotkeyVirtualKey{};
			int bInsertFirst{};
			int bSelect{};

			const auto setup_data = [](
				D2WinListStrc& pList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList);
			setup_data(original_pList);

			// Call both implementations
			sut(&moo_pList, &szText, nullptr, nHotkeyChar, nHotkeyVirtualKey, bInsertFirst, bSelect);
			original(&original_pList, &szText, nullptr, nHotkeyChar, nHotkeyVirtualKey, bInsertFirst, bSelect);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC570 (#10137)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10137, dll_base + 0x0000C570);
		
		SUBCASE("")
		{
			// Input data
			D2WinListStrc moo_pList{};
			Unicode moo_wszText{};
			D2WinListStrc original_pList{};
			Unicode original_wszText{};
			char nHotkeyChar{};
			int nHotkeyVirtualKey{};
			int bInsertFirst{};
			int bSelect{};

			const auto setup_data = [](
				D2WinListStrc& pList,
				Unicode& wszText
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList, moo_wszText);
			setup_data(original_pList, original_wszText);

			// Call both implementations
			sut(&moo_pList, &moo_wszText, nullptr, nHotkeyChar, nHotkeyVirtualKey, bInsertFirst, bSelect);
			original(&original_pList, &original_wszText, nullptr, nHotkeyChar, nHotkeyVirtualKey, bInsertFirst, bSelect);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
			SKIP_MOO_CHECK_EQ(moo_wszText, original_wszText, "Comparing wszText");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC6D0 (#10139)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_GetSelectedDataIndex, dll_base + 0x0000C6D0);
		
		SUBCASE("")
		{
			// Input data
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};

			const auto setup_data = [](
				D2WinListStrc& pList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList);
			setup_data(original_pList);

			// Call both implementations
			const auto moo_result = sut(&moo_pList);
			const auto original_result = original(&original_pList);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC720 (#10140)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_GetDataFromIndex, dll_base + 0x0000C720);
		
		SUBCASE("")
		{
			// Input data
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};
			int32_t nIndex{};

			const auto setup_data = [](
				D2WinListStrc& pList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList);
			setup_data(original_pList);

			// Call both implementations
			const auto moo_result = sut(&moo_pList, nIndex);
			const auto original_result = original(&original_pList, nIndex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC770 (#10141)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10141, dll_base + 0x0000C770);
		
		SUBCASE("")
		{
			// Input data
			D2WinListStrc moo_pList{};
			D2WinListStrc original_pList{};

			const auto setup_data = [](
				D2WinListStrc& pList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList);
			setup_data(original_pList);

			// Call both implementations
			const auto moo_result = sut(&moo_pList);
			const auto original_result = original(&original_pList);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC7A0" * doctest::skip(""))
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_UnloadPentspinCellfile, dll_base + 0x0000C800);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_Draw, dll_base + 0x0000C820);
		
		SUBCASE("")
		{
			// Input data
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};

			const auto setup_data = [](
				D2WinControlStrc& pControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pControl);
			setup_data(original_pControl);

			// Call both implementations
			const auto moo_result = sut(&moo_pControl);
			const auto original_result = original(&original_pControl);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AC9B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_HandleMouseDown, dll_base + 0x0000C9B0);
		
		SUBCASE("")
		{
			// Input data
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};

			const auto setup_data = [](
				SMSGHANDLER_PARAMS& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMsg);
			setup_data(original_pMsg);

			// Call both implementations
			const auto moo_result = sut(&moo_pMsg);
			const auto original_result = original(&original_pMsg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACA70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_HandleCharInput, dll_base + 0x0000CA70);
		
		SUBCASE("")
		{
			// Input data
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};

			const auto setup_data = [](
				SMSGHANDLER_PARAMS& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMsg);
			setup_data(original_pMsg);

			// Call both implementations
			const auto moo_result = sut(&moo_pMsg);
			const auto original_result = original(&original_pMsg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ACAE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LIST_HandleVirtualKeyInput, dll_base + 0x0000CAE0);
		
		SUBCASE("")
		{
			// Input data
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};

			const auto setup_data = [](
				SMSGHANDLER_PARAMS& pMsg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMsg);
			setup_data(original_pMsg);

			// Call both implementations
			const auto moo_result = sut(&moo_pMsg);
			const auto original_result = original(&original_pMsg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}
}
