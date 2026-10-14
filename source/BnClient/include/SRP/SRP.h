#pragma once

#include <Windows.h>

#include <cstdint>

#pragma pack(push, 1)
// Data of a SRP exchange with the server
struct BnSRPSession
{
	char szUserName[32];				//0x00
	char szPassword[32];				//0x20
	uint8_t a[32];						//0x40 Client private key
	uint8_t A[32];						//0x60 Client public key
	uint8_t K[40];						//0x80 Session key
	uint8_t M1[20];						//0xA8 Client proof
};

struct SRPContext
{
	BOOL bInitialized;					//0x00
	void* g;							//0x04 Generator (SBig)
	void* N;							//0x08 Modulus (SBig)
	uint8_t pRandomSeed1[20];			//0x0C
	uint8_t pRandomSeed2[20];			//0x20
	uint8_t pRandomPool[20];			//0x34
	uint32_t nRandomPoolAvailable;		//0x48

	SRPContext();
	BOOL IsInitialized();
	void SeedRandom(uint32_t nSeed);
	void ComputeX(const uint8_t* pSalt, const char* szUserName, const char* szPassword, void** pX);
	void ComputeVerifier(void** pX, void** pVerifier);
	void ComputeU(void** pB, uint32_t* pU);
	BOOL ComputeS(void** pa, void** pB, void** pX, void** pS);
	void ComputeM1(const char* szUserName, const uint8_t* pSalt, const uint8_t* pA, const uint8_t* pB, const uint8_t* pK, uint8_t* pM1);
	void ComputeM2(const uint8_t* pA, const uint8_t* pM1, const uint8_t* pK, uint8_t* pM2);
};

class SRP
{
public:
	SRPContext* m_pContext;				//0x00

	SRP();
	~SRP();

	BOOL Initialize(uint32_t nGeneratorSize, const uint8_t* pGenerator, uint32_t nModulusSize, const uint8_t* pModulus);
	void SeedRandom(uint32_t nSeed);
	void Destroy();
	void GetRandomBytes(uint8_t* pOutput, uint32_t nSize);
	void CreateVerifier(const char* szUserName, const char* szPassword, uint8_t* pSalt, uint8_t* pVerifier);
	void StartLogon(BnSRPSession* pSession, const char* szUserName, const char* szPassword);
	BOOL ProcessChallenge(BnSRPSession* pSession, const uint8_t* pSalt, const uint8_t* pB);
	BOOL VerifyServerProof(BnSRPSession* pSession, const uint8_t* pM2);
};
#pragma pack(pop)
