#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <QUESTS/ACT5/A5Q4.h>
#include <Units/Units.h>


TEST_SUITE("A5Q4Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB59B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_UnitIterate_SetPrimaryGoalDone, dll_base + 0x000859B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB5A80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_ActiveFilterCallback, dll_base + 0x00085A80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB5C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_InitQuestData, dll_base + 0x00085C00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB5CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_StatusFilterCallback, dll_base + 0x00085CD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB5D60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_Callback02_NpcDeactivate, dll_base + 0x00085D60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB5E70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_UnitIterate_StatusCyclerEx, dll_base + 0x00085E70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB5EE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_SeqCallback, dll_base + 0x00085EE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB5F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_Callback11_ScrollMessage, dll_base + 0x00085F70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_UnitIterate_UpdateQuestStateFlags, dll_base + 0x00086100);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_Callback00_NpcActivate, dll_base + 0x00086190);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6320" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_Callback08_MonsterKilled, dll_base + 0x00086320);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB63F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_UnitIterate_SetRewardPending, dll_base + 0x000863F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6500" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_UnitIterate_SetPrimaryGoalDoneForPartyMembers, dll_base + 0x00086500);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_UnitIterate_SetCompletionFlag, dll_base + 0x00086550);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB65C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_UnitIterate_AttachCompletionSound, dll_base + 0x000865C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_Timer_StatusCycler, dll_base + 0x00086600);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_Callback13_PlayerStartedGame, dll_base + 0x00086630);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_Callback03_ChangedLevel, dll_base + 0x00086750);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB67C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_SetRewardGranted, dll_base + 0x000867C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_OnNihlathakActivated, dll_base + 0x00086800);
		
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
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB6840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT5Q4_AnyaOpenPortal, dll_base + 0x00086840);
		
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
}
