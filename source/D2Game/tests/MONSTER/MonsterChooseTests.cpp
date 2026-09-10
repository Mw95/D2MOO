#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2SeedStrc pSeed{};
				D2MonRegDataStrc pMonRegData{};
				
				return std::tuple{ pSeed, pMonRegData };
			};
			
			// Input data
			auto [moo_pSeed, moo_pMonRegData] = setup_data();
			auto [original_pSeed, original_pMonRegData] = setup_data();
			int32_t nCount{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2MonsterRegionStrc pMonsterRegion{};
				D2ActiveRoomStrc pRoom{};
				D2MonStatsTxt* ppMonStatsTxtRecord{};
				
				return std::tuple{ pGame, pMonsterRegion, pRoom, ppMonStatsTxtRecord };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonsterRegion, moo_pRoom, moo_ppMonStatsTxtRecord] = setup_data();
			auto [original_pGame, original_pMonsterRegion, original_pRoom, original_ppMonStatsTxtRecord] = setup_data();
			uint8_t nChance{};
			int32_t bSpawnUMon{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMonsterRegion, &moo_pRoom, &moo_ppMonStatsTxtRecord, nChance, bSpawnUMon);
			const auto original_result = original(&original_pGame, &original_pMonsterRegion, &original_pRoom, &original_ppMonStatsTxtRecord, nChance, bSpawnUMon);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom);
			const auto original_result = original(&original_pRoom);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MonsterRegionStrc pMonsterRegion{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pMonsterRegion, pRoom };
			};
			
			// Input data
			auto [moo_pMonsterRegion, moo_pRoom] = setup_data();
			auto [original_pMonsterRegion, original_pRoom] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonsterRegion, &moo_pRoom);
			const auto original_result = original(&original_pMonsterRegion, &original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonsterRegion, original_pMonsterRegion, "Comparing pMonsterRegion");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
}
