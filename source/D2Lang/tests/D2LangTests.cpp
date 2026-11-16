#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <D2Unicode.h>
#include <D2StrTable.h>

#include <string>

#define D2_USTR(widestr) (const Unicode*)widestr

TEST_CASE("Unicode::directionality")
{
    SUBCASE("ASCII letters")
    {
        CHECK(Unicode(L'a').directionality() == Unicode::DIR_LEFT_TO_RIGHT);
        CHECK(Unicode(L'A').directionality() == Unicode::DIR_LEFT_TO_RIGHT);
    }
    SUBCASE("ASCII digits")
    {
        CHECK(Unicode(L'0').directionality() == Unicode::DIR_LEFT_TO_RIGHT);
    }
    SUBCASE("Whitespace")
    {
        CHECK(Unicode(L' ').directionality() == Unicode::DIR_NEUTRAL);
        CHECK(Unicode(L'\t').directionality() == Unicode::DIR_NEUTRAL);
        CHECK(Unicode(L'\n').directionality() == Unicode::DIR_NEUTRAL);
    }
    SUBCASE("Right-to-left")
    {
        // Hebrew
        CHECK(Unicode(0x590).directionality() == Unicode::DIR_RIGHT_TO_LEFT);
        // Right-to-Left Mark
        CHECK(Unicode(0x200F).directionality() == Unicode::DIR_RIGHT_TO_LEFT);
    }
}

TEST_CASE("Unicode::sprintf")
{
    // TODO: prefill dest buffer with tombstone to check if we overflowed
    SUBCASE("Empty")
    {
        Unicode dest[256];
        Unicode::sprintf(256, dest, D2_USTR(L""));
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Empty with args")
    {
        Unicode dest[256];
        Unicode::sprintf(256, dest, D2_USTR(L""), 123, L"456", 789u);
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Copy string")
    {
        Unicode dest[256];
        Unicode::sprintf(256, dest, D2_USTR(L"Diablo"));
        CHECK(wcscmp((wchar_t*)dest, L"Diablo") == 0);
    }
    SUBCASE("Format %")
    {
        Unicode dest[256];
        Unicode::sprintf(256, dest, D2_USTR(L"%%%%%%%%%%"));
        CHECK(wcscmp((wchar_t*)dest, L"%%%%%") == 0);
    }
    SUBCASE("Format int")
    {
        Unicode dest[256];
        Unicode::sprintf(256, dest, D2_USTR(L"%d"), -2000000000);
        CHECK(wcscmp((wchar_t*)dest, L"-2000000000") == 0);
    }
    SUBCASE("Format unsigned int")
    {
        Unicode dest[256];
        Unicode::sprintf(256, dest, D2_USTR(L"%u"), 4000000000u);
        CHECK(wcscmp((wchar_t*)dest, L"4000000000") == 0);
    }
    SUBCASE("Format string")
    {
        SUBCASE("Normal")
        {
            Unicode dest[256];
            Unicode::sprintf(256, dest, D2_USTR(L"BeforeString:%s:AfterString"), D2_USTR(L"Diablo"));
            CHECK(wcscmp((wchar_t*)dest, L"BeforeString:Diablo:AfterString") == 0);
        }
        SUBCASE("Empty")
        {
            Unicode dest[256];
            Unicode::sprintf(256, dest, D2_USTR(L"BeforeString:%s"), D2_USTR(L""));
            CHECK(wcscmp((wchar_t*)dest, L"BeforeString:") == 0);
        }
        SUBCASE("nullptr")
        {
            Unicode dest[256];
            Unicode::sprintf(256, dest, D2_USTR(L"BeforeString:%s"), nullptr);
            CHECK(wcscmp((wchar_t*)dest, L"BeforeString:") == 0);
        }
    }
    SUBCASE("Format combination")
    {
        Unicode dest[256];
        Unicode::sprintf(
                256,
                dest,
                D2_USTR(L"%s (%u + %d)"),
                D2_USTR(L"Diablo"),
                3u,
                -1);
        CHECK(wcscmp((wchar_t*)dest, L"Diablo (3 + -1)") == 0);
    }
    SUBCASE("Copy truncated string")
    {
        Unicode dest[256];
        Unicode::sprintf(4, dest, D2_USTR(L"Diablo"));
        CHECK(wcscmp((wchar_t*)dest, L"Dia") == 0);
    }
    SUBCASE("Format truncated %")
    {
        Unicode dest[256];
        Unicode::sprintf(4, dest, D2_USTR(L"%%%%%%%%%%"));
        CHECK(wcscmp((wchar_t*)dest, L"%%%") == 0);
    }
    SUBCASE("Format truncated int")
    {
        Unicode dest[256];
        Unicode::sprintf(4, dest, D2_USTR(L"%d"), -2000000000);
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Format truncated unsigned int")
    {
        Unicode dest[256];
        Unicode::sprintf(4, dest, D2_USTR(L"%u"), 4000000000u);
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Format truncated string")
    {
        Unicode dest[256];
        Unicode::sprintf(4, dest, D2_USTR(L"%s"), D2_USTR(L"Diablo"));
        CHECK(wcscmp((wchar_t*)dest, L"Dia") == 0);
    }    
    SUBCASE("% consumes an argument")
    {
        Unicode dest[256];
        Unicode::sprintf(256, dest, D2_USTR(L"%d%%%d"), 1, 2, 3);
        CHECK(wcscmp((wchar_t*)dest, L"1%3") == 0);
    }
    SUBCASE("Ends with string is null-terminated")
    {
        Unicode dest[256];
        for (Unicode& ch : dest) ch = L'X';
        Unicode::sprintf(256, dest, D2_USTR(L"a%s"), D2_USTR(L"bc"));
        CHECK(wcscmp((wchar_t*)dest, L"abc") == 0);
    }
    SUBCASE("Ends with %")
    {
        Unicode dest[256];
        Unicode::sprintf(256, dest, D2_USTR(L"Diablo%"));
        CHECK(wcscmp((wchar_t*)dest, L"Diablo%") == 0);
    }
}

TEST_CASE("Unicode::isWordEnd")
{
    SUBCASE("Index 0")
    {
        CHECK(!Unicode::isWordEnd(D2_USTR(L"0 2345678"), 0));
        CHECK(!Unicode::isWordEnd(D2_USTR(L"A soulstone"), 0));
    }
    SUBCASE("Before whitespace")
    {
        CHECK(Unicode::isWordEnd(D2_USTR(L"0123 5678"), 3));
        CHECK(Unicode::isWordEnd(D2_USTR(L"The soulstone"), 2));
    }
    SUBCASE("On whitespace")
    {
        CHECK(!Unicode::isWordEnd(D2_USTR(L"0123 5678"), 4));
        CHECK(!Unicode::isWordEnd(D2_USTR(L"The soulstone"), 3));
    }
    SUBCASE("Middle of word")
    {
        CHECK(!Unicode::isWordEnd(D2_USTR(L"0123 5678"), 2));
        CHECK(!Unicode::isWordEnd(D2_USTR(L"The soulstone"), 7));
    }
    SUBCASE("End of string")
    {
        CHECK(Unicode::isWordEnd(D2_USTR(L"0123 5678"), wcslen(L"0123 5678") - 1));
        CHECK(Unicode::isWordEnd(D2_USTR(L"The soulstone"), wcslen(L"The soulstone") - 1));
    }
}

TEST_CASE("Unicode::strcat")
{
    SUBCASE("Concatenate empty on empty")
    {
        Unicode dest[256];
        Unicode::strcat(dest, D2_USTR(L""));
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Concatenate text on empty")
    {
        Unicode dest[256];
        Unicode::strcat(dest, D2_USTR(L"Diablo"));
        CHECK(wcscmp((wchar_t*)dest, L"Diablo") == 0);
    }
    SUBCASE("Concatenate text on not empty")
    {
        Unicode dest[256] = { L'3', L':', L' ' };
        Unicode::strcat(dest, D2_USTR(L"Mephisto, "));
        Unicode::strcat(dest, D2_USTR(L"Diablo, "));
        Unicode::strcat(dest, D2_USTR(L"and Baal"));
        CHECK(wcscmp((wchar_t*)dest, L"3: Mephisto, Diablo, and Baal") == 0);
    }
    SUBCASE("Concatenate at correct index")
    {
        Unicode dest[256];
        Unicode::strcat(dest, D2_USTR(L"Diablo"));
        dest[3] = L'\0';
        Unicode::strcat(dest, D2_USTR(L"mond"));
        CHECK(wcscmp((wchar_t*)dest, L"Diamond") == 0);
    }
}

TEST_CASE("Unicode::strchr")
{
    const Unicode* diablo = D2_USTR(L"Diablo");

    SUBCASE("Not found in Empty")
    {
        CHECK(Unicode::strchr(D2_USTR(L""), L'D') == nullptr);
        CHECK(Unicode::strchr(D2_USTR(L""), L'\0') == nullptr);
    }
    SUBCASE("Found in 'Diablo'")
    {
        CHECK(Unicode::strchr(diablo, L'D') == &diablo[0]);
        CHECK(Unicode::strchr(diablo, L'a') == &diablo[2]);
        CHECK(Unicode::strchr(diablo, L'b') == &diablo[3]);
    }
    SUBCASE("Not found in 'Diablo'")
    {
        CHECK(Unicode::strchr(diablo, L'j') == nullptr);
        CHECK(Unicode::strchr(diablo, 0x190) == nullptr);
        CHECK(Unicode::strchr(diablo, L'\0') == nullptr);
    }
}

TEST_CASE("Unicode::strcmp")
{
    SUBCASE("Ordering")
    {
        CHECK(Unicode::strcmp(D2_USTR(L"0"), D2_USTR(L"0")) == 0);
        CHECK(Unicode::strcmp(D2_USTR(L"0"), D2_USTR(L"1")) == -1);
        CHECK(Unicode::strcmp(D2_USTR(L"1"), D2_USTR(L"0")) ==  1);
    }
    SUBCASE("Case sensitive")
    {
        CHECK(Unicode::strcmp(D2_USTR(L"Diablo2"), D2_USTR(L"DIABLO2")) == 1);
        CHECK(Unicode::strcmp(D2_USTR(L"DIABLO2"), D2_USTR(L"Diablo2")) == -1);
    }
}

TEST_CASE("Unicode::strcpy")
{
    SUBCASE("Empty onto empty")
    {
        Unicode dest[256];
        CHECK(Unicode::strcpy(dest, D2_USTR(L"")) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Text onto empty")
    {
        Unicode dest[256];
        CHECK(Unicode::strcpy(dest, D2_USTR(L"Diablo")) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"Diablo") == 0);
    }
    SUBCASE("Text onto not empty")
    {
        Unicode dest[256] = { L'D', L'i', L'a', L'b', L'l', L'o' };
        CHECK(Unicode::strcpy(dest, D2_USTR(L"Baal")) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"Baal") == 0);
    }
}

TEST_CASE("Unicode::stricmp")
{
    SUBCASE("Ordering")
    {
        CHECK(Unicode::stricmp(D2_USTR(L"0"), D2_USTR(L"0")) == 0);
        CHECK(Unicode::stricmp(D2_USTR(L"0"), D2_USTR(L"1")) == -1);
        CHECK(Unicode::stricmp(D2_USTR(L"1"), D2_USTR(L"0")) ==  1);
    }
    SUBCASE("Case sensitive")
    {
        CHECK(Unicode::stricmp(D2_USTR(L"Diablo2"), D2_USTR(L"DIABLO2")) == 0);
        CHECK(Unicode::stricmp(D2_USTR(L"DIABLO2"), D2_USTR(L"Diablo2")) == 0);
    }
}

TEST_CASE("Unicode::strncat")
{
    SUBCASE("Concatenate empty on empty")
    {
        Unicode dest[256];
        Unicode::strncat(dest, D2_USTR(L""), INT_MAX);
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Concatenate text on empty")
    {
        Unicode dest[256];
        Unicode::strncat(dest, D2_USTR(L"Diablo"), INT_MAX);
        CHECK(wcscmp((wchar_t*)dest, L"Diablo") == 0);
    }
    SUBCASE("Concatenate text on not empty")
    {
        Unicode dest[256] = { L'3', L':', L' ' };
        Unicode::strncat(dest, D2_USTR(L"Mephisto, "), INT_MAX);
        Unicode::strncat(dest, D2_USTR(L"Diablo, "), INT_MAX);
        Unicode::strncat(dest, D2_USTR(L"and Baal"), INT_MAX);
        CHECK(wcscmp((wchar_t*)dest, L"3: Mephisto, Diablo, and Baal") == 0);
    }
    SUBCASE("Concatenate at correct index")
    {
        Unicode dest[256];
        Unicode::strncat(dest, D2_USTR(L"Diablo"), INT_MAX);
        dest[3] = L'\0';
        Unicode::strncat(dest, D2_USTR(L"mond"), INT_MAX);
        CHECK(wcscmp((wchar_t*)dest, L"Diamond") == 0);
    }
    SUBCASE("Concatenate partial text")
    {
        Unicode dest[256];
        Unicode::strncat(dest, D2_USTR(L"Diablo"), INT_MAX);
        dest[3] = L'\0';
        Unicode::strncat(dest, D2_USTR(L"mond"), 3);
        CHECK(wcscmp((wchar_t*)dest, L"Diamon") == 0);
    }
}

TEST_CASE("Unicode::strncmp")
{
    const size_t strLenDiablo2 = wcslen(L"Diablo2");

    SUBCASE("Ordering")
    {
        CHECK(Unicode::strncmp(D2_USTR(L"0"), D2_USTR(L"0"), 1) == 0);
        CHECK(Unicode::strncmp(D2_USTR(L"0"), D2_USTR(L"1"), 1) == -1);
        CHECK(Unicode::strncmp(D2_USTR(L"1"), D2_USTR(L"0"), 1) ==  1);
    }
    SUBCASE("Case sensitive")
    {
        CHECK(Unicode::strncmp(D2_USTR(L"Diablo2"), D2_USTR(L"DIABLO2"), strLenDiablo2) == 1);
        CHECK(Unicode::strncmp(D2_USTR(L"DIABLO2"), D2_USTR(L"Diablo2"), strLenDiablo2) == -1);
    }
    SUBCASE("Number of characters to compare")
    {
        CHECK(Unicode::strncmp(D2_USTR(L"Diablo2"), D2_USTR(L"Diablo2"), 0) == 0);
        CHECK(Unicode::strncmp(D2_USTR(L"Diablo2"), D2_USTR(L"Diablo2"), strLenDiablo2) == 0);
        
        CHECK(Unicode::strncmp(D2_USTR(L"Diablo2"), D2_USTR(L"Diablo3"), strLenDiablo2 - 1) == 0);
        CHECK(Unicode::strncmp(D2_USTR(L"Diablo2"), D2_USTR(L"Diablo3"), strLenDiablo2) != 0);
    }
    SUBCASE("Original game bug")
    {
        // Any string that is the prefix of the other is accepted.
        CHECK(Unicode::strncmp(D2_USTR(L"Diablo"), D2_USTR(L"Diablo2"),strLenDiablo2) == 0);
        CHECK(Unicode::strncmp(D2_USTR(L"Diablo2"), D2_USTR(L"Diablo"),strLenDiablo2) == 0);

        CHECK(Unicode::strncmp(D2_USTR(L""), D2_USTR(L"Diablo2"), strLenDiablo2) == 0);
        CHECK(Unicode::strncmp(D2_USTR(L"Diablo2"), D2_USTR(L""), strLenDiablo2) == 0);
    }
}

TEST_CASE("Unicode::strncpy")
{
    SUBCASE("Empty onto empty")
    {
        Unicode dest[256];
        CHECK(Unicode::strncpy(dest, D2_USTR(L""), 1) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Empty onto non-empty")
    {
        Unicode dest[256] = { L'D', L'i', L'a', L'b', L'l', L'o' };
        CHECK(Unicode::strncpy(dest, D2_USTR(L""), 7) == dest);
        CHECK(wmemcmp((wchar_t*)dest, L"\0\0\0\0\0\0", 7) == 0);
    }
    SUBCASE("Text onto empty")
    {
        Unicode dest[256];
        CHECK(Unicode::strncpy(dest, D2_USTR(L"Diablo"), 7) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"Diablo") == 0);
    }
    SUBCASE("Text overfill onto empty")
    {
        Unicode dest[256];
        CHECK(Unicode::strncpy(dest, D2_USTR(L"Diablo"), 13) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"Diablo\0\0\0\0\0\0") == 0);
    }
    SUBCASE("Text onto non-empty")
    {
        Unicode dest[256] = { L'D', L'i', L'a', L'b', L'l', L'o' };
        CHECK(Unicode::strncpy(dest, D2_USTR(L"Baal"), 5) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"Baal") == 0);
    }
    SUBCASE("Text overfill onto non-empty")
    {
        Unicode dest[256] = { L'D', L'i', L'a', L'b', L'l', L'o' };
        CHECK(Unicode::strncpy(dest, D2_USTR(L"Baal"), 9) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"Baal\0\0\0\0") == 0);
    }
}

TEST_CASE("Unicode::strlen")
{
    SUBCASE("Empty")
    {
        CHECK(Unicode::strlen(D2_USTR(L"")) == 0);
    }
    SUBCASE("Not empty")
    {
        CHECK(Unicode::strlen(D2_USTR(L"Diablo2")) == 7);
        CHECK(Unicode::strlen(D2_USTR(L"Mephisto")) == 8);
        CHECK(Unicode::strlen(D2_USTR(L"Baal")) == 4);
    }
    SUBCASE("Null")
    {
        CHECK(Unicode::strlen(nullptr) == 0);
    }
}

TEST_CASE("Unicode::strstr")
{
    const Unicode* diablo = D2_USTR(L"Diablo");

    SUBCASE("Empty")
    {
        CHECK(Unicode::strstr(D2_USTR(L""), D2_USTR(L"")) == nullptr);
        CHECK(Unicode::strstr(diablo, D2_USTR(L"")) == nullptr);
        CHECK(Unicode::strstr(D2_USTR(L""), diablo) == nullptr);
    }
    SUBCASE("Found")
    {
        CHECK(Unicode::strstr(diablo, diablo) == diablo);
        CHECK(Unicode::strstr(diablo, D2_USTR(L"i")) == &diablo[1]);
        CHECK(Unicode::strstr(diablo, D2_USTR(L"abl")) == &diablo[2]);
    }
    SUBCASE("Not found")
    {
        CHECK(Unicode::strstr(diablo, D2_USTR(L"Baal")) == nullptr);
        CHECK(Unicode::strstr(diablo, D2_USTR(L"Lord of Terror")) == nullptr);
    }
    SUBCASE("Case sensitive")
    {
        CHECK(Unicode::strstr(diablo, D2_USTR(L"diablo")) == nullptr);
        CHECK(Unicode::strstr(diablo, D2_USTR(L"DIABLO")) == nullptr);
    }
    SUBCASE("Null")
    {
        CHECK(Unicode::strstr(nullptr, nullptr) == nullptr);
        CHECK(Unicode::strstr(nullptr, D2_USTR(L"Diablo")) == nullptr);
        CHECK(Unicode::strstr(D2_USTR(L"Diablo"), nullptr) == nullptr);
    }
}

TEST_CASE("Unicode::strstri")
{
    const Unicode* str = D2_USTR(L"Diablo II Lord of Destruction");
    CHECK(Unicode::strstri(str, D2_USTR(L"lord")) == str + 10);
    CHECK(Unicode::strstri(str, D2_USTR(L"DIABLO")) == str);
    CHECK(Unicode::strstri(str, D2_USTR(L"destructION")) == str + 18);
    CHECK(Unicode::strstri(str, D2_USTR(L"Baal")) == nullptr);
    CHECK(Unicode::strstri(str, D2_USTR(L"destructions")) == nullptr);
    CHECK(Unicode::strstri(D2_USTR(L"aaab"), D2_USTR(L"AAB")) == D2_USTR(L"aaab") + 1);
    CHECK(Unicode::strstri(nullptr, D2_USTR(L"a")) == nullptr);
    CHECK(Unicode::strstri(str, nullptr) == nullptr);
}

TEST_CASE("Unicode::strcoll")
{
    CHECK(Unicode::strcoll(D2_USTR(L"abc"), D2_USTR(L"abc")) == 0);
    CHECK(Unicode::strcoll(D2_USTR(L"abc"), D2_USTR(L"abd")) < 0);
    CHECK(Unicode::strcoll(D2_USTR(L"abd"), D2_USTR(L"abc")) > 0);
    // Case is ignored by the collation table
    CHECK(Unicode::strcoll(D2_USTR(L"ABC"), D2_USTR(L"abc")) == 0);
    // Accented letters collate with their base letter, before the next letter
    CHECK(Unicode::strcoll(D2_USTR(L"\u00E9a"), D2_USTR(L"eb")) < 0);
    CHECK(Unicode::strcoll(D2_USTR(L"\u00E9"), D2_USTR(L"f")) < 0);
    // Prefix
    CHECK(Unicode::strcoll(D2_USTR(L"ab"), D2_USTR(L"abc")) < 0);
    CHECK(Unicode::strcoll(D2_USTR(L"abc"), D2_USTR(L"ab")) > 0);
    CHECK(Unicode::strcoll(D2_USTR(L""), D2_USTR(L"a")) < 0);
}

TEST_CASE("Unicode::strnicmp")
{
    CHECK(Unicode::strnicmp(D2_USTR(L"abc"), D2_USTR(L"ABC"), 3) == 0);
    CHECK(Unicode::strnicmp(D2_USTR(L"abc"), D2_USTR(L"abd"), 3) == -1);
    CHECK(Unicode::strnicmp(D2_USTR(L"abd"), D2_USTR(L"ABC"), 3) == 1);
    CHECK(Unicode::strnicmp(D2_USTR(L"abc"), D2_USTR(L"abd"), 2) == 0);
    // Vanilla bug: prefixes compare equal
    CHECK(Unicode::strnicmp(D2_USTR(L"ab"), D2_USTR(L"abc"), 3) == 0);
    CHECK(Unicode::strnicmp(D2_USTR(L"abc"), D2_USTR(L"ab"), 3) == 0);
    // Vanilla bug: the first character is compared even if count is 0
    CHECK(Unicode::strnicmp(D2_USTR(L"a"), D2_USTR(L"b"), 0) == -1);
    CHECK(Unicode::strnicmp(D2_USTR(L""), D2_USTR(L"a"), 3) == -1);
}

TEST_CASE("Unicode::strncoll")
{
    CHECK(Unicode::strncoll(D2_USTR(L"abc"), D2_USTR(L"abd"), 2) == 0);
    CHECK(Unicode::strncoll(D2_USTR(L"abc"), D2_USTR(L"abd"), 3) < 0);
}

TEST_CASE("Unicode::isLeftToRight")
{
    CHECK(Unicode(L'a').isLeftToRight());
    CHECK(Unicode(0x58F).isLeftToRight());
    CHECK_FALSE(Unicode(0x590).isLeftToRight());
    CHECK_FALSE(Unicode(0x5FF).isLeftToRight());
    CHECK_FALSE(Unicode(0x600).isLeftToRight());
    CHECK_FALSE(Unicode(0x6FF).isLeftToRight());
    CHECK(Unicode(0x700).isLeftToRight());
}

TEST_CASE("Unicode::toLower")
{
    SUBCASE("Upper to lower")
    {
        CHECK(Unicode(L'A').toLower() == L'a');
        CHECK(Unicode(L'Z').toLower() == L'z');
    }
    SUBCASE("Not alpha")
    {
        CHECK(Unicode(L'\0').toLower() == L'\0');
        CHECK(Unicode(L'0').toLower() == L'0');
        CHECK(Unicode(L' ').toLower() == L' ');
    }
    SUBCASE("Already lower")
    {
        CHECK(Unicode(L'a').toLower() == L'a');
        CHECK(Unicode(L'z').toLower() == L'z');
    }
}

TEST_CASE("Unicode::toUpper")
{
    SUBCASE("Lower to upper")
    {
        CHECK(Unicode(L'a').toUpper() == L'A');
        CHECK(Unicode(L'z').toUpper() == L'Z');
    }
    SUBCASE("Not alpha")
    {
        CHECK(Unicode(L'\0').toUpper() == L'\0');
        CHECK(Unicode(L'0').toUpper() == L'0');
        CHECK(Unicode(L' ').toUpper() == L' ');
    }
    SUBCASE("Already upper")
    {
        CHECK(Unicode(L'A').toUpper() == L'A');
        CHECK(Unicode(L'Z').toUpper() == L'Z');
    }
}

TEST_CASE("Unicode::toUtf")
{
    constexpr size_t dest_capacity = 256;
    char dest[dest_capacity];

    // The official name of Diablo in Japanese
    const wchar_t* utf16JpDiablo = L"\u30C7\u30A3\u30A2\u30D6\u30ED";
    const char* utf8JpDiablo = "\xE3\x83\x87\xE3\x82\xA3\xE3\x82\xA2\xE3\x83\x96\xE3\x83\xAD";

    SUBCASE("Empty")
    {
        CHECK(Unicode::toUtf(dest, D2_USTR(L""), dest_capacity) == dest);
        CHECK(strcmp(dest, "") == 0);
    }
    SUBCASE("Convert ASCII text")
    {
        Unicode::toUtf(dest, D2_USTR(L"Diablo"), dest_capacity);
        CHECK(strcmp(dest, "Diablo") == 0);
    }
    SUBCASE("Partially convert ASCII text")
    {
        Unicode::toUtf(dest, D2_USTR(L"Diablo"), 4);
        CHECK(strcmp(dest, "Dia") == 0);
    }
    SUBCASE("Convert Japanese text")
    {
        Unicode::toUtf(dest, D2_USTR(utf16JpDiablo), dest_capacity);
        CHECK(strcmp(dest, utf8JpDiablo) == 0);
    }
    SUBCASE("Partially convert Japanese text")
    {
        Unicode::toUtf(dest, D2_USTR(utf16JpDiablo), 7);
        CHECK(strncmp(dest, utf8JpDiablo, 6) == 0);
    }
}

TEST_CASE("Unicode::toUnicode")
{
    constexpr size_t dest_capacity = 256;
    Unicode dest[dest_capacity];

    // The official name of Diablo in Japanese
    const char* utf8JpDiablo = "\xE3\x83\x87\xE3\x82\xA3\xE3\x82\xA2\xE3\x83\x96\xE3\x83\xAD";
    const wchar_t* utf16JpDiablo = L"\u30C7\u30A3\u30A2\u30D6\u30ED";

    SUBCASE("Empty")
    {
        CHECK(Unicode::toUnicode(dest, "", dest_capacity) == dest);
        CHECK(wcscmp((wchar_t*)dest, L"") == 0);
    }
    SUBCASE("Convert ASCII text")
    {
        Unicode::toUnicode(dest, "Diablo", dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"Diablo") == 0);
    }
    SUBCASE("Partially convert ASCII text")
    {
        Unicode::toUnicode(dest, "Diablo", 4);
        CHECK(wcscmp((wchar_t*)dest, L"Dia") == 0);
    }
    SUBCASE("Convert Japanese text")
    {
        Unicode::toUnicode(dest, utf8JpDiablo, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, utf16JpDiablo) == 0);
    }
    SUBCASE("Partially convert Japanese text")
    {
        Unicode::toUnicode(dest, utf8JpDiablo, 3);
        CHECK(wcsncmp((wchar_t*)dest, utf16JpDiablo, 2) == 0);
    }
}

TEST_CASE("STR_GroupIntDigits")
{
    constexpr size_t dest_capacity = 256;
    Unicode dest[dest_capacity];

    SUBCASE("0")
    {
        STR_GroupIntDigits(dest, 0, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"0") == 0);
    }
    SUBCASE("1")
    {
        STR_GroupIntDigits(dest, 1, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"1") == 0);
    }
    SUBCASE("-1")
    {
        STR_GroupIntDigits(dest, -1, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"-1") == 0);
    }
    SUBCASE("1234567890")
    {
        STR_GroupIntDigits(dest, 1234567890, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"1,234,567,890") == 0);
    }
    SUBCASE("-1234567890")
    {
        STR_GroupIntDigits(dest, -1234567890, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"-1,234,567,890") == 0);
    }
    SUBCASE("Low max length, positive value")
    {
        STR_GroupIntDigits(dest, 1234567890, 13);
        CHECK(wcscmp((wchar_t*)dest, L"*") == 0);
    }
    SUBCASE("Low max length, negative value")
    {
        STR_GroupIntDigits(dest, -1234567890, 14);
        CHECK(wcscmp((wchar_t*)dest, L"-*") == 0);
    }
}

TEST_CASE("STR_GroupUintDigits")
{
    constexpr size_t dest_capacity = 256;
    Unicode dest[dest_capacity];

    SUBCASE("0")
    {
        STR_GroupUintDigits(dest, 0, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"0") == 0);
    }
    SUBCASE("1")
    {
        STR_GroupUintDigits(dest, 1, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"1") == 0);
    }
    SUBCASE("1234567890")
    {
        STR_GroupUintDigits(dest, 1234567890, dest_capacity);
        CHECK(wcscmp((wchar_t*)dest, L"1,234,567,890") == 0);
    }
    SUBCASE("Low max length")
    {
        STR_GroupUintDigits(dest, 1234567890, 13);
        CHECK(wcscmp((wchar_t*)dest, L"*") == 0);
    }
}

TEST_CASE("Unicode::utfwidth")
{
    CHECK(Unicode(L'a').utfwidth() == 1);
    CHECK(Unicode(0xE9).utfwidth() == 2);
    CHECK(Unicode(0x3042).utfwidth() == 3);
}

TEST_CASE("Unicode::utfnwidth")
{
    CHECK(Unicode::utfnwidth(D2_USTR(L"a\u00E9\u3042"), 10) == 6);
    CHECK(Unicode::utfnwidth(D2_USTR(L"a\u00E9\u3042"), 2) == 3);
    CHECK(Unicode::utfnwidth(D2_USTR(L""), 10) == 0);
}

TEST_CASE("Unicode::unicodenwidth")
{
    CHECK(Unicode::unicodenwidth("a\xC3\xA9\xE3\x81\x82", 10) == 3);
    CHECK(Unicode::unicodenwidth("a\xC3\xA9\xE3\x81\x82", 3) == 2);
    // Characters outside of the BMP are counted too
    CHECK(Unicode::unicodenwidth("\xF0\x90\x80\x80", 10) == 1);
    // Invalid bytes are skipped
    CHECK(Unicode::unicodenwidth("\x80\x80a", 10) == 1);
}

TEST_CASE("Unicode sys map fallbacks")
{
    // Without a loaded sys map, the functions behave like their Windows-1252/strlen counterparts
    CHECK(Unicode::sysWidth(D2_USTR(L"Diablo"), 2) == 6);
    CHECK(Unicode::unicodeWidth("Diablo", 2) == 6);

    Unicode unicode[16];
    Unicode::sys2Unicode(unicode, "Diablo", 16);
    CHECK(wcscmp((wchar_t*)unicode, L"Diablo") == 0);

    char sys[16];
    Unicode::unicode2Sys(sys, D2_USTR(L"Diablo"), 16);
    CHECK(strcmp(sys, "Diablo") == 0);
}

TEST_CASE("Unicode::Personalize")
{
    Unicode dest[64];
    auto personalize = [&](const wchar_t* name, D2C_Language language) {
        Unicode::Personalize(dest, D2_USTR(name), D2_USTR(L"Sword"), 64, (ELANGUAGE)language);
        return std::wstring((const wchar_t*)dest);
    };
    CHECK(personalize(L"Bob", LANGUAGE_ENGLISH) == L"Bob's Sword");
    CHECK(personalize(L"Bobs", LANGUAGE_ENGLISH) == L"Bobs' Sword");
    CHECK(personalize(L"Bob", LANGUAGE_GERMAN) == L"Bobs Sword");
    CHECK(personalize(L"Hans", LANGUAGE_GERMAN) == L"Hans' Sword");
    CHECK(personalize(L"Bob", LANGUAGE_SPANISH) == L"Sword de Bob");
    CHECK(personalize(L"Bob", LANGUAGE_FRENCH) == L"Sword de Bob");
    CHECK(personalize(L"alice", LANGUAGE_FRENCH) == L"Sword d'alice");
    CHECK(personalize(L"Bob", LANGUAGE_ITALIAN) == L"Sword di Bob");
    CHECK(personalize(L"Bob", LANGUAGE_POLISH) == L"Sword(Bob) ");
    CHECK(personalize(L"Bob", LANGUAGE_JAPANESE) == L"(Bob) Sword");

    SUBCASE("Too long")
    {
        for (Unicode& ch : dest) ch = L'X';
        Unicode::Personalize(dest, D2_USTR(L"Bob"), D2_USTR(L"Sword"), 12, (ELANGUAGE)LANGUAGE_ENGLISH);
        CHECK(std::wstring((const wchar_t*)dest) == L"Sword");
    }
}

TEST_CASE("STR_GroupInt64Digits")
{
    Unicode dest[64];
    STR_GroupInt64Digits(dest, 1234567890123LL, 64);
    CHECK(wcscmp((wchar_t*)dest, L"1,234,567,890,123") == 0);
    STR_GroupInt64Digits(dest, -1234567890123LL, 64);
    CHECK(wcscmp((wchar_t*)dest, L"-1,234,567,890,123") == 0);
    STR_GroupInt64Digits(dest, 0, 64);
    CHECK(wcscmp((wchar_t*)dest, L"0") == 0);
    STR_GroupInt64Digits(dest, 1234567890123LL, 17);
    CHECK(wcscmp((wchar_t*)dest, L"*") == 0);
}

TEST_CASE("STR_GroupUint64DigitsWithSuffix")
{
    Unicode dest[64];
    STR_GroupUint64DigitsWithSuffix(dest, 999, 64);
    CHECK(wcscmp((wchar_t*)dest, L"999") == 0);
    STR_GroupUint64DigitsWithSuffix(dest, 999999, 64);
    CHECK(wcscmp((wchar_t*)dest, L"999,999") == 0);
    STR_GroupUint64DigitsWithSuffix(dest, 1234567, 64);
    CHECK(wcscmp((wchar_t*)dest, L"1,234K") == 0);
    STR_GroupUint64DigitsWithSuffix(dest, 1234567890, 64);
    CHECK(wcscmp((wchar_t*)dest, L"1,234M") == 0);
    STR_GroupUint64DigitsWithSuffix(dest, 1234567890123ULL, 64);
    CHECK(wcscmp((wchar_t*)dest, L"1,234B") == 0);
    STR_GroupUint64DigitsWithSuffix(dest, 1234567890123456ULL, 64);
    CHECK(wcscmp((wchar_t*)dest, L"1,234T") == 0);
    // At most 4 groups are removed
    STR_GroupUint64DigitsWithSuffix(dest, 1234567890123456789ULL, 64);
    CHECK(wcscmp((wchar_t*)dest, L"1,234,567T") == 0);
    STR_GroupUint64DigitsWithSuffix(dest, 1234567, 7);
    CHECK(wcscmp((wchar_t*)dest, L"*") == 0);
}

TEST_CASE("Unicode::toUnicode code points beyond the BMP")
{
    // Code points beyond 0xFFFF are decoded and truncated to 16 bits, like the original
    Unicode dest[8];
    Unicode::toUnicode(dest, "a\xF0\x9F\x98\x80" "b", 8);
    CHECK(dest[0].ch == L'a');
    CHECK(dest[1].ch == 0xF600);
    CHECK(dest[2].ch == L'b');
    CHECK(dest[3].ch == 0);
}

TEST_CASE("D2LANG_GetStringHash")
{
    CHECK(D2LANG_GetStringHash("", 100) == 0);
    CHECK(D2LANG_GetStringHash("a", 1000) == 'a');
    CHECK(D2LANG_GetStringHash("ab", 10000) == ('a' << 4) + 'b');
    CHECK(D2LANG_GetStringHash("ab", 7) == (('a' << 4) + 'b') % 7);
    // Characters are sign extended, then the high bits are folded
    CHECK(D2LANG_GetStringHash("\xE9", 0xFFFFFFFF) == ((0xFFFFFFE9 & 0x0FFFFFFF) ^ 0xF0));
}
