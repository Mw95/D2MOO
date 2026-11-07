#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <CharSel.h>

#include "D2LaunchTestFixtures.h"


extern D2RealmCharListCacheStrc* sgpRealmCharListCache;


namespace
{
struct CharSelApi
{
	decltype(&CHARSEL_GetCachedRealmCharList) GetCachedRealmCharList;
	decltype(&CHARSEL_CacheRealmCharList) CacheRealmCharList;
	decltype(&CHARSEL_FreeRealmCharListCache) FreeRealmCharListCache;
	D2RealmCharListCacheStrc** ppCache;
};

const CharSelApi& moo_charsel_api()
{
	static const CharSelApi api = { &CHARSEL_GetCachedRealmCharList, &CHARSEL_CacheRealmCharList, &CHARSEL_FreeRealmCharListCache, &sgpRealmCharListCache };
	return api;
}

const CharSelApi& original_charsel_api()
{
	static const CharSelApi api = {
		reinterpret_cast<decltype(&CHARSEL_GetCachedRealmCharList)>(original_d2launch_address(0x6FA12FC0)),
		reinterpret_cast<decltype(&CHARSEL_CacheRealmCharList)>(original_d2launch_address(0x6FA13000)),
		reinterpret_cast<decltype(&CHARSEL_FreeRealmCharListCache)>(original_d2launch_address(0x6FA130E0)),
		original_d2launch_global<D2RealmCharListCacheStrc*>(0x6FA3CA88),
	};
	return api;
}

std::vector<uint8_t> cached(const CharSelApi& api, const char* szRealmName, size_t nSize)
{
	const uint8_t* pPacket = api.GetCachedRealmCharList(szRealmName);
	return pPacket ? std::vector<uint8_t>(pPacket, pPacket + nSize) : std::vector<uint8_t>();
}

// Number of entries and their sizes are not visible, so the list is walked
size_t cache_entries(const CharSelApi& api)
{
	size_t nEntries = 0;
	for (const D2RealmCharListCacheStrc* pCache = *api.ppCache; pCache; pCache = pCache->pNext)
	{
		++nEntries;
	}
	return nEntries;
}
}


TEST_SUITE("D2LaunchCharSelTests")
{
	TEST_CASE_FIXTURE(D2LaunchStormFixture<NoOpFixture>, "D2Launch.0x6FA12FC0 / D2Launch.0x6FA13000 / D2Launch.0x6FA130E0")
	{
		const std::vector<uint8_t> packet1 = { 0x19, 1, 0, 2, 3, 4, 5, 6, 7 };
		const std::vector<uint8_t> packet2 = { 0x19, 9, 8, 7 };
		const std::vector<uint8_t> packet3 = { 0x17, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE };

		struct Result
		{
			std::vector<std::vector<uint8_t>> lists;
			std::vector<size_t> entries;
		};

		std::vector<Result> results;
		for (const CharSelApi* pApi : { &moo_charsel_api(), &original_charsel_api() })
		{
			const CharSelApi& api = *pApi;
			Result result;
			api.FreeRealmCharListCache();
			result.lists.push_back(cached(api, "USEast", packet1.size()));

			api.CacheRealmCharList("USEast", packet1.data(), packet1.size());
			api.CacheRealmCharList("Europe", packet3.data(), packet3.size());
			result.entries.push_back(cache_entries(api));
			result.lists.push_back(cached(api, "USEast", packet1.size()));
			result.lists.push_back(cached(api, "Europe", packet3.size()));
			result.lists.push_back(cached(api, "USWest", packet1.size()));

			// Replaces the cached list of the realm
			api.CacheRealmCharList("USEast", packet2.data(), packet2.size());
			result.entries.push_back(cache_entries(api));
			result.lists.push_back(cached(api, "USEast", packet2.size()));

			api.FreeRealmCharListCache();
			result.entries.push_back(cache_entries(api));
			result.lists.push_back(cached(api, "USEast", packet2.size()));
			results.push_back(result);
		}

		CHECK_EQ(results[0].entries, results[1].entries);
		REQUIRE_EQ(results[0].lists.size(), results[1].lists.size());
		for (size_t i = 0; i < results[0].lists.size(); ++i)
		{
			CAPTURE(i);
			CHECK_EQ(results[0].lists[i], results[1].lists[i]);
		}

		CHECK_EQ(results[0].entries, std::vector<size_t>{ 2, 2, 0 });
		CHECK_EQ(results[0].lists[1], packet1);
		CHECK_EQ(results[0].lists[2], packet3);
		CHECK(results[0].lists[3].empty());
		CHECK_EQ(results[0].lists[4], packet2);
		CHECK(results[0].lists[5].empty());
	}
}
