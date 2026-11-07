#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <BnRecv.h>

#include "BnclientTestFixtures.h"


namespace
{
struct QueuedMessage
{
	int32_t nType;
	std::vector<uint8_t> data;

	bool operator==(const QueuedMessage& other) const { return nType == other.nType && data == other.data; }
};

// Everything observable after a message was dispatched
struct RecvState
{
	std::vector<int32_t> received;
	std::vector<int32_t> results;
	int32_t nCreateAccountResult = 0;
	int32_t nChangePasswordResult = 0;
	BOOL bDisconnected = FALSE;
	int32_t nError = 0;
	std::string szErrorText;
	bool bHasErrorText = false;
	std::vector<QueuedMessage> queue;
	uint32_t nServerToken = 0;
	std::string szUniqueName;
	BOOL bEmailRequested = FALSE;

	bool operator==(const RecvState& other) const
	{
		return received == other.received && results == other.results && nCreateAccountResult == other.nCreateAccountResult
			&& nChangePasswordResult == other.nChangePasswordResult && bDisconnected == other.bDisconnected && nError == other.nError
			&& szErrorText == other.szErrorText && bHasErrorText == other.bHasErrorText && queue == other.queue
			&& nServerToken == other.nServerToken && szUniqueName == other.szUniqueName && bEmailRequested == other.bEmailRequested;
	}
};

void reset_state(const BnclientApi& api)
{
	api.BNRECV_ResetAllMessages();
	api.BNMESSQUEUE_Clear();
	api.BNMESSQUEUE_SetError(0);
	api.BNMESSQUEUE_SetErrorText(nullptr);
	api.BNSEND_SetServerToken(0x12121212);
	api.BNET_SetUniqueName("");
	api.BNET_SetEmailRequested(FALSE);
}

RecvState capture_state(const BnclientApi& api)
{
	RecvState state;
	for (uint32_t nMessageId = 0; nMessageId < BN_MESSAGE_COUNT; ++nMessageId)
	{
		state.received.push_back(api.BNRECV_WasMessageReceived((uint8_t)nMessageId));
		state.results.push_back(api.BNRECV_GetMessageResult((uint8_t)nMessageId));
	}
	state.nCreateAccountResult = api.BNRECV_GetCreateAccountResult();
	state.nChangePasswordResult = api.BNRECV_GetChangePasswordResult();
	state.bDisconnected = api.BNRECV_IsDisconnected();

	BnMessQueueErrorInfo tErrorInfo = {};
	api.BNMESSQUEUE_PeekLastError(&tErrorInfo);
	state.nError = tErrorInfo.nError;
	state.bHasErrorText = tErrorInfo.szErrorText != nullptr;
	if (tErrorInfo.szErrorText)
	{
		state.szErrorText = tErrorInfo.szErrorText;
	}

	for (int i = 0; i < 100; ++i)
	{
		uint8_t buffer[0x200] = {};
		int32_t nType = -1;
		const uint32_t nBytes = api.BNMESSQUEUE_Read(&nType, buffer);
		if (!nBytes)
		{
			break;
		}
		state.queue.push_back({ nType, std::vector<uint8_t>(buffer, buffer + nBytes) });
	}

	state.nServerToken = api.BNSEND_GetServerToken();
	state.szUniqueName = api.BNET_GetUniqueName();
	state.bEmailRequested = api.BNET_IsEmailRequested();
	return state;
}

// Dispatches the messages on both implementations, compares the states and returns the D2MOO one
RecvState dispatch(const std::vector<std::pair<uint8_t, std::vector<uint8_t>>>& messages)
{
	std::vector<RecvState> states;
	for_each_api([&](const BnclientApi& api)
	{
		reset_state(api);
		for (const auto& [nMessageId, data] : messages)
		{
			std::vector<uint8_t> buffer = data;
			// Some handlers read a few bytes without checking the size
			buffer.resize(std::max<size_t>(buffer.size(), 16) + 16, 0);
			api.BNRECV_DispatchMessage(nMessageId, buffer.data(), (uint32_t)data.size());
		}
		states.push_back(capture_state(api));
	});

	CHECK_MESSAGE(states[0].received == states[1].received, "Comparing the received flags");
	CHECK_MESSAGE(states[0].results == states[1].results, "Comparing the message results");
	CHECK_EQ(states[0].nCreateAccountResult, states[1].nCreateAccountResult);
	CHECK_EQ(states[0].nChangePasswordResult, states[1].nChangePasswordResult);
	CHECK_EQ(states[0].bDisconnected, states[1].bDisconnected);
	CHECK_EQ(states[0].nError, states[1].nError);
	CHECK_EQ(states[0].bHasErrorText, states[1].bHasErrorText);
	CHECK_EQ(states[0].szErrorText, states[1].szErrorText);
	CHECK_MESSAGE(states[0].queue == states[1].queue, "Comparing the queued messages");
	CHECK_EQ(states[0].nServerToken, states[1].nServerToken);
	CHECK_EQ(states[0].szUniqueName, states[1].szUniqueName);
	CHECK_EQ(states[0].bEmailRequested, states[1].bEmailRequested);
	return states[0];
}

RecvState dispatch(uint8_t nMessageId, const std::vector<uint8_t>& data)
{
	return dispatch({ { nMessageId, data } });
}

std::vector<uint8_t> u32(uint32_t nValue)
{
	return { (uint8_t)nValue, (uint8_t)(nValue >> 8), (uint8_t)(nValue >> 16), (uint8_t)(nValue >> 24) };
}

std::vector<uint8_t> operator+(std::vector<uint8_t> a, const std::vector<uint8_t>& b)
{
	a.insert(a.end(), b.begin(), b.end());
	return a;
}

std::vector<uint8_t> str(const char* szString)
{
	return std::vector<uint8_t>(szString, szString + std::strlen(szString) + 1);
}
}


TEST_SUITE("BnclientRecvTests")
{
	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF032A0")
	{
		SUBCASE("Messages without handler only set the received flag")
		{
			for (const uint8_t nMessageId : { 0x01, 0x08, 0x0C, 0x30, 0x5A, 0x5D })
			{
				CAPTURE(nMessageId);
				const auto state = dispatch(nMessageId, u32(1));
				CHECK_EQ(state.received[nMessageId], 1);
			}
		}

		SUBCASE("Ignored messages")
		{
			for (const uint8_t nMessageId : { SID_NULL, SID_ANNOUNCEMENT })
			{
				CAPTURE(nMessageId);
				const auto state = dispatch(nMessageId, u32(1));
				CHECK_EQ(state.received[nMessageId], 1);
			}
		}

		SUBCASE("Message ids out of the handler table")
		{
			for (const uint8_t nMessageId : { (uint8_t)BN_MESSAGE_COUNT, (uint8_t)0x5F, (uint8_t)0x80, (uint8_t)0xFF })
			{
				CAPTURE(nMessageId);
				const auto state = dispatch(nMessageId, u32(1));
				for (const int32_t nReceived : state.received)
				{
					CHECK_EQ(nReceived, 0);
				}
			}
		}
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF02420")
	{
		const auto state = dispatch(SID_CREATEACCOUNT, u32(0x55));
		CHECK_EQ(state.results[SID_CREATEACCOUNT], 0x55);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF02430")
	{
		const auto state = dispatch(SID_CREATEACCOUNT2, u32(6));
		CHECK_EQ(state.nCreateAccountResult, 6);
		CHECK_EQ(state.results[SID_CREATEACCOUNT2], 1);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF02450")
	{
		for (const uint32_t nResult : { 0u, 1u })
		{
			CAPTURE(nResult);
			const auto state = dispatch(SID_CHANGEPASSWORD, u32(nResult));
			CHECK_EQ(state.nChangePasswordResult, nResult);
			CHECK_EQ(state.nError, nResult ? 0 : 14);
		}
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF02520 / Bnclient.0x6FF02540")
	{
		CHECK_EQ(dispatch(SID_LOGONCHALLENGE, u32(0xDEADBEEF)).nServerToken, 0xDEADBEEF);
		CHECK_EQ(dispatch(SID_LOGONCHALLENGEEX, u32(1) + u32(0xFEEDF00D)).nServerToken, 0xFEEDF00D);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF02530")
	{
		CHECK_EQ(dispatch(SID_STARTADVEX3, u32(0)).results[SID_STARTADVEX3], 1);
		CHECK_EQ(dispatch(SID_STARTADVEX3, u32(1)).results[SID_STARTADVEX3], 0);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF02570 / Bnclient.0x6FF02590")
	{
		for (const uint32_t nResult : { 0u, 1u, 2u, 3u, 4u, 0xFFFFFFFFu })
		{
			CAPTURE(nResult);
			dispatch(SID_LOGONRESPONSE, u32(nResult));
			dispatch(SID_LOGONRESPONSE2, u32(nResult));
		}
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF02740")
	{
		for (const uint32_t nResult : { 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u })
		{
			CAPTURE(nResult);
			const auto state = dispatch(SID_CDKEY3, u32(nResult) + str("Key owner name"));
			CHECK_EQ(state.results[SID_CDKEY3], nResult == 0 ? 1 : 0);
			if (nResult == 4)
			{
				CHECK_EQ(state.szErrorText, "Key owner name");
			}
		}
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF028A0")
	{
		const auto state = dispatch(SID_ENTERCHAT, str("UniqueName#3") + str("statstring") + str("account"));
		CHECK_EQ(state.szUniqueName, "UniqueName#3");
		REQUIRE_EQ(state.queue.size(), 1);
		CHECK_EQ(state.queue[0].nType, 2);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF01030")
	{
		const auto event = u32(5) + u32(0x10) + u32(30) + u32(0) + u32(0) + u32(0) + str("User") + str("Hello world");
		const auto state = dispatch(SID_CHATEVENT, event);
		REQUIRE_EQ(state.queue.size(), 1);
		CHECK_EQ(state.queue[0].nType, 0);
		CHECK_MESSAGE(state.queue[0].data == event, "The chat event is queued as is");
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF03250")
	{
		CHECK_EQ(dispatch(SID_SETEMAIL, {}).bEmailRequested, TRUE);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF02310 / Bnclient.0x6FF023E0 / Bnclient.0x6FF022D0")
	{
		std::vector<RecvState> states;
		for_each_api([&](const BnclientApi& api)
		{
			reset_state(api);
			std::vector<uint8_t> data = u32(9);
			api.BNRECV_DispatchMessage(SID_CREATEACCOUNT, data.data(), 4);
			api.BNRECV_DispatchMessage(SID_CREATEACCOUNT2, data.data(), 4);
			api.BNRECV_DispatchMessage(SID_LOGONRESPONSE2, data.data(), 4);
			api.BNRECV_SetDisconnected();
			states.push_back(capture_state(api));

			api.BNRECV_ResetMessage(SID_CREATEACCOUNT);
			states.push_back(capture_state(api));

			api.BNRECV_ResetAllMessages();
			states.push_back(capture_state(api));
		});

		for (size_t i = 0; i < 3; ++i)
		{
			CAPTURE(i);
			CHECK_MESSAGE(states[i] == states[i + 3], "Comparing the states");
		}
		CHECK_EQ(states[0].bDisconnected, TRUE);
		CHECK_EQ(states[0].nError, 18);
		CHECK_EQ(states[1].received[SID_CREATEACCOUNT], 0);
		CHECK_EQ(states[1].results[SID_CREATEACCOUNT], 0);
		CHECK_EQ(states[1].received[SID_CREATEACCOUNT2], 1);
		CHECK_EQ(states[2].bDisconnected, FALSE);
		CHECK_EQ(states[2].nError, 0);
		// The account result is not reset
		CHECK_EQ(states[2].nCreateAccountResult, 9);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF07180 / Bnclient.0x6FF07190 / Bnclient.0x6FF071A0 / Bnclient.0x6FF071B0")
	{
		for (const uint32_t nValue : { 0u, 1u, 2u, 0x89ABCDEFu })
		{
			std::vector<std::pair<uint32_t, uint32_t>> results;
			for_each_api([&](const BnclientApi& api)
			{
				api.BNSEND_SetServerToken(nValue);
				api.BNSEND_SetLogonType(nValue);
				results.emplace_back(api.BNSEND_GetServerToken(), api.BNSEND_GetLogonType());
			});
			CHECK_EQ(results[0], results[1]);
			CHECK_EQ(results[0], std::make_pair(nValue, nValue));
		}
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF01000 / Bnclient.0x6FF01020")
	{
		const std::string szLong(300, 'n');
		for (const char* szName : { "", "Name", "Name#2", szLong.c_str() })
		{
			std::vector<std::string> results;
			for_each_api([&](const BnclientApi& api)
			{
				CHECK_EQ(api.BNET_SetUniqueName(szName), TRUE);
				results.push_back(api.BNET_GetUniqueName());
			});
			CHECK_EQ(results[0], results[1]);
		}
	}
}
