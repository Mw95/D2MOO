#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <MISSILES/Missiles.h>
#include <Units/Units.h>


TEST_SUITE("MissilesTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC552A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILES_RemoveAll, dll_base + 0x000252A0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC552F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILES_Initialize, dll_base + 0x000252F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMissile{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMissile{};
			int32_t nUnitGUID{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMissile);
			setup_data(original_pGame, original_pMissile);

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, nUnitGUID);
			original(&original_pGame, &original_pMissile, nUnitGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILES_Free, dll_base + 0x00025340);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMissile{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMissile{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMissile);
			setup_data(original_pGame, original_pMissile);

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile);
			original(&original_pGame, &original_pMissile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILES_CreateMissileFromParams, dll_base + 0x00025360);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2MissileStrc moo_missileParams{};
			D2GameStrc original_pGame{};
			D2MissileStrc original_missileParams{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2MissileStrc& missileParams
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_missileParams);
			setup_data(original_pGame, original_missileParams);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_missileParams);
			auto original_result = original(&original_pGame, &original_missileParams);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_missileParams, original_missileParams, "Comparing missileParams");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55B70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSILES_SyncToClient, dll_base + 0x00025B70);
		
		SUBCASE("")
		{
			// Input data
			D2ClientStrc moo_pClient{};
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMissile{};
			D2ClientStrc original_pClient{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMissile{};
			int32_t nVelocity{};

			const auto setup_data = [](
				D2ClientStrc& pClient,
				D2GameStrc& pGame,
				D2UnitStrc& pMissile
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pClient, moo_pGame, moo_pMissile);
			setup_data(original_pClient, original_pGame, original_pMissile);

			// Call both implementations
			sut(&moo_pClient, &moo_pGame, &moo_pMissile, nVelocity);
			original(&original_pClient, &original_pGame, &original_pMissile, nVelocity);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
}
