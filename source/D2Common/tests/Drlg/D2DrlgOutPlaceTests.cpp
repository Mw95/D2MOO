#include <D2CommonTestDefines.h>

#ifdef DRLG_OUTPLACE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstdlib>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>
#include <Fixtures/DataTbls/Fixtures.h>

#include <DataTbls/LevelsIds.h>
#include <Drlg/D2DrlgOutdoors.h>
#include <Drlg/D2DrlgOutPlace.h>
#include <Drlg/D2DrlgOutRoom.h>


TEST_SUITE("D2DrlgOutPlaceTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	// Lets pDrlgGrid use the given buffers as cells and row offsets. The grid width is deduced from the buffer sizes.
	template<size_t CellCount, size_t Height>
	void initialize_grid(D2DrlgGridStrc& pDrlgGrid, int32_t(&pCellsFlags)[CellCount], int32_t(&pCellsRowOffsets)[Height])
	{
		constexpr auto nWidth = static_cast<int32_t>(CellCount / Height);
		constexpr auto nHeight = static_cast<int32_t>(Height);

		for (auto i = 0; i < nHeight; ++i)
		{
			pCellsRowOffsets[i] = i * nWidth;
		}

		pDrlgGrid.pCellsFlags = pCellsFlags;
		pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
		pDrlgGrid.nWidth = nWidth;
		pDrlgGrid.nHeight = nHeight;
	}


	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD80480")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_BuildKurast, dll_base + 0x00040480);

		SUBCASE("Kurast Causeway")
		{
			constexpr int32_t grid_width = 32;
			constexpr int32_t grid_height = 32;

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			int32_t moo_pPresetGridCells[grid_width * grid_height]{};
			int32_t moo_pPackedGridCells[grid_width * grid_height]{};
			int32_t moo_pGridRowOffsets[grid_height]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			int32_t original_pPresetGridCells[grid_width * grid_height]{};
			int32_t original_pPackedGridCells[grid_width * grid_height]{};
			int32_t original_pGridRowOffsets[grid_height]{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				int32_t(&pPresetGridCells)[grid_width * grid_height],
				int32_t(&pPackedGridCells)[grid_width * grid_height],
				int32_t(&pGridRowOffsets)[grid_height]
			) {
				initialize_grid(pOutdoors.pGrid[0], pPresetGridCells, pGridRowOffsets);
				initialize_grid(pOutdoors.pGrid[2], pPackedGridCells, pGridRowOffsets);

				pLevel.nLevelId = LEVEL_KURASTCAUSEWAY;
				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pPresetGridCells, moo_pPackedGridCells, moo_pGridRowOffsets);
			setup_data(original_pLevel, original_pOutdoors, original_pPresetGridCells, original_pPackedGridCells, original_pGridRowOffsets);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}

		SUBCASE("Not a Kurast level")
		{
			const int32_t level_id = GENERATE(LEVEL_KURASTDOCKTOWN, LEVEL_SPIDERFOREST, LEVEL_TRAVINCAL);

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgLevelStrc original_pLevel{};

			const auto setup_data = [level_id](
				D2DrlgLevelStrc& pLevel
			) {
				pLevel.nLevelId = level_id;
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

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD806A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_InitAct3OutdoorLevel, dll_base + 0x000406A0);

		SUBCASE("Travincal")
		{
			constexpr int32_t grid_width = 32;
			constexpr int32_t grid_height = 32;

			const auto seed = random_unsigned_integer();

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			D2DrlgVertexStrc moo_pVertex{};
			int32_t moo_pPresetGridCells[grid_width * grid_height]{};
			int32_t moo_pLinkGridCells[grid_width * grid_height]{};
			int32_t moo_pPackedGridCells[grid_width * grid_height]{};
			int32_t moo_pGridRowOffsets[grid_height]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			D2DrlgVertexStrc original_pVertex{};
			int32_t original_pPresetGridCells[grid_width * grid_height]{};
			int32_t original_pLinkGridCells[grid_width * grid_height]{};
			int32_t original_pPackedGridCells[grid_width * grid_height]{};
			int32_t original_pGridRowOffsets[grid_height]{};

			const auto setup_data = [seed](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				D2DrlgVertexStrc& pVertex,
				int32_t(&pPresetGridCells)[grid_width * grid_height],
				int32_t(&pLinkGridCells)[grid_width * grid_height],
				int32_t(&pPackedGridCells)[grid_width * grid_height],
				int32_t(&pGridRowOffsets)[grid_height]
			) {
				initialize_grid(pOutdoors.pGrid[0], pPresetGridCells, pGridRowOffsets);
				initialize_grid(pOutdoors.pGrid[1], pLinkGridCells, pGridRowOffsets);
				initialize_grid(pOutdoors.pGrid[2], pPackedGridCells, pGridRowOffsets);
				pOutdoors.nGridWidth = pOutdoors.pGrid[2].nWidth;
				pOutdoors.nGridHeight = pOutdoors.pGrid[2].nHeight;

				// A single linked vertex (not on the grid border) forming a closed vertex ring
				pVertex.nPosX = 4;
				pVertex.nPosY = 4;
				pVertex.dwFlags = 1;
				pVertex.pNext = &pVertex;
				pOutdoors.pVertex = &pVertex;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_TRAVINCAL;
				pLevel.pSeed.nLowSeed = seed;
				pLevel.pSeed.nHighSeed = 666;
				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pOutdoors, moo_pVertex, moo_pPresetGridCells, moo_pLinkGridCells, moo_pPackedGridCells, moo_pGridRowOffsets);
			setup_data(original_pDrlg, original_pLevel, original_pOutdoors, original_pVertex, original_pPresetGridCells, original_pLinkGridCells, original_pPackedGridCells, original_pGridRowOffsets);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80750")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD80750, dll_base + 0x00040750);

		constexpr int32_t grid_width = 8;
		constexpr int32_t grid_height = 8;

		// Input data
		const auto level_x = 8 * static_cast<int32_t>(random_unsigned_integer(0, 100));
		const auto level_y = 8 * static_cast<int32_t>(random_unsigned_integer(0, 100));
		const auto vertex_id = static_cast<int32_t>(random_unsigned_integer(0, 5));

		int32_t start_x{};
		int32_t start_y{};
		int32_t end_x{};
		int32_t end_y{};
		auto has_obstacles = 0;

		SUBCASE("adjacent vertices")
		{
			start_x = 2;
			start_y = 3;
			end_x = 3;
			end_y = 3;
		}

		SUBCASE("distant vertices")
		{
			start_x = 1;
			start_y = 1;
			end_x = 6;
			end_y = 5;
		}

		SUBCASE("distant vertices with obstacles")
		{
			start_x = 1;
			start_y = 1;
			end_x = 6;
			end_y = 1;
			has_obstacles = 1;
		}

		D2DrlgStrc moo_pDrlg{};
		D2DrlgLevelStrc moo_pLevel{};
		D2DrlgOutdoorInfoStrc moo_pOutdoors{};
		int32_t moo_pPackedGridCells[grid_width * grid_height]{};
		int32_t moo_pGridRowOffsets[grid_height]{};
		D2DrlgStrc original_pDrlg{};
		D2DrlgLevelStrc original_pLevel{};
		D2DrlgOutdoorInfoStrc original_pOutdoors{};
		int32_t original_pPackedGridCells[grid_width * grid_height]{};
		int32_t original_pGridRowOffsets[grid_height]{};
		int nVertexId = vertex_id;

		const auto setup_data = [level_x, level_y, vertex_id, start_x, start_y, end_x, end_y, has_obstacles](
			D2DrlgStrc& pDrlg,
			D2DrlgLevelStrc& pLevel,
			D2DrlgOutdoorInfoStrc& pOutdoors,
			int32_t(&pPackedGridCells)[grid_width * grid_height],
			int32_t(&pGridRowOffsets)[grid_height]
		) {
			initialize_grid(pOutdoors.pGrid[2], pPackedGridCells, pGridRowOffsets);
			pOutdoors.nWidth = 0;
			pOutdoors.nHeight = 0;
			pOutdoors.nGridWidth = pOutdoors.pGrid[2].nWidth;
			pOutdoors.nGridHeight = pOutdoors.pGrid[2].nHeight;

			if (has_obstacles)
			{
				// Wall of cells with a picked file in column 4, only the last two rows can be passed
				for (auto y = 0; y < pOutdoors.nGridHeight - 2; ++y)
				{
					D2DrlgOutdoorPackedGrid2InfoStrc tPackedInfo{ 0 };
					tPackedInfo.bHasPickedFile = true;
					pPackedGridCells[4 + pGridRowOffsets[y]] = tPackedInfo.nPackedValue;
				}
			}

			// Vertex positions are in tiles, grid cells are 8x8 tiles
			pOutdoors.pVertices[6 + vertex_id].nPosX = level_x + 8 * start_x + 4;
			pOutdoors.pVertices[6 + vertex_id].nPosY = level_y + 8 * start_y + 4;
			pOutdoors.pVertices[12 + vertex_id].nPosX = level_x + 8 * end_x + 4;
			pOutdoors.pVertices[12 + vertex_id].nPosY = level_y + 8 * end_y + 4;

			pLevel.pDrlg = &pDrlg;
			pLevel.nPosX = level_x;
			pLevel.nPosY = level_y;
			pLevel.pOutdoors = &pOutdoors;
		};

		setup_data(moo_pDrlg, moo_pLevel, moo_pOutdoors, moo_pPackedGridCells, moo_pGridRowOffsets);
		setup_data(original_pDrlg, original_pLevel, original_pOutdoors, original_pPackedGridCells, original_pGridRowOffsets);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevel, nVertexId);
		const auto original_result = original(&original_pLevel, nVertexId);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80BE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD80BE0, dll_base + 0x00040BE0);

		SUBCASE("")
		{
			// Coordinate differences between two consecutive vertices
			const int directions[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

			for (const auto& direction : directions)
			{
				// -1: default, 0-3: act 1/2/4 border presets, 4-5: act 5 barricade border presets
				for (auto preset_type = -1; preset_type <= 5; ++preset_type)
				{
					int a1 = direction[0];
					int a2 = direction[1];
					int a3 = preset_type;

					// Call both implementations
					const auto moo_result = sut(a1, a2, a3);
					const auto original_result = original(a1, a2, a3);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80C10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD80C10, dll_base + 0x00040C10);

		SUBCASE("")
		{
			// Coordinate differences between two consecutive vertices
			const int directions[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

			for (const auto& current_direction : directions)
			{
				for (const auto& next_direction : directions)
				{
					// The differences are doubled by the caller for vertices without flag 2
					for (auto current_factor = 1; current_factor <= 2; ++current_factor)
					{
						for (auto next_factor = 1; next_factor <= 2; ++next_factor)
						{
							// -1: default, 0-3: act 1/2/4 border presets, 4-5: act 5 barricade border presets
							for (auto preset_type = -1; preset_type <= 5; ++preset_type)
							{
								int a1 = current_factor * current_direction[0];
								int a2 = current_factor * current_direction[1];
								int a3 = next_factor * next_direction[0];
								int a4 = next_factor * next_direction[1];
								int a5 = preset_type;

								// Call both implementations
								const auto moo_result = sut(a1, a2, a3, a4, a5);
								const auto original_result = original(a1, a2, a3, a4, a5);

								// Compare return values
								MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
							}
						}
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80C80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_SetBlankBorderGridCells, dll_base + 0x00040C80);

		SUBCASE("")
		{
			constexpr int32_t grid_width = 9;
			constexpr int32_t grid_height = 9;

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			int32_t moo_pPackedGridCells[grid_width * grid_height]{};
			int32_t moo_pGridRowOffsets[grid_height]{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			int32_t original_pPackedGridCells[grid_width * grid_height]{};
			int32_t original_pGridRowOffsets[grid_height]{};

			const auto setup_data = [](
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				int32_t(&pPackedGridCells)[grid_width * grid_height],
				int32_t(&pGridRowOffsets)[grid_height]
			) {
				initialize_grid(pOutdoors.pGrid[2], pPackedGridCells, pGridRowOffsets);
				pOutdoors.nGridWidth = pOutdoors.pGrid[2].nWidth;
				pOutdoors.nGridHeight = pOutdoors.pGrid[2].nHeight;

				// Level border shaped like a diamond touching the middle of each grid side, the corners outside of it are blank
				const auto center_x = pOutdoors.nGridWidth / 2;
				const auto center_y = pOutdoors.nGridHeight / 2;
				for (auto y = 0; y < pOutdoors.nGridHeight; ++y)
				{
					for (auto x = 0; x < pOutdoors.nGridWidth; ++x)
					{
						if (std::abs(x - center_x) + std::abs(y - center_y) == center_x)
						{
							D2DrlgOutdoorPackedGrid2InfoStrc tPackedInfo{ 0 };
							tPackedInfo.nUnkb00 = true;
							pPackedGridCells[x + pGridRowOffsets[y]] = tPackedInfo.nPackedValue;
						}
					}
				}

				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pLevel, moo_pOutdoors, moo_pPackedGridCells, moo_pGridRowOffsets);
			setup_data(original_pLevel, original_pOutdoors, original_pPackedGridCells, original_pGridRowOffsets);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD80DA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_SetOutGridLinkFlags, dll_base + 0x00040DA0);

		SUBCASE("")
		{
			constexpr int32_t grid_width = 8;
			constexpr int32_t grid_height = 8;

			const auto level_x = 8 * static_cast<int32_t>(random_unsigned_integer(0, 100));
			const auto level_y = 8 * static_cast<int32_t>(random_unsigned_integer(0, 100));

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgWarpStrc moo_pDrlgWarp{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgLevelStrc moo_pAdjacentLevel{};
			D2DrlgOrthStrc moo_pRoomData{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			D2DrlgVertexStrc moo_pVertices[4]{};
			int32_t moo_pLinkGridCells[grid_width * grid_height]{};
			int32_t moo_pPackedGridCells[grid_width * grid_height]{};
			int32_t moo_pGridRowOffsets[grid_height]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgWarpStrc original_pDrlgWarp{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgLevelStrc original_pAdjacentLevel{};
			D2DrlgOrthStrc original_pRoomData{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			D2DrlgVertexStrc original_pVertices[4]{};
			int32_t original_pLinkGridCells[grid_width * grid_height]{};
			int32_t original_pPackedGridCells[grid_width * grid_height]{};
			int32_t original_pGridRowOffsets[grid_height]{};

			const auto setup_data = [level_x, level_y](
				D2DrlgStrc& pDrlg,
				D2DrlgWarpStrc& pDrlgWarp,
				D2DrlgLevelStrc& pLevel,
				D2DrlgLevelStrc& pAdjacentLevel,
				D2DrlgOrthStrc& pRoomData,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				D2DrlgVertexStrc(&pVertices)[4],
				int32_t(&pLinkGridCells)[grid_width * grid_height],
				int32_t(&pPackedGridCells)[grid_width * grid_height],
				int32_t(&pGridRowOffsets)[grid_height]
			) {
				initialize_grid(pOutdoors.pGrid[1], pLinkGridCells, pGridRowOffsets);
				initialize_grid(pOutdoors.pGrid[2], pPackedGridCells, pGridRowOffsets);
				pOutdoors.nGridWidth = pOutdoors.pGrid[2].nWidth;
				pOutdoors.nGridHeight = pOutdoors.pGrid[2].nHeight;

				// Vertex ring along the grid border
				pVertices[0].nPosX = 0;
				pVertices[0].nPosY = 0;
				pVertices[0].dwFlags = 1;
				pVertices[1].nPosX = pOutdoors.nGridWidth - 1;
				pVertices[1].nPosY = 0;
				pVertices[2].nPosX = pOutdoors.nGridWidth - 1;
				pVertices[2].nPosY = pOutdoors.nGridHeight - 1;
				pVertices[2].nDirection = 1;
				pVertices[2].dwFlags = 1;
				pVertices[3].nPosX = 0;
				pVertices[3].nPosY = pOutdoors.nGridHeight - 1;
				for (auto i = 0; i < 4; ++i)
				{
					pVertices[i].pNext = &pVertices[(i + 1) % 4];
				}
				pOutdoors.pVertex = &pVertices[0];

				// Adjacent level north of the first vertex
				pAdjacentLevel.nLevelId = LEVEL_BURIALGROUNDS;
				pAdjacentLevel.nPosX = level_x;
				pAdjacentLevel.nPosY = level_y - 64;
				pAdjacentLevel.nWidth = 64;
				pAdjacentLevel.nHeight = 64;

				pRoomData.pLevel = &pAdjacentLevel;
				pRoomData.nDirection = 1;
				pRoomData.pBox = &pAdjacentLevel.pLevelCoords;
				pOutdoors.pRoomData = &pRoomData;

				pDrlgWarp.nLevel = LEVEL_COLDPLAINS;
				pDrlgWarp.nVis[0] = LEVEL_BLOODMOOR;
				pDrlgWarp.nVis[1] = LEVEL_BURIALGROUNDS;
				pDrlg.pWarp = &pDrlgWarp;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_COLDPLAINS;
				pLevel.nPosX = level_x;
				pLevel.nPosY = level_y;
				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pDrlg, moo_pDrlgWarp, moo_pLevel, moo_pAdjacentLevel, moo_pRoomData, moo_pOutdoors, moo_pVertices, moo_pLinkGridCells, moo_pPackedGridCells, moo_pGridRowOffsets);
			setup_data(original_pDrlg, original_pDrlgWarp, original_pLevel, original_pAdjacentLevel, original_pRoomData, original_pOutdoors, original_pVertices, original_pLinkGridCells, original_pPackedGridCells, original_pGridRowOffsets);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(LvlPrestTxtFixture<NoopFixture>, "D2Common.0x6FD80E10" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_PlaceAct1245OutdoorBorders, dll_base + 0x00040E10);

		SUBCASE("")
		{
			constexpr int32_t grid_width = 8;
			constexpr int32_t grid_height = 8;

			const int32_t level_ids[] = { LEVEL_BLOODMOOR, LEVEL_ROCKYWASTE, LEVEL_OUTERSTEPPES, LEVEL_BLOODYFOOTHILLS };
			const int32_t level_types[] = { LVLTYPE_ACT1_WILDERNESS, LVLTYPE_ACT2_DESERT, LVLTYPE_ACT4_MESA, LVLTYPE_ACT5_BARRICADE };
			const auto level_index = GENERATE(0, 1, 2, 3);
			const auto level_id = level_ids[level_index];
			const auto level_type = level_types[level_index];

			const auto seed = random_unsigned_integer();

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			D2DrlgVertexStrc moo_pVertices[4]{};
			int32_t moo_pPresetGridCells[grid_width * grid_height]{};
			int32_t moo_pPackedGridCells[grid_width * grid_height]{};
			int32_t moo_pGridRowOffsets[grid_height]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			D2DrlgVertexStrc original_pVertices[4]{};
			int32_t original_pPresetGridCells[grid_width * grid_height]{};
			int32_t original_pPackedGridCells[grid_width * grid_height]{};
			int32_t original_pGridRowOffsets[grid_height]{};

			const auto setup_data = [level_id, level_type, seed](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				D2DrlgVertexStrc(&pVertices)[4],
				int32_t(&pPresetGridCells)[grid_width * grid_height],
				int32_t(&pPackedGridCells)[grid_width * grid_height],
				int32_t(&pGridRowOffsets)[grid_height]
			) {
				initialize_grid(pOutdoors.pGrid[0], pPresetGridCells, pGridRowOffsets);
				initialize_grid(pOutdoors.pGrid[2], pPackedGridCells, pGridRowOffsets);
				pOutdoors.nGridWidth = pOutdoors.pGrid[2].nWidth;
				pOutdoors.nGridHeight = pOutdoors.pGrid[2].nHeight;

				// Vertex ring along the grid border, the first edge links to another level
				pVertices[0].nPosX = 0;
				pVertices[0].nPosY = 0;
				pVertices[0].dwFlags = 1;
				pVertices[1].nPosX = pOutdoors.nGridWidth - 1;
				pVertices[1].nPosY = 0;
				pVertices[2].nPosX = pOutdoors.nGridWidth - 1;
				pVertices[2].nPosY = pOutdoors.nGridHeight - 1;
				pVertices[3].nPosX = 0;
				pVertices[3].nPosY = pOutdoors.nGridHeight - 1;
				for (auto i = 0; i < 4; ++i)
				{
					pVertices[i].pNext = &pVertices[(i + 1) % 4];
				}
				pOutdoors.pVertex = &pVertices[0];

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = level_type;
				pLevel.pSeed.nLowSeed = seed;
				pLevel.pSeed.nHighSeed = 666;
				pLevel.pOutdoors = &pOutdoors;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pOutdoors, moo_pVertices, moo_pPresetGridCells, moo_pPackedGridCells, moo_pGridRowOffsets);
			setup_data(original_pDrlg, original_pLevel, original_pOutdoors, original_pVertices, original_pPresetGridCells, original_pPackedGridCells, original_pGridRowOffsets);

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}

	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD81330")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81330, dll_base + 0x00041330);

		const int32_t level_id = GENERATE(LEVEL_ROGUEENCAMPMENT, LEVEL_MOOMOOFARM, LEVEL_LUTGHOLEIN, LEVEL_CANYONOFTHEMAGI, LEVEL_THEPANDEMONIUMFORTRESS, LEVEL_CHAOSSANCTUM, LEVEL_HARROGATH);

		const auto iteration = static_cast<int32_t>(random_unsigned_integer(0, 14));
		const auto current_rand = static_cast<int32_t>(random_unsigned_integer(0, 3));
		int32_t first_rand = 0;

		SUBCASE("direction not rolled yet")
		{
			first_rand = -1;
		}

		SUBCASE("direction already rolled")
		{
			first_rand = static_cast<int32_t>(random_unsigned_integer(0, 3));
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};

		const auto setup_data = [iteration, current_rand, first_rand, level_id](
			D2DrlgLevelLinkDataStrc& pLevelLinkData
		) {
			pLevelLinkData.nRand[0][iteration] = current_rand;
			pLevelLinkData.nRand[1][iteration] = first_rand;
			pLevelLinkData.nIteration = iteration;
			pLevelLinkData.nCurrentLevel = level_id;
		};

		setup_data(moo_pLevelLinkData);
		setup_data(original_pLevelLinkData);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData);
		const auto original_result = original(&original_pLevelLinkData);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81380")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81380, dll_base + 0x00041380);

		const auto seed = random_unsigned_integer();
		const auto iteration = static_cast<int32_t>(random_unsigned_integer(1, 14));
		const auto level_link = static_cast<int32_t>(random_unsigned_integer(0, iteration - 1));
		const D2DrlgCoordStrc linked_level_coord = {
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
		};
		const auto width = static_cast<int32_t>(random_unsigned_integer(1, 200));
		const auto height = static_cast<int32_t>(random_unsigned_integer(1, 200));

		int32_t current_rand = 0;
		int32_t first_rand = 0;

		SUBCASE("direction not rolled yet")
		{
			current_rand = -1;
			first_rand = -1;
		}

		SUBCASE("try next direction")
		{
			current_rand = static_cast<int32_t>(random_unsigned_integer(0, 3));
			first_rand = current_rand;
		}

		SUBCASE("all directions tried")
		{
			current_rand = static_cast<int32_t>(random_unsigned_integer(0, 3));
			first_rand = (current_rand + 1) % 4;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLinkStrc moo_pLink[15]{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		D2DrlgLinkStrc original_pLink[15]{};

		const auto setup_data = [seed, iteration, level_link, linked_level_coord, width, height, current_rand, first_rand](
			D2DrlgLevelLinkDataStrc& pLevelLinkData,
			D2DrlgLinkStrc(&pLink)[15]
		) {
			pLink[iteration].nLevelLink = level_link;

			pLevelLinkData.pSeed.nLowSeed = seed;
			pLevelLinkData.pSeed.nHighSeed = 666;
			pLevelLinkData.pLevelCoord[level_link] = linked_level_coord;
			pLevelLinkData.pLevelCoord[iteration].nWidth = width;
			pLevelLinkData.pLevelCoord[iteration].nHeight = height;
			pLevelLinkData.pLink = pLink;
			pLevelLinkData.nRand[0][iteration] = current_rand;
			pLevelLinkData.nRand[1][iteration] = first_rand;
			pLevelLinkData.nIteration = iteration;
		};

		setup_data(moo_pLevelLinkData, moo_pLink);
		setup_data(original_pLevelLinkData, original_pLink);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData);
		const auto original_result = original(&original_pLevelLinkData);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81430")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81430, dll_base + 0x00041430);
		
		SUBCASE("")
		{
			const auto direction = GENERATE(-1, 0, 1, 2, 3, 4);
			const auto offset_type = GENERATE(0, 1, 2, 3);

			const D2DrlgCoordStrc coord1 = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};
			const D2DrlgCoordStrc coord2 = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};

			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord1{};
			D2DrlgCoordStrc moo_pDrlgCoord2{};
			D2DrlgCoordStrc original_pDrlgCoord1{};
			D2DrlgCoordStrc original_pDrlgCoord2{};
			int a3 = direction;
			int a4 = offset_type;

			const auto setup_data = [coord1, coord2](
				D2DrlgCoordStrc& pDrlgCoord1,
				D2DrlgCoordStrc& pDrlgCoord2
			) {
				pDrlgCoord1 = coord1;
				pDrlgCoord2 = coord2;
			};

			setup_data(moo_pDrlgCoord1, moo_pDrlgCoord2);
			setup_data(original_pDrlgCoord1, original_pDrlgCoord2);

			// Call both implementations
			sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, a3, a4);
			original(&original_pDrlgCoord1, &original_pDrlgCoord2, a3, a4);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81530")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81530, dll_base + 0x00041530);

		const auto seed = random_unsigned_integer();
		const auto iteration = static_cast<int32_t>(random_unsigned_integer(1, 14));
		const auto level_link = static_cast<int32_t>(random_unsigned_integer(0, iteration - 1));
		const D2DrlgCoordStrc linked_level_coord = {
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
		};
		const auto width = static_cast<int32_t>(random_unsigned_integer(1, 200));
		const auto height = static_cast<int32_t>(random_unsigned_integer(1, 200));

		int32_t current_rand = 0;
		int32_t first_rand = 0;

		SUBCASE("direction not rolled yet")
		{
			current_rand = -1;
			first_rand = -1;
		}

		SUBCASE("try next direction")
		{
			current_rand = static_cast<int32_t>(random_unsigned_integer(0, 7));
			first_rand = current_rand;
		}

		SUBCASE("all directions tried")
		{
			current_rand = static_cast<int32_t>(random_unsigned_integer(0, 7));
			first_rand = (current_rand + 1) % 8;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLinkStrc moo_pLink[15]{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		D2DrlgLinkStrc original_pLink[15]{};

		const auto setup_data = [seed, iteration, level_link, linked_level_coord, width, height, current_rand, first_rand](
			D2DrlgLevelLinkDataStrc& pLevelLinkData,
			D2DrlgLinkStrc(&pLink)[15]
		) {
			pLink[iteration].nLevelLink = level_link;

			pLevelLinkData.pSeed.nLowSeed = seed;
			pLevelLinkData.pSeed.nHighSeed = 666;
			pLevelLinkData.pLevelCoord[level_link] = linked_level_coord;
			pLevelLinkData.pLevelCoord[iteration].nWidth = width;
			pLevelLinkData.pLevelCoord[iteration].nHeight = height;
			pLevelLinkData.pLink = pLink;
			pLevelLinkData.nRand[0][iteration] = current_rand;
			pLevelLinkData.nRand[1][iteration] = first_rand;
			pLevelLinkData.nIteration = iteration;
		};

		setup_data(moo_pLevelLinkData, moo_pLink);
		setup_data(original_pLevelLinkData, original_pLink);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData);
		const auto original_result = original(&original_pLevelLinkData);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD815E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD815E0, dll_base + 0x000415E0);
		
		SUBCASE("")
		{
			const auto direction = GENERATE(-1, 0, 1, 2, 3, 4, 5, 6, 7, 8);
			const auto offset_type = GENERATE(0, 1);

			const D2DrlgCoordStrc coord1 = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};
			const D2DrlgCoordStrc coord2 = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};

			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord1{};
			D2DrlgCoordStrc moo_pDrlgCoord2{};
			D2DrlgCoordStrc original_pDrlgCoord1{};
			D2DrlgCoordStrc original_pDrlgCoord2{};
			int a3 = direction;
			int a4 = offset_type;

			const auto setup_data = [coord1, coord2](
				D2DrlgCoordStrc& pDrlgCoord1,
				D2DrlgCoordStrc& pDrlgCoord2
			) {
				pDrlgCoord1 = coord1;
				pDrlgCoord2 = coord2;
			};

			setup_data(moo_pDrlgCoord1, moo_pDrlgCoord2);
			setup_data(original_pDrlgCoord1, original_pDrlgCoord2);

			// Call both implementations
			sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, a3, a4);
			original(&original_pDrlgCoord1, &original_pDrlgCoord2, a3, a4);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81720")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81720, dll_base + 0x00041720);

		const auto seed = random_unsigned_integer();
		const auto iteration = static_cast<int32_t>(random_unsigned_integer(1, 14));
		const auto level_link = static_cast<int32_t>(random_unsigned_integer(0, iteration - 1));
		const D2DrlgCoordStrc linked_level_coord = {
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
		};
		const auto width = static_cast<int32_t>(random_unsigned_integer(1, 200));
		const auto height = static_cast<int32_t>(random_unsigned_integer(1, 200));

		// nRand[0]: current direction, nRand[1]: first direction, nRand[2]: current side, nRand[3]: first side
		int32_t rands[4]{};

		SUBCASE("direction not rolled yet")
		{
			rands[0] = -1;
			rands[1] = -1;
			rands[2] = -1;
			rands[3] = -1;
		}

		SUBCASE("try next direction")
		{
			rands[0] = static_cast<int32_t>(random_unsigned_integer(0, 3));
			rands[1] = static_cast<int32_t>(random_unsigned_integer(0, 3));
			rands[2] = static_cast<int32_t>(random_unsigned_integer(0, 1));
			rands[3] = static_cast<int32_t>(random_unsigned_integer(0, 1));
		}

		SUBCASE("all directions tried")
		{
			rands[0] = static_cast<int32_t>(random_unsigned_integer(0, 3));
			rands[2] = static_cast<int32_t>(random_unsigned_integer(0, 1));
			rands[1] = (rands[2] + rands[0]) % 4;
			rands[3] = (rands[2] + 1) % 2;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLinkStrc moo_pLink[15]{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		D2DrlgLinkStrc original_pLink[15]{};

		const auto setup_data = [seed, iteration, level_link, linked_level_coord, width, height, &rands](
			D2DrlgLevelLinkDataStrc& pLevelLinkData,
			D2DrlgLinkStrc(&pLink)[15]
		) {
			pLink[iteration].nLevelLink = level_link;

			pLevelLinkData.pSeed.nLowSeed = seed;
			pLevelLinkData.pSeed.nHighSeed = 666;
			pLevelLinkData.pLevelCoord[level_link] = linked_level_coord;
			pLevelLinkData.pLevelCoord[iteration].nWidth = width;
			pLevelLinkData.pLevelCoord[iteration].nHeight = height;
			pLevelLinkData.pLink = pLink;
			for (auto i = 0; i < 4; ++i)
			{
				pLevelLinkData.nRand[i][iteration] = rands[i];
			}
			pLevelLinkData.nIteration = iteration;
		};

		setup_data(moo_pLevelLinkData, moo_pLink);
		setup_data(original_pLevelLinkData, original_pLink);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData);
		const auto original_result = original(&original_pLevelLinkData);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81850")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81850, dll_base + 0x00041850);
		
		SUBCASE("")
		{
			const auto direction = GENERATE(-1, 0, 1, 2, 3, 4);
			const auto offset_type = GENERATE(0, 1, 2, 3);

			const D2DrlgCoordStrc coord1 = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};
			const D2DrlgCoordStrc coord2 = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};

			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord1{};
			D2DrlgCoordStrc moo_pDrlgCoord2{};
			D2DrlgCoordStrc original_pDrlgCoord1{};
			D2DrlgCoordStrc original_pDrlgCoord2{};
			int a3 = direction;
			int a4 = offset_type;

			const auto setup_data = [coord1, coord2](
				D2DrlgCoordStrc& pDrlgCoord1,
				D2DrlgCoordStrc& pDrlgCoord2
			) {
				pDrlgCoord1 = coord1;
				pDrlgCoord2 = coord2;
			};

			setup_data(moo_pDrlgCoord1, moo_pDrlgCoord2);
			setup_data(original_pDrlgCoord1, original_pDrlgCoord2);

			// Call both implementations
			sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2, a3, a4);
			original(&original_pDrlgCoord1, &original_pDrlgCoord2, a3, a4);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81950")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81950, dll_base + 0x00041950);

		const auto seed = random_unsigned_integer();
		const auto iteration = static_cast<int32_t>(random_unsigned_integer(1, 14));
		const auto level_link = static_cast<int32_t>(random_unsigned_integer(0, iteration - 1));
		const D2DrlgCoordStrc linked_level_coord = {
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
		};

		// nRand[0]: current direction, nRand[1]: first direction, nRand[2]: current side, nRand[3]: first side
		int32_t rands[4]{};

		SUBCASE("direction not rolled yet")
		{
			rands[0] = -1;
			rands[1] = -1;
			rands[2] = -1;
			rands[3] = -1;
		}

		SUBCASE("try next direction")
		{
			rands[0] = static_cast<int32_t>(random_unsigned_integer(0, 3));
			rands[1] = static_cast<int32_t>(random_unsigned_integer(0, 3));
			rands[2] = static_cast<int32_t>(random_unsigned_integer(0, 1));
			rands[3] = static_cast<int32_t>(random_unsigned_integer(0, 1));
		}

		SUBCASE("all directions tried")
		{
			rands[0] = static_cast<int32_t>(random_unsigned_integer(0, 3));
			rands[2] = static_cast<int32_t>(random_unsigned_integer(0, 1));
			rands[1] = (rands[2] + rands[0]) % 4;
			rands[3] = (rands[2] + 1) % 2;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLinkStrc moo_pLink[15]{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		D2DrlgLinkStrc original_pLink[15]{};

		const auto setup_data = [seed, iteration, level_link, linked_level_coord, &rands](
			D2DrlgLevelLinkDataStrc& pLevelLinkData,
			D2DrlgLinkStrc(&pLink)[15]
		) {
			pLink[iteration].nLevelLink = level_link;

			pLevelLinkData.pSeed.nLowSeed = seed;
			pLevelLinkData.pSeed.nHighSeed = 666;
			pLevelLinkData.pLevelCoord[level_link] = linked_level_coord;
			pLevelLinkData.pLink = pLink;
			for (auto i = 0; i < 4; ++i)
			{
				pLevelLinkData.nRand[i][iteration] = rands[i];
			}
			pLevelLinkData.nIteration = iteration;
		};

		setup_data(moo_pLevelLinkData, moo_pLink);
		setup_data(original_pLevelLinkData, original_pLink);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData);
		const auto original_result = original(&original_pLevelLinkData);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81AD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81AD0, dll_base + 0x00041AD0);
		
		SUBCASE("")
		{
			const auto iteration = static_cast<int32_t>(random_unsigned_integer(1, 14));
			const auto level_link = static_cast<int32_t>(random_unsigned_integer(0, iteration - 1));
			const D2DrlgCoordStrc linked_level_coord = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};
			const auto width = static_cast<int32_t>(random_unsigned_integer(1, 200));
			const auto height = static_cast<int32_t>(random_unsigned_integer(1, 200));

			// Input data
			D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
			D2DrlgLinkStrc moo_pLink[15]{};
			D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
			D2DrlgLinkStrc original_pLink[15]{};

			const auto setup_data = [iteration, level_link, linked_level_coord, width, height](
				D2DrlgLevelLinkDataStrc& pLevelLinkData,
				D2DrlgLinkStrc(&pLink)[15]
			) {
				pLink[iteration].nLevelLink = level_link;

				pLevelLinkData.pLevelCoord[level_link] = linked_level_coord;
				pLevelLinkData.pLevelCoord[iteration].nWidth = width;
				pLevelLinkData.pLevelCoord[iteration].nHeight = height;
				pLevelLinkData.pLink = pLink;
				pLevelLinkData.nRand[0][iteration] = -1;
				pLevelLinkData.nRand[1][iteration] = -1;
				pLevelLinkData.nIteration = iteration;
			};

			setup_data(moo_pLevelLinkData, moo_pLink);
			setup_data(original_pLevelLinkData, original_pLink);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81B30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81B30, dll_base + 0x00041B30);

		const auto seed = random_unsigned_integer();
		const auto iteration = static_cast<int32_t>(random_unsigned_integer(1, 14));
		const auto level_link = static_cast<int32_t>(random_unsigned_integer(0, iteration - 1));
		const D2DrlgCoordStrc linked_level_coord = {
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
		};
		const auto width = static_cast<int32_t>(random_unsigned_integer(1, 200));
		const auto height = static_cast<int32_t>(random_unsigned_integer(1, 200));

		// Only directions 1 and 2 are used
		int32_t current_rand = 0;
		int32_t first_rand = 0;

		SUBCASE("direction not rolled yet")
		{
			current_rand = -1;
			first_rand = -1;
		}

		SUBCASE("try next direction")
		{
			current_rand = static_cast<int32_t>(random_unsigned_integer(1, 2));
			first_rand = current_rand;
		}

		SUBCASE("all directions tried")
		{
			current_rand = static_cast<int32_t>(random_unsigned_integer(1, 2));
			first_rand = 3 - current_rand;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLinkStrc moo_pLink[15]{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		D2DrlgLinkStrc original_pLink[15]{};

		const auto setup_data = [seed, iteration, level_link, linked_level_coord, width, height, current_rand, first_rand](
			D2DrlgLevelLinkDataStrc& pLevelLinkData,
			D2DrlgLinkStrc(&pLink)[15]
		) {
			pLink[iteration].nLevelLink = level_link;

			pLevelLinkData.pSeed.nLowSeed = seed;
			pLevelLinkData.pSeed.nHighSeed = 666;
			pLevelLinkData.pLevelCoord[level_link] = linked_level_coord;
			pLevelLinkData.pLevelCoord[iteration].nWidth = width;
			pLevelLinkData.pLevelCoord[iteration].nHeight = height;
			pLevelLinkData.pLink = pLink;
			pLevelLinkData.nRand[0][iteration] = current_rand;
			pLevelLinkData.nRand[1][iteration] = first_rand;
			pLevelLinkData.nIteration = iteration;
		};

		setup_data(moo_pLevelLinkData, moo_pLink);
		setup_data(original_pLevelLinkData, original_pLink);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData);
		const auto original_result = original(&original_pLevelLinkData);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81BF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81BF0, dll_base + 0x00041BF0);

		const auto seed = random_unsigned_integer();
		const auto iteration = static_cast<int32_t>(random_unsigned_integer(1, 14));
		const auto level_link = static_cast<int32_t>(random_unsigned_integer(0, iteration - 1));
		const D2DrlgCoordStrc linked_level_coord = {
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
			static_cast<int32_t>(random_unsigned_integer(1, 200)),
		};
		const auto width = static_cast<int32_t>(random_unsigned_integer(1, 200));
		const auto height = static_cast<int32_t>(random_unsigned_integer(1, 200));

		int32_t current_rand = 0;
		int32_t first_rand = 0;

		SUBCASE("direction not rolled yet")
		{
			current_rand = -1;
			first_rand = -1;
		}

		SUBCASE("try next direction")
		{
			current_rand = static_cast<int32_t>(random_unsigned_integer(0, 7));
			first_rand = current_rand;
		}

		SUBCASE("all directions tried")
		{
			current_rand = static_cast<int32_t>(random_unsigned_integer(0, 7));
			first_rand = (current_rand + 1) % 8;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLinkStrc moo_pLink[15]{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		D2DrlgLinkStrc original_pLink[15]{};

		const auto setup_data = [seed, iteration, level_link, linked_level_coord, width, height, current_rand, first_rand](
			D2DrlgLevelLinkDataStrc& pLevelLinkData,
			D2DrlgLinkStrc(&pLink)[15]
		) {
			pLink[iteration].nLevelLink = level_link;

			pLevelLinkData.pSeed.nLowSeed = seed;
			pLevelLinkData.pSeed.nHighSeed = 666;
			pLevelLinkData.pLevelCoord[level_link] = linked_level_coord;
			pLevelLinkData.pLevelCoord[iteration].nWidth = width;
			pLevelLinkData.pLevelCoord[iteration].nHeight = height;
			pLevelLinkData.pLink = pLink;
			pLevelLinkData.nRand[0][iteration] = current_rand;
			pLevelLinkData.nRand[1][iteration] = first_rand;
			pLevelLinkData.nIteration = iteration;
		};

		setup_data(moo_pLevelLinkData, moo_pLink);
		setup_data(original_pLevelLinkData, original_pLink);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData);
		const auto original_result = original(&original_pLevelLinkData);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD81CA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD81CA0, dll_base + 0x00041CA0);
		
		SUBCASE("")
		{
			// The seed decides on which side the level is placed, so try a few of them
			REPEAT_10();

			const auto seed = random_unsigned_integer();
			const auto iteration = static_cast<int32_t>(random_unsigned_integer(1, 14));
			const auto level_link = static_cast<int32_t>(random_unsigned_integer(0, iteration - 1));
			const D2DrlgCoordStrc linked_level_coord = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};
			const auto width = static_cast<int32_t>(random_unsigned_integer(1, 200));
			const auto height = static_cast<int32_t>(random_unsigned_integer(1, 200));

			// Input data
			D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
			D2DrlgLinkStrc moo_pLink[15]{};
			D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
			D2DrlgLinkStrc original_pLink[15]{};

			const auto setup_data = [seed, iteration, level_link, linked_level_coord, width, height](
				D2DrlgLevelLinkDataStrc& pLevelLinkData,
				D2DrlgLinkStrc(&pLink)[15]
			) {
				pLink[iteration].nLevelLink = level_link;

				pLevelLinkData.pSeed.nLowSeed = seed;
				pLevelLinkData.pSeed.nHighSeed = 666;
				pLevelLinkData.pLevelCoord[level_link] = linked_level_coord;
				pLevelLinkData.pLevelCoord[iteration].nWidth = width;
				pLevelLinkData.pLevelCoord[iteration].nHeight = height;
				pLevelLinkData.pLink = pLink;
				pLevelLinkData.nRand[0][iteration] = -1;
				pLevelLinkData.nRand[1][iteration] = -1;
				pLevelLinkData.nIteration = iteration;
			};

			setup_data(moo_pLevelLinkData, moo_pLink);
			setup_data(original_pLevelLinkData, original_pLink);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevelLinkData);
			const auto original_result = original(&original_pLevelLinkData);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD81D60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_CreateLevelConnections, dll_base + 0x00041D60);
		
		SUBCASE("Act IV")
		{
			const auto seed = random_unsigned_integer();

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevels[4]{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors[3]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevels[4]{};
			D2DrlgOutdoorInfoStrc original_pOutdoors[3]{};
			uint8_t nActNo = ACT_IV;

			const auto setup_data = [seed](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc(&pLevels)[4],
				D2DrlgOutdoorInfoStrc(&pOutdoors)[3]
			) {
				// The levels of act 4 which are linked by this function, only the town is not an outdoor level
				const int32_t level_ids[] = { LEVEL_THEPANDEMONIUMFORTRESS, LEVEL_OUTERSTEPPES, LEVEL_PLAINSOFDESPAIR, LEVEL_CITYOFTHEDAMNED };
				for (auto i = 0; i < 4; ++i)
				{
					pLevels[i].pDrlg = &pDrlg;
					pLevels[i].nLevelId = level_ids[i];
					if (i == 0)
					{
						pLevels[i].nDrlgType = DRLGTYPE_PRESET;
					}
					else
					{
						pLevels[i].nDrlgType = DRLGTYPE_OUTDOOR;
						pLevels[i].pOutdoors = &pOutdoors[i - 1];
					}
					pLevels[i].pNextLevel = i + 1 < 4 ? &pLevels[i + 1] : nullptr;
				}

				pDrlg.pLevel = &pLevels[0];
				pDrlg.nAct = ACT_IV;
				pDrlg.pSeed.nLowSeed = seed;
				pDrlg.pSeed.nHighSeed = 666;
			};

			setup_data(moo_pDrlg, moo_pLevels, moo_pOutdoors);
			setup_data(original_pDrlg, original_pLevels, original_pOutdoors);

			// Call both implementations
			sut(&moo_pDrlg, nActNo);
			original(&original_pDrlg, nActNo);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}

		SUBCASE("invalid act")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgStrc original_pDrlg{};
			uint8_t nActNo = ACT_V + 1;

			// Call both implementations
			sut(&moo_pDrlg, nActNo);
			original(&original_pDrlg, nActNo);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82050")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD82050, dll_base + 0x00042050);

		// Index into the act 1 wilderness links
		const auto iteration = GENERATE(0, 1, 2, 3, 4);
		auto levels_overlap = 0;

		SUBCASE("levels not overlapping")
		{
			levels_overlap = 0;
		}

		SUBCASE("levels overlapping")
		{
			levels_overlap = 1;
		}

		int32_t directions[15]{};
		int32_t sides[15]{};
		for (auto i = 0; i < 15; ++i)
		{
			directions[i] = static_cast<int32_t>(random_unsigned_integer(0, 3));
			sides[i] = static_cast<int32_t>(random_unsigned_integer(0, 1));
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		int nIteration = iteration;

		const auto setup_data = [levels_overlap, &directions, &sides](
			D2DrlgLevelLinkDataStrc& pLevelLinkData
		) {
			for (auto i = 0; i < 15; ++i)
			{
				pLevelLinkData.pLevelCoord[i].nPosX = levels_overlap ? 0 : 1000 * i;
				pLevelLinkData.pLevelCoord[i].nPosY = 0;
				pLevelLinkData.pLevelCoord[i].nWidth = 100;
				pLevelLinkData.pLevelCoord[i].nHeight = 100;
				pLevelLinkData.nRand[0][i] = directions[i];
				pLevelLinkData.nRand[2][i] = sides[i];
			}
		};

		setup_data(moo_pLevelLinkData);
		setup_data(original_pLevelLinkData);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
		const auto original_result = original(&original_pLevelLinkData, nIteration);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82130")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD82130, dll_base + 0x00042130);

		// Index into the act 1 monastery links
		const auto iteration = GENERATE(0, 1, 2, 3, 4);
		bool levels_overlap = false;

		SUBCASE("levels not overlapping")
		{
			levels_overlap = false;
		}

		SUBCASE("levels overlapping")
		{
			levels_overlap = true;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		int nIteration = iteration;

		const auto setup_data = [levels_overlap](
			D2DrlgLevelLinkDataStrc& pLevelLinkData
		) {
			for (auto i = 0; i < 15; ++i)
			{
				pLevelLinkData.pLevelCoord[i].nPosX = levels_overlap ? 0 : 1000 * i;
				pLevelLinkData.pLevelCoord[i].nPosY = 0;
				pLevelLinkData.pLevelCoord[i].nWidth = 100;
				pLevelLinkData.pLevelCoord[i].nHeight = 100;
			}
		};

		setup_data(moo_pLevelLinkData);
		setup_data(original_pLevelLinkData);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
		const auto original_result = original(&original_pLevelLinkData, nIteration);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD821E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_LinkAct2Outdoors, dll_base + 0x000421E0);

		// Index into the act 2 outdoor links
		const auto iteration = GENERATE(0, 1, 2, 3, 4, 5);
		bool levels_overlap = false;

		SUBCASE("levels not overlapping")
		{
			levels_overlap = false;
		}

		SUBCASE("levels overlapping")
		{
			levels_overlap = true;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		int nIteration = iteration;

		const auto setup_data = [levels_overlap](
			D2DrlgLevelLinkDataStrc& pLevelLinkData
		) {
			for (auto i = 0; i < 15; ++i)
			{
				pLevelLinkData.pLevelCoord[i].nPosX = levels_overlap ? 0 : 1000 * i;
				pLevelLinkData.pLevelCoord[i].nPosY = 0;
				pLevelLinkData.pLevelCoord[i].nWidth = 100;
				pLevelLinkData.pLevelCoord[i].nHeight = 100;
			}
		};

		setup_data(moo_pLevelLinkData);
		setup_data(original_pLevelLinkData);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
		const auto original_result = original(&original_pLevelLinkData, nIteration);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82240")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_LinkAct2Canyon, dll_base + 0x00042240);

		// Index into the act 2 canyon links
		const auto iteration = GENERATE(0, 1);
		bool levels_overlap = false;

		SUBCASE("levels not overlapping")
		{
			levels_overlap = false;
		}

		SUBCASE("levels overlapping")
		{
			levels_overlap = true;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		int nIteration = iteration;

		const auto setup_data = [levels_overlap](
			D2DrlgLevelLinkDataStrc& pLevelLinkData
		) {
			for (auto i = 0; i < 15; ++i)
			{
				pLevelLinkData.pLevelCoord[i].nPosX = levels_overlap ? 0 : 1000 * i;
				pLevelLinkData.pLevelCoord[i].nPosY = 0;
				pLevelLinkData.pLevelCoord[i].nWidth = 100;
				pLevelLinkData.pLevelCoord[i].nHeight = 100;
			}
		};

		setup_data(moo_pLevelLinkData);
		setup_data(original_pLevelLinkData);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
		const auto original_result = original(&original_pLevelLinkData, nIteration);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Comon.0x6FD822A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_LinkAct4Outdoors, dll_base + 0x000422A0);

		// Index into the act 4 outdoor links
		const auto iteration = GENERATE(0, 1, 2, 3);
		bool levels_overlap = false;

		SUBCASE("levels not overlapping")
		{
			levels_overlap = false;
		}

		SUBCASE("levels overlapping")
		{
			levels_overlap = true;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		int nIteration = iteration;

		const auto setup_data = [levels_overlap](
			D2DrlgLevelLinkDataStrc& pLevelLinkData
		) {
			for (auto i = 0; i < 15; ++i)
			{
				pLevelLinkData.pLevelCoord[i].nPosX = levels_overlap ? 0 : 1000 * i;
				pLevelLinkData.pLevelCoord[i].nPosY = 0;
				pLevelLinkData.pLevelCoord[i].nWidth = 100;
				pLevelLinkData.pLevelCoord[i].nHeight = 100;
			}
		};

		setup_data(moo_pLevelLinkData);
		setup_data(original_pLevelLinkData);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
		const auto original_result = original(&original_pLevelLinkData, nIteration);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82300")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_LinkAct4ChaosSanctum, dll_base + 0x00042300);

		// Index into the act 4 chaos sanctum links
		const auto iteration = GENERATE(0, 1);
		bool levels_overlap = false;

		SUBCASE("levels not overlapping")
		{
			levels_overlap = false;
		}

		SUBCASE("levels overlapping")
		{
			levels_overlap = true;
		}

		// Input data
		D2DrlgLevelLinkDataStrc moo_pLevelLinkData{};
		D2DrlgLevelLinkDataStrc original_pLevelLinkData{};
		int nIteration = iteration;

		const auto setup_data = [levels_overlap](
			D2DrlgLevelLinkDataStrc& pLevelLinkData
		) {
			for (auto i = 0; i < 15; ++i)
			{
				pLevelLinkData.pLevelCoord[i].nPosX = levels_overlap ? 0 : 1000 * i;
				pLevelLinkData.pLevelCoord[i].nPosY = 0;
				pLevelLinkData.pLevelCoord[i].nWidth = 100;
				pLevelLinkData.pLevelCoord[i].nHeight = 100;
			}
		};

		setup_data(moo_pLevelLinkData);
		setup_data(original_pLevelLinkData);

		// Call both implementations
		const auto moo_result = sut(&moo_pLevelLinkData, nIteration);
		const auto original_result = original(&original_pLevelLinkData, nIteration);
		
		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pLevelLinkData, original_pLevelLinkData, "Comparing pLevelLinkData");
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82360")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD82360, dll_base + 0x00042360);
		
		SUBCASE("outdoor level")
		{
			const int32_t level_id = GENERATE(LEVEL_BLOODMOOR, LEVEL_COLDPLAINS, LEVEL_STONYFIELD, LEVEL_BURIALGROUNDS);
			const auto iteration = static_cast<int32_t>(random_unsigned_integer(0, 13));

			// Try all combinations of the directions picked for this and the next level
			for (auto current_direction = 0; current_direction < 4; ++current_direction)
			{
				for (auto next_direction = 0; next_direction < 4; ++next_direction)
				{
					// Input data
					D2DrlgLevelStrc moo_pLevel{};
					D2DrlgOutdoorInfoStrc moo_pOutdoors{};
					int moo_pRand[60]{};
					D2DrlgLevelStrc original_pLevel{};
					D2DrlgOutdoorInfoStrc original_pOutdoors{};
					int original_pRand[60]{};
					int nIteration = iteration;

					const auto setup_data = [level_id, iteration, current_direction, next_direction](
						D2DrlgLevelStrc& pLevel,
						D2DrlgOutdoorInfoStrc& pOutdoors,
						int(&pRand)[60]
					) {
						pRand[iteration] = current_direction;
						pRand[iteration + 1] = next_direction;

						pLevel.nLevelId = level_id;
						pLevel.nDrlgType = DRLGTYPE_OUTDOOR;
						pLevel.pOutdoors = &pOutdoors;
					};

					setup_data(moo_pLevel, moo_pOutdoors, moo_pRand);
					setup_data(original_pLevel, original_pOutdoors, original_pRand);

					// Call both implementations
					sut(&moo_pLevel, nIteration, moo_pRand);
					original(&original_pLevel, nIteration, original_pRand);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
					for (auto i = 0; i < 60; ++i)
					{
						MOO_CHECK_EQ(moo_pRand[i], original_pRand[i], "Comparing pRand");
					}
				}
			}
		}

		SUBCASE("not an outdoor level")
		{
			const auto iteration = static_cast<int32_t>(random_unsigned_integer(0, 13));
			const auto current_direction = static_cast<int32_t>(random_unsigned_integer(0, 3));
			const auto next_direction = static_cast<int32_t>(random_unsigned_integer(0, 3));

			// Input data
			D2DrlgLevelStrc moo_pLevel{};
			int moo_pRand[60]{};
			D2DrlgLevelStrc original_pLevel{};
			int original_pRand[60]{};
			int nIteration = iteration;

			const auto setup_data = [iteration, current_direction, next_direction](
				D2DrlgLevelStrc& pLevel,
				int(&pRand)[60]
			) {
				pRand[iteration] = current_direction;
				pRand[iteration + 1] = next_direction;

				pLevel.nLevelId = LEVEL_ROGUEENCAMPMENT;
				pLevel.nDrlgType = DRLGTYPE_PRESET;
			};

			setup_data(moo_pLevel, moo_pRand);
			setup_data(original_pLevel, original_pRand);

			// Call both implementations
			sut(&moo_pLevel, nIteration, moo_pRand);
			original(&original_pLevel, nIteration, original_pRand);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			for (auto i = 0; i < 60; ++i)
			{
				MOO_CHECK_EQ(moo_pRand[i], original_pRand[i], "Comparing pRand");
			}
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD823C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD823C0, dll_base + 0x000423C0);
		
		SUBCASE("")
		{
			const auto seed = random_unsigned_integer();

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLinkStrc moo_pDrlgLink[15]{};
			D2DrlgLevelStrc moo_pLevels[4]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLinkStrc original_pDrlgLink[15]{};
			D2DrlgLevelStrc original_pLevels[4]{};

			const auto setup_data = [seed](
				D2DrlgStrc& pDrlg,
				D2DrlgLinkStrc(&pDrlgLink)[15],
				D2DrlgLevelStrc(&pLevels)[4]
			) {
				// Act 4 like chain of levels, each one linked to the previous one.
				// NOTE: Both implementations get the same (MOO) linker functions, so only the function under test differs.
				const int32_t level_ids[] = { LEVEL_THEPANDEMONIUMFORTRESS, LEVEL_OUTERSTEPPES, LEVEL_PLAINSOFDESPAIR, LEVEL_CITYOFTHEDAMNED };
				for (auto i = 0; i < 4; ++i)
				{
					pDrlgLink[i].pfLinker = i == 0 ? reinterpret_cast<void*>(&sub_6FD81330) : reinterpret_cast<void*>(&sub_6FD81380);
					pDrlgLink[i].nLevel = level_ids[i];
					pDrlgLink[i].nLevelLink = i - 1;
					pDrlgLink[i].nLevelLinkEx = -1;

					pLevels[i].nLevelId = level_ids[i];
					pLevels[i].pNextLevel = i + 1 < 4 ? &pLevels[i + 1] : nullptr;
				}
				pDrlgLink[4].nLevelLink = -1;
				pDrlgLink[4].nLevelLinkEx = -1;

				pDrlg.pLevel = &pLevels[0];
				pDrlg.nAct = ACT_IV;
				pDrlg.pSeed.nLowSeed = seed;
				pDrlg.pSeed.nHighSeed = 666;
			};

			setup_data(moo_pDrlg, moo_pDrlgLink, moo_pLevels);
			setup_data(original_pDrlg, original_pDrlgLink, original_pLevels);

			// Call both implementations
			sut(&moo_pDrlg, moo_pDrlgLink, nullptr, nullptr);
			original(&original_pDrlg, original_pDrlgLink, nullptr, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			for (auto i = 0; i < 15; ++i)
			{
				MOO_CHECK_EQ(moo_pDrlgLink[i], original_pDrlgLink[i], "Comparing pDrlgLink");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD826D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD826D0, dll_base + 0x000426D0);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevels[3]{};
			D2DrlgWarpStrc moo_pDrlgWarps[3]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevels[3]{};
			D2DrlgWarpStrc original_pDrlgWarps[3]{};
			int nStartId = LEVEL_HARROGATH;
			int nEndId = LEVEL_ID_ACT5_BARRICADE_1;

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc(&pLevels)[3],
				D2DrlgWarpStrc(&pDrlgWarps)[3]
			) {
				// Three levels stacked on top of each other, only consecutive ones are adjacent
				const int32_t level_ids[] = { LEVEL_HARROGATH, LEVEL_BLOODYFOOTHILLS, LEVEL_ID_ACT5_BARRICADE_1 };
				for (auto i = 0; i < 3; ++i)
				{
					pLevels[i].nLevelId = level_ids[i];
					pLevels[i].nPosX = 0;
					pLevels[i].nPosY = 80 * i;
					pLevels[i].nWidth = 80;
					pLevels[i].nHeight = 80;
					pLevels[i].pNextLevel = i + 1 < 3 ? &pLevels[i + 1] : nullptr;

					pDrlgWarps[i].nLevel = level_ids[i];
					for (auto j = 0; j < 8; ++j)
					{
						pDrlgWarps[i].nWarp[j] = -1;
					}
					pDrlgWarps[i].pNext = i + 1 < 3 ? &pDrlgWarps[i + 1] : nullptr;
				}

				// The first level already knows its neighbour (with a warp to it), the second one has to add its neighbours
				pDrlgWarps[0].nVis[0] = LEVEL_BLOODYFOOTHILLS;
				pDrlgWarps[0].nWarp[0] = 5;
				pDrlgWarps[2].nVis[0] = LEVEL_BLOODYFOOTHILLS;

				pDrlg.pLevel = &pLevels[0];
				pDrlg.pWarp = &pDrlgWarps[0];
			};

			setup_data(moo_pDrlg, moo_pLevels, moo_pDrlgWarps);
			setup_data(original_pDrlg, original_pLevels, original_pDrlgWarps);

			// Call both implementations
			sut(&moo_pDrlg, nStartId, nEndId);
			original(&original_pDrlg, nStartId, nEndId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD82750")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD82750, dll_base + 0x00042750);
		
		SUBCASE("")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevels[3]{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors[2]{};
			D2DrlgWarpStrc moo_pDrlgWarps[3]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevels[3]{};
			D2DrlgOutdoorInfoStrc original_pOutdoors[2]{};
			D2DrlgWarpStrc original_pDrlgWarps[3]{};
			int nStartId = LEVEL_HARROGATH;
			int nEndId = LEVEL_ID_ACT5_BARRICADE_1;

			const auto setup_data = [](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc(&pLevels)[3],
				D2DrlgOutdoorInfoStrc(&pOutdoors)[2],
				D2DrlgWarpStrc(&pDrlgWarps)[3]
			) {
				// Town followed by two outdoor levels, stacked on top of each other
				const int32_t level_ids[] = { LEVEL_HARROGATH, LEVEL_BLOODYFOOTHILLS, LEVEL_ID_ACT5_BARRICADE_1 };
				for (auto i = 0; i < 3; ++i)
				{
					pLevels[i].pDrlg = &pDrlg;
					pLevels[i].nLevelId = level_ids[i];
					if (i == 0)
					{
						pLevels[i].nDrlgType = DRLGTYPE_PRESET;
					}
					else
					{
						pLevels[i].nDrlgType = DRLGTYPE_OUTDOOR;
						pLevels[i].pOutdoors = &pOutdoors[i - 1];
					}
					pLevels[i].nPosX = 0;
					pLevels[i].nPosY = 80 * i;
					pLevels[i].nWidth = 80;
					pLevels[i].nHeight = 80;
					pLevels[i].pNextLevel = i + 1 < 3 ? &pLevels[i + 1] : nullptr;

					pDrlgWarps[i].nLevel = level_ids[i];
					pDrlgWarps[i].pNext = i + 1 < 3 ? &pDrlgWarps[i + 1] : nullptr;
				}

				// Adjacent levels are visible without a warp (-1)
				pDrlgWarps[0].nVis[0] = LEVEL_BLOODYFOOTHILLS;
				pDrlgWarps[0].nWarp[0] = -1;
				pDrlgWarps[1].nVis[0] = LEVEL_HARROGATH;
				pDrlgWarps[1].nWarp[0] = -1;
				pDrlgWarps[1].nVis[1] = LEVEL_ID_ACT5_BARRICADE_1;
				pDrlgWarps[1].nWarp[1] = -1;
				pDrlgWarps[2].nVis[0] = LEVEL_BLOODYFOOTHILLS;
				pDrlgWarps[2].nWarp[0] = -1;
				// Level reached through a warp, which does not get linked
				pDrlgWarps[2].nVis[1] = LEVEL_ARREATPLATEAU;
				pDrlgWarps[2].nWarp[1] = 2;

				pDrlg.pLevel = &pLevels[0];
				pDrlg.pWarp = &pDrlgWarps[0];
			};

			setup_data(moo_pDrlg, moo_pLevels, moo_pOutdoors, moo_pDrlgWarps);
			setup_data(original_pDrlg, original_pLevels, original_pOutdoors, original_pDrlgWarps);

			// Call both implementations
			sut(&moo_pDrlg, nStartId, nEndId);
			original(&original_pDrlg, nStartId, nEndId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD82820")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GenerateJungles, dll_base + 0x00042820);
		
		SUBCASE("")
		{
			const auto difficulty = GENERATE(0, 1, 2);
			const auto seed = random_unsigned_integer();

			// The jungles are placed relative to Kurast Docks, which uses its level def values
			const auto& docks_level_def = leveldefs_txt[LEVEL_KURASTDOCKTOWN];
			const auto docks_x = static_cast<int32_t>(docks_level_def.dwOffsetX);
			const auto docks_y = static_cast<int32_t>(docks_level_def.dwOffsetY);
			const auto docks_width = static_cast<int32_t>(docks_level_def.dwSizeX[difficulty]);
			const auto docks_height = static_cast<int32_t>(docks_level_def.dwSizeY[difficulty]);

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgLevelStrc moo_pJungleLevels[3]{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgLevelStrc original_pJungleLevels[3]{};

			const auto setup_data = [difficulty, seed, docks_x, docks_y, docks_width, docks_height](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgLevelStrc(&pJungleLevels)[3]
			) {
				// Spider Forest, Great Marsh and Flayer Jungle
				for (auto i = 0; i < 3; ++i)
				{
					pJungleLevels[i].pDrlg = &pDrlg;
					pJungleLevels[i].nLevelId = LEVEL_SPIDERFOREST + i;
					pJungleLevels[i].pNextLevel = i + 1 < 3 ? &pJungleLevels[i + 1] : nullptr;
				}

				pDrlg.pLevel = &pJungleLevels[0];
				pDrlg.pSeed.nLowSeed = seed;
				pDrlg.pSeed.nHighSeed = 666;
				pDrlg.nDifficulty = difficulty;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_KURASTDOCKTOWN;
				pLevel.nPosX = docks_x;
				pLevel.nPosY = docks_y;
				pLevel.nWidth = docks_width;
				pLevel.nHeight = docks_height;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pJungleLevels);
			setup_data(original_pDrlg, original_pLevel, original_pJungleLevels);

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel);
			const auto original_result = original(&original_pLevel);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD83970")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD83970, dll_base + 0x00043970);
		
		SUBCASE("")
		{
			// 0: north, 1-4: west/east of the base jungle, other values do not move the jungle
			const auto placement = GENERATE(0, 1, 2, 3, 4, 5);

			const D2DrlgCoordStrc coord = {
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(0, 1000)) - 500,
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
				static_cast<int32_t>(random_unsigned_integer(1, 200)),
			};

			// Input data
			D2DrlgCoordStrc moo_pDrlgCoord{};
			D2JungleStrc moo_pJungle{};
			D2DrlgCoordStrc original_pDrlgCoord{};
			D2JungleStrc original_pJungle{};
			int nRand = placement;
			int nSizeX = 32 * static_cast<int32_t>(random_unsigned_integer(1, 8));
			int nSizeY = 32 * static_cast<int32_t>(random_unsigned_integer(1, 8));

			const auto setup_data = [coord](
				D2DrlgCoordStrc& pDrlgCoord,
				D2JungleStrc& pJungle
			) {
				pDrlgCoord = coord;
			};

			setup_data(moo_pDrlgCoord, moo_pJungle);
			setup_data(original_pDrlgCoord, original_pJungle);

			// Call both implementations
			sut(&moo_pDrlgCoord, &moo_pJungle, nRand, nSizeX, nSizeY);
			original(&original_pDrlgCoord, &original_pJungle, nRand, nSizeX, nSizeY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
			MOO_CHECK_EQ(moo_pJungle, original_pJungle, "Comparing pJungle");
		}
	}
	
	TEST_CASE_FIXTURE(LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>, "D2Common.0x6FD83A20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_InitOutdoorRoomGrids, dll_base + 0x00043A20);

		const auto room_x = static_cast<int32_t>(random_unsigned_integer(0, 1000));
		const auto room_y = static_cast<int32_t>(random_unsigned_integer(0, 1000));
		
		SUBCASE("Act I level")
		{
			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorInfoStrc moo_pOutdoors{};
			D2DrlgOutdoorRoomStrc moo_pOutdoor{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorInfoStrc original_pOutdoors{};
			D2DrlgOutdoorRoomStrc original_pOutdoor{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [room_x, room_y](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorInfoStrc& pOutdoors,
				D2DrlgOutdoorRoomStrc& pOutdoor,
				D2DrlgRoomStrc& pDrlgRoom
			) {
				// Act 1 levels generate dirt paths, the level has no paths though
				pOutdoors.nVertices = 0;

				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = LEVEL_BLOODMOOR;
				pLevel.nLevelType = LVLTYPE_ACT1_WILDERNESS;
				pLevel.pOutdoors = &pOutdoors;

				// No tile substitutions
				pOutdoor.nSubType = -1;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pOutdoor = &pOutdoor;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pOutdoors, moo_pOutdoor, moo_pDrlgRoom);
			setup_data(original_pDrlg, original_pLevel, original_pOutdoors, original_pOutdoor, original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}

		SUBCASE("Act II - V level")
		{
			const int32_t level_ids[] = { LEVEL_ROCKYWASTE, LEVEL_SPIDERFOREST, LEVEL_LOWERKURAST, LEVEL_OUTERSTEPPES, LEVEL_RIVEROFFLAME, LEVEL_BLOODYFOOTHILLS, LEVEL_TUNDRAWASTELANDS };
			const int32_t level_types[] = { LVLTYPE_ACT2_DESERT, LVLTYPE_ACT3_JUNGLE, LVLTYPE_ACT3_KURAST, LVLTYPE_ACT4_MESA, LVLTYPE_ACT4_LAVA, LVLTYPE_ACT5_BARRICADE, LVLTYPE_ACT5_BARRICADE };
			const auto level_index = GENERATE(0, 1, 2, 3, 4, 5, 6);
			const auto level_id = level_ids[level_index];
			const auto level_type = level_types[level_index];

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgOutdoorRoomStrc moo_pOutdoor{};
			D2DrlgRoomStrc moo_pDrlgRoom{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			D2DrlgOutdoorRoomStrc original_pOutdoor{};
			D2DrlgRoomStrc original_pDrlgRoom{};

			const auto setup_data = [room_x, room_y, level_id, level_type](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel,
				D2DrlgOutdoorRoomStrc& pOutdoor,
				D2DrlgRoomStrc& pDrlgRoom
			) {
				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.nLevelType = level_type;

				// No tile substitutions
				pOutdoor.nSubType = -1;

				pDrlgRoom.pLevel = &pLevel;
				pDrlgRoom.nTileXPos = room_x;
				pDrlgRoom.nTileYPos = room_y;
				pDrlgRoom.nTileWidth = 8;
				pDrlgRoom.nTileHeight = 8;
				pDrlgRoom.pOutdoor = &pOutdoor;
			};

			setup_data(moo_pDrlg, moo_pLevel, moo_pOutdoor, moo_pDrlgRoom);
			setup_data(original_pDrlg, original_pLevel, original_pOutdoor, original_pDrlgRoom);

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(LvlSubTxtFixture<LevelDefsTxtFixture<LevelsTxtFixture<NoopFixture>>>, "D2Common.0x6FD83C90")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGOUTPLACE_CreateOutdoorRoomEx, dll_base + 0x00043C90);
		
		SUBCASE("")
		{
			const int32_t level_id = GENERATE(LEVEL_BLOODMOOR, LEVEL_ROCKYWASTE, LEVEL_SPIDERFOREST, LEVEL_OUTERSTEPPES, LEVEL_BLOODYFOOTHILLS);
			const auto seed = random_unsigned_integer();

			// Input data
			D2DrlgStrc moo_pDrlg{};
			D2DrlgLevelStrc moo_pLevel{};
			D2DrlgStrc original_pDrlg{};
			D2DrlgLevelStrc original_pLevel{};
			int nX = static_cast<int>(random_unsigned_integer(0, 1000));
			int nY = static_cast<int>(random_unsigned_integer(0, 1000));
			int nWidth = 8;
			int nHeight = 8;
			int dwRoomFlags = static_cast<int>(random_unsigned_integer());
			int dwOutdoorFlags = static_cast<int>(random_unsigned_integer());
			int dwOutdoorFlagsEx = static_cast<int>(random_unsigned_integer());
			int dwDT1Mask = static_cast<int>(random_unsigned_integer());

			const auto setup_data = [level_id, seed](
				D2DrlgStrc& pDrlg,
				D2DrlgLevelStrc& pLevel
			) {
				pLevel.pDrlg = &pDrlg;
				pLevel.nLevelId = level_id;
				pLevel.pSeed.nLowSeed = seed;
				pLevel.pSeed.nHighSeed = 666;
			};

			setup_data(moo_pDrlg, moo_pLevel);
			setup_data(original_pDrlg, original_pLevel);

			// Call both implementations
			sut(&moo_pLevel, nX, nY, nWidth, nHeight, dwRoomFlags, dwOutdoorFlags, dwOutdoorFlagsEx, dwDT1Mask);
			original(&original_pLevel, nX, nY, nWidth, nHeight, dwRoomFlags, dwOutdoorFlags, dwOutdoorFlagsEx, dwDT1Mask);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
}

#endif
