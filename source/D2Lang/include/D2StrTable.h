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

#include <D2Constants.h>

#include "D2Lang.h"

#include <cstdint>

enum D2C_LanguageCodeType
{
	// Name of the directory containing the language files, e.g. "ENG" for data\local\lng\ENG
	LANGUAGE_CODE_DIRECTORY = 0,
	// e.g. "ENG" for Japanese and Korean, the language code otherwise
	LANGUAGE_CODE_ALTERNATE = 1,
	// e.g. "USA" for English, "BRA" for Portuguese
	LANGUAGE_CODE_REGION = 2,
	// Four character code such as 'enUS', written without null terminator
	LANGUAGE_CODE_LOCALE = 3,
};

/**
 * Returns the string table language.
 *
 * 1.00: D2Lang.0x100010B9 (#10007)
 * 1.10: D2Lang.0x6FC13DF0 (#10007)
 * 1.13c: D2Lang.0x6FC09290 (#10009)
 * 1.14c: Game.0x00522610
 */
D2LANG_DLL_DECL D2C_Language STRTABLE_GetLanguage();

/**
 * Converts an integer value into a into a null-terminated UCS-2 string,
 * with commas separating every group of three digits. If the required
 * length of the converted string is greater than the nMaxLength, then
 * an asterisk character '*' will be written in place of the digits.
 *
 * The value of nMaxLength must be greater than 2, or an assertion will
 * fail.
 *
 * 1.00: D2Lang.0x100010AF (#10009)
 * 1.10: D2Lang.0x6FC140E0 (#10009)
 * 1.13c: D2Lang.0x6FC09BC0 (#10002)
 * 1.14c: Game.0x00523510
 */
D2LANG_DLL_DECL void __stdcall STR_GroupIntDigits(
		Unicode* pUnicode, int nValue, int nMaxLength);

/**
 * Converts a unsigned integer value into a into a null-terminated UCS-2
 * string, with commas separating every group of three digits. If the
 * required length of the converted string is greater than the
 * nMaxLength, then an asterisk character '*' will be written in place
 * of the digits.
 *
 * The value of nMaxLength must be greater than 2, or an assertion will
 * fail.
 *
 * 1.00: D2Lang.0x100010DC (#10010)
 * 1.10: D2Lang.0x6FC14210 (#10010)
 * 1.13c: D2Lang.0x6FC09A80 (#10006)
 * 1.14c: Game.0x005228A0
 */
D2LANG_DLL_DECL void __stdcall STR_GroupUintDigits(
		Unicode* pUnicode, unsigned int dwValue, int nMaxLength);

/**
 * Writes a code identifying the string table language into szDest.
 * See D2C_LanguageCodeType.
 *
 * 1.10: D2Lang.0x6FC13FB0 (#10006)
 */
D2LANG_DLL_DECL void __stdcall STRTABLE_GetLanguageCode(char* szDest, D2C_LanguageCodeType eType);

/**
 * Returns the language of the operating system, from the "sLanguage"
 * international setting. Returns LANGUAGE_ENGLISH if the language is
 * unknown.
 *
 * 1.10: D2Lang.0x6FC13E60 (#10008)
 */
D2LANG_DLL_DECL D2C_Language STRTABLE_GetSystemLanguage();

/**
 * Same as STR_GroupIntDigits, for 64-bit integers.
 *
 * 1.10: D2Lang.0x6FC14330 (#10011)
 */
D2LANG_DLL_DECL void __stdcall STR_GroupInt64Digits(
		Unicode* pUnicode, int64_t nValue, int nMaxLength);

/**
 * Same as STR_GroupUintDigits for 64-bit integers, but only the 4 to 6
 * most significant digits are kept, followed by a localized suffix for
 * thousands, millions, billions or trillions. For example, 1234567 is
 * written as "1,234K". The digits are truncated, not rounded.
 *
 * 1.10: D2Lang.0x6FC14450 (#10012)
 */
D2LANG_DLL_DECL void __stdcall STR_GroupUint64DigitsWithSuffix(
		Unicode* pUnicode, uint64_t nValue, int nMaxLength);
