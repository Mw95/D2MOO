#include <D2WinTestDefines.h>

#ifdef IMAGE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinImage.h>


TEST_SUITE("D2WinImageTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8ABA90 (#10084)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE2_Create, dll_base + 0x0000BA90);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("image", 4);
			D2WinImageClickRectStrc clickRects[2] = { { 1, 2, 3, 4, D2WinCallbacks::Callback2 }, {} };
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = random_unsigned_integer(1, 800);
			const int32_t nHeight = random_unsigned_integer(1, 600);
			D2WinImageClickRectStrc* pClickRect = GENERATE(true, false) ? clickRects : nullptr;
			int32_t(__stdcall* pfHandleVirtualKeyInput)(SMSGHANDLER_PARAMS*) = GENERATE(D2WinCallbacks::Callback2, nullptr);

			// Call both implementations
			D2WinImage2Strc* moo_result = sut(nX, nY, nWidth, nHeight, cellFile.get(), D2WinCallbacks::Callback, pClickRect, pfHandleVirtualKeyInput);
			D2WinImage2Strc* original_result = original(nX, nY, nWidth, nHeight, cellFile.get(), D2WinCallbacks::Callback, pClickRect, pfHandleVirtualKeyInput);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfHandleVirtualKeyInput, pfHandleVirtualKeyInput);
			CHECK_EQ(original_result->controlHeader.pfHandleVirtualKeyInput, pfHandleVirtualKeyInput);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &IMAGE2_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &IMAGE2_HandleMouseDown);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x0000BD50);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x0000C170);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1BF0 (#10085)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE_Destroy, dll_base + 0x00011BF0);

		SUBCASE("")
		{
			// Input data
			D2WinImageStrc* moo_pImage = d2win_calloc<D2WinImageStrc>();
			D2WinImageStrc* original_pImage = d2win_calloc<D2WinImageStrc>();
			D2WinImageStrc* moo_pOther = d2win_calloc<D2WinImageStrc>();
			D2WinImageStrc* original_pOther = d2win_calloc<D2WinImageStrc>();
			d2win_init_control(moo_pImage->controlHeader, D2WIN_IMAGE);
			d2win_init_control(original_pImage->controlHeader, D2WIN_IMAGE);
			d2win_init_control(moo_pOther->controlHeader, D2WIN_IMAGE, 1, 2, 3, 4);
			d2win_init_control(original_pOther->controlHeader, D2WIN_IMAGE, 1, 2, 3, 4);
			moo_pOther->controlHeader.pNext = &moo_pImage->controlHeader;
			original_pOther->controlHeader.pNext = &original_pImage->controlHeader;
			moo_state.pControlList = &moo_pOther->controlHeader;
			original_state.pControlList = &original_pOther->controlHeader;

			// Call both implementations
			const auto moo_result = sut(&moo_pImage->controlHeader);
			const auto original_result = original(&original_pImage->controlHeader);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8ABB40")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE_Create, dll_base + 0x0000BB40);

		SUBCASE("")
		{
			D2WinFakeCellFile cellFile("image", 1);
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);
			const int32_t nWidth = random_unsigned_integer(1, 800);
			const int32_t nHeight = random_unsigned_integer(1, 600);
			const int32_t nBorderWidth = random_unsigned_integer(0, 100);
			const int32_t nBorderHeight = random_unsigned_integer(0, 100);

			// Call both implementations
			D2WinImageStrc* moo_result = sut(nX, nY, nWidth, nHeight, cellFile.get(), nBorderWidth, nBorderHeight);
			D2WinImageStrc* original_result = original(nX, nY, nWidth, nHeight, cellFile.get(), nBorderWidth, nBorderHeight);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &IMAGE_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &IMAGE2_HandleMouseDown);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x0000BEA0);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x0000C170);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ABC00 (#10086)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE_SetCellFile, dll_base + 0x0000BC00);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile oldCellFile("old", 1);
			D2WinFakeCellFile newCellFile("new", 1);
			D2WinImageClickRectStrc oldClickRect = { 1, 2, 3, 4, D2WinCallbacks::Callback };
			D2WinImageClickRectStrc newClickRect = { 5, 6, 7, 8, D2WinCallbacks::Callback2 };
			D2CellFileStrc* pCellFile = GENERATE(true, false) ? newCellFile.get() : nullptr;
			D2WinImageClickRectStrc* pClickRect = GENERATE(true, false) ? &newClickRect : nullptr;

			D2WinImageStrc moo_pImage{};
			D2WinImageStrc original_pImage{};

			const auto setup_data = [&](
				D2WinImageStrc& pImage
			) {
				d2win_init_control(pImage.controlHeader, D2WIN_IMAGE);
				pImage.controlHeader.pCellFile = oldCellFile.get();
				pImage.pClickRect = &oldClickRect;
			};

			setup_data(moo_pImage);
			setup_data(original_pImage);

			// Call both implementations
			const auto moo_result = sut(&moo_pImage, pCellFile, pClickRect);
			const auto original_result = original(&original_pImage, pCellFile, pClickRect);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");

			// Check specific values
			CHECK_EQ(moo_pImage.pClickRect, pClickRect);
			CHECK_EQ(original_pImage.pClickRect, pClickRect);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ABC40 (#10087)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE_SetCoordinates, dll_base + 0x0000BC40);

		SUBCASE("")
		{
			// Input data
			D2WinImageStrc moo_pImage{};
			D2WinImageStrc original_pImage{};
			d2win_init_control(moo_pImage.controlHeader, D2WIN_IMAGE);
			d2win_init_control(original_pImage.controlHeader, D2WIN_IMAGE);
			const int32_t nX = random_unsigned_integer(0, 800);
			const int32_t nY = random_unsigned_integer(0, 600);

			// Call both implementations
			const auto moo_result = sut(&moo_pImage, nX, nY);
			const auto original_result = original(&original_pImage, nX, nY);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8ABC80 (#10088)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE_SetFrame, dll_base + 0x0000BC80);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("image", 5);
			const int32_t nFrame = GENERATE(-2, 0, 3, 4, 5, 20);

			D2WinImageStrc moo_pImage{};
			D2WinImageStrc original_pImage{};

			const auto setup_data = [&](
				D2WinImageStrc& pImage
			) {
				d2win_init_control(pImage.controlHeader, D2WIN_IMAGE);
				pImage.controlHeader.pCellFile = cellFile.get();
				pImage.nFrame = 1;
			};

			setup_data(moo_pImage);
			setup_data(original_pImage);

			// Call both implementations
			const auto moo_result = sut(&moo_pImage, nFrame);
			const auto original_result = original(&original_pImage, nFrame);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8ABCD0 (#10089)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE_ForceNormalDrawMode, dll_base + 0x0000BCD0);

		SUBCASE("")
		{
			// Input data
			D2WinImageStrc moo_pImage{};
			D2WinImageStrc original_pImage{};
			d2win_init_control(moo_pImage.controlHeader, D2WIN_IMAGE);
			d2win_init_control(original_pImage.controlHeader, D2WIN_IMAGE);
			moo_pImage.eDrawMode = DRAWMODE_TRANS50;
			original_pImage.eDrawMode = DRAWMODE_TRANS50;
			const int32_t nUnused = random_unsigned_integer();

			// Call both implementations
			const auto moo_result = sut(&moo_pImage, nUnused);
			const auto original_result = original(&original_pImage, nUnused);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");

			// Check specific values
			CHECK_EQ(moo_pImage.eDrawMode, DRAWMODE_NORMAL);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8ABD10 (#10090)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE_GetFrameCount, dll_base + 0x0000BD10);

		SUBCASE("")
		{
			// Input data
			const int32_t nFrames = GENERATE(0, 1, 13);
			D2WinFakeCellFile cellFile("image", nFrames);
			D2WinImageStrc moo_pImage{};
			D2WinImageStrc original_pImage{};
			d2win_init_control(moo_pImage.controlHeader, D2WIN_IMAGE);
			d2win_init_control(original_pImage.controlHeader, D2WIN_IMAGE);
			moo_pImage.controlHeader.pCellFile = cellFile.get();
			original_pImage.controlHeader.pCellFile = cellFile.get();

			// Call both implementations
			const auto moo_result = sut(&moo_pImage);
			const auto original_result = original(&original_pImage);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");

			// Check specific values
			CHECK_EQ(moo_result, nFrames);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8ABD50")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE2_Draw, dll_base + 0x0000BD50);

		// Input data
		const uint32_t dwFlags = GENERATE(0u, 1u, 4u, 5u);
		const bool bHasCellFile = GENERATE(true, false);
		const int32_t nWidth = GENERATE(1, 256, 300, 800);
		const int32_t nHeight = GENERATE(1, 256, 600);
		CAPTURE(dwFlags);
		CAPTURE(bHasCellFile);
		CAPTURE(nWidth);
		CAPTURE(nHeight);

		D2WinFakeCellFile cellFile("image", 12);
		D2WinImage2Strc moo_pImage{};
		D2WinImage2Strc original_pImage{};

		const auto setup_data = [&](
			D2WinImage2Strc& pImage
		) {
			d2win_init_control(pImage.controlHeader, D2WIN_IMAGE, 10, 600, nWidth, nHeight);
			pImage.controlHeader.dwFlags = dwFlags;
			pImage.controlHeader.pCellFile = bHasCellFile ? cellFile.get() : nullptr;
			pImage.nFrame = 2;
			pImage.eDrawMode = DRAWMODE_TRANS25;
		};

		setup_data(moo_pImage);
		setup_data(original_pImage);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pImage.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pImage.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8ABEA0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE_Draw, dll_base + 0x0000BEA0);

		// Input data
		// NOTE: The borders must be smaller than the image, which divides by the size of the center of the cell otherwise
		const int32_t nBorderWidth = GENERATE(1, 16, 64);
		const int32_t nBorderHeight = GENERATE(1, 20, 64);
		const int32_t nWidth = GENERATE(128, 256, 300, 700);
		const int32_t nHeight = GENERATE(128, 256, 500);
		CAPTURE(nBorderWidth);
		CAPTURE(nBorderHeight);
		CAPTURE(nWidth);
		CAPTURE(nHeight);

		D2WinFakeCellFile cellFile("image", 1);
		D2WinImageStrc moo_pImage{};
		D2WinImageStrc original_pImage{};

		const auto setup_data = [&](
			D2WinImageStrc& pImage
		) {
			d2win_init_control(pImage.controlHeader, D2WIN_IMAGE, 20, 550, nWidth, nHeight);
			pImage.controlHeader.pCellFile = cellFile.get();
			pImage.nBorderWidth = nBorderWidth;
			pImage.nBorderHeight = nBorderHeight;
		};

		setup_data(moo_pImage);
		setup_data(original_pImage);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pImage.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pImage.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8AC170")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(IMAGE2_HandleMouseDown, dll_base + 0x0000C170);

		// Input data
		const uint32_t dwFlags = GENERATE(0u, 1u, 4u, 5u);
		const bool bHasClickRects = GENERATE(true, false);
		const bool bHasCallback = GENERATE(true, false);
		// Image at x = [100, 220], y = [160, 200]. The click rect is at x = [10, 30], y = [10, 20] relative to the image.
		const int32_t nMouseX = GENERATE(90, 105, 115, 200);
		const int32_t nMouseY = GENERATE(150, 165, 175, 199);
		CAPTURE(dwFlags);
		CAPTURE(bHasClickRects);
		CAPTURE(bHasCallback);
		CAPTURE(nMouseX);
		CAPTURE(nMouseY);

		D2WinImageClickRectStrc clickRects[] =
		{
			{ 10, 20, 20, 10, D2WinCallbacks::Callback2 },
			{ 0, 40, 5, 40, D2WinCallbacks::Callback2 },
			{ 0, 0, 1000, 1000, nullptr }, // Terminator
		};

		D2WinImage2Strc moo_pImage{};
		D2WinImage2Strc original_pImage{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinImage2Strc& pImage,
			SMSGHANDLER_PARAMS& pMsg
		) {
			d2win_init_control(pImage.controlHeader, D2WIN_IMAGE);
			pImage.controlHeader.dwFlags = dwFlags;
			pImage.controlHeader.pfCallback = bHasCallback ? D2WinCallbacks::Callback : nullptr;
			pImage.pClickRect = bHasClickRects ? clickRects : nullptr;
			pMsg.hWindow = reinterpret_cast<HWND>(&pImage);
			pMsg.nMessage = WM_LBUTTONDOWN;
		};

		setup_data(moo_pImage, moo_pMsg);
		setup_data(original_pImage, original_pMsg);
		set_mouse_position(nMouseX, nMouseY);
		D2WinCallLog::name_pointer(&moo_pImage, "pImage");
		D2WinCallLog::name_pointer(&original_pImage, "pImage");

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
		MOO_CHECK_EQ(moo_pImage, original_pImage, "Comparing pImage");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}
}

#endif
