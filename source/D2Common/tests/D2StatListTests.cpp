#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2StatList.h>
#include <GAME/Game.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>

DYNAMIC_ARRAY_TYPE(D2StatStrc)
DYNAMIC_ARRAY_TYPE(uint32_t)


TEST_SUITE("D2StatListTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB57C0 (#10563)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_AreUnitsAligned, dll_base + 0x000757C0);
		
		SUBCASE("")
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
				// TODO: Setup as needed
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
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB5830" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB5830, dll_base + 0x00075830);
		
		SUBCASE("")
		{
			// Input data
			D2StatListExStrc moo_pStatListEx{};
			D2StatListExStrc original_pStatListEx{};
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};

			const auto setup_data = [](
				D2StatListExStrc& pStatListEx
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatListEx);
			setup_data(original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatListEx, nLayer_StatId);
			const auto original_result = original(&original_pStatListEx, nLayer_StatId);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB64A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB64A0, dll_base + 0x000764A0);
		
		SUBCASE("")
		{
			// Input data
			D2StatListExStrc moo_pStatListEx{};
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnit{};
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};

			const auto setup_data = [](
				D2StatListExStrc& pStatListEx,
				D2ItemStatCostTxt& pItemStatCostTxtRecord,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatListEx, moo_pItemStatCostTxtRecord, moo_pUnit);
			setup_data(original_pStatListEx, original_pItemStatCostTxtRecord, original_pUnit);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB6AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_UpdateUnitStat_6FDB6AB0, dll_base + 0x00076AB0);
		
		SUBCASE("")
		{
			// Input data
			D2StatListExStrc moo_pStatList{};
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatList{};
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			D2UnitStrc original_pUnit{};
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};
			int nNewValue{};

			const auto setup_data = [](
				D2StatListExStrc& pStatList,
				D2ItemStatCostTxt& pItemStatCostTxtRecord,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatList, moo_pItemStatCostTxtRecord, moo_pUnit);
			setup_data(original_pStatList, original_pItemStatCostTxtRecord, original_pUnit);

			// Call both implementations
			sut(&moo_pStatList, nLayer_StatId, nNewValue, &moo_pItemStatCostTxtRecord, &moo_pUnit);
			original(&original_pStatList, nLayer_StatId, nNewValue, &original_pItemStatCostTxtRecord, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB6C10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB6C10, dll_base + 0x00076C10);
		
		SUBCASE("")
		{
			// Input data
			D2StatListExStrc moo_pStatListEx{};
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2UnitStrc original_pUnit{};
			D2SLayerStatIdStrc::PackedType nLayer_StatId{};
			int nValue{};

			const auto setup_data = [](
				D2StatListExStrc& pStatListEx,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatListEx, moo_pUnit);
			setup_data(original_pStatListEx, original_pUnit);

			// Call both implementations
			sut(&moo_pStatListEx, nLayer_StatId, nValue, &moo_pUnit);
			original(&original_pStatListEx, nLayer_StatId, nValue, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB6E30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_ExpireStatList_6FDB6E30, dll_base + 0x00076E30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7340 (#10475)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10475_PostStatToStatList, dll_base + 0x00077340);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListStrc moo_pStatList{};
			D2UnitStrc original_pUnit{};
			D2StatListStrc original_pStatList{};
			BOOL bResetFlag{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pStatList);
			setup_data(original_pUnit, original_pStatList);

			// Call both implementations
			sut(&moo_pUnit, &moo_pStatList, bResetFlag);
			original(&original_pUnit, &original_pStatList, bResetFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7560 (#10464)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_AddStat, dll_base + 0x00077560);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nStatId{};
			int nValue{};
			uint16_t nLayer{};

			const auto setup_data = [](
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			sut(&moo_pStatList, nStatId, nValue, nLayer);
			original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB77B0 (#10463)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetStat, dll_base + 0x000777B0);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nStatId{};
			int nValue{};
			uint16_t nLayer{};

			const auto setup_data = [](
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, nValue, nLayer);
			const auto original_result = original(&original_pStatList, nStatId, nValue, nLayer);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7910 (#10465)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetStatIfListIsValid, dll_base + 0x00077910);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nStatId{};
			int nValue{};
			uint16_t nLayer{};

			const auto setup_data = [](
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			sut(&moo_pStatList, nStatId, nValue, nLayer);
			original(&original_pStatList, nStatId, nValue, nLayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7930 (#11294)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetBaseStat, dll_base + 0x00077930);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2UnitStrc moo_pUnit{};
			D2StatListStrc original_pStatList{};
			D2UnitStrc original_pUnit{};
			int nStatId{};
			int nValue{};
			uint16_t nLayer{};

			const auto setup_data = [](
				D2StatListStrc& pStatList,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatList, moo_pUnit);
			setup_data(original_pStatList, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, nValue, nLayer, &moo_pUnit);
			const auto original_result = original(&original_pStatList, nStatId, nValue, nLayer, &original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7AB0 (#10517)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_SetUnitStat, dll_base + 0x00077AB0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nStatId{};
			int nValue{};
			uint16_t nLayer{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nStatId, nValue, nLayer);
			original(&original_pUnit, nStatId, nValue, nLayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB7B00 (#10518)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_AddUnitStat, dll_base + 0x00077B00);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nStatId{};
			int nValue{};
			uint16_t nLayer{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nStatId, nValue, nLayer);
			original(&original_pUnit, nStatId, nValue, nLayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB80C0 (#10515)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_DeactivateTemporaryStates, dll_base + 0x000780C0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8150 (#10468)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_RemoveAllStats, dll_base + 0x00078150);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_GetStateFromStatListEx_6FDB8190, dll_base + 0x00078190);
		
		SUBCASE("")
		{
			// Input data
			D2StatListExStrc moo_pStatListEx{};
			D2StatListExStrc original_pStatListEx{};
			int nStateId{};

			const auto setup_data = [](
				D2StatListExStrc& pStatListEx
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatListEx);
			setup_data(original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatListEx, nStateId);
			const auto original_result = original(&original_pStatListEx, nStateId);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB81E0 (#10480)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromUnitAndState, dll_base + 0x000781E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nState{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nState);
			const auto original_result = original(&original_pUnit, nState);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8200 (#10482)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromFlag, dll_base + 0x00078200);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nFlag{};

			const auto setup_data = [](
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nFlag);
			const auto original_result = original(&original_pStatList, nFlag);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8230 (#10481)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromUnitAndFlag, dll_base + 0x00078230);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nFlag{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8270 (#10483)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromUnitStateOrFlag, dll_base + 0x00078270);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nState{};
			int nFlag{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nState, nFlag);
			const auto original_result = original(&original_pUnit, nState, nFlag);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB82C0 (#10484)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetStatListFromUnitStateAndFlag, dll_base + 0x000782C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nState{};
			int nFlag{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nState, nFlag);
			const auto original_result = original(&original_pUnit, nState, nFlag);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8310 (#10523)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_MergeStatLists, dll_base + 0x00078310);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pTarget{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pTarget{};
			D2UnitStrc original_pUnit{};
			BOOL bType{};

			const auto setup_data = [](
				D2UnitStrc& pTarget,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTarget, moo_pUnit);
			setup_data(original_pTarget, original_pUnit);

			// Call both implementations
			sut(&moo_pTarget, &moo_pUnit, bType);
			original(&original_pTarget, &original_pUnit, bType);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8420 (#10512)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10512, dll_base + 0x00078420);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};
			int nStatId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			sut(&moo_pUnit1, &moo_pUnit2, nStatId, nullptr);
			original(&original_pUnit1, &original_pUnit2, nStatId, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB84E0 (#10513)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10513, dll_base + 0x000784E0);
		
		SUBCASE("")
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
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			sut(&moo_pUnit1, &moo_pUnit2, nullptr);
			original(&original_pUnit1, &original_pUnit2, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB85D0 (#10511)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_FreeModStats, dll_base + 0x000785D0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8620 (#10562)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_GetUnitAlignment, dll_base + 0x00078620);
		
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
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
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
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatListEx{};
			D2StatListStrc original_pStatListEx{};
			int nStatId{};

			const auto setup_data = [](
				D2StatListStrc& pStatListEx
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatListEx);
			setup_data(original_pStatListEx);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatListEx, nStatId);
			const auto original_result = original(&original_pStatListEx, nStatId);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatListEx, original_pStatListEx, "Comparing pStatListEx");
		}

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8890 (#10533)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_RemoveAllStatsFromOverlay, dll_base + 0x00078890);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8C50 (#10573)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_MergeBaseStats, dll_base + 0x00078C50);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pTargetStatList{};
			D2StatListStrc moo_pSourceStatlist{};
			D2StatListStrc original_pTargetStatList{};
			D2StatListStrc original_pSourceStatlist{};

			const auto setup_data = [](
				D2StatListStrc& pTargetStatList,
				D2StatListStrc& pSourceStatlist
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTargetStatList, moo_pSourceStatlist);
			setup_data(original_pTargetStatList, original_pSourceStatlist);

			// Call both implementations
			sut(&moo_pTargetStatList, &moo_pSourceStatlist);
			original(&original_pTargetStatList, &original_pSourceStatlist);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTargetStatList, original_pTargetStatList, "Comparing pTargetStatList");
			MOO_CHECK_EQ(moo_pSourceStatlist, original_pSourceStatlist, "Comparing pSourceStatlist");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8CC0 (#10469)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10469, dll_base + 0x00078CC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8D30 (#10514)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_ClampStaminaManaHP, dll_base + 0x00078D30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8EB0 (#10574)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10574, dll_base + 0x00078EB0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nStateId{};
			BOOL bSet{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nStateId, bSet);
			const auto original_result = original(&original_pUnit, nStateId, bSet);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB8F30 (#10525)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10525, dll_base + 0x00078F30);
		
		SUBCASE("")
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
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			sut(&moo_pUnit1, &moo_pUnit2);
			original(&original_pUnit1, &original_pUnit2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB91C0 (#10474)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10474, dll_base + 0x000791C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnused{};
			D2StatListStrc moo_pStatList{};
			D2UnitStrc original_pUnused{};
			D2StatListStrc original_pStatList{};

			const auto setup_data = [](
				D2UnitStrc& pUnused,
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnused, moo_pStatList);
			setup_data(original_pUnused, original_pStatList);

			// Call both implementations
			sut(&moo_pUnused, &moo_pStatList);
			original(&original_pUnused, &original_pStatList);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9AE0 (#10524)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(STATLIST_ExpireUnitStatlist, dll_base + 0x00079AE0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnused{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnused{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnused,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnused, moo_pUnit);
			setup_data(original_pUnused, original_pUnit);

			// Call both implementations
			sut(&moo_pUnused, &moo_pUnit);
			original(&original_pUnused, &original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9B00 (#10531)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10531_SetStatInStatListLayer0, dll_base + 0x00079B00);
		
		SUBCASE("")
		{
			// Input data
			D2StatListStrc moo_pStatList{};
			D2StatListStrc original_pStatList{};
			int nStatId{};
			int nValue{};
			int nUnused{};

			const auto setup_data = [](
				D2StatListStrc& pStatList
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pStatList);
			setup_data(original_pStatList);

			// Call both implementations
			const auto moo_result = sut(&moo_pStatList, nStatId, nValue, nUnused);
			const auto original_result = original(&original_pStatList, nStatId, nValue, nUnused);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9D60 (#11273)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11273, dll_base + 0x00079D60);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nStatId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nStatId);
			const auto original_result = original(&original_pUnit, nStatId);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9D90 (#11274)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11274, dll_base + 0x00079D90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pTarget{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pTarget{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pTarget,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTarget, moo_pUnit);
			setup_data(original_pTarget, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pTarget, &moo_pUnit);
			const auto original_result = original(&original_pTarget, &original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB9E60 (#11275)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11275, dll_base + 0x00079E60);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pTarget{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pTarget{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pTarget,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTarget, moo_pUnit);
			setup_data(original_pTarget, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pTarget, &moo_pUnit);
			const auto original_result = original(&original_pTarget, &original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
