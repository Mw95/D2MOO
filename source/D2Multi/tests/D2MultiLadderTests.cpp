#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <D2Lang.h>
#include <D2WinRecorder.h>

#include <ChatDlg.h>

#include "D2MultiTestFixtures.h"


extern uint8_t gnLadderType_6F9BC058;
extern int32_t gnLadderPosition_6F9BC05C;
extern int32_t gnLadderRequestedPosition_6F9BC064;
extern int32_t gnLadderEntryCount_6F9C2450;
extern char gszLadderCharacterName_6F9C269C[16];
extern int32_t gnLadderDisplayedPosition_6F9C2708;
extern D2WinTextBoxStrc* gpLadderList_6F9C2814;


namespace
{
struct LadderGlobals
{
	uint8_t* pnLadderType;
	int32_t* pnLadderPosition;
	int32_t* pnLadderRequestedPosition;
	int32_t* pnLadderEntryCount;
	char* szLadderCharacterName;
	int32_t* pnLadderDisplayedPosition;
	D2WinTextBoxStrc** ppLadderList;
};

const LadderGlobals& moo_ladder_globals()
{
	static const LadderGlobals globals = {
		&gnLadderType_6F9BC058, &gnLadderPosition_6F9BC05C, &gnLadderRequestedPosition_6F9BC064, &gnLadderEntryCount_6F9C2450,
		gszLadderCharacterName_6F9C269C, &gnLadderDisplayedPosition_6F9C2708, &gpLadderList_6F9C2814,
	};
	return globals;
}

const LadderGlobals& original_ladder_globals()
{
	static const LadderGlobals globals = {
		original_d2multi_global<uint8_t>(0x6F9BC058),
		original_d2multi_global<int32_t>(0x6F9BC05C),
		original_d2multi_global<int32_t>(0x6F9BC064),
		original_d2multi_global<int32_t>(0x6F9C2450),
		original_d2multi_global<char>(0x6F9C269C),
		original_d2multi_global<int32_t>(0x6F9C2708),
		original_d2multi_global<D2WinTextBoxStrc*>(0x6F9C2814),
	};
	return globals;
}

// Text box functions of the ladder list, recorded in the D2Win recorder log
struct LadderListMock
{
	static BOOL __fastcall SetLine(D2WinTextBoxStrc* pTextBox, int32_t nLine)
	{
		D2WinRecorder::log.push_back("SetLine " + D2WinRecorder::name(pTextBox) + " " + std::to_string(nLine));
		return TRUE;
	}

	static void __fastcall AddEmptyLine(D2WinTextBoxStrc* pTextBox, int32_t nLine)
	{
		D2WinRecorder::log.push_back("10197 " + D2WinRecorder::name(pTextBox) + " " + std::to_string(nLine));
	}

	static BOOL __fastcall SetLineColor(D2WinTextBoxStrc* pTextBox, int32_t nLine, int32_t nColor)
	{
		D2WinRecorder::log.push_back("SetLineColor " + D2WinRecorder::name(pTextBox) + " " + std::to_string(nLine) + " " + std::to_string(nColor));
		return TRUE;
	}

	static BOOL __fastcall SetCellText(D2WinTextBoxStrc* pTextBox, const char* szText, int32_t nLine, int32_t nColumn)
	{
		D2WinRecorder::log.push_back("SetCellText " + D2WinRecorder::name(pTextBox) + " [" + szText + "] " + std::to_string(nLine) + " " + std::to_string(nColumn));
		return TRUE;
	}

	static BOOL __fastcall SetCellUnicodeText(D2WinTextBoxStrc* pTextBox, const Unicode* wszText, int32_t nLine, int32_t nColumn)
	{
		D2WinRecorder::log.push_back("SetCellUnicodeText " + D2WinRecorder::name(pTextBox) + " [" + D2WinRecorder::narrow(wszText) + "] " + std::to_string(nLine) + " " + std::to_string(nColumn));
		return TRUE;
	}

	// D2Lang.#10012, groups the digits of a 64 bits value
	static void __stdcall FormatNumber(Unicode* wszOutput, uint32_t nValueLow, uint32_t nValueHigh, int nMaxLength)
	{
		const std::string szValue = std::to_string(((uint64_t)nValueHigh << 32) | nValueLow) + "/" + std::to_string(nMaxLength);
		size_t i = 0;
		for (; i < szValue.size(); ++i)
		{
			wszOutput[i] = (Unicode)(uint16_t)szValue[i];
		}
		wszOutput[i] = 0;
	}
};

char gFakeLadderList[16];

template<class Fixture>
struct D2MultiLadderFixture : D2MultiFixture<Fixture>
{
	D2MultiLadderFixture()
	{
		hook_d2win_recorder(this->hooks);
		const auto hook = [this](WORD nOrdinal, void* pMooTarget, const void* pReplacement) { this->hooks.hook("D2Win.dll", nOrdinal, pMooTarget, pReplacement, false); };
		hook(10053, reinterpret_cast<void*>(&D2Win_10053), reinterpret_cast<const void*>(&LadderListMock::SetLine));
		hook(10197, reinterpret_cast<void*>(&D2Win_10197), reinterpret_cast<const void*>(&LadderListMock::AddEmptyLine));
		hook(10188, reinterpret_cast<void*>(&D2Win_10188), reinterpret_cast<const void*>(&LadderListMock::SetLineColor));
		hook(10057, reinterpret_cast<void*>(&D2Win_10057), reinterpret_cast<const void*>(&LadderListMock::SetCellText));
		hook(10058, reinterpret_cast<void*>(&D2Win_10058_0), reinterpret_cast<const void*>(&LadderListMock::SetCellUnicodeText));
		this->hooks.hook("D2Lang.dll", 10012, reinterpret_cast<void*>(&D2LANG_10012), reinterpret_cast<const void*>(&LadderListMock::FormatNumber));
		D2WinRecorder::names[gFakeLadderList] = "LadderList";
	}

	~D2MultiLadderFixture()
	{
		for (const LadderGlobals* pGlobals : { &moo_ladder_globals(), &original_ladder_globals() })
		{
			*pGlobals->ppLadderList = nullptr;
			*pGlobals->pnLadderType = 0xFF;
			*pGlobals->pnLadderPosition = -1;
			*pGlobals->pnLadderRequestedPosition = -1;
		}
		D2WinRecorder::reset();
	}
};

struct LadderEntry
{
	uint64_t nExperience;
	uint32_t dwFlags;
	std::string szName;
};

// Entries with names of nNameSize bytes
std::vector<uint8_t> ladder_entries(const std::vector<LadderEntry>& entries, int32_t nNameSize)
{
	std::vector<uint8_t> data;
	for (const LadderEntry& entry : entries)
	{
		for (int i = 0; i < 8; ++i) data.push_back((uint8_t)(entry.nExperience >> (8 * i)));
		for (int i = 0; i < 4; ++i) data.push_back((uint8_t)(entry.dwFlags >> (8 * i)));
		std::vector<uint8_t> name(nNameSize, 0);
		std::memcpy(name.data(), entry.szName.c_str(), std::min<size_t>(entry.szName.size(), nNameSize - 1));
		data.insert(data.end(), name.begin(), name.end());
	}
	return data;
}

uint32_t ladder_flags(uint32_t nClass, uint32_t nProgression, uint32_t nLevel, bool bHardcore, bool bDead, bool bExpansion)
{
	return nClass | (bDead ? 0x10 : 0) | (bHardcore ? 0x20 : 0) | (bExpansion ? 0x40 : 0) | (nProgression << 8) | (nLevel << 16);
}
}


TEST_SUITE("D2MultiLadderTests")
{
	TEST_CASE_FIXTURE(D2MultiLadderFixture<NoOpFixture>, "D2Multi.0x6F9A8240")
	{
		const auto [sut, original] = make_d2multi_pair(CHATDLG_LadderDataCallback, 0x6F9A8240);

		const std::vector<LadderEntry> entries = {
			{ 3520485254ull, ladder_flags(0, 15, 99, false, false, true), "TopAmazon" },
			{ 0x123456789ull, ladder_flags(1, 10, 95, true, false, true), "Sorceress" },
			{ 1000, ladder_flags(2, 5, 70, true, true, false), "DeadNecro" },
			{ 0, ladder_flags(3, 0, 1, false, false, false), "Requested" },
			{ 42, ladder_flags(6, 12, 88, false, true, true), "Assassin" },
		};

		struct Case
		{
			const char* szName;
			uint8_t nLadderType;
			uint8_t nCurrentLadderType;
			int32_t nPosition;
			int32_t nEntryCount;
			int32_t nStart;
			int32_t nCount;
			int32_t nNameSize;
			bool bList;
		};

		const Case cases[] = {
			{ "First page", 0x13, 0x13, -1, 1000, 0, 5, 16, true },
			{ "Later page", 0x13, 0x13, 20, 1000, 40, 5, 16, true },
			{ "Longer names", 0x09, 0x09, -1, 1000, 10, 5, 24, true },
			{ "End of the ladder", 0x13, 0x13, -1, 42, 40, 5, 16, true },
			{ "Start after the end", 0x13, 0x13, -1, 30, 40, 5, 16, true },
			{ "Other ladder type", 0x13, 0x01, -1, 1000, 0, 5, 16, true },
			{ "No ladder list", 0x13, 0x13, -1, 1000, 0, 5, 16, false },
		};

		for (const Case& testCase : cases)
		{
			CAPTURE(testCase.szName);
			const std::vector<uint8_t> data = ladder_entries(entries, testCase.nNameSize);

			std::vector<std::vector<std::string>> logs;
			std::vector<std::vector<int32_t>> states;
			for (const auto& [callback, pGlobals] : { std::make_pair(sut, &moo_ladder_globals()), std::make_pair(original, &original_ladder_globals()) })
			{
				D2WinRecorder::log.clear();
				*pGlobals->pnLadderType = testCase.nCurrentLadderType;
				*pGlobals->pnLadderPosition = testCase.nPosition;
				*pGlobals->pnLadderRequestedPosition = 7;
				*pGlobals->pnLadderDisplayedPosition = 8;
				*pGlobals->pnLadderEntryCount = testCase.nEntryCount;
				std::strcpy(pGlobals->szLadderCharacterName, "Requested");
				*pGlobals->ppLadderList = testCase.bList ? reinterpret_cast<D2WinTextBoxStrc*>(gFakeLadderList) : nullptr;

				callback(testCase.nStart, testCase.nCount, testCase.nNameSize, testCase.nLadderType, data.data());

				logs.push_back(D2WinRecorder::log);
				states.push_back({ *pGlobals->pnLadderType, *pGlobals->pnLadderPosition, *pGlobals->pnLadderRequestedPosition, *pGlobals->pnLadderDisplayedPosition });
			}

			CHECK_EQ(logs[0], logs[1]);
			CHECK_EQ(states[0], states[1]);
		}

		// Five lines with five cells each
		D2WinRecorder::log.clear();
		gnLadderType_6F9BC058 = 0x13;
		gnLadderPosition_6F9BC05C = -1;
		gnLadderEntryCount_6F9C2450 = 1000;
		gpLadderList_6F9C2814 = reinterpret_cast<D2WinTextBoxStrc*>(gFakeLadderList);
		const std::vector<uint8_t> data = ladder_entries(entries, 16);
		sut(0, 5, 16, 0x13, data.data());
		CHECK_EQ(D2WinRecorder::log.size(), 1 + 5 * 7);
		CHECK_EQ(D2WinRecorder::log[0], "SetLine LadderList 0");
	}
}
