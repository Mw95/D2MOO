#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Collision.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Path/Step.h>
#include <Units/Units.h>


DYNAMIC_ARRAY_TYPE(uint16_t)


TEST_SUITE("StepTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAC5E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_GetDirectionVector, dll_base + 0x0006C5E0);
		
		SUBCASE("Random start and target")
		{
			for (auto i = 0; i < 128; ++i)
			{
				// Input data
				// Coordinates are limited so that the tangent computation (127 * delta) does not overflow
				D2CoordStrc moo_pDirectionVector{};
				int moo_pOutDirection{};
				D2CoordStrc original_pDirectionVector{};
				int original_pOutDirection{};
				DWORD dwStartPrecisionX = random_unsigned_integer(0, 0xFFFFFF);
				DWORD dwStartPrecisionY = random_unsigned_integer(0, 0xFFFFFF);
				DWORD dwTargetPrecisionX = random_unsigned_integer(0, 0xFFFFFF);
				DWORD dwTargetPrecisionY = random_unsigned_integer(0, 0xFFFFFF);

				// Call both implementations
				sut(&moo_pDirectionVector, &moo_pOutDirection, dwStartPrecisionX, dwStartPrecisionY, dwTargetPrecisionX, dwTargetPrecisionY);
				original(&original_pDirectionVector, &original_pOutDirection, dwStartPrecisionX, dwStartPrecisionY, dwTargetPrecisionX, dwTargetPrecisionY);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDirectionVector, original_pDirectionVector, "Comparing pDirectionVector");
				MOO_CHECK_EQ(moo_pOutDirection, original_pOutDirection, "Comparing pOutDirection");
			}
		}

		SUBCASE("Same start and target")
		{
			// Input data
			D2CoordStrc moo_pDirectionVector{};
			int moo_pOutDirection{};
			D2CoordStrc original_pDirectionVector{};
			int original_pOutDirection{};
			DWORD dwStartPrecisionX = random_unsigned_integer();
			DWORD dwStartPrecisionY = random_unsigned_integer();
			DWORD dwTargetPrecisionX = dwStartPrecisionX;
			DWORD dwTargetPrecisionY = dwStartPrecisionY;

			// Call both implementations
			sut(&moo_pDirectionVector, &moo_pOutDirection, dwStartPrecisionX, dwStartPrecisionY, dwTargetPrecisionX, dwTargetPrecisionY);
			original(&original_pDirectionVector, &original_pOutDirection, dwStartPrecisionX, dwStartPrecisionY, dwTargetPrecisionX, dwTargetPrecisionY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDirectionVector, original_pDirectionVector, "Comparing pDirectionVector");
			MOO_CHECK_EQ(moo_pOutDirection, original_pOutDirection, "Comparing pOutDirection");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDACEC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDACEC0, dll_base + 0x0006CEC0);
		
		SUBCASE("No velocity")
		{
			// Input data
			const auto precision_x = random_unsigned_integer();
			const auto precision_y = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2FP32_16 moo_a2{};
			D2UnitStrc* moo_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2FP32_16 original_a2{};
			D2UnitStrc* original_pUnit{};

			const auto setup_data = [precision_x, precision_y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tGameCoords.dwPrecisionX = precision_x;
				pDynamicPath.tGameCoords.dwPrecisionY = precision_y;
				pDynamicPath.dwPathPoints = 5;
				pDynamicPath.dwCurrentPointIdx = 2;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_a2, &moo_pUnit);
			const auto original_result = original(&original_pDynamicPath, &original_a2, &original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			// pUnit is used to return the number of saved steps, so it must not be dereferenced
			MOO_CHECK_EQ(reinterpret_cast<uintptr_t&>(moo_pUnit), reinterpret_cast<uintptr_t&>(original_pUnit), "Comparing pUnit");
		}

		SUBCASE("Movement inside the current subtile")
		{
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				const auto x = random_unsigned_integer(0, 65535);
				const auto y = random_unsigned_integer(0, 65535);
				// Starting from the subtile center, a velocity below half a subtile never leaves the subtile
				const auto velocity_x = static_cast<int>(random_unsigned_integer(0, 0xFFFE)) - 0x7FFF;
				const auto velocity_y = static_cast<int>(random_unsigned_integer(0, 0xFFFE)) - 0x7FFF;

				D2DynamicPathStrc moo_pDynamicPath{};
				D2FP32_16 moo_a2{};
				D2UnitStrc* moo_pUnit{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2FP32_16 original_a2{};
				D2UnitStrc* original_pUnit{};

				const auto setup_data = [x, y, velocity_x, velocity_y](
					D2DynamicPathStrc& pDynamicPath
				) {
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(x);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(y);
					pDynamicPath.tVelocityVector.nX = velocity_x;
					pDynamicPath.tVelocityVector.nY = velocity_y;
					pDynamicPath.dwPathType = PATHTYPE_MISSILE;
				};

				setup_data(moo_pDynamicPath);
				setup_data(original_pDynamicPath);

				// Call both implementations
				const auto moo_result = sut(&moo_pDynamicPath, &moo_a2, &moo_pUnit);
				const auto original_result = original(&original_pDynamicPath, &original_a2, &original_pUnit);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
				// pUnit is used to return the number of saved steps, so it must not be dereferenced
				MOO_CHECK_EQ(reinterpret_cast<uintptr_t&>(moo_pUnit), reinterpret_cast<uintptr_t&>(original_pUnit), "Comparing pUnit");
			}
		}

		SUBCASE("Movement across subtiles")
		{
			for (const auto has_wall : { false, true })
			{
				// Input data
				D2DynamicPathStrc moo_pDynamicPath{};
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[16 * 16]{};
				D2FP32_16 moo_a2{};
				D2UnitStrc* moo_pUnit{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[16 * 16]{};
				D2FP32_16 original_a2{};
				D2UnitStrc* original_pUnit{};

				const auto setup_data = [has_wall](
					D2DynamicPathStrc& pDynamicPath,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(& pCollisionMask)[16 * 16]
				) {
					// 16x16 subtiles room starting at subtile (16, 16)
					pCollisionGrid.pRoomCoords.nSubtileX = 16;
					pCollisionGrid.pRoomCoords.nSubtileY = 16;
					pCollisionGrid.pRoomCoords.nSubtileWidth = 16;
					pCollisionGrid.pRoomCoords.nSubtileHeight = 16;
					pCollisionGrid.pCollisionMask = pCollisionMask;

					pRoom.tCoords = pCollisionGrid.pRoomCoords;
					pRoom.pCollisionGrid = &pCollisionGrid;

					if (has_wall)
					{
						// Wall on the path point
						pCollisionMask[(22 - 16) * 16 + (23 - 16)] = COLLIDE_WALL;
					}

					// Unit at subtile (20, 20) walking to the path point (23, 22), which is reachable within one step
					pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
					pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
					pDynamicPath.tVelocityVector.nX = 3 << 16;
					pDynamicPath.tVelocityVector.nY = 2 << 16;
					pDynamicPath.PathPoints[0] = { 23, 22 };
					pDynamicPath.dwPathPoints = 1;
					pDynamicPath.dwPathType = PATHTYPE_ASTAR;
					pDynamicPath.dwFlags = PATH_SAVE_STEPS_MASK;
					pDynamicPath.nDist = 10;
					pDynamicPath.pRoom = &pRoom;
					pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
					pDynamicPath.nFootprintCollisionMask = COLLIDE_PLAYER;
					pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_PLAYER_PATH;
				};

				setup_data(moo_pDynamicPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pDynamicPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pDynamicPath, &moo_a2, &moo_pUnit);
				const auto original_result = original(&original_pDynamicPath, &original_a2, &original_pUnit);
				
				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
				MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
				// pUnit is used to return the number of saved steps, so it must not be dereferenced
				MOO_CHECK_EQ(reinterpret_cast<uintptr_t&>(moo_pUnit), reinterpret_cast<uintptr_t&>(original_pUnit), "Comparing pUnit");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, 16 * 16 }), (DynamicArray<uint16_t>{ original_pCollisionMask, 16 * 16 }), "Comparing pCollisionMask");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAD5E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAD5E0, dll_base + 0x0006D5E0);
		
		SUBCASE("Teleport")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pDestRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[16 * 16]{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pDestRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[16 * 16]{};
			D2PathPointStrc tDest{ 25, 27 };

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pDestRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(& pCollisionMask)[16 * 16]
			) {
				// 16x16 subtiles room starting at subtile (16, 16)
				pCollisionGrid.pRoomCoords.nSubtileX = 16;
				pCollisionGrid.pRoomCoords.nSubtileY = 16;
				pCollisionGrid.pRoomCoords.nSubtileWidth = 16;
				pCollisionGrid.pRoomCoords.nSubtileHeight = 16;
				pCollisionGrid.pCollisionMask = pCollisionMask;

				pDestRoom.tCoords = pCollisionGrid.pRoomCoords;
				pDestRoom.pCollisionGrid = &pCollisionGrid;

				pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
				pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
				pDynamicPath.tVelocityVector.nX = 1 << 16;
				pDynamicPath.tVelocityVector.nY = 1 << 16;
				pDynamicPath.dwPathPoints = 3;
				pDynamicPath.dwCurrentPointIdx = 1;
				pDynamicPath.dwFlags = PATH_UNKNOWN_FLAG_0x00020;
				pDynamicPath.pRoom = &pDestRoom;
				pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
				pDynamicPath.nFootprintCollisionMask = COLLIDE_PLAYER;
			};

			setup_data(moo_pDynamicPath, moo_pDestRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pDynamicPath, original_pDestRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_pDestRoom, tDest);
			const auto original_result = original(&original_pDynamicPath, &original_pDestRoom, tDest);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_pDestRoom, original_pDestRoom, "Comparing pDestRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, 16 * 16 }), (DynamicArray<uint16_t>{ original_pCollisionMask, 16 * 16 }), "Comparing pCollisionMask");
		}

		SUBCASE("Teleport to (0, 0) resets collision")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pDestRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[16 * 16]{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pDestRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[16 * 16]{};
			D2PathPointStrc tDest{ 0, 0 };

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pDestRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(& pCollisionMask)[16 * 16]
			) {
				// 16x16 subtiles room starting at subtile (16, 16)
				pCollisionGrid.pRoomCoords.nSubtileX = 16;
				pCollisionGrid.pRoomCoords.nSubtileY = 16;
				pCollisionGrid.pRoomCoords.nSubtileWidth = 16;
				pCollisionGrid.pRoomCoords.nSubtileHeight = 16;
				pCollisionGrid.pCollisionMask = pCollisionMask;

				pDestRoom.tCoords = pCollisionGrid.pRoomCoords;
				pDestRoom.pCollisionGrid = &pCollisionGrid;

				// Footprint of the unit at subtile (20, 20)
				pCollisionMask[(20 - 16) * 16 + (20 - 16)] = COLLIDE_PLAYER | COLLIDE_NO_PATH;
				pCollisionMask[(20 - 16) * 16 + (19 - 16)] = COLLIDE_PLAYER;
				pCollisionMask[(20 - 16) * 16 + (21 - 16)] = COLLIDE_PLAYER;
				pCollisionMask[(19 - 16) * 16 + (20 - 16)] = COLLIDE_PLAYER;
				pCollisionMask[(21 - 16) * 16 + (20 - 16)] = COLLIDE_PLAYER;

				pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
				pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
				pDynamicPath.pRoom = &pDestRoom;
				pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
				pDynamicPath.nFootprintCollisionMask = COLLIDE_PLAYER;
			};

			setup_data(moo_pDynamicPath, moo_pDestRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pDynamicPath, original_pDestRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_pDestRoom, tDest);
			const auto original_result = original(&original_pDynamicPath, &original_pDestRoom, tDest);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_pDestRoom, original_pDestRoom, "Comparing pDestRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, 16 * 16 }), (DynamicArray<uint16_t>{ original_pCollisionMask, 16 * 16 }), "Comparing pCollisionMask");
		}

		SUBCASE("Teleport missile")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pDestRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[16 * 16]{};
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pDestRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[16 * 16]{};
			D2UnitStrc original_pUnit{};
			D2PathPointStrc tDest{ 25, 27 };

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pDestRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(& pCollisionMask)[16 * 16],
				D2UnitStrc& pUnit
			) {
				// 16x16 subtiles room starting at subtile (16, 16)
				pCollisionGrid.pRoomCoords.nSubtileX = 16;
				pCollisionGrid.pRoomCoords.nSubtileY = 16;
				pCollisionGrid.pRoomCoords.nSubtileWidth = 16;
				pCollisionGrid.pRoomCoords.nSubtileHeight = 16;
				pCollisionGrid.pCollisionMask = pCollisionMask;

				pDestRoom.tCoords = pCollisionGrid.pRoomCoords;
				pDestRoom.pCollisionGrid = &pCollisionGrid;

				// A monster stands at the destination
				pCollisionMask[(27 - 16) * 16 + (25 - 16)] = COLLIDE_MONSTER;

				pUnit.dwUnitType = UNIT_MISSILE;

				pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
				pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
				pDynamicPath.pUnit = &pUnit;
				pDynamicPath.pRoom = &pDestRoom;
				pDynamicPath.dwFlags = PATH_MISSILE_MASK;
				pDynamicPath.dwUnitSize = COLLISION_UNIT_SIZE_SMALL;
				pDynamicPath.nFootprintCollisionMask = COLLIDE_MISSILE;
				pDynamicPath.nMoveTestCollisionMask = COLLIDE_MASK_MONSTER_MISSILE;
			};

			setup_data(moo_pDynamicPath, moo_pDestRoom, moo_pCollisionGrid, moo_pCollisionMask, moo_pUnit);
			setup_data(original_pDynamicPath, original_pDestRoom, original_pCollisionGrid, original_pCollisionMask, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_pDestRoom, tDest);
			const auto original_result = original(&original_pDynamicPath, &original_pDestRoom, tDest);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_pDestRoom, original_pDestRoom, "Comparing pDestRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, 16 * 16 }), (DynamicArray<uint16_t>{ original_pCollisionMask, 16 * 16 }), "Comparing pCollisionMask");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAE250")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATHMISC_SetRoom, dll_base + 0x0006E250);
		
		SUBCASE("Unit without a room")
		{
			// Input data
			D2DynamicPathStrc moo_pPath{};
			D2ActiveRoomStrc moo_pNewRoom{};
			D2UnitStrc moo_pUnit{};
			D2DrlgActStrc moo_pAct{};
			D2DynamicPathStrc original_pPath{};
			D2ActiveRoomStrc original_pNewRoom{};
			D2UnitStrc original_pUnit{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [](
				D2DynamicPathStrc& pPath,
				D2ActiveRoomStrc& pNewRoom,
				D2UnitStrc& pUnit,
				D2DrlgActStrc& pAct
			) {
				// 16x16 subtiles room starting at subtile (16, 16)
				pNewRoom.tCoords.nSubtileX = 16;
				pNewRoom.tCoords.nSubtileY = 16;
				pNewRoom.tCoords.nSubtileWidth = 16;
				pNewRoom.tCoords.nSubtileHeight = 16;
				pNewRoom.pAct = &pAct;

				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pPath;

				pPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
				pPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
				pPath.pUnit = &pUnit;
			};

			setup_data(moo_pPath, moo_pNewRoom, moo_pUnit, moo_pAct);
			setup_data(original_pPath, original_pNewRoom, original_pUnit, original_pAct);

			// Call both implementations
			sut(&moo_pPath, &moo_pNewRoom);
			original(&original_pPath, &original_pNewRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPath, original_pPath, "Comparing pPath");
			MOO_CHECK_EQ(moo_pNewRoom, original_pNewRoom, "Comparing pNewRoom");
		}

		SUBCASE("Unit moving from another room")
		{
			// Input data
			D2DynamicPathStrc moo_pPath{};
			D2ActiveRoomStrc moo_pNewRoom{};
			D2ActiveRoomStrc moo_pOldRoom{};
			D2UnitStrc moo_pUnit{};
			D2DrlgActStrc moo_pAct{};
			D2DynamicPathStrc original_pPath{};
			D2ActiveRoomStrc original_pNewRoom{};
			D2ActiveRoomStrc original_pOldRoom{};
			D2UnitStrc original_pUnit{};
			D2DrlgActStrc original_pAct{};

			const auto setup_data = [](
				D2DynamicPathStrc& pPath,
				D2ActiveRoomStrc& pNewRoom,
				D2ActiveRoomStrc& pOldRoom,
				D2UnitStrc& pUnit,
				D2DrlgActStrc& pAct
			) {
				// 16x16 subtiles room starting at subtile (0, 16), the unit is still registered in it
				pOldRoom.tCoords.nSubtileX = 0;
				pOldRoom.tCoords.nSubtileY = 16;
				pOldRoom.tCoords.nSubtileWidth = 16;
				pOldRoom.tCoords.nSubtileHeight = 16;
				pOldRoom.pUnitFirst = &pUnit;
				pOldRoom.nAllies = 1;

				// 16x16 subtiles room starting at subtile (16, 16)
				pNewRoom.tCoords.nSubtileX = 16;
				pNewRoom.tCoords.nSubtileY = 16;
				pNewRoom.tCoords.nSubtileWidth = 16;
				pNewRoom.tCoords.nSubtileHeight = 16;
				pNewRoom.pAct = &pAct;

				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pPath;

				// The unit has already moved into the new room
				pPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
				pPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
				pPath.pUnit = &pUnit;
				pPath.pRoom = &pOldRoom;
			};

			setup_data(moo_pPath, moo_pNewRoom, moo_pOldRoom, moo_pUnit, moo_pAct);
			setup_data(original_pPath, original_pNewRoom, original_pOldRoom, original_pUnit, original_pAct);

			// Call both implementations
			sut(&moo_pPath, &moo_pNewRoom);
			original(&original_pPath, &original_pNewRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPath, original_pPath, "Comparing pPath");
			MOO_CHECK_EQ(moo_pNewRoom, original_pNewRoom, "Comparing pNewRoom");
			MOO_CHECK_EQ(moo_pOldRoom, original_pOldRoom, "Comparing pOldRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDADF00 (#10230)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10230, dll_base + 0x0006DF00);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[16 * 16]{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[16 * 16]{};
			int a2 = random_unsigned_integer();
			unsigned int a4 = 25;
			__int16 a5 = 27;

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(& pCollisionMask)[16 * 16]
			) {
				// 16x16 subtiles room starting at subtile (16, 16)
				pCollisionGrid.pRoomCoords.nSubtileX = 16;
				pCollisionGrid.pRoomCoords.nSubtileY = 16;
				pCollisionGrid.pRoomCoords.nSubtileWidth = 16;
				pCollisionGrid.pRoomCoords.nSubtileHeight = 16;
				pCollisionGrid.pCollisionMask = pCollisionMask;

				pRoom.tCoords = pCollisionGrid.pRoomCoords;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
				pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
				pDynamicPath.tVelocityVector.nX = 1 << 16;
				pDynamicPath.tVelocityVector.nY = 1 << 16;
				pDynamicPath.dwPathPoints = 3;
				pDynamicPath.pRoom = &pRoom;
				pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
				pDynamicPath.nFootprintCollisionMask = COLLIDE_PLAYER;
			};

			setup_data(moo_pDynamicPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pDynamicPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, a2, &moo_pRoom, a4, a5);
			const auto original_result = original(&original_pDynamicPath, a2, &original_pRoom, a4, a5);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, 16 * 16 }), (DynamicArray<uint16_t>{ original_pCollisionMask, 16 * 16 }), "Comparing pCollisionMask");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDADC20 (#10231)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10231, dll_base + 0x0006DC20);
		
		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pUnit_unused{};
			D2ActiveRoomStrc moo_pRooms{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[16 * 16]{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pUnit_unused{};
			D2ActiveRoomStrc original_pRooms{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[16 * 16]{};
			uint16_t nX = random_unsigned_integer(0, 65535);
			uint16_t nY = random_unsigned_integer(0, 65535);

			const auto setup_data = [](
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRooms,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(& pCollisionMask)[16 * 16]
			) {
				// 16x16 subtiles room starting at subtile (16, 16)
				pCollisionGrid.pRoomCoords.nSubtileX = 16;
				pCollisionGrid.pRoomCoords.nSubtileY = 16;
				pCollisionGrid.pRoomCoords.nSubtileWidth = 16;
				pCollisionGrid.pRoomCoords.nSubtileHeight = 16;
				pCollisionGrid.pCollisionMask = pCollisionMask;

				pRooms.tCoords = pCollisionGrid.pRoomCoords;
				pRooms.pCollisionGrid = &pCollisionGrid;

				pDynamicPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
				pDynamicPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
				pDynamicPath.tVelocityVector.nX = 1 << 16;
				pDynamicPath.tVelocityVector.nY = 1 << 16;
				pDynamicPath.dwPathPoints = 3;
				pDynamicPath.dwCurrentPointIdx = 1;
				pDynamicPath.pRoom = &pRooms;
				pDynamicPath.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
				pDynamicPath.nFootprintCollisionMask = COLLIDE_PLAYER;
			};

			setup_data(moo_pDynamicPath, moo_pRooms, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pDynamicPath, original_pRooms, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pDynamicPath, &moo_pUnit_unused, &moo_pRooms, nX, nY);
			const auto original_result = original(&original_pDynamicPath, &original_pUnit_unused, &original_pRooms, nX, nY);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
			MOO_CHECK_EQ(moo_pUnit_unused, original_pUnit_unused, "Comparing pUnit_unused");
			MOO_CHECK_EQ(moo_pRooms, original_pRooms, "Comparing pRooms");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, 16 * 16 }), (DynamicArray<uint16_t>{ original_pCollisionMask, 16 * 16 }), "Comparing pCollisionMask");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDADF50 (#10232)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10232, dll_base + 0x0006DF50);
		
		const auto is_target_blocked = GENERATE(false, true);

		SUBCASE("")
		{
			// Input data
			D2DynamicPathStrc moo_pPath{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pDestRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[16 * 16]{};
			D2DynamicPathStrc original_pPath{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pDestRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[16 * 16]{};
			int nTargetX = 25;
			int nTargetY = 27;

			const auto setup_data = [is_target_blocked](
				D2DynamicPathStrc& pPath,
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pDestRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(& pCollisionMask)[16 * 16]
			) {
				// 16x16 subtiles room starting at subtile (16, 16)
				pCollisionGrid.pRoomCoords.nSubtileX = 16;
				pCollisionGrid.pRoomCoords.nSubtileY = 16;
				pCollisionGrid.pRoomCoords.nSubtileWidth = 16;
				pCollisionGrid.pRoomCoords.nSubtileHeight = 16;
				pCollisionGrid.pCollisionMask = pCollisionMask;

				pDestRoom.tCoords = pCollisionGrid.pRoomCoords;
				pDestRoom.pCollisionGrid = &pCollisionGrid;

				if (is_target_blocked)
				{
					pCollisionMask[(27 - 16) * 16 + (25 - 16)] = COLLIDE_WALL;
				}

				pUnit.dwUnitType = UNIT_PLAYER;

				pPath.tGameCoords.dwPrecisionX = PATH_ToFP16Center(20);
				pPath.tGameCoords.dwPrecisionY = PATH_ToFP16Center(20);
				pPath.tVelocityVector.nX = 1 << 16;
				pPath.tVelocityVector.nY = 1 << 16;
				pPath.dwPathPoints = 3;
				pPath.dwCurrentPointIdx = 1;
				pPath.pRoom = &pDestRoom;
				pPath.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;
				pPath.nFootprintCollisionMask = COLLIDE_PLAYER;
				pPath.nMoveTestCollisionMask = COLLIDE_MASK_PLAYER_PATH;
			};

			setup_data(moo_pPath, moo_pUnit, moo_pDestRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pPath, original_pUnit, original_pDestRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pPath, &moo_pUnit, &moo_pDestRoom, nTargetX, nTargetY);
			const auto original_result = original(&original_pPath, &original_pUnit, &original_pDestRoom, nTargetX, nTargetY);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPath, original_pPath, "Comparing pPath");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pDestRoom, original_pDestRoom, "Comparing pDestRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, 16 * 16 }), (DynamicArray<uint16_t>{ original_pCollisionMask, 16 * 16 }), "Comparing pCollisionMask");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAE290 (#10233)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PATH_RecacheRoomIfNeeded, dll_base + 0x0006E290);
		
		SUBCASE("Unit path")
		{
			// Input data
			const auto precision_x = random_unsigned_integer();
			const auto precision_y = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [precision_x, precision_y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tGameCoords.dwPrecisionX = precision_x;
				pDynamicPath.tGameCoords.dwPrecisionY = precision_y;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}

		SUBCASE("Missile path outside of any room")
		{
			// Input data
			const auto precision_x = random_unsigned_integer();
			const auto precision_y = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [precision_x, precision_y](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.tGameCoords.dwPrecisionX = precision_x;
				pDynamicPath.tGameCoords.dwPrecisionY = precision_y;
				pDynamicPath.dwFlags = PATH_MISSILE_MASK;
				pDynamicPath.dwPathPoints = 3;
			};

			setup_data(moo_pDynamicPath);
			setup_data(original_pDynamicPath);

			// Call both implementations
			sut(&moo_pDynamicPath);
			original(&original_pDynamicPath);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDynamicPath, original_pDynamicPath, "Comparing pDynamicPath");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAE500 (#10234)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10234, dll_base + 0x0006E500);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2DynamicPathStrc moo_pDynamicPath{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [flags](
				D2DynamicPathStrc& pDynamicPath
			) {
				pDynamicPath.dwFlags = flags;
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAE520 (#10235)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10235_PATH_UpdateRiderPath, dll_base + 0x0006E520);
		
		const auto same_position = GENERATE(false, true);

		SUBCASE("")
		{
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				const auto rider_precision_x = random_unsigned_integer();
				const auto rider_precision_y = random_unsigned_integer();
				const auto mount_precision_x = same_position ? rider_precision_x : random_unsigned_integer();
				const auto mount_precision_y = same_position ? rider_precision_y : random_unsigned_integer();
				const auto rider_flags = random_unsigned_integer();

				D2UnitStrc moo_pRiderUnit{};
				D2UnitStrc moo_pMountUnit{};
				D2DynamicPathStrc moo_pRiderPath{};
				D2DynamicPathStrc moo_pMountPath{};
				D2UnitStrc original_pRiderUnit{};
				D2UnitStrc original_pMountUnit{};
				D2DynamicPathStrc original_pRiderPath{};
				D2DynamicPathStrc original_pMountPath{};

				const auto setup_data = [rider_precision_x, rider_precision_y, mount_precision_x, mount_precision_y, rider_flags](
					D2UnitStrc& pRiderUnit,
					D2UnitStrc& pMountUnit,
					D2DynamicPathStrc& pRiderPath,
					D2DynamicPathStrc& pMountPath
				) {
					pRiderPath.tGameCoords.dwPrecisionX = rider_precision_x;
					pRiderPath.tGameCoords.dwPrecisionY = rider_precision_y;
					pRiderPath.dwFlags = rider_flags;
					pRiderPath.dwPathPoints = 3;

					pMountPath.tGameCoords.dwPrecisionX = mount_precision_x;
					pMountPath.tGameCoords.dwPrecisionY = mount_precision_y;

					pRiderUnit.dwUnitType = UNIT_MONSTER;
					pRiderUnit.pDynamicPath = &pRiderPath;

					pMountUnit.dwUnitType = UNIT_MONSTER;
					pMountUnit.pDynamicPath = &pMountPath;
				};

				setup_data(moo_pRiderUnit, moo_pMountUnit, moo_pRiderPath, moo_pMountPath);
				setup_data(original_pRiderUnit, original_pMountUnit, original_pRiderPath, original_pMountPath);

				// Call both implementations
				sut(&moo_pRiderUnit, &moo_pMountUnit);
				original(&original_pRiderUnit, &original_pMountUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRiderUnit, original_pRiderUnit, "Comparing pRiderUnit");
				MOO_CHECK_EQ(moo_pMountUnit, original_pMountUnit, "Comparing pMountUnit");
			}
		}
	}
}
