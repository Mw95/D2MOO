#include <doctest.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include <Grid.h>
#include <BnRecv.h>
#include <BnSend.h>

#include "BnclientTestFixtures.h"


namespace
{
using Packets = std::vector<BnSendMock::Packet>;

struct SendResult
{
	int nResult = 0;
	Packets packets;
};

// Runs the call on both implementations. The connection is marked as disconnected so that requests waiting for an answer return right away.
std::vector<SendResult> run_both(const std::function<int(const BnclientApi&)>& call, bool bExpansion = true)
{
	std::vector<SendResult> results;
	for_each_api([&](const BnclientApi& api)
	{
		api.BNRECV_ResetAllMessages();
		api.BNRECV_SetDisconnected();
		BnSendMock::sent.clear();
		BnSendMock::bExpansion = bExpansion;

		SendResult result;
		result.nResult = call(api);
		result.packets = BnSendMock::sent;
		results.push_back(result);

		api.BNRECV_ResetAllMessages();
	});
	return results;
}

// Compares the packets and the return values of both implementations, and returns the D2MOO packets
Packets compare_send(const std::function<int(const BnclientApi&)>& call, bool bExpansion = true)
{
	const auto results = run_both(call, bExpansion);
	CHECK_EQ(results[0].nResult, results[1].nResult);
	REQUIRE_EQ(results[0].packets.size(), results[1].packets.size());
	for (size_t i = 0; i < results[0].packets.size(); ++i)
	{
		CAPTURE(i);
		CHECK_EQ(results[0].packets[i].nMessageId, results[1].packets[i].nMessageId);
		CHECK_MESSAGE(results[0].packets[i].data == results[1].packets[i].data, "Comparing the packet bytes");
	}
	return results[0].packets;
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

uint32_t read_u32(const std::vector<uint8_t>& data, size_t nOffset)
{
	uint32_t nValue = 0;
	std::memcpy(&nValue, &data[nOffset], sizeof(nValue));
	return nValue;
}

std::vector<uint8_t> xsha(const void* pData, size_t nSize)
{
	std::vector<uint8_t> hash(20);
	GRID_XSHA(hash.data(), pData, (uint32_t)nSize);
	return hash;
}

std::string lowercase(std::string szString)
{
	std::transform(szString.begin(), szString.end(), szString.begin(), [](char c) { return (char)std::tolower((unsigned char)c); });
	return szString;
}

// Hash of a password sent by Battle.net logons: XSHA(client token, server token, XSHA(password))
std::vector<uint8_t> password_proof(uint32_t nClientToken, uint32_t nServerToken, const std::string& szPassword)
{
	const auto passwordHash = xsha(szPassword.data(), szPassword.size());
	const auto data = u32(nClientToken) + u32(nServerToken) + passwordHash;
	return xsha(data.data(), data.size());
}

std::vector<uint8_t> slice(const std::vector<uint8_t>& data, size_t nOffset, size_t nSize)
{
	return std::vector<uint8_t>(data.begin() + nOffset, data.begin() + nOffset + nSize);
}
}


TEST_SUITE("BnclientSendTests")
{
	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF071C0")
	{
		// The client token is the tick count, so the packets are checked one by one
		const auto results = run_both([](const BnclientApi& api)
		{
			api.BNSEND_SetServerToken(0x0BADF00D);
			return api.BNSEND_LogonResponse2("Account", "PassWord");
		});

		for (const SendResult& result : results)
		{
			CHECK_EQ(result.nResult, TRUE);
			REQUIRE_EQ(result.packets.size(), 1);
			const auto& packet = result.packets[0];
			CHECK_EQ(packet.nMessageId, SID_LOGONRESPONSE2);
			REQUIRE_EQ(packet.data.size(), 8 + 20 + 8);
			CHECK_EQ(read_u32(packet.data, 4), 0x0BADF00D);
			// The password is lowercased
			CHECK_MESSAGE(slice(packet.data, 8, 20) == password_proof(read_u32(packet.data, 0), 0x0BADF00D, "password"), "Checking the password proof");
			CHECK_MESSAGE(slice(packet.data, 28, 8) == str("Account"), "Checking the account name");
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07280")
	{
		const auto packets = compare_send([](const BnclientApi& api) { return api.BNSEND_CreateAccount2("NewAccount", "SeCrEt"); });
		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_CREATEACCOUNT2);
		CHECK_MESSAGE(packets[0].data == xsha("secret", 6) + str("NewAccount"), "Checking the packet");
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07300")
	{
		const auto results = run_both([](const BnclientApi& api)
		{
			api.BNSEND_SetServerToken(0x31415926);
			return api.BNSEND_ChangePassword("Account", "OldPass", "NewPass");
		});

		for (const SendResult& result : results)
		{
			CHECK_EQ(result.nResult, TRUE);
			REQUIRE_EQ(result.packets.size(), 1);
			const auto& packet = result.packets[0];
			CHECK_EQ(packet.nMessageId, SID_CHANGEPASSWORD);
			REQUIRE_EQ(packet.data.size(), 8 + 20 + 20 + 8);
			CHECK_EQ(read_u32(packet.data, 4), 0x31415926);
			CHECK_MESSAGE(slice(packet.data, 8, 20) == password_proof(read_u32(packet.data, 0), 0x31415926, "oldpass"), "Checking the old password proof");
			CHECK_MESSAGE(slice(packet.data, 28, 20) == xsha("newpass", 7), "Checking the new password hash");
			CHECK_MESSAGE(slice(packet.data, 48, 8) == str("Account"), "Checking the account name");
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF073F0 / Bnclient.0x6FF07510")
	{
		const std::vector<uint8_t> realms = u32(0) + u32(2) + u32(1) + str("Europe") + str("Description");

		std::vector<std::vector<uint8_t>> lists;
		const auto packets = compare_send([&](const BnclientApi& api)
		{
			api.BNSEND_StoreRealmList(realms.data(), (uint32_t)realms.size());
			const auto pList = static_cast<const uint8_t*>(api.BNSEND_QueryRealms(0));
			lists.push_back(pList ? std::vector<uint8_t>(pList, pList + realms.size()) : std::vector<uint8_t>());
			return pList != nullptr;
		});

		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_QUERYREALMS2);
		CHECK(packets[0].data.empty());
		CHECK_EQ(lists[0], lists[1]);
		CHECK_EQ(lists[0], realms);

		SUBCASE("The send fails")
		{
			BnSendMock::nSendResult = 0;
			compare_send([](const BnclientApi& api) { return api.BNSEND_QueryRealms(0) != nullptr; });
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07470 / Bnclient.0x6FF074C0")
	{
		const std::vector<uint8_t> adUrl = u32(77) + str("http://www.example.com/");

		std::vector<std::string> urls;
		const auto packets = compare_send([&](const BnclientApi& api)
		{
			api.BNSEND_StoreAdUrl(adUrl.data(), (uint32_t)adUrl.size());
			const char* szUrl = api.BNSEND_QueryAdUrl(77);
			urls.push_back(szUrl ? szUrl : "(null)");
			return szUrl != nullptr;
		});

		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_QUERYADURL);
		CHECK_EQ(packets[0].data, u32(77));
		CHECK_EQ(urls[0], urls[1]);
		CHECK_EQ(urls[0], "http://www.example.com/");
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07550 / Bnclient.0x6FF075B0 / Bnclient.0x6FF075E0")
	{
		const std::vector<uint8_t> channels = str("Diablo II") + str("Op Help") + str("");

		for (const bool bExpansion : { true, false })
		{
			for (const BOOL bClassic : { TRUE, FALSE })
			{
				CAPTURE(bExpansion);
				CAPTURE(bClassic);
				std::vector<std::vector<uint8_t>> lists;
				const auto packets = compare_send([&](const BnclientApi& api)
				{
					api.BNSEND_StoreChannelList(channels.data(), (uint32_t)channels.size());
					const auto pList = static_cast<const uint8_t*>(api.BNSEND_GetChannelList(bClassic));
					lists.push_back(pList ? std::vector<uint8_t>(pList, pList + channels.size()) : std::vector<uint8_t>());

					api.BNSEND_FreeChannelList();
					const bool bFreed = api.BNSEND_GetChannelList(bClassic) == nullptr;
					return bFreed ? 1 : 0;
				}, bExpansion);

				REQUIRE_EQ(packets.size(), 2);
				CHECK_EQ(packets[0].nMessageId, SID_GETCHANNELLIST);
				CHECK_EQ(packets[0].data, u32(bExpansion && !bClassic ? 1 : 0));
				CHECK_EQ(lists[0], lists[1]);
				CHECK_EQ(lists[0], channels);
			}
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07630")
	{
		for (const bool bExpansion : { true, false })
		{
			for (const BOOL bForced : { TRUE, FALSE })
			{
				for (const BOOL bClassic : { TRUE, FALSE })
				{
					for (const char* szChannel : { "Some Channel", "", (const char*)nullptr })
					{
						CAPTURE(bExpansion);
						CAPTURE(bForced);
						CAPTURE(bClassic);
						CAPTURE(szChannel ? szChannel : "(null)");
						const auto packets = compare_send([&](const BnclientApi& api) { return api.BNSEND_JoinChannel(szChannel, bForced, bClassic); }, bExpansion);
						REQUIRE_EQ(packets.size(), 1);
						CHECK_EQ(packets[0].nMessageId, SID_JOINCHANNEL);
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF076D0")
	{
		for (const bool bExpansion : { true, false })
		{
			CAPTURE(bExpansion);
			const auto packets = compare_send([](const BnclientApi& api) { return api.BNSEND_EnterChat("Character", "PX2DRealm,Character,statstring", 0x25); }, bExpansion);
			REQUIRE_EQ(packets.size(), 2);
			CHECK_EQ(packets[0].nMessageId, SID_GETCHANNELLIST);
			CHECK_EQ(packets[0].data, u32(bExpansion ? 'D2XP' : 'D2DV'));
			CHECK_EQ(packets[1].nMessageId, SID_ENTERCHAT);
			CHECK_EQ(packets[1].data, str("Character") + str("PX2DRealm,Character,statstring"));
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF077A0 / Bnclient.0x6FF079C0 / Bnclient.0x6FF079E0")
	{
		const std::pair<int(*)(const BnclientApi&), uint8_t> calls[] = {
			{ [](const BnclientApi& api) { return api.BNSEND_LeaveChat(); }, SID_LEAVECHAT },
			{ [](const BnclientApi& api) { return api.BNSEND_StopAdv(); }, SID_STOPADV },
			{ [](const BnclientApi& api) { return api.BNSEND_LeaveGame(); }, SID_LEAVEGAME },
		};

		for (const auto& [call, nMessageId] : calls)
		{
			CAPTURE(nMessageId);
			const auto packets = compare_send(call);
			REQUIRE_EQ(packets.size(), 1);
			CHECK_EQ(packets[0].nMessageId, nMessageId);
			CHECK(packets[0].data.empty());
		}

		SUBCASE("The send fails")
		{
			BnSendMock::nSendResult = 0;
			for (const auto& [call, nMessageId] : calls)
			{
				compare_send(call);
			}
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07860 / Bnclient.0x6FF078B0")
	{
		for (const bool bExpansion : { true, false })
		{
			CAPTURE(bExpansion);

			// The last value of SID_CHECKAD is the current time
			const auto results = run_both([](const BnclientApi& api) { return api.BNSEND_CheckAd(); }, bExpansion);
			for (const SendResult& result : results)
			{
				REQUIRE_EQ(result.packets.size(), 1);
				CHECK_EQ(result.packets[0].nMessageId, SID_CHECKAD);
				REQUIRE_EQ(result.packets[0].data.size(), 16);
			}
			CHECK_EQ(slice(results[0].packets[0].data, 0, 12), slice(results[1].packets[0].data, 0, 12));
			CHECK_EQ(read_u32(results[0].packets[0].data, 0), 'IX86');
			CHECK_EQ(read_u32(results[0].packets[0].data, 4), bExpansion ? 'D2XP' : 'D2DV');

			const auto packets = compare_send([](const BnclientApi& api) { return api.BNSEND_DisplayAd("file.pcx", "http://link"); }, bExpansion);
			REQUIRE_EQ(packets.size(), 1);
			CHECK_EQ(packets[0].nMessageId, SID_DISPLAYAD);
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07910")
	{
		for (const char* szPassword : { "", "pass", (const char*)nullptr })
		{
			CAPTURE(szPassword ? szPassword : "(null)");
			const auto packets = compare_send([&](const BnclientApi& api) { return api.BNSEND_StartAdvEx3("Game", szPassword, "statstring", 0x12); });
			REQUIRE_EQ(packets.size(), 1);
			CHECK_EQ(packets[0].nMessageId, SID_STARTADVEX3);
		}

		const auto packets = compare_send([](const BnclientApi& api) { return api.BNSEND_StartAdvEx3(nullptr, nullptr, nullptr, 0); });
		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].data, u32(0) + u32(0) + u32(0) + u32(0) + u32(0) + str("") + str("") + str(""));
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07A00")
	{
		for (const uint32_t nResult : { 0u, 1u })
		{
			std::vector<std::pair<BOOL, int32_t>> results;
			for_each_api([&](const BnclientApi& api)
			{
				api.BNRECV_ResetAllMessages();
				int32_t nCreateGameResult = -1;
				const BOOL bBefore = api.BNSEND_GetCreateGameResult(&nCreateGameResult);
				results.emplace_back(bBefore, nCreateGameResult);

				std::vector<uint8_t> data = u32(nResult) + u32(0);
				api.BNRECV_DispatchMessage(SID_STARTADVEX3, data.data(), 4);
				const BOOL bAfter = api.BNSEND_GetCreateGameResult(&nCreateGameResult);
				results.emplace_back(bAfter, nCreateGameResult);
				api.BNRECV_ResetAllMessages();
			});

			CHECK_EQ(results[0], results[2]);
			CHECK_EQ(results[1], results[3]);
			CHECK_EQ(results[1], std::make_pair(TRUE, nResult == 0 ? 1 : 0));
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07A20 / Bnclient.0x6FF07A80 / Bnclient.0x6FF07AB0")
	{
		const std::vector<uint8_t> games = u32(1) + u32(0) + u32(0) + str("Game") + str("") + str("stats");

		for (const char* szPassword : { "pass", (const char*)nullptr })
		{
			std::vector<std::vector<uint8_t>> lists;
			const auto packets = compare_send([&](const BnclientApi& api)
			{
				api.BNSEND_StoreGameList(games.data(), (uint32_t)games.size());
				const auto pList = static_cast<const uint8_t*>(api.BNSEND_GetGameList("Game", szPassword, 1, 2));
				lists.push_back(pList ? std::vector<uint8_t>(pList, pList + games.size()) : std::vector<uint8_t>());
				api.BNSEND_FreeGameList();
				return 1;
			});

			REQUIRE_EQ(packets.size(), 1);
			CHECK_EQ(packets[0].nMessageId, SID_GETADVLISTEX);
			CHECK_EQ(packets[0].data, u32(0) + u32(0) + u32(0) + u32(25) + str("Game") + str(szPassword ? szPassword : "") + str(""));
			CHECK_EQ(lists[0], lists[1]);
			CHECK_EQ(lists[0], games);
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07B60")
	{
		for (const bool bExpansion : { true, false })
		{
			CAPTURE(bExpansion);
			const auto packets = compare_send([](const BnclientApi& api) { return api.BNSEND_NotifyJoin("Game", "pw"); }, bExpansion);
			REQUIRE_EQ(packets.size(), 1);
			CHECK_EQ(packets[0].nMessageId, SID_NOTIFYJOIN);
			CHECK_EQ(packets[0].data, u32(bExpansion ? 'D2XP' : 'D2DV') + u32(10) + str("Game") + str("pw"));
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07BD0 / Bnclient.0x6FF07C60")
	{
		// Answer of SID_LOGONREALMEX: 16 DWORDs then the unique name
		std::vector<uint8_t> logon;
		for (uint32_t i = 0; i < 16; ++i)
		{
			logon = logon + u32(0x01010101 * (i + 1));
		}
		logon = logon + str("Unique#Name");

		for (const auto& answer : { logon, u32(1) + u32(2) })
		{
			CAPTURE(answer.size());
			std::vector<std::vector<uint8_t>> infos;
			const auto results = run_both([&](const BnclientApi& api)
			{
				api.BNSEND_SetServerToken(0x55667788);
				api.BNSEND_StoreRealmLogonInformation(answer.data(), (uint32_t)answer.size());
				const auto pInfo = api.BNSEND_LogonRealm("Europe", "password");
				const auto pBytes = reinterpret_cast<const uint8_t*>(pInfo);
				infos.push_back(pBytes ? std::vector<uint8_t>(pBytes, pBytes + 4 + answer.size()) : std::vector<uint8_t>());
				return pInfo != nullptr;
			});

			CHECK_EQ(results[0].nResult, results[1].nResult);
			CHECK_EQ(infos[0], infos[1]);
			REQUIRE_EQ(infos[0].size(), 4 + answer.size());
			CHECK_EQ(read_u32(infos[0], 0), answer.size());

			// The client token is a counter specific to each implementation
			for (const SendResult& result : results)
			{
				REQUIRE_EQ(result.packets.size(), 1);
				const auto& packet = result.packets[0];
				CHECK_EQ(packet.nMessageId, SID_LOGONREALMEX);
				REQUIRE_EQ(packet.data.size(), 4 + 20 + 7);
				CHECK_MESSAGE(slice(packet.data, 4, 20) == password_proof(read_u32(packet.data, 0), 0x55667788, "password"), "Checking the realm password proof");
				CHECK_EQ(slice(packet.data, 24, 7), str("Europe"));
			}
		}

		SUBCASE("No realm")
		{
			compare_send([](const BnclientApi& api) { return api.BNSEND_LogonRealm(nullptr, "password") != nullptr; });
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07D10")
	{
		for (const BOOL bClicked : { 0, 1, 5 })
		{
			const auto packets = compare_send([&](const BnclientApi& api) { return api.BNSEND_ClickAd(0x1234, bClicked); });
			REQUIRE_EQ(packets.size(), 1);
			CHECK_EQ(packets[0].nMessageId, SID_CLICKAD);
			CHECK_EQ(packets[0].data, u32(0x1234) + u32(bClicked ? 1 : 0));
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07D40")
	{
		const char* keys[] = { "profile\\sex", "profile\\age" };
		const char* values[] = { "", "42" };
		const auto packets = compare_send([&](const BnclientApi& api) { return api.BNSEND_WriteUserData("Account", 2, keys, values); });
		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_WRITEUSERDATA);
		CHECK_EQ(packets[0].data, u32(1) + u32(2) + str("Account") + str(keys[0]) + str(keys[1]) + str(values[0]) + str(values[1]));
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07E90 / Bnclient.0x6FF07E40 / Bnclient.0x6FF07F50")
	{
		const char* keys[] = { "profile\\location", "profile\\description", "System\\Username" };
		const auto packets = compare_send([&](const BnclientApi& api) { return api.BNSEND_RequestUserData("Account", 3, 0x4242, keys); });
		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_READUSERDATA);
		CHECK_EQ(packets[0].data, u32(1) + u32(3) + u32(0x4242) + str("Account") + str(keys[0]) + str(keys[1]) + str(keys[2]));

		struct Result
		{
			BOOL bWithoutAnswer;
			BOOL bWrongRequest;
			BOOL bResult;
			std::vector<std::string> values;
		};

		const std::vector<uint8_t> answer = u32(1) + u32(3) + u32(0x4242) + str("Somewhere") + str("") + str("A long description");
		std::vector<Result> results;
		for_each_api([&](const BnclientApi& api)
		{
			Result result = {};
			char szValue1[32], szValue2[32], szValue3[8];
			char* pValues[] = { szValue1, szValue2, szValue3 };
			const uint32_t pSizes[] = { 31, 31, 7 };

			api.BNRECV_ResetAllMessages();
			result.bWithoutAnswer = api.BNSEND_GetUserData(3, 0x4242, pValues, pSizes);

			// Stored by the handler of SID_READUSERDATA
			std::vector<uint8_t> buffer = answer;
			api.BNRECV_DispatchMessage(SID_READUSERDATA, buffer.data(), (uint32_t)buffer.size());
			result.bWrongRequest = api.BNSEND_GetUserData(3, 0x4243, pValues, pSizes);
			result.bResult = api.BNSEND_GetUserData(3, 0x4242, pValues, pSizes);
			for (char* szValue : pValues)
			{
				result.values.emplace_back(szValue);
			}
			api.BNRECV_ResetAllMessages();
			results.push_back(result);
		});

		for (size_t i = 0; i < 2; ++i)
		{
			CHECK_EQ(results[i].bWithoutAnswer, FALSE);
			CHECK_EQ(results[i].bWrongRequest, FALSE);
			CHECK_EQ(results[i].bResult, TRUE);
		}
		CHECK_EQ(results[0].values, results[1].values);
		CHECK_EQ(results[0].values, std::vector<std::string>{ "Somewhere", "", "A long " });
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF07FF0 / Bnclient.0x6FF08060 / Bnclient.0x6FF08180")
	{
		auto packets = compare_send([](const BnclientApi& api) { return api.BNSEND_SetEmail("me@example.com"); });
		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_SETEMAIL);
		CHECK_EQ(packets[0].data, str("me@example.com"));

		packets = compare_send([](const BnclientApi& api) { return api.BNSEND_ResetPassword("Account", "me@example.com"); });
		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_RESETPASSWORD);
		CHECK_EQ(packets[0].data, str("Account") + str("me@example.com"));

		packets = compare_send([](const BnclientApi& api) { return api.BNSEND_ChangeEmail("Account", "old@example.com", "new@example.com"); });
		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_CHANGEEMAIL);
		CHECK_EQ(packets[0].data, str("Account") + str("old@example.com") + str("new@example.com"));

		SUBCASE("Missing e-mail addresses")
		{
			CHECK(compare_send([](const BnclientApi& api) { return api.BNSEND_ResetPassword("Account", ""); }).empty());
			CHECK(compare_send([](const BnclientApi& api) { return api.BNSEND_ResetPassword("Account", nullptr); }).empty());
			CHECK(compare_send([](const BnclientApi& api) { return api.BNSEND_ChangeEmail("Account", "", "new@example.com"); }).empty());
			CHECK(compare_send([](const BnclientApi& api) { return api.BNSEND_ChangeEmail("Account", "old@example.com", nullptr); }).empty());
		}

		SUBCASE("The send fails")
		{
			BnSendMock::nSendResult = 0;
			compare_send([](const BnclientApi& api) { return api.BNSEND_SetEmail("me@example.com"); });
			compare_send([](const BnclientApi& api) { return api.BNSEND_ResetPassword("Account", "me@example.com"); });
		}
	}

	TEST_CASE_FIXTURE(BnclientSendFixture<NoOpFixture>, "Bnclient.0x6FF02720")
	{
		// SID_PING is answered with the same data
		const auto packets = compare_send([](const BnclientApi& api)
		{
			std::vector<uint8_t> data = u32(0xA5A55A5A);
			api.BNRECV_DispatchMessage(SID_PING, data.data(), (uint32_t)data.size());
			return 1;
		});
		REQUIRE_EQ(packets.size(), 1);
		CHECK_EQ(packets[0].nMessageId, SID_PING);
		CHECK_EQ(packets[0].data, u32(0xA5A55A5A));
	}
}
