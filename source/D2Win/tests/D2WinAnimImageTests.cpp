#include <D2WinTestDefines.h>

#ifdef ANIMIMAGE_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <filesystem>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinAnimImage.h>


TEST_SUITE("D2WinAnimImageTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	// Animations indexed by the animation type of the image (0 = idle, 1 = hovered, 2 = pressed, 3 = pressed idle, 4 = released)
	struct AnimatedImageDescriptors
	{
		D2WinFakeCellFile cellFiles[5] =
		{
			{ "anim0", 10, 50, 40 },
			{ "anim1", 8, 60, 30 },
			{ "anim2", 6, 70, 20 },
			{ "anim3", 1, 80, 10 },
			{ "anim4", 4, 90, 50 },
		};
		D2WinFakeCellFile overlay{ "overlay", 3 };
		D2CellFileStrc* pCellFiles[5] = {};
		D2CellFileStrc* pOverlay = nullptr;
		D2AnimatedImageDescriptor descriptors[5] = {};

		AnimatedImageDescriptors()
		{
			pOverlay = overlay.get();
			for (int i = 0; i < 5; ++i)
			{
				pCellFiles[i] = cellFiles[i].get();
				descriptors[i].ppCellFile1 = &pCellFiles[i];
				descriptors[i].ppCellFile2 = i == 1 ? &pOverlay : nullptr;
				descriptors[i].eDrawMode = i == 1 ? DRAWMODE_TRANS50 : DRAWMODE_NORMAL;
				descriptors[i].nAnimSpeed = i == 3 ? 0 : 2;
			}
		}
	};


	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A53B0 (#10102)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ANIMIMAGE_Create, dll_base + 0x000053B0);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile cellFile("anim", 5);
			AnimatedImageDescriptors descriptors;
			const int nX = random_unsigned_integer(0, 800);
			const int nY = random_unsigned_integer(0, 600);
			const int nWidth = random_unsigned_integer(1, 300);
			const int nHeight = random_unsigned_integer(1, 300);
			const uint32_t nAnimSpeed = random_unsigned_integer(0, 10);
			D2AnimatedImageDescriptor* pDescriptor = GENERATE(true, false) ? descriptors.descriptors : nullptr;
			const DrawMode eDrawMode = GENERATE(DRAWMODE_NORMAL, DRAWMODE_TRANS25, DRAWMODE_TRANS75);

			// Call both implementations
			D2WinAnimImageStrc* moo_result = sut(nX, nY, nWidth, nHeight, cellFile.get(), nAnimSpeed, D2WinCallbacks::Callback, pDescriptor, eDrawMode, D2WinCallbacks::VoidCallback);
			D2WinAnimImageStrc* original_result = original(nX, nY, nWidth, nHeight, cellFile.get(), nAnimSpeed, D2WinCallbacks::Callback, pDescriptor, eDrawMode, D2WinCallbacks::VoidCallback);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Check specific values
			REQUIRE(moo_result != nullptr);
			REQUIRE(original_result != nullptr);
			CHECK_EQ(moo_state.pControlList, &moo_result->controlHeader);
			CHECK_EQ(original_state.pControlList, &original_result->controlHeader);
			CHECK_EQ(moo_result->controlHeader.pfDraw, &ANIMIMAGE_Draw);
			CHECK_EQ(moo_result->controlHeader.pfHandleMouseDown, &ANIMIMAGE_HandleMouseDown);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfDraw), dll_base + 0x00005610);
			CHECK_EQ(reinterpret_cast<uintptr_t>(original_result->controlHeader.pfHandleMouseDown), dll_base + 0x00005900);
			CHECK_EQ(moo_result->controlHeader.pfShouldMouseInputBeHandled != nullptr, original_result->controlHeader.pfShouldMouseInputBeHandled != nullptr);
			CHECK_EQ(moo_result->controlHeader.pfShouldMouseInputBeHandled != nullptr, pDescriptor != nullptr);
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8B1BF0 (#10103)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ANIMIMAGE_Destroy, dll_base + 0x00011BF0);

		SUBCASE("")
		{
			// Input data
			D2WinAnimImageStrc* moo_pAnimImage = d2win_calloc<D2WinAnimImageStrc>();
			D2WinAnimImageStrc* original_pAnimImage = d2win_calloc<D2WinAnimImageStrc>();
			d2win_init_control(moo_pAnimImage->controlHeader, D2WIN_IMAGE);
			d2win_init_control(original_pAnimImage->controlHeader, D2WIN_IMAGE);
			moo_state.pControlList = &moo_pAnimImage->controlHeader;
			original_state.pControlList = &original_pAnimImage->controlHeader;

			// Call both implementations
			const auto moo_result = sut(&moo_pAnimImage->controlHeader);
			const auto original_result = original(&original_pAnimImage->controlHeader);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAnimImage, original_pAnimImage, "Comparing pAnimImage");
			MOO_CHECK_EQ(moo_state.pControlList, original_state.pControlList, "Comparing control list");
			MOO_CHECK_EQ(moo_state.pRemovedControlList, original_state.pRemovedControlList, "Comparing removed control list");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A54A0 (#10106)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10106, dll_base + 0x000054A0);

		SUBCASE("")
		{
			// Input data
			const int32_t nAnimType = GENERATE(0, 1, 2, 3, 4);
			D2WinAnimImageStrc moo_pAnimImage{};
			D2WinAnimImageStrc original_pAnimImage{};
			d2win_init_control(moo_pAnimImage.controlHeader, D2WIN_IMAGE);
			d2win_init_control(original_pAnimImage.controlHeader, D2WIN_IMAGE);
			moo_pAnimImage.nAnimType = nAnimType;
			original_pAnimImage.nAnimType = nAnimType;

			// Call both implementations
			const auto moo_result = sut(&moo_pAnimImage);
			const auto original_result = original(&original_pAnimImage);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAnimImage, original_pAnimImage, "Comparing pAnimImage");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A54D0 (#10104)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10104, dll_base + 0x000054D0);

		SUBCASE("")
		{
			// Input data
			const int32_t nAnimType = GENERATE(0, 1, 2, 3, 4);
			D2WinAnimImageStrc moo_pAnimImage{};
			D2WinAnimImageStrc original_pAnimImage{};

			const auto setup_data = [nAnimType](
				D2WinAnimImageStrc& pAnimImage
			) {
				d2win_init_control(pAnimImage.controlHeader, D2WIN_IMAGE);
				pAnimImage.nAnimType = nAnimType;
				pAnimImage.nFrame = 3;
			};

			setup_data(moo_pAnimImage);
			setup_data(original_pAnimImage);

			// Call both implementations
			const auto moo_result = sut(&moo_pAnimImage);
			const auto original_result = original(&original_pAnimImage);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAnimImage, original_pAnimImage, "Comparing pAnimImage");
		}
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A5530")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ANIMIMAGE_ShouldMouseInputBeHandled, dll_base + 0x00005530);

		// Input data
		const int32_t nAnimType = GENERATE(0, 1, 4);
		// The image is at (100, 200), the hit box depends on the dimensions and offsets of the first frame of the animation
		const int32_t nMouseX = GENERATE(90, 100, 120, 149, 160, 200);
		const int32_t nMouseY = GENERATE(150, 165, 185, 199, 200, 210);
		const bool bHasCellFile = GENERATE(true, false);
		CAPTURE(nAnimType);
		CAPTURE(nMouseX);
		CAPTURE(nMouseY);
		CAPTURE(bHasCellFile);

		AnimatedImageDescriptors descriptors;
		if (!bHasCellFile)
		{
			descriptors.descriptors[nAnimType].ppCellFile1 = nullptr;
		}

		D2WinAnimImageStrc moo_pAnimImage{};
		D2WinAnimImageStrc original_pAnimImage{};

		const auto setup_data = [&](
			D2WinAnimImageStrc& pAnimImage
		) {
			d2win_init_control(pAnimImage.controlHeader, D2WIN_IMAGE, 100, 200, 50, 50);
			pAnimImage.pAnimatedImageDescriptor = descriptors.descriptors;
			pAnimImage.nAnimType = nAnimType;
		};

		setup_data(moo_pAnimImage);
		setup_data(original_pAnimImage);
		set_mouse_position(nMouseX, nMouseY);

		// Call both implementations
		const auto moo_result = sut(&moo_pAnimImage.controlHeader);
		const auto original_result = original(&original_pAnimImage.controlHeader);

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pAnimImage, original_pAnimImage, "Comparing pAnimImage");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A5610")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ANIMIMAGE_Draw, dll_base + 0x00005610);

		// NOTE: The current frame is computed from GetTickCount(). The start time is chosen in the middle of a frame,
		// so that the few milliseconds between the calls of both implementations don't change the result.

		// Input data
		const bool bHasDescriptor = GENERATE(true, false);
		const int32_t nAnimType = GENERATE(0, 1, 2, 3, 4);
		const uint32_t nFrame = GENERATE(0u, 2u, 5u, 9u, 20u);
		const bool bHovered = GENERATE(true, false);
		const int32_t bIsRunning = GENERATE(1, 0);
		CAPTURE(bHasDescriptor);
		CAPTURE(nAnimType);
		CAPTURE(nFrame);
		CAPTURE(bHovered);
		CAPTURE(bIsRunning);

		D2WinFakeCellFile cellFile("anim", 7);
		AnimatedImageDescriptors descriptors;
		const uint32_t nAnimSpeed = 2;
		const uint32_t nFrameDuration = 1000 * nAnimSpeed / 25;
		const DWORD dwStartTickCount = GetTickCount() - 3 * nFrameDuration - nFrameDuration / 2;

		D2WinAnimImageStrc moo_pAnimImage{};
		D2WinAnimImageStrc original_pAnimImage{};

		const auto setup_data = [&](
			D2WinAnimImageStrc& pAnimImage
		) {
			d2win_init_control(pAnimImage.controlHeader, D2WIN_IMAGE, 100, 200, 50, 50);
			pAnimImage.controlHeader.pCellFile = cellFile.get();
			pAnimImage.pAnimatedImageDescriptor = bHasDescriptor ? descriptors.descriptors : nullptr;
			pAnimImage.nAnimType = bHasDescriptor ? nAnimType : 0;
			pAnimImage.nAnimSpeed = nAnimSpeed;
			pAnimImage.dwStartTickCount = dwStartTickCount;
			pAnimImage.nFrame = nFrame;
			pAnimImage.eDrawMode = DRAWMODE_TRANS25;
			pAnimImage.pfOnHoverChanged = D2WinCallbacks::VoidCallback;
			pAnimImage.bIsRunning = bIsRunning;
		};

		setup_data(moo_pAnimImage);
		setup_data(original_pAnimImage);
		set_mouse_position(bHovered ? 120 : 10, bHovered ? 190 : 10);
		D2WinCallLog::name_pointer(&moo_pAnimImage, "pAnimImage");
		D2WinCallLog::name_pointer(&original_pAnimImage, "pAnimImage");

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pAnimImage.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pAnimImage.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pAnimImage, original_pAnimImage, "Comparing pAnimImage");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A5610 - No cell file")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ANIMIMAGE_Draw, dll_base + 0x00005610);

		// Input data
		D2WinAnimImageStrc moo_pAnimImage{};
		D2WinAnimImageStrc original_pAnimImage{};
		d2win_init_control(moo_pAnimImage.controlHeader, D2WIN_IMAGE);
		d2win_init_control(original_pAnimImage.controlHeader, D2WIN_IMAGE);

		// Call both implementations
		D2WinCallLog::clear();
		const auto moo_result = sut(&moo_pAnimImage.controlHeader);
		const auto moo_calls = D2WinCallLog::take();
		const auto original_result = original(&original_pAnimImage.controlHeader);
		const auto original_calls = D2WinCallLog::take();

		// Compare return values
		MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_pAnimImage, original_pAnimImage, "Comparing pAnimImage");
	}

	TEST_CASE_FIXTURE(D2WinFixture<NoopFixture>, "D2Win.0x6F8A5900")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ANIMIMAGE_HandleMouseDown, dll_base + 0x00005900);

		// Input data
		const int32_t nAnimType = GENERATE(0, 1, 2, 3, 4);
		const bool bHasCallback = GENERATE(true, false);
		const int32_t nCallbackResult = GENERATE(0, 1, 7);
		CAPTURE(nAnimType);
		CAPTURE(bHasCallback);
		CAPTURE(nCallbackResult);

		D2WinCallbacks::nReturnValue = nCallbackResult;

		D2WinAnimImageStrc moo_pAnimImage{};
		D2WinAnimImageStrc original_pAnimImage{};
		SMSGHANDLER_PARAMS moo_pMsg{};
		SMSGHANDLER_PARAMS original_pMsg{};

		const auto setup_data = [&](
			D2WinAnimImageStrc& pAnimImage,
			SMSGHANDLER_PARAMS& pMsg
		) {
			d2win_init_control(pAnimImage.controlHeader, D2WIN_IMAGE);
			pAnimImage.controlHeader.pfCallback = bHasCallback ? D2WinCallbacks::Callback : nullptr;
			pAnimImage.nAnimType = nAnimType;
			pAnimImage.nFrame = 3;
			pMsg.hWindow = reinterpret_cast<HWND>(&pAnimImage);
			pMsg.nMessage = WM_LBUTTONDOWN;
		};

		setup_data(moo_pAnimImage, moo_pMsg);
		setup_data(original_pAnimImage, original_pMsg);
		D2WinCallLog::name_pointer(&moo_pAnimImage, "pAnimImage");
		D2WinCallLog::name_pointer(&original_pAnimImage, "pAnimImage");

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
		MOO_CHECK_EQ(moo_pAnimImage, original_pAnimImage, "Comparing pAnimImage");
		MOO_CHECK_EQ(moo_pMsg, original_pMsg, "Comparing pMsg");
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A5980 (#10105)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(ANIMIMAGE_SetIsRunning, dll_base + 0x00005980);

		SUBCASE("")
		{
			// Input data
			const int32_t bIsRunning = GENERATE(0, 1, 5);
			D2WinAnimImageStrc moo_pAnimImage{};
			D2WinAnimImageStrc original_pAnimImage{};
			d2win_init_control(moo_pAnimImage.controlHeader, D2WIN_IMAGE);
			d2win_init_control(original_pAnimImage.controlHeader, D2WIN_IMAGE);
			moo_pAnimImage.bIsRunning = 1;
			original_pAnimImage.bIsRunning = 1;

			// Call both implementations
			const auto moo_result = sut(&moo_pAnimImage, bIsRunning);
			const auto original_result = original(&original_pAnimImage, bIsRunning);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pAnimImage, original_pAnimImage, "Comparing pAnimImage");
		}
	}
}

#endif
