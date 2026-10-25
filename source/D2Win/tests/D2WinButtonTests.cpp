#include <D2WinTestDefines.h>

#ifdef BUTTON_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinButton.h>


TEST_SUITE("D2WinButtonTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Button at x = [100, 220], y = [160, 200]. The message handlers are the ones of the respective implementation.
	void setup_button(D2WinButtonStrc& pButton, bool bOriginal, uint32_t dwButtonFlags = 0)
	{
		d2win_init_control(pButton.controlHeader, D2WIN_BUTTON);
		pButton.dwButtonFlags = dwButtonFlags;
		pButton.nBaseFrame = 2;
		pButton.nIsPressedFrameOffset = 1;
		pButton.nDisabledFrameOffset = 2;
		pButton.controlHeader.pfCallback = D2WinCallbacks::Callback;

		if (bOriginal)
		{
			pButton.controlHeader.pfHandleMouseDown = original_d2win_function<int32_t __stdcall(SMSGHANDLER_PARAMS*)>(0x6F8A6A10);
			pButton.controlHeader.pfHandleMouseUp = original_d2win_function<int32_t __stdcall(SMSGHANDLER_PARAMS*)>(0x6F8A6AF0);
		}
		else
		{
			pButton.controlHeader.pfHandleMouseDown = BUTTON_HandleMouseDown;
			pButton.controlHeader.pfHandleMouseUp = BUTTON_HandleMouseUp;
		}
	}


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A61A0 (#10107)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_Create, dll_base + 0x000061A0);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("button", 8);
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = GENERATE(1, 256, 257, 600);
			const int32_t nHeight = GENERATE(20, 256, 300);
			const int32_t nActivationVirtualKey = GENERATE(0, VK_RETURN);
			const int32_t nBaseFrame = random_unsigned_integer(0, 10);
			const uint32_t nFlags = GENERATE(0u, 2u, 0x20u, 0x7Fu);
			const uint16_t nStringId = GENERATE(0, 1234);

			// Call both implementations
			D2WinButtonStrc* moo_result = sut(nX, nY, nWidth, nHeight, cellFile.get(), D2WinCallbacks::Callback, nActivationVirtualKey, nBaseFrame, nFlags, nStringId, D2WinCallbacks::Callback2);
			D2WinButtonStrc* original_result = original(nX, nY, nWidth, nHeight, cellFile.get(), D2WinCallbacks::Callback, nActivationVirtualKey, nBaseFrame, nFlags, nStringId, D2WinCallbacks::Callback2);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &BUTTON_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &BUTTON_HandleMouseDown);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseUp, &BUTTON_HandleMouseUp);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x000065A0);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x00006A10);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseUp), dll_base + 0x00006AF0);
			CHECK_EQ(moo_result->controlHeader.pfHandleVirtualKeyInput != nullptr, original_result->controlHeader.pfHandleVirtualKeyInput != nullptr);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A62C0 (#10108)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_Destroy, dll_base + 0x000062C0);

		SUBCASE("")
		{
			// Input data
			D2WinButtonStrc* moo_pButton = d2win_calloc<D2WinButtonStrc>();
			D2WinButtonStrc* original_pButton = d2win_calloc<D2WinButtonStrc>();
			setup_button(*moo_pButton, false);
			setup_button(*original_pButton, true);
			moo_state.pControlList = &moo_pButton->controlHeader;
			original_state.pControlList = &original_pButton->controlHeader;

			// Call both implementations
			const auto moo_result = sut(moo_pButton);
			const auto original_result = original(original_pButton);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A62F0 (#10109)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_IsPressed, dll_base + 0x000062F0);

		SUBCASE("")
		{
			// Input data
			const int32_t bIsPressed = GENERATE(0, 1, 2);
			const int32_t bIsCallbackPending = GENERATE(0, 1, 3);
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			setup_button(moo_pButton, false);
			setup_button(original_pButton, true);
			moo_pButton.bIsPressed = bIsPressed;
			original_pButton.bIsPressed = bIsPressed;
			moo_pButton.bIsCallbackPending = bIsCallbackPending;
			original_pButton.bIsCallbackPending = bIsCallbackPending;

			// Call both implementations
			const auto moo_result = sut(&moo_pButton);
			const auto original_result = original(&original_pButton);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6330 (#10110)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetIsPressed, dll_base + 0x00006330);

		SUBCASE("")
		{
			// Input data
			const int32_t bIsPressed = GENERATE(0, 1, 5);
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			setup_button(moo_pButton, false);
			setup_button(original_pButton, true);

			// Call both implementations
			sut(&moo_pButton, bIsPressed);
			original(&original_pButton, bIsPressed);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6360 (#10186)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetText, dll_base + 0x00006360);

		SUBCASE("")
		{
			// Input data
			const Font eFont = GENERATE(D2FONT_FONT8, D2FONT_FONTEXOCET10);
			const wchar_t* wszText = GENERATE(L"", L"OK", L"A somewhat longer button text");
			const int32_t nTextColor = random_unsigned_integer(0, 12);
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			setup_button(moo_pButton, false);
			setup_button(original_pButton, true);

			// Call both implementations
			sut(&moo_pButton, eFont, D2_USTR(wszText), nTextColor);
			original(&original_pButton, eFont, D2_USTR(wszText), nTextColor);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");

			// Check specific values
			CHECK(unicode_equals(moo_pButton.wszText, wszText));
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A63A0 (#10111)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetTextWithStringId, dll_base + 0x000063A0);

		SUBCASE("")
		{
			// Input data
			const Font eFont = GENERATE(D2FONT_FONT8, D2FONT_FONTEXOCET10);
			const uint16_t nStringId = GENERATE(1, 5000);
			const int32_t nTextColor = random_unsigned_integer(0, 12);
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			setup_button(moo_pButton, false);
			setup_button(original_pButton, true);

			// Call both implementations
			sut(&moo_pButton, eFont, nStringId, nTextColor);
			original(&original_pButton, eFont, nStringId, nTextColor);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
			CHECK_EQ(D2LangStringTblMock::calls.size(), 2);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A63F0 (#10112)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetCoordinates, dll_base + 0x000063F0);

		SUBCASE("")
		{
			// Input data
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = random_unsigned_integer(0, 800);
			const int32_t nHeight = random_unsigned_integer(0, 600);
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			setup_button(moo_pButton, false);
			setup_button(original_pButton, true);

			// Call both implementations
			sut(&moo_pButton, nX, nY, nWidth, nHeight);
			original(&original_pButton, nX, nY, nWidth, nHeight);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A6430 (#10113)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SimulateClick, dll_base + 0x00006430);

		// NOTE: The mouse down handler asserts that it's called from a message handler when the button calls its callback on mouse down (flags 1 and 2),
		// but BUTTON_SimulateClick doesn't increment the counter before calling it. Those buttons are tested without callback.

		// Input data
		const uint32_t dwButtonFlags = GENERATE(0u, 1u, 2u, 4u, 6u);
		const uint32_t dwFlags = GENERATE(5u, 1u);
		const bool bHasHandlers = GENERATE(true, false);
		const int32_t bIsPressed = GENERATE(0, 1);
		CAPTURE(dwButtonFlags);
		CAPTURE(dwFlags);
		CAPTURE(bHasHandlers);
		CAPTURE(bIsPressed);

		D2WinButtonStrc moo_pButton{};
		D2WinButtonStrc original_pButton{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinButtonStrc& pButton,
			SMSGHANDLER_PARAMS& pMsg,
			bool bOriginal
		) {
			setup_button(pButton, bOriginal, dwButtonFlags);
			pButton.controlHeader.dwFlags = dwFlags;
			pButton.bIsPressed = bIsPressed;
			pButton.bIsCallbackPending = bIsPressed;
			if (dwButtonFlags & 3)
			{
				pButton.controlHeader.pfCallback = nullptr;
			}

			if (!bHasHandlers)
			{
				pButton.controlHeader.pfHandleMouseDown = nullptr;
				pButton.controlHeader.pfHandleMouseUp = nullptr;
			}

			pMsg.hWindow = reinterpret_cast<HWND>(&pButton);
			pMsg.nMessage = WM_KEYDOWN;
			pMsg.wParam = VK_RETURN;
		};

		setup_data(moo_pButton, moo_pMsg, false);
		setup_data(original_pButton, original_pMsg, true);
		D2WinCallLog::name_pointer(&moo_pButton, "pButton");
		D2WinCallLog::name_pointer(&original_pButton, "pButton");

		// Call both implementations
		D2WinCallLog::clear();
		sut(&moo_pMsg);
		const auto moo_calls = D2WinCallLog::take();
		original(&original_pMsg);
		const auto original_calls = D2WinCallLog::take();

		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		CHECK_EQ(moo_state.nRemovedControlsLocked, original_state.nRemovedControlsLocked);
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A64A0 (#10114)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetBaseFrame, dll_base + 0x000064A0);

		SUBCASE("")
		{
			// Input data
			const int32_t nBaseFrame = random_unsigned_integer(0, 100);
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			setup_button(moo_pButton, false);
			setup_button(original_pButton, true);

			// Call both implementations
			sut(&moo_pButton, nBaseFrame);
			original(&original_pButton, nBaseFrame);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A64D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_OnMouseWheelScrolled, dll_base + 0x000064D0);

		// Input data
		const uint32_t dwButtonFlags = GENERATE(0u, 8u, 0x10u, 0x18u);
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const int32_t nState = GENERATE(0, 1, 2);
		const int32_t nMouseWheelIncrement = GENERATE(-2, 0, 1);
		CAPTURE(dwButtonFlags);
		CAPTURE(dwFlags);
		CAPTURE(nState);
		CAPTURE(nMouseWheelIncrement);

		D2WinButtonStrc moo_pButton{};
		D2WinButtonStrc original_pButton{};

		const auto setup_data = [&](
			D2WinButtonStrc& pButton,
			bool bOriginal
		) {
			setup_button(pButton, bOriginal, dwButtonFlags);
			pButton.controlHeader.dwFlags = dwFlags;
			pButton.bIsPressed = nState == 1;
			pButton.bIsCallbackPending = nState == 2;
		};

		setup_data(moo_pButton, false);
		setup_data(original_pButton, true);
		D2WinCallLog::name_pointer(&moo_pButton, "pButton");
		D2WinCallLog::name_pointer(&original_pButton, "pButton");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pButton, nMouseWheelIncrement);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pButton, nMouseWheelIncrement);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A6570 (#10189)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_SetStringId, dll_base + 0x00006570);

		SUBCASE("")
		{
			// Input data
			const uint16_t nStringId = random_unsigned_integer(0, 0xFFFF);
			D2WinButtonStrc moo_pButton{};
			D2WinButtonStrc original_pButton{};
			setup_button(moo_pButton, false);
			setup_button(original_pButton, true);

			// Call both implementations
			sut(&moo_pButton, nStringId);
			original(&original_pButton, nStringId);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A65A0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_Draw, dll_base + 0x000065A0);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const uint32_t dwButtonFlags = GENERATE(0u, 2u, 0x20u, 0x40u);
		const int32_t nHeight = GENERATE(20, 32, 35, 300);
		const int32_t nState = GENERATE(0, 1, 2);
		const bool bHovered = GENERATE(true, false);
		const bool bHasText = GENERATE(true, false);
		const bool bModal = GENERATE(false, true);
		CAPTURE(dwFlags);
		CAPTURE(dwButtonFlags);
		CAPTURE(nHeight);
		CAPTURE(nState);
		CAPTURE(bHovered);
		CAPTURE(bHasText);
		CAPTURE(bModal);

		D2WinFakeCellFile cellFile("button", 12);
		D2WinButtonStrc moo_pButton{};
		D2WinButtonStrc original_pButton{};
		D2WinControlStrc modalControl{};

		const auto setup_data = [&](
			D2WinButtonStrc& pButton,
			bool bOriginal
		) {
			setup_button(pButton, bOriginal, dwButtonFlags);
			pButton.controlHeader.dwFlags = dwFlags;
			pButton.controlHeader.nWidth = 300;
			pButton.controlHeader.nHeight = nHeight;
			pButton.controlHeader.pCellFile = cellFile.get();
			pButton.bIsPressed = nState != 0;
			pButton.nActivationCounter = nState == 2 ? 1 : 0;
			pButton.nStringId = 1234;
			pButton.pfUpdateHoverState = D2WinCallbacks::Callback2;
			if (bHasText)
			{
				std::memcpy(pButton.wszText, L"Button\xFF" L"c1 text", sizeof(L"Button\xFF" L"c1 text"));
			}
		};

		setup_data(moo_pButton, false);
		setup_data(original_pButton, true);
		set_mouse_position(bHovered ? 150 : 50, bHovered ? 199 : 50);
		if (bModal)
		{
			moo_state.pModalControlList = &modalControl;
			original_state.pModalControlList = &modalControl;
		}

		D2WinCallLog::name_pointer(&moo_pButton, "pButton");
		D2WinCallLog::name_pointer(&original_pButton, "pButton");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pButton.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pButton.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A6A10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_HandleMouseDown, dll_base + 0x00006A10);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const uint32_t dwButtonFlags = GENERATE(0u, 1u, 2u, 4u, 6u);
		const int32_t nState = GENERATE(0, 1, 2);
		CAPTURE(dwFlags);
		CAPTURE(dwButtonFlags);
		CAPTURE(nState);

		D2WinButtonStrc moo_pButton{};
		D2WinButtonStrc original_pButton{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinButtonStrc& pButton,
			SMSGHANDLER_PARAMS& pMsg,
			bool bOriginal
		) {
			setup_button(pButton, bOriginal, dwButtonFlags);
			pButton.controlHeader.dwFlags = dwFlags;
			pButton.bIsPressed = nState != 0;
			pButton.bIsCallbackPending = nState == 2;
			pMsg.hWindow = reinterpret_cast<HWND>(&pButton);
			pMsg.nMessage = WM_LBUTTONDOWN;
		};

		setup_data(moo_pButton, moo_pMsg, false);
		setup_data(original_pButton, original_pMsg, true);
		// The callback may only be called from a message handler
		moo_state.nRemovedControlsLocked = 1;
		original_state.nRemovedControlsLocked = 1;
		D2WinCallLog::name_pointer(&moo_pButton, "pButton");
		D2WinCallLog::name_pointer(&original_pButton, "pButton");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pMsg);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pMsg);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A6AF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_HandleMouseUp, dll_base + 0x00006AF0);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const uint32_t dwButtonFlags = GENERATE(0u, 1u, 2u, 4u);
		const int32_t nState = GENERATE(0, 1, 2);
		const int32_t nCallbackResult = GENERATE(0, 3);
		CAPTURE(dwFlags);
		CAPTURE(dwButtonFlags);
		CAPTURE(nState);
		CAPTURE(nCallbackResult);

		D2WinCallbacks::nReturnValue = nCallbackResult;

		D2WinButtonStrc moo_pButton{};
		D2WinButtonStrc original_pButton{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinButtonStrc& pButton,
			SMSGHANDLER_PARAMS& pMsg,
			bool bOriginal
		) {
			setup_button(pButton, bOriginal, dwButtonFlags);
			pButton.controlHeader.dwFlags = dwFlags;
			pButton.bIsPressed = nState != 0;
			pButton.bIsCallbackPending = nState == 2;
			pMsg.hWindow = reinterpret_cast<HWND>(&pButton);
			pMsg.nMessage = WM_LBUTTONUP;
		};

		setup_data(moo_pButton, moo_pMsg, false);
		setup_data(original_pButton, original_pMsg, true);
		moo_state.nRemovedControlsLocked = 1;
		original_state.nRemovedControlsLocked = 1;
		D2WinCallLog::name_pointer(&moo_pButton, "pButton");
		D2WinCallLog::name_pointer(&original_pButton, "pButton");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pMsg);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pMsg);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A6BB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(BUTTON_HandleVirtualKeyInput, dll_base + 0x00006BB0);

		// Input data
		const UINT nMessage = GENERATE(WM_KEYDOWN, WM_CHAR);
		const WPARAM wParam = GENERATE(VK_RETURN, VK_ESCAPE);
		const uint32_t dwButtonFlags = GENERATE(0u, 2u, 4u);
		const bool bHasHandlers = GENERATE(true, false);
		CAPTURE(nMessage);
		CAPTURE(wParam);
		CAPTURE(dwButtonFlags);
		CAPTURE(bHasHandlers);

		D2WinButtonStrc moo_pButton{};
		D2WinButtonStrc original_pButton{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinButtonStrc& pButton,
			SMSGHANDLER_PARAMS& pMsg,
			bool bOriginal
		) {
			setup_button(pButton, bOriginal, dwButtonFlags);
			pButton.nActivationVirtualKey = VK_RETURN;
			if (!bHasHandlers)
			{
				pButton.controlHeader.pfHandleMouseDown = nullptr;
				pButton.controlHeader.pfHandleMouseUp = nullptr;
			}

			pMsg.hWindow = reinterpret_cast<HWND>(&pButton);
			pMsg.nMessage = nMessage;
			pMsg.wParam = wParam;
		};

		setup_data(moo_pButton, moo_pMsg, false);
		setup_data(original_pButton, original_pMsg, true);
		moo_state.nRemovedControlsLocked = 1;
		original_state.nRemovedControlsLocked = 1;
		D2WinCallLog::name_pointer(&moo_pButton, "pButton");
		D2WinCallLog::name_pointer(&original_pButton, "pButton");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pMsg);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pMsg);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pButton, original_pButton, "Comparing pButton");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		CHECK_EQ(moo_state.nRemovedControlsLocked, original_state.nRemovedControlsLocked);
	}
}

#endif
