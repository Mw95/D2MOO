#include <D2WinTestDefines.h>

#ifdef MAIN_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cwchar>
#include <filesystem>
#include <string>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinAnimImage.h>
#include <D2WinButton.h>
#include <D2WinComp.h>
#include <D2WinEditBox.h>
#include <D2WinList.h>
#include <D2WinMain.h>
#include <D2WinPopUp.h>
#include <D2WinProgressBar.h>
#include <D2WinScrollBar.h>
#include <D2WinTextBox.h>
#include <D2WinTimer.h>


// Globals of the D2MOO implementation that are not declared in the D2Win headers
extern WNDPROC gpfWndProc_6F8FE268;
extern HWND ghMainWindow_6F8FE23C;
extern int32_t dword_6F8FE26C;
extern int32_t(*dword_6F8FE27C)();
extern int32_t gnResolution_6F8FE248;
extern int32_t dword_6F8BDF78;
extern int32_t dword_6F8FE280;
extern int32_t dword_6F8FE274;
extern int32_t dword_6F8BDE18;
extern int32_t dword_6F8FE288;
extern void* dword_6F8FE284;
extern int32_t dword_6F8BDE20;
extern int32_t gbWindowed_6F8FE244;
extern int32_t dword_6F8FE228;
extern int32_t dword_6F8FE22C;
extern D2CompositeUnitStrc* gpCompositeUnitList_6F8FD650;


// NOTE: The background and cursor cell files, the current cursor frame and the state of the mouse buttons are stored in global variables
// whose addresses in the original .dll are unknown. They are only modified through the tested functions.
TEST_SUITE("D2WinMainTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Window and input state of both implementations
	struct MainState
	{
		WNDPROC& pfWndProc;
		HWND& hMainWindow;
		int32_t& bWindowCreated;
		int32_t(*&pfOnQuit)();
		int32_t& nResolution;
		int32_t& bRunning;
		int32_t& bQuitRequested;
		int32_t& bControlPressed;
		int32_t& bShowCursor;
		int32_t& bSoundPaused;
		void*& pSoundState;
		int32_t& bAppActive;
		int32_t& bWindowed;
		int32_t& nCursorX;
		int32_t& nCursorY;
		D2CompositeUnitStrc*& pCompositeUnitList;

		struct Values
		{
			WNDPROC pfWndProc;
			HWND hMainWindow;
			int32_t bWindowCreated;
			int32_t(*pfOnQuit)();
			int32_t nResolution;
			int32_t bRunning;
			int32_t bQuitRequested;
			int32_t bControlPressed;
			int32_t bShowCursor;
			int32_t bSoundPaused;
			void* pSoundState;
			int32_t bAppActive;
			int32_t bWindowed;
			int32_t nCursorX;
			int32_t nCursorY;
			D2CompositeUnitStrc* pCompositeUnitList;
		};

		Values save() const
		{
			return { pfWndProc, hMainWindow, bWindowCreated, pfOnQuit, nResolution, bRunning, bQuitRequested, bControlPressed, bShowCursor, bSoundPaused, pSoundState, bAppActive, bWindowed, nCursorX, nCursorY, pCompositeUnitList };
		}

		void restore(const Values& values)
		{
			pfWndProc = values.pfWndProc;
			hMainWindow = values.hMainWindow;
			bWindowCreated = values.bWindowCreated;
			pfOnQuit = values.pfOnQuit;
			nResolution = values.nResolution;
			bRunning = values.bRunning;
			bQuitRequested = values.bQuitRequested;
			bControlPressed = values.bControlPressed;
			bShowCursor = values.bShowCursor;
			bSoundPaused = values.bSoundPaused;
			pSoundState = values.pSoundState;
			bAppActive = values.bAppActive;
			bWindowed = values.bWindowed;
			nCursorX = values.nCursorX;
			nCursorY = values.nCursorY;
			pCompositeUnitList = values.pCompositeUnitList;
		}
	};

	void check_main_states_eq(const MainState& moo, const MainState& original)
	{
		// The window procedure of the window created by the original .dll is its own
		CHECK_EQ(moo.pfWndProc, original.pfWndProc);
		CHECK_EQ(moo.hMainWindow, original.hMainWindow);
		CHECK_EQ(moo.bWindowCreated, original.bWindowCreated);
		CHECK_EQ(moo.pfOnQuit, original.pfOnQuit);
		CHECK_EQ(moo.nResolution, original.nResolution);
		CHECK_EQ(moo.bRunning, original.bRunning);
		CHECK_EQ(moo.bQuitRequested, original.bQuitRequested);
		CHECK_EQ(moo.bControlPressed, original.bControlPressed);
		CHECK_EQ(moo.bShowCursor, original.bShowCursor);
		CHECK_EQ(moo.bSoundPaused, original.bSoundPaused);
		CHECK_EQ(moo.pSoundState, original.pSoundState);
		CHECK_EQ(moo.bAppActive, original.bAppActive);
		CHECK_EQ(moo.bWindowed, original.bWindowed);
		CHECK_EQ(moo.nCursorX, original.nCursorX);
		CHECK_EQ(moo.nCursorY, original.nCursorY);
	}

	const auto original_BACKGROUND_SetCellFile = reinterpret_cast<decltype(&BACKGROUND_SetCellFile)>(dll_base + 0x0000CF30);
	const auto original_CURSOR_SetCellFile = reinterpret_cast<decltype(&CURSOR_SetCellFile)>(dll_base + 0x0000CF50);
	const auto original_POPUP_Destroy = reinterpret_cast<decltype(&POPUP_Destroy)>(dll_base + 0x0000EBA0);
	const auto original_D2Win_COMMANDS_MouseButton = reinterpret_cast<decltype(&D2Win_COMMANDS_MouseButton_6F8AE070)>(dll_base + 0x0000E070);

	struct MainFixture : D2WinFixture<NoopFixture>
	{
		MainState moo_main = { gpfWndProc_6F8FE268, ghMainWindow_6F8FE23C, dword_6F8FE26C, dword_6F8FE27C, gnResolution_6F8FE248, dword_6F8BDF78, dword_6F8FE280, dword_6F8FE274, dword_6F8BDE18, dword_6F8FE288, dword_6F8FE284, dword_6F8BDE20, gbWindowed_6F8FE244, dword_6F8FE228, dword_6F8FE22C, gpCompositeUnitList_6F8FD650 };
		MainState original_main = {
			original_d2win_global<WNDPROC>(0x6F8FE268),
			original_d2win_global<HWND>(0x6F8FE23C),
			original_d2win_global<int32_t>(0x6F8FE26C),
			original_d2win_global<int32_t(*)()>(0x6F8FE27C),
			original_d2win_global<int32_t>(0x6F8FE248),
			original_d2win_global<int32_t>(0x6F8BDF78),
			original_d2win_global<int32_t>(0x6F8FE280),
			original_d2win_global<int32_t>(0x6F8FE274),
			original_d2win_global<int32_t>(0x6F8BDE18),
			original_d2win_global<int32_t>(0x6F8FE288),
			original_d2win_global<void*>(0x6F8FE284),
			original_d2win_global<int32_t>(0x6F8BDE20),
			original_d2win_global<int32_t>(0x6F8FE244),
			original_d2win_global<int32_t>(0x6F8FE228),
			original_d2win_global<int32_t>(0x6F8FE22C),
			original_d2win_global<D2CompositeUnitStrc*>(0x6F8FD650),
		};
		MainState::Values saved_moo_main = moo_main.save();
		MainState::Values saved_original_main = original_main.save();

		MainFixture()
		{
			moo_main.restore({});
			original_main.restore({});
			// The message loop runs while this is set
			moo_main.bRunning = 1;
			original_main.bRunning = 1;

			// No background, cursor or pop up
			BACKGROUND_SetCellFile(nullptr);
			original_BACKGROUND_SetCellFile(nullptr);
			CURSOR_SetCellFile(nullptr);
			original_CURSOR_SetCellFile(nullptr);
			POPUP_Destroy();
			original_POPUP_Destroy();

			// The internal message handlers of both implementations, as registered by D2Win_10015
			const std::pair<void*, uintptr_t> handlers[] =
			{
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_MouseMove_6F8AD670), 0x0000D670 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_MouseButton_6F8AE070), 0x0000E070 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_Char_6F8ADA80), 0x0000DA80 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_VirtualKey_6F8ADB50), 0x0000DB50 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_Escape_6F8ADB10), 0x0000DB10 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_Control_6F8ADBE0), 0x0000DBE0 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_Control_6F8ADBF0), 0x0000DBF0 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_KeyF1_6F8AE020), 0x0000E020 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_ActivateApp_6F8ADC40), 0x0000DC40 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_SysCommand_6F8ADC00), 0x0000DC00 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_Snapshot_6F8ADE70), 0x0000DE70 },
				{ reinterpret_cast<void*>(&D2Win_COMMANDS_MouseWheel_6F8AE220), 0x0000E220 },
			};

			for (const auto& [moo_handler, original_rva] : handlers)
			{
				const std::string name = "handler 0x" + std::to_string(original_rva);
				D2WinCallLog::name_pointer(moo_handler, name);
				D2WinCallLog::name_pointer(reinterpret_cast<void*>(dll_base + original_rva), name);
			}
		}

		~MainFixture()
		{
			BACKGROUND_SetCellFile(nullptr);
			original_BACKGROUND_SetCellFile(nullptr);
			CURSOR_SetCellFile(nullptr);
			original_CURSOR_SetCellFile(nullptr);
			moo_main.restore(saved_moo_main);
			original_main.restore(saved_original_main);
		}

		// Runs a message handler on both implementations and compares the results
		template<typename Function>
		void compare_message_handler(Function* sut, Function* original, SMSGHANDLER_PARAMS& moo_pMsg, SMSGHANDLER_PARAMS& original_pMsg)
		{
			D2WinCallLog::clear();
			sut(&moo_pMsg);
			const auto moo_calls = D2WinCallLog::take();
			original(&original_pMsg);
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);
			MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
			CHECK_EQ(D2WinCallLog::describe(moo_pMsg.hWindow), D2WinCallLog::describe(original_pMsg.hWindow));
			check_main_states_eq(moo_main, original_main);
			CHECK_EQ(moo_state.nRemovedControlsLocked, original_state.nRemovedControlsLocked);
		}
	};

	// Controls of both implementations whose message handlers are the callbacks of the tests.
	// Control 0 is at x = [100, 220], y = [160, 200], control 1 at x = [150, 270], y = [180, 220], control 2 has no handler.
	struct TestControls
	{
		D2WinControlStrc controls[3]{};

		TestControls(const char* szName)
		{
			for (int i = 0; i < 3; ++i)
			{
				d2win_init_control(controls[i], D2WIN_IMAGE, 100 + 50 * i, 200 + 20 * i);
				D2WinCallLog::name_pointer(&controls[i], std::string(szName) + std::to_string(i));
				controls[i].pNext = i < 2 ? &controls[i + 1] : nullptr;
				if (i < 2)
				{
					auto* pfHandler = i == 0 ? D2WinCallbacks::Callback : D2WinCallbacks::Callback2;
					controls[i].pfHandleMouseDown = pfHandler;
					controls[i].pfHandleMouseUp = pfHandler;
					controls[i].pfHandleCharInput = pfHandler;
					controls[i].pfHandleVirtualKeyInput = pfHandler;
				}
			}
		}
	};


	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACC60 (#10000)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_CreateWindow, dll_base + 0x0000CC60);

		SUBCASE("")
		{
			// Input data
			const HINSTANCE hInstance = GetModuleHandleA(nullptr);
			const DisplayType nRenderMode = GENERATE(DISPLAYTYPE_GDI, DISPLAYTYPE_DIRECT3D);
			const BOOL bWindowed = GENERATE(0, 1);
			const BOOL bCompress = GENERATE(0, 1);
			D2WinCallLog::name_pointer(hInstance, "hInstance");

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(hInstance, nRenderMode, bWindowed, bCompress);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(hInstance, nRenderMode, bWindowed, bCompress);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACC90 (#10001)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_InitializeSpriteCache, dll_base + 0x0000CC90);

		SUBCASE("")
		{
			// Input data
			const BOOL bWindowed = GENERATE(0, 1);
			const D2GameResolutionMode nResolution = static_cast<D2GameResolutionMode>(GENERATE(0, 1, 2));
			TestControls moo_controls("moo"), original_controls("original");

			// The state is reset by the function
			for (D2WinControlState* pState : { &moo_state, &original_state })
			{
				pState->pControlList = pState == &moo_state ? moo_controls.controls : original_controls.controls;
				pState->pRemovedControlList = pState->pControlList;
				pState->nRemovedControlsLocked = 3;
				pState->pActiveEditBox = reinterpret_cast<D2WinEditBoxStrc*>(pState->pControlList);
				pState->pFocusedEditBox = reinterpret_cast<D2WinEditBoxStrc*>(pState->pControlList);
				pState->pCancelButton = pState->pControlList;
				pState->pModalControlList = pState->pControlList;
				pState->bDimBackground = 1;
			}

			moo_main.pfWndProc = D2WinCallbacks::WndProc;
			original_main.pfWndProc = D2WinCallbacks::WndProc;
			moo_main.pfOnQuit = D2WinCallbacks::OnQuit;
			original_main.pfOnQuit = D2WinCallbacks::OnQuit;

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(bWindowed, nResolution);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(bWindowed, nResolution);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
			CHECK_EQ(moo_state.pControlList, nullptr);
			CHECK_EQ(original_state.pControlList, nullptr);
			CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList);
			CHECK_EQ(moo_state.nRemovedControlsLocked, original_state.nRemovedControlsLocked);
			CHECK_EQ(moo_state.pActiveEditBox, original_state.pActiveEditBox);
			CHECK_EQ(moo_state.pFocusedEditBox, original_state.pFocusedEditBox);
			CHECK_EQ(moo_state.pCancelButton, original_state.pCancelButton);
			CHECK_EQ(moo_state.pModalControlList, original_state.pModalControlList);
			CHECK_EQ(moo_state.bDimBackground, original_state.bDimBackground);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACD40 (#10014)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10014_SetWndProc, dll_base + 0x0000CD40);

		SUBCASE("")
		{
			// Input data
			const WNDPROC wndProc = GENERATE(D2WinCallbacks::WndProc, nullptr);

			// Call both implementations
			const auto moo_result = sut(wndProc);
			const auto original_result = original(wndProc);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACD60 (#10015)" * doctest::skip("Loads cell files from the MPQ archives"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10015, dll_base + 0x0000CD60);

		SUBCASE("")
		{
			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut();
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original();
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACDB0 (#10002)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_CloseSpriteCache, dll_base + 0x0000CDB0);

		SUBCASE("")
		{
			moo_main.bWindowCreated = 1;
			original_main.bWindowCreated = 1;
			moo_main.hMainWindow = D2WinMock::hWindow;
			original_main.hMainWindow = D2WinMock::hWindow;

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut();
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original();
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACDD0 (#10003)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10003, dll_base + 0x0000CDD0);

		SUBCASE("")
		{
			moo_main.nResolution = 2;
			original_main.nResolution = 2;

			// Call both implementations
			D2WinCallLog::clear();
			sut();
			const auto moo_calls = D2WinCallLog::take();
			original();
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACDE0 (#10004)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10004, dll_base + 0x0000CDE0);

		SUBCASE("")
		{
			// Input data
			const D2GameResolutionMode bForceResize = static_cast<D2GameResolutionMode>(GENERATE(0, 1, 2));

			// Call both implementations
			D2WinCallLog::clear();
			sut(bForceResize);
			const auto moo_calls = D2WinCallLog::take();
			original(bForceResize);
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACE20 (#10016)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10016, dll_base + 0x0000CE20);

		// NOTE: The pentagram cell file is never loaded by the tests
		SUBCASE("")
		{
			// The removed controls and the fonts are freed with Fog.dll, so they are allocated with it
			for (D2WinControlState* pState : { &moo_state, &original_state })
			{
				D2WinControlStrc* pControls[3] = {};
				for (int i = 0; i < 3; ++i)
				{
					pControls[i] = d2win_calloc<D2WinControlStrc>();
					// Removed controls with flag 1 (or flag 2 after them) are kept
					pControls[i]->dwFlags = i == 1 ? 1 : 0;
					if (i > 0)
					{
						pControls[i - 1]->pNext = pControls[i];
					}
				}

				pState->pRemovedControlList = pControls[0];
				pState->nRemovedControlsLocked = 2;
			}

			for (D2WinFontState* pFontState : { &moo_font_state, &original_font_state })
			{
				for (int i = 0; i < NUM_FONTS; ++i)
				{
					pFontState->pFontCaches[i] = {};
					pFontState->pFontCaches[i].pCellFile = static_cast<D2CellFileStrc*>(D2_ALLOC(16));
					D2WinCallLog::name_pointer(pFontState->pFontCaches[i].pCellFile, "font cell file " + std::to_string(i));
				}

				pFontState->pMonsterIndicatorsCellFile = nullptr;
			}

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut();
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original();
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
			CHECK_EQ(moo_state.nRemovedControlsLocked, original_state.nRemovedControlsLocked);
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACEC0 (#10005)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10005, dll_base + 0x0000CEC0);

		SUBCASE("")
		{
			// Input data
			const D2GameResolutionMode nResolution = static_cast<D2GameResolutionMode>(GENERATE(0, 1, 2));

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(nResolution);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(nResolution);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACF20 (#10006)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10006_ClearDrawCaches, dll_base + 0x0000CF20);

		SUBCASE("")
		{
			// Call both implementations
			D2WinCallLog::clear();
			sut();
			const auto moo_calls = D2WinCallLog::take();
			original();
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACF30 (#10007)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BACKGROUND_SetCellFile, dll_base + 0x0000CF30);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("background", 12);

			// Call both implementations
			const auto moo_result = sut(cellFile.get());
			const auto original_result = original(cellFile.get());

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// The background is drawn by D2Win_10019
			D2WinCallLog::clear();
			D2Win_10019();
			const auto moo_calls = D2WinCallLog::take();
			original_d2win_function<decltype(D2Win_10019)>(0x6F8AD6F0)();
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACF50 (#10011)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CURSOR_SetCellFile, dll_base + 0x0000CF50);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("cursor", 8);
			moo_main.bShowCursor = 1;
			original_main.bShowCursor = 1;
			set_mouse_position(30, 40);

			// Call both implementations
			const auto moo_result = sut(cellFile.get());
			const auto original_result = original(cellFile.get());

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// The cursor is drawn by D2Win_10019
			D2WinCallLog::clear();
			D2Win_10019();
			const auto moo_calls = D2WinCallLog::take();
			original_d2win_function<decltype(D2Win_10019)>(0x6F8AD6F0)();
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACF70 (#10010)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10010, dll_base + 0x0000CF70);

		SUBCASE("")
		{
			// Input data
			int(*pfOnQuit)() = GENERATE(D2WinCallbacks::OnQuit, nullptr);

			// Call both implementations
			sut(pfOnQuit);
			original(pfOnQuit);

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACF80 (#10009)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10009, dll_base + 0x0000CF80);

		SUBCASE("")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
			CHECK_EQ(moo_main.bRunning, 0);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ACF90 (#10008)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10008, dll_base + 0x0000CF90);

		// NOTE: Only the end of the message loop is tested, the loop itself waits for messages of the window
		SUBCASE("")
		{
			// Input data
			const int32_t bQuitRequested = GENERATE(0, 1);
			const int32_t nWindowState = GENERATE(0, 1);
			moo_main.bRunning = 0;
			original_main.bRunning = 0;
			moo_main.bQuitRequested = bQuitRequested;
			original_main.bQuitRequested = bQuitRequested;
			D2WinMock::nWindowState = nWindowState;

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(D2WinCallbacks::LoopCallback);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(D2WinCallbacks::LoopCallback);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD0B0 (#10013)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_SetCellFile, dll_base + 0x0000D0B0);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("cellfile", 1);
			D2CellFileStrc* pCellFile = GENERATE(true, false) ? cellFile.get() : nullptr;
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			d2win_init_control(moo_pControl, D2WIN_IMAGE);
			d2win_init_control(original_pControl, D2WIN_IMAGE);

			// Call both implementations
			const auto moo_result = sut(&moo_pControl, pCellFile);
			const auto original_result = original(&original_pControl, pCellFile);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD0D0 (#10012)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10012, dll_base + 0x0000D0D0);

		// Input data
		// 0: no focused edit box, 1: the edit box is focused, 2: another edit box is focused
		const int nState = GENERATE(0, 1, 2);
		const bool bNull = GENERATE(false, true);
		CAPTURE(nState);
		CAPTURE(bNull);

		D2WinEditBoxStrc moo_pEditBoxes[2]{};
		D2WinEditBoxStrc original_pEditBoxes[2]{};
		for (D2WinEditBoxStrc* pEditBoxes : { moo_pEditBoxes, original_pEditBoxes })
		{
			for (int i = 0; i < 2; ++i)
			{
				d2win_init_control(pEditBoxes[i].controlHeader, D2WIN_EDITBOX);
				pEditBoxes[i].nSelectionStart = 1;
				pEditBoxes[i].nSelectionEnd = 3;
			}
		}

		if (nState)
		{
			moo_state.pFocusedEditBox = &moo_pEditBoxes[nState - 1];
			original_state.pFocusedEditBox = &original_pEditBoxes[nState - 1];
		}

		// Call both implementations
		const auto moo_result = sut(bNull ? nullptr : &moo_pEditBoxes[0]);
		const auto original_result = original(bNull ? nullptr : &original_pEditBoxes[0]);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		for (int i = 0; i < 2; ++i)
		{
			MOO_CHECK_EQ(moo_pEditBoxes[i], original_pEditBoxes[i], "Comparing edit boxes");
		}

		CHECK_EQ(moo_state.pFocusedEditBox == &moo_pEditBoxes[0], original_state.pFocusedEditBox == &original_pEditBoxes[0]);
		CHECK_EQ(moo_state.pFocusedEditBox == nullptr, original_state.pFocusedEditBox == nullptr);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD110 (#10023)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10023, dll_base + 0x0000D110);

		SUBCASE("")
		{
			// Input data
			D2WinEditBoxStrc editBox{};
			D2WinEditBoxStrc* pActiveEditBox = GENERATE(true, false) ? &editBox : nullptr;
			moo_state.pActiveEditBox = pActiveEditBox;
			original_state.pActiveEditBox = pActiveEditBox;

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			CHECK_EQ(moo_result, original_result);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD120")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_AppendToList, dll_base + 0x0000D120);

		SUBCASE("")
		{
			// Input data
			const int nExistingControls = GENERATE(0, 1, 3);
			D2WinControlStrc moo_pControls[4]{};
			D2WinControlStrc original_pControls[4]{};
			for (int i = 0; i < 4; ++i)
			{
				d2win_init_control(moo_pControls[i], D2WIN_IMAGE, i, i, i, i);
				d2win_init_control(original_pControls[i], D2WIN_IMAGE, i, i, i, i);
			}

			for (int i = 0; i < nExistingControls; ++i)
			{
				CONTROL_AppendToList(&moo_pControls[i]);
				CONTROL_AppendToList(&original_pControls[i]);
			}

			// Call both implementations
			const auto moo_result = sut(&moo_pControls[3]);
			const auto original_result = original(&original_pControls[3]);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD160")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_RemoveFromList, dll_base + 0x0000D160);

		// Input data
		const int nIndex = GENERATE(0, 1, 2, 3);
		const bool bReferenced = GENERATE(false, true);
		const bool bExistingRemovedControl = GENERATE(false, true);
		CAPTURE(nIndex);
		CAPTURE(bReferenced);
		CAPTURE(bExistingRemovedControl);

		D2WinControlStrc moo_pControls[5]{};
		D2WinControlStrc original_pControls[5]{};
		for (D2WinControlStrc* pControls : { moo_pControls, original_pControls })
		{
			for (int i = 0; i < 5; ++i)
			{
				d2win_init_control(pControls[i], D2WIN_IMAGE, i, i, i, i);
			}

			pControls[0].pNext = &pControls[1];
			pControls[1].pNext = &pControls[2];
		}

		for (D2WinControlState* pState : { &moo_state, &original_state })
		{
			D2WinControlStrc* pControls = pState == &moo_state ? moo_pControls : original_pControls;
			pState->pControlList = &pControls[0];
			pState->pRemovedControlList = bExistingRemovedControl ? &pControls[4] : nullptr;
			// The global references to the removed control are reset
			if (bReferenced)
			{
				pState->pActiveEditBox = reinterpret_cast<D2WinEditBoxStrc*>(&pControls[nIndex]);
				pState->pFocusedEditBox = reinterpret_cast<D2WinEditBoxStrc*>(&pControls[nIndex]);
				pState->pModalControlList = &pControls[nIndex];
				pState->bDimBackground = 1;
				pState->pCancelButton = &pControls[nIndex];
			}
		}

		// Call both implementations
		const auto moo_result = sut(&moo_pControls[nIndex]);
		const auto original_result = original(&original_pControls[nIndex]);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
		MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		CHECK_EQ(moo_state.pActiveEditBox == nullptr, original_state.pActiveEditBox == nullptr);
		CHECK_EQ(moo_state.pFocusedEditBox == nullptr, original_state.pFocusedEditBox == nullptr);
		CHECK_EQ(moo_state.pModalControlList == nullptr, original_state.pModalControlList == nullptr);
		CHECK_EQ(moo_state.bDimBackground, original_state.bDimBackground);
		CHECK_EQ(moo_state.pCancelButton == nullptr, original_state.pCancelButton == nullptr);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD260 (#10017)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_Create, dll_base + 0x0000D260);

		// Input data
		const int nType = GENERATE(0, D2WIN_EDITBOX, D2WIN_IMAGE, D2WIN_ANIMIMAGE, D2WIN_TEXTBOX, D2WIN_SCROLLBAR, D2WIN_BUTTON, D2WIN_LIST, D2WIN_TIMER, D2WIN_SMACK, D2WIN_PROGRESSBAR, D2WIN_POPUP, D2WIN_ACCOUNTLIST, D2WIN_IMAGE2, 14);
		CAPTURE(nType);

		D2WinFakeCellFile cellFile("cellfile", 4);
		D2CellFileStrc* pCellFile = cellFile.get();
		D2WinEditBoxFontStrc font = { D2FONT_FONT16, 1 };
		D2WinListItemInitStrc listItems[] = { { 'A', 'a', {}, 'A', D2WinCallbacks::Callback2 }, {} };

		D2WinControlInitStrc controlInit{};
		controlInit.nType = nType;
		controlInit.nX = 100;
		controlInit.nY = 200;
		controlInit.nWidth = 120;
		controlInit.nHeight = 40;
		controlInit.nParam = 5;
		controlInit.nStringId = nType == D2WIN_BUTTON ? 1234 : 3;
		controlInit.ppCellFile = &pCellFile;
		controlInit.pfCallback = D2WinCallbacks::Callback;
		switch (nType)
		{
		case D2WIN_EDITBOX:
			controlInit.pParam1 = reinterpret_cast<void*>(D2WinCallbacks::OnReturn);
			controlInit.pParam2 = &font;
			break;

		case D2WIN_TEXTBOX:
		case D2WIN_ACCOUNTLIST:
			controlInit.pParam2 = &font;
			controlInit.pParam3 = reinterpret_cast<void*>(5);
			break;

		case D2WIN_LIST:
			controlInit.pParam1 = listItems;
			controlInit.pParam2 = &font.eFont;
			break;

		case D2WIN_BUTTON:
			controlInit.pParam1 = reinterpret_cast<void*>(2);
			controlInit.pParam2 = reinterpret_cast<void*>(D2WinCallbacks::Callback2);
			controlInit.pParam3 = reinterpret_cast<void*>(4);
			break;

		default:
			break;
		}

		// Call both implementations
		D2WinControlStrc* moo_result = sut(&controlInit);
		D2WinControlStrc* original_result = original(&controlInit);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
		CHECK_EQ(moo_result == nullptr ? -1 : moo_result->nType, original_result == nullptr ? -1 : original_result->nType);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD450 (#10018)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_Destroy, dll_base + 0x0000D450);

		// Input data
		const int nType = GENERATE(D2WIN_EDITBOX, D2WIN_IMAGE, D2WIN_ANIMIMAGE, D2WIN_TEXTBOX, D2WIN_SCROLLBAR, D2WIN_BUTTON, D2WIN_LIST, D2WIN_TIMER, D2WIN_SMACK, D2WIN_PROGRESSBAR, D2WIN_ACCOUNTLIST, D2WIN_IMAGE2);
		CAPTURE(nType);

		D2WinFakeCellFile cellFile("cellfile", 4);
		D2CellFileStrc* pCellFile = cellFile.get();
		D2WinEditBoxFontStrc font = { D2FONT_FONT16, 1 };
		D2WinListItemInitStrc listItems[] = { { 'A', 'a', {}, 'A', D2WinCallbacks::Callback2 }, {} };

		D2WinControlInitStrc controlInit{};
		controlInit.nType = nType;
		controlInit.nX = 100;
		controlInit.nY = 200;
		controlInit.nWidth = 120;
		controlInit.nHeight = 40;
		controlInit.ppCellFile = &pCellFile;
		if (nType == D2WIN_LIST)
		{
			controlInit.pParam1 = listItems;
			controlInit.pParam2 = &font.eFont;
		}

		// The controls are created by the respective implementation
		D2WinControlStrc* moo_pControl = CONTROL_Create(&controlInit);
		D2WinControlStrc* original_pControl = original_d2win_function<decltype(CONTROL_Create)>(0x6F8AD260)(&controlInit);
		REQUIRE(moo_pControl != nullptr);
		REQUIRE(original_pControl != nullptr);
		if (nType == D2WIN_SMACK)
		{
			strcpy_s(reinterpret_cast<D2WinSmackStrc*>(moo_pControl)->szFileName, "D2WinTests_NonExistentVideo.smk");
			strcpy_s(reinterpret_cast<D2WinSmackStrc*>(original_pControl)->szFileName, "D2WinTests_NonExistentVideo.smk");
		}

		D2WinControlStrc* moo_ppControl = moo_pControl;
		D2WinControlStrc* original_ppControl = original_pControl;

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_ppControl);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_ppControl);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		CHECK_EQ(moo_ppControl, nullptr);
		CHECK_EQ(original_ppControl, nullptr);
		CHECK_EQ(moo_state.pControlList == nullptr, original_state.pControlList == nullptr);
		CHECK_EQ(moo_state.pRemovedControlList == moo_pControl, original_state.pRemovedControlList == original_pControl);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD450 (#10018) - Null and unknown controls")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_Destroy, dll_base + 0x0000D450);

		SUBCASE("Null pointer")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}

		SUBCASE("Null control")
		{
			D2WinControlStrc* moo_ppControl = nullptr;
			D2WinControlStrc* original_ppControl = nullptr;

			// Call both implementations
			const auto moo_result = sut(&moo_ppControl);
			const auto original_result = original(&original_ppControl);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}

		SUBCASE("Unknown control type")
		{
			const int nType = GENERATE(0, D2WIN_POPUP, 14);
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			d2win_init_control(moo_pControl, nType);
			d2win_init_control(original_pControl, nType);
			D2WinControlStrc* moo_ppControl = &moo_pControl;
			D2WinControlStrc* original_ppControl = &original_pControl;

			// Call both implementations
			const auto moo_result = sut(&moo_ppControl);
			const auto original_result = original(&original_ppControl);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			CHECK_EQ(moo_ppControl, original_ppControl);
			MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD570 (#10025)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10025_CONTROL_ToggleFirstFlag, dll_base + 0x0000D570);

		SUBCASE("")
		{
			// Input data
			const uint32_t dwFlags = GENERATE(0u, 1u, 0xFFFFFFFFu);
			const int bSet = GENERATE(0, 1, 7);
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			moo_pControl.dwFlags = dwFlags;
			original_pControl.dwFlags = dwFlags;

			// Call both implementations
			sut(&moo_pControl, bSet);
			original(&original_pControl, bSet);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}

		SUBCASE("Null control")
		{
			// Call both implementations
			sut(nullptr, 1);
			original(nullptr, 1);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD5A0 (#10024)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10024_CONTROL_CheckFirstFlag, dll_base + 0x0000D5A0);

		SUBCASE("")
		{
			// Input data
			const uint32_t dwFlags = GENERATE(0u, 1u, 2u, 0xFFFFFFFFu);
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			moo_pControl.dwFlags = dwFlags;
			original_pControl.dwFlags = dwFlags;

			// Call both implementations
			const auto moo_result = sut(&moo_pControl);
			const auto original_result = original(&original_pControl);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD5D0 (#10027)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10027_CONTROL_ToggleThirdFlag, dll_base + 0x0000D5D0);

		SUBCASE("")
		{
			// Input data
			const uint32_t dwFlags = GENERATE(0u, 4u, 0xFFFFFFFFu);
			const int bSet = GENERATE(0, 1, 7);
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			moo_pControl.dwFlags = dwFlags;
			original_pControl.dwFlags = dwFlags;

			// Call both implementations
			sut(&moo_pControl, bSet);
			original(&original_pControl, bSet);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AD620 (#10026)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10026_CONTROL_CheckThirdFlag, dll_base + 0x0000D620);

		SUBCASE("")
		{
			// Input data
			const uint32_t dwFlags = GENERATE(0u, 4u, 3u, 0xFFFFFFFFu);
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			moo_pControl.dwFlags = dwFlags;
			original_pControl.dwFlags = dwFlags;

			// Call both implementations
			const auto moo_result = sut(&moo_pControl);
			const auto original_result = original(&original_pControl);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD650 (#10170)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_MouseInsideRect, dll_base + 0x0000D650);

		// Input data
		const int32_t nMouseX = GENERATE(99, 100, 150, 200, 201);
		const int32_t nMouseY = GENERATE(49, 50, 75, 100, 101);
		CAPTURE(nMouseX);
		CAPTURE(nMouseY);

		const RECT rect = { 100, 50, 200, 100 };
		set_mouse_position(nMouseX, nMouseY);

		// Call both implementations
		const auto moo_result = sut(&rect);
		const auto original_result = original(&rect);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD670")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_MouseMove_6F8AD670, dll_base + 0x0000D670);

		// Input data
		// NOTE: With hardware acceleration, the cursor of the system is moved when the mouse leaves the window, which is not tested
		const int32_t bHardwareAccelerated = GENERATE(0, 1);
		const int nX = GENERATE(0, 100, 799);
		const int nY = GENERATE(0, 300, 599);
		const bool bOutside = GENERATE(false, true);
		CAPTURE(bHardwareAccelerated);
		CAPTURE(nX);
		CAPTURE(nY);
		CAPTURE(bOutside);

		if (bHardwareAccelerated && bOutside)
		{
			return;
		}

		D2WinMock::bHardwareAccelerated = bHardwareAccelerated;
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		for (SMSGHANDLER_PARAMS* pMsg : { &moo_pMsg, &original_pMsg })
		{
			pMsg->nMessage = WM_MOUSEMOVE;
			pMsg->lParam = MAKELPARAM(nX + (bOutside ? 1000 : 0), nY + (bOutside ? 0xF000 : 0));
		}

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
		CHECK_EQ(moo_state.mousePosition.x, original_state.mousePosition.x);
		CHECK_EQ(moo_state.mousePosition.y, original_state.mousePosition.y);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD6F0 (#10019)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10019, dll_base + 0x0000D6F0);

		// Input data
		const int32_t nWindowState = GENERATE(0, 1);
		const bool bWndProc = GENERATE(false, true);
		const int32_t bStartDrawResult = GENERATE(1, 0);
		const int32_t bDimBackground = GENERATE(0, 1);
		const int32_t nRemovedControlsLocked = GENERATE(0, 1);
		CAPTURE(nWindowState);
		CAPTURE(bWndProc);
		CAPTURE(bStartDrawResult);
		CAPTURE(bDimBackground);
		CAPTURE(nRemovedControlsLocked);

		D2WinMock::nWindowState = nWindowState;
		D2WinMock::bStartDrawResult = bStartDrawResult;

		// Progress bars drawn by the respective implementation, the last one in the foreground (flag 8).
		// The timer is initialized by the respective implementation, its timeout elapsed.
		D2WinProgressBarStrc moo_pProgressBars[2]{};
		D2WinProgressBarStrc original_pProgressBars[2]{};
		D2WinTimerStrc moo_pTimer{};
		D2WinTimerStrc original_pTimer{};
		for (const bool bOriginal : { false, true })
		{
			D2WinProgressBarStrc* pProgressBars = bOriginal ? original_pProgressBars : moo_pProgressBars;
			D2WinTimerStrc& pTimer = bOriginal ? original_pTimer : moo_pTimer;
			for (int i = 0; i < 2; ++i)
			{
				d2win_init_control(pProgressBars[i].controlHeader, D2WIN_PROGRESSBAR, 10 + i, 20 + i, 100, 10);
				pProgressBars[i].fProgress = 0.5f;
				pProgressBars[i].controlHeader.pfDraw = bOriginal ? original_d2win_function<int32_t __fastcall(D2WinControlStrc*)>(0x6F8AEFB0) : PROGRESSBAR_Draw;
			}

			pProgressBars[1].controlHeader.dwFlags |= 8;
			d2win_init_control(pTimer.controlHeader, D2WIN_TIMER);
			pTimer.controlHeader.pfInitialize = bOriginal ? original_d2win_function<int32_t __fastcall(D2WinControlStrc*)>(0x6F8B1C60) : TIMER_UpdateTimeout;
			pTimer.controlHeader.pfCallback = D2WinCallbacks::Callback;
			pTimer.dwTickCount = GetTickCount() - 10000;
			pTimer.nTimeout = 1;
			D2WinCallLog::name_pointer(&pTimer, "pTimer");

			pProgressBars[1].controlHeader.pNext = &pTimer.controlHeader;
			pTimer.controlHeader.pNext = &pProgressBars[0].controlHeader;

			D2WinControlState& state = bOriginal ? original_state : moo_state;
			state.pControlList = &pProgressBars[1].controlHeader;
			state.bDimBackground = bDimBackground;
			state.nRemovedControlsLocked = nRemovedControlsLocked;
		}

		if (bWndProc)
		{
			moo_main.pfWndProc = D2WinCallbacks::WndProc;
			original_main.pfWndProc = D2WinCallbacks::WndProc;
		}

		// Call both implementations
		D2WinCallLog::clear();
		sut();
		const auto moo_calls = D2WinCallLog::take();
		original();
		const auto original_calls = D2WinCallLog::take();

		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
		check_main_states_eq(moo_main, original_main);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AD9B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_MAINWINDOW_WndProc_6F8AD9B0, dll_base + 0x0000D9B0);

		// Input data
		// NOTE: WM_CLOSE posts a quit message to the thread running the tests, it is not tested
		const int32_t bWindowCreated = GENERATE(0, 1);
		const bool bWndProc = GENERATE(false, true);
		const BOOL bDispatchMessageResult = GENERATE(0, 1);
		const UINT Msg = GENERATE(WM_MOUSEMOVE, WM_CHAR, WM_NULL);
		CAPTURE(bWindowCreated);
		CAPTURE(bWndProc);
		CAPTURE(bDispatchMessageResult);
		CAPTURE(Msg);

		moo_main.bWindowCreated = bWindowCreated;
		original_main.bWindowCreated = bWindowCreated;
		if (bWndProc)
		{
			moo_main.pfWndProc = D2WinCallbacks::WndProc;
			original_main.pfWndProc = D2WinCallbacks::WndProc;
		}

		D2WinMock::bDispatchMessageResult = bDispatchMessageResult;

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(nullptr, Msg, 12, 34);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(nullptr, Msg, 12, 34);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare the modified globals
		check_main_states_eq(moo_main, original_main);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ADA80")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Char_6F8ADA80, dll_base + 0x0000DA80);

		// Input data
		// 0: no active edit box, 1: active edit box in the control list, 2: active edit box which is not in the modal control list
		const int nEditBoxState = GENERATE(0, 1, 2);
		const bool bModal = GENERATE(false, true);
		const int32_t nCallbackResult = GENERATE(0, 1);
		const WPARAM wParam = GENERATE('a', 0x7F);
		CAPTURE(nEditBoxState);
		CAPTURE(bModal);
		CAPTURE(nCallbackResult);
		CAPTURE(wParam);

		D2WinCallbacks::nReturnValue = nCallbackResult;
		TestControls moo_controls("control"), original_controls("control");
		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};
		for (const bool bOriginal : { false, true })
		{
			D2WinControlState& state = bOriginal ? original_state : moo_state;
			TestControls& controls = bOriginal ? original_controls : moo_controls;
			D2WinEditBoxStrc& editBox = bOriginal ? original_pEditBox : moo_pEditBox;
			d2win_init_control(editBox.controlHeader, D2WIN_EDITBOX);
			editBox.nMaxLength = 256;
			editBox.nSelectionStart = -1;
			editBox.eFont = D2FONT_FONT16;
			D2WinCallLog::name_pointer(&editBox, "pEditBox");

			state.pControlList = controls.controls;
			if (bModal)
			{
				state.pModalControlList = &controls.controls[1];
			}

			if (nEditBoxState)
			{
				state.pActiveEditBox = &editBox;
				if (nEditBoxState == 1)
				{
					controls.controls[2].pNext = &editBox.controlHeader;
				}
			}
		}

		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		moo_pMsg.nMessage = WM_CHAR;
		original_pMsg.nMessage = WM_CHAR;
		moo_pMsg.wParam = wParam;
		original_pMsg.wParam = wParam;

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
		MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ADB10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Escape_6F8ADB10, dll_base + 0x0000DB10);

		// Input data
		// 0: no cancel button, 1: cancel button, 2: cancel button not in the modal control list
		const int nCancelButtonState = GENERATE(0, 1, 2);
		const bool bModal = GENERATE(false, true);
		CAPTURE(nCancelButtonState);
		CAPTURE(bModal);

		TestControls moo_controls("control"), original_controls("control");
		D2WinButtonStrc moo_pButton{};
		D2WinButtonStrc original_pButton{};
		for (const bool bOriginal : { false, true })
		{
			D2WinControlState& state = bOriginal ? original_state : moo_state;
			TestControls& controls = bOriginal ? original_controls : moo_controls;
			D2WinButtonStrc& button = bOriginal ? original_pButton : moo_pButton;
			d2win_init_control(button.controlHeader, D2WIN_BUTTON);
			button.controlHeader.pfHandleMouseDown = D2WinCallbacks::Callback2;
			button.controlHeader.pfHandleMouseUp = D2WinCallbacks::Callback2;
			D2WinCallLog::name_pointer(&button, "pButton");

			state.pControlList = controls.controls;
			if (bModal)
			{
				state.pModalControlList = nCancelButtonState == 2 ? &controls.controls[1] : &button.controlHeader;
				button.controlHeader.pNext = &controls.controls[1];
			}

			if (nCancelButtonState)
			{
				state.pCancelButton = &button;
			}
		}

		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		moo_pMsg.nMessage = WM_KEYDOWN;
		original_pMsg.nMessage = WM_KEYDOWN;
		moo_pMsg.wParam = VK_ESCAPE;
		original_pMsg.wParam = VK_ESCAPE;

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
		MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ADB50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_VirtualKey_6F8ADB50, dll_base + 0x0000DB50);

		// Input data
		// 0: no active edit box, 1: active edit box in the control list, 2: active edit box which is not in the modal control list
		const int nEditBoxState = GENERATE(0, 1, 2);
		const bool bModal = GENERATE(false, true);
		const int32_t nCallbackResult = GENERATE(0, 1);
		const WPARAM wParam = GENERATE(VK_LEFT, VK_F1);
		CAPTURE(nEditBoxState);
		CAPTURE(bModal);
		CAPTURE(nCallbackResult);
		CAPTURE(wParam);

		D2WinCallbacks::nReturnValue = nCallbackResult;
		TestControls moo_controls("control"), original_controls("control");
		D2WinEditBoxStrc moo_pEditBox{};
		D2WinEditBoxStrc original_pEditBox{};
		for (const bool bOriginal : { false, true })
		{
			D2WinControlState& state = bOriginal ? original_state : moo_state;
			TestControls& controls = bOriginal ? original_controls : moo_controls;
			D2WinEditBoxStrc& editBox = bOriginal ? original_pEditBox : moo_pEditBox;
			d2win_init_control(editBox.controlHeader, D2WIN_EDITBOX);
			editBox.nMaxLength = 256;
			editBox.nSelectionStart = -1;
			editBox.eFont = D2FONT_FONT16;
			std::wcscpy(reinterpret_cast<wchar_t*>(editBox.wszText), L"Text");
			editBox.nCursorPosition = 2;
			D2WinCallLog::name_pointer(&editBox, "pEditBox");

			state.pControlList = controls.controls;
			if (bModal)
			{
				state.pModalControlList = &controls.controls[1];
			}

			if (nEditBoxState)
			{
				state.pActiveEditBox = &editBox;
				if (nEditBoxState == 1)
				{
					controls.controls[2].pNext = &editBox.controlHeader;
				}
			}
		}

		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		moo_pMsg.nMessage = WM_KEYDOWN;
		original_pMsg.nMessage = WM_KEYDOWN;
		moo_pMsg.wParam = wParam;
		original_pMsg.wParam = wParam;

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
		MOO_CHECK_EQ(moo_pEditBox, original_pEditBox, "Comparing pEditBox");
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ADBE0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Control_6F8ADBE0, dll_base + 0x0000DBE0);

		SUBCASE("")
		{
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};
			moo_pMsg.nMessage = WM_KEYDOWN;
			original_pMsg.nMessage = WM_KEYDOWN;
			moo_pMsg.wParam = VK_CONTROL;
			original_pMsg.wParam = VK_CONTROL;

			compare_message_handler(sut, original, moo_pMsg, original_pMsg);
			CHECK_EQ(moo_main.bControlPressed, 1);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ADBF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Control_6F8ADBF0, dll_base + 0x0000DBF0);

		SUBCASE("")
		{
			moo_main.bControlPressed = 1;
			original_main.bControlPressed = 1;
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};
			moo_pMsg.nMessage = WM_KEYUP;
			original_pMsg.nMessage = WM_KEYUP;
			moo_pMsg.wParam = VK_CONTROL;
			original_pMsg.wParam = VK_CONTROL;

			compare_message_handler(sut, original, moo_pMsg, original_pMsg);
			CHECK_EQ(moo_main.bControlPressed, 0);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ADC00")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_SysCommand_6F8ADC00, dll_base + 0x0000DC00);

		// Input data
		const WPARAM wParam = GENERATE(SC_SCREENSAVE, SC_KEYMENU, SC_MOVE, SC_MOVE + 2, SC_CLOSE, SC_MINIMIZE);
		const int32_t bFullScreen = GENERATE(0, 1);
		CAPTURE(wParam);
		CAPTURE(bFullScreen);

		D2WinMock::bFullScreen = bFullScreen;
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		for (SMSGHANDLER_PARAMS* pMsg : { &moo_pMsg, &original_pMsg })
		{
			pMsg->nMessage = WM_SYSCOMMAND;
			pMsg->wParam = wParam;
			pMsg->lResult = 1234;
		}

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8ADC40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_ActivateApp_6F8ADC40, dll_base + 0x0000DC40);

		// Input data
		const WPARAM wParam = GENERATE(0, 1);
		const int32_t bSoundPaused = GENERATE(0, 1);
		const int32_t bCutScene = GENERATE(0, 1);
		CAPTURE(wParam);
		CAPTURE(bSoundPaused);
		CAPTURE(bCutScene);

		moo_main.bSoundPaused = bSoundPaused;
		original_main.bSoundPaused = bSoundPaused;
		moo_main.pSoundState = reinterpret_cast<void*>(0x1234);
		original_main.pSoundState = reinterpret_cast<void*>(0x1234);
		D2WinMock::bCutScene = bCutScene;

		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		for (SMSGHANDLER_PARAMS* pMsg : { &moo_pMsg, &original_pMsg })
		{
			pMsg->nMessage = WM_ACTIVATEAPP;
			pMsg->wParam = wParam;
			pMsg->bUseResult = 1;
		}

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADCD0 (#10168)" * doctest::skip("Needs an initialized renderer and writes screenshot files"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10168_WINMAIN_CreateScreenshot, dll_base + 0x0000DCD0);

		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ADE70" * doctest::skip("Needs an initialized renderer and writes screenshot files"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_Snapshot_6F8ADE70, dll_base + 0x0000DE70);

		SUBCASE("")
		{
			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};

			// Call both implementations
			sut(&moo_pMsg);
			original(&original_pMsg);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AE020")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_KeyF1_6F8AE020, dll_base + 0x0000E020);

		// Input data
		const int32_t bControlPressed = GENERATE(0, 1);
		const int32_t nSound10066Result = GENERATE(0, 1);
		const int32_t nSound10069Result = GENERATE(0, 1);
		CAPTURE(bControlPressed);
		CAPTURE(nSound10066Result);
		CAPTURE(nSound10069Result);

		moo_main.bControlPressed = bControlPressed;
		original_main.bControlPressed = bControlPressed;
		D2WinMock::nSound10066Result = nSound10066Result;
		D2WinMock::nSound10069Result = nSound10069Result;

		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		for (SMSGHANDLER_PARAMS* pMsg : { &moo_pMsg, &original_pMsg })
		{
			pMsg->nMessage = WM_KEYDOWN;
			pMsg->wParam = 0x4D;
			pMsg->lResult = 1234;
		}

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AE070")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_MouseButton_6F8AE070, dll_base + 0x0000E070);

		// Input data
		const UINT nMessage = GENERATE(WM_LBUTTONDOWN, WM_LBUTTONUP, WM_RBUTTONDOWN, WM_RBUTTONUP, WM_MBUTTONDOWN);
		const bool bModal = GENERATE(false, true);
		const int32_t nCallbackResult = GENERATE(0, 1);
		// Over no control, over the first control, over both controls
		const int nPosition = GENERATE(0, 1, 2);
		const bool bHitTest = GENERATE(false, true);
		CAPTURE(nMessage);
		CAPTURE(bModal);
		CAPTURE(nCallbackResult);
		CAPTURE(nPosition);
		CAPTURE(bHitTest);

		D2WinCallbacks::nReturnValue = nCallbackResult;
		TestControls moo_controls("control"), original_controls("control");
		for (const bool bOriginal : { false, true })
		{
			D2WinControlState& state = bOriginal ? original_state : moo_state;
			TestControls& controls = bOriginal ? original_controls : moo_controls;
			state.pControlList = controls.controls;
			if (bModal)
			{
				state.pModalControlList = &controls.controls[1];
			}

			// The hit test of an animated image replaces the default rectangle check of the first control
			if (bHitTest)
			{
				controls.controls[0].pfShouldMouseInputBeHandled = bOriginal ? original_d2win_function<int32_t __fastcall(D2WinControlStrc*)>(0x6F8A5530) : ANIMIMAGE_ShouldMouseInputBeHandled;
			}
		}

		const POINT positions[] = { { 10, 10 }, { 110, 170 }, { 160, 190 } };
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		for (SMSGHANDLER_PARAMS* pMsg : { &moo_pMsg, &original_pMsg })
		{
			pMsg->nMessage = nMessage;
			pMsg->lParam = MAKELPARAM(positions[nPosition].x, positions[nPosition].y);
		}

		// The descriptor of the animated image used for the hit test
		D2WinFakeCellFile cellFile("anim", 1, 0, 0);
		D2CellFileStrc* pCellFile = cellFile.get();
		D2AnimatedImageDescriptor descriptor = { &pCellFile, nullptr, DRAWMODE_NORMAL, 0 };
		D2WinAnimImageStrc moo_pAnimImage{};
		D2WinAnimImageStrc original_pAnimImage{};
		if (bHitTest)
		{
			// The animated image replaces the first control
			for (const bool bOriginal : { false, true })
			{
				D2WinAnimImageStrc& animImage = bOriginal ? original_pAnimImage : moo_pAnimImage;
				TestControls& controls = bOriginal ? original_controls : moo_controls;
				animImage.controlHeader = controls.controls[0];
				animImage.pAnimatedImageDescriptor = &descriptor;
				(bOriginal ? original_state : moo_state).pControlList = &animImage.controlHeader;
				D2WinCallLog::name_pointer(&animImage, "control0");
			}
		}

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
		CHECK_EQ(D2Win_IsMouseButtonPressed(), original_d2win_function<decltype(D2Win_IsMouseButtonPressed)>(0x6F8AE500)());

		// The state of the mouse buttons is reset, it's stored in globals that the tests can't access
		moo_state.pControlList = nullptr;
		original_state.pControlList = nullptr;
		moo_state.pModalControlList = nullptr;
		original_state.pModalControlList = nullptr;
		SMSGHANDLER_PARAMS releaseMsg{};
		releaseMsg.nMessage = WM_LBUTTONUP;
		sut(&releaseMsg);
		original(&releaseMsg);
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AE220")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_COMMANDS_MouseWheel_6F8AE220, dll_base + 0x0000E220);

		// Input data
		const int nWheelDelta = GENERATE(-240, -120, 0, 120);
		// Mouse over the first scroll bar, the second scroll bar, between them or far away
		const int nPosition = GENERATE(0, 1, 2, 3);
		const int32_t nMaxSteps = GENERATE(0, 10);
		const bool bModal = GENERATE(false, true);
		CAPTURE(nWheelDelta);
		CAPTURE(nPosition);
		CAPTURE(nMaxSteps);
		CAPTURE(bModal);

		// Two scroll bars (x = [100, 110] and [300, 310], y = [100, 300]) and a button scrolling in both directions
		D2WinScrollBarStrc moo_pScrollBars[2]{};
		D2WinScrollBarStrc original_pScrollBars[2]{};
		D2WinButtonStrc moo_pButton{};
		D2WinButtonStrc original_pButton{};
		for (const bool bOriginal : { false, true })
		{
			D2WinScrollBarStrc* pScrollBars = bOriginal ? original_pScrollBars : moo_pScrollBars;
			D2WinButtonStrc& button = bOriginal ? original_pButton : moo_pButton;
			for (int i = 0; i < 2; ++i)
			{
				d2win_init_control(pScrollBars[i].controlHeader, D2WIN_SCROLLBAR, 100 + 200 * i, 300, 10, 200);
				pScrollBars[i].nMaxSteps = nMaxSteps;
				pScrollBars[i].nCurrentStep = nMaxSteps / 2;
				pScrollBars[i].pfOnScroll = D2WinCallbacks::VoidCallback;
				D2WinCallLog::name_pointer(&pScrollBars[i], "pScrollBar" + std::to_string(i));
			}

			d2win_init_control(button.controlHeader, D2WIN_BUTTON);
			button.dwButtonFlags = 0x18;
			button.controlHeader.pfCallback = D2WinCallbacks::Callback;
			D2WinCallLog::name_pointer(&button, "pButton");

			pScrollBars[0].controlHeader.pNext = &button.controlHeader;
			button.controlHeader.pNext = &pScrollBars[1].controlHeader;

			D2WinControlState& state = bOriginal ? original_state : moo_state;
			state.pControlList = &pScrollBars[0].controlHeader;
			if (bModal)
			{
				state.pModalControlList = &button.controlHeader;
			}
		}

		const POINT positions[] = { { 105, 200 }, { 305, 150 }, { 190, 320 }, { 700, 20 } };
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};
		for (SMSGHANDLER_PARAMS* pMsg : { &moo_pMsg, &original_pMsg })
		{
			pMsg->nMessage = WM_MOUSEWHEEL;
			pMsg->wParam = MAKEWPARAM(0, static_cast<WORD>(static_cast<int16_t>(nWheelDelta)));
			pMsg->lParam = MAKELPARAM(positions[nPosition].x, positions[nPosition].y);
		}

		compare_message_handler(sut, original, moo_pMsg, original_pMsg);
		for (int i = 0; i < 2; ++i)
		{
			MOO_CHECK_EQ(moo_pScrollBars[i], original_pScrollBars[i], "Comparing scroll bars");
		}

		MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AE4A0 (#10029)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10029, dll_base + 0x0000E4A0);

		SUBCASE("")
		{
			// Input data
			const int bShowCursor = GENERATE(0, 1, 5);

			// Call both implementations
			sut(bShowCursor);
			original(bShowCursor);

			// Compare the modified globals
			check_main_states_eq(moo_main, original_main);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE4B0 (#10030)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10030_CONTROL_ToggleFourthFlag, dll_base + 0x0000E4B0);

		SUBCASE("")
		{
			// Input data
			const uint32_t dwFlags = GENERATE(0u, 8u, 0xFFFFFFFFu);
			const int bSet = GENERATE(0, 1, 7);
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			moo_pControl.dwFlags = dwFlags;
			original_pControl.dwFlags = dwFlags;

			// Call both implementations
			sut(&moo_pControl, bSet);
			original(&original_pControl, bSet);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AE4F0 (#10031)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10031, dll_base + 0x0000E4F0);

		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc button{};
			void* pCancelButton = GENERATE(true, false) ? &button : nullptr;

			// Call both implementations
			sut(pCancelButton);
			original(pCancelButton);

			// Compare the modified globals
			CHECK_EQ(moo_state.pCancelButton, original_state.pCancelButton);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AE500 (#10032)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_IsMouseButtonPressed, dll_base + 0x0000E500);

		SUBCASE("")
		{
			// Input data
			const UINT nMessage = GENERATE(WM_LBUTTONDOWN, WM_LBUTTONUP);
			SMSGHANDLER_PARAMS msg{};
			msg.nMessage = nMessage;
			D2Win_COMMANDS_MouseButton_6F8AE070(&msg);
			original_D2Win_COMMANDS_MouseButton(&msg);

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Release the mouse buttons again
			msg.nMessage = WM_LBUTTONUP;
			D2Win_COMMANDS_MouseButton_6F8AE070(&msg);
			original_D2Win_COMMANDS_MouseButton(&msg);
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AE510 (#10033)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10033, dll_base + 0x0000E510);

		SUBCASE("")
		{
			// Input data
			D2WinControlStrc control{};
			D2WinControlStrc* pModalControlList = GENERATE(true, false) ? &control : nullptr;
			const int bDimBackground = GENERATE(0, 1);

			// Call both implementations
			const auto moo_result = sut(pModalControlList, bDimBackground);
			const auto original_result = original(pModalControlList, bDimBackground);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare the modified globals
			CHECK_EQ(moo_state.pModalControlList, original_state.pModalControlList);
			CHECK_EQ(moo_state.bDimBackground, original_state.bDimBackground);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AE530 (#10035)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_GetType, dll_base + 0x0000E530);

		SUBCASE("")
		{
			// Input data
			const int32_t nType = GENERATE(0, D2WIN_EDITBOX, D2WIN_IMAGE2, 100);
			D2WinControlStrc moo_pControl{};
			D2WinControlStrc original_pControl{};
			moo_pControl.nType = nType;
			original_pControl.nType = nType;

			// Call both implementations
			const auto moo_result = sut(&moo_pControl);
			const auto original_result = original(&original_pControl);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pControl, original_pControl, "Comparing pControl");
		}

		SUBCASE("Null control")
		{
			// Call both implementations
			const auto moo_result = sut(nullptr);
			const auto original_result = original(nullptr);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(MainFixture, "D2Win.0x6F8AE540")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(CONTROL_GetModalControlList, dll_base + 0x0000E540);

		SUBCASE("")
		{
			// Input data
			D2WinControlStrc control{};
			D2WinControlStrc* pModalControlList = GENERATE(true, false) ? &control : nullptr;
			moo_state.pModalControlList = pModalControlList;
			original_state.pModalControlList = pModalControlList;

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			CHECK_EQ(moo_result, original_result);
		}
	}
}

#endif
