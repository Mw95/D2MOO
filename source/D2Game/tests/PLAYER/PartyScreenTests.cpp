#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <PLAYER/PartyScreen.h>
#include <Units/Units.h>


TEST_SUITE("PartyScreenTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7AB50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_ToggleLootability, dll_base + 0x0004AB50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			int32_t moo_pFailure{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			int32_t original_pFailure{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				int32_t& pFailure
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pFailure);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pFailure);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nParam, &moo_pFailure);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nParam, &original_pFailure);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pFailure, original_pFailure, "Comparing pFailure");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7AC20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_SendEventUpdateToClient, dll_base + 0x0004AC20);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2ClientStrc original_pClient{};
			int32_t nUnitGUID{};
			uint8_t nType{};

			const auto setup_data = [](
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient);
			setup_data(original_pClient);

			// Call both implementations
			sut(&moo_pClient, nUnitGUID, nType);
			original(&original_pClient, nUnitGUID, nType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7AD10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_ToggleIgnore, dll_base + 0x0004AD10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			int32_t moo_pFailure{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			int32_t original_pFailure{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				int32_t& pFailure
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pFailure);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pFailure);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nParam, &moo_pFailure);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nParam, &original_pFailure);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pFailure, original_pFailure, "Comparing pFailure");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7AD70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_ToggleSquelch, dll_base + 0x0004AD70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			int32_t moo_pFailure{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			int32_t original_pFailure{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				int32_t& pFailure
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pFailure);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pFailure);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nParam, &moo_pFailure);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nParam, &original_pFailure);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pFailure, original_pFailure, "Comparing pFailure");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7ADD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PARTYSCREEN_Command8_6FC7ADD0, dll_base + 0x0004ADD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			int32_t moo_pFailure{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			int32_t original_pFailure{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				int32_t& pFailure
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pFailure);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pFailure);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nParam, &moo_pFailure);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nParam, &original_pFailure);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pFailure, original_pFailure, "Comparing pFailure");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7AED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7AED0, dll_base + 0x0004AED0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pLocalPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pLocalPlayer{};
			void* moo_a3 = nullptr;
			void* original_a3 = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pLocalPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pLocalPlayer);
			setup_data(original_pGame, original_pLocalPlayer);

			// Call both implementations
			sut(&moo_pGame, &moo_pLocalPlayer, moo_a3);
			original(&original_pGame, &original_pLocalPlayer, original_a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pLocalPlayer, original_pLocalPlayer, "Comparing pLocalPlayer");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_InvitationCancelled, dll_base + 0x0004B030);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			int32_t moo_pFailure{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			int32_t original_pFailure{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				int32_t& pFailure
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pFailure);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pFailure);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nParam, &moo_pFailure);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nParam, &original_pFailure);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pFailure, original_pFailure, "Comparing pFailure");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B0E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_ReceivedInvitation, dll_base + 0x0004B0E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			int32_t moo_pFailure{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			int32_t original_pFailure{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				int32_t& pFailure
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pFailure);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pFailure);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nParam, &moo_pFailure);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nParam, &original_pFailure);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pFailure, original_pFailure, "Comparing pFailure");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_PlayerLeftParty, dll_base + 0x0004B160);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			int32_t moo_pFailure{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			int32_t original_pFailure{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				int32_t& pFailure
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pFailure);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pFailure);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nParam, &moo_pFailure);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nParam, &original_pFailure);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pFailure, original_pFailure, "Comparing pFailure");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_PartyIterate_PlayerLeftParty, dll_base + 0x0004B190);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1);
			setup_data(original_pGame, original_pPlayer1);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, moo_pArg);
			original(&original_pGame, &original_pPlayer1, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B1D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_ToggleHostile, dll_base + 0x0004B1D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2UnitStrc moo_pPlayer2{};
			int32_t moo_pFailure{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			D2UnitStrc original_pPlayer2{};
			int32_t original_pFailure{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1,
				D2UnitStrc& pPlayer2,
				int32_t& pFailure
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1, moo_pPlayer2, moo_pFailure);
			setup_data(original_pGame, original_pPlayer1, original_pPlayer2, original_pFailure);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nParam, &moo_pFailure);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nParam, &original_pFailure);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
			SKIP_MOO_CHECK_EQ(moo_pFailure, original_pFailure, "Comparing pFailure");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B3F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7B3F0, dll_base + 0x0004B3F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1);
			setup_data(original_pGame, original_pPlayer1);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, moo_pArg);
			original(&original_pGame, &original_pPlayer1, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7B450, dll_base + 0x0004B450);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7B460, dll_base + 0x0004B460);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer1{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer1{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer1
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer1);
			setup_data(original_pGame, original_pPlayer1);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, moo_pArg);
			original(&original_pGame, &original_pPlayer1, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7B4C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PARTYSCREEN_CommandHandler, dll_base + 0x0004B4C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nCallbackId{};
			int32_t nOtherPlayerGUID{};
			int32_t nParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, nCallbackId, nOtherPlayerGUID, nParam);
			auto original_result = original(&original_pGame, &original_pUnit, nCallbackId, nOtherPlayerGUID, nParam);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
