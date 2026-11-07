#pragma once


#include <cstdint>
#include <utility>
#include <vector>

#include <Windows.h>

#include <doctest.h>

#include <D2WinMain.h>
#include <D2WinControlHeader.h>

#include "D2WinTestFixtures.h"


extern D2WinControlStrc* gpControlList_6F8FE24C;
extern D2WinControlStrc* dword_6F8FE250;
extern D2WinEditBoxStrc* gpNextFocusedEditBox;
extern D2WinEditBoxStrc* gpFocusedEditBox;
extern void* gpEscapeButton;
extern D2WinControlStrc* dword_6F8FE264;
extern int32_t dword_6F8FE278;
extern int32_t dword_6F8BDE18;
extern int32_t gbIsMouseButtonPressed;
extern POINT gMousePosition_6F8FE234;


// The globals of the control lists of one implementation
struct ControlGlobals
{
	D2WinControlStrc** ppControlList;			// 0x6F8FE24C
	D2WinControlStrc** ppRemovedControls;		// 0x6F8FE250, controls removed from the control list
	D2WinEditBoxStrc** ppNextFocusedEditBox;	// 0x6F8FE258
	D2WinEditBoxStrc** ppFocusedEditBox;		// 0x6F8FE25C
	void** ppEscapeButton;						// 0x6F8FE260
	D2WinControlStrc** ppModalControlList;		// 0x6F8FE264
	int32_t* pbDimBackground;					// 0x6F8FE278
	int32_t* pShowCursor;						// 0x6F8BDE18
	int32_t* pbIsMouseButtonPressed;			// 0x6F8FE270
	POINT* pMousePosition;						// 0x6F8FE234
};

inline const ControlGlobals& moo_control_globals()
{
	static const ControlGlobals globals = {
		&gpControlList_6F8FE24C, &dword_6F8FE250, &gpNextFocusedEditBox, &gpFocusedEditBox, &gpEscapeButton,
		&dword_6F8FE264, &dword_6F8FE278, &dword_6F8BDE18, &gbIsMouseButtonPressed, &gMousePosition_6F8FE234,
	};
	return globals;
}

inline const ControlGlobals& original_control_globals()
{
	static const ControlGlobals globals = {
		original_d2win_global<D2WinControlStrc*>(0x6F8FE24C),
		original_d2win_global<D2WinControlStrc*>(0x6F8FE250),
		original_d2win_global<D2WinEditBoxStrc*>(0x6F8FE258),
		original_d2win_global<D2WinEditBoxStrc*>(0x6F8FE25C),
		original_d2win_global<void*>(0x6F8FE260),
		original_d2win_global<D2WinControlStrc*>(0x6F8FE264),
		original_d2win_global<int32_t>(0x6F8FE278),
		original_d2win_global<int32_t>(0x6F8BDE18),
		original_d2win_global<int32_t>(0x6F8FE270),
		original_d2win_global<POINT>(0x6F8FE234),
	};
	return globals;
}

inline const ControlGlobals* const both_control_globals[] = { &moo_control_globals(), &original_control_globals() };

// Saves the control globals of both implementations and restores them when destroyed
struct ControlGlobalsGuard
{
	struct Saved
	{
		D2WinControlStrc* pControlList;
		D2WinControlStrc* pRemovedControls;
		D2WinEditBoxStrc* pNextFocusedEditBox;
		D2WinEditBoxStrc* pFocusedEditBox;
		void* pEscapeButton;
		D2WinControlStrc* pModalControlList;
		int32_t bDimBackground;
		int32_t nShowCursor;
		int32_t bIsMouseButtonPressed;
		POINT mousePosition;
	};
	Saved saved[2];

	ControlGlobalsGuard()
	{
		for (int i = 0; i < 2; ++i)
		{
			const ControlGlobals& globals = *both_control_globals[i];
			saved[i] = { *globals.ppControlList, *globals.ppRemovedControls, *globals.ppNextFocusedEditBox, *globals.ppFocusedEditBox, *globals.ppEscapeButton,
				*globals.ppModalControlList, *globals.pbDimBackground, *globals.pShowCursor, *globals.pbIsMouseButtonPressed, *globals.pMousePosition };
		}
	}

	~ControlGlobalsGuard()
	{
		for (int i = 0; i < 2; ++i)
		{
			const ControlGlobals& globals = *both_control_globals[i];
			*globals.ppControlList = saved[i].pControlList;
			*globals.ppRemovedControls = saved[i].pRemovedControls;
			*globals.ppNextFocusedEditBox = saved[i].pNextFocusedEditBox;
			*globals.ppFocusedEditBox = saved[i].pFocusedEditBox;
			*globals.ppEscapeButton = saved[i].pEscapeButton;
			*globals.ppModalControlList = saved[i].pModalControlList;
			*globals.pbDimBackground = saved[i].bDimBackground;
			*globals.pShowCursor = saved[i].nShowCursor;
			*globals.pbIsMouseButtonPressed = saved[i].bIsMouseButtonPressed;
			*globals.pMousePosition = saved[i].mousePosition;
		}
	}
};

// Saves the control globals of both implementations and restores them at the end of the test
template<class Fixture>
struct D2WinControlFixture : D2WinFixture<Fixture>
{
	ControlGlobalsGuard controlGlobalsGuard;
};

// State of the control lists, the controls being given by their indices
struct ControlListState
{
	std::vector<int32_t> controlList;
	std::vector<int32_t> removedControls;
	int32_t nNextFocusedEditBox;
	int32_t nFocusedEditBox;
	int32_t nEscapeButton;
	int32_t nModalControlList;
	int32_t bDimBackground;

	bool operator==(const ControlListState& other) const
	{
		return controlList == other.controlList && removedControls == other.removedControls && nNextFocusedEditBox == other.nNextFocusedEditBox
			&& nFocusedEditBox == other.nFocusedEditBox && nEscapeButton == other.nEscapeButton && nModalControlList == other.nModalControlList
			&& bDimBackground == other.bDimBackground;
	}
};

inline doctest::String toString(const std::vector<int32_t>& indices)
{
	doctest::String text = "[";
	for (size_t i = 0; i < indices.size(); ++i)
	{
		text += (i ? ", " : "");
		text += doctest::toString(indices[i]);
	}
	return text + "]";
}

inline doctest::String toString(const ControlListState& state)
{
	return "{ list " + toString(state.controlList) + ", removed " + toString(state.removedControls)
		+ ", next focus " + doctest::toString(state.nNextFocusedEditBox) + ", focus " + doctest::toString(state.nFocusedEditBox)
		+ ", escape " + doctest::toString(state.nEscapeButton) + ", modal " + doctest::toString(state.nModalControlList)
		+ ", dim " + doctest::toString(state.bDimBackground) + " }";
}

inline ControlListState read_state(const ControlGlobals& globals, const FakeControls& controls)
{
	return {
		controls.list(*globals.ppControlList),
		controls.list(*globals.ppRemovedControls),
		controls.index(*globals.ppNextFocusedEditBox),
		controls.index(*globals.ppFocusedEditBox),
		controls.index(*globals.ppEscapeButton),
		controls.index(*globals.ppModalControlList),
		*globals.pbDimBackground,
	};
}

// Initial state of a scenario, controls given by their indices
struct ControlListSetup
{
	std::vector<int32_t> controlList;
	std::vector<int32_t> removedControls;
	int32_t nNextFocusedEditBox = -1;
	int32_t nFocusedEditBox = -1;
	int32_t nEscapeButton = -1;
	int32_t nModalControlList = -1;
	int32_t bDimBackground = 0;
};

inline D2WinControlStrc* link_controls(FakeControls& controls, const std::vector<int32_t>& indices)
{
	for (size_t i = 0; i < indices.size(); ++i)
	{
		controls.get(indices[i])->pNext = i + 1 < indices.size() ? controls.get(indices[i + 1]) : nullptr;
	}
	return indices.empty() ? nullptr : controls.get(indices[0]);
}

inline void apply_setup(const ControlGlobals& globals, FakeControls& controls, const ControlListSetup& setup)
{
	for (D2WinControlStrc& control : controls.controls)
	{
		control.pNext = nullptr;
	}
	*globals.ppControlList = link_controls(controls, setup.controlList);
	*globals.ppRemovedControls = link_controls(controls, setup.removedControls);
	*globals.ppNextFocusedEditBox = reinterpret_cast<D2WinEditBoxStrc*>(controls.get(setup.nNextFocusedEditBox));
	*globals.ppFocusedEditBox = reinterpret_cast<D2WinEditBoxStrc*>(controls.get(setup.nFocusedEditBox));
	*globals.ppEscapeButton = controls.get(setup.nEscapeButton);
	*globals.ppModalControlList = controls.get(setup.nModalControlList);
	*globals.pbDimBackground = setup.bDimBackground;
}
