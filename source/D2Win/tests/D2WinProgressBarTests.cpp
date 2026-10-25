#include <D2WinTestDefines.h>

#ifdef PROGRESSBAR_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinProgressBar.h>


TEST_SUITE("D2WinProgressBarTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEED0 (#10091)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PROGRESSBAR_Create, dll_base + 0x0000EED0);

		SUBCASE("")
		{
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = random_unsigned_integer(1, 300);
			const int32_t nHeight = random_unsigned_integer(1, 300);

			// Call both implementations
			D2WinProgressBarStrc* moo_result = sut(nX, nY, nWidth, nHeight);
			D2WinProgressBarStrc* original_result = original(nX, nY, nWidth, nHeight);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &PROGRESSBAR_Draw);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x0000EFB0);
		}

		SUBCASE("Appended to the end of the list")
		{
			D2WinProgressBarStrc* moo_first = sut(1, 2, 3, 4);
			D2WinProgressBarStrc* original_first = original(1, 2, 3, 4);

			// Call both implementations
			D2WinProgressBarStrc* moo_result = sut(5, 6, 7, 8);
			D2WinProgressBarStrc* original_result = original(5, 6, 7, 8);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_first, original_first, "Comparing first progress bar");

			// Check specific values
			CHECK_EQ(moo_state.pControlList, &moo_first->controlHeader);
			CHECK_EQ(moo_first->controlHeader.pNext, &moo_result->controlHeader);
			CHECK_EQ(original_first->controlHeader.pNext, &original_result->controlHeader);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1BF0 (#10092)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PROGRESSBAR_Destroy, dll_base + 0x00011BF0);

		SUBCASE("")
		{
			// Input data
			D2WinProgressBarStrc* moo_pProgressBar = d2win_calloc<D2WinProgressBarStrc>();
			D2WinProgressBarStrc* original_pProgressBar = d2win_calloc<D2WinProgressBarStrc>();

			const auto setup_data = [](
				D2WinProgressBarStrc& pProgressBar
			) {
				d2win_init_control(pProgressBar.controlHeader, D2WIN_PROGRESSBAR);
				pProgressBar.fProgress = 0.5f;
			};

			setup_data(*moo_pProgressBar);
			setup_data(*original_pProgressBar);
			moo_state.pControlList = &moo_pProgressBar->controlHeader;
			original_state.pControlList = &original_pProgressBar->controlHeader;

			// Call both implementations
			const auto moo_result = sut(&moo_pProgressBar->controlHeader);
			const auto original_result = original(&original_pProgressBar->controlHeader);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pProgressBar, original_pProgressBar, "Comparing pProgressBar");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");

			// Check specific values
			CHECK_EQ(moo_state.pRemovedControlList, &moo_pProgressBar->controlHeader);
		}

		SUBCASE("Empty list")
		{
			D2WinProgressBarStrc moo_pProgressBar{};
			D2WinProgressBarStrc original_pProgressBar{};
			d2win_init_control(moo_pProgressBar.controlHeader, D2WIN_PROGRESSBAR);
			d2win_init_control(original_pProgressBar.controlHeader, D2WIN_PROGRESSBAR);

			// Call both implementations
			const auto moo_result = sut(&moo_pProgressBar.controlHeader);
			const auto original_result = original(&original_pProgressBar.controlHeader);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pProgressBar, original_pProgressBar, "Comparing pProgressBar");
			CHECK_EQ(moo_state.pRemovedControlList, nullptr);
			CHECK_EQ(original_state.pRemovedControlList, nullptr);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEF70 (#10093)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PROGRESSBAR_SetProgress, dll_base + 0x0000EF70);

		SUBCASE("")
		{
			// Input data
			D2WinProgressBarStrc moo_pProgressBar{};
			D2WinProgressBarStrc original_pProgressBar{};
			const float fProgress = GENERATE(0.0f, 0.25f, 1.0f, 1.5f, -0.5f);

			const auto setup_data = [](
				D2WinProgressBarStrc& pProgressBar
			) {
				d2win_init_control(pProgressBar.controlHeader, D2WIN_PROGRESSBAR);
			};

			setup_data(moo_pProgressBar);
			setup_data(original_pProgressBar);

			// Call both implementations
			const auto moo_result = sut(&moo_pProgressBar, fProgress);
			const auto original_result = original(&original_pProgressBar, fProgress);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pProgressBar, original_pProgressBar, "Comparing pProgressBar");

			// Check specific values
			CHECK_EQ(moo_pProgressBar.fProgress, fProgress);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AEFB0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(PROGRESSBAR_Draw, dll_base + 0x0000EFB0);

		// Input data
		const uint32_t dwFlags = GENERATE(0u, 1u, 4u, 5u);
		const float fProgress = GENERATE(0.0f, 0.33f, 1.0f);
		CAPTURE(dwFlags);
		CAPTURE(fProgress);

		D2WinProgressBarStrc moo_pProgressBar{};
		D2WinProgressBarStrc original_pProgressBar{};

		const auto setup_data = [dwFlags, fProgress](
			D2WinProgressBarStrc& pProgressBar
		) {
			d2win_init_control(pProgressBar.controlHeader, D2WIN_PROGRESSBAR, 50, 300, 200, 20);
			pProgressBar.controlHeader.dwFlags = dwFlags;
			pProgressBar.fProgress = fProgress;
		};

		setup_data(moo_pProgressBar);
		setup_data(original_pProgressBar);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pProgressBar.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pProgressBar.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pProgressBar, original_pProgressBar, "Comparing pProgressBar");
	}
}

#endif
