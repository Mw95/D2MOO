/**
 * D2MOO
 * Copyright (c) 2020-2022  The Phrozen Keep community
 *
 * This file belongs to D2MOO.
 * File authors: Mir Drualga
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <wchar.h>

#include <D2BasicTypes.h>

#include "D2Lang.h"

struct HD2ARCHIVE__;

/*
 * Language type used by the original exports. It has the same values as
 * D2C_Language, but must be a distinct type to get the same mangled
 * names as the original D2Lang.
 */
enum ELANGUAGE : int {};

/*
* This type must be struct in order to make certain functions'
* mangled names the same as the ones in D2Lang.
*/
struct D2LANG_DLL_DECL Unicode {
 public:
  enum Direction {
    DIR_LEFT_TO_RIGHT = 0xF0,
    DIR_RIGHT_TO_LEFT = 0xF1,
    DIR_NEUTRAL = 0xF2,
  };

  unsigned short ch;

  /**
   * Default parameter value generates the default constructor
   * closure, but also requires dllexport to generate.
   *
   * D2Lang.0x6FC11200 (#10017) ??_FUnicode@@QAEXXZ
   */

  // D2Lang.0x6FC11010 (#10014) ??0Unicode@@QAE@G@Z
  Unicode(unsigned short ch = 0);

  // D2Lang.0x6FC111F0 (#10015) ??4Unicode@@QAEAAU0@ABU0@@Z
  Unicode& operator=(const Unicode& str);

  // D2Lang.0x6FC11020 (#10016) ??BUnicode@@QBEGXZ
  operator unsigned short() const;

  /**
   * Performs case insensitive comparison between a Unicode code
   * unit to another.
   *
   * D2Lang.0x6FC11150 (#10022) ?compare@Unicode@@SIHU1@0@Z
   */
  static BOOL __fastcall compare(Unicode lhs, Unicode rhs);

  /**
   * Returns whether the specified character in the string is the last
   * character of a word. In this function, only characters in the
   * English alphabet or Arabic numerals are considered characters in
   * a word. The first character is also not considered the end of a
   * word.
   *
   * D2Lang.0x6FC11190 (#10031) ?isWordEnd@Unicode@@SIHPBU1@I@Z
   */
  static BOOL __fastcall isWordEnd(const Unicode* str, size_t index);

  /**
   * Performs string conversions on the supplied parameters, similar
   * to standard C's printf.
   *
   * Only the conversion specifiers %%, %d, %u, and %s are supported.
   * %s represents a pointer to a null-terminated Unicode string. To
   * specify an unsupported conversion specifier will result in an
   * assertion error. Flags, minimum field width, precision, and
   * length modifiers are not supported.
   *
   * Vanilla quirk: %% consumes an argument, like the other conversion
   * specifiers.
   *
   * D2Lang.0x6FC11670 (#10033) ?sprintf@Unicode@@SAXHPAU1@PBU1@ZZ
   */
  static void __cdecl sprintf(
      int buffer_size,
      Unicode* buffer,
      const Unicode* format,
      ...);

  /**
   * Appends a null-terminated string to the end of a null-terminated
   * destination string. Returns the destination string.
   *
   * D2Lang.0x6FC113F0 (#10034) ?strcat@Unicode@@SIPAU1@PAU1@PBU1@@Z
   */
  static Unicode* __fastcall strcat(Unicode* dest, const Unicode* src);

  /**
   * Writes into dest a string combining a (player) name and a text,
   * such as "Name's text" in English, according to the grammar of the
   * given language (a D2C_Language value):
   * - English: "Name's text", or "Names' text" if the name ends with 's'
   * - Spanish: "text de Name"
   * - German: "Names text", or "Name' text" if the name ends with 's' or 'z'
   * - French: "text de Name", or "text d'Name" if the name starts with a
   *   lowercase vowel
   * - Italian: "text di Name"
   * - Polish: "text(Name) "
   * - Other languages: "(Name) text"
   *
   * If the result could be longer than maxLength (that is, if the name
   * and text lengths plus 5 exceed it), dest is set to text if text is
   * shorter than maxLength, and left untouched otherwise.
   *
   * Vanilla bug: In English and German, the character before name is
   * read if name is empty.
   *
   * 1.10: D2Lang.0x6FC11D50 (#10018) ?Personalize@Unicode@@SIXPAU1@PBU1@1HW4ELANGUAGE@@@Z
   */
  static void __fastcall Personalize(
      Unicode* dest,
      const Unicode* name,
      const Unicode* text,
      int maxLength,
      ELANGUAGE language);

  /**
   * Returns the first occurrence of a character in a null-terminated
   * string.
   *
   * If the character could not be found, or the character to find is
   * the null-terminating character, then the function returns NULL.
   *
   * D2Lang.0x6FC113C0 (#10035) ?strchr@Unicode@@SIPAU1@PBU1@U1@@Z
   */
  static Unicode* __fastcall strchr(const Unicode* str, Unicode ch);

  /**
   * Compares two null-terminated strings lexicographically. Returns
   * -1, 0, or 1, depending on the results of the comparison.
   *
   * D2Lang.0x6FC11210 (#10036) ?strcmp@Unicode@@SIHPBU1@0@Z
   */
  static int __fastcall strcmp(const Unicode* str1, const Unicode* str2);

  /**
   * Copies the characters from a null-terminated source string into a
   * null-terminated destination string. Returns the destination
   * string.
   *
   * D2Lang.0x6FC114A0 (#10038) ?strcpy@Unicode@@SIPAU1@PAU1@PBU1@@Z
   */
  static Unicode* __fastcall strcpy(Unicode* dest, const Unicode* src);

  /**
   * Performs lexicographical, case-insensitive comparison between two
   * null-terminated strings. Returns -1, 0, or 1, depending on the
   * results of the comparison.
   *
   * If either string is the NULL pointer, then the behavior is
   * undefined.
   *
   * D2Lang.0x6FC112A0 (#10039) ?stricmp@Unicode@@SIHPBU1@0@Z
   */
  static int __fastcall stricmp(const Unicode* str1, const Unicode* str2);

  /**
   * Performs lexicographical, case-insensitive comparison between two
   * null-terminated strings, up to count characters. Returns -1, 0,
   * or 1, depending on the results of the comparison.
   *
   * If either string is the NULL pointer, then the behavior is
   * undefined.
   *
   * Vanilla bug: If one string is a prefix of the other string, then
   * 0 is returned. If count is 0, the first characters are still
   * compared.
   *
   * D2Lang.0x6FC11310 (#10045) ?strnicmp@Unicode@@SIHPBU1@0I@Z
   */
  static int __fastcall strnicmp(const Unicode* str1, const Unicode* str2, size_t count);

  /**
   * Compares two null-terminated strings using the D2Lang collation
   * order, for at most count characters. Characters below 0x100 are
   * compared by their collation weight (letters with diacritics sort
   * next to their base letter, case is ignored); other characters are
   * compared by their code unit. Returns a negative value, zero or a
   * positive value. If both strings collate equally, the result of
   * strnicmp is returned as a tie breaker.
   *
   * 1.10: D2Lang.0x6FC122B0 (#10043) ?strncoll@Unicode@@SIHPBU1@0H@Z
   */
  static int __fastcall strncoll(const Unicode* str1, const Unicode* str2, int count);

  /**
   * Same as strncoll, without a character limit.
   *
   * 1.10: D2Lang.0x6FC111E0 (#10037) ?strcoll@Unicode@@SIHPBU1@0@Z
   */
  static int __fastcall strcoll(const Unicode* str1, const Unicode* str2);

  /**
   * Case-insensitive version of strstr. Returns NULL if either string
   * is NULL or if the substring could not be found.
   *
   * Vanilla bug: If str is empty but substr is not, the character
   * after the null terminator of str is read.
   *
   * 1.10: D2Lang.0x6FC114E0 (#10047) ?strstri@Unicode@@SIPAU1@PBU1@0@Z
   */
  static Unicode* __fastcall strstri(const Unicode* str, const Unicode* substr);

  /**
   * Returns the length of the null-terminated string. If the string
   * pointer is NULL, the function returns 0;
   *
   * D2Lang.0x6FC114C0 (#10040) ?strlen@Unicode@@SIHPBU1@@Z
   */
  static int __fastcall strlen(const Unicode* str);

  /**
   * Appends a null-terminated string to the end of a destination
   * null-terminated string. The maximum number of characters appended
   * is specified as the count. The destination string will always
   * append a terminating null character, so that (count + 1)
   * characters can be written.
   *
   * D2Lang.0x6FC11420 (#10041) ?strncat@Unicode@@SIPAU1@PAU1@PBU1@H@Z
   */
  static Unicode* __fastcall strncat(
      Unicode* dest,
      const Unicode* src,
      int count);

  /*
   * Compares two null-terminated strings or substrings
   * lexicographically. Returns -1, 0, or 1, depending on the results
   * of the comparison.
   *
   * If either string is the NULL pointer, then the behavior is
   * undefined.
   *
   * Vanilla bug: If one string is a prefix of another, then the
   * function will always return 0, even when the specified count is
   * greater than the length of the prefix.
   *
   * D2Lang.0x6FC11250 (#10042) ?strncmp@Unicode@@SIHPBU1@0I@Z
   */
  static int __fastcall strncmp(
      const Unicode* str1,
      const Unicode* str2,
      size_t count);

  /**
   * Copies up to a specified count of characters from a
   * null-terminated source string into a null-terminated destination
   * string. If the count is greater than the length of the source
   * string, then the remaining characters are filled with the null
   * terminator character. Returns the destination string.
   *
   * 1.00: D2Lang.0x1000114A (#10042)
   * 1.10: D2Lang.0x6FC11460 (#10044)
   * 1.11: D2Lang.0x6FC0A900 (#10044)
   * 1.13c: D2Lang.0x6FC0B0D0 (#10044)
   * ?strncpy@Unicode@@SIPAU1@PAU1@PBU1@H@Z
   */
  static Unicode* __fastcall strncpy(
      Unicode* dest, const Unicode* src, int count);

  /**
   * Returns the first occurrence of a null-terminated substring in a
   * null-terminated string. If the substring is empty, or the
   * string does not contain the substring, then the function returns
   * NULL.
   *
   * D2Lang.0x6FC0B020 (#10046) ?strstr@Unicode@@SIPAU1@PBU1@0@Z
   */
  static Unicode* __fastcall strstr(
      const Unicode* str,
      const Unicode* substr);

  /**
   * Converts a null-terminated UTF-8 string into a null-terminated
   * UCS-2 string. The count indicates the capacity of the destination
   * in terms of UCS-2 characters. Returns the pointer to the
   * destination string.
   *
   * Vanilla bug: Specifying INT_MIN for the count results in
   * undefined behavior. Do not specify INT_MIN as the count.
   *
   * D2Lang.0x6FC12A40 (#10051) ?toUnicode@Unicode@@SIPAU1@PAU1@PBDH@Z
   */
  static Unicode* __fastcall toUnicode(
      Unicode* dest,
      const char* src,
      int count);

  /**
   * Converts a null-terminated UCS-2 string into a null-terminated
   * 7-bit ASCII string. The count indicates the capacity of the
   * destination in terms of UCS-2 characters. Returns the pointer to
   * the destination string.
   *
   * 1.00: D2Lang.0x1000109B (#10053)
   * 1.10: D2Lang.0x6FC11C20 (#10055)
   * ?unicode2Win@Unicode@@SIPADPADPBU1@H@Z
   */
  static char* __fastcall unicode2Win(
      char* dest, const Unicode* src, int count);

  /**
   * Converts a null-terminated UCS-2 string into a null-terminated
   * UTF-8 string. The count indicates the capacity of the destination
   * in terms of UTF-8 code units. Returns the pointer to the
   * destination string.
   *
   * Vanilla bug: Specifying INT_MIN for the count results in
   * undefined behavior. Do not specify INT_MIN as the count.
   *
   * Vanilla bug: Count is insufficient for preventing buffer overrun
   * for code points that require three UTF-8 code units. To work
   * around this, specify a lower count value.
   *
   * D2Lang.0x6FC12B60 (#10053) ?toUtf@Unicode@@SIPADPADPBU1@H@Z
   */
  static char* __fastcall toUtf(char* dest, const Unicode* src, int count);
  
  /**
   * Returns the number of UTF-8 code units needed to encode up to
   * count characters of the null-terminated string.
   *
   * 1.10: D2Lang.0x6FC12C30 (#10060) ?utfnwidth@Unicode@@SIIPBU1@H@Z
   */
  static unsigned int __fastcall utfnwidth(const Unicode* str, int count);

  /**
   * Returns the number of characters encoded in the first count bytes
   * of the null-terminated UTF-8 string. Invalid sequences are
   * skipped one byte at a time and are not counted.
   *
   * 1.10: D2Lang.0x6FC12CD0 (#10057) ?unicodenwidth@Unicode@@SIIPBDH@Z
   */
  static unsigned int __fastcall unicodenwidth(const char* str, int count);

  /**
   * Loads the mapping between the system code page and Unicode (a
   * "KAMAP" file, for example data\local\font\JPN\default.map), used
   * by sys2Unicode, unicode2Sys, sysWidth and unicodeWidth. Returns
   * FALSE if the file is not a valid map.
   *
   * 1.10: D2Lang.0x6FC123E0 (#10032) ?loadSysMap@Unicode@@SIHPAUHD2ARCHIVE__@@PBD@Z
   */
  static BOOL __fastcall loadSysMap(HD2ARCHIVE__* hArchive, const char* szFileName);

  /**
   * Frees the system code page map loaded by loadSysMap.
   *
   * 1.10: D2Lang.0x6FC12370 (#10058) ?unloadSysMap@Unicode@@SIXXZ
   */
  static void __fastcall unloadSysMap();

  /**
   * Converts a null-terminated string in the system code page into a
   * UCS-2 string of at most count characters, using the map loaded by
   * loadSysMap. Characters missing from the map are skipped. Falls
   * back to win2Unicode if no map is loaded.
   *
   * Vanilla bug: No null terminator is written if count characters
   * have been converted. A lead byte right before the null terminator
   * consumes the terminator, and reading continues past it.
   *
   * 1.10: D2Lang.0x6FC12650 (#10048) ?sys2Unicode@Unicode@@SIPAU1@PAU1@PBDH@Z
   */
  static Unicode* __fastcall sys2Unicode(Unicode* dest, const char* src, int count);

  /**
   * Converts a null-terminated UCS-2 string into the system code page,
   * using the map loaded by loadSysMap. Characters missing from the
   * map are skipped. Falls back to unicode2Win if no map is loaded.
   *
   * Vanilla bug: Double-byte characters can write one byte past
   * count, and no null terminator is written if count bytes have been
   * written.
   *
   * 1.10: D2Lang.0x6FC127C0 (#10054) ?unicode2Sys@Unicode@@SIPADPADPBU1@H@Z
   */
  static char* __fastcall unicode2Sys(char* dest, const Unicode* src, int count);

  /**
   * Returns the number of bytes needed to store up to count characters
   * of the string in the system code page. Returns the length of the
   * string if no map is loaded.
   *
   * 1.10: D2Lang.0x6FC128D0 (#10049) ?sysWidth@Unicode@@SIKPBU1@H@Z
   */
  static unsigned long __fastcall sysWidth(const Unicode* str, int count);

  /**
   * Returns the number of characters in the first count bytes of a
   * string in the system code page. Returns the length of the string
   * if no map is loaded.
   *
   * 1.10: D2Lang.0x6FC129B0 (#10056) ?unicodeWidth@Unicode@@SIKPBDH@Z
   */
  static unsigned long __fastcall unicodeWidth(const char* str, int count);

  //1.10f: D2Lang.0x6FC11B30 (#10059) ?utf8ToUnicode@Unicode@@SIPAU1@PAU1@PBDH@Z
  static Unicode* __fastcall utf8ToUnicode(Unicode* dest, char const* src, int count);

  /**
   * Converts a null-terminated 7-bit ASCII string into a
   * null-terminated UCS-2 string. The count indicates the capacity of
   * the destination in terms of UCS-2 characters. Returns the pointer
   * to the destination string.
   *
   * 1.00: D2Lang.0x10001122 (#10059)
   * 1.10: D2Lang.0x6FC11BD0 (#10062)
   * ?win2Unicode@Unicode@@SIPAU1@PAU1@PBDH@Z
   */
  static Unicode* __fastcall win2Unicode(
      Unicode* dest, const char* src, int count);

  /**
   * Performs case insensitive comparison between this Unicode code
   * unit to another.
   *
   * D2Lang.0x6FC11110 (#10021) ?compare@Unicode@@QBEHU1@@Z
   */
  BOOL compare(Unicode ch) const;

  // D2Lang.0x6FC11C50 (#10023) ?directionality@Unicode@@QAE?AW4Direction@1@XZ
  Direction directionality();

  /**
   * Returns whether or not this Unicode character is in 
   * "C0 Controls and Basic Latin" character block, otherwise known as
   * the ASCII character block.
   *
   * D2Lang.0x6FC11080 (#10024) ?isASCII@Unicode@@QBEHXZ
   */
  BOOL isASCII() const;

  /**
   * Returns whether or not this Unicode character is an alphabetic
   * character.
   *
   * D2Lang.0x6FC11090 (#10025) ?isAlpha@Unicode@@QBEHXZ
   */
  BOOL isAlpha() const;

  /**
   * Returns FALSE if this character is in the Hebrew (0x590-0x5FF) or
   * Arabic (0x600-0x6FF) blocks, TRUE otherwise.
   *
   * 1.10: D2Lang.0x6FC11A00 (#10026) ?isLeftToRight@Unicode@@QBEHXZ
   */
  BOOL isLeftToRight() const;

  // D2Lang.0x6FC11A30 (#10027) ?isLineBreak@Unicode@@SIHPBU1@I@Z
  static BOOL __fastcall isLineBreak(const Unicode* str, size_t count);

  // D2Lang.0x6FC11050 (#10028) ?isNewline@Unicode@@QBEHXZ
  BOOL isNewline() const;

  // D2Lang.0x6FC11060 (#10029) ?isPipe@Unicode@@QBEHXZ
  BOOL isPipe() const;

  // D2Lang.0x6FC11030 (#10030) ?isWhitespace@Unicode@@QBEHXZ
  BOOL isWhitespace() const;

  /**
   * Returns this character's lowercase if there is a lowercase for
   * this character. Otherwise, returns a copy of this character.
   *
   * Vanilla bug: Returns uppercase for characters in the
   * "Latin-1 Supplement" block.
   *
   * D2Lang.0x6FC110E0 (#10050) ?toLower@Unicode@@QBE?AU1@XZ
   */
  Unicode toLower() const;

  /**
   * Returns this character's uppercase if there is an uppercase for
   * this character. Otherwise, returns a copy of this character.
   *
   * D2Lang.0x6FC110B0 (#10052) ?toUpper@Unicode@@QBE?AU1@XZ
   */
  Unicode toUpper() const;

  /**
   * Returns the number of UTF-8 code units needed to encode this
   * character.
   *
   * 1.10: D2Lang.0x6FC12DB0 (#10061) ?utfwidth@Unicode@@QBEHXZ
   */
  int utfwidth() const;

 private:
  /**
   * Vanilla bug: The characters in the Latin-1 Supplement block are
   * uppercase.
   *
   * D2Lang.[0x6FC1D508 to 0x6FC1D708) (#10019) ?_toLowerTable@Unicode@@0PAGA
   */
  static unsigned short _toLowerTable[256];

  // D2Lang.[0x6FC1D308 to 0x6FC1D508) (#10020) ?_toUpperTable@Unicode@@0PAGA
  static unsigned short _toUpperTable[256];
};
