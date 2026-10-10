#include <D2CommonTestDefines.h>

#ifdef COLLISION_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2CMP.h>
#include <D2Collision.h>
#include <Drlg/D2DrlgDrlg.h>

// TODO: This has to be defined correctly
BEGIN_VISIT(D2TileLibraryEntryStrc)
END_VISIT()

DYNAMIC_ARRAY_TYPE(uint16_t)
DYNAMIC_ARRAY_TYPE(D2BoundingBoxStrc)


namespace
{
	// Subtile position and size of the room used by the tests
	constexpr int32_t room_x = 100;
	constexpr int32_t room_y = 200;
	constexpr int32_t room_size = 10;
	constexpr int32_t collision_mask_size = room_size * room_size;

	// The adjacent room is located right next to the room along the X axis
	constexpr int32_t adjacent_room_x = room_x + room_size;
	constexpr int32_t adjacent_room_y = room_y;

	// Repeated over the collision grids, the pattern size is coprime with the room size so that the rows differ
	constexpr uint16_t collision_mask_pattern[] = {
		COLLIDE_NONE,
		COLLIDE_WALL,
		COLLIDE_MONSTER,
		COLLIDE_NONE,
		COLLIDE_OBJECT | COLLIDE_DOOR,
		COLLIDE_PLAYER,
		COLLIDE_NONE,
		COLLIDE_MISSILE_BARRIER | COLLIDE_VISIBLE,
		COLLIDE_ITEM,
		COLLIDE_NO_PATH | COLLIDE_PET,
		COLLIDE_CORPSE,
	};
	constexpr int32_t collision_mask_pattern_size = sizeof(collision_mask_pattern) / sizeof(collision_mask_pattern[0]);

	struct SubtilePosition
	{
		int32_t nX;
		int32_t nY;
	};

	// Positions in the middle, on the edges and corners of the room, inside the adjacent room and outside of both rooms
	constexpr SubtilePosition test_positions[] = {
		{ room_x + 4, room_y + 5 },
		{ room_x, room_y },
		{ room_x + 9, room_y },
		{ room_x, room_y + 9 },
		{ room_x + 9, room_y + 9 },
		{ room_x, room_y + 4 },
		{ room_x + 9, room_y + 4 },
		{ room_x + 4, room_y },
		{ room_x + 4, room_y + 9 },
		{ adjacent_room_x, adjacent_room_y + 4 },
		{ adjacent_room_x + 4, adjacent_room_y + 5 },
		{ room_x - 1, room_y + 4 },
		{ room_x + 4, room_y - 1 },
		{ room_x + 4, room_y + 10 },
		{ adjacent_room_x + 10, adjacent_room_y + 4 },
	};
	constexpr int test_position_count = sizeof(test_positions) / sizeof(test_positions[0]);

	// Bounding boxes (nLeft, nBottom, nRight, nTop) fully contained in the room
	constexpr D2BoundingBoxStrc room_bounding_boxes[] = {
		{ room_x + 2, room_y + 3, room_x + 5, room_y + 7 },
		{ room_x + 6, room_y + 1, room_x + 6, room_y + 1 },
		{ room_x, room_y, room_x + room_size - 1, room_y + room_size - 1 },
	};

	// Bounding boxes (nLeft, nBottom, nRight, nTop) inside the room, crossing its edge towards the adjacent room,
	// crossing its top edge (where there is no room), crossing both edges and an empty one
	constexpr D2BoundingBoxStrc test_bounding_boxes[] = {
		{ room_x + 2, room_y + 3, room_x + 5, room_y + 7 },
		{ room_x + 8, room_y + 2, room_x + 12, room_y + 4 },
		{ room_x + 3, room_y + 8, room_x + 5, room_y + 11 },
		{ room_x + 8, room_y + 8, room_x + 11, room_y + 11 },
		{ room_x + 5, room_y + 5, room_x + 4, room_y + 6 },
	};

	void setup_coordinates(D2DrlgCoordsStrc& tCoords, int32_t nSubtileX, int32_t nSubtileY)
	{
		tCoords.nSubtileX = nSubtileX;
		tCoords.nSubtileY = nSubtileY;
		tCoords.nSubtileWidth = room_size;
		tCoords.nSubtileHeight = room_size;

		// A tile is made of 5x5 subtiles
		tCoords.nTileXPos = nSubtileX / 5;
		tCoords.nTileYPos = nSubtileY / 5;
		tCoords.nTileWidth = room_size / 5;
		tCoords.nTileHeight = room_size / 5;
	}

	void setup_collision_grid(D2RoomCollisionGridStrc& pCollisionGrid, uint16_t(&pCollisionMask)[collision_mask_size], int32_t nSubtileX, int32_t nSubtileY, uint16_t nAdditionalMask = COLLIDE_NONE)
	{
		setup_coordinates(pCollisionGrid.pRoomCoords, nSubtileX, nSubtileY);

		for (int32_t i = 0; i < collision_mask_size; ++i)
		{
			pCollisionMask[i] = static_cast<uint16_t>(collision_mask_pattern[(nSubtileX + i) % collision_mask_pattern_size] | nAdditionalMask);
		}
		pCollisionGrid.pCollisionMask = pCollisionMask;
	}

	void setup_room(D2ActiveRoomStrc& pRoom, D2RoomCollisionGridStrc& pCollisionGrid, uint16_t(&pCollisionMask)[collision_mask_size], int32_t nSubtileX, int32_t nSubtileY, uint16_t nAdditionalMask = COLLIDE_NONE)
	{
		setup_collision_grid(pCollisionGrid, pCollisionMask, nSubtileX, nSubtileY, nAdditionalMask);

		pRoom.tCoords = pCollisionGrid.pRoomCoords;
		pRoom.pCollisionGrid = &pCollisionGrid;
	}

	void set_adjacent_room(D2ActiveRoomStrc& pRoom, D2ActiveRoomStrc*& pRoomList, D2ActiveRoomStrc& pAdjacentRoom)
	{
		pRoomList = &pAdjacentRoom;
		pRoom.ppRoomList = &pRoomList;
		pRoom.nNumRooms = 1;
	}
}


TEST_SUITE("D2CollisionTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD41000")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_COLLISION_FirstFn_6FD41000, dll_base + 0x00001000);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgTileDataStrc moo_pTileData{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgTileDataStrc original_pTileData{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2DrlgTileDataStrc& pTileData,
				D2TileLibraryEntryStrc& pTileLibraryEntry,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);

				pTileLibraryEntry.dwTileFlags[0] = COLLIDE_WALL;
				pTileLibraryEntry.dwTileFlags[1] = COLLIDE_VISIBLE | COLLIDE_MISSILE_BARRIER;
				pTileLibraryEntry.dwTileFlags[2] = COLLIDE_PRESET;
				pTileLibraryEntry.dwTileFlags[3] = COLLIDE_WALL | COLLIDE_PRESET;

				// Second tile of the first tile row of the room, i.e. at subtile (5, 0) of the collision grid
				pTileData.nPosX = 1;
				pTileData.nPosY = 0;
				pTileData.pTile = &pTileLibraryEntry;
			};

			setup_data(moo_pRoom, moo_pTileData, moo_pTileLibraryEntry, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pTileData, original_pTileLibraryEntry, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			sut(&moo_pRoom, &moo_pTileData, &moo_pTileLibraryEntry);
			original(&original_pRoom, &original_pTileData, &original_pTileLibraryEntry);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
			MOO_CHECK_EQ(moo_pTileLibraryEntry, original_pTileLibraryEntry, "Comparing pTileLibraryEntry");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD411F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD411F0, dll_base + 0x000011F0);

		SUBCASE("")
		{
			// Input data
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};
			uint16_t original_pCollisionMask[collision_mask_size]{};

			// The tile covers 5x5 subtiles, which have to be inside of the collision grid
			const int nX = 5;
			const int nY = 3;

			const auto setup_data = [](
				D2RoomCollisionGridStrc& pCollisionGrid,
				D2TileLibraryEntryStrc& pTileLibraryEntry,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_collision_grid(pCollisionGrid, pCollisionMask, room_x, room_y);

				pTileLibraryEntry.dwTileFlags[0] = COLLIDE_WALL;
				pTileLibraryEntry.dwTileFlags[1] = COLLIDE_VISIBLE | COLLIDE_MISSILE_BARRIER;
				pTileLibraryEntry.dwTileFlags[2] = COLLIDE_PRESET;
				pTileLibraryEntry.dwTileFlags[3] = COLLIDE_WALL | COLLIDE_PRESET;
			};

			setup_data(moo_pCollisionGrid, moo_pTileLibraryEntry, moo_pCollisionMask);
			setup_data(original_pCollisionGrid, original_pTileLibraryEntry, original_pCollisionMask);

			// Call both implementations
			sut(&moo_pCollisionGrid, &moo_pTileLibraryEntry, nX, nY);
			original(&original_pCollisionGrid, &original_pTileLibraryEntry, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pCollisionGrid, original_pCollisionGrid, "Comparing pCollisionGrid");
			MOO_CHECK_EQ(moo_pTileLibraryEntry, original_pTileLibraryEntry, "Comparing pTileLibraryEntry");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD412B0 (#10018)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10018_Return0, dll_base + 0x000012B0);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD412C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_AllocRoomCollisionGrid, dll_base + 0x000012C0);
		const auto [free_sut, free_original] = make_function_pair(COLLISION_FreeRoomCollisionGrid, dll_base + 0x00001610);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc* moo_pRoomList{};
			D2DrlgRoomTilesStrc moo_pRoomTiles{};
			D2DrlgTileDataStrc moo_pFloorTile{};
			D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
			D2ActiveRoomStrc original_pRoom{};
			D2ActiveRoomStrc* original_pRoomList{};
			D2DrlgRoomTilesStrc original_pRoomTiles{};
			D2DrlgTileDataStrc original_pFloorTile{};
			D2TileLibraryEntryStrc original_pTileLibraryEntry{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2ActiveRoomStrc*& pRoomList,
				D2DrlgRoomTilesStrc& pRoomTiles,
				D2DrlgTileDataStrc& pFloorTile,
				D2TileLibraryEntryStrc& pTileLibraryEntry
			) {
				setup_coordinates(pRoom.tCoords, room_x, room_y);

				// The tiles of the adjacent rooms (including the room itself) are applied to the new collision grid
				set_adjacent_room(pRoom, pRoomList, pRoom);

				pTileLibraryEntry.dwTileFlags[0] = COLLIDE_WALL;
				pTileLibraryEntry.dwTileFlags[1] = COLLIDE_VISIBLE | COLLIDE_MISSILE_BARRIER;
				pTileLibraryEntry.dwTileFlags[2] = COLLIDE_PRESET;
				pTileLibraryEntry.dwTileFlags[3] = COLLIDE_WALL | COLLIDE_PRESET;

				// A single floor tile located at the second tile row and column of the room, flagged as wall
				pFloorTile.nPosX = 1;
				pFloorTile.nPosY = 1;
				pFloorTile.dwFlags = 0x40;
				pFloorTile.pTile = &pTileLibraryEntry;

				pRoomTiles.pFloorTiles = &pFloorTile;
				pRoomTiles.nFloors = 1;
				pRoom.pRoomTiles = &pRoomTiles;
			};

			setup_data(moo_pRoom, moo_pRoomList, moo_pRoomTiles, moo_pFloorTile, moo_pTileLibraryEntry);
			setup_data(original_pRoom, original_pRoomList, original_pRoomTiles, original_pFloorTile, original_pTileLibraryEntry);

			// Call both implementations
			sut(nullptr, &moo_pRoom);
			original(nullptr, &original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			REQUIRE(moo_pRoom.pCollisionGrid != nullptr);
			REQUIRE(original_pRoom.pCollisionGrid != nullptr);
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pRoom.pCollisionGrid->pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pRoom.pCollisionGrid->pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");

			// Release the allocated collision grids
			free_sut(nullptr, &moo_pRoom);
			free_original(nullptr, &original_pRoom);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD413E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD413E0, dll_base + 0x000013E0);

		SUBCASE("")
		{
			for (const BOOL bRemoveOldFlags : { FALSE, TRUE })
			{
				CAPTURE(bRemoveOldFlags);

				// Input data
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2RoomCollisionGridStrc moo_pAdjacentCollisionGrid{};
				D2DrlgTileDataStrc moo_pTiles{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2TileLibraryEntryStrc moo_pTileLibraryEntry{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				D2RoomCollisionGridStrc original_pAdjacentCollisionGrid{};
				D2DrlgTileDataStrc original_pTiles{};
				uint16_t original_pCollisionMask[collision_mask_size]{};
				D2TileLibraryEntryStrc original_pTileLibraryEntry{};
				const int nTiles = 1;

				const auto setup_data = [](
					D2RoomCollisionGridStrc& pCollisionGrid,
					D2RoomCollisionGridStrc& pAdjacentCollisionGrid,
					D2DrlgTileDataStrc& pTiles,
					uint16_t(&pCollisionMask)[collision_mask_size],
					D2TileLibraryEntryStrc& pTileLibraryEntry
				) {
					setup_collision_grid(pCollisionGrid, pCollisionMask, room_x, room_y);

					// The tile positions are relative to the adjacent room, which is located left of the room
					setup_coordinates(pAdjacentCollisionGrid.pRoomCoords, room_x - room_size, room_y);

					pTileLibraryEntry.dwTileFlags[0] = COLLIDE_WALL;
					pTileLibraryEntry.dwTileFlags[1] = COLLIDE_VISIBLE | COLLIDE_MISSILE_BARRIER;
					pTileLibraryEntry.dwTileFlags[2] = COLLIDE_PRESET;
					pTileLibraryEntry.dwTileFlags[3] = COLLIDE_WALL | COLLIDE_PRESET;

					// Located at subtile (0, 5) of the collision grid, flagged with all flags converted to collision masks
					pTiles.nPosX = 2;
					pTiles.nPosY = 1;
					pTiles.dwFlags = 0x02 | 0x40 | 0x80;
					pTiles.pTile = &pTileLibraryEntry;
				};

				setup_data(moo_pCollisionGrid, moo_pAdjacentCollisionGrid, moo_pTiles, moo_pCollisionMask, moo_pTileLibraryEntry);
				setup_data(original_pCollisionGrid, original_pAdjacentCollisionGrid, original_pTiles, original_pCollisionMask, original_pTileLibraryEntry);

				// Call both implementations
				sut(&moo_pCollisionGrid, &moo_pAdjacentCollisionGrid, &moo_pTiles, nTiles, bRemoveOldFlags);
				original(&original_pCollisionGrid, &original_pAdjacentCollisionGrid, &original_pTiles, nTiles, bRemoveOldFlags);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pCollisionGrid, original_pCollisionGrid, "Comparing pCollisionGrid");
				MOO_CHECK_EQ(moo_pAdjacentCollisionGrid, original_pAdjacentCollisionGrid, "Comparing pAdjacentCollisionGrid");
				MOO_CHECK_EQ(moo_pTiles, original_pTiles, "Comparing pTiles");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD41610")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_FreeRoomCollisionGrid, dll_base + 0x00001610);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom
			) {
				setup_coordinates(pRoom.tCoords, room_x, room_y);

				// The collision grid has to be allocated from the memory pool
				COLLISION_AllocRoomCollisionGrid(nullptr, &pRoom);
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			sut(nullptr, &moo_pRoom);
			original(nullptr, &original_pRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD41650 (#10118)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckMask, dll_base + 0x00001650);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};
			const uint16_t nMask = COLLIDE_MASK_PLACEMENT;

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			for (const auto& tPosition : test_positions)
			{
				const int nX = tPosition.nX;
				const int nY = tPosition.nY;
				CAPTURE(nX);
				CAPTURE(nY);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom, nX, nY, nMask);
				const auto original_result = original(&original_pRoom, nX, nY, nMask);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD41720 (#10127)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_SetMask, dll_base + 0x00001720);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			for (int i = 0; i < test_position_count; ++i)
			{
				const int nX = test_positions[i].nX;
				const int nY = test_positions[i].nY;
				// Use a different flag for each position, so that the modified subtiles can be told apart
				const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

				// Call both implementations
				sut(&moo_pRoom, nX, nY, nMask);
				original(&original_pRoom, nX, nY, nMask);
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD417F0 (#10123)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_ResetMask, dll_base + 0x000017F0);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_ALL_MASK);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			for (int i = 0; i < test_position_count; ++i)
			{
				const int nX = test_positions[i].nX;
				const int nY = test_positions[i].nY;
				// Use a different flag for each position, so that the modified subtiles can be told apart
				const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

				// Call both implementations
				sut(&moo_pRoom, nX, nY, nMask);
				original(&original_pRoom, nX, nY, nMask);
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD418C0 (#10120)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckMaskWithSizeXY, dll_base + 0x000018C0);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};
			const uint16_t nMask = COLLIDE_MASK_PLACEMENT;

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			for (const auto& tSize : { SubtilePosition{ 0, 0 }, SubtilePosition{ 1, 1 }, SubtilePosition{ 2, 3 }, SubtilePosition{ 3, 3 } })
			{
				for (const auto& tPosition : test_positions)
				{
					const int nX = tPosition.nX;
					const int nY = tPosition.nY;
					const unsigned int nSizeX = tSize.nX;
					const unsigned int nSizeY = tSize.nY;
					CAPTURE(nX);
					CAPTURE(nY);
					CAPTURE(nSizeX);
					CAPTURE(nSizeY);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX, nY, nSizeX, nSizeY, nMask);
					const auto original_result = original(&original_pRoom, nX, nY, nSizeX, nSizeY, nMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD41B40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckCollisionMaskForBoundingBox, dll_base + 0x00001B40);

		SUBCASE("")
		{
			for (const auto& tBoundingBox : room_bounding_boxes)
			{
				for (const uint16_t nMask : { COLLIDE_WALL, COLLIDE_MONSTER, COLLIDE_MASK_PLACEMENT, COLLIDE_ALL_MASK })
				{
					CAPTURE(tBoundingBox.nLeft);
					CAPTURE(tBoundingBox.nBottom);
					CAPTURE(tBoundingBox.nRight);
					CAPTURE(tBoundingBox.nTop);
					CAPTURE(nMask);

					// Input data
					D2RoomCollisionGridStrc moo_pCollisionGrid{};
					D2BoundingBoxStrc moo_pBoundingBox{};
					uint16_t moo_pCollisionMask[collision_mask_size]{};
					D2RoomCollisionGridStrc original_pCollisionGrid{};
					D2BoundingBoxStrc original_pBoundingBox{};
					uint16_t original_pCollisionMask[collision_mask_size]{};

					const auto setup_data = [&tBoundingBox](
						D2RoomCollisionGridStrc& pCollisionGrid,
						D2BoundingBoxStrc& pBoundingBox,
						uint16_t(&pCollisionMask)[collision_mask_size]
					) {
						setup_collision_grid(pCollisionGrid, pCollisionMask, room_x, room_y);
						pBoundingBox = tBoundingBox;
					};

					setup_data(moo_pCollisionGrid, moo_pBoundingBox, moo_pCollisionMask);
					setup_data(original_pCollisionGrid, original_pBoundingBox, original_pCollisionMask);

					// Call both implementations
					const auto moo_result = sut(&moo_pCollisionGrid, &moo_pBoundingBox, nMask);
					const auto original_result = original(&original_pCollisionGrid, &original_pBoundingBox, nMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pCollisionGrid, original_pCollisionGrid, "Comparing pCollisionGrid");
					MOO_CHECK_EQ(moo_pBoundingBox, original_pBoundingBox, "Comparing pBoundingBox");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD41BE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_AdaptBoundingBoxToGrid, dll_base + 0x00001BE0);

		SUBCASE("")
		{
			for (const auto& tBoundingBox : test_bounding_boxes)
			{
				CAPTURE(tBoundingBox.nLeft);
				CAPTURE(tBoundingBox.nBottom);
				CAPTURE(tBoundingBox.nRight);
				CAPTURE(tBoundingBox.nTop);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2BoundingBoxStrc moo_pBoundingBox{};
				// The bounding box is split into up to 3 bounding boxes
				D2BoundingBoxStrc moo_pBoundingBoxes[3]{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2ActiveRoomStrc original_pRoom{};
				D2BoundingBoxStrc original_pBoundingBox{};
				D2BoundingBoxStrc original_pBoundingBoxes[3]{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};

				const auto setup_data = [&tBoundingBox](
					D2ActiveRoomStrc& pRoom,
					D2BoundingBoxStrc& pBoundingBox,
					D2RoomCollisionGridStrc& pCollisionGrid
				) {
					// Only the coordinates of the collision grid are used
					setup_coordinates(pRoom.tCoords, room_x, room_y);
					pCollisionGrid.pRoomCoords = pRoom.tCoords;
					pRoom.pCollisionGrid = &pCollisionGrid;

					pBoundingBox = tBoundingBox;
				};

				setup_data(moo_pRoom, moo_pBoundingBox, moo_pCollisionGrid);
				setup_data(original_pRoom, original_pBoundingBox, original_pCollisionGrid);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom, &moo_pBoundingBox, moo_pBoundingBoxes);
				const auto original_result = original(&original_pRoom, &original_pBoundingBox, original_pBoundingBoxes);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_pBoundingBox, original_pBoundingBox, "Comparing pBoundingBox");
				MOO_CHECK_EQ((DynamicArray<D2BoundingBoxStrc>{ moo_pBoundingBoxes, 3 }), (DynamicArray<D2BoundingBoxStrc>{ original_pBoundingBoxes, 3 }), "Comparing pBoundingBoxes");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD41CA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckCollisionMaskForBoundingBoxRecursively, dll_base + 0x00001CA0);

		SUBCASE("")
		{
			for (const auto& tBoundingBox : test_bounding_boxes)
			{
				CAPTURE(tBoundingBox.nLeft);
				CAPTURE(tBoundingBox.nBottom);
				CAPTURE(tBoundingBox.nRight);
				CAPTURE(tBoundingBox.nTop);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2BoundingBoxStrc moo_pBoundingBox{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc* moo_pRoomList{};
				D2ActiveRoomStrc moo_pAdjacentRoom{};
				D2RoomCollisionGridStrc moo_pAdjacentCollisionGrid{};
				uint16_t moo_pAdjacentCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2BoundingBoxStrc original_pBoundingBox{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc* original_pRoomList{};
				D2ActiveRoomStrc original_pAdjacentRoom{};
				D2RoomCollisionGridStrc original_pAdjacentCollisionGrid{};
				uint16_t original_pAdjacentCollisionMask[collision_mask_size]{};
				const uint16_t nMask = COLLIDE_MASK_PLACEMENT;

				const auto setup_data = [&tBoundingBox](
					D2ActiveRoomStrc& pRoom,
					D2BoundingBoxStrc& pBoundingBox,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size],
					D2ActiveRoomStrc*& pRoomList,
					D2ActiveRoomStrc& pAdjacentRoom,
					D2RoomCollisionGridStrc& pAdjacentCollisionGrid,
					uint16_t(&pAdjacentCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
					setup_room(pAdjacentRoom, pAdjacentCollisionGrid, pAdjacentCollisionMask, adjacent_room_x, adjacent_room_y);
					set_adjacent_room(pRoom, pRoomList, pAdjacentRoom);

					pBoundingBox = tBoundingBox;
				};

				setup_data(moo_pRoom, moo_pBoundingBox, moo_pCollisionGrid, moo_pCollisionMask, moo_pRoomList, moo_pAdjacentRoom, moo_pAdjacentCollisionGrid, moo_pAdjacentCollisionMask);
				setup_data(original_pRoom, original_pBoundingBox, original_pCollisionGrid, original_pCollisionMask, original_pRoomList, original_pAdjacentRoom, original_pAdjacentCollisionGrid, original_pAdjacentCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom, &moo_pBoundingBox, nMask);
				const auto original_result = original(&original_pRoom, &original_pBoundingBox, nMask);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_pBoundingBox, original_pBoundingBox, "Comparing pBoundingBox");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD41DE0 (#10121)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckMaskWithPattern, dll_base + 0x00001DE0);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};
			const uint16_t nMask = COLLIDE_MASK_PLACEMENT;

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Includes an invalid collision pattern
			for (int nCollisionPattern = COLLISION_PATTERN_NONE; nCollisionPattern <= COLLISION_PATTERN_SMALL_NO_PRESENCE + 1; ++nCollisionPattern)
			{
				for (const auto& tPosition : test_positions)
				{
					const int nX = tPosition.nX;
					const int nY = tPosition.nY;
					CAPTURE(nX);
					CAPTURE(nY);
					CAPTURE(nCollisionPattern);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX, nY, nCollisionPattern, nMask);
					const auto original_result = original(&original_pRoom, nX, nY, nCollisionPattern, nMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD42000")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckCollisionMaskWithAdjacentCells, dll_base + 0x00002000);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc* moo_pRoomList{};
			D2ActiveRoomStrc moo_pAdjacentRoom{};
			D2RoomCollisionGridStrc moo_pAdjacentCollisionGrid{};
			uint16_t moo_pAdjacentCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc* moo_pAdjacentRoomList{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc* original_pRoomList{};
			D2ActiveRoomStrc original_pAdjacentRoom{};
			D2RoomCollisionGridStrc original_pAdjacentCollisionGrid{};
			uint16_t original_pAdjacentCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc* original_pAdjacentRoomList{};
			const uint16_t nMask = COLLIDE_MASK_PLACEMENT;

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size],
				D2ActiveRoomStrc*& pRoomList,
				D2ActiveRoomStrc& pAdjacentRoom,
				D2RoomCollisionGridStrc& pAdjacentCollisionGrid,
				uint16_t(&pAdjacentCollisionMask)[collision_mask_size],
				D2ActiveRoomStrc*& pAdjacentRoomList
			) {
				// Both rooms know each other, so that cells on the shared edge can be looked up from either room
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
				setup_room(pAdjacentRoom, pAdjacentCollisionGrid, pAdjacentCollisionMask, adjacent_room_x, adjacent_room_y);
				set_adjacent_room(pRoom, pRoomList, pAdjacentRoom);
				set_adjacent_room(pAdjacentRoom, pAdjacentRoomList, pRoom);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask, moo_pRoomList, moo_pAdjacentRoom, moo_pAdjacentCollisionGrid, moo_pAdjacentCollisionMask, moo_pAdjacentRoomList);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask, original_pRoomList, original_pAdjacentRoom, original_pAdjacentCollisionGrid, original_pAdjacentCollisionMask, original_pAdjacentRoomList);

			for (const auto& tPosition : test_positions)
			{
				const int nX = tPosition.nX;
				const int nY = tPosition.nY;
				CAPTURE(nX);
				CAPTURE(nY);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom, nX, nY, nMask);
				const auto original_result = original(&original_pRoom, nX, nY, nMask);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD42670")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckCollisionMask, dll_base + 0x00002670);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};
			const uint16_t nMask = COLLIDE_MASK_PLACEMENT;

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			for (const auto& tPosition : test_positions)
			{
				const int nX = tPosition.nX;
				const int nY = tPosition.nY;
				CAPTURE(nX);
				CAPTURE(nY);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom, nX, nY, nMask);
				const auto original_result = original(&original_pRoom, nX, nY, nMask);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD42740 (#10122)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckAnyCollisionWithPattern, dll_base + 0x00002740);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Includes an invalid collision pattern
			for (int nCollisionPattern = COLLISION_PATTERN_NONE; nCollisionPattern <= COLLISION_PATTERN_SMALL_NO_PRESENCE + 1; ++nCollisionPattern)
			{
				// A narrow mask leaves some areas without any collision
				for (const uint16_t nMask : { COLLIDE_WALL, COLLIDE_MASK_PLACEMENT })
				{
					for (const auto& tPosition : test_positions)
					{
						const int nX = tPosition.nX;
						const int nY = tPosition.nY;
						CAPTURE(nX);
						CAPTURE(nY);
						CAPTURE(nCollisionPattern);
						CAPTURE(nMask);

						// Call both implementations
						const auto moo_result = sut(&moo_pRoom, nX, nY, nCollisionPattern, nMask);
						const auto original_result = original(&original_pRoom, nX, nY, nCollisionPattern, nMask);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
					}
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD42A30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckAnyCollisionWithAdjacentCells, dll_base + 0x00002A30);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc* moo_pRoomList{};
			D2ActiveRoomStrc moo_pAdjacentRoom{};
			D2RoomCollisionGridStrc moo_pAdjacentCollisionGrid{};
			uint16_t moo_pAdjacentCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc* moo_pAdjacentRoomList{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc* original_pRoomList{};
			D2ActiveRoomStrc original_pAdjacentRoom{};
			D2RoomCollisionGridStrc original_pAdjacentCollisionGrid{};
			uint16_t original_pAdjacentCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc* original_pAdjacentRoomList{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size],
				D2ActiveRoomStrc*& pRoomList,
				D2ActiveRoomStrc& pAdjacentRoom,
				D2RoomCollisionGridStrc& pAdjacentCollisionGrid,
				uint16_t(&pAdjacentCollisionMask)[collision_mask_size],
				D2ActiveRoomStrc*& pAdjacentRoomList
			) {
				// Both rooms know each other, so that cells on the shared edge can be looked up from either room
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
				setup_room(pAdjacentRoom, pAdjacentCollisionGrid, pAdjacentCollisionMask, adjacent_room_x, adjacent_room_y);
				set_adjacent_room(pRoom, pRoomList, pAdjacentRoom);
				set_adjacent_room(pAdjacentRoom, pAdjacentRoomList, pRoom);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask, moo_pRoomList, moo_pAdjacentRoom, moo_pAdjacentCollisionGrid, moo_pAdjacentCollisionMask, moo_pAdjacentRoomList);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask, original_pRoomList, original_pAdjacentRoom, original_pAdjacentCollisionGrid, original_pAdjacentCollisionMask, original_pAdjacentRoomList);

			// A narrow mask leaves some areas without any collision
			for (const uint16_t nMask : { COLLIDE_WALL, COLLIDE_MASK_PLACEMENT })
			{
				for (const auto& tPosition : test_positions)
				{
					const int nX = tPosition.nX;
					const int nY = tPosition.nY;
					CAPTURE(nX);
					CAPTURE(nY);
					CAPTURE(nMask);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX, nY, nMask);
					const auto original_result = original(&original_pRoom, nX, nY, nMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD43080 (#10119)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CheckMaskWithSize, dll_base + 0x00003080);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};
			const uint16_t nMask = COLLIDE_MASK_PLACEMENT;

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Includes an invalid unit size
			for (int nUnitSize = COLLISION_UNIT_SIZE_NONE; nUnitSize <= COLLISION_UNIT_SIZE_COUNT; ++nUnitSize)
			{
				for (const auto& tPosition : test_positions)
				{
					const int nX = tPosition.nX;
					const int nY = tPosition.nY;
					CAPTURE(nX);
					CAPTURE(nY);
					CAPTURE(nUnitSize);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX, nY, nUnitSize, nMask);
					const auto original_result = original(&original_pRoom, nX, nY, nUnitSize, nMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD432A0 (#10128)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_SetMaskWithSize, dll_base + 0x000032A0);

		SUBCASE("")
		{
			// Includes an invalid unit size
			for (int nUnitSize = COLLISION_UNIT_SIZE_NONE; nUnitSize <= COLLISION_UNIT_SIZE_COUNT; ++nUnitSize)
			{
				CAPTURE(nUnitSize);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
				};

				setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				for (int i = 0; i < test_position_count; ++i)
				{
					const int nX = test_positions[i].nX;
					const int nY = test_positions[i].nY;
					// Use a different flag for each position, so that the modified subtiles can be told apart
					const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

					// Call both implementations
					sut(&moo_pRoom, nX, nY, nUnitSize, nMask);
					original(&original_pRoom, nX, nY, nUnitSize, nMask);
				}

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD434B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_SetCollisionMask, dll_base + 0x000034B0);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			for (int i = 0; i < test_position_count; ++i)
			{
				const int nX = test_positions[i].nX;
				const int nY = test_positions[i].nY;
				// Use a different flag for each position, so that the modified subtiles can be told apart
				const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

				// Call both implementations
				sut(&moo_pRoom, nX, nY, nMask);
				original(&original_pRoom, nX, nY, nMask);
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD43580")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_SetCollisionMaskForBoundingBoxRecursively, dll_base + 0x00003580);

		SUBCASE("")
		{
			for (const auto& tBoundingBox : test_bounding_boxes)
			{
				CAPTURE(tBoundingBox.nLeft);
				CAPTURE(tBoundingBox.nBottom);
				CAPTURE(tBoundingBox.nRight);
				CAPTURE(tBoundingBox.nTop);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2BoundingBoxStrc moo_pBoundingBox{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc* moo_pRoomList{};
				D2ActiveRoomStrc moo_pAdjacentRoom{};
				D2RoomCollisionGridStrc moo_pAdjacentCollisionGrid{};
				uint16_t moo_pAdjacentCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2BoundingBoxStrc original_pBoundingBox{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc* original_pRoomList{};
				D2ActiveRoomStrc original_pAdjacentRoom{};
				D2RoomCollisionGridStrc original_pAdjacentCollisionGrid{};
				uint16_t original_pAdjacentCollisionMask[collision_mask_size]{};
				const uint16_t nMask = COLLIDE_MONSTER | COLLIDE_PET;

				const auto setup_data = [&tBoundingBox](
					D2ActiveRoomStrc& pRoom,
					D2BoundingBoxStrc& pBoundingBox,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size],
					D2ActiveRoomStrc*& pRoomList,
					D2ActiveRoomStrc& pAdjacentRoom,
					D2RoomCollisionGridStrc& pAdjacentCollisionGrid,
					uint16_t(&pAdjacentCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
					setup_room(pAdjacentRoom, pAdjacentCollisionGrid, pAdjacentCollisionMask, adjacent_room_x, adjacent_room_y);
					set_adjacent_room(pRoom, pRoomList, pAdjacentRoom);

					pBoundingBox = tBoundingBox;
				};

				setup_data(moo_pRoom, moo_pBoundingBox, moo_pCollisionGrid, moo_pCollisionMask, moo_pRoomList, moo_pAdjacentRoom, moo_pAdjacentCollisionGrid, moo_pAdjacentCollisionMask);
				setup_data(original_pRoom, original_pBoundingBox, original_pCollisionGrid, original_pCollisionMask, original_pRoomList, original_pAdjacentRoom, original_pAdjacentCollisionGrid, original_pAdjacentCollisionMask);

				// Call both implementations
				sut(&moo_pRoom, &moo_pBoundingBox, nMask);
				original(&original_pRoom, &original_pBoundingBox, nMask);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_pBoundingBox, original_pBoundingBox, "Comparing pBoundingBox");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pAdjacentCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pAdjacentCollisionMask, collision_mask_size }), "Comparing pAdjacentCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD436F0 (#10130)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_SetMaskWithPattern, dll_base + 0x000036F0);

		SUBCASE("")
		{
			// Includes an invalid collision pattern
			for (int nCollisionPattern = COLLISION_PATTERN_NONE; nCollisionPattern <= COLLISION_PATTERN_SMALL_NO_PRESENCE + 1; ++nCollisionPattern)
			{
				CAPTURE(nCollisionPattern);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
				};

				setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				for (int i = 0; i < test_position_count; ++i)
				{
					const int nX = test_positions[i].nX;
					const int nY = test_positions[i].nY;
					// Use a different flag for each position, so that the modified subtiles can be told apart
					const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

					// Call both implementations
					sut(&moo_pRoom, nX, nY, nCollisionPattern, nMask);
					original(&original_pRoom, nX, nY, nCollisionPattern, nMask);
				}

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD439D0 (#10124)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_ResetMaskWithSize, dll_base + 0x000039D0);

		SUBCASE("")
		{
			// Includes an invalid unit size
			for (int nUnitSize = COLLISION_UNIT_SIZE_NONE; nUnitSize <= COLLISION_UNIT_SIZE_COUNT; ++nUnitSize)
			{
				CAPTURE(nUnitSize);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_ALL_MASK);
				};

				setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				for (int i = 0; i < test_position_count; ++i)
				{
					const int nX = test_positions[i].nX;
					const int nY = test_positions[i].nY;
					// Use a different flag for each position, so that the modified subtiles can be told apart
					const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

					// Call both implementations
					sut(&moo_pRoom, nX, nY, nUnitSize, nMask);
					original(&original_pRoom, nX, nY, nUnitSize, nMask);
				}

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD43C10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_ResetCollisionMask, dll_base + 0x00003C10);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[collision_mask_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[collision_mask_size]{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[collision_mask_size]
			) {
				setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_ALL_MASK);
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			for (int i = 0; i < test_position_count; ++i)
			{
				const int nX = test_positions[i].nX;
				const int nY = test_positions[i].nY;
				// Use a different flag for each position, so that the modified subtiles can be told apart
				const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

				// Call both implementations
				sut(&moo_pRoom, nX, nY, nMask);
				original(&original_pRoom, nX, nY, nMask);
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD43CE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_ResetCollisionMaskForBoundingBoxRecursively, dll_base + 0x00003CE0);

		SUBCASE("")
		{
			for (const auto& tBoundingBox : test_bounding_boxes)
			{
				CAPTURE(tBoundingBox.nLeft);
				CAPTURE(tBoundingBox.nBottom);
				CAPTURE(tBoundingBox.nRight);
				CAPTURE(tBoundingBox.nTop);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2BoundingBoxStrc moo_pBoundingBox{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc* moo_pRoomList{};
				D2ActiveRoomStrc moo_pAdjacentRoom{};
				D2RoomCollisionGridStrc moo_pAdjacentCollisionGrid{};
				uint16_t moo_pAdjacentCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2BoundingBoxStrc original_pBoundingBox{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc* original_pRoomList{};
				D2ActiveRoomStrc original_pAdjacentRoom{};
				D2RoomCollisionGridStrc original_pAdjacentCollisionGrid{};
				uint16_t original_pAdjacentCollisionMask[collision_mask_size]{};
				const uint16_t nMask = COLLIDE_WALL | COLLIDE_MONSTER | COLLIDE_PET;

				const auto setup_data = [&tBoundingBox](
					D2ActiveRoomStrc& pRoom,
					D2BoundingBoxStrc& pBoundingBox,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size],
					D2ActiveRoomStrc*& pRoomList,
					D2ActiveRoomStrc& pAdjacentRoom,
					D2RoomCollisionGridStrc& pAdjacentCollisionGrid,
					uint16_t(&pAdjacentCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_MONSTER);
					setup_room(pAdjacentRoom, pAdjacentCollisionGrid, pAdjacentCollisionMask, adjacent_room_x, adjacent_room_y, COLLIDE_MONSTER);
					set_adjacent_room(pRoom, pRoomList, pAdjacentRoom);

					pBoundingBox = tBoundingBox;
				};

				setup_data(moo_pRoom, moo_pBoundingBox, moo_pCollisionGrid, moo_pCollisionMask, moo_pRoomList, moo_pAdjacentRoom, moo_pAdjacentCollisionGrid, moo_pAdjacentCollisionMask);
				setup_data(original_pRoom, original_pBoundingBox, original_pCollisionGrid, original_pCollisionMask, original_pRoomList, original_pAdjacentRoom, original_pAdjacentCollisionGrid, original_pAdjacentCollisionMask);

				// Call both implementations
				sut(&moo_pRoom, &moo_pBoundingBox, nMask);
				original(&original_pRoom, &original_pBoundingBox, nMask);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ(moo_pBoundingBox, original_pBoundingBox, "Comparing pBoundingBox");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pAdjacentCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pAdjacentCollisionMask, collision_mask_size }), "Comparing pAdjacentCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD43E60 (#10126)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_ResetMaskWithPattern, dll_base + 0x00003E60);

		SUBCASE("")
		{
			// Includes an invalid collision pattern
			for (int nCollisionPattern = COLLISION_PATTERN_NONE; nCollisionPattern <= COLLISION_PATTERN_SMALL_NO_PRESENCE + 1; ++nCollisionPattern)
			{
				CAPTURE(nCollisionPattern);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_ALL_MASK);
				};

				setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				for (int i = 0; i < test_position_count; ++i)
				{
					const int nX = test_positions[i].nX;
					const int nY = test_positions[i].nY;
					// Use a different flag for each position, so that the modified subtiles can be told apart
					const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

					// Call both implementations
					sut(&moo_pRoom, nX, nY, nCollisionPattern, nMask);
					original(&original_pRoom, nX, nY, nCollisionPattern, nMask);
				}

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44140 (#10125)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_ResetMaskWithSizeXY, dll_base + 0x00004140);

		SUBCASE("")
		{
			for (const auto& tSize : { SubtilePosition{ 0, 0 }, SubtilePosition{ 1, 1 }, SubtilePosition{ 2, 3 }, SubtilePosition{ 3, 3 } })
			{
				const unsigned int nSizeX = tSize.nX;
				const unsigned int nSizeY = tSize.nY;
				CAPTURE(nSizeX);
				CAPTURE(nSizeY);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_ALL_MASK);
				};

				setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				for (int i = 0; i < test_position_count; ++i)
				{
					const int nX = test_positions[i].nX;
					const int nY = test_positions[i].nY;
					// Use a different flag for each position, so that the modified subtiles can be told apart
					const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

					// Call both implementations
					sut(&moo_pRoom, nX, nY, nSizeX, nSizeY, nMask);
					original(&original_pRoom, nX, nY, nSizeX, nSizeY, nMask);
				}

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44370")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_ResetCollisionMaskForBoundingBox, dll_base + 0x00004370);

		SUBCASE("")
		{
			for (const auto& tBoundingBox : room_bounding_boxes)
			{
				CAPTURE(tBoundingBox.nLeft);
				CAPTURE(tBoundingBox.nBottom);
				CAPTURE(tBoundingBox.nRight);
				CAPTURE(tBoundingBox.nTop);

				// Input data
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2BoundingBoxStrc moo_pBoundingBox{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				D2BoundingBoxStrc original_pBoundingBox{};
				uint16_t original_pCollisionMask[collision_mask_size]{};
				const uint16_t nMask = COLLIDE_WALL | COLLIDE_MONSTER | COLLIDE_PET;

				const auto setup_data = [&tBoundingBox](
					D2RoomCollisionGridStrc& pCollisionGrid,
					D2BoundingBoxStrc& pBoundingBox,
					uint16_t(&pCollisionMask)[collision_mask_size]
				) {
					setup_collision_grid(pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_MONSTER);
					pBoundingBox = tBoundingBox;
				};

				setup_data(moo_pCollisionGrid, moo_pBoundingBox, moo_pCollisionMask);
				setup_data(original_pCollisionGrid, original_pBoundingBox, original_pCollisionMask);

				// Call both implementations
				sut(&moo_pCollisionGrid, &moo_pBoundingBox, nMask);
				original(&original_pCollisionGrid, &original_pBoundingBox, nMask);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pCollisionGrid, original_pCollisionGrid, "Comparing pCollisionGrid");
				MOO_CHECK_EQ(moo_pBoundingBox, original_pBoundingBox, "Comparing pBoundingBox");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD443E0 (#10129)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_SetMaskWithSizeXY, dll_base + 0x000043E0);

		SUBCASE("")
		{
			for (const auto& tSize : { SubtilePosition{ 0, 0 }, SubtilePosition{ 1, 1 }, SubtilePosition{ 2, 3 }, SubtilePosition{ 3, 3 } })
			{
				const unsigned int nSizeX = tSize.nX;
				const unsigned int nSizeY = tSize.nY;
				CAPTURE(nSizeX);
				CAPTURE(nSizeY);

				// Input data
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[collision_mask_size]{};

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[collision_mask_size]
				) {
					setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
				};

				setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				for (int i = 0; i < test_position_count; ++i)
				{
					const int nX = test_positions[i].nX;
					const int nY = test_positions[i].nY;
					// Use a different flag for each position, so that the modified subtiles can be told apart
					const uint16_t nMask = static_cast<uint16_t>(1 << (i % 16));

					// Call both implementations
					sut(&moo_pRoom, nX, nY, nSizeX, nSizeY, nMask);
					original(&original_pRoom, nX, nY, nSizeX, nSizeY, nMask);
				}

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44600")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_SetCollisionMaskForBoundingBox, dll_base + 0x00004600);

		SUBCASE("")
		{
			for (const auto& tBoundingBox : room_bounding_boxes)
			{
				CAPTURE(tBoundingBox.nLeft);
				CAPTURE(tBoundingBox.nBottom);
				CAPTURE(tBoundingBox.nRight);
				CAPTURE(tBoundingBox.nTop);

				// Input data
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				D2BoundingBoxStrc moo_pBoundingBox{};
				uint16_t moo_pCollisionMask[collision_mask_size]{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				D2BoundingBoxStrc original_pBoundingBox{};
				uint16_t original_pCollisionMask[collision_mask_size]{};
				const uint16_t nMask = COLLIDE_MONSTER | COLLIDE_PET;

				const auto setup_data = [&tBoundingBox](
					D2RoomCollisionGridStrc& pCollisionGrid,
					D2BoundingBoxStrc& pBoundingBox,
					uint16_t(&pCollisionMask)[collision_mask_size]
				) {
					setup_collision_grid(pCollisionGrid, pCollisionMask, room_x, room_y);
					pBoundingBox = tBoundingBox;
				};

				setup_data(moo_pCollisionGrid, moo_pBoundingBox, moo_pCollisionMask);
				setup_data(original_pCollisionGrid, original_pBoundingBox, original_pCollisionMask);

				// Call both implementations
				sut(&moo_pCollisionGrid, &moo_pBoundingBox, nMask);
				original(&original_pCollisionGrid, &original_pBoundingBox, nMask);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pCollisionGrid, original_pCollisionGrid, "Comparing pCollisionGrid");
				MOO_CHECK_EQ(moo_pBoundingBox, original_pBoundingBox, "Comparing pBoundingBox");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44660 (#10131)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_TryMoveUnitCollisionMask, dll_base + 0x00004660);

		SUBCASE("")
		{
			for (int nUnitSize = COLLISION_UNIT_SIZE_POINT; nUnitSize <= COLLISION_UNIT_SIZE_BIG; ++nUnitSize)
			{
				for (const auto& tDestination : test_positions)
				{
					// The unit moves from the middle of the room to the destination
					const int nX1 = room_x + 4;
					const int nY1 = room_y + 5;
					const int nX2 = tDestination.nX;
					const int nY2 = tDestination.nY;
					CAPTURE(nUnitSize);
					CAPTURE(nX2);
					CAPTURE(nY2);

					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2RoomCollisionGridStrc moo_pCollisionGrid{};
					uint16_t moo_pCollisionMask[collision_mask_size]{};
					D2ActiveRoomStrc original_pRoom{};
					D2RoomCollisionGridStrc original_pCollisionGrid{};
					uint16_t original_pCollisionMask[collision_mask_size]{};
					const uint16_t nCollisionMask = COLLIDE_MONSTER;
					const uint16_t nMoveConditionMask = COLLIDE_MASK_MONSTER_PATH;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom,
						D2RoomCollisionGridStrc& pCollisionGrid,
						uint16_t(&pCollisionMask)[collision_mask_size]
					) {
						setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
					};

					setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
					setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX1, nY1, nX2, nY2, nUnitSize, nCollisionMask, nMoveConditionMask);
					const auto original_result = original(&original_pRoom, nX1, nY1, nX2, nY2, nUnitSize, nCollisionMask, nMoveConditionMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
					MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44910")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_CreateBoundingBox, dll_base + 0x00004910);

		SUBCASE("")
		{
			for (unsigned int nSizeX = 0; nSizeX < 5; ++nSizeX)
			{
				for (unsigned int nSizeY = 0; nSizeY < 5; ++nSizeY)
				{
					CAPTURE(nSizeX);
					CAPTURE(nSizeY);

					// Input data
					D2BoundingBoxStrc moo_pBoundingBox{};
					D2BoundingBoxStrc original_pBoundingBox{};
					const int nCenterX = room_x + 4;
					const int nCenterY = room_y + 5;

					// Call both implementations
					sut(&moo_pBoundingBox, nCenterX, nCenterY, nSizeX, nSizeY);
					original(&original_pBoundingBox, nCenterX, nCenterY, nSizeX, nSizeY);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pBoundingBox, original_pBoundingBox, "Comparing pBoundingBox");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44950 (#10132)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_TryTeleportUnitCollisionMask, dll_base + 0x00004950);

		SUBCASE("")
		{
			// Includes an invalid collision pattern
			for (int nCollisionPattern = COLLISION_PATTERN_NONE; nCollisionPattern <= COLLISION_PATTERN_SMALL_NO_PRESENCE + 1; ++nCollisionPattern)
			{
				for (const auto& tDestination : test_positions)
				{
					// The unit teleports from the middle of the room to the destination
					const int nX1 = room_x + 4;
					const int nY1 = room_y + 5;
					const int nX2 = tDestination.nX;
					const int nY2 = tDestination.nY;
					CAPTURE(nCollisionPattern);
					CAPTURE(nX2);
					CAPTURE(nY2);

					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2RoomCollisionGridStrc moo_pCollisionGrid{};
					uint16_t moo_pCollisionMask[collision_mask_size]{};
					D2ActiveRoomStrc original_pRoom{};
					D2RoomCollisionGridStrc original_pCollisionGrid{};
					uint16_t original_pCollisionMask[collision_mask_size]{};
					const uint16_t nFootprintCollisionMask = COLLIDE_MONSTER;
					const uint16_t nMoveConditionMask = COLLIDE_WALL | COLLIDE_OBJECT;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom,
						D2RoomCollisionGridStrc& pCollisionGrid,
						uint16_t(&pCollisionMask)[collision_mask_size]
					) {
						setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);
					};

					setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
					setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nX1, nY1, nX2, nY2, nCollisionPattern, nFootprintCollisionMask, nMoveConditionMask);
					const auto original_result = original(&original_pRoom, nX1, nY1, nX2, nY2, nCollisionPattern, nFootprintCollisionMask, nMoveConditionMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
					MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask, collision_mask_size }), "Comparing pCollisionMask");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44BB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_ForceTeleportUnitCollisionMaskAndGetCollision, dll_base + 0x00004BB0);

		SUBCASE("")
		{
			// Includes an invalid unit size
			for (int nUnitSize = COLLISION_UNIT_SIZE_NONE; nUnitSize <= COLLISION_UNIT_SIZE_COUNT; ++nUnitSize)
			{
				CAPTURE(nUnitSize);

				// Input data
				D2ActiveRoomStrc moo_pRoom1{};
				D2ActiveRoomStrc moo_pRoom2{};
				D2RoomCollisionGridStrc moo_pCollisionGrid1{};
				D2RoomCollisionGridStrc moo_pCollisionGrid2{};
				uint16_t moo_pCollisionMask1[collision_mask_size]{};
				uint16_t moo_pCollisionMask2[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom1{};
				D2ActiveRoomStrc original_pRoom2{};
				D2RoomCollisionGridStrc original_pCollisionGrid1{};
				D2RoomCollisionGridStrc original_pCollisionGrid2{};
				uint16_t original_pCollisionMask1[collision_mask_size]{};
				uint16_t original_pCollisionMask2[collision_mask_size]{};
				// The unit teleports from the middle of the first room to the middle of the second room
				const int nX1 = room_x + 4;
				const int nY1 = room_y + 5;
				const int nX2 = adjacent_room_x + 5;
				const int nY2 = adjacent_room_y + 4;
				const uint16_t nFootprintCollisionMask = COLLIDE_MONSTER;
				const uint16_t nMoveConditionMask = COLLIDE_MASK_MONSTER_PATH;

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom1,
					D2ActiveRoomStrc& pRoom2,
					D2RoomCollisionGridStrc& pCollisionGrid1,
					D2RoomCollisionGridStrc& pCollisionGrid2,
					uint16_t(&pCollisionMask1)[collision_mask_size],
					uint16_t(&pCollisionMask2)[collision_mask_size]
				) {
					setup_room(pRoom1, pCollisionGrid1, pCollisionMask1, room_x, room_y);
					setup_room(pRoom2, pCollisionGrid2, pCollisionMask2, adjacent_room_x, adjacent_room_y);
				};

				setup_data(moo_pRoom1, moo_pRoom2, moo_pCollisionGrid1, moo_pCollisionGrid2, moo_pCollisionMask1, moo_pCollisionMask2);
				setup_data(original_pRoom1, original_pRoom2, original_pCollisionGrid1, original_pCollisionGrid2, original_pCollisionMask1, original_pCollisionMask2);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom1, nX1, nY1, &moo_pRoom2, nX2, nY2, nUnitSize, nFootprintCollisionMask, nMoveConditionMask);
				const auto original_result = original(&original_pRoom1, nX1, nY1, &original_pRoom2, nX2, nY2, nUnitSize, nFootprintCollisionMask, nMoveConditionMask);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
				MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask1, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask1, collision_mask_size }), "Comparing pCollisionMask1");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask2, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask2, collision_mask_size }), "Comparing pCollisionMask2");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44E00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_TeleportUnitCollisionMask, dll_base + 0x00004E00);

		SUBCASE("")
		{
			// Includes an invalid unit size
			for (int nUnitSize = COLLISION_UNIT_SIZE_NONE; nUnitSize <= COLLISION_UNIT_SIZE_COUNT; ++nUnitSize)
			{
				CAPTURE(nUnitSize);

				// Input data
				D2ActiveRoomStrc moo_pRoom1{};
				D2ActiveRoomStrc moo_pRoom2{};
				D2RoomCollisionGridStrc moo_pCollisionGrid1{};
				D2RoomCollisionGridStrc moo_pCollisionGrid2{};
				uint16_t moo_pCollisionMask1[collision_mask_size]{};
				uint16_t moo_pCollisionMask2[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom1{};
				D2ActiveRoomStrc original_pRoom2{};
				D2RoomCollisionGridStrc original_pCollisionGrid1{};
				D2RoomCollisionGridStrc original_pCollisionGrid2{};
				uint16_t original_pCollisionMask1[collision_mask_size]{};
				uint16_t original_pCollisionMask2[collision_mask_size]{};
				// The unit teleports from the middle of the first room to the middle of the second room
				const int nX1 = room_x + 4;
				const int nY1 = room_y + 5;
				const int nX2 = adjacent_room_x + 5;
				const int nY2 = adjacent_room_y + 4;
				const uint16_t nMask = COLLIDE_MONSTER;

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom1,
					D2ActiveRoomStrc& pRoom2,
					D2RoomCollisionGridStrc& pCollisionGrid1,
					D2RoomCollisionGridStrc& pCollisionGrid2,
					uint16_t(&pCollisionMask1)[collision_mask_size],
					uint16_t(&pCollisionMask2)[collision_mask_size]
				) {
					setup_room(pRoom1, pCollisionGrid1, pCollisionMask1, room_x, room_y);
					setup_room(pRoom2, pCollisionGrid2, pCollisionMask2, adjacent_room_x, adjacent_room_y);
				};

				setup_data(moo_pRoom1, moo_pRoom2, moo_pCollisionGrid1, moo_pCollisionGrid2, moo_pCollisionMask1, moo_pCollisionMask2);
				setup_data(original_pRoom1, original_pRoom2, original_pCollisionGrid1, original_pCollisionGrid2, original_pCollisionMask1, original_pCollisionMask2);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom1, nX1, nY1, &moo_pRoom2, nX2, nY2, nUnitSize, nMask);
				const auto original_result = original(&original_pRoom1, nX1, nY1, &original_pRoom2, nX2, nY2, nUnitSize, nMask);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
				MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask1, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask1, collision_mask_size }), "Comparing pCollisionMask1");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask2, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask2, collision_mask_size }), "Comparing pCollisionMask2");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD44FF0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_TrySetUnitCollisionMask, dll_base + 0x00004FF0);

		SUBCASE("")
		{
			// Includes an invalid collision pattern
			for (int nCollisionPattern = COLLISION_PATTERN_NONE; nCollisionPattern <= COLLISION_PATTERN_SMALL_NO_PRESENCE + 1; ++nCollisionPattern)
			{
				// Destinations in the second room: two subtiles blocked by a wall and a free one
				for (const auto& tDestination : { SubtilePosition{ adjacent_room_x + 5, adjacent_room_y + 4 }, SubtilePosition{ adjacent_room_x + 1, adjacent_room_y }, SubtilePosition{ adjacent_room_x, adjacent_room_y } })
				{
					const int nX2 = tDestination.nX;
					const int nY2 = tDestination.nY;
					CAPTURE(nCollisionPattern);
					CAPTURE(nX2);
					CAPTURE(nY2);

					// Input data
					D2ActiveRoomStrc moo_pRoom1{};
					D2ActiveRoomStrc moo_pRoom2{};
					D2RoomCollisionGridStrc moo_pCollisionGrid1{};
					D2RoomCollisionGridStrc moo_pCollisionGrid2{};
					uint16_t moo_pCollisionMask1[collision_mask_size]{};
					uint16_t moo_pCollisionMask2[collision_mask_size]{};
					D2ActiveRoomStrc original_pRoom1{};
					D2ActiveRoomStrc original_pRoom2{};
					D2RoomCollisionGridStrc original_pCollisionGrid1{};
					D2RoomCollisionGridStrc original_pCollisionGrid2{};
					uint16_t original_pCollisionMask1[collision_mask_size]{};
					uint16_t original_pCollisionMask2[collision_mask_size]{};
					const int nX1 = room_x + 4;
					const int nY1 = room_y + 5;
					const uint16_t nFootprintCollisionMask = COLLIDE_MONSTER;
					const uint16_t nMoveConditionMask = COLLIDE_WALL;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom1,
						D2ActiveRoomStrc& pRoom2,
						D2RoomCollisionGridStrc& pCollisionGrid1,
						D2RoomCollisionGridStrc& pCollisionGrid2,
						uint16_t(&pCollisionMask1)[collision_mask_size],
						uint16_t(&pCollisionMask2)[collision_mask_size]
					) {
						setup_room(pRoom1, pCollisionGrid1, pCollisionMask1, room_x, room_y);
						setup_room(pRoom2, pCollisionGrid2, pCollisionMask2, adjacent_room_x, adjacent_room_y);
					};

					setup_data(moo_pRoom1, moo_pRoom2, moo_pCollisionGrid1, moo_pCollisionGrid2, moo_pCollisionMask1, moo_pCollisionMask2);
					setup_data(original_pRoom1, original_pRoom2, original_pCollisionGrid1, original_pCollisionGrid2, original_pCollisionMask1, original_pCollisionMask2);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom1, nX1, nY1, &moo_pRoom2, nX2, nY2, nCollisionPattern, nFootprintCollisionMask, nMoveConditionMask);
					const auto original_result = original(&original_pRoom1, nX1, nY1, &original_pRoom2, nX2, nY2, nCollisionPattern, nFootprintCollisionMask, nMoveConditionMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
					MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");
					MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask1, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask1, collision_mask_size }), "Comparing pCollisionMask1");
					MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask2, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask2, collision_mask_size }), "Comparing pCollisionMask2");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD451D0 (#10133)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_SetUnitCollisionMask, dll_base + 0x000051D0);

		SUBCASE("")
		{
			// Includes an invalid collision pattern
			for (int nCollisionPattern = COLLISION_PATTERN_NONE; nCollisionPattern <= COLLISION_PATTERN_SMALL_NO_PRESENCE + 1; ++nCollisionPattern)
			{
				CAPTURE(nCollisionPattern);

				// Input data
				D2ActiveRoomStrc moo_pRoom1{};
				D2ActiveRoomStrc moo_pRoom2{};
				D2RoomCollisionGridStrc moo_pCollisionGrid1{};
				D2RoomCollisionGridStrc moo_pCollisionGrid2{};
				uint16_t moo_pCollisionMask1[collision_mask_size]{};
				uint16_t moo_pCollisionMask2[collision_mask_size]{};
				D2ActiveRoomStrc original_pRoom1{};
				D2ActiveRoomStrc original_pRoom2{};
				D2RoomCollisionGridStrc original_pCollisionGrid1{};
				D2RoomCollisionGridStrc original_pCollisionGrid2{};
				uint16_t original_pCollisionMask1[collision_mask_size]{};
				uint16_t original_pCollisionMask2[collision_mask_size]{};
				// The unit moves from the middle of the first room to the middle of the second room
				const int nX1 = room_x + 4;
				const int nY1 = room_y + 5;
				const int nX2 = adjacent_room_x + 5;
				const int nY2 = adjacent_room_y + 4;
				const uint16_t nCollisionMask = COLLIDE_MONSTER | COLLIDE_WALL;

				const auto setup_data = [](
					D2ActiveRoomStrc& pRoom1,
					D2ActiveRoomStrc& pRoom2,
					D2RoomCollisionGridStrc& pCollisionGrid1,
					D2RoomCollisionGridStrc& pCollisionGrid2,
					uint16_t(&pCollisionMask1)[collision_mask_size],
					uint16_t(&pCollisionMask2)[collision_mask_size]
				) {
					setup_room(pRoom1, pCollisionGrid1, pCollisionMask1, room_x, room_y);
					setup_room(pRoom2, pCollisionGrid2, pCollisionMask2, adjacent_room_x, adjacent_room_y);
				};

				setup_data(moo_pRoom1, moo_pRoom2, moo_pCollisionGrid1, moo_pCollisionGrid2, moo_pCollisionMask1, moo_pCollisionMask2);
				setup_data(original_pRoom1, original_pRoom2, original_pCollisionGrid1, original_pCollisionGrid2, original_pCollisionMask1, original_pCollisionMask2);

				// Call both implementations
				sut(&moo_pRoom1, nX1, nY1, &moo_pRoom2, nX2, nY2, nCollisionPattern, nCollisionMask);
				original(&original_pRoom1, nX1, nY1, &original_pRoom2, nX2, nY2, nCollisionPattern, nCollisionMask);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom1, original_pRoom1, "Comparing pRoom1");
				MOO_CHECK_EQ(moo_pRoom2, original_pRoom2, "Comparing pRoom2");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask1, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask1, collision_mask_size }), "Comparing pCollisionMask1");
				MOO_CHECK_EQ((DynamicArray<uint16_t>{ moo_pCollisionMask2, collision_mask_size }), (DynamicArray<uint16_t>{ original_pCollisionMask2, collision_mask_size }), "Comparing pCollisionMask2");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD459D0 (#10135)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_GetFreeCoordinatesWithMaxDistance, dll_base + 0x000059D0);

		SUBCASE("")
		{
			for (int nUnitSize = COLLISION_UNIT_SIZE_POINT; nUnitSize <= COLLISION_UNIT_SIZE_BIG; ++nUnitSize)
			{
				for (const BOOL bAllowNeighborRooms : { FALSE, TRUE })
				{
					for (const int nMaxDistance : { 1, 3, 8 })
					{
						CAPTURE(nUnitSize);
						CAPTURE(bAllowNeighborRooms);
						CAPTURE(nMaxDistance);

						// Input data
						D2ActiveRoomStrc moo_pRoom{};
						D2CoordStrc moo_pSpawnPoint{};
						D2RoomCollisionGridStrc moo_pCollisionGrid{};
						uint16_t moo_pCollisionMask[collision_mask_size]{};
						D2ActiveRoomStrc original_pRoom{};
						D2CoordStrc original_pSpawnPoint{};
						D2RoomCollisionGridStrc original_pCollisionGrid{};
						uint16_t original_pCollisionMask[collision_mask_size]{};
						const unsigned int nMask = COLLIDE_MASK_PLACEMENT;

						const auto setup_data = [](
							D2ActiveRoomStrc& pRoom,
							D2CoordStrc& pSpawnPoint,
							D2RoomCollisionGridStrc& pCollisionGrid,
							uint16_t(&pCollisionMask)[collision_mask_size]
						) {
							setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);

							// The spawn point is blocked by a monster, so that free coordinates have to be searched
							pSpawnPoint.nX = room_x + 5;
							pSpawnPoint.nY = room_y + 4;
						};

						setup_data(moo_pRoom, moo_pSpawnPoint, moo_pCollisionGrid, moo_pCollisionMask);
						setup_data(original_pRoom, original_pSpawnPoint, original_pCollisionGrid, original_pCollisionMask);

						// Call both implementations
						const auto moo_result = sut(&moo_pRoom, &moo_pSpawnPoint, nUnitSize, nMask, bAllowNeighborRooms, nMaxDistance);
						const auto original_result = original(&original_pRoom, &original_pSpawnPoint, nUnitSize, nMask, bAllowNeighborRooms, nMaxDistance);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
						MOO_CHECK_EQ(moo_pSpawnPoint, original_pSpawnPoint, "Comparing pSpawnPoint");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD45A00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_GetFreeCoordinatesImpl, dll_base + 0x00005A00);

		SUBCASE("")
		{
			for (int nUnitSize = COLLISION_UNIT_SIZE_POINT; nUnitSize <= COLLISION_UNIT_SIZE_BIG; ++nUnitSize)
			{
				for (const BOOL bAllowNeighborRooms : { FALSE, TRUE })
				{
					for (const int nPosIncrementValue : { 1, 2 })
					{
						CAPTURE(nUnitSize);
						CAPTURE(bAllowNeighborRooms);
						CAPTURE(nPosIncrementValue);

						// Input data
						D2ActiveRoomStrc moo_pRoom{};
						D2CoordStrc moo_ptSpawnPoint{};
						D2CoordStrc moo_pFieldCoord{};
						D2RoomCollisionGridStrc moo_pCollisionGrid{};
						uint16_t moo_pCollisionMask[collision_mask_size]{};
						D2ActiveRoomStrc original_pRoom{};
						D2CoordStrc original_ptSpawnPoint{};
						D2CoordStrc original_pFieldCoord{};
						D2RoomCollisionGridStrc original_pCollisionGrid{};
						uint16_t original_pCollisionMask[collision_mask_size]{};
						const unsigned int nMask = COLLIDE_MASK_SPAWN | COLLIDE_MONSTER;
						// The collision field tables are not loaded, so every candidate position has to be rejected
						// by the collision mask check of D2Common_11099, before the field data would be accessed
						const unsigned int nFieldMask = COLLIDE_PRESET;
						const int nMaxDistance = 8;

						const auto setup_data = [](
							D2ActiveRoomStrc& pRoom,
							D2CoordStrc& ptSpawnPoint,
							D2CoordStrc& pFieldCoord,
							D2RoomCollisionGridStrc& pCollisionGrid,
							uint16_t(&pCollisionMask)[collision_mask_size]
						) {
							setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_PRESET);

							// The spawn point is blocked by a monster, so that free coordinates have to be searched
							ptSpawnPoint.nX = room_x + 5;
							ptSpawnPoint.nY = room_y + 4;

							pFieldCoord.nX = room_x + 2;
							pFieldCoord.nY = room_y + 2;
						};

						setup_data(moo_pRoom, moo_ptSpawnPoint, moo_pFieldCoord, moo_pCollisionGrid, moo_pCollisionMask);
						setup_data(original_pRoom, original_ptSpawnPoint, original_pFieldCoord, original_pCollisionGrid, original_pCollisionMask);

						// Call both implementations
						const auto moo_result = sut(&moo_pRoom, &moo_ptSpawnPoint, &moo_pFieldCoord, nUnitSize, nMask, nFieldMask, bAllowNeighborRooms, nMaxDistance, nPosIncrementValue);
						const auto original_result = original(&original_pRoom, &original_ptSpawnPoint, &original_pFieldCoord, nUnitSize, nMask, nFieldMask, bAllowNeighborRooms, nMaxDistance, nPosIncrementValue);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
						MOO_CHECK_EQ(moo_ptSpawnPoint, original_ptSpawnPoint, "Comparing ptSpawnPoint");
						MOO_CHECK_EQ(moo_pFieldCoord, original_pFieldCoord, "Comparing pFieldCoord");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD46280 (#10134)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_GetFreeCoordinates, dll_base + 0x00006280);

		SUBCASE("")
		{
			for (int nUnitSize = COLLISION_UNIT_SIZE_POINT; nUnitSize <= COLLISION_UNIT_SIZE_BIG; ++nUnitSize)
			{
				for (const BOOL bAllowNeighborRooms : { FALSE, TRUE })
				{
					CAPTURE(nUnitSize);
					CAPTURE(bAllowNeighborRooms);

					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2CoordStrc moo_pSpawnPoint{};
					D2RoomCollisionGridStrc moo_pCollisionGrid{};
					uint16_t moo_pCollisionMask[collision_mask_size]{};
					D2ActiveRoomStrc original_pRoom{};
					D2CoordStrc original_pSpawnPoint{};
					D2RoomCollisionGridStrc original_pCollisionGrid{};
					uint16_t original_pCollisionMask[collision_mask_size]{};
					const unsigned int nMask = COLLIDE_MASK_PLACEMENT;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom,
						D2CoordStrc& pSpawnPoint,
						D2RoomCollisionGridStrc& pCollisionGrid,
						uint16_t(&pCollisionMask)[collision_mask_size]
					) {
						setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);

						// The spawn point is blocked by a monster, so that free coordinates have to be searched
						pSpawnPoint.nX = room_x + 5;
						pSpawnPoint.nY = room_y + 4;
					};

					setup_data(moo_pRoom, moo_pSpawnPoint, moo_pCollisionGrid, moo_pCollisionMask);
					setup_data(original_pRoom, original_pSpawnPoint, original_pCollisionGrid, original_pCollisionMask);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, &moo_pSpawnPoint, nUnitSize, nMask, bAllowNeighborRooms);
					const auto original_result = original(&original_pRoom, &original_pSpawnPoint, nUnitSize, nMask, bAllowNeighborRooms);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
					MOO_CHECK_EQ(moo_pSpawnPoint, original_pSpawnPoint, "Comparing pSpawnPoint");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD462B0 (#10137)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_GetFreeCoordinatesEx, dll_base + 0x000062B0);

		SUBCASE("")
		{
			for (int nUnitSize = COLLISION_UNIT_SIZE_POINT; nUnitSize <= COLLISION_UNIT_SIZE_BIG; ++nUnitSize)
			{
				for (const int nPosIncrementValue : { 1, 2 })
				{
					CAPTURE(nUnitSize);
					CAPTURE(nPosIncrementValue);

					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2CoordStrc moo_pSpawnPoint{};
					D2RoomCollisionGridStrc moo_pCollisionGrid{};
					uint16_t moo_pCollisionMask[collision_mask_size]{};
					D2ActiveRoomStrc original_pRoom{};
					D2CoordStrc original_pSpawnPoint{};
					D2RoomCollisionGridStrc original_pCollisionGrid{};
					uint16_t original_pCollisionMask[collision_mask_size]{};
					const unsigned int nMask = COLLIDE_MASK_PLACEMENT;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom,
						D2CoordStrc& pSpawnPoint,
						D2RoomCollisionGridStrc& pCollisionGrid,
						uint16_t(&pCollisionMask)[collision_mask_size]
					) {
						setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);

						// The spawn point is blocked by a monster, so that free coordinates have to be searched
						pSpawnPoint.nX = room_x + 5;
						pSpawnPoint.nY = room_y + 4;
					};

					setup_data(moo_pRoom, moo_pSpawnPoint, moo_pCollisionGrid, moo_pCollisionMask);
					setup_data(original_pRoom, original_pSpawnPoint, original_pCollisionGrid, original_pCollisionMask);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, &moo_pSpawnPoint, nUnitSize, nMask, nPosIncrementValue);
					const auto original_result = original(&original_pRoom, &original_pSpawnPoint, nUnitSize, nMask, nPosIncrementValue);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
					MOO_CHECK_EQ(moo_pSpawnPoint, original_pSpawnPoint, "Comparing pSpawnPoint");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD462E0 (#10138)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_GetFreeCoordinatesWithField, dll_base + 0x000062E0);

		SUBCASE("")
		{
			for (int nUnitSize = COLLISION_UNIT_SIZE_POINT; nUnitSize <= COLLISION_UNIT_SIZE_BIG; ++nUnitSize)
			{
				for (const BOOL bAllowNeighborRooms : { FALSE, TRUE })
				{
					CAPTURE(nUnitSize);
					CAPTURE(bAllowNeighborRooms);

					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2CoordStrc moo_pSpawnPoint{};
					D2CoordStrc moo_pFieldCoord{};
					D2RoomCollisionGridStrc moo_pCollisionGrid{};
					uint16_t moo_pCollisionMask[collision_mask_size]{};
					D2ActiveRoomStrc original_pRoom{};
					D2CoordStrc original_pSpawnPoint{};
					D2CoordStrc original_pFieldCoord{};
					D2RoomCollisionGridStrc original_pCollisionGrid{};
					uint16_t original_pCollisionMask[collision_mask_size]{};
					const unsigned int nMask = COLLIDE_MASK_SPAWN | COLLIDE_MONSTER;
					// The collision field tables are not loaded, so every candidate position has to be rejected
					// by the collision mask check of D2Common_11099, before the field data would be accessed
					const unsigned int nFieldMask = COLLIDE_PRESET;

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom,
						D2CoordStrc& pSpawnPoint,
						D2CoordStrc& pFieldCoord,
						D2RoomCollisionGridStrc& pCollisionGrid,
						uint16_t(&pCollisionMask)[collision_mask_size]
					) {
						setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y, COLLIDE_PRESET);

						// The spawn point is blocked by a monster, so that free coordinates have to be searched
						pSpawnPoint.nX = room_x + 5;
						pSpawnPoint.nY = room_y + 4;

						pFieldCoord.nX = room_x + 2;
						pFieldCoord.nY = room_y + 2;
					};

					setup_data(moo_pRoom, moo_pSpawnPoint, moo_pFieldCoord, moo_pCollisionGrid, moo_pCollisionMask);
					setup_data(original_pRoom, original_pSpawnPoint, original_pFieldCoord, original_pCollisionGrid, original_pCollisionMask);

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, &moo_pSpawnPoint, &moo_pFieldCoord, nUnitSize, nMask, nFieldMask, bAllowNeighborRooms);
					const auto original_result = original(&original_pRoom, &original_pSpawnPoint, &original_pFieldCoord, nUnitSize, nMask, nFieldMask, bAllowNeighborRooms);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
					MOO_CHECK_EQ(moo_pSpawnPoint, original_pSpawnPoint, "Comparing pSpawnPoint");
					MOO_CHECK_EQ(moo_pFieldCoord, original_pFieldCoord, "Comparing pFieldCoord");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD46310 (#10136)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10136, dll_base + 0x00006310);

		SUBCASE("")
		{
			// The searched area is (a3 + 2) x (a3 + 2) subtiles large
			for (const int a3 : { 0, 1 })
			{
				// A wide mask doesn't leave any free area, so that the whole search space is covered
				for (const uint16_t nMask : { COLLIDE_WALL, COLLIDE_ALL_MASK })
				{
					CAPTURE(a3);
					CAPTURE(nMask);

					// Input data
					D2ActiveRoomStrc moo_pRoom{};
					D2CoordStrc moo_pCoord{};
					D2ActiveRoomStrc* moo_ppRoom{};
					D2RoomCollisionGridStrc moo_pCollisionGrid{};
					uint16_t moo_pCollisionMask[collision_mask_size]{};
					D2ActiveRoomStrc original_pRoom{};
					D2CoordStrc original_pCoord{};
					D2ActiveRoomStrc* original_ppRoom{};
					D2RoomCollisionGridStrc original_pCollisionGrid{};
					uint16_t original_pCollisionMask[collision_mask_size]{};

					const auto setup_data = [](
						D2ActiveRoomStrc& pRoom,
						D2CoordStrc& pCoord,
						D2RoomCollisionGridStrc& pCollisionGrid,
						uint16_t(&pCollisionMask)[collision_mask_size]
					) {
						setup_room(pRoom, pCollisionGrid, pCollisionMask, room_x, room_y);

						pCoord.nX = room_x + 5;
						pCoord.nY = room_y + 4;
					};

					setup_data(moo_pRoom, moo_pCoord, moo_pCollisionGrid, moo_pCollisionMask);
					setup_data(original_pRoom, original_pCoord, original_pCollisionGrid, original_pCollisionMask);

					// Call both implementations
					sut(&moo_pRoom, &moo_pCoord, a3, nMask, &moo_ppRoom);
					original(&original_pRoom, &original_pCoord, a3, nMask, &original_ppRoom);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
					MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
					MOO_CHECK_EQ(moo_ppRoom, original_ppRoom, "Comparing ppRoom");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD46620")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COLLISION_GetRoomBySubTileCoordinates, dll_base + 0x00006620);

		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc* moo_pRoomList{};
			D2ActiveRoomStrc moo_pAdjacentRoom{};
			D2ActiveRoomStrc original_pRoom{};
			D2ActiveRoomStrc* original_pRoomList{};
			D2ActiveRoomStrc original_pAdjacentRoom{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2ActiveRoomStrc*& pRoomList,
				D2ActiveRoomStrc& pAdjacentRoom
			) {
				// Only the room coordinates are used
				setup_coordinates(pRoom.tCoords, room_x, room_y);
				setup_coordinates(pAdjacentRoom.tCoords, adjacent_room_x, adjacent_room_y);
				set_adjacent_room(pRoom, pRoomList, pAdjacentRoom);
			};

			setup_data(moo_pRoom, moo_pRoomList, moo_pAdjacentRoom);
			setup_data(original_pRoom, original_pRoomList, original_pAdjacentRoom);

			for (const auto& tPosition : test_positions)
			{
				const int nX = tPosition.nX;
				const int nY = tPosition.nY;
				CAPTURE(nX);
				CAPTURE(nY);

				// Call both implementations
				const auto moo_result = sut(&moo_pRoom, nX, nY);
				const auto original_result = original(&original_pRoom, nX, nY);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
}

#endif
