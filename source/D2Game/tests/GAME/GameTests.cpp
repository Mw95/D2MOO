#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			int32_t a1{};
			int32_t a2{};
			int32_t a3{};
			int32_t a4{};
			int32_t a5{};

			// Call both implementations
			auto moo_result = sut(a1, a2, a3, a4, a5);
			auto original_result = original(a1, a2, a3, a4, a5);
			
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
			auto moo_result = sut();
			auto original_result = original();
			
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
			auto moo_result = sut();
			auto original_result = original();
			
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
			auto moo_result = sut();
			auto original_result = original();
			
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
			auto moo_result = sut();
			auto original_result = original();
			
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
			uint16_t nGameId{};

			// Call both implementations
			auto moo_result = sut(nGameId);
			auto original_result = original(nGameId);
			
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
			// Input data
			D2GameDataTableStrc moo_pGameDataTbl{};
			D2GameDataTableStrc original_pGameDataTbl{};
			void* moo_pGameList = nullptr;
			void* original_pGameList = nullptr;

			const auto setup_data = [](
				D2GameDataTableStrc& pGameDataTbl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGameDataTbl);
			setup_data(original_pGameDataTbl);

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
			// Input data
			D2ServerCallbackFunctions moo_pD2ServerCallbackFunctions{};
			D2ServerCallbackFunctions original_pD2ServerCallbackFunctions{};

			const auto setup_data = [](
				D2ServerCallbackFunctions& pD2ServerCallbackFunctions
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pD2ServerCallbackFunctions);
			setup_data(original_pD2ServerCallbackFunctions);

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
			auto moo_result = sut();
			auto original_result = original();
			
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
			// Input data
			D2GameStrc moo_pGameToSanitize{};
			char moo_szGameName{};
			D2GameStrc original_pGameToSanitize{};
			char original_szGameName{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGameToSanitize,
				char& szGameName
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGameToSanitize, moo_szGameName);
			setup_data(original_pGameToSanitize, original_szGameName);

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
			// Input data
			D2GSPacketClt66 moo_pPacket{};
			D2GSPacketClt66 original_pPacket{};
			int32_t nClientId{};

			const auto setup_data = [](
				D2GSPacketClt66& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPacket);
			setup_data(original_pPacket);

			// Call both implementations
			auto moo_result = sut(nClientId, &moo_pPacket);
			auto original_result = original(nClientId, &original_pPacket);
			
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
			// Input data
			char moo_szGameName{};
			uint16_t moo_pGameId{};
			char original_szGameName{};
			uint16_t original_pGameId{};
			char szPassword{};
			char szGameDescription{};
			uint32_t nFlags{};
			uint8_t nArenaTemplate{};
			uint8_t nMaxLevelDifference{};
			uint8_t nMaxPlayers{};

			const auto setup_data = [](
				char& szGameName,
				uint16_t& pGameId
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szGameName, moo_pGameId);
			setup_data(original_szGameName, original_pGameId);

			// Call both implementations
			auto moo_result = sut(&moo_szGameName, &szPassword, &szGameDescription, nFlags, nArenaTemplate, nMaxLevelDifference, nMaxPlayers, &moo_pGameId);
			auto original_result = original(&original_szGameName, &szPassword, &szGameDescription, nFlags, nArenaTemplate, nMaxLevelDifference, nMaxPlayers, &original_pGameId);
			
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
			// Input data
			FILETIME moo_pSaveCreationTimestamp{};
			FILETIME original_pSaveCreationTimestamp{};
			int32_t nClientId{};
			uint8_t pSaveData{};
			uint16_t nSaveSize{};
			uint16_t nTotalSize{};
			int32_t a5{};
			int32_t a6{};
			int32_t nCharSaveTransactionToken{};

			const auto setup_data = [](
				FILETIME& pSaveCreationTimestamp
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSaveCreationTimestamp);
			setup_data(original_pSaveCreationTimestamp);

			// Call both implementations
			auto moo_result = sut(nClientId, &pSaveData, nSaveSize, nTotalSize, a5, a6, &moo_pSaveCreationTimestamp, nCharSaveTransactionToken);
			auto original_result = original(nClientId, &pSaveData, nSaveSize, nTotalSize, a5, a6, &original_pSaveCreationTimestamp, nCharSaveTransactionToken);
			
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
			// Input data
			char moo_szGameName{};
			char original_szGameName{};
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

			const auto setup_data = [](
				char& szGameName
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szGameName);
			setup_data(original_szGameName);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36AA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_SendPacket0x5CToAllConnectedClients, dll_base + 0x00006AA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC36AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_VerifyJoinAct, dll_base + 0x00006AE0);
		
		SUBCASE("")
		{
			int32_t nClientId{};

			// Call both implementations
			auto moo_result = sut(nClientId);
			auto original_result = original(nClientId);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nClientId{};
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
			// Input data
			char moo_pszInOutAccountName{};
			int32_t moo_pOutCharSaveTransactionToken{};
			int32_t moo_a9{};
			int32_t moo_a10{};
			char original_pszInOutAccountName{};
			int32_t original_pOutCharSaveTransactionToken{};
			int32_t original_a9{};
			int32_t original_a10{};
			int32_t nClientId{};
			uint16_t nGameId{};
			uint8_t nPlayerClass{};
			char szClientName{};
			int32_t nTokenId{};
			uint8_t nLocale{};

			const auto setup_data = [](
				char& pszInOutAccountName,
				int32_t& pOutCharSaveTransactionToken,
				int32_t& a9,
				int32_t& a10
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pszInOutAccountName, moo_pOutCharSaveTransactionToken, moo_a9, moo_a10);
			setup_data(original_pszInOutAccountName, original_pOutCharSaveTransactionToken, original_a9, original_a10);

			// Call both implementations
			auto moo_result = sut(nClientId, nGameId, nPlayerClass, &szClientName, nTokenId, &moo_pszInOutAccountName, &moo_pOutCharSaveTransactionToken, nLocale, &moo_a9, &moo_a10);
			auto original_result = original(nClientId, nGameId, nPlayerClass, &szClientName, nTokenId, &original_pszInOutAccountName, &original_pOutCharSaveTransactionToken, nLocale, &original_a9, &original_a10);
			
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
			// Input data
			char moo_szClientName{};
			char moo_szAccountName{};
			char original_szClientName{};
			char original_szAccountName{};
			int32_t dwClientId{};
			uint16_t nGameId{};
			int32_t nClass{};
			int32_t nCharSaveTransactionToken{};
			int32_t nLocale{};
			int32_t a8{};
			int32_t a9{};

			const auto setup_data = [](
				char& szClientName,
				char& szAccountName
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szClientName, moo_szAccountName);
			setup_data(original_szClientName, original_szAccountName);

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
			int32_t nClientId{};

			// Call both implementations
			auto moo_result = sut(nClientId);
			auto original_result = original(nClientId);
			
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
			// Input data
			D2ClientStrc moo_pClient{};
			D2GameStrc moo_pGame{};
			D2ClientStrc original_pClient{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pGame);
			setup_data(original_pClient, original_pGame);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			D2C_SRV2CLT5A_TYPES nEventType{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient);
			setup_data(original_pGame, original_pClient);

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
			char szClientName{};
			D2C_SRV2CLT5A_TYPES nEventType{};

			// Call both implementations
			auto moo_result = sut(&szClientName, nEventType);
			auto original_result = original(&szClientName, nEventType);
			
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_SendSaveHeaderPart_6FC37B90, dll_base + 0x00007B90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC37CE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_EndGame, dll_base + 0x00007CE0);
		
		SUBCASE("")
		{
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC380D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC380D0, dll_base + 0x000080D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

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
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

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
			int32_t nClientId{};

			// Call both implementations
			auto moo_result = sut(nClientId);
			auto original_result = original(nClientId);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC386D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_UpdateProgress, dll_base + 0x000086D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC38990" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_PopulateRoom, dll_base + 0x00008990);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom);
			setup_data(original_pGame, original_pRoom);

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
			int32_t a1{};

			// Call both implementations
			auto moo_result = sut(a1);
			auto original_result = original(a1);
			
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
			// Input data
			D2GameStrc moo_pGame{};
			D2ClientStrc moo_pClient{};
			D2GameStrc original_pGame{};
			D2ClientStrc original_pClient{};
			int32_t a3{};
			int32_t nUnused{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pClient);
			setup_data(original_pGame, original_pClient);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t a2{};

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC392A0 (#10005)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_UpdateClients, dll_base + 0x000092A0);
		
		SUBCASE("")
		{
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
			int32_t nClientId{};

			// Call both implementations
			auto moo_result = sut(nClientId);
			auto original_result = original(nClientId);
			
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC39600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(GAME_CloseGame, dll_base + 0x00009600);
		
		SUBCASE("")
		{
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
			// Input data
			D2GSPacketClt6B moo_pPacket{};
			D2GSPacketClt6B original_pPacket{};
			int32_t nClientId{};

			const auto setup_data = [](
				D2GSPacketClt6B& pPacket
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPacket);
			setup_data(original_pPacket);

			// Call both implementations
			auto moo_result = sut(nClientId, &moo_pPacket);
			auto original_result = original(nClientId, &original_pPacket);
			
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
			auto moo_result = sut();
			auto original_result = original();
			
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
			auto moo_result = sut();
			auto original_result = original();
			
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
			// Input data
			int16_t moo_pCount{};
			int16_t original_pCount{};
			int32_t nArraySize{};

			const auto setup_data = [](
				int16_t& pCount
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCount);
			setup_data(original_pCount);

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
			// Input data
			uint16_t moo_a1{};
			uint16_t original_a1{};
			int32_t nMaxCount{};

			const auto setup_data = [](
				uint16_t& a1
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_a1);
			setup_data(original_a1);

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
			auto moo_result = sut();
			auto original_result = original();
			
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
			// Input data
			int moo_pCurrentMemoryUsage{};
			int moo_pPeakMemoryUsageInLast10s{};
			int original_pCurrentMemoryUsage{};
			int original_pPeakMemoryUsageInLast10s{};

			const auto setup_data = [](
				int& pCurrentMemoryUsage,
				int& pPeakMemoryUsageInLast10s
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pCurrentMemoryUsage, moo_pPeakMemoryUsageInLast10s);
			setup_data(original_pCurrentMemoryUsage, original_pPeakMemoryUsageInLast10s);

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
			uint16_t nGameId{};

			// Call both implementations
			auto moo_result = sut(nGameId);
			auto original_result = original(nGameId);
			
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
			// Input data
			D2GameInfoStrc moo_pGameInfo{};
			D2GameInfoStrc original_pGameInfo{};
			uint16_t nGameId{};

			const auto setup_data = [](
				D2GameInfoStrc& pGameInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGameInfo);
			setup_data(original_pGameInfo);

			// Call both implementations
			auto moo_result = sut(nGameId, &moo_pGameInfo);
			auto original_result = original(nGameId, &original_pGameInfo);
			
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
			// Input data
			uint16_t moo_pServerToken{};
			uint16_t original_pServerToken{};
			int32_t nMaxCount{};

			const auto setup_data = [](
				uint16_t& pServerToken
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pServerToken);
			setup_data(original_pServerToken);

			// Call both implementations
			auto moo_result = sut(&moo_pServerToken, nMaxCount);
			auto original_result = original(&original_pServerToken, nMaxCount);
			
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
			uint16_t nGameId{};

			// Call both implementations
			auto moo_result = sut(nGameId);
			auto original_result = original(nGameId);
			
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
			// Input data
			D2UnitInfoStrc moo_pUnitInfo{};
			D2UnitInfoStrc original_pUnitInfo{};
			uint16_t nGameId{};
			int32_t nMaxCount{};

			const auto setup_data = [](
				D2UnitInfoStrc& pUnitInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnitInfo);
			setup_data(original_pUnitInfo);

			// Call both implementations
			auto moo_result = sut(nGameId, &moo_pUnitInfo, nMaxCount);
			auto original_result = original(nGameId, &original_pUnitInfo, nMaxCount);
			
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
			int32_t a1{};

			// Call both implementations
			auto moo_result = sut(a1);
			auto original_result = original(a1);
			
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
			// Input data
			char moo_szDescription{};
			char original_szDescription{};
			int32_t nClassId{};

			const auto setup_data = [](
				char& szDescription
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szDescription);
			setup_data(original_szDescription);

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
			// Input data
			char moo_szDescription{};
			char original_szDescription{};
			int32_t nClassId{};

			const auto setup_data = [](
				char& szDescription
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szDescription);
			setup_data(original_szDescription);

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
			// Input data
			char moo_szDescription{};
			char original_szDescription{};
			int32_t nClassId{};

			const auto setup_data = [](
				char& szDescription
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szDescription);
			setup_data(original_szDescription);

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
			// Input data
			char moo_szDescription{};
			char original_szDescription{};
			int32_t nClassId{};

			const auto setup_data = [](
				char& szDescription
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szDescription);
			setup_data(original_szDescription);

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
			// Input data
			char moo_szDescription{};
			char original_szDescription{};
			int32_t nClassId{};

			const auto setup_data = [](
				char& szDescription
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szDescription);
			setup_data(original_szDescription);

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
			// Input data
			D2UnitDescriptionListStrc moo_pUnitDescriptionsList{};
			D2UnitDescriptionListStrc original_pUnitDescriptionsList{};
			uint16_t nGameId{};
			uint32_t eType{};

			const auto setup_data = [](
				D2UnitDescriptionListStrc& pUnitDescriptionsList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnitDescriptionsList);
			setup_data(original_pUnitDescriptionsList);

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
			// Input data
			D2UnitInfoStrc moo_pUnitInfo{};
			int32_t moo_pUnitType{};
			int32_t moo_pUnitGUID{};
			D2UnitInfoStrc original_pUnitInfo{};
			int32_t original_pUnitType{};
			int32_t original_pUnitGUID{};
			uint16_t nGameId{};
			int32_t nMaxCount{};

			const auto setup_data = [](
				D2UnitInfoStrc& pUnitInfo,
				int32_t& pUnitType,
				int32_t& pUnitGUID
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnitInfo, moo_pUnitType, moo_pUnitGUID);
			setup_data(original_pUnitInfo, original_pUnitType, original_pUnitGUID);

			// Call both implementations
			auto moo_result = sut(nGameId, nMaxCount, &moo_pUnitInfo, &moo_pUnitType, &moo_pUnitGUID);
			auto original_result = original(nGameId, nMaxCount, &original_pUnitInfo, &original_pUnitType, &original_pUnitGUID);
			
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
			// Input data
			D2GameStatisticsStrc moo_pStats{};
			D2GameStatisticsStrc original_pStats{};

			const auto setup_data = [](
				D2GameStatisticsStrc& pStats
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStats);
			setup_data(original_pStats);

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
			// Input data
			char moo_szMessage{};
			char original_szMessage{};
			uint16_t nGameId{};

			const auto setup_data = [](
				char& szMessage
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szMessage);
			setup_data(original_szMessage);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			GAME_ForEachIngameClientCallbackPtr pFn{};
			void* moo_pContext = nullptr;
			void* original_pContext = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

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
			auto moo_result = sut();
			auto original_result = original();
			
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
			// Input data
			D2UnitStrc moo_pUnit{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pUnit{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pGame);
			setup_data(original_pUnit, original_pGame);

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
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pUnit);
			setup_data(original_pClient, original_pUnit);

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
			// Input data
			D2GameDataTableStrc moo_pGameDataTable{};
			int32_t moo_pLockHandle{};
			D2GameDataTableStrc original_pGameDataTable{};
			int32_t original_pLockHandle{};
			int32_t nUnused{};
			int32_t bForWriting{};

			const auto setup_data = [](
				D2GameDataTableStrc& pGameDataTable,
				int32_t& pLockHandle
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGameDataTable, moo_pLockHandle);
			setup_data(original_pGameDataTable, original_pLockHandle);

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
			// Input data
			D2GameDataTableStrc moo_pGameDataTable{};
			D2GameDataTableStrc original_pGameDataTable{};
			int32_t nUnused{};
			int32_t tLockHandle{};

			const auto setup_data = [](
				D2GameDataTableStrc& pGameDataTable
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGameDataTable);
			setup_data(original_pGameDataTable);

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
			// Input data
			TSLink<D2GameStrc> moo_pLink{};
			TSLink<D2GameStrc> original_pLink{};
			int32_t nUnused{};
			int nLinkOffset{};

			const auto setup_data = [](
				TSLink<D2GameStrc>& pLink
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pLink);
			setup_data(original_pLink);

			// Call both implementations
			auto moo_result = sut(&moo_pLink, nUnused, nLinkOffset);
			auto original_result = original(&original_pLink, nUnused, nLinkOffset);
			
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
			// Input data
			D2GameDataTableStrc moo_pGameDataTable{};
			HASHKEY_NONE moo_pKey{};
			D2GameDataTableStrc original_pGameDataTable{};
			HASHKEY_NONE original_pKey{};
			int32_t nUnused{};
			D2GameGUID nGameGUID{};
			int32_t extrabytes{};
			int32_t flags{};

			const auto setup_data = [](
				D2GameDataTableStrc& pGameDataTable,
				HASHKEY_NONE& pKey
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGameDataTable, moo_pKey);
			setup_data(original_pGameDataTable, original_pKey);

			// Call both implementations
			auto moo_result = sut(&moo_pGameDataTable, nUnused, nGameGUID, &moo_pKey, extrabytes, flags);
			auto original_result = original(&original_pGameDataTable, nUnused, nGameGUID, &original_pKey, extrabytes, flags);
			
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
			// Input data
			D2GameDataTableStrc moo_pGameDataTable{};
			D2GameDataTableStrc original_pGameDataTable{};
			int32_t nUnused{};
			D2GameGUID nGameGUID{};
			HASHKEY_NONE pHashKey{};

			const auto setup_data = [](
				D2GameDataTableStrc& pGameDataTable
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGameDataTable);
			setup_data(original_pGameDataTable);

			// Call both implementations
			auto moo_result = sut(&moo_pGameDataTable, nUnused, nGameGUID, &pHashKey);
			auto original_result = original(&original_pGameDataTable, nUnused, nGameGUID, &pHashKey);
			
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
			// Input data
			STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) moo_pNode{};
			D2GameStrc moo_ptr{};
			STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) original_pNode{};
			D2GameStrc original_ptr{};
			int32_t nUnused{};

			const auto setup_data = [](
				STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot)& pNode,
				D2GameStrc& ptr
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pNode, moo_ptr);
			setup_data(original_pNode, original_ptr);

			// Call both implementations
			auto moo_result = sut(&moo_pNode, nUnused, &moo_ptr);
			auto original_result = original(&original_pNode, nUnused, &original_ptr);
			
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
			// Input data
			STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) moo_pList{};
			STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) original_pList{};

			const auto setup_data = [](
				STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot)& pList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList);
			setup_data(original_pList);

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
			// Input data
			TSLink<D2GameStrc> moo_pLink{};
			TSLink<D2GameStrc> original_pLink{};

			const auto setup_data = [](
				TSLink<D2GameStrc>& pLink
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pLink);
			setup_data(original_pLink);

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
			// Input data
			TSGrowableArray<STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot)> moo_pArray{};
			TSGrowableArray<STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot)> original_pArray{};
			int32_t nUnused{};
			uint32_t nCount{};

			const auto setup_data = [](
				TSGrowableArray<STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot)>& pArray
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pArray);
			setup_data(original_pArray);

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
			// Input data
			STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) moo_pNode{};
			STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) original_pNode{};
			int32_t nUnused{};
			char bShouldFree{};

			const auto setup_data = [](
				STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot)& pNode
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pNode);
			setup_data(original_pNode);

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
			// Input data
			STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) moo_pList{};
			STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot) original_pList{};

			const auto setup_data = [](
				STORM_EXPLICIT_LIST(D2GameStrc, m_linktoslot)& pList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList);
			setup_data(original_pList);

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
			// Input data
			TSExplicitList<D2GameStrc, 0xDDDDDDDD> moo_pList{};
			TSExplicitList<D2GameStrc, 0xDDDDDDDD> original_pList{};
			void* moo_pMemory = nullptr;
			void* original_pMemory = nullptr;
			int32_t nUnused{};

			const auto setup_data = [](
				TSExplicitList<D2GameStrc, 0xDDDDDDDD>& pList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pList);
			setup_data(original_pList);

			// Call both implementations
			sut(moo_pMemory, nUnused, &moo_pList);
			original(original_pMemory, nUnused, &original_pList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemory, original_pMemory, "Comparing pMemory");
			SKIP_MOO_CHECK_EQ(moo_pList, original_pList, "Comparing pList");
		}
	}
}
