#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include "D2MCPClientTestFixtures.h"
#include "D2MCPClientVisitorDefinitions.h"


namespace
{
FClientConnection* const gpFakeConnection = reinterpret_cast<FClientConnection*>(0x24681357);

// Records the calls of the D2MCPClient callbacks
struct CallbackRecorder
{
	struct RequestCall
	{
		int nCallback;
		uint16_t nRequestId;
		ptrdiff_t nDataOffset;	// Offset of the data in the message

		bool operator==(const RequestCall& other) const { return nCallback == other.nCallback && nRequestId == other.nRequestId && nDataOffset == other.nDataOffset; }
	};

	struct LadderCall
	{
		int32_t nStartingPosition;
		int32_t nEntries;
		int32_t nNameSize;
		uint8_t nLadderType;
		std::vector<uint8_t> entries;
		bool bNullEntries;

		bool operator==(const LadderCall& other) const
		{
			return nStartingPosition == other.nStartingPosition && nEntries == other.nEntries && nNameSize == other.nNameSize
				&& nLadderType == other.nLadderType && entries == other.entries && bNullEntries == other.bNullEntries;
		}
	};

	struct MotdCall
	{
		int32_t nId;
		uint32_t nSize;
		std::vector<uint8_t> data;

		bool operator==(const MotdCall& other) const { return nId == other.nId && nSize == other.nSize && data == other.data; }
	};

	static inline const uint8_t* pCurrentMessage = nullptr;
	static inline std::vector<RequestCall> request_calls;
	static inline std::vector<LadderCall> ladder_calls;
	static inline int nLadderBeginCalls = 0;
	static inline std::vector<MotdCall> motd_calls;

	static void __fastcall Msg08Callback(uint16_t nRequestId, const uint8_t* pData)
	{
		request_calls.push_back({ 8, nRequestId, pData - pCurrentMessage });
	}

	static void __fastcall Msg09Callback(uint16_t nRequestId, const uint8_t* pData)
	{
		request_calls.push_back({ 9, nRequestId, pData - pCurrentMessage });
	}

	static void __fastcall LadderDataCallback(int32_t nStartingPosition, int32_t nEntries, int32_t nNameSize, uint8_t nLadderType, const uint8_t* pEntries)
	{
		LadderCall call = { nStartingPosition, nEntries, nNameSize, nLadderType, {}, pEntries == nullptr };
		if (pEntries && nEntries > 0)
		{
			call.entries.assign(pEntries, pEntries + nEntries * (12 + nNameSize));
		}
		ladder_calls.push_back(call);
	}

	static void __fastcall LadderDataBeginCallback()
	{
		++nLadderBeginCalls;
	}

	static void __fastcall MotdCallback(int32_t nId, uint32_t nSize, const uint8_t* pData)
	{
		motd_calls.push_back({ nId, nSize, std::vector<uint8_t>(pData, pData + nSize) });
	}

	static void reset()
	{
		pCurrentMessage = nullptr;
		request_calls.clear();
		ladder_calls.clear();
		nLadderBeginCalls = 0;
		motd_calls.clear();
	}
};

// Everything observable through the D2MCPClient api
struct McpState
{
	BOOL bReturnValue = FALSE;
	uint32_t nLastError = 0;
	uint32_t nGameToken = 0;
	uint32_t nGameHash = 0;
	uint16_t nGameRequestId = 0;
	std::string szGameServerIp;
	D2MCPGameInfoStrc tGameInfo = {};
	uint32_t nCreateQueuePosition = 0;
	std::vector<BOOL> flags;
	BOOL bMsg0EReceived = FALSE;
	std::string szMsg0EString1;
	std::string szMsg0EString2;
	std::vector<uint8_t> charList;
	bool bHasCharList = false;
	std::vector<CallbackRecorder::RequestCall> request_calls;
	std::vector<CallbackRecorder::LadderCall> ladder_calls;
	int nLadderBeginCalls = 0;
	std::vector<CallbackRecorder::MotdCall> motd_calls;
};

// Flags in the order of McpState::flags
const std::vector<std::pair<GetFlag, SetFlag>>& flag_accessors()
{
	static const std::vector<std::pair<GetFlag, SetFlag>> accessors = {
		{ &McpClientApi::D2MCPClientGetCharCreateReceived, &McpClientApi::D2MCPClientSetCharCreateReceived },
		{ &McpClientApi::D2MCPClientGetCharLogonReceived, &McpClientApi::D2MCPClientSetCharLogonReceived },
		{ &McpClientApi::D2MCPClientGetCharDeleteReceived, &McpClientApi::D2MCPClientSetCharDeleteReceived },
		{ &McpClientApi::D2MCPClientGetMsg0BReceived, &McpClientApi::D2MCPClientSetMsg0BReceived },
		{ &McpClientApi::D2MCPClientGetMsg0CReceived, &McpClientApi::D2MCPClientSetMsg0CReceived },
		{ &McpClientApi::D2MCPClientGetMsg0DReceived, &McpClientApi::D2MCPClientSetMsg0DReceived },
		{ &McpClientApi::D2MCPClientGetMsg0FReceived, &McpClientApi::D2MCPClientSetMsg0FReceived },
		{ &McpClientApi::D2MCPClientGetMsg10Received, &McpClientApi::D2MCPClientSetMsg10Received },
		{ &McpClientApi::D2MCPClientGetCreateQueueReceived, &McpClientApi::D2MCPClientSetCreateQueueReceived },
		{ &McpClientApi::D2MCPClientGetCharUpgradeReceived, &McpClientApi::D2MCPClientSetCharUpgradeReceived },
	};
	return accessors;
}

// Puts one implementation in a known state. The game hash, request id and server ip have no setter,
// they stay identical in both implementations since the same messages are sent to both.
void reset_state(const McpClientApi& api, uint16_t nPendingRequestId, bool bWithCallbacks)
{
	api.D2MCPClientSetLastError(0x5555);
	*api.pGameToken = 0x77777777;
	*api.pPendingRequestId = nPendingRequestId;
	api.D2MCPClientClearGameInfo();
	api.D2MCPClientSetCreateQueuePosition(0);
	api.D2MCPClientSetMsg0EStrings(FALSE, "", "");
	api.D2MCPClientSetCharacterList(nullptr, 0);
	for (const auto& [get, set] : flag_accessors())
	{
		(api.*set)(FALSE);
	}

	api.D2MCPClientSetMsg08Callback(bWithCallbacks ? &CallbackRecorder::Msg08Callback : nullptr);
	api.D2MCPClientSetMsg09Callback(bWithCallbacks ? &CallbackRecorder::Msg09Callback : nullptr);
	api.D2MCPClientSetLadderDataCallbacks(bWithCallbacks ? &CallbackRecorder::LadderDataCallback : nullptr, bWithCallbacks ? &CallbackRecorder::LadderDataBeginCallback : nullptr);
	api.D2MCPClientSetMotdCallback(bWithCallbacks ? &CallbackRecorder::MotdCallback : nullptr);
	CallbackRecorder::reset();
}

McpState capture_state(const McpClientApi& api, BOOL bReturnValue)
{
	McpState state;
	state.bReturnValue = bReturnValue;
	state.nLastError = api.D2MCPClientGetLastError();
	state.nGameToken = api.D2MCPClientGetGameToken();
	state.nGameHash = api.D2MCPClientGetGameHash();
	state.nGameRequestId = api.D2MCPClientGetGameRequestId();
	state.szGameServerIp = api.D2MCPClientGetGameServerIp();
	state.tGameInfo = *api.D2MCPClientGetGameInfo();
	state.nCreateQueuePosition = api.D2MCPClientGetCreateQueuePosition();
	for (const auto& [get, set] : flag_accessors())
	{
		state.flags.push_back((api.*get)());
	}

	char szString1[36] = {};
	char szString2[28] = {};
	state.bMsg0EReceived = api.D2MCPClientGetMsg0EStrings(szString1, szString2);
	state.szMsg0EString1 = szString1;
	state.szMsg0EString2 = szString2;

	state.request_calls = CallbackRecorder::request_calls;
	state.ladder_calls = CallbackRecorder::ladder_calls;
	state.nLadderBeginCalls = CallbackRecorder::nLadderBeginCalls;
	state.motd_calls = CallbackRecorder::motd_calls;
	return state;
}

void capture_char_list(McpState& state, const McpClientApi& api, size_t nSize)
{
	const auto pCharList = reinterpret_cast<const uint8_t*>(api.D2MCPClientGetCharacterList());
	state.bHasCharList = pCharList != nullptr;
	if (pCharList)
	{
		state.charList.assign(pCharList, pCharList + nSize);
	}
}

void compare_states(McpState& moo, McpState& original)
{
	MOO_CHECK_EQ(moo.bReturnValue, original.bReturnValue, "Comparing the return values");
	MOO_CHECK_EQ(moo.nLastError, original.nLastError, "Comparing the last error");
	MOO_CHECK_EQ(moo.nGameToken, original.nGameToken, "Comparing the game token");
	MOO_CHECK_EQ(moo.nGameHash, original.nGameHash, "Comparing the game hash");
	MOO_CHECK_EQ(moo.nGameRequestId, original.nGameRequestId, "Comparing the game request id");
	CHECK_EQ(moo.szGameServerIp, original.szGameServerIp);
	MOO_CHECK_EQ(moo.tGameInfo, original.tGameInfo, "Comparing the game info");
	MOO_CHECK_EQ(moo.nCreateQueuePosition, original.nCreateQueuePosition, "Comparing the create queue position");
	CHECK_MESSAGE(moo.flags == original.flags, "Comparing the received flags");
	MOO_CHECK_EQ(moo.bMsg0EReceived, original.bMsg0EReceived, "Comparing the MCP_MSG_0E received flag");
	CHECK_EQ(moo.szMsg0EString1, original.szMsg0EString1);
	CHECK_EQ(moo.szMsg0EString2, original.szMsg0EString2);
	CHECK_EQ(moo.bHasCharList, original.bHasCharList);
	CHECK_MESSAGE(moo.charList == original.charList, "Comparing the character list");
	CHECK_MESSAGE(moo.request_calls == original.request_calls, "Comparing the MCP_MSG_08/MCP_MSG_09 callback calls");
	CHECK_MESSAGE(moo.ladder_calls == original.ladder_calls, "Comparing the ladder data callback calls");
	MOO_CHECK_EQ(moo.nLadderBeginCalls, original.nLadderBeginCalls, "Comparing the ladder data begin callback calls");
	CHECK_MESSAGE(moo.motd_calls == original.motd_calls, "Comparing the MOTD callback calls");
}

struct DispatchOptions
{
	uint16_t nPendingRequestId = 0x1111;
	bool bWithCallbacks = true;
};

// Dispatches the messages one after the other on both implementations, compares and returns the final D2MOO state
McpState dispatch(const std::vector<std::vector<uint8_t>>& messages, DispatchOptions options = {})
{
	std::vector<McpState> states;
	for_each_api([&](const McpClientApi& api)
	{
		reset_state(api, options.nPendingRequestId, options.bWithCallbacks);
		BOOL bReturnValue = FALSE;
		for (const auto& message : messages)
		{
			// The message is copied so that both implementations see the same buffer address offsets
			std::vector<uint8_t> buffer = message;
			CallbackRecorder::pCurrentMessage = buffer.data();
			bReturnValue = api.MCP_DispatchMessage(buffer.data(), (uint32_t)buffer.size());
		}

		McpState state = capture_state(api, bReturnValue);
		capture_char_list(state, api, messages.empty() ? 0 : messages.back().size());
		states.push_back(state);
		api.D2MCPClientSetCharacterList(nullptr, 0);
	});

	compare_states(states[0], states[1]);
	return states[0];
}

McpState dispatch(const std::vector<uint8_t>& message, DispatchOptions options = {})
{
	return dispatch(std::vector<std::vector<uint8_t>>{ message }, options);
}

// Message building helpers
struct MessageBuilder
{
	std::vector<uint8_t> data;

	explicit MessageBuilder(uint8_t nMessageId) { data.push_back(nMessageId); }

	MessageBuilder& u8(uint32_t nValue) { data.push_back((uint8_t)nValue); return *this; }
	MessageBuilder& u16(uint32_t nValue) { u8(nValue); return u8(nValue >> 8); }
	MessageBuilder& u32(uint32_t nValue) { u16(nValue); return u16(nValue >> 16); }
	MessageBuilder& str(const char* szString) { data.insert(data.end(), szString, szString + std::strlen(szString) + 1); return *this; }
	MessageBuilder& raw(const std::vector<uint8_t>& bytes) { data.insert(data.end(), bytes.begin(), bytes.end()); return *this; }

	operator std::vector<uint8_t>() const { return data; }
};

std::vector<uint8_t> result_message(uint8_t nMessageId, uint32_t nResult)
{
	return MessageBuilder(nMessageId).u32(nResult);
}
}


TEST_SUITE("D2MCPClientMessageTests")
{
	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F16F0")
	{
		SUBCASE("Messages without handler")
		{
			for (const uint8_t nMessageId : { (uint8_t)MCP_STARTUP, (uint8_t)MCP_CANCELGAMECREATE, (uint8_t)0x15, (uint8_t)MCP_CHARRANK, (uint8_t)NUM_MCP_MESSAGES, (uint8_t)0x80, (uint8_t)0xFF })
			{
				CAPTURE(nMessageId);
				const auto state = dispatch(result_message(nMessageId, 1));
				CHECK_EQ(state.bReturnValue, FALSE);
				CHECK_EQ(state.nLastError, 0x5555);
			}
		}

		SUBCASE("Message 0x00 is ignored")
		{
			const auto state = dispatch(result_message(0, 1));
			CHECK_EQ(state.bReturnValue, TRUE);
			CHECK_EQ(state.nLastError, 0x5555);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1040")
	{
		const auto state = dispatch(result_message(MCP_CHARCREATE, 0x14));
		CHECK_EQ(state.bReturnValue, TRUE);
		CHECK_EQ(state.nLastError, 0x14);
		CHECK_EQ(state.flags[0], TRUE);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1080")
	{
		SUBCASE("Answer to the pending request")
		{
			const auto state = dispatch(MessageBuilder(MCP_CREATEGAME).u16(0x1111).u32(0xA1B2C3D4).u32(0x1E));
			CHECK_EQ(state.nLastError, 0x1E);
			CHECK_EQ(state.nGameToken, 0xA1B2C3D4);
			CHECK_EQ(state.nGameRequestId, 0x1111);
		}

		SUBCASE("Answer to another request")
		{
			const auto state = dispatch(MessageBuilder(MCP_CREATEGAME).u16(0x2222).u32(0xA1B2C3D4).u32(0x1E));
			CHECK_EQ(state.nLastError, 0x5555);
			CHECK_EQ(state.nGameToken, 0x77777777);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F10C0")
	{
		SUBCASE("Game server address")
		{
			const auto state = dispatch(MessageBuilder(MCP_JOINGAME).u16(0x1111).u32(0x01020304).u32(0x0100007F).u32(0x55AA55AA).u32(0));
			CHECK_EQ(state.nGameToken, 0x01020304);
			CHECK_EQ(state.nGameHash, 0x55AA55AA);
			CHECK_EQ(state.szGameServerIp, "127.0.0.1");
			CHECK_EQ(state.nLastError, 0x5555);
		}

		SUBCASE("No address, with an error")
		{
			const auto state = dispatch(MessageBuilder(MCP_JOINGAME).u16(0x1111).u32(5).u32(0).u32(6).u32(0x29));
			CHECK_EQ(state.nLastError, 0x29);
		}

		SUBCASE("No address, without an error")
		{
			const auto state = dispatch(MessageBuilder(MCP_JOINGAME).u16(0x1111).u32(5).u32(0).u32(6).u32(0));
			CHECK_EQ(state.nLastError, MCPCLIENT_ERROR_GAME_NOT_FOUND);
		}

		SUBCASE("Answer to another request")
		{
			const auto state = dispatch(MessageBuilder(MCP_JOINGAME).u16(0x1112).u32(5).u32(0x0200007F).u32(6).u32(0));
			CHECK_EQ(state.nGameToken, 0x77777777);
			CHECK_EQ(state.nLastError, 0x5555);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1140")
	{
		SUBCASE("Last game of the list")
		{
			const auto state = dispatch(MessageBuilder(MCP_GAMELIST).u16(0x1111).u32(3).u8(4).u32(0x10).str("Game").str("Description"));
			CHECK_EQ(state.tGameInfo.dwIndex, 3);
			CHECK_EQ(state.tGameInfo.nPlayers, 4);
			CHECK_EQ(state.tGameInfo.nStatus, 0x10);
			CHECK_EQ(std::string(state.tGameInfo.szGameName), "Game");
			CHECK_EQ(std::string(state.tGameInfo.szGameDescription), "Description");
			CHECK_EQ(state.tGameInfo.bMoreData, FALSE);
		}

		SUBCASE("More data after the description")
		{
			const auto state = dispatch(MessageBuilder(MCP_GAMELIST).u16(0x1111).u32(0).u8(1).u32(0).str("Game").str("").u8(0x42));
			CHECK_EQ(state.tGameInfo.bMoreData, TRUE);
		}

		SUBCASE("Errors")
		{
			for (const int32_t nStatus : { -1, -2 })
			{
				CAPTURE(nStatus);
				dispatch(MessageBuilder(MCP_GAMELIST).u16(0x1111).u32(7).u8(2).u32(nStatus));
			}
		}

		SUBCASE("Answer to another request")
		{
			const auto state = dispatch(MessageBuilder(MCP_GAMELIST).u16(0x0001).u32(3).u8(4).u32(0).str("Game").str("Description"));
			CHECK_EQ(state.tGameInfo.dwIndex, 0);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1210")
	{
		auto game_info = [](int32_t nStatus, uint8_t nPlayers)
		{
			MessageBuilder message(MCP_GAMEINFO);
			message.u16(0x1111).u32(nStatus).u32(3600).u8(0x0B).u8(0x0C).u8(8).u8(nPlayers);
			for (int i = 0; i < 16; ++i) message.u8(i < nPlayers ? i % 7 : 0);
			for (int i = 0; i < 16; ++i) message.u8(i < nPlayers ? 10 + i : 0);
			message.str("The description");
			for (int i = 0; i < nPlayers; ++i) message.str(("Player" + std::to_string(i)).c_str());
			return std::vector<uint8_t>(message);
		};

		SUBCASE("Players")
		{
			for (const uint8_t nPlayers : { 0, 1, 3, 8 })
			{
				CAPTURE(nPlayers);
				const auto state = dispatch(game_info(0, nPlayers));
				CHECK_EQ(state.tGameInfo.nPlayers, nPlayers);
				CHECK_EQ(state.tGameInfo.dwUptime, 3600);
				CHECK_EQ(std::string(state.tGameInfo.szGameDescription), "The description");
				if (nPlayers > 0)
				{
					CHECK_EQ(std::string(state.tGameInfo.szPlayerName[nPlayers - 1]), "Player" + std::to_string(nPlayers - 1));
				}
			}
		}

		SUBCASE("Errors")
		{
			for (const int32_t nStatus : { -1, -2 })
			{
				CAPTURE(nStatus);
				dispatch(game_info(nStatus, 2));
			}
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1060")
	{
		const auto state = dispatch(result_message(MCP_CHARLOGON, 0x46));
		CHECK_EQ(state.nLastError, 0x46);
		CHECK_EQ(state.flags[1], TRUE);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1360 / D2MCPClient.0x6F9F1380")
	{
		const std::vector<uint8_t> msg08 = MessageBuilder(MCP_MSG_08).u16(0x0808).u32(0x01020304);
		const std::vector<uint8_t> msg09 = MessageBuilder(MCP_MSG_09).u16(0x0909).u32(0x01020304);

		SUBCASE("With callbacks")
		{
			const auto state = dispatch(std::vector<std::vector<uint8_t>>{ msg08, msg09 });
			REQUIRE_EQ(state.request_calls.size(), 2);
			CHECK_EQ(state.request_calls[0].nRequestId, 0x0808);
			CHECK_EQ(state.request_calls[0].nDataOffset, 3);
			CHECK_EQ(state.request_calls[1].nRequestId, 0x0909);
			CHECK_EQ(state.request_calls[1].nDataOffset, 4);
		}

		SUBCASE("Without callbacks")
		{
			DispatchOptions options;
			options.bWithCallbacks = false;
			const auto state = dispatch(std::vector<std::vector<uint8_t>>{ msg08, msg09 }, options);
			CHECK_EQ(state.bReturnValue, TRUE);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F13A0")
	{
		SUBCASE("Answer to the pending request")
		{
			const auto state = dispatch(MessageBuilder(MCP_CHARDELETE).u16(0x1111).u32(0x49));
			CHECK_EQ(state.nLastError, 0x49);
			CHECK_EQ(state.flags[2], TRUE);
		}

		SUBCASE("Answer to another request")
		{
			const auto state = dispatch(MessageBuilder(MCP_CHARDELETE).u16(0x1234).u32(0x49));
			CHECK_EQ(state.flags[2], FALSE);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F13F0 / D2MCPClient.0x6F9F1410 / D2MCPClient.0x6F9F1460 / D2MCPClient.0x6F9F1480")
	{
		const std::pair<uint8_t, size_t> messages[] = { { MCP_MSG_0B, 3 }, { MCP_MSG_0C, 4 }, { MCP_MSG_0D, 5 }, { MCP_MSG_0F, 6 } };
		for (const auto& [nMessageId, nFlag] : messages)
		{
			CAPTURE(nMessageId);
			const auto state = dispatch(result_message(nMessageId, 0x100 + nMessageId));
			CHECK_EQ(state.nLastError, 0x100u + nMessageId);
			CHECK_EQ(state.flags[nFlag], TRUE);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1430")
	{
		const auto state = dispatch(MessageBuilder(MCP_MSG_0E).str("String one").str("Two"));
		CHECK_EQ(state.bMsg0EReceived, TRUE);
		CHECK_EQ(state.szMsg0EString1, "String one");
		CHECK_EQ(state.szMsg0EString2, "Two");
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F14A0")
	{
		SUBCASE("Game server address")
		{
			const auto state = dispatch(MessageBuilder(MCP_MSG_10).u32(0x10101010).u32(0x20202020).u32(0x0403020A).u32(0x33));
			CHECK_EQ(state.nGameToken, 0x10101010);
			CHECK_EQ(state.nGameHash, 0x20202020);
			CHECK_EQ(state.szGameServerIp, "10.2.3.4");
			CHECK_EQ(state.nLastError, 0x33);
			CHECK_EQ(state.flags[7], TRUE);
		}

		SUBCASE("No address")
		{
			for (const uint32_t nResult : { 0u, 0x2Bu })
			{
				CAPTURE(nResult);
				dispatch(MessageBuilder(MCP_MSG_10).u32(1).u32(2).u32(0).u32(nResult));
			}
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1520")
	{
		// A block of the ladder answer: header then nEntries entries of 12 bytes + the name
		auto ladder_block = [](int32_t nStartingPosition, int32_t nEntries, int32_t nNameSize)
		{
			MessageBuilder block(0);
			block.data.clear();
			block.u32(nStartingPosition).u32(nEntries).u32(nNameSize);
			for (int32_t i = 0; i < nEntries * (12 + nNameSize); ++i)
			{
				block.u8(nStartingPosition + i);
			}
			return block.data;
		};

		auto ladder_chunk = [](uint8_t nLadderType, const std::vector<uint8_t>& answer, size_t nOffset, size_t nSize)
		{
			return std::vector<uint8_t>(MessageBuilder(MCP_REQUESTLADDERDATA).u8(nLadderType).u16((uint32_t)answer.size()).u16((uint32_t)nSize).u16((uint32_t)nOffset)
				.raw(std::vector<uint8_t>(answer.begin() + nOffset, answer.begin() + nOffset + nSize)));
		};

		SUBCASE("Empty answer")
		{
			// The original calls the ladder callback without checking it, so it must be set
			const auto state = dispatch(MessageBuilder(MCP_REQUESTLADDERDATA).u8(0x13).u16(0).u16(0).u16(0));
			REQUIRE_EQ(state.ladder_calls.size(), 1);
			CHECK_EQ(state.ladder_calls[0].bNullEntries, true);
			CHECK_EQ(state.nLadderBeginCalls, 0);
		}

		SUBCASE("Single chunk with two blocks")
		{
			std::vector<uint8_t> answer = ladder_block(0, 3, 16);
			const auto block2 = ladder_block(3, 2, 16);
			answer.insert(answer.end(), block2.begin(), block2.end());

			const auto state = dispatch(ladder_chunk(0x1B, answer, 0, answer.size()));
			CHECK_EQ(state.nLadderBeginCalls, 1);
			REQUIRE_EQ(state.ladder_calls.size(), 2);
			CHECK_EQ(state.ladder_calls[0].nEntries, 3);
			CHECK_EQ(state.ladder_calls[1].nStartingPosition, 3);
			CHECK_EQ(state.ladder_calls[1].nLadderType, 0x1B);
		}

		SUBCASE("Answer in three chunks")
		{
			const std::vector<uint8_t> answer = ladder_block(10, 20, 16);
			const size_t nThird = answer.size() / 3;
			const auto state = dispatch(std::vector<std::vector<uint8_t>>{
				ladder_chunk(0x09, answer, 0, nThird),
				ladder_chunk(0x09, answer, nThird, nThird),
				ladder_chunk(0x09, answer, 2 * nThird, answer.size() - 2 * nThird),
			});
			CHECK_EQ(state.nLadderBeginCalls, 1);
			REQUIRE_EQ(state.ladder_calls.size(), 1);
			CHECK_EQ(state.ladder_calls[0].nEntries, 20);
			CHECK_MESSAGE(state.ladder_calls[0].entries == std::vector<uint8_t>(answer.begin() + 12, answer.end()), "Reassembled entries");
		}

		SUBCASE("Partial answer")
		{
			const std::vector<uint8_t> answer = ladder_block(0, 4, 16);
			const auto state = dispatch(ladder_chunk(0x13, answer, 0, answer.size() / 2));
			CHECK_EQ(state.nLadderBeginCalls, 0);
			CHECK(state.ladder_calls.empty());
		}

		SUBCASE("Invalid blocks stop the parsing")
		{
			// Too many entries, name too long, starting position too far
			for (const auto& block : { ladder_block(0, 257, 0), ladder_block(0, 1, 17), ladder_block(2001, 1, 16) })
			{
				std::vector<uint8_t> answer = ladder_block(0, 1, 16);
				answer.insert(answer.end(), block.begin(), block.end());
				if (answer.size() > 0x7000)
				{
					continue;
				}

				const auto state = dispatch(ladder_chunk(0x13, answer, 0, answer.size()));
				CHECK_EQ(state.ladder_calls.size(), 1);
			}
		}

		SUBCASE("Without callbacks")
		{
			const std::vector<uint8_t> answer = ladder_block(0, 2, 16);
			DispatchOptions options;
			options.bWithCallbacks = false;
			dispatch(ladder_chunk(0x13, answer, 0, answer.size()), options);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1690")
	{
		SUBCASE("With callback")
		{
			const auto state = dispatch(MessageBuilder(MCP_MOTD).u8(0xC8).str("Welcome!"));
			REQUIRE_EQ(state.motd_calls.size(), 1);
			// The id is zero-extended
			CHECK_EQ(state.motd_calls[0].nId, 0xC8);
			CHECK_EQ(state.motd_calls[0].nSize, 9);
		}

		SUBCASE("Without callback")
		{
			DispatchOptions options;
			options.bWithCallbacks = false;
			const auto state = dispatch(MessageBuilder(MCP_MOTD).u8(1).str("Welcome!"), options);
			CHECK_EQ(state.bReturnValue, TRUE);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F16C0")
	{
		const auto state = dispatch(result_message(MCP_CREATEQUEUE, 42));
		CHECK_EQ(state.nCreateQueuePosition, 42);
		CHECK_EQ(state.flags[8], TRUE);
		CHECK_EQ(state.nLastError, 0x5555);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F16E0")
	{
		SUBCASE("MCP_CHARLIST")
		{
			const auto state = dispatch(MessageBuilder(MCP_CHARLIST).u16(1).u16(0).u16(1).u16(8).str("Name").str("stats"));
			CHECK_EQ(state.bHasCharList, true);
		}

		SUBCASE("MCP_CHARLIST2")
		{
			const auto state = dispatch(MessageBuilder(MCP_CHARLIST2).u16(1).u16(0).u16(1).u16(1).u32(0x5F5E100).str("Name").str("stats"));
			CHECK_EQ(state.bHasCharList, true);
		}
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F13D0")
	{
		const auto state = dispatch(result_message(MCP_CHARUPGRADE, 0x7A));
		CHECK_EQ(state.nLastError, 0x7A);
		CHECK_EQ(state.flags[9], TRUE);
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1730")
	{
		std::vector<std::pair<BOOL, uint32_t>> results;
		for_each_api([&](const McpClientApi& api)
		{
			api.D2MCPClientSetLastError(0x5555);
			std::vector<uint8_t> startup = result_message(MCP_STARTUP, 0x7E);
			std::vector<uint8_t> other = result_message(MCP_CHARCREATE, 0x7F);
			const BOOL bStartup = api.MCP_DispatchConnectionMessage(startup.data(), (uint32_t)startup.size(), nullptr);
			const BOOL bOther = api.MCP_DispatchConnectionMessage(other.data(), (uint32_t)other.size(), nullptr);
			results.emplace_back(bStartup, api.D2MCPClientGetLastError());
			results.emplace_back(bOther, api.D2MCPClientGetLastError());
		});

		REQUIRE_EQ(results.size(), 4);
		CHECK_EQ(results[0], results[2]);
		CHECK_EQ(results[1], results[3]);
		// MCP_STARTUP is handled on the network thread, the other messages are left to D2MCPClientProcessMessages
		CHECK_EQ(results[0], std::make_pair(TRUE, 0x7Eu));
		CHECK_EQ(results[1], std::make_pair(FALSE, 0x7Eu));
	}

	TEST_CASE_FIXTURE(McpFogFixture<NoOpFixture>, "D2MCPClient.0x6F9F1A20 (#10003)")
	{
		struct Result
		{
			BOOL bWithoutConnection;
			size_t nReceivesWithoutConnection;
			BOOL bWithConnection;
			BOOL bEmptyQueue;
			std::vector<FClientConnection*> receive_connections;
			uint32_t nLastError;
			BOOL bCharLogonReceived;
		};

		std::vector<Result> results;
		for_each_api([&](const McpClientApi& api)
		{
			Result result = {};
			api.D2MCPClientSetLastError(0);
			api.D2MCPClientSetCharLogonReceived(FALSE);
			McpFogMock::receive_queue = { result_message(MCP_CHARLOGON, 0x21) };
			McpFogMock::receive_connections.clear();

			*api.ppConnection = nullptr;
			result.bWithoutConnection = api.D2MCPClientProcessMessages();
			result.nReceivesWithoutConnection = McpFogMock::receive_connections.size();

			*api.ppConnection = gpFakeConnection;
			result.bWithConnection = api.D2MCPClientProcessMessages();
			result.bEmptyQueue = api.D2MCPClientProcessMessages();
			*api.ppConnection = nullptr;

			result.receive_connections = McpFogMock::receive_connections;
			result.nLastError = api.D2MCPClientGetLastError();
			result.bCharLogonReceived = api.D2MCPClientGetCharLogonReceived();
			results.push_back(result);
		});

		for (const Result& result : results)
		{
			CHECK_EQ(result.bWithoutConnection, FALSE);
			CHECK_EQ(result.nReceivesWithoutConnection, 0);
		}
		MOO_CHECK_EQ(results[0].bWithConnection, results[1].bWithConnection, "Comparing the return value with a connection");
		MOO_CHECK_EQ(results[0].bEmptyQueue, results[1].bEmptyQueue, "Comparing the return value without message");
		CHECK_EQ(results[0].receive_connections, results[1].receive_connections);
		MOO_CHECK_EQ(results[0].nLastError, results[1].nLastError, "Comparing the last error");
		MOO_CHECK_EQ(results[0].bCharLogonReceived, results[1].bCharLogonReceived, "Comparing the char logon received flag");
		CHECK_EQ(results[0].nLastError, 0x21);
		CHECK_EQ(results[0].receive_connections, std::vector<FClientConnection*>{ gpFakeConnection, gpFakeConnection });
	}
}
