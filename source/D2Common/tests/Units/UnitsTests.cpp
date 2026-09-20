#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Skills.h>
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBD720 (#11260)" * doctest::skip("Not really testable"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_FreeUnit, dll_base + 0x0007D720);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBDEC0 (#10352)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_FreeCollisionPath, dll_base + 0x0007DEC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE060 (#10351)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_BlockCollisionPath, dll_base + 0x0007E060);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			int nX{};
			int nY{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pRoom);
			setup_data(original_pUnit, original_pRoom);

			// Call both implementations
			sut(&moo_pUnit, &moo_pRoom, nX, nY);
			original(&original_pUnit, &original_pRoom, nX, nY);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE4C0 (#10325)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimData, dll_base + 0x0007E4C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nUnitType{};
			int nClassId{};
			int nMode{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nUnitType, nClassId, nMode);
			original(&original_pUnit, nUnitType, nClassId, nMode);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBE510 (#10349)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimStartFrame, dll_base + 0x0007E510);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEA60 (#10348)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_ChangeAnimMode, dll_base + 0x0007EA60);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nMode{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEB80 (#10357)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_RefreshInventory, dll_base + 0x0007EB80);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL bSetFlag{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBED10 (#10369)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetAnimOrSeqMode, dll_base + 0x0007ED10);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBED40 (#10370)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimOrSeqMode, dll_base + 0x0007ED40);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nAnimMode{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBED90 (#10371)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_InitializeSequence, dll_base + 0x0007ED90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBEE60 (#10373)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StopSequence, dll_base + 0x0007EE60);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBF050 (#10376)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_UpdateAnimRateAndVelocity, dll_base + 0x0007F050);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			char szFile{};
			int nLine{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, &szFile, nLine);
			original(&original_pUnit, &szFile, nLine);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBF910 (#10378)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsAtEndOfFrameCycle, dll_base + 0x0007F910);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFA40 (#10381)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetAnimActionFrame, dll_base + 0x0007FA40);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nFrame{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFA90 (#10382)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetEventFrameInfo, dll_base + 0x0007FA90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nFrame{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nFrame);
			const auto original_result = original(&original_pUnit, nFrame);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFB70 (#10358)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetSkillFromSkillId, dll_base + 0x0007FB70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nSkillId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nSkillId);
			const auto original_result = original(&original_pUnit, nSkillId);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFDB0 (#10413)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_UpdateDirectionAndSpeed, dll_base + 0x0007FDB0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nX{};
			int nY{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFDD0 (#10414)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetNewDirection, dll_base + 0x0007FDD0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFF20 (#10416)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StoreOwnerTypeAndGUID, dll_base + 0x0007FF20);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nOwnerType{};
			D2UnitGUID nOwnerId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nOwnerType, nOwnerId);
			original(&original_pUnit, nOwnerType, nOwnerId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFF40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StoreOwnerInfo, dll_base + 0x0007FF40);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nOwnerType{};
			int nOwnerId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nOwnerType, nOwnerId);
			original(&original_pUnit, nOwnerType, nOwnerId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBFFE0 (#10415)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_StoreOwner, dll_base + 0x0007FFE0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pOwner{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC00E0 (#10418)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetDirectionToCoords, dll_base + 0x000800E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nNewX{};
			int nNewY{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nNewX, nNewY);
			const auto original_result = original(&original_pUnit, nNewX, nNewY);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0160 (#10437)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_SetOverlay, dll_base + 0x00080160);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nOverlay{};
			int nUnused{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0260 (#10368)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetCurrentLifePercentage, dll_base + 0x00080260);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0320 (#10420)")
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC03F0 (#10421)" * doctest::skip("Not really testable"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_FreePlayerData, dll_base + 0x000803F0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC08B0 (#10431)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetDefense, dll_base + 0x000808B0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0AC0 (#10432)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetAttackRate, dll_base + 0x00080AC0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pAttacker{};
			D2UnitStrc original_pAttacker{};

			const auto setup_data = [](
				D2UnitStrc& pAttacker
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAttacker);
			setup_data(original_pAttacker);

			// Call both implementations
			const auto moo_result = sut(&moo_pAttacker);
			const auto original_result = original(&original_pAttacker);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0B60 (#10433)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetBlockRate, dll_base + 0x00080B60);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL bExpansion{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
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
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0DA0 (#10434)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10434, dll_base + 0x00080DA0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			BOOL a2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
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
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0F70 (#10435)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetEquippedWeaponFromMonster, dll_base + 0x00080F70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pMonster{};
			D2UnitStrc original_pMonster{};

			const auto setup_data = [](
				D2UnitStrc& pMonster
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pMonster);
			setup_data(original_pMonster);

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster);
			const auto original_result = original(&original_pMonster);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC0FC0 (#10436)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetFrameBonus, dll_base + 0x00080FC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1120 (#10360)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetMeleeRange, dll_base + 0x00081120);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1230 (#10364)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_TestCollisionByCoordinates, dll_base + 0x00081230);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nX{};
			int nY{};
			int nFlags{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nX, nY, nFlags);
			const auto original_result = original(&original_pUnit, nX, nY, nFlags);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC13D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_TestCollision, dll_base + 0x000813D0);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};
			int nX1{};
			int nY1{};
			int nSize1{};
			int nX2{};
			int nY2{};
			int nSize2{};
			int nCollisionMask{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			const auto moo_result = sut(nX1, nY1, nSize1, nX2, nY2, nSize2, &moo_pRoom, nCollisionMask);
			const auto original_result = original(nX1, nY1, nSize1, nX2, nY2, nSize2, &original_pRoom, nCollisionMask);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC14C0 (#10362)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_TestCollisionWithUnit, dll_base + 0x000814C0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};
			int nCollisionMask{};

			const auto setup_data = [](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_ToggleUnitFlag, dll_base + 0x00081760);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int nFlag{};
			BOOL bSet{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1790 (#10363)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_TestCollisionBetweenInteractingUnits, dll_base + 0x00081790);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};
			int nCollisionMask{};

			const auto setup_data = [](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1A70 (#10361)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsInMeleeRange, dll_base + 0x00081A70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};
			int nRangeBonus{};

			const auto setup_data = [](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1B40 (#10318)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsInMovingMode, dll_base + 0x00081B40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1C30 (#10319)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsInMovingModeEx, dll_base + 0x00081C30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1C50 (#10365)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetHitClass, dll_base + 0x00081C50);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1CE0 (#10366)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetWeaponClass, dll_base + 0x00081CE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1D00 (#10438)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetHealingCost, dll_base + 0x00081D00);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1D90 (#10439)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetInventoryGoldLimit, dll_base + 0x00081D90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1DB0 (#10440)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_MergeDualWieldWeaponStatLists, dll_base + 0x00081DB0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int a2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, a2);
			original(&original_pUnit, a2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC1F10 (#10442)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetItemComponentId, dll_base + 0x00081F10);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pItem{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pItem
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pItem);
			setup_data(original_pUnit, original_pItem);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2630 (#10339)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetStashGoldLimit, dll_base + 0x00082630);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC27C0 (#10461)" * doctest::skip("Not really testable"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_FreeStaticPath, dll_base + 0x000827C0);
		const auto [moo_alloc_static_path, original_alloc_static_path] = make_function_pair(UNITS_AllocStaticPath, dll_base + 0x00082780);

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

			moo_alloc_static_path(&moo_pUnit);
			original_alloc_static_path(&original_pUnit);

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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2860 (#11238)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsCorpseUseable, dll_base + 0x00082860);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2910 (#11307)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_IsObjectInInteractRange, dll_base + 0x00082910);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pObject{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pObject{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pObject
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pObject);
			setup_data(original_pUnit, original_pObject);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pObject);
			const auto original_result = original(&original_pUnit, &original_pObject);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pObject, original_pObject, "Comparing pObject");
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2CB0 (#10399)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10399, dll_base + 0x00082CB0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC2E40 (#10397)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(UNITS_GetDistanceToOtherUnit, dll_base + 0x00082E40);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC3090 (#10406)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10406, dll_base + 0x00083090);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			void* moo_a3 = nullptr;
			void* original_a3 = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nullptr, moo_a3);
			const auto original_result = original(&original_pUnit, nullptr, original_a3);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDC33C0 (#10407)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10407, dll_base + 0x000833C0);
		
		SUBCASE("")
		{
			// Input data
			D2ActiveRoomStrc moo_pRoom{};
			D2ActiveRoomStrc original_pRoom{};
			int nX{};
			int nY{};
			void* moo_a5 = nullptr;
			void* original_a5 = nullptr;
			int a6{};

			const auto setup_data = [](
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pRoom);
			setup_data(original_pRoom);

			// Call both implementations
			const auto moo_result = sut(&moo_pRoom, nX, nY, nullptr, moo_a5, a6);
			const auto original_result = original(&original_pRoom, nX, nY, nullptr, original_a5, a6);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_a5, original_a5, "Comparing a5");
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
