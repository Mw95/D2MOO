#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgOutWild.h>


TEST_SUITE("D2DrlgOutWildTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD84CA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_GetBridgeCoords, dll_base + 0x00044CA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				int pX{};
				int pY{};
				
				return std::tuple{ pLevel, pX, pY };
			};
			
			// Input data
			auto [moo_pLevel, moo_pX, moo_pY] = setup_data();
			auto [original_pLevel, original_pX, original_pY] = setup_data();

			// Call both implementations
			sut(&moo_pLevel, &moo_pX, &moo_pY);
			original(&original_pLevel, &original_pX, &original_pY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD84D30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_InitAct1OutdoorLevel, dll_base + 0x00044D30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_TestSpawnRiver, dll_base + 0x00045060);
		
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
			int nX{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nX);
			const auto original_result = original(&original_pLevel, nX);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD850B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnRiver, dll_base + 0x000450B0);
		
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
			int nX{};

			// Call both implementations
			sut(&moo_pLevel, nX);
			original(&original_pLevel, nX);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD85300, dll_base + 0x00045300);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgVertexStrc pDrlgVertex{};
				
				return std::tuple{ pDrlgVertex };
			};
			
			// Input data
			auto [moo_pDrlgVertex] = setup_data();
			auto [original_pDrlgVertex] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgVertex);
			const auto original_result = original(&original_pDrlgVertex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85350" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD85350, dll_base + 0x00045350);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgVertexStrc pDrlgVertex{};
				
				return std::tuple{ pDrlgVertex };
			};
			
			// Input data
			auto [moo_pDrlgVertex] = setup_data();
			auto [original_pDrlgVertex] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgVertex);
			const auto original_result = original(&original_pDrlgVertex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85390" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnCliffCaves, dll_base + 0x00045390);
		
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
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nX, nY);
			const auto original_result = original(&original_pLevel, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD853F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnTownTransitionsAndCaves, dll_base + 0x000453F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnSpecialPresets, dll_base + 0x00045520);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85920" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnCottage, dll_base + 0x00045920);
		
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
			int nLvlPrestId{};
			int a3{};

			// Call both implementations
			sut(&moo_pLevel, nLvlPrestId, a3);
			original(&original_pLevel, nLvlPrestId, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
}
