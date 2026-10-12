#pragma once

#include <D2BasicTypes.h>
#include <Windows.h>

#pragma pack(push, 1)

constexpr int NUMBER_PALETTE_ENTRIES = 256;

// Lookup tables generated from a palette by CreateD2Palette.
// Blending tables are indexed as [nDestColor][nSrcColor].
struct D2CMPPaletteStrc
{
	PALETTEENTRY pPalette[NUMBER_PALETTE_ENTRIES];									//0x00000
	uint8_t pDarkenTables[32][NUMBER_PALETTE_ENTRIES];								//0x00400
	uint8_t pBrightenTables[16][NUMBER_PALETTE_ENTRIES];							//0x02400
	uint8_t pLightenTable[NUMBER_PALETTE_ENTRIES];									//0x03400
	uint8_t pAlphaBlendTables[3][NUMBER_PALETTE_ENTRIES][NUMBER_PALETTE_ENTRIES];	//0x03500 75%, 50% and 25% opacity
	uint8_t pAdditiveTable[NUMBER_PALETTE_ENTRIES][NUMBER_PALETTE_ENTRIES];			//0x33500
	uint8_t pMultiplyTable[NUMBER_PALETTE_ENTRIES][NUMBER_PALETTE_ENTRIES];			//0x43500
	uint8_t pHueShiftTables[24][NUMBER_PALETTE_ENTRIES];							//0x53500
	uint8_t pHueShiftDarkTables[24][NUMBER_PALETTE_ENTRIES];						//0x54D00
	uint8_t pHueShiftLightTables[24][NUMBER_PALETTE_ENTRIES];						//0x56500
	uint8_t pGreyDarkTable[NUMBER_PALETTE_ENTRIES];									//0x57D00
	uint8_t pGreyLightTable[NUMBER_PALETTE_ENTRIES];								//0x57E00
	uint8_t pSelectiveHueShiftTables[24][NUMBER_PALETTE_ENTRIES];					//0x57F00
	uint8_t unk0x59700[NUMBER_PALETTE_ENTRIES];										//0x59700
	uint8_t pColorizeTables[12][NUMBER_PALETTE_ENTRIES];							//0x59800
	uint8_t pChannelTables[3][NUMBER_PALETTE_ENTRIES];								//0x5A400
	uint8_t unk0x5A700[14][NUMBER_PALETTE_ENTRIES];									//0x5A700
	uint8_t pBrightnessBlendTable[NUMBER_PALETTE_ENTRIES][NUMBER_PALETTE_ENTRIES];	//0x5B500
	uint8_t pDesaturateTable[NUMBER_PALETTE_ENTRIES];								//0x6B500
	uint8_t pTintColors[13][3];														//0x6B600
	uint8_t unk0x6B627[NUMBER_PALETTE_ENTRIES];										//0x6B627
	uint8_t pTintTables[12][NUMBER_PALETTE_ENTRIES];								//0x6B727
};

static_assert(sizeof(D2CMPPaletteStrc) == 0x6C327, "D2CMPPaletteStrc size mismatch");

struct D2CMPHslStrc
{
	double dHue;		//0x00 [0, 360[
	double dSat;		//0x08 [0, 1]
	double dLum;		//0x10 [0, 1]
};

#pragma pack(pop)

