#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <INVENTORY/InvMode.h>
#include <Units/Units.h>


TEST_SUITE("InvModeTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC40FB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_INVMODE_First_6FC40FB0, dll_base + 0x00010FB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2ClientStrc moo_pClient{};
			D2InventoryStrc moo_pInventory{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2ClientStrc original_pClient{};
			D2InventoryStrc original_pInventory{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2ClientStrc& pClient,
				D2InventoryStrc& pInventory
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pClient, moo_pInventory);
			setup_data(original_pGame, original_pUnit, original_pClient, original_pInventory);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pClient, &moo_pInventory);
			original(&original_pGame, &original_pUnit, &original_pClient, &original_pInventory);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC410E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC410E0, dll_base + 0x000110E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pUnused{};
			D2ClientStrc moo_pClient{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pUnused{};
			D2ClientStrc original_pClient{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem,
				D2UnitStrc& pUnused,
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pItem, moo_pUnused, moo_pClient);
			setup_data(original_pPlayer, original_pItem, original_pUnused, original_pClient);

			// Call both implementations
			auto moo_result = sut(&moo_pPlayer, &moo_pItem, &moo_pUnused, &moo_pClient);
			auto original_result = original(&original_pPlayer, &original_pItem, &original_pUnused, &original_pClient);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC415F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ResetSomeItemFlags_6FC415F0, dll_base + 0x000115F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem);
			setup_data(original_pGame, original_pItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pItem);
			original(&original_pGame, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC41660" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC41660, dll_base + 0x00011660);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC416D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_INVMODE_Last_6FC416D0, dll_base + 0x000116D0);
		
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
}
