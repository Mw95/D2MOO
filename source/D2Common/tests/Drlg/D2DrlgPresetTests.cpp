#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgPreset.h>


TEST_SUITE("D2DrlgPresetTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD859A0 (#11222)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_CountPresetObjectsByAct, dll_base + 0x000459A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			uint8_t nAct{};

			// Call both implementations
			const auto moo_result = sut(nAct);
			const auto original_result = original(nAct);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD859E0 (#11223)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetObjectIndexFromObjPreset, dll_base + 0x000459E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			uint8_t nAct{};
			int nUnitId{};

			// Call both implementations
			const auto moo_result = sut(nAct, nUnitId);
			const auto original_result = original(nAct, nUnitId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD85A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_ParseDS1File, dll_base + 0x00045A10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgFileStrc pDrlgFile{};
				
				return std::tuple{ pDrlgFile };
			};
			
			// Input data
			auto [moo_pDrlgFile] = setup_data();
			auto [original_pDrlgFile] = setup_data();
			HD2ARCHIVE hArchive{};
			char szFileName{};

			// Call both implementations
			sut(&moo_pDrlgFile, hArchive, &szFileName);
			original(&original_pDrlgFile, hArchive, &szFileName);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgFile, original_pDrlgFile, "Comparing pDrlgFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_LoadDrlgFile, dll_base + 0x00046050);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgFileStrc* ppDrlgFile{};
				
				return std::tuple{ ppDrlgFile };
			};
			
			// Input data
			auto [moo_ppDrlgFile] = setup_data();
			auto [original_ppDrlgFile] = setup_data();
			HD2ARCHIVE hArchive{};
			char szFile{};

			// Call both implementations
			sut(&moo_ppDrlgFile, hArchive, &szFile);
			original(&original_ppDrlgFile, hArchive, &szFile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppDrlgFile, original_ppDrlgFile, "Comparing ppDrlgFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeDrlgFile, dll_base + 0x00046190);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgFileStrc* ppDrlgFile{};
				
				return std::tuple{ ppDrlgFile };
			};
			
			// Input data
			auto [moo_ppDrlgFile] = setup_data();
			auto [original_ppDrlgFile] = setup_data();

			// Call both implementations
			sut(&moo_ppDrlgFile);
			original(&original_ppDrlgFile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppDrlgFile, original_ppDrlgFile, "Comparing ppDrlgFile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_CopyPresetUnit, dll_base + 0x00046310);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2PresetUnitStrc pPresetUnit{};
				
				return std::tuple{ pPresetUnit };
			};
			
			// Input data
			auto [moo_pPresetUnit] = setup_data();
			auto [original_pPresetUnit] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(moo_pMemPool, &moo_pPresetUnit, nX, nY);
			const auto original_result = original(original_pMemPool, &original_pPresetUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pPresetUnit, original_pPresetUnit, "Comparing pPresetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreePresetUnit, dll_base + 0x00046430);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2PresetUnitStrc pPresetUnit{};
				
				return std::tuple{ pPresetUnit };
			};
			
			// Input data
			auto [moo_pPresetUnit] = setup_data();
			auto [original_pPresetUnit] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pPresetUnit);
			original(original_pMemPool, &original_pPresetUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pPresetUnit, original_pPresetUnit, "Comparing pPresetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86480 (#10020)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_CreateCopyOfMapAI, dll_base + 0x00046480);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MapAIStrc pMapAI{};
				
				return std::tuple{ pMapAI };
			};
			
			// Input data
			auto [moo_pMapAI] = setup_data();
			auto [original_pMapAI] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			const auto moo_result = sut(moo_pMemPool, &moo_pMapAI);
			const auto original_result = original(original_pMemPool, &original_pMapAI);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pMapAI, original_pMapAI, "Comparing pMapAI");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD864F0 (#10021)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_ChangeMapAI, dll_base + 0x000464F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MapAIStrc* ppMapAI1{};
				D2MapAIStrc* ppMapAI2{};
				
				return std::tuple{ ppMapAI1, ppMapAI2 };
			};
			
			// Input data
			auto [moo_ppMapAI1, moo_ppMapAI2] = setup_data();
			auto [original_ppMapAI1, original_ppMapAI2] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_ppMapAI1, &moo_ppMapAI2);
			const auto original_result = original(&original_ppMapAI1, &original_ppMapAI2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppMapAI1, original_ppMapAI1, "Comparing ppMapAI1");
			SKIP_MOO_CHECK_EQ(moo_ppMapAI2, original_ppMapAI2, "Comparing ppMapAI2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86500 (#10022)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeMapAI, dll_base + 0x00046500);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MapAIStrc pMapAI{};
				
				return std::tuple{ pMapAI };
			};
			
			// Input data
			auto [moo_pMapAI] = setup_data();
			auto [original_pMapAI] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pMapAI);
			original(original_pMemPool, &original_pMapAI);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pMapAI, original_pMapAI, "Comparing pMapAI");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AddPresetUnitToDrlgMap, dll_base + 0x00046540);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgMapStrc pDrlgMap{};
				D2SeedStrc pSeed{};
				
				return std::tuple{ pDrlgMap, pSeed };
			};
			
			// Input data
			auto [moo_pDrlgMap, moo_pSeed] = setup_data();
			auto [original_pDrlgMap, original_pSeed] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pDrlgMap, &moo_pSeed);
			original(original_pMemPool, &original_pDrlgMap, &original_pSeed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD867A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_SpawnHardcodedPresetUnits, dll_base + 0x000467A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86AC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AddPresetRiverObjects, dll_base + 0x00046AC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgMapStrc pDrlgMap{};
				D2DrlgGridStrc pDrlgGrid{};
				
				return std::tuple{ pDrlgMap, pDrlgGrid };
			};
			
			// Input data
			auto [moo_pDrlgMap, moo_pDrlgGrid] = setup_data();
			auto [original_pDrlgMap, original_pDrlgGrid] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			int nOffsetX{};

			// Call both implementations
			sut(&moo_pDrlgMap, moo_pMemPool, nOffsetX, &moo_pDrlgGrid);
			original(&original_pDrlgMap, original_pMemPool, nOffsetX, &original_pDrlgGrid);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86C80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreePresetRoomData, dll_base + 0x00046C80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86CE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeDrlgGrids, dll_base + 0x00046CE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pDrlgRoom);
			original(original_pMemPool, &original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86D60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeDrlgGridsFromPresetRoom, dll_base + 0x00046D60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86D80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AllocPresetRoomData, dll_base + 0x00046D80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_InitPresetRoomData, dll_base + 0x00046DC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				D2DrlgMapStrc pDrlgMap{};
				D2DrlgCoordStrc pDrlgCoord{};
				D2DrlgGridStrc a7{};
				
				return std::tuple{ pLevel, pDrlgMap, pDrlgCoord, a7 };
			};
			
			// Input data
			auto [moo_pLevel, moo_pDrlgMap, moo_pDrlgCoord, moo_a7] = setup_data();
			auto [original_pLevel, original_pDrlgMap, original_pDrlgCoord, original_a7] = setup_data();
			uint32_t dwDT1Mask{};
			int dwRoomFlags{};
			int dwPresetFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, &moo_pDrlgMap, &moo_pDrlgCoord, dwDT1Mask, dwRoomFlags, dwPresetFlags, &moo_a7);
			const auto original_result = original(&original_pLevel, &original_pDrlgMap, &original_pDrlgCoord, dwDT1Mask, dwRoomFlags, dwPresetFlags, &original_a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			SKIP_MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
			SKIP_MOO_CHECK_EQ(moo_a7, original_a7, "Comparing a7");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD86E50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_InitPresetRoomGrids, dll_base + 0x00046E50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD870F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetTombStoneTileCoords, dll_base + 0x000470F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				D2CoordStrc* ppTombStoneTiles{};
				int pnTombStoneTiles{};
				
				return std::tuple{ pDrlgRoom, ppTombStoneTiles, pnTombStoneTiles };
			};
			
			// Input data
			auto [moo_pDrlgRoom, moo_ppTombStoneTiles, moo_pnTombStoneTiles] = setup_data();
			auto [original_pDrlgRoom, original_ppTombStoneTiles, original_pnTombStoneTiles] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom, &moo_ppTombStoneTiles, &moo_pnTombStoneTiles);
			original(&original_pDrlgRoom, &original_ppTombStoneTiles, &original_pnTombStoneTiles);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			SKIP_MOO_CHECK_EQ(moo_ppTombStoneTiles, original_ppTombStoneTiles, "Comparing ppTombStoneTiles");
			SKIP_MOO_CHECK_EQ(moo_pnTombStoneTiles, original_pnTombStoneTiles, "Comparing pnTombStoneTiles");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87130" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AddPresetRoomMapTiles, dll_base + 0x00047130);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom);
			original(&original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87560" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_BuildArea, dll_base + 0x00047560);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				D2DrlgMapStrc pDrlgMap{};
				
				return std::tuple{ pLevel, pDrlgMap };
			};
			
			// Input data
			auto [moo_pLevel, moo_pDrlgMap] = setup_data();
			auto [original_pLevel, original_pDrlgMap] = setup_data();
			int nFlags{};
			BOOL bSingleRoom{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, &moo_pDrlgMap, nFlags, bSingleRoom);
			const auto original_result = original(&original_pLevel, &original_pDrlgMap, nFlags, bSingleRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			SKIP_MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_BuildPresetArea, dll_base + 0x00047760);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				D2DrlgGridStrc pDrlgGrid{};
				D2DrlgMapStrc pDrlgMap{};
				
				return std::tuple{ pLevel, pDrlgGrid, pDrlgMap };
			};
			
			// Input data
			auto [moo_pLevel, moo_pDrlgGrid, moo_pDrlgMap] = setup_data();
			auto [original_pLevel, original_pDrlgGrid, original_pDrlgMap] = setup_data();
			int nFlags{};
			BOOL bSingleRoom{};

			// Call both implementations
			sut(&moo_pLevel, &moo_pDrlgGrid, nFlags, &moo_pDrlgMap, bSingleRoom);
			original(&original_pLevel, &original_pDrlgGrid, nFlags, &original_pDrlgMap, bSingleRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			SKIP_MOO_CHECK_EQ(moo_pDrlgGrid, original_pDrlgGrid, "Comparing pDrlgGrid");
			SKIP_MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_SetPickedFileInDrlgMap, dll_base + 0x00047E10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgMapStrc pDrlgMap{};
				
				return std::tuple{ pDrlgMap };
			};
			
			// Input data
			auto [moo_pDrlgMap] = setup_data();
			auto [original_pDrlgMap] = setup_data();
			int nPickedFile{};

			// Call both implementations
			sut(&moo_pDrlgMap, nPickedFile);
			original(&original_pDrlgMap, nPickedFile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_AllocDrlgMap, dll_base + 0x00047E20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				D2DrlgCoordStrc pDrlgCoord{};
				D2SeedStrc pSeed{};
				
				return std::tuple{ pLevel, pDrlgCoord, pSeed };
			};
			
			// Input data
			auto [moo_pLevel, moo_pDrlgCoord, moo_pSeed] = setup_data();
			auto [original_pLevel, original_pDrlgCoord, original_pSeed] = setup_data();
			int nLvlPrestId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nLvlPrestId, &moo_pDrlgCoord, &moo_pSeed);
			const auto original_result = original(&original_pLevel, nLvlPrestId, &original_pDrlgCoord, &original_pSeed);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87F00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetSizeX, dll_base + 0x00047F00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nLvlPrestId{};

			// Call both implementations
			const auto moo_result = sut(nLvlPrestId);
			const auto original_result = original(nLvlPrestId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetSizeY, dll_base + 0x00047F10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nLvlPrestId{};

			// Call both implementations
			const auto moo_result = sut(nLvlPrestId);
			const auto original_result = original(nLvlPrestId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD87F20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_FreeDrlgMap, dll_base + 0x00047F20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgMapStrc pDrlgMap{};
				
				return std::tuple{ pDrlgMap };
			};
			
			// Input data
			auto [moo_pDrlgMap] = setup_data();
			auto [original_pDrlgMap] = setup_data();
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			// Call both implementations
			sut(moo_pMemPool, &moo_pDrlgMap);
			original(original_pMemPool, &original_pDrlgMap);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pDrlgMap, original_pDrlgMap, "Comparing pDrlgMap");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD881A0 (#10008)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetLevelPrestIdFromRoomEx, dll_base + 0x000481A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD881B0 (#10009)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GetPickedLevelPrestFilePathFromRoomEx, dll_base + 0x000481B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgRoom);
			const auto original_result = original(&original_pDrlgRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD881D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_UpdatePops, dll_base + 0x000481D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlgRoom] = setup_data();
			auto [original_pDrlgRoom] = setup_data();
			int nX{};
			int nY{};
			BOOL bOtherRoom{};

			// Call both implementations
			sut(&moo_pDrlgRoom, nX, nY, bOtherRoom);
			original(&original_pDrlgRoom, nX, nY, bOtherRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_TogglePopsVisibility, dll_base + 0x00048450);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom{};
				D2DrlgCoordStrc pDrlgCoord{};
				
				return std::tuple{ pDrlgRoom, pDrlgCoord };
			};
			
			// Input data
			auto [moo_pDrlgRoom, moo_pDrlgCoord] = setup_data();
			auto [original_pDrlgRoom, original_pDrlgCoord] = setup_data();
			int nPopSubIndex{};
			int nTick{};
			BOOL nCellFlags{};

			// Call both implementations
			sut(&moo_pDrlgRoom, nPopSubIndex, &moo_pDrlgCoord, nTick, nCellFlags);
			original(&original_pDrlgRoom, nPopSubIndex, &original_pDrlgCoord, nTick, nCellFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord, original_pDrlgCoord, "Comparing pDrlgCoord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_InitLevelData, dll_base + 0x00048610);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD886F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_GenerateLevel, dll_base + 0x000486F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pLevel);
			original(&original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_ResetDrlgMap, dll_base + 0x00048810);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pLevel };
			};
			
			// Input data
			auto [moo_pLevel] = setup_data();
			auto [original_pLevel] = setup_data();
			BOOL bKeepPreset{};

			// Call both implementations
			sut(&moo_pLevel, bKeepPreset);
			original(&original_pLevel, bKeepPreset);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD88850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLGPRESET_MapTileType, dll_base + 0x00048850);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nId{};

			// Call both implementations
			const auto moo_result = sut(nId);
			const auto original_result = original(nId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
}
