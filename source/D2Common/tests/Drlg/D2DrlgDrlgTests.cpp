#include <D2CommonTestDefines.h>

#ifdef DRLG_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgOutdoors.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("D2DrlgDrlgTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<LvlPrestTxtFixture<NoopFixture>>>, "D2Common.0x6FD74120 (#10014)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_AllocDrlg, dll_base + 0x00034120);

		SUBCASE("")
		{
			// Input data
			D2DrlgActStrc moo_pAct{};
			D2DrlgActStrc original_pAct{};
			// Acts I to III load tile libraries with D2CMP, so Act IV is used to only create the level connections
			uint8_t nActNo = ACT_IV;
			HD2ARCHIVE hArchive = nullptr;
			uint32_t nInitSeed = 0x12345678;
			// Initializing the town level would require the DS1 files
			int nLevelId = LEVEL_NONE;
			uint32_t nFlags = DRLGFLAG_ONCLIENT;
			uint8_t nDifficulty = GENERATE(0, 1, 2);
			AUTOMAPFN pfAutoMap = nullptr;
			TOWNAUTOMAPFN pfTownAutoMap = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nActNo, hArchive, nInitSeed, nLevelId, nFlags, nullptr, nDifficulty, pfAutoMap, pfTownAutoMap);
			const auto original_result = original(&original_pAct, nActNo, hArchive, nInitSeed, nLevelId, nFlags, nullptr, nDifficulty, pfAutoMap, pfTownAutoMap);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
		}
	}

	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<LvlPrestTxtFixture<NoopFixture>>>, "D2Common.0x6FD743B0 (#10012)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_FreeDrlg, dll_base + 0x000343B0);
		const auto [moo_alloc, original_alloc] = make_function_pair(DRLG_AllocDrlg, dll_base + 0x00034120);

		SUBCASE("")
		{
			// Input data
			D2DrlgActStrc moo_pAct{};
			D2DrlgActStrc original_pAct{};
			uint32_t nInitSeed = 0x12345678;

			// Allocate a Drlg with levels and warps, so that these get freed as well
			D2DrlgStrc* moo_pDrlg = moo_alloc(&moo_pAct, ACT_IV, nullptr, nInitSeed, LEVEL_NONE, 0, nullptr, 0, nullptr, nullptr);
			D2DrlgStrc* original_pDrlg = original_alloc(&original_pAct, ACT_IV, nullptr, nInitSeed, LEVEL_NONE, 0, nullptr, 0, nullptr, nullptr);

			// Call both implementations
			sut(moo_pDrlg);
			original(original_pDrlg);

			// Input data can not be compared since it was freed
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74440")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_FreeLevel, dll_base + 0x00034440);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			// Keeps the outdoor info, which is not allocated from the memory pool
			BOOL bAlloc = TRUE;

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgOutdoorInfoStrc& pOutdoors
			) {
				pOutdoors.dwFlags = 0x20 | 0x40 | 0x01;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_BLOODMOOR;
				pLevel.nDrlgType = DRLGTYPE_OUTDOOR;
				pLevel.pOutdoors = &pOutdoors;

				// Data that gets reset
				pLevel.pTileInfo[0].nPosX = 3;
				pLevel.pTileInfo[0].nPosY = 4;
				pLevel.pTileInfo[0].nTileIndex = 5;
				pLevel.nTileInfo = 1;
				pLevel.nRoom_Center_Warp_X[0] = 10;
				pLevel.nRoom_Center_Warp_Y[0] = 20;
				pLevel.nRoomCoords = 1;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors);
			setup_data(original_pLevel, original_pDrlg, original_pOutdoors);

			// Call both implementations
			sut(nullptr, &moo_pLevel, bAlloc);
			original(nullptr, &original_pLevel, bAlloc);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD745C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD745C0, dll_base + 0x000345C0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom1{};
			D2DrlgRoomStrc moo_pDrlgRoom2{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevels[2]{};
			D2DrlgWarpStrc moo_pWarps[2]{};
			D2DrlgRoomStrc original_pDrlgRoom1{};
			D2DrlgRoomStrc original_pDrlgRoom2{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevels[2]{};
			D2DrlgWarpStrc original_pWarps[2]{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom1,
				D2DrlgRoomStrc& pDrlgRoom2,
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc(& pLevels)[2],
				D2DrlgWarpStrc(& pWarps)[2]
			) {
				// Both levels are visible from each other
				pWarps[0].nLevel = LEVEL_BLOODMOOR;
				pWarps[0].nVis[0] = LEVEL_COLDPLAINS;
				pWarps[0].pNext = &pWarps[1];
				pWarps[1].nLevel = LEVEL_COLDPLAINS;
				pWarps[1].nVis[0] = LEVEL_BLOODMOOR;

				pLevels[0].pDrlg = &pDrlg;
				pLevels[0].nLevelId = LEVEL_BLOODMOOR;
				pLevels[0].bActive = 1;
				pLevels[0].pNextLevel = &pLevels[1];
				pLevels[1].pDrlg = &pDrlg;
				pLevels[1].nLevelId = LEVEL_COLDPLAINS;
				pLevels[1].bActive = 0;

				pDrlg.pLevel = &pLevels[0];
				pDrlg.pWarp = &pWarps[0];

				// Moving from the first level to the second one
				pDrlgRoom1.pLevel = &pLevels[0];
				pDrlgRoom2.pLevel = &pLevels[1];
			};

			setup_data(moo_pDrlgRoom1, moo_pDrlgRoom2, moo_pDrlg, moo_pLevels, moo_pWarps);
			setup_data(original_pDrlgRoom1, original_pDrlgRoom2, original_pDrlg, original_pLevels, original_pWarps);

			// Call both implementations
			sut(&moo_pDrlgRoom1, &moo_pDrlgRoom2);
			original(&original_pDrlgRoom1, &original_pDrlgRoom2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74700")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_UpdateAndFreeInactiveRooms, dll_base + 0x00034700);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevels[3]{};
			D2DrlgRoomStrc moo_pDrlgRooms[3]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevels[3]{};
			D2DrlgRoomStrc original_pDrlgRooms[3]{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc(& pLevels)[3],
				D2DrlgRoomStrc(& pDrlgRooms)[3]
			) {
				for (auto i = 0; i < 3; ++i)
				{
					pLevels[i].pDrlg = &pDrlg;
					pLevels[i].pFirstRoomEx = &pDrlgRooms[i];
					pDrlgRooms[i].pLevel = &pLevels[i];
				}

				pLevels[0].pNextLevel = &pLevels[1];
				pLevels[1].pNextLevel = &pLevels[2];
				pDrlg.pLevel = &pLevels[0];

				// Inactive level whose inactive frames are counted down
				pLevels[0].nLevelId = LEVEL_BLOODMOOR;
				pLevels[0].dwInactiveFrames = 5;

				// Inactive level which still has a room with a client in it, so its inactive frames are reset
				pLevels[1].nLevelId = LEVEL_COLDPLAINS;
				pLevels[1].dwInactiveFrames = 0;
				pDrlgRooms[1].fRoomStatus = ROOMSTATUS_CLIENT_IN_ROOM;

				// Active level which is skipped
				pLevels[2].nLevelId = LEVEL_STONYFIELD;
				pLevels[2].bActive = 1;
				pLevels[2].dwInactiveFrames = 3;
			};

			setup_data(moo_pDrlg, moo_pLevels, moo_pDrlgRooms);
			setup_data(original_pDrlg, original_pLevels, original_pDrlgRooms);

			// Call both implementations
			sut(&moo_pDrlg);
			original(&original_pDrlg);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<LvlMazeTxtFixture<LvlPrestTxtFixture<NoopFixture>>>>, "D2Common.0x6FD748D0 (#10013)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_AllocLevel, dll_base + 0x000348D0);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgStrc original_pDrlg{};
			// Outdoor, maze and preset level
			int nLevelId = GENERATE(LEVEL_BLOODMOOR, LEVEL_DENOFEVIL, LEVEL_LUTGHOLEIN);

			const auto setup_data = [](
				D2DrlgStrc& pDrlg
			) {
				pDrlg.dwStartSeed = 0x12345678;
				pDrlg.dwFlags = DRLGFLAG_ONCLIENT;
			};

			setup_data(moo_pDrlg);
			setup_data(original_pDrlg);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<NoopFixture>>, "D2Common.0x6FD749A0 (#10005)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetLevel, dll_base + 0x000349A0);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevels[2]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevels[2]{};
			// Two existing levels and one outdoor level which needs to be allocated
			int nLevelId = GENERATE(LEVEL_BLOODMOOR, LEVEL_COLDPLAINS, LEVEL_STONYFIELD);

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc(& pLevels)[2]
			) {
				pLevels[0].pDrlg = &pDrlg;
				pLevels[0].nLevelId = LEVEL_BLOODMOOR;
				pLevels[0].pNextLevel = &pLevels[1];
				pLevels[1].pDrlg = &pDrlg;
				pLevels[1].nLevelId = LEVEL_COLDPLAINS;

				pDrlg.pLevel = &pLevels[0];
				pDrlg.dwStartSeed = 0x12345678;
			};

			setup_data(moo_pDrlg, moo_pLevels);
			setup_data(original_pDrlg, original_pLevels);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD749D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetHoradricStaffTombLevelId, dll_base + 0x000349D0);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg
			) {
				pDrlg.nStaffTombLevel = LEVEL_TALRASHASTOMB1 + 3;
				pDrlg.nBossTombLevel = LEVEL_TALRASHASTOMB1 + 5;
			};

			setup_data(moo_pDrlg);
			setup_data(original_pDrlg);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg);
			const auto original_result = original(&original_pDrlg);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD749E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetDirectionFromCoordinates, dll_base + 0x000349E0);

		SUBCASE("")
		{
			// Positions of the second coordinates, which are adjacent to the first ones in every direction, or not adjacent at all
			const int nPositionsX[] = { 2, 5, 10, 15, 30 };
			const int nPositionsY[] = { 6, 12, 20, 28, 40 };

			for (const auto nPosX : nPositionsX)
			{
				for (const auto nPosY : nPositionsY)
				{
					// Input data
					D2DrlgCoordStrc moo_pDrlgCoord1{};
					D2DrlgCoordStrc moo_pDrlgCoord2{};
					D2DrlgCoordStrc original_pDrlgCoord1{};
					D2DrlgCoordStrc original_pDrlgCoord2{};

					const auto setup_data = [nPosX, nPosY](
						D2DrlgCoordStrc& pDrlgCoord1,
						D2DrlgCoordStrc& pDrlgCoord2
					) {
						pDrlgCoord1.nPosX = 10;
						pDrlgCoord1.nPosY = 20;
						pDrlgCoord1.nWidth = 5;
						pDrlgCoord1.nHeight = 8;

						pDrlgCoord2.nPosX = nPosX;
						pDrlgCoord2.nPosY = nPosY;
						pDrlgCoord2.nWidth = 5;
						pDrlgCoord2.nHeight = 8;
					};

					setup_data(moo_pDrlgCoord1, moo_pDrlgCoord2);
					setup_data(original_pDrlgCoord1, original_pDrlgCoord2);

					// Call both implementations
					const auto moo_result = sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2);
					const auto original_result = original(&original_pDrlgCoord1, &original_pDrlgCoord2);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
					MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74A40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_CreateRoomForRoomEx, dll_base + 0x00034A40);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgActStrc moo_pAct{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pFloorTile{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgActStrc original_pAct{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pFloorTile{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgActStrc& pAct,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc& pFloorTile,
				D2DrlgRoomStrc* (& ppRoomsNear)[1]
			) {
				pDrlg.pAct = &pAct;
				pAct.pDrlg = &pDrlg;

				// The room needs floors or walls for an active room to be allocated.
				// The floor tile is outside of the room, so its tile library entry (loaded by D2CMP) is not used for the collision.
				pFloorTile.nPosX = 100;
				pFloorTile.nPosY = 100;
				pTileGrid.pTiles.pFloorTiles = &pFloorTile;
				pTileGrid.pTiles.nFloors = 1;

				// A room is always near itself
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 1;

				pDrlgRoom.nTileXPos = 2;
				pDrlgRoom.nTileYPos = 3;
				pDrlgRoom.nTileWidth = 4;
				pDrlgRoom.nTileHeight = 5;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_AUTOMAP_REVEAL;
				pDrlgRoom.pTileGrid = &pTileGrid;
				pDrlgRoom.pSeed.nLowSeed = 0x12345678;
				pDrlgRoom.pSeed.nHighSeed = 0x29A;
			};

			setup_data(moo_pDrlg, moo_pDrlgRoom, moo_pAct, moo_pTileGrid, moo_pFloorTile, moo_ppRoomsNear);
			setup_data(original_pDrlg, original_pDrlgRoom, original_pAct, original_pTileGrid, original_pFloorTile, original_ppRoomsNear);

			// Call both implementations
			sut(&moo_pDrlg, &moo_pDrlgRoom);
			original(&original_pDrlg, &original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74B30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetRoomCenterX_RoomWarpXFromRoom, dll_base + 0x00034B30);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel
			) {
				pLevel.nRoom_Center_Warp_X[0] = 123;
				pLevel.nRoom_Center_Warp_Y[0] = 456;
				pLevel.nRoomCoords = 1;

				pDrlgRoom.pLevel = &pLevel;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel);
			setup_data(original_pDrlgRoom, original_pLevel);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74B40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_ComputeLevelWarpInfo, dll_base + 0x00034B40);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2DrlgRoomStrc moo_pDrlgRooms[4]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			D2DrlgRoomStrc original_pDrlgRooms[4]{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp,
				D2DrlgRoomStrc(& pDrlgRooms)[4]
			) {
				// Only the second warp has a destination
				pWarp.nLevel = LEVEL_BLOODMOOR;
				for (auto i = 0; i < 8; ++i)
				{
					pWarp.nWarp[i] = -1;
				}
				pWarp.nVis[1] = LEVEL_COLDPLAINS;
				pWarp.nWarp[1] = 2;

				pDrlg.pWarp = &pWarp;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_BLOODMOOR;
				pLevel.pFirstRoomEx = &pDrlgRooms[0];
				pLevel.nRooms = 4;

				for (auto i = 0; i < 4; ++i)
				{
					pDrlgRooms[i].pLevel = &pLevel;
					pDrlgRooms[i].nTileXPos = 8 * i;
					pDrlgRooms[i].nTileYPos = 4 * i + 1;
					pDrlgRooms[i].nTileWidth = 8;
					pDrlgRooms[i].nTileHeight = 7;

					if (i < 3)
					{
						pDrlgRooms[i].pDrlgRoomNext = &pDrlgRooms[i + 1];
					}
				}

				// Room with a waypoint
				pDrlgRooms[0].dwFlags = DRLGROOMFLAG_HAS_WAYPOINT;
				// Room with a warp that has a destination
				pDrlgRooms[1].dwFlags = DRLGROOMFLAG_HAS_WARP_1;
				// Room with a warp without destination
				pDrlgRooms[2].dwFlags = DRLGROOMFLAG_HAS_WARP_0;
				// Room without any warp
				pDrlgRooms[3].dwFlags = 0;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pWarp, moo_pDrlgRooms);
			setup_data(original_pLevel, original_pDrlg, original_pWarp, original_pDrlgRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74C10 (#10006)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_InitLevel, dll_base + 0x00034C10);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pDrlg.dwStartSeed = 0x12345678;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_BLOODMOOR;
				// Generating maze, preset or outdoor levels requires the DS1 and tile files,
				// so an unknown Drlg type is used for which only the seed gets initialized
				pLevel.nDrlgType = 0;
			};

			setup_data(moo_pLevel, moo_pDrlg);
			setup_data(original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74D50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetNumberOfPopulatedRoomsInLevel, dll_base + 0x00034D50);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRooms[3]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRooms[3]{};
			int nLevelId = LEVEL_BLOODMOOR;

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc(& pDrlgRooms)[3]
			) {
				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_BLOODMOOR;
				pLevel.pFirstRoomEx = &pDrlgRooms[0];
				pLevel.nRooms = 3;

				pDrlgRooms[0].pDrlgRoomNext = &pDrlgRooms[1];
				pDrlgRooms[1].pDrlgRoomNext = &pDrlgRooms[2];

				// The second room is not populated
				pDrlgRooms[1].dwFlags = DRLGROOMFLAG_POPULATION_ZERO;

				pDrlg.pLevel = &pLevel;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pDrlgRooms);
			setup_data(original_pDrlg, original_pLevel, original_pDrlgRooms);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74D90")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetMinAndMaxCoordinatesFromLevel, dll_base + 0x00034D90);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRooms[3]{};
			int moo_pTileMinX{};
			int moo_pTileMinY{};
			int moo_pTileMaxX{};
			int moo_pTileMaxY{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRooms[3]{};
			int original_pTileMinX{};
			int original_pTileMinY{};
			int original_pTileMaxX{};
			int original_pTileMaxY{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc(& pDrlgRooms)[3],
				int& pTileMinX,
				int& pTileMinY,
				int& pTileMaxX,
				int& pTileMaxY
			) {
				pLevel.pFirstRoomEx = &pDrlgRooms[0];
				pLevel.nRooms = 3;

				pDrlgRooms[0].nTileXPos = 10;
				pDrlgRooms[0].nTileYPos = 10;
				pDrlgRooms[0].nTileWidth = 8;
				pDrlgRooms[0].nTileHeight = 8;
				pDrlgRooms[0].pDrlgRoomNext = &pDrlgRooms[1];

				pDrlgRooms[1].nTileXPos = 2;
				pDrlgRooms[1].nTileYPos = 18;
				pDrlgRooms[1].nTileWidth = 8;
				pDrlgRooms[1].nTileHeight = 16;
				pDrlgRooms[1].pDrlgRoomNext = &pDrlgRooms[2];

				pDrlgRooms[2].nTileXPos = 18;
				pDrlgRooms[2].nTileYPos = 4;
				pDrlgRooms[2].nTileWidth = 16;
				pDrlgRooms[2].nTileHeight = 6;

				// Values get overwritten
				pTileMinX = -1;
				pTileMinY = -1;
				pTileMaxX = -1;
				pTileMaxY = -1;
			};

			setup_data(moo_pLevel, moo_pDrlgRooms, moo_pTileMinX, moo_pTileMinY, moo_pTileMaxX, moo_pTileMaxY);
			setup_data(original_pLevel, original_pDrlgRooms, original_pTileMinX, original_pTileMinY, original_pTileMaxX, original_pTileMaxY);

			// Call both implementations
			sut(&moo_pLevel, &moo_pTileMinX, &moo_pTileMinY, &moo_pTileMaxX, &moo_pTileMaxY);
			original(&original_pLevel, &original_pTileMinX, &original_pTileMinY, &original_pTileMaxX, &original_pTileMaxY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pTileMinX, original_pTileMinX, "Comparing pTileMinX");
			MOO_CHECK_EQ(moo_pTileMinY, original_pTileMinY, "Comparing pTileMinY");
			MOO_CHECK_EQ(moo_pTileMaxX, original_pTileMaxX, "Comparing pTileMaxX");
			MOO_CHECK_EQ(moo_pTileMaxY, original_pTileMaxY, "Comparing pTileMaxY");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74E10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_UpdateRoomExCoordinates, dll_base + 0x00034E10);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRooms[3]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRooms[3]{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc(& pDrlgRooms)[3]
			) {
				// The level is big enough to contain all of its rooms
				pLevel.nPosX = 100;
				pLevel.nPosY = 200;
				pLevel.nWidth = 40;
				pLevel.nHeight = 40;
				pLevel.pFirstRoomEx = &pDrlgRooms[0];
				pLevel.nRooms = 3;

				for (auto i = 0; i < 3; ++i)
				{
					pDrlgRooms[i].pLevel = &pLevel;
					pDrlgRooms[i].nTileWidth = 8;
					pDrlgRooms[i].nTileHeight = 8;
				}

				pDrlgRooms[0].nTileXPos = 5;
				pDrlgRooms[0].nTileYPos = 5;
				pDrlgRooms[0].pDrlgRoomNext = &pDrlgRooms[1];

				pDrlgRooms[1].nTileXPos = 13;
				pDrlgRooms[1].nTileYPos = 5;
				pDrlgRooms[1].pDrlgRoomNext = &pDrlgRooms[2];

				pDrlgRooms[2].nTileXPos = 5;
				pDrlgRooms[2].nTileYPos = 13;
			};

			setup_data(moo_pLevel, moo_pDrlgRooms);
			setup_data(original_pLevel, original_pDrlgRooms);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			for (auto i = 0; i < 3; ++i)
			{
				MOO_CHECK_EQ(moo_pDrlgRooms[i], original_pDrlgRooms[i], "Comparing pDrlgRooms");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74EF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetRoomExFromLevelAndCoordinates, dll_base + 0x00034EF0);

		SUBCASE("")
		{
			// Coordinates inside the first room, inside the second room and outside of all rooms
			const int nCoordinates[][2] = { { 3, 4 }, { 12, 4 }, { 30, 30 } };

			for (const auto& [nX, nY] : nCoordinates)
			{
				// Input data
				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgRoomStrc moo_pDrlgRooms[2]{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgRoomStrc original_pDrlgRooms[2]{};

				const auto setup_data = [](
					D2DrlgLevelStrc& pLevel,
					D2DrlgRoomStrc(& pDrlgRooms)[2]
				) {
					pLevel.pFirstRoomEx = &pDrlgRooms[0];
					pLevel.nRooms = 2;

					for (auto i = 0; i < 2; ++i)
					{
						pDrlgRooms[i].pLevel = &pLevel;
						pDrlgRooms[i].nTileXPos = 10 * i;
						pDrlgRooms[i].nTileYPos = 0;
						pDrlgRooms[i].nTileWidth = 10;
						pDrlgRooms[i].nTileHeight = 10;
					}

					pDrlgRooms[0].pDrlgRoomNext = &pDrlgRooms[1];
				};

				setup_data(moo_pLevel, moo_pDrlgRooms);
				setup_data(original_pLevel, original_pDrlgRooms);

				// Call both implementations
				const auto moo_result = sut(&moo_pLevel, nX, nY);
				const auto original_result = original(&original_pLevel, nX, nY);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74F70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetRoomExFromCoordinates, dll_base + 0x00034F70);

		SUBCASE("")
		{
			// Coordinates inside the hint room, inside a room near the hint room, inside a room only found through the level
			// and inside the level, but outside of all rooms. All of them are inside the level, so no other level is needed.
			const int nCoordinates[][2] = { { 5, 5 }, { 15, 5 }, { 5, 15 }, { 15, 15 } };

			for (const auto bPassLevel : { true, false })
			{
				for (const auto& [nX, nY] : nCoordinates)
				{
					// Input data
					D2DrlgStrc moo_pDrlg{};
					D2DrlgRoomStrc moo_pDrlgRoom{};
					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgRoomStrc moo_pDrlgRooms[2]{};
					D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgRoomStrc original_pDrlgRoom{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgRoomStrc original_pDrlgRooms[2]{};
					D2DrlgRoomStrc* original_ppRoomsNear[2]{};

					const auto setup_data = [](
						D2DrlgStrc& pDrlg,
						D2DrlgRoomStrc& pDrlgRoom,
						D2DrlgLevelStrc& pLevel,
						D2DrlgRoomStrc(& pDrlgRooms)[2],
						D2DrlgRoomStrc* (& ppRoomsNear)[2]
					) {
						pLevel.pDrlg = &pDrlg;
						pLevel.nLevelId = LEVEL_BLOODMOOR;
						pLevel.nPosX = 0;
						pLevel.nPosY = 0;
						pLevel.nWidth = 20;
						pLevel.nHeight = 20;
						pLevel.pFirstRoomEx = &pDrlgRoom;
						pLevel.nRooms = 3;

						pDrlg.pLevel = &pLevel;

						// Hint room
						pDrlgRoom.pLevel = &pLevel;
						pDrlgRoom.nTileXPos = 0;
						pDrlgRoom.nTileYPos = 0;
						pDrlgRoom.nTileWidth = 10;
						pDrlgRoom.nTileHeight = 10;
						pDrlgRoom.pDrlgRoomNext = &pDrlgRooms[0];

						// The hint room itself is skipped in the near rooms
						ppRoomsNear[0] = &pDrlgRoom;
						ppRoomsNear[1] = &pDrlgRooms[0];
						pDrlgRoom.ppRoomsNear = ppRoomsNear;
						pDrlgRoom.nRoomsNear = 2;

						// Room near the hint room
						pDrlgRooms[0].pLevel = &pLevel;
						pDrlgRooms[0].nTileXPos = 10;
						pDrlgRooms[0].nTileYPos = 0;
						pDrlgRooms[0].nTileWidth = 10;
						pDrlgRooms[0].nTileHeight = 10;
						pDrlgRooms[0].pDrlgRoomNext = &pDrlgRooms[1];

						// Room only found through the level
						pDrlgRooms[1].pLevel = &pLevel;
						pDrlgRooms[1].nTileXPos = 0;
						pDrlgRooms[1].nTileYPos = 10;
						pDrlgRooms[1].nTileWidth = 10;
						pDrlgRooms[1].nTileHeight = 10;
					};

					setup_data(moo_pDrlg, moo_pDrlgRoom, moo_pLevel, moo_pDrlgRooms, moo_ppRoomsNear);
					setup_data(original_pDrlg, original_pDrlgRoom, original_pLevel, original_pDrlgRooms, original_ppRoomsNear);

					// Call both implementations
					const auto moo_result = sut(nX, nY, &moo_pDrlg, &moo_pDrlgRoom, bPassLevel ? &moo_pLevel : nullptr);
					const auto original_result = original(nX, nY, &original_pDrlg, &original_pDrlgRoom, bPassLevel ? &original_pLevel : nullptr);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
					MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD751C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_IsTownLevel, dll_base + 0x000351C0);

		SUBCASE("")
		{
			for (auto i = 0; i < 256; ++i)
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

	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<NoopFixture>>, "D2Common.0x6FD75260 (#10000)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetLevelTypeFromLevelId, dll_base + 0x00035260);

		SUBCASE("")
		{
			for (auto i = 0; i < leveldefs_record_count; ++i)
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

	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<LvlMazeTxtFixture<LvlPrestTxtFixture<NoopFixture>>>>, "D2Common.0x6FD75270")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_SetLevelPositionAndSize, dll_base + 0x00035270);

		SUBCASE("")
		{
			const auto difficulty = GENERATE(0, 1, 2);

			for (auto i = 0; i < leveldefs_record_count; ++i)
			{
				// Input data
				D2DrlgStrc moo_pDrlg{};
				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgLevelStrc original_pLevel{};

				const auto setup_data = [i, difficulty](
					D2DrlgStrc& pDrlg,
					D2DrlgLevelStrc& pLevel
				) {
					// Used to allocate the level this level depends on, if any
					pDrlg.dwStartSeed = 0x12345678;
					pDrlg.nDifficulty = difficulty;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = i;
				};

				setup_data(moo_pDrlg, moo_pLevel);
				setup_data(original_pDrlg, original_pLevel);

				// Call both implementations
				sut(&moo_pDrlg, &moo_pLevel);
				original(&original_pDrlg, &original_pLevel);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75300 (#10001)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetActNoFromLevelId, dll_base + 0x00035300);

		SUBCASE("")
		{
			for (auto i = 0; i < 256; ++i)
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

	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<NoopFixture>>, "D2Common.0x6FD75330 (#10004)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetSaveMonstersFromLevelId, dll_base + 0x00035330);

		SUBCASE("")
		{
			for (auto i = 0; i < leveldefs_record_count; ++i)
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

	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<NoopFixture>>, "D2Common.0x6FD75350 (#10002)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetLOSDrawFromLevelId, dll_base + 0x00035350);

		SUBCASE("")
		{
			for (auto i = 0; i < leveldefs_record_count; ++i)
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

	TEST_CASE_FIXTURE(LevelsTxtFixture<LevelDefsTxtFixture<NoopFixture>>, "D2Common.0x6FD75370")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetDrlgWarpFromLevelId, dll_base + 0x00035370);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			// Existing warp and warp which needs to be allocated
			int nLevelId = GENERATE(LEVEL_BLOODMOOR, LEVEL_COLDPLAINS);

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp
			) {
				pWarp.nLevel = LEVEL_BLOODMOOR;
				pWarp.nVis[0] = LEVEL_ROGUEENCAMPMENT;
				pWarp.nWarp[0] = 1;

				pDrlg.pWarp = &pWarp;
			};

			setup_data(moo_pDrlg, moo_pWarp);
			setup_data(original_pDrlg, original_pWarp);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD753F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_SetWarpId, dll_base + 0x000353F0);

		SUBCASE("")
		{
			// nVis, nWarp, nId: Existing vis, new vis in the first free slot and new vis in a given slot
			const int nParameters[][3] = {
				{ LEVEL_ROGUEENCAMPMENT, 5, -1 },
				{ LEVEL_DENOFEVIL, 3, -1 },
				{ LEVEL_DENOFEVIL, 3, 4 },
			};

			for (const auto& [nVis, nWarp, nId] : nParameters)
			{
				// Input data
				D2DrlgWarpStrc moo_pDrlgWarp{};
				D2DrlgWarpStrc original_pDrlgWarp{};

				const auto setup_data = [](
					D2DrlgWarpStrc& pDrlgWarp
				) {
					pDrlgWarp.nLevel = LEVEL_BLOODMOOR;
					for (auto i = 0; i < 8; ++i)
					{
						pDrlgWarp.nWarp[i] = -1;
					}
					pDrlgWarp.nVis[0] = LEVEL_ROGUEENCAMPMENT;
					pDrlgWarp.nVis[1] = LEVEL_COLDPLAINS;
					pDrlgWarp.nWarp[1] = 2;
				};

				setup_data(moo_pDrlgWarp);
				setup_data(original_pDrlgWarp);

				// Call both implementations
				sut(&moo_pDrlgWarp, nVis, nWarp, nId);
				original(&original_pDrlgWarp, nVis, nWarp, nId);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgWarp, original_pDrlgWarp, "Comparing pDrlgWarp");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75450")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_IsOnClient, dll_base + 0x00035450);

		SUBCASE("")
		{
			const uint32_t nFlags[] = { 0, DRLGFLAG_ONCLIENT, DRLGFLAG_REFRESH, DRLGFLAG_ONCLIENT | DRLGFLAG_REFRESH };

			for (const auto dwFlags : nFlags)
			{
				// Input data
				D2DrlgStrc moo_pDrlg{};
				D2DrlgStrc original_pDrlg{};

				const auto setup_data = [dwFlags](
					D2DrlgStrc& pDrlg
				) {
					pDrlg.dwFlags = dwFlags;
				};

				setup_data(moo_pDrlg);
				setup_data(original_pDrlg);

				// Call both implementations
				const auto moo_result = sut(&moo_pDrlg);
				const auto original_result = original(&original_pDrlg);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			}
		}
	}
}

#endif
