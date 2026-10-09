#include <doctest.h>

#include <Windows.h>

#include <array>
#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Collision.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Path/PathMisc.h>
#include <Units/Units.h>


TEST_SUITE("PathMiscTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	// Room used by the tests: a square of subtiles with a vertical wall in its middle, open at both ends
	constexpr int32_t ROOM_X = 1000;
	constexpr int32_t ROOM_Y = 1000;
	constexpr int32_t ROOM_SIZE = 32;
	constexpr int32_t WALL_X = ROOM_SIZE / 2;
	constexpr int32_t WALL_GAP = 4;

	using CollisionMask = std::array<uint16_t, ROOM_SIZE * ROOM_SIZE>;

	void setup_room(D2ActiveRoomStrc& pRoom, D2RoomCollisionGridStrc& pCollisionGrid, CollisionMask& pCollisionMask)
	{
		pRoom.tCoords.nSubtileX = ROOM_X;
		pRoom.tCoords.nSubtileY = ROOM_Y;
		pRoom.tCoords.nSubtileWidth = ROOM_SIZE;
		pRoom.tCoords.nSubtileHeight = ROOM_SIZE;
		pRoom.pCollisionGrid = &pCollisionGrid;

		pCollisionGrid.pRoomCoords = pRoom.tCoords;
		pCollisionGrid.pCollisionMask = pCollisionMask.data();

		for (int32_t y = WALL_GAP; y < ROOM_SIZE - WALL_GAP; ++y)
		{
			pCollisionMask[WALL_X + y * ROOM_SIZE] = COLLIDE_WALL;
		}
	}

	// Returns a point inside the room that is at least 2 subtiles away from its borders
	auto random_room_point() -> D2PathPointStrc
	{
		return D2PathPointStrc{
			uint16_t(random_unsigned_integer(ROOM_X + 2, ROOM_X + ROOM_SIZE - 3)),
			uint16_t(random_unsigned_integer(ROOM_Y + 2, ROOM_Y + ROOM_SIZE - 3))
		};
	}


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA880")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAA880, dll_base + 0x0006A880);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				// Input data
				const std::array<int, 3> aTestDir = {
					int(random_unsigned_integer(0, 7)),
					int(random_unsigned_integer(0, 7)),
					int(random_unsigned_integer(0, 7))
				};

				D2PathInfoStrc moo_pPathInfo{};
				int moo_pTestDir[3]{};
				int moo_pDirection{};
				D2PathInfoStrc original_pPathInfo{};
				int original_pTestDir[3]{};
				int original_pDirection{};
				D2PathPointStrc pPoint = random_room_point();
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [aTestDir](
					D2PathInfoStrc& pPathInfo,
					int (&pTestDir)[3],
					int& pDirection,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_MONSTER;
					pDynamicPath.pUnit = &pUnit;

					pPathInfo.pStartRoom = &pRoom;
					pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
					pPathInfo.nCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pPathInfo.pDynamicPath = &pDynamicPath;

					pTestDir[0] = aTestDir[0];
					pTestDir[1] = aTestDir[1];
					pTestDir[2] = aTestDir[2];

					pDirection = PATH_DIR_NULL;
				};

				setup_data(moo_pPathInfo, moo_pTestDir, moo_pDirection, moo_pDynamicPath, moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pTestDir, original_pDirection, original_pDynamicPath, original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo, moo_pTestDir, pPoint, &moo_pDirection);
				const auto original_result = original(&original_pPathInfo, original_pTestDir, pPoint, &original_pDirection);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				for (auto j = 0; j < 3; ++j)
				{
					MOO_CHECK_EQ(moo_pTestDir[j], original_pTestDir[j], "Comparing pTestDir");
				}
				MOO_CHECK_EQ(moo_pDirection, original_pDirection, "Comparing pDirection");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDABA50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDABA50, dll_base + 0x0006BA50);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				// Small differences use a lookup table, bigger ones are computed
				D2PathPointStrc pPoint1{ uint16_t(random_unsigned_integer(1000, 1020)), uint16_t(random_unsigned_integer(1000, 1020)) };
				D2PathPointStrc pPoint2{ uint16_t(random_unsigned_integer(1000, 1020)), uint16_t(random_unsigned_integer(1000, 1020)) };

				// Call both implementations
				const auto moo_result = sut(pPoint1, pPoint2);
				const auto original_result = original(pPoint1, pPoint2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB6A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAB6A0, dll_base + 0x0006B6A0);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				D2PathPointStrc pPoint1{ uint16_t(random_unsigned_integer(1000, 1020)), uint16_t(random_unsigned_integer(1000, 1020)) };
				D2PathPointStrc pPoint2{ uint16_t(random_unsigned_integer(1000, 1020)), uint16_t(random_unsigned_integer(1000, 1020)) };

				// Call both implementations
				const auto moo_result = sut(pPoint1, pPoint2);
				const auto original_result = original(pPoint1, pPoint2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB750")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAB750, dll_base + 0x0006B750);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				int nX1 = random_unsigned_integer(1000, 1020);
				int nY1 = random_unsigned_integer(1000, 1020);
				int nX2 = random_unsigned_integer(1000, 1020);
				int nY2 = random_unsigned_integer(1000, 1020);

				// Call both implementations
				const auto moo_result = sut(nX1, nY1, nX2, nY2);
				const auto original_result = original(nX1, nY1, nX2, nY2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB7D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAB7D0, dll_base + 0x0006B7D0);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				// Input data
				int moo_pTestDir[3]{};
				int original_pTestDir[3]{};
				int nUnused{};
				D2PathPointStrc pPoint1{ uint16_t(random_unsigned_integer(1000, 1020)), uint16_t(random_unsigned_integer(1000, 1020)) };
				D2PathPointStrc pPoint2{ uint16_t(random_unsigned_integer(1000, 1020)), uint16_t(random_unsigned_integer(1000, 1020)) };

				const auto setup_data = [](
					int (&pTestDir)[3]
				) {
					// Output only, make sure every element gets written
					pTestDir[0] = PATH_DIR_NULL;
					pTestDir[1] = PATH_DIR_NULL;
					pTestDir[2] = PATH_DIR_NULL;
				};

				setup_data(moo_pTestDir);
				setup_data(original_pTestDir);

				// Call both implementations
				sut(moo_pTestDir, nUnused, pPoint1, pPoint2);
				original(original_pTestDir, nUnused, pPoint1, pPoint2);

				// Compare potentially modified input data
				for (auto j = 0; j < 3; ++j)
				{
					MOO_CHECK_EQ(moo_pTestDir[j], original_pTestDir[j], "Comparing pTestDir");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB0B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAB0B0, dll_base + 0x0006B0B0);

		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				const auto nVelocity = (i % 4 == 0) ? 0 : int32_t(random_unsigned_integer(1, 0x800));

				D2PathInfoStrc moo_pPathInfo{};
				D2PathInfoStrc original_pPathInfo{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetCoord, nVelocity](
					D2PathInfoStrc& pPathInfo,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_MONSTER;

					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tStartCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tStartCoord.Y);
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pDynamicPath.dwVelocity = nVelocity;
					pDynamicPath.dwCurrentPointIdx = 3;

					pPathInfo.tStartCoord = tStartCoord;
					pPathInfo.tTargetCoord = tTargetCoord;
					pPathInfo.pStartRoom = &pRoom;
					pPathInfo.nDistMax = 30;
					pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
					pPathInfo.nCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pPathInfo.pDynamicPath = &pDynamicPath;
				};

				setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pDynamicPath, original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo);
				const auto original_result = original(&original_pPathInfo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAA9F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_Toward_6FDAA9F0, dll_base + 0x0006A9F0);

		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				const auto nVelocity = (i % 4 == 0) ? 0 : int32_t(random_unsigned_integer(1, 0x800));
				// A direction offset makes the path computation use a different algorithm
				const auto nDirOffset = (i % 2 == 0) ? 0 : int32_t(random_unsigned_integer(1, 7));

				D2PathInfoStrc moo_pPathInfo{};
				D2PathInfoStrc original_pPathInfo{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetCoord, nVelocity, nDirOffset](
					D2PathInfoStrc& pPathInfo,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_MONSTER;

					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tStartCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tStartCoord.Y);
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pDynamicPath.dwVelocity = nVelocity;
					pDynamicPath.nDirOffset = nDirOffset;

					pPathInfo.tStartCoord = tStartCoord;
					pPathInfo.tTargetCoord = tTargetCoord;
					pPathInfo.pStartRoom = &pRoom;
					pPathInfo.nDistMax = 30;
					pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
					pPathInfo.nCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pPathInfo.pDynamicPath = &pDynamicPath;
				};

				setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pDynamicPath, original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo);
				const auto original_result = original(&original_pPathInfo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAABF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_CheckCollisionsToNextPosition, dll_base + 0x0006ABF0);

		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				const auto nVelocity = (i % 4 == 0) ? 0 : int32_t(random_unsigned_integer(1, 0x800));

				D2DynamicPathStrc moo_pDynamicPath{};
				D2PathPointStrc moo_pGameCoord{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2PathPointStrc original_pGameCoord{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetCoord, nVelocity](
					D2DynamicPathStrc& pDynamicPath,
					D2PathPointStrc& pGameCoord,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_PLAYER;

					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tStartCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tStartCoord.Y);
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_PLAYER_PATH;
					pDynamicPath.dwVelocity = nVelocity;
					pDynamicPath.PathPoints[0] = tTargetCoord;
					pDynamicPath.dwPathPoints = 1;

					pGameCoord = tTargetCoord;
				};

				setup_data(moo_pDynamicPath, moo_pGameCoord, moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pDynamicPath, original_pGameCoord, original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pDynamicPath, &moo_pGameCoord);
				const auto original_result = original(&original_pDynamicPath, &original_pGameCoord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_pGameCoord, original_pGameCoord, "Comparing pGameCoord");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB130")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_Straight_Compute, dll_base + 0x0006B130);

		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				const auto nVelocity = (i % 4 == 0) ? 0 : int32_t(random_unsigned_integer(1, 0x800));
				const auto nMaxDistance = random_unsigned_integer(0, 3);

				D2PathInfoStrc moo_pPathInfo{};
				D2PathInfoStrc original_pPathInfo{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetCoord, nVelocity, nMaxDistance](
					D2PathInfoStrc& pPathInfo,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_MONSTER;

					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tStartCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tStartCoord.Y);
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pDynamicPath.dwVelocity = nVelocity;

					pPathInfo.tStartCoord = tStartCoord;
					pPathInfo.tTargetCoord = tTargetCoord;
					pPathInfo.pStartRoom = &pRoom;
					pPathInfo.field_14 = nMaxDistance;
					pPathInfo.nDistMax = 30;
					pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
					pPathInfo.nCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pPathInfo.pDynamicPath = &pDynamicPath;
				};

				setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pDynamicPath, original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo);
				const auto original_result = original(&original_pPathInfo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB270")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_Knockback_Server, dll_base + 0x0006B270);

		SUBCASE("Without target unit")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				const auto nDist = uint8_t(random_unsigned_integer(0, 40));

				D2PathInfoStrc moo_pPathInfo{};
				D2PathInfoStrc original_pPathInfo{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetCoord, nDist](
					D2PathInfoStrc& pPathInfo,
					D2DynamicPathStrc& pDynamicPath,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pDynamicPath.nDist = nDist;

					pPathInfo.tStartCoord = tStartCoord;
					pPathInfo.tTargetCoord = tTargetCoord;
					pPathInfo.pDynamicPath = &pDynamicPath;
				};

				setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pDynamicPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo);
				const auto original_result = original(&original_pPathInfo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}

		SUBCASE("With target unit")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetUnitCoord = random_room_point();
				const auto nDist = uint8_t(random_unsigned_integer(0, 40));

				D2PathInfoStrc moo_pPathInfo{};
				D2PathInfoStrc original_pPathInfo{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pTargetUnit{};
				D2UnitStrc original_pTargetUnit{};
				D2DynamicPathStrc moo_pTargetDynamicPath{};
				D2DynamicPathStrc original_pTargetDynamicPath{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetUnitCoord, nDist](
					D2PathInfoStrc& pPathInfo,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pTargetUnit,
					D2DynamicPathStrc& pTargetDynamicPath,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pTargetDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tTargetUnitCoord.X);
					pTargetDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tTargetUnitCoord.Y);

					pTargetUnit.dwUnitType = UNIT_PLAYER;
					pTargetUnit.pDynamicPath = &pTargetDynamicPath;

					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.pTargetUnit = &pTargetUnit;
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pDynamicPath.nDist = nDist;

					pPathInfo.tStartCoord = tStartCoord;
					pPathInfo.pDynamicPath = &pDynamicPath;
				};

				setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pTargetUnit, moo_pTargetDynamicPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pDynamicPath, original_pTargetUnit, original_pTargetDynamicPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo);
				const auto original_result = original(&original_pPathInfo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB1E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_Leap_6FDAB1E0, dll_base + 0x0006B1E0);

		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				const auto nVelocity = (i % 4 == 0) ? 0 : int32_t(random_unsigned_integer(1, 0x800));

				D2PathInfoStrc moo_pPathInfo{};
				D2PathInfoStrc original_pPathInfo{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetCoord, nVelocity](
					D2PathInfoStrc& pPathInfo,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_PLAYER;

					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tStartCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tStartCoord.Y);
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_PLAYER_PATH;
					pDynamicPath.dwVelocity = nVelocity;
					pDynamicPath.dwPathPoints = 1;

					pPathInfo.tStartCoord = tStartCoord;
					pPathInfo.tTargetCoord = tTargetCoord;
					pPathInfo.pDynamicPath = &pDynamicPath;
				};

				setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pDynamicPath, original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo);
				const auto original_result = original(&original_pPathInfo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB240")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_Knockback_Client, dll_base + 0x0006B240);

		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				const auto nVelocity = (i % 4 == 0) ? 0 : int32_t(random_unsigned_integer(1, 0x800));

				D2PathInfoStrc moo_pPathInfo{};
				D2PathInfoStrc original_pPathInfo{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetCoord, nVelocity](
					D2PathInfoStrc& pPathInfo,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_PLAYER;

					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tStartCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tStartCoord.Y);
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_PLAYER_PATH;
					pDynamicPath.dwVelocity = nVelocity;
					pDynamicPath.dwPathPoints = 1;

					pPathInfo.tStartCoord = tStartCoord;
					pPathInfo.tTargetCoord = tTargetCoord;
					pPathInfo.pDynamicPath = &pDynamicPath;
				};

				setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pDynamicPath, original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo);
				const auto original_result = original(&original_pPathInfo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB0C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_BackupTurn_Compute, dll_base + 0x0006B0C0);

		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();

				D2PathInfoStrc moo_pPathInfo{};
				D2PathInfoStrc original_pPathInfo{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tStartCoord, tTargetCoord](
					D2PathInfoStrc& pPathInfo,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_MONSTER;

					pDynamicPath.pUnit = &pUnit;

					pPathInfo.tStartCoord = tStartCoord;
					pPathInfo.tTargetCoord = tTargetCoord;
					pPathInfo.pStartRoom = &pRoom;
					// The path gets computed up to 3 times, keep it short enough to fit into the path points
					pPathInfo.nDistMax = 20;
					pPathInfo.nCollisionPattern = COLLISION_PATTERN_NONE;
					pPathInfo.nCollisionMask = COLLIDE_MASK_MONSTER_PATH;
					pPathInfo.pDynamicPath = &pDynamicPath;
				};

				setup_data(moo_pPathInfo, moo_pDynamicPath, moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pPathInfo, original_pDynamicPath, original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pPathInfo);
				const auto original_result = original(&original_pPathInfo);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPathInfo, original_pPathInfo, "Comparing pPathInfo");
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB790")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetDirections_6FDAB790, dll_base + 0x0006B790);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				// Input data
				int moo_pTestDir[3]{};
				int original_pTestDir[3]{};
				D2PathPointStrc pPoint1{ uint16_t(random_unsigned_integer(1000, 1020)), uint16_t(random_unsigned_integer(1000, 1020)) };
				D2PathPointStrc pPoint2{ uint16_t(random_unsigned_integer(1000, 1020)), uint16_t(random_unsigned_integer(1000, 1020)) };

				const auto setup_data = [](
					int (&pTestDir)[3]
				) {
					// Output only, make sure every element gets written
					pTestDir[0] = PATH_DIR_NULL;
					pTestDir[1] = PATH_DIR_NULL;
					pTestDir[2] = PATH_DIR_NULL;
				};

				setup_data(moo_pTestDir);
				setup_data(original_pTestDir);

				// Call both implementations
				sut(moo_pTestDir, pPoint1, pPoint2);
				original(original_pTestDir, pPoint1, pPoint2);

				// Compare potentially modified input data
				for (auto j = 0; j < 3; ++j)
				{
					MOO_CHECK_EQ(moo_pTestDir[j], original_pTestDir[j], "Comparing pTestDir");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB3C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ComputePathBlessedHammer_6FDAB3C0, dll_base + 0x0006B3C0);

		SUBCASE("")
		{
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto nOffsetX = uint16_t(random_unsigned_integer(0, 0xFFFF));
				const auto nOffsetY = uint16_t(random_unsigned_integer(0, 0xFFFF));

				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};

				const auto setup_data = [tStartCoord, nOffsetX, nOffsetY](
					D2DynamicPathStrc& pDynamicPath
				) {
					pDynamicPath.tGameCoords.wPosX = tStartCoord.X;
					pDynamicPath.tGameCoords.wOffsetX = nOffsetX;
					pDynamicPath.tGameCoords.wPosY = tStartCoord.Y;
					pDynamicPath.tGameCoords.wOffsetY = nOffsetY;
				};

				setup_data(moo_pDynamicPath);
				setup_data(original_pDynamicPath);

				// Call both implementations
				const auto moo_result = sut(&moo_pDynamicPath);
				const auto original_result = original(&original_pDynamicPath);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAAD10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_RayTrace, dll_base + 0x0006AD10);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				// Input data
				const auto tDestination = random_room_point();

				D2DynamicPathStrc moo_pDynamicPath{};
				D2PathPointStrc moo_pPathDestination{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2PathPointStrc original_pPathDestination{};
				D2PathPointStrc tStartCoord = random_room_point();
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tDestination](
					D2DynamicPathStrc& pDynamicPath,
					D2PathPointStrc& pPathDestination,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask);

					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_NONE;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_MONSTER_PATH;

					pPathDestination = tDestination;
				};

				setup_data(moo_pDynamicPath, moo_pPathDestination, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pDynamicPath, original_pPathDestination, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pDynamicPath, &moo_pPathDestination, tStartCoord);
				const auto original_result = original(&original_pDynamicPath, &original_pPathDestination, tStartCoord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_pPathDestination, original_pPathDestination, "Comparing pPathDestination");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB4A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ComputePathChargedBolt_6FDAB4A0, dll_base + 0x0006B4A0);

		SUBCASE("")
		{
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				const auto tStartCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				// Generates nDistMax / 2 + 1 points, which must fit into the path points
				const auto nDistMax = random_unsigned_integer(0, 2 * (D2DynamicPathStrc::MAXPATHLEN - 1));
				const auto nLowSeed = random_unsigned_integer();
				const auto nHighSeed = random_unsigned_integer();

				D2DynamicPathStrc moo_pDynamicPath{};
				D2SeedStrc moo_pSeed{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2SeedStrc original_pSeed{};

				const auto setup_data = [tStartCoord, tTargetCoord, nDistMax, nLowSeed, nHighSeed](
					D2DynamicPathStrc& pDynamicPath,
					D2SeedStrc& pSeed
				) {
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tStartCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tStartCoord.Y);
					pDynamicPath.tTargetCoord = tTargetCoord;
					pDynamicPath.nDistMax = nDistMax;

					pSeed.nLowSeed = nLowSeed;
					pSeed.nHighSeed = nHighSeed;
				};

				setup_data(moo_pDynamicPath, moo_pSeed);
				setup_data(original_pDynamicPath, original_pSeed);

				// Call both implementations
				const auto moo_result = sut(&moo_pDynamicPath, &moo_pSeed);
				const auto original_result = original(&original_pDynamicPath, &original_pSeed);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAB610")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAB610, dll_base + 0x0006B610);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				int nX1 = random_unsigned_integer(1000, 1020);
				int nY1 = random_unsigned_integer(1000, 1020);
				int nX2 = random_unsigned_integer(1000, 1020);
				int nY2 = random_unsigned_integer(1000, 1020);

				// Call both implementations
				const auto moo_result = sut(nX1, nY1, nX2, nY2);
				const auto original_result = original(nX1, nY1, nX2, nY2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC700 (#10215)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ComputeDirection, dll_base + 0x0006C700);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				int nX1 = random_unsigned_integer(1000, 1100);
				int nY1 = random_unsigned_integer(1000, 1100);
				int nX2 = random_unsigned_integer(1000, 1100);
				int nY2 = random_unsigned_integer(1000, 1100);

				// Call both implementations
				const auto moo_result = sut(nX1, nY1, nX2, nY2);
				const auto original_result = original(nX1, nY1, nX2, nY2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC760")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ComputeDirectionFromPreciseCoords_6FDAC760, dll_base + 0x0006C760);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				// Keep the coordinates close enough to each other to not overflow when computing the tangent
				DWORD dwStartPrecisionX = random_unsigned_integer(PATH_ToFP16Corner(1000), PATH_ToFP16Corner(1100));
				DWORD dwStartPrecisionY = random_unsigned_integer(PATH_ToFP16Corner(1000), PATH_ToFP16Corner(1100));
				DWORD dwTargetPrecisionX = random_unsigned_integer(PATH_ToFP16Corner(1000), PATH_ToFP16Corner(1100));
				DWORD dwTargetPrecisionY = random_unsigned_integer(PATH_ToFP16Corner(1000), PATH_ToFP16Corner(1100));

				// Call both implementations
				const auto moo_result = sut(dwStartPrecisionX, dwStartPrecisionY, dwTargetPrecisionX, dwTargetPrecisionY);
				const auto original_result = original(dwStartPrecisionX, dwStartPrecisionY, dwTargetPrecisionX, dwTargetPrecisionY);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC790")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_ComputeVelocityAndDirectionVectorsToNextPoint, dll_base + 0x0006C790);

		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				// Input data
				const auto tCurrentCoord = random_room_point();
				// Being exactly at the center of the subtile allows path points to be skipped as duplicates
				const auto nOffsetX = (i & 8) ? uint16_t(0x8000) : uint16_t(random_unsigned_integer(0, 0xFFFF));
				const auto nOffsetY = (i & 8) ? uint16_t(0x8000) : uint16_t(random_unsigned_integer(0, 0xFFFF));
				const auto nVelocity = int32_t(random_unsigned_integer(0, 0x1000));
				const auto nDirection = random_unsigned_integer(0, PATH_NB_DIRECTIONS - 1);
				const auto dwFlags = (i & 16) ? PATH_UNKNOWN_FLAG_0x00200 : 0u;

				constexpr int32_t nPathPoints = 4;
				std::array<D2PathPointStrc, nPathPoints> aPathPoints{};
				for (auto& tPathPoint : aPathPoints)
				{
					tPathPoint = random_unsigned_integer(0, 1) ? tCurrentCoord : random_room_point();
				}

				D2DynamicPathStrc moo_pPath{};
				D2DynamicPathStrc original_pPath{};
				BOOL bNormalizeDirectionIfSamePos = (i & 1) ? TRUE : FALSE;
				BOOL bForceDirectionNormalization = (i & 2) ? TRUE : FALSE;

				const auto setup_data = [tCurrentCoord, nPathPoints, nOffsetX, nOffsetY, nVelocity, nDirection, dwFlags, aPathPoints](
					D2DynamicPathStrc& pPath
				) {
					pPath.tGameCoords.wPosX = tCurrentCoord.X;
					pPath.tGameCoords.wOffsetX = nOffsetX;
					pPath.tGameCoords.wPosY = tCurrentCoord.Y;
					pPath.tGameCoords.wOffsetY = nOffsetY;
					pPath.dwVelocity = nVelocity;
					pPath.nDirection = nDirection;
					pPath.dwFlags = dwFlags;

					for (auto j = 0; j < nPathPoints; ++j)
					{
						pPath.PathPoints[j] = aPathPoints[j];
					}
					pPath.dwPathPoints = nPathPoints;
					pPath.dwCurrentPointIdx = 0;
				};

				setup_data(moo_pPath);
				setup_data(original_pPath);

				// Call both implementations
				sut(&moo_pPath, bNormalizeDirectionIfSamePos, bForceDirectionNormalization);
				original(&original_pPath, bNormalizeDirectionIfSamePos, bForceDirectionNormalization);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPath, original_pPath, "Comparing pPath");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC8F0 (#10236)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10236, dll_base + 0x0006C8F0);

		SUBCASE("Without dynamic path")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int a2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, a2);
			const auto original_result = original(&original_pUnit, a2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("With dynamic path")
		{
			for (auto nPathType : { PATHTYPE_ASTAR, PATHTYPE_TOWARD, PATHTYPE_TOWARD_FINISH, PATHTYPE_WALL_FOLLOW })
			{
				for (auto i = 0; i < 4; ++i)
				{
					// Input data
					const auto tCurrentCoord = random_room_point();
					const auto tFinalTargetCoord = random_room_point();
					const auto nDistance = random_unsigned_integer(0, 20);
					const auto nCurrentPointIdx = int32_t(random_unsigned_integer(0, 20));
					const auto dwFlags = (i & 1) ? PATH_UNKNOWN_FLAG_0x00010 : 0u;

					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};
					D2DynamicPathStrc moo_pDynamicPath{};
					D2DynamicPathStrc original_pDynamicPath{};
					int a2 = (i & 2) ? TRUE : FALSE;

					const auto setup_data = [nPathType, tCurrentCoord, tFinalTargetCoord, nDistance, nCurrentPointIdx, dwFlags](
						D2UnitStrc& pUnit,
						D2DynamicPathStrc& pDynamicPath
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pDynamicPath = &pDynamicPath;

						// Without a room, no path can be computed
						pDynamicPath.pUnit = &pUnit;
						pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tCurrentCoord.X);
						pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tCurrentCoord.Y);
						pDynamicPath.tFinalTargetCoord = tFinalTargetCoord;
						pDynamicPath.dwPathType = nPathType;
						pDynamicPath.dwFlags = dwFlags;
						pDynamicPath.nDistance = nDistance;
						pDynamicPath.dwCurrentPointIdx = nCurrentPointIdx;
					};

					setup_data(moo_pUnit, moo_pDynamicPath);
					setup_data(original_pUnit, original_pDynamicPath);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, a2);
					const auto original_result = original(&original_pUnit, a2);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC9A0 (#10226)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10226, dll_base + 0x0006C9A0);

		SUBCASE("Without dynamic path")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			signed int a2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, a2);
			const auto original_result = original(&original_pUnit, a2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Not moving")
		{
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				const auto tCurrentCoord = random_room_point();
				const auto nOffsetX = uint16_t(random_unsigned_integer(0, 0xFFFF));
				const auto nOffsetY = uint16_t(random_unsigned_integer(0, 0xFFFF));
				const auto nPathPoints = int32_t(random_unsigned_integer(0, 10));
				const auto nCollidedWithMask = random_unsigned_integer(0, 0xFFFF);
				uint32_t dwFlags = PATH_UNKNOWN_FLAG_0x00008;
				if (i & 1)
				{
					dwFlags |= PATH_UNKNOWN_FLAG_0x00020;
				}
				if (i & 2)
				{
					dwFlags |= PATH_MISSILE_MASK;
				}

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				signed int a2 = random_unsigned_integer(0, 2048);

				const auto setup_data = [tCurrentCoord, nOffsetX, nOffsetY, nPathPoints, nCollidedWithMask, dwFlags](
					D2UnitStrc& pUnit,
					D2DynamicPathStrc& pDynamicPath
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pDynamicPath = &pDynamicPath;

					// Without velocity, the movement gets reset
					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.tGameCoords.wPosX = tCurrentCoord.X;
					pDynamicPath.tGameCoords.wOffsetX = nOffsetX;
					pDynamicPath.tGameCoords.wPosY = tCurrentCoord.Y;
					pDynamicPath.tGameCoords.wOffsetY = nOffsetY;
					pDynamicPath.dwFlags = dwFlags;
					pDynamicPath.dwPathPoints = nPathPoints;
					pDynamicPath.dwCurrentPointIdx = 1;
					pDynamicPath.nCollidedWithMask = nCollidedWithMask;
					pDynamicPath.tVelocityVector.nX = 0x100;
					pDynamicPath.tVelocityVector.nY = 0x100;
				};

				setup_data(moo_pUnit, moo_pDynamicPath);
				setup_data(original_pUnit, original_pDynamicPath);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, a2);
				const auto original_result = original(&original_pUnit, a2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAD530 (#10227)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10227, dll_base + 0x0006D530);

		SUBCASE("Without dynamic path")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without target unit")
		{
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				const auto tCurrentCoord = random_room_point();
				const auto tTargetCoord = (i % 2 == 0) ? tCurrentCoord : random_room_point();

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};

				const auto setup_data = [tCurrentCoord, tTargetCoord](
					D2UnitStrc& pUnit,
					D2DynamicPathStrc& pDynamicPath
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pDynamicPath = &pDynamicPath;

					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tCurrentCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tCurrentCoord.Y);
					pDynamicPath.tTargetCoord = tTargetCoord;
				};

				setup_data(moo_pUnit, moo_pDynamicPath);
				setup_data(original_pUnit, original_pDynamicPath);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("With target unit")
		{
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				const auto tCurrentCoord = random_room_point();
				const auto tTargetCoord = random_room_point();
				const auto tTargetUnitCoord = random_room_point();
				const auto nStepNum = uint8_t(random_unsigned_integer(0, 20));

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc moo_pTargetUnit{};
				D2UnitStrc original_pTargetUnit{};
				D2DynamicPathStrc moo_pTargetDynamicPath{};
				D2DynamicPathStrc original_pTargetDynamicPath{};

				const auto setup_data = [tCurrentCoord, tTargetCoord, tTargetUnitCoord, nStepNum](
					D2UnitStrc& pUnit,
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pTargetUnit,
					D2DynamicPathStrc& pTargetDynamicPath
				) {
					pTargetDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tTargetUnitCoord.X);
					pTargetDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tTargetUnitCoord.Y);

					pTargetUnit.dwUnitType = UNIT_PLAYER;
					pTargetUnit.pDynamicPath = &pTargetDynamicPath;

					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pDynamicPath = &pDynamicPath;

					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tCurrentCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tCurrentCoord.Y);
					pDynamicPath.tTargetCoord = tTargetCoord;
					pDynamicPath.pTargetUnit = &pTargetUnit;
					pDynamicPath.nStepNum = nStepNum;
				};

				setup_data(moo_pUnit, moo_pDynamicPath, moo_pTargetUnit, moo_pTargetDynamicPath);
				setup_data(original_pUnit, original_pDynamicPath, original_pTargetUnit, original_pTargetDynamicPath);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAD590 (#10229)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10229, dll_base + 0x0006D590);

		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto tCurrentCoord = random_room_point();
				const auto tDestCoord = random_room_point();
				const auto nPathPoints = int32_t(random_unsigned_integer(0, 10));

				D2DynamicPathStrc moo_pDynamicPath{};
				D2UnitStrc moo_pUnit{};
				D2ActiveRoomStrc moo_pDestRoom{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2UnitStrc original_pUnit{};
				D2ActiveRoomStrc original_pDestRoom{};
				uint32_t nDestX = tDestCoord.X;
				uint32_t nDestY = tDestCoord.Y;
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				CollisionMask moo_pCollisionMask{};
				CollisionMask original_pCollisionMask{};

				const auto setup_data = [tCurrentCoord, nPathPoints](
					D2DynamicPathStrc& pDynamicPath,
					D2UnitStrc& pUnit,
					D2ActiveRoomStrc& pDestRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					CollisionMask& pCollisionMask
				) {
					setup_room(pDestRoom, pCollisionGrid, pCollisionMask);

					pUnit.dwUnitType = UNIT_PLAYER;

					// The unit stays in the same room, so it doesn't need to be moved to another one
					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.pRoom = &pDestRoom;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tCurrentCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tCurrentCoord.Y);
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
					pDynamicPath.nFootprintCollisionMask = COLLIDE_PLAYER;
					pDynamicPath.dwPathPoints = nPathPoints;
					pDynamicPath.dwFlags = PATH_UNKNOWN_FLAG_0x00020;
				};

				setup_data(moo_pDynamicPath, moo_pUnit, moo_pDestRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pDynamicPath, original_pUnit, original_pDestRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pDynamicPath, &moo_pUnit, &moo_pDestRoom, nDestX, nDestY);
				const auto original_result = original(&original_pDynamicPath, &original_pUnit, &original_pDestRoom, nDestX, nDestY);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pDestRoom, original_pDestRoom, "Comparing pDestRoom");
				CHECK_MESSAGE(moo_pCollisionMask == original_pCollisionMask, "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDADA20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_RecacheRoom, dll_base + 0x0006DA20);

		SUBCASE("Room is up to date")
		{
			for (auto i = 0; i < 8; ++i)
			{
				// Input data
				const auto tCurrentCoord = random_room_point();

				D2DynamicPathStrc moo_pDynamicPath{};
				D2ActiveRoomStrc moo_pHintRoom{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2ActiveRoomStrc original_pHintRoom{};
				D2ActiveRoomStrc moo_pRoom{};
				D2ActiveRoomStrc original_pRoom{};

				const auto setup_data = [tCurrentCoord](
					D2DynamicPathStrc& pDynamicPath,
					D2ActiveRoomStrc& pHintRoom,
					D2ActiveRoomStrc& pRoom
				) {
					pRoom.tCoords.nSubtileX = ROOM_X;
					pRoom.tCoords.nSubtileY = ROOM_Y;
					pRoom.tCoords.nSubtileWidth = ROOM_SIZE;
					pRoom.tCoords.nSubtileHeight = ROOM_SIZE;

					// Hint room next to the current one
					pHintRoom.tCoords = pRoom.tCoords;
					pHintRoom.tCoords.nSubtileX += ROOM_SIZE;

					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tCurrentCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tCurrentCoord.Y);
				};

				setup_data(moo_pDynamicPath, moo_pHintRoom, moo_pRoom);
				setup_data(original_pDynamicPath, original_pHintRoom, original_pRoom);

				// Call both implementations
				sut(&moo_pDynamicPath, &moo_pHintRoom);
				original(&original_pDynamicPath, &original_pHintRoom);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_pHintRoom, original_pHintRoom, "Comparing pHintRoom");
			}
		}

		SUBCASE("Room found from hint room")
		{
			for (auto i = 0; i < 8; ++i)
			{
				// Input data
				const auto tCurrentCoord = random_room_point();

				D2DynamicPathStrc moo_pDynamicPath{};
				D2ActiveRoomStrc moo_pHintRoom{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2ActiveRoomStrc original_pHintRoom{};
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				D2DrlgActStrc moo_pAct{};
				D2DrlgActStrc original_pAct{};

				const auto setup_data = [tCurrentCoord](
					D2DynamicPathStrc& pDynamicPath,
					D2ActiveRoomStrc& pHintRoom,
					D2UnitStrc& pUnit,
					D2DrlgActStrc& pAct
				) {
					pHintRoom.tCoords.nSubtileX = ROOM_X;
					pHintRoom.tCoords.nSubtileY = ROOM_Y;
					pHintRoom.tCoords.nSubtileWidth = ROOM_SIZE;
					pHintRoom.tCoords.nSubtileHeight = ROOM_SIZE;
					pHintRoom.pAct = &pAct;

					// The unit gets added to the room it is found in
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pDynamicPath = &pDynamicPath;

					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tCurrentCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tCurrentCoord.Y);
				};

				setup_data(moo_pDynamicPath, moo_pHintRoom, moo_pUnit, moo_pAct);
				setup_data(original_pDynamicPath, original_pHintRoom, original_pUnit, original_pAct);

				// Call both implementations
				sut(&moo_pDynamicPath, &moo_pHintRoom);
				original(&original_pDynamicPath, &original_pHintRoom);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_pHintRoom, original_pHintRoom, "Comparing pHintRoom");
			}
		}

		SUBCASE("Missile without room")
		{
			for (auto i = 0; i < 8; ++i)
			{
				// Input data
				const auto tCurrentCoord = random_room_point();
				const auto nPathPoints = int32_t(random_unsigned_integer(1, 10));

				D2DynamicPathStrc moo_pDynamicPath{};
				D2ActiveRoomStrc moo_pHintRoom{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2ActiveRoomStrc original_pHintRoom{};

				const auto setup_data = [tCurrentCoord, nPathPoints](
					D2DynamicPathStrc& pDynamicPath,
					D2ActiveRoomStrc& pHintRoom
				) {
					// Hint room that doesn't contain the current position
					pHintRoom.tCoords.nSubtileX = ROOM_X + ROOM_SIZE;
					pHintRoom.tCoords.nSubtileY = ROOM_Y;
					pHintRoom.tCoords.nSubtileWidth = ROOM_SIZE;
					pHintRoom.tCoords.nSubtileHeight = ROOM_SIZE;

					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(tCurrentCoord.X);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(tCurrentCoord.Y);
					pDynamicPath.dwFlags = PATH_MISSILE_MASK;
					pDynamicPath.dwPathPoints = nPathPoints;
				};

				setup_data(moo_pDynamicPath, moo_pHintRoom);
				setup_data(original_pDynamicPath, original_pHintRoom);

				// Call both implementations
				sut(&moo_pDynamicPath, &moo_pHintRoom);
				original(&original_pDynamicPath, &original_pHintRoom);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_pHintRoom, original_pHintRoom, "Comparing pHintRoom");
			}
		}
	}
}
