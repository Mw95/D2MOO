#include <D2CommonTestDefines.h>

#ifdef ITEMS_TESTS

#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <memory>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2BitManip.h>
#include <D2DataTbls.h>
#include <D2Inventory.h>
#include <D2Items.h>
#include <D2QuestRecord.h>
#include <D2StatList.h>
#include <D2States.h>
#include <DataTbls/MonsterIds.h>
#include <GAME/Game.h>
#include <Path/Path.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


// The buffer pointer is advanced while reading from/writing to the bitstream and points into a different stream for
// both implementations. Therefore it is omitted here, the content of the streams is compared separately.
BEGIN_VISIT(D2BitBufferStrc)
	OMIT(pBuffer)
	FIELD(nBits)
	FIELD(nPos)
	FIELD(nPosBits)
	FIELD(bFull)
END_VISIT()

DYNAMIC_ARRAY_TYPE(uint8_t)
DYNAMIC_ARRAY_TYPE(D2StatStrc)


namespace
{
	auto make_stat(int nStat, int nLayer, int nValue) -> D2StatStrc
	{
		D2StatStrc stat{};
		stat.nStat = static_cast<uint16_t>(nStat);
		stat.nLayer = static_cast<uint16_t>(nLayer);
		stat.nValue = nValue;
		return stat;
	}

	// Stat arrays are searched with a binary search, therefore the stats have to be sorted by their packed layer/stat id
	auto sorted_stats(std::vector<D2StatStrc> stats) -> std::vector<D2StatStrc>
	{
		std::sort(stats.begin(), stats.end(), [](const D2StatStrc& a, const D2StatStrc& b) { return a.nPackedValue < b.nPackedValue; });
		return stats;
	}

	// Sets up an extended stat list for the unit, the vectors pStats and pFullStats are used as storage for the stat arrays.
	// Both arrays get a capacity of at least nCapacity, so that stats can be inserted without reallocating the storage.
	// Note: The capacity must not exceed the stat count by more than D2StatsArrayStrc::nShrinkThreshold if stats might get removed.
	void setup_stat_list(
		D2UnitStrc& pUnit,
		D2StatListExStrc& pStatListEx,
		std::vector<D2StatStrc>& pStats,
		const std::vector<D2StatStrc>& stats,
		std::vector<D2StatStrc>& pFullStats,
		const std::vector<D2StatStrc>& full_stats,
		size_t nCapacity = 0
	) {
		pStats = stats;
		pStats.resize(std::max(stats.size(), nCapacity));
		pFullStats = full_stats;
		pFullStats.resize(std::max(full_stats.size(), nCapacity));

		pUnit.pStatListEx = &pStatListEx;

		pStatListEx.pUnit = &pUnit;
		pStatListEx.pOwner = &pUnit;
		pStatListEx.dwOwnerType = pUnit.dwUnitType;
		pStatListEx.dwOwnerId = pUnit.dwUnitId;
		pStatListEx.dwFlags |= STATLIST_EXTENDED;

		pStatListEx.Stats.pStat = pStats.empty() ? nullptr : pStats.data();
		pStatListEx.Stats.nStatCount = static_cast<uint16_t>(stats.size());
		pStatListEx.Stats.nCapacity = static_cast<uint16_t>(pStats.size());

		pStatListEx.FullStats.pStat = pFullStats.empty() ? nullptr : pFullStats.data();
		pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(full_stats.size());
		pStatListEx.FullStats.nCapacity = static_cast<uint16_t>(pFullStats.size());
	}

	// Sets a value of the data tables which is not covered by the fixtures for both implementations
	template<typename T, typename U>
	void set_data_tables_value(uintptr_t d2common_base, T D2DataTablesStrc::* member, U value)
	{
		const auto offset = reinterpret_cast<uintptr_t>(&(sgptDataTables->*member)) - reinterpret_cast<uintptr_t>(sgptDataTables);

		sgptDataTables->*member = static_cast<T>(value);
		*reinterpret_cast<T*>(d2common_base + 0x000A9608 + offset) = static_cast<T>(value);

		const auto original_sgptDataTables = reinterpret_cast<D2DataTablesStrc**>(d2common_base + 0x00096A20);
		*original_sgptDataTables = sgptDataTables;
	}

	// The skill id and the skill level of some stat layers (e.g. charged skills) are packed with these values,
	// they are usually set while loading ItemStatCost.txt
	void setup_skill_layer_packing(uintptr_t d2common_base)
	{
		set_data_tables_value(d2common_base, &D2DataTablesStrc::nStuff, 6);
		set_data_tables_value(d2common_base, &D2DataTablesStrc::nShiftedStuff, (1 << 6) - 1);
	}

	auto make_skill_layer(int nSkillId, int nSkillLevel) -> int
	{
		return (nSkillId << 6) + (nSkillLevel & ((1 << 6) - 1));
	}

	// The visitor of the stat arrays only compares the first stat, this compares all stats of the arrays
	void check_stat_arrays_eq(const D2StatsArrayStrc& moo_stats_array, const D2StatsArrayStrc& original_stats_array, const char* context_title)
	{
		CHECK_MESSAGE(moo_stats_array.nStatCount == original_stats_array.nStatCount, context_title);
		if (moo_stats_array.nStatCount == original_stats_array.nStatCount && moo_stats_array.nStatCount > 0)
		{
			auto moo_stats = DynamicArray<D2StatStrc>{ moo_stats_array.pStat, moo_stats_array.nStatCount };
			auto original_stats = DynamicArray<D2StatStrc>{ original_stats_array.pStat, original_stats_array.nStatCount };
			MOO_CHECK_EQ(moo_stats, original_stats, context_title);
		}
	}

	constexpr auto item_set_state_count = 6;

	// Properties of a stat list of an item set state (STATE_ITEMSET1-6)
	struct SetStateStatListProperties
	{
		int bPresent;
		uint32_t dwFlags;
		std::vector<D2StatStrc> stats;
	};

	// Sets up the stat lists of the item set states, they are linked to the extended stat list of the unit
	void setup_set_state_stat_lists(
		const SetStateStatListProperties (&properties)[item_set_state_count],
		D2UnitStrc& pUnit,
		D2StatListExStrc& pStatListEx,
		D2StatListStrc (&pSetStateStatLists)[item_set_state_count],
		std::vector<D2StatStrc> (&pSetStateStats)[item_set_state_count]
	) {
		for (auto i = 0; i < item_set_state_count; ++i)
		{
			if (!properties[i].bPresent)
			{
				continue;
			}

			auto& pStatList = pSetStateStatLists[i];
			pSetStateStats[i] = properties[i].stats;

			pStatList.pUnit = &pUnit;
			pStatList.dwOwnerType = pUnit.dwUnitType;
			pStatList.dwOwnerId = pUnit.dwUnitId;
			pStatList.dwFlags = properties[i].dwFlags;
			pStatList.dwStateNo = STATE_ITEMSET1 + i;
			pStatList.Stats.pStat = pSetStateStats[i].empty() ? nullptr : pSetStateStats[i].data();
			pStatList.Stats.nStatCount = static_cast<uint16_t>(pSetStateStats[i].size());
			pStatList.Stats.nCapacity = static_cast<uint16_t>(pSetStateStats[i].size());
			pStatList.pParent = &pStatListEx;

			auto& pLastStatList = (pStatList.dwFlags & STATLIST_SET) ? pStatListEx.pMyStats : pStatListEx.pMyLastList;
			pStatList.pPrevLink = pLastStatList;
			if (pLastStatList)
			{
				pLastStatList->pNextLink = &pStatList;
			}
			pLastStatList = &pStatList;
		}
	}

	// Writes the values (value and bit count) to a bitstream of nSize bytes, the remaining bits of the bitstream are random
	auto make_bitstream(const std::vector<std::pair<uint32_t, int>>& values, size_t nSize) -> std::vector<uint8_t>
	{
		std::vector<uint8_t> bitstream(nSize);
		for (auto& byte : bitstream)
		{
			byte = static_cast<uint8_t>(random_unsigned_integer(0, 255));
		}

		D2BitBufferStrc buffer{};
		BITMANIP_Initialize(&buffer, bitstream.data(), nSize);
		for (const auto& [value, bits] : values)
		{
			BITMANIP_Write(&buffer, value, bits);
		}

		return bitstream;
	}

	// Random properties of an item which gets serialized
	struct SerializedItemProperties
	{
		int nClassId;
		int nAnimMode;
		D2CoordStrc tCoords;
		uint32_t dwInitSeed;
		uint32_t dwItemFlags;
		uint32_t dwQualityNo;
		uint32_t dwRealmData[2];
		int32_t dwFileIndex;
		uint32_t dwItemLevel;
		uint16_t wItemFormat;
		uint16_t wRarePrefix;
		uint16_t wRareSuffix;
		uint16_t wAutoAffix;
		uint16_t wMagicPrefix[ITEMS_MAX_MODS];
		uint16_t wMagicSuffix[ITEMS_MAX_MODS];
		uint8_t nBodyLoc;
		uint8_t nInvPage;
		uint8_t nEarLvl;
		uint8_t nInvGfxIdx;
		char szPlayerName[16];
		std::vector<D2StatStrc> stats;
		std::vector<D2StatStrc> magic_stats;
	};

	// Note: Runewords are not covered, as there is no fixture for Runes.txt
	auto make_serialized_item_properties(int nClassId, int nItemStatCostTxtRecordCount) -> SerializedItemProperties
	{
		const uint32_t item_flags[] = { IFLAG_IDENTIFIED, IFLAG_SOCKETED, IFLAG_ETHEREAL, IFLAG_PERSONALIZED, IFLAG_ISEAR, IFLAG_INIT, IFLAG_NEWITEM, IFLAG_STARTITEM };

		SerializedItemProperties properties{};
		properties.nClassId = nClassId;
		properties.nAnimMode = random_unsigned_integer(IMODE_STORED, IMODE_SOCKETED);
		properties.tCoords.nX = random_unsigned_integer(0, 3) ? random_unsigned_integer(0, 15) : random_unsigned_integer(0, 0xFFFF);
		properties.tCoords.nY = random_unsigned_integer(0, 3) ? random_unsigned_integer(0, 15) : random_unsigned_integer(0, 0xFFFF);
		properties.dwInitSeed = random_unsigned_integer();
		for (const auto item_flag : item_flags)
		{
			properties.dwItemFlags |= random_unsigned_integer(0, 2) == 0 ? item_flag : 0;
		}
		properties.dwQualityNo = random_unsigned_integer(ITEMQUAL_INFERIOR, ITEMQUAL_TEMPERED);
		properties.dwRealmData[0] = random_unsigned_integer();
		properties.dwRealmData[1] = random_unsigned_integer(0, 1) * random_unsigned_integer();
		properties.dwFileIndex = random_unsigned_integer(0, 4095);
		properties.dwItemLevel = random_unsigned_integer(0, 127);
		properties.wItemFormat = random_unsigned_integer(0, 1);
		properties.wRarePrefix = random_unsigned_integer(0, 255);
		properties.wRareSuffix = random_unsigned_integer(0, 255);
		properties.wAutoAffix = random_unsigned_integer(0, 1) * random_unsigned_integer(0, 2047);
		for (auto i = 0; i < ITEMS_MAX_MODS; ++i)
		{
			properties.wMagicPrefix[i] = random_unsigned_integer(0, 1) * random_unsigned_integer(0, 2047);
			properties.wMagicSuffix[i] = random_unsigned_integer(0, 1) * random_unsigned_integer(0, 2047);
		}
		properties.nBodyLoc = random_unsigned_integer(0, 15);
		properties.nInvPage = random_unsigned_integer(0, 5);
		properties.nEarLvl = random_unsigned_integer(0, 127);
		properties.nInvGfxIdx = random_unsigned_integer(0, 7);

		const auto name_length = random_unsigned_integer(0, 15);
		for (auto i = 0u; i < name_length; ++i)
		{
			properties.szPlayerName[i] = static_cast<char>(random_unsigned_integer('a', 'z'));
		}

		const auto max_durability = static_cast<int>(random_unsigned_integer(0, 250));
		properties.stats = sorted_stats({
			make_stat(STAT_GOLD, 0, random_unsigned_integer(0, 1) ? random_unsigned_integer(1, 4095) : random_unsigned_integer(4096, 1000000)),
			make_stat(STAT_ARMORCLASS, 0, random_unsigned_integer(1, 200)),
			make_stat(STAT_QUANTITY, 0, random_unsigned_integer(1, 300)),
			make_stat(STAT_DURABILITY, 0, random_unsigned_integer(0, max_durability)),
			make_stat(STAT_MAXDURABILITY, 0, max_durability),
			make_stat(STAT_ITEM_NUMSOCKETS, 0, random_unsigned_integer(1, 6)),
			make_stat(STAT_QUESTITEMDIFFICULTY, 0, random_unsigned_integer(0, 2)),
		});

		std::vector<D2StatStrc> magic_stats;
		for (auto i = 0; i < 5; ++i)
		{
			magic_stats.push_back(make_stat(random_unsigned_integer(0, nItemStatCostTxtRecordCount - 1), random_unsigned_integer(0, 3), random_unsigned_integer(1, 20)));
		}
		magic_stats = sorted_stats(magic_stats);
		magic_stats.erase(std::unique(magic_stats.begin(), magic_stats.end(), [](const D2StatStrc& a, const D2StatStrc& b) { return a.nPackedValue == b.nPackedValue; }), magic_stats.end());
		properties.magic_stats = magic_stats;

		return properties;
	}

	// Sets up an item which can be serialized. The magic properties of the item are stored in a separate stat list.
	void setup_serialized_item(
		const SerializedItemProperties& properties,
		D2UnitStrc& pItem,
		D2ItemDataStrc& pItemData,
		D2StaticPathStrc& pStaticPath,
		D2StatListExStrc& pStatListEx,
		std::vector<D2StatStrc>& pStats,
		std::vector<D2StatStrc>& pFullStats,
		D2StatListStrc& pMagicStatList,
		std::vector<D2StatStrc>& pMagicStats
	) {
		pItem.dwUnitType = UNIT_ITEM;
		pItem.dwClassId = properties.nClassId;
		pItem.dwAnimMode = properties.nAnimMode;
		pItem.dwInitSeed = properties.dwInitSeed;
		pItem.pItemData = &pItemData;
		pItem.pStaticPath = &pStaticPath;

		pStaticPath.tGameCoords = properties.tCoords;

		pItemData.dwItemFlags = properties.dwItemFlags;
		pItemData.dwQualityNo = properties.dwQualityNo;
		pItemData.dwRealmData[0] = properties.dwRealmData[0];
		pItemData.dwRealmData[1] = properties.dwRealmData[1];
		pItemData.dwFileIndex = properties.dwFileIndex;
		pItemData.dwItemLevel = properties.dwItemLevel;
		pItemData.wItemFormat = properties.wItemFormat;
		pItemData.wRarePrefix = properties.wRarePrefix;
		pItemData.wRareSuffix = properties.wRareSuffix;
		pItemData.wAutoAffix = properties.wAutoAffix;
		for (auto i = 0; i < ITEMS_MAX_MODS; ++i)
		{
			pItemData.wMagicPrefix[i] = properties.wMagicPrefix[i];
			pItemData.wMagicSuffix[i] = properties.wMagicSuffix[i];
		}
		pItemData.nBodyLoc = properties.nBodyLoc;
		pItemData.nInvPage = properties.nInvPage;
		pItemData.nEarLvl = properties.nEarLvl;
		pItemData.nInvGfxIdx = properties.nInvGfxIdx;
		std::memcpy(pItemData.szPlayerName, properties.szPlayerName, sizeof(pItemData.szPlayerName));

		setup_stat_list(pItem, pStatListEx, pStats, properties.stats, pFullStats, properties.stats);

		pMagicStats = properties.magic_stats;
		pMagicStatList.pUnit = &pItem;
		pMagicStatList.dwOwnerType = UNIT_ITEM;
		pMagicStatList.dwFlags = STATLIST_MAGIC;
		pMagicStatList.Stats.pStat = pMagicStats.empty() ? nullptr : pMagicStats.data();
		pMagicStatList.Stats.nStatCount = static_cast<uint16_t>(pMagicStats.size());
		pMagicStatList.Stats.nCapacity = static_cast<uint16_t>(pMagicStats.size());
		pMagicStatList.pParent = &pStatListEx;
		pStatListEx.pMyLastList = &pMagicStatList;
	}
}


// The fixtures are defined with internal linkage, as other tests might define fixtures with the same names
namespace
{
	// There is no fixture for the MagicPrefix/MagicSuffix/AutoMagic tables (yet). This fixture sets up an empty magic affix table,
	// so that functions can look up affixes without failing assertions. These look ups never return a record.
	template<class Fixture>
	struct EmptyMagicAffixTxtFixture : Fixture
	{
		uintptr_t magicaffix_d2common_base;
		D2MagicAffixTxt magicaffix_txt[1];

		EmptyMagicAffixTxtFixture() : magicaffix_txt{}
		{
			const auto working_directory = std::filesystem::current_path();
			magicaffix_d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

			set_data_tables_value(magicaffix_d2common_base, &D2DataTablesStrc::pMagicAffixDataTables, D2MagicAffixDataTbl{ 0, magicaffix_txt, magicaffix_txt, magicaffix_txt, magicaffix_txt });
		}

		~EmptyMagicAffixTxtFixture()
		{
			set_data_tables_value(magicaffix_d2common_base, &D2DataTablesStrc::pMagicAffixDataTables, D2MagicAffixDataTbl{});
		}
	};


	// Sets up the linker which is used to look up item ids by item codes (see DATATBLS_GetItemIdFromItemCode), requires the ItemsTxtFixture
	template<class Fixture>
	struct ItemsLinkerFixture : Fixture
	{
		uintptr_t linker_d2common_base;

		ItemsLinkerFixture()
		{
			const auto working_directory = std::filesystem::current_path();
			linker_d2common_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

			auto* pLinker = static_cast<D2TxtLinkStrc*>(FOG_AllocLinker(__FILE__, __LINE__));

			for (auto i = 0; i < this->items_record_count; ++i)
			{
				FOG_10215(pLinker, this->items_txt[i].dwCode);
			}

			set_data_tables_value(linker_d2common_base, &D2DataTablesStrc::pItemsLinker, pLinker);
		}

		~ItemsLinkerFixture()
		{
			FOG_FreeLinker(sgptDataTables->pItemsLinker);
			set_data_tables_value(linker_d2common_base, &D2DataTablesStrc::pItemsLinker, nullptr);
		}
	};
}

TEST_SUITE("D2ItemsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98380 (#10687)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AllocItemData, dll_base + 0x00058380);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				pItem.dwUnitType = UNIT_ITEM;
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			sut(nullptr, &moo_pItem);
			original(nullptr, &original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD983F0 (#10688)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_FreeItemData, dll_base + 0x000583F0);
		const auto [moo_alloc, original_alloc] = make_function_pair(ITEMS_AllocItemData, dll_base + 0x00058380);
		
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

			moo_alloc(nullptr, &moo_pItem);
			original_alloc(nullptr, &original_pItem);

			// Call both implementations
			sut(nullptr, &moo_pItem);
			original(nullptr, &original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98430 (#10689)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetBodyLocation, dll_base + 0x00058430);
		
		SUBCASE("")
		{
			// Input data
			const auto body_loc = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [body_loc](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.nBodyLoc = body_loc;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98450 (#10690)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetBodyLocation, dll_base + 0x00058450);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint8_t nBodyLoc = random_unsigned_integer(0, 255);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nBodyLoc);
			original(&original_pItem, nBodyLoc);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98470 (#10691)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemSeed, dll_base + 0x00058470);
		
		SUBCASE("")
		{
			// Input data
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [low_seed, high_seed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.pSeed.nLowSeed = low_seed;
				pItemData.pSeed.nHighSeed = high_seed;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98490 (#10692)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_InitItemSeed, dll_base + 0x00058490);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem);
			original(&original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD984B0 (#10693)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemStartSeed, dll_base + 0x000584B0);
		
		SUBCASE("")
		{
			// Input data
			const auto init_seed = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [init_seed](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwInitSeed = init_seed;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD984D0 (#10694)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetItemStartSeed, dll_base + 0x000584D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nSeed = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nSeed);
			original(&original_pItem, nSeed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98550 (#10695)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemQuality, dll_base + 0x00058550);
		
		SUBCASE("")
		{
			// Input data
			const auto quality = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [quality](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwQualityNo = quality;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98580 (#10696)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetItemQuality, dll_base + 0x00058580);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nQuality = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nQuality);
			original(&original_pItem, nQuality);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD985A0 (#10699)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetPrefixId, dll_base + 0x000585A0);
		
		SUBCASE("")
		{
			// Input data
			uint16_t prefixes[3] = {
				static_cast<uint16_t>(random_unsigned_integer(0, 65535)),
				static_cast<uint16_t>(random_unsigned_integer(0, 65535)),
				static_cast<uint16_t>(random_unsigned_integer(0, 65535))
			};

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nPrefixNo = GENERATE(0, 1, 2);

			const auto setup_data = [&prefixes](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				memcpy(pItemData.wMagicPrefix, prefixes, sizeof(pItemData.wMagicPrefix));
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, nPrefixNo);
			const auto original_result = original(&original_pItem, nPrefixNo);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD985D0 (#10700)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AssignPrefix, dll_base + 0x000585D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint16_t nPrefix = random_unsigned_integer(0, 65535);
			int nPrefixNo = GENERATE(0, 1, 2);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nPrefix, nPrefixNo);
			original(&original_pItem, nPrefix, nPrefixNo);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98600 (#10697)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAutoAffix, dll_base + 0x00058600);
		
		SUBCASE("")
		{
			// Input data
			const auto affix = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [affix](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.wAutoAffix = affix;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98630 (#10698)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetAutoAffix, dll_base + 0x00058630);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint16_t nAffix = random_unsigned_integer(0, 65535);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nAffix);
			original(&original_pItem, nAffix);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98650 (#10701)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSuffixId, dll_base + 0x00058650);
		
		SUBCASE("")
		{
			// Input data
			uint16_t suffixes[3] = {
				static_cast<uint16_t>(random_unsigned_integer(0, 65535)),
				static_cast<uint16_t>(random_unsigned_integer(0, 65535)),
				static_cast<uint16_t>(random_unsigned_integer(0, 65535))
			};

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nSuffixNo = GENERATE(0, 1, 2);

			const auto setup_data = [&suffixes](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				memcpy(pItemData.wMagicSuffix, suffixes, sizeof(pItemData.wMagicSuffix));
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, nSuffixNo);
			const auto original_result = original(&original_pItem, nSuffixNo);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98680 (#10702)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AssignSuffix, dll_base + 0x00058680);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint16_t nSuffix = random_unsigned_integer(0, 65535);
			int nSuffixNo = GENERATE(0, 1, 2);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nSuffix, nSuffixNo);
			original(&original_pItem, nSuffix, nSuffixNo);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD986B0 (#10703)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetRarePrefixId, dll_base + 0x000586B0);
		
		SUBCASE("")
		{
			// Input data
			const auto rare_prefix = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [rare_prefix](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.wRarePrefix = rare_prefix;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD986E0 (#10704)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AssignRarePrefix, dll_base + 0x000586E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint16_t nPrefix = random_unsigned_integer(0, 65535);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nPrefix);
			original(&original_pItem, nPrefix);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98700 (#10705)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetRareSuffixId, dll_base + 0x00058700);
		
		SUBCASE("")
		{
			// Input data
			const auto rare_suffix = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [rare_suffix](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.wRareSuffix = rare_suffix;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98730 (#10706)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AssignRareSuffix, dll_base + 0x00058730);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint16_t nSuffix = random_unsigned_integer(0, 65535);
			
			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nSuffix);
			original(&original_pItem, nSuffix);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98750 (#10707)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckItemFlag, dll_base + 0x00058750);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto flags = random_unsigned_integer();

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				uint32_t dwFlag = (1 << i);

				const auto setup_data = [flags](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = flags;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, dwFlag, __LINE__, __FILE__);
				const auto original_result = original(&original_pItem, dwFlag, __LINE__, __FILE__);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98780 (#10708)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetItemFlag, dll_base + 0x00058780);
		
		SUBCASE("")
		{
			const auto set = GENERATE(true, false);

			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto flags = random_unsigned_integer();

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				uint32_t dwFlag = (1 << i);
				BOOL bSet = set;

				const auto setup_data = [flags](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = flags;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				sut(&moo_pItem, dwFlag, bSet);
				original(&original_pItem, dwFlag, bSet);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD987C0 (#10709)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemFlags, dll_base + 0x000587C0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			
			const auto setup_data = [flags](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwItemFlags = flags;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD987E0 (#10710)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckItemCMDFlag, dll_base + 0x000587E0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto flags = random_unsigned_integer();

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				int nFlag = (1 << i);

				const auto setup_data = [flags](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItemData.dwCommandFlags = flags;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, nFlag);
				const auto original_result = original(&original_pItem, nFlag);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98810 (#10711)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetItemCMDFlag, dll_base + 0x00058810);
		
		SUBCASE("")
		{
			const auto set = GENERATE(true, false);

			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto flags = random_unsigned_integer();

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				int nFlag = (1 << i);
				BOOL bSet = set;

				const auto setup_data = [flags](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItemData.dwCommandFlags = flags;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				sut(&moo_pItem, nFlag, bSet);
				original(&original_pItem, nFlag, bSet);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98850 (#10712)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemCMDFlags, dll_base + 0x00058850);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [flags](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwCommandFlags = flags;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98870 (#10717)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemLevel, dll_base + 0x00058870);
		
		SUBCASE("")
		{
			// Input data
			const auto item_level = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [item_level](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwItemLevel = item_level;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD988B0 (#10718)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetItemLevel, dll_base + 0x000588B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nItemLevel = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nItemLevel);
			original(&original_pItem, nItemLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD988E0 (#10719)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetInvPage, dll_base + 0x000588E0);
		
		SUBCASE("")
		{
			// Input data
			const auto inv_page = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [inv_page](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.nInvPage = inv_page;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98900 (#10720)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetInvPage, dll_base + 0x00058900);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint8_t nPage = random_unsigned_integer(0, 255);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nPage);
			original(&original_pItem, nPage);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98920 (#10721)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetCellOverlap, dll_base + 0x00058920);
		
		SUBCASE("")
		{
			// Input data
			const auto cell_overlap = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [cell_overlap](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.nCellOverlap = cell_overlap;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98940 (#10722)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetCellOverlap, dll_base + 0x00058940);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nCellOverlap = random_unsigned_integer(0, 255);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nCellOverlap);
			original(&original_pItem, nCellOverlap);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98960 (#10853)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemCell, dll_base + 0x00058960);
		
		SUBCASE("")
		{
			// Input data
			const auto item_cell = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [item_cell](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.nItemCell = item_cell;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98980 (#10854)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetItemCell, dll_base + 0x00058980);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nItemCell = random_unsigned_integer(0, 255);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nItemCell);
			original(&original_pItem, nItemCell);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD989A0 (#10723)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetEarName, dll_base + 0x000589A0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				strcpy_s(pItemData.szPlayerName, "Player");
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD989C0 (#10724)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetEarName, dll_base + 0x000589C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			char* moo_szName = "Player";
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			char* original_szName = "Player";

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, moo_szName);
			original(&original_pItem, original_szName);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD989F0 (#10725)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetEarLevel, dll_base + 0x000589F0);

		SUBCASE("")
		{
			// Input data
			const auto ear_level = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [ear_level](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.nEarLvl = ear_level;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98A10 (#10726)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetEarLevel, dll_base + 0x00058A10);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nLevel = random_unsigned_integer(0, 255);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nLevel);
			original(&original_pItem, nLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98A30 (#10727)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetVarGfxIndex, dll_base + 0x00058A30);
		
		SUBCASE("")
		{
			// Input data
			const auto index = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [index](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.nInvGfxIdx = index;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98A50 (#10728)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetVarGfxIndex, dll_base + 0x00058A50);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint8_t nIndex = random_unsigned_integer(0, 255);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nIndex);
			original(&original_pItem, nIndex);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FD98A70 (#10777)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsRepairable, dll_base + 0x00058A70);

		SUBCASE("")
		{
			const auto item_flags = GENERATE(0u, static_cast<uint32_t>(IFLAG_IDENTIFIED), static_cast<uint32_t>(IFLAG_IDENTIFIED | IFLAG_ETHEREAL));

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto stats = sorted_stats({
					make_stat(STAT_QUANTITY, 0, random_unsigned_integer(0, 50)),
					make_stat(STAT_MAXDURABILITY, 0, random_unsigned_integer(0, 1) * random_unsigned_integer(1, 250)),
					make_stat(STAT_ITEM_INDESCTRUCTIBLE, 0, random_unsigned_integer(0, 3) == 0),
					make_stat(STAT_ITEM_CHARGED_SKILL, random_unsigned_integer(0, 0xFFFF), (random_unsigned_integer(1, 255) << 8) + random_unsigned_integer(0, 255)),
				});

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;

				const auto setup_data = [i, item_flags, &stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = item_flags;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemTypesTxtFixture<NoopFixture>, "D2Common.0x6FD98C60 (#10780)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAmmoTypeFromItemType, dll_base + 0x00058C60);
		
		SUBCASE("")
		{
			for (auto i = 0; i < itemtypes_record_count; ++i)
			{
				int nItemType = i;

				// Call both implementations
				const auto moo_result = sut(nItemType);
				const auto original_result = original(nItemType);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD98CA0 (#10781)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAmmoType, dll_base + 0x00058CA0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemTypesTxtFixture<NoopFixture>, "D2Common.0x6FD98D20 (#10782)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetQuiverTypeFromItemType, dll_base + 0x00058D20);
		
		SUBCASE("")
		{
			for (auto i = 0; i < itemtypes_record_count; ++i)
			{
				int nItemType = i;

				// Call both implementations
				const auto moo_result = sut(nItemType);
				const auto original_result = original(nItemType);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD98D60 (#10783)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetQuiverType, dll_base + 0x00058D60);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemTypesTxtFixture<NoopFixture>, "D2Common.0x6FD98DE0 (#10784)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAutoStackFromItemType, dll_base + 0x00058DE0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < itemtypes_record_count; ++i)
			{
				int nItemType = i;

				// Call both implementations
				const auto moo_result = sut(nItemType);
				const auto original_result = original(nItemType);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD98E20 (#10785)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAutoStack, dll_base + 0x00058E20);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD98EA0 (#10786)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetReload, dll_base + 0x00058EA0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD98F20 (#10787)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetReEquip, dll_base + 0x00058F20);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD98FA0 (#10788)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetStorePage, dll_base + 0x00058FA0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99020 (#10789)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetVarInvGfxCount, dll_base + 0x00059020);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD990A0 (#10790)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetVarInvGfxString, dll_base + 0x000590A0);
		
		SUBCASE("")
		{
			const auto id = GENERATE(0, 1, 2, 3, 4, 5);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};
				int nId = id;

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, nId);
				const auto original_result = original(&original_pItem, nId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99140 (#10792)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CanBeRare, dll_base + 0x00059140);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD991C0 (#10791)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CanBeMagic, dll_base + 0x000591C0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99240 (#10793)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CanBeNormal, dll_base + 0x00059240);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD992C0 (#10744)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetWeaponClassCode, dll_base + 0x000592C0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD992F0 (#10745)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_Get2HandWeaponClassCode, dll_base + 0x000592F0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99370 (#10746)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetBaseCode, dll_base + 0x00059370);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD993F0 (#10747)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAltGfx, dll_base + 0x000593F0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99480 (#10748)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetComponent, dll_base + 0x00059480);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD99500 (#10749)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetDimensions, dll_base + 0x00059500);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				uint8_t moo_pWidth{};
				uint8_t moo_pHeight{};
				D2UnitStrc original_pItem{};
				uint8_t original_pWidth{};
				uint8_t original_pHeight{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					uint8_t& pWidth,
					uint8_t& pHeight
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem, moo_pWidth, moo_pHeight);
				setup_data(original_pItem, original_pWidth, original_pHeight);

				// Call both implementations
				sut(&moo_pItem, &moo_pWidth, &moo_pHeight, __FILE__, __LINE__);
				original(&original_pItem, &original_pWidth, &original_pHeight, __FILE__, __LINE__);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pWidth, original_pWidth, "Comparing pWidth");
				MOO_CHECK_EQ(moo_pHeight, original_pHeight, "Comparing pHeight");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99540 (#10750)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAllowedBodyLocations, dll_base + 0x00059540);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				uint8_t moo_pBodyLoc1{};
				uint8_t moo_pBodyLoc2{};
				D2UnitStrc original_pItem{};
				uint8_t original_pBodyLoc1{};
				uint8_t original_pBodyLoc2{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					uint8_t& pBodyLoc1,
					uint8_t& pBodyLoc2
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem, moo_pBodyLoc1, moo_pBodyLoc2);
				setup_data(original_pItem, original_pBodyLoc1, original_pBodyLoc2);

				// Call both implementations
				sut(&moo_pItem, &moo_pBodyLoc1, &moo_pBodyLoc2);
				original(&original_pItem, &original_pBodyLoc1, &original_pBodyLoc2);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pBodyLoc1, original_pBodyLoc1, "Comparing pBodyLoc1");
				MOO_CHECK_EQ(moo_pBodyLoc2, original_pBodyLoc2, "Comparing pBodyLoc2");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD995D0 (#10751)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemType, dll_base + 0x000595D0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99640 (#10752)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemTypeFromItemId, dll_base + 0x00059640);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				uint32_t dwItemId = i;

				// Call both implementations
				const auto moo_result = sut(dwItemId);
				const auto original_result = original(dwItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD99680 (#10753)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemQlvl, dll_base + 0x00059680);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD99700 (#10754)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfFlagIsSet, dll_base + 0x00059700);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				int nFlags = random_unsigned_integer();
				int nFlag = (1 << i);

				// Call both implementations
				const auto moo_result = sut(nFlags, nFlag);
				const auto original_result = original(nFlags, nFlag);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD99710 (#10755)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetOrRemoveFlag, dll_base + 0x00059710);
		
		SUBCASE("")
		{
			const auto set = GENERATE(true, false);

			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto flags = random_unsigned_integer();

				int moo_pFlags{};
				int original_pFlags{};
				int nFlag = (1 << i);
				BOOL bSet = set;

				const auto setup_data = [flags](
					int& pFlags
				) {
					pFlags = flags;
				};

				setup_data(moo_pFlags);
				setup_data(original_pFlags);

				// Call both implementations
				sut(&moo_pFlags, nFlag, bSet);
				original(&original_pFlags, nFlag, bSet);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pFlags, original_pFlags, "Comparing pFlags");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<ExperienceTxtFixture<EmptyMagicAffixTxtFixture<NoopFixture>>>>>, "D2Common.0x6FD99740 (#10756)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckRequirements, dll_base + 0x00059740);

		// Note: Unique and set items are not covered, the magic affix table is empty
		SUBCASE("")
		{
			const auto item_flags = GENERATE(0u, static_cast<uint32_t>(IFLAG_IDENTIFIED), static_cast<uint32_t>(IFLAG_IDENTIFIED | IFLAG_ETHEREAL));
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);
			const BOOL bEquipping = GENERATE(FALSE, TRUE);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const D2C_ItemQualities qualities[] = { ITEMQUAL_INFERIOR, ITEMQUAL_NORMAL, ITEMQUAL_SUPERIOR, ITEMQUAL_MAGIC, ITEMQUAL_RARE, ITEMQUAL_CRAFT, ITEMQUAL_TEMPERED };
				const auto quality = qualities[random_unsigned_integer(0, std::size(qualities) - 1)];
				const auto unit_class = unit_type == UNIT_PLAYER ? random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1) : random_unsigned_integer(MONSTER_ACT5HIRE1 - 1, MONSTER_ACT5HIRE2 + 1);

				const auto item_stats = sorted_stats({
					make_stat(STAT_QUANTITY, 0, random_unsigned_integer(0, 50)),
					make_stat(STAT_ITEM_REQ_PERCENT, 0, static_cast<int>(random_unsigned_integer(0, 100)) - 50),
					make_stat(STAT_ITEM_LEVELREQ, 0, random_unsigned_integer(0, 10)),
				});

				const auto unit_stats = sorted_stats({
					make_stat(STAT_STRENGTH, 0, random_unsigned_integer(0, 200)),
					make_stat(STAT_DEXTERITY, 0, random_unsigned_integer(0, 200)),
					make_stat(STAT_LEVEL, 0, random_unsigned_integer(1, 99)),
				});

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pItemStatListEx{};
				std::vector<D2StatStrc> moo_pItemStats;
				std::vector<D2StatStrc> moo_pItemFullStats;
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pUnitStatListEx{};
				std::vector<D2StatStrc> moo_pUnitStats;
				std::vector<D2StatStrc> moo_pUnitFullStats;
				BOOL moo_bStrength{};
				BOOL moo_bDexterity{};
				BOOL moo_bLevel{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pItemStatListEx{};
				std::vector<D2StatStrc> original_pItemStats;
				std::vector<D2StatStrc> original_pItemFullStats;
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pUnitStatListEx{};
				std::vector<D2StatStrc> original_pUnitStats;
				std::vector<D2StatStrc> original_pUnitFullStats;
				BOOL original_bStrength{};
				BOOL original_bDexterity{};
				BOOL original_bLevel{};

				const auto setup_data = [i, item_flags, quality, unit_type, unit_class, &item_stats, &unit_stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pItemStatListEx,
					std::vector<D2StatStrc>& pItemStats,
					std::vector<D2StatStrc>& pItemFullStats,
					D2UnitStrc& pUnit,
					D2StatListExStrc& pUnitStatListEx,
					std::vector<D2StatStrc>& pUnitStats,
					std::vector<D2StatStrc>& pUnitFullStats,
					BOOL& bStrength,
					BOOL& bDexterity,
					BOOL& bLevel
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = item_flags;
					pItemData.dwQualityNo = quality;
					setup_stat_list(pItem, pItemStatListEx, pItemStats, item_stats, pItemFullStats, item_stats);

					pUnit.dwUnitType = unit_type;
					pUnit.dwClassId = unit_class;
					setup_stat_list(pUnit, pUnitStatListEx, pUnitStats, unit_stats, pUnitFullStats, unit_stats);

					bStrength = TRUE;
					bDexterity = TRUE;
					bLevel = TRUE;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pItemStatListEx, moo_pItemStats, moo_pItemFullStats, moo_pUnit, moo_pUnitStatListEx, moo_pUnitStats, moo_pUnitFullStats, moo_bStrength, moo_bDexterity, moo_bLevel);
				setup_data(original_pItem, original_pItemData, original_pItemStatListEx, original_pItemStats, original_pItemFullStats, original_pUnit, original_pUnitStatListEx, original_pUnitStats, original_pUnitFullStats, original_bStrength, original_bDexterity, original_bLevel);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &moo_pUnit, bEquipping, &moo_bStrength, &moo_bDexterity, &moo_bLevel);
				const auto original_result = original(&original_pItem, &original_pUnit, bEquipping, &original_bStrength, &original_bDexterity, &original_bLevel);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_bStrength, original_bStrength, "Comparing bStrength");
				MOO_CHECK_EQ(moo_bDexterity, original_bDexterity, "Comparing bDexterity");
				MOO_CHECK_EQ(moo_bLevel, original_bLevel, "Comparing bLevel");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99BC0 (#10741)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetQuestFromItemId, dll_base + 0x00059BC0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99C60 (#10742)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetQuest, dll_base + 0x00059C60);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD99D40 (#10743)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetNormalCode, dll_base + 0x00059D40);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<SkillsTxtFixture<UniqueItemsTxtFixture<SetItemsTxtFixture<ExperienceTxtFixture<EmptyMagicAffixTxtFixture<NoopFixture>>>>>>>>, "D2Common.0x6FD99DB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetRequiredLevel, dll_base + 0x00059DB0);

		// Note: The magic affix table is empty, affixes do not contribute to the required level
		SUBCASE("Inferior, normal, superior, magic, rare, crafted and tempered")
		{
			const auto quality = GENERATE(ITEMQUAL_INFERIOR, ITEMQUAL_NORMAL, ITEMQUAL_SUPERIOR, ITEMQUAL_MAGIC, ITEMQUAL_RARE, ITEMQUAL_CRAFT, ITEMQUAL_TEMPERED);
			const auto with_player = GENERATE(0, 1);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto player_class = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);

				const auto stats = sorted_stats({
					make_stat(STAT_ITEM_LEVELREQ, 0, random_unsigned_integer(0, 10)),
					make_stat(STAT_ITEM_NONCLASSSKILL, random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 3)),
					make_stat(STAT_ITEM_SINGLESKILL, random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 3)),
				});

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc moo_pPlayer{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2UnitStrc original_pPlayer{};

				const auto setup_data = [i, quality, player_class, &stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2UnitStrc& pPlayer
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = quality;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);

					pPlayer.dwUnitType = UNIT_PLAYER;
					pPlayer.dwClassId = player_class;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pPlayer);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats, original_pPlayer);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, with_player ? &moo_pPlayer : nullptr);
				const auto original_result = original(&original_pItem, with_player ? &original_pPlayer : nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			}
		}

		SUBCASE("Unique")
		{
			const auto with_player = GENERATE(false, true);
			const auto player_flags_ex = GENERATE(0u, static_cast<uint32_t>(UNITFLAGEX_ISEXPANSION));
			const auto item_format = GENERATE(0, 1);

			for (auto i = 0; i < uniqueitems_record_count; ++i)
			{
				// Input data
				const auto item_id = random_unsigned_integer(0, items_record_count - 1);
				const auto stats = sorted_stats({
					make_stat(STAT_ITEM_LEVELREQ, 0, random_unsigned_integer(0, 10)),
				});

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc moo_pPlayer{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2UnitStrc original_pPlayer{};

				const auto setup_data = [i, item_id, player_flags_ex, item_format, &stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2UnitStrc& pPlayer
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = item_id;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = ITEMQUAL_UNIQUE;
					pItemData.dwFileIndex = i;
					pItemData.wItemFormat = item_format;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);

					pPlayer.dwUnitType = UNIT_PLAYER;
					pPlayer.dwFlagEx = player_flags_ex;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pPlayer);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats, original_pPlayer);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, with_player ? &moo_pPlayer : nullptr);
				const auto original_result = original(&original_pItem, with_player ? &original_pPlayer : nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			}
		}

		SUBCASE("Set")
		{
			for (auto i = 0; i < setitems_record_count; ++i)
			{
				// Input data
				const auto item_id = random_unsigned_integer(0, items_record_count - 1);
				const auto stats = sorted_stats({
					make_stat(STAT_ITEM_LEVELREQ, 0, random_unsigned_integer(0, 10)),
				});

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc moo_pPlayer{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2UnitStrc original_pPlayer{};

				const auto setup_data = [i, item_id, &stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2UnitStrc& pPlayer
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = item_id;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = ITEMQUAL_SET;
					pItemData.dwFileIndex = i;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);

					pPlayer.dwUnitType = UNIT_PLAYER;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pPlayer);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats, original_pPlayer);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &moo_pPlayer);
				const auto original_result = original(&original_pItem, &original_pPlayer);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<SkillsTxtFixture<ExperienceTxtFixture<EmptyMagicAffixTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FD9A3F0 (#10757)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetLevelRequirement, dll_base + 0x0005A3F0);
		
		// Note: The magic affix table is empty, affixes do not contribute to the required level
		SUBCASE("")
		{
			const auto quality = GENERATE(ITEMQUAL_INFERIOR, ITEMQUAL_NORMAL, ITEMQUAL_SUPERIOR, ITEMQUAL_MAGIC, ITEMQUAL_RARE, ITEMQUAL_CRAFT, ITEMQUAL_TEMPERED);
			const auto with_player = GENERATE(false, true);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto player_class = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);

				const auto stats = sorted_stats({
					make_stat(STAT_ITEM_LEVELREQ, 0, random_unsigned_integer(0, 10)),
					make_stat(STAT_ITEM_NONCLASSSKILL, random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 3)),
					make_stat(STAT_ITEM_SINGLESKILL, random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 3)),
				});

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i, quality, player_class, &stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2UnitStrc& pUnit
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = quality;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);

					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = player_class;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pUnit);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, with_player ? &moo_pUnit : nullptr);
				const auto original_result = original(&original_pItem, with_player ? &original_pUnit : nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A400 (#10758)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckBodyLocation, dll_base + 0x0005A400);
		
		SUBCASE("")
		{
			for (auto j = 0; j < 13; ++j)
			{
				for (auto i = 0; i < items_record_count; ++i)
				{
					// Input data
					D2UnitStrc moo_pItem{};
					D2UnitStrc original_pItem{};
					uint8_t nBodyLoc = j;

					const auto setup_data = [i](
						D2UnitStrc& pItem
					) {
						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = i;
					};

					// NOTE: For whatever reason, the test fails without at least one of these
					CAPTURE(i);
					CAPTURE(j);

					setup_data(moo_pItem);
					setup_data(original_pItem);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem, nBodyLoc);
					const auto original_result = original(&original_pItem, nBodyLoc);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemTypesTxtFixture<NoopFixture>, "D2Common.0x6FD9A4F0 (#10762)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckItemTypeIfThrowable, dll_base + 0x0005A4F0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < itemtypes_record_count; ++i)
			{
				int nItemType = i;

				// Call both implementations
				const auto moo_result = sut(nItemType);
				const auto original_result = original(nItemType);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A530 (#10759)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfThrowable, dll_base + 0x0005A530);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A5B0 (#10760)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetMissileType, dll_base + 0x0005A5B0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A5E0 (#10761)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetMeleeRange, dll_base + 0x0005A5E0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD9A610 (#10763)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckWeaponClassByItemId, dll_base + 0x0005A610);
		
		SUBCASE("")
		{
			for (auto j = 0; j < NUM_WEAPON_CLASSES; ++j)
			{
				for (auto i = 0; i < items_record_count; ++i)
				{
					int nItemId = i;
					int nWeapClass = j;

					// Call both implementations
					const auto moo_result = sut(nItemId, nWeapClass);
					const auto original_result = original(nItemId, nWeapClass);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD9A660 (#10764)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckWeaponClass, dll_base + 0x0005A660);
		
		SUBCASE("")
		{
			for (auto j = 0; j < NUM_WEAPON_CLASSES; ++j)
			{
				for (auto i = 0; i < items_record_count; ++i)
				{
					// Input data
					D2UnitStrc moo_pItem{};
					D2UnitStrc original_pItem{};
					int nWeapClass = j;

					const auto setup_data = [i](
						D2UnitStrc& pItem
					) {
						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = i;
					};

					setup_data(moo_pItem);
					setup_data(original_pItem);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem, nWeapClass);
					const auto original_result = original(&original_pItem, nWeapClass);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A6C0 (#10766)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckWeaponIfTwoHandedByItemId, dll_base + 0x0005A6C0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A700 (#10765)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckWeaponIfTwoHanded, dll_base + 0x0005A700);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A750 (#10767)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfStackable, dll_base + 0x0005A750);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A7A0 (#10768)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfBeltable, dll_base + 0x0005A7A0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD9A820 (#10769)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_ComparePotionTypes, dll_base + 0x0005A820);
		
		SUBCASE("")
		{
			for (auto j = 0; j < items_record_count; ++j)
			{
				for (auto i = 0; i < items_record_count; ++i)
				{
					// Input data
					D2UnitStrc moo_pItem1{};
					D2UnitStrc moo_pItem2{};
					D2UnitStrc original_pItem1{};
					D2UnitStrc original_pItem2{};

					const auto setup_data = [i, j](
						D2UnitStrc& pItem1,
						D2UnitStrc& pItem2
					) {
						pItem1.dwUnitType = UNIT_ITEM;
						pItem1.dwClassId = i;
						pItem2.dwUnitType = UNIT_ITEM;
						pItem2.dwClassId = j;
					};

					setup_data(moo_pItem1, moo_pItem2);
					setup_data(original_pItem1, original_pItem2);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem1, &moo_pItem2);
					const auto original_result = original(&original_pItem1, &original_pItem2);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem1, original_pItem1, "Comparing pItem1");
					MOO_CHECK_EQ(moo_pItem2, original_pItem2, "Comparing pItem2");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A960 (#10770)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfAutoBeltable, dll_base + 0x0005A960);

		SUBCASE("No inventory")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(nullptr, &moo_pItem);
				const auto original_result = original(nullptr, &original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}

		SUBCASE("Items in belt")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				int belt_item_ids[4] = {};
				for (auto& belt_item_id : belt_item_ids)
				{
					// Some belt slots are left empty
					belt_item_id = static_cast<int>(random_unsigned_integer(0, items_record_count)) - 1;
				}

				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pGrids[INVGRID_BELT + 1]{};
				D2UnitStrc* moo_pBeltGridItems[16]{};
				D2UnitStrc moo_pBeltItems[4]{};
				D2UnitStrc moo_pItem{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pGrids[INVGRID_BELT + 1]{};
				D2UnitStrc* original_pBeltGridItems[16]{};
				D2UnitStrc original_pBeltItems[4]{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i, &belt_item_ids](
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc (&pGrids)[INVGRID_BELT + 1],
					D2UnitStrc* (&pBeltGridItems)[16],
					D2UnitStrc (&pBeltItems)[4],
					D2UnitStrc& pItem
				) {
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pGrids = pGrids;
					pInventory.nGridCount = INVGRID_BELT + 1;

					pGrids[INVGRID_BELT].nGridWidth = 16;
					pGrids[INVGRID_BELT].nGridHeight = 1;
					pGrids[INVGRID_BELT].ppItems = pBeltGridItems;

					for (auto j = 0; j < 4; ++j)
					{
						if (belt_item_ids[j] >= 0)
						{
							pBeltItems[j].dwUnitType = UNIT_ITEM;
							pBeltItems[j].dwClassId = belt_item_ids[j];
							pBeltGridItems[j] = &pBeltItems[j];
						}
					}

					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pInventory, moo_pGrids, moo_pBeltGridItems, moo_pBeltItems, moo_pItem);
				setup_data(original_pInventory, original_pGrids, original_pBeltGridItems, original_pBeltItems, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pInventory, &moo_pItem);
				const auto original_result = original(&original_pInventory, &original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9AA00 (#10771)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfUseable, dll_base + 0x0005AA00);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9AA70 (#10772)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetUniqueColumnFromItemsTxt, dll_base + 0x0005AA70);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9AB00 (#10773)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsQuestItem, dll_base + 0x0005AB00);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FD9AB90" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CalculateAdditionalCostsForChargedSkills, dll_base + 0x0005AB90);

		setup_skill_layer_packing(dll_base);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				const auto stats = sorted_stats({
					make_stat(STAT_ITEM_CHARGED_SKILL, make_skill_layer(i, random_unsigned_integer(1, 20)), (random_unsigned_integer(1, 255) << 8) + random_unsigned_integer(0, 255)),
					make_stat(STAT_ITEM_CHARGED_SKILL, make_skill_layer(random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 20)), (random_unsigned_integer(1, 255) << 8) + random_unsigned_integer(0, 255)),
				});

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				int nBaseCost = random_unsigned_integer(0, 100000);

				const auto setup_data = [&stats](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats
				) {
					pUnit.dwUnitType = UNIT_ITEM;
					setup_stat_list(pUnit, pStatListEx, pStats, stats, pFullStats, stats);
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStats, moo_pFullStats);
				setup_data(original_pUnit, original_pStatListEx, original_pStats, original_pFullStats);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nBaseCost);
				const auto original_result = original(&original_pUnit, nBaseCost);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FD9ACE0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CalculateAdditionalCostsForBonusStats, dll_base + 0x0005ACE0);

		setup_skill_layer_packing(dll_base);

		SUBCASE("")
		{
			const auto with_base_stat = GENERATE(false, true);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				// Input data
				// The layer is valid for stats encoding a skill id and a skill level
				const auto layer = make_skill_layer(random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 20));
				const auto value = static_cast<int>(random_unsigned_integer(1, 100));
				const auto sell_cost = static_cast<int>(random_unsigned_integer(0, 10000));
				const auto buy_cost = static_cast<int>(random_unsigned_integer(0, 10000));
				const auto rep_cost = static_cast<int>(random_unsigned_integer(0, 10000));

				const auto full_stats = sorted_stats({ make_stat(i, layer, value) });
				const auto stats = with_base_stat ? sorted_stats({ make_stat(i, layer, value / 2) }) : std::vector<D2StatStrc>{};

				D2UnitStrc moo_pItem{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				int moo_pSellCost{};
				int moo_pBuyCost{};
				int moo_pRepCost{};
				D2UnitStrc original_pItem{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				int original_pSellCost{};
				int original_pBuyCost{};
				int original_pRepCost{};
				unsigned int nDivisor = random_unsigned_integer(1, 4);

				const auto setup_data = [&stats, &full_stats, sell_cost, buy_cost, rep_cost](
					D2UnitStrc& pItem,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					int& pSellCost,
					int& pBuyCost,
					int& pRepCost
				) {
					pItem.dwUnitType = UNIT_ITEM;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, full_stats);
					pSellCost = sell_cost;
					pBuyCost = buy_cost;
					pRepCost = rep_cost;
				};

				setup_data(moo_pItem, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pSellCost, moo_pBuyCost, moo_pRepCost);
				setup_data(original_pItem, original_pStatListEx, original_pStats, original_pFullStats, original_pSellCost, original_pBuyCost, original_pRepCost);

				// Call both implementations
				sut(&moo_pItem, &moo_pSellCost, &moo_pBuyCost, &moo_pRepCost, nDivisor);
				original(&original_pItem, &original_pSellCost, &original_pBuyCost, &original_pRepCost, nDivisor);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pSellCost, original_pSellCost, "Comparing pSellCost");
				MOO_CHECK_EQ(moo_pBuyCost, original_pBuyCost, "Comparing pBuyCost");
				MOO_CHECK_EQ(moo_pRepCost, original_pRepCost, "Comparing pRepCost");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<SkillsTxtFixture<NpcTxtFixture<BooksTxtFixture<MonStatsTxtFixture<UniqueItemsTxtFixture<SetItemsTxtFixture<EmptyMagicAffixTxtFixture<NoopFixture>>>>>>>>>>>, "D2Common.0x6FD9B1C0" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CalculateTransactionCost, dll_base + 0x0005B1C0);

		setup_skill_layer_packing(dll_base);

		// Note: The magic affix table is empty, affixes do not contribute to the costs
		SUBCASE("")
		{
			const auto nTransactionType = GENERATE(TRANSACTIONTYPE_BUY, TRANSACTIONTYPE_SELL, TRANSACTIONTYPE_GAMBLE, TRANSACTIONTYPE_REPAIR);
			const auto item_flags = GENERATE(0u, static_cast<uint32_t>(IFLAG_IDENTIFIED), static_cast<uint32_t>(IFLAG_IDENTIFIED | IFLAG_ETHEREAL), static_cast<uint32_t>(IFLAG_STARTITEM), static_cast<uint32_t>(IFLAG_ISEAR));

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto quest_flags_size = static_cast<int>(sizeof(uint16_t) * NUM_QUEST_WORDS);
				const auto quest_flags = std::make_unique<uint8_t[]>(quest_flags_size);
				for (auto j = 0; j < quest_flags_size; ++j)
				{
					quest_flags[j] = random_unsigned_integer(0, 255);
				}

				const auto quality = random_unsigned_integer(ITEMQUAL_INFERIOR, ITEMQUAL_TEMPERED);
				const auto item_format = random_unsigned_integer(0, 1);
				// The file index is used for monster body parts as well as for unique and set items
				const auto file_index = random_unsigned_integer(0, std::min({ monstats_record_count, uniqueitems_record_count, setitems_record_count }) - 1);
				const auto book_id = random_unsigned_integer(0, books_record_count - 1);
				const auto ear_level = random_unsigned_integer(1, 99);
				const auto max_durability = static_cast<int>(random_unsigned_integer(1, 250));

				const auto item_stats = sorted_stats({
					make_stat(STAT_ARMORCLASS, 0, random_unsigned_integer(1, 200)),
					make_stat(STAT_QUANTITY, 0, random_unsigned_integer(1, 50)),
					make_stat(STAT_DURABILITY, 0, random_unsigned_integer(0, max_durability)),
					make_stat(STAT_MAXDURABILITY, 0, max_durability),
					make_stat(STAT_ITEM_INDESCTRUCTIBLE, 0, random_unsigned_integer(0, 7) == 0),
					make_stat(STAT_ITEM_CHARGED_SKILL, make_skill_layer(random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 20)), (random_unsigned_integer(1, 50) << 8) + random_unsigned_integer(0, 50)),
					make_stat(STAT_ITEM_REPLENISH_DURABILITY, 0, random_unsigned_integer(0, 1)),
					make_stat(STAT_ITEM_REPLENISH_QUANTITY, 0, random_unsigned_integer(0, 1)),
					make_stat(STAT_ITEM_EXTRA_STACK, 0, random_unsigned_integer(0, 20)),
				});

				const auto player_stats = sorted_stats({
					make_stat(STAT_LEVEL, 0, random_unsigned_integer(1, 99)),
					make_stat(STAT_ITEM_REDUCEDPRICES, 0, random_unsigned_integer(0, 20)),
				});

				D2UnitStrc moo_pPlayer{};
				D2StatListExStrc moo_pPlayerStatListEx{};
				std::vector<D2StatStrc> moo_pPlayerStats;
				std::vector<D2StatStrc> moo_pPlayerFullStats;
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pItemStatListEx{};
				std::vector<D2StatStrc> moo_pItemStats;
				std::vector<D2StatStrc> moo_pItemFullStats;
				D2BitBufferStrc moo_pQuestFlags{};
				std::unique_ptr<uint8_t[]> moo_pQuestFlagsBuffer;
				D2UnitStrc original_pPlayer{};
				D2StatListExStrc original_pPlayerStatListEx{};
				std::vector<D2StatStrc> original_pPlayerStats;
				std::vector<D2StatStrc> original_pPlayerFullStats;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pItemStatListEx{};
				std::vector<D2StatStrc> original_pItemStats;
				std::vector<D2StatStrc> original_pItemFullStats;
				D2BitBufferStrc original_pQuestFlags{};
				std::unique_ptr<uint8_t[]> original_pQuestFlagsBuffer;
				D2C_Difficulties nDifficulty = static_cast<D2C_Difficulties>(random_unsigned_integer(DIFFMODE_NORMAL, DIFFMODE_HELL));
				int nVendorId = npc_txt[random_unsigned_integer(0, npc_record_count - 1)].dwNpc;

				const auto setup_data = [&, i](
					D2UnitStrc& pPlayer,
					D2StatListExStrc& pPlayerStatListEx,
					std::vector<D2StatStrc>& pPlayerStats,
					std::vector<D2StatStrc>& pPlayerFullStats,
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pItemStatListEx,
					std::vector<D2StatStrc>& pItemStats,
					std::vector<D2StatStrc>& pItemFullStats,
					D2BitBufferStrc& pQuestFlags,
					std::unique_ptr<uint8_t[]>& pQuestFlagsBuffer
				) {
					pPlayer.dwUnitType = UNIT_PLAYER;
					setup_stat_list(pPlayer, pPlayerStatListEx, pPlayerStats, player_stats, pPlayerFullStats, player_stats);

					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = item_flags;
					pItemData.dwQualityNo = quality;
					pItemData.wItemFormat = item_format;
					pItemData.dwFileIndex = file_index;
					pItemData.wMagicSuffix[0] = book_id;
					pItemData.nEarLvl = ear_level;
					setup_stat_list(pItem, pItemStatListEx, pItemStats, item_stats, pItemFullStats, item_stats);

					pQuestFlagsBuffer = std::make_unique<uint8_t[]>(quest_flags_size);
					std::memcpy(pQuestFlagsBuffer.get(), quest_flags.get(), quest_flags_size);
					BITMANIP_Initialize(&pQuestFlags, pQuestFlagsBuffer.get(), quest_flags_size);
				};

				setup_data(moo_pPlayer, moo_pPlayerStatListEx, moo_pPlayerStats, moo_pPlayerFullStats, moo_pItem, moo_pItemData, moo_pItemStatListEx, moo_pItemStats, moo_pItemFullStats, moo_pQuestFlags, moo_pQuestFlagsBuffer);
				setup_data(original_pPlayer, original_pPlayerStatListEx, original_pPlayerStats, original_pPlayerFullStats, original_pItem, original_pItemData, original_pItemStatListEx, original_pItemStats, original_pItemFullStats, original_pQuestFlags, original_pQuestFlagsBuffer);

				// Call both implementations
				const auto moo_result = sut(&moo_pPlayer, &moo_pItem, nDifficulty, &moo_pQuestFlags, nVendorId, nTransactionType);
				const auto original_result = original(&original_pPlayer, &original_pItem, nDifficulty, &original_pQuestFlags, nVendorId, nTransactionType);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
				auto moo_quest_flags = DynamicArray<uint8_t>{ moo_pQuestFlagsBuffer.get(), quest_flags_size };
				auto original_quest_flags = DynamicArray<uint8_t>{ original_pQuestFlagsBuffer.get(), quest_flags_size };
				MOO_CHECK_EQ(moo_quest_flags, original_quest_flags, "Comparing pQuestFlags buffer");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>>>, "D2Common.0x6FD9CB50" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CalculateAdditionalCostsForItemSkill, dll_base + 0x0005CB50);

		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto sell_cost = static_cast<int>(random_unsigned_integer(0, 100000));
				const auto buy_cost = static_cast<int>(random_unsigned_integer(0, 100000));
				const auto rep_cost = static_cast<int>(random_unsigned_integer(0, 100000));

				const auto stats = sorted_stats({
					make_stat(STAT_ITEM_SINGLESKILL, random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 3)),
					make_stat(STAT_ITEM_SINGLESKILL, random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 3)),
				});

				D2UnitStrc moo_pItem{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				int moo_pSellCost{};
				int moo_pBuyCost{};
				int moo_pRepCost{};
				D2UnitStrc original_pItem{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				int original_pSellCost{};
				int original_pBuyCost{};
				int original_pRepCost{};
				unsigned int nDivisor = random_unsigned_integer(1, 4);

				const auto setup_data = [i, &stats, sell_cost, buy_cost, rep_cost](
					D2UnitStrc& pItem,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					int& pSellCost,
					int& pBuyCost,
					int& pRepCost
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);
					pSellCost = sell_cost;
					pBuyCost = buy_cost;
					pRepCost = rep_cost;
				};

				setup_data(moo_pItem, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pSellCost, moo_pBuyCost, moo_pRepCost);
				setup_data(original_pItem, original_pStatListEx, original_pStats, original_pFullStats, original_pSellCost, original_pBuyCost, original_pRepCost);

				// Call both implementations
				sut(&moo_pItem, &moo_pSellCost, &moo_pBuyCost, &moo_pRepCost, nDivisor);
				original(&original_pItem, &original_pSellCost, &original_pBuyCost, &original_pRepCost, nDivisor);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pSellCost, original_pSellCost, "Comparing pSellCost");
				MOO_CHECK_EQ(moo_pBuyCost, original_pBuyCost, "Comparing pBuyCost");
				MOO_CHECK_EQ(moo_pRepCost, original_pRepCost, "Comparing pRepCost");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9CDC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckUnitFlagEx, dll_base + 0x0005CDC0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				const auto flags = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				int nFlag = (1 << i);

				const auto setup_data = [flags](
					D2UnitStrc& pUnit
				) {
					pUnit.dwFlagEx = flags;
				};

				setup_data(moo_pUnit);
				setup_data(original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nFlag);
				const auto original_result = original(&original_pUnit, nFlag);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<SkillsTxtFixture<NpcTxtFixture<BooksTxtFixture<MonStatsTxtFixture<UniqueItemsTxtFixture<SetItemsTxtFixture<EmptyMagicAffixTxtFixture<NoopFixture>>>>>>>>>>>, "D2Common.0x6FD9CDE0 (#10775)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetTransactionCost, dll_base + 0x0005CDE0);

		setup_skill_layer_packing(dll_base);

		// Note: The magic affix table is empty, affixes do not contribute to the costs
		SUBCASE("")
		{
			const auto nTransactionType = GENERATE(TRANSACTIONTYPE_BUY, TRANSACTIONTYPE_SELL, TRANSACTIONTYPE_GAMBLE, TRANSACTIONTYPE_REPAIR);
			const auto item_flags = GENERATE(0u, static_cast<uint32_t>(IFLAG_IDENTIFIED), static_cast<uint32_t>(IFLAG_IDENTIFIED | IFLAG_ETHEREAL), static_cast<uint32_t>(IFLAG_STARTITEM), static_cast<uint32_t>(IFLAG_ISEAR));

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto quest_flags_size = static_cast<int>(sizeof(uint16_t) * NUM_QUEST_WORDS);
				const auto quest_flags = std::make_unique<uint8_t[]>(quest_flags_size);
				for (auto j = 0; j < quest_flags_size; ++j)
				{
					quest_flags[j] = random_unsigned_integer(0, 255);
				}

				const auto quality = random_unsigned_integer(ITEMQUAL_INFERIOR, ITEMQUAL_TEMPERED);
				const auto item_format = random_unsigned_integer(0, 1);
				// The file index is used for monster body parts as well as for unique and set items
				const auto file_index = random_unsigned_integer(0, std::min({ monstats_record_count, uniqueitems_record_count, setitems_record_count }) - 1);
				const auto book_id = random_unsigned_integer(0, books_record_count - 1);
				const auto ear_level = random_unsigned_integer(1, 99);
				const auto max_durability = static_cast<int>(random_unsigned_integer(1, 250));

				const auto item_stats = sorted_stats({
					make_stat(STAT_ARMORCLASS, 0, random_unsigned_integer(1, 200)),
					make_stat(STAT_QUANTITY, 0, random_unsigned_integer(1, 50)),
					make_stat(STAT_DURABILITY, 0, random_unsigned_integer(0, max_durability)),
					make_stat(STAT_MAXDURABILITY, 0, max_durability),
					make_stat(STAT_ITEM_INDESCTRUCTIBLE, 0, random_unsigned_integer(0, 7) == 0),
					make_stat(STAT_ITEM_CHARGED_SKILL, make_skill_layer(random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 20)), (random_unsigned_integer(1, 50) << 8) + random_unsigned_integer(0, 50)),
					make_stat(STAT_ITEM_REPLENISH_DURABILITY, 0, random_unsigned_integer(0, 1)),
					make_stat(STAT_ITEM_REPLENISH_QUANTITY, 0, random_unsigned_integer(0, 1)),
					make_stat(STAT_ITEM_EXTRA_STACK, 0, random_unsigned_integer(0, 20)),
				});

				const auto player_stats = sorted_stats({
					make_stat(STAT_LEVEL, 0, random_unsigned_integer(1, 99)),
					make_stat(STAT_ITEM_REDUCEDPRICES, 0, random_unsigned_integer(0, 20)),
				});

				D2UnitStrc moo_pPlayer{};
				D2StatListExStrc moo_pPlayerStatListEx{};
				std::vector<D2StatStrc> moo_pPlayerStats;
				std::vector<D2StatStrc> moo_pPlayerFullStats;
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pItemStatListEx{};
				std::vector<D2StatStrc> moo_pItemStats;
				std::vector<D2StatStrc> moo_pItemFullStats;
				D2BitBufferStrc moo_pQuestFlags{};
				std::unique_ptr<uint8_t[]> moo_pQuestFlagsBuffer;
				D2UnitStrc original_pPlayer{};
				D2StatListExStrc original_pPlayerStatListEx{};
				std::vector<D2StatStrc> original_pPlayerStats;
				std::vector<D2StatStrc> original_pPlayerFullStats;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pItemStatListEx{};
				std::vector<D2StatStrc> original_pItemStats;
				std::vector<D2StatStrc> original_pItemFullStats;
				D2BitBufferStrc original_pQuestFlags{};
				std::unique_ptr<uint8_t[]> original_pQuestFlagsBuffer;
				D2C_Difficulties nDifficulty = static_cast<D2C_Difficulties>(random_unsigned_integer(DIFFMODE_NORMAL, DIFFMODE_HELL));
				int nVendorId = npc_txt[random_unsigned_integer(0, npc_record_count - 1)].dwNpc;

				const auto setup_data = [&, i](
					D2UnitStrc& pPlayer,
					D2StatListExStrc& pPlayerStatListEx,
					std::vector<D2StatStrc>& pPlayerStats,
					std::vector<D2StatStrc>& pPlayerFullStats,
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pItemStatListEx,
					std::vector<D2StatStrc>& pItemStats,
					std::vector<D2StatStrc>& pItemFullStats,
					D2BitBufferStrc& pQuestFlags,
					std::unique_ptr<uint8_t[]>& pQuestFlagsBuffer
				) {
					pPlayer.dwUnitType = UNIT_PLAYER;
					setup_stat_list(pPlayer, pPlayerStatListEx, pPlayerStats, player_stats, pPlayerFullStats, player_stats);

					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = item_flags;
					pItemData.dwQualityNo = quality;
					pItemData.wItemFormat = item_format;
					pItemData.dwFileIndex = file_index;
					pItemData.wMagicSuffix[0] = book_id;
					pItemData.nEarLvl = ear_level;
					setup_stat_list(pItem, pItemStatListEx, pItemStats, item_stats, pItemFullStats, item_stats);

					pQuestFlagsBuffer = std::make_unique<uint8_t[]>(quest_flags_size);
					std::memcpy(pQuestFlagsBuffer.get(), quest_flags.get(), quest_flags_size);
					BITMANIP_Initialize(&pQuestFlags, pQuestFlagsBuffer.get(), quest_flags_size);
				};

				setup_data(moo_pPlayer, moo_pPlayerStatListEx, moo_pPlayerStats, moo_pPlayerFullStats, moo_pItem, moo_pItemData, moo_pItemStatListEx, moo_pItemStats, moo_pItemFullStats, moo_pQuestFlags, moo_pQuestFlagsBuffer);
				setup_data(original_pPlayer, original_pPlayerStatListEx, original_pPlayerStats, original_pPlayerFullStats, original_pItem, original_pItemData, original_pItemStatListEx, original_pItemStats, original_pItemFullStats, original_pQuestFlags, original_pQuestFlagsBuffer);

				// Call both implementations
				const auto moo_result = sut(&moo_pPlayer, &moo_pItem, nDifficulty, &moo_pQuestFlags, nVendorId, nTransactionType);
				const auto original_result = original(&original_pPlayer, &original_pItem, nDifficulty, &original_pQuestFlags, nVendorId, nTransactionType);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
				auto moo_quest_flags = DynamicArray<uint8_t>{ moo_pQuestFlagsBuffer.get(), quest_flags_size };
				auto original_quest_flags = DynamicArray<uint8_t>{ original_pQuestFlagsBuffer.get(), quest_flags_size };
				MOO_CHECK_EQ(moo_quest_flags, original_quest_flags, "Comparing pQuestFlags buffer");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9CE10 (#10794)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetMaxStack, dll_base + 0x0005CE10);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9CE50 (#10795)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetTotalMaxStack, dll_base + 0x0005CE50);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9CEF0 (#10798)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSpawnStackFromItemId, dll_base + 0x0005CEF0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9CF30 (#10799)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSpawnStack, dll_base + 0x0005CF30);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9CFB0 (#10796)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetMinStackFromItemId, dll_base + 0x0005CFB0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9CFF0 (#10797)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetMinStack, dll_base + 0x0005CFF0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<BooksTxtFixture<NoopFixture>>>, "D2Common.0x6FD9D0F0 (#10804)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSpellIcon, dll_base + 0x0005D0F0);

		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Includes an invalid book id
				for (auto j = 0; j <= books_record_count; ++j)
				{
					// Input data
					D2UnitStrc moo_pItem{};
					D2ItemDataStrc moo_pItemData{};
					D2UnitStrc original_pItem{};
					D2ItemDataStrc original_pItemData{};

					const auto setup_data = [i, j](
						D2UnitStrc& pItem,
						D2ItemDataStrc& pItemData
					) {
						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = i;
						pItem.pItemData = &pItemData;
						pItemData.wMagicSuffix[0] = j;
					};

					setup_data(moo_pItem, moo_pItemData);
					setup_data(original_pItem, original_pItemData);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem);
					const auto original_result = original(&original_pItem);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D1E0 (#10805)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetDurWarnCount, dll_base + 0x0005D1E0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D260 (#10806)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetQtyWarnCount, dll_base + 0x0005D260);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D2E0 (#10807)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetStrengthBonus, dll_base + 0x0005D2E0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D310 (#10808)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetDexBonus, dll_base + 0x0005D310);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D340 (#10809)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfSocketableByItemId, dll_base + 0x0005D340);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D360 (#10810)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfSocketable, dll_base + 0x0005D360);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FD9D390 (#10811)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_HasDurability, dll_base + 0x0005D390);
		
		SUBCASE("destructible")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2StatListExStrc moo_pStatListEx{};
				D2StatStrc moo_pStat{};
				D2UnitStrc original_pItem{};
				D2StatListExStrc original_pStatListEx{};
				D2StatStrc original_pStat{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					D2StatListExStrc& pStatListEx,
					D2StatStrc& pStat
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.FullStats.pStat = &pStat;
					pStatListEx.FullStats.nStatCount = 1;
					pStat.nStat = STAT_MAXDURABILITY;
					pStat.nValue = 20;
				};

				setup_data(moo_pItem, moo_pStatListEx, moo_pStat);
				setup_data(original_pItem, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}

		SUBCASE("indestructible")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2StatListExStrc moo_pStatListEx{};
				D2StatStrc moo_pStat[2]{};
				D2UnitStrc original_pItem{};
				D2StatListExStrc original_pStatListEx{};
				D2StatStrc original_pStat[2]{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					D2StatListExStrc& pStatListEx,
					D2StatStrc(&pStat)[2]
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.FullStats.pStat = pStat;
					pStatListEx.FullStats.nStatCount = 2;
					pStat[0].nStat = STAT_MAXDURABILITY;
					pStat[0].nValue = 20;
					pStat[1].nStat = STAT_ITEM_INDESCTRUCTIBLE;
					pStat[1].nValue = 1;
				};

				setup_data(moo_pItem, moo_pStatListEx, moo_pStat);
				setup_data(original_pItem, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D3F0 (#10813)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetStaffMods, dll_base + 0x0005D3F0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D470 (#10814)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAllowedGemSocketsFromItemId, dll_base + 0x0005D470);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D490 (#10815)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetMaxSockets, dll_base + 0x0005D490);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FD9D580 (#10816)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSockets, dll_base + 0x0005D580);
		
		SUBCASE("")
		{
			// Input data
			const auto sockets = random_unsigned_integer(0, 6);

			D2UnitStrc moo_pItem{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pStat{};
			D2UnitStrc original_pItem{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pStat{};

			const auto setup_data = [sockets](
				D2UnitStrc& pItem,
				D2StatListExStrc& pStatListEx,
				D2StatStrc& pStat
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.FullStats.pStat = &pStat;
				pStatListEx.FullStats.nStatCount = 1;
				pStat.nStat = STAT_ITEM_NUMSOCKETS;
				pStat.nValue = sockets;
			};

			setup_data(moo_pItem, moo_pStatListEx, moo_pStat);
			setup_data(original_pItem, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FD9D5E0 (#10817)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AddSockets, dll_base + 0x0005D5E0);
		
		SUBCASE("")
		{
			const auto quality = GENERATE(ITEMQUAL_INFERIOR, ITEMQUAL_NORMAL, ITEMQUAL_SUPERIOR, ITEMQUAL_MAGIC, ITEMQUAL_SET, ITEMQUAL_RARE, ITEMQUAL_UNIQUE, ITEMQUAL_CRAFT, ITEMQUAL_TEMPERED);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto item_level = random_unsigned_integer(1, 99);
				const auto current_sockets = static_cast<int>(random_unsigned_integer(0, 6));
				const auto stats = current_sockets ? sorted_stats({ make_stat(STAT_ITEM_NUMSOCKETS, 0, current_sockets) }) : std::vector<D2StatStrc>{};

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				int nSockets = random_unsigned_integer(0, 7);

				const auto setup_data = [i, quality, item_level, &stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = quality;
					pItemData.dwItemLevel = item_level;
					// Reserve space for the socket stat
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats, stats.size() + 1);
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats);

				// Call both implementations
				sut(&moo_pItem, nSockets);
				original(&original_pItem, nSockets);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FD9D7C0 (#10818)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetSockets, dll_base + 0x0005D7C0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto item_level = random_unsigned_integer(1, 99);
				const auto current_sockets = static_cast<int>(random_unsigned_integer(0, 6));
				const auto stats = current_sockets ? sorted_stats({ make_stat(STAT_ITEM_NUMSOCKETS, 0, current_sockets) }) : std::vector<D2StatStrc>{};

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				int nSockets = random_unsigned_integer(0, 7);

				const auto setup_data = [i, item_level, &stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemLevel = item_level;
					// Reserve space for the socket stat
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats, stats.size() + 1);
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats);

				// Call both implementations
				sut(&moo_pItem, nSockets);
				original(&original_pItem, nSockets);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D900 (#10819)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetGemApplyTypeFromItemId, dll_base + 0x0005D900);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D940 (#10820)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetGemApplyType, dll_base + 0x0005D940);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D9D0 (#10821)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsSocketFiller, dll_base + 0x0005D9D0);
		
		SUBCASE("")
		{
			for (auto j = 0; j < itemtypes_record_count; ++j)
			{
				for (auto i = 0; i < items_record_count; ++i)
				{
					// Input data
					D2UnitStrc moo_pItem{};
					D2UnitStrc original_pItem{};

					const auto setup_data = [i](
						D2UnitStrc& pItem
					) {
						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = i;
					};

					setup_data(moo_pItem);
					setup_data(original_pItem);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem);
					const auto original_result = original(&original_pItem);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FD9D9E0 (#10822)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetRunesTxtRecordFromItem, dll_base + 0x0005D9E0);

		SUBCASE("")
		{
			const auto quality = GENERATE(ITEMQUAL_NORMAL, ITEMQUAL_SUPERIOR, ITEMQUAL_MAGIC);
			const auto matching_runes = GENERATE(false, true);
			const auto matching_sockets = GENERATE(false, true);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto socketed_item_count = static_cast<int>(random_unsigned_integer(1, 6));
				int socketed_item_ids[6] = {};
				for (auto& socketed_item_id : socketed_item_ids)
				{
					socketed_item_id = random_unsigned_integer(1, items_record_count - 1);
				}

				// A runeword which requires the socketed items and is valid for weapons and armor
				D2RunesTxt runes_txt{};
				runes_txt.nComplete = 1;
				runes_txt.wStringId = random_unsigned_integer(1, 0xFFFF);
				runes_txt.wIType[0] = ITEMTYPE_WEAPON;
				runes_txt.wIType[1] = ITEMTYPE_ANY_ARMOR;
				for (auto j = 0; j < socketed_item_count; ++j)
				{
					runes_txt.nRune[j] = matching_runes ? socketed_item_ids[j] : socketed_item_ids[j] + 1;
				}

				set_data_tables_value(dll_base, &D2DataTablesStrc::pRuneDataTables, D2RuneDataTbl{ 1, &runes_txt });

				const auto stats = sorted_stats({
					make_stat(STAT_ITEM_NUMSOCKETS, 0, matching_sockets ? socketed_item_count : socketed_item_count + 1),
				});

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pSocketedItems[6]{};
				D2ItemDataStrc moo_pSocketedItemsData[6]{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pSocketedItems[6]{};
				D2ItemDataStrc original_pSocketedItemsData[6]{};

				const auto setup_data = [i, quality, socketed_item_count, &socketed_item_ids, &stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2InventoryStrc& pInventory,
					D2UnitStrc (&pSocketedItems)[6],
					D2ItemDataStrc (&pSocketedItemsData)[6]
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItem.pInventory = &pInventory;
					pItemData.dwQualityNo = quality;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);

					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pItem;
					pInventory.pFirstItem = &pSocketedItems[0];
					pInventory.pLastItem = &pSocketedItems[socketed_item_count - 1];
					pInventory.dwItemCount = socketed_item_count;

					for (auto j = 0; j < socketed_item_count; ++j)
					{
						pSocketedItems[j].dwUnitType = UNIT_ITEM;
						pSocketedItems[j].dwClassId = socketed_item_ids[j];
						pSocketedItems[j].dwAnimMode = IMODE_SOCKETED;
						pSocketedItems[j].pItemData = &pSocketedItemsData[j];
						pSocketedItemsData[j].pExtraData.pParentInv = &pInventory;
						pSocketedItemsData[j].pExtraData.pPreviousItem = j > 0 ? &pSocketedItems[j - 1] : nullptr;
						pSocketedItemsData[j].pExtraData.pNextItem = j < socketed_item_count - 1 ? &pSocketedItems[j + 1] : nullptr;
					}
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pInventory, moo_pSocketedItems, moo_pSocketedItemsData);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats, original_pInventory, original_pSocketedItems, original_pSocketedItemsData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				set_data_tables_value(dll_base, &D2DataTablesStrc::pRuneDataTables, D2RuneDataTbl{});

				// Compare return values
				CHECK_EQ(moo_result, original_result);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9DE10 (#10802)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsMetalItem, dll_base + 0x0005DE10);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9DE50 (#10801)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckBitField1Flag4, dll_base + 0x0005DE50);

		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}

	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9DE90 (#10774)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsNotQuestItemByItemId, dll_base + 0x0005DE90);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9DEE0 (#10732)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetFileIndex, dll_base + 0x0005DEE0);
		
		SUBCASE("")
		{
			// Input data
			const auto file_index = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [file_index](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwFileIndex = file_index;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9DF60 (#10733)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetFileIndex, dll_base + 0x0005DF60);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			uint32_t dwFileIndex = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, dwFileIndex);
			original(&original_pItem, dwFileIndex);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9DFE0 (#11244)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetRealmData, dll_base + 0x0005DFE0);
		
		SUBCASE("")
		{
			// Input data
			const auto realm_data0 = random_unsigned_integer();
			const auto realm_data1 = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			int moo_pRealmData0{};
			int moo_pRealmData1{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int original_pRealmData0{};
			int original_pRealmData1{};

			const auto setup_data = [realm_data0, realm_data1](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData,
				int& pRealmData0,
				int& pRealmData1
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwRealmData[0] = realm_data0;
				pItemData.dwRealmData[1] = realm_data1;
			};

			setup_data(moo_pItem, moo_pItemData, moo_pRealmData0, moo_pRealmData1);
			setup_data(original_pItem, original_pItemData, original_pRealmData0, original_pRealmData1);

			// Call both implementations
			sut(&moo_pItem, &moo_pRealmData0, &moo_pRealmData1);
			original(&original_pItem, &original_pRealmData0, &original_pRealmData1);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			MOO_CHECK_EQ(moo_pRealmData0, original_pRealmData0, "Comparing pRealmData0");
			MOO_CHECK_EQ(moo_pRealmData1, original_pRealmData1, "Comparing pRealmData1");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9E070 (#11245)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetRealmData, dll_base + 0x0005E070);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int a2 = random_unsigned_integer();
			int a3 = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, a2, a3);
			original(&original_pItem, a2, a3);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9E0A0 (#10734)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetOwnerId, dll_base + 0x0005E0A0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			D2UnitGUID nOwnerGUID = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nOwnerGUID);
			original(&original_pItem, nOwnerGUID);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9E120 (#10735)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetOwnerId, dll_base + 0x0005E120);
		
		SUBCASE("")
		{
			// Input data
			const auto owner_guid = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [owner_guid](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwOwnerGUID = owner_guid;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9E1A0 (#10736)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsBodyItem, dll_base + 0x0005E1A0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9E2A0 (#10738)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsClassValidByItemId, dll_base + 0x0005E2A0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9E310 (#10737)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsClassValid, dll_base + 0x0005E310);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9E390 (#10739)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetClassOfClassSpecificItem, dll_base + 0x0005E390);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9E410 (#10823)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetWeaponClassId, dll_base + 0x0005E410);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9E480 (#10824)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetTransmogrifyFromItemId, dll_base + 0x0005E480);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				int nItemId = i;

				// Call both implementations
				const auto moo_result = sut(nItemId);
				const auto original_result = original(nItemId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9E4C0 (#10825)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetTransmogrify, dll_base + 0x0005E4C0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9E550 (#10826)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsMagSetRarUniCrfOrTmp, dll_base + 0x0005E550);
		
		SUBCASE("")
		{
			// Input data
			const auto quality = GENERATE(
				ITEMQUAL_INFERIOR,
				ITEMQUAL_NORMAL,
				ITEMQUAL_SUPERIOR,
				ITEMQUAL_MAGIC,
				ITEMQUAL_SET,
				ITEMQUAL_RARE,
				ITEMQUAL_UNIQUE,
				ITEMQUAL_CRAFT,
				ITEMQUAL_TEMPERED
			);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [quality](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwQualityNo = quality;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD9E580 (#10740)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsNotQuestItem, dll_base + 0x0005E580);
		
		SUBCASE("IFLAG_NOSELL set")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwItemFlags |= IFLAG_NOSELL;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}

		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9E5F0 (#10827)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetHitClassFromItem, dll_base + 0x0005E5F0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pItem
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pItem);
				setup_data(original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD9E670 (#10828)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_Is1Or2Handed, dll_base + 0x0005E670);
		
		SUBCASE("Player")
		{
			for (auto j = 0; j < NUMBER_OF_PLAYERCLASSES; ++j)
			{
				for (auto i = 0; i < items_record_count; ++i)
				{
					// Input data
					D2UnitStrc moo_pPlayer{};
					D2UnitStrc moo_pItem{};
					D2UnitStrc original_pPlayer{};
					D2UnitStrc original_pItem{};

					const auto setup_data = [i, j](
						D2UnitStrc& pPlayer,
						D2UnitStrc& pItem
					) {
						pPlayer.dwUnitType = UNIT_PLAYER;
						pPlayer.dwClassId = j;
						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = i;
					};

					setup_data(moo_pPlayer, moo_pItem);
					setup_data(original_pPlayer, original_pItem);

					// Call both implementations
					const auto moo_result = sut(&moo_pPlayer, &moo_pItem);
					const auto original_result = original(&original_pPlayer, &original_pItem);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				}
			}
		}

		SUBCASE("Monster")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pPlayer{};
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pPlayer{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i](
					D2UnitStrc& pPlayer,
					D2UnitStrc& pItem
				) {
					pPlayer.dwUnitType = UNIT_MONSTER;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pPlayer, moo_pItem);
				setup_data(original_pPlayer, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pPlayer, &moo_pItem);
				const auto original_result = original(&original_pPlayer, &original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<UniqueItemsTxtFixture<SetItemsTxtFixture<EmptyMagicAffixTxtFixture<NoopFixture>>>>>, "D2Common.0x6FD9E710 (#10829)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetColor, dll_base + 0x0005E710);

		// Note: The magic affix table is empty and items with socketed gems are not covered (the Gems table is not available)
		SUBCASE("Unique")
		{
			const int nTransType = GENERATE(0, 1);

			for (auto i = 0; i < uniqueitems_record_count; ++i)
			{
				// Input data
				const auto item_id = random_unsigned_integer(0, items_record_count - 1);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				uint8_t moo_pColor{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				uint8_t original_pColor{};

				const auto setup_data = [i, item_id](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					uint8_t& pColor
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = item_id;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = ITEMQUAL_UNIQUE;
					pItemData.dwFileIndex = i;
					pColor = 0xFF;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pColor);
				setup_data(original_pItem, original_pItemData, original_pColor);

				// Call both implementations
				const auto moo_result = sut(nullptr, &moo_pItem, &moo_pColor, nTransType);
				const auto original_result = original(nullptr, &original_pItem, &original_pColor, nTransType);

				// Compare return values
				CHECK_EQ(moo_result, original_result);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pColor, original_pColor, "Comparing pColor");
			}
		}

		SUBCASE("Set")
		{
			const int nTransType = GENERATE(0, 1);

			for (auto i = 0; i < setitems_record_count; ++i)
			{
				// Input data
				const auto item_id = random_unsigned_integer(0, items_record_count - 1);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				uint8_t moo_pColor{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				uint8_t original_pColor{};

				const auto setup_data = [i, item_id](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					uint8_t& pColor
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = item_id;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = ITEMQUAL_SET;
					pItemData.dwFileIndex = i;
					pColor = 0xFF;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pColor);
				setup_data(original_pItem, original_pItemData, original_pColor);

				// Call both implementations
				const auto moo_result = sut(nullptr, &moo_pItem, &moo_pColor, nTransType);
				const auto original_result = original(nullptr, &original_pItem, &original_pColor, nTransType);

				// Compare return values
				CHECK_EQ(moo_result, original_result);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pColor, original_pColor, "Comparing pColor");
			}
		}

		SUBCASE("Other qualities")
		{
			const int nTransType = GENERATE(0, 1);
			const auto quality = GENERATE(ITEMQUAL_INFERIOR, ITEMQUAL_NORMAL, ITEMQUAL_SUPERIOR, ITEMQUAL_MAGIC, ITEMQUAL_RARE, ITEMQUAL_CRAFT, ITEMQUAL_TEMPERED);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto item_level = random_unsigned_integer(1, 99);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				uint8_t moo_pColor{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				uint8_t original_pColor{};

				const auto setup_data = [i, quality, item_level](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					uint8_t& pColor
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = quality;
					pItemData.dwItemLevel = item_level;
					pItemData.dwItemFlags = IFLAG_SOCKETED;
					pColor = 0xFF;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pColor);
				setup_data(original_pItem, original_pItemData, original_pColor);

				// Call both implementations
				const auto moo_result = sut(nullptr, &moo_pItem, &moo_pColor, nTransType);
				const auto original_result = original(nullptr, &original_pItem, &original_pColor, nTransType);

				// Compare return values
				CHECK_EQ(moo_result, original_result);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pColor, original_pColor, "Comparing pColor");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SetItemsTxtFixture<NoopFixture>, "D2Common.0x6FD9EE70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSetItemsTxtRecord, dll_base + 0x0005EE70);
		
		SUBCASE("")
		{
			for (auto i = 0; i < setitems_record_count; ++i)
			{
				int nRecordId = i;

				// Call both implementations
				const auto moo_result = sut(nRecordId);
				const auto original_result = original(nRecordId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FD9EEA0 (#10830)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsImbueable, dll_base + 0x0005EEA0);
		
		SUBCASE("")
		{
			const auto item_flags = GENERATE(0u, static_cast<uint32_t>(IFLAG_NOSELL), static_cast<uint32_t>(IFLAG_SOCKETED), static_cast<uint32_t>(IFLAG_BROKEN), static_cast<uint32_t>(IFLAG_IDENTIFIED));
			const auto with_socketed_item = GENERATE(0, 1);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto quality = random_unsigned_integer(ITEMQUAL_INFERIOR, ITEMQUAL_TEMPERED);
				const auto flags_ex = random_unsigned_integer(0, 1) ? static_cast<uint32_t>(UNITFLAGEX_ISEXPANSION) : 0u;
				const auto socketed_item_id = random_unsigned_integer(0, items_record_count - 1);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pSocketedItem{};
				D2ItemDataStrc moo_pSocketedItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pSocketedItem{};
				D2ItemDataStrc original_pSocketedItemData{};

				const auto setup_data = [i, item_flags, with_socketed_item, quality, flags_ex, socketed_item_id](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2InventoryStrc& pInventory,
					D2UnitStrc& pSocketedItem,
					D2ItemDataStrc& pSocketedItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.dwFlagEx = flags_ex;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = item_flags;
					pItemData.dwQualityNo = quality;

					if (with_socketed_item)
					{
						pItem.pInventory = &pInventory;
						pInventory.dwSignature = D2C_InventoryHeader;
						pInventory.pOwner = &pItem;
						pInventory.pFirstItem = &pSocketedItem;
						pInventory.pLastItem = &pSocketedItem;
						pInventory.dwItemCount = 1;

						pSocketedItem.dwUnitType = UNIT_ITEM;
						pSocketedItem.dwClassId = socketed_item_id;
						pSocketedItem.dwAnimMode = IMODE_SOCKETED;
						pSocketedItem.pItemData = &pSocketedItemData;
						pSocketedItemData.pExtraData.pParentInv = &pInventory;
					}
				};

				setup_data(moo_pItem, moo_pItemData, moo_pInventory, moo_pSocketedItem, moo_pSocketedItemData);
				setup_data(original_pItem, original_pItemData, original_pInventory, original_pSocketedItem, original_pSocketedItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FD9F080 (#10832)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsPersonalizable, dll_base + 0x0005F080);
		
		SUBCASE("With IFLAG_NOSELL")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags |= IFLAG_NOSELL;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}

		SUBCASE("With IFLAG_BROKEN")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags |= IFLAG_BROKEN;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}

		SUBCASE("With IFLAG_PERSONALIZED")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags |= IFLAG_PERSONALIZED;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}

		SUBCASE("Without flags")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FD9F260 (#10831)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsSocketable, dll_base + 0x0005F260);
		
		SUBCASE("")
		{
			const auto item_flags = GENERATE(0u, static_cast<uint32_t>(IFLAG_NOSELL), static_cast<uint32_t>(IFLAG_SOCKETED), static_cast<uint32_t>(IFLAG_BROKEN), static_cast<uint32_t>(IFLAG_IDENTIFIED));
			const auto with_socketed_item = GENERATE(0, 1);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto quality = random_unsigned_integer(ITEMQUAL_INFERIOR, ITEMQUAL_TEMPERED);
				const auto item_level = random_unsigned_integer(1, 99);
				const auto sockets = random_unsigned_integer(0, 1) * random_unsigned_integer(1, 6);
				const auto stats = sockets ? sorted_stats({ make_stat(STAT_ITEM_NUMSOCKETS, 0, sockets) }) : std::vector<D2StatStrc>{};
				const auto socketed_item_id = random_unsigned_integer(0, items_record_count - 1);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pSocketedItem{};
				D2ItemDataStrc moo_pSocketedItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pSocketedItem{};
				D2ItemDataStrc original_pSocketedItemData{};

				const auto setup_data = [i, item_flags, with_socketed_item, quality, item_level, &stats, socketed_item_id](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2InventoryStrc& pInventory,
					D2UnitStrc& pSocketedItem,
					D2ItemDataStrc& pSocketedItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = item_flags;
					pItemData.dwQualityNo = quality;
					pItemData.dwItemLevel = item_level;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);

					if (with_socketed_item)
					{
						pItem.pInventory = &pInventory;
						pInventory.dwSignature = D2C_InventoryHeader;
						pInventory.pOwner = &pItem;
						pInventory.pFirstItem = &pSocketedItem;
						pInventory.pLastItem = &pSocketedItem;
						pInventory.dwItemCount = 1;

						pSocketedItem.dwUnitType = UNIT_ITEM;
						pSocketedItem.dwClassId = socketed_item_id;
						pSocketedItem.dwAnimMode = IMODE_SOCKETED;
						pSocketedItem.pItemData = &pSocketedItemData;
						pSocketedItemData.pExtraData.pParentInv = &pInventory;
					}
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pInventory, moo_pSocketedItem, moo_pSocketedItemData);
				setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats, original_pInventory, original_pSocketedItem, original_pSocketedItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<SkillsTxtFixture<NpcTxtFixture<BooksTxtFixture<MonStatsTxtFixture<UniqueItemsTxtFixture<SetItemsTxtFixture<EmptyMagicAffixTxtFixture<NoopFixture>>>>>>>>>>, "D2Common.0x6FD9F490 (#10877)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAllRepairCosts, dll_base + 0x0005F490);

		setup_skill_layer_packing(dll_base);

		// Note: The magic affix table is empty, affixes do not contribute to the costs
		SUBCASE("")
		{
			for (auto repetition = 0; repetition < 200; ++repetition)
			{
				// Input data
				const auto quest_flags_size = static_cast<int>(sizeof(uint16_t) * NUM_QUEST_WORDS);
				const auto quest_flags = std::make_unique<uint8_t[]>(quest_flags_size);
				for (auto j = 0; j < quest_flags_size; ++j)
				{
					quest_flags[j] = random_unsigned_integer(0, 255);
				}

				const auto player_stats = sorted_stats({
					make_stat(STAT_LEVEL, 0, random_unsigned_integer(1, 99)),
					make_stat(STAT_ITEM_REDUCEDPRICES, 0, random_unsigned_integer(0, 20)),
				});

				// Some body locations are left empty
				int item_ids[NUM_BODYLOC] = {};
				uint32_t item_flags[NUM_BODYLOC] = {};
				uint32_t item_qualities[NUM_BODYLOC] = {};
				std::vector<D2StatStrc> item_stats[NUM_BODYLOC];
				for (auto j = 0; j < NUM_BODYLOC; ++j)
				{
					const auto max_durability = static_cast<int>(random_unsigned_integer(1, 250));

					item_ids[j] = static_cast<int>(random_unsigned_integer(0, items_record_count)) - 1;
					item_flags[j] = IFLAG_IDENTIFIED | (random_unsigned_integer(0, 3) == 0 ? IFLAG_ETHEREAL : 0);
					item_qualities[j] = random_unsigned_integer(ITEMQUAL_INFERIOR, ITEMQUAL_TEMPERED);
					item_stats[j] = sorted_stats({
						make_stat(STAT_ARMORCLASS, 0, random_unsigned_integer(1, 200)),
						make_stat(STAT_QUANTITY, 0, random_unsigned_integer(1, 50)),
						make_stat(STAT_DURABILITY, 0, random_unsigned_integer(0, max_durability)),
						make_stat(STAT_MAXDURABILITY, 0, max_durability),
						make_stat(STAT_ITEM_CHARGED_SKILL, make_skill_layer(random_unsigned_integer(0, skills_record_count - 1), random_unsigned_integer(1, 20)), (random_unsigned_integer(1, 50) << 8) + random_unsigned_integer(0, 50)),
					});
				}

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pUnitStatListEx{};
				std::vector<D2StatStrc> moo_pUnitStats;
				std::vector<D2StatStrc> moo_pUnitFullStats;
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pGrids[INVGRID_BODYLOC + 1]{};
				D2UnitStrc* moo_pBodyLocGridItems[13]{};
				D2UnitStrc moo_pItems[NUM_BODYLOC]{};
				D2ItemDataStrc moo_pItemsData[NUM_BODYLOC]{};
				D2StatListExStrc moo_pItemsStatListEx[NUM_BODYLOC]{};
				std::vector<D2StatStrc> moo_pItemsStats[NUM_BODYLOC];
				std::vector<D2StatStrc> moo_pItemsFullStats[NUM_BODYLOC];
				D2BitBufferStrc moo_pQuestFlags{};
				std::unique_ptr<uint8_t[]> moo_pQuestFlagsBuffer;
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pUnitStatListEx{};
				std::vector<D2StatStrc> original_pUnitStats;
				std::vector<D2StatStrc> original_pUnitFullStats;
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pGrids[INVGRID_BODYLOC + 1]{};
				D2UnitStrc* original_pBodyLocGridItems[13]{};
				D2UnitStrc original_pItems[NUM_BODYLOC]{};
				D2ItemDataStrc original_pItemsData[NUM_BODYLOC]{};
				D2StatListExStrc original_pItemsStatListEx[NUM_BODYLOC]{};
				std::vector<D2StatStrc> original_pItemsStats[NUM_BODYLOC];
				std::vector<D2StatStrc> original_pItemsFullStats[NUM_BODYLOC];
				D2BitBufferStrc original_pQuestFlags{};
				std::unique_ptr<uint8_t[]> original_pQuestFlagsBuffer;
				int nNpcId = npc_txt[random_unsigned_integer(0, npc_record_count - 1)].dwNpc;
				D2C_Difficulties nDifficulty = static_cast<D2C_Difficulties>(random_unsigned_integer(DIFFMODE_NORMAL, DIFFMODE_HELL));

				const auto setup_data = [&player_stats, &item_ids, &item_flags, &item_qualities, &item_stats, &quest_flags, quest_flags_size](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pUnitStatListEx,
					std::vector<D2StatStrc>& pUnitStats,
					std::vector<D2StatStrc>& pUnitFullStats,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc (&pGrids)[INVGRID_BODYLOC + 1],
					D2UnitStrc* (&pBodyLocGridItems)[13],
					D2UnitStrc (&pItems)[NUM_BODYLOC],
					D2ItemDataStrc (&pItemsData)[NUM_BODYLOC],
					D2StatListExStrc (&pItemsStatListEx)[NUM_BODYLOC],
					std::vector<D2StatStrc> (&pItemsStats)[NUM_BODYLOC],
					std::vector<D2StatStrc> (&pItemsFullStats)[NUM_BODYLOC],
					D2BitBufferStrc& pQuestFlags,
					std::unique_ptr<uint8_t[]>& pQuestFlagsBuffer
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pInventory = &pInventory;
					setup_stat_list(pUnit, pUnitStatListEx, pUnitStats, player_stats, pUnitFullStats, player_stats);

					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.pGrids = pGrids;
					pInventory.nGridCount = INVGRID_BODYLOC + 1;

					pGrids[INVGRID_BODYLOC].nGridWidth = 13;
					pGrids[INVGRID_BODYLOC].nGridHeight = 1;
					pGrids[INVGRID_BODYLOC].ppItems = pBodyLocGridItems;

					for (auto j = 0; j < NUM_BODYLOC; ++j)
					{
						if (item_ids[j] >= 0)
						{
							pItems[j].dwUnitType = UNIT_ITEM;
							pItems[j].dwClassId = item_ids[j];
							pItems[j].dwAnimMode = IMODE_EQUIP;
							pItems[j].pItemData = &pItemsData[j];
							pItemsData[j].dwItemFlags = item_flags[j];
							pItemsData[j].dwQualityNo = item_qualities[j];
							pItemsData[j].nBodyLoc = j;
							pItemsData[j].pExtraData.pParentInv = &pInventory;
							setup_stat_list(pItems[j], pItemsStatListEx[j], pItemsStats[j], item_stats[j], pItemsFullStats[j], item_stats[j]);

							pBodyLocGridItems[j] = &pItems[j];
						}
					}

					pQuestFlagsBuffer = std::make_unique<uint8_t[]>(quest_flags_size);
					std::memcpy(pQuestFlagsBuffer.get(), quest_flags.get(), quest_flags_size);
					BITMANIP_Initialize(&pQuestFlags, pQuestFlagsBuffer.get(), quest_flags_size);
				};

				setup_data(moo_pUnit, moo_pUnitStatListEx, moo_pUnitStats, moo_pUnitFullStats, moo_pInventory, moo_pGrids, moo_pBodyLocGridItems, moo_pItems, moo_pItemsData, moo_pItemsStatListEx, moo_pItemsStats, moo_pItemsFullStats, moo_pQuestFlags, moo_pQuestFlagsBuffer);
				setup_data(original_pUnit, original_pUnitStatListEx, original_pUnitStats, original_pUnitFullStats, original_pInventory, original_pGrids, original_pBodyLocGridItems, original_pItems, original_pItemsData, original_pItemsStatListEx, original_pItemsStats, original_pItemsFullStats, original_pQuestFlags, original_pQuestFlagsBuffer);

				// Call both implementations
				const auto moo_result = sut(nullptr, &moo_pUnit, nNpcId, nDifficulty, &moo_pQuestFlags, nullptr);
				const auto original_result = original(nullptr, &original_pUnit, nNpcId, nDifficulty, &original_pQuestFlags, nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				for (auto j = 0; j < NUM_BODYLOC; ++j)
				{
					MOO_CHECK_EQ(moo_pItems[j], original_pItems[j], "Comparing pItems");
				}
				MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemStatCostTxtFixture<NoopFixture>>, "D2Common.0x6FD9F720 (#10833)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AreStackablesEqual, dll_base + 0x0005F720);

		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				for (auto repetition = 0; repetition < 10; ++repetition)
				{
					// Input data
					// The values are chosen from small ranges, so that both equal and different items are generated
					const int item_ids[2] = { i, random_unsigned_integer(0, 3) ? i : static_cast<int>(random_unsigned_integer(0, items_record_count - 1)) };
					uint32_t item_flags[2] = {};
					uint32_t item_qualities[2] = {};
					int file_indices[2] = {};
					std::vector<D2StatStrc> item_stats[2];
					for (auto j = 0; j < 2; ++j)
					{
						item_flags[j] = random_unsigned_integer(0, 3) == 0 ? IFLAG_ETHEREAL : 0;
						item_qualities[j] = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer(0, ITEMQUAL_TEMPERED) : ITEMQUAL_NORMAL;
						file_indices[j] = random_unsigned_integer(0, 3) == 0;
						item_stats[j] = sorted_stats({
							make_stat(STAT_MINDAMAGE, 0, random_unsigned_integer(0, 1)),
							make_stat(STAT_MAXDAMAGE, 0, random_unsigned_integer(0, 1)),
							make_stat(STAT_SECONDARY_MINDAMAGE, 0, random_unsigned_integer(0, 1)),
							make_stat(STAT_SECONDARY_MAXDAMAGE, 0, random_unsigned_integer(0, 1)),
							make_stat(STAT_ITEM_THROW_MINDAMAGE, 0, random_unsigned_integer(0, 1)),
							make_stat(STAT_ITEM_THROW_MAXDAMAGE, 0, random_unsigned_integer(0, 1)),
							make_stat(STAT_ITEM_NUMSOCKETS, 0, random_unsigned_integer(0, 7) == 0),
						});
					}

					D2UnitStrc moo_pItem1{};
					D2ItemDataStrc moo_pItemData1{};
					D2StatListExStrc moo_pStatListEx1{};
					std::vector<D2StatStrc> moo_pStats1;
					std::vector<D2StatStrc> moo_pFullStats1;
					D2UnitStrc moo_pItem2{};
					D2ItemDataStrc moo_pItemData2{};
					D2StatListExStrc moo_pStatListEx2{};
					std::vector<D2StatStrc> moo_pStats2;
					std::vector<D2StatStrc> moo_pFullStats2;
					D2UnitStrc original_pItem1{};
					D2ItemDataStrc original_pItemData1{};
					D2StatListExStrc original_pStatListEx1{};
					std::vector<D2StatStrc> original_pStats1;
					std::vector<D2StatStrc> original_pFullStats1;
					D2UnitStrc original_pItem2{};
					D2ItemDataStrc original_pItemData2{};
					D2StatListExStrc original_pStatListEx2{};
					std::vector<D2StatStrc> original_pStats2;
					std::vector<D2StatStrc> original_pFullStats2;

					const auto setup_data = [&item_ids, &item_flags, &item_qualities, &file_indices, &item_stats](
						D2UnitStrc& pItem1,
						D2ItemDataStrc& pItemData1,
						D2StatListExStrc& pStatListEx1,
						std::vector<D2StatStrc>& pStats1,
						std::vector<D2StatStrc>& pFullStats1,
						D2UnitStrc& pItem2,
						D2ItemDataStrc& pItemData2,
						D2StatListExStrc& pStatListEx2,
						std::vector<D2StatStrc>& pStats2,
						std::vector<D2StatStrc>& pFullStats2
					) {
						pItem1.dwUnitType = UNIT_ITEM;
						pItem1.dwClassId = item_ids[0];
						pItem1.pItemData = &pItemData1;
						pItemData1.dwItemFlags = item_flags[0];
						pItemData1.dwQualityNo = item_qualities[0];
						pItemData1.dwFileIndex = file_indices[0];
						setup_stat_list(pItem1, pStatListEx1, pStats1, item_stats[0], pFullStats1, item_stats[0]);

						pItem2.dwUnitType = UNIT_ITEM;
						pItem2.dwClassId = item_ids[1];
						pItem2.pItemData = &pItemData2;
						pItemData2.dwItemFlags = item_flags[1];
						pItemData2.dwQualityNo = item_qualities[1];
						pItemData2.dwFileIndex = file_indices[1];
						setup_stat_list(pItem2, pStatListEx2, pStats2, item_stats[1], pFullStats2, item_stats[1]);
					};

					setup_data(moo_pItem1, moo_pItemData1, moo_pStatListEx1, moo_pStats1, moo_pFullStats1, moo_pItem2, moo_pItemData2, moo_pStatListEx2, moo_pStats2, moo_pFullStats2);
					setup_data(original_pItem1, original_pItemData1, original_pStatListEx1, original_pStats1, original_pFullStats1, original_pItem2, original_pItemData2, original_pStatListEx2, original_pStats2, original_pFullStats2);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem1, &moo_pItem2);
					const auto original_result = original(&original_pItem1, &original_pItem2);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem1, original_pItem1, "Comparing pItem1");
					MOO_CHECK_EQ(moo_pItem2, original_pItem2, "Comparing pItem2");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemStatCostTxtFixture<NoopFixture>>, "D2Common.0x6FD9FA70 (#10834)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CanItemBeUsedForThrowSkill, dll_base + 0x0005FA70);

		SUBCASE("")
		{
			const auto with_quantity = GENERATE(false, true);
			const auto throwable = GENERATE(false, true);
			const auto reduced_stack = GENERATE(false, true);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				std::vector<D2StatStrc> stats;
				if (with_quantity)
				{
					stats.push_back(make_stat(STAT_QUANTITY, 0, random_unsigned_integer(1, 50)));
				}
				if (throwable)
				{
					stats.push_back(make_stat(STAT_ITEM_THROWABLE, 0, 1));
				}
				if (reduced_stack)
				{
					stats.push_back(make_stat(STAT_ITEM_EXTRA_STACK, 0, -static_cast<int>(random_unsigned_integer(1, 500))));
				}
				stats = sorted_stats(stats);

				D2UnitStrc moo_pItem{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc original_pItem{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;

				const auto setup_data = [i, &stats](
					D2UnitStrc& pItem,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);
				};

				setup_data(moo_pItem, moo_pStatListEx, moo_pStats, moo_pFullStats);
				setup_data(original_pItem, original_pStatListEx, original_pStats, original_pFullStats);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FB40 (#11079)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_11079_Return0, dll_base + 0x0005FB40);
		
		SUBCASE("")
		{
			int a1{};
			int a2{};

			// Call both implementations
			const auto moo_result = sut(a1, a2);
			const auto original_result = original(a1, a2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(SetItemsTxtFixture<SetsTxtFixture<NoopFixture>>, "D2Common.0x6FD9FB50 (#10836)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSetItemsMask, dll_base + 0x0005FB50);

		SUBCASE("")
		{
			const BOOL bDontIgnoreInputItem = GENERATE(FALSE, TRUE);

			for (auto i = 0; i < setitems_record_count; ++i)
			{
				// Input data
				// The first item is the set item which is passed to the function, the other items mostly belong to the same set
				std::vector<int> same_set_items;
				for (auto j = 0; j < setitems_record_count; ++j)
				{
					if (setitems_txt[j].nSetId == setitems_txt[i].nSetId)
					{
						same_set_items.push_back(j);
					}
				}

				constexpr auto item_count = 6;
				int file_indices[item_count] = {};
				uint32_t item_qualities[item_count] = {};
				uint32_t item_flags[item_count] = {};
				char node_pages[item_count] = {};
				for (auto j = 0; j < item_count; ++j)
				{
					file_indices[j] = j == 0 ? i : random_unsigned_integer(0, 4) ? same_set_items[random_unsigned_integer(0, same_set_items.size() - 1)] : random_unsigned_integer(0, setitems_record_count - 1);
					item_qualities[j] = j == 0 || random_unsigned_integer(0, 4) ? ITEMQUAL_SET : ITEMQUAL_UNIQUE;
					item_flags[j] = random_unsigned_integer(0, 7) == 0 ? IFLAG_BROKEN : random_unsigned_integer(0, 7) == 0 ? IFLAG_NOEQUIP : 0;
					node_pages[j] = random_unsigned_integer(0, 4) ? NODEPAGE_EQUIP : NODEPAGE_STORAGE;
				}

				D2UnitStrc moo_pPlayer{};
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pItems[item_count]{};
				D2ItemDataStrc moo_pItemsData[item_count]{};
				D2UnitStrc original_pPlayer{};
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pItems[item_count]{};
				D2ItemDataStrc original_pItemsData[item_count]{};

				const auto setup_data = [item_count, &file_indices, &item_qualities, &item_flags, &node_pages](
					D2UnitStrc& pPlayer,
					D2InventoryStrc& pInventory,
					D2UnitStrc (&pItems)[item_count],
					D2ItemDataStrc (&pItemsData)[item_count]
				) {
					pPlayer.dwUnitType = UNIT_PLAYER;
					pPlayer.pInventory = &pInventory;

					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pPlayer;
					pInventory.pFirstItem = &pItems[0];
					pInventory.pLastItem = &pItems[item_count - 1];
					pInventory.dwItemCount = item_count;

					for (auto j = 0; j < item_count; ++j)
					{
						pItems[j].dwUnitType = UNIT_ITEM;
						pItems[j].pItemData = &pItemsData[j];
						pItemsData[j].dwQualityNo = item_qualities[j];
						pItemsData[j].dwFileIndex = file_indices[j];
						pItemsData[j].dwItemFlags = item_flags[j];
						pItemsData[j].pExtraData.pParentInv = &pInventory;
						pItemsData[j].pExtraData.nNodePosOther = node_pages[j];
						pItemsData[j].pExtraData.pPreviousItem = j > 0 ? &pItems[j - 1] : nullptr;
						pItemsData[j].pExtraData.pNextItem = j < item_count - 1 ? &pItems[j + 1] : nullptr;
					}
				};

				setup_data(moo_pPlayer, moo_pInventory, moo_pItems, moo_pItemsData);
				setup_data(original_pPlayer, original_pInventory, original_pItems, original_pItemsData);

				// Call both implementations
				const auto moo_result = sut(&moo_pPlayer, &moo_pItems[0], bDontIgnoreInputItem);
				const auto original_result = original(&original_pPlayer, &original_pItems[0], bDontIgnoreInputItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
				for (auto j = 0; j < item_count; ++j)
				{
					MOO_CHECK_EQ(moo_pItems[j], original_pItems[j], "Comparing pItems");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SetItemsTxtFixture<NoopFixture>, "D2Common.0x6FD9FD80 (#10838)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSetItemsTxtRecordFromItem, dll_base + 0x0005FD80);
		
		SUBCASE("")
		{
			for (auto i = 0; i < setitems_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = ITEMQUAL_SET;
					pItemData.dwFileIndex = i;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FE20 (#10839)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CanBeEquipped, dll_base + 0x0005FE20);
		
		SUBCASE("IFLAG_BROKEN set")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwItemFlags |= IFLAG_BROKEN;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, false);
		}

		SUBCASE("IFLAG_NOEQUIP set")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwItemFlags |= IFLAG_NOEQUIP;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, false);
		}

		SUBCASE("equippable")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, true);
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<ExperienceTxtFixture<EmptyMagicAffixTxtFixture<NoopFixture>>>>>, "D2Common.0x6FD9FE70 (#10840)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsCharmUsable, dll_base + 0x0005FE70);

		// Note: Unique and set items are not covered, the magic affix table is empty
		SUBCASE("")
		{
			const auto item_flags = GENERATE(0u, static_cast<uint32_t>(IFLAG_IDENTIFIED), static_cast<uint32_t>(IFLAG_IDENTIFIED | IFLAG_BROKEN), static_cast<uint32_t>(IFLAG_IDENTIFIED | IFLAG_NOEQUIP));
			const auto inventory_page = GENERATE(INVPAGE_INVENTORY, INVPAGE_CUBE);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const D2C_ItemQualities qualities[] = { ITEMQUAL_INFERIOR, ITEMQUAL_NORMAL, ITEMQUAL_SUPERIOR, ITEMQUAL_MAGIC, ITEMQUAL_RARE, ITEMQUAL_CRAFT, ITEMQUAL_TEMPERED };
				const auto quality = qualities[random_unsigned_integer(0, std::size(qualities) - 1)];
				const auto player_class = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);

				const auto item_stats = sorted_stats({
					make_stat(STAT_QUANTITY, 0, random_unsigned_integer(0, 50)),
					make_stat(STAT_ITEM_REQ_PERCENT, 0, static_cast<int>(random_unsigned_integer(0, 100)) - 50),
					make_stat(STAT_ITEM_LEVELREQ, 0, random_unsigned_integer(0, 10)),
				});

				const auto player_stats = sorted_stats({
					make_stat(STAT_STRENGTH, 0, random_unsigned_integer(0, 200)),
					make_stat(STAT_DEXTERITY, 0, random_unsigned_integer(0, 200)),
					make_stat(STAT_LEVEL, 0, random_unsigned_integer(1, 99)),
				});

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pItemStatListEx{};
				std::vector<D2StatStrc> moo_pItemStats;
				std::vector<D2StatStrc> moo_pItemFullStats;
				D2UnitStrc moo_pPlayer{};
				D2StatListExStrc moo_pPlayerStatListEx{};
				std::vector<D2StatStrc> moo_pPlayerStats;
				std::vector<D2StatStrc> moo_pPlayerFullStats;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pItemStatListEx{};
				std::vector<D2StatStrc> original_pItemStats;
				std::vector<D2StatStrc> original_pItemFullStats;
				D2UnitStrc original_pPlayer{};
				D2StatListExStrc original_pPlayerStatListEx{};
				std::vector<D2StatStrc> original_pPlayerStats;
				std::vector<D2StatStrc> original_pPlayerFullStats;

				const auto setup_data = [i, item_flags, quality, inventory_page, player_class, &item_stats, &player_stats](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pItemStatListEx,
					std::vector<D2StatStrc>& pItemStats,
					std::vector<D2StatStrc>& pItemFullStats,
					D2UnitStrc& pPlayer,
					D2StatListExStrc& pPlayerStatListEx,
					std::vector<D2StatStrc>& pPlayerStats,
					std::vector<D2StatStrc>& pPlayerFullStats
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.dwItemFlags = item_flags;
					pItemData.dwQualityNo = quality;
					pItemData.nInvPage = inventory_page;
					setup_stat_list(pItem, pItemStatListEx, pItemStats, item_stats, pItemFullStats, item_stats);

					pPlayer.dwUnitType = UNIT_PLAYER;
					pPlayer.dwClassId = player_class;
					setup_stat_list(pPlayer, pPlayerStatListEx, pPlayerStats, player_stats, pPlayerFullStats, player_stats);
				};

				setup_data(moo_pItem, moo_pItemData, moo_pItemStatListEx, moo_pItemStats, moo_pItemFullStats, moo_pPlayer, moo_pPlayerStatListEx, moo_pPlayerStats, moo_pPlayerFullStats);
				setup_data(original_pItem, original_pItemData, original_pItemStatListEx, original_pItemStats, original_pItemFullStats, original_pPlayer, original_pPlayerStatListEx, original_pPlayerStats, original_pPlayerFullStats);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &moo_pPlayer);
				const auto original_result = original(&original_pItem, &original_pPlayer);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FF00 (#10776)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetNoOfUnidItems, dll_base + 0x0005FF00);

		SUBCASE("")
		{
			for (auto item_count = 0; item_count <= 20; ++item_count)
			{
				// Input data
				std::vector<uint32_t> item_flags(item_count);
				std::vector<char> node_pages(item_count);
				std::vector<uint8_t> inventory_pages(item_count);
				for (auto j = 0; j < item_count; ++j)
				{
					item_flags[j] = random_unsigned_integer(0, 1) ? IFLAG_IDENTIFIED : 0;
					node_pages[j] = random_unsigned_integer(NODEPAGE_STORAGE, NODEPAGE_EQUIP);
					inventory_pages[j] = random_unsigned_integer(INVPAGE_INVENTORY, INVPAGE_BELT);
				}

				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				std::vector<D2UnitStrc> moo_pItems(item_count);
				std::vector<D2ItemDataStrc> moo_pItemsData(item_count);
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				std::vector<D2UnitStrc> original_pItems(item_count);
				std::vector<D2ItemDataStrc> original_pItemsData(item_count);

				const auto setup_data = [item_count, &item_flags, &node_pages, &inventory_pages](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					std::vector<D2UnitStrc>& pItems,
					std::vector<D2ItemDataStrc>& pItemsData
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pInventory = &pInventory;

					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.pFirstItem = item_count > 0 ? &pItems[0] : nullptr;
					pInventory.pLastItem = item_count > 0 ? &pItems[item_count - 1] : nullptr;
					pInventory.dwItemCount = item_count;

					for (auto j = 0; j < item_count; ++j)
					{
						pItems[j].dwUnitType = UNIT_ITEM;
						pItems[j].pItemData = &pItemsData[j];
						pItemsData[j].dwItemFlags = item_flags[j];
						pItemsData[j].nInvPage = inventory_pages[j];
						pItemsData[j].pExtraData.pParentInv = &pInventory;
						pItemsData[j].pExtraData.nNodePosOther = node_pages[j];
						pItemsData[j].pExtraData.pPreviousItem = j > 0 ? &pItems[j - 1] : nullptr;
						pItemsData[j].pExtraData.pNextItem = j < item_count - 1 ? &pItems[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pItems, moo_pItemsData);
				setup_data(original_pUnit, original_pInventory, original_pItems, original_pItemsData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				for (auto j = 0; j < item_count; ++j)
				{
					MOO_CHECK_EQ(moo_pItems[j], original_pItems[j], "Comparing pItems");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FF90 (#10841)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetBonusLifeBasedOnClass, dll_base + 0x0005FF90);
		
		SUBCASE("Player")
		{
			// Input data
			const auto class_id = GENERATE(
				PCLASS_AMAZON,
				PCLASS_SORCERESS,
				PCLASS_NECROMANCER,
				PCLASS_PALADIN,
				PCLASS_BARBARIAN,
				PCLASS_DRUID,
				PCLASS_ASSASSIN
			);

			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};
			int nValue = random_unsigned_integer(0, 65535);

			const auto setup_data = [class_id](
				D2UnitStrc& pPlayer
			) {
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = class_id;
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, nValue);
			const auto original_result = original(&original_pPlayer, nValue);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}

		SUBCASE("Monster")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};
			int nValue = random_unsigned_integer(0, 65535);

			const auto setup_data = [](
				D2UnitStrc& pPlayer
			) {
				pPlayer.dwUnitType = UNIT_MONSTER;
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, nValue);
			const auto original_result = original(&original_pPlayer, nValue);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FFE0 (#10842)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetBonusManaBasedOnClass, dll_base + 0x0005FFE0);
		
		SUBCASE("Player")
		{
			// Input data
			const auto class_id = GENERATE(
				PCLASS_AMAZON,
				PCLASS_SORCERESS,
				PCLASS_NECROMANCER,
				PCLASS_PALADIN,
				PCLASS_BARBARIAN,
				PCLASS_DRUID,
				PCLASS_ASSASSIN
			);

			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};
			int nValue = random_unsigned_integer(0, 65535);

			const auto setup_data = [class_id](
				D2UnitStrc& pPlayer
			) {
				pPlayer.dwUnitType = UNIT_PLAYER;
				pPlayer.dwClassId = class_id;
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, nValue);
			const auto original_result = original(&original_pPlayer, nValue);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}

		SUBCASE("Monster")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};
			int nValue = random_unsigned_integer(0, 65535);

			const auto setup_data = [](
				D2UnitStrc& pPlayer
			) {
				pPlayer.dwUnitType = UNIT_MONSTER;
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, nValue);
			const auto original_result = original(&original_pPlayer, nValue);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA0030 (#10875)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemFormat, dll_base + 0x00060030);
		
		SUBCASE("")
		{
			// Input data
			const auto item_format = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [item_format](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.wItemFormat = item_format;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA00B0 (#10876)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetItemFormat, dll_base + 0x000600B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};
			int nItemFormat = random_unsigned_integer(0, 65535);

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			sut(&moo_pItem, nItemFormat);
			original(&original_pItem, nItemFormat);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FDA0130 (#10878)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetWeaponAttackSpeed, dll_base + 0x00060130);

		// There are no fixtures for PlrType.txt, PlrMode.txt and AnimData.d2, minimal tables are set up instead
		const char* player_type_tokens[NUMBER_OF_PLAYERCLASSES] = { "AM", "SO", "NE", "PA", "BA", "DZ", "AI" };
		D2PlrModeTypeTxt player_types[PLRMODE_ATTACK1 + 1] = {};
		D2PlrModeTypeTxt player_modes[PLRMODE_ATTACK1 + 1] = {};
		for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
		{
			std::strcpy(player_types[i].szToken, player_type_tokens[i]);
		}
		std::strcpy(player_modes[PLRMODE_ATTACK1].szToken, "A1");

		set_data_tables_value(dll_base, &D2DataTablesStrc::pPlrModeDataTables, D2PlrModeDataTbl{ PLRMODE_ATTACK1 + 1, player_types, player_types, player_modes });

		SUBCASE("")
		{
			const auto with_anim_data_record = GENERATE(false, true);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// The function only accepts weapons
				D2UnitStrc weapon{};
				weapon.dwUnitType = UNIT_ITEM;
				weapon.dwClassId = i;
				if (!ITEMS_CheckItemTypeId(&weapon, ITEMTYPE_WEAPON))
				{
					continue;
				}

				// Input data
				const auto player_class = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);

				// The anim data record name consists of the class token, the mode token and the weapon class
				char weapon_class[4] = {};
				std::memcpy(weapon_class, &items_txt[i].dwWeapClass, 3);
				for (auto& c : weapon_class)
				{
					c = c == ' ' ? '\0' : static_cast<char>(std::toupper(c));
				}

				D2AnimDataRecordStrc anim_data_record{};
				std::snprintf(anim_data_record.szAnimDataName, sizeof(anim_data_record.szAnimDataName), "%s%s%s", player_type_tokens[player_class], "A1", weapon_class);
				anim_data_record.dwFrames = random_unsigned_integer(1, 30);
				anim_data_record.dwAnimSpeed = random_unsigned_integer(128, 256);

				uint8_t anim_data_record_hash = 0;
				for (auto c = anim_data_record.szAnimDataName; *c; ++c)
				{
					anim_data_record_hash += *c;
				}

				std::vector<uint8_t> anim_data_bucket(sizeof(D2AnimDataBucketStrc));
				reinterpret_cast<D2AnimDataBucketStrc*>(anim_data_bucket.data())->nbEntries = 1;
				std::memcpy(reinterpret_cast<D2AnimDataBucketStrc*>(anim_data_bucket.data())->aEntries, &anim_data_record, sizeof(anim_data_record));

				D2AnimDataBucketStrc empty_anim_data_bucket{};
				auto anim_data = std::make_unique<D2AnimDataTableStrc>();
				std::fill(std::begin(anim_data->pHashTableBucket), std::end(anim_data->pHashTableBucket), &empty_anim_data_bucket);
				if (with_anim_data_record)
				{
					anim_data->pHashTableBucket[anim_data_record_hash] = reinterpret_cast<D2AnimDataBucketStrc*>(anim_data_bucket.data());
				}
				anim_data->tDefaultRecord.dwFrames = 1;
				anim_data->tDefaultRecord.dwAnimSpeed = 256;

				set_data_tables_value(dll_base, &D2DataTablesStrc::pAnimData, anim_data.get());

				const auto stats = sorted_stats({
					make_stat(STAT_ATTACKRATE, 0, static_cast<int>(random_unsigned_integer(0, 100)) - 50),
					make_stat(STAT_ITEM_FASTERATTACKRATE, 0, random_unsigned_integer(0, 100)),
				});

				D2UnitStrc moo_pUnit{};
				D2UnitStrc moo_pWeapon{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc original_pUnit{};
				D2UnitStrc original_pWeapon{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;

				const auto setup_data = [i, player_class, &stats](
					D2UnitStrc& pUnit,
					D2UnitStrc& pWeapon,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = player_class;

					pWeapon.dwUnitType = UNIT_ITEM;
					pWeapon.dwClassId = i;
					setup_stat_list(pWeapon, pStatListEx, pStats, stats, pFullStats, stats);
				};

				setup_data(moo_pUnit, moo_pWeapon, moo_pStatListEx, moo_pStats, moo_pFullStats);
				setup_data(original_pUnit, original_pWeapon, original_pStatListEx, original_pStats, original_pFullStats);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pWeapon);
				const auto original_result = original(&original_pUnit, &original_pWeapon);

				set_data_tables_value(dll_base, &D2DataTablesStrc::pAnimData, nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pWeapon, original_pWeapon, "Comparing pWeapon");
			}
		}

		set_data_tables_value(dll_base, &D2DataTablesStrc::pPlrModeDataTables, D2PlrModeDataTbl{});
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDA02B0 (#10879)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_HasUsedCharges, dll_base + 0x000602B0);

		SUBCASE("")
		{
			for (auto charged_skill_count = 0; charged_skill_count <= 5; ++charged_skill_count)
			{
				for (auto repetition = 0; repetition < 20; ++repetition)
				{
					// Input data
					// The charges are often full, so that items with and without used charges are generated
					std::vector<D2StatStrc> stats;
					for (auto j = 0; j < charged_skill_count; ++j)
					{
						const auto max_charges = random_unsigned_integer(1, 255);
						const auto charges = random_unsigned_integer(0, 3) ? max_charges : random_unsigned_integer(0, max_charges);
						stats.push_back(make_stat(STAT_ITEM_CHARGED_SKILL, j, (max_charges << 8) + charges));
					}
					stats = sorted_stats(stats);

					D2UnitStrc moo_pItem{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStats;
					std::vector<D2StatStrc> moo_pFullStats;
					BOOL moo_pHasChargedSkills{};
					D2UnitStrc original_pItem{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStats;
					std::vector<D2StatStrc> original_pFullStats;
					BOOL original_pHasChargedSkills{};

					const auto setup_data = [&stats](
						D2UnitStrc& pItem,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStats,
						std::vector<D2StatStrc>& pFullStats,
						BOOL& pHasChargedSkills
					) {
						pItem.dwUnitType = UNIT_ITEM;
						setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats);
						pHasChargedSkills = 2;
					};

					setup_data(moo_pItem, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pHasChargedSkills);
					setup_data(original_pItem, original_pStatListEx, original_pStats, original_pFullStats, original_pHasChargedSkills);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem, &moo_pHasChargedSkills);
					const auto original_result = original(&original_pItem, &original_pHasChargedSkills);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
					MOO_CHECK_EQ(moo_pHasChargedSkills, original_pHasChargedSkills, "Comparing pHasChargedSkills");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA0340 (#10880)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsEthereal, dll_base + 0x00060340);
		
		SUBCASE("set")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwItemFlags |= IFLAG_ETHEREAL;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, IFLAG_ETHEREAL);
		}

		SUBCASE("not set")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pItem{};
			D2ItemDataStrc moo_pItemData{};
			D2UnitStrc original_pItem{};
			D2ItemDataStrc original_pItemData{};

			const auto setup_data = [flags](
				D2UnitStrc& pItem,
				D2ItemDataStrc& pItemData
			) {
				pItem.dwUnitType = UNIT_ITEM;
				pItem.pItemData = &pItemData;
				pItemData.dwItemFlags = flags & ~IFLAG_ETHEREAL;
			};

			setup_data(moo_pItem, moo_pItemData);
			setup_data(original_pItem, original_pItemData);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");

			CHECK_EQ(moo_result, 0);
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemsTxtFixture<NoopFixture>>, "D2Common.0x6FDA0370 (#10883)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetCompactItemDataFromBitstream, dll_base + 0x00060370);

		SUBCASE("")
		{
			const BOOL bCheckForHeader = GENERATE(FALSE, TRUE);
			const auto item_flags = GENERATE(0u, static_cast<uint32_t>(IFLAG_IDENTIFIED), static_cast<uint32_t>(IFLAG_ISEAR), static_cast<uint32_t>(IFLAG_LOWQUALITY), static_cast<uint32_t>(IFLAG_COMPACTSAVE));

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto valid_header = random_unsigned_integer(0, 7) != 0;
				const auto anim_mode = random_unsigned_integer(IMODE_STORED, IMODE_SOCKETED);

				std::vector<std::pair<uint32_t, int>> values;
				if (bCheckForHeader)
				{
					values.push_back({ valid_header ? 'MJ' : random_unsigned_integer(0, 0xFFFF), 16 });
				}
				values.push_back({ item_flags, 32 });
				values.push_back({ random_unsigned_integer(0, 1023), 10 });
				values.push_back({ anim_mode, 3 });
				if (anim_mode == IMODE_ONGROUND || anim_mode == IMODE_DROPPING)
				{
					values.push_back({ random_unsigned_integer(0, 0xFFFF), 16 });
					values.push_back({ random_unsigned_integer(0, 0xFFFF), 16 });
				}
				else
				{
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 7), 3 });
				}
				if (!(item_flags & IFLAG_ISEAR))
				{
					values.push_back({ items_txt[i].dwCode, 32 });
				}

				constexpr auto bitstream_size = 32;
				const auto bitstream = make_bitstream(values, bitstream_size);

				std::vector<uint8_t> moo_pBitstream;
				D2ItemSaveStrc moo_pItemSave{};
				std::vector<uint8_t> original_pBitstream;
				D2ItemSaveStrc original_pItemSave{};
				size_t nSize = bitstream_size;

				const auto setup_data = [&bitstream](
					std::vector<uint8_t>& pBitstream
				) {
					pBitstream = bitstream;
				};

				setup_data(moo_pBitstream);
				setup_data(original_pBitstream);

				// Call both implementations
				const auto moo_result = sut(moo_pBitstream.data(), nSize, bCheckForHeader, &moo_pItemSave);
				const auto original_result = original(original_pBitstream.data(), nSize, bCheckForHeader, &original_pItemSave);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");

				// The fields of D2ItemSaveStrc are not covered by its visitor (yet)
				CHECK_EQ(moo_pItemSave.nClassId, original_pItemSave.nClassId);
				CHECK_EQ(moo_pItemSave.nX, original_pItemSave.nX);
				CHECK_EQ(moo_pItemSave.nY, original_pItemSave.nY);
				CHECK_EQ(moo_pItemSave.nAnimMode, original_pItemSave.nAnimMode);
				CHECK_EQ(moo_pItemSave.dwFlags, original_pItemSave.dwFlags);
				CHECK_EQ(moo_pItemSave.nStorePage, original_pItemSave.nStorePage);
				CHECK_EQ(moo_pItemSave.nBodyloc, original_pItemSave.nBodyloc);
				CHECK_EQ(moo_pItemSave.nItemFileIndex, original_pItemSave.nItemFileIndex);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>>, "D2Common.0x6FDA0490 (#10882)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DecodeItemFromBitstream, dll_base + 0x00060490);

		// Note: Complete items are only covered if they are unidentified and without a header, as the magic properties of other items are stored
		// in newly allocated stat lists. The difficulty of quest items is stored in a newly allocated stat list as well, this is not covered either.
		// Ears and personalized items are not covered, as the name of the player is read until a terminating zero is found in the random bitstream.
		SUBCASE("")
		{
			const uint32_t dwVersion = GENERATE(87, 92, 96);
			const auto with_socketed_item_count = GENERATE(0, 1);

			for (auto i = 0; i < items_record_count; ++i)
			{
				const auto compact = items_txt[i].nCompactSave != 0;
				if (compact && dwVersion > 92 && items_txt[i].nQuest && items_txt[i].nQuestDiffCheck)
				{
					continue;
				}

				// Input data
				const BOOL bCheckForHeader = compact && random_unsigned_integer(0, 1);
				const auto valid_header = random_unsigned_integer(0, 7) != 0;
				const uint32_t complete_item_flags[] = { 0, IFLAG_SOCKETED, IFLAG_ETHEREAL, IFLAG_RUNEWORD, IFLAG_LOWQUALITY, IFLAG_SOCKETED | IFLAG_ETHEREAL };
				const auto item_flags = compact
					? static_cast<uint32_t>(IFLAG_COMPACTSAVE) | (random_unsigned_integer(0, 1) ? IFLAG_ETHEREAL : 0) | (random_unsigned_integer(0, 1) ? IFLAG_IDENTIFIED : 0)
					: complete_item_flags[random_unsigned_integer(0, std::size(complete_item_flags) - 1)];
				const auto anim_mode = random_unsigned_integer(IMODE_STORED, IMODE_SOCKETED);

				std::vector<std::pair<uint32_t, int>> values;
				if (bCheckForHeader)
				{
					values.push_back({ valid_header ? 'MJ' : random_unsigned_integer(0, 0xFFFF), 16 });
				}
				values.push_back({ item_flags, 32 });
				values.push_back({ random_unsigned_integer(0, 1023), 10 });
				values.push_back({ anim_mode, 3 });
				if (anim_mode == IMODE_ONGROUND || anim_mode == IMODE_DROPPING)
				{
					values.push_back({ random_unsigned_integer(0, 0xFFFF), 16 });
					values.push_back({ random_unsigned_integer(0, 0xFFFF), 16 });
				}
				else
				{
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 7), 3 });
				}
				values.push_back({ items_txt[i].dwCode, 32 });

				// The remaining bits are random
				constexpr auto bitstream_size = 32;
				const auto bitstream = make_bitstream(values, bitstream_size);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StaticPathStrc moo_pStaticPath{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				int moo_pSocketedItemCount{};
				BOOL moo_pFail{};
				std::vector<uint8_t> moo_pBitstream;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StaticPathStrc original_pStaticPath{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				int original_pSocketedItemCount{};
				BOOL original_pFail{};
				std::vector<uint8_t> original_pBitstream;
				size_t nSize = bitstream_size;

				const auto setup_data = [&bitstream](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StaticPathStrc& pStaticPath,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					std::vector<uint8_t>& pBitstream
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItem.pStaticPath = &pStaticPath;
					// The stat arrays are allocated by the implementations
					setup_stat_list(pItem, pStatListEx, pStats, {}, pFullStats, {});

					pBitstream = bitstream;
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStaticPath, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pBitstream);
				setup_data(original_pItem, original_pItemData, original_pStaticPath, original_pStatListEx, original_pStats, original_pFullStats, original_pBitstream);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, moo_pBitstream.data(), nSize, bCheckForHeader, with_socketed_item_count ? &moo_pSocketedItemCount : nullptr, dwVersion, &moo_pFail);
				const auto original_result = original(&original_pItem, original_pBitstream.data(), nSize, bCheckForHeader, with_socketed_item_count ? &original_pSocketedItemCount : nullptr, dwVersion, &original_pFail);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				check_stat_arrays_eq(moo_pStatListEx.Stats, original_pStatListEx.Stats, "Comparing pItem->pStatListEx->Stats");
				check_stat_arrays_eq(moo_pStatListEx.FullStats, original_pStatListEx.FullStats, "Comparing pItem->pStatListEx->FullStats");
				MOO_CHECK_EQ(moo_pSocketedItemCount, original_pSocketedItemCount, "Comparing pSocketedItemCount");
				MOO_CHECK_EQ(moo_pFail, original_pFail, "Comparing pFail");
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>>, "D2Common.0x6FDA0620")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DecodeItemBitstreamCompact, dll_base + 0x00060620);

		// Note: Ears are not covered, as the name of the player is read until a terminating zero is found in the random bitstream
		SUBCASE("")
		{
			const BOOL bCheckForHeader = GENERATE(FALSE, TRUE);
			const uint32_t dwVersion = GENERATE(87, 92, 96);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// The difficulty of quest items is stored in a newly allocated stat list, this is not covered
				if (dwVersion > 92 && items_txt[i].nQuest && items_txt[i].nQuestDiffCheck)
				{
					continue;
				}

				// Input data
				const auto item_flags = static_cast<uint32_t>(IFLAG_COMPACTSAVE) | (random_unsigned_integer(0, 1) ? IFLAG_ETHEREAL : 0) | (random_unsigned_integer(0, 1) ? IFLAG_IDENTIFIED : 0);
				const auto anim_mode = random_unsigned_integer(IMODE_STORED, IMODE_SOCKETED);

				std::vector<std::pair<uint32_t, int>> values;
				values.push_back({ random_unsigned_integer(0, 1023), 10 });
				values.push_back({ anim_mode, 3 });
				if (anim_mode == IMODE_ONGROUND || anim_mode == IMODE_DROPPING)
				{
					values.push_back({ random_unsigned_integer(0, 0xFFFF), 16 });
					values.push_back({ random_unsigned_integer(0, 0xFFFF), 16 });
				}
				else
				{
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 7), 3 });
				}
				values.push_back({ items_txt[i].dwCode, 32 });

				// The remaining bits (gold, realm data) are random
				constexpr auto bitstream_size = 32;
				const auto bitstream = make_bitstream(values, bitstream_size);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StaticPathStrc moo_pStaticPath{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2BitBufferStrc moo_pBuffer{};
				std::vector<uint8_t> moo_pBitstream;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StaticPathStrc original_pStaticPath{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2BitBufferStrc original_pBuffer{};
				std::vector<uint8_t> original_pBitstream;

				const auto setup_data = [item_flags, &bitstream](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StaticPathStrc& pStaticPath,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2BitBufferStrc& pBuffer,
					std::vector<uint8_t>& pBitstream
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItem.pStaticPath = &pStaticPath;
					pItemData.dwItemFlags = item_flags;
					// The stat arrays are allocated by the implementations
					setup_stat_list(pItem, pStatListEx, pStats, {}, pFullStats, {});

					pBitstream = bitstream;
					BITMANIP_Initialize(&pBuffer, pBitstream.data(), pBitstream.size());
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStaticPath, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pBuffer, moo_pBitstream);
				setup_data(original_pItem, original_pItemData, original_pStaticPath, original_pStatListEx, original_pStats, original_pFullStats, original_pBuffer, original_pBitstream);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &moo_pBuffer, bCheckForHeader, dwVersion);
				const auto original_result = original(&original_pItem, &original_pBuffer, bCheckForHeader, dwVersion);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				check_stat_arrays_eq(moo_pStatListEx.Stats, original_pStatListEx.Stats, "Comparing pItem->pStatListEx->Stats");
				check_stat_arrays_eq(moo_pStatListEx.FullStats, original_pStatListEx.FullStats, "Comparing pItem->pStatListEx->FullStats");
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>>, "D2Common.0x6FDA0A20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DecodeItemBitstreamComplete, dll_base + 0x00060A20);

		// Note: Only unidentified items without a header are covered, as the magic properties of other items are stored in newly allocated stat lists.
		// Ears and personalized items are not covered, as the name of the player is read until a terminating zero is found in the random bitstream.
		SUBCASE("")
		{
			const BOOL bCheckForHeader = FALSE;
			const BOOL bGamble = GENERATE(FALSE, TRUE);
			const uint32_t dwVersion = GENERATE(87, 92, 96);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const uint32_t item_flags[] = { 0, IFLAG_SOCKETED, IFLAG_ETHEREAL, IFLAG_RUNEWORD, IFLAG_SOCKETED | IFLAG_ETHEREAL };
				const auto item_flag = item_flags[random_unsigned_integer(0, std::size(item_flags) - 1)];
				const auto anim_mode = random_unsigned_integer(IMODE_STORED, IMODE_SOCKETED);

				std::vector<std::pair<uint32_t, int>> values;
				values.push_back({ random_unsigned_integer(0, 1023), 10 });
				values.push_back({ anim_mode, 3 });
				if (anim_mode == IMODE_ONGROUND || anim_mode == IMODE_DROPPING)
				{
					values.push_back({ random_unsigned_integer(0, 0xFFFF), 16 });
					values.push_back({ random_unsigned_integer(0, 0xFFFF), 16 });
				}
				else
				{
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 15), 4 });
					values.push_back({ random_unsigned_integer(0, 7), 3 });
				}
				values.push_back({ items_txt[i].dwCode, 32 });

				// The remaining bits (quality, affixes, defense, durability, quantity, sockets) are random
				constexpr auto bitstream_size = 32;
				const auto bitstream = make_bitstream(values, bitstream_size);

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StaticPathStrc moo_pStaticPath{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2BitBufferStrc moo_pBuffer{};
				int moo_pSocketedItems{};
				std::vector<uint8_t> moo_pBitstream;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StaticPathStrc original_pStaticPath{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2BitBufferStrc original_pBuffer{};
				int original_pSocketedItems{};
				std::vector<uint8_t> original_pBitstream;

				const auto setup_data = [item_flag, &bitstream](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StaticPathStrc& pStaticPath,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2BitBufferStrc& pBuffer,
					std::vector<uint8_t>& pBitstream
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItem.pStaticPath = &pStaticPath;
					pItemData.dwItemFlags = item_flag;
					// The stat arrays are allocated by the implementations
					setup_stat_list(pItem, pStatListEx, pStats, {}, pFullStats, {});

					pBitstream = bitstream;
					BITMANIP_Initialize(&pBuffer, pBitstream.data(), pBitstream.size());
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStaticPath, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pBuffer, moo_pBitstream);
				setup_data(original_pItem, original_pItemData, original_pStaticPath, original_pStatListEx, original_pStats, original_pFullStats, original_pBuffer, original_pBitstream);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &moo_pBuffer, bCheckForHeader, bGamble, &moo_pSocketedItems, dwVersion);
				const auto original_result = original(&original_pItem, &original_pBuffer, bCheckForHeader, bGamble, &original_pSocketedItems, dwVersion);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				check_stat_arrays_eq(moo_pStatListEx.Stats, original_pStatListEx.Stats, "Comparing pItem->pStatListEx->Stats");
				check_stat_arrays_eq(moo_pStatListEx.FullStats, original_pStatListEx.FullStats, "Comparing pItem->pStatListEx->FullStats");
				MOO_CHECK_EQ(moo_pSocketedItems, original_pSocketedItems, "Comparing pSocketedItems");
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsLinkerFixture<ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>>, "D2Common.0x6FDA2690")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetDefenseOrDamage, dll_base + 0x00062690);

		SUBCASE("")
		{
			const int nStat = GENERATE(STAT_ARMORCLASS, STAT_ITEM_ARMOR_PERCENT, STAT_MAXDAMAGE, STAT_ITEM_MAXDAMAGE_PERCENT, STAT_MINDAMAGE, STAT_ITEM_MINDAMAGE_PERCENT, STAT_STRENGTH);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				// Some stats are missing, the others might be lower or higher than the values of the item record
				const int stat_ids[] = { STAT_ARMORCLASS, STAT_MINDAMAGE, STAT_MAXDAMAGE, STAT_SECONDARY_MINDAMAGE, STAT_SECONDARY_MAXDAMAGE, STAT_ITEM_THROW_MINDAMAGE, STAT_ITEM_THROW_MAXDAMAGE };
				std::vector<D2StatStrc> stats;
				for (const auto stat_id : stat_ids)
				{
					if (random_unsigned_integer(0, 3) != 0)
					{
						stats.push_back(make_stat(stat_id, 0, random_unsigned_integer(1, 200)));
					}
				}
				stats = sorted_stats(stats);
				const auto stat_capacity = std::size(stat_ids);

				D2UnitStrc moo_pItem{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2UnitStrc original_pItem{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;

				const auto setup_data = [i, &stats, stat_capacity](
					D2UnitStrc& pItem,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					// Reserve space for all stats which might get inserted
					setup_stat_list(pItem, pStatListEx, pStats, stats, pFullStats, stats, stat_capacity);
				};

				setup_data(moo_pItem, moo_pStatListEx, moo_pStats, moo_pFullStats);
				setup_data(original_pItem, original_pStatListEx, original_pStats, original_pFullStats);

				// Call both implementations
				sut(&moo_pItem, nStat);
				original(&original_pItem, nStat);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				check_stat_arrays_eq(moo_pStatListEx.Stats, original_pStatListEx.Stats, "Comparing pItem->pStatListEx->Stats");
				check_stat_arrays_eq(moo_pStatListEx.FullStats, original_pStatListEx.FullStats, "Comparing pItem->pStatListEx->FullStats");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDA29D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_ReadStatFromItemBitstream, dll_base + 0x000629D0);

		SUBCASE("")
		{
			const uint32_t dwVersion = GENERATE(87, 89, 92, 96);
			const int n109 = GENERATE(0, 1);
			const auto with_stat_list = GENERATE(0, 1);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				// Input data
				constexpr auto bitstream_size = 16;
				const auto bitstream = make_bitstream({}, bitstream_size);

				D2BitBufferStrc moo_pBuffer{};
				std::vector<uint8_t> moo_pBitstream;
				D2StatListStrc moo_pStatList{};
				D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
				D2BitBufferStrc original_pBuffer{};
				std::vector<uint8_t> original_pBitstream;
				D2StatListStrc original_pStatList{};
				D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
				int nStatId = i;

				const auto setup_data = [this, i, &bitstream](
					D2BitBufferStrc& pBuffer,
					std::vector<uint8_t>& pBitstream,
					D2StatListStrc& pStatList,
					D2ItemStatCostTxt& pItemStatCostTxtRecord
				) {
					pBitstream = bitstream;
					BITMANIP_Initialize(&pBuffer, pBitstream.data(), pBitstream.size());

					// The stat array is allocated by the implementations
					pStatList.dwOwnerType = UNIT_ITEM;
					pStatList.dwFlags = STATLIST_MAGIC;

					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				setup_data(moo_pBuffer, moo_pBitstream, moo_pStatList, moo_pItemStatCostTxtRecord);
				setup_data(original_pBuffer, original_pBitstream, original_pStatList, original_pItemStatCostTxtRecord);

				// Call both implementations
				sut(&moo_pBuffer, with_stat_list ? &moo_pStatList : nullptr, &moo_pItemStatCostTxtRecord, nStatId, dwVersion, n109);
				original(&original_pBuffer, with_stat_list ? &original_pStatList : nullptr, &original_pItemStatCostTxtRecord, nStatId, dwVersion, n109);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
				check_stat_arrays_eq(moo_pStatList.Stats, original_pStatList.Stats, "Comparing pStatList->Stats");
				MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FDA2BA0 (#10881)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SerializeItemToBitstream, dll_base + 0x00062BA0);

		SUBCASE("")
		{
			const BOOL bServer = GENERATE(FALSE, TRUE);
			const BOOL bSaveItemInv = GENERATE(FALSE, TRUE);
			const BOOL bGamble = GENERATE(FALSE, TRUE);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto properties = make_serialized_item_properties(i, itemstatcost_record_count);
				const int with_socketed_item = random_unsigned_integer(0, 1) == 1;
				const auto socketed_item_properties = make_serialized_item_properties(random_unsigned_integer(0, items_record_count - 1), itemstatcost_record_count);
				const auto bitstream_size = static_cast<int>(random_unsigned_integer(0, 3) ? 512 : random_unsigned_integer(1, 16));

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StaticPathStrc moo_pStaticPath{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2StatListStrc moo_pMagicStatList{};
				std::vector<D2StatStrc> moo_pMagicStats;
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pSocketedItem{};
				D2ItemDataStrc moo_pSocketedItemData{};
				D2StaticPathStrc moo_pSocketedItemStaticPath{};
				D2StatListExStrc moo_pSocketedItemStatListEx{};
				std::vector<D2StatStrc> moo_pSocketedItemStats;
				std::vector<D2StatStrc> moo_pSocketedItemFullStats;
				D2StatListStrc moo_pSocketedItemMagicStatList{};
				std::vector<D2StatStrc> moo_pSocketedItemMagicStats;
				std::vector<uint8_t> moo_pBitstream;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StaticPathStrc original_pStaticPath{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2StatListStrc original_pMagicStatList{};
				std::vector<D2StatStrc> original_pMagicStats;
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pSocketedItem{};
				D2ItemDataStrc original_pSocketedItemData{};
				D2StaticPathStrc original_pSocketedItemStaticPath{};
				D2StatListExStrc original_pSocketedItemStatListEx{};
				std::vector<D2StatStrc> original_pSocketedItemStats;
				std::vector<D2StatStrc> original_pSocketedItemFullStats;
				D2StatListStrc original_pSocketedItemMagicStatList{};
				std::vector<D2StatStrc> original_pSocketedItemMagicStats;
				std::vector<uint8_t> original_pBitstream;
				size_t nSize = bitstream_size;

				const auto setup_data = [&properties, with_socketed_item, &socketed_item_properties, bitstream_size](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StaticPathStrc& pStaticPath,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2StatListStrc& pMagicStatList,
					std::vector<D2StatStrc>& pMagicStats,
					D2InventoryStrc& pInventory,
					D2UnitStrc& pSocketedItem,
					D2ItemDataStrc& pSocketedItemData,
					D2StaticPathStrc& pSocketedItemStaticPath,
					D2StatListExStrc& pSocketedItemStatListEx,
					std::vector<D2StatStrc>& pSocketedItemStats,
					std::vector<D2StatStrc>& pSocketedItemFullStats,
					D2StatListStrc& pSocketedItemMagicStatList,
					std::vector<D2StatStrc>& pSocketedItemMagicStats,
					std::vector<uint8_t>& pBitstream
				) {
					setup_serialized_item(properties, pItem, pItemData, pStaticPath, pStatListEx, pStats, pFullStats, pMagicStatList, pMagicStats);

					if (with_socketed_item)
					{
						setup_serialized_item(socketed_item_properties, pSocketedItem, pSocketedItemData, pSocketedItemStaticPath, pSocketedItemStatListEx, pSocketedItemStats, pSocketedItemFullStats, pSocketedItemMagicStatList, pSocketedItemMagicStats);
						pSocketedItemData.pExtraData.pParentInv = &pInventory;

						pItem.pInventory = &pInventory;
						pInventory.dwSignature = D2C_InventoryHeader;
						pInventory.pOwner = &pItem;
						pInventory.pFirstItem = &pSocketedItem;
						pInventory.pLastItem = &pSocketedItem;
						pInventory.dwItemCount = 1;
					}

					pBitstream.resize(bitstream_size);
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStaticPath, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pMagicStatList, moo_pMagicStats, moo_pInventory, moo_pSocketedItem, moo_pSocketedItemData, moo_pSocketedItemStaticPath, moo_pSocketedItemStatListEx, moo_pSocketedItemStats, moo_pSocketedItemFullStats, moo_pSocketedItemMagicStatList, moo_pSocketedItemMagicStats, moo_pBitstream);
				setup_data(original_pItem, original_pItemData, original_pStaticPath, original_pStatListEx, original_pStats, original_pFullStats, original_pMagicStatList, original_pMagicStats, original_pInventory, original_pSocketedItem, original_pSocketedItemData, original_pSocketedItemStaticPath, original_pSocketedItemStatListEx, original_pSocketedItemStats, original_pSocketedItemFullStats, original_pSocketedItemMagicStatList, original_pSocketedItemMagicStats, original_pBitstream);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, moo_pBitstream.data(), nSize, bServer, bSaveItemInv, bGamble);
				const auto original_result = original(&original_pItem, original_pBitstream.data(), nSize, bServer, bSaveItemInv, bGamble);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pSocketedItem, original_pSocketedItem, "Comparing pSocketedItem");
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "Inlined in D2Common.0x6FDA2C00")
	{
		// Set up function pointers
		// The function is inlined in ITEMS_SerializeItem in the original game. Therefore it is compared with ITEMS_SerializeItem
		// (without saving socketed items), which writes the header and the item flags before serializing the compact item.
		const auto sut = &ITEMS_SerializeItemCompact;
		const auto original = reinterpret_cast<decltype(&ITEMS_SerializeItem)>(dll_base + 0x00062C00);

		SUBCASE("")
		{
			const BOOL bServer = GENERATE(FALSE, TRUE);

			for (auto i = 0; i < items_record_count; ++i)
			{
				if (!items_txt[i].nCompactSave)
				{
					continue;
				}

				// Input data
				const auto properties = make_serialized_item_properties(i, itemstatcost_record_count);
				const auto bitstream_size = static_cast<int>(random_unsigned_integer(0, 3) ? 512 : random_unsigned_integer(1, 16));

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StaticPathStrc moo_pStaticPath{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2StatListStrc moo_pMagicStatList{};
				std::vector<D2StatStrc> moo_pMagicStats;
				D2BitBufferStrc moo_pBuffer{};
				D2ItemsTxt moo_pItemsTxtRecord{};
				std::vector<uint8_t> moo_pBitstream;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StaticPathStrc original_pStaticPath{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2StatListStrc original_pMagicStatList{};
				std::vector<D2StatStrc> original_pMagicStats;
				D2BitBufferStrc original_pBuffer{};
				std::vector<uint8_t> original_pBitstream;

				const auto setup_data = [&properties, bitstream_size](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StaticPathStrc& pStaticPath,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2StatListStrc& pMagicStatList,
					std::vector<D2StatStrc>& pMagicStats,
					D2BitBufferStrc& pBuffer,
					std::vector<uint8_t>& pBitstream
				) {
					setup_serialized_item(properties, pItem, pItemData, pStaticPath, pStatListEx, pStats, pFullStats, pMagicStatList, pMagicStats);

					pBitstream.resize(bitstream_size);
					BITMANIP_Initialize(&pBuffer, pBitstream.data(), bitstream_size);
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStaticPath, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pMagicStatList, moo_pMagicStats, moo_pBuffer, moo_pBitstream);
				setup_data(original_pItem, original_pItemData, original_pStaticPath, original_pStatListEx, original_pStats, original_pFullStats, original_pMagicStatList, original_pMagicStats, original_pBuffer, original_pBitstream);

				moo_pItemsTxtRecord = items_txt[i];

				// Write the header and the item flags like ITEMS_SerializeItem does
				auto moo_item_flags = (moo_pItemData.dwItemFlags & ~IFLAG_INIT) | IFLAG_JUSTSAVED | IFLAG_COMPACTSAVE;
				if (bServer)
				{
					BITMANIP_Write(&moo_pBuffer, 'MJ', 16);
				}
				else if (!(moo_item_flags & IFLAG_IDENTIFIED))
				{
					moo_item_flags &= ~IFLAG_SOCKETED;
				}
				BITMANIP_Write(&moo_pBuffer, moo_item_flags, 32);

				// Call both implementations
				sut(&moo_pItem, &moo_pBuffer, &moo_pItemsTxtRecord, bServer);
				original(&original_pItem, &original_pBuffer, bServer, FALSE, FALSE);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pItemsTxtRecord, items_txt[i], "Comparing pItemsTxtRecord");
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FDA2C00" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SerializeItem, dll_base + 0x00062C00);

		SUBCASE("")
		{
			const BOOL bServer = GENERATE(FALSE, TRUE);
			const BOOL bSaveItemInv = GENERATE(FALSE, TRUE);
			const BOOL bGamble = GENERATE(FALSE, TRUE);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto properties = make_serialized_item_properties(i, itemstatcost_record_count);
				const int with_socketed_item = random_unsigned_integer(0, 1) == 1;
				const auto socketed_item_properties = make_serialized_item_properties(random_unsigned_integer(0, items_record_count - 1), itemstatcost_record_count);
				const auto bitstream_size = static_cast<int>(random_unsigned_integer(0, 3) ? 512 : random_unsigned_integer(1, 16));

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StaticPathStrc moo_pStaticPath{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2StatListStrc moo_pMagicStatList{};
				std::vector<D2StatStrc> moo_pMagicStats;
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pSocketedItem{};
				D2ItemDataStrc moo_pSocketedItemData{};
				D2StaticPathStrc moo_pSocketedItemStaticPath{};
				D2StatListExStrc moo_pSocketedItemStatListEx{};
				std::vector<D2StatStrc> moo_pSocketedItemStats;
				std::vector<D2StatStrc> moo_pSocketedItemFullStats;
				D2StatListStrc moo_pSocketedItemMagicStatList{};
				std::vector<D2StatStrc> moo_pSocketedItemMagicStats;
				D2BitBufferStrc moo_pBuffer{};
				std::vector<uint8_t> moo_pBitstream;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StaticPathStrc original_pStaticPath{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2StatListStrc original_pMagicStatList{};
				std::vector<D2StatStrc> original_pMagicStats;
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pSocketedItem{};
				D2ItemDataStrc original_pSocketedItemData{};
				D2StaticPathStrc original_pSocketedItemStaticPath{};
				D2StatListExStrc original_pSocketedItemStatListEx{};
				std::vector<D2StatStrc> original_pSocketedItemStats;
				std::vector<D2StatStrc> original_pSocketedItemFullStats;
				D2StatListStrc original_pSocketedItemMagicStatList{};
				std::vector<D2StatStrc> original_pSocketedItemMagicStats;
				D2BitBufferStrc original_pBuffer{};
				std::vector<uint8_t> original_pBitstream;

				const auto setup_data = [&properties, with_socketed_item, &socketed_item_properties, bitstream_size](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StaticPathStrc& pStaticPath,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2StatListStrc& pMagicStatList,
					std::vector<D2StatStrc>& pMagicStats,
					D2InventoryStrc& pInventory,
					D2UnitStrc& pSocketedItem,
					D2ItemDataStrc& pSocketedItemData,
					D2StaticPathStrc& pSocketedItemStaticPath,
					D2StatListExStrc& pSocketedItemStatListEx,
					std::vector<D2StatStrc>& pSocketedItemStats,
					std::vector<D2StatStrc>& pSocketedItemFullStats,
					D2StatListStrc& pSocketedItemMagicStatList,
					std::vector<D2StatStrc>& pSocketedItemMagicStats,
					D2BitBufferStrc& pBuffer,
					std::vector<uint8_t>& pBitstream
				) {
					setup_serialized_item(properties, pItem, pItemData, pStaticPath, pStatListEx, pStats, pFullStats, pMagicStatList, pMagicStats);

					if (with_socketed_item)
					{
						setup_serialized_item(socketed_item_properties, pSocketedItem, pSocketedItemData, pSocketedItemStaticPath, pSocketedItemStatListEx, pSocketedItemStats, pSocketedItemFullStats, pSocketedItemMagicStatList, pSocketedItemMagicStats);
						pSocketedItemData.pExtraData.pParentInv = &pInventory;

						pItem.pInventory = &pInventory;
						pInventory.dwSignature = D2C_InventoryHeader;
						pInventory.pOwner = &pItem;
						pInventory.pFirstItem = &pSocketedItem;
						pInventory.pLastItem = &pSocketedItem;
						pInventory.dwItemCount = 1;
					}

					pBitstream.resize(bitstream_size);
					BITMANIP_Initialize(&pBuffer, pBitstream.data(), bitstream_size);
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStaticPath, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pMagicStatList, moo_pMagicStats, moo_pInventory, moo_pSocketedItem, moo_pSocketedItemData, moo_pSocketedItemStaticPath, moo_pSocketedItemStatListEx, moo_pSocketedItemStats, moo_pSocketedItemFullStats, moo_pSocketedItemMagicStatList, moo_pSocketedItemMagicStats, moo_pBuffer, moo_pBitstream);
				setup_data(original_pItem, original_pItemData, original_pStaticPath, original_pStatListEx, original_pStats, original_pFullStats, original_pMagicStatList, original_pMagicStats, original_pInventory, original_pSocketedItem, original_pSocketedItemData, original_pSocketedItemStaticPath, original_pSocketedItemStatListEx, original_pSocketedItemStats, original_pSocketedItemFullStats, original_pSocketedItemMagicStatList, original_pSocketedItemMagicStats, original_pBuffer, original_pBitstream);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem, &moo_pBuffer, bServer, bSaveItemInv, bGamble);
				const auto original_result = original(&original_pItem, &original_pBuffer, bServer, bSaveItemInv, bGamble);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pSocketedItem, original_pSocketedItem, "Comparing pSocketedItem");
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA2FD0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_WriteBitsToBitstream, dll_base + 0x00062FD0);

		SUBCASE("")
		{
			for (auto nBits = 1; nBits <= 32; ++nBits)
			{
				for (auto repetition = 0; repetition < 20; ++repetition)
				{
					// Input data
					// The data is written at a random position of the bitstream, the data might exceed the bit count or be negative
					constexpr auto bitstream_size = 16;
					const auto initial_bits = static_cast<int>(random_unsigned_integer(0, 8 * bitstream_size));
					const auto initial_bitstream = make_bitstream({}, bitstream_size);

					D2BitBufferStrc moo_pBuffer{};
					std::vector<uint8_t> moo_pBitstream;
					D2BitBufferStrc original_pBuffer{};
					std::vector<uint8_t> original_pBitstream;
					int nData = random_unsigned_integer(0, 3) == 0 ? static_cast<int>(random_unsigned_integer()) : static_cast<int>(random_unsigned_integer(0, (1u << (nBits - 1)) * 2 - 1));

					const auto setup_data = [&initial_bitstream, initial_bits](
						D2BitBufferStrc& pBuffer,
						std::vector<uint8_t>& pBitstream
					) {
						pBitstream = initial_bitstream;
						BITMANIP_Initialize(&pBuffer, pBitstream.data(), pBitstream.size());
						pBuffer.pBuffer += initial_bits / 8;
						pBuffer.nPos = initial_bits / 8;
						pBuffer.nPosBits = initial_bits % 8;
					};

					setup_data(moo_pBuffer, moo_pBitstream);
					setup_data(original_pBuffer, original_pBitstream);

					// Call both implementations
					sut(&moo_pBuffer, nData, nBits);
					original(&original_pBuffer, nData, nBits);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
					auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
					auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
					MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FDA3010" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SerializeItemComplete, dll_base + 0x00063010);

		SUBCASE("")
		{
			const BOOL bServer = GENERATE(FALSE, TRUE);
			const BOOL bGamble = GENERATE(FALSE, TRUE);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				const auto properties = make_serialized_item_properties(i, itemstatcost_record_count);
				const int with_socketed_item = random_unsigned_integer(0, 1) == 1;
				const auto socketed_item_properties = make_serialized_item_properties(random_unsigned_integer(0, items_record_count - 1), itemstatcost_record_count);
				const auto bitstream_size = static_cast<int>(random_unsigned_integer(0, 3) ? 512 : random_unsigned_integer(1, 16));

				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StaticPathStrc moo_pStaticPath{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2StatListStrc moo_pMagicStatList{};
				std::vector<D2StatStrc> moo_pMagicStats;
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pSocketedItem{};
				D2ItemDataStrc moo_pSocketedItemData{};
				D2StaticPathStrc moo_pSocketedItemStaticPath{};
				D2StatListExStrc moo_pSocketedItemStatListEx{};
				std::vector<D2StatStrc> moo_pSocketedItemStats;
				std::vector<D2StatStrc> moo_pSocketedItemFullStats;
				D2StatListStrc moo_pSocketedItemMagicStatList{};
				std::vector<D2StatStrc> moo_pSocketedItemMagicStats;
				D2BitBufferStrc moo_pBuffer{};
				std::vector<uint8_t> moo_pBitstream;
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StaticPathStrc original_pStaticPath{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2StatListStrc original_pMagicStatList{};
				std::vector<D2StatStrc> original_pMagicStats;
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pSocketedItem{};
				D2ItemDataStrc original_pSocketedItemData{};
				D2StaticPathStrc original_pSocketedItemStaticPath{};
				D2StatListExStrc original_pSocketedItemStatListEx{};
				std::vector<D2StatStrc> original_pSocketedItemStats;
				std::vector<D2StatStrc> original_pSocketedItemFullStats;
				D2StatListStrc original_pSocketedItemMagicStatList{};
				std::vector<D2StatStrc> original_pSocketedItemMagicStats;
				D2BitBufferStrc original_pBuffer{};
				std::vector<uint8_t> original_pBitstream;

				const auto setup_data = [&properties, with_socketed_item, &socketed_item_properties, bitstream_size](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StaticPathStrc& pStaticPath,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2StatListStrc& pMagicStatList,
					std::vector<D2StatStrc>& pMagicStats,
					D2InventoryStrc& pInventory,
					D2UnitStrc& pSocketedItem,
					D2ItemDataStrc& pSocketedItemData,
					D2StaticPathStrc& pSocketedItemStaticPath,
					D2StatListExStrc& pSocketedItemStatListEx,
					std::vector<D2StatStrc>& pSocketedItemStats,
					std::vector<D2StatStrc>& pSocketedItemFullStats,
					D2StatListStrc& pSocketedItemMagicStatList,
					std::vector<D2StatStrc>& pSocketedItemMagicStats,
					D2BitBufferStrc& pBuffer,
					std::vector<uint8_t>& pBitstream
				) {
					setup_serialized_item(properties, pItem, pItemData, pStaticPath, pStatListEx, pStats, pFullStats, pMagicStatList, pMagicStats);

					if (with_socketed_item)
					{
						setup_serialized_item(socketed_item_properties, pSocketedItem, pSocketedItemData, pSocketedItemStaticPath, pSocketedItemStatListEx, pSocketedItemStats, pSocketedItemFullStats, pSocketedItemMagicStatList, pSocketedItemMagicStats);
						pSocketedItemData.pExtraData.pParentInv = &pInventory;

						pItem.pInventory = &pInventory;
						pInventory.dwSignature = D2C_InventoryHeader;
						pInventory.pOwner = &pItem;
						pInventory.pFirstItem = &pSocketedItem;
						pInventory.pLastItem = &pSocketedItem;
						pInventory.dwItemCount = 1;
					}

					pBitstream.resize(bitstream_size);
					BITMANIP_Initialize(&pBuffer, pBitstream.data(), bitstream_size);
				};

				setup_data(moo_pItem, moo_pItemData, moo_pStaticPath, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pMagicStatList, moo_pMagicStats, moo_pInventory, moo_pSocketedItem, moo_pSocketedItemData, moo_pSocketedItemStaticPath, moo_pSocketedItemStatListEx, moo_pSocketedItemStats, moo_pSocketedItemFullStats, moo_pSocketedItemMagicStatList, moo_pSocketedItemMagicStats, moo_pBuffer, moo_pBitstream);
				setup_data(original_pItem, original_pItemData, original_pStaticPath, original_pStatListEx, original_pStats, original_pFullStats, original_pMagicStatList, original_pMagicStats, original_pInventory, original_pSocketedItem, original_pSocketedItemData, original_pSocketedItemStaticPath, original_pSocketedItemStatListEx, original_pSocketedItemStats, original_pSocketedItemFullStats, original_pSocketedItemMagicStatList, original_pSocketedItemMagicStats, original_pBuffer, original_pBitstream);

				// Call both implementations
				sut(&moo_pItem, &moo_pBuffer, bServer, bGamble);
				original(&original_pItem, &original_pBuffer, bServer, bGamble);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				MOO_CHECK_EQ(moo_pSocketedItem, original_pSocketedItem, "Comparing pSocketedItem");
				MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
				auto moo_bitstream = DynamicArray<uint8_t>{ moo_pBitstream.data(), bitstream_size };
				auto original_bitstream = DynamicArray<uint8_t>{ original_pBitstream.data(), bitstream_size };
				MOO_CHECK_EQ(moo_bitstream, original_bitstream, "Comparing pBitstream");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDA42B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetItemStatCostTxtRecord, dll_base + 0x000642B0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				int nStatId = i;

				// Call both implementations
				const auto moo_result = sut(nStatId);
				const auto original_result = original(nStatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SetItemsTxtFixture<NoopFixture>, "D2Common.0x6FDA42E0 (#10837)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetNoOfSetItemsFromItem, dll_base + 0x000642E0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < setitems_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i](
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = ITEMQUAL_SET;
					pItemData.dwFileIndex = i;
				};

				setup_data(moo_pItem, moo_pItemData);
				setup_data(original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pItem);
				const auto original_result = original(&original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}

	TEST_CASE_FIXTURE(SetItemsTxtFixture<NoopFixture>, "D2Common.0x6FDA4380" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDA4380, dll_base + 0x00064380);

		SUBCASE("")
		{
			const auto quality = GENERATE(ITEMQUAL_SET, ITEMQUAL_UNIQUE);

			for (auto i = 0; i < setitems_record_count; ++i)
			{
				for (auto repetition = 0; repetition < 5; ++repetition)
				{
					// Input data
					// The stat lists of the item set states are (de-)activated, they have no stats
					SetStateStatListProperties set_state_stat_lists[item_set_state_count];
					for (auto& set_state_stat_list : set_state_stat_lists)
					{
						set_state_stat_list.bPresent = random_unsigned_integer(0, 3) != 0;
						set_state_stat_list.dwFlags = random_unsigned_integer(0, 1) ? STATLIST_SET : 0;
					}

					D2UnitStrc moo_pItem{};
					D2ItemDataStrc moo_pItemData{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStats;
					std::vector<D2StatStrc> moo_pFullStats;
					D2StatListStrc moo_pSetStateStatLists[item_set_state_count]{};
					std::vector<D2StatStrc> moo_pSetStateStats[item_set_state_count];
					D2UnitStrc original_pItem{};
					D2ItemDataStrc original_pItemData{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStats;
					std::vector<D2StatStrc> original_pFullStats;
					D2StatListStrc original_pSetStateStatLists[item_set_state_count]{};
					std::vector<D2StatStrc> original_pSetStateStats[item_set_state_count];
					unsigned int nSetItemMask = random_unsigned_integer(0, 0x7F);

					const auto setup_data = [i, quality, &set_state_stat_lists](
						D2UnitStrc& pItem,
						D2ItemDataStrc& pItemData,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStats,
						std::vector<D2StatStrc>& pFullStats,
						D2StatListStrc (&pSetStateStatLists)[item_set_state_count],
						std::vector<D2StatStrc> (&pSetStateStats)[item_set_state_count]
					) {
						pItem.dwUnitType = UNIT_ITEM;
						pItem.pItemData = &pItemData;
						pItemData.dwQualityNo = quality;
						pItemData.dwFileIndex = i;
						setup_stat_list(pItem, pStatListEx, pStats, {}, pFullStats, {});
						setup_set_state_stat_lists(set_state_stat_lists, pItem, pStatListEx, pSetStateStatLists, pSetStateStats);
					};

					setup_data(moo_pItem, moo_pItemData, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pSetStateStatLists, moo_pSetStateStats);
					setup_data(original_pItem, original_pItemData, original_pStatListEx, original_pStats, original_pFullStats, original_pSetStateStatLists, original_pSetStateStats);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem, nSetItemMask);
					const auto original_result = original(&original_pItem, nSetItemMask);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
					for (auto j = 0; j < item_set_state_count; ++j)
					{
						MOO_CHECK_EQ(moo_pSetStateStatLists[j], original_pSetStateStatLists[j], "Comparing pSetStateStatLists");
					}
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SetItemsTxtFixture<SetsTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FDA4490" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDA4490, dll_base + 0x00064490);

		// Note: Removing an existing stat list of an item set state (a3 == 1) is not covered, as the stat list gets freed
		SUBCASE("")
		{
			const int a3 = GENERATE(0, 1, 2);
			const auto with_matching_stat_list = GENERATE(false, true);

			if (a3 == 1 && with_matching_stat_list)
			{
				return;
			}

			for (auto i = 0; i < setitems_record_count; ++i)
			{
				// Input data
				// The stat lists of the item set states store the id of the set
				const int set_id = setitems_txt[i].nSetId;
				const auto matching_stat_list = random_unsigned_integer(0, item_set_state_count - 1);
				int set_ids_sum = 0;

				SetStateStatListProperties set_state_stat_lists[item_set_state_count];
				for (auto j = 0; j < item_set_state_count; ++j)
				{
					const auto matching = with_matching_stat_list && j == matching_stat_list;
					const auto other_set_id = set_id + static_cast<int>(random_unsigned_integer(1, 10));

					set_state_stat_lists[j].bPresent = matching || random_unsigned_integer(0, 1);
					set_state_stat_lists[j].stats = { make_stat(STAT_VALUE, 0, matching ? set_id : other_set_id) };
					if (set_state_stat_lists[j].bPresent)
					{
						set_ids_sum += set_state_stat_lists[j].stats[0].nValue;
					}
				}

				const auto unit_stats = set_ids_sum ? sorted_stats({ make_stat(STAT_VALUE, 0, set_ids_sum) }) : std::vector<D2StatStrc>{};

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStats;
				std::vector<D2StatStrc> moo_pFullStats;
				D2StatListStrc moo_pSetStateStatLists[item_set_state_count]{};
				std::vector<D2StatStrc> moo_pSetStateStats[item_set_state_count];
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStats;
				std::vector<D2StatStrc> original_pFullStats;
				D2StatListStrc original_pSetStateStatLists[item_set_state_count]{};
				std::vector<D2StatStrc> original_pSetStateStats[item_set_state_count];
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i, &set_state_stat_lists, &unit_stats](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStats,
					std::vector<D2StatStrc>& pFullStats,
					D2StatListStrc (&pSetStateStatLists)[item_set_state_count],
					std::vector<D2StatStrc> (&pSetStateStats)[item_set_state_count],
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					// Reserve space for the stat of a new stat list
					setup_stat_list(pUnit, pStatListEx, pStats, {}, pFullStats, unit_stats, unit_stats.size() + 1);
					setup_set_state_stat_lists(set_state_stat_lists, pUnit, pStatListEx, pSetStateStatLists, pSetStateStats);

					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = ITEMQUAL_SET;
					pItemData.dwFileIndex = i;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStats, moo_pFullStats, moo_pSetStateStatLists, moo_pSetStateStats, moo_pItem, moo_pItemData);
				setup_data(original_pUnit, original_pStatListEx, original_pStats, original_pFullStats, original_pSetStateStatLists, original_pSetStateStats, original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pItem, a3);
				const auto original_result = original(&original_pUnit, &original_pItem, a3);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				check_stat_arrays_eq(moo_pStatListEx.FullStats, original_pStatListEx.FullStats, "Comparing pUnit->pStatListEx->FullStats");
				for (auto j = 0; j < item_set_state_count; ++j)
				{
					MOO_CHECK_EQ(moo_pSetStateStatLists[j], original_pSetStateStatLists[j], "Comparing pSetStateStatLists");
				}
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SetItemsTxtFixture<SetsTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FDA4640 (#10866)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_UpdateSets, dll_base + 0x00064640);

		// Note: The item is the only item in the inventory of the unit, so that no set bonuses are applied.
		// Removing an existing stat list of an item set state (a3 == 1) is not covered, as the stat list gets freed.
		SUBCASE("")
		{
			const int a3 = GENERATE(0, 1, 2);
			const int a4 = GENERATE(0, 1);
			const auto with_matching_stat_list = GENERATE(false, true);

			if (a3 == 1 && with_matching_stat_list)
			{
				return;
			}

			for (auto i = 0; i < setitems_record_count; ++i)
			{
				// Input data
				const int in_inventory = random_unsigned_integer(0, 3) != 0;
				const int node_page = random_unsigned_integer(0, 3) ? NODEPAGE_EQUIP : NODEPAGE_STORAGE;

				// The stat lists of the item set states of the unit store the id of the set
				const int set_id = setitems_txt[i].nSetId;
				const auto matching_stat_list = random_unsigned_integer(0, item_set_state_count - 1);
				int set_ids_sum = 0;

				SetStateStatListProperties unit_set_state_stat_lists[item_set_state_count];
				for (auto j = 0; j < item_set_state_count; ++j)
				{
					const auto matching = with_matching_stat_list && j == matching_stat_list;
					const auto other_set_id = set_id + static_cast<int>(random_unsigned_integer(1, 10));

					unit_set_state_stat_lists[j].bPresent = matching || random_unsigned_integer(0, 1);
					unit_set_state_stat_lists[j].stats = { make_stat(STAT_VALUE, 0, matching ? set_id : other_set_id) };
					if (unit_set_state_stat_lists[j].bPresent)
					{
						set_ids_sum += unit_set_state_stat_lists[j].stats[0].nValue;
					}
				}

				const auto unit_stats = set_ids_sum ? sorted_stats({ make_stat(STAT_VALUE, 0, set_ids_sum) }) : std::vector<D2StatStrc>{};

				// The stat lists of the item set states of the item are (de-)activated, they have no stats
				SetStateStatListProperties item_set_state_stat_lists[item_set_state_count];
				for (auto& item_set_state_stat_list : item_set_state_stat_lists)
				{
					item_set_state_stat_list.bPresent = random_unsigned_integer(0, 3) != 0;
					item_set_state_stat_list.dwFlags = random_unsigned_integer(0, 1) ? STATLIST_SET : 0;
				}

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pUnitStatListEx{};
				std::vector<D2StatStrc> moo_pUnitStats;
				std::vector<D2StatStrc> moo_pUnitFullStats;
				D2StatListStrc moo_pUnitSetStateStatLists[item_set_state_count]{};
				std::vector<D2StatStrc> moo_pUnitSetStateStats[item_set_state_count];
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2StatListExStrc moo_pItemStatListEx{};
				std::vector<D2StatStrc> moo_pItemStats;
				std::vector<D2StatStrc> moo_pItemFullStats;
				D2StatListStrc moo_pItemSetStateStatLists[item_set_state_count]{};
				std::vector<D2StatStrc> moo_pItemSetStateStats[item_set_state_count];
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pUnitStatListEx{};
				std::vector<D2StatStrc> original_pUnitStats;
				std::vector<D2StatStrc> original_pUnitFullStats;
				D2StatListStrc original_pUnitSetStateStatLists[item_set_state_count]{};
				std::vector<D2StatStrc> original_pUnitSetStateStats[item_set_state_count];
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};
				D2StatListExStrc original_pItemStatListEx{};
				std::vector<D2StatStrc> original_pItemStats;
				std::vector<D2StatStrc> original_pItemFullStats;
				D2StatListStrc original_pItemSetStateStatLists[item_set_state_count]{};
				std::vector<D2StatStrc> original_pItemSetStateStats[item_set_state_count];

				const auto setup_data = [i, in_inventory, node_page, &unit_set_state_stat_lists, &unit_stats, &item_set_state_stat_lists](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pUnitStatListEx,
					std::vector<D2StatStrc>& pUnitStats,
					std::vector<D2StatStrc>& pUnitFullStats,
					D2StatListStrc (&pUnitSetStateStatLists)[item_set_state_count],
					std::vector<D2StatStrc> (&pUnitSetStateStats)[item_set_state_count],
					D2InventoryStrc& pInventory,
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData,
					D2StatListExStrc& pItemStatListEx,
					std::vector<D2StatStrc>& pItemStats,
					std::vector<D2StatStrc>& pItemFullStats,
					D2StatListStrc (&pItemSetStateStatLists)[item_set_state_count],
					std::vector<D2StatStrc> (&pItemSetStateStats)[item_set_state_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pInventory = &pInventory;
					// Reserve space for the stat of a new stat list
					setup_stat_list(pUnit, pUnitStatListEx, pUnitStats, {}, pUnitFullStats, unit_stats, unit_stats.size() + 1);
					setup_set_state_stat_lists(unit_set_state_stat_lists, pUnit, pUnitStatListEx, pUnitSetStateStatLists, pUnitSetStateStats);

					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;

					pItem.dwUnitType = UNIT_ITEM;
					pItem.pItemData = &pItemData;
					pItemData.dwQualityNo = ITEMQUAL_SET;
					pItemData.dwFileIndex = i;
					setup_stat_list(pItem, pItemStatListEx, pItemStats, {}, pItemFullStats, {});
					setup_set_state_stat_lists(item_set_state_stat_lists, pItem, pItemStatListEx, pItemSetStateStatLists, pItemSetStateStats);

					if (in_inventory)
					{
						pInventory.pFirstItem = &pItem;
						pInventory.pLastItem = &pItem;
						pInventory.dwItemCount = 1;
						pItemData.pExtraData.pParentInv = &pInventory;
						pItemData.pExtraData.nNodePosOther = node_page;
					}
				};

				setup_data(moo_pUnit, moo_pUnitStatListEx, moo_pUnitStats, moo_pUnitFullStats, moo_pUnitSetStateStatLists, moo_pUnitSetStateStats, moo_pInventory, moo_pItem, moo_pItemData, moo_pItemStatListEx, moo_pItemStats, moo_pItemFullStats, moo_pItemSetStateStatLists, moo_pItemSetStateStats);
				setup_data(original_pUnit, original_pUnitStatListEx, original_pUnitStats, original_pUnitFullStats, original_pUnitSetStateStatLists, original_pUnitSetStateStats, original_pInventory, original_pItem, original_pItemData, original_pItemStatListEx, original_pItemStats, original_pItemFullStats, original_pItemSetStateStatLists, original_pItemSetStateStats);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pItem, a3, a4);
				const auto original_result = original(&original_pUnit, &original_pItem, a3, a4);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				check_stat_arrays_eq(moo_pUnitStatListEx.FullStats, original_pUnitStatListEx.FullStats, "Comparing pUnit->pStatListEx->FullStats");
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
				for (auto j = 0; j < item_set_state_count; ++j)
				{
					MOO_CHECK_EQ(moo_pUnitSetStateStatLists[j], original_pUnitSetStateStatLists[j], "Comparing pUnitSetStateStatLists");
					MOO_CHECK_EQ(moo_pItemSetStateStatLists[j], original_pItemSetStateStatLists[j], "Comparing pItemSetStateStatLists");
				}
			}
		}
	}
}

#endif
