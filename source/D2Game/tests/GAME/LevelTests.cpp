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
#include <GAME/Level.h>
#include <Units/Units.h>


TEST_SUITE("LevelTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BBA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_UpdateUnitsInAdjacentRooms, dll_base + 0x0000BBA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pRoom, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pClient] = setup_data();
			auto [original_pGame, original_pRoom, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pClient);
			original(&original_pGame, &original_pRoom, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BD10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_RemoveUnitsExceptClientPlayer, dll_base + 0x0000BD10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pRoom, pClient };
			};
			
			// Input data
			auto [moo_pRoom, moo_pClient] = setup_data();
			auto [original_pRoom, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pClient);
			original(&original_pRoom, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BDE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_FreeDrlgDeletes, dll_base + 0x0000BDE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BE40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_AddClient, dll_base + 0x0000BE40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pRoom, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pClient] = setup_data();
			auto [original_pGame, original_pRoom, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pClient);
			original(&original_pGame, &original_pRoom, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BF00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_RemoveClient, dll_base + 0x0000BF00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pRoom, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pClient] = setup_data();
			auto [original_pGame, original_pRoom, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pClient);
			original(&original_pGame, &original_pRoom, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3BFB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_RemoveClientFromAdjacentRooms, dll_base + 0x0000BFB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pRoom, pClient };
			};
			
			// Input data
			auto [moo_pRoom, moo_pClient] = setup_data();
			auto [original_pRoom, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pRoom, &moo_pClient);
			original(&original_pRoom, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C010" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_SynchronizeDayNightCycleWithClient, dll_base + 0x0000C010);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C0B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_ChangeAct, dll_base + 0x0000C0B0);
		
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
			int32_t nDestinationLevelId{};
			int32_t nTileCalc{};

			// Call both implementations
			sut(&moo_pGame, &moo_pClient, nDestinationLevelId, nTileCalc);
			original(&original_pGame, &original_pClient, nDestinationLevelId, nTileCalc);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_WarpUnit, dll_base + 0x0000C410);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pGame, pPlayer };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer] = setup_data();
			auto [original_pGame, original_pPlayer] = setup_data();
			int32_t nDestinationLevelId{};
			int32_t nTileCalc{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nDestinationLevelId, nTileCalc);
			original(&original_pGame, &original_pPlayer, nDestinationLevelId, nTileCalc);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C510" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_LoadAct, dll_base + 0x0000C510);
		
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
			uint8_t nAct{};

			// Call both implementations
			sut(&moo_pGame, nAct);
			original(&original_pGame, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_RemoveAllUnits, dll_base + 0x0000C580);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC3C5B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(LEVEL_UpdateQueuedUnitsInAllActs, dll_base + 0x0000C5B0);
		
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
}
