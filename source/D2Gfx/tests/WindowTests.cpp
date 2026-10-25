#include <D2GfxTestDefines.h>

#ifdef WINDOW_TESTS

#include <doctest.h>

#include <Windows.h>

#include <filesystem>
#include <vector>

#include <D2GfxTestDefinitions.h>
#include <TestUtilities.h>

#include <D2Constants.h>
#include <D2Gfx.h>
#include <DisplayType.h>
#include <Window.h>

#include <Fixtures/D2Gfx/D2GfxGlobalsFixture.h>


// Not tested, since they create real windows, change the display settings or hide the taskbar:
// - WINDOW_Create (#10023)
// - WINDOW_Destroy (#10024)
// - WINDOW_ShowCursor (#10029)
// - WINDOW_UpdatePlacement (#10039)
// - WINDOW_ShowAll (#10040)
// WINDOW_GetState (#10026) and WINDOW_EndCutScene (#10033) are only tested without a window.


using GfxFixture = D2GfxGlobalsFixture<NoopFixture>;


// D2GFX_SetPalette passes the palette of each implementation to the graphics interface, so its address is checked and removed before comparing calls
static void normalize_set_palette_calls(std::vector<D2GfxInterfaceCallStrc>& calls, D2GfxGlobals& globals)
{
	for (auto& call : calls)
	{
		if (call.nFunction == D2GFX_INTERFACE_FUNCTION_INDEX(pfSetPalette))
		{
			CHECK_EQ(call.nArgs[0], reinterpret_cast<uintptr_t>(&globals.Palette[0]));
			call.nArgs[0] = 0;
		}
	}
}

static void __cdecl dummy_cutscene_frame()
{
}


TEST_SUITE("WindowTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Gfx.dll").string().c_str()));


	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA748B0 (#10025)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_SetPaused, dll_base + 0x000048B0);

		const auto bPaused = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			// Call both implementations
			sut(bPaused);
			original(bPaused);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA748C0 (#10026)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_GetState, dll_base + 0x000048C0);

		const auto bPaused = GENERATE(0, 1);
		const auto bWindowState = GENERATE(0, 1);

		SUBCASE("")
		{
			// The window is only used when the state changes, a fake one is enough otherwise
			const auto hWnd = bPaused == bWindowState ? reinterpret_cast<HWND>(static_cast<uintptr_t>(random_unsigned_integer(1))) : nullptr;

			const auto setup_data = [bPaused, bWindowState, hWnd](
				D2GfxGlobals& globals
			) {
				globals.bPaused = bPaused;
				globals.bWindowState = bWindowState;
				globals.hWnd = hWnd;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA749C0 (#10027)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_GetWindow, dll_base + 0x000049C0);

		SUBCASE("")
		{
			// The window is only returned, a fake one is enough
			const auto hWnd = reinterpret_cast<HWND>(static_cast<uintptr_t>(random_unsigned_integer()));

			const auto setup_data = [hWnd](
				D2GfxGlobals& globals
			) {
				globals.hWnd = hWnd;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			CHECK_EQ(moo_result, original_result);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA749D0 (#10041)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_GetDimensions, dll_base + 0x000049D0);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same pointers
			int32_t nWidth = 0;
			int32_t nHeight = 0;
			const auto nReturnValue = random_unsigned_integer();

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut(&nWidth, &nHeight);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original(&nWidth, &nHeight);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74A80 (#10028)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_IsFullScreen, dll_base + 0x00004A80);

		const auto bHasGraphicsInterface = GENERATE(0, 1);
		const auto bIsWindowed = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));

		SUBCASE("")
		{
			const auto setup_data = [bHasGraphicsInterface, bIsWindowed](
				D2GfxGlobals& globals
			) {
				if (!bHasGraphicsInterface)
				{
					globals.pGraphicsInterface = nullptr;
				}
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74AA0 (#10043)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_Activate, dll_base + 0x00004AA0);

		const auto bActive = GENERATE(0, 1, static_cast<int32_t>(random_unsigned_integer()));
		const auto bIsWindowed = GENERATE(0, 1);

		SUBCASE("")
		{
			const auto nReturnValue = random_unsigned_integer();

			const auto setup_data = [bIsWindowed](
				D2GfxGlobals& globals
			) {
				globals.bIsWindowed = bIsWindowed;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut(bActive);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original(bActive);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74AE0 (#10030)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_Resize, dll_base + 0x00004AE0);

		// Only the supported resolutions, an unknown resolution is a fatal error that would end the tests
		const auto nResolution = GENERATE(D2GAMERES_640x480, D2GAMERES_800x600);
		const auto nCurrentResolution = GENERATE(D2GAMERES_640x480, D2GAMERES_800x600);
		const auto bForceResize = GENERATE(0, 1);
		const auto bIsWindowed = GENERATE(0, 1);

		SUBCASE("")
		{
			const auto nReturnValue = random_unsigned_integer();

			// No window, it is only resized with SetWindowPos which fails without one
			const auto setup_data = [nCurrentResolution, bIsWindowed](
				D2GfxGlobals& globals
			) {
				globals.nResolutionMode = nCurrentResolution;
				globals.bIsWindowed = bIsWindowed;
				globals.hWnd = nullptr;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations
			D2GraphicsInterfaceMock::return_value = nReturnValue;
			const auto moo_result = sut(nResolution, bForceResize);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			const auto original_result = original(nResolution, bForceResize);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74C60 (#10031)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_ClearCaches, dll_base + 0x00004C60);

		SUBCASE("")
		{
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74C70 (#10032)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_PlayCutscene, dll_base + 0x00004C70);

		SUBCASE("")
		{
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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74CA0 (#10033)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_EndCutScene, dll_base + 0x00004CA0);

		// Only the supported resolutions, an unknown resolution is a fatal error that would end the tests
		const auto nResolution = GENERATE(D2GAMERES_640x480, D2GAMERES_800x600);
		const auto bPaused = GENERATE(0, 1);
		const auto bWindowState = GENERATE(0, 1);
		const auto bIsWindowed = GENERATE(0, 1);

		SUBCASE("")
		{
			// No window, so the window state is never changed
			const auto setup_data = [bPaused, bWindowState, bIsWindowed](
				D2GfxGlobals& globals
			) {
				globals.bPaused = bPaused;
				globals.bWindowState = bWindowState;
				globals.bIsWindowed = bIsWindowed;
				globals.hWnd = nullptr;
				globals.nResolutionMode = D2GAMERES_640x480;
			};

			setup_data(moo_globals);
			setup_data(original_globals);

			// Call both implementations. Failing to resize the window is a fatal error.
			D2GraphicsInterfaceMock::return_value = 1;
			sut(nResolution);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(nResolution);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			normalize_set_palette_calls(moo_calls, moo_globals);
			normalize_set_palette_calls(original_calls, original_globals);

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74DE0 (#10034)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_OpenSmackCutscene, dll_base + 0x00004DE0);

		const auto nResolution = GENERATE(D2GAMERES_640x480, D2GAMERES_800x600);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface
			const char* szFile = "data\\local\\video\\New_Bliz640x480.bik";

			// Call both implementations
			sut(szFile, nResolution, dummy_cutscene_frame);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(szFile, nResolution, dummy_cutscene_frame);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74E20 (#10035)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_CheckCutScene, dll_base + 0x00004E20);

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

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74E50 (#10036)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_DecodeSmacker, dll_base + 0x00004E50);

		REPEAT_5();

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface so both implementations get the same buffer
			const char* szSmacker = "data\\local\\video\\d2intro640x292.bik";
			uint8_t pBuffer[16] = {};
			const int32_t nVersion = random_signed_integer(0, 10);

			// Call both implementations
			sut(szSmacker, pBuffer, nVersion);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(szSmacker, pBuffer, nVersion);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74E90 (#10037)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_PlaySmacker, dll_base + 0x00004E90);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface
			uint8_t pContext[16] = {};

			// Call both implementations
			sut(pContext);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(pContext);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}

	TEST_CASE_FIXTURE(GfxFixture, "D2Gfx.0x6FA74ED0 (#10038)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(WINDOW_CloseSmacker, dll_base + 0x00004ED0);

		SUBCASE("")
		{
			// Input data, only forwarded to the graphics interface
			uint8_t pContext[16] = {};

			// Call both implementations
			sut(pContext);
			auto moo_calls = D2GraphicsInterfaceMock::take_calls();

			original(pContext);
			auto original_calls = D2GraphicsInterfaceMock::take_calls();

			// Compare calls to the graphics interface
			check_calls_eq(moo_calls, original_calls);

			// Compare potentially modified global data
			check_globals_eq("Comparing globals");
		}
	}
}

#endif
