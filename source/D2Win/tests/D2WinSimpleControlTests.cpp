#include <doctest.h>

#include <cstdint>
#include <string>
#include <vector>

#include <Windows.h>

#include <D2CMP.h>

#include <D2WinImage.h>
#include <D2WinProgressBar.h>
#include <D2WinScrollBar.h>
#include <D2WinTimer.h>

#include "D2WinControlFixtures.h"


extern uint32_t gdwNextRepeatTickCount;


namespace
{
// Creates a control with both implementations, each one in an empty control list
template<typename Control, typename Create>
std::pair<Control*, Control*> create_both(Create&& create)
{
	Control* pControls[2] = {};
	for (int i = 0; i < 2; ++i)
	{
		const ControlGlobals& globals = *both_control_globals[i];
		*globals.ppControlList = nullptr;
		pControls[i] = create(i == 0);
		REQUIRE(pControls[i] != nullptr);
		CHECK_EQ(*globals.ppControlList, &pControls[i]->controlHeader);
		CHECK_EQ(pControls[i]->controlHeader.pNext, nullptr);
		*globals.ppControlList = nullptr;
	}
	return { pControls[0], pControls[1] };
}

template<typename Control>
void free_both(std::pair<Control*, Control*> controls)
{
	FogMemoryMock::Free(controls.first, __FILE__, __LINE__, 0);
	FogMemoryMock::Free(controls.second, __FILE__, __LINE__, 0);
}

// D2CMP.#10046, the cel files of the tests are fake, their frame count is their first int
struct CellFileMock
{
	static int __stdcall GetCelsPerDirection(D2CellFileStrc* pCellFile)
	{
		return *reinterpret_cast<int32_t*>(pCellFile);
	}
};

template<class Fixture>
struct D2WinSimpleControlFixture : D2WinControlFixture<Fixture>
{
	ImportTablePatch patches;

	D2WinSimpleControlFixture()
	{
		CallbackRecorder::reset();
		this->hook("D2CMP.dll", 10046, &D2CMP_CelFileGetCelsPerDirection, &CellFileMock::GetCelsPerDirection);
		patches.patch_both(get_original_d2win(), "KERNEL32.dll", "GetTickCount", reinterpret_cast<const void*>(&TickCountMock::GetTickCount));
	}

	~D2WinSimpleControlFixture()
	{
		CallbackRecorder::reset();
	}
};
}


TEST_SUITE("D2WinSimpleControlTests")
{
	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8AF040 (#10063)")
	{
		const auto [sut, original] = make_d2win_pair(SCROLLBAR_Create, 0x6F8AF040);

		PointerPairs pointers;
		pointers.add_function(SCROLLBAR_Draw, 0x6F8AF330);
		pointers.add_function(SCROLLBAR_HandleMouseDown, 0x6F8AF4D0);
		pointers.add_function(SCROLLBAR_HandleMouseUp, 0x6F8AF6B0);

		int32_t cellFile[4] = { 3 };
		for (auto pfCallback : { (int32_t(__stdcall*)(SMSGHANDLER_PARAMS*))nullptr, &CallbackRecorder::Callback })
		{
			const auto scrollBars = create_both<D2WinScrollBarStrc>([&](bool bMoo)
			{
				return (bMoo ? sut : original)(15, 420, 10, 200, reinterpret_cast<D2CellFileStrc*>(cellFile), pfCallback);
			});
			CHECK_EQ(describe_differences(*scrollBars.first, *scrollBars.second, pointers), "");
			free_both(scrollBars);
		}
	}

	// Accessors of the scroll bar
	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8AF130 (#10066)")
	{
		const auto [set_max, original_set_max] = make_d2win_pair(SCROLLBAR_SetMaxSteps, 0x6F8AF130);
		const auto [get_max, original_get_max] = make_d2win_pair(SCROLLBAR_GetMaxSteps, 0x6F8AF100);
		const auto [set_current, original_set_current] = make_d2win_pair(SCROLLBAR_SetCurrentStep, 0x6F8AF170);
		const auto [get_current, original_get_current] = make_d2win_pair(SCROLLBAR_GetCurrentStep, 0x6F8AF1B0);
		const auto [set_text_box, original_set_text_box] = make_d2win_pair(SCROLLBAR_SetTextBox, 0x6F8AF1E0);
		const auto [set_callback, original_set_callback] = make_d2win_pair(SCROLLBAR_SetStepChangeCallback, 0x6F8AF210);
		const auto [set_page, original_set_page] = make_d2win_pair(D2Win_10202, 0x6F8AF2D0);
		const auto [get_page, original_get_page] = make_d2win_pair(D2Win_10201, 0x6F8AF300);

		for (int32_t nMaxSteps : { -5, 0, 1, 10 })
		{
			for (int32_t nCurrentStep : { -3, 0, 4, 10, 25 })
			{
				CAPTURE(nMaxSteps);
				CAPTURE(nCurrentStep);

				D2WinScrollBarStrc moo = {};
				D2WinScrollBarStrc orig = {};
				moo.controlHeader.nType = orig.controlHeader.nType = D2WIN_SCROLLBAR;

				CHECK_EQ(set_max(&moo, nMaxSteps), original_set_max(&orig, nMaxSteps));
				CHECK_EQ(get_max(&moo), original_get_max(&orig));
				CHECK_EQ(set_current(&moo, nCurrentStep), original_set_current(&orig, nCurrentStep));
				CHECK_EQ(get_current(&moo), original_get_current(&orig));
				set_page(&moo, nCurrentStep * 2);
				original_set_page(&orig, nCurrentStep * 2);
				CHECK_EQ(get_page(&moo), original_get_page(&orig));
				D2WinTextBoxStrc* pTextBox = reinterpret_cast<D2WinTextBoxStrc*>(&moo);
				CHECK_EQ(set_text_box(&moo, pTextBox), original_set_text_box(&orig, pTextBox));
				CHECK_EQ(set_callback(&moo, &CallbackRecorder::VoidCallback), original_set_callback(&orig, &CallbackRecorder::VoidCallback));
				CHECK_EQ(describe_differences(moo, orig), "");
			}
		}
	}

	// Mouse wheel and arrow steps
	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8AF240")
	{
		const auto [sut, original] = make_d2win_pair(sub_6F8AF240, 0x6F8AF240);

		for (int32_t bDragged : { 0, 1 })
		{
			for (int32_t nCurrentStep : { 0, 1, 5, 9, 10 })
			{
				for (int32_t nDirection : { -120, -1, 0, 1, 3 })
				{
					for (bool bCallback : { false, true })
					{
						CAPTURE(bDragged);
						CAPTURE(nCurrentStep);
						CAPTURE(nDirection);
						CAPTURE(bCallback);

						D2WinScrollBarStrc scrollBars[2] = {};
						std::vector<std::string> logs[2];
						int32_t results[2];
						for (int i = 0; i < 2; ++i)
						{
							D2WinScrollBarStrc& scrollBar = scrollBars[i];
							scrollBar.controlHeader.nType = D2WIN_SCROLLBAR;
							scrollBar.nMaxSteps = 10;
							scrollBar.nCurrentStep = nCurrentStep;
							scrollBar.bIsStepIndicatorDragged = bDragged;
							scrollBar.pfOnStepChange = bCallback ? &CallbackRecorder::VoidCallback : nullptr;

							SMSGHANDLER_PARAMS msg = {};
							msg.hWindow = (HWND)&scrollBar;
							msg.nMessage = WM_MOUSEWHEEL;
							CallbackRecorder::log.clear();
							results[i] = (i == 0 ? sut : original)(&msg, &scrollBar, nDirection);
							logs[i] = CallbackRecorder::log;
						}

						CHECK_EQ(results[0], results[1]);
						CHECK_EQ(logs[0], logs[1]);
						CHECK_EQ(describe_differences(scrollBars[0], scrollBars[1]), "");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8AF4D0")
	{
		const auto [sut, original] = make_d2win_pair(SCROLLBAR_HandleMouseDown, 0x6F8AF4D0);
		const auto [mouse_up, original_mouse_up] = make_d2win_pair(SCROLLBAR_HandleMouseUp, 0x6F8AF6B0);

		struct Setup
		{
			int32_t nHeight;
			int32_t nMaxSteps;
			int32_t nCurrentStep;
			int32_t nPageStep;
			int32_t bUpper;
			int32_t bLower;
			int32_t bDragged;
		};

		std::vector<Setup> setups;
		for (int32_t nHeight : { 40, 31, 200 })
		{
			for (int32_t nMaxSteps : { 0, 3, 50 })
			{
				for (int32_t nCurrentStep : { 0, 2, 50 })
				{
					setups.push_back({ nHeight, nMaxSteps, std::min(nCurrentStep, nMaxSteps), 0, 0, 0, 0 });
				}
			}
			setups.push_back({ nHeight, 50, 20, 7, 0, 0, 0 });
			setups.push_back({ nHeight, 50, 20, 0, 1, 0, 0 });
			setups.push_back({ nHeight, 50, 20, 0, 0, 1, 0 });
			setups.push_back({ nHeight, 50, 20, 0, 0, 0, 1 });
		}

		constexpr int32_t nX = 100;
		constexpr int32_t nY = 400;
		const UINT messages[] = { WM_LBUTTONDOWN, WM_RBUTTONDOWN };
		const uint32_t flags[] = { 5, 1, 4 };

		for (const Setup& setup : setups)
		{
			std::vector<POINT> points = { { nX - 1, nY - 5 }, { nX + 11, nY - 5 }, { nX + 5, nY + 1 } };
			for (int32_t nOffsetY = -5; nOffsetY <= setup.nHeight + 5; nOffsetY += 3)
			{
				points.push_back({ nX + 5, nY - setup.nHeight + nOffsetY });
			}

			for (const POINT& point : points)
			{
				for (UINT nMessage : messages)
				{
					for (uint32_t dwFlags : flags)
					{
						if ((nMessage != WM_LBUTTONDOWN || dwFlags != 5) && (point.x != nX + 5 || point.y != nY - setup.nHeight + 10))
						{
							continue;
						}

						CAPTURE(setup.nHeight);
						CAPTURE(setup.nMaxSteps);
						CAPTURE(setup.nCurrentStep);
						CAPTURE(setup.nPageStep);
						CAPTURE(setup.bUpper);
						CAPTURE(setup.bLower);
						CAPTURE(setup.bDragged);
						CAPTURE(point.x);
						CAPTURE(point.y);
						CAPTURE(nMessage);
						CAPTURE(dwFlags);

						D2WinScrollBarStrc scrollBars[2] = {};
						std::vector<std::string> logs[2];
						int32_t results[2];
						int32_t upResults[2];
						D2WinScrollBarStrc afterUp[2] = {};
						for (int i = 0; i < 2; ++i)
						{
							D2WinScrollBarStrc& scrollBar = scrollBars[i];
							scrollBar.controlHeader.nType = D2WIN_SCROLLBAR;
							scrollBar.controlHeader.dwFlags = dwFlags;
							scrollBar.controlHeader.nImageX = nX;
							scrollBar.controlHeader.nImageY = nY;
							scrollBar.controlHeader.nWidth = 10;
							scrollBar.controlHeader.nHeight = setup.nHeight;
							scrollBar.controlHeader.pfCallback = &CallbackRecorder::Callback;
							scrollBar.nMaxSteps = setup.nMaxSteps;
							scrollBar.nCurrentStep = setup.nCurrentStep;
							scrollBar.nPageStep = setup.nPageStep;
							scrollBar.bIsUpperArrowPressed = setup.bUpper;
							scrollBar.bIsLowerArrowPressed = setup.bLower;
							scrollBar.bIsStepIndicatorDragged = setup.bDragged;
							scrollBar.pfOnStepChange = &CallbackRecorder::VoidCallback;

							*both_control_globals[i]->pMousePosition = point;

							SMSGHANDLER_PARAMS msg = {};
							msg.hWindow = (HWND)&scrollBar;
							msg.nMessage = nMessage;
							CallbackRecorder::log.clear();
							CallbackRecorder::nResult = 7;
							results[i] = (i == 0 ? sut : original)(&msg);
							logs[i] = CallbackRecorder::log;

							afterUp[i] = scrollBar;
							msg.hWindow = (HWND)&afterUp[i];
							msg.nMessage = WM_LBUTTONUP;
							upResults[i] = (i == 0 ? mouse_up : original_mouse_up)(&msg);
						}

						CHECK_EQ(results[0], results[1]);
						CHECK_EQ(logs[0], logs[1]);
						CHECK_EQ(describe_differences(scrollBars[0], scrollBars[1]), "");
						CHECK_EQ(upResults[0], upResults[1]);
						CHECK_EQ(describe_differences(afterUp[0], afterUp[1]), "");
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8B1B70")
	{
		const auto [sut, original] = make_d2win_pair(TIMER_Create, 0x6F8B1B70);

		PointerPairs pointers;
		pointers.add_function(TIMER_UpdateDefault, 0x6F8B1C60);
		pointers.add_function(TIMER_HandleVirtualKeyInput, 0x6F8B1D70);

		TickCountMock::dwTickCount = 123456;
		for (uint32_t nTimeout : { 0u, 5u, 0xFFFFFFFFu })
		{
			const auto timers = create_both<D2WinTimerStrc>([&](bool bMoo) { return (bMoo ? sut : original)(nTimeout, &CallbackRecorder::Callback); });
			CHECK_EQ(describe_differences(*timers.first, *timers.second, pointers), "");
			free_both(timers);
		}
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8B1C30 (#10182)")
	{
		const auto [disable_space, original_disable_space] = make_d2win_pair(TIMER_DisableSpaceKey, 0x6F8B1C00);
		const auto [set_repeating, original_set_repeating] = make_d2win_pair(TIMER_SetRepeating, 0x6F8B1C30);

		PointerPairs pointers;
		pointers.add_function(TIMER_UpdateDefault, 0x6F8B1C60);
		pointers.add_function(TIMER_UpdateRepeating, 0x6F8B1CF0);
		pointers.add_function(TIMER_HandleVirtualKeyInput, 0x6F8B1D70);

		D2WinTimerStrc timers[2] = {};
		for (int i = 0; i < 2; ++i)
		{
			timers[i].controlHeader.nType = D2WIN_TIMER;
			timers[i].controlHeader.pfUpdate = i == 0 ? &TIMER_UpdateDefault : reinterpret_cast<int32_t(__fastcall*)(D2WinControlStrc*)>(original_d2win_address(0x6F8B1C60));
			timers[i].controlHeader.pfHandleVirtualKeyInput = i == 0 ? &TIMER_HandleVirtualKeyInput : reinterpret_cast<int32_t(__stdcall*)(SMSGHANDLER_PARAMS*)>(original_d2win_address(0x6F8B1D70));
		}

		set_repeating(&timers[0]);
		original_set_repeating(&timers[1]);
		CHECK_EQ(describe_differences(timers[0], timers[1], pointers), "");
		CHECK_NE(timers[0].controlHeader.pfUpdate, &TIMER_UpdateDefault);

		disable_space(&timers[0]);
		original_disable_space(&timers[1]);
		CHECK_EQ(describe_differences(timers[0], timers[1], pointers), "");
		CHECK_EQ(timers[1].controlHeader.pfHandleVirtualKeyInput, nullptr);
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8B1C60")
	{
		const auto [sut, original] = make_d2win_pair(TIMER_UpdateDefault, 0x6F8B1C60);

		const DWORD createTicks[] = { 0, 999, 1000, 0xFFFFFC00 };
		const DWORD elapsed[] = { 0, 999, 1000, 2000, 2999, 3001, 4000, 100000 };
		for (DWORD dwCreated : createTicks)
		{
			for (DWORD dwElapsed : elapsed)
			{
				for (uint32_t nTimeout : { 0u, 2u, 3u })
				{
					for (uint32_t dwFlags : { 5u, 4u, 1u })
					{
						for (bool bCallback : { false, true })
						{
							CAPTURE(dwCreated);
							CAPTURE(dwElapsed);
							CAPTURE(nTimeout);
							CAPTURE(dwFlags);
							CAPTURE(bCallback);

							int32_t results[2];
							std::vector<std::string> logs[2];
							for (int i = 0; i < 2; ++i)
							{
								D2WinTimerStrc timer = {};
								timer.controlHeader.nType = D2WIN_TIMER;
								timer.controlHeader.dwFlags = dwFlags;
								timer.controlHeader.pfCallback = bCallback ? &CallbackRecorder::Callback : nullptr;
								timer.nTimeout = nTimeout;
								timer.dwTickCount = dwCreated;

								TickCountMock::dwTickCount = dwCreated + dwElapsed;
								CallbackRecorder::log.clear();
								results[i] = (i == 0 ? sut : original)(&timer.controlHeader);
								logs[i] = CallbackRecorder::log;
							}

							CHECK_EQ(results[0], results[1]);
							CHECK_EQ(logs[0], logs[1]);
						}
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8B1CF0")
	{
		const auto [sut, original] = make_d2win_pair(TIMER_UpdateRepeating, 0x6F8B1CF0);
		uint32_t* const pNextRepeats[2] = { &gdwNextRepeatTickCount, original_d2win_global<uint32_t>(0x6F96A8E0) };
		const uint32_t savedNextRepeats[2] = { *pNextRepeats[0], *pNextRepeats[1] };

		// A sequence of updates, the next repeat tick count carries over
		const DWORD ticks[] = { 1000, 1000, 1100, 1249, 1250, 1300, 1500, 2000, 100, 0xFFFFFFF0, 0xFFFFFFFF, 5 };
		for (uint32_t dwFlags : { 5u, 4u })
		{
			std::vector<std::string> logs[2];
			std::vector<uint32_t> nextRepeats[2];
			std::vector<int32_t> results[2];
			for (int i = 0; i < 2; ++i)
			{
				*pNextRepeats[i] = 0;
				D2WinTimerStrc timer = {};
				timer.controlHeader.nType = D2WIN_TIMER;
				timer.controlHeader.dwFlags = dwFlags;
				timer.controlHeader.pfCallback = &CallbackRecorder::Callback;
				timer.nTimeout = 250;

				CallbackRecorder::log.clear();
				for (DWORD dwTick : ticks)
				{
					TickCountMock::dwTickCount = dwTick;
					results[i].push_back((i == 0 ? sut : original)(&timer.controlHeader));
					nextRepeats[i].push_back(*pNextRepeats[i]);
				}
				logs[i] = CallbackRecorder::log;
			}

			CAPTURE(dwFlags);
			CHECK_EQ(results[0], results[1]);
			CHECK_EQ(logs[0], logs[1]);
			CHECK_EQ(nextRepeats[0], nextRepeats[1]);
		}

		*pNextRepeats[0] = savedNextRepeats[0];
		*pNextRepeats[1] = savedNextRepeats[1];
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8B1D70")
	{
		const auto [sut, original] = make_d2win_pair(TIMER_HandleVirtualKeyInput, 0x6F8B1D70);

		for (UINT nMessage : { (UINT)WM_KEYDOWN, (UINT)WM_CHAR, (UINT)WM_KEYUP })
		{
			for (WPARAM wParam : { (WPARAM)VK_SPACE, (WPARAM)VK_RETURN, (WPARAM)0x120 })
			{
				for (bool bCallback : { false, true })
				{
					CAPTURE(nMessage);
					CAPTURE(wParam);
					CAPTURE(bCallback);

					int32_t results[2];
					std::vector<std::string> logs[2];
					for (int i = 0; i < 2; ++i)
					{
						D2WinTimerStrc timer = {};
						timer.controlHeader.nType = D2WIN_TIMER;
						timer.controlHeader.pfCallback = bCallback ? &CallbackRecorder::Callback : nullptr;

						SMSGHANDLER_PARAMS msg = {};
						msg.hWindow = (HWND)&timer;
						msg.nMessage = nMessage;
						msg.wParam = wParam;
						CallbackRecorder::log.clear();
						CallbackRecorder::nResult = 3;
						results[i] = (i == 0 ? sut : original)(&msg);
						logs[i] = CallbackRecorder::log;
					}

					CHECK_EQ(results[0], results[1]);
					CHECK_EQ(logs[0], logs[1]);
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8AEED0 (#10091)")
	{
		const auto [sut, original] = make_d2win_pair(PROGRESSBAR_Create, 0x6F8AEED0);
		const auto [set_progress, original_set_progress] = make_d2win_pair(PROGRESSBAR_SetProgress, 0x6F8AEF70);

		PointerPairs pointers;
		pointers.add_function(PROGRESSBAR_Draw, 0x6F8AEFB0);

		const auto progressBars = create_both<D2WinProgressBarStrc>([&](bool bMoo) { return (bMoo ? sut : original)(20, 500, 300, 18); });
		CHECK_EQ(describe_differences(*progressBars.first, *progressBars.second, pointers), "");

		for (float fProgress : { 0.0f, 0.25f, 1.0f, -3.5f })
		{
			CHECK_EQ(set_progress(progressBars.first, fProgress), original_set_progress(progressBars.second, fProgress));
			CHECK_EQ(describe_differences(*progressBars.first, *progressBars.second, pointers), "");
		}
		free_both(progressBars);
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8ABA90 (#10084)")
	{
		const auto [sut, original] = make_d2win_pair(IMAGE2_Create, 0x6F8ABA90);

		PointerPairs pointers;
		pointers.add_function(IMAGE2_Draw, 0x6F8ABD50);
		pointers.add_function(IMAGE2_HandleMouseDown, 0x6F8AC170);

		int32_t cellFile[4] = { 3 };
		D2WinImageClickRectStrc clickRect = { 1, 2, 3, 4, &CallbackRecorder::OtherCallback };
		const auto images = create_both<D2WinImage2Strc>([&](bool bMoo)
		{
			return (bMoo ? sut : original)(5, 300, 200, 100, reinterpret_cast<D2CellFileStrc*>(cellFile), &CallbackRecorder::Callback, &clickRect, &CallbackRecorder::OtherCallback);
		});
		CHECK_EQ(describe_differences(*images.first, *images.second, pointers), "");
		free_both(images);
	}

	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8ABB40")
	{
		const auto [sut, original] = make_d2win_pair(IMAGE_Create, 0x6F8ABB40);

		PointerPairs pointers;
		pointers.add_function(IMAGE_Draw, 0x6F8ABEA0);
		pointers.add_function(IMAGE2_HandleMouseDown, 0x6F8AC170);

		int32_t cellFile[4] = { 9 };
		const auto images = create_both<D2WinImageStrc>([&](bool bMoo)
		{
			return (bMoo ? sut : original)(5, 300, 200, 100, reinterpret_cast<D2CellFileStrc*>(cellFile), 12, 34);
		});
		CHECK_EQ(describe_differences(*images.first, *images.second, pointers), "");
		free_both(images);
	}

	// Setters of the images
	TEST_CASE_FIXTURE(D2WinSimpleControlFixture<NoOpFixture>, "D2Win.0x6F8ABC80 (#10088)")
	{
		const auto [set_cell_file, original_set_cell_file] = make_d2win_pair(IMAGE_SetCellFile, 0x6F8ABC00);
		const auto [set_coordinates, original_set_coordinates] = make_d2win_pair(IMAGE_SetCoordinates, 0x6F8ABC40);
		const auto [set_frame, original_set_frame] = make_d2win_pair(IMAGE_SetFrame, 0x6F8ABC80);
		const auto [force_normal, original_force_normal] = make_d2win_pair(IMAGE_ForceNormalDrawMode, 0x6F8ABCD0);
		const auto [get_frame_count, original_get_frame_count] = make_d2win_pair(IMAGE_GetFrameCount, 0x6F8ABD10);

		for (int32_t nFrames : { 0, 1, 5 })
		{
			for (int32_t nFrame : { -2, 0, 3, 4, 5, 100 })
			{
				CAPTURE(nFrames);
				CAPTURE(nFrame);

				int32_t cellFile[4] = { nFrames };
				D2WinImageClickRectStrc clickRect = {};

				D2WinImageStrc moo = {};
				D2WinImageStrc orig = {};
				moo.controlHeader.nType = orig.controlHeader.nType = D2WIN_IMAGE;
				moo.eDrawMode = orig.eDrawMode = (DrawMode)3;

				D2CellFileStrc* pCellFile = reinterpret_cast<D2CellFileStrc*>(cellFile);
				CHECK_EQ(set_cell_file(&moo, pCellFile, &clickRect), original_set_cell_file(&orig, pCellFile, &clickRect));
				CHECK_EQ(set_coordinates(&moo, nFrame, -nFrame), original_set_coordinates(&orig, nFrame, -nFrame));
				CHECK_EQ(set_frame(&moo, nFrame), original_set_frame(&orig, nFrame));
				CHECK_EQ(get_frame_count(&moo), original_get_frame_count(&orig));
				CHECK_EQ(describe_differences(moo, orig), "");
				CHECK_EQ(force_normal(&moo, 1), original_force_normal(&orig, 1));
				CHECK_EQ(describe_differences(moo, orig), "");
			}
		}
	}
}
