#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgOutDesr.h>


TEST_SUITE("D2DrlgOutDesrTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "Inlined in D2Common.0x6FD7D430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceDesertTransitionToTown, dll_base + 0x0003D430);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7D430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_InitAct2OutdoorLevel, dll_base + 0x0003D430);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7D870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlacePresetVariants, dll_base + 0x0003D870);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();
			int pLevelPrestIds{};
			unsigned int nVariants{};
			BOOL bIterateFiles{};

			// Call both implementations
			sut(&moo_pLevel, &pLevelPrestIds, nVariants, bIterateFiles);
			original(&original_pLevel, &pLevelPrestIds, nVariants, bIterateFiles);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7D9B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceBorders, dll_base + 0x0003D9B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7D9F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_AddExits, dll_base + 0x0003D9F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DA60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceFillsInFarOasis, dll_base + 0x0003DA60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DAC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceRuinsInLostCity, dll_base + 0x0003DAC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DB00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceFillsInLostCity, dll_base + 0x0003DB00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DBC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceFillsInCanyon, dll_base + 0x0003DBC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
}
