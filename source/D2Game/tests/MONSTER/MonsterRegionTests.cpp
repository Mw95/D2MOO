#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <MONSTER/MonsterRegion.h>
#include <MONSTER/MonsterSpawn.h>
#include <Units/Units.h>


TEST_SUITE("MonsterRegionTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC66260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC66260, dll_base + 0x00036260);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			int32_t moo_pX{};
			int32_t moo_pY{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCoordListStrc original_pRoomCoordList{};
			int32_t original_pX{};
			int32_t original_pY{};
			int32_t nSuperUniqueId{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2RoomCoordListStrc& pRoomCoordList,
				int32_t& pX,
				int32_t& pY
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pRoomCoordList, moo_pX, moo_pY);
			setup_data(original_pGame, original_pRoom, original_pRoomCoordList, original_pX, original_pY);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pRoomCoordList, nSuperUniqueId, &moo_pX, &moo_pY, a7);
			auto original_result = original(&original_pGame, &original_pRoom, &original_pRoomCoordList, nSuperUniqueId, &original_pX, &original_pY, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pRoomCoordList");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC66560" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SpawnPresetMonster_6FC66560, dll_base + 0x00036560);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nClassId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pRoom, nClassId, nX, nY, nMode);
			auto original_result = original(&original_pGame, &original_pRoom, nClassId, nX, nY, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC66FC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERREGION_GetMonStats2TxtRecord, dll_base + 0x00036FC0);
		
		SUBCASE("")
		{
			int32_t nMonsterId{};

			// Call both implementations
			auto moo_result = sut(nMonsterId);
			auto original_result = original(nMonsterId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC67010" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERREGION_CheckMonStats2Flag, dll_base + 0x00037010);
		
		SUBCASE("")
		{
			int32_t nMonsterId{};
			int32_t nFlag{};

			// Call both implementations
			auto moo_result = sut(nMonsterId, nFlag);
			auto original_result = original(nMonsterId, nFlag);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC67080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERREGION_SanitizeMonsterId, dll_base + 0x00037080);
		
		SUBCASE("")
		{
			int32_t nMonsterId{};

			// Call both implementations
			auto moo_result = sut(nMonsterId);
			auto original_result = original(nMonsterId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC670A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC670A0, dll_base + 0x000370A0);
		
		SUBCASE("")
		{
			int32_t nMonsterId{};

			// Call both implementations
			auto moo_result = sut(nMonsterId);
			auto original_result = original(nMonsterId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC67190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PopulateRoom_6FC67190, dll_base + 0x00037190);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom);
			original(&original_pGame, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC67570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC67570, dll_base + 0x00037570);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			D2UnkMonCreateStrc2 moo_a5{};
			int32_t moo_pX{};
			int32_t moo_pY{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCoordListStrc original_pRoomCoordList{};
			D2UnkMonCreateStrc2 original_a5{};
			int32_t original_pX{};
			int32_t original_pY{};
			int32_t nMonsterId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2RoomCoordListStrc& pRoomCoordList,
				D2UnkMonCreateStrc2& a5,
				int32_t& pX,
				int32_t& pY
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pRoomCoordList, moo_a5, moo_pX, moo_pY);
			setup_data(original_pGame, original_pRoom, original_pRoomCoordList, original_a5, original_pX, original_pY);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pRoomCoordList, nMonsterId, &moo_a5, &moo_pX, &moo_pY);
			auto original_result = original(&original_pGame, &original_pRoom, &original_pRoomCoordList, nMonsterId, &original_a5, &original_pX, &original_pY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pRoomCoordList");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC677D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC677D0, dll_base + 0x000377D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCoordListStrc moo_pRoomCoordList{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCoordListStrc original_pRoomCoordList{};
			int32_t nMonsterId{};
			uint8_t nMin{};
			uint8_t nMax{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2RoomCoordListStrc& pRoomCoordList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pRoomCoordList);
			setup_data(original_pGame, original_pRoom, original_pRoomCoordList);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pRoomCoordList, nMonsterId, nMin, nMax);
			auto original_result = original(&original_pGame, &original_pRoom, &original_pRoomCoordList, nMonsterId, nMin, nMax);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pRoomCoordList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC679F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC679F0, dll_base + 0x000379F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom);
			original(&original_pGame, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC67B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERREGION_InitializeAll, dll_base + 0x00037B90);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonsterRegion{};
			D2SeedStrc moo_pSeed{};
			D2MonsterRegionStrc* original_ppMonsterRegion{};
			D2SeedStrc original_pSeed{};
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;
			uint32_t nLowSeed{};
			uint8_t nDifficulty{};
			int32_t bExpansion{};

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonsterRegion,
				D2SeedStrc& pSeed
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonsterRegion, moo_pSeed);
			setup_data(original_ppMonsterRegion, original_pSeed);

			// Call both implementations
			sut(moo_pMemPool, &moo_ppMonsterRegion, &moo_pSeed, nLowSeed, nDifficulty, bExpansion);
			original(original_pMemPool, &original_ppMonsterRegion, &original_pSeed, nLowSeed, nDifficulty, bExpansion);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_ppMonsterRegion, original_ppMonsterRegion, "Comparing ppMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC67F30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERREGION_FreeAll, dll_base + 0x00037F30);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonsterRegion{};
			D2MonsterRegionStrc* original_ppMonsterRegion{};
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonsterRegion
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonsterRegion);
			setup_data(original_ppMonsterRegion);

			// Call both implementations
			sut(moo_pMemPool, &moo_ppMonsterRegion);
			original(original_pMemPool, &original_ppMonsterRegion);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_ppMonsterRegion, original_ppMonsterRegion, "Comparing ppMonsterRegion");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC67F90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERREGION_GetMonsterRegionFromLevelId, dll_base + 0x00037F90);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonsterRegion{};
			D2MonsterRegionStrc* original_ppMonsterRegion{};
			int32_t nLevelId{};

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonsterRegion
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonsterRegion);
			setup_data(original_ppMonsterRegion);

			// Call both implementations
			auto moo_result = sut(&moo_ppMonsterRegion, nLevelId);
			auto original_result = original(&original_ppMonsterRegion, nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppMonsterRegion, original_ppMonsterRegion, "Comparing ppMonsterRegion");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC67FA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC67FA0, dll_base + 0x00037FA0);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonsterRegion{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnit{};
			D2MonsterRegionStrc* original_ppMonsterRegion{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonsterRegion,
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonsterRegion, moo_pRoom, moo_pUnit);
			setup_data(original_ppMonsterRegion, original_pRoom, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_ppMonsterRegion, &moo_pRoom, &moo_pUnit);
			auto original_result = original(&original_ppMonsterRegion, &original_pRoom, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppMonsterRegion, original_ppMonsterRegion, "Comparing ppMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68110" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC68110, dll_base + 0x00038110);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68180" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC68180, dll_base + 0x00038180);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonsterRegion{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnit{};
			D2MonsterRegionStrc* original_ppMonsterRegion{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnit{};
			int32_t bToggleFlag{};

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonsterRegion,
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonsterRegion, moo_pRoom, moo_pUnit);
			setup_data(original_ppMonsterRegion, original_pRoom, original_pUnit);

			// Call both implementations
			sut(&moo_ppMonsterRegion, &moo_pRoom, &moo_pUnit, bToggleFlag);
			original(&original_ppMonsterRegion, &original_pRoom, &original_pUnit, bToggleFlag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppMonsterRegion, original_ppMonsterRegion, "Comparing ppMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC681C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC681C0, dll_base + 0x000381C0);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonsterRegion{};
			D2UnitStrc moo_pUnit{};
			D2MonsterRegionStrc* original_ppMonsterRegion{};
			D2UnitStrc original_pUnit{};
			int32_t nPreviousAlignment{};
			int32_t nNewAlignment{};

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonsterRegion,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonsterRegion, moo_pUnit);
			setup_data(original_ppMonsterRegion, original_pUnit);

			// Call both implementations
			sut(&moo_ppMonsterRegion, &moo_pUnit, nPreviousAlignment, nNewAlignment);
			original(&original_ppMonsterRegion, &original_pUnit, nPreviousAlignment, nNewAlignment);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppMonsterRegion, original_ppMonsterRegion, "Comparing ppMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC68240, dll_base + 0x00038240);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonsterRegion{};
			D2UnitStrc moo_pUnit{};
			D2MonsterRegionStrc* original_ppMonsterRegion{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonsterRegion,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonsterRegion, moo_pUnit);
			setup_data(original_ppMonsterRegion, original_pUnit);

			// Call both implementations
			sut(&moo_ppMonsterRegion, &moo_pUnit);
			original(&original_ppMonsterRegion, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppMonsterRegion, original_ppMonsterRegion, "Comparing ppMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC68280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC68280, dll_base + 0x00038280);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonsterRegion{};
			D2UnitStrc moo_pUnit{};
			D2MonsterRegionStrc* original_ppMonsterRegion{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonsterRegion,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonsterRegion, moo_pUnit);
			setup_data(original_ppMonsterRegion, original_pUnit);

			// Call both implementations
			sut(&moo_ppMonsterRegion, &moo_pUnit);
			original(&original_ppMonsterRegion, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppMonsterRegion, original_ppMonsterRegion, "Comparing ppMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC682C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC682C0, dll_base + 0x000382C0);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc* moo_ppMonRegion{};
			D2UnitStrc moo_pUnit{};
			D2MonsterRegionStrc* original_ppMonRegion{};
			D2UnitStrc original_pUnit{};
			int32_t nLevelId1{};
			int32_t nLevelId2{};
			int32_t nAlignment{};
			int32_t bDead{};
			int32_t a6{};

			const auto setup_data = [](
				D2MonsterRegionStrc*& ppMonRegion,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppMonRegion, moo_pUnit);
			setup_data(original_ppMonRegion, original_pUnit);

			// Call both implementations
			sut(&moo_ppMonRegion, nLevelId1, nLevelId2, nAlignment, bDead, a6, &moo_pUnit);
			original(&original_ppMonRegion, nLevelId1, nLevelId2, nAlignment, bDead, a6, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppMonRegion, original_ppMonRegion, "Comparing ppMonRegion");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
