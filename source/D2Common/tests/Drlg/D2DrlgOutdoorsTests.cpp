#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cstdarg>
#include <filesystem>
#include <utility>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Fog.h>
#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgDrlgGrid.h>
#include <Drlg/D2DrlgDrlgVer.h>
#include <Drlg/D2DrlgOutdoors.h>
#include <Drlg/D2DrlgOutRoom.h>
#include <Drlg/D2DrlgTileSub.h>

#include <Fixtures/DataTbls/Fixtures.h>


DYNAMIC_ARRAY_TYPE(int)


// Allocates the row offsets followed by the cells, as done in DRLGGRID_InitializeGridCells
static void setup_grid(D2DrlgGridStrc& pGrid, std::vector<int32_t>& cells, int width, int height, const std::vector<int32_t>& values = {})
{
	cells.assign(height * (width + 1), 0);
	for (auto i = 0; i < height; ++i)
	{
		cells[i] = i * width;
	}
	std::copy(values.begin(), values.end(), cells.begin() + height);

	pGrid.nWidth = width;
	pGrid.nHeight = height;
	pGrid.pCellsRowOffsets = cells.data();
	pGrid.pCellsFlags = cells.data() + height;
}

static auto random_integer(int min, int max) -> int
{
	return min + static_cast<int>(random_unsigned_integer(0, static_cast<uint32_t>(max - min)));
}

// Random cell values limited to mask, on average only one in one_in cells gets a (potentially) non-zero value
static auto random_grid_values(int width, int height, uint32_t mask, uint32_t one_in = 1) -> std::vector<int32_t>
{
	std::vector<int32_t> values(width * height, 0);
	for (auto& value : values)
	{
		if (random_unsigned_integer(1, one_in) == 1)
		{
			value = static_cast<int32_t>(random_unsigned_integer() & mask);
		}
	}

	return values;
}


TEST_SUITE("D2DrlgOutdoorsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DC20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_GetOutLinkVisFlag, dll_base + 0x0003DC20);

		constexpr int nGridWidth = 6;
		constexpr int nGridHeight = 5;

		// Corners and edges of the grid, as well as an inner cell
		const D2CoordStrc vertex_positions[] =
		{
			{ 0, 2 },
			{ 0, 0 },
			{ 3, 0 },
			{ nGridWidth - 1, 0 },
			{ nGridWidth - 1, 2 },
			{ nGridWidth - 1, nGridHeight - 1 },
			{ 3, nGridHeight - 1 },
			{ 0, nGridHeight - 1 },
			{ 2, 2 },
		};

		SUBCASE("")
		{
			for (const auto& vertex_position : vertex_positions)
			{
				for (int nDirection = 0; nDirection < 4; ++nDirection)
				{
					for (const BOOL bInit : { FALSE, TRUE })
					{
						// Input data
						const auto level_x = random_integer(0, 1000) * 8;
						const auto level_y = random_integer(0, 1000) * 8;
						const auto vis_index = random_integer(0, 7);

						D2DrlgLevelStrc moo_pLevel{};
						D2DrlgVertexStrc moo_pDrlgVertex{};
						D2DrlgStrc moo_pDrlg{};
						D2DrlgWarpStrc moo_pWarp{};
						D2DrlgOutdoorInfoStrc moo_pOutdoors{};
						D2DrlgOrthStrc moo_pRoomData{};
						D2DrlgCoordStrc moo_pBox{};
						D2DrlgLevelStrc moo_pLinkedLevel{};
						D2DrlgLevelStrc original_pLevel{};
						D2DrlgVertexStrc original_pDrlgVertex{};
						D2DrlgStrc original_pDrlg{};
						D2DrlgWarpStrc original_pWarp{};
						D2DrlgOutdoorInfoStrc original_pOutdoors{};
						D2DrlgOrthStrc original_pRoomData{};
						D2DrlgCoordStrc original_pBox{};
						D2DrlgLevelStrc original_pLinkedLevel{};

						const auto setup_data = [&vertex_position, nDirection, bInit, level_x, level_y, vis_index](
							D2DrlgLevelStrc& pLevel,
							D2DrlgVertexStrc& pDrlgVertex,
							D2DrlgStrc& pDrlg,
							D2DrlgWarpStrc& pWarp,
							D2DrlgOutdoorInfoStrc& pOutdoors,
							D2DrlgOrthStrc& pRoomData,
							D2DrlgCoordStrc& pBox,
							D2DrlgLevelStrc& pLinkedLevel
						) {
							pWarp.nLevel = LEVEL_COLDPLAINS;
							pWarp.nVis[vis_index] = LEVEL_BLOODMOOR;

							pDrlg.pWarp = &pWarp;

							pLinkedLevel.nLevelId = LEVEL_BLOODMOOR;

							// The box surrounds the whole level, so whether the link is found only depends on its direction
							pBox.nPosX = level_x - 16;
							pBox.nPosY = level_y - 16;
							pBox.nWidth = 8 * nGridWidth + 32;
							pBox.nHeight = 8 * nGridHeight + 32;

							pRoomData.pLevel = &pLinkedLevel;
							pRoomData.nDirection = static_cast<uint8_t>(nDirection);
							pRoomData.bInit = bInit;
							pRoomData.pBox = &pBox;

							pOutdoors.nGridWidth = nGridWidth;
							pOutdoors.nGridHeight = nGridHeight;
							pOutdoors.pRoomData = &pRoomData;

							pLevel.pDrlg = &pDrlg;
							pLevel.nLevelId = LEVEL_COLDPLAINS;
							pLevel.nPosX = level_x;
							pLevel.nPosY = level_y;
							pLevel.nWidth = 8 * nGridWidth;
							pLevel.nHeight = 8 * nGridHeight;
							pLevel.pOutdoors = &pOutdoors;

							pDrlgVertex.nPosX = vertex_position.nX;
							pDrlgVertex.nPosY = vertex_position.nY;
						};

						setup_data(moo_pLevel, moo_pDrlgVertex, moo_pDrlg, moo_pWarp, moo_pOutdoors, moo_pRoomData, moo_pBox, moo_pLinkedLevel);
						setup_data(original_pLevel, original_pDrlgVertex, original_pDrlg, original_pWarp, original_pOutdoors, original_pRoomData, original_pBox, original_pLinkedLevel);

						// Call both implementations
						const auto moo_result = sut(&moo_pLevel, &moo_pDrlgVertex);
						const auto original_result = original(&original_pLevel, &original_pDrlgVertex);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
						MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DD00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_GetPresetIndexFromGridCell, dll_base + 0x0003DD00);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("")
		{
			// Input data
			const auto grid0_values = random_grid_values(nGridWidth, nGridHeight, 0x3FF);
			const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0xFFFFFFFF);

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			std::vector<int32_t> moo_pGrid0{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			std::vector<int32_t> original_pGrid0{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [&grid0_values, &grid2_values](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid0,
				std::vector<int32_t>& pGrid2
			) {
				setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight, grid0_values);
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
			setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

			for (int nY = 0; nY < nGridHeight; ++nY)
			{
				for (int nX = 0; nX < nGridWidth; ++nX)
				{
					// Call both implementations
					const auto moo_result = sut(&moo_pLevel, nX, nY);
					const auto original_result = original(&original_pLevel, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DD40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_AlterAdjacentPresetGridCells, dll_base + 0x0003DD40);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("")
		{
			// Input data
			const auto grid0_values = random_grid_values(nGridWidth, nGridHeight, 0x3FF);
			const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0xFFFFFFFF);

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			std::vector<int32_t> moo_pGrid0{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			std::vector<int32_t> original_pGrid0{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [&grid0_values, &grid2_values](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid0,
				std::vector<int32_t>& pGrid2
			) {
				setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight, grid0_values);
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
			setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

			for (int nY = 0; nY < nGridHeight; nY += 2)
			{
				for (int nX = 0; nX < nGridWidth; nX += 2)
				{
					// Call both implementations
					sut(&moo_pLevel, nX, nY);
					original(&original_pLevel, nX, nY);
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DD70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_SetBlankGridCell, dll_base + 0x0003DD70);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("")
		{
			// Input data
			const auto grid0_values = random_grid_values(nGridWidth, nGridHeight, 0x3FF);
			const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0xFFFFFFFF);

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			std::vector<int32_t> moo_pGrid0{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			std::vector<int32_t> original_pGrid0{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [&grid0_values, &grid2_values](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid0,
				std::vector<int32_t>& pGrid2
			) {
				setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight, grid0_values);
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
			setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

			for (int nY = 0; nY < nGridHeight; nY += 2)
			{
				for (int nX = 0; nX < nGridWidth; nX += 2)
				{
					// Call both implementations
					sut(&moo_pLevel, nX, nY);
					original(&original_pLevel, nX, nY);
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DDB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_TestGridCellNonLvlLink, dll_base + 0x0003DDB0);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("")
		{
			// Input data
			const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0xFFFFFFFF);

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [&grid2_values](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid2
			) {
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid2);
			setup_data(original_pLevel, original_pOutdoors, original_pGrid2);

			for (int nY = 0; nY < nGridHeight; ++nY)
			{
				for (int nX = 0; nX < nGridWidth; ++nX)
				{
					// Call both implementations
					const auto moo_result = sut(&moo_pLevel, nX, nY);
					const auto original_result = original(&original_pLevel, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7DDD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_TestGridCellSpawnValid, dll_base + 0x0003DDD0);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("")
		{
			// Input data
			// Only some cells get flags, so that there are cells in which spawning is valid
			const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0xFFFFFFFF, 2);

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [&grid2_values](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid2
			) {
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid2);
			setup_data(original_pLevel, original_pOutdoors, original_pGrid2);

			for (int nY = 0; nY < nGridHeight; ++nY)
			{
				for (int nX = 0; nX < nGridWidth; ++nX)
				{
					// Call both implementations
					const auto moo_result = sut(&moo_pLevel, nX, nY);
					const auto original_result = original(&original_pLevel, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7DDF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_TestOutdoorLevelPreset, dll_base + 0x0003DDF0);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		// 0 tests a single cell, the others are presets of 1x1, 2x2 and 3x3 cells
		const int level_prest_ids[] = { 0, LVLPREST_ACT1_WILD_BORDER_1, LVLPREST_ACT4_PITS_1_16X16, LVLPREST_ACT4_MESA_1_24X24 };

		SUBCASE("")
		{
			// Input data
			// Only some cells are blocked, so that presets fit into the grid
			const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1B81, 6);

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [&grid2_values](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				std::vector<int32_t>& pGrid2
			) {
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;

				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid2);
			setup_data(original_pLevel, original_pOutdoors, original_pGrid2);

			for (const int nLevelPrestId : level_prest_ids)
			{
				for (int nOffset = 0; nOffset <= 2; ++nOffset)
				{
					for (char nFlags = 0; nFlags < 16; ++nFlags)
					{
						// Positions outside of the grid are included, they are expected to be rejected
						for (int nY = -1; nY <= nGridHeight; ++nY)
						{
							for (int nX = -1; nX <= nGridWidth; ++nX)
							{
								// Call both implementations
								const auto moo_result = sut(&moo_pLevel, nX, nY, nLevelPrestId, nOffset, nFlags);
								const auto original_result = original(&original_pLevel, nX, nY, nLevelPrestId, nOffset, nFlags);

								// Compare return values
								MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
							}
						}
					}
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7DEF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_SpawnOutdoorLevelPresetEx, dll_base + 0x0003DEF0);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		// Act 1 and Act 2 borders get special handling when bBorder is set
		const int level_prest_ids[] = { LVLPREST_ACT1_WILD_BORDER_1, LVLPREST_ACT2_DESERT_BORDER_1, LVLPREST_ACT4_PITS_1_16X16, LVLPREST_ACT4_MESA_1_24X24 };

		SUBCASE("Given picked file")
		{
			for (const int nLevelPrestId : level_prest_ids)
			{
				for (const BOOL bBorder : { FALSE, TRUE })
				{
					// Input data
					const int nX = random_integer(0, nGridWidth - lvlprest_txt[nLevelPrestId].nSizeX / 8);
					const int nY = random_integer(0, nGridHeight - lvlprest_txt[nLevelPrestId].nSizeY / 8);
					const int nPickedFile = random_integer(0, 15);
					const auto grid0_values = random_grid_values(nGridWidth, nGridHeight, 0x3FF);
					const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0xFFFFFFFF);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [&grid0_values, &grid2_values](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight, grid0_values);
						setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;

						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					sut(&moo_pLevel, nX, nY, nLevelPrestId, nPickedFile, bBorder);
					original(&original_pLevel, nX, nY, nLevelPrestId, nPickedFile, bBorder);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
				}
			}
		}

		SUBCASE("Random picked file")
		{
			for (const int nLevelPrestId : level_prest_ids)
			{
				// Without a matching build, a new one is allocated from the memory pool
				for (const BOOL bHasBuild : { FALSE, TRUE })
				{
					// Input data
					const int nX = random_integer(0, nGridWidth - lvlprest_txt[nLevelPrestId].nSizeX / 8);
					const int nY = random_integer(0, nGridHeight - lvlprest_txt[nLevelPrestId].nSizeY / 8);
					const int nPickedFile = -1;
					const BOOL bBorder = FALSE;
					const auto build_divisor = random_integer(1, 8);
					const auto build_rand = random_integer(0, build_divisor - 1);
					const auto seed_low = random_unsigned_integer();
					const auto seed_high = random_unsigned_integer();
					const auto grid0_values = random_grid_values(nGridWidth, nGridHeight, 0x3FF);
					const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0xFFFFFFFF);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgBuildStrc moo_pBuild{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgBuildStrc original_pBuild{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [&grid0_values, &grid2_values, nLevelPrestId, bHasBuild, build_divisor, build_rand, seed_low, seed_high](
						D2DrlgLevelStrc& pLevel,
						D2DrlgStrc& pDrlg,
						D2DrlgBuildStrc& pBuild,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight, grid0_values);
						setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;

						pLevel.pDrlg = &pDrlg;
						pLevel.pSeed.nLowSeed = seed_low;
						pLevel.pSeed.nHighSeed = seed_high;
						pLevel.pOutdoors = &pOutdoors;

						if (bHasBuild)
						{
							pBuild.nPreset = nLevelPrestId;
							pBuild.nDivisor = build_divisor;
							pBuild.nRand = build_rand;

							pLevel.pBuild = &pBuild;
						}
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pBuild, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pDrlg, original_pBuild, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					sut(&moo_pLevel, nX, nY, nLevelPrestId, nPickedFile, bBorder);
					original(&original_pLevel, nX, nY, nLevelPrestId, nPickedFile, bBorder);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7E0F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_SpawnPresetFarAway, dll_base + 0x0003E0F0);

		constexpr int nGridWidth = 10;
		constexpr int nGridHeight = 10;

		const int level_prest_ids[] = { LVLPREST_ACT1_WILD_BORDER_1, LVLPREST_ACT4_PITS_1_16X16, LVLPREST_ACT4_MESA_1_24X24 };

		SUBCASE("")
		{
			for (const int nLvlPrestId : level_prest_ids)
			{
				for (int nOffset = 0; nOffset <= 1; ++nOffset)
				{
					// Input data
					const int nRand = random_integer(0, 15);
					const char nFlags = static_cast<char>(random_integer(0, 15));
					const auto level_x = random_integer(0, 1000) * 8;
					const auto level_y = random_integer(0, 1000) * 8;
					const auto coord_x = level_x + random_integer(-64, 8 * nGridWidth + 64);
					const auto coord_y = level_y + random_integer(-64, 8 * nGridHeight + 64);
					const auto coord_width = random_integer(0, 64);
					const auto coord_height = random_integer(0, 64);
					const auto seed_low = random_unsigned_integer();
					const auto seed_high = random_unsigned_integer();
					// Only some cells are blocked, so that presets fit into the grid
					const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1B81, 5);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgCoordStrc moo_pDrlgCoord{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgCoordStrc original_pDrlgCoord{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [&grid2_values, level_x, level_y, coord_x, coord_y, coord_width, coord_height, seed_low, seed_high](
						D2DrlgLevelStrc& pLevel,
						D2DrlgCoordStrc& pDrlgCoord,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
						setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;

						pLevel.pSeed.nLowSeed = seed_low;
						pLevel.pSeed.nHighSeed = seed_high;
						pLevel.nPosX = level_x;
						pLevel.nPosY = level_y;
						pLevel.nWidth = 8 * nGridWidth;
						pLevel.nHeight = 8 * nGridHeight;
						pLevel.pOutdoors = &pOutdoors;

						pDrlgCoord.nPosX = coord_x;
						pDrlgCoord.nPosY = coord_y;
						pDrlgCoord.nWidth = coord_width;
						pDrlgCoord.nHeight = coord_height;
					};

					setup_data(moo_pLevel, moo_pDrlgCoord, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pDrlgCoord, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					const auto moo_result = sut(&moo_pLevel, &moo_pDrlgCoord, nLvlPrestId, nRand, nOffset, nFlags);
					const auto original_result = original(&original_pLevel, &original_pDrlgCoord, nLvlPrestId, nRand, nOffset, nFlags);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
					MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7E330")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_SpawnOutdoorLevelPreset, dll_base + 0x0003E330);

		constexpr int nGridWidth = 10;
		constexpr int nGridHeight = 10;

		const int level_prest_ids[] = { LVLPREST_ACT1_WILD_BORDER_1, LVLPREST_ACT4_PITS_1_16X16, LVLPREST_ACT4_MESA_1_24X24 };

		SUBCASE("")
		{
			for (const int nLevelPrestId : level_prest_ids)
			{
				for (int nOffset = 0; nOffset <= 1; ++nOffset)
				{
					// Input data
					const int nRand = random_integer(0, 15);
					const char nFlags = static_cast<char>(random_integer(0, 15));
					const auto seed_low = random_unsigned_integer();
					const auto seed_high = random_unsigned_integer();
					// Only some cells are blocked, so that presets fit into the grid
					const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1B81, 5);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [&grid2_values, seed_low, seed_high](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
						setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;

						pLevel.pSeed.nLowSeed = seed_low;
						pLevel.pSeed.nHighSeed = seed_high;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					const auto moo_result = sut(&moo_pLevel, nLevelPrestId, nRand, nOffset, nFlags);
					const auto original_result = original(&original_pLevel, nLevelPrestId, nRand, nOffset, nFlags);

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

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7E4D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_SpawnRandomOutdoorDS1, dll_base + 0x0003E4D0);

		constexpr int nGridWidth = 10;
		constexpr int nGridHeight = 10;

		const int level_prest_ids[] = { LVLPREST_ACT1_WILD_BORDER_1, LVLPREST_ACT4_PITS_1_16X16, LVLPREST_ACT4_MESA_1_24X24 };

		SUBCASE("")
		{
			for (const int nLvlPrestId : level_prest_ids)
			{
				for (int i = 0; i < 4; ++i)
				{
					// Input data
					const int nRand = random_integer(0, 15);
					const auto seed_low = random_unsigned_integer();
					const auto seed_high = random_unsigned_integer();
					// Some cells are blocked, some (also) mark spots next to which the preset is preferably spawned (0x80)
					const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1B81, 4);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [&grid2_values, seed_low, seed_high](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
						setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;

						pLevel.pSeed.nLowSeed = seed_low;
						pLevel.pSeed.nHighSeed = seed_high;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					const auto moo_result = sut(&moo_pLevel, nLvlPrestId, nRand);
					const auto original_result = original(&original_pLevel, nLvlPrestId, nRand);

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

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7E6D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_SpawnAct12Waypoint, dll_base + 0x0003E6D0);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("Cold Plains")
		{
			for (int i = 0; i < 8; ++i)
			{
				// Input data
				const auto vis_index = random_integer(0, 7);
				const auto seed_low = random_unsigned_integer();
				const auto seed_high = random_unsigned_integer();
				// Vis flags of the links to other levels
				const auto grid1_values = random_grid_values(nGridWidth, nGridHeight, 0xFF0, 4);
				// Some cells are level links (0x400), some are blocked
				const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1FFF, 2);

				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgWarpStrc moo_pWarp{};
				D2DrlgOutdoorInfoStrc moo_pOutdoors{};
				std::vector<int32_t> moo_pGrid1{};
				std::vector<int32_t> moo_pGrid2{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgWarpStrc original_pWarp{};
				D2DrlgOutdoorInfoStrc original_pOutdoors{};
				std::vector<int32_t> original_pGrid1{};
				std::vector<int32_t> original_pGrid2{};

				const auto setup_data = [&grid1_values, &grid2_values, vis_index, seed_low, seed_high](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg,
					D2DrlgWarpStrc& pWarp,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid1,
					std::vector<int32_t>& pGrid2
				) {
					pWarp.nLevel = LEVEL_COLDPLAINS;
					pWarp.nVis[vis_index] = LEVEL_BLOODMOOR;

					pDrlg.pWarp = &pWarp;

					setup_grid(pOutdoors.pGrid[1], pGrid1, nGridWidth, nGridHeight, grid1_values);
					setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
					pOutdoors.nGridWidth = nGridWidth;
					pOutdoors.nGridHeight = nGridHeight;

					pLevel.pDrlg = &pDrlg;
					pLevel.nLevelId = LEVEL_COLDPLAINS;
					pLevel.pSeed.nLowSeed = seed_low;
					pLevel.pSeed.nHighSeed = seed_high;
					pLevel.pOutdoors = &pOutdoors;
				};

				setup_data(moo_pLevel, moo_pDrlg, moo_pWarp, moo_pOutdoors, moo_pGrid1, moo_pGrid2);
				setup_data(original_pLevel, original_pDrlg, original_pWarp, original_pOutdoors, original_pGrid1, original_pGrid2);

				// Call both implementations
				sut(&moo_pLevel);
				original(&original_pLevel);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid1.data(), (int)moo_pGrid1.size() }), (DynamicArray<int>{ original_pGrid1.data(), (int)original_pGrid1.size() }), "Comparing pGrid[1]");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
			}
		}

		SUBCASE("Other levels")
		{
			for (const int nLevelId : { LEVEL_STONYFIELD, LEVEL_DRYHILLS })
			{
				// Input data
				const auto seed_low = random_unsigned_integer();
				const auto seed_high = random_unsigned_integer();
				// Only some cells are blocked, so that the waypoint can be placed
				const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1FFF, 2);

				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgOutdoorInfoStrc moo_pOutdoors{};
				std::vector<int32_t> moo_pGrid1{};
				std::vector<int32_t> moo_pGrid2{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgOutdoorInfoStrc original_pOutdoors{};
				std::vector<int32_t> original_pGrid1{};
				std::vector<int32_t> original_pGrid2{};

				const auto setup_data = [&grid2_values, nLevelId, seed_low, seed_high](
					D2DrlgLevelStrc& pLevel,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid1,
					std::vector<int32_t>& pGrid2
				) {
					setup_grid(pOutdoors.pGrid[1], pGrid1, nGridWidth, nGridHeight);
					setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
					pOutdoors.nGridWidth = nGridWidth;
					pOutdoors.nGridHeight = nGridHeight;

					pLevel.nLevelId = nLevelId;
					pLevel.pSeed.nLowSeed = seed_low;
					pLevel.pSeed.nHighSeed = seed_high;
					pLevel.pOutdoors = &pOutdoors;
				};

				setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid1, moo_pGrid2);
				setup_data(original_pLevel, original_pOutdoors, original_pGrid1, original_pGrid2);

				// Call both implementations
				sut(&moo_pLevel);
				original(&original_pLevel);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid1.data(), (int)moo_pGrid1.size() }), (DynamicArray<int>{ original_pGrid1.data(), (int)original_pGrid1.size() }), "Comparing pGrid[1]");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7E940")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_SpawnAct12Shrines, dll_base + 0x0003E940);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("")
		{
			for (int nShrines = 0; nShrines <= 8; ++nShrines)
			{
				// Input data
				const auto seed_low = random_unsigned_integer();
				const auto seed_high = random_unsigned_integer();
				// Only some cells are blocked, so that shrines can be placed
				const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1FFF, 2);

				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgOutdoorInfoStrc moo_pOutdoors{};
				std::vector<int32_t> moo_pGrid1{};
				std::vector<int32_t> moo_pGrid2{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgOutdoorInfoStrc original_pOutdoors{};
				std::vector<int32_t> original_pGrid1{};
				std::vector<int32_t> original_pGrid2{};

				const auto setup_data = [&grid2_values, seed_low, seed_high](
					D2DrlgLevelStrc& pLevel,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					std::vector<int32_t>& pGrid1,
					std::vector<int32_t>& pGrid2
				) {
					setup_grid(pOutdoors.pGrid[1], pGrid1, nGridWidth, nGridHeight);
					setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
					pOutdoors.nGridWidth = nGridWidth;
					pOutdoors.nGridHeight = nGridHeight;

					pLevel.pSeed.nLowSeed = seed_low;
					pLevel.pSeed.nHighSeed = seed_high;
					pLevel.pOutdoors = &pOutdoors;
				};

				setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid1, moo_pGrid2);
				setup_data(original_pLevel, original_pOutdoors, original_pGrid1, original_pGrid2);

				// Call both implementations
				sut(&moo_pLevel, nShrines);
				original(&original_pLevel, nShrines);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid1.data(), (int)moo_pGrid1.size() }), (DynamicArray<int>{ original_pGrid1.data(), (int)original_pGrid1.size() }), "Comparing pGrid[1]");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
			}
		}
	}

	TEST_CASE_FIXTURE(LvlSubTxtFixture<LvlPrestTxtFixture<NoopFixture>>, "D2Common.0x6FD7EB20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_AddAct124SecondaryBorder, dll_base + 0x0003EB20);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		const int nLevelPrestId = LVLPREST_ACT4_MESA_BORDER_1;

		// Borders are spawned into single grid cells
		REQUIRE(lvlprest_txt[nLevelPrestId].nSizeX / 8 == 1);
		REQUIRE(lvlprest_txt[nLevelPrestId].nSizeY / 8 == 1);

		// Substitution files are usually loaded from DS1 files. Instead, a file with a single substitution group of one cell is used.
		// Its first cell is tested, the third cell (at (rolled field_14 + 1) * (width + 1) = 2) is used as replacement.
		// The data tables are global, so this data is shared by both implementations.
		D2DrlgSubstGroupStrc substitution_group{};
		substitution_group.tBox.nWidth = 1;
		substitution_group.tBox.nHeight = 1;
		substitution_group.field_14 = 1;

		D2DrlgFileStrc substitution_file{};
		substitution_file.nWallLayers = 1;
		substitution_file.nFloorLayers = 1;
		substitution_file.nSubstGroups = 1;
		substitution_file.pSubstGroups = &substitution_group;

		std::vector<int32_t> substitution_wall_grid{};
		std::vector<int32_t> substitution_floor_grid{};

		// Wall and floor values of the substitution cells: spawn a border preset, alter the preset grid cells or blank the grid cells
		const std::pair<std::vector<int32_t>, std::vector<int32_t>> substitutions[] =
		{
			{ { 0, 0, 0x101 }, { 0, 0, 0 } },
			{ { 0, 0, 0 }, { 0, 0, 2 } },
			{ { 0, 0, 0 }, { 0, 0, 0 } },
		};

		SUBCASE("")
		{
			for (int nLvlSubId = 1; nLvlSubId <= 3; ++nLvlSubId)
			{
				for (const auto& [wall_values, floor_values] : substitutions)
				{
					D2DrlgGridStrc tWallGrid{};
					D2DrlgGridStrc tFloorGrid{};
					setup_grid(tWallGrid, substitution_wall_grid, 3, 1, wall_values);
					setup_grid(tFloorGrid, substitution_floor_grid, 3, 1, floor_values);

					for (int i = 0; i < lvlsub_record_count; ++i)
					{
						if (static_cast<int>(lvlsub_txt[i].dwType) == nLvlSubId)
						{
							lvlsub_txt[i].pDrlgFile = &substitution_file;
							lvlsub_txt[i].pWallGrid[0] = tWallGrid;
							lvlsub_txt[i].pFloorGrid = tFloorGrid;
						}
					}

					// Rivers change the size of the area used for the substitution with type 1
					for (const uint32_t dwFlags : { 0u, static_cast<uint32_t>(OUTDOOR_RIVER_OTHER) })
					{
						// Input data
						const auto seed_low = random_unsigned_integer();
						const auto seed_high = random_unsigned_integer();
						const auto grid0_values = random_grid_values(nGridWidth, nGridHeight, 0x3FF);
						const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1FFF, 2);

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

						const auto setup_data = [&grid0_values, &grid2_values, dwFlags, seed_low, seed_high](
							D2DrlgLevelStrc& pLevel,
							D2DrlgStrc& pDrlg,
							D2DrlgOutdoorInfoStrc& pOutdoors,
							std::vector<int32_t>& pGrid0,
							std::vector<int32_t>& pGrid2
						) {
							pOutdoors.dwFlags = dwFlags;
							setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight, grid0_values);
							setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);
							pOutdoors.nGridWidth = nGridWidth;
							pOutdoors.nGridHeight = nGridHeight;

							pLevel.pDrlg = &pDrlg;
							pLevel.nLevelId = LEVEL_OUTERSTEPPES;
							pLevel.pSeed.nLowSeed = seed_low;
							pLevel.pSeed.nHighSeed = seed_high;
							pLevel.pOutdoors = &pOutdoors;
						};

						setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
						setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2);

						// Call both implementations
						sut(&moo_pLevel, nLvlSubId, nLevelPrestId);
						original(&original_pLevel, nLvlSubId, nLevelPrestId);

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
						MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
						MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7EBA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_AllocOutdoorInfo, dll_base + 0x0003EBA0);

		SUBCASE("")
		{
			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg
			) {
				pLevel.pDrlg = &pDrlg;
			};

			setup_data(moo_pLevel, moo_pDrlg);
			setup_data(original_pLevel, original_pDrlg);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<LvlSubTxtFixture<NoopFixture>>>, "D2Common.0x6FD7EBD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_GenerateLevel, dll_base + 0x0003EBD0);

		SUBCASE("")
		{
			// Input data
			// The Kurast Causeway does not spawn any presets during the initialization of Act 3 outdoor levels,
			// so the level only consists of outdoor rooms and no DS1 files have to be loaded
			const auto level_x = random_integer(0, 1000) * 8;
			const auto level_y = random_integer(0, 1000) * 8;
			const auto level_width = random_integer(2, 6) * 8;
			const auto level_height = random_integer(2, 6) * 8;
			const auto seed_low = random_unsigned_integer();
			const auto seed_high = random_unsigned_integer();

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};

			const auto setup_data = [level_x, level_y, level_width, level_height, seed_low, seed_high](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgOutdoorInfoStrc& pOutdoors
			) {
				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_KURASTCAUSEWAY;
				pLevel.nLevelType = LVLTYPE_ACT3_KURAST;
				pLevel.nDrlgType = DRLGTYPE_OUTDOOR;
				pLevel.pSeed.nLowSeed = seed_low;
				pLevel.pSeed.nHighSeed = seed_high;
				pLevel.nPosX = level_x;
				pLevel.nPosY = level_y;
				pLevel.nWidth = level_width;
				pLevel.nHeight = level_height;
				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors);
			setup_data(original_pLevel, original_pDrlg, original_pOutdoors);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7EEE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_FreeOutdoorInfo, dll_base + 0x0003EEE0);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("")
		{
			for (const BOOL bKeepRoomData : { FALSE, TRUE })
			{
				// Input data
				const auto dwFlags = random_unsigned_integer(0, 0x7FF);
				const auto nVertices = random_integer(0, 6);

				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgStrc original_pDrlg{};

				const auto setup_data = [dwFlags, nVertices](
					D2DrlgLevelStrc& pLevel,
					D2DrlgStrc& pDrlg
				) {
					pLevel.pDrlg = &pDrlg;

					// The outdoor info and everything it references is freed by the function, so it has to be allocated from the memory pool
					D2DrlgOutdoorInfoStrc* pOutdoors = D2_CALLOC_STRC_POOL(pDrlg.pMempool, D2DrlgOutdoorInfoStrc);
					pOutdoors->dwFlags = dwFlags;
					pOutdoors->nGridWidth = nGridWidth;
					pOutdoors->nGridHeight = nGridHeight;

					for (auto& pGrid : pOutdoors->pGrid)
					{
						DRLGGRID_InitializeGridCells(pDrlg.pMempool, &pGrid, nGridWidth, nGridHeight);
					}

					D2DrlgCoordStrc tGridCoords = { 0, 0, nGridWidth, nGridHeight };
					DRLGVER_CreateVertices(pDrlg.pMempool, &pOutdoors->pVertex, &tGridCoords, 0, nullptr);

					for (int i = 0; i < nVertices; ++i)
					{
						pOutdoors->pVertices[i].nPosX = i;
						pOutdoors->pVertices[6 + i].nPosX = i;
						pOutdoors->pVertices[12 + i].nPosY = i;
						pOutdoors->pVertices[18 + i].nPosY = i;

						pOutdoors->pPathStarts[i] = DRLGVER_AllocVertex(pDrlg.pMempool, 0);
						pOutdoors->pPathStarts[i]->pNext = DRLGVER_AllocVertex(pDrlg.pMempool, 0);
					}
					pOutdoors->nVertices = nVertices;

					for (int i = 0; i < 2; ++i)
					{
						D2DrlgOrthStrc* pRoomData = D2_CALLOC_STRC_POOL(pDrlg.pMempool, D2DrlgOrthStrc);
						pRoomData->pNext = pOutdoors->pRoomData;
						pOutdoors->pRoomData = pRoomData;
					}

					pLevel.pOutdoors = pOutdoors;
				};

				setup_data(moo_pLevel, moo_pDrlg);
				setup_data(original_pLevel, original_pDrlg);

				// Call both implementations
				sut(&moo_pLevel, bKeepRoomData);
				original(&original_pLevel, bKeepRoomData);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7EFE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_OUTDOORS_GenerateDirtPath, dll_base + 0x0003EFE0);

		constexpr int nRoomWidth = 8;
		constexpr int nRoomHeight = 8;
		constexpr int nPathVertices = 5;

		SUBCASE("")
		{
			for (int iteration = 0; iteration < 16; ++iteration)
			{
				// Input data
				const auto room_x = random_integer(1, 100) * 8;
				const auto room_y = random_integer(1, 100) * 8;

				// Vertices of the dirt paths, in and around the room
				D2CoordStrc path_positions[nPathVertices] = {};
				for (auto& path_position : path_positions)
				{
					path_position.nX = room_x + random_integer(-4, nRoomWidth + 4);
					path_position.nY = room_y + random_integer(-4, nRoomHeight + 4);
				}

				D2DrlgLevelStrc moo_pLevel{};
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgStrc moo_pDrlg{};
				D2DrlgOutdoorInfoStrc moo_pOutdoors{};
				D2DrlgVertexStrc moo_pPathVertices[nPathVertices]{};
				D2DrlgOutdoorRoomStrc moo_pOutdoorRoom{};
				std::vector<int32_t> moo_pFloorGrid{};
				D2DrlgLevelStrc original_pLevel{};
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgStrc original_pDrlg{};
				D2DrlgOutdoorInfoStrc original_pOutdoors{};
				D2DrlgVertexStrc original_pPathVertices[nPathVertices]{};
				D2DrlgOutdoorRoomStrc original_pOutdoorRoom{};
				std::vector<int32_t> original_pFloorGrid{};

				const auto setup_data = [&path_positions, room_x, room_y](
					D2DrlgLevelStrc& pLevel,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgStrc& pDrlg,
					D2DrlgOutdoorInfoStrc& pOutdoors,
					D2DrlgVertexStrc (&pPathVertices)[nPathVertices],
					D2DrlgOutdoorRoomStrc& pOutdoorRoom,
					std::vector<int32_t>& pFloorGrid
				) {
					for (int i = 0; i < nPathVertices; ++i)
					{
						pPathVertices[i].nPosX = path_positions[i].nX;
						pPathVertices[i].nPosY = path_positions[i].nY;
					}

					// The first path consists of three vertices, the second one of two
					pPathVertices[0].pNext = &pPathVertices[1];
					pPathVertices[1].pNext = &pPathVertices[2];
					pPathVertices[3].pNext = &pPathVertices[4];

					pOutdoors.pPathStarts[0] = &pPathVertices[0];
					pOutdoors.pPathStarts[1] = &pPathVertices[3];
					pOutdoors.nVertices = 2;

					pLevel.pDrlg = &pDrlg;
					pLevel.pOutdoors = &pOutdoors;

					setup_grid(pOutdoorRoom.pFloorGrid, pFloorGrid, nRoomWidth + 1, nRoomHeight + 1);

					pDrlgRoom.pLevel = &pLevel;
					pDrlgRoom.nTileXPos = room_x;
					pDrlgRoom.nTileYPos = room_y;
					pDrlgRoom.nTileWidth = nRoomWidth;
					pDrlgRoom.nTileHeight = nRoomHeight;
					pDrlgRoom.nType = DRLGTYPE_MAZE;
					pDrlgRoom.pOutdoor = &pOutdoorRoom;
				};

				setup_data(moo_pLevel, moo_pDrlgRoom, moo_pDrlg, moo_pOutdoors, moo_pPathVertices, moo_pOutdoorRoom, moo_pFloorGrid);
				setup_data(original_pLevel, original_pDrlgRoom, original_pDrlg, original_pOutdoors, original_pPathVertices, original_pOutdoorRoom, original_pFloorGrid);

				// Call both implementations
				sut(&moo_pLevel, &moo_pDrlgRoom);
				original(&original_pLevel, &original_pDrlgRoom);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pFloorGrid.data(), (int)moo_pFloorGrid.size() }), (DynamicArray<int>{ original_pFloorGrid.data(), (int)original_pFloorGrid.size() }), "Comparing pFloorGrid");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7F250")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_SpawnAct1DirtPaths, dll_base + 0x0003F250);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		// Positions of the Rogue Encampment relative to the level, so that its exit is next to the edge in the respective direction
		const D2CoordStrc town_offsets[] = { { -64, 8 }, { 8, -40 }, { 8 * nGridWidth, 8 }, { 8, 8 * nGridHeight } };

		SUBCASE("")
		{
			for (int nDirection = ALTDIR_WEST; nDirection <= ALTDIR_SOUTH; ++nDirection)
			{
				// A preset with an exit to the north adds a second path
				for (const BOOL bHasPreset : { FALSE, TRUE })
				{
					// Input data
					const auto level_x = random_integer(10, 1000) * 8;
					const auto level_y = random_integer(10, 1000) * 8;
					const auto town_x = level_x + town_offsets[nDirection].nX;
					const auto town_y = level_y + town_offsets[nDirection].nY;
					const auto seed_low = random_unsigned_integer();
					const auto seed_high = random_unsigned_integer();

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgOrthStrc moo_pRoomData{};
					D2DrlgLevelStrc moo_pTownLevel{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};
					D2DrlgOrthStrc original_pRoomData{};
					D2DrlgLevelStrc original_pTownLevel{};

					const auto setup_data = [nDirection, bHasPreset, level_x, level_y, town_x, town_y, seed_low, seed_high](
						D2DrlgLevelStrc& pLevel,
						D2DrlgStrc& pDrlg,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2,
						D2DrlgOrthStrc& pRoomData,
						D2DrlgLevelStrc& pTownLevel
					) {
						pTownLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
						pTownLevel.nPosX = town_x;
						pTownLevel.nPosY = town_y;

						pRoomData.pLevel = &pTownLevel;
						pRoomData.nDirection = static_cast<uint8_t>(nDirection);

						setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
						setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);

						if (bHasPreset)
						{
							constexpr int nPresetX = 6;
							constexpr int nPresetY = 1;
							pOutdoors.pGrid[0].pCellsFlags[nPresetX + pOutdoors.pGrid[0].pCellsRowOffsets[nPresetY]] = 24;
							pOutdoors.pGrid[2].pCellsFlags[nPresetX + pOutdoors.pGrid[2].pCellsRowOffsets[nPresetY]] = 0x200;
						}

						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;
						pOutdoors.pRoomData = &pRoomData;

						pLevel.pDrlg = &pDrlg;
						pLevel.nLevelId = LEVEL_BLOODMOOR;
						pLevel.pSeed.nLowSeed = seed_low;
						pLevel.pSeed.nHighSeed = seed_high;
						pLevel.nPosX = level_x;
						pLevel.nPosY = level_y;
						pLevel.nWidth = 8 * nGridWidth;
						pLevel.nHeight = 8 * nGridHeight;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pGrid0, moo_pGrid2, moo_pRoomData, moo_pTownLevel);
					setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pGrid0, original_pGrid2, original_pRoomData, original_pTownLevel);

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

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7F500")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_CalculatePathCoordinates, dll_base + 0x0003F500);

		SUBCASE("")
		{
			for (int nDirection = ALTDIR_WEST; nDirection <= ALTDIR_SOUTHWEST; ++nDirection)
			{
				for (int i = 0; i < 4; ++i)
				{
					// Input data
					const auto level_x = random_integer(-1000, 1000) * 8;
					const auto level_y = random_integer(-1000, 1000) * 8;
					const auto vertex_x = level_x + random_integer(-64, 128);
					const auto vertex_y = level_y + random_integer(-64, 128);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgVertexStrc moo_pVertex1{};
					D2DrlgVertexStrc moo_pVertex2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgVertexStrc original_pVertex1{};
					D2DrlgVertexStrc original_pVertex2{};

					const auto setup_data = [nDirection, level_x, level_y, vertex_x, vertex_y](
						D2DrlgLevelStrc& pLevel,
						D2DrlgVertexStrc& pVertex1,
						D2DrlgVertexStrc& pVertex2
					) {
						pLevel.nPosX = level_x;
						pLevel.nPosY = level_y;

						pVertex1.nPosX = vertex_x;
						pVertex1.nPosY = vertex_y;
						pVertex1.nDirection = static_cast<uint8_t>(nDirection);
					};

					setup_data(moo_pLevel, moo_pVertex1, moo_pVertex2);
					setup_data(original_pLevel, original_pVertex1, original_pVertex2);

					// Call both implementations
					sut(&moo_pLevel, &moo_pVertex1, &moo_pVertex2);
					original(&original_pLevel, &original_pVertex1, &original_pVertex2);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					MOO_CHECK_EQ(moo_pVertex1, original_pVertex1, "Comparing pVertex1");
					MOO_CHECK_EQ(moo_pVertex2, original_pVertex2, "Comparing pVertex2");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7F5B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD7F5B0, dll_base + 0x0003F5B0);

		// The bridge is searched with the grid width as limit for both coordinates, so the grid has to be square
		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;

		SUBCASE("")
		{
			// Bridges only exist on levels with rivers
			for (const BOOL bHasBridge : { FALSE, TRUE })
			{
				CAPTURE(bHasBridge);

				for (int iteration = 0; iteration < 8; ++iteration)
				{
					// Input data
					const auto level_x = random_integer(0, 1000) * 8;
					const auto level_y = random_integer(0, 1000) * 8;
					const auto bridge_y = random_integer(1, nGridHeight - 2);
					const auto nVertices = random_integer(1, 6);

					D2CoordStrc vertex_positions[6] = {};
					for (auto& vertex_position : vertex_positions)
					{
						vertex_position.nX = level_x + random_integer(0, 8 * nGridWidth - 1);
						vertex_position.nY = level_y + random_integer(0, 8 * nGridHeight - 1);
					}

					// Only some cells are blocked, so that the center of the paths can be placed
					const auto grid2_values = random_grid_values(nGridWidth, nGridHeight, 0x1B81, 3);

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					std::vector<int32_t> moo_pGrid0{};
					std::vector<int32_t> moo_pGrid2{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					std::vector<int32_t> original_pGrid0{};
					std::vector<int32_t> original_pGrid2{};

					const auto setup_data = [&vertex_positions, &grid2_values, bHasBridge, level_x, level_y, bridge_y, nVertices](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						std::vector<int32_t>& pGrid0,
						std::vector<int32_t>& pGrid2
					) {
						setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
						setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight, grid2_values);

						if (bHasBridge)
						{
							// Bridge preset (28) with picked file 1, in the center column
							const int nBridgeX = nGridWidth / 2 - 1;
							pOutdoors.pGrid[0].pCellsFlags[nBridgeX + pOutdoors.pGrid[0].pCellsRowOffsets[bridge_y]] = 28;
							pOutdoors.pGrid[2].pCellsFlags[nBridgeX + pOutdoors.pGrid[2].pCellsRowOffsets[bridge_y]] = 0x10000;

							pOutdoors.dwFlags = OUTDOOR_RIVER;
						}

						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;
						for (int i = 0; i < nVertices; ++i)
						{
							pOutdoors.pVertices[i].nPosX = vertex_positions[i].nX;
							pOutdoors.pVertices[i].nPosY = vertex_positions[i].nY;
						}
						pOutdoors.nVertices = nVertices;

						pLevel.nPosX = level_x;
						pLevel.nPosY = level_y;
						pLevel.nWidth = 8 * nGridWidth;
						pLevel.nHeight = 8 * nGridHeight;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pOutdoors, moo_pGrid0, moo_pGrid2);
					setup_data(original_pLevel, original_pOutdoors, original_pGrid0, original_pGrid2);

					// Call both implementations
					sut(&moo_pLevel);
					original(&original_pLevel);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD7F810")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD7F810, dll_base + 0x0003F810);

		constexpr int nGridWidth = 8;
		constexpr int nGridHeight = 8;
		constexpr int nMaxPathVertices = 5;

		SUBCASE("")
		{
			for (int nPathVertices = 0; nPathVertices <= nMaxPathVertices; ++nPathVertices)
			{
				// Paths ending in a direction (not 4) get an additional vertex at their start
				for (const BOOL bHasDirection : { FALSE, TRUE })
				{
					// Input data
					const int nVertexId = random_integer(0, 5);
					const auto level_x = random_integer(0, 1000) * 8;
					const auto level_y = random_integer(0, 1000) * 8;
					const auto seed_low = random_unsigned_integer();
					const auto seed_high = random_unsigned_integer();
					const int nDirection = bHasDirection ? random_integer(0, 3) : 4;

					// Vertices of the path, in grid coordinates
					D2CoordStrc path_positions[nMaxPathVertices] = {};
					for (auto& path_position : path_positions)
					{
						path_position.nX = random_integer(0, nGridWidth - 1);
						path_position.nY = random_integer(0, nGridHeight - 1);
					}

					// Start, end and center positions of the path, in level coordinates
					D2CoordStrc vertex_positions[4] = {};
					for (auto& vertex_position : vertex_positions)
					{
						vertex_position.nX = level_x + random_integer(0, 8 * nGridWidth - 1);
						vertex_position.nY = level_y + random_integer(0, 8 * nGridHeight - 1);
					}

					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgStrc moo_pDrlg{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					D2DrlgVertexStrc moo_pPathVertices[nMaxPathVertices]{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgStrc original_pDrlg{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					D2DrlgVertexStrc original_pPathVertices[nMaxPathVertices]{};

					const auto setup_data = [&path_positions, &vertex_positions, nPathVertices, nVertexId, nDirection, level_x, level_y, seed_low, seed_high](
						D2DrlgLevelStrc& pLevel,
						D2DrlgStrc& pDrlg,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						D2DrlgVertexStrc (&pPathVertices)[nMaxPathVertices]
					) {
						for (int i = 0; i < nPathVertices; ++i)
						{
							pPathVertices[i].nPosX = path_positions[i].nX;
							pPathVertices[i].nPosY = path_positions[i].nY;
							pPathVertices[i].pNext = i + 1 < nPathVertices ? &pPathVertices[i + 1] : nullptr;
						}

						pOutdoors.pPathStarts[nVertexId] = nPathVertices > 0 ? &pPathVertices[0] : nullptr;

						for (int i = 0; i < 4; ++i)
						{
							pOutdoors.pVertices[6 * i + nVertexId].nPosX = vertex_positions[i].nX;
							pOutdoors.pVertices[6 * i + nVertexId].nPosY = vertex_positions[i].nY;
						}
						pOutdoors.pVertices[18 + nVertexId].nDirection = static_cast<uint8_t>(nDirection);
						pOutdoors.nGridWidth = nGridWidth;
						pOutdoors.nGridHeight = nGridHeight;

						pLevel.pDrlg = &pDrlg;
						pLevel.pSeed.nLowSeed = seed_low;
						pLevel.pSeed.nHighSeed = seed_high;
						pLevel.nPosX = level_x;
						pLevel.nPosY = level_y;
						pLevel.nWidth = 8 * nGridWidth;
						pLevel.nHeight = 8 * nGridHeight;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pPathVertices);
					setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pPathVertices);

					// Call both implementations
					sut(&moo_pLevel, nVertexId);
					original(&original_pLevel, nVertexId);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD7F9B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTDOORS_InitAct4OutdoorLevel, dll_base + 0x0003F9B0);

		// The Chaos Sanctum consists of 5x5 presets which are placed 3 grid cells apart from each other
		constexpr int nGridWidth = 16;
		constexpr int nGridHeight = 16;

		for (const int nLevelPrestId : { LVLPREST_ACT4_LAVA_X, LVLPREST_ACT4_DIABLO_ARM_N, LVLPREST_ACT4_DIABLO_ARM_W, LVLPREST_ACT4_DIABLO_HEART, LVLPREST_ACT4_DIABLO_ARM_E, LVLPREST_ACT4_DIABLO_ARM_S, LVLPREST_ACT4_DIABLO_ENTRY })
		{
			REQUIRE(lvlprest_txt[nLevelPrestId].nSizeX / 8 <= nGridWidth - 12);
			REQUIRE(lvlprest_txt[nLevelPrestId].nSizeY / 8 <= nGridHeight - 12);
		}

		SUBCASE("Chaos Sanctum")
		{
			// Input data
			const auto seed_low = random_unsigned_integer();
			const auto seed_high = random_unsigned_integer();

			// Corners of the level, in grid coordinates
			const D2CoordStrc border_positions[] = { { 0, nGridHeight - 1 }, { 0, 0 }, { nGridWidth - 1, 0 }, { nGridWidth - 1, nGridHeight - 1 } };
			// Outgoing links of the borders
			int32_t border_flags[4] = {};
			for (auto& border_flag : border_flags)
			{
				border_flag = random_integer(0, 1);
			}

			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc moo_pDrlg{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			D2DrlgVertexStrc moo_pBorderVertices[4]{};
			std::vector<int32_t> moo_pGrid0{};
			std::vector<int32_t> moo_pGrid1{};
			std::vector<int32_t> moo_pGrid2{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			D2DrlgVertexStrc original_pBorderVertices[4]{};
			std::vector<int32_t> original_pGrid0{};
			std::vector<int32_t> original_pGrid1{};
			std::vector<int32_t> original_pGrid2{};

			const auto setup_data = [&border_positions, &border_flags, seed_low, seed_high](
				D2DrlgLevelStrc& pLevel,
				D2DrlgStrc& pDrlg,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				D2DrlgVertexStrc (&pBorderVertices)[4],
				std::vector<int32_t>& pGrid0,
				std::vector<int32_t>& pGrid1,
				std::vector<int32_t>& pGrid2
			) {
				// The borders form a closed ring
				for (int i = 0; i < 4; ++i)
				{
					pBorderVertices[i].nPosX = border_positions[i].nX;
					pBorderVertices[i].nPosY = border_positions[i].nY;
					pBorderVertices[i].dwFlags = border_flags[i];
					pBorderVertices[i].pNext = &pBorderVertices[(i + 1) % 4];
				}

				setup_grid(pOutdoors.pGrid[0], pGrid0, nGridWidth, nGridHeight);
				setup_grid(pOutdoors.pGrid[1], pGrid1, nGridWidth, nGridHeight);
				setup_grid(pOutdoors.pGrid[2], pGrid2, nGridWidth, nGridHeight);
				pOutdoors.nGridWidth = nGridWidth;
				pOutdoors.nGridHeight = nGridHeight;
				pOutdoors.pVertex = &pBorderVertices[0];

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_CHAOSSANCTUM;
				pLevel.pSeed.nLowSeed = seed_low;
				pLevel.pSeed.nHighSeed = seed_high;
				pLevel.nWidth = 8 * nGridWidth;
				pLevel.nHeight = 8 * nGridHeight;
				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pDrlg, moo_pOutdoors, moo_pBorderVertices, moo_pGrid0, moo_pGrid1, moo_pGrid2);
			setup_data(original_pLevel, original_pDrlg, original_pOutdoors, original_pBorderVertices, original_pGrid0, original_pGrid1, original_pGrid2);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid0.data(), (int)moo_pGrid0.size() }), (DynamicArray<int>{ original_pGrid0.data(), (int)original_pGrid0.size() }), "Comparing pGrid[0]");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid1.data(), (int)moo_pGrid1.size() }), (DynamicArray<int>{ original_pGrid1.data(), (int)original_pGrid1.size() }), "Comparing pGrid[1]");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pGrid2.data(), (int)moo_pGrid2.size() }), (DynamicArray<int>{ original_pGrid2.data(), (int)original_pGrid2.size() }), "Comparing pGrid[2]");
		}
	}
}
