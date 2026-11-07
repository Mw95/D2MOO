#include <doctest.h>

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <Windows.h>

#include <D2WinEditBox.h>

#include "D2WinControlFixtures.h"
#include "D2WinFontFixtures.h"


extern D2WinEditBoxStrc* dword_6F8FD8B0;
extern int dword_6F8FD8B4;


namespace
{
#define D2WIN_EDITBOX_FUNCTIONS(X) \
	X(Create, D2Win_10070_EDITBOX_Create, 0x6F8A6C80) \
	X(Destroy, D2Win_10071_EDITBOX_Destroy, 0x6F8A6DC0) \
	X(SetKeyFilter, EDITBOX_SetKeyFilter, 0x6F8A6E10) \
	X(SetChangeCallback, EDITBOX_SetChangeCallback, 0x6F8A6E60) \
	X(ClearSelection, EDITBOX_ClearSelection, 0x6F8A6EB0) \
	X(SelectAll, D2Win_10082, 0x6F8A6F10) \
	X(HandleChar, D2Win_10074, 0x6F8A6F70) \
	X(DeleteSelection, sub_6F8A7970, 0x6F8A7970) \
	X(HandleKeyDown, EDITBOX_HandleKeyDown, 0x6F8A7AB0) \
	X(SetMaxLength, EDITBOX_SetMaxLength, 0x6F8A80A0) \
	X(SetWinText, D2Win_10076, 0x6F8A80F0) \
	X(SetText, EDITBOX_SetText, 0x6F8A8140) \
	X(GetText, D2Win_10077_EDITBOX_GetText, 0x6F8A81E0) \
	X(SetNextEditBox, D2Win_10080_EDITBOX_SetNextEditBox, 0x6F8A8230) \
	X(DrawSingleLine, EDITBOX_DrawSingleLine, 0x6F8A82D0) \
	X(DrawMultiLine, EDITBOX_DrawMultiLine, 0x6F8A86C0) \
	X(GetCaretPosition, EDITBOX_GetCaretPosition, 0x6F8A8D60) \
	X(HandleSingleLineMouseDown, EDITBOX_HandleSingleLineMouseDown, 0x6F8A9120) \
	X(HandleMouseUp, EDITBOX_HandleMouseUp, 0x6F8A93A0) \
	X(PlaceMultiLineCaret, EDITBOX_PlaceMultiLineCaret, 0x6F8A9410) \
	X(HandleMultiLineMouseDown, sub_6F8A97D0, 0x6F8A97D0) \
	X(IsNumber, D2Win_10078_IsNumber, 0x6F8A9850) \
	X(IsLetter, D2Win_10079_IsLetter, 0x6F8A9870) \
	X(UpdateVisibleRange, sub_6F8A98A0, 0x6F8A98A0)

// The edit box functions of one implementation
struct EditBoxApi
{
#define D2WIN_DECLARE_FUNCTION(name, function, address) decltype(&function) name;
	D2WIN_EDITBOX_FUNCTIONS(D2WIN_DECLARE_FUNCTION)
#undef D2WIN_DECLARE_FUNCTION
};

const EditBoxApi& editbox_api(int nImplementation)
{
#define D2WIN_MOO_FUNCTION(name, function, address) &function,
#define D2WIN_ORIGINAL_FUNCTION(name, function, address) reinterpret_cast<decltype(&function)>(original_d2win_address(address)),
	static const EditBoxApi moo = { D2WIN_EDITBOX_FUNCTIONS(D2WIN_MOO_FUNCTION) };
	static const EditBoxApi original = { D2WIN_EDITBOX_FUNCTIONS(D2WIN_ORIGINAL_FUNCTION) };
#undef D2WIN_MOO_FUNCTION
#undef D2WIN_ORIGINAL_FUNCTION
	return nImplementation == 0 ? moo : original;
}

// Clipboard and keyboard functions of user32
struct EditBoxInputMock
{
	static inline bool bShift = false;
	static inline bool bClipboardAvailable = true;
	static inline std::string szClipboard;
	static inline std::vector<std::string> log;

	static SHORT WINAPI GetKeyState(int nVirtualKey)
	{
		return (SHORT)(nVirtualKey == VK_SHIFT && bShift ? 0x8001 : 0);
	}

	static BOOL WINAPI IsClipboardFormatAvailable(UINT nFormat)
	{
		return bClipboardAvailable && nFormat == CF_TEXT;
	}

	static BOOL WINAPI OpenClipboard(HWND)
	{
		return TRUE;
	}

	static BOOL WINAPI CloseClipboard()
	{
		return TRUE;
	}

	static BOOL WINAPI EmptyClipboard()
	{
		log.push_back("EmptyClipboard");
		return TRUE;
	}

	static HANDLE WINAPI GetClipboardData(UINT nFormat)
	{
		if (nFormat != CF_TEXT)
		{
			return nullptr;
		}

		// Leaked like the clipboard data owned by the system
		HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, szClipboard.size() + 1);
		std::memcpy(GlobalLock(hData), szClipboard.c_str(), szClipboard.size() + 1);
		GlobalUnlock(hData);
		return hData;
	}

	static HANDLE WINAPI SetClipboardData(UINT nFormat, HANDLE hData)
	{
		const char* szData = static_cast<const char*>(GlobalLock(hData));
		szClipboard = szData ? szData : "";
		GlobalUnlock(hData);
		log.push_back("SetClipboardData " + std::to_string(nFormat) + " [" + szClipboard + "]");
		return hData;
	}
};

// Callbacks of the edit boxes
struct EditBoxCallbacks
{
	static inline std::vector<std::string> log;

	static int32_t __stdcall OnReturn(const Unicode* wszText)
	{
		log.push_back("OnReturn " + (wszText ? "[" + narrow_unicode(wszText) + "]" : std::string("null")));
		return 1;
	}

	// Refuses 'x', replaces 'q' with 'Q'
	static BOOL __stdcall KeyFilter(D2WinEditBoxStrc*, int32_t nPosition, char* pChar)
	{
		log.push_back("KeyFilter " + std::to_string(nPosition) + " " + std::to_string((uint8_t)*pChar));
		if (*pChar == 'q')
		{
			*pChar = 'Q';
		}
		return *pChar != 'x';
	}

	static void __stdcall OnChange(int32_t nValue)
	{
		log.push_back("OnChange " + std::to_string(nValue));
	}
};

int32_t* message_depth(int nImplementation)
{
	return nImplementation == 0 ? &dword_6F8FE254 : original_d2win_global<int32_t>(0x6F8FE254);
}

// The double click globals
struct DoubleClickGlobals
{
	D2WinEditBoxStrc** ppLastClickedEditBox;
	int* pLastClickTickCount;
};

const DoubleClickGlobals& double_click_globals(int nImplementation)
{
	static const DoubleClickGlobals moo = { &dword_6F8FD8B0, &dword_6F8FD8B4 };
	static const DoubleClickGlobals original = { original_d2win_global<D2WinEditBoxStrc*>(0x6F8FD8B0), original_d2win_global<int>(0x6F8FD8B4) };
	return nImplementation == 0 ? moo : original;
}

template<class Fixture>
struct D2WinEditBoxFixture : D2WinFontFixture<Fixture>
{
	ControlGlobalsGuard controlGlobalsGuard;
	ImportTablePatch inputPatches;
	int32_t savedDepths[2];
	D2WinEditBoxStrc* savedLastClicked[2];
	int savedLastTicks[2];

	D2WinEditBoxFixture()
	{
		const auto patch = [this](const char* szName, const void* pReplacement)
		{
			inputPatches.patch(GetModuleHandleA(nullptr), "USER32.dll", szName, pReplacement, false);
			inputPatches.patch(get_original_d2win(), "USER32.dll", szName, pReplacement, false);
		};
		patch("GetKeyState", reinterpret_cast<const void*>(&EditBoxInputMock::GetKeyState));
		patch("IsClipboardFormatAvailable", reinterpret_cast<const void*>(&EditBoxInputMock::IsClipboardFormatAvailable));
		patch("OpenClipboard", reinterpret_cast<const void*>(&EditBoxInputMock::OpenClipboard));
		patch("CloseClipboard", reinterpret_cast<const void*>(&EditBoxInputMock::CloseClipboard));
		patch("EmptyClipboard", reinterpret_cast<const void*>(&EditBoxInputMock::EmptyClipboard));
		patch("GetClipboardData", reinterpret_cast<const void*>(&EditBoxInputMock::GetClipboardData));
		patch("SetClipboardData", reinterpret_cast<const void*>(&EditBoxInputMock::SetClipboardData));

		for (int i = 0; i < 2; ++i)
		{
			savedDepths[i] = *message_depth(i);
			*message_depth(i) = 1;
			savedLastClicked[i] = *double_click_globals(i).ppLastClickedEditBox;
			savedLastTicks[i] = *double_click_globals(i).pLastClickTickCount;
		}
	}

	~D2WinEditBoxFixture()
	{
		for (int i = 0; i < 2; ++i)
		{
			*message_depth(i) = savedDepths[i];
			*double_click_globals(i).ppLastClickedEditBox = savedLastClicked[i];
			*double_click_globals(i).pLastClickTickCount = savedLastTicks[i];
		}
	}
};

// Name of a function pointer of an edit box, so that both implementations can be compared
template<typename Function>
std::string function_name(int nImplementation, Function pFunction)
{
	if (pFunction == nullptr)
	{
		return "null";
	}

	const EditBoxApi& api = editbox_api(nImplementation);
	const void* pAddress = reinterpret_cast<const void*>(pFunction);
#define D2WIN_NAME_FUNCTION(name, function, address) if (pAddress == reinterpret_cast<const void*>(api.name)) return #name;
	D2WIN_EDITBOX_FUNCTIONS(D2WIN_NAME_FUNCTION)
#undef D2WIN_NAME_FUNCTION
	if (pAddress == reinterpret_cast<const void*>(&CallbackRecorder::Callback)) return "Callback";
	if (pAddress == reinterpret_cast<const void*>(&EditBoxCallbacks::OnReturn)) return "OnReturn";
	if (pAddress == reinterpret_cast<const void*>(&EditBoxCallbacks::KeyFilter)) return "KeyFilter";
	if (pAddress == reinterpret_cast<const void*>(&EditBoxCallbacks::OnChange)) return "OnChange";
	return "unknown";
}

struct EditBoxPair
{
	D2WinEditBoxStrc* pEditBox;
	D2WinEditBoxStrc* pSecond;

	std::string name(const void* pPointer) const
	{
		return pPointer == nullptr ? "null" : pPointer == pEditBox ? "first" : pPointer == pSecond ? "second" : "unknown";
	}
};

std::string describe_editbox(int nImplementation, const EditBoxPair& boxes, const D2WinEditBoxStrc* pEditBox)
{
	const D2WinControlStrc& header = pEditBox->controlHeader;
	std::string szText = "type " + std::to_string(header.nType) + " flags " + std::to_string(header.dwFlags)
		+ " rect " + std::to_string(header.nImageX) + "," + std::to_string(header.nImageY) + "," + std::to_string(header.nWidth) + "," + std::to_string(header.nHeight)
		+ " draw " + function_name(nImplementation, header.pfDraw) + " down " + function_name(nImplementation, header.pfHandleMouseDown)
		+ " up " + function_name(nImplementation, header.pfHandleMouseUp) + " char " + function_name(nImplementation, header.pfHandleCharInput)
		+ " key " + function_name(nImplementation, header.pfHandleVirtualKeyInput) + " callback " + function_name(nImplementation, header.pfCallback)
		+ " next control " + boxes.name(header.pNext);
	szText += "\ninset " + std::to_string(pEditBox->nTextInsetX) + "," + std::to_string(pEditBox->nTextInsetY)
		+ " max " + std::to_string(pEditBox->nMaxLength) + " visible " + std::to_string(pEditBox->nFirstVisibleChar) + "-" + std::to_string(pEditBox->nLastVisibleChar)
		+ " selection " + std::to_string(pEditBox->nSelectionStart) + "-" + std::to_string(pEditBox->nSelectionEnd)
		+ " caret " + std::to_string(pEditBox->nCaretPosition) + " flags " + std::to_string(pEditBox->dwEditBoxFlags)
		+ " return " + function_name(nImplementation, pEditBox->pfOnReturn) + " filter " + function_name(nImplementation, pEditBox->pfKeyFilter)
		+ " change " + function_name(nImplementation, pEditBox->pfOnChange) + " font " + std::to_string(pEditBox->eFont) + " color " + std::to_string(pEditBox->nTextColor)
		+ " next " + boxes.name(pEditBox->pNext) + " previous " + boxes.name(pEditBox->pPrevious) + " mouse selecting " + std::to_string(pEditBox->bMouseSelecting)
		+ "\ntext [" + narrow_unicode(pEditBox->wszText) + "]";
	return szText;
}

std::string describe_state(int nImplementation, const EditBoxPair& boxes)
{
	const ControlGlobals& globals = *both_control_globals[nImplementation];
	const DoubleClickGlobals& doubleClick = double_click_globals(nImplementation);
	std::string szText = describe_editbox(nImplementation, boxes, boxes.pEditBox)
		+ "\nfocus " + boxes.name(*globals.ppFocusedEditBox) + " next focus " + boxes.name(*globals.ppNextFocusedEditBox)
		+ " last clicked " + boxes.name(*doubleClick.ppLastClickedEditBox) + " at " + std::to_string(*doubleClick.pLastClickTickCount)
		+ " depth " + std::to_string(*message_depth(nImplementation));
	for (const std::string& szCall : EditBoxCallbacks::log)
	{
		szText += "\n" + szCall;
	}
	for (const std::string& szCall : CallbackRecorder::log)
	{
		szText += "\n" + szCall;
	}
	for (const std::string& szCall : EditBoxInputMock::log)
	{
		szText += "\n" + szCall;
	}
	szText += "\nclipboard [" + EditBoxInputMock::szClipboard + "]";
	return szText;
}

using EditBoxOperation = std::function<std::string(int nImplementation, const EditBoxApi& api, const EditBoxPair& boxes)>;
using EditBoxOperations = std::vector<std::pair<std::string, EditBoxOperation>>;

void add_chars(EditBoxOperations& operations, const std::string& szChars)
{
	for (char c : szChars)
	{
		operations.emplace_back("Char " + std::to_string((uint8_t)c), [c](int, const EditBoxApi& api, const EditBoxPair& boxes)
		{
			return std::to_string(api.HandleChar(boxes.pEditBox, (uint8_t)c));
		});
	}
}

void add_keys(EditBoxOperations& operations, std::initializer_list<int> keys, bool bShift = false)
{
	for (int nKey : keys)
	{
		operations.emplace_back("Key " + std::to_string(nKey) + (bShift ? " shift" : ""), [nKey, bShift](int, const EditBoxApi& api, const EditBoxPair& boxes)
		{
			EditBoxInputMock::bShift = bShift;
			const int32_t nResult = api.HandleKeyDown(boxes.pEditBox, (char)nKey);
			EditBoxInputMock::bShift = false;
			return std::to_string(nResult);
		});
	}
}

// Tick count of the start of the scenarios. The clicks happen shortly after, so that the fake fonts are not unloaded.
constexpr DWORD nBaseTickCount = 5000 << 10;

void add_click(EditBoxOperations& operations, int32_t nOffsetX, int32_t nOffsetY, DWORD dwTick, bool bShift = false)
{
	operations.emplace_back("Click " + std::to_string(nOffsetX) + "," + std::to_string(nOffsetY) + " at " + std::to_string(dwTick) + (bShift ? " shift" : ""),
		[=](int nImplementation, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		D2WinEditBoxStrc* pEditBox = boxes.pEditBox;
		*both_control_globals[nImplementation]->pMousePosition = { pEditBox->controlHeader.nImageX + nOffsetX, pEditBox->controlHeader.nImageY - pEditBox->controlHeader.nHeight + nOffsetY };
		TickCountMock::dwTickCount = nBaseTickCount + dwTick;
		EditBoxInputMock::bShift = bShift;
		SMSGHANDLER_PARAMS msg = {};
		msg.hWindow = (HWND)pEditBox;
		msg.nMessage = WM_LBUTTONDOWN;
		const int32_t nDown = pEditBox->controlHeader.pfHandleMouseDown(&msg);
		msg.nMessage = WM_LBUTTONUP;
		const int32_t nUp = api.HandleMouseUp(&msg);
		EditBoxInputMock::bShift = false;
		return std::to_string(nDown) + " " + std::to_string(nUp);
	});
}

EditBoxOperations editbox_operations(bool bMultiLine)
{
	EditBoxOperations operations;
	const auto add = [&](std::string szName, EditBoxOperation operation) { operations.emplace_back(std::move(szName), std::move(operation)); };

	add("Focus", [](int nImplementation, const EditBoxApi&, const EditBoxPair& boxes)
	{
		*both_control_globals[nImplementation]->ppFocusedEditBox = boxes.pEditBox;
		return std::string();
	});
	add_chars(operations, "Hello world");
	add_keys(operations, { VK_LEFT, VK_LEFT, VK_LEFT });
	add_keys(operations, { VK_LEFT, VK_LEFT }, true);
	add_chars(operations, "\x03");
	add_keys(operations, { VK_HOME });
	add_keys(operations, { VK_END }, true);
	add_chars(operations, "\x18");
	add_chars(operations, "\x16\x16");
	add_keys(operations, { VK_HOME, VK_RIGHT, VK_RIGHT, VK_DELETE, VK_BACK, VK_END, VK_BACK });
	add_chars(operations, "\x01");
	add_chars(operations, "abc\x7F\xFF\x0E" "def");
	if (bMultiLine)
	{
		add_chars(operations, "\r" "second line\r\rfourth");
		add_keys(operations, { VK_UP, VK_UP, VK_RIGHT, VK_DOWN, VK_DOWN, VK_DOWN, VK_UP });
		add_keys(operations, { VK_UP, VK_DOWN }, true);
		add_chars(operations, "Z");
	}
	add("GetCaretPosition", [](int, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		int32_t nX = -1;
		int32_t nY = -1;
		api.GetCaretPosition(boxes.pEditBox, &nX, &nY);
		return std::to_string(nX) + "," + std::to_string(nY);
	});

	// Clicks and double clicks
	add_click(operations, 3, 10, 1000);
	add_click(operations, 40, 10, 2000);
	add_click(operations, 40, 10, 2100);
	add_click(operations, 80, 10, 5000, true);
	add_click(operations, 500, 10, 9000);
	add_click(operations, 20, 30, 12000);
	add_click(operations, 20, -30, 15000);

	add("SetMaxLength", [](int, const EditBoxApi& api, const EditBoxPair& boxes) { api.SetMaxLength(boxes.pEditBox, 12); return std::string(); });
	add_chars(operations, "0123456789");
	add("SetText", [](int, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		static const std::vector<Unicode> wszText = to_unicode("A text longer than the maximum length of the edit box");
		return std::to_string(api.SetText(boxes.pEditBox, wszText.data())) + " [" + narrow_unicode(api.GetText(boxes.pEditBox)) + "]";
	});
	add("SetMaxLength 256", [](int, const EditBoxApi& api, const EditBoxPair& boxes) { api.SetMaxLength(boxes.pEditBox, 256); return std::string(); });
	add("SetWinText", [](int, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		return std::to_string(api.SetWinText(boxes.pEditBox, "Win \xE9t\xE9 text that is long enough to scroll the visible range of the box")) + " [" + narrow_unicode(api.GetText(boxes.pEditBox)) + "]";
	});
	add("UpdateVisibleRange", [](int, const EditBoxApi& api, const EditBoxPair& boxes) { api.UpdateVisibleRange(boxes.pEditBox); return std::string(); });
	add_keys(operations, { VK_HOME, VK_RIGHT, VK_RIGHT, VK_RIGHT });
	add_keys(operations, { VK_END }, true);
	add("DeleteSelection", [](int, const EditBoxApi& api, const EditBoxPair& boxes) { api.DeleteSelection(boxes.pEditBox); return std::string(); });
	add("SelectAll", [](int, const EditBoxApi& api, const EditBoxPair& boxes) { return std::to_string(api.SelectAll(boxes.pEditBox)); });
	add("ClearSelection", [](int, const EditBoxApi& api, const EditBoxPair& boxes) { api.ClearSelection(boxes.pEditBox); return std::string(); });

	// Key filter and change callback
	add("SetKeyFilter", [](int, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		api.SetKeyFilter(boxes.pEditBox, &EditBoxCallbacks::KeyFilter);
		api.SetChangeCallback(boxes.pEditBox, &EditBoxCallbacks::OnChange);
		return std::string();
	});
	add_chars(operations, "aqxz\t");
	add("Paste filtered", [](int, const EditBoxApi&, const EditBoxPair&) { EditBoxInputMock::szClipboard = "pqr"; return std::string(); });
	add_chars(operations, "\x16");
	add("Paste refused", [](int, const EditBoxApi&, const EditBoxPair&) { EditBoxInputMock::szClipboard = "abxcd"; return std::string(); });
	add_chars(operations, "\x16");
	add("Number filter", [](int, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		api.SetKeyFilter(boxes.pEditBox, api.IsNumber);
		return std::string();
	});
	add_chars(operations, "1a2");
	add("Letter filter", [](int, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		api.SetKeyFilter(boxes.pEditBox, reinterpret_cast<EditBoxKeyFilterCallback>(api.IsLetter));
		return std::string();
	});
	add_chars(operations, "1a2B");
	add("No filter", [](int, const EditBoxApi& api, const EditBoxPair& boxes) { api.SetKeyFilter(boxes.pEditBox, nullptr); return std::string(); });

	// Tab to the next edit box, Enter and Escape
	add("SetNextEditBox", [](int, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		api.SetNextEditBox(boxes.pEditBox, boxes.pSecond);
		api.SetNextEditBox(boxes.pSecond, boxes.pEditBox);
		return std::string();
	});
	add_keys(operations, { VK_TAB });
	add_keys(operations, { VK_TAB }, true);
	add_keys(operations, { VK_RETURN, VK_ESCAPE });
	add_chars(operations, "\r\x1B");
	add("Disabled", [](int, const EditBoxApi& api, const EditBoxPair& boxes)
	{
		boxes.pEditBox->controlHeader.dwFlags = 4;
		const int32_t nChar = api.HandleChar(boxes.pEditBox, 'k');
		const int32_t nKey = api.HandleKeyDown(boxes.pEditBox, VK_BACK);
		boxes.pEditBox->controlHeader.dwFlags = 5;
		return std::to_string(nChar) + " " + std::to_string(nKey);
	});
	return operations;
}
}


TEST_SUITE("D2WinEditBoxTests")
{
	TEST_CASE_FIXTURE(D2WinEditBoxFixture<NoOpFixture>, "D2Win.0x6F8A9850 (#10078)")
	{
		const auto [is_number, original_is_number] = make_d2win_pair(D2Win_10078_IsNumber, 0x6F8A9850);
		const auto [is_letter, original_is_letter] = make_d2win_pair(D2Win_10079_IsLetter, 0x6F8A9870);

		for (int nChar = 0; nChar < 256; ++nChar)
		{
			char c = (char)nChar;
			char d = (char)nChar;
			CAPTURE(nChar);
			CHECK_EQ(is_number(nullptr, 0, &c), original_is_number(nullptr, 0, &d));
			CHECK_EQ(is_letter(0, 0, &c), original_is_letter(0, 0, &d));
			CHECK_EQ(c, d);
		}
	}

	// Runs the same scenario on edit boxes created with different settings, and compares the edit boxes after each step
	TEST_CASE_FIXTURE(D2WinEditBoxFixture<NoOpFixture>, "D2Win.0x6F8A6C80 (#10070)")
	{
		struct Setup
		{
			const char* szName;
			int32_t nWidth;
			int32_t nHeight;
			uint32_t dwFlags;
			bool bFont;
			bool bReturn;
		};

		const Setup setups[] = {
			{ "Single line", 200, 20, 0, false, true },
			{ "Password", 150, 20, EDITBOX_PASSWORD, true, false },
			{ "Keep editing", 120, 25, EDITBOX_RETURN_KEEPS_EDITING | EDITBOX_TAB_TO_KEY_FILTER | EDITBOX_ALLOW_COLOR_CODE | EDITBOX_ALLOW_CHAR_14, false, true },
			{ "Multi line", 160, 80, EDITBOX_MULTILINE, true, true },
			{ "Narrow multi line", 60, 120, EDITBOX_MULTILINE | EDITBOX_RETURN_KEEPS_EDITING, false, false },
		};

		int32_t fontInfo[2] = { D2FONT_FONT8, 3 };
		int32_t cellFile[4] = { 2 };

		for (const Setup& setup : setups)
		{
			CAPTURE(setup.szName);
			const EditBoxOperations operations = editbox_operations((setup.dwFlags & EDITBOX_MULTILINE) != 0);

			std::vector<std::string> logs[2];
			for (int i = 0; i < 2; ++i)
			{
				TickCountMock::dwTickCount = nBaseTickCount;
				install_fonts(false);
				const EditBoxApi& api = editbox_api(i);
				const ControlGlobals& globals = *both_control_globals[i];
				*globals.ppControlList = nullptr;
				*globals.ppRemovedControls = nullptr;
				*globals.ppFocusedEditBox = nullptr;
				*globals.ppNextFocusedEditBox = nullptr;
				*double_click_globals(i).ppLastClickedEditBox = nullptr;
				*double_click_globals(i).pLastClickTickCount = 0;
				EditBoxInputMock::szClipboard.clear();
				EditBoxInputMock::log.clear();
				EditBoxCallbacks::log.clear();
				CallbackRecorder::reset();

				EditBoxPair boxes = {};
				boxes.pEditBox = api.Create(50, 400, setup.nWidth, setup.nHeight, 4, 3, reinterpret_cast<D2CellFileStrc*>(cellFile),
					setup.bReturn ? reinterpret_cast<int32_t>(&EditBoxCallbacks::OnReturn) : 0, &CallbackRecorder::Callback, setup.dwFlags,
					setup.bFont ? reinterpret_cast<int32_t>(fontInfo) : 0);
				boxes.pSecond = api.Create(50, 450, 100, 20, 0, 0, nullptr, 0, nullptr, 0, 0);
				REQUIRE(boxes.pEditBox != nullptr);
				REQUIRE(boxes.pSecond != nullptr);

				logs[i].push_back("Create\n" + describe_state(i, boxes) + "\nsecond " + describe_editbox(i, boxes, boxes.pSecond)
					+ "\nlist " + boxes.name(*globals.ppControlList));

				for (const auto& [szName, operation] : operations)
				{
					EditBoxInputMock::log.clear();
					EditBoxCallbacks::log.clear();
					CallbackRecorder::log.clear();
					const std::string szResult = operation(i, api, boxes);
					logs[i].push_back(szName + " -> " + szResult + "\n" + describe_state(i, boxes));
				}

				logs[i].push_back("Destroy -> " + std::to_string(api.Destroy(boxes.pEditBox)) + " " + std::to_string(api.Destroy(boxes.pSecond))
					+ " focus " + boxes.name(*globals.ppFocusedEditBox) + " list " + boxes.name(*globals.ppControlList));
				FogMemoryMock::Free(boxes.pEditBox, __FILE__, __LINE__, 0);
				FogMemoryMock::Free(boxes.pSecond, __FILE__, __LINE__, 0);
				*globals.ppRemovedControls = nullptr;
				*globals.ppFocusedEditBox = nullptr;
				*globals.ppNextFocusedEditBox = nullptr;
				*double_click_globals(i).ppLastClickedEditBox = nullptr;
			}

			REQUIRE_EQ(logs[0].size(), logs[1].size());
			for (size_t nStep = 0; nStep < logs[0].size(); ++nStep)
			{
				CAPTURE(nStep);
				CHECK_EQ(logs[0][nStep], logs[1][nStep]);
			}
		}
	}
}
