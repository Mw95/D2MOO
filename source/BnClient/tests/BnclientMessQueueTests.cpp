#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <BnMessQueue.h>

#include "BnclientTestFixtures.h"


namespace
{
// Message queue functions of one implementation
struct MessQueueApi
{
	decltype(&BNMESSQUEUE_PushData) PushData;
	decltype(&BNMESSQUEUE_PushString) PushString;
	decltype(&BNMESSQUEUE_Read) Read;
	decltype(&BNMESSQUEUE_Clear) Clear;
	decltype(&BNMESSQUEUE_SetErrorIfNone) SetErrorIfNone;
	decltype(&BNMESSQUEUE_SetError) SetError;
	decltype(&BNMESSQUEUE_SetErrorText) SetErrorText;
	decltype(&BNMESSQUEUE_GetLastError) GetLastError;
	decltype(&BNMESSQUEUE_PeekLastError) PeekLastError;
};

const MessQueueApi& moo_api()
{
	static const MessQueueApi api = {
		&BNMESSQUEUE_PushData,
		&BNMESSQUEUE_PushString,
		&BNMESSQUEUE_Read,
		&BNMESSQUEUE_Clear,
		&BNMESSQUEUE_SetErrorIfNone,
		&BNMESSQUEUE_SetError,
		&BNMESSQUEUE_SetErrorText,
		&BNMESSQUEUE_GetLastError,
		&BNMESSQUEUE_PeekLastError,
	};
	return api;
}

const MessQueueApi& original_api()
{
	static const MessQueueApi api = {
		reinterpret_cast<decltype(&BNMESSQUEUE_PushData)>(original_bnclient_address(0x6FF06320)),
		reinterpret_cast<decltype(&BNMESSQUEUE_PushString)>(original_bnclient_address(0x6FF063F0)),
		reinterpret_cast<decltype(&BNMESSQUEUE_Read)>(original_bnclient_address(0x6FF064A0)),
		reinterpret_cast<decltype(&BNMESSQUEUE_Clear)>(original_bnclient_address(0x6FF06530)),
		reinterpret_cast<decltype(&BNMESSQUEUE_SetErrorIfNone)>(original_bnclient_address(0x6FF06580)),
		reinterpret_cast<decltype(&BNMESSQUEUE_SetError)>(original_bnclient_address(0x6FF065B0)),
		reinterpret_cast<decltype(&BNMESSQUEUE_SetErrorText)>(original_bnclient_address(0x6FF065E0)),
		reinterpret_cast<decltype(&BNMESSQUEUE_GetLastError)>(original_bnclient_address(0x6FF06610)),
		reinterpret_cast<decltype(&BNMESSQUEUE_PeekLastError)>(original_bnclient_address(0x6FF06670)),
	};
	return api;
}

template<typename Test>
void for_each_api(Test&& test)
{
	test(moo_api());
	test(original_api());
}

struct ReadResult
{
	uint32_t nBytes;
	int32_t nType;
	std::vector<uint8_t> data;

	bool operator==(const ReadResult& other) const { return nBytes == other.nBytes && nType == other.nType && data == other.data; }
};

// Reads the queue until it is empty
std::vector<ReadResult> read_all(const MessQueueApi& api)
{
	std::vector<ReadResult> results;
	for (int i = 0; i < 100; ++i)
	{
		uint8_t buffer[0x200];
		std::memset(buffer, 0xCC, sizeof(buffer));
		int32_t nType = -1;
		const uint32_t nBytes = api.Read(&nType, buffer);
		if (!nBytes)
		{
			results.push_back({ 0, nType, {} });
			break;
		}
		// Everything after the copied bytes must be left untouched
		results.push_back({ nBytes, nType, std::vector<uint8_t>(buffer, buffer + sizeof(buffer)) });
	}
	return results;
}

struct ErrorState
{
	int32_t nError;
	const char* szErrorText;

	bool operator==(const ErrorState& other) const { return nError == other.nError && szErrorText == other.szErrorText; }
};
}


TEST_SUITE("BnclientMessQueueTests")
{
	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF06320 / Bnclient.0x6FF063F0 / Bnclient.0x6FF064A0")
	{
		const std::string szLong(0x200, 'L');
		std::vector<uint8_t> data(0x150);
		for (size_t i = 0; i < data.size(); ++i)
		{
			data[i] = (uint8_t)(i * 7);
		}

		std::vector<std::vector<ReadResult>> results;
		for_each_api([&](const MessQueueApi& api)
		{
			api.Clear();
			CHECK_EQ(api.PushString(1, "Hello"), TRUE);
			CHECK_EQ(api.PushData(2, data.data(), 16), TRUE);
			// Empty data
			CHECK_EQ(api.PushData(3, data.data(), 0), TRUE);
			// Too long, truncated to the size of the entry
			CHECK_EQ(api.PushData(4, data.data(), (uint32_t)data.size()), TRUE);
			CHECK_EQ(api.PushString(5, szLong.c_str()), TRUE);
			CHECK_EQ(api.PushString(6, ""), TRUE);
			results.push_back(read_all(api));
		});

		CHECK_MESSAGE(results[0] == results[1], "Comparing the read messages");
		REQUIRE_EQ(results[0].size(), 7);
		CHECK_EQ(results[0][0].nBytes, 6);
		CHECK_EQ(results[0][1].nBytes, 16);
		CHECK_EQ(results[0][3].nBytes, 0x120);
		CHECK_EQ(results[0][4].nBytes, 0x120);
		CHECK_EQ(results[0][6].nBytes, 0);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF06530")
	{
		std::vector<std::vector<ReadResult>> results;
		for_each_api([&](const MessQueueApi& api)
		{
			api.PushString(1, "one");
			api.PushString(2, "two");
			CHECK_EQ(api.Clear(), TRUE);
			results.push_back(read_all(api));

			// The queue still works after being cleared
			api.PushString(3, "three");
			results.push_back(read_all(api));
		});

		CHECK_MESSAGE(results[0] == results[2], "Comparing the queue after BNMESSQUEUE_Clear");
		CHECK_MESSAGE(results[1] == results[3], "Comparing the queue after a new message");
		CHECK_EQ(results[0].size(), 1);
		CHECK_EQ(results[1].size(), 2);
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF06580 / Bnclient.0x6FF065B0 / Bnclient.0x6FF065E0 / Bnclient.0x6FF06610 / Bnclient.0x6FF06670")
	{
		static char szErrorText[] = "Error text";

		std::vector<std::vector<ErrorState>> results;
		for_each_api([&](const MessQueueApi& api)
		{
			std::vector<ErrorState> states;
			auto peek = [&]()
			{
				BnMessQueueErrorInfo tInfo = { -1, nullptr };
				CHECK_EQ(api.PeekLastError(&tInfo), TRUE);
				states.push_back({ tInfo.nError, tInfo.szErrorText });
			};
			auto get = [&]()
			{
				BnMessQueueErrorInfo tInfo = { -1, nullptr };
				CHECK_EQ(api.GetLastError(&tInfo), TRUE);
				states.push_back({ tInfo.nError, tInfo.szErrorText });
			};

			// Start without error
			api.SetError(0);
			api.SetErrorText(nullptr);
			get();
			get();

			api.SetError(18);
			peek();
			// Does not replace an error
			api.SetErrorIfNone(19);
			peek();
			// Reading the error clears it, but not the text
			api.SetErrorText(szErrorText);
			get();
			peek();
			api.SetErrorIfNone(20);
			peek();
			api.SetError(0);
			peek();
			api.SetErrorText(nullptr);
			get();
			results.push_back(states);
		});

		CHECK_MESSAGE(results[0] == results[1], "Comparing the error states");
		REQUIRE_EQ(results[0].size(), 9);
		CHECK_EQ(results[0][2].nError, 18);
		CHECK_EQ(results[0][3].nError, 18);
		CHECK_EQ(results[0][4].szErrorText, szErrorText);
		CHECK_EQ(results[0][5].nError, 0);
		CHECK_EQ(results[0][6].nError, 20);
	}
}
