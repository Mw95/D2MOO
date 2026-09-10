#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <QUESTS/ACT1/A1Q4.h>
#include <Units/Units.h>


TEST_SUITE("A1Q4Tests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC99D00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UpdateObjects, dll_base + 0x00069D00);
		
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
			char a2{};
			char a3{};

			// Call both implementations
			sut(&moo_pQuestData, a2, a3);
			original(&original_pQuestData, a2, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC99DE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_RemoveCainFromTristram, dll_base + 0x00069DE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC99E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SendPacket0x5DToClient, dll_base + 0x00069E80);
		
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
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC99EC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SetMonolithOrder, dll_base + 0x00069EC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC99F90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SetInvisibleObjectGUID, dll_base + 0x00069F90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2QuestDataStrc pQuestData{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pQuestData, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pQuestData, moo_pUnit] = setup_data();
			auto [original_pGame, original_pQuestData, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pQuestData, &moo_pUnit);
			original(&original_pGame, &original_pQuestData, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC99FC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_ActiveFilterCallback, dll_base + 0x00069FC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A0E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_SetPrimaryGoalDone, dll_base + 0x0006A0E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Timer_RemoveCainFromTristram, dll_base + 0x0006A160);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SpawnCainInTristram, dll_base + 0x0006A190);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_StatusCyclerEx, dll_base + 0x0006A3D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_SetPrimaryGoalDoneForPartyMembers, dll_base + 0x0006A440);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A4D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_SetCompletionFlag, dll_base + 0x0006A4D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_FindPlayersInTristram, dll_base + 0x0006A530);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction10_CainGibbet, dll_base + 0x0006A580);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A6E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction06_CairnStone, dll_base + 0x0006A6E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A7C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_OpenPortalToTristram, dll_base + 0x0006A7C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_SetEnterAreaFlag, dll_base + 0x0006A870);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9A8D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction09_Monolith, dll_base + 0x0006A8D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9ACD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction12_InifussTree, dll_base + 0x0006ACD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9AEA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback09_PlayerDroppedWithQuestItem, dll_base + 0x0006AEA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9AF10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_ResetInifussTree, dll_base + 0x0006AF10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9AFD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_UpdateQuestStateFlags, dll_base + 0x0006AFD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9B050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SendStoneOrderToClient, dll_base + 0x0006B050);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9B0F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_InitQuestData, dll_base + 0x0006B0F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9B250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback02_NpcDeactivate, dll_base + 0x0006B250);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9B2F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback11_ScrollMessage, dll_base + 0x0006B2F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9B610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback00_NpcActivate, dll_base + 0x0006B610);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9B930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback14_PlayerJoinedGame, dll_base + 0x0006B930);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9B970" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback10_PlayerLeavesGame, dll_base + 0x0006B970);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9B9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback03_ChangedLevel, dll_base + 0x0006B9D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9BC80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SpawnCainInTown, dll_base + 0x0006BC80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pGame, pRoom };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom] = setup_data();
			auto [original_pGame, original_pRoom] = setup_data();
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, nX, nY);
			original(&original_pGame, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9BEF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_AddPlayerGUIDs, dll_base + 0x0006BEF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9BF70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback04_ItemPickedUp, dll_base + 0x0006BF70);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9BFB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback06_6FC9BFB0, dll_base + 0x0006BFB0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9BFF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SeqCallback, dll_base + 0x0006BFF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C0A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback13_PlayerStartedGame, dll_base + 0x0006C0A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_Callback08_MonsterKilled, dll_base + 0x0006C220);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UnitIterate_SetCustom6Flag, dll_base + 0x0006C300);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction09_InifussTree, dll_base + 0x0006C340);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C3A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction13_InvisibleObject, dll_base + 0x0006C3A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UpdateQuestStateOnActChange, dll_base + 0x0006C460);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction54_CainStartPosition, dll_base + 0x0006C540);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C5B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_CreateCowPortal, dll_base + 0x0006C5B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C6E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction61_CainPortal, dll_base + 0x0006C6E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UpdatePortalInTown, dll_base + 0x0006C710);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2QuestDataStrc pQuestData{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pQuestData, pUnit };
			};
			
			// Input data
			auto [moo_pQuestData, moo_pUnit] = setup_data();
			auto [original_pQuestData, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pQuestData, &moo_pUnit);
			original(&original_pQuestData, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C7A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_GetCainPortalInTownCoordinates, dll_base + 0x0006C7A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2CoordStrc pCoord{};
				
				return std::tuple{ pGame, pUnit, pCoord };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pCoord] = setup_data();
			auto [original_pGame, original_pUnit, original_pCoord] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pCoord);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pCoord);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C7F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SpawnCainPortalOutsideTown, dll_base + 0x0006C7F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_GetCainPortalOutsideTownCoordinates, dll_base + 0x0006C930);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2CoordStrc pCoord{};
				
				return std::tuple{ pGame, pUnit, pCoord };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pCoord] = setup_data();
			auto [original_pGame, original_pUnit, original_pCoord] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pCoord);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pCoord);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C990" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_UpdateCainPortalCoordinates, dll_base + 0x0006C990);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9C9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_SpawnCainPortalInTown, dll_base + 0x0006C9D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9CBE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_OnCainInTownActivated, dll_base + 0x0006CBE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC9CC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ACT1Q4_IsCainInTristramDeactivated, dll_base + 0x0006CC00);
		
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
			const auto moo_result = sut(&moo_pGame);
			const auto original_result = original(&original_pGame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
}
