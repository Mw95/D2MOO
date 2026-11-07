#include <doctest.h>

#include <cstring>
#include <vector>

#include "D2MCPClientTestFixtures.h"
#include "D2MCPClientVisitorDefinitions.h"


namespace
{
struct ConnectResult
{
	bool bThreadCreated = false;
	DWORD nExitCode = 0;
	bool bSameThreadOnSecondCall = false;
	bool bThreadMatchesGetter = false;
	uint32_t nLastError = 0;
	std::vector<McpFogMock::CreateCall> create_calls;
	std::vector<FClientConnection*> start_calls;
	std::vector<McpFogMock::SentMessage> sent_raw;
	std::vector<McpFogMock::SentMessage> sent;
	std::vector<FClientConnection*> destroy_calls;
	bool bCallbackIsDispatchConnectionMessage = false;
	FClientConnection* pConnectionAfterThread = nullptr;
	// After D2MCPClientCloseMCP
	std::vector<FClientConnection*> close_calls;
	FClientConnection* pConnectionAfterClose = nullptr;
	HANDLE hThreadAfterClose = nullptr;
};

D2MCPConnectInfoStrc make_connect_info()
{
	D2MCPConnectInfoStrc tConnectInfo = {};
	tConnectInfo.dwMCPCookie = 0x11111111;
	tConnectInfo.dwMCPStatus = 0x22222222;
	tConnectInfo.dwMCPChunk1[0] = 0x33333333;
	tConnectInfo.dwMCPChunk1[1] = 0x44444444;
	tConnectInfo.dwMCPIp = 0x0401A8C0;	// 192.168.1.4
	tConnectInfo.dwMCPPort = 6113;
	for (uint32_t i = 0; i < 12; ++i)
	{
		tConnectInfo.dwMCPChunk2[i] = 0x50505050 + i;
	}
	std::strcpy(tConnectInfo.szBattleNetUniqueName, "UniqueName#2");
	return tConnectInfo;
}

// Connects with the given mock configuration, waits for the connection thread then closes the connection
template<typename Setup>
ConnectResult run_connect(const McpClientApi& api, Setup&& setup)
{
	McpFogMock::reset();
	setup();
	api.D2MCPClientSetLastError(0x5555);

	const D2MCPConnectInfoStrc tConnectInfo = make_connect_info();

	ConnectResult result;
	const HANDLE hThread = api.D2MCPClientConnect(&tConnectInfo);
	result.bThreadCreated = hThread != nullptr;
	REQUIRE(hThread != nullptr);
	REQUIRE_EQ(WaitForSingleObject(hThread, 10000), WAIT_OBJECT_0);
	GetExitCodeThread(hThread, &result.nExitCode);

	result.bSameThreadOnSecondCall = api.D2MCPClientConnect(&tConnectInfo) == hThread;
	result.bThreadMatchesGetter = api.D2MCPClientGetConnectionThread() == hThread;
	result.nLastError = api.D2MCPClientGetLastError();
	result.create_calls = McpFogMock::create_calls;
	result.start_calls = McpFogMock::start_calls;
	result.sent_raw = McpFogMock::sent_raw;
	result.sent = McpFogMock::sent;
	result.destroy_calls = McpFogMock::destroy_calls;
	result.bCallbackIsDispatchConnectionMessage = McpFogMock::pMessageCallback == reinterpret_cast<FClientConnectionMessageCallback>(api.MCP_DispatchConnectionMessage);
	result.pConnectionAfterThread = *api.ppConnection;

	api.D2MCPClientCloseMCP();
	result.close_calls = McpFogMock::close_calls;
	result.pConnectionAfterClose = *api.ppConnection;
	result.hThreadAfterClose = api.D2MCPClientGetConnectionThread();
	return result;
}

template<typename Setup>
ConnectResult compare_connect(Setup&& setup)
{
	std::vector<ConnectResult> results;
	for_each_api([&](const McpClientApi& api) { results.push_back(run_connect(api, setup)); });

	const ConnectResult& moo = results[0];
	const ConnectResult& original = results[1];
	CHECK_EQ(moo.bThreadCreated, original.bThreadCreated);
	CHECK_EQ(moo.nExitCode, original.nExitCode);
	CHECK_EQ(moo.bSameThreadOnSecondCall, original.bSameThreadOnSecondCall);
	CHECK_EQ(moo.bThreadMatchesGetter, original.bThreadMatchesGetter);
	CHECK_EQ(moo.nLastError, original.nLastError);
	CHECK_MESSAGE(moo.create_calls == original.create_calls, "Comparing the ClientCreate calls");
	CHECK_MESSAGE(moo.start_calls == original.start_calls, "Comparing the ClientStart calls");
	CHECK_MESSAGE(moo.sent_raw == original.sent_raw, "Comparing the raw data sent");
	CHECK_MESSAGE(moo.sent == original.sent, "Comparing the messages sent");
	CHECK_MESSAGE(moo.destroy_calls == original.destroy_calls, "Comparing the ClientDestroy calls");
	CHECK_EQ(moo.bCallbackIsDispatchConnectionMessage, original.bCallbackIsDispatchConnectionMessage);
	CHECK_EQ(moo.pConnectionAfterThread, original.pConnectionAfterThread);
	CHECK_MESSAGE(moo.close_calls == original.close_calls, "Comparing the ClientClose calls");
	CHECK_EQ(moo.pConnectionAfterClose, original.pConnectionAfterClose);
	CHECK_EQ(moo.hThreadAfterClose, original.hThreadAfterClose);
	return moo;
}
}


TEST_SUITE("D2MCPClientConnectionTests")
{
	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F17D0 (#10000) / D2MCPClient.0x6F9F1980 (#10001)")
	{
		SUBCASE("The connection could not be established")
		{
			const auto result = compare_connect([] { McpFogMock::pSafeSock = nullptr; });

			CHECK_EQ(result.nExitCode, FALSE);
			CHECK_EQ(result.nLastError, MCPCLIENT_ERROR_CONNECTION_FAILED);
			REQUIRE_EQ(result.create_calls.size(), 1);
			CHECK_EQ(result.create_calls[0].szIpAddress, "192.168.1.4");
			CHECK_EQ(result.create_calls[0].nPort, 6113);
			CHECK_EQ(result.create_calls[0].szName, "clt->mcp");
			CHECK_EQ(result.bCallbackIsDispatchConnectionMessage, true);
			CHECK(result.sent.empty());
			// The connection is kept until D2MCPClientCloseMCP
			CHECK_EQ(result.pConnectionAfterThread, McpFogMock::pMockConnection);
			CHECK_EQ(result.close_calls, std::vector<FClientConnection*>{ McpFogMock::pMockConnection });
			CHECK_EQ(result.pConnectionAfterClose, nullptr);
			CHECK_EQ(result.hThreadAfterClose, nullptr);
		}

		SUBCASE("Socket error")
		{
			const auto result = compare_connect([]
			{
				McpFogMock::pSafeSock = &McpFogMock::tMockSafeSock;
				McpFogMock::nFogError = 3;
			});

			CHECK_EQ(result.nExitCode, FALSE);
			CHECK_EQ(result.nLastError, MCPCLIENT_ERROR_CONNECTION_FAILED);
			CHECK(result.sent_raw.empty());
		}

		SUBCASE("MCP_STARTUP succeeds")
		{
			const auto result = compare_connect([]
			{
				McpFogMock::pSafeSock = &McpFogMock::tMockSafeSock;
				McpFogMock::bAnswerStartup = true;
				McpFogMock::nStartupResult = 0;
			});

			CHECK_EQ(result.nExitCode, TRUE);
			CHECK_EQ(result.nLastError, 0);
			// The protocol byte (1 = MCP) is sent first
			REQUIRE_EQ(result.sent_raw.size(), 1);
			CHECK_EQ(result.sent_raw[0].data, std::vector<uint8_t>{ 1 });

			REQUIRE_EQ(result.sent.size(), 1);
			std::vector<uint8_t> expected = { MCP_STARTUP };
			const D2MCPConnectInfoStrc tConnectInfo = make_connect_info();
			auto append = [&expected](const void* pData, size_t nSize)
			{
				expected.insert(expected.end(), static_cast<const uint8_t*>(pData), static_cast<const uint8_t*>(pData) + nSize);
			};
			append(&tConnectInfo.dwMCPCookie, 4);
			append(&tConnectInfo.dwMCPStatus, 4);
			append(tConnectInfo.dwMCPChunk1, sizeof(tConnectInfo.dwMCPChunk1));
			append(tConnectInfo.dwMCPChunk2, sizeof(tConnectInfo.dwMCPChunk2));
			append(tConnectInfo.szBattleNetUniqueName, std::strlen(tConnectInfo.szBattleNetUniqueName) + 1);
			CHECK_MESSAGE(result.sent[0].data == expected, "Comparing the MCP_STARTUP message");
		}

		SUBCASE("MCP_STARTUP fails")
		{
			const auto result = compare_connect([]
			{
				McpFogMock::pSafeSock = &McpFogMock::tMockSafeSock;
				McpFogMock::bAnswerStartup = true;
				McpFogMock::nStartupResult = 0x0C;
			});

			CHECK_EQ(result.nExitCode, TRUE);
			CHECK_EQ(result.nLastError, 0x0C);
		}

		SUBCASE("MCP_STARTUP cannot be sent")
		{
			const auto result = compare_connect([]
			{
				McpFogMock::pSafeSock = &McpFogMock::tMockSafeSock;
				McpFogMock::send_result = FALSE;
			});

			CHECK_EQ(result.nExitCode, TRUE);
			CHECK_EQ(result.nLastError, MCPCLIENT_ERROR_STARTUP_SEND_FAILED);
		}

		SUBCASE("Disconnected while waiting for MCP_STARTUP")
		{
			const auto result = compare_connect([]
			{
				McpFogMock::pSafeSock = &McpFogMock::tMockSafeSock;
				McpFogMock::bPeerNameResult = FALSE;
			});

			CHECK_EQ(result.nExitCode, TRUE);
			CHECK_EQ(result.nLastError, MCPCLIENT_ERROR_CONNECTION_FAILED);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1980 (#10001) without connection")
	{
		std::vector<std::vector<FClientConnection*>> results;
		for_each_api([&](const McpClientApi& api)
		{
			McpFogMock::close_calls.clear();
			*api.ppConnection = nullptr;
			api.D2MCPClientCloseMCP();
			results.push_back(McpFogMock::close_calls);
		});

		CHECK(results[0].empty());
		CHECK(results[1].empty());
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F19E0 (#10002)")
	{
		struct Case
		{
			FClientConnection* pConnection;
			FSafeSock* pSafeSock;
			BOOL bPeerNameResult;
		};

		const Case cases[] = {
			{ nullptr, nullptr, TRUE },
			{ McpFogMock::pMockConnection, nullptr, TRUE },
			{ McpFogMock::pMockConnection, &McpFogMock::tMockSafeSock, TRUE },
			{ McpFogMock::pMockConnection, &McpFogMock::tMockSafeSock, FALSE },
		};

		for (const Case& testCase : cases)
		{
			std::vector<BOOL> results;
			for_each_api([&](const McpClientApi& api)
			{
				McpFogMock::pSafeSock = testCase.pSafeSock;
				McpFogMock::bPeerNameResult = testCase.bPeerNameResult;
				*api.ppConnection = testCase.pConnection;
				results.push_back(api.D2MCPClientIsConnected());
				*api.ppConnection = nullptr;
			});

			MOO_CHECK_EQ(results[0], results[1], "Comparing D2MCPClientIsConnected");
			CHECK_EQ(results[0], testCase.pConnection && testCase.pSafeSock && testCase.bPeerNameResult);
		}
	}
}
