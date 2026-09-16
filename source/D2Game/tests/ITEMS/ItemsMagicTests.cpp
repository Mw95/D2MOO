#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int32_t bRequireSpawnableAffix{};
			int32_t bForceAffixRoll{};
			int32_t bAssignProperties{};
			int32_t bPrefixes{};
			int32_t nPreferredAffixIndex{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex);
			auto original_result = original(&original_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex);
			
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
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int32_t bRequireSpawnableAffix{};
			int32_t bForceAffixRoll{};
			int32_t bAssignProperties{};
			int32_t bPrefixes{};
			int32_t nPreferredAffixIndex{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex);
			auto original_result = original(&original_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex);
			
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
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int32_t bRequireSpawnableAffix{};
			int32_t bForceAffixRoll{};
			int32_t bAssignProperties{};
			int32_t bPrefixes{};
			int32_t nPreferredAffixIndex{};
			int32_t nAutoMagicGroup{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex, nAutoMagicGroup);
			auto original_result = original(&original_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex, nAutoMagicGroup);
			
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
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int32_t bRequireSpawnableAffix{};
			int32_t bForceAffixRoll{};
			int32_t bAssignProperties{};
			int32_t bPrefixes{};
			int32_t nPreferredAffixIndex{};
			int32_t nAutoMagicGroup{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex, nAutoMagicGroup);
			auto original_result = original(&original_pItem, bRequireSpawnableAffix, bForceAffixRoll, bAssignProperties, bPrefixes, nPreferredAffixIndex, nAutoMagicGroup);
			
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
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int32_t bPrefix{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pItem, bPrefix);
			auto original_result = original(&original_pItem, bPrefix);
			
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
			auto moo_result = sut(&moo_pItem, &moo_pItemDrop);
			auto original_result = original(&original_pItem, &original_pItemDrop);
			
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
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int32_t bPrefix{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pItem, bPrefix);
			auto original_result = original(&original_pItem, bPrefix);
			
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
			auto moo_result = sut(&moo_pItem, &moo_pItemDrop);
			auto original_result = original(&original_pItem, &original_pItemDrop);
			
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
			auto moo_result = sut(&moo_pItem, &moo_pItemDrop);
			auto original_result = original(&original_pItem, &original_pItemDrop);
			
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
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int32_t bScroll{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pItem, bScroll);
			auto original_result = original(&original_pItem, bScroll);
			
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
			auto moo_result = sut(&moo_pItem, &moo_pItemDrop);
			auto original_result = original(&original_pItem, &original_pItemDrop);
			
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
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			auto moo_result = sut(&moo_pItem);
			auto original_result = original(&original_pItem);
			
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
			auto moo_result = sut(&moo_pUnit, &moo_pItemDrop);
			auto original_result = original(&original_pUnit, &original_pItemDrop);
			
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
			auto moo_result = sut(&moo_pItem, &moo_pItemDrop);
			auto original_result = original(&original_pItem, &original_pItemDrop);
			
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
			auto moo_result = sut(&moo_pItem, &moo_pItemDrop);
			auto original_result = original(&original_pItem, &original_pItemDrop);
			
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
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nItemLevel{};
			int32_t nClassFirstSkillId{};
			int32_t a4{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

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
			auto moo_result = sut(&moo_pItem, &moo_pItemDrop);
			auto original_result = original(&original_pItem, &original_pItemDrop);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pItemDrop, original_pItemDrop, "Comparing pItemDrop");
		}
	}
}
