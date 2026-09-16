#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <AI/AiGeneral.h>
#include <GAME/Game.h>
#include <MONSTER/MonsterMode.h>
#include <Units/Units.h>


TEST_SUITE("MonsterModeTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62770" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_IsMonster_6FC62770, dll_base + 0x00032770);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit);
			auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC62780, dll_base + 0x00032780);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender, moo_pGame);
			setup_data(original_pAttacker, original_pDefender, original_pGame);

			// Call both implementations
			sut(&moo_pAttacker, &moo_pDefender, &moo_pGame);
			original(&original_pAttacker, &original_pDefender, &original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC627B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC627B0, dll_base + 0x000327B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nMode{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nMode);
			original(&original_pUnit, nMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62D90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC62D90, dll_base + 0x00032D90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pUnit{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pGame);
			setup_data(original_pUnit, original_pGame);

			// Call both implementations
			sut(&moo_pUnit, &moo_pGame);
			original(&original_pUnit, &original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62DF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC62DF0, dll_base + 0x00032DF0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pDamage);
			setup_data(original_pUnit, original_pDamage);

			// Call both implementations
			sut(&moo_pUnit, &moo_pDamage);
			original(&original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62E70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTER_ApplyCriticalDamage_6FC62E70, dll_base + 0x00032E70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2DamageStrc moo_pDamage{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			D2DamageStrc original_pDamage{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender, moo_pDamage);
			setup_data(original_pAttacker, original_pDefender, original_pDamage);

			// Call both implementations
			sut(&moo_pAttacker, &moo_pDefender, &moo_pDamage);
			original(&original_pAttacker, &original_pDefender, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62F50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC62F50, dll_base + 0x00032F50);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit);
			auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62F90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERMODE_ResetVelocityParams_6FC62F90, dll_base + 0x00032F90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62FC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERMODE_SetVelocityParams_6FC62FC0, dll_base + 0x00032FC0);
		
		SUBCASE("")
		{
			// Input data
			D2AiParamStrc moo_pAiParam{};
			D2AiParamStrc original_pAiParam{};
			int32_t a2{};
			int32_t nVel{};
			uint8_t a4{};

			const auto setup_data = [](
				D2AiParamStrc& pAiParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAiParam);
			setup_data(original_pAiParam);

			// Call both implementations
			sut(&moo_pAiParam, a2, nVel, a4);
			original(&original_pAiParam, a2, nVel, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAiParam, original_pAiParam, "Comparing pAiParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC62FF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERMODE_AllocParams_6FC62FF0, dll_base + 0x00032FF0);
		
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
			auto moo_result = sut(&moo_pGame);
			auto original_result = original(&original_pGame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERMODE_FreeParams_6FC63020, dll_base + 0x00033020);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2AiParamStrc moo_pAiParam{};
			D2GameStrc original_pGame{};
			D2AiParamStrc original_pAiParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2AiParamStrc& pAiParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAiParam);
			setup_data(original_pGame, original_pAiParam);

			// Call both implementations
			sut(&moo_pGame, &moo_pAiParam);
			original(&original_pGame, &original_pAiParam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAiParam, original_pAiParam, "Comparing pAiParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERMODE_Unk_6FC63040, dll_base + 0x00033040);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			sut(&moo_pGame, &moo_pModeChange, a3);
			original(&original_pGame, &original_pModeChange, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC631B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC631B0, dll_base + 0x000331B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2ModeChangeStrc original_pModeChange{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pModeChange);
			setup_data(original_pGame, original_pUnit, original_pModeChange);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a7, &moo_pModeChange);
			original(&original_pGame, &original_pUnit, a7, &original_pModeChange);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTER_ApplyStatRegen_6FC63440, dll_base + 0x00033440);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, a4);
			original(&original_pGame, &original_pUnit, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63650" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERMODE_GetMonStatsTxtRecord, dll_base + 0x00033650);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC63680, dll_base + 0x00033680);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC63940, dll_base + 0x00033940);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63A30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC63A30, dll_base + 0x00033A30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RemoveModeChangeEventCallback_6FC63B20, dll_base + 0x00033B20);
		
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
			auto moo_result = sut(&moo_pGame, &moo_pMonster);
			auto original_result = original(&original_pGame, &original_pMonster);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63B30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC63B30, dll_base + 0x00033B30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC63E80, dll_base + 0x00033E80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			DWORD dwDir{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, dwDir);
			original(&original_pGame, &original_pUnit, dwDir);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC63FD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC63FD0, dll_base + 0x00033FD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker);
			setup_data(original_pGame, original_pAttacker);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker);
			original(&original_pGame, &original_pAttacker);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64090, dll_base + 0x00034090);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC641D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC641D0, dll_base + 0x000341D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker);
			setup_data(original_pGame, original_pAttacker);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker);
			original(&original_pGame, &original_pAttacker);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64280, dll_base + 0x00034280);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC642C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC642C0, dll_base + 0x000342C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64310, dll_base + 0x00034310);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC643D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC643D0, dll_base + 0x000343D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC643E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC643E0, dll_base + 0x000343E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64410, dll_base + 0x00034410);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64450, dll_base + 0x00034450);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64480, dll_base + 0x00034480);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC644E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC644E0, dll_base + 0x000344E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64510" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64510, dll_base + 0x00034510);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64540, dll_base + 0x00034540);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC645E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC645E0, dll_base + 0x000345E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64790, dll_base + 0x00034790);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64B10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetMonsterBaseId_6FC64B10, dll_base + 0x00034B10);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit);
			auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64B50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64B50, dll_base + 0x00034B50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64B60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64B60, dll_base + 0x00034B60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64CD0, dll_base + 0x00034CD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64E20, dll_base + 0x00034E20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64E60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64E60, dll_base + 0x00034E60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			auto original_result = original(&original_pGame, &original_pModeChange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64E90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC64E90, dll_base + 0x00034E90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC64F50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERMODE_GetCallbackTableRecord, dll_base + 0x00034F50);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nMode{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nMode);
			auto original_result = original(&original_pUnit, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction01_6FC65080, dll_base + 0x00035080);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, a4);
			original(&original_pGame, &original_pUnit, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65150" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction02_6FC65150, dll_base + 0x00035150);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, a4);
			original(&original_pGame, &original_pUnit, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ModeChange_6FC65220, dll_base + 0x00035220);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ModeChangeStrc moo_pModeChange{};
			D2GameStrc original_pGame{};
			D2ModeChangeStrc original_pModeChange{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pModeChange);
			setup_data(original_pGame, original_pModeChange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pModeChange, a3);
			auto original_result = original(&original_pGame, &original_pModeChange, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC65680, dll_base + 0x00035680);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2AiParamStrc moo_pAiParam{};
			D2UnitStrc original_pUnit{};
			D2AiParamStrc original_pAiParam{};
			int32_t nPathType{};
			int32_t dwNewDist{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2AiParamStrc& pAiParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pAiParam);
			setup_data(original_pUnit, original_pAiParam);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nPathType, &moo_pAiParam, dwNewDist);
			auto original_result = original(&original_pUnit, nPathType, &original_pAiParam, dwNewDist);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiParam, original_pAiParam, "Comparing pAiParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERMODE_GetModeChangeInfo, dll_base + 0x00035780);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ModeChangeStrc moo_pModeChange{};
			D2UnitStrc original_pUnit{};
			D2ModeChangeStrc original_pModeChange{};
			int32_t nMode{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2ModeChangeStrc& pModeChange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pModeChange);
			setup_data(original_pUnit, original_pModeChange);

			// Call both implementations
			sut(&moo_pUnit, nMode, &moo_pModeChange);
			original(&original_pUnit, nMode, &original_pModeChange);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pModeChange, original_pModeChange, "Comparing pModeChange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction13_6FC65890, dll_base + 0x00035890);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, a4);
			original(&original_pGame, &original_pUnit, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC658B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction07_6FC658B0, dll_base + 0x000358B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, a4);
			original(&original_pGame, &original_pUnit, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65920" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction11_6FC65920, dll_base + 0x00035920);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, a4);
			original(&original_pGame, &original_pUnit, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERMODE_EventHandler, dll_base + 0x00035930);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2C_EventTypes nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEvent, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, nEvent, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC659B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC659B0, dll_base + 0x000359B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, a4);
			original(&original_pGame, &original_pUnit, &original_pTarget, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
}
