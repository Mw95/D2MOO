#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Game.h>
#include <MONSTER/MonsterUnique.h>
#include <Units/Units.h>


TEST_SUITE("MonsterUniqueTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_ToggleUnitFlag, dll_base + 0x0003AC00);
		
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
			int32_t nFlag{};
			int32_t bSet{};

			// Call both implementations
			sut(&moo_pUnit, nFlag, bSet);
			original(&original_pUnit, nFlag, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AC30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_GetUMods, dll_base + 0x0003AC30);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AC50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_GetNameSeed, dll_base + 0x0003AC50);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AC70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CheckMonTypeFlag, dll_base + 0x0003AC70);
		
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
			uint16_t nFlag{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nFlag);
			const auto original_result = original(&original_pUnit, nFlag);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6ACA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_ToggleMonTypeFlag, dll_base + 0x0003ACA0);
		
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
			uint16_t nFlag{};
			int32_t bSet{};

			// Call both implementations
			sut(&moo_pUnit, nFlag, bSet);
			original(&original_pUnit, nFlag, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6ACD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_GetBossHcIdx, dll_base + 0x0003ACD0);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6ACF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_HasUMods, dll_base + 0x0003ACF0);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AD10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_GetSuperUniqueBossHcIdx, dll_base + 0x0003AD10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AD50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod1_RandomName, dll_base + 0x0003AD50);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AD90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod2_HealthBonus, dll_base + 0x0003AD90);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AF70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CalculatePercentage, dll_base + 0x0003AF70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t a1{};
			int32_t a2{};
			int32_t a3{};

			// Call both implementations
			const auto moo_result = sut(a1, a2, a3);
			const auto original_result = original(a1, a2, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6AFF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod4_LevelBonus, dll_base + 0x0003AFF0);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod16_Champion, dll_base + 0x0003B030);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B210" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod36_Ghostly, dll_base + 0x0003B210);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B3A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod37_Fanatic, dll_base + 0x0003B3A0);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B3E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod38_Possessed, dll_base + 0x0003B3E0);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B4B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod39_Berserk, dll_base + 0x0003B4B0);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B5D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod41_AlwaysRun, dll_base + 0x0003B5D0);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod8_Resistant, dll_base + 0x0003B610);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B8C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod26_Teleport, dll_base + 0x0003B8C0);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6B910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod30_AuraEnchanted, dll_base + 0x0003B910);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6BA70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod5_Strong, dll_base + 0x0003BA70);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6BB80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod6_Fast, dll_base + 0x0003BB80);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6BC10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod9_FireEnchanted, dll_base + 0x0003BC10);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6BDD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod17_LightningEnchanted, dll_base + 0x0003BDD0);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6BF90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod18_ColdEnchanted, dll_base + 0x0003BF90);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6C160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod23_PoisonEnchanted, dll_base + 0x0003C160);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6C340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_UMod25_ManaSteal, dll_base + 0x0003C340);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6C4F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastAmplifyDamage, dll_base + 0x0003C4F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t a3{};
			int32_t a4{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, a4);
			original(&original_pGame, &original_pUnit, a3, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6C5B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CurseCallback_ApplyAmplifyDamage, dll_base + 0x0003C5B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pUnit, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pTarget] = setup_data();
			auto [original_pGame, original_pUnit, original_pTarget] = setup_data();
			int32_t nSkillLevel{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nSkillLevel);
			original(&original_pGame, &original_pUnit, &original_pTarget, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6C710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_FireEnchantedModeChange, dll_base + 0x0003C710);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pBoss{};
				
				return std::tuple{ pGame, pBoss };
			};
			
			// Input data
			auto [moo_pGame, moo_pBoss] = setup_data();
			auto [original_pGame, original_pBoss] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pBoss, nUMod, bUnique);
			original(&original_pGame, &original_pBoss, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pBoss, original_pBoss, "Comparing pBoss");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6C740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastCorpseExplode, dll_base + 0x0003C740);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6C9E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastCorpseExplode2, dll_base + 0x0003C9E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CAB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastNova, dll_base + 0x0003CAB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CB40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastLightUniqueMissile, dll_base + 0x0003CB40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CD30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6CD30, dll_base + 0x0003CD30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CD60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastColdUniqueMissile, dll_base + 0x0003CD60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CDB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastCorpsePoisonCloud, dll_base + 0x0003CDB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CE50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_KillMinions, dll_base + 0x0003CE50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CEC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_MinionCallback_KillMinion, dll_base + 0x0003CEC0);
		
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
			void* moo_pGameArg = nullptr;
			void* original_pGameArg = nullptr;
			void* moo_pUnused = nullptr;
			void* original_pUnused = nullptr;

			// Call both implementations
			sut(&moo_pUnit, moo_pGameArg, moo_pUnused);
			original(&original_pUnit, original_pGameArg, original_pUnused);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pGameArg, original_pGameArg, "Comparing pGameArg");
			SKIP_MOO_CHECK_EQ(moo_pUnused, original_pUnused, "Comparing pUnused");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CF10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6CF10, dll_base + 0x0003CF10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6CF90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6CF90, dll_base + 0x0003CF90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6D030" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_ScarabModeChange, dll_base + 0x0003D030);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pBoss{};
				
				return std::tuple{ pGame, pBoss };
			};
			
			// Input data
			auto [moo_pGame, moo_pBoss] = setup_data();
			auto [original_pGame, original_pBoss] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pBoss, nUMod, bUnique);
			original(&original_pGame, &original_pBoss, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pBoss, original_pBoss, "Comparing pBoss");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6D060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastBugLightningMissile, dll_base + 0x0003D060);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6D1C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_ApplyElementalDamage, dll_base + 0x0003D1C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6D410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_GetMonUModTxtRecord, dll_base + 0x0003D410);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			uint32_t nUMod{};

			// Call both implementations
			const auto moo_result = sut(nUMod);
			const auto original_result = original(nUMod);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6D440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6D440, dll_base + 0x0003D440);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6D690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_StealBeltItem, dll_base + 0x0003D690);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6D800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_QuestCompleteModeChange, dll_base + 0x0003D800);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6D8B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastQueenPoisonCloudMissile, dll_base + 0x0003D8B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6DA40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6DA40, dll_base + 0x0003DA40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6DCB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_LightningEnchantedModeChange, dll_base + 0x0003DCB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pBoss{};
				
				return std::tuple{ pGame, pBoss };
			};
			
			// Input data
			auto [moo_pGame, moo_pBoss] = setup_data();
			auto [original_pGame, original_pBoss] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pBoss, nUMod, bUnique);
			original(&original_pGame, &original_pBoss, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pBoss, original_pBoss, "Comparing pBoss");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6DCE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_ColdEnchantedModeChange, dll_base + 0x0003DCE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pBoss{};
				
				return std::tuple{ pGame, pBoss };
			};
			
			// Input data
			auto [moo_pGame, moo_pBoss] = setup_data();
			auto [original_pGame, original_pBoss] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pBoss, nUMod, bUnique);
			original(&original_pGame, &original_pBoss, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pBoss, original_pBoss, "Comparing pBoss");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6DD20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6DD20, dll_base + 0x0003DD20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6DDE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6DDE0, dll_base + 0x0003DDE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6DFA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_ApplyShatterState, dll_base + 0x0003DFA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6DFC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6DFC0, dll_base + 0x0003DFC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_SetTrapDamage, dll_base + 0x0003E070);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E240, dll_base + 0x0003E240);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E390" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_SuicideModeChange, dll_base + 0x0003E390);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pBoss{};
				
				return std::tuple{ pGame, pBoss };
			};
			
			// Input data
			auto [moo_pGame, moo_pBoss] = setup_data();
			auto [original_pGame, original_pBoss] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pBoss, nUMod, bUnique);
			original(&original_pGame, &original_pBoss, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pBoss, original_pBoss, "Comparing pBoss");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CastSuicideExplodeMissile, dll_base + 0x0003E410);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E700" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CreatePainWorm, dll_base + 0x0003E700);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E730" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E730, dll_base + 0x0003E730);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E770" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E770, dll_base + 0x0003E770);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E780, dll_base + 0x0003E780);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pUnit, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pMissile] = setup_data();
			auto [original_pGame, original_pUnit, original_pMissile] = setup_data();
			int32_t nIndex{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pMissile, nIndex);
			original(&original_pGame, &original_pUnit, &original_pMissile, nIndex);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E860" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E860, dll_base + 0x0003E860);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_AiFunction08_6FC6E870, dll_base + 0x0003E870);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E890, dll_base + 0x0003E890);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E8A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E8A0, dll_base + 0x0003E8A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit);
			original(&original_pGame, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E8B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E8B0, dll_base + 0x0003E8B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pUnit, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pMissile] = setup_data();
			auto [original_pGame, original_pUnit, original_pMissile] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pMissile);
			original(&original_pGame, &original_pUnit, &original_pMissile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E8D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E8D0, dll_base + 0x0003E8D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2RoomCoordListStrc pRoomCoordList{};
				
				return std::tuple{ pGame, pRoom, pRoomCoordList };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pRoomCoordList] = setup_data();
			auto [original_pGame, original_pRoom, original_pRoomCoordList] = setup_data();
			int32_t nSuperUniqueId{};
			int32_t a5{};
			uint16_t nX{};
			uint16_t nY{};
			int32_t a8{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pRoomCoordList, nSuperUniqueId, a5, nX, nY, a8);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pRoomCoordList, nSuperUniqueId, a5, nX, nY, a8);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pRoomCoordList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6E940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6E940, dll_base + 0x0003E940);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t a3{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3);
			original(&original_pGame, &original_pUnit, a3);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6EBE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_GetMonsterData, dll_base + 0x0003EBE0);
		
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

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit);
			const auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6EBF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_GetUModCount, dll_base + 0x0003EBF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				uint8_t pUMods{};
				
				return std::tuple{ pUMods };
			};
			
			// Input data
			auto [moo_pUMods] = setup_data();
			auto [original_pUMods] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pUMods);
			const auto original_result = original(&original_pUMods);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUMods, original_pUMods, "Comparing pUMods");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6EC10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6EC10, dll_base + 0x0003EC10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2MonUModTxt pMonUModTxtRecord{};
				
				return std::tuple{ pUnit, pMonUModTxtRecord };
			};
			
			// Input data
			auto [moo_pUnit, moo_pMonUModTxtRecord] = setup_data();
			auto [original_pUnit, original_pMonUModTxtRecord] = setup_data();
			int32_t bExpansion{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, &moo_pMonUModTxtRecord, bExpansion);
			const auto original_result = original(&original_pUnit, &original_pMonUModTxtRecord, bExpansion);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMonUModTxtRecord, original_pMonUModTxtRecord, "Comparing pMonUModTxtRecord");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6EE90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6EE90, dll_base + 0x0003EE90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				uint8_t a3{};
				
				return std::tuple{ pGame, pUnit, a3 };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_a3] = setup_data();
			auto [original_pGame, original_pUnit, original_a3] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_a3);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6F160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CheckMonModeFlag, dll_base + 0x0003F160);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nMonsterId{};
			int32_t nFlag{};

			// Call both implementations
			const auto moo_result = sut(nMonsterId, nFlag);
			const auto original_result = original(nMonsterId, nFlag);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6F1D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERUNIQUE_CheckMonStatsFlag, dll_base + 0x0003F1D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nMonsterId{};
			int32_t nFlag{};

			// Call both implementations
			const auto moo_result = sut(nMonsterId, nFlag);
			const auto original_result = original(nMonsterId, nFlag);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6F220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SpawnMonster_6FC6F220, dll_base + 0x0003F220);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2RoomCoordListStrc pRoomCoordList{};
				
				return std::tuple{ pGame, pRoom, pRoomCoordList };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pRoomCoordList] = setup_data();
			auto [original_pGame, original_pRoom, original_pRoomCoordList] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nUnitGUID{};
			int32_t nClassId{};
			int32_t a8{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, &moo_pRoomCoordList, nX, nY, nUnitGUID, nClassId, a8);
			const auto original_result = original(&original_pGame, &original_pRoom, &original_pRoomCoordList, nX, nY, nUnitGUID, nClassId, a8);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pRoomCoordList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6F440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SpawnMinions_6FC6F440, dll_base + 0x0003F440);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				D2RoomCoordListStrc pRoomCoordList{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pRoom, pRoomCoordList, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pRoomCoordList, moo_pUnit] = setup_data();
			auto [original_pGame, original_pRoom, original_pRoomCoordList, original_pUnit] = setup_data();
			int32_t bSpawnMinions{};
			int32_t nMinGroup{};
			int32_t nMaxGroup{};

			// Call both implementations
			sut(&moo_pGame, &moo_pRoom, &moo_pRoomCoordList, &moo_pUnit, bSpawnMinions, nMinGroup, nMaxGroup);
			original(&original_pGame, &original_pRoom, &original_pRoomCoordList, &original_pUnit, bSpawnMinions, nMinGroup, nMaxGroup);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pRoomCoordList, original_pRoomCoordList, "Comparing pRoomCoordList");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6F670" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6F670, dll_base + 0x0003F670);
		
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
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pUnit, nUMod, bUnique);
			original(&original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6F690" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_SpawnSuperUnique_6FC6F690, dll_base + 0x0003F690);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pGame, pRoom };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom] = setup_data();
			auto [original_pGame, original_pRoom] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nSuperUnique{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nX, nY, nSuperUnique);
			const auto original_result = original(&original_pGame, &original_pRoom, nX, nY, nSuperUnique);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6FBA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6FBA0, dll_base + 0x0003FBA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				uint8_t pUMods{};
				
				return std::tuple{ pGame, pRoom, pUMods };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pUMods] = setup_data();
			auto [original_pGame, original_pRoom, original_pUMods] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nClassId{};
			int32_t nUnitGUID{};
			uint16_t nNameSeed{};
			int32_t bChampion{};
			int32_t bSuperUnique{};
			int16_t nBossHcIdx{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nX, nY, nClassId, nUnitGUID, nNameSeed, bChampion, bSuperUnique, nBossHcIdx, &moo_pUMods);
			const auto original_result = original(&original_pGame, &original_pRoom, nX, nY, nClassId, nUnitGUID, nNameSeed, bChampion, bSuperUnique, nBossHcIdx, &original_pUMods);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pUMods, original_pUMods, "Comparing pUMods");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6FDC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC6FDC0, dll_base + 0x0003FDC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2ActiveRoomStrc pRoom{};
				uint8_t pUMods{};
				
				return std::tuple{ pGame, pRoom, pUMods };
			};
			
			// Input data
			auto [moo_pGame, moo_pRoom, moo_pUMods] = setup_data();
			auto [original_pGame, original_pRoom, original_pUMods] = setup_data();
			int32_t nX{};
			int32_t nY{};
			int32_t nClassId{};
			int32_t nUnitGUID{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pRoom, nX, nY, nClassId, nUnitGUID, &moo_pUMods);
			const auto original_result = original(&original_pGame, &original_pRoom, nX, nY, nClassId, nUnitGUID, &original_pUMods);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
			SKIP_MOO_CHECK_EQ(moo_pUMods, original_pUMods, "Comparing pUMods");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6FF10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_BOSSES_AssignUMod_6FC6FF10, dll_base + 0x0003FF10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			int32_t nUMod{};
			int32_t bUnique{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod, bUnique);
			original(&original_pGame, &original_pUnit, nUMod, bUnique);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC6FFD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERS_Unk_6FC6FFD0, dll_base + 0x0003FFD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit] = setup_data();
			auto [original_pGame, original_pUnit] = setup_data();
			uint8_t nUMod{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nUMod);
			original(&original_pGame, &original_pUnit, nUMod);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
