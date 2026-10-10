#include <D2CommonTestDefines.h>

#ifdef DRLG_GRID_TESTS

#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlgGrid.h>
#include <Fog.h>


DYNAMIC_ARRAY_TYPE(int)


TEST_SUITE("D2DrlgDrlgGridTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_OverwriteFlag, dll_base + 0x00035BA0);
		
		SUBCASE("")
		{
			// Input data
			const auto flag = random_unsigned_integer();

			int moo_pFlag{};
			int original_pFlag{};
			int nFlag = random_unsigned_integer();

			const auto setup_data = [flag](
				int& pFlag
			) {
				pFlag = flag;
			};

			setup_data(moo_pFlag);
			setup_data(original_pFlag);

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_OrFlag, dll_base + 0x00035BB0);
		
		SUBCASE("")
		{
			// Input data
			const auto flag = random_unsigned_integer();

			int moo_pFlag{};
			int original_pFlag{};
			int nFlag = random_unsigned_integer();

			const auto setup_data = [flag](
				int& pFlag
			) {
				pFlag = flag;
			};

			setup_data(moo_pFlag);
			setup_data(original_pFlag);

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_AndFlag, dll_base + 0x00035BC0);
		
		SUBCASE("")
		{
			// Input data
			const auto flag = random_unsigned_integer();

			int moo_pFlag{};
			int original_pFlag{};
			int nFlag = random_unsigned_integer();

			const auto setup_data = [flag](
				int& pFlag
			) {
				pFlag = flag;
			};

			setup_data(moo_pFlag);
			setup_data(original_pFlag);

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_XorFlag, dll_base + 0x00035BD0);
		
		SUBCASE("")
		{
			// Input data
			const auto flag = random_unsigned_integer();

			int moo_pFlag{};
			int original_pFlag{};
			int nFlag = random_unsigned_integer();

			const auto setup_data = [flag](
				int& pFlag
			) {
				pFlag = flag;
			};

			setup_data(moo_pFlag);
			setup_data(original_pFlag);

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_OverwriteFlagIfZero, dll_base + 0x00035BE0);

		SUBCASE("is zero")
		{
			// Input data
			const auto flag = 0;

			int moo_pFlag{};
			int original_pFlag{};
			int nFlag = random_unsigned_integer();

			const auto setup_data = [flag](
				int& pFlag
			) {
				pFlag = flag;
			};

			setup_data(moo_pFlag);
			setup_data(original_pFlag);

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}

		SUBCASE("is not zero")
		{
			// Input data
			const auto flag = random_unsigned_integer();

			int moo_pFlag{};
			int original_pFlag{};
			int nFlag = random_unsigned_integer();

			const auto setup_data = [flag](
				int& pFlag
			) {
				pFlag = flag;
			};

			setup_data(moo_pFlag);
			setup_data(original_pFlag);

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_AndNegatedFlag, dll_base + 0x00035BF0);

		SUBCASE("")
		{
			// Input data
			const auto flag = random_unsigned_integer();

			int moo_pFlag{};
			int original_pFlag{};
			int nFlag = random_unsigned_integer();

			const auto setup_data = [flag](
				int& pFlag
			) {
				pFlag = flag;
			};

			setup_data(moo_pFlag);
			setup_data(original_pFlag);

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75C00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_IsGridValid, dll_base + 0x00035C00);
		
		SUBCASE("valid")
		{
			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			D2DrlgGridStrc original_pDrlgGrid{};

			const auto setup_data = [](
				D2DrlgGridStrc& pDrlgGrid
			) {
				pDrlgGrid.pCellsFlags = (int32_t*)1;
			};

			setup_data(moo_pDrlgGrid);
			setup_data(original_pDrlgGrid);

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgGrid);
			const auto original_result = original(&original_pDrlgGrid);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}

		SUBCASE("invalid")
		{
			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			D2DrlgGridStrc original_pDrlgGrid{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgGrid);
			const auto original_result = original(&original_pDrlgGrid);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75C20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_IsPointInsideGridArea, dll_base + 0x00035C20);
		
		SUBCASE("")
		{
			// Input data
			const auto width = 5;
			const auto height = 5;

			for (auto j = -1; j < height + 1; ++j)
			{
				for (auto i = -1; i < width + 1; ++i)
				{
					D2DrlgGridStrc moo_pDrlgGrid{};
					D2DrlgGridStrc original_pDrlgGrid{};
					int nX = i;
					int nY = j;

					const auto setup_data = [width, height](
						D2DrlgGridStrc& pDrlgGrid
					) {
						pDrlgGrid.nWidth = width;
						pDrlgGrid.nHeight = height;
					};

					setup_data(moo_pDrlgGrid);
					setup_data(original_pDrlgGrid);

					// Call both implementations
					const auto moo_result = sut(&moo_pDrlgGrid, nX, nY);
					const auto original_result = original(&original_pDrlgGrid, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75C50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_AlterGridFlag, dll_base + 0x00035C50);

		SUBCASE("")
		{
			constexpr auto width = 4;
			constexpr auto height = 3;

			for (auto operation = static_cast<int>(FLAG_OPERATION_OR); operation <= FLAG_OPERATION_AND_NEGATED; ++operation)
			{
				int cell_values[width * height];
				for (auto& cell_value : cell_values)
				{
					cell_value = random_unsigned_integer(0, 3);
				}

				// Input data
				D2DrlgGridStrc moo_pDrlgGrid{};
				int moo_pCellsFlags[width * height]{};
				int moo_pCellsRowOffsets[height]{};
				D2DrlgGridStrc original_pDrlgGrid{};
				int original_pCellsFlags[width * height]{};
				int original_pCellsRowOffsets[height]{};
				int nX = random_unsigned_integer(0, width - 1);
				int nY = random_unsigned_integer(0, height - 1);
				int nFlag = random_unsigned_integer();
				FlagOperation eOperation = static_cast<FlagOperation>(operation);

				const auto setup_data = [width, height, &cell_values](
					D2DrlgGridStrc& pDrlgGrid,
					int (&pCellsFlags)[width * height],
					int (&pCellsRowOffsets)[height]
				) {
					std::copy(std::begin(cell_values), std::end(cell_values), std::begin(pCellsFlags));
					for (auto row = 0; row < height; ++row)
					{
						pCellsRowOffsets[row] = row * width;
					}

					pDrlgGrid.pCellsFlags = pCellsFlags;
					pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
					pDrlgGrid.nWidth = width;
					pDrlgGrid.nHeight = height;
				};

				setup_data(moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets);
				setup_data(original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets);

				// Call both implementations
				sut(&moo_pDrlgGrid, nX, nY, nFlag, eOperation);
				original(&original_pDrlgGrid, nX, nY, nFlag, eOperation);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellsFlags, width * height }), (DynamicArray<int>{ original_pCellsFlags, width * height }), "Comparing pCellsFlags");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellsRowOffsets, height }), (DynamicArray<int>{ original_pCellsRowOffsets, height }), "Comparing pCellsRowOffsets");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75C80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_GetGridFlagsPointer, dll_base + 0x00035C80);

		SUBCASE("")
		{
			constexpr auto width = 4;
			constexpr auto height = 3;

			int cell_values[width * height];
			for (auto& cell_value : cell_values)
			{
				cell_value = random_unsigned_integer();
			}

			for (auto j = 0; j < height; ++j)
			{
				for (auto i = 0; i < width; ++i)
				{
					// Input data
					D2DrlgGridStrc moo_pDrlgGrid{};
					int moo_pCellsFlags[width * height]{};
					int moo_pCellsRowOffsets[height]{};
					D2DrlgGridStrc original_pDrlgGrid{};
					int original_pCellsFlags[width * height]{};
					int original_pCellsRowOffsets[height]{};
					int nX = i;
					int nY = j;

					const auto setup_data = [width, height, &cell_values](
						D2DrlgGridStrc& pDrlgGrid,
						int (&pCellsFlags)[width * height],
						int (&pCellsRowOffsets)[height]
					) {
						std::copy(std::begin(cell_values), std::end(cell_values), std::begin(pCellsFlags));
						for (auto row = 0; row < height; ++row)
						{
							pCellsRowOffsets[row] = row * width;
						}

						pDrlgGrid.pCellsFlags = pCellsFlags;
						pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
						pDrlgGrid.nWidth = width;
						pDrlgGrid.nHeight = height;
					};

					setup_data(moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets);
					setup_data(original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets);

					// Call both implementations
					const auto moo_result = sut(&moo_pDrlgGrid, nX, nY);
					const auto original_result = original(&original_pDrlgGrid, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					auto moo_result_index = static_cast<int>(moo_result - moo_pCellsFlags);
					auto original_result_index = static_cast<int>(original_result - original_pCellsFlags);
					MOO_CHECK_EQ(moo_result_index, original_result_index, "Comparing result indices");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75CA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_GetGridEntry, dll_base + 0x00035CA0);

		SUBCASE("")
		{
			constexpr auto width = 4;
			constexpr auto height = 3;

			int cell_values[width * height];
			for (auto& cell_value : cell_values)
			{
				cell_value = random_unsigned_integer();
			}

			for (auto j = 0; j < height; ++j)
			{
				for (auto i = 0; i < width; ++i)
				{
					// Input data
					D2DrlgGridStrc moo_pDrlgGrid{};
					int moo_pCellsFlags[width * height]{};
					int moo_pCellsRowOffsets[height]{};
					D2DrlgGridStrc original_pDrlgGrid{};
					int original_pCellsFlags[width * height]{};
					int original_pCellsRowOffsets[height]{};
					int nX = i;
					int nY = j;

					const auto setup_data = [width, height, &cell_values](
						D2DrlgGridStrc& pDrlgGrid,
						int (&pCellsFlags)[width * height],
						int (&pCellsRowOffsets)[height]
					) {
						std::copy(std::begin(cell_values), std::end(cell_values), std::begin(pCellsFlags));
						for (auto row = 0; row < height; ++row)
						{
							pCellsRowOffsets[row] = row * width;
						}

						pDrlgGrid.pCellsFlags = pCellsFlags;
						pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
						pDrlgGrid.nWidth = width;
						pDrlgGrid.nHeight = height;
					};

					setup_data(moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets);
					setup_data(original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets);

					// Call both implementations
					const auto moo_result = sut(&moo_pDrlgGrid, nX, nY);
					const auto original_result = original(&original_pDrlgGrid, nX, nY);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75CC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_AlterAllGridFlags, dll_base + 0x00035CC0);

		SUBCASE("")
		{
			constexpr auto width = 4;
			constexpr auto height = 3;

			for (auto operation = static_cast<int>(FLAG_OPERATION_OR); operation <= FLAG_OPERATION_AND_NEGATED; ++operation)
			{
				int cell_values[width * height];
				for (auto& cell_value : cell_values)
				{
					cell_value = random_unsigned_integer(0, 3);
				}

				// Input data
				D2DrlgGridStrc moo_pDrlgGrid{};
				int moo_pCellsFlags[width * height]{};
				int moo_pCellsRowOffsets[height]{};
				D2DrlgGridStrc original_pDrlgGrid{};
				int original_pCellsFlags[width * height]{};
				int original_pCellsRowOffsets[height]{};
				int nFlag = random_unsigned_integer();
				FlagOperation eOperation = static_cast<FlagOperation>(operation);

				const auto setup_data = [width, height, &cell_values](
					D2DrlgGridStrc& pDrlgGrid,
					int (&pCellsFlags)[width * height],
					int (&pCellsRowOffsets)[height]
				) {
					std::copy(std::begin(cell_values), std::end(cell_values), std::begin(pCellsFlags));
					for (auto row = 0; row < height; ++row)
					{
						pCellsRowOffsets[row] = row * width;
					}

					pDrlgGrid.pCellsFlags = pCellsFlags;
					pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
					pDrlgGrid.nWidth = width;
					pDrlgGrid.nHeight = height;
				};

				setup_data(moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets);
				setup_data(original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets);

				// Call both implementations
				sut(&moo_pDrlgGrid, nFlag, eOperation);
				original(&original_pDrlgGrid, nFlag, eOperation);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellsFlags, width * height }), (DynamicArray<int>{ original_pCellsFlags, width * height }), "Comparing pCellsFlags");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellsRowOffsets, height }), (DynamicArray<int>{ original_pCellsRowOffsets, height }), "Comparing pCellsRowOffsets");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75D20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_AlterEdgeGridFlags, dll_base + 0x00035D20);

		SUBCASE("")
		{
			constexpr auto width = 5;
			constexpr auto height = 4;

			for (auto operation = static_cast<int>(FLAG_OPERATION_OR); operation <= FLAG_OPERATION_AND_NEGATED; ++operation)
			{
				int cell_values[width * height];
				for (auto& cell_value : cell_values)
				{
					cell_value = random_unsigned_integer(0, 3);
				}

				// Input data
				D2DrlgGridStrc moo_pDrlgGrid{};
				int moo_pCellsFlags[width * height]{};
				int moo_pCellsRowOffsets[height]{};
				D2DrlgGridStrc original_pDrlgGrid{};
				int original_pCellsFlags[width * height]{};
				int original_pCellsRowOffsets[height]{};
				int nFlag = random_unsigned_integer();
				FlagOperation eOperation = static_cast<FlagOperation>(operation);

				const auto setup_data = [width, height, &cell_values](
					D2DrlgGridStrc& pDrlgGrid,
					int (&pCellsFlags)[width * height],
					int (&pCellsRowOffsets)[height]
				) {
					std::copy(std::begin(cell_values), std::end(cell_values), std::begin(pCellsFlags));
					for (auto row = 0; row < height; ++row)
					{
						pCellsRowOffsets[row] = row * width;
					}

					pDrlgGrid.pCellsFlags = pCellsFlags;
					pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
					pDrlgGrid.nWidth = width;
					pDrlgGrid.nHeight = height;
				};

				setup_data(moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets);
				setup_data(original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets);

				// Call both implementations
				sut(&moo_pDrlgGrid, nFlag, eOperation);
				original(&original_pDrlgGrid, nFlag, eOperation);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellsFlags, width * height }), (DynamicArray<int>{ original_pCellsFlags, width * height }), "Comparing pCellsFlags");
				MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellsRowOffsets, height }), (DynamicArray<int>{ original_pCellsRowOffsets, height }), "Comparing pCellsRowOffsets");
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75F10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_SetVertexGridFlags, dll_base + 0x00035F10);

		SUBCASE("")
		{
			constexpr auto width = 5;
			constexpr auto height = 5;
			constexpr auto next_vertex_count = 5;

			// Vertex positions, some of them are outside of the grid
			const int vertex_positions[next_vertex_count + 1][2] = {
				{ 0, 0 },
				{ 4, 2 },
				{ -1, 3 },
				{ 2, 5 },
				{ 5, 1 },
				{ 2, 4 },
			};

			int cell_values[width * height];
			for (auto& cell_value : cell_values)
			{
				cell_value = random_unsigned_integer();
			}

			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			int moo_pCellsFlags[width * height]{};
			int moo_pCellsRowOffsets[height]{};
			D2DrlgVertexStrc moo_pDrlgVertex{};
			D2DrlgVertexStrc moo_pNextVertices[next_vertex_count]{};
			D2DrlgGridStrc original_pDrlgGrid{};
			int original_pCellsFlags[width * height]{};
			int original_pCellsRowOffsets[height]{};
			D2DrlgVertexStrc original_pDrlgVertex{};
			D2DrlgVertexStrc original_pNextVertices[next_vertex_count]{};
			int nFlag = random_unsigned_integer();

			const auto setup_data = [width, height, next_vertex_count, &cell_values, &vertex_positions](
				D2DrlgGridStrc& pDrlgGrid,
				int (&pCellsFlags)[width * height],
				int (&pCellsRowOffsets)[height],
				D2DrlgVertexStrc& pDrlgVertex,
				D2DrlgVertexStrc (&pNextVertices)[next_vertex_count]
			) {
				std::copy(std::begin(cell_values), std::end(cell_values), std::begin(pCellsFlags));
				for (auto row = 0; row < height; ++row)
				{
					pCellsRowOffsets[row] = row * width;
				}

				pDrlgGrid.pCellsFlags = pCellsFlags;
				pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
				pDrlgGrid.nWidth = width;
				pDrlgGrid.nHeight = height;

				pDrlgVertex.nPosX = vertex_positions[0][0];
				pDrlgVertex.nPosY = vertex_positions[0][1];
				pDrlgVertex.pNext = &pNextVertices[0];

				for (auto i = 0; i < next_vertex_count; ++i)
				{
					pNextVertices[i].nPosX = vertex_positions[i + 1][0];
					pNextVertices[i].nPosY = vertex_positions[i + 1][1];
					pNextVertices[i].pNext = i + 1 < next_vertex_count ? &pNextVertices[i + 1] : nullptr;
				}
			};

			setup_data(moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets, moo_pDrlgVertex, moo_pNextVertices);
			setup_data(original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets, original_pDrlgVertex, original_pNextVertices);

			// Call both implementations
			sut(&moo_pDrlgGrid, &moo_pDrlgVertex, nFlag);
			original(&original_pDrlgGrid, &original_pDrlgVertex, nFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellsFlags, width * height }), (DynamicArray<int>{ original_pCellsFlags, width * height }), "Comparing pCellsFlags");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75F60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD75F60, dll_base + 0x00035F60);

		SUBCASE("")
		{
			constexpr auto coord_x = 10;
			constexpr auto coord_y = 20;
			constexpr auto width = 8;
			constexpr auto height = 8;
			constexpr auto line_count = 6;

			// Start and end positions of the lines, covering both main directions, both signs and lines partly outside of the coordinates
			const int lines[line_count][4] = {
				{ 11, 21, 16, 23 },
				{ 16, 26, 9, 22 },
				{ 12, 19, 14, 27 },
				{ 17, 27, 15, 21 },
				{ 13, 23, 13, 23 },
				{ 10, 20, 17, 27 },
			};

			for (const auto& line : lines)
			{
				for (auto operation = static_cast<int>(FLAG_OPERATION_OR); operation <= FLAG_OPERATION_AND_NEGATED; ++operation)
				{
					int cell_values[width * height];
					for (auto& cell_value : cell_values)
					{
						cell_value = random_unsigned_integer(0, 3);
					}

					// Input data
					D2DrlgGridStrc moo_pDrlgGrid{};
					int moo_pCellsFlags[width * height]{};
					int moo_pCellsRowOffsets[height]{};
					D2DrlgVertexStrc moo_pDrlgVertex{};
					D2DrlgVertexStrc moo_pNextVertex{};
					D2DrlgCoordStrc moo_pDrlgCoord{};
					D2DrlgGridStrc original_pDrlgGrid{};
					int original_pCellsFlags[width * height]{};
					int original_pCellsRowOffsets[height]{};
					D2DrlgVertexStrc original_pDrlgVertex{};
					D2DrlgVertexStrc original_pNextVertex{};
					D2DrlgCoordStrc original_pDrlgCoord{};
					int nFlag = random_unsigned_integer();
					FlagOperation eOperation = static_cast<FlagOperation>(operation);
					int nSize = 3;

					const auto setup_data = [coord_x, coord_y, width, height, &cell_values, &line](
						D2DrlgGridStrc& pDrlgGrid,
						int (&pCellsFlags)[width * height],
						int (&pCellsRowOffsets)[height],
						D2DrlgVertexStrc& pDrlgVertex,
						D2DrlgVertexStrc& pNextVertex,
						D2DrlgCoordStrc& pDrlgCoord
					) {
						std::copy(std::begin(cell_values), std::end(cell_values), std::begin(pCellsFlags));
						for (auto row = 0; row < height; ++row)
						{
							pCellsRowOffsets[row] = row * width;
						}

						pDrlgGrid.pCellsFlags = pCellsFlags;
						pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
						pDrlgGrid.nWidth = width;
						pDrlgGrid.nHeight = height;

						pDrlgVertex.nPosX = line[0];
						pDrlgVertex.nPosY = line[1];
						pDrlgVertex.pNext = &pNextVertex;

						pNextVertex.nPosX = line[2];
						pNextVertex.nPosY = line[3];

						pDrlgCoord.nPosX = coord_x;
						pDrlgCoord.nPosY = coord_y;
						pDrlgCoord.nWidth = width;
						pDrlgCoord.nHeight = height;
					};

					setup_data(moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets, moo_pDrlgVertex, moo_pNextVertex, moo_pDrlgCoord);
					setup_data(original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets, original_pDrlgVertex, original_pNextVertex, original_pDrlgCoord);

					// Call both implementations
					sut(&moo_pDrlgGrid, &moo_pDrlgVertex, &moo_pDrlgCoord, nFlag, eOperation, nSize);
					original(&original_pDrlgGrid, &original_pDrlgVertex, &original_pDrlgCoord, nFlag, eOperation, nSize);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
					MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
					MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
					MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellsFlags, width * height }), (DynamicArray<int>{ original_pCellsFlags, width * height }), "Comparing pCellsFlags");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76230")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_InitializeGridCells, dll_base + 0x00036230);

		SUBCASE("")
		{
			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			D2DrlgGridStrc original_pDrlgGrid{};
			int nWidth = random_unsigned_integer(1, 16);
			int nHeight = random_unsigned_integer(1, 16);

			const auto setup_data = [](
				D2DrlgGridStrc& pDrlgGrid
			) {
				pDrlgGrid.unk0x10 = 1;
			};

			setup_data(moo_pDrlgGrid);
			setup_data(original_pDrlgGrid);

			// Call both implementations
			sut(nullptr, &moo_pDrlgGrid, nWidth, nHeight);
			original(nullptr, &original_pDrlgGrid, nWidth, nHeight);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pDrlgGrid.pCellsRowOffsets, nHeight * (nWidth + 1) }), (DynamicArray<int>{ original_pDrlgGrid.pCellsRowOffsets, nHeight * (nWidth + 1) }), "Comparing pCellsRowOffsets");

			auto moo_cells_flags_offset = static_cast<int>(moo_pDrlgGrid.pCellsFlags - moo_pDrlgGrid.pCellsRowOffsets);
			auto original_cells_flags_offset = static_cast<int>(original_pDrlgGrid.pCellsFlags - original_pDrlgGrid.pCellsRowOffsets);
			MOO_CHECK_EQ(moo_cells_flags_offset, original_cells_flags_offset, "Comparing pCellsFlags offset");

			D2_FREE_POOL(nullptr, moo_pDrlgGrid.pCellsRowOffsets);
			D2_FREE_POOL(nullptr, original_pDrlgGrid.pCellsRowOffsets);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD762B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_FillGrid, dll_base + 0x000362B0);

		SUBCASE("")
		{
			constexpr auto width = 5;
			constexpr auto height = 4;

			int cell_values[width * height];
			for (auto& cell_value : cell_values)
			{
				cell_value = random_unsigned_integer();
			}

			int row_offset_values[height];
			for (auto& row_offset_value : row_offset_values)
			{
				row_offset_value = random_unsigned_integer();
			}

			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			int moo_pCellPos[width * height]{};
			int moo_pCellRowOffsets[height]{};
			D2DrlgGridStrc original_pDrlgGrid{};
			int original_pCellPos[width * height]{};
			int original_pCellRowOffsets[height]{};
			int nWidth = width;
			int nHeight = height;

			const auto setup_data = [width, height, &cell_values, &row_offset_values](
				D2DrlgGridStrc& pDrlgGrid,
				int (&pCellPos)[width * height],
				int (&pCellRowOffsets)[height]
			) {
				std::copy(std::begin(cell_values), std::end(cell_values), std::begin(pCellPos));
				std::copy(std::begin(row_offset_values), std::end(row_offset_values), std::begin(pCellRowOffsets));
				pDrlgGrid.unk0x10 = 1;
			};

			setup_data(moo_pDrlgGrid, moo_pCellPos, moo_pCellRowOffsets);
			setup_data(original_pDrlgGrid, original_pCellPos, original_pCellRowOffsets);

			// Call both implementations
			sut(&moo_pDrlgGrid, nWidth, nHeight, moo_pCellPos, moo_pCellRowOffsets);
			original(&original_pDrlgGrid, nWidth, nHeight, original_pCellPos, original_pCellRowOffsets);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellPos, width * height }), (DynamicArray<int>{ original_pCellPos, width * height }), "Comparing pCellPos");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellRowOffsets, height }), (DynamicArray<int>{ original_pCellRowOffsets, height }), "Comparing pCellRowOffsets");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76310")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_FillNewCellFlags, dll_base + 0x00036310);

		SUBCASE("")
		{
			constexpr auto width = 16;
			constexpr auto height = 16;

			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			int moo_pCellPos[width * height]{};
			D2DrlgCoordStrc moo_pDrlgCoord{};
			D2DrlgGridStrc original_pDrlgGrid{};
			int original_pCellPos[width * height]{};
			D2DrlgCoordStrc original_pDrlgCoord{};
			int nWidth = width;

			const auto setup_data = [](
				D2DrlgCoordStrc& pDrlgCoord
			) {
				pDrlgCoord.nPosX = 3;
				pDrlgCoord.nPosY = 5;
				pDrlgCoord.nWidth = 4;
				pDrlgCoord.nHeight = 6;
			};

			setup_data(moo_pDrlgCoord);
			setup_data(original_pDrlgCoord);

			// Call both implementations
			sut(nullptr, &moo_pDrlgGrid, moo_pCellPos, &moo_pDrlgCoord, nWidth);
			original(nullptr, &original_pDrlgGrid, original_pCellPos, &original_pDrlgCoord, nWidth);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellPos, width * height }), (DynamicArray<int>{ original_pCellPos, width * height }), "Comparing pCellPos");
			MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pDrlgGrid.pCellsRowOffsets, moo_pDrlgCoord.nHeight }), (DynamicArray<int>{ original_pDrlgGrid.pCellsRowOffsets, original_pDrlgCoord.nHeight }), "Comparing pCellsRowOffsets");

			auto moo_cells_flags_offset = static_cast<int>(moo_pDrlgGrid.pCellsFlags - moo_pCellPos);
			auto original_cells_flags_offset = static_cast<int>(original_pDrlgGrid.pCellsFlags - original_pCellPos);
			MOO_CHECK_EQ(moo_cells_flags_offset, original_cells_flags_offset, "Comparing pCellsFlags offset");

			D2_FREE_POOL(nullptr, moo_pDrlgGrid.pCellsRowOffsets);
			D2_FREE_POOL(nullptr, original_pDrlgGrid.pCellsRowOffsets);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76380")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_AssignCellsOffsetsAndFlags, dll_base + 0x00036380);

		SUBCASE("")
		{
			constexpr auto width = 16;
			constexpr auto height = 16;
			constexpr auto coord_height = 6;

			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			int moo_pCellPos[width * height]{};
			D2DrlgCoordStrc moo_pDrlgCoord{};
			int moo_pCellFlags[coord_height]{};
			D2DrlgGridStrc original_pDrlgGrid{};
			int original_pCellPos[width * height]{};
			D2DrlgCoordStrc original_pDrlgCoord{};
			int original_pCellFlags[coord_height]{};
			int nWidth = width;

			const auto setup_data = [coord_height](
				D2DrlgCoordStrc& pDrlgCoord
			) {
				pDrlgCoord.nPosX = 3;
				pDrlgCoord.nPosY = 5;
				pDrlgCoord.nWidth = 4;
				pDrlgCoord.nHeight = coord_height;
			};

			setup_data(moo_pDrlgCoord);
			setup_data(original_pDrlgCoord);

			// Call both implementations
			sut(&moo_pDrlgGrid, moo_pCellPos, &moo_pDrlgCoord, nWidth, moo_pCellFlags);
			original(&original_pDrlgGrid, original_pCellPos, &original_pDrlgCoord, nWidth, original_pCellFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellPos, width * height }), (DynamicArray<int>{ original_pCellPos, width * height }), "Comparing pCellPos");
			MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
			MOO_CHECK_EQ((DynamicArray<int>{ moo_pCellFlags, coord_height }), (DynamicArray<int>{ original_pCellFlags, coord_height }), "Comparing pCellFlags");

			auto moo_cells_flags_offset = static_cast<int>(moo_pDrlgGrid.pCellsFlags - moo_pCellPos);
			auto original_cells_flags_offset = static_cast<int>(original_pDrlgGrid.pCellsFlags - original_pCellPos);
			MOO_CHECK_EQ(moo_cells_flags_offset, original_cells_flags_offset, "Comparing pCellsFlags offset");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD763E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_FreeGrid, dll_base + 0x000363E0);

		SUBCASE("allocated")
		{
			constexpr auto width = 4;
			constexpr auto height = 3;

			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			D2DrlgGridStrc original_pDrlgGrid{};

			const auto setup_data = [width, height](
				D2DrlgGridStrc& pDrlgGrid
			) {
				pDrlgGrid.pCellsRowOffsets = (int32_t*)D2_CALLOC_POOL(nullptr, sizeof(int32_t) * height * (width + 1));
				pDrlgGrid.pCellsFlags = &pDrlgGrid.pCellsRowOffsets[height];
				pDrlgGrid.nWidth = width;
				pDrlgGrid.nHeight = height;
			};

			setup_data(moo_pDrlgGrid);
			setup_data(original_pDrlgGrid);

			// Call both implementations
			sut(nullptr, &moo_pDrlgGrid);
			original(nullptr, &original_pDrlgGrid);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}

		SUBCASE("not allocated")
		{
			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			D2DrlgGridStrc original_pDrlgGrid{};

			// Call both implementations
			sut(nullptr, &moo_pDrlgGrid);
			original(nullptr, &original_pDrlgGrid);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76410")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_ResetGrid, dll_base + 0x00036410);

		SUBCASE("")
		{
			constexpr auto width = 4;
			constexpr auto height = 3;

			// Input data
			D2DrlgGridStrc moo_pDrlgGrid{};
			int moo_pCellsFlags[width * height]{};
			int moo_pCellsRowOffsets[height]{};
			D2DrlgGridStrc original_pDrlgGrid{};
			int original_pCellsFlags[width * height]{};
			int original_pCellsRowOffsets[height]{};

			const auto setup_data = [width, height](
				D2DrlgGridStrc& pDrlgGrid,
				int (&pCellsFlags)[width * height],
				int (&pCellsRowOffsets)[height]
			) {
				pDrlgGrid.pCellsFlags = pCellsFlags;
				pDrlgGrid.pCellsRowOffsets = pCellsRowOffsets;
				pDrlgGrid.nWidth = width;
				pDrlgGrid.nHeight = height;
			};

			setup_data(moo_pDrlgGrid, moo_pCellsFlags, moo_pCellsRowOffsets);
			setup_data(original_pDrlgGrid, original_pCellsFlags, original_pCellsRowOffsets);

			// Call both implementations
			sut(&moo_pDrlgGrid);
			original(&original_pDrlgGrid);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
}

#endif
