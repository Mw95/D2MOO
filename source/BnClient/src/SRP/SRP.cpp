#include "SRP/SRP.h"

#include <climits>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <new>

#include <Storm.h>

#include "SRP/SHA.h"


static const char* gszSRPSeparator = ":";


//Bnclient.0x6FF158C0
static void* __fastcall SRP_BigFromUnsigned(uint32_t nValue)
{
	void* pBig;
	SBigNew(&pBig);
	SBigFromUnsigned(pBig, nValue);
	return pBig;
}

//Bnclient.0x6FF158E0
static void* __fastcall SRP_BigFromBinary(const uint8_t* pData, uint32_t nSize)
{
	void* pBig;
	SBigNew(&pBig);
	SBigFromBinary(pBig, pData, nSize);
	return pBig;
}

//Bnclient.0x6FF15910
static uint32_t __fastcall SRP_BigToBinary(void* pBig, uint8_t* pOutput, uint32_t nSize)
{
	uint32_t nBytesWritten;
	SBigToBinaryBuffer(pBig, pOutput, nSize, &nBytesWritten);
	if (nBytesWritten < nSize)
	{
		SMemZero(&pOutput[nBytesWritten], nSize - nBytesWritten);
	}
	return nBytesWritten;
}

//Bnclient.0x6FF15950
static int __fastcall SRP_BigCompare(void* pBigA, void* pBigB)
{
	return SBigCompare(pBigA, pBigB);
}

//Bnclient.0x6FF15960
static int __fastcall SRP_BigCompareUnsigned(void* pBig, uint32_t nValue)
{
	void* pValue;
	SBigNew(&pValue);
	SBigFromUnsigned(pValue, nValue);
	const int nResult = SBigCompare(pBig, pValue);
	SBigDel(pValue);
	return nResult;
}

//Bnclient.0x6FF159A0
static void __fastcall SRP_BigAdd(void* pResult, void* pBigA, void* pBigB)
{
	SBigAdd(pResult, pBigA, pBigB);
}

//Bnclient.0x6FF159B0
static void __fastcall SRP_BigSub(void* pResult, void* pBigA, void* pBigB)
{
	SBigSub(pResult, pBigA, pBigB);
}

//Bnclient.0x6FF159C0
static void __fastcall SRP_BigMulUnsigned(void* pResult, void* pBig, uint32_t nValue)
{
	void* pValue;
	SBigNew(&pValue);
	SBigFromUnsigned(pValue, nValue);
	SBigMul(pResult, pBig, pValue);
	SBigDel(pValue);
}

//Bnclient.0x6FF15A00
static void __fastcall SRP_BigPowMod(void* pResult, void* pBase, void* pExponent, void* pModulus)
{
	SBigPowMod(pResult, pBase, pExponent, pModulus);
}

//Bnclient.0x6FF15A20
static void __fastcall SRP_BigDel(void* pBig)
{
	SBigDel(pBig);
}

//Bnclient.0x6FF13670
SRPContext::SRPContext()
{
	bInitialized = FALSE;
	nRandomPoolAvailable = 0;
}

//Bnclient.0x6FF13680
void SRPContext::SeedRandom(uint32_t nSeed)
{
	uint32_t aSeedData[3];
	aSeedData[0] = (uint32_t)time(nullptr);
	aSeedData[1] = nSeed;
	srand(nSeed);
	aSeedData[2] = rand();

	SHA1Context tContext;
	SHA1_Init(&tContext);
	SHA1_Update(&tContext, aSeedData, sizeof(aSeedData));
	SHA1_Final(pRandomSeed1, &tContext);

	memcpy(pRandomSeed2, pRandomSeed1, sizeof(pRandomSeed2));
	memset(pRandomPool, 0x00, sizeof(pRandomPool));
	nRandomPoolAvailable = 0;
}

//Bnclient.0x6FF137D0
void SRPContext::ComputeX(const uint8_t* pSalt, const char* szUserName, const char* szPassword, void** pX)
{
	SHA1Context tContext;
	uint8_t pDigest[20];

	SHA1_Init(&tContext);
	SHA1_Update(&tContext, szUserName, SStrLen(szUserName));
	SHA1_Update(&tContext, gszSRPSeparator, SStrLen(gszSRPSeparator));
	SHA1_Update(&tContext, szPassword, SStrLen(szPassword));
	SHA1_Final(pDigest, &tContext);

	SHA1_Init(&tContext);
	SHA1_Update(&tContext, pSalt, 32);
	SHA1_Update(&tContext, pDigest, sizeof(pDigest));
	SHA1_Final(pDigest, &tContext);

	*pX = SRP_BigFromBinary(pDigest, sizeof(pDigest));
}

//Bnclient.0x6FF13890
void SRPContext::ComputeVerifier(void** pX, void** pVerifier)
{
	SRP_BigPowMod(*pVerifier, g, *pX, N);
}

//Bnclient.0x6FF138B0
void SRPContext::ComputeU(void** pB, uint32_t* pU)
{
	uint8_t pBuffer[32];
	SRP_BigToBinary(*pB, pBuffer, sizeof(pBuffer));

	SHA1Context tContext;
	uint8_t pDigest[20];
	SHA1_Init(&tContext);
	SHA1_Update(&tContext, pBuffer, sizeof(pBuffer));
	SHA1_Final(pDigest, &tContext);

	*pU = ((uint32_t)pDigest[0] << 24) | ((uint32_t)pDigest[1] << 16) | ((uint32_t)pDigest[2] << 8) | pDigest[3];
}

//Bnclient.0x6FF13930
BOOL SRPContext::ComputeS(void** pa, void** pB, void** pX, void** pS)
{
	if (SRP_BigCompare(*pB, N) >= 0 || !SRP_BigCompareUnsigned(*pB, 0))
	{
		return FALSE;
	}

	uint32_t u;
	ComputeU(pB, &u);
	if (!u)
	{
		return FALSE;
	}

	void* v = SRP_BigFromUnsigned(0);
	ComputeVerifier(pX, &v);

	void* pBase = SRP_BigFromUnsigned(0);
	void* pExponent = SRP_BigFromUnsigned(0);

	// S = (B - v) ^ (a + u * x) % N
	if (SRP_BigCompare(*pB, v) < 0)
	{
		SRP_BigAdd(pExponent, *pB, N);
		SRP_BigSub(pBase, pExponent, v);
	}
	else
	{
		SRP_BigSub(pBase, *pB, v);
	}

	SRP_BigMulUnsigned(pExponent, *pX, u);
	SRP_BigAdd(pExponent, pExponent, *pa);
	SRP_BigPowMod(*pS, pBase, pExponent, N);

	SRP_BigDel(pExponent);
	SRP_BigDel(pBase);
	SRP_BigDel(v);
	return TRUE;
}

//Bnclient.0x6FF13A40
void SRPContext::ComputeM1(const char* szUserName, const uint8_t* pSalt, const uint8_t* pA, const uint8_t* pB, const uint8_t* pK, uint8_t* pM1)
{
	SHA1Context tContext;
	uint8_t pBuffer[32];
	uint8_t pModulusHash[20];
	uint8_t pGeneratorHash[20];
	uint8_t pXorHash[20];
	uint8_t pUserNameHash[20];

	SRP_BigToBinary(N, pBuffer, sizeof(pBuffer));
	SHA1_Init(&tContext);
	SHA1_Update(&tContext, pBuffer, sizeof(pBuffer));
	SHA1_Final(pModulusHash, &tContext);

	SRP_BigToBinary(g, pBuffer, sizeof(pBuffer));
	SHA1_Init(&tContext);
	SHA1_Update(&tContext, pBuffer, sizeof(pBuffer));
	SHA1_Final(pGeneratorHash, &tContext);

	for (int i = 0; i < 20; ++i)
	{
		pXorHash[i] = pGeneratorHash[i] ^ pModulusHash[i];
	}

	SHA1_Init(&tContext);
	SHA1_Update(&tContext, szUserName, SStrLen(szUserName));
	SHA1_Final(pUserNameHash, &tContext);

	SHA1_Init(&tContext);
	SHA1_Update(&tContext, pXorHash, sizeof(pXorHash));
	SHA1_Update(&tContext, pUserNameHash, sizeof(pUserNameHash));
	SHA1_Update(&tContext, pSalt, 32);
	SHA1_Update(&tContext, pA, 32);
	SHA1_Update(&tContext, pB, 32);
	SHA1_Update(&tContext, pK, 40);
	SHA1_Final(pM1, &tContext);
}

//Bnclient.0x6FF13B90
void SRPContext::ComputeM2(const uint8_t* pA, const uint8_t* pM1, const uint8_t* pK, uint8_t* pM2)
{
	SHA1Context tContext;
	SHA1_Init(&tContext);
	SHA1_Update(&tContext, pA, 32);
	SHA1_Update(&tContext, pM1, 20);
	SHA1_Update(&tContext, pK, 40);
	SHA1_Final(pM2, &tContext);
}

//Bnclient.0x6FF13BE0
BOOL SRPContext::IsInitialized()
{
	return bInitialized != FALSE;
}

//Bnclient.0x6FF13BF0
SRP::SRP()
{
	m_pContext = nullptr;
	if (void* pMemory = SMemAlloc(sizeof(SRPContext), __FILE__, __LINE__, 0))
	{
		m_pContext = new (pMemory) SRPContext();
	}
}

//Bnclient.0x6FF13C20
SRP::~SRP()
{
	if (m_pContext)
	{
		SMemFree(m_pContext, "delete", -1, 0);
	}
}

//Bnclient.0x6FF13C40
BOOL SRP::Initialize(uint32_t nGeneratorSize, const uint8_t* pGenerator, uint32_t nModulusSize, const uint8_t* pModulus)
{
	if (m_pContext->bInitialized)
	{
		SRP_BigDel(m_pContext->N);
		SRP_BigDel(m_pContext->g);
	}

	m_pContext->g = SRP_BigFromBinary(pGenerator, nGeneratorSize);
	m_pContext->N = SRP_BigFromBinary(pModulus, nModulusSize);
	m_pContext->bInitialized = TRUE;

	if (!m_pContext->IsInitialized())
	{
		SRP_BigDel(m_pContext->N);
		SRP_BigDel(m_pContext->g);
		m_pContext->bInitialized = FALSE;
	}

	return m_pContext->bInitialized;
}

//Bnclient.0x6FF13CC0
void SRP::SeedRandom(uint32_t nSeed)
{
	m_pContext->SeedRandom(nSeed);
}

//Bnclient.0x6FF13CD0
void SRP::Destroy()
{
	if (m_pContext->bInitialized)
	{
		SRP_BigDel(m_pContext->N);
		SRP_BigDel(m_pContext->g);
	}

	m_pContext->bInitialized = FALSE;
}

//Bnclient.0x6FF13700
void SRP::GetRandomBytes(uint8_t* pOutput, uint32_t nSize)
{
	if (!nSize)
	{
		return;
	}

	while (nSize > m_pContext->nRandomPoolAvailable)
	{
		const uint32_t nAvailable = m_pContext->nRandomPoolAvailable;
		memcpy(pOutput, &m_pContext->pRandomPool[sizeof(m_pContext->pRandomPool) - nAvailable], nAvailable);
		pOutput += nAvailable;
		nSize -= nAvailable;

		SHA1Context tContext;
		SHA1_Init(&tContext);
		SHA1_Update(&tContext, m_pContext->pRandomSeed1, sizeof(m_pContext->pRandomSeed1));
		SHA1_Update(&tContext, m_pContext->pRandomPool, sizeof(m_pContext->pRandomPool));
		SHA1_Update(&tContext, m_pContext->pRandomSeed2, sizeof(m_pContext->pRandomSeed2));
		SHA1_Final(m_pContext->pRandomPool, &tContext);
		m_pContext->nRandomPoolAvailable = sizeof(m_pContext->pRandomPool);
	}

	if (nSize)
	{
		memcpy(pOutput, &m_pContext->pRandomPool[sizeof(m_pContext->pRandomPool) - m_pContext->nRandomPoolAvailable], nSize);
		m_pContext->nRandomPoolAvailable -= nSize;
	}
}

//Bnclient.0x6FF13D00
void SRP::CreateVerifier(const char* szUserName, const char* szPassword, uint8_t* pSalt, uint8_t* pVerifier)
{
	GetRandomBytes(pSalt, 32);

	void* x;
	m_pContext->ComputeX(pSalt, szUserName, szPassword, &x);

	void* v = SRP_BigFromUnsigned(0);
	m_pContext->ComputeVerifier(&x, &v);
	SRP_BigToBinary(v, pVerifier, 32);

	SRP_BigDel(x);
	SRP_BigDel(v);
}

//Bnclient.0x6FF13D70
void SRP::StartLogon(BnSRPSession* pSession, const char* szUserName, const char* szPassword)
{
	SStrCopy(pSession->szUserName, szUserName, INT_MAX);
	SStrCopy(pSession->szPassword, szPassword, INT_MAX);

	GetRandomBytes(pSession->a, sizeof(pSession->a));

	void* a = SRP_BigFromBinary(pSession->a, sizeof(pSession->a));
	void* A = SRP_BigFromUnsigned(0);
	SRP_BigPowMod(A, m_pContext->g, a, m_pContext->N);
	SRP_BigDel(a);

	SRP_BigToBinary(A, pSession->A, sizeof(pSession->A));
	SRP_BigDel(A);
}

//Bnclient.0x6FF13E00
BOOL SRP::ProcessChallenge(BnSRPSession* pSession, const uint8_t* pSalt, const uint8_t* pB)
{
	void* B = SRP_BigFromBinary(pB, 32);
	if (SRP_BigCompareUnsigned(B, 0) != 1)
	{
		SRP_BigDel(B);
		return FALSE;
	}

	void* x;
	m_pContext->ComputeX(pSalt, pSession->szUserName, pSession->szPassword, &x);

	void* S = SRP_BigFromUnsigned(0);
	void* a = SRP_BigFromBinary(pSession->a, sizeof(pSession->a));
	const BOOL bResult = m_pContext->ComputeS(&a, &B, &x, &S);
	SRP_BigDel(a);
	SRP_BigDel(B);
	SRP_BigDel(x);

	if (!bResult)
	{
		SRP_BigDel(S);
		return FALSE;
	}

	uint8_t pS[32];
	SRP_BigToBinary(S, pS, sizeof(pS));
	SHA_Interleave(pSession->K, pS, sizeof(pS));
	SRP_BigDel(S);

	m_pContext->ComputeM1(pSession->szUserName, pSalt, pSession->A, pB, pSession->K, pSession->M1);
	return TRUE;
}

//Bnclient.0x6FF13F20
BOOL SRP::VerifyServerProof(BnSRPSession* pSession, const uint8_t* pM2)
{
	uint8_t pExpectedM2[20];
	m_pContext->ComputeM2(pSession->A, pSession->M1, pSession->K, pExpectedM2);
	return memcmp(pExpectedM2, pM2, sizeof(pExpectedM2)) == 0;
}
