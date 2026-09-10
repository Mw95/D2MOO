#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <MONSTER/MonsterMsg.h>
#include <Units/Units.h>


TEST_SUITE("MonsterMsgTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC659E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC659E0, dll_base + 0x000359E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pUnit, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pClient] = setup_data();
			auto [original_pGame, original_pUnit, original_pClient] = setup_data();
			int32_t a4{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient, a4);
			original(&original_pGame, &original_pUnit, &original_pClient, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC65C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC65C70, dll_base + 0x00035C70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pMonster, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster, moo_pClient] = setup_data();
			auto [original_pGame, original_pMonster, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster, &moo_pClient);
			original(&original_pGame, &original_pMonster, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
}
