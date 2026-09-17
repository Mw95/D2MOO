#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2StatList.h>
#include <DataTbls/SkillsTbls.h>
#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <SKILLS/Skills.h>
#include <Units/Units.h>


TEST_SUITE("SkillsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0F8B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0F8B0, dll_base + 0x000DF8B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nValue{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nValue);
			const auto original_result = original(&original_pGame, &original_pUnit, nValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0FA00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0FA00, dll_base + 0x000DFA00);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			uint32_t nAuraFilter{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pTarget);
			setup_data(original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pTarget, nAuraFilter);
			const auto original_result = original(&original_pUnit, &original_pTarget, nAuraFilter);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0FDD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0FDD0, dll_base + 0x000DFDD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0FE50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0FE50, dll_base + 0x000DFE50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nullptr, moo_pArgs);
			original(&original_pGame, &original_pUnit, nullptr, original_pArgs);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD0FE80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD0FE80, dll_base + 0x000DFE80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};
			int32_t nAuraRange{};
			uint32_t nAuraFilter{};
			void* moo_pCallbackArgs = nullptr;
			void* original_pCallbackArgs = nullptr;
			int32_t bCheckMonAuraFlag{};
			char szFile{};
			int32_t nLine{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nX, nY, nAuraRange, nAuraFilter, nullptr, moo_pCallbackArgs, bCheckMonAuraFlag, &szFile, nLine);
			original(&original_pGame, &original_pUnit, nX, nY, nAuraRange, nAuraFilter, nullptr, original_pCallbackArgs, bCheckMonAuraFlag, &szFile, nLine);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArgs, original_pCallbackArgs, "Comparing pCallbackArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10140, dll_base + 0x000E0140);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pAttackerArg{};
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pAttackerArg{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nUnused{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pAttackerArg,
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAttackerArg, moo_pUnit, moo_pDamage);
			setup_data(original_pGame, original_pAttackerArg, original_pUnit, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pAttackerArg, &moo_pUnit, &moo_pDamage, nUnused);
			original(&original_pGame, &original_pAttackerArg, &original_pUnit, &original_pDamage, nUnused);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttackerArg, original_pAttackerArg, "Comparing pAttackerArg");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10200" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10200, dll_base + 0x000E0200);
		
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
			int32_t nAuraRange{};
			uint32_t nAuraFilter{};

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY, nAuraRange, &moo_pDamage, nAuraFilter);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY, nAuraRange, &original_pDamage, nAuraFilter);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10250, dll_base + 0x000E0250);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nState{};
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
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nState, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, &original_pTarget, nState, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10360, dll_base + 0x000E0360);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint32_t nFlags{};
			int32_t nDistance{};
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nFlags, &moo_pUnit, nDistance, nullptr, moo_pArgs);
			const auto original_result = original(&original_pGame, nFlags, &original_pUnit, nDistance, nullptr, original_pArgs);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_FindAuraTarget, dll_base + 0x000E0630);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nAuraRange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nAuraRange, nullptr);
			const auto original_result = original(&original_pGame, &original_pUnit, nAuraRange, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD106F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD106F0, dll_base + 0x000E06F0);
		
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
			const auto moo_result = sut(&moo_pAuraCallback, &moo_pUnit);
			const auto original_result = original(&original_pAuraCallback, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAuraCallback, original_pAuraCallback, "Comparing pAuraCallback");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10790, dll_base + 0x000E0790);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};
			int32_t nAuraRange{};
			uint32_t nAuraFilter{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY, nAuraRange, nAuraFilter);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY, nAuraRange, nAuraFilter);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD107E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD107E0, dll_base + 0x000E07E0);
		
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
			const auto moo_result = sut(&moo_pAuraCallback, &moo_pUnit);
			const auto original_result = original(&original_pAuraCallback, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAuraCallback, original_pAuraCallback, "Comparing pAuraCallback");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD107F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD107F0, dll_base + 0x000E07F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			int32_t moo_a8{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t original_a8{};
			int32_t nX{};
			int32_t nY{};
			int32_t nAuraRange{};
			uint32_t nAuraFilter{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				int32_t& a8
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_a8);
			setup_data(original_pGame, original_pUnit, original_a8);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY, nAuraRange, nAuraFilter, a7, &moo_a8);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY, nAuraRange, nAuraFilter, a7, &original_a8);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a8, original_a8, "Comparing a8");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10880, dll_base + 0x000E0880);
		
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
			const auto moo_result = sut(&moo_pAuraCallback, &moo_pUnit);
			const auto original_result = original(&original_pAuraCallback, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAuraCallback, original_pAuraCallback, "Comparing pAuraCallback");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD108D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD108D0, dll_base + 0x000E08D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nSkillId);
			original(&original_pGame, &original_pUnit, nSkillId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10A50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SKILLMANA_Consume_6FD10A50, dll_base + 0x000E0A50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pPlayer, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10C90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SKILLMANA_AuraConsume_6FD10C90, dll_base + 0x000E0C90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nManaCost{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nManaCost);
			const auto original_result = original(&original_pUnit, nManaCost);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10CE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10CE0, dll_base + 0x000E0CE0);
		
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
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10D90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10D90, dll_base + 0x000E0D90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nSize{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSize, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nSize, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10E20, dll_base + 0x000E0E20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitFindDataStrc moo_pUnitFindData{};
			D2GameStrc original_pGame{};
			D2UnitFindDataStrc original_pUnitFindData{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitFindDataStrc& pUnitFindData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnitFindData);
			setup_data(original_pGame, original_pUnitFindData);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnitFindData);
			original(&original_pGame, &original_pUnitFindData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnitFindData, original_pUnitFindData, "Comparing pUnitFindData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10E50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10E50, dll_base + 0x000E0E50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD10EC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD10EC0, dll_base + 0x000E0EC0);
		
		SUBCASE("")
		{
			// Input data
			D2CurseStrc moo_pCurse{};
			D2CurseStrc original_pCurse{};

			const auto setup_data = [](
				D2CurseStrc& pCurse
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCurse);
			setup_data(original_pCurse);

			// Call both implementations
			const auto moo_result = sut(&moo_pCurse);
			const auto original_result = original(&original_pCurse);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCurse, original_pCurse, "Comparing pCurse");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11260, dll_base + 0x000E1260);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nStatId{};
			int32_t nState{};
			StatListRemoveCallback pfRemoveStatCallback{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pTarget);
			setup_data(original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pTarget, nSkillId, nSkillLevel, nStatId, nState, pfRemoveStatCallback);
			const auto original_result = original(&original_pUnit, &original_pTarget, nSkillId, nSkillLevel, nStatId, nState, pfRemoveStatCallback);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11340, dll_base + 0x000E1340);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pItem);
			setup_data(original_pGame, original_pUnit, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11420, dll_base + 0x000E1420);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nMissileId{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nX{};
			int32_t nY{};
			int32_t nTargetX{};
			int32_t nTargetY{};
			int32_t bCheckItemQuantity{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nMissileId, &moo_pUnit, nSkillId, nSkillLevel, nX, nY, nTargetX, nTargetY, bCheckItemQuantity);
			const auto original_result = original(&original_pGame, nMissileId, &original_pUnit, nSkillId, nSkillLevel, nX, nY, nTargetX, nTargetY, bCheckItemQuantity);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD115E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CreateMissile_6FD115E0, dll_base + 0x000E15E0);
		
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
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel, nMissileId, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel, nMissileId, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11710, dll_base + 0x000E1710);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nMissileId{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nX{};
			int32_t nY{};
			int32_t nTargetX{};
			int32_t nTargetY{};
			int32_t bSkipCheck{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nMissileId, &moo_pUnit, nSkillId, nSkillLevel, nX, nY, nTargetX, nTargetY, bSkipCheck);
			const auto original_result = original(&original_pGame, nMissileId, &original_pUnit, nSkillId, nSkillLevel, nX, nY, nTargetX, nTargetY, bSkipCheck);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD118C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD118C0, dll_base + 0x000E18C0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD119C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD119C0, dll_base + 0x000E19C0);
		
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
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11AE0, dll_base + 0x000E1AE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pItem);
			setup_data(original_pGame, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			original(&original_pGame, &original_pUnit, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11B50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CheckSkillIfUnitsClassSkill_6FD11B50, dll_base + 0x000E1B50);
		
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
			const auto moo_result = sut(&moo_pUnit, nSkillId);
			const auto original_result = original(&original_pUnit, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11BA0, dll_base + 0x000E1BA0);
		
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
			sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SKILLS_SetDelay_6FD11C00, dll_base + 0x000E1C00);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nDelay{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nDelay);
			original(&original_pGame, &original_pUnit, nDelay);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11C90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11C90, dll_base + 0x000E1C90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nStateId{};
			int32_t a3{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nStateId, a3);
			const auto original_result = original(&original_pUnit, nStateId, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11D90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11D90, dll_base + 0x000E1D90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t nLength{};
			int32_t nSkillId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pDamage);
			setup_data(original_pUnit, original_pDamage);

			// Call both implementations
			sut(&moo_pUnit, &moo_pDamage, nLength, nSkillId);
			original(&original_pUnit, &original_pDamage, nLength, nSkillId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11E40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD11E40, dll_base + 0x000E1E40);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			int32_t moo_pResistStatId{};
			int32_t moo_pElementalType{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			int32_t original_pResistStatId{};
			int32_t original_pElementalType{};
			int32_t nElementalType{};
			int32_t nDamage{};
			int32_t nLength{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage,
				int32_t& pResistStatId,
				int32_t& pElementalType
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pDamage, moo_pResistStatId, moo_pElementalType);
			setup_data(original_pUnit, original_pDamage, original_pResistStatId, original_pElementalType);

			// Call both implementations
			sut(&moo_pUnit, &moo_pDamage, nElementalType, nDamage, nLength, &moo_pResistStatId, &moo_pElementalType);
			original(&original_pUnit, &original_pDamage, nElementalType, nDamage, nLength, &original_pResistStatId, &original_pElementalType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
			SKIP_MOO_CHECK_EQ(moo_pResistStatId, original_pResistStatId, "Comparing pResistStatId");
			SKIP_MOO_CHECK_EQ(moo_pElementalType, original_pElementalType, "Comparing pElementalType");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD11FF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt01_Attack_LeftHandSwing, dll_base + 0x000E1FF0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD12060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt65_Throw_LeftHandThrow, dll_base + 0x000E2060);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD120A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt02_Kick, dll_base + 0x000E20A0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD12150" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt03_Unsummon, dll_base + 0x000E2150);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD12210" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo001_Attack_LeftHandSwing, dll_base + 0x000E2210);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD123D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo002_Kick_PowerStrike_MonIceSpear_Impale_Bash_Stun_Concentrate_BearSmite_Vengeance_Berserk_FireClaws, dll_base + 0x000E23D0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD12670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo004_Unsummon, dll_base + 0x000E2670);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD126B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo003_Throw, dll_base + 0x000E26B0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD12800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvDo005_LeftHandThrow, dll_base + 0x000E2800);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD12950" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD12950, dll_base + 0x000E2950);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel, a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD12BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SKILLS_Handler_6FD12BA0, dll_base + 0x000E2BA0);
		
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
			int32_t a6{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel, a5, a6, a7);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel, a5, a6, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD12FD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD12FD0, dll_base + 0x000E2FD0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILL_ComputePeriodicRate, dll_base + 0x000E3220);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2SkillsTxt moo_pSkillsTxtRecord{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2SkillsTxt original_pSkillsTxtRecord{};
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pSkillsTxtRecord, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pSkillsTxtRecord, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSkillsTxtRecord, original_pSkillsTxtRecord, "Comparing pSkillsTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD13260, dll_base + 0x000E3260);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel, a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13330" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD13330, dll_base + 0x000E3330);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a5{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, a5, nSkillId, nSkillLevel, a6);
			const auto original_result = original(&original_pGame, &original_pUnit, a5, nSkillId, nSkillLevel, a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD13410, dll_base + 0x000E3410);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction09_6FD13470, dll_base + 0x000E3470);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillIdArg{};
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
			sut(&moo_pGame, &moo_pUnit, nSkillIdArg, a4);
			original(&original_pGame, &original_pUnit, nSkillIdArg, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction10_6FD13610, dll_base + 0x000E3610);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t nSkillId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, nSkillId);
			original(&original_pGame, &original_pUnit, a3, nSkillId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD136E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD136E0, dll_base + 0x000E36E0);
		
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
			const auto moo_result = sut(&moo_pUnit, nSkillId);
			const auto original_result = original(&original_pUnit, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AssignSkill_6FD13800, dll_base + 0x000E3800);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t a2{};
			int32_t nSkillId{};
			int32_t nFlags{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, a2, nSkillId, nFlags);
			original(&original_pUnit, a2, nSkillId, nFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CreateLinkPortal_6FD13B20, dll_base + 0x000E3B20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPortal{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPortal{};
			int32_t nDestLevel{};
			int32_t nSourceLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPortal
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPortal);
			setup_data(original_pGame, original_pPortal);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPortal, nDestLevel, nSourceLevel);
			const auto original_result = original(&original_pGame, &original_pPortal, nDestLevel, nSourceLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPortal, original_pPortal, "Comparing pPortal");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD13DF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CreatePortalObject_6FD13DF0, dll_base + 0x000E3DF0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc* moo_ppSourceUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			D2UnitStrc* original_ppSourceUnit{};
			int32_t nX{};
			int32_t nY{};
			int32_t nDestLevel{};
			int32_t nObjectId{};
			int32_t bPerm{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom,
				D2UnitStrc*& ppSourceUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pRoom, moo_ppSourceUnit);
			setup_data(original_pGame, original_pUnit, original_pRoom, original_ppSourceUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pRoom, nX, nY, nDestLevel, &moo_ppSourceUnit, nObjectId, bPerm);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pRoom, nX, nY, nDestLevel, &original_ppSourceUnit, nObjectId, bPerm);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_ppSourceUnit, original_ppSourceUnit, "Comparing ppSourceUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetXAndYFromTargetUnit_6FD14020, dll_base + 0x000E4020);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			int32_t moo_pX{};
			int32_t moo_pY{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t original_pX{};
			int32_t original_pY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				int32_t& pX,
				int32_t& pY
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pX, moo_pY);
			setup_data(original_pGame, original_pUnit, original_pX, original_pY);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pX, &original_pY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD140D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD140D0, dll_base + 0x000E40D0);
		
		SUBCASE("")
		{
			// Input data
			int32_t moo_pX{};
			int32_t moo_pY{};
			int32_t original_pX{};
			int32_t original_pY{};

			const auto setup_data = [](
				int32_t& pX,
				int32_t& pY
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14120, dll_base + 0x000E4120);
		
		SUBCASE("")
		{
			// Input data
			int32_t moo_pX{};
			int32_t moo_pY{};
			int32_t original_pX{};
			int32_t original_pY{};

			const auto setup_data = [](
				int32_t& pX,
				int32_t& pY
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pX, moo_pY);
			setup_data(original_pX, original_pY);

			// Call both implementations
			sut(&moo_pX, &moo_pY);
			original(&original_pX, &original_pY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14170" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14170, dll_base + 0x000E4170);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_a3{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_a3{};
			int32_t nMissileId{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nVelocity{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pOwner,
				D2UnitStrc& a3
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pOwner, moo_a3);
			setup_data(original_pGame, original_pOwner, original_a3);

			// Call both implementations
			sut(&moo_pGame, &moo_pOwner, &moo_a3, nMissileId, nSkillId, nSkillLevel, nVelocity);
			original(&original_pGame, &original_pOwner, &original_a3, nMissileId, nSkillId, nSkillLevel, nVelocity);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14260, dll_base + 0x000E4260);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2MissileStrc moo_missileParams{};
			D2GameStrc original_pGame{};
			D2MissileStrc original_missileParams{};
			int32_t nMissiles{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2MissileStrc& missileParams
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_missileParams);
			setup_data(original_pGame, original_missileParams);

			// Call both implementations
			sut(&moo_pGame, nMissiles, &moo_missileParams);
			original(&original_pGame, nMissiles, &original_missileParams);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_missileParams, original_missileParams, "Comparing missileParams");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14370" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction06_6FD14370, dll_base + 0x000E4370);
		
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
			sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14400" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14400, dll_base + 0x000E4400);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nDoFunc{};
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
			sut(&moo_pGame, &moo_pUnit, nDoFunc, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, nDoFunc, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SummonPet_6FD14430, dll_base + 0x000E4430);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2SummonArgStrc moo_pSummonArg{};
			D2GameStrc original_pGame{};
			D2SummonArgStrc original_pSummonArg{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2SummonArgStrc& pSummonArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pSummonArg);
			setup_data(original_pGame, original_pSummonArg);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pSummonArg);
			const auto original_result = original(&original_pGame, &original_pSummonArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pSummonArg, original_pSummonArg, "Comparing pSummonArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD146D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD146D0, dll_base + 0x000E46D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14770" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14770, dll_base + 0x000E4770);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nFlags{};
			int32_t nSkillLevel{};
			int32_t nRange{};
			CurseCallbackFunc pfCurse{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, nFlags, &moo_pUnit, nSkillLevel, nRange, pfCurse);
			original(&original_pGame, nFlags, &original_pUnit, nSkillLevel, nRange, pfCurse);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD149B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD149B0, dll_base + 0x000E49B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2EffectStrc moo_pEffect{};
			D2GameStrc original_pGame{};
			D2EffectStrc original_pEffect{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2EffectStrc& pEffect
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pEffect);
			setup_data(original_pGame, original_pEffect);

			// Call both implementations
			sut(&moo_pGame, &moo_pEffect);
			original(&original_pGame, &original_pEffect);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pEffect, original_pEffect, "Comparing pEffect");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14BD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14BD0, dll_base + 0x000E4BD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nFlags{};
			int32_t nX{};
			int32_t nY{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			void* moo_pfAreaEffect = nullptr;
			void* original_pfAreaEffect = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, nFlags, nX, nY, &moo_pUnit, nSkillId, nSkillLevel, moo_pfAreaEffect);
			original(&original_pGame, nFlags, nX, nY, &original_pUnit, nSkillId, nSkillLevel, original_pfAreaEffect);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pfAreaEffect, original_pfAreaEffect, "Comparing pfAreaEffect");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14C30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14C30, dll_base + 0x000E4C30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14C60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetSkills_6FD14C60, dll_base + 0x000E4C60);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t bRemove{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nSkillId, nSkillLevel, bRemove);
			original(&original_pUnit, nSkillId, nSkillLevel, bRemove);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RefreshPassiveSkills_6FD14CC0, dll_base + 0x000E4CC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14D20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14D20, dll_base + 0x000E4D20);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2MonSkillInfoStrc moo_pMonSkillInfo{};
			D2UnitStrc original_pUnit{};
			D2MonSkillInfoStrc original_pMonSkillInfo{};
			int32_t nUnused{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2MonSkillInfoStrc& pMonSkillInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pMonSkillInfo);
			setup_data(original_pUnit, original_pMonSkillInfo);

			// Call both implementations
			sut(&moo_pUnit, nUnused, &moo_pMonSkillInfo);
			original(&original_pUnit, nUnused, &original_pMonSkillInfo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMonSkillInfo, original_pMonSkillInfo, "Comparing pMonSkillInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14DD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RollElementalDamage_6FD14DD0, dll_base + 0x000E4DD0);
		
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
			const auto moo_result = sut(&moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pUnit, &original_pDamage, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14EC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RollPhysicalDamage_6FD14EC0, dll_base + 0x000E4EC0);
		
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
			sut(&moo_pUnit, &moo_pDamage, nSkillId, nSkillLevel);
			original(&original_pUnit, &original_pDamage, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD14F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD14F70, dll_base + 0x000E4F70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnused{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnused{};
			D2UnitStrc original_pUnit{};
			int32_t nDelay{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnused,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnused, moo_pUnit);
			setup_data(original_pGame, original_pUnused, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnused, &moo_pUnit, nDelay);
			original(&original_pGame, &original_pUnused, &original_pUnit, nDelay);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15080, dll_base + 0x000E5080);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t a2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, a2);
			original(&original_pUnit, a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD150A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD150A0, dll_base + 0x000E50A0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15190, dll_base + 0x000E5190);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			D2C_AiSpecialState nAiSpecialState{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nAiSpecialState);
			const auto original_result = original(&original_pUnit, nAiSpecialState);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15210" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15210, dll_base + 0x000E5210);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pTarget);
			setup_data(original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pTarget, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pUnit, &original_pTarget, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15320" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15320, dll_base + 0x000E5320);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitFindArgStrc moo_pArg{};
			D2UnitStrc original_pUnit{};
			D2UnitFindArgStrc original_pArg{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitFindArgStrc& pArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pArg);
			setup_data(original_pUnit, original_pArg);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pArg);
			const auto original_result = original(&original_pUnit, &original_pArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15340, dll_base + 0x000E5340);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMissileId);
			const auto original_result = original(&original_pGame, &original_pUnit, nMissileId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15460, dll_base + 0x000E5460);
		
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
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15470, dll_base + 0x000E5470);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nAttackRate{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nAttackRate);
			original(&original_pUnit, nAttackRate);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD154D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD154D0, dll_base + 0x000E54D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15500" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15500, dll_base + 0x000E5500);
		
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
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetSummonIdFromSkill_6FD15580, dll_base + 0x000E5580);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			int32_t moo_pSpawnMode{};
			int32_t moo_pX{};
			int32_t moo_pY{};
			D2UnitStrc original_pUnit{};
			int32_t original_pSpawnMode{};
			int32_t original_pX{};
			int32_t original_pY{};
			int32_t bFromMonster{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				int32_t& pSpawnMode,
				int32_t& pX,
				int32_t& pY
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pSpawnMode, moo_pX, moo_pY);
			setup_data(original_pUnit, original_pSpawnMode, original_pX, original_pY);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, bFromMonster, nSkillId, nSkillLevel, &moo_pSpawnMode, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pUnit, bFromMonster, nSkillId, nSkillLevel, &original_pSpawnMode, &original_pX, &original_pY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSpawnMode, original_pSpawnMode, "Comparing pSpawnMode");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD155E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD155E0, dll_base + 0x000E55E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2SkillsTxt moo_pSkillsTxtRecord{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			D2SkillsTxt original_pSkillsTxtRecord{};
			D2DamageStrc original_pDamage{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t a8{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget,
				D2SkillsTxt& pSkillsTxtRecord,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget, moo_pSkillsTxtRecord, moo_pDamage);
			setup_data(original_pGame, original_pUnit, original_pTarget, original_pSkillsTxtRecord, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, &moo_pSkillsTxtRecord, nSkillId, nSkillLevel, &moo_pDamage, a8);
			original(&original_pGame, &original_pUnit, &original_pTarget, &original_pSkillsTxtRecord, nSkillId, nSkillLevel, &original_pDamage, a8);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pSkillsTxtRecord, original_pSkillsTxtRecord, "Comparing pSkillsTxtRecord");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD15650" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD15650, dll_base + 0x000E5650);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pUnit{};
			D2DamageStrc moo_pDamage{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pUnit{};
			D2DamageStrc original_pDamage{};
			uint16_t wResultFlags{};
			int32_t a5{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pOwner,
				D2UnitStrc& pUnit,
				D2DamageStrc& pDamage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pOwner, moo_pUnit, moo_pDamage);
			setup_data(original_pGame, original_pOwner, original_pUnit, original_pDamage);

			// Call both implementations
			sut(&moo_pGame, &moo_pOwner, &moo_pUnit, wResultFlags, a5, &moo_pDamage, a7);
			original(&original_pGame, &original_pOwner, &original_pUnit, wResultFlags, a5, &original_pDamage, a7);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FD156A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD156A0, dll_base + 0x000E56A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2C_UnitEventTypes nUnitEventType{};
			int32_t a4{};
			int32_t a5{};
			int32_t nEventFunc{};
			int32_t a7{};
			int32_t a8{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nUnitEventType, a4, a5, nEventFunc, a7, a8);
			const auto original_result = original(&original_pGame, &original_pUnit, nUnitEventType, a4, a5, nEventFunc, a7, a8);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC808D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SrvSt18_Attract, dll_base + 0x000508D0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
