#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

#pragma pack(push, 1)

struct FOGIFFBondEntry				// sizeof 0x0C
{
	uint32_t dwKey;					// 0x00
	uint32_t dwValue1;				// 0x04
	uint32_t dwValue2;				// 0x08
};

// Small key/values chunk tagged 'BOND', with a fixed maximum size of 1024 bytes.
struct FOGIFFBond					// sizeof 0x08 + 0x0C * nEntries
{
	uint32_t dwTag;					// 0x00 'BOND'
	uint32_t nEntries;				// 0x04
	FOGIFFBondEntry pEntries[1];	// 0x08
};

#pragma pack(pop)

enum FOGIFFErrors : int32_t
{
	FOG_IFF_ERROR_NONE = 0,
	FOG_IFF_ERROR_NO_SPACE = 0x0E,
	FOG_IFF_ERROR_NOT_FOUND = 0x16,
};

// 1.10f: 0x6FF61A20 (#10199)
FOG_DLL_DECL FOGIFFBond* __fastcall FOG_IFFReadBond(uint8_t** ppData, uint32_t* pDataSize);
// 1.10f: 0x6FF61A70 (#10200)
FOG_DLL_DECL FOGIFFBond* __fastcall FOG_IFFCreateBond();
// 1.10f: 0x6FF61A90 (#10201)
FOG_DLL_DECL int32_t __fastcall FOG_IFFWriteBond(FOGIFFBond* pBond, uint8_t* pDest, int32_t* pDestSize, int32_t* pWrittenSize);
// 1.10f: 0x6FF61AE0 (#10202)
FOG_DLL_DECL void __fastcall FOG_IFFFreeBond(FOGIFFBond* pBond);
// 1.10f: 0x6FF61AF0 (#10203)
FOG_DLL_DECL int32_t __fastcall FOG_IFFAddBondEntry(uint32_t dwKey, uint32_t dwValue1, uint32_t dwValue2, FOGIFFBond* pBond);
// 1.10f: 0x6FF61B40 (#10204)
FOG_DLL_DECL int32_t __fastcall FOG_IFFAddBondEntryByName(const char* szName, uint32_t dwValue1, uint32_t dwValue2, FOGIFFBond* pBond);
// 1.10f: 0x6FF61B90 (#10205)
FOG_DLL_DECL int32_t __fastcall FOG_IFFGetBondEntry(uint32_t dwKey, FOGIFFBond* pBond, uint32_t* pValue1, uint32_t* pValue2);
// 1.10f: 0x6FF61BD0 (#10206)
FOG_DLL_DECL int32_t __fastcall FOG_IFFGetBondEntryByName(const char* szName, FOGIFFBond* pBond, uint32_t* pValue1, uint32_t* pValue2);
