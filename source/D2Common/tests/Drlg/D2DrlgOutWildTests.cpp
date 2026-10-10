#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cstdarg>
#include <filesystem>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgGrid.h>
#include <Drlg/D2DrlgDrlgVer.h>
#include <Drlg/D2DrlgOutdoors.h>
#include <Drlg/D2DrlgOutWild.h>
#include <Drlg/D2DrlgPreset.h>

#include <Fixtures/DataTbls/Fixtures.h>

DYNAMIC_ARRAY_TYPE(int)


// Allocates the row offsets followed by the cells, as done in DRLGGRID_InitializeGridCells
static void setup_grid(D2DrlgGridStrc& pGrid, std::vector<int32_t>& cells, int width, int height)
{
	cells.assign(height * (width + 1), 0);
	for (auto i = 0; i < height; ++i)
	{
		cells[i] = i * width;
	}

	pGrid.nWidth = width;
	pGrid.nHeight = height;
	pGrid.pCellsRowOffsets = cells.data();
	pGrid.pCellsFlags = cells.data() + height;
}

// Marks the outermost cells as level border, as done by DRLGOUTPLACE_PlaceAct1245OutdoorBorders
static void mark_border_cells(D2DrlgOutdoorInfoStrc& pOutdoors, int width, int height, int nBorderLvlPrestId = 0)
{
	D2DrlgOutdoorPackedGrid2InfoStrc tBorderInfo{};
	tBorderInfo.nUnkb00 = true;

	for (auto nY = 0; nY < height; ++nY)
	{
		for (auto nX = 0; nX < width; ++nX)
		{
			if (nX == 0 || nY == 0 || nX == width - 1 || nY == height - 1)
			{
				pOutdoors.pGrid[0].pCellsFlags[nX + pOutdoors.pGrid[0].pCellsRowOffsets[nY]] = nBorderLvlPrestId;
				pOutdoors.pGrid[2].pCellsFlags[nX + pOutdoors.pGrid[2].pCellsRowOffsets[nY]] = tBorderInfo.nPackedValue;
			}
		}
	}
}


TEST_SUITE("D2DrlgOutWildTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD84CA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_GetBridgeCoords, dll_base + 0x00044CA0);

		for (auto bHasBridge : { false, true })
		{
			for (auto grid_size : { 10, 12, 16 })
			{
				for (auto iteration = 0; iteration < 4; ++iteration)
				{
					// Input data
					const auto bridge_y = static_cast<int>(random_unsigned_integer(1, grid_size - 2));

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					int moo_pX{};
					int moo_pY{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};
					int original_pX{};
					int original_pY{};

					const auto setup_data = [bHasBridge, grid_size, bridge_y](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, grid_size, grid_size);
						setup_grid(pOutdoors.pGrid[2], pGrid2, grid_size, grid_size);

						pOutdoors.nGridWidth = grid_size;
						pOutdoors.nGridHeight = grid_size;

						if (bHasBridge)
						{
							// The bridge is spawned in the middle column, on top of the upper river preset
							const auto bridge_x = grid_size / 2 - 1;
							DRLGGRID_AlterGridFlag(&pOutdoors.pGrid[0], bridge_x, bridge_y, LVLPREST_ACT1_BRIDGE, FLAG_OPERATION_OVERWRITE);

							D2DrlgOutdoorPackedGrid2InfoStrc tPackedInfo{};
							tPackedInfo.bHasPickedFile = true;
							tPackedInfo.nPickedFile = 1;
							DRLGGRID_AlterGridFlag(&pOutdoors.pGrid[2], bridge_x, bridge_y, tPackedInfo.nPackedValue, FLAG_OPERATION_OVERWRITE);
						}

						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					sut(&moo_pLevel, &moo_pX, &moo_pY);
					original(&original_pLevel, &original_pX, &original_pY);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
					MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD84D30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_InitAct1OutdoorLevel, dll_base + 0x00044D30);

		// The levels outside of Blood Moor - Tamoe Highland don't get the secondary borders and paths,
		// so no LvlSub.txt (DS1 substitution files) data is required.
		// Rogue Encampment goes through the cliff detection on the vertices, Burial Grounds spawns the graveyard.
		for (auto level_id : { LEVEL_ROGUEENCAMPMENT, LEVEL_BURIALGROUNDS })
		{
			for (auto grid_size : { 10, 12, 16 })
			{
				for (auto iteration = 0; iteration < 4; ++iteration)
				{
					// Input data
					const auto seed = random_unsigned_integer();

					// Make sure the graveyard (spawned at (1, 1)) fits into the level borders
					const auto grid_width = std::max(grid_size, DRLGPRESET_GetSizeX(LVLPREST_ACT1_GRAVEYARD) / 8 + 2);
					const auto grid_height = std::max(grid_size, DRLGPRESET_GetSizeY(LVLPREST_ACT1_GRAVEYARD) / 8 + 2);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgVertexStrc moo_pVertices[4]{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};
					D2DrlgVertexStrc original_pVertices[4]{};

					const auto setup_data = [level_id, seed, grid_width, grid_height](
						D2DrlgLevelStrc& pLevel,
						D2DrlgStrc& pDrlg,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2,
						D2DrlgVertexStrc(& pVertices)[4]
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, grid_width, grid_height);
						setup_grid(pOutdoors.pGrid[2], pGrid2, grid_width, grid_height);

						pOutdoors.nGridWidth = grid_width;
						pOutdoors.nGridHeight = grid_height;

						// Clockwise ring of vertices on the corners of the grid, without level links.
						// The level borders get placed along it by DRLGOUTPLACE_PlaceAct1245OutdoorBorders.
						pVertices[0].nPosX = 0;
						pVertices[0].nPosY = 0;
						pVertices[1].nPosX = grid_width - 1;
						pVertices[1].nPosY = 0;
						pVertices[2].nPosX = grid_width - 1;
						pVertices[2].nPosY = grid_height - 1;
						pVertices[3].nPosX = 0;
						pVertices[3].nPosY = grid_height - 1;

						for (auto i = 0; i < 4; ++i)
						{
							pVertices[i].pNext = &pVertices[(i + 1) % 4];
						}

						pOutdoors.pVertex = &pVertices[0];

						pLevel.pDrlg = &pDrlg;
						pLevel.nLevelId = level_id;
						pLevel.nLevelType = LVLTYPE_ACT1_WILDERNESS;
						pLevel.pSeed.nLowSeed = seed;
						pLevel.pSeed.nHighSeed = 666;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2, moo_pVertices);
					setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2, original_pVertices);

					// Call both implementations
					sut(&moo_pLevel);
					original(&original_pLevel);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85060")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_TestSpawnRiver, dll_base + 0x00045060);

		for (auto bBlocked : { false, true })
		{
			for (auto grid_size : { 10, 12, 16 })
			{
				for (auto iteration = 0; iteration < 4; ++iteration)
				{
					// Input data
					int nX = random_unsigned_integer(1, grid_size - 3);
					const auto blocked_x = nX + static_cast<int>(random_unsigned_integer(0, 1));
					const auto blocked_y = static_cast<int>(random_unsigned_integer(0, grid_size - 1));

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [bBlocked, grid_size, blocked_x, blocked_y](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[2], pGrid2, grid_size, grid_size);

						pOutdoors.nGridWidth = grid_size;
						pOutdoors.nGridHeight = grid_size;

						if (bBlocked)
						{
							// A cell with a direction (e.g. a cliff) in one of the two river columns prevents the river
							D2DrlgOutdoorPackedGrid2InfoStrc tPackedInfo{};
							tPackedInfo.bHasDirection = true;
							DRLGGRID_AlterGridFlag(&pOutdoors.pGrid[2], blocked_x, blocked_y, tPackedInfo.nPackedValue, FLAG_OPERATION_OVERWRITE);
						}

						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid2);
					setup_data(original_pLevel, original_pOutdoors, original_pGrid2);

					// Call both implementations
					const auto moo_result = sut(&moo_pLevel, nX);
					const auto original_result = original(&original_pLevel, nX);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD850B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnRiver, dll_base + 0x000450B0);

		// Without a bridge, with a bridge across the river and with a bridge ending at the river
		for (int outdoor_flags : { 0, (int)OUTDOOR_RIVER, (int)OUTDOOR_BRIDGE })
		{
			for (auto grid_size : { 10, 12, 16 })
			{
				for (auto iteration = 0; iteration < 4; ++iteration)
				{
					// Input data
					const auto seed = random_unsigned_integer();
					int nX = grid_size / 2 - 1;

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [outdoor_flags, seed, grid_size](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, grid_size, grid_size);
						setup_grid(pOutdoors.pGrid[2], pGrid2, grid_size, grid_size);

						pOutdoors.dwFlags = outdoor_flags;
						pOutdoors.nGridWidth = grid_size;
						pOutdoors.nGridHeight = grid_size;

						// The level borders have already been placed on the outermost grid cells
						mark_border_cells(pOutdoors, grid_size, grid_size, LVLPREST_ACT1_WILD_BORDER_1);

						pLevel.pSeed.nLowSeed = seed;
						pLevel.pSeed.nHighSeed = 666;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					sut(&moo_pLevel, nX);
					original(&original_pLevel, nX);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85300")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD85300, dll_base + 0x00045300);

		for (auto iteration = 0; iteration < 64; ++iteration)
		{
			// Input data
			D2DrlgVertexStrc moo_pDrlgVertex{};
			D2DrlgVertexStrc moo_pNext{};
			D2DrlgVertexStrc moo_pNextNext{};
			D2DrlgVertexStrc original_pDrlgVertex{};
			D2DrlgVertexStrc original_pNext{};
			D2DrlgVertexStrc original_pNextNext{};

			// Random positions on a small grid, so that all orderings of the coordinates occur
			int32_t positions[6]{};
			for (auto& position : positions)
			{
				position = random_unsigned_integer(0, 2);
			}
			const auto flags = random_unsigned_integer(0, 3);

			const auto setup_data = [&positions, flags](
				D2DrlgVertexStrc& pDrlgVertex,
				D2DrlgVertexStrc& pNext,
				D2DrlgVertexStrc& pNextNext
			) {
				pDrlgVertex.nPosX = positions[0];
				pDrlgVertex.nPosY = positions[1];
				pDrlgVertex.dwFlags = flags & 1;
				pDrlgVertex.pNext = &pNext;

				pNext.nPosX = positions[2];
				pNext.nPosY = positions[3];
				pNext.dwFlags = (flags >> 1) & 1;
				pNext.pNext = &pNextNext;

				pNextNext.nPosX = positions[4];
				pNextNext.nPosY = positions[5];
				pNextNext.pNext = &pDrlgVertex;
			};

			setup_data(moo_pDrlgVertex, moo_pNext, moo_pNextNext);
			setup_data(original_pDrlgVertex, original_pNext, original_pNextNext);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgVertex);
			const auto original_result = original(&original_pDrlgVertex);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85350")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD85350, dll_base + 0x00045350);

		for (auto iteration = 0; iteration < 64; ++iteration)
		{
			// Input data
			D2DrlgVertexStrc moo_pDrlgVertex{};
			D2DrlgVertexStrc moo_pNext{};
			D2DrlgVertexStrc original_pDrlgVertex{};
			D2DrlgVertexStrc original_pNext{};

			// Random positions on a small grid, so that all orderings of the coordinates occur
			int32_t positions[4]{};
			for (auto& position : positions)
			{
				position = random_unsigned_integer(0, 2);
			}
			const auto flags = random_unsigned_integer(0, 3);

			const auto setup_data = [&positions, flags](
				D2DrlgVertexStrc& pDrlgVertex,
				D2DrlgVertexStrc& pNext
			) {
				pDrlgVertex.nPosX = positions[0];
				pDrlgVertex.nPosY = positions[1];
				pDrlgVertex.dwFlags = flags & 1;
				pDrlgVertex.pNext = &pNext;

				pNext.nPosX = positions[2];
				pNext.nPosY = positions[3];
				pNext.dwFlags = (flags >> 1) & 1;
				pNext.pNext = &pDrlgVertex;
			};

			setup_data(moo_pDrlgVertex, moo_pNext);
			setup_data(original_pDrlgVertex, original_pNext);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgVertex);
			const auto original_result = original(&original_pDrlgVertex);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD85390")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnCliffCaves, dll_base + 0x00045390);

		// Make sure both caves fit into the level borders
		const auto cave_size_x = std::max(DRLGPRESET_GetSizeX(LVLPREST_ACT1_WILD_CLIFF_CAVE_LEFT), DRLGPRESET_GetSizeX(LVLPREST_ACT1_WILD_CLIFF_CAVE_RIGHT)) / 8;
		const auto cave_size_y = std::max(DRLGPRESET_GetSizeY(LVLPREST_ACT1_WILD_CLIFF_CAVE_LEFT), DRLGPRESET_GetSizeY(LVLPREST_ACT1_WILD_CLIFF_CAVE_RIGHT)) / 8;

		// 16 and 17 are the cliff borders which can hold the left and right cave, the others don't spawn anything
		for (auto grid_entry : { 0, 15, 16, 17, 18 })
		{
			for (auto grid_size : { 10, 12, 16 })
			{
				for (auto iteration = 0; iteration < 4; ++iteration)
				{
					// Input data
					const auto seed = random_unsigned_integer();
					int nX = random_unsigned_integer(1, grid_size - 1 - cave_size_x);
					int nY = random_unsigned_integer(1, grid_size - 1 - cave_size_y);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [grid_entry, seed, grid_size, nX, nY](
						D2DrlgLevelStrc& pLevel,
						D2DrlgStrc& pDrlg,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, grid_size, grid_size);
						setup_grid(pOutdoors.pGrid[2], pGrid2, grid_size, grid_size);

						pOutdoors.nGridWidth = grid_size;
						pOutdoors.nGridHeight = grid_size;

						// The level borders have already been placed on the outermost grid cells
						mark_border_cells(pOutdoors, grid_size, grid_size);

						DRLGGRID_AlterGridFlag(&pOutdoors.pGrid[0], nX, nY, grid_entry, FLAG_OPERATION_OVERWRITE);

						pLevel.pDrlg = &pDrlg;
						pLevel.pSeed.nLowSeed = seed;
						pLevel.pSeed.nHighSeed = 666;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					const auto moo_result = sut(&moo_pLevel, nX, nY);
					const auto original_result = original(&original_pLevel, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD853F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnTownTransitionsAndCaves, dll_base + 0x000453F0);

		// Make sure the town transitions fit into the grid
		const auto transition_size = std::max({
			DRLGPRESET_GetSizeX(LVLPREST_ACT1_TOWN_1_TRANSITION_S) / 8,
			DRLGPRESET_GetSizeY(LVLPREST_ACT1_TOWN_1_TRANSITION_S) / 8,
			DRLGPRESET_GetSizeX(LVLPREST_ACT1_TOWN_1_TRANSITION_E) / 8,
			DRLGPRESET_GetSizeY(LVLPREST_ACT1_TOWN_1_TRANSITION_E) / 8 + 1,
		});

		// The town transitions and the river are spawned with the cave entrance already placed,
		// the cave entrance is spawned on its own (Cold Plains, so the Rogue Encampment level isn't required)
		for (int outdoor_flags : { (int)OUTDOOR_SOUTHWEST, (int)OUTDOOR_NORTHWEST, (int)OUTDOOR_SOUTHEAST, (int)OUTDOOR_NORTHEAST, (int)OUTDOOR_RIVER, 0 })
		{
			for (auto grid_size : { 10, 12, 16 })
			{
				for (auto iteration = 0; iteration < 4; ++iteration)
				{
					// Input data
					const auto seed = random_unsigned_integer();
					const auto grid_width = std::max(grid_size, transition_size);
					const auto grid_height = std::max(grid_size, transition_size);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [outdoor_flags, seed, grid_width, grid_height](
						D2DrlgLevelStrc& pLevel,
						D2DrlgStrc& pDrlg,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, grid_width, grid_height);
						setup_grid(pOutdoors.pGrid[2], pGrid2, grid_width, grid_height);

						pOutdoors.dwFlags = outdoor_flags ? (outdoor_flags | OUTDOOR_OUT_CAVES) : 0;
						pOutdoors.nGridWidth = grid_width;
						pOutdoors.nGridHeight = grid_height;

						// The level borders have already been placed on the outermost grid cells
						mark_border_cells(pOutdoors, grid_width, grid_height, LVLPREST_ACT1_WILD_BORDER_1);

						pLevel.pDrlg = &pDrlg;
						pLevel.nLevelId = LEVEL_COLDPLAINS;
						pLevel.pSeed.nLowSeed = seed;
						pLevel.pSeed.nHighSeed = 666;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					sut(&moo_pLevel);
					original(&original_pLevel);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD85520")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnSpecialPresets, dll_base + 0x00045520);

		for (auto level_id : { LEVEL_BLOODMOOR, LEVEL_COLDPLAINS, LEVEL_STONYFIELD, LEVEL_DARKWOOD, LEVEL_BLACKMARSH, LEVEL_TAMOEHIGHLAND, LEVEL_BURIALGROUNDS, LEVEL_MOOMOOFARM })
		{
			for (auto grid_size : { 10, 12, 16 })
			{
				for (auto iteration = 0; iteration < 4; ++iteration)
				{
					// Input data
					const auto seed = random_unsigned_integer();

					// Make sure the graveyard (spawned at (1, 1)) fits into the level borders
					const auto grid_width = std::max(grid_size, DRLGPRESET_GetSizeX(LVLPREST_ACT1_GRAVEYARD) / 8 + 2);
					const auto grid_height = std::max(grid_size, DRLGPRESET_GetSizeY(LVLPREST_ACT1_GRAVEYARD) / 8 + 2);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [level_id, seed, grid_width, grid_height](
						D2DrlgLevelStrc& pLevel,
						D2DrlgStrc& pDrlg,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, grid_width, grid_height);
						setup_grid(pOutdoors.pGrid[2], pGrid2, grid_width, grid_height);

						pOutdoors.nGridWidth = grid_width;
						pOutdoors.nGridHeight = grid_height;

						// The level borders have already been placed on the outermost grid cells
						mark_border_cells(pOutdoors, grid_width, grid_height, LVLPREST_ACT1_WILD_BORDER_1);

						pLevel.pDrlg = &pDrlg;
						pLevel.nLevelId = level_id;
						pLevel.pSeed.nLowSeed = seed;
						pLevel.pSeed.nHighSeed = 666;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					sut(&moo_pLevel);
					original(&original_pLevel);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD85920")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTWILD_SpawnCottage, dll_base + 0x00045920);

		for (int nLvlPrestId : { LVLPREST_ACT1_COTTAGES_1, LVLPREST_ACT1_COTTAGES_2, LVLPREST_ACT1_FALLEN_CAMP_1, LVLPREST_ACT1_FALLEN_CAMP_2 })
		{
			for (int a3 : { 0, 1 })
			{
				for (auto grid_size : { 10, 12, 16 })
				{
					for (auto iteration = 0; iteration < 4; ++iteration)
					{
						// Input data
						const auto seed = random_unsigned_integer();

						D2DrlgLevelStrc moo_pLevel{};
						D2DrlgStrc moo_pDrlg{};
						D2DrlgOutdoorInfoStrc moo_pOutdoors{};
						std::vector<int32_t> moo_pGrid0{};
						std::vector<int32_t> moo_pGrid2{};
						D2DrlgLevelStrc original_pLevel{};
						D2DrlgStrc original_pDrlg{};
						D2DrlgOutdoorInfoStrc original_pOutdoors{};
						std::vector<int32_t> original_pGrid0{};
						std::vector<int32_t> original_pGrid2{};

						const auto setup_data = [seed, grid_size](
							D2DrlgLevelStrc& pLevel,
							D2DrlgStrc& pDrlg,
							D2DrlgOutdoorInfoStrc& pOutdoors,
							std::vector<int32_t>& pGrid0,
							std::vector<int32_t>& pGrid2
						) {
							setup_grid(pOutdoors.pGrid[0], pGrid0, grid_size, grid_size);
							setup_grid(pOutdoors.pGrid[2], pGrid2, grid_size, grid_size);

							pOutdoors.nGridWidth = grid_size;
							pOutdoors.nGridHeight = grid_size;

							// The level borders have already been placed on the outermost grid cells
							mark_border_cells(pOutdoors, grid_size, grid_size, LVLPREST_ACT1_WILD_BORDER_1);

							pLevel.pDrlg = &pDrlg;
							pLevel.nLevelId = LEVEL_TAMOEHIGHLAND;
							pLevel.pSeed.nLowSeed = seed;
							pLevel.pSeed.nHighSeed = 666;
							pLevel.pOutdoors = &pOutdoors;
						};

						setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
						setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2);

						// Call both implementations
						sut(&moo_pLevel, nLvlPrestId, a3);
						original(&original_pLevel, nLvlPrestId, a3);

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
						MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
						MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
					}
				}
			}
		}
	}
}
