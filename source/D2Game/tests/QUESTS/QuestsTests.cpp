#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <QUESTS/Quests.h>
#include <Units/Units.h>


TEST_SUITE("QuestsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93B60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_FreeChainRecord, dll_base + 0x00063B60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2QuestChainStrc moo_pRecord{};
			D2GameStrc original_pGame{};
			D2QuestChainStrc original_pRecord{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2QuestChainStrc& pRecord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRecord);
			setup_data(original_pGame, original_pRecord);

			// Call both implementations
			sut(&moo_pGame, &moo_pRecord);
			original(&original_pGame, &original_pRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRecord, original_pRecord, "Comparing pRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_GetQuestData, dll_base + 0x00063B90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nId{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nId);
			const auto original_result = original(&original_pGame, nId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93BD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_AttachLevelChainRecord, dll_base + 0x00063BD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t bDebug{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pRoom);
			setup_data(original_pGame, original_pUnit, original_pRoom);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pRoom, bDebug);
			original(&original_pGame, &original_pUnit, &original_pRoom, bDebug);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93C40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_CreateChainRecord, dll_base + 0x00063C40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nQuestId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nQuestId);
			const auto original_result = original(&original_pGame, &original_pUnit, nQuestId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93D60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_InitScrollTextChain, dll_base + 0x00063D60);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2TextHeaderStrc moo_pTextControl{};
			D2QuestDataStrc original_pQuest{};
			D2TextHeaderStrc original_pTextControl{};
			int32_t nNPCID{};
			int32_t nIndex{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest,
				D2TextHeaderStrc& pTextControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest, moo_pTextControl);
			setup_data(original_pQuest, original_pTextControl);

			// Call both implementations
			sut(&moo_pQuest, &moo_pTextControl, nNPCID, nIndex);
			original(&original_pQuest, &original_pTextControl, nNPCID, nIndex);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pTextControl, original_pTextControl, "Comparing pTextControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_QuestInit, dll_base + 0x00063DC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93FD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_QuestFree, dll_base + 0x00063FD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_GetGlobalSeed, dll_base + 0x00064080);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC940B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_ParseKill, dll_base + 0x000640B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc moo_pAttacker{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pDefender{};
			D2UnitStrc original_pAttacker{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pDefender,
				D2UnitStrc& pAttacker
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pDefender, moo_pAttacker);
			setup_data(original_pGame, original_pDefender, original_pAttacker);

			// Call both implementations
			sut(&moo_pGame, &moo_pDefender, &moo_pAttacker);
			original(&original_pGame, &original_pDefender, &original_pAttacker);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94210" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_StatusCycler, dll_base + 0x00064210);
		
		SUBCASE("")
		{
			// Input data
			D2QuestArgStrc moo_pArgs{};
			D2QuestArgStrc original_pArgs{};
			bool bForceActive{};

			const auto setup_data = [](
				D2QuestArgStrc& pArgs
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pArgs);
			setup_data(original_pArgs);

			// Call both implementations
			sut(&moo_pArgs, bForceActive);
			original(&original_pArgs, bForceActive);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94290" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_ChangeLevel, dll_base + 0x00064290);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nOldLevelId{};
			int32_t nTargetLevelId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, nOldLevelId, nTargetLevelId, &moo_pUnit);
			original(&original_pGame, nOldLevelId, nTargetLevelId, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC942D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_EventCallback, dll_base + 0x000642D0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestArgStrc moo_pArgs{};
			D2QuestArgStrc original_pArgs{};
			bool bCheckActive{};
			bool bCheckAct{};

			const auto setup_data = [](
				D2QuestArgStrc& pArgs
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pArgs);
			setup_data(original_pArgs);

			// Call both implementations
			sut(&moo_pArgs, bCheckActive, bCheckAct);
			original(&original_pArgs, bCheckActive, bCheckAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94390" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_PlayerDroppedWithQuestItem, dll_base + 0x00064390);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer);
			original(&original_pGame, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC944B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_NPCActivate, dll_base + 0x000644B0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pTarget{};
			D2TextHeaderStrc moo_pTextControl{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pTarget{};
			D2TextHeaderStrc original_pTextControl{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pTarget,
				D2TextHeaderStrc& pTextControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pTarget, moo_pTextControl);
			setup_data(original_pClient, original_pPlayer, original_pTarget, original_pTextControl);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pTarget, &moo_pTextControl);
			original(&original_pClient, &original_pPlayer, &original_pTarget, &original_pTextControl);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pTextControl, original_pTextControl, "Comparing pTextControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC944F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_NPCDeactivate, dll_base + 0x000644F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNPC{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNPC{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pNPC
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pNPC);
			setup_data(original_pGame, original_pPlayer, original_pNPC);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pNPC);
			original(&original_pGame, &original_pPlayer, &original_pNPC);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_ItemPickedUp, dll_base + 0x00064520);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pItem);
			setup_data(original_pGame, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pItem);
			original(&original_pGame, &original_pPlayer, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_ItemDropped, dll_base + 0x00064550);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pItem);
			setup_data(original_pGame, original_pPlayer, original_pItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pItem);
			original(&original_pGame, &original_pPlayer, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_QuestUpdater, dll_base + 0x00064580);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_CreateTimer, dll_base + 0x00064690);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2QuestDataStrc original_pQuest{};
			QUESTUPDATE pfnCallback{};
			int32_t nTicks{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest);
			setup_data(original_pQuest);

			// Call both implementations
			sut(&moo_pQuest, pfnCallback, nTicks);
			original(&original_pQuest, pfnCallback, nTicks);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_RefreshStatus, dll_base + 0x00064710);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			uint8_t moo_pQuestList{};
			D2BitBufferStrc moo_pQuestFlags{};
			D2QuestDataStrc original_pQuest{};
			uint8_t original_pQuestList{};
			D2BitBufferStrc original_pQuestFlags{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest,
				uint8_t& pQuestList,
				D2BitBufferStrc& pQuestFlags
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest, moo_pQuestList, moo_pQuestFlags);
			setup_data(original_pQuest, original_pQuestList, original_pQuestFlags);

			// Call both implementations
			sut(&moo_pQuest, &moo_pQuestList, &moo_pQuestFlags);
			original(&original_pQuest, &original_pQuestList, &original_pQuestFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pQuestList, original_pQuestList, "Comparing pQuestList");
			SKIP_MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC947F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_StatusCallback, dll_base + 0x000647F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94A30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_DebugOutput, dll_base + 0x00064A30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			char szMessage{};
			char szFile{};
			int32_t nLine{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &szMessage, &szFile, nLine);
			const auto original_result = original(&original_pGame, &szMessage, &szFile, nLine);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94A50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_DeleteItem, dll_base + 0x00064A50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint32_t dwItemCode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, dwItemCode);
			original(&original_pGame, &original_pPlayer, dwItemCode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_StatusCyclerEx, dll_base + 0x00064B20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint8_t nQuestId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nQuestId);
			original(&original_pGame, &original_pPlayer, nQuestId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94CA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_UnitIterate, dll_base + 0x00064CA0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2UnitStrc moo_pUnit{};
			D2QuestDataStrc original_pQuest{};
			D2UnitStrc original_pUnit{};
			int32_t nIterateState{};
			bool bIterate{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest, moo_pUnit);
			setup_data(original_pQuest, original_pUnit);

			// Call both implementations
			sut(&moo_pQuest, nIterateState, &moo_pUnit, nullptr, bIterate);
			original(&original_pQuest, nIterateState, &original_pUnit, nullptr, bIterate);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94CF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_StateDebug, dll_base + 0x00064CF0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuestData{};
			D2QuestDataStrc original_pQuestData{};
			int32_t nState{};
			char szFile{};
			int32_t nLine{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuestData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestData);
			setup_data(original_pQuestData);

			// Call both implementations
			const auto moo_result = sut(&moo_pQuestData, nState, &szFile, nLine);
			const auto original_result = original(&original_pQuestData, nState, &szFile, nLine);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestData, original_pQuestData, "Comparing pQuestData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94D40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_NPCMessage, dll_base + 0x00064D40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t dwNPCGUID{};
			uint16_t nMessage{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, dwNPCGUID, nMessage);
			original(&original_pGame, &original_pPlayer, dwNPCGUID, nMessage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC94DB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SequenceCycler, dll_base + 0x00064DB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t bGameEnter{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, bGameEnter);
			original(&original_pGame, &original_pPlayer, bGameEnter);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95360 (#10037)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_CheckFirstPickedSet, dll_base + 0x00065360);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC953A0 (#10038)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_CheckNotIntroQuest, dll_base + 0x000653A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nQuestId{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nQuestId);
			const auto original_result = original(&original_pGame, nQuestId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SendCurrentFlags, dll_base + 0x00065430);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient);
			setup_data(original_pGame, original_pClient);

			// Call both implementations
			sut(&moo_pGame, &moo_pClient);
			original(&original_pGame, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_ActiveCycler, dll_base + 0x00065490);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNPC{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNPC{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pNPC
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pNPC);
			setup_data(original_pGame, original_pPlayer, original_pNPC);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pNPC);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pNPC);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC956C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SetGlobalState, dll_base + 0x000656C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nQuestId{};
			int32_t nState{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame, nQuestId, nState);
			original(&original_pGame, nQuestId, nState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95700" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_GetGlobalState, dll_base + 0x00065700);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nQuestId{};
			int32_t nState{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nQuestId, nState);
			const auto original_result = original(&original_pGame, nQuestId, nState);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_WarrivSpawn, dll_base + 0x00065740);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pWarriv{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pWarriv{};
			int32_t nXpos{};
			int32_t nYpos{};
			int32_t nWarrivID{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pWarriv
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pWarriv);
			setup_data(original_pGame, original_pWarriv);

			// Call both implementations
			sut(&moo_pGame, &moo_pWarriv, nXpos, nYpos, nWarrivID);
			original(&original_pGame, &original_pWarriv, nXpos, nYpos, nWarrivID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pWarriv, original_pWarriv, "Comparing pWarriv");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_UseClueItem, dll_base + 0x00065790);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nUnitId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUnitId);
			original(&original_pGame, &original_pUnit, nUnitId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction18_JerhynPosition, dll_base + 0x00065800);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction19_JerhynPositionEx, dll_base + 0x00065830);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95860" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction20_TaintedAltar, dll_base + 0x00065860);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC958A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction15_MalusStand, dll_base + 0x000658A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC958E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction07_CainGibbet, dll_base + 0x000658E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95920 (#10035)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_DisableSequences, dll_base + 0x00065920);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_ObjectEvents, dll_base + 0x00065930);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_InitFunction23_LamEsenTomeStand, dll_base + 0x00065CC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95D10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SetJadeFigurineBoss, dll_base + 0x00065D10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95DB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SetGoldenBirdSpawn, dll_base + 0x00065DB0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95DF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_CreateItem, dll_base + 0x00065DF0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint32_t dwCode{};
			int32_t nLevel{};
			uint8_t nQuality{};
			int32_t bDroppable{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, dwCode, nLevel, nQuality, bDroppable);
			const auto original_result = original(&original_pGame, &original_pPlayer, dwCode, nLevel, nQuality, bDroppable);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC95F30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_UpdateNPCIntros, dll_base + 0x00065F30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint8_t nAct{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nAct);
			original(&original_pGame, &original_pUnit, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC960C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_ActChange_HirelingChangeAct, dll_base + 0x000660C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pVendor{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pVendor{};
			uint32_t dwDestLvl{};
			uint32_t unk{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pVendor
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pVendor);
			setup_data(original_pGame, original_pUnit, original_pVendor);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pVendor, dwDestLvl, unk);
			original(&original_pGame, &original_pUnit, &original_pVendor, dwDestLvl, unk);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pVendor, original_pVendor, "Comparing pVendor");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC964B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_DeleteItemEx, dll_base + 0x000664B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pInventory, moo_pItem);
			setup_data(original_pGame, original_pPlayer, original_pInventory, original_pItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pInventory, &moo_pItem);
			original(&original_pGame, &original_pPlayer, &original_pInventory, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_HellPortalActChange, dll_base + 0x00066580);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pObject{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pObject{};
			int32_t nLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pObject
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pObject);
			setup_data(original_pGame, original_pPlayer, original_pObject);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nLevel, &moo_pObject);
			original(&original_pGame, &original_pPlayer, nLevel, &original_pObject);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC967D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SetIntroFlags, dll_base + 0x000667D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t pNPCs{};
			int32_t nNPCs{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &pNPCs, nNPCs);
			original(&original_pGame, &original_pPlayer, &pNPCs, nNPCs);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_AddPlayerGUID, dll_base + 0x00066810);
		
		SUBCASE("")
		{
			// Input data
			D2QuestGUIDStrc moo_pQuestGUID{};
			D2QuestGUIDStrc original_pQuestGUID{};
			int32_t dwGUID{};

			const auto setup_data = [](
				D2QuestGUIDStrc& pQuestGUID
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuestGUID);
			setup_data(original_pQuestGUID);

			// Call both implementations
			sut(&moo_pQuestGUID, dwGUID);
			original(&original_pQuestGUID, dwGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuestGUID, original_pQuestGUID, "Comparing pQuestGUID");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_FastRemovePlayerGUID, dll_base + 0x00066840);
		
		SUBCASE("")
		{
			// Input data
			D2QuestGUIDStrc moo_pGUIDs{};
			D2QuestGUIDStrc original_pGUIDs{};
			int32_t dwGUID{};

			const auto setup_data = [](
				D2QuestGUIDStrc& pGUIDs
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGUIDs);
			setup_data(original_pGUIDs);

			// Call both implementations
			const auto moo_result = sut(&moo_pGUIDs, dwGUID);
			const auto original_result = original(&original_pGUIDs, dwGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGUIDs, original_pGUIDs, "Comparing pGUIDs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_QuickCheckPlayerGUID, dll_base + 0x00066880);
		
		SUBCASE("")
		{
			// Input data
			D2QuestGUIDStrc moo_pGUIDs{};
			D2QuestGUIDStrc original_pGUIDs{};
			int32_t dwGUID{};

			const auto setup_data = [](
				D2QuestGUIDStrc& pGUIDs
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGUIDs);
			setup_data(original_pGUIDs);

			// Call both implementations
			const auto moo_result = sut(&moo_pGUIDs, dwGUID);
			const auto original_result = original(&original_pGUIDs, dwGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGUIDs, original_pGUIDs, "Comparing pGUIDs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC968B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_CheckPlayerGUID, dll_base + 0x000668B0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2QuestDataStrc original_pQuest{};
			int32_t dwGUID{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest);
			setup_data(original_pQuest);

			// Call both implementations
			const auto moo_result = sut(&moo_pQuest, dwGUID);
			const auto original_result = original(&original_pQuest, dwGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC968E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_ResetPlayerGUIDCount, dll_base + 0x000668E0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestGUIDStrc moo_pGUIDs{};
			D2QuestGUIDStrc original_pGUIDs{};

			const auto setup_data = [](
				D2QuestGUIDStrc& pGUIDs
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGUIDs);
			setup_data(original_pGUIDs);

			// Call both implementations
			sut(&moo_pGUIDs);
			original(&original_pGUIDs);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGUIDs, original_pGUIDs, "Comparing pGUIDs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC968F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_QuickRemovePlayerGUID, dll_base + 0x000668F0);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2QuestArgStrc moo_pQuestArg{};
			D2QuestDataStrc original_pQuest{};
			D2QuestArgStrc original_pQuestArg{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest,
				D2QuestArgStrc& pQuestArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest, moo_pQuestArg);
			setup_data(original_pQuest, original_pQuestArg);

			// Call both implementations
			sut(&moo_pQuest, &moo_pQuestArg);
			original(&original_pQuest, &original_pQuestArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pQuestArg, original_pQuestArg, "Comparing pQuestArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_GetFreePosition, dll_base + 0x00066940);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2CoordStrc moo_pCoord{};
			D2ActiveRoomStrc* moo_ppRoom{};
			D2ActiveRoomStrc original_pRoom{};
			D2CoordStrc original_pCoord{};
			D2ActiveRoomStrc* original_ppRoom{};
			uint32_t nSize{};
			uint16_t fCollision{};
			int32_t nRadius{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom,
				D2CoordStrc& pCoord,
				D2ActiveRoomStrc*& ppRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pRoom, moo_pCoord, moo_ppRoom);
			setup_data(original_pRoom, original_pCoord, original_ppRoom);

			// Call both implementations
			sut(&moo_pRoom, &moo_pCoord, nSize, fCollision, &moo_ppRoom, nRadius);
			original(&original_pRoom, &original_pCoord, nSize, fCollision, &original_ppRoom, nRadius);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
			SKIP_MOO_CHECK_EQ(moo_ppRoom, original_ppRoom, "Comparing ppRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96C80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_RemovePlayerGUID, dll_base + 0x00066C80);
		
		SUBCASE("")
		{
			// Input data
			D2QuestDataStrc moo_pQuest{};
			D2QuestArgStrc moo_pArgs{};
			D2QuestDataStrc original_pQuest{};
			D2QuestArgStrc original_pArgs{};

			const auto setup_data = [](
				D2QuestDataStrc& pQuest,
				D2QuestArgStrc& pArgs
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pQuest, moo_pArgs);
			setup_data(original_pQuest, original_pArgs);

			// Call both implementations
			sut(&moo_pQuest, &moo_pArgs);
			original(&original_pQuest, &original_pArgs);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pQuest, original_pQuest, "Comparing pQuest");
			SKIP_MOO_CHECK_EQ(moo_pArgs, original_pArgs, "Comparing pArgs");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96D20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_UpdatePlayerFlags, dll_base + 0x00066D20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96D60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_GUIDUpdate, dll_base + 0x00066D60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2QuestGUIDStrc moo_pQuestGUID{};
			D2GameStrc original_pGame{};
			D2QuestGUIDStrc original_pQuestGUID{};
			int32_t nQuest{};
			uint16_t wSoundCMD{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2QuestGUIDStrc& pQuestGUID
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pQuestGUID);
			setup_data(original_pGame, original_pQuestGUID);

			// Call both implementations
			sut(&moo_pGame, &moo_pQuestGUID, nQuest, wSoundCMD);
			original(&original_pGame, &original_pQuestGUID, nQuest, wSoundCMD);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pQuestGUID, original_pQuestGUID, "Comparing pQuestGUID");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SendScrollMessage, dll_base + 0x00066E20);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pUnit{};
			uint16_t nMessage{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pUnit);
			setup_data(original_pPlayer, original_pUnit);

			// Call both implementations
			sut(&moo_pPlayer, &moo_pUnit, nMessage);
			original(&original_pPlayer, &original_pUnit, nMessage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_TriggerFX, dll_base + 0x00066E80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			uint8_t a2{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame, a2);
			original(&original_pGame, a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96EA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_FXIterate, dll_base + 0x00066EA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pArg);
			const auto original_result = original(&original_pGame, &original_pUnit, original_pArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC96F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_NPCActivateSpeeches, dll_base + 0x00066F10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pTarget{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pTarget);
			setup_data(original_pGame, original_pPlayer, original_pTarget);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pTarget);
			original(&original_pGame, &original_pPlayer, &original_pTarget);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC97020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_PortalCheck, dll_base + 0x00067020);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2CoordStrc moo_pCoord{};
			D2ActiveRoomStrc* moo_ppRoom{};
			D2GameStrc original_pGame{};
			D2CoordStrc original_pCoord{};
			D2ActiveRoomStrc* original_ppRoom{};
			int32_t nLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2CoordStrc& pCoord,
				D2ActiveRoomStrc*& ppRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pCoord, moo_ppRoom);
			setup_data(original_pGame, original_pCoord, original_ppRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pCoord, nLevel, &moo_ppRoom);
			const auto original_result = original(&original_pGame, &original_pCoord, nLevel, &original_ppRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
			SKIP_MOO_CHECK_EQ(moo_ppRoom, original_ppRoom, "Comparing ppRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC97040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SetObjectSelection, dll_base + 0x00067040);
		
		SUBCASE("")
		{
			// Input data
			D2ObjOperateFnStrc moo_pOp{};
			D2ObjOperateFnStrc original_pOp{};

			const auto setup_data = [](
				D2ObjOperateFnStrc& pOp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pOp);
			setup_data(original_pOp);

			// Call both implementations
			const auto moo_result = sut(&moo_pOp);
			const auto original_result = original(&original_pOp);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pOp, original_pOp, "Comparing pOp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC970E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SendLogUpdate, dll_base + 0x000670E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			uint8_t nQuestId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nQuestId);
			original(&original_pUnit, nQuestId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC97120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SendLogUpdateEx, dll_base + 0x00067120);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};
			uint8_t nQuestId{};
			uint8_t nAct{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

			// Call both implementations
			sut(&moo_pPlayer, nQuestId, nAct);
			original(&original_pPlayer, nQuestId, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC97190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SpawnCriticalMonster, dll_base + 0x00067190);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nXpos{};
			int32_t nYpos{};
			int32_t bSpecialInit{};
			int32_t nMonster{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nXpos, nYpos, &moo_pRoom, bSpecialInit, nMonster);
			const auto original_result = original(&original_pGame, nXpos, nYpos, &original_pRoom, bSpecialInit, nMonster);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC973D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_MonsterSpawn, dll_base + 0x000673D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC97400" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_LevelWarpCheck, dll_base + 0x00067400);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nSourceLevel{};
			int32_t nTargetLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nSourceLevel, nTargetLevel);
			const auto original_result = original(&original_pGame, &original_pPlayer, nSourceLevel, nTargetLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC974B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_SpawnMonster, dll_base + 0x000674B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2CoordStrc moo_pPosition{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2CoordStrc original_pPosition{};
			int32_t nType{};
			int32_t nIndex{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2CoordStrc& pPosition
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pPosition);
			setup_data(original_pGame, original_pUnit, original_pPosition);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pPosition, nType, nIndex);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pPosition, nType, nIndex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pPosition, original_pPosition, "Comparing pPosition");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC975A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(QUESTS_MapPresetSpawn, dll_base + 0x000675A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2MapAIStrc moo_pMapAI{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2MapAIStrc original_pMapAI{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2MapAIStrc& pMapAI
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pMapAI);
			setup_data(original_pGame, original_pUnit, original_pMapAI);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pMapAI);
			original(&original_pGame, &original_pUnit, &original_pMapAI);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMapAI, original_pMapAI, "Comparing pMapAI");
		}
	}
}
