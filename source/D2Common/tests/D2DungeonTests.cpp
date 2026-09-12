#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Collision.h>
#include <D2Dungeon.h>
#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <Units/Units.h>

#include "TestFixtures/LevelsTxtFixture.h"
#include "TestFixtures/PortalLevelsFixture.h"


TEST_SUITE("D2DungeonTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B8A0 (#10038)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AllocAct, dll_base + 0x0004B8A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();
			uint8_t nActNo{};
			uint32_t nInitSeed{};
			BOOL bClient{};
			uint8_t nDifficulty{};
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nTownLevelId{};
			AUTOMAPFN pfAutoMap{};
			TOWNAUTOMAPFN pfTownAutoMap{};

			// Call both implementations
			const auto moo_result = sut(nActNo, nInitSeed, bClient, &moo_pGame, nDifficulty, moo_pMemPool, nTownLevelId, pfAutoMap, pfTownAutoMap);
			const auto original_result = original(nActNo, nInitSeed, bClient, &original_pGame, nDifficulty, original_pMemPool, nTownLevelId, pfAutoMap, pfTownAutoMap);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B950 (#10039)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FreeAct, dll_base + 0x0004B950);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			sut(&moo_pAct);
			original(&original_pAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetMemPoolFromAct, dll_base + 0x0004B9D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B9E0 (#10026)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ToggleRoomTilesEnableFlag, dll_base + 0x0004B9E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			BOOL bEnabled{};

			// Call both implementations
			sut(&moo_pRoom, bEnabled);
			original(&original_pRoom, bEnabled);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BA20 (#10027)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetWarpTileFromRoomAndSourceLevelId, dll_base + 0x0004BA20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2LvlWarpTxt* ppLvlWarpTxtRecord{};
				
				return std::tuple{ pRoom, ppLvlWarpTxtRecord };
			};
			
			// Input data
			auto [moo_pRoom, moo_ppLvlWarpTxtRecord] = setup_data();
			auto [original_pRoom, original_ppLvlWarpTxtRecord] = setup_data();
			int nSourceLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nSourceLevel, &moo_ppLvlWarpTxtRecord);
			const auto original_result = original(&original_pRoom, nSourceLevel, &original_ppLvlWarpTxtRecord);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_ppLvlWarpTxtRecord, original_ppLvlWarpTxtRecord, "Comparing ppLvlWarpTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BAB0 (#10028)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetLvlWarpTxtRecordFromRoomAndUnit, dll_base + 0x0004BAB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pRoom, pUnit };
			};
			
			// Input data
			auto [moo_pRoom, moo_pUnit] = setup_data();
			auto [original_pRoom, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pUnit);
			const auto original_result = original(&original_pRoom, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BAF0 (#10030)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetFloorTilesFromRoom, dll_base + 0x0004BAF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				int pFloorCount{};
				
				return std::tuple{ pRoom, pFloorCount };
			};
			
			// Input data
			auto [moo_pRoom, moo_pFloorCount] = setup_data();
			auto [original_pRoom, original_pFloorCount] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pFloorCount);
			const auto original_result = original(&original_pRoom, &original_pFloorCount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pFloorCount, original_pFloorCount, "Comparing pFloorCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BB20 (#10031)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetWallTilesFromRoom, dll_base + 0x0004BB20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				int pWallCount{};
				
				return std::tuple{ pRoom, pWallCount };
			};
			
			// Input data
			auto [moo_pRoom, moo_pWallCount] = setup_data();
			auto [original_pRoom, original_pWallCount] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pWallCount);
			const auto original_result = original(&original_pRoom, &original_pWallCount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pWallCount, original_pWallCount, "Comparing pWallCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BB60 (#10032)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoofTilesFromRoom, dll_base + 0x0004BB60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				int pRoofCount{};
				
				return std::tuple{ pRoom, pRoofCount };
			};
			
			// Input data
			auto [moo_pRoom, moo_pRoofCount] = setup_data();
			auto [original_pRoom, original_pRoofCount] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pRoofCount);
			const auto original_result = original(&original_pRoom, &original_pRoofCount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRoofCount, original_pRoofCount, "Comparing pRoofCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BBA0 (#10033)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetTileDataFromAct, dll_base + 0x0004BBA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BBB0 (#10034)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomCoordinates, dll_base + 0x0004BBB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2DrlgCoordsStrc pCoords{};
				
				return std::tuple{ pRoom, pCoords };
			};
			
			// Input data
			auto [moo_pRoom, moo_pCoords] = setup_data();
			auto [original_pRoom, original_pCoords] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pCoords);
			original(&original_pRoom, &original_pCoords);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCoords, original_pCoords, "Comparing pCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BC10 (#10035)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetAdjacentRoomsListFromRoom, dll_base + 0x0004BC10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2ActiveRoomStrc** pppRoomList{};
				int pNumRooms{};
				
				return std::tuple{ pRoom, pppRoomList, pNumRooms };
			};
			
			// Input data
			auto [moo_pRoom, moo_pppRoomList, moo_pNumRooms] = setup_data();
			auto [original_pRoom, original_pppRoomList, original_pNumRooms] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pppRoomList, &moo_pNumRooms);
			original(&original_pRoom, &original_pppRoomList, &original_pNumRooms);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pppRoomList, original_pppRoomList, "Comparing pppRoomList");
			SKIP_MOO_CHECK_EQ(moo_pNumRooms, original_pNumRooms, "Comparing pNumRooms");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BC50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AllocRoom, dll_base + 0x0004BC50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2DrlgRoomStrc pDrlgRoom{};
				D2DrlgCoordsStrc pDrlgCoords{};
				D2DrlgRoomTilesStrc pRoomTiles{};
				
				return std::tuple{ pAct, pDrlgRoom, pDrlgCoords, pRoomTiles };
			};
			
			// Input data
			auto [moo_pAct, moo_pDrlgRoom, moo_pDrlgCoords, moo_pRoomTiles] = setup_data();
			auto [original_pAct, original_pDrlgRoom, original_pDrlgCoords, original_pRoomTiles] = setup_data();
			int nLowSeed{};
			uint32_t dwFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, &moo_pDrlgRoom, &moo_pDrlgCoords, &moo_pRoomTiles, nLowSeed, dwFlags);
			const auto original_result = original(&original_pAct, &original_pDrlgRoom, &original_pDrlgCoords, &original_pRoomTiles, nLowSeed, dwFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
			SKIP_MOO_CHECK_EQ(moo_pRoomTiles, original_pRoomTiles, "Comparing pRoomTiles");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BD90 (#10040)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_DoRoomsTouchOrOverlap, dll_base + 0x0004BD90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc ptFirst{};
				D2ActiveRoomStrc ptSecond{};
				
				return std::tuple{ ptFirst, ptSecond };
			};
			
			// Input data
			auto [moo_ptFirst, moo_ptSecond] = setup_data();
			auto [original_ptFirst, original_ptSecond] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_ptFirst, &moo_ptSecond);
			const auto original_result = original(&original_ptFirst, &original_ptSecond);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ptFirst, original_ptFirst, "Comparing ptFirst");
			SKIP_MOO_CHECK_EQ(moo_ptSecond, original_ptSecond, "Comparing ptSecond");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BE30 (#10043)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AreTileCoordinatesInsideRoom, dll_base + 0x0004BE30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nX, nY);
			const auto original_result = original(&original_pRoom, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BE90 (#10048)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_CheckRoomsOverlapping_BROKEN, dll_base + 0x0004BE90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pPrimary{};
				D2ActiveRoomStrc pSecondary{};
				
				return std::tuple{ pPrimary, pSecondary };
			};
			
			// Input data
			auto [moo_pPrimary, moo_pSecondary] = setup_data();
			auto [original_pPrimary, original_pSecondary] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pPrimary, &moo_pSecondary);
			const auto original_result = original(&original_pPrimary, &original_pSecondary);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPrimary, original_pPrimary, "Comparing pPrimary");
			SKIP_MOO_CHECK_EQ(moo_pSecondary, original_pSecondary, "Comparing pSecondary");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Commmon.0x6FD8BF00 (#10051)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FindRoomByTileCoordinates, dll_base + 0x0004BF00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nX, nY);
			const auto original_result = original(&original_pAct, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BF50 (#10050)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetAdjacentRoomByTileCoordinates, dll_base + 0x0004BF50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nX, nY);
			const auto original_result = original(&original_pRoom, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BFF0 (#10049)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_CallRoomCallback, dll_base + 0x0004BFF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			ROOMCALLBACKFN pfnRoomCallback{};
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			// Call both implementations
			sut(&moo_pRoom, pfnRoomCallback, moo_pArgs);
			original(&original_pRoom, pfnRoomCallback, original_pArgs);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C080 (#10052)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10052, dll_base + 0x0004C080);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				RECT pRect{};
				
				return std::tuple{ pRoom, pRect };
			};
			
			// Input data
			auto [moo_pRoom, moo_pRect] = setup_data();
			auto [original_pRoom, original_pRect] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pRect);
			original(&original_pRoom, &original_pRect);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRect, original_pRect, "Comparing pRect");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C170 (#10053)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetSubtileRect, dll_base + 0x0004C170);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				RECT pRect{};
				
				return std::tuple{ pRoom, pRect };
			};
			
			// Input data
			auto [moo_pRoom, moo_pRect] = setup_data();
			auto [original_pRoom, original_pRect] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pRect);
			original(&original_pRoom, &original_pRect);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRect, original_pRect, "Comparing pRect");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C210 (#10054)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRGB_IntensityFromRoom, dll_base + 0x0004C210);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				uint8_t pIntensity{};
				uint8_t pRed{};
				uint8_t pGreen{};
				uint8_t pBlue{};
				
				return std::tuple{ pRoom, pIntensity, pRed, pGreen, pBlue };
			};
			
			// Input data
			auto [moo_pRoom, moo_pIntensity, moo_pRed, moo_pGreen, moo_pBlue] = setup_data();
			auto [original_pRoom, original_pIntensity, original_pRed, original_pGreen, original_pBlue] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pIntensity, &moo_pRed, &moo_pGreen, &moo_pBlue);
			original(&original_pRoom, &original_pIntensity, &original_pRed, &original_pGreen, &original_pBlue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pIntensity, original_pIntensity, "Comparing pIntensity");
			SKIP_MOO_CHECK_EQ(moo_pRed, original_pRed, "Comparing pRed");
			SKIP_MOO_CHECK_EQ(moo_pGreen, original_pGreen, "Comparing pGreen");
			SKIP_MOO_CHECK_EQ(moo_pBlue, original_pBlue, "Comparing pBlue");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C240 (#10041)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FindRoomBySubtileCoordinates, dll_base + 0x0004C240);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nX, nY);
			const auto original_result = original(&original_pAct, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C290" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AreSubtileCoordinatesInsideRoom, dll_base + 0x0004C290);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgCoordsStrc pDrlgCoords{};
				
				return std::tuple{ pDrlgCoords };
			};
			
			// Input data
			auto [moo_pDrlgCoords] = setup_data();
			auto [original_pDrlgCoords] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgCoords, nX, nY);
			const auto original_result = original(&original_pDrlgCoords, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C2F0 (#10046)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FindActSpawnLocation, dll_base + 0x0004C2F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				int pX{};
				int pY{};
				
				return std::tuple{ pAct, pX, pY };
			};
			
			// Input data
			auto [moo_pAct, moo_pX, moo_pY] = setup_data();
			auto [original_pAct, original_pX, original_pY] = setup_data();
			int nLevelId{};
			int nTileIndex{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nLevelId, nTileIndex, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pAct, nLevelId, nTileIndex, &original_pX, &original_pY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C340 (#10045)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FindActSpawnLocationEx, dll_base + 0x0004C340);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				int pX{};
				int pY{};
				
				return std::tuple{ pAct, pX, pY };
			};
			
			// Input data
			auto [moo_pAct, moo_pX, moo_pY] = setup_data();
			auto [original_pAct, original_pX, original_pY] = setup_data();
			int nLevelId{};
			int nTileIndex{};
			int nUnitSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nLevelId, nTileIndex, &moo_pX, &moo_pY, nUnitSize);
			const auto original_result = original(&original_pAct, nLevelId, nTileIndex, &original_pX, &original_pY, nUnitSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C4A0 (#10029)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetFirstUnitInRoom, dll_base + 0x0004C4A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C4E0 (#10100)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_IncreaseAlliedCountOfRoom, dll_base + 0x0004C4E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Comon.0x6FD8C4F0 (#10036)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetAlliedCountFromRoom, dll_base + 0x0004C4F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C510 (#10101)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_DecreaseAlliedCountOfRoom, dll_base + 0x0004C510);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetUnitListFromRoom, dll_base + 0x0004C550);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetUnitUpdateListFromRoom, dll_base + 0x0004C580);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			BOOL bUpdate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, bUpdate);
			const auto original_result = original(&original_pRoom, bUpdate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C5C0 (#10055)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetPresetUnitsFromRoom, dll_base + 0x0004C5C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetCollisionGridFromRoom, dll_base + 0x0004C600);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_SetCollisionGridInRoom, dll_base + 0x0004C630);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2RoomCollisionGridStrc pCollisionGrid{};
				
				return std::tuple{ pRoom, pCollisionGrid };
			};
			
			// Input data
			auto [moo_pRoom, moo_pCollisionGrid] = setup_data();
			auto [original_pRoom, original_pCollisionGrid] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pCollisionGrid);
			original(&original_pRoom, &original_pCollisionGrid);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCollisionGrid, original_pCollisionGrid, "Comparing pCollisionGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C660 (#10063)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_SetClientIsInSight, dll_base + 0x0004C660);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();
			int nLevelId{};
			int nX{};
			int nY{};

			// Call both implementations
			sut(&moo_pAct, nLevelId, nX, nY, &moo_pRoom);
			original(&original_pAct, nLevelId, nX, nY, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C6B0 (#10064)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UnsetClientIsInSight, dll_base + 0x0004C6B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();
			int nLevelId{};
			int nX{};
			int nY{};

			// Call both implementations
			sut(&moo_pAct, nLevelId, nX, nY, &moo_pRoom);
			original(&original_pAct, nLevelId, nX, nY, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C700 (#10062)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ChangeClientRoom, dll_base + 0x0004C700);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom1{};
				D2ActiveRoomStrc pRoom2{};
				
				return std::tuple{ pRoom1, pRoom2 };
			};
			
			// Input data
			auto [moo_pRoom1, moo_pRoom2] = setup_data();
			auto [original_pRoom1, original_pRoom2] = setup_data();

			// Call both implementations
			sut(&moo_pRoom1, &moo_pRoom2);
			original(&original_pRoom1, &original_pRoom2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
			SKIP_MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C730 (#10065)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_StreamRoomAtCoords, dll_base + 0x0004C730);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nX, nY);
			const auto original_result = original(&original_pAct, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C770 (#10056)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomFromAct, dll_base + 0x0004C770);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C7A0 (#10057)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetLevelIdFromRoom, dll_base + 0x0004C7A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C7C0 (#10058)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetWarpDestinationLevel, dll_base + 0x0004C7C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nSourceLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nSourceLevel);
			const auto original_result = original(&original_pRoom, nSourceLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C7E0 (#10059)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetLevelIdFromPopulatedRoom, dll_base + 0x0004C7E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C800 (#10060)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_HasWaypoint, dll_base + 0x0004C800);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C840 (#10061)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetPickedLevelPrestFilePathFromRoom, dll_base + 0x0004C840);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C860 (#10066)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AllocDrlgDelete, dll_base + 0x0004C860);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nUnitType{};
			D2UnitGUID nUnitGuid{};

			// Call both implementations
			sut(&moo_pRoom, nUnitType, nUnitGuid);
			original(&original_pRoom, nUnitType, nUnitGuid);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C8B0 (#10067)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FreeDrlgDelete, dll_base + 0x0004C8B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C910 (#10068)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetDrlgDeleteFromRoom, dll_base + 0x0004C910);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C940 (#10069)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetARoomInClientSight, dll_base + 0x0004C940);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C980 (#10070)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetARoomInSightButWithoutClient, dll_base + 0x0004C980);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, &moo_pRoom);
			const auto original_result = original(&original_pAct, &original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C9E0 (#10071)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_TestRoomCanUnTile, dll_base + 0x0004C9E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, &moo_pRoom);
			const auto original_result = original(&original_pAct, &original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CA60 (#10072)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomStatusFlags, dll_base + 0x0004CA60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CA80 (#10073)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10073, dll_base + 0x0004CA80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CAE0 (#10074)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10074, dll_base + 0x0004CAE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CB10 (#10075)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10075, dll_base + 0x0004CB10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			BOOL bSet{};

			// Call both implementations
			sut(&moo_pRoom, bSet);
			original(&original_pRoom, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CB60 (#10079)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AddClientToRoom, dll_base + 0x0004CB60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pRoom, pClient };
			};
			
			// Input data
			auto [moo_pRoom, moo_pClient] = setup_data();
			auto [original_pRoom, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pClient);
			original(&original_pRoom, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CC50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdateClientListOfRoom, dll_base + 0x0004CC50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CD10 (#10080)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_RemoveClientFromRoom, dll_base + 0x0004CD10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pRoom, pClient };
			};
			
			// Input data
			auto [moo_pRoom, moo_pClient] = setup_data();
			auto [original_pRoom, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pClient);
			original(&original_pRoom, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CDF0 (#10081)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10081_GetTileCountFromRoom, dll_base + 0x0004CDF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CE40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FreeRoom, dll_base + 0x0004CE40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pRoom);
			original(original_pMemPool, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CF10 (#10076)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_RemoveRoomFromAct, dll_base + 0x0004CF10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pAct, pRoom };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom] = setup_data();
			auto [original_pAct, original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pAct, &moo_pRoom);
			original(&original_pAct, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D000 (#10077)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10077, dll_base + 0x0004D000);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom1{};
				D2ActiveRoomStrc pRoom2{};
				
				return std::tuple{ pRoom1, pRoom2 };
			};
			
			// Input data
			auto [moo_pRoom1, moo_pRoom2] = setup_data();
			auto [original_pRoom1, original_pRoom2] = setup_data();

			// Call both implementations
			sut(&moo_pRoom1, &moo_pRoom2);
			original(&original_pRoom1, &original_pRoom2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
			SKIP_MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D030 (#10078)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdateAndFreeInactiveRooms, dll_base + 0x0004D030);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			sut(&moo_pAct);
			original(&original_pAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D040 (#10044)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_CheckLOSDraw, dll_base + 0x0004D040);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D060")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetEnvironmentFromAct, dll_base + 0x0004D060);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				D2DrlgEnvironmentStrc pEnvironment{};

				D2DrlgActStrc pAct{};
				pAct.pEnvironment = &pEnvironment;
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D090 (#10088)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetDrlgFromAct, dll_base + 0x0004D090);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};

				D2DrlgActStrc pAct{};
				pAct.pDrlg = &pDrlg;
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD912D0 (#10089)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetInitSeedFromAct, dll_base + 0x000512D0);
		
		SUBCASE("")
		{
			const auto init_seed = random_unsigned_integer();

			const auto setup_data = [&init_seed]() {
				D2DrlgActStrc pAct{};

				pAct.dwInitSeed = init_seed;
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D0C0 (#10007)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomExFromRoom, dll_base + 0x0004D0C0);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};

				D2ActiveRoomStrc pRoom{};
				pRoom.pDrlgRoom = &pDrlgRoom;
				
				return std::tuple{ pRoom, pDrlgRoom };
			};
			
			// Input data
			auto [moo_pRoom, moo_pDrlgRoom] = setup_data();
			auto [original_pRoom, original_pDrlgRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(LevelsTxtFixture<NoopFixture>, "D2Common.0x6FD8D0D0 (#10086)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_IsTownLevelId, dll_base + 0x0004D0D0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < levels_record_count; ++i)
			{
				int nLevelId = i;

				// Call both implementations
				const auto moo_result = sut(nLevelId);
				const auto original_result = original(nLevelId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(LevelsTxtFixture<NoopFixture>, "D2Common.0x6FD8D0E0 (#10082)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_IsRoomInTown, dll_base + 0x0004D0E0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < levels_record_count; ++i)
			{
				const auto setup_data = [&i]() {
					D2DrlgLevelStrc pLevel{};
					pLevel.nLevelId = i;

					D2DrlgRoomStrc pDrlgRoom{};
					pDrlgRoom.pLevel = &pLevel;

					D2ActiveRoomStrc pRoom{};
					pRoom.pDrlgRoom = &pDrlgRoom;

					return std::tuple{ pRoom, pDrlgRoom, pLevel };
				};

				// Input data
				auto [moo_pRoom, moo_pDrlgRoom, moo_pLevel] = setup_data();
				auto [original_pRoom, original_pDrlgRoom, original_pLevel] = setup_data();

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom);
				const auto original_result = original(&original_pRoom);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D100 (#10083)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10083_Return0, dll_base + 0x0004D100);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};

				D2DrlgRoomStrc pDrlgRoom{};
				pDrlgRoom.pLevel = &pLevel;

				D2ActiveRoomStrc pRoom{};
				pRoom.pDrlgRoom = &pDrlgRoom;
				
				return std::tuple{ pRoom, pDrlgRoom, pLevel };
			};
			
			// Input data
			auto [moo_pRoom, moo_pDrlgRoom, moo_pLevel] = setup_data();
			auto [original_pRoom, original_pDrlgRoom, original_pLevel] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D130 (#10084)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10084, dll_base + 0x0004D130);

		REPEAT_10();
		
		SUBCASE("")
		{
			const auto flags = random_unsigned_integer();

			const auto setup_data = [&flags]() {
				D2ActiveRoomStrc pRoom{};

				pRoom.dwFlags = flags;
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D140 (#10085)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetTownLevelIdFromActNo, dll_base + 0x0004D140);
		
		SUBCASE("")
		{
			uint8_t nAct = GENERATE(0, 1, 2, 3, 4);

			// Call both implementations
			const auto moo_result = sut(nAct);
			const auto original_result = original(nAct);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D180 (#10087)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10087, dll_base + 0x0004D180);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D1C0 (#10090)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetNumberOfPopulatedRoomsInLevel, dll_base + 0x0004D1C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nLevelId);
			const auto original_result = original(&original_pAct, nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D1E0 (#10025)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetWarpCoordinatesFromRoom, dll_base + 0x0004D1E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D220 (#10091)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdateWarpRoomSelect, dll_base + 0x0004D220);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nLevelId{};

			// Call both implementations
			sut(&moo_pRoom, nLevelId);
			original(&original_pRoom, nLevelId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D260 (#10092)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdateWarpRoomDeselect, dll_base + 0x0004D260);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nLevelId{};

			// Call both implementations
			sut(&moo_pRoom, nLevelId);
			original(&original_pRoom, nLevelId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D2A0 (#10093)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdatePops, dll_base + 0x0004D2A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nX{};
			int nY{};
			BOOL bOtherRoom{};

			// Call both implementations
			sut(&moo_pRoom, nX, nY, bOtherRoom);
			original(&original_pRoom, nX, nY, bOtherRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D2E0 (#10094)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetTombStoneTileCoords, dll_base + 0x0004D2E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2CoordStrc* ppTombStoneTiles{};
				int pnTombStoneTiles{};
				
				return std::tuple{ pRoom, ppTombStoneTiles, pnTombStoneTiles };
			};
			
			// Input data
			auto [moo_pRoom, moo_ppTombStoneTiles, moo_pnTombStoneTiles] = setup_data();
			auto [original_pRoom, original_ppTombStoneTiles, original_pnTombStoneTiles] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_ppTombStoneTiles, &moo_pnTombStoneTiles);
			original(&original_pRoom, &original_ppTombStoneTiles, &original_pnTombStoneTiles);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_ppTombStoneTiles, original_ppTombStoneTiles, "Comparing ppTombStoneTiles");
			SKIP_MOO_CHECK_EQ(moo_pnTombStoneTiles, original_pnTombStoneTiles, "Comparing pnTombStoneTiles");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D300 (#10095)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10095, dll_base + 0x0004D300);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nX, nY);
			const auto original_result = original(&original_pRoom, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D3A0 (#10096)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10096, dll_base + 0x0004D3A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nX, nY);
			const auto original_result = original(&original_pRoom, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D3C0 (#10097)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomCoordList, dll_base + 0x0004D3C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D3D0 (#10098)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetPortalLevelArrayFromPortalFlags, dll_base + 0x0004D3D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int* ppLevels{};
				int pnLevels{};
				
				return std::tuple{ ppLevels, pnLevels };
			};
			
			// Input data
			auto [moo_ppLevels, moo_pnLevels] = setup_data();
			auto [original_ppLevels, original_pnLevels] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nFlags{};

			// Call both implementations
			sut(moo_pMemPool, nFlags, &moo_ppLevels, &moo_pnLevels);
			original(original_pMemPool, nFlags, &original_ppLevels, &original_pnLevels);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_ppLevels, original_ppLevels, "Comparing ppLevels");
			SKIP_MOO_CHECK_EQ(moo_pnLevels, original_pnLevels, "Comparing pnLevels");
		}
	}
	
	TEST_CASE_FIXTURE(PortalLevelsFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD8D4B0 (#10099)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetPortalFlagFromLevelId, dll_base + 0x0004D4B0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < levels_record_count; ++i)
			{
				int nPortalLevelId = i;

				// Call both implementations
				const auto moo_result = sut(nPortalLevelId);
				const auto original_result = original(nPortalLevelId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D4F0 (#10037)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetTownLevelIdFromAct, dll_base + 0x0004D4F0);
		
		SUBCASE("")
		{
			const auto town_id = random_unsigned_integer();

			const auto setup_data = [&town_id]() {
				D2DrlgActStrc pAct{};
				
				pAct.nTownId = town_id;

				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D520 (#10047)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetHoradricStaffTombLevelId, dll_base + 0x0004D520);
		
		SUBCASE("")
		{
			D2DrlgStrc pDrlg{};

			pDrlg.nStaffTombLevel = random_unsigned_integer();
			
			const auto setup_data = [&pDrlg]() {
				D2DrlgActStrc pAct{};

				pAct.pDrlg = &pDrlg;
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D540 (#10102)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ToggleHasPortalFlag, dll_base + 0x0004D540);

		REPEAT_10();
		
		SUBCASE("bReset = FALSE")
		{
			D2DrlgRoomStrc pDrlgRoom{};
			pDrlgRoom.dwFlags = random_unsigned_integer();

			const auto setup_data = [&pDrlgRoom]() {
				D2ActiveRoomStrc pRoom{};

				pRoom.pDrlgRoom = &pDrlgRoom;
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			BOOL bReset = FALSE;

			// Call both implementations
			sut(&moo_pRoom, bReset);
			original(&original_pRoom, bReset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}

		SUBCASE("bReset = TRUE")
		{
			D2DrlgRoomStrc pDrlgRoom{};
			pDrlgRoom.dwFlags = random_unsigned_integer();

			const auto setup_data = [&pDrlgRoom]() {
				D2ActiveRoomStrc pRoom{};

				pRoom.pDrlgRoom = &pDrlgRoom;

				return std::tuple{ pRoom };
			};

			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			BOOL bReset = TRUE;

			// Call both implementations
			sut(&moo_pRoom, bReset);
			original(&original_pRoom, bReset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D560 (#10104)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AnimateTiles, dll_base + 0x0004D560);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D580 (#10105)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_InitRoomTileAnimation, dll_base + 0x0004D580);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2ActiveRoomStrc pRoom1{};
				D2ActiveRoomStrc pRoom2{};
				
				return std::tuple{ pAct, pRoom1, pRoom2 };
			};
			
			// Input data
			auto [moo_pAct, moo_pRoom1, moo_pRoom2] = setup_data();
			auto [original_pAct, original_pRoom1, original_pRoom2] = setup_data();

			// Call both implementations
			sut(&moo_pAct, &moo_pRoom1, &moo_pRoom2);
			original(&original_pAct, &original_pRoom1, &original_pRoom2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
			SKIP_MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D5C0 (#10103)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_SetActCallbackFunc, dll_base + 0x0004D5C0);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				
				return std::tuple{ pAct };
			};
			
			// Input data
			auto [moo_pAct] = setup_data();
			auto [original_pAct] = setup_data();
			ACTCALLBACKFN pActCallbackFunction = (ACTCALLBACKFN)random_unsigned_integer();

			// Call both implementations
			sut(&moo_pAct, pActCallbackFunction);
			original(&original_pAct, pActCallbackFunction);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D600 (#10106)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_SaveKilledUnitGUID, dll_base + 0x0004D600);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 20; ++i)
			{
				const auto setup_data = []() {
					D2ActiveRoomStrc pRoom{};

					return std::tuple{ pRoom };
				};

				// Input data
				auto [moo_pRoom] = setup_data();
				auto [original_pRoom] = setup_data();
				D2UnitGUID nUnitGUID = random_unsigned_integer();

				// Call both implementations
				sut(&moo_pRoom, nUnitGUID);
				original(&original_pRoom, nUnitGUID);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D690 (#10107)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ClientToGameTileCoords, dll_base + 0x0004D690);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;
				
				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D870 (#10108)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ClientToGameSubtileCoords, dll_base + 0x0004D870);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D8A0 (#10109)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ClientToGameCoords, dll_base + 0x0004D8A0);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D6E0 (#10110)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GameTileToClientCoords, dll_base + 0x0004D6E0);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D630 (#10111)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GameSubtileToClientCoords, dll_base + 0x0004D630);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D660 (#10112)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GameToClientCoords, dll_base + 0x0004D660);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D8C0 (#10113)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GameTileToSubtileCoords, dll_base + 0x0004D8C0);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D710 (#10114)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ClientTileDrawPositionToGameCoords, dll_base + 0x0004D710);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			sut(nX, nY, &moo_pX, &moo_pY);
			original(nX, nY, &original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D790 (#10115)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GameToClientTileDrawPositionCoords, dll_base + 0x0004D790);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			sut(nX, nY, &moo_pX, &moo_pY);
			original(nX, nY, &original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D7D0 (#10116)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ClientSubileDrawPositionToGameCoords, dll_base + 0x0004D7D0);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			sut(nX, nY, &moo_pX, &moo_pY);
			original(nX, nY, &original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D830 (#10117)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GameToClientSubtileDrawPositionCoords, dll_base + 0x0004D830);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			const auto setup_data = [&x, &y]() {
				int pX = x;
				int pY = y;

				return std::tuple{ pX, pY };
			};
			
			// Input data
			auto [moo_pX, moo_pY] = setup_data();
			auto [original_pX, original_pY] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			sut(nX, nY, &moo_pX, &moo_pY);
			original(nX, nY, &original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
}
