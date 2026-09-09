#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>


TEST_SUITE("D2DrlgDrlgTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74120 (#10014)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_AllocDrlg, dll_base + 0x00034120);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgActStrc pAct{};
				D2GameStrc pGame{};
				
				return std::tuple{ pAct, pGame };
			};
			
			// Input data
			auto [moo_pAct, moo_pGame] = setup_data();
			auto [original_pAct, original_pGame] = setup_data();
			uint8_t nActNo{};
			HD2ARCHIVE hArchive{};
			uint32_t nInitSeed{};
			int nLevelId{};
			uint32_t nFlags{};
			uint8_t nDifficulty{};
			AUTOMAPFN pfAutoMap{};
			TOWNAUTOMAPFN pfTownAutoMap{};

			// Call both implementations
			const auto moo_result = sut(&moo_pAct, nActNo, hArchive, nInitSeed, nLevelId, nFlags, &moo_pGame, nDifficulty, pfAutoMap, pfTownAutoMap);
			const auto original_result = original(&original_pAct, nActNo, hArchive, nInitSeed, nLevelId, nFlags, &original_pGame, nDifficulty, pfAutoMap, pfTownAutoMap);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAct, original_pAct, "Comparing pAct");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD743B0 (#10012)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_FreeDrlg, dll_base + 0x000343B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();

			// Call both implementations
			sut(&moo_pDrlg);
			original(&original_pDrlg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_FreeLevel, dll_base + 0x00034440);
		
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
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			BOOL bAlloc{};

			// Call both implementations
			sut(moo_pMemPool, &moo_pLevel, bAlloc);
			original(original_pMemPool, &original_pLevel, bAlloc);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD745C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD745C0, dll_base + 0x000345C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgRoomStrc pDrlgRoom1{};
				D2DrlgRoomStrc pDrlgRoom2{};
				
				return std::tuple{ pDrlgRoom1, pDrlgRoom2 };
			};
			
			// Input data
			auto [moo_pDrlgRoom1, moo_pDrlgRoom2] = setup_data();
			auto [original_pDrlgRoom1, original_pDrlgRoom2] = setup_data();

			// Call both implementations
			sut(&moo_pDrlgRoom1, &moo_pDrlgRoom2);
			original(&original_pDrlgRoom1, &original_pDrlgRoom2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom1, original_pDrlgRoom1, "Comparing pDrlgRoom1");
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom2, original_pDrlgRoom2, "Comparing pDrlgRoom2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74700" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_UpdateAndFreeInactiveRooms, dll_base + 0x00034700);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();

			// Call both implementations
			sut(&moo_pDrlg);
			original(&original_pDrlg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD748D0 (#10013)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_AllocLevel, dll_base + 0x000348D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD749A0 (#10005)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetLevel, dll_base + 0x000349A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD749D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetHoradricStaffTombLevelId, dll_base + 0x000349D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg);
			const auto original_result = original(&original_pDrlg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD749E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetDirectionFromCoordinates, dll_base + 0x000349E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgCoordStrc pDrlgCoord1{};
				D2DrlgCoordStrc pDrlgCoord2{};
				
				return std::tuple{ pDrlgCoord1, pDrlgCoord2 };
			};
			
			// Input data
			auto [moo_pDrlgCoord1, moo_pDrlgCoord2] = setup_data();
			auto [original_pDrlgCoord1, original_pDrlgCoord2] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlgCoord1, &moo_pDrlgCoord2);
			const auto original_result = original(&original_pDrlgCoord1, &original_pDrlgCoord2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord1, original_pDrlgCoord1, "Comparing pDrlgCoord1");
			SKIP_MOO_CHECK_EQ(moo_pDrlgCoord2, original_pDrlgCoord2, "Comparing pDrlgCoord2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74A40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_CreateRoomForRoomEx, dll_base + 0x00034A40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				D2DrlgRoomStrc pDrlgRoom{};
				
				return std::tuple{ pDrlg, pDrlgRoom };
			};
			
			// Input data
			auto [moo_pDrlg, moo_pDrlgRoom] = setup_data();
			auto [original_pDrlg, original_pDrlgRoom] = setup_data();

			// Call both implementations
			sut(&moo_pDrlg, &moo_pDrlgRoom);
			original(&original_pDrlg, &original_pDrlgRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74B30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetRoomCenterX_RoomWarpXFromRoom, dll_base + 0x00034B30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74B40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_ComputeLevelWarpInfo, dll_base + 0x00034B40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74C10 (#10006)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_InitLevel, dll_base + 0x00034C10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74D50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetNumberOfPopulatedRoomsInLevel, dll_base + 0x00034D50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74D90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetMinAndMaxCoordinatesFromLevel, dll_base + 0x00034D90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgLevelStrc pLevel{};
				int pTileMinX{};
				int pTileMinY{};
				int pTileMaxX{};
				int pTileMaxY{};
				
				return std::tuple{ pLevel, pTileMinX, pTileMinY, pTileMaxX, pTileMaxY };
			};
			
			// Input data
			auto [moo_pLevel, moo_pTileMinX, moo_pTileMinY, moo_pTileMaxX, moo_pTileMaxY] = setup_data();
			auto [original_pLevel, original_pTileMinX, original_pTileMinY, original_pTileMaxX, original_pTileMaxY] = setup_data();

			// Call both implementations
			sut(&moo_pLevel, &moo_pTileMinX, &moo_pTileMinY, &moo_pTileMaxX, &moo_pTileMaxY);
			original(&original_pLevel, &original_pTileMinX, &original_pTileMinY, &original_pTileMaxX, &original_pTileMaxY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
			SKIP_MOO_CHECK_EQ(moo_pTileMinX, original_pTileMinX, "Comparing pTileMinX");
			SKIP_MOO_CHECK_EQ(moo_pTileMinY, original_pTileMinY, "Comparing pTileMinY");
			SKIP_MOO_CHECK_EQ(moo_pTileMaxX, original_pTileMaxX, "Comparing pTileMaxX");
			SKIP_MOO_CHECK_EQ(moo_pTileMaxY, original_pTileMaxY, "Comparing pTileMaxY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_UpdateRoomExCoordinates, dll_base + 0x00034E10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74EF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetRoomExFromLevelAndCoordinates, dll_base + 0x00034EF0);
		
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
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLevel, nX, nY);
			const auto original_result = original(&original_pLevel, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD74F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetRoomExFromCoordinates, dll_base + 0x00034F70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				D2DrlgRoomStrc pDrlgRoom{};
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pDrlg, pDrlgRoom, pLevel };
			};
			
			// Input data
			auto [moo_pDrlg, moo_pDrlgRoom, moo_pLevel] = setup_data();
			auto [original_pDrlg, original_pDrlgRoom, original_pLevel] = setup_data();
			int nX{};
			int nY{};

			// Call both implementations
			const auto moo_result = sut(nX, nY, &moo_pDrlg, &moo_pDrlgRoom, &moo_pLevel);
			const auto original_result = original(nX, nY, &original_pDrlg, &original_pDrlgRoom, &original_pLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			SKIP_MOO_CHECK_EQ(moo_pDrlgRoom, original_pDrlgRoom, "Comparing pDrlgRoom");
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD751C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_IsTownLevel, dll_base + 0x000351C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(nLevelId);
			const auto original_result = original(nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75260 (#10000)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetLevelTypeFromLevelId, dll_base + 0x00035260);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(nLevelId);
			const auto original_result = original(nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_SetLevelPositionAndSize, dll_base + 0x00035270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				D2DrlgLevelStrc pLevel{};
				
				return std::tuple{ pDrlg, pLevel };
			};
			
			// Input data
			auto [moo_pDrlg, moo_pLevel] = setup_data();
			auto [original_pDrlg, original_pLevel] = setup_data();

			// Call both implementations
			sut(&moo_pDrlg, &moo_pLevel);
			original(&original_pDrlg, &original_pLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
			SKIP_MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75300 (#10001)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetActNoFromLevelId, dll_base + 0x00035300);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(nLevelId);
			const auto original_result = original(nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75330 (#10004)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetSaveMonstersFromLevelId, dll_base + 0x00035330);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(nLevelId);
			const auto original_result = original(nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75350 (#10002)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetLOSDrawFromLevelId, dll_base + 0x00035350);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(nLevelId);
			const auto original_result = original(nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75370" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_GetDrlgWarpFromLevelId, dll_base + 0x00035370);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();
			int nLevelId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg, nLevelId);
			const auto original_result = original(&original_pDrlg, nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD753F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_SetWarpId, dll_base + 0x000353F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgWarpStrc pDrlgWarp{};
				
				return std::tuple{ pDrlgWarp };
			};
			
			// Input data
			auto [moo_pDrlgWarp] = setup_data();
			auto [original_pDrlgWarp] = setup_data();
			int nVis{};
			int nWarp{};
			int nId{};

			// Call both implementations
			sut(&moo_pDrlgWarp, nVis, nWarp, nId);
			original(&original_pDrlgWarp, nVis, nWarp, nId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlgWarp, original_pDrlgWarp, "Comparing pDrlgWarp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD75450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(DRLG_IsOnClient, dll_base + 0x00035450);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2DrlgStrc pDrlg{};
				
				return std::tuple{ pDrlg };
			};
			
			// Input data
			auto [moo_pDrlg] = setup_data();
			auto [original_pDrlg] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pDrlg);
			const auto original_result = original(&original_pDrlg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDrlg, original_pDrlg, "Comparing pDrlg");
		}
	}
}
