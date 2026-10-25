#include <D2WinTestDefines.h>

#ifdef POPUP_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cwchar>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinPopUp.h>


// NOTE: The pop up created by POPUP_Create is stored in a global variable whose address in the original .dll is unknown.
// It is retrieved from the control list instead, and the tests destroy it before returning.
TEST_SUITE("D2WinPopUpTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	const auto original_POPUP_Create = reinterpret_cast<decltype(&POPUP_Create)>(dll_base + 0x0000EAE0);
	const auto original_POPUP_Destroy = reinterpret_cast<decltype(&POPUP_Destroy)>(dll_base + 0x0000EBA0);

	// Creates the pop up of both implementations at the current mouse position
	struct PopUpPair
	{
		D2WinPopUpStrc* moo = nullptr;
		D2WinPopUpStrc* original = nullptr;

		PopUpPair(D2WinControlState& moo_state, D2WinControlState& original_state)
		{
			POPUP_Create();
			original_POPUP_Create();
			moo = reinterpret_cast<D2WinPopUpStrc*>(moo_state.pControlList);
			original = reinterpret_cast<D2WinPopUpStrc*>(original_state.pControlList);
			REQUIRE(moo != nullptr);
			REQUIRE(original != nullptr);
			D2WinCallLog::name_pointer(moo, "pPopUp");
			D2WinCallLog::name_pointer(original, "pPopUp");
		}

		~PopUpPair()
		{
			POPUP_Destroy();
			original_POPUP_Destroy();
		}
	};

	void add_line(D2WinPopUpStrc* pPopUp, const wchar_t* wszText, void(__stdcall* pfHandleMouseInput)())
	{
		D2WinPopUpLineStrc& line = pPopUp->lines[pPopUp->nLines];
		std::wcscpy(line.wszText, wszText);
		line.pfHandleMouseInput = pfHandleMouseInput;
		++pPopUp->nLines;
		pPopUp->controlHeader.nHeight = 20 * pPopUp->nLines;
		pPopUp->controlHeader.nWidth = 100;
	}


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEAE0 (#10094)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(POPUP_Create, dll_base + 0x0000EAE0);

		set_mouse_position(random_unsigned_integer(0, 800), random_unsigned_integer(0, 600));

		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();

			// Compare the created pop ups
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			REQUIRE(moo_state.pControlList != nullptr);
			REQUIRE(original_state.pControlList != nullptr);
			CHECK_EQ(moo_state.pControlList->pfDraw, &POPUP_Draw);
			CHECK_EQ(moo_state.pControlList->pfInitialize, &POPUP_Initialize);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_state.pControlList->pfDraw), dll_base + 0x0000EDB0);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_state.pControlList->pfInitialize), dll_base + 0x0000ED10);
		}

		SUBCASE("Replaces the previous pop up")
		{
			sut();
			original();

			// Call both implementations
			sut();
			original();

			// Compare the created pop ups
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
			REQUIRE(moo_state.pRemovedControlList != nullptr);
			CHECK_EQ(moo_state.pControlList->pNext, nullptr);
		}

		POPUP_Destroy();
		original_POPUP_Destroy();
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEBA0 (#10095)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(POPUP_Destroy, dll_base + 0x0000EBA0);

		SUBCASE("")
		{
			POPUP_Create();
			original_POPUP_Create();

			// Call both implementations
			sut();
			original();

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
			CHECK_EQ(moo_state.pControlList, nullptr);
		}

		SUBCASE("Without pop up")
		{
			// Call both implementations
			sut();
			original();

			// Compare potentially modified input data
			CHECK_EQ(moo_state.pRemovedControlList, nullptr);
			CHECK_EQ(original_state.pRemovedControlList, nullptr);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEBC0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(POPUP_IsActive, dll_base + 0x0000EBC0);

		SUBCASE("Without pop up")
		{
			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}

		SUBCASE("With pop up")
		{
			const uint32_t dwFlags = GENERATE(0u, 1u, 4u, 5u, 13u);
			PopUpPair popUps(moo_state, original_state);
			popUps.moo->controlHeader.dwFlags = dwFlags;
			popUps.original->controlHeader.dwFlags = dwFlags;

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEC10 (#10096)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(POPUP_AddLine, dll_base + 0x0000EC10);

		SUBCASE("")
		{
			// Input data
			const int32_t nExistingLines = GENERATE(0, 3, 7, 8);
			const wchar_t* wszText = GENERATE(L"", L"Line", L"A much longer line of the pop up");
			PopUpPair popUps(moo_state, original_state);
			for (int32_t i = 0; i < nExistingLines; ++i)
			{
				add_line(popUps.moo, L"Existing", nullptr);
				add_line(popUps.original, L"Existing", nullptr);
			}

			D2WinPopUpLineStrc moo_pPopUpLine{};
			D2WinPopUpLineStrc original_pPopUpLine{};
			std::wcscpy(moo_pPopUpLine.wszText, wszText);
			std::wcscpy(original_pPopUpLine.wszText, wszText);
			moo_pPopUpLine.pfHandleMouseInput = D2WinCallbacks::PopUpLineCallback;
			original_pPopUpLine.pfHandleMouseInput = D2WinCallbacks::PopUpLineCallback;

			// Call both implementations
			const auto moo_result = sut(&moo_pPopUpLine);
			const auto original_result = original(&original_pPopUpLine);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(popUps.moo, popUps.original, "Comparing pop up");
			MOO_CHECK_EQ(moo_pPopUpLine, original_pPopUpLine, "Comparing pPopUpLine");
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AECA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(POPUP_HandleMouseButtonInput, dll_base + 0x0000ECA0);

		SUBCASE("")
		{
			// Input data
			const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
			const int32_t nCurrentLine = GENERATE(-1, 0, 1);
			CAPTURE(dwFlags);
			CAPTURE(nCurrentLine);

			PopUpPair popUps(moo_state, original_state);
			for (D2WinPopUpStrc* pPopUp : { popUps.moo, popUps.original })
			{
				add_line(pPopUp, L"With callback", D2WinCallbacks::PopUpLineCallback);
				add_line(pPopUp, L"Without callback", nullptr);
				pPopUp->controlHeader.dwFlags = dwFlags;
				pPopUp->nCurrentLine = nCurrentLine;
			}

			SMSGHANDLER_PARAMS moo_pMsg{};
			SMSGHANDLER_PARAMS original_pMsg{};
			moo_pMsg.nMessage = WM_LBUTTONDOWN;
			original_pMsg.nMessage = WM_LBUTTONDOWN;

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
			MOO_CHECK_EQ(popUps.moo, popUps.original, "Comparing pop up");
			MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AED10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(POPUP_Initialize, dll_base + 0x0000ED10);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		// Pop up at x = [100, 200], y = [160, 200]
		const int32_t nMouseX = GENERATE(99, 100, 150, 200, 201);
		const int32_t nMouseY = GENERATE(159, 160, 170, 185, 200, 201);
		CAPTURE(dwFlags);
		CAPTURE(nMouseX);
		CAPTURE(nMouseY);

		D2WinPopUpStrc moo_pPopUp{};
		D2WinPopUpStrc original_pPopUp{};

		const auto setup_data = [&](
			D2WinPopUpStrc& pPopUp
		) {
			d2win_init_control(pPopUp.controlHeader, D2WIN_POPUP, 100, 200, 0, 0);
			add_line(&pPopUp, L"First", nullptr);
			add_line(&pPopUp, L"Second", nullptr);
			pPopUp.controlHeader.dwFlags = dwFlags;
			pPopUp.nCurrentLine = 5;
		};

		setup_data(moo_pPopUp);
		setup_data(original_pPopUp);
		set_mouse_position(nMouseX, nMouseY);

		// Call both implementations
		const auto moo_result = sut(&moo_pPopUp.controlHeader);
		const auto original_result = original(&original_pPopUp.controlHeader);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pPopUp, original_pPopUp, "Comparing pPopUp");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEDB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(POPUP_Draw, dll_base + 0x0000EDB0);

		// Input data
		const uint32_t dwFlags = GENERATE(5u, 4u, 1u);
		const int32_t nLines = GENERATE(0, 1, 3);
		const int32_t nCurrentLine = GENERATE(-1, 0, 2);
		CAPTURE(dwFlags);
		CAPTURE(nLines);
		CAPTURE(nCurrentLine);

		D2WinPopUpStrc moo_pPopUp{};
		D2WinPopUpStrc original_pPopUp{};

		const auto setup_data = [&](
			D2WinPopUpStrc& pPopUp
		) {
			d2win_init_control(pPopUp.controlHeader, D2WIN_POPUP, 100, 200, 0, 0);
			for (int32_t i = 0; i < nLines; ++i)
			{
				add_line(&pPopUp, i % 2 ? L"Odd line" : L"Even line", nullptr);
			}

			pPopUp.controlHeader.dwFlags = dwFlags;
			pPopUp.nCurrentLine = nCurrentLine;
		};

		setup_data(moo_pPopUp);
		setup_data(original_pPopUp);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pPopUp.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pPopUp.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pPopUp, original_pPopUp, "Comparing pPopUp");
		CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
	}
}

#endif
