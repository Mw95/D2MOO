/**
 * D2MOO
 * Copyright (c) 2020-2022  The Phrozen Keep community
 *
 * This file belongs to D2MOO.
 * File authors: Mir Drualga, Lectem
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

#include <D2Unicode.h>

#include <assert.h>
#include <ctype.h>

#include "Fog.h"

/**
 * Collation weights of the characters [0x00, 0xFF], used by strncoll.
 * Letters are mapped to [0x100, 0x122] regardless of case, and accented
 * letters share the weight of their base letter.
 *
 * 1.10: D2Lang.[0x6FC1D108 to 0x6FC1D308)
 */
static const unsigned short sgCollationTable[256] = {
  0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
  0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F,
  0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
  0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
  0x0040, 0x0100, 0x0101, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A, 0x010B, 0x010C, 0x010D, 0x010F,
  0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
  0x0060, 0x0100, 0x0101, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A, 0x010B, 0x010C, 0x010D, 0x010F,
  0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
  0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x0113, 0x008B, 0x0120, 0x008D, 0x008E, 0x008F,
  0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x0113, 0x009B, 0x0120, 0x009D, 0x009E, 0x0119,
  0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
  0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
  0x0100, 0x0100, 0x0100, 0x0100, 0x011E, 0x011D, 0x011B, 0x0102, 0x0104, 0x0104, 0x0104, 0x0104, 0x0108, 0x0108, 0x0108, 0x0108,
  0x0121, 0x010E, 0x010F, 0x010F, 0x010F, 0x010F, 0x011F, 0x00D7, 0x011C, 0x0115, 0x0115, 0x0115, 0x0115, 0x0119, 0x0122, 0x0113,
  0x0100, 0x0100, 0x0100, 0x0100, 0x011E, 0x011D, 0x011B, 0x0102, 0x0104, 0x0104, 0x0104, 0x0104, 0x0108, 0x0108, 0x0108, 0x0108,
  0x0121, 0x010E, 0x010F, 0x010F, 0x010F, 0x010F, 0x011F, 0x00F7, 0x011C, 0x0115, 0x0115, 0x0115, 0x0115, 0x0119, 0x0122, 0x0119,
};

BOOL __fastcall Unicode::isWordEnd(const Unicode* str, size_t index) {
  if (index == 0) {
    return FALSE;
  }

  return ::isalnum(str[index].ch)
      && !::isalnum(str[index + 1].ch);
}

void __cdecl Unicode::sprintf(
    int buffer_size,
    Unicode* buffer,
    const Unicode* format,
    ...) {

  if (format == NULL) {
    return;
  }

  int i_buffer = 0;
  buffer[0].ch = L'\0';

  va_list args;
  va_start(args, format);

  Unicode percent_sign[2] = { L'%', L'\0' };
  const Unicode* strstr_result = NULL;

  for (int i_format = 0; format[i_format].ch != L'\0'; i_format += 2) {
    unsigned short conversion_specifier = L'\0';
    const Unicode* next_percent_sign = Unicode::strstr(&format[i_format], percent_sign);
    if (next_percent_sign != NULL) {
      strstr_result = next_percent_sign;
      conversion_specifier = next_percent_sign[1];
    }

    /*
     * Copy format into buffer up to where the % is found, or if % not
     * found, then copy the remaining string.
     */
    while (&format[i_format] != strstr_result
        && format[i_format].ch != L'\0') {
      if (i_buffer >= buffer_size) {
        buffer[i_buffer - 1].ch = L'\0';
        va_end(args);
        return;
      }

      buffer[i_buffer] = format[i_format];

      ++i_format;
      ++i_buffer;
    }

    if (i_buffer >= buffer_size) {
      buffer[i_buffer - 1].ch = L'\0';
      va_end(args);
      return;
    }

    if (format[i_format].ch == L'\0') {
      buffer[i_buffer].ch = L'\0';
      va_end(args);
      return;
    }

    D2_ASSERT(strstr_result != NULL);

    /*
     * Note: every conversion specifier consumes an argument, including
     * %%. The converted values are copied along with their null
     * terminator.
     */
    switch (conversion_specifier) {
      case L'\0': {
        /*
         * % is the last character.
         */
        Unicode::strcpy(&buffer[i_buffer], percent_sign);
        va_end(args);
        return;
      }

      case L'%': {
        (void)va_arg(args, int);

        if (i_buffer + 1 >= buffer_size) {
          va_end(args);
          return;
        }

        Unicode::strcpy(&buffer[i_buffer], percent_sign);
        ++i_buffer;

        break;
      }

      case L'd':
      case L'u': {
        char itoa_buffer[16];

        if (conversion_specifier == L'd') {
          ::_itoa(va_arg(args, int), itoa_buffer, 10); // NOLINT(clang-diagnostic-deprecated-declarations)
        } else {
          ::_ultoa(va_arg(args, unsigned int), itoa_buffer, 10); // NOLINT(clang-diagnostic-deprecated-declarations)
        }

        Unicode itoa_unicode[15];
        Unicode::toUnicode(itoa_unicode, itoa_buffer, 15);

        int itoa_length = Unicode::strlen(itoa_unicode);
        if ((i_buffer + itoa_length + 1) >= buffer_size) {
          va_end(args);
          return;
        }

        Unicode::strcpy(&buffer[i_buffer], itoa_unicode);
        i_buffer += itoa_length;

        break;
      }

      case L's': {
        const Unicode* arg_string = va_arg(args, const Unicode*);
        const int arg_s_length = Unicode::strlen(arg_string);

        if (arg_s_length == 0 || (i_buffer + arg_s_length + 1) >= buffer_size) {
          /*
           * Append as much of the string as possible, then stop.
           *
           * Vanilla bug: The original appends to the end of the string
           * starting at buffer[i_buffer], which is not null-terminated
           * after copying literal characters from the format, and
           * dereferences a NULL argument. Here the buffer is terminated
           * at i_buffer first, and NULL is treated as an empty string.
           */
          buffer[i_buffer].ch = L'\0';
          if (arg_string != NULL) {
            Unicode::strncat(
                &buffer[i_buffer],
                arg_string,
                buffer_size - (i_buffer + 1));
          }
          va_end(args);
          return;
        }

        Unicode::strcpy(&buffer[i_buffer], arg_string);
        i_buffer += arg_s_length;

        break;
      }

      default: {
        FOG_DisplayHalt(
            "Unknown format specifier in Unicode::sprintf",
            __FILE__,
            __LINE__);
        exit(-1);
      }
    }
  }

  va_end(args);
}

Unicode* __fastcall Unicode::strcat(Unicode* dest, const Unicode* src) {
  size_t i = 0;
  while (dest[i].ch != L'\0') {
    ++i;
  }

  Unicode::strcpy(&dest[i], src);

  return dest;
}

Unicode* __fastcall Unicode::strchr(const Unicode* str, Unicode ch) {
  for (size_t i = 0; str[i].ch != L'\0'; ++i) {
    if (str[i].ch == ch.ch) {
      return (Unicode*)&str[i];
    }
  }

  return NULL;
}

int __fastcall Unicode::strcmp(const Unicode* str1, const Unicode* str2) {
  /*
   * This loop does not run beyond the end of either string. If the
   * end of only one string is reached, then a comparison between '\0'
   * to a different character is made, and a return is guaranteed to
   * happen.
   */
  for (size_t i = 0; (str1[i].ch != L'\0') || (str2[i].ch != L'\0'); ++i) {
    if (str1[i].ch < str2[i].ch) {
      return -1;
    } else if (str1[i].ch > str2[i].ch) {
      return 1;
    }
  }

  return 0;
}

Unicode* __fastcall Unicode::strcpy(Unicode* dest, const Unicode* src) {
  size_t i = 0;
  do {
    dest[i].ch = src[i].ch;
  } while (src[i++].ch != L'\0');

  return dest;
}

int __fastcall Unicode::stricmp(const Unicode* str1, const Unicode* str2) {
  /*
   * This loop does not run beyond the end of either string. If the
   * end of only one string is reached, then a comparison between '\0'
   * to a different character is made, and a return is guaranteed to
   * happen.
   */
  for (size_t i = 0; (str1[i].ch != L'\0') || (str2[i].ch != L'\0'); ++i) {
    Unicode ch1_upper = str1[i].toUpper();
    Unicode ch2_upper = str2[i].toUpper();

    if (ch1_upper.ch < ch2_upper.ch) {
      return -1;
    } else if (ch1_upper.ch > ch2_upper.ch) {
      return 1;
    }
  }

  return 0;
}

int __fastcall Unicode::strnicmp(const Unicode* str1, const Unicode* str2, size_t count) {
  /*
   * Faithful to the original: the uppercase characters being compared
   * are loaded before the pointers are advanced, so the comparison
   * lags one character behind the end-of-string checks.
   *
   * Vanilla bug: If one string is a prefix of the other string, then
   * 0 is returned. If count is 0, the first characters are still
   * compared.
   */
  unsigned short ch1_upper = str1->toUpper().ch;
  unsigned short ch2_upper = str2->toUpper().ch;

  if (str1->ch != L'\0') {
    do {
      if (str2->ch == L'\0' || count-- == 0 || ch1_upper != ch2_upper) {
        break;
      }

      ch1_upper = (str1++)->toUpper().ch;
      ch2_upper = (str2++)->toUpper().ch;
    } while (str1->ch != L'\0');
  }

  if (ch1_upper < ch2_upper) {
    return -1;
  }

  return (ch1_upper > ch2_upper) ? 1 : 0;
}

int __fastcall Unicode::strlen(const Unicode* str) {
  if (str == NULL) {
    return 0;
  }

  int i = 0;
  while ((str++)->ch != L'\0') {
    ++i;
  }

  return i;
}

Unicode* __fastcall Unicode::strncat(
    Unicode* dest,
    const Unicode* src,
    int count) {
  int i_dest = 0;
  while (dest[i_dest].ch != L'\0') {
    ++i_dest;
  }

  int i_src;
  for (i_src = 0; i_src != count && src[i_src].ch != L'\0'; ++i_src) {
    dest[i_dest + i_src] = src[i_src];
  }

  dest[i_dest + i_src] = L'\0';

  return dest;
}

int __fastcall Unicode::strncmp(
    const Unicode* str1,
    const Unicode* str2,
    size_t count) {
  /*
   * Vanilla bug: If one string is a prefix of the other string, then
   * the loop ends early and 0 is returned.
   */
  for (size_t i = 0;
      (str1[i].ch != L'\0') && (str2[i].ch != L'\0') && (i < count);
      ++i) {
    if (str1[i].ch < str2[i].ch) {
      return -1;
    } else if (str1[i].ch > str2[i].ch) {
      return 1;
    }
  }

  return 0;
}

/**
 * This implementation outputs the same binary from 1.00.
 *
 * 1.00: D2Lang.0x1000114A (#10042)
 * 1.10: D2Lang.0x6FC11460 (#10044)
 * 1.11: D2Lang.0x6FC0A900 (#10044)
 * 1.13c: D2Lang.0x6FC0B0D0 (#10044)
 * ?strncpy@Unicode@@SIPAU1@PAU1@PBU1@H@Z
 */
Unicode* __fastcall Unicode::strncpy(
    Unicode* dest, const Unicode* src, int count)
{
  // Copy src into dest, up to count characters.
  Unicode* current_dest = dest;
  for (; (count--) != 0 && src->ch != L'\0'; ++current_dest, ++src)
  {
    current_dest->ch = src->ch;
  }

  // Fill remaining characters as null-terminator.
  for (; count != -1; ++current_dest, --count)
  {
    current_dest->ch = L'\0';
  }

  return dest;
}

Unicode* __fastcall Unicode::strstr(
    const Unicode* str,
    const Unicode* substr) {
  if (str == NULL || substr == NULL) {
    return NULL;
  }

  size_t i_str;
  for (i_str = 0; ; ++i_str) {
    for (; str[i_str].ch != substr[0].ch; ++i_str) {
      if (str[i_str].ch == L'\0') {
        return NULL;
      }
    }

    if (str[i_str].ch == '\0') {
      return NULL;
    }

    size_t i_substr;
    for (i_substr = 0;
        str[i_str + i_substr].ch == substr[i_substr].ch;
        ++i_substr) {
      if (str[i_str + i_substr].ch == L'\0') {
        break;
      }

      if (substr[i_substr].ch == L'\0') {
        return (Unicode*)&str[i_str];
      }
    }

    if (substr[i_substr].ch == L'\0') {
      return (Unicode*)&str[i_str];
    }
  }

  return (Unicode*)&str[i_str];
}

int __fastcall Unicode::strncoll(const Unicode* str1, const Unicode* str2, int count) {
  int i = 0;
  if (str1[0].ch != L'\0') {
    while (str2[i].ch != L'\0' && i < count) {
      const unsigned short ch1 = str1[i].ch;
      const unsigned short ch2 = str2[i].ch;

      int diff;
      if (ch1 < 0x100 && ch2 < 0x100) {
        diff = sgCollationTable[ch1] - sgCollationTable[ch2];
      } else {
        diff = ch1 - ch2;
      }

      if (diff != 0) {
        return diff;
      }

      ++i;
      if (str1[i].ch == L'\0') {
        break;
      }
    }
  }

  if (i < count && str1[i].ch != str2[i].ch) {
    return (str1[i].ch != L'\0') ? 1 : -1;
  }

  return Unicode::strnicmp(str1, str2, count);
}

int __fastcall Unicode::strcoll(const Unicode* str1, const Unicode* str2) {
  return Unicode::strncoll(str1, str2, 0x7FFFFFFF);
}

Unicode* __fastcall Unicode::strstri(const Unicode* str, const Unicode* substr) {
  if (str == NULL || substr == NULL) {
    return NULL;
  }

  for (;;) {
    // Find a candidate for the first character.
    while (str->toUpper().ch != substr->toUpper().ch) {
      ++str;
      if (str->ch == L'\0') {
        return NULL;
      }
    }

    size_t i = 0;
    while (str[i].toUpper().ch == substr[i].toUpper().ch && str[i].ch != L'\0') {
      if (substr[i].ch == L'\0') {
        return (Unicode*)str;
      }
      ++i;
    }

    if (substr[i].ch == L'\0') {
      return (Unicode*)str;
    }

    if (str[i].ch == L'\0') {
      return NULL;
    }

    ++str;
  }
}
