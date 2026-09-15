#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Event.h>
#include <GAME/Game.h>
#include <Units/Units.h>


TEST_SUITE("EventTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34840" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_EVENTS_Delete_6FC34840, dll_base + 0x00004840);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2C_EventTypes nEventType{};
			int32_t nEventCustomId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEventType, nEventCustomId);
			original(&original_pGame, &original_pUnit, nEventType, nEventCustomId);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34890" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC34890, dll_base + 0x00004890);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2EventTimerStrc moo_pTimer{};
			D2GameStrc original_pGame{};
			D2EventTimerStrc original_pTimer{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2EventTimerStrc& pTimer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pTimer);
			setup_data(original_pGame, original_pTimer);

			// Call both implementations
			sut(&moo_pGame, &moo_pTimer);
			original(&original_pGame, &original_pTimer);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC349B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC349B0, dll_base + 0x000049B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nEvent{};
			EventTimerCallback pCallback{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEvent, pCallback);
			original(&original_pGame, &original_pUnit, nEvent, pCallback);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC349F0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC349F0, dll_base + 0x000049F0);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34A30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_DeleteTimersOnUnit_6FC34A30, dll_base + 0x00004A30);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34AE0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_AllocEventQueue, dll_base + 0x00004AE0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34BD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_IterateEvents, dll_base + 0x00004BD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			sut(&moo_pGame);
			original(&original_pGame);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_ExecutePlayerEvents, dll_base + 0x00004CC0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2EventTimerQueueStrc moo_pTimerQueue{};
			D2EventTimerStrc moo_pEventTimer{};
			D2GameStrc original_pGame{};
			D2EventTimerQueueStrc original_pTimerQueue{};
			D2EventTimerStrc original_pEventTimer{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2EventTimerQueueStrc& pTimerQueue,
				D2EventTimerStrc& pEventTimer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pTimerQueue, moo_pEventTimer);
			setup_data(original_pGame, original_pTimerQueue, original_pEventTimer);

			// Call both implementations
			sut(&moo_pGame, &moo_pTimerQueue, &moo_pEventTimer, a4);
			original(&original_pGame, &original_pTimerQueue, &original_pEventTimer, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pTimerQueue, original_pTimerQueue, "Comparing pTimerQueue");
			SKIP_MOO_CHECK_EQ(moo_pEventTimer, original_pEventTimer, "Comparing pEventTimer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34DB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_ExecuteMonsterEvents, dll_base + 0x00004DB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2EventTimerQueueStrc moo_pTimerQueue{};
			D2EventTimerStrc moo_pEventTimer{};
			D2GameStrc original_pGame{};
			D2EventTimerQueueStrc original_pTimerQueue{};
			D2EventTimerStrc original_pEventTimer{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2EventTimerQueueStrc& pTimerQueue,
				D2EventTimerStrc& pEventTimer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pTimerQueue, moo_pEventTimer);
			setup_data(original_pGame, original_pTimerQueue, original_pEventTimer);

			// Call both implementations
			sut(&moo_pGame, &moo_pTimerQueue, &moo_pEventTimer, a4);
			original(&original_pGame, &original_pTimerQueue, &original_pEventTimer, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pTimerQueue, original_pTimerQueue, "Comparing pTimerQueue");
			SKIP_MOO_CHECK_EQ(moo_pEventTimer, original_pEventTimer, "Comparing pEventTimer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34EA0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_ExecuteObjectEvents, dll_base + 0x00004EA0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2EventTimerQueueStrc moo_pTimerQueue{};
			D2EventTimerStrc moo_pEventTimer{};
			D2GameStrc original_pGame{};
			D2EventTimerQueueStrc original_pTimerQueue{};
			D2EventTimerStrc original_pEventTimer{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2EventTimerQueueStrc& pTimerQueue,
				D2EventTimerStrc& pEventTimer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pTimerQueue, moo_pEventTimer);
			setup_data(original_pGame, original_pTimerQueue, original_pEventTimer);

			// Call both implementations
			sut(&moo_pGame, &moo_pTimerQueue, &moo_pEventTimer, a4);
			original(&original_pGame, &original_pTimerQueue, &original_pEventTimer, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pTimerQueue, original_pTimerQueue, "Comparing pTimerQueue");
			SKIP_MOO_CHECK_EQ(moo_pEventTimer, original_pEventTimer, "Comparing pEventTimer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC34F90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_ExecuteMissileEvents, dll_base + 0x00004F90);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2EventTimerQueueStrc moo_pTimerQueue{};
			D2EventTimerStrc moo_pEventTimer{};
			D2GameStrc original_pGame{};
			D2EventTimerQueueStrc original_pTimerQueue{};
			D2EventTimerStrc original_pEventTimer{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2EventTimerQueueStrc& pTimerQueue,
				D2EventTimerStrc& pEventTimer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pTimerQueue, moo_pEventTimer);
			setup_data(original_pGame, original_pTimerQueue, original_pEventTimer);

			// Call both implementations
			sut(&moo_pGame, &moo_pTimerQueue, &moo_pEventTimer, a4);
			original(&original_pGame, &original_pTimerQueue, &original_pEventTimer, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pTimerQueue, original_pTimerQueue, "Comparing pTimerQueue");
			SKIP_MOO_CHECK_EQ(moo_pEventTimer, original_pEventTimer, "Comparing pEventTimer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35080" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_ExecuteItemEvents, dll_base + 0x00005080);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2EventTimerQueueStrc moo_pTimerQueue{};
			D2EventTimerStrc moo_pEventTimer{};
			D2GameStrc original_pGame{};
			D2EventTimerQueueStrc original_pTimerQueue{};
			D2EventTimerStrc original_pEventTimer{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2EventTimerQueueStrc& pTimerQueue,
				D2EventTimerStrc& pEventTimer
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pTimerQueue, moo_pEventTimer);
			setup_data(original_pGame, original_pTimerQueue, original_pEventTimer);

			// Call both implementations
			sut(&moo_pGame, &moo_pTimerQueue, &moo_pEventTimer, a4);
			original(&original_pGame, &original_pTimerQueue, &original_pEventTimer, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pTimerQueue, original_pTimerQueue, "Comparing pTimerQueue");
			SKIP_MOO_CHECK_EQ(moo_pEventTimer, original_pEventTimer, "Comparing pEventTimer");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35170" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_GetEventFrame, dll_base + 0x00005170);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t nEvent{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nEvent);
			const auto original_result = original(&original_pGame, &original_pUnit, nEvent);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC351B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_SetEvent, dll_base + 0x000051B0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2C_EventTypes nEventType{};
			int32_t nExpireFrame{};
			int32_t dwEventCustomId{};
			int32_t dwEventCustomParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEventType, nExpireFrame, dwEventCustomId, dwEventCustomParam);
			original(&original_pGame, &original_pUnit, nEventType, nExpireFrame, dwEventCustomId, dwEventCustomParam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC351D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GAME_InitTimer_6FC351D0, dll_base + 0x000051D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2C_EventTypes nEventType{};
			int32_t nExpireFrame{};
			EventTimerCallback pfCallBack{};
			int32_t dwEventCustomId{};
			int32_t dwEventCustomParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEventType, nExpireFrame, pfCallBack, dwEventCustomId, dwEventCustomParam);
			original(&original_pGame, &original_pUnit, nEventType, nExpireFrame, pfCallBack, dwEventCustomId, dwEventCustomParam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC353D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC353D0, dll_base + 0x000053D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};
			int32_t nUnitType{};
			int32_t nExpireFrame{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, nUnitType, nExpireFrame);
			const auto original_result = original(&original_pGame, nUnitType, nExpireFrame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35410" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_AllocTimerSlab, dll_base + 0x00005410);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2GameStrc original_pGame{};

			const auto setup_data = [](
				D2GameStrc& pGame
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame);
			setup_data(original_pGame);

			// Call both implementations
			const auto moo_result = sut(&moo_pGame);
			const auto original_result = original(&original_pGame);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35460" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(EVENT_AllocateUnitTimer, dll_base + 0x00005460);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC35570" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FC35570, dll_base + 0x00005570);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2C_EventTypes nEventType{};
			int32_t dwEventCustomId{};
			int32_t dwEventCustomParam{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nEventType, dwEventCustomId, dwEventCustomParam);
			original(&original_pGame, &original_pUnit, nEventType, dwEventCustomId, dwEventCustomParam);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FC351D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(j_D2GAME_InitTimer_6FC351D0, dll_base + 0x000051D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2C_EventTypes nEventType{};
			int32_t nExpireFrame{};
			EventTimerCallback pfCallBack{};
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
			sut(&moo_pGame, &moo_pUnit, nEventType, nExpireFrame, pfCallBack, nSkillId, nSkillLevel);
			original(&original_pGame, &original_pUnit, nEventType, nExpireFrame, pfCallBack, nSkillId, nSkillLevel);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
