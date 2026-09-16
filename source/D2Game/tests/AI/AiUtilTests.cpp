#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <AI/AiGeneral.h>
#include <AI/AiUtil.h>
#include <GAME/Game.h>
#include <Units/Units.h>


TEST_SUITE("AiUtilTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Game.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1210" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_GetDistanceToCoordinates_FullUnitSize, dll_base + 0x000C1210);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pTarget{};
			D2UnitStrc moo_pSource{};
			D2UnitStrc original_pTarget{};
			D2UnitStrc original_pSource{};

			const auto setup_data = [](
				D2UnitStrc& pTarget,
				D2UnitStrc& pSource
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pTarget, moo_pSource);
			setup_data(original_pTarget, original_pSource);

			// Call both implementations
			auto moo_result = sut(&moo_pTarget, &moo_pSource);
			auto original_result = original(&original_pTarget, &original_pSource);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pSource, original_pSource, "Comparing pSource");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1310" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_GetDistanceToCoordinates_HalfUnitSize, dll_base + 0x000C1310);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nX, nY);
			auto original_result = original(&original_pUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF13B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_GetDistanceToCoordinates_NoUnitSize, dll_base + 0x000C13B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nX, nY);
			auto original_result = original(&original_pUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1440" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_GetDistanceToCoordinates, dll_base + 0x000C1440);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nX{};
			int32_t nY{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nX, nY);
			auto original_result = original(&original_pUnit, nX, nY);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF14D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF14D0, dll_base + 0x000C14D0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit1{};
			D2UnitStrc moo_pUnit2{};
			D2UnitStrc original_pUnit1{};
			D2UnitStrc original_pUnit2{};

			const auto setup_data = [](
				D2UnitStrc& pUnit1,
				D2UnitStrc& pUnit2
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit1, moo_pUnit2);
			setup_data(original_pUnit1, original_pUnit2);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit1, &moo_pUnit2);
			auto original_result = original(&original_pUnit1, &original_pUnit2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			SKIP_MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF16D0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF16D0, dll_base + 0x000C16D0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1740" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1740, dll_base + 0x000C1740);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1780" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1780, dll_base + 0x000C1780);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1980" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1980, dll_base + 0x000C1980);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1A50" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1A50, dll_base + 0x000C1A50);
		
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1B30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1B30, dll_base + 0x000C1B30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1BD0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1BD0, dll_base + 0x000C1BD0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1CB0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1CB0, dll_base + 0x000C1CB0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1DC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1DC0, dll_base + 0x000C1DC0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1E30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1E30, dll_base + 0x000C1E30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			void* moo_pCallbackArg = nullptr;
			void* original_pCallbackArg = nullptr;

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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pTarget, moo_pCallbackArg);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pTarget, original_pCallbackArg);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
			SKIP_MOO_CHECK_EQ(moo_pCallbackArg, original_pCallbackArg, "Comparing pCallbackArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF1E80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF1E80, dll_base + 0x000C1E80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_a3 = nullptr;
			void* original_a3 = nullptr;
			int32_t nCallbackId{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_a3, nullptr, nCallbackId);
			auto original_result = original(&original_pGame, &original_pUnit, original_a3, nullptr, nCallbackId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_a3, original_a3, "Comparing a3");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF20E0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF20E0, dll_base + 0x000C20E0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;
			void* moo_ppUnit = nullptr;
			void* original_ppUnit = nullptr;

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, moo_pArg, moo_ppUnit);
			original(&original_pUnit, original_pArg, original_ppUnit);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
			SKIP_MOO_CHECK_EQ(moo_ppUnit, original_ppUnit, "Comparing ppUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2110" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF2110, dll_base + 0x000C2110);
		
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
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pAiControl, &moo_pDistance, &moo_pCombat);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pAiControl, &original_pDistance, &original_pCombat);
			
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
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF27B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF27B0, dll_base + 0x000C27B0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc* moo_ppTarget{};
			int32_t moo_pTargetDistance{};
			D2UnitStrc moo_a4{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc* original_ppTarget{};
			int32_t original_pTargetDistance{};
			D2UnitStrc original_a4{};
			int32_t a5{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc*& ppTarget,
				int32_t& pTargetDistance,
				D2UnitStrc& a4
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_ppTarget, moo_pTargetDistance, moo_a4);
			setup_data(original_pUnit, original_ppTarget, original_pTargetDistance, original_a4);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, &moo_ppTarget, &moo_pTargetDistance, &moo_a4, a5);
			auto original_result = original(&original_pUnit, &original_ppTarget, &original_pTargetDistance, &original_a4, a5);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_ppTarget, original_ppTarget, "Comparing ppTarget");
			SKIP_MOO_CHECK_EQ(moo_pTargetDistance, original_pTargetDistance, "Comparing pTargetDistance");
			SKIP_MOO_CHECK_EQ(moo_a4, original_a4, "Comparing a4");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2920" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF2920, dll_base + 0x000C2920);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc* moo_ppUnit{};
			int32_t moo_pDistance{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc* original_ppUnit{};
			int32_t original_pDistance{};
			int32_t a3{};
			int32_t a4{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				D2UnitStrc*& ppUnit,
				int32_t& pDistance
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_ppUnit, moo_pDistance);
			setup_data(original_pGame, original_pUnit, original_ppUnit, original_pDistance);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, a3, a4, &moo_ppUnit, &moo_pDistance);
			auto original_result = original(&original_pGame, &original_pUnit, a3, a4, &original_ppUnit, &original_pDistance);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_ppUnit, original_ppUnit, "Comparing ppUnit");
			SKIP_MOO_CHECK_EQ(moo_pDistance, original_pDistance, "Comparing pDistance");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2B80" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_FindTargetInAdjacentRooms, dll_base + 0x000C2B80);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pArg, nullptr);
			auto original_result = original(&original_pGame, &original_pUnit, original_pArg, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2C00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_FindTargetInAdjacentActiveRooms, dll_base + 0x000C2C00);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			void* moo_pArg = nullptr;
			void* original_pArg = nullptr;

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit);
			setup_data(original_pGame, original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, moo_pArg, nullptr);
			auto original_result = original(&original_pGame, &original_pUnit, original_pArg, nullptr);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pArg, original_pArg, "Comparing pArg");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2CC0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF2CC0, dll_base + 0x000C2CC0);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			int32_t moo_pDistance{};
			int32_t moo_pInMeleeRange{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			int32_t original_pDistance{};
			int32_t original_pInMeleeRange{};

			const auto setup_data = [](
				D2GameStrc& pGame,
				D2UnitStrc& pUnit,
				int32_t& pDistance,
				int32_t& pInMeleeRange
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pGame, moo_pUnit, moo_pDistance, moo_pInMeleeRange);
			setup_data(original_pGame, original_pUnit, original_pDistance, original_pInMeleeRange);

			// Call both implementations
			auto moo_result = sut(&moo_pGame, &moo_pUnit, &moo_pDistance, &moo_pInMeleeRange);
			auto original_result = original(&original_pGame, &original_pUnit, &original_pDistance, &original_pInMeleeRange);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pDistance, original_pDistance, "Comparing pDistance");
			SKIP_MOO_CHECK_EQ(moo_pInMeleeRange, original_pInMeleeRange, "Comparing pInMeleeRange");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2DF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_CheckAiControlFlag, dll_base + 0x000C2DF0);
		
		SUBCASE("")
		{
			// Input data
			D2AiControlStrc moo_pAiControl{};
			D2AiControlStrc original_pAiControl{};
			uint16_t nFlag{};

			const auto setup_data = [](
				D2AiControlStrc& pAiControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAiControl);
			setup_data(original_pAiControl);

			// Call both implementations
			auto moo_result = sut(&moo_pAiControl, nFlag);
			auto original_result = original(&original_pAiControl, nFlag);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2E00" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_ToggleAiControlFlag, dll_base + 0x000C2E00);
		
		SUBCASE("")
		{
			// Input data
			D2AiControlStrc moo_pAiControl{};
			D2AiControlStrc original_pAiControl{};
			uint16_t nFlag{};
			int32_t bSet{};

			const auto setup_data = [](
				D2AiControlStrc& pAiControl
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pAiControl);
			setup_data(original_pAiControl);

			// Call both implementations
			sut(&moo_pAiControl, nFlag, bSet);
			original(&original_pAiControl, nFlag, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pAiControl, original_pAiControl, "Comparing pAiControl");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2E20" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_ToggleAiControlFlag0x20, dll_base + 0x000C2E20);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t bSet{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			sut(&moo_pUnit, bSet);
			original(&original_pUnit, bSet);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2E70" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(sub_6FCF2E70, dll_base + 0x000C2E70);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit);
			auto original_result = original(&original_pUnit);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2E90" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_CheckIfMonsterUsesSkill, dll_base + 0x000C2E90);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			int32_t nSkillId{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nSkillId);
			auto original_result = original(&original_pUnit, nSkillId);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2EF0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_SetOwnerGUIDAndType, dll_base + 0x000C2EF0);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pOwner{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pOwner{};

			const auto setup_data = [](
				D2UnitStrc& pUnit,
				D2UnitStrc& pOwner
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit, moo_pOwner);
			setup_data(original_pUnit, original_pOwner);

			// Call both implementations
			sut(&moo_pUnit, &moo_pOwner);
			original(&original_pUnit, &original_pOwner);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pOwner, original_pOwner, "Comparing pOwner");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF2F30" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_ApplyTerrorCurseState, dll_base + 0x000C2F30);
		
		SUBCASE("")
		{
			// Input data
			D2GameStrc moo_pGame{};
			D2UnitStrc moo_pUnit{};
			D2UnitStrc moo_pTarget{};
			D2GameStrc original_pGame{};
			D2UnitStrc original_pUnit{};
			D2UnitStrc original_pTarget{};
			int32_t nSkillId{};
			int32_t nParam1{};
			int32_t nDuration{};

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
			sut(&moo_pGame, &moo_pUnit, &moo_pTarget, nSkillId, nParam1, nDuration);
			original(&original_pGame, &original_pUnit, &original_pTarget, nSkillId, nParam1, nDuration);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pGame, original_pGame, "Comparing pGame");
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
			SKIP_MOO_CHECK_EQ(moo_pTarget, original_pTarget, "Comparing pTarget");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Game.0x6FCF3000" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(AIUTIL_CanUnitSwitchAi, dll_base + 0x000C3000);
		
		SUBCASE("")
		{
			// Input data
			D2UnitStrc moo_pUnit{};
			D2UnitStrc original_pUnit{};
			D2C_AiSpecialState nAiSpecialState{};

			const auto setup_data = [](
				D2UnitStrc& pUnit
			) {
				// TODO: Setup as needed
			};

			setup_data(moo_pUnit);
			setup_data(original_pUnit);

			// Call both implementations
			auto moo_result = sut(&moo_pUnit, nAiSpecialState);
			auto original_result = original(&original_pUnit, nAiSpecialState);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
}
