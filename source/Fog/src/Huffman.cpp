#include <Fog.h>

#include <cstring>

// Huffman coding used to compress network packets.
// Codes are canonical, assigned from the longest to the shortest code length.

#define HUFFMAN_SYMBOLS 256
#define HUFFMAN_MAX_CODE_LENGTH 16

// Fog.0x6FF75E68
// Code length of each byte value
static uint8_t gnHuffmanCodeLengths[HUFFMAN_SYMBOLS] =
{
	0x01, 0x04, 0x06, 0x07, 0x07, 0x06, 0x07, 0x07, 0x07, 0x08, 0x07, 0x08, 0x08, 0x07, 0x09, 0x08,
	0x08, 0x08, 0x07, 0x06, 0x06, 0x07, 0x08, 0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A, 0x08, 0x07, 0x08,
	0x08, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x0A, 0x0A, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0B,
	0x09, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x0A, 0x0A, 0x0A, 0x0A,
	0x09, 0x0A, 0x0A, 0x09, 0x0A, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x09, 0x0A, 0x0B,
	0x09, 0x08, 0x09, 0x0A, 0x0B, 0x09, 0x09, 0x0A, 0x09, 0x0A, 0x0A, 0x0A, 0x0B, 0x0A, 0x0A, 0x0A,
	0x0A, 0x0A, 0x09, 0x09, 0x09, 0x0A, 0x0A, 0x07, 0x07, 0x07, 0x0A, 0x09, 0x08, 0x07, 0x0A, 0x0A,
	0x0A, 0x0B, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0B, 0x0A, 0x0A, 0x0A, 0x0A,
	0x07, 0x0A, 0x0A, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A,
	0x09, 0x0B, 0x0B, 0x0A, 0x0B, 0x09, 0x09, 0x09, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
	0x0A, 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
	0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
	0x0A, 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0B,
	0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
	0x0A, 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
	0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x06,
};

// Fog.0x6FF9FCF8
// Code of each byte value. Note: codes are stored on 8 bits, the upper bits of the longest codes are lost.
static uint8_t gnHuffmanCodes[HUFFMAN_SYMBOLS];

// Fog.0x6FF9F5F8
// Decoding table indexed by the next 8 bits of the stream. Each entry points to a node in gnHuffmanDecodeNodes:
// node[0] is the number of extra bits to read, node[1 + extra bits value] is the decoded byte.
static uint8_t* gpHuffmanDecodeTable[256];
// Fog.0x6FF9F9F8
static uint8_t gnHuffmanDecodeNodes[0x300];

// Fog.0x6FF9EDF8
static uint64_t gnHuffmanSymbolsStatistics[HUFFMAN_SYMBOLS];
// Fog.0x6FF9FDF8
static uint64_t gnHuffmanUncompressedBytes;
// Fog.0x6FF9FE00
static uint64_t gnHuffmanCompressedBytes;
// Fog.0x6FF9FE08
static uint64_t gnHuffmanHeaderBytes;

// 1.10f: 0x6FF5CC40 (#10218)
// Resets the statistics and initializes the coding tables with the default code lengths.
int __fastcall FOG_10218()
{
	memset(gnHuffmanSymbolsStatistics, 0, sizeof(gnHuffmanSymbolsStatistics));
	gnHuffmanUncompressedBytes = 0;
	gnHuffmanCompressedBytes = 0;
	gnHuffmanHeaderBytes = 0;
	return FOG_10219(gnHuffmanCodeLengths);
}

// 1.10f: 0x6FF5C9E0 (#10219)
// Initializes the coding tables from the code length of each byte value. Returns FALSE if a code length is not in [1, 15].
int __fastcall FOG_10219(uint8_t* pCodeLengths)
{
	int nCountPerLength[HUFFMAN_MAX_CODE_LENGTH] = {};
	for (int i = 0; i < HUFFMAN_SYMBOLS; ++i)
	{
		if (pCodeLengths[i] == 0 || pCodeLengths[i] >= HUFFMAN_MAX_CODE_LENGTH)
		{
			return FALSE;
		}
		++nCountPerLength[pCodeLengths[i]];
	}

	// Compute the offset of each length, sorting from the longest to the shortest code length.
	// nCountPerLength[0] is used as the running total.
	for (int nLength = HUFFMAN_MAX_CODE_LENGTH - 1; nLength > 0; --nLength)
	{
		const int nCount = nCountPerLength[nLength];
		nCountPerLength[nLength] = nCountPerLength[0];
		nCountPerLength[0] += nCount;
	}

	uint8_t nSortedSymbols[HUFFMAN_SYMBOLS];
	for (int i = 0; i < HUFFMAN_SYMBOLS; ++i)
	{
		nSortedSymbols[nCountPerLength[pCodeLengths[i]]++] = (uint8_t)i;
	}

	uint8_t nSortedLengths[HUFFMAN_SYMBOLS];
	for (int i = 0; i < HUFFMAN_SYMBOLS; ++i)
	{
		nSortedLengths[i] = pCodeLengths[nSortedSymbols[i]];
	}
	memmove(gnHuffmanCodeLengths, pCodeLengths, sizeof(gnHuffmanCodeLengths));

	gnHuffmanCodes[nSortedSymbols[0]] = 0;
	for (int i = 0; i + 1 < HUFFMAN_SYMBOLS; ++i)
	{
		const int nNextCode = gnHuffmanCodes[nSortedSymbols[i]] + 1;
		gnHuffmanCodes[nSortedSymbols[i + 1]] = (uint8_t)(nNextCode >> (nSortedLengths[i] - nSortedLengths[i + 1]));
	}

	// Build the decoding table, from the shortest to the longest code
	uint8_t* pNode = gnHuffmanDecodeNodes;
	for (int i = HUFFMAN_SYMBOLS - 1; i >= 0; --i)
	{
		const int nLength = nSortedLengths[i];
		const uint32_t nCode = gnHuffmanCodes[nSortedSymbols[i]];
		if (nLength <= 8)
		{
			const uint32_t nFirstEntry = nCode << (8 - nLength);
			const int nEntries = 1 << (8 - nLength);
			pNode[0] = 0;
			pNode[1] = nSortedSymbols[i];
			for (int j = 0; j < nEntries; ++j)
			{
				gpHuffmanDecodeTable[nFirstEntry + j] = pNode;
			}
			pNode += 2;
		}
		else
		{
			const uint32_t nEntry = nCode >> (nLength - 8);
			const int nExtraEntries = 1 << (nLength - 8);
			// Only the first code of the 8 bits prefix builds the node
			if (nCode & (nExtraEntries - 1))
			{
				continue;
			}

			gpHuffmanDecodeTable[nEntry] = pNode;
			*pNode++ = (uint8_t)(nLength - 8);
			int nFilledEntries = 0;
			const uint8_t* pSymbol = &nSortedSymbols[i];
			while (nFilledEntries < nExtraEntries)
			{
				// Note: the length is looked up with the number of filled entries instead of the symbol index. Kept as is for compatibility.
				const int nRepeat = 1 << (nLength - nSortedLengths[i + nFilledEntries]);
				pNode += nRepeat;
				for (int j = 0; j < nRepeat; ++j)
				{
					++nFilledEntries;
					gpHuffmanDecodeTable[nEntry][nFilledEntries] = *pSymbol;
				}
				++pSymbol;
			}
		}
	}

	return TRUE;
}

// 1.10f: 0x6FF5CC90 (#10222)
// Updates the compression statistics with the packet, returns the size it would have once compressed (including its header).
int __fastcall FOG_10222(const uint8_t* pData, int nSize)
{
	uint32_t nBits = 0;
	for (int i = 0; i < nSize; ++i)
	{
		++gnHuffmanSymbolsStatistics[pData[i]];
		nBits += gnHuffmanCodeLengths[pData[i]];
	}

	uint32_t nCompressedSize = (nBits + 7) / 8 + 1;
	uint32_t nHeaderSize = 1;
	if (nCompressedSize >= 0xF0)
	{
		++nCompressedSize;
		nHeaderSize = 2;
	}

	gnHuffmanUncompressedBytes += (uint32_t)nSize;
	gnHuffmanCompressedBytes += nCompressedSize;
	gnHuffmanHeaderBytes += nHeaderSize;
	return nCompressedSize;
}

// 1.10f: 0x6FF5CD50 (#10223)
// Returns the compressed size, or 0 if pDest is too small.
int __fastcall FOG_10223(uint8_t* pDest, int nDestSize, const uint8_t* pSrc, int nSrcSize)
{
	uint8_t* pOutput = pDest;
	uint8_t nCurrentByte = 0;
	int nFreeBits = 8;
	while (nSrcSize)
	{
		--nSrcSize;
		const uint8_t nSymbol = *pSrc++;
		int nRemainingBits = gnHuffmanCodeLengths[nSymbol];
		const uint32_t nCode = gnHuffmanCodes[nSymbol];
		while (nRemainingBits >= nFreeBits)
		{
			nRemainingBits -= nFreeBits;
			if (nDestSize-- == 0)
			{
				return 0;
			}
			*pOutput++ = nCurrentByte | (uint8_t)(nCode >> nRemainingBits);
			nCurrentByte = 0;
			nFreeBits = 8;
		}

		if (nRemainingBits)
		{
			nFreeBits -= nRemainingBits;
			nCurrentByte |= (uint8_t)(nCode << nFreeBits);
		}
	}

	if (nFreeBits < 8)
	{
		if (nDestSize == 0)
		{
			return 0;
		}
		*pOutput++ = nCurrentByte;
	}

	return pOutput - pDest;
}

// 1.10f: 0x6FF5CE00 (#10224)
// Returns the decompressed size, or 0 if pDest is too small.
int __fastcall FOG_10224(char* pDest, int nDestSize, uint8_t* pSrc, int nSrcSize)
{
	char* pOutput = pDest;
	uint32_t nBitBuffer = 0;
	int nEmptyBits = 32;
	while (true)
	{
		while (nEmptyBits >= 8 && nSrcSize > 0)
		{
			nEmptyBits -= 8;
			nBitBuffer |= (uint32_t)*pSrc++ << nEmptyBits;
			--nSrcSize;
		}

		const uint8_t* pNode = gpHuffmanDecodeTable[nBitBuffer >> 24];
		const int nExtraBits = pNode[0];
		const uint32_t nIndex = (nBitBuffer >> (24 - nExtraBits)) & ((1u << nExtraBits) - 1);
		const uint8_t nSymbol = pNode[1 + nIndex];
		const int nCodeLength = gnHuffmanCodeLengths[nSymbol];
		nEmptyBits += nCodeLength;
		if (nEmptyBits > 32)
		{
			return pOutput - pDest;
		}

		if (nDestSize-- == 0)
		{
			return 0;
		}
		*pOutput++ = (char)nSymbol;
		nBitBuffer <<= nCodeLength;
	}
}
