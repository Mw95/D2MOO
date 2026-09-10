#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <GAME/Game.h>
#include <UNIT/SUnitEvent.h>
#include <Units/Units.h>


TEST_SUITE("SUnitEventTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3610" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITEVENT_FreeEventList, dll_base + 0x00093610);
		
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3650" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITEVENT_Register, dll_base + 0x00093650);
		
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
			D2C_UnitEventTypes nUnitEvent{};
			int32_t nGUID1{};
			int32_t nGUID2{};
			D2UnitEventCallbackFunction pCallback{};
			uint32_t nQueueNo{};
			int32_t a8{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nUnitEvent, nGUID1, nGUID2, pCallback, nQueueNo, a8);
			const auto original_result = original(&original_pGame, &original_pUnit, nUnitEvent, nGUID1, nGUID2, pCallback, nQueueNo, a8);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC36D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITEVENT_Unregister, dll_base + 0x000936D0);
		
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
			int32_t nTimerQueueNo{};
			int32_t a4{};

			// Call both implementations
			sut(&moo_pGame, &moo_pUnit, nTimerQueueNo, a4);
			original(&original_pGame, &original_pUnit, nTimerQueueNo, a4);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3750" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITEVENT_GetEvent, dll_base + 0x00093750);
		
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
			int32_t nTimerQueueNo{};
			int32_t a4{};
			int32_t nGUID1{};

			// Call both implementations
			const auto moo_result = sut(&moo_pGame, &moo_pUnit, nTimerQueueNo, a4, nGUID1);
			const auto original_result = original(&original_pGame, &original_pUnit, nTimerQueueNo, a4, nGUID1);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCC3790" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SUNITEVENT_Trigger, dll_base + 0x00093790);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2GameStrc pGame{};
				D2UnitStrc pUnit{};
				D2UnitStrc pEventSourceUnit{};
				D2DamageStrc pDamage{};
				
				return std::tuple{ pGame, pUnit, pEventSourceUnit, pDamage };
			};
			
			// Input data
			auto [moo_pGame, moo_pUnit, moo_pEventSourceUnit, moo_pDamage] = setup_data();
			auto [original_pGame, original_pUnit, original_pEventSourceUnit, original_pDamage] = setup_data();
			D2C_UnitEventTypes nUnitEvent{};

			// Call both implementations
			sut(&moo_pGame, nUnitEvent, &moo_pUnit, &moo_pEventSourceUnit, &moo_pDamage);
			original(&original_pGame, nUnitEvent, &original_pUnit, &original_pEventSourceUnit, &original_pDamage);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pEventSourceUnit, original_pEventSourceUnit, "Comparing pEventSourceUnit");
			SKIP_MOO_CHECK_EQ(moo_pDamage, original_pDamage, "Comparing pDamage");
		}
	}
}
