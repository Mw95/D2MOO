#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <RandomUnsignedInteger.h>

#include <ChatDlg.h>
#include <ComCallback.h>

#include "D2MultiTestFixtures.h"


namespace
{
std::vector<Unicode> unicode(const std::string& szString)
{
	std::vector<Unicode> wszString;
	for (const char c : szString)
	{
		wszString.push_back((Unicode)(uint16_t)(uint8_t)c);
	}
	wszString.push_back(0);
	return wszString;
}

std::string narrow(const Unicode* wszString)
{
	std::string szString;
	for (; *wszString != 0; ++wszString)
	{
		szString += (char)(uint16_t)*wszString;
	}
	return szString;
}

// Character data of a Diablo II statstring: version, 11 components, class + 1, 11 colors, level, flags, guild flags, ladder, 2 unknown bytes
std::string character_data(uint8_t nClass, uint8_t nLevel, uint16_t nFlags, uint8_t nLadder)
{
	std::string data;
	auto encode14 = [&data](uint32_t nValue)
	{
		data += (char)((nValue & 0x7F) | 0x80);
		data += (char)(((nValue >> 7) & 0x7F) | 0x80);
	};
	encode14(10);
	for (int i = 0; i < 11; ++i) data += (char)(i + 1);
	data += (char)(nClass + 1);
	for (int i = 0; i < 11; ++i) data += (char)(0x20 + i);
	data += (char)nLevel;
	encode14(nFlags);
	encode14(0);
	data += (char)nLadder;
	data += (char)0xFF;
	data += (char)0xFF;
	return data;
}
}


TEST_SUITE("D2MultiTextTests")
{
	TEST_CASE_FIXTURE(D2MultiFixture<NoOpFixture>, "D2Multi.0x6F9A1000")
	{
		const auto [sut, original] = make_d2multi_pair(CHATDLG_DecodeCDKey, 0x6F9A1000);

		const char szAlphabet[] = "246789BCDEFGHJKMNPRTVWXZbcdefghjkmnprtvwxz0135AILOQSUY_ ";
		uint32_t nValidKeys = 0;
		for (int i = 0; i < 4000; ++i)
		{
			char szKey[17] = {};
			for (int j = 0; j < 16; ++j)
			{
				szKey[j] = szAlphabet[random_unsigned_integer(0, i % 4 == 0 ? sizeof(szAlphabet) - 2 : 23)];
			}

			uint32_t moo_values[2] = { 1, 1 }, original_values[2] = { 2, 2 };
			const BOOL moo_result = sut(szKey, &moo_values[0], &moo_values[1]);
			const BOOL original_result = original(szKey, &original_values[0], &original_values[1]);

			CAPTURE(szKey);
			CHECK_EQ(moo_result, original_result);
			if (original_result)
			{
				CHECK_EQ(moo_values[0], original_values[0]);
				CHECK_EQ(moo_values[1], original_values[1]);
			}
			nValidKeys += moo_result ? 1 : 0;
		}
		CHECK_GT(nValidKeys, 0);
	}

	TEST_CASE("D2Multi.0x6F9A7250")
	{
		const auto [sut, original] = make_d2multi_pair(CHATDLG_CompareCommand, 0x6F9A7250);

		const char* szTexts[] = { "", "/w", "/W user hello", "/whisper user", "/me waves", "/m", "/r reply", "/notify", "/NOTIFY x", "hello", "/f list", "/ignore" };
		const char* szCommands[] = { "", "/w", "/whisper", "/me", "/m", "/r", "/reply", "/notify", "/f", "/friends", "/i" };
		for (const char* szText : szTexts)
		{
			for (const char* szCommand : szCommands)
			{
				CAPTURE(szText);
				CAPTURE(szCommand);
				CHECK_EQ(sut(szText, szCommand), original(szText, szCommand));
			}
		}
	}

	TEST_CASE_FIXTURE(D2MultiFixture<NoOpFixture>, "D2Multi.0x6F9AB370 / D2Multi.0x6F9AB390")
	{
		const auto [moo_account, original_account] = make_d2multi_pair(CHATDLG_GetAccountName, 0x6F9AB370);
		const auto [moo_character, original_character] = make_d2multi_pair(CHATDLG_GetCharacterName, 0x6F9AB390);

		for (const char* szUserName : { "", "Account", "Character*Account", "*Account", "Character*", "a*b*c", "*" })
		{
			CAPTURE(szUserName);
			const char* moo_result = moo_account(szUserName);
			const char* original_result = original_account(szUserName);
			// Both return a pointer into the given name
			CHECK_EQ(moo_result - szUserName, original_result - szUserName);

			char moo_name[64] = {}, original_name[64] = {};
			moo_character(szUserName, moo_name);
			original_character(szUserName, original_name);
			CHECK_EQ(std::string(moo_name), std::string(original_name));
		}
	}

	TEST_CASE_FIXTURE(D2MultiFixture<NoOpFixture>, "D2Multi.0x6F9A5580")
	{
		const auto [sut, original] = make_d2multi_pair(CHATDLG_GetClassName, 0x6F9A5580);

		for (int32_t nClass = -1; nClass < 10; ++nClass)
		{
			CAPTURE(nClass);
			Unicode moo_name[32] = {}, original_name[32] = {};
			sut(moo_name, nClass);
			original(original_name, nClass);
			CHECK_EQ(narrow(moo_name), narrow(original_name));
		}
	}

	TEST_CASE_FIXTURE(D2MultiFixture<NoOpFixture>, "D2Multi.0x6F9AC970")
	{
		const auto [sut, original] = make_d2multi_pair(COMCALLBACK_ParseStatstring, 0x6F9AC970);

		const std::string szD2XP = std::string("PX2D") + "USEast,Hero," + character_data(3, 42, 0x0520, 1);
		const std::string szD2DV = std::string("VD2D") + "Europe,Sorc," + character_data(1, 99, 0x0004, 0xFF);
		const std::string szNoComponents = std::string("PX2D") + "USEast,Hero," + std::string("\x8A\x80", 2) + std::string(11, (char)0xFF);
		const std::string szOpen = "PX2D";
		const std::string szOthers[] = { "RATS 0 0 0", "PXES", "NB2W", "3RAW", "PX3W", "LTRD", "TAHC", "ABCD", "ab", "" };

		std::vector<std::string> statstrings = { szD2XP, szD2DV, szNoComponents, szOpen };
		statstrings.insert(statstrings.end(), std::begin(szOthers), std::end(szOthers));

		// Channel operator, administrator, representative, speaker and other special users
		for (const uint32_t nFlags : { 0x00u, 0x01u, 0x02u, 0x04u, 0x08u, 0x10u, 0x20u, 0x1000u, 0x100000u })
		{
			for (const std::string& szStatstring : statstrings)
			{
				CAPTURE(nFlags);
				CAPTURE(szStatstring);

				D2MultiChannelUserStrc moo_user, original_user;
				std::memset(&moo_user, 0, sizeof(moo_user));
				std::strcpy(moo_user.szUserName, "Hero*Account");
				original_user = moo_user;

				const uint8_t moo_class = sut(&moo_user, "Hero*Account", szStatstring.c_str(), nFlags);
				const uint8_t original_class = original(&original_user, "Hero*Account", szStatstring.c_str(), nFlags);

				CHECK_EQ(moo_class, original_class);
				CHECK_EQ(std::memcmp(&moo_user, &original_user, sizeof(moo_user)), 0);
			}
		}

		SUBCASE("Diablo II character")
		{
			D2MultiChannelUserStrc user = {};
			std::strcpy(user.szUserName, "Hero*Account");
			sut(&user, "Hero*Account", szD2XP.c_str(), 0);
			CHECK_EQ(std::string(user.szRealmName), "USEast");
			CHECK_EQ(std::string(user.szCharacterName), "Hero");
			CHECK_EQ(user.dwProduct, 'D2XP');
		}
	}

	TEST_CASE_FIXTURE(D2MultiFixture<NoOpFixture>, "D2Multi.0x6F9AF110 / D2Multi.0x6F9AF1F0")
	{
		const auto [moo_append, original_append] = make_d2multi_pair(COMCALLBACK_AppendColorCode, 0x6F9AF110);
		const auto [moo_prepend, original_prepend] = make_d2multi_pair(COMCALLBACK_PrependColorCode, 0x6F9AF1F0);

		for (const char* szText : { "", "text", "<User> " })
		{
			for (const int32_t nColor : { 0, 1, 4, 9, 10, 12 })
			{
				CAPTURE(szText);
				CAPTURE(nColor);
				auto moo_text = unicode(szText), original_text = unicode(szText);
				moo_text.resize(0x200);
				original_text.resize(0x200);

				moo_append(moo_text.data(), nColor);
				original_append(original_text.data(), nColor);
				CHECK_EQ(narrow(moo_text.data()), narrow(original_text.data()));

				moo_prepend(moo_text.data(), nColor + 1);
				original_prepend(original_text.data(), nColor + 1);
				CHECK_EQ(narrow(moo_text.data()), narrow(original_text.data()));
			}
		}
	}

	TEST_CASE_FIXTURE(D2MultiFixture<NoOpFixture>, "D2Multi.0x6F9AD5F0")
	{
		const auto [sut, original] = make_d2multi_pair(COMCALLBACK_RemoveColorCodes, 0x6F9AD5F0);

		// The color code is string 0xF9A, "#3994" with the mocked string table
		for (const char* szText : { "", "plain text", "#39941red", "start #39942 middle #39943end", "#3994", "#3994#39945", "#399", "x#39940" })
		{
			CAPTURE(szText);
			auto moo_text = unicode(szText), original_text = unicode(szText);
			moo_text.resize(0x200);
			original_text.resize(0x200);

			sut(moo_text.data());
			original(original_text.data());
			CHECK_EQ(narrow(moo_text.data()), narrow(original_text.data()));
		}
	}
}
