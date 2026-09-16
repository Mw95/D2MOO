#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2StatList.h>
#include <GAME/Game.h>
#include <SKILLS/SkillSor.h>
#include <SKILLS/Skills.h>
#include <Units/Units.h>


TEST_SUITE("SkillSorTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD156F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_DoInferno, dll_base + 0x000E56F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nMissileId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel, nMissileId);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel, nMissileId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_StartInferno, dll_base + 0x000E5940);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel, a5);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt11_Inferno_ArcticBlast, dll_base + 0x000E5AB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15B40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt12_Telekinesis_DragonFlight, dll_base + 0x000E5B40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15CF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt13_ThunderStorm, dll_base + 0x000E5CF0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15D50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt14_Hydra, dll_base + 0x000E5D50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15E50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_MissileInit_ChargedBolt, dll_base + 0x000E5E50);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			int32_t a2{};

			const auto setup_data = [](
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			sut(&moo_pMissile, a2);
			original(&original_pMissile, a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15EB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo017_ChargedBolt_BoltSentry, dll_base + 0x000E5EB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD16040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CurseStateCallback_DefensiveBuff, dll_base + 0x000E6040);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListStrc moo_pStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListStrc original_pStatList{};
			int32_t nState{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pStatList);
			setup_data(original_pUnit, original_pStatList);

			// Call both implementations
			sut(&moo_pUnit, nState, &moo_pStatList);
			original(&original_pUnit, nState, &original_pStatList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD160A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo018_DefensiveBuff, dll_base + 0x000E60A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD16270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo019_Inferno_ArcticBlast, dll_base + 0x000E6270);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD162D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo020_StaticField, dll_base + 0x000E62D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD163E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_AuraCallback_StaticField, dll_base + 0x000E63E0);
		
		SUBCASE("")
		{
			// Input data
			D2AuraCallbackStrc moo_pAuraCallback{};
			D2UnitStrc moo_pDefender{};
			D2AuraCallbackStrc original_pAuraCallback{};
			D2UnitStrc original_pDefender{};

			const auto setup_data = [](
				D2AuraCallbackStrc& pAuraCallback,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAuraCallback, moo_pDefender);
			setup_data(original_pAuraCallback, original_pDefender);

			// Call both implementations
			auto moo_result = sut(&moo_pAuraCallback, &moo_pDefender);
			auto original_result = original(&original_pAuraCallback, &original_pDefender);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAuraCallback, original_pAuraCallback, "Comparing pAuraCallback");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD166A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo021_Telekinesis, dll_base + 0x000E66A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD169A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo022_NovaAttack, dll_base + 0x000E69A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD16A60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo023_Blaze_EnergyShield_SpiderLay, dll_base + 0x000E6A60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD16C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CreateBlazeMissile, dll_base + 0x000E6C00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD16D70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo024_FireWall, dll_base + 0x000E6D70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD17040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo025_Enchant, dll_base + 0x000E7040);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD17200" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo026_ChainLightning, dll_base + 0x000E7200);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD172B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo151_Unused, dll_base + 0x000E72B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD17450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo027_Teleport, dll_base + 0x000E7450);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD174E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo028_Meteor_Blizzard_Eruption_BaalTaunt_Catapult, dll_base + 0x000E74E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD17570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo029_ThunderStorm, dll_base + 0x000E7570);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD17820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_EventFunc24_EnergyShield, dll_base + 0x000E7820);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pUnit, original_pDamage);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD17C30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo144_Hydra, dll_base + 0x000E7C30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD17F40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_EventFunc01_ChillingArmor, dll_base + 0x000E7F40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pUnit, original_pDamage);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD180E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_EventFunc02_FrozenArmor, dll_base + 0x000E80E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pUnit, original_pDamage);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD18200" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_EventFunc03_ShiverArmor, dll_base + 0x000E8200);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nEvent{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pUnit, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pUnit, original_pDamage);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, nEvent, &moo_pAttacker, &moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, nEvent, &original_pAttacker, &original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
}
