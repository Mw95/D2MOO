#include <D2WinTestDefines.h>

#ifdef ARCHIVE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinArchive.h>


TEST_SUITE("D2WinArchiveTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A59C0 (#10039)" * doctest::skip("Needs MPQ archives to load the cell file from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadCellFile, dll_base + 0x000059C0);

		SUBCASE("")
		{
			const char* szFile = "DATA\\GLOBAL\\UI\\CURSOR\\Pentspin";
			int32_t nType = 0;

			// Call both implementations
			const auto moo_result = sut(szFile, nType);
			const auto original_result = original(szFile, nType);

			// Compare return values
			CHECK_EQ(moo_result != nullptr, original_result != nullptr);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5A50 (#10040)" * doctest::skip("Needs MPQ archives to load the cell file from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadCellFileWithFileSize, dll_base + 0x00005A50);

		SUBCASE("")
		{
			const char* szFile = "DATA\\GLOBAL\\UI\\CURSOR\\Pentspin";
			uint32_t moo_pFileSize{};
			uint32_t original_pFileSize{};
			int32_t nType = 0;

			// Call both implementations
			const auto moo_result = sut(szFile, &moo_pFileSize, nType);
			const auto original_result = original(szFile, &original_pFileSize, nType);

			// Compare return values
			CHECK_EQ(moo_result != nullptr, original_result != nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pFileSize, original_pFileSize, "Comparing pFileSize");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A5AE0 (#10041)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_FreeCellFile, dll_base + 0x00005AE0);

		SUBCASE("Null cell file")
		{
			// Call both implementations
			D2WinCallLog::clear();
			sut(nullptr);
			const auto moo_calls = D2WinCallLog::take();
			original(nullptr);
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);
		}

		SUBCASE("Allocated cell file")
		{
			// The cell file is freed with Fog.dll, its content doesn't matter since D2CMP is mocked
			D2CellFileStrc* moo_pCellFile = static_cast<D2CellFileStrc*>(D2_ALLOC(64));
			D2CellFileStrc* original_pCellFile = static_cast<D2CellFileStrc*>(D2_ALLOC(64));
			D2WinCallLog::name_pointer(moo_pCellFile, "pCellFile");
			D2WinCallLog::name_pointer(original_pCellFile, "pCellFile");

			// Call both implementations
			D2WinCallLog::clear();
			sut(moo_pCellFile);
			const auto moo_calls = D2WinCallLog::take();
			original(original_pCellFile);
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5B00 (#10205)" * doctest::skip("Shows a message box waiting for user input"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_ShowInsertExpansionDiscMessage, dll_base + 0x00005B00);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5B20 (#10174)" * doctest::skip("Shows a message box waiting for user input"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_ShowInsertPlayDiscMessage, dll_base + 0x00005B20);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5B40 (#10183)" * doctest::skip("Shows a message box waiting for user input"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_ShowInsertCinematicsDisc, dll_base + 0x00005B40);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5B60 (#10037)" * doctest::skip("Needs the MPQ archives"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadArchives, dll_base + 0x00005B60);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5CB0 (#10036)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_FreeArchives, dll_base + 0x00005CB0);

		// NOTE: The tests never load the archives, so there is nothing to free
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5DE0 (#10038)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_GetArchive, dll_base + 0x00005DE0);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			CHECK_EQ(moo_result, original_result);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5DF0 (#10185)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10185, dll_base + 0x00005DF0);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5E80 (#10171)" * doctest::skip("Needs the MPQ archives"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadExpansionArchives, dll_base + 0x00005E80);

		SUBCASE("")
		{
			D2ConfigStrc moo_pConfig{};
			D2ConfigStrc original_pConfig{};

			// Call both implementations
			const auto moo_result = sut(nullptr, nullptr, nullptr, &moo_pConfig);
			const auto original_result = original(nullptr, nullptr, nullptr, &original_pConfig);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A60A0 (#10172)" * doctest::skip("Needs the MPQ archives"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_LoadVideoArchives, dll_base + 0x000060A0);

		SUBCASE("")
		{
			int32_t bExpansion = 0;

			// Call both implementations
			const auto moo_result = sut(nullptr, nullptr, bExpansion);
			const auto original_result = original(nullptr, nullptr, bExpansion);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6110 (#10173)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ARCHIVE_UnloadExpansionArchives, dll_base + 0x00006110);

		// NOTE: The tests never load the archives, so there is nothing to unload
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
}

#endif
