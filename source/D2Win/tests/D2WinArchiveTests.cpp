#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinArchive.h>


TEST_SUITE("D2WinArchiveTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A59C0 (#10039)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadCellFile, dll_base + 0x000059C0);
		
		SUBCASE("")
		{
			char szFile{};
			int32_t nType{};

			// Call both implementations
			const auto moo_result = sut(&szFile, nType);
			const auto original_result = original(&szFile, nType);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5A50 (#10040)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadCellFileWithFileSize, dll_base + 0x00005A50);
		
		SUBCASE("")
		{
			// Input data
			uint32_t moo_pFileSize{};
			uint32_t original_pFileSize{};
			char szFile{};
			int32_t nType{};

			const auto setup_data = [](
				uint32_t& pFileSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pFileSize);
			setup_data(original_pFileSize);

			// Call both implementations
			const auto moo_result = sut(&szFile, &moo_pFileSize, nType);
			const auto original_result = original(&szFile, &original_pFileSize, nType);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pFileSize, original_pFileSize, "Comparing pFileSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5AE0 (#10041)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_FreeCellFile, dll_base + 0x00005AE0);
		
		SUBCASE("")
		{
			// Input data
			D2CellFileStrc moo_pCellFile{};
			D2CellFileStrc original_pCellFile{};

			const auto setup_data = [](
				D2CellFileStrc& pCellFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCellFile);
			setup_data(original_pCellFile);

			// Call both implementations
			sut(&moo_pCellFile);
			original(&original_pCellFile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCellFile, original_pCellFile, "Comparing pCellFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5B00 (#10205)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_ShowInsertExpansionDiscMessage, dll_base + 0x00005B00);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5B20 (#10174)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_ShowInsertPlayDiscMessage, dll_base + 0x00005B20);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5B40 (#10183)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_ShowInsertCinematicsDisc, dll_base + 0x00005B40);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5B60 (#10037)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadArchives, dll_base + 0x00005B60);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5CB0 (#10036)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_FreeArchives, dll_base + 0x00005CB0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5DE0 (#10038)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_GetArchive, dll_base + 0x00005DE0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5DF0 (#10185)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10185, dll_base + 0x00005DF0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5E80 (#10171)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadExpansionArchives, dll_base + 0x00005E80);
		
		SUBCASE("")
		{
			// Input data
			D2ConfigStrc moo_pConfig{};
			D2ConfigStrc original_pConfig{};
			ARCHIVE_ShowMessageFunctionPtr pfShowInsertPlayDisc{};
			ARCHIVE_ShowMessageFunctionPtr pfShowInsertExpansionDisc{};
			HANDLE hFile{};

			const auto setup_data = [](
				D2ConfigStrc& pConfig
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pConfig);
			setup_data(original_pConfig);

			// Call both implementations
			const auto moo_result = sut(pfShowInsertPlayDisc, pfShowInsertExpansionDisc, hFile, &moo_pConfig);
			const auto original_result = original(pfShowInsertPlayDisc, pfShowInsertExpansionDisc, hFile, &original_pConfig);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pConfig, original_pConfig, "Comparing pConfig");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A60A0 (#10172)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadVideoArchives, dll_base + 0x000060A0);
		
		SUBCASE("")
		{
			ARCHIVE_ShowMessageFunctionPtr pfShowMessage{};
			HANDLE hFile{};
			int32_t bExpansion{};

			// Call both implementations
			const auto moo_result = sut(pfShowMessage, hFile, bExpansion);
			const auto original_result = original(pfShowMessage, hFile, bExpansion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6110 (#10173)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_UnloadExpansionArchives, dll_base + 0x00006110);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
}
