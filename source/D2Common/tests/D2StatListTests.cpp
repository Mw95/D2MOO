#include <D2CommonTestDefines.h>

#ifdef STATLIST_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <limits>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2States.h>
#include <D2StatList.h>
#include <GAME/Game.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>

DYNAMIC_ARRAY_TYPE(D2StatStrc)
DYNAMIC_ARRAY_TYPE(uint32_t)


// Returns the ids of the stats which are not involved in any stat op, so that changing their values does not trigger
// recursive updates of other stats (which might require reallocations of the stat arrays)
static std::vector<uint16_t> get_plain_stat_ids(const D2ItemStatCostTxt* pItemStatCostTxt, int nRecordCount, size_t nMaxCount = std::numeric_limits<size_t>::max())
{
	std::vector<uint16_t> stat_ids;

	for (int i = 0; i < nRecordCount && stat_ids.size() < nMaxCount; ++i)
	{
		if (!pItemStatCostTxt[i].bIsBaseOfOtherStatOp && !pItemStatCostTxt[i].bHasOpStatData && !pItemStatCostTxt[i].bHasOpApplyingToItem)
		{
			stat_ids.push_back(static_cast<uint16_t>(i));
		}
	}

	return stat_ids;
}


struct StatCallbackCall
{
	D2UnitStrc* pUnit1;
	int nStatId;
	int nValue;
	D2UnitStrc* pUnit2;
};

static std::vector<StatCallbackCall> stat_callback_calls;

static void __fastcall record_stat_callback(D2UnitStrc* pUnit1, int nStatId, int nValue, D2UnitStrc* pUnit2)
{
	stat_callback_calls.push_back({ pUnit1, nStatId, nValue, pUnit2 });
}

static void check_stat_callback_calls_eq(
	const std::vector<StatCallbackCall>& moo_calls, D2UnitStrc* moo_pUnit1, D2UnitStrc* moo_pUnit2,
	const std::vector<StatCallbackCall>& original_calls, D2UnitStrc* original_pUnit1, D2UnitStrc* original_pUnit2
)
{
	REQUIRE_EQ(moo_calls.size(), original_calls.size());

	for (size_t i = 0; i < moo_calls.size(); ++i)
	{
		CHECK_EQ(moo_calls[i].pUnit1, moo_pUnit1);
		CHECK_EQ(original_calls[i].pUnit1, original_pUnit1);
		CHECK_EQ(moo_calls[i].nStatId, original_calls[i].nStatId);
		CHECK_EQ(moo_calls[i].nValue, original_calls[i].nValue);
		CHECK_EQ(moo_calls[i].pUnit2, moo_pUnit2);
		CHECK_EQ(original_calls[i].pUnit2, original_pUnit2);
	}
}


TEST_SUITE("D2StatListTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB57C0 (#10563)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_AreUnitsAligned, dll_base + 0x000757C0);

		SUBCASE("Units without stat lists")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit2.dwUnitType = UNIT_MONSTER;
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");

			CHECK_EQ(moo_result, TRUE);
		}

		SUBCASE("pUnit1 = pUnit2")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pUnit);
			const auto original_result = original(&original_pUnit, &original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, TRUE);
		}

		SUBCASE("Units with alignment state")
		{
			const int alignment1 = GENERATE(UNIT_ALIGNMENT_EVIL, UNIT_ALIGNMENT_NEUTRAL, UNIT_ALIGNMENT_GOOD);

			for (const int alignment2 : { UNIT_ALIGNMENT_EVIL, UNIT_ALIGNMENT_NEUTRAL, UNIT_ALIGNMENT_GOOD })
			{
				// Input data
				D2UnitStrc moo_pUnit1{};
				D2StatListExStrc moo_pStatListEx1{};
				D2StatListStrc moo_pAlignmentStatList1{};
				D2StatStrc moo_pAlignmentStat1{};
				D2UnitStrc moo_pUnit2{};
				D2StatListExStrc moo_pStatListEx2{};
				D2StatListStrc moo_pAlignmentStatList2{};
				D2StatStrc moo_pAlignmentStat2{};
				D2UnitStrc original_pUnit1{};
				D2StatListExStrc original_pStatListEx1{};
				D2StatListStrc original_pAlignmentStatList1{};
				D2StatStrc original_pAlignmentStat1{};
				D2UnitStrc original_pUnit2{};
				D2StatListExStrc original_pStatListEx2{};
				D2StatListStrc original_pAlignmentStatList2{};
				D2StatStrc original_pAlignmentStat2{};

				const auto setup_data = [](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					D2StatListStrc& pAlignmentStatList,
					D2StatStrc& pAlignmentStat,
					int nUnitType,
					int nAlignment
				) {
					pUnit.dwUnitType = nUnitType;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.pMyLastList = &pAlignmentStatList;
					pAlignmentStatList.dwStateNo = STATE_ALIGNMENT;
					pAlignmentStat.nLayer = 0;
					pAlignmentStat.nStat = STAT_ALIGNMENT;
					pAlignmentStat.nValue = nAlignment;
					pAlignmentStatList.Stats.pStat = &pAlignmentStat;
					pAlignmentStatList.Stats.nStatCount = 1;
					pAlignmentStatList.Stats.nCapacity = 1;
				};

				setup_data(moo_pUnit1, moo_pStatListEx1, moo_pAlignmentStatList1, moo_pAlignmentStat1, UNIT_PLAYER, alignment1);
				setup_data(moo_pUnit2, moo_pStatListEx2, moo_pAlignmentStatList2, moo_pAlignmentStat2, UNIT_MONSTER, alignment2);
				setup_data(original_pUnit1, original_pStatListEx1, original_pAlignmentStatList1, original_pAlignmentStat1, UNIT_PLAYER, alignment1);
				setup_data(original_pUnit2, original_pStatListEx2, original_pAlignmentStatList2, original_pAlignmentStat2, UNIT_MONSTER, alignment2);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
				const auto original_result = original(&original_pUnit1, &original_pUnit2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
				MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");

				CHECK_EQ(moo_result, (alignment1 == alignment2 && alignment1 != UNIT_ALIGNMENT_NEUTRAL) ? TRUE : FALSE);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB5830")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB5830, dll_base + 0x00075830);

		SUBCASE("")
		{
			// Input data
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto full_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto child_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 100 + i;

				full_stat_array[i].nLayer = 0;
				full_stat_array[i].nStat = static_cast<uint16_t>(i);
				full_stat_array[i].nValue = 300 + 2 * i;

				child_stat_array[i].nLayer = 0;
				child_stat_array[i].nStat = static_cast<uint16_t>(i);
				child_stat_array[i].nValue = 200 + i;
			}

			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc moo_pChildStatList{};
			const auto moo_pChildStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListExStrc original_pStatListEx{};
			const auto original_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc original_pChildStatList{};
			const auto original_pChildStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &base_stat_array, &full_stat_array, &child_stat_array](
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pBaseStat,
				const std::unique_ptr<D2StatStrc[]>& pFullStat,
				D2StatListStrc& pChildStatList,
				const std::unique_ptr<D2StatStrc[]>& pChildStat
			) {
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = UNIT_PLAYER;
				std::memcpy(pBaseStat.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.Stats.pStat = pBaseStat.get();
				pStatListEx.Stats.nStatCount = itemstatcost_record_count;
				pStatListEx.Stats.nCapacity = itemstatcost_record_count;
				std::memcpy(pFullStat.get(), full_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pFullStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				pStatListEx.pMyLastList = &pChildStatList;
				std::memcpy(pChildStat.get(), child_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pChildStatList.Stats.pStat = pChildStat.get();
				pChildStatList.Stats.nStatCount = itemstatcost_record_count;
				pChildStatList.Stats.nCapacity = itemstatcost_record_count;
			};

			setup_data(moo_pStatListEx, moo_pBaseStat, moo_pFullStat, moo_pChildStatList, moo_pChildStat);
			setup_data(original_pStatListEx, original_pBaseStat, original_pFullStat, original_pChildStatList, original_pChildStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nLayer_StatId);
				const auto original_result = original(&original_pStatListEx, nLayer_StatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB6300")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_FindStatIndex_6FDB6300, dll_base + 0x00076300);
		
		SUBCASE("Returns right index for matching layer")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};

			const auto setup_data = [&stat_array, this](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				// Call both implementations
				const auto moo_result = sut(&moo_pStatArray, nLayer_StatId);
				const auto original_result = original(&original_pStatArray, nLayer_StatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

				CHECK_EQ(moo_result, i);
			}
		}

		SUBCASE("Returns -1 for non-matching layer")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 1;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};

			const auto setup_data = [&stat_array, this](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				// Call both implementations
				const auto moo_result = sut(&moo_pStatArray, nLayer_StatId);
				const auto original_result = original(&original_pStatArray, nLayer_StatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

				CHECK_EQ(moo_result, -1);
			}
		}

		SUBCASE("Returns -1 for non-matching stat id")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};

			const auto setup_data = [&stat_array, this](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i + itemstatcost_record_count)).nPackedValue;

				// Call both implementations
				const auto moo_result = sut(&moo_pStatArray, nLayer_StatId);
				const auto original_result = original(&original_pStatArray, nLayer_StatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

				CHECK_EQ(moo_result, -1);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB6340")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetBaseStat_6FDB6340, dll_base + 0x00076340);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				const auto setup_data = [this, i, &stat_array](
					D2StatListStrc& pStatList,
					const std::unique_ptr<D2StatStrc[]>& pStat,
					D2ItemStatCostTxt& pItemStatCostTxtRecord
				) {
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatList.Stats.pStat = pStat.get();
					pStatList.Stats.nStatCount = itemstatcost_record_count;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				setup_data(moo_pStatList, moo_pStat, moo_pItemStatCostTxtRecord);
				setup_data(original_pStatList, original_pStat, original_pItemStatCostTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatList, nLayer_StatId, &moo_pItemStatCostTxtRecord);
				const auto original_result = original(&original_pStatList, nLayer_StatId, &original_pItemStatCostTxtRecord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
				MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}

		SUBCASE("Applies min value")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 0;
			}

			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc moo_pOwner{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2StatListExStrc original_pStatListEx{};
			D2UnitStrc original_pOwner{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};

			for (auto i : { 0, 1, 2, 3, 7, 9, 11 })
			{
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				const auto setup_data = [this, i, &stat_array](
					D2StatListExStrc& pStatListEx,
					D2UnitStrc& pOwner,
					const std::unique_ptr<D2StatStrc[]>& pStat,
					D2ItemStatCostTxt& pItemStatCostTxtRecord
				) {
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.pOwner = &pOwner;
					pOwner.dwUnitType = UNIT_PLAYER;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.Stats.pStat = pStat.get();
					pStatListEx.Stats.nStatCount = itemstatcost_record_count;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				setup_data(moo_pStatListEx, moo_pOwner, moo_pStat, moo_pItemStatCostTxtRecord);
				setup_data(original_pStatListEx, original_pOwner, original_pStat, original_pItemStatCostTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nLayer_StatId, &moo_pItemStatCostTxtRecord);
				const auto original_result = original(&original_pStatListEx, nLayer_StatId, &original_pItemStatCostTxtRecord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
				MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");

				CHECK_EQ(moo_result, (itemstatcost_txt[i].dwMinAccr << itemstatcost_txt[i].nValShift));
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB63E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetTotalStat_6FDB63E0, dll_base + 0x000763E0);
		
		SUBCASE("D2StatListStrc")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			
			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				const auto setup_data = [this, i, &stat_array](
					D2StatListStrc& pStatList,
					const std::unique_ptr<D2StatStrc[]>& pStat,
					D2ItemStatCostTxt& pItemStatCostTxtRecord
				) {
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatList.Stats.pStat = pStat.get();
					pStatList.Stats.nStatCount = itemstatcost_record_count;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				setup_data(moo_pStatList, moo_pStat, moo_pItemStatCostTxtRecord);
				setup_data(original_pStatList, original_pStat, original_pItemStatCostTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatList, nLayer_StatId, &moo_pItemStatCostTxtRecord);
				const auto original_result = original(&original_pStatList, nLayer_StatId, &original_pItemStatCostTxtRecord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
				MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}

		SUBCASE("D2StatListExStrc")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}
			
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				const auto setup_data = [this, i, &stat_array](
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pStat,
					D2ItemStatCostTxt& pItemStatCostTxtRecord
				) {
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.FullStats.pStat = pStat.get();
					pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				setup_data(moo_pStatListEx, moo_pStat, moo_pItemStatCostTxtRecord);
				setup_data(original_pStatListEx, original_pStat, original_pItemStatCostTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nLayer_StatId, &moo_pItemStatCostTxtRecord);
				const auto original_result = original(&original_pStatListEx, nLayer_StatId, &original_pItemStatCostTxtRecord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
				MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}

		SUBCASE("Applies min value")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 0;
			}

			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc moo_pOwner{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2StatListExStrc original_pStatListEx{};
			D2UnitStrc original_pOwner{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};

			for (auto i : { 0, 1, 2, 3, 7, 9, 11 })
			{
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				const auto setup_data = [this, i, &stat_array](
					D2StatListExStrc& pStatListEx,
					D2UnitStrc& pOwner,
					const std::unique_ptr<D2StatStrc[]>& pStat,
					D2ItemStatCostTxt& pItemStatCostTxtRecord
				) {
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.pOwner = &pOwner;
					pOwner.dwUnitType = UNIT_PLAYER;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.FullStats.pStat = pStat.get();
					pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				setup_data(moo_pStatListEx, moo_pOwner, moo_pStat, moo_pItemStatCostTxtRecord);
				setup_data(original_pStatListEx, original_pOwner, original_pStat, original_pItemStatCostTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nLayer_StatId, &moo_pItemStatCostTxtRecord);
				const auto original_result = original(&original_pStatListEx, nLayer_StatId, &original_pItemStatCostTxtRecord);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
				MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");

				CHECK_EQ(moo_result, (itemstatcost_txt[i].dwMinAccr << itemstatcost_txt[i].nValShift));
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB64A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB64A0, dll_base + 0x000764A0);

		SUBCASE("Stat already in full stats")
		{
			// Input data
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto full_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 100 + i;

				full_stat_array[i].nLayer = 0;
				full_stat_array[i].nStat = static_cast<uint16_t>(i);
				full_stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnit{};

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				// Stats which are the base of other stat ops trigger updates of other stats (which might require reallocations)
				if (itemstatcost_txt[i].bIsBaseOfOtherStatOp)
				{
					continue;
				}

				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				const auto setup_data = [this, i, &base_stat_array, &full_stat_array](
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pBaseStat,
					const std::unique_ptr<D2StatStrc[]>& pFullStat,
					D2ItemStatCostTxt& pItemStatCostTxtRecord,
					D2UnitStrc& pUnit
				) {
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pBaseStat.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.Stats.pStat = pBaseStat.get();
					pStatListEx.Stats.nStatCount = itemstatcost_record_count;
					pStatListEx.Stats.nCapacity = itemstatcost_record_count;
					std::memcpy(pFullStat.get(), full_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.FullStats.pStat = pFullStat.get();
					pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
					pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				setup_data(moo_pStatListEx, moo_pBaseStat, moo_pFullStat, moo_pItemStatCostTxtRecord, moo_pUnit);
				setup_data(original_pStatListEx, original_pBaseStat, original_pFullStat, original_pItemStatCostTxtRecord, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nLayer_StatId, &moo_pItemStatCostTxtRecord, &moo_pUnit);
				const auto original_result = original(&original_pStatListEx, nLayer_StatId, &original_pItemStatCostTxtRecord, &original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.FullStats.pStat, moo_pStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.FullStats.pStat, original_pStatListEx.FullStats.nStatCount }), "Comparing pStatListEx->FullStats");
				MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Stat not yet in full stats")
		{
			// Input data
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 100 + i;
			}

			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatStrc moo_pFullStat[1]{};
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatStrc original_pFullStat[1]{};
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnit{};

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				// Stats which are the base of other stat ops trigger updates of other stats (which might require reallocations)
				if (itemstatcost_txt[i].bIsBaseOfOtherStatOp)
				{
					continue;
				}

				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				const auto setup_data = [this, i, &base_stat_array](
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pBaseStat,
					D2StatStrc(&pFullStat)[1],
					D2ItemStatCostTxt& pItemStatCostTxtRecord,
					D2UnitStrc& pUnit
				) {
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pBaseStat.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.Stats.pStat = pBaseStat.get();
					pStatListEx.Stats.nStatCount = itemstatcost_record_count;
					pStatListEx.Stats.nCapacity = itemstatcost_record_count;
					pFullStat[0] = {};
					pStatListEx.FullStats.pStat = pFullStat;
					pStatListEx.FullStats.nStatCount = 0;
					pStatListEx.FullStats.nCapacity = 1;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				setup_data(moo_pStatListEx, moo_pBaseStat, moo_pFullStat, moo_pItemStatCostTxtRecord, moo_pUnit);
				setup_data(original_pStatListEx, original_pBaseStat, original_pFullStat, original_pItemStatCostTxtRecord, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nLayer_StatId, &moo_pItemStatCostTxtRecord, &moo_pUnit);
				const auto original_result = original(&original_pStatListEx, nLayer_StatId, &original_pItemStatCostTxtRecord, &original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
				MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB6920")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_FindStat_6FDB6920, dll_base + 0x00076920);
		
		SUBCASE("Returns right pointer for matching layer")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};

			const auto setup_data = [&stat_array, this](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				// Call both implementations
				const auto moo_result = sut(&moo_pStatArray, nLayer_StatId);
				const auto original_result = original(&original_pStatArray, nLayer_StatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

				CHECK_EQ(moo_result, &moo_pStat[i]);
			}
		}

		SUBCASE("Returns nullptr for non-matching layer")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 1;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};

			const auto setup_data = [&stat_array, this](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i)).nPackedValue;

				// Call both implementations
				const auto moo_result = sut(&moo_pStatArray, nLayer_StatId);
				const auto original_result = original(&original_pStatArray, nLayer_StatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

				CHECK_EQ(moo_result, nullptr);
			}
		}

		SUBCASE("Returns nullptr for non-matching stat id")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};

			const auto setup_data = [&stat_array, this](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(static_cast<uint16_t>(i + itemstatcost_record_count)).nPackedValue;

				// Call both implementations
				const auto moo_result = sut(&moo_pStatArray, nLayer_StatId);
				const auto original_result = original(&original_pStatArray, nLayer_StatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

				CHECK_EQ(moo_result, nullptr);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB6970")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_InsertStatOrFail_6FDB6970, dll_base + 0x00076970);
		
		SUBCASE("Already inserted")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(2 * size);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(2 * size);
			D2SLayerStatIdStrc::PackedType nLayer_StatId = stat_array[5].nPackedValue;

			const auto setup_data = [&stat_array, size](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = size;
				pStatArray.nCapacity = 2 * size;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pStatArray, nLayer_StatId);
			const auto original_result = original(nullptr, &original_pStatArray, nLayer_StatId);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

			CHECK_EQ(moo_result, nullptr);
		}

		SUBCASE("Inserted at end")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(2 * size);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(2 * size);
			D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(42).nPackedValue;

			const auto setup_data = [&stat_array, size](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = size;
				pStatArray.nCapacity = 2 * size;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pStatArray, nLayer_StatId);
			const auto original_result = original(nullptr, &original_pStatArray, nLayer_StatId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

			CHECK_EQ(moo_result, &moo_pStatArray.pStat[size]);
			CHECK_EQ(moo_pStatArray.nStatCount, size + 1);
		}

		SUBCASE("Inserted in the middle")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(2 * size);
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(2 * size);
			D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::Make(1, size / 2).nPackedValue;

			const auto setup_data = [&stat_array, size](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = size;
				pStatArray.nCapacity = 2 * size;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pStatArray, nLayer_StatId);
			const auto original_result = original(nullptr, &original_pStatArray, nLayer_StatId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");

			CHECK_EQ(moo_result, &moo_pStatArray.pStat[size / 2 + 1]);
			CHECK_EQ(moo_pStatArray.nStatCount, size + 1);
		}

		// NOTE: Reallocation is not (yet) tested because the tests don't use Fog.dll for allocations
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB6A30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_RemoveStat_6FDB6A30, dll_base + 0x00076A30);
		
		SUBCASE("")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatsArrayStrc moo_pStatArray{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatStrc* moo_pStatToRemove = &moo_pStat[5];
			D2StatsArrayStrc original_pStatArray{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatStrc* original_pStatToRemove = &original_pStat[5];

			const auto setup_data = [&stat_array, size](
				D2StatsArrayStrc& pStatArray,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatArray.pStat = pStat.get();
				pStatArray.nStatCount = size;
				pStatArray.nCapacity = size + 3;
			};

			setup_data(moo_pStatArray, moo_pStat);
			setup_data(original_pStatArray, original_pStat);

			// Call both implementations
			sut(nullptr, &moo_pStatArray, moo_pStatToRemove);
			original(nullptr, &original_pStatArray, original_pStatToRemove);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatArray, original_pStatArray, "Comparing pStatArray");
			MOO_CHECK_EQ(moo_pStatToRemove, original_pStatToRemove, "Comparing pStatToRemove");

			CHECK_EQ(moo_pStatArray.nStatCount, size - 1);
		}

		// NOTE: Reallocation is not (yet) tested because the tests don't use Fog.dll for allocations
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB6AB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_UpdateUnitStat_6FDB6AB0, dll_base + 0x00076AB0);

		SUBCASE("Updates existing stat")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnit{};
			D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(5).nPackedValue;
			int nNewValue = 42;

			const auto setup_data = [&stat_array, size](
				D2StatListExStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2ItemStatCostTxt& pItemStatCostTxtRecord,
				D2UnitStrc& pUnit
			) {
				pStatList.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.FullStats.pStat = pStat.get();
				pStatList.FullStats.nStatCount = size;
				pStatList.FullStats.nCapacity = size + 3;
				pItemStatCostTxtRecord.bHasOpApplyingToItem = TRUE;
			};

			setup_data(moo_pStatList, moo_pStat, moo_pItemStatCostTxtRecord, moo_pUnit);
			setup_data(original_pStatList, original_pStat, original_pItemStatCostTxtRecord, original_pUnit);

			// Call both implementations
			sut(&moo_pStatList, nLayer_StatId, nNewValue, &moo_pItemStatCostTxtRecord, &moo_pUnit);
			original(&original_pStatList, nLayer_StatId, nNewValue, &original_pItemStatCostTxtRecord, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.FullStats.pStat, moo_pStatList.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.FullStats.pStat, original_pStatList.FullStats.nStatCount }), "Comparing pStatList->FullStats");
			MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_pStatList.FullStats.nStatCount, size);
			CHECK_EQ(moo_pStatList.FullStats.pStat[5].nValue, nNewValue);
			CHECK_NE(moo_pStatList.dwFlags & STATLIST_PERMANENT, 0u);
		}

		SUBCASE("Inserts new stat")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnit{};
			D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(42).nPackedValue;
			int nNewValue = 42;

			const auto setup_data = [&stat_array, size](
				D2StatListExStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2ItemStatCostTxt& pItemStatCostTxtRecord,
				D2UnitStrc& pUnit
			) {
				pStatList.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.FullStats.pStat = pStat.get();
				pStatList.FullStats.nStatCount = size;
				pStatList.FullStats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat, moo_pItemStatCostTxtRecord, moo_pUnit);
			setup_data(original_pStatList, original_pStat, original_pItemStatCostTxtRecord, original_pUnit);

			// Call both implementations
			sut(&moo_pStatList, nLayer_StatId, nNewValue, &moo_pItemStatCostTxtRecord, &moo_pUnit);
			original(&original_pStatList, nLayer_StatId, nNewValue, &original_pItemStatCostTxtRecord, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.FullStats.pStat, moo_pStatList.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.FullStats.pStat, original_pStatList.FullStats.nStatCount }), "Comparing pStatList->FullStats");
			MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_pStatList.FullStats.nStatCount, size + 1);
			CHECK_EQ(moo_pStatList.FullStats.pStat[size].nStat, 42);
			CHECK_EQ(moo_pStatList.FullStats.pStat[size].nValue, nNewValue);
		}

		SUBCASE("Removes stat with new value 0")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnit{};
			D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(5).nPackedValue;
			int nNewValue = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListExStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2ItemStatCostTxt& pItemStatCostTxtRecord,
				D2UnitStrc& pUnit
			) {
				pStatList.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.FullStats.pStat = pStat.get();
				pStatList.FullStats.nStatCount = size;
				pStatList.FullStats.nCapacity = size + 3;
				pItemStatCostTxtRecord.nKeepZero = FALSE;
			};

			setup_data(moo_pStatList, moo_pStat, moo_pItemStatCostTxtRecord, moo_pUnit);
			setup_data(original_pStatList, original_pStat, original_pItemStatCostTxtRecord, original_pUnit);

			// Call both implementations
			sut(&moo_pStatList, nLayer_StatId, nNewValue, &moo_pItemStatCostTxtRecord, &moo_pUnit);
			original(&original_pStatList, nLayer_StatId, nNewValue, &original_pItemStatCostTxtRecord, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.FullStats.pStat, moo_pStatList.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.FullStats.pStat, original_pStatList.FullStats.nStatCount }), "Comparing pStatList->FullStats");
			MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_pStatList.FullStats.nStatCount, size - 1);
			CHECK_EQ(moo_pStatList.FullStats.pStat[5].nStat, 6);
		}

		SUBCASE("Keeps stat with new value 0 if nKeepZero is set")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnit{};
			D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(5).nPackedValue;
			int nNewValue = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListExStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2ItemStatCostTxt& pItemStatCostTxtRecord,
				D2UnitStrc& pUnit
			) {
				pStatList.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.FullStats.pStat = pStat.get();
				pStatList.FullStats.nStatCount = size;
				pStatList.FullStats.nCapacity = size + 3;
				pItemStatCostTxtRecord.nKeepZero = TRUE;
			};

			setup_data(moo_pStatList, moo_pStat, moo_pItemStatCostTxtRecord, moo_pUnit);
			setup_data(original_pStatList, original_pStat, original_pItemStatCostTxtRecord, original_pUnit);

			// Call both implementations
			sut(&moo_pStatList, nLayer_StatId, nNewValue, &moo_pItemStatCostTxtRecord, &moo_pUnit);
			original(&original_pStatList, nLayer_StatId, nNewValue, &original_pItemStatCostTxtRecord, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.FullStats.pStat, moo_pStatList.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.FullStats.pStat, original_pStatList.FullStats.nStatCount }), "Comparing pStatList->FullStats");
			MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_pStatList.FullStats.nStatCount, size);
			CHECK_EQ(moo_pStatList.FullStats.pStat[5].nValue, 0);
		}

		// NOTE: Reallocation is not (yet) tested because the tests don't use Fog.dll for allocations
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB6C10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB6C10, dll_base + 0x00076C10);

		SUBCASE("Extended stat list")
		{
			// Input data
			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			int nValue = 1000;

			const auto setup_data = [this, &stat_array](
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2UnitStrc& pUnit
			) {
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
			};

			for (const auto nStatId : plain_stat_ids)
			{
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(nStatId).nPackedValue;

				setup_data(moo_pStatListEx, moo_pStat, moo_pUnit);
				setup_data(original_pStatListEx, original_pStat, original_pUnit);

				// Call both implementations
				sut(&moo_pStatListEx, nLayer_StatId, nValue, &moo_pUnit);
				original(&original_pStatListEx, nLayer_StatId, nValue, &original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.FullStats.pStat, moo_pStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.FullStats.pStat, original_pStatListEx.FullStats.nStatCount }), "Comparing pStatListEx->FullStats");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_pStat[nStatId].nValue, stat_array[nStatId].nValue + nValue);
			}
		}

		SUBCASE("Regular stat list with extended parent")
		{
			// Input data
			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatListEx{};
			D2StatListExStrc moo_pParentStatListEx{};
			const auto moo_pParentStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListExStrc original_pParentStatListEx{};
			const auto original_pParentStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			int nValue = -1000;

			const auto setup_data = [this, &stat_array](
				D2StatListExStrc& pStatListEx,
				D2StatListExStrc& pParentStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pParentStat,
				D2UnitStrc& pUnit
			) {
				pStatListEx.pParent = &pParentStatListEx;
				pParentStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pParentStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pParentStatListEx.FullStats.pStat = pParentStat.get();
				pParentStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pParentStatListEx.FullStats.nCapacity = itemstatcost_record_count;
			};

			for (const auto nStatId : plain_stat_ids)
			{
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(nStatId).nPackedValue;

				setup_data(moo_pStatListEx, moo_pParentStatListEx, moo_pParentStat, moo_pUnit);
				setup_data(original_pStatListEx, original_pParentStatListEx, original_pParentStat, original_pUnit);

				// Call both implementations
				sut(&moo_pStatListEx, nLayer_StatId, nValue, &moo_pUnit);
				original(&original_pStatListEx, nLayer_StatId, nValue, &original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
				MOO_CHECK_EQ(moo_pParentStatListEx, original_pParentStatListEx, "Comparing pParentStatListEx");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pParentStatListEx.FullStats.pStat, moo_pParentStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pParentStatListEx.FullStats.pStat, original_pParentStatListEx.FullStats.nStatCount }), "Comparing pParentStatListEx->FullStats");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_pParentStat[nStatId].nValue, stat_array[nStatId].nValue + nValue);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB6E30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_ExpireStatList_6FDB6E30, dll_base + 0x00076E30);

		SUBCASE("")
		{
			// Input data
			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count, 10);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = plain_stat_ids[i];
				stat_array[i].nValue = 100 + i;
			}

			const auto parent_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				parent_stat_array[i].nLayer = 0;
				parent_stat_array[i].nStat = static_cast<uint16_t>(i);
				parent_stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2StatListStrc moo_pPreviousStatList{};
			D2StatListExStrc moo_pParentStatListEx{};
			const auto moo_pParentStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2StatListStrc original_pPreviousStatList{};
			D2StatListExStrc original_pParentStatListEx{};
			const auto original_pParentStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, stat_count, &stat_array, &parent_stat_array](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2StatListStrc& pPreviousStatList,
				D2StatListExStrc& pParentStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pParentStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = stat_count;
				pStatList.Stats.nCapacity = stat_count;
				pStatList.pParent = &pParentStatListEx;
				pStatList.pPrevLink = &pPreviousStatList;
				pPreviousStatList.pNextLink = &pStatList;
				pPreviousStatList.pParent = &pParentStatListEx;
				pParentStatListEx.dwFlags |= STATLIST_EXTENDED;
				pParentStatListEx.pMyLastList = &pStatList;
				std::memcpy(pParentStat.get(), parent_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pParentStatListEx.FullStats.pStat = pParentStat.get();
				pParentStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pParentStatListEx.FullStats.nCapacity = itemstatcost_record_count;
			};

			setup_data(moo_pStatList, moo_pStat, moo_pPreviousStatList, moo_pParentStatListEx, moo_pParentStat);
			setup_data(original_pStatList, original_pStat, original_pPreviousStatList, original_pParentStatListEx, original_pParentStat);

			// Call both implementations
			sut(&moo_pStatList);
			original(&original_pStatList);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ(moo_pPreviousStatList, original_pPreviousStatList, "Comparing pPreviousStatList");
			MOO_CHECK_EQ(moo_pParentStatListEx, original_pParentStatListEx, "Comparing pParentStatListEx");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pParentStatListEx.FullStats.pStat, moo_pParentStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pParentStatListEx.FullStats.pStat, original_pParentStatListEx.FullStats.nStatCount }), "Comparing pParentStatListEx->FullStats");

			CHECK_EQ(moo_pStatList.pParent, nullptr);
			CHECK_EQ(moo_pStatList.pPrevLink, nullptr);
			CHECK_EQ(moo_pPreviousStatList.pNextLink, nullptr);
			CHECK_EQ(moo_pParentStatListEx.pMyLastList, &moo_pPreviousStatList);

			for (auto i = 0; i < stat_count; ++i)
			{
				CHECK_EQ(moo_pParentStat[plain_stat_ids[i]].nValue, parent_stat_array[plain_stat_ids[i]].nValue - stat_array[i].nValue);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7030 (#10485)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_FreeStatList, dll_base + 0x00077030);
		const auto [moo_alloc, original_alloc] = make_function_pair(STATLIST_AllocStatList, dll_base + 0x00077140);

		SUBCASE("")
		{
			// Input data
			uint32_t fFilter = random_unsigned_integer();
			uint32_t dwTimeout = random_unsigned_integer();
			int nUnitType = random_unsigned_integer();
			D2UnitGUID nUnitGUID = random_unsigned_integer();

			D2StatListStrc* moo_pStatList = moo_alloc(nullptr, fFilter, dwTimeout, nUnitType, nUnitGUID);
			D2StatListStrc* original_pStatList = original_alloc(nullptr, fFilter, dwTimeout, nUnitType, nUnitGUID);

			// Call both implementations
			sut(moo_pStatList);
			original(original_pStatList);

			// Input data can not be compared since it was freed
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7050" * doctest::skip("Not really testable"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_STATLIST_FreeStatListImpl_6FDB7050, dll_base + 0x00077050);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [](
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			sut(&moo_pStatList);
			original(&original_pStatList);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7110 (#10527)" * doctest::skip("Not really testable"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_FreeStatListEx, dll_base + 0x00077110);
		
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
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7140 (#10470)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_AllocStatList, dll_base + 0x00077140);
		
		SUBCASE("")
		{
			uint32_t fFilter = random_unsigned_integer();
			uint32_t dwTimeout = random_unsigned_integer();
			int nUnitType = random_unsigned_integer();
			D2UnitGUID nUnitGUID = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(nullptr, fFilter, dwTimeout, nUnitType, nUnitGUID);
			const auto original_result = original(nullptr, fFilter, dwTimeout, nUnitType, nUnitGUID);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(StatesTxtFixture<NoopFixture>, "D2Common.0x6FDB7190 (#10526)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_AllocStatListEx, dll_base + 0x00077190);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = random_unsigned_integer();
			const auto unit_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2GameStrc moo_pGame{};
			D2UnitStrc original_pUnit{};
			D2GameStrc original_pGame{};
			char nFlags = random_unsigned_integer(0, 127);
			StatListValueChangeFunc pfOnValueChanged = (StatListValueChangeFunc)random_unsigned_integer();

			const auto setup_data = [unit_type, unit_id](
				D2UnitStrc& pUnit,
				D2GameStrc& pGame
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwUnitId = unit_id;
			};

			setup_data(moo_pUnit, moo_pGame);
			setup_data(original_pUnit, original_pGame);

			// Call both implementations
			sut(&moo_pUnit, nFlags, pfOnValueChanged, &moo_pGame);
			original(&original_pUnit, nFlags, pfOnValueChanged, &original_pGame);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			//SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7260 (#10471)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetOwnerType, dll_base + 0x00077260);
		
		SUBCASE("")
		{
			// Input data
			const auto owner_type = random_unsigned_integer();

			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [owner_type](
				D2StatListStrc& pStatList
			) {
				pStatList.dwOwnerType = owner_type;
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList);
			const auto original_result = original(&original_pStatList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD912D0 (#10472)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetOwnerGUID, dll_base + 0x000512D0);
		
		SUBCASE("")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();

			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [owner_id](
				D2StatListStrc& pStatList
			) {
				pStatList.dwOwnerId = owner_id;
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList);
			const auto original_result = original(&original_pStatList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7280 (#11304)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetBaseStatsCount, dll_base + 0x00077280);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_count = random_unsigned_integer(0, 8192);

			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [stat_count](
				D2StatListStrc& pStatList
			) {
				pStatList.Stats.nStatCount = stat_count;
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList);
			const auto original_result = original(&original_pStatList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB72A0 (#11305)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetFullStatsCountFromUnit, dll_base + 0x000772A0);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_count = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};

			const auto setup_data = [stat_count](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pUnit.pStatListEx = &pStatListEx;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB72C0 (#10478)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetState, dll_base + 0x000772C0);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nState = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pStatList, nState);
			original(&original_pStatList, nState);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB72E0 (#10479)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetState, dll_base + 0x000772E0);
		
		SUBCASE("")
		{
			// Input data
			const auto state = random_unsigned_integer();

			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [state](
				D2StatListStrc& pStatList
			) {
				pStatList.dwStateNo = state;
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList);
			const auto original_result = original(&original_pStatList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7300 (#10528)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetExpireFrame, dll_base + 0x00077300);
		
		SUBCASE("nExpireFrame = 0")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nExpireFrame = 0;

			// Call both implementations
			sut(&moo_pStatList, nExpireFrame);
			original(&original_pStatList, nExpireFrame);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}

		SUBCASE("nExpireFrame = random_unsigned_integer()")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nExpireFrame = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pStatList, nExpireFrame);
			original(&original_pStatList, nExpireFrame);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7320 (#10529)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetExpireFrame, dll_base + 0x00077320);
		
		SUBCASE("")
		{
			// Input data
			const auto expire_frame = random_unsigned_integer();

			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [expire_frame](
				D2StatListStrc& pStatList
			) {
				pStatList.dwExpireFrame = expire_frame;
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList);
			const auto original_result = original(&original_pStatList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7340 (#10475)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10475_PostStatToStatList, dll_base + 0x00077340);

		SUBCASE("Regular stat list")
		{
			// Input data
			const BOOL reset_flag = GENERATE(FALSE, TRUE);

			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count, 10);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = plain_stat_ids[i];
				stat_array[i].nValue = 100 + i;
			}

			const auto unit_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				unit_stat_array[i].nLayer = 0;
				unit_stat_array[i].nStat = static_cast<uint16_t>(i);
				unit_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pUnitStatListEx{};
			const auto moo_pUnitStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc moo_pPreviousStatList{};
			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pUnitStatListEx{};
			const auto original_pUnitStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc original_pPreviousStatList{};
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			BOOL bResetFlag = reset_flag;

			const auto setup_data = [this, stat_count, &stat_array, &unit_stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pUnitStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pUnitStat,
				D2StatListStrc& pPreviousStatList,
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pUnitStatListEx;
				pUnitStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pUnitStat.get(), unit_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pUnitStatListEx.FullStats.pStat = pUnitStat.get();
				pUnitStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pUnitStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				pUnitStatListEx.pMyLastList = &pPreviousStatList;
				pPreviousStatList.pParent = &pUnitStatListEx;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = stat_count;
				pStatList.Stats.nCapacity = stat_count;
			};

			setup_data(moo_pUnit, moo_pUnitStatListEx, moo_pUnitStat, moo_pPreviousStatList, moo_pStatList, moo_pStat);
			setup_data(original_pUnit, original_pUnitStatListEx, original_pUnitStat, original_pPreviousStatList, original_pStatList, original_pStat);

			// Call both implementations
			sut(&moo_pUnit, &moo_pStatList, bResetFlag);
			original(&original_pUnit, &original_pStatList, bResetFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pUnitStatListEx.FullStats.pStat, moo_pUnitStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pUnitStatListEx.FullStats.pStat, original_pUnitStatListEx.FullStats.nStatCount }), "Comparing pUnitStatListEx->FullStats");
			MOO_CHECK_EQ(moo_pPreviousStatList, original_pPreviousStatList, "Comparing pPreviousStatList");
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");

			CHECK_EQ(moo_pUnitStatListEx.pMyLastList, &moo_pStatList);
			CHECK_EQ(moo_pStatList.pParent, &moo_pUnitStatListEx);
			CHECK_EQ(moo_pStatList.pUnit, &moo_pUnit);
			CHECK_EQ(moo_pStatList.pPrevLink, &moo_pPreviousStatList);
			CHECK_EQ(moo_pPreviousStatList.pNextLink, &moo_pStatList);

			if (bResetFlag)
			{
				for (auto i = 0; i < stat_count; ++i)
				{
					CHECK_EQ(moo_pUnitStat[plain_stat_ids[i]].nValue, unit_stat_array[plain_stat_ids[i]].nValue + stat_array[i].nValue);
				}
			}
		}

		SUBCASE("Stat list with STATLIST_SET")
		{
			// Input data
			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count, 10);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = plain_stat_ids[i];
				stat_array[i].nValue = 100 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pUnitStatListEx{};
			D2StatListStrc moo_pPreviousStatList{};
			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pUnitStatListEx{};
			D2StatListStrc original_pPreviousStatList{};
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			BOOL bResetFlag = TRUE;

			const auto setup_data = [stat_count, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pUnitStatListEx,
				D2StatListStrc& pPreviousStatList,
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pUnitStatListEx;
				pUnitStatListEx.dwFlags |= STATLIST_EXTENDED;
				pUnitStatListEx.pMyStats = &pPreviousStatList;
				pPreviousStatList.dwFlags = STATLIST_SET;
				pPreviousStatList.pParent = &pUnitStatListEx;
				pStatList.dwFlags = STATLIST_SET;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = stat_count;
				pStatList.Stats.nCapacity = stat_count;
			};

			setup_data(moo_pUnit, moo_pUnitStatListEx, moo_pPreviousStatList, moo_pStatList, moo_pStat);
			setup_data(original_pUnit, original_pUnitStatListEx, original_pPreviousStatList, original_pStatList, original_pStat);

			// Call both implementations
			sut(&moo_pUnit, &moo_pStatList, bResetFlag);
			original(&original_pUnit, &original_pStatList, bResetFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pPreviousStatList, original_pPreviousStatList, "Comparing pPreviousStatList");
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");

			CHECK_EQ(moo_pUnitStatListEx.pMyStats, &moo_pStatList);
			CHECK_EQ(moo_pUnitStatListEx.pMyLastList, nullptr);
			CHECK_EQ(moo_pStatList.pParent, &moo_pUnitStatListEx);
			CHECK_EQ(moo_pStatList.pUnit, &moo_pUnit);
			CHECK_EQ(moo_pStatList.pPrevLink, &moo_pPreviousStatList);
			CHECK_EQ(moo_pPreviousStatList.pNextLink, &moo_pStatList);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7560 (#10464)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_AddStat, dll_base + 0x00077560);

		SUBCASE("Adds value to existing stat")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			int nStatId = 5;
			int nValue = 42;
			uint16_t nLayer = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			sut(&moo_pStatList, nStatId, nValue, nLayer);
			original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_pStatList.Stats.nStatCount, size);
			CHECK_EQ(moo_pStatList.Stats.pStat[nStatId].nValue, stat_array[nStatId].nValue + nValue);
		}

		SUBCASE("Inserts new stat")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			int nStatId = 42;
			int nValue = 42;
			uint16_t nLayer = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			sut(&moo_pStatList, nStatId, nValue, nLayer);
			original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_pStatList.Stats.nStatCount, size + 1);
			CHECK_EQ(moo_pStatList.Stats.pStat[size].nStat, nStatId);
			CHECK_EQ(moo_pStatList.Stats.pStat[size].nValue, nValue);
		}

		SUBCASE("Removes stat reaching 0")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			int nStatId = 5;
			int nValue = -stat_array[nStatId].nValue;
			uint16_t nLayer = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			sut(&moo_pStatList, nStatId, nValue, nLayer);
			original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_pStatList.Stats.nStatCount, size - 1);
			CHECK_EQ(moo_pStatList.Stats.pStat[nStatId].nStat, nStatId + 1);
		}

		// NOTE: Reallocation is not (yet) tested because the tests don't use Fog.dll for allocations
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7690")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_InsertStatModOrFail_6FDB7690, dll_base + 0x00077690);
		
		SUBCASE("")
		{
			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				// Input data
				const auto size = 20;
				const auto stat_array = std::make_unique<D2StatStrc[]>(size);
				std::memset(stat_array.get(), 0, sizeof(D2StatStrc) * size);

				D2StatListExStrc moo_pStatListEx{};
				D2StatsArrayStrc moo_pStatArray{};
				const auto moo_pStat = std::make_unique<D2StatStrc[]>(size);
				D2StatListExStrc original_pStatListEx{};
				D2StatsArrayStrc original_pStatArray{};
				const auto original_pStat = std::make_unique<D2StatStrc[]>(size);
				D2SLayerStatIdStrc::PackedType nLayer_StatId = D2SLayerStatIdStrc::MakeFromStatId(i).nPackedValue;

				const auto setup_data = [&stat_array, size](
					D2StatListExStrc& pStatListEx,
					D2StatsArrayStrc& pStatArray,
					const std::unique_ptr<D2StatStrc[]>& pStat
				) {
					pStatListEx.ModStats.pStat = pStat.get();
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
					pStatArray.pStat = pStat.get();
					pStatArray.nStatCount = 0;
					pStatArray.nCapacity = size;
				};

				setup_data(moo_pStatListEx, moo_pStatArray, moo_pStat);
				setup_data(original_pStatListEx, original_pStatArray, original_pStat);

				// Call both implementations
				sut(&moo_pStatListEx, nLayer_StatId);
				original(&original_pStatListEx, nLayer_StatId);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB77B0 (#10463)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetStat, dll_base + 0x000777B0);

		SUBCASE("Changes existing stat")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			int nStatId = 5;
			int nValue = 42;
			uint16_t nLayer = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, nValue, nLayer);
			const auto original_result = original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_result, TRUE);
			CHECK_EQ(moo_pStatList.Stats.nStatCount, size);
			CHECK_EQ(moo_pStatList.Stats.pStat[nStatId].nValue, nValue);
		}

		SUBCASE("Inserts new stat")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			int nStatId = 42;
			int nValue = 42;
			uint16_t nLayer = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, nValue, nLayer);
			const auto original_result = original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_result, TRUE);
			CHECK_EQ(moo_pStatList.Stats.nStatCount, size + 1);
			CHECK_EQ(moo_pStatList.Stats.pStat[size].nStat, nStatId);
			CHECK_EQ(moo_pStatList.Stats.pStat[size].nValue, nValue);
		}

		SUBCASE("Removes stat set to 0")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			int nStatId = 5;
			int nValue = 0;
			uint16_t nLayer = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, nValue, nLayer);
			const auto original_result = original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_result, TRUE);
			CHECK_EQ(moo_pStatList.Stats.nStatCount, size - 1);
			CHECK_EQ(moo_pStatList.Stats.pStat[nStatId].nStat, nStatId + 1);
		}

		SUBCASE("Unchanged value")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			int nStatId = 5;
			int nValue = stat_array[nStatId].nValue;
			uint16_t nLayer = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, nValue, nLayer);
			const auto original_result = original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_result, FALSE);
			CHECK_EQ(moo_pStatList.Stats.nStatCount, size);
		}

		// NOTE: Reallocation is not (yet) tested because the tests don't use Fog.dll for allocations
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7910 (#10465)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetStatIfListIsValid, dll_base + 0x00077910);

		SUBCASE("pStatList = nullptr")
		{
			// Input data
			int nStatId = 5;
			int nValue = 42;
			uint16_t nLayer = 0;

			// Call both implementations
			sut(nullptr, nStatId, nValue, nLayer);
			original(nullptr, nStatId, nValue, nLayer);
		}

		SUBCASE("Changes existing stat")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size + 3);
			int nStatId = 5;
			int nValue = 42;
			uint16_t nLayer = 0;

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size + 3;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			sut(&moo_pStatList, nStatId, nValue, nLayer);
			original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_pStatList.Stats.pStat[nStatId].nValue, nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7930 (#11294)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetBaseStat, dll_base + 0x00077930);

		SUBCASE("")
		{
			// Input data
			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto full_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 100 + i;

				full_stat_array[i].nLayer = 0;
				full_stat_array[i].nStat = static_cast<uint16_t>(i);
				full_stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(itemstatcost_record_count);
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			uint16_t nLayer = 0;

			const auto setup_data = [this, &base_stat_array, &full_stat_array](
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pBaseStat,
				const std::unique_ptr<D2StatStrc[]>& pFullStat,
				const std::unique_ptr<D2SLayerStatIdStrc[]>& pModStat,
				D2UnitStrc& pUnit
			) {
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = UNIT_PLAYER;
				std::memcpy(pBaseStat.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.Stats.pStat = pBaseStat.get();
				pStatListEx.Stats.nStatCount = itemstatcost_record_count;
				pStatListEx.Stats.nCapacity = itemstatcost_record_count;
				std::memcpy(pFullStat.get(), full_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pFullStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				std::memset(pModStat.get(), 0, sizeof(D2SLayerStatIdStrc) * itemstatcost_record_count);
				pStatListEx.ModStats.pStat = pModStat.get();
				pStatListEx.ModStats.nStatCount = 0;
				pStatListEx.ModStats.nCapacity = itemstatcost_record_count;
			};

			for (const auto nStatId : plain_stat_ids)
			{
				int nValue = 200 + nStatId;

				setup_data(moo_pStatListEx, moo_pBaseStat, moo_pFullStat, moo_pModStat, moo_pUnit);
				setup_data(original_pStatListEx, original_pBaseStat, original_pFullStat, original_pModStat, original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nStatId, nValue, nLayer, &moo_pUnit);
				const auto original_result = original(&original_pStatListEx, nStatId, nValue, nLayer, &original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.Stats.pStat, moo_pStatListEx.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.Stats.pStat, original_pStatListEx.Stats.nStatCount }), "Comparing pStatListEx->Stats");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.FullStats.pStat, moo_pStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.FullStats.pStat, original_pStatListEx.FullStats.nStatCount }), "Comparing pStatListEx->FullStats");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, TRUE);
				CHECK_EQ(moo_pBaseStat[nStatId].nValue, nValue);
				CHECK_EQ(moo_pFullStat[nStatId].nValue, full_stat_array[nStatId].nValue + nValue - base_stat_array[nStatId].nValue);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7AB0 (#10517)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetUnitStat, dll_base + 0x00077AB0);

		SUBCASE("")
		{
			// Input data
			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto full_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 100 + i;

				full_stat_array[i].nLayer = 0;
				full_stat_array[i].nStat = static_cast<uint16_t>(i);
				full_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(itemstatcost_record_count);
			uint16_t nLayer = 0;

			const auto setup_data = [this, &base_stat_array, &full_stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pBaseStat,
				const std::unique_ptr<D2StatStrc[]>& pFullStat,
				const std::unique_ptr<D2SLayerStatIdStrc[]>& pModStat
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = UNIT_PLAYER;
				std::memcpy(pBaseStat.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.Stats.pStat = pBaseStat.get();
				pStatListEx.Stats.nStatCount = itemstatcost_record_count;
				pStatListEx.Stats.nCapacity = itemstatcost_record_count;
				std::memcpy(pFullStat.get(), full_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pFullStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				std::memset(pModStat.get(), 0, sizeof(D2SLayerStatIdStrc) * itemstatcost_record_count);
				pStatListEx.ModStats.pStat = pModStat.get();
				pStatListEx.ModStats.nStatCount = 0;
				pStatListEx.ModStats.nCapacity = itemstatcost_record_count;
			};

			for (const auto nStatId : plain_stat_ids)
			{
				int nValue = 200 + nStatId;

				setup_data(moo_pUnit, moo_pStatListEx, moo_pBaseStat, moo_pFullStat, moo_pModStat);
				setup_data(original_pUnit, original_pStatListEx, original_pBaseStat, original_pFullStat, original_pModStat);

				// Call both implementations
				sut(&moo_pUnit, nStatId, nValue, nLayer);
				original(&original_pUnit, nStatId, nValue, nLayer);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.Stats.pStat, moo_pStatListEx.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.Stats.pStat, original_pStatListEx.Stats.nStatCount }), "Comparing pStatListEx->Stats");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.FullStats.pStat, moo_pStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.FullStats.pStat, original_pStatListEx.FullStats.nStatCount }), "Comparing pStatListEx->FullStats");

				CHECK_EQ(moo_pBaseStat[nStatId].nValue, nValue);
				CHECK_EQ(moo_pFullStat[nStatId].nValue, full_stat_array[nStatId].nValue + nValue - base_stat_array[nStatId].nValue);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7B00 (#10518)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_AddUnitStat, dll_base + 0x00077B00);

		SUBCASE("")
		{
			// Input data
			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto full_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 100 + i;

				full_stat_array[i].nLayer = 0;
				full_stat_array[i].nStat = static_cast<uint16_t>(i);
				full_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(itemstatcost_record_count);
			int nValue = 42;
			uint16_t nLayer = 0;

			const auto setup_data = [this, &base_stat_array, &full_stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pBaseStat,
				const std::unique_ptr<D2StatStrc[]>& pFullStat,
				const std::unique_ptr<D2SLayerStatIdStrc[]>& pModStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = UNIT_PLAYER;
				std::memcpy(pBaseStat.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.Stats.pStat = pBaseStat.get();
				pStatListEx.Stats.nStatCount = itemstatcost_record_count;
				pStatListEx.Stats.nCapacity = itemstatcost_record_count;
				std::memcpy(pFullStat.get(), full_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pFullStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				std::memset(pModStat.get(), 0, sizeof(D2SLayerStatIdStrc) * itemstatcost_record_count);
				pStatListEx.ModStats.pStat = pModStat.get();
				pStatListEx.ModStats.nStatCount = 0;
				pStatListEx.ModStats.nCapacity = itemstatcost_record_count;
			};

			for (const auto nStatId : plain_stat_ids)
			{
				setup_data(moo_pUnit, moo_pStatListEx, moo_pBaseStat, moo_pFullStat, moo_pModStat);
				setup_data(original_pUnit, original_pStatListEx, original_pBaseStat, original_pFullStat, original_pModStat);

				// Call both implementations
				sut(&moo_pUnit, nStatId, nValue, nLayer);
				original(&original_pUnit, nStatId, nValue, nLayer);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.Stats.pStat, moo_pStatListEx.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.Stats.pStat, original_pStatListEx.Stats.nStatCount }), "Comparing pStatListEx->Stats");
				MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.FullStats.pStat, moo_pStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.FullStats.pStat, original_pStatListEx.FullStats.nStatCount }), "Comparing pStatListEx->FullStats");

				CHECK_EQ(moo_pBaseStat[nStatId].nValue, base_stat_array[nStatId].nValue + nValue);
				CHECK_EQ(moo_pFullStat[nStatId].nValue, full_stat_array[nStatId].nValue + nValue);
			}
		}
	}
		
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7B30 (#10521)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetUnitBaseStat, dll_base + 0x00077B30);

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			uint16_t nLayer = 0;

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				const auto setup_data = [this, i, &stat_array](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pStat
				) {
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.Stats.pStat = pStat.get();
					pStatListEx.Stats.nStatCount = itemstatcost_record_count;
				};

				int nStatId = i;

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
				setup_data(original_pUnit, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nStatId, nLayer);
				const auto original_result = original(&original_pUnit, nStatId, nLayer);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7C30 (#10519)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_UnitGetStatValue, dll_base + 0x00077C30);

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			uint16_t nLayer = 0;

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				const auto setup_data = [this, i, &stat_array](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pStat
				) {
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.FullStats.pStat = pStat.get();
					pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				};

				int nStatId = i;

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
				setup_data(original_pUnit, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nStatId, nLayer);
				const auto original_result = original(&original_pUnit, nStatId, nLayer);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7E30 (#10520)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_UnitGetItemStatOrSkillStatValue, dll_base + 0x00077E30);

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			uint16_t nLayer = 0;

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				const auto setup_data = [this, i, &stat_array](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pStat
				) {
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.FullStats.pStat = pStat.get();
					pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				};

				int nStatId = i;

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
				setup_data(original_pUnit, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nStatId, nLayer);
				const auto original_result = original(&original_pUnit, nStatId, nLayer);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7D40 (#10466)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatValue, dll_base + 0x00077D40);

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			uint16_t nLayer = 0;

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				const auto setup_data = [this, i, &stat_array](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pStat
				) {
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.Stats.pStat = pStat.get();
					pStatListEx.Stats.nStatCount = itemstatcost_record_count;
				};

				int nStatId = i;

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
				setup_data(original_pUnit, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nStatId, nLayer);
				const auto original_result = original(&original_pStatListEx, nStatId, nLayer);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}
	}

	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB7F40 (#10522)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetUnitStatBonus, dll_base + 0x00077F40);

		SUBCASE("")
		{
			// Input data
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 10000 - (i + 1);
			}

			const auto full_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				full_stat_array[i].nLayer = 0;
				full_stat_array[i].nStat = static_cast<uint16_t>(i);
				full_stat_array[i].nValue = 10000 + (i + 1);
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			uint16_t nLayer = 0;

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				const auto setup_data = [this, i, &base_stat_array, &full_stat_array](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pBaseStat,
					const std::unique_ptr<D2StatStrc[]>& pFullStat
				) {
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pBaseStat.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					std::memcpy(pFullStat.get(), full_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.Stats.pStat = pBaseStat.get();
					pStatListEx.Stats.nStatCount = itemstatcost_record_count;
					pStatListEx.FullStats.pStat = pFullStat.get();
					pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				};

				int nStatId = i;

				setup_data(moo_pUnit, moo_pStatListEx, moo_pBaseStat, moo_pFullStat);
				setup_data(original_pUnit, original_pStatListEx, original_pBaseStat, original_pFullStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nStatId, nLayer);
				const auto original_result = original(&original_pUnit, nStatId, nLayer);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, 2 * (i + 1));
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB80C0 (#10515)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_DeactivateTemporaryStates, dll_base + 0x000780C0);
		const auto [moo_alloc, original_alloc] = make_function_pair(STATLIST_AllocStatList, dll_base + 0x00077140);

		SUBCASE("STATLIST_NEWLENGTH is not set")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pTemporaryStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pTemporaryStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pTemporaryStatList
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pTemporaryStatList;
				pTemporaryStatList.dwFlags = STATLIST_TEMPONLY;
				pTemporaryStatList.pParent = &pStatListEx;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pTemporaryStatList);
			setup_data(original_pUnit, original_pStatListEx, original_pTemporaryStatList);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pTemporaryStatList, original_pTemporaryStatList, "Comparing pTemporaryStatList");

			CHECK_EQ(moo_pStatListEx.pMyLastList, &moo_pTemporaryStatList);
		}

		SUBCASE("Frees temporary stat lists")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc* moo_pTemporaryStatList = moo_alloc(nullptr, STATLIST_TEMPONLY, 0, UNIT_PLAYER, 0);
			D2StatListStrc moo_pPermanentStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc* original_pTemporaryStatList = original_alloc(nullptr, STATLIST_TEMPONLY, 0, UNIT_PLAYER, 0);
			D2StatListStrc original_pPermanentStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pTemporaryStatList,
				D2StatListStrc& pPermanentStatList
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED | STATLIST_NEWLENGTH;
				pStatListEx.pMyLastList = &pTemporaryStatList;
				pTemporaryStatList.pParent = &pStatListEx;
				pTemporaryStatList.pPrevLink = &pPermanentStatList;
				pPermanentStatList.pParent = &pStatListEx;
				pPermanentStatList.pNextLink = &pTemporaryStatList;
			};

			setup_data(moo_pUnit, moo_pStatListEx, *moo_pTemporaryStatList, moo_pPermanentStatList);
			setup_data(original_pUnit, original_pStatListEx, *original_pTemporaryStatList, original_pPermanentStatList);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			// pTemporaryStatList can not be compared since it was freed
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pPermanentStatList, original_pPermanentStatList, "Comparing pPermanentStatList");

			CHECK_EQ(moo_pStatListEx.pMyLastList, &moo_pPermanentStatList);
			CHECK_EQ(moo_pPermanentStatList.pNextLink, nullptr);
			CHECK_EQ(moo_pStatListEx.dwFlags & STATLIST_NEWLENGTH, 0u);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8120 (#10467)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10467, dll_base + 0x00078120);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_count = 10;
			const auto stats = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				stats[i].nValue = random_unsigned_integer();
			}

			for (auto i = 0; i < stat_count; ++i)
			{
				D2StatListStrc moo_pStatList{};
				const auto moo_stats = std::make_unique<D2StatStrc[]>(stat_count);
				D2StatListStrc original_pStatList{};
				const auto original_stats = std::make_unique<D2StatStrc[]>(stat_count);
				int nStatIndex = i;

				const auto setup_data = [stat_count, &stats](
					D2StatListStrc& pStatList,
					const std::unique_ptr<D2StatStrc[]>& stat_array
				) {
					std::memcpy(stat_array.get(), stats.get(), sizeof(D2StatStrc) * stat_count);

					pStatList.Stats.nStatCount = stat_count;
					pStatList.Stats.pStat = stat_array.get();
				};

				setup_data(moo_pStatList, moo_stats);
				setup_data(original_pStatList, original_stats);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatList, nStatIndex);
				const auto original_result = original(&original_pStatList, nStatIndex);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB8150 (#10468)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_RemoveAllStats, dll_base + 0x00078150);

		SUBCASE("")
		{
			// Input data
			// NOTE: The stat arrays get reallocated if more than 8 stats are removed, which is not (yet) supported by the tests because they don't use Fog.dll for allocations
			const auto size = 8;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size);

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			sut(&moo_pStatList);
			original(&original_pStatList);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");

			CHECK_EQ(moo_pStatList.Stats.nStatCount, 0);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8190")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_GetStateFromStatListEx_6FDB8190, dll_base + 0x00078190);

		SUBCASE("")
		{
			// Input data
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pLastStatList{};
			D2StatListStrc moo_pFirstStatList{};
			D2StatListStrc moo_pSetStatList{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pLastStatList{};
			D2StatListStrc original_pFirstStatList{};
			D2StatListStrc original_pSetStatList{};

			const auto setup_data = [](
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pLastStatList,
				D2StatListStrc& pFirstStatList,
				D2StatListStrc& pSetStatList
			) {
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pLastStatList;
				pLastStatList.dwStateNo = 1;
				pLastStatList.pPrevLink = &pFirstStatList;
				pFirstStatList.dwStateNo = 2;
				pFirstStatList.pNextLink = &pLastStatList;
				pStatListEx.pMyStats = &pSetStatList;
				pSetStatList.dwFlags = STATLIST_SET;
				pSetStatList.dwStateNo = 3;
			};

			setup_data(moo_pStatListEx, moo_pLastStatList, moo_pFirstStatList, moo_pSetStatList);
			setup_data(original_pStatListEx, original_pLastStatList, original_pFirstStatList, original_pSetStatList);

			const std::pair<int, D2StatListStrc*> expected_results[] = {
				{ 0, nullptr },
				{ 1, &moo_pLastStatList },
				{ 2, &moo_pFirstStatList },
				{ 3, &moo_pSetStatList },
				{ 4, nullptr },
			};

			for (const auto& [nStateId, expected_result] : expected_results)
			{
				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nStateId);
				const auto original_result = original(&original_pStatListEx, nStateId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");

				CHECK_EQ(moo_result, expected_result);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB81E0 (#10480)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromUnitAndState, dll_base + 0x000781E0);

		SUBCASE("pUnit->pStatListEx = nullptr")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nState = 1;

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nState);
			const auto original_result = original(&original_pUnit, nState);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, nullptr);
		}

		SUBCASE("pUnit->pStatListEx is an extended stat list")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pLastStatList{};
			D2StatListStrc moo_pFirstStatList{};
			D2StatListStrc moo_pSetStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pLastStatList{};
			D2StatListStrc original_pFirstStatList{};
			D2StatListStrc original_pSetStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pLastStatList,
				D2StatListStrc& pFirstStatList,
				D2StatListStrc& pSetStatList
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pLastStatList;
				pLastStatList.dwStateNo = 1;
				pLastStatList.pPrevLink = &pFirstStatList;
				pFirstStatList.dwStateNo = 2;
				pFirstStatList.pNextLink = &pLastStatList;
				pStatListEx.pMyStats = &pSetStatList;
				pSetStatList.dwFlags = STATLIST_SET;
				pSetStatList.dwStateNo = 3;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pLastStatList, moo_pFirstStatList, moo_pSetStatList);
			setup_data(original_pUnit, original_pStatListEx, original_pLastStatList, original_pFirstStatList, original_pSetStatList);

			const std::pair<int, D2StatListStrc*> expected_results[] = {
				{ 0, nullptr },
				{ 1, &moo_pLastStatList },
				{ 2, &moo_pFirstStatList },
				{ 3, &moo_pSetStatList },
				{ 4, nullptr },
			};

			for (const auto& [nState, expected_result] : expected_results)
			{
				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nState);
				const auto original_result = original(&original_pUnit, nState);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, expected_result);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8200 (#10482)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromFlag, dll_base + 0x00078200);

		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc moo_pBuffStatList{};
			D2StatListStrc moo_pCurseStatList{};
			D2StatListStrc original_pStatList{};
			D2StatListStrc original_pBuffStatList{};
			D2StatListStrc original_pCurseStatList{};

			const auto setup_data = [](
				D2StatListStrc& pStatList,
				D2StatListStrc& pBuffStatList,
				D2StatListStrc& pCurseStatList
			) {
				pStatList.dwFlags = STATLIST_OVERLAY;
				pStatList.pPrevLink = &pBuffStatList;
				pBuffStatList.dwFlags = STATLIST_BUFF;
				pBuffStatList.pNextLink = &pStatList;
				pBuffStatList.pPrevLink = &pCurseStatList;
				pCurseStatList.dwFlags = STATLIST_CURSE;
				pCurseStatList.pNextLink = &pBuffStatList;
			};

			setup_data(moo_pStatList, moo_pBuffStatList, moo_pCurseStatList);
			setup_data(original_pStatList, original_pBuffStatList, original_pCurseStatList);

			const std::pair<int, D2StatListStrc*> expected_results[] = {
				{ STATLIST_BUFF, &moo_pBuffStatList },
				{ STATLIST_CURSE, &moo_pCurseStatList },
				{ STATLIST_BUFF | STATLIST_CURSE, &moo_pBuffStatList },
				{ STATLIST_OVERLAY, nullptr },
			};

			for (const auto& [nFlag, expected_result] : expected_results)
			{
				// Call both implementations
				const auto moo_result = sut(&moo_pStatList, nFlag);
				const auto original_result = original(&original_pStatList, nFlag);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");

				CHECK_EQ(moo_result, expected_result);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8230 (#10481)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromUnitAndFlag, dll_base + 0x00078230);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pBuffStatList{};
			D2StatListStrc moo_pCurseStatList{};
			D2StatListStrc moo_pSetStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pBuffStatList{};
			D2StatListStrc original_pCurseStatList{};
			D2StatListStrc original_pSetStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pBuffStatList,
				D2StatListStrc& pCurseStatList,
				D2StatListStrc& pSetStatList
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pBuffStatList;
				pBuffStatList.dwFlags = STATLIST_BUFF;
				pBuffStatList.pPrevLink = &pCurseStatList;
				pCurseStatList.dwFlags = STATLIST_CURSE;
				pCurseStatList.pNextLink = &pBuffStatList;
				pStatListEx.pMyStats = &pSetStatList;
				pSetStatList.dwFlags = STATLIST_SET | STATLIST_MAGIC;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pBuffStatList, moo_pCurseStatList, moo_pSetStatList);
			setup_data(original_pUnit, original_pStatListEx, original_pBuffStatList, original_pCurseStatList, original_pSetStatList);

			const std::pair<int, D2StatListStrc*> expected_results[] = {
				{ STATLIST_BUFF, &moo_pBuffStatList },
				{ STATLIST_CURSE, &moo_pCurseStatList },
				{ STATLIST_MAGIC, nullptr },
				{ STATLIST_SET | STATLIST_MAGIC, &moo_pSetStatList },
				{ STATLIST_SET | STATLIST_BUFF, nullptr },
			};

			for (const auto& [nFlag, expected_result] : expected_results)
			{
				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nFlag);
				const auto original_result = original(&original_pUnit, nFlag);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, expected_result);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8270 (#10483)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromUnitStateOrFlag, dll_base + 0x00078270);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pBuffStatList{};
			D2StatListStrc moo_pCurseStatList{};
			D2StatListStrc moo_pSetStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pBuffStatList{};
			D2StatListStrc original_pCurseStatList{};
			D2StatListStrc original_pSetStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pBuffStatList,
				D2StatListStrc& pCurseStatList,
				D2StatListStrc& pSetStatList
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pBuffStatList;
				pBuffStatList.dwFlags = STATLIST_BUFF;
				pBuffStatList.dwStateNo = 1;
				pBuffStatList.pPrevLink = &pCurseStatList;
				pCurseStatList.dwFlags = STATLIST_CURSE;
				pCurseStatList.dwStateNo = 2;
				pCurseStatList.pNextLink = &pBuffStatList;
				pStatListEx.pMyStats = &pSetStatList;
				pSetStatList.dwFlags = STATLIST_SET;
				pSetStatList.dwStateNo = 3;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pBuffStatList, moo_pCurseStatList, moo_pSetStatList);
			setup_data(original_pUnit, original_pStatListEx, original_pBuffStatList, original_pCurseStatList, original_pSetStatList);

			const std::tuple<int, int, D2StatListStrc*> expected_results[] = {
				{ 1, 0, &moo_pBuffStatList },
				{ 2, STATLIST_BUFF, &moo_pCurseStatList },
				{ 3, 0, &moo_pSetStatList },
				{ 4, STATLIST_BUFF, nullptr },
				{ 0, STATLIST_BUFF, &moo_pBuffStatList },
				{ 0, STATLIST_CURSE, &moo_pCurseStatList },
				{ 0, STATLIST_OVERLAY, nullptr },
			};

			for (const auto& [nState, nFlag, expected_result] : expected_results)
			{
				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nState, nFlag);
				const auto original_result = original(&original_pUnit, nState, nFlag);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, expected_result);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB82C0 (#10484)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromUnitStateAndFlag, dll_base + 0x000782C0);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pBuffStatList{};
			D2StatListStrc moo_pCurseStatList{};
			D2StatListStrc moo_pSetStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pBuffStatList{};
			D2StatListStrc original_pCurseStatList{};
			D2StatListStrc original_pSetStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pBuffStatList,
				D2StatListStrc& pCurseStatList,
				D2StatListStrc& pSetStatList
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pBuffStatList;
				pBuffStatList.dwFlags = STATLIST_BUFF;
				pBuffStatList.dwStateNo = 1;
				pBuffStatList.pPrevLink = &pCurseStatList;
				pCurseStatList.dwFlags = STATLIST_CURSE;
				pCurseStatList.dwStateNo = 2;
				pCurseStatList.pNextLink = &pBuffStatList;
				pStatListEx.pMyStats = &pSetStatList;
				pSetStatList.dwFlags = STATLIST_SET | STATLIST_MAGIC;
				pSetStatList.dwStateNo = 3;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pBuffStatList, moo_pCurseStatList, moo_pSetStatList);
			setup_data(original_pUnit, original_pStatListEx, original_pBuffStatList, original_pCurseStatList, original_pSetStatList);

			const std::tuple<int, int, D2StatListStrc*> expected_results[] = {
				{ 1, STATLIST_BUFF, &moo_pBuffStatList },
				{ 1, STATLIST_CURSE, nullptr },
				{ 2, 0, &moo_pCurseStatList },
				{ 2, STATLIST_CURSE, &moo_pCurseStatList },
				{ 3, 0, nullptr },
				{ 3, STATLIST_SET, &moo_pSetStatList },
				{ 3, STATLIST_SET | STATLIST_MAGIC, &moo_pSetStatList },
				{ 3, STATLIST_SET | STATLIST_BUFF, nullptr },
				{ 4, 0, nullptr },
			};

			for (const auto& [nState, nFlag, expected_result] : expected_results)
			{
				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nState, nFlag);
				const auto original_result = original(&original_pUnit, nState, nFlag);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, expected_result);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB8310 (#10523)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_MergeStatLists, dll_base + 0x00078310);

		SUBCASE("Stat list is not merged into target yet")
		{
			// Input data
			const BOOL type = GENERATE(FALSE, TRUE);

			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto unit_stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				unit_stat_array[i].nLayer = 0;
				unit_stat_array[i].nStat = plain_stat_ids[i];
				unit_stat_array[i].nValue = 100 + i;
			}

			const auto target_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				target_stat_array[i].nLayer = 0;
				target_stat_array[i].nStat = static_cast<uint16_t>(i);
				target_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pTarget{};
			D2StatListExStrc moo_pTargetStatListEx{};
			const auto moo_pTargetStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pUnitStatListEx{};
			const auto moo_pUnitStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2UnitStrc original_pTarget{};
			D2StatListExStrc original_pTargetStatListEx{};
			const auto original_pTargetStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pUnitStatListEx{};
			const auto original_pUnitStat = std::make_unique<D2StatStrc[]>(stat_count);
			BOOL bType = type;

			const auto setup_data = [this, stat_count, &unit_stat_array, &target_stat_array](
				D2UnitStrc& pTarget,
				D2StatListExStrc& pTargetStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pTargetStat,
				D2UnitStrc& pUnit,
				D2StatListExStrc& pUnitStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pUnitStat
			) {
				pTarget.pStatListEx = &pTargetStatListEx;
				pTargetStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pTargetStat.get(), target_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pTargetStatListEx.FullStats.pStat = pTargetStat.get();
				pTargetStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pTargetStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pStatListEx = &pUnitStatListEx;
				pUnitStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pUnitStat.get(), unit_stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pUnitStatListEx.FullStats.pStat = pUnitStat.get();
				pUnitStatListEx.FullStats.nStatCount = stat_count;
				pUnitStatListEx.FullStats.nCapacity = stat_count;
			};

			setup_data(moo_pTarget, moo_pTargetStatListEx, moo_pTargetStat, moo_pUnit, moo_pUnitStatListEx, moo_pUnitStat);
			setup_data(original_pTarget, original_pTargetStatListEx, original_pTargetStat, original_pUnit, original_pUnitStatListEx, original_pUnitStat);

			// Call both implementations
			sut(&moo_pTarget, &moo_pUnit, bType);
			original(&original_pTarget, &original_pUnit, bType);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pTargetStatListEx.FullStats.pStat, moo_pTargetStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pTargetStatListEx.FullStats.pStat, original_pTargetStatListEx.FullStats.nStatCount }), "Comparing pTargetStatListEx->FullStats");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_pUnitStatListEx.pUnit, &moo_pTarget);
			CHECK_EQ(moo_pUnitStatListEx.pParent, &moo_pTargetStatListEx);
			CHECK_EQ(moo_pTargetStatListEx.pMyLastList, &moo_pUnitStatListEx);
		}

		SUBCASE("Stat list is already merged into target")
		{
			// Input data
			const BOOL type = GENERATE(FALSE, TRUE);

			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto unit_stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				unit_stat_array[i].nLayer = 0;
				unit_stat_array[i].nStat = plain_stat_ids[i];
				unit_stat_array[i].nValue = 100 + i;
			}

			const auto target_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				target_stat_array[i].nLayer = 0;
				target_stat_array[i].nStat = static_cast<uint16_t>(i);
				target_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pTarget{};
			D2StatListExStrc moo_pTargetStatListEx{};
			const auto moo_pTargetStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pUnitStatListEx{};
			const auto moo_pUnitStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2UnitStrc original_pTarget{};
			D2StatListExStrc original_pTargetStatListEx{};
			const auto original_pTargetStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pUnitStatListEx{};
			const auto original_pUnitStat = std::make_unique<D2StatStrc[]>(stat_count);
			BOOL bType = type;

			const auto setup_data = [this, stat_count, bType, &unit_stat_array, &target_stat_array](
				D2UnitStrc& pTarget,
				D2StatListExStrc& pTargetStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pTargetStat,
				D2UnitStrc& pUnit,
				D2StatListExStrc& pUnitStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pUnitStat
			) {
				pTarget.pStatListEx = &pTargetStatListEx;
				pTargetStatListEx.dwFlags |= STATLIST_EXTENDED;
				pTargetStatListEx.pMyLastList = &pUnitStatListEx;
				std::memcpy(pTargetStat.get(), target_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pTargetStatListEx.FullStats.pStat = pTargetStat.get();
				pTargetStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pTargetStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pStatListEx = &pUnitStatListEx;
				pUnitStatListEx.dwFlags |= STATLIST_EXTENDED;

				// Only stat lists with matching dynamic flags get updated
				if (bType)
				{
					pUnitStatListEx.dwFlags |= STATLIST_DYNAMIC;
				}

				pUnitStatListEx.pUnit = &pTarget;
				pUnitStatListEx.pParent = &pTargetStatListEx;
				std::memcpy(pUnitStat.get(), unit_stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pUnitStatListEx.FullStats.pStat = pUnitStat.get();
				pUnitStatListEx.FullStats.nStatCount = stat_count;
				pUnitStatListEx.FullStats.nCapacity = stat_count;
			};

			setup_data(moo_pTarget, moo_pTargetStatListEx, moo_pTargetStat, moo_pUnit, moo_pUnitStatListEx, moo_pUnitStat);
			setup_data(original_pTarget, original_pTargetStatListEx, original_pTargetStat, original_pUnit, original_pUnitStatListEx, original_pUnitStat);

			// Call both implementations
			sut(&moo_pTarget, &moo_pUnit, bType);
			original(&original_pTarget, &original_pUnit, bType);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pTargetStatListEx.FullStats.pStat, moo_pTargetStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pTargetStatListEx.FullStats.pStat, original_pTargetStatListEx.FullStats.nStatCount }), "Comparing pTargetStatListEx->FullStats");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ((moo_pUnitStatListEx.dwFlags & STATLIST_DYNAMIC) != 0, !bType);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB83A0 (#10535)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetOwner, dll_base + 0x000783A0);
		
		SUBCASE("pUnit = nullptr")
		{
			// Input data
			BOOL moo_pStatNotDynamic{};
			BOOL original_pStatNotDynamic{};

			// Call both implementations
			const auto moo_result = sut(nullptr, &moo_pStatNotDynamic);
			const auto original_result = original(nullptr, &original_pStatNotDynamic);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatNotDynamic, original_pStatNotDynamic, "Comparing pStatNotDynamic");
		}

		SUBCASE("pUnit->pStatListEx = nullptr")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			BOOL moo_pStatNotDynamic{};
			D2UnitStrc original_pUnit{};
			BOOL original_pStatNotDynamic{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				BOOL& pStatNotDynamic
			) {
				pUnit.pStatListEx = nullptr;
			};

			setup_data(moo_pUnit, moo_pStatNotDynamic);
			setup_data(original_pUnit, original_pStatNotDynamic);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pStatNotDynamic);
			const auto original_result = original(&original_pUnit, &original_pStatNotDynamic);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pStatNotDynamic, original_pStatNotDynamic, "Comparing pStatNotDynamic");
		}

		SUBCASE("pUnit->pStatListEx->pParent = nullptr")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			BOOL moo_pStatNotDynamic{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			BOOL original_pStatNotDynamic{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				BOOL& pStatNotDynamic
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.pParent = nullptr;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStatNotDynamic);
			setup_data(original_pUnit, original_pStatListEx, original_pStatNotDynamic);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pStatNotDynamic);
			const auto original_result = original(&original_pUnit, &original_pStatNotDynamic);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pStatNotDynamic, original_pStatNotDynamic, "Comparing pStatNotDynamic");
		}

		SUBCASE("pUnit->pStatListEx->pParent is a regular stat list")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pParentStatList{};
			BOOL moo_pStatNotDynamic{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pParentStatList{};
			BOOL original_pStatNotDynamic{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pParentStatList,
				BOOL& pStatNotDynamic
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.pParent = &pParentStatList;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pParentStatList, moo_pStatNotDynamic);
			setup_data(original_pUnit, original_pStatListEx, original_pParentStatList, original_pStatNotDynamic);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pStatNotDynamic);
			const auto original_result = original(&original_pUnit, &original_pStatNotDynamic);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pStatNotDynamic, original_pStatNotDynamic, "Comparing pStatNotDynamic");
		}

		SUBCASE("pUnit->pStatListEx->pParent is an extended stat list")
		{
			// Input data
			const auto is_dynamic = GENERATE(0, 1);
			const auto flags = random_unsigned_integer();
			const auto unit_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListExStrc moo_pParentStatListEx{};
			BOOL moo_pStatNotDynamic{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListExStrc original_pParentStatListEx{};
			BOOL original_pStatNotDynamic{};

			const auto setup_data = [is_dynamic, flags, unit_id](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListExStrc& pParentStatListEx,
				BOOL& pStatNotDynamic
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.pParent = &pParentStatListEx;
				pParentStatListEx.dwFlags |= STATLIST_EXTENDED;
				pUnit.dwUnitId = unit_id;

				if (is_dynamic)
				{
					pStatListEx.dwFlags = flags | STATLIST_DYNAMIC;
				}
				else
				{
					pStatListEx.dwFlags = flags & ~STATLIST_DYNAMIC;
				}

				pParentStatListEx.pOwner = &pUnit;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pParentStatListEx, moo_pStatNotDynamic);
			setup_data(original_pUnit, original_pStatListEx, original_pParentStatListEx, original_pStatNotDynamic);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pStatNotDynamic);
			const auto original_result = original(&original_pUnit, &original_pStatNotDynamic);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pStatNotDynamic, original_pStatNotDynamic, "Comparing pStatNotDynamic");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8420 (#10512)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10512, dll_base + 0x00078420);

		SUBCASE("")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			// Stat 25 is a mod stat without base stat
			const uint16_t mod_stat_ids[] = { 3, 7, 9, 25 };
			const auto mod_stat_count = static_cast<int>(std::size(mod_stat_ids));

			D2UnitStrc moo_pUnit1{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size);
			const auto moo_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(mod_stat_count);
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size);
			const auto original_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(mod_stat_count);
			D2UnitStrc original_pUnit2{};

			const auto setup_data = [&stat_array, size, &mod_stat_ids, mod_stat_count](
				D2UnitStrc& pUnit1,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				const std::unique_ptr<D2SLayerStatIdStrc[]>& pModStat,
				D2UnitStrc& pUnit2
			) {
				pUnit1.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatListEx.Stats.pStat = pStat.get();
				pStatListEx.Stats.nStatCount = size;
				pStatListEx.Stats.nCapacity = size;

				for (auto i = 0; i < mod_stat_count; ++i)
				{
					pModStat[i] = D2SLayerStatIdStrc::MakeFromStatId(mod_stat_ids[i]);
				}

				pStatListEx.ModStats.pStat = pModStat.get();
				pStatListEx.ModStats.nStatCount = mod_stat_count;
				pStatListEx.ModStats.nCapacity = mod_stat_count;
			};

			setup_data(moo_pUnit1, moo_pStatListEx, moo_pStat, moo_pModStat, moo_pUnit2);
			setup_data(original_pUnit1, original_pStatListEx, original_pStat, original_pModStat, original_pUnit2);

			for (auto nStatId = 0; nStatId < 30; ++nStatId)
			{
				// Call both implementations
				stat_callback_calls.clear();
				sut(&moo_pUnit1, &moo_pUnit2, nStatId, record_stat_callback);
				const auto moo_calls = std::move(stat_callback_calls);

				stat_callback_calls.clear();
				original(&original_pUnit1, &original_pUnit2, nStatId, record_stat_callback);
				const auto original_calls = std::move(stat_callback_calls);

				// Compare callback calls
				check_stat_callback_calls_eq(moo_calls, &moo_pUnit1, &moo_pUnit2, original_calls, &original_pUnit1, &original_pUnit2);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
				MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");

				const auto is_mod_stat_with_base_stat = nStatId == 3 || nStatId == 7 || nStatId == 9;
				CHECK_EQ(moo_calls.size(), is_mod_stat_with_base_stat ? 1u : 0u);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB84E0 (#10513)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10513, dll_base + 0x000784E0);

		SUBCASE("")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			// Stat 25 is a mod stat without base stat
			const uint16_t mod_stat_ids[] = { 3, 7, 9, 25 };
			const auto mod_stat_count = static_cast<int>(std::size(mod_stat_ids));

			D2UnitStrc moo_pUnit1{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size);
			const auto moo_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(mod_stat_count);
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size);
			const auto original_pModStat = std::make_unique<D2SLayerStatIdStrc[]>(mod_stat_count);
			D2UnitStrc original_pUnit2{};

			const auto setup_data = [&stat_array, size, &mod_stat_ids, mod_stat_count](
				D2UnitStrc& pUnit1,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				const std::unique_ptr<D2SLayerStatIdStrc[]>& pModStat,
				D2UnitStrc& pUnit2
			) {
				pUnit1.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatListEx.Stats.pStat = pStat.get();
				pStatListEx.Stats.nStatCount = size;
				pStatListEx.Stats.nCapacity = size;

				for (auto i = 0; i < mod_stat_count; ++i)
				{
					pModStat[i] = D2SLayerStatIdStrc::MakeFromStatId(mod_stat_ids[i]);
				}

				pStatListEx.ModStats.pStat = pModStat.get();
				pStatListEx.ModStats.nStatCount = mod_stat_count;
				pStatListEx.ModStats.nCapacity = mod_stat_count;
			};

			setup_data(moo_pUnit1, moo_pStatListEx, moo_pStat, moo_pModStat, moo_pUnit2);
			setup_data(original_pUnit1, original_pStatListEx, original_pStat, original_pModStat, original_pUnit2);

			// Call both implementations
			stat_callback_calls.clear();
			sut(&moo_pUnit1, &moo_pUnit2, record_stat_callback);
			const auto moo_calls = std::move(stat_callback_calls);

			stat_callback_calls.clear();
			original(&original_pUnit1, &original_pUnit2, record_stat_callback);
			const auto original_calls = std::move(stat_callback_calls);

			// Compare callback calls
			check_stat_callback_calls_eq(moo_calls, &moo_pUnit1, &moo_pUnit2, original_calls, &original_pUnit1, &original_pUnit2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");

			REQUIRE_EQ(moo_calls.size(), static_cast<size_t>(mod_stat_count));

			for (auto i = 0; i < mod_stat_count; ++i)
			{
				CHECK_EQ(moo_calls[i].nStatId, mod_stat_ids[i]);
				CHECK_EQ(moo_calls[i].nValue, mod_stat_ids[i] < size ? stat_array[mod_stat_ids[i]].nValue : 0);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB85D0 (#10511)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_FreeModStats, dll_base + 0x000785D0);

		// NOTE: Freeing allocated mod stats is not (yet) tested because the tests don't use Fog.dll for allocations

		SUBCASE("Extended stat list")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.ModStats.pStat = nullptr;
				pStatListEx.ModStats.nStatCount = 0;
				pStatListEx.ModStats.nCapacity = D2ModStatsArrayStrc::nGrowthAmount;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_pStatListEx.ModStats.nCapacity, 0);
		}

		SUBCASE("Regular stat list")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.ModStats.pStat = nullptr;
				pStatListEx.ModStats.nStatCount = 0;
				pStatListEx.ModStats.nCapacity = D2ModStatsArrayStrc::nGrowthAmount;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_pStatListEx.ModStats.nCapacity, D2ModStatsArrayStrc::nGrowthAmount);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB8620 (#10562)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetUnitAlignment, dll_base + 0x00078620);

		SUBCASE("pUnit->pStatListEx = nullptr")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, UNIT_ALIGNMENT_EVIL);
		}

		SUBCASE("pUnit is neither a player nor a monster")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pUnit.dwUnitType = UNIT_OBJECT;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, UNIT_ALIGNMENT_GOOD);
		}

		SUBCASE("pUnit without alignment state")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, UNIT_ALIGNMENT_EVIL);
		}

		SUBCASE("pUnit with alignment state")
		{
			// Input data
			const int alignment = GENERATE(UNIT_ALIGNMENT_EVIL, UNIT_ALIGNMENT_NEUTRAL, UNIT_ALIGNMENT_GOOD);

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pAlignmentStatList{};
			D2StatStrc moo_pAlignmentStat{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pAlignmentStatList{};
			D2StatStrc original_pAlignmentStat{};

			const auto setup_data = [alignment](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pAlignmentStatList,
				D2StatStrc& pAlignmentStat
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pAlignmentStatList;
				pAlignmentStatList.dwStateNo = STATE_ALIGNMENT;
				pAlignmentStat.nLayer = 0;
				pAlignmentStat.nStat = STAT_ALIGNMENT;
				pAlignmentStat.nValue = alignment;
				pAlignmentStatList.Stats.pStat = &pAlignmentStat;
				pAlignmentStatList.Stats.nStatCount = 1;
				pAlignmentStatList.Stats.nCapacity = 1;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pAlignmentStatList, moo_pAlignmentStat);
			setup_data(original_pUnit, original_pStatListEx, original_pAlignmentStatList, original_pAlignmentStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, alignment);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8750 (#10534)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10534, dll_base + 0x00078750);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8770 (#10530)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10530_D2CheckStatlistFlagDMGRed, dll_base + 0x00078770);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB87A0 (#10532)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetTotalStatValue_Layer0, dll_base + 0x000787A0);

		SUBCASE("D2StatListStrc")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &stat_array](
				D2StatListStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.Stats.pStat = pStat.get();
				pStatListEx.Stats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pStatListEx, moo_pStat);
			setup_data(original_pStatListEx, original_pStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				int nStatId = i;

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nStatId);
				const auto original_result = original(&original_pStatListEx, nStatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}

		SUBCASE("D2StatListExStrc")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				const auto setup_data = [this, i, &stat_array](
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pStat,
					D2ItemStatCostTxt& pItemStatCostTxtRecord
				) {
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.FullStats.pStat = pStat.get();
					pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				int nStatId = i;

				setup_data(moo_pStatListEx, moo_pStat, moo_pItemStatCostTxtRecord);
				setup_data(original_pStatListEx, original_pStat, original_pItemStatCostTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pStatListEx, nStatId);
				const auto original_result = original(&original_pStatListEx, nStatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB8890 (#10533)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_RemoveAllStatsFromOverlay, dll_base + 0x00078890);

		SUBCASE("Without overlay stat list")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pBuffStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pBuffStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pBuffStatList
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED | STATLIST_UNK_0x100;
				pStatListEx.pMyLastList = &pBuffStatList;
				pBuffStatList.dwFlags = STATLIST_BUFF;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pBuffStatList);
			setup_data(original_pUnit, original_pStatListEx, original_pBuffStatList);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_pStatListEx.dwFlags & STATLIST_UNK_0x100, 0u);
		}

		SUBCASE("With overlay stat list")
		{
			// Input data
			// NOTE: The stat arrays get reallocated if more than 8 stats are removed, which is not (yet) supported by the tests because they don't use Fog.dll for allocations
			const auto size = 8;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pBuffStatList{};
			const auto moo_pBuffStat = std::make_unique<D2StatStrc[]>(size);
			D2StatListStrc moo_pOverlayStatList{};
			const auto moo_pOverlayStat = std::make_unique<D2StatStrc[]>(size);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pBuffStatList{};
			const auto original_pBuffStat = std::make_unique<D2StatStrc[]>(size);
			D2StatListStrc original_pOverlayStatList{};
			const auto original_pOverlayStat = std::make_unique<D2StatStrc[]>(size);

			const auto setup_data = [&stat_array, size](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pBuffStatList,
				const std::unique_ptr<D2StatStrc[]>& pBuffStat,
				D2StatListStrc& pOverlayStatList,
				const std::unique_ptr<D2StatStrc[]>& pOverlayStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED | STATLIST_UNK_0x100;
				pStatListEx.pMyLastList = &pBuffStatList;
				pBuffStatList.dwFlags = STATLIST_BUFF;
				std::memcpy(pBuffStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pBuffStatList.Stats.pStat = pBuffStat.get();
				pBuffStatList.Stats.nStatCount = size;
				pBuffStatList.Stats.nCapacity = size;
				pBuffStatList.pPrevLink = &pOverlayStatList;
				pOverlayStatList.dwFlags = STATLIST_OVERLAY;
				std::memcpy(pOverlayStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pOverlayStatList.Stats.pStat = pOverlayStat.get();
				pOverlayStatList.Stats.nStatCount = size;
				pOverlayStatList.Stats.nCapacity = size;
				pOverlayStatList.pNextLink = &pBuffStatList;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pBuffStatList, moo_pBuffStat, moo_pOverlayStatList, moo_pOverlayStat);
			setup_data(original_pUnit, original_pStatListEx, original_pBuffStatList, original_pBuffStat, original_pOverlayStatList, original_pOverlayStat);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pOverlayStatList, original_pOverlayStatList, "Comparing pOverlayStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pBuffStatList.Stats.pStat, moo_pBuffStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pBuffStatList.Stats.pStat, original_pBuffStatList.Stats.nStatCount }), "Comparing pBuffStatList->Stats");

			CHECK_EQ(moo_pStatListEx.dwFlags & STATLIST_UNK_0x100, 0u);
			CHECK_EQ(moo_pBuffStatList.Stats.nStatCount, size);
			CHECK_EQ(moo_pOverlayStatList.Stats.nStatCount, 0);
		}
	}
	
	TEST_CASE_FIXTURE(StatesTxtFixture<NoopFixture>, "D2Common.0x6FDB8900")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_STATES_ToggleState_6FDB8900, dll_base + 0x00078900);
		
		SUBCASE("")
		{
			const auto set = GENERATE(0, 1);

			const auto size = 2 * (sgptDataTables->nStatesTxtRecordCount + 31) / 32;

			const auto stat_flags = std::make_unique<uint32_t[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_flags[i] = random_unsigned_integer();
			}

			const auto unit_flags = random_unsigned_integer();

			for (auto i = 0; i < states_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				const auto moo_StatFlags = std::make_unique<uint32_t[]>(size);
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				const auto original_StatFlags = std::make_unique<uint32_t[]>(size);
				int nState = i;
				BOOL bSet = set;

				const auto setup_data = [size, unit_flags, &stat_flags](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<uint32_t[]>& StatFlags
				) {
					pUnit.dwFlagEx = unit_flags;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.StatFlags = StatFlags.get();
					std::memcpy(StatFlags.get(), stat_flags.get(), sizeof(uint32_t) * size);
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags);
				setup_data(original_pUnit, original_pStatListEx, original_StatFlags);

				// Call both implementations
				sut(&moo_pUnit, nState, bSet);
				original(&original_pUnit, nState, bSet);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(StatesTxtFixture<NoopFixture>, "D2Common.0x6FDB8A90")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_STATES_GetStatFlags_6FDB8A90, dll_base + 0x00078A90);
		
		SUBCASE("")
		{
			// Input data
			const auto size = 2 * (sgptDataTables->nStatesTxtRecordCount + 31) / 32;

			const auto stat_flags = std::make_unique<uint32_t[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_flags[i] = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_StatFlags = std::make_unique<uint32_t[]>(size);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_StatFlags = std::make_unique<uint32_t[]>(size);

			const auto setup_data = [size, &stat_flags](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<uint32_t[]>& StatFlags
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.StatFlags = StatFlags.get();
				std::memcpy(StatFlags.get(), stat_flags.get(), sizeof(uint32_t) * size);
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags);
			setup_data(original_pUnit, original_pStatListEx, original_StatFlags);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ((DynamicArray<uint32_t> { moo_result, size }), (DynamicArray<uint32_t> { original_result, size }), "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(StatesTxtFixture<NoopFixture>, "D2Common.0x6FDB8AC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_STATES_GetListGfxFlags_6FDB8AC0, dll_base + 0x00078AC0);
		
		SUBCASE("")
		{
			// Input data
			const auto size = 2 * (sgptDataTables->nStatesTxtRecordCount + 31) / 32;

			const auto stat_flags = std::make_unique<uint32_t[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_flags[i] = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_StatFlags = std::make_unique<uint32_t[]>(size);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_StatFlags = std::make_unique<uint32_t[]>(size);

			const auto setup_data = [size, &stat_flags](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<uint32_t[]>& StatFlags
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.StatFlags = StatFlags.get();
				std::memcpy(StatFlags.get(), stat_flags.get(), sizeof(uint32_t) * size);
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags);
			setup_data(original_pUnit, original_pStatListEx, original_StatFlags);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ((DynamicArray<uint32_t> { moo_result, size / 2 }), (DynamicArray<uint32_t> { original_result, size / 2 }), "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8BA0 (#11268)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetFullStatsDataFromUnit, dll_base + 0x00078BA0);

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(20);

			for (auto i = 0; i < 20; ++i)
			{
				stat_array[i].nLayer = random_unsigned_integer(0, 255);
				stat_array[i].nStat = random_unsigned_integer(0, 255);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pOutStatBuffer[10]{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(20);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pOutStatBuffer[10]{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(20);
			int nBufferSize = 10;

			const auto setup_data = [&stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2StatStrc(&pOutStatBuffer)[10]
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * 20);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = 20;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pOutStatBuffer);
			setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pOutStatBuffer);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, moo_pOutStatBuffer, nBufferSize);
			const auto original_result = original(&original_pUnit, original_pOutStatBuffer, nBufferSize);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pOutStatBuffer, 10 }), (DynamicArray<D2StatStrc> { original_pOutStatBuffer, 10 }), "Comparing pOutStatBuffer");

			CHECK_EQ(moo_result, 10);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8C00 (#11243)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetBaseStatsData, dll_base + 0x00078C00);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(20);

			for (auto i = 0; i < 20; ++i)
			{
				stat_array[i].nLayer = random_unsigned_integer(0, 255);
				stat_array[i].nStat = random_unsigned_integer(0, 255);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2StatListStrc moo_pStatList{};
			D2StatStrc moo_pOutStatBuffer[30]{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(20);
			D2StatListStrc original_pStatList{};
			D2StatStrc original_pOutStatBuffer[30]{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(20);
			int nBufferSize = 30;

			const auto setup_data = [&stat_array](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2StatStrc(&pOutStatBuffer)[30]
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * 20);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = 20;
			};

			setup_data(moo_pStatList, moo_pStat, moo_pOutStatBuffer);
			setup_data(original_pStatList, original_pStat, original_pOutStatBuffer);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, moo_pOutStatBuffer, nBufferSize);
			const auto original_result = original(&original_pStatList, original_pOutStatBuffer, nBufferSize);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pOutStatBuffer, 20 }), (DynamicArray<D2StatStrc> { original_pOutStatBuffer, 20 }), "Comparing pOutStatBuffer");

			CHECK_EQ(moo_result, 20);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB8C50 (#10573)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_MergeBaseStats, dll_base + 0x00078C50);

		SUBCASE("")
		{
			// Input data
			// The source stats 10 to 19 are added to existing target stats, the source stats 20 to 29 are inserted
			const auto target_size = 20;
			const auto source_size = 20;
			const auto source_first_stat_id = 10;
			const auto merged_size = source_first_stat_id + source_size;

			const auto target_stat_array = std::make_unique<D2StatStrc[]>(target_size);

			for (auto i = 0; i < target_size; ++i)
			{
				target_stat_array[i].nLayer = 0;
				target_stat_array[i].nStat = static_cast<uint16_t>(i);
				target_stat_array[i].nValue = 10000 + i;
			}

			const auto source_stat_array = std::make_unique<D2StatStrc[]>(source_size);

			for (auto i = 0; i < source_size; ++i)
			{
				source_stat_array[i].nLayer = 0;
				source_stat_array[i].nStat = static_cast<uint16_t>(source_first_stat_id + i);
				source_stat_array[i].nValue = 100 + i;
			}

			D2StatListStrc moo_pTargetStatList{};
			const auto moo_pTargetStat = std::make_unique<D2StatStrc[]>(merged_size);
			D2StatListStrc moo_pSourceStatlist{};
			const auto moo_pSourceStat = std::make_unique<D2StatStrc[]>(source_size);
			D2StatListStrc original_pTargetStatList{};
			const auto original_pTargetStat = std::make_unique<D2StatStrc[]>(merged_size);
			D2StatListStrc original_pSourceStatlist{};
			const auto original_pSourceStat = std::make_unique<D2StatStrc[]>(source_size);

			const auto setup_data = [&target_stat_array, &source_stat_array, target_size, source_size, merged_size](
				D2StatListStrc& pTargetStatList,
				const std::unique_ptr<D2StatStrc[]>& pTargetStat,
				D2StatListStrc& pSourceStatlist,
				const std::unique_ptr<D2StatStrc[]>& pSourceStat
			) {
				std::memcpy(pTargetStat.get(), target_stat_array.get(), sizeof(D2StatStrc) * target_size);
				pTargetStatList.Stats.pStat = pTargetStat.get();
				pTargetStatList.Stats.nStatCount = target_size;
				pTargetStatList.Stats.nCapacity = merged_size;
				std::memcpy(pSourceStat.get(), source_stat_array.get(), sizeof(D2StatStrc) * source_size);
				pSourceStatlist.Stats.pStat = pSourceStat.get();
				pSourceStatlist.Stats.nStatCount = source_size;
				pSourceStatlist.Stats.nCapacity = source_size;
			};

			setup_data(moo_pTargetStatList, moo_pTargetStat, moo_pSourceStatlist, moo_pSourceStat);
			setup_data(original_pTargetStatList, original_pTargetStat, original_pSourceStatlist, original_pSourceStat);

			// Call both implementations
			sut(&moo_pTargetStatList, &moo_pSourceStatlist);
			original(&original_pTargetStatList, &original_pSourceStatlist);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTargetStatList, original_pTargetStatList, "Comparing pTargetStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pTargetStatList.Stats.pStat, moo_pTargetStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pTargetStatList.Stats.pStat, original_pTargetStatList.Stats.nStatCount }), "Comparing pTargetStatList->Stats");
			MOO_CHECK_EQ(moo_pSourceStatlist, original_pSourceStatlist, "Comparing pSourceStatlist");

			REQUIRE_EQ(moo_pTargetStatList.Stats.nStatCount, merged_size);

			for (auto i = 0; i < merged_size; ++i)
			{
				const auto target_value = i < target_size ? target_stat_array[i].nValue : 0;
				const auto source_value = i >= source_first_stat_id ? source_stat_array[i - source_first_stat_id].nValue : 0;

				CHECK_EQ(moo_pTargetStat[i].nStat, i);
				CHECK_EQ(moo_pTargetStat[i].nValue, target_value + source_value);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8CA0 (#10477)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetStatRemoveCallback, dll_base + 0x00078CA0);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			StatListRemoveCallback pfStatRemove = (StatListRemoveCallback)random_unsigned_integer();

			// Call both implementations
			sut(&moo_pStatList, pfStatRemove);
			original(&original_pStatList, pfStatRemove);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(StatesTxtFixture<NoopFixture>, "D2Common.0x6FDB8CC0 (#10469)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10469, dll_base + 0x00078CC0);
		const auto [moo_alloc, original_alloc] = make_function_pair(STATLIST_AllocStatList, dll_base + 0x00077140);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc* moo_pRemovableStatList = moo_alloc(nullptr, 0, 0, UNIT_MONSTER, 0);
			D2StatListStrc moo_pBasicStatList{};
			D2StatListStrc moo_pItemStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc* original_pRemovableStatList = original_alloc(nullptr, 0, 0, UNIT_MONSTER, 0);
			D2StatListStrc original_pBasicStatList{};
			D2StatListStrc original_pItemStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pRemovableStatList,
				D2StatListStrc& pBasicStatList,
				D2StatListStrc& pItemStatList
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.pMyLastList = &pRemovableStatList;
				pRemovableStatList.dwStateNo = STATE_NONE;
				pRemovableStatList.pParent = &pStatListEx;
				pRemovableStatList.pPrevLink = &pBasicStatList;
				pBasicStatList.dwFlags = STATLIST_BASIC;
				pBasicStatList.pParent = &pStatListEx;
				pBasicStatList.pNextLink = &pRemovableStatList;
				pBasicStatList.pPrevLink = &pItemStatList;
				pItemStatList.dwOwnerType = UNIT_ITEM;
				pItemStatList.pParent = &pStatListEx;
				pItemStatList.pNextLink = &pBasicStatList;
			};

			setup_data(moo_pUnit, moo_pStatListEx, *moo_pRemovableStatList, moo_pBasicStatList, moo_pItemStatList);
			setup_data(original_pUnit, original_pStatListEx, *original_pRemovableStatList, original_pBasicStatList, original_pItemStatList);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			// pRemovableStatList can not be compared since it was freed
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pBasicStatList, original_pBasicStatList, "Comparing pBasicStatList");
			MOO_CHECK_EQ(moo_pItemStatList, original_pItemStatList, "Comparing pItemStatList");

			CHECK_EQ(moo_pStatListEx.pMyLastList, &moo_pBasicStatList);
			CHECK_EQ(moo_pBasicStatList.pNextLink, nullptr);
			CHECK_EQ(moo_pBasicStatList.pPrevLink, &moo_pItemStatList);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB8D30 (#10514)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_ClampStaminaManaHP, dll_base + 0x00078D30);

		SUBCASE("")
		{
			// Input data
			// Hitpoints and stamina are above their maximum and get clamped, mana is below its maximum and stays unchanged
			const std::pair<int, int> base_stats[] = {
				{ STAT_HITPOINTS, 2000 },
				{ STAT_MANA, 500 },
				{ STAT_STAMINA, 300 },
			};

			const std::pair<int, int> full_stats[] = {
				{ STAT_HITPOINTS, 2000 },
				{ STAT_MAXHP, 1000 },
				{ STAT_MANA, 500 },
				{ STAT_MAXMANA, 800 },
				{ STAT_STAMINA, 300 },
				{ STAT_MAXSTAMINA, 100 },
			};

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pBaseStat[3]{};
			D2StatStrc moo_pFullStat[6]{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pBaseStat[3]{};
			D2StatStrc original_pFullStat[6]{};

			const auto setup_data = [&base_stats, &full_stats](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatStrc(&pBaseStat)[3],
				D2StatStrc(&pFullStat)[6]
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;

				for (auto i = 0; i < 3; ++i)
				{
					pBaseStat[i].nLayer = 0;
					pBaseStat[i].nStat = static_cast<uint16_t>(base_stats[i].first);
					pBaseStat[i].nValue = base_stats[i].second;
				}

				pStatListEx.Stats.pStat = pBaseStat;
				pStatListEx.Stats.nStatCount = 3;
				pStatListEx.Stats.nCapacity = 3;

				for (auto i = 0; i < 6; ++i)
				{
					pFullStat[i].nLayer = 0;
					pFullStat[i].nStat = static_cast<uint16_t>(full_stats[i].first);
					pFullStat[i].nValue = full_stats[i].second;
				}

				pStatListEx.FullStats.pStat = pFullStat;
				pStatListEx.FullStats.nStatCount = 6;
				pStatListEx.FullStats.nCapacity = 6;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pBaseStat, moo_pFullStat);
			setup_data(original_pUnit, original_pStatListEx, original_pBaseStat, original_pFullStat);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pBaseStat, 3 }), (DynamicArray<D2StatStrc> { original_pBaseStat, 3 }), "Comparing pBaseStat");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pFullStat, 6 }), (DynamicArray<D2StatStrc> { original_pFullStat, 6 }), "Comparing pFullStat");

			CHECK_EQ(moo_pBaseStat[0].nValue, 1000);
			CHECK_EQ(moo_pBaseStat[1].nValue, 500);
			CHECK_EQ(moo_pBaseStat[2].nValue, 100);
			CHECK_EQ(moo_pFullStat[0].nValue, 1000);
			CHECK_EQ(moo_pFullStat[2].nValue, 500);
			CHECK_EQ(moo_pFullStat[4].nValue, 100);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB8EB0 (#10574)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10574, dll_base + 0x00078EB0);

		SUBCASE("No stat list with state")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			int nStateId = 42;
			BOOL bSet = TRUE;

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
			};

			setup_data(moo_pUnit, moo_pStatListEx);
			setup_data(original_pUnit, original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nStateId, bSet);
			const auto original_result = original(&original_pUnit, nStateId, bSet);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, FALSE);
		}

		SUBCASE("Sets STATLIST_SET")
		{
			// Input data
			const auto state_id = 42;

			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count, 5);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = plain_stat_ids[i];
				stat_array[i].nValue = 100 + i;
			}

			const auto unit_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				unit_stat_array[i].nLayer = 0;
				unit_stat_array[i].nStat = static_cast<uint16_t>(i);
				unit_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pUnitStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pUnitStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			int nStateId = state_id;
			BOOL bSet = TRUE;

			const auto setup_data = [this, state_id, stat_count, &stat_array, &unit_stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pUnitStat,
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pUnitStat.get(), unit_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pUnitStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				pStatListEx.pMyLastList = &pStatList;
				pStatList.dwStateNo = state_id;
				pStatList.pParent = &pStatListEx;
				pStatList.pUnit = &pUnit;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = stat_count;
				pStatList.Stats.nCapacity = stat_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pUnitStat, moo_pStatList, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pUnitStat, original_pStatList, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nStateId, bSet);
			const auto original_result = original(&original_pUnit, nStateId, bSet);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.FullStats.pStat, moo_pStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.FullStats.pStat, original_pStatListEx.FullStats.nStatCount }), "Comparing pStatListEx->FullStats");
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");

			CHECK_EQ(moo_result, TRUE);
			CHECK_NE(moo_pStatList.dwFlags & STATLIST_SET, 0u);
			CHECK_EQ(moo_pStatListEx.pMyLastList, nullptr);
			CHECK_EQ(moo_pStatListEx.pMyStats, &moo_pStatList);

			for (auto i = 0; i < stat_count; ++i)
			{
				CHECK_EQ(moo_pUnitStat[plain_stat_ids[i]].nValue, unit_stat_array[plain_stat_ids[i]].nValue - stat_array[i].nValue);
			}
		}

		SUBCASE("Clears STATLIST_SET")
		{
			// Input data
			const auto state_id = 42;

			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count, 5);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = plain_stat_ids[i];
				stat_array[i].nValue = 100 + i;
			}

			const auto unit_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				unit_stat_array[i].nLayer = 0;
				unit_stat_array[i].nStat = static_cast<uint16_t>(i);
				unit_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pUnitStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pUnitStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			int nStateId = state_id;
			BOOL bSet = FALSE;

			const auto setup_data = [this, state_id, stat_count, &stat_array, &unit_stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pUnitStat,
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pUnitStat.get(), unit_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pUnitStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				pStatListEx.pMyStats = &pStatList;
				pStatList.dwFlags = STATLIST_SET;
				pStatList.dwStateNo = state_id;
				pStatList.pParent = &pStatListEx;
				pStatList.pUnit = &pUnit;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = stat_count;
				pStatList.Stats.nCapacity = stat_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pUnitStat, moo_pStatList, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pUnitStat, original_pStatList, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nStateId, bSet);
			const auto original_result = original(&original_pUnit, nStateId, bSet);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx.FullStats.pStat, moo_pStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx.FullStats.pStat, original_pStatListEx.FullStats.nStatCount }), "Comparing pStatListEx->FullStats");
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");

			CHECK_EQ(moo_result, TRUE);
			CHECK_EQ(moo_pStatList.dwFlags & STATLIST_SET, 0u);
			CHECK_EQ(moo_pStatListEx.pMyLastList, &moo_pStatList);
			CHECK_EQ(moo_pStatListEx.pMyStats, nullptr);

			for (auto i = 0; i < stat_count; ++i)
			{
				CHECK_EQ(moo_pUnitStat[plain_stat_ids[i]].nValue, unit_stat_array[plain_stat_ids[i]].nValue + stat_array[i].nValue);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB8F30 (#10525)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10525, dll_base + 0x00078F30);

		SUBCASE("")
		{
			// Input data
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto full_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto source_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 100 + i;

				full_stat_array[i].nLayer = 0;
				full_stat_array[i].nStat = static_cast<uint16_t>(i);
				full_stat_array[i].nValue = 10000 + i;

				source_stat_array[i].nLayer = 0;
				source_stat_array[i].nStat = static_cast<uint16_t>(i);
				source_stat_array[i].nValue = 200 + i;
			}

			D2UnitStrc moo_pUnit1{};
			D2StatListExStrc moo_pStatListEx1{};
			const auto moo_pBaseStat1 = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStat1 = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc moo_pUnit2{};
			D2StatListExStrc moo_pStatListEx2{};
			const auto moo_pFullStat2 = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit1{};
			D2StatListExStrc original_pStatListEx1{};
			const auto original_pBaseStat1 = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStat1 = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit2{};
			D2StatListExStrc original_pStatListEx2{};
			const auto original_pFullStat2 = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &base_stat_array, &full_stat_array, &source_stat_array](
				D2UnitStrc& pUnit1,
				D2StatListExStrc& pStatListEx1,
				const std::unique_ptr<D2StatStrc[]>& pBaseStat1,
				const std::unique_ptr<D2StatStrc[]>& pFullStat1,
				D2UnitStrc& pUnit2,
				D2StatListExStrc& pStatListEx2,
				const std::unique_ptr<D2StatStrc[]>& pFullStat2
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pStatListEx = &pStatListEx1;
				pStatListEx1.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pBaseStat1.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx1.Stats.pStat = pBaseStat1.get();
				pStatListEx1.Stats.nStatCount = itemstatcost_record_count;
				pStatListEx1.Stats.nCapacity = itemstatcost_record_count;
				std::memcpy(pFullStat1.get(), full_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx1.FullStats.pStat = pFullStat1.get();
				pStatListEx1.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx1.FullStats.nCapacity = itemstatcost_record_count;
				pUnit2.pStatListEx = &pStatListEx2;
				pStatListEx2.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pFullStat2.get(), source_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx2.FullStats.pStat = pFullStat2.get();
				pStatListEx2.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx2.FullStats.nCapacity = itemstatcost_record_count;
			};

			setup_data(moo_pUnit1, moo_pStatListEx1, moo_pBaseStat1, moo_pFullStat1, moo_pUnit2, moo_pStatListEx2, moo_pFullStat2);
			setup_data(original_pUnit1, original_pStatListEx1, original_pBaseStat1, original_pFullStat1, original_pUnit2, original_pStatListEx2, original_pFullStat2);

			// Call both implementations
			sut(&moo_pUnit1, &moo_pUnit2);
			original(&original_pUnit1, &original_pUnit2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatListEx1.FullStats.pStat, moo_pStatListEx1.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatListEx1.FullStats.pStat, original_pStatListEx1.FullStats.nStatCount }), "Comparing pStatListEx1->FullStats");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB91C0 (#10474)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10474, dll_base + 0x000791C0);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnused{};
			D2StatListStrc moo_pStatList{};
			D2StatListStrc moo_pPreviousStatList{};
			D2StatListStrc moo_pNextStatList{};
			D2UnitStrc original_pUnused{};
			D2StatListStrc original_pStatList{};
			D2StatListStrc original_pPreviousStatList{};
			D2StatListStrc original_pNextStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnused,
				D2StatListStrc& pStatList,
				D2StatListStrc& pPreviousStatList,
				D2StatListStrc& pNextStatList
			) {
				pStatList.pPrevLink = &pPreviousStatList;
				pStatList.pNextLink = &pNextStatList;
				pPreviousStatList.pNextLink = &pStatList;
				pNextStatList.pPrevLink = &pStatList;
			};

			setup_data(moo_pUnused, moo_pStatList, moo_pPreviousStatList, moo_pNextStatList);
			setup_data(original_pUnused, original_pStatList, original_pPreviousStatList, original_pNextStatList);

			// Call both implementations
			sut(&moo_pUnused, &moo_pStatList);
			original(&original_pUnused, &original_pStatList);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ(moo_pPreviousStatList, original_pPreviousStatList, "Comparing pPreviousStatList");
			MOO_CHECK_EQ(moo_pNextStatList, original_pNextStatList, "Comparing pNextStatList");

			CHECK_EQ(moo_pStatList.pPrevLink, nullptr);
			CHECK_EQ(moo_pStatList.pNextLink, nullptr);
			CHECK_EQ(moo_pPreviousStatList.pNextLink, &moo_pNextStatList);
			CHECK_EQ(moo_pNextStatList.pPrevLink, &moo_pPreviousStatList);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB91D0 (#10564)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetMaxLifeFromUnit, dll_base + 0x000791D0);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[STAT_MAXHP].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB92C0 (#10565)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetMaxManaFromUnit, dll_base + 0x000792C0);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[STAT_MAXMANA].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB93B0 (#10566)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetMaxStaminaFromUnit, dll_base + 0x000793B0);

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[STAT_MAXSTAMINA].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB94A0 (#10567)" * doctest::skip("Seems incorrect at the moment (wrong stat array)"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetMaxDurabilityFromUnit, dll_base + 0x000794A0);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.Stats.pStat = pStat.get();
				pStatListEx.Stats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[STAT_MAXDURABILITY].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB95D0 (#10568)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetMaxDamageFromUnit, dll_base + 0x000795D0);

		SUBCASE("")
		{
			// Input data
			const auto two_handed = GENERATE(0, 1);

			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			BOOL b2Handed = two_handed;

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, b2Handed);
			const auto original_result = original(&original_pUnit, b2Handed);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[b2Handed ? STAT_SECONDARY_MAXDAMAGE : STAT_MAXDAMAGE].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB96F0 (#10569)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetMinDamageFromUnit, dll_base + 0x000796F0);
		
		SUBCASE("")
		{
			// Input data
			const auto two_handed = GENERATE(0, 1);

			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			BOOL b2Handed = two_handed;

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, b2Handed);
			const auto original_result = original(&original_pUnit, b2Handed);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[b2Handed ? STAT_SECONDARY_MINDAMAGE : STAT_MINDAMAGE].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB9810 (#10570)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetMaxThrowDamageFromUnit, dll_base + 0x00079810);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[STAT_ITEM_THROW_MAXDAMAGE].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB9900 (#10571)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetMinThrowDamageFromUnit, dll_base + 0x00079900);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[STAT_ITEM_THROW_MINDAMAGE].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB99F0 (#10572)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetDefenseFromUnit, dll_base + 0x000799F0);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
			setup_data(original_pUnit, original_pStatListEx, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, stat_array[STAT_ARMORCLASS].nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB9AE0 (#10524)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_ExpireUnitStatlist, dll_base + 0x00079AE0);

		SUBCASE("")
		{
			// Input data
			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count, 10);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = plain_stat_ids[i];
				stat_array[i].nValue = 100 + i;
			}

			const auto parent_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				parent_stat_array[i].nLayer = 0;
				parent_stat_array[i].nStat = static_cast<uint16_t>(i);
				parent_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnused{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2StatListExStrc moo_pParentStatListEx{};
			const auto moo_pParentStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnused{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2StatListExStrc original_pParentStatListEx{};
			const auto original_pParentStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, stat_count, &stat_array, &parent_stat_array](
				D2UnitStrc& pUnused,
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2StatListExStrc& pParentStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pParentStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = stat_count;
				pStatListEx.FullStats.nCapacity = stat_count;
				pStatListEx.pParent = &pParentStatListEx;
				pParentStatListEx.dwFlags |= STATLIST_EXTENDED;
				pParentStatListEx.pMyLastList = &pStatListEx;
				std::memcpy(pParentStat.get(), parent_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pParentStatListEx.FullStats.pStat = pParentStat.get();
				pParentStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pParentStatListEx.FullStats.nCapacity = itemstatcost_record_count;
			};

			setup_data(moo_pUnused, moo_pUnit, moo_pStatListEx, moo_pStat, moo_pParentStatListEx, moo_pParentStat);
			setup_data(original_pUnused, original_pUnit, original_pStatListEx, original_pStat, original_pParentStatListEx, original_pParentStat);

			// Call both implementations
			sut(&moo_pUnused, &moo_pUnit);
			original(&original_pUnused, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pParentStatListEx, original_pParentStatListEx, "Comparing pParentStatListEx");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pParentStatListEx.FullStats.pStat, moo_pParentStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pParentStatListEx.FullStats.pStat, original_pParentStatListEx.FullStats.nStatCount }), "Comparing pParentStatListEx->FullStats");

			CHECK_EQ(moo_pStatListEx.pParent, nullptr);
			CHECK_EQ(moo_pParentStatListEx.pMyLastList, nullptr);

			for (auto i = 0; i < stat_count; ++i)
			{
				CHECK_EQ(moo_pParentStat[plain_stat_ids[i]].nValue, parent_stat_array[plain_stat_ids[i]].nValue - stat_array[i].nValue);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB9B00 (#10531)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10531_SetStatInStatListLayer0, dll_base + 0x00079B00);

		SUBCASE("")
		{
			// Input data
			const auto size = 20;
			const auto stat_array = std::make_unique<D2StatStrc[]>(size);

			for (auto i = 0; i < size; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2StatListStrc moo_pStatList{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(size);
			D2StatListStrc original_pStatList{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(size);
			int nStatId = 5;
			int nValue = 42;
			int nUnused = random_unsigned_integer();

			const auto setup_data = [&stat_array, size](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * size);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = size;
				pStatList.Stats.nCapacity = size;
			};

			setup_data(moo_pStatList, moo_pStat);
			setup_data(original_pStatList, original_pStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, nValue, nUnused);
			const auto original_result = original(&original_pStatList, nStatId, nValue, nUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pStatList.Stats.pStat, moo_pStatList.Stats.nStatCount }), (DynamicArray<D2StatStrc> { original_pStatList.Stats.pStat, original_pStatList.Stats.nStatCount }), "Comparing pStatList->Stats");

			CHECK_EQ(moo_result, TRUE);
			CHECK_EQ(moo_pStatList.Stats.pStat[nStatId].nValue, nValue);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB9B10 (#11248)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11248, dll_base + 0x00079B10);

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				stat_array[i].nLayer = 0;
				stat_array[i].nStat = static_cast<uint16_t>(i);
				stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pUnused{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnused{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				const auto setup_data = [this, i, &stat_array](
					D2UnitStrc& pUnused,
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					const std::unique_ptr<D2StatStrc[]>& pStat,
					D2ItemStatCostTxt& pItemStatCostTxtRecord
				) {
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
					pStatListEx.FullStats.pStat = pStat.get();
					pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
					pItemStatCostTxtRecord = itemstatcost_txt[i];
				};

				int nStatId = i;

				setup_data(moo_pUnused, moo_pUnit, moo_pStatListEx, moo_pStat, moo_pItemStatCostTxtRecord);
				setup_data(original_pUnused, original_pUnit, original_pStatListEx, original_pStat, original_pItemStatCostTxtRecord);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnused, &moo_pUnit, nStatId);
				const auto original_result = original(&original_pUnused, &original_pUnit, nStatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, 10000 + i);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E60 (#11264)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetSkillId, dll_base + 0x00069E60);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nSkillId = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pStatList, nSkillId);
			original(&original_pStatList, nSkillId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9C10 (#11265)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetSkillId, dll_base + 0x00079C10);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_id = random_unsigned_integer();

			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [skill_id](
				D2StatListStrc& pStatList
			) {
				pStatList.dwSkillNo = skill_id;
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList);
			const auto original_result = original(&original_pStatList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9C20 (#11266)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetSkillLevel, dll_base + 0x00079C20);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nSkillLevel = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pStatList, nSkillLevel);
			original(&original_pStatList, nSkillLevel);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA9E70 (#11267)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetSkillLevel, dll_base + 0x00069E70);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_level = random_unsigned_integer();

			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [skill_level](
				D2StatListStrc& pStatList
			) {
				pStatList.dwSLvl = skill_level;
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList);
			const auto original_result = original(&original_pStatList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9C30 (#11269)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_11269_CopyStats, dll_base + 0x00079C30);

		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(20);

			for (auto i = 0; i < 20; ++i)
			{
				stat_array[i].nLayer = random_unsigned_integer(0, 255);
				stat_array[i].nStat = i >= 15 ? static_cast<uint16_t>(42 + i) : 42;
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pBuffer[10]{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(20);
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pBuffer[10]{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(20);
			int nStatId = 42;
			int nBufferSize = 10;

			const auto setup_data = [&stat_array](
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2StatStrc(&pBuffer)[10]
			) {
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * 20);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = 20;
			};

			setup_data(moo_pStatListEx, moo_pStat, moo_pBuffer);
			setup_data(original_pStatListEx, original_pStat, original_pBuffer);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatListEx, nStatId, moo_pBuffer, nBufferSize);
			const auto original_result = original(&original_pStatListEx, nStatId, original_pBuffer, nBufferSize);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pBuffer, 10 }), (DynamicArray<D2StatStrc> { original_pBuffer, 10 }), "Comparing pBuffer");

			for (auto i = 0; i < moo_result; ++i)
			{
				CHECK_EQ(moo_pBuffer[i].nStat, 42);
			}

			CHECK_EQ(moo_result, 10);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9C50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_CopyStats_6FDB9C50, dll_base + 0x00079C50);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(20);

			for (auto i = 0; i < 20; ++i)
			{
				stat_array[i].nLayer = random_unsigned_integer(0, 255);
				stat_array[i].nStat = i < 15 ? static_cast<uint16_t>(i) : 20;
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2StatListStrc moo_pStatList{};
			D2StatStrc moo_pBuffer[10]{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(20);
			D2StatListStrc original_pStatList{};
			D2StatStrc original_pBuffer[10]{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(20);
			int nStatId = 20;
			int nBufferSize = 10;

			const auto setup_data = [&stat_array](
				D2StatListStrc& pStatList,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2StatStrc (&pBuffer)[10]
			) {
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * 20);
				pStatList.Stats.pStat = pStat.get();
				pStatList.Stats.nStatCount = 20;
			};

			setup_data(moo_pStatList, moo_pStat, moo_pBuffer);
			setup_data(original_pStatList, original_pStat, original_pBuffer);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, moo_pBuffer, nBufferSize);
			const auto original_result = original(&original_pStatList, nStatId, original_pBuffer, nBufferSize);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pBuffer, 10 }), (DynamicArray<D2StatStrc> { original_pBuffer, 10 }), "Comparing pBuffer");

			for (auto i = 0; i < moo_result; ++i)
			{
				CHECK_EQ(moo_pBuffer[i].nStat, 20);
			}

			CHECK_EQ(moo_result, 5);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9D20 (#11270)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_CopyStats, dll_base + 0x00079D20);
		
		SUBCASE("")
		{
			// Input data
			const auto stat_array = std::make_unique<D2StatStrc[]>(20);

			for (auto i = 0; i < 20; ++i)
			{
				stat_array[i].nLayer = random_unsigned_integer(0, 255);
				stat_array[i].nStat = i >= 7 ? static_cast<uint16_t>(23 + i) : 23;
				stat_array[i].nValue = random_unsigned_integer();
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pBuffer[10]{};
			const auto moo_pStat = std::make_unique<D2StatStrc[]>(20);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pBuffer[10]{};
			const auto original_pStat = std::make_unique<D2StatStrc[]>(20);
			int nStatId = 23;
			int nBufferSize = 10;

			const auto setup_data = [&stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pStat,
				D2StatStrc(&pBuffer)[10]
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pStat.get(), stat_array.get(), sizeof(D2StatStrc) * 20);
				pStatListEx.FullStats.pStat = pStat.get();
				pStatListEx.FullStats.nStatCount = 20;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pBuffer);
			setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pBuffer);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nStatId, moo_pBuffer, nBufferSize);
			const auto original_result = original(&original_pUnit, nStatId, original_pBuffer, nBufferSize);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pBuffer, 10 }), (DynamicArray<D2StatStrc> { original_pBuffer, 10 }), "Comparing pBuffer");

			for (auto i = 0; i < moo_result; ++i)
			{
				CHECK_EQ(moo_pBuffer[i].nStat, 23);
			}

			CHECK_EQ(moo_result, 7);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB9D60 (#11273)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11273, dll_base + 0x00079D60);

		SUBCASE("")
		{
			// Input data
			const auto base_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto full_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				base_stat_array[i].nLayer = 0;
				base_stat_array[i].nStat = static_cast<uint16_t>(i);
				base_stat_array[i].nValue = 100 + i;

				full_stat_array[i].nLayer = 0;
				full_stat_array[i].nStat = static_cast<uint16_t>(i);
				full_stat_array[i].nValue = 300 + 2 * i;
			}

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			const auto moo_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto moo_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			const auto original_pBaseStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			const auto original_pFullStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			const auto setup_data = [this, &base_stat_array, &full_stat_array](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pBaseStat,
				const std::unique_ptr<D2StatStrc[]>& pFullStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = UNIT_PLAYER;
				std::memcpy(pBaseStat.get(), base_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.Stats.pStat = pBaseStat.get();
				pStatListEx.Stats.nStatCount = itemstatcost_record_count;
				pStatListEx.Stats.nCapacity = itemstatcost_record_count;
				std::memcpy(pFullStat.get(), full_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pStatListEx.FullStats.pStat = pFullStat.get();
				pStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pStatListEx.FullStats.nCapacity = itemstatcost_record_count;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pBaseStat, moo_pFullStat);
			setup_data(original_pUnit, original_pStatListEx, original_pBaseStat, original_pFullStat);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				int nStatId = i;

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nStatId);
				const auto original_result = original(&original_pUnit, nStatId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB9D90 (#11274)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11274, dll_base + 0x00079D90);

		SUBCASE("")
		{
			// Input data
			const auto is_dynamic = GENERATE(0, 1);

			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto unit_stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				unit_stat_array[i].nLayer = 0;
				unit_stat_array[i].nStat = plain_stat_ids[i];
				unit_stat_array[i].nValue = 100 + i;
			}

			const auto target_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				target_stat_array[i].nLayer = 0;
				target_stat_array[i].nStat = static_cast<uint16_t>(i);
				target_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pTarget{};
			D2StatListExStrc moo_pTargetStatListEx{};
			const auto moo_pTargetStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pUnitStatListEx{};
			const auto moo_pUnitStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2UnitStrc original_pTarget{};
			D2StatListExStrc original_pTargetStatListEx{};
			const auto original_pTargetStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pUnitStatListEx{};
			const auto original_pUnitStat = std::make_unique<D2StatStrc[]>(stat_count);

			const auto setup_data = [this, is_dynamic, stat_count, &unit_stat_array, &target_stat_array](
				D2UnitStrc& pTarget,
				D2StatListExStrc& pTargetStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pTargetStat,
				D2UnitStrc& pUnit,
				D2StatListExStrc& pUnitStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pUnitStat
			) {
				pTarget.pStatListEx = &pTargetStatListEx;
				pTargetStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pTargetStat.get(), target_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pTargetStatListEx.FullStats.pStat = pTargetStat.get();
				pTargetStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pTargetStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				pUnit.pStatListEx = &pUnitStatListEx;
				pUnitStatListEx.dwFlags |= STATLIST_EXTENDED;

				if (is_dynamic)
				{
					pUnitStatListEx.dwFlags |= STATLIST_DYNAMIC;
				}

				pUnitStatListEx.pUnit = &pTarget;
				std::memcpy(pUnitStat.get(), unit_stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pUnitStatListEx.FullStats.pStat = pUnitStat.get();
				pUnitStatListEx.FullStats.nStatCount = stat_count;
				pUnitStatListEx.FullStats.nCapacity = stat_count;
			};

			setup_data(moo_pTarget, moo_pTargetStatListEx, moo_pTargetStat, moo_pUnit, moo_pUnitStatListEx, moo_pUnitStat);
			setup_data(original_pTarget, original_pTargetStatListEx, original_pTargetStat, original_pUnit, original_pUnitStatListEx, original_pUnitStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pTarget, &moo_pUnit);
			const auto original_result = original(&original_pTarget, &original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pTargetStatListEx.FullStats.pStat, moo_pTargetStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pTargetStatListEx.FullStats.pStat, original_pTargetStatListEx.FullStats.nStatCount }), "Comparing pTargetStatListEx->FullStats");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, is_dynamic ? TRUE : FALSE);
			CHECK_EQ(moo_pUnitStatListEx.dwFlags & STATLIST_DYNAMIC, 0u);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB9E60 (#11275)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11275, dll_base + 0x00079E60);

		SUBCASE("")
		{
			// Input data
			const auto is_dynamic = GENERATE(0, 1);

			const auto plain_stat_ids = get_plain_stat_ids(itemstatcost_txt.get(), itemstatcost_record_count);
			const auto stat_count = static_cast<int>(plain_stat_ids.size());
			const auto unit_stat_array = std::make_unique<D2StatStrc[]>(stat_count);

			for (auto i = 0; i < stat_count; ++i)
			{
				unit_stat_array[i].nLayer = 0;
				unit_stat_array[i].nStat = plain_stat_ids[i];
				unit_stat_array[i].nValue = 100 + i;
			}

			const auto target_stat_array = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);

			for (auto i = 0; i < itemstatcost_record_count; ++i)
			{
				target_stat_array[i].nLayer = 0;
				target_stat_array[i].nStat = static_cast<uint16_t>(i);
				target_stat_array[i].nValue = 10000 + i;
			}

			D2UnitStrc moo_pTarget{};
			D2StatListExStrc moo_pTargetStatListEx{};
			const auto moo_pTargetStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pUnitStatListEx{};
			const auto moo_pUnitStat = std::make_unique<D2StatStrc[]>(stat_count);
			D2UnitStrc original_pTarget{};
			D2StatListExStrc original_pTargetStatListEx{};
			const auto original_pTargetStat = std::make_unique<D2StatStrc[]>(itemstatcost_record_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pUnitStatListEx{};
			const auto original_pUnitStat = std::make_unique<D2StatStrc[]>(stat_count);

			const auto setup_data = [this, is_dynamic, stat_count, &unit_stat_array, &target_stat_array](
				D2UnitStrc& pTarget,
				D2StatListExStrc& pTargetStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pTargetStat,
				D2UnitStrc& pUnit,
				D2StatListExStrc& pUnitStatListEx,
				const std::unique_ptr<D2StatStrc[]>& pUnitStat
			) {
				pTarget.pStatListEx = &pTargetStatListEx;
				pTargetStatListEx.dwFlags |= STATLIST_EXTENDED;
				std::memcpy(pTargetStat.get(), target_stat_array.get(), sizeof(D2StatStrc) * itemstatcost_record_count);
				pTargetStatListEx.FullStats.pStat = pTargetStat.get();
				pTargetStatListEx.FullStats.nStatCount = itemstatcost_record_count;
				pTargetStatListEx.FullStats.nCapacity = itemstatcost_record_count;
				pUnit.pStatListEx = &pUnitStatListEx;
				pUnitStatListEx.dwFlags |= STATLIST_EXTENDED;

				if (is_dynamic)
				{
					pUnitStatListEx.dwFlags |= STATLIST_DYNAMIC;
				}

				pUnitStatListEx.pUnit = &pTarget;
				std::memcpy(pUnitStat.get(), unit_stat_array.get(), sizeof(D2StatStrc) * stat_count);
				pUnitStatListEx.FullStats.pStat = pUnitStat.get();
				pUnitStatListEx.FullStats.nStatCount = stat_count;
				pUnitStatListEx.FullStats.nCapacity = stat_count;
			};

			setup_data(moo_pTarget, moo_pTargetStatListEx, moo_pTargetStat, moo_pUnit, moo_pUnitStatListEx, moo_pUnitStat);
			setup_data(original_pTarget, original_pTargetStatListEx, original_pTargetStat, original_pUnit, original_pUnitStatListEx, original_pUnitStat);

			// Call both implementations
			const auto moo_result = sut(&moo_pTarget, &moo_pUnit);
			const auto original_result = original(&original_pTarget, &original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			MOO_CHECK_EQ((DynamicArray<D2StatStrc> { moo_pTargetStatListEx.FullStats.pStat, moo_pTargetStatListEx.FullStats.nStatCount }), (DynamicArray<D2StatStrc> { original_pTargetStatListEx.FullStats.pStat, original_pTargetStatListEx.FullStats.nStatCount }), "Comparing pTargetStatListEx->FullStats");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			CHECK_EQ(moo_result, is_dynamic ? FALSE : TRUE);
			CHECK_NE(moo_pUnitStatListEx.dwFlags & STATLIST_DYNAMIC, 0u);
		}
	}
}

#endif
