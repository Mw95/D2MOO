#include <doctest.h>

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <Windows.h>

#include <D2WinScrollBar.h>
#include <D2WinTextBox.h>

#include "D2WinControlFixtures.h"
#include "D2WinFontFixtures.h"


namespace
{
#define D2WIN_TEXTBOX_FUNCTIONS(X) \
	X(Create, D2Win_10042_TEXTBOX_Create, 0x6F8AFAA0) \
	X(Destroy, D2Win_10043_TEXTBOX_Destroy, 0x6F8AFDC0) \
	X(Clear, D2Win_10047, 0x6F8AFE30) \
	X(SetLineGaps, D2Win_10062, 0x6F8AFED0) \
	X(AddWinText, D2Win_10045, 0x6F8AFF30) \
	X(AddUtf8Text, D2Win_10046, 0x6F8AFFB0) \
	X(AddText, D2Win_10044, 0x6F8B0030) \
	X(AddLine, D2Win_10051, 0x6F8B0040) \
	X(AddLines, D2Win_10198, 0x6F8B05E0) \
	X(SetWinCellText, D2Win_10057, 0x6F8B0750) \
	X(SetCellText, D2Win_10058_0, 0x6F8B07C0) \
	X(ClearLineCells, D2Win_10197, 0x6F8B08F0) \
	X(GetNumLines, D2Win_10052_TEXTBOX_GetNumLines, 0x6F8B09E0) \
	X(GetTopLine, D2Win_10054, 0x6F8B0A30) \
	X(GetSelectedLine, D2Win_10049, 0x6F8B0A80) \
	X(SetSelectedLine, D2Win_10050_TEXTBOX_SetLine, 0x6F8B0AD0) \
	X(SetTopLine, D2Win_10053, 0x6F8B0B30) \
	X(GetVisibleLines, D2Win_10055, 0x6F8B0BC0) \
	X(GetSelectedText, D2Win_10048, 0x6F8B0C50) \
	X(GetCellText, D2Win_10196, 0x6F8B0CC0) \
	X(SetNumColumns, D2Win_10056, 0x6F8B0DC0) \
	X(SetColumnOffset, D2Win_10059, 0x6F8B0E60) \
	X(SetColumnAlign, D2Win_10060, 0x6F8B0EE0) \
	X(GetLastLineIndex, D2Win_10061, 0x6F8B0F60) \
	X(SetVisible, D2Win_10187, 0x6F8B0FC0) \
	X(SetLineColor, D2Win_10188, 0x6F8B1030) \
	X(HandleMouseDown, TEXTBOX_HandleMouseDown, 0x6F8B15A0) \
	X(HandleVirtualKeyInput, TEXTBOX_HandleVirtualKeyInput, 0x6F8B16B0) \
	X(GetScrollMaxSteps, D2Win_10190, 0x6F8B18F0) \
	X(SetScrollMaxSteps, D2Win_10191, 0x6F8B1940) \
	X(GetScrollStep, D2Win_10192, 0x6F8B1990) \
	X(SetScrollStep, D2Win_10193, 0x6F8B19E0) \
	X(SetScrollTextBox, D2Win_10194, 0x6F8B1A30) \
	X(SetScrollCallback, D2Win_10195, 0x6F8B1A80) \
	X(SetScrollPageStep, D2Win_10204, 0x6F8B1AD0) \
	X(GetScrollPageStep, D2Win_10203_TEXTBOX, 0x6F8B1B20) \
	X(Draw, TEXTBOX_Draw, 0x6F8B1130) \
	X(ScrollBarDraw, SCROLLBAR_Draw, 0x6F8AF330) \
	X(ScrollBarHandleMouseDown, SCROLLBAR_HandleMouseDown, 0x6F8AF4D0) \
	X(ScrollBarHandleMouseUp, SCROLLBAR_HandleMouseUp, 0x6F8AF6B0)

// The text box functions of one implementation
struct TextBoxApi
{
#define D2WIN_DECLARE_FUNCTION(name, function, address) decltype(&function) name;
	D2WIN_TEXTBOX_FUNCTIONS(D2WIN_DECLARE_FUNCTION)
#undef D2WIN_DECLARE_FUNCTION
};

const TextBoxApi& textbox_api(int nImplementation)
{
#define D2WIN_MOO_FUNCTION(name, function, address) &function,
#define D2WIN_ORIGINAL_FUNCTION(name, function, address) reinterpret_cast<decltype(&function)>(original_d2win_address(address)),
	static const TextBoxApi moo = { D2WIN_TEXTBOX_FUNCTIONS(D2WIN_MOO_FUNCTION) };
	static const TextBoxApi original = { D2WIN_TEXTBOX_FUNCTIONS(D2WIN_ORIGINAL_FUNCTION) };
#undef D2WIN_MOO_FUNCTION
#undef D2WIN_ORIGINAL_FUNCTION
	return nImplementation == 0 ? moo : original;
}

// Name of a function pointer of a control, so that both implementations can be compared
template<typename Function>
std::string function_name(int nImplementation, Function pFunction)
{
	if (pFunction == nullptr)
	{
		return "null";
	}

	const TextBoxApi& api = textbox_api(nImplementation);
	const void* pAddress = reinterpret_cast<const void*>(pFunction);
	if (pAddress == reinterpret_cast<const void*>(api.Draw)) return "TEXTBOX_Draw";
	if (pAddress == reinterpret_cast<const void*>(api.HandleMouseDown)) return "TEXTBOX_HandleMouseDown";
	if (pAddress == reinterpret_cast<const void*>(api.HandleVirtualKeyInput)) return "TEXTBOX_HandleVirtualKeyInput";
	if (pAddress == reinterpret_cast<const void*>(api.ScrollBarDraw)) return "SCROLLBAR_Draw";
	if (pAddress == reinterpret_cast<const void*>(api.ScrollBarHandleMouseDown)) return "SCROLLBAR_HandleMouseDown";
	if (pAddress == reinterpret_cast<const void*>(api.ScrollBarHandleMouseUp)) return "SCROLLBAR_HandleMouseUp";
	if (pAddress == reinterpret_cast<const void*>(&CallbackRecorder::Callback)) return "Callback";
	if (pAddress == reinterpret_cast<const void*>(&CallbackRecorder::VoidCallback)) return "VoidCallback";
	return "unknown";
}

std::string describe_header(int nImplementation, const D2WinControlStrc& header)
{
	return "type " + std::to_string(header.nType) + " flags " + std::to_string(header.dwFlags)
		+ " cel " + std::to_string(header.pCellFile != nullptr)
		+ " rect " + std::to_string(header.nImageX) + "," + std::to_string(header.nImageY) + "," + std::to_string(header.nWidth) + "," + std::to_string(header.nHeight)
		+ " draw " + function_name(nImplementation, header.pfDraw) + " update " + function_name(nImplementation, header.pfUpdate)
		+ " down " + function_name(nImplementation, header.pfHandleMouseDown) + " up " + function_name(nImplementation, header.pfHandleMouseUp)
		+ " char " + function_name(nImplementation, header.pfHandleCharInput) + " key " + function_name(nImplementation, header.pfHandleVirtualKeyInput)
		+ " callback " + function_name(nImplementation, header.pfCallback) + " hit " + function_name(nImplementation, header.pfShouldMouseInputBeHandled);
}

// Text description of a text box, its lines and its scroll bar
std::string describe_textbox(int nImplementation, const D2WinTextBoxStrc* pTextBox)
{
	std::string szText = describe_header(nImplementation, pTextBox->controlHeader);
	szText += "\ninset " + std::to_string(pTextBox->nTextInsetX) + "," + std::to_string(pTextBox->nTextInsetY)
		+ " lines " + std::to_string(pTextBox->nNumLines) + " top " + std::to_string(pTextBox->nLine)
		+ " flags " + std::to_string(pTextBox->dwTextBoxFlags) + " selected " + std::to_string(pTextBox->nCurrentLine)
		+ " columns " + std::to_string(pTextBox->nNumColumns);
	for (int i = 0; i < 5; ++i)
	{
		szText += " " + std::to_string(pTextBox->nColumnOffsets[i]) + "/" + std::to_string(pTextBox->nColumnAlignFlags[i]);
	}
	szText += " font " + std::to_string(pTextBox->eFont) + " " + std::to_string(pTextBox->field_98)
		+ " scroll " + std::to_string(pTextBox->nScrollOffset) + " gaps " + std::to_string(pTextBox->nWrappedLineGap) + "," + std::to_string(pTextBox->nLineGap)
		+ " spacing " + std::to_string(pTextBox->nLineSpacing);

	int nIndex = 0;
	int nCurrent = -1;
	int nLast = -1;
	for (const D2WinTextBoxLineStrc* pLine = pTextBox->pFirstLine; pLine && nIndex < 1000; pLine = pLine->pNext, ++nIndex)
	{
		szText += "\n  " + std::to_string(nIndex) + ": color " + std::to_string(pLine->nColor) + " wrapped " + std::to_string((int)pLine->bWrappedSegment);
		for (int i = 0; i < 5; ++i)
		{
			szText += pLine->pColumns[i] ? " [" + narrow_unicode(pLine->pColumns[i]) + "]" : " null";
		}
		if (pLine == pTextBox->pCurrentLine)
		{
			nCurrent = nIndex;
		}
		if (pLine == pTextBox->pLastLine)
		{
			nLast = nIndex;
		}
	}
	szText += "\ncurrent line " + std::to_string(nCurrent) + " last line " + std::to_string(nLast)
		+ " (" + std::to_string(pTextBox->pCurrentLine != nullptr) + std::to_string(pTextBox->pLastLine != nullptr) + ")";

	if (const D2WinScrollBarStrc* pScrollBar = pTextBox->pScrollBar)
	{
		szText += "\nscroll bar " + describe_header(nImplementation, pScrollBar->controlHeader)
			+ "\n  pressed " + std::to_string(pScrollBar->bIsUpperArrowPressed) + std::to_string(pScrollBar->bIsLowerArrowPressed)
			+ " steps " + std::to_string(pScrollBar->nCurrentStep) + "/" + std::to_string(pScrollBar->nMaxSteps)
			+ " page " + std::to_string(pScrollBar->nPageStep)
			+ " text box " + (pScrollBar->pTextBox == pTextBox ? std::string("self") : std::to_string(pScrollBar->pTextBox != nullptr))
			+ " dragged " + std::to_string(pScrollBar->bIsStepIndicatorDragged)
			+ " callback " + function_name(nImplementation, pScrollBar->pfOnStepChange);
	}
	return szText;
}

std::string text_result(const Unicode* wszText)
{
	return wszText ? "[" + narrow_unicode(wszText) + "]" : "null";
}

struct TextBoxSetup
{
	const char* szName;
	int32_t nWidth;
	int32_t nHeight;
	int32_t nInsetX;
	int32_t nInsetY;
	uint32_t dwFlags;
	bool bFont;
	bool bScrollBarRect;
};

// An operation of a scenario, run with the functions of one implementation, returns a description of its result
using TextBoxOperation = std::function<std::string(int nImplementation, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)>;

std::vector<std::pair<std::string, TextBoxOperation>> textbox_operations(bool bScrollBar, bool bSelectable)
{
	std::vector<std::pair<std::string, TextBoxOperation>> operations;
	const auto add = [&](std::string szName, TextBoxOperation operation) { operations.emplace_back(std::move(szName), std::move(operation)); };

	static const std::vector<Unicode> wszHello = to_unicode("Hello");
	static const std::vector<Unicode> wszLong = to_unicode("   A long line of text that does not fit in the width of the text box and has to be wrapped on several lines, maybe even more than two of them");
	static const std::vector<Unicode> wszNoSpace = to_unicode("Averyveryverylongwordwithoutanyspacethatcannotbewrappedatallanywhereinthewholebox");
	static const std::vector<Unicode> wszCell = to_unicode("Cell");
	static const std::vector<Unicode> wszRepeated = to_unicode("Repeated");

	add("AddText", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddText(pTextBox, wszHello.data())); });
	add("AddUtf8Text", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddUtf8Text(pTextBox, "Utf8 \xC3\xA9t\xC3\xA9", 2)); });
	add("AddWinText", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { api.AddWinText(pTextBox, "Win \xE9t\xE9"); return std::string(); });
	add("AddLine long", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddLine(pTextBox, wszLong.data(), 3, 0, 0)); });
	add("AddLine indent 1", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddLine(pTextBox, wszLong.data(), 1, 0, 1)); });
	add("AddLine indent 2", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddLine(pTextBox, wszHello.data(), 5, 1, 2)); });
	add("AddLine no space", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddLine(pTextBox, wszNoSpace.data(), 0, 0, 0)); });
	add("AddLines", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddLines(pTextBox, wszRepeated.data(), 3, 7, 1)); });
	add("SetLineGaps", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.SetLineGaps(pTextBox, 2, 3)); });
	add("AddLines after gaps", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddLines(pTextBox, wszRepeated.data(), 4, 1, 0)); });
	add("Getters", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
	{
		return std::to_string(api.GetNumLines(pTextBox)) + " " + std::to_string(api.GetTopLine(pTextBox)) + " " + std::to_string(api.GetSelectedLine(pTextBox))
			+ " " + std::to_string(api.GetVisibleLines(pTextBox)) + " " + std::to_string(api.GetLastLineIndex(pTextBox))
			+ " " + text_result(api.GetSelectedText(pTextBox)) + " " + text_result(api.GetCellText(pTextBox, 2, 0)) + " " + text_result(api.GetCellText(pTextBox, 0, 1));
	});
	add("SetNumColumns", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
	{
		api.SetNumColumns(pTextBox, 3);
		api.SetColumnOffset(pTextBox, 0, 0);
		api.SetColumnOffset(pTextBox, 1, 60);
		api.SetColumnOffset(pTextBox, 2, 120);
		api.SetColumnAlign(pTextBox, 1, 1);
		api.SetColumnAlign(pTextBox, 2, 2);
		return std::string();
	});
	add("SetCellText", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
	{
		return std::to_string(api.SetCellText(pTextBox, wszCell.data(), 1, 1)) + " " + std::to_string(api.SetWinCellText(pTextBox, "Win cell", 2, 2))
			+ " " + std::to_string(api.SetCellText(pTextBox, wszCell.data(), 999, 1));
	});
	add("ClearLineCells", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
	{
		api.ClearLineCells(pTextBox, 1);
		return std::to_string(api.SetCellText(pTextBox, wszHello.data(), 1, 2)) + " " + text_result(api.GetCellText(pTextBox, 1, 0)) + " " + text_result(api.GetCellText(pTextBox, 1, 2));
	});
	add("SetLineColor", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
	{
		return std::to_string(api.SetLineColor(pTextBox, 2, 9)) + std::to_string(api.SetLineColor(pTextBox, 0, 8));
	});
	add("SetLineColor all", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.SetLineColor(pTextBox, -1, 6)); });
	for (int32_t nLine : { 2, 0, 100, 5 })
	{
		add("SetTopLine " + std::to_string(nLine), [nLine](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.SetTopLine(pTextBox, nLine)); });
	}
	for (int32_t nLine : { -5, 3, 100, -1, 1 })
	{
		add("SetSelectedLine " + std::to_string(nLine), [nLine](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
		{
			api.SetSelectedLine(pTextBox, nLine);
			return std::to_string(api.GetSelectedLine(pTextBox)) + " " + text_result(api.GetSelectedText(pTextBox));
		});
	}

	// Clicks on the lines, above and below the box
	for (int32_t nOffsetY : { -10, 0, 5, 17, 33, 60, 95, 150 })
	{
		for (uint32_t dwFlags : { 5u, 1u })
		{
			if (dwFlags != 5 && nOffsetY != 17)
			{
				continue;
			}
			add("HandleMouseDown " + std::to_string(nOffsetY) + " flags " + std::to_string(dwFlags), [nOffsetY, dwFlags](int nImplementation, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
			{
				const uint32_t dwOldFlags = pTextBox->controlHeader.dwFlags;
				pTextBox->controlHeader.dwFlags = dwFlags;
				*both_control_globals[nImplementation]->pMousePosition = { pTextBox->controlHeader.nImageX + 10, pTextBox->controlHeader.nImageY - pTextBox->controlHeader.nHeight + nOffsetY };
				SMSGHANDLER_PARAMS msg = {};
				msg.hWindow = (HWND)pTextBox;
				msg.nMessage = WM_LBUTTONDOWN;
				const int32_t nResult = api.HandleMouseDown(&msg);
				pTextBox->controlHeader.dwFlags = dwOldFlags;
				return std::to_string(nResult);
			});
		}
	}

	// Key navigation
	if (bSelectable)
	{
		add("SetSelectedLine 0", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { api.SetSelectedLine(pTextBox, 0); return std::string(); });
		for (WPARAM wParam : { VK_DOWN, VK_DOWN, VK_NEXT, VK_NEXT, VK_DOWN, VK_NEXT, VK_UP, VK_PRIOR, VK_PRIOR, VK_END, VK_UP, VK_NEXT, VK_HOME, VK_PRIOR, VK_UP, VK_RETURN })
		{
			add("HandleVirtualKeyInput " + std::to_string(wParam), [wParam](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
			{
				SMSGHANDLER_PARAMS msg = {};
				msg.hWindow = (HWND)pTextBox;
				msg.nMessage = WM_KEYDOWN;
				msg.wParam = wParam;
				return std::to_string(api.HandleVirtualKeyInput(&msg));
			});
		}
	}

	if (bScrollBar)
	{
		add("Scroll bar", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
		{
			std::string szResult = std::to_string(api.GetScrollMaxSteps(pTextBox)) + " " + std::to_string(api.GetScrollStep(pTextBox)) + " " + std::to_string(api.GetScrollPageStep(pTextBox));
			szResult += " " + std::to_string(api.SetScrollMaxSteps(pTextBox, 4)) + " " + std::to_string(api.SetScrollStep(pTextBox, 9));
			szResult += " " + std::to_string(api.SetScrollCallback(pTextBox, &CallbackRecorder::VoidCallback));
			api.SetScrollPageStep(pTextBox, 3);
			szResult += " " + std::to_string(api.GetScrollMaxSteps(pTextBox)) + " " + std::to_string(api.GetScrollStep(pTextBox)) + " " + std::to_string(api.GetScrollPageStep(pTextBox));
			return szResult;
		});
		add("Scroll bar click", [](int nImplementation, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox)
		{
			D2WinScrollBarStrc* pScrollBar = pTextBox->pScrollBar;
			*both_control_globals[nImplementation]->pMousePosition = { pScrollBar->controlHeader.nImageX + 5, pScrollBar->controlHeader.nImageY - 2 };
			SMSGHANDLER_PARAMS msg = {};
			msg.hWindow = (HWND)pScrollBar;
			msg.nMessage = WM_LBUTTONDOWN;
			const int32_t nResult = api.ScrollBarHandleMouseDown(&msg);
			return std::to_string(nResult) + " " + std::to_string(api.ScrollBarHandleMouseUp(&msg));
		});
		add("SetScrollTextBox", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.SetScrollTextBox(pTextBox, nullptr)) + std::to_string(api.SetScrollTextBox(pTextBox, pTextBox)); });
	}

	add("SetVisible 0", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { api.SetVisible(pTextBox, FALSE); return std::string(); });
	add("SetVisible 1", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { api.SetVisible(pTextBox, TRUE); return std::string(); });
	add("Clear", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.Clear(pTextBox)); });
	add("AddText after clear", [](int, const TextBoxApi& api, D2WinTextBoxStrc* pTextBox) { return std::to_string(api.AddText(pTextBox, wszHello.data())); });
	add("Clear null", [](int, const TextBoxApi& api, D2WinTextBoxStrc*) { return std::to_string(api.Clear(nullptr)); });
	return operations;
}
}


TEST_SUITE("D2WinTextBoxTests")
{
	// Runs scenarios on text boxes created with different settings, and compares the text boxes after each step
	TEST_CASE_FIXTURE(D2WinFontFixture<NoOpFixture>, "D2Win.0x6F8AFAA0 (#10042)")
	{
		ControlGlobalsGuard controlGlobalsGuard;

		const TextBoxSetup setups[] = {
			{ "Plain", 200, 100, 5, 5, 0, false, false },
			{ "Selectable with scroll bar", 240, 120, 4, 6, TEXTBOXFLAG_SELECTABLE | TEXTBOXFLAG_SCROLLBAR, true, false },
			{ "Scroll bar rect", 220, 90, 0, 0, TEXTBOXFLAG_SCROLLBAR | TEXTBOXFLAG_CENTERED, false, true },
			{ "Clamped selection", 300, 60, 2, 3, TEXTBOXFLAG_SELECTABLE | TEXTBOXFLAG_CLAMP_SELECTION, true, false },
			{ "No word wrap", 150, 300, 8, 1, TEXTBOXFLAG_NO_WORD_WRAP | TEXTBOXFLAG_RIGHT_ALIGNED, false, false },
		};

		// Font info: font and an unknown value
		int32_t fontInfo[2] = { D2FONT_FONT8, 7 };
		int32_t scrollBarRect[3] = { 400, 350, 80 };
		int32_t cellFile[4] = { 3 };

		for (const TextBoxSetup& setup : setups)
		{
			CAPTURE(setup.szName);

			const bool bScrollBar = (setup.dwFlags & TEXTBOXFLAG_SCROLLBAR) != 0;
			const bool bSelectable = (setup.dwFlags & TEXTBOXFLAG_SELECTABLE) != 0;
			const auto operations = textbox_operations(bScrollBar, bSelectable);

			std::vector<std::string> logs[2];
			for (int i = 0; i < 2; ++i)
			{
				install_fonts(false);
				const TextBoxApi& api = textbox_api(i);
				const ControlGlobals& globals = *both_control_globals[i];
				*globals.ppControlList = nullptr;
				*globals.ppRemovedControls = nullptr;
				*globals.ppFocusedEditBox = nullptr;
				CallbackRecorder::reset();

				D2WinTextBoxStrc* pTextBox = api.Create(30, 450, setup.nWidth, setup.nHeight, setup.nInsetX, setup.nInsetY, reinterpret_cast<D2CellFileStrc*>(cellFile),
					&CallbackRecorder::Callback, setup.dwFlags, setup.bFont ? reinterpret_cast<int32_t>(fontInfo) : 0, setup.bScrollBarRect ? reinterpret_cast<int32_t>(scrollBarRect) : 0);
				REQUIRE(pTextBox != nullptr);

				logs[i].push_back("Create: " + describe_textbox(i, pTextBox) + "\ncontrol list " + std::to_string(*globals.ppControlList == &pTextBox->controlHeader)
					+ " " + std::to_string(pTextBox->pScrollBar && pTextBox->controlHeader.pNext == &pTextBox->pScrollBar->controlHeader));

				for (const auto& [szName, operation] : operations)
				{
					CallbackRecorder::log.clear();
					const std::string szResult = operation(i, api, pTextBox);
					std::string szLog = szName + " -> " + szResult + "\n" + describe_textbox(i, pTextBox);
					for (const std::string& szCall : CallbackRecorder::log)
					{
						szLog += "\n" + szCall;
					}
					logs[i].push_back(szLog);
				}

				D2WinScrollBarStrc* pScrollBar = pTextBox->pScrollBar;
				logs[i].push_back("Destroy -> " + std::to_string(api.Destroy(pTextBox)) + " " + std::to_string(*globals.ppControlList == nullptr) + " " + std::to_string(pTextBox->pFirstLine == nullptr));
				FogMemoryMock::Free(pScrollBar, __FILE__, __LINE__, 0);
				FogMemoryMock::Free(pTextBox, __FILE__, __LINE__, 0);
				*globals.ppRemovedControls = nullptr;
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
