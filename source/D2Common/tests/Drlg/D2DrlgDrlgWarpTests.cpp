#include <D2CommonTestDefines.h>

#ifdef DRLG_WARP_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/LevelsTbls.h>
#include <DataTbls/ObjectsTbls.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgWarp.h>
#include <Drlg/D2DrlgPreset.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("D2DrlgDrlgWarpTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78780")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetDestinationRoom, dll_base + 0x00038780);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2RoomTileStrc moo_pSourceRoomTile{};
			D2LvlWarpTxt moo_pSourceLvlWarpTxtRecord{};
			D2DrlgRoomStrc moo_pDestinationDrlgRoom{};
			D2RoomTileStrc moo_pDestinationRoomTile{};
			D2LvlWarpTxt moo_pDestinationLvlWarpTxtRecord{};
			D2ActiveRoomStrc moo_pDestinationRoom{};
			int moo_pDestinationLevel{};
			D2LvlWarpTxt* moo_ppLvlWarpTxtRecord{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2RoomTileStrc original_pSourceRoomTile{};
			D2LvlWarpTxt original_pSourceLvlWarpTxtRecord{};
			D2DrlgRoomStrc original_pDestinationDrlgRoom{};
			D2RoomTileStrc original_pDestinationRoomTile{};
			D2LvlWarpTxt original_pDestinationLvlWarpTxtRecord{};
			D2ActiveRoomStrc original_pDestinationRoom{};
			int original_pDestinationLevel{};
			D2LvlWarpTxt* original_ppLvlWarpTxtRecord{};
			int nSourceLevel = 1;
			const int nDestinationLevel = 2;

			const auto setup_data = [nSourceLevel, nDestinationLevel](
				D2DrlgRoomStrc& pDrlgRoom,
				D2RoomTileStrc& pSourceRoomTile,
				D2LvlWarpTxt& pSourceLvlWarpTxtRecord,
				D2DrlgRoomStrc& pDestinationDrlgRoom,
				D2RoomTileStrc& pDestinationRoomTile,
				D2LvlWarpTxt& pDestinationLvlWarpTxtRecord,
				D2ActiveRoomStrc& pDestinationRoom
			) {
				// The source room has a warp tile leading to the destination room
				pSourceLvlWarpTxtRecord.dwLevelId = nSourceLevel;
				pSourceRoomTile.pDrlgRoom = &pDestinationDrlgRoom;
				pSourceRoomTile.pLvlWarpTxtRecord = &pSourceLvlWarpTxtRecord;
				pDrlgRoom.pRoomTiles = &pSourceRoomTile;

				// The destination room has a warp tile leading back to the source room
				pDestinationLvlWarpTxtRecord.dwLevelId = nDestinationLevel;
				pDestinationRoomTile.pDrlgRoom = &pDrlgRoom;
				pDestinationRoomTile.pLvlWarpTxtRecord = &pDestinationLvlWarpTxtRecord;
				pDestinationDrlgRoom.pRoomTiles = &pDestinationRoomTile;

				// Destination room is already initialized, so no room activation is needed
				pDestinationDrlgRoom.pRoom = &pDestinationRoom;
			};

			setup_data(moo_pDrlgRoom, moo_pSourceRoomTile, moo_pSourceLvlWarpTxtRecord, moo_pDestinationDrlgRoom, moo_pDestinationRoomTile, moo_pDestinationLvlWarpTxtRecord, moo_pDestinationRoom);
			setup_data(original_pDrlgRoom, original_pSourceRoomTile, original_pSourceLvlWarpTxtRecord, original_pDestinationDrlgRoom, original_pDestinationRoomTile, original_pDestinationLvlWarpTxtRecord, original_pDestinationRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nSourceLevel, &moo_pDestinationLevel, &moo_ppLvlWarpTxtRecord);
			const auto original_result = original(&original_pDrlgRoom, nSourceLevel, &original_pDestinationLevel, &original_ppLvlWarpTxtRecord);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDestinationLevel, original_pDestinationLevel, "Comparing pDestinationLevel");
			MOO_CHECK_EQ(moo_ppLvlWarpTxtRecord, original_ppLvlWarpTxtRecord, "Comparing ppLvlWarpTxtRecord");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD787F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_ToggleRoomTilesEnableFlag, dll_base + 0x000387F0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2RoomTileStrc moo_pRoomTile1{};
			D2RoomTileStrc moo_pRoomTile2{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2RoomTileStrc original_pRoomTile1{};
			D2RoomTileStrc original_pRoomTile2{};
			BOOL bEnabled = GENERATE(FALSE, TRUE);

			const auto setup_data = [bEnabled](
				D2DrlgRoomStrc& pDrlgRoom,
				D2RoomTileStrc& pRoomTile1,
				D2RoomTileStrc& pRoomTile2
			) {
				pRoomTile1.bEnabled = !bEnabled;
				pRoomTile1.pNext = &pRoomTile2;
				pRoomTile2.bEnabled = !bEnabled;
				pDrlgRoom.pRoomTiles = &pRoomTile1;
			};

			setup_data(moo_pDrlgRoom, moo_pRoomTile1, moo_pRoomTile2);
			setup_data(original_pDrlgRoom, original_pRoomTile1, original_pRoomTile2);

			// Call both implementations
			sut(&moo_pDrlgRoom, bEnabled);
			original(&original_pDrlgRoom, bEnabled);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pRoomTile1.bEnabled, original_pRoomTile1.bEnabled, "Comparing pRoomTile1.bEnabled");
			MOO_CHECK_EQ(moo_pRoomTile2.bEnabled, original_pRoomTile2.bEnabled, "Comparing pRoomTile2.bEnabled");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78810")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_UpdateWarpRoomSelect, dll_base + 0x00038810);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2RoomTileStrc moo_pRoomTile{};
			D2LvlWarpTxt moo_pLvlWarpTxtRecord{};
			D2DrlgTileDataStrc moo_pDeselectedTileData{};
			D2DrlgTileDataStrc moo_pSelectedTileData{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2RoomTileStrc original_pRoomTile{};
			D2LvlWarpTxt original_pLvlWarpTxtRecord{};
			D2DrlgTileDataStrc original_pDeselectedTileData{};
			D2DrlgTileDataStrc original_pSelectedTileData{};
			int nLevelId = 1;

			const auto setup_data = [nLevelId](
				D2DrlgRoomStrc& pDrlgRoom,
				D2RoomTileStrc& pRoomTile,
				D2LvlWarpTxt& pLvlWarpTxtRecord,
				D2DrlgTileDataStrc& pDeselectedTileData,
				D2DrlgTileDataStrc& pSelectedTileData
			) {
				pLvlWarpTxtRecord.dwLevelId = nLevelId;
				pDeselectedTileData.dwFlags = 0x09;
				pSelectedTileData.dwFlags = 0x01;
				pRoomTile.pLvlWarpTxtRecord = &pLvlWarpTxtRecord;
				pRoomTile.unk0x0C = &pDeselectedTileData;
				pRoomTile.unk0x10 = &pSelectedTileData;
				pDrlgRoom.pRoomTiles = &pRoomTile;
			};

			setup_data(moo_pDrlgRoom, moo_pRoomTile, moo_pLvlWarpTxtRecord, moo_pDeselectedTileData, moo_pSelectedTileData);
			setup_data(original_pDrlgRoom, original_pRoomTile, original_pLvlWarpTxtRecord, original_pDeselectedTileData, original_pSelectedTileData);

			// Call both implementations
			sut(&moo_pDrlgRoom, nLevelId);
			original(&original_pDrlgRoom, nLevelId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDeselectedTileData, original_pDeselectedTileData, "Comparing pDeselectedTileData");
			MOO_CHECK_EQ(moo_pSelectedTileData, original_pSelectedTileData, "Comparing pSelectedTileData");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78870")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_UpdateWarpRoomDeselect, dll_base + 0x00038870);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2RoomTileStrc moo_pRoomTile{};
			D2LvlWarpTxt moo_pLvlWarpTxtRecord{};
			D2DrlgTileDataStrc moo_pDeselectedTileData{};
			D2DrlgTileDataStrc moo_pSelectedTileData{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2RoomTileStrc original_pRoomTile{};
			D2LvlWarpTxt original_pLvlWarpTxtRecord{};
			D2DrlgTileDataStrc original_pDeselectedTileData{};
			D2DrlgTileDataStrc original_pSelectedTileData{};
			int nLevelId = 1;

			const auto setup_data = [nLevelId](
				D2DrlgRoomStrc& pDrlgRoom,
				D2RoomTileStrc& pRoomTile,
				D2LvlWarpTxt& pLvlWarpTxtRecord,
				D2DrlgTileDataStrc& pDeselectedTileData,
				D2DrlgTileDataStrc& pSelectedTileData
			) {
				pLvlWarpTxtRecord.dwLevelId = nLevelId;
				pDeselectedTileData.dwFlags = 0x01;
				pSelectedTileData.dwFlags = 0x09;
				pRoomTile.pLvlWarpTxtRecord = &pLvlWarpTxtRecord;
				pRoomTile.unk0x0C = &pDeselectedTileData;
				pRoomTile.unk0x10 = &pSelectedTileData;
				pDrlgRoom.pRoomTiles = &pRoomTile;
			};

			setup_data(moo_pDrlgRoom, moo_pRoomTile, moo_pLvlWarpTxtRecord, moo_pDeselectedTileData, moo_pSelectedTileData);
			setup_data(original_pDrlgRoom, original_pRoomTile, original_pLvlWarpTxtRecord, original_pDeselectedTileData, original_pSelectedTileData);

			// Call both implementations
			sut(&moo_pDrlgRoom, nLevelId);
			original(&original_pDrlgRoom, nLevelId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDeselectedTileData, original_pDeselectedTileData, "Comparing pDeselectedTileData");
			MOO_CHECK_EQ(moo_pSelectedTileData, original_pSelectedTileData, "Comparing pSelectedTileData");
		}
	}

	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD788D0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD788D0, dll_base + 0x000388D0);

		SUBCASE("")
		{
			// Find a level without a fixed position, so the room is looked up via the level's center
			int nLevelId = -1;
			for (int i = 1; i < leveldefs_record_count && i < levels_record_count; ++i)
			{
				if (!leveldefs_txt[i].dwPosition)
				{
					nLevelId = i;
					break;
				}
			}
			REQUIRE(nLevelId != -1);

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			int moo_pX{};
			int moo_pY{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			int original_pX{};
			int original_pY{};
			int nTileIndex{};

			const auto setup_data = [nLevelId](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2ActiveRoomStrc& pRoom
			) {
				pDrlg.pLevel = &pLevel;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = nLevelId;
				pLevel.nPosX = 0;
				pLevel.nPosY = 0;
				pLevel.nWidth = 16;
				pLevel.nHeight = 16;
				pLevel.pFirstRoomEx = &pDrlgRoom;
				pLevel.nRooms = 1;

				// Room covers the level's center and is already initialized
				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = 0;
				pDrlgRoom.nTileYPos = 0;
				pDrlgRoom.nTileWidth = 16;
				pDrlgRoom.nTileHeight = 16;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED;
				pDrlgRoom.pRoom = &pRoom;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pDrlgRoom, moo_pRoom);
			setup_data(original_pDrlg, original_pLevel, original_pDrlgRoom, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId, nTileIndex, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pDrlg, nLevelId, nTileIndex, &original_pX, &original_pY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}

	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FD78C10" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetWaypointRoomExFromLevel, dll_base + 0x00038C10);

		SUBCASE("")
		{
			// Find a waypoint object
			int nWaypointObjectId = -1;
			for (int i = 0; i < objects_record_count && i < 573; ++i)
			{
				if (objects_txt[i].nSubClass & OBJSUBCLASS_WAYPOINT)
				{
					nWaypointObjectId = i;
					break;
				}
			}
			REQUIRE(nWaypointObjectId != -1);

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			D2PresetUnitStrc moo_pPresetUnit{};
			int moo_pX{};
			int moo_pY{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			D2PresetUnitStrc original_pPresetUnit{};
			int original_pX{};
			int original_pY{};

			const auto setup_data = [nWaypointObjectId](
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2ActiveRoomStrc& pRoom,
				D2PresetUnitStrc& pPresetUnit
			) {
				pLevel.pFirstRoomEx = &pDrlgRoom;

				// Waypoint room which is already initialized
				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = 3;
				pDrlgRoom.nTileYPos = 4;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_HAS_WAYPOINT | DRLGROOMFLAG_TILELIB_LOADED;
				pDrlgRoom.pRoom = &pRoom;
				pDrlgRoom.pPresetUnits = &pPresetUnit;

				pPresetUnit.nUnitType = UNIT_OBJECT;
				pPresetUnit.nIndex = nWaypointObjectId;
				pPresetUnit.nXpos = 10;
				pPresetUnit.nYpos = 15;
			};

			setup_data(moo_pLevel, moo_pDrlgRoom, moo_pRoom, moo_pPresetUnit);
			setup_data(original_pLevel, original_pDrlgRoom, original_pRoom, original_pPresetUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pLevel, &original_pX, &original_pY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78CC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetWarpIdArrayFromLevelId, dll_base + 0x00038CC0);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			int nLevelId = 1;

			const auto setup_data = [nLevelId](
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp
			) {
				pWarp.nLevel = nLevelId;
				for (int i = 0; i < 8; ++i)
				{
					pWarp.nWarp[i] = i + 1;
				}
				pDrlg.pWarp = &pWarp;
			};

			setup_data(moo_pDrlg, moo_pWarp);
			setup_data(original_pDrlg, original_pWarp);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);

			// Compare return values
			for (int i = 0; i < 8; ++i)
			{
				MOO_CHECK_EQ(moo_result[i], original_result[i], "Comparing results");
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78D10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetWarpDestinationFromArray, dll_base + 0x00038D10);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			uint8_t nArrayId = random_unsigned_integer(0, 7);
			const int nLevelId = 1;

			const auto setup_data = [nLevelId](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp
			) {
				pWarp.nLevel = nLevelId;
				for (int i = 0; i < 8; ++i)
				{
					pWarp.nWarp[i] = i + 1;
				}
				pDrlg.pWarp = &pWarp;
				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = nLevelId;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pWarp);
			setup_data(original_pLevel, original_pDrlg, original_pWarp);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nArrayId);
			const auto original_result = original(&original_pLevel, nArrayId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(LvlWarpTxtFixture<NoopFixture>, "D2Common.0x6FD78D80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetLvlWarpTxtRecordFromWarpIdAndDirection, dll_base + 0x00038D80);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarp{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarp{};
			uint8_t nWarpId = random_unsigned_integer(0, 7);
			char szDirection = GENERATE('b', 'l', 'r');
			const int nLevelId = 1;

			const auto setup_data = [nLevelId](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pWarp
			) {
				// Warp destinations are levels which have LvlWarp.txt records
				pWarp.nLevel = nLevelId;
				for (int i = 0; i < 8; ++i)
				{
					pWarp.nWarp[i] = i + 1;
				}
				pDrlg.pWarp = &pWarp;
				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = nLevelId;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pWarp);
			setup_data(original_pLevel, original_pDrlg, original_pWarp);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nWarpId, szDirection);
			const auto original_result = original(&original_pLevel, nWarpId, szDirection);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78DF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGWARP_GetLvlWarpTxtRecordFromUnit, dll_base + 0x00038DF0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2RoomTileStrc moo_pRoomTile1{};
			D2RoomTileStrc moo_pRoomTile2{};
			D2LvlWarpTxt moo_pLvlWarpTxtRecord1{};
			D2LvlWarpTxt moo_pLvlWarpTxtRecord2{};
			D2UnitStrc moo_pUnit{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2RoomTileStrc original_pRoomTile1{};
			D2RoomTileStrc original_pRoomTile2{};
			D2LvlWarpTxt original_pLvlWarpTxtRecord1{};
			D2LvlWarpTxt original_pLvlWarpTxtRecord2{};
			D2UnitStrc original_pUnit{};
			const int nClassId = 2;

			const auto setup_data = [nClassId](
				D2DrlgRoomStrc& pDrlgRoom,
				D2RoomTileStrc& pRoomTile1,
				D2RoomTileStrc& pRoomTile2,
				D2LvlWarpTxt& pLvlWarpTxtRecord1,
				D2LvlWarpTxt& pLvlWarpTxtRecord2,
				D2UnitStrc& pUnit
			) {
				pUnit.dwClassId = nClassId;

				// First tile leads to a different level, second tile matches the unit's class id
				pLvlWarpTxtRecord1.dwLevelId = nClassId + 1;
				pLvlWarpTxtRecord1.dwSelectX = 1;
				pLvlWarpTxtRecord2.dwLevelId = nClassId;
				pLvlWarpTxtRecord2.dwSelectX = 2;

				pRoomTile1.pLvlWarpTxtRecord = &pLvlWarpTxtRecord1;
				pRoomTile1.bEnabled = TRUE;
				pRoomTile1.pNext = &pRoomTile2;
				pRoomTile2.pLvlWarpTxtRecord = &pLvlWarpTxtRecord2;
				pRoomTile2.bEnabled = TRUE;
				pDrlgRoom.pRoomTiles = &pRoomTile1;
			};

			setup_data(moo_pDrlgRoom, moo_pRoomTile1, moo_pRoomTile2, moo_pLvlWarpTxtRecord1, moo_pLvlWarpTxtRecord2, moo_pUnit);
			setup_data(original_pDrlgRoom, original_pRoomTile1, original_pRoomTile2, original_pLvlWarpTxtRecord1, original_pLvlWarpTxtRecord2, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, &moo_pUnit);
			const auto original_result = original(&original_pDrlgRoom, &original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			MOO_CHECK_EQ(moo_result->dwSelectX, original_result->dwSelectX, "Comparing returned record");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}

#endif
