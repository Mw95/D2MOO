#include <doctest.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <RandomUnsignedInteger.h>

#include <BnCache.h>

#include "BnclientTestFixtures.h"


namespace
{
struct CacheApi
{
	decltype(&BNCACHE_Open) Open;
	decltype(&BNCACHE_Close) Close;
	decltype(&BNCACHE_StoreFile) StoreFile;
	decltype(&BNCACHE_LoadFile) LoadFile;
	decltype(&BNCACHE_FreeFile) FreeFile;
	decltype(&BNCACHE_FindHashEntry) FindHashEntry;
};

const CacheApi& moo_cache_api()
{
	static const CacheApi api = { &BNCACHE_Open, &BNCACHE_Close, &BNCACHE_StoreFile, &BNCACHE_LoadFile, &BNCACHE_FreeFile, &BNCACHE_FindHashEntry };
	return api;
}

const CacheApi& original_cache_api()
{
	static const CacheApi api = {
		reinterpret_cast<decltype(&BNCACHE_Open)>(original_bnclient_address(0x6FF08CC0)),
		reinterpret_cast<decltype(&BNCACHE_Close)>(original_bnclient_address(0x6FF08BE0)),
		reinterpret_cast<decltype(&BNCACHE_StoreFile)>(original_bnclient_address(0x6FF09DA0)),
		reinterpret_cast<decltype(&BNCACHE_LoadFile)>(original_bnclient_address(0x6FF09500)),
		reinterpret_cast<decltype(&BNCACHE_FreeFile)>(original_bnclient_address(0x6FF08CA0)),
		reinterpret_cast<decltype(&BNCACHE_FindHashEntry)>(original_bnclient_address(0x6FF0AA80)),
	};
	return api;
}

// Both implementations use bncache.dat next to the executable. An existing cache is restored after the test.
template<class Fixture>
struct CacheFixture : BnclientStormFixture<Fixture>
{
	std::filesystem::path cache_path;
	std::filesystem::path backup_path;
	bool bHadCache = false;

	CacheFixture()
	{
		char szPath[MAX_PATH] = {};
		GetModuleFileNameA(GetModuleHandleA(nullptr), szPath, MAX_PATH);
		cache_path = std::filesystem::path(szPath).parent_path() / "bncache.dat";
		backup_path = cache_path;
		backup_path += ".moo-backup";
		bHadCache = std::filesystem::exists(cache_path);
		if (bHadCache)
		{
			std::filesystem::rename(cache_path, backup_path);
		}
	}

	~CacheFixture()
	{
		moo_cache_api().Close();
		original_cache_api().Close();
		std::error_code error;
		std::filesystem::remove(cache_path, error);
		if (bHadCache)
		{
			std::filesystem::rename(backup_path, cache_path, error);
		}
	}

	std::vector<uint8_t> read_cache() const
	{
		std::ifstream file(cache_path, std::ios::binary);
		return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	}

	void write_cache(const std::vector<uint8_t>& data) const
	{
		std::ofstream file(cache_path, std::ios::binary | std::ios::trunc);
		file.write(reinterpret_cast<const char*>(data.data()), (std::streamsize)data.size());
	}
};

struct StoredFile
{
	std::string szName;
	std::vector<uint8_t> data;
	FILETIME tFileTime;
};

std::vector<uint8_t> random_data(size_t nSize)
{
	std::vector<uint8_t> data(nSize);
	for (uint8_t& nByte : data)
	{
		nByte = (uint8_t)random_unsigned_integer(0, 255);
	}
	return data;
}

constexpr uint32_t MIN_LIFETIME = 15 * 24 * 60 * 60;
constexpr uint32_t MAX_LIFETIME = 30 * 24 * 60 * 60;

// Loads a file with an implementation and checks its content
void check_load(const CacheApi& api, const StoredFile& file)
{
	CAPTURE(file.szName);
	FILETIME tFileTime = { 1, 1 };
	void* pBuffer = nullptr;
	uint32_t nSize = 0;
	REQUIRE_EQ(api.LoadFile(file.szName.c_str(), &tFileTime, &pBuffer, &nSize), TRUE);
	REQUIRE(pBuffer != nullptr);
	CHECK_EQ(nSize, (uint32_t)file.data.size());
	CHECK_EQ(std::memcmp(pBuffer, file.data.data(), file.data.size()), 0);
	CHECK_EQ(tFileTime.dwLowDateTime, file.tFileTime.dwLowDateTime);
	CHECK_EQ(tFileTime.dwHighDateTime, file.tFileTime.dwHighDateTime);
	CHECK_EQ(api.FreeFile(pBuffer, nSize), TRUE);
}

void check_missing(const CacheApi& api, const char* szName)
{
	CAPTURE(szName);
	FILETIME tFileTime = { 1, 1 };
	void* pBuffer = reinterpret_cast<void*>(1);
	uint32_t nSize = 1;
	CHECK_EQ(api.LoadFile(szName, &tFileTime, &pBuffer, &nSize), FALSE);
	CHECK_EQ(pBuffer, nullptr);
	CHECK_EQ(nSize, 0);
	CHECK_EQ(tFileTime.dwLowDateTime, 0);
	CHECK_EQ(tFileTime.dwHighDateTime, 0);
}
}


TEST_SUITE("BnclientCacheTests")
{
	TEST_CASE_FIXTURE(CacheFixture<NoOpFixture>, "Bnclient.0x6FF08CC0 / Bnclient.0x6FF09DA0 / Bnclient.0x6FF09500 / Bnclient.0x6FF08BE0")
	{
		const StoredFile files[] = {
			{ "bnnews-d2xp.txt", random_data(100), { 0x12345678, 0x01C9ABCD } },
			{ "ad001234.pcx", random_data(0x3000), { 0x87654321, 0x01C80000 } },
			{ "Tos_USA.txt", random_data(1), { 0, 0 } },
			{ "news.txt", random_data(0x400), { 5, 6 } },
		};

		// Each implementation reads the files stored by the other one
		for (const auto& [pWriter, pReader] : { std::make_pair(&moo_cache_api(), &original_cache_api()), std::make_pair(&original_cache_api(), &moo_cache_api()) })
		{
			const bool bMooWriter = pWriter == &moo_cache_api();
			CAPTURE(bMooWriter);
			std::filesystem::remove(cache_path);

			REQUIRE_EQ(pWriter->Open(), TRUE);
			for (const StoredFile& file : files)
			{
				CHECK_EQ(pWriter->StoreFile(file.szName.c_str(), file.data.data(), (uint32_t)file.data.size(), &file.tFileTime, MIN_LIFETIME, MAX_LIFETIME), TRUE);
			}
			// Replaced by a smaller version
			const StoredFile replaced = { "news.txt", random_data(0x80), { 7, 8 } };
			CHECK_EQ(pWriter->StoreFile(replaced.szName.c_str(), replaced.data.data(), (uint32_t)replaced.data.size(), &replaced.tFileTime, MIN_LIFETIME, MAX_LIFETIME), TRUE);
			check_load(*pWriter, files[0]);
			pWriter->Close();

			REQUIRE_EQ(pReader->Open(), TRUE);
			for (size_t i = 0; i < 3; ++i)
			{
				check_load(*pReader, files[i]);
			}
			check_load(*pReader, replaced);
			// The names are case insensitive
			check_load(*pReader, { "BNNEWS-D2XP.TXT", files[0].data, files[0].tFileTime });
			check_missing(*pReader, "missing.txt");

			// Both find the same hash table entries
			for (const char* szName : { "bnnews-d2xp.txt", "AD001234.PCX", "news.txt", "missing.txt" })
			{
				for (const uint32_t nLocale : { 0u, 0x409u })
				{
					CAPTURE(szName);
					CAPTURE(nLocale);
					const uint32_t nReaderIndex = pReader->FindHashEntry(szName, nLocale);
					pReader->Close();
					REQUIRE_EQ(pWriter->Open(), TRUE);
					const uint32_t nWriterIndex = pWriter->FindHashEntry(szName, nLocale);
					pWriter->Close();
					REQUIRE_EQ(pReader->Open(), TRUE);
					CHECK_EQ(nReaderIndex, nWriterIndex);
				}
			}
			CHECK_EQ(pReader->FindHashEntry("missing.txt", 0), BNCACHE_HASH_ENTRY_EMPTY);
			pReader->Close();
		}
	}

	TEST_CASE_FIXTURE(CacheFixture<NoOpFixture>, "Bnclient.0x6FF09DA0 / Bnclient.0x6FF09500 invalid arguments")
	{
		const std::vector<uint8_t> data = random_data(16);
		const FILETIME tFileTime = { 1, 2 };

		for (const CacheApi* pApi : { &moo_cache_api(), &original_cache_api() })
		{
			CAPTURE(pApi == &moo_cache_api());
			std::filesystem::remove(cache_path);

			// The cache is not open
			CHECK_EQ(pApi->StoreFile("file.txt", data.data(), (uint32_t)data.size(), &tFileTime, MIN_LIFETIME, MAX_LIFETIME), FALSE);
			check_missing(*pApi, "file.txt");

			REQUIRE_EQ(pApi->Open(), TRUE);
			CHECK_EQ(pApi->StoreFile(nullptr, data.data(), (uint32_t)data.size(), &tFileTime, MIN_LIFETIME, MAX_LIFETIME), FALSE);
			CHECK_EQ(pApi->StoreFile("", data.data(), (uint32_t)data.size(), &tFileTime, MIN_LIFETIME, MAX_LIFETIME), FALSE);
			CHECK_EQ(pApi->StoreFile("file.txt", nullptr, (uint32_t)data.size(), &tFileTime, MIN_LIFETIME, MAX_LIFETIME), FALSE);
			CHECK_EQ(pApi->StoreFile("file.txt", data.data(), 0, &tFileTime, MIN_LIFETIME, MAX_LIFETIME), FALSE);
			CHECK_EQ(pApi->StoreFile("file.txt", data.data(), (uint32_t)data.size(), nullptr, MIN_LIFETIME, MAX_LIFETIME), FALSE);
			CHECK_EQ(pApi->StoreFile("file.txt", data.data(), (uint32_t)data.size(), &tFileTime, MIN_LIFETIME, 0), FALSE);
			check_missing(*pApi, "file.txt");
			check_missing(*pApi, "");

			void* pBuffer = nullptr;
			uint32_t nSize = 0;
			CHECK_EQ(pApi->LoadFile(nullptr, nullptr, &pBuffer, &nSize), FALSE);
			CHECK_EQ(pApi->FreeFile(nullptr, 0), FALSE);
			pApi->Close();
		}
	}

	TEST_CASE_FIXTURE(CacheFixture<NoOpFixture>, "Bnclient.0x6FF08CC0 invalid cache files")
	{
		const std::vector<uint8_t> data = random_data(0x40);
		const FILETIME tFileTime = { 3, 4 };

		// Version 2 signature, unknown signature, too small, wrong header CRC
		std::vector<std::vector<uint8_t>> caches = {
			{ 0x42, 0x4E, 0x32, 0x1A },
			{ 0x42, 0x4E, 0x33, 0x1A, 1, 2, 3 },
			std::vector<uint8_t>(0x200, 0),
			random_data(0x1000),
		};
		std::vector<uint8_t> wrongCRC(0x1000, 0);
		wrongCRC[0] = 0x42; wrongCRC[1] = 0x4E; wrongCRC[2] = 0x33; wrongCRC[3] = 0x1A;
		caches.push_back(wrongCRC);

		for (size_t i = 0; i < caches.size(); ++i)
		{
			CAPTURE(i);
			std::vector<std::vector<uint8_t>> results;
			for (const CacheApi* pApi : { &moo_cache_api(), &original_cache_api() })
			{
				write_cache(caches[i]);
				CHECK_EQ(pApi->Open(), TRUE);
				// The cache is replaced by an empty one
				check_missing(*pApi, "file.txt");
				CHECK_EQ(pApi->StoreFile("file.txt", data.data(), (uint32_t)data.size(), &tFileTime, MIN_LIFETIME, MAX_LIFETIME), TRUE);
				check_load(*pApi, { "file.txt", data, tFileTime });
				pApi->Close();
				results.push_back(read_cache());
			}
			// The files only differ in the access and expiration times
			CHECK_EQ(results[0].size(), results[1].size());
		}
	}
}
