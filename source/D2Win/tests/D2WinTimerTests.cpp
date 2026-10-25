#include <D2WinTestDefines.h>

#ifdef TIMER_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinTimer.h>


TEST_SUITE("D2WinTimerTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1B70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TIMER_Create, dll_base + 0x00011B70);

		SUBCASE("")
		{
			const uint32_t nTimeout = random_unsigned_integer(1, 100);

			// Call both implementations
			D2WinTimerStrc* moo_result = sut(nTimeout, D2WinCallbacks::Callback);
			D2WinTimerStrc* original_result = original(nTimeout, D2WinCallbacks::Callback);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfHandleVirtualKeyInput != nullptr, original_result->controlHeader.pfHandleVirtualKeyInput != nullptr);
			CHECK_EQ(moo_result->controlHeader.pfInitialize != nullptr, original_result->controlHeader.pfInitialize != nullptr);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1BF0 (#10181)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TIMER_Destroy, dll_base + 0x00011BF0);

		// Input data
		D2WinTimerStrc* moo_pTimers[3] = {};
		D2WinTimerStrc* original_pTimers[3] = {};

		for (int i = 0; i < 3; ++i)
		{
			moo_pTimers[i] = d2win_calloc<D2WinTimerStrc>();
			original_pTimers[i] = d2win_calloc<D2WinTimerStrc>();
			d2win_init_control(moo_pTimers[i]->controlHeader, D2WIN_TIMER);
			d2win_init_control(original_pTimers[i]->controlHeader, D2WIN_TIMER);
			moo_pTimers[i]->nTimeout = i;
			original_pTimers[i]->nTimeout = i;

			if (i > 0)
			{
				moo_pTimers[i - 1]->controlHeader.pNext = &moo_pTimers[i]->controlHeader;
				original_pTimers[i - 1]->controlHeader.pNext = &original_pTimers[i]->controlHeader;
			}
		}

		moo_state.pControlList = &moo_pTimers[0]->controlHeader;
		original_state.pControlList = &original_pTimers[0]->controlHeader;

		const int nIndex = GENERATE(0, 1, 2);
		CAPTURE(nIndex);

		// Call both implementations
		const auto moo_result = sut(&moo_pTimers[nIndex]->controlHeader);
		const auto original_result = original(&original_pTimers[nIndex]->controlHeader);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
		MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");

		// Check specific values
		CHECK_EQ(moo_state.pRemovedControlList, &moo_pTimers[nIndex]->controlHeader);
		CHECK_EQ(moo_pTimers[nIndex]->controlHeader.pNext, nullptr);

		// Not in the list anymore
		CHECK_EQ(sut(&moo_pTimers[nIndex]->controlHeader), original(&original_pTimers[nIndex]->controlHeader));
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1C00 (#10180)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10180, dll_base + 0x00011C00);

		SUBCASE("")
		{
			// Input data
			D2WinTimerStrc moo_pTimer{};
			D2WinTimerStrc original_pTimer{};

			const auto setup_data = [](
				D2WinTimerStrc& pTimer
			) {
				d2win_init_control(pTimer.controlHeader, D2WIN_TIMER);
				pTimer.controlHeader.pfHandleVirtualKeyInput = D2WinCallbacks::Callback;
				pTimer.nTimeout = 5;
			};

			setup_data(moo_pTimer);
			setup_data(original_pTimer);

			// Call both implementations
			sut(&moo_pTimer);
			original(&original_pTimer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");

			// Check specific values
			CHECK_EQ(moo_pTimer.controlHeader.pfHandleVirtualKeyInput, original_pTimer.controlHeader.pfHandleVirtualKeyInput);
			CHECK_EQ(moo_pTimer.controlHeader.pfHandleVirtualKeyInput, nullptr);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1C30 (#10182)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10182, dll_base + 0x00011C30);

		SUBCASE("")
		{
			// Input data
			D2WinTimerStrc moo_pTimer{};
			D2WinTimerStrc original_pTimer{};

			const auto setup_data = [](
				D2WinTimerStrc& pTimer
			) {
				d2win_init_control(pTimer.controlHeader, D2WIN_TIMER);
				pTimer.nTimeout = 5;
			};

			setup_data(moo_pTimer);
			setup_data(original_pTimer);

			// Call both implementations
			sut(&moo_pTimer);
			original(&original_pTimer);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");

			// Check specific values: both implementations use their own TIMER_UpdateInterval
			CHECK_EQ(moo_pTimer.controlHeader.pfInitialize, &TIMER_UpdateInterval);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_pTimer.controlHeader.pfInitialize), dll_base + 0x00011CF0);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1C60")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TIMER_UpdateTimeout, dll_base + 0x00011C60);

		// Input data
		const uint32_t dwFlags = GENERATE(0u, 1u, 4u, 5u);
		const bool bElapsed = GENERATE(false, true);
		CAPTURE(dwFlags);
		CAPTURE(bElapsed);

		D2WinTimerStrc moo_pTimer{};
		D2WinTimerStrc original_pTimer{};

		const DWORD dwTickCount = GetTickCount();
		const auto setup_data = [dwFlags, bElapsed, dwTickCount](
			D2WinTimerStrc& pTimer
		) {
			d2win_init_control(pTimer.controlHeader, D2WIN_TIMER);
			pTimer.controlHeader.dwFlags = dwFlags;
			pTimer.controlHeader.pfCallback = D2WinCallbacks::Callback;
			// The timeout is in seconds
			pTimer.nTimeout = bElapsed ? 2 : 1000;
			pTimer.dwTickCount = dwTickCount - 10000;
		};

		setup_data(moo_pTimer);
		setup_data(original_pTimer);
		D2WinCallLog::name_pointer(&moo_pTimer, "pTimer");
		D2WinCallLog::name_pointer(&original_pTimer, "pTimer");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pTimer.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pTimer.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1CF0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TIMER_UpdateInterval, dll_base + 0x00011CF0);

		// NOTE: The time of the next call is stored in a global variable of each implementation whose address in the original .dll is unknown.
		// The first call of each subcase brings this variable in a known state.

		// Input data
		D2WinTimerStrc moo_pTimer{};
		D2WinTimerStrc original_pTimer{};

		const auto setup_data = [](
			D2WinTimerStrc& pTimer,
			uint32_t nTimeout
		) {
			d2win_init_control(pTimer.controlHeader, D2WIN_TIMER);
			pTimer.controlHeader.pfCallback = D2WinCallbacks::Callback;
			pTimer.nTimeout = nTimeout;
		};

		D2WinCallLog::name_pointer(&moo_pTimer, "pTimer");
		D2WinCallLog::name_pointer(&original_pTimer, "pTimer");

		SUBCASE("Interval elapsed")
		{
			setup_data(moo_pTimer, 0);
			setup_data(original_pTimer, 0);

			sut(&moo_pTimer.controlHeader);
			original(&original_pTimer.controlHeader);

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(&moo_pTimer.controlHeader);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(&original_pTimer.controlHeader);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);
			CHECK_FALSE(moo_calls.empty());

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");
		}

		SUBCASE("Interval not elapsed")
		{
			setup_data(moo_pTimer, 0x10000000);
			setup_data(original_pTimer, 0x10000000);

			sut(&moo_pTimer.controlHeader);
			original(&original_pTimer.controlHeader);

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(&moo_pTimer.controlHeader);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(&original_pTimer.controlHeader);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);
			CHECK(moo_calls.empty());

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");
		}

		SUBCASE("Disabled")
		{
			const uint32_t dwFlags = GENERATE(0u, 1u, 4u);
			setup_data(moo_pTimer, 0);
			setup_data(original_pTimer, 0);
			moo_pTimer.controlHeader.dwFlags = dwFlags;
			original_pTimer.controlHeader.dwFlags = dwFlags;

			// Call both implementations
			D2WinCallLog::clear();
			const auto moo_result = sut(&moo_pTimer.controlHeader);
			const auto moo_calls = D2WinCallLog::take();
			const auto original_result = original(&original_pTimer.controlHeader);
			const auto original_calls = D2WinCallLog::take();

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
			CHECK_EQ(moo_calls, original_calls);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");
		}

		// Restore a short interval, the subcases with a long interval would otherwise block the other subcases
		setup_data(moo_pTimer, 0);
		setup_data(original_pTimer, 0);
		moo_pTimer.controlHeader.pfCallback = nullptr;
		original_pTimer.controlHeader.pfCallback = nullptr;
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1D70")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(TIMER_HandleVirtualKeyInput, dll_base + 0x00011D70);

		// Input data
		const UINT nMessage = GENERATE(WM_KEYDOWN, WM_CHAR);
		const WPARAM wParam = GENERATE(VK_SPACE, VK_RETURN, 'a');
		const bool bHasCallback = GENERATE(true, false);
		CAPTURE(nMessage);
		CAPTURE(wParam);
		CAPTURE(bHasCallback);

		D2WinTimerStrc moo_pTimer{};
		D2WinTimerStrc original_pTimer{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [nMessage, wParam, bHasCallback](
			D2WinTimerStrc& pTimer,
			SMSGHANDLER_PARAMS& pMsg
		) {
			d2win_init_control(pTimer.controlHeader, D2WIN_TIMER);
			pTimer.controlHeader.pfCallback = bHasCallback ? D2WinCallbacks::Callback : nullptr;
			pMsg.hWindow = reinterpret_cast<HWND>(&pTimer);
			pMsg.nMessage = nMessage;
			pMsg.wParam = wParam;
		};

		setup_data(moo_pTimer, moo_pMsg);
		setup_data(original_pTimer, original_pMsg);
		D2WinCallLog::name_pointer(&moo_pTimer, "pTimer");
		D2WinCallLog::name_pointer(&original_pTimer, "pTimer");

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
		MOO_CHECK_EQ(moo_pTimer, original_pTimer, "Comparing pTimer");
	}
}

#endif
