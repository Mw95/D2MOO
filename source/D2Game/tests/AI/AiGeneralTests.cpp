#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <AI/AiGeneral.h>
#include <GAME/Game.h>
#include <Units/Units.h>


TEST_SUITE("AiGeneralTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCED00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_AllocAiControl, dll_base + 0x0009ED00);
		
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
			const auto moo_result = sut(&moo_pGame);
			const auto original_result = original(&original_pGame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCED40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_SetAiControlParam, dll_base + 0x0009ED40);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};
			int32_t nIndex{};
			int32_t nParamValue{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

			// Call both implementations
			sut(&moo_pMonster, nIndex, nParamValue);
			original(&original_pMonster, nIndex, nParamValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCED80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetAiControlParam, dll_base + 0x0009ED80);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nIndex{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nIndex);
			const auto original_result = original(&original_pUnit, nIndex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCEDC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_AllocAiCommand, dll_base + 0x0009EDC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCEE40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_FreeCurrentAiCommand, dll_base + 0x0009EE40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCEEB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_FreeAllAiCommands, dll_base + 0x0009EEB0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCEEF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetCurrentAiCommandFromUnit, dll_base + 0x0009EEF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCEF10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetAiCommandFromParam, dll_base + 0x0009EF10);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nCmdParam{};
			int32_t bSet{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nCmdParam, bSet);
			const auto original_result = original(&original_pUnit, nCmdParam, bSet);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCEF70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_AllocCommandsForMinions, dll_base + 0x0009EF70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiCmdStrc moo_pAiCmd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiCmdStrc original_pAiCmd{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiCmdStrc& pAiCmd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiCmd);
			setup_data(original_pGame, original_pUnit, original_pAiCmd);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pAiCmd);
			original(&original_pGame, &original_pUnit, &original_pAiCmd);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiCmd, original_pAiCmd, "Comparing pAiCmd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_CopyAiCommand, dll_base + 0x0009F050);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiCmdStrc moo_pAiCmd{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiCmdStrc original_pAiCmd{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiCmdStrc& pAiCmd
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiCmd);
			setup_data(original_pGame, original_pUnit, original_pAiCmd);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiCmd);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiCmd);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiCmd, original_pAiCmd, "Comparing pAiCmd");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_SetCurrentAiCommand, dll_base + 0x0009F090);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nCmdParam{};
			int32_t bSet{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nCmdParam, bSet);
			const auto original_result = original(&original_pGame, &original_pUnit, nCmdParam, bSet);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_FreeAiControl, dll_base + 0x0009F190);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2AiControlStrc moo_pAiControl{};
			D2GameStrc original_pGame{};
			D2AiControlStrc original_pAiControl{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2AiControlStrc& pAiControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pAiControl);
			setup_data(original_pGame, original_pAiControl);

			// Call both implementations
			sut(&moo_pGame, &moo_pAiControl);
			original(&original_pGame, &original_pAiControl);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetMapAiFromUnit, dll_base + 0x0009F240);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_SetOwnerData, dll_base + 0x0009F270);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nOwnerGUID{};
			int32_t nOwnerType{};
			int32_t bSetFlag1{};
			int32_t bSetFlag2{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nOwnerGUID, nOwnerType, bSetFlag1, bSetFlag2);
			original(&original_pGame, &original_pUnit, nOwnerGUID, nOwnerType, bSetFlag1, bSetFlag2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF2D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetOwnerData, dll_base + 0x0009F2D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			int32_t moo_pUnitGUID{};
			int32_t moo_pUnitType{};
			D2UnitStrc original_pUnit{};
			int32_t original_pUnitGUID{};
			int32_t original_pUnitType{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				int32_t& pUnitGUID,
				int32_t& pUnitType
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pUnitGUID, moo_pUnitType);
			setup_data(original_pUnit, original_pUnitGUID, original_pUnitType);

			// Call both implementations
			sut(&moo_pUnit, &moo_pUnitGUID, &moo_pUnitType);
			original(&original_pUnit, &original_pUnitGUID, &original_pUnitType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pUnitGUID, original_pUnitGUID, "Comparing pUnitGUID");
			SKIP_MOO_CHECK_EQ(moo_pUnitType, original_pUnitType, "Comparing pUnitType");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF320" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetMinionOwner, dll_base + 0x0009F320);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_AllocMinionList, dll_base + 0x0009F360);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pMinion{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pMinion{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pMinion
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pMinion);
			setup_data(original_pGame, original_pUnit, original_pMinion);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pMinion);
			original(&original_pGame, &original_pUnit, &original_pMinion);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMinion, original_pMinion, "Comparing pMinion");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF3C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_FreeMinionList, dll_base + 0x0009F3C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF4B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCCF4B0, dll_base + 0x0009F4B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF590" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_FreeAllMinionLists, dll_base + 0x0009F590);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2MinionListStrc moo_pMinionList{};
			D2GameStrc original_pGame{};
			D2MinionListStrc original_pMinionList{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2MinionListStrc& pMinionList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMinionList);
			setup_data(original_pGame, original_pMinionList);

			// Call both implementations
			sut(&moo_pGame, &moo_pMinionList);
			original(&original_pGame, &original_pMinionList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMinionList, original_pMinionList, "Comparing pMinionList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF5C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_ExecuteCallbackOnMinions, dll_base + 0x0009F5C0);
		
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
			sut(&moo_pUnit, moo_a2, moo_a3, nullptr);
			original(&original_pUnit, original_a2, original_a3, nullptr);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetAiControlInfo, dll_base + 0x0009F680);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			int32_t moo_pOwnerGUID{};
			int32_t moo_pOwnerType{};
			int32_t moo_pAiControlFlag1{};
			int32_t moo_pAiControlFlag2{};
			D2MinionListStrc* moo_ppMinionList{};
			D2UnitStrc original_pUnit{};
			int32_t original_pOwnerGUID{};
			int32_t original_pOwnerType{};
			int32_t original_pAiControlFlag1{};
			int32_t original_pAiControlFlag2{};
			D2MinionListStrc* original_ppMinionList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				int32_t& pOwnerGUID,
				int32_t& pOwnerType,
				int32_t& pAiControlFlag1,
				int32_t& pAiControlFlag2,
				D2MinionListStrc*& ppMinionList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pOwnerGUID, moo_pOwnerType, moo_pAiControlFlag1, moo_pAiControlFlag2, moo_ppMinionList);
			setup_data(original_pUnit, original_pOwnerGUID, original_pOwnerType, original_pAiControlFlag1, original_pAiControlFlag2, original_ppMinionList);

			// Call both implementations
			sut(&moo_pUnit, &moo_pOwnerGUID, &moo_pOwnerType, &moo_pAiControlFlag1, &moo_pAiControlFlag2, &moo_ppMinionList);
			original(&original_pUnit, &original_pOwnerGUID, &original_pOwnerType, &original_pAiControlFlag1, &original_pAiControlFlag2, &original_ppMinionList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pOwnerGUID, original_pOwnerGUID, "Comparing pOwnerGUID");
			SKIP_MOO_CHECK_EQ(moo_pOwnerType, original_pOwnerType, "Comparing pOwnerType");
			SKIP_MOO_CHECK_EQ(moo_pAiControlFlag1, original_pAiControlFlag1, "Comparing pAiControlFlag1");
			SKIP_MOO_CHECK_EQ(moo_pAiControlFlag2, original_pAiControlFlag2, "Comparing pAiControlFlag2");
			SKIP_MOO_CHECK_EQ(moo_ppMinionList, original_ppMinionList, "Comparing ppMinionList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_SetAiControlInfo, dll_base + 0x0009F710);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2MinionListStrc moo_pMinionList{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2MinionListStrc original_pMinionList{};
			DWORD nOwnerGUID{};
			DWORD nOwnerType{};
			int32_t bSetFlag1{};
			int32_t bSetFlag2{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2MinionListStrc& pMinionList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pMinionList);
			setup_data(original_pGame, original_pUnit, original_pMinionList);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nOwnerGUID, nOwnerType, bSetFlag1, bSetFlag2, &moo_pMinionList);
			original(&original_pGame, &original_pUnit, nOwnerGUID, nOwnerType, bSetFlag1, bSetFlag2, &original_pMinionList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMinionList, original_pMinionList, "Comparing pMinionList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF7C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_UpdateMinionList, dll_base + 0x0009F7C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF9B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIGENERAL_GetMinionSpawnClassId, dll_base + 0x0009F9B0);
		
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
}
