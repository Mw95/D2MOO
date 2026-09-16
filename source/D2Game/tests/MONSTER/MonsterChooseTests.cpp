#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <MONSTER/MonsterChoose.h>
#include <MONSTER/MonsterSpawn.h>


TEST_SUITE("MonsterChooseTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC62020, dll_base + 0x00032020);
		
		SUBCASE("")
		{
			// Input data
			D2SeedStrc moo_pSeed{};
			D2MonRegDataStrc moo_pMonRegData{};
			D2SeedStrc original_pSeed{};
			D2MonRegDataStrc original_pMonRegData{};
			int32_t nCount{};

			const auto setup_data = [](
				D2SeedStrc& pSeed,
				D2MonRegDataStrc& pMonRegData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSeed, moo_pMonRegData);
			setup_data(original_pSeed, original_pMonRegData);

			// Call both implementations
			sut(&moo_pSeed, &moo_pMonRegData, nCount);
			original(&original_pSeed, &original_pMonRegData, nCount);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
			SKIP_MOO_CHECK_EQ(moo_pMonRegData, original_pMonRegData, "Comparing pMonRegData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERCHOOSE_GetPresetMonsterId, dll_base + 0x00032420);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2MonsterRegionStrc moo_pMonsterRegion{};
			D2ActiveRoomStrc moo_pRoom{};
			D2MonStatsTxt* moo_ppMonStatsTxtRecord{};
			D2GameStrc original_pGame{};
			D2MonsterRegionStrc original_pMonsterRegion{};
			D2ActiveRoomStrc original_pRoom{};
			D2MonStatsTxt* original_ppMonStatsTxtRecord{};
			uint8_t nChance{};
			int32_t bSpawnUMon{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2MonsterRegionStrc& pMonsterRegion,
				D2ActiveRoomStrc& pRoom,
				D2MonStatsTxt*& ppMonStatsTxtRecord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMonsterRegion, moo_pRoom, moo_ppMonStatsTxtRecord);
			setup_data(original_pGame, original_pMonsterRegion, original_pRoom, original_ppMonStatsTxtRecord);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pMonsterRegion, &moo_pRoom, &moo_ppMonStatsTxtRecord, nChance, bSpawnUMon);
			auto original_result = original(&original_pGame, &original_pMonsterRegion, &original_pRoom, &original_ppMonStatsTxtRecord, nChance, bSpawnUMon);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonsterRegion, original_pMonsterRegion, "Comparing pMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_ppMonStatsTxtRecord, original_ppMonStatsTxtRecord, "Comparing ppMonStatsTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC62640, dll_base + 0x00032640);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			auto moo_result = sut(&moo_pRoom);
			auto original_result = original(&original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERCHOOSE_GetBossSpawnType, dll_base + 0x00032670);
		
		SUBCASE("")
		{
			// Input data
			D2MonsterRegionStrc moo_pMonsterRegion{};
			D2ActiveRoomStrc moo_pRoom{};
			D2MonsterRegionStrc original_pMonsterRegion{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2MonsterRegionStrc& pMonsterRegion,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonsterRegion, moo_pRoom);
			setup_data(original_pMonsterRegion, original_pRoom);

			// Call both implementations
			auto moo_result = sut(&moo_pMonsterRegion, &moo_pRoom);
			auto original_result = original(&original_pMonsterRegion, &original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonsterRegion, original_pMonsterRegion, "Comparing pMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
}
