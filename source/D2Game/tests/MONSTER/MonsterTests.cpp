#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};
			int32_t nAiState{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

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
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

			// Call both implementations
			auto moo_result = sut(&moo_pMonster);
			auto original_result = original(&original_pMonster);
			
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
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};
			int32_t nLevelId{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

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
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

			// Call both implementations
			auto moo_result = sut(&moo_pMonster);
			auto original_result = original(&original_pMonster);
			
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
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};
			uint16_t nFlag{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

			// Call both implementations
			auto moo_result = sut(&moo_pMonster, nFlag);
			auto original_result = original(&original_pMonster, nFlag);
			
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
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};
			uint16_t nFlag{};
			int32_t bSet{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pMonster{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pMonster{};
			int32_t nUnitGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pMonster);
			setup_data(original_pGame, original_pRoom, original_pMonster);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pUnit{};
			D2MonRegDataStrc moo_pMonRegData{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pUnit{};
			D2MonRegDataStrc original_pMonRegData{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pUnit,
				D2MonRegDataStrc& pMonRegData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pUnit, moo_pMonRegData);
			setup_data(original_pGame, original_pRoom, original_pUnit, original_pMonRegData);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMonster{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMonster{};
			int32_t nX{};
			int32_t nY{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMonster);
			setup_data(original_pGame, original_pMonster);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pMonster, nX, nY, a5);
			auto original_result = original(&original_pGame, &original_pMonster, nX, nY, a5);
			
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTER_Free, dll_base + 0x00030C10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMonster{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMonster{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMonster);
			setup_data(original_pGame, original_pMonster);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMonster{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMonster{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMonster);
			setup_data(original_pGame, original_pMonster);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMonster{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMonster{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMonster);
			setup_data(original_pGame, original_pMonster);

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
			int32_t nPlayerCount{};

			// Call both implementations
			auto moo_result = sut(nPlayerCount);
			auto original_result = original(nPlayerCount);
			
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
			int32_t nPlayerCount{};

			// Call both implementations
			auto moo_result = sut(nPlayerCount);
			auto original_result = original(nPlayerCount);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2PlayerCountBonusStrc moo_pPlayerCountBonus{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc moo_pMonster{};
			D2GameStrc original_pGame{};
			D2PlayerCountBonusStrc original_pPlayerCountBonus{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc original_pMonster{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2PlayerCountBonusStrc& pPlayerCountBonus,
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayerCountBonus, moo_pRoom, moo_pMonster);
			setup_data(original_pGame, original_pPlayerCountBonus, original_pRoom, original_pMonster);

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
			// Input data
			D2MonRegDataStrc moo_pMonRegData{};
			D2UnitStrc moo_pUnit{};
			D2MonRegDataStrc original_pMonRegData{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2MonRegDataStrc& pMonRegData,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonRegData, moo_pUnit);
			setup_data(original_pMonRegData, original_pUnit);

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
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

			// Call both implementations
			auto moo_result = sut(&moo_pMonster);
			auto original_result = original(&original_pMonster);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nClassId{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nClassId, nMode);
			auto original_result = original(&original_pGame, &original_pUnit, nClassId, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
