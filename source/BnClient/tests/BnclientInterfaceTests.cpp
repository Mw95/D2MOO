#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <BnClient.h>
#include <BnConnect.h>
#include <BNNews.h>
#include <BnRecv.h>

#include "BnclientTestFixtures.h"


extern "C" BNCLIENT_DLL_DECL BnClientInterface* __cdecl QueryInterface();


namespace
{
BnClientInterface* original_interface()
{
	using QueryInterfaceFunction = BnClientInterface*(__cdecl*)();
	const auto pfQueryInterface = reinterpret_cast<QueryInterfaceFunction>(GetProcAddress(get_original_bnclient(), "QueryInterface"));
	REQUIRE(pfQueryInterface != nullptr);
	return pfQueryInterface();
}

// Address in the original dll of the function documented for each slot of BnClientInterface
const std::pair<uint32_t, uintptr_t> gaInterfaceSlots[] = {
	{ 0x00, 0x6FF0ABF0 },	// BNLOG_Initialize
	{ 0x04, 0x6FF01B20 },	// BNET_OpenBNetConnection
	{ 0x08, 0x6FF01C70 },	// BNET_Logon
	{ 0x0C, 0x6FF01CC0 },	// BNET_GetLogonInfo
	{ 0x10, 0x6FF01EA0 },	// BNET_CloseBNetConnection
	{ 0x14, 0x6FF077C0 },	// BNSEND_ChatCommand
	{ 0x18, 0x6FF01020 },	// BNET_GetUniqueName
	{ 0x1C, 0x6FF07630 },	// BNSEND_JoinChannel
	{ 0x20, 0x6FF075E0 },	// BNSEND_GetChannelList
	{ 0x24, 0x6FF064A0 },	// BNMESSQUEUE_Read
	{ 0x28, 0x6FF06610 },	// BNMESSQUEUE_GetLastError
	{ 0x2C, 0x6FF03370 },	// BNDOWNLOAD_RequestFileTime
	{ 0x30, 0x6FF07860 },	// BNSEND_CheckAd
	{ 0x34, 0x6FF07910 },	// BNSEND_StartAdvEx3
	{ 0x38, 0x6FF07AB0 },	// BNSEND_GetGameList
	{ 0x3C, 0x6FF07B60 },	// BNSEND_NotifyJoin
	{ 0x40, 0x6FF07510 },	// BNSEND_QueryRealms
	{ 0x44, 0x6FF07C60 },	// BNSEND_LogonRealm
	{ 0x48, 0x6FF04750 },	// BNDOWNLOAD_RunUpgrade
	{ 0x4C, 0x6FF04E00 },	// BNDOWNLOAD_GetStatus
	{ 0x50, 0x6FF04E10 },	// BNDOWNLOAD_StartPatch
	{ 0x54, 0x6FF01E10 },	// BNET_EnterChat
	{ 0x58, 0x6FF01E90 },	// BNET_LeaveChat
	{ 0x5C, 0x6FF02240 },	// BNET_GetVersion
	{ 0x60, 0x6FF01D00 },	// BNET_CreateAccount
	{ 0x64, 0x6FF01D50 },	// BNET_GetCreateAccountResult
	{ 0x68, 0x6FF02260 },	// BNET_IsConnected
	{ 0x6C, 0x6FF07D10 },	// BNSEND_ClickAd
	{ 0x70, 0x6FF03C10 },	// BNDOWNLOAD_CancelAll
	{ 0x74, 0x6FF07D40 },	// BNSEND_WriteUserData
	{ 0x78, 0x6FF07E90 },	// BNSEND_RequestUserData
	{ 0x7C, 0x6FF07F50 },	// BNSEND_GetUserData
	{ 0x80, 0x6FF01C40 },	// BNET_GetConnectionState
	{ 0x84, 0x6FF0ACD0 },	// BNLOG_Printf
	{ 0x88, 0x6FF0AC60 },	// BNLOG_Command
	{ 0x8C, 0x6FF07A00 },	// BNSEND_GetCreateGameResult
	{ 0x90, 0x6FF079C0 },	// BNSEND_StopAdv
	{ 0x94, 0x6FF07070 },	// BNCDKEY_Validate
	{ 0x98, 0x6FF018B0 },	// BNET_GetBnGatewayAccess
	{ 0x9C, 0x6FF01D80 },	// BNET_ChangePassword
	{ 0xA0, 0x6FF01DE0 },	// BNET_GetChangePasswordResult
	{ 0xA4, 0x6FF074C0 },	// BNSEND_QueryAdUrl
	{ 0xA8, 0x6FF06740 },	// BNNEWS_LoadBNetNews
	{ 0xAC, 0x6FF06990 },	// BNNEWS_FreeBNetNews
	{ 0xB0, 0x6FF02250 },	// BNET_GetBuild
	{ 0xB4, 0x6FF022A0 },	// BNET_IsEmailRequested
	{ 0xB8, 0x6FF07FF0 },	// BNSEND_SetEmail
	{ 0xBC, 0x6FF08060 },	// BNSEND_ResetPassword
	{ 0xC0, 0x6FF08180 },	// BNSEND_ChangeEmail
	{ 0xC4, 0x6FF079E0 },	// BNSEND_LeaveGame
};

// Records the news callbacks
struct NewsRecorder
{
	struct Item
	{
		uint32_t nTimestamp;
		std::string szText;

		bool operator==(const Item& other) const { return nTimestamp == other.nTimestamp && szText == other.szText; }
	};

	// The done callback is recorded as an item with this timestamp
	static constexpr uint32_t DONE = 0xFFFFFFFF;
	static inline std::vector<Item> calls;

	static int32_t __fastcall ItemCallback(uint32_t nTimestamp, const char* szText)
	{
		calls.push_back({ nTimestamp, szText });
		return 1;
	}

	static int32_t __fastcall DoneCallback()
	{
		calls.push_back({ DONE, "" });
		return 1;
	}
};

std::vector<uint8_t> news_message(int8_t nItems, uint32_t nOldestTimestamp, uint32_t nNewestTimestamp, const std::vector<std::pair<uint32_t, std::string>>& items)
{
	std::vector<uint8_t> message = { (uint8_t)nItems, 0, 0, 0, 0 };
	auto u32 = [&message](uint32_t nValue)
	{
		for (int i = 0; i < 4; ++i)
		{
			message.push_back((uint8_t)(nValue >> (8 * i)));
		}
	};
	u32(nOldestTimestamp);
	u32(nNewestTimestamp);
	for (const auto& [nTimestamp, szText] : items)
	{
		u32(nTimestamp);
		message.insert(message.end(), szText.begin(), szText.end());
		message.push_back(0);
	}
	return message;
}
}


TEST_SUITE("BnclientInterfaceTests")
{
	TEST_CASE("Bnclient.0x6FF0AD80 (#23)")
	{
		static_assert(sizeof(BnClientInterface) == 0xC8, "BnClientInterface has 50 slots");

		const auto pOriginal = reinterpret_cast<const uintptr_t*>(original_interface());
		REQUIRE_EQ(reinterpret_cast<uintptr_t>(pOriginal), original_bnclient_address(0x6FF19E70));
		for (const auto& [nOffset, nAddress] : gaInterfaceSlots)
		{
			CAPTURE(nOffset);
			CHECK_EQ(pOriginal[nOffset / 4], original_bnclient_address(nAddress));
		}

		// The D2MOO table is complete
		const auto pMoo = reinterpret_cast<const uintptr_t*>(QueryInterface());
		REQUIRE(pMoo != nullptr);
		CHECK_EQ(QueryInterface(), QueryInterface());
		for (uint32_t i = 0; i < sizeof(BnClientInterface) / 4; ++i)
		{
			CAPTURE(i);
			CHECK_NE(pMoo[i], 0);
		}
	}

	TEST_CASE("Bnclient.0x6FF02240 / Bnclient.0x6FF02250")
	{
		BnClientInterface* pMoo = QueryInterface();
		BnClientInterface* pOriginal = original_interface();
		CHECK_EQ(pMoo->GetVersion(), pOriginal->GetVersion());
		CHECK_EQ(pMoo->GetBuild(), pOriginal->GetBuild());
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF06740 / Bnclient.0x6FF069E0 / Bnclient.0x6FF06990")
	{
		const auto [moo_load, original_load] = make_bnclient_pair(BNNEWS_LoadBNetNews, 0x6FF06740);
		const auto [moo_free, original_free] = make_bnclient_pair(BNNEWS_FreeBNetNews, 0x6FF06990);

		// Out of order, with a message of the day (timestamp 0) and a replaced item
		const std::vector<std::vector<uint8_t>> messages = {
			news_message(3, 100, 300, { { 200, "Second" }, { 100, "First" }, { 0, "Message of the day" } }),
			news_message(2, 100, 400, { { 400, "Fourth" }, { 200, "Second, updated" } }),
			news_message(2, 150, 500, { { 300, "Third" }, { 500, "Fifth" } }),
			news_message(0, 0, 500, {}),
		};

		struct Result
		{
			BOOL bLoaded;
			std::vector<BnSendMock::Packet> packets;
			std::vector<std::vector<NewsRecorder::Item>> calls;
			BOOL bFreed;
		};

		std::vector<Result> results;
		for (const auto& [load, free, api] : { std::make_tuple(moo_load, moo_free, &moo_api()), std::make_tuple(original_load, original_free, &original_api()) })
		{
			Result result;
			BnSendMock::sent.clear();
			NewsRecorder::calls.clear();
			// The cache is not opened, so nothing is loaded and the news timestamp is 0
			result.bLoaded = load(&NewsRecorder::ItemCallback, &NewsRecorder::DoneCallback);
			result.packets = BnSendMock::sent;
			result.calls.push_back(NewsRecorder::calls);

			for (const auto& message : messages)
			{
				NewsRecorder::calls.clear();
				std::vector<uint8_t> buffer = message;
				api->BNRECV_DispatchMessage(SID_NEWS_INFO, buffer.data(), (uint32_t)buffer.size());
				result.calls.push_back(NewsRecorder::calls);
			}

			result.bFreed = free();

			// Without callbacks
			NewsRecorder::calls.clear();
			std::vector<uint8_t> buffer = messages[0];
			api->BNRECV_DispatchMessage(SID_NEWS_INFO, buffer.data(), (uint32_t)buffer.size());
			result.calls.push_back(NewsRecorder::calls);
			free();
			results.push_back(result);
		}

		CHECK_EQ(results[0].bLoaded, results[1].bLoaded);
		CHECK_EQ(results[0].bFreed, results[1].bFreed);
		CHECK_MESSAGE(results[0].packets == results[1].packets, "Comparing the SID_NEWS_INFO request");
		REQUIRE_EQ(results[0].calls.size(), results[1].calls.size());
		for (size_t i = 0; i < results[0].calls.size(); ++i)
		{
			CAPTURE(i);
			CHECK_MESSAGE(results[0].calls[i] == results[1].calls[i], "Comparing the news callbacks");
		}

		REQUIRE_EQ(results[0].packets.size(), 1);
		CHECK_EQ(results[0].packets[0].nMessageId, SID_NEWS_INFO);
		CHECK_EQ(results[0].packets[0].data, std::vector<uint8_t>(4, 0));

		// Newest first, after the done callback
		const std::vector<NewsRecorder::Item> expected = {
			{ NewsRecorder::DONE, "" }, { 500, "Fifth" }, { 400, "Fourth" }, { 300, "Third" }, { 200, "Second, updated" },
		};
		CHECK_MESSAGE(results[0].calls[3] == expected, "Checking the news after the third message");
		CHECK(results[0].calls.back().empty());
	}
}
