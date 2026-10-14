#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

#pragma pack(push, 1)

struct FOGSha1Context			// sizeof 0x5C
{
	uint32_t nBitCount[2];		// 0x00 Low, high
	uint32_t nState[5];			// 0x08
	uint8_t pBuffer[64];		// 0x1C
};

#pragma pack(pop)

// Battle.net's broken SHA-1 variant: no length padding, little endian words and a broken message schedule.
// 1.10f: 0x6FF63B40 (#10189)
FOG_DLL_DECL void __fastcall FOG_XSha1(uint32_t* pDigest, const void* pData, uint32_t nSize);

// Standard SHA-1. These are member functions (__thiscall), the unused parameters emulate it with __fastcall.
// 1.10f: 0x6FF64270 (#10248)
FOG_DLL_DECL void __fastcall FOG_Sha1Initialize(FOGSha1Context* pContext);
// 1.10f: 0x6FF642B0 (#10249)
FOG_DLL_DECL void __fastcall FOG_Sha1Update(FOGSha1Context* pContext, int nUnused, const void* pData, uint32_t nSize);
// 1.10f: 0x6FF64350 (#10250)
FOG_DLL_DECL void __fastcall FOG_Sha1Finalize(FOGSha1Context* pContext, int nUnused, uint8_t* pDigest);
