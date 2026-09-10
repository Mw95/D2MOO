#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

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
			// TODO: Setup as needed
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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();
			int32_t nUniqueItemId{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem] = setup_data();
			auto [original_pGame, original_pItem] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc* ppItem{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ ppItem, pItemDrop };
			};
			
			// Input data
			auto [moo_ppItem, moo_pItemDrop] = setup_data();
			auto [original_ppItem, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, pItem, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_pItem, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pItem{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pItem, pItemDrop };
			};
			
			// Input data
			auto [moo_pItem, moo_pItemDrop] = setup_data();
			auto [original_pItem, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, pItem, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_pItem, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, pItem, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_pItem, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, pItem, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_pItem, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, pItem, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_pItem, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pItem{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pItem, pItemDrop };
			};
			
			// Input data
			auto [moo_pItem, moo_pItemDrop] = setup_data();
			auto [original_pItem, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc* ppItem{};
				
				return std::tuple{ ppItem };
			};
			
			// Input data
			auto [moo_ppItem] = setup_data();
			auto [original_ppItem] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ItemDropStrc pItemDrop{};
				D2UnitStrc* ppItem{};
				
				return std::tuple{ pGame, pItemDrop, ppItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pItemDrop, moo_ppItem] = setup_data();
			auto [original_pGame, original_pItemDrop, original_ppItem] = setup_data();
			int32_t nLowSeed{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ItemDropStrc pItemDrop{};
				D2UnitStrc* ppItem{};
				uint32_t pLowSeed{};
				
				return std::tuple{ pGame, pItemDrop, ppItem, pLowSeed };
			};
			
			// Input data
			auto [moo_pGame, moo_pItemDrop, moo_ppItem, moo_pLowSeed] = setup_data();
			auto [original_pGame, original_pItemDrop, original_ppItem, original_pLowSeed] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2SeedStrc pSeed{};
				
				return std::tuple{ pSeed };
			};
			
			// Input data
			auto [moo_pSeed] = setup_data();
			auto [original_pSeed] = setup_data();
			int32_t nMax{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc* ppUnit{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, ppUnit, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_ppUnit, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_ppUnit, original_pItemDrop] = setup_data();
			int32_t bQuestItem{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2SeedStrc pSeed{};
				
				return std::tuple{ pSeed };
			};
			
			// Input data
			auto [moo_pSeed] = setup_data();
			auto [original_pSeed] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				BYTE pBitstream{};
				D2ItemSaveStrc pItemSave{};
				uint32_t pSize{};
				
				return std::tuple{ pGame, pRoom, pBitstream, pItemSave, pSize };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pBitstream, moo_pItemSave, moo_pSize] = setup_data();
			auto [original_pGame, original_pRoom, original_pBitstream, original_pItemSave, original_pSize] = setup_data();
			uint32_t nBufferSize{};
			int32_t bCheckForHeader{};
			uint32_t dwVersion{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_pItemDrop] = setup_data();
			int32_t bUseSeed{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2CoordStrc pCoords{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, pRoom, pCoords, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pCoords, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_pRoom, original_pCoords, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2SeedStrc pSeed{};
				
				return std::tuple{ pGame, pSeed };
			};
			
			// Input data
			auto [moo_pGame, moo_pSeed] = setup_data();
			auto [original_pGame, original_pSeed] = setup_data();
			int32_t nLevelId{};
			int32_t a4{};
			int32_t a5{};
			int32_t a6{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2CoordStrc pCoord{};
				
				return std::tuple{ pGame, pRoom, pCoord };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pCoord] = setup_data();
			auto [original_pGame, original_pRoom, original_pCoord] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2CoordStrc pCoords{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pRoom, pCoords, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pCoords, moo_pUnit] = setup_data();
			auto [original_pGame, original_pRoom, original_pCoords, original_pUnit] = setup_data();
			int32_t a4{};
			int32_t a5{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2CoordStrc pCoords{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pRoom, pCoords, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pCoords, moo_pUnit] = setup_data();
			auto [original_pGame, original_pRoom, original_pCoords, original_pUnit] = setup_data();
			int32_t a4{};
			int32_t a5{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2CoordStrc pCoord{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pRoom, pCoord, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pCoord, moo_pUnit] = setup_data();
			auto [original_pGame, original_pRoom, original_pCoord, original_pUnit] = setup_data();
			int32_t a4{};
			int32_t a5{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t pItemLevel{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pGame, pUnit, pItemLevel, pItemDrop };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItemLevel, moo_pItemDrop] = setup_data();
			auto [original_pGame, original_pUnit, original_pItemLevel, original_pItemDrop] = setup_data();
			int32_t nQuality{};
			int32_t a6{};
			int32_t a7{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer{};
				D2GameStrc pGame{};
				
				return std::tuple{ pPlayer, pGame };
			};
			
			// Input data
			auto [moo_pPlayer, moo_pGame] = setup_data();
			auto [original_pPlayer, original_pGame] = setup_data();
			int32_t nItemId{};
			int32_t nSpawnTarget{};
			int32_t nQuality{};
			int32_t bNoSockets{};
			int32_t bNoEthereal{};
			int32_t nItemLevel{};
			int32_t bUseSeed{};
			int32_t dwSeed{};
			int32_t dwItemSeed{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem] = setup_data();
			auto [original_pGame, original_pItem] = setup_data();

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC50320" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RemoveFromAllPlayers, dll_base + 0x00020320);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer{};
				D2UnitStrc pItem{};
				D2InventoryStrc pInventory{};
				
				return std::tuple{ pPlayer, pItem, pInventory };
			};
			
			// Input data
			auto [moo_pPlayer, moo_pItem, moo_pInventory] = setup_data();
			auto [original_pPlayer, original_pItem, original_pInventory] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			uint32_t dwItemCode{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();
			int32_t nLevelId{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pUnit, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ItemDropStrc pItemDrop{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pItemDrop, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pItemDrop, moo_pItem] = setup_data();
			auto [original_pGame, original_pItemDrop, original_pItem] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			uint32_t nValue{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			uint32_t nValue{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2UnitStrc pOwner{};
				
				return std::tuple{ pGame, pItem, pOwner };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pOwner] = setup_data();
			auto [original_pGame, original_pItem, original_pOwner] = setup_data();
			int32_t bDuplicateSocketFillers{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				D2UnitStrc pPlayer{};
				D2TCExShortStrc pTCTxtRecord{};
				D2UnitStrc* ppItems{};
				int32_t pnItemsDropped{};
				
				return std::tuple{ pGame, pMonster, pPlayer, pTCTxtRecord, ppItems, pnItemsDropped };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster, moo_pPlayer, moo_pTCTxtRecord, moo_ppItems, moo_pnItemsDropped] = setup_data();
			auto [original_pGame, original_pMonster, original_pPlayer, original_pTCTxtRecord, original_ppItems, original_pnItemsDropped] = setup_data();
			int32_t nQuality{};
			int32_t nLvl{};
			int32_t a7{};
			int32_t nMaxItems{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pRoom };
			};
			
			// Input data
			auto [moo_pRoom] = setup_data();
			auto [original_pRoom] = setup_data();
			int32_t nSubtileX{};
			int32_t nSubtileY{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				D2UnitStrc pPlayer{};
				D2UnitStrc* ppItems{};
				int32_t pnItemsDropped{};
				
				return std::tuple{ pGame, pMonster, pPlayer, ppItems, pnItemsDropped };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster, moo_pPlayer, moo_ppItems, moo_pnItemsDropped] = setup_data();
			auto [original_pGame, original_pMonster, original_pPlayer, original_ppItems, original_pnItemsDropped] = setup_data();
			int32_t nTCId{};
			int32_t nQuality{};
			int32_t nItemLevel{};
			int32_t a7{};
			int32_t nMaxItems{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pGame, pUnit, pItem, pRoom };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pRoom] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pRoom] = setup_data();
			int32_t nX{};
			int32_t nY{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();
			int32_t nAct{};

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem] = setup_data();
			auto [original_pGame, original_pItem] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2ItemDropStrc pItemDrop{};
				
				return std::tuple{ pUnit, pItemDrop };
			};
			
			// Input data
			auto [moo_pUnit, moo_pItemDrop] = setup_data();
			auto [original_pUnit, original_pItemDrop] = setup_data();

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
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();
			int32_t nItemLvl{};
			int32_t nClassFirstSkillId{};
			int32_t nSkillCount{};
			int32_t nItemDropLvl{};

			// Call both implementations
			sut(&moo_pUnit, nItemLvl, nClassFirstSkillId, nSkillCount, nItemDropLvl);
			original(&original_pUnit, nItemLvl, nClassFirstSkillId, nSkillCount, nItemDropLvl);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
