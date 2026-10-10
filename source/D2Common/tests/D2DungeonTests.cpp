#include <D2CommonTestDefines.h>

#ifdef DUNGEON_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <string>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Collision.h>
#include <D2Dungeon.h>
#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgLogic.h>
#include <Drlg/D2DrlgOutRoom.h>
#include <Drlg/D2DrlgPreset.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <Path/Path.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>

BEGIN_VISIT(RECT)
	FIELD(left)
	FIELD(top)
	FIELD(right)
	FIELD(bottom)
END_VISIT()

DYNAMIC_ARRAY_TYPE(int)


// Callback for DUNGEON_CallRoomCallback, pArgs points to the number of remaining calls
static int32_t __stdcall IncreaseAlliedCountUntilNoCallsRemain(D2ActiveRoomStrc* pRoom, void* pArgs)
{
	int* pRemainingCalls = static_cast<int*>(pArgs);

	++pRoom->nAllies;
	--*pRemainingCalls;

	return *pRemainingCalls > 0;
}


TEST_SUITE("D2DungeonTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	// NOTE: may_fail because the allocated environment stores the result of GetTickCount
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<LvlPrestTxtFixture<LvlMazeTxtFixture<NoopFixture>>>>, "D2Common.0x6FD8B8A0 (#10038)" * doctest::may_fail())
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AllocAct, dll_base + 0x0004B8A0);

		SUBCASE("")
		{
			// Input data
			// Only Act V on the client is used: Acts I-III load tile libraries through D2CMP and the server initializes the town level
			uint8_t nActNo = ACT_V;
			uint32_t nInitSeed = random_unsigned_integer();
			BOOL bClient = TRUE;
			uint8_t nDifficulty = random_unsigned_integer(0, 2);
			int nTownLevelId = LEVEL_HARROGATH;
			AUTOMAPFN pfAutoMap = nullptr;
			TOWNAUTOMAPFN pfTownAutoMap = nullptr;

			// Call both implementations
			const auto moo_result = sut(nActNo, nInitSeed, bClient, nullptr, nDifficulty, nullptr, nTownLevelId, pfAutoMap, pfTownAutoMap);
			const auto original_result = original(nActNo, nInitSeed, bClient, nullptr, nDifficulty, nullptr, nTownLevelId, pfAutoMap, pfTownAutoMap);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<LvlPrestTxtFixture<LvlMazeTxtFixture<NoopFixture>>>>, "D2Common.0x6FD8B950 (#10039)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FreeAct, dll_base + 0x0004B950);
		const auto [moo_alloc, original_alloc] = make_function_pair(DUNGEON_AllocAct, dll_base + 0x0004B8A0);

		SUBCASE("")
		{
			// Input data
			const auto init_seed = random_unsigned_integer();

			D2DrlgActStrc* moo_pAct = moo_alloc(ACT_V, init_seed, TRUE, nullptr, 0, nullptr, LEVEL_HARROGATH, nullptr, nullptr);
			D2DrlgActStrc* original_pAct = original_alloc(ACT_V, init_seed, TRUE, nullptr, 0, nullptr, LEVEL_HARROGATH, nullptr, nullptr);

			// Call both implementations
			sut(moo_pAct);
			original(original_pAct);

			// Input data can not be compared since it was freed
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B9D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetMemPoolFromAct, dll_base + 0x0004B9D0);
		
		SUBCASE("")
		{
			// Input data
			const auto mempool = (void*)random_unsigned_integer();

			D2DrlgActStrc moo_pAct{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [mempool](
				D2DrlgActStrc& pAct
			) {
				pAct.pMemPool = mempool;
			};

			setup_data(moo_pAct);
			setup_data(original_pAct);

			// Call both implementations
			const auto moo_result = (int)sut(&moo_pAct);
			const auto original_result = (int)original(&original_pAct);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8B9E0 (#10026)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ToggleRoomTilesEnableFlag, dll_base + 0x0004B9E0);

		SUBCASE("")
		{
			for (auto bEnabled : { FALSE, TRUE })
			{
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2RoomTileStrc moo_pRoomTiles[2]{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2RoomTileStrc original_pRoomTiles[2]{};

				const auto setup_data = [bEnabled](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2RoomTileStrc(& pRoomTiles)[2]
				) {
					pRoomTiles[0].bEnabled = !bEnabled;
					pRoomTiles[0].pNext = &pRoomTiles[1];
					pRoomTiles[1].bEnabled = !bEnabled;

					pDrlgRoom.pRoomTiles = &pRoomTiles[0];
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pRoomTiles);
				setup_data(original_pRoom, original_pDrlgRoom, original_pRoomTiles);

				// Call both implementations
				sut(&moo_pRoom, bEnabled);
				original(&original_pRoom, bEnabled);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

				// Check specific values
				for (auto i = 0; i < 2; ++i)
				{
					CHECK_EQ(moo_pRoomTiles[i].bEnabled, original_pRoomTiles[i].bEnabled);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BA20 (#10027)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetWarpTileFromRoomAndSourceLevelId, dll_base + 0x0004BA20);

		SUBCASE("")
		{
			// Input data
			const int source_level = random_unsigned_integer(1, 136);
			const int destination_level = random_unsigned_integer(1, 136);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2RoomTileStrc moo_pSourceRoomTile{};
			D2LvlWarpTxt moo_pSourceLvlWarp{};
			D2DrlgRoomStrc moo_pDestinationDrlgRoom{};
			D2RoomTileStrc moo_pDestinationRoomTile{};
			D2LvlWarpTxt moo_pDestinationLvlWarp{};
			D2ActiveRoomStrc moo_pDestinationRoom{};
			D2UnitStrc moo_pUnits[2]{};
			D2LvlWarpTxt* moo_ppLvlWarpTxtRecord{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2RoomTileStrc original_pSourceRoomTile{};
			D2LvlWarpTxt original_pSourceLvlWarp{};
			D2DrlgRoomStrc original_pDestinationDrlgRoom{};
			D2RoomTileStrc original_pDestinationRoomTile{};
			D2LvlWarpTxt original_pDestinationLvlWarp{};
			D2ActiveRoomStrc original_pDestinationRoom{};
			D2UnitStrc original_pUnits[2]{};
			D2LvlWarpTxt* original_ppLvlWarpTxtRecord{};
			int nSourceLevel = source_level;

			const auto setup_data = [source_level, destination_level](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2RoomTileStrc& pSourceRoomTile,
				D2LvlWarpTxt& pSourceLvlWarp,
				D2DrlgRoomStrc& pDestinationDrlgRoom,
				D2RoomTileStrc& pDestinationRoomTile,
				D2LvlWarpTxt& pDestinationLvlWarp,
				D2ActiveRoomStrc& pDestinationRoom,
				D2UnitStrc(& pUnits)[2]
			) {
				// The source room links to the destination room ...
				pSourceLvlWarp.dwLevelId = source_level;
				pSourceRoomTile.pLvlWarpTxtRecord = &pSourceLvlWarp;
				pSourceRoomTile.pDrlgRoom = &pDestinationDrlgRoom;
				pDrlgRoom.pRoomTiles = &pSourceRoomTile;
				pRoom.pDrlgRoom = &pDrlgRoom;

				// ... which links back to the source room
				pDestinationLvlWarp.dwLevelId = destination_level;
				pDestinationRoomTile.pLvlWarpTxtRecord = &pDestinationLvlWarp;
				pDestinationRoomTile.pDrlgRoom = &pDrlgRoom;
				pDestinationDrlgRoom.pRoomTiles = &pDestinationRoomTile;

				// The destination room is already active, so it doesn't have to be initialized
				pDestinationDrlgRoom.pRoom = &pDestinationRoom;
				pDestinationRoom.pDrlgRoom = &pDestinationDrlgRoom;

				// Only the second unit is the warp tile to the destination level
				pUnits[0].dwUnitType = UNIT_MONSTER;
				pUnits[0].dwClassId = destination_level;
				pUnits[0].pRoomNext = &pUnits[1];
				pUnits[1].dwUnitType = UNIT_TILE;
				pUnits[1].dwClassId = destination_level;
				pDestinationRoom.pUnitFirst = &pUnits[0];
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pSourceRoomTile, moo_pSourceLvlWarp, moo_pDestinationDrlgRoom, moo_pDestinationRoomTile, moo_pDestinationLvlWarp, moo_pDestinationRoom, moo_pUnits);
			setup_data(original_pRoom, original_pDrlgRoom, original_pSourceRoomTile, original_pSourceLvlWarp, original_pDestinationDrlgRoom, original_pDestinationRoomTile, original_pDestinationLvlWarp, original_pDestinationRoom, original_pUnits);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nSourceLevel, &moo_ppLvlWarpTxtRecord);
			const auto original_result = original(&original_pRoom, nSourceLevel, &original_ppLvlWarpTxtRecord);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_ppLvlWarpTxtRecord, original_ppLvlWarpTxtRecord, "Comparing ppLvlWarpTxtRecord");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pUnits[1]);
			CHECK_EQ(original_result, &original_pUnits[1]);
			CHECK_EQ(moo_ppLvlWarpTxtRecord, &moo_pDestinationLvlWarp);
			CHECK_EQ(original_ppLvlWarpTxtRecord, &original_pDestinationLvlWarp);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BAB0 (#10028)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetLvlWarpTxtRecordFromRoomAndUnit, dll_base + 0x0004BAB0);

		SUBCASE("")
		{
			for (auto i = 0; i < 4; ++i)
			{
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2RoomTileStrc moo_pRoomTiles[3]{};
				D2LvlWarpTxt moo_pLvlWarps[3]{};
				D2UnitStrc moo_pUnit{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2RoomTileStrc original_pRoomTiles[3]{};
				D2LvlWarpTxt original_pLvlWarps[3]{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2RoomTileStrc(& pRoomTiles)[3],
					D2LvlWarpTxt(& pLvlWarps)[3],
					D2UnitStrc& pUnit
				) {
					for (auto j = 0; j < 3; ++j)
					{
						pLvlWarps[j].dwLevelId = 10 * (j + 1);
						pRoomTiles[j].pLvlWarpTxtRecord = &pLvlWarps[j];
						// The second tile is disabled and must not be returned
						pRoomTiles[j].bEnabled = j != 1;
						pRoomTiles[j].pNext = j < 2 ? &pRoomTiles[j + 1] : nullptr;
					}

					pDrlgRoom.pRoomTiles = &pRoomTiles[0];
					pRoom.pDrlgRoom = &pDrlgRoom;

					// Class ids 10, 20, 30 and 40 (no matching tile)
					pUnit.dwUnitType = UNIT_TILE;
					pUnit.dwClassId = 10 * (i + 1);
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pRoomTiles, moo_pLvlWarps, moo_pUnit);
				setup_data(original_pRoom, original_pDrlgRoom, original_pRoomTiles, original_pLvlWarps, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom, &moo_pUnit);
				const auto original_result = original(&original_pRoom, &original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				// Check specific values
				CHECK_EQ(moo_result == nullptr ? -1 : moo_result - moo_pLvlWarps, original_result == nullptr ? -1 : original_result - original_pLvlWarps);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BAF0 (#10030)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetFloorTilesFromRoom, dll_base + 0x0004BAF0);

		SUBCASE("With room tiles")
		{
			// Input data
			const auto floors = random_unsigned_integer(1, 3);
			const auto pos_x = random_unsigned_integer(0, 100);
			const auto pos_y = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomTilesStrc moo_pRoomTiles{};
			D2DrlgTileDataStrc moo_pFloorTiles[3]{};
			int moo_pFloorCount{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomTilesStrc original_pRoomTiles{};
			D2DrlgTileDataStrc original_pFloorTiles[3]{};
			int original_pFloorCount{};

			const auto setup_data = [floors, pos_x, pos_y](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomTilesStrc& pRoomTiles,
				D2DrlgTileDataStrc(& pFloorTiles)[3]
			) {
				pFloorTiles[0].nPosX = pos_x;
				pFloorTiles[0].nPosY = pos_y;

				pRoomTiles.pFloorTiles = &pFloorTiles[0];
				pRoomTiles.nFloors = floors;
				pRoom.pRoomTiles = &pRoomTiles;
			};

			setup_data(moo_pRoom, moo_pRoomTiles, moo_pFloorTiles);
			setup_data(original_pRoom, original_pRoomTiles, original_pFloorTiles);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pFloorCount);
			const auto original_result = original(&original_pRoom, &original_pFloorCount);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pFloorCount, original_pFloorCount, "Comparing pFloorCount");
		}

		SUBCASE("Without room tiles")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			int moo_pFloorCount = 1;
			D2ActiveRoomStrc original_pRoom{};
			int original_pFloorCount = 1;

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pFloorCount);
			const auto original_result = original(&original_pRoom, &original_pFloorCount);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pFloorCount, original_pFloorCount, "Comparing pFloorCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BB20 (#10031)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetWallTilesFromRoom, dll_base + 0x0004BB20);

		SUBCASE("")
		{
			// Input data
			const auto walls = random_unsigned_integer(1, 3);
			const auto pos_x = random_unsigned_integer(0, 100);
			const auto pos_y = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomTilesStrc moo_pRoomTiles{};
			D2DrlgTileDataStrc moo_pWallTiles[3]{};
			int moo_pWallCount{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomTilesStrc original_pRoomTiles{};
			D2DrlgTileDataStrc original_pWallTiles[3]{};
			int original_pWallCount{};

			const auto setup_data = [walls, pos_x, pos_y](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomTilesStrc& pRoomTiles,
				D2DrlgTileDataStrc(& pWallTiles)[3]
			) {
				pWallTiles[0].nPosX = pos_x;
				pWallTiles[0].nPosY = pos_y;

				pRoomTiles.pWallTiles = &pWallTiles[0];
				pRoomTiles.nWalls = walls;
				pRoom.pRoomTiles = &pRoomTiles;
			};

			setup_data(moo_pRoom, moo_pRoomTiles, moo_pWallTiles);
			setup_data(original_pRoom, original_pRoomTiles, original_pWallTiles);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pWallCount);
			const auto original_result = original(&original_pRoom, &original_pWallCount);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pWallCount, original_pWallCount, "Comparing pWallCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BB60 (#10032)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoofTilesFromRoom, dll_base + 0x0004BB60);

		SUBCASE("")
		{
			// Input data
			const auto roofs = random_unsigned_integer(1, 3);
			const auto pos_x = random_unsigned_integer(0, 100);
			const auto pos_y = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomTilesStrc moo_pRoomTiles{};
			D2DrlgTileDataStrc moo_pRoofTiles[3]{};
			int moo_pRoofCount{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomTilesStrc original_pRoomTiles{};
			D2DrlgTileDataStrc original_pRoofTiles[3]{};
			int original_pRoofCount{};

			const auto setup_data = [roofs, pos_x, pos_y](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomTilesStrc& pRoomTiles,
				D2DrlgTileDataStrc(& pRoofTiles)[3]
			) {
				pRoofTiles[0].nPosX = pos_x;
				pRoofTiles[0].nPosY = pos_y;

				pRoomTiles.pRoofTiles = &pRoofTiles[0];
				pRoomTiles.nRoofs = roofs;
				pRoom.pRoomTiles = &pRoomTiles;
			};

			setup_data(moo_pRoom, moo_pRoomTiles, moo_pRoofTiles);
			setup_data(original_pRoom, original_pRoomTiles, original_pRoofTiles);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pRoofCount);
			const auto original_result = original(&original_pRoom, &original_pRoofCount);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pRoofCount, original_pRoofCount, "Comparing pRoofCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BBA0 (#10033)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetTileDataFromAct, dll_base + 0x0004BBA0);

		SUBCASE("")
		{
			// Input data
			const auto width = random_unsigned_integer(0, 100);
			const auto height = random_unsigned_integer(0, 100);
			const auto flags = random_unsigned_integer();

			D2DrlgActStrc moo_pAct{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [width, height, flags](
				D2DrlgActStrc& pAct
			) {
				pAct.pTileData.nWidth = width;
				pAct.pTileData.nHeight = height;
				pAct.pTileData.dwFlags = flags;
			};

			setup_data(moo_pAct);
			setup_data(original_pAct);

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pAct.pTileData);
			CHECK_EQ(original_result, &original_pAct.pTileData);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BBB0 (#10034)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomCoordinates, dll_base + 0x0004BBB0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordsStrc coords{};
			coords.nSubtileX = random_unsigned_integer(0, 1000);
			coords.nSubtileY = random_unsigned_integer(0, 1000);
			coords.nSubtileWidth = random_unsigned_integer(0, 100);
			coords.nSubtileHeight = random_unsigned_integer(0, 100);
			coords.nTileXPos = random_unsigned_integer(0, 1000);
			coords.nTileYPos = random_unsigned_integer(0, 1000);
			coords.nTileWidth = random_unsigned_integer(0, 100);
			coords.nTileHeight = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgCoordsStrc moo_pCoords{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgCoordsStrc original_pCoords{};

			const auto setup_data = [coords](
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.tCoords = coords;
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			sut(&moo_pRoom, &moo_pCoords);
			original(&original_pRoom, &original_pCoords);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pCoords, original_pCoords, "Comparing pCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BC10 (#10035)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetAdjacentRoomsListFromRoom, dll_base + 0x0004BC10);

		SUBCASE("")
		{
			// Input data
			const auto adjacent_rooms = random_unsigned_integer(1, 3);
			const auto allies = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc moo_pAdjacentRooms[3]{};
			D2ActiveRoomStrc* moo_pRoomList[3]{};
			D2ActiveRoomStrc** moo_pppRoomList{};
			int moo_pNumRooms{};
			D2ActiveRoomStrc original_pRoom{};
			D2ActiveRoomStrc original_pAdjacentRooms[3]{};
			D2ActiveRoomStrc* original_pRoomList[3]{};
			D2ActiveRoomStrc** original_pppRoomList{};
			int original_pNumRooms{};

			const auto setup_data = [adjacent_rooms, allies](
				D2ActiveRoomStrc& pRoom,
				D2ActiveRoomStrc(& pAdjacentRooms)[3],
				D2ActiveRoomStrc*(& pRoomList)[3]
			) {
				for (auto i = 0; i < 3; ++i)
				{
					pAdjacentRooms[i].nAllies = allies + i;
					pRoomList[i] = &pAdjacentRooms[i];
				}

				pRoom.ppRoomList = &pRoomList[0];
				pRoom.nNumRooms = adjacent_rooms;
			};

			setup_data(moo_pRoom, moo_pAdjacentRooms, moo_pRoomList);
			setup_data(original_pRoom, original_pAdjacentRooms, original_pRoomList);

			// Call both implementations
			sut(&moo_pRoom, &moo_pppRoomList, &moo_pNumRooms);
			original(&original_pRoom, &original_pppRoomList, &original_pNumRooms);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pNumRooms, original_pNumRooms, "Comparing pNumRooms");

			// Check specific values
			CHECK_EQ(moo_pppRoomList, &moo_pRoomList[0]);
			CHECK_EQ(original_pppRoomList, &original_pRoomList[0]);

			for (auto i = 0; i < original_pNumRooms; ++i)
			{
				MOO_CHECK_EQ(moo_pppRoomList[i], original_pppRoomList[i], "Comparing pppRoomList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BC50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AllocRoom, dll_base + 0x0004BC50);

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordsStrc coords{};
			coords.nSubtileX = 5 * random_unsigned_integer(0, 200);
			coords.nSubtileY = 5 * random_unsigned_integer(0, 200);
			coords.nSubtileWidth = 5 * random_unsigned_integer(1, 8);
			coords.nSubtileHeight = 5 * random_unsigned_integer(1, 8);
			coords.nTileXPos = coords.nSubtileX / 5;
			coords.nTileYPos = coords.nSubtileY / 5;
			coords.nTileWidth = coords.nSubtileWidth / 5;
			coords.nTileHeight = coords.nSubtileHeight / 5;

			D2DrlgActStrc moo_pAct{};
			D2ActiveRoomStrc moo_pPreviousRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgCoordsStrc moo_pDrlgCoords{};
			D2DrlgRoomTilesStrc moo_pRoomTiles{};
			D2DrlgActStrc original_pAct{};
			D2ActiveRoomStrc original_pPreviousRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			D2DrlgCoordsStrc original_pDrlgCoords{};
			D2DrlgRoomTilesStrc original_pRoomTiles{};
			int nLowSeed = random_unsigned_integer();
			uint32_t dwFlags = random_unsigned_integer();

			const auto setup_data = [coords](
				D2DrlgActStrc& pAct,
				D2ActiveRoomStrc& pPreviousRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc*(& ppRoomsNear)[1],
				D2DrlgCoordsStrc& pDrlgCoords
			) {
				// The act already contains a room, the new one is expected to be prepended
				pAct.pRoom = &pPreviousRoom;

				// A room is always near itself
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = &ppRoomsNear[0];
				pDrlgRoom.nRoomsNear = 1;

				pDrlgCoords = coords;
			};

			setup_data(moo_pAct, moo_pPreviousRoom, moo_pDrlgRoom, moo_ppRoomsNear, moo_pDrlgCoords);
			setup_data(original_pAct, original_pPreviousRoom, original_pDrlgRoom, original_ppRoomsNear, original_pDrlgCoords);

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, &moo_pDrlgRoom, &moo_pDrlgCoords, &moo_pRoomTiles, nLowSeed, dwFlags);
			const auto original_result = original(&original_pAct, &original_pDrlgRoom, &original_pDrlgCoords, &original_pRoomTiles, nLowSeed, dwFlags);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
			MOO_CHECK_EQ(moo_pRoomTiles, original_pRoomTiles, "Comparing pRoomTiles");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pRoom, moo_result);
			CHECK_EQ(original_pDrlgRoom.pRoom, original_result);
			CHECK_EQ(moo_result->ppRoomList[0], moo_result);
			CHECK_EQ(original_result->ppRoomList[0], original_result);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BD90 (#10040)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_DoRoomsTouchOrOverlap, dll_base + 0x0004BD90);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordsStrc first_coords{};
			first_coords.nTileXPos = random_unsigned_integer(0, 20);
			first_coords.nTileYPos = random_unsigned_integer(0, 20);
			first_coords.nTileWidth = random_unsigned_integer(0, 10);
			first_coords.nTileHeight = random_unsigned_integer(0, 10);

			D2DrlgCoordsStrc second_coords{};
			second_coords.nTileXPos = random_unsigned_integer(0, 20);
			second_coords.nTileYPos = random_unsigned_integer(0, 20);
			second_coords.nTileWidth = random_unsigned_integer(0, 10);
			second_coords.nTileHeight = random_unsigned_integer(0, 10);

			D2ActiveRoomStrc moo_ptFirst{};
			D2ActiveRoomStrc moo_ptSecond{};
			D2ActiveRoomStrc original_ptFirst{};
			D2ActiveRoomStrc original_ptSecond{};

			const auto setup_data = [first_coords, second_coords](
				D2ActiveRoomStrc& ptFirst,
				D2ActiveRoomStrc& ptSecond
			) {
				ptFirst.tCoords = first_coords;
				ptSecond.tCoords = second_coords;
			};

			setup_data(moo_ptFirst, moo_ptSecond);
			setup_data(original_ptFirst, original_ptSecond);

			// Call both implementations
			const auto moo_result = sut(&moo_ptFirst, &moo_ptSecond);
			const auto original_result = original(&original_ptFirst, &original_ptSecond);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ptFirst, original_ptFirst, "Comparing ptFirst");
			MOO_CHECK_EQ(moo_ptSecond, original_ptSecond, "Comparing ptSecond");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BE30 (#10043)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AreTileCoordinatesInsideRoom, dll_base + 0x0004BE30);

		SUBCASE("")
		{
			for (auto x = 8; x < 18; ++x)
			{
				for (auto y = 8; y < 18; ++y)
				{
					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2ActiveRoomStrc original_pRoom{};
					int nX = x;
					int nY = y;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom
					) {
						pRoom.tCoords.nTileXPos = 10;
						pRoom.tCoords.nTileYPos = 11;
						pRoom.tCoords.nTileWidth = 5;
						pRoom.tCoords.nTileHeight = 4;
					};

					setup_data(moo_pRoom);
					setup_data(original_pRoom);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX, nY);
					const auto original_result = original(&original_pRoom, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BE90 (#10048)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_CheckRoomsOverlapping_BROKEN, dll_base + 0x0004BE90);

		SUBCASE("")
		{
			for (auto width = 0; width < 3; ++width)
			{
				for (auto height = 0; height < 3; ++height)
				{
					// Input data
					const auto pos_x = random_unsigned_integer(0, 1000);
					const auto pos_y = random_unsigned_integer(0, 1000);

					D2ActiveRoomStrc moo_pPrimary{};
					D2ActiveRoomStrc moo_pSecondary{};
					D2ActiveRoomStrc original_pPrimary{};
					D2ActiveRoomStrc original_pSecondary{};

					const auto setup_data = [width, height, pos_x, pos_y](
						D2ActiveRoomStrc& pPrimary
					) {
						pPrimary.tCoords.nTileXPos = pos_x;
						pPrimary.tCoords.nTileYPos = pos_y;
						pPrimary.tCoords.nTileWidth = width;
						pPrimary.tCoords.nTileHeight = height;
					};

					setup_data(moo_pPrimary);
					setup_data(original_pPrimary);

					// Call both implementations
					const auto moo_result = sut(&moo_pPrimary, &moo_pSecondary);
					const auto original_result = original(&original_pPrimary, &original_pSecondary);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pPrimary, original_pPrimary, "Comparing pPrimary");
					MOO_CHECK_EQ(moo_pSecondary, original_pSecondary, "Comparing pSecondary");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Commmon.0x6FD8BF00 (#10051)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FindRoomByTileCoordinates, dll_base + 0x0004BF00);

		SUBCASE("")
		{
			for (auto x = 0; x < 32; x += 3)
			{
				for (auto y = 0; y < 12; y += 2)
				{
					// Input data
					D2DrlgActStrc moo_pAct{};
					D2ActiveRoomStrc moo_pRooms[3]{};
					D2DrlgActStrc original_pAct{};
					D2ActiveRoomStrc original_pRooms[3]{};
					int nX = x;
					int nY = y;

					const auto setup_data = [](
						D2DrlgActStrc& pAct,
						D2ActiveRoomStrc(& pRooms)[3]
					) {
						// Three rooms next to each other with a gap between the second and the third one
						for (auto i = 0; i < 3; ++i)
						{
							pRooms[i].tCoords.nTileXPos = 10 * i + (i == 2 ? 2 : 0);
							pRooms[i].tCoords.nTileYPos = 2;
							pRooms[i].tCoords.nTileWidth = 8;
							pRooms[i].tCoords.nTileHeight = 8;
							pRooms[i].pRoomNext = i < 2 ? &pRooms[i + 1] : nullptr;
						}

						pAct.pRoom = &pRooms[0];
					};

					setup_data(moo_pAct, moo_pRooms);
					setup_data(original_pAct, original_pRooms);

					// Call both implementations
					const auto moo_result = sut(&moo_pAct, nX, nY);
					const auto original_result = original(&original_pAct, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");

					// Check specific values
					CHECK_EQ(moo_result == nullptr ? -1 : moo_result - moo_pRooms, original_result == nullptr ? -1 : original_result - original_pRooms);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BF50 (#10050)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetAdjacentRoomByTileCoordinates, dll_base + 0x0004BF50);

		SUBCASE("")
		{
			for (auto x = 0; x < 32; x += 3)
			{
				for (auto y = 0; y < 12; y += 2)
				{
					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2ActiveRoomStrc moo_pAdjacentRooms[3]{};
					D2ActiveRoomStrc* moo_pRoomList[3]{};
					D2ActiveRoomStrc original_pRoom{};
					D2ActiveRoomStrc original_pAdjacentRooms[3]{};
					D2ActiveRoomStrc* original_pRoomList[3]{};
					int nX = x;
					int nY = y;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom,
						D2ActiveRoomStrc(& pAdjacentRooms)[3],
						D2ActiveRoomStrc*(& pRoomList)[3]
					) {
						// Three adjacent rooms next to each other with a gap between the second and the third one
						for (auto i = 0; i < 3; ++i)
						{
							pAdjacentRooms[i].tCoords.nTileXPos = 10 * i + (i == 2 ? 2 : 0);
							pAdjacentRooms[i].tCoords.nTileYPos = 2;
							pAdjacentRooms[i].tCoords.nTileWidth = 8;
							pAdjacentRooms[i].tCoords.nTileHeight = 8;
							pRoomList[i] = &pAdjacentRooms[i];
						}

						pRoom.ppRoomList = &pRoomList[0];
						pRoom.nNumRooms = 3;
					};

					setup_data(moo_pRoom, moo_pAdjacentRooms, moo_pRoomList);
					setup_data(original_pRoom, original_pAdjacentRooms, original_pRoomList);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX, nY);
					const auto original_result = original(&original_pRoom, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

					// Check specific values
					CHECK_EQ(moo_result == nullptr ? -1 : moo_result - moo_pAdjacentRooms, original_result == nullptr ? -1 : original_result - original_pAdjacentRooms);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8BFF0 (#10049)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_CallRoomCallback, dll_base + 0x0004BFF0);

		SUBCASE("")
		{
			for (auto i = 1; i <= 4; ++i)
			{
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc moo_pAdjacentRooms[3]{};
				D2ActiveRoomStrc* moo_pRoomList[3]{};
				int moo_nRemainingCalls = i;
				D2ActiveRoomStrc original_pRoom{};
				D2ActiveRoomStrc original_pAdjacentRooms[3]{};
				D2ActiveRoomStrc* original_pRoomList[3]{};
				int original_nRemainingCalls = i;
				ROOMCALLBACKFN pfnRoomCallback = IncreaseAlliedCountUntilNoCallsRemain;
				void* moo_pArgs = &moo_nRemainingCalls;
				void* original_pArgs = &original_nRemainingCalls;

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom,
					D2ActiveRoomStrc(& pAdjacentRooms)[3],
					D2ActiveRoomStrc*(& pRoomList)[3]
				) {
					for (auto j = 0; j < 3; ++j)
					{
						pRoomList[j] = &pAdjacentRooms[j];
					}

					pRoom.ppRoomList = &pRoomList[0];
					pRoom.nNumRooms = 3;
				};

				setup_data(moo_pRoom, moo_pAdjacentRooms, moo_pRoomList);
				setup_data(original_pRoom, original_pAdjacentRooms, original_pRoomList);

				// Call both implementations
				sut(&moo_pRoom, pfnRoomCallback, moo_pArgs);
				original(&original_pRoom, pfnRoomCallback, original_pArgs);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_nRemainingCalls, original_nRemainingCalls, "Comparing pArgs");

				for (auto j = 0; j < 3; ++j)
				{
					MOO_CHECK_EQ(moo_pAdjacentRooms[j], original_pAdjacentRooms[j], "Comparing pAdjacentRooms");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C080 (#10052)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10052, dll_base + 0x0004C080);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto pos_x = random_unsigned_integer(0, 1000);
			const auto pos_y = random_unsigned_integer(0, 1000);
			const auto width = random_unsigned_integer(0, 64);
			const auto height = random_unsigned_integer(0, 64);

			D2ActiveRoomStrc moo_pRoom{};
			RECT moo_pRect{};
			D2ActiveRoomStrc original_pRoom{};
			RECT original_pRect{};

			const auto setup_data = [pos_x, pos_y, width, height](
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.tCoords.nTileXPos = pos_x;
				pRoom.tCoords.nTileYPos = pos_y;
				pRoom.tCoords.nTileWidth = width;
				pRoom.tCoords.nTileHeight = height;
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			sut(&moo_pRoom, &moo_pRect);
			original(&original_pRoom, &original_pRect);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pRect, original_pRect, "Comparing pRect");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C170 (#10053)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetSubtileRect, dll_base + 0x0004C170);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto subtile_x = random_unsigned_integer(0, 5000);
			const auto subtile_y = random_unsigned_integer(0, 5000);
			const auto subtile_width = random_unsigned_integer(0, 320);
			const auto subtile_height = random_unsigned_integer(0, 320);

			D2ActiveRoomStrc moo_pRoom{};
			RECT moo_pRect{};
			D2ActiveRoomStrc original_pRoom{};
			RECT original_pRect{};

			const auto setup_data = [subtile_x, subtile_y, subtile_width, subtile_height](
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.tCoords.nSubtileX = subtile_x;
				pRoom.tCoords.nSubtileY = subtile_y;
				pRoom.tCoords.nSubtileWidth = subtile_width;
				pRoom.tCoords.nSubtileHeight = subtile_height;
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			sut(&moo_pRoom, &moo_pRect);
			original(&original_pRoom, &original_pRect);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pRect, original_pRect, "Comparing pRect");
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD8C210 (#10054)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRGB_IntensityFromRoom, dll_base + 0x0004C210);

		SUBCASE("")
		{
			for (auto i = 0; i < levels_record_count; ++i)
			{
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgLevelStrc moo_pLevel{};
				uint8_t moo_pIntensity{};
				uint8_t moo_pRed{};
				uint8_t moo_pGreen{};
				uint8_t moo_pBlue{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgLevelStrc original_pLevel{};
				uint8_t original_pIntensity{};
				uint8_t original_pRed{};
				uint8_t original_pGreen{};
				uint8_t original_pBlue{};

				const auto setup_data = [i](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgLevelStrc& pLevel
				) {
					pLevel.nLevelId = i;
					pDrlgRoom.pLevel = &pLevel;
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pLevel);
				setup_data(original_pRoom, original_pDrlgRoom, original_pLevel);

				// Call both implementations
				sut(&moo_pRoom, &moo_pIntensity, &moo_pRed, &moo_pGreen, &moo_pBlue);
				original(&original_pRoom, &original_pIntensity, &original_pRed, &original_pGreen, &original_pBlue);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_pIntensity, original_pIntensity, "Comparing pIntensity");
				MOO_CHECK_EQ(moo_pRed, original_pRed, "Comparing pRed");
				MOO_CHECK_EQ(moo_pGreen, original_pGreen, "Comparing pGreen");
				MOO_CHECK_EQ(moo_pBlue, original_pBlue, "Comparing pBlue");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C240 (#10041)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FindRoomBySubtileCoordinates, dll_base + 0x0004C240);

		SUBCASE("")
		{
			for (auto x = 0; x < 160; x += 7)
			{
				for (auto y = 0; y < 60; y += 6)
				{
					// Input data
					D2DrlgActStrc moo_pAct{};
					D2ActiveRoomStrc moo_pRooms[3]{};
					D2DrlgActStrc original_pAct{};
					D2ActiveRoomStrc original_pRooms[3]{};
					int nX = x;
					int nY = y;

					const auto setup_data = [](
						D2DrlgActStrc& pAct,
						D2ActiveRoomStrc(& pRooms)[3]
					) {
						// Three rooms next to each other with a gap between the second and the third one
						for (auto i = 0; i < 3; ++i)
						{
							pRooms[i].tCoords.nSubtileX = 50 * i + (i == 2 ? 10 : 0);
							pRooms[i].tCoords.nSubtileY = 10;
							pRooms[i].tCoords.nSubtileWidth = 40;
							pRooms[i].tCoords.nSubtileHeight = 40;
							pRooms[i].pRoomNext = i < 2 ? &pRooms[i + 1] : nullptr;
						}

						pAct.pRoom = &pRooms[0];
					};

					setup_data(moo_pAct, moo_pRooms);
					setup_data(original_pAct, original_pRooms);

					// Call both implementations
					const auto moo_result = sut(&moo_pAct, nX, nY);
					const auto original_result = original(&original_pAct, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");

					// Check specific values
					CHECK_EQ(moo_result == nullptr ? -1 : moo_result - moo_pRooms, original_result == nullptr ? -1 : original_result - original_pRooms);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C290")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AreSubtileCoordinatesInsideRoom, dll_base + 0x0004C290);

		SUBCASE("")
		{
			for (auto x = 40; x < 90; x += 3)
			{
				for (auto y = 40; y < 90; y += 3)
				{
					// Input data
					D2DrlgCoordsStrc moo_pDrlgCoords{};
					D2DrlgCoordsStrc original_pDrlgCoords{};
					int nX = x;
					int nY = y;

					const auto setup_data = [](
						D2DrlgCoordsStrc& pDrlgCoords
					) {
						pDrlgCoords.nSubtileX = 50;
						pDrlgCoords.nSubtileY = 55;
						pDrlgCoords.nSubtileWidth = 25;
						pDrlgCoords.nSubtileHeight = 20;
					};

					setup_data(moo_pDrlgCoords);
					setup_data(original_pDrlgCoords);

					// Call both implementations
					const auto moo_result = sut(&moo_pDrlgCoords, nX, nY);
					const auto original_result = original(&original_pDrlgCoords, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pDrlgCoords, original_pDrlgCoords, "Comparing pDrlgCoords");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD8C2F0 (#10046)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FindActSpawnLocation, dll_base + 0x0004C2F0);

		SUBCASE("")
		{
			// Input data
			// Make the level spawn at its waypoint, so that no level generation is needed
			leveldefs_txt[LEVEL_ROGUEENCAMPMENT].dwPosition = 0;

			D2DrlgActStrc moo_pAct{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			int moo_pX{};
			int moo_pY{};
			D2DrlgActStrc original_pAct{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			int original_pX{};
			int original_pY{};
			int nLevelId = LEVEL_ROGUEENCAMPMENT;
			int nTileIndex = 0;

			const auto setup_data = [](
				D2DrlgActStrc& pAct,
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2ActiveRoomStrc& pRoom
			) {
				pAct.pDrlg = &pDrlg;

				// The level is already initialized and has a waypoint room
				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
				pLevel.pDrlg = &pDrlg;
				pLevel.pFirstRoomEx = &pDrlgRoom;
				pDrlg.pLevel = &pLevel;

				// The tile library is already loaded and the room is already active, so no further initialization is needed
				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nType = DRLGTYPE_OUTDOOR;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_HAS_WAYPOINT | DRLGROOMFLAG_TILELIB_LOADED;
				pDrlgRoom.nTileXPos = 10;
				pDrlgRoom.nTileYPos = 12;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 6;
				pDrlgRoom.pRoom = &pRoom;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pAct, moo_pDrlg, moo_pLevel, moo_pDrlgRoom, moo_pRoom);
			setup_data(original_pAct, original_pDrlg, original_pLevel, original_pDrlgRoom, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nLevelId, nTileIndex, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pAct, nLevelId, nTileIndex, &original_pX, &original_pY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pRoom);
			CHECK_EQ(original_result, &original_pRoom);
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD8C340 (#10045)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FindActSpawnLocationEx, dll_base + 0x0004C340);

		SUBCASE("")
		{
			// Input data
			// Make the level spawn at its waypoint, so that no level generation is needed
			leveldefs_txt[LEVEL_ROGUEENCAMPMENT].dwPosition = 0;

			D2DrlgActStrc moo_pAct{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[40 * 30]{};
			int moo_pX{};
			int moo_pY{};
			D2DrlgActStrc original_pAct{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[40 * 30]{};
			int original_pX{};
			int original_pY{};
			int nLevelId = LEVEL_ROGUEENCAMPMENT;
			int nTileIndex = 0;
			int nUnitSize = COLLISION_UNIT_SIZE_POINT;

			const auto setup_data = [](
				D2DrlgActStrc& pAct,
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(& pCollisionMask)[40 * 30]
			) {
				pAct.pDrlg = &pDrlg;

				// The level is already initialized and has a waypoint room
				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
				pLevel.pDrlg = &pDrlg;
				pLevel.pFirstRoomEx = &pDrlgRoom;
				pDrlg.pLevel = &pLevel;

				// The tile library is already loaded and the room is already active, so no further initialization is needed
				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nType = DRLGTYPE_OUTDOOR;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_HAS_WAYPOINT | DRLGROOMFLAG_TILELIB_LOADED;
				pDrlgRoom.nTileXPos = 10;
				pDrlgRoom.nTileYPos = 12;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 6;
				pDrlgRoom.pRoom = &pRoom;

				pRoom.pDrlgRoom = &pDrlgRoom;
				pRoom.tCoords.nTileXPos = 10;
				pRoom.tCoords.nTileYPos = 12;
				pRoom.tCoords.nTileWidth = 8;
				pRoom.tCoords.nTileHeight = 6;
				pRoom.tCoords.nSubtileX = 50;
				pRoom.tCoords.nSubtileY = 60;
				pRoom.tCoords.nSubtileWidth = 40;
				pRoom.tCoords.nSubtileHeight = 30;

				// Block the subtile in the center of the room, so that the next free subtile has to be found
				pCollisionMask[(14 * 5 + 3 - 50) + (15 * 5 + 3 - 60) * 40] = COLLIDE_WALL;
				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = &pCollisionMask[0];
				pRoom.pCollisionGrid = &pCollisionGrid;
			};

			setup_data(moo_pAct, moo_pDrlg, moo_pLevel, moo_pDrlgRoom, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pAct, original_pDrlg, original_pLevel, original_pDrlgRoom, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nLevelId, nTileIndex, &moo_pX, &moo_pY, nUnitSize);
			const auto original_result = original(&original_pAct, nLevelId, nTileIndex, &original_pX, &original_pY, nUnitSize);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pRoom);
			CHECK_EQ(original_result, &original_pRoom);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C4A0 (#10029)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetFirstUnitInRoom, dll_base + 0x0004C4A0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			uint32_t coords_y[3]{};
			for (auto i = 0; i < 3; ++i)
			{
				coords_y[i] = random_unsigned_integer(0, 1000);
			}

			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnits[3]{};
			D2DynamicPathStrc moo_pDynamicPaths[3]{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnits[3]{};
			D2DynamicPathStrc original_pDynamicPaths[3]{};

			const auto setup_data = [coords_y](
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc(& pUnits)[3],
				D2DynamicPathStrc(& pDynamicPaths)[3]
			) {
				for (auto i = 0; i < 3; ++i)
				{
					pDynamicPaths[i].dwClientCoordY = coords_y[i];
					pUnits[i].dwUnitType = UNIT_MONSTER;
					pUnits[i].pDynamicPath = &pDynamicPaths[i];
					pUnits[i].pRoomNext = i < 2 ? &pUnits[i + 1] : nullptr;
				}

				pRoom.pUnitFirst = &pUnits[0];
			};

			setup_data(moo_pRoom, moo_pUnits, moo_pDynamicPaths);
			setup_data(original_pRoom, original_pUnits, original_pDynamicPaths);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C4E0 (#10100)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_IncreaseAlliedCountOfRoom, dll_base + 0x0004C4E0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto allies = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [allies](
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.nAllies = allies;
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Comon.0x6FD8C4F0 (#10036)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetAlliedCountFromRoom, dll_base + 0x0004C4F0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto allies = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [allies](
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.nAllies = allies;
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C510 (#10101)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_DecreaseAlliedCountOfRoom, dll_base + 0x0004C510);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto allies = random_unsigned_integer(1, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [allies](
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.nAllies = allies;
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C550")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetUnitListFromRoom, dll_base + 0x0004C550);

		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_id](
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.dwUnitId = unit_id;
				pRoom.pUnitFirst = &pUnit;
			};

			setup_data(moo_pRoom, moo_pUnit);
			setup_data(original_pRoom, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(*moo_result, *original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pRoom.pUnitFirst);
			CHECK_EQ(original_result, &original_pRoom.pUnitFirst);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C580")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetUnitUpdateListFromRoom, dll_base + 0x0004C580);

		SUBCASE("")
		{
			for (auto bUpdate : { FALSE, TRUE })
			{
				// Input data
				const auto unit_id = random_unsigned_integer();

				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgActStrc moo_pAct{};
				D2UnitStrc moo_pUnit{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgActStrc original_pAct{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [unit_id](
					D2ActiveRoomStrc& pRoom,
					D2DrlgActStrc& pAct,
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwUnitId = unit_id;
					pRoom.pUnitUpdate = &pUnit;
					pRoom.pAct = &pAct;
				};

				setup_data(moo_pRoom, moo_pAct, moo_pUnit);
				setup_data(original_pRoom, original_pAct, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom, bUpdate);
				const auto original_result = original(&original_pRoom, bUpdate);

				// Compare return values
				MOO_CHECK_EQ(*moo_result, *original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

				// Check specific values
				CHECK_EQ(moo_result, &moo_pRoom.pUnitUpdate);
				CHECK_EQ(original_result, &original_pRoom.pUnitUpdate);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C5C0 (#10055)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetPresetUnitsFromRoom, dll_base + 0x0004C5C0);

		SUBCASE("")
		{
			for (uint32_t flags : { 0u, (uint32_t)DRLGROOMFLAG_AUTOMAP_REVEAL, (uint32_t)DRLGROOMFLAG_PRESET_UNITS_SPAWNED, (uint32_t)(DRLGROOMFLAG_AUTOMAP_REVEAL | DRLGROOMFLAG_PRESET_UNITS_SPAWNED) })
			{
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2PresetUnitStrc moo_pPresetUnit{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2PresetUnitStrc original_pPresetUnit{};

				const auto setup_data = [flags](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2PresetUnitStrc& pPresetUnit
				) {
					pDrlgRoom.dwFlags = flags;
					pDrlgRoom.pPresetUnits = &pPresetUnit;
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pPresetUnit);
				setup_data(original_pRoom, original_pDrlgRoom, original_pPresetUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom);
				const auto original_result = original(&original_pRoom);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

				// Check specific values
				CHECK_EQ(moo_result == &moo_pPresetUnit, original_result == &original_pPresetUnit);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C600")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetCollisionGridFromRoom, dll_base + 0x0004C600);

		SUBCASE("")
		{
			// Input data
			const auto subtile_x = random_unsigned_integer(0, 5000);
			const auto subtile_y = random_unsigned_integer(0, 5000);

			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};

			const auto setup_data = [subtile_x, subtile_y](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid
			) {
				pCollisionGrid.pRoomCoords.nSubtileX = subtile_x;
				pCollisionGrid.pRoomCoords.nSubtileY = subtile_y;
				pRoom.pCollisionGrid = &pCollisionGrid;
			};

			setup_data(moo_pRoom, moo_pCollisionGrid);
			setup_data(original_pRoom, original_pCollisionGrid);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pCollisionGrid);
			CHECK_EQ(original_result, &original_pCollisionGrid);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C630")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_SetCollisionGridInRoom, dll_base + 0x0004C630);

		SUBCASE("")
		{
			// Input data
			const auto subtile_x = random_unsigned_integer(0, 5000);
			const auto subtile_y = random_unsigned_integer(0, 5000);

			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};

			const auto setup_data = [subtile_x, subtile_y](
				D2RoomCollisionGridStrc& pCollisionGrid
			) {
				pCollisionGrid.pRoomCoords.nSubtileX = subtile_x;
				pCollisionGrid.pRoomCoords.nSubtileY = subtile_y;
			};

			setup_data(moo_pCollisionGrid);
			setup_data(original_pCollisionGrid);

			// Call both implementations
			sut(&moo_pRoom, &moo_pCollisionGrid);
			original(&original_pRoom, &original_pCollisionGrid);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pCollisionGrid, original_pCollisionGrid, "Comparing pCollisionGrid");

			// Check specific values
			CHECK_EQ(moo_pRoom.pCollisionGrid, &moo_pCollisionGrid);
			CHECK_EQ(original_pRoom.pCollisionGrid, &original_pCollisionGrid);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C660 (#10063)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_SetClientIsInSight, dll_base + 0x0004C660);

		SUBCASE("")
		{
			// Input data
			D2DrlgActStrc moo_pAct{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc original_pAct{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			D2ActiveRoomStrc original_pRoom{};
			int nLevelId = LEVEL_ROGUEENCAMPMENT;
			int nX = 14;
			int nY = 15;

			const auto setup_data = [](
				D2DrlgActStrc& pAct,
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc*(& ppRoomsNear)[1],
				D2ActiveRoomStrc& pRoom
			) {
				for (auto i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pDrlg.pLevel = &pLevel;
				pAct.pDrlg = &pDrlg;

				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
				pLevel.pDrlg = &pDrlg;
				pLevel.pFirstRoomEx = &pDrlgRoom;

				// The room has no status yet, its tile library is already loaded and it is already active
				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nType = DRLGTYPE_OUTDOOR;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED;
				pDrlgRoom.fRoomStatus = ROOMSTATUS_COUNT;
				pDrlgRoom.nTileXPos = 10;
				pDrlgRoom.nTileYPos = 12;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 6;
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = &ppRoomsNear[0];
				pDrlgRoom.nRoomsNear = 1;
				pDrlgRoom.pRoom = &pRoom;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pAct, moo_pDrlg, moo_pLevel, moo_pDrlgRoom, moo_ppRoomsNear, moo_pRoom);
			setup_data(original_pAct, original_pDrlg, original_pLevel, original_pDrlgRoom, original_ppRoomsNear, original_pRoom);

			// Call both implementations
			sut(&moo_pAct, nLevelId, nX, nY, &moo_pRoom);
			original(&original_pAct, nLevelId, nX, nY, &original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pStatusNext, &moo_pDrlg.tStatusRoomsLists[moo_pDrlgRoom.fRoomStatus]);
			CHECK_EQ(original_pDrlgRoom.pStatusNext, &original_pDrlg.tStatusRoomsLists[original_pDrlgRoom.fRoomStatus]);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C6B0 (#10064)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UnsetClientIsInSight, dll_base + 0x0004C6B0);

		SUBCASE("")
		{
			// Input data
			D2DrlgActStrc moo_pAct{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc original_pAct{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			D2ActiveRoomStrc original_pRoom{};
			int nLevelId = LEVEL_ROGUEENCAMPMENT;
			int nX = 14;
			int nY = 15;

			const auto setup_data = [](
				D2DrlgActStrc& pAct,
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc*(& ppRoomsNear)[1],
				D2ActiveRoomStrc& pRoom
			) {
				for (auto i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pDrlg.pLevel = &pLevel;
				pAct.pDrlg = &pDrlg;

				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
				pLevel.pDrlg = &pDrlg;
				pLevel.pFirstRoomEx = &pDrlgRoom;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nType = DRLGTYPE_OUTDOOR;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED;
				pDrlgRoom.nTileXPos = 10;
				pDrlgRoom.nTileYPos = 12;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 6;
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = &ppRoomsNear[0];
				pDrlgRoom.nRoomsNear = 1;
				pDrlgRoom.pRoom = &pRoom;
				pRoom.pDrlgRoom = &pDrlgRoom;

				// The room is in sight of a client (same state as after DUNGEON_SetClientIsInSight)
				pDrlgRoom.fRoomStatus = ROOMSTATUS_CLIENT_IN_SIGHT;
				pDrlgRoom.wRoomsInList[ROOMSTATUS_CLIENT_IN_SIGHT] = 1;
				pDrlgRoom.wRoomsInList[ROOMSTATUS_CLIENT_OUT_OF_SIGHT] = 1;
				pDrlgRoom.wRoomsInList[ROOMSTATUS_UNTILE] = 1;

				D2DrlgRoomStrc& pStatusRoomsListHead = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_SIGHT];
				pDrlgRoom.pStatusNext = &pStatusRoomsListHead;
				pDrlgRoom.pStatusPrev = pStatusRoomsListHead.pStatusPrev;
				pStatusRoomsListHead.pStatusPrev->pStatusNext = &pDrlgRoom;
				pStatusRoomsListHead.pStatusPrev = &pDrlgRoom;
			};

			setup_data(moo_pAct, moo_pDrlg, moo_pLevel, moo_pDrlgRoom, moo_ppRoomsNear, moo_pRoom);
			setup_data(original_pAct, original_pDrlg, original_pLevel, original_pDrlgRoom, original_ppRoomsNear, original_pRoom);

			// Call both implementations
			sut(&moo_pAct, nLevelId, nX, nY, &moo_pRoom);
			original(&original_pAct, nLevelId, nX, nY, &original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pStatusNext == nullptr, original_pDrlgRoom.pStatusNext == nullptr);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C700 (#10062)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_ChangeClientRoom, dll_base + 0x0004C700);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRooms[2]{};
			D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
			D2ActiveRoomStrc moo_pRoom1{};
			D2ActiveRoomStrc moo_pRoom2{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRooms[2]{};
			D2DrlgRoomStrc* original_ppRoomsNear[2]{};
			D2ActiveRoomStrc original_pRoom1{};
			D2ActiveRoomStrc original_pRoom2{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc(& pDrlgRooms)[2],
				D2DrlgRoomStrc*(& ppRoomsNear)[2],
				D2ActiveRoomStrc& pRoom1,
				D2ActiveRoomStrc& pRoom2
			) {
				for (auto i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pDrlg.pLevel = &pLevel;

				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
				pLevel.pDrlg = &pDrlg;
				pLevel.pFirstRoomEx = &pDrlgRooms[0];

				D2ActiveRoomStrc* pRooms[2] = { &pRoom1, &pRoom2 };
				for (auto i = 0; i < 2; ++i)
				{
					// Both rooms have their tile library loaded, are already active and are only near to themselves
					pDrlgRooms[i].pLevel = &pLevel;
					pDrlgRooms[i].nType = DRLGTYPE_OUTDOOR;
					pDrlgRooms[i].dwFlags = DRLGROOMFLAG_TILELIB_LOADED;
					pDrlgRooms[i].nTileXPos = 10 + 8 * i;
					pDrlgRooms[i].nTileYPos = 12;
					pDrlgRooms[i].nTileWidth = 8;
					pDrlgRooms[i].nTileHeight = 6;
					ppRoomsNear[i] = &pDrlgRooms[i];
					pDrlgRooms[i].ppRoomsNear = &ppRoomsNear[i];
					pDrlgRooms[i].nRoomsNear = 1;
					pDrlgRooms[i].pDrlgRoomNext = i < 1 ? &pDrlgRooms[i + 1] : nullptr;
					pDrlgRooms[i].pRoom = pRooms[i];
					pRooms[i]->pDrlgRoom = &pDrlgRooms[i];
				}

				// The client is currently in the first room, the second room has no status yet
				pDrlgRooms[0].fRoomStatus = ROOMSTATUS_CLIENT_IN_ROOM;
				for (auto i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlgRooms[0].wRoomsInList[i] = 1;
				}

				D2DrlgRoomStrc& pStatusRoomsListHead = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_ROOM];
				pDrlgRooms[0].pStatusNext = &pStatusRoomsListHead;
				pDrlgRooms[0].pStatusPrev = pStatusRoomsListHead.pStatusPrev;
				pStatusRoomsListHead.pStatusPrev->pStatusNext = &pDrlgRooms[0];
				pStatusRoomsListHead.pStatusPrev = &pDrlgRooms[0];

				pDrlgRooms[1].fRoomStatus = ROOMSTATUS_COUNT;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pDrlgRooms, moo_ppRoomsNear, moo_pRoom1, moo_pRoom2);
			setup_data(original_pDrlg, original_pLevel, original_pDrlgRooms, original_ppRoomsNear, original_pRoom1, original_pRoom2);

			// Call both implementations
			sut(&moo_pRoom1, &moo_pRoom2);
			original(&original_pRoom1, &original_pRoom2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
			MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C730 (#10065)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_StreamRoomAtCoords, dll_base + 0x0004C730);

		SUBCASE("")
		{
			for (auto x = 0; x < 36; x += 3)
			{
				for (auto y = 5; y < 25; y += 3)
				{
					// Input data
					D2DrlgActStrc moo_pAct{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgLevelStrc moo_pLevels[2]{};
					D2DrlgRoomStrc moo_pDrlgRooms[3]{};
					D2ActiveRoomStrc moo_pRooms[2]{};
					D2DrlgActStrc original_pAct{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgLevelStrc original_pLevels[2]{};
					D2DrlgRoomStrc original_pDrlgRooms[3]{};
					D2ActiveRoomStrc original_pRooms[2]{};
					int nX = x;
					int nY = y;

					const auto setup_data = [](
						D2DrlgActStrc& pAct,
						D2DrlgStrc& pDrlg,
						D2DrlgLevelStrc(& pLevels)[2],
						D2DrlgRoomStrc(& pDrlgRooms)[3],
						D2ActiveRoomStrc(& pRooms)[2]
					) {
						pAct.pDrlg = &pDrlg;
						pDrlg.pLevel = &pLevels[1];

						// Coordinates outside of all levels fall back to LEVEL_NONE, which is already initialized here but has no room at these coordinates
						pLevels[0].nLevelId = LEVEL_NONE;
						pLevels[0].pDrlg = &pDrlg;
						pLevels[0].pFirstRoomEx = &pDrlgRooms[0];
						pDrlgRooms[0].pLevel = &pLevels[0];
						pDrlgRooms[0].nTileXPos = -100;
						pDrlgRooms[0].nTileYPos = -100;
						pDrlgRooms[0].nTileWidth = 1;
						pDrlgRooms[0].nTileHeight = 1;

						// The level consists of two rooms, which have their tile library loaded and are already active
						pLevels[1].nLevelId = LEVEL_ROGUEENCAMPMENT;
						pLevels[1].pDrlg = &pDrlg;
						pLevels[1].nPosX = 10;
						pLevels[1].nPosY = 10;
						pLevels[1].nWidth = 20;
						pLevels[1].nHeight = 10;
						pLevels[1].pFirstRoomEx = &pDrlgRooms[1];
						pLevels[1].pNextLevel = &pLevels[0];

						for (auto i = 1; i < 3; ++i)
						{
							pDrlgRooms[i].pLevel = &pLevels[1];
							pDrlgRooms[i].nType = DRLGTYPE_OUTDOOR;
							pDrlgRooms[i].dwFlags = DRLGROOMFLAG_TILELIB_LOADED;
							pDrlgRooms[i].nTileXPos = 10 * i;
							pDrlgRooms[i].nTileYPos = 10;
							pDrlgRooms[i].nTileWidth = 10;
							pDrlgRooms[i].nTileHeight = 10;
							pDrlgRooms[i].pDrlgRoomNext = i < 2 ? &pDrlgRooms[i + 1] : nullptr;
							pDrlgRooms[i].pRoom = &pRooms[i - 1];
							pRooms[i - 1].pDrlgRoom = &pDrlgRooms[i];
						}
					};

					setup_data(moo_pAct, moo_pDrlg, moo_pLevels, moo_pDrlgRooms, moo_pRooms);
					setup_data(original_pAct, original_pDrlg, original_pLevels, original_pDrlgRooms, original_pRooms);

					// Call both implementations
					const auto moo_result = sut(&moo_pAct, nX, nY);
					const auto original_result = original(&original_pAct, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");

					// Check specific values
					CHECK_EQ(moo_result == nullptr ? -1 : moo_result - moo_pRooms, original_result == nullptr ? -1 : original_result - original_pRooms);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C770 (#10056)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomFromAct, dll_base + 0x0004C770);

		SUBCASE("")
		{
			// Input data
			const auto allies = random_unsigned_integer(0, 100);

			D2DrlgActStrc moo_pAct{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc original_pAct{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [allies](
				D2DrlgActStrc& pAct,
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.nAllies = allies;
				pAct.pRoom = &pRoom;
			};

			setup_data(moo_pAct, moo_pRoom);
			setup_data(original_pAct, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pAct);
			const auto original_result = original(&original_pAct);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pRoom);
			CHECK_EQ(original_result, &original_pRoom);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C7A0 (#10057)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetLevelIdFromRoom, dll_base + 0x0004C7A0);

		SUBCASE("")
		{
			// Input data
			const auto level_id = random_unsigned_integer(0, 136);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};

			const auto setup_data = [level_id](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel
			) {
				pLevel.nLevelId = level_id;
				pDrlgRoom.pLevel = &pLevel;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pLevel);
			setup_data(original_pRoom, original_pDrlgRoom, original_pLevel);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C7C0 (#10058)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetWarpDestinationLevel, dll_base + 0x0004C7C0);

		SUBCASE("")
		{
			// Input data
			const int source_level = random_unsigned_integer(1, 136);
			const int destination_level = random_unsigned_integer(1, 136);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2RoomTileStrc moo_pSourceRoomTile{};
			D2LvlWarpTxt moo_pSourceLvlWarp{};
			D2DrlgRoomStrc moo_pDestinationDrlgRoom{};
			D2RoomTileStrc moo_pDestinationRoomTile{};
			D2LvlWarpTxt moo_pDestinationLvlWarp{};
			D2DrlgLevelStrc moo_pDestinationLevel{};
			D2ActiveRoomStrc moo_pDestinationRoom{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2RoomTileStrc original_pSourceRoomTile{};
			D2LvlWarpTxt original_pSourceLvlWarp{};
			D2DrlgRoomStrc original_pDestinationDrlgRoom{};
			D2RoomTileStrc original_pDestinationRoomTile{};
			D2LvlWarpTxt original_pDestinationLvlWarp{};
			D2DrlgLevelStrc original_pDestinationLevel{};
			D2ActiveRoomStrc original_pDestinationRoom{};
			int nSourceLevel = source_level;

			const auto setup_data = [source_level, destination_level](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2RoomTileStrc& pSourceRoomTile,
				D2LvlWarpTxt& pSourceLvlWarp,
				D2DrlgRoomStrc& pDestinationDrlgRoom,
				D2RoomTileStrc& pDestinationRoomTile,
				D2LvlWarpTxt& pDestinationLvlWarp,
				D2DrlgLevelStrc& pDestinationLevel,
				D2ActiveRoomStrc& pDestinationRoom
			) {
				// The source room links to the destination room ...
				pSourceLvlWarp.dwLevelId = source_level;
				pSourceRoomTile.pLvlWarpTxtRecord = &pSourceLvlWarp;
				pSourceRoomTile.pDrlgRoom = &pDestinationDrlgRoom;
				pDrlgRoom.pRoomTiles = &pSourceRoomTile;
				pRoom.pDrlgRoom = &pDrlgRoom;

				// ... which links back to the source room
				pDestinationLvlWarp.dwLevelId = destination_level;
				pDestinationRoomTile.pLvlWarpTxtRecord = &pDestinationLvlWarp;
				pDestinationRoomTile.pDrlgRoom = &pDrlgRoom;
				pDestinationDrlgRoom.pRoomTiles = &pDestinationRoomTile;
				pDestinationLevel.nLevelId = destination_level;
				pDestinationDrlgRoom.pLevel = &pDestinationLevel;

				// The destination room is already active, so it doesn't have to be initialized
				pDestinationDrlgRoom.pRoom = &pDestinationRoom;
				pDestinationRoom.pDrlgRoom = &pDestinationDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pSourceRoomTile, moo_pSourceLvlWarp, moo_pDestinationDrlgRoom, moo_pDestinationRoomTile, moo_pDestinationLvlWarp, moo_pDestinationLevel, moo_pDestinationRoom);
			setup_data(original_pRoom, original_pDrlgRoom, original_pSourceRoomTile, original_pSourceLvlWarp, original_pDestinationDrlgRoom, original_pDestinationRoomTile, original_pDestinationLvlWarp, original_pDestinationLevel, original_pDestinationRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nSourceLevel);
			const auto original_result = original(&original_pRoom, nSourceLevel);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C7E0 (#10059)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetLevelIdFromPopulatedRoom, dll_base + 0x0004C7E0);

		SUBCASE("")
		{
			for (uint32_t flags : { 0u, (uint32_t)DRLGROOMFLAG_POPULATION_ZERO })
			{
				// Input data
				const auto level_id = random_unsigned_integer(1, 136);

				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgLevelStrc moo_pLevel{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgLevelStrc original_pLevel{};

				const auto setup_data = [flags, level_id](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgLevelStrc& pLevel
				) {
					pLevel.nLevelId = level_id;
					pDrlgRoom.pLevel = &pLevel;
					pDrlgRoom.dwFlags = flags;
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pLevel);
				setup_data(original_pRoom, original_pDrlgRoom, original_pLevel);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C800 (#10060)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_HasWaypoint, dll_base + 0x0004C800);

		SUBCASE("")
		{
			for (uint32_t flags : { 0u, (uint32_t)DRLGROOMFLAG_HAS_WAYPOINT, (uint32_t)DRLGROOMFLAG_HAS_WAYPOINT_SMALL, (uint32_t)DRLGROOMFLAG_HAS_WAYPOINT_MASK, (uint32_t)DRLGROOMFLAG_HAS_WARP_MASK })
			{
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};

				const auto setup_data = [flags](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom
				) {
					pDrlgRoom.dwFlags = flags;
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom);
				setup_data(original_pRoom, original_pDrlgRoom);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C840 (#10061)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetPickedLevelPrestFilePathFromRoom, dll_base + 0x0004C840);

		SUBCASE("")
		{
			for (auto type : { DRLGTYPE_MAZE, DRLGTYPE_PRESET, DRLGTYPE_OUTDOOR })
			{
				for (auto picked_file = 0; picked_file < 6; ++picked_file)
				{
					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2DrlgRoomStrc moo_pDrlgRoom{};
					D2DrlgPresetRoomStrc moo_pPresetRoom{};
					D2DrlgMapStrc moo_pDrlgMap{};
					D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
					D2ActiveRoomStrc original_pRoom{};
					D2DrlgRoomStrc original_pDrlgRoom{};
					D2DrlgPresetRoomStrc original_pPresetRoom{};
					D2DrlgMapStrc original_pDrlgMap{};
					D2LvlPrestTxt original_pLvlPrestTxtRecord{};

					const auto setup_data = [type, picked_file](
						D2ActiveRoomStrc& pRoom,
						D2DrlgRoomStrc& pDrlgRoom,
						D2DrlgPresetRoomStrc& pPresetRoom,
						D2DrlgMapStrc& pDrlgMap,
						D2LvlPrestTxt& pLvlPrestTxtRecord
					) {
						for (auto i = 0; i < 6; ++i)
						{
							std::snprintf(pLvlPrestTxtRecord.szFile[i], sizeof(pLvlPrestTxtRecord.szFile[i]), "Act1\\Town\\TownFile%d.ds1", i);
						}

						pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;
						pDrlgMap.nPickedFile = picked_file;
						pPresetRoom.pMap = &pDrlgMap;

						pDrlgRoom.nType = type;
						if (type == DRLGTYPE_PRESET)
						{
							pDrlgRoom.pMaze = &pPresetRoom;
						}
						pRoom.pDrlgRoom = &pDrlgRoom;
					};

					setup_data(moo_pRoom, moo_pDrlgRoom, moo_pPresetRoom, moo_pDrlgMap, moo_pLvlPrestTxtRecord);
					setup_data(original_pRoom, original_pDrlgRoom, original_pPresetRoom, original_pDrlgMap, original_pLvlPrestTxtRecord);

					// Call both implementations
					const auto moo_result = std::string(sut(&moo_pRoom));
					const auto original_result = std::string(original(&original_pRoom));

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C860 (#10066)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AllocDrlgDelete, dll_base + 0x0004C860);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pRoom, moo_pAct);
			setup_data(original_pRoom, original_pAct);

			for (auto i = 0; i < 3; ++i)
			{
				int nUnitType = random_unsigned_integer(UNIT_PLAYER, UNIT_TILE);
				D2UnitGUID nUnitGuid = random_unsigned_integer();

				// Call both implementations
				sut(&moo_pRoom, nUnitType, nUnitGuid);
				original(&original_pRoom, nUnitType, nUnitGuid);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C8B0 (#10067)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FreeDrlgDelete, dll_base + 0x0004C8B0);
		const auto [moo_alloc, original_alloc] = make_function_pair(DUNGEON_AllocDrlgDelete, dll_base + 0x0004C860);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pRoom, moo_pAct);
			setup_data(original_pRoom, original_pAct);

			// The deletions have to be allocated by the respective implementation, since they are freed
			for (auto i = 0; i < 3; ++i)
			{
				const int unit_type = random_unsigned_integer(UNIT_PLAYER, UNIT_TILE);
				const D2UnitGUID unit_guid = random_unsigned_integer();

				moo_alloc(&moo_pRoom, unit_type, unit_guid);
				original_alloc(&original_pRoom, unit_type, unit_guid);
			}

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C910 (#10068)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetDrlgDeleteFromRoom, dll_base + 0x0004C910);

		SUBCASE("")
		{
			// Input data
			int unit_types[2]{};
			D2UnitGUID unit_guids[2]{};
			for (auto i = 0; i < 2; ++i)
			{
				unit_types[i] = random_unsigned_integer(UNIT_PLAYER, UNIT_TILE);
				unit_guids[i] = random_unsigned_integer();
			}

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgDeleteStrc moo_pDrlgDeletes[2]{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgDeleteStrc original_pDrlgDeletes[2]{};

			const auto setup_data = [unit_types, unit_guids](
				D2ActiveRoomStrc& pRoom,
				D2DrlgDeleteStrc(& pDrlgDeletes)[2]
			) {
				for (auto i = 0; i < 2; ++i)
				{
					pDrlgDeletes[i].nUnitType = unit_types[i];
					pDrlgDeletes[i].nUnitGUID = unit_guids[i];
					pDrlgDeletes[i].pNext = i < 1 ? &pDrlgDeletes[i + 1] : nullptr;
				}

				pRoom.pDrlgDelete = &pDrlgDeletes[0];
			};

			setup_data(moo_pRoom, moo_pDrlgDeletes);
			setup_data(original_pRoom, original_pDrlgDeletes);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pDrlgDeletes[0]);
			CHECK_EQ(original_result, &original_pDrlgDeletes[0]);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C940 (#10069)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetARoomInClientSight, dll_base + 0x0004C940);

		SUBCASE("")
		{
			for (auto status = 0; status <= ROOMSTATUS_COUNT; ++status)
			{
				// Input data
				D2DrlgActStrc moo_pAct{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgActStrc original_pAct{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2ActiveRoomStrc original_pRoom{};

				const auto setup_data = [status](
					D2DrlgActStrc& pAct,
					D2DrlgStrc& pDrlg,
					D2DrlgRoomStrc& pDrlgRoom,
					D2ActiveRoomStrc& pRoom
				) {
					for (auto i = 0; i < ROOMSTATUS_COUNT; ++i)
					{
						pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
						pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
						pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
					}
					pAct.pDrlg = &pDrlg;

					pDrlgRoom.pRoom = &pRoom;
					pRoom.pDrlgRoom = &pDrlgRoom;

					// Put the room into the status list matching its status
					pDrlgRoom.fRoomStatus = status;
					if (status < ROOMSTATUS_COUNT)
					{
						D2DrlgRoomStrc& pStatusRoomsListHead = pDrlg.tStatusRoomsLists[status];
						pDrlgRoom.pStatusNext = &pStatusRoomsListHead;
						pDrlgRoom.pStatusPrev = pStatusRoomsListHead.pStatusPrev;
						pStatusRoomsListHead.pStatusPrev->pStatusNext = &pDrlgRoom;
						pStatusRoomsListHead.pStatusPrev = &pDrlgRoom;
					}
				};

				setup_data(moo_pAct, moo_pDrlg, moo_pDrlgRoom, moo_pRoom);
				setup_data(original_pAct, original_pDrlg, original_pDrlgRoom, original_pRoom);

				// Call both implementations
				const auto moo_result = sut(&moo_pAct);
				const auto original_result = original(&original_pAct);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");

				// Check specific values
				CHECK_EQ(moo_result == &moo_pRoom, original_result == &original_pRoom);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C980 (#10070)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetARoomInSightButWithoutClient, dll_base + 0x0004C980);

		SUBCASE("")
		{
			for (auto status = 0; status < ROOMSTATUS_COUNT; ++status)
			{
				for (auto rooms_in_status = 1; rooms_in_status <= 2; ++rooms_in_status)
				{
					// Input data
					D2DrlgActStrc moo_pAct{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgRoomStrc moo_pDrlgRooms[3]{};
					D2ActiveRoomStrc moo_pRooms[3]{};
					D2DrlgActStrc original_pAct{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgRoomStrc original_pDrlgRooms[3]{};
					D2ActiveRoomStrc original_pRooms[3]{};

					const auto setup_data = [status, rooms_in_status](
						D2DrlgActStrc& pAct,
						D2DrlgStrc& pDrlg,
						D2DrlgRoomStrc(& pDrlgRooms)[3],
						D2ActiveRoomStrc(& pRooms)[3]
					) {
						for (auto i = 0; i < ROOMSTATUS_COUNT; ++i)
						{
							pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
							pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
							pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
						}
						pAct.pDrlg = &pDrlg;

						// The first rooms have the given status, the last room is in sight of a client
						for (auto i = 0; i < 3; ++i)
						{
							const auto room_status = i < rooms_in_status ? status : ROOMSTATUS_CLIENT_IN_SIGHT;
							if (i >= rooms_in_status && i != 2)
							{
								continue;
							}

							pDrlgRooms[i].pRoom = &pRooms[i];
							pRooms[i].pDrlgRoom = &pDrlgRooms[i];
							pDrlgRooms[i].fRoomStatus = room_status;

							D2DrlgRoomStrc& pStatusRoomsListHead = pDrlg.tStatusRoomsLists[room_status];
							pDrlgRooms[i].pStatusNext = &pStatusRoomsListHead;
							pDrlgRooms[i].pStatusPrev = pStatusRoomsListHead.pStatusPrev;
							pStatusRoomsListHead.pStatusPrev->pStatusNext = &pDrlgRooms[i];
							pStatusRoomsListHead.pStatusPrev = &pDrlgRooms[i];
						}
					};

					setup_data(moo_pAct, moo_pDrlg, moo_pDrlgRooms, moo_pRooms);
					setup_data(original_pAct, original_pDrlg, original_pDrlgRooms, original_pRooms);

					// Call both implementations
					const auto moo_result = sut(&moo_pAct, &moo_pRooms[0]);
					const auto original_result = original(&original_pAct, &original_pRooms[0]);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
					MOO_CHECK_EQ(moo_pRooms[0], original_pRooms[0], "Comparing pRoom");

					// Check specific values
					CHECK_EQ(moo_result == nullptr ? -1 : moo_result - moo_pRooms, original_result == nullptr ? -1 : original_result - original_pRooms);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8C9E0 (#10071)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_TestRoomCanUnTile, dll_base + 0x0004C9E0);

		SUBCASE("")
		{
			for (auto level_id : { LEVEL_ROGUEENCAMPMENT, LEVEL_BLOODMOOR, LEVEL_ROCKYSUMMIT })
			{
				for (uint32_t flags : { 0u, (uint32_t)DRLGROOMFLAG_HASPORTAL })
				{
					for (auto status = 0; status <= ROOMSTATUS_COUNT; ++status)
					{
						for (auto other_room_status = 1; other_room_status <= 3; other_room_status += 2)
						{
							// Input data
							D2DrlgActStrc moo_pAct{};
							D2ActiveRoomStrc moo_pRoom{};
							D2DrlgRoomStrc moo_pDrlgRooms[2]{};
							D2DrlgLevelStrc moo_pLevel{};
							D2DrlgStrc moo_pDrlg{};
							D2DrlgActStrc original_pAct{};
							D2ActiveRoomStrc original_pRoom{};
							D2DrlgRoomStrc original_pDrlgRooms[2]{};
							D2DrlgLevelStrc original_pLevel{};
							D2DrlgStrc original_pDrlg{};

							const auto setup_data = [level_id, flags, status, other_room_status](
								D2DrlgActStrc& pAct,
								D2ActiveRoomStrc& pRoom,
								D2DrlgRoomStrc(& pDrlgRooms)[2],
								D2DrlgLevelStrc& pLevel,
								D2DrlgStrc& pDrlg
							) {
								// Only servers are allowed to untile rooms
								pAct.bClient = FALSE;

								pLevel.nLevelId = level_id;
								pLevel.pDrlg = &pDrlg;
								pLevel.pFirstRoomEx = &pDrlgRooms[0];

								pDrlgRooms[0].pLevel = &pLevel;
								pDrlgRooms[0].dwFlags = flags;
								pDrlgRooms[0].fRoomStatus = status;
								pDrlgRooms[0].pDrlgRoomNext = &pDrlgRooms[1];
								pDrlgRooms[1].pLevel = &pLevel;
								pDrlgRooms[1].fRoomStatus = other_room_status;

								pRoom.pDrlgRoom = &pDrlgRooms[0];
							};

							setup_data(moo_pAct, moo_pRoom, moo_pDrlgRooms, moo_pLevel, moo_pDrlg);
							setup_data(original_pAct, original_pRoom, original_pDrlgRooms, original_pLevel, original_pDrlg);

							// Call both implementations
							const auto moo_result = sut(&moo_pAct, &moo_pRoom);
							const auto original_result = original(&original_pAct, &original_pRoom);

							// Compare return values
							MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

							// Compare potentially modified input data
							MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
							MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
						}
					}
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CA60 (#10072)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomStatusFlags, dll_base + 0x0004CA60);

		SUBCASE("")
		{
			for (auto status = 0; status <= ROOMSTATUS_COUNT; ++status)
			{
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};

				const auto setup_data = [status](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom
				) {
					pDrlgRoom.fRoomStatus = status;
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom);
				setup_data(original_pRoom, original_pDrlgRoom);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CA80 (#10073)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10073, dll_base + 0x0004CA80);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto rooms_near = random_unsigned_integer(2, 3);
			uint32_t flags[3]{};
			for (auto i = 0; i < 3; ++i)
			{
				// Make it likely that all adjacent rooms have the flag
				flags[i] = random_unsigned_integer(0, 3) != 0;
			}

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pAdjacentRooms[3]{};
			D2ActiveRoomStrc* moo_pRoomList[3]{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pAdjacentRooms[3]{};
			D2ActiveRoomStrc* original_pRoomList[3]{};

			const auto setup_data = [rooms_near, flags](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2ActiveRoomStrc(& pAdjacentRooms)[3],
				D2ActiveRoomStrc*(& pRoomList)[3]
			) {
				for (auto i = 0; i < 3; ++i)
				{
					pAdjacentRooms[i].dwFlags = flags[i];
					pRoomList[i] = &pAdjacentRooms[i];
				}

				pDrlgRoom.nRoomsNear = rooms_near;
				pRoom.pDrlgRoom = &pDrlgRoom;
				pRoom.ppRoomList = &pRoomList[0];
				pRoom.nNumRooms = 3;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pAdjacentRooms, moo_pRoomList);
			setup_data(original_pRoom, original_pDrlgRoom, original_pAdjacentRooms, original_pRoomList);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CAE0 (#10074)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10074, dll_base + 0x0004CAE0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [flags](
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.dwFlags = flags;
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CB10 (#10075)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10075, dll_base + 0x0004CB10);

		REPEAT_10();

		SUBCASE("")
		{
			for (auto bSet : { FALSE, TRUE })
			{
				// Input data
				const auto flags = random_unsigned_integer();

				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};

				const auto setup_data = [flags](
					D2ActiveRoomStrc& pRoom
				) {
					pRoom.dwFlags = flags;
				};

				setup_data(moo_pRoom);
				setup_data(original_pRoom);

				// Call both implementations
				sut(&moo_pRoom, bSet);
				original(&original_pRoom, bSet);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CB60 (#10079)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AddClientToRoom, dll_base + 0x0004CB60);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ClientStrc* moo_ppClients[4]{};
			D2ClientStrc moo_pClients[3]{};
			D2ActiveRoomStrc original_pRoom{};
			D2ClientStrc* original_ppClients[4]{};
			D2ClientStrc original_pClients[3]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2ClientStrc*(& ppClients)[4],
				D2ClientStrc(& pClients)[3]
			) {
				// The room has enough space for another client, so that no reallocation is needed
				ppClients[0] = &pClients[2];
				ppClients[1] = &pClients[0];
				pRoom.ppClients = &ppClients[0];
				pRoom.nNumClients = 2;
				pRoom.nMaxClients = 4;
			};

			setup_data(moo_pRoom, moo_ppClients, moo_pClients);
			setup_data(original_pRoom, original_ppClients, original_pClients);

			// Call both implementations
			sut(&moo_pRoom, &moo_pClients[1]);
			original(&original_pRoom, &original_pClients[1]);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pClients[1], original_pClients[1], "Comparing pClient");

			// Check specific values
			for (auto i = 0; i < original_pRoom.nNumClients; ++i)
			{
				CHECK_EQ(moo_ppClients[i] - moo_pClients, original_ppClients[i] - original_pClients);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CC50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdateClientListOfRoom, dll_base + 0x0004CC50);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ClientStrc* moo_ppClients[3]{};
			D2ClientStrc moo_pClients[3]{};
			D2ActiveRoomStrc original_pRoom{};
			D2ClientStrc* original_ppClients[3]{};
			D2ClientStrc original_pClients[3]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2ClientStrc*(& ppClients)[3],
				D2ClientStrc(& pClients)[3]
			) {
				// The clients are expected to be sorted by their address
				ppClients[0] = &pClients[2];
				ppClients[1] = &pClients[0];
				ppClients[2] = &pClients[1];
				pRoom.ppClients = &ppClients[0];
				pRoom.nNumClients = 3;
				pRoom.nMaxClients = 3;
			};

			setup_data(moo_pRoom, moo_ppClients, moo_pClients);
			setup_data(original_pRoom, original_ppClients, original_pClients);

			// Call both implementations
			sut(&moo_pRoom);
			original(&original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			for (auto i = 0; i < original_pRoom.nNumClients; ++i)
			{
				CHECK_EQ(moo_ppClients[i] - moo_pClients, original_ppClients[i] - original_pClients);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CD10 (#10080)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_RemoveClientFromRoom, dll_base + 0x0004CD10);

		SUBCASE("")
		{
			for (auto i = 0; i < 3; ++i)
			{
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2ClientStrc* moo_ppClients[3]{};
				D2ClientStrc moo_pClients[3]{};
				D2ActiveRoomStrc original_pRoom{};
				D2ClientStrc* original_ppClients[3]{};
				D2ClientStrc original_pClients[3]{};

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom,
					D2ClientStrc*(& ppClients)[3],
					D2ClientStrc(& pClients)[3]
				) {
					for (auto j = 0; j < 3; ++j)
					{
						ppClients[j] = &pClients[j];
					}
					pRoom.ppClients = &ppClients[0];
					pRoom.nNumClients = 3;
					pRoom.nMaxClients = 3;
				};

				setup_data(moo_pRoom, moo_ppClients, moo_pClients);
				setup_data(original_pRoom, original_ppClients, original_pClients);

				// Call both implementations
				sut(&moo_pRoom, &moo_pClients[i]);
				original(&original_pRoom, &original_pClients[i]);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_pClients[i], original_pClients[i], "Comparing pClient");

				// Check specific values
				for (auto j = 0; j < original_pRoom.nNumClients; ++j)
				{
					CHECK_EQ(moo_ppClients[j] - moo_pClients, original_ppClients[j] - original_pClients);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CDF0 (#10081)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10081_GetTileCountFromRoom, dll_base + 0x0004CDF0);

		REPEAT_10();

		SUBCASE("")
		{
			for (auto clients = 0; clients < 2; ++clients)
			{
				// Input data
				const auto tile_count = random_unsigned_integer(0, 100);

				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};

				const auto setup_data = [clients, tile_count](
					D2ActiveRoomStrc& pRoom
				) {
					pRoom.nNumClients = clients;
					pRoom.nTileCount = tile_count;
				};

				setup_data(moo_pRoom);
				setup_data(original_pRoom);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CE40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_FreeRoom, dll_base + 0x0004CE40);
		const auto [moo_alloc, original_alloc] = make_function_pair(DUNGEON_AllocRoom, dll_base + 0x0004BC50);

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordsStrc coords{};
			coords.nSubtileX = 50;
			coords.nSubtileY = 60;
			coords.nSubtileWidth = 40;
			coords.nSubtileHeight = 30;
			coords.nTileXPos = 10;
			coords.nTileYPos = 12;
			coords.nTileWidth = 8;
			coords.nTileHeight = 6;

			const auto low_seed = random_unsigned_integer();
			const auto flags = random_unsigned_integer();

			D2DrlgActStrc moo_pAct{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgCoordsStrc moo_pDrlgCoords{};
			D2DrlgRoomTilesStrc moo_pRoomTiles{};
			D2DrlgActStrc original_pAct{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			D2DrlgCoordsStrc original_pDrlgCoords{};
			D2DrlgRoomTilesStrc original_pRoomTiles{};

			const auto setup_data = [coords](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc*(& ppRoomsNear)[1],
				D2DrlgCoordsStrc& pDrlgCoords
			) {
				// A room is always near itself
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = &ppRoomsNear[0];
				pDrlgRoom.nRoomsNear = 1;

				pDrlgCoords = coords;
			};

			setup_data(moo_pDrlgRoom, moo_ppRoomsNear, moo_pDrlgCoords);
			setup_data(original_pDrlgRoom, original_ppRoomsNear, original_pDrlgCoords);

			// The room has to be allocated by the respective implementation, since it is freed
			D2ActiveRoomStrc* moo_pRoom = moo_alloc(&moo_pAct, &moo_pDrlgRoom, &moo_pDrlgCoords, &moo_pRoomTiles, low_seed, flags);
			D2ActiveRoomStrc* original_pRoom = original_alloc(&original_pAct, &original_pDrlgRoom, &original_pDrlgCoords, &original_pRoomTiles, low_seed, flags);

			// Call both implementations
			sut(nullptr, moo_pRoom);
			original(nullptr, original_pRoom);

			// Input data can not be compared since it was freed
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8CF10 (#10076)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_RemoveRoomFromAct, dll_base + 0x0004CF10);
		const auto [moo_alloc, original_alloc] = make_function_pair(DUNGEON_AllocRoom, dll_base + 0x0004BC50);

		SUBCASE("")
		{
			for (auto removed_room = 0; removed_room < 2; ++removed_room)
			{
				// Input data
				D2DrlgCoordsStrc coords[2]{};
				for (auto i = 0; i < 2; ++i)
				{
					coords[i].nSubtileX = 50 + 40 * i;
					coords[i].nSubtileY = 60;
					coords[i].nSubtileWidth = 40;
					coords[i].nSubtileHeight = 30;
					coords[i].nTileXPos = 10 + 8 * i;
					coords[i].nTileYPos = 12;
					coords[i].nTileWidth = 8;
					coords[i].nTileHeight = 6;
				}

				const auto low_seed = random_unsigned_integer();
				const auto flags = random_unsigned_integer();

				D2DrlgActStrc moo_pAct{};
				D2DrlgRoomStrc moo_pDrlgRooms[2]{};
				D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
				D2DrlgCoordsStrc moo_pDrlgCoords[2]{};
				D2DrlgRoomTilesStrc moo_pRoomTiles[2]{};
				D2DrlgActStrc original_pAct{};
				D2DrlgRoomStrc original_pDrlgRooms[2]{};
				D2DrlgRoomStrc* original_ppRoomsNear[2]{};
				D2DrlgCoordsStrc original_pDrlgCoords[2]{};
				D2DrlgRoomTilesStrc original_pRoomTiles[2]{};

				const auto setup_data = [coords](
					D2DrlgRoomStrc(& pDrlgRooms)[2],
					D2DrlgRoomStrc*(& ppRoomsNear)[2],
					D2DrlgCoordsStrc(& pDrlgCoords)[2]
				) {
					// Both rooms are near to each other (and themselves)
					for (auto i = 0; i < 2; ++i)
					{
						ppRoomsNear[i] = &pDrlgRooms[i];
						pDrlgCoords[i] = coords[i];
					}

					for (auto i = 0; i < 2; ++i)
					{
						pDrlgRooms[i].ppRoomsNear = &ppRoomsNear[0];
						pDrlgRooms[i].nRoomsNear = 2;
					}
				};

				setup_data(moo_pDrlgRooms, moo_ppRoomsNear, moo_pDrlgCoords);
				setup_data(original_pDrlgRooms, original_ppRoomsNear, original_pDrlgCoords);

				// The rooms have to be allocated by the respective implementation, since one of them is freed
				D2ActiveRoomStrc* moo_pRooms[2]{};
				D2ActiveRoomStrc* original_pRooms[2]{};
				for (auto i = 0; i < 2; ++i)
				{
					moo_pRooms[i] = moo_alloc(&moo_pAct, &moo_pDrlgRooms[i], &moo_pDrlgCoords[i], &moo_pRoomTiles[i], low_seed + i, flags);
					original_pRooms[i] = original_alloc(&original_pAct, &original_pDrlgRooms[i], &original_pDrlgCoords[i], &original_pRoomTiles[i], low_seed + i, flags);
				}

				// Call both implementations
				sut(&moo_pAct, moo_pRooms[removed_room]);
				original(&original_pAct, original_pRooms[removed_room]);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
				MOO_CHECK_EQ(moo_pRooms[1 - removed_room], original_pRooms[1 - removed_room], "Comparing remaining pRoom");

				for (auto i = 0; i < 2; ++i)
				{
					MOO_CHECK_EQ(moo_pDrlgRooms[i], original_pDrlgRooms[i], "Comparing pDrlgRooms");
				}

				// The removed room can not be compared since it was freed
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D000 (#10077)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10077, dll_base + 0x0004D000);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom1{};
			D2ActiveRoomStrc moo_pRoom2{};
			D2DrlgRoomStrc moo_pDrlgRooms[2]{};
			D2DrlgLevelStrc moo_pLevels[3]{};
			D2DrlgWarpStrc moo_pWarps[2]{};
			D2DrlgStrc moo_pDrlg{};
			D2ActiveRoomStrc original_pRoom1{};
			D2ActiveRoomStrc original_pRoom2{};
			D2DrlgRoomStrc original_pDrlgRooms[2]{};
			D2DrlgLevelStrc original_pLevels[3]{};
			D2DrlgWarpStrc original_pWarps[2]{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom1,
				D2ActiveRoomStrc& pRoom2,
				D2DrlgRoomStrc(& pDrlgRooms)[2],
				D2DrlgLevelStrc(& pLevels)[3],
				D2DrlgWarpStrc(& pWarps)[2],
				D2DrlgStrc& pDrlg
			) {
				// The third level is visible from both other levels
				for (auto i = 0; i < 3; ++i)
				{
					pLevels[i].nLevelId = LEVEL_BLOODMOOR + i;
					pLevels[i].pDrlg = &pDrlg;
					pLevels[i].bActive = i != 1;
					pLevels[i].pNextLevel = i < 2 ? &pLevels[i + 1] : nullptr;
				}
				pDrlg.pLevel = &pLevels[0];

				for (auto i = 0; i < 2; ++i)
				{
					pWarps[i].nLevel = pLevels[i].nLevelId;
					pWarps[i].nVis[0] = pLevels[2].nLevelId;
					pWarps[i].pNext = i < 1 ? &pWarps[i + 1] : nullptr;
				}
				pDrlg.pWarp = &pWarps[0];

				// The client moves from a room in the first level to a room in the second level
				pDrlgRooms[0].pLevel = &pLevels[0];
				pDrlgRooms[1].pLevel = &pLevels[1];
				pRoom1.pDrlgRoom = &pDrlgRooms[0];
				pRoom2.pDrlgRoom = &pDrlgRooms[1];
			};

			setup_data(moo_pRoom1, moo_pRoom2, moo_pDrlgRooms, moo_pLevels, moo_pWarps, moo_pDrlg);
			setup_data(original_pRoom1, original_pRoom2, original_pDrlgRooms, original_pLevels, original_pWarps, original_pDrlg);

			// Call both implementations
			sut(&moo_pRoom1, &moo_pRoom2);
			original(&original_pRoom1, &original_pRoom2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
			MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");

			// Check specific values
			for (auto i = 0; i < 3; ++i)
			{
				CHECK_EQ(moo_pLevels[i].bActive, original_pLevels[i].bActive);
				CHECK_EQ(moo_pLevels[i].dwInactiveFrames, original_pLevels[i].dwInactiveFrames);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D030 (#10078)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdateAndFreeInactiveRooms, dll_base + 0x0004D030);

		SUBCASE("")
		{
			// Input data
			const auto inactive_frames = random_unsigned_integer(1, 10);

			D2DrlgActStrc moo_pAct{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevels[3]{};
			D2DrlgRoomStrc moo_pDrlgRooms[3]{};
			D2DrlgActStrc original_pAct{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevels[3]{};
			D2DrlgRoomStrc original_pDrlgRooms[3]{};

			const auto setup_data = [inactive_frames](
				D2DrlgActStrc& pAct,
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc(& pLevels)[3],
				D2DrlgRoomStrc(& pDrlgRooms)[3]
			) {
				for (auto i = 0; i < 3; ++i)
				{
					pDrlgRooms[i].pLevel = &pLevels[i];
					pDrlgRooms[i].fRoomStatus = ROOMSTATUS_CLIENT_OUT_OF_SIGHT;

					pLevels[i].nLevelId = LEVEL_BLOODMOOR + i;
					pLevels[i].pDrlg = &pDrlg;
					pLevels[i].pFirstRoomEx = &pDrlgRooms[i];
					pLevels[i].pNextLevel = i < 2 ? &pLevels[i + 1] : nullptr;
				}

				// The first level is inactive and waits for some frames
				pLevels[0].bActive = FALSE;
				pLevels[0].dwInactiveFrames = inactive_frames;

				// The second level is inactive, but still has a room in use, so it has to wait again
				pLevels[1].bActive = FALSE;
				pLevels[1].dwInactiveFrames = 0;

				// The third level is active
				pLevels[2].bActive = TRUE;
				pLevels[2].dwInactiveFrames = inactive_frames;

				pDrlg.pLevel = &pLevels[0];
				pAct.pDrlg = &pDrlg;
			};

			setup_data(moo_pAct, moo_pDrlg, moo_pLevels, moo_pDrlgRooms);
			setup_data(original_pAct, original_pDrlg, original_pLevels, original_pDrlgRooms);

			// Call both implementations
			sut(&moo_pAct);
			original(&original_pAct);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");

			// Check specific values
			for (auto i = 0; i < 3; ++i)
			{
				CHECK_EQ(moo_pLevels[i].dwInactiveFrames, original_pLevels[i].dwInactiveFrames);
				CHECK_EQ(moo_pLevels[i].pFirstRoomEx == &moo_pDrlgRooms[i], original_pLevels[i].pFirstRoomEx == &original_pDrlgRooms[i]);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D040 (#10044)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_CheckLOSDraw, dll_base + 0x0004D040);

		SUBCASE("")
		{
			for (auto type : { DRLGTYPE_MAZE, DRLGTYPE_PRESET, DRLGTYPE_OUTDOOR })
			{
				for (uint32_t flags : { 0u, (uint32_t)DRLGROOMFLAG_NO_LOS_DRAW })
				{
					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2DrlgRoomStrc moo_pDrlgRoom{};
					D2ActiveRoomStrc original_pRoom{};
					D2DrlgRoomStrc original_pDrlgRoom{};

					const auto setup_data = [type, flags](
						D2ActiveRoomStrc& pRoom,
						D2DrlgRoomStrc& pDrlgRoom
					) {
						pDrlgRoom.nType = type;
						pDrlgRoom.dwFlags = flags;
						pRoom.pDrlgRoom = &pDrlgRoom;
					};

					setup_data(moo_pRoom, moo_pDrlgRoom);
					setup_data(original_pRoom, original_pDrlgRoom);

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
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D060")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetEnvironmentFromAct, dll_base + 0x0004D060);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgActStrc moo_pAct{};
			D2DrlgEnvironmentStrc moo_pEnvironment{};
			D2DrlgActStrc original_pAct{};
			D2DrlgEnvironmentStrc original_pEnvironment{};

			const auto setup_data = [](
				D2DrlgActStrc& pAct,
				D2DrlgEnvironmentStrc& pEnvironment
			) {
				pAct.pEnvironment = &pEnvironment;
			};

			setup_data(moo_pAct, moo_pEnvironment);
			setup_data(original_pAct, original_pEnvironment);

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
			// Input data
			D2DrlgActStrc moo_pAct{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgActStrc original_pAct{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgActStrc& pAct,
				D2DrlgStrc& pDrlg
			) {
				pAct.pDrlg = &pDrlg;
			};

			setup_data(moo_pAct, moo_pDrlg);
			setup_data(original_pAct, original_pDrlg);

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
			// Input data
			const auto init_seed = random_unsigned_integer();

			D2DrlgActStrc moo_pAct{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [init_seed](
				D2DrlgActStrc& pAct
			) {
				pAct.dwInitSeed = init_seed;
			};

			setup_data(moo_pAct);
			setup_data(original_pAct);

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
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom);
			setup_data(original_pRoom, original_pDrlgRoom);

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
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgLevelStrc moo_pLevel{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgLevelStrc original_pLevel{};

				const auto setup_data = [i](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgLevelStrc& pLevel
				) {
					pLevel.nLevelId = i;
					pDrlgRoom.pLevel = &pLevel;
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pLevel);
				setup_data(original_pRoom, original_pDrlgRoom, original_pLevel);

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
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel
			) {
				pDrlgRoom.pLevel = &pLevel;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pLevel);
			setup_data(original_pRoom, original_pDrlgRoom, original_pLevel);

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
			// Input data
			const auto flags = random_unsigned_integer();

			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [flags](
				D2ActiveRoomStrc& pRoom
			) {
				pRoom.dwFlags = flags;
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D180 (#10087)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10087, dll_base + 0x0004D180);

		REPEAT_10();

		SUBCASE("")
		{
			for (auto type : { DRLGTYPE_MAZE, DRLGTYPE_PRESET, DRLGTYPE_OUTDOOR })
			{
				// Input data
				const auto flags = random_unsigned_integer();

				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgOutdoorRoomStrc moo_pOutdoorRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgOutdoorRoomStrc original_pOutdoorRoom{};

				const auto setup_data = [type, flags](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgOutdoorRoomStrc& pOutdoorRoom
				) {
					pDrlgRoom.nType = type;
					if (type == DRLGTYPE_MAZE)
					{
						pOutdoorRoom.dwFlags = flags;
						pDrlgRoom.pOutdoor = &pOutdoorRoom;
					}
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pOutdoorRoom);
				setup_data(original_pRoom, original_pDrlgRoom, original_pOutdoorRoom);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D1C0 (#10090)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetNumberOfPopulatedRoomsInLevel, dll_base + 0x0004D1C0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			uint32_t flags[4]{};
			for (auto i = 0; i < 4; ++i)
			{
				flags[i] = random_unsigned_integer(0, 1) ? DRLGROOMFLAG_POPULATION_ZERO : 0;
			}

			D2DrlgActStrc moo_pAct{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevels[2]{};
			D2DrlgRoomStrc moo_pDrlgRooms[4]{};
			D2DrlgActStrc original_pAct{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevels[2]{};
			D2DrlgRoomStrc original_pDrlgRooms[4]{};
			int nLevelId = LEVEL_BLOODMOOR;

			const auto setup_data = [flags](
				D2DrlgActStrc& pAct,
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc(& pLevels)[2],
				D2DrlgRoomStrc(& pDrlgRooms)[4]
			) {
				// The level is the second one in the list of levels
				pLevels[0].nLevelId = LEVEL_ROGUEENCAMPMENT;
				pLevels[0].pDrlg = &pDrlg;
				pLevels[0].pNextLevel = &pLevels[1];
				pLevels[1].nLevelId = LEVEL_BLOODMOOR;
				pLevels[1].pDrlg = &pDrlg;
				pLevels[1].pFirstRoomEx = &pDrlgRooms[0];
				pLevels[1].nRooms = 4;

				for (auto i = 0; i < 4; ++i)
				{
					pDrlgRooms[i].pLevel = &pLevels[1];
					pDrlgRooms[i].dwFlags = flags[i];
					pDrlgRooms[i].pDrlgRoomNext = i < 3 ? &pDrlgRooms[i + 1] : nullptr;
				}

				pDrlg.pLevel = &pLevels[0];
				pAct.pDrlg = &pDrlg;
			};

			setup_data(moo_pAct, moo_pDrlg, moo_pLevels, moo_pDrlgRooms);
			setup_data(original_pAct, original_pDrlg, original_pLevels, original_pDrlgRooms);

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nLevelId);
			const auto original_result = original(&original_pAct, nLevelId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D1E0 (#10025)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetWarpCoordinatesFromRoom, dll_base + 0x0004D1E0);

		SUBCASE("")
		{
			// Input data
			int warp_x[9]{};
			for (auto i = 0; i < 9; ++i)
			{
				warp_x[i] = random_unsigned_integer(0, 1000);
			}

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};

			const auto setup_data = [warp_x](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel
			) {
				for (auto i = 0; i < 9; ++i)
				{
					pLevel.nRoom_Center_Warp_X[i] = warp_x[i];
				}

				pDrlgRoom.pLevel = &pLevel;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pLevel);
			setup_data(original_pRoom, original_pDrlgRoom, original_pLevel);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ((DynamicArray<int> { moo_result, 9 }), (DynamicArray<int> { original_result, 9 }), "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_result, moo_pLevel.nRoom_Center_Warp_X);
			CHECK_EQ(original_result, original_pLevel.nRoom_Center_Warp_X);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D220 (#10091)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdateWarpRoomSelect, dll_base + 0x0004D220);

		SUBCASE("")
		{
			for (auto level_id = 10; level_id <= 30; level_id += 10)
			{
				// Input data
				uint32_t flags[8]{};
				for (auto i = 0; i < 8; ++i)
				{
					flags[i] = random_unsigned_integer();
				}

				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2RoomTileStrc moo_pRoomTiles[2]{};
				D2LvlWarpTxt moo_pLvlWarps[2]{};
				D2DrlgTileDataStrc moo_pTileDatas[8]{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2RoomTileStrc original_pRoomTiles[2]{};
				D2LvlWarpTxt original_pLvlWarps[2]{};
				D2DrlgTileDataStrc original_pTileDatas[8]{};
				int nLevelId = level_id;

				const auto setup_data = [flags](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2RoomTileStrc(& pRoomTiles)[2],
					D2LvlWarpTxt(& pLvlWarps)[2],
					D2DrlgTileDataStrc(& pTileDatas)[8]
				) {
					for (auto i = 0; i < 8; ++i)
					{
						pTileDatas[i].dwFlags = flags[i];
						// Each room tile has two lists of two tiles
						pTileDatas[i].unk0x20 = i % 2 == 0 ? &pTileDatas[i + 1] : nullptr;
					}

					for (auto i = 0; i < 2; ++i)
					{
						pLvlWarps[i].dwLevelId = 10 * (i + 1);
						pRoomTiles[i].pLvlWarpTxtRecord = &pLvlWarps[i];
						pRoomTiles[i].unk0x0C = &pTileDatas[4 * i];
						pRoomTiles[i].unk0x10 = &pTileDatas[4 * i + 2];
						pRoomTiles[i].pNext = i < 1 ? &pRoomTiles[i + 1] : nullptr;
					}

					pDrlgRoom.pRoomTiles = &pRoomTiles[0];
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pRoomTiles, moo_pLvlWarps, moo_pTileDatas);
				setup_data(original_pRoom, original_pDrlgRoom, original_pRoomTiles, original_pLvlWarps, original_pTileDatas);

				// Call both implementations
				sut(&moo_pRoom, nLevelId);
				original(&original_pRoom, nLevelId);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

				for (auto i = 0; i < 8; ++i)
				{
					MOO_CHECK_EQ(moo_pTileDatas[i], original_pTileDatas[i], "Comparing pTileDatas");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D260 (#10092)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdateWarpRoomDeselect, dll_base + 0x0004D260);

		SUBCASE("")
		{
			for (auto level_id = 10; level_id <= 30; level_id += 10)
			{
				// Input data
				uint32_t flags[8]{};
				for (auto i = 0; i < 8; ++i)
				{
					flags[i] = random_unsigned_integer();
				}

				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2RoomTileStrc moo_pRoomTiles[2]{};
				D2LvlWarpTxt moo_pLvlWarps[2]{};
				D2DrlgTileDataStrc moo_pTileDatas[8]{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2RoomTileStrc original_pRoomTiles[2]{};
				D2LvlWarpTxt original_pLvlWarps[2]{};
				D2DrlgTileDataStrc original_pTileDatas[8]{};
				int nLevelId = level_id;

				const auto setup_data = [flags](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2RoomTileStrc(& pRoomTiles)[2],
					D2LvlWarpTxt(& pLvlWarps)[2],
					D2DrlgTileDataStrc(& pTileDatas)[8]
				) {
					for (auto i = 0; i < 8; ++i)
					{
						pTileDatas[i].dwFlags = flags[i];
						// Each room tile has two lists of two tiles
						pTileDatas[i].unk0x20 = i % 2 == 0 ? &pTileDatas[i + 1] : nullptr;
					}

					for (auto i = 0; i < 2; ++i)
					{
						pLvlWarps[i].dwLevelId = 10 * (i + 1);
						pRoomTiles[i].pLvlWarpTxtRecord = &pLvlWarps[i];
						pRoomTiles[i].unk0x0C = &pTileDatas[4 * i];
						pRoomTiles[i].unk0x10 = &pTileDatas[4 * i + 2];
						pRoomTiles[i].pNext = i < 1 ? &pRoomTiles[i + 1] : nullptr;
					}

					pDrlgRoom.pRoomTiles = &pRoomTiles[0];
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pRoomTiles, moo_pLvlWarps, moo_pTileDatas);
				setup_data(original_pRoom, original_pDrlgRoom, original_pRoomTiles, original_pLvlWarps, original_pTileDatas);

				// Call both implementations
				sut(&moo_pRoom, nLevelId);
				original(&original_pRoom, nLevelId);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

				for (auto i = 0; i < 8; ++i)
				{
					MOO_CHECK_EQ(moo_pTileDatas[i], original_pTileDatas[i], "Comparing pTileDatas");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D2A0 (#10093)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_UpdatePops, dll_base + 0x0004D2A0);

		SUBCASE("")
		{
			for (auto bOtherRoom : { FALSE, TRUE })
			{
				// Input data
				int orientations[2]{};
				for (auto i = 0; i < 2; ++i)
				{
					orientations[i] = random_unsigned_integer(1, 1000);
				}

				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
				D2DrlgTileGridStrc moo_pTileGrid{};
				D2DrlgPresetRoomStrc moo_pPresetRoom{};
				D2DrlgMapStrc moo_pDrlgMap{};
				D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
				int32_t moo_pPopsIndex[2]{};
				int32_t moo_pPopsSubIndex[2]{};
				int32_t moo_pPopsOrientation[2]{};
				D2DrlgCoordStrc moo_pPopsLocation[2]{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgRoomStrc* original_ppRoomsNear[1]{};
				D2DrlgTileGridStrc original_pTileGrid{};
				D2DrlgPresetRoomStrc original_pPresetRoom{};
				D2DrlgMapStrc original_pDrlgMap{};
				D2LvlPrestTxt original_pLvlPrestTxtRecord{};
				int32_t original_pPopsIndex[2]{};
				int32_t original_pPopsSubIndex[2]{};
				int32_t original_pPopsOrientation[2]{};
				D2DrlgCoordStrc original_pPopsLocation[2]{};
				// The coordinates are not inside of any pop, so the pops of the room are reset without depending on the current tick count
				int nX = 100;
				int nY = 100;

				const auto setup_data = [orientations](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgRoomStrc*(& ppRoomsNear)[1],
					D2DrlgTileGridStrc& pTileGrid,
					D2DrlgPresetRoomStrc& pPresetRoom,
					D2DrlgMapStrc& pDrlgMap,
					D2LvlPrestTxt& pLvlPrestTxtRecord,
					int32_t(& pPopsIndex)[2],
					int32_t(& pPopsSubIndex)[2],
					int32_t(& pPopsOrientation)[2],
					D2DrlgCoordStrc(& pPopsLocation)[2]
				) {
					for (auto i = 0; i < 2; ++i)
					{
						pPopsIndex[i] = i + 1;
						pPopsSubIndex[i] = i;
						pPopsOrientation[i] = orientations[i];
						pPopsLocation[i].nPosX = 2 * i;
						pPopsLocation[i].nPosY = 2 * i;
						pPopsLocation[i].nWidth = 1;
						pPopsLocation[i].nHeight = 1;
					}

					pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;
					pDrlgMap.nPops = 2;
					pDrlgMap.pPopsIndex = &pPopsIndex[0];
					pDrlgMap.pPopsSubIndex = &pPopsSubIndex[0];
					pDrlgMap.pPopsOrientation = &pPopsOrientation[0];
					pDrlgMap.pPopsLocation = &pPopsLocation[0];
					pPresetRoom.pMap = &pDrlgMap;

					// The room is an active preset room without any tiles, which is only near to itself
					pDrlgRoom.nType = DRLGTYPE_PRESET;
					pDrlgRoom.pMaze = &pPresetRoom;
					pDrlgRoom.pTileGrid = &pTileGrid;
					ppRoomsNear[0] = &pDrlgRoom;
					pDrlgRoom.ppRoomsNear = &ppRoomsNear[0];
					pDrlgRoom.nRoomsNear = 1;
					pDrlgRoom.pRoom = &pRoom;
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_ppRoomsNear, moo_pTileGrid, moo_pPresetRoom, moo_pDrlgMap, moo_pLvlPrestTxtRecord, moo_pPopsIndex, moo_pPopsSubIndex, moo_pPopsOrientation, moo_pPopsLocation);
				setup_data(original_pRoom, original_pDrlgRoom, original_ppRoomsNear, original_pTileGrid, original_pPresetRoom, original_pDrlgMap, original_pLvlPrestTxtRecord, original_pPopsIndex, original_pPopsSubIndex, original_pPopsOrientation, original_pPopsLocation);

				// Call both implementations
				sut(&moo_pRoom, nX, nY, bOtherRoom);
				original(&original_pRoom, nX, nY, bOtherRoom);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

				// Check specific values
				for (auto i = 0; i < 2; ++i)
				{
					CHECK_EQ(moo_pPopsOrientation[i], original_pPopsOrientation[i]);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D2E0 (#10094)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetTombStoneTileCoords, dll_base + 0x0004D2E0);

		SUBCASE("")
		{
			for (auto type : { DRLGTYPE_MAZE, DRLGTYPE_PRESET, DRLGTYPE_OUTDOOR })
			{
				// Input data
				const auto tombstone_tiles = random_unsigned_integer(1, 3);
				D2CoordStrc coords[3]{};
				for (auto i = 0; i < 3; ++i)
				{
					coords[i].nX = random_unsigned_integer(0, 1000);
					coords[i].nY = random_unsigned_integer(0, 1000);
				}

				D2ActiveRoomStrc moo_pRoom{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgPresetRoomStrc moo_pPresetRoom{};
				D2CoordStrc moo_pTombStoneTiles[3]{};
				D2CoordStrc* moo_ppTombStoneTiles{};
				int moo_pnTombStoneTiles{};
				D2ActiveRoomStrc original_pRoom{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgPresetRoomStrc original_pPresetRoom{};
				D2CoordStrc original_pTombStoneTiles[3]{};
				D2CoordStrc* original_ppTombStoneTiles{};
				int original_pnTombStoneTiles{};

				const auto setup_data = [type, tombstone_tiles, coords](
					D2ActiveRoomStrc& pRoom,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgPresetRoomStrc& pPresetRoom,
					D2CoordStrc(& pTombStoneTiles)[3]
				) {
					for (auto i = 0; i < 3; ++i)
					{
						pTombStoneTiles[i] = coords[i];
					}

					pPresetRoom.pTombStoneTiles = &pTombStoneTiles[0];
					pPresetRoom.nTombStoneTiles = tombstone_tiles;

					pDrlgRoom.nType = type;
					if (type == DRLGTYPE_PRESET)
					{
						pDrlgRoom.pMaze = &pPresetRoom;
					}
					pRoom.pDrlgRoom = &pDrlgRoom;
				};

				setup_data(moo_pRoom, moo_pDrlgRoom, moo_pPresetRoom, moo_pTombStoneTiles);
				setup_data(original_pRoom, original_pDrlgRoom, original_pPresetRoom, original_pTombStoneTiles);

				// Call both implementations
				sut(&moo_pRoom, &moo_ppTombStoneTiles, &moo_pnTombStoneTiles);
				original(&original_pRoom, &original_ppTombStoneTiles, &original_pnTombStoneTiles);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_ppTombStoneTiles, original_ppTombStoneTiles, "Comparing ppTombStoneTiles");
				MOO_CHECK_EQ(moo_pnTombStoneTiles, original_pnTombStoneTiles, "Comparing pnTombStoneTiles");

				// Check specific values
				CHECK_EQ(moo_ppTombStoneTiles == &moo_pTombStoneTiles[0], original_ppTombStoneTiles == &original_pTombStoneTiles[0]);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D300 (#10095)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10095, dll_base + 0x0004D300);

		SUBCASE("")
		{
			for (auto x = -10; x < 110; x += 7)
			{
				for (auto y = -10; y < 60; y += 7)
				{
					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2ActiveRoomStrc moo_pAdjacentRoom{};
					D2ActiveRoomStrc* moo_pRoomList[1]{};
					D2DrlgRoomStrc moo_pDrlgRooms[2]{};
					D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfos[2]{};
					D2RoomCoordListStrc moo_pRoomCoordLists[2]{};
					D2ActiveRoomStrc original_pRoom{};
					D2ActiveRoomStrc original_pAdjacentRoom{};
					D2ActiveRoomStrc* original_pRoomList[1]{};
					D2DrlgRoomStrc original_pDrlgRooms[2]{};
					D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfos[2]{};
					D2RoomCoordListStrc original_pRoomCoordLists[2]{};
					int nX = x;
					int nY = y;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom,
						D2ActiveRoomStrc& pAdjacentRoom,
						D2ActiveRoomStrc*(& pRoomList)[1],
						D2DrlgRoomStrc(& pDrlgRooms)[2],
						D2DrlgLogicalRoomInfoStrc(& pLogicalRoomInfos)[2],
						D2RoomCoordListStrc(& pRoomCoordLists)[2]
					) {
						D2ActiveRoomStrc* pRooms[2] = { &pRoom, &pAdjacentRoom };
						for (auto i = 0; i < 2; ++i)
						{
							// Both rooms have a single coord list
							pRoomCoordLists[i].nIndex = 3 + 4 * i;
							pLogicalRoomInfos[i].dwFlags = DRLGLOGIC_ROOMINFO_HAS_COORD_LIST;
							pLogicalRoomInfos[i].nLists = 1;
							pLogicalRoomInfos[i].pCoordList = &pRoomCoordLists[i];
							pDrlgRooms[i].pLogicalRoomInfo = &pLogicalRoomInfos[i];

							pRooms[i]->pDrlgRoom = &pDrlgRooms[i];
							pRooms[i]->tCoords.nSubtileX = 50 * i;
							pRooms[i]->tCoords.nSubtileY = 0;
							pRooms[i]->tCoords.nSubtileWidth = 50;
							pRooms[i]->tCoords.nSubtileHeight = 50;
						}

						pRoomList[0] = &pAdjacentRoom;
						pRoom.ppRoomList = &pRoomList[0];
						pRoom.nNumRooms = 1;
					};

					setup_data(moo_pRoom, moo_pAdjacentRoom, moo_pRoomList, moo_pDrlgRooms, moo_pLogicalRoomInfos, moo_pRoomCoordLists);
					setup_data(original_pRoom, original_pAdjacentRoom, original_pRoomList, original_pDrlgRooms, original_pLogicalRoomInfos, original_pRoomCoordLists);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX, nY);
					const auto original_result = original(&original_pRoom, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D3A0 (#10096)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10096, dll_base + 0x0004D3A0);

		SUBCASE("")
		{
			// Input data
			const auto index = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo{};
			D2RoomCoordListStrc original_pRoomCoordList{};
			int nX = random_unsigned_integer(0, 1000);
			int nY = random_unsigned_integer(0, 1000);

			const auto setup_data = [index](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo,
				D2RoomCoordListStrc& pRoomCoordList
			) {
				// The room has a single coord list, which is returned for all coordinates
				pRoomCoordList.nIndex = index;
				pLogicalRoomInfo.dwFlags = DRLGLOGIC_ROOMINFO_HAS_COORD_LIST;
				pLogicalRoomInfo.nLists = 1;
				pLogicalRoomInfo.pCoordList = &pRoomCoordList;
				pDrlgRoom.pLogicalRoomInfo = &pLogicalRoomInfo;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pLogicalRoomInfo, moo_pRoomCoordList);
			setup_data(original_pRoom, original_pDrlgRoom, original_pLogicalRoomInfo, original_pRoomCoordList);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nX, nY);
			const auto original_result = original(&original_pRoom, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pRoomCoordList);
			CHECK_EQ(original_result, &original_pRoomCoordList);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D3C0 (#10097)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetRoomCoordList, dll_base + 0x0004D3C0);

		SUBCASE("")
		{
			// Input data
			const auto index = random_unsigned_integer(0, 100);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo{};
			D2RoomCoordListStrc original_pRoomCoordList{};

			const auto setup_data = [index](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo,
				D2RoomCoordListStrc& pRoomCoordList
			) {
				pRoomCoordList.nIndex = index;
				pLogicalRoomInfo.dwFlags = DRLGLOGIC_ROOMINFO_HAS_COORD_LIST;
				pLogicalRoomInfo.nLists = 1;
				pLogicalRoomInfo.pCoordList = &pRoomCoordList;
				pDrlgRoom.pLogicalRoomInfo = &pLogicalRoomInfo;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_pLogicalRoomInfo, moo_pRoomCoordList);
			setup_data(original_pRoom, original_pDrlgRoom, original_pLogicalRoomInfo, original_pRoomCoordList);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pRoomCoordList);
			CHECK_EQ(original_result, &original_pRoomCoordList);
		}
	}
	
	TEST_CASE_FIXTURE(PortalLevelsFixture<NoopFixture>, "D2Common.0x6FD8D3D0 (#10098)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_GetPortalLevelArrayFromPortalFlags, dll_base + 0x0004D3D0);
		
		SUBCASE("")
		{
			// Input data
			int* moo_ppLevels = nullptr;
			int moo_pnLevels{};
			int* original_ppLevels = nullptr;
			int original_pnLevels{};
			int nFlags = 1;

			// Call both implementations
			sut(nullptr, nFlags, &moo_ppLevels, &moo_pnLevels);
			original(nullptr, nFlags, &original_ppLevels, &original_pnLevels);

			// Compare potentially modified input data
			MOO_CHECK_EQ((DynamicArray<int> { moo_ppLevels, moo_pnLevels }), (DynamicArray<int> { original_ppLevels, original_pnLevels }), "Comparing ppLevels");
			MOO_CHECK_EQ(moo_pnLevels, original_pnLevels, "Comparing pnLevels");
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
			// Input data
			const auto town_id = random_unsigned_integer();

			D2DrlgActStrc moo_pAct{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [town_id](
				D2DrlgActStrc& pAct
			) {
				pAct.nTownId = town_id;
			};

			setup_data(moo_pAct);
			setup_data(original_pAct);

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
			// Input data
			const auto staff_tomb_level = random_unsigned_integer();

			D2DrlgActStrc moo_pAct{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgActStrc original_pAct{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [staff_tomb_level](
				D2DrlgActStrc& pAct,
				D2DrlgStrc& pDrlg
			) {
				pDrlg.nStaffTombLevel = staff_tomb_level;
				pAct.pDrlg = &pDrlg;
			};

			setup_data(moo_pAct, moo_pDrlg);
			setup_data(original_pAct, original_pDrlg);

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
			// Input data
			const auto flags = random_unsigned_integer();

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			BOOL bReset = FALSE;

			const auto setup_data = [flags](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pDrlgRoom.dwFlags = flags;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom);
			setup_data(original_pRoom, original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pRoom, bReset);
			original(&original_pRoom, bReset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}

		SUBCASE("bReset = TRUE")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			BOOL bReset = TRUE;

			const auto setup_data = [flags](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pDrlgRoom.dwFlags = flags;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom);
			setup_data(original_pRoom, original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pRoom, bReset);
			original(&original_pRoom, bReset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D560 (#10104)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_AnimateTiles, dll_base + 0x0004D560);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto frames = random_unsigned_integer(1, 4);
			const auto current_frame = random_unsigned_integer(0, (frames << 8) - 1);
			const auto animation_speed = random_unsigned_integer(1, 0x100);

			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgAnimTileGridStrc moo_pAnimTileGrid{};
			D2DrlgTileDataStrc* moo_ppMapTileData[4]{};
			D2DrlgTileDataStrc moo_pTileDatas[4]{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgAnimTileGridStrc original_pAnimTileGrid{};
			D2DrlgTileDataStrc* original_ppMapTileData[4]{};
			D2DrlgTileDataStrc original_pTileDatas[4]{};

			const auto setup_data = [frames, current_frame, animation_speed](
				D2ActiveRoomStrc& pRoom,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc*(& ppRoomsNear)[1],
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgAnimTileGridStrc& pAnimTileGrid,
				D2DrlgTileDataStrc*(& ppMapTileData)[4],
				D2DrlgTileDataStrc(& pTileDatas)[4]
			) {
				// Only the tile of the current frame is visible
				for (auto i = 0; i < 4; ++i)
				{
					pTileDatas[i].dwFlags = i == (current_frame >> 8) ? 0 : MAPTILE_HIDDEN;
					ppMapTileData[i] = &pTileDatas[i];
				}

				pAnimTileGrid.ppMapTileData = &ppMapTileData[0];
				pAnimTileGrid.nFrames = frames;
				pAnimTileGrid.nCurrentFrame = current_frame;
				pAnimTileGrid.nAnimationSpeed = animation_speed;
				pTileGrid.pAnimTiles = &pAnimTileGrid;

				// The room has an animated floor and is only near to itself
				pDrlgRoom.dwFlags = DRLGROOMFLAG_ANIMATED_FLOOR;
				pDrlgRoom.pTileGrid = &pTileGrid;
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = &ppRoomsNear[0];
				pDrlgRoom.nRoomsNear = 1;
				pRoom.pDrlgRoom = &pDrlgRoom;
			};

			setup_data(moo_pRoom, moo_pDrlgRoom, moo_ppRoomsNear, moo_pTileGrid, moo_pAnimTileGrid, moo_ppMapTileData, moo_pTileDatas);
			setup_data(original_pRoom, original_pDrlgRoom, original_ppRoomsNear, original_pTileGrid, original_pAnimTileGrid, original_ppMapTileData, original_pTileDatas);

			for (auto i = 0; i < 10; ++i)
			{
				// Call both implementations
				sut(&moo_pRoom);
				original(&original_pRoom);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

				// Check specific values
				CHECK_EQ(moo_pAnimTileGrid.nCurrentFrame, original_pAnimTileGrid.nCurrentFrame);
				for (auto j = 0; j < 4; ++j)
				{
					MOO_CHECK_EQ(moo_pTileDatas[j], original_pTileDatas[j], "Comparing pTileDatas");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D580 (#10105)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_InitRoomTileAnimation, dll_base + 0x0004D580);

		SUBCASE("")
		{
			for (auto room1_in_act : { 0, 1 })
			{
				// Input data
				const auto current_frame = random_unsigned_integer(1, 0x3FF);

				D2DrlgActStrc moo_pAct{};
				D2ActiveRoomStrc moo_pRoom1{};
				D2ActiveRoomStrc moo_pRoom2{};
				D2ActiveRoomStrc moo_pOtherRoom{};
				D2DrlgRoomStrc moo_pDrlgRooms[2]{};
				D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
				D2DrlgTileGridStrc moo_pTileGrids[2]{};
				D2DrlgAnimTileGridStrc moo_pAnimTileGrids[2]{};
				D2DrlgActStrc original_pAct{};
				D2ActiveRoomStrc original_pRoom1{};
				D2ActiveRoomStrc original_pRoom2{};
				D2ActiveRoomStrc original_pOtherRoom{};
				D2DrlgRoomStrc original_pDrlgRooms[2]{};
				D2DrlgRoomStrc* original_ppRoomsNear[2]{};
				D2DrlgTileGridStrc original_pTileGrids[2]{};
				D2DrlgAnimTileGridStrc original_pAnimTileGrids[2]{};

				const auto setup_data = [room1_in_act, current_frame](
					D2DrlgActStrc& pAct,
					D2ActiveRoomStrc& pRoom1,
					D2ActiveRoomStrc& pRoom2,
					D2ActiveRoomStrc& pOtherRoom,
					D2DrlgRoomStrc(& pDrlgRooms)[2],
					D2DrlgRoomStrc*(& ppRoomsNear)[2],
					D2DrlgTileGridStrc(& pTileGrids)[2],
					D2DrlgAnimTileGridStrc(& pAnimTileGrids)[2]
				) {
					// Both rooms are only near to themselves and have animated tiles
					D2ActiveRoomStrc* pRooms[2] = { &pRoom1, &pRoom2 };
					for (auto i = 0; i < 2; ++i)
					{
						pTileGrids[i].pAnimTiles = &pAnimTileGrids[i];
						pDrlgRooms[i].pTileGrid = &pTileGrids[i];
						ppRoomsNear[i] = &pDrlgRooms[i];
						pDrlgRooms[i].ppRoomsNear = &ppRoomsNear[i];
						pDrlgRooms[i].nRoomsNear = 1;
						pRooms[i]->pDrlgRoom = &pDrlgRooms[i];
					}

					// The animation frame of the first room is expected to be copied to the second room
					pAnimTileGrids[0].nCurrentFrame = current_frame;

					// The first room is only taken into account if it is in the act's room list
					pAct.pRoom = &pOtherRoom;
					if (room1_in_act)
					{
						pOtherRoom.pRoomNext = &pRoom1;
					}
				};

				setup_data(moo_pAct, moo_pRoom1, moo_pRoom2, moo_pOtherRoom, moo_pDrlgRooms, moo_ppRoomsNear, moo_pTileGrids, moo_pAnimTileGrids);
				setup_data(original_pAct, original_pRoom1, original_pRoom2, original_pOtherRoom, original_pDrlgRooms, original_ppRoomsNear, original_pTileGrids, original_pAnimTileGrids);

				// Call both implementations
				sut(&moo_pAct, &moo_pRoom1, &moo_pRoom2);
				original(&original_pAct, &original_pRoom1, &original_pRoom2);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
				MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
				MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");

				// Check specific values
				for (auto i = 0; i < 2; ++i)
				{
					CHECK_EQ(moo_pAnimTileGrids[i].nCurrentFrame, original_pAnimTileGrids[i].nCurrentFrame);
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD8D5C0 (#10103)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DUNGEON_SetActCallbackFunc, dll_base + 0x0004D5C0);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgActStrc moo_pAct{};
			D2DrlgActStrc original_pAct{};
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
				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};
			int nX{};
			int nY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};
			int nX{};
			int nY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};
			int nX{};
			int nY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
					pX = x;
					pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

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
			// Input data
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			int moo_pX{};
			int moo_pY{};
			int original_pX{};
			int original_pY{};
			int nX{};
			int nY{};

			const auto setup_data = [x, y](
				int& pX,
				int& pY
			) {
				pX = x;
				pY = y;
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

			// Call both implementations
			sut(nX, nY, &moo_pX, &moo_pY);
			original(nX, nY, &original_pX, &original_pY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
}

#endif
