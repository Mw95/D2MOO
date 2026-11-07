#include <doctest.h>

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <D2Config.h>

#include <ChatDlg.h>
#include <ComCallback.h>

#include "D2MultiTestFixtures.h"
#include "D2MultiWinMocks.h"


extern D2MultiChannelUserStrc* gpChannelUsers_6F9C2B1C;
extern D2MultiUserHistoryStrc* gpUserHistory_6F9C2B20;
extern int32_t gnUserHistoryCount_6F9C2B24;
extern int32_t gnChannelUserCount_6F9C2B28;
extern int32_t gnUserListScroll_6F9C2B2C;
extern D2MultiChannelUserStrc* gptSelectedUnit_6F9C2B30;
extern BOOL gbRandomSeeded_6F9C2B3C;
extern int32_t gnSelectedUserIndex_6F9BE790;
extern D2ConfigStrc* gpConfig_6F9C26F0;
extern char gszCurrentChannel_6F9C2918[256];
extern D2WinControlStrc* gpUserListPageUp_6F9C2684;
extern D2WinControlStrc* gpUserListPageDown_6F9C2688;
extern D2WinControlStrc* gpUserListUp_6F9C268C;
extern D2WinControlStrc* gpUserListDown_6F9C2690;
extern D2WinTextBoxStrc* gpChannelTitle_6F9C28AC;
extern BOOL gbChatNotCreated_6F9C270C;
extern D2WinEditBoxStrc* gpChatEditBox_6F9C28A8;
extern D2WinControlStrc* gpSendButton_6F9C2658;
extern D2WinControlStrc* gpWhisperButton_6F9C265C;
extern D2WinControlStrc* gpSquelchButton_6F9C2664;
extern D2WinControlStrc* gpUnsquelchButton_6F9C2668;
extern D2WinControlStrc* gpEmoteButton_6F9C266C;


namespace
{
struct UserListGlobals
{
	D2MultiChannelUserStrc** ppChannelUsers;
	D2MultiUserHistoryStrc** ppUserHistory;
	int32_t* pnUserHistoryCount;
	int32_t* pnChannelUserCount;
	int32_t* pnUserListScroll;
	D2MultiChannelUserStrc** ppSelectedUnit;
	BOOL* pbRandomSeeded;
	int32_t* pnSelectedUserIndex;
	D2ConfigStrc** ppConfig;
	char* szCurrentChannel;
	D2WinControlStrc** ppPageUp;
	D2WinControlStrc** ppPageDown;
	D2WinControlStrc** ppUp;
	D2WinControlStrc** ppDown;
	D2WinTextBoxStrc** ppChannelTitle;
	BOOL* pbChatNotCreated;
	D2WinEditBoxStrc** ppChatEditBox;
	D2WinControlStrc** ppSendButton;
	D2WinControlStrc** ppWhisperButton;
	D2WinControlStrc** ppSquelchButton;
	D2WinControlStrc** ppUnsquelchButton;
	D2WinControlStrc** ppEmoteButton;
};

const UserListGlobals& moo_list_globals()
{
	static const UserListGlobals globals = {
		&gpChannelUsers_6F9C2B1C, &gpUserHistory_6F9C2B20, &gnUserHistoryCount_6F9C2B24, &gnChannelUserCount_6F9C2B28, &gnUserListScroll_6F9C2B2C,
		&gptSelectedUnit_6F9C2B30, &gbRandomSeeded_6F9C2B3C, &gnSelectedUserIndex_6F9BE790, &gpConfig_6F9C26F0, gszCurrentChannel_6F9C2918,
		&gpUserListPageUp_6F9C2684, &gpUserListPageDown_6F9C2688, &gpUserListUp_6F9C268C, &gpUserListDown_6F9C2690, &gpChannelTitle_6F9C28AC,
		&gbChatNotCreated_6F9C270C, &gpChatEditBox_6F9C28A8, &gpSendButton_6F9C2658, &gpWhisperButton_6F9C265C, &gpSquelchButton_6F9C2664,
		&gpUnsquelchButton_6F9C2668, &gpEmoteButton_6F9C266C,
	};
	return globals;
}

const UserListGlobals& original_list_globals()
{
	static const UserListGlobals globals = {
		original_d2multi_global<D2MultiChannelUserStrc*>(0x6F9C2B1C),
		original_d2multi_global<D2MultiUserHistoryStrc*>(0x6F9C2B20),
		original_d2multi_global<int32_t>(0x6F9C2B24),
		original_d2multi_global<int32_t>(0x6F9C2B28),
		original_d2multi_global<int32_t>(0x6F9C2B2C),
		original_d2multi_global<D2MultiChannelUserStrc*>(0x6F9C2B30),
		original_d2multi_global<BOOL>(0x6F9C2B3C),
		original_d2multi_global<int32_t>(0x6F9BE790),
		original_d2multi_global<D2ConfigStrc*>(0x6F9C26F0),
		original_d2multi_global<char>(0x6F9C2918),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C2684),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C2688),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C268C),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C2690),
		original_d2multi_global<D2WinTextBoxStrc*>(0x6F9C28AC),
		original_d2multi_global<BOOL>(0x6F9C270C),
		original_d2multi_global<D2WinEditBoxStrc*>(0x6F9C28A8),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C2658),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C265C),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C2664),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C2668),
		original_d2multi_global<D2WinControlStrc*>(0x6F9C266C),
	};
	return globals;
}

struct UserListApi
{
	decltype(&COMCALLBACK_AddUser) AddUser;
	decltype(&COMCALLBACK_ClearUserList) ClearUserList;
	decltype(&COMCALLBACK_ScrollUserList) ScrollUserList;
	decltype(&COMCALLBACK_UpdateUserList) UpdateUserList;
	decltype(&COMCALLBACK_UpdateChatButtons) UpdateChatButtons;
	const UserListGlobals* pGlobals;
};

const UserListApi& moo_list_api()
{
	static const UserListApi api = { &COMCALLBACK_AddUser, &COMCALLBACK_ClearUserList, &COMCALLBACK_ScrollUserList, &COMCALLBACK_UpdateUserList, &COMCALLBACK_UpdateChatButtons, &moo_list_globals() };
	return api;
}

const UserListApi& original_list_api()
{
	static const UserListApi api = {
		reinterpret_cast<decltype(&COMCALLBACK_AddUser)>(original_d2multi_address(0x6F9AC590)),
		reinterpret_cast<decltype(&COMCALLBACK_ClearUserList)>(original_d2multi_address(0x6F9AD050)),
		reinterpret_cast<decltype(&COMCALLBACK_ScrollUserList)>(original_d2multi_address(0x6F9AB5B0)),
		reinterpret_cast<decltype(&COMCALLBACK_UpdateUserList)>(original_d2multi_address(0x6F9AC100)),
		reinterpret_cast<decltype(&COMCALLBACK_UpdateChatButtons)>(original_d2multi_address(0x6F9AF030)),
		&original_list_globals(),
	};
	return api;
}

// Character data of a Diablo II statstring, see D2MultiTextTests
std::string character_data(uint8_t nClass, uint8_t nLevel, uint16_t nFlags, uint8_t nLadder)
{
	std::string data;
	auto encode14 = [&data](uint32_t nValue)
	{
		data += (char)((nValue & 0x7F) | 0x80);
		data += (char)(((nValue >> 7) & 0x7F) | 0x80);
	};
	encode14(10);
	for (int i = 0; i < 11; ++i) data += (char)(i + 1);
	data += (char)(nClass + 1);
	for (int i = 0; i < 11; ++i) data += (char)(0x20 + i);
	data += (char)nLevel;
	encode14(nFlags);
	encode14(0);
	data += (char)nLadder;
	data += (char)0xFF;
	data += (char)0xFF;
	return data;
}

struct ExpansionMock
{
	static inline BOOL bExpansion = TRUE;
	static int __fastcall IsExpansion() { return bExpansion; }
};

// Fake controls, only their addresses are used
char gaFakeControls[16][16];

template<class Fixture>
struct D2MultiUserListFixture : D2MultiFixture<Fixture>
{
	D2ConfigStrc tConfig;

	D2MultiUserListFixture()
	{
		hook_d2win_recorder(this->hooks);
		this->hooks.hook("Fog.dll", 10227, reinterpret_cast<void*>(&FOG_IsExpansion), reinterpret_cast<const void*>(&ExpansionMock::IsExpansion));
		ExpansionMock::bExpansion = TRUE;
		std::memset(&tConfig, 0, sizeof(tConfig));
		tConfig.unpackedCTemp.nCharacterSaveFlags = 0x24;

		const char* szNames[] = { "PageUp", "PageDown", "Up", "Down", "ChannelTitle", "ChatEditBox", "Send", "Whisper", "Squelch", "Unsquelch", "Emote" };
		for (int i = 0; i < 11; ++i)
		{
			D2WinRecorder::names[gaFakeControls[i]] = szNames[i];
		}
		for (const UserListGlobals* pGlobals : { &moo_list_globals(), &original_list_globals() })
		{
			reset_globals(*pGlobals, FALSE);
		}
	}

	~D2MultiUserListFixture()
	{
		for (const UserListGlobals* pGlobals : { &moo_list_globals(), &original_list_globals() })
		{
			free_lists(*pGlobals);
			*pGlobals->ppConfig = nullptr;
			*pGlobals->ppPageUp = *pGlobals->ppPageDown = *pGlobals->ppUp = *pGlobals->ppDown = nullptr;
			*pGlobals->ppChannelTitle = nullptr;
			*pGlobals->ppChatEditBox = nullptr;
			*pGlobals->ppSendButton = *pGlobals->ppWhisperButton = *pGlobals->ppSquelchButton = *pGlobals->ppUnsquelchButton = *pGlobals->ppEmoteButton = nullptr;
			*pGlobals->pbChatNotCreated = FALSE;
		}
		D2WinRecorder::reset();
	}

	// The nodes are allocated with the mocked FOG_Alloc (malloc)
	static void free_lists(const UserListGlobals& globals)
	{
		for (D2MultiChannelUserStrc* pUser = *globals.ppChannelUsers; pUser;)
		{
			D2MultiChannelUserStrc* pNext = pUser->pNext;
			std::free(pUser);
			pUser = pNext;
		}
		*globals.ppChannelUsers = nullptr;
		for (D2MultiUserHistoryStrc* pHistory = *globals.ppUserHistory; pHistory;)
		{
			D2MultiUserHistoryStrc* pNext = pHistory->pNext;
			std::free(pHistory);
			pHistory = pNext;
		}
		*globals.ppUserHistory = nullptr;
		*globals.pnUserHistoryCount = 0;
		*globals.pnChannelUserCount = 0;
		*globals.pnUserListScroll = 0;
		*globals.ppSelectedUnit = nullptr;
		*globals.pnSelectedUserIndex = -1;
	}

	void reset_globals(const UserListGlobals& globals, BOOL bChatNotCreated)
	{
		free_lists(globals);
		// Already seeded: the random start frames come from each implementation's CRT and are not compared
		*globals.pbRandomSeeded = TRUE;
		*globals.ppConfig = &tConfig;
		std::strcpy(globals.szCurrentChannel, "Diablo II USA-1");
		*globals.ppPageUp = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[0]);
		*globals.ppPageDown = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[1]);
		*globals.ppUp = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[2]);
		*globals.ppDown = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[3]);
		*globals.ppChannelTitle = reinterpret_cast<D2WinTextBoxStrc*>(gaFakeControls[4]);
		*globals.ppChatEditBox = reinterpret_cast<D2WinEditBoxStrc*>(gaFakeControls[5]);
		*globals.ppSendButton = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[6]);
		*globals.ppWhisperButton = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[7]);
		*globals.ppSquelchButton = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[8]);
		*globals.ppUnsquelchButton = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[9]);
		*globals.ppEmoteButton = reinterpret_cast<D2WinControlStrc*>(gaFakeControls[10]);
		*globals.pbChatNotCreated = bChatNotCreated;
	}
};

// The channel users, with the pointers replaced by unit numbers and list positions
struct UserSnapshot
{
	std::vector<std::vector<uint8_t>> users;
	int32_t nCount;
	int32_t nScroll;
	int nSelected;
	int32_t nSelectedIndex;
	int32_t nHistoryCount;

	bool operator==(const UserSnapshot& other) const
	{
		return users == other.users && nCount == other.nCount && nScroll == other.nScroll && nSelected == other.nSelected && nSelectedIndex == other.nSelectedIndex && nHistoryCount == other.nHistoryCount;
	}
};

UserSnapshot snapshot(const UserListGlobals& globals)
{
	UserSnapshot result = {};
	result.nSelected = -1;
	int nIndex = 0;
	for (D2MultiChannelUserStrc* pUser = *globals.ppChannelUsers; pUser; pUser = pUser->pNext, ++nIndex)
	{
		D2MultiChannelUserStrc tUser = *pUser;
		tUser.pCompositeUnit = reinterpret_cast<D2CompositeUnitStrc*>((intptr_t)D2WinRecorder::unit_id(pUser->pCompositeUnit));
		tUser.pNext = nullptr;
		const auto pBytes = reinterpret_cast<const uint8_t*>(&tUser);
		result.users.emplace_back(pBytes, pBytes + sizeof(tUser));
		if (pUser == *globals.ppSelectedUnit)
		{
			result.nSelected = nIndex;
		}
	}
	result.nCount = *globals.pnChannelUserCount;
	result.nScroll = *globals.pnUserListScroll;
	result.nSelectedIndex = *globals.pnSelectedUserIndex;
	result.nHistoryCount = *globals.pnUserHistoryCount;
	return result;
}

struct Step
{
	std::string szName;
	std::vector<std::string> log;
	UserSnapshot users;
	int nReturnedUser;
};

struct UserSpec
{
	const char* szUserName;
	std::string szStatstring;
	uint32_t nFlags;
};

std::vector<UserSpec> user_specs()
{
	std::vector<UserSpec> users = {
		{ "Amazon*First", "PX2D" "USEast,Amazon," + character_data(0, 10, 0x0020, 0xFF), 0x00 },
		{ "Sorc*Second", "PX2D" "USEast,Sorc," + character_data(1, 50, 0x0524, 1), 0x02 },
		{ "Necro*Third", "VD2D" "Europe,Necro," + character_data(2, 80, 0x0A00, 0xFF), 0x04 },
		{ "*Chat", "TAHC", 0x08 },
		{ "Paladin*Fifth", "PX2D" "USWest,Paladin," + character_data(3, 99, 0x0F2C, 1), 0x01 },
		{ "Barb*Sixth", "PX2D" "USEast,Barb," + character_data(4, 30, 0x002C, 0xFF), 0x20 },
		{ "*Starcraft", "RATS 0 0 0", 0x00 },
		{ "Druid*Eighth", "PX2D" "Asia,Druid," + character_data(5, 75, 0x0A20, 0xFF), 0x00 },
		{ "Assassin*Ninth", "PX2D" "Asia,Assassin," + character_data(6, 60, 0x0624, 1), 0x00 },
		{ "Open*Tenth", "PX2D", 0x00 },
	};
	for (int i = 0; i < 6; ++i)
	{
		// Named "Extra<n>*Account<n>" by run_user_list
		users.push_back({ nullptr, "PX2D" "USEast,Extra," + character_data((uint8_t)(i % 7), (uint8_t)(i * 9 + 1), (uint16_t)(0x0020 | (i << 8)), 0xFF), (uint32_t)(i & 1 ? 0x04 : 0) });
	}
	return users;
}

std::vector<Step> run_user_list(const UserListApi& api, D2MultiUserListFixture<NoOpFixture>& fixture, BOOL bChatNotCreated)
{
	std::vector<Step> steps;
	D2WinRecorder::start_run();
	fixture.reset_globals(*api.pGlobals, bChatNotCreated);

	const auto record = [&steps, &api](const std::string& szName, D2MultiChannelUserStrc* pReturned)
	{
		int nReturned = -1;
		int nIndex = 0;
		for (D2MultiChannelUserStrc* pUser = *api.pGlobals->ppChannelUsers; pUser; pUser = pUser->pNext, ++nIndex)
		{
			if (pUser == pReturned)
			{
				nReturned = nIndex;
			}
		}
		steps.push_back({ szName, D2WinRecorder::log, snapshot(*api.pGlobals), nReturned });
		D2WinRecorder::log.clear();
	};

	std::vector<UserSpec> users = user_specs();
	for (size_t i = 0; i < users.size(); ++i)
	{
		std::string szUserName = users[i].szUserName ? users[i].szUserName : "Extra" + std::to_string(i) + "*Account" + std::to_string(i);
		record("AddUser " + szUserName, api.AddUser(szUserName.c_str(), users[i].szStatstring.c_str(), users[i].nFlags));
	}

	// The same account with another character and other flags updates the user
	record("Update Sorc*Second", api.AddUser("Druid*Second", ("PX2D" "USEast,Druid," + character_data(5, 51, 0x0520, 1)).c_str(), 0x00));
	record("Update *Chat", api.AddUser("*Chat", "TAHC", 0x02));

	api.ScrollUserList(3);
	record("Scroll 3", nullptr);
	api.ScrollUserList(100);
	record("Scroll 100", nullptr);
	api.ScrollUserList(-1);
	record("Scroll -1", nullptr);

	// Select a user, the selection is cleared with the list
	*api.pGlobals->ppSelectedUnit = (*api.pGlobals->ppChannelUsers)->pNext;
	*api.pGlobals->pnSelectedUserIndex = 1;
	api.UpdateUserList();
	record("Update with a selection", nullptr);
	if (!bChatNotCreated)
	{
		api.UpdateChatButtons();
		record("Update chat buttons", nullptr);
	}

	api.ClearUserList();
	record("Clear", nullptr);

	api.ScrollUserList(1);
	record("Scroll the empty list", nullptr);
	return steps;
}
}


TEST_SUITE("D2MultiUserListTests")
{
	TEST_CASE_FIXTURE(D2MultiUserListFixture<NoOpFixture>, "D2Multi.0x6F9AC590 / D2Multi.0x6F9AD050 / D2Multi.0x6F9AB5B0 / D2Multi.0x6F9AC100 / D2Multi.0x6F9AF030")
	{
		struct Variant
		{
			const char* szName;
			BOOL bExpansion;
			BOOL bChatNotCreated;
			std::vector<uint32_t> failingClasses;
			std::vector<Unicode> editBoxText;
		};

		const Variant variants[] = {
			{ "Expansion", TRUE, FALSE, {}, {} },
			{ "Classic, chat not created", FALSE, TRUE, {}, {} },
			{ "Composite units failing for some classes", TRUE, FALSE, { 1, 5 }, { 'h', 'i', 0 } },
		};

		for (const Variant& variant : variants)
		{
			CAPTURE(variant.szName);
			ExpansionMock::bExpansion = variant.bExpansion;
			D2WinRecorder::failingClasses = variant.failingClasses;
			D2WinRecorder::editBoxText = variant.editBoxText;

			const std::vector<Step> moo_steps = run_user_list(moo_list_api(), *this, variant.bChatNotCreated);
			CHECK_FALSE(D2WinRecorder::bFrameOutOfRange);
			const std::vector<Step> original_steps = run_user_list(original_list_api(), *this, variant.bChatNotCreated);
			CHECK_FALSE(D2WinRecorder::bFrameOutOfRange);

			REQUIRE_EQ(moo_steps.size(), original_steps.size());
			for (size_t i = 0; i < moo_steps.size(); ++i)
			{
				CAPTURE(moo_steps[i].szName);
				CHECK_EQ(moo_steps[i].log, original_steps[i].log);
				CHECK_EQ(moo_steps[i].nReturnedUser, original_steps[i].nReturnedUser);
				CHECK_EQ(moo_steps[i].users.nCount, original_steps[i].users.nCount);
				CHECK_EQ(moo_steps[i].users.nScroll, original_steps[i].users.nScroll);
				CHECK_EQ(moo_steps[i].users.nSelected, original_steps[i].users.nSelected);
				CHECK_EQ(moo_steps[i].users.nSelectedIndex, original_steps[i].users.nSelectedIndex);
				CHECK_EQ(moo_steps[i].users.nHistoryCount, original_steps[i].users.nHistoryCount);
				CHECK_MESSAGE(moo_steps[i].users.users == original_steps[i].users.users, "Comparing the channel users");
			}

			// All the users are added, then cleared
			CHECK_EQ(moo_steps[15].users.nCount, 16);
			CHECK_EQ(moo_steps[moo_steps.size() - 2].users.nCount, 0);
			CHECK(moo_steps[moo_steps.size() - 2].users.users.empty());
		}
	}
}
