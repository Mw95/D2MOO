#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2SkillStrc moo_pSkill{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2SkillStrc original_pSkill{};
			int32_t nMode{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2SkillStrc& pSkill
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pSkill);
			setup_data(original_pGame, original_pUnit, original_pSkill);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_a2{};
			D2UnitStrc moo_pTargetUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_a2{};
			D2UnitStrc original_pTargetUnit{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& a2,
				D2UnitStrc& pTargetUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_a2, moo_pTargetUnit);
			setup_data(original_pGame, original_a2, original_pTargetUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc original_pPlayer{};
			int32_t a2{};

			const auto setup_data = [](
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pPlayer);
			setup_data(original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2ActiveRoomStrc moo_pRoom{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2ActiveRoomStrc original_pRoom{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2ActiveRoomStrc& pRoom
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pRoom);
			setup_data(original_pGame, original_pUnit, original_pRoom);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pUnit{};
			int32_t nBodyloc{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pUnit);
			setup_data(original_pGame, original_pItem, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pItem{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pItem{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pItem,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pItem, moo_pPlayer);
			setup_data(original_pGame, original_pItem, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pDeadBody{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pDeadBody{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pDeadBody
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pDeadBody);
			setup_data(original_pGame, original_pPlayer, original_pDeadBody);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pDefender{};
			D2UnitStrc moo_pAttacker{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pDefender{};
			D2UnitStrc original_pAttacker{};
			int32_t a3{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pDefender,
				D2UnitStrc& pAttacker
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pDefender, moo_pAttacker);
			setup_data(original_pGame, original_pDefender, original_pAttacker);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pTarget{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pTarget);
			setup_data(original_pGame, original_pPlayer, original_pTarget);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2UnitStrc moo_pWeapon{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2UnitStrc original_pWeapon{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2UnitStrc& pWeapon
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pWeapon);
			setup_data(original_pGame, original_pPlayer, original_pWeapon);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer);
			setup_data(original_pGame, original_pPlayer);

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
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnkPlrModeStrc2 moo_a2{};
			D2UnitStrc original_pUnit{};
			D2UnkPlrModeStrc2 original_a2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnkPlrModeStrc2& a2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_a2);
			setup_data(original_pUnit, original_a2);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillId{};
			int32_t nSkillLevel{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2ClientStrc moo_pClient{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2ClientStrc original_pClient{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2ClientStrc& pClient
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pClient);
			setup_data(original_pGame, original_pPlayer, original_pClient);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2SkillStrc moo_pUsedSkill{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2SkillStrc original_pUsedSkill{};
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};
			int32_t a7{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2SkillStrc& pUsedSkill
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pUsedSkill);
			setup_data(original_pGame, original_pUnit, original_pUsedSkill);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pPlayer{};
			D2SkillStrc moo_pSkill{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pPlayer{};
			D2SkillStrc original_pSkill{};
			BYTE nMode{};
			int32_t nUnitType{};
			int32_t nTargetGUID{};
			int32_t bAllowReEnter{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pPlayer,
				D2SkillStrc& pSkill
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pPlayer, moo_pSkill);
			setup_data(original_pGame, original_pPlayer, original_pSkill);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

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
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2C_EventTypes nEvent{};
			int32_t dwArg{};
			int32_t dwArgEx{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEvent, dwArg, dwArgEx);
			original(&original_pGame, &original_pUnit, nEvent, dwArg, dwArgEx);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
