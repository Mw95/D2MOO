#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2StatList.h>
#include <DataTbls/SkillsTbls.h>
#include <GAME/Game.h>
#include <SKILLS/SkillAss.h>
#include <SKILLS/Skills.h>
#include <Units/Units.h>


TEST_SUITE("SkillAssTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF5090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt22_PsychicHammer, dll_base + 0x000C5090);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF50E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo033_PsychicHammer, dll_base + 0x000C50E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF52C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt23_AssasinChargeStrikes, dll_base + 0x000C52C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF52E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_StatRemoveCallback_ProgressiveStrike, dll_base + 0x000C52E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF52F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo034_TigerStrike_CobraStrike_RoyalStrike, dll_base + 0x000C52F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF55B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo035_FistsOfFire_ClawsOfThunder_BladesOfIce, dll_base + 0x000C55B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF5680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF5680, dll_base + 0x000C5680);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF5870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF5870, dll_base + 0x000C5870);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF5B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkillsTxtRecord, dll_base + 0x000C5B90);
		
		SUBCASE("")
		{
			int32_t nSkillId{};

			// Call both implementations
			auto moo_result = sut(nSkillId);
			auto original_result = original(nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF5BC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF5BC0, dll_base + 0x000C5BC0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListStrc moo_pStatList{};
			D2DamageStrc moo_pDamage{};
			D2UnitStrc original_pUnit{};
			D2StatListStrc original_pStatList{};
			D2DamageStrc original_pDamage{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListStrc& pStatList,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pStatList, moo_pDamage);
			setup_data(original_pUnit, original_pStatList, original_pDamage);

			// Call both implementations
			sut(&moo_pUnit, &moo_pStatList, &moo_pDamage);
			original(&original_pUnit, &original_pStatList, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF5DE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF5DE0, dll_base + 0x000C5DE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF5E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetProgressiveSkillMissileId, dll_base + 0x000C5E20);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nSkillId);
			auto original_result = original(&original_pUnit, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF5EE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_EvaluateProgressiveSkillCalc, dll_base + 0x000C5EE0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel);
			auto original_result = original(&original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF6000" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo038_FistsOfFire_BladesOfIce_ProgressiveFn2, dll_base + 0x000C6000);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF6140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo039_FistsOfFire_BladesOfIce_ProgressiveFn3, dll_base + 0x000C6140);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF6420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo036_ClawsOfThunder_ProgressiveFn2, dll_base + 0x000C6420);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF6500" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo037_ClawsOfThunder_ProgressiveFn3, dll_base + 0x000C6500);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF6600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF6600, dll_base + 0x000C6600);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nLowSeed{};
			int32_t nMissileId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nStep{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nLowSeed, nMissileId, nX, nY, nSkillId, nSkillLevel, nStep);
			original(&original_pGame, &original_pUnit, nLowSeed, nMissileId, nX, nY, nSkillId, nSkillLevel, nStep);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF6C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF6C10, dll_base + 0x000C6C10);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			int32_t nLowSeed{};

			const auto setup_data = [](
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			sut(&moo_pMissile, nLowSeed);
			original(&original_pMissile, nLowSeed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF6C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo143_FistsOfFire_RoyalStrike_ProgressiveFn, dll_base + 0x000C6C70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF6D70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF6D70, dll_base + 0x000C6D70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nLowSeed{};
			int32_t nMissileId{};
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nStep{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nLowSeed, nMissileId, nX, nY, nSkillId, nSkillLevel, nStep);
			original(&original_pGame, &original_pUnit, nLowSeed, nMissileId, nX, nY, nSkillId, nSkillLevel, nStep);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF7390" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF7390, dll_base + 0x000C7390);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMissile{};
			D2UnitStrc original_pMissile{};
			int32_t nInitSeed{};

			const auto setup_data = [](
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMissile);
			setup_data(original_pMissile);

			// Call both implementations
			sut(&moo_pMissile, nInitSeed);
			original(&original_pMissile, nInitSeed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF7590" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo040_RoyalStrike_ProgressiveFn1, dll_base + 0x000C7590);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF7610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo041_RoyalStrike_ProgressiveFn3, dll_base + 0x000C7610);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF77E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF77E0, dll_base + 0x000C77E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pDamage);
			setup_data(original_pGame, original_pUnit, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF7AD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt24_DragonTalon, dll_base + 0x000C7AD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF7CE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF7CE0, dll_base + 0x000C7CE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2DamageStrc moo_pDamage{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2DamageStrc original_pDamage{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2DamageStrc& pDamage,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pDamage, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pDamage, original_pUnit, original_pTarget);

			// Call both implementations
			sut(&moo_pGame, &moo_pDamage, &moo_pUnit, &moo_pTarget, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pDamage, &original_pUnit, &original_pTarget, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8110" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo042_DragonTalon, dll_base + 0x000C8110);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8330" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF8330, dll_base + 0x000C8330);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMissile{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMissile{};
			D2UnitStrc original_pUnit{};
			int32_t nMissileId{};
			int32_t nSubMissiles{};
			int32_t nRange{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMissile,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMissile, moo_pUnit);
			setup_data(original_pGame, original_pMissile, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit, nMissileId, nSubMissiles, nRange, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit, nMissileId, nSubMissiles, nRange, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo043_ShockField, dll_base + 0x000C8550);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF8610, dll_base + 0x000C8610);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2SkillsTxt moo_pSkillsTxtRecord{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2SkillsTxt original_pSkillsTxtRecord{};
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2SkillsTxt& pSkillsTxtRecord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pSkillsTxtRecord);
			setup_data(original_pGame, original_pUnit, original_pSkillsTxtRecord);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY, &moo_pSkillsTxtRecord, nSkillId, nSkillLevel);
			auto original_result = original(&original_pGame, &original_pUnit, nX, nY, &original_pSkillsTxtRecord, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSkillsTxtRecord, original_pSkillsTxtRecord, "Comparing pSkillsTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF88E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo044_BladeSentinel, dll_base + 0x000C88E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8B00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo045_Sentry, dll_base + 0x000C8B00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo046_DragonClaw, dll_base + 0x000C8BA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF8C70, dll_base + 0x000C8C70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nSkillId{};
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
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, &original_pTarget, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8DD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF8DD0, dll_base + 0x000C8DD0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pDefender{};
			D2UnitStrc original_pDefender{};

			const auto setup_data = [](
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDefender);
			setup_data(original_pDefender);

			// Call both implementations
			sut(&moo_pDefender);
			original(&original_pDefender);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF8ED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo047_CloakOfShadows, dll_base + 0x000C8ED0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_AuraCallback_CloakOfShadows, dll_base + 0x000C9160);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo048_BladeFury, dll_base + 0x000C9260);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF93B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt26_BladeFury, dll_base + 0x000C93B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_StatRemoveCallback_RemoveState, dll_base + 0x000C9550);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF9580, dll_base + 0x000C9580);
		
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
			int32_t bCheckOnInit{};

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
			sut(&moo_pGame, &moo_pUnit, &moo_pPet, nSkillId, nSkillLevel, nItemLevel, bCheckOnInit);
			original(&original_pGame, &original_pUnit, &original_pPet, nSkillId, nSkillLevel, nItemLevel, bCheckOnInit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPet, original_pPet, "Comparing pPet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo049_ShadowWarrior_Master, dll_base + 0x000C9750);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9B50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt27_DragonTail, dll_base + 0x000C9B50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo050_DragonTail, dll_base + 0x000C9C70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9EA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_StatRemoveCallback_MindBlast, dll_base + 0x000C9EA0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2StatListStrc moo_pStatList{};
			D2UnitStrc original_pItem{};
			D2StatListStrc original_pStatList{};
			int32_t nState{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pStatList);
			setup_data(original_pItem, original_pStatList);

			// Call both implementations
			sut(&moo_pItem, nState, &moo_pStatList);
			original(&original_pItem, nState, &original_pStatList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF9FF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_AuraCallback_MindBlast, dll_base + 0x000C9FF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCFA350" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo051_MindBlast, dll_base + 0x000CA350);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCFA4F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo052_DragonFlight, dll_base + 0x000CA4F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCFA720" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt28_BladeShield, dll_base + 0x000CA720);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCFA880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo053_Unused, dll_base + 0x000CA880);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCFA980" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_AuraCallback_SrvDo142, dll_base + 0x000CA980);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCFAA20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo142_Unused, dll_base + 0x000CAA20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCFAB60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo054_BladeShield, dll_base + 0x000CAB60);
		
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
}
