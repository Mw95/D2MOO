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
#include <ITEMS/ItemMode.h>
#include <Units/Units.h>


TEST_SUITE("ItemModeTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC41900" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_Return1_6FC41900, dll_base + 0x00011900);
		
		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC41910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMMODE_ServerStatlistCallback_6FC41910, dll_base + 0x00011910);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pOwner{};
				D2UnitStrc pOther{};
				
				return std::tuple{ pGame, pOwner, pOther };
			};
			
			// Input data
			auto [moo_pGame, moo_pOwner, moo_pOther] = setup_data();
			auto [original_pGame, original_pOwner, original_pOther] = setup_data();
			int32_t nLayer_StatId{};
			int32_t nPreviousValue{};
			int32_t nNewValue{};

			// Call both implementations
			sut(&moo_pGame, &moo_pOwner, &moo_pOther, nLayer_StatId, nPreviousValue, nNewValue);
			original(&original_pGame, &original_pOwner, &original_pOther, nLayer_StatId, nPreviousValue, nNewValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pOther, original_pOther, "Comparing pOther");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC42050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC42050, dll_base + 0x00012050);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pItem{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pItem, pClient };
			};
			
			// Input data
			auto [moo_pItem, moo_pClient] = setup_data();
			auto [original_pItem, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pItem, &moo_pClient);
			original(&original_pItem, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC420B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC420B0, dll_base + 0x000120B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pItem{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pItem, pClient };
			};
			
			// Input data
			auto [moo_pItem, moo_pClient] = setup_data();
			auto [original_pItem, original_pClient] = setup_data();

			// Call both implementations
			sut(&moo_pItem, &moo_pClient);
			original(&original_pItem, &original_pClient);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC42120" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC42120, dll_base + 0x00012120);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pUnit, pItem };
			};
			
			// Input data
			auto [moo_pUnit, moo_pItem] = setup_data();
			auto [original_pUnit, original_pItem] = setup_data();
			int32_t a3{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pItem, a3);
			const auto original_result = original(&original_pUnit, &original_pItem, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC42310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMS_UpdateItemStatlist_6FC42310, dll_base + 0x00012310);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pItem, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pUnit] = setup_data();
			auto [original_pGame, original_pItem, original_pUnit] = setup_data();
			int32_t a4{};

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pUnit, a4);
			original(&original_pGame, &original_pItem, &original_pUnit, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC424E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMS_UpdateTransferredProperties_6FC424E0, dll_base + 0x000124E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pItem, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pTarget] = setup_data();
			auto [original_pGame, original_pItem, original_pTarget] = setup_data();
			int32_t bUpdateStatList{};
			int32_t bUpdateVitals{};

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pTarget, bUpdateStatList, bUpdateVitals);
			original(&original_pGame, &original_pItem, &original_pTarget, bUpdateStatList, bUpdateVitals);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC425F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC425F0, dll_base + 0x000125F0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC428F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC428F0, dll_base + 0x000128F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pItem{};
				D2ItemsTxt pItemsTxtRecord{};
				D2UnitStrc pPreviousItem{};
				
				return std::tuple{ pItem, pItemsTxtRecord, pPreviousItem };
			};
			
			// Input data
			auto [moo_pItem, moo_pItemsTxtRecord, moo_pPreviousItem] = setup_data();
			auto [original_pItem, original_pItemsTxtRecord, original_pPreviousItem] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pItemsTxtRecord, &moo_pPreviousItem);
			const auto original_result = original(&original_pItem, &original_pItemsTxtRecord, &original_pPreviousItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemsTxtRecord, original_pItemsTxtRecord, "Comparing pItemsTxtRecord");
			SKIP_MOO_CHECK_EQ(moo_pPreviousItem, original_pPreviousItem, "Comparing pPreviousItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC42B80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PickupItemEx_6FC42B80, dll_base + 0x00012B80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a4{};
				
				return std::tuple{ pGame, pUnit, a4 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a4] = setup_data();
			auto [original_pGame, original_pUnit, original_a4] = setup_data();
			int32_t nItemGUID{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nItemGUID, &moo_a4);
			original(&original_pGame, &original_pUnit, nItemGUID, &original_a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC42DD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PickupGold_6FC42DD0, dll_base + 0x00012DD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pGoldPile{};
				
				return std::tuple{ pGame, pUnit, pGoldPile };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pGoldPile] = setup_data();
			auto [original_pGame, original_pUnit, original_pGoldPile] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pGoldPile);
			original(&original_pGame, &original_pUnit, &original_pGoldPile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pGoldPile, original_pGoldPile, "Comparing pGoldPile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC42F20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC42F20, dll_base + 0x00012F20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				int32_t pBodyLoc{};
				
				return std::tuple{ pUnit, pItem, pBodyLoc };
			};
			
			// Input data
			auto [moo_pUnit, moo_pItem, moo_pBodyLoc] = setup_data();
			auto [original_pUnit, original_pItem, original_pBodyLoc] = setup_data();
			int32_t bSkipRequirementCheck{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pItem, &moo_pBodyLoc, bSkipRequirementCheck);
			const auto original_result = original(&original_pUnit, &original_pItem, &original_pBodyLoc, bSkipRequirementCheck);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBodyLoc, original_pBodyLoc, "Comparing pBodyLoc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC43160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC43160, dll_base + 0x00013160);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2ItemModeArgStrc pItemModeArg{};
				
				return std::tuple{ pUnit, pItem, pItemModeArg };
			};
			
			// Input data
			auto [moo_pUnit, moo_pItem, moo_pItemModeArg] = setup_data();
			auto [original_pUnit, original_pItem, original_pItemModeArg] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_pItem, &moo_pItemModeArg);
			original(&original_pUnit, &original_pItem, &original_pItemModeArg);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemModeArg, original_pItemModeArg, "Comparing pItemModeArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC43280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC43280, dll_base + 0x00013280);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ItemModeArgStrc pArg1{};
				D2ItemModeArgStrc pArg2{};
				
				return std::tuple{ pArg1, pArg2 };
			};
			
			// Input data
			auto [moo_pArg1, moo_pArg2] = setup_data();
			auto [original_pArg1, original_pArg2] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pArg1, &moo_pArg2);
			const auto original_result = original(&original_pArg1, &original_pArg2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pArg1, original_pArg1, "Comparing pArg1");
			SKIP_MOO_CHECK_EQ(moo_pArg2, original_pArg2, "Comparing pArg2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC43340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PickupItem_6FC43340, dll_base + 0x00013340);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a4{};
				
				return std::tuple{ pGame, pUnit, a4 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a4] = setup_data();
			auto [original_pGame, original_pUnit, original_a4] = setup_data();
			int32_t nItemGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, &moo_a4);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, &original_a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC437F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC437F0, dll_base + 0x000137F0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC43AF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC43AF0, dll_base + 0x00013AF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pUnit, pItem };
			};
			
			// Input data
			auto [moo_pUnit, moo_pItem] = setup_data();
			auto [original_pUnit, original_pItem] = setup_data();
			int32_t nQuantityBonus{};

			// Call both implementations
			sut(&moo_pUnit, &moo_pItem, nQuantityBonus);
			original(&original_pUnit, &original_pItem, nQuantityBonus);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC43BF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC43BF0, dll_base + 0x00013BF0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC43E60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC43E60, dll_base + 0x00013E60);
		
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
			int32_t bRemove{};
			int32_t nPage{};
			char szFile{};
			int32_t nLine{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, bRemove, nPage, &szFile, nLine);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, bRemove, nPage, &szFile, nLine);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC44030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC44030, dll_base + 0x00014030);
		
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
			int32_t nItemGUID{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nItemGUID);
			original(&original_pGame, &original_pUnit, nItemGUID);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC44410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PlaceItem_6FC44410, dll_base + 0x00014410);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2InventoryStrc pInventory{};
				
				return std::tuple{ pGame, pPlayer, pInventory };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pInventory] = setup_data();
			auto [original_pGame, original_pPlayer, original_pInventory] = setup_data();
			char szFile{};
			int32_t nLine{};
			int32_t nUnitId{};
			int32_t nX{};
			int32_t nY{};
			int32_t a8{};
			int32_t a9{};

			// Call both implementations
			const auto moo_result = sut(&szFile, nLine, &moo_pGame, &moo_pPlayer, nUnitId, nX, nY, a8, a9, &moo_pInventory);
			const auto original_result = original(&szFile, nLine, &original_pGame, &original_pPlayer, nUnitId, nX, nY, a8, a9, &original_pInventory);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC446B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC446B0, dll_base + 0x000146B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a4{};
				D2InventoryStrc pInventoryArg{};
				
				return std::tuple{ pGame, pUnit, a4, pInventoryArg };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a4, moo_pInventoryArg] = setup_data();
			auto [original_pGame, original_pUnit, original_a4, original_pInventoryArg] = setup_data();
			int32_t nItemGUID{};
			int32_t a5{};
			int32_t bSetQuantityFlag{};
			int32_t a8{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, &moo_a4, a5, bSetQuantityFlag, &moo_pInventoryArg, a8);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, &original_a4, a5, bSetQuantityFlag, &original_pInventoryArg, a8);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
			SKIP_MOO_CHECK_EQ(moo_pInventoryArg, original_pInventoryArg, "Comparing pInventoryArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC44A90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMS_UpdateInventoryItems_6FC44A90, dll_base + 0x00014A90);
		
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
			int32_t bRefresh{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, bRefresh);
			original(&original_pGame, &original_pUnit, bRefresh);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC44F00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC44F00, dll_base + 0x00014F00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnkItemModeStrc a2{};
				
				return std::tuple{ pUnit, a2 };
			};
			
			// Input data
			auto [moo_pUnit, moo_a2] = setup_data();
			auto [original_pUnit, original_a2] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_a2);
			original(&original_pUnit, &original_a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC44FB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC44FB0, dll_base + 0x00014FB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnkItemModeStrc a2{};
				
				return std::tuple{ pUnit, a2 };
			};
			
			// Input data
			auto [moo_pUnit, moo_a2] = setup_data();
			auto [original_pUnit, original_a2] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_a2);
			original(&original_pUnit, &original_a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC45050" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMS_UpdateInventoryItems_6FC45050, dll_base + 0x00015050);
		
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
			int32_t a3{};
			int32_t bRefresh{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, bRefresh);
			original(&original_pGame, &original_pUnit, a3, bRefresh);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC45060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC45060, dll_base + 0x00015060);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				int32_t a6{};
				
				return std::tuple{ pGame, pPlayer, a6 };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_a6] = setup_data();
			auto [original_pGame, original_pPlayer, original_a6] = setup_data();
			int32_t nItemGUID{};
			uint8_t nBodyLoc{};
			int32_t bSkipRequirementCheck{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nItemGUID, nBodyLoc, bSkipRequirementCheck, &moo_a6);
			const auto original_result = original(&original_pGame, &original_pPlayer, nItemGUID, nBodyLoc, bSkipRequirementCheck, &original_a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC45300" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC45300, dll_base + 0x00015300);
		
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
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC45550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC45550, dll_base + 0x00015550);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a6{};
				
				return std::tuple{ pGame, pUnit, a6 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a6] = setup_data();
			auto [original_pGame, original_pUnit, original_a6] = setup_data();
			int32_t nItemGUID{};
			uint8_t nBodyLoc{};
			int32_t bSkipRequirementCheck{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, nBodyLoc, bSkipRequirementCheck, &moo_a6);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, nBodyLoc, bSkipRequirementCheck, &original_a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC45930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC45930, dll_base + 0x00015930);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC45B30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC45B30, dll_base + 0x00015B30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a5{};
				
				return std::tuple{ pGame, pUnit, a5 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a5] = setup_data();
			auto [original_pGame, original_pUnit, original_a5] = setup_data();
			uint8_t nBodyLoc{};
			int32_t bSetQuantityFlag{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nBodyLoc, bSetQuantityFlag, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nBodyLoc, bSetQuantityFlag, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC45E60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC45E60, dll_base + 0x00015E60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a6{};
				
				return std::tuple{ pGame, pUnit, a6 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a6] = setup_data();
			auto [original_pGame, original_pUnit, original_a6] = setup_data();
			int32_t nItemGUID{};
			uint8_t nBodyLoc{};
			int32_t bSkipRequirementCheck{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, nBodyLoc, bSkipRequirementCheck, &moo_a6);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, nBodyLoc, bSkipRequirementCheck, &original_a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC46270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC46270, dll_base + 0x00016270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a5{};
				
				return std::tuple{ pGame, pUnit, a5 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a5] = setup_data();
			auto [original_pGame, original_pUnit, original_a5] = setup_data();
			int32_t nItemGUID{};
			uint8_t nBodyLoc{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, nBodyLoc, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, nBodyLoc, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC46840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC46840, dll_base + 0x00016840);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a3{};
				
				return std::tuple{ pGame, pUnit, a3 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a3] = setup_data();
			auto [original_pGame, original_pUnit, original_a3] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_a3);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC46D40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC46D40, dll_base + 0x00016D40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a7{};
				
				return std::tuple{ pGame, pUnit, a7 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a7] = setup_data();
			auto [original_pGame, original_pUnit, original_a7] = setup_data();
			int32_t nCursorItemGUID{};
			int32_t nGridItemGUID{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nCursorItemGUID, nGridItemGUID, nX, nY, &moo_a7);
			const auto original_result = original(&original_pGame, &original_pUnit, nCursorItemGUID, nGridItemGUID, nX, nY, &original_a7);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a7, original_a7, "Comparing a7");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC471F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RemoveItem_6FC471F0, dll_base + 0x000171F0);
		
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
			int32_t bSendPacket{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pItem, bSendPacket);
			original(&original_pGame, &original_pUnit, &original_pItem, bSendPacket);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC47380" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC47380, dll_base + 0x00017380);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC47470" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC47470, dll_base + 0x00017470);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a5{};
				
				return std::tuple{ pGame, pUnit, a5 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a5] = setup_data();
			auto [original_pGame, original_pUnit, original_a5] = setup_data();
			int32_t nTargetGUID{};
			int32_t nUseItemGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nTargetGUID, nUseItemGUID, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nTargetGUID, nUseItemGUID, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC47C90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC47C90, dll_base + 0x00017C90);
		
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
			int32_t nSkillId{};

			// Call both implementations
			sut(&moo_pUnit, nSkillId);
			original(&original_pUnit, nSkillId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC47D30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC47D30, dll_base + 0x00017D30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a6{};
				
				return std::tuple{ pGame, pUnit, a6 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a6] = setup_data();
			auto [original_pGame, original_pUnit, original_a6] = setup_data();
			int32_t nItemGUID{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, nX, nY, &moo_a6);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, nX, nY, &original_a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC484E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC484E0, dll_base + 0x000184E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a5{};
				
				return std::tuple{ pGame, pUnit, a5 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a5] = setup_data();
			auto [original_pGame, original_pUnit, original_a5] = setup_data();
			int32_t nItemGUID1{};
			int32_t nItemGUID2{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID1, nItemGUID2, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID1, nItemGUID2, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC48930" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_Return0_6FC48930, dll_base + 0x00018930);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				int32_t a2{};
				
				return std::tuple{ a2 };
			};
			
			// Input data
			auto [moo_a2] = setup_data();
			auto [original_a2] = setup_data();
			int32_t a1{};

			// Call both implementations
			const auto moo_result = sut(a1, &moo_a2);
			const auto original_result = original(a1, &original_a2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC48940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC48940, dll_base + 0x00018940);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a6{};
				
				return std::tuple{ pGame, pUnit, a6 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a6] = setup_data();
			auto [original_pGame, original_pUnit, original_a6] = setup_data();
			int32_t nItemGUID{};
			int32_t nBeltSlot{};
			int32_t bFindFreeSlot{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, nBeltSlot, bFindFreeSlot, &moo_a6);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, nBeltSlot, bFindFreeSlot, &original_a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC48B40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC48B40, dll_base + 0x00018B40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a4{};
				
				return std::tuple{ pGame, pUnit, a4 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a4] = setup_data();
			auto [original_pGame, original_pUnit, original_a4] = setup_data();
			int32_t nItemGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, &moo_a4);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, &original_a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC48D50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC48D50, dll_base + 0x00018D50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a5{};
				
				return std::tuple{ pGame, pUnit, a5 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a5] = setup_data();
			auto [original_pGame, original_pUnit, original_a5] = setup_data();
			int32_t nCursorItemGUID{};
			int32_t nBeltItemGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nCursorItemGUID, nBeltItemGUID, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nCursorItemGUID, nBeltItemGUID, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC49090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC49090, dll_base + 0x00019090);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC49140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC49140, dll_base + 0x00019140);
		
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
			int8_t nX{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nX);
			original(&original_pGame, &original_pUnit, nX);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC49220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC49220, dll_base + 0x00019220);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a6{};
				
				return std::tuple{ pGame, pUnit, a6 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a6] = setup_data();
			auto [original_pGame, original_pUnit, original_a6] = setup_data();
			int32_t nItemGUID{};
			int32_t nX{};
			int32_t nY{};
			int32_t bUseOnMerc{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, nX, nY, &moo_a6, bUseOnMerc);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, nX, nY, &original_a6, bUseOnMerc);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a6, original_a6, "Comparing a6");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC49670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMS_Identify_6FC49670, dll_base + 0x00019670);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pPlayer, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pItem] = setup_data();
			auto [original_pGame, original_pPlayer, original_pItem] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pItem);
			original(&original_pGame, &original_pPlayer, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC49760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RemoveItemIfOnCursor_6FC49760, dll_base + 0x00019760);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pPlayer, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pItem] = setup_data();
			auto [original_pGame, original_pPlayer, original_pItem] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC497E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMSOCKET_PlaceItem_6FC497E0, dll_base + 0x000197E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t bPlaced{};
				
				return std::tuple{ pGame, pUnit, bPlaced };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_bPlaced] = setup_data();
			auto [original_pGame, original_pUnit, original_bPlaced] = setup_data();
			int32_t nSocketFillerGUID{};
			int32_t nItemGUID{};
			int32_t bRefresh{};
			int32_t bResetCursorItem{};
			int32_t bCheckMode{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSocketFillerGUID, nItemGUID, &moo_bPlaced, bRefresh, bResetCursorItem, bCheckMode);
			const auto original_result = original(&original_pGame, &original_pUnit, nSocketFillerGUID, nItemGUID, &original_bPlaced, bRefresh, bResetCursorItem, bCheckMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_bPlaced, original_bPlaced, "Comparing bPlaced");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC49AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC49AE0, dll_base + 0x00019AE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a5{};
				
				return std::tuple{ pGame, pUnit, a5 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a5] = setup_data();
			auto [original_pGame, original_pUnit, original_a5] = setup_data();
			int32_t nScrollGUID{};
			int32_t nBookGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nScrollGUID, nBookGUID, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nScrollGUID, nBookGUID, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC49DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC49DC0, dll_base + 0x00019DC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				int32_t a5{};
				
				return std::tuple{ pGame, pUnit, a5 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a5] = setup_data();
			auto [original_pGame, original_pUnit, original_a5] = setup_data();
			int32_t nItemGUID{};
			int32_t nCubeGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, nCubeGUID, &moo_a5);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, nCubeGUID, &original_a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC49F80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC49F80, dll_base + 0x00019F80);
		
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
			int32_t nItemGUID{};
			uint8_t nBodyLoc{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nItemGUID, nBodyLoc);
			const auto original_result = original(&original_pGame, &original_pUnit, nItemGUID, nBodyLoc);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4A2E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4A2E0, dll_base + 0x0001A2E0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4A350" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4A350, dll_base + 0x0001A350);
		
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
			int32_t nLengthStatId{};
			int32_t nValueStatId{};
			int32_t nMaxValue{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pItem, nLengthStatId, nValueStatId, nMaxValue);
			const auto original_result = original(&original_pGame, &original_pItem, nLengthStatId, nValueStatId, nMaxValue);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4A450" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4A450, dll_base + 0x0001A450);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4A460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_Items_EventsHandler_6FC4A460, dll_base + 0x0001A460);
		
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
			D2C_EventTypes nEventType{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEventType);
			original(&original_pGame, &original_pUnit, nEventType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4A4B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_DoKeyCheck_6FC4A4B0, dll_base + 0x0001A4B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4A660" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_Transmogrify_6FC4A660, dll_base + 0x0001A660);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4A9B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4A9B0, dll_base + 0x0001A9B0);
		
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
			uint8_t nBodyLoc{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, nBodyLoc);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, nBodyLoc);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4AB10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4AB10, dll_base + 0x0001AB10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer{};
				D2UnitStrc pItem{};
				D2UnitStrc* ppItem1{};
				D2UnitStrc* ppItem2{};
				int32_t pBodyLoc{};
				
				return std::tuple{ pPlayer, pItem, ppItem1, ppItem2, pBodyLoc };
			};
			
			// Input data
			auto [moo_pPlayer, moo_pItem, moo_ppItem1, moo_ppItem2, moo_pBodyLoc] = setup_data();
			auto [original_pPlayer, original_pItem, original_ppItem1, original_ppItem2, original_pBodyLoc] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &moo_pItem, &moo_ppItem1, &moo_ppItem2, &moo_pBodyLoc);
			const auto original_result = original(&original_pPlayer, &original_pItem, &original_ppItem1, &original_ppItem2, &original_pBodyLoc);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_ppItem1, original_ppItem1, "Comparing ppItem1");
			SKIP_MOO_CHECK_EQ(moo_ppItem2, original_ppItem2, "Comparing ppItem2");
			SKIP_MOO_CHECK_EQ(moo_pBodyLoc, original_pBodyLoc, "Comparing pBodyLoc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4AD80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4AD80, dll_base + 0x0001AD80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pCorpse{};
				
				return std::tuple{ pGame, pPlayer, pCorpse };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pCorpse] = setup_data();
			auto [original_pGame, original_pPlayer, original_pCorpse] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, &moo_pCorpse);
			const auto original_result = original(&original_pGame, &original_pPlayer, &original_pCorpse);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pCorpse, original_pCorpse, "Comparing pCorpse");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_UpdatePlayerVitals_6FC4B240, dll_base + 0x0001B240);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B2D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CheckHasFilledSockets_6FC4B2D0, dll_base + 0x0001B2D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pItem{};
				
				return std::tuple{ pItem };
			};
			
			// Input data
			auto [moo_pItem] = setup_data();
			auto [original_pItem] = setup_data();
			char szFile{};
			int32_t nLine{};

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &szFile, nLine);
			const auto original_result = original(&original_pItem, &szFile, nLine);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4B310, dll_base + 0x0001B310);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				D2UnitStrc pSocketable{};
				
				return std::tuple{ pGame, pUnit, pItem, pSocketable };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_pSocketable] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_pSocketable] = setup_data();
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_pSocketable, a5);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_pSocketable, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pSocketable, original_pSocketable, "Comparing pSocketable");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4B430, dll_base + 0x0001B430);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				int32_t a4{};
				
				return std::tuple{ pGame, pUnit, pItem, a4 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pItem, moo_a4] = setup_data();
			auto [original_pGame, original_pUnit, original_pItem, original_a4] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem, &moo_a4);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem, &original_a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B520" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4B520, dll_base + 0x0001B520);
		
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
			int32_t nValue{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pItem, nValue);
			original(&original_pGame, &original_pUnit, &original_pItem, nValue);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4B580, dll_base + 0x0001B580);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B630" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RepairBrokenItem_6FC4B630, dll_base + 0x0001B630);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pGame, pPlayer, pItem };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pItem] = setup_data();
			auto [original_pGame, original_pPlayer, original_pItem] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pItem);
			original(&original_pGame, &original_pPlayer, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4B740, dll_base + 0x0001B740);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnitStrc pItem{};
				
				return std::tuple{ pUnit, pItem };
			};
			
			// Input data
			auto [moo_pUnit, moo_pItem] = setup_data();
			auto [original_pUnit, original_pItem] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_pItem);
			original(&original_pUnit, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4B830, dll_base + 0x0001B830);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4B9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4B9D0, dll_base + 0x0001B9D0);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BA50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4BA50, dll_base + 0x0001BA50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BB90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_UpdatePlayerItems_6FC4BB90, dll_base + 0x0001BB90);
		
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
			int32_t a3{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3);
			original(&original_pGame, &original_pUnit, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BBB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4BBB0, dll_base + 0x0001BBB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pGame, pItem, pPlayer };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pPlayer] = setup_data();
			auto [original_pGame, original_pItem, original_pPlayer] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pPlayer);
			original(&original_pGame, &original_pItem, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMS_UpdateStatList_6FC4BC00, dll_base + 0x0001BC00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pItem, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pUnit] = setup_data();
			auto [original_pGame, original_pItem, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pUnit);
			original(&original_pGame, &original_pItem, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BC10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_ITEMMODE_Unk_6FC4BC10, dll_base + 0x0001BC10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BD50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RechargeItem_6FC4BD50, dll_base + 0x0001BD50);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pItem);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BE80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4BE80, dll_base + 0x0001BE80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pUnit, pGame, pRoom };
			};
			
			// Input data
			auto [moo_pUnit, moo_pGame, moo_pRoom] = setup_data();
			auto [original_pUnit, original_pGame, original_pRoom] = setup_data();
			int32_t nUnitGUID{};

			// Call both implementations
			sut(&moo_pUnit, &moo_pGame, nUnitGUID, &moo_pRoom);
			original(&original_pUnit, &original_pGame, nUnitGUID, &original_pRoom);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BF00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetFreeSpaceEx_6FC4BF00, dll_base + 0x0001BF00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2ActiveRoomStrc pRoom{};
				D2CoordStrc pCoords{};
				D2CoordStrc pReturnCoords{};
				
				return std::tuple{ pRoom, pCoords, pReturnCoords };
			};
			
			// Input data
			auto [moo_pRoom, moo_pCoords, moo_pReturnCoords] = setup_data();
			auto [original_pRoom, original_pCoords, original_pReturnCoords] = setup_data();
			int32_t nUnitSize{};

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, &moo_pCoords, &moo_pReturnCoords, nUnitSize);
			const auto original_result = original(&original_pRoom, &original_pCoords, &original_pReturnCoords, nUnitSize);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pCoords, original_pCoords, "Comparing pCoords");
			SKIP_MOO_CHECK_EQ(moo_pReturnCoords, original_pReturnCoords, "Comparing pReturnCoords");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4BFF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4BFF0, dll_base + 0x0001BFF0);
		
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
			int32_t nItemType{};
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pSeed, nLevelId, nItemType, a5);
			const auto original_result = original(&original_pGame, &original_pSeed, nLevelId, nItemType, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4C1E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4C1E0, dll_base + 0x0001C1E0);
		
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
			int32_t nItemType{};
			int32_t a5{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pSeed, nLevelId, nItemType, a5);
			const auto original_result = original(&original_pGame, &original_pSeed, nLevelId, nItemType, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4C3D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4C3D0, dll_base + 0x0001C3D0);
		
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
			int32_t nItemType{};
			int32_t a5{};
			int32_t a6{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pSeed, nLevelId, nItemType, a5, a6);
			const auto original_result = original(&original_pGame, &original_pSeed, nLevelId, nItemType, a5, a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC4C5F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC4C5F0, dll_base + 0x0001C5F0);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_ppUnit, &moo_pItemDrop);
			const auto original_result = original(&original_pGame, &original_ppUnit, &original_pItemDrop);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_ppUnit, original_ppUnit, "Comparing ppUnit");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
}
