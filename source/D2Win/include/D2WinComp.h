#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Gfx.h>
#include <D2Unicode.h>

#pragma pack(push, 1)
// Header of a .COF file. It is followed by:
// - D2CofLayerStrc[nLayers]
// - uint8_t frameKeys[nFrames]
// - uint8_t layerPriorities[nDirections][nFrames][nLayers]
struct D2CofDataStrc
{
	uint8_t nLayers;						//0x00
	uint8_t nFrames;						//0x01
	uint8_t nDirections;					//0x02
	uint8_t nVersion;						//0x03
	uint32_t unk0x04;						//0x04
	int32_t nBoundingBox[4];				//0x08
	int32_t nAnimRate;						//0x18
};

struct D2CofLayerStrc
{
	uint8_t nComponent;						//0x00
	uint8_t nShadow;						//0x01
	uint8_t nSelectable;					//0x02
	uint8_t nTransparent;					//0x03
	uint8_t nDrawEffect;					//0x04
	uint8_t szWeaponClass[4];				//0x05
};

struct D2CofNodeStrc
{
	int32_t nRefCount;						//0x00
	uint32_t nMode;							//0x04
	uint32_t nClass;						//0x08
	uint32_t dwWClassToken;					//0x0C
	uint32_t nFileSize;						//0x10
	D2CofDataStrc* pCofData;				//0x14
	D2CofNodeStrc* pNext;					//0x18
	D2CofNodeStrc* pPrev;					//0x1C
};

struct D2CofInfoStrc
{
	D2CofNodeStrc* pCofNode;				//0x00
	D2CofInfoStrc* pNext;					//0x04
};

struct D2GfxInfoStrc
{
	D2CofInfoStrc* pCofInfo;				//0x00
};

struct D2CompositeUnitStrc
{
	uint32_t dwFlags;						//0x00
	uint8_t nDirection;						//0x04
	uint8_t nDirections;					//0x05
	uint8_t unk0x06[2];						//0x06
	int32_t nFrame;							//0x08 - 24.8 fixed point
	int32_t nFrames;						//0x0C
	int32_t nAnimRate;						//0x10
	int32_t nX;								//0x14
	int32_t nY;								//0x18
	uint32_t nClass;						//0x1C
	uint32_t nMode;							//0x20
	uint32_t nWClassTokenIndex;				//0x24
	uint8_t nComponentColors[16];			//0x28
	uint32_t dwComponentTokens[16];			//0x38
	int32_t nComponentItemTypes[16];		//0x78
	D2GfxInfoStrc* pGfxInfo;				//0xB8
	D2CellFileStrc* pEmblemCellFile;		//0xBC
	uint8_t nEmblemColor1;					//0xC0
	uint8_t nEmblemColor2;					//0xC1
	uint8_t unk0xC2[2];						//0xC2
	D2CompositeUnitStrc* pNext;				//0xC4
	D2CompositeUnitStrc* pPrev;				//0xC8
	Unicode wszAccountName[64];				//0xCC
	Unicode wszCharName[64];				//0x14C
	Unicode wszUnk0x1CC[16];				//0x1CC
	Unicode wszRealmName[32];				//0x1EC
	int32_t nLevel;							//0x22C
	uint32_t dwProductCode;					//0x230
};
#pragma pack(pop)

static_assert(sizeof(D2CofDataStrc) == 0x1C, "D2CofDataStrc size mismatch");
static_assert(sizeof(D2CofLayerStrc) == 0x09, "D2CofLayerStrc size mismatch");
static_assert(sizeof(D2CompositeUnitStrc) == 0x234, "D2CompositeUnitStrc size mismatch");


//D2Win.0x6F8A15E0
void __fastcall sub_6F8A15E0(D2CompositeUnitStrc* pCompositeUnit);
//D2Win.0x6F8A1890
BOOL __fastcall sub_6F8A1890(D2CompositeUnitStrc* pCompositeUnit, uint32_t dwGamma);
//D2Win.0x6F8A1D10
BOOL __fastcall sub_6F8A1D10(D2CompositeUnitStrc* pCompositeUnit);
//D2Win.0x6F8A2070
BOOL __fastcall sub_6F8A2070(D2CompositeUnitStrc* pCompositeUnit);
//D2Win.0x6F8A2A20 (#10142)
void __stdcall D2Win_10142_CompUnitDestroy(D2CompositeUnitStrc* pCompositeUnit, BOOL bFree);
//D2Win.0x6F8A2BD0 (#10154)
void __stdcall D2Win_10154(D2CompositeUnitStrc* pCompositeUnit, const Unicode* wszAccountName, const Unicode* wszCharName, const Unicode* wszUnk0x1CC, const Unicode* wszRealmName, int32_t nLevel, uint32_t dwProductCode);
//D2Win.0x6F8A2C50 (#10143)
BOOL __fastcall D2Win_10143(D2CompositeUnitStrc* pCompositeUnit, uint32_t nMode);
//D2Win.0x6F8A3360 (#10159)
void __stdcall D2Win_10159(D2CellFileStrc* pSquelchCelFile, D2CellFileStrc* pSelectedCelFile);
//D2Win.0x6F8A3390 (#10144)
D2CompositeUnitStrc* __stdcall D2Win_10144(uint32_t nClass, uint32_t nMode, uint8_t* pComponents, const uint8_t* pComponentColors);
//D2Win.0x6F8A4260 (#10145)
void __stdcall D2Win_10145(D2CompositeUnitStrc* pCompositeUnit, uint32_t nClass, uint32_t nMode, uint8_t* pComponents, const uint8_t* pComponentColors);
//D2Win.0x6F8A43C0 (#10146)
void __stdcall D2Win_10146();
//D2Win.0x6F8A4400 (#10147)
D2CompositeUnitStrc* __stdcall D2Win_10147();
//D2Win.0x6F8A4410 (#10148)
D2CompositeUnitStrc* __stdcall D2Win_10148(D2CompositeUnitStrc* pCompositeUnit);
//D2Win.0x6F8A4440 (#10149)
void __stdcall D2Win_10149(D2CompositeUnitStrc* pCompositeUnit, uint8_t nDirection);
//D2Win.0x6F8A4490 (#10150)
uint8_t __stdcall D2Win_10150(D2CompositeUnitStrc* pCompositeUnit);
//D2Win.0x6F8A44C0 (#10169)
int32_t __stdcall D2Win_10169(D2CompositeUnitStrc* pCompositeUnit);
//D2Win.0x6F8A44F0 (#10151)
void __stdcall D2Win_10151(D2CompositeUnitStrc* pCompositeUnit, int32_t nFrame);
//D2Win.0x6F8A4540 (#10152)
void __stdcall D2Win_10152(D2CompositeUnitStrc* pCompositeUnit, int32_t nX);
//D2Win.0x6F8A4570 (#10153)
void __stdcall D2Win_10153(D2CompositeUnitStrc* pCompositeUnit, int32_t nY);
//D2Win.0x6F8A45A0 (#10155)
uint32_t __stdcall D2Win_10155(D2CompositeUnitStrc* pCompositeUnit);
//D2Win.0x6F8A45D0 (#10156)
void __stdcall D2Win_10156(D2CompositeUnitStrc* pCompositeUnit, uint32_t dwFlags);
//D2Win.0x6F8A4600 (#10158)
void __stdcall D2Win_10158(D2CompositeUnitStrc* pCompositeUnit, uint8_t nEmblem, uint8_t nEmblemColor1, uint8_t nEmblemColor2);
//D2Win.0x6F8A46E0 (#10157)
void __stdcall D2Win_10157();
//D2Win.0x6F8A4C10
void __stdcall sub_6F8A4C10();
//D2Win.0x6F8A4C70 (#10161)
const char* __stdcall D2Win_10161(int32_t nClass, int32_t nProgression, BOOL bHardcore, BOOL bExpansion);
//D2Win.0x6F8A4CE0 (#10160)
const char* __stdcall D2Win_10160_GetPlayerTitle(int32_t nClass, int32_t nTitle, BOOL bExpansion);
