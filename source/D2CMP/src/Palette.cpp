#include "Palette.h"

#include <cmath>
#include <cstring>

#include <Fog.h>

#include "D2CMP.h"


//D2CMP.0x6FE0EDB8
static const uint8_t gaTintColors[13][3] = {
	{ 0xFF, 0xFF, 0xFF },
	{ 0xFF, 0x4D, 0x4D },
	{ 0x00, 0xFF, 0x00 },
	{ 0x69, 0x69, 0xFF },
	{ 0xC7, 0xB3, 0x77 },
	{ 0x69, 0x69, 0x69 },
	{ 0x00, 0x00, 0x00 },
	{ 0xD0, 0xC2, 0x7D },
	{ 0xFF, 0xA8, 0x00 },
	{ 0xFF, 0xFF, 0x64 },
	{ 0x00, 0x80, 0x00 },
	{ 0xAE, 0x00, 0xFF },
	{ 0x00, 0xC8, 0x00 },
};

static int gaSquares[2 * NUMBER_PALETTE_ENTRIES];					//D2CMP.0x6FE94BF8 Indexed from -256 to 255
static BOOL sgbTestBackground;										//D2CMP.0x6FE953F8
static int sgnPaletteEndEntry;										//D2CMP.0x6FE953FC
static int sgnPaletteStartEntry;									//D2CMP.0x6FE95400
static uint8_t sgRawPalette[3 * NUMBER_PALETTE_ENTRIES];			//D2CMP.0x6FE95408
static uint8_t sgPaletteMask[NUMBER_PALETTE_ENTRIES];				//D2CMP.0x6FE95708
static PALETTEENTRY sgPalette[NUMBER_PALETTE_ENTRIES];				//D2CMP.0x6FE95808
static BOOL sgbPaletteLoaded;										//D2CMP.0x6FE95C08
static uint32_t sgdwTransparentColor;								//D2CMP.0x6FE95C0C
static BOOL sgbFixBlack;											//D2CMP.0x6FE95C10
static BOOL sgbUsePaletteMask;										//D2CMP.0x6FE95C14

static inline int& PALETTE_Square(int nValue)
{
	return gaSquares[nValue + NUMBER_PALETTE_ENTRIES];
}

// Inlined helper
static uint8_t PALETTE_FindClosestColor(const PALETTEENTRY* pPalette, int nRed, int nGreen, int nBlue)
{
	return D2CMP_GetClosestColor(pPalette, NUMBER_PALETTE_ENTRIES, nRed, nGreen, nBlue);
}

// Inlined helper
static void PALETTE_RgbToHsl(const PALETTEENTRY& tEntry, D2CMPHslStrc& tHsl)
{
	constexpr double dInv255 = 1.0 / 255.0;
	const double dRed = tEntry.peRed * dInv255;
	const double dGreen = tEntry.peGreen * dInv255;
	const double dBlue = tEntry.peBlue * dInv255;

	double dMax = dGreen > dBlue ? dGreen : dBlue;
	if (dRed > dMax)
	{
		dMax = dRed;
	}

	double dMin = dGreen < dBlue ? dGreen : dBlue;
	if (dRed < dMin)
	{
		dMin = dRed;
	}

	const double dSum = dMax + dMin;
	const double dLum = dSum * 0.5;
	D2_ASSERT(dLum >= 0.0f && dLum <= 1.0f);

	if (dMax == dMin)
	{
		tHsl.dHue = 0.0;
		tHsl.dSat = 0.0;
		tHsl.dLum = dLum;
		return;
	}

	const double dDelta = dMax - dMin;
	double dSat;
	if (dLum <= 0.5)
	{
		dSat = dDelta / dSum;
	}
	else
	{
		dSat = dDelta / (2.0 - dSum);
	}
	D2_ASSERT(dSat >= 0.0f && dSat <= 1.0f);

	double dHue;
	if (dRed == dMax)
	{
		dHue = (dGreen - dBlue) / dDelta;
	}
	else if (dGreen == dMax)
	{
		dHue = (dBlue - dRed) / dDelta + 2.0;
	}
	else
	{
		dHue = (dRed - dGreen) / dDelta + 4.0;
	}

	dHue *= 60.0;
	if (dHue < 0.0)
	{
		dHue += 360.0;
	}
	D2_ASSERT(dHue >= 0.0f && dHue < 360.0f);

	tHsl.dHue = dHue;
	tHsl.dSat = dSat;
	tHsl.dLum = dLum;
}

// Inlined helper
static double PALETTE_HueToRgb(double dM1, double dM2, double dHue)
{
	if (dHue > 360.0)
	{
		dHue -= 360.0;
	}

	if (dHue < 0.0)
	{
		dHue += 360.0;
	}

	if (dHue < 60.0)
	{
		return (dM2 - dM1) * dHue * (1.0 / 60.0) + dM1;
	}

	if (dHue < 180.0)
	{
		return dM2;
	}

	if (dHue < 240.0)
	{
		return (dM2 - dM1) * (240.0 - dHue) * (1.0 / 60.0) + dM1;
	}

	return dM1;
}

//D2CMP.0x6FDFA770
static void __fastcall PALETTE_HslToRgb(const D2CMPHslStrc* pHsl, PALETTEENTRY* pColors)
{
	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		const D2CMPHslStrc& tHsl = pHsl[i];
		PALETTEENTRY& tColor = pColors[i];
		if (tHsl.dSat == 0.0)
		{
			const uint8_t nGrey = (uint8_t)(int)(tHsl.dLum * 255.0);
			tColor.peRed = nGrey;
			tColor.peGreen = nGrey;
			tColor.peBlue = nGrey;
			continue;
		}

		double dM2;
		if (tHsl.dLum <= 0.5)
		{
			dM2 = (tHsl.dSat + 1.0) * tHsl.dLum;
		}
		else
		{
			dM2 = tHsl.dLum + tHsl.dSat - tHsl.dLum * tHsl.dSat;
		}
		const double dM1 = 2.0 * tHsl.dLum - dM2;

		tColor.peRed = (uint8_t)(int)(PALETTE_HueToRgb(dM1, dM2, tHsl.dHue + 120.0) * 255.0);
		tColor.peGreen = (uint8_t)(int)(PALETTE_HueToRgb(dM1, dM2, tHsl.dHue) * 255.0);
		tColor.peBlue = (uint8_t)(int)(PALETTE_HueToRgb(dM1, dM2, tHsl.dHue - 120.0) * 255.0);
	}
}

// Inlined helper
static void PALETTE_BuildTableFromHsl(const PALETTEENTRY* pPalette, const D2CMPHslStrc* pHsl, uint8_t* pTable)
{
	PALETTEENTRY aColors[NUMBER_PALETTE_ENTRIES];
	PALETTE_HslToRgb(pHsl, aColors);
	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		pTable[i] = PALETTE_FindClosestColor(pPalette, aColors[i].peRed, aColors[i].peGreen, aColors[i].peBlue);
	}
}

// Inlined helper
static void PALETTE_ShiftHue(D2CMPHslStrc& tHsl, double dShift)
{
	const double dHue = dShift + tHsl.dHue;
	tHsl.dHue = dHue;
	if (dHue > 360.0)
	{
		tHsl.dHue = dHue - 360.0;
	}
}

//D2CMP.0x6FDF8F70
static void __fastcall PALETTE_BuildAdditiveTable(D2CMPPaletteStrc* pPal)
{
	for (int nSrc = 0; nSrc < NUMBER_PALETTE_ENTRIES; ++nSrc)
	{
		const PALETTEENTRY& tSrc = pPal->pPalette[nSrc];
		for (int nDest = 0; nDest < NUMBER_PALETTE_ENTRIES; ++nDest)
		{
			const PALETTEENTRY& tDest = pPal->pPalette[nDest];
			const int nRed = tDest.peRed + tSrc.peRed;
			const int nGreen = tDest.peGreen + tSrc.peGreen;
			const int nBlue = tDest.peBlue + tSrc.peBlue;
			pPal->pAdditiveTable[nDest][nSrc] = PALETTE_FindClosestColor(pPal->pPalette, nRed < 255 ? nRed : 255, nGreen < 255 ? nGreen : 255, nBlue < 255 ? nBlue : 255);
		}
	}
}

//D2CMP.0x6FDF95C0
static void __fastcall PALETTE_BuildMultiplyTable(D2CMPPaletteStrc* pPal)
{
	for (int nSrc = 0; nSrc < NUMBER_PALETTE_ENTRIES; ++nSrc)
	{
		const PALETTEENTRY& tSrc = pPal->pPalette[nSrc];
		for (int nDest = 0; nDest < NUMBER_PALETTE_ENTRIES; ++nDest)
		{
			const PALETTEENTRY& tDest = pPal->pPalette[nDest];
			const uint8_t nRed = (uint8_t)((uint32_t)tDest.peRed * tSrc.peRed / 255);
			const uint8_t nGreen = (uint8_t)((uint32_t)tDest.peGreen * tSrc.peGreen / 255);
			const uint8_t nBlue = (uint8_t)((uint32_t)tDest.peBlue * tSrc.peBlue / 255);
			pPal->pMultiplyTable[nDest][nSrc] = PALETTE_FindClosestColor(pPal->pPalette, nRed, nGreen, nBlue);
		}
	}
}

//D2CMP.0x6FDF9740
static void __fastcall PALETTE_BuildDesaturateAndBrightnessBlendTables(D2CMPPaletteStrc* pPal)
{
	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		const PALETTEENTRY& tColor = pPal->pPalette[i];
		const uint8_t nRed = tColor.peRed - tColor.peRed / 3;
		const uint8_t nGreen = tColor.peGreen - tColor.peGreen / 3;
		const uint8_t nBlue = tColor.peBlue - tColor.peBlue / 3;
		pPal->pDesaturateTable[i] = PALETTE_FindClosestColor(pPal->pPalette, nRed, nGreen, nBlue);
	}

	for (int nSrc = 0; nSrc < NUMBER_PALETTE_ENTRIES; ++nSrc)
	{
		const PALETTEENTRY& tSrc = pPal->pPalette[nSrc];
		int nAlpha = tSrc.peRed > tSrc.peGreen ? tSrc.peRed : tSrc.peGreen;
		if (tSrc.peBlue > nAlpha)
		{
			nAlpha = tSrc.peBlue;
		}
		const int nInvAlpha = 255 - nAlpha;

		for (int nDest = 0; nDest < NUMBER_PALETTE_ENTRIES; ++nDest)
		{
			const PALETTEENTRY& tDest = pPal->pPalette[nDest];
			const uint8_t nRed = (uint8_t)((uint32_t)(tDest.peRed * nInvAlpha + tSrc.peRed * nAlpha) / 255);
			const uint8_t nGreen = (uint8_t)((uint32_t)(tDest.peGreen * nInvAlpha + tSrc.peGreen * nAlpha) / 255);
			const uint8_t nBlue = (uint8_t)((uint32_t)(tDest.peBlue * nInvAlpha + tSrc.peBlue * nAlpha) / 255);
			pPal->pBrightnessBlendTable[nDest][nSrc] = PALETTE_FindClosestColor(pPal->pPalette, nRed, nGreen, nBlue);
		}
	}
}

//D2CMP.0x6FDF9A60
static void __fastcall PALETTE_BuildTintTables(D2CMPPaletteStrc* pPal)
{
	for (int nTint = 0; nTint < 12; ++nTint)
	{
		const uint8_t* pTint = pPal->pTintColors[nTint + 1];
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			const int nIntensity = pPal->pPalette[i].peRed;
			const uint8_t nRed = (uint8_t)(pTint[0] * nIntensity / 255);
			const uint8_t nGreen = (uint8_t)(pTint[1] * nIntensity / 255);
			const uint8_t nBlue = (uint8_t)(pTint[2] * nIntensity / 255);
			pPal->pTintTables[nTint][i] = PALETTE_FindClosestColor(pPal->pPalette, nRed, nGreen, nBlue);
		}
	}
}

//D2CMP.0x6FDF9BD0
static void __fastcall PALETTE_BuildBrightenTables(D2CMPPaletteStrc* pPal)
{
	for (int nLevel = 1; nLevel <= 16; ++nLevel)
	{
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			const PALETTEENTRY& tColor = pPal->pPalette[i];
			const int nRed = tColor.peRed + (((255 - tColor.peRed) * nLevel) >> 4);
			const int nGreen = tColor.peGreen + (((255 - tColor.peGreen) * nLevel) >> 4);
			const int nBlue = tColor.peBlue + (((255 - tColor.peBlue) * nLevel) >> 4);
			pPal->pBrightenTables[nLevel - 1][i] = PALETTE_FindClosestColor(pPal->pPalette, nRed, nGreen, nBlue);
		}
	}
}

//D2CMP.0x6FDF9D20
static void __fastcall PALETTE_BuildHueTables(D2CMPPaletteStrc* pPal, const D2CMPHslStrc* pHsl)
{
	D2CMPHslStrc aHsl[NUMBER_PALETTE_ENTRIES];

	for (int nShift = 0; nShift < 24; ++nShift)
	{
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			aHsl[i] = pHsl[i];
			PALETTE_ShiftHue(aHsl[i], nShift * 15.0f);
		}
		PALETTE_BuildTableFromHsl(pPal->pPalette, aHsl, pPal->pHueShiftTables[nShift]);
	}

	for (int nShift = 0; nShift < 24; ++nShift)
	{
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			aHsl[i] = pHsl[i];
			PALETTE_ShiftHue(aHsl[i], nShift * 15.0f);
			aHsl[i].dSat = 0.5;
			aHsl[i].dLum -= 0.1f;
			if (aHsl[i].dLum < 0.0)
			{
				aHsl[i].dLum = 0.0;
			}
		}
		PALETTE_BuildTableFromHsl(pPal->pPalette, aHsl, pPal->pHueShiftDarkTables[nShift]);
	}

	for (int nShift = 0; nShift < 24; ++nShift)
	{
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			aHsl[i] = pHsl[i];
			PALETTE_ShiftHue(aHsl[i], nShift * 15.0f);
			aHsl[i].dSat = 0.5;
			aHsl[i].dLum += 0.2f;
			if (aHsl[i].dLum > 1.0)
			{
				aHsl[i].dLum = 1.0;
			}
		}
		PALETTE_BuildTableFromHsl(pPal->pPalette, aHsl, pPal->pHueShiftLightTables[nShift]);
	}

	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		aHsl[i] = pHsl[i];
		aHsl[i].dLum *= 0.5;
		aHsl[i].dSat = 0.0;
	}
	PALETTE_BuildTableFromHsl(pPal->pPalette, aHsl, pPal->pGreyDarkTable);

	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		aHsl[i] = pHsl[i];
		aHsl[i].dLum = aHsl[i].dLum * (5.0f / 6.0f) + (1.0f / 6.0f);
		aHsl[i].dSat = 0.0;
	}
	PALETTE_BuildTableFromHsl(pPal->pPalette, aHsl, pPal->pGreyLightTable);

	// Only colors with a hue in ]45, 315[ are shifted, other colors keep the grey light color
	for (int nShift = 0; nShift < 24; ++nShift)
	{
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			if (pHsl[i].dHue > 45.0 && pHsl[i].dHue < 315.0)
			{
				aHsl[i] = pHsl[i];
				PALETTE_ShiftHue(aHsl[i], nShift * 15.0f);
			}
		}
		PALETTE_BuildTableFromHsl(pPal->pPalette, aHsl, pPal->pSelectiveHueShiftTables[nShift]);
	}

	for (int nHue = 0; nHue < 12; ++nHue)
	{
		const double dHue = nHue * 30.0f;
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			aHsl[i] = pHsl[i];
			aHsl[i].dHue = dHue;
			aHsl[i].dSat = 1.0;
		}
		PALETTE_BuildTableFromHsl(pPal->pPalette, aHsl, pPal->pColorizeTables[nHue]);
	}

	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		const PALETTEENTRY& tColor = pPal->pPalette[i];
		const int nSquaredMagnitude = tColor.peRed * tColor.peRed + tColor.peGreen * tColor.peGreen + tColor.peBlue * tColor.peBlue;
		const uint8_t nMagnitude = (uint8_t)(int)sqrt((double)nSquaredMagnitude);
		pPal->pChannelTables[0][i] = PALETTE_FindClosestColor(pPal->pPalette, nMagnitude, 0, 0);
		pPal->pChannelTables[1][i] = PALETTE_FindClosestColor(pPal->pPalette, 0, nMagnitude, 0);
		pPal->pChannelTables[2][i] = PALETTE_FindClosestColor(pPal->pPalette, 0, 0, nMagnitude);
	}
}

//D2CMP.0x6FDFA9E0
static void __fastcall PALETTE_BuildLightenTable(D2CMPPaletteStrc* pPal, D2CMPHslStrc* pHsl)
{
	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		if (pHsl[i].dLum != 0.0)
		{
			pHsl[i].dLum += 0.2f;
			if (pHsl[i].dLum > 1.0)
			{
				pHsl[i].dLum = 1.0;
			}
		}
	}

	PALETTE_BuildTableFromHsl(pPal->pPalette, pHsl, pPal->pLightenTable);
}

//D2CMP.0x6FDF90E0 (#10000)
D2CMPPaletteStrc* __stdcall D2CMP_CreateD2Palette(const PALETTEENTRY* pPal)
{
	D2CMPHslStrc aHsl[NUMBER_PALETTE_ENTRIES];

	D2_ASSERT(pPal);

	D2CMPPaletteStrc* pPalette = (D2CMPPaletteStrc*)VirtualAlloc(nullptr, sizeof(D2CMPPaletteStrc), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(pPalette->pPalette, pPal, sizeof(pPalette->pPalette));

	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		PALETTE_RgbToHsl(pPalette->pPalette[i], aHsl[i]);
	}

	static const int anOpacities[3] = { 0xBF, 0x7F, 0x3F };
	for (int nTable = 0; nTable < 3; ++nTable)
	{
		const int nAlpha = anOpacities[nTable];
		const int nInvAlpha = 255 - nAlpha;
		for (int nSrc = 0; nSrc < NUMBER_PALETTE_ENTRIES; ++nSrc)
		{
			const PALETTEENTRY& tSrc = pPalette->pPalette[nSrc];
			for (int nDest = 0; nDest < NUMBER_PALETTE_ENTRIES; ++nDest)
			{
				const PALETTEENTRY& tDest = pPalette->pPalette[nDest];
				const uint8_t nRed = (uint8_t)((uint32_t)(tDest.peRed * nInvAlpha + tSrc.peRed * nAlpha) / 255);
				const uint8_t nGreen = (uint8_t)((uint32_t)(tDest.peGreen * nInvAlpha + tSrc.peGreen * nAlpha) / 255);
				const uint8_t nBlue = (uint8_t)((uint32_t)(tSrc.peBlue * nAlpha + tDest.peBlue * nInvAlpha) / 255);
				pPalette->pAlphaBlendTables[nTable][nDest][nSrc] = D2CMP_GetClosestColor(pPalette->pPalette, NUMBER_PALETTE_ENTRIES, nRed, nGreen, nBlue);
			}
		}
	}

	for (uint32_t nLevel = 1; nLevel <= 32; ++nLevel)
	{
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			const PALETTEENTRY& tColor = pPalette->pPalette[i];
			pPalette->pDarkenTables[nLevel - 1][i] = D2CMP_GetClosestColor(pPalette->pPalette, NUMBER_PALETTE_ENTRIES, (tColor.peRed * nLevel) >> 5, (tColor.peGreen * nLevel) >> 5, (tColor.peBlue * nLevel) >> 5);
		}
	}

	PALETTE_BuildBrightenTables(pPalette);
	PALETTE_BuildAdditiveTable(pPalette);
	PALETTE_BuildMultiplyTable(pPalette);
	PALETTE_BuildHueTables(pPalette, aHsl);
	PALETTE_BuildLightenTable(pPalette, aHsl);
	PALETTE_BuildDesaturateAndBrightnessBlendTables(pPalette);
	memcpy(pPalette->pTintColors, gaTintColors, sizeof(pPalette->pTintColors));
	PALETTE_BuildTintTables(pPalette);
	return pPalette;
}

//D2CMP.0x6FDFAAF0 (#10001)
D2CMPPaletteStrc* __stdcall D2CMP_CreateD2PaletteByteStream(const PALETTEENTRY* pPal, int* pSize)
{
	*pSize = sizeof(D2CMPPaletteStrc);
	return D2CMP_CreateD2Palette(pPal);
}

//D2CMP.0x6FDFAB10 (#10002)
void __stdcall D2CMP_DestroyD2Palette(D2CMPPaletteStrc* pPalette)
{
	if (pPalette)
	{
		VirtualFree(pPalette, 0, MEM_RELEASE);
	}
}

//D2CMP.0x6FDF8F60 (#10003)
void __stdcall D2CMP_UpdateD2TransparencyTable(D2CMPPaletteStrc* pPalette, int nUnused)
{
	PALETTE_BuildAdditiveTable(pPalette);
}

//D2CMP.0x6FDFAB20 (#10004)
uint8_t __stdcall D2CMP_GetClosestColor(const PALETTEENTRY* pPalette, uint32_t nPaletteSize, int nRed, int nGreen, int nBlue)
{
	uint32_t nBestDistance = 0xFFFFFFFF;
	uint32_t nBestIndex = 0;
	for (uint32_t i = 0; i < nPaletteSize; ++i)
	{
		const int nDiffRed = pPalette[i].peRed - nRed;
		const int nDiffGreen = pPalette[i].peGreen - nGreen;
		const int nDiffBlue = pPalette[i].peBlue - nBlue;
		const uint32_t nDistance = nDiffBlue * nDiffBlue + nDiffGreen * nDiffGreen + nDiffRed * nDiffRed;
		if (nDistance < nBestDistance)
		{
			nBestIndex = i;
			nBestDistance = nDistance;
		}
	}
	return (uint8_t)nBestIndex;
}

//D2CMP.0x6FDFABA0 (#10005)
uint8_t __stdcall D2CMP_GetFurthestColor(const PALETTEENTRY* pPalette, uint32_t nPaletteSize, int nRed, int nGreen, int nBlue)
{
	uint32_t nBestDistance = 0;
	uint32_t nBestIndex = 0;
	for (uint32_t i = 0; i < nPaletteSize; ++i)
	{
		const int nDiffRed = pPalette[i].peRed - nRed;
		const int nDiffGreen = pPalette[i].peGreen - nGreen;
		const int nDiffBlue = pPalette[i].peBlue - nBlue;
		const uint32_t nDistance = nDiffBlue * nDiffBlue + nDiffGreen * nDiffGreen + nDiffRed * nDiffRed;
		if (nDistance > nBestDistance)
		{
			nBestIndex = i;
			nBestDistance = nDistance;
		}
	}
	return (uint8_t)nBestIndex;
}

//D2CMP.0x6FDFAC20 (#10009)
void __stdcall D2CMP_PaletteSetTransparency(PALETTEENTRY tColor)
{
	sgdwTransparentColor = (tColor.peRed << 16) | (tColor.peGreen << 8) | tColor.peBlue;
}

//D2CMP.0x6FDFAC50 (#10006)
BOOL __stdcall D2CMP_PaletteInit(const char* pszPalette, int PaletteStartEntry, int PaletteEndEntry)
{
	D2_ASSERT(pszPalette != NULL);
	D2_ASSERT(PaletteStartEntry <= PaletteEndEntry);
	D2_ASSERT(PaletteStartEntry >= 0);
	D2_ASSERT(PaletteEndEntry < NUMBER_PALETTE_ENTRIES);

	sgnPaletteEndEntry = PaletteEndEntry;
	sgnPaletteStartEntry = 1;
	for (int i = -NUMBER_PALETTE_ENTRIES; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		PALETTE_Square(i) = i * i;
	}
	sgdwTransparentColor = 0;

	if (!lstrlenA(pszPalette))
	{
		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			sgPalette[i].peRed = (uint8_t)i;
			sgPalette[i].peGreen = (uint8_t)i;
			sgPalette[i].peBlue = (uint8_t)i;
		}
		sgbPaletteLoaded = TRUE;
		return TRUE;
	}

	HANDLE hFile = CreateFileA(pszPalette, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("Unable to open ");
		OutputDebugStringA(pszPalette);
		OutputDebugStringA("\n");
		return FALSE;
	}

	DWORD dwFileSizeHigh = 0;
	if (GetFileSize(hFile, &dwFileSizeHigh) == sizeof(sgRawPalette))
	{
		// .dat palette, stored as BGR
		DWORD dwBytesRead = 0;
		ReadFile(hFile, sgRawPalette, sizeof(sgRawPalette), &dwBytesRead, nullptr);
		if (dwBytesRead != sizeof(sgRawPalette))
		{
			sgbPaletteLoaded = FALSE;
			CloseHandle(hFile);
			return sgbPaletteLoaded;
		}

		for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
		{
			sgPalette[i].peBlue = sgRawPalette[3 * i + 0];
			sgPalette[i].peGreen = sgRawPalette[3 * i + 1];
			sgPalette[i].peRed = sgRawPalette[3 * i + 2];
		}

		sgbPaletteLoaded = TRUE;
		CloseHandle(hFile);
		return sgbPaletteLoaded;
	}

	// Try to read the palette of a .pcx file
	CloseHandle(hFile);
	hFile = CreateFileA(pszPalette, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("Unable to open ");
		OutputDebugStringA(pszPalette);
		OutputDebugStringA("\n");
		sgbPaletteLoaded = FALSE;
		return FALSE;
	}

	uint8_t pPcxHeader[128] = {};
	DWORD dwBytesRead = 0;
	ReadFile(hFile, pPcxHeader, sizeof(pPcxHeader), &dwBytesRead, nullptr);
	if (dwBytesRead != sizeof(pPcxHeader) || pPcxHeader[0] != 0x0A || pPcxHeader[1] != 5 || pPcxHeader[3] != 8)
	{
		OutputDebugStringA("File is not a valid 256-color PCX file.\n");
		CloseHandle(hFile);
		sgbPaletteLoaded = FALSE;
		return FALSE;
	}

	uint8_t pPcxPalette[1 + 3 * NUMBER_PALETTE_ENTRIES] = {};
	SetFilePointer(hFile, -(LONG)sizeof(pPcxPalette), nullptr, FILE_END);
	ReadFile(hFile, pPcxPalette, sizeof(pPcxPalette), &dwBytesRead, nullptr);
	if (dwBytesRead != sizeof(pPcxPalette) || pPcxPalette[0] != 0x0C)
	{
		OutputDebugStringA("Unable to extract palette from\n");
		CloseHandle(hFile);
		sgbPaletteLoaded = FALSE;
		return FALSE;
	}

	for (int i = 0; i < NUMBER_PALETTE_ENTRIES; ++i)
	{
		sgPalette[i].peRed = pPcxPalette[1 + 3 * i + 0];
		sgPalette[i].peGreen = pPcxPalette[1 + 3 * i + 1];
		sgPalette[i].peBlue = pPcxPalette[1 + 3 * i + 2];
	}

	CloseHandle(hFile);
	sgbPaletteLoaded = TRUE;
	return TRUE;
}

//D2CMP.0x6FDFAFD0 (#10010)
void __stdcall D2CMP_PaletteTestBackground(BOOL bTestBackground)
{
	sgbTestBackground = bTestBackground;
}

//D2CMP.0x6FDFAFE0 (#10007)
uint8_t __stdcall D2CMP_Palette24BitTo8BitPixel(uint8_t nBlue, uint8_t nGreen, uint8_t nRed)
{
	uint32_t nBestDistance = 0x7FFFFFFF;
	int nBestIndex = 0;
	for (int i = sgnPaletteStartEntry; i <= sgnPaletteEndEntry; ++i)
	{
		if (sgbUsePaletteMask && !sgPaletteMask[i])
		{
			continue;
		}

		if (sgbTestBackground && sgdwTransparentColor == (uint32_t)((nBlue << 16) | (nGreen << 8) | nRed))
		{
			return 0;
		}

		const uint32_t nDistance = PALETTE_Square(nBlue - sgPalette[i].peBlue) + PALETTE_Square(nGreen - sgPalette[i].peGreen) + PALETTE_Square(nRed - sgPalette[i].peRed);
		if (nDistance < nBestDistance)
		{
			nBestDistance = nDistance;
			nBestIndex = i;
		}
	}

	return (uint8_t)nBestIndex;
}

//D2CMP.0x6FDFB0D0 (#10008)
BOOL __stdcall D2CMP_Palette24BitTo8BitImage(const uint8_t* pSrc, uint8_t* pDest, uint32_t nPixels, D2CMPColorConvertCallback pfnConvert)
{
	if (!sgbPaletteLoaded)
	{
		return FALSE;
	}

	D2CMPColorConvertCallback pfnPixelConvert = pfnConvert ? pfnConvert : D2CMP_Palette24BitTo8BitPixel;
	for (uint32_t i = 0; i < nPixels; ++i)
	{
		uint8_t nBlue = pSrc[0];
		uint8_t nGreen = pSrc[1];
		uint8_t nRed = pSrc[2];
		pSrc += 3;

		if (sgbFixBlack && nBlue <= 10 && nGreen <= 10 && nRed <= 10)
		{
			nBlue = 4;
			nRed = 0;
			nGreen = 0;
		}

		*pDest++ = pfnPixelConvert(nBlue, nGreen, nRed);
	}

	return FALSE;
}

//D2CMP.0x6FDFB170 (#10011)
void __stdcall D2CMP_PaletteFixBlack(BOOL bFixBlack)
{
	sgbFixBlack = bFixBlack;
}

//D2CMP.0x6FDFB180 (#10012)
void __stdcall D2CMP_PaletteSetMask(const uint8_t* pMask)
{
	sgbUsePaletteMask = TRUE;
	memcpy(sgPaletteMask, pMask, sizeof(sgPaletteMask));
}
