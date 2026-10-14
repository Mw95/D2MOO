#include "Grid.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <Fog.h>
#include <Storm.h>

#include "BnConnect.h"


uint32_t gnGridCDKeyXPSize;
uint32_t gnGridOwnerSize;
char* sgpCDKeyXP;
char* sgpCDKey;
uint32_t gnGridCDKeySize;
char* sgpOwner;
uint16_t gaGridKeys[GRID_SLOTS][GRID_IDEA_KEYLEN];
GridHashContext gaGridHashes[GRID_SLOTS];

BOOL gbGridFirstLoad = TRUE;


//Bnclient.0x6FF0B820
uint16_t __fastcall GRID_IDEAMulInv(uint16_t x)
{
	if (x <= 1)
	{
		return x;
	}

	uint32_t t1 = 0x10001 / x;
	uint32_t y = 0x10001 % x;
	if (y == 1)
	{
		return (uint16_t)(1 - t1);
	}

	uint32_t t0 = 1;
	uint32_t nValue = x;
	do
	{
		uint32_t q = nValue / y;
		nValue = nValue % y;
		t0 += q * t1;
		if (nValue == 1)
		{
			return (uint16_t)t0;
		}

		q = y / nValue;
		y = y % nValue;
		t1 += q * t0;
	}
	while (y != 1);

	return (uint16_t)(1 - t1);
}

//Bnclient.0x6FF0B880
void __fastcall GRID_IDEAInvertKey(const uint16_t* pEncryptionKey, uint16_t* pDecryptionKey)
{
	uint16_t aTemp[GRID_IDEA_KEYLEN];
	uint16_t* p = &aTemp[GRID_IDEA_KEYLEN];

	uint16_t t1 = GRID_IDEAMulInv(*pEncryptionKey++);
	uint16_t t2 = -*pEncryptionKey++;
	uint16_t t3 = -*pEncryptionKey++;
	*--p = GRID_IDEAMulInv(*pEncryptionKey++);
	*--p = t3;
	*--p = t2;
	*--p = t1;

	for (int j = 1; j < GRID_IDEA_ROUNDS; ++j)
	{
		t1 = *pEncryptionKey++;
		*--p = *pEncryptionKey++;
		*--p = t1;

		t1 = GRID_IDEAMulInv(*pEncryptionKey++);
		t2 = -*pEncryptionKey++;
		t3 = -*pEncryptionKey++;
		*--p = GRID_IDEAMulInv(*pEncryptionKey++);
		*--p = t2;
		*--p = t3;
		*--p = t1;
	}

	t1 = *pEncryptionKey++;
	*--p = *pEncryptionKey++;
	*--p = t1;

	t1 = GRID_IDEAMulInv(*pEncryptionKey++);
	t2 = -*pEncryptionKey++;
	t3 = -*pEncryptionKey++;
	*--p = GRID_IDEAMulInv(*pEncryptionKey++);
	*--p = t3;
	*--p = t2;
	*--p = t1;

	for (int j = 0; j < GRID_IDEA_KEYLEN; ++j)
	{
		*pDecryptionKey++ = aTemp[j];
		aTemp[j] = 0;
	}
}

static uint16_t GRID_IDEAMul(uint16_t a, uint16_t b)
{
	if (!a)
	{
		return 1 - b;
	}

	if (!b)
	{
		return 1 - a;
	}

	const uint32_t p = (uint32_t)a * b;
	const uint16_t nLow = (uint16_t)p;
	const uint16_t nHigh = (uint16_t)(p >> 16);
	return nLow - nHigh + (nLow < nHigh);
}

//Bnclient.0x6FF0BBF0
void __fastcall GRID_IDEACipher(const uint16_t* pInput, uint16_t* pOutput, const uint16_t* pKey)
{
	uint16_t x1 = pInput[0];
	uint16_t x2 = pInput[1];
	uint16_t x3 = pInput[2];
	uint16_t x4 = pInput[3];

	for (int r = 0; r < GRID_IDEA_ROUNDS; ++r)
	{
		x1 = GRID_IDEAMul(x1, *pKey++);
		x2 += *pKey++;
		x3 += *pKey++;
		x4 = GRID_IDEAMul(x4, *pKey++);

		uint16_t t2 = x1 ^ x3;
		t2 = GRID_IDEAMul(t2, *pKey++);
		uint16_t t1 = t2 + (x2 ^ x4);
		t1 = GRID_IDEAMul(t1, *pKey++);
		t2 = t1 + t2;

		x1 ^= t1;
		x4 ^= t2;
		t2 ^= x2;
		x2 = x3 ^ t1;
		x3 = t2;
	}

	pOutput[0] = GRID_IDEAMul(x1, *pKey++);
	pOutput[1] = x3 + *pKey++;
	pOutput[2] = x2 + *pKey++;
	pOutput[3] = GRID_IDEAMul(x4, *pKey);
}

//Bnclient.0x6FF0BE50
void __stdcall GRID_ClearKeys()
{
	memset(gaGridKeys, 0x00, sizeof(gaGridKeys));
}

//Bnclient.0x6FF0BE70
void __fastcall GRID_CryptBlock(int nSlot, const uint8_t* pInput, uint8_t* pOutput)
{
	GRID_IDEACipher((const uint16_t*)pInput, (uint16_t*)pOutput, gaGridKeys[nSlot]);
}

static void GRID_IDEAExpandKey(const uint8_t* pUserKey, uint16_t* pKey)
{
	memcpy(pKey, pUserKey, 8 * sizeof(uint16_t));

	uint16_t* Z = pKey;
	for (int i = 0, j = 8; j < GRID_IDEA_KEYLEN; ++j)
	{
		++i;
		Z[i + 7] = (uint16_t)((Z[i & 7] << 9) | (Z[(i + 1) & 7] >> 7));
		Z += i & 8;
		i &= 7;
	}
}

//Bnclient.0x6FF0BE90
void __fastcall GRID_SetKey(int nSlot, BOOL bEncrypt, const uint8_t* pUserKey)
{
	if (bEncrypt)
	{
		GRID_IDEAExpandKey(pUserKey, gaGridKeys[nSlot]);
		return;
	}

	uint16_t aEncryptionKey[GRID_IDEA_KEYLEN];
	GRID_IDEAExpandKey(pUserKey, aEncryptionKey);
	GRID_IDEAInvertKey(aEncryptionKey, gaGridKeys[nSlot]);
}

static uint32_t GRID_RotateLeft(uint32_t nValue, int nBits)
{
	return (nValue << nBits) | (nValue >> (32 - nBits));
}

//Bnclient.0x6FF0BF70
void __fastcall GRID_XSHATransform(uint32_t* pContext)
{
	uint32_t W[80];
	memcpy(W, &pContext[5], 16 * sizeof(uint32_t));

	for (int i = 16; i < 80; ++i)
	{
		const uint32_t nShift = (W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]) & 0x1F;
		W[i] = nShift ? GRID_RotateLeft(1, nShift) : 1;
	}

	uint32_t a = pContext[0];
	uint32_t b = pContext[1];
	uint32_t c = pContext[2];
	uint32_t d = pContext[3];
	uint32_t e = pContext[4];

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
			f = d ^ c ^ b;
			k = 0x6ED9EBA1;
		}
		else if (i < 60)
		{
			f = ((c | b) & d) | (c & b);
			k = 0x8F1BBCDC;
		}
		else
		{
			f = d ^ c ^ b;
			k = 0xCA62C1D6;
		}

		const uint32_t nTemp = f + GRID_RotateLeft(a, 5) + W[i] + e + k;
		e = d;
		d = c;
		c = GRID_RotateLeft(b, 30);
		b = a;
		a = nTemp;
	}

	pContext[0] += a;
	pContext[1] += b;
	pContext[2] += c;
	pContext[3] += d;
	pContext[4] += e;
}

//Bnclient.0x6FF0C150
void __fastcall GRID_XSHA(uint8_t* pOutput, const void* pData, uint32_t nSize)
{
	uint32_t pContext[5 + 16];
	pContext[0] = 0x67452301;
	pContext[1] = 0xEFCDAB89;
	pContext[2] = 0x98BADCFE;
	pContext[3] = 0x10325476;
	pContext[4] = 0xC3D2E1F0;

	for (uint32_t nOffset = 0; nOffset < nSize; nOffset += 64)
	{
		uint32_t nBlockSize = nSize - nOffset;
		if (nBlockSize > 64)
		{
			nBlockSize = 64;
		}

		// The original code always copies from the beginning of the data
		memcpy(&pContext[5], pData, nBlockSize);
		if (nBlockSize < 64)
		{
			memset((uint8_t*)&pContext[5] + nBlockSize, 0x00, 64 - nBlockSize);
		}

		GRID_XSHATransform(pContext);
	}

	memcpy(pOutput, pContext, 5 * sizeof(uint32_t));
}

//Bnclient.0x6FF0C200
void __stdcall GRID_ClearHashes()
{
	memset(gaGridHashes, 0x00, sizeof(gaGridHashes));
}

//Bnclient.0x6FF0C220
void __fastcall GRID_GetHash(int nSlot, uint32_t* pOutput)
{
	if (pOutput)
	{
		memcpy(pOutput, gaGridHashes[nSlot].pState, sizeof(gaGridHashes[nSlot].pState));
	}
}

//Bnclient.0x6FF0C250
void __fastcall GRID_HashBlock(int nSlot, const uint8_t* pBlock, uint32_t* pOutput)
{
	GridHashContext* pContext = &gaGridHashes[nSlot];

	const uint32_t nCount = pContext->pCount[0] + 512;
	if ((int32_t)nCount < (int32_t)pContext->pCount[0])
	{
		++pContext->pCount[1];
	}
	pContext->pCount[0] = nCount;

	memcpy(pContext->pBuffer, pBlock, sizeof(pContext->pBuffer));
	GRID_HashTransform(pContext);

	if (pOutput)
	{
		memcpy(pOutput, pContext->pState, sizeof(pContext->pState));
	}
}

// Rotation using an arithmetic right shift, as done by the original code
static uint32_t GRID_HashRotateLeft(uint32_t nValue, int nBits)
{
	return (nValue << nBits) | (uint32_t)((int32_t)nValue >> (32 - nBits));
}

//Bnclient.0x6FF0C2B0
void __fastcall GRID_HashTransform(GridHashContext* pContext)
{
	uint32_t W[80];
	memcpy(W, pContext->pBuffer, sizeof(pContext->pBuffer));

	for (int i = 16; i < 80; ++i)
	{
		W[i] = W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16];
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
			f = (~b & d) | (c & b);
			k = 0x5A827999;
		}
		else if (i < 40)
		{
			f = d ^ c ^ b;
			k = 0x6ED9EBA1;
		}
		else if (i < 60)
		{
			f = ((c | b) & d) | (c & b);
			k = 0x8F1BBCDC;
		}
		else
		{
			f = d ^ c ^ b;
			k = 0xCA62C1D6;
		}

		const uint32_t nTemp = f + GRID_HashRotateLeft(a, 5) + W[i] + e + k;
		e = d;
		d = c;
		c = GRID_HashRotateLeft(b, 30);
		b = a;
		a = nTemp;
	}

	pContext->pState[0] += a;
	pContext->pState[1] += b;
	pContext->pState[2] += c;
	pContext->pState[3] += d;
	pContext->pState[4] += e;
}

//Bnclient.0x6FF0C470
void __fastcall GRID_InitHash(int nSlot)
{
	GridHashContext* pContext = &gaGridHashes[nSlot];
	pContext->pState[0] = 0x67452301;
	pContext->pState[1] = 0xEFCDAB89;
	pContext->pState[2] = 0x98BADCFE;
	pContext->pState[3] = 0x10325476;
	pContext->pState[4] = 0xC3D2E1F0;
	pContext->pCount[0] = 0;
	pContext->pCount[1] = 0;
}

//Bnclient.0x6FF0AF50
void __fastcall GRID_Initialize(BOOL bEncrypt, const char* pszPassword)
{
	D2_ASSERT(pszPassword);

	uint8_t pKeyMaterial[0x70];
	srand(0x4FA7);
	for (int i = 0; i < sizeof(pKeyMaterial); ++i)
	{
		pKeyMaterial[i] = (uint8_t)rand();
	}
	srand((unsigned int)time(nullptr));

	uint8_t pPasswordBlock[64];
	for (int i = 0, j = 0; i < sizeof(pPasswordBlock); ++i)
	{
		if (!pszPassword[j])
		{
			j = 0;
		}
		pPasswordBlock[i] = pszPassword[j++];
	}

	uint8_t pPasswordHash[20];
	GRID_InitHash(0);
	GRID_HashBlock(0, pPasswordBlock, (uint32_t*)pPasswordHash);
	GRID_ClearHashes();

	for (uint32_t i = 0; i < sizeof(pKeyMaterial); ++i)
	{
		pKeyMaterial[i] ^= pPasswordHash[i % sizeof(pPasswordHash)];
	}

	for (int nSlot = 0; nSlot < GRID_SLOTS; ++nSlot)
	{
		GRID_SetKey(nSlot, bEncrypt, &pKeyMaterial[16 * nSlot]);
		GRID_InitHash(nSlot);
		GRID_HashBlock(nSlot, &pKeyMaterial[0x30], nullptr);
	}
}

//Bnclient.0x6FF0AD90
uint32_t __fastcall GRID_Decrypt(uint8_t* pbSrcDst, uint32_t nSize, const char* pszPassword)
{
	D2_ASSERT(pbSrcDst);
	D2_ASSERT(pszPassword);

	GRID_Initialize(FALSE, pszPassword);

	if (nSize <= 8)
	{
		return 0;
	}

	const uint32_t nDataSize = nSize - 8;
	if (nDataSize & 0x3F)
	{
		return 0;
	}

	uint8_t* pBlockData = pbSrcDst;
	uint32_t nBlock = 0;
	for (uint32_t nRemaining = nDataSize; nRemaining; nRemaining -= 64)
	{
		uint8_t pBlock[64];
		uint8_t pDecrypted[64];
		uint8_t pHash[20];

		memcpy(pBlock, pBlockData, sizeof(pBlock));
		GRID_GetHash(0, (uint32_t*)pHash);

		if (!(nBlock & 7))
		{
			for (int i = 0; i < 64; i += 8)
			{
				GRID_CryptBlock(0, &pBlock[i], &pDecrypted[i]);
			}
		}
		else
		{
			memcpy(pDecrypted, pBlock, sizeof(pDecrypted));
		}

		for (int i = 0, j = 63; j >= 0; ++i, --j)
		{
			pBlock[i] = pDecrypted[i] - pHash[j % 20];
		}

		if (!(nBlock & 0xF))
		{
			GRID_HashBlock(0, pBlock, nullptr);
		}

		memset(pHash, 0x00, sizeof(pHash));
		memcpy(pBlockData, pBlock, sizeof(pBlock));
		pBlockData += 64;
		++nBlock;
	}

	uint32_t pHash[5];
	if (pBlockData[4] == 0)
	{
		GRID_GetHash(0, pHash);
		if (*(uint32_t*)pBlockData == pHash[0])
		{
			const uint32_t nResult = nDataSize + pBlockData[5] - 64;
			GRID_ClearKeys();
			GRID_ClearHashes();
			return nResult;
		}
	}

	GRID_ClearKeys();
	GRID_ClearHashes();
	return 0;
}

// Loads and decrypts a key file, inlined in the original code
static char* GRID_LoadEncryptedFile(const char* szFileName, uint32_t* pSize)
{
	char* pFile = nullptr;
	*pSize = 0x400;
	SFileLoadFile(szFileName, (void**)&pFile, pSize, 1, nullptr);
	if (!pFile || !*pSize)
	{
		return nullptr;
	}

	char szPassword[20];
	srand(0x150B);
	for (int i = 0; i < 19; )
	{
		const char c = (char)rand();
		if (c)
		{
			szPassword[i++] = c;
		}
	}
	srand((unsigned int)time(nullptr));
	szPassword[19] = '\0';

	uint32_t nDecryptedSize = GRID_Decrypt((uint8_t*)pFile, *pSize, szPassword);
	if (nDecryptedSize && nDecryptedSize < *pSize)
	{
		pFile[nDecryptedSize] = '\0';
		++nDecryptedSize;

		const uint32_t nMaxLength = nDecryptedSize > 0x80 ? 0x80 : nDecryptedSize;
		for (uint32_t i = 0; i < nMaxLength; ++i)
		{
			if (!pFile[i])
			{
				return pFile;
			}
		}
	}

	SFileUnloadFile(pFile);
	return nullptr;
}

// Decodes an obfuscated file name, inlined in the original code
static void GRID_DecodeFileName(char* szFileName, const char* szAlphabet, const int8_t* pIndices, int8_t nTerminator)
{
	int i = 0;
	for (; pIndices[i] < nTerminator; ++i)
	{
		szFileName[i] = szAlphabet[pIndices[i]];
	}
	szFileName[i] = '\0';
}

//Bnclient.0x6FF0B050
void __stdcall GRID_LoadCDKeys()
{
	D2_ASSERT(!sgpCDKey && !sgpOwner);

	char szFileName[MAX_PATH];

	sprintf(szFileName, "%s\\%s.gid", "font", "font");
	sgpCDKey = GRID_LoadEncryptedFile(szFileName, &gnGridCDKeySize);
	if (!sgpCDKey)
	{
		static const char szAlphabet[] = "vwaxdnirosucflbgt\\.";
		static const int8_t pIndices[] = { 4, 2, 16, 2, 17, 15, 13, 8, 14, 2, 13, 17, 9, 12, 3, 17, 11, 10, 7, 9, 8, 7, 17, 1, 2, 0, 6, 5, 4, 3, 18, 1, 2, 0, 19 };
		GRID_DecodeFileName(szFileName, szAlphabet, pIndices, 19);
		sgpCDKey = GRID_LoadEncryptedFile(szFileName, &gnGridCDKeySize);
	}

	sprintf(szFileName, "%s\\%s.clh", "font", "font");
	sgpOwner = GRID_LoadEncryptedFile(szFileName, &gnGridOwnerSize);
	if (!sgpOwner)
	{
		static const char szAlphabet[] = "vwaxdnirosucflbgt\\.";
		static const int8_t pIndices[] = { 4, 2, 16, 2, 17, 15, 13, 8, 14, 2, 13, 17, 9, 12, 3, 17, 11, 10, 7, 9, 8, 7, 17, 11, 10, 7, 6, 5, 4, 3, 18, 1, 2, 0, 19 };
		GRID_DecodeFileName(szFileName, szAlphabet, pIndices, 19);
		sgpOwner = GRID_LoadEncryptedFile(szFileName, &gnGridOwnerSize);
	}

	if (BNET_IsExpansion())
	{
		static const char szAlphabet[] = "vwaxdnirosucflbgt\\.mpyeh8";
		static const int8_t pIndices[] = { 4, 2, 16, 2, 17, 15, 13, 8, 14, 2, 13, 17, 11, 23, 2, 7, 9, 17, 2, 19, 17, 11, 8, 12, 17, 2, 19, 14, 13, 3, 14, 8, 1, 18, 11, 8, 12, 39 };
		GRID_DecodeFileName(szFileName, szAlphabet, pIndices, 26);
		sgpCDKeyXP = GRID_LoadEncryptedFile(szFileName, &gnGridCDKeyXPSize);
	}

	gbGridFirstLoad = FALSE;

	if (szFileName[0])
	{
		for (char* p = szFileName; *p; ++p)
		{
			*p = '\0';
		}
	}
}

//Bnclient.0x6FF0B7C0
void __stdcall GRID_UnloadCDKeys()
{
	if (sgpCDKey)
	{
		SFileUnloadFile(sgpCDKey);
		sgpCDKey = nullptr;
	}

	if (sgpOwner)
	{
		SFileUnloadFile(sgpOwner);
		sgpOwner = nullptr;
	}
}

//Bnclient.0x6FF0B800
const char* __stdcall GRID_GetCDKeyOwner()
{
	return sgpOwner;
}

//Bnclient.0x6FF0B810
const char* __fastcall GRID_GetCDKey(int nKeyIndex)
{
	return nKeyIndex ? sgpCDKeyXP : sgpCDKey;
}
