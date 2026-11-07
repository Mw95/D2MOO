#include <doctest.h>

#include <cstdint>
#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include <Windows.h>

#include <D2Lang.h>
#include <D2LangStringMocks.h>

#include <D2WinAccountList.h>
#include <D2WinList.h>

#include "D2WinControlFixtures.h"
#include "D2WinFontFixtures.h"


extern uint32_t dword_6F8FE220;


namespace
{
#define D2WIN_LIST_FUNCTIONS(X) \
	X(Create, LIST_Create, 0x6F8AC270) \
	X(Destroy, LIST_Destroy, 0x6F8AC490) \
	X(AddWinEntry, D2Win_10138, 0x6F8AC4F0) \
	X(AddEntry, D2Win_10137, 0x6F8AC570) \
	X(GetSelectedIndex, LIST_GetSelectedDataIndex, 0x6F8AC6D0) \
	X(GetData, LIST_GetDataFromIndex, 0x6F8AC720) \
	X(GetCount, D2Win_10141, 0x6F8AC770) \
	X(Draw, LIST_Draw, 0x6F8AC820) \
	X(HandleMouseDown, LIST_HandleMouseDown, 0x6F8AC9B0) \
	X(HandleCharInput, LIST_HandleCharInput, 0x6F8ACA70) \
	X(HandleVirtualKeyInput, LIST_HandleVirtualKeyInput, 0x6F8ACAE0) \
	X(AccountCreate, ACCOUNTLIST_Create, 0x6F8A4E90) \
	X(AccountDestroy, ACCOUNTLIST_Destroy, 0x6F8A4F70) \
	X(AccountFreeData, ACCOUNTLIST_FreeData, 0x6F8A4FC0) \
	X(AccountAdd, ACCOUNTLIST_AllocData, 0x6F8A5010) \
	X(AccountRemove, ACCOUNTLIST_RemoveEntry, 0x6F8A5080) \
	X(AccountGetSelectedText, ACCOUNTLIST_GetTextFromSelectedEntry, 0x6F8A5140) \
	X(AccountDraw, ACCOUNTLIST_Draw, 0x6F8A5180) \
	X(AccountHandleMouseDown, ACCOUNTLIST_HandleMouseDown, 0x6F8A52E0)

// The list functions of one implementation
struct ListApi
{
#define D2WIN_DECLARE_FUNCTION(name, function, address) decltype(&function) name;
	D2WIN_LIST_FUNCTIONS(D2WIN_DECLARE_FUNCTION)
#undef D2WIN_DECLARE_FUNCTION
};

const ListApi& list_api(int nImplementation)
{
#define D2WIN_MOO_FUNCTION(name, function, address) &function,
#define D2WIN_ORIGINAL_FUNCTION(name, function, address) reinterpret_cast<decltype(&function)>(original_d2win_address(address)),
	static const ListApi moo = { D2WIN_LIST_FUNCTIONS(D2WIN_MOO_FUNCTION) };
	static const ListApi original = { D2WIN_LIST_FUNCTIONS(D2WIN_ORIGINAL_FUNCTION) };
#undef D2WIN_MOO_FUNCTION
#undef D2WIN_ORIGINAL_FUNCTION
	return nImplementation == 0 ? moo : original;
}

template<typename Function>
std::string function_name(int nImplementation, Function pFunction)
{
	if (pFunction == nullptr)
	{
		return "null";
	}

	const ListApi& api = list_api(nImplementation);
	const void* pAddress = reinterpret_cast<const void*>(pFunction);
#define D2WIN_NAME_FUNCTION(name, function, address) if (pAddress == reinterpret_cast<const void*>(api.name)) return #name;
	D2WIN_LIST_FUNCTIONS(D2WIN_NAME_FUNCTION)
#undef D2WIN_NAME_FUNCTION
	if (pAddress == reinterpret_cast<const void*>(&CallbackRecorder::Callback)) return "Callback";
	if (pAddress == reinterpret_cast<const void*>(&CallbackRecorder::OtherCallback)) return "OtherCallback";
	return "unknown";
}

std::string describe_header(int nImplementation, const D2WinControlStrc& header)
{
	return "type " + std::to_string(header.nType) + " flags " + std::to_string(header.dwFlags)
		+ " rect " + std::to_string(header.nImageX) + "," + std::to_string(header.nImageY) + "," + std::to_string(header.nWidth) + "," + std::to_string(header.nHeight)
		+ " draw " + function_name(nImplementation, header.pfDraw) + " down " + function_name(nImplementation, header.pfHandleMouseDown)
		+ " up " + function_name(nImplementation, header.pfHandleMouseUp) + " char " + function_name(nImplementation, header.pfHandleCharInput)
		+ " key " + function_name(nImplementation, header.pfHandleVirtualKeyInput) + " callback " + function_name(nImplementation, header.pfCallback);
}

std::string describe_list(int nImplementation, const D2WinListStrc* pList)
{
	std::string szText = describe_header(nImplementation, pList->controlHeader)
		+ "\nfont " + std::to_string(pList->eFont) + " line " + std::to_string(pList->nLineHeight) + "+" + std::to_string(pList->nLinePadding)
		+ " first " + std::to_string(pList->nFirstVisibleEntry) + " count " + std::to_string(pList->nEntryCount)
		+ " selected " + std::to_string(pList->nSelectedIndex) + " last visible " + std::to_string(pList->nLastVisibleOffset)
		+ " pentagram " + std::to_string(pList->nPentagramFrame) + " widest " + std::to_string(pList->nWidestEntry);

	int nIndex = 0;
	int nSelected = -1;
	for (const D2WinListDataStrc* pData = pList->pDataList; pData && nIndex < 100; pData = pData->pNext, ++nIndex)
	{
		szText += "\n  " + std::to_string(nIndex) + ": [" + narrow_unicode(pData->wszText) + "] width " + std::to_string(pData->nTextWidth)
			+ " activate " + function_name(nImplementation, pData->pfOnActivate) + " hot key " + std::to_string((uint8_t)pData->nHotKey)
			+ " virtual key " + std::to_string(pData->nVirtualKey);
		if (pData == pList->pSelectedDataEntry)
		{
			nSelected = nIndex;
		}
	}
	return szText + "\nselected entry " + std::to_string(nSelected) + " (" + std::to_string(pList->pSelectedDataEntry != nullptr) + ")";
}

std::string describe_account_list(int nImplementation, const D2WinAccountListStrc* pAccountList)
{
	std::string szText = describe_header(nImplementation, pAccountList->controlHeader)
		+ "\nfirst " + std::to_string(pAccountList->nFirstDrawnEntry) + " " + std::to_string(pAccountList->field_4C)
		+ " font " + std::to_string(pAccountList->eFont) + " " + std::to_string(pAccountList->field_54);
	int nIndex = 0;
	int nSelected = -1;
	for (const D2WinAccountListDataStrc* pData = pAccountList->pDataList; pData && nIndex < 100; pData = pData->pNext, ++nIndex)
	{
		szText += "\n  " + std::to_string(nIndex) + ": [" + std::string(pData->szText, strnlen(pData->szText, sizeof(pData->szText))) + "]";
		if (pData == pAccountList->pSelectedDataEntry)
		{
			nSelected = nIndex;
		}
	}
	return szText + "\nselected entry " + std::to_string(nSelected) + " (" + std::to_string(pAccountList->pSelectedDataEntry != nullptr) + ")";
}

// An entry of the table given to LIST_Create
#pragma pack(push, 1)
struct ListEntryInit
{
	uint32_t nStringId;
	char nHotKey;
	char pad[3];
	int32_t nVirtualKey;
	int32_t(__stdcall* pfOnActivate)(SMSGHANDLER_PARAMS*);
};
#pragma pack(pop)

template<class Fixture>
struct D2WinListFixture : D2WinFontFixture<Fixture>
{
	ControlGlobalsGuard controlGlobalsGuard;
	uint32_t savedDoubleClickTicks[2];

	D2WinListFixture()
	{
		hook_d2lang_string_mocks(this->hooks);
		CallbackRecorder::reset();
		savedDoubleClickTicks[0] = dword_6F8FE220;
		savedDoubleClickTicks[1] = *original_d2win_global<uint32_t>(0x6F8FE220);
	}

	~D2WinListFixture()
	{
		dword_6F8FE220 = savedDoubleClickTicks[0];
		*original_d2win_global<uint32_t>(0x6F8FE220) = savedDoubleClickTicks[1];
		CallbackRecorder::reset();
	}
};

uint32_t* double_click_tick(int nImplementation)
{
	return nImplementation == 0 ? &dword_6F8FE220 : original_d2win_global<uint32_t>(0x6F8FE220);
}

using ListOperation = std::function<std::string(int nImplementation, const ListApi& api, D2WinListStrc* pList)>;
}


TEST_SUITE("D2WinListTests")
{
	TEST_CASE_FIXTURE(D2WinListFixture<NoOpFixture>, "D2Win.0x6F8AC270 (#10135)")
	{
		const ListEntryInit entries[] = {
			{ 1000, 'a', {}, VK_F1, &CallbackRecorder::Callback },
			{ 1001, 'B', {}, 0, &CallbackRecorder::OtherCallback },
			{ 25, '\x81', {}, 0x170, nullptr },
			{ 0xFFFF, 'z', {}, VK_F2, &CallbackRecorder::Callback },
			{ 0 },
		};
		const ListEntryInit noEntries[] = { { 0 } };

		struct Setup
		{
			const char* szName;
			Font nFont;
			int32_t nHeight;
			const ListEntryInit* pEntries;
		};
		const Setup setups[] = {
			{ "Font16", D2FONT_FONT16, 100, entries },
			{ "Font8", D2FONT_FONT8, 37, entries },
			{ "Font42", D2FONT_FONT42, 300, entries },
			{ "Empty", D2FONT_FONT30, 90, noEntries },
		};

		const std::vector<Unicode> wszAdded = to_unicode("Added entry");

		std::vector<std::pair<std::string, ListOperation>> operations;
		const auto add = [&](std::string szName, ListOperation operation) { operations.emplace_back(std::move(szName), std::move(operation)); };
		add("Getters", [](int, const ListApi& api, D2WinListStrc* pList)
		{
			std::string szResult = std::to_string(api.GetSelectedIndex(pList)) + " " + std::to_string(api.GetCount(pList));
			for (int32_t nIndex : { -1, 0, 2, 3, 10 })
			{
				const D2WinListDataStrc* pData = api.GetData(pList, nIndex);
				szResult += " " + (pData ? "[" + narrow_unicode(pData->wszText) + "]" : std::string("null"));
			}
			return szResult;
		});
		add("AddEntry", [&wszAdded](int, const ListApi& api, D2WinListStrc* pList) { api.AddEntry(pList, const_cast<Unicode*>(wszAdded.data()), &CallbackRecorder::OtherCallback, 'x', VK_F5, 0, 0); return std::string(); });
		add("AddEntry first selected", [&wszAdded](int, const ListApi& api, D2WinListStrc* pList) { api.AddEntry(pList, const_cast<Unicode*>(wszAdded.data()), nullptr, 'y', 0, 1, 1); return std::string(); });
		add("AddWinEntry selected", [](int, const ListApi& api, D2WinListStrc* pList) { api.AddWinEntry(pList, "Win \xE9ntry with a longer text", &CallbackRecorder::Callback, '\xE9', VK_F6, 0, 1); return std::string(); });
		add("Getters again", operations.front().second);

		for (int nKey : { VK_DOWN, VK_DOWN, VK_UP, VK_UP, VK_UP, VK_DOWN, VK_DOWN, VK_DOWN, VK_DOWN, VK_DOWN, VK_RETURN, VK_F1, VK_F5, 0x170, VK_F9 })
		{
			for (UINT nMessage : { (UINT)WM_KEYDOWN, (UINT)WM_CHAR })
			{
				if (nMessage == WM_CHAR && nKey != VK_DOWN)
				{
					continue;
				}
				add("Key " + std::to_string(nKey) + " message " + std::to_string(nMessage), [nKey, nMessage](int, const ListApi& api, D2WinListStrc* pList)
				{
					SMSGHANDLER_PARAMS msg = {};
					msg.hWindow = (HWND)pList;
					msg.nMessage = nMessage;
					msg.wParam = nKey;
					return std::to_string(api.HandleVirtualKeyInput(&msg));
				});
			}
		}

		for (int nChar : { (int)'a', (int)'A', (int)'B', (int)'x', 0x81, 0x181, 0xE9, (int)'q' })
		{
			add("Char " + std::to_string(nChar), [nChar](int, const ListApi& api, D2WinListStrc* pList)
			{
				SMSGHANDLER_PARAMS msg = {};
				msg.hWindow = (HWND)pList;
				msg.nMessage = WM_CHAR;
				msg.wParam = nChar;
				return std::to_string(api.HandleCharInput(&msg));
			});
		}

		// Hit rectangles as LIST_Draw would set them, then clicks and double clicks
		add("Hit rectangles", [](int, const ListApi&, D2WinListStrc* pList)
		{
			int32_t nTop = 100;
			for (D2WinListDataStrc* pData = pList->pDataList; pData; pData = pData->pNext, nTop += 20)
			{
				pData->nHitRectLeft = 10;
				pData->nHitRectRight = 200;
				pData->nHitRectTop = nTop;
				pData->nHitRectBottom = nTop + 20;
			}
			return std::string();
		});
		const POINT clicks[] = { { 50, 110 }, { 50, 110 }, { 50, 130 }, { 50, 130 }, { 50, 130 }, { 10, 130 }, { 50, 120 }, { 50, 150 }, { 50, 150 }, { 300, 150 } };
		const DWORD ticks[] = { 1000, 1100, 1200, 1499, 2000, 2100, 2200, 2300, 2700, 2800 };
		for (size_t i = 0; i < std::size(clicks); ++i)
		{
			const POINT point = clicks[i];
			const DWORD dwTick = (5000 << 10) + ticks[i];
			add("Click " + std::to_string(point.x) + "," + std::to_string(point.y) + " at " + std::to_string(ticks[i]), [point, dwTick](int nImplementation, const ListApi& api, D2WinListStrc* pList)
			{
				*both_control_globals[nImplementation]->pMousePosition = point;
				TickCountMock::dwTickCount = dwTick;
				SMSGHANDLER_PARAMS msg = {};
				msg.hWindow = (HWND)pList;
				msg.nMessage = WM_LBUTTONDOWN;
				return std::to_string(api.HandleMouseDown(&msg)) + " tick " + std::to_string(*double_click_tick(nImplementation) - (5000 << 10));
			});
		}

		for (const Setup& setup : setups)
		{
			CAPTURE(setup.szName);
			if (setup.pEntries == noEntries)
			{
				// The key handlers expect at least one entry
				continue;
			}

			std::vector<std::string> logs[2];
			for (int i = 0; i < 2; ++i)
			{
				TickCountMock::dwTickCount = 5000 << 10;
				install_fonts(false);
				const ListApi& api = list_api(i);
				const ControlGlobals& globals = *both_control_globals[i];
				*globals.ppControlList = nullptr;
				*globals.ppRemovedControls = nullptr;
				*double_click_tick(i) = 5000 << 10;
				CallbackRecorder::reset();
				D2LangStringMock::calls.clear();

				Font nFont = setup.nFont;
				D2WinListStrc* pList = api.Create(40, 400, 250, setup.nHeight, const_cast<ListEntryInit*>(setup.pEntries), &nFont);
				REQUIRE(pList != nullptr);
				pList->controlHeader.pfCallback = &CallbackRecorder::Callback;

				std::string szCreate = "Create\n" + describe_list(i, pList) + "\nlist " + std::to_string(*globals.ppControlList == &pList->controlHeader) + " strings";
				for (short nString : D2LangStringMock::calls)
				{
					szCreate += " " + std::to_string((uint16_t)nString);
				}
				logs[i].push_back(szCreate);

				for (const auto& [szName, operation] : operations)
				{
					CallbackRecorder::log.clear();
					std::string szLog = szName + " -> " + operation(i, api, pList) + "\n" + describe_list(i, pList);
					for (const std::string& szCall : CallbackRecorder::log)
					{
						szLog += "\n" + szCall;
					}
					logs[i].push_back(szLog);
				}

				logs[i].push_back("Destroy -> " + std::to_string(api.Destroy(pList)) + " " + std::to_string(*globals.ppControlList == nullptr));
				FogMemoryMock::Free(pList, __FILE__, __LINE__, 0);
				*globals.ppRemovedControls = nullptr;
			}

			REQUIRE_EQ(logs[0].size(), logs[1].size());
			for (size_t nStep = 0; nStep < logs[0].size(); ++nStep)
			{
				CAPTURE(nStep);
				CHECK_EQ(logs[0][nStep], logs[1][nStep]);
			}
		}

		// Creating a list without entries
		D2WinListStrc* pLists[2] = {};
		for (int i = 0; i < 2; ++i)
		{
			TickCountMock::dwTickCount = 5000 << 10;
			install_fonts(false);
			*both_control_globals[i]->ppControlList = nullptr;
			Font nFont = D2FONT_FONT30;
			pLists[i] = list_api(i).Create(1, 2, 3, 90, const_cast<ListEntryInit*>(noEntries), &nFont);
			REQUIRE(pLists[i] != nullptr);
		}
		CHECK_EQ(describe_list(0, pLists[0]), describe_list(1, pLists[1]));
		for (int i = 0; i < 2; ++i)
		{
			list_api(i).Destroy(pLists[i]);
			FogMemoryMock::Free(pLists[i], __FILE__, __LINE__, 0);
			*both_control_globals[i]->ppControlList = nullptr;
			*both_control_globals[i]->ppRemovedControls = nullptr;
		}
	}

	TEST_CASE_FIXTURE(D2WinListFixture<NoOpFixture>, "D2Win.0x6F8A4E90 (#10162)")
	{
		int32_t fontInfo[2] = { D2FONT_FONT8, 9 };

		for (bool bFont : { false, true })
		{
			CAPTURE(bFont);

			std::vector<std::string> logs[2];
			for (int i = 0; i < 2; ++i)
			{
				const ListApi& api = list_api(i);
				const ControlGlobals& globals = *both_control_globals[i];
				*globals.ppControlList = nullptr;
				*globals.ppRemovedControls = nullptr;

				D2WinAccountListStrc* pAccountList = api.AccountCreate(20, 300, 720, 120, 77, bFont ? fontInfo : nullptr);
				REQUIRE(pAccountList != nullptr);
				const auto log = [&](const std::string& szStep) { logs[i].push_back(szStep + "\n" + describe_account_list(i, pAccountList)); };
				log("Create " + std::to_string(*globals.ppControlList == &pAccountList->controlHeader));

				char szBuffer[64] = {};
				std::strcpy(szBuffer, "untouched");
				log("Selected text of an empty list -> " + std::to_string(api.AccountGetSelectedText(pAccountList, szBuffer)) + " [" + szBuffer + "]");

				SMSGHANDLER_PARAMS msg = {};
				msg.hWindow = (HWND)pAccountList;
				msg.nMessage = WM_LBUTTONDOWN;
				*globals.pMousePosition = { 30, 200 };
				log("Click an empty list -> " + std::to_string(api.AccountHandleMouseDown(&msg)));

				for (const char* szText : { "First", "Second", "Third", "0123456789012345678901234567890123456789012345678", "Fifth", "Sixth", "Seventh", "Eighth" })
				{
					api.AccountAdd(pAccountList, szText);
					log(std::string("Add ") + szText);
				}

				// Clicks on the grid of 6 columns of 120 pixels and lines of 20 pixels
				const POINT points[] = { { 20, 181 }, { 141, 181 }, { 260, 181 }, { 625, 181 }, { 25, 201 }, { 150, 201 }, { 260, 221 }, { 19, 181 }, { 25, 120 }, { 900, 181 } };
				for (const POINT& point : points)
				{
					*globals.pMousePosition = point;
					std::strcpy(szBuffer, "untouched");
					const int32_t nResult = api.AccountHandleMouseDown(&msg);
					const int32_t nText = api.AccountGetSelectedText(pAccountList, szBuffer);
					log("Click " + std::to_string(point.x) + "," + std::to_string(point.y) + " -> " + std::to_string(nResult) + " " + std::to_string(nText) + " [" + szBuffer + "]");
				}

				for (uint32_t dwFlags : { 1u, 4u })
				{
					pAccountList->controlHeader.dwFlags = dwFlags;
					*globals.pMousePosition = points[0];
					log("Click with flags " + std::to_string(dwFlags) + " -> " + std::to_string(api.AccountHandleMouseDown(&msg)));
				}
				pAccountList->controlHeader.dwFlags = 5;

				*globals.pMousePosition = points[1];
				api.AccountHandleMouseDown(&msg);
				for (const char* szText : { "Second", "Missing", "First", "Eighth", "Second" })
				{
					log(std::string("Remove ") + szText + " -> " + std::to_string(api.AccountRemove(pAccountList, szText)));
				}

				// The entries are freed but the list still points to them, it can't be described anymore
				logs[i].push_back("Destroy -> " + std::to_string(api.AccountDestroy(pAccountList)) + " " + std::to_string(*globals.ppControlList == nullptr));
				FogMemoryMock::Free(pAccountList, __FILE__, __LINE__, 0);
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
