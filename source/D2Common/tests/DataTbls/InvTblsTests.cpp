#include <D2CommonTestDefines.h>

#ifdef INV_TBLS_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/InvTbls.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("InvTblsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD542D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadInventoryTxt, dll_base + 0x000142D0);
		
		SUBCASE("")
		{
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD54F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_UnloadInventoryTxt, dll_base + 0x00014F10);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<NoopFixture>, "D2Common.0x6FD54F20 (#10635)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetInventoryRect, dll_base + 0x00014F20);
		
		SUBCASE("")
		{
			const auto high_res = GENERATE(0, 1);

			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				D2InvRectStrc moo_pInvRect{};
				D2InvRectStrc original_pInvRect{};
				int nInventoryTxtId = i;
				int bHigherRes = high_res;

				// Call both implementations
				sut(nInventoryTxtId, bHigherRes, &moo_pInvRect);
				original(nInventoryTxtId, bHigherRes, &original_pInvRect);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pInvRect, original_pInvRect, "Comparing pInvRect");
			}
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<NoopFixture>, "D2Common.0x6FD54FB0 (#10636)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetInventoryGridInfo, dll_base + 0x00014FB0);
		
		SUBCASE("")
		{
			const auto high_res = GENERATE(0, 1);

			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				D2InventoryGridInfoStrc moo_pInventoryGridInfo{};
				D2InventoryGridInfoStrc original_pInventoryGridInfo{};
				int nInventoryTxtId= i;
				int bHigherRes = high_res;

				// Call both implementations
				sut(nInventoryTxtId, bHigherRes, &moo_pInventoryGridInfo);
				original(nInventoryTxtId, bHigherRes, &original_pInventoryGridInfo);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pInventoryGridInfo, original_pInventoryGridInfo, "Comparing pInventoryGridInfo");
			}
		}
	}
	
	TEST_CASE_FIXTURE(InventoryTxtFixture<NoopFixture>, "D2Common.0x6FD55030 (#10637)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetInventoryComponentGrid, dll_base + 0x00015030);
		
		SUBCASE("")
		{
			const auto high_res = GENERATE(0, 1);

			for (auto j = 0; j < 10; ++j)
			{
				for (auto i = 0; i < 16; ++i)
				{
					// Input data
					D2InvCompGridStrc moo_pInvCompGrid{};
					D2InvCompGridStrc original_pInvCompGrid{};
					int nInventoryTxtId = i;
					int bHigherRes = high_res;
					int nComponent = j;

					// Call both implementations
					sut(nInventoryTxtId, bHigherRes, &moo_pInvCompGrid, nComponent);
					original(nInventoryTxtId, bHigherRes, &original_pInvCompGrid, nComponent);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pInvCompGrid, original_pInvCompGrid, "Comparing pInvCompGrid");
				}
			}
		}
	}
}

#endif
