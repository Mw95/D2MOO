#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2StatList.h>
#include <GAME/Game.h>
#include <MISSILES/MissMode.h>
#include <SKILLS/Skills.h>
#include <Units/Units.h>


TEST_SUITE("MissModeTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55CE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_UnitFindCallback_CanCollideWithMonster, dll_base + 0x00025CE0);
		
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
			void* moo_pArgument = nullptr;
			void* original_pArgument = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, moo_pArgument);
			const auto original_result = original(&original_pUnit, original_pArgument);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArgument, original_pArgument, "Comparing pArgument");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55D90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_UnitFindCallback_CanCollideWithGoodAlignmentUnit, dll_base + 0x00025D90);
		
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
			void* moo_pArgument = nullptr;
			void* original_pArgument = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, moo_pArgument);
			const auto original_result = original(&original_pUnit, original_pArgument);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArgument, original_pArgument, "Comparing pArgument");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55E60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_UnitFindCallback_CanCollideWithPlayerOrMonster, dll_base + 0x00025E60);
		
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
			void* moo_pArgument = nullptr;
			void* original_pArgument = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, moo_pArgument);
			const auto original_result = original(&original_pUnit, original_pArgument);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArgument, original_pArgument, "Comparing pArgument");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55F20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_UnitFindCallback_CanMissileDestroy, dll_base + 0x00025F20);
		
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
			void* moo_pArgument = nullptr;
			void* original_pArgument = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, moo_pArgument);
			const auto original_result = original(&original_pUnit, original_pArgument);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArgument, original_pArgument, "Comparing pArgument");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC55F80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_FillDamageParams, dll_base + 0x00025F80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				D2UnitStrc pTarget{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pMissile, pTarget, pDamage };
			};
			
			// Input data
			auto [moo_pMissile, moo_pTarget, moo_pDamage] = setup_data();
			auto [original_pMissile, original_pTarget, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pMissile, &moo_pTarget, &moo_pDamage);
			original(&original_pMissile, &original_pTarget, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC56290" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_RollDamageValue, dll_base + 0x00026290);
		
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
			int32_t nMinDamStat{};
			int32_t nMaxDamStat{};
			int32_t nMasteryStat{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, nMinDamStat, nMaxDamStat, nMasteryStat);
			const auto original_result = original(&original_pUnit, nMinDamStat, nMaxDamStat, nMasteryStat);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC56480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_GetDamageValue, dll_base + 0x00026480);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pAttacker{};
				D2UnitStrc pDefender{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pAttacker, pDefender, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pAttacker, moo_pDefender, moo_pDamage] = setup_data();
			auto [original_pGame, original_pAttacker, original_pDefender, original_pDamage] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pAttacker, &moo_pDefender, &moo_pDamage);
			const auto original_result = original(&original_pGame, &original_pAttacker, &original_pDefender, &original_pDamage);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC56730" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_ResetDamageParams, dll_base + 0x00026730);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC567E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_AddDamageValue, dll_base + 0x000267E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();
			int32_t nDamage{};

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage, nDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage, nDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC568F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_CreatePoisonCloudHitSubmissiles, dll_base + 0x000268F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pOwner{};
				D2UnitStrc pOrigin{};
				
				return std::tuple{ pGame, pOwner, pOrigin };
			};
			
			// Input data
			auto [moo_pGame, moo_pOwner, moo_pOrigin] = setup_data();
			auto [original_pGame, original_pOwner, original_pOrigin] = setup_data();
			int32_t nMissileId{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nSubStep{};
			int32_t nMainStep{};
			int32_t nLoops{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pOwner, &moo_pOrigin, nMissileId, nSkillId, nSkillLevel, nSubStep, nMainStep, nLoops);
			const auto original_result = original(&original_pGame, &original_pOwner, &original_pOrigin, nMissileId, nSkillId, nSkillLevel, nSubStep, nMainStep, nLoops);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pOrigin, original_pOrigin, "Comparing pOrigin");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC56AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_CreateImmolationArrowHitSubmissiles, dll_base + 0x00026AB0);
		
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
			int32_t nMissileId{};
			int32_t nRange{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, nMissileId, nRange);
			original(&original_pGame, &original_pUnit, a3, nMissileId, nRange);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC56D50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_HandleMissileCollision, dll_base + 0x00026D50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC56FA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_CreatePlagueJavelin_PoisonJavelin_PoisonTrapHitSubmissiles, dll_base + 0x00026FA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pOrigin{};
				
				return std::tuple{ pGame, pOrigin };
			};
			
			// Input data
			auto [moo_pGame, moo_pOrigin] = setup_data();
			auto [original_pGame, original_pOrigin] = setup_data();
			int32_t nMissileId{};
			int32_t nRange{};
			int32_t nLoops{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pOrigin, nMissileId, nRange, nLoops);
			const auto original_result = original(&original_pGame, &original_pOrigin, nMissileId, nRange, nLoops);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOrigin, original_pOrigin, "Comparing pOrigin");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC570B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo02_PlagueJavelin_PoisonJavelin_PoisonTrap, dll_base + 0x000270B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC57140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo03_PoisonCloud_Blizzard_ThunderStorm_HandOfGod, dll_base + 0x00027140);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC571D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo05_FireWall_ImmolationFire_MeteorFire_MoltenBoulderFirePath, dll_base + 0x000271D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC573B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo06_MoltenBoulder_FireWallMaker, dll_base + 0x000273B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC57510" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo07_GuidedArrow_BoneSpirit, dll_base + 0x00027510);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC57640" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo08_MonBlizzCenter, dll_base + 0x00027640);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC576F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_CreateMissileWithCollisionCheck, dll_base + 0x000276F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();
			int32_t nRange{};
			int32_t nFrames{};
			int32_t nMissileId{};
			uint16_t nCollisionMask{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, nRange, nFrames, nMissileId, nCollisionMask);
			const auto original_result = original(&original_pGame, &original_pMissile, nRange, nFrames, nMissileId, nCollisionMask);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC57910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo09_BatLightningBolt, dll_base + 0x00027910);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC57A40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo10_BlizzardCenter, dll_base + 0x00027A40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC57B60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo11_FingerMageSpider, dll_base + 0x00027B60);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC57DA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo12_DiabWallMaker, dll_base + 0x00027DA0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC57F00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo13_BoneWallMaker, dll_base + 0x00027F00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58140" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo14_GrimWard, dll_base + 0x00028140);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC581F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo15_FrozenOrb, dll_base + 0x000281F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo16_FrozenOrbNova, dll_base + 0x00028340);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo17_CairnStones, dll_base + 0x00028480);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC585E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo18_TowerChestSpawner, dll_base + 0x000285E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58860" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo20_BladeCreeper, dll_base + 0x00028860);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo21_Distraction, dll_base + 0x00028940);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58B00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo22_LightningTrailingJavelin, dll_base + 0x00028B00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo23_24_SuccFireBall_FirestormMaker, dll_base + 0x00028CC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo25_EruptionCenter, dll_base + 0x00028E10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC58F30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo26_Vines_PlagueVines, dll_base + 0x00028F30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC59040" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo27_Tornado, dll_base + 0x00029040);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC591C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo28_Volcano, dll_base + 0x000291C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC594B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo29_RecyclerDelay, dll_base + 0x000294B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC596C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo33_VineRecyclerDelay, dll_base + 0x000296C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC598D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo30_RabiesPlague, dll_base + 0x000298D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC59B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo31_WakeOfDestructionMaker_BaalColdMaker, dll_base + 0x00029B90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC59CB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo32_TigerFury, dll_base + 0x00029CB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC59D80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo34_BaalTauntControl, dll_base + 0x00029D80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC59FB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo35_RoyalStrikeChaosIce, dll_base + 0x00029FB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5A180" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit01_Fireball_ExplodingArrow_FreezingArrowExplosion, dll_base + 0x0002A180);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5A330" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit24_PantherPotOrange, dll_base + 0x0002A330);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5A4F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit02_PlagueJavelin_PoisonPotion, dll_base + 0x0002A4F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5A580" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit44_ExplodingJavelin, dll_base + 0x0002A580);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5A740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit03_ExplosivePotion_BombOnGround, dll_base + 0x0002A740);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5A760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit07_HolyBolt_FistOfTheHeavenBolt, dll_base + 0x0002A760);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5A9B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit08_Blaze, dll_base + 0x0002A9B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5AA00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit06_Unused, dll_base + 0x0002AA00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5AB00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit09_ImmolationArrow, dll_base + 0x0002AB00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5AD40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit10_GuidedArrow_BoneSpirit, dll_base + 0x0002AD40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5B020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit12_ChainLightning_LightningStrike, dll_base + 0x0002B020);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5B280" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit13_GlacialSpike_HellMeteorDown, dll_base + 0x0002B280);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5B4E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit04_ExplodingArrow_FreezingArrow_RoyalStrikeMeteorCenter, dll_base + 0x0002B4E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5B5C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit11_Unused, dll_base + 0x0002B5C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5B6A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit14_MeteorCenter_CatapultMeteor_RoyalStrikeMeteor, dll_base + 0x0002B6A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5B910" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_CreateMeteor_MoltenBoulderSubmissiles, dll_base + 0x0002B910);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();
			int32_t nMissileId{};
			int32_t nRange{};
			int32_t nStep{};

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, nMissileId, nRange, nStep);
			original(&original_pGame, &original_pMissile, nMissileId, nRange, nStep);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5BA50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit15_SpiderGooLay, dll_base + 0x0002BA50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5BB80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit16_SpiderGoo_VinesTrail_VinesWither, dll_base + 0x0002BB80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5BD30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit17_Howl, dll_base + 0x0002BD30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5BED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit18_Shout_BattleCommand_BattleOrders, dll_base + 0x0002BED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5BF30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit19_FingerMageSpider, dll_base + 0x0002BF30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5C0D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit20_LightningFury, dll_base + 0x0002C0D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5C2D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_LightningFury_AuraCallback, dll_base + 0x0002C2D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2AuraCallbackStrc pAuraCallback{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pAuraCallback, pTarget };
			};
			
			// Input data
			auto [moo_pAuraCallback, moo_pTarget] = setup_data();
			auto [original_pAuraCallback, original_pTarget] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAuraCallback, &moo_pTarget);
			const auto original_result = original(&original_pAuraCallback, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAuraCallback, original_pAuraCallback, "Comparing pAuraCallback");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5C3A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit21_BattleCry, dll_base + 0x0002C3A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5C4D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit22_FistOfTheHeavensDelay, dll_base + 0x0002C4D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5C790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_FistOfTheHeavensDelay_AuraCallback, dll_base + 0x0002C790);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2AuraCallbackStrc pAuraCallback{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pAuraCallback, pTarget };
			};
			
			// Input data
			auto [moo_pAuraCallback, moo_pTarget] = setup_data();
			auto [original_pAuraCallback, original_pTarget] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pAuraCallback, &moo_pTarget);
			const auto original_result = original(&original_pAuraCallback, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAuraCallback, original_pAuraCallback, "Comparing pAuraCallback");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5C860" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_CreatePantherPotGreenSubmissiles, dll_base + 0x0002C860);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pOwner{};
				D2UnitStrc pOrigin{};
				
				return std::tuple{ pGame, pOwner, pOrigin };
			};
			
			// Input data
			auto [moo_pGame, moo_pOwner, moo_pOrigin] = setup_data();
			auto [original_pGame, original_pOwner, original_pOrigin] = setup_data();
			int32_t nMissileId{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};
			int32_t nStep{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pOwner, &moo_pOrigin, nMissileId, nSkillId, nSkillLevel, nStep);
			const auto original_result = original(&original_pGame, &original_pOwner, &original_pOrigin, nMissileId, nSkillId, nSkillLevel, nStep);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
			SKIP_MOO_CHECK_EQ(moo_pOrigin, original_pOrigin, "Comparing pOrigin");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5C990" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit25_PantherPotGreen, dll_base + 0x0002C990);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5CA50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit26_GrimWardStart, dll_base + 0x0002CA50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5CBE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit27_GrimWard, dll_base + 0x0002CBE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5CBF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit28_GrimWardScare, dll_base + 0x0002CBF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5CE10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit29_FrozenOrb, dll_base + 0x0002CE10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5CF50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit05_Unused, dll_base + 0x0002CF50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit31_FireHead, dll_base + 0x0002D070);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit32_CairnStones, dll_base + 0x0002D160);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit33_TowerChestSpawner, dll_base + 0x0002D270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D290" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit35_OrbMist, dll_base + 0x0002D290);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D320" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit36_MissileInAir, dll_base + 0x0002D320);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit37_BladeCreeper, dll_base + 0x0002D430);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_CatapultChargedBall_LightningTrailingJavelin_SubmissileInitFunc, dll_base + 0x0002D440);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMissile{};
				
				return std::tuple{ pMissile };
			};
			
			// Input data
			auto [moo_pMissile] = setup_data();
			auto [original_pMissile] = setup_data();
			int32_t nUnused{};

			// Call both implementations
			sut(&moo_pMissile, nUnused);
			original(&original_pMissile, nUnused);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit38_CatapultChargedBall, dll_base + 0x0002D490);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D620" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit39_ImpSpawnMonsters, dll_base + 0x0002D620);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D6A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit40_CatapultSpikeBall, dll_base + 0x0002D6A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D7C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit43_HealingVortex, dll_base + 0x0002D7C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5D950" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit45_LightningTrailingJavelin, dll_base + 0x0002D950);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5DA80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit47_MoltenBoulder, dll_base + 0x0002DA80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5DD10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit48_MoltenBoulderEmerge, dll_base + 0x0002DD10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5DE50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit50_PlagueVinesTrail, dll_base + 0x0002DE50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5DED0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit51_VolcanoDebris, dll_base + 0x0002DED0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5DFC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit52_BladeFury, dll_base + 0x0002DFC0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E0D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit53_RabiesContagion, dll_base + 0x0002E0D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E160" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit54_BaalSpawnMonsters, dll_base + 0x0002E160);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit55_Baalnferno, dll_base + 0x0002E220);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E370" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit56_ArmageddonControl, dll_base + 0x0002E370);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit58_BaalTauntLightningControl, dll_base + 0x0002E530);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E760" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit59_BaalTauntPoisonControl, dll_base + 0x0002E760);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E7F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit23_Unused, dll_base + 0x0002E7F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg01_FireArrow_MagicArrow_ColdArrow, dll_base + 0x0002E890);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5E9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg12_LightningJavelin, dll_base + 0x0002E9D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5EB20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg02_IceArrow_RoyalStrikeChaos, dll_base + 0x0002EB20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5EC70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg03_Blaze_FireWall_ImmolationFire_MeteorFire, dll_base + 0x0002EC70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5ECE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg04_IceBlast, dll_base + 0x0002ECE0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5ED00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg10_BladesOfIceCubes, dll_base + 0x0002ED00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5ED50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg05_BlessedHammer, dll_base + 0x0002ED50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5EF40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg06_Unused, dll_base + 0x0002EF40);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5EF80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg07_Warcry_ShockWave, dll_base + 0x0002EF80);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F060" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg08_EruptionCrack, dll_base + 0x0002F060);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F0C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg09_Twister, dll_base + 0x0002F0C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F170" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg11_RabiesContagion, dll_base + 0x0002F170);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F1F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg13_BlessedHammerEx, dll_base + 0x0002F1F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmg14_MoltenBoulder, dll_base + 0x0002F250);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pUnit, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F4B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_GetMonStats2TxtRecord_6FC5F4B0, dll_base + 0x0002F4B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			int32_t nRecordId{};

			// Call both implementations
			const auto moo_result = sut(nRecordId);
			const auto original_result = original(nRecordId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F4E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SetDamageFlags, dll_base + 0x0002F4E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pDefender{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pMissile, pDefender, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pDefender, moo_pDamage] = setup_data();
			auto [original_pGame, original_pMissile, original_pDefender, original_pDamage] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, &moo_pDefender, &moo_pDamage);
			original(&original_pGame, &original_pMissile, &original_pDefender, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F6C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo19_RadamentDeath, dll_base + 0x0002F6C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F7C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_RadamentDeathAreaEffectCallback, dll_base + 0x0002F7C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pCorpse{};
				
				return std::tuple{ pGame, pUnit, pCorpse };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pCorpse] = setup_data();
			auto [original_pGame, original_pUnit, original_pCorpse] = setup_data();
			int32_t nSkillLevel{};
			int32_t nUnused{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pCorpse, nSkillLevel, nUnused);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pCorpse, nSkillLevel, nUnused);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pCorpse, original_pCorpse, "Comparing pCorpse");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F7E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_RadamentDeathAreaEffectCallbackFirstFrame, dll_base + 0x0002F7E0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pCorpse{};
				
				return std::tuple{ pGame, pUnit, pCorpse };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pCorpse] = setup_data();
			auto [original_pGame, original_pUnit, original_pCorpse] = setup_data();
			int32_t nSkillLevel{};
			int32_t nUnused{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pCorpse, nSkillLevel, nUnused);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pCorpse, nSkillLevel, nUnused);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pCorpse, original_pCorpse, "Comparing pCorpse");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F800" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo36_BaalFxControl, dll_base + 0x0002F800);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F860" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvHit57_BaalFxControl, dll_base + 0x0002F860);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F8B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo37_Unused, dll_base + 0x0002F8B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5F8C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDo01_BasicMissile, dll_base + 0x0002F8C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile);
			const auto original_result = original(&original_pGame, &original_pMissile);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC5FAD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDmgHitHandler, dll_base + 0x0002FAD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pMissile, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile, moo_pUnit] = setup_data();
			auto [original_pGame, original_pMissile, original_pUnit] = setup_data();
			int32_t a4{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pMissile, &moo_pUnit, a4);
			const auto original_result = original(&original_pGame, &original_pMissile, &original_pUnit, a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_ToggleStateOff, dll_base + 0x00030080);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				struct D2StatListStrc pStatList{};
				
				return std::tuple{ pUnit, pStatList };
			};
			
			// Input data
			auto [moo_pUnit, moo_pStatList] = setup_data();
			auto [original_pUnit, original_pStatList] = setup_data();
			int32_t nState{};

			// Call both implementations
			sut(&moo_pUnit, nState, &moo_pStatList);
			original(&original_pUnit, nState, &original_pStatList);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pStatList, original_pStatList, "Comparing pStatList");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC60090" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSMODE_SrvDoHandler, dll_base + 0x00030090);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ pGame, pMissile };
			};
			
			// Input data
			auto [moo_pGame, moo_pMissile] = setup_data();
			auto [original_pGame, original_pMissile] = setup_data();
			D2C_EventTypes nEventType{};

			// Call both implementations
			sut(&moo_pGame, &moo_pMissile, nEventType);
			original(&original_pGame, &original_pMissile, nEventType);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
}
