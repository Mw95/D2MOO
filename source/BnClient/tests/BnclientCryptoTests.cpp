#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <EqualityMacros.h>
#include <RandomUnsignedInteger.h>

#include <BnCache.h>
#include <BnSend.h>
#include <Grid.h>
#include <SHA.h>

#include "BnclientTestFixtures.h"


namespace
{
std::vector<uint8_t> random_bytes(size_t nSize)
{
	std::vector<uint8_t> bytes(nSize);
	for (auto& byte : bytes)
	{
		byte = (uint8_t)random_unsigned_integer(0, 0xFF);
	}
	return bytes;
}

template<typename T>
void fill_random(T& object)
{
	const auto bytes = random_bytes(sizeof(object));
	std::memcpy(&object, bytes.data(), sizeof(object));
}

template<typename T>
bool same_bytes(const T& a, const T& b)
{
	return std::memcmp(&a, &b, sizeof(T)) == 0;
}

// Sizes around the SHA-1 block size, and some larger ones
const size_t gnDataSizes[] = { 0, 1, 3, 55, 56, 57, 63, 64, 65, 119, 128, 1000, 4097 };

// gaGridKeys in the original dll
constexpr uintptr_t GRID_KEYS_ADDRESS = 0x6FF1DBD8;
}


TEST_SUITE("BnclientCryptoTests")
{
	TEST_CASE("Bnclient.0x6FF13F70")
	{
		const auto [sut, original] = make_bnclient_pair(SHA1_Init, 0x6FF13F70);

		SHA1Context moo_context, original_context;
		fill_random(moo_context);
		original_context = moo_context;

		sut(&moo_context);
		original(&original_context);

		CHECK(same_bytes(moo_context, original_context));
		CHECK_EQ(moo_context.pState[0], 0x67452301);
		CHECK_EQ(moo_context.pCount[0], 0);
	}

	TEST_CASE("Bnclient.0x6FF14060")
	{
		const auto [sut, original] = make_bnclient_pair(SHA1_Transform, 0x6FF14060);

		for (int i = 0; i < 50; ++i)
		{
			SHA1Context moo_context, original_context;
			fill_random(moo_context);
			original_context = moo_context;
			const auto block = random_bytes(64);

			sut(&moo_context, block.data());
			original(&original_context, block.data());

			CHECK(same_bytes(moo_context, original_context));
		}
	}

	TEST_CASE("Bnclient.0x6FF13FA0 / Bnclient.0x6FF15720")
	{
		const auto [moo_init, original_init] = make_bnclient_pair(SHA1_Init, 0x6FF13F70);
		const auto [moo_update, original_update] = make_bnclient_pair(SHA1_Update, 0x6FF13FA0);
		const auto [moo_final, original_final] = make_bnclient_pair(SHA1_Final, 0x6FF15720);

		for (const size_t nSize : gnDataSizes)
		{
			CAPTURE(nSize);
			const auto data = random_bytes(nSize);

			SUBCASE("Single update")
			{
				SHA1Context moo_context, original_context;
				moo_init(&moo_context);
				original_init(&original_context);
				moo_update(&moo_context, data.data(), (uint32_t)data.size());
				original_update(&original_context, data.data(), (uint32_t)data.size());
				CHECK(same_bytes(moo_context, original_context));

				uint8_t moo_digest[20] = {}, original_digest[20] = {};
				moo_final(moo_digest, &moo_context);
				original_final(original_digest, &original_context);
				CHECK(same_bytes(moo_digest, original_digest));
			}

			SUBCASE("Updates of random sizes")
			{
				SHA1Context moo_context, original_context;
				moo_init(&moo_context);
				original_init(&original_context);
				for (size_t nOffset = 0; nOffset < nSize;)
				{
					const size_t nChunk = std::min<size_t>(nSize - nOffset, random_unsigned_integer(1, 100));
					moo_update(&moo_context, &data[nOffset], (uint32_t)nChunk);
					original_update(&original_context, &data[nOffset], (uint32_t)nChunk);
					nOffset += nChunk;
				}
				CHECK(same_bytes(moo_context, original_context));

				uint8_t moo_digest[20] = {}, original_digest[20] = {};
				moo_final(moo_digest, &moo_context);
				original_final(original_digest, &original_context);
				CHECK(same_bytes(moo_digest, original_digest));
			}
		}
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF157D0")
	{
		const auto [sut, original] = make_bnclient_pair(SHA_Interleave, 0x6FF157D0);

		for (const size_t nSize : { 2, 3, 32, 33, 64, 65, 128 })
		{
			CAPTURE(nSize);
			const auto input = random_bytes(nSize);
			uint8_t moo_output[40] = {}, original_output[40] = {};

			const auto moo_result = sut(moo_output, input.data(), (uint32_t)input.size());
			const auto original_result = original(original_output, input.data(), (uint32_t)input.size());

			CHECK_EQ(moo_result, moo_output);
			CHECK_EQ(original_result, original_output);
			CHECK(same_bytes(moo_output, original_output));
		}
	}

	TEST_CASE("Bnclient.0x6FF0B820")
	{
		const auto [sut, original] = make_bnclient_pair(GRID_IDEAMulInv, 0x6FF0B820);

		uint32_t nDifferences = 0;
		for (uint32_t x = 0; x <= 0xFFFF; ++x)
		{
			if (sut((uint16_t)x) != original((uint16_t)x))
			{
				++nDifferences;
			}
		}
		CHECK_EQ(nDifferences, 0);
	}

	TEST_CASE("Bnclient.0x6FF0B880")
	{
		const auto [sut, original] = make_bnclient_pair(GRID_IDEAInvertKey, 0x6FF0B880);

		for (int i = 0; i < 20; ++i)
		{
			uint16_t key[GRID_IDEA_KEYLEN];
			fill_random(key);
			uint16_t moo_output[GRID_IDEA_KEYLEN] = {}, original_output[GRID_IDEA_KEYLEN] = {};

			sut(key, moo_output);
			original(key, original_output);

			CHECK(same_bytes(moo_output, original_output));
		}
	}

	TEST_CASE("Bnclient.0x6FF0BBF0")
	{
		const auto [sut, original] = make_bnclient_pair(GRID_IDEACipher, 0x6FF0BBF0);

		for (int i = 0; i < 50; ++i)
		{
			uint16_t key[GRID_IDEA_KEYLEN];
			uint16_t input[4];
			fill_random(key);
			fill_random(input);
			uint16_t moo_output[4] = {}, original_output[4] = {};

			sut(input, moo_output, key);
			original(input, original_output, key);

			CHECK(same_bytes(moo_output, original_output));
		}
	}

	TEST_CASE("Bnclient.0x6FF0BE90 / Bnclient.0x6FF0BE70 / Bnclient.0x6FF0BE50")
	{
		const auto [moo_set_key, original_set_key] = make_bnclient_pair(GRID_SetKey, 0x6FF0BE90);
		const auto [moo_crypt, original_crypt] = make_bnclient_pair(GRID_CryptBlock, 0x6FF0BE70);
		const auto [moo_clear, original_clear] = make_bnclient_pair(GRID_ClearKeys, 0x6FF0BE50);

		for (int nSlot = 0; nSlot < GRID_SLOTS; ++nSlot)
		{
			for (const BOOL bEncrypt : { TRUE, FALSE })
			{
				CAPTURE(nSlot);
				CAPTURE(bEncrypt);
				const auto user_key = random_bytes(16);
				moo_set_key(nSlot, bEncrypt, user_key.data());
				original_set_key(nSlot, bEncrypt, user_key.data());

				for (int i = 0; i < 10; ++i)
				{
					const auto input = random_bytes(8);
					uint8_t moo_output[8] = {}, original_output[8] = {};
					moo_crypt(nSlot, input.data(), moo_output);
					original_crypt(nSlot, input.data(), original_output);
					CHECK(same_bytes(moo_output, original_output));
				}
			}
		}

		SUBCASE("Encryption followed by decryption")
		{
			const auto user_key = random_bytes(16);
			const auto input = random_bytes(8);
			uint8_t encrypted[8] = {}, decrypted[8] = {};
			moo_set_key(0, TRUE, user_key.data());
			moo_set_key(1, FALSE, user_key.data());
			moo_crypt(0, input.data(), encrypted);
			moo_crypt(1, encrypted, decrypted);
			CHECK_EQ(std::memcmp(decrypted, input.data(), 8), 0);
		}

		SUBCASE("Cleared keys")
		{
			moo_clear();
			original_clear();

			const auto input = random_bytes(8);
			uint8_t moo_output[8] = {}, original_output[8] = {};
			moo_crypt(2, input.data(), moo_output);
			original_crypt(2, input.data(), original_output);
			CHECK(same_bytes(moo_output, original_output));

			uint16_t original_keys[GRID_SLOTS][GRID_IDEA_KEYLEN];
			std::memcpy(original_keys, original_bnclient_global<uint16_t>(GRID_KEYS_ADDRESS), sizeof(original_keys));
			CHECK(same_bytes(gaGridKeys, original_keys));
		}
	}

	TEST_CASE("Bnclient.0x6FF0BF70")
	{
		const auto [sut, original] = make_bnclient_pair(GRID_XSHATransform, 0x6FF0BF70);

		for (int i = 0; i < 50; ++i)
		{
			uint32_t moo_context[5 + 16], original_context[5 + 16];
			fill_random(moo_context);
			std::memcpy(original_context, moo_context, sizeof(moo_context));

			sut(moo_context);
			original(original_context);

			CHECK(same_bytes(moo_context, original_context));
		}
	}

	TEST_CASE("Bnclient.0x6FF0C150")
	{
		const auto [sut, original] = make_bnclient_pair(GRID_XSHA, 0x6FF0C150);

		for (const size_t nSize : gnDataSizes)
		{
			CAPTURE(nSize);
			const auto data = random_bytes(nSize);
			uint8_t moo_output[20] = {}, original_output[20] = {};

			sut(moo_output, data.data(), (uint32_t)data.size());
			original(original_output, data.data(), (uint32_t)data.size());

			CHECK(same_bytes(moo_output, original_output));
		}
	}

	TEST_CASE("Bnclient.0x6FF0C2B0")
	{
		const auto [sut, original] = make_bnclient_pair(GRID_HashTransform, 0x6FF0C2B0);

		for (int i = 0; i < 50; ++i)
		{
			GridHashContext moo_context, original_context;
			fill_random(moo_context);
			original_context = moo_context;

			sut(&moo_context);
			original(&original_context);

			CHECK(same_bytes(moo_context, original_context));
		}
	}

	TEST_CASE("Bnclient.0x6FF0C470 / Bnclient.0x6FF0C250 / Bnclient.0x6FF0C220 / Bnclient.0x6FF0C200")
	{
		const auto [moo_init, original_init] = make_bnclient_pair(GRID_InitHash, 0x6FF0C470);
		const auto [moo_hash, original_hash] = make_bnclient_pair(GRID_HashBlock, 0x6FF0C250);
		const auto [moo_get, original_get] = make_bnclient_pair(GRID_GetHash, 0x6FF0C220);
		const auto [moo_clear, original_clear] = make_bnclient_pair(GRID_ClearHashes, 0x6FF0C200);

		for (int nSlot = 0; nSlot < GRID_SLOTS; ++nSlot)
		{
			CAPTURE(nSlot);
			moo_init(nSlot);
			original_init(nSlot);

			for (int i = 0; i < 5; ++i)
			{
				const auto block = random_bytes(64);
				uint32_t moo_output[5] = {}, original_output[5] = {};
				moo_hash(nSlot, block.data(), moo_output);
				original_hash(nSlot, block.data(), original_output);
				CHECK(same_bytes(moo_output, original_output));

				// Without output
				moo_hash(nSlot, block.data(), nullptr);
				original_hash(nSlot, block.data(), nullptr);
			}

			uint32_t moo_state[5] = {}, original_state[5] = {};
			moo_get(nSlot, moo_state);
			original_get(nSlot, original_state);
			CHECK(same_bytes(moo_state, original_state));

			// Does nothing without output
			moo_get(nSlot, nullptr);
			original_get(nSlot, nullptr);
		}

		moo_clear();
		original_clear();
		for (int nSlot = 0; nSlot < GRID_SLOTS; ++nSlot)
		{
			uint32_t moo_state[5] = { 1 }, original_state[5] = { 1 };
			moo_get(nSlot, moo_state);
			original_get(nSlot, original_state);
			CHECK(same_bytes(moo_state, original_state));
		}
	}

	TEST_CASE("Bnclient.0x6FF0AF50 / Bnclient.0x6FF0AD90")
	{
		const auto [moo_decrypt, original_decrypt] = make_bnclient_pair(GRID_Decrypt, 0x6FF0AD90);

		for (const char* szPassword : { "a", "password", "a much longer password than the 64 bytes block used by the hash function" })
		{
			for (const size_t nSize : { 0, 8, 9, 64, 72, 136, 200, 8 + 64 * 5 })
			{
				CAPTURE(szPassword);
				CAPTURE(nSize);
				std::vector<uint8_t> moo_data = random_bytes(nSize);
				std::vector<uint8_t> original_data = moo_data;

				const auto moo_result = moo_decrypt(moo_data.data(), (uint32_t)moo_data.size(), szPassword);
				const auto original_result = original_decrypt(original_data.data(), (uint32_t)original_data.size(), szPassword);

				CHECK_EQ(moo_result, original_result);
				CHECK(moo_data == original_data);
			}
		}
	}

	TEST_CASE("Bnclient.0x6FF09D40")
	{
		const auto [sut, original] = make_bnclient_pair(BNCACHE_HashString, 0x6FF09D40);

		// The crypt table is created by BNCACHE_Open, both implementations use the same one here
		std::vector<uint32_t> crypt_table(0x500);
		uint32_t nSeed = 0x00100001;
		for (uint32_t i = 0; i < 0x100; ++i)
		{
			for (uint32_t j = 0, nIndex = i; j < 5; ++j, nIndex += 0x100)
			{
				nSeed = (nSeed * 125 + 3) % 0x2AAAAB;
				const uint32_t nHigh = (nSeed & 0xFFFF) << 16;
				nSeed = (nSeed * 125 + 3) % 0x2AAAAB;
				crypt_table[nIndex] = nHigh | (nSeed & 0xFFFF);
			}
		}

		uint32_t** ppOriginalCryptTable = original_bnclient_global<uint32_t*>(0x6FF1DB80);
		uint32_t* const pMooPrevious = gpBnCacheCryptTable;
		uint32_t* const pOriginalPrevious = *ppOriginalCryptTable;
		gpBnCacheCryptTable = crypt_table.data();
		*ppOriginalCryptTable = crypt_table.data();

		// Characters above 0x7F are not tested: they are passed to toupper as negative values, which the debug CRT rejects
		for (const char* szString : { "", "a", "BNNews-D2DV", "lowercase and UPPERCASE", "path\\to\\some_file.mpq", "\x7F" })
		{
			for (uint32_t nHashType = 0; nHashType < 3; ++nHashType)
			{
				CAPTURE(szString);
				CAPTURE(nHashType);
				CHECK_EQ(sut(szString, nHashType), original(szString, nHashType));
			}
		}

		// No string
		CHECK_EQ(sut(nullptr, 0), original(nullptr, 0));

		gpBnCacheCryptTable = pMooPrevious;
		*ppOriginalCryptTable = pOriginalPrevious;
	}

	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF06E80")
	{
		const auto [sut, original] = make_bnclient_pair(BNCDKEY_Decode, 0x6FF06E80);

		// Characters accepted in a CD key, and some others
		const char szAlphabet[] = "246789BCDEFGHJKMNPRTVWXZbcdefghjkmnprtvwxz0135AILOQSUY_ ";

		uint32_t nValidKeys = 0;
		for (int i = 0; i < 4000; ++i)
		{
			char szKey[17] = {};
			for (int j = 0; j < 16; ++j)
			{
				szKey[j] = szAlphabet[random_unsigned_integer(0, i % 4 == 0 ? sizeof(szAlphabet) - 2 : 23)];
			}

			uint32_t moo_values[3] = { 1, 1, 1 }, original_values[3] = { 2, 2, 2 };
			const auto moo_result = sut(szKey, &moo_values[0], &moo_values[1], &moo_values[2]);
			const auto original_result = original(szKey, &original_values[0], &original_values[1], &original_values[2]);

			CAPTURE(szKey);
			CHECK_EQ(moo_result, original_result);
			CHECK(same_bytes(moo_values, original_values));
			nValidKeys += moo_result ? 1 : 0;
		}
		// Roughly one key out of 256 has a valid checksum
		CHECK_GT(nValidKeys, 0);

		SUBCASE("No key")
		{
			uint32_t moo_values[3] = { 1, 1, 1 }, original_values[3] = { 2, 2, 2 };
			CHECK_EQ(sut(nullptr, &moo_values[0], &moo_values[1], &moo_values[2]), original(nullptr, &original_values[0], &original_values[1], &original_values[2]));
			CHECK(same_bytes(moo_values, original_values));
		}
	}
}
