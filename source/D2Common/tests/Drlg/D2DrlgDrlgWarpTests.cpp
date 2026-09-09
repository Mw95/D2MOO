#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgWarp.h>
#include <Units/Units.h>


TEST_SUITE("D2DrlgDrlgWarpTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetDestinationRoom, dll_base + 0x00038780);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				int pDestinationLevel{};
				D2LvlWarpTxt* ppLvlWarpTxtRecord{};
				
				return std::tuple{ pDrlgRoom, pDestinationLevel, ppLvlWarpTxtRecord };
			};
			
			// Input data
			auto [moo_pDrlgRoom, moo_pDestinationLevel, moo_ppLvlWarpTxtRecord] = setup_data();
			auto [original_pDrlgRoom, original_pDestinationLevel, original_ppLvlWarpTxtRecord] = setup_data();
			int nSourceLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nSourceLevel, &moo_pDestinationLevel, &moo_ppLvlWarpTxtRecord);
			const auto original_result = original(&original_pDrlgRoom, nSourceLevel, &original_pDestinationLevel, &original_ppLvlWarpTxtRecord);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			SKIP_MOO_CHECK_EQ(moo_pDestinationLevel, original_pDestinationLevel, "Comparing pDestinationLevel");
			SKIP_MOO_CHECK_EQ(moo_ppLvlWarpTxtRecord, original_ppLvlWarpTxtRecord, "Comparing ppLvlWarpTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD787F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_ToggleRoomTilesEnableFlag, dll_base + 0x000387F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();
			BOOL bEnabled{};

			// Call both implementations
			sut(&moo_pDrlgRoom, bEnabled);
			original(&original_pDrlgRoom, bEnabled);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_UpdateWarpRoomSelect, dll_base + 0x00038810);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();
			int nLevelId{};

			// Call both implementations
			sut(&moo_pDrlgRoom, nLevelId);
			original(&original_pDrlgRoom, nLevelId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_UpdateWarpRoomDeselect, dll_base + 0x00038870);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();
			int nLevelId{};

			// Call both implementations
			sut(&moo_pDrlgRoom, nLevelId);
			original(&original_pDrlgRoom, nLevelId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD788D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD788D0, dll_base + 0x000388D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				int pX{};
				int pY{};
				
				return std::tuple{ pDrlg, pX, pY };
			};
			
			// Input data
			auto [moo_pDrlg, moo_pX, moo_pY] = setup_data();
			auto [original_pDrlg, original_pX, original_pY] = setup_data();
			int nLevelId{};
			int nTileIndex{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId, nTileIndex, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pDrlg, nLevelId, nTileIndex, &original_pX, &original_pY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetWaypointRoomExFromLevel, dll_base + 0x00038C10);
		
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
			const auto moo_result = sut(&moo_pLevel, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pLevel, &original_pX, &original_pY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetWarpIdArrayFromLevelId, dll_base + 0x00038CC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetWarpDestinationFromArray, dll_base + 0x00038D10);
		
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
			uint8_t nArrayId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nArrayId);
			const auto original_result = original(&original_pLevel, nArrayId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78D80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetLvlWarpTxtRecordFromWarpIdAndDirection, dll_base + 0x00038D80);
		
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
			uint8_t nWarpId{};
			char szDirection{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nWarpId, szDirection);
			const auto original_result = original(&original_pLevel, nWarpId, szDirection);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78DF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetLvlWarpTxtRecordFromUnit, dll_base + 0x00038DF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pDrlgRoom, pUnit };
			};
			
			// Input data
			auto [moo_pDrlgRoom, moo_pUnit] = setup_data();
			auto [original_pDrlgRoom, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, &moo_pUnit);
			const auto original_result = original(&original_pDrlgRoom, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
