#include <doctest.h>

#include <cstdint>
#include <utility>
#include <vector>

#include <Windows.h>

#include <D2WinMain.h>
#include <D2WinControlHeader.h>

#include "D2WinControlFixtures.h"


TEST_SUITE("D2WinControlTests")
{
	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AD120")
	{
		const auto [sut, original] = make_d2win_pair(CONTROL_AppendToList, 0x6F8AD120);

		const ControlListSetup setups[] = {
			{},
			{ { 0 } },
			{ { 0, 1, 2 } },
			{ { 3, 1 }, { 2 } },
		};

		for (const ControlListSetup& setup : setups)
		{
			for (int32_t nAppended : { 4, 5 })
			{
				CAPTURE(toString(setup.controlList));
				CAPTURE(nAppended);

				ControlListState states[2];
				int results[2];
				for (int i = 0; i < 2; ++i)
				{
					FakeControls controls(6);
					apply_setup(*both_control_globals[i], controls, setup);
					results[i] = (i == 0 ? sut : original)(controls.get(nAppended));
					states[i] = read_state(*both_control_globals[i], controls);
				}

				CHECK_EQ(results[0], results[1]);
				CHECK_EQ(states[0], states[1]);
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AD160")
	{
		const auto [sut, original] = make_d2win_pair(CONTROL_RemoveFromList, 0x6F8AD160);

		const ControlListSetup setups[] = {
			{},
			{ { 0 } },
			{ { 0, 1, 2 } },
			{ { 0, 1, 2 }, { 3 } },
			{ { 0, 1, 2 }, { 3, 4 }, 1, 1, 1, 1, 1 },
			{ { 2, 0 }, {}, 0, 2, 1, 2, 1 },
			{ {}, {}, 1, 1, 1, 1, 1 },
		};

		for (const ControlListSetup& setup : setups)
		{
			for (int32_t nRemoved : { 0, 1, 2, 5 })
			{
				CAPTURE(toString(setup.controlList));
				CAPTURE(toString(setup.removedControls));
				CAPTURE(nRemoved);

				ControlListState states[2];
				int results[2];
				for (int i = 0; i < 2; ++i)
				{
					FakeControls controls(6);
					apply_setup(*both_control_globals[i], controls, setup);
					results[i] = (i == 0 ? sut : original)(controls.get(nRemoved));
					states[i] = read_state(*both_control_globals[i], controls);
				}

				CHECK_EQ(results[0], results[1]);
				CHECK_EQ(states[0], states[1]);
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AE510 (#10033)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10033, 0x6F8AE510);
		const auto [sut_get, original_get] = make_d2win_pair(sub_6F8AE540, 0x6F8AE540);

		for (int32_t nModal : { -1, 0, 2 })
		{
			for (int32_t bDim : { 0, 1, 7 })
			{
				ControlListState states[2];
				int results[2];
				int32_t gets[2];
				for (int i = 0; i < 2; ++i)
				{
					FakeControls controls(3);
					apply_setup(*both_control_globals[i], controls, {});
					results[i] = (i == 0 ? sut : original)(controls.get(nModal), bDim);
					gets[i] = controls.index((i == 0 ? sut_get : original_get)());
					states[i] = read_state(*both_control_globals[i], controls);
				}

				CHECK_EQ(results[0], results[1]);
				CHECK_EQ(gets[0], gets[1]);
				CHECK_EQ(states[0], states[1]);
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AE4F0 (#10031)")
	{
		const auto [sut, original] = make_d2win_pair(CONTROL_SetEscapeButton, 0x6F8AE4F0);

		for (int32_t nButton : { 1, -1 })
		{
			ControlListState states[2];
			for (int i = 0; i < 2; ++i)
			{
				FakeControls controls(2);
				apply_setup(*both_control_globals[i], controls, { {}, {}, -1, -1, 0 });
				(i == 0 ? sut : original)(controls.get(nButton));
				states[i] = read_state(*both_control_globals[i], controls);
			}
			CHECK_EQ(states[0], states[1]);
		}
	}

	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AE4A0 (#10029)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10029, 0x6F8AE4A0);

		for (int nValue : { 0, 1, -5 })
		{
			sut(nValue);
			original(nValue);
			CHECK_EQ(*moo_control_globals().pShowCursor, nValue);
			CHECK_EQ(*original_control_globals().pShowCursor, nValue);
		}
	}

	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AE500 (#10032)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_IsMouseButtonPressed, 0x6F8AE500);

		for (int32_t bPressed : { 0, 1, 3 })
		{
			*moo_control_globals().pbIsMouseButtonPressed = bPressed;
			*original_control_globals().pbIsMouseButtonPressed = bPressed;
			CHECK_EQ(sut(), original());
		}
	}

	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AE530 (#10035)")
	{
		const auto [sut, original] = make_d2win_pair(CONTROL_GetType, 0x6F8AE530);

		CHECK_EQ(sut(nullptr), original(nullptr));
		for (int32_t nType = 0; nType <= D2WIN_IMAGE2 + 1; ++nType)
		{
			D2WinControlStrc control = {};
			control.nType = nType;
			CHECK_EQ(sut(&control), original(&control));
		}
	}

	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AD650 (#10170)")
	{
		const auto [sut, original] = make_d2win_pair(CONTROL_MouseInsideRect, 0x6F8AD650);

		const RECT rect = { 10, 20, 110, 70 };
		const POINT points[] = { { 10, 20 }, { 109, 69 }, { 110, 30 }, { 50, 70 }, { 9, 40 }, { 50, 19 }, { -1, -1 } };
		for (const POINT& point : points)
		{
			CAPTURE(point.x);
			CAPTURE(point.y);
			*moo_control_globals().pMousePosition = point;
			*original_control_globals().pMousePosition = point;
			CHECK_EQ(sut(&rect), original(&rect));
		}
	}

	// Flag setters and getters, on all the flag combinations of the first four bits and a few others
	TEST_CASE_FIXTURE(D2WinControlFixture<NoOpFixture>, "D2Win.0x6F8AD570 (#10025)")
	{
		const auto [set_enabled, original_set_enabled] = make_d2win_pair(CONTROL_SetEnabled, 0x6F8AD570);
		const auto [is_enabled, original_is_enabled] = make_d2win_pair(CONTROL_IsEnabled, 0x6F8AD5A0);
		const auto [set_visible, original_set_visible] = make_d2win_pair(CONTROL_SetVisible, 0x6F8AD5D0);
		const auto [is_visible, original_is_visible] = make_d2win_pair(CONTROL_IsVisible, 0x6F8AD620);
		const auto [set_fourth, original_set_fourth] = make_d2win_pair(D2Win_10030_CONTROL_ToggleFourthFlag, 0x6F8AE4B0);

		// Disabling a null control does nothing
		set_enabled(nullptr, FALSE);
		original_set_enabled(nullptr, FALSE);

		std::vector<uint32_t> flags;
		for (uint32_t dwFlags = 0; dwFlags < 0x10; ++dwFlags)
		{
			flags.push_back(dwFlags);
			flags.push_back(dwFlags | 0x80000030);
		}

		for (uint32_t dwFlags : flags)
		{
			for (int bValue : { 0, 1, 2 })
			{
				CAPTURE(dwFlags);
				CAPTURE(bValue);

				D2WinControlStrc moo = {};
				D2WinControlStrc orig = {};

				moo.dwFlags = orig.dwFlags = dwFlags;
				set_enabled(&moo, bValue);
				original_set_enabled(&orig, bValue);
				CHECK_EQ(moo.dwFlags, orig.dwFlags);
				CHECK_EQ(is_enabled(&moo), original_is_enabled(&orig));

				moo.dwFlags = orig.dwFlags = dwFlags;
				set_visible(&moo, bValue);
				original_set_visible(&orig, bValue);
				CHECK_EQ(moo.dwFlags, orig.dwFlags);
				CHECK_EQ(is_visible(&moo), original_is_visible(&orig));

				moo.dwFlags = orig.dwFlags = dwFlags;
				set_fourth(&moo, bValue);
				original_set_fourth(&orig, bValue);
				CHECK_EQ(moo.dwFlags, orig.dwFlags);

				moo.dwFlags = orig.dwFlags = dwFlags;
				CHECK_EQ(is_enabled(&moo), original_is_enabled(&orig));
				CHECK_EQ(is_visible(&moo), original_is_visible(&orig));
			}
		}
	}
}
