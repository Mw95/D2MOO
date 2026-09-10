#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <ITEMS/ItemsMagic.h>
#include <Units/Units.h>


TEST_SUITE("ItemsMagicTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52920" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RollMagicAffixes, dll_base + 0x00022920);
		
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
			int32_t bRequireSpawnableAffix{};
			int32_t bForceAffixRoll{};
			int32_t bAssignProperties{};
			int32_t bPrefixes{};
			int32_t nPreferredAffixIndex{};

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex);
			const auto original_result = original(&original_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52980" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RollMagicAffixesOld, dll_base + 0x00022980);
		
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
			int32_t bRequireSpawnableAffix{};
			int32_t bForceAffixRoll{};
			int32_t bAssignProperties{};
			int32_t bPrefixes{};
			int32_t nPreferredAffixIndex{};

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex);
			const auto original_result = original(&original_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC52C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RollMagicAffixesNew, dll_base + 0x00022C00);
		
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
			int32_t bRequireSpawnableAffix{};
			int32_t bForceAffixRoll{};
			int32_t bAssignProperties{};
			int32_t bPrefixes{};
			int32_t nPreferredAffixIndex{};
			int32_t nAutoMagicGroup{};

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex, nAutoMagicGroup);
			const auto original_result = original(&original_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex, nAutoMagicGroup);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC53080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RollMagicAffixesWithAutomagicGroup, dll_base + 0x00023080);
		
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
			int32_t bRequireSpawnableAffix{};
			int32_t bForceAffixRoll{};
			int32_t bAssignProperties{};
			int32_t bPrefixes{};
			int32_t nPreferredAffixIndex{};
			int32_t nAutoMagicGroup{};

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex, nAutoMagicGroup);
			const auto original_result = original(&original_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex, nAutoMagicGroup);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC530E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_RollTemperedItemAffix, dll_base + 0x000230E0);
		
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
			int32_t bPrefix{};

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, bPrefix);
			const auto original_result = original(&original_pItem, bPrefix);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC53360" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RollRareItem_6FC53360, dll_base + 0x00023360);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC53610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_RollRareAffix_6FC53610, dll_base + 0x00023610);
		
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
			int32_t bPrefix{};

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, bPrefix);
			const auto original_result = original(&original_pItem, bPrefix);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC53760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC53760, dll_base + 0x00023760);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC53CD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC53CD0, dll_base + 0x00023CD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC54240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC54240, dll_base + 0x00024240);
		
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
			int32_t bScroll{};

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, bScroll);
			const auto original_result = original(&original_pItem, bScroll);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC542C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC542C0, dll_base + 0x000242C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC544A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC544A0, dll_base + 0x000244A0);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC54690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC54690, dll_base + 0x00024690);
		
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
			const auto moo_result = sut(&moo_pUnit, &moo_pItemDrop);
			const auto original_result = original(&original_pUnit, &original_pItemDrop);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC549F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC549F0, dll_base + 0x000249F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC54D00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC54D00, dll_base + 0x00024D00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC55060, dll_base + 0x00025060);
		
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
			int32_t nItemLevel{};
			int32_t nClassFirstSkillId{};
			int32_t a4{};

			// Call both implementations
			sut(&moo_pUnit, nItemLevel, nClassFirstSkillId, a4);
			original(&original_pUnit, nItemLevel, nClassFirstSkillId, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC55270, dll_base + 0x00025270);
		
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
}
