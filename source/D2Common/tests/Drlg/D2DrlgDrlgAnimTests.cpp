#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2CMP.h>
#include <Drlg/D2DrlgDrlgAnim.h>
#include <Drlg/D2DrlgRoomTile.h>


TEST_SUITE("D2DrlgDrlgAnimTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75480")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGANIM_InitCache, dll_base + 0x00035480);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgTileDataStrc moo_pTileData{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgTileDataStrc original_pTileData{};

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgTileDataStrc& pTileData
			) {
				// Acts other than I-III have no animated tiles, so the tile data is only cleared
				pDrlg.nAct = ACT_IV;

				// Fill the tile data so that clearing it can be observed
				pTileData.nWidth = 160;
				pTileData.nHeight = 80;
				pTileData.nPosX = 3;
				pTileData.nPosY = 4;
				pTileData.dwFlags = MAPTILE_HIDDEN;
				pTileData.nTileType = TILETYPE_WALL_LEFT;
				pTileData.nRed = 255;
				pTileData.nGreen = 128;
				pTileData.nBlue = 64;
				pTileData.nIntensity = 32;
			};

			setup_data(moo_pDrlg, moo_pTileData);
			setup_data(original_pDrlg, original_pTileData);

			// Call both implementations
			sut(&moo_pDrlg, &moo_pTileData);
			original(&original_pDrlg, &original_pTileData);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75560")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGANIM_TestLoadAnimatedRoomTiles, dll_base + 0x00035560);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgGridStrc moo_pDrlgGrid{};
			D2DrlgGridStrc moo_pTileTypeGrid{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgGridStrc original_pDrlgGrid{};
			D2DrlgGridStrc original_pTileTypeGrid{};
			int32_t moo_pCellsFlags[4]{};
			int32_t moo_pCellsRowOffsets[2]{};
			int32_t original_pCellsFlags[4]{};
			int32_t original_pCellsRowOffsets[2]{};
			int nTileType = TILETYPE_FLOOR;
			int nTileX = 1;
			int nTileY = 1;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgGridStrc& pDrlgGrid,
				D2DrlgGridStrc& pTileTypeGrid,
				int32_t(& pCellsFlags)[4],
				int32_t(& pCellsRowOffsets)[2]
			) {
				// Non-zero tile positions, so the room's 2x2 tiles are iterated without an extra row/column
				pDrlgRoom.nTileWidth = 2;
				pDrlgRoom.nTileHeight = 2;

				pCellsRowOffsets[0] = 0;
				pCellsRowOffsets[1] = 2;

				// Tiles with style/sequence but neither wall, floor nor shadow flags are not checked for animation
				D2C_PackedTileInformation tTileInfo{};
				tTileInfo.bLOS = 1;
				tTileInfo.nTileStyle = 5;
				tTileInfo.nTileSequence = 3;
				for (auto i = 0; i < 4; ++i)
				{
					pCellsFlags[i] = tTileInfo.nPackedValue;
				}

				pDrlgGrid.pCellsFlags = pCellsFlags;
				pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
				pDrlgGrid.nWidth = 2;
				pDrlgGrid.nHeight = 2;
			};

			setup_data(moo_pDrlgRoom, moo_pDrlgGrid, moo_pTileTypeGrid, moo_pCellsFlags, moo_pCellsRowOffsets);
			setup_data(original_pDrlgRoom, original_pDrlgGrid, original_pTileTypeGrid, original_pCellsFlags, original_pCellsRowOffsets);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pDrlgGrid, &moo_pTileTypeGrid, nTileType, nTileX, nTileY);
			original(&original_pDrlgRoom, &original_pDrlgGrid, &original_pTileTypeGrid, nTileType, nTileX, nTileY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			MOO_CHECK_EQ(moo_pTileTypeGrid, original_pTileTypeGrid, "Comparing pTileTypeGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD756B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGANIM_AnimateTiles, dll_base + 0x000356B0);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc* moo_ppRoomsNear[1]{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgAnimTileGridStrc moo_pAnimTileGrid{};
			D2DrlgTileDataStrc* moo_ppMapTileData[2]{};
			D2DrlgTileDataStrc moo_pTileData[2]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc* original_ppRoomsNear[1]{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgAnimTileGridStrc original_pAnimTileGrid{};
			D2DrlgTileDataStrc* original_ppMapTileData[2]{};
			D2DrlgTileDataStrc original_pTileData[2]{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc*(& ppRoomsNear)[1],
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgAnimTileGridStrc& pAnimTileGrid,
				D2DrlgTileDataStrc*(& ppMapTileData)[2],
				D2DrlgTileDataStrc(& pTileData)[2]
			) {
				// Rooms are always near to themselves
				ppRoomsNear[0] = &pDrlgRoom;
				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 1;
				pDrlgRoom.dwFlags = DRLGROOMFLAG_ANIMATED_FLOOR;
				pDrlgRoom.pTileGrid = &pTileGrid;

				pTileGrid.pAnimTiles = &pAnimTileGrid;

				// Two frames, currently showing the first one; advancing by one full frame shows the second one
				pTileData[0].nTileType = TILETYPE_FLOOR;
				pTileData[1].nTileType = TILETYPE_FLOOR;
				pTileData[1].dwFlags = MAPTILE_HIDDEN;
				ppMapTileData[0] = &pTileData[0];
				ppMapTileData[1] = &pTileData[1];

				pAnimTileGrid.ppMapTileData = ppMapTileData;
				pAnimTileGrid.nFrames = 2;
				pAnimTileGrid.nCurrentFrame = 0;
				pAnimTileGrid.nAnimationSpeed = 0x100;
			};

			setup_data(moo_pDrlgRoom, moo_ppRoomsNear, moo_pTileGrid, moo_pAnimTileGrid, moo_ppMapTileData, moo_pTileData);
			setup_data(original_pDrlgRoom, original_ppRoomsNear, original_pTileGrid, original_pAnimTileGrid, original_ppMapTileData, original_pTileData);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTileData[0], original_pTileData[0], "Comparing pTileData[0]");
			MOO_CHECK_EQ(moo_pTileData[1], original_pTileData[1], "Comparing pTileData[1]");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75740")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGANIM_AllocAnimationTileGrids, dll_base + 0x00035740);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgGridStrc moo_pWallGrid{};
			D2DrlgGridStrc moo_pFloorGrid{};
			D2DrlgGridStrc moo_pShadowGrid{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgGridStrc original_pWallGrid{};
			D2DrlgGridStrc original_pFloorGrid{};
			D2DrlgGridStrc original_pShadowGrid{};
			int nAnimationSpeed{};
			int nWalls{};
			int nFloors{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgGridStrc& pWallGrid,
				D2DrlgGridStrc& pFloorGrid,
				D2DrlgGridStrc& pShadowGrid
			) {
				// The room has no wall, floor or roof tiles, so no animation tile grids are allocated
				pDrlgRoom.pTileGrid = &pTileGrid;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pWallGrid, moo_pFloorGrid, moo_pShadowGrid);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pWallGrid, original_pFloorGrid, original_pShadowGrid);

			// Call both implementations
			sut(&moo_pDrlgRoom, nAnimationSpeed, &moo_pWallGrid, nWalls, &moo_pFloorGrid, nFloors, &moo_pShadowGrid);
			original(&original_pDrlgRoom, nAnimationSpeed, &original_pWallGrid, nWalls, &original_pFloorGrid, nFloors, &original_pShadowGrid);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pWallGrid, original_pWallGrid, "Comparing pWallGrid");
			MOO_CHECK_EQ(moo_pFloorGrid, original_pFloorGrid, "Comparing pFloorGrid");
			MOO_CHECK_EQ(moo_pShadowGrid, original_pShadowGrid, "Comparing pShadowGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD757B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGANIM_AllocAnimationTileGrid, dll_base + 0x000357B0);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileDataStrc moo_pTiles{};
			D2DrlgGridStrc moo_pDrlgGrid{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileDataStrc original_pTiles{};
			D2DrlgGridStrc original_pDrlgGrid{};
			int nAnimationSpeed{};
			int nTiles = 1;
			int nUnused{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileDataStrc& pTiles,
				D2DrlgGridStrc& pDrlgGrid
			) {
				// A tile without a tile library entry is not animated, so it is skipped
				pTiles.nPosX = 1;
				pTiles.nPosY = 2;
				pTiles.nTileType = TILETYPE_FLOOR;
				pTiles.pTile = nullptr;
			};

			setup_data(moo_pDrlgRoom, moo_pTiles, moo_pDrlgGrid);
			setup_data(original_pDrlgRoom, original_pTiles, original_pDrlgGrid);

			// Call both implementations
			sut(&moo_pDrlgRoom, nAnimationSpeed, &moo_pTiles, nTiles, &moo_pDrlgGrid, nUnused);
			original(&original_pDrlgRoom, nAnimationSpeed, &original_pTiles, nTiles, &original_pDrlgGrid, nUnused);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pTiles, original_pTiles, "Comparing pTiles");
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75B00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGANIM_UpdateFrameInAdjacentRooms, dll_base + 0x00035B00);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom1{};
			D2DrlgRoomStrc moo_pDrlgRoom2{};
			D2DrlgRoomStrc* moo_ppRoomsNear1[1]{};
			D2DrlgRoomStrc* moo_ppRoomsNear2[1]{};
			D2DrlgTileGridStrc moo_pTileGrid1{};
			D2DrlgTileGridStrc moo_pTileGrid2{};
			D2DrlgAnimTileGridStrc moo_pAnimTileGrid1{};
			D2DrlgAnimTileGridStrc moo_pAnimTileGrids2[2]{};
			D2DrlgRoomStrc original_pDrlgRoom1{};
			D2DrlgRoomStrc original_pDrlgRoom2{};
			D2DrlgRoomStrc* original_ppRoomsNear1[1]{};
			D2DrlgRoomStrc* original_ppRoomsNear2[1]{};
			D2DrlgTileGridStrc original_pTileGrid1{};
			D2DrlgTileGridStrc original_pTileGrid2{};
			D2DrlgAnimTileGridStrc original_pAnimTileGrid1{};
			D2DrlgAnimTileGridStrc original_pAnimTileGrids2[2]{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom1,
				D2DrlgRoomStrc& pDrlgRoom2,
				D2DrlgRoomStrc*(& ppRoomsNear1)[1],
				D2DrlgRoomStrc*(& ppRoomsNear2)[1],
				D2DrlgTileGridStrc& pTileGrid1,
				D2DrlgTileGridStrc& pTileGrid2,
				D2DrlgAnimTileGridStrc& pAnimTileGrid1,
				D2DrlgAnimTileGridStrc(& pAnimTileGrids2)[2]
			) {
				// Source room, its animated tiles define the current frame
				ppRoomsNear1[0] = &pDrlgRoom1;
				pDrlgRoom1.ppRoomsNear = ppRoomsNear1;
				pDrlgRoom1.nRoomsNear = 1;
				pDrlgRoom1.pTileGrid = &pTileGrid1;
				pTileGrid1.pAnimTiles = &pAnimTileGrid1;
				pAnimTileGrid1.nFrames = 4;
				pAnimTileGrid1.nCurrentFrame = 0x180;
				pAnimTileGrid1.nAnimationSpeed = 0x80;

				// Target room, all of its animated tiles get synchronized to the source room's frame
				ppRoomsNear2[0] = &pDrlgRoom2;
				pDrlgRoom2.ppRoomsNear = ppRoomsNear2;
				pDrlgRoom2.nRoomsNear = 1;
				pDrlgRoom2.pTileGrid = &pTileGrid2;
				pTileGrid2.pAnimTiles = &pAnimTileGrids2[0];
				pAnimTileGrids2[0].pNext = &pAnimTileGrids2[1];
				for (auto i = 0; i < 2; ++i)
				{
					pAnimTileGrids2[i].nFrames = 4;
					pAnimTileGrids2[i].nCurrentFrame = 0;
					pAnimTileGrids2[i].nAnimationSpeed = 0x80;
				}
			};

			setup_data(moo_pDrlgRoom1, moo_pDrlgRoom2, moo_ppRoomsNear1, moo_ppRoomsNear2, moo_pTileGrid1, moo_pTileGrid2, moo_pAnimTileGrid1, moo_pAnimTileGrids2);
			setup_data(original_pDrlgRoom1, original_pDrlgRoom2, original_ppRoomsNear1, original_ppRoomsNear2, original_pTileGrid1, original_pTileGrid2, original_pAnimTileGrid1, original_pAnimTileGrids2);

			// Call both implementations
			sut(&moo_pDrlgRoom1, &moo_pDrlgRoom2);
			original(&original_pDrlgRoom1, &original_pDrlgRoom2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");
		}
	}
}
