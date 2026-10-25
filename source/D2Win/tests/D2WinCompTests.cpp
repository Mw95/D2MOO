#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2WinComp.h>


TEST_SUITE("D2WinCompTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A15E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_DrawShadow, dll_base + 0x000015E0);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit);
			original(&original_pCompositeUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A1890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_Draw, dll_base + 0x00001890);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			uint32_t dwGamma{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pCompositeUnit, dwGamma);
			const auto original_result = original(&original_pCompositeUnit, dwGamma);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A1D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_DrawName, dll_base + 0x00001D10);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pCompositeUnit);
			const auto original_result = original(&original_pCompositeUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A2070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_DrawHoverInfo, dll_base + 0x00002070);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pCompositeUnit);
			const auto original_result = original(&original_pCompositeUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A2A20 (#10142)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10142_CompUnitDestroy, dll_base + 0x00002A20);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			BOOL bFree{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit, bFree);
			original(&original_pCompositeUnit, bFree);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A2BD0 (#10154)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10154, dll_base + 0x00002BD0);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			Unicode wszAccountName{};
			Unicode wszCharName{};
			Unicode wszUnk0x1CC{};
			Unicode wszRealmName{};
			int32_t nLevel{};
			uint32_t dwProductCode{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit, &wszAccountName, &wszCharName, &wszUnk0x1CC, &wszRealmName, nLevel, dwProductCode);
			original(&original_pCompositeUnit, &wszAccountName, &wszCharName, &wszUnk0x1CC, &wszRealmName, nLevel, dwProductCode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A2C50 (#10143)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10143, dll_base + 0x00002C50);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			uint32_t nMode{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pCompositeUnit, nMode);
			const auto original_result = original(&original_pCompositeUnit, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A3360 (#10159)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10159, dll_base + 0x00003360);
		
		SUBCASE("")
		{
			// Input data
			D2CellFileStrc moo_pSquelchCelFile{};
			D2CellFileStrc moo_pSelectedCelFile{};
			D2CellFileStrc original_pSquelchCelFile{};
			D2CellFileStrc original_pSelectedCelFile{};

			const auto setup_data = [](
				D2CellFileStrc& pSquelchCelFile,
				D2CellFileStrc& pSelectedCelFile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSquelchCelFile, moo_pSelectedCelFile);
			setup_data(original_pSquelchCelFile, original_pSelectedCelFile);

			// Call both implementations
			sut(&moo_pSquelchCelFile, &moo_pSelectedCelFile);
			original(&original_pSquelchCelFile, &original_pSelectedCelFile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSquelchCelFile, original_pSquelchCelFile, "Comparing pSquelchCelFile");
			SKIP_MOO_CHECK_EQ(moo_pSelectedCelFile, original_pSelectedCelFile, "Comparing pSelectedCelFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A3390 (#10144)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10144, dll_base + 0x00003390);
		
		SUBCASE("")
		{
			// Input data
			uint8_t moo_pComponents{};
			uint8_t original_pComponents{};
			uint32_t nClass{};
			uint32_t nMode{};
			uint8_t pComponentColors{};

			const auto setup_data = [](
				uint8_t& pComponents
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pComponents);
			setup_data(original_pComponents);

			// Call both implementations
			const auto moo_result = sut(nClass, nMode, &moo_pComponents, &pComponentColors);
			const auto original_result = original(nClass, nMode, &original_pComponents, &pComponentColors);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pComponents, original_pComponents, "Comparing pComponents");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4260 (#10145)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10145, dll_base + 0x00004260);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			uint8_t moo_pComponents{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			uint8_t original_pComponents{};
			uint32_t nClass{};
			uint32_t nMode{};
			uint8_t pComponentColors{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit,
				uint8_t& pComponents
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit, moo_pComponents);
			setup_data(original_pCompositeUnit, original_pComponents);

			// Call both implementations
			sut(&moo_pCompositeUnit, nClass, nMode, &moo_pComponents, &pComponentColors);
			original(&original_pCompositeUnit, nClass, nMode, &original_pComponents, &pComponentColors);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
			SKIP_MOO_CHECK_EQ(moo_pComponents, original_pComponents, "Comparing pComponents");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A43C0 (#10146)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10146, dll_base + 0x000043C0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4400 (#10147)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10147, dll_base + 0x00004400);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4410 (#10148)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10148, dll_base + 0x00004410);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pCompositeUnit);
			const auto original_result = original(&original_pCompositeUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4440 (#10149)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10149, dll_base + 0x00004440);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			uint8_t nDirection{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit, nDirection);
			original(&original_pCompositeUnit, nDirection);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4490 (#10150)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10150, dll_base + 0x00004490);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pCompositeUnit);
			const auto original_result = original(&original_pCompositeUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A44C0 (#10169)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10169, dll_base + 0x000044C0);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pCompositeUnit);
			const auto original_result = original(&original_pCompositeUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A44F0 (#10151)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10151, dll_base + 0x000044F0);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			int32_t nFrame{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit, nFrame);
			original(&original_pCompositeUnit, nFrame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4540 (#10152)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10152, dll_base + 0x00004540);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			int32_t nX{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit, nX);
			original(&original_pCompositeUnit, nX);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4570 (#10153)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10153, dll_base + 0x00004570);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			int32_t nY{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit, nY);
			original(&original_pCompositeUnit, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A45A0 (#10155)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10155, dll_base + 0x000045A0);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pCompositeUnit);
			const auto original_result = original(&original_pCompositeUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A45D0 (#10156)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10156, dll_base + 0x000045D0);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			uint32_t dwFlags{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit, dwFlags);
			original(&original_pCompositeUnit, dwFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4600 (#10158)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10158, dll_base + 0x00004600);
		
		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			uint8_t nEmblem{};
			uint8_t nEmblemColor1{};
			uint8_t nEmblemColor2{};

			const auto setup_data = [](
				D2CompositeUnitStrc& pCompositeUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCompositeUnit);
			setup_data(original_pCompositeUnit);

			// Call both implementations
			sut(&moo_pCompositeUnit, nEmblem, nEmblemColor1, nEmblemColor2);
			original(&original_pCompositeUnit, nEmblem, nEmblemColor1, nEmblemColor2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A46E0 (#10157)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10157, dll_base + 0x000046E0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_InitEmblemColors, dll_base + 0x00004C10);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4C70 (#10161)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10161, dll_base + 0x00004C70);
		
		SUBCASE("")
		{
			int32_t nClass{};
			int32_t nProgression{};
			BOOL bHardcore{};
			BOOL bExpansion{};

			// Call both implementations
			const auto moo_result = sut(nClass, nProgression, bHardcore, bExpansion);
			const auto original_result = original(nClass, nProgression, bHardcore, bExpansion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4CE0 (#10160)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10160_GetPlayerTitle, dll_base + 0x00004CE0);
		
		SUBCASE("")
		{
			int32_t nClass{};
			int32_t nTitle{};
			BOOL bExpansion{};

			// Call both implementations
			const auto moo_result = sut(nClass, nTitle, bExpansion);
			const auto original_result = original(nClass, nTitle, bExpansion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
}
