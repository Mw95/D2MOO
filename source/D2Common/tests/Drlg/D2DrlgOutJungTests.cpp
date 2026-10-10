#include <D2CommonTestDefines.h>

#ifdef DRLG_OUTJUNG_TESTS

#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cstdarg>
#include <filesystem>
#include <tuple>
#include <utility>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2DataTbls.h>
#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Drlg/D2DrlgDrlgGrid.h>
#include <Drlg/D2DrlgOutdoors.h>
#include <Drlg/D2DrlgOutJung.h>
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


TEST_SUITE("D2DrlgOutJungTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<LvlPrestTxtFixture<NoopFixture>>>, "D2Common.0x6FD7FC20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTJUNG_BuildJungle, dll_base + 0x0003FC20);
		
		for (auto level_id : { LEVEL_SPIDERFOREST, LEVEL_GREATMARSH, LEVEL_FLAYERJUNGLE })
		{
			for (auto difficulty = 0; difficulty < 3; ++difficulty)
			{
				for (auto iteration = 0; iteration < 4; ++iteration)
				{
					// Input data
					const auto seed = random_unsigned_integer();

					// The level is made of nSizeX * nSizeY blocks of 32x32 tiles (4x4 grid cells)
					const auto size_x = static_cast<int>(leveldefs_txt[LEVEL_SPIDERFOREST].dwSizeX[difficulty] >> 5);
					const auto size_y = static_cast<int>(leveldefs_txt[LEVEL_SPIDERFOREST].dwSizeY[difficulty] >> 5);

					// Make sure the head and tail presets also fit into the grid
					const auto grid_width = std::max({ 4 * size_x, DRLGPRESET_GetSizeX(LVLPREST_ACT3_JUNGLE_HEAD) / 8, DRLGPRESET_GetSizeX(LVLPREST_ACT3_JUNGLE_TAIL) / 8 });
					const auto grid_height = std::max({ 4 * size_y, 4 * (size_y - 1) + DRLGPRESET_GetSizeY(LVLPREST_ACT3_JUNGLE_HEAD) / 8, DRLGPRESET_GetSizeY(LVLPREST_ACT3_JUNGLE_TAIL) / 8 });

					// Jungle definitions: empty blocks, regular jungle presets and at most 3 clearings
					std::vector<int32_t> jungle_defs(size_x * size_y);
					auto clearings = 0;
					for (auto& jungle_def : jungle_defs)
					{
						switch (random_unsigned_integer(0, 2))
						{
						case 0:
							jungle_def = 0;
							break;

						case 1:
							jungle_def = random_unsigned_integer(LVLPREST_ACT3_JUNGLE_W, LVLPREST_ACT3_JUNGLE_NSE_W);
							break;

						default:
							if (clearings < 3)
							{
								jungle_def = random_unsigned_integer(LVLPREST_ACT3_CLEARING_WEBBY_W, LVLPREST_ACT3_CLEARING_WEBBY_NS);
								++clearings;
							}
							else
							{
								jungle_def = random_unsigned_integer(LVLPREST_ACT3_JUNGLE_W, LVLPREST_ACT3_JUNGLE_NSE_W);
							}
							break;
						}
					}

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pJungleDefs{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pJungleDefs{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [level_id, difficulty, seed, grid_width, grid_height, &jungle_defs, clearings](
						D2DrlgLevelStrc& pLevel,
						D2DrlgStrc& pDrlg,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pJungleDefs,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						pDrlg.nDifficulty = difficulty;

						setup_grid(pOutdoors.pGrid[0], pGrid0, grid_width, grid_height);
						setup_grid(pOutdoors.pGrid[2], pGrid2, grid_width, grid_height);

						pOutdoors.nGridWidth = grid_width;
						pOutdoors.nGridHeight = grid_height;

						pJungleDefs = jungle_defs;

						pLevel.pDrlg = &pDrlg;
						pLevel.nLevelId = level_id;
						pLevel.pSeed.nLowSeed = seed;
						pLevel.pSeed.nHighSeed = 666;
						pLevel.pOutdoors = &pOutdoors;
						pLevel.pJungleDefs = pJungleDefs.data();
						pLevel.nJungleDefs = clearings;
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pJungleDefs, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pJungleDefs, original_pGrid0, original_pGrid2);

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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7FE50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTJUNG_BuildLowerKurast, dll_base + 0x0003FE50);
		
		for (auto jungle_interlink : { FALSE, TRUE })
		{
			for (auto size_in_cells : { 4, 8, 12, 16 })
			{
				// Input data
				const auto seed = random_unsigned_integer();
				const auto width = 8 * size_in_cells;
				const auto height = 8 * size_in_cells;

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

				const auto setup_data = [jungle_interlink, seed, width, height](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid0,
					std::vector<int32_t>& pGrid2
				) {
					pDrlg.bJungleInterlink = jungle_interlink;

					const auto grid_width = width / 8;
					const auto grid_height = height / 8;
					setup_grid(pOutdoors.pGrid[0], pGrid0, grid_width, grid_height);
					setup_grid(pOutdoors.pGrid[2], pGrid2, grid_width, grid_height);

					pOutdoors.nGridWidth = grid_width;
					pOutdoors.nGridHeight = grid_height;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_LOWERKURAST;
					pLevel.pSeed.nLowSeed = seed;
					pLevel.pSeed.nHighSeed = 666;
					pLevel.nWidth = width;
					pLevel.nHeight = height;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7FFA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTJUNG_BuildKurastBazaar, dll_base + 0x0003FFA0);
		
		for (auto jungle_interlink : { FALSE, TRUE })
		{
			for (auto size_in_cells : { 4, 8, 12, 16 })
			{
				// Input data
				const auto seed = random_unsigned_integer();
				const auto width = 8 * size_in_cells;
				const auto height = 8 * size_in_cells;

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

				const auto setup_data = [jungle_interlink, seed, width, height](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid0,
					std::vector<int32_t>& pGrid2
				) {
					pDrlg.bJungleInterlink = jungle_interlink;

					const auto grid_width = width / 8;
					const auto grid_height = height / 8;
					setup_grid(pOutdoors.pGrid[0], pGrid0, grid_width, grid_height);
					setup_grid(pOutdoors.pGrid[2], pGrid2, grid_width, grid_height);

					pOutdoors.nGridWidth = grid_width;
					pOutdoors.nGridHeight = grid_height;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_KURASTBAZAAR;
					pLevel.pSeed.nLowSeed = seed;
					pLevel.pSeed.nHighSeed = 666;
					pLevel.nWidth = width;
					pLevel.nHeight = height;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD800E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTJUNG_BuildUpperKurast, dll_base + 0x000400E0);
		
		for (auto jungle_interlink : { FALSE, TRUE })
		{
			for (auto size_in_cells : { 4, 8, 12, 16 })
			{
				// Input data
				const auto seed = random_unsigned_integer();
				const auto width = 8 * size_in_cells;
				const auto height = 8 * size_in_cells;

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

				const auto setup_data = [jungle_interlink, seed, width, height](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid0,
					std::vector<int32_t>& pGrid2
				) {
					pDrlg.bJungleInterlink = jungle_interlink;

					const auto grid_width = width / 8;
					const auto grid_height = height / 8;
					setup_grid(pOutdoors.pGrid[0], pGrid0, grid_width, grid_height);
					setup_grid(pOutdoors.pGrid[2], pGrid2, grid_width, grid_height);

					pOutdoors.nGridWidth = grid_width;
					pOutdoors.nGridHeight = grid_height;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_UPPERKURAST;
					pLevel.pSeed.nLowSeed = seed;
					pLevel.pSeed.nHighSeed = 666;
					pLevel.nWidth = width;
					pLevel.nHeight = height;
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
	
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD80230")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTJUNG_SpawnRandomPreset, dll_base + 0x00040230);
		
		// Same arguments as used by DRLGOUTPLACE for the Lower Kurast
		const std::tuple<int, int, int> arguments[] = {
			{ LVLPREST_ACT3_SLUMS_16X16, LVLPREST_ACT3_SLUMS_16X16, 4 },
			{ LVLPREST_ACT3_SLUMS_08X16, LVLPREST_ACT3_SLUMS_16X08, 0 },
			{ LVLPREST_ACT3_SLUMS_08X08, LVLPREST_ACT3_SLUMS_08X08, 0 },
		};

		for (const auto& [level_prest_id1, level_prest_id2, max_presets] : arguments)
		{
			for (auto size_in_cells : { 4, 8, 12, 16 })
			{
				// Input data
				const auto seed = random_unsigned_integer();
				const auto grid_width = size_in_cells;
				const auto grid_height = size_in_cells;

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
				int nLevelPrestId1 = level_prest_id1;
				int nLevelPrestId2 = level_prest_id2;
				int a4 = max_presets;

				const auto setup_data = [seed, grid_width, grid_height](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid0,
					std::vector<int32_t>& pGrid2
				) {
					setup_grid(pOutdoors.pGrid[0], pGrid0, grid_width, grid_height);
					setup_grid(pOutdoors.pGrid[2], pGrid2, grid_width, grid_height);

					// Mark the border cells as already occupied (like after DRLGOUTJUNG_BuildLowerKurast)
					D2DrlgOutdoorPackedGrid2InfoStrc tPackedInfo{ 0 };
					tPackedInfo.bHasPickedFile = true;
					for (auto y = 0; y < grid_height; ++y)
					{
						for (auto x = 0; x < grid_width; ++x)
						{
							if (x == 0 || y == 0 || x == grid_width - 1 || y == grid_height - 1)
							{
								pGrid2[grid_height + y * grid_width + x] = tPackedInfo.nPackedValue;
							}
						}
					}

					pOutdoors.nGridWidth = grid_width;
					pOutdoors.nGridHeight = grid_height;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_LOWERKURAST;
					pLevel.pSeed.nLowSeed = seed;
					pLevel.pSeed.nHighSeed = 666;
					pLevel.pOutdoors = &pOutdoors;
				};

				setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
				setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2);

				// Call both implementations
				sut(&moo_pLevel, nLevelPrestId1, nLevelPrestId2, a4);
				original(&original_pLevel, nLevelPrestId1, nLevelPrestId2, a4);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
			}
		}
	}
}

#endif
