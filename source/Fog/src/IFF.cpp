#include <IFF.h>
#include <Storm.h>

#include <cstddef>
#include <cstring>

#define FOG_IFF_BOND_TAG 0x444E4F42 // 'BOND'
#define FOG_IFF_BOND_MAX_SIZE 1024

static uint32_t IFF_GetBondSize(const FOGIFFBond* pBond)
{
	return offsetof(FOGIFFBond, pEntries) + pBond->nEntries * sizeof(FOGIFFBondEntry);
}

// 1.10f: 0x6FF61A20 (#10199)
// Returns the bond at *ppData and advances *ppData past it, or nullptr if the data is not a valid bond.
FOGIFFBond* __fastcall FOG_IFFReadBond(uint8_t** ppData, uint32_t* pDataSize)
{
	if (*pDataSize < offsetof(FOGIFFBond, pEntries))
	{
		return nullptr;
	}

	FOGIFFBond* pBond = (FOGIFFBond*)*ppData;
	if (pBond->dwTag != FOG_IFF_BOND_TAG)
	{
		return nullptr;
	}

	const uint32_t nBondSize = IFF_GetBondSize(pBond);
	if (nBondSize > FOG_IFF_BOND_MAX_SIZE || nBondSize > *pDataSize)
	{
		return nullptr;
	}

	*ppData += nBondSize;
	*pDataSize -= nBondSize;
	return pBond;
}

// 1.10f: 0x6FF61A70 (#10200)
FOGIFFBond* __fastcall FOG_IFFCreateBond()
{
	// Flag 8: zero the memory
	FOGIFFBond* pBond = (FOGIFFBond*)SMemAlloc(FOG_IFF_BOND_MAX_SIZE, __FILE__, __LINE__, 8);
	pBond->dwTag = FOG_IFF_BOND_TAG;
	return pBond;
}

// 1.10f: 0x6FF61A90 (#10201)
int32_t __fastcall FOG_IFFWriteBond(FOGIFFBond* pBond, uint8_t* pDest, int32_t* pDestSize, int32_t* pWrittenSize)
{
	*pWrittenSize = 0;
	const int32_t nBondSize = (int32_t)IFF_GetBondSize(pBond);
	if (nBondSize > *pDestSize)
	{
		return FOG_IFF_ERROR_NO_SPACE;
	}

	*pWrittenSize = nBondSize;
	*pDestSize -= nBondSize;
	memcpy(pDest, pBond, nBondSize);
	return FOG_IFF_ERROR_NONE;
}

// 1.10f: 0x6FF61AE0 (#10202)
void __fastcall FOG_IFFFreeBond(FOGIFFBond* pBond)
{
	SMemFree(pBond, __FILE__, __LINE__, 0);
}

// 1.10f: 0x6FF61AF0 (#10203)
int32_t __fastcall FOG_IFFAddBondEntry(uint32_t dwKey, uint32_t dwValue1, uint32_t dwValue2, FOGIFFBond* pBond)
{
	if (IFF_GetBondSize(pBond) + sizeof(FOGIFFBondEntry) > FOG_IFF_BOND_MAX_SIZE)
	{
		return FOG_IFF_ERROR_NO_SPACE;
	}

	FOGIFFBondEntry* pEntry = &pBond->pEntries[pBond->nEntries];
	pEntry->dwKey = dwKey;
	pEntry->dwValue1 = dwValue1;
	pEntry->dwValue2 = dwValue2;
	++pBond->nEntries;
	return FOG_IFF_ERROR_NONE;
}

// 1.10f: 0x6FF61B40 (#10204)
int32_t __fastcall FOG_IFFAddBondEntryByName(const char* szName, uint32_t dwValue1, uint32_t dwValue2, FOGIFFBond* pBond)
{
	return FOG_IFFAddBondEntry(SStrHash(szName, 0, 0), dwValue1, dwValue2, pBond);
}

// 1.10f: 0x6FF61B90 (#10205)
int32_t __fastcall FOG_IFFGetBondEntry(uint32_t dwKey, FOGIFFBond* pBond, uint32_t* pValue1, uint32_t* pValue2)
{
	for (uint32_t i = 0; i < pBond->nEntries; ++i)
	{
		if (pBond->pEntries[i].dwKey == dwKey)
		{
			*pValue1 = pBond->pEntries[i].dwValue1;
			*pValue2 = pBond->pEntries[i].dwValue2;
			return FOG_IFF_ERROR_NONE;
		}
	}
	return FOG_IFF_ERROR_NOT_FOUND;
}

// 1.10f: 0x6FF61BD0 (#10206)
int32_t __fastcall FOG_IFFGetBondEntryByName(const char* szName, FOGIFFBond* pBond, uint32_t* pValue1, uint32_t* pValue2)
{
	return FOG_IFFGetBondEntry(SStrHash(szName, 0, 0), pBond, pValue1, pValue2);
}
