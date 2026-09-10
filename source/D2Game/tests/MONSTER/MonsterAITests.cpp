#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <MONSTER/MonsterAI.h>
#include <Units/Units.h>


TEST_SUITE("MonsterAITests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61190" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61190, dll_base + 0x00031190);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				Unk pItemCode{};
				
				return std::tuple{ pGame, pMonster, pItemCode };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster, moo_pItemCode] = setup_data();
			auto [original_pGame, original_pMonster, original_pItemCode] = setup_data();
			DWORD dwILvl{};
			DWORD dwQuality{};

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster, &moo_pItemCode, dwILvl, dwQuality);
			original(&original_pGame, &original_pMonster, &original_pItemCode, dwILvl, dwQuality);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pItemCode, original_pItemCode, "Comparing pItemCode");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61270" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61270, dll_base + 0x00031270);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pUnit{};
				D2MercDataStrc pMercData{};
				
				return std::tuple{ pGame, pPlayer, pUnit, pMercData };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pUnit, moo_pMercData] = setup_data();
			auto [original_pGame, original_pPlayer, original_pUnit, original_pMercData] = setup_data();
			int16_t nId{};
			int32_t bDead{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pUnit, nId, &moo_pMercData, bDead);
			original(&original_pGame, &original_pPlayer, &original_pUnit, nId, &original_pMercData, bDead);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pMercData, original_pMercData, "Comparing pMercData");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERAI_SendMercStats, dll_base + 0x00031490);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pGame, pPlayer };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer] = setup_data();
			auto [original_pGame, original_pPlayer] = setup_data();
			DWORD dwZero{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, dwZero);
			original(&original_pGame, &original_pPlayer, dwZero);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERAI_UpdateMercStatsAndSkills, dll_base + 0x00031610);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pMerc{};
				
				return std::tuple{ pGame, pPlayer, pMerc };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pMerc] = setup_data();
			auto [original_pGame, original_pPlayer, original_pMerc] = setup_data();
			int32_t nLevel{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pMerc, nLevel);
			original(&original_pGame, &original_pPlayer, &original_pMerc, nLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pMerc, original_pMerc, "Comparing pMerc");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61980" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERAI_AllocMonsterInteract, dll_base + 0x00031980);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				
				return std::tuple{ pGame };
			};
			
			// Input data
			auto [moo_pGame] = setup_data();
			auto [original_pGame] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pGame);
			const auto original_result = original(&original_pGame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC619A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERAI_FreeMonsterInteract, dll_base + 0x000319A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2MonsterInteractStrc pMonInteract{};
				
				return std::tuple{ pGame, pMonInteract };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonInteract] = setup_data();
			auto [original_pGame, original_pMonInteract] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMonInteract);
			original(&original_pGame, &original_pMonInteract);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonInteract, original_pMonInteract, "Comparing pMonInteract");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC619F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERAI_GetInteractUnitCount, dll_base + 0x000319F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MonsterInteractStrc pMonInteract{};
				
				return std::tuple{ pMonInteract };
			};
			
			// Input data
			auto [moo_pMonInteract] = setup_data();
			auto [original_pMonInteract] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonInteract);
			const auto original_result = original(&original_pMonInteract);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonInteract, original_pMonInteract, "Comparing pMonInteract");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61A10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERAI_HasInteractUnit, dll_base + 0x00031A10);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MonsterInteractStrc pMonInteract{};
				
				return std::tuple{ pMonInteract };
			};
			
			// Input data
			auto [moo_pMonInteract] = setup_data();
			auto [original_pMonInteract] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonInteract);
			const auto original_result = original(&original_pMonInteract);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonInteract, original_pMonInteract, "Comparing pMonInteract");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61A30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERAI_IsInteractingWith, dll_base + 0x00031A30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2MonsterInteractStrc pMonInteract{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pMonInteract, pUnit };
			};
			
			// Input data
			auto [moo_pMonInteract, moo_pUnit] = setup_data();
			auto [original_pMonInteract, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonInteract, &moo_pUnit);
			const auto original_result = original(&original_pMonInteract, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonInteract, original_pMonInteract, "Comparing pMonInteract");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61A50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MONSTERAI_RemoveInteractInfoFor, dll_base + 0x00031A50);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				D2MonsterInteractStrc pMonInteract{};
				
				return std::tuple{ pGame, pMonster, pMonInteract };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster, moo_pMonInteract] = setup_data();
			auto [original_pGame, original_pMonster, original_pMonInteract] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster, &moo_pMonInteract);
			original(&original_pGame, &original_pMonster, &original_pMonInteract);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pMonInteract, original_pMonInteract, "Comparing pMonInteract");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61AB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61AB0, dll_base + 0x00031AB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pNpc{};
				D2MonsterInteractStrc pMonInteract{};
				
				return std::tuple{ pGame, pUnit, pNpc, pMonInteract };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pNpc, moo_pMonInteract] = setup_data();
			auto [original_pGame, original_pUnit, original_pNpc, original_pMonInteract] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pNpc, &moo_pMonInteract);
			original(&original_pGame, &original_pUnit, &original_pNpc, &original_pMonInteract);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pMonInteract, original_pMonInteract, "Comparing pMonInteract");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61AF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_NPCS_SetInteractTrading_6FC61AF0, dll_base + 0x00031AF0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pNPC{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pNPC, pPlayer };
			};
			
			// Input data
			auto [moo_pNPC, moo_pPlayer] = setup_data();
			auto [original_pNPC, original_pPlayer] = setup_data();

			// Call both implementations
			sut(&moo_pNPC, &moo_pPlayer);
			original(&original_pNPC, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61B30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61B30, dll_base + 0x00031B30);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pMonster, pPlayer };
			};
			
			// Input data
			auto [moo_pMonster, moo_pPlayer] = setup_data();
			auto [original_pMonster, original_pPlayer] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster, &moo_pPlayer);
			const auto original_result = original(&original_pMonster, &original_pPlayer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61B70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61B70, dll_base + 0x00031B70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pNpc{};
				D2MonsterInteractStrc pMonInteract{};
				
				return std::tuple{ pGame, pPlayer, pNpc, pMonInteract };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pNpc, moo_pMonInteract] = setup_data();
			auto [original_pGame, original_pPlayer, original_pNpc, original_pMonInteract] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pNpc, &moo_pMonInteract);
			original(&original_pGame, &original_pPlayer, &original_pNpc, &original_pMonInteract);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pNpc, original_pNpc, "Comparing pNpc");
			SKIP_MOO_CHECK_EQ(moo_pMonInteract, original_pMonInteract, "Comparing pMonInteract");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61C70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61C70, dll_base + 0x00031C70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pTarget{};
				D2MonsterInteractStrc pMonInteract{};
				
				return std::tuple{ pGame, pUnit, pTarget, pMonInteract };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pTarget, moo_pMonInteract] = setup_data();
			auto [original_pGame, original_pUnit, original_pTarget, original_pMonInteract] = setup_data();
			char a5{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, &moo_pMonInteract, a5);
			original(&original_pGame, &original_pUnit, &original_pTarget, &original_pMonInteract, a5);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pMonInteract, original_pMonInteract, "Comparing pMonInteract");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61E30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61E30, dll_base + 0x00031E30);
		
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
			int32_t a2{};
			int32_t a3{};

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit, a2, a3);
			const auto original_result = original(&original_pUnit, a2, a3);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61EC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61EC0, dll_base + 0x00031EC0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61EE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61EE0, dll_base + 0x00031EE0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61F00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61F00, dll_base + 0x00031F00);
		
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
			sut(&moo_pMonster);
			original(&original_pMonster);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61F20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC61F20, dll_base + 0x00031F20);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pMonster{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pMonster, pUnit };
			};
			
			// Input data
			auto [moo_pMonster, moo_pUnit] = setup_data();
			auto [original_pMonster, original_pUnit] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pMonster, &moo_pUnit);
			const auto original_result = original(&original_pMonster, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC61F70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_MONSTERAI_Last_6FC61F70, dll_base + 0x00031F70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pMonster{};
				
				return std::tuple{ pGame, pMonster };
			};
			
			// Input data
			auto [moo_pGame, moo_pMonster] = setup_data();
			auto [original_pGame, original_pMonster] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pMonster, nullptr);
			original(&original_pGame, &original_pMonster, nullptr);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pMonster, original_pMonster, "Comparing pMonster");
		}
	}
}
