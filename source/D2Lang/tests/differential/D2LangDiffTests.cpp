// Differential tests: D2MOO's D2Lang implementation (linked statically) vs the original 1.10f D2Lang.dll (loaded at
// runtime), run under wine. See README.md.
//
// Usage: D2LangDiffTests.exe [group]
// Environment variables:
// - SEED: seed of the random inputs
// - TEST_LANGUAGE: language written to data\local\use by the "locale" group (must run first in the process, as both
//   implementations cache the language)
// - TEST_EXPANSION: whether the "strtable" group loads expansionstring.tbl (default 1)
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <functional>
#include <D2Unicode.h>
#include <D2StrTable.h>
#include <D2Crc16.h>
#include <D2Lang.h>
#include <limits.h>
#include <algorithm>
#include <wchar.h>
#define D2_USTR(widestr) (const Unicode*)widestr

static HMODULE gOrig;
template<class T> T ord(int o) { T p = (T)GetProcAddress(gOrig, MAKEINTRESOURCEA(o)); if (!p) { printf("missing ordinal %d\n", o); exit(2); } return p; }

static unsigned gSeed = 12345;
static unsigned rnd() { gSeed = gSeed * 1103515245u + 12345u; return (gSeed >> 8); }
static const unsigned short kAlphabet[] = { 'a','b','c','A','B','C','e','E',' ','1','%','\n','|',0xE9,0xC9,0xE0,0xFF,0x8A,0x9A,0x100,0x590,0x600,0x3042,0x4E00,0xAC00,0x7F,0x1F,0xD7 };
static std::vector<Unicode> rstr(int maxLen, const unsigned short* alpha = kAlphabet, int n = sizeof(kAlphabet)/2) {
    int len = rnd() % (maxLen + 1);
    std::vector<Unicode> v; for (int i = 0; i < len; ++i) v.push_back(Unicode(alpha[rnd() % n])); v.push_back(Unicode(0));
    for (int i = 0; i < 8; ++i) v.push_back(Unicode(0x1234)); // garbage after terminator to catch over-reads differences
    return v;
}
static std::string dump(const Unicode* s) { std::string r; char b[8]; for (; s->ch; ++s) { sprintf(b, s->ch < 0x80 && s->ch >= 0x20 ? "%c" : "\\x%X", s->ch); r += b; } return r; }

static std::string hexdump(const Unicode* s, int n) { std::string r; char b[8]; for (int i = 0; i < n; ++i) { sprintf(b, s[i].ch >= 0x20 && s[i].ch < 0x7F ? " %c" : " %X", s[i].ch); r += b; } return r; }
static std::string hexbytes(const std::string& s) { std::string r; char b[8]; for (unsigned char c : s) { sprintf(b, "%02X ", c); r += b; } return r; }
static int gFail = 0, gChecks = 0;
#define EXPECT_EQ(a, b, ...) do { auto _a = (a); auto _b = (b); ++gChecks; if (!(_a == _b)) { if (gFail++ < 30) { printf("MISMATCH %s:%d moo=%lld orig=%lld ", __FILE__, __LINE__, (long long)_a, (long long)_b); printf(__VA_ARGS__); printf("\n"); } } } while (0)

typedef int(__fastcall* strcoll_t)(const Unicode*, const Unicode*);
typedef int(__fastcall* strncoll_t)(const Unicode*, const Unicode*, int);
typedef Unicode*(__fastcall* strstri_t)(const Unicode*, const Unicode*);
typedef BOOL(__thiscall* member_bool_t)(const Unicode*);

static void test_collation() {
    auto o_strcoll = ord<strcoll_t>(10037);
    auto o_strncoll = ord<strncoll_t>(10043);
    auto o_strstri = ord<strstri_t>(10047);
    auto o_isltr = ord<member_bool_t>(10026);
    for (int i = 0; i < 20000; ++i) {
        auto a = rstr(6), b = rstr(6);
        if (rnd() % 3 == 0) { b = a; if (b.size() > 1 && rnd() % 2) b[rnd() % (b.size() - 1)] = Unicode(kAlphabet[rnd() % 8]); }
        EXPECT_EQ(Unicode::strcoll(a.data(), b.data()), o_strcoll(a.data(), b.data()), "strcoll '%s' '%s'", dump(a.data()).c_str(), dump(b.data()).c_str());
        int n = rnd() % 8;
        EXPECT_EQ(Unicode::strncoll(a.data(), b.data(), n), o_strncoll(a.data(), b.data(), n), "strncoll '%s' '%s' %d", dump(a.data()).c_str(), dump(b.data()).c_str(), n);
        static const unsigned short small[] = { 'a','b','A','B',0xE9,0xC9 };
        auto h = rstr(10, small, 6), nd = rstr(3, small, 6);
        if (h.size() > 1) { // the original reads past the terminator of empty strings
            EXPECT_EQ(Unicode::strstri(h.data(), nd.data()), o_strstri(h.data(), nd.data()), "strstri '%s' '%s'", dump(h.data()).c_str(), dump(nd.data()).c_str());
        }
    }
    for (unsigned c = 0; c < 0x10000; ++c) { Unicode u(c); EXPECT_EQ(u.isLeftToRight(), o_isltr(&u), "isLeftToRight %X", c); }
}


// Buffer helpers: both implementations write into buffers pre-filled with the same pattern, then the full buffers are compared.
template<class T> struct Buf { std::vector<T> moo, orig; Buf(size_t n) : moo(n + 16, T(0xCDCD)), orig(n + 16, T(0xCDCD)) {} bool same() const { return memcmp(moo.data(), orig.data(), moo.size() * sizeof(T)) == 0; } };
static std::string ascii(int maxLen) { std::string s; int n = rnd() % (maxLen + 1); for (int i = 0; i < n; ++i) { static const char a[] = "abcXYZ 019%|\n\t,.-"; s += a[rnd() % (sizeof(a) - 1)]; } return s; }
static std::string bytes(int maxLen) { std::string s; int n = rnd() % (maxLen + 1); for (int i = 0; i < n; ++i) { int r = rnd() % 4; s += (char)(r == 0 ? 0x80 + rnd() % 0x80 : r == 1 ? 0xC0 + rnd() % 0x3F : r == 2 ? 0x20 + rnd() % 0x60 : 0xE0 + rnd() % 0x20); } return s; }

typedef BOOL(__thiscall* m_bool_t)(const Unicode*);
typedef int(__thiscall* m_int_t)(const Unicode*);
typedef void(__thiscall* m_ret_unicode_t)(const Unicode*, Unicode*);
typedef BOOL(__thiscall* m_compare_t)(const Unicode*, unsigned);
typedef BOOL(__stdcall* s_compare_t)(unsigned, unsigned);
typedef BOOL(__fastcall* str_size_bool_t)(const Unicode*, size_t);
typedef Unicode*(__fastcall* strchr_t)(const Unicode*, int, unsigned);
typedef int(__fastcall* strcmp_t)(const Unicode*, const Unicode*);
typedef int(__fastcall* strncmp_t)(const Unicode*, const Unicode*, size_t);
typedef Unicode*(__fastcall* strcpy_t)(Unicode*, const Unicode*);
typedef Unicode*(__fastcall* strncpy_t)(Unicode*, const Unicode*, int);
typedef int(__fastcall* strlen_t)(const Unicode*);
typedef Unicode*(__fastcall* to_unicode_t)(Unicode*, const char*, int);
typedef char*(__fastcall* from_unicode_t)(char*, const Unicode*, int);
typedef void(__cdecl* sprintf_t)(int, Unicode*, const Unicode*, ...);
typedef void(__stdcall* crc16_t)(unsigned short*, const unsigned char*, size_t, size_t);
typedef void(__stdcall* group_t)(Unicode*, int, int);
typedef void(__stdcall* ugroup_t)(Unicode*, unsigned, int);

static void test_audit_char() {
    auto o_isASCII = ord<m_bool_t>(10024), o_isAlpha = ord<m_bool_t>(10025), o_isNewline = ord<m_bool_t>(10028), o_isPipe = ord<m_bool_t>(10029), o_isWhitespace = ord<m_bool_t>(10030);
    auto o_dir = ord<m_int_t>(10023);
    auto o_toLower = ord<m_ret_unicode_t>(10050), o_toUpper = ord<m_ret_unicode_t>(10052);
    auto o_mcompare = ord<m_compare_t>(10021); auto o_scompare = ord<s_compare_t>(10022);
    for (unsigned c = 0; c < 0x10000; ++c) {
        Unicode u(c);
        EXPECT_EQ(!!u.isASCII(), !!o_isASCII(&u), "isASCII %X", c);
        if (c < 0x100) EXPECT_EQ(!!u.isAlpha(), !!o_isAlpha(&u), "isAlpha %X", c); // CRT isalpha is undefined above 0xFF
        EXPECT_EQ(!!u.isNewline(), !!o_isNewline(&u), "isNewline %X", c);
        EXPECT_EQ(!!u.isPipe(), !!o_isPipe(&u), "isPipe %X", c);
        EXPECT_EQ(!!u.isWhitespace(), !!o_isWhitespace(&u), "isWhitespace %X", c);
        EXPECT_EQ((int)u.directionality(), o_dir(&u), "directionality %X", c);
        Unicode r; o_toLower(&u, &r); EXPECT_EQ(u.toLower().ch, r.ch, "toLower %X", c);
        o_toUpper(&u, &r); EXPECT_EQ(u.toUpper().ch, r.ch, "toUpper %X", c);
        unsigned d = kAlphabet[rnd() % (sizeof(kAlphabet) / 2)];
        EXPECT_EQ(!!u.compare(Unicode(d)), !!o_mcompare(&u, d), "compare %X %X", c, d);
        EXPECT_EQ(!!Unicode::compare(u, Unicode(d)), !!o_scompare(c, d), "static compare %X %X", c, d);
    }
}

static void test_audit_str() {
    auto o_isLineBreak = ord<str_size_bool_t>(10027), o_isWordEnd = ord<str_size_bool_t>(10031);
    auto o_strchr = ord<strchr_t>(10035);
    auto o_strcmp = ord<strcmp_t>(10036), o_stricmp = ord<strcmp_t>(10039);
    auto o_strncmp = ord<strncmp_t>(10042), o_strnicmp = ord<strncmp_t>(10045);
    auto o_strcat = ord<strcpy_t>(10034), o_strcpy = ord<strcpy_t>(10038);
    auto o_strncat = ord<strncpy_t>(10041), o_strncpy = ord<strncpy_t>(10044);
    auto o_strlen = ord<strlen_t>(10040);
    auto o_strstr = ord<strstri_t>(10046);
    static const unsigned short ascii_alpha[] = { 'a','b','A','1',' ','\n','|','.',',','-' };
    for (int i = 0; i < 20000; ++i) {
        auto a = rstr(6), b = rstr(6);
        if (rnd() % 3 == 0) { b = a; if (b.size() > 1 && rnd() % 2) b[rnd() % (b.size() - 1)] = Unicode(kAlphabet[rnd() % 8]); }
        std::string da = dump(a.data()), db = dump(b.data());
        size_t n = rnd() % 8;
        EXPECT_EQ(Unicode::strcmp(a.data(), b.data()), o_strcmp(a.data(), b.data()), "strcmp '%s' '%s'", da.c_str(), db.c_str());
        EXPECT_EQ(Unicode::stricmp(a.data(), b.data()), o_stricmp(a.data(), b.data()), "stricmp '%s' '%s'", da.c_str(), db.c_str());
        EXPECT_EQ(Unicode::strncmp(a.data(), b.data(), n), o_strncmp(a.data(), b.data(), n), "strncmp '%s' '%s' %d", da.c_str(), db.c_str(), (int)n);
        EXPECT_EQ(Unicode::strnicmp(a.data(), b.data(), n), o_strnicmp(a.data(), b.data(), n), "strnicmp '%s' '%s' %d", da.c_str(), db.c_str(), (int)n);
        EXPECT_EQ(Unicode::strlen(a.data()), o_strlen(a.data()), "strlen '%s'", da.c_str());
        unsigned ch = rnd() % 4 ? kAlphabet[rnd() % 10] : 0;
        EXPECT_EQ(Unicode::strchr(a.data(), Unicode(ch)), o_strchr(a.data(), 0, ch), "strchr '%s' %X", da.c_str(), ch);
        static const unsigned short small[] = { 'a','b','A' };
        auto h = rstr(10, small, 3), nd = rstr(3, small, 3);
        EXPECT_EQ(Unicode::strstr(h.data(), nd.data()), o_strstr(h.data(), nd.data()), "strstr '%s' '%s'", dump(h.data()).c_str(), dump(nd.data()).c_str());
        // Copies
        { Buf<Unicode> buf(32); Unicode::strcpy(buf.moo.data(), a.data()); o_strcpy(buf.orig.data(), a.data()); EXPECT_EQ(buf.same(), true, "strcpy '%s'", da.c_str()); }
        { Buf<Unicode> buf(32); int c = (int)(rnd() % 10); Unicode::strncpy(buf.moo.data(), a.data(), c); o_strncpy(buf.orig.data(), a.data(), c); EXPECT_EQ(buf.same(), true, "strncpy '%s' %d", da.c_str(), c); }
        { Buf<Unicode> buf(32); Unicode::strcpy(buf.moo.data(), b.data()); Unicode::strcpy(buf.orig.data(), b.data()); Unicode::strcat(buf.moo.data(), a.data()); o_strcat(buf.orig.data(), a.data()); EXPECT_EQ(buf.same(), true, "strcat '%s'", da.c_str()); }
        { Buf<Unicode> buf(32); int c = (int)(rnd() % 10) - 1; Unicode::strcpy(buf.moo.data(), b.data()); Unicode::strcpy(buf.orig.data(), b.data()); Unicode::strncat(buf.moo.data(), a.data(), c); o_strncat(buf.orig.data(), a.data(), c); EXPECT_EQ(buf.same(), true, "strncat '%s' %d", da.c_str(), c); }
        // Classification on ASCII strings (the CRT classification functions are undefined above 0xFF)
        auto w = rstr(8, ascii_alpha, 10); size_t idx = w.size() > 1 ? rnd() % (w.size() - 1) : 0;
        EXPECT_EQ(!!Unicode::isWordEnd(w.data(), idx), !!o_isWordEnd(w.data(), idx), "isWordEnd '%s' %d", dump(w.data()).c_str(), (int)idx);
        EXPECT_EQ(!!Unicode::isLineBreak(w.data(), idx), !!o_isLineBreak(w.data(), idx), "isLineBreak '%s' %d", dump(w.data()).c_str(), (int)idx);
    }
}

static void test_audit_conv() {
    auto o_toUnicode = ord<to_unicode_t>(10051), o_utf8ToUnicode = ord<to_unicode_t>(10059), o_win2Unicode = ord<to_unicode_t>(10062);
    auto o_toUtf = ord<from_unicode_t>(10053), o_unicode2Win = ord<from_unicode_t>(10055);
    for (int i = 0; i < 20000; ++i) {
        std::string s = rnd() % 2 ? ascii(12) : bytes(12);
        int c = (int)(rnd() % 16);
        { Buf<Unicode> buf(32); Unicode::toUnicode(buf.moo.data(), s.c_str(), c); o_toUnicode(buf.orig.data(), s.c_str(), c); EXPECT_EQ(buf.same(), true, "toUnicode '%s' %d\n  moo =%s\n  orig=%s", hexbytes(s).c_str(), c, hexdump(buf.moo.data(), 14).c_str(), hexdump(buf.orig.data(), 14).c_str()); }
        if (c > 0) { Buf<Unicode> buf(32); Unicode::win2Unicode(buf.moo.data(), s.c_str(), c); o_win2Unicode(buf.orig.data(), s.c_str(), c); EXPECT_EQ(buf.same(), true, "win2Unicode len=%d %d", (int)s.size(), c); }
        if (c > 0) { Buf<Unicode> buf(32); Unicode::utf8ToUnicode(buf.moo.data(), s.c_str(), c); o_utf8ToUnicode(buf.orig.data(), s.c_str(), c); EXPECT_EQ(buf.same(), true, "utf8ToUnicode len=%d %d", (int)s.size(), c); }
        auto u = rstr(8);
        { Buf<char> buf(64); Unicode::toUtf(buf.moo.data(), u.data(), c); o_toUtf(buf.orig.data(), u.data(), c); EXPECT_EQ(buf.same(), true, "toUtf '%s' %d", dump(u.data()).c_str(), c); }
        { Buf<char> buf(64); Unicode::unicode2Win(buf.moo.data(), u.data(), c); o_unicode2Win(buf.orig.data(), u.data(), c); EXPECT_EQ(buf.same(), true, "unicode2Win '%s' %d", dump(u.data()).c_str(), c); }
    }
}

static void test_audit_misc() {
    auto o_sprintf = ord<sprintf_t>(10033);
    auto o_crc = ord<crc16_t>(10005);
    auto o_gi = ord<group_t>(10009); auto o_gu = ord<ugroup_t>(10010);
    static const wchar_t* fmts[] = { L"", L"abc", L"%d", L"%u", L"%s", L"%%", L"a%db%uc%sd", L"%s%s", L"%", L"x%", L"%d%%%d", L"value: %d!" };
    const Unicode* sarg = D2_USTR(L"str"); const Unicode* earg = D2_USTR(L"");
    for (int i = 0; i < 20000; ++i) {
        const wchar_t* fw = fmts[rnd() % 12]; const Unicode* f = D2_USTR(fw);
        int size = 1 + rnd() % 24; int v1 = (int)rnd() - 0x400000; unsigned v2 = rnd(); const Unicode* s1 = rnd() % 4 ? sarg : earg;
        // The original appends empty/overflowing %s arguments to whatever string starts at the current position, which is
        // only defined if the buffer is zeroed: only compare with garbage-filled buffers when that can not happen.
        bool zeroFill = rnd() % 2;
        Buf<Unicode> buf(32);
        if (zeroFill) { std::fill(buf.moo.begin(), buf.moo.end(), Unicode(0)); std::fill(buf.orig.begin(), buf.orig.end(), Unicode(0)); }
        else if (wcsstr(fw, L"%s") && (s1 == earg || size < 24)) continue;
        // %s args are passed where %s is expected, other positions get ints.
        if (wcscmp(fw, L"%s") == 0 || wcscmp(fw, L"%s%s") == 0) { Unicode::sprintf(size, buf.moo.data(), f, s1, sarg); o_sprintf(size, buf.orig.data(), f, s1, sarg); }
        else { Unicode::sprintf(size, buf.moo.data(), f, v1, v2, s1, sarg); o_sprintf(size, buf.orig.data(), f, v1, v2, s1, sarg); }
        EXPECT_EQ(buf.same(), true, "sprintf '%ls' size=%d s1='%ls' zero=%d\n  moo =%s\n  orig=%s", fw, size, (const wchar_t*)s1, zeroFill, hexdump(buf.moo.data(), 26).c_str(), hexdump(buf.orig.data(), 26).c_str());
    }
    for (int i = 0; i < 2000; ++i) {
        unsigned char data[64]; for (auto& d : data) d = (unsigned char)rnd();
        size_t s = rnd() % 32, e = s + 1 + rnd() % 32;
        unsigned short a = 0, b = 0; CRC16_CalculateChecksum(&a, data, s, e); o_crc(&b, data, s, e);
        EXPECT_EQ(a, b, "crc16 %d %d", (int)s, (int)e);
    }
    for (int i = 0; i < 20000; ++i) {
        int v = (int)rnd() * (rnd() % 2 ? 1 : -1) >> (rnd() % 31); int len = 3 + rnd() % 14;
        if (v == INT_MIN) continue;
        { Buf<Unicode> buf(32); STR_GroupIntDigits(buf.moo.data(), v, len); o_gi(buf.orig.data(), v, len); EXPECT_EQ(buf.same(), true, "STR_GroupIntDigits %d %d", v, len); }
        { Buf<Unicode> buf(32); STR_GroupUintDigits(buf.moo.data(), (unsigned)v, len); o_gu(buf.orig.data(), (unsigned)v, len); EXPECT_EQ(buf.same(), true, "STR_GroupUintDigits %u %d", (unsigned)v, len); }
    }
}

typedef unsigned(__fastcall* width_u_t)(const Unicode*, int);
typedef unsigned(__fastcall* width_c_t)(const char*, int);
typedef BOOL(__fastcall* loadsysmap_t)(void*, const char*);
typedef void(__fastcall* unloadsysmap_t)();

static void compare_sys_functions(const char* label) {
    auto o_sysWidth = ord<width_u_t>(10049); auto o_unicodeWidth = ord<width_c_t>(10056);
    auto o_sys2Unicode = ord<to_unicode_t>(10048); auto o_unicode2Sys = ord<from_unicode_t>(10054);
    static const unsigned short alpha[] = { 'a','b','@',0x9A,0xE9,0xA5,0x3041,0x30E9,0x80,0x1F,'\n',0xFF,0x4E00,0x100 };
    for (int i = 0; i < 20000; ++i) {
        auto u = rstr(10, alpha, sizeof(alpha) / 2); int c = (int)(rnd() % 14);
        EXPECT_EQ(Unicode::sysWidth(u.data(), c), o_sysWidth(u.data(), c), "%s sysWidth '%s' %d", label, dump(u.data()).c_str(), c);
        { Buf<char> buf(64); Unicode::unicode2Sys(buf.moo.data(), u.data(), c); o_unicode2Sys(buf.orig.data(), u.data(), c); EXPECT_EQ(buf.same(), true, "%s unicode2Sys '%s' %d", label, dump(u.data()).c_str(), c); }
        std::string b = rnd() % 2 ? ascii(12) : bytes(12);
        EXPECT_EQ(Unicode::unicodeWidth(b.c_str(), c), o_unicodeWidth(b.c_str(), c), "%s unicodeWidth len=%d %d", label, (int)b.size(), c);
        if (c > 0) { Buf<Unicode> buf(32); Unicode::sys2Unicode(buf.moo.data(), b.c_str(), c); o_sys2Unicode(buf.orig.data(), b.c_str(), c); EXPECT_EQ(buf.same(), true, "%s sys2Unicode len=%d %d", label, (int)b.size(), c); }
    }
}

static void test_widths() {
    auto o_utfnwidth = ord<width_u_t>(10060); auto o_unicodenwidth = ord<width_c_t>(10057);
    auto o_utfwidth = ord<m_int_t>(10061);
    for (unsigned c = 0; c < 0x10000; ++c) { Unicode u(c); EXPECT_EQ(u.utfwidth(), o_utfwidth(&u), "utfwidth %X", c); }
    for (int i = 0; i < 20000; ++i) {
        auto u = rstr(10); int c = (int)(rnd() % 14) - 1;
        EXPECT_EQ(Unicode::utfnwidth(u.data(), c), o_utfnwidth(u.data(), c), "utfnwidth '%s' %d", dump(u.data()).c_str(), c);
        std::string b = rnd() % 2 ? ascii(12) : bytes(12);
        if (rnd() % 4 == 0) { b = "\xF0\x90\x80\x80" "a\xE3\x81\x82" "\xC3\xA9"; }
        EXPECT_EQ(Unicode::unicodenwidth(b.c_str(), c), o_unicodenwidth(b.c_str(), c), "unicodenwidth len=%d %d", (int)b.size(), c);
    }
}

static void test_sysmap() {
    auto o_load = ord<loadsysmap_t>(10032); auto o_unload = ord<unloadsysmap_t>(10058);
    compare_sys_functions("nomap");
    EXPECT_EQ(Unicode::loadSysMap(nullptr, "bad.map"), o_load(nullptr, "bad.map"), "loadSysMap bad");
    compare_sys_functions("badmap");
    EXPECT_EQ(Unicode::loadSysMap(nullptr, "test.map"), o_load(nullptr, "test.map"), "loadSysMap");
    {
        Unicode u[8]; Unicode::sys2Unicode(u, "abc\xE0", 8);
        char c[8] = {}; Unicode::unicode2Sys(c, u, 8);
        printf("  map loaded: sys2Unicode(\"abc\\xE0\") = %s, back = %02X %02X %02X %02X %02X, sysWidth=%lu\n", dump(u).c_str(), (unsigned char)c[0], (unsigned char)c[1], (unsigned char)c[2], (unsigned char)c[3], (unsigned char)c[4], Unicode::sysWidth(u, 8));
    }
    compare_sys_functions("map");
    Unicode::unloadSysMap(); o_unload();
    compare_sys_functions("unloaded");
}

typedef void(__fastcall* personalize_t)(Unicode*, const Unicode*, const Unicode*, int, ELANGUAGE);
static void test_personalize() {
    auto o_personalize = ord<personalize_t>(10018);
    static const unsigned short alpha[] = { 'a','e','s','z','S','Z','A','o','u','x',' ' };
    for (int i = 0; i < 30000; ++i) {
        auto name = rstr(8, alpha, sizeof(alpha) / 2), text = rstr(8, alpha, sizeof(alpha) / 2);
        if (name.size() == 1) continue; // empty name reads before the string in English/German
        int maxLen = rnd() % 24; int lang = rnd() % 15;
        Buf<Unicode> buf(40);
        Unicode::Personalize(buf.moo.data(), name.data(), text.data(), maxLen, (ELANGUAGE)lang);
        o_personalize(buf.orig.data(), name.data(), text.data(), maxLen, (ELANGUAGE)lang);
        EXPECT_EQ(buf.same(), true, "Personalize '%s' '%s' %d lang=%d moo='%s' orig='%s'", dump(name.data()).c_str(), dump(text.data()).c_str(), maxLen, lang, dump(buf.moo.data()).c_str(), dump(buf.orig.data()).c_str());
    }
}

typedef void(__stdcall* langcode_t)(char*, int);
typedef D2C_Language(__cdecl* getlang_t)();
typedef void(__stdcall* group64_t)(Unicode*, int64_t, int);
typedef void(__stdcall* ugroup64_t)(Unicode*, uint64_t, int);
static void test_locale() {
    // Must run first in the process: the language is cached by both implementations
    const char* langEnv = getenv("TEST_LANGUAGE"); int lang = langEnv ? atoi(langEnv) : 0;
    { FILE* f = fopen("data\\local\\use", "wb"); fputc(lang, f); fclose(f); }
    auto o_getlang = ord<getlang_t>(10007), o_syslang = ord<getlang_t>(10008);
    auto o_code = ord<langcode_t>(10006);
    EXPECT_EQ(STRTABLE_GetLanguage(), o_getlang(), "GetLanguage %d", lang);
    printf("  language %d -> %d\n", lang, (int)STRTABLE_GetLanguage());
    EXPECT_EQ(STRTABLE_GetSystemLanguage(), o_syslang(), "GetSystemLanguage");
    for (int type = 0; type < 6; ++type) {
        char a[16], b[16]; memset(a, 0x55, 16); memset(b, 0x55, 16);
        STRTABLE_GetLanguageCode(a, (D2C_LanguageCodeType)type); o_code(b, type);
        EXPECT_EQ(memcmp(a, b, 16), 0, "GetLanguageCode lang=%d type=%d '%.4s' '%.4s'", lang, type, a, b);
    }
    auto o_g64 = ord<group64_t>(10011); auto o_ug64 = ord<ugroup64_t>(10012);
    for (int i = 0; i < 30000; ++i) {
        uint64_t r = ((uint64_t)rnd() << 40) ^ ((uint64_t)rnd() << 20) ^ rnd();
        r >>= rnd() % 64;
        int64_t v = (int64_t)r * (rnd() % 2 ? 1 : -1); int len = 3 + rnd() % 30;
        if (v == INT64_MIN) continue;
        { Buf<Unicode> buf(40); STR_GroupInt64Digits(buf.moo.data(), v, len); o_g64(buf.orig.data(), v, len); EXPECT_EQ(buf.same(), true, "STR_GroupInt64Digits %lld %d moo=%s orig=%s", (long long)v, len, dump(buf.moo.data()).c_str(), dump(buf.orig.data()).c_str()); }
        { Buf<Unicode> buf(40); STR_GroupUint64DigitsWithSuffix(buf.moo.data(), r, len); o_ug64(buf.orig.data(), r, len); EXPECT_EQ(buf.same(), true, "STR_GroupUint64DigitsWithSuffix %llu %d moo=%s orig=%s", (unsigned long long)r, len, dump(buf.moo.data()).c_str(), dump(buf.orig.data()).c_str()); }
    }
}

typedef BOOL(__fastcall* loadstrings_t)(void*, const char*, BOOL);
typedef void(__fastcall* freestrings_t)();
typedef uint32_t(__stdcall* hash_t)(const char*, uint32_t);
typedef const Unicode*(__fastcall* getstr_t)(short);
typedef short(__stdcall* gettblindex_t)(char*, const Unicode**);
typedef const Unicode*(__fastcall* getbyref_t)(char*);

static bool same_string(const Unicode* a, const Unicode* b) { if (!a || !b) return a == b; return Unicode::strcmp(a, b) == 0 && Unicode::strlen(a) == Unicode::strlen(b); }

static void test_strtable() {
    const char* expEnv = getenv("TEST_EXPANSION"); BOOL bExpansion = expEnv ? atoi(expEnv) : TRUE;
    auto o_load = ord<loadstrings_t>(10000); auto o_free = ord<freestrings_t>(10001);
    auto o_hash = ord<hash_t>(10002); auto o_getstr = ord<getstr_t>(10004);
    auto o_gettbl = ord<gettblindex_t>(10013); auto o_byref = ord<getbyref_t>(10003);
    auto o_ug64 = ord<ugroup64_t>(10012);

    for (int i = 0; i < 20000; ++i) {
        std::string k = ascii(12); uint32_t size = 1 + rnd() % 10000;
        if (rnd() % 2) k += (char)(0x80 + rnd() % 0x80);
        EXPECT_EQ(D2LANG_GetStringHash(k.c_str(), size), o_hash(k.c_str(), size), "hash '%s' %u", k.c_str(), size);
    }

    EXPECT_EQ(D2LANG_LoadStrings(nullptr, nullptr, bExpansion), o_load(nullptr, nullptr, bExpansion), "LoadStrings");
    EXPECT_EQ(D2LANG_LoadStrings(nullptr, "ENG", bExpansion), o_load(nullptr, "ENG", bExpansion), "LoadStrings again");
    printf("  expansion=%d, string 0 = '%s', 10003 = '%s'\n", bExpansion, dump(D2LANG_GetStringFromTblIndex(0)).c_str(), dump(D2LANG_GetStringFromTblIndex(10003)).c_str());

    for (int id = -2; id < 26000; ++id) {
        if (id >= 0 && id >= 6000 && id < 10000) continue; // out of range ids: trace + fallback to 500, sample a few only
        const Unicode* a = D2LANG_GetStringFromTblIndex((short)id); const Unicode* b = o_getstr((short)id);
        EXPECT_EQ(same_string(a, b), true, "GetStringFromTblIndex %d moo='%s' orig='%s'", id, dump(a).c_str(), dump(b).c_str());
    }
    for (int id : { 6000, 6001, 9999 }) { EXPECT_EQ(same_string(D2LANG_GetStringFromTblIndex(id), o_getstr(id)), true, "GetStringFromTblIndex %d", id); }

    std::vector<std::string> keys;
    { FILE* f = fopen("keys.txt", "rb"); char line[256]; while (fgets(line, sizeof(line), f)) { line[strcspn(line, "\r\n")] = 0; keys.push_back(line); } fclose(f); }
    for (int i = 0; i < 300; ++i) keys.push_back("unknown" + std::to_string(i % 100)); // repeated unknown keys use the cache
    keys.push_back(""); keys.push_back("BASE1"); keys.push_back("Base1");
    for (auto& k : keys) {
        std::vector<char> ka(k.begin(), k.end()), kb(k.begin(), k.end()); ka.push_back(0); kb.push_back(0);
        const Unicode* ua = nullptr; const Unicode* ub = nullptr;
        short ia = D2LANG_GetTblIndex(ka.data(), &ua); short ib = o_gettbl(kb.data(), &ub);
        EXPECT_EQ(ia, ib, "GetTblIndex index '%s'", k.c_str());
        EXPECT_EQ(same_string(ua, ub), true, "GetTblIndex string '%s' moo='%s' orig='%s'", k.c_str(), dump(ua).c_str(), dump(ub).c_str());
        EXPECT_EQ(same_string(D2LANG_GetStringByReferenceString(ka.data()), o_byref(kb.data())), true, "GetStringByReferenceString '%s'", k.c_str());
    }
    // Suffixes read from the string table
    for (uint64_t v : { 999ull, 1234567ull, 1234567890ull, 1234567890123ull, 1234567890123456ull }) {
        Buf<Unicode> buf(40); STR_GroupUint64DigitsWithSuffix(buf.moo.data(), v, 30); o_ug64(buf.orig.data(), v, 30);
        EXPECT_EQ(buf.same(), true, "suffix %llu moo=%s orig=%s", (unsigned long long)v, dump(buf.moo.data()).c_str(), dump(buf.orig.data()).c_str());
    }

    // Reference counting: still loaded after the first free
    D2LANG_FreeStrings(); o_free();
    EXPECT_EQ(same_string(D2LANG_GetStringFromTblIndex(1), o_getstr(1)), true, "after first free");
    D2LANG_FreeStrings(); o_free();
    // Reload after a full free
    EXPECT_EQ(D2LANG_LoadStrings(nullptr, nullptr, bExpansion), o_load(nullptr, nullptr, bExpansion), "LoadStrings reload");
    EXPECT_EQ(same_string(D2LANG_GetStringFromTblIndex(10003), o_getstr(10003)), true, "after reload");
    { char k[] = "unknown1"; const Unicode* ua; const Unicode* ub; D2LANG_GetTblIndex(k, &ua); o_gettbl(k, &ub); EXPECT_EQ(same_string(ua, ub), true, "unknown after reload '%s' '%s'", dump(ua).c_str(), dump(ub).c_str()); }
    D2LANG_FreeStrings(); o_free();
}

int main(int argc, char** argv) {
    if (getenv("SEED")) gSeed = atoi(getenv("SEED"));
    gOrig = LoadLibraryA("D2Lang.dll");
    if (!gOrig) { printf("cannot load D2Lang.dll %lu\n", GetLastError()); return 2; }
    std::vector<std::pair<const char*, void(*)()>> tests = {
        { "locale", test_locale },
        { "collation", test_collation },
        { "audit_char", test_audit_char },
        { "audit_str", test_audit_str },
        { "audit_conv", test_audit_conv },
        { "audit_misc", test_audit_misc },
        { "widths", test_widths },
        { "sysmap", test_sysmap },
        { "personalize", test_personalize },
        { "strtable", test_strtable },
    };
    for (auto& t : tests) {
        if (argc > 1 && strcmp(argv[1], t.first)) continue;
        int before = gFail; t.second(); printf("%-12s %s\n", t.first, gFail == before ? "OK" : "FAILED");
    }
    printf("%d checks, %d failures\n", gChecks, gFail);
    return gFail ? 1 : 0;
}
