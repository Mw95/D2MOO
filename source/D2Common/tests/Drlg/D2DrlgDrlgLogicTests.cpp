#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlgLogic.h>


TEST_SUITE("D2DrlgDrlgLogicTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_FreeDrlgCoordList, dll_base + 0x00036420);
		
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

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_SetTileGridFlags, dll_base + 0x00036830);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnkDrlgLogicStrc a1{};
				
				return std::tuple{ a1 };
			};
			
			// Input data
			auto [moo_a1] = setup_data();
			auto [original_a1] = setup_data();
			int nX{};
			int nY{};
			int a4{};

			// Call both implementations
			sut(&moo_a1, nX, nY, a4);
			original(&original_a1, nX, nY, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD769B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD769B0, dll_base + 0x000369B0);
		
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

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76A90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD76A90, dll_base + 0x00036A90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom1{};
				D2DrlgRoomStrc pDrlgRoom2{};
				
				return std::tuple{ pDrlgRoom1, pDrlgRoom2 };
			};
			
			// Input data
			auto [moo_pDrlgRoom1, moo_pDrlgRoom2] = setup_data();
			auto [original_pDrlgRoom1, original_pDrlgRoom2] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			sut(&moo_pDrlgRoom1, &moo_pDrlgRoom2, nX, nY);
			original(&original_pDrlgRoom1, &original_pDrlgRoom2, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD76B90, dll_base + 0x00036B90);
		
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
			int nIndex1{};
			int nIndex2{};
			BOOL bNode{};

			// Call both implementations
			sut(&moo_pDrlgRoom, nIndex1, nIndex2, bNode);
			original(&original_pDrlgRoom, nIndex1, nIndex2, bNode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76C20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_CheckLayer1ButNotWallObject, dll_base + 0x00036C20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgTileDataStrc pTileData{};
				
				return std::tuple{ pTileData };
			};
			
			// Input data
			auto [moo_pTileData] = setup_data();
			auto [original_pTileData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pTileData);
			const auto original_result = original(&original_pTileData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76C50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_SetCoordListForTiles, dll_base + 0x00036C50);
		
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

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76CF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_AssignCoordListsForGrids, dll_base + 0x00036CF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				D2DrlgLogicalRoomInfoStrc pDrlgCoordList{};
				
				return std::tuple{ pDrlgRoom, pDrlgCoordList };
			};
			
			// Input data
			auto [moo_pDrlgRoom, moo_pDrlgCoordList] = setup_data();
			auto [original_pDrlgRoom, original_pDrlgCoordList] = setup_data();
			int nLists{};

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pDrlgCoordList, nLists);
			original(&original_pDrlgRoom, &original_pDrlgCoordList, nLists);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoordList, original_pDrlgCoordList, "Comparing pDrlgCoordList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76F90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_AllocCoordLists, dll_base + 0x00036F90);
		
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

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_GetRoomCoordListIndex, dll_base + 0x00037080);
		
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
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nX, nY);
			const auto original_result = original(&original_pDrlgRoom, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77110" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD77110, dll_base + 0x00037110);
		
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
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nX, nY);
			const auto original_result = original(&original_pDrlgRoom, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_GetRoomCoordList, dll_base + 0x00037190);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
}
