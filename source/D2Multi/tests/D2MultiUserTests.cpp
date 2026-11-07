#include <doctest.h>

#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <ComCallback.h>
#include <D2WinComp.h>

#include "D2MultiTestFixtures.h"


extern D2MultiChannelUserStrc* gpChannelUsers_6F9C2B1C;
extern D2MultiUserHistoryStrc* gpUserHistory_6F9C2B20;
extern int32_t gnUserHistoryCount_6F9C2B24;


namespace
{
struct UserGlobals
{
	D2MultiChannelUserStrc** ppChannelUsers;
	D2MultiUserHistoryStrc** ppUserHistory;
	int32_t* pnUserHistoryCount;
};

const UserGlobals& moo_user_globals()
{
	static const UserGlobals globals = { &gpChannelUsers_6F9C2B1C, &gpUserHistory_6F9C2B20, &gnUserHistoryCount_6F9C2B24 };
	return globals;
}

const UserGlobals& original_user_globals()
{
	static const UserGlobals globals = {
		original_d2multi_global<D2MultiChannelUserStrc*>(0x6F9C2B1C),
		original_d2multi_global<D2MultiUserHistoryStrc*>(0x6F9C2B20),
		original_d2multi_global<int32_t>(0x6F9C2B24),
	};
	return globals;
}

using History = std::vector<std::pair<std::string, std::string>>;

History read_history(const UserGlobals& globals)
{
	History history;
	for (D2MultiUserHistoryStrc* pHistory = *globals.ppUserHistory; pHistory; pHistory = pHistory->pNext)
	{
		history.emplace_back(pHistory->szUserName, pHistory->szCharacterName);
	}
	return history;
}

// The nodes are allocated with the mocked FOG_Alloc (malloc)
void free_history(const UserGlobals& globals)
{
	for (D2MultiUserHistoryStrc* pHistory = *globals.ppUserHistory; pHistory;)
	{
		D2MultiUserHistoryStrc* pNext = pHistory->pNext;
		std::free(pHistory);
		pHistory = pNext;
	}
	*globals.ppUserHistory = nullptr;
	*globals.pnUserHistoryCount = 0;
}

// The composite unit of the fake channel users is their unit flags
struct D2WinCompositeMock
{
	static inline std::map<std::tuple<int, int, BOOL>, std::string> titles;

	static int __stdcall GetUnitFlags(D2CompositeUnitStrc* pCompositeUnit)
	{
		return (int)reinterpret_cast<uintptr_t>(pCompositeUnit);
	}

	static const char* __stdcall GetPlayerTitle(int nClass, int nTitle, BOOL bExpansion)
	{
		std::string& szTitle = titles[{ nClass, nTitle, bExpansion }];
		szTitle = "Title" + std::to_string(nClass) + "/" + std::to_string(nTitle) + "/" + std::to_string(bExpansion);
		return szTitle.c_str();
	}
};

template<class Fixture>
struct D2MultiUserFixture : D2MultiFixture<Fixture>
{
	D2MultiUserFixture()
	{
		this->hooks.hook("D2Win.dll", 10155, reinterpret_cast<void*>(&D2Win_10155), reinterpret_cast<const void*>(&D2WinCompositeMock::GetUnitFlags), false);
		this->hooks.hook("D2Win.dll", 10160, reinterpret_cast<void*>(&D2Win_10160_GetPlayerTitle), reinterpret_cast<const void*>(&D2WinCompositeMock::GetPlayerTitle), false);
		for (const UserGlobals* pGlobals : { &moo_user_globals(), &original_user_globals() })
		{
			*pGlobals->ppChannelUsers = nullptr;
			*pGlobals->ppUserHistory = nullptr;
			*pGlobals->pnUserHistoryCount = 0;
		}
	}

	~D2MultiUserFixture()
	{
		for (const UserGlobals* pGlobals : { &moo_user_globals(), &original_user_globals() })
		{
			*pGlobals->ppChannelUsers = nullptr;
			free_history(*pGlobals);
		}
	}
};
}


TEST_SUITE("D2MultiUserTests")
{
	TEST_CASE_FIXTURE(D2MultiUserFixture<NoOpFixture>, "D2Multi.0x6F9ADCE0")
	{
		const auto [sut, original] = make_d2multi_pair(COMCALLBACK_AddUserHistory, 0x6F9ADCE0);

		// The same account with another character only updates the character name
		const std::pair<const char*, const char*> users[] = {
			{ "Hero*Account", "Hero" },
			{ "*Other", "" },
			{ "Sorc*Third", "Sorc" },
			{ "Paladin*Account", "Paladin" },
			{ "*account", "" },
			{ "Necro*Other", "Necro" },
		};

		for (const auto& [szUserName, szCharacterName] : users)
		{
			CAPTURE(szUserName);
			sut(szUserName, szCharacterName);
			original(szUserName, szCharacterName);
			CHECK_EQ(read_history(moo_user_globals()), read_history(original_user_globals()));
			CHECK_EQ(*moo_user_globals().pnUserHistoryCount, *original_user_globals().pnUserHistoryCount);
		}

		const History expected = { { "Hero*Account", "Paladin" }, { "*Other", "Necro" }, { "Sorc*Third", "Sorc" }, { "*account", "" } };
		CHECK_EQ(read_history(moo_user_globals()), expected);

		SUBCASE("The oldest user is removed when the history is full")
		{
			for (int i = 0; i < COMCALLBACK_MAX_USER_HISTORY + 3; ++i)
			{
				const std::string szUserName = "C" + std::to_string(i) + "*A" + std::to_string(i);
				const std::string szCharacterName = "C" + std::to_string(i);
				sut(szUserName.c_str(), szCharacterName.c_str());
				original(szUserName.c_str(), szCharacterName.c_str());
			}

			const History moo_history = read_history(moo_user_globals());
			CHECK_EQ(moo_history.size(), COMCALLBACK_MAX_USER_HISTORY);
			CHECK_MESSAGE(moo_history == read_history(original_user_globals()), "Comparing the full histories");
			CHECK_EQ(*moo_user_globals().pnUserHistoryCount, *original_user_globals().pnUserHistoryCount);
		}
	}

	TEST_CASE_FIXTURE(D2MultiUserFixture<NoOpFixture>, "D2Multi.0x6F9ADE40")
	{
		const auto [sut, original] = make_d2multi_pair(COMCALLBACK_GetUserDisplayName, 0x6F9ADE40);
		const auto [moo_add_history, original_add_history] = make_d2multi_pair(COMCALLBACK_AddUserHistory, 0x6F9ADCE0);

		for (const auto& add_history : { moo_add_history, original_add_history })
		{
			add_history("Hero*Account", "Hero");
			add_history("*Classic", "");
			add_history("Sorc*Ladder", "Sorc");
			add_history("Druid*Expansion", "Druid");
			add_history("Barb*Hardcore", "Barb");
		}

		// Channel users, with their unit flags as composite unit
		const auto unit_flags = [](bool bLow, bool bHigh, bool bHardcore, bool bExpansion)
		{
			return reinterpret_cast<D2CompositeUnitStrc*>((uintptr_t)((bLow << 6) | (bHigh << 7) | (bHardcore << 5) | (bExpansion << 12)));
		};
		D2MultiChannelUserStrc channelUsers[5];
		std::memset(channelUsers, 0, sizeof(channelUsers));
		const std::tuple<const char*, uint8_t, D2CompositeUnitStrc*> userData[] = {
			{ "Hero*Account", 3, unit_flags(true, false, false, false) },
			{ "Sorc*Ladder", 1, unit_flags(false, true, false, true) },
			{ "Druid*Expansion", 5, unit_flags(true, true, false, true) },
			{ "Barb*Hardcore", 4, unit_flags(true, true, true, false) },
			{ "*Classic", 7, unit_flags(false, false, true, true) },
		};
		for (size_t i = 0; i < std::size(userData); ++i)
		{
			std::strcpy(channelUsers[i].szUserName, std::get<0>(userData[i]));
			channelUsers[i].nClass = std::get<1>(userData[i]);
			channelUsers[i].pCompositeUnit = std::get<2>(userData[i]);
			channelUsers[i].pNext = i + 1 < std::size(userData) ? &channelUsers[i + 1] : nullptr;
		}

		const char* szUserNames[] = {
			"Hero*Account", "HERO*account", "Sorc*Ladder", "Druid*Expansion", "Barb*Hardcore", "*Classic",
			"Unknown*User", "*Unknown", "NoSeparator", "user@Azeroth*Account", "Char*user@Azeroth", "@*", "",
		};

		for (const bool bWithChannelUsers : { false, true })
		{
			*moo_user_globals().ppChannelUsers = bWithChannelUsers ? channelUsers : nullptr;
			*original_user_globals().ppChannelUsers = bWithChannelUsers ? channelUsers : nullptr;

			for (const char* szUserName : szUserNames)
			{
				CAPTURE(bWithChannelUsers);
				CAPTURE(szUserName);
				char moo_title[256] = {}, original_title[256] = {};
				char moo_name[256] = {}, original_name[256] = {};
				std::memset(moo_title, 'x', 16);
				std::memset(original_title, 'x', 16);

				sut(szUserName, moo_title, moo_name);
				original(szUserName, original_title, original_name);

				CHECK_EQ(std::string(moo_title), std::string(original_title));
				CHECK_EQ(std::string(moo_name), std::string(original_name));
			}
		}

		char szTitle[256] = {}, szName[256] = {};
		sut("Druid*Expansion", szTitle, szName);
		CHECK_EQ(std::string(szTitle), "Title5/3/1");
		CHECK_EQ(std::string(szName), "Druid");
	}
}
