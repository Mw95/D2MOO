#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <AI/AiBaal.h>
#include <AI/AiGeneral.h>
#include <GAME/Game.h>
#include <Units/Units.h>


TEST_SUITE("AiBaalTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIBAAL_CountLivingMinions, dll_base + 0x0009D450);
		
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
			void* moo_ppUnitArg = nullptr;
			void* original_ppUnitArg = nullptr;
			void* moo_pCounterArg = nullptr;
			void* original_pCounterArg = nullptr;

			// Call both implementations
			sut(&moo_pUnit, moo_ppUnitArg, moo_pCounterArg);
			original(&original_pUnit, original_ppUnitArg, original_pCounterArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_ppUnitArg, original_ppUnitArg, "Comparing ppUnitArg");
			SKIP_MOO_CHECK_EQ(moo_pCounterArg, original_pCounterArg, "Comparing pCounterArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk135_140_6FCCD470, dll_base + 0x0009D470);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2AiTickParamStrc pAiTickParam{};
				
				return std::tuple{ pGame, pUnit, pAiTickParam };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pAiTickParam] = setup_data();
			auto [original_pGame, original_pUnit, original_pAiTickParam] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			original(&original_pGame, &original_pUnit, &original_pAiTickParam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn135_BaalCrab, dll_base + 0x0009D520);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2AiTickParamStrc pAiTickParam{};
				
				return std::tuple{ pGame, pUnit, pAiTickParam };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pAiTickParam] = setup_data();
			auto [original_pGame, original_pUnit, original_pAiTickParam] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			original(&original_pGame, &original_pUnit, &original_pAiTickParam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIBAAL_GetTarget, dll_base + 0x0009D630);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t pMax{};
				int32_t pCount{};
				
				return std::tuple{ pGame, pUnit, pMax, pCount };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pMax, moo_pCount] = setup_data();
			auto [original_pGame, original_pUnit, original_pMax, original_pCount] = setup_data();
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pMax, &moo_pCount, moo_pArgs, nullptr);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pMax, &original_pCount, original_pArgs, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMax, original_pMax, "Comparing pMax");
			SKIP_MOO_CHECK_EQ(moo_pCount, original_pCount, "Comparing pCount");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCD8A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIBAAL_GetTargetScore, dll_base + 0x0009D8A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pUnit, pTarget };
			};
			
			// Input data
			auto [moo_pUnit, moo_pTarget] = setup_data();
			auto [original_pUnit, original_pTarget] = setup_data();
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pTarget, moo_pArgs);
			const auto original_result = original(&original_pUnit, &original_pTarget, original_pArgs);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCDBB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIBAAL_CullPotentialTargets, dll_base + 0x0009DBB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pBaal{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pBaal, pTarget };
			};
			
			// Input data
			auto [moo_pBaal, moo_pTarget] = setup_data();
			auto [original_pBaal, original_pTarget] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pBaal, &moo_pTarget);
			const auto original_result = original(&original_pBaal, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pBaal, original_pBaal, "Comparing pBaal");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCDC80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIBAAL_RollRandomAiParam, dll_base + 0x0009DC80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2AiControlStrc pAiControl{};
				D2UnitStrc pTarget{};
				D2AiCmdStrc pAiCmd{};
				
				return std::tuple{ pGame, pUnit, pAiControl, pTarget, pAiCmd };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pAiControl, moo_pTarget, moo_pAiCmd] = setup_data();
			auto [original_pGame, original_pUnit, original_pAiControl, original_pTarget, original_pAiCmd] = setup_data();
			int32_t nMax{};
			int32_t nCount{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, &moo_pTarget, nMax, nCount, &moo_pAiCmd);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiControl, &original_pTarget, nMax, nCount, &original_pAiCmd);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pAiCmd, original_pAiCmd, "Comparing pAiCmd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCE040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AI_CheckSpecialSkillsOnPrimeEvil, dll_base + 0x0009E040);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCE100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AI_GetRandomArrayIndex, dll_base + 0x0009E100);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int32_t pArray{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pArray, pUnit };
			};
			
			// Input data
			auto [moo_pArray, moo_pUnit] = setup_data();
			auto [original_pArray, original_pUnit] = setup_data();
			int32_t nArraySize{};
			int32_t nDefaultValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pArray, nArraySize, &moo_pUnit, nDefaultValue);
			const auto original_result = original(&original_pArray, nArraySize, &original_pUnit, nDefaultValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pArray, original_pArray, "Comparing pArray");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCE1A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIBAAL_RollRandomAiParamForNonCollidingUnit, dll_base + 0x0009E1A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2AiControlStrc pAiControl{};
				D2UnitStrc pUnit{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pAiControl, pUnit, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pAiControl, moo_pUnit, moo_pTarget] = setup_data();
			auto [original_pGame, original_pAiControl, original_pUnit, original_pTarget] = setup_data();
			int32_t nCount{};
			int32_t bInMediumRange{};
			int32_t bInFarRange{};
			int32_t bInCloseRange{};
			int32_t nMax{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pAiControl, &moo_pUnit, &moo_pTarget, nCount, bInMediumRange, bInFarRange, bInCloseRange, nMax);
			const auto original_result = original(&original_pGame, &original_pAiControl, &original_pUnit, &original_pTarget, nCount, bInMediumRange, bInFarRange, bInCloseRange, nMax);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCE450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIBAAL_MainSkillHandler, dll_base + 0x0009E450);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2AiControlStrc pAiControl{};
				D2UnitStrc pTarget{};
				D2AiCmdStrc pAiCmd{};
				
				return std::tuple{ pGame, pUnit, pAiControl, pTarget, pAiCmd };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pAiControl, moo_pTarget, moo_pAiCmd] = setup_data();
			auto [original_pGame, original_pUnit, original_pAiControl, original_pTarget, original_pAiCmd] = setup_data();
			int32_t nParam{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, &moo_pTarget, nParam, &moo_pAiCmd);
			original(&original_pGame, &original_pUnit, &original_pAiControl, &original_pTarget, nParam, &original_pAiCmd);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pAiCmd, original_pAiCmd, "Comparing pAiCmd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCEB70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn140_BaalCrabClone, dll_base + 0x0009EB70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2AiTickParamStrc pAiTickParam{};
				
				return std::tuple{ pGame, pUnit, pAiTickParam };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pAiTickParam] = setup_data();
			auto [original_pGame, original_pUnit, original_pAiTickParam] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			original(&original_pGame, &original_pUnit, &original_pAiTickParam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
}
