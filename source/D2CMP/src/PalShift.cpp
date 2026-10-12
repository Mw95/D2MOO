#include "PalShift.h"

#include <cstring>

#include <Archive.h>
#include <Fog.h>

#include "D2CMP.h"


static uint8_t gaPalShiftTransforms[PALSHIFT_NUM_PALETTES][PALSHIFT_NUM_ACTS * PALSHIFT_NUM_TRANSFORMS][PALSHIFT_TRANSFORM_SIZE];	//D2CMP.0x6FE95C18
static int gnPalShiftAct = 1;	//D2CMP.0x6FE0EF64

//D2CMP.0x6FDFB5C0
static void __fastcall PALSHIFT_LoadPalette(const char* szName, int nPalette)
{
	char szPath[256];
	strcpy(szPath, "Data\\Global\\Items\\Palette\\");
	strcat(szPath, szName);
	strcat(szPath, ".dat");

	const int nSize = PALSHIFT_NUM_TRANSFORMS * PALSHIFT_TRANSFORM_SIZE;
	HSFILE hFile = nullptr;
	if (!ARCHIVE_OpenFile(nullptr, szPath, &hFile, TRUE))
	{
		D2_CHECK(0);
		memset(gaPalShiftTransforms[nPalette], 0x00, nSize);
		return;
	}

	ARCHIVE_ReadFileToBuffer(nullptr, hFile, gaPalShiftTransforms[nPalette], nSize);
	ARCHIVE_CloseFile(nullptr, hFile);
}

//D2CMP.0x6FDFB1B0 (#10096)
void __stdcall D2CMP_PalShiftInit()
{
	PALSHIFT_LoadPalette("grey", 1);
	PALSHIFT_LoadPalette("grey2", 2);
	PALSHIFT_LoadPalette("gold", 3);
	PALSHIFT_LoadPalette("brown", 4);
	PALSHIFT_LoadPalette("greybrown", 5);
	PALSHIFT_LoadPalette("invgrey", 6);
	PALSHIFT_LoadPalette("invgrey2", 7);
	PALSHIFT_LoadPalette("invgreybrown", 8);
}

//D2CMP.0x6FDFB740 (#10097)
void __stdcall D2CMP_PalShiftSetAct(int nAct)
{
	if (nAct > 0 && nAct <= PALSHIFT_NUM_ACTS)
	{
		gnPalShiftAct = nAct;
	}
}

//D2CMP.0x6FDFB760 (#10098)
uint8_t* __stdcall D2CMP_PalShiftGetTransform(int nPalette, int nTransform)
{
	if (nPalette >= PALSHIFT_NUM_PALETTES || nTransform >= PALSHIFT_NUM_TRANSFORMS || nPalette == 0)
	{
		return nullptr;
	}

	// Gold and brown are not supported
	if (nPalette > 2 && nPalette <= 4)
	{
		return nullptr;
	}

	return gaPalShiftTransforms[nPalette][nTransform];
}
