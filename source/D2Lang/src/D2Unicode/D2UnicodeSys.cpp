/**
 * D2MOO
 * Copyright (c) 2020-2022  The Phrozen Keep community
 *
 * This file belongs to D2MOO.
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

// Conversions between Unicode and the "system" code page (Unicode\UNISYS.CPP in the original sources).

#include <D2Unicode.h>

#include <stdlib.h>
#include <string.h>

#include <Archive.h>
#include <Fog.h>
#include <Storm.h>

#pragma pack(push, 1)

struct SysMapEntry {
  uint16_t sys;
  uint16_t unicode;
};

#pragma pack(pop)

// 1.10: D2Lang.0x6FC20C68
static uint16_t sgnSysMapEntries;
// Sorted by Unicode character, for unicode2Sys.
// 1.10: D2Lang.0x6FC20C6C
static SysMapEntry* sgpSysMap;
// Pairs of [first, last] bytes that are single-byte characters in the system code page.
// 1.10: D2Lang.0x6FC20C70
static uint8_t (*sgpSingleByteRanges)[2];
// 1.10: D2Lang.0x6FC20C74
static char sgszSysMapName[41];
// Indices of sgpSysMap sorted by system character, for sys2Unicode.
// 1.10: D2Lang.0x6FC20C9C
static uint16_t* sgpSysMapIndices;
// 1.10: D2Lang.0x6FC20CA0
static uint8_t sgnSingleByteRanges;

static void* SysMapAlloc(size_t nSize) {
  return SMemAlloc(nSize, "new[]", -1, 0);
}

static void SysMapFree(void* pMemory) {
  SMemFree(pMemory, "delete[]", -1, 0);
}

static bool IsSingleByteChar(uint8_t ch) {
  for (int i = 0; i < sgnSingleByteRanges; ++i) {
    if (sgpSingleByteRanges[i][0] <= ch && ch <= sgpSingleByteRanges[i][1]) {
      return true;
    }
  }

  return false;
}

static int __cdecl CompareSysMapEntriesByUnicode(const void* pLhs, const void* pRhs) {
  return static_cast<const SysMapEntry*>(pLhs)->unicode - static_cast<const SysMapEntry*>(pRhs)->unicode;
}

/**
 * Returns the system character for a Unicode character, or -1 if the
 * character is not in the map. Control characters are not mapped.
 */
static int UnicodeToSysChar(unsigned short ch) {
  if (ch < 0x20) {
    return ch;
  }

  SysMapEntry key;
  key.unicode = ch;
  const SysMapEntry* pEntry = static_cast<const SysMapEntry*>(
      bsearch(&key, sgpSysMap, sgnSysMapEntries, sizeof(SysMapEntry), CompareSysMapEntriesByUnicode));
  if (pEntry == NULL) {
    return -1;
  }

  return pEntry->sys;
}

/**
 * Returns the Unicode character for a system character, or -1 if the
 * character is not in the map. Control characters are not mapped.
 */
static int SysToUnicodeChar(unsigned short ch) {
  if (ch < 0x20) {
    return ch;
  }

  int nLast = sgnSysMapEntries - 1;
  if (ch < sgpSysMap[sgpSysMapIndices[0]].sys || ch > sgpSysMap[sgpSysMapIndices[nLast]].sys) {
    return -1;
  }

  int nFound = nLast;
  if (ch != sgpSysMap[sgpSysMapIndices[nLast]].sys) {
    int nLow = 0;
    int nHigh = nLast;
    nFound = nHigh >> 1;
    do {
      if (ch < sgpSysMap[sgpSysMapIndices[nFound]].sys) {
        nHigh = nFound;
      } else {
        nLow = nFound;
      }
      nFound = (nHigh + nLow) >> 1;
    } while (nHigh - nLow > 1);

    if (sgpSysMap[sgpSysMapIndices[nFound]].sys != ch) {
      return -1;
    }
  }

  return sgpSysMap[sgpSysMapIndices[nFound]].unicode;
}

/**
 * The map file has the following layout:
 * - "KAMAP\n"
 * - The name of the map, terminated by 0x1A (at most 40 characters)
 * - uint16_t nEntries
 * - uint8_t nRanges
 * - uint8_t aRanges[nRanges][2]: ranges of single-byte characters
 * - uint16_t aMap[nEntries][2]: pairs of (system character, Unicode character), sorted by Unicode character
 * - uint16_t aIndices[nEntries]: indices of aMap sorted by system character
 *
 * 1.10: D2Lang.0x6FC123E0 (#10032)
 */
BOOL __fastcall Unicode::loadSysMap(HD2ARCHIVE__* hArchive, const char* szFileName) {
  uint8_t* pFile = (uint8_t*)ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(hArchive, szFileName, nullptr);

  if (::strncmp((const char*)pFile, "KAMAP\n", 5) != 0) {
    D2_FREE(pFile);
    return FALSE;
  }

  const uint8_t* pName = pFile + 6;
  int nNameLength = 0;
  while (pName[nNameLength] != 0x1A) {
    ++nNameLength;
    if (nNameLength >= 40) {
      D2_FREE(pFile);
      return FALSE;
    }
  }

  // Note: one byte larger than the original buffer, which could be overflowed by one byte.
  char szName[41];
  ::strncpy(szName, (const char*)pName, nNameLength + 1);
  szName[nNameLength + 1] = '\0';
  ::strtok(szName, "\n");

  const uint8_t* pEntriesCount = pName + nNameLength + 5;
  const uint16_t nEntries = *(const uint16_t*)pEntriesCount;
  const uint8_t nRanges = pEntriesCount[2];
  const uint8_t* pData = pEntriesCount + 3;

  if (sgpSingleByteRanges) {
    SysMapFree(sgpSingleByteRanges);
  }
  sgpSingleByteRanges = (uint8_t(*)[2])SysMapAlloc(nRanges * 2);
  if (!sgpSingleByteRanges) {
    D2_FREE(pFile);
    return FALSE;
  }
  memcpy(sgpSingleByteRanges, pData, nRanges * 2);
  pData += nRanges * 2;

  if (sgpSysMap) {
    SysMapFree(sgpSysMap);
  }
  sgpSysMap = (SysMapEntry*)SysMapAlloc(nEntries * sizeof(SysMapEntry));
  if (!sgpSysMap) {
    D2_FREE(pFile);
    return FALSE;
  }
  for (int i = 0; i < nEntries; ++i) {
    // Vanilla bug: Only the low byte of each character is read.
    sgpSysMap[i].sys = pData[0];
    sgpSysMap[i].unicode = pData[2];
    pData += 4;
  }

  if (sgpSysMapIndices) {
    SysMapFree(sgpSysMapIndices);
  }
  sgpSysMapIndices = (uint16_t*)SysMapAlloc(nEntries * sizeof(uint16_t));
  if (!sgpSysMapIndices) {
    D2_FREE(pFile);
    return FALSE;
  }
  for (int i = 0; i < nEntries; ++i) {
    sgpSysMapIndices[i] = *(const uint16_t*)pData;
    pData += 2;
  }

  sgnSysMapEntries = nEntries;
  sgnSingleByteRanges = nRanges;
  ::strcpy(sgszSysMapName, szName);

  D2_FREE(pFile);
  return TRUE;
}

/**
 * 1.10: D2Lang.0x6FC12370 (#10058)
 */
void __fastcall Unicode::unloadSysMap() {
  if (sgpSingleByteRanges) {
    SysMapFree(sgpSingleByteRanges);
    sgpSingleByteRanges = nullptr;
  }

  if (sgpSysMap) {
    SysMapFree(sgpSysMap);
    sgpSysMap = nullptr;
  }

  if (sgpSysMapIndices) {
    SysMapFree(sgpSysMapIndices);
    sgpSysMapIndices = nullptr;
  }
}

/**
 * 1.10: D2Lang.0x6FC12650 (#10048)
 */
Unicode* __fastcall Unicode::sys2Unicode(Unicode* dest, const char* src, int count) {
  if (!sgpSysMapIndices) {
    return Unicode::win2Unicode(dest, src, count);
  }

  const uint8_t* pSrc = (const uint8_t*)src;
  int i = 0;
  while (i < count) {
    const uint8_t ch = *pSrc;
    if (ch == '\0') {
      break;
    }

    unsigned short sysChar;
    if (ch >= 0x20 && !IsSingleByteChar(ch)) {
      sysChar = (ch << 8) | pSrc[1];
      pSrc += 2;
    } else {
      sysChar = ch;
      pSrc += 1;
    }

    const int nUnicode = SysToUnicodeChar(sysChar);
    if (nUnicode < 0) {
      continue;
    }

    dest[i].ch = nUnicode;
    ++i;
  }

  if (*pSrc == '\0' && i < count) {
    dest[i].ch = L'\0';
  }

  return dest;
}

/**
 * 1.10: D2Lang.0x6FC127C0 (#10054)
 */
char* __fastcall Unicode::unicode2Sys(char* dest, const Unicode* src, int count) {
  if (!sgpSysMap) {
    return Unicode::unicode2Win(dest, src, count);
  }

  int i = 0;
  for (; i < count; ++src) {
    if (src->ch == L'\0') {
      break;
    }

    const int nSysChar = UnicodeToSysChar(src->ch);
    if (nSysChar < 0) {
      continue;
    }

    const uint8_t nLowByte = nSysChar & 0xFF;
    if ((nSysChar & 0xFF00) == 0 && (nLowByte < 0x20 || IsSingleByteChar(nLowByte))) {
      dest[i++] = nLowByte;
    } else {
      // Note: characters that are not single-byte characters are written on two bytes, even if the high byte is 0.
      dest[i++] = nSysChar >> 8;
      dest[i++] = nLowByte;
    }
  }

  if (src->ch == L'\0' && i < count) {
    dest[i] = '\0';
  }

  return dest;
}

/**
 * 1.10: D2Lang.0x6FC128D0 (#10049)
 */
unsigned long __fastcall Unicode::sysWidth(const Unicode* str, int count) {
  if (!sgpSysMap) {
    return Unicode::strlen(str);
  }

  unsigned long nWidth = 0;
  for (int i = 0; i < count && str[i].ch != L'\0'; ++i) {
    const int nSysChar = UnicodeToSysChar(str[i].ch);
    if (nSysChar < 0) {
      continue;
    }

    const uint8_t nLowByte = nSysChar & 0xFF;
    if ((nSysChar & 0xFF00) == 0 && (nLowByte < 0x20 || IsSingleByteChar(nLowByte))) {
      nWidth += 1;
    } else {
      nWidth += 2;
    }
  }

  return nWidth;
}

/**
 * 1.10: D2Lang.0x6FC129B0 (#10056)
 */
unsigned long __fastcall Unicode::unicodeWidth(const char* str, int count) {
  if (!sgpSysMapIndices) {
    return ::strlen(str);
  }

  unsigned long nWidth = 0;
  for (int i = 0; i < count && str[i] != '\0'; ++nWidth) {
    const uint8_t ch = str[i];
    if (ch < 0x20 || IsSingleByteChar(ch)) {
      i += 1;
    } else {
      i += 2;
    }
  }

  return nWidth;
}
