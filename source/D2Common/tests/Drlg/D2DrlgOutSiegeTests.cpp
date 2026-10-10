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
#include <Drlg/D2DrlgOutdoors.h>
#include <Drlg/D2DrlgOutSiege.h>

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

static int32_t& grid_cell(D2DrlgGridStrc& pGrid, int nX, int nY)
{
	return pGrid.pCellsFlags[nX + pGrid.pCellsRowOffsets[nY]];
}


TEST_SUITE("D2DrlgOutSiegeTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD84100")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD84100, dll_base + 0x00044100);

		SUBCASE("")
		{
			for (auto nLevelId : { LEVEL_ID_ACT5_BARRICADE_1, LEVEL_ARREATPLATEAU, LEVEL_TUNDRAWASTELANDS })
			{
				// Input data
				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgLevelStrc original_pLevel{};

				const auto setup_data = [nLevelId](
					D2DrlgLevelStrc& pLevel
				) {
					pLevel.nLevelId = nLevelId;
				};

				CAPTURE(nLevelId);

				setup_data(moo_pLevel);
				setup_data(original_pLevel);

				// Call both implementations
				const auto moo_result = sut(&moo_pLevel);
				const auto original_result = original(&original_pLevel);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			}
		}
	}

	// NOTE: Only the Bloody Foothills branch is tested. The other branch requires a full vertex setup and
	// adds a secondary border via DRLGTILESUB_AddSecondaryBorder, which loads DS1 files from the archive.
	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD84110")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTSIEGE_InitAct5OutdoorLevel, dll_base + 0x00044110);

		SUBCASE("")
		{
			// The level is filled from right to left with the 15 siege presets
			const auto nPresetWidth = lvlprest_txt[LVLPREST_ACT5_SIEGE_TO_TOWN].nSizeX / 8;
			auto nGridHeight = 0;
			for (auto i = 0; i < 15; ++i)
			{
				nGridHeight = std::max(nGridHeight, lvlprest_txt[LVLPREST_ACT5_SIEGE_TO_TOWN + i].nSizeY / 8);
			}
			const auto nGridWidth = 15 * nPresetWidth;

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			std::vector<int32_t> moo_pGrid0{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			std::vector<int32_t> original_pGrid0{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [nGridWidth, nGridHeight](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid0,
				std::vector<int32_t>& pGrid2
			) {
				pLevel.nLevelId = LEVEL_BLOODYFOOTHILLS;
				pLevel.nWidth = 8 * nGridWidth;
				pLevel.nHeight = 8 * nGridHeight;
				pLevel.pOutdoors = &pOutdoors;

				pOutdoors.nWidth = pLevel.nWidth;
				pOutdoors.nHeight = pLevel.nHeight;
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
			setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD844F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTSIEGE_PlaceCaves, dll_base + 0x000444F0);

		SUBCASE("")
		{
			for (auto nLevelId : { LEVEL_ARREATPLATEAU, LEVEL_TUNDRAWASTELANDS })
			{
				// Covers both the nWidth <= nHeight and the nWidth > nHeight case
				for (auto bWide : { false, true })
				{
					const auto nGridWidth = bWide ? 18 : 16;
					const auto nGridHeight = bWide ? 16 : 18;

					// Input data
					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [nLevelId, nGridWidth, nGridHeight](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						pLevel.nLevelId = nLevelId;
						pLevel.nWidth = 8 * nGridWidth;
						pLevel.nHeight = 8 * nGridHeight;
						pLevel.pOutdoors = &pOutdoors;

						pOutdoors.nWidth = pLevel.nWidth;
						pOutdoors.nHeight = pLevel.nHeight;
						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;

						setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
						setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);
					};

					CAPTURE(nLevelId);
					CAPTURE(bWide);

					setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

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

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD84580")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTSIEGE_PlaceBarricadeEntrancesAndExits, dll_base + 0x00044580);

		SUBCASE("")
		{
			const auto nGridWidth = 18;
			const auto nGridHeight = 18;

			// Input data
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
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			const auto setup_data = [nGridWidth, nGridHeight, low_seed, high_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid0,
				std::vector<int32_t>& pGrid2
			) {
				// Not Bloody Foothills, such that the presets pick a random file (allocates a D2DrlgBuildStrc from pDrlg->pMempool)
				pLevel.nLevelId = LEVEL_ID_ACT5_BARRICADE_1;
				pLevel.pDrlg = &pDrlg;
				pLevel.pSeed.nLowSeed = low_seed;
				pLevel.pSeed.nHighSeed = high_seed;
				pLevel.nWidth = 8 * nGridWidth;
				pLevel.nHeight = 8 * nGridHeight;
				pLevel.pOutdoors = &pOutdoors;

				pOutdoors.nWidth = pLevel.nWidth;
				pOutdoors.nHeight = pLevel.nHeight;
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);

				// Mark one level link on each border of the level
				D2DrlgOutdoorPackedGrid2InfoStrc tPackedInfo{ 0 };
				tPackedInfo.bLvlLink = true;
				grid_cell(pOutdoors.pGrid[2], 4, 0) = tPackedInfo.nPackedValue;
				grid_cell(pOutdoors.pGrid[2], 4, nGridHeight - 2) = tPackedInfo.nPackedValue;
				grid_cell(pOutdoors.pGrid[2], 0, 8) = tPackedInfo.nPackedValue;
				grid_cell(pOutdoors.pGrid[2], nGridWidth - 2, 8) = tPackedInfo.nPackedValue;
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

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD846C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD846C0, dll_base + 0x000446C0);

		SUBCASE("")
		{
			const auto nGridWidth = 8;
			const auto nGridHeight = 8;

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [nGridWidth, nGridHeight](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid2
			) {
				pLevel.pOutdoors = &pOutdoors;

				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid2);
			setup_data(original_pLevel, original_pOutdoors, original_pGrid2);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
		}
	}

	// NOTE: Only the Bloody Foothills branch is tested. All other levels call DRLGTILESUB_AddSecondaryBorder,
	// which loads DS1 files from the archive.
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD84700")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTSIEGE_AddACt5SecondaryBorder, dll_base + 0x00044700);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgLevelStrc original_pLevel{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel
			) {
				pLevel.nLevelId = LEVEL_BLOODYFOOTHILLS;
			};

			setup_data(moo_pLevel);
			setup_data(original_pLevel);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD84780")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD84780, dll_base + 0x00044780);

		SUBCASE("")
		{
			// Valid (nStyle, a3) ranges. Any other combination hits D2_UNREACHABLE
			struct StyleRange
			{
				int nStyle;
				int nMin;
				int nMax;
			};

			const StyleRange style_ranges[] =
			{
				{ 49, 1, 16 },
				{ 49, 31, 46 },
				{ 48, 1, 8 },
				{ 48, 30, 31 },
			};

			for (auto nLevelId : { LEVEL_ARREATPLATEAU, LEVEL_TUNDRAWASTELANDS })
			{
				for (const auto& style_range : style_ranges)
				{
					for (auto i = style_range.nMin; i <= style_range.nMax; ++i)
					{
						// Input data
						D2DrlgLevelStrc moo_pLevel{};
						D2DrlgLevelStrc original_pLevel{};
						int nStyle = style_range.nStyle;
						int a3 = i;

						const auto setup_data = [nLevelId](
							D2DrlgLevelStrc& pLevel
						) {
							pLevel.nLevelId = nLevelId;
						};

						CAPTURE(nLevelId);
						CAPTURE(nStyle);
						CAPTURE(a3);

						setup_data(moo_pLevel);
						setup_data(original_pLevel);

						// Call both implementations
						const auto moo_result = sut(&moo_pLevel, nStyle, a3);
						const auto original_result = original(&original_pLevel, nStyle, a3);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD84820")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD84820, dll_base + 0x00044820);

		SUBCASE("")
		{
			const auto nGridWidth = 4;
			const auto nGridHeight = 4;

			// a3 = 31 -> -5 (always TRUE), a3 = 30 -> 0, a3 = 1 -> LVLPREST_ACT5_BARRICADE_CLIFF_BORDER_3
			for (auto nSubStyle : { 31, 30, 1 })
			{
				for (auto nExpected : { 0, (int)LVLPREST_ACT5_BARRICADE_CLIFF_BORDER_3 })
				{
					// (1, 1) is a level link, (2, 1) is not
					for (auto nCellX : { 1, 2 })
					{
						// Input data
						D2DrlgLevelStrc moo_pLevel{};
						D2DrlgOutdoorInfoStrc moo_pOutdoors{};
						std::vector<int32_t> moo_pGrid2{};
						D2DrlgLevelStrc original_pLevel{};
						D2DrlgOutdoorInfoStrc original_pOutdoors{};
						std::vector<int32_t> original_pGrid2{};
						int nX = nCellX;
						int nY = 1;
						int a4 = nExpected;
						int a5{};
						unsigned int a6 = (48 << 20) | (nSubStyle << 8);

						const auto setup_data = [nGridWidth, nGridHeight](
							D2DrlgLevelStrc& pLevel,
							D2DrlgOutdoorInfoStrc& pOutdoors,
							std::vector<int32_t>& pGrid2
						) {
							pLevel.nLevelId = LEVEL_ARREATPLATEAU;
							pLevel.pOutdoors = &pOutdoors;

							pOutdoors.nGridWidth = nGridWidth;
							pOutdoors.nGridHeight = nGridHeight;

							setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);

							D2DrlgOutdoorPackedGrid2InfoStrc tPackedInfo{ 0 };
							tPackedInfo.bLvlLink = true;
							grid_cell(pOutdoors.pGrid[2], 1, 1) = tPackedInfo.nPackedValue;
						};

						CAPTURE(nSubStyle);
						CAPTURE(nExpected);
						CAPTURE(nCellX);

						setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid2);
						setup_data(original_pLevel, original_pOutdoors, original_pGrid2);

						// Call both implementations
						const auto moo_result = sut(&moo_pLevel, nX, nY, a4, a5, a6);
						const auto original_result = original(&original_pLevel, nX, nY, a4, a5, a6);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
						MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD84870")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTSIEGE_PlaceSpecialPresets, dll_base + 0x00044870);

		SUBCASE("")
		{
			// NOTE: DRLGOUTDOORS_SpawnOutdoorLevelPreset supports at most 256 cells for (nGridWidth - 2) * (nGridHeight - 2)
			const auto nGridWidth = 18;
			const auto nGridHeight = 18;

			for (auto nLevelId : { LEVEL_ID_ACT5_BARRICADE_1, LEVEL_ARREATPLATEAU, LEVEL_TUNDRAWASTELANDS })
			{
				// Input data
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
				const auto low_seed = random_unsigned_integer();
				const auto high_seed = random_unsigned_integer();

				const auto setup_data = [nLevelId, nGridWidth, nGridHeight, low_seed, high_seed](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid0,
					std::vector<int32_t>& pGrid2
				) {
					pLevel.nLevelId = nLevelId;
					pLevel.pDrlg = &pDrlg;
					pLevel.pSeed.nLowSeed = low_seed;
					pLevel.pSeed.nHighSeed = high_seed;
					pLevel.nWidth = 8 * nGridWidth;
					pLevel.nHeight = 8 * nGridHeight;
					pLevel.pOutdoors = &pOutdoors;

					pOutdoors.nWidth = pLevel.nWidth;
					pOutdoors.nHeight = pLevel.nHeight;
					pOutdoors.nGridWidth = nGridWidth;
					pOutdoors.nGridHeight = nGridHeight;

					setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
					setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);
				};

				CAPTURE(nLevelId);
				CAPTURE(low_seed);
				CAPTURE(high_seed);

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

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD84910")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTSIEGE_PlacePrisons, dll_base + 0x00044910);

		SUBCASE("")
		{
			const auto nGridWidth = 16;
			const auto nGridHeight = 16;

			// Input data
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
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			const auto setup_data = [nGridWidth, nGridHeight, low_seed, high_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid0,
				std::vector<int32_t>& pGrid2
			) {
				pLevel.nLevelId = LEVEL_ID_ACT5_BARRICADE_1;
				pLevel.pDrlg = &pDrlg;
				pLevel.pSeed.nLowSeed = low_seed;
				pLevel.pSeed.nHighSeed = high_seed;
				pLevel.nWidth = 8 * nGridWidth;
				pLevel.nHeight = 8 * nGridHeight;
				pLevel.pOutdoors = &pOutdoors;

				pOutdoors.nWidth = pLevel.nWidth;
				pOutdoors.nHeight = pLevel.nHeight;
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);

				// Place barricade presets (which can be turned into prisons) in the upper left part of the level
				D2DrlgOutdoorPackedGrid2InfoStrc tPackedInfo{ 0 };
				tPackedInfo.bHasPickedFile = true;
				for (auto nY = 0; nY < 8; nY += 2)
				{
					for (auto nX = 0; nX < 8; nX += 2)
					{
						grid_cell(pOutdoors.pGrid[0], nX, nY) = LVLPREST_ACT5_BARRICADE_1 + (nX / 2 + nY / 2) % 8;
						grid_cell(pOutdoors.pGrid[2], nX, nY) = tPackedInfo.nPackedValue;
					}
				}
			};

			CAPTURE(low_seed);
			CAPTURE(high_seed);

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

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD84BB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTSIEGE_ConnectBarricadeAndSiege, dll_base + 0x00044BB0);

		SUBCASE("")
		{
			const auto nGridWidth = 18;
			const auto nGridHeight = 18;

			// Input data
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
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			const auto setup_data = [nGridWidth, nGridHeight, low_seed, high_seed](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid0,
				std::vector<int32_t>& pGrid2
			) {
				pLevel.nLevelId = LEVEL_ID_ACT5_BARRICADE_1;
				pLevel.pDrlg = &pDrlg;
				pLevel.pSeed.nLowSeed = low_seed;
				pLevel.pSeed.nHighSeed = high_seed;
				pLevel.nWidth = 8 * nGridWidth;
				pLevel.nHeight = 8 * nGridHeight;
				pLevel.pOutdoors = &pOutdoors;

				pOutdoors.nWidth = pLevel.nWidth;
				pOutdoors.nHeight = pLevel.nHeight;
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);
			};

			CAPTURE(low_seed);
			CAPTURE(high_seed);

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
