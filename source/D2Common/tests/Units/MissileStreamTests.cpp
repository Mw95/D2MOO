#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <Units/MissileStream.h>
#include <Units/Units.h>


TEST_SUITE("MissileStreamTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));

	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC230 (#11213)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_AllocMissileStream, dll_base + 0x0007C230);
		
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

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC280 (#11214)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_FreeMissileStream, dll_base + 0x0007C280);
		
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

			// Call both implementations
			sut(&moo_pMissile);
			original(&original_pMissile);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC2E0 (#11215)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_ExecuteHit, dll_base + 0x0007C2E0);
		
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
			int nCollisionMask{};
			int nCollisionPattern{};

			// Call both implementations
			sut(&moo_pUnit, nCollisionMask, nCollisionPattern, nullptr);
			original(&original_pUnit, nCollisionMask, nCollisionPattern, nullptr);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit, original_pUnit, "Comparing pUnit");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC3B0" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_Return1, dll_base + 0x0007C3B0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc pUnit1{};
				
				return std::tuple{ pUnit1 };
			};
			
			// Input data
			auto [moo_pUnit1] = setup_data();
			auto [original_pUnit1] = setup_data();
			void* moo_pUnit2 = nullptr;
			void* original_pUnit2 = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_pUnit1, moo_pUnit2);
			const auto original_result = original(&original_pUnit1, original_pUnit2);
			
			// Compare return values
			SKIP_MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_pUnit1, original_pUnit1, "Comparing pUnit1");
			SKIP_MOO_CHECK_EQ(moo_pUnit2, original_pUnit2, "Comparing pUnit2");
		}
	}
	
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDBC3C0 (#11216)" * doctest::skip(""))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(MISSTREAM_Update, dll_base + 0x0007C3C0);
		
		SUBCASE("")
		{
			// TODO: Setup as needed
			const auto setup_data = []() {
				D2UnitStrc a1{};
				D2UnitStrc pMissile{};
				
				return std::tuple{ a1, pMissile };
			};
			
			// Input data
			auto [moo_a1, moo_pMissile] = setup_data();
			auto [original_a1, original_pMissile] = setup_data();
			int a3{};
			int a4{};

			// Call both implementations
			sut(&moo_a1, &moo_pMissile, a3, a4, nullptr, nullptr);
			original(&original_a1, &original_pMissile, a3, a4, nullptr, nullptr);

			// Compare potentially modified input data
			SKIP_MOO_CHECK_EQ(moo_a1, original_a1, "Comparing a1");
			SKIP_MOO_CHECK_EQ(moo_pMissile, original_pMissile, "Comparing pMissile");
		}
	}
}
