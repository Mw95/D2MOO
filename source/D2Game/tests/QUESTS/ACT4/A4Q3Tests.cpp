#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <QUESTS/ACT4/A4Q3.h>
#include <Units/Units.h>


TEST_SUITE("A4Q3Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCAFF50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction48_HellForge, dll_base + 0x0007FF50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCAFFC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_UnitIterate_StatusCyclerEx, dll_base + 0x0007FFC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_UnitIterate_SetPrimaryGoalDone, dll_base + 0x00080030);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB00E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction49_HellForge, dll_base + 0x000800E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB03A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_UnitIterate_SetCompletionFlag, dll_base + 0x000803A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0400" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_ActiveFilterCallback, dll_base + 0x00080400);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_InitQuestData, dll_base + 0x00080460);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback04_ItemPickedUp, dll_base + 0x00080550);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB05C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_SeqCallback, dll_base + 0x000805C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0650" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback03_ChangedLevel, dll_base + 0x00080650);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB06D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_UnitIterate_UpdateQuestStateFlags, dll_base + 0x000806D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback11_ScrollMessage, dll_base + 0x00080760);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0920" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback00_NpcActivate, dll_base + 0x00080920);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0A80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback02_NpcDeactivate, dll_base + 0x00080A80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback09_PlayerDroppedWithQuestItem, dll_base + 0x00080AE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0B00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback14_PlayerJoinedGame, dll_base + 0x00080B00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback13_PlayerStartedGame, dll_base + 0x00080B20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_Callback08_MonsterKilled, dll_base + 0x00080C00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB0C40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT4Q3_CreateReward, dll_base + 0x00080C40);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2UnitStrc moo_pUnit{};
			D2QuestDataStrc original_pQuestData{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData, moo_pUnit);
			setup_data(original_pQuestData, original_pUnit);

			// Call both implementations
			sut(&moo_pQuestData, &moo_pUnit);
			original(&original_pQuestData, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
