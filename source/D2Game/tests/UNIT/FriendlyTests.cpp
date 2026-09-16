#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <UNIT/Friendly.h>
#include <Units/Units.h>


TEST_SUITE("FriendlyTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB9A50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FRIENDLY_RemoveHostility, dll_base + 0x00089A50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pPlayer2{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pPlayer2{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pPlayer2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pPlayer2);
			setup_data(original_pGame, original_pPlayer, original_pPlayer2);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pPlayer2);
			auto original_result = original(&original_pGame, &original_pPlayer, &original_pPlayer2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCB9AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(FRIENDLY_OpenHostility, dll_base + 0x00089AB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pPlayer2{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pPlayer2{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pPlayer2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pPlayer2);
			setup_data(original_pGame, original_pPlayer, original_pPlayer2);

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pPlayer2);
			original(&original_pGame, &original_pPlayer, &original_pPlayer2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pPlayer2, original_pPlayer2, "Comparing pPlayer2");
		}
	}
}
