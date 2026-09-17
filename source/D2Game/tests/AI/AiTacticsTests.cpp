#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <AI/AiGeneral.h>
#include <AI/AiTactics.h>
#include <GAME/Game.h>
#include <Units/Units.h>


TEST_SUITE("AiTacticsTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCF9D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCCF9D0, dll_base + 0x0009F9D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiControlStrc moo_pAiControl{};
			int32_t moo_pDistance{};
			int32_t moo_pCombat{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiControlStrc original_pAiControl{};
			int32_t original_pDistance{};
			int32_t original_pCombat{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiControlStrc& pAiControl,
				int32_t& pDistance,
				int32_t& pCombat
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiControl, moo_pDistance, moo_pCombat);
			setup_data(original_pGame, original_pUnit, original_pAiControl, original_pDistance, original_pCombat);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, &moo_pDistance, &moo_pCombat);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiControl, &original_pDistance, &original_pCombat);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
			SKIP_MOO_CHECK_EQ(moo_pDistance, original_pDistance, "Comparing pDistance");
			SKIP_MOO_CHECK_EQ(moo_pCombat, original_pCombat, "Comparing pCombat");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCFC00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCCFC00, dll_base + 0x0009FC00);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiControlStrc moo_pAiControl{};
			int32_t moo_pDistance{};
			int32_t moo_pCombat{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiControlStrc original_pAiControl{};
			int32_t original_pDistance{};
			int32_t original_pCombat{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiControlStrc& pAiControl,
				int32_t& pDistance,
				int32_t& pCombat
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiControl, moo_pDistance, moo_pCombat);
			setup_data(original_pGame, original_pUnit, original_pAiControl, original_pDistance, original_pCombat);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, &moo_pDistance, &moo_pCombat);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiControl, &original_pDistance, &original_pCombat);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
			SKIP_MOO_CHECK_EQ(moo_pDistance, original_pDistance, "Comparing pDistance");
			SKIP_MOO_CHECK_EQ(moo_pCombat, original_pCombat, "Comparing pCombat");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCFD40" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCCFD40, dll_base + 0x0009FD40);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiControlStrc moo_pAiControl{};
			int32_t moo_pDistance{};
			int32_t moo_pCombat{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiControlStrc original_pAiControl{};
			int32_t original_pDistance{};
			int32_t original_pCombat{};
			int32_t nMaxDistance{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiControlStrc& pAiControl,
				int32_t& pDistance,
				int32_t& pCombat
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiControl, moo_pDistance, moo_pCombat);
			setup_data(original_pGame, original_pUnit, original_pAiControl, original_pDistance, original_pCombat);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, &moo_pDistance, &moo_pCombat, nMaxDistance);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiControl, &original_pDistance, &original_pCombat, nMaxDistance);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
			SKIP_MOO_CHECK_EQ(moo_pDistance, original_pDistance, "Comparing pDistance");
			SKIP_MOO_CHECK_EQ(moo_pCombat, original_pCombat, "Comparing pCombat");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCFD70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCCFD70, dll_base + 0x0009FD70);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			int32_t moo_bCloseToTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t original_bCloseToTarget{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				int32_t& bCloseToTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_bCloseToTarget);
			setup_data(original_pGame, original_pUnit, original_bCloseToTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_bCloseToTarget);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_bCloseToTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_bCloseToTarget, original_bCloseToTarget, "Comparing bCloseToTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCFDE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCCFDE0, dll_base + 0x0009FDE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pNPC{};
			D2UnitStrc moo_pPlayer{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pNPC{};
			D2UnitStrc original_pPlayer{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pNPC,
				D2UnitStrc& pPlayer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pNPC, moo_pPlayer);
			setup_data(original_pGame, original_pNPC, original_pPlayer);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pNPC, &moo_pPlayer, moo_pCallbackArg);
			const auto original_result = original(&original_pGame, &original_pNPC, &original_pPlayer, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pNPC, original_pNPC, "Comparing pNPC");
			SKIP_MOO_CHECK_EQ(moo_pPlayer, original_pPlayer, "Comparing pPlayer");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCFEA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_ChangeModeAndTargetUnit, dll_base + 0x0009FEA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTargetUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTargetUnit{};
			int32_t nMode{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTargetUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTargetUnit);
			setup_data(original_pGame, original_pUnit, original_pTargetUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMode, &moo_pTargetUnit);
			const auto original_result = original(&original_pGame, &original_pUnit, nMode, &original_pTargetUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCFEE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_ChangeModeAndTargetCoordinates, dll_base + 0x0009FEE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMode, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nMode, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCFF20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_UseSequenceSkill, dll_base + 0x0009FF20);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTargetUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTargetUnit{};
			int32_t nSkillId{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTargetUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTargetUnit);
			setup_data(original_pGame, original_pUnit, original_pTargetUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nSkillId, &moo_pTargetUnit, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nSkillId, &original_pTargetUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCCFFB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_UseSkill, dll_base + 0x0009FFB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			uint8_t nMode{};
			int32_t nSkillId{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMode, nSkillId, &moo_pTarget, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nMode, nSkillId, &original_pTarget, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD00A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_IdleInNeutralMode, dll_base + 0x000A00A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nFrames{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nFrames);
			original(&original_pGame, &original_pUnit, nFrames);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0110" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_Idle, dll_base + 0x000A0110);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nFrames{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nFrames);
			original(&original_pGame, &original_pUnit, nFrames);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0150" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCD0150, dll_base + 0x000A0150);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nFrames{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nFrames);
			original(&original_pGame, &original_pUnit, nFrames);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD01B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_SetVelocity, dll_base + 0x000A01B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t a2{};
			int32_t nVel{};
			uint8_t a4{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, a2, nVel, a4);
			original(&original_pUnit, a2, nVel, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0220" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkToTargetUnitWithFlags, dll_base + 0x000A0220);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTargetUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTargetUnit{};
			uint8_t nFlag{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTargetUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTargetUnit);
			setup_data(original_pGame, original_pUnit, original_pTargetUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTargetUnit, nFlag);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTargetUnit, nFlag);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTargetUnit, original_pTargetUnit, "Comparing pTargetUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0240" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_MoveToTarget, dll_base + 0x000A0240);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nMode{};
			int32_t nX{};
			int32_t nY{};
			uint8_t bStep{};
			uint8_t nFlags{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nMode, nX, nY, bStep, nFlags);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nMode, nX, nY, bStep, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD03B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkToTargetUnit, dll_base + 0x000A03B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD03D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_RunToTargetUnitWithFlags, dll_base + 0x000A03D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			uint8_t nFlags{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nFlags);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD03F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_RunToTargetUnit, dll_base + 0x000A03F0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCD0410, dll_base + 0x000A0410);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			uint8_t nFlags{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nFlags);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nFlags);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkToTargetCoordinates, dll_base + 0x000A0460);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0480" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_RunToTargetCoordinates, dll_base + 0x000A0480);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD04A0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkToTargetCoordinatesDeleteAiEvent, dll_base + 0x000A04A0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD04C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_RunToTargetCoordinatesDeleteAiEvent, dll_base + 0x000A04C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD04E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkToTargetCoordinatesNoSteps, dll_base + 0x000A04E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0500" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkToTargetUnitWithSteps, dll_base + 0x000A0500);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			uint8_t bStep{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, bStep);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, bStep);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0530" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_RunToTargetUnitWithSteps, dll_base + 0x000A0530);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			uint8_t bStep{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, bStep);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, bStep);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0560" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AICORE_Escape_6FCD0560, dll_base + 0x000A0560);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nMaxDistance{};
			int32_t bDeleteAiEventCallback{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nMaxDistance, bDeleteAiEventCallback);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nMaxDistance, bDeleteAiEventCallback);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD06D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCD06D0, dll_base + 0x000A06D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nMaxDistance{};
			int32_t bDeleteAiEventCallback{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nMaxDistance, bDeleteAiEventCallback);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nMaxDistance, bDeleteAiEventCallback);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkCloseToUnit, dll_base + 0x000A0840);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nMaxDistance{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nMaxDistance);
			const auto original_result = original(&original_pGame, &original_pUnit, nMaxDistance);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD09D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WanderToTarget, dll_base + 0x000A09D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nMaxDistance{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nMaxDistance);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nMaxDistance);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0B60" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_AICORE_WalkToOwner_6FCD0B60, dll_base + 0x000A0B60);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pOwner{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pOwner{};
			int32_t nMaxDistance{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pOwner);
			setup_data(original_pGame, original_pUnit, original_pOwner);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pOwner, nMaxDistance);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pOwner, nMaxDistance);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0D00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_RunCloseToTargetUnit, dll_base + 0x000A0D00);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nMaxDistance{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nMaxDistance);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nMaxDistance);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCD0E80, dll_base + 0x000A0E80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t a4{};
			int32_t bDeleteAiEventCallback{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, a4, bDeleteAiEventCallback);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, a4, bDeleteAiEventCallback);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD0F10" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_AddMessage, dll_base + 0x000A0F10);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pScrollTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pScrollTarget{};
			uint16_t wMessage{};
			int32_t bScrollMessage{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pScrollTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pScrollTarget);
			setup_data(original_pGame, original_pUnit, original_pScrollTarget);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, &moo_pScrollTarget, wMessage, bScrollMessage);
			original(&original_pGame, &original_pUnit, &original_pScrollTarget, wMessage, bScrollMessage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pScrollTarget, original_pScrollTarget, "Comparing pScrollTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1020" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_ChangeModeAndTargetCoordinatesOneStep, dll_base + 0x000A1020);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY, nMode);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1070" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_ChangeModeAndTargetCoordinatesNoStep, dll_base + 0x000A1070);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nX, nY, nMode);
			const auto original_result = original(&original_pGame, &original_pUnit, nX, nY, nMode);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD10C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_MoveInRadiusToTarget, dll_base + 0x000A10C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nMode{};
			int32_t a5{};
			int32_t a6{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nMode, a5, a6);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, nMode, a5, a6);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD12C0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkInRadiusToTarget, dll_base + 0x000A12C0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, a4, a5);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, a4, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD12E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_WalkAroundTargetWithScaledDistance, dll_base + 0x000A12E0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2AiControlStrc moo_pAiControl{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2AiControlStrc original_pAiControl{};
			D2UnitStrc original_pTarget{};
			int32_t nScale{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2AiControlStrc& pAiControl,
				D2UnitStrc& pTarget
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pAiControl, moo_pTarget);
			setup_data(original_pGame, original_pUnit, original_pAiControl, original_pTarget);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, &moo_pTarget, nScale);
			const auto original_result = original(&original_pGame, &original_pUnit, &original_pAiControl, &original_pTarget, nScale);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1430" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_GetTargetMinion, dll_base + 0x000A1430);
		
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
			const auto moo_result = sut(&moo_pGame, &moo_pUnit);
			const auto original_result = original(&original_pGame, &original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCD1490" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AITACTICS_UseSkillInRange, dll_base + 0x000A1490);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nRange{};
			uint16_t wSkillId{};
			uint8_t nMode{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, nRange, wSkillId, nMode);
			original(&original_pUnit, nRange, wSkillId, nMode);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
