#include <doctest.h>

#include <cstring>
#include <ctime>
#include <string>
#include <vector>

#include <CharSel.h>
#include <MainMenus.h>

#include "D2LaunchTestFixtures.h"


namespace
{
using CharFilter = int32_t(__stdcall*)(D2WinEditBoxStrc* pEditBox, int32_t nPos, char* pChar);

std::vector<Unicode> unicode(const char* szString)
{
	std::vector<Unicode> wszString;
	for (const char* pChar = szString; ; ++pChar)
	{
		wszString.push_back((Unicode)(uint16_t)(uint8_t)*pChar);
		if (!*pChar)
		{
			break;
		}
	}
	return wszString;
}

// Compares the results of both filters for every character, and checks that the character is not modified
void compare_filter(CharFilter sut, CharFilter original, const char* szText, int32_t nPos)
{
	auto wszText = unicode(szText);
	auto pEditBox = reinterpret_cast<D2WinEditBoxStrc*>(wszText.data());

	for (int c = 0; c < 256; ++c)
	{
		CAPTURE(c);
		char moo_char = (char)c, original_char = (char)c;
		const auto moo_result = sut(pEditBox, nPos, &moo_char);
		const auto original_result = original(pEditBox, nPos, &original_char);
		CHECK_EQ(moo_result != 0, original_result != 0);
		CHECK_EQ(moo_char, original_char);
	}
}
}


TEST_SUITE("D2LaunchFilterTests")
{
	TEST_CASE_FIXTURE(D2LaunchUiFixture<NoOpFixture>, "D2Launch.0x6FA19890 / D2Launch.0x6FA19E40 / D2Launch.0x6FA1AA40")
	{
		const std::pair<CharFilter, uintptr_t> filters[] = {
			{ &MENU_AccountNameCharFilter, 0x6FA19890 },
			{ &MENU_LoginAccountNameCharFilter, 0x6FA19E40 },
			{ &MENU_CreateAccountNameCharFilter, 0x6FA1AA40 },
		};

		for (const auto& [sut, nAddress] : filters)
		{
			CAPTURE(nAddress);
			for (const int32_t nPos : { 0, 1, 15 })
			{
				compare_filter(sut, reinterpret_cast<CharFilter>(original_d2launch_address(nAddress)), "Account", nPos);
			}
		}

		// Some characters
		char c = 'a';
		CHECK_NE(MENU_AccountNameCharFilter(nullptr, 0, &c), 0);
		c = '#';
		CHECK_EQ(MENU_AccountNameCharFilter(nullptr, 0, &c), 0);
	}

	TEST_CASE_FIXTURE(D2LaunchUiFixture<NoOpFixture>, "D2Launch.0x6FA19EC0")
	{
		const auto original = reinterpret_cast<CharFilter>(original_d2launch_address(0x6FA19EC0));
		compare_filter(&MENU_PasswordCharFilter, original, "", 0);
		compare_filter(&MENU_PasswordCharFilter, original, "secret", 6);
	}

	TEST_CASE_FIXTURE(D2LaunchUiFixture<NoOpFixture>, "D2Launch.0x6FA1C0E0")
	{
		const auto original = reinterpret_cast<CharFilter>(original_d2launch_address(0x6FA1C0E0));

		// '-' and '_' are only accepted once, and not as the first character
		for (const char* szText : { "", "Name", "Na-me", "Na_me", "-", "_name" })
		{
			for (const int32_t nPos : { 0, 1, 3, 15 })
			{
				CAPTURE(szText);
				CAPTURE(nPos);
				compare_filter(&MENU_CharacterNameCharFilter, original, szText, nPos);
			}
		}

		auto wszText = unicode("Name");
		char c = '-';
		CHECK_NE(MENU_CharacterNameCharFilter(reinterpret_cast<D2WinEditBoxStrc*>(wszText.data()), 2, &c), 0);
		CHECK_EQ(MENU_CharacterNameCharFilter(reinterpret_cast<D2WinEditBoxStrc*>(wszText.data()), 0, &c), 0);
	}

	TEST_CASE_FIXTURE(D2LaunchUiFixture<NoOpFixture>, "D2Launch.0x6FA14520")
	{
		const auto [sut, original] = make_d2launch_pair(CHARSEL_GetClassName, 0x6FA14520);

		for (int nClass = 0; nClass < 256; ++nClass)
		{
			CAPTURE(nClass);
			Unicode moo_buffer[32] = { (Unicode)'x', 0 }, original_buffer[32] = { (Unicode)'x', 0 };

			D2LangStringMock::calls.clear();
			const Unicode* moo_result = sut(moo_buffer, (uint8_t)nClass);
			const auto moo_calls = D2LangStringMock::calls;

			D2LangStringMock::calls.clear();
			const Unicode* original_result = original(original_buffer, (uint8_t)nClass);
			const auto original_calls = D2LangStringMock::calls;

			CHECK_EQ(moo_calls, original_calls);
			CHECK_EQ(moo_result == moo_buffer, original_result == original_buffer);
			CHECK_EQ(std::memcmp(moo_buffer, original_buffer, sizeof(moo_buffer)), 0);
		}
	}

	TEST_CASE("D2Launch.0x6FA14600")
	{
		const auto [sut, original] = make_d2launch_pair(CHARSEL_GetDaysBeforeExpiration, 0x6FA14600);

		const uint32_t nNow = (uint32_t)time(nullptr);
		// Half days, so that the time passed between both calls does not matter
		for (const int64_t nOffset : { -1000000LL, -43200LL, 43200LL, 86400LL + 43200LL, 59 * 86400LL + 43200LL, 61 * 86400LL + 43200LL, 1000 * 86400LL + 43200LL })
		{
			CAPTURE(nOffset);
			const uint32_t dwExpirationTime = (uint32_t)(nNow + nOffset);
			CHECK_EQ(sut(dwExpirationTime), original(dwExpirationTime));
		}

		CHECK_EQ(sut(0), original(0));
		CHECK_EQ(sut(nNow + 10 * 86400 + 43200), 10);
	}
}
