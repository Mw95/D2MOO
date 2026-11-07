#include <doctest.h>

#include <cstring>
#include <vector>

#include <RandomUnsignedInteger.h>

#include "D2MCPClientTestFixtures.h"
#include "D2MCPClientVisitorDefinitions.h"


namespace
{
// Sets the flag with `set` then reads it back with `get`, on both implementations
void check_flag_round_trip(SetFlag set, GetFlag get)
{
	for (const BOOL bValue : { TRUE, FALSE, static_cast<BOOL>(random_unsigned_integer(2)), FALSE })
	{
		std::vector<BOOL> results;
		for_each_api([&](const McpClientApi& api)
		{
			(api.*set)(bValue);
			results.push_back((api.*get)());
		});

		MOO_CHECK_EQ(results[0], results[1], "Comparing the flag read back");
		CHECK_EQ(results[0], bValue);
	}
}
}


TEST_SUITE("D2MCPClientStateTests")
{
	TEST_CASE("D2MCPClient.0x6F9F1AB0 (#10046) / D2MCPClient.0x6F9F1AA0 (#10047)")
	{
		for (const uint32_t nError : { 0u, 2u, 51u, random_unsigned_integer(), 0u })
		{
			std::vector<uint32_t> results;
			for_each_api([&](const McpClientApi& api)
			{
				api.D2MCPClientSetLastError(nError);
				results.push_back(api.D2MCPClientGetLastError());
			});

			MOO_CHECK_EQ(results[0], results[1], "Comparing the last error");
			CHECK_EQ(results[0], nError);
		}
	}

	TEST_CASE("D2MCPClient.0x6F9F1CD0 (#10050) / D2MCPClient.0x6F9F1CE0 (#10051)")
	{
		for (const uint32_t nPosition : { 0u, 1u, random_unsigned_integer(), 0u })
		{
			std::vector<uint32_t> results;
			for_each_api([&](const McpClientApi& api)
			{
				api.D2MCPClientSetCreateQueuePosition(nPosition);
				results.push_back(api.D2MCPClientGetCreateQueuePosition());
			});

			MOO_CHECK_EQ(results[0], results[1], "Comparing the queue position");
			CHECK_EQ(results[0], nPosition);
		}
	}

	TEST_CASE("D2MCPClient.0x6F9F1AC0 (#10029) / D2MCPClient.0x6F9F1AD0 (#10028)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetCharCreateReceived, &McpClientApi::D2MCPClientGetCharCreateReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1AE0 (#10031) / D2MCPClient.0x6F9F1AF0 (#10030)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetCharLogonReceived, &McpClientApi::D2MCPClientGetCharLogonReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1B00 (#10033) / D2MCPClient.0x6F9F1B10 (#10032)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetCharDeleteReceived, &McpClientApi::D2MCPClientGetCharDeleteReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1B50 (#10035) / D2MCPClient.0x6F9F1B40 (#10034)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetMsg0BReceived, &McpClientApi::D2MCPClientGetMsg0BReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1B60 (#10037) / D2MCPClient.0x6F9F1B70 (#10036)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetMsg0CReceived, &McpClientApi::D2MCPClientGetMsg0CReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1C30 (#10040) / D2MCPClient.0x6F9F1C40 (#10041)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetMsg0DReceived, &McpClientApi::D2MCPClientGetMsg0DReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1C50 (#10042) / D2MCPClient.0x6F9F1C60 (#10043)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetMsg0FReceived, &McpClientApi::D2MCPClientGetMsg0FReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1C70 (#10044) / D2MCPClient.0x6F9F1C80 (#10045)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetMsg10Received, &McpClientApi::D2MCPClientGetMsg10Received);
	}

	TEST_CASE("D2MCPClient.0x6F9F1CF0 (#10052) / D2MCPClient.0x6F9F1D00 (#10053)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetCreateQueueReceived, &McpClientApi::D2MCPClientGetCreateQueueReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1B20 (#10061) / D2MCPClient.0x6F9F1B30 (#10060)")
	{
		check_flag_round_trip(&McpClientApi::D2MCPClientSetCharUpgradeReceived, &McpClientApi::D2MCPClientGetCharUpgradeReceived);
	}

	TEST_CASE("D2MCPClient.0x6F9F1B80 (#10038) / D2MCPClient.0x6F9F1BC0 (#10039)")
	{
		struct Result
		{
			BOOL bReceived;
			char szString1[36];
			char szString2[28];
		};

		SUBCASE("Strings that fit the buffers")
		{
			for (const BOOL bReceived : { TRUE, FALSE })
			{
				std::vector<Result> results;
				for_each_api([&](const McpClientApi& api)
				{
					Result result = {};
					api.D2MCPClientSetMsg0EStrings(bReceived, "First string", "Second");
					result.bReceived = api.D2MCPClientGetMsg0EStrings(result.szString1, result.szString2);
					results.push_back(result);
				});

				MOO_CHECK_EQ(results[0].bReceived, results[1].bReceived, "Comparing the received flag");
				MOO_CHECK_EQ(results[0].szString1, results[1].szString1, "Comparing szString1");
				MOO_CHECK_EQ(results[0].szString2, results[1].szString2, "Comparing szString2");
				CHECK_EQ(results[0].bReceived, bReceived);
				CHECK_EQ(std::strcmp(results[0].szString1, "First string"), 0);
				CHECK_EQ(std::strcmp(results[0].szString2, "Second"), 0);
			}
		}

		SUBCASE("Longest strings")
		{
			const char szString1[] = "01234567890123456789012345678901234";	// 35 characters
			const char szString2[] = "012345678901234567890123456";			// 27 characters

			std::vector<Result> results;
			for_each_api([&](const McpClientApi& api)
			{
				Result result = {};
				api.D2MCPClientSetMsg0EStrings(TRUE, szString1, szString2);
				result.bReceived = api.D2MCPClientGetMsg0EStrings(result.szString1, result.szString2);
				results.push_back(result);
			});

			MOO_CHECK_EQ(results[0].szString1, results[1].szString1, "Comparing szString1");
			MOO_CHECK_EQ(results[0].szString2, results[1].szString2, "Comparing szString2");
			CHECK_EQ(std::strcmp(results[0].szString1, szString1), 0);
			CHECK_EQ(std::strcmp(results[0].szString2, szString2), 0);
		}
	}

	TEST_CASE("D2MCPClient.0x6F9F1C00 (#10019) / D2MCPClient.0x6F9F1C10 (#10020)")
	{
		std::vector<D2MCPGameInfoStrc*> results;
		for_each_api([&](const McpClientApi& api)
		{
			D2MCPGameInfoStrc* pGameInfo = api.D2MCPClientGetGameInfo();
			REQUIRE(pGameInfo != nullptr);
			// The pointer to the global does not change
			CHECK_EQ(api.D2MCPClientGetGameInfo(), pGameInfo);

			std::memset(pGameInfo, 0xA5, sizeof(*pGameInfo));
			api.D2MCPClientClearGameInfo();
			results.push_back(pGameInfo);
		});

		MOO_CHECK_EQ(results[0], results[1], "Comparing the game info after D2MCPClientClearGameInfo");

		const D2MCPGameInfoStrc tEmpty = {};
		CHECK_EQ(std::memcmp(results[0], &tEmpty, sizeof(tEmpty)), 0);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1D10 (#10057) / D2MCPClient.0x6F9F1D20 (#10058)")
	{
		SUBCASE("MCP_CHARLIST2")
		{
			// Header, then for each character: DWORD, name, stats string.
			// maxCharsAllowed is the number of characters, since the original game walks that many entries without checking the size.
			std::vector<uint8_t> message = { MCP_CHARLIST2, 2, 0, 0, 0, 2, 0, 2, 0 };
			for (const char* szString : { "\x01\x02\x03\x04" "Alice", "\x84\x80stats", "\x05\x06\x07\x08" "Bob", "\x84\x80" })
			{
				message.insert(message.end(), szString, szString + std::strlen(szString) + 1);
			}

			std::vector<std::vector<uint8_t>> results;
			for_each_api([&](const McpClientApi& api)
			{
				api.D2MCPClientSetCharacterList(message.data(), (uint32_t)message.size());
				D2MCPCharListStrc* pCharList = api.D2MCPClientGetCharacterList();
				REQUIRE(pCharList != nullptr);
				// The message is copied
				CHECK_NE(reinterpret_cast<uint8_t*>(pCharList), message.data());

				const auto pBytes = reinterpret_cast<const uint8_t*>(pCharList);
				results.emplace_back(pBytes, pBytes + message.size());
			});

			CHECK_MESSAGE(results[0] == results[1], "Comparing the stored character list");
			CHECK_EQ(results[0], message);

			std::vector<D2MCPCharListStrc*> pHeaders;
			for_each_api([&](const McpClientApi& api) { pHeaders.push_back(api.D2MCPClientGetCharacterList()); });
			MOO_CHECK_EQ(pHeaders[0], pHeaders[1], "Comparing the character list header");
		}

		SUBCASE("MCP_CHARLIST")
		{
			const std::vector<uint8_t> message = { MCP_CHARLIST, 1, 0, 0, 0, 1, 0, 8, 0, 'x', 0 };

			std::vector<std::vector<uint8_t>> results;
			for_each_api([&](const McpClientApi& api)
			{
				api.D2MCPClientSetCharacterList(message.data(), (uint32_t)message.size());
				const auto pBytes = reinterpret_cast<const uint8_t*>(api.D2MCPClientGetCharacterList());
				REQUIRE(pBytes != nullptr);
				results.emplace_back(pBytes, pBytes + message.size());
			});

			CHECK_MESSAGE(results[0] == results[1], "Comparing the stored character list");
		}

		SUBCASE("Freeing the list")
		{
			const std::vector<uint8_t> message = { MCP_CHARLIST, 0, 0, 0, 0, 0, 0, 8, 0 };

			std::vector<D2MCPCharListStrc*> results;
			for_each_api([&](const McpClientApi& api)
			{
				api.D2MCPClientSetCharacterList(message.data(), (uint32_t)message.size());
				REQUIRE(api.D2MCPClientGetCharacterList() != nullptr);
				api.D2MCPClientSetCharacterList(nullptr, 0);
				results.push_back(api.D2MCPClientGetCharacterList());
			});

			CHECK_EQ(results[0], nullptr);
			CHECK_EQ(results[1], nullptr);
		}
	}

	TEST_CASE("D2MCPClient.0x6F9F17C0 (#10055)")
	{
		// No connection was made by the tests
		std::vector<HANDLE> results;
		for_each_api([&](const McpClientApi& api) { results.push_back(api.D2MCPClientGetConnectionThread()); });

		CHECK_EQ(results[0], results[1]);
		CHECK_EQ(results[0], nullptr);
	}
}
