#include <D2WinTestDefines.h>

#ifdef SCROLLBAR_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinScrollBar.h>
#include <D2WinTextBox.h>


TEST_SUITE("D2WinScrollBarTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Scroll bar at x = [100, 110], y = [200, 300]
	void setup_scrollbar(D2WinScrollBarStrc& pScrollBar, int32_t nMaxSteps, int32_t nCurrentStep)
	{
		d2win_init_control(pScrollBar.controlHeader, D2WIN_SCROLLBAR, 100, 300, 10, 100);
		pScrollBar.nMaxSteps = nMaxSteps;
		pScrollBar.nCurrentStep = nCurrentStep;
	}

	// Text box with 10 lines, used to check that the scroll bar scrolls it
	struct TextBoxWithLines
	{
		D2WinTextBoxStrc textBox{};
		D2WinTextBoxLineStrc lines[10]{};

		TextBoxWithLines()
		{
			d2win_init_control(textBox.controlHeader, D2WIN_TEXTBOX);
			for (int i = 0; i < 10; ++i)
			{
				lines[i].nColor = i;
				lines[i].pNext = i < 9 ? &lines[i + 1] : nullptr;
			}

			textBox.pFirstLine = &lines[0];
			textBox.pLastLine = &lines[9];
			textBox.pCurrentLine = &lines[0];
			textBox.nNumLines = 10;
		}
	};


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AF040 (#10063)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_Create, dll_base + 0x0000F040);

		SUBCASE("")
		{
			D2WinFakeCellFile cellFile("scrollbar", 6);
			const int nX = random_unsigned_integer(0, 800);
			const int nY = random_unsigned_integer(0, 600);
			const int nWidth = random_unsigned_integer(1, 20);
			const int nHeight = random_unsigned_integer(30, 300);

			// Call both implementations
			D2WinScrollBarStrc* moo_result = sut(nX, nY, nWidth, nHeight, cellFile.get(), D2WinCallbacks::Callback);
			D2WinScrollBarStrc* original_result = original(nX, nY, nWidth, nHeight, cellFile.get(), D2WinCallbacks::Callback);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &SCROLLBAR_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &SCROLLBAR_HandleMouseDown);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseUp, &SCROLLBAR_HandleMouseUp);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x0000F330);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x0000F4D0);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseUp), dll_base + 0x0000F6B0);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1BF0 (#10064)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_Destroy, dll_base + 0x00011BF0);

		SUBCASE("")
		{
			// Input data
			D2WinScrollBarStrc* moo_pScrollBar = d2win_calloc<D2WinScrollBarStrc>();
			D2WinScrollBarStrc* original_pScrollBar = d2win_calloc<D2WinScrollBarStrc>();
			setup_scrollbar(*moo_pScrollBar, 10, 2);
			setup_scrollbar(*original_pScrollBar, 10, 2);
			moo_state.pControlList = &moo_pScrollBar->controlHeader;
			original_state.pControlList = &original_pScrollBar->controlHeader;

			// Call both implementations
			const auto moo_result = sut(&moo_pScrollBar->controlHeader);
			const auto original_result = original(&original_pScrollBar->controlHeader);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF100 (#10065)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_GetMaxSteps, dll_base + 0x0000F100);

		SUBCASE("")
		{
			// Input data
			const int32_t nMaxSteps = random_unsigned_integer(0, 1000);
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_scrollbar(moo_pScrollBar, nMaxSteps, 0);
			setup_scrollbar(original_pScrollBar, nMaxSteps, 0);

			// Call both implementations
			const auto moo_result = sut(&moo_pScrollBar);
			const auto original_result = original(&original_pScrollBar);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");

			// Check specific values
			CHECK_EQ(moo_result, nMaxSteps);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF130 (#10066)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_SetMaxSteps, dll_base + 0x0000F130);

		SUBCASE("")
		{
			// Input data
			const int32_t nMaxSteps = GENERATE(-10, -1, 0, 1, 50);
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_scrollbar(moo_pScrollBar, 20, 15);
			setup_scrollbar(original_pScrollBar, 20, 15);

			// Call both implementations
			const auto moo_result = sut(&moo_pScrollBar, nMaxSteps);
			const auto original_result = original(&original_pScrollBar, nMaxSteps);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF170 (#10068)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_SetCurrentStep, dll_base + 0x0000F170);

		SUBCASE("")
		{
			// Input data
			const int32_t nCurrentStep = GENERATE(-5, 0, 7, 20, 21, 100);
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_scrollbar(moo_pScrollBar, 20, 3);
			setup_scrollbar(original_pScrollBar, 20, 3);

			// Call both implementations
			const auto moo_result = sut(&moo_pScrollBar, nCurrentStep);
			const auto original_result = original(&original_pScrollBar, nCurrentStep);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF1B0 (#10067)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_GetCurrentStep, dll_base + 0x0000F1B0);

		SUBCASE("")
		{
			// Input data
			const int32_t nCurrentStep = random_unsigned_integer(0, 1000);
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_scrollbar(moo_pScrollBar, 1000, nCurrentStep);
			setup_scrollbar(original_pScrollBar, 1000, nCurrentStep);

			// Call both implementations
			const auto moo_result = sut(&moo_pScrollBar);
			const auto original_result = original(&original_pScrollBar);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");

			// Check specific values
			CHECK_EQ(moo_result, nCurrentStep);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF1E0 (#10069)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_SetTextBox, dll_base + 0x0000F1E0);

		SUBCASE("")
		{
			// Input data
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			TextBoxWithLines moo_pTextBox;
			TextBoxWithLines original_pTextBox;
			setup_scrollbar(moo_pScrollBar, 10, 0);
			setup_scrollbar(original_pScrollBar, 10, 0);

			// Call both implementations
			const auto moo_result = sut(&moo_pScrollBar, &moo_pTextBox.textBox);
			const auto original_result = original(&original_pScrollBar, &original_pTextBox.textBox);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");

			// Check specific values
			CHECK_EQ(moo_pScrollBar.pTextBox, &moo_pTextBox.textBox);
			CHECK_EQ(original_pScrollBar.pTextBox, &original_pTextBox.textBox);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF210")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_SetCallback, dll_base + 0x0000F210);

		SUBCASE("")
		{
			// Input data
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_scrollbar(moo_pScrollBar, 10, 0);
			setup_scrollbar(original_pScrollBar, 10, 0);
			void(__stdcall* pfCallback)(SMSGHANDLER_PARAMS*) = GENERATE(D2WinCallbacks::VoidCallback, nullptr);

			// Call both implementations
			const auto moo_result = sut(&moo_pScrollBar, pfCallback);
			const auto original_result = original(&original_pScrollBar, pfCallback);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AF240")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_HandleMouseWheel, dll_base + 0x0000F240);

		// Input data
		const int nWheelDelta = GENERATE(-3, -1, 0, 1, 2);
		const int32_t nCurrentStep = GENERATE(0, 5, 10);
		const bool bDragged = GENERATE(false, true);
		const bool bWithTextBox = GENERATE(false, true);
		CAPTURE(nWheelDelta);
		CAPTURE(nCurrentStep);
		CAPTURE(bDragged);
		CAPTURE(bWithTextBox);

		D2WinScrollBarStrc moo_pScrollBar{};
		D2WinScrollBarStrc original_pScrollBar{};
		TextBoxWithLines moo_pTextBox;
		TextBoxWithLines original_pTextBox;
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [nCurrentStep, bDragged](
			D2WinScrollBarStrc& pScrollBar,
			SMSGHANDLER_PARAMS& pMsg,
			D2WinTextBoxStrc* pTextBox
		) {
			setup_scrollbar(pScrollBar, 10, nCurrentStep);
			pScrollBar.bIsStepIndicatorDragged = bDragged;
			pScrollBar.pTextBox = pTextBox;
			pScrollBar.pfOnScroll = D2WinCallbacks::VoidCallback;
			pMsg.hWindow = reinterpret_cast<HWND>(&pScrollBar);
			pMsg.nMessage = WM_MOUSEWHEEL;
		};

		setup_data(moo_pScrollBar, moo_pMsg, bWithTextBox ? &moo_pTextBox.textBox : nullptr);
		setup_data(original_pScrollBar, original_pMsg, bWithTextBox ? &original_pTextBox.textBox : nullptr);
		D2WinCallLog::name_pointer(&moo_pScrollBar, "pScrollBar");
		D2WinCallLog::name_pointer(&original_pScrollBar, "pScrollBar");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pMsg, &moo_pScrollBar, nWheelDelta);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pMsg, &original_pScrollBar, nWheelDelta);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		if (bWithTextBox)
		{
			MOO_CHECK_EQ(moo_pTextBox.textBox, original_pTextBox.textBox, "Comparing pTextBox");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF2D0 (#10202)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10202, dll_base + 0x0000F2D0);

		SUBCASE("")
		{
			// Input data
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_scrollbar(moo_pScrollBar, 10, 0);
			setup_scrollbar(original_pScrollBar, 10, 0);
			const int nPageSize = GENERATE(-1, 0, 3, 100);

			// Call both implementations
			sut(&moo_pScrollBar, nPageSize);
			original(&original_pScrollBar, nPageSize);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF300 (#10201)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10201, dll_base + 0x0000F300);

		SUBCASE("")
		{
			// Input data
			const int32_t nPageSize = random_unsigned_integer(0, 100);
			D2WinScrollBarStrc moo_pScrollBar{};
			D2WinScrollBarStrc original_pScrollBar{};
			setup_scrollbar(moo_pScrollBar, 10, 0);
			setup_scrollbar(original_pScrollBar, 10, 0);
			moo_pScrollBar.nPageSize = nPageSize;
			original_pScrollBar.nPageSize = nPageSize;

			// Call both implementations
			const auto moo_result = sut(&moo_pScrollBar);
			const auto original_result = original(&original_pScrollBar);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");

			// Check specific values
			CHECK_EQ(moo_result, nPageSize);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AF330")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_Draw, dll_base + 0x0000F330);

		// NOTE: The state of the mouse buttons is stored in a global variable whose address in the original .dll is unknown.
		// The tests don't press the mouse buttons, so the step indicator is never dragged while drawing.

		// Input data
		const uint32_t dwFlags = GENERATE(0u, 1u, 4u, 5u);
		const int32_t nMaxSteps = GENERATE(0, 1, 7);
		const int32_t nHeight = GENERATE(20, 100);
		const bool bUpperArrowPressed = GENERATE(false, true);
		const bool bLowerArrowPressed = GENERATE(false, true);
		CAPTURE(dwFlags);
		CAPTURE(nMaxSteps);
		CAPTURE(nHeight);
		CAPTURE(bUpperArrowPressed);
		CAPTURE(bLowerArrowPressed);

		D2WinFakeCellFile cellFile("scrollbar", 6);
		D2WinScrollBarStrc moo_pScrollBar{};
		D2WinScrollBarStrc original_pScrollBar{};

		const auto setup_data = [&](
			D2WinScrollBarStrc& pScrollBar
		) {
			setup_scrollbar(pScrollBar, nMaxSteps, nMaxSteps / 2);
			pScrollBar.controlHeader.dwFlags = dwFlags;
			pScrollBar.controlHeader.nHeight = nHeight;
			pScrollBar.controlHeader.pCellFile = cellFile.get();
			pScrollBar.bIsUpperArrowPressed = bUpperArrowPressed;
			pScrollBar.bIsLowerArrowPressed = bLowerArrowPressed;
			pScrollBar.bIsStepIndicatorDragged = 1;
		};

		setup_data(moo_pScrollBar);
		setup_data(original_pScrollBar);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pScrollBar.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pScrollBar.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AF4D0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_HandleMouseDown, dll_base + 0x0000F4D0);

		// Input data
		const UINT nMessage = GENERATE(WM_LBUTTONDOWN, WM_RBUTTONDOWN);
		const int32_t nMouseX = GENERATE(95, 105);
		// Upper arrow, track above the step indicator, step indicator, track below the step indicator, lower arrow
		const int32_t nMouseY = GENERATE(205, 215, 246, 270, 295);
		const int32_t nMaxSteps = GENERATE(0, 1, 10, 100);
		const int32_t nPageSize = GENERATE(0, 3);
		const int32_t nState = GENERATE(0, 1, 2, 3);
		CAPTURE(nMessage);
		CAPTURE(nMouseX);
		CAPTURE(nMouseY);
		CAPTURE(nMaxSteps);
		CAPTURE(nPageSize);
		CAPTURE(nState);

		D2WinScrollBarStrc moo_pScrollBar{};
		D2WinScrollBarStrc original_pScrollBar{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinScrollBarStrc& pScrollBar,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_scrollbar(pScrollBar, nMaxSteps, nMaxSteps / 2);
			pScrollBar.nPageSize = nPageSize;
			pScrollBar.bIsUpperArrowPressed = nState == 1;
			pScrollBar.bIsLowerArrowPressed = nState == 2;
			pScrollBar.bIsStepIndicatorDragged = nState == 3;
			pScrollBar.pfOnScroll = D2WinCallbacks::VoidCallback;
			pScrollBar.controlHeader.pfCallback = D2WinCallbacks::Callback;
			pMsg.hWindow = reinterpret_cast<HWND>(&pScrollBar);
			pMsg.nMessage = nMessage;
		};

		setup_data(moo_pScrollBar, moo_pMsg);
		setup_data(original_pScrollBar, original_pMsg);
		set_mouse_position(nMouseX, nMouseY);
		D2WinCallLog::name_pointer(&moo_pScrollBar, "pScrollBar");
		D2WinCallLog::name_pointer(&original_pScrollBar, "pScrollBar");

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
		MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8AF6B0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(SCROLLBAR_HandleMouseUp, dll_base + 0x0000F6B0);

		// Input data
		const int32_t nState = GENERATE(0, 1, 2, 3);
		CAPTURE(nState);

		D2WinScrollBarStrc moo_pScrollBar{};
		D2WinScrollBarStrc original_pScrollBar{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [nState](
			D2WinScrollBarStrc& pScrollBar,
			SMSGHANDLER_PARAMS& pMsg
		) {
			setup_scrollbar(pScrollBar, 10, 5);
			pScrollBar.bIsUpperArrowPressed = nState == 1;
			pScrollBar.bIsLowerArrowPressed = nState == 2;
			pScrollBar.bIsStepIndicatorDragged = nState == 3;
			pMsg.hWindow = reinterpret_cast<HWND>(&pScrollBar);
			pMsg.nMessage = WM_LBUTTONUP;
		};

		setup_data(moo_pScrollBar, moo_pMsg);
		setup_data(original_pScrollBar, original_pMsg);

		// Call both implementations
		const auto moo_result = sut(&moo_pMsg);
		const auto original_result = original(&original_pMsg);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pScrollBar, original_pScrollBar, "Comparing pScrollBar");
	}
}

#endif
