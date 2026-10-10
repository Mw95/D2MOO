#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Skills.h>
#include <D2States.h>
#include <DataTbls/MonsterIds.h>
#include <DataTbls/ObjectsIds.h>
#include <DataTbls/ObjectsTbls.h>
#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Event.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


TEST_SUITE("UnitsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD520 (#10457)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetDirection, dll_base + 0x0007D520);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM);
			const auto direction = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [unit_type, direction](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.nDirection = direction;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto direction = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, direction](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.nDirection = direction;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD570 (#10320)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetStartSkill, dll_base + 0x0007D570);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pFirstSkill{};
			D2UnitStrc original_pUnit{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pFirstSkill{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pFirstSkill
			) {
				pUnit.pSkills = &pSkillList;
				pSkillList.pFirstSkill = &pFirstSkill;
				pFirstSkill.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pSkillList, moo_pFirstSkill);
			setup_data(original_pUnit, original_pSkillList, original_pFirstSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD5B0 (#10321)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetLeftSkill, dll_base + 0x0007D5B0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pLeftSkill{};
			D2UnitStrc original_pUnit{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pLeftSkill{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pLeftSkill
			) {
				pUnit.pSkills = &pSkillList;
				pSkillList.pLeftSkill = &pLeftSkill;
				pLeftSkill.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pSkillList, moo_pLeftSkill);
			setup_data(original_pUnit, original_pSkillList, original_pLeftSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD5F0 (#10322)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetRightSkill, dll_base + 0x0007D5F0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pRightSkill{};
			D2UnitStrc original_pUnit{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pRightSkill{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pRightSkill
			) {
				pUnit.pSkills = &pSkillList;
				pSkillList.pRightSkill = &pRightSkill;
				pRightSkill.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pSkillList, moo_pRightSkill);
			setup_data(original_pUnit, original_pSkillList, original_pRightSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD630 (#10324)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetUsedSkill, dll_base + 0x0007D630);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pUsedSkill{};
			D2UnitStrc original_pUnit{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pUsedSkill{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pUsedSkill
			) {
				pUnit.pSkills = &pSkillList;

				pUsedSkill.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pSkillList, moo_pUsedSkill);
			setup_data(original_pUnit, original_pSkillList, original_pUsedSkill);

			// Call both implementations
			sut(&moo_pUnit, &moo_pUsedSkill);
			original(&original_pUnit, &original_pUsedSkill);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pUsedSkill, original_pUsedSkill, "Comparing pUsedSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD670 (#10323)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetUsedSkill, dll_base + 0x0007D670);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pUsedSkill{};
			D2UnitStrc original_pUnit{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pUsedSkill{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pUsedSkill
			) {
				pUnit.pSkills = &pSkillList;
				pSkillList.pUsedSkill = &pUsedSkill;
				pUsedSkill.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pSkillList, moo_pUsedSkill);
			setup_data(original_pUnit, original_pSkillList, original_pUsedSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD6B0 (#11259)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_AllocUnit, dll_base + 0x0007D6B0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 6; ++i)
			{
				int nUnitType = i;

				// Call both implementations
				const auto moo_result = sut(nullptr, nUnitType);
				const auto original_result = original(nullptr, nUnitType);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD720 (#11260)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_FreeUnit, dll_base + 0x0007D720);
		const auto [moo_alloc, original_alloc] = make_function_pair(UNITS_AllocUnit, dll_base + 0x0007D6B0);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc* moo_pUnit = moo_alloc(nullptr, UNIT_PLAYER);
			D2UnitStrc* original_pUnit = original_alloc(nullptr, UNIT_PLAYER);

			// Call both implementations
			sut(moo_pUnit);
			original(original_pUnit);

			// Input data is freed, so we cannot compare it after the call
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD780 (#10327)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetPrecisionX, dll_base + 0x0007D780);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [unit_type, x](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, x](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.dwPrecisionX = x;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD7D0 (#10330)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetPrecisionY, dll_base + 0x0007D7D0);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [unit_type, y](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nY = y;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.dwPrecisionY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD820 (#10328)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetXForStaticUnit, dll_base + 0x0007D820);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			int nX = random_unsigned_integer(0, 65535);

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			sut(&moo_pUnit, nX);
			original(&original_pUnit, nX);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD890 (#10331)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetYForStaticUnit, dll_base + 0x0007D890);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			int nY = random_unsigned_integer(0, 65535);

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			sut(&moo_pUnit, nY);
			original(&original_pUnit, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<ObjectsTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>>, "D2Common.0x6FDBD900 (#10336)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetUnitSizeX, dll_base + 0x0007D900);
		
		SUBCASE("Player")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
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

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
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

		SUBCASE("Object")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.pObjectTxt = &objects_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Item")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_ITEM;
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

		SUBCASE("Missile")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MISSILE;
					pUnit.dwClassId = i;
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

		SUBCASE("Tile")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_TILE;
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
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<ObjectsTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>>, "D2Common.0x6FDBDA00 (#10337)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetUnitSizeY, dll_base + 0x0007DA00);
		
		SUBCASE("Player")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
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

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
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

		SUBCASE("Object")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.pObjectTxt = &objects_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Item")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_ITEM;
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

		SUBCASE("Missile")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MISSILE;
					pUnit.dwClassId = i;
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

		SUBCASE("Tile")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_TILE;
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDB10 (#10333)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetClientCoordX, dll_base + 0x0007DB10);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [unit_type, x](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.dwClientCoordX = x;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, x](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.dwClientCoordX = x;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDB60 (#10334)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetClientCoordY, dll_base + 0x0007DB60);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [unit_type, y](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.dwClientCoordY = y;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.dwClientCoordY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDBB0 (#10411)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetAbsoluteXDistance, dll_base + 0x0007DBB0);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto x1 = random_unsigned_integer(0, 65535);
			const auto x2 = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit1{};
			D2StaticPathStrc moo_pStaticPath1{};
			D2UnitStrc moo_pUnit2{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2UnitStrc original_pUnit1{};
			D2StaticPathStrc original_pStaticPath1{};
			D2UnitStrc original_pUnit2{};
			D2StaticPathStrc original_pStaticPath2{};

			const auto setup_data = [x1, x2](
				D2UnitStrc& pUnit1,
				D2StaticPathStrc& pStaticPath1,
				D2UnitStrc& pUnit2,
				D2StaticPathStrc& pStaticPath2
			) {
				pUnit1.dwUnitType = UNIT_OBJECT;
				pUnit1.pStaticPath = &pStaticPath1;
				pStaticPath1.tGameCoords.nX = x1;

				pUnit2.dwUnitType = UNIT_OBJECT;
				pUnit2.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
			};

			setup_data(moo_pUnit1, moo_pStaticPath1, moo_pUnit2, moo_pStaticPath2);
			setup_data(original_pUnit1, original_pStaticPath1, original_pUnit2, original_pStaticPath2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto x1 = random_unsigned_integer(0, 65535);
			const auto x2 = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2DynamicPathStrc original_pDynamicPath2{};

			const auto setup_data = [x1, x2](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2DynamicPathStrc& pDynamicPath2
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;

				pUnit2.dwUnitType = UNIT_PLAYER;
				pUnit2.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosX = x2;
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDC20 (#10412)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetAbsoluteYDistance, dll_base + 0x0007DC20);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto y1 = random_unsigned_integer(0, 65535);
			const auto y2 = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit1{};
			D2StaticPathStrc moo_pStaticPath1{};
			D2UnitStrc moo_pUnit2{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2UnitStrc original_pUnit1{};
			D2StaticPathStrc original_pStaticPath1{};
			D2UnitStrc original_pUnit2{};
			D2StaticPathStrc original_pStaticPath2{};

			const auto setup_data = [y1, y2](
				D2UnitStrc& pUnit1,
				D2StaticPathStrc& pStaticPath1,
				D2UnitStrc& pUnit2,
				D2StaticPathStrc& pStaticPath2
			) {
				pUnit1.dwUnitType = UNIT_OBJECT;
				pUnit1.pStaticPath = &pStaticPath1;
				pStaticPath1.tGameCoords.nY = y1;

				pUnit2.dwUnitType = UNIT_OBJECT;
				pUnit2.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nY = y2;
			};

			setup_data(moo_pUnit1, moo_pStaticPath1, moo_pUnit2, moo_pStaticPath2);
			setup_data(original_pUnit1, original_pStaticPath1, original_pUnit2, original_pStaticPath2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto y1 = random_unsigned_integer(0, 65535);
			const auto y2 = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2DynamicPathStrc original_pDynamicPath2{};

			const auto setup_data = [y1, y2](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2DynamicPathStrc& pDynamicPath2
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosY = y1;
									
				pUnit2.dwUnitType = UNIT_PLAYER;
				pUnit2.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosY = y2;
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDC90 (#10340)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetTargetX, dll_base + 0x0007DC90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nTargetX = random_unsigned_integer(0, 65535);

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			sut(&moo_pUnit, nTargetX);
			original(&original_pUnit, nTargetX);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDCD0 (#10341)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetTargetY, dll_base + 0x0007DCD0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nTargetY = random_unsigned_integer(0, 65535);

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			sut(&moo_pUnit, nTargetY);
			original(&original_pUnit, nTargetY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDD10 (#10332)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetCoords, dll_base + 0x0007DD10);

		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2CoordStrc moo_pCoord{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2CoordStrc original_pCoord{};

			const auto setup_data = [unit_type, x, y](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2CoordStrc& pClientCoords
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
				pStaticPath.tGameCoords.nY = y;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pCoord);
			setup_data(original_pUnit, original_pStaticPath, original_pCoord);

			// Call both implementations
			sut(&moo_pUnit, &moo_pCoord);
			original(&original_pUnit, &original_pCoord);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2CoordStrc moo_pCoord{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2CoordStrc original_pCoord{};

			const auto setup_data = [unit_type, x, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2CoordStrc& pCoord
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pCoord);
			setup_data(original_pUnit, original_pDynamicPath, original_pCoord);

			// Call both implementations
			sut(&moo_pUnit, &moo_pCoord);
			original(&original_pUnit, &original_pCoord);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDDA0 (#10335)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetClientCoords, dll_base + 0x0007DDA0);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2CoordStrc moo_pClientCoords{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2CoordStrc original_pClientCoords{};

			const auto setup_data = [unit_type, x, y](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2CoordStrc& pClientCoords
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.dwClientCoordX = x;
				pStaticPath.dwClientCoordY = y;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pClientCoords);
			setup_data(original_pUnit, original_pStaticPath, original_pClientCoords);

			// Call both implementations
			sut(&moo_pUnit, &moo_pClientCoords);
			original(&original_pUnit, &original_pClientCoords);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pClientCoords, original_pClientCoords, "Comparing pClientCoords");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2CoordStrc moo_pClientCoords{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2CoordStrc original_pClientCoords{};

			const auto setup_data = [unit_type, x, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2CoordStrc& pClientCoords
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.dwClientCoordX = x;
				pDynamicPath.dwClientCoordY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pClientCoords);
			setup_data(original_pUnit, original_pDynamicPath, original_pClientCoords);

			// Call both implementations
			sut(&moo_pUnit, &moo_pClientCoords);
			original(&original_pUnit, &original_pClientCoords);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pClientCoords, original_pClientCoords, "Comparing pClientCoords");
		}
	}
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDBDE10 (#10338)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetCollisionMask, dll_base + 0x0007DE10);
		
		SUBCASE("Object")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.pObjectTxt = &objects_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Item")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_ITEM;
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

		SUBCASE("Tile")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_TILE;
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

		SUBCASE("Dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto collision_mask = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, collision_mask](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.nFootprintCollisionMask = collision_mask;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDEC0 (#10352)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_FreeCollisionPath, dll_base + 0x0007DEC0);

		REPEAT_10();

		constexpr int room_size = 32;

		// The unit is placed far enough from the room borders so that its footprint always fits into the room
		const auto room_x = random_unsigned_integer(0, 10000);
		const auto room_y = random_unsigned_integer(0, 10000);
		const auto x = room_x + random_unsigned_integer(8, room_size - 8);
		const auto y = room_y + random_unsigned_integer(8, room_size - 8);

		uint16_t collision_mask[room_size * room_size]{};
		for (auto& mask : collision_mask)
		{
			mask = random_unsigned_integer(0, 0xFFFF);
		}

		SUBCASE("Player")
		{
			// Input data
			const auto footprint_collision_mask = random_unsigned_integer(0, 0xFFFF);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};

			const auto setup_data = [room_size, room_x, room_y, x, y, footprint_collision_mask, &collision_mask](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
				pDynamicPath.pRoom = &pRoom;
				pDynamicPath.nFootprintCollisionMask = footprint_collision_mask;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			for (auto i = 0; i < room_size * room_size; ++i)
			{
				MOO_CHECK_EQ(moo_pCollisionMask[i], original_pCollisionMask[i], "Comparing pCollisionMask");
			}
		}

		SUBCASE("Object")
		{
			// Input data
			const auto size_x = random_unsigned_integer(0, 8);
			const auto size_y = random_unsigned_integer(0, 8);
			const auto is_door = random_unsigned_integer(0, 1);
			const auto blocks_vis = random_unsigned_integer(0, 1);
			const auto block_missile = random_unsigned_integer(0, 1);
			const auto sub_class = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ObjectDataStrc moo_pObjectData{};
			D2ObjectsTxt moo_pObjectsTxtRecord{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ObjectDataStrc original_pObjectData{};
			D2ObjectsTxt original_pObjectsTxtRecord{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};

			const auto setup_data = [room_size, room_x, room_y, x, y, size_x, size_y, is_door, blocks_vis, block_missile, sub_class, &collision_mask](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ObjectDataStrc& pObjectData,
				D2ObjectsTxt& pObjectsTxtRecord,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit.dwUnitType = UNIT_OBJECT;
				pUnit.pStaticPath = &pStaticPath;
				pUnit.pObjectData = &pObjectData;
				pObjectData.pObjectTxt = &pObjectsTxtRecord;
				pObjectsTxtRecord.dwSizeX = size_x;
				pObjectsTxtRecord.dwSizeY = size_y;
				pObjectsTxtRecord.nIsDoor = is_door;
				pObjectsTxtRecord.nBlocksVis = blocks_vis;
				pObjectsTxtRecord.nBlockMissile = block_missile;
				pObjectsTxtRecord.nSubClass = sub_class;
				pStaticPath.tGameCoords.nX = x;
				pStaticPath.tGameCoords.nY = y;
				pStaticPath.pRoom = &pRoom;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pObjectData, moo_pObjectsTxtRecord, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit, original_pStaticPath, original_pObjectData, original_pObjectsTxtRecord, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			for (auto i = 0; i < room_size * room_size; ++i)
			{
				MOO_CHECK_EQ(moo_pCollisionMask[i], original_pCollisionMask[i], "Comparing pCollisionMask");
			}
		}

		SUBCASE("Item")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};

			const auto setup_data = [room_size, room_x, room_y, x, y, &collision_mask](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit.dwUnitType = UNIT_ITEM;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
				pStaticPath.tGameCoords.nY = y;
				pStaticPath.pRoom = &pRoom;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit, original_pStaticPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			for (auto i = 0; i < room_size * room_size; ++i)
			{
				MOO_CHECK_EQ(moo_pCollisionMask[i], original_pCollisionMask[i], "Comparing pCollisionMask");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE060 (#10351)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_BlockCollisionPath, dll_base + 0x0007E060);

		REPEAT_10();

		constexpr int room_size = 32;

		// The collision is placed far enough from the room borders so that the footprint always fits into the room
		const auto room_x = random_unsigned_integer(0, 10000);
		const auto room_y = random_unsigned_integer(0, 10000);
		int nX = room_x + random_unsigned_integer(8, room_size - 8);
		int nY = room_y + random_unsigned_integer(8, room_size - 8);

		uint16_t collision_mask[room_size * room_size]{};
		for (auto& mask : collision_mask)
		{
			mask = random_unsigned_integer(0, 0xFFFF);
		}

		SUBCASE("Player")
		{
			// Input data
			const auto footprint_collision_mask = random_unsigned_integer(0, 0xFFFF);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};

			const auto setup_data = [room_size, room_x, room_y, footprint_collision_mask, &collision_mask](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.nFootprintCollisionMask = footprint_collision_mask;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			sut(&moo_pUnit, &moo_pRoom, nX, nY);
			original(&original_pUnit, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			for (auto i = 0; i < room_size * room_size; ++i)
			{
				MOO_CHECK_EQ(moo_pCollisionMask[i], original_pCollisionMask[i], "Comparing pCollisionMask");
			}
		}

		SUBCASE("Object")
		{
			// Input data
			const auto size_x = random_unsigned_integer(0, 8);
			const auto size_y = random_unsigned_integer(0, 8);
			const auto is_door = random_unsigned_integer(0, 1);
			const auto blocks_vis = random_unsigned_integer(0, 1);
			const auto block_missile = random_unsigned_integer(0, 1);
			const auto sub_class = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2ObjectDataStrc moo_pObjectData{};
			D2ObjectsTxt moo_pObjectsTxtRecord{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit{};
			D2ObjectDataStrc original_pObjectData{};
			D2ObjectsTxt original_pObjectsTxtRecord{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};

			const auto setup_data = [room_size, room_x, room_y, size_x, size_y, is_door, blocks_vis, block_missile, sub_class, &collision_mask](
				D2UnitStrc& pUnit,
				D2ObjectDataStrc& pObjectData,
				D2ObjectsTxt& pObjectsTxtRecord,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit.dwUnitType = UNIT_OBJECT;
				pUnit.pObjectData = &pObjectData;
				pObjectData.pObjectTxt = &pObjectsTxtRecord;
				pObjectsTxtRecord.dwSizeX = size_x;
				pObjectsTxtRecord.dwSizeY = size_y;
				pObjectsTxtRecord.nIsDoor = is_door;
				pObjectsTxtRecord.nBlocksVis = blocks_vis;
				pObjectsTxtRecord.nBlockMissile = block_missile;
				pObjectsTxtRecord.nSubClass = sub_class;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit, moo_pObjectData, moo_pObjectsTxtRecord, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit, original_pObjectData, original_pObjectsTxtRecord, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			sut(&moo_pUnit, &moo_pRoom, nX, nY);
			original(&original_pUnit, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			for (auto i = 0; i < room_size * room_size; ++i)
			{
				MOO_CHECK_EQ(moo_pCollisionMask[i], original_pCollisionMask[i], "Comparing pCollisionMask");
			}
		}

		SUBCASE("Item")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};

			const auto setup_data = [room_size, room_x, room_y, &collision_mask](
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit.dwUnitType = UNIT_ITEM;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			sut(&moo_pUnit, &moo_pRoom, nX, nY);
			original(&original_pUnit, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");

			for (auto i = 0; i < room_size * room_size; ++i)
			{
				MOO_CHECK_EQ(moo_pCollisionMask[i], original_pCollisionMask[i], "Comparing pCollisionMask");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE1A0 (#10350)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_InitializeStaticPath, dll_base + 0x0007E1A0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ActiveRoomStrc original_pRoom{};
			int nX = random_unsigned_integer(0, 65535);
			int nY = random_unsigned_integer(0, 65535);

			const auto setup_data = [unit_type, flags](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pRoom.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pRoom);
			setup_data(original_pUnit, original_pStaticPath, original_pRoom);

			// Call both implementations
			sut(&moo_pUnit, &moo_pRoom, nX, nY);
			original(&original_pUnit, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE210 (#10343)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_ResetRoom, dll_base + 0x0007E210);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [unit_type, flags](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.pRoom = &pRoom;
				pRoom.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pRoom);
			setup_data(original_pUnit, original_pStaticPath, original_pRoom);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [unit_type, flags](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;
				pRoom.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE270 (#10342)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetRoom, dll_base + 0x0007E270);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [unit_type, flags](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.pRoom = &pRoom;
				pRoom.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pRoom);
			setup_data(original_pUnit, original_pStaticPath, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};

			const auto setup_data = [unit_type, flags](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;
				pRoom.dwFlags = flags;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE2D0 (#10344)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetTargetUnitForDynamicUnit, dll_base + 0x0007E2D0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto target_type = random_unsigned_integer();
			const auto target_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pTargetUnit{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pTargetUnit{};

			const auto setup_data = [unit_type, target_type, target_id](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pTargetUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pTargetUnit.dwUnitType = target_type;
				pTargetUnit.dwUnitId = target_id;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pTargetUnit);
			setup_data(original_pUnit, original_pDynamicPath, original_pTargetUnit);

			// Call both implementations
			sut(&moo_pUnit, &moo_pTargetUnit);
			original(&original_pUnit, &original_pTargetUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE330 (#10345)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetTargetTypeFromDynamicUnit, dll_base + 0x0007E330);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto target_type = random_unsigned_integer();
			const auto target_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pTargetUnit{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pTargetUnit{};

			const auto setup_data = [unit_type, target_type, target_id](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pTargetUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pTargetUnit = &pTargetUnit;
				pTargetUnit.dwUnitType = target_type;
				pTargetUnit.dwUnitId = target_id;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pTargetUnit);
			setup_data(original_pUnit, original_pDynamicPath, original_pTargetUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE3A0 (#10346)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetTargetGUIDFromDynamicUnit, dll_base + 0x0007E3A0);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto target_type = random_unsigned_integer();
			const auto target_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pTargetUnit{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pTargetUnit{};

			const auto setup_data = [unit_type, target_type, target_id](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pTargetUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pTargetUnit = &pTargetUnit;
				pTargetUnit.dwUnitType = target_type;
				pTargetUnit.dwUnitId = target_id;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pTargetUnit);
			setup_data(original_pUnit, original_pDynamicPath, original_pTargetUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE410 (#10347)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetTargetUnitForPlayerOrMonster, dll_base + 0x0007E410);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);
			const auto target_type = random_unsigned_integer();
			const auto target_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc moo_pTargetUnit{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2UnitStrc original_pTargetUnit{};

			const auto setup_data = [unit_type, target_type, target_id](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2UnitStrc& pTargetUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pTargetUnit.dwUnitType = target_type;
				pTargetUnit.dwUnitId = target_id;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pTargetUnit);
			setup_data(original_pUnit, original_pDynamicPath, original_pTargetUnit);

			// Call both implementations
			sut(&moo_pUnit, &moo_pTargetUnit);
			original(&original_pUnit, &original_pTargetUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(CharStatsTxtFixture<NoopFixture>, "D2Common.0x6FDBE470 (#10354)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetRunAndWalkSpeedForPlayer, dll_base + 0x0007E470);
		
		SUBCASE("")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				// Input data
				int moo_pWalkSpeed{};
				int moo_pRunSpeed{};
				int original_pWalkSpeed{};
				int original_pRunSpeed{};
				int nUnused{};
				int nCharId = i;

				// Call both implementations
				sut(nUnused, nCharId, &moo_pWalkSpeed, &moo_pRunSpeed);
				original(nUnused, nCharId, &original_pWalkSpeed, &original_pRunSpeed);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pWalkSpeed, original_pWalkSpeed, "Comparing pWalkSpeed");
				MOO_CHECK_EQ(moo_pRunSpeed, original_pRunSpeed, "Comparing pRunSpeed");
			}
		}
	}
	
	TEST_CASE_FIXTURE(AnimDataFixture<MonModeTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>>, "D2Common.0x6FDBE4C0 (#10325)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimData, dll_base + 0x0007E4C0);

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				int nUnitType = UNIT_MONSTER;
				int nClassId = i;
				int nMode = random_unsigned_integer(0, monmode_record_count - 1);

				const auto setup_data = [](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
				};

				setup_data(moo_pUnit);
				setup_data(original_pUnit);

				// Call both implementations
				sut(&moo_pUnit, nUnitType, nClassId, nMode);
				original(&original_pUnit, nUnitType, nClassId, nMode);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				// The anim data records are part of the data tables, so both implementations have to use the same record
				CHECK_EQ(moo_pUnit.pAnimData, original_pUnit.pAnimData);
			}
		}

		SUBCASE("Other")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_ITEM, UNIT_MISSILE, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nUnitType = unit_type;
			int nClassId = random_unsigned_integer(0, 255);
			int nMode = random_unsigned_integer(0, 255);

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nUnitType, nClassId, nMode);
			original(&original_pUnit, nUnitType, nClassId, nMode);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			// The anim data records are part of the data tables, so both implementations have to use the same record
			CHECK_EQ(moo_pUnit.pAnimData, original_pUnit.pAnimData);
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<ObjectsTxtFixture<NoopFixture>>, "D2Common.0x6FDBE510 (#10349)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimStartFrame, dll_base + 0x0007E510);

		SUBCASE("Item")
		{
			// Input data
			const auto item_mode = GENERATE(IMODE_STORED, IMODE_EQUIP, IMODE_INBELT, IMODE_ONGROUND, IMODE_ONCURSOR, IMODE_DROPPING, IMODE_SOCKETED);
			const auto action_frame = random_unsigned_integer(0, 255);
			const auto anim_speed = random_unsigned_integer(0, 0x7FFF);
			const auto frame_count = random_unsigned_integer();
			const auto current_frame = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [item_mode, action_frame, anim_speed, frame_count, current_frame](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_ITEM;
				pUnit.dwItemMode = item_mode;
				pUnit.nActionFrame = action_frame;
				pUnit.wAnimSpeed = anim_speed;
				pUnit.dwFrameCountPrecise = frame_count;
				pUnit.nSeqCurrentFramePrecise = current_frame;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Missile")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				// Input data
				const auto action_frame = random_unsigned_integer(0, 255);

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i, action_frame](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MISSILE;
					pUnit.dwClassId = i;
					pUnit.nActionFrame = action_frame;
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

		SUBCASE("Object")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				const auto anim_mode = random_unsigned_integer(0, 7);
				const auto action_frame = random_unsigned_integer(0, 255);
				const auto low_seed = random_unsigned_integer();
				const auto high_seed = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i, anim_mode, action_frame, low_seed, high_seed](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.dwClassId = i;
					pUnit.dwAnimMode = anim_mode;
					pUnit.nActionFrame = action_frame;
					pUnit.pSeed.nLowSeed = low_seed;
					pUnit.pSeed.nHighSeed = high_seed;
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
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEA60 (#10348)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_ChangeAnimMode, dll_base + 0x0007EA60);

		SUBCASE("Tile")
		{
			// Input data
			const auto anim_mode = random_unsigned_integer();
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nMode = random_unsigned_integer();

			const auto setup_data = [anim_mode, flags](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_TILE;
				pUnit.dwAnimMode = anim_mode;
				pUnit.dwFlags = flags;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nMode);
			const auto original_result = original(&original_pUnit, nMode);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Neutral monster")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nMode = MONMODE_NEUTRAL;

			const auto setup_data = [flags](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.dwAnimMode = MONMODE_NEUTRAL;
				pUnit.dwFlags = flags;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nMode);
			const auto original_result = original(&original_pUnit, nMode);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Item with unchanged mode")
		{
			// Input data
			const auto item_mode = GENERATE(IMODE_STORED, IMODE_EQUIP, IMODE_INBELT, IMODE_ONGROUND, IMODE_ONCURSOR, IMODE_DROPPING, IMODE_SOCKETED);
			const auto flags = random_unsigned_integer();
			const auto room_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};
			int nMode = item_mode;

			const auto setup_data = [item_mode, flags, room_flags](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pUnit.dwUnitType = UNIT_ITEM;
				pUnit.dwItemMode = item_mode;
				pUnit.dwFlags = flags;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.pRoom = &pRoom;
				pRoom.dwFlags = room_flags;
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pRoom, moo_pAct);
			setup_data(original_pUnit, original_pStaticPath, original_pRoom, original_pAct);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nMode);
			const auto original_result = original(&original_pUnit, nMode);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Item with changed mode")
		{
			// Input data
			const auto item_mode = GENERATE(IMODE_STORED, IMODE_EQUIP, IMODE_INBELT, IMODE_ONGROUND, IMODE_ONCURSOR, IMODE_DROPPING, IMODE_SOCKETED);
			const auto previous_item_mode = (item_mode + random_unsigned_integer(1, 6)) % 7;
			const auto flags = random_unsigned_integer();
			const auto room_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};
			int nMode = item_mode;

			const auto setup_data = [previous_item_mode, flags, room_flags](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pUnit.dwUnitType = UNIT_ITEM;
				pUnit.dwItemMode = previous_item_mode;
				pUnit.dwFlags = flags;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.pRoom = &pRoom;
				pRoom.dwFlags = room_flags;
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pRoom, moo_pAct);
			setup_data(original_pUnit, original_pStaticPath, original_pRoom, original_pAct);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nMode);
			const auto original_result = original(&original_pUnit, nMode);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEAD0 (#10355)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsCurrentRoomInvalid, dll_base + 0x0007EAD0);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM);
			const auto needs_update = GENERATE(0, 1);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};

			const auto setup_data = [unit_type, needs_update](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.bRoomNeedsUpdate = needs_update;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto needs_update = GENERATE(0, 1);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, needs_update](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				if (needs_update)
				{
					pDynamicPath.dwFlags |= PATH_CURRENT_ROOM_INVALID;
				}
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEB20 (#10356)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetCurrentRoomInvalid, dll_base + 0x0007EB20);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM);
			const auto needs_update = GENERATE(0, 1);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			int a2 = needs_update;

			const auto setup_data = [unit_type, needs_update](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			sut(&moo_pUnit, a2);
			original(&original_pUnit, a2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto needs_update = GENERATE(0, 1);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int a2 = needs_update;

			const auto setup_data = [unit_type, needs_update](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			sut(&moo_pUnit, a2);
			original(&original_pUnit, a2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEB80 (#10357)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_RefreshInventory, dll_base + 0x0007EB80);

		SUBCASE("bSetFlag = FALSE")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto flags_ex = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL bSetFlag = FALSE;

			const auto setup_data = [unit_type, flags_ex](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFlagEx = flags_ex;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, bSetFlag);
			original(&original_pUnit, bSetFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("bSetFlag = TRUE, dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto flags = random_unsigned_integer();
			const auto flags_ex = random_unsigned_integer();
			const auto room_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};
			BOOL bSetFlag = TRUE;

			const auto setup_data = [unit_type, flags, flags_ex, room_flags](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFlags = flags;
				pUnit.dwFlagEx = flags_ex;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;
				pRoom.dwFlags = room_flags;
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom, moo_pAct);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom, original_pAct);

			// Call both implementations
			sut(&moo_pUnit, bSetFlag);
			original(&original_pUnit, bSetFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("bSetFlag = TRUE, static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto flags = random_unsigned_integer();
			const auto flags_ex = random_unsigned_integer();
			const auto room_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};
			BOOL bSetFlag = TRUE;

			const auto setup_data = [unit_type, flags, flags_ex, room_flags](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFlags = flags;
				pUnit.dwFlagEx = flags_ex;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.pRoom = &pRoom;
				pRoom.dwFlags = room_flags;
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pRoom, moo_pAct);
			setup_data(original_pUnit, original_pStaticPath, original_pRoom, original_pAct);

			// Call both implementations
			sut(&moo_pUnit, bSetFlag);
			original(&original_pUnit, bSetFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEBE0 (#10409)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetInventoryRecordId, dll_base + 0x0007EBE0);
		
		SUBCASE("Player")
		{
			const auto expansion = GENERATE(0, 1);

			for (auto j = 0; j < NUMBER_OF_PLAYERCLASSES; ++j)
			{
				for (auto i = 0; i < 6; ++i)
				{
					// Input data
					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};
					int nInvPage = i;
					BOOL bLoD = expansion;

					const auto setup_data = [j](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = j;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nInvPage, bLoD);
					const auto original_result = original(&original_pUnit, nInvPage, bLoD);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				}
			}
		}

		SUBCASE("Monster")
		{
			const auto expansion = GENERATE(0, 1);

			for (auto i = 0; i < 6; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				int nInvPage = i;
				BOOL bLoD = expansion;

				const auto setup_data = [](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
				};

				setup_data(moo_pUnit);
				setup_data(original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nInvPage, bLoD);
				const auto original_result = original(&original_pUnit, nInvPage, bLoD);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Object")
		{
			const auto expansion = GENERATE(0, 1);
			const auto class_id = GENERATE(OBJECT_GUILD_VAULT, OBJECT_TROPHY_CASE);

			for (auto i = 0; i < 6; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};
				int nInvPage = i;
				BOOL bLoD = expansion;

				const auto setup_data = [class_id](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = class_id;
				};

				setup_data(moo_pUnit);
				setup_data(original_pUnit);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nInvPage, bLoD);
				const auto original_result = original(&original_pUnit, nInvPage, bLoD);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBECD0 (#10383)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_ResetLightMap, dll_base + 0x0007ECD0);
		
		SUBCASE("")
		{
			// Input data
			const auto light = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [light](
				D2UnitStrc& pUnit
			) {
				pUnit.pLight = (D2GfxLightStrc*)light;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = (int)sut(&moo_pUnit);
			const auto original_result = (int)original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBED10 (#10369)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetAnimOrSeqMode, dll_base + 0x0007ED10);
		
		SUBCASE("With anim sequence")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto anim_mode = random_unsigned_integer();
			const auto seq_mode = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2AnimSeqTxt moo_pAnimSeq{};
			D2UnitStrc original_pUnit{};
			D2AnimSeqTxt original_pAnimSeq{};

			const auto setup_data = [unit_type, anim_mode, seq_mode](
				D2UnitStrc& pUnit,
				D2AnimSeqTxt& pAnimSeq
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwAnimMode = anim_mode;
				pUnit.dwSeqMode = seq_mode;
				pUnit.pAnimSeq = &pAnimSeq;
			};

			setup_data(moo_pUnit, moo_pAnimSeq);
			setup_data(original_pUnit, original_pAnimSeq);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without anim sequence")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto anim_mode = random_unsigned_integer();
			const auto seq_mode = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type, anim_mode, seq_mode](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwAnimMode = anim_mode;
				pUnit.dwSeqMode = seq_mode;
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

		SUBCASE("nullptr")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBED40 (#10370)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimOrSeqMode, dll_base + 0x0007ED40);
		
		SUBCASE("With anim sequence")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto anim_mode = random_unsigned_integer();
			const auto seq_mode = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2AnimSeqTxt moo_pAnimSeq{};
			D2UnitStrc original_pUnit{};
			D2AnimSeqTxt original_pAnimSeq{};
			int nAnimMode = random_unsigned_integer();

			const auto setup_data = [unit_type, anim_mode, seq_mode](
				D2UnitStrc& pUnit,
				D2AnimSeqTxt& pAnimSeq
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwAnimMode = anim_mode;
				pUnit.dwSeqMode = seq_mode;
				pUnit.pAnimSeq = &pAnimSeq;
			};

			setup_data(moo_pUnit, moo_pAnimSeq);
			setup_data(original_pUnit, original_pAnimSeq);

			// Call both implementations
			sut(&moo_pUnit, nAnimMode);
			original(&original_pUnit, nAnimMode);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without anim sequence")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto anim_mode = random_unsigned_integer();
			const auto seq_mode = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nAnimMode = random_unsigned_integer();

			const auto setup_data = [unit_type, anim_mode, seq_mode](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwAnimMode = anim_mode;
				pUnit.dwSeqMode = seq_mode;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nAnimMode);
			original(&original_pUnit, nAnimMode);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(CharStatsTxtFixture<NoopFixture>, "D2Common.0x6FDBED90 (#10371)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_InitializeSequence, dll_base + 0x0007ED90);
		
		SUBCASE("Player with sequence skill")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				// The player sequence table contains 24 entries, the first one is unused
				for (auto j = 1; j < 24; ++j)
				{
					// Input data
					const auto flags = random_unsigned_integer();
					const auto action_frame = random_unsigned_integer(0, 255);

					D2UnitStrc moo_pUnit{};
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pUsedSkill{};
					D2SkillsTxt moo_pSkillsTxtRecord{};
					D2UnitStrc original_pUnit{};
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pUsedSkill{};
					D2SkillsTxt original_pSkillsTxtRecord{};

					const auto setup_data = [i, j, flags, action_frame](
						D2UnitStrc& pUnit,
						D2SkillListStrc& pSkillList,
						D2SkillStrc& pUsedSkill,
						D2SkillsTxt& pSkillsTxtRecord
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = i;
						pUnit.dwFlags = flags;
						pUnit.nActionFrame = action_frame;
						pUnit.pSkills = &pSkillList;
						pSkillList.pUsedSkill = &pUsedSkill;
						pUsedSkill.pSkillsTxt = &pSkillsTxtRecord;
						pSkillsTxtRecord.nSeqNum = j;
					};

					setup_data(moo_pUnit, moo_pSkillList, moo_pUsedSkill, moo_pSkillsTxtRecord);
					setup_data(original_pUnit, original_pSkillList, original_pUsedSkill, original_pSkillsTxtRecord);

					// Call both implementations
					sut(&moo_pUnit);
					original(&original_pUnit);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

					// The sequences are static data of the respective DLL, so only check whether a sequence was found by both implementations
					CHECK_EQ(moo_pUnit.pAnimSeq == nullptr, original_pUnit.pAnimSeq == nullptr);
				}
			}
		}

		SUBCASE("No used skill")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto flags = random_unsigned_integer();
			const auto action_frame = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type, flags, action_frame](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFlags = flags;
				pUnit.nActionFrame = action_frame;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			CHECK_EQ(moo_pUnit.pAnimSeq, original_pUnit.pAnimSeq);
		}

		SUBCASE("nullptr")
		{
			// Call both implementations
			sut(nullptr);
			original(nullptr);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEE20 (#10372)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimationFrame, dll_base + 0x0007EE20);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			const auto seq_frame = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nFrame = random_unsigned_integer(0, 255);

			const auto setup_data = [seq_frame](
				D2UnitStrc& pUnit
			) {
				pUnit.dwSeqFrame = seq_frame;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nFrame);
			original(&original_pUnit, nFrame);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEE60 (#10373)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StopSequence, dll_base + 0x0007EE60);

		REPEAT_10();
		
		SUBCASE("With anim sequence")
		{
			constexpr int sequence_length = 16;

			// Input data
			D2AnimSeqTxt anim_seq[sequence_length]{};
			for (auto& anim_seq_record : anim_seq)
			{
				anim_seq_record.nMode = random_unsigned_integer(0, 255);
				anim_seq_record.nFrame = random_unsigned_integer(0, 255);
				anim_seq_record.nDir = random_unsigned_integer(0, 255);
				anim_seq_record.nEvent = static_cast<D2AnimSeqEvent>(random_unsigned_integer(0, 4));
			}

			// The new sequence frame has to stay within the sequence, even after wrapping around
			const auto seq_frame_count = sequence_length << 8;
			const auto seq_frame = random_unsigned_integer(0, seq_frame_count - 1);
			const auto seq_speed = random_unsigned_integer(0, seq_frame_count);
			const auto seq_mode = random_unsigned_integer(0, 255);
			const auto frame_count = random_unsigned_integer();
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2AnimSeqTxt moo_pAnimSeq[sequence_length]{};
			D2UnitStrc original_pUnit{};
			D2AnimSeqTxt original_pAnimSeq[sequence_length]{};

			const auto setup_data = [&anim_seq, seq_frame_count, seq_frame, seq_speed, seq_mode, frame_count, flags](
				D2UnitStrc& pUnit,
				D2AnimSeqTxt(&pAnimSeq)[sequence_length]
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.dwFlags = flags;
				pUnit.pAnimSeq = pAnimSeq;
				pUnit.dwSeqFrameCount = seq_frame_count;
				pUnit.dwSeqFrame = seq_frame;
				pUnit.dwSeqSpeed = seq_speed;
				pUnit.dwSeqMode = seq_mode;
				pUnit.dwFrameCountPrecise = frame_count;
				std::memcpy(pAnimSeq, anim_seq, sizeof(anim_seq));
			};

			setup_data(moo_pUnit, moo_pAnimSeq);
			setup_data(original_pUnit, original_pAnimSeq);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without anim sequence")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE);

			D2AnimDataRecordStrc anim_data_record{};
			for (auto& frame_flag : anim_data_record.pFrameFlags)
			{
				frame_flag = random_unsigned_integer(0, 4);
			}

			// The frame count has to be at least 1, otherwise the loop processing the animation would never end
			const auto frame_count = random_unsigned_integer(1 << 8, D2AnimDataRecordStrc::MAX_FRAME_FLAGS << 8);
			const auto current_frame = random_unsigned_integer(0, frame_count - 1);
			const auto anim_speed = random_unsigned_integer(0, 1024);
			const auto action_frame = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2AnimDataRecordStrc moo_pAnimData{};
			D2UnitStrc original_pUnit{};
			D2AnimDataRecordStrc original_pAnimData{};

			const auto setup_data = [unit_type, &anim_data_record, frame_count, current_frame, anim_speed, action_frame](
				D2UnitStrc& pUnit,
				D2AnimDataRecordStrc& pAnimData
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFrameCountPrecise = frame_count;
				pUnit.nSeqCurrentFramePrecise = current_frame;
				pUnit.wAnimSpeed = anim_speed;
				pUnit.nActionFrame = action_frame;
				pUnit.pAnimData = &pAnimData;
				pAnimData = anim_data_record;
			};

			setup_data(moo_pUnit, moo_pAnimData);
			setup_data(original_pUnit, original_pAnimData);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEFF0 (#10374)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_UpdateFrame, dll_base + 0x0007EFF0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto current_frame = random_unsigned_integer(0, 255);
			const auto anim_speed = random_unsigned_integer(1, 5);
			const auto frame_count = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [current_frame, anim_speed, frame_count](
				D2UnitStrc& pUnit
			) {
				pUnit.nSeqCurrentFramePrecise = current_frame;
				pUnit.wAnimSpeed = anim_speed;
				pUnit.dwFrameCountPrecise = frame_count;
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBF020 (#10375)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_10375_UNITS_SetFrameNonRate, dll_base + 0x0007F020);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto current_frame = random_unsigned_integer(0, 255);
			const auto anim_speed = random_unsigned_integer(1, 5);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nRate = random_unsigned_integer(0, 255);
			int nFailRate = random_unsigned_integer(0, 255);

			const auto setup_data = [current_frame, anim_speed](
				D2UnitStrc& pUnit
			) {
				pUnit.nSeqCurrentFramePrecise = current_frame;
				pUnit.wAnimSpeed = anim_speed;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nRate, nFailRate);
			original(&original_pUnit, nRate, nFailRate);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(AnimDataFixture<MonModeTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>>, "D2Common.0x6FDBF050 (#10376)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_UpdateAnimRateAndVelocity, dll_base + 0x0007F050);
		
		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				const auto anim_mode = random_unsigned_integer(0, std::min<int>(monmode_record_count, NUMBER_OF_MONMODES) - 1);
				const auto anim_speed = random_unsigned_integer(0, 0x7FFF);
				const auto seq_speed = random_unsigned_integer();
				const auto velocity = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2UnitStrc original_pUnit{};
				D2DynamicPathStrc original_pDynamicPath{};
				const char* szFile = __FILE__;
				int nLine = __LINE__;

				const auto setup_data = [i, anim_mode, anim_speed, seq_speed, velocity](
					D2UnitStrc& pUnit,
					D2DynamicPathStrc& pDynamicPath
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
					pUnit.dwAnimMode = anim_mode;
					pUnit.wAnimSpeed = anim_speed;
					pUnit.dwSeqSpeed = seq_speed;
					pUnit.pDynamicPath = &pDynamicPath;
					pDynamicPath.dwVelocity = velocity;
					pDynamicPath.dwMaxVelocity = velocity;
				};

				setup_data(moo_pUnit, moo_pDynamicPath);
				setup_data(original_pUnit, original_pDynamicPath);

				// Call both implementations
				sut(&moo_pUnit, szFile, nLine);
				original(&original_pUnit, szFile, nLine);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				// The anim data records are part of the data tables, so both implementations have to use the same record
				CHECK_EQ(moo_pUnit.pAnimData, original_pUnit.pAnimData);
			}
		}

		SUBCASE("Item")
		{
			// Input data
			const auto anim_speed = random_unsigned_integer(0, 0x7FFF);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			const char* szFile = __FILE__;
			int nLine = __LINE__;

			const auto setup_data = [anim_speed](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_ITEM;
				pUnit.wAnimSpeed = anim_speed;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, szFile, nLine);
			original(&original_pUnit, szFile, nLine);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Invalid unit type")
		{
			// Input data
			const auto unit_type = random_unsigned_integer(UNIT_TILE, 255);
			const auto anim_speed = random_unsigned_integer(0, 0x7FFF);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			const char* szFile = __FILE__;
			int nLine = __LINE__;

			const auto setup_data = [unit_type, anim_speed](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.wAnimSpeed = anim_speed;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, szFile, nLine);
			original(&original_pUnit, szFile, nLine);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("nullptr")
		{
			// Input data
			const char* szFile = __FILE__;
			int nLine = __LINE__;

			// Call both implementations
			sut(nullptr, szFile, nLine);
			original(nullptr, szFile, nLine);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBF8D0 (#10377)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimationSpeed, dll_base + 0x0007F8D0);
		
		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int16_t nSpeed = random_unsigned_integer(0, 65535);

			// Call both implementations
			sut(&moo_pUnit, nSpeed);
			original(&original_pUnit, nSpeed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBF910 (#10378)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsAtEndOfFrameCycle, dll_base + 0x0007F910);

		REPEAT_10();
		
		SUBCASE("With anim sequence")
		{
			// Input data
			const auto frame_count = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2AnimSeqTxt moo_pAnimSeq{};
			D2UnitStrc original_pUnit{};
			D2AnimSeqTxt original_pAnimSeq{};

			const auto setup_data = [frame_count](
				D2UnitStrc& pUnit,
				D2AnimSeqTxt& pAnimSeq
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
				pUnit.pAnimSeq = &pAnimSeq;
				pUnit.dwFrameCountPrecise = frame_count;
			};

			setup_data(moo_pUnit, moo_pAnimSeq);
			setup_data(original_pUnit, original_pAnimSeq);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without anim sequence")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto frame_count = random_unsigned_integer(0, 0x10000);
			const auto current_frame = random_unsigned_integer(0, 0x10000);
			const auto anim_speed = random_unsigned_integer(0, 0x7FFF);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type, frame_count, current_frame, anim_speed](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFrameCountPrecise = frame_count;
				pUnit.nSeqCurrentFramePrecise = current_frame;
				pUnit.wAnimSpeed = anim_speed;
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
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDBF970 (#10379)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetShiftedFrameMetrics, dll_base + 0x0007F970);
		
		REPEAT_10();

		SUBCASE("object")
		{
			for (auto j = 0; j < 8; ++j)
			{
				for (auto i = 0; i < objects_record_count; ++i)
				{
					// Input data
					const auto current_frame = random_unsigned_integer();
					const auto frame_count = random_unsigned_integer();

					D2UnitStrc moo_pUnit{};
					D2ObjectDataStrc moo_pObjectData{};
					int moo_pFrameNo{};
					int moo_pFrameCount{};
					D2UnitStrc original_pUnit{};
					D2ObjectDataStrc original_pObjectData{};
					int original_pFrameNo{};
					int original_pFrameCount{};

					const auto setup_data = [this, current_frame, frame_count, i, j](
						D2UnitStrc& pUnit,
						D2ObjectDataStrc& pObjectData,
						int& pFrameNo,
						int& pFrameCount
					) {
						pUnit.dwUnitType = UNIT_OBJECT;
						pUnit.dwAnimMode = j;
						pUnit.pObjectData = &pObjectData;
						pObjectData.pObjectTxt = &objects_txt[i];
						pUnit.nSeqCurrentFramePrecise = current_frame;
						pUnit.dwFrameCountPrecise = frame_count;
					};

					setup_data(moo_pUnit, moo_pObjectData, moo_pFrameNo, moo_pFrameCount);
					setup_data(original_pUnit, original_pObjectData, original_pFrameNo, original_pFrameCount);

					// Call both implementations
					sut(&moo_pUnit, &moo_pFrameNo, &moo_pFrameCount);
					original(&original_pUnit, &original_pFrameNo, &original_pFrameCount);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pFrameNo, original_pFrameNo, "Comparing pFrameNo");
					MOO_CHECK_EQ(moo_pFrameCount, original_pFrameCount, "Comparing pFrameCount");
				}
			}
		}

		SUBCASE("other")
		{
			// Input data
			const auto current_frame = random_unsigned_integer();
			const auto frame_count = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			int moo_pFrameNo{};
			int moo_pFrameCount{};
			D2UnitStrc original_pUnit{};
			int original_pFrameNo{};
			int original_pFrameCount{};

			const auto setup_data = [current_frame, frame_count](
				D2UnitStrc& pUnit,
				int& pFrameNo,
				int& pFrameCount
			) {
				pUnit.nSeqCurrentFramePrecise = current_frame;
				pUnit.dwFrameCountPrecise = frame_count;
			};

			setup_data(moo_pUnit, moo_pFrameNo, moo_pFrameCount);
			setup_data(original_pUnit, original_pFrameNo, original_pFrameCount);

			// Call both implementations
			sut(&moo_pUnit, &moo_pFrameNo, &moo_pFrameCount);
			original(&original_pUnit, &original_pFrameNo, &original_pFrameCount);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pFrameNo, original_pFrameNo, "Comparing pFrameNo");
			MOO_CHECK_EQ(moo_pFrameCount, original_pFrameCount, "Comparing pFrameCount");
		}
	}
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDBF9E0 (#10380)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetFrameMetrics, dll_base + 0x0007F9E0);
		
		REPEAT_10();

		SUBCASE("object")
		{
			for (auto j = 0; j < 8; ++j)
			{
				for (auto i = 0; i < objects_record_count; ++i)
				{
					// Input data
					const auto current_frame = random_unsigned_integer();
					const auto frame_count = random_unsigned_integer();

					D2UnitStrc moo_pUnit{};
					D2ObjectDataStrc moo_pObjectData{};
					int moo_pFrame{};
					int moo_pFrameCount{};
					D2UnitStrc original_pUnit{};
					D2ObjectDataStrc original_pObjectData{};
					int original_pFrame{};
					int original_pFrameCount{};

					const auto setup_data = [this, current_frame, frame_count, i, j](
						D2UnitStrc& pUnit,
						D2ObjectDataStrc& pObjectData,
						int& pFrame,
						int& pFrameCount
					) {
						pUnit.dwUnitType = UNIT_OBJECT;
						pUnit.dwAnimMode = j;
						pUnit.pObjectData = &pObjectData;
						pObjectData.pObjectTxt = &objects_txt[i];
						pUnit.nSeqCurrentFramePrecise = current_frame;
						pUnit.dwFrameCountPrecise = frame_count;
					};

					setup_data(moo_pUnit, moo_pObjectData, moo_pFrame, moo_pFrameCount);
					setup_data(original_pUnit, original_pObjectData, original_pFrame, original_pFrameCount);

					// Call both implementations
					sut(&moo_pUnit, &moo_pFrame, &moo_pFrameCount);
					original(&original_pUnit, &original_pFrame, &original_pFrameCount);

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pFrame, original_pFrame, "Comparing pFrame");
					MOO_CHECK_EQ(moo_pFrameCount, original_pFrameCount, "Comparing pFrameCount");
				}
			}
		}

		SUBCASE("other")
		{
			// Input data
			const auto current_frame = random_unsigned_integer();
			const auto frame_count = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			int moo_pFrame{};
			int moo_pFrameCount{};
			D2UnitStrc original_pUnit{};
			int original_pFrame{};
			int original_pFrameCount{};

			const auto setup_data = [current_frame, frame_count](
				D2UnitStrc& pUnit,
				int& pFrame,
				int& pFrameCount
			) {
				pUnit.nSeqCurrentFramePrecise = current_frame;
				pUnit.dwFrameCountPrecise = frame_count;
			};

			setup_data(moo_pUnit, moo_pFrame, moo_pFrameCount);
			setup_data(original_pUnit, original_pFrame, original_pFrameCount);

			// Call both implementations
			sut(&moo_pUnit, &moo_pFrame, &moo_pFrameCount);
			original(&original_pUnit, &original_pFrame, &original_pFrameCount);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pFrame, original_pFrame, "Comparing pFrame");
			MOO_CHECK_EQ(moo_pFrameCount, original_pFrameCount, "Comparing pFrameCount");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFA40 (#10381)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimActionFrame, dll_base + 0x0007FA40);
		
		SUBCASE("With anim data")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto action_frame = random_unsigned_integer(0, 255);

			D2AnimDataRecordStrc anim_data_record{};
			for (auto& frame_flag : anim_data_record.pFrameFlags)
			{
				frame_flag = random_unsigned_integer(0, 5);
			}

			for (auto i = 0; i < 2 * D2AnimDataRecordStrc::MAX_FRAME_FLAGS; ++i)
			{
				D2UnitStrc moo_pUnit{};
				D2AnimDataRecordStrc moo_pAnimData{};
				D2UnitStrc original_pUnit{};
				D2AnimDataRecordStrc original_pAnimData{};
				int nFrame = i;

				const auto setup_data = [unit_type, action_frame, &anim_data_record](
					D2UnitStrc& pUnit,
					D2AnimDataRecordStrc& pAnimData
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.nActionFrame = action_frame;
					pUnit.pAnimData = &pAnimData;
					pAnimData = anim_data_record;
				};

				setup_data(moo_pUnit, moo_pAnimData);
				setup_data(original_pUnit, original_pAnimData);

				// Call both implementations
				sut(&moo_pUnit, nFrame);
				original(&original_pUnit, nFrame);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Without anim data")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto action_frame = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nFrame = random_unsigned_integer(0, D2AnimDataRecordStrc::MAX_FRAME_FLAGS - 1);

			const auto setup_data = [unit_type, action_frame](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.nActionFrame = action_frame;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nFrame);
			original(&original_pUnit, nFrame);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("nullptr")
		{
			// Input data
			int nFrame = random_unsigned_integer(0, D2AnimDataRecordStrc::MAX_FRAME_FLAGS - 1);

			// Call both implementations
			sut(nullptr, nFrame);
			original(nullptr, nFrame);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFA90 (#10382)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetEventFrameInfo, dll_base + 0x0007FA90);
		
		SUBCASE("Player or monster")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);
			const auto anim_mode = random_unsigned_integer(0, NUMBER_OF_PLRMODES - 1);

			D2AnimDataRecordStrc anim_data_record{};
			for (auto& frame_flag : anim_data_record.pFrameFlags)
			{
				frame_flag = random_unsigned_integer(0, 255);
			}

			for (auto i = 0; i < 2 * D2AnimDataRecordStrc::MAX_FRAME_FLAGS; ++i)
			{
				D2UnitStrc moo_pUnit{};
				D2AnimDataRecordStrc moo_pAnimData{};
				D2UnitStrc original_pUnit{};
				D2AnimDataRecordStrc original_pAnimData{};
				int nFrame = i;

				// Units in sequence mode do not have a used skill, so no sequence is found for them
				const auto setup_data = [unit_type, anim_mode, &anim_data_record](
					D2UnitStrc& pUnit,
					D2AnimDataRecordStrc& pAnimData
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.dwAnimMode = anim_mode;
					pUnit.pAnimData = &pAnimData;
					pAnimData = anim_data_record;
				};

				setup_data(moo_pUnit, moo_pAnimData);
				setup_data(original_pUnit, original_pAnimData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nFrame);
				const auto original_result = original(&original_pUnit, nFrame);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Other")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto anim_mode = random_unsigned_integer();

			D2AnimDataRecordStrc anim_data_record{};
			for (auto& frame_flag : anim_data_record.pFrameFlags)
			{
				frame_flag = random_unsigned_integer(0, 255);
			}

			for (auto i = 0; i < 2 * D2AnimDataRecordStrc::MAX_FRAME_FLAGS; ++i)
			{
				D2UnitStrc moo_pUnit{};
				D2AnimDataRecordStrc moo_pAnimData{};
				D2UnitStrc original_pUnit{};
				D2AnimDataRecordStrc original_pAnimData{};
				int nFrame = i;

				const auto setup_data = [unit_type, anim_mode, &anim_data_record](
					D2UnitStrc& pUnit,
					D2AnimDataRecordStrc& pAnimData
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.dwAnimMode = anim_mode;
					pUnit.pAnimData = &pAnimData;
					pAnimData = anim_data_record;
				};

				setup_data(moo_pUnit, moo_pAnimData);
				setup_data(original_pUnit, original_pAnimData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nFrame);
				const auto original_result = original(&original_pUnit, nFrame);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDBFB40 (#10410)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_HasCollision, dll_base + 0x0007FB40);
		
		SUBCASE("object")
		{
			for (auto j = 0; j < 8; ++j)
			{
				for (auto i = 0; i < objects_record_count; ++i)
				{
					// Input data
					D2UnitStrc moo_pUnit{};
					D2ObjectDataStrc moo_pObjectData{};
					D2UnitStrc original_pUnit{};
					D2ObjectDataStrc original_pObjectData{};

					const auto setup_data = [this, i, j](
						D2UnitStrc& pUnit,
						D2ObjectDataStrc& pObjectData
					) {
						pUnit.dwUnitType = UNIT_OBJECT;
						pUnit.dwAnimMode = j;
						pUnit.pObjectData = &pObjectData;
						pObjectData.pObjectTxt = &objects_txt[i];
					};

					setup_data(moo_pUnit, moo_pObjectData);
					setup_data(original_pUnit, original_pObjectData);

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

		SUBCASE("other")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE, UNIT_ITEM);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
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
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDBFB70 (#10358)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetSkillFromSkillId, dll_base + 0x0007FB70);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				auto moo_pSkills = std::make_unique<D2SkillStrc[]>(skills_record_count);
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				auto original_pSkills = std::make_unique<D2SkillStrc[]>(skills_record_count);
				int nSkillId = i;

				const auto setup_data = [this](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					std::unique_ptr<D2SkillStrc[]>& skills
				) {
					std::memset(skills.get(), 0, sizeof(D2SkillStrc) * skills_record_count);
					pUnit.pSkills = &pSkillList;

					for (auto i = 0; i < skills_record_count; ++i)
					{
						skills[i].pSkillsTxt = &skills_txt[i];
						if (i > 0)
						{
							skills[i - 1].pNextSkill = &skills[i];
						}
					}

					pSkillList.pFirstSkill = &skills[0];
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pSkillList, original_pSkills);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSkillId);
				const auto original_result = original(&original_pUnit, nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDBFC10 (#10392)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsDoor, dll_base + 0x0007FC10);
		
		SUBCASE("object")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.pObjectTxt = &objects_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("other")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE, UNIT_ITEM);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
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
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDBFC50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_CheckIfObjectOrientationIs1, dll_base + 0x0007FC50);
		
		SUBCASE("")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
					) {
						pUnit.dwUnitType = UNIT_OBJECT;
						pUnit.pObjectData = &pObjectData;
						pObjectData.pObjectTxt = &objects_txt[i];
					};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

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
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDBFC90 (#10393)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsShrine, dll_base + 0x0007FC90);
		
		SUBCASE("")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.pObjectTxt = &objects_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

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
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDBFCB0 (#10394)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetObjectTxtRecordFromObject, dll_base + 0x0007FCB0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.pObjectTxt = &objects_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

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
	
	TEST_CASE_FIXTURE(ShrinesTxtFixture<NoopFixture>, "D2Common.0x6FDBFD00 (#10395)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetShrineTxtRecordFromObject, dll_base + 0x0007FD00);
		
		SUBCASE("")
		{
			for (auto i = 0; i < shrines_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.pShrineTxt = &shrines_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

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
	
	TEST_CASE_FIXTURE(ShrinesTxtFixture<NoopFixture>, "D2Common.0x6FDBFD50 (#10396)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetShrineTxtRecordInObjectData, dll_base + 0x0007FD50);
		
		SUBCASE("")
		{
			for (auto i = 0; i < shrines_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2ShrinesTxt moo_pShrinesTxtRecord{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};
				D2ShrinesTxt original_pShrinesTxtRecord{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData,
					D2ShrinesTxt& pShrinesTxtRecord
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pShrinesTxtRecord = shrines_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData, moo_pShrinesTxtRecord);
				setup_data(original_pUnit, original_pObjectData, original_pShrinesTxtRecord);

				// Call both implementations
				sut(&moo_pUnit, &moo_pShrinesTxtRecord);
				original(&original_pUnit, &original_pShrinesTxtRecord);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pShrinesTxtRecord, original_pShrinesTxtRecord, "Comparing pShrinesTxtRecord");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFDB0 (#10413)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_UpdateDirectionAndSpeed, dll_base + 0x0007FDB0);

		REPEAT_10();
		
		SUBCASE("With dynamic path")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto precision_x = random_unsigned_integer();
			const auto precision_y = random_unsigned_integer();
			const auto direction = random_unsigned_integer(0, PATH_NB_DIRECTIONS - 1);
			const auto new_direction = random_unsigned_integer(0, PATH_NB_DIRECTIONS - 1);
			const auto diff_direction = random_unsigned_integer(0, 255);
			const auto path_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nX = (precision_x >> 16) + random_unsigned_integer(0, 64) - 32;
			int nY = (precision_y >> 16) + random_unsigned_integer(0, 64) - 32;

			const auto setup_data = [unit_type, precision_x, precision_y, direction, new_direction, diff_direction, path_flags](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.dwPrecisionX = precision_x;
				pDynamicPath.tGameCoords.dwPrecisionY = precision_y;
				pDynamicPath.nDirection = direction;
				pDynamicPath.nNewDirection = new_direction;
				pDynamicPath.nDiffDirection = diff_direction;
				pDynamicPath.dwFlags = path_flags;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			sut(&moo_pUnit, nX, nY);
			original(&original_pUnit, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without dynamic path")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nX = random_unsigned_integer(0, 65535);
			int nY = random_unsigned_integer(0, 65535);

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nX, nY);
			original(&original_pUnit, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFDD0 (#10414)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetNewDirection, dll_base + 0x0007FDD0);

		REPEAT_10();
		
		SUBCASE("Target differs from position")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(32, 65535 - 32);
			const auto y = random_unsigned_integer(32, 65535 - 32);
			const auto target_x = x + random_unsigned_integer(1, 32);
			const auto target_y = y - random_unsigned_integer(0, 32);
			const auto new_direction = random_unsigned_integer(0, PATH_NB_DIRECTIONS - 1);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, x, y, target_x, target_y, new_direction](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
				pDynamicPath.tTargetCoord.X = target_x;
				pDynamicPath.tTargetCoord.Y = target_y;
				pDynamicPath.nNewDirection = new_direction;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Target equals position")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);
			const auto new_direction = random_unsigned_integer(0, PATH_NB_DIRECTIONS - 1);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [unit_type, x, y, new_direction](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
				pDynamicPath.tTargetCoord.X = x;
				pDynamicPath.tTargetCoord.Y = y;
				pDynamicPath.nNewDirection = new_direction;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<NoopFixture>>, "D2Common.0x6FDBFF20 (#10416)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StoreOwnerTypeAndGUID, dll_base + 0x0007FF20);
		
		SUBCASE("Without stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto flags_ex = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nOwnerType = random_unsigned_integer(0, UNIT_TYPES_COUNT);
			D2UnitGUID nOwnerId = random_unsigned_integer();

			const auto setup_data = [unit_type, flags_ex](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFlagEx = flags_ex;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nOwnerType, nOwnerId);
			original(&original_pUnit, nOwnerType, nOwnerId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("With stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto unit_id = random_unsigned_integer();
			const auto flag_count = (states_record_count >> 5) + 1;

			// The unit does not have a path, so it is not linked to any room which would need to be refreshed
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			int nOwnerType = random_unsigned_integer(0, UNIT_TYPES_COUNT);
			D2UnitGUID nOwnerId = random_unsigned_integer();

			const auto setup_data = [unit_type, unit_id](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				std::unique_ptr<uint32_t[]>& StatFlags
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwUnitId = unit_id;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = unit_type;
				pStatListEx.dwOwnerId = unit_id;
				pStatListEx.pOwner = &pUnit;
				pStatListEx.StatFlags = StatFlags.get();
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags);
			setup_data(original_pUnit, original_pStatListEx, original_StatFlags);

			// Call both implementations
			sut(&moo_pUnit, nOwnerType, nOwnerId);
			original(&original_pUnit, nOwnerType, nOwnerId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			for (auto i = 0; i < 2 * flag_count; ++i)
			{
				MOO_CHECK_EQ(moo_StatFlags[i], original_StatFlags[i], "Comparing StatFlags");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<NoopFixture>>, "D2Common.0x6FDBFF40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StoreOwnerInfo, dll_base + 0x0007FF40);
		
		SUBCASE("Without stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto flags_ex = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nOwnerType = random_unsigned_integer(0, UNIT_TYPES_COUNT);
			int nOwnerId = random_unsigned_integer();

			const auto setup_data = [unit_type, flags_ex](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFlagEx = flags_ex;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nOwnerType, nOwnerId);
			original(&original_pUnit, nOwnerType, nOwnerId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("With stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto unit_id = random_unsigned_integer();
			const auto flag_count = (states_record_count >> 5) + 1;

			// The unit does not have a path, so it is not linked to any room which would need to be refreshed
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			int nOwnerType = random_unsigned_integer(0, UNIT_TYPES_COUNT);
			int nOwnerId = random_unsigned_integer();

			const auto setup_data = [unit_type, unit_id](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				std::unique_ptr<uint32_t[]>& StatFlags
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwUnitId = unit_id;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = unit_type;
				pStatListEx.dwOwnerId = unit_id;
				pStatListEx.pOwner = &pUnit;
				pStatListEx.StatFlags = StatFlags.get();
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags);
			setup_data(original_pUnit, original_pStatListEx, original_StatFlags);

			// Call both implementations
			sut(&moo_pUnit, nOwnerType, nOwnerId);
			original(&original_pUnit, nOwnerType, nOwnerId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			for (auto i = 0; i < 2 * flag_count; ++i)
			{
				MOO_CHECK_EQ(moo_StatFlags[i], original_StatFlags[i], "Comparing StatFlags");
			}
		}

		SUBCASE("With stat list containing the source unit state")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto unit_id = random_unsigned_integer();
			const auto flag_count = (states_record_count >> 5) + 1;

			// The unit does not have a path, so it is not linked to any room which would need to be refreshed
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pSourceUnitStatList{};
			auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pSourceUnitStatList{};
			auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			int nOwnerType = random_unsigned_integer(0, UNIT_TYPES_COUNT);
			int nOwnerId = random_unsigned_integer();

			const auto setup_data = [unit_type, unit_id](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pSourceUnitStatList,
				std::unique_ptr<uint32_t[]>& StatFlags
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwUnitId = unit_id;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = unit_type;
				pStatListEx.dwOwnerId = unit_id;
				pStatListEx.pOwner = &pUnit;
				pStatListEx.StatFlags = StatFlags.get();

				// The stat list of the state is already linked to the unit's stat list
				pStatListEx.pMyLastList = &pSourceUnitStatList;
				pSourceUnitStatList.dwStateNo = STATE_SOURCEUNIT;
				pSourceUnitStatList.dwOwnerType = unit_type;
				pSourceUnitStatList.dwOwnerId = unit_id;
				pSourceUnitStatList.pUnit = &pUnit;
				pSourceUnitStatList.pParent = &pStatListEx;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pSourceUnitStatList, moo_StatFlags);
			setup_data(original_pUnit, original_pStatListEx, original_pSourceUnitStatList, original_StatFlags);

			// Call both implementations
			sut(&moo_pUnit, nOwnerType, nOwnerId);
			original(&original_pUnit, nOwnerType, nOwnerId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			for (auto i = 0; i < 2 * flag_count; ++i)
			{
				MOO_CHECK_EQ(moo_StatFlags[i], original_StatFlags[i], "Comparing StatFlags");
			}
		}

		SUBCASE("nullptr")
		{
			// Input data
			int nOwnerType = random_unsigned_integer(0, UNIT_TYPES_COUNT);
			int nOwnerId = random_unsigned_integer();

			// Call both implementations
			sut(nullptr, nOwnerType, nOwnerId);
			original(nullptr, nOwnerType, nOwnerId);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<NoopFixture>>, "D2Common.0x6FDBFFE0 (#10415)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StoreOwner, dll_base + 0x0007FFE0);
		
		SUBCASE("With owner, without stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto flags_ex = random_unsigned_integer();
			const auto owner_type = random_unsigned_integer(0, UNIT_TYPES_COUNT);
			const auto owner_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pOwner{};

			const auto setup_data = [unit_type, flags_ex, owner_type, owner_id](
				D2UnitStrc& pUnit,
				D2UnitStrc& pOwner
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFlagEx = flags_ex;
				pOwner.dwUnitType = owner_type;
				pOwner.dwUnitId = owner_id;
			};

			setup_data(moo_pUnit, moo_pOwner);
			setup_data(original_pUnit, original_pOwner);

			// Call both implementations
			sut(&moo_pUnit, &moo_pOwner);
			original(&original_pUnit, &original_pOwner);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}

		SUBCASE("With owner, with stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto unit_id = random_unsigned_integer();
			const auto owner_type = random_unsigned_integer(0, UNIT_TYPES_COUNT);
			const auto owner_id = random_unsigned_integer();
			const auto flag_count = (states_record_count >> 5) + 1;

			// The unit does not have a path, so it is not linked to any room which would need to be refreshed
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			D2UnitStrc original_pOwner{};

			const auto setup_data = [unit_type, unit_id, owner_type, owner_id](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				std::unique_ptr<uint32_t[]>& StatFlags,
				D2UnitStrc& pOwner
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwUnitId = unit_id;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = unit_type;
				pStatListEx.dwOwnerId = unit_id;
				pStatListEx.pOwner = &pUnit;
				pStatListEx.StatFlags = StatFlags.get();
				pOwner.dwUnitType = owner_type;
				pOwner.dwUnitId = owner_id;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags, moo_pOwner);
			setup_data(original_pUnit, original_pStatListEx, original_StatFlags, original_pOwner);

			// Call both implementations
			sut(&moo_pUnit, &moo_pOwner);
			original(&original_pUnit, &original_pOwner);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");

			for (auto i = 0; i < 2 * flag_count; ++i)
			{
				MOO_CHECK_EQ(moo_StatFlags[i], original_StatFlags[i], "Comparing StatFlags");
			}
		}

		SUBCASE("Without owner, without stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto flags_ex = random_unsigned_integer();
			const auto owner_type = random_unsigned_integer();
			const auto owner_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type, flags_ex, owner_type, owner_id](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwFlagEx = flags_ex;
				pUnit.dwOwnerType = owner_type;
				pUnit.dwOwnerGUID = owner_id;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nullptr);
			original(&original_pUnit, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without owner, with stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto unit_id = random_unsigned_integer();
			const auto flags_ex = random_unsigned_integer() & ~UNITFLAGEX_ISSHAPESHIFTED;
			const auto owner_type = random_unsigned_integer();
			const auto owner_id = random_unsigned_integer();
			const auto flag_count = (states_record_count >> 5) + 1;

			// The state flags of the unit contain the source unit state, but no corresponding stat list.
			// The unit does not have a path, so it is not linked to any room which would need to be refreshed
			auto stat_flags = std::make_unique<uint32_t[]>(2 * flag_count);
			stat_flags[STATE_SOURCEUNIT >> 5] |= gdwBitMasks[STATE_SOURCEUNIT & 31];

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);

			const auto setup_data = [unit_type, unit_id, flags_ex, owner_type, owner_id, &stat_flags, flag_count](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				std::unique_ptr<uint32_t[]>& StatFlags
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwUnitId = unit_id;
				pUnit.dwFlagEx = flags_ex;
				pUnit.dwOwnerType = owner_type;
				pUnit.dwOwnerGUID = owner_id;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = unit_type;
				pStatListEx.dwOwnerId = unit_id;
				pStatListEx.pOwner = &pUnit;
				pStatListEx.StatFlags = StatFlags.get();
				std::memcpy(StatFlags.get(), stat_flags.get(), sizeof(uint32_t) * 2 * flag_count);
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags);
			setup_data(original_pUnit, original_pStatListEx, original_StatFlags);

			// Call both implementations
			sut(&moo_pUnit, nullptr);
			original(&original_pUnit, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

			for (auto i = 0; i < 2 * flag_count; ++i)
			{
				MOO_CHECK_EQ(moo_StatFlags[i], original_StatFlags[i], "Comparing StatFlags");
			}
		}

		SUBCASE("nullptr")
		{
			// Call both implementations
			sut(nullptr, nullptr);
			original(nullptr, nullptr);
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0060 (#10417)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StoreLastAttacker, dll_base + 0x00080060);
		
		SUBCASE("")
		{
			// Input data
			const auto killer_type = random_unsigned_integer();
			const auto killer_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pKiller{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pKiller{};

			const auto setup_data = [killer_type, killer_id](
				D2UnitStrc& pUnit,
				D2UnitStrc& pKiller
			) {
				pKiller.dwUnitType = killer_type;
				pKiller.dwUnitId = killer_id;
			};

			setup_data(moo_pUnit, moo_pKiller);
			setup_data(original_pUnit, original_pKiller);

			// Call both implementations
			sut(&moo_pUnit, &moo_pKiller);
			original(&original_pUnit, &original_pKiller);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pKiller, original_pKiller, "Comparing pKiller");
		}

		SUBCASE("nullptr")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit
			) {
				pUnit.dwKillerType = random_unsigned_integer();
				pUnit.dwKillerGUID = random_unsigned_integer();
				pUnit.dwFlagEx = flags | UNITFLAGEX_STORELASTATTACKER;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nullptr);
			original(&original_pUnit, nullptr);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC00E0 (#10418)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetDirectionToCoords, dll_base + 0x000800E0);

		REPEAT_10();
		
		SUBCASE("Static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			int nNewX = x + random_unsigned_integer(0, 64) - 32;
			int nNewY = y + random_unsigned_integer(0, 64) - 32;

			const auto setup_data = [unit_type, x, y](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
				pStaticPath.tGameCoords.nY = y;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nNewX, nNewY);
			const auto original_result = original(&original_pUnit, nNewX, nNewY);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nNewX = x + random_unsigned_integer(0, 64) - 32;
			int nNewY = y + random_unsigned_integer(0, 64) - 32;

			const auto setup_data = [unit_type, x, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nNewX, nNewY);
			const auto original_result = original(&original_pUnit, nNewX, nNewY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<OverlayTxtFixture<NoopFixture>>, "D2Common.0x6FDC0160 (#10437)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetOverlay, dll_base + 0x00080160);
		
		SUBCASE("Invalid overlay")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto invalid_overlay = GENERATE(-1, 0);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nOverlay = invalid_overlay < 0 ? -static_cast<int>(random_unsigned_integer(1, 0x7FFF)) : random_unsigned_integer(overlay_record_count, 0x7FFF);
			int nUnused = random_unsigned_integer();

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nOverlay, nUnused);
			original(&original_pUnit, nOverlay, nUnused);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without overlay stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto unit_id = random_unsigned_integer();
			const auto flags = random_unsigned_integer();
			const auto room_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};
			int nOverlay = random_unsigned_integer(0, overlay_record_count - 1);
			int nUnused = random_unsigned_integer();

			const auto setup_data = [unit_type, unit_id, flags, room_flags](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwUnitId = unit_id;
				pUnit.dwFlags = flags;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = unit_type;
				pStatListEx.dwOwnerId = unit_id;
				pStatListEx.pOwner = &pUnit;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;
				pRoom.dwFlags = room_flags;
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pDynamicPath, moo_pRoom, moo_pAct);
			setup_data(original_pUnit, original_pStatListEx, original_pDynamicPath, original_pRoom, original_pAct);

			// Call both implementations
			sut(&moo_pUnit, nOverlay, nUnused);
			original(&original_pUnit, nOverlay, nUnused);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("With overlay stat list")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto unit_id = random_unsigned_integer();
			const auto flags = random_unsigned_integer();
			const auto room_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatListStrc moo_pOverlayStatList{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2DrlgActStrc moo_pAct{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatListStrc original_pOverlayStatList{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2DrlgActStrc original_pAct{};
			int nOverlay = random_unsigned_integer(0, overlay_record_count - 1);
			int nUnused = random_unsigned_integer();

			const auto setup_data = [unit_type, unit_id, flags, room_flags](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatListStrc& pOverlayStatList,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2DrlgActStrc& pAct
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwUnitId = unit_id;
				pUnit.dwFlags = flags;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags = STATLIST_EXTENDED;
				pStatListEx.dwOwnerType = unit_type;
				pStatListEx.dwOwnerId = unit_id;
				pStatListEx.pOwner = &pUnit;

				// The overlay stat list is already linked to the unit's stat list
				pStatListEx.pMyLastList = &pOverlayStatList;
				pOverlayStatList.dwFlags = STATLIST_OVERLAY;
				pOverlayStatList.dwOwnerType = unit_type;
				pOverlayStatList.dwOwnerId = unit_id;
				pOverlayStatList.pUnit = &pUnit;
				pOverlayStatList.pParent = &pStatListEx;

				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.pRoom = &pRoom;
				pRoom.dwFlags = room_flags;
				pRoom.pAct = &pAct;
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pOverlayStatList, moo_pDynamicPath, moo_pRoom, moo_pAct);
			setup_data(original_pUnit, original_pStatListEx, original_pOverlayStatList, original_pDynamicPath, original_pRoom, original_pAct);

			// Call both implementations
			sut(&moo_pUnit, nOverlay, nUnused);
			original(&original_pUnit, nOverlay, nUnused);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<NoopFixture>, "D2Common.0x6FDC01F0 (#10367)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetBeltType, dll_base + 0x000801F0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_ITEM;
					pUnit.dwClassId = i;
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
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDC0260 (#10368)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetCurrentLifePercentage, dll_base + 0x00080260);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pStat[2]{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pStat[2]{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatStrc(&pStat)[2]
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;

				pStat[0].nStat = STAT_HITPOINTS;
				pStat[0].nValue = 0x800;
				pStat[1].nStat = STAT_MAXHP;
				pStat[1].nValue = 0x1000;

				pStatListEx.FullStats.pStat = pStat;
				pStatListEx.FullStats.nStatCount = 2;
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

			CHECK_EQ(moo_result, 50);
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDC02A0 (#10359)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsSoftMonster, dll_base + 0x000802A0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
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
	
	TEST_CASE_FIXTURE(PortalLevelsFixture<NoopFixture>, "D2Common.0x6FDC0320 (#10420)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_AllocPlayerData, dll_base + 0x00080320);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(PortalLevelsFixture<NoopFixture>, "D2Common.0x6FDC03F0 (#10421)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_FreePlayerData, dll_base + 0x000803F0);
		const auto [moo_alloc, original_alloc] = make_function_pair(UNITS_AllocPlayerData, dll_base + 0x00080320);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};

			moo_alloc(&moo_pPlayer);
			original_alloc(&original_pPlayer);

			// Call both implementations
			sut(nullptr, &moo_pPlayer);
			original(nullptr, &original_pPlayer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC04A0 (#10422)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetNameInPlayerData, dll_base + 0x000804A0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			char moo_szName[16]{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			char original_szName[16]{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData,
				char (&szName)[16]
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				strcpy_s(szName, "Player");
			};

			setup_data(moo_pUnit, moo_pPlayerData, moo_szName);
			setup_data(original_pUnit, original_pPlayerData, original_szName);

			// Call both implementations
			sut(&moo_pUnit, moo_szName);
			original(&original_pUnit, original_szName);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_szName, original_szName, "Comparing szName");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0530 (#10423)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetPlayerName, dll_base + 0x00080530);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				strcpy_s(pPlayerData.szName, "Player");
			};

			setup_data(moo_pUnit, moo_pPlayerData);
			setup_data(original_pUnit, original_pPlayerData);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC05B0 (#10424)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetPlayerData, dll_base + 0x000805B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				strcpy_s(pPlayerData.szName, "Player");
			};

			setup_data(moo_pUnit, moo_pPlayerData);
			setup_data(original_pUnit, original_pPlayerData);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0600 (#10425)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetPlayerPortalFlags, dll_base + 0x00080600);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int nPortalFlags = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
			};

			setup_data(moo_pUnit, moo_pPlayerData);
			setup_data(original_pUnit, original_pPlayerData);

			// Call both implementations
			sut(&moo_pUnit, nPortalFlags);
			original(&original_pUnit, nPortalFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0660 (#10426)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetPlayerPortalFlags, dll_base + 0x00080660);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pPlayerData.nPortalFlags = flags;
			};

			setup_data(moo_pUnit, moo_pPlayerData);
			setup_data(original_pUnit, original_pPlayerData);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(ObjectsTxtFixture<NoopFixture>, "D2Common.0x6FDC06C0 (#10353)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetNameOffsetFromObject, dll_base + 0x000806C0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < objects_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.pObjectTxt = &objects_txt[i];
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0700 (#10427)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetObjectPortalFlags, dll_base + 0x00080700);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2ObjectDataStrc moo_pObjectData{};
			D2UnitStrc original_pUnit{};
			D2ObjectDataStrc original_pObjectData{};

			const auto setup_data = [flags](
				D2UnitStrc& pUnit,
				D2ObjectDataStrc& pObjectData
			) {
				pUnit.dwUnitType = UNIT_OBJECT;
				pUnit.pObjectData = &pObjectData;
				pObjectData.nPortalFlags = flags;
			};

			setup_data(moo_pUnit, moo_pObjectData);
			setup_data(original_pUnit, original_pObjectData);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0760 (#10428)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetObjectPortalFlags, dll_base + 0x00080760);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ObjectDataStrc moo_pObjectData{};
			D2UnitStrc original_pUnit{};
			D2ObjectDataStrc original_pObjectData{};
			uint8_t nPortalFlag = random_unsigned_integer(0, 255);

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
				};

			setup_data(moo_pUnit, moo_pObjectData);
			setup_data(original_pUnit, original_pObjectData);

			// Call both implementations
			sut(&moo_pUnit, nPortalFlag);
			original(&original_pUnit, nPortalFlag);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC07C0 (#10429)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_CheckObjectPortalFlag, dll_base + 0x000807C0);
		
		REPEAT_10();

		SUBCASE("")
		{
			const auto flags = random_unsigned_integer(0, 255);

			for (auto i = 0; i < 8; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2ObjectDataStrc moo_pObjectData{};
				D2UnitStrc original_pUnit{};
				D2ObjectDataStrc original_pObjectData{};
				uint8_t nFlag = (1 << i);

				const auto setup_data = [flags](
					D2UnitStrc& pUnit,
					D2ObjectDataStrc& pObjectData
				) {
					pUnit.dwUnitType = UNIT_OBJECT;
					pUnit.pObjectData = &pObjectData;
					pObjectData.nPortalFlags = flags;
				};

				setup_data(moo_pUnit, moo_pObjectData);
				setup_data(original_pUnit, original_pObjectData);

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
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDC0820 (#10430)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetOverlayHeight, dll_base + 0x00080820);
		
		SUBCASE("Player")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
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

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
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
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<StatesTxtFixture<ItemStatCostTxtFixture<NoopFixture>>>, "D2Common.0x6FDC08B0 (#10431)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetDefense, dll_base + 0x000808B0);

		REPEAT_10();

		// The stats of a stat array are expected to be sorted
		const auto sort_stats = [](D2StatStrc* pStats, int nStatCount) {
			std::sort(pStats, pStats + nStatCount, [](const D2StatStrc& lhs, const D2StatStrc& rhs) {
				return lhs.nPackedValue < rhs.nPackedValue;
			});
		};

		D2StatStrc stats[5]{};
		stats[0].nStat = STAT_DEXTERITY;
		stats[0].nValue = random_unsigned_integer(0, 255);
		stats[1].nStat = STAT_ARMORCLASS;
		stats[1].nValue = random_unsigned_integer(0, 10000);
		stats[2].nStat = STAT_ITEM_ARMOR_PERCENT;
		stats[2].nValue = random_unsigned_integer(0, 300);
		stats[3].nStat = STAT_SKILL_ARMOR_PERCENT;
		stats[3].nValue = random_unsigned_integer(0, 300);
		stats[4].nStat = STAT_ARMOR_OVERRIDE_PERCENT;
		stats[4].nValue = random_unsigned_integer(0, 1) ? random_unsigned_integer(0, 100) : 0;
		sort_stats(stats, 5);
		
		SUBCASE("Without holy shield")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);
			const auto flag_count = (states_record_count >> 5) + 1;

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pStat[5]{};
			auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pStat[5]{};
			auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);

			const auto setup_data = [unit_type, &stats](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatStrc(&pStat)[5],
				std::unique_ptr<uint32_t[]>& StatFlags
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.FullStats.pStat = pStat;
				pStatListEx.FullStats.nStatCount = 5;
				pStatListEx.StatFlags = StatFlags.get();
				std::memcpy(pStat, stats, sizeof(stats));
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_StatFlags);
			setup_data(original_pUnit, original_pStatListEx, original_pStat, original_StatFlags);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("With holy shield, without equipped shield")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);
			const auto flag_count = (states_record_count >> 5) + 1;

			D2StatStrc holy_shield_stats[2]{};
			holy_shield_stats[0].nStat = STAT_MODIFIERLIST_SKILL;
			holy_shield_stats[0].nValue = random_unsigned_integer(0, skills_record_count - 1);
			holy_shield_stats[1].nStat = STAT_MODIFIERLIST_LEVEL;
			holy_shield_stats[1].nValue = random_unsigned_integer(1, 50);
			sort_stats(holy_shield_stats, 2);

			// The unit does not have an inventory, so the holy shield bonus is not applied
			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pStat[5]{};
			D2StatListStrc moo_pHolyShieldStatList{};
			D2StatStrc moo_pHolyShieldStat[2]{};
			auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pStat[5]{};
			D2StatListStrc original_pHolyShieldStatList{};
			D2StatStrc original_pHolyShieldStat[2]{};
			auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);

			const auto setup_data = [unit_type, &stats, &holy_shield_stats](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatStrc(&pStat)[5],
				D2StatListStrc& pHolyShieldStatList,
				D2StatStrc(&pHolyShieldStat)[2],
				std::unique_ptr<uint32_t[]>& StatFlags
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.FullStats.pStat = pStat;
				pStatListEx.FullStats.nStatCount = 5;
				pStatListEx.StatFlags = StatFlags.get();
				StatFlags[STATE_HOLYSHIELD >> 5] |= gdwBitMasks[STATE_HOLYSHIELD & 31];
				std::memcpy(pStat, stats, sizeof(stats));

				pStatListEx.pMyLastList = &pHolyShieldStatList;
				pHolyShieldStatList.dwStateNo = STATE_HOLYSHIELD;
				pHolyShieldStatList.pParent = &pStatListEx;
				pHolyShieldStatList.Stats.pStat = pHolyShieldStat;
				pHolyShieldStatList.Stats.nStatCount = 2;
				std::memcpy(pHolyShieldStat, holy_shield_stats, sizeof(holy_shield_stats));
			};

			setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pHolyShieldStatList, moo_pHolyShieldStat, moo_StatFlags);
			setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pHolyShieldStatList, original_pHolyShieldStat, original_StatFlags);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<CharStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDC0AC0 (#10432)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetAttackRate, dll_base + 0x00080AC0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < charstats_record_count; ++i)
			{
				// Input data
				const auto to_hit = random_unsigned_integer(0, 65535);
				const auto dexterity = random_unsigned_integer(0, 255);

				D2UnitStrc moo_pAttacker{};
				D2StatListExStrc moo_pStatListEx{};
				D2StatStrc moo_pStat[2]{};
				D2UnitStrc original_pAttacker{};
				D2StatListExStrc original_pStatListEx{};
				D2StatStrc original_pStat[2]{};

				const auto setup_data = [i, to_hit, dexterity](
					D2UnitStrc& pAttacker,
					D2StatListExStrc& pStatListEx,
					D2StatStrc(&pStat)[2]
				) {
					pAttacker.dwUnitType = UNIT_PLAYER;
					pAttacker.dwClassId = i;

					pAttacker.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.FullStats.pStat = pStat;
					pStatListEx.FullStats.nStatCount = 2;
					pStat[0].nStat = STAT_TOHIT;
					pStat[0].nValue = to_hit;
					pStat[1].nStat = STAT_DEXTERITY;
					pStat[1].nValue = dexterity;
				};

				setup_data(moo_pAttacker, moo_pStatListEx, moo_pStat);
				setup_data(original_pAttacker, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pAttacker);
				const auto original_result = original(&original_pAttacker);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<CharStatsTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FDC0B60 (#10433)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetBlockRate, dll_base + 0x00080B60);

		// The stats of a stat array are expected to be sorted
		const auto sort_stats = [](D2StatStrc* pStats, int nStatCount) {
			std::sort(pStats, pStats + nStatCount, [](const D2StatStrc& lhs, const D2StatStrc& rhs) {
				return lhs.nPackedValue < rhs.nPackedValue;
			});
		};
		
		SUBCASE("Player with equipped item")
		{
			// Every item is tested in both hands, only shields are expected to give a block chance
			for (auto i = 0; i < items_record_count; ++i)
			for (const auto body_loc : { BODYLOC_RARM, BODYLOC_LARM })
			{
				// Input data
				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);

				D2StatStrc stats[3]{};
				stats[0].nStat = STAT_TOBLOCK;
				stats[0].nValue = random_unsigned_integer(0, 100);
				stats[1].nStat = STAT_LEVEL;
				stats[1].nValue = random_unsigned_integer(0, 99);
				stats[2].nStat = STAT_DEXTERITY;
				stats[2].nValue = random_unsigned_integer(0, 500);
				sort_stats(stats, 3);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				D2StatStrc moo_pStat[3]{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				D2StatStrc original_pStat[3]{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pItem{};
				BOOL bExpansion = random_unsigned_integer(0, 1);

				const auto setup_data = [i, body_loc, class_id, &stats](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					D2StatStrc(&pStat)[3],
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pItem
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.FullStats.pStat = pStat;
					pStatListEx.FullStats.nStatCount = 3;
					std::memcpy(pStat, stats, sizeof(stats));

					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[body_loc] = &pItem;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pItem);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, bExpansion);
				const auto original_result = original(&original_pUnit, bExpansion);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Player without inventory")
		{
			// Input data
			const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL bExpansion = random_unsigned_integer(0, 1);

			const auto setup_data = [class_id](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = class_id;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, bExpansion);
			const auto original_result = original(&original_pUnit, bExpansion);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Monsters which can block with a shield look up the item code of their shield component,
				// which requires the item code linker. These monsters are skipped, if they have such a component.
				const auto bCanBlockWithShield = !(monstats_txt[i].dwMonStatsFlags & gdwBitMasks[MONSTATSFLAGINDEX_NOSHLDBLOCK])
					&& i != MONSTER_DIABLO && i != MONSTER_DOOMKNIGHT1 && i != MONSTER_DIABLOCLONE && i != MONSTER_ACT3HIRE;
				const auto pMonStats2TxtRecord = UNITS_GetMonStats2TxtRecordFromMonsterId(i);
				if (bCanBlockWithShield && pMonStats2TxtRecord && pMonStats2TxtRecord->nComponentChoiceCounts[7] > 0)
				{
					continue;
				}

				// Input data
				const auto to_block = random_unsigned_integer(0, 100);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				D2StatStrc moo_pStat{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				D2StatStrc original_pStat{};
				BOOL bExpansion = random_unsigned_integer(0, 1);

				const auto setup_data = [i, to_block](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					D2StatStrc& pStat
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.FullStats.pStat = &pStat;
					pStatListEx.FullStats.nStatCount = 1;
					pStat.nStat = STAT_TOBLOCK;
					pStat.nValue = to_block;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
				setup_data(original_pUnit, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, bExpansion);
				const auto original_result = original(&original_pUnit, bExpansion);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Other")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL bExpansion = random_unsigned_integer(0, 1);

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, bExpansion);
			const auto original_result = original(&original_pUnit, bExpansion);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("nullptr")
		{
			// Input data
			BOOL bExpansion = random_unsigned_integer(0, 1);

			// Call both implementations
			const auto moo_result = sut(nullptr, bExpansion);
			const auto original_result = original(nullptr, bExpansion);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FDC0DA0 (#10434)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10434, dll_base + 0x00080DA0);
		
		SUBCASE("Without inventory")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL a2 = random_unsigned_integer(0, 1);

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, a2);
			const auto original_result = original(&original_pUnit, a2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Unit which cannot dual wield")
		{
			const auto class_id = GENERATE(PCLASS_AMAZON, PCLASS_SORCERESS, PCLASS_NECROMANCER, PCLASS_PALADIN, PCLASS_DRUID);

			// Every item is tested in both hands
			for (auto i = 0; i < items_record_count; ++i)
			for (const auto body_loc : { BODYLOC_RARM, BODYLOC_LARM })
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pItem{};
				BOOL a2 = random_unsigned_integer(0, 1);

				const auto setup_data = [i, body_loc, class_id](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pItem
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[body_loc] = &pItem;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pItem);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, a2);
				const auto original_result = original(&original_pUnit, a2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Unit which can dual wield")
		{
			// Input data
			const auto class_id = GENERATE(PCLASS_BARBARIAN, PCLASS_ASSASSIN);
			const auto weapon_selection = GENERATE(0, 1, 2, 3, 4);

			for (auto iteration = 0; iteration < 100; ++iteration)
			{
				const auto right_hand_item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto left_hand_item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto right_hand_item_id = random_unsigned_integer(0, 1000);
				const auto left_hand_item_id = random_unsigned_integer(1001, 2000);
				const auto left_item_guid_choice = random_unsigned_integer(0, 2);
				const auto left_item_guid = left_item_guid_choice == 0 ? D2UnitInvalidGUID : left_item_guid_choice == 1 ? right_hand_item_id : left_hand_item_id;
				const auto has_used_skill = random_unsigned_integer(0, 1);
				const auto skill_flags = random_unsigned_integer();
				const auto seq_frame = random_unsigned_integer(0, 0xFFF);
				const auto flags_ex = random_unsigned_integer() & ~UNITFLAGEX_ISSHAPESHIFTED;

				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pUsedSkill{};
				D2SkillsTxt moo_pSkillsTxtRecord{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pRightHandItem{};
				D2UnitStrc moo_pLeftHandItem{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pUsedSkill{};
				D2SkillsTxt original_pSkillsTxtRecord{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pRightHandItem{};
				D2UnitStrc original_pLeftHandItem{};
				BOOL a2 = random_unsigned_integer(0, 1);

				const auto setup_data = [class_id, weapon_selection, right_hand_item_class_id, left_hand_item_class_id, right_hand_item_id, left_hand_item_id, left_item_guid, has_used_skill, skill_flags, seq_frame, flags_ex](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc& pUsedSkill,
					D2SkillsTxt& pSkillsTxtRecord,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pRightHandItem,
					D2UnitStrc& pLeftHandItem
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.dwSeqFrame = seq_frame;
					pUnit.dwFlagEx = flags_ex;

					pUnit.pSkills = &pSkillList;
					if (has_used_skill)
					{
						pSkillList.pUsedSkill = &pUsedSkill;
					}
					pUsedSkill.pSkillsTxt = &pSkillsTxtRecord;
					pUsedSkill.dwFlags = skill_flags;
					pSkillsTxtRecord.nWeapSel = weapon_selection;

					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = left_item_guid;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[BODYLOC_RARM] = &pRightHandItem;
					pBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
					pRightHandItem.dwUnitType = UNIT_ITEM;
					pRightHandItem.dwClassId = right_hand_item_class_id;
					pRightHandItem.dwUnitId = right_hand_item_id;
					pLeftHandItem.dwUnitType = UNIT_ITEM;
					pLeftHandItem.dwClassId = left_hand_item_class_id;
					pLeftHandItem.dwUnitId = left_hand_item_id;
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pUsedSkill, moo_pSkillsTxtRecord, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
				setup_data(original_pUnit, original_pSkillList, original_pUsedSkill, original_pSkillsTxtRecord, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, a2);
				const auto original_result = original(&original_pUnit, a2);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FDC0F70 (#10435)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetEquippedWeaponFromMonster, dll_base + 0x00080F70);
		
		SUBCASE("Monster with equipped item")
		{
			// Every item is tested in both hands, only weapons are expected to be returned
			for (auto i = 0; i < items_record_count; ++i)
			for (const auto body_loc : { BODYLOC_RARM, BODYLOC_LARM })
			{
				// Input data
				const auto item_id = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i, body_loc, item_id](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pItem
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[body_loc] = &pItem;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.dwUnitId = item_id;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pItem);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Monster without inventory")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_MONSTER;
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

		SUBCASE("Other unit types")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2InventoryStrc moo_pInventory{};
			D2UnitStrc original_pUnit{};
			D2InventoryStrc original_pInventory{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit,
				D2InventoryStrc& pInventory
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pInventory = &pInventory;
				pInventory.dwSignature = D2C_InventoryHeader;
				pInventory.pOwner = &pUnit;
			};

			setup_data(moo_pUnit, moo_pInventory);
			setup_data(original_pUnit, original_pInventory);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("nullptr")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FDC0FC0 (#10436)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetFrameBonus, dll_base + 0x00080FC0);
		
		SUBCASE("Player without inventory")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_PLRMODES; ++j)
				{
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

		SUBCASE("Player with equipped item")
		{
			const auto class_id = GENERATE(PCLASS_AMAZON, PCLASS_SORCERESS, PCLASS_NECROMANCER, PCLASS_PALADIN, PCLASS_BARBARIAN, PCLASS_DRUID, PCLASS_ASSASSIN);
			const auto anim_mode = GENERATE(PLRMODE_ATTACK1, PLRMODE_ATTACK2, PLRMODE_SPECIAL3, PLRMODE_SPECIAL4);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i, class_id, anim_mode](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pItem
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.dwAnimMode = anim_mode;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[BODYLOC_RARM] = &pItem;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pItem);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Other unit types")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto class_id = random_unsigned_integer(0, 255);
			const auto anim_mode = random_unsigned_integer(0, 255);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type, class_id, anim_mode](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwClassId = class_id;
				pUnit.dwAnimMode = anim_mode;
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

		SUBCASE("nullptr")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FDC1120 (#10360)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetMeleeRange, dll_base + 0x00081120);
		
		SUBCASE("Player with equipped item")
		{
			// Every item is tested in both hands
			for (auto i = 0; i < items_record_count; ++i)
			for (const auto body_loc : { BODYLOC_RARM, BODYLOC_LARM })
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i, body_loc](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pItem
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[body_loc] = &pItem;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pItem);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Player without inventory")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
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

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				const auto anim_mode = random_unsigned_integer(0, NUMBER_OF_MONMODES - 1);

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i, anim_mode](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
					pUnit.dwAnimMode = anim_mode;
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

		SUBCASE("Other unit types")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1230 (#10364)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_TestCollisionByCoordinates, dll_base + 0x00081230);

		REPEAT_10();

		constexpr int room_size = 32;

		const auto room_x = random_unsigned_integer(0, 10000);
		const auto room_y = random_unsigned_integer(0, 10000);
		const auto x = room_x + random_unsigned_integer(4, room_size - 5);
		const auto y = room_y + random_unsigned_integer(4, room_size - 5);

		// Most of the subtiles do not have any collision, so that both blocked and free lines can occur
		uint16_t collision_mask[room_size * room_size]{};
		for (auto& mask : collision_mask)
		{
			mask = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer(0, 0xFFFF) : 0;
		}
		
		SUBCASE("Dynamic unit")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};
			int nX = room_x + random_unsigned_integer(4, room_size - 5);
			int nY = room_y + random_unsigned_integer(4, room_size - 5);
			int nFlags = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [room_size, room_x, room_y, x, y, &collision_mask](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
				pDynamicPath.pRoom = &pRoom;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit, original_pDynamicPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY, nFlags);
			const auto original_result = original(&original_pUnit, nX, nY, nFlags);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Object")
		{
			// Input data
			const auto size_x = random_unsigned_integer(0, 4);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2ObjectDataStrc moo_pObjectData{};
			D2ObjectsTxt moo_pObjectsTxtRecord{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2ObjectDataStrc original_pObjectData{};
			D2ObjectsTxt original_pObjectsTxtRecord{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};
			int nX = room_x + random_unsigned_integer(4, room_size - 5);
			int nY = room_y + random_unsigned_integer(4, room_size - 5);
			int nFlags = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [room_size, room_x, room_y, x, y, size_x, &collision_mask](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2ObjectDataStrc& pObjectData,
				D2ObjectsTxt& pObjectsTxtRecord,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit.dwUnitType = UNIT_OBJECT;
				pUnit.pStaticPath = &pStaticPath;
				pUnit.pObjectData = &pObjectData;
				pObjectData.pObjectTxt = &pObjectsTxtRecord;
				pObjectsTxtRecord.dwSizeX = size_x;
				pStaticPath.tGameCoords.nX = x;
				pStaticPath.tGameCoords.nY = y;
				pStaticPath.pRoom = &pRoom;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pObjectData, moo_pObjectsTxtRecord, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit, original_pStaticPath, original_pObjectData, original_pObjectsTxtRecord, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY, nFlags);
			const auto original_result = original(&original_pUnit, nX, nY, nFlags);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Without room")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nX = random_unsigned_integer(0, 10000);
			int nY = random_unsigned_integer(0, 10000);
			int nFlags = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [x, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY, nFlags);
			const auto original_result = original(&original_pUnit, nX, nY, nFlags);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("nullptr")
		{
			// Input data
			int nX = random_unsigned_integer(0, 10000);
			int nY = random_unsigned_integer(0, 10000);
			int nFlags = random_unsigned_integer(0, 0xFFFF);

			// Call both implementations
			const auto moo_result = sut(nullptr, nX, nY, nFlags);
			const auto original_result = original(nullptr, nX, nY, nFlags);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC13D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_TestCollision, dll_base + 0x000813D0);

		REPEAT_10();

		constexpr int room_size = 32;
		
		SUBCASE("With room")
		{
			// Input data
			const auto room_x = random_unsigned_integer(0, 10000);
			const auto room_y = random_unsigned_integer(0, 10000);

			// Most of the subtiles do not have any collision, so that both blocked and free lines can occur
			uint16_t collision_mask[room_size * room_size]{};
			for (auto& mask : collision_mask)
			{
				mask = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer(0, 0xFFFF) : 0;
			}

			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};
			int nX1 = room_x + random_unsigned_integer(4, room_size - 5);
			int nY1 = room_y + random_unsigned_integer(4, room_size - 5);
			int nSize1 = random_unsigned_integer(0, 4);
			int nX2 = room_x + random_unsigned_integer(4, room_size - 5);
			int nY2 = room_y + random_unsigned_integer(4, room_size - 5);
			int nSize2 = random_unsigned_integer(0, 4);
			int nCollisionMask = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [room_size, room_x, room_y, &collision_mask](
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(nX1, nY1, nSize1, nX2, nY2, nSize2, &moo_pRoom, nCollisionMask);
			const auto original_result = original(nX1, nY1, nSize1, nX2, nY2, nSize2, &original_pRoom, nCollisionMask);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}

		SUBCASE("Without room")
		{
			// Input data
			int nX1 = random_unsigned_integer(0, 10000);
			int nY1 = random_unsigned_integer(0, 10000);
			int nSize1 = random_unsigned_integer(0, 4);
			int nX2 = nX1 + random_unsigned_integer(0, 16) - 8;
			int nY2 = nY1 + random_unsigned_integer(0, 16) - 8;
			int nSize2 = random_unsigned_integer(0, 4);
			int nCollisionMask = random_unsigned_integer(0, 0xFFFF);

			// Call both implementations
			const auto moo_result = sut(nX1, nY1, nSize1, nX2, nY2, nSize2, nullptr, nCollisionMask);
			const auto original_result = original(nX1, nY1, nSize1, nX2, nY2, nSize2, nullptr, nCollisionMask);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC14C0 (#10362)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_TestCollisionWithUnit, dll_base + 0x000814C0);

		REPEAT_10();

		constexpr int room_size = 32;

		const auto room_x = random_unsigned_integer(0, 10000);
		const auto room_y = random_unsigned_integer(0, 10000);
		const auto x1 = room_x + random_unsigned_integer(4, room_size - 5);
		const auto y1 = room_y + random_unsigned_integer(4, room_size - 5);
		const auto x2 = room_x + random_unsigned_integer(4, room_size - 5);
		const auto y2 = room_y + random_unsigned_integer(4, room_size - 5);

		// Most of the subtiles do not have any collision, so that both blocked and free lines can occur
		uint16_t collision_mask[room_size * room_size]{};
		for (auto& mask : collision_mask)
		{
			mask = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer(0, 0xFFFF) : 0;
		}
		
		SUBCASE("Two players")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2DynamicPathStrc original_pDynamicPath2{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};
			int nCollisionMask = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [room_size, room_x, room_y, x1, y1, x2, y2, &collision_mask](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2DynamicPathStrc& pDynamicPath2,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pDynamicPath1.pRoom = &pRoom;

				pUnit2.dwUnitType = UNIT_PLAYER;
				pUnit2.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosX = x2;
				pDynamicPath2.tGameCoords.wPosY = y2;
				pDynamicPath2.pRoom = &pRoom;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, nCollisionMask);
			const auto original_result = original(&original_pUnit1, &original_pUnit2, nCollisionMask);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}

		SUBCASE("Player and item")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2StaticPathStrc original_pStaticPath2{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};
			int nCollisionMask = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [room_size, room_x, room_y, x1, y1, x2, y2, &collision_mask](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2StaticPathStrc& pStaticPath2,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pDynamicPath1.pRoom = &pRoom;

				pUnit2.dwUnitType = UNIT_ITEM;
				pUnit2.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
				pStaticPath2.tGameCoords.nY = y2;
				pStaticPath2.pRoom = &pRoom;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pStaticPath2, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pStaticPath2, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, nCollisionMask);
			const auto original_result = original(&original_pUnit1, &original_pUnit2, nCollisionMask);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}

		SUBCASE("Without room")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2DynamicPathStrc original_pDynamicPath2{};
			int nCollisionMask = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [x1, y1, x2, y2](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2DynamicPathStrc& pDynamicPath2
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pUnit2.dwUnitType = UNIT_PLAYER;
				pUnit2.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosX = x2;
				pDynamicPath2.tGameCoords.wPosY = y2;
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, nCollisionMask);
			const auto original_result = original(&original_pUnit1, &original_pUnit2, nCollisionMask);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1760")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_ToggleUnitFlag, dll_base + 0x00081760);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nFlag = GENERATE(1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768);
			BOOL bSet = GENERATE(0, 1);

			const auto setup_data = [flags](
				D2UnitStrc& pUnit
			) {
				pUnit.dwFlags = flags;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nFlag, bSet);
			original(&original_pUnit, nFlag, bSet);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1790 (#10363)" * doctest::skip("Needs checking"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_TestCollisionBetweenInteractingUnits, dll_base + 0x00081790);

		REPEAT_10();

		constexpr int room_size = 32;

		const auto room_x = random_unsigned_integer(0, 10000);
		const auto room_y = random_unsigned_integer(0, 10000);
		const auto x1 = room_x + random_unsigned_integer(4, room_size - 5);
		const auto y1 = room_y + random_unsigned_integer(4, room_size - 5);
		const auto x2 = room_x + random_unsigned_integer(4, room_size - 5);
		const auto y2 = room_y + random_unsigned_integer(4, room_size - 5);

		// Most of the subtiles do not have any collision, so that both blocked and free lines can occur
		uint16_t collision_mask[room_size * room_size]{};
		for (auto& mask : collision_mask)
		{
			mask = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer(0, 0xFFFF) : 0;
		}
		
		SUBCASE("Two players")
		{
			// Input data
			const auto anim_mode1 = random_unsigned_integer(0, NUMBER_OF_PLRMODES - 1);
			const auto collision_pattern1 = random_unsigned_integer(COLLISION_PATTERN_NONE, COLLISION_PATTERN_SMALL_NO_PRESENCE);
			const auto footprint_collision_mask1 = random_unsigned_integer(0, 0xFFFF);
			const auto anim_mode2 = random_unsigned_integer(0, NUMBER_OF_PLRMODES - 1);
			const auto collision_pattern2 = random_unsigned_integer(COLLISION_PATTERN_NONE, COLLISION_PATTERN_SMALL_NO_PRESENCE);
			const auto footprint_collision_mask2 = random_unsigned_integer(0, 0xFFFF);

			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2DynamicPathStrc original_pDynamicPath2{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};
			int nCollisionMask = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [room_size, room_x, room_y, x1, y1, x2, y2, anim_mode1, collision_pattern1, footprint_collision_mask1, anim_mode2, collision_pattern2, footprint_collision_mask2, &collision_mask](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2DynamicPathStrc& pDynamicPath2,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pDynamicPath1.pRoom = &pRoom;
				pUnit1.dwAnimMode = anim_mode1;
				pDynamicPath1.dwCollisionPattern = collision_pattern1;
				pDynamicPath1.nFootprintCollisionMask = footprint_collision_mask1;

				pUnit2.dwUnitType = UNIT_PLAYER;
				pUnit2.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosX = x2;
				pDynamicPath2.tGameCoords.wPosY = y2;
				pDynamicPath2.pRoom = &pRoom;
				pUnit2.dwAnimMode = anim_mode2;
				pDynamicPath2.dwCollisionPattern = collision_pattern2;
				pDynamicPath2.nFootprintCollisionMask = footprint_collision_mask2;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, nCollisionMask);
			const auto original_result = original(&original_pUnit1, &original_pUnit2, nCollisionMask);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");

			for (auto i = 0; i < room_size * room_size; ++i)
			{
				MOO_CHECK_EQ(moo_pCollisionMask[i], original_pCollisionMask[i], "Comparing pCollisionMask");
			}
		}

		SUBCASE("Player and item")
		{
			// Input data
			const auto anim_mode1 = random_unsigned_integer(0, NUMBER_OF_PLRMODES - 1);
			const auto collision_pattern1 = random_unsigned_integer(COLLISION_PATTERN_NONE, COLLISION_PATTERN_SMALL_NO_PRESENCE);
			const auto footprint_collision_mask1 = random_unsigned_integer(0, 0xFFFF);

			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2ActiveRoomStrc moo_pRoom{};
			D2RoomCollisionGridStrc moo_pCollisionGrid{};
			uint16_t moo_pCollisionMask[room_size * room_size]{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2StaticPathStrc original_pStaticPath2{};
			D2ActiveRoomStrc original_pRoom{};
			D2RoomCollisionGridStrc original_pCollisionGrid{};
			uint16_t original_pCollisionMask[room_size * room_size]{};
			int nCollisionMask = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [room_size, room_x, room_y, x1, y1, x2, y2, anim_mode1, collision_pattern1, footprint_collision_mask1, &collision_mask](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2StaticPathStrc& pStaticPath2,
				D2ActiveRoomStrc& pRoom,
				D2RoomCollisionGridStrc& pCollisionGrid,
				uint16_t(&pCollisionMask)[room_size * room_size]
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pDynamicPath1.pRoom = &pRoom;
				pUnit1.dwAnimMode = anim_mode1;
				pDynamicPath1.dwCollisionPattern = collision_pattern1;
				pDynamicPath1.nFootprintCollisionMask = footprint_collision_mask1;

				pUnit2.dwUnitType = UNIT_ITEM;
				pUnit2.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
				pStaticPath2.tGameCoords.nY = y2;
				pStaticPath2.pRoom = &pRoom;

				pRoom.tCoords.nSubtileX = room_x;
				pRoom.tCoords.nSubtileY = room_y;
				pRoom.tCoords.nSubtileWidth = room_size;
				pRoom.tCoords.nSubtileHeight = room_size;
				pRoom.pCollisionGrid = &pCollisionGrid;

				pCollisionGrid.pRoomCoords = pRoom.tCoords;
				pCollisionGrid.pCollisionMask = pCollisionMask;
				std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pStaticPath2, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pStaticPath2, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, nCollisionMask);
			const auto original_result = original(&original_pUnit1, &original_pUnit2, nCollisionMask);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");

			for (auto i = 0; i < room_size * room_size; ++i)
			{
				MOO_CHECK_EQ(moo_pCollisionMask[i], original_pCollisionMask[i], "Comparing pCollisionMask");
			}
		}

		SUBCASE("Without room")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2DynamicPathStrc original_pDynamicPath2{};
			int nCollisionMask = random_unsigned_integer(0, 0xFFFF);

			const auto setup_data = [x1, y1, x2, y2](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2DynamicPathStrc& pDynamicPath2
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pUnit2.dwUnitType = UNIT_PLAYER;
				pUnit2.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosX = x2;
				pDynamicPath2.tGameCoords.wPosY = y2;
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, nCollisionMask);
			const auto original_result = original(&original_pUnit1, &original_pUnit2, nCollisionMask);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDC1A70 (#10361)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsInMeleeRange, dll_base + 0x00081A70);

		constexpr int room_size = 32;

		const auto room_x = random_unsigned_integer(0, 10000);
		const auto room_y = random_unsigned_integer(0, 10000);

		// Most of the subtiles do not have any collision, so that both blocked and free lines can occur
		uint16_t collision_mask[room_size * room_size]{};
		for (auto& mask : collision_mask)
		{
			mask = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer(0, 0xFFFF) : 0;
		}

		SUBCASE("Player attacking monster")
		{
			// The player does not have an inventory, so its melee range is 0
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				const auto anim_mode = random_unsigned_integer(0, NUMBER_OF_MONMODES - 1);

				// Both units are close to each other, so that they can be in melee range
				const auto x1 = room_x + random_unsigned_integer(10, room_size - 11);
				const auto y1 = room_y + random_unsigned_integer(10, room_size - 11);
				const auto x2 = x1 + random_unsigned_integer(0, 12) - 6;
				const auto y2 = y1 + random_unsigned_integer(0, 12) - 6;

				D2UnitStrc moo_pUnit1{};
				D2DynamicPathStrc moo_pDynamicPath1{};
				D2UnitStrc moo_pUnit2{};
				D2DynamicPathStrc moo_pDynamicPath2{};
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[room_size * room_size]{};
				D2UnitStrc original_pUnit1{};
				D2DynamicPathStrc original_pDynamicPath1{};
				D2UnitStrc original_pUnit2{};
				D2DynamicPathStrc original_pDynamicPath2{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[room_size * room_size]{};
				int nRangeBonus = random_unsigned_integer(0, 5);

				const auto setup_data = [i, anim_mode, room_size, room_x, room_y, x1, y1, x2, y2, &collision_mask](
					D2UnitStrc& pUnit1,
					D2DynamicPathStrc& pDynamicPath1,
					D2UnitStrc& pUnit2,
					D2DynamicPathStrc& pDynamicPath2,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[room_size * room_size]
				) {
					pUnit1.dwUnitType = UNIT_PLAYER;
					pUnit1.pDynamicPath = &pDynamicPath1;
					pDynamicPath1.tGameCoords.wPosX = x1;
					pDynamicPath1.tGameCoords.wPosY = y1;
					pDynamicPath1.pRoom = &pRoom;

					pUnit2.dwUnitType = UNIT_MONSTER;
					pUnit2.dwClassId = i;
					pUnit2.dwAnimMode = anim_mode;
					pUnit2.pDynamicPath = &pDynamicPath2;
					pDynamicPath2.tGameCoords.wPosX = x2;
					pDynamicPath2.tGameCoords.wPosY = y2;
					pDynamicPath2.pRoom = &pRoom;

					pRoom.tCoords.nSubtileX = room_x;
					pRoom.tCoords.nSubtileY = room_y;
					pRoom.tCoords.nSubtileWidth = room_size;
					pRoom.tCoords.nSubtileHeight = room_size;
					pRoom.pCollisionGrid = &pCollisionGrid;

					pCollisionGrid.pRoomCoords = pRoom.tCoords;
					pCollisionGrid.pCollisionMask = pCollisionMask;
					std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
				};

				setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, nRangeBonus);
				const auto original_result = original(&original_pUnit1, &original_pUnit2, nRangeBonus);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
				MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
			}
		}

		SUBCASE("Monster attacking player")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				const auto anim_mode = random_unsigned_integer(0, NUMBER_OF_MONMODES - 1);

				// Both units are close to each other, so that they can be in melee range
				const auto x1 = room_x + random_unsigned_integer(10, room_size - 11);
				const auto y1 = room_y + random_unsigned_integer(10, room_size - 11);
				const auto x2 = x1 + random_unsigned_integer(0, 12) - 6;
				const auto y2 = y1 + random_unsigned_integer(0, 12) - 6;

				D2UnitStrc moo_pUnit1{};
				D2DynamicPathStrc moo_pDynamicPath1{};
				D2UnitStrc moo_pUnit2{};
				D2DynamicPathStrc moo_pDynamicPath2{};
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				uint16_t moo_pCollisionMask[room_size * room_size]{};
				D2UnitStrc original_pUnit1{};
				D2DynamicPathStrc original_pDynamicPath1{};
				D2UnitStrc original_pUnit2{};
				D2DynamicPathStrc original_pDynamicPath2{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				uint16_t original_pCollisionMask[room_size * room_size]{};
				int nRangeBonus = random_unsigned_integer(0, 5);

				const auto setup_data = [i, anim_mode, room_size, room_x, room_y, x1, y1, x2, y2, &collision_mask](
					D2UnitStrc& pUnit1,
					D2DynamicPathStrc& pDynamicPath1,
					D2UnitStrc& pUnit2,
					D2DynamicPathStrc& pDynamicPath2,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					uint16_t(&pCollisionMask)[room_size * room_size]
				) {
					pUnit1.dwUnitType = UNIT_MONSTER;
					pUnit1.dwClassId = i;
					pUnit1.dwAnimMode = anim_mode;
					pUnit1.pDynamicPath = &pDynamicPath1;
					pDynamicPath1.tGameCoords.wPosX = x1;
					pDynamicPath1.tGameCoords.wPosY = y1;
					pDynamicPath1.pRoom = &pRoom;

					pUnit2.dwUnitType = UNIT_PLAYER;
					pUnit2.pDynamicPath = &pDynamicPath2;
					pDynamicPath2.tGameCoords.wPosX = x2;
					pDynamicPath2.tGameCoords.wPosY = y2;
					pDynamicPath2.pRoom = &pRoom;

					pRoom.tCoords.nSubtileX = room_x;
					pRoom.tCoords.nSubtileY = room_y;
					pRoom.tCoords.nSubtileWidth = room_size;
					pRoom.tCoords.nSubtileHeight = room_size;
					pRoom.pCollisionGrid = &pCollisionGrid;

					pCollisionGrid.pRoomCoords = pRoom.tCoords;
					pCollisionGrid.pCollisionMask = pCollisionMask;
					std::memcpy(pCollisionMask, collision_mask, sizeof(collision_mask));
				};

				setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, nRangeBonus);
				const auto original_result = original(&original_pUnit1, &original_pUnit2, nRangeBonus);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
				MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
			}
		}

		SUBCASE("nullptr")
		{
			// Input data
			int nRangeBonus = random_unsigned_integer(0, 5);

			// Call both implementations
			const auto moo_result = sut(nullptr, nullptr, nRangeBonus);
			const auto original_result = original(nullptr, nullptr, nRangeBonus);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDC1B40 (#10318)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsInMovingMode, dll_base + 0x00081B40);
		
		SUBCASE("UNIT_PLAYER")
		{
			for (auto i = 0; i < NUMBER_OF_PLRMODES; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwAnimMode = i;
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

		SUBCASE("UNIT_MONSTER")
		{
			for (auto j = 0; j < monstats_record_count; ++j)
			{
				for (auto i = 0; i < NUMBER_OF_MONMODES; ++i)
				{
					// Input data
					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};

					const auto setup_data = [i, j](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = j;
						pUnit.dwAnimMode = i;
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

		SUBCASE("Others, not UNIT_MISSILE")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
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
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDC1C30 (#10319)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsInMovingModeEx, dll_base + 0x00081C30);
		
		SUBCASE("UNIT_PLAYER")
		{
			for (auto i = 0; i < NUMBER_OF_PLRMODES; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwAnimMode = i;
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

		SUBCASE("UNIT_MONSTER")
		{
			for (auto j = 0; j < monstats_record_count; ++j)
			{
				for (auto i = 0; i < NUMBER_OF_MONMODES; ++i)
				{
					// Input data
					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};

					const auto setup_data = [i, j](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = j;
						pUnit.dwAnimMode = i;
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

		SUBCASE("Others, not UNIT_MISSILE")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
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
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>>>, "D2Common.0x6FDC1C50 (#10365)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetHitClass, dll_base + 0x00081C50);

		SUBCASE("Player with equipped item")
		{
			const auto class_id = GENERATE(PCLASS_AMAZON, PCLASS_SORCERESS, PCLASS_NECROMANCER, PCLASS_PALADIN, PCLASS_BARBARIAN, PCLASS_DRUID, PCLASS_ASSASSIN);

			// Every item is tested in both hands
			for (auto i = 0; i < items_record_count; ++i)
			for (const auto body_loc : { BODYLOC_RARM, BODYLOC_LARM })
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i, body_loc, class_id](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pItem
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[body_loc] = &pItem;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pItem);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Player without inventory")
		{
			// Input data
			const auto class_id = GENERATE(PCLASS_AMAZON, PCLASS_SORCERESS, PCLASS_NECROMANCER, PCLASS_PALADIN, PCLASS_BARBARIAN, PCLASS_DRUID, PCLASS_ASSASSIN);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [class_id](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = class_id;
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

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
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

		SUBCASE("Other unit types")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
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

		SUBCASE("nullptr")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FDC1CE0 (#10366)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetWeaponClass, dll_base + 0x00081CE0);

		SUBCASE("Player with equipped item")
		{
			const auto class_id = GENERATE(PCLASS_AMAZON, PCLASS_SORCERESS, PCLASS_NECROMANCER, PCLASS_PALADIN, PCLASS_BARBARIAN, PCLASS_DRUID, PCLASS_ASSASSIN);

			// Every item is tested in both hands
			for (auto i = 0; i < items_record_count; ++i)
			for (const auto body_loc : { BODYLOC_RARM, BODYLOC_LARM })
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pItem{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pItem{};

				const auto setup_data = [i, body_loc, class_id](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pItem
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[body_loc] = &pItem;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pItem);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pItem);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}

		SUBCASE("Player without inventory")
		{
			// Input data
			const auto class_id = GENERATE(PCLASS_AMAZON, PCLASS_SORCERESS, PCLASS_NECROMANCER, PCLASS_PALADIN, PCLASS_BARBARIAN, PCLASS_DRUID, PCLASS_ASSASSIN);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [class_id](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = class_id;
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

		SUBCASE("Other unit types without inventory")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
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
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDC1D00 (#10438)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetHealingCost, dll_base + 0x00081D00);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			const auto max_hp = random_unsigned_integer(256, 65535);
			const auto hp = random_unsigned_integer(256, max_hp);
			const auto max_mana = random_unsigned_integer(256, 65535);
			const auto mana = random_unsigned_integer(256, max_mana);
			const auto level = random_unsigned_integer(1, 100);

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pStat[5]{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pStat[5]{};

			const auto setup_data = [max_hp, hp, max_mana, mana, level](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatStrc(&pStat)[5]
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.FullStats.pStat = pStat;
				pStatListEx.FullStats.nStatCount = 5;
				pStat[0].nStat = STAT_HITPOINTS;
				pStat[0].nValue = hp;
				pStat[1].nStat = STAT_MAXHP;
				pStat[1].nValue = max_hp;
				pStat[2].nStat = STAT_MANA;
				pStat[2].nValue = mana;
				pStat[3].nStat = STAT_MAXMANA;
				pStat[3].nValue = max_mana;
				pStat[4].nStat = STAT_LEVEL;
				pStat[4].nValue = level;
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
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDC1D90 (#10439)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetInventoryGoldLimit, dll_base + 0x00081D90);
		
		SUBCASE("")
		{
			// Input data
			const auto level = random_unsigned_integer(1, 100);

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pStat{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pStat{};

			const auto setup_data = [level](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatStrc& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.FullStats.pStat = &pStat;
				pStatListEx.FullStats.nStatCount = 1;
				pStat.nStat = STAT_LEVEL;
				pStat.nValue = level;
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
		}
	}
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FDC1DB0 (#10440)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_MergeDualWieldWeaponStatLists, dll_base + 0x00081DB0);
		
		SUBCASE("Unit which cannot dual wield")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_TILE);
			const auto class_id = random_unsigned_integer(0, 1) ? PCLASS_AMAZON : PCLASS_SORCERESS;

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int a2 = random_unsigned_integer(0, 1);

			const auto setup_data = [unit_type, class_id](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.dwClassId = class_id;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, a2);
			original(&original_pUnit, a2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Unit which can dual wield, without inventory")
		{
			// Input data
			const auto class_id = GENERATE(PCLASS_BARBARIAN, PCLASS_ASSASSIN);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int a2 = random_unsigned_integer(0, 1);

			const auto setup_data = [class_id](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.dwClassId = class_id;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, a2);
			original(&original_pUnit, a2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("Unit which can dual wield, with equipped items")
		{
			// Input data
			const auto class_id = GENERATE(PCLASS_BARBARIAN, PCLASS_ASSASSIN);

			// The items do not have stat lists, so none of them are merged into the unit's stats
			for (auto iteration = 0; iteration < 100; ++iteration)
			{
				const auto right_hand_item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto left_hand_item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto right_hand_item_id = random_unsigned_integer(0, 1000);
				const auto left_hand_item_id = random_unsigned_integer(1001, 2000);
				const auto left_item_guid_choice = random_unsigned_integer(0, 2);
				const auto left_item_guid = left_item_guid_choice == 0 ? D2UnitInvalidGUID : left_item_guid_choice == 1 ? right_hand_item_id : left_hand_item_id;

				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pRightHandItem{};
				D2UnitStrc moo_pLeftHandItem{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pRightHandItem{};
				D2UnitStrc original_pLeftHandItem{};
				int a2 = random_unsigned_integer(0, 1);

				const auto setup_data = [class_id, right_hand_item_class_id, left_hand_item_class_id, right_hand_item_id, left_hand_item_id, left_item_guid](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pRightHandItem,
					D2UnitStrc& pLeftHandItem
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = left_item_guid;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[BODYLOC_RARM] = &pRightHandItem;
					pBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;
					pRightHandItem.dwUnitType = UNIT_ITEM;
					pRightHandItem.dwClassId = right_hand_item_class_id;
					pRightHandItem.dwUnitId = right_hand_item_id;
					pLeftHandItem.dwUnitType = UNIT_ITEM;
					pLeftHandItem.dwClassId = left_hand_item_class_id;
					pLeftHandItem.dwUnitId = left_hand_item_id;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pRightHandItem, moo_pLeftHandItem);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pRightHandItem, original_pLeftHandItem);

				// Call both implementations
				sut(&moo_pUnit, a2);
				original(&original_pUnit, a2);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pRightHandItem, original_pRightHandItem, "Comparing pRightHandItem");
				MOO_CHECK_EQ(moo_pLeftHandItem, original_pLeftHandItem, "Comparing pLeftHandItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<NoopFixture>, "D2Common.0x6FDC1EE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetMonStats2TxtRecord, dll_base + 0x00081EE0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < monstats2_record_count; ++i)
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
	
	TEST_CASE_FIXTURE(ItemsTxtFixture<ItemTypesTxtFixture<NoopFixture>>, "D2Common.0x6FDC1F10 (#10442)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetItemComponentId, dll_base + 0x00081F10);
		
		SUBCASE("Item not held in a hand")
		{
			const auto body_loc = GENERATE(BODYLOC_NONE, BODYLOC_HEAD, BODYLOC_NECK, BODYLOC_TORSO, BODYLOC_RRIN, BODYLOC_LRIN, BODYLOC_BELT, BODYLOC_FEET, BODYLOC_GLOVES, BODYLOC_SWRARM, BODYLOC_SWLARM);

			for (auto i = 0; i < items_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc moo_pItem{};
				D2ItemDataStrc moo_pItemData{};
				D2UnitStrc original_pUnit{};
				D2UnitStrc original_pItem{};
				D2ItemDataStrc original_pItemData{};

				const auto setup_data = [i, body_loc](
					D2UnitStrc& pUnit,
					D2UnitStrc& pItem,
					D2ItemDataStrc& pItemData
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pItem.dwUnitType = UNIT_ITEM;
					pItem.dwClassId = i;
					pItem.pItemData = &pItemData;
					pItemData.nBodyLoc = body_loc;
				};

				setup_data(moo_pUnit, moo_pItem, moo_pItemData);
				setup_data(original_pUnit, original_pItem, original_pItemData);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pItem);
				const auto original_result = original(&original_pUnit, &original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}

		SUBCASE("Player with items in both hands")
		{
			const auto class_id = GENERATE(PCLASS_AMAZON, PCLASS_SORCERESS, PCLASS_NECROMANCER, PCLASS_PALADIN, PCLASS_BARBARIAN, PCLASS_DRUID, PCLASS_ASSASSIN);

			for (auto iteration = 0; iteration < 100; ++iteration)
			{
				// Input data
				const auto right_hand_item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto left_hand_item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto right_hand_item_flags = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer() : 0;
				const auto left_hand_item_flags = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer() : 0;
				const auto right_hand_item_id = random_unsigned_integer(0, 1000);
				const auto left_hand_item_id = random_unsigned_integer(1001, 2000);
				const auto left_item_guid_choice = random_unsigned_integer(0, 2);
				const auto left_item_guid = left_item_guid_choice == 0 ? D2UnitInvalidGUID : left_item_guid_choice == 1 ? right_hand_item_id : left_hand_item_id;
				const auto use_right_hand_item = random_unsigned_integer(0, 1);

				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pRightHandItem{};
				D2ItemDataStrc moo_pRightHandItemData{};
				D2UnitStrc moo_pLeftHandItem{};
				D2ItemDataStrc moo_pLeftHandItemData{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pRightHandItem{};
				D2ItemDataStrc original_pRightHandItemData{};
				D2UnitStrc original_pLeftHandItem{};
				D2ItemDataStrc original_pLeftHandItemData{};

				const auto setup_data = [class_id, right_hand_item_class_id, left_hand_item_class_id, right_hand_item_flags, left_hand_item_flags, right_hand_item_id, left_hand_item_id, left_item_guid](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pRightHandItem,
					D2ItemDataStrc& pRightHandItemData,
					D2UnitStrc& pLeftHandItem,
					D2ItemDataStrc& pLeftHandItemData
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = left_item_guid;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[BODYLOC_RARM] = &pRightHandItem;
					pBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;

					pRightHandItem.dwUnitType = UNIT_ITEM;
					pRightHandItem.dwClassId = right_hand_item_class_id;
					pRightHandItem.dwUnitId = right_hand_item_id;
					pRightHandItem.pItemData = &pRightHandItemData;
					pRightHandItemData.nBodyLoc = BODYLOC_RARM;
					pRightHandItemData.dwItemFlags = right_hand_item_flags;

					pLeftHandItem.dwUnitType = UNIT_ITEM;
					pLeftHandItem.dwClassId = left_hand_item_class_id;
					pLeftHandItem.dwUnitId = left_hand_item_id;
					pLeftHandItem.pItemData = &pLeftHandItemData;
					pLeftHandItemData.nBodyLoc = BODYLOC_LARM;
					pLeftHandItemData.dwItemFlags = left_hand_item_flags;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pRightHandItem, moo_pRightHandItemData, moo_pLeftHandItem, moo_pLeftHandItemData);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pRightHandItem, original_pRightHandItemData, original_pLeftHandItem, original_pLeftHandItemData);

				auto& moo_pItem = use_right_hand_item ? moo_pRightHandItem : moo_pLeftHandItem;
				auto& original_pItem = use_right_hand_item ? original_pRightHandItem : original_pLeftHandItem;

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pItem);
				const auto original_result = original(&original_pUnit, &original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}

		SUBCASE("Monster with items in both hands")
		{
			const auto class_id = GENERATE(MONSTER_SKELETON1, MONSTER_SHADOWWARRIOR, MONSTER_SHADOWMASTER);

			for (auto iteration = 0; iteration < 100; ++iteration)
			{
				// Input data
				const auto right_hand_item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto left_hand_item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto right_hand_item_flags = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer() : 0;
				const auto left_hand_item_flags = random_unsigned_integer(0, 3) == 0 ? random_unsigned_integer() : 0;
				const auto right_hand_item_id = random_unsigned_integer(0, 1000);
				const auto left_hand_item_id = random_unsigned_integer(1001, 2000);
				const auto left_item_guid_choice = random_unsigned_integer(0, 2);
				const auto left_item_guid = left_item_guid_choice == 0 ? D2UnitInvalidGUID : left_item_guid_choice == 1 ? right_hand_item_id : left_hand_item_id;
				const auto use_right_hand_item = random_unsigned_integer(0, 1);

				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pRightHandItem{};
				D2ItemDataStrc moo_pRightHandItemData{};
				D2UnitStrc moo_pLeftHandItem{};
				D2ItemDataStrc moo_pLeftHandItemData{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pRightHandItem{};
				D2ItemDataStrc original_pRightHandItemData{};
				D2UnitStrc original_pLeftHandItem{};
				D2ItemDataStrc original_pLeftHandItemData{};

				const auto setup_data = [class_id, right_hand_item_class_id, left_hand_item_class_id, right_hand_item_flags, left_hand_item_flags, right_hand_item_id, left_hand_item_id, left_item_guid](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pRightHandItem,
					D2ItemDataStrc& pRightHandItemData,
					D2UnitStrc& pLeftHandItem,
					D2ItemDataStrc& pLeftHandItemData
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = class_id;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pOwner = &pUnit;
					pInventory.dwLeftItemGUID = left_item_guid;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[BODYLOC_RARM] = &pRightHandItem;
					pBodyLocItems[BODYLOC_LARM] = &pLeftHandItem;

					pRightHandItem.dwUnitType = UNIT_ITEM;
					pRightHandItem.dwClassId = right_hand_item_class_id;
					pRightHandItem.dwUnitId = right_hand_item_id;
					pRightHandItem.pItemData = &pRightHandItemData;
					pRightHandItemData.nBodyLoc = BODYLOC_RARM;
					pRightHandItemData.dwItemFlags = right_hand_item_flags;

					pLeftHandItem.dwUnitType = UNIT_ITEM;
					pLeftHandItem.dwClassId = left_hand_item_class_id;
					pLeftHandItem.dwUnitId = left_hand_item_id;
					pLeftHandItem.pItemData = &pLeftHandItemData;
					pLeftHandItemData.nBodyLoc = BODYLOC_LARM;
					pLeftHandItemData.dwItemFlags = left_hand_item_flags;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pRightHandItem, moo_pRightHandItemData, moo_pLeftHandItem, moo_pLeftHandItemData);
				setup_data(original_pUnit, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pRightHandItem, original_pRightHandItemData, original_pLeftHandItem, original_pLeftHandItemData);

				auto& moo_pItem = use_right_hand_item ? moo_pRightHandItem : moo_pLeftHandItem;
				auto& original_pItem = use_right_hand_item ? original_pRightHandItem : original_pLeftHandItem;

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pItem);
				const auto original_result = original(&original_pUnit, &original_pItem);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDC1FE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetMonStats2TxtRecordFromMonsterId, dll_base + 0x00081FE0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				int nMonsterId = i;

				// Call both implementations
				const auto moo_result = sut(nMonsterId);
				const auto original_result = original(nMonsterId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDC2030 (#10443)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_InitRightSkill, dll_base + 0x00082030);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				const auto unit_id = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2PlayerDataStrc moo_pPlayerData{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pRightSkill{};
				D2UnitStrc original_pUnit{};
				D2PlayerDataStrc original_pPlayerData{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pRightSkill{};

				const auto setup_data = [this, unit_id, i](
					D2UnitStrc& pUnit,
					D2PlayerDataStrc& pPlayerData,
					D2SkillListStrc& pSkillList,
					D2SkillStrc& pRightSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = unit_id;
					pUnit.pPlayerData = &pPlayerData;
					pUnit.pSkills = &pSkillList;
					pSkillList.pRightSkill = &pRightSkill;
					pRightSkill.nOwnerGUID = unit_id;
					pRightSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pUnit, moo_pPlayerData, moo_pSkillList, moo_pRightSkill);
				setup_data(original_pUnit, original_pPlayerData, original_pSkillList, original_pRightSkill);

				// Call both implementations
				sut(&moo_pUnit);
				original(&original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDC20A0 (#10444)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_InitLeftSkill, dll_base + 0x000820A0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				const auto unit_id = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2PlayerDataStrc moo_pPlayerData{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pLeftSkill{};
				D2UnitStrc original_pUnit{};
				D2PlayerDataStrc original_pPlayerData{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pLeftSkill{};

				const auto setup_data = [this, unit_id, i](
					D2UnitStrc& pUnit,
					D2PlayerDataStrc& pPlayerData,
					D2SkillListStrc& pSkillList,
					D2SkillStrc& pLeftSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = unit_id;
					pUnit.pPlayerData = &pPlayerData;
					pUnit.pSkills = &pSkillList;
					pSkillList.pLeftSkill = &pLeftSkill;
					pLeftSkill.nOwnerGUID = unit_id;
					pLeftSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pUnit, moo_pPlayerData, moo_pSkillList, moo_pLeftSkill);
				setup_data(original_pUnit, original_pPlayerData, original_pSkillList, original_pLeftSkill);

				// Call both implementations
				sut(&moo_pUnit);
				original(&original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDC2110 (#10445)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_InitSwitchRightSkill, dll_base + 0x00082110);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				const auto unit_id = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2PlayerDataStrc moo_pPlayerData{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pRightSkill{};
				D2UnitStrc original_pUnit{};
				D2PlayerDataStrc original_pPlayerData{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pRightSkill{};

				const auto setup_data = [this, unit_id, i](
					D2UnitStrc& pUnit,
					D2PlayerDataStrc& pPlayerData,
					D2SkillListStrc& pSkillList,
					D2SkillStrc& pRightSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = unit_id;
					pUnit.pPlayerData = &pPlayerData;
					pUnit.pSkills = &pSkillList;
					pSkillList.pRightSkill = &pRightSkill;
					pRightSkill.nOwnerGUID = unit_id;
					pRightSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pUnit, moo_pPlayerData, moo_pSkillList, moo_pRightSkill);
				setup_data(original_pUnit, original_pPlayerData, original_pSkillList, original_pRightSkill);

				// Call both implementations
				sut(&moo_pUnit);
				original(&original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDC2180 (#10446)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_InitSwitchLeftSkill, dll_base + 0x00082180);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				const auto unit_id = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2PlayerDataStrc moo_pPlayerData{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pLeftSkill{};
				D2UnitStrc original_pUnit{};
				D2PlayerDataStrc original_pPlayerData{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pLeftSkill{};

				const auto setup_data = [this, unit_id, i](
					D2UnitStrc& pUnit,
					D2PlayerDataStrc& pPlayerData,
					D2SkillListStrc& pSkillList,
					D2SkillStrc& pLeftSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = unit_id;
					pUnit.pPlayerData = &pPlayerData;
					pUnit.pSkills = &pSkillList;
					pSkillList.pLeftSkill = &pLeftSkill;
					pLeftSkill.nOwnerGUID = unit_id;
					pLeftSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pUnit, moo_pPlayerData, moo_pSkillList, moo_pLeftSkill);
				setup_data(original_pUnit, original_pPlayerData, original_pSkillList, original_pLeftSkill);

				// Call both implementations
				sut(&moo_pUnit);
				original(&original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC21F0 (#10447)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetRightSkillData, dll_base + 0x000821F0);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_id = random_unsigned_integer();
			const auto skill_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			int moo_pRightSkillId{};
			int moo_pRightSkillFlags{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int original_pRightSkillId{};
			int original_pRightSkillFlags{};

			const auto setup_data = [skill_id, skill_flags](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData,
				int& pRightSkillId,
				int& pRightSkillFlags
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pPlayerData.nRightSkillId = skill_id;
				pPlayerData.nRightSkillFlags = skill_flags;
			};

			setup_data(moo_pUnit, moo_pPlayerData, moo_pRightSkillId, moo_pRightSkillFlags);
			setup_data(original_pUnit, original_pPlayerData, original_pRightSkillId, original_pRightSkillFlags);

			// Call both implementations
			sut(&moo_pUnit, &moo_pRightSkillId, &moo_pRightSkillFlags);
			original(&original_pUnit, &original_pRightSkillId, &original_pRightSkillFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pRightSkillId, original_pRightSkillId, "Comparing pRightSkillId");
			MOO_CHECK_EQ(moo_pRightSkillFlags, original_pRightSkillFlags, "Comparing pRightSkillFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2250 (#10448)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetLeftSkillData, dll_base + 0x00082250);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_id = random_unsigned_integer();
			const auto skill_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			int moo_pLeftSkillId{};
			int moo_pLeftSkillFlags{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int original_pLeftSkillId{};
			int original_pLeftSkillFlags{};

			const auto setup_data = [skill_id, skill_flags](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData,
				int& pLeftSkillId,
				int& pLeftSkillFlags
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pPlayerData.nLeftSkillId = skill_id;
				pPlayerData.nLeftSkillFlags = skill_flags;
			};

			setup_data(moo_pUnit, moo_pPlayerData, moo_pLeftSkillId, moo_pLeftSkillFlags);
			setup_data(original_pUnit, original_pPlayerData, original_pLeftSkillId, original_pLeftSkillFlags);

			// Call both implementations
			sut(&moo_pUnit, &moo_pLeftSkillId, &moo_pLeftSkillFlags);
			original(&original_pUnit, &original_pLeftSkillId, &original_pLeftSkillFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pLeftSkillId, original_pLeftSkillId, "Comparing pLeftSkillId");
			MOO_CHECK_EQ(moo_pLeftSkillFlags, original_pLeftSkillFlags, "Comparing pLeftSkillFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC22B0 (#10449)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetSwitchRightSkillDataResetRightSkill, dll_base + 0x000822B0);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_id = random_unsigned_integer();
			const auto skill_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			int moo_pSwitchRightSkillId{};
			int moo_pSwitchRightSkillFlags{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int original_pSwitchRightSkillId{};
			int original_pSwitchRightSkillFlags{};

			const auto setup_data = [skill_id, skill_flags](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData,
				int& pSwitchRightSkillId,
				int& pSwitchRightSkillFlags
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pPlayerData.nSwitchRightSkillId = skill_id;
				pPlayerData.nSwitchRightSkillFlags = skill_flags;

				pPlayerData.nRightSkillId = random_unsigned_integer();
				pPlayerData.nRightSkillFlags = random_unsigned_integer();
				pPlayerData.nWeaponGUID = random_unsigned_integer();
				pPlayerData.unk0x94 = random_unsigned_integer();
			};

			setup_data(moo_pUnit, moo_pPlayerData, moo_pSwitchRightSkillId, moo_pSwitchRightSkillFlags);
			setup_data(original_pUnit, original_pPlayerData, original_pSwitchRightSkillId, original_pSwitchRightSkillFlags);

			// Call both implementations
			sut(&moo_pUnit, &moo_pSwitchRightSkillId, &moo_pSwitchRightSkillFlags);
			original(&original_pUnit, &original_pSwitchRightSkillId, &original_pSwitchRightSkillFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pSwitchRightSkillId, original_pSwitchRightSkillId, "Comparing pSwitchRightSkillId");
			MOO_CHECK_EQ(moo_pSwitchRightSkillFlags, original_pSwitchRightSkillFlags, "Comparing pSwitchRightSkillFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2330 (#10450)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetSwitchLeftSkillDataResetLeftSkill, dll_base + 0x00082330);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_id = random_unsigned_integer();
			const auto skill_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			int moo_pSwitchLeftSkillId{};
			int moo_pSwitchLeftSkillFlags{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int original_pSwitchLeftSkillId{};
			int original_pSwitchLeftSkillFlags{};

			const auto setup_data = [skill_id, skill_flags](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData,
				int& pSwitchLeftSkillId,
				int& pSwitchLeftSkillFlags
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pPlayerData.nSwitchLeftSkillId = skill_id;
				pPlayerData.nSwitchLeftSkillFlags = skill_flags;

				pPlayerData.nLeftSkillId = random_unsigned_integer();
				pPlayerData.nLeftSkillFlags = random_unsigned_integer();
				pPlayerData.nWeaponGUID = random_unsigned_integer();
				pPlayerData.unk0x94 = random_unsigned_integer();
			};

			setup_data(moo_pUnit, moo_pPlayerData, moo_pSwitchLeftSkillId, moo_pSwitchLeftSkillFlags);
			setup_data(original_pUnit, original_pPlayerData, original_pSwitchLeftSkillId, original_pSwitchLeftSkillFlags);

			// Call both implementations
			sut(&moo_pUnit, &moo_pSwitchLeftSkillId, &moo_pSwitchLeftSkillFlags);
			original(&original_pUnit, &original_pSwitchLeftSkillId, &original_pSwitchLeftSkillFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pSwitchLeftSkillId, original_pSwitchLeftSkillId, "Comparing pSwitchLeftSkillId");
			MOO_CHECK_EQ(moo_pSwitchLeftSkillFlags, original_pSwitchLeftSkillFlags, "Comparing pSwitchLeftSkillFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC23B0 (#10451)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetSwitchLeftSkillData, dll_base + 0x000823B0);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_id = random_unsigned_integer();
			const auto skill_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			int moo_pSwitchLeftSkillId{};
			int moo_pSwitchLeftSkillFlags{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int original_pSwitchLeftSkillId{};
			int original_pSwitchLeftSkillFlags{};

			const auto setup_data = [skill_id, skill_flags](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData,
				int& pSwitchLeftSkillId,
				int& pSwitchLeftSkillFlags
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pPlayerData.nSwitchLeftSkillId = skill_id;
				pPlayerData.nSwitchLeftSkillFlags = skill_flags;
			};

			setup_data(moo_pUnit, moo_pPlayerData, moo_pSwitchLeftSkillId, moo_pSwitchLeftSkillFlags);
			setup_data(original_pUnit, original_pPlayerData, original_pSwitchLeftSkillId, original_pSwitchLeftSkillFlags);

			// Call both implementations
			sut(&moo_pUnit, &moo_pSwitchLeftSkillId, &moo_pSwitchLeftSkillFlags);
			original(&original_pUnit, &original_pSwitchLeftSkillId, &original_pSwitchLeftSkillFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pSwitchLeftSkillId, original_pSwitchLeftSkillId, "Comparing pSwitchLeftSkillId");
			MOO_CHECK_EQ(moo_pSwitchLeftSkillFlags, original_pSwitchLeftSkillFlags, "Comparing pSwitchLeftSkillFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2420 (#10452)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetSwitchRightSkillData, dll_base + 0x00082420);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_id = random_unsigned_integer();
			const auto skill_flags = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			int moo_pSwitchRightSkillId{};
			int moo_pSwitchRightSkillFlags{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int original_pSwitchRightSkillId{};
			int original_pSwitchRightSkillFlags{};

			const auto setup_data = [skill_id, skill_flags](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData,
				int& pSwitchRightSkillId,
				int& pSwitchRightSkillFlags
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pPlayerData.nSwitchRightSkillId = skill_id;
				pPlayerData.nSwitchRightSkillFlags = skill_flags;
			};

			setup_data(moo_pUnit, moo_pPlayerData, moo_pSwitchRightSkillId, moo_pSwitchRightSkillFlags);
			setup_data(original_pUnit, original_pPlayerData, original_pSwitchRightSkillId, original_pSwitchRightSkillFlags);

			// Call both implementations
			sut(&moo_pUnit, &moo_pSwitchRightSkillId, &moo_pSwitchRightSkillFlags);
			original(&original_pUnit, &original_pSwitchRightSkillId, &original_pSwitchRightSkillFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pSwitchRightSkillId, original_pSwitchRightSkillId, "Comparing pSwitchRightSkillId");
			MOO_CHECK_EQ(moo_pSwitchRightSkillFlags, original_pSwitchRightSkillFlags, "Comparing pSwitchRightSkillFlags");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2490 (#10453)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetSwitchLeftSkill, dll_base + 0x00082490);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int nSwitchLeftSkillId = random_unsigned_integer();
			int nSwitchLeftSkillFlags = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
			};

			setup_data(moo_pUnit, moo_pPlayerData);
			setup_data(original_pUnit, original_pPlayerData);

			// Call both implementations
			sut(&moo_pUnit, nSwitchLeftSkillId, nSwitchLeftSkillFlags);
			original(&original_pUnit, nSwitchLeftSkillId, nSwitchLeftSkillFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC24E0 (#10454)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetSwitchRightSkill, dll_base + 0x000824E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int nSwitchRightSkillId = random_unsigned_integer();
			int nSwitchRightSkillFlags = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
			};

			setup_data(moo_pUnit, moo_pPlayerData);
			setup_data(original_pUnit, original_pPlayerData);

			// Call both implementations
			sut(&moo_pUnit, nSwitchRightSkillId, nSwitchRightSkillFlags);
			original(&original_pUnit, nSwitchRightSkillId, nSwitchRightSkillFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2530 (#10455)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetWeaponGUID, dll_base + 0x00082530);
		
		SUBCASE("")
		{
			// Input data
			const auto weapon_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc moo_pWeapon{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			D2UnitStrc original_pWeapon{};

			const auto setup_data = [weapon_id](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData,
				D2UnitStrc& pWeapon
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pWeapon.dwUnitType = UNIT_ITEM;
				pWeapon.dwUnitId = weapon_id;
			};

			setup_data(moo_pUnit, moo_pPlayerData, moo_pWeapon);
			setup_data(original_pUnit, original_pPlayerData, original_pWeapon);

			// Call both implementations
			sut(&moo_pUnit, &moo_pWeapon);
			original(&original_pUnit, &original_pWeapon);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pWeapon, original_pWeapon, "Comparing pWeapon");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC25B0 (#10456)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetWeaponGUID, dll_base + 0x000825B0);
		
		SUBCASE("")
		{
			// Input data
			const auto weapon_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};

			const auto setup_data = [weapon_id](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
				pPlayerData.nWeaponGUID = weapon_id;
			};

			setup_data(moo_pUnit, moo_pPlayerData);
			setup_data(original_pUnit, original_pPlayerData);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDC2630 (#10339)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetStashGoldLimit, dll_base + 0x00082630);

		REPEAT_10();
		
		SUBCASE("")
		{
			// Input data
			const auto level = random_unsigned_integer(1, 100);

			D2UnitStrc moo_pUnit{};
			D2StatListExStrc moo_pStatListEx{};
			D2StatStrc moo_pStat{};
			D2UnitStrc original_pUnit{};
			D2StatListExStrc original_pStatListEx{};
			D2StatStrc original_pStat{};

			const auto setup_data = [level](
				D2UnitStrc& pUnit,
				D2StatListExStrc& pStatListEx,
				D2StatStrc& pStat
			) {
				pUnit.pStatListEx = &pStatListEx;
				pStatListEx.dwFlags |= STATLIST_EXTENDED;
				pStatListEx.FullStats.pStat = &pStat;
				pStatListEx.FullStats.nStatCount = 1;
				pStat.nStat = STAT_LEVEL;
				pStat.nValue = level;
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
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDC2680 (#10317)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_CanSwitchAI, dll_base + 0x00082680);
		
		SUBCASE("")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				int nMonsterId = i;

				// Call both implementations
				const auto moo_result = sut(nMonsterId);
				const auto original_result = original(nMonsterId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2720 (#10458)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetTimerArg, dll_base + 0x00082720);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2TimerArgStrc moo_pTimerArg{};
			D2UnitStrc original_pUnit{};
			D2TimerArgStrc original_pTimerArg{};

			const auto setup_data = [unit_id](
				D2UnitStrc& pUnit,
				D2TimerArgStrc& pTimerArg
			) {
				pTimerArg.dwUnitId = unit_id;
			};

			setup_data(moo_pUnit, moo_pTimerArg);
			setup_data(original_pUnit, original_pTimerArg);

			// Call both implementations
			sut(&moo_pUnit, &moo_pTimerArg);
			original(&original_pUnit, &original_pTimerArg);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pTimerArg, original_pTimerArg, "Comparing pTimerArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2750 (#10459)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetTimerArg, dll_base + 0x00082750);
		
		SUBCASE("")
		{
			// Input data
			const auto unit_id = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2TimerArgStrc moo_pTimerArg{};
			D2UnitStrc original_pUnit{};
			D2TimerArgStrc original_pTimerArg{};

			const auto setup_data = [unit_id](
				D2UnitStrc& pUnit,
				D2TimerArgStrc& pTimerArg
			) {
				pUnit.pTimerParams = &pTimerArg;
				pTimerArg.dwUnitId = unit_id;
			};

			setup_data(moo_pUnit, moo_pTimerArg);
			setup_data(original_pUnit, original_pTimerArg);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2780 (#10460)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_AllocStaticPath, dll_base + 0x00082780);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_OBJECT;
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC27C0 (#10461)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_FreeStaticPath, dll_base + 0x000827C0);
		const auto [moo_alloc, original_alloc] = make_function_pair(UNITS_AllocStaticPath, dll_base + 0x00082780);

		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = UNIT_OBJECT;
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			moo_alloc(&moo_pUnit);
			original_alloc(&original_pUnit);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDC27F0 (#10462)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_CanDualWield, dll_base + 0x000827F0);
		
		SUBCASE("Player")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = i;
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

		SUBCASE("Monster")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
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

		SUBCASE("Other")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM, UNIT_ITEM);

			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [unit_type](
				D2UnitStrc& pUnit
			) {
				pUnit.dwUnitType = unit_type;
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
	
	TEST_CASE_FIXTURE(StatesTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FDC2860 (#11238)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsCorpseUseable, dll_base + 0x00082860);
		
		SUBCASE("STATEMASK_UDEAD set")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				const auto flag_count = (states_record_count >> 5) + 1;
				const auto flags = std::make_unique<uint32_t[]>(2 * flag_count);

				for (auto j = 0; j < 2 * flag_count; ++j)
				{
					flags[j] |= sgptDataTables->fStateMasks[STATEMASK_UDEAD][j];
				}

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);

				const auto setup_data = [&flags, flag_count, i](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::unique_ptr<uint32_t[]>& StatFlags
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
					pUnit.dwAnimMode = MONMODE_DEAD;
					memcpy(StatFlags.get(), flags.get(), sizeof(uint32_t) * 2 * flag_count);
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.StatFlags = StatFlags.get();
					pUnit.pStatListEx = &pStatListEx;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags);
				setup_data(original_pUnit, original_pStatListEx, original_StatFlags);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				CHECK_EQ(moo_result, 0);
			}
		}

		SUBCASE("STATEMASK_UDEAD not set")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				// Input data
				const auto flag_count = (states_record_count >> 5) + 1;
				const auto flags = std::make_unique<uint32_t[]>(2 * flag_count);
				std::memset(flags.get(), 0, sizeof(uint32_t) * 2 * flag_count);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				auto moo_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				auto original_StatFlags = std::make_unique<uint32_t[]>(2 * flag_count);

				const auto setup_data = [&flags, flag_count, i](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::unique_ptr<uint32_t[]>& StatFlags
				) {
					pUnit.dwUnitType = UNIT_MONSTER;
					pUnit.dwClassId = i;
					pUnit.dwAnimMode = MONMODE_DEAD;
					memcpy(StatFlags.get(), flags.get(), sizeof(uint32_t) * 2 * flag_count);
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.StatFlags = StatFlags.get();
					pUnit.pStatListEx = &pStatListEx;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_StatFlags);
				setup_data(original_pUnit, original_pStatListEx, original_StatFlags);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");

				D2MonStats2Txt* pMonStats2TxtRecord = UNITS_GetMonStats2TxtRecordFromMonsterId(i);
				CHECK_EQ(moo_result, (!(pMonStats2TxtRecord->dwFlags & gdwBitMasks[MONSTATS2FLAGINDEX_DEADCOL]) && (pMonStats2TxtRecord->dwFlags & gdwBitMasks[MONSTATS2FLAGINDEX_CORPSESEL])));
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2910 (#11307)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsObjectInInteractRange, dll_base + 0x00082910);

		REPEAT_10();

		SUBCASE("Player and object")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;
			const auto size_x2 = random_unsigned_integer(0, 5);
			const auto size_y2 = random_unsigned_integer(0, 5);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pObject{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2ObjectDataStrc moo_pObjectData2{};
			D2ObjectsTxt moo_pObjectsTxtRecord2{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pObject{};
			D2StaticPathStrc original_pStaticPath2{};
			D2ObjectDataStrc original_pObjectData2{};
			D2ObjectsTxt original_pObjectsTxtRecord2{};

			const auto setup_data = [x1, y1, x2, y2, size_x2, size_y2](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pObject,
				D2StaticPathStrc& pStaticPath2,
				D2ObjectDataStrc& pObjectData2,
				D2ObjectsTxt& pObjectsTxtRecord2
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pObject.dwUnitType = UNIT_OBJECT;
				pObject.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
				pStaticPath2.tGameCoords.nY = y2;
				pObject.pObjectData = &pObjectData2;
				pObjectData2.pObjectTxt = &pObjectsTxtRecord2;
				pObjectsTxtRecord2.dwSizeX = size_x2;
				pObjectsTxtRecord2.dwSizeY = size_y2;
			};

			setup_data(moo_pUnit, moo_pDynamicPath1, moo_pObject, moo_pStaticPath2, moo_pObjectData2, moo_pObjectsTxtRecord2);
			setup_data(original_pUnit, original_pDynamicPath1, original_pObject, original_pStaticPath2, original_pObjectData2, original_pObjectsTxtRecord2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pObject);
			const auto original_result = original(&original_pUnit, &original_pObject);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}

		SUBCASE("Item and object")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;
			const auto size_x2 = random_unsigned_integer(0, 5);
			const auto size_y2 = random_unsigned_integer(0, 5);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath1{};
			D2UnitStrc moo_pObject{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2ObjectDataStrc moo_pObjectData2{};
			D2ObjectsTxt moo_pObjectsTxtRecord2{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath1{};
			D2UnitStrc original_pObject{};
			D2StaticPathStrc original_pStaticPath2{};
			D2ObjectDataStrc original_pObjectData2{};
			D2ObjectsTxt original_pObjectsTxtRecord2{};

			const auto setup_data = [x1, y1, x2, y2, size_x2, size_y2](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath1,
				D2UnitStrc& pObject,
				D2StaticPathStrc& pStaticPath2,
				D2ObjectDataStrc& pObjectData2,
				D2ObjectsTxt& pObjectsTxtRecord2
			) {
				pUnit.dwUnitType = UNIT_ITEM;
				pUnit.pStaticPath = &pStaticPath1;
				pStaticPath1.tGameCoords.nX = x1;
				pStaticPath1.tGameCoords.nY = y1;
				pObject.dwUnitType = UNIT_OBJECT;
				pObject.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
				pStaticPath2.tGameCoords.nY = y2;
				pObject.pObjectData = &pObjectData2;
				pObjectData2.pObjectTxt = &pObjectsTxtRecord2;
				pObjectsTxtRecord2.dwSizeX = size_x2;
				pObjectsTxtRecord2.dwSizeY = size_y2;
			};

			setup_data(moo_pUnit, moo_pStaticPath1, moo_pObject, moo_pStaticPath2, moo_pObjectData2, moo_pObjectsTxtRecord2);
			setup_data(original_pUnit, original_pStaticPath1, original_pObject, original_pStaticPath2, original_pObjectData2, original_pObjectsTxtRecord2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pObject);
			const auto original_result = original(&original_pUnit, &original_pObject);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}

		SUBCASE("Other unit instead of object")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pObject{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pObject{};
			D2DynamicPathStrc original_pDynamicPath2{};

			const auto setup_data = [x1, y1, x2, y2](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pObject,
				D2DynamicPathStrc& pDynamicPath2
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pObject.dwUnitType = UNIT_PLAYER;
				pObject.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosX = x2;
				pDynamicPath2.tGameCoords.wPosY = y2;
			};

			setup_data(moo_pUnit, moo_pDynamicPath1, moo_pObject, moo_pDynamicPath2);
			setup_data(original_pUnit, original_pDynamicPath1, original_pObject, original_pDynamicPath2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pObject);
			const auto original_result = original(&original_pUnit, &original_pObject);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
		}

		SUBCASE("nullptr")
		{
			// Input data
			const auto x = random_unsigned_integer(0, 10000);
			const auto y = random_unsigned_integer(0, 10000);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};

			const auto setup_data = [x, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nullptr);
			const auto original_result = original(&original_pUnit, nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(CharStatsTxtFixture<NoopFixture>, "D2Common.0x6FDC2C80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetCharStatsTxtRecord, dll_base + 0x00082C80);
		
		SUBCASE("")
		{
			for (auto i = 0; i < charstats_record_count; ++i)
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2CB0 (#10399)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10399, dll_base + 0x00082CB0);

		REPEAT_10();

		SUBCASE("Player and object")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;
			const auto size_x2 = random_unsigned_integer(0, 5);
			const auto size_y2 = random_unsigned_integer(0, 5);

			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2ObjectDataStrc moo_pObjectData2{};
			D2ObjectsTxt moo_pObjectsTxtRecord2{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2StaticPathStrc original_pStaticPath2{};
			D2ObjectDataStrc original_pObjectData2{};
			D2ObjectsTxt original_pObjectsTxtRecord2{};

			const auto setup_data = [x1, y1, x2, y2, size_x2, size_y2](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2StaticPathStrc& pStaticPath2,
				D2ObjectDataStrc& pObjectData2,
				D2ObjectsTxt& pObjectsTxtRecord2
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pUnit2.dwUnitType = UNIT_OBJECT;
				pUnit2.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
				pStaticPath2.tGameCoords.nY = y2;
				pUnit2.pObjectData = &pObjectData2;
				pObjectData2.pObjectTxt = &pObjectsTxtRecord2;
				pObjectsTxtRecord2.dwSizeX = size_x2;
				pObjectsTxtRecord2.dwSizeY = size_y2;
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pStaticPath2, moo_pObjectData2, moo_pObjectsTxtRecord2);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pStaticPath2, original_pObjectData2, original_pObjectsTxtRecord2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}

		SUBCASE("Object and item")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;
			const auto size_x1 = random_unsigned_integer(0, 5);
			const auto size_y1 = random_unsigned_integer(0, 5);

			D2UnitStrc moo_pUnit1{};
			D2StaticPathStrc moo_pStaticPath1{};
			D2ObjectDataStrc moo_pObjectData1{};
			D2ObjectsTxt moo_pObjectsTxtRecord1{};
			D2UnitStrc moo_pUnit2{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2UnitStrc original_pUnit1{};
			D2StaticPathStrc original_pStaticPath1{};
			D2ObjectDataStrc original_pObjectData1{};
			D2ObjectsTxt original_pObjectsTxtRecord1{};
			D2UnitStrc original_pUnit2{};
			D2StaticPathStrc original_pStaticPath2{};

			const auto setup_data = [x1, y1, x2, y2, size_x1, size_y1](
				D2UnitStrc& pUnit1,
				D2StaticPathStrc& pStaticPath1,
				D2ObjectDataStrc& pObjectData1,
				D2ObjectsTxt& pObjectsTxtRecord1,
				D2UnitStrc& pUnit2,
				D2StaticPathStrc& pStaticPath2
			) {
				pUnit1.dwUnitType = UNIT_OBJECT;
				pUnit1.pStaticPath = &pStaticPath1;
				pStaticPath1.tGameCoords.nX = x1;
				pStaticPath1.tGameCoords.nY = y1;
				pUnit1.pObjectData = &pObjectData1;
				pObjectData1.pObjectTxt = &pObjectsTxtRecord1;
				pObjectsTxtRecord1.dwSizeX = size_x1;
				pObjectsTxtRecord1.dwSizeY = size_y1;
				pUnit2.dwUnitType = UNIT_ITEM;
				pUnit2.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
				pStaticPath2.tGameCoords.nY = y2;
			};

			setup_data(moo_pUnit1, moo_pStaticPath1, moo_pObjectData1, moo_pObjectsTxtRecord1, moo_pUnit2, moo_pStaticPath2);
			setup_data(original_pUnit1, original_pStaticPath1, original_pObjectData1, original_pObjectsTxtRecord1, original_pUnit2, original_pStaticPath2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}

		SUBCASE("Item and player")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;

			D2UnitStrc moo_pUnit1{};
			D2StaticPathStrc moo_pStaticPath1{};
			D2UnitStrc moo_pUnit2{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2UnitStrc original_pUnit1{};
			D2StaticPathStrc original_pStaticPath1{};
			D2UnitStrc original_pUnit2{};
			D2DynamicPathStrc original_pDynamicPath2{};

			const auto setup_data = [x1, y1, x2, y2](
				D2UnitStrc& pUnit1,
				D2StaticPathStrc& pStaticPath1,
				D2UnitStrc& pUnit2,
				D2DynamicPathStrc& pDynamicPath2
			) {
				pUnit1.dwUnitType = UNIT_ITEM;
				pUnit1.pStaticPath = &pStaticPath1;
				pStaticPath1.tGameCoords.nX = x1;
				pStaticPath1.tGameCoords.nY = y1;
				pUnit2.dwUnitType = UNIT_PLAYER;
				pUnit2.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosX = x2;
				pDynamicPath2.tGameCoords.wPosY = y2;
			};

			setup_data(moo_pUnit1, moo_pStaticPath1, moo_pUnit2, moo_pDynamicPath2);
			setup_data(original_pUnit1, original_pStaticPath1, original_pUnit2, original_pDynamicPath2);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2E40 (#10397)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetDistanceToOtherUnit, dll_base + 0x00082E40);

		REPEAT_10();

		SUBCASE("Player and object")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;
			const auto size_x2 = random_unsigned_integer(0, 5);
			const auto size_y2 = random_unsigned_integer(0, 5);

			D2UnitStrc moo_pUnit1{};
			D2DynamicPathStrc moo_pDynamicPath1{};
			D2UnitStrc moo_pUnit2{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2ObjectDataStrc moo_pObjectData2{};
			D2ObjectsTxt moo_pObjectsTxtRecord2{};
			D2UnitStrc original_pUnit1{};
			D2DynamicPathStrc original_pDynamicPath1{};
			D2UnitStrc original_pUnit2{};
			D2StaticPathStrc original_pStaticPath2{};
			D2ObjectDataStrc original_pObjectData2{};
			D2ObjectsTxt original_pObjectsTxtRecord2{};

			const auto setup_data = [x1, y1, x2, y2, size_x2, size_y2](
				D2UnitStrc& pUnit1,
				D2DynamicPathStrc& pDynamicPath1,
				D2UnitStrc& pUnit2,
				D2StaticPathStrc& pStaticPath2,
				D2ObjectDataStrc& pObjectData2,
				D2ObjectsTxt& pObjectsTxtRecord2
			) {
				pUnit1.dwUnitType = UNIT_PLAYER;
				pUnit1.pDynamicPath = &pDynamicPath1;
				pDynamicPath1.tGameCoords.wPosX = x1;
				pDynamicPath1.tGameCoords.wPosY = y1;
				pUnit2.dwUnitType = UNIT_OBJECT;
				pUnit2.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
				pStaticPath2.tGameCoords.nY = y2;
				pUnit2.pObjectData = &pObjectData2;
				pObjectData2.pObjectTxt = &pObjectsTxtRecord2;
				pObjectsTxtRecord2.dwSizeX = size_x2;
				pObjectsTxtRecord2.dwSizeY = size_y2;
			};

			setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pStaticPath2, moo_pObjectData2, moo_pObjectsTxtRecord2);
			setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pStaticPath2, original_pObjectData2, original_pObjectsTxtRecord2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}

		SUBCASE("Object and item")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;
			const auto size_x1 = random_unsigned_integer(0, 5);
			const auto size_y1 = random_unsigned_integer(0, 5);

			D2UnitStrc moo_pUnit1{};
			D2StaticPathStrc moo_pStaticPath1{};
			D2ObjectDataStrc moo_pObjectData1{};
			D2ObjectsTxt moo_pObjectsTxtRecord1{};
			D2UnitStrc moo_pUnit2{};
			D2StaticPathStrc moo_pStaticPath2{};
			D2UnitStrc original_pUnit1{};
			D2StaticPathStrc original_pStaticPath1{};
			D2ObjectDataStrc original_pObjectData1{};
			D2ObjectsTxt original_pObjectsTxtRecord1{};
			D2UnitStrc original_pUnit2{};
			D2StaticPathStrc original_pStaticPath2{};

			const auto setup_data = [x1, y1, x2, y2, size_x1, size_y1](
				D2UnitStrc& pUnit1,
				D2StaticPathStrc& pStaticPath1,
				D2ObjectDataStrc& pObjectData1,
				D2ObjectsTxt& pObjectsTxtRecord1,
				D2UnitStrc& pUnit2,
				D2StaticPathStrc& pStaticPath2
			) {
				pUnit1.dwUnitType = UNIT_OBJECT;
				pUnit1.pStaticPath = &pStaticPath1;
				pStaticPath1.tGameCoords.nX = x1;
				pStaticPath1.tGameCoords.nY = y1;
				pUnit1.pObjectData = &pObjectData1;
				pObjectData1.pObjectTxt = &pObjectsTxtRecord1;
				pObjectsTxtRecord1.dwSizeX = size_x1;
				pObjectsTxtRecord1.dwSizeY = size_y1;
				pUnit2.dwUnitType = UNIT_ITEM;
				pUnit2.pStaticPath = &pStaticPath2;
				pStaticPath2.tGameCoords.nX = x2;
				pStaticPath2.tGameCoords.nY = y2;
			};

			setup_data(moo_pUnit1, moo_pStaticPath1, moo_pObjectData1, moo_pObjectsTxtRecord1, moo_pUnit2, moo_pStaticPath2);
			setup_data(original_pUnit1, original_pStaticPath1, original_pObjectData1, original_pObjectsTxtRecord1, original_pUnit2, original_pStaticPath2);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			const auto original_result = original(&original_pUnit1, &original_pUnit2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}

		SUBCASE("Item and player")
		{
			// Input data
			const auto x1 = random_unsigned_integer(16, 10000);
			const auto y1 = random_unsigned_integer(16, 10000);
			const auto x2 = x1 + random_unsigned_integer(0, 24) - 12;
			const auto y2 = y1 + random_unsigned_integer(0, 24) - 12;

			D2UnitStrc moo_pUnit1{};
			D2StaticPathStrc moo_pStaticPath1{};
			D2UnitStrc moo_pUnit2{};
			D2DynamicPathStrc moo_pDynamicPath2{};
			D2UnitStrc original_pUnit1{};
			D2StaticPathStrc original_pStaticPath1{};
			D2UnitStrc original_pUnit2{};
			D2DynamicPathStrc original_pDynamicPath2{};

			const auto setup_data = [x1, y1, x2, y2](
				D2UnitStrc& pUnit1,
				D2StaticPathStrc& pStaticPath1,
				D2UnitStrc& pUnit2,
				D2DynamicPathStrc& pDynamicPath2
			) {
				pUnit1.dwUnitType = UNIT_ITEM;
				pUnit1.pStaticPath = &pStaticPath1;
				pStaticPath1.tGameCoords.nX = x1;
				pStaticPath1.tGameCoords.nY = y1;
				pUnit2.dwUnitType = UNIT_PLAYER;
				pUnit2.pDynamicPath = &pDynamicPath2;
				pDynamicPath2.tGameCoords.wPosX = x2;
				pDynamicPath2.tGameCoords.wPosY = y2;
			};

			setup_data(moo_pUnit1, moo_pStaticPath1, moo_pUnit2, moo_pDynamicPath2);
			setup_data(original_pUnit1, original_pStaticPath1, original_pUnit2, original_pDynamicPath2);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2F50 (#10398)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetDistanceToCoordinates, dll_base + 0x00082F50);
		
		SUBCASE("static unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			int nX = random_unsigned_integer(0, 65535);
			int nY = random_unsigned_integer(0, 65535);

			const auto setup_data = [unit_type, x, y](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
				pStaticPath.tGameCoords.nY = y;
			};

			setup_data(moo_pUnit, moo_pStaticPath);
			setup_data(original_pUnit, original_pStaticPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY);
			const auto original_result = original(&original_pUnit, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}

		SUBCASE("dynamic unit")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			int nX = random_unsigned_integer(0, 65535);
			int nY = random_unsigned_integer(0, 65535);

			const auto setup_data = [unit_type, x, y](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
			};

			setup_data(moo_pUnit, moo_pDynamicPath);
			setup_data(original_pUnit, original_pDynamicPath);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY);
			const auto original_result = original(&original_pUnit, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2FF0 (#10400)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsInRange, dll_base + 0x00082FF0);

		SUBCASE("static unit - in range")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2CoordStrc moo_pCoord{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2CoordStrc original_pCoord{};
			int nDistance = random_unsigned_integer(1, 10);
			const auto x_offset = random_unsigned_integer(0, nDistance);
			const auto y_offset = random_unsigned_integer(0, nDistance);

			const auto setup_data = [unit_type, x, y, x_offset, y_offset](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2CoordStrc& pCoord
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
				pStaticPath.tGameCoords.nY = y;
				pCoord.nX = x + x_offset;
				pCoord.nY = y + y_offset;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pCoord);
			setup_data(original_pUnit, original_pStaticPath, original_pCoord);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pCoord, nDistance);
			const auto original_result = original(&original_pUnit, &original_pCoord, nDistance);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}

		SUBCASE("static unit - out of range")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_OBJECT, UNIT_ITEM, UNIT_TILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2StaticPathStrc moo_pStaticPath{};
			D2CoordStrc moo_pCoord{};
			D2UnitStrc original_pUnit{};
			D2StaticPathStrc original_pStaticPath{};
			D2CoordStrc original_pCoord{};
			int nDistance = random_unsigned_integer(1, 10);
			const auto x_offset = random_unsigned_integer(nDistance + 1, 255);
			const auto y_offset = random_unsigned_integer(nDistance + 1, 255);

			const auto setup_data = [unit_type, x, y, x_offset, y_offset](
				D2UnitStrc& pUnit,
				D2StaticPathStrc& pStaticPath,
				D2CoordStrc& pCoord
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pStaticPath = &pStaticPath;
				pStaticPath.tGameCoords.nX = x;
				pStaticPath.tGameCoords.nY = y;
				pCoord.nX = x + x_offset;
				pCoord.nY = y + y_offset;
			};

			setup_data(moo_pUnit, moo_pStaticPath, moo_pCoord);
			setup_data(original_pUnit, original_pStaticPath, original_pCoord);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pCoord, nDistance);
			const auto original_result = original(&original_pUnit, &original_pCoord, nDistance);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}

		SUBCASE("dynamic unit - in range")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2CoordStrc moo_pCoord{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2CoordStrc original_pCoord{};
			int nDistance = random_unsigned_integer(1, 10);
			const auto x_offset = random_unsigned_integer(0, nDistance);
			const auto y_offset = random_unsigned_integer(0, nDistance);

			const auto setup_data = [unit_type, x, y, x_offset, y_offset](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2CoordStrc& pCoord
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
				pCoord.nX = x + x_offset;
				pCoord.nY = y + y_offset;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pCoord);
			setup_data(original_pUnit, original_pDynamicPath, original_pCoord);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pCoord, nDistance);
			const auto original_result = original(&original_pUnit, &original_pCoord, nDistance);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}

		SUBCASE("dynamic unit - out of range")
		{
			// Input data
			const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);
			const auto x = random_unsigned_integer(0, 65535);
			const auto y = random_unsigned_integer(0, 65535);

			D2UnitStrc moo_pUnit{};
			D2DynamicPathStrc moo_pDynamicPath{};
			D2CoordStrc moo_pCoord{};
			D2UnitStrc original_pUnit{};
			D2DynamicPathStrc original_pDynamicPath{};
			D2CoordStrc original_pCoord{};
			int nDistance = random_unsigned_integer(1, 10);
			const auto x_offset = random_unsigned_integer(nDistance + 1, 255);
			const auto y_offset = random_unsigned_integer(nDistance + 1, 255);

			const auto setup_data = [unit_type, x, y, x_offset, y_offset](
				D2UnitStrc& pUnit,
				D2DynamicPathStrc& pDynamicPath,
				D2CoordStrc& pCoord
			) {
				pUnit.dwUnitType = unit_type;
				pUnit.pDynamicPath = &pDynamicPath;
				pDynamicPath.tGameCoords.wPosX = x;
				pDynamicPath.tGameCoords.wPosY = y;
				pCoord.nX = x + x_offset;
				pCoord.nY = y + y_offset;
			};

			setup_data(moo_pUnit, moo_pDynamicPath, moo_pCoord);
			setup_data(original_pUnit, original_pDynamicPath, original_pCoord);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pCoord, nDistance);
			const auto original_result = original(&original_pUnit, &original_pCoord, nDistance);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pCoord, original_pCoord, "Comparing pCoord");
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FDC3090 (#10406)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10406, dll_base + 0x00083090);

		// Accepts the units with an odd id and counts how often it gets called
		struct UnitCallback
		{
			static int __fastcall AcceptOddUnitIds(D2UnitStrc* pUnit, void* pCallCount)
			{
				++*static_cast<int*>(pCallCount);
				return pUnit->dwUnitId & 1;
			}
		};

		REPEAT_10();

		SUBCASE("")
		{
			constexpr int room_count = 2;
			constexpr int room_size = 16;
			constexpr int unit_count = 16;

			// Input data
			const auto room_x = random_unsigned_integer(0, 10000);
			const auto room_y = random_unsigned_integer(0, 10000);
			const auto center_x = room_x + room_size / 2;
			const auto center_y = room_y + room_size / 2;

			// The units are placed around the tested position, in one of the two rooms adjacent to the starting room
			struct UnitInput
			{
				uint32_t nUnitType;
				int32_t nClassId;
				uint32_t nAnimMode;
				int32_t nRoom;
				uint32_t nX;
				uint32_t nY;
			};

			UnitInput unit_inputs[unit_count]{};
			for (auto& unit_input : unit_inputs)
			{
				unit_input.nUnitType = random_unsigned_integer(0, 1) ? random_unsigned_integer(UNIT_PLAYER, UNIT_MONSTER) : random_unsigned_integer(UNIT_OBJECT, UNIT_ITEM);
				switch (unit_input.nUnitType)
				{
				case UNIT_PLAYER:
					unit_input.nClassId = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
					break;
				case UNIT_MONSTER:
					unit_input.nClassId = random_unsigned_integer(0, monstats_record_count - 1);
					break;
				case UNIT_MISSILE:
					unit_input.nClassId = random_unsigned_integer(0, missiles_record_count - 1);
					break;
				default:
					unit_input.nClassId = random_unsigned_integer(0, 255);
					break;
				}
				unit_input.nAnimMode = random_unsigned_integer(0, NUMBER_OF_PLRMODES - 1);
				unit_input.nRoom = random_unsigned_integer(0, room_count - 1);
				unit_input.nX = center_x + random_unsigned_integer(0, 6) - 3;
				unit_input.nY = center_y + random_unsigned_integer(0, 6) - 3;
			}

			D2ActiveRoomStrc moo_pRooms[room_count]{};
			D2ActiveRoomStrc* moo_ppRoomList[room_count]{};
			D2UnitStrc moo_pUnits[unit_count]{};
			D2DynamicPathStrc moo_pDynamicPaths[unit_count]{};
			int moo_call_count = 0;
			D2ActiveRoomStrc original_pRooms[room_count]{};
			D2ActiveRoomStrc* original_ppRoomList[room_count]{};
			D2UnitStrc original_pUnits[unit_count]{};
			D2DynamicPathStrc original_pDynamicPaths[unit_count]{};
			int original_call_count = 0;
			void* moo_a3 = &moo_call_count;
			void* original_a3 = &original_call_count;

			const auto setup_data = [room_count, room_size, room_x, room_y, unit_count, &unit_inputs](
				D2ActiveRoomStrc(&pRooms)[room_count],
				D2ActiveRoomStrc* (&ppRoomList)[room_count],
				D2UnitStrc(&pUnits)[unit_count],
				D2DynamicPathStrc(&pDynamicPaths)[unit_count]
			) {
				// The first room is the starting room, both rooms are part of its adjacent rooms
				for (auto i = 0; i < room_count; ++i)
				{
					pRooms[i].tCoords.nSubtileX = room_x + i * room_size;
					pRooms[i].tCoords.nSubtileY = room_y;
					pRooms[i].tCoords.nSubtileWidth = room_size;
					pRooms[i].tCoords.nSubtileHeight = room_size;
					ppRoomList[i] = &pRooms[i];
				}
				pRooms[0].ppRoomList = ppRoomList;
				pRooms[0].nNumRooms = room_count;

				for (auto i = 0; i < unit_count; ++i)
				{
					pUnits[i].dwUnitType = unit_inputs[i].nUnitType;
					pUnits[i].dwClassId = unit_inputs[i].nClassId;
					pUnits[i].dwUnitId = i;
					pUnits[i].dwAnimMode = unit_inputs[i].nAnimMode;

					// Only players, monsters and missiles are checked for their positions
					if (unit_inputs[i].nUnitType == UNIT_PLAYER || unit_inputs[i].nUnitType == UNIT_MONSTER || unit_inputs[i].nUnitType == UNIT_MISSILE)
					{
						pUnits[i].pDynamicPath = &pDynamicPaths[i];
						pDynamicPaths[i].tGameCoords.wPosX = unit_inputs[i].nX;
						pDynamicPaths[i].tGameCoords.wPosY = unit_inputs[i].nY;
						pDynamicPaths[i].pRoom = &pRooms[unit_inputs[i].nRoom];
					}

					pUnits[i].pRoomNext = pRooms[unit_inputs[i].nRoom].pUnitFirst;
					pRooms[unit_inputs[i].nRoom].pUnitFirst = &pUnits[i];
				}
			};

			setup_data(moo_pRooms, moo_ppRoomList, moo_pUnits, moo_pDynamicPaths);
			setup_data(original_pRooms, original_ppRoomList, original_pUnits, original_pDynamicPaths);

			// The searching unit is one of the dynamic units in the starting room, which is skipped by the search itself
			auto searching_unit = -1;
			for (auto i = 0; i < unit_count; ++i)
			{
				if (moo_pUnits[i].pDynamicPath && unit_inputs[i].nRoom == 0)
				{
					searching_unit = i;
					break;
				}
			}

			if (searching_unit < 0)
			{
				return;
			}

			// Call both implementations
			const auto moo_result = sut(&moo_pUnits[searching_unit], UnitCallback::AcceptOddUnitIds, moo_a3);
			const auto original_result = original(&original_pUnits[searching_unit], UnitCallback::AcceptOddUnitIds, original_a3);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			MOO_CHECK_EQ(moo_call_count, original_call_count, "Comparing callback calls");

			// Compare potentially modified input data
			for (auto i = 0; i < room_count; ++i)
			{
				MOO_CHECK_EQ(moo_pRooms[i], original_pRooms[i], "Comparing pRooms");
			}

			for (auto i = 0; i < unit_count; ++i)
			{
				MOO_CHECK_EQ(moo_pUnits[i], original_pUnits[i], "Comparing pUnits");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FDC33C0 (#10407)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10407, dll_base + 0x000833C0);

		// Accepts the units with an odd id and counts how often it gets called
		struct UnitCallback
		{
			static int __fastcall AcceptOddUnitIds(D2UnitStrc* pUnit, void* pCallCount)
			{
				++*static_cast<int*>(pCallCount);
				return pUnit->dwUnitId & 1;
			}
		};

		REPEAT_10();

		SUBCASE("")
		{
			constexpr int room_count = 2;
			constexpr int room_size = 16;
			constexpr int unit_count = 16;

			// Input data
			const auto room_x = random_unsigned_integer(0, 10000);
			const auto room_y = random_unsigned_integer(0, 10000);
			const auto center_x = room_x + room_size / 2;
			const auto center_y = room_y + room_size / 2;

			// The units are placed around the tested position, in one of the two rooms adjacent to the starting room
			struct UnitInput
			{
				uint32_t nUnitType;
				int32_t nClassId;
				uint32_t nAnimMode;
				int32_t nRoom;
				uint32_t nX;
				uint32_t nY;
			};

			UnitInput unit_inputs[unit_count]{};
			for (auto& unit_input : unit_inputs)
			{
				unit_input.nUnitType = random_unsigned_integer(0, 1) ? random_unsigned_integer(UNIT_PLAYER, UNIT_MONSTER) : random_unsigned_integer(UNIT_OBJECT, UNIT_ITEM);
				switch (unit_input.nUnitType)
				{
				case UNIT_PLAYER:
					unit_input.nClassId = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
					break;
				case UNIT_MONSTER:
					unit_input.nClassId = random_unsigned_integer(0, monstats_record_count - 1);
					break;
				case UNIT_MISSILE:
					unit_input.nClassId = random_unsigned_integer(0, missiles_record_count - 1);
					break;
				default:
					unit_input.nClassId = random_unsigned_integer(0, 255);
					break;
				}
				unit_input.nAnimMode = random_unsigned_integer(0, NUMBER_OF_PLRMODES - 1);
				unit_input.nRoom = random_unsigned_integer(0, room_count - 1);
				unit_input.nX = center_x + random_unsigned_integer(0, 6) - 3;
				unit_input.nY = center_y + random_unsigned_integer(0, 6) - 3;
			}

			D2ActiveRoomStrc moo_pRooms[room_count]{};
			D2ActiveRoomStrc* moo_ppRoomList[room_count]{};
			D2UnitStrc moo_pUnits[unit_count]{};
			D2DynamicPathStrc moo_pDynamicPaths[unit_count]{};
			int moo_call_count = 0;
			D2ActiveRoomStrc original_pRooms[room_count]{};
			D2ActiveRoomStrc* original_ppRoomList[room_count]{};
			D2UnitStrc original_pUnits[unit_count]{};
			D2DynamicPathStrc original_pDynamicPaths[unit_count]{};
			int original_call_count = 0;
			void* moo_a5 = &moo_call_count;
			void* original_a5 = &original_call_count;
			int nX = center_x + random_unsigned_integer(0, 4) - 2;
			int nY = center_y + random_unsigned_integer(0, 4) - 2;
			int a6 = random_unsigned_integer(0, 4);

			const auto setup_data = [room_count, room_size, room_x, room_y, unit_count, &unit_inputs](
				D2ActiveRoomStrc(&pRooms)[room_count],
				D2ActiveRoomStrc* (&ppRoomList)[room_count],
				D2UnitStrc(&pUnits)[unit_count],
				D2DynamicPathStrc(&pDynamicPaths)[unit_count]
			) {
				// The first room is the starting room, both rooms are part of its adjacent rooms
				for (auto i = 0; i < room_count; ++i)
				{
					pRooms[i].tCoords.nSubtileX = room_x + i * room_size;
					pRooms[i].tCoords.nSubtileY = room_y;
					pRooms[i].tCoords.nSubtileWidth = room_size;
					pRooms[i].tCoords.nSubtileHeight = room_size;
					ppRoomList[i] = &pRooms[i];
				}
				pRooms[0].ppRoomList = ppRoomList;
				pRooms[0].nNumRooms = room_count;

				for (auto i = 0; i < unit_count; ++i)
				{
					pUnits[i].dwUnitType = unit_inputs[i].nUnitType;
					pUnits[i].dwClassId = unit_inputs[i].nClassId;
					pUnits[i].dwUnitId = i;
					pUnits[i].dwAnimMode = unit_inputs[i].nAnimMode;

					// Only players, monsters and missiles are checked for their positions
					if (unit_inputs[i].nUnitType == UNIT_PLAYER || unit_inputs[i].nUnitType == UNIT_MONSTER || unit_inputs[i].nUnitType == UNIT_MISSILE)
					{
						pUnits[i].pDynamicPath = &pDynamicPaths[i];
						pDynamicPaths[i].tGameCoords.wPosX = unit_inputs[i].nX;
						pDynamicPaths[i].tGameCoords.wPosY = unit_inputs[i].nY;
						pDynamicPaths[i].pRoom = &pRooms[unit_inputs[i].nRoom];
					}

					pUnits[i].pRoomNext = pRooms[unit_inputs[i].nRoom].pUnitFirst;
					pRooms[unit_inputs[i].nRoom].pUnitFirst = &pUnits[i];
				}
			};

			setup_data(moo_pRooms, moo_ppRoomList, moo_pUnits, moo_pDynamicPaths);
			setup_data(original_pRooms, original_ppRoomList, original_pUnits, original_pDynamicPaths);

			// Call both implementations
			const auto moo_result = sut(&moo_pRooms[0], nX, nY, UnitCallback::AcceptOddUnitIds, moo_a5, a6);
			const auto original_result = original(&original_pRooms[0], nX, nY, UnitCallback::AcceptOddUnitIds, original_a5, a6);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			MOO_CHECK_EQ(moo_call_count, original_call_count, "Comparing callback calls");

			// Compare potentially modified input data
			for (auto i = 0; i < room_count; ++i)
			{
				MOO_CHECK_EQ(moo_pRooms[i], original_pRooms[i], "Comparing pRooms");
			}

			for (auto i = 0; i < unit_count; ++i)
			{
				MOO_CHECK_EQ(moo_pUnits[i], original_pUnits[i], "Comparing pUnits");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3680 (#10419)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetInteractData, dll_base + 0x00083680);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2PlayerDataStrc moo_pPlayerData{};
			D2UnitStrc original_pUnit{};
			D2PlayerDataStrc original_pPlayerData{};
			int nSkillId = random_unsigned_integer();
			int nUnitType = random_unsigned_integer();
			D2UnitGUID nUnitGUID = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2PlayerDataStrc& pPlayerData
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pPlayerData = &pPlayerData;
			};

			setup_data(moo_pUnit, moo_pPlayerData);
			setup_data(original_pUnit, original_pPlayerData);

			// Call both implementations
			sut(&moo_pUnit, nSkillId, nUnitType, nUnitGUID);
			original(&original_pUnit, nSkillId, nUnitType, nUnitGUID);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
