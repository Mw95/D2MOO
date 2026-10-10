#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgGrid.h>
#include <Drlg/D2DrlgDrlgVer.h>
#include <Drlg/D2DrlgOutDesr.h>
#include <Drlg/D2DrlgOutdoors.h>

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


TEST_SUITE("D2DrlgOutDesrTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7D430")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_InitAct2OutdoorLevel, dll_base + 0x0003D430);
		
		// Valley of Snakes only gets its borders and exit, so no LvlSub.txt (DS1 substitution files) data is required
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
				D2DrlgVertexStrc moo_pVertices[4]{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgOutdoorInfoStrc original_pOutdoors{};
				std::vector<int32_t> original_pGrid0{};
				std::vector<int32_t> original_pGrid2{};
				D2DrlgVertexStrc original_pVertices[4]{};

				const auto setup_data = [seed, grid_size](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid0,
					std::vector<int32_t>& pGrid2,
					D2DrlgVertexStrc(& pVertices)[4]
				) {
					setup_grid(pOutdoors.pGrid[0], pGrid0, grid_size, grid_size);
					setup_grid(pOutdoors.pGrid[2], pGrid2, grid_size, grid_size);

					pOutdoors.nGridWidth = grid_size;
					pOutdoors.nGridHeight = grid_size;

					// Clockwise ring of vertices on the corners of the grid, without level links.
					// The level borders get placed along it by DRLGOUTPLACE_PlaceAct1245OutdoorBorders.
					pVertices[0].nPosX = 0;
					pVertices[0].nPosY = 0;
					pVertices[1].nPosX = grid_size - 1;
					pVertices[1].nPosY = 0;
					pVertices[2].nPosX = grid_size - 1;
					pVertices[2].nPosY = grid_size - 1;
					pVertices[3].nPosX = 0;
					pVertices[3].nPosY = grid_size - 1;

					for (auto i = 0; i < 4; ++i)
					{
						pVertices[i].pNext = &pVertices[(i + 1) % 4];
					}

					pOutdoors.pVertex = &pVertices[0];

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_VALLEYOFSNAKES;
					pLevel.nLevelType = LVLTYPE_ACT2_DESERT;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7D870")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlacePresetVariants, dll_base + 0x0003D870);
		
		const int pLevelPrestIds[] = { LVLPREST_ACT2_DESERT_OASIS_1, LVLPREST_ACT2_DESERT_RUINS_08X08, LVLPREST_ACT2_DESERT_FILL_HEAD_2, LVLPREST_ACT2_DESERT_FILL_MESA_1 };
		const unsigned int nVariants = ARRAY_SIZE(pLevelPrestIds);

		for (auto bIterateFiles : { FALSE, TRUE })
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
						mark_border_cells(pOutdoors, grid_size, grid_size);

						pLevel.pDrlg = &pDrlg;
						pLevel.nLevelId = LEVEL_DRYHILLS;
						pLevel.pSeed.nLowSeed = seed;
						pLevel.pSeed.nHighSeed = 666;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					sut(&moo_pLevel, pLevelPrestIds, nVariants, bIterateFiles);
					original(&original_pLevel, pLevelPrestIds, nVariants, bIterateFiles);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(LvlSubTxtFixture<LvlPrestTxtFixture<NoopFixture>>, "D2Common.0x6FD7D9B0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceBorders, dll_base + 0x0003D9B0);
		
		// The secondary borders are loaded from the LvlSub.txt substitution files (DS1)
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
					mark_border_cells(pOutdoors, grid_size, grid_size, LVLPREST_ACT2_DESERT_BORDER_1);

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_ROCKYWASTE;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7D9F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_AddExits, dll_base + 0x0003D9F0);
		
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
					mark_border_cells(pOutdoors, grid_size, grid_size);

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_ROCKYWASTE;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7DA60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceFillsInFarOasis, dll_base + 0x0003DA60);
		
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
					mark_border_cells(pOutdoors, grid_size, grid_size);

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_FAROASIS;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7DAC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceRuinsInLostCity, dll_base + 0x0003DAC0);
		
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
					mark_border_cells(pOutdoors, grid_size, grid_size);

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_LOSTCITY;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7DB00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceFillsInLostCity, dll_base + 0x0003DB00);
		
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
					mark_border_cells(pOutdoors, grid_size, grid_size);

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_LOSTCITY;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7DBC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDESR_PlaceFillsInCanyon, dll_base + 0x0003DBC0);
		
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
					mark_border_cells(pOutdoors, grid_size, grid_size);

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_CANYONOFTHEMAGI;
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
