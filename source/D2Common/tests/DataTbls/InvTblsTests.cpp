#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/InvTbls.h>


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
			// TODO: Setup as needed
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD54F20 (#10635)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetInventoryRect, dll_base + 0x00014F20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2InvRectStrc pInvRect{};
				
				return std::tuple{ pInvRect };
			};
			
			// Input data
			auto [moo_pInvRect] = setup_data();
			auto [original_pInvRect] = setup_data();
			int nInventoryTxtId{};
			int bHigherRes{};

			// Call both implementations
			sut(nInventoryTxtId, bHigherRes, &moo_pInvRect);
			original(nInventoryTxtId, bHigherRes, &original_pInvRect);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pInvRect, original_pInvRect, "Comparing pInvRect");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD54FB0 (#10636)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetInventoryGridInfo, dll_base + 0x00014FB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2InventoryGridInfoStrc pInventoryGridInfo{};
				
				return std::tuple{ pInventoryGridInfo };
			};
			
			// Input data
			auto [moo_pInventoryGridInfo] = setup_data();
			auto [original_pInventoryGridInfo] = setup_data();
			int nInventoryTxtId{};
			int bHigherRes{};

			// Call both implementations
			sut(nInventoryTxtId, bHigherRes, &moo_pInventoryGridInfo);
			original(nInventoryTxtId, bHigherRes, &original_pInventoryGridInfo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pInventoryGridInfo, original_pInventoryGridInfo, "Comparing pInventoryGridInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD55030 (#10637)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetInventoryComponentGrid, dll_base + 0x00015030);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2InvCompGridStrc pInvCompGrid{};
				
				return std::tuple{ pInvCompGrid };
			};
			
			// Input data
			auto [moo_pInvCompGrid] = setup_data();
			auto [original_pInvCompGrid] = setup_data();
			int nInventoryTxtId{};
			int bHigherRes{};
			int nComponent{};

			// Call both implementations
			sut(nInventoryTxtId, bHigherRes, &moo_pInvCompGrid, nComponent);
			original(nInventoryTxtId, bHigherRes, &original_pInvCompGrid, nComponent);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pInvCompGrid, original_pInvCompGrid, "Comparing pInvCompGrid");
		}
	}
}
