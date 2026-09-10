#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <QUESTS/ACT3/A3Q3.h>
#include <Units/Units.h>


TEST_SUITE("A3Q3Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA8DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_StatusFilterCallback, dll_base + 0x00078DC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA8F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_ActiveFilterCallback, dll_base + 0x00078F10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA8FC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_UnitIterate_SetGidbinnBroughtBackQuestState, dll_base + 0x00078FC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_InitQuestData, dll_base + 0x00079050);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9130" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback02_NpcDeactivate, dll_base + 0x00079130);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA91A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_UnitIterate_UpdateQuestStateFlags, dll_base + 0x000791A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_UnitIterate_StatusCyclerEx, dll_base + 0x00079260);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA92D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback00_NpcActivate, dll_base + 0x000792D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback03_ChangedLevel, dll_base + 0x00079490);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback11_ScrollMessage, dll_base + 0x00079540);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_UnitIterate_SetCompletionFlag, dll_base + 0x00079820);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA98A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback04_ItemPickedUp, dll_base + 0x000798A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9990" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_SeqCallback, dll_base + 0x00079990);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9A00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback14_PlayerJoinedGame, dll_base + 0x00079A00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9A30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback09_PlayerDroppedWithQuestItem, dll_base + 0x00079A30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9A70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback13_PlayerStartedGame, dll_base + 0x00079A70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9BA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction25_Gidbinn, dll_base + 0x00079BA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjInitFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9C30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction31_GidbinnDecoy, dll_base + 0x00079C30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9D50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_SpawnGidbinnBoss, dll_base + 0x00079D50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2QuestDataStrc pQuestData{};
				
				return std::tuple{ pGame, pQuestData };
			};
			
			// Input data
			auto [moo_pGame, moo_pQuestData] = setup_data();
			auto [original_pGame, original_pQuestData] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pQuestData);
			const auto original_result = original(&original_pGame, &original_pQuestData);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9E40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_Callback08_MonsterKilled, dll_base + 0x00079E40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9EF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_GetAltarCoordinates, dll_base + 0x00079EF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2CoordStrc pCoord{};
				
				return std::tuple{ pGame, pCoord };
			};
			
			// Input data
			auto [moo_pGame, moo_pCoord] = setup_data();
			auto [original_pGame, original_pCoord] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pCoord);
			const auto original_result = original(&original_pGame, &original_pCoord);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9F30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT3Q3_SetAltarMode, dll_base + 0x00079F30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCA9FA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction39_GidbinnAltar, dll_base + 0x00079FA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ObjInitFnStrc pOp{};
				
				return std::tuple{ pOp };
			};
			
			// Input data
			auto [moo_pOp] = setup_data();
			auto [original_pOp] = setup_data();

			// Call both implementations
			sut(&moo_pOp);
			original(&original_pOp);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
}
