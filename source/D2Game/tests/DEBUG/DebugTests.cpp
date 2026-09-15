#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DEBUG/Debug.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Units/Units.h>


TEST_SUITE("DebugTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD2E0 (#10025)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DEBUG_GetUnitFromTypeAndGUID, dll_base + 0x0009D2E0);
		
		SUBCASE("")
		{
			int32_t nUnitType{};
			int32_t nUnitGUID{};

			// Call both implementations
			const auto moo_result = sut(nUnitType, nUnitGUID);
			const auto original_result = original(nUnitType, nUnitGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD310 (#10026)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DEBUG_GetAct, dll_base + 0x0009D310);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD350 (#10027)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DEBUG_GetFreeMonsterIndex, dll_base + 0x0009D350);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD3B0 (#10028)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DEBUG_GetRoomBySubtileCoordinates, dll_base + 0x0009D3B0);
		
		SUBCASE("")
		{
			uint8_t nAct{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			const auto moo_result = sut(nAct, nX, nY);
			const auto original_result = original(nAct, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
}
