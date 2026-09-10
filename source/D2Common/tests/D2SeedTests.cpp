#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>
#include <tuple>

#include <TestDefinitions.h>
#include <TestUtilities.h>

#include <D2Seed.h>


TEST_SUITE("D2SeedTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Common.dll").string().c_str()));


	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDA5260 (#10916)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SEED_Return, dll_base + 0x00065260);

		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();

			// NOTE: Nothing to test. The function just returns
		}
	}

	// NOTE: may_fail() is used here because the function uses time() and GetTickCount(), which can potentially lead to different results on each call
	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAEA80 (#10920)" * doctest::may_fail())
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SEED_GetRandomValue, dll_base + 0x0006EA80);

		// Repeat the test multiple times with different random values
		[[maybe_unused]] const auto repetition = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

		SUBCASE("")
		{
			int nValue = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(nValue);
			const auto original_result = original(nValue);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAEAB0 (#10912)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SEED_InitSeed, dll_base + 0x0006EAB0);

		SUBCASE("")
		{
			const auto setup_data = []() {
				D2SeedStrc pSeed{};

				return std::tuple{ pSeed };
			};

			// Input data
			auto [moo_pSeed] = setup_data();
			auto [original_pSeed] = setup_data();

			// Call both implementations
			sut(&moo_pSeed);
			original(&original_pSeed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");

			// Check specific values
			CHECK_EQ(moo_pSeed.nLowSeed, 1);
			CHECK_EQ(moo_pSeed.nHighSeed, 666);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAEAC0 (#10913)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SEED_InitLowSeed, dll_base + 0x0006EAC0);

		SUBCASE("")
		{
			const auto setup_data = []() {
				D2SeedStrc pSeed{};

				return std::tuple{ pSeed };
			};

			// Input data
			auto [moo_pSeed] = setup_data();
			auto [original_pSeed] = setup_data();
			int nLowSeed = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSeed, nLowSeed);
			original(&original_pSeed, nLowSeed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");

			// Check specific values
			CHECK_EQ(moo_pSeed.nLowSeed, nLowSeed);
			CHECK_EQ(moo_pSeed.nHighSeed, 666);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAEAD0 (#10914)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SEED_GetLowSeed, dll_base + 0x0006EAD0);

		SUBCASE("")
		{
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			const auto setup_data = [&low_seed, &high_seed]() {
				D2SeedStrc pSeed{ low_seed, high_seed };

				return std::tuple{ pSeed };
			};

			// Input data
			auto [moo_pSeed] = setup_data();
			auto [original_pSeed] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pSeed);
			const auto original_result = original(&original_pSeed);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");

			// Check specific values
			CHECK_EQ(moo_result, low_seed);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAEAE0 (#10921)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SEED_SetSeeds, dll_base + 0x0006EAE0);

		SUBCASE("")
		{
			const auto setup_data = []() {
				D2SeedStrc pSeed{};

				return std::tuple{ pSeed };
			};

			// Input data
			auto [moo_pSeed] = setup_data();
			auto [original_pSeed] = setup_data();
			uint32_t nLowSeed = random_unsigned_integer();
			uint32_t nHighSeed = random_unsigned_integer();

			// Call both implementations
			sut(&moo_pSeed, nLowSeed, nHighSeed);
			original(&original_pSeed, nLowSeed, nHighSeed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");

			// Check specific values
			CHECK_EQ(moo_pSeed.nLowSeed, nLowSeed);
			CHECK_EQ(moo_pSeed.nHighSeed, nHighSeed);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAEAF0 (#10922)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SEED_GetSeeds, dll_base + 0x0006EAF0);

		SUBCASE("")
		{
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			const auto setup_data = [&low_seed, &high_seed]() {
				D2SeedStrc pSeed{ low_seed, high_seed };
				uint32_t pLowSeed{};
				uint32_t pHighSeed{};

				return std::tuple{ pSeed, pLowSeed, pHighSeed };
			};

			// Input data
			auto [moo_pSeed, moo_pLowSeed, moo_pHighSeed] = setup_data();
			auto [original_pSeed, original_pLowSeed, original_pHighSeed] = setup_data();

			// Call both implementations
			sut(&moo_pSeed, &moo_pLowSeed, &moo_pHighSeed);
			original(&original_pSeed, &original_pLowSeed, &original_pHighSeed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");
			MOO_CHECK_EQ(moo_pLowSeed, original_pLowSeed, "Comparing pLowSeed");
			MOO_CHECK_EQ(moo_pHighSeed, original_pHighSeed, "Comparing pHighSeed");

			// Check specific values
			CHECK_EQ(moo_pLowSeed, moo_pSeed.nLowSeed);
			CHECK_EQ(moo_pHighSeed, moo_pSeed.nHighSeed);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Common.0x6FDAEB00 (#10915)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SEED_GetHighSeed, dll_base + 0x0006EB00);

		SUBCASE("")
		{
			const auto low_seed = random_unsigned_integer();
			const auto high_seed = random_unsigned_integer();

			const auto setup_data = [&low_seed, &high_seed]() {
				D2SeedStrc pSeed{ low_seed, high_seed };

				return std::tuple{ pSeed };
			};

			// Input data
			auto [moo_pSeed] = setup_data();
			auto [original_pSeed] = setup_data();

			// Call both implementations
			const auto moo_result = sut(&moo_pSeed);
			const auto original_result = original(&original_pSeed);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pSeed, original_pSeed, "Comparing pSeed");

			// Check specific values
			CHECK_EQ(moo_result, moo_pSeed.nHighSeed);
		}
	}
}
