#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <MONSTER/Monster.h>
#include <Units/Units.h>


TEST_SUITE("MonsterTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC601C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_SetAiState, dll_base + 0x000301C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();
			int32_t nAiState{};

			// Call both implementations
			sut(&moo_pMonster, nAiState);
			original(&original_pMonster, nAiState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC601E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_GetAiState, dll_base + 0x000301E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster);
			const auto original_result = original(&original_pMonster);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60200" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_SetLevelId, dll_base + 0x00030200);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();
			int32_t nLevelId{};

			// Call both implementations
			sut(&moo_pMonster, nLevelId);
			original(&original_pMonster, nLevelId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_GetLevelId, dll_base + 0x00030220);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster);
			const auto original_result = original(&original_pMonster);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_CheckSummonerFlag, dll_base + 0x00030240);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();
			uint16_t nFlag{};

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster, nFlag);
			const auto original_result = original(&original_pMonster, nFlag);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_ToggleSummonerFlag, dll_base + 0x00030270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();
			uint16_t nFlag{};
			int32_t bSet{};

			// Call both implementations
			sut(&moo_pMonster, nFlag, bSet);
			original(&original_pMonster, nFlag, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC602A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_Initialize, dll_base + 0x000302A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2UnitStrc pMonster{};
				
				return std::tuple{ pGame, pRoom, pMonster };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pMonster] = setup_data();
			auto [original_pGame, original_pRoom, original_pMonster] = setup_data();
			int32_t nUnitGUID{};

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pMonster, nUnitGUID);
			original(&original_pGame, &original_pRoom, &original_pMonster, nUnitGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC603D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_InitializeStatsAndSkills, dll_base + 0x000303D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2UnitStrc pUnit{};
				D2MonRegDataStrc pMonRegData{};
				
				return std::tuple{ pGame, pRoom, pUnit, pMonRegData };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pUnit, moo_pMonRegData] = setup_data();
			auto [original_pGame, original_pRoom, original_pUnit, original_pMonRegData] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pUnit, &moo_pMonRegData);
			original(&original_pGame, &original_pRoom, &original_pUnit, &original_pMonRegData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMonRegData, original_pMonRegData, "Comparing pMonRegData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60B10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_SetVelocityAndPosition, dll_base + 0x00030B10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				
				return std::tuple{ pGame, pMonster };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster] = setup_data();
			auto [original_pGame, original_pMonster] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMonster, nX, nY, a5);
			const auto original_result = original(&original_pGame, &original_pMonster, nX, nY, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60BC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_RemoveAll, dll_base + 0x00030BC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_Free, dll_base + 0x00030C10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				
				return std::tuple{ pGame, pMonster };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster] = setup_data();
			auto [original_pGame, original_pMonster] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster);
			original(&original_pGame, &original_pMonster);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_UpdateAiCallbackEvent, dll_base + 0x00030CD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				
				return std::tuple{ pGame, pMonster };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster] = setup_data();
			auto [original_pGame, original_pMonster] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster);
			original(&original_pGame, &original_pMonster);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60E50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_DeleteEvents, dll_base + 0x00030E50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				
				return std::tuple{ pGame, pMonster };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster] = setup_data();
			auto [original_pGame, original_pMonster] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster);
			original(&original_pGame, &original_pMonster);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60E70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_GetHpBonus, dll_base + 0x00030E70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nPlayerCount{};

			// Call both implementations
			const auto moo_result = sut(nPlayerCount);
			const auto original_result = original(nPlayerCount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "Inlined in D2Game.0x6FC60E90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_GetExperienceBonus, dll_base + 0x00030E90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nPlayerCount{};

			// Call both implementations
			const auto moo_result = sut(nPlayerCount);
			const auto original_result = original(nPlayerCount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60E90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_GetPlayerCountBonus, dll_base + 0x00030E90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2PlayerCountBonusStrc pPlayerCountBonus{};
				D2ActiveRoomStrc pRoom{};
				D2UnitStrc pMonster{};
				
				return std::tuple{ pGame, pPlayerCountBonus, pRoom, pMonster };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayerCountBonus, moo_pRoom, moo_pMonster] = setup_data();
			auto [original_pGame, original_pPlayerCountBonus, original_pRoom, original_pMonster] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayerCountBonus, &moo_pRoom, &moo_pMonster);
			original(&original_pGame, &original_pPlayerCountBonus, &original_pRoom, &original_pMonster);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayerCountBonus, original_pPlayerCountBonus, "Comparing pPlayerCountBonus");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_SetComponents, dll_base + 0x00030F70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MonRegDataStrc pMonRegData{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pMonRegData, pUnit };
			};
			
			// Input data
			auto [moo_pMonRegData, moo_pUnit] = setup_data();
			auto [original_pMonRegData, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pMonRegData, &moo_pUnit);
			original(&original_pMonRegData, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonRegData, original_pMonRegData, "Comparing pMonRegData");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC610C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_HasComponents, dll_base + 0x000310C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster);
			const auto original_result = original(&original_pMonster);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC610F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_Reinitialize, dll_base + 0x000310F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nClassId{};
			int32_t nMode{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nClassId, nMode);
			const auto original_result = original(&original_pGame, &original_pUnit, nClassId, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
