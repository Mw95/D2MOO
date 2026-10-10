#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <string>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Fog.h>

#include <D2DataTbls.h>
#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgRoom.h>
#include <Drlg/D2DrlgOutRoom.h>
#include <Drlg/D2DrlgPreset.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("D2DrlgDrlgRoomTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD771C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_AllocRoomEx, dll_base + 0x000371C0);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			// Outdoor rooms don't allocate any additional room data
			int nType = DRLGTYPE_OUTDOOR;

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pLevel.pDrlg = &pDrlg;
				pLevel.dwFlags = DRLGLEVELFLAG_AUTOMAP_REVEAL;
				pLevel.pSeed.nLowSeed = 1234;
				pLevel.pSeed.nHighSeed = 666;
			};

			setup_data(moo_pLevel, moo_pDrlg);
			setup_data(original_pLevel, original_pDrlg);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nType);
			const auto original_result = original(&original_pLevel, nType);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");

			// Check specific values
			CHECK_EQ(moo_result->pLevel, &moo_pLevel);
			CHECK_EQ(moo_result->nType, nType);
			CHECK_NE(moo_result->dwFlags & DRLGROOMFLAG_AUTOMAP_REVEAL, 0u);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77280")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD77280, dll_base + 0x00037280);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};
			BOOL bClient = TRUE;
			uint32_t nFlags = 3;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2ActiveRoomStrc& pRoom
			) {
				// No DRLGROOMFLAG_HAS_ROOM, so the room doesn't get freed
				pDrlgRoom.pRoom = &pRoom;
			};

			setup_data(moo_pDrlgRoom, moo_pRoom);
			setup_data(original_pDrlgRoom, original_pRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom, bClient, nFlags);
			original(&original_pDrlgRoom, bClient, nFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pRoom, nullptr);
			CHECK_EQ(moo_pDrlgRoom.dwOtherFlags, 1u);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD772B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_FreeRoomTiles, dll_base + 0x000372B0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				// The room tiles get freed by the function, so they have to be allocated from the memory pool
				D2RoomTileStrc* pRoomTile1 = D2_CALLOC_STRC_POOL(nullptr, D2RoomTileStrc);
				D2RoomTileStrc* pRoomTile2 = D2_CALLOC_STRC_POOL(nullptr, D2RoomTileStrc);
				pRoomTile1->pNext = pRoomTile2;
				pDrlgRoom.pRoomTiles = pRoomTile1;
			};

			setup_data(moo_pDrlgRoom);
			setup_data(original_pDrlgRoom);

			// Call both implementations
			sut(nullptr, &moo_pDrlgRoom);
			original(nullptr, &original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pRoomTiles, nullptr);
			CHECK_EQ(original_pDrlgRoom.pRoomTiles, nullptr);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD772F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_FreeRoomEx, dll_base + 0x000372F0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc* moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc* original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc*& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				// The room gets freed by the function, so it has to be allocated from the memory pool
				pDrlgRoom = D2_CALLOC_STRC_POOL(nullptr, D2DrlgRoomStrc);
				pDrlgRoom->pLevel = &pLevel;

				pLevel.pDrlg = &pDrlg;
				pLevel.pFirstRoomEx = pDrlgRoom;
				pLevel.nRooms = 1;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(moo_pDrlgRoom);
			original(original_pDrlgRoom);

			// Compare potentially modified input data
			// NOTE: pDrlgRoom can not be compared since it was freed
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");

			// Check specific values
			CHECK_EQ(moo_pLevel.pFirstRoomEx, nullptr);
			CHECK_EQ(moo_pLevel.nRooms, 0);
			CHECK_EQ(original_pLevel.pFirstRoomEx, nullptr);
			CHECK_EQ(original_pLevel.nRooms, 0);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD774F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_FreeRoomData, dll_base + 0x000374F0);

		SUBCASE("")
		{
			// Input data
			D2DrlgOrthStrc* moo_pDrlgRoomData{};
			D2DrlgOrthStrc* original_pDrlgRoomData{};

			const auto setup_data = [](
				D2DrlgOrthStrc*& pDrlgRoomData
			) {
				// The orths get freed by the function, so they have to be allocated from the memory pool
				pDrlgRoomData = D2_CALLOC_STRC_POOL(nullptr, D2DrlgOrthStrc);
				pDrlgRoomData->pNext = D2_CALLOC_STRC_POOL(nullptr, D2DrlgOrthStrc);
			};

			setup_data(moo_pDrlgRoomData);
			setup_data(original_pDrlgRoomData);

			// Call both implementations
			sut(nullptr, moo_pDrlgRoomData);
			original(nullptr, original_pDrlgRoomData);

			// Input data can not be compared since it was freed
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77520")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_AllocDrlgOrthsForRooms, dll_base + 0x00037520);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom1{};
			D2DrlgRoomStrc moo_pDrlgRoom2{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pDrlgRoom1{};
			D2DrlgRoomStrc original_pDrlgRoom2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			int nDirection = DIRECTION_SOUTHEAST;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom1,
				D2DrlgRoomStrc& pDrlgRoom2,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pLevel.pDrlg = &pDrlg;

				pDrlgRoom1.pLevel = &pLevel;
				pDrlgRoom1.pDrlgCoord = { 0, 0, 8, 8 };

				pDrlgRoom2.pLevel = &pLevel;
				pDrlgRoom2.pDrlgCoord = { 8, 0, 8, 8 };
			};

			setup_data(moo_pDrlgRoom1, moo_pDrlgRoom2, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom1, original_pDrlgRoom2, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom1, &moo_pDrlgRoom2, nDirection);
			original(&original_pDrlgRoom1, &original_pDrlgRoom2, nDirection);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");

			// Check specific values
			REQUIRE_NE(moo_pDrlgRoom1.pDrlgOrth, nullptr);
			REQUIRE_NE(original_pDrlgRoom1.pDrlgOrth, nullptr);
			CHECK_EQ(moo_pDrlgRoom1.pDrlgOrth->pDrlgRoom, &moo_pDrlgRoom2);
			CHECK_EQ(moo_pDrlgRoom1.pDrlgOrth->nDirection, original_pDrlgRoom1.pDrlgOrth->nDirection);
			CHECK_EQ(moo_pDrlgRoom1.pDrlgOrth->bInit, original_pDrlgRoom1.pDrlgOrth->bInit);

			REQUIRE_NE(moo_pDrlgRoom2.pDrlgOrth, nullptr);
			REQUIRE_NE(original_pDrlgRoom2.pDrlgOrth, nullptr);
			CHECK_EQ(moo_pDrlgRoom2.pDrlgOrth->pDrlgRoom, &moo_pDrlgRoom1);
			CHECK_EQ(moo_pDrlgRoom2.pDrlgOrth->nDirection, original_pDrlgRoom2.pDrlgOrth->nDirection);
			CHECK_EQ(moo_pDrlgRoom2.pDrlgOrth->bInit, original_pDrlgRoom2.pDrlgOrth->bInit);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77600")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_AddOrth, dll_base + 0x00037600);

		SUBCASE("")
		{
			// Input data
			D2DrlgOrthStrc* moo_ppDrlgOrth{};
			D2DrlgOrthStrc moo_pExistingDrlgOrth{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgOrthStrc* original_ppDrlgOrth{};
			D2DrlgOrthStrc original_pExistingDrlgOrth{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			int nDirection = DIRECTION_SOUTHEAST;
			BOOL bIsPreset = TRUE;

			const auto setup_data = [](
				D2DrlgOrthStrc*& ppDrlgOrth,
				D2DrlgOrthStrc& pExistingDrlgOrth,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pLevel.pDrlg = &pDrlg;

				// The new orth has a higher direction, so it gets inserted after the existing one
				pExistingDrlgOrth.nDirection = DIRECTION_SOUTHWEST;
				ppDrlgOrth = &pExistingDrlgOrth;
			};

			setup_data(moo_ppDrlgOrth, moo_pExistingDrlgOrth, moo_pLevel, moo_pDrlg);
			setup_data(original_ppDrlgOrth, original_pExistingDrlgOrth, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_ppDrlgOrth, &moo_pLevel, nDirection, bIsPreset);
			original(&original_ppDrlgOrth, &original_pLevel, nDirection, bIsPreset);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ppDrlgOrth, original_ppDrlgOrth, "Comparing ppDrlgOrth");
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");

			// Check specific values
			CHECK_EQ(moo_ppDrlgOrth, &moo_pExistingDrlgOrth);
			REQUIRE_NE(moo_pExistingDrlgOrth.pNext, nullptr);
			REQUIRE_NE(original_pExistingDrlgOrth.pNext, nullptr);
			CHECK_EQ(moo_pExistingDrlgOrth.pNext->pLevel, &moo_pLevel);
			CHECK_EQ(moo_pExistingDrlgOrth.pNext->pBox, &moo_pLevel.pLevelCoords);
			CHECK_EQ(moo_pExistingDrlgOrth.pNext->nDirection, original_pExistingDrlgOrth.pNext->nDirection);
			CHECK_EQ(moo_pExistingDrlgOrth.pNext->bPreset, original_pExistingDrlgOrth.pNext->bPreset);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD776B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD776B0, dll_base + 0x000376B0);

		SUBCASE("")
		{
			// Input data
			D2DrlgOrthStrc moo_pDrlgOrth1{};
			D2DrlgOrthStrc moo_pDrlgOrth2{};
			D2DrlgCoordStrc moo_pBox1{};
			D2DrlgCoordStrc moo_pBox2{};
			D2DrlgOrthStrc original_pDrlgOrth1{};
			D2DrlgOrthStrc original_pDrlgOrth2{};
			D2DrlgCoordStrc original_pBox1{};
			D2DrlgCoordStrc original_pBox2{};

			const auto setup_data = [](
				D2DrlgOrthStrc& pDrlgOrth1,
				D2DrlgOrthStrc& pDrlgOrth2,
				D2DrlgCoordStrc& pBox1,
				D2DrlgCoordStrc& pBox2
			) {
				// Same direction, so the boxes' positions get compared
				pDrlgOrth1.nDirection = DIRECTION_SOUTHWEST;
				pDrlgOrth2.nDirection = DIRECTION_SOUTHWEST;

				pBox1 = { 0, 10, 5, 5 };
				pBox2 = { 0, 5, 5, 5 };

				pDrlgOrth1.pBox = &pBox1;
				pDrlgOrth2.pBox = &pBox2;
			};

			setup_data(moo_pDrlgOrth1, moo_pDrlgOrth2, moo_pBox1, moo_pBox2);
			setup_data(original_pDrlgOrth1, original_pDrlgOrth2, original_pBox1, original_pBox2);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgOrth1, &moo_pDrlgOrth2);
			const auto original_result = original(&original_pDrlgOrth1, &original_pDrlgOrth2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgOrth1, original_pDrlgOrth1, "Comparing pDrlgOrth1");
			MOO_CHECK_EQ(moo_pDrlgOrth2, original_pDrlgOrth2, "Comparing pDrlgOrth2");

			// Check specific values
			CHECK_EQ(moo_result, TRUE);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77740")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetRectanglesManhattanDistanceAndCheckNotOverlapping, dll_base + 0x00037740);

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord1{};
			D2DrlgCoordStrc moo_pDrlgCoord2{};
			int moo_pDistanceX{};
			int moo_pDistanceY{};
			D2DrlgCoordStrc original_pDrlgCoord1{};
			D2DrlgCoordStrc original_pDrlgCoord2{};
			int original_pDistanceX{};
			int original_pDistanceY{};
			int nMaxDistance = 2;

			const auto setup_data = [](
				D2DrlgCoordStrc& pDrlgCoord1,
				D2DrlgCoordStrc& pDrlgCoord2,
				int& pDistanceX,
				int& pDistanceY
			) {
				pDrlgCoord1 = { 0, 0, 10, 10 };
				pDrlgCoord2 = { 15, 3, 5, 5 };
			};

			setup_data(moo_pDrlgCoord1, moo_pDrlgCoord2, moo_pDistanceX, moo_pDistanceY);
			setup_data(original_pDrlgCoord1, original_pDrlgCoord2, original_pDistanceX, original_pDistanceY);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, nMaxDistance, &moo_pDistanceX, &moo_pDistanceY);
			const auto original_result = original(&original_pDrlgCoord1, &original_pDrlgCoord2, nMaxDistance, &original_pDistanceX, &original_pDistanceY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
			MOO_CHECK_EQ(moo_pDistanceX, original_pDistanceX, "Comparing pDistanceX");
			MOO_CHECK_EQ(moo_pDistanceY, original_pDistanceY, "Comparing pDistanceY");

			// Check specific values
			CHECK_EQ(moo_pDistanceX, 5);
			CHECK_EQ(moo_pDistanceY, -7);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD777B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_CheckNotOverlappingUsingManhattanDistance, dll_base + 0x000377B0);

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord1{};
			D2DrlgCoordStrc moo_pDrlgCoord2{};
			D2DrlgCoordStrc original_pDrlgCoord1{};
			D2DrlgCoordStrc original_pDrlgCoord2{};
			int nMaxDistance = 0;

			const auto setup_data = [](
				D2DrlgCoordStrc& pDrlgCoord1,
				D2DrlgCoordStrc& pDrlgCoord2
			) {
				// Overlapping rectangles
				pDrlgCoord1 = { 0, 0, 10, 10 };
				pDrlgCoord2 = { 5, 5, 10, 10 };
			};

			setup_data(moo_pDrlgCoord1, moo_pDrlgCoord2);
			setup_data(original_pDrlgCoord1, original_pDrlgCoord2);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, nMaxDistance);
			const auto original_result = original(&original_pDrlgCoord1, &original_pDrlgCoord2, nMaxDistance);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");

			// Check specific values
			CHECK_EQ(moo_result, FALSE);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77800")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_CheckOverlappingWithOrthogonalMargin, dll_base + 0x00037800);

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord1{};
			D2DrlgCoordStrc moo_pDrlgCoord2{};
			D2DrlgCoordStrc original_pDrlgCoord1{};
			D2DrlgCoordStrc original_pDrlgCoord2{};
			int nOrthogonalDistanceMax = 3;

			const auto setup_data = [](
				D2DrlgCoordStrc& pDrlgCoord1,
				D2DrlgCoordStrc& pDrlgCoord2
			) {
				// Rectangles touching on the X axis
				pDrlgCoord1 = { 0, 0, 10, 10 };
				pDrlgCoord2 = { 10, 2, 5, 5 };
			};

			setup_data(moo_pDrlgCoord1, moo_pDrlgCoord2);
			setup_data(original_pDrlgCoord1, original_pDrlgCoord2);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, nOrthogonalDistanceMax);
			const auto original_result = original(&original_pDrlgCoord1, &original_pDrlgCoord2, nOrthogonalDistanceMax);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");

			// Check specific values
			CHECK_EQ(moo_result, TRUE);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77890")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGMAZE_CheckRoomNotOverlaping, dll_base + 0x00037890);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom1{};
			D2DrlgRoomStrc moo_pIgnoredRoom{};
			D2DrlgRoomStrc moo_pOtherRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom1{};
			D2DrlgRoomStrc original_pIgnoredRoom{};
			D2DrlgRoomStrc original_pOtherRoom{};
			int nMargin = 2;

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom1,
				D2DrlgRoomStrc& pIgnoredRoom,
				D2DrlgRoomStrc& pOtherRoom
			) {
				pDrlgRoom1.pDrlgCoord = { 0, 0, 10, 10 };
				// The ignored room overlaps, but must not be taken into account
				pIgnoredRoom.pDrlgCoord = { 5, 5, 10, 10 };
				// The other room is far enough away
				pOtherRoom.pDrlgCoord = { 20, 0, 10, 10 };

				pLevel.pFirstRoomEx = &pDrlgRoom1;
				pDrlgRoom1.pDrlgRoomNext = &pIgnoredRoom;
				pIgnoredRoom.pDrlgRoomNext = &pOtherRoom;
			};

			setup_data(moo_pLevel, moo_pDrlgRoom1, moo_pIgnoredRoom, moo_pOtherRoom);
			setup_data(original_pLevel, original_pDrlgRoom1, original_pIgnoredRoom, original_pOtherRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, &moo_pDrlgRoom1, &moo_pIgnoredRoom, nMargin);
			const auto original_result = original(&original_pLevel, &original_pDrlgRoom1, &original_pIgnoredRoom, nMargin);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			MOO_CHECK_EQ(moo_pIgnoredRoom, original_pIgnoredRoom, "Comparing pIgnoredRoom");

			// Check specific values
			CHECK_EQ(moo_result, TRUE);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77910")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_AddRoomExToLevel, dll_base + 0x00037910);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc moo_pExistingRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc original_pExistingRoom{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc& pExistingRoom
			) {
				pLevel.pFirstRoomEx = &pExistingRoom;
				pLevel.nRooms = 1;
			};

			setup_data(moo_pLevel, moo_pDrlgRoom, moo_pExistingRoom);
			setup_data(original_pLevel, original_pDrlgRoom, original_pExistingRoom);

			// Call both implementations
			sut(&moo_pLevel, &moo_pDrlgRoom);
			original(&original_pLevel, &original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_pLevel.pFirstRoomEx, &moo_pDrlgRoom);
			CHECK_EQ(moo_pLevel.nRooms, 2);
			CHECK_EQ(moo_pDrlgRoom.pDrlgRoomNext, &moo_pExistingRoom);
			CHECK_EQ(original_pDrlgRoom.pDrlgRoomNext, &original_pExistingRoom);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77930")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_AreXYInsideCoordinates, dll_base + 0x00037930);

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord{};
			D2DrlgCoordStrc original_pDrlgCoord{};
			int nX = 12;
			int nY = 22;

			const auto setup_data = [](
				D2DrlgCoordStrc& pDrlgCoord
			) {
				pDrlgCoord = { 10, 20, 5, 5 };
			};

			setup_data(moo_pDrlgCoord);
			setup_data(original_pDrlgCoord);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgCoord, nX, nY);
			const auto original_result = original(&original_pDrlgCoord, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");

			// Check specific values
			CHECK_EQ(moo_result, TRUE);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77980")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_AreXYInsideCoordinatesOrOnBorder, dll_base + 0x00037980);

		SUBCASE("")
		{
			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord{};
			D2DrlgCoordStrc original_pDrlgCoord{};
			// On the border
			int nX = 15;
			int nY = 25;

			const auto setup_data = [](
				D2DrlgCoordStrc& pDrlgCoord
			) {
				pDrlgCoord = { 10, 20, 5, 5 };
			};

			setup_data(moo_pDrlgCoord);
			setup_data(original_pDrlgCoord);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgCoord, nX, nY);
			const auto original_result = original(&original_pDrlgCoord, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");

			// Check specific values
			CHECK_EQ(moo_result, TRUE);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD779D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_CheckLOSDraw, dll_base + 0x000379D0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_NO_LOS_DRAW;
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

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD779F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD779F0, dll_base + 0x000379F0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgOutdoorRoomStrc moo_pOutdoor{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgOutdoorRoomStrc original_pOutdoor{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgOutdoorRoomStrc& pOutdoor
			) {
				pOutdoor.dwFlags = 0x80;

				pDrlgRoom.nType = DRLGTYPE_MAZE;
				pDrlgRoom.pOutdoor = &pOutdoor;
			};

			setup_data(moo_pDrlgRoom, moo_pOutdoor);
			setup_data(original_pDrlgRoom, original_pOutdoor);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_result, 0x80);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77A00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_CheckWaypointFlags, dll_base + 0x00037A00);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pDrlgRoom.dwFlags = DRLGROOMFLAG_HAS_WAYPOINT | DRLGROOMFLAG_AUTOMAP_REVEAL;
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

			// Check specific values
			CHECK_EQ(moo_result, DRLGROOMFLAG_HAS_WAYPOINT);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77A10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_GetLevelId, dll_base + 0x00037A10);

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
				pLevel.nLevelId = LEVEL_BLOODMOOR;
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

			// Check specific values
			CHECK_EQ(moo_result, LEVEL_BLOODMOOR);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77A20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_GetWarpDestinationLevel, dll_base + 0x00037A20);

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
			D2DrlgLevelStrc moo_pDestinationLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2RoomTileStrc original_pSourceRoomTile{};
			D2LvlWarpTxt original_pSourceLvlWarpTxtRecord{};
			D2DrlgRoomStrc original_pDestinationDrlgRoom{};
			D2RoomTileStrc original_pDestinationRoomTile{};
			D2LvlWarpTxt original_pDestinationLvlWarpTxtRecord{};
			D2ActiveRoomStrc original_pDestinationRoom{};
			D2DrlgLevelStrc original_pDestinationLevel{};
			int nSourceLevel = LEVEL_COLDPLAINS;

			const auto setup_data = [nSourceLevel](
				D2DrlgRoomStrc& pDrlgRoom,
				D2RoomTileStrc& pSourceRoomTile,
				D2LvlWarpTxt& pSourceLvlWarpTxtRecord,
				D2DrlgRoomStrc& pDestinationDrlgRoom,
				D2RoomTileStrc& pDestinationRoomTile,
				D2LvlWarpTxt& pDestinationLvlWarpTxtRecord,
				D2ActiveRoomStrc& pDestinationRoom,
				D2DrlgLevelStrc& pDestinationLevel
			) {
				// The room's warp tile leads to the destination room
				pSourceLvlWarpTxtRecord.dwLevelId = nSourceLevel;
				pSourceRoomTile.pLvlWarpTxtRecord = &pSourceLvlWarpTxtRecord;
				pSourceRoomTile.pDrlgRoom = &pDestinationDrlgRoom;
				pDrlgRoom.pRoomTiles = &pSourceRoomTile;

				// The destination room's warp tile leads back to the room
				pDestinationLvlWarpTxtRecord.dwLevelId = LEVEL_BLOODMOOR;
				pDestinationRoomTile.pLvlWarpTxtRecord = &pDestinationLvlWarpTxtRecord;
				pDestinationRoomTile.pDrlgRoom = &pDrlgRoom;
				pDestinationDrlgRoom.pRoomTiles = &pDestinationRoomTile;

				// The destination room is already active, so it doesn't need to be initialized
				pDestinationLevel.nLevelId = LEVEL_COLDPLAINS;
				pDestinationDrlgRoom.pLevel = &pDestinationLevel;
				pDestinationDrlgRoom.pRoom = &pDestinationRoom;
				pDestinationRoom.pDrlgRoom = &pDestinationDrlgRoom;
			};

			setup_data(moo_pDrlgRoom, moo_pSourceRoomTile, moo_pSourceLvlWarpTxtRecord, moo_pDestinationDrlgRoom, moo_pDestinationRoomTile, moo_pDestinationLvlWarpTxtRecord, moo_pDestinationRoom, moo_pDestinationLevel);
			setup_data(original_pDrlgRoom, original_pSourceRoomTile, original_pSourceLvlWarpTxtRecord, original_pDestinationDrlgRoom, original_pDestinationRoomTile, original_pDestinationLvlWarpTxtRecord, original_pDestinationRoom, original_pDestinationLevel);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nSourceLevel);
			const auto original_result = original(&original_pDrlgRoom, nSourceLevel);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_result, LEVEL_COLDPLAINS);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77AB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_GetLevelIdFromPopulatedRoom, dll_base + 0x00037AB0);

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
				pLevel.nLevelId = LEVEL_BLOODMOOR;
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

			// Check specific values
			CHECK_EQ(moo_result, LEVEL_BLOODMOOR);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77AF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_HasWaypoint, dll_base + 0x00037AF0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pDrlgRoom.dwFlags = DRLGROOMFLAG_HAS_WAYPOINT_SMALL;
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

			// Check specific values
			CHECK_EQ(moo_result, TRUE);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77B20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_GetPickedLevelPrestFilePathFromRoomEx, dll_base + 0x00037B20);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgPresetRoomStrc moo_pPresetRoom{};
			D2DrlgMapStrc moo_pDrlgMap{};
			D2LvlPrestTxt moo_pLvlPrestTxtRecord{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgPresetRoomStrc original_pPresetRoom{};
			D2DrlgMapStrc original_pDrlgMap{};
			D2LvlPrestTxt original_pLvlPrestTxtRecord{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgPresetRoomStrc& pPresetRoom,
				D2DrlgMapStrc& pDrlgMap,
				D2LvlPrestTxt& pLvlPrestTxtRecord
			) {
				constexpr char szFile[] = "Act1\\Tristram\\Tri_Town4.ds1";
				std::memcpy(pLvlPrestTxtRecord.szFile[1], szFile, sizeof(szFile));

				pDrlgMap.nPickedFile = 1;
				pDrlgMap.pLvlPrestTxtRecord = &pLvlPrestTxtRecord;

				pPresetRoom.pMap = &pDrlgMap;

				pDrlgRoom.nType = DRLGTYPE_PRESET;
				pDrlgRoom.pMaze = &pPresetRoom;
			};

			setup_data(moo_pDrlgRoom, moo_pPresetRoom, moo_pDrlgMap, moo_pLvlPrestTxtRecord);
			setup_data(original_pDrlgRoom, original_pPresetRoom, original_pDrlgMap, original_pLvlPrestTxtRecord);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(std::string(moo_result), std::string(original_result));
			CHECK_EQ(moo_result, &moo_pLvlPrestTxtRecord.szFile[1][0]);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77B50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_ReorderNearRoomList, dll_base + 0x00037B50);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc* moo_ppRoomsNear[3]{};
			D2DrlgRoomStrc moo_pNearDrlgRooms[3]{};
			D2ActiveRoomStrc moo_pRooms[2]{};
			D2ActiveRoomStrc* moo_ppRoomList[3]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc* original_ppRoomsNear[3]{};
			D2DrlgRoomStrc original_pNearDrlgRooms[3]{};
			D2ActiveRoomStrc original_pRooms[2]{};
			D2ActiveRoomStrc* original_ppRoomList[3]{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc*(& ppRoomsNear)[3],
				D2DrlgRoomStrc(& pNearDrlgRooms)[3],
				D2ActiveRoomStrc(& pRooms)[2],
				D2ActiveRoomStrc*(& ppRoomList)[3]
			) {
				for (auto i = 0; i < 3; ++i)
				{
					ppRoomsNear[i] = &pNearDrlgRooms[i];
				}

				// Make the active rooms distinguishable
				pRooms[0].nNumRooms = 1;
				pRooms[1].nNumRooms = 2;

				// The middle room has no active room, so it gets skipped
				pNearDrlgRooms[0].pRoom = &pRooms[0];
				pNearDrlgRooms[2].pRoom = &pRooms[1];

				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 3;

				// The unused entries of the room list are expected to be cleared
				ppRoomList[2] = &pRooms[0];
			};

			setup_data(moo_pDrlgRoom, moo_ppRoomsNear, moo_pNearDrlgRooms, moo_pRooms, moo_ppRoomList);
			setup_data(original_pDrlgRoom, original_ppRoomsNear, original_pNearDrlgRooms, original_pRooms, original_ppRoomList);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, moo_ppRoomList);
			const auto original_result = original(&original_pDrlgRoom, original_ppRoomList);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_ppRoomList[0], original_ppRoomList[0], "Comparing ppRoomList[0]");
			MOO_CHECK_EQ(moo_ppRoomList[1], original_ppRoomList[1], "Comparing ppRoomList[1]");
			MOO_CHECK_EQ(moo_ppRoomList[2], original_ppRoomList[2], "Comparing ppRoomList[2]");

			// Check specific values
			CHECK_EQ(moo_result, 2);
			CHECK_EQ(moo_ppRoomList[0], &moo_pRooms[0]);
			CHECK_EQ(moo_ppRoomList[1], &moo_pRooms[1]);
			CHECK_EQ(moo_ppRoomList[2], nullptr);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77BB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD77BB0, dll_base + 0x00037BB0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgRoomStrc moo_pTownDrlgRoom{};
			D2DrlgLevelStrc moo_pTownLevel{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgRoomStrc original_pTownDrlgRoom{};
			D2DrlgLevelStrc original_pTownLevel{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgRoomStrc& pTownDrlgRoom,
				D2DrlgLevelStrc& pTownLevel
			) {
				pLevel.nLevelId = LEVEL_BLOODMOOR;
				pTownLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;

				// No warp flags, so no other levels have to be initialized
				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.pDrlgCoord = { 0, 0, 8, 8 };

				// Adjacent room in a town level, so the room is expected to become unpopulated
				pTownDrlgRoom.pLevel = &pTownLevel;
				pTownDrlgRoom.pDrlgCoord = { 8, 0, 8, 8 };

				pLevel.pFirstRoomEx = &pDrlgRoom;
				pDrlgRoom.pDrlgRoomNext = &pTownDrlgRoom;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pTownDrlgRoom, moo_pTownLevel);
			setup_data(original_pDrlgRoom, original_pLevel, original_pTownDrlgRoom, original_pTownLevel);

			// Call both implementations
			sut(nullptr, &moo_pDrlgRoom);
			original(nullptr, &original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.nRoomsNear, 2);
			CHECK_NE(moo_pDrlgRoom.dwFlags & DRLGROOMFLAG_POPULATION_ZERO, 0u);
			for (auto i = 0; i < moo_pDrlgRoom.nRoomsNear; ++i)
			{
				MOO_CHECK_EQ(moo_pDrlgRoom.ppRoomsNear[i], original_pDrlgRoom.ppRoomsNear[i], "Comparing ppRoomsNear");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77EB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_SortRoomListByPosition, dll_base + 0x00037EB0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc* moo_ppRoomList[3]{};
			D2DrlgRoomStrc moo_pDrlgRooms[3]{};
			D2DrlgRoomStrc* original_ppRoomList[3]{};
			D2DrlgRoomStrc original_pDrlgRooms[3]{};
			int nListSize = 3;

			const auto setup_data = [](
				D2DrlgRoomStrc*(& ppRoomList)[3],
				D2DrlgRoomStrc(& pDrlgRooms)[3]
			) {
				// Rooms are listed from right to left, so they are expected to be reversed by the sort
				pDrlgRooms[0].pDrlgCoord = { 20, 0, 10, 10 };
				pDrlgRooms[1].pDrlgCoord = { 10, 0, 10, 10 };
				pDrlgRooms[2].pDrlgCoord = { 0, 0, 10, 10 };

				for (auto i = 0; i < 3; ++i)
				{
					ppRoomList[i] = &pDrlgRooms[i];
				}
			};

			setup_data(moo_ppRoomList, moo_pDrlgRooms);
			setup_data(original_ppRoomList, original_pDrlgRooms);

			// Call both implementations
			sut(moo_ppRoomList, nListSize);
			original(original_ppRoomList, nListSize);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_ppRoomList[0], original_ppRoomList[0], "Comparing ppRoomList[0]");
			MOO_CHECK_EQ(moo_ppRoomList[1], original_ppRoomList[1], "Comparing ppRoomList[1]");
			MOO_CHECK_EQ(moo_ppRoomList[2], original_ppRoomList[2], "Comparing ppRoomList[2]");

			// Check specific values
			CHECK_EQ(moo_ppRoomList[0], &moo_pDrlgRooms[2]);
			CHECK_EQ(moo_ppRoomList[1], &moo_pDrlgRooms[1]);
			CHECK_EQ(moo_ppRoomList[2], &moo_pDrlgRooms[0]);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77F00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD77F00, dll_base + 0x00037F00);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom1{};
			D2DrlgRoomStrc moo_pDrlgRoom2{};
			D2DrlgRoomStrc original_pDrlgRoom1{};
			D2DrlgRoomStrc original_pDrlgRoom2{};
			uint8_t nWarpId = 0;
			char nWarpFlag = 1;
			// No direction, so only the near rooms get updated
			int nDirection = -1;

			const auto setup_data = [nWarpFlag](
				D2DrlgRoomStrc& pDrlgRoom1,
				D2DrlgRoomStrc& pDrlgRoom2
			) {
				pDrlgRoom1.pDrlgCoord = { 0, 0, 8, 8 };

				// The near rooms list gets reallocated by the function, so it has to be allocated from the memory pool
				pDrlgRoom1.ppRoomsNear = (D2DrlgRoomStrc**)D2_ALLOC_POOL(nullptr, sizeof(D2DrlgRoomStrc*));
				pDrlgRoom1.ppRoomsNear[0] = &pDrlgRoom1;
				pDrlgRoom1.nRoomsNear = 1;

				// Adjacent room with the matching warp flag
				pDrlgRoom2.pDrlgCoord = { 8, 0, 8, 8 };
				pDrlgRoom2.dwFlags = DRLGROOMFLAG_HAS_WARP_0 << nWarpFlag;
			};

			setup_data(moo_pDrlgRoom1, moo_pDrlgRoom2);
			setup_data(original_pDrlgRoom1, original_pDrlgRoom2);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pDrlgRoom1, nWarpId, &moo_pDrlgRoom2, nWarpFlag, nDirection);
			const auto original_result = original(nullptr, &original_pDrlgRoom1, nWarpId, &original_pDrlgRoom2, nWarpFlag, nDirection);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");

			// Check specific values
			CHECK_EQ(moo_result, TRUE);
			REQUIRE_EQ(moo_pDrlgRoom1.nRoomsNear, 2);
			CHECK_EQ(moo_pDrlgRoom1.ppRoomsNear[0], &moo_pDrlgRoom1);
			CHECK_EQ(moo_pDrlgRoom1.ppRoomsNear[1], &moo_pDrlgRoom2);
			CHECK_EQ(original_pDrlgRoom1.ppRoomsNear[0], &original_pDrlgRoom1);
			CHECK_EQ(original_pDrlgRoom1.ppRoomsNear[1], &original_pDrlgRoom2);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD780E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_AllocPresetUnit, dll_base + 0x000380E0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			int nUnitType = UNIT_OBJECT;
			int nIndex = 30;
			int nMode = 1;
			int nX = 5;
			int nY = 7;

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nullptr, nUnitType, nIndex, nMode, nX, nY);
			const auto original_result = original(&original_pDrlgRoom, nullptr, nUnitType, nIndex, nMode, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pPresetUnits, moo_result);
			CHECK_EQ(original_pDrlgRoom.pPresetUnits, original_result);
			CHECK_EQ(moo_result->nUnitType, original_result->nUnitType);
			CHECK_EQ(moo_result->nIndex, original_result->nIndex);
			CHECK_EQ(moo_result->nMode, original_result->nMode);
			CHECK_EQ(moo_result->nXpos, original_result->nXpos);
			CHECK_EQ(moo_result->nYpos, original_result->nYpos);
			CHECK_EQ(moo_result->pNext, nullptr);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78160")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_GetPresetUnits, dll_base + 0x00038160);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2PresetUnitStrc moo_pPresetUnit{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2PresetUnitStrc original_pPresetUnit{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2PresetUnitStrc& pPresetUnit
			) {
				pPresetUnit.nUnitType = UNIT_OBJECT;
				pPresetUnit.nIndex = 30;

				// Preset units haven't been spawned yet
				pDrlgRoom.pPresetUnits = &pPresetUnit;
			};

			setup_data(moo_pDrlgRoom, moo_pPresetUnit);
			setup_data(original_pDrlgRoom, original_pPresetUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pPresetUnit);
			CHECK_NE(moo_pDrlgRoom.dwFlags & DRLGROOMFLAG_PRESET_UNITS_SPAWNED, 0u);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78190")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_SetRoom, dll_base + 0x00038190);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2ActiveRoomStrc original_pRoom{};

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pRoom);
			original(&original_pDrlgRoom, &original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_pDrlgRoom.pRoom, &moo_pRoom);
			CHECK_EQ(original_pDrlgRoom.pRoom, &original_pRoom);
		}
	}

	TEST_CASE_FIXTURE(LevelDefsTxtFixture<NoopFixture>, "D2Common.0x6FD781A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_GetRGB_IntensityFromRoomEx, dll_base + 0x000381A0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			uint8_t moo_pIntensity{};
			uint8_t moo_pRed{};
			uint8_t moo_pGreen{};
			uint8_t moo_pBlue{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			uint8_t original_pIntensity{};
			uint8_t original_pRed{};
			uint8_t original_pGreen{};
			uint8_t original_pBlue{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel
			) {
				pLevel.nLevelId = LEVEL_BLOODMOOR;
				pDrlgRoom.pLevel = &pLevel;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel);
			setup_data(original_pDrlgRoom, original_pLevel);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pIntensity, &moo_pRed, &moo_pGreen, &moo_pBlue);
			original(&original_pDrlgRoom, &original_pIntensity, &original_pRed, &original_pGreen, &original_pBlue);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pIntensity, original_pIntensity, "Comparing pIntensity");
			MOO_CHECK_EQ(moo_pRed, original_pRed, "Comparing pRed");
			MOO_CHECK_EQ(moo_pGreen, original_pGreen, "Comparing pGreen");
			MOO_CHECK_EQ(moo_pBlue, original_pBlue, "Comparing pBlue");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD781E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_GetVisArrayFromLevelId, dll_base + 0x000381E0);

		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pWarps[2]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pWarps[2]{};
			int nLevelId = LEVEL_BLOODMOOR;

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc(& pWarps)[2]
			) {
				pWarps[0].nLevel = LEVEL_ROGUEENCAMPMENT;
				pWarps[0].nVis[0] = LEVEL_BLOODMOOR;
				pWarps[0].pNext = &pWarps[1];

				// The level is found in the second entry of the list
				pWarps[1].nLevel = LEVEL_BLOODMOOR;
				pWarps[1].nVis[0] = LEVEL_ROGUEENCAMPMENT;
				pWarps[1].nVis[1] = LEVEL_COLDPLAINS;

				pDrlg.pWarp = &pWarps[0];
			};

			setup_data(moo_pDrlg, moo_pWarps);
			setup_data(original_pDrlg, original_pWarps);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pWarps[1].nVis[0]);
			CHECK_EQ(original_result, &original_pWarps[1].nVis[0]);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD78230")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGROOM_GetDrlgFromRoomEx, dll_base + 0x00038230);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgRoomStrc original_pRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pLevel.pDrlg = &pDrlg;
				pRoom.pLevel = &pLevel;
			};

			setup_data(moo_pRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pDrlg);
			CHECK_EQ(original_result, &original_pDrlg);
		}
	}
}
