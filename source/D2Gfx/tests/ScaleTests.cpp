#include <D2GfxTestDefines.h>

#ifdef SCALE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <filesystem>

#include <D2GfxTestDefinitions.h>
#include <TestUtilities.h>

#include <D2Gfx.h>
#include <DisplayType.h>
#include <Scale.h>

#include <Fixtures/D2Gfx/D2GfxGlobalsFixture.h>


extern int32_t gnChangedScaleFactor;


using GfxFixture = D2GfxGlobalsFixture<NoopFixture>;


TEST_SUITE("ScaleTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Gfx.dll").string().c_str()));


	// gnChangedScaleFactor has no known address in the original dll, so it is set with SCALE_DecreaseFactor (#10063) and SCALE_IncreaseFactor (#10062).
	// The factor is 256 + 32 * nSteps, at most 512.
	static void set_changed_scale_factor(int32_t nSteps)
	{
		const auto [moo_decrease, original_decrease] = make_function_pair(SCALE_DecreaseFactor, dll_base + 0x00003FB0);
		const auto [moo_increase, original_increase] = make_function_pair(SCALE_IncreaseFactor, dll_base + 0x00003F80);

		for (auto i = 0; i < 8; ++i)
		{
			moo_decrease();
			original_decrease();
		}

		for (auto i = 0; i < nSteps; ++i)
		{
			moo_increase();
			original_increase();
		}
	}

	// The perspective functions assert that a hardware accelerated render mode is used and that the perspective is enabled
	static void enable_perspective(D2GfxGlobals& globals)
	{
		globals.nDisplayType = DISPLAYTYPE_DIRECT3D;
		globals.GfxSettings.bPerspectiveCapable = 1;
		globals.GfxSettings.bPerspectiveEnabled = 1;
	}


	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73F30 (#10059)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_UpdateFactor, dll_base + 0x00003F30);

		const auto nSteps = GENERATE(0, 1, 4, 8, 9);

		SUBCASE("")
		{
			set_changed_scale_factor(nSteps);

			// Call both implementations
			sut();
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original();
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");

			// Check specific values
			CHECK_EQ(moo_globals.nScaleFactor, gnChangedScaleFactor);
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73F50 (#10060)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_GetFactor, dll_base + 0x00003F50);

		const auto nScaleFactor = GENERATE(256, 512, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [nScaleFactor](
				D2GfxGlobals& globals
			) {
				globals.nScaleFactor = nScaleFactor;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73F60 (#10061)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_SetDefaultFactor, dll_base + 0x00003F60);

		const auto nScaleFactor = GENERATE(256, 512, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [nScaleFactor](
				D2GfxGlobals& globals
			) {
				globals.nScaleFactor = nScaleFactor;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			sut();
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original();
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73F80 (#10062)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_IncreaseFactor, dll_base + 0x00003F80);
		const auto [moo_update, original_update] = make_function_pair(SCALE_UpdateFactor, dll_base + 0x00003F30);

		const auto nSteps = GENERATE(0, 1, 7, 8);

		SUBCASE("")
		{
			set_changed_scale_factor(nSteps);

			// Call both implementations
			sut();
			original();

			// The changed factor is only visible once it is applied
			moo_update();
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original_update();
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73FB0 (#10063)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_DecreaseFactor, dll_base + 0x00003FB0);
		const auto [moo_update, original_update] = make_function_pair(SCALE_UpdateFactor, dll_base + 0x00003F30);

		const auto nSteps = GENERATE(0, 1, 7, 8);

		SUBCASE("")
		{
			set_changed_scale_factor(nSteps);

			// Call both implementations
			sut();
			original();

			// The changed factor is only visible once it is applied
			moo_update();
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original_update();
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73FE0 (#10064)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_SetPerspectiveScale, dll_base + 0x00003FE0);
		const auto [moo_check, original_check] = make_function_pair(SCALE_CheckPerspectivePosition, dll_base + 0x00004060);

		REPEAT_10();

		SUBCASE("")
		{
			enable_perspective(moo_globals);
			enable_perspective(original_globals);

			// Input data
			const int32_t nXScale = random_signed_integer(-0x1000000, 0x1000000);
			const int32_t nYScale = random_signed_integer(-0x1000000, 0x1000000);

			// Call both implementations
			sut(nXScale, nYScale);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(nXScale, nYScale);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");

			// The scale has no known address in the original dll, compare it through SCALE_CheckPerspectivePosition
			for (const int32_t nOffset : { 0, 0x320000, 0x320001, -0x320000, -0x320001 })
			{
				const auto moo_x_result = moo_check(nXScale + nOffset, nYScale);
				const auto original_x_result = original_check(nXScale + nOffset, nYScale);
				MOO_CHECK_EQ(moo_x_result, original_x_result, "Comparing SCALE_CheckPerspectivePosition results");

				const auto moo_y_result = moo_check(nXScale, nYScale + nOffset);
				const auto original_y_result = original_check(nXScale, nYScale + nOffset);
				MOO_CHECK_EQ(moo_y_result, original_y_result, "Comparing SCALE_CheckPerspectivePosition results");
			}
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74060 (#10065)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_CheckPerspectivePosition, dll_base + 0x00004060);
		const auto [moo_set_scale, original_set_scale] = make_function_pair(SCALE_SetPerspectiveScale, dll_base + 0x00003FE0);

		REPEAT_10();

		SUBCASE("")
		{
			enable_perspective(moo_globals);
			enable_perspective(original_globals);

			// The scale has no known address in the original dll, it is set with SCALE_SetPerspectiveScale
			const int32_t nXScale = random_signed_integer(-0x1000000, 0x1000000);
			const int32_t nYScale = random_signed_integer(-0x1000000, 0x1000000);
			moo_set_scale(nXScale, nYScale);
			original_set_scale(nXScale, nYScale);
			D2GraphicsInterfaceMock::take_calls();

			for (auto i = 0; i < 50; ++i)
			{
				// Input data, around the limits of the check
				const int32_t nXPos = nXScale + random_signed_integer(-0x400000, 0x400000);
				const int32_t nYPos = nYScale + random_signed_integer(-0x400000, 0x400000);

				// Call both implementations
				const auto moo_result = sut(nXPos, nYPos);
				const auto original_result = original(nXPos, nYPos);

				// Compare return values
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			}

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74100 (#10066)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_AdjustPerspectivePosition, dll_base + 0x00004100);

		REPEAT_10();

		SUBCASE("")
		{
			enable_perspective(moo_globals);
			enable_perspective(original_globals);

			// Input data, the outputs are only forwarded to the graphics interface so both implementations get the same pointers
			const int32_t nXPos = static_cast<int32_t>(random_unsigned_integer());
			const int32_t nYPos = static_cast<int32_t>(random_unsigned_integer());
			const int32_t nBais = static_cast<int32_t>(random_unsigned_integer());
			int32_t nXAdjust = 0;
			int32_t nYAdjust = 0;

			// Call both implementations
			sut(nXPos, nYPos, nBais, &nXAdjust, &nYAdjust);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(nXPos, nYPos, nBais, &nXAdjust, &nYAdjust);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74170 (#10067)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_ScalePerspectivePosition, dll_base + 0x00004170);

		const auto bOrder = GENERATE(0, 1);

		SUBCASE("")
		{
			enable_perspective(moo_globals);
			enable_perspective(original_globals);

			// Input data, the outputs are only forwarded to the graphics interface so both implementations get the same pointers
			const int32_t nXPos = static_cast<int32_t>(random_unsigned_integer());
			const int32_t nYPos = static_cast<int32_t>(random_unsigned_integer());
			const int32_t nAngle = static_cast<int32_t>(random_unsigned_integer());
			int32_t nXAdjust = 0;
			int32_t nYAdjust = 0;

			// Call both implementations
			sut(nXPos, nYPos, nAngle, &nXAdjust, &nYAdjust, bOrder);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(nXPos, nYPos, nAngle, &nXAdjust, &nYAdjust, bOrder);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74200 (#10068)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCALE_SetDefaultFactorPerspectiveFactor, dll_base + 0x00004200);

		SUBCASE("")
		{
			enable_perspective(moo_globals);
			enable_perspective(original_globals);

			// Call both implementations
			sut();
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original();
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}
}

#endif
