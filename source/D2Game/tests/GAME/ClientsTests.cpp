#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <Units/Units.h>


TEST_SUITE("ClientsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_Initialize, dll_base + 0x00001CD0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31D50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_Release, dll_base + 0x00001D50);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31D80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetExpansionClientCount, dll_base + 0x00001D80);
		
		SUBCASE("")
		{
			// Call both implementations
			auto moo_result = sut();
			auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31DE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetClientFromClientId, dll_base + 0x00001DE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nClientId{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, nClientId);
			auto original_result = original(&original_pGame, nClientId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetPlayerFromClient, dll_base + 0x00001E20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			BOOL bIgnoreDeath{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient, bIgnoreDeath);
			auto original_result = original(&original_pClient, bIgnoreDeath);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31EA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetPlayerInClient, dll_base + 0x00001EA0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC31EF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC31EF0, dll_base + 0x00001EF0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoomArg{};
			D2ClientStrc original_pClient{};
			D2UnitStrc original_pPlayer{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoomArg{};
			int32_t nXArg{};
			int32_t nYArg{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2UnitStrc& pPlayer,
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoomArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPlayer, moo_pGame, moo_pRoomArg);
			setup_data(original_pClient, original_pPlayer, original_pGame, original_pRoomArg);

			// Call both implementations
			sut(&moo_pClient, &moo_pPlayer, &moo_pGame, &moo_pRoomArg, nXArg, nYArg);
			original(&original_pClient, &original_pPlayer, &original_pGame, &original_pRoomArg, nXArg, nYArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoomArg, original_pRoomArg, "Comparing pRoomArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC32220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC32220, dll_base + 0x00002220);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC32260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_AddPlayerToGame, dll_base + 0x00002260);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoomArg{};
			D2ClientStrc original_pClient{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoomArg{};
			int32_t a3{};
			int32_t nXArg{};
			int32_t nYArg{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoomArg
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pGame, moo_pRoomArg);
			setup_data(original_pClient, original_pGame, original_pRoomArg);

			// Call both implementations
			auto moo_result = sut(&moo_pClient, &moo_pGame, a3, &moo_pRoomArg, nXArg, nYArg);
			auto original_result = original(&original_pClient, &original_pGame, a3, &original_pRoomArg, nXArg, nYArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoomArg, original_pRoomArg, "Comparing pRoomArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC325E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_AddToGame, dll_base + 0x000025E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nClientId{};
			uint8_t nClassIdOrCharTemplate{};
			char szClientName{};
			char szAccount{};
			int32_t nCharSaveTransactionToken{};
			uint32_t nLocale{};
			int32_t a8{};
			int32_t a9{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, nClientId, nClassIdOrCharTemplate, &szClientName, &szAccount, nCharSaveTransactionToken, nLocale, a8, a9);
			auto original_result = original(&original_pGame, nClientId, nClassIdOrCharTemplate, &szClientName, &szAccount, nCharSaveTransactionToken, nLocale, a8, a9);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC327E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetGameData, dll_base + 0x000027E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC32810" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_FillCharacterPreviewInfo, dll_base + 0x00002810);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2CharacterPreviewInfoStrc moo_pCharacterPreviewInfo{};
			D2ClientStrc original_pClient{};
			D2CharacterPreviewInfoStrc original_pCharacterPreviewInfo{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2CharacterPreviewInfoStrc& pCharacterPreviewInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pCharacterPreviewInfo);
			setup_data(original_pClient, original_pCharacterPreviewInfo);

			// Call both implementations
			sut(&moo_pClient, &moo_pCharacterPreviewInfo);
			original(&original_pClient, &original_pCharacterPreviewInfo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pCharacterPreviewInfo, original_pCharacterPreviewInfo, "Comparing pCharacterPreviewInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC32A30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_RemoveClientFromGame, dll_base + 0x00002A30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nClientIdToRemove{};
			BOOL bTriggerSave{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame, nClientIdToRemove, bTriggerSave);
			original(&original_pGame, nClientIdToRemove, bTriggerSave);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC32FE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_FreeClientsFromGame, dll_base + 0x00002FE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC33020, dll_base + 0x00003020);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ActiveRoomStrc moo_pRoom{};
			D2ClientStrc original_pClient{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pRoom);
			setup_data(original_pClient, original_pRoom);

			// Call both implementations
			sut(&moo_pClient, &moo_pRoom);
			original(&original_pClient, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33210" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_RefreshUnitsUpdateList, dll_base + 0x00003210);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint32_t nUpdateSize{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUpdateSize);
			original(&original_pClient, nUpdateSize);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33510" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetUnitX, dll_base + 0x00003510);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33540" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetUnitY, dll_base + 0x00003540);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetUnitsUpdateList, dll_base + 0x00003570);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientUnitUpdateSortStrc moo_pSort{};
			D2ClientStrc original_pClient{};
			D2ClientUnitUpdateSortStrc original_pSort{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2ClientUnitUpdateSortStrc& pSort
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pSort);
			setup_data(original_pClient, original_pSort);

			// Call both implementations
			sut(&moo_pClient, &moo_pSort);
			original(&original_pClient, &original_pSort);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pSort, original_pSort, "Comparing pSort");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC33670, dll_base + 0x00003670);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC337B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_IsInGame, dll_base + 0x000037B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nClientId{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, nClientId);
			auto original_result = original(&original_pGame, nClientId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC337E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetRoomInClient, dll_base + 0x000037E0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ActiveRoomStrc moo_pRoom{};
			D2ClientStrc original_pClient{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pRoom);
			setup_data(original_pClient, original_pRoom);

			// Call both implementations
			sut(&moo_pClient, &moo_pRoom);
			original(&original_pClient, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetClientDead_6FC33830, dll_base + 0x00003830);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			void* moo_pAlwaysNull = nullptr;
			void* original_pAlwaysNull = nullptr;

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, moo_pAlwaysNull);
			original(&original_pClient, original_pAlwaysNull);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pAlwaysNull, original_pAlwaysNull, "Comparing pAlwaysNull");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetActNo, dll_base + 0x00003890);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC338C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetActNo, dll_base + 0x000038C0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nAct{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nAct);
			original(&original_pClient, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC33910, dll_base + 0x00003910);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetSaveChecksumFromClient_6FC33940, dll_base + 0x00003940);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33970" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetSaveFileChecksum_6FC33970, dll_base + 0x00003970);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint32_t a2{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, a2);
			original(&original_pClient, a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC339A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetClientId, dll_base + 0x000039A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC339E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetClassId, dll_base + 0x000039E0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetClassId, dll_base + 0x00003A10);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nClass{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nClass);
			original(&original_pClient, nClass);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33A20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetFlags, dll_base + 0x00003A20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nFlags);
			original(&original_pClient, nFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33A30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetFlags, dll_base + 0x00003A30);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33A40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_ToggleFlag, dll_base + 0x00003A40);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint16_t nFlag{};
			int32_t bSet{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nFlag, bSet);
			original(&original_pClient, nFlag, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33A60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_CheckFlag, dll_base + 0x00003A60);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint16_t nFlag{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient, nFlag);
			auto original_result = original(&original_pClient, nFlag);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33A70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_UpdateCharacterProgression, dll_base + 0x00003A70);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint16_t nAct{};
			uint16_t nDifficulty{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nAct, nDifficulty);
			original(&original_pClient, nAct, nDifficulty);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33AC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetClientState, dll_base + 0x00003AC0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			D2ClientState nClientState{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nClientState);
			original(&original_pClient, nClientState);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33AF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetIronGolemItemGUID, dll_base + 0x00003AF0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nIronGolemItemGUID{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nIronGolemItemGUID);
			original(&original_pClient, nIronGolemItemGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetCreateTime, dll_base + 0x00003B20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			DWORD dwCreateTime{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, dwCreateTime);
			original(&original_pClient, dwCreateTime);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33B50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetCreateTime, dll_base + 0x00003B50);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33B80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetGame, dll_base + 0x00003B80);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33BB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_IsInUnitsRoom, dll_base + 0x00003BB0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ClientStrc moo_pClient{};
			D2UnitStrc original_pUnit{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pClient);
			setup_data(original_pUnit, original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, &moo_pClient);
			auto original_result = original(&original_pUnit, &original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33BE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetName, dll_base + 0x00003BE0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC33C10, dll_base + 0x00003C10);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33C50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_CheckState, dll_base + 0x00003C50);
		
		SUBCASE("")
		{
			int32_t nClientId{};
			D2ClientState nExpectedClientState{};

			// Call both implementations
			auto moo_result = sut(nClientId, nExpectedClientState);
			auto original_result = original(nClientId, nExpectedClientState);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_UpdatePing, dll_base + 0x00003CD0);
		
		SUBCASE("")
		{
			int32_t nClientId{};
			int32_t a2{};
			int32_t arg_0{};

			// Call both implementations
			sut(nClientId, a2, arg_0);
			original(nClientId, a2, arg_0);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33EA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC33EA0, dll_base + 0x00003EA0);
		
		SUBCASE("")
		{
			// Input data
			char moo_szName{};
			char original_szName{};
			int32_t nClientId{};

			const auto setup_data = [](
				char& szName
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szName);
			setup_data(original_szName);

			// Call both implementations
			auto moo_result = sut(nClientId, &moo_szName);
			auto original_result = original(nClientId, &original_szName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33F20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetClientIdByName, dll_base + 0x00003F20);
		
		SUBCASE("")
		{
			char szName{};

			// Call both implementations
			auto moo_result = sut(&szName);
			auto original_result = original(&szName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC33F90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC33F90, dll_base + 0x00003F90);
		
		SUBCASE("")
		{
			// Input data
			char moo_szGameName{};
			char original_szGameName{};
			char szName{};

			const auto setup_data = [](
				char& szGameName
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_szGameName);
			setup_data(original_szGameName);

			// Call both implementations
			auto moo_result = sut(&szName, &moo_szGameName);
			auto original_result = original(&szName, &original_szGameName);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_szGameName, original_szGameName, "Comparing szGameName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_AttachSaveFile, dll_base + 0x00004020);
		
		SUBCASE("")
		{
			int32_t nClientId{};
			void* moo_pSaveData = nullptr;
			void* original_pSaveData = nullptr;
			int32_t nSize{};
			int32_t nTotalSize{};
			BOOL bUnlockCharacter{};
			int32_t a6{};
			int32_t a7{};

			// Call both implementations
			auto moo_result = sut(nClientId, moo_pSaveData, nSize, nTotalSize, bUnlockCharacter, a6, a7);
			auto original_result = original(nClientId, original_pSaveData, nSize, nTotalSize, bUnlockCharacter, a6, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSaveData, original_pSaveData, "Comparing pSaveData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34170" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetSaveHeader, dll_base + 0x00004170);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC341A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetSaveHeaderSize, dll_base + 0x000041A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC341D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_CopySaveDataToClient, dll_base + 0x000041D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			void* moo_pData = nullptr;
			void* original_pData = nullptr;
			uint32_t nSize{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, moo_pData, nSize);
			original(&original_pClient, original_pData, nSize);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pData, original_pData, "Comparing pData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_FreeSaveHeader, dll_base + 0x00004280);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetSaveLoadComplete_6FC34300, dll_base + 0x00004300);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34350" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_GetSaveHeader_6FC34350, dll_base + 0x00004350);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34390" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_SetSaveLoaded_6FC34390, dll_base + 0x00004390);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient);
			original(&original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC343D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENT_IsSaveLoaded, dll_base + 0x000043D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34420" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetNext, dll_base + 0x00004420);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetSkillHotKey, dll_base + 0x00004430);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nHotkeyId{};
			int16_t nSkillId{};
			uint8_t nHand{};
			int32_t nItemGUID{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nHotkeyId, nSkillId, nHand, nItemGUID);
			original(&original_pClient, nHotkeyId, nSkillId, nHand, nItemGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetSkillHotKey, dll_base + 0x00004460);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			int32_t moo_pSkillId{};
			int32_t moo_nHand{};
			int32_t moo_nItemGUID{};
			D2ClientStrc original_pClient{};
			int32_t original_pSkillId{};
			int32_t original_nHand{};
			int32_t original_nItemGUID{};
			int32_t nId{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				int32_t& pSkillId,
				int32_t& nHand,
				int32_t& nItemGUID
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pSkillId, moo_nHand, moo_nItemGUID);
			setup_data(original_pClient, original_pSkillId, original_nHand, original_nItemGUID);

			// Call both implementations
			sut(&moo_pClient, nId, &moo_pSkillId, &moo_nHand, &moo_nItemGUID);
			original(&original_pClient, nId, &original_pSkillId, &original_nHand, &original_nItemGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pSkillId, original_pSkillId, "Comparing pSkillId");
			SKIP_MOO_CHECK_EQ(moo_nHand, original_nHand, "Comparing nHand");
			SKIP_MOO_CHECK_EQ(moo_nItemGUID, original_nItemGUID, "Comparing nItemGUID");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC344A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetGuildFlags, dll_base + 0x000044A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC344B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetGuildFlags, dll_base + 0x000044B0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int16_t nFlags{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nFlags);
			original(&original_pClient, nFlags);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC344C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetGuildTag, dll_base + 0x000044C0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			int32_t moo_pTag{};
			D2ClientStrc original_pClient{};
			int32_t original_pTag{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				int32_t& pTag
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pTag);
			setup_data(original_pClient, original_pTag);

			// Call both implementations
			sut(&moo_pClient, &moo_pTag);
			original(&original_pClient, &original_pTag);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pTag, original_pTag, "Comparing pTag");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC344D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetGuildTag, dll_base + 0x000044D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			int32_t moo_a2{};
			D2ClientStrc original_pClient{};
			int32_t original_a2{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				int32_t& a2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_a2);
			setup_data(original_pClient, original_a2);

			// Call both implementations
			sut(&moo_pClient, &moo_a2);
			original(&original_pClient, &original_a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC344E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetGuildName, dll_base + 0x000044E0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			char moo_szName{};
			D2ClientStrc original_pClient{};
			char original_szName{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				char& szName
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_szName);
			setup_data(original_pClient, original_szName);

			// Call both implementations
			sut(&moo_pClient, &moo_szName);
			original(&original_pClient, &original_szName);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34500" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetGuildName, dll_base + 0x00004500);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			char moo_szName{};
			D2ClientStrc original_pClient{};
			char original_szName{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				char& szName
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_szName);
			setup_data(original_pClient, original_szName);

			// Call both implementations
			sut(&moo_pClient, &moo_szName);
			original(&original_pClient, &original_szName);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetGuildEmblem, dll_base + 0x00004520);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			uint8_t moo_pBackgroundColor{};
			uint8_t moo_pForegroundColor{};
			uint8_t moo_pEmblemType{};
			D2ClientStrc original_pClient{};
			uint8_t original_pBackgroundColor{};
			uint8_t original_pForegroundColor{};
			uint8_t original_pEmblemType{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				uint8_t& pBackgroundColor,
				uint8_t& pForegroundColor,
				uint8_t& pEmblemType
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pBackgroundColor, moo_pForegroundColor, moo_pEmblemType);
			setup_data(original_pClient, original_pBackgroundColor, original_pForegroundColor, original_pEmblemType);

			// Call both implementations
			sut(&moo_pClient, &moo_pBackgroundColor, &moo_pForegroundColor, &moo_pEmblemType);
			original(&original_pClient, &original_pBackgroundColor, &original_pForegroundColor, &original_pEmblemType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pBackgroundColor, original_pBackgroundColor, "Comparing pBackgroundColor");
			SKIP_MOO_CHECK_EQ(moo_pForegroundColor, original_pForegroundColor, "Comparing pForegroundColor");
			SKIP_MOO_CHECK_EQ(moo_pEmblemType, original_pEmblemType, "Comparing pEmblemType");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetGuildEmblem, dll_base + 0x00004550);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t nBackgroundColor{};
			uint8_t nForegroundColor{};
			uint8_t nEmblemType{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nBackgroundColor, nForegroundColor, nEmblemType);
			original(&original_pClient, nBackgroundColor, nForegroundColor, nEmblemType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetExperienceLoss, dll_base + 0x00004570);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nExpLoss{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nExpLoss);
			original(&original_pClient, nExpLoss);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC345A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetExperienceLoss, dll_base + 0x000045A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC345B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetWeaponSwitch, dll_base + 0x000045B0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC345C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_SetWeaponSwitch, dll_base + 0x000045C0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			uint8_t bSwitchWeapon{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, bSwitchWeapon);
			original(&original_pClient, bSwitchWeapon);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC345D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_PacketDataList_Append, dll_base + 0x000045D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2PacketDataStrc moo_pPacketData{};
			D2ClientStrc original_pClient{};
			D2PacketDataStrc original_pPacketData{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2PacketDataStrc& pPacketData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pPacketData);
			setup_data(original_pClient, original_pPacketData);

			// Call both implementations
			sut(&moo_pClient, &moo_pPacketData);
			original(&original_pClient, &original_pPacketData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pPacketData, original_pPacketData, "Comparing pPacketData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_PacketDataList_Reset, dll_base + 0x00004600);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2PacketDataStrc moo_pSinglePacketData{};
			D2ClientStrc original_pClient{};
			D2PacketDataStrc original_pSinglePacketData{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2PacketDataStrc& pSinglePacketData
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pSinglePacketData);
			setup_data(original_pClient, original_pSinglePacketData);

			// Call both implementations
			sut(&moo_pClient, &moo_pSinglePacketData);
			original(&original_pClient, &original_pSinglePacketData);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pSinglePacketData, original_pSinglePacketData, "Comparing pSinglePacketData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_PacketDataList_PopHead, dll_base + 0x00004630);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_PacketDataList_GetTail, dll_base + 0x00004670);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34680" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_PacketDataList_GetHead, dll_base + 0x00004680);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_CopyAccountNameToBuffer, dll_base + 0x00004690);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			char moo_szAccount{};
			D2ClientStrc original_pClient{};
			char original_szAccount{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				char& szAccount
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_szAccount);
			setup_data(original_pClient, original_szAccount);

			// Call both implementations
			sut(&moo_pClient, &moo_szAccount);
			original(&original_pClient, &original_szAccount);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_szAccount, original_szAccount, "Comparing szAccount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC346A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetCharSaveTransactionToken_6FC346A0, dll_base + 0x000046A0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			int32_t moo_pCharSaveTransactionToken{};
			D2ClientStrc original_pClient{};
			int32_t original_pCharSaveTransactionToken{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				int32_t& pCharSaveTransactionToken
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pCharSaveTransactionToken);
			setup_data(original_pClient, original_pCharSaveTransactionToken);

			// Call both implementations
			sut(&moo_pClient, &moo_pCharSaveTransactionToken);
			original(&original_pClient, &original_pCharSaveTransactionToken);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pCharSaveTransactionToken, original_pCharSaveTransactionToken, "Comparing pCharSaveTransactionToken");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC346B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetRealmIdFromClient_6FC346B0, dll_base + 0x000046B0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientInfoStrc* moo_ppClientInfo{};
			D2ClientStrc original_pClient{};
			D2ClientInfoStrc* original_ppClientInfo{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2ClientInfoStrc*& ppClientInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_ppClientInfo);
			setup_data(original_pClient, original_ppClientInfo);

			// Call both implementations
			sut(&moo_pClient, &moo_ppClientInfo);
			original(&original_pClient, &original_ppClientInfo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_ppClientInfo, original_ppClientInfo, "Comparing ppClientInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC346C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SetClientsRealmId_6FC346C0, dll_base + 0x000046C0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientInfoStrc moo_pClientInfo{};
			D2ClientStrc original_pClient{};
			D2ClientInfoStrc original_pClientInfo{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2ClientInfoStrc& pClientInfo
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pClientInfo);
			setup_data(original_pClient, original_pClientInfo);

			// Call both implementations
			sut(&moo_pClient, &moo_pClientInfo);
			original(&original_pClient, &original_pClientInfo);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pClientInfo, original_pClientInfo, "Comparing pClientInfo");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC346D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_GetClientPlayerData, dll_base + 0x000046D0);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pClient);
			auto original_result = original(&original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34700" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_NotifyWarpAttempt, dll_base + 0x00004700);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC347A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CLIENTS_ShouldDelayWarpAttempt, dll_base + 0x000047A0);
		
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
}
