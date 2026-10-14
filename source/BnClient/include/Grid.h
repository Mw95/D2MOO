#pragma once

#include <Windows.h>

#include <cstdint>

#define GRID_IDEA_ROUNDS 8
#define GRID_IDEA_KEYLEN (6 * GRID_IDEA_ROUNDS + 4)
#define GRID_SLOTS 3

#pragma pack(push, 1)
// SHA-1 variant used by the grid cipher
struct GridHashContext
{
	uint32_t pState[5];					//0x00
	uint32_t pCount[2];					//0x14
	uint32_t pBuffer[16];				//0x1C
};
#pragma pack(pop)

uint16_t __fastcall GRID_IDEAMulInv(uint16_t x);
void __fastcall GRID_IDEAInvertKey(const uint16_t* pEncryptionKey, uint16_t* pDecryptionKey);
void __fastcall GRID_IDEACipher(const uint16_t* pInput, uint16_t* pOutput, const uint16_t* pKey);
void __stdcall GRID_ClearKeys();
void __fastcall GRID_CryptBlock(int nSlot, const uint8_t* pInput, uint8_t* pOutput);
void __fastcall GRID_SetKey(int nSlot, BOOL bEncrypt, const uint8_t* pUserKey);
void __fastcall GRID_XSHATransform(uint32_t* pContext);
void __fastcall GRID_XSHA(uint8_t* pOutput, const void* pData, uint32_t nSize);
void __stdcall GRID_ClearHashes();
void __fastcall GRID_GetHash(int nSlot, uint32_t* pOutput);
void __fastcall GRID_HashBlock(int nSlot, const uint8_t* pBlock, uint32_t* pOutput);
void __fastcall GRID_HashTransform(GridHashContext* pContext);
void __fastcall GRID_InitHash(int nSlot);
void __fastcall GRID_Initialize(BOOL bEncrypt, const char* pszPassword);
uint32_t __fastcall GRID_Decrypt(uint8_t* pbSrcDst, uint32_t nSize, const char* pszPassword);

void __stdcall GRID_LoadCDKeys();
void __stdcall GRID_UnloadCDKeys();
const char* __stdcall GRID_GetCDKeyOwner();
const char* __fastcall GRID_GetCDKey(int nKeyIndex);
