#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <QUESTS/ACT1/A1Q5.h>
#include <Units/Units.h>


TEST_SUITE("A1Q5Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9CD00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction06_TowerTome, dll_base + 0x0006CD00);
		
		SUBCASE("")
		{
			// Input data
			D2ObjOperateFnStrc moo_pOp{};
			D2ObjOperateFnStrc original_pOp{};
			int32_t nOperate{};

			const auto setup_data = [](
				D2ObjOperateFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			auto moo_result = sut(&moo_pOp, nOperate);
			auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9CDA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_UnitIterate_StatusCyclerEx, dll_base + 0x0006CDA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9CE00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_UnitIterate_UpdateQuestStateFlags, dll_base + 0x0006CE00);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9CED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_ActiveFilterCallback, dll_base + 0x0006CED0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2UnitStrc moo_pPlayer{};
			D2BitBufferStrc moo_pQuestFlags{};
			D2UnitStrc moo_pNPC{};
			D2QuestDataStrc original_pQuest{};
			D2UnitStrc original_pPlayer{};
			D2BitBufferStrc original_pQuestFlags{};
			D2UnitStrc original_pNPC{};
			int32_t nNpcId{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest,
				D2UnitStrc& pPlayer,
				D2BitBufferStrc& pQuestFlags,
				D2UnitStrc& pNPC
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest, moo_pPlayer, moo_pQuestFlags, moo_pNPC);
			setup_data(original_pQuest, original_pPlayer, original_pQuestFlags, original_pNPC);

			// Call both implementations
			auto moo_result = sut(&moo_pQuest, nNpcId, &moo_pPlayer, &moo_pQuestFlags, &moo_pNPC);
			auto original_result = original(&original_pQuest, nNpcId, &original_pPlayer, &original_pQuestFlags, &original_pNPC);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9CF20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_UnitIterate_SetPrimaryGoalDone, dll_base + 0x0006CF20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, moo_pData);
			original(&original_pGame, &original_pUnit, original_pData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9CFD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_SpawnTowerChestMissiles, dll_base + 0x0006CFD0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2Act1Quest5Strc moo_pQuestDataEx{};
			D2QuestDataStrc original_pQuestData{};
			D2Act1Quest5Strc original_pQuestDataEx{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2Act1Quest5Strc& pQuestDataEx
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestDataEx);
			setup_data(original_pQuestData, original_pQuestDataEx);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestDataEx);
			original(&original_pQuestData, &original_pQuestDataEx);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestDataEx, original_pQuestDataEx, "Comparing pQuestDataEx");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9D2E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_InitQuestData, dll_base + 0x0006D2E0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestDataStrc original_pQuestData{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData);
			setup_data(original_pQuestData);

			// Call both implementations
			sut(&moo_pQuestData);
			original(&original_pQuestData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9D3B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_Callback11_ScrollMessage, dll_base + 0x0006D3B0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuestData{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestArg);
			setup_data(original_pQuestData, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9D5D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_UpdateUnitGUIDLists, dll_base + 0x0006D5D0);
		
		SUBCASE("")
		{
			// Input data
			D2Act1Quest5Strc moo_pQuestDataEx{};
			D2Act1Quest5Strc original_pQuestDataEx{};
			int32_t nUnitGUID{};
			int32_t a3{};

			const auto setup_data = [](
				D2Act1Quest5Strc& pQuestDataEx
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestDataEx);
			setup_data(original_pQuestDataEx);

			// Call both implementations
			auto moo_result = sut(&moo_pQuestDataEx, nUnitGUID, a3);
			auto original_result = original(&original_pQuestDataEx, nUnitGUID, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestDataEx, original_pQuestDataEx, "Comparing pQuestDataEx");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9D650" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_Callback10_PlayerLeavesGame, dll_base + 0x0006D650);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuestData{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestArg);
			setup_data(original_pQuestData, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9D6A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_Callback00_NpcActivate, dll_base + 0x0006D6A0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuestData{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestArg);
			setup_data(original_pQuestData, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9D830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_Callback03_ChangedLevel, dll_base + 0x0006D830);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuestData{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestArg);
			setup_data(original_pQuestData, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9D970" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_SeqCallback, dll_base + 0x0006D970);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestDataStrc original_pQuestData{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData);
			setup_data(original_pQuestData);

			// Call both implementations
			auto moo_result = sut(&moo_pQuestData);
			auto original_result = original(&original_pQuestData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9D9F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_Callback08_MonsterKilled, dll_base + 0x0006D9F0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuestData{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestArg);
			setup_data(original_pQuestData, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9DBE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_UnitIterate_SetRewardGranted, dll_base + 0x0006DBE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9DC80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_UnitIterate_AttachCompletionSound, dll_base + 0x0006DC80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9DD40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_UnitIterate_SetCompletionFlag, dll_base + 0x0006DD40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9DD90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_UnitIterate_SetPrimaryGoalDoneForPartyMembers, dll_base + 0x0006DD90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9DDE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_Timer_StatusCycler, dll_base + 0x0006DDE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2QuestDataStrc moo_pQuestData{};
			D2GameStrc original_pGame{};
			D2QuestDataStrc original_pQuestData{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2QuestDataStrc& pQuestData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pQuestData);
			setup_data(original_pGame, original_pQuestData);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pQuestData);
			auto original_result = original(&original_pGame, &original_pQuestData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9DE10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q5_Callback13_PlayerStartedGame, dll_base + 0x0006DE10);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuestData{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pQuestArg);
			setup_data(original_pQuestData, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9DEE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction04_TowerTome, dll_base + 0x0006DEE0);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9DF30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction47_CountessChest, dll_base + 0x0006DF30);
		
		SUBCASE("")
		{
			// Input data
			D2ObjInitFnStrc moo_pOp{};
			D2ObjInitFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjInitFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
}
