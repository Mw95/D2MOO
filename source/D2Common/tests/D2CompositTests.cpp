#include <D2CommonTestDefines.h>

#ifdef COMPOSIT_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Composit.h>
#include <D2Monsters.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>

DYNAMIC_ARRAY_TYPE(char)
DYNAMIC_ARRAY_TYPE(uint8_t)


TEST_SUITE("D2CompositTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(MonModeTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FD466C0 (#10884)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10884_COMPOSIT_unk, dll_base + 0x000066C0);

		// TODO: UNIT_PLAYER and UNIT_OBJECT require PlrModeType/ObjModeType tables, for which no fixture exists yet
		SUBCASE("Monster")
		{
			const BOOL bAddPathPrefix = GENERATE(FALSE, TRUE);

			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < monmode_record_count; ++j)
				{
					CAPTURE(bAddPathPrefix);
					CAPTURE(i);
					CAPTURE(j);

					// Input data
					D2UnitStrc moo_pUnit{};
					D2InventoryStrc moo_pInventory{};
					char moo_szPath[MAX_PATH]{};
					int moo_pWeaponClassCode{};
					D2UnitStrc original_pUnit{};
					D2InventoryStrc original_pInventory{};
					char original_szPath[MAX_PATH]{};
					int original_pWeaponClassCode{};
					int nClass = i;
					int nMode = j;
					int nUnitType = UNIT_MONSTER;
					int a9 = TRUE;

					const auto setup_data = [i, j](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = j;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					sut(&moo_pUnit, nClass, nMode, nUnitType, &moo_pInventory, moo_szPath, &moo_pWeaponClassCode, bAddPathPrefix, a9);
					original(&original_pUnit, nClass, nMode, nUnitType, &original_pInventory, original_szPath, &original_pWeaponClassCode, bAddPathPrefix, a9);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
					MOO_CHECK_EQ((DynamicArray<char>{ moo_szPath, MAX_PATH }), (DynamicArray<char>{ original_szPath, MAX_PATH }), "Comparing szPath");
					MOO_CHECK_EQ(moo_pWeaponClassCode, original_pWeaponClassCode, "Comparing pWeaponClassCode");
				}
			}
		}

		SUBCASE("Unsupported unit types")
		{
			const int nUnitType = GENERATE(UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const BOOL bAddPathPrefix = GENERATE(FALSE, TRUE);

			// Input data
			D2UnitStrc moo_pUnit{};
			D2InventoryStrc moo_pInventory{};
			char moo_szPath[MAX_PATH]{};
			int moo_pWeaponClassCode{};
			D2UnitStrc original_pUnit{};
			D2InventoryStrc original_pInventory{};
			char original_szPath[MAX_PATH]{};
			int original_pWeaponClassCode{};
			int nClass{};
			int nMode{};
			int a9 = TRUE;

			const auto setup_data = [nUnitType](
				D2UnitStrc& pUnit,
				int& pWeaponClassCode
			) {
				pUnit.dwUnitType = nUnitType;
				pWeaponClassCode = ' hth';
			};

			setup_data(moo_pUnit, moo_pWeaponClassCode);
			setup_data(original_pUnit, original_pWeaponClassCode);

			// Call both implementations
			sut(&moo_pUnit, nClass, nMode, nUnitType, &moo_pInventory, moo_szPath, &moo_pWeaponClassCode, bAddPathPrefix, a9);
			original(&original_pUnit, nClass, nMode, nUnitType, &original_pInventory, original_szPath, &original_pWeaponClassCode, bAddPathPrefix, a9);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ((DynamicArray<char>{ moo_szPath, MAX_PATH }), (DynamicArray<char>{ original_szPath, MAX_PATH }), "Comparing szPath");
			MOO_CHECK_EQ(moo_pWeaponClassCode, original_pWeaponClassCode, "Comparing pWeaponClassCode");
		}
	}
	
	TEST_CASE_FIXTURE(MonModeTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FD46BC0 (#10885)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10885_COMPOSIT_unk, dll_base + 0x00006BC0);

		// TODO: UNIT_PLAYER and UNIT_OBJECT require PlrModeType/ObjModeType tables, for which no fixture exists yet
		SUBCASE("Monster")
		{
			const BOOL bAddPathPrefix = GENERATE(FALSE, TRUE);
			const auto use_unit_mode = GENERATE(0, 1);

			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < monmode_record_count; ++j)
				{
					CAPTURE(bAddPathPrefix);
					CAPTURE(use_unit_mode);
					CAPTURE(i);
					CAPTURE(j);

					// Input data
					D2UnitStrc moo_pUnit{};
					char moo_szPath[MAX_PATH]{};
					int moo_pWeaponClassCode{};
					D2InventoryStrc moo_pInventory{};
					D2UnitStrc original_pUnit{};
					char original_szPath[MAX_PATH]{};
					int original_pWeaponClassCode{};
					D2InventoryStrc original_pInventory{};
					int a5 = TRUE;
					int nAnimMode = use_unit_mode ? -1 : j;

					const auto setup_data = [i, j, use_unit_mode](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = use_unit_mode ? j : MONMODE_NEUTRAL;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					sut(&moo_pUnit, moo_szPath, &moo_pWeaponClassCode, bAddPathPrefix, a5, &moo_pInventory, nAnimMode);
					original(&original_pUnit, original_szPath, &original_pWeaponClassCode, bAddPathPrefix, a5, &original_pInventory, nAnimMode);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ((DynamicArray<char>{ moo_szPath, MAX_PATH }), (DynamicArray<char>{ original_szPath, MAX_PATH }), "Comparing szPath");
					MOO_CHECK_EQ(moo_pWeaponClassCode, original_pWeaponClassCode, "Comparing pWeaponClassCode");
					MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
				}
			}
		}

		SUBCASE("Unsupported unit types")
		{
			const int nUnitType = GENERATE(UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const BOOL bAddPathPrefix = GENERATE(FALSE, TRUE);

			// Input data
			D2UnitStrc moo_pUnit{};
			char moo_szPath[MAX_PATH]{};
			int moo_pWeaponClassCode{};
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc original_pUnit{};
			char original_szPath[MAX_PATH]{};
			int original_pWeaponClassCode{};
			D2InventoryStrc original_pInventory{};
			int a5 = TRUE;
			int nAnimMode = -1;

			const auto setup_data = [nUnitType](
				D2UnitStrc& pUnit,
				int& pWeaponClassCode
			) {
				pUnit.dwUnitType = nUnitType;
				pWeaponClassCode = ' hth';
			};

			setup_data(moo_pUnit, moo_pWeaponClassCode);
			setup_data(original_pUnit, original_pWeaponClassCode);

			// Call both implementations
			sut(&moo_pUnit, moo_szPath, &moo_pWeaponClassCode, bAddPathPrefix, a5, &moo_pInventory, nAnimMode);
			original(&original_pUnit, original_szPath, &original_pWeaponClassCode, bAddPathPrefix, a5, &original_pInventory, nAnimMode);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ((DynamicArray<char>{ moo_szPath, MAX_PATH }), (DynamicArray<char>{ original_szPath, MAX_PATH }), "Comparing szPath");
			MOO_CHECK_EQ(moo_pWeaponClassCode, original_pWeaponClassCode, "Comparing pWeaponClassCode");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD46C60 (#10886)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_GetWeaponClassIdFromCode, dll_base + 0x00006C60);
		
		SUBCASE("")
		{
			int nWeaponClassCode = GENERATE(' sh1', ' th1', ' wob', ' sh2', ' th2', ' sj1', ' tj1', ' ss1', ' ts1', ' fts', ' wbx', ' 1th', ' 2th', ' xxx');

			// Call both implementations
			const auto moo_result = sut(nWeaponClassCode);
			const auto original_result = original(nWeaponClassCode);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(CharStatsTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FD46C90 (#10887)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_GetWeaponClassCode, dll_base + 0x00006C90);

		SUBCASE("Player")
		{
			for (auto i = 0; i < charstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_PLRMODES; ++j)
				{
					CAPTURE(i);
					CAPTURE(j);

					// Input data
					D2UnitStrc moo_pUnit{};
					D2InventoryStrc moo_pInventory{};
					int moo_pWeaponClassId{};
					D2UnitStrc original_pUnit{};
					D2InventoryStrc original_pInventory{};
					int original_pWeaponClassId{};
					int nUnitType = UNIT_PLAYER;
					int nClass = i;
					int nMode = j;

					const auto setup_data = [i, j](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = j;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nUnitType, nClass, nMode, &moo_pInventory, &moo_pWeaponClassId);
					const auto original_result = original(&original_pUnit, nUnitType, nClass, nMode, &original_pInventory, &original_pWeaponClassId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
					MOO_CHECK_EQ(moo_pWeaponClassId, original_pWeaponClassId, "Comparing pWeaponClassId");
				}
			}
		}

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_MONMODES; ++j)
				{
					CAPTURE(i);
					CAPTURE(j);

					// Input data
					D2UnitStrc moo_pUnit{};
					D2InventoryStrc moo_pInventory{};
					int moo_pWeaponClassId{};
					D2UnitStrc original_pUnit{};
					D2InventoryStrc original_pInventory{};
					int original_pWeaponClassId{};
					int nUnitType = UNIT_MONSTER;
					int nClass = i;
					int nMode = j;

					const auto setup_data = [i, j](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = j;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nUnitType, nClass, nMode, &moo_pInventory, &moo_pWeaponClassId);
					const auto original_result = original(&original_pUnit, nUnitType, nClass, nMode, &original_pInventory, &original_pWeaponClassId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
					MOO_CHECK_EQ(moo_pWeaponClassId, original_pWeaponClassId, "Comparing pWeaponClassId");
				}
			}
		}

		SUBCASE("Other unit types")
		{
			const int nUnitType = GENERATE(UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			// Input data
			D2UnitStrc moo_pUnit{};
			D2InventoryStrc moo_pInventory{};
			int moo_pWeaponClassId{};
			D2UnitStrc original_pUnit{};
			D2InventoryStrc original_pInventory{};
			int original_pWeaponClassId{};
			int nClass{};
			int nMode{};

			const auto setup_data = [nUnitType](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = nUnitType;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nUnitType, nClass, nMode, &moo_pInventory, &moo_pWeaponClassId);
			const auto original_result = original(&original_pUnit, nUnitType, nClass, nMode, &original_pInventory, &original_pWeaponClassId);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pWeaponClassId, original_pWeaponClassId, "Comparing pWeaponClassId");
		}
	}
	
	TEST_CASE_FIXTURE(CharStatsTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FD47150 (#10888)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_GetWeaponClassId, dll_base + 0x00007150);

		const BOOL a5 = GENERATE(FALSE, TRUE);
		const auto use_unit_mode = GENERATE(0, 1);

		SUBCASE("Player")
		{
			for (auto i = 0; i < charstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_PLRMODES; ++j)
				{
					CAPTURE(a5);
					CAPTURE(use_unit_mode);
					CAPTURE(i);
					CAPTURE(j);

					// Input data
					D2UnitStrc moo_pUnit{};
					D2InventoryStrc moo_pInventory{};
					int moo_pWeaponClassId{};
					D2UnitStrc original_pUnit{};
					D2InventoryStrc original_pInventory{};
					int original_pWeaponClassId{};
					int nAnimMode = use_unit_mode ? -1 : j;

					const auto setup_data = [i, j, use_unit_mode](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = use_unit_mode ? j : PLRMODE_NEUTRAL;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, &moo_pInventory, &moo_pWeaponClassId, nAnimMode, a5);
					const auto original_result = original(&original_pUnit, &original_pInventory, &original_pWeaponClassId, nAnimMode, a5);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
					MOO_CHECK_EQ(moo_pWeaponClassId, original_pWeaponClassId, "Comparing pWeaponClassId");
				}
			}
		}

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_MONMODES; ++j)
				{
					CAPTURE(a5);
					CAPTURE(use_unit_mode);
					CAPTURE(i);
					CAPTURE(j);

					// Input data
					D2UnitStrc moo_pUnit{};
					D2InventoryStrc moo_pInventory{};
					int moo_pWeaponClassId{};
					D2UnitStrc original_pUnit{};
					D2InventoryStrc original_pInventory{};
					int original_pWeaponClassId{};
					int nAnimMode = use_unit_mode ? -1 : j;

					const auto setup_data = [i, j, use_unit_mode](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = use_unit_mode ? j : MONMODE_NEUTRAL;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, &moo_pInventory, &moo_pWeaponClassId, nAnimMode, a5);
					const auto original_result = original(&original_pUnit, &original_pInventory, &original_pWeaponClassId, nAnimMode, a5);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
					MOO_CHECK_EQ(moo_pWeaponClassId, original_pWeaponClassId, "Comparing pWeaponClassId");
				}
			}
		}

		SUBCASE("Other unit types")
		{
			const int nUnitType = GENERATE(UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			CAPTURE(a5);
			CAPTURE(use_unit_mode);

			// Input data
			D2UnitStrc moo_pUnit{};
			D2InventoryStrc moo_pInventory{};
			int moo_pWeaponClassId{};
			D2UnitStrc original_pUnit{};
			D2InventoryStrc original_pInventory{};
			int original_pWeaponClassId{};
			int nAnimMode = use_unit_mode ? -1 : 0;

			const auto setup_data = [nUnitType](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = nUnitType;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pInventory, &moo_pWeaponClassId, nAnimMode, a5);
			const auto original_result = original(&original_pUnit, &original_pInventory, &original_pWeaponClassId, nAnimMode, a5);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			MOO_CHECK_EQ(moo_pWeaponClassId, original_pWeaponClassId, "Comparing pWeaponClassId");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD47200 (#10889)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_IsArmorComponent, dll_base + 0x00007200);
		
		SUBCASE("")
		{
			for (auto i = 0; i < NUM_COMPONENTS; ++i)
			{
				int nComponent = i;

				// Call both implementations
				const auto moo_result = sut(nComponent);
				const auto original_result = original(nComponent);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(CharStatsTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FD47230 (#10890)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_IsWeaponBowOrXBow, dll_base + 0x00007230);

		SUBCASE("Player")
		{
			for (auto i = 0; i < charstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_PLRMODES; ++j)
				{
					CAPTURE(i);
					CAPTURE(j);

					// Input data
					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};

					const auto setup_data = [i, j](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = j;
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
		}

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_MONMODES; ++j)
				{
					CAPTURE(i);
					CAPTURE(j);

					// Input data
					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};

					const auto setup_data = [i, j](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = j;
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
		}

		SUBCASE("Other unit types")
		{
			const int nUnitType = GENERATE(UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [nUnitType](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = nUnitType;
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FD472E0 (#10891)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMPOSIT_GetArmorTypeFromComponent, dll_base + 0x000072E0);
		
		SUBCASE("")
		{
			// Input data
			uint8_t moo_pArmorComponents[8]{};
			uint8_t original_pArmorComponents[8]{};
			int nComponent = GENERATE(1, 2, 3, 4, 8, 9);

			const auto setup_data = [](
				uint8_t(&pArmorComponents)[8]
			) {
				for (auto i = 0; i < 8; ++i)
				{
					pArmorComponents[i] = i + 10;
				}
			};

			setup_data(moo_pArmorComponents);
			setup_data(original_pArmorComponents);

			// Call both implementations
			const auto moo_result = sut(nComponent, moo_pArmorComponents);
			const auto original_result = original(nComponent, original_pArmorComponents);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ((DynamicArray<uint8_t> { moo_pArmorComponents, 8 }), (DynamicArray<uint8_t> { original_pArmorComponents, 8 }), "Comparing pArmorComponents");
		}
	}
}

#endif
