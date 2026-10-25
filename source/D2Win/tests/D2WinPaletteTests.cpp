#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinPalette.h>


TEST_SUITE("D2WinPaletteTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE550 (#10177)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10177, dll_base + 0x0000E550);
		
		SUBCASE("")
		{
			uint8_t nAct{};

			// Call both implementations
			const auto moo_result = sut(nAct);
			const auto original_result = original(nAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE5E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PALETTE_LoadFiles, dll_base + 0x0000E5E0);
		
		SUBCASE("")
		{
			char szDatFileName{};
			char szPL2FileName{};

			// Call both implementations
			const auto moo_result = sut(&szDatFileName, &szPL2FileName);
			const auto original_result = original(&szDatFileName, &szPL2FileName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE940 (#10179)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10179, dll_base + 0x0000E940);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE9A0 (#10176)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10176, dll_base + 0x0000E9A0);
		
		SUBCASE("")
		{
			int32_t bStartFade{};

			// Call both implementations
			sut(bStartFade);
			original(bStartFade);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE9F0 (#10028)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10028, dll_base + 0x0000E9F0);
		
		SUBCASE("")
		{
			char pszPalDatFilename{};
			char pszPalPL2Filename{};

			// Call both implementations
			const auto moo_result = sut(&pszPalDatFilename, &pszPalPL2Filename);
			const auto original_result = original(&pszPalDatFilename, &pszPalPL2Filename);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AEA80 (#10034)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10034_MixRGB, dll_base + 0x0000EA80);
		
		SUBCASE("")
		{
			uint8_t nRed{};
			uint8_t nGreen{};
			uint8_t nBlue{};

			// Call both implementations
			const auto moo_result = sut(nRed, nGreen, nBlue);
			const auto original_result = original(nRed, nGreen, nBlue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AEAC0 (#10178)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10178, dll_base + 0x0000EAC0);
		
		SUBCASE("")
		{
			// Input data
			D2ShadowLightGammaPaletteStrc moo_pBuffer{};
			D2ShadowLightGammaPaletteStrc original_pBuffer{};

			const auto setup_data = [](
				D2ShadowLightGammaPaletteStrc& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pBuffer);
			setup_data(original_pBuffer);

			// Call both implementations
			sut(&moo_pBuffer);
			original(&original_pBuffer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
}
