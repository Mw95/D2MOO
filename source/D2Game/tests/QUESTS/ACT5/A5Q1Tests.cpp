#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <QUESTS/ACT5/A5Q1.h>
#include <Units/Units.h>


TEST_SUITE("A5Q1Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1200" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_UnitIterate_SetPrimaryGoalDone, dll_base + 0x00081200);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_ActiveFilterCallback, dll_base + 0x00081280);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_InitQuestData, dll_base + 0x00081300);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB13D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_StatusFilterCallback, dll_base + 0x000813D0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2UnitStrc moo_pPlayer{};
			D2BitBufferStrc moo_pGlobalFlags{};
			D2BitBufferStrc moo_pFlags{};
			uint8_t moo_pStatus{};
			D2QuestDataStrc original_pQuest{};
			D2UnitStrc original_pPlayer{};
			D2BitBufferStrc original_pGlobalFlags{};
			D2BitBufferStrc original_pFlags{};
			uint8_t original_pStatus{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest,
				D2UnitStrc& pPlayer,
				D2BitBufferStrc& pGlobalFlags,
				D2BitBufferStrc& pFlags,
				uint8_t& pStatus
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest, moo_pPlayer, moo_pGlobalFlags, moo_pFlags, moo_pStatus);
			setup_data(original_pQuest, original_pPlayer, original_pGlobalFlags, original_pFlags, original_pStatus);

			// Call both implementations
			auto moo_result = sut(&moo_pQuest, &moo_pPlayer, &moo_pGlobalFlags, &moo_pFlags, &moo_pStatus);
			auto original_result = original(&original_pQuest, &original_pPlayer, &original_pGlobalFlags, &original_pFlags, &original_pStatus);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pGlobalFlags, original_pGlobalFlags, "Comparing pGlobalFlags");
			SKIP_MOO_CHECK_EQ(moo_pFlags, original_pFlags, "Comparing pFlags");
			SKIP_MOO_CHECK_EQ(moo_pStatus, original_pStatus, "Comparing pStatus");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_Callback02_NpcDeactivate, dll_base + 0x00081470);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB14D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_UnitIterate_StatusCyclerEx, dll_base + 0x000814D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_Callback11_ScrollMessage, dll_base + 0x00081540);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB16B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_UnitIterate_UpdateQuestStateFlags, dll_base + 0x000816B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_Callback00_NpcActivate, dll_base + 0x00081740);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_Callback08_MonsterKilled, dll_base + 0x00081830);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB18E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_UnitIterate_SetRewardPending, dll_base + 0x000818E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB19A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_UnitIterate_SetPrimaryGoalDoneForPartyMembers, dll_base + 0x000819A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB19F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_UnitIterate_SetCompletionFlag, dll_base + 0x000819F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1A60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_UnitIterate_AttachCompletionSound, dll_base + 0x00081A60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1AA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_Callback03_ChangedLevel, dll_base + 0x00081AA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_SeqCallback, dll_base + 0x00081BA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_Callback13_PlayerStartedGame, dll_base + 0x00081C10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_SetRewardGranted, dll_base + 0x00081D10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1D90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction71_LarzukStandard, dll_base + 0x00081D90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB1E60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_OnSiegeBossActivated, dll_base + 0x00081E60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "Inlined in D2Game.0x6FC975A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q1_ChangeLarzukMapAI, dll_base + 0x000675A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2MapAIStrc moo_pMapAi{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2MapAIStrc original_pMapAi{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2MapAIStrc& pMapAi
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pMapAi);
			setup_data(original_pGame, original_pUnit, original_pMapAi);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pMapAi);
			original(&original_pGame, &original_pUnit, &original_pMapAi);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMapAi, original_pMapAi, "Comparing pMapAi");
		}
	}
}
