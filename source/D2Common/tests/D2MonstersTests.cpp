#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Monsters.h>
#include <Drlg/D2DrlgDrlg.h>
#include <Units/Units.h>

#include "TestFixtures/CompCodeTxtFixture.h"
#include "TestFixtures/HirelingTxtFixture.h"
#include "TestFixtures/LevelsTxtFixture.h"
#include "TestFixtures/MonstatsTxtFixture.h"
#include "TestFixtures/Monstats2TxtFixture.h"


TEST_SUITE("D2MonstersTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA4C10 (#11082)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_HirelingInit, dll_base + 0x00064C10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				D2HirelingInitStrc pHirelingInit{};
				
				return std::tuple{ pMonster, pHirelingInit };
			};
			
			// Input data
			auto [moo_pMonster, moo_pHirelingInit] = setup_data();
			auto [original_pMonster, original_pHirelingInit] = setup_data();
			BOOL bExpansion{};
			int nLowSeed{};
			int nAct{};
			int nDifficulty{};

			// Call both implementations
			const auto moo_result = sut(bExpansion, &moo_pMonster, nLowSeed, nAct, nDifficulty, &moo_pHirelingInit);
			const auto original_result = original(bExpansion, &original_pMonster, nLowSeed, nAct, nDifficulty, &original_pHirelingInit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pHirelingInit, original_pHirelingInit, "Comparing pHirelingInit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA4E20 (#11081)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11081, dll_base + 0x00064E20);

		REPEAT_10();
		
		SUBCASE("")
		{
			const auto hireling_init_id = GENERATE(0, 1, 2, 3);

			const auto setup_data = [hireling_init_id]() {
				D2HirelingInitStrc pHirelingInit{};

				pHirelingInit.nId = hireling_init_id;
				
				return std::tuple{ pHirelingInit };
			};
			
			// Input data
			auto [moo_pHirelingInit] = setup_data();
			auto [original_pHirelingInit] = setup_data();
			int nLowSeed = random_unsigned_integer();
			uint8_t a3 = GENERATE(0, 1, 2);

			// Call both implementations
			const auto moo_result = sut(nLowSeed, &moo_pHirelingInit, a3);
			const auto original_result = original(nLowSeed, &original_pHirelingInit, a3);
			
			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pHirelingInit, original_pHirelingInit, "Comparing pHirelingInit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA51A0 (#11085)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetHirelingDescString, dll_base + 0x000651A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int nId{};

			// Call both implementations
			const auto moo_result = sut(nId);
			const auto original_result = original(nId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(HirelingTxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDA51C0 (#11086)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetActFromHirelingTxt, dll_base + 0x000651C0);
		
		SUBCASE("bExpansion = FALSE, valid class_id")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				BOOL bExpansion = FALSE;
				int nClassId = class_id;
				uint16_t nNameId = 0;

				// Call both implementations
				const auto moo_result = sut(bExpansion, nClassId, nNameId);
				const auto original_result = original(bExpansion, nClassId, nNameId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}

		SUBCASE("bExpansion = TRUE, valid class_id")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				BOOL bExpansion = TRUE;
				int nClassId = class_id;
				uint16_t nNameId = 0;

				// Call both implementations
				const auto moo_result = sut(bExpansion, nClassId, nNameId);
				const auto original_result = original(bExpansion, nClassId, nNameId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}

		SUBCASE("")
		{
			std::set<std::pair<uint16_t, uint16_t>> unique_name_ids;
			for (auto i = 0; i < hireling_record_count; ++i)
			{
				const auto& hireling_record = hireling_txt[i];
				unique_name_ids.insert({hireling_record.wNameFirst, hireling_record.wNameLast});
			}

			SUBCASE("bExpansion = FALSE, invalid class_id")
			{
				for (auto pair : unique_name_ids)
				{
					for (auto name_id = pair.first; name_id < pair.second; ++name_id)
					{
						BOOL bExpansion = FALSE;
						int nClassId = -1;
						uint16_t nNameId = name_id;

						// Call both implementations
						const auto moo_result = sut(bExpansion, nClassId, nNameId);
						const auto original_result = original(bExpansion, nClassId, nNameId);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
					}
				}
			}

			SUBCASE("bExpansion = TRUE, invalid class_id")
			{
				for (auto pair : unique_name_ids)
				{
					for (auto name_id = pair.first; name_id < pair.second; ++name_id)
					{
						BOOL bExpansion = TRUE;
						int nClassId = -1;
						uint16_t nNameId = name_id;

						// Call both implementations
						const auto moo_result = sut(bExpansion, nClassId, nNameId);
						const auto original_result = original(bExpansion, nClassId, nNameId);

						// Compare return values
						MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
					}
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5200 (#11084)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetHirelingExpForNextLevel, dll_base + 0x00065200);
		
		SUBCASE("")
		{
			for (auto i = 1; i < 100; ++i)
			{
				int nLevel = i;
				int nExpPerLevel = random_unsigned_integer(0, 65535);

				// Call both implementations
				const auto moo_result = sut(nLevel, nExpPerLevel);
				const auto original_result = original(nLevel, nExpPerLevel);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5220 (#11083)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetHirelingResurrectionCost, dll_base + 0x00065220);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pHireling{};
				
				return std::tuple{ pHireling };
			};
			
			// Input data
			auto [moo_pHireling] = setup_data();
			auto [original_pHireling] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pHireling);
			const auto original_result = original(&original_pHireling);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pHireling, original_pHireling, "Comparing pHireling");
		}
	}
	
	TEST_CASE_FIXTURE(MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDA5270 (#11068)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2COMMON_11068_GetCompInfo, dll_base + 0x00065270);

		REPEAT_10();
		
		SUBCASE("")
		{
			const auto class_id = random_unsigned_integer(0, monstats_record_count - 1);

			const auto setup_data = [class_id]() {
				D2UnitStrc pMonster{};

				pMonster.dwUnitType = UNIT_MONSTER;
				pMonster.dwClassId = class_id;
				
				return std::tuple{ pMonster };
			};
			
			for (auto i = 0; i < 16; ++i)
			{
				// Input data
				auto [moo_pMonster] = setup_data();
				auto [original_pMonster] = setup_data();
				int nComponent = i;

				// Call both implementations
				const auto moo_result = sut(&moo_pMonster, nComponent);
				const auto original_result = original(&original_pMonster, nComponent);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}
	}
	
	TEST_CASE_FIXTURE(LevelsTxtFixture<CompCodeTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>>, "D2Common.0x6FDA52F0 (#11069)" * doctest::skip("Takes quite long, but passes"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11069, dll_base + 0x000652F0);
		
		SUBCASE("")
		{
			for (auto level_id = 0; level_id < levels_record_count; ++level_id)
			{
				for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
				{
					for (auto i = 0; i < 16; ++i)
					{
						for (auto j = 0; j < 12; ++j)
						{
							const auto setup_data = [class_id, level_id]() {
								D2DrlgLevelStrc pLevel{};
								pLevel.nLevelId = level_id;

								D2DrlgRoomStrc pDrlgRoom{};
								pDrlgRoom.pLevel = &pLevel;

								D2ActiveRoomStrc pRoom{};
								pRoom.pDrlgRoom = &pDrlgRoom;

								D2DynamicPathStrc pDynamicPath{};
								pDynamicPath.pRoom = &pRoom;

								D2UnitStrc pMonster{};

								pMonster.dwUnitType = UNIT_MONSTER;
								pMonster.dwClassId = class_id;

								pMonster.pDynamicPath = &pDynamicPath;

								return std::tuple{ pMonster, pDynamicPath, pRoom, pDrlgRoom, pLevel };
							};

							// Input data
							auto [moo_pMonster, moo_pDynamicPath, moo_pRoom, moo_pDrlgRoom, moo_pLevel] = setup_data();
							auto [original_pMonster, original_pDynamicPath, original_pRoom, original_pDrlgRoom, original_pLevel] = setup_data();
							unsigned int nIndex = i;
							unsigned int nComponent = j;

							// Call both implementations
							const auto moo_result = sut(&moo_pMonster, nIndex, nComponent);
							const auto original_result = original(&original_pMonster, nIndex, nComponent);

							// Compare return values
							MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

							// Compare potentially modified input data
							MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
						}
					}
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(CompCodeTxtFixture<MonStats2TxtFixture<MonStatsTxtFixture<NoopFixture>>>, "D2Common.0x6FDA5450 (#11070)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11070, dll_base + 0x00065450);

		REPEAT_10();
		
		SUBCASE("")
		{
			const auto monster_id = random_unsigned_integer(0, monstats_record_count - 1);

			for (auto i = 0; i < 16; ++i)
			{
				for (auto j = 0; j < 12; ++j)
				{
					// Input data
					int nMonsterId = monster_id;
					unsigned int nComponent = i;
					unsigned int a3 = j;

					// Call both implementations
					const auto moo_result = sut(nMonsterId, nComponent, a3);
					const auto original_result = original(nMonsterId, nComponent, a3);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA54E0 (#11050)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11050, dll_base + 0x000654E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				
				return std::tuple{ pUnit };
			};
			
			// Input data
			auto [moo_pUnit] = setup_data();
			auto [original_pUnit] = setup_data();
			int a2{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, a2);
			const auto original_result = original(&original_pUnit, a2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA55E0 (#11052)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11052, dll_base + 0x000655E0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				uint8_t a1 = i;

				// Call both implementations
				const auto moo_result = sut(a1);
				const auto original_result = original(a1);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5600 (#11053)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11053, dll_base + 0x00065600);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 64; ++i)
			{
				uint8_t a1 = i;

				// Call both implementations
				const auto moo_result = sut(a1);
				const auto original_result = original(a1);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5620 (#11054)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11054, dll_base + 0x00065620);
		
		SUBCASE("")
		{
			for (auto i = 0; i < 8; ++i)
			{
				uint8_t a1 = i;

				// Call both implementations
				const auto moo_result = sut(a1);
				const auto original_result = original(a1);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5640 (#11055)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11055, dll_base + 0x00065640);
		
		SUBCASE("")
		{
			const auto setup_data = []() {
				int a2{};
				int a3{};

				return std::tuple{ a2, a3 };
			};

			for (auto i = 0; i < 32; ++i)
			{
				// Input data
				auto [moo_a2, moo_a3] = setup_data();
				auto [original_a2, original_a3] = setup_data();
				uint8_t a1 = i;

				// Call both implementations
				sut(a1, &moo_a2, &moo_a3);
				original(a1, &original_a2, &original_a3);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
				MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5670 (#11297)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_SetMonsterNameInMonsterData, dll_base + 0x00065670);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();
			Unicode wszName{};

			// Call both implementations
			sut(&moo_pMonster, &wszName);
			original(&original_pMonster, &wszName);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA56C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_CanBeInTown, dll_base + 0x000656C0);

		SUBCASE("")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwClassId = class_id;

					return std::tuple{ pMonster };
				};

				// Input data
				auto [moo_pMonster] = setup_data();
				auto [original_pMonster] = setup_data();

				// Call both implementations
				const auto moo_result = sut(&moo_pMonster);
				const auto original_result = original(&original_pMonster);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA5750 (#11057)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_IsSandLeaper, dll_base + 0x00065750);
		
		SUBCASE("bAlwaysReturnFalse = FALSE")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwClassId = class_id;

					return std::tuple{ pMonster };
				};

				// Input data
				auto [moo_pMonster] = setup_data();
				auto [original_pMonster] = setup_data();
				BOOL bAlwaysReturnFalse = FALSE;

				// Call both implementations
				const auto moo_result = sut(&moo_pMonster, bAlwaysReturnFalse);
				const auto original_result = original(&original_pMonster, bAlwaysReturnFalse);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}

		SUBCASE("bAlwaysReturnFalse = TRUE")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwClassId = class_id;

					return std::tuple{ pMonster };
				};

				// Input data
				auto [moo_pMonster] = setup_data();
				auto [original_pMonster] = setup_data();
				BOOL bAlwaysReturnFalse = TRUE;

				// Call both implementations
				const auto moo_result = sut(&moo_pMonster, bAlwaysReturnFalse);
				const auto original_result = original(&original_pMonster, bAlwaysReturnFalse);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA57D0 (#11058)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_IsDemon, dll_base + 0x000657D0);
		
		SUBCASE("")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwClassId = class_id;

					return std::tuple{ pMonster };
				};

				// Input data
				auto [moo_pMonster] = setup_data();
				auto [original_pMonster] = setup_data();

				// Call both implementations
				const auto moo_result = sut(&moo_pMonster);
				const auto original_result = original(&original_pMonster);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA5830 (#11059)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_IsUndead, dll_base + 0x00065830);
		
		SUBCASE("")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwClassId = class_id;

					return std::tuple{ pMonster };
				};

				// Input data
				auto [moo_pMonster] = setup_data();
				auto [original_pMonster] = setup_data();

				// Call both implementations
				const auto moo_result = sut(&moo_pMonster);
				const auto original_result = original(&original_pMonster);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA58A0 (#11060)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_IsBoss, dll_base + 0x000658A0);
		
		SUBCASE("pMonStatsTxtRecord = nullptr")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2MonStatsTxt pMonStatsTxtRecord{};
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwClassId = class_id;

					return std::tuple{ pMonStatsTxtRecord, pMonster };
				};

				// Input data
				auto [moo_pMonStatsTxtRecord, moo_pMonster] = setup_data();
				auto [original_pMonStatsTxtRecord, original_pMonster] = setup_data();

				// Call both implementations
				const auto moo_result = sut(&moo_pMonStatsTxtRecord, &moo_pMonster);
				const auto original_result = original(&original_pMonStatsTxtRecord, &original_pMonster);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonStatsTxtRecord, original_pMonStatsTxtRecord, "Comparing pMonStatsTxtRecord");
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}

		SUBCASE("pMonStatsTxtRecord set")
		{
			const auto class_id = random_unsigned_integer(0, monstats_record_count - 1);

			const auto setup_data = [this, &class_id]() {
				D2MonStatsTxt pMonStatsTxtRecord{};
				D2UnitStrc pMonster{};

				pMonster.dwUnitType = UNIT_MONSTER;

				pMonStatsTxtRecord = monstats_txt[class_id];

				return std::tuple{ pMonStatsTxtRecord, pMonster };
			};

			// Input data
			auto [moo_pMonStatsTxtRecord, moo_pMonster] = setup_data();
			auto [original_pMonStatsTxtRecord, original_pMonster] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonStatsTxtRecord, &moo_pMonster);
			const auto original_result = original(&original_pMonStatsTxtRecord, &original_pMonster);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pMonStatsTxtRecord, original_pMonStatsTxtRecord, "Comparing pMonStatsTxtRecord");
			MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5900 (#11064)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_IsDead, dll_base + 0x00065900);
		
		SUBCASE("")
		{
			for (auto i = 0; i < NUMBER_OF_MONMODES; ++i)
			{
				const auto setup_data = [i]() {
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwAnimMode = i;

					return std::tuple{ pMonster };
				};

				// Input data
				auto [moo_pMonster] = setup_data();
				auto [original_pMonster] = setup_data();

				// Call both implementations
				const auto moo_result = sut(&moo_pMonster);
				const auto original_result = original(&original_pMonster);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5930 (#11280)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetSpawnMode_XY, dll_base + 0x00065930);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				int pSpawnMode{};
				int pX{};
				int pY{};
				
				return std::tuple{ pMonster, pSpawnMode, pX, pY };
			};
			
			// Input data
			auto [moo_pMonster, moo_pSpawnMode, moo_pX, moo_pY] = setup_data();
			auto [original_pMonster, original_pSpawnMode, original_pX, original_pY] = setup_data();
			BOOL bFromMonster{};
			int nSkillId{};
			int nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster, bFromMonster, nSkillId, nSkillLevel, &moo_pSpawnMode, &moo_pX, &moo_pY);
			const auto original_result = original(&original_pMonster, bFromMonster, nSkillId, nSkillLevel, &original_pSpawnMode, &original_pX, &original_pY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pSpawnMode, original_pSpawnMode, "Comparing pSpawnMode");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5B30 (#11061)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetMinionSpawnInfo, dll_base + 0x00065B30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				int pId{};
				int pX{};
				int pY{};
				int pSpawnMode{};
				
				return std::tuple{ pMonster, pId, pX, pY, pSpawnMode };
			};
			
			// Input data
			auto [moo_pMonster, moo_pId, moo_pX, moo_pY, moo_pSpawnMode] = setup_data();
			auto [original_pMonster, original_pId, original_pX, original_pY, original_pSpawnMode] = setup_data();
			int nDifficulty{};

			// Call both implementations
			sut(&moo_pMonster, &moo_pId, &moo_pX, &moo_pY, &moo_pSpawnMode, nDifficulty, nullptr);
			original(&original_pMonster, &original_pId, &original_pX, &original_pY, &original_pSpawnMode, nDifficulty, nullptr);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pId, original_pId, "Comparing pId");
			SKIP_MOO_CHECK_EQ(moo_pX, original_pX, "Comparing pX");
			SKIP_MOO_CHECK_EQ(moo_pY, original_pY, "Comparing pY");
			SKIP_MOO_CHECK_EQ(moo_pSpawnMode, original_pSpawnMode, "Comparing pSpawnMode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA6410 (#11051)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetMaximalLightRadius, dll_base + 0x00066410);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster);
			const auto original_result = original(&original_pMonster);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(LevelsTxtFixture<MonStatsTxtFixture<NoopFixture>>, "D2Common.0x6FDA64B0 (#11063)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11063, dll_base + 0x000664B0);
		
		SUBCASE("")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 1; j < levels_record_count; ++j)
				{
					const auto setup_data = [j]() {
						D2DrlgLevelStrc pLevel{};
						pLevel.nLevelId = j;

						D2DrlgRoomStrc pDrlgRoom{};
						pDrlgRoom.pLevel = &pLevel;

						D2ActiveRoomStrc pRoom{};
						pRoom.pDrlgRoom = &pDrlgRoom;

						return std::tuple{ pRoom, pDrlgRoom, pLevel };
					};

					// Input data
					auto [moo_pRoom, moo_pDrlgRoom, moo_pLevel] = setup_data();
					auto [original_pRoom, original_pDrlgRoom, original_pLevel] = setup_data();
					int nMonsterId = i;

					// Call both implementations
					const auto moo_result = sut(&moo_pRoom, nMonsterId);
					const auto original_result = original(&original_pRoom, nMonsterId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

					// Compare potentially modified input data
					MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA6620 (#11065)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_IsPrimeEvil, dll_base + 0x00066620);
		
		SUBCASE("")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwClassId = class_id;

					return std::tuple{ pMonster };
				};

				// Input data
				auto [moo_pMonster] = setup_data();
				auto [original_pMonster] = setup_data();

				// Call both implementations
				const auto moo_result = sut(&moo_pMonster);
				const auto original_result = original(&original_pMonster);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA6680 (#11066)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Common_11066, dll_base + 0x00066680);
		
		SUBCASE("")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2UnitStrc pMonster{};

					pMonster.dwUnitType = UNIT_MONSTER;
					pMonster.dwClassId = class_id;

					int pDirectionX{};
					int pDirectionY{};

					return std::tuple{ pMonster, pDirectionX, pDirectionY };
				};

				// Input data
				auto [moo_pMonster, moo_pDirectionX, moo_pDirectionY] = setup_data();
				auto [original_pMonster, original_pDirectionX, original_pDirectionY] = setup_data();

				// Call both implementations
				sut(&moo_pMonster, &moo_pDirectionX, &moo_pDirectionY);
				original(&original_pMonster, &original_pDirectionX, &original_pDirectionY);

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
				MOO_CHECK_EQ(moo_pDirectionX, original_pDirectionX, "Comparing pDirectionX");
				MOO_CHECK_EQ(moo_pDirectionY, original_pDirectionY, "Comparing pDirectionY");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA6730 (#11067)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetHirelingTypeId, dll_base + 0x00066730);
		
		SUBCASE("")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				const auto setup_data = [class_id]() {
					D2UnitStrc pHireling{};

					pHireling.dwUnitType = UNIT_MONSTER;
					pHireling.dwClassId = class_id;

					return std::tuple{ pHireling };
				};

				// Input data
				auto [moo_pHireling] = setup_data();
				auto [original_pHireling] = setup_data();

				// Call both implementations
				const auto moo_result = sut(&moo_pHireling);
				const auto original_result = original(&original_pHireling);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

				// Compare potentially modified input data
				MOO_CHECK_EQ(moo_pHireling, original_pHireling, "Comparing pHireling");
			}
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA6790 (#11246)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_ApplyClassicScaling, dll_base + 0x00066790);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				
				return std::tuple{ pMonster };
			};
			
			// Input data
			auto [moo_pMonster] = setup_data();
			auto [original_pMonster] = setup_data();
			BOOL bExpansion{};
			uint8_t nDifficulty{};

			// Call both implementations
			sut(&moo_pMonster, bExpansion, nDifficulty);
			original(&original_pMonster, bExpansion, nDifficulty);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA6920")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetBaseIdFromMonsterId, dll_base + 0x00066920);
		
		SUBCASE("")
		{
			for (auto class_id = 0; class_id < monstats_record_count; ++class_id)
			{
				int nMonsterId = class_id;

				// Call both implementations
				const auto moo_result = sut(nMonsterId);
				const auto original_result = original(nMonsterId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA6950")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_GetClassIdFromMonsterChain, dll_base + 0x00066950);
		
		SUBCASE("")
		{
			for (auto i = 0; i < monstats_record_count; ++i)
			{
				for (auto j = 0; j < 16; ++j)
				{
					int nMonsterId = i;
					int nChainId = j;

					// Call both implementations
					const auto moo_result = sut(nMonsterId, nChainId);
					const auto original_result = original(nMonsterId, nChainId);

					// Compare return values
					MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				}
			}
		}
	}
	
	TEST_CASE_FIXTURE(MonStatsTxtFixture<NoopFixture>, "D2Common.0x6FDA69C0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERS_ValidateMonsterId, dll_base + 0x000669C0);
		
		SUBCASE("")
		{
			for (auto class_id = -1; class_id < monstats_record_count + 1; ++class_id)
			{
				int nMonsterId = class_id;

				// Call both implementations
				const auto moo_result = sut(nMonsterId);
				const auto original_result = original(nMonsterId);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}
		}
	}
}
