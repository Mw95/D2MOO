#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinSmack.h>


TEST_SUITE("D2WinSmackTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF710 (#10097)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_Create, dll_base + 0x0000F710);
		
		SUBCASE("")
		{
			int32_t nX{};
			int32_t nY{};
			int32_t nWidth{};
			int32_t nHeight{};

			// Call both implementations
			const auto moo_result = sut(nX, nY, nWidth, nHeight, nullptr);
			const auto original_result = original(nX, nY, nWidth, nHeight, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF7E0 (#10099)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_Decode, dll_base + 0x0000F7E0);
		
		SUBCASE("")
		{
			// Input data
			D2WinSmackStrc moo_pSmack{};
			D2WinSmackStrc original_pSmack{};
			char szFileName{};
			int nVersion{};
			int nUnused{};
			int nUnused2{};

			const auto setup_data = [](
				D2WinSmackStrc& pSmack
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSmack);
			setup_data(original_pSmack);

			// Call both implementations
			const auto moo_result = sut(&moo_pSmack, &szFileName, nVersion, nUnused, nUnused2);
			const auto original_result = original(&original_pSmack, &szFileName, nVersion, nUnused, nUnused2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF860 (#10101)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_DeleteFile, dll_base + 0x0000F860);
		
		SUBCASE("")
		{
			// Input data
			D2WinSmackStrc moo_pSmack{};
			D2WinSmackStrc original_pSmack{};

			const auto setup_data = [](
				D2WinSmackStrc& pSmack
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSmack);
			setup_data(original_pSmack);

			// Call both implementations
			const auto moo_result = sut(&moo_pSmack);
			const auto original_result = original(&original_pSmack);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF8B0 (#10100)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_SetCoordinates, dll_base + 0x0000F8B0);
		
		SUBCASE("")
		{
			// Input data
			D2WinSmackStrc moo_pSmack{};
			D2WinSmackStrc original_pSmack{};
			int nX{};
			int nY{};

			const auto setup_data = [](
				D2WinSmackStrc& pSmack
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSmack);
			setup_data(original_pSmack);

			// Call both implementations
			const auto moo_result = sut(&moo_pSmack, nX, nY);
			const auto original_result = original(&original_pSmack, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF900 (#10098)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_Destroy, dll_base + 0x0000F900);
		
		SUBCASE("")
		{
			// Input data
			D2WinSmackStrc moo_pSmack{};
			D2WinSmackStrc original_pSmack{};

			const auto setup_data = [](
				D2WinSmackStrc& pSmack
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSmack);
			setup_data(original_pSmack);

			// Call both implementations
			const auto moo_result = sut(&moo_pSmack);
			const auto original_result = original(&original_pSmack);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSmack, original_pSmack, "Comparing pSmack");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF950 (#10184)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10184, dll_base + 0x0000F950);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF960" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_Draw, dll_base + 0x0000F960);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFA40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SMACK_HandleMouseDown, dll_base + 0x0000FA40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AFA90 (#10208)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10208, dll_base + 0x0000FA90);
		
		SUBCASE("")
		{
			int bReducedLineSpacing{};

			// Call both implementations
			sut(bReducedLineSpacing);
			original(bReducedLineSpacing);
		}
	}
}
