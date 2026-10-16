#include "StormInternal.h"

#include <cstdio>
#include <cstring>
#include <cmath>

// String functions

// Storm.0x6FFE2370
static const uint32_t sgdwHashTable[16] =
{
	0x486E26EE, 0xDCAA16B3, 0xE1918EEF, 0x202DAFDB, 0x341C7DC7, 0x1C365303, 0x40EF2D37, 0x65FD5E49,
	0xD6057177, 0x904ECE93, 0x1C38024F, 0x98FD323B, 0xE3061AE7, 0xA39B0FA1, 0x9797F25F, 0xE4444563,
};

// Storm.0x6FFE23B0
static const uint64_t sgqwHashTable[16] =
{
	0x486E26EEDCAA16B3ull, 0xE1918EEF202DAFDBull, 0x341C7DC71C365303ull, 0x40EF2D3765FD5E49ull,
	0xD6057177904ECE93ull, 0x1C38024F98FD323Bull, 0xE3061AE7A39B0FA1ull, 0x9797F25FE4444563ull,
	0xCD2EC20C8DC1B898ull, 0x31759633799A306Dull, 0x8C2063852E6E9627ull, 0x79237D9973922C66ull,
	0x8728628D28628824ull, 0x8F1F7E9625887795ull, 0x296E3281389C0D60ull, 0x6F4893CA61636542ull,
};

#define SSTR_FRACTION_DIGITS 20

// Storm.0x6FFEC910 : sgdFractionTable[n][d] = d * 10^-(n+1)
static double sgdFractionTable[SSTR_FRACTION_DIGITS][10];

// Storm.0x6FFDA2C0
void SStrInitialize()
{
	for (int32_t nExponent = -1; nExponent > -1 - SSTR_FRACTION_DIGITS; --nExponent)
	{
		const double dPower = pow(10.0, nExponent);
		for (int32_t nDigit = 0; nDigit < 10; ++nDigit)
		{
			sgdFractionTable[-1 - nExponent][nDigit] = nDigit * dPower;
		}
	}
}

// Storm.0x6FFDA5B0
static int SStrVPrintfInternal(char* dest, size_t maxchars, const char* format, va_list arglist)
{
	if (!maxchars)
	{
		return 0;
	}

	if (maxchars == STORM_MAX_STR)
	{
		return vsprintf(dest, format, arglist);
	}

	const uint32_t nResult = (uint32_t)_vsnprintf(dest, maxchars, format, arglist);
	if (nResult < maxchars)
	{
		return nResult;
	}

	dest[maxchars - 1] = '\0';
	return maxchars - 1;
}

// Storm.0x6FFDAFA0
// Bob Jenkins' lookup2 hash function
static uint32_t SStrBobJenkinsHash(const uint8_t* k, uint32_t length, uint32_t initval)
{
#define SSTR_BJMIX(a, b, c)                     \
	{                                           \
		a -= b; a -= c; a ^= (c >> 13);         \
		b -= c; b -= a; b ^= (a << 8);          \
		c -= a; c -= b; c ^= (b >> 13);         \
		a -= b; a -= c; a ^= (c >> 12);         \
		b -= c; b -= a; b ^= (a << 16);         \
		c -= a; c -= b; c ^= (b >> 5);          \
		a -= b; a -= c; a ^= (c >> 3);          \
		b -= c; b -= a; b ^= (a << 10);         \
		c -= a; c -= b; c ^= (b >> 15);         \
	}

	uint32_t a = 0x9E3779B9;
	uint32_t b = 0x9E3779B9;
	uint32_t c = initval;
	uint32_t len = length;

	while (len >= 12)
	{
		a += k[0] + ((uint32_t)k[1] << 8) + ((uint32_t)k[2] << 16) + ((uint32_t)k[3] << 24);
		b += k[4] + ((uint32_t)k[5] << 8) + ((uint32_t)k[6] << 16) + ((uint32_t)k[7] << 24);
		c += k[8] + ((uint32_t)k[9] << 8) + ((uint32_t)k[10] << 16) + ((uint32_t)k[11] << 24);
		SSTR_BJMIX(a, b, c);
		k += 12;
		len -= 12;
	}

	c += length;
	switch (len)
	{
	case 11: c += (uint32_t)k[10] << 24; // fallthrough
	case 10: c += (uint32_t)k[9] << 16;  // fallthrough
	case 9:  c += (uint32_t)k[8] << 8;   // fallthrough
	case 8:  b += (uint32_t)k[7] << 24;  // fallthrough
	case 7:  b += (uint32_t)k[6] << 16;  // fallthrough
	case 6:  b += (uint32_t)k[5] << 8;   // fallthrough
	case 5:  b += k[4];                  // fallthrough
	case 4:  a += (uint32_t)k[3] << 24;  // fallthrough
	case 3:  a += (uint32_t)k[2] << 16;  // fallthrough
	case 2:  a += (uint32_t)k[1] << 8;   // fallthrough
	case 1:  a += k[0];                  // fallthrough
	default: break;
	}
	SSTR_BJMIX(a, b, c);
	return c;

#undef SSTR_BJMIX
}

// Storm.#501
size_t __stdcall SStrCopy(char* dest, const char* source, size_t destsize)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(dest);
	STORM_VALIDATE_ARG(source);
	STORM_VALIDATE_END(0);

	if (!destsize)
	{
		return 0;
	}

	char* pLast = dest + destsize - 1;
	char* pDest = dest;
	while (pDest != pLast)
	{
		const char c = *source++;
		*pDest = c;
		if (!c)
		{
			return pDest - dest;
		}
		++pDest;
	}
	*pLast = '\0';
	return pLast - dest;
}

// Storm.#502
uint32_t __stdcall SStrHash(const char* string, uint32_t flags, uint32_t seed)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(0);

	uint32_t dwHash = seed ? seed : 0x7FED7FED;
	uint32_t dwShift = 0xEEEEEEEE;
	for (const uint8_t* pChar = (const uint8_t*)string; *pChar; ++pChar)
	{
		uint32_t c = *pChar;
		if (!(flags & SSTR_HASH_CASESENSITIVE))
		{
			if (c >= 'a' && c <= 'z')
			{
				c -= 'a' - 'A';
			}
			if (c == '/')
			{
				c = '\\';
			}
		}

		dwHash = (dwHash + dwShift) ^ (sgdwHashTable[c >> 4] - sgdwHashTable[c & 0xF]);
		dwShift = c + dwShift + (dwShift << 5) + dwHash + 3;
	}

	return dwHash ? dwHash : 1;
}

// Storm.#503
size_t __stdcall SStrNCat(char* base, const char* append, size_t max_length)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(base);
	STORM_VALIDATE_ARG(append);
	STORM_VALIDATE_END(0);

	if (!max_length)
	{
		return 0;
	}

	char* pLast = base + max_length - 1;
	if (max_length != STORM_MAX_STR)
	{
		*pLast = '\0';
	}

	char* pDest = base + strlen(base);
	while (pDest != pLast)
	{
		const char c = *append++;
		*pDest = c;
		if (!c)
		{
			return pDest - base;
		}
		++pDest;
	}
	*pLast = '\0';
	return pLast - base;
}

// Storm.#504
void __stdcall SStrTokenize(const char** string, char* buffer, size_t bufferchars, const char* delimiter, int32_t* quoted)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_ARG(*string);
	STORM_VALIDATE_ARG(buffer || !bufferchars);
	STORM_VALIDATE_ARG(delimiter);
	STORM_VALIDATE_END_VOID;

	const BOOL bQuotesAllowed = SStrChr(delimiter, '"') != nullptr;
	const char* pCurrent = *string;
	BOOL bInQuotes = FALSE;
	BOOL bWasQuoted = FALSE;

	// Skip the leading delimiters
	while (*pCurrent && SStrChr(delimiter, *pCurrent))
	{
		if (bQuotesAllowed && *pCurrent == '"')
		{
			bInQuotes = TRUE;
			bWasQuoted = TRUE;
			++pCurrent;
			break;
		}
		++pCurrent;
	}

	size_t nCount = 0;
	for (char c = *pCurrent; c; c = *pCurrent)
	{
		if (bQuotesAllowed && c == '"')
		{
			if (nCount && !bInQuotes)
			{
				break;
			}

			bWasQuoted = TRUE;
			bInQuotes = !bInQuotes;
			++pCurrent;
			if (!bInQuotes)
			{
				break;
			}
			continue;
		}

		if (!bInQuotes && SStrChr(delimiter, c))
		{
			++pCurrent;
			break;
		}

		if (nCount + 1 < bufferchars)
		{
			buffer[nCount++] = c;
		}
		++pCurrent;
	}

	if (nCount < bufferchars)
	{
		buffer[nCount] = '\0';
	}

	*string = pCurrent;
	if (quoted)
	{
		*quoted = bWasQuoted;
	}
}

// Storm.#505
const char* __stdcall SStrSearch(const char* string, char c, BOOL bReverse)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(nullptr);

	return bReverse ? SStrChrR(string, c) : SStrChr(string, c);
}

// Storm.#506
size_t __stdcall SStrLen(const char* string)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(0);

	return strlen(string);
}

// Storm.#507
void* __stdcall SStrDup(int a1)
{
	const char* string = (const char*)(uintptr_t)a1;

	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(nullptr);

	const size_t nSize = SStrLen(string) + 1;
	char* pResult = (char*)SMemAlloc(nSize, "C:\\projects\\D2\\head\\Diablo2\\3rdParty\\STORM\\SOURCE\\SSTR.CPP", 498, 0);
	SMemCopy(pResult, string, nSize);
	return pResult;
}

// Storm.#508
int32_t __stdcall SStrCmp(const char* Str1, const char* Str2, size_t MaxCount)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(Str1);
	STORM_VALIDATE_ARG(Str2);
	STORM_VALIDATE_END((int32_t)(Str1 - Str2));

	return strncmp(Str1, Str2, MaxCount);
}

// Storm.#509
int32_t __stdcall SStrCmpI(const char* Str1, const char* Str, size_t MaxCount)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(Str1);
	STORM_VALIDATE_ARG(Str);
	STORM_VALIDATE_END((int32_t)(Str1 - Str));

	return _strnicmp(Str1, Str, MaxCount);
}

// Storm.#510
char* __stdcall SStrUpper(char* Str)
{
	return _strupr(Str);
}

// Storm.#571
const char* __stdcall SStrChr(const char* string, char c)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(nullptr);

	for (; *string; ++string)
	{
		if (*string == c)
		{
			return string;
		}
	}
	return nullptr;
}

// Storm.#572
const char* __stdcall SStrChrR(const char* string, char c)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(nullptr);

	const char* pResult = nullptr;
	for (; *string; ++string)
	{
		if (*string == c)
		{
			pResult = string;
		}
	}
	return pResult;
}

// Shared by SStrToDouble and SStrToFloat
static double SStrParseDouble(const char* string)
{
	const BOOL bNegative = *string == '-';
	if (bNegative)
	{
		++string;
	}

	// Integer part, accumulated 9 digits at a time
	const char* pChunkStart = string;
	uint32_t nChunk = (uint32_t)(*string - '0');
	double dAccumulator = 0.0;
	double dResult;
	if (nChunk < 10)
	{
		++string;
		for (uint32_t nDigit = (uint32_t)(*string - '0'); nDigit < 10; nDigit = (uint32_t)(*string - '0'))
		{
			++string;
			nChunk = nDigit + 10 * nChunk;
			if (nChunk >= 0x19999999)
			{
				dAccumulator = pow(10.0, (double)(int32_t)(string - pChunkStart)) * dAccumulator + (double)(int64_t)nChunk;
				nChunk = 0;
				pChunkStart = string;
			}
		}

		if (dAccumulator != 0.0)
		{
			dResult = pow(10.0, (double)(int32_t)(string - pChunkStart)) * dAccumulator + (double)(int64_t)nChunk;
		}
		else
		{
			dResult = (double)(int64_t)nChunk;
		}
	}
	else
	{
		dResult = 0.0;
	}

	// Fractional part
	if (*string == '.')
	{
		++string;
		uint32_t nDigit = (uint32_t)(*string - '0');
		if (nDigit < 10)
		{
			int32_t nExponent = -1;
			uint32_t nRow = 0;
			do
			{
				++string;
				if (nExponent > -1 - SSTR_FRACTION_DIGITS)
				{
					dResult += sgdFractionTable[nRow][nDigit];
				}
				else
				{
					dResult = pow(10.0, (double)nExponent) * (double)(int64_t)nDigit + dResult;
				}
				nDigit = (uint32_t)(*string - '0');
				--nExponent;
				++nRow;
			}
			while (nDigit < 10);
		}
	}

	// Exponent
	if (*string == 'e' || *string == 'E')
	{
		++string;
		if (*string == '+')
		{
			++string;
		}
		dResult = pow(10.0, (double)SStrToInt(string)) * dResult;
	}

	return bNegative ? -dResult : dResult;
}

// Storm.#573
double __stdcall SStrToDouble(const char* string)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(0.0);

	return SStrParseDouble(string);
}

// Storm.#574
float __stdcall SStrToFloat(const char* string)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(0.0f);

	return (float)SStrParseDouble(string);
}

// Storm.#575
int32_t __stdcall SStrToInt(const char* string)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(0);

	const BOOL bNegative = *string == '-';
	if (bNegative)
	{
		++string;
	}

	uint32_t nResult = 0;
	for (uint32_t nDigit = (uint32_t)(*string - '0'); nDigit < 10; nDigit = (uint32_t)(*++string - '0'))
	{
		nResult = nDigit + 10 * nResult;
	}

	return bNegative ? -(int32_t)nResult : (int32_t)nResult;
}

// Storm.#576
uint32_t __stdcall SStrToUnsigned(const char* string)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(0);

	uint32_t nResult = 0;
	for (uint32_t nDigit = (uint32_t)(*string - '0'); nDigit < 10; nDigit = (uint32_t)(*++string - '0'))
	{
		nResult = nDigit + 10 * nResult;
	}
	return nResult;
}

// Storm.#577
int64_t __stdcall SStrToInt64(const char* string)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(0);

	const BOOL bNegative = *string == '-';
	if (bNegative)
	{
		++string;
	}

	// Accumulated 9 digits at a time
	uint64_t nAccumulator = 0;
	uint32_t nChunk = (uint32_t)(*string - '0');
	uint64_t nResult;
	if (nChunk < 10)
	{
		const char* pChunkStart = string;
		++string;
		for (uint32_t nDigit = (uint32_t)(*string - '0'); nDigit < 10; nDigit = (uint32_t)(*string - '0'))
		{
			++string;
			nChunk = nDigit + 10 * nChunk;
			if (nChunk >= 0x19999999)
			{
				const uint64_t nMultiplier = (uint64_t)(int64_t)(pow(10.0, (double)(int32_t)(string - pChunkStart)) + 0.5);
				nAccumulator = nMultiplier * nAccumulator + nChunk;
				nChunk = 0;
				pChunkStart = string;
			}
		}

		if (nAccumulator)
		{
			const uint64_t nMultiplier = (uint64_t)(int64_t)(pow(10.0, (double)(int32_t)(string - pChunkStart)) + 0.5);
			nResult = nMultiplier * nAccumulator + nChunk;
		}
		else
		{
			nResult = nChunk;
		}
	}
	else
	{
		nResult = 0;
	}

	return bNegative ? -(int64_t)nResult : (int64_t)nResult;
}

// Storm.#578
int __cdecl SStrPrintf(char* DstBuf, size_t MaxCount, const char* Format, ...)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(DstBuf);
	STORM_VALIDATE_ARG(Format);
	STORM_VALIDATE_END(0);

	va_list args;
	va_start(args, Format);
	const int nResult = SStrVPrintfInternal(DstBuf, MaxCount, Format, args);
	va_end(args);
	return nResult;
}

// Storm.#579
int __stdcall SStrLower(char* Str)
{
	return (int)(intptr_t)_strlwr(Str);
}

// Storm.#580
uint64_t __stdcall SStrHash64(const char* string, uint32_t flags, uint64_t seed)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(0);

	uint64_t qwHash = seed ? seed : 0x7FED7FED7FED7FEDull;
	uint64_t qwShift = 0xEEEEEEEEEEEEEEEEull;
	for (const uint8_t* pChar = (const uint8_t*)string; *pChar; ++pChar)
	{
		uint32_t c = *pChar;
		if (!(flags & SSTR_HASH_CASESENSITIVE))
		{
			if (c >= 'a' && c <= 'z')
			{
				c -= 'a' - 'A';
			}
			if (c == '/')
			{
				c = '\\';
			}
		}

		qwHash = (qwHash + qwShift) ^ (sgqwHashTable[c >> 4] - sgqwHashTable[c & 0xF]);
		qwShift = qwShift * 33 + c + qwHash + 3;
	}

	return qwHash ? qwHash : 1;
}

// Storm.#581
int __cdecl SStrVPrintf(char* DstBuf, size_t MaxCount, const char* Format, va_list ArgList)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(DstBuf);
	STORM_VALIDATE_ARG(Format);
	STORM_VALIDATE_END(0);

	return SStrVPrintfInternal(DstBuf, MaxCount, Format, ArgList);
}

// Storm.#582
uint32_t __stdcall SHashString(const char* string)
{
	char szNormalized[1024];
	uint32_t nLength = 0;
	for (; *string && nLength < sizeof(szNormalized) - 1; ++string, ++nLength)
	{
		char c = *string;
		if (c >= 'a' && c <= 'z')
		{
			c -= 'a' - 'A';
		}
		else if (c == '/')
		{
			c = '\\';
		}
		szNormalized[nLength] = c;
	}
	szNormalized[nLength] = '\0';

	return SStrBobJenkinsHash((const uint8_t*)szNormalized, nLength, 0);
}

// Not exported by Storm 1.08, declared by the squall headers
uint32_t SStrHashHT(const char* string)
{
	return SHashString(string);
}

char* SStrChr(char* string, char search)
{
	return (char*)SStrChr((const char*)string, search);
}

char* SStrChrR(char* string, char search)
{
	return (char*)SStrChrR((const char*)string, search);
}
