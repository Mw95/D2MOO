#pragma once

#include <cstdint>

#pragma pack(push, 1)
struct SHA1Context
{
	uint32_t pState[5];					//0x00
	uint32_t pCount[2];					//0x14 Message length in bits (low, high)
	uint8_t pBuffer[64];				//0x1C
};
#pragma pack(pop)

void __fastcall SHA1_Init(SHA1Context* pContext);
void __fastcall SHA1_Update(SHA1Context* pContext, const void* pData, uint32_t nSize);
void __fastcall SHA1_Transform(SHA1Context* pContext, const uint8_t* pBlock);
void __fastcall SHA1_Final(uint8_t* pDigest, SHA1Context* pContext);
uint8_t* __fastcall SHA_Interleave(uint8_t* pOutput, const uint8_t* pInput, uint32_t nSize);
