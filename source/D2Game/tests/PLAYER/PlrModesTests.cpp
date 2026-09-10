#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Skills.h>
#include <Drlg/D2DrlgDrlg.h>
#include <GAME/Clients.h>
#include <GAME/Game.h>
#include <PLAYER/PlrModes.h>
#include <Units/Units.h>


TEST_SUITE("PlrModesTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F340" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PLRMODES_First_6FC7F340, dll_base + 0x0004F340);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2SkillStrc pSkill{};
				
				return std::tuple{ pGame, pUnit, pSkill };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pSkill] = setup_data();
			auto [original_pGame, original_pUnit, original_pSkill] = setup_data();
			int32_t nMode{};
			int32_t a4{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMode, a4, &moo_pSkill);
			const auto original_result = original(&original_pGame, &original_pUnit, nMode, a4, &original_pSkill);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F550" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartXY_Neutral, dll_base + 0x0004F550);
		
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
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nMode, nX, nY);
			original(&original_pGame, &original_pPlayer, nMode, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F5A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartID_WalkRunKnockback, dll_base + 0x0004F5A0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc a2{};
				D2UnitStrc pTargetUnit{};
				
				return std::tuple{ pGame, a2, pTargetUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_a2, moo_pTargetUnit] = setup_data();
			auto [original_pGame, original_a2, original_pTargetUnit] = setup_data();
			int32_t a3{};

			// Call both implementations
			sut(&moo_pGame, &moo_a2, a3, &moo_pTargetUnit);
			original(&original_pGame, &original_a2, a3, &original_pTargetUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
			SKIP_MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7F600, dll_base + 0x0004F600);
		
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
			int32_t nMode{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nMode);
			original(&original_pGame, &original_pPlayer, nMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F730" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartXY_WalkRunKnockback, dll_base + 0x0004F730);
		
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
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nMode, nX, nY);
			original(&original_pGame, &original_pPlayer, nMode, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7F780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7F780, dll_base + 0x0004F780);
		
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
			int32_t a3{};
			int32_t a4{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, a3, a4);
			const auto original_result = original(&original_pGame, &original_pPlayer, a3, a4);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7FB70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7FB70, dll_base + 0x0004FB70);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pPlayer };
			};
			
			// Input data
			auto [moo_pPlayer] = setup_data();
			auto [original_pPlayer] = setup_data();
			int32_t a2{};

			// Call both implementations
			sut(&moo_pPlayer, a2);
			original(&original_pPlayer, a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7FB90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7FB90, dll_base + 0x0004FB90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pPlayer };
			};
			
			// Input data
			auto [moo_pPlayer] = setup_data();
			auto [original_pPlayer] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer);
			const auto original_result = original(&original_pPlayer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7FBB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC7FBB0, dll_base + 0x0004FBB0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pPlayer };
			};
			
			// Input data
			auto [moo_pPlayer] = setup_data();
			auto [original_pPlayer] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pPlayer);
			const auto original_result = original(&original_pPlayer);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC7FBD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_CORPSE_Handler_6FC7FBD0, dll_base + 0x0004FBD0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2ActiveRoomStrc pRoom{};
				
				return std::tuple{ pGame, pUnit, pRoom };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pRoom] = setup_data();
			auto [original_pGame, original_pUnit, original_pRoom] = setup_data();
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY, &moo_pRoom);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY, &original_pRoom);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pRoom, original_pRoom, "Comparing pRoom");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC802F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC802F0, dll_base + 0x000502F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2UnitStrc pUnit{};
				
				return std::tuple{ pGame, pItem, pUnit };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pUnit] = setup_data();
			auto [original_pGame, original_pItem, original_pUnit] = setup_data();
			int32_t nBodyloc{};

			// Call both implementations
			sut(&moo_pGame, nBodyloc, &moo_pItem, &moo_pUnit);
			original(&original_pGame, nBodyloc, &original_pItem, &original_pUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC803F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC803F0, dll_base + 0x000503F0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pItem{};
				D2UnitStrc pPlayer{};
				
				return std::tuple{ pGame, pItem, pPlayer };
			};
			
			// Input data
			auto [moo_pGame, moo_pItem, moo_pPlayer] = setup_data();
			auto [original_pGame, original_pItem, original_pPlayer] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pItem, &moo_pPlayer);
			original(&original_pGame, &original_pItem, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pItem, original_pItem, "Comparing pItem");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC80440, dll_base + 0x00050440);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pDeadBody{};
				
				return std::tuple{ pGame, pPlayer, pDeadBody };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pDeadBody] = setup_data();
			auto [original_pGame, original_pPlayer, original_pDeadBody] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pDeadBody);
			original(&original_pGame, &original_pPlayer, &original_pDeadBody);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pDeadBody, original_pDeadBody, "Comparing pDeadBody");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC805B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartID_Death, dll_base + 0x000505B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pDefender{};
				D2UnitStrc pAttacker{};
				
				return std::tuple{ pGame, pDefender, pAttacker };
			};
			
			// Input data
			auto [moo_pGame, moo_pDefender, moo_pAttacker] = setup_data();
			auto [original_pGame, original_pDefender, original_pAttacker] = setup_data();
			int32_t a3{};

			// Call both implementations
			sut(&moo_pGame, &moo_pDefender, a3, &moo_pAttacker);
			original(&original_pGame, &original_pDefender, a3, &original_pAttacker);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pDefender, original_pDefender, "Comparing pDefender");
			SKIP_MOO_CHECK_EQ(moo_pAttacker, original_pAttacker, "Comparing pAttacker");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80710" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartXY_Dead, dll_base + 0x00050710);
		
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
			int32_t a5{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, a3, a4, a5);
			original(&original_pGame, &original_pUnit, a3, a4, a5);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80870" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartXY_Block, dll_base + 0x00050870);
		
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
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nMode, nX, nY);
			original(&original_pGame, &original_pPlayer, nMode, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC808D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC808D0, dll_base + 0x000508D0);
		
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
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pPlayer, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC808E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartXY_GetHit, dll_base + 0x000508E0);
		
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
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nMode, nX, nY);
			original(&original_pGame, &original_pPlayer, nMode, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80940" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartXY_AttackCastThrowKickSpecialSequence, dll_base + 0x00050940);
		
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
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nMode, nX, nY);
			original(&original_pGame, &original_pPlayer, nMode, nX, nY);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC809B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PLRMODE_StartID_AttackCastThrowKickSpecialSequence, dll_base + 0x000509B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pTarget{};
				
				return std::tuple{ pGame, pPlayer, pTarget };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pTarget] = setup_data();
			auto [original_pGame, original_pPlayer, original_pTarget] = setup_data();
			int32_t nMode{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, nMode, &moo_pTarget);
			original(&original_pGame, &original_pPlayer, nMode, &original_pTarget);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80A30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC80A30, dll_base + 0x00050A30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC80B90, dll_base + 0x00050B90);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2UnitStrc pWeapon{};
				
				return std::tuple{ pGame, pPlayer, pWeapon };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pWeapon] = setup_data();
			auto [original_pGame, original_pPlayer, original_pWeapon] = setup_data();

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pWeapon);
			original(&original_pGame, &original_pPlayer, &original_pWeapon);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pWeapon, original_pWeapon, "Comparing pWeapon");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80E10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC80E10, dll_base + 0x00050E10);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer);
			original(&original_pGame, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80EE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC80EE0, dll_base + 0x00050EE0);
		
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
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pPlayer, nSkillId, nSkillLevel);
			const auto original_result = original(&original_pGame, &original_pPlayer, nSkillId, nSkillLevel);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC80F80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EVENTS_StatRegen_6FC80F80, dll_base + 0x00050F80);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81250" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81250, dll_base + 0x00051250);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC814F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC814F0, dll_base + 0x000514F0);
		
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

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer);
			original(&original_pGame, &original_pPlayer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81560" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81560, dll_base + 0x00051560);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit{};
				D2UnkPlrModeStrc2 a2{};
				
				return std::tuple{ pUnit, a2 };
			};
			
			// Input data
			auto [moo_pUnit, moo_a2] = setup_data();
			auto [original_pUnit, original_a2] = setup_data();

			// Call both implementations
			sut(&moo_pUnit, &moo_a2);
			original(&original_pUnit, &original_a2);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a2, original_a2, "Comparing a2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81600" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81600, dll_base + 0x00051600);
		
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
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81650" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81650, dll_base + 0x00051650);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2ClientStrc pClient{};
				
				return std::tuple{ pGame, pPlayer, pClient };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pClient] = setup_data();
			auto [original_pGame, original_pPlayer, original_pClient] = setup_data();
			int32_t a4{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pClient, a4);
			original(&original_pGame, &original_pPlayer, &original_pClient, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pClient, original_pClient, "Comparing pClient");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC817D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC817D0, dll_base + 0x000517D0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2SkillStrc pUsedSkill{};
				
				return std::tuple{ pGame, pUnit, pUsedSkill };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pUsedSkill] = setup_data();
			auto [original_pGame, original_pUnit, original_pUsedSkill] = setup_data();
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};
			int32_t a7{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pUsedSkill, nMode, nX, nY, a7);
			original(&original_pGame, &original_pUnit, &original_pUsedSkill, nMode, nX, nY, a7);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pUsedSkill, original_pUsedSkill, "Comparing pUsedSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81890, dll_base + 0x00051890);
		
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
			int32_t nMode{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMode);
			const auto original_result = original(&original_pGame, &original_pUnit, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81A00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_PLAYERMODE_Change_6FC81A00, dll_base + 0x00051A00);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pPlayer{};
				D2SkillStrc pSkill{};
				
				return std::tuple{ pGame, pPlayer, pSkill };
			};
			
			// Input data
			auto [moo_pGame, moo_pPlayer, moo_pSkill] = setup_data();
			auto [original_pGame, original_pPlayer, original_pSkill] = setup_data();
			BYTE nMode{};
			int32_t nUnitType{};
			int32_t nTargetGUID{};
			int32_t bAllowReEnter{};

			// Call both implementations
			sut(&moo_pGame, &moo_pPlayer, &moo_pSkill, nMode, nUnitType, nTargetGUID, bAllowReEnter);
			original(&original_pGame, &original_pPlayer, &original_pSkill, nMode, nUnitType, nTargetGUID, bAllowReEnter);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pSkill, original_pSkill, "Comparing pSkill");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81B20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81B20, dll_base + 0x00051B20);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81B90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC81B90, dll_base + 0x00051B90);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC81BD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EVENTS_Callback_6FC81BD0, dll_base + 0x00051BD0);
		
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
			D2C_EventTypes nEvent{};
			int32_t dwArg{};
			int32_t dwArgEx{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEvent, dwArg, dwArgEx);
			original(&original_pGame, &original_pUnit, nEvent, dwArg, dwArgEx);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
