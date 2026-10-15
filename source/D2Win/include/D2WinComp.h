#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Gfx.h>
#include <D2Unicode.h>

#pragma pack(push, 1)
struct D2CofDataStrc
{
	uint8_t nLayers;
	uint8_t nFramesPerDirection;
	uint8_t nDirections;
	uint8_t nVersion;
	uint32_t unk0x04;
	uint32_t nBoxLeft;
	uint32_t nBoxRight;
	uint32_t nBoxTop;
	uint32_t nBoxBottom;
	uint32_t nAnimSpeed;
};

struct D2CofNodeStrc
{
	int32_t nRefCount;
	uint32_t nMode;
	uint32_t nClass;
	uint32_t dwWeaponClass;
	uint32_t unk0x10;
	D2CofDataStrc* pCofData;
	D2CofNodeStrc* pNext;
	D2CofNodeStrc* pPrev;
};

struct D2CofInfoStrc
{
	D2CofNodeStrc* pCofNode;
	D2CofInfoStrc* pNext;
};

struct D2GfxInfoStrc
{
	D2CofInfoStrc* pCofInfo;
};

struct D2CompositeUnitStrc
{
	uint32_t dwFlags;
	uint8_t nDirection;
	uint8_t nDirections;
	uint8_t unk0x06;
	uint8_t unk0x07;
	int32_t nFrame;							// 8.8 fixed point
	int32_t nFrameCount;
	uint32_t nAnimSpeed;
	int32_t nX;
	int32_t nY;
	int32_t nUnitIndex;
	int32_t nMode;
	int32_t nWClassTokenIndex;
	uint8_t nComponentColors[16];
	uint32_t dwArmorType[16];
	uint32_t unk0x78;
	uint32_t unk0x7C;
	uint32_t unk0x80;
	uint32_t unk0x84;
	uint32_t unk0x88;
	uint32_t unk0x8C;
	uint32_t unk0x90;
	uint32_t unk0x94;
	uint32_t unk0x98;
	uint32_t unk0x9C;
	uint32_t unk0xA0;
	uint32_t unk0xA4;
	uint32_t unk0xA8;
	uint32_t unk0xAC;
	uint32_t unk0xB0;
	uint32_t unk0xB4;
	D2GfxInfoStrc* pGfxInfo;
	D2CellFileStrc* pEmblemCellFile;
	uint8_t nEmblemColor1;
	uint8_t nEmblemColor2;
	uint8_t unk0xC2;
	uint8_t unk0xC3;
	D2CompositeUnitStrc* pNext;
	D2CompositeUnitStrc* pPrev;
	Unicode wszAccountName[64];
	Unicode wszCharName[64];
	Unicode wszGuildTag[16];
	Unicode wszRealmName[32];
	int32_t nCharLevel;
	uint32_t dwProductCode;
};
#pragma pack(pop)


void __stdcall D2COMP_InitEmblemColorTables();
//1.10f: D2Win.0x6F8A46E0 (#10157)
//1.14d: 0x00505550
void __stdcall D2Win_10157();
//1.10f: D2Win.0x6F8A4400 (#10147)
//1.14d: 0x00505150
D2CompositeUnitStrc* __stdcall D2Win_10147();
//1.10f: D2Win.0x6F8A4410 (#10148)
//1.14d: 0x00505160
inline void* D2Win_10148(void*)
{
	return nullptr;
}
//1.10f: D2Win.0x6F8A15E0
//1.14d: 0x00503A50
inline void sub_6F8A15E0(void*)
{
}
//1.10f: D2Win.0x6F8A1890
//1.14d: 0x00503BA0
inline void sub_6F8A1890(void*, int)
{
}
//1.10f: D2Win.0x6F8A1D10
//1.14d: 0x00505810
inline void sub_6F8A1D10(void*)
{
}
//1.10f: D2Win.0x6F8A2070
//1.14d: 0x00505A80
inline void sub_6F8A2070(void*)
{
}
//1.10f: D2Win.0x6F8A2A20 (#10142)
//1.14d: 0x005041B0
void __stdcall D2Win_10142_CompUnitDestroy(D2CompositeUnitStrc* pCompositeUnit, int bUnlinkAndFree);
//1.10f: D2Win.0x6F8A4CE0 (#10160)
//1.14d: 0x00505640
const char* __stdcall D2Win_10160_GetPlayerTitle(int nClass, int nTitle, BOOL bExpansion);
//D2Win.0x6F8A2C50 (#10143)
BOOL __fastcall D2Win_10143(D2CompositeUnitStrc* pCompositeUnit, int nMode);
//D2Win.0x6F8A3390 (#10144)
D2CompositeUnitStrc* __stdcall D2Win_10144(unsigned int nUnitIndex, int nMode, BYTE* pComponents, BYTE* pComponentsColors);
//D2Win.0x6F8A4440 (#10149)
void __stdcall D2Win_10149(D2CompositeUnitStrc* pCompositeUnit, uint8_t a2);
//D2Win.0x6F8A44F0 (#10151)
void __stdcall D2Win_10151(D2CompositeUnitStrc* pCompositeUnit, int a2);
//D2Win.0x6F8A4540 (#10152)
void __stdcall D2Win_10152(D2CompositeUnitStrc* pCompositeUnit, int nX);
//D2Win.0x6F8A4570 (#10153)
void __stdcall D2Win_10153(D2CompositeUnitStrc* pCompositeUnit, int nY);
//D2Win.0x6F8A45D0 (#10156)
void __stdcall D2Win_10156(D2CompositeUnitStrc* pCompositeUnit, int nFlags);
//D2Win.0x6F8A4C70 (#10161)
const char* __stdcall D2Win_10161(int a1, int a2, int a3, BOOL bSoftCore);
