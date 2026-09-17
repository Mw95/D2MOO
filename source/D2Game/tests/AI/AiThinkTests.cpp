#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <AI/AiGeneral.h>
#include <AI/AiThink.h>
#include <D2Skills.h>
#include <GAME/Game.h>
#include <Units/Units.h>


TEST_SUITE("AiThinkTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1660" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState02_6FCD1660, dll_base + 0x000A1660);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn002_Skeleton, dll_base + 0x000A1750);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn003_Zombie, dll_base + 0x000A1880);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1990" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn004_Bighead, dll_base + 0x000A1990);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn005_BloodHawk, dll_base + 0x000A1BA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1D50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn006_Fallen, dll_base + 0x000A1D50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD2220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn007_Brute, dll_base + 0x000A2220);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD2370" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn008_SandRaider, dll_base + 0x000A2370);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD2680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_SandRaider, dll_base + 0x000A2680);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD27A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn009_Wraith, dll_base + 0x000A27A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD2850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn010_CorruptRogue, dll_base + 0x000A2850);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD2A00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn011_Baboon, dll_base + 0x000A2A00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD2E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn014_QuillRat, dll_base + 0x000A2E80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD2FF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn013_FallenShaman, dll_base + 0x000A2FF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD32E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_FallenShaman, dll_base + 0x000A32E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD34A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk015_6FCD34A0, dll_base + 0x000A34A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD3540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn015_SandMaggot, dll_base + 0x000A3540);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD3900" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn016_ClawViper, dll_base + 0x000A3900);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD3B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn142_ClawViperEx, dll_base + 0x000A3B90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD3E70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn017_SandLeaper, dll_base + 0x000A3E70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD4050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn018_PantherWoman, dll_base + 0x000A4050);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD41F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_Panther, dll_base + 0x000A41F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD4390" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn012_019_Goatman_Swarm, dll_base + 0x000A4390);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD4440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn020_Scarab, dll_base + 0x000A4440);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD4720" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn021_Mummy, dll_base + 0x000A4720);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD48B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn022_GreaterMummy, dll_base + 0x000A48B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD4C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_GreaterMummy, dll_base + 0x000A4C10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD4DD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn023_Vulture, dll_base + 0x000A4DD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD55D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCD55D0, dll_base + 0x000A55D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD5710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_Vulture, dll_base + 0x000A5710);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD5850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn024_Mosquito, dll_base + 0x000A5850);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD6960" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_UnitFindCallback_Willowisp, dll_base + 0x000A6960);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitFindArgStrc moo_pUnitFindArg{};
			D2UnitStrc original_pUnit{};
			D2UnitFindArgStrc original_pUnitFindArg{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitFindArgStrc& pUnitFindArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pUnitFindArg);
			setup_data(original_pUnit, original_pUnitFindArg);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pUnitFindArg);
			const auto original_result = original(&original_pUnit, &original_pUnitFindArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pUnitFindArg, original_pUnitFindArg, "Comparing pUnitFindArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD69E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn026_Arach, dll_base + 0x000A69E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD6D60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn027_ThornHulk, dll_base + 0x000A6D60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD6FD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn028_Vampire, dll_base + 0x000A6FD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD76F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk029_6FCD76F0, dll_base + 0x000A76F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD7760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn029_BatDemon, dll_base + 0x000A7760);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD7BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn030_Fetish, dll_base + 0x000A7BA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD7EB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn033_HellMeteor, dll_base + 0x000A7EB0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD8090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn034_Andariel, dll_base + 0x000A8090);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD8260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn035_CorruptArcher, dll_base + 0x000A8260);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD85B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn036_CorruptLancer, dll_base + 0x000A85B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD88C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn037_SkeletonBow, dll_base + 0x000A88C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD8A60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn038_MaggotLarva, dll_base + 0x000A8A60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD8B60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn039_PinHead, dll_base + 0x000A8B60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD8D20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn040_MaggotEgg, dll_base + 0x000A8D20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD8E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk043_045_121_6FCD8E10, dll_base + 0x000A8E10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD8E30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn043_FoulCrowNest, dll_base + 0x000A8E30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD8FE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn044_Duriel, dll_base + 0x000A8FE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD91F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn045_Sarcophagus, dll_base + 0x000A91F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD93A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn046_ElementalBeast, dll_base + 0x000A93A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD94D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn047_FlyingScimitar, dll_base + 0x000A94D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD9640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn048_ZakarumZealot, dll_base + 0x000A9640);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD9A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn049_ZakarumPriest, dll_base + 0x000A9A10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD9F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_ZakarumPriest, dll_base + 0x000A9F10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDA0C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_FindTargetForMephisto, dll_base + 0x000AA0C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2MonStatsTxt moo_pMonStatsTxtRecord{};
			D2UnitStrc moo_a4{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2MonStatsTxt original_pMonStatsTxtRecord{};
			D2UnitStrc original_a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2MonStatsTxt& pMonStatsTxtRecord,
				D2UnitStrc& a4
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pMonStatsTxtRecord, moo_a4);
			setup_data(original_pGame, original_pUnit, original_pMonStatsTxtRecord, original_a4);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pMonStatsTxtRecord, &moo_a4);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pMonStatsTxtRecord, &original_a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMonStatsTxtRecord, original_pMonStatsTxtRecord, "Comparing pMonStatsTxtRecord");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDA190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_Mephisto, dll_base + 0x000AA190);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDA300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn050_Mephisto, dll_base + 0x000AA300);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDA910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk052_6FCDA910, dll_base + 0x000AA910);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDAAA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn052_FrogDemon, dll_base + 0x000AAAA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDAFC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn053_Summoner, dll_base + 0x000AAFC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDB3E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn055_Izual, dll_base + 0x000AB3E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDB720" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn056_Tentacle, dll_base + 0x000AB720);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDBAA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn057_TentacleHead, dll_base + 0x000ABAA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDBCE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn063_GargoyleTrap, dll_base + 0x000ABCE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDBF20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn064_SkeletonMage, dll_base + 0x000ABF20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDC170" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState04_6FCDC170, dll_base + 0x000AC170);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDC1C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn065_FetishShaman, dll_base + 0x000AC1C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDC420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_FetishShaman, dll_base + 0x000AC420);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDC600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn066_SandMaggotQueen, dll_base + 0x000AC600);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDC840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn068_VileMother, dll_base + 0x000AC840);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDCBF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn069_VileDog, dll_base + 0x000ACBF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDCCD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn070_FingerMage, dll_base + 0x000ACCD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDD060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn071_Regurgitator, dll_base + 0x000AD060);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDD5C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_Regurgitator, dll_base + 0x000AD5C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDD790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn072_DoomKnight, dll_base + 0x000AD790);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDD850" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn073_AbyssKnight, dll_base + 0x000AD850);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDDB10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn074_OblivionKnight, dll_base + 0x000ADB10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDDFA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_OblivionKnight, dll_base + 0x000ADFA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDE150" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn075_QuillMother, dll_base + 0x000AE150);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDE2B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn076_EvilHole, dll_base + 0x000AE2B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDE4D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn077_TrapMissile, dll_base + 0x000AE4D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDE570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn078_TrapRightArrow, dll_base + 0x000AE570);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDE710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn079_TrapLeftArrow, dll_base + 0x000AE710);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDE8B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn080_092_TrapPoison_TrapNova, dll_base + 0x000AE8B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDE960" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn087_TrapMelee, dll_base + 0x000AE960);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDE9E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn082_InvisoSpawner, dll_base + 0x000AE9E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDEAF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn083_MosquitoNest, dll_base + 0x000AEAF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDEC70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk084_6FCDEC70, dll_base + 0x000AEC70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDECE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn084_BoneWall, dll_base + 0x000AECE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDED10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn085_HighPriest, dll_base + 0x000AED10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDF2E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_HighPriest, dll_base + 0x000AF2E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDF410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn094_DesertTurret, dll_base + 0x000AF410);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDF780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn089_Megademon, dll_base + 0x000AF780);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDFA50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn093_ArcaneTower, dll_base + 0x000AFA50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDFB80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn095_PantherJavelin, dll_base + 0x000AFB80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCDFD50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn096_FetishBlowgun, dll_base + 0x000AFD50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn114_ReanimatedHorde, dll_base + 0x000B0050);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn113_SiegeTower, dll_base + 0x000B0220);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_SiegeBeast, dll_base + 0x000B0430);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn115_SiegeBeast, dll_base + 0x000B0610);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0960" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_GetSquaredDistance, dll_base + 0x000B0960);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			SKIP_MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0A50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn116_Minion, dll_base + 0x000B0A50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn117_SuicideMinion, dll_base + 0x000B0C10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn118_Succubus, dll_base + 0x000B0CD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE0FE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn119_SuccubusWitch, dll_base + 0x000B0FE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE1480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState14_6FCE1480, dll_base + 0x000B1480);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE1550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn120_Overseer, dll_base + 0x000B1550);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE1910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_Overseer_Nihlathak, dll_base + 0x000B1910);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE1B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn121_MinionSpawner, dll_base + 0x000B1B90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE1CA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_MinionSpawner, dll_base + 0x000B1CA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE1D30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState16_6FCE1D30, dll_base + 0x000B1D30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE1DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState16_6FCE1DC0, dll_base + 0x000B1DC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE2080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk122_6FCE2080, dll_base + 0x000B2080);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE2090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn122_Imp, dll_base + 0x000B2090);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE2570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn123_Catapult, dll_base + 0x000B2570);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE25D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn124_FrozenHorror, dll_base + 0x000B25D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE2760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn125_BloodLord, dll_base + 0x000B2760);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE28A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn097_Spirit, dll_base + 0x000B28A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE28F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn098_Smith, dll_base + 0x000B28F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE2960" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn067_NecroPet, dll_base + 0x000B2960);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE2BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_PetMove_6FCE2BA0, dll_base + 0x000B2BA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pUnit{};
			int32_t a4{};
			int32_t bRun{};
			int32_t nVelocity{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pOwner,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pOwner, moo_pUnit);
			setup_data(original_pGame, original_pOwner, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pOwner, &moo_pUnit, a4, bRun, nVelocity, a7);
			const auto original_result = original(&original_pGame, &original_pOwner, &original_pUnit, a4, bRun, nVelocity, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE34B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE34B0, dll_base + 0x000B34B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE34E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE34E0, dll_base + 0x000B34E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc moo_pOwner{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			D2UnitStrc original_pOwner{};
			D2AiTickParamStrc original_pAiTickParam{};
			int32_t a5{};
			int32_t a7{};
			int32_t a8{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget,
				D2UnitStrc& pOwner,
				D2AiTickParamStrc& pAiTickParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget, moo_pOwner, moo_pAiTickParam);
			setup_data(original_pGame, original_pUnit, original_pTarget, original_pOwner, original_pAiTickParam);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, &moo_pOwner, a5, &moo_pAiTickParam, a7, a8);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, &original_pOwner, a5, &original_pAiTickParam, a7, a8);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE3740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE3740, dll_base + 0x000B3740);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE39E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn061_Hireable, dll_base + 0x000B39E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE3EE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PETAI_PetMove_6FCE3EE0, dll_base + 0x000B3EE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pUnit{};
			int32_t eMotionType{};
			int32_t bRun{};
			int32_t nSpeed{};
			BYTE bSteps{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pOwner,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pOwner, moo_pUnit);
			setup_data(original_pGame, original_pOwner, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pOwner, &moo_pUnit, eMotionType, bRun, nSpeed, bSteps);
			const auto original_result = original(&original_pGame, &original_pOwner, &original_pUnit, eMotionType, bRun, nSpeed, bSteps);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE4610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE4610, dll_base + 0x000B4610);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc moo_pTarget{};
			D2SeedStrc moo_pSeed{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pOwner{};
			D2UnitStrc original_pTarget{};
			D2SeedStrc original_pSeed{};
			D2AiTickParamStrc original_pAiTickParam{};
			int32_t nClassId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pOwner,
				D2UnitStrc& pTarget,
				D2SeedStrc& pSeed,
				D2AiTickParamStrc& pAiTickParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pOwner, moo_pTarget, moo_pSeed, moo_pAiTickParam);
			setup_data(original_pGame, original_pUnit, original_pOwner, original_pTarget, original_pSeed, original_pAiTickParam);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nClassId, &moo_pOwner, &moo_pTarget, &moo_pSeed, &moo_pAiTickParam);
			original(&original_pGame, &original_pUnit, nClassId, &original_pOwner, &original_pTarget, &original_pSeed, &original_pAiTickParam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE4830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE4830, dll_base + 0x000B4830);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2SeedStrc moo_pSeed{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			D2SeedStrc original_pSeed{};
			int32_t nMonsterId{};
			int32_t nHirelingId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget,
				D2SeedStrc& pSeed
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget, moo_pSeed);
			setup_data(original_pGame, original_pUnit, original_pTarget, original_pSeed);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nMonsterId, nHirelingId, &moo_pTarget, &moo_pSeed);
			original(&original_pGame, &original_pUnit, nMonsterId, nHirelingId, &original_pTarget, &original_pSeed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE4B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState03_6FCE4B90, dll_base + 0x000B4B90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE4CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState03_6FCE4CC0, dll_base + 0x000B4CC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE4FD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE4FD0, dll_base + 0x000B4FD0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			void* moo_a2 = nullptr;
			void* original_a2 = nullptr;
			void* moo_a3 = nullptr;
			void* original_a3 = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, moo_a2, moo_a3);
			original(&original_pUnit, original_a2, original_a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE4FF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn090_Griswold, dll_base + 0x000B4FF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE5080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState13_6FCE5080, dll_base + 0x000B5080);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE5520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE5520, dll_base + 0x000B5520);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE5610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk129_6FCE5610, dll_base + 0x000B5610);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE5640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn129_GenericSpawner, dll_base + 0x000B5640);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE58D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk59_6FCE58D0, dll_base + 0x000B58D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE58E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn059_BloodRaven, dll_base + 0x000B58E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE5EE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE5EE0, dll_base + 0x000B5EE0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE61E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE61E0, dll_base + 0x000B61E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2MapAIPathPositionStrc moo_pPosition{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiTickParamStrc original_pAiTickParam{};
			D2MapAIPathPositionStrc original_pPosition{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiTickParamStrc& pAiTickParam,
				D2MapAIPathPositionStrc& pPosition
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiTickParam, moo_pPosition);
			setup_data(original_pGame, original_pUnit, original_pAiTickParam, original_pPosition);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam, &moo_pPosition);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam, &original_pPosition);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
			SKIP_MOO_CHECK_EQ(moo_pPosition, original_pPosition, "Comparing pPosition");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE6270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE6270, dll_base + 0x000B6270);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2MapAIPathPositionStrc moo_pPosition{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiTickParamStrc original_pAiTickParam{};
			D2MapAIPathPositionStrc original_pPosition{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiTickParamStrc& pAiTickParam,
				D2MapAIPathPositionStrc& pPosition
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiTickParam, moo_pPosition);
			setup_data(original_pGame, original_pUnit, original_pAiTickParam, original_pPosition);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam, &moo_pPosition);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam, &original_pPosition);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
			SKIP_MOO_CHECK_EQ(moo_pPosition, original_pPosition, "Comparing pPosition");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE6340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE6340, dll_base + 0x000B6340);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2MapAIPathPositionStrc moo_pPosition{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiTickParamStrc original_pAiTickParam{};
			D2MapAIPathPositionStrc original_pPosition{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiTickParamStrc& pAiTickParam,
				D2MapAIPathPositionStrc& pPosition
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiTickParam, moo_pPosition);
			setup_data(original_pGame, original_pUnit, original_pAiTickParam, original_pPosition);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam, &moo_pPosition);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam, &original_pPosition);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
			SKIP_MOO_CHECK_EQ(moo_pPosition, original_pPosition, "Comparing pPosition");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE64D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE64D0, dll_base + 0x000B64D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2MapAIPathPositionStrc moo_pPosition{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiTickParamStrc original_pAiTickParam{};
			D2MapAIPathPositionStrc original_pPosition{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiTickParamStrc& pAiTickParam,
				D2MapAIPathPositionStrc& pPosition
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiTickParam, moo_pPosition);
			setup_data(original_pGame, original_pUnit, original_pAiTickParam, original_pPosition);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam, &moo_pPosition);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam, &original_pPosition);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
			SKIP_MOO_CHECK_EQ(moo_pPosition, original_pPosition, "Comparing pPosition");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE6660" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn032_Npc, dll_base + 0x000B6660);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE69A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCE69A0, dll_base + 0x000B69A0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE6CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_ExecuteMapAiAction, dll_base + 0x000B6CD0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE6DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn054_NpcStationary, dll_base + 0x000B6DC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE6F80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn041_Towner, dll_base + 0x000B6F80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn081_JarJar, dll_base + 0x000B7070);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE73A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn031_NpcOutOfTown, dll_base + 0x000B73A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_SpawnNpcPortal, dll_base + 0x000B7640);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE77A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn060_GoodNpcRanged, dll_base + 0x000B77A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState06_6FCE7930, dll_base + 0x000B7930);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7A60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn062_TownRogue, dll_base + 0x000B7A60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7AC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn058_Navi, dll_base + 0x000B7AC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn001_100_Idle_Buffy, dll_base + 0x000B7C10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7C40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState09_6FCE7C40, dll_base + 0x000B7C40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7CF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState10_17_6FCE7CF0, dll_base + 0x000B7CF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState11_6FCE7E20, dll_base + 0x000B7E20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE7E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState11_6FCE7E80, dll_base + 0x000B7E80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE81B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_SpecialState12_6FCE81B0, dll_base + 0x000B81B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE82F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk051_6FCE82F0, dll_base + 0x000B82F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE83A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_GetTargetScore, dll_base + 0x000B83A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2AiCmdStrc moo_pAiCmd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			D2AiCmdStrc original_pAiCmd{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget,
				D2AiCmdStrc& pAiCmd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget, moo_pAiCmd);
			setup_data(original_pGame, original_pUnit, original_pTarget, original_pAiCmd);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, &moo_pAiCmd);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, &original_pAiCmd);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pAiCmd, original_pAiCmd, "Comparing pAiCmd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE86C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_GetTargetForBoss, dll_base + 0x000B86C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			int32_t moo_a3{};
			int32_t moo_pCounter{};
			D2AiCmdStrc moo_pAiCmd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t original_a3{};
			int32_t original_pCounter{};
			D2AiCmdStrc original_pAiCmd{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				int32_t& a3,
				int32_t& pCounter,
				D2AiCmdStrc& pAiCmd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_a3, moo_pCounter, moo_pAiCmd);
			setup_data(original_pGame, original_pUnit, original_a3, original_pCounter, original_pAiCmd);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_a3, &moo_pCounter, &moo_pAiCmd, nullptr);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_a3, &original_pCounter, &original_pAiCmd, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			SKIP_MOO_CHECK_EQ(moo_pCounter, original_pCounter, "Comparing pCounter");
			SKIP_MOO_CHECK_EQ(moo_pAiCmd, original_pAiCmd, "Comparing pAiCmd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE8950" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn051_Diablo, dll_base + 0x000B8950);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE97C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_CullPotentialTargetsForDiablo, dll_base + 0x000B97C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pTarget);
			setup_data(original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pTarget);
			const auto original_result = original(&original_pUnit, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn042_Vendor, dll_base + 0x000B9890);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE98E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn086_Hydra, dll_base + 0x000B98E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9980" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn099_TrappedSoul, dll_base + 0x000B9980);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9AF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn088_7TIllusion, dll_base + 0x000B9AF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn091_DarkWanderer, dll_base + 0x000B9BA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9CE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk101_104_6FCE9CE0, dll_base + 0x000B9CE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9D00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn101_AssassinSentry, dll_base + 0x000B9D00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9E60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_AssasinSentryHasLostTarget, dll_base + 0x000B9E60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiTickParamStrc original_pAiTickParam{};
			int32_t bDecreaseParam{};

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam, bDecreaseParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam, bDecreaseParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9FB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk102_6FCE9FB0, dll_base + 0x000B9FB0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCE9FD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn102_BladeCreeper, dll_base + 0x000B9FD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEA2A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn103_InvisoPet, dll_base + 0x000BA2A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEA490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn104_DeathSentry, dll_base + 0x000BA490);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEA680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk105_6FCEA680, dll_base + 0x000BA680);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEA6D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn105_ShadowWarrior, dll_base + 0x000BA6D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEAC10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_ShadowWarriorCheckUseSkill, dll_base + 0x000BAC10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pOwner{};
			D2SkillStrc moo_pSkill{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pOwner{};
			D2SkillStrc original_pSkill{};
			D2AiTickParamStrc original_pAiTickParam{};
			int32_t nSkillId{};
			int32_t bCombat{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pOwner,
				D2SkillStrc& pSkill,
				D2AiTickParamStrc& pAiTickParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pOwner, moo_pSkill, moo_pAiTickParam);
			setup_data(original_pGame, original_pUnit, original_pOwner, original_pSkill, original_pAiTickParam);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pOwner, &moo_pSkill, nSkillId, bCombat, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pOwner, &original_pSkill, nSkillId, bCombat, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEAF20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_ShadowMasterCheckTargetPetType, dll_base + 0x000BAF20);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nSkillId);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEAFE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk106_6FCEAFE0, dll_base + 0x000BAFE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEB1B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk143_6FCEB1B0, dll_base + 0x000BB1B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEB240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn106_143_ShadowMaster, dll_base + 0x000BB240);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEC840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_IsTargetKillableByShadowMaster, dll_base + 0x000BC840);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_a1{};
			D2UnitStrc moo_a2{};
			D2UnitStrc original_a1{};
			D2UnitStrc original_a2{};

			const auto setup_data = [](
				D2UnitStrc& a1,
				D2UnitStrc& a2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_a1, moo_a2);
			setup_data(original_a1, original_a2);

			// Call both implementations
			const auto moo_result = sut(&moo_a1, &moo_a2);
			const auto original_result = original(&original_a1, &original_a2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEC910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_ShadowMaster, dll_base + 0x000BC910);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCECBA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCECBA0, dll_base + 0x000BCBA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_a2{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2AiTickParamStrc moo_a9{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_a2{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			D2AiTickParamStrc original_a9{};
			WORD wSkillId{};
			int32_t a5{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& a2,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget,
				D2AiTickParamStrc& a9
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_a2, moo_pUnit, moo_pTarget, moo_a9);
			setup_data(original_pGame, original_a2, original_pUnit, original_pTarget, original_a9);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_a2, &moo_pUnit, wSkillId, a5, &moo_pTarget, nX, nY, &moo_a9);
			const auto original_result = original(&original_pGame, &original_a2, &original_pUnit, wSkillId, a5, &original_pTarget, nX, nY, &original_a9);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_a9, original_a9, "Comparing a9");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCECC40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk_110_111_6FCECC40, dll_base + 0x000BCC40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCECC50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn110_Vines, dll_base + 0x000BCC50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCECE50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn111_CycleOfLife, dll_base + 0x000BCE50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCED140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AI_Unk107_6FCED140, dll_base + 0x000BD140);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCED190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn107_Raven, dll_base + 0x000BD190);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "Inlined in D2Game.0x6FCED540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn108_Fenris, dll_base + 0x000BD540);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "Inlined in D2Game.0x6FCED540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn108_SpiritWolf, dll_base + 0x000BD540);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCED540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn108_DruidWolf, dll_base + 0x000BD540);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEDF70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn112_DruidBear, dll_base + 0x000BDF70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEE250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn109_Totem, dll_base + 0x000BE250);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEE450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn127_NpcBarb, dll_base + 0x000BE450);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEE6F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn126_CatapultSpotter, dll_base + 0x000BE6F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEEAD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn130_DeathMauler, dll_base + 0x000BEAD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEEC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn131_Wussie, dll_base + 0x000BEC00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEEE60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn128_Nihlathak, dll_base + 0x000BEE60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEF330" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn132_AncientStatue, dll_base + 0x000BF330);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEF3F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_AncientBarb1SkillHandler, dll_base + 0x000BF3F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEF730" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_AreUnitsInSameLevel, dll_base + 0x000BF730);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pTarget);
			setup_data(original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pTarget);
			const auto original_result = original(&original_pUnit, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "Inlined in D2Game.0x6FCEFBC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_AncientBarb2SkillHandler, dll_base + 0x000BFBC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEFA10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_AncientBarb3SkillHandler, dll_base + 0x000BFA10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEFBC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn133_Ancient, dll_base + 0x000BFBC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCEFBF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn134_BaalThrone, dll_base + 0x000BFBF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_BaalThroneSetAiParamFlag, dll_base + 0x000C0030);
		
		SUBCASE("")
		{
			// Input data
			D2AiTickParamStrc moo_pAiTickParam{};
			D2AiTickParamStrc original_pAiTickParam{};
			int32_t nFlag{};
			int32_t bSet{};

			const auto setup_data = [](
				D2AiTickParamStrc& pAiTickParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAiTickParam);
			setup_data(original_pAiTickParam);

			// Call both implementations
			sut(&moo_pAiTickParam, nFlag, bSet);
			original(&original_pAiTickParam, nFlag, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_BaalToStairs, dll_base + 0x000C0050);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn138_BaalToStairs, dll_base + 0x000C0090);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0180" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn136_BaalTaunt, dll_base + 0x000C0180);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF02D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn139_BaalTentacle, dll_base + 0x000C02D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn141_BaalMinion, dll_base + 0x000C0420);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_TargetCallback_PutridDefiler, dll_base + 0x000C0570);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF05B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_Fn137_PutridDefiler, dll_base + 0x000C05B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF06A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_GetSpecialStateFromAiControl, dll_base + 0x000C06A0);
		
		SUBCASE("")
		{
			// Input data
			D2AiControlStrc moo_pAiControl{};
			D2AiControlStrc original_pAiControl{};

			const auto setup_data = [](
				D2AiControlStrc& pAiControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAiControl);
			setup_data(original_pAiControl);

			// Call both implementations
			const auto moo_result = sut(&moo_pAiControl);
			const auto original_result = original(&original_pAiControl);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF06B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_SetAiControlParams, dll_base + 0x000C06B0);
		
		SUBCASE("")
		{
			// Input data
			D2AiControlStrc moo_pAiControl{};
			D2AiControlStrc original_pAiControl{};
			int32_t nParam0{};
			int32_t nParam1{};
			int32_t nParam2{};

			const auto setup_data = [](
				D2AiControlStrc& pAiControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAiControl);
			setup_data(original_pAiControl);

			// Call both implementations
			sut(&moo_pAiControl, nParam0, nParam1, nParam2);
			original(&original_pAiControl, nParam0, nParam1, nParam2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF06E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_CanUnitSwitchAi, dll_base + 0x000C06E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2MonStatsTxt moo_pMonStatsTxtRecord{};
			D2UnitStrc original_pUnit{};
			D2MonStatsTxt original_pMonStatsTxtRecord{};
			D2C_AiSpecialState nAiSpecialState{};
			int32_t bCheckIfSuperUnique{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2MonStatsTxt& pMonStatsTxtRecord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pMonStatsTxtRecord);
			setup_data(original_pUnit, original_pMonStatsTxtRecord);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pMonStatsTxtRecord, nAiSpecialState, bCheckIfSuperUnique);
			const auto original_result = original(&original_pUnit, &original_pMonStatsTxtRecord, nAiSpecialState, bCheckIfSuperUnique);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMonStatsTxtRecord, original_pMonStatsTxtRecord, "Comparing pMonStatsTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_GetAiTableRecord, dll_base + 0x000C0750);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF07D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITHINK_ExecuteAiFn, dll_base + 0x000C07D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiControlStrc moo_pAiControl{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiControlStrc original_pAiControl{};
			D2C_AiSpecialState nAiSpecialState{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiControlStrc& pAiControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiControl);
			setup_data(original_pGame, original_pUnit, original_pAiControl);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, nAiSpecialState);
			original(&original_pGame, &original_pUnit, &original_pAiControl, nAiSpecialState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0A70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction03_6FCF0A70, dll_base + 0x000C0A70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AICORE_MinionLeash_6FCF0D10, dll_base + 0x000C0D10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMonster{};
			D2AiTickParamStrc moo_pAiTickParam{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMonster{};
			D2AiTickParamStrc original_pAiTickParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMonster,
				D2AiTickParamStrc& pAiTickParam
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMonster, moo_pAiTickParam);
			setup_data(original_pGame, original_pMonster, original_pAiTickParam);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMonster, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pMonster, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "Inlined in D2Game.0x6FCF0E40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF0E40_inline, dll_base + 0x000C0E40);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF0E40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF0E40, dll_base + 0x000C0E40);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiTickParam);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiTickParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiTickParam, original_pAiTickParam, "Comparing pAiTickParam");
		}
	}
}
