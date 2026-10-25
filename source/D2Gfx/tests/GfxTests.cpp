#include <D2GfxTestDefines.h>

#ifdef GFX_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#include <D2GfxTestDefinitions.h>
#include <TestUtilities.h>

#include <D2Gfx.h>
#include <DisplayType.h>
#include <DrawMode.h>

#include <Fixtures/D2Gfx/D2GfxGlobalsFixture.h>
#include <Fixtures/D2Gfx/D2GfxSoftwareRendererFixture.h>


DYNAMIC_ARRAY_TYPE(PALETTEENTRY)


// Not tested:
// - D2GFX_Initialize (#10000) and D2GFX_Release (#10001) register a window class and load the render dlls
// - j_D2GFX_10040_ShowAllWindows (0x6FA73980) only calls WINDOW_ShowAll (#10040), see WindowTests.cpp


using GfxFixture = D2GfxGlobalsFixture<NoopFixture>;


TEST_SUITE("GfxTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Gfx.dll").string().c_str()));


	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73990 (#10002)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_ReturnFalse, dll_base + 0x00003990);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");

			// Check specific values
			CHECK_EQ(moo_result, 0);
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73AC0 (#10003)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_GetDisplayType, dll_base + 0x00003AC0);

		const auto nDisplayType = GENERATE(DISPLAYTYPE_NONE, DISPLAYTYPE_GDI, DISPLAYTYPE_SOFTWARE, DISPLAYTYPE_DDRAW, DISPLAYTYPE_GLIDE, DISPLAYTYPE_OPENGL, DISPLAYTYPE_DIRECT3D, DISPLAYTYPE_RAVE);

		SUBCASE("")
		{
			const auto setup_data = [nDisplayType](
				D2GfxGlobals& globals
			) {
				globals.nDisplayType = nDisplayType;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73AD0 (#10004)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_CheckWindowed, dll_base + 0x00003AD0);

		const auto bIsWindowed = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bIsWindowed](
				D2GfxGlobals& globals
			) {
				globals.bIsWindowed = bIsWindowed;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73AE0 (#10005)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_GetResolutionMode, dll_base + 0x00003AE0);

		const auto nResolutionMode = GENERATE(D2GAMERES_640x480, D2GAMERES_800x600, NUM_GAME_RESOLUTIONS, D2GAMERES_1344x700);

		SUBCASE("")
		{
			const auto setup_data = [nResolutionMode](
				D2GfxGlobals& globals
			) {
				globals.nResolutionMode = nResolutionMode;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73AF0 (#10007)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_CheckUnitPerspective, dll_base + 0x00003AF0);

		const auto bPerspectiveCapable = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bPerspectiveCapable](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.bPerspectiveCapable = bPerspectiveCapable;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73B00 (#10008)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetUnitPerspective, dll_base + 0x00003B00);

		const auto nDisplayType = GENERATE(DISPLAYTYPE_NONE, DISPLAYTYPE_GDI, DISPLAYTYPE_SOFTWARE, DISPLAYTYPE_DDRAW, DISPLAYTYPE_GLIDE, DISPLAYTYPE_OPENGL, DISPLAYTYPE_DIRECT3D, DISPLAYTYPE_RAVE);
		const auto bPerspective = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [nDisplayType](
				D2GfxGlobals& globals
			) {
				globals.nDisplayType = nDisplayType;
				globals.GfxSettings.bPerspectiveCapable = 1;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			sut(bPerspective);
			original(bPerspective);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73B20 (#10047)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_HardwareAcceleratedRenderMode, dll_base + 0x00003B20);

		const auto nDisplayType = GENERATE(DISPLAYTYPE_NONE, DISPLAYTYPE_GDI, DISPLAYTYPE_SOFTWARE, DISPLAYTYPE_DDRAW, DISPLAYTYPE_GLIDE, DISPLAYTYPE_OPENGL, DISPLAYTYPE_DIRECT3D, DISPLAYTYPE_RAVE);

		SUBCASE("")
		{
			const auto setup_data = [nDisplayType](
				D2GfxGlobals& globals
			) {
				globals.nDisplayType = nDisplayType;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73B30 (#10009)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_TogglePerspective, dll_base + 0x00003B30);

		const auto bPerspectiveEnabled = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bPerspectiveEnabled](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.bPerspectiveEnabled = bPerspectiveEnabled;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73B50 (#10010)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_CheckPerspective, dll_base + 0x00003B50);

		const auto bPerspectiveCapable = GENERATE(0, 1);
		const auto bPerspectiveEnabled = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bPerspectiveCapable, bPerspectiveEnabled](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.bPerspectiveCapable = bPerspectiveCapable;
				globals.GfxSettings.bPerspectiveEnabled = bPerspectiveEnabled;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73B70 (#10011)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetPerspective, dll_base + 0x00003B70);

		const auto bPerspective = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			// Call both implementations
			sut(bPerspective);
			original(bPerspective);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73B80 (#10012)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_ToggleBlendedShadows, dll_base + 0x00003B80);

		const auto bBlendedShadows = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bBlendedShadows](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.bBlendedShadows = bBlendedShadows;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73BA0 (#10013)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_CheckBlendedShadows, dll_base + 0x00003BA0);

		const auto bBlendedShadows = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bBlendedShadows](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.bBlendedShadows = bBlendedShadows;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73BB0 (#10014)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetBlendShadows, dll_base + 0x00003BB0);

		const auto bBlendedShadows = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			// Call both implementations
			sut(bBlendedShadows);
			original(bBlendedShadows);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73BC0 (#10015)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_ToggleLowQuality, dll_base + 0x00003BC0);

		const auto bLowQuality = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bLowQuality](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.bLowQuality = bLowQuality;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73BE0 (#10016)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_CheckLowQuality, dll_base + 0x00003BE0);

		const auto bLowQuality = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bLowQuality](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.bLowQuality = bLowQuality;
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73BF0 (#10017)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetLowQuality, dll_base + 0x00003BF0);

		const auto bLowQuality = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			// Call both implementations
			sut(bLowQuality);
			original(bLowQuality);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73C00 (#10018)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetGamma, dll_base + 0x00003C00);

		// 0 keeps the current gamma
		const auto dwGamma = GENERATE(0u, random_unsigned_integer(1, 255));

		SUBCASE("")
		{
			const auto nReturnValue = random_unsigned_integer();
			const int32_t nGamma = random_signed_integer(0, 255);

			const auto setup_data = [nGamma](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.nGamma = nGamma;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut(dwGamma);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original(dwGamma);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73C20 (#10019)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_GammaCanBeControlled, dll_base + 0x00003C20);

		const auto nReturnValue = GENERATE(0u, 1u, random_unsigned_integer());

		SUBCASE("")
		{
			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut();
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original();
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73C30 (#10020)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_EnableVSync, dll_base + 0x00003C30);

		const auto bVSync = GENERATE(0, 1);

		SUBCASE("")
		{
			const auto setup_data = [bVSync](
				D2GfxGlobals& globals
			) {
				globals.GfxSettings.bVSync = bVSync;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			sut();
			original();

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73C40 (#10021)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_GetCacheResults, dll_base + 0x00003C40);

		SUBCASE("")
		{
			const auto nReturnValue = random_unsigned_integer();

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut();
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original();
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			CHECK_EQ(moo_result, original_result);

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73C50 (#10022)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetViewMatrixAdjust, dll_base + 0x00003C50);

		const auto nAdjust = GENERATE(0, 1, 2, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			// Call both implementations
			sut(nAdjust);
			original(nAdjust);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73C60 (#10042)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetOption, dll_base + 0x00003C60);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int32_t nOption = random_signed_integer(0, 20);
			const int32_t nValue = static_cast<int32_t>(random_unsigned_integer());
			const auto nReturnValue = random_unsigned_integer();

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut(nOption, nValue);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original(nOption, nValue);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73C90 (#10044)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_StartDraw, dll_base + 0x00003C90);

		const auto bClear = GENERATE(0, 1);

		SUBCASE("")
		{
			// Input data
			const auto nRed = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			const auto nGreen = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			const auto nBlue = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			const auto nReturnValue = random_unsigned_integer();

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut(bClear, nRed, nGreen, nBlue);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original(bClear, nRed, nGreen, nBlue);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73CB0 (#10045)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_EndScene, dll_base + 0x00003CB0);

		// The results of the graphics interface are ignored
		const auto nReturnValue = GENERATE(0u, 1u);

		SUBCASE("")
		{
			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut();
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original();
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73CD0 (#10046)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_GetBackBuffer, dll_base + 0x00003CD0);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same buffer
			uint8_t pBuffer[16] = {};
			const auto nReturnValue = random_unsigned_integer();

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut(pBuffer);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original(pBuffer);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73CE0 (#10051)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_UtilDiamond, dll_base + 0x00003CE0);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same rect
			RECT pRect = { random_signed_integer(0, 800), random_signed_integer(0, 600), random_signed_integer(0, 800), random_signed_integer(0, 600) };
			const auto nPaletteIndex = static_cast<uint8_t>(random_unsigned_integer(0, 255));

			// Call both implementations
			sut(&pRect, nPaletteIndex);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(&pRect, nPaletteIndex);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73D00 (#10052)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_UtilRect, dll_base + 0x00003D00);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same rect
			RECT pRect = { random_signed_integer(0, 800), random_signed_integer(0, 600), random_signed_integer(0, 800), random_signed_integer(0, 600) };
			const auto nPaletteIndex = static_cast<uint8_t>(random_unsigned_integer(0, 255));

			// Call both implementations
			sut(&pRect, nPaletteIndex);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(&pRect, nPaletteIndex);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73D20 (#10053)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_UtilFilledRect, dll_base + 0x00003D20);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same rect
			RECT pRect = { random_signed_integer(0, 800), random_signed_integer(0, 600), random_signed_integer(0, 800), random_signed_integer(0, 600) };
			const auto nPaletteIndex = static_cast<uint8_t>(random_unsigned_integer(0, 255));

			// Call both implementations
			sut(&pRect, nPaletteIndex);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(&pRect, nPaletteIndex);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73D40 (#10054)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_UtilPoint, dll_base + 0x00003D40);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same point
			POINT pPoint = { random_signed_integer(0, 800), random_signed_integer(0, 600) };
			const auto nSize = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			const auto nPaletteIndex = static_cast<uint8_t>(random_unsigned_integer(0, 255));

			// Call both implementations
			sut(&pPoint, nSize, nPaletteIndex);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(&pPoint, nSize, nPaletteIndex);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73D60 (#10055)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_DrawBox, dll_base + 0x00003D60);

		const auto eDrawMode = GENERATE(DRAWMODE_TRANS25, DRAWMODE_TRANS50, DRAWMODE_TRANS75, DRAWMODE_MODULATE, DRAWMODE_BURN, DRAWMODE_NORMAL, DRAWMODE_TRANSHIGHLIGHT, DRAWMODE_HIGHLIGHT);

		SUBCASE("")
		{
			for (auto i = 0; i < 20; ++i)
			{
				// Input data, the box is not drawn when the end is before the start
				const int32_t nXStart = random_signed_integer(0, 100);
				const int32_t nYStart = random_signed_integer(0, 100);
				const int32_t nXEnd = random_signed_integer(0, 100);
				const int32_t nYEnd = random_signed_integer(0, 100);
				const uint32_t dwColor = random_unsigned_integer();

				// Call both implementations
				sut(nXStart, nYStart, nXEnd, nYEnd, dwColor, eDrawMode);
				auto moo_calls = D2GraphicsInterfaceMock::take_calls();

				original(nXStart, nYStart, nXEnd, nYEnd, dwColor, eDrawMode);
				auto original_calls = D2GraphicsInterfaceMock::take_calls();

				// Compare calls to the graphics interface
				check_calls_eq(moo_calls, original_calls);
			}

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73DA0 (#10056)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_DrawBoxAlpha, dll_base + 0x00003DA0);

		SUBCASE("")
		{
			for (auto i = 0; i < 50; ++i)
			{
				// Input data, the box is not drawn when the end is before the start
				const int32_t nXStart = random_signed_integer(0, 100);
				const int32_t nYStart = random_signed_integer(0, 100);
				const int32_t nXEnd = random_signed_integer(0, 100);
				const int32_t nYEnd = random_signed_integer(0, 100);
				const uint32_t dwColor = random_unsigned_integer();
				const auto nAlpha = static_cast<uint8_t>(random_unsigned_integer(0, 255));

				// Call both implementations
				sut(nXStart, nYStart, nXEnd, nYEnd, dwColor, nAlpha);
				auto moo_calls = D2GraphicsInterfaceMock::take_calls();

				original(nXStart, nYStart, nXEnd, nYEnd, dwColor, nAlpha);
				auto original_calls = D2GraphicsInterfaceMock::take_calls();

				// Compare calls to the graphics interface
				check_calls_eq(moo_calls, original_calls);
			}

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73DE0 (#10057)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_DrawLine, dll_base + 0x00003DE0);

		SUBCASE("")
		{
			for (auto i = 0; i < 50; ++i)
			{
				// Input data
				const int32_t nXStart = random_signed_integer(-100, 900);
				const int32_t nYStart = random_signed_integer(-100, 700);
				const int32_t nXEnd = random_signed_integer(-100, 900);
				const int32_t nYEnd = random_signed_integer(-100, 700);
				const auto nColor = static_cast<uint8_t>(random_unsigned_integer(0, 255));
				const auto nAlpha = static_cast<uint8_t>(random_unsigned_integer(0, 255));

				// Call both implementations
				sut(nXStart, nYStart, nXEnd, nYEnd, nColor, nAlpha);
				auto moo_calls = D2GraphicsInterfaceMock::take_calls();

				original(nXStart, nYStart, nXEnd, nYEnd, nColor, nAlpha);
				auto original_calls = D2GraphicsInterfaceMock::take_calls();

				// Compare calls to the graphics interface
				check_calls_eq(moo_calls, original_calls);
			}

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73E10 (#10058)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_ClearScreen, dll_base + 0x00003E10);

		const auto bPartial = GENERATE(0, 1);

		SUBCASE("")
		{
			// Call both implementations
			sut(bPartial);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(bPartial);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73E30 (#10079)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_FloorTileDraw, dll_base + 0x00003E30);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same tile, light and tile data
			uint8_t pTile[0x60] = {};
			D2GfxLightExStrc pLight[81] = {};
			uint8_t pTileData[16] = {};
			const int32_t nXPos = random_signed_integer(-200, 1000);
			const int32_t nYPos = random_signed_integer(-200, 800);
			const int32_t nWorldXpos = static_cast<int32_t>(random_unsigned_integer());
			const int32_t nWorldYpos = static_cast<int32_t>(random_unsigned_integer());
			const auto nAlpha = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			const int32_t nScreenPanels = random_signed_integer(0, 3);
			const auto nReturnValue = random_unsigned_integer(0, 1);

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut(reinterpret_cast<D2TileLibraryEntryStrc*>(pTile), pLight, nXPos, nYPos, nWorldXpos, nWorldYpos, nAlpha, nScreenPanels, pTileData);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original(reinterpret_cast<D2TileLibraryEntryStrc*>(pTile), pLight, nXPos, nYPos, nWorldXpos, nWorldYpos, nAlpha, nScreenPanels, pTileData);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73E70 (#10048)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetPalette, dll_base + 0x00003E70);

		// nullptr sets the last palette again
		const auto bNullPalette = GENERATE(0, 1);

		SUBCASE("")
		{
			// Input data
			PALETTEENTRY moo_pPalette[256] = {};
			for (auto& entry : moo_pPalette)
			{
				const uint32_t nColor = random_unsigned_integer();
				std::memcpy(&entry, &nColor, sizeof(entry));
			}
			PALETTEENTRY original_pPalette[256] = {};
			std::memcpy(original_pPalette, moo_pPalette, sizeof(original_pPalette));

			// The last palette of both implementations
			PALETTEENTRY pLastPalette[256] = {};
			for (auto& entry : pLastPalette)
			{
				const uint32_t nColor = random_unsigned_integer();
				std::memcpy(&entry, &nColor, sizeof(entry));
			}

			const auto setup_data = [&pLastPalette](
				D2GfxGlobals& globals
			) {
				std::memcpy(globals.Palette, pLastPalette, sizeof(globals.Palette));
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			sut(bNullPalette ? nullptr : moo_pPalette);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(bNullPalette ? nullptr : original_pPalette);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// The palette passed to the graphics interface belongs to each implementation
			REQUIRE_EQ(moo_calls.size(), 1u);
			REQUIRE_EQ(original_calls.size(), 1u);
			CHECK_EQ(moo_calls[0].nArgs[0], reinterpret_cast<uintptr_t>(bNullPalette ? &moo_globals.Palette[0] : &moo_pPalette[0]));
			CHECK_EQ(original_calls[0].nArgs[0], reinterpret_cast<uintptr_t>(bNullPalette ? &original_globals.Palette[0] : &original_pPalette[0]));
			moo_calls[0].nArgs[0] = 0;
			original_calls[0].nArgs[0] = 0;

			// Compare potentially modified input data
			DynamicArray<PALETTEENTRY> moo_pPalette_array{ moo_pPalette, 256 };
			DynamicArray<PALETTEENTRY> original_pPalette_array{ original_pPalette, 256 };
			MOO_CHECK_EQ(moo_pPalette_array, original_pPalette_array, "Comparing pPalette");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(D2GfxSoftwareRendererFixture<GfxFixture>, "D2Gfx.0x6FA73EB0 (#10049)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetPaletteTables, dll_base + 0x00003EB0);

		SUBCASE("")
		{
			// Input data
			D2PaletteTableStrc moo_pPaletteTables = palette_table;
			D2PaletteTableStrc original_pPaletteTables = palette_table;

			const auto setup_data = [](
				D2GfxSoftwareRendererGlobals& renderer
			) {
				renderer.pTransPalettes = nullptr;
				std::memset(renderer.pPaletteTable, 0, sizeof(renderer.pPaletteTable));
				std::memset(renderer.ShadowLightPalettes, 0, sizeof(renderer.ShadowLightPalettes));
			};

			setup_data(moo_renderer);
			setup_data(original_renderer);

			// Call both implementations
			sut(&moo_pPaletteTables);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(&original_pPaletteTables);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// The palette tables passed to the graphics interface are different for both implementations
			REQUIRE_EQ(moo_calls.size(), 1u);
			REQUIRE_EQ(original_calls.size(), 1u);
			CHECK_EQ(moo_calls[0].nArgs[0], reinterpret_cast<uintptr_t>(&moo_pPaletteTables));
			CHECK_EQ(original_calls[0].nArgs[0], reinterpret_cast<uintptr_t>(&original_pPaletteTables));
			moo_calls[0].nArgs[0] = 0;
			original_calls[0].nArgs[0] = 0;

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pPaletteTables, original_pPaletteTables, "Comparing pPaletteTables");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_renderer_eq("Comparing renderer globals");
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73ED0 (#10050)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_SetAmbientColor, dll_base + 0x00003ED0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const auto nRed = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			const auto nGreen = static_cast<uint8_t>(random_unsigned_integer(0, 255));
			const auto nBlue = static_cast<uint8_t>(random_unsigned_integer(0, 255));

			// Call both implementations
			sut(nRed, nGreen, nBlue);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(nRed, nGreen, nBlue);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73EF0 (#10069)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_OutputString, dll_base + 0x00003EF0);

		REPEAT_10();

		SUBCASE("")
		{
			// Input data
			const int32_t nXPos = random_signed_integer(0, 800);
			const int32_t nYPos = random_signed_integer(0, 600);
			const char* szFormat = "%d %s %u %x";
			const int32_t nValue = static_cast<int32_t>(random_unsigned_integer());
			const std::string szString = std::to_string(random_unsigned_integer());
			const uint32_t nUnsignedValue = random_unsigned_integer();
			const uint32_t nHexValue = random_unsigned_integer();

			// Call both implementations
			sut(nXPos, nYPos, szFormat, nValue, szString.c_str(), nUnsignedValue, nHexValue);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();
			auto moo_strings = D2GraphicsInterfaceMock::take_output_strings();

			original(nXPos, nYPos, szFormat, nValue, szString.c_str(), nUnsignedValue, nHexValue);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();
			auto original_strings = D2GraphicsInterfaceMock::take_output_strings();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);
			CHECK_EQ(moo_strings, original_strings);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA73F10 (#10070)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2GFX_DebugDraw, dll_base + 0x00003F10);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same lights
			uint32_t pLight[16] = {};
			uint32_t pPlayerLight[16] = {};
			const int32_t nXPos = random_signed_integer(0, 800);
			const int32_t nYPos = random_signed_integer(0, 600);

			// Call both implementations
			sut(pLight, pPlayerLight, nXPos, nYPos);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(pLight, pPlayerLight, nXPos, nYPos);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}
}

#endif
