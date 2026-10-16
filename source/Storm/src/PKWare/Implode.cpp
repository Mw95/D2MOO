#include "PKWare.h"

#include <cstring>

// Compression

#define PKWARE_MAX_REP_LENGTH   0x204
#define PKWARE_OUT_BUFFER_SIZE  0x800

// Storm.0x6FFE9248
static const uint8_t sgImplodeDistBits[64] =
{
	0x02, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
};

// Storm.0x6FFE9288
static const uint8_t sgImplodeDistCode[64] =
{
	0x03, 0x0D, 0x05, 0x19, 0x09, 0x11, 0x01, 0x3E, 0x1E, 0x2E, 0x0E, 0x36, 0x16, 0x26, 0x06, 0x3A,
	0x1A, 0x2A, 0x0A, 0x32, 0x12, 0x22, 0x42, 0x02, 0x7C, 0x3C, 0x5C, 0x1C, 0x6C, 0x2C, 0x4C, 0x0C,
	0x74, 0x34, 0x54, 0x14, 0x64, 0x24, 0x44, 0x04, 0x78, 0x38, 0x58, 0x18, 0x68, 0x28, 0x48, 0x08,
	0xF0, 0x70, 0xB0, 0x30, 0xD0, 0x50, 0x90, 0x10, 0xE0, 0x60, 0xA0, 0x20, 0xC0, 0x40, 0x80, 0x00,
};

// Storm.0x6FFE92C8
static const uint8_t sgImplodeExLenBits[16] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
};

// Storm.0x6FFE92D8
static const uint8_t sgImplodeLenBits[16] =
{
	0x03, 0x02, 0x03, 0x03, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x07, 0x07,
};

// Storm.0x6FFE92E8
static const uint8_t sgImplodeLenCode[16] =
{
	0x05, 0x03, 0x01, 0x06, 0x0A, 0x02, 0x0C, 0x14, 0x04, 0x18, 0x08, 0x30, 0x10, 0x20, 0x40, 0x00,
};

// Storm.0x6FFE92F8
static const uint8_t sgImplodeChBitsAsc[256] =
{
	0x0B, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x08, 0x07, 0x0C, 0x0C, 0x07, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x04, 0x0A, 0x08, 0x0C, 0x0A, 0x0C, 0x0A, 0x08, 0x07, 0x07, 0x08, 0x09, 0x07, 0x06, 0x07, 0x08,
	0x07, 0x06, 0x07, 0x07, 0x07, 0x07, 0x08, 0x07, 0x07, 0x08, 0x08, 0x0C, 0x0B, 0x07, 0x09, 0x0B,
	0x0C, 0x06, 0x07, 0x06, 0x06, 0x05, 0x07, 0x08, 0x08, 0x06, 0x0B, 0x09, 0x06, 0x07, 0x06, 0x06,
	0x07, 0x0B, 0x06, 0x06, 0x06, 0x07, 0x09, 0x08, 0x09, 0x09, 0x0B, 0x08, 0x0B, 0x09, 0x0C, 0x08,
	0x0C, 0x05, 0x06, 0x06, 0x06, 0x05, 0x06, 0x06, 0x06, 0x05, 0x0B, 0x07, 0x05, 0x06, 0x05, 0x05,
	0x06, 0x0A, 0x05, 0x05, 0x05, 0x05, 0x08, 0x07, 0x08, 0x08, 0x0A, 0x0B, 0x0B, 0x0C, 0x0C, 0x0C,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0D, 0x0C, 0x0D, 0x0D, 0x0D, 0x0C, 0x0D, 0x0D, 0x0D, 0x0C, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0D,
	0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
};

// Storm.0x6FFE93F8
static const uint16_t sgImplodeChCodeAsc[256] =
{
	0x0490, 0x0FE0, 0x07E0, 0x0BE0, 0x03E0, 0x0DE0, 0x05E0, 0x09E0,
	0x01E0, 0x00B8, 0x0062, 0x0EE0, 0x06E0, 0x0022, 0x0AE0, 0x02E0,
	0x0CE0, 0x04E0, 0x08E0, 0x00E0, 0x0F60, 0x0760, 0x0B60, 0x0360,
	0x0D60, 0x0560, 0x1240, 0x0960, 0x0160, 0x0E60, 0x0660, 0x0A60,
	0x000F, 0x0250, 0x0038, 0x0260, 0x0050, 0x0C60, 0x0390, 0x00D8,
	0x0042, 0x0002, 0x0058, 0x01B0, 0x007C, 0x0029, 0x003C, 0x0098,
	0x005C, 0x0009, 0x001C, 0x006C, 0x002C, 0x004C, 0x0018, 0x000C,
	0x0074, 0x00E8, 0x0068, 0x0460, 0x0090, 0x0034, 0x00B0, 0x0710,
	0x0860, 0x0031, 0x0054, 0x0011, 0x0021, 0x0017, 0x0014, 0x00A8,
	0x0028, 0x0001, 0x0310, 0x0130, 0x003E, 0x0064, 0x001E, 0x002E,
	0x0024, 0x0510, 0x000E, 0x0036, 0x0016, 0x0044, 0x0030, 0x00C8,
	0x01D0, 0x00D0, 0x0110, 0x0048, 0x0610, 0x0150, 0x0060, 0x0088,
	0x0FA0, 0x0007, 0x0026, 0x0006, 0x003A, 0x001B, 0x001A, 0x002A,
	0x000A, 0x000B, 0x0210, 0x0004, 0x0013, 0x0032, 0x0003, 0x001D,
	0x0012, 0x0190, 0x000D, 0x0015, 0x0005, 0x0019, 0x0008, 0x0078,
	0x00F0, 0x0070, 0x0290, 0x0410, 0x0010, 0x07A0, 0x0BA0, 0x03A0,
	0x0240, 0x1C40, 0x0C40, 0x1440, 0x0440, 0x1840, 0x0840, 0x1040,
	0x0040, 0x1F80, 0x0F80, 0x1780, 0x0780, 0x1B80, 0x0B80, 0x1380,
	0x0380, 0x1D80, 0x0D80, 0x1580, 0x0580, 0x1980, 0x0980, 0x1180,
	0x0180, 0x1E80, 0x0E80, 0x1680, 0x0680, 0x1A80, 0x0A80, 0x1280,
	0x0280, 0x1C80, 0x0C80, 0x1480, 0x0480, 0x1880, 0x0880, 0x1080,
	0x0080, 0x1F00, 0x0F00, 0x1700, 0x0700, 0x1B00, 0x0B00, 0x1300,
	0x0DA0, 0x05A0, 0x09A0, 0x01A0, 0x0EA0, 0x06A0, 0x0AA0, 0x02A0,
	0x0CA0, 0x04A0, 0x08A0, 0x00A0, 0x0F20, 0x0720, 0x0B20, 0x0320,
	0x0D20, 0x0520, 0x0920, 0x0120, 0x0E20, 0x0620, 0x0A20, 0x0220,
	0x0C20, 0x0420, 0x0820, 0x0020, 0x0FC0, 0x07C0, 0x0BC0, 0x03C0,
	0x0DC0, 0x05C0, 0x09C0, 0x01C0, 0x0EC0, 0x06C0, 0x0AC0, 0x02C0,
	0x0CC0, 0x04C0, 0x08C0, 0x00C0, 0x0F40, 0x0740, 0x0B40, 0x0340,
	0x0300, 0x0D40, 0x1D00, 0x0D00, 0x1500, 0x0540, 0x0500, 0x1900,
	0x0900, 0x0940, 0x1100, 0x0100, 0x1E00, 0x0E00, 0x0140, 0x1600,
	0x0600, 0x1A00, 0x0E40, 0x0640, 0x0A40, 0x0A00, 0x1200, 0x0200,
	0x1C00, 0x0C00, 0x1400, 0x0400, 0x1800, 0x0800, 0x1000, 0x0000,
};

#pragma pack(push, 4)
struct TCmpStruct
{
	uint32_t nDistance;                 // 0000 Backward distance of the found repetition, minus one
	uint32_t nOutBytes;                 // 0004 Bytes available in szOutBuffer
	uint32_t nOutBits;                  // 0008 Bits available in the last byte of szOutBuffer
	uint32_t nDictSizeBits;             // 000C 4, 5 or 6 for 0x400, 0x800 or 0x1000
	uint32_t nDictSizeMask;             // 0010 0x0F, 0x1F or 0x3F
	uint32_t nType;                     // 0014 PKWARE_CMP_BINARY or PKWARE_CMP_ASCII
	uint32_t nDictSizeBytes;            // 0018
	uint8_t pDistBits[0x40];            // 001C
	uint8_t pDistCodes[0x40];           // 005C
	uint8_t pChBits[0x306];             // 009C Bit length of each literal (0x000-0x0FF: bytes, 0x100-0x305: repetitions)
	uint16_t pChCodes[0x306];           // 03A2 Code of each literal
	uint16_t nUnused09AE;               // 09AE
	void* pParam;                       // 09B0
	PKWAREREADBUF pfnReadBuf;           // 09B4
	PKWAREWRITEBUF pfnWriteBuf;         // 09B8
	uint16_t pPrefixTable[0x204];       // 09BC
	uint32_t nUnused0DC4;               // 0DC4
	uint16_t pPairHashToIndex[0x900];   // 0DC8 Index of the first position of each byte pair hash in pPairHashOffsets
	uint16_t nPairHashToIndexEnd;       // 1FC8
	uint8_t szOutBuffer[0x802];         // 1FCA
	uint8_t pWorkBuffer[0x2204];        // 27CC Dictionary followed by the data to compress
	uint16_t pPairHashOffsets[0x2204];  // 49D0 Offsets in pWorkBuffer, sorted by byte pair hash
};
#pragma pack(pop)

static_assert(offsetof(TCmpStruct, pParam) == 0x09B0, "Size mismatch");
static_assert(offsetof(TCmpStruct, pPairHashOffsets) == 0x49D0, "Size mismatch");
static_assert(sizeof(TCmpStruct) == PKWARE_IMPLODE_BUFFER_SIZE, "Size mismatch");

static inline uint32_t PKWareBytePairHash(const uint8_t* pBuffer)
{
	return pBuffer[0] * 4 + pBuffer[1] * 5;
}

// Storm.0x6FFDFD40
static void PKWareMemSet(void* pDest, uint8_t nValue, uint32_t nSize)
{
	memset(pDest, nValue, nSize);
}

// Storm.0x6FFE0570
static void PKWareMemCopy(void* pDest, const void* pSource, uint32_t nSize)
{
	// Copies forward, the regions may overlap
	uint8_t* pDest8 = (uint8_t*)pDest;
	const uint8_t* pSource8 = (const uint8_t*)pSource;
	for (uint32_t i = 0; i < nSize; ++i)
	{
		pDest8[i] = pSource8[i];
	}
}

// Storm.0x6FFDFDB0
static void PKWareFlushBuffer(TCmpStruct* pWork)
{
	uint32_t nSize = PKWARE_OUT_BUFFER_SIZE;
	pWork->pfnWriteBuf((char*)pWork->szOutBuffer, &nSize, pWork->pParam);

	const uint8_t nSavedFirst = pWork->szOutBuffer[PKWARE_OUT_BUFFER_SIZE];
	const uint8_t nSavedLast = pWork->szOutBuffer[pWork->nOutBytes];
	pWork->nOutBytes -= PKWARE_OUT_BUFFER_SIZE;
	PKWareMemSet(pWork->szOutBuffer, 0, sizeof(pWork->szOutBuffer));

	if (pWork->nOutBytes)
	{
		pWork->szOutBuffer[0] = nSavedFirst;
	}
	if (pWork->nOutBits)
	{
		pWork->szOutBuffer[pWork->nOutBytes] = nSavedLast;
	}
}

// Storm.0x6FFDFCB0
static void PKWareOutputBits(TCmpStruct* pWork, uint32_t nBits, uint32_t nValue)
{
	if (nBits > 8)
	{
		PKWareOutputBits(pWork, 8, nValue);
		nValue >>= 8;
		nBits -= 8;
	}

	const uint32_t nOutBits = pWork->nOutBits;
	pWork->szOutBuffer[pWork->nOutBytes] |= (uint8_t)(nValue << nOutBits);
	pWork->nOutBits += nBits;
	if (pWork->nOutBits > 8)
	{
		++pWork->nOutBytes;
		pWork->szOutBuffer[pWork->nOutBytes] = (uint8_t)(nValue >> (8 - nOutBits));
		pWork->nOutBits &= 7;
	}
	else
	{
		pWork->nOutBits &= 7;
		if (!pWork->nOutBits)
		{
			++pWork->nOutBytes;
		}
	}

	if (pWork->nOutBytes >= PKWARE_OUT_BUFFER_SIZE)
	{
		PKWareFlushBuffer(pWork);
	}
}

// Storm.0x6FFDFE30
// Sorts the positions of the buffer by byte pair hash
static void PKWareSortBuffer(TCmpStruct* pWork, uint8_t* pBegin, uint8_t* pEnd)
{
	PKWareMemSet(pWork->pPairHashToIndex, 0, sizeof(pWork->pPairHashToIndex));

	// Count the occurrences of each pair hash
	for (uint8_t* pCurrent = pBegin; pCurrent < pEnd; ++pCurrent)
	{
		++pWork->pPairHashToIndex[PKWareBytePairHash(pCurrent)];
	}

	// Convert to the number of hashes lower or equal
	uint16_t nTotal = 0;
	for (uint16_t* pIndex = pWork->pPairHashToIndex; pIndex < &pWork->nPairHashToIndexEnd; ++pIndex)
	{
		nTotal += *pIndex;
		*pIndex = nTotal;
	}

	// Store the offsets, so that each element points to the first occurrence of the hash
	for (--pEnd; pEnd >= pBegin; --pEnd)
	{
		const uint32_t nHash = PKWareBytePairHash(pEnd);
		--pWork->pPairHashToIndex[nHash];
		pWork->pPairHashOffsets[pWork->pPairHashToIndex[nHash]] = (uint16_t)(pEnd - pWork->pWorkBuffer);
	}
}

// Storm.0x6FFDF970
// Finds the longest (and most recent) repetition of the data at pInput
static uint32_t PKWareFindRepetition(TCmpStruct* pWork, uint8_t* pInput)
{
	uint32_t nRepLength = 1;

	uint16_t* pHashToIndex = &pWork->pPairHashToIndex[PKWareBytePairHash(pInput)];
	const uint32_t nMinOffset = (uint32_t)(pInput - pWork->pWorkBuffer) - pWork->nDictSizeBytes + 1;
	uint32_t nIndex = *pHashToIndex;
	if (pWork->pPairHashOffsets[nIndex] < nMinOffset)
	{
		while (pWork->pPairHashOffsets[nIndex] < nMinOffset)
		{
			++nIndex;
		}
		*pHashToIndex = (uint16_t)nIndex;
	}

	uint8_t* pLimit = pInput - 1;
	uint8_t* pPrevious = pWork->pWorkBuffer + pWork->pPairHashOffsets[nIndex];
	if (pPrevious >= pLimit)
	{
		return 0;
	}

	uint32_t nEqualBytes = 0;
	while (true)
	{
		if (pPrevious[nRepLength - 1] == pInput[nRepLength - 1] && *pPrevious == *pInput)
		{
			uint8_t* pPrev = pPrevious + 1;
			uint8_t* pCurrent = pInput + 1;
			nEqualBytes = 2;
			while (true)
			{
				++pPrev;
				++pCurrent;
				if (*pPrev != *pCurrent)
				{
					break;
				}
				if (++nEqualBytes >= PKWARE_MAX_REP_LENGTH)
				{
					break;
				}
			}

			if (nEqualBytes >= nRepLength)
			{
				pWork->nDistance = (uint32_t)(pInput - pPrev + nEqualBytes - 1);
				nRepLength = nEqualBytes;
				if (nEqualBytes > 10)
				{
					break;
				}
			}
		}

		++nIndex;
		pPrevious = pWork->pWorkBuffer + pWork->pPairHashOffsets[nIndex];
		if (pPrevious >= pLimit)
		{
			return nRepLength >= 2 ? nRepLength : 0;
		}
	}

	if (nEqualBytes == PKWARE_MAX_REP_LENGTH)
	{
		--pWork->nDistance;
		return nEqualBytes;
	}

	if (pWork->pWorkBuffer + pWork->pPairHashOffsets[nIndex + 1] >= pLimit)
	{
		return nRepLength;
	}

	// Look for a longer repetition at a more recent position, using a prefix table of the found repetition
	uint16_t nPrefix = 0;
	int16_t nPrefixPos = 1;
	pWork->pPrefixTable[0] = 0xFFFF;
	pWork->pPrefixTable[1] = 0;
	while (nPrefixPos < (int32_t)nRepLength)
	{
		if (pInput[nPrefixPos] != pInput[(int16_t)nPrefix])
		{
			nPrefix = pWork->pPrefixTable[(int16_t)nPrefix];
			if (nPrefix != 0xFFFF)
			{
				continue;
			}
		}
		++nPrefixPos;
		++nPrefix;
		pWork->pPrefixTable[nPrefixPos] = nPrefix;
	}

	int32_t nMatched = nRepLength;
	uint8_t* pRepEnd = pWork->pWorkBuffer + pWork->pPairHashOffsets[nIndex] + nRepLength;
	while (true)
	{
		nMatched = (int16_t)pWork->pPrefixTable[nMatched];
		if (nMatched == -1)
		{
			nMatched = 0;
		}

		// Skip the repetitions that do not reach the end of the previous one
		do
		{
			++nIndex;
			pPrevious = pWork->pWorkBuffer + pWork->pPairHashOffsets[nIndex];
			if (pPrevious >= pLimit)
			{
				return nRepLength;
			}
		}
		while (pPrevious + nMatched < pRepEnd);

		const uint8_t nPreLastByte = pInput[nRepLength - 2];
		if (pPrevious[nRepLength - 2] == nPreLastByte)
		{
			if (pPrevious + nMatched != pRepEnd)
			{
				nMatched = 0;
				pRepEnd = pPrevious;
			}
		}
		else
		{
			do
			{
				++nIndex;
				pPrevious = pWork->pWorkBuffer + pWork->pPairHashOffsets[nIndex];
				if (pPrevious >= pLimit)
				{
					return nRepLength;
				}
			}
			while (pPrevious[nRepLength - 2] != nPreLastByte || *pPrevious != *pInput);

			nMatched = 2;
			pRepEnd = pPrevious + 2;
		}

		while (*pRepEnd == pInput[nMatched])
		{
			if (++nMatched >= PKWARE_MAX_REP_LENGTH)
			{
				break;
			}
			++pRepEnd;
		}

		if (nMatched < (int32_t)nRepLength)
		{
			continue;
		}

		pWork->nDistance = (uint32_t)(pInput - pPrevious - 1);
		if (nMatched <= (int32_t)nRepLength)
		{
			continue;
		}

		nRepLength = nMatched;
		if (nMatched == PKWARE_MAX_REP_LENGTH)
		{
			return nRepLength;
		}

		while (nPrefixPos < (int32_t)nRepLength)
		{
			if (pInput[nPrefixPos] != pInput[(int16_t)nPrefix])
			{
				nPrefix = pWork->pPrefixTable[(int16_t)nPrefix];
				if (nPrefix != 0xFFFF)
				{
					continue;
				}
			}
			++nPrefixPos;
			++nPrefix;
			pWork->pPrefixTable[nPrefixPos] = nPrefix;
		}
	}
}

static void PKWareOutputLiteral(TCmpStruct* pWork, uint32_t nLiteral)
{
	PKWareOutputBits(pWork, pWork->pChBits[nLiteral], pWork->pChCodes[nLiteral]);
}

// Storm.0x6FFDF5F0
static void PKWareWriteCompressedData(TCmpStruct* pWork)
{
	uint8_t* pInput = pWork->pWorkBuffer + pWork->nDictSizeBytes + PKWARE_MAX_REP_LENGTH;
	bool bInputEnded = false;
	uint32_t nPhase = 0;

	pWork->szOutBuffer[0] = (uint8_t)pWork->nType;
	pWork->szOutBuffer[1] = (uint8_t)pWork->nDictSizeBits;
	pWork->nOutBytes = 2;
	PKWareMemSet(&pWork->szOutBuffer[2], 0, PKWARE_OUT_BUFFER_SIZE);
	pWork->nOutBits = 0;

	do
	{
		// Load up to 0x1000 bytes
		uint32_t nTotalLoaded = 0;
		uint32_t nBytesToLoad = 0x1000;
		while (nBytesToLoad)
		{
			const uint32_t nLoaded = pWork->pfnReadBuf((char*)pWork->pWorkBuffer + pWork->nDictSizeBytes + PKWARE_MAX_REP_LENGTH + nTotalLoaded, &nBytesToLoad, pWork->pParam);
			if (!nLoaded)
			{
				if (!nTotalLoaded && !nPhase)
				{
					goto Exit;
				}
				bInputEnded = true;
				break;
			}
			nTotalLoaded += nLoaded;
			nBytesToLoad -= nLoaded;
		}

		uint8_t* pInputEnd = pWork->pWorkBuffer + pWork->nDictSizeBytes + nTotalLoaded;
		if (bInputEnded)
		{
			pInputEnd += PKWARE_MAX_REP_LENGTH;
		}

		// Sort the new data, and the dictionary built from the previous data
		switch (nPhase)
		{
		case 0:
			PKWareSortBuffer(pWork, pInput, pInputEnd + 1);
			++nPhase;
			if (pWork->nDictSizeBytes != 0x1000)
			{
				++nPhase;
			}
			break;
		case 1:
			PKWareSortBuffer(pWork, pInput - pWork->nDictSizeBytes + PKWARE_MAX_REP_LENGTH, pInputEnd + 1);
			++nPhase;
			break;
		default:
			PKWareSortBuffer(pWork, pInput - pWork->nDictSizeBytes, pInputEnd + 1);
			break;
		}

		while (pInput < pInputEnd)
		{
			uint32_t nRepLength = PKWareFindRepetition(pWork, pInput);
			while (nRepLength)
			{
				// A repetition of 2 bytes far away takes more space than the literals
				if (nRepLength == 2 && pWork->nDistance >= 0x100)
				{
					break;
				}

				if (bInputEnded && pInput + nRepLength > pInputEnd)
				{
					// Do not go beyond the end of the data
					nRepLength = (uint32_t)(pInputEnd - pInput);
					if (nRepLength < 2 || (nRepLength == 2 && pWork->nDistance >= 0x100))
					{
						break;
					}
				}
				else if (nRepLength < 8 && pInput + 1 < pInputEnd)
				{
					// Check if there is a better repetition starting at the next byte
					const uint32_t nSavedRepLength = nRepLength;
					const uint32_t nSavedDistance = pWork->nDistance;
					nRepLength = PKWareFindRepetition(pWork, pInput + 1);
					if (nSavedRepLength < nRepLength && (nSavedRepLength + 1 < nRepLength || nSavedDistance > 0x80))
					{
						PKWareOutputLiteral(pWork, *pInput);
						++pInput;
						continue;
					}

					nRepLength = nSavedRepLength;
					pWork->nDistance = nSavedDistance;
				}

				PKWareOutputLiteral(pWork, nRepLength + 0xFE);
				if (nRepLength == 2)
				{
					PKWareOutputBits(pWork, pWork->pDistBits[pWork->nDistance >> 2], pWork->pDistCodes[pWork->nDistance >> 2]);
					PKWareOutputBits(pWork, 2, pWork->nDistance & 3);
				}
				else
				{
					PKWareOutputBits(pWork, pWork->pDistBits[pWork->nDistance >> pWork->nDictSizeBits], pWork->pDistCodes[pWork->nDistance >> pWork->nDictSizeBits]);
					PKWareOutputBits(pWork, pWork->nDictSizeBits, pWork->nDictSizeMask & pWork->nDistance);
				}
				pInput += nRepLength;
				goto NextInput;
			}

			PKWareOutputLiteral(pWork, *pInput);
			++pInput;
		NextInput:;
		}

		if (!bInputEnded)
		{
			pInput -= 0x1000;
			PKWareMemCopy(pWork->pWorkBuffer, pWork->pWorkBuffer + 0x1000, pWork->nDictSizeBytes + PKWARE_MAX_REP_LENGTH);
		}
	}
	while (!bInputEnded);

Exit:
	// End of stream marker
	PKWareOutputLiteral(pWork, 0x305);
	if (pWork->nOutBits)
	{
		++pWork->nOutBytes;
	}
	pWork->pfnWriteBuf((char*)pWork->szOutBuffer, &pWork->nOutBytes, pWork->pParam);
}

uint32_t __cdecl PKWareImplode(PKWAREREADBUF pfnReadBuf, PKWAREWRITEBUF pfnWriteBuf, void* pWorkBuffer, void* pParam, uint32_t* pType, uint32_t* pDictSize)
{
	TCmpStruct* pWork = (TCmpStruct*)pWorkBuffer;
	pWork->pfnReadBuf = pfnReadBuf;
	pWork->pfnWriteBuf = pfnWriteBuf;
	pWork->nDictSizeBytes = *pDictSize;
	pWork->nType = *pType;
	pWork->pParam = pParam;
	pWork->nDictSizeBits = 4;
	pWork->nDictSizeMask = 0x0F;

	switch (*pDictSize)
	{
	case 0x1000:
		++pWork->nDictSizeBits;
		pWork->nDictSizeMask |= 0x20;
		// fallthrough
	case 0x800:
		++pWork->nDictSizeBits;
		pWork->nDictSizeMask |= 0x10;
		// fallthrough
	case 0x400:
		break;
	default:
		return PKWARE_CMP_INVALID_DICTSIZE;
	}

	uint32_t nLiteral;
	switch (*pType)
	{
	case PKWARE_CMP_BINARY:
	{
		uint16_t nCode = 0;
		for (nLiteral = 0; nLiteral < 0x100; ++nLiteral)
		{
			pWork->pChBits[nLiteral] = 9;
			pWork->pChCodes[nLiteral] = nCode;
			nCode += 2;
		}
		break;
	}
	case PKWARE_CMP_ASCII:
		for (nLiteral = 0; nLiteral < 0x100; ++nLiteral)
		{
			pWork->pChBits[nLiteral] = sgImplodeChBitsAsc[nLiteral] + 1;
			pWork->pChCodes[nLiteral] = sgImplodeChCodeAsc[nLiteral] * 2;
		}
		break;
	default:
		return PKWARE_CMP_INVALID_MODE;
	}

	// Literals of the repetition lengths
	for (uint32_t i = 0; i < 0x10; ++i)
	{
		for (uint32_t nExtra = 0; nExtra < (1u << sgImplodeExLenBits[i]); ++nExtra)
		{
			pWork->pChBits[nLiteral] = sgImplodeExLenBits[i] + sgImplodeLenBits[i] + 1;
			pWork->pChCodes[nLiteral] = (uint16_t)((nExtra << (sgImplodeLenBits[i] + 1)) | (sgImplodeLenCode[i] * 2) | 1);
			++nLiteral;
		}
	}

	PKWareMemCopy(pWork->pDistCodes, sgImplodeDistCode, sizeof(sgImplodeDistCode));
	PKWareMemCopy(pWork->pDistBits, sgImplodeDistBits, sizeof(sgImplodeDistBits));
	PKWareWriteCompressedData(pWork);
	return PKWARE_CMP_NO_ERROR;
}
