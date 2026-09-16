#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2StatList.h>
#include <GAME/Game.h>
#include <UNIT/SUnitDmg.h>
#include <Units/Units.h>


TEST_SUITE("SUnitDmgTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBE2F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_SetHitClass, dll_base + 0x0008E2F0);
		
		SUBCASE("")
		{
			// Input data
			D2DamageStrc moo_pDamage{};
			D2DamageStrc original_pDamage{};
			uint32_t nHitClass{};

			const auto setup_data = [](
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDamage);
			setup_data(original_pDamage);

			// Call both implementations
			auto moo_result = sut(&moo_pDamage, nHitClass);
			auto original_result = original(&original_pDamage, nHitClass);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBE310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_GetColdEffect, dll_base + 0x0008E310);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBE360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_RemoveFreezeState, dll_base + 0x0008E360);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			struct D2StatListStrc moo_pStatList{};
			D2UnitStrc original_pUnit{};
			struct D2StatListStrc original_pStatList{};
			int32_t nState{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				struct D2StatListStrc& pStatList
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBE420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ApplyDamageBonuses, dll_base + 0x0008E420);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			int32_t bGetStats{};
			int32_t nMinDmg{};
			int32_t nMaxDmg{};
			int32_t nDamagePercent{};
			int32_t nDamage{};
			uint8_t nSrcDam{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pItem);
			setup_data(original_pUnit, original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, bGetStats, &moo_pItem, nMinDmg, nMaxDmg, nDamagePercent, nDamage, nSrcDam);
			auto original_result = original(&original_pUnit, bGetStats, &original_pItem, nMinDmg, nMaxDmg, nDamagePercent, nDamage, nSrcDam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBE7E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_FillDamageValues, dll_base + 0x0008E7E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			D2DamageStrc original_pDamage{};
			int32_t a5{};
			uint8_t nSrcDam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pDefender, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, &moo_pDamage, a5, nSrcDam);
			original(&original_pGame, &original_pAttacker, &original_pDefender, &original_pDamage, a5, nSrcDam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBF400" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_CheckMonType, dll_base + 0x0008F400);
		
		SUBCASE("")
		{
			int32_t nMonType1{};
			int32_t nMonType2{};

			// Call both implementations
			auto moo_result = sut(nMonType1, nMonType2);
			auto original_result = original(nMonType1, nMonType2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBF450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_RollDamageValueInRange, dll_base + 0x0008F450);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nMinDamage{};
			int32_t nMaxDamage{};
			int32_t nMinDamageBonusPct{};
			int32_t nMaxDamageBonusPct{};
			int32_t nDamage{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nMinDamage, nMaxDamage, nMinDamageBonusPct, nMaxDamageBonusPct, nDamage);
			auto original_result = original(&original_pUnit, nMinDamage, nMaxDamage, nMinDamageBonusPct, nMaxDamageBonusPct, nDamage);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBF620" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_CalculateTotalDamage, dll_base + 0x0008F620);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			D2DamageStrc original_pDamage{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pDefender, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, &moo_pDamage);
			original(&original_pGame, &original_pAttacker, &original_pDefender, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBFB40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ApplyResistancesAndAbsorb, dll_base + 0x0008FB40);
		
		SUBCASE("")
		{
			// Input data
			D2DamageInfoStrc moo_pDamageInfo{};
			D2DamageInfoStrc original_pDamageInfo{};
			D2DamageStatTableStrc pDamageStatTableRecord{};
			int32_t bDontAbsorb{};

			const auto setup_data = [](
				D2DamageInfoStrc& pDamageInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDamageInfo);
			setup_data(original_pDamageInfo);

			// Call both implementations
			sut(&moo_pDamageInfo, &pDamageStatTableRecord, bDontAbsorb);
			original(&original_pDamageInfo, &pDamageStatTableRecord, bDontAbsorb);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDamageInfo, original_pDamageInfo, "Comparing pDamageInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBFE90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ExecuteEvents, dll_base + 0x0008FE90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			D2DamageStrc original_pDamage{};
			int32_t bMissile{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pDefender, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, bMissile, &moo_pDamage);
			original(&original_pGame, &original_pAttacker, &original_pDefender, bMissile, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC05D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_GetMonStatsTxtRecordFromUnit, dll_base + 0x000905D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC05F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_AddLeechedLife, dll_base + 0x000905F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nLifeLeeched{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nLifeLeeched);
			auto original_result = original(&original_pUnit, nLifeLeeched);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC0660" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_AddLeechedMana, dll_base + 0x00090660);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nManaLeeched{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nManaLeeched);
			auto original_result = original(&original_pUnit, nManaLeeched);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC06C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ApplyPoisonDamage, dll_base + 0x000906C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t nPoisonDamage{};
			int32_t nPoisonLength{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender);
			setup_data(original_pAttacker, original_pDefender);

			// Call both implementations
			sut(&moo_pAttacker, &moo_pDefender, nPoisonDamage, nPoisonLength);
			original(&original_pAttacker, &original_pDefender, nPoisonDamage, nPoisonLength);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC0800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ApplyBurnDamage, dll_base + 0x00090800);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t nBurnDamage{};
			int32_t nBurnLength{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender);
			setup_data(original_pAttacker, original_pDefender);

			// Call both implementations
			sut(&moo_pAttacker, &moo_pDefender, nBurnDamage, nBurnLength);
			original(&original_pAttacker, &original_pDefender, nBurnDamage, nBurnLength);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC0940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ApplyColdState, dll_base + 0x00090940);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t nColdLength{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender);
			setup_data(original_pAttacker, original_pDefender);

			// Call both implementations
			sut(&moo_pAttacker, &moo_pDefender, nColdLength);
			original(&original_pAttacker, &original_pDefender, nColdLength);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC0B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_RemoveShatterState, dll_base + 0x00090B90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			struct D2StatListStrc moo_pStatList{};
			D2UnitStrc original_pUnit{};
			struct D2StatListStrc original_pStatList{};
			int32_t nState{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				struct D2StatListStrc& pStatList
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC0BE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ApplyFreezeState, dll_base + 0x00090BE0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t nFreezeLength{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender);
			setup_data(original_pAttacker, original_pDefender);

			// Call both implementations
			sut(&moo_pAttacker, &moo_pDefender, nFreezeLength);
			original(&original_pAttacker, &original_pDefender, nFreezeLength);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC0E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_FreeAttackerCombatList, dll_base + 0x00090E20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC0E90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_FreeAttackerDefenderCombatList, dll_base + 0x00090E90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender);
			setup_data(original_pGame, original_pAttacker, original_pDefender);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender);
			original(&original_pGame, &original_pAttacker, &original_pDefender);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC0F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_KillMonster, dll_base + 0x00090F10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc moo_pAttacker{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pDefender{};
			D2UnitStrc original_pAttacker{};
			int32_t bPetKill{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pDefender,
				D2UnitStrc& pAttacker
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pDefender, moo_pAttacker);
			setup_data(original_pGame, original_pDefender, original_pAttacker);

			// Call both implementations
			sut(&moo_pGame, &moo_pDefender, &moo_pAttacker, bPetKill);
			original(&original_pGame, &original_pDefender, &original_pAttacker, bPetKill);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC1260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ExecuteMissileDamage, dll_base + 0x00091260);
		
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
			sut(&moo_pGame, &moo_pAttacker, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pAttacker, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC1870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCC1870, dll_base + 0x00091870);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nHitClass{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pDamage);
			setup_data(original_pUnit, original_pDamage);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, &moo_pDamage, nHitClass);
			auto original_result = original(&original_pUnit, &original_pDamage, nHitClass);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC1A50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_GetHitClass, dll_base + 0x00091A50);
		
		SUBCASE("")
		{
			// Input data
			D2DamageStrc moo_pDamage{};
			D2DamageStrc original_pDamage{};
			uint32_t nBaseHitClass{};

			const auto setup_data = [](
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pDamage);
			setup_data(original_pDamage);

			// Call both implementations
			auto moo_result = sut(&moo_pDamage, nBaseHitClass);
			auto original_result = original(&original_pDamage, nBaseHitClass);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC1AC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_DrainItemDurability, dll_base + 0x00091AC0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t nUnused{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender);
			setup_data(original_pGame, original_pAttacker, original_pDefender);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, nUnused);
			original(&original_pGame, &original_pAttacker, &original_pDefender, nUnused);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC1D70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_GetDamageFromUnits, dll_base + 0x00091D70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender);
			setup_data(original_pAttacker, original_pDefender);

			// Call both implementations
			auto moo_result = sut(&moo_pAttacker, &moo_pDefender);
			auto original_result = original(&original_pAttacker, &original_pDefender);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC1DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10033, dll_base + 0x00091DC0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			int32_t moo_a2{};
			int32_t moo_a3{};
			D2UnitStrc original_pUnit{};
			int32_t original_a2{};
			int32_t original_a3{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				int32_t& a2,
				int32_t& a3
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_a2, moo_a3);
			setup_data(original_pUnit, original_a2, original_a3);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, &moo_a2, &moo_a3);
			auto original_result = original(&original_pUnit, &original_a2, &original_a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC1E70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_IsHitSuccessful, dll_base + 0x00091E70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t nStatValue{};
			int32_t bMissile{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender);
			setup_data(original_pAttacker, original_pDefender);

			// Call both implementations
			auto moo_result = sut(&moo_pAttacker, &moo_pDefender, nStatValue, bMissile);
			auto original_result = original(&original_pAttacker, &original_pDefender, nStatValue, bMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_GetResultFlags, dll_base + 0x00092300);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t nStatValue{};
			int32_t nRangeOffset{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender);
			setup_data(original_pGame, original_pAttacker, original_pDefender);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, nStatValue, nRangeOffset);
			auto original_result = original(&original_pGame, &original_pAttacker, &original_pDefender, nStatValue, nRangeOffset);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_AllocCombat, dll_base + 0x00092420);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			D2DamageStrc original_pDamage{};
			uint8_t nSrcDam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pDefender, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, &moo_pDamage, nSrcDam);
			original(&original_pGame, &original_pAttacker, &original_pDefender, &original_pDamage, nSrcDam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ApplyBlockOrDodge, dll_base + 0x00092530);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t bAvoid{};
			int32_t bBlock{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender);
			setup_data(original_pGame, original_pAttacker, original_pDefender);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, bAvoid, bBlock);
			auto original_result = original(&original_pGame, &original_pAttacker, &original_pDefender, bAvoid, bBlock);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ApplyDodge, dll_base + 0x00092610);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			int32_t bAvoid{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker, moo_pDefender);
			setup_data(original_pAttacker, original_pDefender);

			// Call both implementations
			auto moo_result = sut(&moo_pAttacker, &moo_pDefender, bAvoid);
			auto original_result = original(&original_pAttacker, &original_pDefender, bAvoid);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_GetWeaponBlock, dll_base + 0x00092850);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_SetMissileDamageFlagsForNearbyUnits, dll_base + 0x00092910);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nX{};
			int32_t nY{};
			int32_t nSize{};
			int32_t a7{};
			int32_t a8{};
			int32_t a10{};

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY, nSize, &moo_pDamage, a7, a8, nullptr, a10);
			auto original_result = original(&original_pGame, &original_pUnit, nX, nY, nSize, &original_pDamage, a7, a8, nullptr, a10);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2BC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_RollDamage, dll_base + 0x00092BC0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pDamage);
			setup_data(original_pUnit, original_pDamage);

			// Call both implementations
			sut(&moo_pUnit, nSkillId, nSkillLevel, &moo_pDamage);
			original(&original_pUnit, nSkillId, nSkillLevel, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2BF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_RollSuckBloodDamage, dll_base + 0x00092BF0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};
			D2DamageStrc original_pDamage{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender, moo_pDamage);
			setup_data(original_pGame, original_pAttacker, original_pDefender, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, nSkillId, nSkillLevel, &moo_pDamage);
			original(&original_pGame, &original_pAttacker, &original_pDefender, nSkillId, nSkillLevel, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_DistributeExperience, dll_base + 0x00092C70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc moo_pDefender{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			D2UnitStrc original_pDefender{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker,
				D2UnitStrc& pDefender
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker, moo_pDefender);
			setup_data(original_pGame, original_pAttacker, original_pDefender);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttacker, &moo_pDefender);
			original(&original_pGame, &original_pAttacker, &original_pDefender);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC2EC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_ComputeExperienceGain, dll_base + 0x00092EC0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttacker{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttacker{};
			uint32_t nAttackerLevel{};
			uint32_t nDefenderLevel{};
			uint32_t nDefenderExperience{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttacker
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttacker);
			setup_data(original_pGame, original_pAttacker);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pAttacker, nAttackerLevel, nDefenderLevel, nDefenderExperience);
			auto original_result = original(&original_pGame, &original_pAttacker, nAttackerLevel, nDefenderLevel, nDefenderExperience);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3170" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_AddExperienceForPlayer, dll_base + 0x00093170);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint32_t nOldLevel{};
			uint32_t nExperienceGained{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nOldLevel, nExperienceGained);
			original(&original_pGame, &original_pUnit, nOldLevel, nExperienceGained);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3200" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_PartyCallback_ComputePartyExperience, dll_base + 0x00093200);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, moo_pArg);
			original(&original_pGame, &original_pUnit, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_AddExperienceForHireling, dll_base + 0x00093360);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pHireling{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pHireling{};
			uint32_t nLevel{};
			uint32_t nExperienceBonus{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pHireling
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pHireling);
			setup_data(original_pGame, original_pPlayer, original_pHireling);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pHireling, nLevel, nExperienceBonus);
			original(&original_pGame, &original_pPlayer, &original_pHireling, nLevel, nExperienceBonus);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pHireling, original_pHireling, "Comparing pHireling");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC34A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_AddExperience, dll_base + 0x000934A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint32_t nExperienceBonus{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nExperienceBonus);
			original(&original_pGame, &original_pUnit, nExperienceBonus);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3510" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITDMG_SetExperienceForTargetLevel, dll_base + 0x00093510);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint32_t nTargetLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nTargetLevel);
			original(&original_pGame, &original_pUnit, nTargetLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
