#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2StatList.h>
#include <GAME/Game.h>
#include <SKILLS/SkillNec.h>
#include <SKILLS/Skills.h>
#include <Units/Units.h>


TEST_SUITE("SkillNecTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0AF30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt15_RaiseSkeleton_Mage, dll_base + 0x000DAF30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0AF70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt16_PoisonDagger, dll_base + 0x000DAF70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B0B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt17_Poison_CorpseExplosion, dll_base + 0x000DB0B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B0F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt19_BonePrison, dll_base + 0x000DB0F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt20_IronGolem, dll_base + 0x000DB120);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt21_Revive, dll_base + 0x000DB190);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0B250, dll_base + 0x000DB250);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B2B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0B2B0, dll_base + 0x000DB2B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0B3D0, dll_base + 0x000DB3D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nStatId{};
			int32_t nResist{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nStatId, nResist);
			auto original_result = original(&original_pUnit, nStatId, nResist);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0B450, dll_base + 0x000DB450);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, moo_pArgs);
			auto original_result = original(&original_pUnit, original_pArgs);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo030_Curse, dll_base + 0x000DB790);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0B9F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0B9F0, dll_base + 0x000DB9F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nSkillLevel{};

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
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nSkillLevel);
			original(&original_pGame, &original_pUnit, &original_pTarget, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0BB60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo059_Attract, dll_base + 0x000DBB60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0BDA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0BDA0, dll_base + 0x000DBDA0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, moo_pArg);
			auto original_result = original(&original_pUnit, original_pArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0BE50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo061_Confuse, dll_base + 0x000DBE50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0C060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0C060, dll_base + 0x000DC060);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, moo_pArg);
			auto original_result = original(&original_pUnit, original_pArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0C2B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0C2B0, dll_base + 0x000DC2B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0C2E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetSummonResistance_6FD0C2E0, dll_base + 0x000DC2E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pPet{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pPet{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pPet
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pPet);
			setup_data(original_pUnit, original_pPet);

			// Call both implementations
			sut(&moo_pUnit, &moo_pPet);
			original(&original_pUnit, &original_pPet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPet, original_pPet, "Comparing pPet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0C3A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetUnitComponent_6FD0C3A0, dll_base + 0x000DC3A0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pPet{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pPet{};
			int32_t nLevel{};
			int32_t bHasShield{};
			int32_t bSpecial{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pPet
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pPet);
			setup_data(original_pUnit, original_pPet);

			// Call both implementations
			sut(&moo_pUnit, &moo_pPet, nLevel, bHasShield, bSpecial);
			original(&original_pUnit, &original_pPet, nLevel, bHasShield, bSpecial);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPet, original_pPet, "Comparing pPet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0C500" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0C500, dll_base + 0x000DC500);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};
			uint8_t nIndex{};
			uint8_t nComponent{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

			// Call both implementations
			sut(&moo_pMonster, nIndex, nComponent);
			original(&original_pMonster, nIndex, nComponent);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0C530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetSummonPassiveStats_6FD0C530, dll_base + 0x000DC530);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pPet{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pPet{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nItemLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pPet
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pPet);
			setup_data(original_pGame, original_pUnit, original_pPet);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pPet, nSkillId, nSkillLevel, nItemLevel);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pPet, nSkillId, nSkillLevel, nItemLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPet, original_pPet, "Comparing pPet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0CB10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SKILLS_SetSummonBaseStats_6FD0CB10, dll_base + 0x000DCB10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pPet{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pPet{};
			int32_t nPetLevelArg{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pPet
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pPet);
			setup_data(original_pGame, original_pUnit, original_pPet);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pPet, nPetLevelArg, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pPet, nPetLevelArg, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPet, original_pPet, "Comparing pPet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0CC10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo031_RaiseSkeleton_Mage, dll_base + 0x000DCC10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0CFC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo032_PoisonDagger, dll_base + 0x000DCFC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0D000" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0D000, dll_base + 0x000DD000);
		
		SUBCASE("")
		{
			// Input data
			D2AuraCallbackStrc moo_pAuraCallback{};
			D2UnitStrc moo_pUnit{};
			D2AuraCallbackStrc original_pAuraCallback{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2AuraCallbackStrc& pAuraCallback,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAuraCallback, moo_pUnit);
			setup_data(original_pAuraCallback, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pAuraCallback, &moo_pUnit);
			auto original_result = original(&original_pAuraCallback, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAuraCallback, original_pAuraCallback, "Comparing pAuraCallback");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0D0D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo055_CorpseExplosion, dll_base + 0x000DD0D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0D620" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo056_Golem, dll_base + 0x000DD620);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0D7B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo057_IronGolem, dll_base + 0x000DD7B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0DAC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo058_Revive, dll_base + 0x000DDAC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0DF40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0DF40, dll_base + 0x000DDF40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pMonster{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pMonster{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pMonster);
			setup_data(original_pGame, original_pUnit, original_pMonster);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pMonster, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, &original_pMonster, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0E050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo060_BoneWall, dll_base + 0x000DE050);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0E4C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo062_BonePrison, dll_base + 0x000DE4C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0E790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo063_PoisonExplosion, dll_base + 0x000DE790);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0E840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EventFunc04_6FD0E840, dll_base + 0x000DE840);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0EDE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EventFunc05_6FD0EDE0, dll_base + 0x000DEDE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0F000" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EventFunc22_6FD0F000, dll_base + 0x000DF000);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0F1F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EventFunc23_6FD0F1F0, dll_base + 0x000DF1F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0F590" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0F590, dll_base + 0x000DF590);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nValue{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nValue);
			auto original_result = original(&original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0F5E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EventFunc26_6FD0F5E0, dll_base + 0x000DF5E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0F7A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EventFunc27_6FD0F7A0, dll_base + 0x000DF7A0);
		
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
