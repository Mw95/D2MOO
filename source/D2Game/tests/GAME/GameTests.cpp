#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <UNIT/SUnit.h>
#include <Units/Units.h>


TEST_SUITE("GameTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC356D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC356D0, dll_base + 0x000056D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t a1{};
			int32_t a2{};
			int32_t a3{};
			int32_t a4{};
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3, a4, a5);
			const auto original_result = original(a1, a2, a3, a4, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35700" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC35700, dll_base + 0x00005700);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35720" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC35720, dll_base + 0x00005720);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC357C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10046, dll_base + 0x000057C0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10050, dll_base + 0x00005810);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetGameGUIDFromGameId, dll_base + 0x00005840);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			uint16_t nGameId{};

			// Call both implementations
			const auto moo_result = sut(nGameId);
			const auto original_result = original(nGameId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_InitGameDataTable, dll_base + 0x00005880);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameDataTableStrc pGameDataTbl{};
				
				return std::tuple{ pGameDataTbl };
			};
			
			// Input data
			auto [moo_pGameDataTbl] = setup_data();
			auto [original_pGameDataTbl] = setup_data();
			void* moo_pGameList = nullptr;
			void* original_pGameList = nullptr;

			// Call both implementations
			sut(&moo_pGameDataTbl, moo_pGameList);
			original(&original_pGameDataTbl, original_pGameList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGameDataTbl, original_pGameDataTbl, "Comparing pGameDataTbl");
			SKIP_MOO_CHECK_EQ(moo_pGameList, original_pGameList, "Comparing pGameList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC358E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SetServerCallbackFunctions, dll_base + 0x000058E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ServerCallbackFunctions pD2ServerCallbackFunctions{};
				
				return std::tuple{ pD2ServerCallbackFunctions };
			};
			
			// Input data
			auto [moo_pD2ServerCallbackFunctions] = setup_data();
			auto [original_pD2ServerCallbackFunctions] = setup_data();

			// Call both implementations
			sut(&moo_pD2ServerCallbackFunctions);
			original(&original_pD2ServerCallbackFunctions);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pD2ServerCallbackFunctions, original_pD2ServerCallbackFunctions, "Comparing pD2ServerCallbackFunctions");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35920 (#10010)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SetInitSeed, dll_base + 0x00005920);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nInitSeed{};

			// Call both implementations
			sut(nInitSeed);
			original(nInitSeed);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10011, dll_base + 0x00005930);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_ResolveGameNameConflict, dll_base + 0x00005A10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGameToSanitize{};
				char szGameName{};
				
				return std::tuple{ pGameToSanitize, szGameName };
			};
			
			// Input data
			auto [moo_pGameToSanitize, moo_szGameName] = setup_data();
			auto [original_pGameToSanitize, original_szGameName] = setup_data();
			int32_t a3{};

			// Call both implementations
			sut(&moo_pGameToSanitize, &moo_szGameName, a3);
			original(&original_pGameToSanitize, &original_szGameName, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGameToSanitize, original_pGameToSanitize, "Comparing pGameToSanitize");
			SKIP_MOO_CHECK_EQ(moo_szGameName, original_szGameName, "Comparing szGameName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35CB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_VerifyCreateNewGame, dll_base + 0x00005CB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GSPacketClt66 pPacket{};
				
				return std::tuple{ pPacket };
			};
			
			// Input data
			auto [moo_pPacket] = setup_data();
			auto [original_pPacket] = setup_data();
			int32_t nClientId{};

			// Call both implementations
			const auto moo_result = sut(nClientId, &moo_pPacket);
			const auto original_result = original(nClientId, &original_pPacket);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35E50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10056, dll_base + 0x00005E50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t a1{};

			// Call both implementations
			sut(a1);
			original(a1);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35E70 (#10047)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_CreateNewEmptyGame, dll_base + 0x00005E70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szGameName{};
				uint16_t pGameId{};
				
				return std::tuple{ szGameName, pGameId };
			};
			
			// Input data
			auto [moo_szGameName, moo_pGameId] = setup_data();
			auto [original_szGameName, original_pGameId] = setup_data();
			char szPassword{};
			char szGameDescription{};
			uint32_t nFlags{};
			uint8_t nArenaTemplate{};
			uint8_t nMaxLevelDifference{};
			uint8_t nMaxPlayers{};

			// Call both implementations
			const auto moo_result = sut(&moo_szGameName, &szPassword, &szGameDescription, nFlags, nArenaTemplate, nMaxLevelDifference, nMaxPlayers, &moo_pGameId);
			const auto original_result = original(&original_szGameName, &szPassword, &szGameDescription, nFlags, nArenaTemplate, nMaxLevelDifference, nMaxPlayers, &original_pGameId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szGameName, original_szGameName, "Comparing szGameName");
			SKIP_MOO_CHECK_EQ(moo_pGameId, original_pGameId, "Comparing pGameId");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36280 (#10007)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_ReceiveDatabaseCharacter, dll_base + 0x00006280);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				FILETIME pSaveCreationTimestamp{};
				
				return std::tuple{ pSaveCreationTimestamp };
			};
			
			// Input data
			auto [moo_pSaveCreationTimestamp] = setup_data();
			auto [original_pSaveCreationTimestamp] = setup_data();
			int32_t nClientId{};
			uint8_t pSaveData{};
			uint16_t nSaveSize{};
			uint16_t nTotalSize{};
			int32_t a5{};
			int32_t a6{};
			int32_t nCharSaveTransactionToken{};

			// Call both implementations
			const auto moo_result = sut(nClientId, &pSaveData, nSaveSize, nTotalSize, a5, a6, &moo_pSaveCreationTimestamp, nCharSaveTransactionToken);
			const auto original_result = original(nClientId, &pSaveData, nSaveSize, nTotalSize, a5, a6, &original_pSaveCreationTimestamp, nCharSaveTransactionToken);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSaveCreationTimestamp, original_pSaveCreationTimestamp, "Comparing pSaveCreationTimestamp");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SendGameInit, dll_base + 0x00006570);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szGameName{};
				
				return std::tuple{ szGameName };
			};
			
			// Input data
			auto [moo_szGameName] = setup_data();
			auto [original_szGameName] = setup_data();
			int32_t nClientId{};
			uint8_t nGameType{};
			uint8_t nCharTemplate{};
			char szClientName{};
			int32_t nArena{};
			uint32_t nFlags{};
			int32_t nArenaTemplate{};
			int32_t a9{};
			int32_t a10{};
			uint8_t nDifficulty{};
			uint8_t nLocale{};
			int32_t a13{};
			int32_t a14{};

			// Call both implementations
			sut(nClientId, &moo_szGameName, nGameType, nCharTemplate, &szClientName, nArena, nFlags, nArenaTemplate, a9, a10, nDifficulty, nLocale, a13, a14);
			original(nClientId, &original_szGameName, nGameType, nCharTemplate, &szClientName, nArena, nFlags, nArenaTemplate, a9, a10, nDifficulty, nLocale, a13, a14);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szGameName, original_szGameName, "Comparing szGameName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC369C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC369C0, dll_base + 0x000069C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pClient] = setup_data();
			auto [original_pGame, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pClient);
			original(&original_pGame, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36AA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SendPacket0x5CToAllConnectedClients, dll_base + 0x00006AA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pClient] = setup_data();
			auto [original_pGame, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pClient);
			original(&original_pGame, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_VerifyJoinAct, dll_base + 0x00006AE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};

			// Call both implementations
			const auto moo_result = sut(nClientId);
			const auto original_result = original(nClientId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC36B20, dll_base + 0x00006B20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};
			char szFile{};
			int32_t nLine{};

			// Call both implementations
			sut(nClientId, &szFile, nLine);
			original(nClientId, &szFile, nLine);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36C20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC36C20, dll_base + 0x00006C20);
		
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
			int32_t nClientId{};
			char szFile{};
			int32_t nLine{};

			// Call both implementations
			sut(&moo_pGame, nClientId, &szFile, nLine);
			original(&original_pGame, nClientId, &szFile, nLine);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36C60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SendActInit, dll_base + 0x00006C60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};

			// Call both implementations
			sut(nClientId);
			original(nClientId);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36DF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_VerifyJoinGame, dll_base + 0x00006DF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char pszInOutAccountName{};
				int32_t pOutCharSaveTransactionToken{};
				int32_t a9{};
				int32_t a10{};
				
				return std::tuple{ pszInOutAccountName, pOutCharSaveTransactionToken, a9, a10 };
			};
			
			// Input data
			auto [moo_pszInOutAccountName, moo_pOutCharSaveTransactionToken, moo_a9, moo_a10] = setup_data();
			auto [original_pszInOutAccountName, original_pOutCharSaveTransactionToken, original_a9, original_a10] = setup_data();
			int32_t nClientId{};
			uint16_t nGameId{};
			uint8_t nPlayerClass{};
			char szClientName{};
			int32_t nTokenId{};
			uint8_t nLocale{};

			// Call both implementations
			const auto moo_result = sut(nClientId, nGameId, nPlayerClass, &szClientName, nTokenId, &moo_pszInOutAccountName, &moo_pOutCharSaveTransactionToken, nLocale, &moo_a9, &moo_a10);
			const auto original_result = original(nClientId, nGameId, nPlayerClass, &szClientName, nTokenId, &original_pszInOutAccountName, &original_pOutCharSaveTransactionToken, nLocale, &original_a9, &original_a10);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pszInOutAccountName, original_pszInOutAccountName, "Comparing pszInOutAccountName");
			SKIP_MOO_CHECK_EQ(moo_pOutCharSaveTransactionToken, original_pOutCharSaveTransactionToken, "Comparing pOutCharSaveTransactionToken");
			SKIP_MOO_CHECK_EQ(moo_a9, original_a9, "Comparing a9");
			SKIP_MOO_CHECK_EQ(moo_a10, original_a10, "Comparing a10");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37150" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_JoinGame, dll_base + 0x00007150);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szClientName{};
				char szAccountName{};
				
				return std::tuple{ szClientName, szAccountName };
			};
			
			// Input data
			auto [moo_szClientName, moo_szAccountName] = setup_data();
			auto [original_szClientName, original_szAccountName] = setup_data();
			int32_t dwClientId{};
			uint16_t nGameId{};
			int32_t nClass{};
			int32_t nCharSaveTransactionToken{};
			int32_t nLocale{};
			int32_t a8{};
			int32_t a9{};

			// Call both implementations
			sut(dwClientId, nGameId, nClass, &moo_szClientName, &moo_szAccountName, nCharSaveTransactionToken, nLocale, a8, a9);
			original(dwClientId, nGameId, nClass, &original_szClientName, &original_szAccountName, nCharSaveTransactionToken, nLocale, a8, a9);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szClientName, original_szClientName, "Comparing szClientName");
			SKIP_MOO_CHECK_EQ(moo_szAccountName, original_szAccountName, "Comparing szAccountName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37560" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_VerifyEndGame, dll_base + 0x00007560);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};

			// Call both implementations
			const auto moo_result = sut(nClientId);
			const auto original_result = original(nClientId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC375A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_TriggerClientSave, dll_base + 0x000075A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ClientStrc pClient{};
				D2GameStrc pGame{};
				
				return std::tuple{ pClient, pGame };
			};
			
			// Input data
			auto [moo_pClient, moo_pGame] = setup_data();
			auto [original_pClient, original_pGame] = setup_data();

			// Call both implementations
			sut(&moo_pClient, &moo_pGame);
			original(&original_pClient, &original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_DisconnectClient, dll_base + 0x00007690);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pClient] = setup_data();
			auto [original_pGame, original_pClient] = setup_data();
			D2C_SRV2CLT5A_TYPES nEventType{};

			// Call both implementations
			sut(&moo_pGame, &moo_pClient, nEventType);
			original(&original_pGame, &original_pClient, nEventType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_DisconnectClientById, dll_base + 0x00007750);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};
			D2C_SRV2CLT5A_TYPES nEventType{};

			// Call both implementations
			sut(nClientId, nEventType);
			original(nClientId, nEventType);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37880" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_DisconnectClientByName, dll_base + 0x00007880);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			char szClientName{};
			D2C_SRV2CLT5A_TYPES nEventType{};

			// Call both implementations
			const auto moo_result = sut(&szClientName, nEventType);
			const auto original_result = original(&szClientName, nEventType);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC379C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10024_RemoveClientFromGame, dll_base + 0x000079C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};

			// Call both implementations
			sut(nClientId);
			original(nClientId);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37B10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC37B10, dll_base + 0x00007B10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_SendSaveHeaderPart_6FC37B90, dll_base + 0x00007B90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pClient] = setup_data();
			auto [original_pGame, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pClient);
			original(&original_pGame, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37CE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_EndGame, dll_base + 0x00007CE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};
			int32_t a2{};

			// Call both implementations
			sut(nClientId, a2);
			original(nClientId, a2);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37FB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC37FB0, dll_base + 0x00007FB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pClient] = setup_data();
			auto [original_pGame, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pClient);
			original(&original_pGame, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC380D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC380D0, dll_base + 0x000080D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ClientStrc pClient{};
				
				return std::tuple{ pClient };
			};
			
			// Input data
			auto [moo_pClient] = setup_data();
			auto [original_pClient] = setup_data();
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			// Call both implementations
			sut(&moo_pClient, moo_pArg);
			original(&original_pClient, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC380F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC380F0, dll_base + 0x000080F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ClientStrc pClient{};
				
				return std::tuple{ pClient };
			};
			
			// Input data
			auto [moo_pClient] = setup_data();
			auto [original_pClient] = setup_data();
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			// Call both implementations
			sut(&moo_pClient, moo_pArg);
			original(&original_pClient, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC38100" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_VerifyDisconnect, dll_base + 0x00008100);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};

			// Call both implementations
			const auto moo_result = sut(nClientId);
			const auto original_result = original(nClientId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC38140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC38140, dll_base + 0x00008140);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			void* moo_a1 = nullptr;
			void* original_a1 = nullptr;
			int32_t a2{};

			// Call both implementations
			sut(moo_a1, a2);
			original(original_a1, a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC38530 (#10003)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_ProcessNetworkMessages, dll_base + 0x00008530);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC385A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC385A0, dll_base + 0x000085A0);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom);
			original(&original_pGame, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC38610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_UpdateEnvironment, dll_base + 0x00008610);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC386D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_UpdateProgress, dll_base + 0x000086D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC38990" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_PopulateRoom, dll_base + 0x00008990);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom);
			original(&original_pGame, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC389C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_UpdateAllClients_6FC389C0, dll_base + 0x000089C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC38E00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC38E00, dll_base + 0x00008E00);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC38E20 (#10004)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_UpdateGamesProgress, dll_base + 0x00008E20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t a1{};

			// Call both implementations
			const auto moo_result = sut(a1);
			const auto original_result = original(a1);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC39030, dll_base + 0x00009030);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pClient] = setup_data();
			auto [original_pGame, original_pClient] = setup_data();
			int32_t a3{};
			int32_t nUnused{};

			// Call both implementations
			sut(&moo_pGame, &moo_pClient, a3, nUnused);
			original(&original_pGame, &original_pClient, a3, nUnused);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC39270, dll_base + 0x00009270);
		
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
			int32_t a2{};

			// Call both implementations
			sut(&moo_pGame, a2);
			original(&original_pGame, a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC392A0 (#10005)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_UpdateClients, dll_base + 0x000092A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t a1{};
			int32_t a2{};

			// Call both implementations
			sut(a1, a2);
			original(a1, a2);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC394E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetGameByClientId, dll_base + 0x000094E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};

			// Call both implementations
			const auto moo_result = sut(nClientId);
			const auto original_result = original(nClientId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC395B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_LeaveGamesCriticalSection, dll_base + 0x000095B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_CloseGame, dll_base + 0x00009600);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			D2GameGUID nGameGUID{};

			// Call both implementations
			sut(nGameGUID);
			original(nGameGUID);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC39870, dll_base + 0x00009870);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nClientId{};

			// Call both implementations
			sut(nClientId);
			original(nClientId);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC399A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC399A0, dll_base + 0x000099A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GSPacketClt6B pPacket{};
				
				return std::tuple{ pPacket };
			};
			
			// Input data
			auto [moo_pPacket] = setup_data();
			auto [original_pPacket] = setup_data();
			int32_t nClientId{};

			// Call both implementations
			const auto moo_result = sut(nClientId, &moo_pPacket);
			const auto original_result = original(nClientId, &original_pPacket);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPacket, original_pPacket, "Comparing pPacket");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC399C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_CloseAllGames, dll_base + 0x000099C0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39B50 (#10012)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetGamesCount, dll_base + 0x00009B50);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39B70 (#10057)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10057, dll_base + 0x00009B70);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10053, dll_base + 0x00009C70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int16_t pCount{};
				
				return std::tuple{ pCount };
			};
			
			// Input data
			auto [moo_pCount] = setup_data();
			auto [original_pCount] = setup_data();
			int32_t nArraySize{};

			// Call both implementations
			sut(&moo_pCount, nArraySize);
			original(&original_pCount, nArraySize);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCount, original_pCount, "Comparing pCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39D80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10054, dll_base + 0x00009D80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				uint16_t a1{};
				
				return std::tuple{ a1 };
			};
			
			// Input data
			auto [moo_a1] = setup_data();
			auto [original_a1] = setup_data();
			int32_t nMaxCount{};

			// Call both implementations
			sut(&moo_a1, nMaxCount);
			original(&original_a1, nMaxCount);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39EC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10051, dll_base + 0x00009EC0);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39ED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetMemoryUsage, dll_base + 0x00009ED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int pCurrentMemoryUsage{};
				int pPeakMemoryUsageInLast10s{};
				
				return std::tuple{ pCurrentMemoryUsage, pPeakMemoryUsageInLast10s };
			};
			
			// Input data
			auto [moo_pCurrentMemoryUsage, moo_pPeakMemoryUsageInLast10s] = setup_data();
			auto [original_pCurrentMemoryUsage, original_pPeakMemoryUsageInLast10s] = setup_data();

			// Call both implementations
			sut(&moo_pCurrentMemoryUsage, &moo_pPeakMemoryUsageInLast10s);
			original(&original_pCurrentMemoryUsage, &original_pPeakMemoryUsageInLast10s);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pCurrentMemoryUsage, original_pCurrentMemoryUsage, "Comparing pCurrentMemoryUsage");
			SKIP_MOO_CHECK_EQ(moo_pPeakMemoryUsageInLast10s, original_pPeakMemoryUsageInLast10s, "Comparing pPeakMemoryUsageInLast10s");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39EF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10013, dll_base + 0x00009EF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			uint16_t nGameId{};

			// Call both implementations
			const auto moo_result = sut(nGameId);
			const auto original_result = original(nGameId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39FF0 (#10014)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetGameInformation, dll_base + 0x00009FF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameInfoStrc pGameInfo{};
				
				return std::tuple{ pGameInfo };
			};
			
			// Input data
			auto [moo_pGameInfo] = setup_data();
			auto [original_pGameInfo] = setup_data();
			uint16_t nGameId{};

			// Call both implementations
			const auto moo_result = sut(nGameId, &moo_pGameInfo);
			const auto original_result = original(nGameId, &original_pGameInfo);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGameInfo, original_pGameInfo, "Comparing pGameInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A390 (#10015)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetGameServerGameIds, dll_base + 0x0000A390);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				uint16_t pServerToken{};
				
				return std::tuple{ pServerToken };
			};
			
			// Input data
			auto [moo_pServerToken] = setup_data();
			auto [original_pServerToken] = setup_data();
			int32_t nMaxCount{};

			// Call both implementations
			const auto moo_result = sut(&moo_pServerToken, nMaxCount);
			const auto original_result = original(&original_pServerToken, nMaxCount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pServerToken, original_pServerToken, "Comparing pServerToken");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A490 (#10016)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetPlayerUnitsCount, dll_base + 0x0000A490);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			uint16_t nGameId{};

			// Call both implementations
			const auto moo_result = sut(nGameId);
			const auto original_result = original(nGameId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A5A0 (#10017)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetPlayerUnitsInfo, dll_base + 0x0000A5A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitInfoStrc pUnitInfo{};
				
				return std::tuple{ pUnitInfo };
			};
			
			// Input data
			auto [moo_pUnitInfo] = setup_data();
			auto [original_pUnitInfo] = setup_data();
			uint16_t nGameId{};
			int32_t nMaxCount{};

			// Call both implementations
			const auto moo_result = sut(nGameId, &moo_pUnitInfo, nMaxCount);
			const auto original_result = original(nGameId, &original_pUnitInfo, nMaxCount);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnitInfo, original_pUnitInfo, "Comparing pUnitInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A6F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_ReturnArgument, dll_base + 0x0000A6F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t a1{};

			// Call both implementations
			const auto moo_result = sut(a1);
			const auto original_result = original(a1);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A700" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetPlayerDescription, dll_base + 0x0000A700);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szDescription{};
				
				return std::tuple{ szDescription };
			};
			
			// Input data
			auto [moo_szDescription] = setup_data();
			auto [original_szDescription] = setup_data();
			int32_t nClassId{};

			// Call both implementations
			sut(&moo_szDescription, nClassId);
			original(&original_szDescription, nClassId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szDescription, original_szDescription, "Comparing szDescription");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A7C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetMonsterDescription, dll_base + 0x0000A7C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szDescription{};
				
				return std::tuple{ szDescription };
			};
			
			// Input data
			auto [moo_szDescription] = setup_data();
			auto [original_szDescription] = setup_data();
			int32_t nClassId{};

			// Call both implementations
			sut(&moo_szDescription, nClassId);
			original(&original_szDescription, nClassId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szDescription, original_szDescription, "Comparing szDescription");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetObjectDescription, dll_base + 0x0000A820);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szDescription{};
				
				return std::tuple{ szDescription };
			};
			
			// Input data
			auto [moo_szDescription] = setup_data();
			auto [original_szDescription] = setup_data();
			int32_t nClassId{};

			// Call both implementations
			sut(&moo_szDescription, nClassId);
			original(&original_szDescription, nClassId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szDescription, original_szDescription, "Comparing szDescription");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A860" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetItemDescription, dll_base + 0x0000A860);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szDescription{};
				
				return std::tuple{ szDescription };
			};
			
			// Input data
			auto [moo_szDescription] = setup_data();
			auto [original_szDescription] = setup_data();
			int32_t nClassId{};

			// Call both implementations
			sut(&moo_szDescription, nClassId);
			original(&original_szDescription, nClassId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szDescription, original_szDescription, "Comparing szDescription");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A8A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetMissileDescription, dll_base + 0x0000A8A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szDescription{};
				
				return std::tuple{ szDescription };
			};
			
			// Input data
			auto [moo_szDescription] = setup_data();
			auto [original_szDescription] = setup_data();
			int32_t nClassId{};

			// Call both implementations
			sut(&moo_szDescription, nClassId);
			original(&original_szDescription, nClassId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szDescription, original_szDescription, "Comparing szDescription");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3A8B0 (#10019)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetUnitsDescriptions, dll_base + 0x0000A8B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitDescriptionListStrc pUnitDescriptionsList{};
				
				return std::tuple{ pUnitDescriptionsList };
			};
			
			// Input data
			auto [moo_pUnitDescriptionsList] = setup_data();
			auto [original_pUnitDescriptionsList] = setup_data();
			uint16_t nGameId{};
			uint32_t eType{};

			// Call both implementations
			sut(nGameId, &moo_pUnitDescriptionsList, eType);
			original(nGameId, &original_pUnitDescriptionsList, eType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnitDescriptionsList, original_pUnitDescriptionsList, "Comparing pUnitDescriptionsList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3AB20 (#10018)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10018, dll_base + 0x0000AB20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitInfoStrc pUnitInfo{};
				int32_t pUnitType{};
				int32_t pUnitGUID{};
				
				return std::tuple{ pUnitInfo, pUnitType, pUnitGUID };
			};
			
			// Input data
			auto [moo_pUnitInfo, moo_pUnitType, moo_pUnitGUID] = setup_data();
			auto [original_pUnitInfo, original_pUnitType, original_pUnitGUID] = setup_data();
			uint16_t nGameId{};
			int32_t nMaxCount{};

			// Call both implementations
			const auto moo_result = sut(nGameId, nMaxCount, &moo_pUnitInfo, &moo_pUnitType, &moo_pUnitGUID);
			const auto original_result = original(nGameId, nMaxCount, &original_pUnitInfo, &original_pUnitType, &original_pUnitGUID);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnitInfo, original_pUnitInfo, "Comparing pUnitInfo");
			SKIP_MOO_CHECK_EQ(moo_pUnitType, original_pUnitType, "Comparing pUnitType");
			SKIP_MOO_CHECK_EQ(moo_pUnitGUID, original_pUnitGUID, "Comparing pUnitGUID");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3ACD0 (#10020)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_GetStatistics, dll_base + 0x0000ACD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStatisticsStrc pStats{};
				
				return std::tuple{ pStats };
			};
			
			// Input data
			auto [moo_pStats] = setup_data();
			auto [original_pStats] = setup_data();

			// Call both implementations
			sut(&moo_pStats);
			original(&original_pStats);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pStats, original_pStats, "Comparing pStats");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3AE10 (#10021)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SendMessageToAllClients, dll_base + 0x0000AE10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t a1{};
			int32_t nPacketParam{};
			char szMessage{};

			// Call both implementations
			sut(a1, nPacketParam, &szMessage);
			original(a1, nPacketParam, &szMessage);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3AFB0 (#10022)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SendMessageToGameClients, dll_base + 0x0000AFB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				char szMessage{};
				
				return std::tuple{ szMessage };
			};
			
			// Input data
			auto [moo_szMessage] = setup_data();
			auto [original_szMessage] = setup_data();
			uint16_t nGameId{};

			// Call both implementations
			sut(nGameId, &moo_szMessage);
			original(nGameId, &original_szMessage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szMessage, original_szMessage, "Comparing szMessage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B0E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_ForEachIngameClient, dll_base + 0x0000B0E0);
		
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
			GAME_ForEachIngameClientCallbackPtr pFn{};
			void* moo_pContext = nullptr;
			void* original_pContext = nullptr;

			// Call both implementations
			sut(&moo_pGame, pFn, moo_pContext);
			original(&original_pGame, pFn, original_pContext);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pContext, original_pContext, "Comparing pContext");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3B160, dll_base + 0x0000B160);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_LeaveGlobalGamesCriticalSection, dll_base + 0x0000B220);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Game_10008, dll_base + 0x0000B280);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t a1{};

			// Call both implementations
			sut(a1);
			original(a1);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B2A0 (#10009)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SetGlobalAct, dll_base + 0x0000B2A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nAct{};

			// Call both implementations
			sut(nAct);
			original(nAct);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B2B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3B2B0, dll_base + 0x0000B2B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2GameStrc pGame{};
				
				return std::tuple{ pUnit, pGame };
			};
			
			// Input data
			auto [moo_pUnit, moo_pGame] = setup_data();
			auto [original_pUnit, original_pGame] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_pGame);
			original(&original_pUnit, &original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC3B3D0, dll_base + 0x0000B3D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ClientStrc pClient{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pClient, pUnit };
			};
			
			// Input data
			auto [moo_pClient, moo_pUnit] = setup_data();
			auto [original_pClient, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pClient, &moo_pUnit);
			original(&original_pClient, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B510" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_SyncEnterLock, dll_base + 0x0000B510);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameDataTableStrc pGameDataTable{};
				int32_t pLockHandle{};
				
				return std::tuple{ pGameDataTable, pLockHandle };
			};
			
			// Input data
			auto [moo_pGameDataTable, moo_pLockHandle] = setup_data();
			auto [original_pGameDataTable, original_pLockHandle] = setup_data();
			int32_t nUnused{};
			int32_t bForWriting{};

			// Call both implementations
			sut(&moo_pGameDataTable, nUnused, &moo_pLockHandle, bForWriting);
			original(&original_pGameDataTable, nUnused, &original_pLockHandle, bForWriting);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGameDataTable, original_pGameDataTable, "Comparing pGameDataTable");
			SKIP_MOO_CHECK_EQ(moo_pLockHandle, original_pLockHandle, "Comparing pLockHandle");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_SyncLeaveLock, dll_base + 0x0000B540);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameDataTableStrc pGameDataTable{};
				
				return std::tuple{ pGameDataTable };
			};
			
			// Input data
			auto [moo_pGameDataTable] = setup_data();
			auto [original_pGameDataTable] = setup_data();
			int32_t nUnused{};
			int32_t tLockHandle{};

			// Call both implementations
			sut(&moo_pGameDataTable, nUnused, tLockHandle);
			original(&original_pGameDataTable, nUnused, tLockHandle);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGameDataTable, original_pGameDataTable, "Comparing pGameDataTable");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B560" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_TLink_NextLink, dll_base + 0x0000B560);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				TSLink<D2GameStrc> pLink{};
				
				return std::tuple{ pLink };
			};
			
			// Input data
			auto [moo_pLink] = setup_data();
			auto [original_pLink] = setup_data();
			int32_t nUnused{};
			int nLinkOffset{};

			// Call both implementations
			const auto moo_result = sut(&moo_pLink, nUnused, nLinkOffset);
			const auto original_result = original(&original_pLink, nUnused, nLinkOffset);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLink, original_pLink, "Comparing pLink");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B590" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_New, dll_base + 0x0000B590);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameDataTableStrc pGameDataTable{};
				HASHKEY_NONE pKey{};
				
				return std::tuple{ pGameDataTable, pKey };
			};
			
			// Input data
			auto [moo_pGameDataTable, moo_pKey] = setup_data();
			auto [original_pGameDataTable, original_pKey] = setup_data();
			int32_t nUnused{};
			D2GameGUID nGameGUID{};
			int32_t extrabytes{};
			int32_t flags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGameDataTable, nUnused, nGameGUID, &moo_pKey, extrabytes, flags);
			const auto original_result = original(&original_pGameDataTable, nUnused, nGameGUID, &original_pKey, extrabytes, flags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGameDataTable, original_pGameDataTable, "Comparing pGameDataTable");
			SKIP_MOO_CHECK_EQ(moo_pKey, original_pKey, "Comparing pKey");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B6A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_Ptr, dll_base + 0x0000B6A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameDataTableStrc pGameDataTable{};
				
				return std::tuple{ pGameDataTable };
			};
			
			// Input data
			auto [moo_pGameDataTable] = setup_data();
			auto [original_pGameDataTable] = setup_data();
			int32_t nUnused{};
			D2GameGUID nGameGUID{};
			HASHKEY_NONE pHashKey{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGameDataTable, nUnused, nGameGUID, &pHashKey);
			const auto original_result = original(&original_pGameDataTable, nUnused, nGameGUID, &pHashKey);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGameDataTable, original_pGameDataTable, "Comparing pGameDataTable");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B6F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_TSExplicitList_Link, dll_base + 0x0000B6F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) pNode{};
				D2GameStrc ptr{};
				
				return std::tuple{ pNode, ptr };
			};
			
			// Input data
			auto [moo_pNode, moo_ptr] = setup_data();
			auto [original_pNode, original_ptr] = setup_data();
			int32_t nUnused{};

			// Call both implementations
			const auto moo_result = sut(&moo_pNode, nUnused, &moo_ptr);
			const auto original_result = original(&original_pNode, nUnused, &original_ptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pNode, original_pNode, "Comparing pNode");
			SKIP_MOO_CHECK_EQ(moo_ptr, original_ptr, "Comparing ptr");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B8E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_TSExplicitList_UnlinkAll_AndUninitTerminator, dll_base + 0x0000B8E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) pList{};
				
				return std::tuple{ pList };
			};
			
			// Input data
			auto [moo_pList] = setup_data();
			auto [original_pList] = setup_data();

			// Call both implementations
			sut(&moo_pList);
			original(&original_pList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B960" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_TSLink_Unlink, dll_base + 0x0000B960);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				TSLink<D2GameStrc> pLink{};
				
				return std::tuple{ pLink };
			};
			
			// Input data
			auto [moo_pLink] = setup_data();
			auto [original_pLink] = setup_data();

			// Call both implementations
			sut(&moo_pLink);
			original(&original_pLink);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pLink, original_pLink, "Comparing pLink");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3B9A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_GrowableArray_TSExplicitList_SetCount, dll_base + 0x0000B9A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				TSGrowableArray<STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot)> pArray{};
				
				return std::tuple{ pArray };
			};
			
			// Input data
			auto [moo_pArray] = setup_data();
			auto [original_pArray] = setup_data();
			int32_t nUnused{};
			uint32_t nCount{};

			// Call both implementations
			sut(&moo_pArray, nUnused, nCount);
			original(&original_pArray, nUnused, nCount);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pArray, original_pArray, "Comparing pArray");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BB10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_TSExplicitList_Destroy, dll_base + 0x0000BB10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) pNode{};
				
				return std::tuple{ pNode };
			};
			
			// Input data
			auto [moo_pNode] = setup_data();
			auto [original_pNode] = setup_data();
			int32_t nUnused{};
			char bShouldFree{};

			// Call both implementations
			sut(&moo_pNode, nUnused, bShouldFree);
			original(&original_pNode, nUnused, bShouldFree);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pNode, original_pNode, "Comparing pNode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BB40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_TSExplicitList_InitializeTerminator, dll_base + 0x0000BB40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) pList{};
				
				return std::tuple{ pList };
			};
			
			// Input data
			auto [moo_pList] = setup_data();
			auto [original_pList] = setup_data();

			// Call both implementations
			sut(&moo_pList);
			original(&original_pList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BB50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_TSExplicitList_InplaceNew, dll_base + 0x0000BB50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			void* moo_pMemory = nullptr;
			void* original_pMemory = nullptr;

			// Call both implementations
			sut(moo_pMemory);
			original(original_pMemory);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemory, original_pMemory, "Comparing pMemory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BB80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GameDataTable_TSExplicitList_InplaceNew_WithList, dll_base + 0x0000BB80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				TSExplicitList<D2GameStrc, 0xDDDDDDDD> pList{};
				
				return std::tuple{ pList };
			};
			
			// Input data
			auto [moo_pList] = setup_data();
			auto [original_pList] = setup_data();
			void* moo_pMemory = nullptr;
			void* original_pMemory = nullptr;
			int32_t nUnused{};

			// Call both implementations
			sut(moo_pMemory, nUnused, &moo_pList);
			original(original_pMemory, nUnused, &original_pList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemory, original_pMemory, "Comparing pMemory");
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
}
