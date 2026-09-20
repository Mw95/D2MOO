#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/BeltsTbls.h>

#include <Fixtures/DataTbls/Fixtures.h>


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
	
	TEST_CASE_FIXTURE(BeltsTxtFixture<NoopFixture>, "D2Common.0x6FD493B0 (#10638)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetBeltsTxtRecord, dll_base + 0x000093B0);
		
		SUBCASE("")
		{
			const auto high_res = GENERATE(0, 1);

			for (auto i = 0; i < 7; ++i)
			{
				// Input data
				D2BeltsTxt moo_pRecord{};
				D2BeltsTxt original_pRecord{};
				int nIndex = i;
				int bHigherRes = high_res;

				// Call both implementations
				sut(nIndex, bHigherRes, &moo_pRecord);
				original(nIndex, bHigherRes, &original_pRecord);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRecord, original_pRecord, "Comparing pRecord");
			}
		}
	}
	
	TEST_CASE_FIXTURE(BeltsTxtFixture<NoopFixture>, "D2Common.0x6FD49420 (#10639)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DATATBLS_GetInvRectFromBeltsTxt, dll_base + 0x00009420);
		
		SUBCASE("")
		{
			const auto high_res = GENERATE(0, 1);

			for (auto j = 0; j < 16; ++j)
			{
				for (auto i = 0; i < 7; ++i)
				{
					// Input data
					D2InvRectStrc moo_pInvRect{};
					D2InvRectStrc original_pInvRect{};
					int nIndex = i;
					int bHigherRes = high_res;
					int nBoxId = j;

					// Call both implementations
					sut(nIndex, bHigherRes, &moo_pInvRect, nBoxId);
					original(nIndex, bHigherRes, &original_pInvRect, nBoxId);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pInvRect, original_pInvRect, "Comparing pInvRect");
				}
			}
		}
	}
}
