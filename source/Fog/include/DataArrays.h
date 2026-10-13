#pragma once

#include <D2BasicTypes.h>
#include <Fog.h>

#pragma pack(push, 1)

// Array of fixed size elements accessed through handles.
// The first 16 bits of each element hold a "salt" value, 0 meaning the element is unused.
// Handles are made of the element index in the high 16 bits and the salt in the low 16 bits,
// so that a handle to a freed and reused element is detected as invalid.
struct FOGDataArray								// sizeof 0x120
{
	char szName[256];							// 0x000
	int32_t nMaxElements;						// 0x100
	int32_t nElementSize;						// 0x104
	BOOL fValid;								// 0x108
	int32_t nFirstFreeElementHint;				// 0x10C
	int32_t nLastUsedElement;					// 0x110
	int32_t nUsedElements;						// 0x114
	uint16_t nNextSalt;							// 0x118
	uint16_t pad0x11A;							// 0x11A
	uint8_t* pElements;							// 0x11C
	// Elements data follows
};

#pragma pack(pop)

using FOGDataArrayHandle = int32_t;
constexpr FOGDataArrayHandle FOG_DATA_ARRAY_INVALID_HANDLE = -1;

// 1.10f: 0x6FF5D7E0 (#10060)
FOG_DLL_DECL FOGDataArray* __fastcall FOG_DataArrayCreate(const char* szName, int32_t nMaxElements, int32_t nElementSize);
// 1.10f: 0x6FF5D860 (#10061)
FOG_DLL_DECL void __fastcall FOG_DataArrayDestroy(FOGDataArray* pDataArray);
// 1.10f: 0x6FF5D890 (#10062)
FOG_DLL_DECL void __fastcall FOG_DataArrayInitialize(FOGDataArray* pDataArray);
// 1.10f: 0x6FF5D8F0 (#10063)
FOG_DLL_DECL void __fastcall FOG_DataArrayClear(FOGDataArray* pDataArray);
// 1.10f: 0x6FF5D970 (#10064)
FOG_DLL_DECL FOGDataArrayHandle __fastcall FOG_DataArrayAllocElement(FOGDataArray* pDataArray);
// 1.10f: 0x6FF5DA50 (#10065)
FOG_DLL_DECL void __fastcall FOG_DataArrayFreeElement(FOGDataArray* pDataArray, FOGDataArrayHandle hElement);
// 1.10f: 0x6FF5DBC0 (#10066)
FOG_DLL_DECL void* __fastcall FOG_DataArrayGetElementChecked(FOGDataArray* pDataArray, FOGDataArrayHandle hElement);
// 1.10f: 0x6FF5DB00 (#10067)
FOG_DLL_DECL void* __fastcall FOG_DataArrayGetElement(FOGDataArray* pDataArray, FOGDataArrayHandle hElement);
