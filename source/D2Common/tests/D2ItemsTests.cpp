#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Items.h>
#include <D2StatList.h>
#include <GAME/Game.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


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
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				pItem.dwUnitType = UNIT_ITEM;
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			sut(moo_pMemPool, &moo_pItem);
			original(original_pMemPool, &original_pItem);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD983F0 (#10688)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_FreeItemData, dll_base + 0x000583F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			void* moo_pMemPool = nullptr;
			void* original_pMemPool = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			sut(moo_pMemPool, &moo_pItem);
			original(original_pMemPool, &original_pItem);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMemPool, original_pMemPool, "Comparing pMemPool");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD98A70 (#10777)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsRepairable, dll_base + 0x00058A70);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD99740 (#10756)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckRequirements, dll_base + 0x00059740);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pUnit{};
			BOOL moo_bStrength{};
			BOOL moo_bDexterity{};
			BOOL moo_bLevel{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pUnit{};
			BOOL original_bStrength{};
			BOOL original_bDexterity{};
			BOOL original_bLevel{};
			BOOL bEquipping{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2UnitStrc& pUnit,
				BOOL& bStrength,
				BOOL& bDexterity,
				BOOL& bLevel
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pUnit, moo_bStrength, moo_bDexterity, moo_bLevel);
			setup_data(original_pItem, original_pUnit, original_bStrength, original_bDexterity, original_bLevel);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pUnit, bEquipping, &moo_bStrength, &moo_bDexterity, &moo_bLevel);
			const auto original_result = original(&original_pItem, &original_pUnit, bEquipping, &original_bStrength, &original_bDexterity, &original_bLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_bStrength, original_bStrength, "Comparing bStrength");
			SKIP_MOO_CHECK_EQ(moo_bDexterity, original_bDexterity, "Comparing bDexterity");
			SKIP_MOO_CHECK_EQ(moo_bLevel, original_bLevel, "Comparing bLevel");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD99BC0 (#10741)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetQuestFromItemId, dll_base + 0x00059BC0);
		
		SUBCASE("")
		{
			int nItemId{};

			// Call both implementations
			const auto moo_result = sut(nItemId);
			const auto original_result = original(nItemId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD99C60 (#10742)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetQuest, dll_base + 0x00059C60);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD99DB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetRequiredLevel, dll_base + 0x00059DB0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pPlayer);
			setup_data(original_pItem, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pPlayer);
			const auto original_result = original(&original_pItem, &original_pPlayer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9A3F0 (#10757)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetLevelRequirement, dll_base + 0x0005A3F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pUnit);
			setup_data(original_pItem, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pUnit);
			const auto original_result = original(&original_pItem, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9A400 (#10758)" * doctest::skip("Needs to have a closer look"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckBodyLocation, dll_base + 0x0005A400);
		
		SUBCASE("")
		{
			for (auto j = 0; j < NUM_BODYLOC; ++j)
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9A820 (#10769)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_ComparePotionTypes, dll_base + 0x0005A820);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem1{};
			D2UnitStrc moo_pItem2{};
			D2UnitStrc original_pItem1{};
			D2UnitStrc original_pItem2{};

			const auto setup_data = [](
				D2UnitStrc& pItem1,
				D2UnitStrc& pItem2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem1, moo_pItem2);
			setup_data(original_pItem1, original_pItem2);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem1, &moo_pItem2);
			const auto original_result = original(&original_pItem1, &original_pItem2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem1, original_pItem1, "Comparing pItem1");
			SKIP_MOO_CHECK_EQ(moo_pItem2, original_pItem2, "Comparing pItem2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9A960 (#10770)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckIfAutoBeltable, dll_base + 0x0005A960);
		
		SUBCASE("")
		{
			// Input data
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc moo_pItem{};
			D2InventoryStrc original_pInventory{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2InventoryStrc& pInventory,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pInventory, moo_pItem);
			setup_data(original_pInventory, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pInventory, &moo_pItem);
			const auto original_result = original(&original_pInventory, &original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9AB90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CalculateAdditionalCostsForChargedSkills, dll_base + 0x0005AB90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nBaseCost{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nBaseCost);
			const auto original_result = original(&original_pUnit, nBaseCost);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9ACE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CalculateAdditionalCostsForBonusStats, dll_base + 0x0005ACE0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			int moo_pSellCost{};
			int moo_pBuyCost{};
			int moo_pRepCost{};
			D2UnitStrc original_pItem{};
			int original_pSellCost{};
			int original_pBuyCost{};
			int original_pRepCost{};
			unsigned int nDivisor{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				int& pSellCost,
				int& pBuyCost,
				int& pRepCost
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pSellCost, moo_pBuyCost, moo_pRepCost);
			setup_data(original_pItem, original_pSellCost, original_pBuyCost, original_pRepCost);

			// Call both implementations
			sut(&moo_pItem, &moo_pSellCost, &moo_pBuyCost, &moo_pRepCost, nDivisor);
			original(&original_pItem, &original_pSellCost, &original_pBuyCost, &original_pRepCost, nDivisor);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pSellCost, original_pSellCost, "Comparing pSellCost");
			SKIP_MOO_CHECK_EQ(moo_pBuyCost, original_pBuyCost, "Comparing pBuyCost");
			SKIP_MOO_CHECK_EQ(moo_pRepCost, original_pRepCost, "Comparing pRepCost");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9B1C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CalculateTransactionCost, dll_base + 0x0005B1C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2BitBufferStrc moo_pQuestFlags{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			D2BitBufferStrc original_pQuestFlags{};
			D2C_Difficulties nDifficulty{};
			int nVendorId{};
			D2C_TransactionTypes nTransactionType{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem,
				D2BitBufferStrc& pQuestFlags
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pItem, moo_pQuestFlags);
			setup_data(original_pPlayer, original_pItem, original_pQuestFlags);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &moo_pItem, nDifficulty, &moo_pQuestFlags, nVendorId, nTransactionType);
			const auto original_result = original(&original_pPlayer, &original_pItem, nDifficulty, &original_pQuestFlags, nVendorId, nTransactionType);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9CB50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CalculateAdditionalCostsForItemSkill, dll_base + 0x0005CB50);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			int moo_pSellCost{};
			int moo_pBuyCost{};
			int moo_pRepCost{};
			D2UnitStrc original_pItem{};
			int original_pSellCost{};
			int original_pBuyCost{};
			int original_pRepCost{};
			unsigned int nDivisor{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				int& pSellCost,
				int& pBuyCost,
				int& pRepCost
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pSellCost, moo_pBuyCost, moo_pRepCost);
			setup_data(original_pItem, original_pSellCost, original_pBuyCost, original_pRepCost);

			// Call both implementations
			sut(&moo_pItem, &moo_pSellCost, &moo_pBuyCost, &moo_pRepCost, nDivisor);
			original(&original_pItem, &original_pSellCost, &original_pBuyCost, &original_pRepCost, nDivisor);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pSellCost, original_pSellCost, "Comparing pSellCost");
			SKIP_MOO_CHECK_EQ(moo_pBuyCost, original_pBuyCost, "Comparing pBuyCost");
			SKIP_MOO_CHECK_EQ(moo_pRepCost, original_pRepCost, "Comparing pRepCost");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9CDE0 (#10775)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetTransactionCost, dll_base + 0x0005CDE0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			D2BitBufferStrc moo_pQuestFlags{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			D2BitBufferStrc original_pQuestFlags{};
			D2C_Difficulties nDifficulty{};
			int nVendorId{};
			D2C_TransactionTypes nTransactionType{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem,
				D2BitBufferStrc& pQuestFlags
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pItem, moo_pQuestFlags);
			setup_data(original_pPlayer, original_pItem, original_pQuestFlags);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &moo_pItem, nDifficulty, &moo_pQuestFlags, nVendorId, nTransactionType);
			const auto original_result = original(&original_pPlayer, &original_pItem, nDifficulty, &original_pQuestFlags, nVendorId, nTransactionType);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
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
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9D0F0 (#10804)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSpellIcon, dll_base + 0x0005D0F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9D390 (#10811)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_HasDurability, dll_base + 0x0005D390);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9D580 (#10816)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSockets, dll_base + 0x0005D580);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9D5E0 (#10817)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AddSockets, dll_base + 0x0005D5E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int nSockets{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			sut(&moo_pItem, nSockets);
			original(&original_pItem, nSockets);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9D7C0 (#10818)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetSockets, dll_base + 0x0005D7C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int nSockets{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			sut(&moo_pItem, nSockets);
			original(&original_pItem, nSockets);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9D9D0 (#10821)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsSocketFiller, dll_base + 0x0005D9D0);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FD9DDD0 (#10803)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CheckBitField1Flag1, dll_base + 0x0005DDD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9E580 (#10740)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsNotQuestItem, dll_base + 0x0005E580);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9E710 (#10829)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetColor, dll_base + 0x0005E710);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pItem{};
			uint8_t moo_pColor{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pItem{};
			uint8_t original_pColor{};
			int nTransType{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				D2UnitStrc& pItem,
				uint8_t& pColor
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pItem, moo_pColor);
			setup_data(original_pPlayer, original_pItem, original_pColor);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &moo_pItem, &moo_pColor, nTransType);
			const auto original_result = original(&original_pPlayer, &original_pItem, &original_pColor, nTransType);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pColor, original_pColor, "Comparing pColor");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9EEA0 (#10830)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsImbueable, dll_base + 0x0005EEA0);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9F080 (#10832)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsPersonalizable, dll_base + 0x0005F080);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9F260 (#10831)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsSocketable, dll_base + 0x0005F260);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9F490 (#10877)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetAllRepairCosts, dll_base + 0x0005F490);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2BitBufferStrc moo_pQuestFlags{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2BitBufferStrc original_pQuestFlags{};
			int nNpcId{};
			D2C_Difficulties nDifficulty{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2BitBufferStrc& pQuestFlags
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pQuestFlags);
			setup_data(original_pGame, original_pUnit, original_pQuestFlags);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nNpcId, nDifficulty, &moo_pQuestFlags, nullptr);
			const auto original_result = original(&original_pGame, &original_pUnit, nNpcId, nDifficulty, &original_pQuestFlags, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pQuestFlags, original_pQuestFlags, "Comparing pQuestFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9F720 (#10833)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_AreStackablesEqual, dll_base + 0x0005F720);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem1{};
			D2UnitStrc moo_pItem2{};
			D2UnitStrc original_pItem1{};
			D2UnitStrc original_pItem2{};

			const auto setup_data = [](
				D2UnitStrc& pItem1,
				D2UnitStrc& pItem2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem1, moo_pItem2);
			setup_data(original_pItem1, original_pItem2);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem1, &moo_pItem2);
			const auto original_result = original(&original_pItem1, &original_pItem2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem1, original_pItem1, "Comparing pItem1");
			SKIP_MOO_CHECK_EQ(moo_pItem2, original_pItem2, "Comparing pItem2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FA70 (#10834)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_CanItemBeUsedForThrowSkill, dll_base + 0x0005FA70);
		
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
			const auto moo_result = sut(&moo_pItem);
			const auto original_result = original(&original_pItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FB50 (#10836)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetSetItemsMask, dll_base + 0x0005FB50);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pSetItem{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pSetItem{};
			BOOL bDontIgnoreInputItem{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer,
				D2UnitStrc& pSetItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer, moo_pSetItem);
			setup_data(original_pPlayer, original_pSetItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer, &moo_pSetItem, bDontIgnoreInputItem);
			const auto original_result = original(&original_pPlayer, &original_pSetItem, bDontIgnoreInputItem);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pSetItem, original_pSetItem, "Comparing pSetItem");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FE70 (#10840)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_IsCharmUsable, dll_base + 0x0005FE70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pPlayer);
			setup_data(original_pItem, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pPlayer);
			const auto original_result = original(&original_pItem, &original_pPlayer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD9FF00 (#10776)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetNoOfUnidItems, dll_base + 0x0005FF00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA0130 (#10878)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetWeaponAttackSpeed, dll_base + 0x00060130);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pWeapon{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pWeapon{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pWeapon
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pWeapon);
			setup_data(original_pUnit, original_pWeapon);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pWeapon);
			const auto original_result = original(&original_pUnit, &original_pWeapon);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pWeapon, original_pWeapon, "Comparing pWeapon");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA02B0 (#10879)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_HasUsedCharges, dll_base + 0x000602B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			BOOL moo_pHasChargedSkills{};
			D2UnitStrc original_pItem{};
			BOOL original_pHasChargedSkills{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				BOOL& pHasChargedSkills
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pHasChargedSkills);
			setup_data(original_pItem, original_pHasChargedSkills);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pHasChargedSkills);
			const auto original_result = original(&original_pItem, &original_pHasChargedSkills);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pHasChargedSkills, original_pHasChargedSkills, "Comparing pHasChargedSkills");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA0370 (#10883)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_GetCompactItemDataFromBitstream, dll_base + 0x00060370);
		
		SUBCASE("")
		{
			// Input data
			uint8_t moo_pBitstream{};
			D2ItemSaveStrc moo_pItemSave{};
			uint8_t original_pBitstream{};
			D2ItemSaveStrc original_pItemSave{};
			size_t nSize{};
			BOOL bCheckForHeader{};

			const auto setup_data = [](
				uint8_t& pBitstream,
				D2ItemSaveStrc& pItemSave
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pBitstream, moo_pItemSave);
			setup_data(original_pBitstream, original_pItemSave);

			// Call both implementations
			const auto moo_result = sut(&moo_pBitstream, nSize, bCheckForHeader, &moo_pItemSave);
			const auto original_result = original(&original_pBitstream, nSize, bCheckForHeader, &original_pItemSave);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pBitstream, original_pBitstream, "Comparing pBitstream");
			SKIP_MOO_CHECK_EQ(moo_pItemSave, original_pItemSave, "Comparing pItemSave");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA0490 (#10882)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DecodeItemFromBitstream, dll_base + 0x00060490);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			uint8_t moo_pBitstream{};
			int moo_pSocketedItemCount{};
			BOOL moo_pFail{};
			D2UnitStrc original_pItem{};
			uint8_t original_pBitstream{};
			int original_pSocketedItemCount{};
			BOOL original_pFail{};
			size_t nSize{};
			BOOL bCheckForHeader{};
			uint32_t dwVersion{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				uint8_t& pBitstream,
				int& pSocketedItemCount,
				BOOL& pFail
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pBitstream, moo_pSocketedItemCount, moo_pFail);
			setup_data(original_pItem, original_pBitstream, original_pSocketedItemCount, original_pFail);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pBitstream, nSize, bCheckForHeader, &moo_pSocketedItemCount, dwVersion, &moo_pFail);
			const auto original_result = original(&original_pItem, &original_pBitstream, nSize, bCheckForHeader, &original_pSocketedItemCount, dwVersion, &original_pFail);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBitstream, original_pBitstream, "Comparing pBitstream");
			SKIP_MOO_CHECK_EQ(moo_pSocketedItemCount, original_pSocketedItemCount, "Comparing pSocketedItemCount");
			SKIP_MOO_CHECK_EQ(moo_pFail, original_pFail, "Comparing pFail");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA0620" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DecodeItemBitstreamCompact, dll_base + 0x00060620);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2BitBufferStrc moo_pBuffer{};
			D2UnitStrc original_pItem{};
			D2BitBufferStrc original_pBuffer{};
			BOOL bCheckForHeader{};
			uint32_t dwVersion{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2BitBufferStrc& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pBuffer);
			setup_data(original_pItem, original_pBuffer);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pBuffer, bCheckForHeader, dwVersion);
			const auto original_result = original(&original_pItem, &original_pBuffer, bCheckForHeader, dwVersion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA0A20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_DecodeItemBitstreamComplete, dll_base + 0x00060A20);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2BitBufferStrc moo_pBuffer{};
			int moo_pSocketedItems{};
			D2UnitStrc original_pItem{};
			D2BitBufferStrc original_pBuffer{};
			int original_pSocketedItems{};
			BOOL bCheckForHeader{};
			BOOL bGamble{};
			uint32_t dwVersion{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2BitBufferStrc& pBuffer,
				int& pSocketedItems
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pBuffer, moo_pSocketedItems);
			setup_data(original_pItem, original_pBuffer, original_pSocketedItems);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pBuffer, bCheckForHeader, bGamble, &moo_pSocketedItems, dwVersion);
			const auto original_result = original(&original_pItem, &original_pBuffer, bCheckForHeader, bGamble, &original_pSocketedItems, dwVersion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
			SKIP_MOO_CHECK_EQ(moo_pSocketedItems, original_pSocketedItems, "Comparing pSocketedItems");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA2690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SetDefenseOrDamage, dll_base + 0x00062690);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			int nStat{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			sut(&moo_pItem, nStat);
			original(&original_pItem, nStat);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA29D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_ReadStatFromItemBitstream, dll_base + 0x000629D0);
		
		SUBCASE("")
		{
			// Input data
			D2BitBufferStrc moo_pBuffer{};
			D2StatListStrc moo_pStatList{};
			D2ItemStatCostTxt moo_pItemStatCostTxtRecord{};
			D2BitBufferStrc original_pBuffer{};
			D2StatListStrc original_pStatList{};
			D2ItemStatCostTxt original_pItemStatCostTxtRecord{};
			int nStatId{};
			uint32_t dwVersion{};
			int n109{};

			const auto setup_data = [](
				D2BitBufferStrc& pBuffer,
				D2StatListStrc& pStatList,
				D2ItemStatCostTxt& pItemStatCostTxtRecord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pBuffer, moo_pStatList, moo_pItemStatCostTxtRecord);
			setup_data(original_pBuffer, original_pStatList, original_pItemStatCostTxtRecord);

			// Call both implementations
			sut(&moo_pBuffer, &moo_pStatList, &moo_pItemStatCostTxtRecord, nStatId, dwVersion, n109);
			original(&original_pBuffer, &original_pStatList, &original_pItemStatCostTxtRecord, nStatId, dwVersion, n109);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
			SKIP_MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
			SKIP_MOO_CHECK_EQ(moo_pItemStatCostTxtRecord, original_pItemStatCostTxtRecord, "Comparing pItemStatCostTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA2BA0 (#10881)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SerializeItemToBitstream, dll_base + 0x00062BA0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			uint8_t moo_pBitstream{};
			D2UnitStrc original_pItem{};
			uint8_t original_pBitstream{};
			size_t nSize{};
			BOOL bServer{};
			BOOL bSaveItemInv{};
			BOOL bGamble{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				uint8_t& pBitstream
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pBitstream);
			setup_data(original_pItem, original_pBitstream);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pBitstream, nSize, bServer, bSaveItemInv, bGamble);
			const auto original_result = original(&original_pItem, &original_pBitstream, nSize, bServer, bSaveItemInv, bGamble);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBitstream, original_pBitstream, "Comparing pBitstream");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "Inlined in D2Common.0x6FDA2C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SerializeItemCompact, dll_base + 0x00062C00);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2BitBufferStrc moo_pBuffer{};
			D2ItemsTxt moo_pItemsTxtRecord{};
			D2UnitStrc original_pItem{};
			D2BitBufferStrc original_pBuffer{};
			D2ItemsTxt original_pItemsTxtRecord{};
			BOOL bServer{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2BitBufferStrc& pBuffer,
				D2ItemsTxt& pItemsTxtRecord
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pBuffer, moo_pItemsTxtRecord);
			setup_data(original_pItem, original_pBuffer, original_pItemsTxtRecord);

			// Call both implementations
			sut(&moo_pItem, &moo_pBuffer, &moo_pItemsTxtRecord, bServer);
			original(&original_pItem, &original_pBuffer, &original_pItemsTxtRecord, bServer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
			SKIP_MOO_CHECK_EQ(moo_pItemsTxtRecord, original_pItemsTxtRecord, "Comparing pItemsTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA2C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SerializeItem, dll_base + 0x00062C00);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2BitBufferStrc moo_pBuffer{};
			D2UnitStrc original_pItem{};
			D2BitBufferStrc original_pBuffer{};
			BOOL bServer{};
			BOOL bSaveItemInv{};
			BOOL bGamble{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2BitBufferStrc& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pBuffer);
			setup_data(original_pItem, original_pBuffer);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, &moo_pBuffer, bServer, bSaveItemInv, bGamble);
			const auto original_result = original(&original_pItem, &original_pBuffer, bServer, bSaveItemInv, bGamble);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA2FD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_WriteBitsToBitstream, dll_base + 0x00062FD0);
		
		SUBCASE("")
		{
			// Input data
			D2BitBufferStrc moo_pBuffer{};
			D2BitBufferStrc original_pBuffer{};
			int nData{};
			int nBits{};

			const auto setup_data = [](
				D2BitBufferStrc& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pBuffer);
			setup_data(original_pBuffer);

			// Call both implementations
			sut(&moo_pBuffer, nData, nBits);
			original(&original_pBuffer, nData, nBits);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA3010" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_SerializeItemComplete, dll_base + 0x00063010);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2BitBufferStrc moo_pBuffer{};
			D2UnitStrc original_pItem{};
			D2BitBufferStrc original_pBuffer{};
			BOOL bServer{};
			BOOL bGamble{};

			const auto setup_data = [](
				D2UnitStrc& pItem,
				D2BitBufferStrc& pBuffer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem, moo_pBuffer);
			setup_data(original_pItem, original_pBuffer);

			// Call both implementations
			sut(&moo_pItem, &moo_pBuffer, bServer, bGamble);
			original(&original_pItem, &original_pBuffer, bServer, bGamble);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pBuffer, original_pBuffer, "Comparing pBuffer");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA4380" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDA4380, dll_base + 0x00064380);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pItem{};
			unsigned int nSetItemMask{};

			const auto setup_data = [](
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pItem);
			setup_data(original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pItem, nSetItemMask);
			const auto original_result = original(&original_pItem, nSetItemMask);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA4490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDA4490, dll_base + 0x00064490);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			int a3{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pItem);
			setup_data(original_pUnit, original_pItem);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA4640 (#10866)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ITEMS_UpdateSets, dll_base + 0x00064640);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};
			int a3{};
			int a4{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pItem);
			setup_data(original_pUnit, original_pItem);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pItem, a3, a4);
			const auto original_result = original(&original_pUnit, &original_pItem, a3, a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
		}
	}
}
