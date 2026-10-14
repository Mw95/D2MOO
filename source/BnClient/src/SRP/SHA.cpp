#include "SRP/SHA.h"

#include <Windows.h>

#include <cstring>

#include <Storm.h>


//Bnclient.0x6FF1CCF8
static const uint8_t gnSHA1PaddingStart = 0x80;
//Bnclient.0x6FF1D944
static const uint8_t gnSHA1PaddingZero = 0x00;


static uint32_t SHA1_RotateLeft(uint32_t nValue, int nBits)
{
	return (nValue << nBits) | (nValue >> (32 - nBits));
}

//Bnclient.0x6FF13F70
void __fastcall SHA1_Init(SHA1Context* pContext)
{
	pContext->pState[0] = 0x67452301;
	pContext->pState[1] = 0xEFCDAB89;
	pContext->pState[2] = 0x98BADCFE;
	pContext->pState[3] = 0x10325476;
	pContext->pState[4] = 0xC3D2E1F0;
	pContext->pCount[1] = 0;
	pContext->pCount[0] = 0;
}

//Bnclient.0x6FF13FA0
void __fastcall SHA1_Update(SHA1Context* pContext, const void* pData, uint32_t nSize)
{
	const uint8_t* pBytes = (const uint8_t*)pData;

	uint32_t nBufferedBytes = (pContext->pCount[0] >> 3) & 0x3F;
	pContext->pCount[0] += nSize << 3;
	if (pContext->pCount[0] < (nSize << 3))
	{
		++pContext->pCount[1];
	}
	pContext->pCount[1] += nSize >> 29;

	uint32_t nOffset = 0;
	if (nBufferedBytes + nSize > 63)
	{
		nOffset = 64 - nBufferedBytes;
		memcpy(&pContext->pBuffer[nBufferedBytes], pBytes, nOffset);
		SHA1_Transform(pContext, pContext->pBuffer);

		for (; nOffset + 63 < nSize; nOffset += 64)
		{
			SHA1_Transform(pContext, &pBytes[nOffset]);
		}

		nBufferedBytes = 0;
	}

	memcpy(&pContext->pBuffer[nBufferedBytes], &pBytes[nOffset], nSize - nOffset);
}

//Bnclient.0x6FF14060
void __fastcall SHA1_Transform(SHA1Context* pContext, const uint8_t* pBlock)
{
	uint32_t W[80];
	for (int i = 0; i < 16; ++i)
	{
		W[i] = ((uint32_t)pBlock[4 * i] << 24) | ((uint32_t)pBlock[4 * i + 1] << 16) | ((uint32_t)pBlock[4 * i + 2] << 8) | pBlock[4 * i + 3];
	}

	for (int i = 16; i < 80; ++i)
	{
		W[i] = SHA1_RotateLeft(W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16], 1);
	}

	uint32_t a = pContext->pState[0];
	uint32_t b = pContext->pState[1];
	uint32_t c = pContext->pState[2];
	uint32_t d = pContext->pState[3];
	uint32_t e = pContext->pState[4];

	for (int i = 0; i < 80; ++i)
	{
		uint32_t f;
		uint32_t k;
		if (i < 20)
		{
			f = (b & c) | (~b & d);
			k = 0x5A827999;
		}
		else if (i < 40)
		{
			f = b ^ c ^ d;
			k = 0x6ED9EBA1;
		}
		else if (i < 60)
		{
			f = (b & c) | (b & d) | (c & d);
			k = 0x8F1BBCDC;
		}
		else
		{
			f = b ^ c ^ d;
			k = 0xCA62C1D6;
		}

		const uint32_t nTemp = SHA1_RotateLeft(a, 5) + f + e + k + W[i];
		e = d;
		d = c;
		c = SHA1_RotateLeft(b, 30);
		b = a;
		a = nTemp;
	}

	pContext->pState[0] += a;
	pContext->pState[1] += b;
	pContext->pState[2] += c;
	pContext->pState[3] += d;
	pContext->pState[4] += e;
}

//Bnclient.0x6FF15720
void __fastcall SHA1_Final(uint8_t* pDigest, SHA1Context* pContext)
{
	uint8_t pFinalCount[8];
	for (int i = 0; i < 8; ++i)
	{
		pFinalCount[i] = (uint8_t)(pContext->pCount[i < 4 ? 1 : 0] >> ((3 - (i & 3)) * 8));
	}

	SHA1_Update(pContext, &gnSHA1PaddingStart, 1);
	while ((pContext->pCount[0] & 0x1F8) != 0x1C0)
	{
		SHA1_Update(pContext, &gnSHA1PaddingZero, 1);
	}
	SHA1_Update(pContext, pFinalCount, sizeof(pFinalCount));

	for (int i = 0; i < 20; ++i)
	{
		pDigest[i] = (uint8_t)(pContext->pState[i >> 2] >> ((3 - (i & 3)) * 8));
	}
}

//Bnclient.0x6FF157D0
uint8_t* __fastcall SHA_Interleave(uint8_t* pOutput, const uint8_t* pInput, uint32_t nSize)
{
	while (nSize && *pInput == 0)
	{
		++pInput;
		--nSize;
	}

	if (nSize & 1)
	{
		++pInput;
		--nSize;
	}

	const uint32_t nHalfSize = nSize / 2;
	uint8_t* pBuffer = (uint8_t*)SMemAlloc(nHalfSize, __FILE__, __LINE__, 0);
	if (!pBuffer)
	{
		return nullptr;
	}

	SHA1Context tContext;
	uint8_t pDigest[20];

	for (uint32_t i = 0; i < nHalfSize; ++i)
	{
		pBuffer[i] = pInput[2 * i];
	}

	SHA1_Init(&tContext);
	SHA1_Update(&tContext, pBuffer, nHalfSize);
	SHA1_Final(pDigest, &tContext);
	for (int i = 0; i < 20; ++i)
	{
		pOutput[2 * i] = pDigest[i];
	}

	for (uint32_t i = 0; i < nHalfSize; ++i)
	{
		pBuffer[i] = pInput[2 * i + 1];
	}

	SHA1_Init(&tContext);
	SHA1_Update(&tContext, pBuffer, nHalfSize);
	SHA1_Final(pDigest, &tContext);
	for (int i = 0; i < 20; ++i)
	{
		pOutput[2 * i + 1] = pDigest[i];
	}

	SMemFree(pBuffer, __FILE__, __LINE__, 0);
	return pOutput;
}
