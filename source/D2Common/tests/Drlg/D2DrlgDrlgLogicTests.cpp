#include <D2CommonTestDefines.h>

#ifdef DRLG_LOGIC_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Fog.h>
#include <D2CMP.h>
#include <Drlg/D2DrlgDrlgLogic.h>


namespace
{
	// Makes the grid use the given storage, with its rows laid out contiguously
	void setup_grid(D2DrlgGridStrc& pGrid, int32_t* pCellsFlags, int32_t* pCellsRowOffsets, int32_t nWidth, int32_t nHeight)
	{
		pGrid.pCellsFlags = pCellsFlags;
		pGrid.pCellsRowOffsets = pCellsRowOffsets;
		pGrid.nWidth = nWidth;
		pGrid.nHeight = nHeight;

		for (int32_t i = 0; i < nHeight; ++i)
		{
			pCellsRowOffsets[i] = i * nWidth;
		}
	}

	// The cells of pIndexY store pointers to the coord lists
	int32_t to_grid_entry(D2RoomCoordListStrc* pRoomCoordList)
	{
		return (int32_t)(intptr_t)pRoomCoordList;
	}
}


TEST_SUITE("D2DrlgDrlgLogicTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76420")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_FreeDrlgCoordList, dll_base + 0x00036420);

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
				// No memory pool is set, so Fog uses its default allocator
				pLevel.pDrlg = &pDrlg;
				pDrlgRoom.pLevel = &pLevel;

				// Everything owned by the logical room info gets freed, so it has to be allocated through Fog
				D2DrlgLogicalRoomInfoStrc* pLogicalRoomInfo = D2_CALLOC_STRC_POOL(nullptr, D2DrlgLogicalRoomInfoStrc);
				pLogicalRoomInfo->dwFlags = DRLGLOGIC_ROOMINFO_HAS_GRID_CELLS;
				pLogicalRoomInfo->pIndexX.pCellsRowOffsets = (int32_t*)D2_CALLOC_POOL(nullptr, sizeof(int32_t));
				pLogicalRoomInfo->pIndexY.pCellsRowOffsets = (int32_t*)D2_CALLOC_POOL(nullptr, sizeof(int32_t));
				pLogicalRoomInfo->pCoordList = D2_CALLOC_STRC_POOL(nullptr, D2RoomCoordListStrc);
				pLogicalRoomInfo->pCoordList->pNext = D2_CALLOC_STRC_POOL(nullptr, D2RoomCoordListStrc);

				pDrlgRoom.pLogicalRoomInfo = pLogicalRoomInfo;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDrlgRoom.pLogicalRoomInfo, original_pDrlgRoom.pLogicalRoomInfo, "Comparing pDrlgRoom.pLogicalRoomInfo");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76830")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_SetTileGridFlags, dll_base + 0x00036830);

		SUBCASE("")
		{
			// Input data
			D2UnkDrlgLogicStrc moo_a1{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgGridStrc moo_pIndexGrid{};
			int32_t moo_pIndexGridCells[9]{};
			int32_t moo_pIndexGridRowOffsets[3]{};
			D2DrlgGridStrc moo_pBlockingGrid{};
			int32_t moo_pBlockingGridCells[9]{};
			int32_t moo_pBlockingGridRowOffsets[3]{};
			D2DrlgGridStrc moo_pTileTypeGrid{};
			int32_t moo_pTileTypeGridCells[9]{};
			int32_t moo_pTileTypeGridRowOffsets[3]{};
			D2UnkDrlgLogicStrc original_a1{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgGridStrc original_pIndexGrid{};
			int32_t original_pIndexGridCells[9]{};
			int32_t original_pIndexGridRowOffsets[3]{};
			D2DrlgGridStrc original_pBlockingGrid{};
			int32_t original_pBlockingGridCells[9]{};
			int32_t original_pBlockingGridRowOffsets[3]{};
			D2DrlgGridStrc original_pTileTypeGrid{};
			int32_t original_pTileTypeGridCells[9]{};
			int32_t original_pTileTypeGridRowOffsets[3]{};
			int nX = 0;
			int nY = 0;
			int a4 = -1;

			const auto setup_data = [](
				D2UnkDrlgLogicStrc& a1,
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgGridStrc& pIndexGrid,
				int32_t(& pIndexGridCells)[9],
				int32_t(& pIndexGridRowOffsets)[3],
				D2DrlgGridStrc& pBlockingGrid,
				int32_t(& pBlockingGridCells)[9],
				int32_t(& pBlockingGridRowOffsets)[3],
				D2DrlgGridStrc& pTileTypeGrid,
				int32_t(& pTileTypeGridCells)[9],
				int32_t(& pTileTypeGridRowOffsets)[3]
			) {
				// 2x2 tiles room, the grids cover the room including its border, so they have 3x3 cells
				pDrlgRoom.nTileWidth = 2;
				pDrlgRoom.nTileHeight = 2;

				setup_grid(pIndexGrid, pIndexGridCells, pIndexGridRowOffsets, 3, 3);
				setup_grid(pBlockingGrid, pBlockingGridCells, pBlockingGridRowOffsets, 3, 3);
				setup_grid(pTileTypeGrid, pTileTypeGridCells, pTileTypeGridRowOffsets, 3, 3);

				// Block the center cell, its tile type decides from which directions it is filled
				pBlockingGridCells[1 + 1 * 3] = 1;
				pTileTypeGridCells[1 + 1 * 3] = 1;

				a1.pDrlgRoom = &pDrlgRoom;
				a1.field_4 = &pIndexGrid;
				a1.field_14 = &pBlockingGrid;
				a1.pTileTypeGrid = &pTileTypeGrid;
				// Must contain 0x10000000, which marks a cell as visited
				a1.nFlags = 0x10000001;
			};

			setup_data(moo_a1, moo_pDrlgRoom, moo_pIndexGrid, moo_pIndexGridCells, moo_pIndexGridRowOffsets, moo_pBlockingGrid, moo_pBlockingGridCells, moo_pBlockingGridRowOffsets, moo_pTileTypeGrid, moo_pTileTypeGridCells, moo_pTileTypeGridRowOffsets);
			setup_data(original_a1, original_pDrlgRoom, original_pIndexGrid, original_pIndexGridCells, original_pIndexGridRowOffsets, original_pBlockingGrid, original_pBlockingGridCells, original_pBlockingGridRowOffsets, original_pTileTypeGrid, original_pTileTypeGridCells, original_pTileTypeGridRowOffsets);

			// Call both implementations
			sut(&moo_a1, nX, nY, a4);
			original(&original_a1, nX, nY, a4);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
			for (int i = 0; i < 9; ++i)
			{
				MOO_CHECK_EQ(moo_pIndexGridCells[i], original_pIndexGridCells[i], "Comparing pIndexGridCells");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD769B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD769B0, dll_base + 0x000369B0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc moo_pDrlgRoomNear{};
			D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfoNear{};
			int32_t moo_pIndexYCells[4]{};
			int32_t moo_pIndexYRowOffsets[2]{};
			int32_t moo_pIndexYCellsNear[4]{};
			int32_t moo_pIndexYRowOffsetsNear[2]{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			D2RoomCoordListStrc moo_pRoomCoordListNear{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoomNear{};
			D2DrlgRoomStrc* original_ppRoomsNear[2]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfoNear{};
			int32_t original_pIndexYCells[4]{};
			int32_t original_pIndexYRowOffsets[2]{};
			int32_t original_pIndexYCellsNear[4]{};
			int32_t original_pIndexYRowOffsetsNear[2]{};
			D2RoomCoordListStrc original_pRoomCoordList{};
			D2RoomCoordListStrc original_pRoomCoordListNear{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc& pDrlgRoomNear,
				D2DrlgRoomStrc*(& ppRoomsNear)[2],
				D2DrlgLevelStrc& pLevel,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfoNear,
				int32_t(& pIndexYCells)[4],
				int32_t(& pIndexYRowOffsets)[2],
				int32_t(& pIndexYCellsNear)[4],
				int32_t(& pIndexYRowOffsetsNear)[2],
				D2RoomCoordListStrc& pRoomCoordList,
				D2RoomCoordListStrc& pRoomCoordListNear
			) {
				pLevel.nLevelId = 1;

				// Two 1x1 tiles rooms of the same level sharing their border at nX = 1
				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = 0;
				pDrlgRoom.nTileYPos = 0;
				pDrlgRoom.nTileWidth = 1;
				pDrlgRoom.nTileHeight = 1;
				pDrlgRoom.pLogicalRoomInfo = &pLogicalRoomInfo;

				pDrlgRoomNear.pLevel = &pLevel;
				pDrlgRoomNear.nTileXPos = 1;
				pDrlgRoomNear.nTileYPos = 0;
				pDrlgRoomNear.nTileWidth = 1;
				pDrlgRoomNear.nTileHeight = 1;
				pDrlgRoomNear.pLogicalRoomInfo = &pLogicalRoomInfoNear;

				ppRoomsNear[0] = &pDrlgRoom;
				ppRoomsNear[1] = &pDrlgRoomNear;
				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 2;

				// Each room has a single coord list covering all of its cells, with different indices
				pRoomCoordList.nIndex = 1;
				pLogicalRoomInfo.pCoordList = &pRoomCoordList;
				setup_grid(pLogicalRoomInfo.pIndexY, pIndexYCells, pIndexYRowOffsets, 2, 2);
				for (auto& nCell : pIndexYCells)
				{
					nCell = to_grid_entry(&pRoomCoordList);
				}

				pRoomCoordListNear.nIndex = 2;
				pLogicalRoomInfoNear.pCoordList = &pRoomCoordListNear;
				setup_grid(pLogicalRoomInfoNear.pIndexY, pIndexYCellsNear, pIndexYRowOffsetsNear, 2, 2);
				for (auto& nCell : pIndexYCellsNear)
				{
					nCell = to_grid_entry(&pRoomCoordListNear);
				}
			};

			setup_data(moo_pDrlgRoom, moo_pDrlgRoomNear, moo_ppRoomsNear, moo_pLevel, moo_pLogicalRoomInfo, moo_pLogicalRoomInfoNear, moo_pIndexYCells, moo_pIndexYRowOffsets, moo_pIndexYCellsNear, moo_pIndexYRowOffsetsNear, moo_pRoomCoordList, moo_pRoomCoordListNear);
			setup_data(original_pDrlgRoom, original_pDrlgRoomNear, original_ppRoomsNear, original_pLevel, original_pLogicalRoomInfo, original_pLogicalRoomInfoNear, original_pIndexYCells, original_pIndexYRowOffsets, original_pIndexYCellsNear, original_pIndexYRowOffsetsNear, original_pRoomCoordList, original_pRoomCoordListNear);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pRoomCoordList.nIndex, original_pRoomCoordList.nIndex, "Comparing pRoomCoordList.nIndex");
			MOO_CHECK_EQ(moo_pRoomCoordListNear.nIndex, original_pRoomCoordListNear.nIndex, "Comparing pRoomCoordListNear.nIndex");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76A90")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD76A90, dll_base + 0x00036A90);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom1{};
			D2DrlgRoomStrc moo_pDrlgRoom2{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo1{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo2{};
			int32_t moo_pIndexYCells1[4]{};
			int32_t moo_pIndexYRowOffsets1[2]{};
			int32_t moo_pIndexYCells2[4]{};
			int32_t moo_pIndexYRowOffsets2[2]{};
			D2RoomCoordListStrc moo_pRoomCoordList1{};
			D2RoomCoordListStrc moo_pRoomCoordList2{};
			D2DrlgRoomStrc original_pDrlgRoom1{};
			D2DrlgRoomStrc original_pDrlgRoom2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo1{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo2{};
			int32_t original_pIndexYCells1[4]{};
			int32_t original_pIndexYRowOffsets1[2]{};
			int32_t original_pIndexYCells2[4]{};
			int32_t original_pIndexYRowOffsets2[2]{};
			D2RoomCoordListStrc original_pRoomCoordList1{};
			D2RoomCoordListStrc original_pRoomCoordList2{};
			// On the border shared by both rooms
			int nX = 1;
			int nY = 0;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom1,
				D2DrlgRoomStrc& pDrlgRoom2,
				D2DrlgLevelStrc& pLevel,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo1,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo2,
				int32_t(& pIndexYCells1)[4],
				int32_t(& pIndexYRowOffsets1)[2],
				int32_t(& pIndexYCells2)[4],
				int32_t(& pIndexYRowOffsets2)[2],
				D2RoomCoordListStrc& pRoomCoordList1,
				D2RoomCoordListStrc& pRoomCoordList2
			) {
				pLevel.nLevelId = 1;

				// Two 1x1 tiles rooms of the same level sharing their border at nX = 1
				pDrlgRoom1.pLevel = &pLevel;
				pDrlgRoom1.nTileXPos = 0;
				pDrlgRoom1.nTileYPos = 0;
				pDrlgRoom1.nTileWidth = 1;
				pDrlgRoom1.nTileHeight = 1;
				pDrlgRoom1.pLogicalRoomInfo = &pLogicalRoomInfo1;

				pDrlgRoom2.pLevel = &pLevel;
				pDrlgRoom2.nTileXPos = 1;
				pDrlgRoom2.nTileYPos = 0;
				pDrlgRoom2.nTileWidth = 1;
				pDrlgRoom2.nTileHeight = 1;
				pDrlgRoom2.pLogicalRoomInfo = &pLogicalRoomInfo2;

				// Each room has a single coord list covering all of its cells, with different indices
				pRoomCoordList1.nIndex = 1;
				pLogicalRoomInfo1.pCoordList = &pRoomCoordList1;
				setup_grid(pLogicalRoomInfo1.pIndexY, pIndexYCells1, pIndexYRowOffsets1, 2, 2);
				for (auto& nCell : pIndexYCells1)
				{
					nCell = to_grid_entry(&pRoomCoordList1);
				}

				pRoomCoordList2.nIndex = 2;
				pLogicalRoomInfo2.pCoordList = &pRoomCoordList2;
				setup_grid(pLogicalRoomInfo2.pIndexY, pIndexYCells2, pIndexYRowOffsets2, 2, 2);
				for (auto& nCell : pIndexYCells2)
				{
					nCell = to_grid_entry(&pRoomCoordList2);
				}
			};

			setup_data(moo_pDrlgRoom1, moo_pDrlgRoom2, moo_pLevel, moo_pLogicalRoomInfo1, moo_pLogicalRoomInfo2, moo_pIndexYCells1, moo_pIndexYRowOffsets1, moo_pIndexYCells2, moo_pIndexYRowOffsets2, moo_pRoomCoordList1, moo_pRoomCoordList2);
			setup_data(original_pDrlgRoom1, original_pDrlgRoom2, original_pLevel, original_pLogicalRoomInfo1, original_pLogicalRoomInfo2, original_pIndexYCells1, original_pIndexYRowOffsets1, original_pIndexYCells2, original_pIndexYRowOffsets2, original_pRoomCoordList1, original_pRoomCoordList2);

			// Call both implementations
			sut(&moo_pDrlgRoom1, &moo_pDrlgRoom2, nX, nY);
			original(&original_pDrlgRoom1, &original_pDrlgRoom2, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");
			MOO_CHECK_EQ(moo_pRoomCoordList1.nIndex, original_pRoomCoordList1.nIndex, "Comparing pRoomCoordList1.nIndex");
			MOO_CHECK_EQ(moo_pRoomCoordList2.nIndex, original_pRoomCoordList2.nIndex, "Comparing pRoomCoordList2.nIndex");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76B90")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD76B90, dll_base + 0x00036B90);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgRoomStrc moo_pDrlgRoomNear{};
			D2DrlgRoomStrc* moo_ppRoomsNear[2]{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfoNear{};
			D2RoomCoordListStrc moo_pRoomCoordLists[2]{};
			D2RoomCoordListStrc moo_pRoomCoordListNear{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgRoomStrc original_pDrlgRoomNear{};
			D2DrlgRoomStrc* original_ppRoomsNear[2]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfoNear{};
			D2RoomCoordListStrc original_pRoomCoordLists[2]{};
			D2RoomCoordListStrc original_pRoomCoordListNear{};
			int nIndex1 = 1;
			int nIndex2 = 2;
			BOOL bNode = FALSE;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgRoomStrc& pDrlgRoomNear,
				D2DrlgRoomStrc*(& ppRoomsNear)[2],
				D2DrlgLevelStrc& pLevel,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfoNear,
				D2RoomCoordListStrc(& pRoomCoordLists)[2],
				D2RoomCoordListStrc& pRoomCoordListNear
			) {
				pLevel.nLevelId = 1;

				// Only the first coord list has the index which gets replaced
				pRoomCoordLists[0].nIndex = 1;
				pRoomCoordLists[0].pNext = &pRoomCoordLists[1];
				pRoomCoordLists[1].nIndex = 3;
				pLogicalRoomInfo.pCoordList = &pRoomCoordLists[0];

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.pLogicalRoomInfo = &pLogicalRoomInfo;

				// The near room of the same level gets its index replaced as well
				pRoomCoordListNear.nIndex = 1;
				pLogicalRoomInfoNear.pCoordList = &pRoomCoordListNear;

				pDrlgRoomNear.pLevel = &pLevel;
				pDrlgRoomNear.pLogicalRoomInfo = &pLogicalRoomInfoNear;

				ppRoomsNear[0] = &pDrlgRoom;
				ppRoomsNear[1] = &pDrlgRoomNear;
				pDrlgRoom.ppRoomsNear = ppRoomsNear;
				pDrlgRoom.nRoomsNear = 2;
			};

			setup_data(moo_pDrlgRoom, moo_pDrlgRoomNear, moo_ppRoomsNear, moo_pLevel, moo_pLogicalRoomInfo, moo_pLogicalRoomInfoNear, moo_pRoomCoordLists, moo_pRoomCoordListNear);
			setup_data(original_pDrlgRoom, original_pDrlgRoomNear, original_ppRoomsNear, original_pLevel, original_pLogicalRoomInfo, original_pLogicalRoomInfoNear, original_pRoomCoordLists, original_pRoomCoordListNear);

			// Call both implementations
			sut(&moo_pDrlgRoom, nIndex1, nIndex2, bNode);
			original(&original_pDrlgRoom, nIndex1, nIndex2, bNode);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			for (int i = 0; i < 2; ++i)
			{
				MOO_CHECK_EQ(moo_pRoomCoordLists[i].nIndex, original_pRoomCoordLists[i].nIndex, "Comparing pRoomCoordLists.nIndex");
			}
			MOO_CHECK_EQ(moo_pRoomCoordListNear.nIndex, original_pRoomCoordListNear.nIndex, "Comparing pRoomCoordListNear.nIndex");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76C20" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_CheckLayer1ButNotWallObject, dll_base + 0x00036C20);

		SUBCASE("")
		{
			// Input data
			D2DrlgTileDataStrc moo_pTileData{};
			D2DrlgTileDataStrc original_pTileData{};

			const auto setup_data = [](
				D2DrlgTileDataStrc& pTileData
			) {
				// Wall layer 1 is stored as layer + 1
				pTileData.dwFlags = 2 << MAPTILE_WALL_LAYER_BIT;
				pTileData.nTileType = TILETYPE_WALL_LEFT;
			};

			setup_data(moo_pTileData);
			setup_data(original_pTileData);

			// Call both implementations
			const auto moo_result = sut(&moo_pTileData);
			const auto original_result = original(&original_pTileData);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTileData, original_pTileData, "Comparing pTileData");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76C50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_SetCoordListForTiles, dll_base + 0x00036C50);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgTileGridStrc moo_pTileGrid{};
			D2DrlgTileDataStrc moo_pWallTiles[2]{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo{};
			int32_t moo_pIndexYCells[4]{};
			int32_t moo_pIndexYRowOffsets[2]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgTileGridStrc original_pTileGrid{};
			D2DrlgTileDataStrc original_pWallTiles[2]{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo{};
			int32_t original_pIndexYCells[4]{};
			int32_t original_pIndexYRowOffsets[2]{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgTileGridStrc& pTileGrid,
				D2DrlgTileDataStrc(& pWallTiles)[2],
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo,
				int32_t(& pIndexYCells)[4],
				int32_t(& pIndexYRowOffsets)[2]
			) {
				pWallTiles[0].nPosX = 0;
				pWallTiles[0].nPosY = 0;
				pWallTiles[1].nPosX = 1;
				pWallTiles[1].nPosY = 1;

				pTileGrid.pTiles.pWallTiles = pWallTiles;
				pTileGrid.pTiles.nWalls = 2;
				pDrlgRoom.pTileGrid = &pTileGrid;

				// The wall tiles get the entries of pIndexY at their positions
				setup_grid(pLogicalRoomInfo.pIndexY, pIndexYCells, pIndexYRowOffsets, 2, 2);
				pIndexYCells[0] = 1;
				pIndexYCells[1] = 2;
				pIndexYCells[2] = 3;
				pIndexYCells[3] = 4;
				pDrlgRoom.pLogicalRoomInfo = &pLogicalRoomInfo;
			};

			setup_data(moo_pDrlgRoom, moo_pTileGrid, moo_pWallTiles, moo_pLogicalRoomInfo, moo_pIndexYCells, moo_pIndexYRowOffsets);
			setup_data(original_pDrlgRoom, original_pTileGrid, original_pWallTiles, original_pLogicalRoomInfo, original_pIndexYCells, original_pIndexYRowOffsets);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			for (int i = 0; i < 2; ++i)
			{
				MOO_CHECK_EQ(moo_pWallTiles[i], original_pWallTiles[i], "Comparing pWallTiles");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76CF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_AssignCoordListsForGrids, dll_base + 0x00036CF0);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLogicalRoomInfoStrc moo_pDrlgCoordList{};
			int32_t moo_pIndexXCells[4]{};
			int32_t moo_pIndexXRowOffsets[2]{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLogicalRoomInfoStrc original_pDrlgCoordList{};
			int32_t original_pIndexXCells[4]{};
			int32_t original_pIndexXRowOffsets[2]{};
			int nLists = 1;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgLogicalRoomInfoStrc& pDrlgCoordList,
				int32_t(& pIndexXCells)[4],
				int32_t(& pIndexXRowOffsets)[2]
			) {
				// No memory pool is set, so Fog uses its default allocator
				pLevel.pDrlg = &pDrlg;
				pDrlgRoom.pLevel = &pLevel;

				// 1x1 tiles room, the grids cover the room including its border, so they have 2x2 cells
				pDrlgRoom.nTileXPos = 2;
				pDrlgRoom.nTileYPos = 3;
				pDrlgRoom.nTileWidth = 1;
				pDrlgRoom.nTileHeight = 1;

				// One index per row, the second row being a node
				setup_grid(pDrlgCoordList.pIndexX, pIndexXCells, pIndexXRowOffsets, 2, 2);
				pIndexXCells[0] = 0x10000001;
				pIndexXCells[1] = 0x10000001;
				pIndexXCells[2] = 0x30000002;
				pIndexXCells[3] = 0x30000002;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg, moo_pDrlgCoordList, moo_pIndexXCells, moo_pIndexXRowOffsets);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg, original_pDrlgCoordList, original_pIndexXCells, original_pIndexXRowOffsets);

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_pDrlgCoordList, nLists);
			original(&original_pDrlgRoom, &original_pDrlgCoordList, nLists);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pDrlgCoordList, original_pDrlgCoordList, "Comparing pDrlgCoordList");

			// Compare the allocated coord lists
			D2RoomCoordListStrc* moo_pRoomCoordList = moo_pDrlgCoordList.pCoordList;
			D2RoomCoordListStrc* original_pRoomCoordList = original_pDrlgCoordList.pCoordList;
			while (moo_pRoomCoordList && original_pRoomCoordList)
			{
				for (int i = 0; i < 2; ++i)
				{
					MOO_CHECK_EQ(moo_pRoomCoordList->pBox[i].nPosX, original_pRoomCoordList->pBox[i].nPosX, "Comparing pCoordList.pBox.nPosX");
					MOO_CHECK_EQ(moo_pRoomCoordList->pBox[i].nPosY, original_pRoomCoordList->pBox[i].nPosY, "Comparing pCoordList.pBox.nPosY");
					MOO_CHECK_EQ(moo_pRoomCoordList->pBox[i].nWidth, original_pRoomCoordList->pBox[i].nWidth, "Comparing pCoordList.pBox.nWidth");
					MOO_CHECK_EQ(moo_pRoomCoordList->pBox[i].nHeight, original_pRoomCoordList->pBox[i].nHeight, "Comparing pCoordList.pBox.nHeight");
				}
				MOO_CHECK_EQ(moo_pRoomCoordList->bNode, original_pRoomCoordList->bNode, "Comparing pCoordList.bNode");
				MOO_CHECK_EQ(moo_pRoomCoordList->nIndex, original_pRoomCoordList->nIndex, "Comparing pCoordList.nIndex");

				moo_pRoomCoordList = moo_pRoomCoordList->pNext;
				original_pRoomCoordList = original_pRoomCoordList->pNext;
			}
			MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pCoordList lengths");

			// Free the allocated memory
			for (D2DrlgLogicalRoomInfoStrc* pDrlgCoordList : { &moo_pDrlgCoordList, &original_pDrlgCoordList })
			{
				D2_FREE_POOL(nullptr, pDrlgCoordList->pIndexY.pCellsRowOffsets);

				D2RoomCoordListStrc* pRoomCoordList = pDrlgCoordList->pCoordList;
				while (pRoomCoordList)
				{
					D2RoomCoordListStrc* pNext = pRoomCoordList->pNext;
					D2_FREE_POOL(nullptr, pRoomCoordList);
					pRoomCoordList = pNext;
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76F90")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_AllocCoordLists, dll_base + 0x00036F90);

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
				// No memory pool is set, so Fog uses its default allocator
				pLevel.pDrlg = &pDrlg;
				pDrlgRoom.pLevel = &pLevel;

				pDrlgRoom.nTileXPos = 2;
				pDrlgRoom.nTileYPos = 3;
				pDrlgRoom.nTileWidth = 4;
				pDrlgRoom.nTileHeight = 5;
			};

			setup_data(moo_pDrlgRoom, moo_pLevel, moo_pDrlg);
			setup_data(original_pDrlgRoom, original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			MOO_CHECK_EQ(moo_pLevel.nCoordLists, original_pLevel.nCoordLists, "Comparing pLevel.nCoordLists");

			// Compare the allocated logical room info
			D2DrlgLogicalRoomInfoStrc* moo_pLogicalRoomInfo = moo_pDrlgRoom.pLogicalRoomInfo;
			D2DrlgLogicalRoomInfoStrc* original_pLogicalRoomInfo = original_pDrlgRoom.pLogicalRoomInfo;
			REQUIRE(moo_pLogicalRoomInfo != nullptr);
			REQUIRE(original_pLogicalRoomInfo != nullptr);
			MOO_CHECK_EQ(moo_pLogicalRoomInfo->dwFlags, original_pLogicalRoomInfo->dwFlags, "Comparing pLogicalRoomInfo.dwFlags");
			MOO_CHECK_EQ(moo_pLogicalRoomInfo->nLists, original_pLogicalRoomInfo->nLists, "Comparing pLogicalRoomInfo.nLists");

			D2RoomCoordListStrc* moo_pRoomCoordList = moo_pLogicalRoomInfo->pCoordList;
			D2RoomCoordListStrc* original_pRoomCoordList = original_pLogicalRoomInfo->pCoordList;
			REQUIRE(moo_pRoomCoordList != nullptr);
			REQUIRE(original_pRoomCoordList != nullptr);
			for (int i = 0; i < 2; ++i)
			{
				MOO_CHECK_EQ(moo_pRoomCoordList->pBox[i].nPosX, original_pRoomCoordList->pBox[i].nPosX, "Comparing pCoordList.pBox.nPosX");
				MOO_CHECK_EQ(moo_pRoomCoordList->pBox[i].nPosY, original_pRoomCoordList->pBox[i].nPosY, "Comparing pCoordList.pBox.nPosY");
				MOO_CHECK_EQ(moo_pRoomCoordList->pBox[i].nWidth, original_pRoomCoordList->pBox[i].nWidth, "Comparing pCoordList.pBox.nWidth");
				MOO_CHECK_EQ(moo_pRoomCoordList->pBox[i].nHeight, original_pRoomCoordList->pBox[i].nHeight, "Comparing pCoordList.pBox.nHeight");
			}
			MOO_CHECK_EQ(moo_pRoomCoordList->nIndex, original_pRoomCoordList->nIndex, "Comparing pCoordList.nIndex");

			// Free the allocated memory
			D2_FREE_POOL(nullptr, moo_pRoomCoordList);
			D2_FREE_POOL(nullptr, original_pRoomCoordList);
			D2_FREE_POOL(nullptr, moo_pLogicalRoomInfo);
			D2_FREE_POOL(nullptr, original_pLogicalRoomInfo);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77080")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_GetRoomCoordListIndex, dll_base + 0x00037080);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo{};
			int32_t moo_pIndexYCells[4]{};
			int32_t moo_pIndexYRowOffsets[2]{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo{};
			int32_t original_pIndexYCells[4]{};
			int32_t original_pIndexYRowOffsets[2]{};
			D2RoomCoordListStrc original_pRoomCoordList{};
			// Subtile coordinates, they correspond to the tile (2, 1) of the level, i.e. the cell (1, 0) of the room
			int nX = 10;
			int nY = 5;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo,
				int32_t(& pIndexYCells)[4],
				int32_t(& pIndexYRowOffsets)[2],
				D2RoomCoordListStrc& pRoomCoordList
			) {
				pDrlgRoom.nTileXPos = 1;
				pDrlgRoom.nTileYPos = 1;
				pDrlgRoom.nTileWidth = 1;
				pDrlgRoom.nTileHeight = 1;

				pRoomCoordList.nIndex = 3;

				setup_grid(pLogicalRoomInfo.pIndexY, pIndexYCells, pIndexYRowOffsets, 2, 2);
				pIndexYCells[1] = to_grid_entry(&pRoomCoordList);
				pDrlgRoom.pLogicalRoomInfo = &pLogicalRoomInfo;
			};

			setup_data(moo_pDrlgRoom, moo_pLogicalRoomInfo, moo_pIndexYCells, moo_pIndexYRowOffsets, moo_pRoomCoordList);
			setup_data(original_pDrlgRoom, original_pLogicalRoomInfo, original_pIndexYCells, original_pIndexYRowOffsets, original_pRoomCoordList);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nX, nY);
			const auto original_result = original(&original_pDrlgRoom, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77110")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD77110, dll_base + 0x00037110);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo{};
			int32_t moo_pIndexYCells[4]{};
			int32_t moo_pIndexYRowOffsets[2]{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo{};
			int32_t original_pIndexYCells[4]{};
			int32_t original_pIndexYRowOffsets[2]{};
			D2RoomCoordListStrc original_pRoomCoordList{};
			// Subtile coordinates, they correspond to the tile (2, 1) of the level, i.e. the cell (1, 0) of the room
			int nX = 10;
			int nY = 5;

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo,
				int32_t(& pIndexYCells)[4],
				int32_t(& pIndexYRowOffsets)[2],
				D2RoomCoordListStrc& pRoomCoordList
			) {
				pDrlgRoom.nTileXPos = 1;
				pDrlgRoom.nTileYPos = 1;
				pDrlgRoom.nTileWidth = 1;
				pDrlgRoom.nTileHeight = 1;

				pRoomCoordList.nIndex = 3;

				setup_grid(pLogicalRoomInfo.pIndexY, pIndexYCells, pIndexYRowOffsets, 2, 2);
				pIndexYCells[1] = to_grid_entry(&pRoomCoordList);
				pDrlgRoom.pLogicalRoomInfo = &pLogicalRoomInfo;
			};

			setup_data(moo_pDrlgRoom, moo_pLogicalRoomInfo, moo_pIndexYCells, moo_pIndexYRowOffsets, moo_pRoomCoordList);
			setup_data(original_pDrlgRoom, original_pLogicalRoomInfo, original_pIndexYCells, original_pIndexYRowOffsets, original_pRoomCoordList);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom, nX, nY);
			const auto original_result = original(&original_pDrlgRoom, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			REQUIRE(moo_result == &moo_pRoomCoordList);
			REQUIRE(original_result == &original_pRoomCoordList);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD77190")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGLOGIC_GetRoomCoordList, dll_base + 0x00037190);

		SUBCASE("")
		{
			// Input data
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc moo_pLogicalRoomInfo{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			D2DrlgRoomStrc original_pDrlgRoom{};
			D2DrlgLogicalRoomInfoStrc original_pLogicalRoomInfo{};
			D2RoomCoordListStrc original_pRoomCoordList{};

			const auto setup_data = [](
				D2DrlgRoomStrc& pDrlgRoom,
				D2DrlgLogicalRoomInfoStrc& pLogicalRoomInfo,
				D2RoomCoordListStrc& pRoomCoordList
			) {
				pRoomCoordList.nIndex = 1;

				pLogicalRoomInfo.dwFlags = DRLGLOGIC_ROOMINFO_HAS_COORD_LIST;
				pLogicalRoomInfo.nLists = 1;
				pLogicalRoomInfo.pCoordList = &pRoomCoordList;
				pDrlgRoom.pLogicalRoomInfo = &pLogicalRoomInfo;
			};

			setup_data(moo_pDrlgRoom, moo_pLogicalRoomInfo, moo_pRoomCoordList);
			setup_data(original_pDrlgRoom, original_pLogicalRoomInfo, original_pRoomCoordList);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			REQUIRE(moo_result == &moo_pRoomCoordList);
			REQUIRE(original_result == &original_pRoomCoordList);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
}

#endif
