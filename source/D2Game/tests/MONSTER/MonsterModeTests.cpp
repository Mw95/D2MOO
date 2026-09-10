#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pAttacker{};
				D2UnitStrc pDefender{};
				D2GameStrc pGame{};
				
				return std::tuple{ pAttacker, pDefender, pGame };
			};
			
			// Input data
			auto [moo_pAttacker, moo_pDefender, moo_pGame] = setup_data();
			auto [original_pAttacker, original_pDefender, original_pGame] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();
			int32_t nMode{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2GameStrc pGame{};
				
				return std::tuple{ pUnit, pGame };
			};
			
			// Input data
			auto [moo_pUnit, moo_pGame] = setup_data();
			auto [original_pUnit, original_pGame] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pUnit, original_pDamage] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pAttacker{};
				D2UnitStrc pDefender{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pAttacker, pDefender, pDamage };
			};
			
			// Input data
			auto [moo_pAttacker, moo_pDefender, moo_pDamage] = setup_data();
			auto [original_pAttacker, original_pDefender, original_pDamage] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2AiParamStrc pAiParam{};
				
				return std::tuple{ pAiParam };
			};
			
			// Input data
			auto [moo_pAiParam] = setup_data();
			auto [original_pAiParam] = setup_data();
			int32_t a2{};
			int32_t nVel{};
			uint8_t a4{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame);
			const auto original_result = original(&original_pGame);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2AiParamStrc pAiParam{};
				
				return std::tuple{ pGame, pAiParam };
			};
			
			// Input data
			auto [moo_pGame, moo_pAiParam] = setup_data();
			auto [original_pGame, original_pAiParam] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();
			int32_t a3{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pUnit, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pUnit, original_pModeChange] = setup_data();
			int32_t a7{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t a3{};
			int32_t a4{};

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
			// TODO: Setup as needed
			int32_t nMonsterId{};

			// Call both implementations
			const auto moo_result = sut(nMonsterId);
			const auto original_result = original(nMonsterId);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			const auto moo_result = sut(&moo_pGame, &moo_pMonster);
			const auto original_result = original(&original_pGame, &original_pMonster);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			DWORD dwDir{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				
				return std::tuple{ pGame, pAttacker };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker] = setup_data();
			auto [original_pGame, original_pAttacker] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				
				return std::tuple{ pGame, pAttacker };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker] = setup_data();
			auto [original_pGame, original_pAttacker] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange);
			const auto original_result = original(&original_pGame, &original_pModeChange);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();
			int32_t nMode{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nMode);
			const auto original_result = original(&original_pUnit, nMode);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t a3{};
			int32_t a4{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t a3{};
			int32_t a4{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pGame, pModeChange };
			};
			
			// Input data
			auto [moo_pGame, moo_pModeChange] = setup_data();
			auto [original_pGame, original_pModeChange] = setup_data();
			int32_t a3{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pModeChange, a3);
			const auto original_result = original(&original_pGame, &original_pModeChange, a3);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2AiParamStrc pAiParam{};
				
				return std::tuple{ pUnit, pAiParam };
			};
			
			// Input data
			auto [moo_pUnit, moo_pAiParam] = setup_data();
			auto [original_pUnit, original_pAiParam] = setup_data();
			int32_t nPathType{};
			int32_t dwNewDist{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nPathType, &moo_pAiParam, dwNewDist);
			const auto original_result = original(&original_pUnit, nPathType, &original_pAiParam, dwNewDist);
			
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2ModeChangeStrc pModeChange{};
				
				return std::tuple{ pUnit, pModeChange };
			};
			
			// Input data
			auto [moo_pUnit, moo_pModeChange] = setup_data();
			auto [original_pUnit, original_pModeChange] = setup_data();
			int32_t nMode{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t a3{};
			int32_t a4{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t a3{};
			int32_t a4{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t a3{};
			int32_t a4{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			D2C_EventTypes nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pTarget] = setup_data();
			int32_t a4{};

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
