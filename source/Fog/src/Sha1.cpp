#include <Sha1.h>

#include <cstring>

static uint32_t SHA1_RotateLeft(uint32_t nValue, int nBits)
{
	return (nValue << nBits) | (nValue >> (32 - nBits));
}

// Shared by the standard and broken SHA-1, only the message schedule differs
static void SHA1_Compress(uint32_t pState[5], const uint32_t pSchedule[80])
{
	uint32_t a = pState[0];
	uint32_t b = pState[1];
	uint32_t c = pState[2];
	uint32_t d = pState[3];
	uint32_t e = pState[4];
	for (int i = 0; i < 80; ++i)
	{
		uint32_t f;
		uint32_t k;
		if (i < 20)
		{
			f = (~b & d) | (c & b);
			k = 0x5A827999;
		}
		else if (i < 40)
		{
			f = b ^ c ^ d;
			k = 0x6ED9EBA1;
		}
		else if (i < 60)
		{
			f = ((c | b) & d) | (c & b);
			k = 0x8F1BBCDC;
		}
		else
		{
			f = b ^ c ^ d;
			k = 0xCA62C1D6;
		}

		const uint32_t nTemp = SHA1_RotateLeft(a, 5) + f + e + pSchedule[i] + k;
		e = d;
		d = c;
		c = SHA1_RotateLeft(b, 30);
		b = a;
		a = nTemp;
	}

	pState[0] += a;
	pState[1] += b;
	pState[2] += c;
	pState[3] += d;
	pState[4] += e;
}

// 1.10f: 0x6FF63B40 (#10189)
void __fastcall FOG_XSha1(uint32_t* pDigest, const void* pData, uint32_t nSize)
{
	uint32_t pState[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
	const uint8_t* pBytes = (const uint8_t*)pData;
	for (uint32_t nOffset = 0; nOffset < nSize; nOffset += 64)
	{
		uint32_t pSchedule[80] = {};
		const uint32_t nBlockSize = nSize - nOffset > 64 ? 64 : nSize - nOffset;
		memcpy(pSchedule, &pBytes[nOffset], nBlockSize);
		for (int i = 16; i < 80; ++i)
		{
			// Note: arguments of the rotation are swapped compared to SHA-1
			pSchedule[i] = 1u << ((pSchedule[i - 16] ^ pSchedule[i - 8] ^ pSchedule[i - 14] ^ pSchedule[i - 3]) & 0x1F);
		}
		SHA1_Compress(pState, pSchedule);
	}
	memcpy(pDigest, pState, sizeof(pState));
}

// 1.10f: 0x6FF63DF0
static void SHA1_Transform(uint32_t pState[5], const uint8_t* pBlock)
{
	uint32_t pSchedule[80];
	for (int i = 0; i < 16; ++i)
	{
		pSchedule[i] = (pBlock[4 * i] << 24) | (pBlock[4 * i + 1] << 16) | (pBlock[4 * i + 2] << 8) | pBlock[4 * i + 3];
	}
	for (int i = 16; i < 80; ++i)
	{
		pSchedule[i] = SHA1_RotateLeft(pSchedule[i - 3] ^ pSchedule[i - 8] ^ pSchedule[i - 14] ^ pSchedule[i - 16], 1);
	}
	SHA1_Compress(pState, pSchedule);
}

// 1.10f: 0x6FF64270 (#10248)
void __fastcall FOG_Sha1Initialize(FOGSha1Context* pContext)
{
	pContext->nBitCount[0] = 0;
	pContext->nBitCount[1] = 0;
	pContext->nState[0] = 0x67452301;
	pContext->nState[1] = 0xEFCDAB89;
	pContext->nState[2] = 0x98BADCFE;
	pContext->nState[3] = 0x10325476;
	pContext->nState[4] = 0xC3D2E1F0;
}

// 1.10f: 0x6FF642B0 (#10249)
void __fastcall FOG_Sha1Update(FOGSha1Context* pContext, int nUnused, const void* pData, uint32_t nSize)
{
	const uint8_t* pBytes = (const uint8_t*)pData;
	uint32_t nBufferUsed = (pContext->nBitCount[0] >> 3) & 0x3F;
	const uint64_t nBitCount = (((uint64_t)pContext->nBitCount[1] << 32) | pContext->nBitCount[0]) + (uint64_t)nSize * 8;
	pContext->nBitCount[0] = (uint32_t)nBitCount;
	pContext->nBitCount[1] = (uint32_t)(nBitCount >> 32);

	if (nBufferUsed && nBufferUsed + nSize >= 64)
	{
		const uint32_t nMissing = 64 - nBufferUsed;
		memcpy(&pContext->pBuffer[nBufferUsed], pBytes, nMissing);
		SHA1_Transform(pContext->nState, pContext->pBuffer);
		pBytes += nMissing;
		nSize -= nMissing;
		nBufferUsed = 0;
	}
	else if (nBufferUsed)
	{
		memcpy(&pContext->pBuffer[nBufferUsed], pBytes, nSize);
		return;
	}

	while (nSize >= 64)
	{
		SHA1_Transform(pContext->nState, pBytes);
		pBytes += 64;
		nSize -= 64;
	}

	memcpy(pContext->pBuffer, pBytes, nSize);
}

// 1.10f: 0x6FF64350 (#10250)
void __fastcall FOG_Sha1Finalize(FOGSha1Context* pContext, int nUnused, uint8_t* pDigest)
{
	static const uint8_t pPadding[64] = { 0x80 };

	uint8_t pLength[8];
	uint32_t nLow = pContext->nBitCount[0];
	uint32_t nHigh = pContext->nBitCount[1];
	for (int i = 7; i >= 0; --i)
	{
		pLength[i] = (uint8_t)nLow;
		nLow = (nLow >> 8) | (nHigh << 24);
		nHigh >>= 8;
	}

	const uint32_t nPaddingSize = ((0xFFFFFFF7 - (pContext->nBitCount[0] >> 3)) & 0x3F) + 1;
	FOG_Sha1Update(pContext, 0, pPadding, nPaddingSize);
	FOG_Sha1Update(pContext, 0, pLength, sizeof(pLength));

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			pDigest[4 * i + j] = (uint8_t)(pContext->nState[i] >> (24 - 8 * j));
		}
	}
}
