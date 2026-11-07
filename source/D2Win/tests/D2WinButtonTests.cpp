#include <doctest.h>

#include <cstdint>
#include <string>
#include <vector>

#include <Windows.h>

#include <D2Lang.h>
#include <D2LangStringMocks.h>
#include <D2Sound.h>

#include <D2WinButton.h>

#include "D2WinControlFixtures.h"


namespace
{
// D2Sound.#10039, plays a sound file
struct ButtonSoundMock
{
	static void __fastcall PlaySoundFile(const char* szFile)
	{
		CallbackRecorder::log.push_back(std::string("Sound ") + szFile);
	}
};

// The button functions of each implementation
struct ButtonFunctions
{
	int32_t(__fastcall* pfDraw)(D2WinControlStrc*);
	BOOL(__stdcall* pfHandleMouseDown)(SMSGHANDLER_PARAMS*);
	int32_t(__stdcall* pfHandleMouseUp)(SMSGHANDLER_PARAMS*);
	int32_t(__stdcall* pfHandleVirtualKeyInput)(SMSGHANDLER_PARAMS*);
};

const ButtonFunctions& button_functions(int nImplementation)
{
	static const ButtonFunctions moo = { &BUTTON_Draw, &BUTTON_HandleMouseDown, &BUTTON_HandleMouseUp, &BUTTON_HandleVirtualKeyInput };
	static const ButtonFunctions original = {
		reinterpret_cast<decltype(moo.pfDraw)>(original_d2win_address(0x6F8A65A0)),
		reinterpret_cast<decltype(moo.pfHandleMouseDown)>(original_d2win_address(0x6F8A6A10)),
		reinterpret_cast<decltype(moo.pfHandleMouseUp)>(original_d2win_address(0x6F8A6AF0)),
		reinterpret_cast<decltype(moo.pfHandleVirtualKeyInput)>(original_d2win_address(0x6F8A6BB0)),
	};
	return nImplementation == 0 ? moo : original;
}

PointerPairs button_pointers()
{
	PointerPairs pointers;
	pointers.add_function(BUTTON_Draw, 0x6F8A65A0);
	pointers.add_function(BUTTON_HandleMouseDown, 0x6F8A6A10);
	pointers.add_function(BUTTON_HandleMouseUp, 0x6F8A6AF0);
	pointers.add_function(BUTTON_HandleVirtualKeyInput, 0x6F8A6BB0);
	return pointers;
}

int32_t* message_depth(int nImplementation)
{
	return nImplementation == 0 ? &dword_6F8FE254 : original_d2win_global<int32_t>(0x6F8FE254);
}

template<class Fixture>
struct D2WinButtonFixture : D2WinControlFixture<Fixture>
{
	int32_t savedDepths[2];

	D2WinButtonFixture()
	{
		CallbackRecorder::reset();
		hook_d2lang_string_mocks(this->hooks);
		this->hook("D2Sound.dll", 10039, &D2SOUND_10039, &ButtonSoundMock::PlaySoundFile);
		for (int i = 0; i < 2; ++i)
		{
			savedDepths[i] = *message_depth(i);
			// The handlers are called from the message loop, which counts the nested messages
			*message_depth(i) = 1;
		}
	}

	~D2WinButtonFixture()
	{
		for (int i = 0; i < 2; ++i)
		{
			*message_depth(i) = savedDepths[i];
		}
		CallbackRecorder::reset();
	}
};

// A button set up like BUTTON_Create would for the given implementation
D2WinButtonStrc make_button(int nImplementation, uint32_t dwFlags, uint32_t dwButtonFlags, int32_t bIsPressed, int32_t bIsCallbackPending, bool bCallback, bool bHandlers = true)
{
	const ButtonFunctions& functions = button_functions(nImplementation);
	D2WinButtonStrc button = {};
	button.controlHeader.nType = D2WIN_BUTTON;
	button.controlHeader.dwFlags = dwFlags;
	button.controlHeader.nImageX = 100;
	button.controlHeader.nImageY = 300;
	button.controlHeader.nWidth = 80;
	button.controlHeader.nHeight = 30;
	button.controlHeader.pfDraw = functions.pfDraw;
	if (bHandlers)
	{
		button.controlHeader.pfHandleMouseDown = reinterpret_cast<int32_t(__stdcall*)(SMSGHANDLER_PARAMS*)>(functions.pfHandleMouseDown);
		button.controlHeader.pfHandleMouseUp = functions.pfHandleMouseUp;
	}
	button.controlHeader.pfHandleVirtualKeyInput = functions.pfHandleVirtualKeyInput;
	button.controlHeader.pfCallback = bCallback ? &CallbackRecorder::Callback : nullptr;
	button.dwButtonFlags = dwButtonFlags;
	button.bIsPressed = bIsPressed;
	button.bIsCallbackPending = bIsCallbackPending;
	button.nActivationVirtualKey = VK_RETURN;
	return button;
}

// The states of the buttons tested by the handlers
struct ButtonState
{
	uint32_t dwFlags;
	uint32_t dwButtonFlags;
	int32_t bIsPressed;
	int32_t bIsCallbackPending;
	bool bCallback;
};

std::vector<ButtonState> button_states()
{
	std::vector<ButtonState> states;
	for (uint32_t dwFlags : { 5u, 4u, 1u, 7u })
	{
		for (uint32_t dwButtonFlags : { 0u, 1u, 2u, 3u, 4u, 6u, 0x18u })
		{
			for (int32_t nPressed = 0; nPressed < 4; ++nPressed)
			{
				for (bool bCallback : { true, false })
				{
					if (!bCallback && (dwFlags != 5 || nPressed != 0))
					{
						continue;
					}
					states.push_back({ dwFlags, dwButtonFlags, nPressed & 1, nPressed >> 1, bCallback });
				}
			}
		}
	}
	return states;
}

#define CAPTURE_BUTTON_STATE(state) \
	CAPTURE(state.dwFlags); \
	CAPTURE(state.dwButtonFlags); \
	CAPTURE(state.bIsPressed); \
	CAPTURE(state.bIsCallbackPending); \
	CAPTURE(state.bCallback)

// Runs a handler of both implementations on the same button state, and compares the results
template<typename Run>
void compare_button_handlers(const ButtonState& state, Run&& run, bool bHandlers = true)
{
	D2WinButtonStrc buttons[2];
	std::vector<std::string> logs[2];
	int32_t results[2];
	int32_t depths[2];
	for (int i = 0; i < 2; ++i)
	{
		buttons[i] = make_button(i, state.dwFlags, state.dwButtonFlags, state.bIsPressed, state.bIsCallbackPending, state.bCallback, bHandlers);
		CallbackRecorder::log.clear();
		CallbackRecorder::nResult = 9;
		results[i] = run(i, buttons[i]);
		logs[i] = CallbackRecorder::log;
		depths[i] = *message_depth(i);
	}

	CHECK_EQ(results[0], results[1]);
	CHECK_EQ(logs[0], logs[1]);
	CHECK_EQ(depths[0], depths[1]);
	CHECK_EQ(describe_differences(buttons[0], buttons[1], button_pointers()), "");
}
}


TEST_SUITE("D2WinButtonTests")
{
	TEST_CASE_FIXTURE(D2WinButtonFixture<NoOpFixture>, "D2Win.0x6F8A61A0 (#10107)")
	{
		const auto [sut, original] = make_d2win_pair(BUTTON_Create, 0x6F8A61A0);

		struct Case
		{
			int32_t nWidth;
			int32_t nHeight;
			int32_t nActivationVirtualKey;
			uint32_t dwFlags;
			uint16_t nStringId;
		};

		const Case cases[] = {
			{ 80, 30, 0, 0, 0 },
			{ 256, 256, VK_ESCAPE, BUTTONFLAG_HAS_DISABLED_FRAMES, 0 },
			{ 257, 40, VK_RETURN, BUTTONFLAG_HAS_DISABLED_FRAMES | BUTTONFLAG_IS_TOGGLE, 5103 },
			{ 600, 513, 0, BUTTONFLAG_SUBTITLE, 0xFFFF },
			{ 0, 0, 'A', 0x7F, 1 },
		};

		int32_t cellFile[4] = { 8 };
		for (const Case& testCase : cases)
		{
			CAPTURE(testCase.nWidth);
			CAPTURE(testCase.nHeight);
			CAPTURE(testCase.nActivationVirtualKey);
			CAPTURE(testCase.dwFlags);
			CAPTURE(testCase.nStringId);

			const auto buttons = [&]()
			{
				D2WinButtonStrc* pButtons[2] = {};
				for (int i = 0; i < 2; ++i)
				{
					const ControlGlobals& globals = *both_control_globals[i];
					*globals.ppControlList = nullptr;
					pButtons[i] = (i == 0 ? sut : original)(40, 450, testCase.nWidth, testCase.nHeight, reinterpret_cast<D2CellFileStrc*>(cellFile),
						&CallbackRecorder::Callback, testCase.nActivationVirtualKey, 3, testCase.dwFlags, testCase.nStringId, &CallbackRecorder::OtherCallback);
					REQUIRE(pButtons[i] != nullptr);
					CHECK_EQ(*globals.ppControlList, &pButtons[i]->controlHeader);
					*globals.ppControlList = nullptr;
				}
				return std::pair{ pButtons[0], pButtons[1] };
			}();

			CHECK_EQ(describe_differences(*buttons.first, *buttons.second, button_pointers()), "");
			FogMemoryMock::Free(buttons.first, __FILE__, __LINE__, 0);
			FogMemoryMock::Free(buttons.second, __FILE__, __LINE__, 0);
		}
	}

	// Setters and getters
	TEST_CASE_FIXTURE(D2WinButtonFixture<NoOpFixture>, "D2Win.0x6F8A6330 (#10110)")
	{
		const auto [is_pressed, original_is_pressed] = make_d2win_pair(BUTTON_IsPressed, 0x6F8A62F0);
		const auto [set_pressed, original_set_pressed] = make_d2win_pair(BUTTON_SetIsPressed, 0x6F8A6330);
		const auto [set_text, original_set_text] = make_d2win_pair(BUTTON_SetText, 0x6F8A6360);
		const auto [set_text_id, original_set_text_id] = make_d2win_pair(BUTTON_SetTextWithStringId, 0x6F8A63A0);
		const auto [set_coordinates, original_set_coordinates] = make_d2win_pair(BUTTON_SetCoordinates, 0x6F8A63F0);
		const auto [set_base_frame, original_set_base_frame] = make_d2win_pair(BUTTON_SetBaseFrame, 0x6F8A64A0);
		const auto [set_string_id, original_set_string_id] = make_d2win_pair(BUTTON_SetStringId, 0x6F8A6570);

		for (int32_t nPressed = 0; nPressed < 4; ++nPressed)
		{
			D2WinButtonStrc moo = make_button(0, 5, 0, nPressed & 1, nPressed >> 1, true);
			D2WinButtonStrc orig = make_button(1, 5, 0, nPressed & 1, nPressed >> 1, true);
			CAPTURE(nPressed);
			CHECK_EQ(is_pressed(&moo), original_is_pressed(&orig));
		}

		for (BOOL bPressed : { 0, 1, 5 })
		{
			D2WinButtonStrc moo = make_button(0, 5, 0, 0, 1, true);
			D2WinButtonStrc orig = make_button(1, 5, 0, 0, 1, true);
			set_pressed(&moo, bPressed);
			original_set_pressed(&orig, bPressed);
			CHECK_EQ(is_pressed(&moo), original_is_pressed(&orig));
			CHECK_EQ(describe_differences(moo, orig, button_pointers()), "");
		}

		D2WinButtonStrc moo = make_button(0, 5, 0, 0, 0, true);
		D2WinButtonStrc orig = make_button(1, 5, 0, 0, 0, true);
		const Unicode wszText[] = { 'O', 'k', 0 };
		set_text(&moo, (Font)3, wszText, 4);
		original_set_text(&orig, (Font)3, wszText, 4);
		CHECK_EQ(describe_differences(moo, orig, button_pointers()), "");

		set_text_id(&moo, (Font)1, 3456, 2);
		original_set_text_id(&orig, (Font)1, 3456, 2);
		CHECK_EQ(describe_differences(moo, orig, button_pointers()), "");

		set_coordinates(&moo, 1, 2, 3, 4);
		original_set_coordinates(&orig, 1, 2, 3, 4);
		set_base_frame(&moo, 11);
		original_set_base_frame(&orig, 11);
		set_string_id(&moo, 0xFFFE);
		original_set_string_id(&orig, 0xFFFE);
		CHECK_EQ(describe_differences(moo, orig, button_pointers()), "");
	}

	TEST_CASE_FIXTURE(D2WinButtonFixture<NoOpFixture>, "D2Win.0x6F8A6A10")
	{
		for (const ButtonState& state : button_states())
		{
			for (UINT nMessage : { (UINT)WM_LBUTTONDOWN, (UINT)WM_RBUTTONDOWN })
			{
				CAPTURE_BUTTON_STATE(state);
				CAPTURE(nMessage);
				compare_button_handlers(state, [&](int i, D2WinButtonStrc& button)
				{
					SMSGHANDLER_PARAMS msg = {};
					msg.hWindow = (HWND)&button;
					msg.nMessage = nMessage;
					return (int32_t)button_functions(i).pfHandleMouseDown(&msg);
				});
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinButtonFixture<NoOpFixture>, "D2Win.0x6F8A6AF0")
	{
		for (const ButtonState& state : button_states())
		{
			CAPTURE_BUTTON_STATE(state);
			compare_button_handlers(state, [&](int i, D2WinButtonStrc& button)
			{
				SMSGHANDLER_PARAMS msg = {};
				msg.hWindow = (HWND)&button;
				msg.nMessage = WM_LBUTTONUP;
				return button_functions(i).pfHandleMouseUp(&msg);
			});
		}
	}

	TEST_CASE_FIXTURE(D2WinButtonFixture<NoOpFixture>, "D2Win.0x6F8A6BB0")
	{
		for (const ButtonState& state : button_states())
		{
			for (UINT nMessage : { (UINT)WM_KEYDOWN, (UINT)WM_CHAR })
			{
				for (WPARAM wParam : { (WPARAM)VK_RETURN, (WPARAM)VK_ESCAPE })
				{
					for (bool bHandlers : { true, false })
					{
						if (!bHandlers && (nMessage != WM_KEYDOWN || wParam != VK_RETURN))
						{
							continue;
						}

						CAPTURE_BUTTON_STATE(state);
						CAPTURE(nMessage);
						CAPTURE(wParam);
						CAPTURE(bHandlers);
						compare_button_handlers(state, [&](int i, D2WinButtonStrc& button)
						{
							SMSGHANDLER_PARAMS msg = {};
							msg.hWindow = (HWND)&button;
							msg.nMessage = nMessage;
							msg.wParam = wParam;
							return button_functions(i).pfHandleVirtualKeyInput(&msg);
						}, bHandlers);
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinButtonFixture<NoOpFixture>, "D2Win.0x6F8A6430 (#10113)")
	{
		const auto [sut, original] = make_d2win_pair(BUTTON_SimulateClick, 0x6F8A6430);

		for (const ButtonState& state : button_states())
		{
			for (bool bHandlers : { true, false })
			{
				CAPTURE_BUTTON_STATE(state);
				CAPTURE(bHandlers);
				compare_button_handlers(state, [&, sut = sut, original = original](int i, D2WinButtonStrc& button)
				{
					SMSGHANDLER_PARAMS msg = {};
					msg.hWindow = (HWND)&button;
					msg.nMessage = WM_KEYDOWN;
					msg.wParam = VK_ESCAPE;
					(i == 0 ? sut : original)(&msg);
					return 0;
				}, bHandlers);
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinButtonFixture<NoOpFixture>, "D2Win.0x6F8A64D0")
	{
		const auto [sut, original] = make_d2win_pair(BUTTON_OnMouseWheelScrolled, 0x6F8A64D0);

		for (const ButtonState& state : button_states())
		{
			for (int32_t nIncrement : { -2, -1, 0, 1, 3 })
			{
				CAPTURE_BUTTON_STATE(state);
				CAPTURE(nIncrement);
				compare_button_handlers(state, [&, sut = sut, original = original](int i, D2WinButtonStrc& button)
				{
					return (int32_t)(i == 0 ? sut : original)(&button, nIncrement);
				});
			}
		}
	}
}
