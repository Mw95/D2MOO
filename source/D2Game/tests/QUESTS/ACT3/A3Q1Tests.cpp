#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <QUESTS/ACT3/A3Q1.h>
#include <Units/Units.h>


TEST_SUITE("A3Q1Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA6E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_ActiveFilterCallback, dll_base + 0x00076E80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuest{};
				D2UnitStrc pPlayer{};
				D2BitBufferStrc pQuestFlags{};
				D2UnitStrc pNPC{};
				
				return std::tuple{ pQuest, pPlayer, pQuestFlags, pNPC };
			};
			
			// Input data
			auto [moo_pQuest, moo_pPlayer, moo_pQuestFlags, moo_pNPC] = setup_data();
			auto [original_pQuest, original_pPlayer, original_pQuestFlags, original_pNPC] = setup_data();
			int32_t nNpcId{};

			// Call both implementations
			const auto moo_result = sut(&moo_pQuest, nNpcId, &moo_pPlayer, &moo_pQuestFlags, &moo_pNPC);
			const auto original_result = original(&original_pQuest, nNpcId, &original_pPlayer, &original_pQuestFlags, &original_pNPC);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA6F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction28_LamEsenTome, dll_base + 0x00076F10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjOperateFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();
			int32_t nOperate{};

			// Call both implementations
			const auto moo_result = sut(&moo_pOp, nOperate);
			const auto original_result = original(&original_pOp, nOperate);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_UnitIterate_StatusCyclerEx, dll_base + 0x00077040);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA70B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback00_NpcActivate, dll_base + 0x000770B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback11_ScrollMessage, dll_base + 0x00077190);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA73B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_UnitIterate_UpdateQuestStateFlags, dll_base + 0x000773B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_UnitIterate_SetPrimaryGoalDone, dll_base + 0x00077420);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA74A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_UnitIterate_AddStatPointReward, dll_base + 0x000774A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA74F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_UnitIterate_SetCompletionFlag, dll_base + 0x000774F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pData);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback02_NpcDeactivate, dll_base + 0x00077530);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_InitQuestData, dll_base + 0x00077580);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				
				return std::tuple{ pQuestData };
			};
			
			// Input data
			auto [moo_pQuestData] = setup_data();
			auto [original_pQuestData] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData);
			original(&original_pQuestData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback03_ChangedLevel, dll_base + 0x00077670);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback04_ItemPickedUp, dll_base + 0x00077740);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA77D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback05_ItemDropped, dll_base + 0x000777D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback09_PlayerDroppedWithQuestItem, dll_base + 0x00077830);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback14_PlayerJoinedGame, dll_base + 0x00077870);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA78D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_Callback13_PlayerStartedGame, dll_base + 0x000778D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2QuestArgStrc pQuestArg{};
				
				return std::tuple{ pQuestData, pQuestArg };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pQuestArg] = setup_data();
			auto [original_pQuestData, original_pQuestArg] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pQuestArg);
			original(&original_pQuestData, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA79A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_SeqCallback, dll_base + 0x000779A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				
				return std::tuple{ pQuestData };
			};
			
			// Input data
			auto [moo_pQuestData] = setup_data();
			auto [original_pQuestData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pQuestData);
			const auto original_result = original(&original_pQuestData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_StatusFilterCallback, dll_base + 0x00077A10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuest{};
				D2UnitStrc pPlayer{};
				D2BitBufferStrc pGlobalFlags{};
				D2BitBufferStrc pFlags{};
				uint8_t pStatus{};
				
				return std::tuple{ pQuest, pPlayer, pGlobalFlags, pFlags, pStatus };
			};
			
			// Input data
			auto [moo_pQuest, moo_pPlayer, moo_pGlobalFlags, moo_pFlags, moo_pStatus] = setup_data();
			auto [original_pQuest, original_pPlayer, original_pGlobalFlags, original_pFlags, original_pStatus] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pQuest, &moo_pPlayer, &moo_pGlobalFlags, &moo_pFlags, &moo_pStatus);
			const auto original_result = original(&original_pQuest, &original_pPlayer, &original_pGlobalFlags, &original_pFlags, &original_pStatus);
			
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA7B40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q1_UnitIterate_CheckForTomeItem, dll_base + 0x00077B40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pData = nullptr;
			void* original_pData = nullptr;

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, moo_pData);
			original(&original_pGame, &original_pUnit, original_pData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
}
