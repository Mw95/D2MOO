#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <UNIT/SUnitNpc.h>
#include <Units/Units.h>


TEST_SUITE("SUnitNpcTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC67D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_FirstFn_6FCC67D0, dll_base + 0x000967D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2NpcRecordStrc moo_pNpcRecord{};
			D2GameStrc original_pGame{};
			D2NpcRecordStrc original_pNpcRecord{};
			int32_t nVendorId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2NpcRecordStrc& pNpcRecord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pNpcRecord);
			setup_data(original_pGame, original_pNpcRecord);

			// Call both implementations
			sut(&moo_pGame, nVendorId, &moo_pNpcRecord);
			original(&original_pGame, nVendorId, &original_pNpcRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpcRecord, original_pNpcRecord, "Comparing pNpcRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC6970" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_RepairItem_6FCC6970, dll_base + 0x00096970);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pPlayer);
			setup_data(original_pGame, original_pItem, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pPlayer);
			original(&original_pGame, &original_pItem, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC6A60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_GenerateStoreItem_6FCC6A60, dll_base + 0x00096A60);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pNpc{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pNpc{};
			D2GameStrc original_pGame{};
			int32_t szCode{};
			int32_t a4{};
			int32_t nQuality{};
			int32_t nItemLevel{};
			int32_t nPlayerLevel{};

			const auto setup_data = [](
				D2UnitStrc& pNpc,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pNpc, moo_pGame);
			setup_data(original_pNpc, original_pGame);

			// Call both implementations
			auto moo_result = sut(&moo_pNpc, szCode, &moo_pGame, a4, nQuality, nItemLevel, nPlayerLevel);
			auto original_result = original(&original_pNpc, szCode, &original_pGame, a4, nQuality, nItemLevel, nPlayerLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC6F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCC6F10, dll_base + 0x00096F10);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pNpc{};
			D2UnitStrc moo_pItem{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pNpc{};
			D2UnitStrc original_pItem{};
			D2GameStrc original_pGame{};
			int32_t bInit{};

			const auto setup_data = [](
				D2UnitStrc& pNpc,
				D2UnitStrc& pItem,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pNpc, moo_pItem, moo_pGame);
			setup_data(original_pNpc, original_pItem, original_pGame);

			// Call both implementations
			sut(&moo_pNpc, &moo_pItem, &moo_pGame, bInit);
			original(&original_pNpc, &original_pItem, &original_pGame, bInit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC6FF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_BuildHirelingList_6FCC6FF0, dll_base + 0x00096FF0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient, moo_pUnit);
			setup_data(original_pGame, original_pClient, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pClient, &moo_pUnit, a4);
			original(&original_pGame, &original_pClient, &original_pUnit, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC7100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_FillStoreInventory_6FCC7100, dll_base + 0x00097100);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNpc{};
			D2NpcTradeStrc moo_pTrade{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNpc{};
			D2NpcTradeStrc original_pTrade{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pNpc,
				D2NpcTradeStrc& pTrade
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pNpc, moo_pTrade);
			setup_data(original_pGame, original_pPlayer, original_pNpc, original_pTrade);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pNpc, &moo_pTrade);
			original(&original_pGame, &original_pPlayer, &original_pNpc, &original_pTrade);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pTrade, original_pTrade, "Comparing pTrade");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC74F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_STORES_CreateVendorCache_6FCC74F0, dll_base + 0x000974F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNPC{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNPC{};
			int32_t a4{};
			int32_t a5{};

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
			sut(&moo_pGame, &moo_pPlayer, &moo_pNPC, a4, a5);
			original(&original_pGame, &original_pPlayer, &original_pNPC, a4, a5);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC7680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_STORES_SellItem_6FCC7680, dll_base + 0x00097680);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nNpcGUID{};
			int32_t nItemGUID{};
			int16_t nItemMode{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, nNpcGUID, nItemGUID, nItemMode, a6);
			auto original_result = original(&original_pGame, &original_pPlayer, nNpcGUID, nItemGUID, nItemMode, a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC7E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCC7E20, dll_base + 0x00097E20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pNpc{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pNpc{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pUnit{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pNpc,
				D2UnitStrc& pItem,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pNpc, moo_pItem, moo_pUnit);
			setup_data(original_pGame, original_pNpc, original_pItem, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pNpc, &moo_pItem, &moo_pUnit, a5);
			original(&original_pGame, &original_pNpc, &original_pItem, &original_pUnit, a5);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC7FA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCC7FA0, dll_base + 0x00097FA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNpc{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNpc{};
			uint16_t wName{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pNpc
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pNpc);
			setup_data(original_pGame, original_pPlayer, original_pNpc);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pNpc, wName);
			original(&original_pGame, &original_pPlayer, &original_pNpc, wName);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC8430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCC8430, dll_base + 0x00098430);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC84D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCC84D0, dll_base + 0x000984D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pPet{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pPet{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pPet
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pPet);
			setup_data(original_pGame, original_pPlayer, original_pPet);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pPet);
			original(&original_pGame, &original_pPlayer, &original_pPet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pPet, original_pPet, "Comparing pPet");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC8630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MERCS_Create_6FCC8630, dll_base + 0x00098630);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint16_t wName{};
			uint32_t nSeed{};
			int16_t wVersion{};
			int32_t nBaseMonster{};
			int32_t bDead{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, wName, nSeed, wVersion, nBaseMonster, bDead);
			auto original_result = original(&original_pGame, &original_pPlayer, wName, nSeed, wVersion, nBaseMonster, bDead);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC87C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCC87C0, dll_base + 0x000987C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pPlayer{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			int32_t moo_a4{};
			D2GameStrc original_pPlayer{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			int32_t original_a4{};

			const auto setup_data = [](
				D2GameStrc& pPlayer,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem,
				int32_t& a4
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pUnit, moo_pItem, moo_a4);
			setup_data(original_pPlayer, original_pUnit, original_pItem, original_a4);

			// Call both implementations
			auto moo_result = sut(&moo_pPlayer, &moo_pUnit, &moo_pItem, &moo_a4);
			auto original_result = original(&original_pPlayer, &original_pUnit, &original_pItem, &original_a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC88B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCC88B0, dll_base + 0x000988B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNpc{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNpc{};
			int32_t nItemGUID{};
			int32_t nItemMode{};
			uint16_t nTransactionType{};
			int32_t nCost{};
			int32_t bMultibuy{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pNpc
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pNpc);
			setup_data(original_pGame, original_pPlayer, original_pNpc);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pNpc, nItemGUID, nItemMode, nTransactionType, nCost, bMultibuy);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_pNpc, nItemGUID, nItemMode, nTransactionType, nCost, bMultibuy);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC92A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_BuyItemHandler_6FCC92A0, dll_base + 0x000992A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nNpcUnitId{};
			int32_t nItemId{};
			int32_t nItemMode{};
			uint16_t nTransactionType{};
			int32_t nCost{};
			int32_t bMultibuy{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, nNpcUnitId, nItemId, nItemMode, nTransactionType, nCost, bMultibuy);
			auto original_result = original(&original_pGame, &original_pPlayer, nNpcUnitId, nItemId, nItemMode, nTransactionType, nCost, bMultibuy);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC9350" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_ResurrectMerc_6FCC9350, dll_base + 0x00099350);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nNpcUnitId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nNpcUnitId);
			original(&original_pGame, &original_pPlayer, nNpcUnitId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC9540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_HireMerc_6FCC9540, dll_base + 0x00099540);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nNpcUnitId{};
			uint16_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nNpcUnitId, a4);
			original(&original_pGame, &original_pPlayer, nNpcUnitId, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC95B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_Repair_6FCC95B0, dll_base + 0x000995B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nNpcGUID{};
			int32_t nItemGUID{};
			int32_t nUnused{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nNpcGUID, nItemGUID, nUnused, a6);
			auto original_result = original(&original_pGame, &original_pUnit, nNpcGUID, nItemGUID, nUnused, a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC9C90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_IdentifyAllItems_6FCC9C90, dll_base + 0x00099C90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nNpcGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nNpcGUID);
			original(&original_pGame, &original_pPlayer, nNpcGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC9F40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(NPC_HandleDialogMessage, dll_base + 0x00099F40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nType{};
			int32_t nNpcGUID{};
			int32_t nItemGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, nType, nNpcGUID, nItemGUID);
			auto original_result = original(&original_pGame, &original_pPlayer, nType, nNpcGUID, nItemGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCA990" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_IdentifyBoughtItem_6FCCA990, dll_base + 0x0009A990);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nItemGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nItemGUID);
			original(&original_pGame, &original_pPlayer, nItemGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCA9F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_STORES_FillGamble_6FCCA9F0, dll_base + 0x0009A9F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pNpc{};
			D2UnitStrc moo_pUnit{};
			D2NpcRecordStrc moo_pNpcRecord{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pNpc{};
			D2UnitStrc original_pUnit{};
			D2NpcRecordStrc original_pNpcRecord{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pNpc,
				D2UnitStrc& pUnit,
				D2NpcRecordStrc& pNpcRecord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pNpc, moo_pUnit, moo_pNpcRecord);
			setup_data(original_pGame, original_pNpc, original_pUnit, original_pNpcRecord);

			// Call both implementations
			sut(&moo_pGame, &moo_pNpc, &moo_pUnit, &moo_pNpcRecord);
			original(&original_pGame, &original_pNpc, &original_pUnit, &original_pNpcRecord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pNpcRecord, original_pNpcRecord, "Comparing pNpcRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCAE20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_STORES_CreateVendorCache_6FCCAE20, dll_base + 0x0009AE20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNpc{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNpc{};
			int32_t bGamble{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pNpc
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pNpc);
			setup_data(original_pGame, original_pPlayer, original_pNpc);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pNpc, bGamble);
			original(&original_pGame, &original_pPlayer, &original_pNpc, bGamble);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCAF30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_RemoveStates_6FCCAF30, dll_base + 0x0009AF30);
		
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
			auto moo_result = sut(&moo_pUnit);
			auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCAFA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITNPC_PetIterate_Heal, dll_base + 0x0009AFA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_a2{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_a2{};
			D2UnitStrc original_pUnit{};
			void* moo_a4 = nullptr;
			void* original_a4 = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& a2,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_a2, moo_pUnit);
			setup_data(original_pGame, original_a2, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_a2, &moo_pUnit, moo_a4);
			original(&original_pGame, &original_a2, &original_pUnit, original_a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_HealPlayer_6FCCB080, dll_base + 0x0009B080);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pNpc{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pNpc{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pNpc
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pNpc);
			setup_data(original_pGame, original_pUnit, original_pNpc);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pNpc);
			original(&original_pGame, &original_pUnit, &original_pNpc);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_Heal_6FCCB220, dll_base + 0x0009B220);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pNpc{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pNpc{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pNpc
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pNpc);
			setup_data(original_pGame, original_pUnit, original_pNpc);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pNpc);
			original(&original_pGame, &original_pUnit, &original_pNpc);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_PurchaseHeal_6FCCB280, dll_base + 0x0009B280);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nNpcGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nNpcGUID);
			original(&original_pGame, &original_pUnit, nNpcGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB4D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_ResetInteract_6FCCB4D0, dll_base + 0x0009B4D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNpc{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNpc{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pNpc
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pNpc);
			setup_data(original_pGame, original_pPlayer, original_pNpc);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pNpc);
			original(&original_pGame, &original_pPlayer, &original_pNpc);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_AssignMercenary_6FCCB520, dll_base + 0x0009B520);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nMonster{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nMonster);
			original(&original_pGame, &original_pPlayer, nMonster);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCB7D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPC_IsItemInNpcInventory_6FCCB7D0, dll_base + 0x0009B7D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pNpc{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pNpc{};
			D2UnitStrc original_pItem{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pNpc,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pNpc, moo_pItem);
			setup_data(original_pGame, original_pPlayer, original_pNpc, original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pNpc, &moo_pItem, a4);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_pNpc, &original_pItem, a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
}
