#include <D2CommonTestDefines.h>

#ifdef DRLG_ACTIVATE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgActivate.h>
#include <Drlg/D2DrlgDrlg.h>


TEST_SUITE("D2DrlgActivateTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD733D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_RoomExSetStatus_ClientInRoom, dll_base + 0x000333D0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				// Empty status lists the room gets linked into
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.fRoomStatus = ROOMSTATUS_COUNT;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73450")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_RoomExSetStatus_ClientInSight, dll_base + 0x00033450);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				// Empty status lists the room gets linked into
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				// Room already exists, so no room needs to be created
				pDrlgRoom.dwFlags = DRLGROOMFLAG_HAS_ROOM;
				pDrlgRoom.fRoomStatus = ROOMSTATUS_COUNT;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73550")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_RoomExSetStatus_ClientOutOfSight, dll_base + 0x00033550);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				// Empty status lists the room gets linked into
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED | DRLGROOMFLAG_HAS_ROOM;
				pDrlgRoom.nType = DRLGTYPE_MAZE;
				pDrlgRoom.fRoomStatus = ROOMSTATUS_COUNT;
				// Room is also referenced as in sight, so status gets upgraded to ROOMSTATUS_CLIENT_IN_SIGHT
				pDrlgRoom.wRoomsInList[ROOMSTATUS_CLIENT_IN_SIGHT] = 1;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD736F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_RoomExSetStatus_Untile, dll_base + 0x000336F0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				// Empty status lists the room gets linked into
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				// Tiles are already loaded and room is no preset, so nothing needs to be loaded
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED;
				pDrlgRoom.nType = DRLGTYPE_MAZE;
				pDrlgRoom.fRoomStatus = ROOMSTATUS_COUNT;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73790")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_RoomExIdentifyRealStatus, dll_base + 0x00033790);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				// Empty status lists the room gets linked into
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;

				// Room is in the ROOMSTATUS_CLIENT_IN_ROOM list, but is only referenced as ROOMSTATUS_CLIENT_OUT_OF_SIGHT
				D2DrlgRoomStrc& tStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_ROOM];
				pDrlgRoom.fRoomStatus = ROOMSTATUS_CLIENT_IN_ROOM;
				pDrlgRoom.pStatusNext = &tStatusList;
				pDrlgRoom.pStatusPrev = &tStatusList;
				tStatusList.pStatusNext = &pDrlgRoom;
				tStatusList.pStatusPrev = &pDrlgRoom;
				pDrlgRoom.wRoomsInList[ROOMSTATUS_CLIENT_OUT_OF_SIGHT] = 1;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73880")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_RoomExStatusUnset_Untile, dll_base + 0x00033880);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				// Empty status lists, the drlg is not on the client so the room won't be freed
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;

				// Room is in the ROOMSTATUS_UNTILE list, but isn't referenced anymore
				D2DrlgRoomStrc& tStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_UNTILE];
				pDrlgRoom.fRoomStatus = ROOMSTATUS_UNTILE;
				pDrlgRoom.pStatusNext = &tStatusList;
				pDrlgRoom.pStatusPrev = &tStatusList;
				tStatusList.pStatusNext = &pDrlgRoom;
				tStatusList.pStatusPrev = &pDrlgRoom;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD739A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_SetClientIsInSight, dll_base + 0x000339A0);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc moo_pDrlgRoomHint{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoomHint{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			int nLevelId = LEVEL_ROGUEENCAMPMENT;
			int nX = 10;
			int nY = 20;

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc& pDrlgRoomHint,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc*(& ppRoomsNear)[1]
			) {
				// Empty status lists the room gets linked into
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pDrlg.pLevel = &pLevel;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;

				// Hint room contains the coordinates
				pDrlgRoomHint.pLevel = &pLevel;
				pDrlgRoomHint.nTileXPos = 8;
				pDrlgRoomHint.nTileYPos = 16;
				pDrlgRoomHint.nTileWidth = 8;
				pDrlgRoomHint.nTileHeight = 8;
				pDrlgRoomHint.dwFlags = DRLGROOMFLAG_TILELIB_LOADED | DRLGROOMFLAG_HAS_ROOM;
				pDrlgRoomHint.nType = DRLGTYPE_MAZE;
				pDrlgRoomHint.fRoomStatus = ROOMSTATUS_COUNT;

				// The status gets propagated to the rooms near, which includes the room itself
				ppRoomsNear[0] = &pDrlgRoomHint;
				pDrlgRoomHint.ppRoomsNear = ppRoomsNear;
				pDrlgRoomHint.nRoomsNear = 1;
			};

			setup_data(moo_pDrlg, moo_pDrlgRoomHint, moo_pLevel, moo_ppRoomsNear);
			setup_data(original_pDrlg, original_pDrlgRoomHint, original_pLevel, original_ppRoomsNear);

			// Call both implementations
			sut(&moo_pDrlg, nLevelId, nX, nY, &moo_pDrlgRoomHint);
			original(&original_pDrlg, nLevelId, nX, nY, &original_pDrlgRoomHint);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			MOO_CHECK_EQ(moo_pDrlgRoomHint, original_pDrlgRoomHint, "Comparing pDrlgRoomHint");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73A30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_RoomExPropagateSetStatus, dll_base + 0x00033A30);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			uint8_t nStatus = ROOMSTATUS_CLIENT_OUT_OF_SIGHT;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc*(& ppRoomsNear)[1]
			) {
				// Empty status lists the room gets linked into
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED;
				pDrlgRoom.nType = DRLGTYPE_MAZE;
				pDrlgRoom.fRoomStatus = ROOMSTATUS_COUNT;

				// The status gets propagated to the rooms near, which includes the room itself
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 1;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_ppRoomsNear);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_ppRoomsNear);

			// Call both implementations
			sut(nullptr, &moo_pDrlgRoom, nStatus);
			original(nullptr, &original_pDrlgRoom, nStatus);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73B40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_UnsetClientIsInSight, dll_base + 0x00033B40);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc moo_pDrlgRoomHint{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoomHint{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			int nLevelId = LEVEL_ROGUEENCAMPMENT;
			int nX = 10;
			int nY = 20;

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc& pDrlgRoomHint,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc*(& ppRoomsNear)[1]
			) {
				// Empty status lists, the drlg is not on the client so the room won't be freed
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pDrlg.pLevel = &pLevel;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;

				// Hint room contains the coordinates
				pDrlgRoomHint.pLevel = &pLevel;
				pDrlgRoomHint.nTileXPos = 8;
				pDrlgRoomHint.nTileYPos = 16;
				pDrlgRoomHint.nTileWidth = 8;
				pDrlgRoomHint.nTileHeight = 8;

				// The status gets propagated to the rooms near, which includes the room itself
				ppRoomsNear[0] = &pDrlgRoomHint;
				pDrlgRoomHint.ppRoomsNear = ppRoomsNear;
				pDrlgRoomHint.nRoomsNear = 1;

				// State of the room after the client got in sight of it
				D2DrlgRoomStrc& tStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_SIGHT];
				pDrlgRoomHint.fRoomStatus = ROOMSTATUS_CLIENT_IN_SIGHT;
				pDrlgRoomHint.pStatusNext = &tStatusList;
				pDrlgRoomHint.pStatusPrev = &tStatusList;
				tStatusList.pStatusNext = &pDrlgRoomHint;
				tStatusList.pStatusPrev = &pDrlgRoomHint;
				pDrlgRoomHint.wRoomsInList[ROOMSTATUS_CLIENT_IN_SIGHT] = 1;
				pDrlgRoomHint.wRoomsInList[ROOMSTATUS_CLIENT_OUT_OF_SIGHT] = 1;
				pDrlgRoomHint.wRoomsInList[ROOMSTATUS_UNTILE] = 1;
			};

			setup_data(moo_pDrlg, moo_pDrlgRoomHint, moo_pLevel, moo_ppRoomsNear);
			setup_data(original_pDrlg, original_pDrlgRoomHint, original_pLevel, original_ppRoomsNear);

			// Call both implementations
			sut(&moo_pDrlg, nLevelId, nX, nY, &moo_pDrlgRoomHint);
			original(&original_pDrlg, nLevelId, nX, nY, &original_pDrlgRoomHint);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			MOO_CHECK_EQ(moo_pDrlgRoomHint, original_pDrlgRoomHint, "Comparing pDrlgRoomHint");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73BE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_RoomExPropagateUnsetStatus, dll_base + 0x00033BE0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			uint8_t nStatus = ROOMSTATUS_CLIENT_OUT_OF_SIGHT;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc*(& ppRoomsNear)[1]
			) {
				// Empty status lists, the drlg is not on the client so the room won't be freed
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom.pLevel = &pLevel;

				// The status gets propagated to the rooms near, which includes the room itself
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 1;

				// State of the room after ROOMSTATUS_CLIENT_OUT_OF_SIGHT was propagated to it
				D2DrlgRoomStrc& tStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_OUT_OF_SIGHT];
				pDrlgRoom.fRoomStatus = ROOMSTATUS_CLIENT_OUT_OF_SIGHT;
				pDrlgRoom.pStatusNext = &tStatusList;
				pDrlgRoom.pStatusPrev = &tStatusList;
				tStatusList.pStatusNext = &pDrlgRoom;
				tStatusList.pStatusPrev = &pDrlgRoom;
				pDrlgRoom.wRoomsInList[ROOMSTATUS_CLIENT_OUT_OF_SIGHT] = 1;
				pDrlgRoom.wRoomsInList[ROOMSTATUS_UNTILE] = 1;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_ppRoomsNear);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_ppRoomsNear);

			// Call both implementations
			sut(&moo_pDrlgRoom, nStatus);
			original(&original_pDrlgRoom, nStatus);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73C40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_ChangeClientRoom, dll_base + 0x00033C40);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pPreviousRoom{};
			D2DrlgRoomStrc moo_pNewRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc* moo_ppPreviousRoomsNear[1]{};
			D2DrlgRoomStrc* moo_ppNewRoomsNear[1]{};
			D2DrlgRoomStrc original_pPreviousRoom{};
			D2DrlgRoomStrc original_pNewRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc* original_ppPreviousRoomsNear[1]{};
			D2DrlgRoomStrc* original_ppNewRoomsNear[1]{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pPreviousRoom,
				D2DrlgRoomStrc& pNewRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc*(& ppPreviousRoomsNear)[1],
				D2DrlgRoomStrc*(& ppNewRoomsNear)[1]
			) {
				// Empty status lists, the drlg is not on the client so the rooms won't be freed
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pLevel.pDrlg = &pDrlg;

				// The client is currently in the previous room
				pPreviousRoom.pLevel = &pLevel;
				ppPreviousRoomsNear[0] = &pPreviousRoom;
				pPreviousRoom.ppRoomsNear = ppPreviousRoomsNear;
				pPreviousRoom.nRoomsNear = 1;

				D2DrlgRoomStrc& tStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_ROOM];
				pPreviousRoom.fRoomStatus = ROOMSTATUS_CLIENT_IN_ROOM;
				pPreviousRoom.pStatusNext = &tStatusList;
				pPreviousRoom.pStatusPrev = &tStatusList;
				tStatusList.pStatusNext = &pPreviousRoom;
				tStatusList.pStatusPrev = &pPreviousRoom;
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pPreviousRoom.wRoomsInList[i] = 1;
				}

				// The new room is loaded, but has no status yet
				pNewRoom.pLevel = &pLevel;
				ppNewRoomsNear[0] = &pNewRoom;
				pNewRoom.ppRoomsNear = ppNewRoomsNear;
				pNewRoom.nRoomsNear = 1;
				pNewRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED | DRLGROOMFLAG_HAS_ROOM;
				pNewRoom.nType = DRLGTYPE_MAZE;
				pNewRoom.fRoomStatus = ROOMSTATUS_COUNT;
			};

			setup_data(moo_pPreviousRoom, moo_pNewRoom, moo_pLevel, moo_pDrlg, moo_ppPreviousRoomsNear, moo_ppNewRoomsNear);
			setup_data(original_pPreviousRoom, original_pNewRoom, original_pLevel, original_pDrlg, original_ppPreviousRoomsNear, original_ppNewRoomsNear);

			// Call both implementations
			sut(&moo_pPreviousRoom, &moo_pNewRoom);
			original(&original_pPreviousRoom, &original_pNewRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPreviousRoom, original_pPreviousRoom, "Comparing pPreviousRoom");
			MOO_CHECK_EQ(moo_pNewRoom, original_pNewRoom, "Comparing pNewRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73CF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_InitializeRoomEx, dll_base + 0x00033CF0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				// Tiles are loaded, preset units are added and the room exists already, so nothing needs to be loaded
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED | DRLGROOMFLAG_PRESET_UNITS_ADDED | DRLGROOMFLAG_HAS_ROOM;
				pDrlgRoom.nType = DRLGTYPE_PRESET;
			};

			setup_data(moo_pDrlgRoom);
			setup_data(original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73D80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_StreamRoomAtCoords, dll_base + 0x00033D80);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			int nX = 10;
			int nY = 20;

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2ActiveRoomStrc& pRoom
			) {
				// Level and its first room contain the coordinates
				pDrlg.pLevel = &pLevel;

				pLevel.pDrlg = &pDrlg;
				pLevel.nPosX = 0;
				pLevel.nPosY = 0;
				pLevel.nWidth = 32;
				pLevel.nHeight = 32;
				pLevel.pFirstRoomEx = &pDrlgRoom;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = 8;
				pDrlgRoom.nTileYPos = 16;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				// Tiles are loaded and the room exists already, so nothing needs to be loaded
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED | DRLGROOMFLAG_HAS_ROOM;
				pDrlgRoom.nType = DRLGTYPE_MAZE;
				pDrlgRoom.pRoom = &pRoom;

				pRoom.tCoords.nTileXPos = 8;
				pRoom.tCoords.nTileYPos = 16;
				pRoom.tCoords.nTileWidth = 8;
				pRoom.tCoords.nTileHeight = 8;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pDrlgRoom, moo_pRoom);
			setup_data(original_pDrlg, original_pLevel, original_pDrlgRoom, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nX, nY);
			const auto original_result = original(&original_pDrlg, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73E30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_InitializeRoomExStatusLists, dll_base + 0x00033E30);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg
			) {
				// Status lists are initialized by the function, a zero-initialized drlg is all that is needed
				(void)pDrlg;
			};

			setup_data(moo_pDrlg);
			setup_data(original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlg);
			original(&original_pDrlg);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73E60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_GetARoomInClientSight, dll_base + 0x00033E60);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc& pDrlgRoom,
				D2ActiveRoomStrc& pRoom
			) {
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}

				// No room with the client in it, but one room in sight of the client
				D2DrlgRoomStrc& tStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_SIGHT];
				pDrlgRoom.fRoomStatus = ROOMSTATUS_CLIENT_IN_SIGHT;
				pDrlgRoom.pStatusNext = &tStatusList;
				pDrlgRoom.pStatusPrev = &tStatusList;
				tStatusList.pStatusNext = &pDrlgRoom;
				tStatusList.pStatusPrev = &pDrlgRoom;
				pDrlgRoom.pRoom = &pRoom;

				pRoom.tCoords.nTileXPos = 8;
				pRoom.tCoords.nTileYPos = 16;
				pRoom.tCoords.nTileWidth = 8;
				pRoom.tCoords.nTileHeight = 8;
			};

			setup_data(moo_pDrlg, moo_pDrlgRoom, moo_pRoom);
			setup_data(original_pDrlg, original_pDrlgRoom, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg);
			const auto original_result = original(&original_pDrlg);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73E90")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_GetARoomInSightButWithoutClient, dll_base + 0x00033E90);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc moo_pInSightRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc original_pInSightRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc& pInSightRoom,
				D2ActiveRoomStrc& pRoom
			) {
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}

				// The room is the last (and only) room with the client in it
				D2DrlgRoomStrc& tInRoomStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_ROOM];
				pDrlgRoom.fRoomStatus = ROOMSTATUS_CLIENT_IN_ROOM;
				pDrlgRoom.pStatusNext = &tInRoomStatusList;
				pDrlgRoom.pStatusPrev = &tInRoomStatusList;
				tInRoomStatusList.pStatusNext = &pDrlgRoom;
				tInRoomStatusList.pStatusPrev = &pDrlgRoom;

				// So the first room in sight is expected to be returned
				D2DrlgRoomStrc& tInSightStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_IN_SIGHT];
				pInSightRoom.fRoomStatus = ROOMSTATUS_CLIENT_IN_SIGHT;
				pInSightRoom.pStatusNext = &tInSightStatusList;
				pInSightRoom.pStatusPrev = &tInSightStatusList;
				tInSightStatusList.pStatusNext = &pInSightRoom;
				tInSightStatusList.pStatusPrev = &pInSightRoom;
				pInSightRoom.pRoom = &pRoom;

				pRoom.tCoords.nTileXPos = 8;
				pRoom.tCoords.nTileYPos = 16;
				pRoom.tCoords.nTileWidth = 8;
				pRoom.tCoords.nTileHeight = 8;
			};

			setup_data(moo_pDrlg, moo_pDrlgRoom, moo_pInSightRoom, moo_pRoom);
			setup_data(original_pDrlg, original_pDrlgRoom, original_pInSightRoom, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, &moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlg, &original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73EF0 (#10015)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_GetRoomsAllocationStats, dll_base + 0x00033EF0);

		SUBCASE("")
		{
			// Input data
			int moo_pOutStatsClientAllocatedRooms{};
			int moo_pOutStatsClientFreedRooms{};
			int moo_pOutStatsAllocatedRooms{};
			int moo_pOutStatsFreedRooms{};
			int original_pOutStatsClientAllocatedRooms{};
			int original_pOutStatsClientFreedRooms{};
			int original_pOutStatsAllocatedRooms{};
			int original_pOutStatsFreedRooms{};

			const auto setup_data = [](
				int& pOutStatsClientAllocatedRooms,
				int& pOutStatsClientFreedRooms,
				int& pOutStatsAllocatedRooms,
				int& pOutStatsFreedRooms
			) {
				// Values are expected to be overwritten
				pOutStatsClientAllocatedRooms = -1;
				pOutStatsClientFreedRooms = -1;
				pOutStatsAllocatedRooms = -1;
				pOutStatsFreedRooms = -1;
			};

			setup_data(moo_pOutStatsClientAllocatedRooms, moo_pOutStatsClientFreedRooms, moo_pOutStatsAllocatedRooms, moo_pOutStatsFreedRooms);
			setup_data(original_pOutStatsClientAllocatedRooms, original_pOutStatsClientFreedRooms, original_pOutStatsAllocatedRooms, original_pOutStatsFreedRooms);

			// Call both implementations
			sut(&moo_pOutStatsClientAllocatedRooms, &moo_pOutStatsClientFreedRooms, &moo_pOutStatsAllocatedRooms, &moo_pOutStatsFreedRooms);
			original(&original_pOutStatsClientAllocatedRooms, &original_pOutStatsClientFreedRooms, &original_pOutStatsAllocatedRooms, &original_pOutStatsFreedRooms);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pOutStatsClientAllocatedRooms, original_pOutStatsClientAllocatedRooms, "Comparing pOutStatsClientAllocatedRooms");
			MOO_CHECK_EQ(moo_pOutStatsClientFreedRooms, original_pOutStatsClientFreedRooms, "Comparing pOutStatsClientFreedRooms");
			MOO_CHECK_EQ(moo_pOutStatsAllocatedRooms, original_pOutStatsAllocatedRooms, "Comparing pOutStatsAllocatedRooms");
			MOO_CHECK_EQ(moo_pOutStatsFreedRooms, original_pOutStatsFreedRooms, "Comparing pOutStatsFreedRooms");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD73F20 (#10003)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_Update, dll_base + 0x00033F20);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgRoomStrc& pDrlgRoom
			) {
				for (int i = 0; i < ROOMSTATUS_COUNT; ++i)
				{
					pDrlg.tStatusRoomsLists[i].fRoomStatus = i;
					pDrlg.tStatusRoomsLists[i].pStatusNext = &pDrlg.tStatusRoomsLists[i];
					pDrlg.tStatusRoomsLists[i].pStatusPrev = &pDrlg.tStatusRoomsLists[i];
				}
				pDrlg.nAllocatedRooms = 3;
				pDrlg.nFreedRooms = 1;
				// Timeout expires during this update, so the rooms out of sight get iterated
				pDrlg.nRoomsInitTimeout = 1;

				// One room out of sight, which exists already so it doesn't need to be created
				D2DrlgRoomStrc& tStatusList = pDrlg.tStatusRoomsLists[ROOMSTATUS_CLIENT_OUT_OF_SIGHT];
				pDrlgRoom.dwFlags = DRLGROOMFLAG_HAS_ROOM;
				pDrlgRoom.fRoomStatus = ROOMSTATUS_CLIENT_OUT_OF_SIGHT;
				pDrlgRoom.pStatusNext = &tStatusList;
				pDrlgRoom.pStatusPrev = &tStatusList;
				tStatusList.pStatusNext = &pDrlgRoom;
				tStatusList.pStatusPrev = &pDrlgRoom;
			};

			setup_data(moo_pDrlg, moo_pDrlgRoom);
			setup_data(original_pDrlg, original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pDrlg);
			original(&original_pDrlg);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74060")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_TestRoomCanUnTile, dll_base + 0x00034060);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				// Drlg must not be on the client
				pLevel.pDrlg = &pDrlg;
				// Town levels check all of their rooms
				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
				pLevel.pFirstRoomEx = &pDrlgRoom;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.fRoomStatus = ROOMSTATUS_CLIENT_OUT_OF_SIGHT;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD740F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_ToggleHasPortalFlag, dll_base + 0x000340F0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			BOOL bReset = FALSE;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				// Other flags are expected to be kept
				pDrlgRoom.dwFlags = DRLGROOMFLAG_TILELIB_LOADED | DRLGROOMFLAG_HAS_ROOM;
			};

			setup_data(moo_pDrlgRoom);
			setup_data(original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom, bReset);
			original(&original_pDrlgRoom, bReset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74110")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGACTIVATE_GetRoomStatusFlags, dll_base + 0x00034110);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pDrlgRoom.fRoomStatus = ROOMSTATUS_CLIENT_OUT_OF_SIGHT;
			};

			setup_data(moo_pDrlgRoom);
			setup_data(original_pDrlgRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
}

#endif
