#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinAccountList.h>


TEST_SUITE("D2WinAccountListTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4E90 (#10162)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_Create, dll_base + 0x00004E90);
		
		SUBCASE("")
		{
			int32_t nX{};
			int32_t nY{};
			int32_t nWidth{};
			int32_t nHeight{};
			int32_t nUnused{};
			void* moo_pFont = nullptr;
			void* original_pFont = nullptr;

			// Call both implementations
			const auto moo_result = sut(nX, nY, nWidth, nHeight, nUnused, moo_pFont);
			const auto original_result = original(nX, nY, nWidth, nHeight, nUnused, original_pFont);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pFont, original_pFont, "Comparing pFont");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4F70 (#10163)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_Destroy, dll_base + 0x00004F70);
		
		SUBCASE("")
		{
			// Input data
			D2WinAccountListStrc moo_pAccountList{};
			D2WinAccountListStrc original_pAccountList{};

			const auto setup_data = [](
				D2WinAccountListStrc& pAccountList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAccountList);
			setup_data(original_pAccountList);

			// Call both implementations
			const auto moo_result = sut(&moo_pAccountList);
			const auto original_result = original(&original_pAccountList);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAccountList, original_pAccountList, "Comparing pAccountList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4FC0 (#10164)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_FreeData, dll_base + 0x00004FC0);
		
		SUBCASE("")
		{
			// Input data
			D2WinAccountListStrc moo_pAccountList{};
			D2WinAccountListStrc original_pAccountList{};

			const auto setup_data = [](
				D2WinAccountListStrc& pAccountList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAccountList);
			setup_data(original_pAccountList);

			// Call both implementations
			sut(&moo_pAccountList);
			original(&original_pAccountList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAccountList, original_pAccountList, "Comparing pAccountList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5010 (#10165)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_AllocData, dll_base + 0x00005010);
		
		SUBCASE("")
		{
			// Input data
			D2WinAccountListStrc moo_pAccountList{};
			D2WinAccountListStrc original_pAccountList{};
			char szText{};

			const auto setup_data = [](
				D2WinAccountListStrc& pAccountList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAccountList);
			setup_data(original_pAccountList);

			// Call both implementations
			sut(&moo_pAccountList, &szText);
			original(&original_pAccountList, &szText);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAccountList, original_pAccountList, "Comparing pAccountList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5080 (#10166)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_RemoveEntry, dll_base + 0x00005080);
		
		SUBCASE("")
		{
			// Input data
			D2WinAccountListStrc moo_pAccountList{};
			D2WinAccountListStrc original_pAccountList{};
			char szText{};

			const auto setup_data = [](
				D2WinAccountListStrc& pAccountList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAccountList);
			setup_data(original_pAccountList);

			// Call both implementations
			const auto moo_result = sut(&moo_pAccountList, &szText);
			const auto original_result = original(&original_pAccountList, &szText);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAccountList, original_pAccountList, "Comparing pAccountList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5140 (#10167)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_GetTextFromSelectedEntry, dll_base + 0x00005140);
		
		SUBCASE("")
		{
			// Input data
			D2WinAccountListStrc moo_pAccountList{};
			char moo_szBuffer{};
			D2WinAccountListStrc original_pAccountList{};
			char original_szBuffer{};

			const auto setup_data = [](
				D2WinAccountListStrc& pAccountList,
				char& szBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAccountList, moo_szBuffer);
			setup_data(original_pAccountList, original_szBuffer);

			// Call both implementations
			const auto moo_result = sut(&moo_pAccountList, &moo_szBuffer);
			const auto original_result = original(&original_pAccountList, &original_szBuffer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAccountList, original_pAccountList, "Comparing pAccountList");
			SKIP_MOO_CHECK_EQ(moo_szBuffer, original_szBuffer, "Comparing szBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5180" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_Draw, dll_base + 0x00005180);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A52E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACCOUNTLIST_HandleMouseDown, dll_base + 0x000052E0);
		
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
