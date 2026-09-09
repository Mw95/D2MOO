#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlgGrid.h>


TEST_SUITE("D2DrlgDrlgGridTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_OverwriteFlag, dll_base + 0x00035BA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int pFlag{};
				
				return std::tuple{ pFlag };
			};
			
			// Input data
			auto [moo_pFlag] = setup_data();
			auto [original_pFlag] = setup_data();
			int nFlag{};

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_OrFlag, dll_base + 0x00035BB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int pFlag{};
				
				return std::tuple{ pFlag };
			};
			
			// Input data
			auto [moo_pFlag] = setup_data();
			auto [original_pFlag] = setup_data();
			int nFlag{};

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_AndFlag, dll_base + 0x00035BC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int pFlag{};
				
				return std::tuple{ pFlag };
			};
			
			// Input data
			auto [moo_pFlag] = setup_data();
			auto [original_pFlag] = setup_data();
			int nFlag{};

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75BD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRGLGRID_XorFlag, dll_base + 0x00035BD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int pFlag{};
				
				return std::tuple{ pFlag };
			};
			
			// Input data
			auto [moo_pFlag] = setup_data();
			auto [original_pFlag] = setup_data();
			int nFlag{};

			// Call both implementations
			sut(&moo_pFlag, nFlag);
			original(&original_pFlag, nFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pFlag, original_pFlag, "Comparing pFlag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_IsGridValid, dll_base + 0x00035C00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgGrid);
			const auto original_result = original(&original_pDrlgGrid);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75C20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_IsPointInsideGridArea, dll_base + 0x00035C20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgGrid, nX, nY);
			const auto original_result = original(&original_pDrlgGrid, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75C50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_AlterGridFlag, dll_base + 0x00035C50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();
			int nX{};
			int nY{};
			int nFlag{};
			FlagOperation eOperation{};

			// Call both implementations
			sut(&moo_pDrlgGrid, nX, nY, nFlag, eOperation);
			original(&original_pDrlgGrid, nX, nY, nFlag, eOperation);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75C80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_GetGridFlagsPointer, dll_base + 0x00035C80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgGrid, nX, nY);
			const auto original_result = original(&original_pDrlgGrid, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75CA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_GetGridEntry, dll_base + 0x00035CA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgGrid, nX, nY);
			const auto original_result = original(&original_pDrlgGrid, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_AlterAllGridFlags, dll_base + 0x00035CC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();
			int nFlag{};
			FlagOperation eOperation{};

			// Call both implementations
			sut(&moo_pDrlgGrid, nFlag, eOperation);
			original(&original_pDrlgGrid, nFlag, eOperation);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75D20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_AlterEdgeGridFlags, dll_base + 0x00035D20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();
			int nFlag{};
			FlagOperation eOperation{};

			// Call both implementations
			sut(&moo_pDrlgGrid, nFlag, eOperation);
			original(&original_pDrlgGrid, nFlag, eOperation);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_SetVertexGridFlags, dll_base + 0x00035F10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				D2DrlgVertexStrc pDrlgVertex{};
				
				return std::tuple{ pDrlgGrid, pDrlgVertex };
			};
			
			// Input data
			auto [moo_pDrlgGrid, moo_pDrlgVertex] = setup_data();
			auto [original_pDrlgGrid, original_pDrlgVertex] = setup_data();
			int nFlag{};

			// Call both implementations
			sut(&moo_pDrlgGrid, &moo_pDrlgVertex, nFlag);
			original(&original_pDrlgGrid, &original_pDrlgVertex, nFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			SKIP_MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75F60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD75F60, dll_base + 0x00035F60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				D2DrlgVertexStrc pDrlgVertex{};
				D2DrlgCoordStrc pDrlgCoord{};
				
				return std::tuple{ pDrlgGrid, pDrlgVertex, pDrlgCoord };
			};
			
			// Input data
			auto [moo_pDrlgGrid, moo_pDrlgVertex, moo_pDrlgCoord] = setup_data();
			auto [original_pDrlgGrid, original_pDrlgVertex, original_pDrlgCoord] = setup_data();
			int nFlag{};
			FlagOperation eOperation{};
			int nSize{};

			// Call both implementations
			sut(&moo_pDrlgGrid, &moo_pDrlgVertex, &moo_pDrlgCoord, nFlag, eOperation, nSize);
			original(&original_pDrlgGrid, &original_pDrlgVertex, &original_pDrlgCoord, nFlag, eOperation, nSize);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			SKIP_MOO_CHECK_EQ(moo_pDrlgVertex, original_pDrlgVertex, "Comparing pDrlgVertex");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76230" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_InitializeGridCells, dll_base + 0x00036230);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nWidth{};
			int nHeight{};

			// Call both implementations
			sut(moo_pMemPool, &moo_pDrlgGrid, nWidth, nHeight);
			original(original_pMemPool, &original_pDrlgGrid, nWidth, nHeight);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD762B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_FillGrid, dll_base + 0x000362B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				int pCellPos{};
				int pCellRowOffsets{};
				
				return std::tuple{ pDrlgGrid, pCellPos, pCellRowOffsets };
			};
			
			// Input data
			auto [moo_pDrlgGrid, moo_pCellPos, moo_pCellRowOffsets] = setup_data();
			auto [original_pDrlgGrid, original_pCellPos, original_pCellRowOffsets] = setup_data();
			int nWidth{};
			int nHeight{};

			// Call both implementations
			sut(&moo_pDrlgGrid, nWidth, nHeight, &moo_pCellPos, &moo_pCellRowOffsets);
			original(&original_pDrlgGrid, nWidth, nHeight, &original_pCellPos, &original_pCellRowOffsets);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			SKIP_MOO_CHECK_EQ(moo_pCellPos, original_pCellPos, "Comparing pCellPos");
			SKIP_MOO_CHECK_EQ(moo_pCellRowOffsets, original_pCellRowOffsets, "Comparing pCellRowOffsets");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_FillNewCellFlags, dll_base + 0x00036310);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				int pCellPos{};
				D2DrlgCoordStrc pDrlgCoord{};
				
				return std::tuple{ pDrlgGrid, pCellPos, pDrlgCoord };
			};
			
			// Input data
			auto [moo_pDrlgGrid, moo_pCellPos, moo_pDrlgCoord] = setup_data();
			auto [original_pDrlgGrid, original_pCellPos, original_pDrlgCoord] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nWidth{};

			// Call both implementations
			sut(moo_pMemPool, &moo_pDrlgGrid, &moo_pCellPos, &moo_pDrlgCoord, nWidth);
			original(original_pMemPool, &original_pDrlgGrid, &original_pCellPos, &original_pDrlgCoord, nWidth);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			SKIP_MOO_CHECK_EQ(moo_pCellPos, original_pCellPos, "Comparing pCellPos");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76380" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_AssignCellsOffsetsAndFlags, dll_base + 0x00036380);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				int pCellPos{};
				D2DrlgCoordStrc pDrlgCoord{};
				int pCellFlags{};
				
				return std::tuple{ pDrlgGrid, pCellPos, pDrlgCoord, pCellFlags };
			};
			
			// Input data
			auto [moo_pDrlgGrid, moo_pCellPos, moo_pDrlgCoord, moo_pCellFlags] = setup_data();
			auto [original_pDrlgGrid, original_pCellPos, original_pDrlgCoord, original_pCellFlags] = setup_data();
			int nWidth{};

			// Call both implementations
			sut(&moo_pDrlgGrid, &moo_pCellPos, &moo_pDrlgCoord, nWidth, &moo_pCellFlags);
			original(&original_pDrlgGrid, &original_pCellPos, &original_pDrlgCoord, nWidth, &original_pCellFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			SKIP_MOO_CHECK_EQ(moo_pCellPos, original_pCellPos, "Comparing pCellPos");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
			SKIP_MOO_CHECK_EQ(moo_pCellFlags, original_pCellFlags, "Comparing pCellFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD763E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_FreeGrid, dll_base + 0x000363E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pDrlgGrid);
			original(original_pMemPool, &original_pDrlgGrid);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD76410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGGRID_ResetGrid, dll_base + 0x00036410);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgGrid] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgGrid);
			original(&original_pDrlgGrid);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
}
