#include <doctest.h>

#include <cstring>
#include <string>
#include <tuple>
#include <vector>

#include <BnClient.h>
#include <D2Config.h>

#include <ChatDlg.h>
#include <Gate.h>

#include "D2MultiTestFixtures.h"


extern D2MultiGameListEntryStrc gaGameList_6F9D11C0[GATE_MAX_GAMES];
extern int32_t gnGameListCount_6F9DFA4C;
extern BnClientInterface* gptComInt_6F9C19BC;
extern D2ConfigStrc* gpConfig_6F9C26F0;


namespace
{
struct GateGlobals
{
	D2MultiGameListEntryStrc* pGameList;
	int32_t* pnGameListCount;
	BnClientInterface** ppComInt;
	D2ConfigStrc** ppConfig;
};

const GateGlobals& moo_gate_globals()
{
	static const GateGlobals globals = { gaGameList_6F9D11C0, &gnGameListCount_6F9DFA4C, &gptComInt_6F9C19BC, &gpConfig_6F9C26F0 };
	return globals;
}

const GateGlobals& original_gate_globals()
{
	static const GateGlobals globals = {
		original_d2multi_global<D2MultiGameListEntryStrc>(0x6F9D11C0),
		original_d2multi_global<int32_t>(0x6F9DFA4C),
		original_d2multi_global<BnClientInterface*>(0x6F9C19BC),
		original_d2multi_global<D2ConfigStrc*>(0x6F9C26F0),
	};
	return globals;
}

std::vector<uint8_t> entry_bytes(const D2MultiGameListEntryStrc* pEntries, int32_t nCount)
{
	const auto pBytes = reinterpret_cast<const uint8_t*>(pEntries);
	return std::vector<uint8_t>(pBytes, pBytes + nCount * sizeof(D2MultiGameListEntryStrc));
}

// Bnclient interface returning a prepared game list
struct FakeGameList
{
	struct Request
	{
		std::string szGameName;
		std::string szPassword;
		uint32_t nFlags;
		uint32_t nFilter;

		bool operator==(const Request& other) const { return szGameName == other.szGameName && szPassword == other.szPassword && nFlags == other.nFlags && nFilter == other.nFilter; }
	};

	static inline std::vector<Request> requests;
	static inline std::vector<uint8_t> response;

	static void* __fastcall GetGamesList(const char* szGameName, const char* szPassword, uint32_t nFlags, uint32_t nFilter)
	{
		requests.push_back({ szGameName ? szGameName : "(null)", szPassword ? szPassword : "(null)", nFlags, nFilter });
		return response.empty() ? nullptr : response.data();
	}

	static BnClientInterface* table()
	{
		static BnClientInterface tInterface = []()
		{
			BnClientInterface tTable;
			std::memset(&tTable, 0, sizeof(tTable));
			tTable.GetGamesList = &GetGamesList;
			return tTable;
		}();
		return &tInterface;
	}

	// Count, then each game: 12 unknown bytes, IP address, 16 unknown bytes, name, password and statstring
	static void set_games(int32_t nCount, const std::vector<std::tuple<uint32_t, std::string, std::string, std::string>>& games)
	{
		response.clear();
		auto u32 = [](uint32_t nValue)
		{
			for (int i = 0; i < 4; ++i)
			{
				response.push_back((uint8_t)(nValue >> (8 * i)));
			}
		};
		u32((uint32_t)nCount);
		for (const auto& [nIpAddress, szName, szPassword, szStatstring] : games)
		{
			for (int i = 0; i < 3; ++i) u32(0xA0A0A0A0 + i);
			u32(nIpAddress);
			for (int i = 0; i < 4; ++i) u32(0xB0B0B0B0 + i);
			for (const std::string* pString : { &szName, &szPassword, &szStatstring })
			{
				response.insert(response.end(), pString->begin(), pString->end());
				response.push_back(0);
			}
		}
		response.resize(response.size() + 16, 0);
	}
};

template<class Fixture>
struct D2MultiGateFixture : D2MultiFixture<Fixture>
{
	D2ConfigStrc tConfig;

	D2MultiGateFixture()
	{
		std::memset(&tConfig, 0, sizeof(tConfig));
		for (const GateGlobals* pGlobals : { &moo_gate_globals(), &original_gate_globals() })
		{
			*pGlobals->pnGameListCount = 0;
			*pGlobals->ppComInt = FakeGameList::table();
			*pGlobals->ppConfig = &tConfig;
		}
		FakeGameList::requests.clear();
		FakeGameList::response.clear();
	}

	~D2MultiGateFixture()
	{
		for (const GateGlobals* pGlobals : { &moo_gate_globals(), &original_gate_globals() })
		{
			*pGlobals->pnGameListCount = 0;
			*pGlobals->ppComInt = nullptr;
			*pGlobals->ppConfig = nullptr;
		}
		FakeGameList::requests.clear();
		FakeGameList::response.clear();
	}
};
}


TEST_SUITE("D2MultiGateTests")
{
	TEST_CASE_FIXTURE(D2MultiGateFixture<NoOpFixture>, "D2Multi.0x6F9AF5D0")
	{
		const auto [sut, original] = make_d2multi_pair(GATE_AddMCPGame, 0x6F9AF5D0);

		const std::tuple<uint16_t, uint16_t, const char*, const char*> games[] = {
			{ 1, 3, "Game1", "Description" },
			{ 2, 8, "Another game", "" },
			{ 1, 4, "Same token", "Ignored" },
			{ 0x1234, 0, "", "Empty name" },
			{ 0xFFFF, 1, "LongNameGame123", "A description of 31 characters." },
		};

		for (const auto& [nToken, nPlayers, szName, szDescription] : games)
		{
			CAPTURE(szName);
			D2MultiMCPGameListStrc tGame;
			std::memset(&tGame, 0xCC, sizeof(tGame));
			tGame.nType = 0;
			tGame.nGameToken = nToken;
			tGame.nPlayers = nPlayers;
			std::strcpy(tGame.szGameName, szName);
			std::strcpy(tGame.szGameDescription, szDescription);

			sut(&tGame);
			original(&tGame);

			REQUIRE_EQ(*moo_gate_globals().pnGameListCount, *original_gate_globals().pnGameListCount);
			// The first byte of the entries is not written
			std::vector<uint8_t> moo_entries = entry_bytes(moo_gate_globals().pGameList, *moo_gate_globals().pnGameListCount);
			std::vector<uint8_t> original_entries = entry_bytes(original_gate_globals().pGameList, *original_gate_globals().pnGameListCount);
			for (int32_t i = 0; i < *moo_gate_globals().pnGameListCount; ++i)
			{
				moo_entries[i * sizeof(D2MultiGameListEntryStrc)] = 0;
				original_entries[i * sizeof(D2MultiGameListEntryStrc)] = 0;
			}
			CHECK_MESSAGE(moo_entries == original_entries, "Comparing the game list");
		}

		CHECK_EQ(*moo_gate_globals().pnGameListCount, 4);
	}

	TEST_CASE_FIXTURE(D2MultiGateFixture<NoOpFixture>, "D2Multi.0x6F9B1770")
	{
		const auto [sut, original] = make_d2multi_pair(GATE_FindBattleNetGame, 0x6F9B1770);

		struct Response
		{
			const char* szName;
			int32_t nCount;
			std::vector<std::tuple<uint32_t, std::string, std::string, std::string>> games;
		};

		std::vector<Response> responses = {
			{ "No list", -1, {} },
			{ "Empty list", 0, {} },
			{ "Negative count", -3, { { 0x0100007F, "Game", "", "0Normal game" } } },
		};
		for (char nDifficulty = '0'; nDifficulty <= '6'; ++nDifficulty)
		{
			responses.push_back({ "Difficulty", 1, { { 0x0A00000A, "Game", "password", std::string(1, nDifficulty) + "Description" } } });
		}
		responses.push_back({ "Several games", 2, { { 0x0B00000B, "First", "", "1First game" }, { 0x0C00000C, "Second", "", "0Second game" } } });

		// Classic and expansion, softcore and hardcore, with each difficulty reached
		std::vector<uint16_t> characterFlags;
		for (const uint16_t nMode : { 0x00, 0x04, 0x20, 0x24 })
		{
			for (const uint16_t nProgression : { 0x000, 0x300, 0x400, 0x500, 0x700, 0x800, 0x900, 0xA00, 0xF00 })
			{
				characterFlags.push_back(nMode | nProgression);
			}
		}

		for (const uint16_t nCharacterFlags : characterFlags)
		{
			tConfig.unpackedCTemp.nCharacterSaveFlags = nCharacterFlags;
			for (const Response& response : responses)
			{
				CAPTURE(nCharacterFlags);
				CAPTURE(response.szName);
				CAPTURE(response.games.empty() ? std::string() : std::get<3>(response.games[0]));

				std::vector<std::tuple<int32_t, std::vector<uint8_t>, std::vector<FakeGameList::Request>>> results;
				for (const auto& find : { sut, original })
				{
					if (response.nCount == -1)
					{
						FakeGameList::response.clear();
					}
					else
					{
						FakeGameList::set_games(response.nCount, response.games);
					}
					FakeGameList::requests.clear();

					D2MultiGameListEntryStrc tGame;
					std::memset(&tGame, 0xCC, sizeof(tGame));
					const int32_t nResult = find("GameName", "Password", &tGame);
					results.emplace_back(nResult, entry_bytes(&tGame, 1), FakeGameList::requests);
				}

				CHECK_EQ(std::get<0>(results[0]), std::get<0>(results[1]));
				CHECK_MESSAGE(std::get<1>(results[0]) == std::get<1>(results[1]), "Comparing the game entries");
				CHECK_MESSAGE(std::get<2>(results[0]) == std::get<2>(results[1]), "Comparing the requests");
			}
		}

		// A softcore character in normal can only join normal games
		tConfig.unpackedCTemp.nCharacterSaveFlags = 0;
		FakeGameList::set_games(1, { { 0x0A00000A, "Game", "", "1Nightmare" } });
		D2MultiGameListEntryStrc tGame = {};
		CHECK_EQ(sut("Game", "", &tGame), 1);
		FakeGameList::set_games(1, { { 0x0A00000A, "Game", "", "2Hell" } });
		CHECK_EQ(sut("Game", "", &tGame), 0);
	}
}
