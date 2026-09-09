#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/BeltsTbls.h>


TEST_SUITE("BeltsTblsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD48880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_LoadBeltsTxt, dll_base + 0x00008880);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			HD2ARCHIVE hArchive{};

			// Call both implementations
			sut(hArchive);
			original(hArchive);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD493A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_UnloadBeltsTxt, dll_base + 0x000093A0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD493B0 (#10638)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetBeltsTxtRecord, dll_base + 0x000093B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2BeltsTxt pRecord{};
				
				return std::tuple{ pRecord };
			};
			
			// Input data
			auto [moo_pRecord] = setup_data();
			auto [original_pRecord] = setup_data();
			int nIndex{};
			int bHigherRes{};

			// Call both implementations
			sut(nIndex, bHigherRes, &moo_pRecord);
			original(nIndex, bHigherRes, &original_pRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRecord, original_pRecord, "Comparing pRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD49420 (#10639)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetInvRectFromBeltsTxt, dll_base + 0x00009420);
		
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
			int nIndex{};
			int bHigherRes{};
			int nBoxId{};

			// Call both implementations
			sut(nIndex, bHigherRes, &moo_pInvRect, nBoxId);
			original(nIndex, bHigherRes, &original_pInvRect, nBoxId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pInvRect, original_pInvRect, "Comparing pInvRect");
		}
	}
}
