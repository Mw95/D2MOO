#include "CelCmp.h"

#include <cstring>

#include <Fog.h>

#include "FastCmp.h"
#include "Raw.h"

//D2CMP.0x6FE09550
static const int gaNormalDirToFileDir[8][32] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 5, 6, 7, 0, 2, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 5, 6, 7, 0, 2, 1, 3, 8, 9, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 5, 6, 7, 0, 2, 1, 3, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

//D2CMP.0x6FE0A0D0
static const int gaGameDirToFileDir[8][64] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4 },
	{ 4, 4, 8, 8, 8, 8, 0, 0, 0, 0, 9, 9, 9, 9, 5, 5, 5, 5, 10, 10, 10, 10, 1, 1, 1, 1, 11, 11, 11, 11, 6, 6, 6, 6, 12, 12, 12, 12, 2, 2, 2, 2, 13, 13, 13, 13, 7, 7, 7, 7, 14, 14, 14, 14, 3, 3, 3, 3, 15, 15, 15, 15, 4, 4 },
	{ 4, 16, 16, 8, 8, 17, 17, 0, 0, 18, 18, 9, 9, 19, 19, 5, 5, 20, 20, 10, 10, 21, 21, 1, 1, 22, 22, 11, 11, 23, 23, 6, 6, 24, 24, 12, 12, 25, 25, 2, 2, 26, 26, 13, 13, 27, 27, 7, 7, 28, 28, 14, 14, 29, 29, 3, 3, 30, 30, 15, 15, 31, 31, 4 },
	{ 4, 32, 16, 33, 8, 34, 17, 35, 0, 36, 18, 37, 9, 38, 19, 39, 5, 40, 20, 41, 10, 42, 21, 43, 1, 44, 22, 45, 11, 46, 23, 47, 6, 48, 24, 49, 12, 50, 25, 51, 2, 52, 26, 53, 13, 54, 27, 55, 7, 56, 28, 57, 14, 58, 29, 59, 3, 60, 30, 61, 15, 62, 31, 63 },
};

//D2CMP.0x6FE0A8D0
static const int gaGameDirToShadowGameDir[8][64] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 24, 24, 24, 24, 24, 24, 24, 24, 32, 32, 32, 32, 32, 32, 32, 32, 40, 40, 40, 40, 40, 40, 40, 40, 48, 48, 48, 48, 48, 48, 48, 48, 56, 56, 56, 56, 56, 56, 56, 56, 0, 0, 0, 0 },
	{ 4, 4, 8, 8, 8, 8, 12, 12, 12, 12, 16, 16, 16, 16, 20, 20, 20, 20, 24, 24, 24, 24, 28, 28, 28, 28, 32, 32, 32, 32, 36, 36, 36, 36, 40, 40, 40, 40, 44, 44, 44, 44, 48, 48, 48, 48, 52, 52, 52, 52, 56, 56, 56, 56, 60, 60, 60, 60, 0, 0, 0, 0, 4, 4 },
	{ 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14, 16, 16, 18, 18, 20, 20, 22, 22, 24, 24, 26, 26, 28, 28, 30, 30, 32, 32, 34, 34, 36, 36, 38, 38, 40, 40, 42, 42, 44, 44, 46, 46, 48, 48, 50, 50, 52, 52, 54, 54, 56, 56, 58, 58, 60, 60, 62, 62, 0, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

//D2CMP.0x6FE0B0D0
static const int gaGameDirToNormalDir[8][64] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 0, 0 },
	{ 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 0 },
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63 },
};

//D2CMP.0x6FE0B8D0
static const uint8_t gaConvertDir8To4[8] = { 1, 1, 3, 3, 5, 5, 7, 7 };
//D2CMP.0x6FE0B8D8
static const uint8_t gaConvertDir16To8[16] = { 0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14 };
//D2CMP.0x6FE0B8E8
static const uint8_t gaConvertShadowDir8To4[8] = { 3, 3, 5, 5, 7, 7, 1, 1 };
//D2CMP.0x6FE0B8F0
static const uint8_t gaConvertShadowDir16To8[16] = { 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14, 0, 0 };

//D2CMP.0x6FE091B0
static const CelEncodeFunc sgpfnEncodeFunc[NUM_CELFORMATS] = { FASTCMP_EncodeCelList, nullptr };
//D2CMP.0x6FE091B8
static const CelDrawFunc sgpfnDecodeFunc[NUM_CELFORMATS] = { FASTCMP_DrawCel, nullptr };
//D2CMP.0x6FE091C0
static const CelConvert24To8Func sgpfnConvert24To8Func[NUM_CELFORMATS] = { FASTCMP_ConvertCelFile24To8, nullptr };
//D2CMP.0x6FE091C8
static const CelTransformFunc sgpfnTransformFunc[NUM_CELFORMATS] = { FASTCMP_TransformCel, nullptr };


// Global list of the cel compression lists, originally a TSHashTable<CELLIST, HASHKEY_NONE>
struct D2CelListsStrc
{
	D2CelCompressListStrc* pFirst;
	CRITICAL_SECTION tLock;					//D2CMP.0x6FE12CF8

	D2CelListsStrc()
	{
		pFirst = nullptr;
		InitializeCriticalSection(&tLock);
	}

	~D2CelListsStrc()
	{
		DeleteCriticalSection(&tLock);
		while (pFirst)
		{
			D2CelCompressListStrc* pNext = pFirst->pNext;
			while (pFirst->pFirstImage)
			{
				D2CelCompressImageStrc* pNextImage = pFirst->pFirstImage->pNext;
				D2_FREE(pFirst->pFirstImage);
				pFirst->pFirstImage = pNextImage;
			}
			D2_FREE(pFirst);
			pFirst = pNext;
		}
	}
};

static D2CelListsStrc sgtCelLists;			//D2CMP.0x6FE12CA8
static uint32_t sgnLastCelListHandle;		//D2CMP.0x6FE12CF0
static BOOL sgbCelListHandleWrapped;		//D2CMP.0x6FE12CF4
static CelHardwareFreeCallback sgpfnHardwareFreeCallback;	//D2CMP.0x6FE12D10

//D2CMP.0x6FDF1000
void __cdecl CELCMP_InitCelLists()
{
	// Construction of sgtCelLists, done by the C++ runtime
}

// Inlined helper (D2CMP.0x6FE00346)
int GetFirstBit(uint32_t nValue)
{
	if (!nValue)
	{
		return 0;
	}

	int nBit = 0;
	while (!(nValue & (1 << nBit)))
	{
		++nBit;
	}
	return nBit + 1;
}

// Inlined helper
static int BITCOUNT(uint32_t nValue)
{
	int nCount = 0;
	for (; nValue; nValue >>= 1)
	{
		nCount += nValue & 1;
	}
	return nCount;
}

// Inlined helper
static D2CelCompressListStrc* CELCMP_FindList(uint32_t hCelList)
{
	for (D2CelCompressListStrc* pList = sgtCelLists.pFirst; pList; pList = pList->pNext)
	{
		if (pList->hCelList == hCelList)
		{
			return pList;
		}
	}
	return nullptr;
}

// Inlined helper
static D2GfxCellStrc* CELCMP_GetCel(D2CellFileStrc* pFile, int nIndex)
{
	return pFile->pGfxCells[nIndex];
}

//D2CMP.0x6FDF11D0 (#10017)
int __stdcall D2CMP_CelNormalDirToFileDir(int nDirection, int nDirections)
{
	return gaNormalDirToFileDir[GetFirstBit(nDirections)][nDirection];
}

//D2CMP.0x6FDF11F0 (#10018)
int __stdcall D2CMP_CelGameDirToFileDir(int nGameDirection, int nDirections)
{
	return gaGameDirToFileDir[GetFirstBit(nDirections)][nGameDirection];
}

//D2CMP.0x6FDF1210 (#10019)
int __stdcall D2CMP_CelConvertDir(uint32_t nDirection, uint32_t nStartDirs, int nEndDirs, BOOL bShadow)
{
	D2_ASSERT(nDirection < nStartDirs);

	if (nStartDirs == 8 && nEndDirs == 4)
	{
		return bShadow ? gaConvertShadowDir8To4[nDirection] : gaConvertDir8To4[nDirection];
	}

	if (nStartDirs == 16 && nEndDirs == 8)
	{
		return bShadow ? gaConvertShadowDir16To8[nDirection] : gaConvertDir16To8[nDirection];
	}

	FOG_DisplayHalt("Could not convert direction!", __FILE__, __LINE__);
	exit(-1);
}

//D2CMP.0x6FDF12B0 (#10020)
int __stdcall D2CMP_CelConvertBlock(int nStartDirs, int nEndDirs)
{
	if (nStartDirs == 4 && nEndDirs == 8)
	{
		return 0;
	}

	if (nStartDirs == 8 && nEndDirs == 16)
	{
		return 1;
	}

	FOG_DisplayHalt("Could not convert direction!", __FILE__, __LINE__);
	exit(-1);
}

//D2CMP.0x6FDF1300 (#10021)
int __stdcall D2CMP_CelGameDirToShadowGameDir(uint32_t nGameDirection, uint32_t nLevelOfRotation)
{
	D2_ASSERT(nGameDirection < CELFILE_NUMGAMEDIRECTIONS);
	D2_ASSERT(GetFirstBit( nLevelOfRotation ) < 8);
	D2_ASSERT(BITCOUNT( nLevelOfRotation ) == 1);
	return gaGameDirToShadowGameDir[GetFirstBit(nLevelOfRotation)][nGameDirection];
}

//D2CMP.0x6FDF1400 (#10022)
int __stdcall D2CMP_CelGameDirToNormalDir(uint32_t nGameDirection, uint32_t nLevelOfRotation)
{
	D2_ASSERT(nGameDirection < CELFILE_NUMGAMEDIRECTIONS);
	D2_ASSERT(GetFirstBit( nLevelOfRotation ) < 8);
	D2_ASSERT(BITCOUNT( nLevelOfRotation ) == 1);
	return gaGameDirToNormalDir[GetFirstBit(nLevelOfRotation)][nGameDirection];
}

//D2CMP.0x6FDF14E0 (#10013)
uint32_t __stdcall D2CMP_CelCompressCreate(uint32_t format, uint32_t dwNumDirections, const uint32_t* pTransparentColor, BOOL b24Bit)
{
	D2_ASSERT(BITCOUNT( dwNumDirections ) == 1);
	D2_ASSERT(dwNumDirections <= 32);
	D2_ASSERT(format < NUM_CELFORMATS);

	EnterCriticalSection(&sgtCelLists.tLock);

	// Find an unused handle
	while (true)
	{
		++sgnLastCelListHandle;
		if (!sgnLastCelListHandle)
		{
			sgbCelListHandleWrapped = TRUE;
			continue;
		}

		if (!sgbCelListHandleWrapped || !CELCMP_FindList(sgnLastCelListHandle))
		{
			break;
		}
	}

	const uint32_t hCelList = sgnLastCelListHandle;
	D2CelCompressListStrc* pList = D2_ALLOC_STRC(D2CelCompressListStrc);
	memset(pList, 0x00, sizeof(*pList));
	pList->hCelList = hCelList;
	pList->pNext = sgtCelLists.pFirst;
	sgtCelLists.pFirst = pList;

	pList->dwNumDirections = dwNumDirections;
	pList->eFormat = format;
	pList->nImages = 0;
	pList->dwFlags = 0;
	if (b24Bit)
	{
		pList->dwFlags = CELFILE_24BIT;
		if (pTransparentColor)
		{
			pList->dwTransparentColor = *pTransparentColor;
		}
	}

	LeaveCriticalSection(&sgtCelLists.tLock);
	return hCelList;
}

//D2CMP.0x6FDF1670 (#10015)
void __stdcall D2CMP_CelCompressAddImage(uint32_t hCelList, const uint8_t* pImage, uint32_t dwImageByteStride, uint32_t dwPixelHeight, uint32_t dwPixelWidth, int nXOffset, int nYOffset, uint32_t dwFlags)
{
	D2_ASSERT(dwPixelHeight && dwPixelWidth);
	D2_ASSERT(dwImageByteStride >= dwPixelWidth);

	EnterCriticalSection(&sgtCelLists.tLock);

	D2CelCompressListStrc* pList = CELCMP_FindList(hCelList);
	if (!pList)
	{
		// The original game would crash here
		LeaveCriticalSection(&sgtCelLists.tLock);
		return;
	}

	D2CelCompressImageStrc* pImageEntry = D2_ALLOC_STRC(D2CelCompressImageStrc);
	memset(pImageEntry, 0x00, sizeof(*pImageEntry));
	if (pList->pLastImage)
	{
		pList->pLastImage->pNext = pImageEntry;
	}
	else
	{
		pList->pFirstImage = pImageEntry;
	}
	pList->pLastImage = pImageEntry;
	++pList->nImages;

	pImageEntry->dwHeight = dwPixelHeight;
	pImageEntry->dwSize = dwPixelHeight * dwPixelWidth;
	pImageEntry->dwWidth = dwPixelWidth;
	pImageEntry->nXOffset = nXOffset;
	pImageEntry->nYOffset = nYOffset;
	pImageEntry->dwFlags = dwFlags;

	uint32_t dwRowSize = dwPixelWidth;
	if (pList->dwFlags & CELFILE_24BIT)
	{
		dwRowSize *= 3;
	}

	pImageEntry->pData = (uint8_t*)D2_ALLOC(dwRowSize * dwPixelHeight);
	for (uint32_t nY = 0; nY < dwPixelHeight; ++nY)
	{
		memcpy(&pImageEntry->pData[nY * dwRowSize], &pImage[nY * dwImageByteStride], dwRowSize);
	}

	LeaveCriticalSection(&sgtCelLists.tLock);
}

//D2CMP.0x6FDF17E0 (#10014)
void __stdcall D2CMP_CelCompressDestroy(uint32_t hCelList)
{
	EnterCriticalSection(&sgtCelLists.tLock);

	D2CelCompressListStrc* pList = CELCMP_FindList(hCelList);
	if (!pList)
	{
		// The original game would crash here
		LeaveCriticalSection(&sgtCelLists.tLock);
		return;
	}

	for (D2CelCompressImageStrc* pImage = pList->pFirstImage; pImage; pImage = pImage->pNext)
	{
		D2_FREE(pImage->pData);
	}

	while (pList->pFirstImage)
	{
		D2CelCompressImageStrc* pNext = pList->pFirstImage->pNext;
		D2_FREE(pList->pFirstImage);
		pList->pFirstImage = pNext;
	}
	pList->pLastImage = nullptr;

	D2CelCompressListStrc** ppList = &sgtCelLists.pFirst;
	while (*ppList != pList)
	{
		ppList = &(*ppList)->pNext;
	}
	*ppList = pList->pNext;
	D2_FREE(pList);

	LeaveCriticalSection(&sgtCelLists.tLock);
}

//D2CMP.0x6FDF18D0 (#10016)
uint32_t __stdcall D2CMP_CelCompressCreateCelFile(uint32_t hCelList, D2CellFileStrc** ppCelFile)
{
	EnterCriticalSection(&sgtCelLists.tLock);

	D2CelCompressListStrc* pList = CELCMP_FindList(hCelList);
	*ppCelFile = nullptr;

	if (!pList || !pList->nImages)
	{
		// Note: the original game does not release the lock here
		LeaveCriticalSection(&sgtCelLists.tLock);
		return 0x85200001;
	}

	if (pList->nImages % pList->dwNumDirections)
	{
		// Note: the original game does not release the lock here
		LeaveCriticalSection(&sgtCelLists.tLock);
		return 0x85200002;
	}

	D2CellFileStrc* pCelFile = (D2CellFileStrc*)D2_ALLOC(offsetof(D2CellFileStrc, pGfxCells) + sizeof(D2GfxCellStrc*) * pList->nImages);
	pCelFile->dwVersion = CELFILE_VERSION;
	pCelFile->dwFlags = pList->dwFlags;
	pCelFile->eFormat = pList->eFormat;
	pCelFile->nDirections = pList->dwNumDirections;
	pCelFile->nFrames = pList->nImages / pList->dwNumDirections;

	if (pList->dwFlags & CELFILE_24BIT)
	{
		RAW_CreateCels(pList, pCelFile);
		pCelFile->dwTermination = pList->dwTransparentColor;
	}
	else
	{
		sgpfnEncodeFunc[pList->eFormat](pList, pCelFile);
	}

	LeaveCriticalSection(&sgtCelLists.tLock);
	*ppCelFile = pCelFile;
	return 0;
}

//D2CMP.0x6FDF1A00 (#10029)
void __stdcall D2CMP_CelFileHalve(D2CellFileStrc* hFile, int nUnused)
{
	D2_ASSERT(hFile);
}

//D2CMP.0x6FDF1A30 (#10025)
BOOL __stdcall D2CMP_CelFileConvert24To8(D2CellFileStrc* pFile, D2CellFileStrc** ppOutFile, uint32_t dwTransparentColor, D2CMPColorConvertCallback pfnConvert)
{
	D2_ASSERT(pFile->dwFlags & CELFILE_24BIT);

	D2CellFileStrc* pNewFile = (D2CellFileStrc*)D2_ALLOC(offsetof(D2CellFileStrc, pGfxCells) + sizeof(D2GfxCellStrc*) * pFile->nDirections * pFile->nFrames);
	pNewFile->dwVersion = CELFILE_VERSION;
	pNewFile->dwFlags = pFile->dwFlags & ~(CELFILE_SERIALIZED | CELFILE_HARDWARE | CELFILE_24BIT);
	pNewFile->nDirections = pFile->nDirections;
	pNewFile->nFrames = pFile->nFrames;
	pNewFile->eFormat = CELFORMAT_DC6;
	sgpfnConvert24To8Func[pFile->eFormat](pFile, pNewFile, dwTransparentColor, pfnConvert);
	*ppOutFile = pNewFile;
	return TRUE;
}

//D2CMP.0x6FDF1AD0 (#10030)
void __stdcall D2CMP_CelFileConvertOldToNew(D2OldCellFileStrc* pOldFile, D2CellFileStrc** ppNewFile, int* pSize)
{
	D2_ASSERT(pOldFile->dwFlags & CELFILE_SERIALIZED);
	D2_ASSERT(pOldFile->dwVersion == ( CELFILE_VERSION - 1 ));

	pOldFile->dwFlags |= CELFILE_HARDWARE;

	const int nCels = pOldFile->nFrames * pOldFile->nDirections;
	for (int i = 0; i < nCels; ++i)
	{
		pOldFile->pGfxCells[i] = (D2OldGfxCellStrc*)((uint8_t*)pOldFile + (uintptr_t)pOldFile->pGfxCells[i]);
		D2OldGfxCellStrc* pOldCel = pOldFile->pGfxCells[i];
		if (pOldCel->dwHardwareDataSize)
		{
			pOldCel->pHardwareData += (uintptr_t)pOldFile;
		}
		else
		{
			pOldCel->pHardwareData = nullptr;
		}
	}

	int nSize = offsetof(D2CellFileStrc, pGfxCells) + sizeof(D2GfxCellStrc*) * nCels;
	for (int i = 0; i < nCels; ++i)
	{
		nSize += pOldFile->pGfxCells[i]->dwLength + pOldFile->pGfxCells[i]->dwHardwareDataSize + offsetof(D2GfxCellStrc, pPixels) + 3;
	}

	uint8_t* pBuffer = (uint8_t*)D2_ALLOC(nSize);
	D2CellFileStrc* pNewFile = (D2CellFileStrc*)pBuffer;
	pNewFile->dwVersion = CELFILE_VERSION;
	pNewFile->dwFlags = (pOldFile->dwFlags & CELFILE_24BIT) ? (CELFILE_SERIALIZED | CELFILE_24BIT) : CELFILE_SERIALIZED;
	pNewFile->eFormat = 0;
	pNewFile->dwTermination = 0;
	pNewFile->nDirections = pOldFile->nDirections;
	pNewFile->nFrames = pOldFile->nFrames;

	uint8_t* pCursor = (uint8_t*)&pNewFile->pGfxCells[nCels];
	for (int i = 0; i < nCels; ++i)
	{
		D2OldGfxCellStrc* pOldCel = pOldFile->pGfxCells[i];
		D2GfxCellStrc* pNewCel = (D2GfxCellStrc*)pCursor;
		pNewFile->dwGfxCellOffsets[i] = pCursor - pBuffer;

		pNewCel->dwFlags = pOldCel->dwFlags;
		pNewCel->dwWidth = pOldCel->dwWidth;
		pNewCel->dwHeight = pOldCel->dwHeight;
		pNewCel->nXOffset = pOldCel->nXOffset;
		pNewCel->nYOffset = pOldCel->nYOffset;
		pNewCel->dwHardwareDataSize = pOldCel->dwHardwareDataSize;
		pNewCel->dwLength = pOldCel->dwLength;
		memcpy(pNewCel->pPixels, pOldCel->pPixels, pOldCel->dwLength);
		pCursor += pNewCel->dwLength + offsetof(D2GfxCellStrc, pPixels) + 3;

		if (pOldCel->pHardwareData)
		{
			// Note: the original game copies from the address of the pointer instead of the hardware data
			memcpy(pCursor, &pOldCel->pHardwareData, pOldCel->dwHardwareDataSize);
			pNewCel->dwCellNodeOffset = pCursor - pBuffer;
			pCursor += pOldCel->dwHardwareDataSize;
		}
		else
		{
			pNewCel->dwCellNodeOffset = 0;
		}
	}

	*ppNewFile = pNewFile;
	*pSize = nSize;
}

//D2CMP.0x6FDF1CC0 (#10026)
void __stdcall D2CMP_CelFileIteratePixels(D2CellFileStrc* pFile, D2CMPPixelCallback pfnCallback)
{
	D2_ASSERT(pFile->dwFlags & CELFILE_24BIT);

	for (int nDirection = 0; nDirection < pFile->nDirections; ++nDirection)
	{
		for (int nFrame = 0; nFrame < pFile->nFrames; ++nFrame)
		{
			RAW_IteratePixels(CELCMP_GetCel(pFile, nFrame + nDirection * pFile->nFrames), pfnCallback, pFile->dwTermination);
		}
	}
}

//D2CMP.0x6FDF1D30 (#10023)
BOOL __stdcall D2CMP_CelFileSerialize(D2CellFileStrc* pFile, void** ppData, int* pSize)
{
	const int nCels = pFile->nFrames * pFile->nDirections;
	int nSize = offsetof(D2CellFileStrc, pGfxCells) + sizeof(D2GfxCellStrc*) * nCels;
	for (int i = 0; i < nCels; ++i)
	{
		nSize += pFile->pGfxCells[i]->dwLength + pFile->pGfxCells[i]->dwHardwareDataSize + offsetof(D2GfxCellStrc, pPixels) + 3;
	}

	uint8_t* pBuffer = (uint8_t*)D2_ALLOC(nSize);
	D2CellFileStrc* pNewFile = (D2CellFileStrc*)pBuffer;
	memcpy(pNewFile, pFile, sizeof(D2CellFileStrc));
	pNewFile->dwFlags = (pNewFile->dwFlags & ~CELFILE_HARDWARE) | CELFILE_SERIALIZED;

	D2GfxCellNodeStrc* pHardwareDataToFree = nullptr;
	uint8_t* pCursor = (uint8_t*)&pNewFile->pGfxCells[nCels];
	for (int i = 0; i < nCels; ++i)
	{
		D2GfxCellStrc* pCel = pFile->pGfxCells[i];
		D2GfxCellStrc* pNewCel = (D2GfxCellStrc*)pCursor;
		pNewFile->dwGfxCellOffsets[i] = pCursor - pBuffer;

		const int nCelSize = pCel->dwLength + offsetof(D2GfxCellStrc, pPixels) + 3;
		memcpy(pNewCel, pCel, nCelSize);
		pCursor += nCelSize;

		if (pCel->pCellNode && pCel->pCellNode->pData)
		{
			memcpy(pCursor, pCel->pCellNode->pData, pCel->dwHardwareDataSize);
			if (i == 0)
			{
				pHardwareDataToFree = pFile->pGfxCells[0]->pCellNode;
			}
		}

		pNewCel->dwCellNodeOffset = pCursor - pBuffer;
		pCursor += pCel->dwHardwareDataSize;
	}

	if (pHardwareDataToFree)
	{
		D2_FREE(pHardwareDataToFree);
	}

	*ppData = pNewFile;
	*pSize = nSize;
	return TRUE;
}

//D2CMP.0x6FDF1EA0 (#10024)
void __stdcall D2CMP_CelFileNormalize(D2CellFileStrc* pFile, D2CellFileStrc** ppOutFile, const char* szFile, int nLine, int nSpecVersion, int nUnused)
{
	if (!pFile)
	{
		return;
	}

	D2_ASSERT(pFile->dwFlags & CELFILE_SERIALIZED);
	if (nSpecVersion == -1)
	{
		D2_ASSERT(pFile->dwVersion == CELFILE_VERSION);
	}
	else
	{
		D2_ASSERT(pFile->dwVersion == (DWORD)nSpecVersion);
	}

	if (pFile->dwFlags & CELFILE_HARDWARE)
	{
		return;
	}

	pFile->dwFlags |= CELFILE_HARDWARE;

	const int nCels = pFile->nFrames * pFile->nDirections;
	D2GfxCellNodeStrc* pCellNodes = (D2GfxCellNodeStrc*)D2_ALLOC(sizeof(D2GfxCellNodeStrc) * nCels);
	memset(pCellNodes, 0x00, sizeof(D2GfxCellNodeStrc) * nCels);
	for (int i = 0; i < nCels; ++i)
	{
		pFile->pGfxCells[i] = (D2GfxCellStrc*)((uint8_t*)pFile + pFile->dwGfxCellOffsets[i]);
		pFile->pGfxCells[i]->pCellNode = &pCellNodes[i];
	}

	*ppOutFile = pFile;
}

//D2CMP.0x6FDF1FA0 (#10028)
void __stdcall D2CMP_CelFileFreeSerialized(void* pSerializedFile)
{
	D2_ASSERT(pSerializedFile);
	D2_FREE(pSerializedFile);
}

//D2CMP.0x6FDF1FE0 (#10027)
void __stdcall D2CMP_CelFileFree(D2CellFileStrc* pCelFile)
{
	D2_ASSERT(pCelFile);

	if (pCelFile->dwFlags & (CELFILE_SERIALIZED | CELFILE_HARDWARE))
	{
		if (pCelFile->dwFlags & CELFILE_HARDWARE)
		{
			D2CMP_CelFileFreeHardware(pCelFile);
		}
		D2_FREE(pCelFile);
	}
}

//D2CMP.0x6FDF2030 (#10031)
void __stdcall D2CMP_CelFileTransform(D2CellFileStrc* pCelFile, const uint8_t* pTransform)
{
	D2_ASSERT(pCelFile);

	for (int i = 0; i < pCelFile->nDirections * pCelFile->nFrames; ++i)
	{
		sgpfnTransformFunc[pCelFile->eFormat](pCelFile->pGfxCells[i], pTransform);
	}
}

//D2CMP.0x6FDF20A0 (#10033)
void __stdcall D2CMP_CelDraw(D2GfxDataStrc* pCelContext, int nX, int nY, int nClipLeft, int nClipRight, uint8_t* pDestSurface, int nSurfaceHeight, int nStride, const uint8_t* pPalette, const uint8_t* pBlendTable, const uint8_t* pPalShift)
{
	D2CellFileStrc* pCelFile = pCelContext->pCellFile;
	if (pCelFile)
	{
		D2_ASSERT(pCelFile->dwVersion == CELFILE_VERSION);
		D2_ASSERT(!( pCelFile->dwFlags & CELFILE_24BIT ));
	}

	D2_ASSERT(pDestSurface);

	D2GfxCellStrc* pCel = pCelContext->pCurrentCell;
	D2_ASSERT(pCel);

	int nBottom = nY + pCel->nYOffset;
	const int nLeft = nX + pCel->nXOffset;
	int nLinesToDraw = pCel->dwHeight;
	int nLinesToSkip = 0;
	if (nBottom - (int)pCel->dwHeight < 0)
	{
		nLinesToDraw = nBottom + 1;
	}

	if (nLinesToDraw <= 0)
	{
		return;
	}

	if (nBottom >= nSurfaceHeight)
	{
		nLinesToSkip = nBottom - nSurfaceHeight + 1;
		nLinesToDraw -= nLinesToSkip;
		if (nLinesToDraw <= 0)
		{
			return;
		}
		nBottom = nSurfaceHeight - 1;
	}

	if (!nClipLeft && !nClipRight && (nLeft < 0 || nBottom < 0))
	{
		return;
	}

	const CelDrawFunc pfnDraw = sgpfnDecodeFunc[pCelFile ? pCelFile->eFormat : 0];
	D2_ASSERT(pfnDraw); // sgpfnDecodeFunc[eFormat]
	pfnDraw(pCel, &pDestSurface[nLeft + nBottom * nStride], nLeft, nClipLeft, nClipRight, nStride, nLinesToSkip, nLinesToDraw, pPalette, pBlendTable, pPalShift);
}

//D2CMP.0x6FDF2210 (#10042)
BOOL __stdcall D2CMP_CelGetRawData(D2CellFileStrc* pCelFile, int nDirection, int nFrame, uint8_t* pBuffer)
{
	D2_ASSERT(pCelFile->dwVersion == CELFILE_VERSION);
	D2_ASSERT(pCelFile->dwFlags & CELFILE_24BIT);

	const int nFileDirection = gaGameDirToFileDir[GetFirstBit(pCelFile->nDirections)][nDirection];
	const D2GfxCellStrc* pCel = pCelFile->pGfxCells[nFrame + nFileDirection * pCelFile->nFrames];
	memcpy(pBuffer, pCel->pPixels, 3 * pCel->dwWidth * pCel->dwHeight);
	return TRUE;
}

//D2CMP.0x6FDF22C0 (#10034)
void __stdcall D2CMP_CelDrawEx(D2GfxDataStrc* pCelContext, int nX, int nY, int nClipLeft, int nClipRight, uint8_t* pDestSurface, int nSurfaceHeight, int nStride, const uint8_t* pPalette, const uint8_t* pBlendTable, int nLinesToSkip, int nLinesToDraw, const uint8_t* pPalShift)
{
	D2CellFileStrc* pCelFile = pCelContext->pCellFile;
	if (pCelFile)
	{
		D2_ASSERT(pCelFile->dwVersion == CELFILE_VERSION);
		D2_ASSERT(!( pCelFile->dwFlags & CELFILE_24BIT ));
	}

	D2_ASSERT(pDestSurface);

	D2GfxCellStrc* pCel = pCelContext->pCurrentCell;
	D2_ASSERT(pCel);

	const int nLeft = nX + pCel->nXOffset;
	const int nBottom = nY + pCel->nYOffset;
	int nDrawBottom = nBottom - nLinesToSkip;
	int nDrawTop = nDrawBottom - nLinesToDraw;
	if (nDrawBottom < 0 || nDrawTop >= nSurfaceHeight)
	{
		return;
	}

	if (nDrawTop < 0)
	{
		nDrawTop = 0;
	}

	if (nDrawBottom >= nSurfaceHeight)
	{
		nDrawBottom = nSurfaceHeight - 1;
	}

	const int nLines = nDrawBottom - nDrawTop;
	if (!nLines)
	{
		return;
	}

	// Note: the original game asserts with pCelFile->format even if pCelFile is nullptr
	const CelDrawFunc pfnDraw = sgpfnDecodeFunc[pCelFile->eFormat];
	D2_ASSERT(pfnDraw); // sgpfnDecodeFunc[pCelFile->format]
	pfnDraw(pCel, &pDestSurface[nLeft + nDrawBottom * nStride], nLeft, nClipLeft, nClipRight, nStride, nBottom - nDrawBottom, nLines, pPalette, pBlendTable, pPalShift);
}

//D2CMP.0x6FDF2410 (#10035)
void __stdcall D2CMP_CelDrawShadow(D2GfxDataStrc* pCelContext, int nX, int nY, int nClipLeft, int nClipRight, uint8_t* pDestSurface, int nSurfaceHeight, int nStride, const uint8_t* pBlendTable, uint8_t nShadowColor)
{
	D2CellFileStrc* pCelFile = pCelContext->pCellFile;
	if (pCelFile)
	{
		D2_ASSERT(pCelFile->dwVersion == CELFILE_VERSION);
		D2_ASSERT(!( pCelFile->dwFlags & CELFILE_24BIT ));
	}

	D2_ASSERT(pDestSurface);

	D2GfxCellStrc* pCel = pCelContext->pCurrentCell;
	D2_ASSERT(pCel);

	// Shadows are half the height of the sprite, and skewed
	const int nHalfYOffset = pCel->nYOffset / 2;
	int nLeft = nX + pCel->nXOffset + nHalfYOffset;
	int nBottom = nY + nHalfYOffset;
	int nLinesToDraw = pCel->dwHeight >> 1;
	int nLinesToSkip = 0;
	if (nBottom - (int)pCel->dwHeight / 2 < 0)
	{
		nLinesToDraw = nBottom + 1;
	}

	if (nLinesToDraw <= 0)
	{
		return;
	}

	if (nBottom >= nSurfaceHeight)
	{
		nLinesToSkip = nBottom - nSurfaceHeight + 1;
		nLinesToDraw -= nLinesToSkip;
		if (nLinesToDraw <= 0)
		{
			return;
		}
		nBottom = nSurfaceHeight - 1;
	}

	nLeft -= nLinesToSkip;
	FASTCMP_DrawCelShadow(pCel, &pDestSurface[nLeft + nBottom * nStride], nLeft, nClipLeft, nClipRight, nStride, nLinesToSkip, nLinesToDraw, pBlendTable, nShadowColor);
}

//D2CMP.0x6FDF2540 (#10036)
D2GfxCellStrc* __stdcall D2CMP_CelGetHandle(D2GfxDataStrc* pCelContext)
{
	D2_ASSERT(pCelContext);

	D2CellFileStrc* pCelFile = pCelContext->pCellFile;
	D2_ASSERT(pCelFile && pCelFile->dwVersion == CELFILE_VERSION && pCelContext->nDirection < CELFILE_NUMGAMEDIRECTIONS && pCelContext->nFrame <= (uint32_t)pCelFile->nFrames); // ValidCelContext( pCelContext )

	const int nFileDirection = gaGameDirToFileDir[GetFirstBit(pCelFile->nDirections)][pCelContext->nDirection];
	return pCelFile->pGfxCells[pCelContext->nFrame + nFileDirection * pCelFile->nFrames];
}

//D2CMP.0x6FDF25E0 (#10037)
uint32_t __stdcall D2CMP_CelGetWidth(D2GfxCellStrc* pCel)
{
	D2_ASSERT(pCel);
	return pCel->dwWidth;
}

//D2CMP.0x6FDF2610 (#10038)
uint32_t __stdcall D2CMP_CelGetHeight(D2GfxCellStrc* pCel)
{
	D2_ASSERT(pCel);
	return pCel->dwHeight;
}

//D2CMP.0x6FDF2640 (#10039)
int __stdcall D2CMP_CelGetOffsetX(D2GfxCellStrc* pCel)
{
	D2_ASSERT(pCel);
	return pCel->nXOffset;
}

//D2CMP.0x6FDF2670 (#10040)
int __stdcall D2CMP_CelGetOffsetY(D2GfxCellStrc* pCel)
{
	D2_ASSERT(pCel);
	return pCel->nYOffset;
}

//D2CMP.0x6FDF26A0 (#10041)
uint8_t* __stdcall D2CMP_CelGetControlData(D2GfxCellStrc* ptCel)
{
	D2_ASSERT(ptCel);
	return ptCel->pPixels;
}

//D2CMP.0x6FDF26D0 (#10047)
int __stdcall D2CMP_CelFileGetNumDirections(D2CellFileStrc* pFile)
{
	D2_ASSERT(pFile->dwVersion == CELFILE_VERSION);
	return pFile->nDirections;
}

//D2CMP.0x6FDF2700 (#10046)
int __stdcall D2CMP_CelFileGetCelsPerDirection(D2CellFileStrc* pFile)
{
	D2_ASSERT(pFile->dwVersion == CELFILE_VERSION);
	return pFile->nFrames;
}

//D2CMP.0x6FDF2730 (#10044)
void __stdcall D2CMP_CelSetHardwareFreeCallback(CelHardwareFreeCallback pfnCallback)
{
	sgpfnHardwareFreeCallback = pfnCallback;
}

//D2CMP.0x6FDF2740 (#10045)
CelHardwareFreeCallback __stdcall D2CMP_CelGetHardwareFreeCallback()
{
	return sgpfnHardwareFreeCallback;
}

//D2CMP.0x6FDF2750 (#10032)
BOOL __stdcall D2CMP_CelFileFreeHardware(D2CellFileStrc* ptFile)
{
	if (!ptFile)
	{
		return FALSE;
	}

	D2_ASSERT(ptFile->dwVersion == CELFILE_VERSION);

	D2GfxCellNodeStrc* lpParent = ptFile->pGfxCells[0]->pCellNode;
	D2_ASSERT(lpParent);

	for (int i = 0; i < ptFile->nFrames * ptFile->nDirections; ++i)
	{
		D2GfxCellStrc* pCel = ptFile->pGfxCells[i];
		if (pCel && pCel->pCellNode)
		{
			if (sgpfnHardwareFreeCallback)
			{
				sgpfnHardwareFreeCallback(pCel->pCellNode);
			}
			pCel->pCellNode = nullptr;
		}
	}

	D2_FREE(lpParent);
	return TRUE;
}

//D2CMP.0x6FDF2820 (#10043)
D2GfxCellNodeStrc* __stdcall D2CMP_CelGetHardwareData(D2GfxCellStrc* ptCel)
{
	D2_ASSERT(ptCel);
	return ptCel->pCellNode;
}
