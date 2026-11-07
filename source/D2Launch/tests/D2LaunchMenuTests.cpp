#include <doctest.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <StormStorageMocks.h>

#include <BNet.h>
#include <CharSel.h>
#include <MainMenus.h>

#include "D2LaunchTestFixtures.h"


extern D2ShardStrc** sgptShardArray;
extern int32_t sgnShardListSize;
extern BOOL sgbConnectionCancelled;
extern BOOL sgbLoggedIn;
extern char sgszPreferredRealmName[256];


namespace
{
template<class Fixture>
struct D2LaunchStorageFixture : D2LaunchStormFixture<Fixture>
{
	D2LaunchStorageFixture()
	{
		hook_storm_storage_mocks(this->hooks);
	}

	~D2LaunchStorageFixture()
	{
		StormStorageMock::reset();
	}
};

struct RealmListApi
{
	decltype(&MENU_GetRealmCount) GetRealmCount;
	decltype(&MENU_GetRealmName) GetRealmName;
	decltype(&MENU_FreeRealmList) FreeRealmList;
	D2ShardStrc*** pppShardArray;
	int32_t* pnShardListSize;
};

const RealmListApi& moo_realm_list_api()
{
	static const RealmListApi api = { &MENU_GetRealmCount, &MENU_GetRealmName, &MENU_FreeRealmList, &sgptShardArray, &sgnShardListSize };
	return api;
}

const RealmListApi& original_realm_list_api()
{
	static const RealmListApi api = {
		reinterpret_cast<decltype(&MENU_GetRealmCount)>(original_d2launch_address(0x6FA1D140)),
		reinterpret_cast<decltype(&MENU_GetRealmName)>(original_d2launch_address(0x6FA1D150)),
		reinterpret_cast<decltype(&MENU_FreeRealmList)>(original_d2launch_address(0x6FA1D010)),
		original_d2launch_global<D2ShardStrc**>(0x6FA3D0FC),
		original_d2launch_global<int32_t>(0x6FA3D100),
	};
	return api;
}

char* duplicate(const char* szString)
{
	char* szCopy = static_cast<char*>(std::malloc(std::strlen(szString) + 1));
	std::strcpy(szCopy, szString);
	return szCopy;
}

// Shard list allocated with the mocked Fog allocator (malloc), so that MENU_FreeRealmList can free it
D2ShardStrc** make_shard_array(const std::vector<std::pair<const char*, const char*>>& shards)
{
	auto ppShards = static_cast<D2ShardStrc**>(std::calloc(shards.size() + 1, sizeof(D2ShardStrc*)));
	for (size_t i = 0; i < shards.size(); ++i)
	{
		ppShards[i] = static_cast<D2ShardStrc*>(std::malloc(sizeof(D2ShardStrc)));
		ppShards[i]->pszName = duplicate(shards[i].first);
		ppShards[i]->pszDescription = duplicate(shards[i].second);
	}
	return ppShards;
}
}


TEST_SUITE("D2LaunchMenuTests")
{
	TEST_CASE("D2Launch.0x6FA1D0F0")
	{
		const auto [sut, original] = make_d2launch_pair(MENU_CompareShards, 0x6FA1D0F0);

		const char* szNames[] = { "", "USEast", "USWest", "Europe", "Asia", "useast", "USEast2", "U" };
		for (const char* szLeft : szNames)
		{
			for (const char* szRight : szNames)
			{
				CAPTURE(szLeft);
				CAPTURE(szRight);
				D2ShardStrc left = { const_cast<char*>(szLeft), const_cast<char*>("") };
				D2ShardStrc right = { const_cast<char*>(szRight), const_cast<char*>("") };
				const D2ShardStrc* pLeft = &left;
				const D2ShardStrc* pRight = &right;
				const int moo_result = sut(&pLeft, &pRight);
				const int original_result = original(&pLeft, &pRight);
				// Only the sign is meaningful for qsort
				CHECK_EQ((moo_result > 0) - (moo_result < 0), (original_result > 0) - (original_result < 0));
			}
		}

		// Sorting with both comparators gives the same order
		std::vector<D2ShardStrc> shards;
		for (const char* szName : szNames)
		{
			shards.push_back({ const_cast<char*>(szName), const_cast<char*>("") });
		}
		std::vector<D2ShardStrc*> moo_sorted, original_sorted;
		for (auto& shard : shards)
		{
			moo_sorted.push_back(&shard);
			original_sorted.push_back(&shard);
		}
		std::qsort(moo_sorted.data(), moo_sorted.size(), sizeof(D2ShardStrc*), sut);
		std::qsort(original_sorted.data(), original_sorted.size(), sizeof(D2ShardStrc*), original);
		CHECK_MESSAGE(moo_sorted == original_sorted, "Comparing the sorted shards");
	}

	TEST_CASE_FIXTURE(D2LaunchStormFixture<NoOpFixture>, "D2Launch.0x6FA1D140 / D2Launch.0x6FA1D150 / D2Launch.0x6FA1D010")
	{
		const std::vector<std::pair<const char*, const char*>> shards = { { "Asia", "Asian realm" }, { "Europe", "European realm" }, { "USEast", "" } };

		struct Result
		{
			int32_t nCountWithoutList;
			BOOL bFreedWithoutList;
			int32_t nCount;
			std::vector<std::string> names;
			BOOL bFreed;
			bool bArrayCleared;
			int32_t nCountAfterFree;
		};

		std::vector<Result> results;
		for (const RealmListApi* pApi : { &moo_realm_list_api(), &original_realm_list_api() })
		{
			const RealmListApi& api = *pApi;
			Result result = {};

			// No list was requested
			*api.pppShardArray = nullptr;
			*api.pnShardListSize = -1;
			result.nCountWithoutList = api.GetRealmCount();
			result.bFreedWithoutList = api.FreeRealmList();

			*api.pppShardArray = make_shard_array(shards);
			*api.pnShardListSize = (int32_t)shards.size();
			result.nCount = api.GetRealmCount();
			for (int32_t i = 0; i < result.nCount; ++i)
			{
				result.names.emplace_back(api.GetRealmName(i));
			}

			result.bFreed = api.FreeRealmList();
			result.bArrayCleared = *api.pppShardArray == nullptr;
			result.nCountAfterFree = api.GetRealmCount();

			*api.pppShardArray = nullptr;
			*api.pnShardListSize = 0;
			results.push_back(result);
		}

		CHECK_EQ(results[0].nCountWithoutList, results[1].nCountWithoutList);
		CHECK_EQ(results[0].bFreedWithoutList, results[1].bFreedWithoutList);
		CHECK_EQ(results[0].nCount, results[1].nCount);
		CHECK_EQ(results[0].names, results[1].names);
		CHECK_EQ(results[0].bFreed, results[1].bFreed);
		CHECK_EQ(results[0].bArrayCleared, results[1].bArrayCleared);
		CHECK_EQ(results[0].nCountAfterFree, results[1].nCountAfterFree);

		CHECK_EQ(results[0].names, std::vector<std::string>{ "Asia", "Europe", "USEast" });
		CHECK(results[0].bArrayCleared);
	}

	TEST_CASE("D2Launch.0x6FA1F5B0")
	{
		const auto [sut, original] = make_d2launch_pair(MENU_ByteSwapUnicodeString, 0x6FA1F5B0);

		for (const uint32_t nLength : { 0u, 1u, 7u, 32u })
		{
			CAPTURE(nLength);
			std::vector<Unicode> moo_string(40), original_string(40);
			for (size_t i = 0; i < moo_string.size(); ++i)
			{
				const uint16_t nChar = (uint16_t)(0x1234 + i * 0x0F31);
				moo_string[i] = nChar;
				original_string[i] = nChar;
			}

			sut(moo_string.data(), nLength);
			original(original_string.data(), nLength);

			for (size_t i = 0; i < moo_string.size(); ++i)
			{
				CAPTURE(i);
				CHECK_EQ((uint16_t)moo_string[i], (uint16_t)original_string[i]);
			}
			if (nLength > 0)
			{
				CHECK_EQ((uint16_t)moo_string[0], 0x3412);
			}
		}
	}

	TEST_CASE_FIXTURE(D2LaunchStorageFixture<NoOpFixture>, "D2Launch.0x6FA1E600")
	{
		const auto [sut, original] = make_d2launch_pair(MENU_ShouldPlayExpansionIntro, 0x6FA1E600);

		// The unlocked cinematics are stored in the last number of "Aux Battle.net"
		for (const char* szValue : { (const char*)nullptr, "", "0.0.0.0", "1.2.3.16", "1.2.3.144", "1.2.3.31", "1.2.3.255", "1.2.3.272", "1.2.3", "garbage", "4.5.6.-16", "127.0.0.1" })
		{
			CAPTURE(szValue ? szValue : "(none)");
			StormStorageMock::reset();
			if (szValue)
			{
				StormStorageMock::set_registry_string("Diablo II", "Aux Battle.net", szValue);
			}

			CHECK_EQ(sut(), original());
		}

		StormStorageMock::reset();
		StormStorageMock::set_registry_string("Diablo II", "Aux Battle.net", "1.2.3.16");
		CHECK_EQ(sut(), TRUE);
		StormStorageMock::set_registry_string("Diablo II", "Aux Battle.net", "1.2.3.144");
		CHECK_EQ(sut(), FALSE);
	}

	TEST_CASE("D2Launch.0x6FA110E0 / D2Launch.0x6FA110F0 / D2Launch.0x6FA11100 / D2Launch.0x6FA11110")
	{
		const auto [moo_cancel, original_cancel] = make_d2launch_pair(BNET_CancelConnection, 0x6FA110E0);
		const auto [moo_reset, original_reset] = make_d2launch_pair(BNET_ResetConnectionCancelled, 0x6FA110F0);
		const auto [moo_is_cancelled, original_is_cancelled] = make_d2launch_pair(BNET_IsConnectionCancelled, 0x6FA11100);
		const auto [moo_is_logged_in, original_is_logged_in] = make_d2launch_pair(BNET_IsLoggedIn, 0x6FA11110);

		BOOL* pbOriginalCancelled = original_d2launch_global<BOOL>(0x6FA3B808);
		BOOL* pbOriginalLoggedIn = original_d2launch_global<BOOL>(0x6FA3B80C);
		const BOOL bMooCancelled = sgbConnectionCancelled, bOriginalCancelled = *pbOriginalCancelled;
		const BOOL bMooLoggedIn = sgbLoggedIn, bOriginalLoggedIn = *pbOriginalLoggedIn;

		sgbConnectionCancelled = 7;
		*pbOriginalCancelled = 7;
		CHECK_EQ(moo_is_cancelled(), original_is_cancelled());
		moo_cancel();
		original_cancel();
		CHECK_EQ(sgbConnectionCancelled, *pbOriginalCancelled);
		CHECK_EQ(moo_is_cancelled(), original_is_cancelled());
		CHECK_EQ(moo_is_cancelled(), TRUE);
		moo_reset();
		original_reset();
		CHECK_EQ(sgbConnectionCancelled, *pbOriginalCancelled);
		CHECK_EQ(moo_is_cancelled(), FALSE);

		for (const BOOL bLoggedIn : { FALSE, TRUE, 5 })
		{
			sgbLoggedIn = bLoggedIn;
			*pbOriginalLoggedIn = bLoggedIn;
			CHECK_EQ(moo_is_logged_in(), original_is_logged_in());
		}

		sgbConnectionCancelled = bMooCancelled;
		*pbOriginalCancelled = bOriginalCancelled;
		sgbLoggedIn = bMooLoggedIn;
		*pbOriginalLoggedIn = bOriginalLoggedIn;
	}

	TEST_CASE("D2Launch.0x6FA13AE0")
	{
		const auto [sut, original] = make_d2launch_pair(CHARSEL_GetPreferredRealmName, 0x6FA13AE0);
		CHECK_EQ(sut(), sgszPreferredRealmName);
		CHECK_EQ(reinterpret_cast<uintptr_t>(original()), original_d2launch_address(0x6FA3C7D8));
	}
}
