#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			void* moo_ppUnitArg = nullptr;
			void* original_ppUnitArg = nullptr;
			void* moo_pCounterArg = nullptr;
			void* original_pCounterArg = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiTickParamStrc original_pAiTickParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiTickParamStrc& pAiTickParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiTickParam);
			setup_data(original_pGame, original_pUnit, original_pAiTickParam);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiTickParamStrc original_pAiTickParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiTickParamStrc& pAiTickParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiTickParam);
			setup_data(original_pGame, original_pUnit, original_pAiTickParam);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			int32_t moo_pMax{};
			int32_t moo_pCount{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t original_pMax{};
			int32_t original_pCount{};
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				int32_t& pMax,
				int32_t& pCount
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pMax, moo_pCount);
			setup_data(original_pGame, original_pUnit, original_pMax, original_pCount);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pMax, &moo_pCount, moo_pArgs, nullptr);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pMax, &original_pCount, original_pArgs, nullptr);
			
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
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pArgs = nullptr;
			void* original_pArgs = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pTarget);
			setup_data(original_pUnit, original_pTarget);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, &moo_pTarget, moo_pArgs);
			auto original_result = original(&original_pUnit, &original_pTarget, original_pArgs);
			
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
			// Input data
			D2UnitStrc moo_pBaal{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc original_pBaal{};
			D2UnitStrc original_pTarget{};

			const auto setup_data = [](
				D2UnitStrc& pBaal,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pBaal, moo_pTarget);
			setup_data(original_pBaal, original_pTarget);

			// Call both implementations
			auto moo_result = sut(&moo_pBaal, &moo_pTarget);
			auto original_result = original(&original_pBaal, &original_pTarget);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiControlStrc moo_pAiControl{};
			D2UnitStrc moo_pTarget{};
			D2AiCmdStrc moo_pAiCmd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiControlStrc original_pAiControl{};
			D2UnitStrc original_pTarget{};
			D2AiCmdStrc original_pAiCmd{};
			int32_t nMax{};
			int32_t nCount{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiControlStrc& pAiControl,
				D2UnitStrc& pTarget,
				D2AiCmdStrc& pAiCmd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiControl, moo_pTarget, moo_pAiCmd);
			setup_data(original_pGame, original_pUnit, original_pAiControl, original_pTarget, original_pAiCmd);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, &moo_pTarget, nMax, nCount, &moo_pAiCmd);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pAiControl, &original_pTarget, nMax, nCount, &original_pAiCmd);
			
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCE100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AI_GetRandomArrayIndex, dll_base + 0x0009E100);
		
		SUBCASE("")
		{
			// Input data
			int32_t moo_pArray{};
			D2UnitStrc moo_pUnit{};
			int32_t original_pArray{};
			D2UnitStrc original_pUnit{};
			int32_t nArraySize{};
			int32_t nDefaultValue{};

			const auto setup_data = [](
				int32_t& pArray,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pArray, moo_pUnit);
			setup_data(original_pArray, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pArray, nArraySize, &moo_pUnit, nDefaultValue);
			auto original_result = original(&original_pArray, nArraySize, &original_pUnit, nDefaultValue);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2AiControlStrc moo_pAiControl{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2AiControlStrc original_pAiControl{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nCount{};
			int32_t bInMediumRange{};
			int32_t bInFarRange{};
			int32_t bInCloseRange{};
			int32_t nMax{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2AiControlStrc& pAiControl,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAiControl, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pAiControl, original_pUnit, original_pTarget);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pAiControl, &moo_pUnit, &moo_pTarget, nCount, bInMediumRange, bInFarRange, bInCloseRange, nMax);
			auto original_result = original(&original_pGame, &original_pAiControl, &original_pUnit, &original_pTarget, nCount, bInMediumRange, bInFarRange, bInCloseRange, nMax);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiControlStrc moo_pAiControl{};
			D2UnitStrc moo_pTarget{};
			D2AiCmdStrc moo_pAiCmd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiControlStrc original_pAiControl{};
			D2UnitStrc original_pTarget{};
			D2AiCmdStrc original_pAiCmd{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiControlStrc& pAiControl,
				D2UnitStrc& pTarget,
				D2AiCmdStrc& pAiCmd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiControl, moo_pTarget, moo_pAiCmd);
			setup_data(original_pGame, original_pUnit, original_pAiControl, original_pTarget, original_pAiCmd);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiTickParamStrc original_pAiTickParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiTickParamStrc& pAiTickParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiTickParam);
			setup_data(original_pGame, original_pUnit, original_pAiTickParam);

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
