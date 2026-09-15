#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <ITEMS/Items.h>
#include <Units/Units.h>


TEST_SUITE("ItemsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4D470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetUniqueItemsTxtRecord, dll_base + 0x0001D470);
		
		SUBCASE("")
		{
			int32_t nUniqueItemId{};

			// Call both implementations
			const auto moo_result = sut(nUniqueItemId);
			const auto original_result = original(nUniqueItemId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4D4A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_HasUniqueBeenDroppedAlready, dll_base + 0x0001D4A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nUniqueItemId{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nUniqueItemId);
			const auto original_result = original(&original_pGame, nUniqueItemId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4D4E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CanUniqueItemBeDropped, dll_base + 0x0001D4E0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4D5E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4D5E0, dll_base + 0x0001D5E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc* moo_ppItem{};
			D2ItemDropStrc moo_pItemDrop{};
			D2UnitStrc* original_ppItem{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2UnitStrc*& ppItem,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppItem, moo_pItemDrop);
			setup_data(original_ppItem, original_pItemDrop);

			// Call both implementations
			const auto moo_result = sut(&moo_ppItem, &moo_pItemDrop);
			const auto original_result = original(&original_ppItem, &original_pItemDrop);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4D6B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4D6B0, dll_base + 0x0001D6B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pItemDrop);
			setup_data(original_pGame, original_pItem, original_pItemDrop);

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pItemDrop);
			original(&original_pGame, &original_pItem, &original_pItemDrop);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4D800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_MakeEthereal, dll_base + 0x0001D800);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDropStrc moo_pItemDrop{};
			D2UnitStrc original_pItem{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pItemDrop);
			setup_data(original_pItem, original_pItemDrop);

			// Call both implementations
			sut(&moo_pItem, &moo_pItemDrop);
			original(&original_pItem, &original_pItemDrop);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4D900" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4D900, dll_base + 0x0001D900);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pItemDrop);
			setup_data(original_pGame, original_pItem, original_pItemDrop);

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pItemDrop);
			original(&original_pGame, &original_pItem, &original_pItemDrop);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4DA10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AssignCharmAffixes, dll_base + 0x0001DA10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pItemDrop);
			setup_data(original_pGame, original_pItem, original_pItemDrop);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pItem, &moo_pItemDrop);
			const auto original_result = original(&original_pGame, &original_pItem, &original_pItemDrop);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4DB60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMS_AssignSpecial_6FC4DB60, dll_base + 0x0001DB60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pItemDrop);
			setup_data(original_pGame, original_pItem, original_pItemDrop);

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pItemDrop);
			original(&original_pGame, &original_pItem, &original_pItemDrop);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4DC20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4DC20, dll_base + 0x0001DC20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pItemDrop);
			setup_data(original_pGame, original_pItem, original_pItemDrop);

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pItemDrop);
			original(&original_pGame, &original_pItem, &original_pItemDrop);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4DE00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RollItemQuality, dll_base + 0x0001DE00);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDropStrc moo_pItemDrop{};
			D2UnitStrc original_pItem{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pItemDrop);
			setup_data(original_pItem, original_pItemDrop);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pItemDrop);
			const auto original_result = original(&original_pItem, &original_pItemDrop);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4E1A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4E1A0, dll_base + 0x0001E1A0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc* moo_ppItem{};
			D2UnitStrc* original_ppItem{};

			const auto setup_data = [](
				D2UnitStrc*& ppItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_ppItem);
			setup_data(original_ppItem);

			// Call both implementations
			sut(&moo_ppItem);
			original(&original_ppItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4E1F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4E1F0, dll_base + 0x0001E1F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ItemDropStrc moo_pItemDrop{};
			D2UnitStrc* moo_ppItem{};
			D2GameStrc original_pGame{};
			D2ItemDropStrc original_pItemDrop{};
			D2UnitStrc* original_ppItem{};
			int32_t nLowSeed{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ItemDropStrc& pItemDrop,
				D2UnitStrc*& ppItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItemDrop, moo_ppItem);
			setup_data(original_pGame, original_pItemDrop, original_ppItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pItemDrop, &moo_ppItem, nLowSeed);
			original(&original_pGame, &original_pItemDrop, &original_ppItem, nLowSeed);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
			SKIP_MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4E430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4E430, dll_base + 0x0001E430);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ItemDropStrc moo_pItemDrop{};
			D2UnitStrc* moo_ppItem{};
			uint32_t moo_pLowSeed{};
			D2GameStrc original_pGame{};
			D2ItemDropStrc original_pItemDrop{};
			D2UnitStrc* original_ppItem{};
			uint32_t original_pLowSeed{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ItemDropStrc& pItemDrop,
				D2UnitStrc*& ppItem,
				uint32_t& pLowSeed
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItemDrop, moo_ppItem, moo_pLowSeed);
			setup_data(original_pGame, original_pItemDrop, original_ppItem, original_pLowSeed);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pItemDrop, &moo_ppItem, &moo_pLowSeed);
			const auto original_result = original(&original_pGame, &original_pItemDrop, &original_ppItem, &original_pLowSeed);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
			SKIP_MOO_CHECK_EQ(moo_ppItem, original_ppItem, "Comparing ppItem");
			SKIP_MOO_CHECK_EQ(moo_pLowSeed, original_pLowSeed, "Comparing pLowSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4E4D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RollLimitedRandomNumber, dll_base + 0x0001E4D0);
		
		SUBCASE("")
		{
			// Input data
			D2SeedStrc moo_pSeed{};
			D2SeedStrc original_pSeed{};
			int32_t nMax{};

			const auto setup_data = [](
				D2SeedStrc& pSeed
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSeed);
			setup_data(original_pSeed);

			// Call both implementations
			const auto moo_result = sut(&moo_pSeed, nMax);
			const auto original_result = original(&original_pSeed, nMax);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4E520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_InitItemStats_6FC4E520, dll_base + 0x0001E520);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc* moo_ppUnit{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2UnitStrc* original_ppUnit{};
			D2ItemDropStrc original_pItemDrop{};
			int32_t bQuestItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc*& ppUnit,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_ppUnit, moo_pItemDrop);
			setup_data(original_pGame, original_ppUnit, original_pItemDrop);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_ppUnit, &moo_pItemDrop, bQuestItem);
			const auto original_result = original(&original_pGame, &original_ppUnit, &original_pItemDrop, bQuestItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_ppUnit, original_ppUnit, "Comparing ppUnit");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4EBF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RollRandomNumber, dll_base + 0x0001EBF0);
		
		SUBCASE("")
		{
			// Input data
			D2SeedStrc moo_pSeed{};
			D2SeedStrc original_pSeed{};

			const auto setup_data = [](
				D2SeedStrc& pSeed
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pSeed);
			setup_data(original_pSeed);

			// Call both implementations
			const auto moo_result = sut(&moo_pSeed);
			const auto original_result = original(&original_pSeed);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4EC10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4EC10, dll_base + 0x0001EC10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			BYTE moo_pBitstream{};
			D2ItemSaveStrc moo_pItemSave{};
			uint32_t moo_pSize{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			BYTE original_pBitstream{};
			D2ItemSaveStrc original_pItemSave{};
			uint32_t original_pSize{};
			uint32_t nBufferSize{};
			int32_t bCheckForHeader{};
			uint32_t dwVersion{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				BYTE& pBitstream,
				D2ItemSaveStrc& pItemSave,
				uint32_t& pSize
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pBitstream, moo_pItemSave, moo_pSize);
			setup_data(original_pGame, original_pRoom, original_pBitstream, original_pItemSave, original_pSize);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pBitstream, nBufferSize, bCheckForHeader, &moo_pItemSave, &moo_pSize, dwVersion);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pBitstream, nBufferSize, bCheckForHeader, &original_pItemSave, &original_pSize, dwVersion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pBitstream, original_pBitstream, "Comparing pBitstream");
			SKIP_MOO_CHECK_EQ(moo_pItemSave, original_pItemSave, "Comparing pItemSave");
			SKIP_MOO_CHECK_EQ(moo_pSize, original_pSize, "Comparing pSize");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4ED80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CreateItemEx_6FC4ED80, dll_base + 0x0001ED80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2ItemDropStrc original_pItemDrop{};
			int32_t bUseSeed{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItemDrop);
			setup_data(original_pGame, original_pItemDrop);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pItemDrop, bUseSeed);
			const auto original_result = original(&original_pGame, &original_pItemDrop, bUseSeed);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4F290" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4F290, dll_base + 0x0001F290);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2CoordStrc moo_pCoords{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2CoordStrc original_pCoords{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2CoordStrc& pCoords,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pCoords, moo_pItemDrop);
			setup_data(original_pGame, original_pRoom, original_pCoords, original_pItemDrop);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pCoords, &moo_pItemDrop);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pCoords, &original_pItemDrop);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCoords, original_pCoords, "Comparing pCoords");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4F4A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4F4A0, dll_base + 0x0001F4A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2SeedStrc moo_pSeed{};
			D2GameStrc original_pGame{};
			D2SeedStrc original_pSeed{};
			int32_t nLevelId{};
			int32_t a4{};
			int32_t a5{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2SeedStrc& pSeed
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pSeed);
			setup_data(original_pGame, original_pSeed);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pSeed, nLevelId, a4, a5, a6);
			const auto original_result = original(&original_pGame, &original_pSeed, nLevelId, a4, a5, a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4F640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4F640, dll_base + 0x0001F640);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2CoordStrc moo_pCoord{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2CoordStrc original_pCoord{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2CoordStrc& pCoord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pCoord);
			setup_data(original_pGame, original_pRoom, original_pCoord);

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pCoord);
			original(&original_pGame, &original_pRoom, &original_pCoord);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4F830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_DropArmor_6FC4F830, dll_base + 0x0001F830);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2CoordStrc moo_pCoords{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2CoordStrc original_pCoords{};
			D2UnitStrc original_pUnit{};
			int32_t a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2CoordStrc& pCoords,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pCoords, moo_pUnit);
			setup_data(original_pGame, original_pRoom, original_pCoords, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pCoords, a4, a5, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pCoords, a4, a5, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCoords, original_pCoords, "Comparing pCoords");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4FA50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_DropWeapon_6FC4FA50, dll_base + 0x0001FA50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2CoordStrc moo_pCoords{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2CoordStrc original_pCoords{};
			D2UnitStrc original_pUnit{};
			int32_t a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2CoordStrc& pCoords,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pCoords, moo_pUnit);
			setup_data(original_pGame, original_pRoom, original_pCoords, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pCoords, a4, a5, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pCoords, a4, a5, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCoords, original_pCoords, "Comparing pCoords");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4FCA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4FCA0, dll_base + 0x0001FCA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ActiveRoomStrc moo_pRoom{};
			D2CoordStrc moo_pCoord{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2ActiveRoomStrc original_pRoom{};
			D2CoordStrc original_pCoord{};
			D2UnitStrc original_pUnit{};
			int32_t a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ActiveRoomStrc& pRoom,
				D2CoordStrc& pCoord,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pRoom, moo_pCoord, moo_pUnit);
			setup_data(original_pGame, original_pRoom, original_pCoord, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pCoord, a4, a5, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pCoord, a4, a5, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4FEC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_DropItemAtUnit_6FC4FEC0, dll_base + 0x0001FEC0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			int32_t moo_pItemLevel{};
			D2ItemDropStrc moo_pItemDrop{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t original_pItemLevel{};
			D2ItemDropStrc original_pItemDrop{};
			int32_t nQuality{};
			int32_t a6{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				int32_t& pItemLevel,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pItemLevel, moo_pItemDrop);
			setup_data(original_pGame, original_pUnit, original_pItemLevel, original_pItemDrop);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nQuality, &moo_pItemLevel, &moo_pItemDrop, a6, a7);
			const auto original_result = original(&original_pGame, &original_pUnit, nQuality, &original_pItemLevel, &original_pItemDrop, a6, a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItemLevel, original_pItemLevel, "Comparing pItemLevel");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC501A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CreateItemUnit_6FC501A0, dll_base + 0x000201A0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pPlayer{};
			D2GameStrc original_pGame{};
			int32_t nItemId{};
			int32_t nSpawnTarget{};
			int32_t nQuality{};
			int32_t bNoSockets{};
			int32_t bNoEthereal{};
			int32_t nItemLevel{};
			int32_t bUseSeed{};
			int32_t dwSeed{};
			int32_t dwItemSeed{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pGame);
			setup_data(original_pPlayer, original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, nItemId, &moo_pGame, nSpawnTarget, nQuality, bNoSockets, bNoEthereal, nItemLevel, bUseSeed, dwSeed, dwItemSeed);
			const auto original_result = original(&original_pPlayer, nItemId, &original_pGame, nSpawnTarget, nQuality, bNoSockets, bNoEthereal, nItemLevel, bUseSeed, dwSeed, dwItemSeed);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC502B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC502B0, dll_base + 0x000202B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC502E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RemoveAll, dll_base + 0x000202E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50320" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RemoveFromAllPlayers, dll_base + 0x00020320);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_PlayerIterateCallback_RemoveItem, dll_base + 0x00020340);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, moo_pArg);
			original(&original_pGame, &original_pUnit, original_pArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC503A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsInPlayersInventory, dll_base + 0x000203A0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			D2InventoryStrc original_pInventory{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem,
				D2InventoryStrc& pInventory
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pItem, moo_pInventory);
			setup_data(original_pPlayer, original_pItem, original_pInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &moo_pItem, &moo_pInventory);
			const auto original_result = original(&original_pPlayer, &original_pItem, &original_pInventory);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_FindQuestItem, dll_base + 0x00020410);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint32_t dwItemCode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, dwItemCode);
			const auto original_result = original(&original_pGame, &original_pUnit, dwItemCode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC504F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemLevelForNewItem, dll_base + 0x000204F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nLevelId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nLevelId);
			const auto original_result = original(&original_pUnit, nLevelId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50560" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_UpdateDurability, dll_base + 0x00020560);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pItem);
			setup_data(original_pGame, original_pUnit, original_pItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			original(&original_pGame, &original_pUnit, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50820" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_FillItemDrop, dll_base + 0x00020820);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2ItemDropStrc moo_pItemDrop{};
			D2UnitStrc moo_pItem{};
			D2GameStrc original_pGame{};
			D2ItemDropStrc original_pItemDrop{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2ItemDropStrc& pItemDrop,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItemDrop, moo_pItem);
			setup_data(original_pGame, original_pItemDrop, original_pItem);

			// Call both implementations
			sut(&moo_pGame, &moo_pItemDrop, &moo_pItem);
			original(&original_pGame, &original_pItemDrop, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC509F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DropGoldPile, dll_base + 0x000209F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint32_t nValue{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nValue);
			original(&original_pGame, &original_pUnit, nValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50C50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_HandleGoldTransaction, dll_base + 0x00020C50);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			uint32_t nValue{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nValue);
			original(&original_pGame, &original_pUnit, nValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50D80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DropPlayerEar, dll_base + 0x00020D80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetHealthPotionDropCode, dll_base + 0x00020F70);
		
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
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50FF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetManaPotionDropCode, dll_base + 0x00020FF0);
		
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
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC51070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_Duplicate, dll_base + 0x00021070);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pOwner{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pOwner{};
			int32_t bDuplicateSocketFillers{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pOwner);
			setup_data(original_pGame, original_pItem, original_pOwner);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pItem, &moo_pOwner, bDuplicateSocketFillers);
			const auto original_result = original(&original_pGame, &original_pItem, &original_pOwner, bDuplicateSocketFillers);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC512C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC512C0, dll_base + 0x000212C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC51310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC51310, dll_base + 0x00021310);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC51360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_DropTC_6FC51360, dll_base + 0x00021360);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMonster{};
			D2UnitStrc moo_pPlayer{};
			D2TCExShortStrc moo_pTCTxtRecord{};
			D2UnitStrc* moo_ppItems{};
			int32_t moo_pnItemsDropped{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMonster{};
			D2UnitStrc original_pPlayer{};
			D2TCExShortStrc original_pTCTxtRecord{};
			D2UnitStrc* original_ppItems{};
			int32_t original_pnItemsDropped{};
			int32_t nQuality{};
			int32_t nLvl{};
			int32_t a7{};
			int32_t nMaxItems{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMonster,
				D2UnitStrc& pPlayer,
				D2TCExShortStrc& pTCTxtRecord,
				D2UnitStrc*& ppItems,
				int32_t& pnItemsDropped
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMonster, moo_pPlayer, moo_pTCTxtRecord, moo_ppItems, moo_pnItemsDropped);
			setup_data(original_pGame, original_pMonster, original_pPlayer, original_pTCTxtRecord, original_ppItems, original_pnItemsDropped);

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster, &moo_pPlayer, &moo_pTCTxtRecord, nQuality, nLvl, a7, &moo_ppItems, &moo_pnItemsDropped, nMaxItems);
			original(&original_pGame, &original_pMonster, &original_pPlayer, &original_pTCTxtRecord, nQuality, nLvl, a7, &original_ppItems, &original_pnItemsDropped, nMaxItems);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pTCTxtRecord, original_pTCTxtRecord, "Comparing pTCTxtRecord");
			SKIP_MOO_CHECK_EQ(moo_ppItems, original_ppItems, "Comparing ppItems");
			SKIP_MOO_CHECK_EQ(moo_pnItemsDropped, original_pnItemsDropped, "Comparing pnItemsDropped");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetRoom_6FC52070, dll_base + 0x00022070);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nSubtileX{};
			int32_t nSubtileY{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nSubtileX, nSubtileY);
			const auto original_result = original(&original_pRoom, nSubtileX, nSubtileY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52110" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC52110, dll_base + 0x00022110);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pMonster{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc* moo_ppItems{};
			int32_t moo_pnItemsDropped{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pMonster{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc* original_ppItems{};
			int32_t original_pnItemsDropped{};
			int32_t nTCId{};
			int32_t nQuality{};
			int32_t nItemLevel{};
			int32_t a7{};
			int32_t nMaxItems{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pMonster,
				D2UnitStrc& pPlayer,
				D2UnitStrc*& ppItems,
				int32_t& pnItemsDropped
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pMonster, moo_pPlayer, moo_ppItems, moo_pnItemsDropped);
			setup_data(original_pGame, original_pMonster, original_pPlayer, original_ppItems, original_pnItemsDropped);

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster, &moo_pPlayer, nTCId, nQuality, nItemLevel, a7, &moo_ppItems, &moo_pnItemsDropped, nMaxItems);
			original(&original_pGame, &original_pMonster, &original_pPlayer, nTCId, nQuality, nItemLevel, a7, &original_ppItems, &original_pnItemsDropped, nMaxItems);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_ppItems, original_ppItems, "Comparing ppItems");
			SKIP_MOO_CHECK_EQ(moo_pnItemsDropped, original_pnItemsDropped, "Comparing pnItemsDropped");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC521D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetGroundRemovalTime, dll_base + 0x000221D0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52260" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_DropItem_6FC52260, dll_base + 0x00022260);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pItem, moo_pRoom);
			setup_data(original_pGame, original_pUnit, original_pItem, original_pRoom);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pRoom, nX, nY);
			original(&original_pGame, &original_pUnit, &original_pItem, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DeleteInactiveItems, dll_base + 0x00022300);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nAct{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame, nAct);
			original(&original_pGame, nAct);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC523B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DestroyRunewordStatList, dll_base + 0x000223B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC52410, dll_base + 0x00022410);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ItemDropStrc moo_pItemDrop{};
			D2UnitStrc original_pUnit{};
			D2ItemDropStrc original_pItemDrop{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2ItemDropStrc& pItemDrop
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pItemDrop);
			setup_data(original_pUnit, original_pItemDrop);

			// Call both implementations
			sut(&moo_pUnit, &moo_pItemDrop);
			original(&original_pUnit, &original_pItemDrop);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52650" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC52650, dll_base + 0x00022650);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nItemLvl{};
			int32_t nClassFirstSkillId{};
			int32_t nSkillCount{};
			int32_t nItemDropLvl{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nItemLvl, nClassFirstSkillId, nSkillCount, nItemDropLvl);
			original(&original_pUnit, nItemLvl, nClassFirstSkillId, nSkillCount, nItemDropLvl);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
