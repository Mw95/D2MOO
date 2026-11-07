#include <doctest.h>

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <D2WinRecorder.h>
#include <ImportTablePatch.h>
#include <StormStorageMocks.h>

#include <CharSel.h>
#include <MainMenus.h>

#include "D2LaunchTestFixtures.h"


// The globals used by the character list, with their address in the original dll
#define D2LAUNCH_CHARLIST_GLOBALS(X) \
	X(BOOL, gbAllowHardcore, 0x6FA3CA44) \
	X(int32_t, gnGameType, 0x6FA3CD5C) \
	X(BOOL, sgbCharacterListFull, 0x6FA3CA78) \
	X(BOOL, sgbCreateNewCharacterDisabled, 0x6FA3CA58) \
	X(uint8_t, sgbTestRealmNamesInitialized, 0x6FA3CA48) \
	X(int32_t, sgnCharacterCount, 0x6FA3CA64) \
	X(int32_t, sgnCreateNewCharacterIndex, 0x6FA3321C) \
	X(int32_t, sgnMoreCharactersIndex, 0x6FA33220) \
	X(int32_t, sgnRealmState, 0x6FA3CA4C) \
	X(int32_t, sgnScrollOffset, 0x6FA3CA68) \
	X(int32_t, sgnSelectedIndex, 0x6FA33218) \
	X(int32_t, sgnVisibleSlotCount, 0x6FA33224) \
	X(D2WinControlStrc*, sgpConvertToExpansionButton, 0x6FA3CA38) \
	X(D2WinControlStrc*, sgpCreateNewCharacterButton, 0x6FA3C90C) \
	X(D2WinImageStrc*, sgpCreateNewCharacterDisabledImage, 0x6FA3B884) \
	X(D2WinControlStrc*, sgpDeleteButton, 0x6FA3C8D8) \
	X(D2WinControlStrc*, sgpOkButton, 0x6FA3B8C0) \
	X(D2WinTextBoxStrc*, sgpRealmStatusTextBox, 0x6FA3CA70) \
	X(D2WinButtonStrc*, sgpScrollDownButton, 0x6FA3B9D4) \
	X(D2WinButtonStrc*, sgpScrollUpButton, 0x6FA3B888) \
	X(D2WinTextBoxStrc*, sgpSelectedCharacterClassTextBox, 0x6FA3B9C8) \
	X(D2WinTextBoxStrc*, sgpSelectedCharacterNameTextBox, 0x6FA3B8B4) \
	X(D2WinTextBoxStrc*, sgpSelectedCharacterRealmTextBox, 0x6FA3B9D0) \
	X(D2WinImageStrc*, sgpSelectionImage, 0x6FA3B8B8) \
	X(D2CharSelNodeStrc*, sgptCharacterList, 0x6FA3CA5C) \
	X(D2CharSelNodeStrc*, sgptSelected, 0x6FA3CA60) \
	X(D2RealmCharListCacheStrc*, sgpRealmCharListCache, 0x6FA3CA88) \
	X(D2ShardStrc**, sgptShardArray, 0x6FA3D0FC) \
	X(int32_t, sgnShardListSize, 0x6FA3D100)

#define X(TYPE, NAME, ADDRESS) extern TYPE NAME;
D2LAUNCH_CHARLIST_GLOBALS(X)
#undef X
extern int32_t sganCharacterSlotY[CHARSEL_MAX_VISIBLE_SLOTS];
extern D2WinTextBoxStrc* sgpCharacterSlotTextBoxes[CHARSEL_MAX_VISIBLE_SLOTS];
extern Unicode sgawszTestRealmNames[7][256];


namespace
{
struct CharListGlobals
{
#define X(TYPE, NAME, ADDRESS) TYPE* p_##NAME;
	D2LAUNCH_CHARLIST_GLOBALS(X)
#undef X
	int32_t* pnSlotY;
	D2WinTextBoxStrc** ppSlotTextBoxes;
};

const CharListGlobals& moo_charlist_globals()
{
	static const CharListGlobals globals = {
#define X(TYPE, NAME, ADDRESS) &NAME,
		D2LAUNCH_CHARLIST_GLOBALS(X)
#undef X
		sganCharacterSlotY,
		sgpCharacterSlotTextBoxes,
	};
	return globals;
}

const CharListGlobals& original_charlist_globals()
{
	static const CharListGlobals globals = {
#define X(TYPE, NAME, ADDRESS) original_d2launch_global<TYPE>(ADDRESS),
		D2LAUNCH_CHARLIST_GLOBALS(X)
#undef X
		original_d2launch_global<int32_t>(0x6FA3B894),
		original_d2launch_global<D2WinTextBoxStrc*>(0x6FA3C910),
	};
	return globals;
}

struct CharListApi
{
	decltype(&CHARSEL_LoadRealmCharacters) LoadRealmCharacters;
	decltype(&CHARSEL_AddCharacter) AddCharacter;
	decltype(&CHARSEL_UpdateCharacterList) UpdateCharacterList;
	decltype(&CHARSEL_UpdateSelection) UpdateSelection;
	const CharListGlobals* pGlobals;
};

const CharListApi& moo_charlist_api()
{
	static const CharListApi api = { &CHARSEL_LoadRealmCharacters, &CHARSEL_AddCharacter, &CHARSEL_UpdateCharacterList, &CHARSEL_UpdateSelection, &moo_charlist_globals() };
	return api;
}

const CharListApi& original_charlist_api()
{
	static const CharListApi api = {
		reinterpret_cast<decltype(&CHARSEL_LoadRealmCharacters)>(original_d2launch_address(0x6FA16350)),
		reinterpret_cast<decltype(&CHARSEL_AddCharacter)>(original_d2launch_address(0x6FA147F0)),
		reinterpret_cast<decltype(&CHARSEL_UpdateCharacterList)>(original_d2launch_address(0x6FA13B40)),
		reinterpret_cast<decltype(&CHARSEL_UpdateSelection)>(original_d2launch_address(0x6FA14D30)),
		&original_charlist_globals(),
	};
	return api;
}

struct ExpansionMock
{
	static inline BOOL bExpansion = TRUE;
	static int __fastcall IsExpansion() { return bExpansion; }
};

struct TickCountMock
{
	static inline DWORD dwTickCount = 100000;
	static DWORD WINAPI GetTickCount() { return dwTickCount; }
};

// Fake controls, only their addresses are used
char gaFakeControls[32][16];

template<class Fixture>
struct CharListFixture : D2LaunchFileFixture<Fixture>
{
	ImportTablePatch patches;

	CharListFixture()
	{
		hook_d2lang_string_mocks(this->hooks);
		hook_storm_storage_mocks(this->hooks);
		hook_d2win_recorder(this->hooks);
		this->hooks.hook("Fog.dll", 10227, reinterpret_cast<void*>(&FOG_IsExpansion), reinterpret_cast<const void*>(&ExpansionMock::IsExpansion));
		patches.patch_both(get_original_d2launch(), "KERNEL32.dll", "GetTickCount", reinterpret_cast<const void*>(&TickCountMock::GetTickCount));
		ExpansionMock::bExpansion = TRUE;
	}

	~CharListFixture()
	{
		for (const CharListGlobals* pGlobals : { &moo_charlist_globals(), &original_charlist_globals() })
		{
			free_list(*pGlobals);
		}
		D2WinRecorder::reset();
		StormStorageMock::reset();
	}

	// The nodes are allocated with the mocked FOG_Alloc (malloc)
	static void free_list(const CharListGlobals& globals)
	{
		for (D2CharSelNodeStrc* pNode = *globals.p_sgptCharacterList; pNode;)
		{
			D2CharSelNodeStrc* pNext = pNode->pNext;
			std::free(pNode);
			pNode = pNext;
		}
		*globals.p_sgptCharacterList = nullptr;
		*globals.p_sgptSelected = nullptr;
	}

	static void reset_globals(const CharListGlobals& globals)
	{
		free_list(globals);
		int nControl = 0;
		const auto control = [&nControl](const char* szName)
		{
			D2WinRecorder::names[gaFakeControls[nControl]] = szName;
			return gaFakeControls[nControl++];
		};

		*globals.p_gbAllowHardcore = FALSE;
		*globals.p_gnGameType = 3;
		*globals.p_sgbCharacterListFull = FALSE;
		*globals.p_sgbCreateNewCharacterDisabled = FALSE;
		*globals.p_sgbTestRealmNamesInitialized = 0;
		*globals.p_sgnCharacterCount = 0;
		*globals.p_sgnCreateNewCharacterIndex = -999;
		*globals.p_sgnMoreCharactersIndex = -999;
		*globals.p_sgnRealmState = 0;
		*globals.p_sgnScrollOffset = 0;
		*globals.p_sgnSelectedIndex = -1;
		*globals.p_sgnVisibleSlotCount = 4;
		*globals.p_sgpConvertToExpansionButton = reinterpret_cast<D2WinControlStrc*>(control("ConvertToExpansion"));
		*globals.p_sgpCreateNewCharacterButton = reinterpret_cast<D2WinControlStrc*>(control("CreateNewCharacter"));
		*globals.p_sgpCreateNewCharacterDisabledImage = reinterpret_cast<D2WinImageStrc*>(control("CreateNewCharacterDisabled"));
		*globals.p_sgpDeleteButton = reinterpret_cast<D2WinControlStrc*>(control("Delete"));
		*globals.p_sgpOkButton = reinterpret_cast<D2WinControlStrc*>(control("Ok"));
		*globals.p_sgpRealmStatusTextBox = reinterpret_cast<D2WinTextBoxStrc*>(control("RealmStatus"));
		*globals.p_sgpScrollDownButton = reinterpret_cast<D2WinButtonStrc*>(control("ScrollDown"));
		*globals.p_sgpScrollUpButton = reinterpret_cast<D2WinButtonStrc*>(control("ScrollUp"));
		*globals.p_sgpSelectedCharacterClassTextBox = reinterpret_cast<D2WinTextBoxStrc*>(control("SelectedClass"));
		*globals.p_sgpSelectedCharacterNameTextBox = reinterpret_cast<D2WinTextBoxStrc*>(control("SelectedName"));
		*globals.p_sgpSelectedCharacterRealmTextBox = reinterpret_cast<D2WinTextBoxStrc*>(control("SelectedRealm"));
		*globals.p_sgpSelectionImage = reinterpret_cast<D2WinImageStrc*>(control("Selection"));
		*globals.p_sgpRealmCharListCache = nullptr;
		*globals.p_sgptShardArray = nullptr;
		*globals.p_sgnShardListSize = 0;
		for (int i = 0; i < CHARSEL_MAX_VISIBLE_SLOTS; ++i)
		{
			globals.pnSlotY[i] = 100 + 50 * i;
			globals.ppSlotTextBoxes[i] = reinterpret_cast<D2WinTextBoxStrc*>(control(("Slot" + std::to_string(i)).c_str()));
		}
	}
};

// The fields of a node that are always written, with the composite unit replaced by its number
std::string describe(const D2CharSelNodeStrc* pNode)
{
	std::string szRealm;
	for (const Unicode* p = pNode->wszRealm; *p != 0; ++p)
	{
		szRealm += (char)(uint16_t)*p;
	}
	return std::string(pNode->szName) + "|" + szRealm + "|" + D2WinRecorder::bytes(pNode->pComponents, 16) + "|" + D2WinRecorder::bytes(pNode->pComponentColors, 16)
		+ "|" + std::to_string(pNode->nClass) + "|" + std::to_string(pNode->nLevel) + "|" + std::to_string(pNode->nFlags) + "|" + std::to_string(pNode->nVersion)
		+ "|" + std::to_string(pNode->nGuildFlags) + "|" + std::string(pNode->szGuildTag, strnlen(pNode->szGuildTag, 3)) + "|" + std::to_string(pNode->bLadder)
		+ "|" + std::to_string(pNode->unk0x32F) + "|" + std::to_string(pNode->unk0x330) + "|" + std::to_string(pNode->eType) + "|unit" + std::to_string(D2WinRecorder::unit_id(pNode->hUnit))
		+ "|" + std::to_string(pNode->dwLastWriteTimeLow) + "|" + std::to_string(pNode->dwLastWriteTimeHigh) + "|" + std::to_string(pNode->dwExpirationTime);
}

struct State
{
	std::vector<std::string> nodes;
	int nSelected;
	std::vector<int64_t> scalars;

	bool operator==(const State& other) const { return nodes == other.nodes && nSelected == other.nSelected && scalars == other.scalars; }
};

State capture(const CharListGlobals& globals)
{
	State state = {};
	state.nSelected = -1;
	int nIndex = 0;
	for (D2CharSelNodeStrc* pNode = *globals.p_sgptCharacterList; pNode; pNode = pNode->pNext, ++nIndex)
	{
		state.nodes.push_back(describe(pNode));
		if (pNode == *globals.p_sgptSelected)
		{
			state.nSelected = nIndex;
		}
	}
	state.scalars = {
		*globals.p_gbAllowHardcore, *globals.p_sgbCharacterListFull, *globals.p_sgbCreateNewCharacterDisabled, *globals.p_sgbTestRealmNamesInitialized,
		*globals.p_sgnCharacterCount, *globals.p_sgnCreateNewCharacterIndex, *globals.p_sgnMoreCharactersIndex, *globals.p_sgnRealmState,
		*globals.p_sgnScrollOffset, *globals.p_sgnSelectedIndex, *globals.p_sgnVisibleSlotCount,
	};
	return state;
}

// Statstring of a character: version, 11 components, class + 1, 11 colors, level, flags, guild flags, ladder, 2 unknown bytes, guild tag.
// No byte is zero, the statstring is zero terminated.
std::string statstring(uint8_t nClass, uint8_t nLevel, uint16_t nFlags, uint8_t nLadder, const char* szGuildTag = "")
{
	std::string data;
	auto encode14 = [&data](uint32_t nValue)
	{
		data += (char)((nValue & 0x7F) | 0x80);
		data += (char)(((nValue >> 7) & 0x7F) | 0x80);
	};
	encode14(0x84);
	for (int i = 0; i < 11; ++i) data += (char)(i % 3 == 0 ? 0xFF : i + 1);
	data += (char)(nClass + 1);
	for (int i = 0; i < 11; ++i) data += (char)(i % 4 == 0 ? 0xFF : 0x20 + i);
	data += (char)nLevel;
	encode14(nFlags);
	encode14(0x10);
	data += (char)nLadder;
	data += (char)0xFF;
	data += (char)0xFF;
	data += szGuildTag;
	return data;
}

struct Character
{
	std::string szName;
	std::string szStatstring;
	uint32_t dwExpirationTime;
};

// Character list packet of the MCP (0x17 or 0x19 with expiration times)
std::vector<uint8_t> char_list_packet(uint8_t nPacketId, uint16_t nMaxCharacters, uint16_t nTotal, const std::vector<Character>& characters, int nReturned = -1)
{
	std::vector<uint8_t> packet = { nPacketId };
	auto u16 = [&packet](uint16_t nValue) { packet.push_back((uint8_t)nValue); packet.push_back((uint8_t)(nValue >> 8)); };
	u16(nMaxCharacters);
	u16(nTotal);
	u16(0);
	u16((uint16_t)(nReturned < 0 ? characters.size() : nReturned));
	for (const Character& character : characters)
	{
		if (nPacketId == 0x19)
		{
			for (int i = 0; i < 4; ++i) packet.push_back((uint8_t)(character.dwExpirationTime >> (8 * i)));
		}
		packet.insert(packet.end(), character.szName.begin(), character.szName.end());
		packet.push_back(0);
		packet.insert(packet.end(), character.szStatstring.begin(), character.szStatstring.end());
		packet.push_back(0);
	}
	return packet;
}

struct Step
{
	std::string szName;
	std::vector<std::string> log;
	State state;
	BOOL bResult;
};
}


TEST_SUITE("D2LaunchCharListTests")
{
	TEST_CASE_FIXTURE(CharListFixture<NoOpFixture>, "D2Launch.0x6FA16350 / D2Launch.0x6FA147F0 / D2Launch.0x6FA13B40 / D2Launch.0x6FA14D30")
	{
		const std::vector<Character> characters = {
			{ "Amazon", statstring(0, 12, 0x0020, 0xFF), 1000 },
			{ "Hardcore", statstring(1, 40, 0x0424, 1, "ABC"), 2000 },
			{ "Classic", statstring(2, 80, 0x0A00, 0xFF), 0 },
			{ "Dead", statstring(3, 30, 0x002C, 0xFF), 3000 },
			{ "Druid", statstring(5, 99, 0x0F20, 1), 4000 },
			{ "Assassin", statstring(6, 1, 0x0020, 0xFF, "G"), 5000 },
		};

		struct Case
		{
			const char* szName;
			BOOL bExpansion;
			const char* szRealmName;
			std::vector<uint8_t> packet;
			std::vector<uint32_t> failingClasses;
		};

		const Case cases[] = {
			{ "Expansion list with expiration times", TRUE, "USEast", char_list_packet(0x19, 8, 6, characters), {} },
			{ "Classic list", FALSE, "Europe", char_list_packet(0x17, 8, 3, { characters[0], characters[1], characters[2] }), {} },
			{ "More characters than returned", TRUE, "USWest", char_list_packet(0x19, 8, 10, { characters[0], characters[4] }), {} },
			{ "Full list", TRUE, "Asia", char_list_packet(0x19, 2, 2, { characters[1], characters[3] }), {} },
			{ "Fewer returned than announced", TRUE, "USEast", char_list_packet(0x19, 8, 1, { characters[0], characters[1] }), {} },
			{ "Test realm", TRUE, "BetaWest", char_list_packet(0x19, 8, 2, { characters[0], characters[1] }), {} },
			{ "Composite unit failure", TRUE, "USEast", char_list_packet(0x19, 8, 3, { characters[0], characters[4], characters[5] }), { 5 } },
			{ "Empty list", TRUE, "USEast", char_list_packet(0x19, 8, 0, {}), {} },
		};

		for (const Case& testCase : cases)
		{
			CAPTURE(testCase.szName);
			ExpansionMock::bExpansion = testCase.bExpansion;

			std::vector<std::vector<Step>> runs;
			for (const CharListApi* pApi : { &moo_charlist_api(), &original_charlist_api() })
			{
				D2WinRecorder::start_run();
				D2WinRecorder::names.clear();
				D2WinRecorder::failingClasses = testCase.failingClasses;
				StormStorageMock::reset();
				reset_globals(*pApi->pGlobals);
				std::vector<Step> steps;
				const auto record = [&steps, pApi](const char* szStep, BOOL bResult)
				{
					steps.push_back({ szStep, D2WinRecorder::log, capture(*pApi->pGlobals), bResult });
					D2WinRecorder::log.clear();
				};

				pApi->LoadRealmCharacters(testCase.szRealmName, testCase.packet.data(), FALSE);
				record("Load", 0);

				// A local character with a last write time, sorted by it in the expansion
				const std::string szLocal = statstring(4, 25, 0x0020, 0xFF);
				record("AddCharacter", pApi->AddCharacter("Local", nullptr, reinterpret_cast<const uint8_t*>(szLocal.c_str()), 0, 0x10, 0x01D00000));

				*pApi->pGlobals->p_sgnSelectedIndex = 1;
				record("Select", pApi->UpdateSelection());
				*pApi->pGlobals->p_sgnScrollOffset = 1;
				pApi->UpdateCharacterList();
				record("Scroll", 0);

				steps.back().log.push_back(StormStorageMock::registry_writes.empty() ? "registry untouched" : "registry written");
				runs.push_back(steps);
			}

			REQUIRE_EQ(runs[0].size(), runs[1].size());
			for (size_t i = 0; i < runs[0].size(); ++i)
			{
				CAPTURE(runs[0][i].szName);
				CHECK_EQ(runs[0][i].bResult, runs[1][i].bResult);
				CHECK_EQ(runs[0][i].log, runs[1][i].log);
				CHECK_EQ(runs[0][i].state.nodes, runs[1][i].state.nodes);
				CHECK_EQ(runs[0][i].state.nSelected, runs[1][i].state.nSelected);
				CHECK_EQ(runs[0][i].state.scalars, runs[1][i].state.scalars);
			}
		}
	}
}
