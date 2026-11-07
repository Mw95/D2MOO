#include <doctest.h>

#include <algorithm>
#include <ctime>
#include <cstring>
#include <string>
#include <vector>

#include <D2Config.h>
#include <SaveLoad.h>

#include "D2LaunchTestFixtures.h"


namespace
{
constexpr size_t SAVE_HEADER_SIZE = 0x14F;
constexpr size_t CHECKSUM_OFFSET = 0x0C;
constexpr size_t CREATE_TIME_OFFSET = 0x2C;
constexpr size_t LAST_PLAYED_OFFSET = 0x30;

uint32_t read_u32(const std::vector<uint8_t>& data, size_t nOffset)
{
	uint32_t nValue = 0;
	std::memcpy(&nValue, &data[nOffset], sizeof(nValue));
	return nValue;
}

void write_u32(std::vector<uint8_t>& data, size_t nOffset, uint32_t nValue)
{
	std::memcpy(&data[nOffset], &nValue, sizeof(nValue));
}

// Header of a 1.10 save file
std::vector<uint8_t> make_save(uint32_t nVersion, uint8_t nClass, uint8_t nLevel, uint32_t dwStatus, size_t nSize = 0x400)
{
	std::vector<uint8_t> data(nSize);
	for (size_t i = 0; i < data.size(); ++i)
	{
		data[i] = (uint8_t)(i * 13 + 7);
	}
	write_u32(data, 0x00, 0xAA55AA55);
	write_u32(data, 0x04, nVersion);
	if (nVersion <= 0x5B)
	{
		write_u32(data, 0x18, dwStatus);
		data[0x22] = nClass;
		data[0x24] = nLevel;
	}
	else
	{
		write_u32(data, 0x24, dwStatus);
		data[0x28] = nClass;
		data[0x2B] = nLevel;
	}
	return data;
}
}


TEST_SUITE("D2LaunchSaveTests")
{
	TEST_CASE_FIXTURE(D2LaunchFileFixture<NoOpFixture>, "D2Launch.0x6FA279F0 / D2Launch.0x6FA27B50 / D2Launch.0x6FA27B60")
	{
		const auto [moo_create, original_create] = make_d2launch_pair(SAVE_CreateCharacter, 0x6FA279F0);
		const auto [moo_set_realm, original_set_realm] = make_d2launch_pair(SAVE_SetRealmCharacter, 0x6FA27B50);
		const auto [moo_write, original_write] = make_d2launch_pair(SAVE_WriteCharacterFile, 0x6FA27B60);

		for (uint8_t nClass = 0; nClass < 7; ++nClass)
		{
			for (const uint16_t nSaveFlags : { 0x00, 0x04, 0x20, 0x24 })
			{
				for (const BOOL bRealm : { FALSE, TRUE })
				{
					CAPTURE(nClass);
					CAPTURE(nSaveFlags);
					CAPTURE(bRealm);

					D2CharacterPreviewInfoStrc moo_preview, original_preview;
					std::memset(&moo_preview, 0xCC, sizeof(moo_preview));
					std::memset(&original_preview, 0xCC, sizeof(original_preview));

					const uint32_t nTimeBefore = (uint32_t)time(nullptr);
					moo_create("MooHero", nClass, &moo_preview, nSaveFlags);
					moo_set_realm(bRealm);
					const BOOL moo_result = moo_write("MooHero");

					original_create("MooHero", nClass, &original_preview, nSaveFlags);
					original_set_realm(bRealm);
					// Written to another file, the name in the header is the same
					std::filesystem::rename(save_directory / "MooHero.d2s", save_directory / "First.d2s");
					const BOOL original_result = original_write("MooHero");
					const uint32_t nTimeAfter = (uint32_t)time(nullptr);

					CHECK_EQ(moo_result, original_result);
					CHECK_EQ(moo_result, TRUE);
					CHECK_EQ(std::memcmp(&moo_preview, &original_preview, sizeof(moo_preview)), 0);

					auto moo_file = read_file("First.d2s");
					auto original_file = read_file("MooHero.d2s");
					REQUIRE_EQ(moo_file.size(), SAVE_HEADER_SIZE);
					REQUIRE_EQ(original_file.size(), SAVE_HEADER_SIZE);

					// The times may differ, and the checksum depends on them
					for (auto* pFile : { &moo_file, &original_file })
					{
						const uint32_t nCreateTime = read_u32(*pFile, CREATE_TIME_OFFSET);
						CHECK_GE(nCreateTime, nTimeBefore);
						CHECK_LE(nCreateTime, nTimeAfter);
						CHECK_EQ(read_u32(*pFile, LAST_PLAYED_OFFSET), nCreateTime);

						std::vector<uint8_t> unchecked = *pFile;
						write_u32(unchecked, CHECKSUM_OFFSET, 0);
						CHECK_EQ(read_u32(*pFile, CHECKSUM_OFFSET), D2LaunchFileMock::ComputeChecksum(unchecked.data(), unchecked.size()));

						write_u32(*pFile, CHECKSUM_OFFSET, 0);
						write_u32(*pFile, CREATE_TIME_OFFSET, 0);
						write_u32(*pFile, LAST_PLAYED_OFFSET, 0);
					}
					CHECK_MESSAGE(moo_file == original_file, "Comparing the save headers");

					std::filesystem::remove(save_directory / "First.d2s");
					std::filesystem::remove(save_directory / "MooHero.d2s");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2LaunchFileFixture<NoOpFixture>, "D2Launch.0x6FA27B60 without save directory")
	{
		const auto [sut, original] = make_d2launch_pair(SAVE_WriteCharacterFile, 0x6FA27B60);
		D2LaunchFileMock::szSavePath = (save_directory / "missing").string() + "\\";
		CHECK_EQ(sut("Hero"), original("Hero"));
		CHECK_EQ(sut("Hero"), FALSE);
	}

	TEST_CASE_FIXTURE(D2LaunchFileFixture<NoOpFixture>, "D2Launch.0x6FA27D80")
	{
		const auto [sut, original] = make_d2launch_pair(SAVE_ReadCharacterPreview, 0x6FA27D80);

		struct Case
		{
			const char* szName;
			std::vector<uint8_t> data;
		};

		std::vector<Case> cases = {
			{ "Current", make_save(0x60, 3, 42, 0x24) },
			{ "CurrentExpansion", make_save(0x60, 6, 99, 0x20) },
			{ "Old", make_save(0x50, 2, 12, 0x04) },
			{ "OldestSupported", make_save(0x47, 1, 1, 0) },
			{ "TooOld", make_save(0x46, 1, 1, 0) },
			{ "Newer", make_save(0x61, 1, 1, 0) },
			{ "Short", make_save(0x60, 1, 1, 0, 0x100) },
			{ "OldShort", make_save(0x50, 1, 1, 0, 0x80) },
			{ "Tiny", make_save(0x60, 1, 1, 0, 8) },
			{ "BadMagic", make_save(0x60, 1, 1, 0) },
		};
		write_u32(cases.back().data, 0, 0x12345678);

		// Without components, the default ones are used
		auto noComponents = make_save(0x60, 4, 30, 0);
		std::memset(&noComponents[0x88], 0, 16);
		cases.push_back({ "NoComponents", noComponents });

		for (const Case& testCase : cases)
		{
			write_file(std::string(testCase.szName) + ".d2s", testCase.data);
		}

		for (const char* szName : { "Current", "CurrentExpansion", "Old", "OldestSupported", "TooOld", "Newer", "Short", "OldShort", "Tiny", "BadMagic", "NoComponents", "Missing" })
		{
			CAPTURE(szName);
			uint8_t moo_preview[sizeof(D2CharacterPreviewInfoStrc)], original_preview[sizeof(D2CharacterPreviewInfoStrc)];
			std::memset(moo_preview, 0xCC, sizeof(moo_preview));
			std::memset(original_preview, 0xCC, sizeof(original_preview));

			const BOOL moo_result = sut(szName, moo_preview);
			const BOOL original_result = original(szName, original_preview);

			CHECK_EQ(moo_result, original_result);
			CHECK_EQ(std::memcmp(moo_preview, original_preview, sizeof(moo_preview)), 0);
		}

		uint8_t preview[sizeof(D2CharacterPreviewInfoStrc)] = {};
		CHECK_EQ(sut("Current", preview), TRUE);
		CHECK_EQ(reinterpret_cast<D2CharacterPreviewInfoStrc*>(preview)->nLevel, 42);
		CHECK_EQ(reinterpret_cast<D2CharacterPreviewInfoStrc*>(preview)->nClass, 4);
		CHECK_EQ(sut("Newer", preview), FALSE);
	}

	TEST_CASE_FIXTURE(D2LaunchFileFixture<NoOpFixture>, "D2Launch.0x6FA27F80")
	{
		const auto [sut, original] = make_d2launch_pair(SAVE_ConvertCharacterToExpansion, 0x6FA27F80);

		const std::pair<const char*, std::vector<uint8_t>> cases[] = {
			{ "Current", make_save(0x60, 3, 42, 0x04) },
			{ "Old", make_save(0x50, 2, 12, 0x04) },
			{ "OldShort", make_save(0x50, 2, 12, 0x04, 0x80) },
			{ "Short", make_save(0x60, 1, 1, 0, 0x100) },
			{ "Tiny", make_save(0x60, 1, 1, 0, 4) },
			{ "Large", make_save(0x60, 1, 1, 0, 0x3000) },
		};

		for (const auto& [szName, data] : cases)
		{
			CAPTURE(szName);
			write_file(std::string("Moo") + szName + ".d2s", data);
			write_file(std::string("Org") + szName + ".d2s", data);

			const BOOL moo_result = sut((std::string("Moo") + szName).c_str());
			const BOOL original_result = original((std::string("Org") + szName).c_str());

			CHECK_EQ(moo_result, original_result);
			CHECK_MESSAGE(read_file(std::string("Moo") + szName + ".d2s") == read_file(std::string("Org") + szName + ".d2s"), "Comparing the converted files");
		}

		CHECK_EQ(sut("Missing"), original("Missing"));
	}

	TEST_CASE_FIXTURE(D2LaunchFileFixture<NoOpFixture>, "D2Launch.0x6FA27C00")
	{
		const auto [sut, original] = make_d2launch_pair(SAVE_DeleteCharacter, 0x6FA27C00);

		for (const char* szSubDirectory : { (const char*)nullptr, "", "Realm" })
		{
			CAPTURE(szSubDirectory ? szSubDirectory : "(null)");
			const auto directory = szSubDirectory && *szSubDirectory ? save_directory / szSubDirectory : save_directory;
			std::filesystem::create_directories(directory);

			std::vector<std::vector<std::string>> results;
			for (const auto& [pfDelete, szPrefix] : { std::make_pair(sut, std::string("Moo")), std::make_pair(original, std::string("Org")) })
			{
				for (const char* szExtension : { ".d2s", ".key", ".ma0", ".map" })
				{
					write_file((directory / (szPrefix + "Hero" + szExtension)).lexically_relative(save_directory).string(), { 1, 2, 3 });
				}
				write_file((directory / (szPrefix + "Hero2.d2s")).lexically_relative(save_directory).string(), { 1 });
				std::filesystem::create_directories(directory / (szPrefix + "Hero.dir"));

				pfDelete((szPrefix + "Hero").c_str(), szSubDirectory);

				std::vector<std::string> remaining;
				for (const auto& entry : std::filesystem::directory_iterator(directory))
				{
					const std::string szFileName = entry.path().filename().string();
					if (szFileName.rfind(szPrefix, 0) == 0)
					{
						remaining.push_back(szFileName.substr(szPrefix.size()));
					}
				}
				std::sort(remaining.begin(), remaining.end());
				results.push_back(remaining);
			}

			CHECK_EQ(results[0], results[1]);
			CHECK_EQ(results[0], std::vector<std::string>{ "Hero.dir", "Hero2.d2s" });
		}
	}
}
