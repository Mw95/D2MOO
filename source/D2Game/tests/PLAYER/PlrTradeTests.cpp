#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <PLAYER/PlrTrade.h>
#include <Units/Units.h>


TEST_SUITE("PlrTradeTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8F3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(OBJECTS_OperateFunction32_Bank, dll_base + 0x0005F3D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8F450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_CheckCubeInput, dll_base + 0x0005F450);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2InventoryStrc moo_pInventory{};
			D2CubeMainTxt moo_pCubeMainTxt{};
			D2CubeItemStrc moo_pCubeItem{};
			int32_t moo_a6{};
			D2GameStrc original_pGame{};
			D2InventoryStrc original_pInventory{};
			D2CubeMainTxt original_pCubeMainTxt{};
			D2CubeItemStrc original_pCubeItem{};
			int32_t original_a6{};
			int32_t nInputIndex{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2InventoryStrc& pInventory,
				D2CubeMainTxt& pCubeMainTxt,
				D2CubeItemStrc& pCubeItem,
				int32_t& a6
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pInventory, moo_pCubeMainTxt, moo_pCubeItem, moo_a6);
			setup_data(original_pGame, original_pInventory, original_pCubeMainTxt, original_pCubeItem, original_a6);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pInventory, &moo_pCubeMainTxt, nInputIndex, &moo_pCubeItem, &moo_a6);
			auto original_result = original(&original_pGame, &original_pInventory, &original_pCubeMainTxt, nInputIndex, &original_pCubeItem, &original_a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			SKIP_MOO_CHECK_EQ(moo_pCubeMainTxt, original_pCubeMainTxt, "Comparing pCubeMainTxt");
			SKIP_MOO_CHECK_EQ(moo_pCubeItem, original_pCubeItem, "Comparing pCubeItem");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC8FE40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_RollRandomItemClassOfSameType, dll_base + 0x0005FE40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nItemLevel{};
			int32_t nItemId{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, nItemLevel, nItemId);
			auto original_result = original(&original_pGame, nItemLevel, nItemId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC90010" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_CreateCubeOutputs, dll_base + 0x00060010);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2CubeMainTxt moo_pCubeMainTxt{};
			D2CubeItemStrc moo_pCubeItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2CubeMainTxt original_pCubeMainTxt{};
			D2CubeItemStrc original_pCubeItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2CubeMainTxt& pCubeMainTxt,
				D2CubeItemStrc& pCubeItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pCubeMainTxt, moo_pCubeItem);
			setup_data(original_pGame, original_pUnit, original_pCubeMainTxt, original_pCubeItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pCubeMainTxt, &moo_pCubeItem);
			original(&original_pGame, &original_pUnit, &original_pCubeMainTxt, &original_pCubeItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pCubeMainTxt, original_pCubeMainTxt, "Comparing pCubeMainTxt");
			SKIP_MOO_CHECK_EQ(moo_pCubeItem, original_pCubeItem, "Comparing pCubeItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC90A60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_Free, dll_base + 0x00060A60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC90AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC90AE0, dll_base + 0x00060AE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3);
			original(&original_pGame, &original_pUnit, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC90BE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC90BE0, dll_base + 0x00060BE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, moo_pArg);
			original(&original_pGame, &original_pPlayer, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC90C20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC90C20, dll_base + 0x00060C20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC90D70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_SendEventPacketToPlayer, dll_base + 0x00060D70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			char moo_szSource{};
			D2UnitStrc original_pPlayer{};
			char original_szSource{};
			D2C_SRV2CLT5A_TYPES nType{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				char& szSource
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_szSource);
			setup_data(original_pPlayer, original_szSource);

			// Call both implementations
			sut(&moo_pPlayer, nType, &moo_szSource);
			original(&original_pPlayer, nType, &original_szSource);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_szSource, original_szSource, "Comparing szSource");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC90DE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_TryToTrade, dll_base + 0x00060DE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC91050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC91050, dll_base + 0x00061050);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			D2PlayerDataStrc moo_pPlayerData1{};
			D2PlayerDataStrc moo_pPlayerData2{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			D2PlayerDataStrc original_pPlayerData1{};
			D2PlayerDataStrc original_pPlayerData2{};
			int32_t nTradeState{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				D2PlayerDataStrc& pPlayerData1,
				D2PlayerDataStrc& pPlayerData2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pPlayerData1, moo_pPlayerData2);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pPlayerData1, original_pPlayerData2);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, &moo_pPlayerData1, &moo_pPlayerData2, nTradeState);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, &original_pPlayerData1, &original_pPlayerData2, nTradeState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pPlayerData1, original_pPlayerData1, "Comparing pPlayerData1");
			SKIP_MOO_CHECK_EQ(moo_pPlayerData2, original_pPlayerData2, "Comparing pPlayerData2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC91250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC91250, dll_base + 0x00061250);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			uint16_t nButton{};
			int32_t nGoldAmount{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, nButton, nGoldAmount);
			auto original_result = original(&original_pGame, &original_pPlayer, nButton, nGoldAmount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC92130" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_HandleCubeInteraction, dll_base + 0x00062130);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC927D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_AllocPlayerTrade, dll_base + 0x000627D0);
		
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
			auto moo_result = sut(&moo_pGame, &moo_pPlayer);
			auto original_result = original(&original_pGame, &original_pPlayer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC92890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_AddGold, dll_base + 0x00062890);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nStat{};
			int32_t nValue{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nStat, nValue);
			original(&original_pUnit, nStat, nValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC92920" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC92920, dll_base + 0x00062920);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			D2PlayerDataStrc moo_pPlayerData1{};
			D2PlayerDataStrc moo_pPlayerData2{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			D2PlayerDataStrc original_pPlayerData1{};
			D2PlayerDataStrc original_pPlayerData2{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				D2PlayerDataStrc& pPlayerData1,
				D2PlayerDataStrc& pPlayerData2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pPlayerData1, moo_pPlayerData2);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pPlayerData1, original_pPlayerData2);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, &moo_pPlayerData1, &moo_pPlayerData2);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, &original_pPlayerData1, &original_pPlayerData2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pPlayerData1, original_pPlayerData1, "Comparing pPlayerData1");
			SKIP_MOO_CHECK_EQ(moo_pPlayerData2, original_pPlayerData2, "Comparing pPlayerData2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC92A90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC92A90, dll_base + 0x00062A90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2);
			auto original_result = original(&original_pGame, &original_pPlayer1, &original_pPlayer2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC92CF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_StopAllPlayerInteractions, dll_base + 0x00062CF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC92EE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC92EE0, dll_base + 0x00062EE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC92EF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC92EF0, dll_base + 0x00062EF0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC92F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC92F10, dll_base + 0x00062F10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC931D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC931D0, dll_base + 0x000631D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC933F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRTRADE_CopyTradeSaveDataToBuffer, dll_base + 0x000633F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			uint8_t moo_pBuffer{};
			D2UnitStrc original_pUnit{};
			uint8_t original_pBuffer{};
			int32_t nBufferSize{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				uint8_t& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pBuffer);
			setup_data(original_pUnit, original_pBuffer);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, &moo_pBuffer, nBufferSize);
			auto original_result = original(&original_pUnit, &original_pBuffer, nBufferSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC93430, dll_base + 0x00063430);
		
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
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pItem);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC93740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC93740, dll_base + 0x00063740);
		
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC937A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PLRTRADE_IsInteractingWithPlayer, dll_base + 0x000637A0);
		
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit);
			auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC937F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PLRTRADE_Last_6FC937F0, dll_base + 0x000637F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, a3, a4);
			original(&original_pGame, &original_pPlayer, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
}
