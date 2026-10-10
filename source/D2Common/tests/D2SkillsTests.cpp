#include <doctest.h>

#include <Windows.h>

#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <filesystem>
#include <iterator>
#include <memory>
#include <vector>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Calc.h>
#include <Fog.h>

#include <D2Collision.h>
#include <D2Combat.h>
#include <D2Dungeon.h>
#include <D2Inventory.h>
#include <D2Items.h>
#include <D2Monsters.h>
#include <D2Skills.h>
#include <D2StatList.h>
#include <D2States.h>
#include <DataTbls/LevelsIds.h>
#include <DataTbls/SkillsIds.h>
#include <DataTbls/SkillsTbls.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Path/Path.h>
#include <Units/Item.h>
#include <Units/Player.h>
#include <Units/Units.h>

#include <Fixtures/DataTbls/Fixtures.h>


DYNAMIC_ARRAY_TYPE(int);
DYNAMIC_ARRAY_TYPE(uint16_t);
DYNAMIC_ARRAY_TYPE(uint32_t);


TEST_SUITE("D2SkillsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDAEB10 (#10938)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetPassiveState, dll_base + 0x0006EB10);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				int nSkillId = i;

				// Call both implementations
				const auto moo_result = sut(nSkillId);
				const auto original_result = original(nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<MissilesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDAEB60 (#11271)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSpecialParamValue, dll_base + 0x0006EB60);

		SUBCASE("")
		{
			// Input data
			std::vector<D2StatStrc> stat_array(5);
			stat_array[0].nStat = STAT_LEVEL;
			stat_array[0].nValue = random_unsigned_integer(1, 99);

			for (auto i = 1; i < 5; ++i)
			{
				stat_array[i].nStat = static_cast<uint16_t>(STAT_PASSIVE_FIRE_MASTERY + i - 1);
				stat_array[i].nValue = random_unsigned_integer(0, 200);
			}

			for (auto i = 0; i < skills_record_count; ++i)
			{
				const auto skill_level = random_unsigned_integer(0, 20);

				for (auto j = 0; j < 74; ++j)
				{
					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pSkill{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pSkill{};
					uint8_t nParamId = static_cast<uint8_t>(j);
					int nSkillId = i;
					int nSkillLevel = skill_level;

					const auto setup_data = [this, &stat_array, i, skill_level](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						D2SkillListStrc& pSkillList,
						D2SkillStrc& pSkill
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pUnit.pSkills = &pSkillList;
						pSkillList.pFirstSkill = &pSkill;
						pSkill.pSkillsTxt = &skills_txt[i];
						pSkill.nSkillLevel = skill_level;
						pSkill.nOwnerGUID = D2UnitInvalidGUID;
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pSkillList, moo_pSkill);
					setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pSkillList, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nParamId, nSkillId, nSkillLevel);
					const auto original_result = original(&original_pUnit, nParamId, nSkillId, nSkillLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<MissilesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDAF6A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAF6A0, dll_base + 0x0006F6A0);

		SUBCASE("with skill calc")
		{
			// Input data
			std::vector<D2StatStrc> stat_array(5);
			stat_array[0].nStat = STAT_LEVEL;
			stat_array[0].nValue = random_unsigned_integer(1, 99);

			for (auto i = 1; i < 5; ++i)
			{
				stat_array[i].nStat = static_cast<uint16_t>(STAT_PASSIVE_FIRE_MASTERY + i - 1);
				stat_array[i].nValue = random_unsigned_integer(0, 200);
			}

			for (auto i = 0; i < skills_record_count; ++i)
			{
				const auto skill_level = random_unsigned_integer(0, 20);

				for (auto j = 0; j < 74; ++j)
				{
					D2SkillCalcStrc moo_pSkillCalc{};
					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pSkill{};
					D2SkillCalcStrc original_pSkillCalc{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pSkill{};
					int32_t nParamId = j;

					const auto setup_data = [this, &stat_array, i, skill_level](
						D2SkillCalcStrc& pSkillCalc,
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						D2SkillListStrc& pSkillList,
						D2SkillStrc& pSkill
					) {
						pSkillCalc.pUnit = &pUnit;
						pSkillCalc.nSkillId = i;
						pSkillCalc.nSkillLevel = skill_level;
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pUnit.pSkills = &pSkillList;
						pSkillList.pFirstSkill = &pSkill;
						pSkill.pSkillsTxt = &skills_txt[i];
						pSkill.nSkillLevel = skill_level;
						pSkill.nOwnerGUID = D2UnitInvalidGUID;
					};

					setup_data(moo_pSkillCalc, moo_pUnit, moo_pStatListEx, moo_pStat, moo_pSkillList, moo_pSkill);
					setup_data(original_pSkillCalc, original_pUnit, original_pStatListEx, original_pStat, original_pSkillList, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(nParamId, &moo_pSkillCalc);
					const auto original_result = original(nParamId, &original_pSkillCalc);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pSkillCalc, original_pSkillCalc, "Comparing pUserData");
					MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				}
			}
		}

		SUBCASE("without skill calc")
		{
			for (auto i = 0; i < 74; ++i)
			{
				int32_t nParamId = i;

				// Call both implementations
				const auto moo_result = sut(nParamId, nullptr);
				const auto original_result = original(nParamId, nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<MissilesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FDAF6C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAF6C0, dll_base + 0x0006F6C0);

		SUBCASE("with skill calc")
		{
			// Input data
			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			add_stat(STAT_LEVEL, 0, random_unsigned_integer(1, 99));
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDCLASSSKILLS, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_NONCLASSSKILL, i, random_unsigned_integer(0, 5));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < 32; ++i)
			{
				add_stat(STAT_ITEM_ELEMSKILL, i, random_unsigned_integer(0, 3));
			}
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < 8 * NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDSKILL_TAB, i, random_unsigned_integer(0, 3));
			}
			for (int i = STAT_PASSIVE_FIRE_MASTERY; i <= STAT_PASSIVE_POIS_MASTERY; ++i)
			{
				add_stat(i, 0, random_unsigned_integer(0, 200));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				const auto skill_level = random_unsigned_integer(0, 20);
				const auto calc_skill_id = random_unsigned_integer(0, skills_record_count - 1);
				const auto calc_skill_level = random_unsigned_integer(0, 20);

				for (auto j = 0; j < 74; ++j)
				{
					D2SkillCalcStrc moo_pSkillCalc{};
					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					std::vector<uint32_t> moo_pStatFlags;
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pSkill{};
					D2SkillCalcStrc original_pSkillCalc{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					std::vector<uint32_t> original_pStatFlags;
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pSkill{};
					int nSkillId = i;
					int nParamId = j;
					int nUnused{};

					const auto setup_data = [this, &stat_array, &state_flags, i, class_id, skill_level, calc_skill_id, calc_skill_level](
						D2SkillCalcStrc& pSkillCalc,
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						std::vector<uint32_t>& pStatFlags,
						D2SkillListStrc& pSkillList,
						D2SkillStrc& pSkill
					) {
						pSkillCalc.pUnit = &pUnit;
						pSkillCalc.nSkillId = calc_skill_id;
						pSkillCalc.nSkillLevel = calc_skill_level;
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = class_id;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pStatFlags = state_flags;
						pStatListEx.StatFlags = pStatFlags.data();
						pUnit.pSkills = &pSkillList;
						pSkillList.pFirstSkill = &pSkill;
						pSkill.pSkillsTxt = &skills_txt[i];
						pSkill.nSkillLevel = skill_level;
						pSkill.nOwnerGUID = D2UnitInvalidGUID;
					};

					setup_data(moo_pSkillCalc, moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkillList, moo_pSkill);
					setup_data(original_pSkillCalc, original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkillList, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(nSkillId, nParamId, nUnused, &moo_pSkillCalc);
					const auto original_result = original(nSkillId, nParamId, nUnused, &original_pSkillCalc);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pSkillCalc, original_pSkillCalc, "Comparing pUserData");
					MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				}
			}
		}

		SUBCASE("without skill calc")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				int nSkillId = i;
				int nParamId = random_unsigned_integer(0, 73);
				int nUnused{};

				// Call both implementations
				const auto moo_result = sut(nSkillId, nParamId, nUnused, nullptr);
				const auto original_result = original(nSkillId, nParamId, nUnused, nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MissilesTxtFixture<NoopFixture>, "D2Common.0x6FDAF780")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAF780, dll_base + 0x0006F780);

		SUBCASE("with skill calc")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				const auto skill_id = random_unsigned_integer(0, 512);
				const auto skill_level = random_unsigned_integer(0, 20);

				for (auto j = 0; j < 44; ++j)
				{
					// Input data
					D2SkillCalcStrc moo_pSkillCalc{};
					D2UnitStrc moo_pUnit{};
					D2SkillCalcStrc original_pSkillCalc{};
					D2UnitStrc original_pUnit{};
					int nMissileId = i;
					int nParamId = j;
					int nUnused{};

					const auto setup_data = [skill_id, skill_level](
						D2SkillCalcStrc& pSkillCalc,
						D2UnitStrc& pUnit
					) {
						pSkillCalc.pUnit = &pUnit;
						pSkillCalc.nSkillId = skill_id;
						pSkillCalc.nSkillLevel = skill_level;
						pUnit.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pSkillCalc, moo_pUnit);
					setup_data(original_pSkillCalc, original_pUnit);

					// Call both implementations
					const auto moo_result = sut(nMissileId, nParamId, nUnused, &moo_pSkillCalc);
					const auto original_result = original(nMissileId, nParamId, nUnused, &original_pSkillCalc);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pSkillCalc, original_pSkillCalc, "Comparing pUserData");
				}
			}
		}

		SUBCASE("without skill calc")
		{
			for (auto i = 0; i < missiles_record_count; ++i)
			{
				int nMissileId = i;
				int nParamId = random_unsigned_integer(0, 43);
				int nUnused{};

				// Call both implementations
				const auto moo_result = sut(nMissileId, nParamId, nUnused, nullptr);
				const auto original_result = original(nMissileId, nParamId, nUnused, nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<MissilesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDAF7A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDAF7A0, dll_base + 0x0006F7A0);

		SUBCASE("with skill calc")
		{
			// Input data
			std::vector<D2StatStrc> stat_array(5);
			stat_array[0].nStat = STAT_LEVEL;
			stat_array[0].nValue = random_unsigned_integer(1, 99);

			for (auto i = 1; i < 5; ++i)
			{
				stat_array[i].nStat = static_cast<uint16_t>(STAT_PASSIVE_FIRE_MASTERY + i - 1);
				stat_array[i].nValue = random_unsigned_integer(0, 200);
			}

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j < 74; ++j)
				{
					const auto calc_skill_id = random_unsigned_integer(0, skills_record_count - 1);
					const auto calc_skill_level = random_unsigned_integer(0, 20);

					D2SkillCalcStrc moo_pSkillCalc{};
					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2SkillCalcStrc original_pSkillCalc{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					int nSkillId = i;
					int a2 = random_unsigned_integer(0, 73);
					int a3 = j;

					const auto setup_data = [&stat_array, calc_skill_id, calc_skill_level](
						D2SkillCalcStrc& pSkillCalc,
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat
					) {
						pSkillCalc.pUnit = &pUnit;
						pSkillCalc.nSkillId = calc_skill_id;
						pSkillCalc.nSkillLevel = calc_skill_level;
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					};

					setup_data(moo_pSkillCalc, moo_pUnit, moo_pStatListEx, moo_pStat);
					setup_data(original_pSkillCalc, original_pUnit, original_pStatListEx, original_pStat);

					// Call both implementations
					const auto moo_result = sut(nSkillId, a2, a3, &moo_pSkillCalc);
					const auto original_result = original(nSkillId, a2, a3, &original_pSkillCalc);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pSkillCalc, original_pSkillCalc, "Comparing pUserData");
				}
			}
		}

		SUBCASE("without skill calc")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				int nSkillId = i;
				int a2 = random_unsigned_integer(0, 73);
				int a3 = random_unsigned_integer(0, 73);

				// Call both implementations
				const auto moo_result = sut(nSkillId, a2, a3, nullptr);
				const auto original_result = original(nSkillId, a2, a3, nullptr);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<MissilesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FDAF7E0 (#11276)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_EvaluateSkillFormula, dll_base + 0x0006F7E0);

		SUBCASE("")
		{
			// Input data
			std::vector<uint8_t> skills_code;
			std::vector<unsigned int> param_calcs;
			std::vector<unsigned int> skill_level_calcs;

			for (auto i = 0; i < 74; ++i)
			{
				// <param i> + <constant>
				param_calcs.push_back(static_cast<unsigned int>(skills_code.size()));
				skills_code.push_back(AST_Callback_Param_UInt8);
				skills_code.push_back(static_cast<uint8_t>(i));
				skills_code.push_back(AST_Raw_Int8);
				skills_code.push_back(static_cast<uint8_t>(random_unsigned_integer(1, 100)));
				skills_code.push_back(AST_Addition);
				skills_code.push_back(AST_None);
			}

			for (auto i = 0; i < skills_record_count; ++i)
			{
				// skill(<skill i>).<param 16>, evaluated by sub_6FDAF6C0
				skill_level_calcs.push_back(static_cast<unsigned int>(skills_code.size()));
				skills_code.push_back(AST_Raw_Int16);
				skills_code.push_back(static_cast<uint8_t>(i & 0xFF));
				skills_code.push_back(static_cast<uint8_t>((i >> 8) & 0xFF));
				skills_code.push_back(AST_Raw_Int8);
				skills_code.push_back(16);
				skills_code.push_back(AST_CallbackTable);
				skills_code.push_back(3);
				skills_code.push_back(AST_None);
			}

			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			add_stat(STAT_LEVEL, 0, random_unsigned_integer(1, 99));
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDCLASSSKILLS, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_NONCLASSSKILL, i, random_unsigned_integer(0, 5));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < 32; ++i)
			{
				add_stat(STAT_ITEM_ELEMSKILL, i, random_unsigned_integer(0, 3));
			}
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < 8 * NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDSKILL_TAB, i, random_unsigned_integer(0, 3));
			}
			for (int i = STAT_PASSIVE_FIRE_MASTERY; i <= STAT_PASSIVE_POIS_MASTERY; ++i)
			{
				add_stat(i, 0, random_unsigned_integer(0, 200));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			const auto previous_skills_code = sgptDataTables->pSkillsCode;
			const auto previous_skills_code_size = sgptDataTables->nSkillsCodeSize;
			sgptDataTables->pSkillsCode = reinterpret_cast<FOGASTNodeStrc*>(skills_code.data());
			sgptDataTables->nSkillsCodeSize = static_cast<unsigned int>(skills_code.size());

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				const auto skill_level = random_unsigned_integer(0, 20);

				std::vector<unsigned int> calcs = param_calcs;
				calcs.push_back(skill_level_calcs[i]);
				calcs.push_back(static_cast<unsigned int>(skills_code.size()));

				for (const auto calc : calcs)
				{
					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					std::vector<uint32_t> moo_pStatFlags;
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pSkill{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					std::vector<uint32_t> original_pStatFlags;
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pSkill{};
					unsigned int nCalc = calc;
					int nSkillId = i;
					int nSkillLevel = skill_level;

					const auto setup_data = [this, &stat_array, &state_flags, i, class_id, skill_level](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						std::vector<uint32_t>& pStatFlags,
						D2SkillListStrc& pSkillList,
						D2SkillStrc& pSkill
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = class_id;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pStatFlags = state_flags;
						pStatListEx.StatFlags = pStatFlags.data();
						pUnit.pSkills = &pSkillList;
						pSkillList.pFirstSkill = &pSkill;
						pSkill.pSkillsTxt = &skills_txt[i];
						pSkill.nSkillLevel = skill_level;
						pSkill.nOwnerGUID = D2UnitInvalidGUID;
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkillList, moo_pSkill);
					setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkillList, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nCalc, nSkillId, nSkillLevel);
					const auto original_result = original(&original_pUnit, nCalc, nSkillId, nSkillLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				}
			}

			sgptDataTables->pSkillsCode = previous_skills_code;
			sgptDataTables->nSkillsCodeSize = previous_skills_code_size;
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<MissilesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FDAF850 (#11302)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_EvaluateSkillDescFormula, dll_base + 0x0006F850);

		SUBCASE("")
		{
			// Input data
			std::vector<uint8_t> skilldesc_code;
			std::vector<unsigned int> param_calcs;
			std::vector<unsigned int> skill_level_calcs;

			for (auto i = 0; i < 74; ++i)
			{
				// <param i> * <constant>
				param_calcs.push_back(static_cast<unsigned int>(skilldesc_code.size()));
				skilldesc_code.push_back(AST_Callback_Param_UInt8);
				skilldesc_code.push_back(static_cast<uint8_t>(i));
				skilldesc_code.push_back(AST_Raw_Int8);
				skilldesc_code.push_back(static_cast<uint8_t>(random_unsigned_integer(1, 100)));
				skilldesc_code.push_back(AST_Multipliction);
				skilldesc_code.push_back(AST_None);
			}

			for (auto i = 0; i < skills_record_count; ++i)
			{
				// skill(<skill i>).<param 16>, evaluated by sub_6FDAF6C0
				skill_level_calcs.push_back(static_cast<unsigned int>(skilldesc_code.size()));
				skilldesc_code.push_back(AST_Raw_Int16);
				skilldesc_code.push_back(static_cast<uint8_t>(i & 0xFF));
				skilldesc_code.push_back(static_cast<uint8_t>((i >> 8) & 0xFF));
				skilldesc_code.push_back(AST_Raw_Int8);
				skilldesc_code.push_back(16);
				skilldesc_code.push_back(AST_CallbackTable);
				skilldesc_code.push_back(3);
				skilldesc_code.push_back(AST_None);
			}

			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			add_stat(STAT_LEVEL, 0, random_unsigned_integer(1, 99));
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDCLASSSKILLS, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_NONCLASSSKILL, i, random_unsigned_integer(0, 5));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < 32; ++i)
			{
				add_stat(STAT_ITEM_ELEMSKILL, i, random_unsigned_integer(0, 3));
			}
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < 8 * NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDSKILL_TAB, i, random_unsigned_integer(0, 3));
			}
			for (int i = STAT_PASSIVE_FIRE_MASTERY; i <= STAT_PASSIVE_POIS_MASTERY; ++i)
			{
				add_stat(i, 0, random_unsigned_integer(0, 200));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			const auto previous_skilldesc_code = sgptDataTables->pSkillDescCode;
			const auto previous_skilldesc_code_size = sgptDataTables->nSkillDescCodeSize;
			sgptDataTables->pSkillDescCode = reinterpret_cast<FOGASTNodeStrc*>(skilldesc_code.data());
			sgptDataTables->nSkillDescCodeSize = static_cast<unsigned int>(skilldesc_code.size());

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				const auto skill_level = random_unsigned_integer(0, 20);

				std::vector<unsigned int> calcs = param_calcs;
				calcs.push_back(skill_level_calcs[i]);
				calcs.push_back(static_cast<unsigned int>(skilldesc_code.size()));

				for (const auto calc : calcs)
				{
					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					std::vector<uint32_t> moo_pStatFlags;
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pSkill{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					std::vector<uint32_t> original_pStatFlags;
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pSkill{};
					unsigned int nCalc = calc;
					int nSkillId = i;
					int nSkillLevel = skill_level;

					const auto setup_data = [this, &stat_array, &state_flags, i, class_id, skill_level](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						std::vector<uint32_t>& pStatFlags,
						D2SkillListStrc& pSkillList,
						D2SkillStrc& pSkill
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = class_id;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pStatFlags = state_flags;
						pStatListEx.StatFlags = pStatFlags.data();
						pUnit.pSkills = &pSkillList;
						pSkillList.pFirstSkill = &pSkill;
						pSkill.pSkillsTxt = &skills_txt[i];
						pSkill.nSkillLevel = skill_level;
						pSkill.nOwnerGUID = D2UnitInvalidGUID;
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkillList, moo_pSkill);
					setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkillList, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nCalc, nSkillId, nSkillLevel);
					const auto original_result = original(&original_pUnit, nCalc, nSkillId, nSkillLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				}
			}

			sgptDataTables->pSkillDescCode = previous_skilldesc_code;
			sgptDataTables->nSkillDescCodeSize = previous_skilldesc_code_size;
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDAF8C0 (#10940)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_RefreshSkill, dll_base + 0x0006F8C0);

		const auto flag_count = (states_record_count >> 5) + 1;

		SUBCASE("skill not learned")
		{
			// Input data
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<uint32_t> moo_pStatFlags;
				D2SkillListStrc moo_pSkillList{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<uint32_t> original_pStatFlags;
				D2SkillListStrc original_pSkillList{};
				int nSkillId = i;

				const auto setup_data = [&state_flags](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<uint32_t>& pStatFlags,
					D2SkillListStrc& pSkillList
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pUnit.pSkills = &pSkillList;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags, moo_pSkillList);
				setup_data(original_pUnit, original_pStatListEx, original_pStatFlags, original_pSkillList);

				// Call both implementations
				sut(&moo_pUnit, nSkillId);
				original(&original_pUnit, nSkillId);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}

		SUBCASE("skill learned")
		{
			// Input data
			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto skill_level = random_unsigned_integer(0, 20);

				// The unit's stat list may get extended and reallocated, so it has to be allocated from the memory pool
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc* moo_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* moo_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2StatStrc* moo_pStat = static_cast<D2StatStrc*>(D2_CALLOC_POOL(nullptr, stat_array.size() * sizeof(D2StatStrc)));
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc* original_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* original_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2StatStrc* original_pStat = static_cast<D2StatStrc*>(D2_CALLOC_POOL(nullptr, stat_array.size() * sizeof(D2StatStrc)));
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkill{};
				int nSkillId = i;

				const auto setup_data = [this, &stat_array, &state_flags, flag_count, i, skill_level](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					uint32_t* pStatFlags,
					D2StatStrc* pStat,
					D2SkillListStrc& pSkillList,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = 1;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags = STATLIST_EXTENDED;
					pStatListEx.dwOwnerType = UNIT_PLAYER;
					pStatListEx.dwOwnerId = 1;
					pStatListEx.pOwner = &pUnit;
					std::memcpy(pStatFlags, state_flags.data(), 2 * flag_count * sizeof(uint32_t));
					pStatListEx.StatFlags = pStatFlags;
					std::memcpy(pStat, stat_array.data(), stat_array.size() * sizeof(D2StatStrc));
					pStatListEx.FullStats.pStat = pStat;
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(stat_array.size());
					pStatListEx.FullStats.nCapacity = static_cast<uint16_t>(stat_array.size());
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkill;
					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nSkillLevel = skill_level;
					pSkill.nOwnerGUID = D2UnitInvalidGUID;
				};

				setup_data(moo_pUnit, *moo_pStatListEx, moo_pStatFlags, moo_pStat, moo_pSkillList, moo_pSkill);
				setup_data(original_pUnit, *original_pStatListEx, original_pStatFlags, original_pStat, original_pSkillList, original_pSkill);

				// Call both implementations
				sut(&moo_pUnit, nSkillId);
				original(&original_pUnit, nSkillId);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				STATLIST_FreeStatListEx(&moo_pUnit);
				STATLIST_FreeStatListEx(&original_pUnit);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDAFB40 (#10941)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_RefreshPassiveSkills, dll_base + 0x0006FB40);

		SUBCASE("")
		{
			// Input data
			std::vector<uint16_t> passive_skills;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				if (skills_txt[i].nPassiveState >= 0)
				{
					passive_skills.push_back(static_cast<uint16_t>(i));
				}
			}

			const auto flag_count = (states_record_count >> 5) + 1;
			const auto skill_count = static_cast<int>(passive_skills.size());

			std::vector<uint32_t> state_flags(2 * flag_count);
			std::vector<uint32_t> skill_levels(skill_count);

			const auto previous_passive_skills = sgptDataTables->pPassiveSkills;
			const auto previous_passive_skill_count = sgptDataTables->nPassiveSkills;
			sgptDataTables->pPassiveSkills = passive_skills.data();
			sgptDataTables->nPassiveSkills = skill_count;

			for (auto k = 0; k < 10; ++k)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				for (auto& skill_level : skill_levels)
				{
					skill_level = random_unsigned_integer(0, 20);
				}

				// The unit's stat list may get extended and reallocated, so it has to be allocated from the memory pool
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc* moo_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* moo_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc moo_pSkillList{};
				std::vector<D2SkillStrc> moo_pSkills(skill_count);
				D2UnitStrc original_pUnit{};
				D2StatListExStrc* original_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* original_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc original_pSkillList{};
				std::vector<D2SkillStrc> original_pSkills(skill_count);

				const auto setup_data = [this, &state_flags, &passive_skills, &skill_levels, flag_count, skill_count](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					uint32_t* pStatFlags,
					D2SkillListStrc& pSkillList,
					std::vector<D2SkillStrc>& pSkills
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = 1;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags = STATLIST_EXTENDED;
					pStatListEx.dwOwnerType = UNIT_PLAYER;
					pStatListEx.dwOwnerId = 1;
					pStatListEx.pOwner = &pUnit;
					std::memcpy(pStatFlags, state_flags.data(), 2 * flag_count * sizeof(uint32_t));
					pStatListEx.StatFlags = pStatFlags;
					pUnit.pSkills = &pSkillList;

					for (auto i = 0; i < skill_count; ++i)
					{
						pSkills[i].pSkillsTxt = &skills_txt[passive_skills[i]];
						pSkills[i].nSkillLevel = skill_levels[i];
						pSkills[i].nOwnerGUID = D2UnitInvalidGUID;
						pSkills[i].pNextSkill = i + 1 < skill_count ? &pSkills[i + 1] : nullptr;
					}

					pSkillList.pFirstSkill = skill_count > 0 ? &pSkills[0] : nullptr;
				};

				setup_data(moo_pUnit, *moo_pStatListEx, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, *original_pStatListEx, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit);
				original(&original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				STATLIST_FreeStatListEx(&moo_pUnit);
				STATLIST_FreeStatListEx(&original_pUnit);
			}

			sgptDataTables->pPassiveSkills = previous_passive_skills;
			sgptDataTables->nPassiveSkills = previous_passive_skill_count;
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDAFC30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetHighestLevelSkillFromSkillId, dll_base + 0x0006FC30);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 8;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(0, 20);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;

				const auto setup_data = [this, &skill_ids, &skill_levels, &owner_guids](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nSkillLevel = skill_levels[j];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pSkillList, original_pSkills);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSkillId);
				const auto original_result = original(&original_pUnit, nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(moo_result ? moo_result - moo_pSkills : -1, original_result ? original_result - original_pSkills : -1);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFC80 (#10942)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkillModeFromUnit, dll_base + 0x0006FC80);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_mode = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2SkillStrc moo_pSkill{};
			D2UnitStrc original_pUnit{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [skill_mode](
				D2UnitStrc& pUnit,
				D2SkillStrc& pSkill
			) {
				pSkill.dwSkillMode = skill_mode;
			};

			setup_data(moo_pUnit, moo_pSkill);
			setup_data(original_pUnit, original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
			const auto original_result = original(&original_pUnit, &original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFCA0 (#11049)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_Return1, dll_base + 0x0006FCA0);
		
		SUBCASE("")
		{
			int a1{};

			// Call both implementations
			const auto moo_result = sut(a1);
			const auto original_result = original(a1);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDAFCB0 (#10944)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetRange, dll_base + 0x0006FCB0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				D2SkillStrc moo_pSkill{};
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, i](
					D2SkillStrc& pSkill
				) {
					pSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pSkill);
				setup_data(original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pSkill);
				const auto original_result = original(&original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFCD0 (#10945)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_AllocSkillList, dll_base + 0x0006FCD0);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Clean up
			D2_FREE_POOL(nullptr, moo_result);
			D2_FREE_POOL(nullptr, original_result);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<CharStatsTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>>, "D2Common.0x6FDAFD10 (#10946)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_InitSkillList, dll_base + 0x0006FD10);

		SUBCASE("empty skill list")
		{
			for (auto i = 0; i < charstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};

				const auto setup_data = [i](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = i;
					pUnit.pSkills = &pSkillList;
				};

				setup_data(moo_pUnit, moo_pSkillList);
				setup_data(original_pUnit, original_pSkillList);

				// Call both implementations
				sut(&moo_pUnit);
				original(&original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				for (auto pSkill = moo_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				for (auto pSkill = original_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}
			}
		}

		SUBCASE("skill list with base skill")
		{
			for (auto i = 0; i < charstats_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = i;
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkill;
					pSkill.pSkillsTxt = &skills_txt[0];
					pSkill.nSkillLevel = 1;
					pSkill.nOwnerGUID = D2UnitInvalidGUID;
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkill);
				setup_data(original_pUnit, original_pSkillList, original_pSkill);

				// Call both implementations
				sut(&moo_pUnit);
				original(&original_pUnit);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				CHECK_EQ(moo_pSkillList.pLeftSkill, &moo_pSkill);
				CHECK_EQ(original_pSkillList.pLeftSkill, &original_pSkill);
				CHECK_EQ(moo_pSkillList.pRightSkill, &moo_pSkill);
				CHECK_EQ(original_pSkillList.pRightSkill, &original_pSkill);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFEA0 (#10947)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetNextSkill, dll_base + 0x0006FEA0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc moo_pNextSkill{};
			D2SkillStrc original_pSkill{};
			D2SkillStrc original_pNextSkill{};

			const auto setup_data = [flags](
				D2SkillStrc& pSkill,
				D2SkillStrc& pNextSkill
			) {
				pSkill.pNextSkill = &pNextSkill;
				pNextSkill.dwFlags = flags;
			};

			setup_data(moo_pSkill, moo_pNextSkill);
			setup_data(original_pSkill, original_pNextSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFEA0 (#10948)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetFirstSkillFromSkillList, dll_base + 0x0006FEA0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pFirstSkill{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pFirstSkill{};

			const auto setup_data = [flags](
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pFirstSkill
			) {
				pSkillList.pFirstSkill = &pFirstSkill;
				pFirstSkill.dwFlags = flags;
			};

			setup_data(moo_pSkillList, moo_pFirstSkill);
			setup_data(original_pSkillList, original_pFirstSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkillList);
			const auto original_result = original(&original_pSkillList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFEC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetLeftSkillFromSkillList, dll_base + 0x0006FEC0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pLeftSkill{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pLeftSkill{};

			const auto setup_data = [flags](
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pLeftSkill
			) {
				pSkillList.pLeftSkill = &pLeftSkill;
				pLeftSkill.dwFlags = flags;
			};

			setup_data(moo_pSkillList, moo_pLeftSkill);
			setup_data(original_pSkillList, original_pLeftSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkillList);
			const auto original_result = original(&original_pSkillList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFEF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetRightSkillFromSkillList, dll_base + 0x0006FEF0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pRightSkill{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pRightSkill{};

			const auto setup_data = [flags](
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pRightSkill
			) {
				pSkillList.pRightSkill = &pRightSkill;
				pRightSkill.dwFlags = flags;
			};

			setup_data(moo_pSkillList, moo_pRightSkill);
			setup_data(original_pSkillList, original_pRightSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkillList);
			const auto original_result = original(&original_pSkillList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFF20")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetUsedSkillInSkillList, dll_base + 0x0006FF20);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pUsedSkill{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pUsedSkill{};

			const auto setup_data = [flags](
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pUsedSkill
			) {
				pUsedSkill.dwFlags = flags;
			};

			setup_data(moo_pSkillList, moo_pUsedSkill);
			setup_data(original_pSkillList, original_pUsedSkill);

			// Call both implementations
			sut(&moo_pSkillList, &moo_pUsedSkill);
			original(&original_pSkillList, &original_pUsedSkill);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			MOO_CHECK_EQ(moo_pUsedSkill, original_pUsedSkill, "Comparing pUsedSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAFF30")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetUsedSkillFromSkillList, dll_base + 0x0006FF30);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2SkillListStrc moo_pSkillList{};
			D2SkillStrc moo_pUsedSkill{};
			D2SkillListStrc original_pSkillList{};
			D2SkillStrc original_pUsedSkill{};

			const auto setup_data = [flags](
				D2SkillListStrc& pSkillList,
				D2SkillStrc& pUsedSkill
			) {
				pSkillList.pUsedSkill = &pUsedSkill;
				pUsedSkill.dwFlags = flags;
			};

			setup_data(moo_pSkillList, moo_pUsedSkill);
			setup_data(original_pSkillList, original_pUsedSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkillList);
			const auto original_result = original(&original_pSkillList);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDAFF40 (#10949)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkillById, dll_base + 0x0006FF40);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 8;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(0, 20);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 3);
				}

				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;
				D2UnitGUID nOwnerGUID = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 3);

				const auto setup_data = [this, &skill_ids, &skill_levels, &owner_guids](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nSkillLevel = skill_levels[j];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pSkillList, original_pSkills);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSkillId, nOwnerGUID);
				const auto original_result = original(&original_pUnit, nSkillId, nOwnerGUID);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(moo_result ? moo_result - moo_pSkills : -1, original_result ? original_result - original_pSkills : -1);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDAFF80 (#10950)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetHighestLevelSkillFromUnitAndId, dll_base + 0x0006FF80);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 8;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(0, 20);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;

				const auto setup_data = [this, &skill_ids, &skill_levels, &owner_guids](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nSkillLevel = skill_levels[j];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pSkillList, original_pSkills);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSkillId);
				const auto original_result = original(&original_pUnit, nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(moo_result ? moo_result - moo_pSkills : -1, original_result ? original_result - original_pSkills : -1);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDAFFD0 (#10951)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_RemoveSkill, dll_base + 0x0006FFD0);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 4;
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			// Skill 0 (Attack) is used as fallback for the active skills and must therefore not be removed
			for (auto i = 1; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				// The first skill is always Attack
				uint32_t skill_ids[skill_count]{ SKILL_ATTACK };
				uint32_t skill_levels[skill_count]{ 1 };
				D2UnitGUID owner_guids[skill_count]{ D2UnitInvalidGUID };

				for (auto j = 1; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(1, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(1, 3);
					owner_guids[j] = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				const auto left_skill_index = random_unsigned_integer(0, skill_count - 1);
				const auto right_skill_index = random_unsigned_integer(0, skill_count - 1);
				const auto used_skill_index = random_unsigned_integer(0, skill_count);

				// Skills get freed by the function, so they have to be allocated from the memory pool
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc* moo_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* moo_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc* moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc* original_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* original_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc* original_pSkills[skill_count]{};
				int nSkillId = i;
				const char* szFile = __FILE__;
				int nLine = __LINE__;

				for (auto j = 0; j < skill_count; ++j)
				{
					moo_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
					original_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
				}

				const auto setup_data = [this, &state_flags, &skill_ids, &skill_levels, &owner_guids, flag_count, left_skill_index, right_skill_index, used_skill_index](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					uint32_t* pStatFlags,
					D2SkillListStrc& pSkillList,
					D2SkillStrc* (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = 1;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags = STATLIST_EXTENDED;
					pStatListEx.dwOwnerType = UNIT_PLAYER;
					pStatListEx.dwOwnerId = 1;
					pStatListEx.pOwner = &pUnit;
					std::memcpy(pStatFlags, state_flags.data(), 2 * flag_count * sizeof(uint32_t));
					pStatListEx.StatFlags = pStatFlags;
					pUnit.pSkills = &pSkillList;

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j]->pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j]->nSkillLevel = skill_levels[j];
						pSkills[j]->nOwnerGUID = owner_guids[j];
						pSkills[j]->pNextSkill = j + 1 < skill_count ? pSkills[j + 1] : nullptr;
					}

					pSkillList.pFirstSkill = pSkills[0];
					pSkillList.pLeftSkill = pSkills[left_skill_index];
					pSkillList.pRightSkill = pSkills[right_skill_index];
					pSkillList.pUsedSkill = used_skill_index < skill_count ? pSkills[used_skill_index] : nullptr;
				};

				setup_data(moo_pUnit, *moo_pStatListEx, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, *original_pStatListEx, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit, nSkillId, szFile, nLine);
				original(&original_pUnit, nSkillId, szFile, nLine);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				for (auto pSkill = moo_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				for (auto pSkill = original_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				STATLIST_FreeStatListEx(&moo_pUnit);
				STATLIST_FreeStatListEx(&original_pUnit);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDAFFF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_SKILLS_RemoveSkill_6FDAFFF0, dll_base + 0x0006FFF0);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 4;
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			// Skill 0 (Attack) is used as fallback for the active skills and must therefore not be removed
			for (auto i = 1; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				// The first skill is always Attack
				uint32_t skill_ids[skill_count]{ SKILL_ATTACK };
				uint32_t skill_levels[skill_count]{ 1 };
				D2UnitGUID owner_guids[skill_count]{ D2UnitInvalidGUID };

				for (auto j = 1; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(1, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(1, 3);
					owner_guids[j] = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				const auto left_skill_index = random_unsigned_integer(0, skill_count - 1);
				const auto right_skill_index = random_unsigned_integer(0, skill_count - 1);
				const auto used_skill_index = random_unsigned_integer(0, skill_count);

				// Skills get freed by the function, so they have to be allocated from the memory pool
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc* moo_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* moo_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc* moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc* original_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* original_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc* original_pSkills[skill_count]{};
				int nSkillId = i;
				int bDecrementAndCheckSkillLevel = random_unsigned_integer(0, 1);
				const char* szFile = __FILE__;
				int nLine = __LINE__;

				for (auto j = 0; j < skill_count; ++j)
				{
					moo_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
					original_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
				}

				const auto setup_data = [this, &state_flags, &skill_ids, &skill_levels, &owner_guids, flag_count, left_skill_index, right_skill_index, used_skill_index](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					uint32_t* pStatFlags,
					D2SkillListStrc& pSkillList,
					D2SkillStrc* (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = 1;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags = STATLIST_EXTENDED;
					pStatListEx.dwOwnerType = UNIT_PLAYER;
					pStatListEx.dwOwnerId = 1;
					pStatListEx.pOwner = &pUnit;
					std::memcpy(pStatFlags, state_flags.data(), 2 * flag_count * sizeof(uint32_t));
					pStatListEx.StatFlags = pStatFlags;
					pUnit.pSkills = &pSkillList;

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j]->pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j]->nSkillLevel = skill_levels[j];
						pSkills[j]->nOwnerGUID = owner_guids[j];
						pSkills[j]->pNextSkill = j + 1 < skill_count ? pSkills[j + 1] : nullptr;
					}

					pSkillList.pFirstSkill = pSkills[0];
					pSkillList.pLeftSkill = pSkills[left_skill_index];
					pSkillList.pRightSkill = pSkills[right_skill_index];
					pSkillList.pUsedSkill = used_skill_index < skill_count ? pSkills[used_skill_index] : nullptr;
				};

				setup_data(moo_pUnit, *moo_pStatListEx, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, *original_pStatListEx, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit, nSkillId, bDecrementAndCheckSkillLevel, szFile, nLine);
				original(&original_pUnit, nSkillId, bDecrementAndCheckSkillLevel, szFile, nLine);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				for (auto pSkill = moo_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				for (auto pSkill = original_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				STATLIST_FreeStatListEx(&moo_pUnit);
				STATLIST_FreeStatListEx(&original_pUnit);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB0270 (#10958)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10958, dll_base + 0x00070270);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2SkillListStrc moo_pSkillList{};
			D2UnitStrc original_pUnit{};
			D2SkillListStrc original_pSkillList{};
			int a2 = random_unsigned_integer();

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2SkillListStrc& pSkillList
			) {
				pUnit.pSkills = &pSkillList;
			};

			setup_data(moo_pUnit, moo_pSkillList);
			setup_data(original_pUnit, original_pSkillList);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, a2);
			const auto original_result = original(&original_pUnit, a2);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB02A0 (#10959)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10959, dll_base + 0x000702A0);
		
		SUBCASE("")
		{
			// Input data
			const auto a2 = random_unsigned_integer();

			D2UnitStrc moo_pUnit{};
			D2SkillListStrc moo_pSkillList{};
			D2UnitStrc original_pUnit{};
			D2SkillListStrc original_pSkillList{};

			const auto setup_data = [a2](
				D2UnitStrc& pUnit,
				D2SkillListStrc& pSkillList
			) {
				pUnit.pSkills = &pSkillList;
				pSkillList.unk014 = a2;
			};

			setup_data(moo_pUnit, moo_pSkillList);
			setup_data(original_pUnit, original_pSkillList);

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB02C0 (#10960)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_FreeSkillList, dll_base + 0x000702C0);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 4;

			// The skill list and skills get freed by the function, so they have to be allocated from the memory pool
			D2UnitStrc moo_pUnit{};
			D2SkillListStrc* moo_pSkillList = D2_CALLOC_STRC_POOL(nullptr, D2SkillListStrc);
			D2SkillStrc* moo_pSkills[skill_count]{};
			D2UnitStrc original_pUnit{};
			D2SkillListStrc* original_pSkillList = D2_CALLOC_STRC_POOL(nullptr, D2SkillListStrc);
			D2SkillStrc* original_pSkills[skill_count]{};

			for (auto i = 0; i < skill_count; ++i)
			{
				moo_pSkills[i] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
				original_pSkills[i] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
			}

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2SkillListStrc& pSkillList,
				D2SkillStrc* (&pSkills)[skill_count]
			) {
				pUnit.dwUnitType = UNIT_PLAYER;
				pUnit.pSkills = &pSkillList;
				pSkillList.pFirstSkill = pSkills[0];
				pSkillList.pLeftSkill = pSkills[0];
				pSkillList.pRightSkill = pSkills[0];

				for (auto i = 0; i < skill_count; ++i)
				{
					pSkills[i]->pNextSkill = i + 1 < skill_count ? pSkills[i + 1] : nullptr;
				}
			};

			setup_data(moo_pUnit, *moo_pSkillList, moo_pSkills);
			setup_data(original_pUnit, *original_pSkillList, original_pSkills);

			// Call both implementations
			sut(&moo_pUnit);
			original(&original_pUnit);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			CHECK_EQ(moo_pUnit.pSkills, nullptr);
			CHECK_EQ(original_pUnit.pSkills, nullptr);
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB0320 (#10952)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_AddSkill, dll_base + 0x00070320);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 3;
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(1, 25);
					owner_guids[j] = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				// Skills get added to the skill list, so they have to be allocated from the memory pool to be able to free them afterwards
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc* moo_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* moo_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc* moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc* original_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* original_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc* original_pSkills[skill_count]{};
				int nSkillId = i;

				for (auto j = 0; j < skill_count; ++j)
				{
					moo_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
					original_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
				}

				const auto setup_data = [this, &state_flags, &skill_ids, &skill_levels, &owner_guids, flag_count, unit_type, class_id](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					uint32_t* pStatFlags,
					D2SkillListStrc& pSkillList,
					D2SkillStrc* (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.dwClassId = class_id;
					pUnit.dwUnitId = 1;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags = STATLIST_EXTENDED;
					pStatListEx.dwOwnerType = unit_type;
					pStatListEx.dwOwnerId = 1;
					pStatListEx.pOwner = &pUnit;
					std::memcpy(pStatFlags, state_flags.data(), 2 * flag_count * sizeof(uint32_t));
					pStatListEx.StatFlags = pStatFlags;
					pUnit.pSkills = &pSkillList;

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j]->pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j]->nSkillLevel = skill_levels[j];
						pSkills[j]->nOwnerGUID = owner_guids[j];
						pSkills[j]->pNextSkill = j + 1 < skill_count ? pSkills[j + 1] : nullptr;
					}

					pSkillList.pFirstSkill = pSkills[0];
				};

				setup_data(moo_pUnit, *moo_pStatListEx, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, *original_pStatListEx, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSkillId);
				const auto original_result = original(&original_pUnit, nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				for (auto pSkill = moo_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				for (auto pSkill = original_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				STATLIST_FreeStatListEx(&moo_pUnit);
				STATLIST_FreeStatListEx(&original_pUnit);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB04D0 (#10953)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_AssignSkill, dll_base + 0x000704D0);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 4;
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			// Skill 0 (Attack) is used as fallback for the active skills and must therefore not be removed
			for (auto i = 1; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);

				// The first skill is always Attack
				uint32_t skill_ids[skill_count]{ SKILL_ATTACK };
				uint32_t skill_levels[skill_count]{ 1 };
				D2UnitGUID owner_guids[skill_count]{ D2UnitInvalidGUID };

				for (auto j = 1; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(1, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(1, 3);
					owner_guids[j] = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				const auto left_skill_index = random_unsigned_integer(0, skill_count - 1);
				const auto right_skill_index = random_unsigned_integer(0, skill_count - 1);
				const auto used_skill_index = random_unsigned_integer(0, skill_count);

				// Skills get added to and freed from the skill list, so they have to be allocated from the memory pool
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc* moo_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* moo_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc* moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc* original_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* original_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc* original_pSkills[skill_count]{};
				int nSkillId = i;
				int nSkillLevel = random_unsigned_integer(0, 3);
				BOOL bRemove = random_unsigned_integer(0, 1);
				const char* szFile = __FILE__;
				int nLine = __LINE__;

				for (auto j = 0; j < skill_count; ++j)
				{
					moo_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
					original_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
				}

				const auto setup_data = [this, &state_flags, &skill_ids, &skill_levels, &owner_guids, flag_count, class_id, left_skill_index, right_skill_index, used_skill_index](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					uint32_t* pStatFlags,
					D2SkillListStrc& pSkillList,
					D2SkillStrc* (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.dwUnitId = 1;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags = STATLIST_EXTENDED;
					pStatListEx.dwOwnerType = UNIT_PLAYER;
					pStatListEx.dwOwnerId = 1;
					pStatListEx.pOwner = &pUnit;
					std::memcpy(pStatFlags, state_flags.data(), 2 * flag_count * sizeof(uint32_t));
					pStatListEx.StatFlags = pStatFlags;
					pUnit.pSkills = &pSkillList;

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j]->pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j]->nSkillLevel = skill_levels[j];
						pSkills[j]->nOwnerGUID = owner_guids[j];
						pSkills[j]->pNextSkill = j + 1 < skill_count ? pSkills[j + 1] : nullptr;
					}

					pSkillList.pFirstSkill = pSkills[0];
					pSkillList.pLeftSkill = pSkills[left_skill_index];
					pSkillList.pRightSkill = pSkills[right_skill_index];
					pSkillList.pUsedSkill = used_skill_index < skill_count ? pSkills[used_skill_index] : nullptr;
				};

				setup_data(moo_pUnit, *moo_pStatListEx, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, *original_pStatListEx, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit, nSkillId, nSkillLevel, bRemove, szFile, nLine);
				original(&original_pUnit, nSkillId, nSkillLevel, bRemove, szFile, nLine);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				for (auto pSkill = moo_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				for (auto pSkill = original_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				STATLIST_FreeStatListEx(&moo_pUnit);
				STATLIST_FreeStatListEx(&original_pUnit);
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB05E0 (#10954)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10954, dll_base + 0x000705E0);

		const BOOL bFreeMemory = GENERATE(FALSE, TRUE);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 4;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				const D2UnitGUID owner_guid = random_unsigned_integer(0, 100);

				// The first skill is always Attack, which is used as active skill
				uint32_t skill_ids[skill_count]{ SKILL_ATTACK };
				uint32_t skill_levels[skill_count]{ 1 };
				uint32_t skill_charges[skill_count]{ 0 };
				D2UnitGUID owner_guids[skill_count]{ D2UnitInvalidGUID };

				for (auto j = 1; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(1, 20);
					skill_charges[j] = random_unsigned_integer(0, 100);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : owner_guid;
				}

				const auto used_skill_index = random_unsigned_integer(0, skill_count);

				// Skills get added to and freed from the skill list, so they have to be allocated from the memory pool
				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc* moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc* original_pSkills[skill_count]{};
				D2UnitGUID nOwnerGUID = owner_guid;
				int nSkillId = i;
				int nSkillLevel = random_unsigned_integer(0, 20);
				int nCharges = random_unsigned_integer(0, 100);

				for (auto j = 0; j < skill_count; ++j)
				{
					moo_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
					original_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
				}

				const auto setup_data = [this, &skill_ids, &skill_levels, &skill_charges, &owner_guids, used_skill_index](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc* (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pSkills = &pSkillList;

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j]->pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j]->nSkillLevel = skill_levels[j];
						pSkills[j]->nCharges = skill_charges[j];
						pSkills[j]->nOwnerGUID = owner_guids[j];
						pSkills[j]->pNextSkill = j + 1 < skill_count ? pSkills[j + 1] : nullptr;
					}

					pSkillList.pFirstSkill = pSkills[0];
					pSkillList.pLeftSkill = pSkills[0];
					pSkillList.pRightSkill = pSkills[0];
					pSkillList.pUsedSkill = used_skill_index < skill_count ? pSkills[used_skill_index] : nullptr;
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit, nOwnerGUID, nSkillId, nSkillLevel, nCharges, bFreeMemory);
				original(&original_pUnit, nOwnerGUID, nSkillId, nSkillLevel, nCharges, bFreeMemory);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				for (auto pSkill = moo_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				for (auto pSkill = original_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB08C0 (#10957)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetOwnerGUIDFromSkill, dll_base + 0x000708C0);
		
		SUBCASE("")
		{
			// Input data
			const auto owner_id = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [owner_id](
				D2SkillStrc& pSkill
			) {
				pSkill.nOwnerGUID = owner_id;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB08F0 (#10955)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkillInfo, dll_base + 0x000708F0);
		
		SUBCASE("valid owner GUID")
		{
			// Input data
			const auto owner_id = random_unsigned_integer(0, 100);
			const auto skill_id = random_unsigned_integer(0, skills_record_count);
			const auto skill_level = random_unsigned_integer();
			const auto charges = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2UnitGUID moo_pOwnerGUID{};
			int moo_pSkillId{};
			int moo_pSkillLevel{};
			int moo_pCharges{};
			D2SkillStrc original_pSkill{};
			D2UnitGUID original_pOwnerGUID{};
			int original_pSkillId{};
			int original_pSkillLevel{};
			int original_pCharges{};

			const auto setup_data = [this, owner_id, skill_id, skill_level, charges](
				D2SkillStrc& pSkill,
				D2UnitGUID& pOwnerGUID,
				int& pSkillId,
				int& pSkillLevel,
				int& pCharges
			) {
				pSkill.nOwnerGUID = owner_id;
				pSkill.pSkillsTxt = &skills_txt[skill_id];
				pSkill.nSkillLevel = skill_level;
				pSkill.nCharges = charges;
			};

			setup_data(moo_pSkill, moo_pOwnerGUID, moo_pSkillId, moo_pSkillLevel, moo_pCharges);
			setup_data(original_pSkill, original_pOwnerGUID, original_pSkillId, original_pSkillLevel, original_pCharges);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill, &moo_pOwnerGUID, &moo_pSkillId, &moo_pSkillLevel, &moo_pCharges);
			const auto original_result = original(&original_pSkill, &original_pOwnerGUID, &original_pSkillId, &original_pSkillLevel, &original_pCharges);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			MOO_CHECK_EQ(moo_pOwnerGUID, original_pOwnerGUID, "Comparing pOwnerGUID");
			MOO_CHECK_EQ(moo_pSkillId, original_pSkillId, "Comparing pSkillId");
			MOO_CHECK_EQ(moo_pSkillLevel, original_pSkillLevel, "Comparing pSkillLevel");
			MOO_CHECK_EQ(moo_pCharges, original_pCharges, "Comparing pCharges");
		}

		SUBCASE("invalid owner GUID")
		{
			// Input data
			const auto owner_id = D2UnitInvalidGUID;
			const auto skill_id = random_unsigned_integer(0, skills_record_count);
			const auto skill_level = random_unsigned_integer();
			const auto charges = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2UnitGUID moo_pOwnerGUID{};
			int moo_pSkillId{};
			int moo_pSkillLevel{};
			int moo_pCharges{};
			D2SkillStrc original_pSkill{};
			D2UnitGUID original_pOwnerGUID{};
			int original_pSkillId{};
			int original_pSkillLevel{};
			int original_pCharges{};

			const auto setup_data = [this, owner_id, skill_id, skill_level, charges](
				D2SkillStrc& pSkill,
				D2UnitGUID& pOwnerGUID,
				int& pSkillId,
				int& pSkillLevel,
				int& pCharges
			) {
				pSkill.nOwnerGUID = owner_id;
				pSkill.pSkillsTxt = &skills_txt[skill_id];
				pSkill.nSkillLevel = skill_level;
				pSkill.nCharges = charges;
			};

			setup_data(moo_pSkill, moo_pOwnerGUID, moo_pSkillId, moo_pSkillLevel, moo_pCharges);
			setup_data(original_pSkill, original_pOwnerGUID, original_pSkillId, original_pSkillLevel, original_pCharges);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill, &moo_pOwnerGUID, &moo_pSkillId, &moo_pSkillLevel, &moo_pCharges);
			const auto original_result = original(&original_pSkill, &original_pOwnerGUID, &original_pSkillId, &original_pSkillLevel, &original_pCharges);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			MOO_CHECK_EQ(moo_pOwnerGUID, original_pOwnerGUID, "Comparing pOwnerGUID");
			MOO_CHECK_EQ(moo_pSkillId, original_pSkillId, "Comparing pSkillId");
			MOO_CHECK_EQ(moo_pSkillLevel, original_pSkillLevel, "Comparing pSkillLevel");
			MOO_CHECK_EQ(moo_pCharges, original_pCharges, "Comparing pCharges");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB0960 (#10956)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetCharges, dll_base + 0x00070960);
		
		SUBCASE("valid owner GUID")
		{
			// Input data
			const auto owner_id = random_unsigned_integer(0, 100);

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nCharges = random_unsigned_integer();

			const auto setup_data = [owner_id](
				D2SkillStrc& pSkill
			) {
				pSkill.nOwnerGUID = owner_id;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill, nCharges);
			const auto original_result = original(&original_pSkill, nCharges);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}

		SUBCASE("invalid owner GUID")
		{
			// Input data
			const auto owner_id = D2UnitInvalidGUID;

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nCharges = random_unsigned_integer();

			const auto setup_data = [owner_id](
				D2SkillStrc& pSkill
			) {
				pSkill.nOwnerGUID = owner_id;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill, nCharges);
			const auto original_result = original(&original_pSkill, nCharges);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB09A0 (#10961)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetLeftActiveSkill, dll_base + 0x000709A0);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 6;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				uint32_t skill_ids[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 3);
				}

				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;
				D2UnitGUID nOwnerGUID = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 3);

				const auto setup_data = [this, &skill_ids, &owner_guids](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit, nSkillId, nOwnerGUID);
				original(&original_pUnit, nSkillId, nOwnerGUID);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				CHECK_EQ(moo_pSkillList.pLeftSkill ? moo_pSkillList.pLeftSkill - moo_pSkills : -1, original_pSkillList.pLeftSkill ? original_pSkillList.pLeftSkill - original_pSkills : -1);
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB0A30 (#10962)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetRightActiveSkill, dll_base + 0x00070A30);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 6;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				uint32_t skill_ids[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 3);
				}

				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;
				D2UnitGUID nOwnerGUID = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 3);

				const auto setup_data = [this, &skill_ids, &owner_guids](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit, nSkillId, nOwnerGUID);
				original(&original_pUnit, nSkillId, nOwnerGUID);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				CHECK_EQ(moo_pSkillList.pRightSkill ? moo_pSkillList.pRightSkill - moo_pSkills : -1, original_pSkillList.pRightSkill ? original_pSkillList.pRightSkill - original_pSkills : -1);
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB0AC0 (#10963)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkillIdFromSkill, dll_base + 0x00070AC0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				D2SkillStrc moo_pSkill{};
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, i](
					D2SkillStrc& pSkill
				) {
					pSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pSkill);
				setup_data(original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pSkill, __FILE__, __LINE__);
				const auto original_result = original(&original_pSkill, __FILE__, __LINE__);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FDB0AF0 (#10965)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSeqNumFromSkill, dll_base + 0x00070AF0);
		
		SUBCASE("Player")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pUnit, moo_pSkill);
				setup_data(original_pUnit, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
				const auto original_result = original(&original_pUnit, &original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}

		SUBCASE("Monster")
		{
			for (auto j = 0; j < monstats_record_count; ++j)
			{
				for (auto i = 0; i < skills_record_count; ++i)
				{
					// Input data
					D2UnitStrc moo_pUnit{};
					D2SkillStrc moo_pSkill{};
					D2UnitStrc original_pUnit{};
					D2SkillStrc original_pSkill{};

					const auto setup_data = [this, i, j](
						D2UnitStrc& pUnit,
						D2SkillStrc& pSkill
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = j;
						pSkill.pSkillsTxt = &skills_txt[i];
					};

					setup_data(moo_pUnit, moo_pSkill);
					setup_data(original_pUnit, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
					const auto original_result = original(&original_pUnit, &original_pSkill);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB0B70 (#10964)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetUseState, dll_base + 0x00070B70);

		SUBCASE("")
		{
			// Input data
			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			add_stat(STAT_HITPOINTS, 0, random_unsigned_integer(0, 500) << 8);
			add_stat(STAT_MANA, 0, random_unsigned_integer(0, 500) << 8);
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDCLASSSKILLS, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_NONCLASSSKILL, i, random_unsigned_integer(0, 5));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				const auto shape_shifted = random_unsigned_integer(0, 1);
				const auto skill_level = random_unsigned_integer(0, 5);
				const auto owner_guid = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				const auto charges = random_unsigned_integer(0, 3);
				const auto quantity = random_unsigned_integer(0, 3);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				std::vector<uint32_t> moo_pStatFlags;
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				std::vector<uint32_t> original_pStatFlags;
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, &stat_array, &state_flags, i, class_id, shape_shifted, skill_level, owner_guid, charges, quantity](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					std::vector<uint32_t>& pStatFlags,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.dwFlagEx = shape_shifted ? UNITFLAGEX_ISSHAPESHIFTED : 0;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = INVGRID_BODYLOC + 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nSkillLevel = skill_level;
					pSkill.nOwnerGUID = owner_guid;
					pSkill.nCharges = charges;
					pSkill.nQuantity = quantity;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pSkill);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
				const auto original_result = original(&original_pUnit, &original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB0F50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_SKILLMANA_CheckStat_6FDB0F50, dll_base + 0x00070F50);

		SUBCASE("")
		{
			// Input data
			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			add_stat(STAT_HITPOINTS, 0, random_unsigned_integer(0, 100) << 8);
			add_stat(STAT_MANA, 0, random_unsigned_integer(0, 100) << 8);
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto shape_shifted = random_unsigned_integer(0, 1);
				const auto skill_level = random_unsigned_integer(0, 20);
				const auto owner_guid = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				const auto charges = random_unsigned_integer(0, 3);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				std::vector<uint32_t> moo_pStatFlags;
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				std::vector<uint32_t> original_pStatFlags;
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, &stat_array, &state_flags, i, shape_shifted, skill_level, owner_guid, charges](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					std::vector<uint32_t>& pStatFlags,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwFlagEx = shape_shifted ? UNITFLAGEX_ISSHAPESHIFTED : 0;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nSkillLevel = skill_level;
					pSkill.nOwnerGUID = owner_guid;
					pSkill.nCharges = charges;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkill);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
				const auto original_result = original(&original_pUnit, &original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1050")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB1050, dll_base + 0x00071050);

		SUBCASE("")
		{
			// Input data
			bool has_items[NUM_BODYLOC]{};
			uint32_t item_class_ids[NUM_BODYLOC]{};

			for (auto i = 0; i < NUM_BODYLOC; ++i)
			{
				has_items[i] = random_unsigned_integer(0, 3) != 0;
				item_class_ids[i] = random_unsigned_integer(0, 500);
			}

			for (auto i = -1; i <= NUM_BODYLOC; ++i)
			{
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pItems[NUM_BODYLOC]{};
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pItems[NUM_BODYLOC]{};
				int nBodyLoc = i;

				const auto setup_data = [&has_items, &item_class_ids](
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc (&pItems)[NUM_BODYLOC]
				) {
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = INVGRID_BODYLOC + 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;

					for (auto j = 0; j < NUM_BODYLOC; ++j)
					{
						pItems[j].dwUnitType = UNIT_ITEM;
						pItems[j].dwClassId = item_class_ids[j];
						pItems[j].dwUnitId = j;
						pBodyLocItems[j] = has_items[j] ? &pItems[j] : nullptr;
					}
				};

				setup_data(moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pItems);
				setup_data(original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pItems);

				// Call both implementations
				const auto moo_result = sut(&moo_pInventory, nBodyLoc);
				const auto original_result = original(&original_pInventory, nBodyLoc);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(moo_result ? moo_result - moo_pItems : -1, original_result ? original_result - original_pItems : -1);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pInventory, original_pInventory, "Comparing pInventory");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>, "D2Common.0x6FDB1070")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB1070, dll_base + 0x00071070);

		SUBCASE("with inventory")
		{
			// Input data
			constexpr auto item_count = 3;
			constexpr D2UnitGUID first_item_guid = 10;
			const D2UnitGUID owner_guids[] = { D2UnitInvalidGUID, first_item_guid, first_item_guid + 1, first_item_guid + 2, first_item_guid + item_count };

			for (auto i = 0; i < skills_record_count; ++i)
			{
				const auto skill_level = random_unsigned_integer(0, 63);
				const auto owner_guid = owner_guids[random_unsigned_integer(0, std::size(owner_guids) - 1)];

				std::vector<D2StatStrc> stat_arrays[item_count];

				for (auto j = 0; j < item_count; ++j)
				{
					// Charges for the current skill at random levels
					std::vector<uint32_t> levels = { skill_level, random_unsigned_integer(0, 63), random_unsigned_integer(0, 63) };
					std::sort(levels.begin(), levels.end());
					levels.erase(std::unique(levels.begin(), levels.end()), levels.end());

					for (const auto level : levels)
					{
						D2StatStrc stat{};
						stat.nStat = STAT_ITEM_CHARGED_SKILL;
						stat.nLayer = static_cast<uint16_t>((i << 6) + level);
						stat.nValue = random_unsigned_integer(0, 1);
						stat_arrays[j].push_back(stat);
					}
				}

				D2UnitStrc moo_pUnit{};
				D2InventoryStrc moo_pInventory{};
				D2UnitStrc moo_pItems[item_count]{};
				D2ItemDataStrc moo_pItemData[item_count]{};
				D2StatListExStrc moo_pItemStatListEx[item_count]{};
				std::vector<D2StatStrc> moo_pItemStats[item_count];
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2InventoryStrc original_pInventory{};
				D2UnitStrc original_pItems[item_count]{};
				D2ItemDataStrc original_pItemData[item_count]{};
				D2StatListExStrc original_pItemStatListEx[item_count]{};
				std::vector<D2StatStrc> original_pItemStats[item_count];
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, &stat_arrays, i, skill_level, owner_guid, first_item_guid](
					D2UnitStrc& pUnit,
					D2InventoryStrc& pInventory,
					D2UnitStrc (&pItems)[item_count],
					D2ItemDataStrc (&pItemData)[item_count],
					D2StatListExStrc (&pItemStatListEx)[item_count],
					std::vector<D2StatStrc> (&pItemStats)[item_count],
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pInventory = &pInventory;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.pFirstItem = &pItems[0];
					pInventory.pLastItem = &pItems[item_count - 1];

					for (auto j = 0; j < item_count; ++j)
					{
						pItems[j].dwUnitType = UNIT_ITEM;
						pItems[j].dwUnitId = first_item_guid + j;
						pItems[j].pItemData = &pItemData[j];
						pItemData[j].pExtraData.pParentInv = &pInventory;
						pItemData[j].pExtraData.pPreviousItem = j > 0 ? &pItems[j - 1] : nullptr;
						pItemData[j].pExtraData.pNextItem = j + 1 < item_count ? &pItems[j + 1] : nullptr;
						pItems[j].pStatListEx = &pItemStatListEx[j];
						pItemStatListEx[j].dwFlags |= STATLIST_EXTENDED;
						pItemStats[j] = stat_arrays[j];
						pItemStatListEx[j].FullStats.pStat = pItemStats[j].data();
						pItemStatListEx[j].FullStats.nStatCount = static_cast<uint16_t>(pItemStats[j].size());
					}

					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nSkillLevel = skill_level;
					pSkill.nOwnerGUID = owner_guid;
				};

				setup_data(moo_pUnit, moo_pInventory, moo_pItems, moo_pItemData, moo_pItemStatListEx, moo_pItemStats, moo_pSkill);
				setup_data(original_pUnit, original_pInventory, original_pItems, original_pItemData, original_pItemStatListEx, original_pItemStats, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
				const auto original_result = original(&original_pUnit, &original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}

		SUBCASE("without inventory")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				D2UnitStrc moo_pUnit{};
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, i](
					D2UnitStrc& pUnit,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nOwnerGUID = D2UnitInvalidGUID;
				};

				setup_data(moo_pUnit, moo_pSkill);
				setup_data(original_pUnit, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
				const auto original_result = original(&original_pUnit, &original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemTypesTxtFixture<ItemsTxtFixture<SkillsTxtFixture<NoopFixture>>>>, "D2Common.0x6FDB1130")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FDB1130, dll_base + 0x00071130);

		const int nType = GENERATE(0, 1);

		SUBCASE("with item")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j < 20; ++j)
				{
					// Input data
					uint32_t item_class_ids[2]{};
					uint32_t item_flags[2]{};
					std::vector<D2StatStrc> stat_arrays[2];

					for (auto k = 0; k < 2; ++k)
					{
						item_class_ids[k] = random_unsigned_integer(0, items_record_count - 1);
						item_flags[k] = (random_unsigned_integer(0, 7) ? 0 : IFLAG_NOEQUIP) | (random_unsigned_integer(0, 7) ? 0 : IFLAG_BROKEN);

						D2StatStrc quantity{};
						quantity.nStat = STAT_QUANTITY;
						quantity.nValue = random_unsigned_integer(0, 3);
						stat_arrays[k].push_back(quantity);

						D2StatStrc magic_arrow{};
						magic_arrow.nStat = STAT_ITEM_MAGICARROW;
						magic_arrow.nValue = random_unsigned_integer(0, 3) ? 0 : 1;
						stat_arrays[k].push_back(magic_arrow);
					}

					const auto has_other_item = random_unsigned_integer(0, 3) != 0;

					D2UnitStrc moo_pItem{};
					D2ItemDataStrc moo_pItemData{};
					D2StatListExStrc moo_pItemStatListEx{};
					std::vector<D2StatStrc> moo_pItemStats;
					D2UnitStrc moo_pUnit{};
					D2ItemDataStrc moo_pUnitItemData{};
					D2StatListExStrc moo_pUnitStatListEx{};
					std::vector<D2StatStrc> moo_pUnitStats;
					D2SkillsTxt moo_pSkillsTxtRecord{};
					D2UnitStrc original_pItem{};
					D2ItemDataStrc original_pItemData{};
					D2StatListExStrc original_pItemStatListEx{};
					std::vector<D2StatStrc> original_pItemStats;
					D2UnitStrc original_pUnit{};
					D2ItemDataStrc original_pUnitItemData{};
					D2StatListExStrc original_pUnitStatListEx{};
					std::vector<D2StatStrc> original_pUnitStats;
					D2SkillsTxt original_pSkillsTxtRecord{};

					const auto setup_data = [this, &item_class_ids, &item_flags, &stat_arrays, i](
						D2UnitStrc& pItem,
						D2ItemDataStrc& pItemData,
						D2StatListExStrc& pItemStatListEx,
						std::vector<D2StatStrc>& pItemStats,
						D2UnitStrc& pUnit,
						D2ItemDataStrc& pUnitItemData,
						D2StatListExStrc& pUnitStatListEx,
						std::vector<D2StatStrc>& pUnitStats,
						D2SkillsTxt& pSkillsTxtRecord
					) {
						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = item_class_ids[0];
						pItem.pItemData = &pItemData;
						pItemData.dwItemFlags = item_flags[0];
						pItem.pStatListEx = &pItemStatListEx;
						pItemStatListEx.dwFlags |= STATLIST_EXTENDED;
						pItemStats = stat_arrays[0];
						pItemStatListEx.FullStats.pStat = pItemStats.data();
						pItemStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pItemStats.size());

						pUnit.dwUnitType = UNIT_ITEM;
						pUnit.dwClassId = item_class_ids[1];
						pUnit.pItemData = &pUnitItemData;
						pUnitItemData.dwItemFlags = item_flags[1];
						pUnit.pStatListEx = &pUnitStatListEx;
						pUnitStatListEx.dwFlags |= STATLIST_EXTENDED;
						pUnitStats = stat_arrays[1];
						pUnitStatListEx.FullStats.pStat = pUnitStats.data();
						pUnitStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pUnitStats.size());

						pSkillsTxtRecord = skills_txt[i];
					};

					setup_data(moo_pItem, moo_pItemData, moo_pItemStatListEx, moo_pItemStats, moo_pUnit, moo_pUnitItemData, moo_pUnitStatListEx, moo_pUnitStats, moo_pSkillsTxtRecord);
					setup_data(original_pItem, original_pItemData, original_pItemStatListEx, original_pItemStats, original_pUnit, original_pUnitItemData, original_pUnitStatListEx, original_pUnitStats, original_pSkillsTxtRecord);

					// Call both implementations
					const auto moo_result = sut(&moo_pItem, has_other_item ? &moo_pUnit : nullptr, &moo_pSkillsTxtRecord, nType);
					const auto original_result = original(&original_pItem, has_other_item ? &original_pUnit : nullptr, &original_pSkillsTxtRecord, nType);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkillsTxtRecord, original_pSkillsTxtRecord, "Comparing pSkillsTxtRecord");
				}
			}
		}

		SUBCASE("without item")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				const auto item_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto has_other_item = random_unsigned_integer(0, 1) != 0;

				D2UnitStrc moo_pUnit{};
				D2SkillsTxt moo_pSkillsTxtRecord{};
				D2UnitStrc original_pUnit{};
				D2SkillsTxt original_pSkillsTxtRecord{};

				const auto setup_data = [this, i, item_class_id](
					D2UnitStrc& pUnit,
					D2SkillsTxt& pSkillsTxtRecord
				) {
					pUnit.dwUnitType = UNIT_ITEM;
					pUnit.dwClassId = item_class_id;
					pSkillsTxtRecord = skills_txt[i];
				};

				setup_data(moo_pUnit, moo_pSkillsTxtRecord);
				setup_data(original_pUnit, original_pSkillsTxtRecord);

				// Call both implementations
				const auto moo_result = sut(nullptr, has_other_item ? &moo_pUnit : nullptr, &moo_pSkillsTxtRecord, nType);
				const auto original_result = original(nullptr, has_other_item ? &original_pUnit : nullptr, &original_pSkillsTxtRecord, nType);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillsTxtRecord, original_pSkillsTxtRecord, "Comparing pSkillsTxtRecord");
			}
		}
	}
	
	TEST_CASE_FIXTURE(StatesTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FDB1380")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_SKILLS_CheckShapeRestriction_6FDB1380, dll_base + 0x00071380);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j < 10; ++j)
				{
					for (auto& flag : state_flags)
					{
						flag = random_unsigned_integer(0, 7) ? 0 : random_unsigned_integer();
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<uint32_t> moo_pStatFlags;
					D2SkillStrc moo_pSkill{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<uint32_t> original_pStatFlags;
					D2SkillStrc original_pSkill{};

					const auto setup_data = [this, &state_flags, i](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<uint32_t>& pStatFlags,
						D2SkillStrc& pSkill
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStatFlags = state_flags;
						pStatListEx.StatFlags = pStatFlags.data();
						pSkill.pSkillsTxt = &skills_txt[i];
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags, moo_pSkill);
					setup_data(original_pUnit, original_pStatListEx, original_pStatFlags, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
					const auto original_result = original(&original_pUnit, &original_pSkill);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillsTxtFixture<NoopFixture>>>, "D2Common.0x6FDB1400")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_SKILLMANA_CheckStartStat_6FDB1400, dll_base + 0x00071400);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				std::vector<D2StatStrc> stat_array(1);
				stat_array[0].nStat = STAT_MANA;
				stat_array[0].nValue = random_unsigned_integer(0, 2 * std::max<int>(skills_txt[i].wStartMana, 1)) << 8;

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				std::vector<uint32_t> moo_pStatFlags;
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				std::vector<uint32_t> original_pStatFlags;
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, &stat_array, &state_flags, unit_type, i](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					std::vector<uint32_t>& pStatFlags,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkill);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
				const auto original_result = original(&original_pUnit, &original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB1450")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CheckSkillDelay, dll_base + 0x00071450);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto skill_level = random_unsigned_integer(0, 20);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<uint32_t> moo_pStatFlags;
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<uint32_t> original_pStatFlags;
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, &state_flags, unit_type, i, skill_level](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<uint32_t>& pStatFlags,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nSkillLevel = skill_level;
					pSkill.nOwnerGUID = D2UnitInvalidGUID;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags, moo_pSkill);
				setup_data(original_pUnit, original_pStatListEx, original_pStatFlags, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
				const auto original_result = original(&original_pUnit, &original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB1540 (#10966)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkillsTxtRecordFromSkill, dll_base + 0x00071540);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				D2SkillStrc moo_pSkill{};
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, i](
					D2SkillStrc& pSkill
				) {
					pSkill.pSkillsTxt = &skills_txt[i];
				};

				setup_data(moo_pSkill);
				setup_data(original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pSkill);
				const auto original_result = original(&original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(StatesTxtFixture<NoopFixture>, "D2Common.0x6FDB1550 (#10967)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetShrineSkillLevelBonus, dll_base + 0x00071550);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_OBJECT, UNIT_MISSILE, UNIT_ITEM);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < 100; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<uint32_t> moo_pStatFlags;
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<uint32_t> original_pStatFlags;

				const auto setup_data = [&state_flags, unit_type](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<uint32_t>& pStatFlags
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags);
				setup_data(original_pUnit, original_pStatListEx, original_pStatFlags);

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
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB1580")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetBonusSkillLevel, dll_base + 0x00071580);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);

		SUBCASE("")
		{
			// Input data
			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDCLASSSKILLS, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_NONCLASSSKILL, i, random_unsigned_integer(0, 5));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < 32; ++i)
			{
				add_stat(STAT_ITEM_ELEMSKILL, i, random_unsigned_integer(0, 3));
			}
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < 8 * NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDSKILL_TAB, i, random_unsigned_integer(0, 3));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				const auto skill_level = random_unsigned_integer(0, 3);
				const auto level_bonus = random_unsigned_integer(0, 3);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				std::vector<uint32_t> moo_pStatFlags;
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				std::vector<uint32_t> original_pStatFlags;
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, &stat_array, &state_flags, unit_type, class_id, i, skill_level, level_bonus](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					std::vector<uint32_t>& pStatFlags,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.dwClassId = class_id;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nSkillLevel = skill_level;
					pSkill.nLevelBonus = level_bonus;
					pSkill.nOwnerGUID = D2UnitInvalidGUID;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkill);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
				const auto original_result = original(&original_pUnit, &original_pSkill);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB1700 (#10968)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkillLevel, dll_base + 0x00071700);

		const BOOL bBonus = GENERATE(FALSE, TRUE);

		SUBCASE("")
		{
			// Input data
			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDCLASSSKILLS, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_NONCLASSSKILL, i, random_unsigned_integer(0, 5));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < 32; ++i)
			{
				add_stat(STAT_ITEM_ELEMSKILL, i, random_unsigned_integer(0, 3));
			}
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < 8 * NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDSKILL_TAB, i, random_unsigned_integer(0, 3));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				const int skill_level = static_cast<int>(random_unsigned_integer(0, 120)) - 10;
				const auto owner_guid = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				std::vector<uint32_t> moo_pStatFlags;
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				std::vector<uint32_t> original_pStatFlags;
				D2SkillStrc original_pSkill{};

				const auto setup_data = [this, &stat_array, &state_flags, class_id, i, skill_level, owner_guid](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					std::vector<uint32_t>& pStatFlags,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nSkillLevel = skill_level;
					pSkill.nOwnerGUID = owner_guid;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkill);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkill);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pSkill, bBonus);
				const auto original_result = original(&original_pUnit, &original_pSkill, bBonus);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB1750 (#11029)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetBonusSkillLevelFromSkillId, dll_base + 0x00071750);

		SUBCASE("")
		{
			// Input data
			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDCLASSSKILLS, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_NONCLASSSKILL, i, random_unsigned_integer(0, 5));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < 32; ++i)
			{
				add_stat(STAT_ITEM_ELEMSKILL, i, random_unsigned_integer(0, 3));
			}
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < 8 * NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDSKILL_TAB, i, random_unsigned_integer(0, 3));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);
			constexpr auto skill_count = 4;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(0, 20);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				std::vector<uint32_t> moo_pStatFlags;
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				std::vector<uint32_t> original_pStatFlags;
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;

				const auto setup_data = [this, &stat_array, &state_flags, &skill_ids, &skill_levels, &owner_guids, class_id](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					std::vector<uint32_t>& pStatFlags,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nSkillLevel = skill_levels[j];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSkillId);
				const auto original_result = original(&original_pUnit, nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB17A0 (#11030)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11030, dll_base + 0x000717A0);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 3;
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 3) ? random_unsigned_integer(0, skills_record_count - 1) : i;
					skill_levels[j] = random_unsigned_integer(0, 20);
					owner_guids[j] = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				// Skills get added to the skill list, so they have to be allocated from the memory pool to be able to free them afterwards
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc* moo_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* moo_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc* moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc* original_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* original_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc* original_pSkills[skill_count]{};
				int nSkillId = i;
				int a3 = static_cast<int>(random_unsigned_integer(0, 4)) - 1;

				for (auto j = 0; j < skill_count; ++j)
				{
					moo_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
					original_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
				}

				const auto setup_data = [this, &state_flags, &skill_ids, &skill_levels, &owner_guids, flag_count, class_id](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					uint32_t* pStatFlags,
					D2SkillListStrc& pSkillList,
					D2SkillStrc* (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.dwUnitId = 1;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags = STATLIST_EXTENDED;
					pStatListEx.dwOwnerType = UNIT_PLAYER;
					pStatListEx.dwOwnerId = 1;
					pStatListEx.pOwner = &pUnit;
					std::memcpy(pStatFlags, state_flags.data(), 2 * flag_count * sizeof(uint32_t));
					pStatListEx.StatFlags = pStatFlags;
					pUnit.pSkills = &pSkillList;

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j]->pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j]->nSkillLevel = skill_levels[j];
						pSkills[j]->nOwnerGUID = owner_guids[j];
						pSkills[j]->pNextSkill = j + 1 < skill_count ? pSkills[j + 1] : nullptr;
					}

					pSkillList.pFirstSkill = pSkills[0];
				};

				setup_data(moo_pUnit, *moo_pStatListEx, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, *original_pStatListEx, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit, nSkillId, a3);
				original(&original_pUnit, nSkillId, a3);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				for (auto pSkill = moo_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				for (auto pSkill = original_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				STATLIST_FreeStatListEx(&moo_pUnit);
				STATLIST_FreeStatListEx(&original_pUnit);
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB1820 (#11031)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11031, dll_base + 0x00071820);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 3;
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				uint32_t skill_level_bonuses[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 3) ? random_unsigned_integer(0, skills_record_count - 1) : i;
					skill_levels[j] = random_unsigned_integer(0, 20);
					skill_level_bonuses[j] = random_unsigned_integer(0, 3);
					owner_guids[j] = random_unsigned_integer(0, 3) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				// Skills get added to the skill list, so they have to be allocated from the memory pool to be able to free them afterwards
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc* moo_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* moo_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc* moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc* original_pStatListEx = D2_CALLOC_STRC_POOL(nullptr, D2StatListExStrc);
				uint32_t* original_pStatFlags = static_cast<uint32_t*>(D2_CALLOC_POOL(nullptr, 2 * flag_count * sizeof(uint32_t)));
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc* original_pSkills[skill_count]{};
				int nSkillId = i;
				int a3 = static_cast<int>(random_unsigned_integer(0, 8)) - 4;

				for (auto j = 0; j < skill_count; ++j)
				{
					moo_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
					original_pSkills[j] = D2_CALLOC_STRC_POOL(nullptr, D2SkillStrc);
				}

				const auto setup_data = [this, &state_flags, &skill_ids, &skill_levels, &skill_level_bonuses, &owner_guids, flag_count, class_id](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					uint32_t* pStatFlags,
					D2SkillListStrc& pSkillList,
					D2SkillStrc* (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.dwUnitId = 1;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags = STATLIST_EXTENDED;
					pStatListEx.dwOwnerType = UNIT_PLAYER;
					pStatListEx.dwOwnerId = 1;
					pStatListEx.pOwner = &pUnit;
					std::memcpy(pStatFlags, state_flags.data(), 2 * flag_count * sizeof(uint32_t));
					pStatListEx.StatFlags = pStatFlags;
					pUnit.pSkills = &pSkillList;

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j]->pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j]->nSkillLevel = skill_levels[j];
						pSkills[j]->nLevelBonus = skill_level_bonuses[j];
						pSkills[j]->nOwnerGUID = owner_guids[j];
						pSkills[j]->pNextSkill = j + 1 < skill_count ? pSkills[j + 1] : nullptr;
					}

					pSkillList.pFirstSkill = pSkills[0];
				};

				setup_data(moo_pUnit, *moo_pStatListEx, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, *original_pStatListEx, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				sut(&moo_pUnit, nSkillId, a3);
				original(&original_pUnit, nSkillId, a3);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");

				// Clean up
				for (auto pSkill = moo_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				for (auto pSkill = original_pSkillList.pFirstSkill; pSkill;)
				{
					const auto pNextSkill = pSkill->pNextSkill;
					D2_FREE_POOL(nullptr, pSkill);
					pSkill = pNextSkill;
				}

				STATLIST_FreeStatListEx(&moo_pUnit);
				STATLIST_FreeStatListEx(&original_pUnit);
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB18B0 (#10974)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetSkillMode, dll_base + 0x000718B0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				// Input data
				D2SkillStrc moo_pSkill{};
				D2SkillStrc original_pSkill{};
				int nSkillMode = i;

				// Call both implementations
				sut(&moo_pSkill, nSkillMode);
				original(&original_pSkill, nSkillMode);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB18D0 (#10975)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkillMode, dll_base + 0x000718D0);
		
		SUBCASE("")
		{
			// Input data
			const auto skill_mode = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [skill_mode](
				D2SkillStrc& pSkill
			) {
				pSkill.dwSkillMode = skill_mode;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB18F0 (#10969)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10969, dll_base + 0x000718F0);
		
		SUBCASE("")
		{
			// Input data
			const auto value = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [value](
				D2SkillStrc& pSkill
			) {
				pSkill.unk0x10[0] = value;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1920 (#10970)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10970, dll_base + 0x00071920);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nUnknown = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSkill, nUnknown);
			original(&original_pSkill, nUnknown);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1950 (#10971)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10971, dll_base + 0x00071950);
		
		SUBCASE("")
		{
			// Input data
			const auto value = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [value](
				D2SkillStrc& pSkill
			) {
				pSkill.unk0x10[1] = value;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1980 (#10972)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10972, dll_base + 0x00071980);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nUnknown = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSkill, nUnknown);
			original(&original_pSkill, nUnknown);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB19B0 (#10973)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_10973, dll_base + 0x000719B0);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [](
				D2SkillStrc& pSkill
			) {
				pSkill.unk0x10[0] = random_unsigned_integer();
				pSkill.unk0x10[1] = random_unsigned_integer();

			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			sut(&moo_pSkill);
			original(&original_pSkill);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB19F0 (#10976)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetParam1, dll_base + 0x000719F0);
		
		SUBCASE("")
		{
			// Input data
			const auto par1 = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [par1](
				D2SkillStrc& pSkill
			) {
				pSkill.nPar1 = par1;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1A20 (#10977)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetParam2, dll_base + 0x00071A20);
		
		SUBCASE("")
		{
			// Input data
			const auto par2 = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [par2](
				D2SkillStrc& pSkill
			) {
				pSkill.nPar2 = par2;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1A50 (#10978)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetParam3, dll_base + 0x00071A50);
		
		SUBCASE("")
		{
			// Input data
			const auto par3 = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [par3](
				D2SkillStrc& pSkill
			) {
				pSkill.nPar3 = par3;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1A80 (#10979)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetParam4, dll_base + 0x00071A80);
		
		SUBCASE("")
		{
			// Input data
			const auto par4 = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [par4](
				D2SkillStrc& pSkill
			) {
				pSkill.nPar4 = par4;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1AB0 (#10980)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetParam1, dll_base + 0x00071AB0);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nPar1 = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSkill, nPar1);
			original(&original_pSkill, nPar1);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1AE0 (#10981)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetParam2, dll_base + 0x00071AE0);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nPar2 = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSkill, nPar2);
			original(&original_pSkill, nPar2);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1B10 (#10982)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetParam3, dll_base + 0x00071B10);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nPar3 = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSkill, nPar3);
			original(&original_pSkill, nPar3);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1B40 (#10983)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetParam4, dll_base + 0x00071B40);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nPar4 = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSkill, nPar4);
			original(&original_pSkill, nPar4);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1B70 (#10984)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetFlags, dll_base + 0x00071B70);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nFlags = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSkill, nFlags);
			original(&original_pSkill, nFlags);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB1BA0 (#10985)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetFlags, dll_base + 0x00071BA0);
		
		SUBCASE("")
		{
			// Input data
			const auto flags = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [flags](
				D2SkillStrc& pSkill
			) {
				pSkill.dwFlags = flags;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB1BC0 (#10986)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetRequiredLevel, dll_base + 0x00071BC0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				int nSkillId = i;

				// Call both implementations
				const auto moo_result = sut(nSkillId);
				const auto original_result = original(nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB1C00 (#10987)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetRequiredLevelBasedOnCurrent, dll_base + 0x00071C00);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 4;

			for (auto i = -1; i <= skills_record_count; ++i)
			{
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) && i >= 0 && i < skills_record_count ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(0, 20);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				const auto has_skills = random_unsigned_integer(0, 7) != 0;

				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;

				const auto setup_data = [this, &skill_ids, &skill_levels, &owner_guids, has_skills](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pSkills = has_skills ? &pSkillList : nullptr;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nSkillLevel = skill_levels[j];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
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
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FDB1C80 (#10988)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CheckRequiredSkills, dll_base + 0x00071C80);

		SUBCASE("")
		{
			// Input data
			constexpr auto max_skill_count = 5;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto k = 0; k < 10; ++k)
				{
					std::vector<D2StatStrc> stat_array(1);
					stat_array[0].nStat = STAT_LEVEL;
					stat_array[0].nValue = random_unsigned_integer(1, 99);

					// The first skill is always Attack, followed by the required skills and the skill itself (each with a random chance)
					std::vector<uint32_t> skill_ids = { SKILL_ATTACK };
					for (const auto required_skill : skills_txt[i].nReqSkill)
					{
						if (required_skill >= 0 && required_skill < skills_record_count && random_unsigned_integer(0, 3))
						{
							skill_ids.push_back(required_skill);
						}
					}
					if (random_unsigned_integer(0, 1))
					{
						skill_ids.push_back(i);
					}

					const auto skill_count = static_cast<int>(skill_ids.size());
					uint32_t skill_levels[max_skill_count]{};

					for (auto j = 0; j < skill_count; ++j)
					{
						skill_levels[j] = random_unsigned_integer(0, 2);
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pSkills[max_skill_count]{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pSkills[max_skill_count]{};
					int nSkillId = i;

					const auto setup_data = [this, &stat_array, &skill_ids, &skill_levels, skill_count](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						D2SkillListStrc& pSkillList,
						D2SkillStrc (&pSkills)[max_skill_count]
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pUnit.pSkills = &pSkillList;
						pSkillList.pFirstSkill = &pSkills[0];

						for (auto j = 0; j < skill_count; ++j)
						{
							pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
							pSkills[j].nSkillLevel = skill_levels[j];
							pSkills[j].nOwnerGUID = D2UnitInvalidGUID;
							pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
						}
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pSkillList, moo_pSkills);
					setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pSkillList, original_pSkills);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nSkillId);
					const auto original_result = original(&original_pUnit, nSkillId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB1F80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetSkill, dll_base + 0x00071F80);

		SUBCASE("")
		{
			// Input data
			constexpr auto skill_count = 8;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(0, 20);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 3);
				}

				D2UnitStrc moo_pUnit{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;
				D2UnitGUID nOwnerGUID = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 3);

				const auto setup_data = [this, &skill_ids, &skill_levels, &owner_guids](
					D2UnitStrc& pUnit,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nSkillLevel = skill_levels[j];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pSkillList, original_pSkills);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSkillId, nOwnerGUID);
				const auto original_result = original(&original_pUnit, nSkillId, nOwnerGUID);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(moo_result ? moo_result - moo_pSkills : -1, original_result ? original_result - original_pSkills : -1);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FDB1FC0 (#10989)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CheckRequiredAttributes, dll_base + 0x00071FC0);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto k = 0; k < 10; ++k)
				{
					// Input data, the stats are sorted by their id
					const int stat_ids[] = { STAT_STRENGTH, STAT_ENERGY, STAT_DEXTERITY, STAT_VITALITY, STAT_LEVEL };
					std::vector<D2StatStrc> stat_array(std::size(stat_ids));

					for (auto j = 0; j < static_cast<int>(std::size(stat_ids)); ++j)
					{
						stat_array[j].nStat = static_cast<uint16_t>(stat_ids[j]);
						stat_array[j].nValue = random_unsigned_integer(0, 150);
					}

					const auto skill_level = random_unsigned_integer(0, 20);
					const auto has_skill = random_unsigned_integer(0, 1) != 0;

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2SkillListStrc moo_pSkillList{};
					D2SkillStrc moo_pSkill{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					D2SkillListStrc original_pSkillList{};
					D2SkillStrc original_pSkill{};
					int nSkillId = i;

					const auto setup_data = [this, &stat_array, i, skill_level, has_skill](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						D2SkillListStrc& pSkillList,
						D2SkillStrc& pSkill
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pUnit.pSkills = &pSkillList;
						pSkillList.pFirstSkill = has_skill ? &pSkill : nullptr;
						pSkill.pSkillsTxt = &skills_txt[i];
						pSkill.nSkillLevel = skill_level;
						pSkill.nOwnerGUID = D2UnitInvalidGUID;
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pSkillList, moo_pSkill);
					setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pSkillList, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nSkillId);
					const auto original_result = original(&original_pUnit, nSkillId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB2110 (#10999)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetToHitFactor, dll_base + 0x00072110);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j <= 30; ++j)
				{
					// Input data
					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};
					int nSkillId = i;
					int nSkillLevel = j;

					const auto setup_data = [](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel);
					const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillDescTxtFixture<ExperienceTxtFixture<SkillsTxtFixture<NoopFixture>>>>>, "D2Common.0x6FDB21E0 (#11000)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetHighestSkillLevelById, dll_base + 0x000721E0);

		SUBCASE("")
		{
			// Input data
			std::vector<D2StatStrc> stat_array;
			const auto add_stat = [&stat_array](int nStatId, int nLayer, int nValue)
			{
				D2StatStrc stat{};
				stat.nStat = static_cast<uint16_t>(nStatId);
				stat.nLayer = static_cast<uint16_t>(nLayer);
				stat.nValue = nValue;
				stat_array.push_back(stat);
			};

			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDCLASSSKILLS, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_NONCLASSSKILL, i, random_unsigned_integer(0, 5));
			}
			for (auto i = 0; i < skills_record_count; ++i)
			{
				add_stat(STAT_ITEM_SINGLESKILL, i, random_unsigned_integer(0, 3));
			}
			for (auto i = 0; i < 32; ++i)
			{
				add_stat(STAT_ITEM_ELEMSKILL, i, random_unsigned_integer(0, 3));
			}
			add_stat(STAT_ITEM_ALLSKILLS, 0, random_unsigned_integer(0, 3));
			for (auto i = 0; i < 8 * NUMBER_OF_PLAYERCLASSES; ++i)
			{
				add_stat(STAT_ITEM_ADDSKILL_TAB, i, random_unsigned_integer(0, 3));
			}

			std::sort(stat_array.begin(), stat_array.end(), [](const D2StatStrc& lhs, const D2StatStrc& rhs) { return lhs.nPackedValue < rhs.nPackedValue; });

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);
			constexpr auto skill_count = 4;

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto& flag : state_flags)
				{
					flag = random_unsigned_integer();
				}

				const auto class_id = random_unsigned_integer(0, NUMBER_OF_PLAYERCLASSES - 1);
				uint32_t skill_ids[skill_count]{};
				uint32_t skill_levels[skill_count]{};
				D2UnitGUID owner_guids[skill_count]{};

				for (auto j = 0; j < skill_count; ++j)
				{
					skill_ids[j] = random_unsigned_integer(0, 1) ? i : random_unsigned_integer(0, skills_record_count - 1);
					skill_levels[j] = random_unsigned_integer(0, 20);
					owner_guids[j] = random_unsigned_integer(0, 1) ? D2UnitInvalidGUID : random_unsigned_integer(0, 100);
				}

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				std::vector<uint32_t> moo_pStatFlags;
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkills[skill_count]{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				std::vector<uint32_t> original_pStatFlags;
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkills[skill_count]{};
				int nSkillId = i;

				const auto setup_data = [this, &stat_array, &state_flags, &skill_ids, &skill_levels, &owner_guids, class_id](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					std::vector<uint32_t>& pStatFlags,
					D2SkillListStrc& pSkillList,
					D2SkillStrc (&pSkills)[skill_count]
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwClassId = class_id;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkills[0];

					for (auto j = 0; j < skill_count; ++j)
					{
						pSkills[j].pSkillsTxt = &skills_txt[skill_ids[j]];
						pSkills[j].nSkillLevel = skill_levels[j];
						pSkills[j].nOwnerGUID = owner_guids[j];
						pSkills[j].pNextSkill = j + 1 < skill_count ? &pSkills[j + 1] : nullptr;
					}
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pStatFlags, moo_pSkillList, moo_pSkills);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pStatFlags, original_pSkillList, original_pSkills);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nSkillId);
				const auto original_result = original(&original_pUnit, nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB2280 (#11001)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetManaCosts, dll_base + 0x00072280);

		SUBCASE("")
		{
			for (auto j = 0; j < 30; ++j)
			{
				for (auto i = 0; i < skills_record_count; ++i)
				{
					int nSkillId = i;
					int nSkillLevel = j;

					// Call both implementations
					const auto moo_result = sut(nSkillId, nSkillLevel);
					const auto original_result = original(nSkillId, nSkillLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB22E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CalculateDamageBonusByLevel, dll_base + 0x000722E0);
		
		SUBCASE("")
		{
			// Input data
			uint32_t level_damage[5] = { random_unsigned_integer(0, 256), random_unsigned_integer(0, 256), random_unsigned_integer(0, 256), random_unsigned_integer(0, 256), random_unsigned_integer(0, 256) };

			int moo_pLevelDamage[5]{};
			int original_pLevelDamage[5]{};
			int nLevel{};

			const auto setup_data = [&level_damage](
				int (&pLevelDamage)[5]
			) {
				std::memcpy(pLevelDamage, level_damage, sizeof(pLevelDamage));
			};

			setup_data(moo_pLevelDamage);
			setup_data(original_pLevelDamage);

			// Call both implementations
			const auto moo_result = sut(nLevel, moo_pLevelDamage);
			const auto original_result = original(nLevel, original_pLevelDamage);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ((DynamicArray<int> { moo_pLevelDamage, 5 }), (DynamicArray<int> { original_pLevelDamage, 5 }), "Comparing pLevelDamage");
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FDB2390 (#11002)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetMinPhysDamage, dll_base + 0x00072390);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j <= 30; ++j)
				{
					// Input data, the stats are sorted by their id
					const int stat_ids[] = { STAT_STRENGTH, STAT_DEXTERITY, STAT_LEVEL, STAT_MINDAMAGE, STAT_MAXDAMAGE };
					std::vector<D2StatStrc> stat_array(std::size(stat_ids));

					for (auto k = 0; k < static_cast<int>(std::size(stat_ids)); ++k)
					{
						stat_array[k].nStat = static_cast<uint16_t>(stat_ids[k]);
						stat_array[k].nValue = random_unsigned_integer(0, 150);
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					int nSkillId = i;
					int nSkillLevel = j;
					BOOL a4 = random_unsigned_integer(0, 1);

					const auto setup_data = [&stat_array, unit_type](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat
					) {
						pUnit.dwUnitType = unit_type;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
					setup_data(original_pUnit, original_pStatListEx, original_pStat);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel, a4);
					const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel, a4);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FDB25D0 (#11003)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetMaxPhysDamage, dll_base + 0x000725D0);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j <= 30; ++j)
				{
					// Input data, the stats are sorted by their id
					const int stat_ids[] = { STAT_STRENGTH, STAT_DEXTERITY, STAT_LEVEL, STAT_MINDAMAGE, STAT_MAXDAMAGE };
					std::vector<D2StatStrc> stat_array(std::size(stat_ids));

					for (auto k = 0; k < static_cast<int>(std::size(stat_ids)); ++k)
					{
						stat_array[k].nStat = static_cast<uint16_t>(stat_ids[k]);
						stat_array[k].nValue = random_unsigned_integer(0, 150);
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					int nSkillId = i;
					int nSkillLevel = j;
					BOOL a4 = random_unsigned_integer(0, 1);

					const auto setup_data = [&stat_array, unit_type](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat
					) {
						pUnit.dwUnitType = unit_type;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
					setup_data(original_pUnit, original_pStatListEx, original_pStat);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel, a4);
					const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel, a4);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FDB2810 (#11004)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetMinElemDamage, dll_base + 0x00072810);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j <= 30; ++j)
				{
					// Input data
					std::vector<D2StatStrc> stat_array(4);

					for (auto k = 0; k < 4; ++k)
					{
						stat_array[k].nStat = static_cast<uint16_t>(STAT_PASSIVE_FIRE_MASTERY + k);
						stat_array[k].nValue = random_unsigned_integer(0, 200);
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					int nSkillId = i;
					int nSkillLevel = j;
					BOOL a4 = random_unsigned_integer(0, 1);

					const auto setup_data = [&stat_array](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
					setup_data(original_pUnit, original_pStatListEx, original_pStat);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel, a4);
					const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel, a4);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB29D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CalculateMasteryBonus, dll_base + 0x000729D0);

		const int nElemType = GENERATE(ELEMTYPE_NONE, ELEMTYPE_FIRE, ELEMTYPE_LTNG, ELEMTYPE_MAGIC, ELEMTYPE_COLD, ELEMTYPE_POIS, ELEMTYPE_FREEZE);

		SUBCASE("")
		{
			for (auto i = 0; i < 100; ++i)
			{
				// Input data
				std::vector<D2StatStrc> stat_array(4);

				for (auto k = 0; k < 4; ++k)
				{
					stat_array[k].nStat = static_cast<uint16_t>(STAT_PASSIVE_FIRE_MASTERY + k);
					stat_array[k].nValue = random_unsigned_integer(0, 200);
				}

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				int nSrcDamage = random_unsigned_integer(0, 0x200000);

				const auto setup_data = [&stat_array](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
				setup_data(original_pUnit, original_pStatListEx, original_pStat);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, nElemType, nSrcDamage);
				const auto original_result = original(&original_pUnit, nElemType, nSrcDamage);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<SkillsTxtFixture<NoopFixture>>, "D2Common.0x6FDB2B00 (#11005)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetMaxElemDamage, dll_base + 0x00072B00);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j <= 30; ++j)
				{
					// Input data
					std::vector<D2StatStrc> stat_array(4);

					for (auto k = 0; k < 4; ++k)
					{
						stat_array[k].nStat = static_cast<uint16_t>(STAT_PASSIVE_FIRE_MASTERY + k);
						stat_array[k].nValue = random_unsigned_integer(0, 200);
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					int nSkillId = i;
					int nSkillLevel = j;
					BOOL a4 = random_unsigned_integer(0, 1);

					const auto setup_data = [&stat_array](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat);
					setup_data(original_pUnit, original_pStatListEx, original_pStat);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel, a4);
					const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel, a4);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB2CA0 (#11006)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetElementalLength, dll_base + 0x00072CA0);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j <= 30; ++j)
				{
					// Input data
					D2UnitStrc moo_pUnit{};
					D2UnitStrc original_pUnit{};
					int nSkillId = i;
					int nSkillLevel = j;
					BOOL bUnused{};

					const auto setup_data = [](
						D2UnitStrc& pUnit
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
					};

					setup_data(moo_pUnit);
					setup_data(original_pUnit);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel, bUnused);
					const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel, bUnused);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB2E70 (#11239)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_Return0, dll_base + 0x00072E70);
		
		SUBCASE("")
		{
			int arg{};

			// Call both implementations
			const auto moo_result = sut(arg);
			const auto original_result = original(arg);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB2E80 (#11008)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetClassIdFromSkillId, dll_base + 0x00072E80);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				int nSkillId = i;

				// Call both implementations
				const auto moo_result = sut(nSkillId);
				const auto original_result = original(nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB2EC0 (#11010)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_IsPlayerClassSkill, dll_base + 0x00072EC0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				int moo_pPlayerClass{};
				int original_pPlayerClass{};
				int nSkillId = i;

				// Call both implementations
				const auto moo_result = sut(nSkillId, &moo_pPlayerClass);
				const auto original_result = original(nSkillId, &original_pPlayerClass);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pPlayerClass, original_pPlayerClass, "Comparing pPlayerClass");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB2F40 (#11011)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetQuantity, dll_base + 0x00072F40);
		
		SUBCASE("")
		{
			// Input data
			const auto quantity = random_unsigned_integer();

			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};

			const auto setup_data = [quantity](
				D2SkillStrc& pSkill
			) {
				pSkill.nQuantity = quantity;
			};

			setup_data(moo_pSkill);
			setup_data(original_pSkill);

			// Call both implementations
			const auto moo_result = sut(&moo_pSkill);
			const auto original_result = original(&original_pSkill);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB2F70 (#11012)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_SetQuantity, dll_base + 0x00072F70);
		
		SUBCASE("")
		{
			// Input data
			D2SkillStrc moo_pSkill{};
			D2SkillStrc original_pSkill{};
			int nQuantity = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSkill, nQuantity);
			original(&original_pSkill, nQuantity);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDB2FA0 (#11014)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11014_ConvertShapeShiftedMode, dll_base + 0x00072FA0);
		
		SUBCASE("")
		{
			for (auto j = 0; j < 20; ++j)
			{
				for (auto i = 0; i < monstats_record_count; ++i)
				{
					int nArrayIndex = j;
					int nMonsterId = i;

					// Call both implementations
					const auto moo_result = sut(nArrayIndex, nMonsterId);
					const auto original_result = original(nArrayIndex, nMonsterId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<StatesTxtFixture<NoopFixture>>>, "D2Common.0x6FDB30A0 (#11013)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_11013_ConvertMode, dll_base + 0x000730A0);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);

		SUBCASE("")
		{
			// Input data
			std::vector<short> transform_states;

			for (auto i = 0; i < states_record_count; ++i)
			{
				if (states_txt[i].dwStateFlags & gdwBitMasks[STATEMASK_DISGUISE])
				{
					transform_states.push_back(static_cast<short>(i));
				}
			}

			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			const auto previous_transform_states = sgptDataTables->pTransformStates;
			const auto previous_transform_state_count = sgptDataTables->nTransformStates;
			sgptDataTables->pTransformStates = transform_states.data();
			sgptDataTables->nTransformStates = static_cast<int>(transform_states.size());

			for (auto i = 0; i < 1000; ++i)
			{
				std::fill(state_flags.begin(), state_flags.end(), 0);

				if (!transform_states.empty() && random_unsigned_integer(0, 7))
				{
					const auto state = transform_states[random_unsigned_integer(0, static_cast<uint32_t>(transform_states.size()) - 1)];
					state_flags[state >> 5] |= gdwBitMasks[state & 31];
				}

				const auto shape_shifted = random_unsigned_integer(0, 7) != 0;
				const auto type = random_unsigned_integer(0, 5);
				const auto class_id = random_unsigned_integer(0, 100);
				// The mode is used as an index into fixed size tables (16 entries for monsters, 20 for players)
				const auto mode = random_unsigned_integer(0, unit_type == UNIT_MONSTER ? 15 : 19);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<uint32_t> moo_pStatFlags;
				int moo_pType{};
				int moo_pClass{};
				int moo_pMode{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<uint32_t> original_pStatFlags;
				int original_pType{};
				int original_pClass{};
				int original_pMode{};
				const char* szFile = __FILE__;
				int nLine = __LINE__;

				const auto setup_data = [&state_flags, unit_type, shape_shifted, type, class_id, mode](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<uint32_t>& pStatFlags,
					int& pType,
					int& pClass,
					int& pMode
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.dwFlagEx = shape_shifted ? UNITFLAGEX_ISSHAPESHIFTED : 0;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pType = type;
					pClass = class_id;
					pMode = mode;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags, moo_pType, moo_pClass, moo_pMode);
				setup_data(original_pUnit, original_pStatListEx, original_pStatFlags, original_pType, original_pClass, original_pMode);

				// Call both implementations
				sut(&moo_pUnit, &moo_pType, &moo_pClass, &moo_pMode, szFile, nLine);
				original(&original_pUnit, &original_pType, &original_pClass, &original_pMode, szFile, nLine);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pType, original_pType, "Comparing pType");
				MOO_CHECK_EQ(moo_pClass, original_pClass, "Comparing pClass");
				MOO_CHECK_EQ(moo_pMode, original_pMode, "Comparing pMode");
			}

			sgptDataTables->pTransformStates = previous_transform_states;
			sgptDataTables->nTransformStates = previous_transform_state_count;
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB3290 (#11015)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11015, dll_base + 0x00073290);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				// Input data
				const auto unit_id = random_unsigned_integer(0, 1000);
				const auto target_x = random_unsigned_integer(0, 0xFFFF);
				const auto target_y = random_unsigned_integer(0, 0xFFFF);
				const auto a2 = random_unsigned_integer(0, 1);
				const auto position = a2 ? unit_id + (UNIT_PLAYER << 16) : target_x + 3 * target_y;
				// Either the position is the same as last time (only the Y position changes) or it is a new position
				const auto x_position = random_unsigned_integer(0, 1) ? position : random_unsigned_integer();
				const auto y_position = random_unsigned_integer();

				D2UnitStrc moo_pUnit{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2SkillListStrc moo_pSkillList{};
				D2SkillStrc moo_pSkill{};
				D2UnitStrc original_pUnit{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2SkillListStrc original_pSkillList{};
				D2SkillStrc original_pSkill{};
				int nSkillId = i;

				const auto setup_data = [this, i, unit_id, target_x, target_y, x_position, y_position](
					D2UnitStrc& pUnit,
					D2DynamicPathStrc& pDynamicPath,
					D2SkillListStrc& pSkillList,
					D2SkillStrc& pSkill
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwUnitId = unit_id;
					pUnit.pDynamicPath = &pDynamicPath;
					pDynamicPath.tTargetCoord.X = static_cast<uint16_t>(target_x);
					pDynamicPath.tTargetCoord.Y = static_cast<uint16_t>(target_y);
					pUnit.pSkills = &pSkillList;
					pSkillList.pFirstSkill = &pSkill;
					pSkill.pSkillsTxt = &skills_txt[i];
					pSkill.nOwnerGUID = D2UnitInvalidGUID;
					pSkill.nXpos = x_position;
					pSkill.nYpos = y_position;
				};

				setup_data(moo_pUnit, moo_pDynamicPath, moo_pSkillList, moo_pSkill);
				setup_data(original_pUnit, original_pDynamicPath, original_pSkillList, original_pSkill);

				// Call both implementations
				sut(&moo_pUnit, a2, nSkillId);
				original(&original_pUnit, a2, nSkillId);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pSkillList, original_pSkillList, "Comparing pSkillList");
			}
		}
	}
	
	TEST_CASE_FIXTURE(StatesTxtFixture<CharStatsTxtFixture<SkillsTxtFixture<NoopFixture>>>, "D2Common.0x6FDB3340 (#11016)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11016, dll_base + 0x00073340);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_PLAYERCLASSES; ++j)
				{
					for (auto& flag : state_flags)
					{
						flag = random_unsigned_integer(0, 3) ? 0 : random_unsigned_integer();
					}

					const auto anim_mode = random_unsigned_integer(0, 19);

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<uint32_t> moo_pStatFlags;
					D2SkillStrc moo_pSkill{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<uint32_t> original_pStatFlags;
					D2SkillStrc original_pSkill{};

					const auto setup_data = [this, &state_flags, i, j, anim_mode](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<uint32_t>& pStatFlags,
						D2SkillStrc& pSkill
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.dwClassId = j;
						pUnit.dwAnimMode = anim_mode;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStatFlags = state_flags;
						pStatListEx.StatFlags = pStatFlags.data();
						pSkill.pSkillsTxt = &skills_txt[i];
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags, moo_pSkill);
					setup_data(original_pUnit, original_pStatListEx, original_pStatFlags, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, &moo_pSkill);
					const auto original_result = original(&original_pUnit, &original_pSkill);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<StatesTxtFixture<NoopFixture>>>, "D2Common.0x6FDB33A0 (#11017)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_11017_CheckUnitIfConsumeable, dll_base + 0x000733A0);

		const int a2 = GENERATE(0, 1);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_MONMODES; ++j)
				{
					for (auto& flag : state_flags)
					{
						flag = random_unsigned_integer(0, 3) ? 0 : random_unsigned_integer();
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<uint32_t> moo_pStatFlags;
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<uint32_t> original_pStatFlags;

					const auto setup_data = [&state_flags, i, j](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<uint32_t>& pStatFlags
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = j;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStatFlags = state_flags;
						pStatListEx.StatFlags = pStatFlags.data();
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags);
					setup_data(original_pUnit, original_pStatListEx, original_pStatFlags);

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
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<StatesTxtFixture<NoopFixture>>>, "D2Common.0x6FDB3480 (#11020)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11020, dll_base + 0x00073480);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_MONMODES; ++j)
				{
					for (auto& flag : state_flags)
					{
						flag = random_unsigned_integer(0, 3) ? 0 : random_unsigned_integer();
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<uint32_t> moo_pStatFlags;
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<uint32_t> original_pStatFlags;

					const auto setup_data = [&state_flags, i, j](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<uint32_t>& pStatFlags
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = j;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStatFlags = state_flags;
						pStatListEx.StatFlags = pStatFlags.data();
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags);
					setup_data(original_pUnit, original_pStatListEx, original_pStatFlags);

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
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<StatesTxtFixture<NoopFixture>>>, "D2Common.0x6FDB3520 (#11022)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CanUnitCorpseBeSelected, dll_base + 0x00073520);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < NUMBER_OF_MONMODES; ++j)
				{
					for (auto& flag : state_flags)
					{
						flag = random_unsigned_integer(0, 3) ? 0 : random_unsigned_integer();
					}

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<uint32_t> moo_pStatFlags;
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<uint32_t> original_pStatFlags;

					const auto setup_data = [&state_flags, i, j](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<uint32_t>& pStatFlags
					) {
						pUnit.dwUnitType = UNIT_MONSTER;
						pUnit.dwClassId = i;
						pUnit.dwAnimMode = j;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStatFlags = state_flags;
						pStatListEx.StatFlags = pStatFlags.data();
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags);
					setup_data(original_pUnit, original_pStatListEx, original_pStatFlags);

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
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemTypesTxtFixture<ItemsTxtFixture<SkillsTxtFixture<NoopFixture>>>>, "D2Common.0x6FDB35B0 (#11024)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11024, dll_base + 0x000735B0);

		const int nType = GENERATE(0, 1, 2, 3);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto k = 0; k < 10; ++k)
				{
					// Input data, mastery stats with item types as layers (one in each third of the item types, so they are unique and sorted)
					std::vector<D2StatStrc> stat_array;

					for (int nStatId = STAT_PASSIVE_MASTERY_MELEE_TH; nStatId <= STAT_PASSIVE_MASTERY_THROW_CRIT; ++nStatId)
					{
						for (auto j = 0; j < 3; ++j)
						{
							D2StatStrc stat{};
							stat.nStat = static_cast<uint16_t>(nStatId);
							stat.nLayer = static_cast<uint16_t>(random_unsigned_integer(j * itemtypes_record_count / 3, (j + 1) * itemtypes_record_count / 3 - 1));
							stat.nValue = random_unsigned_integer(0, 100);
							stat_array.push_back(stat);
						}
					}

					const auto item_class_id = random_unsigned_integer(0, items_record_count - 1);

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2UnitStrc moo_pItem{};
					D2SkillStrc moo_pSkill{};
					BOOL moo_pHasThrowBonus{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					D2UnitStrc original_pItem{};
					D2SkillStrc original_pSkill{};
					BOOL original_pHasThrowBonus{};

					const auto setup_data = [this, &stat_array, i, item_class_id](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						D2UnitStrc& pItem,
						D2SkillStrc& pSkill,
						BOOL& pHasThrowBonus
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = item_class_id;
						pSkill.pSkillsTxt = &skills_txt[i];
						pHasThrowBonus = TRUE;
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pItem, moo_pSkill, moo_pHasThrowBonus);
					setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pItem, original_pSkill, original_pHasThrowBonus);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, &moo_pItem, &moo_pSkill, nType, &moo_pHasThrowBonus);
					const auto original_result = original(&original_pUnit, &original_pItem, &original_pSkill, nType, &original_pHasThrowBonus);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
					MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
					MOO_CHECK_EQ(moo_pHasThrowBonus, original_pHasThrowBonus, "Comparing pHasThrowBonus");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemTypesTxtFixture<ItemsTxtFixture<SkillsTxtFixture<NoopFixture>>>>, "D2Common.0x6FDB36D0 (#11023)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetWeaponMasteryBonus, dll_base + 0x000736D0);

		const int nType = GENERATE(0, 1, 2, 3);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto k = 0; k < 10; ++k)
				{
					// Input data, mastery stats with item types as layers (one in each third of the item types, so they are unique and sorted)
					std::vector<D2StatStrc> stat_array;

					for (int nStatId = STAT_PASSIVE_MASTERY_MELEE_TH; nStatId <= STAT_PASSIVE_MASTERY_THROW_CRIT; ++nStatId)
					{
						for (auto j = 0; j < 3; ++j)
						{
							D2StatStrc stat{};
							stat.nStat = static_cast<uint16_t>(nStatId);
							stat.nLayer = static_cast<uint16_t>(random_unsigned_integer(j * itemtypes_record_count / 3, (j + 1) * itemtypes_record_count / 3 - 1));
							stat.nValue = random_unsigned_integer(0, 100);
							stat_array.push_back(stat);
						}
					}

					const auto item_class_id = random_unsigned_integer(0, items_record_count - 1);

					D2UnitStrc moo_pUnit{};
					D2StatListExStrc moo_pStatListEx{};
					std::vector<D2StatStrc> moo_pStat;
					D2UnitStrc moo_pItem{};
					D2SkillStrc moo_pSkill{};
					D2UnitStrc original_pUnit{};
					D2StatListExStrc original_pStatListEx{};
					std::vector<D2StatStrc> original_pStat;
					D2UnitStrc original_pItem{};
					D2SkillStrc original_pSkill{};

					const auto setup_data = [this, &stat_array, i, item_class_id](
						D2UnitStrc& pUnit,
						D2StatListExStrc& pStatListEx,
						std::vector<D2StatStrc>& pStat,
						D2UnitStrc& pItem,
						D2SkillStrc& pSkill
					) {
						pUnit.dwUnitType = UNIT_PLAYER;
						pUnit.pStatListEx = &pStatListEx;
						pStatListEx.dwFlags |= STATLIST_EXTENDED;
						pStat = stat_array;
						pStatListEx.FullStats.pStat = pStat.data();
						pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
						pItem.dwUnitType = UNIT_ITEM;
						pItem.dwClassId = item_class_id;
						pSkill.pSkillsTxt = &skills_txt[i];
					};

					setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pItem, moo_pSkill);
					setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pItem, original_pSkill);

					// Call both implementations
					const auto moo_result = sut(&moo_pUnit, &moo_pItem, &moo_pSkill, nType);
					const auto original_result = original(&original_pUnit, &original_pItem, &original_pSkill, nType);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
					MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB37B0 (#11032)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11032, dll_base + 0x000737B0);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j <= 5; ++j)
				{
					for (auto k = 0; k <= 3; ++k)
					{
						// Input data
						D2UnitStrc moo_pUnit{};
						D2UnitStrc original_pUnit{};
						int nSkillId = i;
						int nSkillLevel = j;
						int nType = k;

						const auto setup_data = [](
							D2UnitStrc& pUnit
						) {
							pUnit.dwUnitType = UNIT_PLAYER;
						};

						setup_data(moo_pUnit);
						setup_data(original_pUnit);

						// Call both implementations
						const auto moo_result = sut(&moo_pUnit, nSkillId, nSkillLevel, nType);
						const auto original_result = original(&original_pUnit, nSkillId, nSkillLevel, nType);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

						// Compare potentially modified input data
						MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
					}
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB3910 (#11025)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11025, dll_base + 0x00073910);

		SUBCASE("")
		{
			// Input data
			constexpr auto room_size = 32;
			std::vector<uint16_t> collision_mask(room_size * room_size);

			for (auto i = 0; i < 1000; ++i)
			{
				const auto room_x = random_unsigned_integer(1000, 2000);
				const auto room_y = random_unsigned_integer(1000, 2000);

				for (auto& mask : collision_mask)
				{
					mask = random_unsigned_integer(0, 7) ? 0 : static_cast<uint16_t>(random_unsigned_integer(0, 0xFFFF));
				}

				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				std::vector<uint16_t> moo_pCollisionMask;
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				std::vector<uint16_t> original_pCollisionMask;
				// The coordinates are mostly inside of the room
				int nX1 = room_x + random_unsigned_integer(0, room_size + 3) - 2;
				int nY1 = room_y + random_unsigned_integer(0, room_size + 3) - 2;
				int nX2 = room_x + random_unsigned_integer(0, room_size + 3) - 2;
				int nY2 = room_y + random_unsigned_integer(0, room_size + 3) - 2;
				int a6 = random_unsigned_integer(0, 0xFFFF);

				const auto setup_data = [&collision_mask, room_x, room_y](
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					std::vector<uint16_t>& pCollisionMask
				) {
					pRoom.tCoords.nSubtileX = room_x;
					pRoom.tCoords.nSubtileY = room_y;
					pRoom.tCoords.nSubtileWidth = room_size;
					pRoom.tCoords.nSubtileHeight = room_size;
					pRoom.pCollisionGrid = &pCollisionGrid;
					pCollisionGrid.pRoomCoords = pRoom.tCoords;
					pCollisionMask = collision_mask;
					pCollisionGrid.pCollisionMask = pCollisionMask.data();
				};

				setup_data(moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(nX1, nY1, nX2, nY2, &moo_pRoom, a6);
				const auto original_result = original(nX1, nY1, nX2, nY2, &original_pRoom, a6);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				MOO_CHECK_EQ((DynamicArray<uint16_t> { moo_pCollisionMask.data(), room_size * room_size }), (DynamicArray<uint16_t> { original_pCollisionMask.data(), room_size * room_size }), "Comparing pCollisionMask");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB3960 (#11026)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11026, dll_base + 0x00073960);

		SUBCASE("")
		{
			// Input data
			constexpr auto room_size = 32;
			std::vector<uint16_t> collision_mask(room_size * room_size);

			for (auto i = 0; i < 1000; ++i)
			{
				const auto room_x = random_unsigned_integer(1000, 2000);
				const auto room_y = random_unsigned_integer(1000, 2000);
				const auto unit_x = room_x + random_unsigned_integer(0, room_size - 1);
				const auto unit_y = room_y + random_unsigned_integer(0, room_size - 1);
				const auto has_room = random_unsigned_integer(0, 7) != 0;

				for (auto& mask : collision_mask)
				{
					mask = random_unsigned_integer(0, 7) ? 0 : static_cast<uint16_t>(random_unsigned_integer(0, 0xFFFF));
				}

				D2UnitStrc moo_pUnit{};
				D2DynamicPathStrc moo_pDynamicPath{};
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				std::vector<uint16_t> moo_pCollisionMask;
				D2UnitStrc original_pUnit{};
				D2DynamicPathStrc original_pDynamicPath{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				std::vector<uint16_t> original_pCollisionMask;
				// The coordinates are mostly inside of the room
				int nX = room_x + random_unsigned_integer(0, room_size + 3) - 2;
				int nY = room_y + random_unsigned_integer(0, room_size + 3) - 2;
				uint16_t nColMask = static_cast<uint16_t>(random_unsigned_integer(0, 0xFFFF));

				const auto setup_data = [&collision_mask, room_x, room_y, unit_x, unit_y, has_room](
					D2UnitStrc& pUnit,
					D2DynamicPathStrc& pDynamicPath,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					std::vector<uint16_t>& pCollisionMask
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pDynamicPath = &pDynamicPath;
					pDynamicPath.pUnit = &pUnit;
					pDynamicPath.tGameCoords.wPosX = static_cast<uint16_t>(unit_x);
					pDynamicPath.tGameCoords.wPosY = static_cast<uint16_t>(unit_y);
					pDynamicPath.pRoom = has_room ? &pRoom : nullptr;
					pRoom.tCoords.nSubtileX = room_x;
					pRoom.tCoords.nSubtileY = room_y;
					pRoom.tCoords.nSubtileWidth = room_size;
					pRoom.tCoords.nSubtileHeight = room_size;
					pRoom.pCollisionGrid = &pCollisionGrid;
					pCollisionGrid.pRoomCoords = pRoom.tCoords;
					pCollisionMask = collision_mask;
					pCollisionGrid.pCollisionMask = pCollisionMask.data();
				};

				setup_data(moo_pUnit, moo_pDynamicPath, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask);
				setup_data(original_pUnit, original_pDynamicPath, original_pRoom, original_pCollisionGrid, original_pCollisionMask);

				// Call both implementations
				const auto moo_result = sut(nX, nY, &moo_pUnit, nColMask);
				const auto original_result = original(nX, nY, &original_pUnit, nColMask);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB3A10 (#11027)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetShiftedManaCosts, dll_base + 0x00073A10);

		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				for (auto j = 0; j < 30; ++j)
				{
					int nSkillId = i;
					int nLevel = j;

					// Call both implementations
					const auto moo_result = sut(nSkillId, nLevel);
					const auto original_result = original(nSkillId, nLevel);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB3A90 (#11028)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11028, dll_base + 0x00073A90);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 1000; ++i)
			{
				int a1 = i;

				// Call both implementations
				const auto moo_result = sut(a1);
				const auto original_result = original(a1);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB3AB0 (#11033)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11033, dll_base + 0x00073AB0);
		
		SUBCASE("")
		{
			for (auto j = 0; j < 256; ++j)
			{
				for (auto i = 0; i < 256; ++i)
				{
					int nLevel = j;
					int nParam = i;
					int nMax = random_unsigned_integer(1024, 8092);

					// Call both implementations
					const auto moo_result = sut(nLevel, nParam, nMax);
					const auto original_result = original(nLevel, nParam, nMax);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB3B00 (#11034)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11034, dll_base + 0x00073B00);
		
		SUBCASE("")
		{
			for (auto j = 0; j < 100; ++j)
			{
				for (auto i = 0; i < skills_record_count; ++i)
				{
					int nLevel = j;
					int nSkillId = i;

					// Call both implementations
					const auto moo_result = sut(nLevel, nSkillId);
					const auto original_result = original(nLevel, nSkillId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB3B90 (#11035)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11035, dll_base + 0x00073B90);
		
		SUBCASE("")
		{
			for (auto j = 0; j < 100; ++j)
			{
				for (auto i = 0; i < skills_record_count; ++i)
				{
					int nLevel = j;
					int nSkillId = i;

					// Call both implementations
					const auto moo_result = sut(nLevel, nSkillId);
					const auto original_result = original(nLevel, nSkillId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB3C20 (#11036)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_11036_GetMonCurseResistanceSubtraction, dll_base + 0x00073C20);
		
		SUBCASE("")
		{
			for (auto j = 0; j < 100; ++j)
			{
				for (auto i = 0; i < skills_record_count; ++i)
				{
					int nLevel = j;
					int nSkillId = i;

					// Call both implementations
					const auto moo_result = sut(nLevel, nSkillId);
					const auto original_result = original(nLevel, nSkillId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB3CB0 (#11037)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CheckIfCanLeapTo, dll_base + 0x00073CB0);

		const int level_id = GENERATE(LEVEL_ROGUEENCAMPMENT, LEVEL_BLOODMOOR);

		SUBCASE("")
		{
			// Input data
			constexpr auto room_size = 64;
			std::vector<uint16_t> collision_mask(room_size * room_size);

			for (auto i = 0; i < 1000; ++i)
			{
				const auto room_x = random_unsigned_integer(1000, 2000);
				const auto room_y = random_unsigned_integer(1000, 2000);
				// The units are placed away from the room borders
				const auto unit1_x = room_x + random_unsigned_integer(16, room_size - 17);
				const auto unit1_y = room_y + random_unsigned_integer(16, room_size - 17);
				const auto unit2_x = room_x + random_unsigned_integer(16, room_size - 17);
				const auto unit2_y = room_y + random_unsigned_integer(16, room_size - 17);

				for (auto& mask : collision_mask)
				{
					mask = random_unsigned_integer(0, 7) ? 0 : static_cast<uint16_t>(random_unsigned_integer(0, 0xFFFF));
				}

				D2UnitStrc moo_pUnit1{};
				D2DynamicPathStrc moo_pDynamicPath1{};
				D2UnitStrc moo_pUnit2{};
				D2DynamicPathStrc moo_pDynamicPath2{};
				D2ActiveRoomStrc moo_pRoom{};
				D2RoomCollisionGridStrc moo_pCollisionGrid{};
				std::vector<uint16_t> moo_pCollisionMask;
				D2DrlgRoomStrc moo_pDrlgRoom{};
				D2DrlgLevelStrc moo_pLevel{};
				int moo_pX{};
				int moo_pY{};
				D2UnitStrc original_pUnit1{};
				D2DynamicPathStrc original_pDynamicPath1{};
				D2UnitStrc original_pUnit2{};
				D2DynamicPathStrc original_pDynamicPath2{};
				D2ActiveRoomStrc original_pRoom{};
				D2RoomCollisionGridStrc original_pCollisionGrid{};
				std::vector<uint16_t> original_pCollisionMask;
				D2DrlgRoomStrc original_pDrlgRoom{};
				D2DrlgLevelStrc original_pLevel{};
				int original_pX{};
				int original_pY{};

				const auto setup_data = [&collision_mask, level_id, room_x, room_y, unit1_x, unit1_y, unit2_x, unit2_y](
					D2UnitStrc& pUnit1,
					D2DynamicPathStrc& pDynamicPath1,
					D2UnitStrc& pUnit2,
					D2DynamicPathStrc& pDynamicPath2,
					D2ActiveRoomStrc& pRoom,
					D2RoomCollisionGridStrc& pCollisionGrid,
					std::vector<uint16_t>& pCollisionMask,
					D2DrlgRoomStrc& pDrlgRoom,
					D2DrlgLevelStrc& pLevel,
					int& pX,
					int& pY
				) {
					pRoom.tCoords.nSubtileX = room_x;
					pRoom.tCoords.nSubtileY = room_y;
					pRoom.tCoords.nSubtileWidth = room_size;
					pRoom.tCoords.nSubtileHeight = room_size;
					pRoom.pCollisionGrid = &pCollisionGrid;
					pCollisionGrid.pRoomCoords = pRoom.tCoords;
					pCollisionMask = collision_mask;
					pCollisionGrid.pCollisionMask = pCollisionMask.data();
					pRoom.pDrlgRoom = &pDrlgRoom;
					pDrlgRoom.pLevel = &pLevel;
					pLevel.nLevelId = level_id;

					pUnit1.dwUnitType = UNIT_PLAYER;
					pUnit1.pDynamicPath = &pDynamicPath1;
					pDynamicPath1.pUnit = &pUnit1;
					pDynamicPath1.tGameCoords.wPosX = static_cast<uint16_t>(unit1_x);
					pDynamicPath1.tGameCoords.wPosY = static_cast<uint16_t>(unit1_y);
					pDynamicPath1.pRoom = &pRoom;
					pDynamicPath1.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;

					pUnit2.dwUnitType = UNIT_PLAYER;
					pUnit2.pDynamicPath = &pDynamicPath2;
					pDynamicPath2.pUnit = &pUnit2;
					pDynamicPath2.tGameCoords.wPosX = static_cast<uint16_t>(unit2_x);
					pDynamicPath2.tGameCoords.wPosY = static_cast<uint16_t>(unit2_y);
					pDynamicPath2.pRoom = &pRoom;
					pDynamicPath2.dwCollisionPattern = COLLISION_PATTERN_SMALL_UNIT_PRESENCE;

					pX = -1;
					pY = -1;
				};

				setup_data(moo_pUnit1, moo_pDynamicPath1, moo_pUnit2, moo_pDynamicPath2, moo_pRoom, moo_pCollisionGrid, moo_pCollisionMask, moo_pDrlgRoom, moo_pLevel, moo_pX, moo_pY);
				setup_data(original_pUnit1, original_pDynamicPath1, original_pUnit2, original_pDynamicPath2, original_pRoom, original_pCollisionGrid, original_pCollisionMask, original_pDrlgRoom, original_pLevel, original_pX, original_pY);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit1, &moo_pUnit2, &moo_pX, &moo_pY);
				const auto original_result = original(&original_pUnit1, &original_pUnit2, &original_pX, &original_pY);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
				MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
				MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
				MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<NoopFixture>, "D2Common.0x6FDB3F60 (#11039)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_11039_CheckWeaponIsMissileBased, dll_base + 0x00073F60);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER, UNIT_MISSILE);

		SUBCASE("")
		{
			for (auto i = 0; i < 100; ++i)
			{
				// Input data, the stats are sorted by their id
				std::vector<D2StatStrc> stat_array(2);
				stat_array[0].nStat = STAT_ITEM_MAGICARROW;
				stat_array[0].nValue = random_unsigned_integer(0, 1) ? 0 : random_unsigned_integer(1, 5);
				stat_array[1].nStat = STAT_ITEM_EXPLOSIVEARROW;
				stat_array[1].nValue = random_unsigned_integer(0, 1) ? 0 : random_unsigned_integer(1, 5);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				int moo_pValue = -1;
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				int original_pValue = -1;

				const auto setup_data = [&stat_array, unit_type](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					int& pValue
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pValue);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pValue);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit, &moo_pValue);
				const auto original_result = original(&original_pUnit, &original_pValue);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pValue, original_pValue, "Comparing pValue");
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB4020 (#11040)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_IsEnhanceable, dll_base + 0x00074020);
		
		SUBCASE("")
		{
			for (auto i = 0; i < skills_record_count; ++i)
			{
				int nSkillId = i;

				// Call both implementations
				const auto moo_result = sut(nSkillId);
				const auto original_result = original(nSkillId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<NoopFixture>>, "D2Common.0x6FDB4070 (#11230)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_RemoveTransformStatesFromShapeshiftedUnit, dll_base + 0x00074070);

		SUBCASE("")
		{
			// Input data
			std::vector<short> transform_states;

			for (auto i = 0; i < states_record_count; ++i)
			{
				if (states_txt[i].dwStateFlags & gdwBitMasks[STATEMASK_DISGUISE])
				{
					transform_states.push_back(static_cast<short>(i));
				}
			}

			const auto transform_state_count = static_cast<int>(transform_states.size());
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);
			std::vector<bool> has_stat_lists(transform_state_count);

			const auto previous_transform_states = sgptDataTables->pTransformStates;
			const auto previous_transform_state_count = sgptDataTables->nTransformStates;
			sgptDataTables->pTransformStates = transform_states.data();
			sgptDataTables->nTransformStates = transform_state_count;

			for (auto i = 0; i < 100; ++i)
			{
				std::fill(state_flags.begin(), state_flags.end(), 0);

				for (auto j = 0; j < transform_state_count; ++j)
				{
					const auto state = transform_states[j];
					if (random_unsigned_integer(0, 1))
					{
						state_flags[state >> 5] |= gdwBitMasks[state & 31];
					}

					has_stat_lists[j] = random_unsigned_integer(0, 1) != 0;
				}

				const auto shape_shifted = random_unsigned_integer(0, 3) != 0;

				// The state stat lists get freed by the function, so they have to be allocated from the memory pool
				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<uint32_t> moo_pStatFlags;
				std::vector<D2StatListStrc*> moo_pStateStatLists(transform_state_count);
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<uint32_t> original_pStatFlags;
				std::vector<D2StatListStrc*> original_pStateStatLists(transform_state_count);

				for (auto j = 0; j < transform_state_count; ++j)
				{
					moo_pStateStatLists[j] = has_stat_lists[j] ? D2_CALLOC_STRC_POOL(nullptr, D2StatListStrc) : nullptr;
					original_pStateStatLists[j] = has_stat_lists[j] ? D2_CALLOC_STRC_POOL(nullptr, D2StatListStrc) : nullptr;
				}

				const auto setup_data = [&state_flags, &transform_states, transform_state_count, shape_shifted](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<uint32_t>& pStatFlags,
					std::vector<D2StatListStrc*>& pStateStatLists
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.dwFlagEx = shape_shifted ? UNITFLAGEX_ISSHAPESHIFTED : 0;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatListEx.pOwner = &pUnit;
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();

					// Link the state stat lists into the unit's stat list
					for (auto j = 0; j < transform_state_count; ++j)
					{
						if (D2StatListStrc* pStatList = pStateStatLists[j])
						{
							pStatList->dwOwnerType = UNIT_PLAYER;
							pStatList->dwStateNo = transform_states[j];
							pStatList->pUnit = &pUnit;
							pStatList->pParent = &pStatListEx;
							pStatList->pPrevLink = pStatListEx.pMyLastList;

							if (pStatListEx.pMyLastList)
							{
								pStatListEx.pMyLastList->pNextLink = pStatList;
							}

							pStatListEx.pMyLastList = pStatList;
						}
					}
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags, moo_pStateStatLists);
				setup_data(original_pUnit, original_pStatListEx, original_pStatFlags, original_pStateStatLists);

				// Call both implementations
				const auto moo_result = sut(&moo_pUnit);
				const auto original_result = original(&original_pUnit);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ((DynamicArray<uint32_t> { moo_pStatFlags.data(), 2 * flag_count }), (DynamicArray<uint32_t> { original_pStatFlags.data(), 2 * flag_count }), "Comparing StatFlags");

				// Clean up the stat lists that have not been freed
				for (auto pStatList = moo_pStatListEx.pMyLastList; pStatList;)
				{
					const auto pPrevLink = pStatList->pPrevLink;
					D2_FREE_POOL(nullptr, pStatList);
					pStatList = pPrevLink;
				}

				for (auto pStatList = original_pStatListEx.pMyLastList; pStatList;)
				{
					const auto pPrevLink = pStatList->pPrevLink;
					D2_FREE_POOL(nullptr, pStatList);
					pStatList = pPrevLink;
				}
			}

			sgptDataTables->pTransformStates = previous_transform_states;
			sgptDataTables->nTransformStates = previous_transform_state_count;
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB4100 (#11041)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetClassSkillId, dll_base + 0x00074100);
		
		SUBCASE("")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				for (auto j = 0; j < class_skill_counts[i]; ++j)
				{
					int nClassId = i;
					int nPosition = j;

					// Call both implementations
					const auto moo_result = sut(nClassId, nPosition);
					const auto original_result = original(nClassId, nPosition);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(SkillsTxtFixture<NoopFixture>, "D2Common.0x6FDB4150 (#11042)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetPlayerSkillCount, dll_base + 0x00074150);
		
		SUBCASE("")
		{
			for (auto i = 0; i < NUMBER_OF_PLAYERCLASSES; ++i)
			{
				int nClassId = i;

				// Call both implementations
				const auto moo_result = sut(nClassId);
				const auto original_result = original(nClassId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDB4180 (#11043)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11043, dll_base + 0x00074180);

		const auto unit_type = GENERATE(UNIT_PLAYER, UNIT_MONSTER);

		SUBCASE("")
		{
			for (auto i = 0; i < 100; ++i)
			{
				// Input data
				const auto shape_shifted = random_unsigned_integer(0, 3) != 0;
				const auto frame_count = random_unsigned_integer(0, 0x7FFFFFFF);

				D2UnitStrc moo_pUnit{};
				D2UnitStrc original_pUnit{};

				const auto setup_data = [unit_type, shape_shifted, frame_count](
					D2UnitStrc& pUnit
				) {
					pUnit.dwUnitType = unit_type;
					pUnit.dwFlagEx = shape_shifted ? UNITFLAGEX_ISSHAPESHIFTED : 0;
					pUnit.dwFrameCountPrecise = frame_count;
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
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<StatesTxtFixture<SkillsTxtFixture<NoopFixture>>>, "D2Common.0x6FDB41D0 (#11047)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_GetConcentrationDamageBonus, dll_base + 0x000741D0);

		SUBCASE("")
		{
			// Input data
			const auto flag_count = (states_record_count >> 5) + 1;
			std::vector<uint32_t> state_flags(2 * flag_count);

			for (auto i = 0; i < skills_record_count; ++i)
			{
				std::fill(state_flags.begin(), state_flags.end(), 0);

				if (random_unsigned_integer(0, 3))
				{
					state_flags[STATE_CONCENTRATION >> 5] |= gdwBitMasks[STATE_CONCENTRATION & 31];
				}

				const auto has_state_stat_list = random_unsigned_integer(0, 3) != 0;

				std::vector<D2StatStrc> stat_array(1);
				stat_array[0].nStat = STAT_DAMAGEPERCENT;
				stat_array[0].nValue = random_unsigned_integer(0, 500);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<uint32_t> moo_pStatFlags;
				D2StatListStrc moo_pStateStatList{};
				std::vector<D2StatStrc> moo_pStateStats;
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<uint32_t> original_pStatFlags;
				D2StatListStrc original_pStateStatList{};
				std::vector<D2StatStrc> original_pStateStats;
				int nSkillId = i;

				const auto setup_data = [&state_flags, &stat_array, has_state_stat_list](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<uint32_t>& pStatFlags,
					D2StatListStrc& pStateStatList,
					std::vector<D2StatStrc>& pStateStats
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStatFlags = state_flags;
					pStatListEx.StatFlags = pStatFlags.data();
					pStatListEx.pMyLastList = has_state_stat_list ? &pStateStatList : nullptr;
					pStateStatList.dwStateNo = STATE_CONCENTRATION;
					pStateStatList.pParent = &pStatListEx;
					pStateStatList.pUnit = &pUnit;
					pStateStats = stat_array;
					pStateStatList.Stats.pStat = pStateStats.data();
					pStateStatList.Stats.nStatCount = static_cast<uint16_t>(pStateStats.size());
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStatFlags, moo_pStateStatList, moo_pStateStats);
				setup_data(original_pUnit, original_pStatListEx, original_pStatFlags, original_pStateStatList, original_pStateStats);

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
	
	TEST_CASE_FIXTURE(ItemStatCostTxtFixture<ItemTypesTxtFixture<ItemsTxtFixture<NoopFixture>>>, "D2Common.0x6FDB4260 (#11283)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SKILLS_CalculateKickDamage, dll_base + 0x00074260);

		SUBCASE("")
		{
			for (auto i = 0; i < 1000; ++i)
			{
				// Input data, the stats are sorted by their id
				const int stat_ids[] = { STAT_STRENGTH, STAT_DEXTERITY, STAT_ITEM_MAXDAMAGE_PERCENT, STAT_DAMAGEPERCENT, STAT_ITEM_KICKDAMAGE };
				std::vector<D2StatStrc> stat_array(std::size(stat_ids));

				for (auto j = 0; j < static_cast<int>(std::size(stat_ids)); ++j)
				{
					stat_array[j].nStat = static_cast<uint16_t>(stat_ids[j]);
					stat_array[j].nValue = random_unsigned_integer(0, 200);
				}

				const auto has_inventory = random_unsigned_integer(0, 7) != 0;
				const auto has_boots = random_unsigned_integer(0, 7) != 0;
				const auto boots_class_id = random_unsigned_integer(0, items_record_count - 1);
				const auto min_damage = random_unsigned_integer(0, 100);
				const auto max_damage = random_unsigned_integer(0, 100);
				const auto damage_percent = random_unsigned_integer(0, 100);

				D2UnitStrc moo_pUnit{};
				D2StatListExStrc moo_pStatListEx{};
				std::vector<D2StatStrc> moo_pStat;
				D2InventoryStrc moo_pInventory{};
				D2InventoryGridStrc moo_pBodyLocGrid{};
				D2UnitStrc* moo_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc moo_pBoots{};
				D2ItemDataStrc moo_pBootsItemData{};
				int moo_pMinDamage{};
				int moo_pMaxDamage{};
				int moo_pDamagePercent{};
				D2UnitStrc original_pUnit{};
				D2StatListExStrc original_pStatListEx{};
				std::vector<D2StatStrc> original_pStat;
				D2InventoryStrc original_pInventory{};
				D2InventoryGridStrc original_pBodyLocGrid{};
				D2UnitStrc* original_pBodyLocItems[NUM_BODYLOC]{};
				D2UnitStrc original_pBoots{};
				D2ItemDataStrc original_pBootsItemData{};
				int original_pMinDamage{};
				int original_pMaxDamage{};
				int original_pDamagePercent{};

				const auto setup_data = [&stat_array, has_inventory, has_boots, boots_class_id, min_damage, max_damage, damage_percent](
					D2UnitStrc& pUnit,
					D2StatListExStrc& pStatListEx,
					std::vector<D2StatStrc>& pStat,
					D2InventoryStrc& pInventory,
					D2InventoryGridStrc& pBodyLocGrid,
					D2UnitStrc* (&pBodyLocItems)[NUM_BODYLOC],
					D2UnitStrc& pBoots,
					D2ItemDataStrc& pBootsItemData,
					int& pMinDamage,
					int& pMaxDamage,
					int& pDamagePercent
				) {
					pUnit.dwUnitType = UNIT_PLAYER;
					pUnit.pStatListEx = &pStatListEx;
					pStatListEx.dwFlags |= STATLIST_EXTENDED;
					pStat = stat_array;
					pStatListEx.FullStats.pStat = pStat.data();
					pStatListEx.FullStats.nStatCount = static_cast<uint16_t>(pStat.size());
					pUnit.pInventory = has_inventory ? &pInventory : nullptr;
					pInventory.dwSignature = D2C_InventoryHeader;
					pInventory.dwLeftItemGUID = D2UnitInvalidGUID;
					pInventory.pGrids = &pBodyLocGrid;
					pInventory.nGridCount = INVGRID_BODYLOC + 1;
					pBodyLocGrid.nGridWidth = NUM_BODYLOC;
					pBodyLocGrid.nGridHeight = 1;
					pBodyLocGrid.ppItems = pBodyLocItems;
					pBodyLocItems[BODYLOC_FEET] = has_boots ? &pBoots : nullptr;
					pBoots.dwUnitType = UNIT_ITEM;
					pBoots.dwClassId = boots_class_id;
					pBoots.pItemData = &pBootsItemData;
					pBootsItemData.nBodyLoc = BODYLOC_FEET;
					pMinDamage = min_damage;
					pMaxDamage = max_damage;
					pDamagePercent = damage_percent;
				};

				setup_data(moo_pUnit, moo_pStatListEx, moo_pStat, moo_pInventory, moo_pBodyLocGrid, moo_pBodyLocItems, moo_pBoots, moo_pBootsItemData, moo_pMinDamage, moo_pMaxDamage, moo_pDamagePercent);
				setup_data(original_pUnit, original_pStatListEx, original_pStat, original_pInventory, original_pBodyLocGrid, original_pBodyLocItems, original_pBoots, original_pBootsItemData, original_pMinDamage, original_pMaxDamage, original_pDamagePercent);

				// Call both implementations
				sut(&moo_pUnit, &moo_pMinDamage, &moo_pMaxDamage, &moo_pDamagePercent);
				original(&original_pUnit, &original_pMinDamage, &original_pMaxDamage, &original_pDamagePercent);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
				MOO_CHECK_EQ(moo_pBoots, original_pBoots, "Comparing pBoots");
				MOO_CHECK_EQ(moo_pMinDamage, original_pMinDamage, "Comparing pMinDamage");
				MOO_CHECK_EQ(moo_pMaxDamage, original_pMaxDamage, "Comparing pMaxDamage");
				MOO_CHECK_EQ(moo_pDamagePercent, original_pDamagePercent, "Comparing pDamagePercent");
			}
		}
	}
}
