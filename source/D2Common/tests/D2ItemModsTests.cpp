#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <filesystem>
#include <iterator>
#include <memory>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Calc.h>
#include <D2DataTbls.h>
#include <D2Inventory.h>
#include <D2ItemMods.h>
#include <D2Items.h>
#include <D2StatList.h>
#include <D2States.h>
#include <Fog.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


// Builds the item code linker, which is required to look up items by their code (e.g. in sub_6FD92CF0)
template<class Fixture>
struct ItemsLinkerFixture : Fixture
{
	void* items_linker;
	D2TxtLinkStrc** original_items_linker;

	ItemsLinkerFixture()
	{
		const auto working_directory = std::filesystem::current_path();
		const auto d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

		items_linker = FOG_AllocLinker(__FILE__, __LINE__);

		for (auto i = 0; i < sgptDataTables->pItemDataTables.nItemsTxtRecordCount; ++i)
		{
			FOG_10215(items_linker, static_cast<int>(sgptDataTables->pItemDataTables.pItemsTxt[i].dwCode));
		}

		sgptDataTables->pItemsLinker = static_cast<D2TxtLinkStrc*>(items_linker);

		original_items_linker = reinterpret_cast<D2TxtLinkStrc**>(d2common_base + 0x000A9608 + 0x00000094);
		*original_items_linker = sgptDataTables->pItemsLinker;
	}

	~ItemsLinkerFixture()
	{
		sgptDataTables->pItemsLinker = nullptr;
		*original_items_linker = nullptr;

		FOG_FreeLinker(items_linker);
	}
};


// Sets the bit layout of charged skill layers (skill level and skill id) like the ItemStatCost.txt loader does
template<class Fixture>
struct ChargedSkillLayerFixture : Fixture
{
	int* original_stuff;
	int* original_shifted_stuff;

	ChargedSkillLayerFixture()
	{
		const auto working_directory = std::filesystem::current_path();
		const auto d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

		sgptDataTables->nStuff = 6;
		sgptDataTables->nShiftedStuff = (1 << sgptDataTables->nStuff) - 1;

		original_stuff = reinterpret_cast<int*>(d2common_base + 0x000A9608 + 0x00000C6C);
		*original_stuff = sgptDataTables->nStuff;

		original_shifted_stuff = reinterpret_cast<int*>(d2common_base + 0x000A9608 + 0x00000C70);
		*original_shifted_stuff = sgptDataTables->nShiftedStuff;
	}

	~ChargedSkillLayerFixture()
	{
		sgptDataTables->nStuff = 0;
		sgptDataTables->nShiftedStuff = 0;

		*original_stuff = 0;
		*original_shifted_stuff = 0;
	}
};


TEST_SUITE("D2ItemModsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92640 (#10844)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10844_ITEMMODS_First, dll_base + 0x00052640);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			int moo_pLayer{};
			int moo_pValue{};
			int original_pLayer{};
			int original_pValue{};
			int nDataBits = random_unsigned_integer();

			// Call both implementations
			sut(nDataBits, &moo_pLayer, &moo_pValue);
			original(nDataBits, &original_pLayer, &original_pValue);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pLayer, original_pLayer, "Comparing pLayer");
			MOO_CHECK_EQ(moo_pValue, original_pValue, "Comparing pValue");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92670 (#10846)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10846, dll_base + 0x00052670);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			int moo_a2{};
			int moo_a3{};
			int moo_a4{};
			int moo_a5{};
			int original_a2{};
			int original_a3{};
			int original_a4{};
			int original_a5{};
			int nDataBits = random_unsigned_integer();

			// Call both implementations
			sut(nDataBits, &moo_a2, &moo_a3, &moo_a4, &moo_a5);
			original(nDataBits, &original_a2, &original_a3, &original_a4, &original_a5);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
			MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
		}
	}

	TEST_CASE_FIXTURE(ChargedSkillLayerFixture<ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>>, "D2Common.0x6FD926C0 (#11293)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_GetItemCharges, dll_base + 0x000526C0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nChargedSkillId = static_cast<int>(random_unsigned_integer(0, skills_record_count - 1));
			const auto nChargedSkillLevel = static_cast<int>(random_unsigned_integer(1, 63));
			const auto nChargedLayer = (nChargedSkillLevel & sgptDataTables->nShiftedStuff) + (nChargedSkillId << sgptDataTables->nStuff);
			const auto nMaxCharges = static_cast<int>(random_unsigned_integer(1, 255));
			const auto nCharges = static_cast<int>(random_unsigned_integer(0, nMaxCharges));

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pStatList{};
			D2StatStrc moo_pStat{};
			int moo_pValue{};
			D2StatListStrc* moo_ppStatList{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pStatList{};
			D2StatStrc original_pStat{};
			int original_pValue{};
			D2StatListStrc* original_ppStatList{};
			// Either query the charged skill of the item or a (most likely) different one
			int nSkillId = random_unsigned_integer(0, 1) ? nChargedSkillId : static_cast<int>(random_unsigned_integer(0, skills_record_count));
			int nSkillLevel = random_unsigned_integer(0, 1) ? nChargedSkillLevel : static_cast<int>(random_unsigned_integer(0, 64));

			const auto setup_data = [nChargedLayer, nMaxCharges, nCharges](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pStatList,
				D2StatStrc& pStat,
				int& pValue,
				D2StatListStrc*& ppStatList
			) {
				pStat.nLayer = nChargedLayer;
				pStat.nStat = STAT_ITEM_CHARGED_SKILL;
				pStat.nValue = (nMaxCharges << 8) + nCharges;

				pStatList.dwOwnerType = UNIT_ITEM;
				pStatList.dwFlags = STATLIST_MAGIC;
				pStatList.Stats.pStat = &pStat;
				pStatList.Stats.nStatCount = 1;
				pStatList.Stats.nCapacity = 1;
				pStatList.pUnit = &pItem;
				pStatList.pParent = &pStatListEx;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pStatList;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pStatListEx = &pStatListEx;

				pValue = -1;
				ppStatList = &pStatList;
			};

			setup_data(moo_pItem, moo_pStatListEx, moo_pStatList, moo_pStat, moo_pValue, moo_ppStatList);
			setup_data(original_pItem, original_pStatListEx, original_pStatList, original_pStat, original_pValue, original_ppStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, nSkillId, nSkillLevel, &moo_pValue, &moo_ppStatList);
			const auto original_result = original(&original_pItem, nSkillId, nSkillLevel, &original_pValue, &original_ppStatList);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pValue, original_pValue, "Comparing pValue");
			MOO_CHECK_EQ(moo_ppStatList, original_ppStatList, "Comparing ppStatList");
		}
	}

	TEST_CASE_FIXTURE(ChargedSkillLayerFixture<ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>>, "D2Common.0x6FD927D0 (#10847)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_UpdateItemWithSkillCharges, dll_base + 0x000527D0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nChargedSkillId = static_cast<int>(random_unsigned_integer(0, skills_record_count - 1));
			const auto nChargedSkillLevel = static_cast<int>(random_unsigned_integer(1, 63));
			const auto nChargedLayer = (nChargedSkillLevel & sgptDataTables->nShiftedStuff) + (nChargedSkillId << sgptDataTables->nStuff);
			const auto nMaxCharges = static_cast<int>(random_unsigned_integer(1, 255));
			const auto nCharges = static_cast<int>(random_unsigned_integer(0, nMaxCharges));

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pStatList{};
			D2StatStrc moo_pStat{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pStatList{};
			D2StatStrc original_pStat{};
			// Either update the charged skill of the item or a (most likely) different one
			int nSkillId = random_unsigned_integer(0, 1) ? nChargedSkillId : static_cast<int>(random_unsigned_integer(0, skills_record_count));
			int nSkillLevel = random_unsigned_integer(0, 1) ? nChargedSkillLevel : static_cast<int>(random_unsigned_integer(0, 64));
			int a4 = random_unsigned_integer(0, 255);

			const auto setup_data = [nChargedLayer, nMaxCharges, nCharges](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pStatList,
				D2StatStrc& pStat
			) {
				pStat.nLayer = nChargedLayer;
				pStat.nStat = STAT_ITEM_CHARGED_SKILL;
				pStat.nValue = (nMaxCharges << 8) + nCharges;

				pStatList.dwOwnerType = UNIT_ITEM;
				pStatList.dwFlags = STATLIST_MAGIC;
				pStatList.Stats.pStat = &pStat;
				pStatList.Stats.nStatCount = 1;
				pStatList.Stats.nCapacity = 1;
				pStatList.pUnit = &pItem;
				pStatList.pParent = &pStatListEx;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pStatList;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx, moo_pStatList, moo_pStat);
			setup_data(original_pItem, original_pStatListEx, original_pStatList, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, nSkillId, nSkillLevel, a4);
			const auto original_result = original(&original_pItem, nSkillId, nSkillLevel, a4);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD928D0 (#10843)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_GetByTimeAdjustment, dll_base + 0x000528D0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			int moo_pItemModPeriodOfDay{};
			int moo_pItemModMin{};
			int moo_pItemModMax{};
			int original_pItemModPeriodOfDay{};
			int original_pItemModMin{};
			int original_pItemModMax{};
			int nAmount = random_unsigned_integer();
			int nPeriodOfDay = random_unsigned_integer();
			int nBaseTime = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(nAmount, nPeriodOfDay, nBaseTime, &moo_pItemModPeriodOfDay, &moo_pItemModMin, &moo_pItemModMax);
			const auto original_result = original(nAmount, nPeriodOfDay, nBaseTime, &original_pItemModPeriodOfDay, &original_pItemModMin, &original_pItemModMax);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItemModPeriodOfDay, original_pItemModPeriodOfDay, "Comparing pItemModPeriodOfDay");
			MOO_CHECK_EQ(moo_pItemModMin, original_pItemModMin, "Comparing pItemModMin");
			MOO_CHECK_EQ(moo_pItemModMax, original_pItemModMax, "Comparing pItemModMax");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD929A0 (#10849)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10849, dll_base + 0x000529A0);

		REPEAT_10();
		
		SUBCASE("")
		{
			int a1 = random_unsigned_integer();
			int a2 = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(a1, a2);
			const auto original_result = original(a1, a2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD929B0 (#10845)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10845, dll_base + 0x000529B0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			int moo_a2{};
			int moo_a3{};
			int moo_a4{};
			int original_a2{};
			int original_a3{};
			int original_a4{};
			int nDataBits = random_unsigned_integer();

			// Call both implementations
			sut(nDataBits, &moo_a2, &moo_a3, &moo_a4);
			original(nDataBits, &original_a2, &original_a3, &original_a4);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD929E0 (#10850)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10850, dll_base + 0x000529E0);
		
		REPEAT_10();

		SUBCASE("")
		{
			int a1 = random_unsigned_integer();
			int a2 = random_unsigned_integer();
			int a3 = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3);
			const auto original_result = original(a1, a2, a3);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92A00 (#10848)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10848, dll_base + 0x00052A00);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			int moo_pClass{};
			int moo_pTab{};
			int moo_pLevel{};
			int original_pClass{};
			int original_pTab{};
			int original_pLevel{};
			int nDataBits = random_unsigned_integer();

			// Call both implementations
			sut(nDataBits, &moo_pClass, &moo_pTab, &moo_pLevel);
			original(nDataBits, &original_pClass, &original_pTab, &original_pLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pClass, original_pClass, "Comparing pClass");
			MOO_CHECK_EQ(moo_pTab, original_pTab, "Comparing pTab");
			MOO_CHECK_EQ(moo_pLevel, original_pLevel, "Comparing pLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92A60 (#10851)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10851, dll_base + 0x00052A60);

		REPEAT_10();
		
		SUBCASE("")
		{
			int a1 = random_unsigned_integer();
			int a2 = random_unsigned_integer();
			int a3 = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3);
			const auto original_result = original(a1, a2, a3);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD92A80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD92A80, dll_base + 0x00052A80);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_ITEM_ARMOR_PERLEVEL, STAT_ITEM_HP_PERLEVEL, STAT_ITEM_MANA_PERLEVEL, STAT_ITEM_STRENGTH_PERLEVEL,
				STAT_ITEM_TOHIT_PERLEVEL, STAT_ITEM_RESIST_FIRE_PERLEVEL, STAT_ITEM_REPLENISH_DURABILITY,
			};

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD92C40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_GetOrCreateStatList, dll_base + 0x00052C40);

		SUBCASE("Creates new stat list for item")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nState = random_unsigned_integer(0, 1) ? STATE_RUNEWORD : 0;
			int fFilter = STATLIST_MAGIC;

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwOwnerId = 1;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = 1;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pItem, nState, fFilter);
			const auto original_result = original(nullptr, &original_pItem, nState, fFilter);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}

		SUBCASE("Creates new stat list for unit")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			int nState = random_unsigned_integer(0, 1) ? STATE_ITEMSET1 : 0;
			int fFilter = STATLIST_MAGIC;

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_PLAYER;
				pStatListEx.dwOwnerId = 2;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pUnit;

				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwUnitId = 2;
				pUnit.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nullptr, nState, fFilter);
			const auto original_result = original(&original_pUnit, nullptr, nState, fFilter);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Returns existing stat list")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pStatList{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pStatList{};
			int nState = random_unsigned_integer(0, 1) ? STATE_RUNEWORD : 0;
			int fFilter = STATLIST_MAGIC;

			const auto setup_data = [nState, fFilter](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pStatList
			) {
				pStatList.dwOwnerType = UNIT_ITEM;
				pStatList.dwOwnerId = 1;
				pStatList.dwFlags = fFilter;
				pStatList.dwStateNo = nState;
				pStatList.pUnit = &pItem;
				pStatList.pParent = &pStatListEx;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwOwnerId = 1;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pStatList;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwUnitId = 1;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx, moo_pStatList);
			setup_data(original_pItem, original_pStatListEx, original_pStatList);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pItem, nState, fFilter);
			const auto original_result = original(nullptr, &original_pItem, nState, fFilter);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			// Check specific values
			CHECK_EQ(moo_result, &moo_pStatList);
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD92CF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD92CF0, dll_base + 0x00052CF0);

		SUBCASE("")
		{
			const int stat_ids[] = {
				STAT_ITEM_ARMOR_PERCENT, STAT_ARMORCLASS, STAT_ITEM_MAXDAMAGE_PERCENT, STAT_MAXDAMAGE,
				STAT_ITEM_MINDAMAGE_PERCENT, STAT_MINDAMAGE, STAT_STRENGTH,
			};

			for (auto i = 0; i < items_record_count; ++i)
			{
				for (const auto stat_id : stat_ids)
				{
					// Input data
					D2UnitStrc moo_pItem{};
					D2StatListExStrc moo_pStatListEx{};
					D2UnitStrc original_pItem{};
					D2StatListExStrc original_pStatListEx{};
					int nStatId = stat_id;

					const auto setup_data = [i](
						D2UnitStrc& pItem,
						D2StatListExStrc& pStatListEx
					) {
						pStatListEx.dwOwnerType = UNIT_ITEM;
						pStatListEx.dwFlags = STATLIST_EXTENDED;
						pStatListEx.pOwner = &pItem;

						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = i;
						pItem.pStatListEx = &pStatListEx;
					};

					setup_data(moo_pItem, moo_pStatListEx);
					setup_data(original_pItem, original_pStatListEx);

					// Call both implementations
					sut(&moo_pItem, nStatId);
					original(&original_pItem, nStatId);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD92E80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD92E80, dll_base + 0x00052E80);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_ARMORCLASS, STAT_STRENGTH, STAT_MAXHP, STAT_MAXMANA, STAT_FIRERESIST, STAT_POISONMAXDAM, STAT_ITEM_GOLDBONUS,
			};
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 100);
			pProperty.nMax = random_unsigned_integer(0, 100);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD92EB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD92EB0, dll_base + 0x00052EB0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_ARMORCLASS, STAT_STRENGTH, STAT_MAXHP, STAT_MAXDAMAGE, STAT_MINDAMAGE,
				STAT_ITEM_ARMOR_PERCENT, STAT_ITEM_MAXDAMAGE_PERCENT, STAT_ITEM_MINDAMAGE_PERCENT, STAT_POISONMAXDAM,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 100);
			pProperty.nMax = random_unsigned_integer(0, 100);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int a7 = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, a7, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, a7, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD93170" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD93170, dll_base + 0x00053170);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemLevel = random_unsigned_integer(1, 99);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 6);
			int nStatId = STAT_ITEM_NUMSOCKETS;
			int nApplyType{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemLevel](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.dwItemLevel = nItemLevel;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD931C0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD931C0, dll_base + 0x000531C0);

		const auto nDurability = static_cast<int>(random_unsigned_integer(1, 250));
		const auto nMaxDurability = static_cast<int>(random_unsigned_integer(nDurability, 250));

		// The stat arrays are allocated with the game's allocator, since the function removes stats from them
		const auto setup_durability = [nDurability, nMaxDurability](
			D2UnitStrc& pItem,
			D2StatListExStrc& pStatListEx
		) {
			for (auto pStatsArray : { &pStatListEx.Stats, &pStatListEx.FullStats })
			{
				pStatsArray->pStat = static_cast<D2StatStrc*>(D2_CALLOC_POOL(nullptr, 2 * sizeof(D2StatStrc)));
				pStatsArray->pStat[0].nStat = STAT_DURABILITY;
				pStatsArray->pStat[0].nValue = nDurability;
				pStatsArray->pStat[1].nStat = STAT_MAXDURABILITY;
				pStatsArray->pStat[1].nValue = nMaxDurability;
				pStatsArray->nStatCount = 2;
				pStatsArray->nCapacity = 2;
			}

			pStatListEx.dwOwnerType = UNIT_ITEM;
			pStatListEx.dwFlags = STATLIST_EXTENDED;
			pStatListEx.pOwner = &pItem;

			pItem.dwUnitType = UNIT_ITEM;
			pItem.pStatListEx = &pStatListEx;
		};
		
		SUBCASE("Removes durability from item")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			int nStatId = -1;
			int nApplyType{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [&setup_durability](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				setup_durability(pItem, pStatListEx);
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}

		SUBCASE("Removes durability from a9")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_a9{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_a9{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			int nStatId = -1;
			int nApplyType{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [&setup_durability](
				D2UnitStrc& pItem,
				D2UnitStrc& a9,
				D2StatListExStrc& pStatListEx
			) {
				pItem.dwUnitType = UNIT_ITEM;

				setup_durability(a9, pStatListEx);
			};

			setup_data(moo_pItem, moo_a9, moo_pStatListEx);
			setup_data(original_pItem, original_a9, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, &moo_a9);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, &original_a9);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_a9, original_a9, "Comparing a9");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD93200")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD93200, dll_base + 0x00053200);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_ITEM_ARMOR_PERCENT, STAT_ITEM_MAXMANA_PERCENT, STAT_ITEM_MAXHP_PERCENT, STAT_ITEM_DAMAGETOMANA,
				STAT_ITEM_MAXDURABILITY_PERCENT, STAT_STAMINARECOVERYBONUS, STAT_MANARECOVERYBONUS, STAT_ITEM_TOHIT_PERCENT,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 100);
			pProperty.nMax = random_unsigned_integer(0, 100);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD93230")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD93230, dll_base + 0x00053230);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 100);
			pProperty.nMax = random_unsigned_integer(0, 100);
			int nStatId = -1;
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD93410")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD93410, dll_base + 0x00053410);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_MAXHP, STAT_MAXMANA, STAT_FIRERESIST, STAT_MAXFIRERESIST, STAT_MAXDAMAGE, STAT_MINDAMAGE,
				STAT_ITEM_MAXDAMAGE_PERCENT, STAT_ITEM_MINDAMAGE_PERCENT, STAT_ITEM_THROW_MINDAMAGE, STAT_ITEM_THROW_MAXDAMAGE,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			int a4 = random_unsigned_integer(0, 100);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int a7 = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, a4, nStatId, nApplyType, a7, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, a4, nStatId, nApplyType, a7, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD935B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD935B0, dll_base + 0x000535B0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 20);
			pProperty.nMax = random_unsigned_integer(0, 20);
			int nStatId = -1;
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD93790")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD93790, dll_base + 0x00053790);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nStatId = STAT_MINDAMAGE;
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD93A20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD93A20, dll_base + 0x00053A20);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nStatId = STAT_MAXDAMAGE;
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD93CB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD93CB0, dll_base + 0x00053CB0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 300);
			pProperty.nMax = random_unsigned_integer(0, 300);
			int nStatId = -1;
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD94060")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD94060, dll_base + 0x00054060);

		SUBCASE("")
		{
			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				// Input data
				const auto nValue = static_cast<int>(random_unsigned_integer(0, 2000)) - 1000;

				int moo_pValue{};
				int original_pValue{};
				int nStatId = i;

				const auto setup_data = [nValue](
					int& pValue
				) {
					pValue = nValue;
				};

				setup_data(moo_pValue);
				setup_data(original_pValue);

				// Call both implementations
				sut(nStatId, &moo_pValue);
				original(nStatId, &original_pValue);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pValue, original_pValue, "Comparing pValue");
			}
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD94160")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD94160, dll_base + 0x00054160);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 5);
			pProperty.nMax = random_unsigned_integer(0, 5);
			int nStatId = STAT_ITEM_ALLSKILLS;
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ChargedSkillLayerFixture<ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>>, "D2Common.0x6FD94190")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD94190, dll_base + 0x00054190);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nItemLevel = random_unsigned_integer(0, 99);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, skills_record_count);
			pProperty.nMin = static_cast<int>(random_unsigned_integer(0, 300)) - 30;
			pProperty.nMax = static_cast<int>(random_unsigned_integer(0, 40)) - 20;
			int nStatId = STAT_ITEM_CHARGED_SKILL;
			int nApplyType{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemLevel, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.dwItemLevel = nItemLevel;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD943C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD943C0, dll_base + 0x000543C0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_ITEM_ARMOR_BYTIME, STAT_ITEM_HP_BYTIME, STAT_ITEM_STRENGTH_BYTIME, STAT_ITEM_TOHIT_BYTIME,
				STAT_ITEM_RESIST_COLD_BYTIME, STAT_ITEM_FIND_MAGIC_BYTIME, STAT_ITEM_DEADLYSTRIKE_BYTIME,
			};

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			// The values have to be in the valid range, the function asserts otherwise
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 3);
			pProperty.nMin = static_cast<int>(random_unsigned_integer(0, 500)) - 250;
			pProperty.nMax = pProperty.nMin + static_cast<int>(random_unsigned_integer(0, 500));
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD944E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD944E0, dll_base + 0x000544E0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_FIREMINDAM, STAT_LIGHTMINDAM, STAT_MAGICMINDAM, STAT_ITEM_THROW_MINDAMAGE, STAT_MINDAMAGE,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = pProperty.nMin + random_unsigned_integer(0, 50);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD94AB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD94AB0, dll_base + 0x00054AB0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_COLDMINDAM, STAT_POISONMINDAM,
			};

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 250);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = pProperty.nMin + random_unsigned_integer(0, 50);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FD94E80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD94E80, dll_base + 0x00054E80);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, skills_record_count);
			pProperty.nMin = random_unsigned_integer(0, 5);
			pProperty.nMax = random_unsigned_integer(0, 5);
			int nStatId = STAT_ITEM_SINGLESKILL;
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD94F70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD94F70, dll_base + 0x00054F70);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 5);
			pProperty.nMax = random_unsigned_integer(0, 5);
			int nStatId = STAT_ITEM_ELEMSKILL;
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD95050")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD95050, dll_base + 0x00055050);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_ITEM_ADDCLASSSKILLS, STAT_UNSENTPARAM1, STAT_ITEM_ADDEXPERIENCE, STAT_ITEM_HEALAFTERKILL,
				STAT_ITEM_REDUCEDPRICES, STAT_ATTACK_VS_MONTYPE, STAT_DAMAGE_VS_MONTYPE,
			};
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 25);
			pProperty.nMax = random_unsigned_integer(0, 25);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD95200")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD95200, dll_base + 0x00055200);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			int nType = random_unsigned_integer(0, 7);
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 100);
			pProperty.nMin = random_unsigned_integer(0, 100);
			pProperty.nMax = random_unsigned_integer(0, 100);
			int nStatId = random_unsigned_integer(0, 300);
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, nullptr, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, nullptr, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD95210")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD95210, dll_base + 0x00055210);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_ITEM_FASTERATTACKRATE, STAT_ITEM_FASTERMOVEVELOCITY, STAT_ITEM_FASTERGETHITRATE,
				STAT_ITEM_FASTERBLOCKRATE, STAT_ITEM_FASTERCASTRATE,
			};
			const auto nItemFormat = random_unsigned_integer(0, 1);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nApplyType = random_unsigned_integer(0, 1);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemFormat, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nStatId, nApplyType, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<PropertiesTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FD95430 (#10855)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_AssignProperty, dll_base + 0x00055430);

		// Items with item format 0 use a fixed size property table, so only the properties covered by it are used.
		// Layer and values are restricted to ranges that are valid for all properties (e.g. by time properties assert on them).
		const auto nPropertyCount = std::min(properties_record_count, 246);
		const auto make_random_property = [nPropertyCount]()
		{
			D2PropertyStrc pProperty{};
			pProperty.nProperty = random_unsigned_integer(0, 4) ? static_cast<int>(random_unsigned_integer(0, nPropertyCount - 1)) : -1;
			pProperty.nLayer = random_unsigned_integer(0, 3);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = pProperty.nMin + random_unsigned_integer(0, 50);
			return pProperty;
		};

		const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
		const auto nItemFormat = random_unsigned_integer(0, 1) ? 101 : 0;
		const auto nItemLevel = random_unsigned_integer(1, 99);
		const auto nLowSeed = random_unsigned_integer();

		const auto setup_item = [nClassId, nItemFormat, nItemLevel, nLowSeed](
			D2UnitStrc& pItem,
			D2ItemDataStrc& pItemData,
			D2StatListExStrc& pStatListEx
		) {
			pItemData.pSeed.nLowSeed = nLowSeed;
			pItemData.pSeed.nHighSeed = 666;
			pItemData.dwItemLevel = nItemLevel;
			pItemData.wItemFormat = nItemFormat;

			pStatListEx.dwOwnerType = UNIT_ITEM;
			pStatListEx.dwFlags = STATLIST_EXTENDED;
			pStatListEx.pOwner = &pItem;

			pItem.dwUnitType = UNIT_ITEM;
			pItem.dwClassId = nClassId;
			pItem.pItemData = &pItemData;
			pItem.pStatListEx = &pStatListEx;
		};

		REPEAT_10();

		SUBCASE("Magic affix")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = PROPMODE_AFFIX;
			D2MagicAffixTxt pMods{};
			for (auto& pProperty : pMods.pProperties)
			{
				pProperty = make_random_property();
			}
			int nPropSet{};
			int nApplyType{};

			const auto setup_data = [&setup_item](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				setup_item(pItem, pItemData, pStatListEx);
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			sut(nType, nullptr, &moo_pItem, &pMods, nPropSet, nApplyType);
			original(nType, nullptr, &original_pItem, &pMods, nPropSet, nApplyType);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}

		SUBCASE("Gem")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = PROPMODE_GEM;
			D2GemsTxt pMods{};
			for (auto& pPropertySet : pMods.pProperties)
			{
				for (auto& pProperty : pPropertySet)
				{
					pProperty = make_random_property();
				}
			}
			int nPropSet = random_unsigned_integer(0, 2);
			int nApplyType{};

			const auto setup_data = [&setup_item](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				setup_item(pItem, pItemData, pStatListEx);
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			sut(nType, nullptr, &moo_pItem, &pMods, nPropSet, nApplyType);
			original(nType, nullptr, &original_pItem, &pMods, nPropSet, nApplyType);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<PropertiesTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FD95810" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD95810, dll_base + 0x00055810);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemFormat = random_unsigned_integer(0, 1) ? 101 : 0;
			const auto nItemLevel = random_unsigned_integer(1, 99);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = PROPMODE_AFFIX;
			int nIndex{};
			int nPropSet{};
			int nApplyType{};
			// Items with item format 0 use a fixed size property table, so only the properties covered by it are used.
			// Layer and values are restricted to ranges that are valid for all properties (e.g. by time properties assert on them).
			D2PropertyStrc pProperty{};
			pProperty.nProperty = random_unsigned_integer(0, std::min(properties_record_count, 246) - 1);
			pProperty.nLayer = random_unsigned_integer(0, 3);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = pProperty.nMin + random_unsigned_integer(0, 50);
			int nState{};
			int fStatlist = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemFormat, nItemLevel, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.dwItemLevel = nItemLevel;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			sut(nType, nullptr, &moo_pItem, nullptr, nIndex, nPropSet, nApplyType, &pProperty, nState, fStatlist, nullptr);
			original(nType, nullptr, &original_pItem, nullptr, nIndex, nPropSet, nApplyType, &pProperty, nState, fStatlist, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD958D0 (#10865)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_ApplyEthereality, dll_base + 0x000558D0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int stat_ids[] = {
				STAT_MINDAMAGE, STAT_MAXDAMAGE, STAT_SECONDARY_MINDAMAGE, STAT_SECONDARY_MAXDAMAGE,
				STAT_ARMORCLASS, STAT_ITEM_THROW_MINDAMAGE, STAT_ITEM_THROW_MAXDAMAGE,
			};
			std::array<int, 7> stat_values{};
			for (auto& nValue : stat_values)
			{
				nValue = random_unsigned_integer(1, 200);
			}
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};

			// The base stats are sorted by their stat id and allocated with the game's allocator, since the function modifies them
			const auto setup_data = [&stat_ids, &stat_values, nClassId](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				const auto nStatCount = static_cast<uint16_t>(std::size(stat_ids));
				pStatListEx.Stats.pStat = static_cast<D2StatStrc*>(D2_CALLOC_POOL(nullptr, nStatCount * sizeof(D2StatStrc)));
				pStatListEx.Stats.nStatCount = nStatCount;
				pStatListEx.Stats.nCapacity = nStatCount;
				for (auto i = 0; i < nStatCount; ++i)
				{
					pStatListEx.Stats.pStat[i].nStat = stat_ids[i];
					pStatListEx.Stats.pStat[i].nValue = stat_values[i];
				}

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			sut(&moo_pItem);
			original(&original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<PropertiesTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FD959F0 (#10867)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_UpdateRuneword, dll_base + 0x000559F0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nRuneClassId = static_cast<int>(random_unsigned_integer(1, items_record_count - 1));
			const auto nItemLevel = random_unsigned_integer(1, 99);
			const auto nLowSeed = random_unsigned_integer();

			// A runeword which consists of the single rune socketed into the item
			D2RunesTxt pRunesTxtRecord{};
			pRunesTxtRecord.nComplete = 1;
			pRunesTxtRecord.nRune[0] = nRuneClassId;
			pRunesTxtRecord.wIType[0] = items_txt[nClassId].wType[0];
			for (auto& pProperty : pRunesTxtRecord.pProperties)
			{
				pProperty.nProperty = -1;
			}
			const auto nProperties = random_unsigned_integer(0, std::size(pRunesTxtRecord.pProperties));
			for (auto i = 0u; i < nProperties; ++i)
			{
				// Layer and values are restricted to ranges that are valid for all properties
				pRunesTxtRecord.pProperties[i].nProperty = random_unsigned_integer(0, properties_record_count - 1);
				pRunesTxtRecord.pProperties[i].nLayer = random_unsigned_integer(0, 3);
				pRunesTxtRecord.pProperties[i].nMin = random_unsigned_integer(0, 50);
				pRunesTxtRecord.pProperties[i].nMax = pRunesTxtRecord.pProperties[i].nMin + random_unsigned_integer(0, 50);
			}

			sgptDataTables->pRuneDataTables.nRunesTxtRecordCount = 1;
			sgptDataTables->pRuneDataTables.pRunesTxt = &pRunesTxtRecord;

			const auto original_runes_record_count = reinterpret_cast<int*>(dll_base + 0x000A9608 + 0x00000EDC);
			const auto original_runes = reinterpret_cast<D2RunesTxt**>(dll_base + 0x000A9608 + 0x00000EE0);
			*original_runes_record_count = 1;
			*original_runes = &pRunesTxtRecord;

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pRune{};
			D2ItemDataStrc moo_pRuneData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pRune{};
			D2ItemDataStrc original_pRuneData{};
			int nUnused{};

			const auto setup_data = [nClassId, nRuneClassId, nItemLevel, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx,
				D2InventoryStrc& pInventory,
				D2UnitStrc& pRune,
				D2ItemDataStrc& pRuneData
			) {
				pRuneData.dwQualityNo = ITEMQUAL_NORMAL;
				pRuneData.pExtraData.pParentInv = &pInventory;

				pRune.dwUnitType = UNIT_ITEM;
				pRune.dwClassId = nRuneClassId;
				pRune.pItemData = &pRuneData;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pItem;
				pInventory.pFirstItem = &pRune;
				pInventory.pLastItem = &pRune;
				pInventory.dwItemCount = 1;

				pItemData.dwQualityNo = ITEMQUAL_NORMAL;
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.dwItemLevel = nItemLevel;
				pItemData.wItemFormat = 101;

				// The number of sockets is allocated with the game's allocator, since the stats of the runeword get added to it
				pStatListEx.FullStats.pStat = static_cast<D2StatStrc*>(D2_CALLOC_POOL(nullptr, sizeof(D2StatStrc)));
				pStatListEx.FullStats.pStat[0].nStat = STAT_ITEM_NUMSOCKETS;
				pStatListEx.FullStats.pStat[0].nValue = 1;
				pStatListEx.FullStats.nStatCount = 1;
				pStatListEx.FullStats.nCapacity = 1;
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
				pItem.pInventory = &pInventory;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pInventory, moo_pRune, moo_pRuneData);
			setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pInventory, original_pRune, original_pRuneData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pItem, nUnused);
			const auto original_result = original(&original_pItem, &original_pItem, nUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			sgptDataTables->pRuneDataTables.nRunesTxtRecordCount = 0;
			sgptDataTables->pRuneDataTables.pRunesTxt = nullptr;
			*original_runes_record_count = 0;
			*original_runes = nullptr;
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<PropertiesTxtFixture<SkillsTxtFixture<SetItemsTxtFixture<SetsTxtFixture<NoopFixture>>>>>>>>, "D2Common.0x6FD95A70" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_UpdateFullSetBoni, dll_base + 0x00055A70);

		constexpr auto MAX_SET_ITEMS = 6;
		using SetItemUnits = std::array<D2UnitStrc, MAX_SET_ITEMS>;
		using SetItemData = std::array<D2ItemDataStrc, MAX_SET_ITEMS>;

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto nSetItemId = static_cast<int>(random_unsigned_integer(0, setitems_record_count - 1));
			const auto nSetId = setitems_txt[nSetItemId].nSetId;

			// Collect all items of the set, a random number of them is equipped
			std::array<int, MAX_SET_ITEMS> set_item_ids{};
			auto nSetItems = 0;
			set_item_ids[nSetItems++] = nSetItemId;
			for (auto i = 0; i < setitems_record_count && nSetItems < MAX_SET_ITEMS; ++i)
			{
				if (i != nSetItemId && setitems_txt[i].nSetId == nSetId)
				{
					set_item_ids[nSetItems++] = i;
				}
			}
			const auto nEquippedItems = static_cast<int>(random_unsigned_integer(1, nSetItems));

			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemLevel = random_unsigned_integer(1, 99);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pUnitStatListEx{};
			D2InventoryStrc moo_pInventory{};
			SetItemUnits moo_pItems{};
			SetItemData moo_pItemData{};
			D2StatListExStrc moo_pItemStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pUnitStatListEx{};
			D2InventoryStrc original_pInventory{};
			SetItemUnits original_pItems{};
			SetItemData original_pItemData{};
			D2StatListExStrc original_pItemStatListEx{};
			int nState = random_unsigned_integer(0, 3) ? STATE_ITEMFULLSET : 0;

			const auto setup_data = [&set_item_ids, nEquippedItems, nClassId, nItemLevel, nLowSeed](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pUnitStatListEx,
				D2InventoryStrc& pInventory,
				SetItemUnits& pItems,
				SetItemData& pItemData,
				D2StatListExStrc& pItemStatListEx
			) {
				for (auto i = 0; i < nEquippedItems; ++i)
				{
					pItemData[i].dwQualityNo = ITEMQUAL_SET;
					pItemData[i].pSeed.nLowSeed = nLowSeed + i;
					pItemData[i].pSeed.nHighSeed = 666;
					pItemData[i].dwFileIndex = set_item_ids[i];
					pItemData[i].dwItemLevel = nItemLevel;
					pItemData[i].wItemFormat = 101;
					pItemData[i].pExtraData.pParentInv = &pInventory;
					pItemData[i].pExtraData.pPreviousItem = i > 0 ? &pItems[i - 1] : nullptr;
					pItemData[i].pExtraData.pNextItem = i + 1 < nEquippedItems ? &pItems[i + 1] : nullptr;
					pItemData[i].pExtraData.nNodePosOther = NODEPAGE_EQUIP;

					pItems[i].dwUnitType = UNIT_ITEM;
					pItems[i].dwClassId = nClassId;
					pItems[i].pItemData = &pItemData[i];
				}

				pItemStatListEx.dwOwnerType = UNIT_ITEM;
				pItemStatListEx.dwFlags = STATLIST_EXTENDED;
				pItemStatListEx.pOwner = &pItems[0];
				pItems[0].pStatListEx = &pItemStatListEx;

				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pUnit;
				pInventory.pFirstItem = &pItems[0];
				pInventory.pLastItem = &pItems[nEquippedItems - 1];
				pInventory.dwItemCount = nEquippedItems;

				pUnitStatListEx.dwOwnerType = UNIT_PLAYER;
				pUnitStatListEx.dwFlags = STATLIST_EXTENDED;
				pUnitStatListEx.pOwner = &pUnit;

				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pStatListEx = &pUnitStatListEx;
				pUnit.pInventory = &pInventory;
			};

			setup_data(moo_pUnit, moo_pUnitStatListEx, moo_pInventory, moo_pItems, moo_pItemData, moo_pItemStatListEx);
			setup_data(original_pUnit, original_pUnitStatListEx, original_pInventory, original_pItems, original_pItemData, original_pItemStatListEx);

			// Call both implementations
			sut(&moo_pUnit, &moo_pItems[0], nState);
			original(&original_pUnit, &original_pItems[0], nState);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pItems[0], original_pItems[0], "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<PropertiesTxtFixture<NoopFixture>>>, "D2Common.0x6FD95BE0 (#10859)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_CanItemHaveMagicAffix, dll_base + 0x00055BE0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			D2MagicAffixTxt pMagicAffixTxtRecord{};
			pMagicAffixTxtRecord.pProperties[0].nProperty = random_unsigned_integer(0, properties_record_count - 1);
			const auto nITypes = random_unsigned_integer(1, std::size(pMagicAffixTxtRecord.wIType));
			for (auto i = 0u; i < nITypes; ++i)
			{
				pMagicAffixTxtRecord.wIType[i] = random_unsigned_integer(1, itemtypes_record_count - 1);
			}
			const auto nETypes = random_unsigned_integer(0, std::size(pMagicAffixTxtRecord.wEType));
			for (auto i = 0u; i < nETypes; ++i)
			{
				pMagicAffixTxtRecord.wEType[i] = random_unsigned_integer(1, itemtypes_record_count - 1);
			}

			for (auto i = 0; i < items_record_count; ++i)
			{
				const auto nItemFormat = random_unsigned_integer(0, 1) ? 101 : 1;
				const auto nItemLevel = random_unsigned_integer(1, 99);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i, nItemFormat, nItemLevel](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItemData.dwItemLevel = nItemLevel;
					pItemData.wItemFormat = nItemFormat;

					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &pMagicAffixTxtRecord);
				const auto original_result = original(&original_pItem, &pMagicAffixTxtRecord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}

	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD95CC0 (#10860)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_CanItemHaveRareAffix, dll_base + 0x00055CC0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nVersion = random_unsigned_integer(0, 1) ? 100 : 0;
			std::array<uint16_t, 7> itypes{};
			const auto nITypes = random_unsigned_integer(1, itypes.size());
			for (auto i = 0u; i < nITypes; ++i)
			{
				itypes[i] = random_unsigned_integer(1, itemtypes_record_count - 1);
			}
			std::array<uint16_t, 4> etypes{};
			const auto nETypes = random_unsigned_integer(0, etypes.size());
			for (auto i = 0u; i < nETypes; ++i)
			{
				etypes[i] = random_unsigned_integer(1, itemtypes_record_count - 1);
			}

			for (auto i = 0; i < items_record_count; ++i)
			{
				const auto nItemFormat = random_unsigned_integer(0, 1) ? 101 : 1;

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2RareAffixTxt moo_pRareAffixTxtRecord{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2RareAffixTxt original_pRareAffixTxtRecord{};

				const auto setup_data = [i, nItemFormat, nVersion, &itypes, &etypes](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2RareAffixTxt& pRareAffixTxtRecord
				) {
					pRareAffixTxtRecord.wVersion = nVersion;
					std::copy(itypes.begin(), itypes.end(), std::begin(pRareAffixTxtRecord.wIType));
					std::copy(etypes.begin(), etypes.end(), std::begin(pRareAffixTxtRecord.wEType));

					pItemData.wItemFormat = nItemFormat;

					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pRareAffixTxtRecord);
				setup_data(original_pItem, original_pItemData, original_pRareAffixTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &moo_pRareAffixTxtRecord);
				const auto original_result = original(&original_pItem, &original_pRareAffixTxtRecord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pRareAffixTxtRecord, original_pRareAffixTxtRecord, "Comparing pRareAffixTxtRecord");
			}
		}
	}

	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD95D60 (#10861)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_CanItemBeHighQuality, dll_base + 0x00055D60);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			std::array<uint8_t, 10> flags{};
			for (auto& nFlag : flags)
			{
				nFlag = random_unsigned_integer(0, 1);
			}

			for (auto i = 0; i < items_record_count; ++i)
			{
				D2UnitStrc moo_pItem{};
				D2QualityItemsTxt moo_pQualityItemsTxtRecord{};
				D2UnitStrc original_pItem{};
				D2QualityItemsTxt original_pQualityItemsTxtRecord{};

				const auto setup_data = [i, &flags](
					D2UnitStrc& pItem,
					D2QualityItemsTxt& pQualityItemsTxtRecord
				) {
					pQualityItemsTxtRecord.nArmor = flags[0];
					pQualityItemsTxtRecord.nWeapon = flags[1];
					pQualityItemsTxtRecord.nShield = flags[2];
					pQualityItemsTxtRecord.nScepter = flags[3];
					pQualityItemsTxtRecord.nWand = flags[4];
					pQualityItemsTxtRecord.nStaff = flags[5];
					pQualityItemsTxtRecord.nBow = flags[6];
					pQualityItemsTxtRecord.nBoots = flags[7];
					pQualityItemsTxtRecord.nGloves = flags[8];
					pQualityItemsTxtRecord.nBelt = flags[9];

					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem, moo_pQualityItemsTxtRecord);
				setup_data(original_pItem, original_pQualityItemsTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &moo_pQualityItemsTxtRecord);
				const auto original_result = original(&original_pItem, &original_pQualityItemsTxtRecord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pQualityItemsTxtRecord, original_pQualityItemsTxtRecord, "Comparing pQualityItemsTxtRecord");
			}
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD95E90 (#10862)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_SetRandomElixirFileIndex, dll_base + 0x00055E90);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			sut(&moo_pItem);
			original(&original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<PropertiesTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FD95F90 (#10868)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_AddCraftPropertyList, dll_base + 0x00055F90);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemFormat = random_unsigned_integer(0, 1) ? 101 : 0;
			const auto nItemLevel = random_unsigned_integer(1, 99);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2PropertyStrc moo_pProperty{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			D2PropertyStrc original_pProperty{};
			// Items with item format 0 use a fixed size property table, so only the properties covered by it are used.
			// Layer and values are restricted to ranges that are valid for all properties (e.g. by time properties assert on them).
			const auto nProperty = static_cast<int>(random_unsigned_integer(0, std::min(properties_record_count, 246) - 1));
			const auto nLayer = static_cast<int>(random_unsigned_integer(0, 3));
			const auto nMin = static_cast<int>(random_unsigned_integer(0, 50));
			const auto nMax = nMin + static_cast<int>(random_unsigned_integer(0, 50));
			int nUnused{};

			const auto setup_data = [nClassId, nItemFormat, nItemLevel, nLowSeed, nProperty, nLayer, nMin, nMax](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx,
				D2PropertyStrc& pProperty
			) {
				pProperty.nProperty = nProperty;
				pProperty.nLayer = nLayer;
				pProperty.nMin = nMin;
				pProperty.nMax = nMax;

				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.dwItemLevel = nItemLevel;
				pItemData.wItemFormat = nItemFormat;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pProperty);
			setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pProperty);

			// Call both implementations
			sut(&moo_pItem, &moo_pProperty, nUnused);
			original(&original_pItem, &original_pProperty, nUnused);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pProperty, original_pProperty, "Comparing pProperty");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD95FC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc01, dll_base + 0x00055FC0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_STRENGTH, STAT_ARMORCLASS, STAT_MAXDAMAGE, STAT_ITEM_ARMOR_PERCENT, STAT_FIRERESIST, STAT_POISONMAXDAM,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD96110")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_AddPropertyToItemStatList, dll_base + 0x00056110);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_STRENGTH, STAT_MAXHP, STAT_FIRERESIST, STAT_POISONMAXDAM, STAT_ITEM_SINGLESKILL, STAT_ITEM_ADDCLASSSKILLS,
			};

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer = random_unsigned_integer(0, 6);
			int nValue = random_unsigned_integer(0, 50);
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD96210")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc02, dll_base + 0x00056210);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_STRENGTH, STAT_ARMORCLASS, STAT_MAXDAMAGE, STAT_MINDAMAGE, STAT_ITEM_ARMOR_PERCENT, STAT_POISONMAXDAM,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD96350")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc03, dll_base + 0x00056350);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_STRENGTH, STAT_ARMORCLASS, STAT_MAXDAMAGE, STAT_ITEM_ARMOR_PERCENT, STAT_FIRERESIST, STAT_POISONMAXDAM,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 50));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD964A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc04, dll_base + 0x000564A0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_STRENGTH, STAT_ARMORCLASS, STAT_MAXDAMAGE, STAT_MINDAMAGE, STAT_ITEM_ARMOR_PERCENT, STAT_POISONMAXDAM,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 50));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD965F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc05, dll_base + 0x000565F0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = STAT_MINDAMAGE;
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 50));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD96880")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc06, dll_base + 0x00056880);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = STAT_MAXDAMAGE;
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 50));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD96B00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc07, dll_base + 0x00056B00);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = STAT_ITEM_MAXDAMAGE_PERCENT;
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 300));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD96DA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc08, dll_base + 0x00056DA0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_STRENGTH, STAT_MAXHP, STAT_ITEM_FASTERCASTRATE, STAT_POISONMAXDAM,
			};
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 50));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FD96EE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc09, dll_base + 0x00056EE0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_ITEM_SINGLESKILL, STAT_ITEM_NONCLASSSKILL, STAT_ITEM_AURA,
			};
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, skills_record_count);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 20));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD97040")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc24, dll_base + 0x00057040);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_ITEM_SINGLESKILL, STAT_ITEM_ELEMSKILL, STAT_ITEM_ADDCLASSSKILLS,
			};
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 20));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD97180" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc10, dll_base + 0x00057180);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = STAT_ITEM_ADDSKILL_TAB;
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 5));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FD972E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc11, dll_base + 0x000572E0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_ITEM_SKILLONATTACK, STAT_ITEM_SKILLONKILL, STAT_ITEM_SKILLONHIT, STAT_ITEM_SKILLONGETHIT,
			};
			const auto nItemLevel = random_unsigned_integer(0, 99);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, skills_record_count);
			pProperty.nMin = static_cast<int>(random_unsigned_integer(0, 105)) - 5;
			pProperty.nMax = static_cast<int>(random_unsigned_integer(0, 40)) - 20;
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemLevel, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.dwItemLevel = nItemLevel;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD97430")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc14, dll_base + 0x00057430);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemLevel = random_unsigned_integer(0, 99);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 6);
			pProperty.nMin = random_unsigned_integer(0, 6);
			pProperty.nMax = random_unsigned_integer(0, 6);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = STAT_ITEM_NUMSOCKETS;
			int nLayer{};
			int nValue = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 6));
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemLevel, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.dwItemLevel = nItemLevel;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ChargedSkillLayerFixture<ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>>, "D2Common.0x6FD975F0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc19, dll_base + 0x000575F0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nItemLevel = random_unsigned_integer(0, 99);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, skills_record_count);
			pProperty.nMin = static_cast<int>(random_unsigned_integer(0, 300)) - 30;
			pProperty.nMax = static_cast<int>(random_unsigned_integer(0, 40)) - 20;
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = STAT_ITEM_CHARGED_SKILL;
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nItemLevel, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.dwItemLevel = nItemLevel;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD97830")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc18, dll_base + 0x00057830);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_ITEM_ARMOR_BYTIME, STAT_ITEM_HP_BYTIME, STAT_ITEM_STRENGTH_BYTIME, STAT_ITEM_RESIST_COLD_BYTIME, STAT_ITEM_FIND_MAGIC_BYTIME,
			};

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = static_cast<int>(random_unsigned_integer(0, 6)) - 1;
			pProperty.nMin = static_cast<int>(random_unsigned_integer(0, 1400)) - 300;
			pProperty.nMax = static_cast<int>(random_unsigned_integer(0, 1400)) - 300;
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD97920")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc15, dll_base + 0x00057920);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_MINDAMAGE, STAT_FIREMINDAM, STAT_STRENGTH,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD979A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc16, dll_base + 0x000579A0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_MAXDAMAGE, STAT_FIREMAXDAM, STAT_STRENGTH,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD97A20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc17, dll_base + 0x00057A20);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_MAXDAMAGE, STAT_ITEM_MAXDAMAGE_PERLEVEL, STAT_ITEM_ARMOR_PERLEVEL,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 1) ? 0 : static_cast<int>(random_unsigned_integer(1, 50));
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD97BA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc20, dll_base + 0x00057BA0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = STAT_ITEM_INDESCTRUCTIBLE;
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx
			) {
				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pStatListEx);
			setup_data(original_pItem, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD97C20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc21, dll_base + 0x00057C20);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_ITEM_ADDCLASSSKILLS, STAT_ITEM_ELEMSKILL, STAT_ITEM_SINGLESKILL,
			};
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer = random_unsigned_integer(0, 6);
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD97D50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc22, dll_base + 0x00057D50);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_ITEM_ADDCLASSSKILLS, STAT_ITEM_ELEMSKILL, STAT_ITEM_SINGLESKILL,
			};
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD97E80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc12, dll_base + 0x00057E80);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_ITEM_ADDCLASSSKILLS, STAT_ITEM_ELEMSKILL, STAT_ITEM_SINGLESKILL,
			};
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 50);
			pProperty.nMin = random_unsigned_integer(0, 6);
			pProperty.nMax = random_unsigned_integer(0, 6);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FD97FB0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc13, dll_base + 0x00057FB0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const short stat_ids[] = {
				STAT_MAXDURABILITY, STAT_ITEM_MAXDURABILITY_PERCENT,
			};
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(0, 1);
			D2PropertyStrc pProperty{};
			pProperty.nLayer = random_unsigned_integer(0, 20);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = random_unsigned_integer(0, 50);
			int nSet = random_unsigned_integer(0, 1);
			short nStatId = stat_ids[random_unsigned_integer(0, std::size(stat_ids) - 1)];
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>, "D2Common.0x6FD98120")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_PropertyFunc23, dll_base + 0x00058120);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			std::array<int, 8> stat_ids = {
				STAT_MINDAMAGE, STAT_MAXDAMAGE, STAT_SECONDARY_MINDAMAGE, STAT_SECONDARY_MAXDAMAGE,
				STAT_ARMORCLASS, STAT_MAXDURABILITY, STAT_ITEM_THROW_MINDAMAGE, STAT_ITEM_THROW_MAXDAMAGE,
			};
			std::sort(stat_ids.begin(), stat_ids.end());
			std::array<int, 8> stat_values{};
			for (auto& nValue : stat_values)
			{
				nValue = random_unsigned_integer(0, 200);
			}
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto bEthereal = random_unsigned_integer(0, 1);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType{};
			D2PropertyStrc pProperty{};
			int nSet{};
			short nStatId{};
			int nLayer{};
			int nValue{};
			int nState{};
			int fStatList = STATLIST_MAGIC;

			// The stats are sorted by their stat id and allocated with the game's allocator, since the function modifies them
			const auto setup_data = [&stat_ids, &stat_values, nClassId, bEthereal](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				const auto nStatCount = static_cast<uint16_t>(stat_ids.size());
				for (auto pStatsArray : { &pStatListEx.Stats, &pStatListEx.FullStats })
				{
					pStatsArray->pStat = static_cast<D2StatStrc*>(D2_CALLOC_POOL(nullptr, nStatCount * sizeof(D2StatStrc)));
					pStatsArray->nStatCount = nStatCount;
					pStatsArray->nCapacity = nStatCount;
					for (auto i = 0; i < nStatCount; ++i)
					{
						pStatsArray->pStat[i].nStat = stat_ids[i];
						pStatsArray->pStat[i].nValue = stat_values[i];
					}
				}

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItemData.dwItemFlags = bEthereal ? IFLAG_ETHEREAL : 0;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(nType, nullptr, &moo_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);
			const auto original_result = original(nType, nullptr, &original_pItem, &pProperty, nSet, nStatId, nLayer, nValue, nState, fStatList, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemStatCostTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<PropertiesTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FD98160 (#11292)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_11292_ItemAssignProperty, dll_base + 0x00058160);

		REPEAT_20();

		SUBCASE("")
		{
			// Input data
			const auto nClassId = static_cast<int>(random_unsigned_integer(0, items_record_count - 1));
			const auto nItemLevel = random_unsigned_integer(1, 99);
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2StatListExStrc original_pStatListEx{};
			int nType = random_unsigned_integer(PROPMODE_AFFIX, PROPMODE_UNUSED);
			int nIndex{};
			int nPropSet{};
			// Layer and values are restricted to ranges that are valid for all properties
			D2PropertyStrc pProperty{};
			pProperty.nProperty = static_cast<int>(random_unsigned_integer(0, properties_record_count)) - 1;
			pProperty.nLayer = random_unsigned_integer(0, 3);
			pProperty.nMin = random_unsigned_integer(0, 50);
			pProperty.nMax = pProperty.nMin + random_unsigned_integer(0, 50);
			int nState{};
			int fStatlist = STATLIST_MAGIC;

			const auto setup_data = [nClassId, nItemLevel, nLowSeed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				D2StatListExStrc& pStatListEx
			) {
				pItemData.pSeed.nLowSeed = nLowSeed;
				pItemData.pSeed.nHighSeed = 666;
				pItemData.dwItemLevel = nItemLevel;
				pItemData.wItemFormat = 101;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.pOwner = &pItem;

				pItem.dwUnitType = UNIT_ITEM;
				pItem.dwClassId = nClassId;
				pItem.pItemData = &pItemData;
				pItem.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pStatListEx);
			setup_data(original_pItem, original_pItemData, original_pStatListEx);

			// Call both implementations
			sut(nType, nullptr, &moo_pItem, nullptr, nIndex, nPropSet, &pProperty, nState, fStatlist, nullptr);
			original(nType, nullptr, &original_pItem, nullptr, nIndex, nPropSet, &pProperty, nState, fStatlist, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98220")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD98220, dll_base + 0x00058220);

		REPEAT_10();

		SUBCASE("Rolls with the seed of the unit")
		{
			// Input data
			const auto nLowSeed = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2ItemCalcStrc moo_pUserData{};
			D2UnitStrc original_pUnit{};
			D2ItemCalcStrc original_pUserData{};
			int nMin = random_unsigned_integer(0, 100);
			int nMax = random_unsigned_integer(0, 100);
			int nUnused{};

			const auto setup_data = [nLowSeed](
				D2UnitStrc& pUnit,
				D2ItemCalcStrc& pUserData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pSeed.nLowSeed = nLowSeed;
				pUnit.pSeed.nHighSeed = 666;

				pUserData.pUnit = &pUnit;
			};

			setup_data(moo_pUnit, moo_pUserData);
			setup_data(original_pUnit, original_pUserData);

			// Call both implementations
			const auto moo_result = sut(nMin, nMax, nUnused, &moo_pUserData);
			const auto original_result = original(nMin, nMax, nUnused, &original_pUserData);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Returns 0 without user data")
		{
			// Input data
			int nMin = random_unsigned_integer(0, 100);
			int nMax = random_unsigned_integer(0, 100);
			int nUnused{};

			// Call both implementations
			const auto moo_result = sut(nMin, nMax, nUnused, nullptr);
			const auto original_result = original(nMin, nMax, nUnused, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD982A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FD982A0, dll_base + 0x000582A0);

		SUBCASE("")
		{
			// Input data
			// Base and full stats contain all stats (sorted by their stat id) with random values
			const auto base_values = std::make_unique<int[]>(itemstatcost_record_count);
			const auto full_values = std::make_unique<int[]>(itemstatcost_record_count);
			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_values[i] = random_unsigned_integer(0, 1000);
				full_values[i] = base_values[i] + random_unsigned_integer(0, 1000);
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStats = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStats = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemCalcStrc moo_pUserData{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStats = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStats = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemCalcStrc original_pUserData{};
			int nUnused{};

			const auto setup_data = [&base_values, &full_values, this](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStats,
				const std::unique_ptr<D2StatStrc[]>& pFullStats,
				D2ItemCalcStrc& pUserData
			) {
				for (auto i = 0; i < itemstatcost_record_count; ++i)
				{
					pStats[i].nStat = static_cast<uint16_t>(i);
					pStats[i].nValue = base_values[i];
					pFullStats[i].nStat = static_cast<uint16_t>(i);
					pFullStats[i].nValue = full_values[i];
				}

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.Stats.pStat = pStats.get();
				pStatListEx.Stats.nStatCount = static_cast<uint16_t>(itemstatcost_record_count);
				pStatListEx.Stats.nCapacity = static_cast<uint16_t>(itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pFullStats.get();
				pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(itemstatcost_record_count);
				pStatListEx.FullStats.nCapacity = static_cast<uint16_t>(itemstatcost_record_count);
				pStatListEx.pOwner = &pUnit;

				pUnit.dwUnitType = UNIT_ITEM;
				pUnit.pStatListEx = &pStatListEx;

				pUserData.pUnit = &pUnit;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pUserData);
			setup_data(original_pUnit, original_pStatListEx, original_pStats, original_pFullStats, original_pUserData);

			for (auto i = 0; i < itemstatcost_record_count + 1; ++i)
			{
				// The attack rate requires a fully set up player or monster
				if (i == STAT_TOHIT)
				{
					continue;
				}

				for (auto j = 0; j < 3; ++j)
				{
					int nStatId = i;
					int a2 = j;

					// Call both implementations
					const auto moo_result = sut(nStatId, a2, nUnused, &moo_pUserData);
					const auto original_result = original(nStatId, a2, nUnused, &original_pUserData);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD98300 (#11300)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMMODS_EvaluateItemFormula, dll_base + 0x00058300);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nStatId = random_unsigned_integer(STAT_STRENGTH, STAT_VITALITY);
			const auto nStatValue = static_cast<int>(random_unsigned_integer(0, 1000));
			const auto nConstant1 = static_cast<int8_t>(random_unsigned_integer(0, 200) - 100);
			const auto nConstant2 = static_cast<int8_t>(random_unsigned_integer(0, 200) - 100);

			// Two formulas: "nConstant1 + nConstant2" at offset 0 and "stat(nStatId, a2)" at offset 6
			std::array<uint8_t, 14> code = {
				AST_Raw_Int8, static_cast<uint8_t>(nConstant1),
				AST_Raw_Int8, static_cast<uint8_t>(nConstant2),
				AST_Addition,
				AST_None,
				AST_Raw_Int16, static_cast<uint8_t>(nStatId & 0xFF), static_cast<uint8_t>(nStatId >> 8),
				AST_Raw_Int8, static_cast<uint8_t>(random_unsigned_integer(0, 2)),
				AST_CallbackTable, 3,
				AST_None,
			};

			sgptDataTables->pItemsCode = reinterpret_cast<FOGASTNodeStrc*>(code.data());
			sgptDataTables->nItemsCodeSize = static_cast<unsigned int>(code.size());

			const auto original_items_code = reinterpret_cast<FOGASTNodeStrc**>(dll_base + 0x000A9608 + 0x00000098);
			const auto original_items_code_size = reinterpret_cast<unsigned int*>(dll_base + 0x000A9608 + 0x0000009C);
			*original_items_code = sgptDataTables->pItemsCode;
			*original_items_code_size = sgptDataTables->nItemsCodeSize;

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pStat{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pStat{};
			const unsigned int calcs[] = { 0, 6, static_cast<unsigned int>(code.size()) };
			unsigned int nCalc = calcs[random_unsigned_integer(0, std::size(calcs) - 1)];

			const auto setup_data = [nStatId, nStatValue](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatStrc& pStat
			) {
				pStat.nStat = nStatId;
				pStat.nValue = nStatValue;

				pStatListEx.dwOwnerType = UNIT_ITEM;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.Stats.pStat = &pStat;
				pStatListEx.Stats.nStatCount = 1;
				pStatListEx.Stats.nCapacity = 1;
				pStatListEx.FullStats.pStat = &pStat;
				pStatListEx.FullStats.nStatCount = 1;
				pStatListEx.FullStats.nCapacity = 1;
				pStatListEx.pOwner = &pUnit;

				pUnit.dwUnitType = UNIT_ITEM;
				pUnit.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nullptr, nCalc);
			const auto original_result = original(&original_pUnit, nullptr, nCalc);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			sgptDataTables->pItemsCode = nullptr;
			sgptDataTables->nItemsCodeSize = 0;
			*original_items_code = nullptr;
			*original_items_code_size = 0;
		}
	}
}
