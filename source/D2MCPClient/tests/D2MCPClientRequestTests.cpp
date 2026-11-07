#include <doctest.h>

#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include <RandomUnsignedInteger.h>

#include "D2MCPClientTestFixtures.h"
#include "D2MCPClientVisitorDefinitions.h"


namespace
{
// Value used for the connection, never dereferenced since the Fog functions are mocked
FClientConnection* const gpFakeConnection = reinterpret_cast<FClientConnection*>(0x13572468);

struct RequestResult
{
	BOOL bResult = FALSE;
	std::vector<McpFogMock::SentMessage> sent;
	uint16_t nPendingRequestId = 0;
	uint32_t nLastError = 0;
	uint32_t nGameToken = 0;
	BOOL bCharCreateReceived = FALSE;
};

// Calls a request on one implementation, with a known state before the call
RequestResult run_request(const McpClientApi& api, const std::function<BOOL(const McpClientApi&)>& request)
{
	*api.ppConnection = gpFakeConnection;
	*api.pPendingRequestId = 0xBEEF;
	*api.pGameToken = 0xCAFEBABE;
	api.D2MCPClientSetLastError(0x1234);
	api.D2MCPClientSetCharCreateReceived(TRUE);
	McpFogMock::sent.clear();

	RequestResult result;
	result.bResult = request(api);
	result.sent = McpFogMock::sent;
	result.nPendingRequestId = *api.pPendingRequestId;
	result.nLastError = api.D2MCPClientGetLastError();
	result.nGameToken = *api.pGameToken;
	result.bCharCreateReceived = api.D2MCPClientGetCharCreateReceived();

	*api.ppConnection = nullptr;
	return result;
}

// Runs the request on both implementations, compares everything observable and returns the D2MOO result
RequestResult compare_request(const std::function<BOOL(const McpClientApi&)>& request)
{
	std::vector<RequestResult> results;
	for_each_api([&](const McpClientApi& api) { results.push_back(run_request(api, request)); });

	const RequestResult& moo = results[0];
	const RequestResult& original = results[1];
	MOO_CHECK_EQ(moo.bResult, original.bResult, "Comparing the return values");
	MOO_CHECK_EQ(moo.nPendingRequestId, original.nPendingRequestId, "Comparing the pending request id");
	MOO_CHECK_EQ(moo.nLastError, original.nLastError, "Comparing the last error");
	MOO_CHECK_EQ(moo.nGameToken, original.nGameToken, "Comparing the game token");
	MOO_CHECK_EQ(moo.bCharCreateReceived, original.bCharCreateReceived, "Comparing the char create received flag");

	REQUIRE_EQ(moo.sent.size(), original.sent.size());
	for (size_t i = 0; i < moo.sent.size(); ++i)
	{
		CHECK_EQ(moo.sent[i].pConnection, original.sent[i].pConnection);
		CHECK_MESSAGE(moo.sent[i].data == original.sent[i].data, "Comparing the sent message bytes");
	}

	return moo;
}

std::vector<uint8_t> bytes(std::initializer_list<int> values)
{
	return std::vector<uint8_t>(values.begin(), values.end());
}

std::vector<uint8_t> concat(std::vector<uint8_t> data, const std::string& szString)
{
	data.insert(data.end(), szString.begin(), szString.end());
	data.push_back(0);
	return data;
}

void check_single_message(const RequestResult& result, const std::vector<uint8_t>& expected)
{
	REQUIRE_EQ(result.sent.size(), 1);
	CHECK_EQ(result.sent[0].pConnection, gpFakeConnection);
	CHECK_MESSAGE(result.sent[0].data == expected, "Comparing the sent message with the expected one");
}
}


TEST_SUITE("D2MCPClientRequestTests")
{
	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1CA0 (#10008)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientCharCreate("Diablo", 3, 0x24); });

		check_single_message(result, concat(bytes({ MCP_CHARCREATE, 3, 0, 0, 0, 0x24, 0 }), "Diablo"));
		CHECK_EQ(result.bResult, TRUE);
		CHECK_EQ(result.nLastError, MCPCLIENT_ERROR_NONE);
		// The "char create received" flag is reset
		CHECK_EQ(result.bCharCreateReceived, FALSE);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1CC0 (#10009)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientCharLogon("Baal"); });

		check_single_message(result, concat(bytes({ MCP_CHARLOGON }), "Baal"));
		CHECK_EQ(result.nLastError, MCPCLIENT_ERROR_NONE);
		CHECK_EQ(result.nPendingRequestId, 0xBEEF);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2180 (#10004)")
	{
		D2MCPCreateGameInfoStrc tCreateGameInfo = {};
		std::strcpy(tCreateGameInfo.szGameName, "Game-1");
		std::strcpy(tCreateGameInfo.szGamePassword, "pw");
		std::strcpy(tCreateGameInfo.szGameDescription, "A description");
		tCreateGameInfo.dwFlags = 0x2000;
		tCreateGameInfo.nUnk0x44 = 0x11;
		tCreateGameInfo.nLevelDifference = 0xFF;
		tCreateGameInfo.nMaxPlayers = 8;

		const uint16_t nRequestId = (uint16_t)random_unsigned_integer(0, 0xFFFF);
		const auto result = compare_request([&](const McpClientApi& api) { return api.D2MCPClientCreateGame(&tCreateGameInfo, nRequestId); });

		auto expected = bytes({ MCP_CREATEGAME, nRequestId & 0xFF, nRequestId >> 8, 0x00, 0x20, 0, 0, 0x11, 0xFF, 8 });
		expected = concat(concat(concat(expected, "Game-1"), "pw"), "A description");
		check_single_message(result, expected);
		CHECK_EQ(result.nPendingRequestId, nRequestId);
		// The game token is reset
		CHECK_EQ(result.nGameToken, 0);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2300 (#10005)")
	{
		SUBCASE("With a password")
		{
			const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientJoinGame("Game", "secret", 0x1234); });
			check_single_message(result, concat(concat(bytes({ MCP_JOINGAME, 0x34, 0x12 }), "Game"), "secret"));
			CHECK_EQ(result.nPendingRequestId, 0x1234);
		}

		SUBCASE("Without a password")
		{
			const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientJoinGame("Game", "", 7); });
			check_single_message(result, concat(concat(bytes({ MCP_JOINGAME, 7, 0 }), "Game"), ""));
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2400 (#10006)")
	{
		D2MCPGameListRequestStrc tRequest = {};
		std::strcpy(tRequest.szSearchString, "baal");
		tRequest.dwFlags = 0x800;

		const auto result = compare_request([&](const McpClientApi& api) { return api.D2MCPClientRequestGameList(&tRequest, 0x4321); });
		check_single_message(result, concat(bytes({ MCP_GAMELIST, 0x21, 0x43, 0x00, 0x08, 0, 0 }), "baal"));
		CHECK_EQ(result.nPendingRequestId, 0x4321);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2490 (#10007)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientRequestGameInfo("Some game", 99); });
		check_single_message(result, concat(bytes({ MCP_GAMEINFO, 99, 0 }), "Some game"));
		CHECK_EQ(result.nPendingRequestId, 99);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2520 (#10013)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientSendMsg08("message 8", 0x0808); });
		check_single_message(result, concat(bytes({ MCP_MSG_08, 0x08, 0x08 }), "message 8"));
		CHECK_EQ(result.nPendingRequestId, 0x0808);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F25D0 (#10014)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientSendMsg09("message 9", 0x0909); });
		check_single_message(result, concat(bytes({ MCP_MSG_09, 0x09, 0x09 }), "message 9"));
		CHECK_EQ(result.nPendingRequestId, 0x0909);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2680 (#10021)")
	{
		SUBCASE("Regular name")
		{
			const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientCharDelete("Old", 0x0A0A); });
			check_single_message(result, concat(bytes({ MCP_CHARDELETE, 0x0A, 0x0A }), "Old"));
			CHECK_EQ(result.nPendingRequestId, 0x0A0A);
		}

		SUBCASE("Name longer than the message buffer is truncated")
		{
			const std::string szLongName(2000, 'n');
			compare_request([&](const McpClientApi& api) { return api.D2MCPClientCharDelete(szLongName.c_str(), 1); });
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F26E0 (#10062)")
	{
		SUBCASE("Regular name")
		{
			const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientCharUpgrade("Classic"); });
			check_single_message(result, concat(bytes({ MCP_CHARUPGRADE }), "Classic"));
		}

		SUBCASE("Name longer than the message buffer is truncated")
		{
			const std::string szLongName(2000, 'u');
			compare_request([&](const McpClientApi& api) { return api.D2MCPClientCharUpgrade(szLongName.c_str()); });
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2730 (#10022)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientSendMsg0B("first", "second"); });
		check_single_message(result, concat(concat(bytes({ MCP_MSG_0B }), "first"), "second"));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2820 (#10023)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientSendMsg0C("string"); });
		check_single_message(result, concat(bytes({ MCP_MSG_0C }), "string"));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F28C0 (#10024)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientSendMsg0D(); });
		check_single_message(result, bytes({ MCP_MSG_0D }));
		CHECK_EQ(result.nLastError, MCPCLIENT_ERROR_NONE);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F28F0 (#10025)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientSendMsg0F(); });
		check_single_message(result, bytes({ MCP_MSG_0F }));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2920 (#10026)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientSendMsg10(); });
		check_single_message(result, bytes({ MCP_MSG_10 }));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2950 (#10027)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientRequestLadderData(0x13, 0x0102); });
		check_single_message(result, bytes({ MCP_REQUESTLADDERDATA, 0x13, 0x02, 0x01 }));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2990 (#10049)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientRequestMotd(); });
		check_single_message(result, bytes({ MCP_MOTD }));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F29C0 (#10054)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientCancelGameCreate(); });
		check_single_message(result, bytes({ MCP_CANCELGAMECREATE }));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F29F0 (#10056)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientRequestCharList(); });
		check_single_message(result, bytes({ MCP_CHARLIST2, 8, 0, 0, 0 }));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F2A20 (#10059)")
	{
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientCharRank("Ranked", 0x11223344, 0x55667788); });
		check_single_message(result, concat(bytes({ MCP_CHARRANK, 0x44, 0x33, 0x22, 0x11, 0x88, 0x77, 0x66, 0x55 }), "Ranked"));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "Requests return the result of the Fog send function")
	{
		McpFogMock::send_result = FALSE;
		const auto result = compare_request([](const McpClientApi& api) { return api.D2MCPClientRequestMotd(); });
		CHECK_EQ(result.bResult, FALSE);

		McpFogMock::send_result = 2;
		const auto result2 = compare_request([](const McpClientApi& api) { return api.D2MCPClientCharLogon("x"); });
		CHECK_EQ(result2.bResult, 2);
	}
}
