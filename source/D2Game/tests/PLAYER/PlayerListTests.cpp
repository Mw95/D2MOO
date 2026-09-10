#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <PLAYER/PlayerList.h>
#include <Units/Units.h>


TEST_SUITE("PlayerListTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBA690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_FreePlayerLists, dll_base + 0x0008A690);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer);
			original(&original_pGame, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBA6E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_IterateCallback_FreePlayerList, dll_base + 0x0008A6E0);
		
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
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, moo_pArg);
			original(&original_pGame, &original_pPlayer, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBA750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_AllocPlayerList, dll_base + 0x0008A750);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pGame, pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pGame, original_pPlayer1, original_pPlayer2] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBA840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_ToggleFlag, dll_base + 0x0008A840);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pGame, pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pGame, original_pPlayer1, original_pPlayer2] = setup_data();
			uint32_t nFlags{};
			int32_t bSet{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2, nFlags, bSet);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2, nFlags, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBA8E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_CheckFlag, dll_base + 0x0008A8E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pPlayer1, original_pPlayer2] = setup_data();
			uint32_t nFlags{};

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer1, &moo_pPlayer2, nFlags);
			const auto original_result = original(&original_pPlayer1, &original_pPlayer2, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBA930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_GetFlags, dll_base + 0x0008A930);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pPlayer1, original_pPlayer2] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer1, &moo_pPlayer2);
			const auto original_result = original(&original_pPlayer1, &original_pPlayer2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBA980" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBA980, dll_base + 0x0008A980);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pPlayer1, original_pPlayer2] = setup_data();
			int32_t a3{};

			// Call both implementations
			sut(&moo_pPlayer1, &moo_pPlayer2, a3);
			original(&original_pPlayer1, &original_pPlayer2, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBA9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBA9D0, dll_base + 0x0008A9D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pPlayer1, original_pPlayer2] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer1, &moo_pPlayer2);
			const auto original_result = original(&original_pPlayer1, &original_pPlayer2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAA20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBAA20, dll_base + 0x0008AA20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pPlayer1, original_pPlayer2] = setup_data();

			// Call both implementations
			sut(&moo_pPlayer1, &moo_pPlayer2);
			original(&original_pPlayer1, &original_pPlayer2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAAA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBAAA0, dll_base + 0x0008AAA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pGame, pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pGame, original_pPlayer1, original_pPlayer2] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer1, &moo_pPlayer2);
			original(&original_pGame, &original_pPlayer1, &original_pPlayer2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAB20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBAB20, dll_base + 0x0008AB20);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer);
			original(&original_pGame, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAB50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBAB50, dll_base + 0x0008AB50);
		
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
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, moo_pArg);
			original(&original_pGame, &original_pPlayer, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAD60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_sub_6FCBAD60, dll_base + 0x0008AD60);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer);
			original(&original_pGame, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAE20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_GetHostileDelay, dll_base + 0x0008AE20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pPlayer1, original_pPlayer2] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer1, &moo_pPlayer2);
			const auto original_result = original(&original_pPlayer1, &original_pPlayer2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAE70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLAYERLIST_SetHostileDelay, dll_base + 0x0008AE70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer1{};
				D2UnitStrc pPlayer2{};
				
				return std::tuple{ pPlayer1, pPlayer2 };
			};
			
			// Input data
			auto [moo_pPlayer1, moo_pPlayer2] = setup_data();
			auto [original_pPlayer1, original_pPlayer2] = setup_data();
			int32_t a3{};

			// Call both implementations
			sut(&moo_pPlayer1, &moo_pPlayer2, a3);
			original(&original_pPlayer1, &original_pPlayer2, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer1, original_pPlayer1, "Comparing pPlayer1");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCBAED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCBAED0, dll_base + 0x0008AED0);
		
		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}
}
