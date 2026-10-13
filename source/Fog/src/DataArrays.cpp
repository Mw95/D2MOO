#include <DataArrays.h>

#include <cstring>
#include <cstdlib>

static uint16_t* DATAARRAY_GetElementSalt(FOGDataArray* pDataArray, int32_t nIndex)
{
	return (uint16_t*)&pDataArray->pElements[nIndex * pDataArray->nElementSize];
}

static void DATAARRAY_Halt(const char* szMessage, int nLine)
{
	FOG_DisplayAssert(szMessage, __FILE__, nLine);
	exit(-1);
}

#define DATAARRAY_ASSERT_VALID(pDataArray) if (!(pDataArray)->fValid) { DATAARRAY_Halt("lptDataArray->fValid", __LINE__); }

static void DATAARRAY_ResetElements(FOGDataArray* pDataArray)
{
	pDataArray->nLastUsedElement = -1;
	pDataArray->nUsedElements = 0;
	pDataArray->nFirstFreeElementHint = 0;
	pDataArray->nNextSalt = 0x8000;
	for (int32_t i = 0; i < pDataArray->nMaxElements; ++i)
	{
		*DATAARRAY_GetElementSalt(pDataArray, i) = 0;
	}
}

// 1.10f: 0x6FF5D7E0 (#10060)
FOGDataArray* __fastcall FOG_DataArrayCreate(const char* szName, int32_t nMaxElements, int32_t nElementSize)
{
	FOGDataArray* pDataArray = (FOGDataArray*)FOG_Alloc(sizeof(FOGDataArray) + nMaxElements * nElementSize, __FILE__, __LINE__, 0);
	if (pDataArray)
	{
		memset(pDataArray, 0, sizeof(FOGDataArray));
		strncpy(pDataArray->szName, szName, sizeof(pDataArray->szName));
		pDataArray->nMaxElements = nMaxElements;
		pDataArray->nElementSize = nElementSize;
		pDataArray->pElements = (uint8_t*)&pDataArray[1];
		pDataArray->fValid = FALSE;
	}
	return pDataArray;
}

// 1.10f: 0x6FF5D860 (#10061)
void __fastcall FOG_DataArrayDestroy(FOGDataArray* pDataArray)
{
	memset(pDataArray, 0, sizeof(FOGDataArray));
	FOG_Free(pDataArray, __FILE__, __LINE__, 0);
}

// 1.10f: 0x6FF5D890 (#10062)
void __fastcall FOG_DataArrayInitialize(FOGDataArray* pDataArray)
{
	pDataArray->fValid = TRUE;
	DATAARRAY_ResetElements(pDataArray);
}

// 1.10f: 0x6FF5D8F0 (#10063)
void __fastcall FOG_DataArrayClear(FOGDataArray* pDataArray)
{
	DATAARRAY_ASSERT_VALID(pDataArray);
	DATAARRAY_ResetElements(pDataArray);
}

// 1.10f: 0x6FF5D970 (#10064)
// Returns a handle to a new zeroed element, or FOG_DATA_ARRAY_INVALID_HANDLE if the array is full.
FOGDataArrayHandle __fastcall FOG_DataArrayAllocElement(FOGDataArray* pDataArray)
{
	DATAARRAY_ASSERT_VALID(pDataArray);

	for (int32_t nIndex = pDataArray->nFirstFreeElementHint; nIndex < pDataArray->nMaxElements; ++nIndex)
	{
		uint16_t* pSalt = DATAARRAY_GetElementSalt(pDataArray, nIndex);
		if (*pSalt != 0)
		{
			continue;
		}

		memset(pSalt, 0, pDataArray->nElementSize);
		*pSalt = pDataArray->nNextSalt;
		++pDataArray->nNextSalt;
		if (pDataArray->nNextSalt == 0)
		{
			pDataArray->nNextSalt = 0x8000;
		}

		++pDataArray->nUsedElements;
		pDataArray->nFirstFreeElementHint = nIndex + 1;
		if (pDataArray->nLastUsedElement < nIndex)
		{
			pDataArray->nLastUsedElement = nIndex;
		}
		return (nIndex << 16) | *pSalt;
	}

	return FOG_DATA_ARRAY_INVALID_HANDLE;
}

static void DATAARRAY_HaltInvalidHandle(FOGDataArray* pDataArray, FOGDataArrayHandle hElement, int nLine)
{
	char szMessage[256];
	FOG_csprintf(szMessage, "%s index #%d (0x%x) (%p.#%d) is unused or changed", pDataArray->szName, (int16_t)(hElement >> 16), hElement, nullptr, pDataArray->nElementSize);
	DATAARRAY_Halt(szMessage, nLine);
}

// 1.10f: 0x6FF5DA50 (#10065)
void __fastcall FOG_DataArrayFreeElement(FOGDataArray* pDataArray, FOGDataArrayHandle hElement)
{
	uint16_t* pSalt = (uint16_t*)FOG_DataArrayGetElement(pDataArray, hElement);
	if (!pSalt)
	{
		DATAARRAY_HaltInvalidHandle(pDataArray, hElement, __LINE__);
	}

	*pSalt = 0;

	const int32_t nIndex = (int16_t)(hElement >> 16);
	if (nIndex < pDataArray->nFirstFreeElementHint)
	{
		pDataArray->nFirstFreeElementHint = nIndex;
	}

	if (nIndex == pDataArray->nLastUsedElement)
	{
		// Find the new last used element
		uint8_t* pElement = (uint8_t*)pSalt;
		do
		{
			pElement -= pDataArray->nElementSize;
			--pDataArray->nLastUsedElement;
		}
		while (pDataArray->nLastUsedElement >= 0 && *(uint16_t*)pElement == 0);
	}

	--pDataArray->nUsedElements;
}

// 1.10f: 0x6FF5DBC0 (#10066)
// Same as FOG_DataArrayGetElement but halts if the handle is invalid.
void* __fastcall FOG_DataArrayGetElementChecked(FOGDataArray* pDataArray, FOGDataArrayHandle hElement)
{
	void* pElement = FOG_DataArrayGetElement(pDataArray, hElement);
	if (!pElement)
	{
		DATAARRAY_HaltInvalidHandle(pDataArray, hElement, __LINE__);
	}
	return pElement;
}

// 1.10f: 0x6FF5DB00 (#10067)
// Returns the element of the handle or nullptr if it is unused or was reused.
// A handle with a salt of 0 matches any used element at its index.
void* __fastcall FOG_DataArrayGetElement(FOGDataArray* pDataArray, FOGDataArrayHandle hElement)
{
	if (hElement == FOG_DATA_ARRAY_INVALID_HANDLE)
	{
		return nullptr;
	}

	const int32_t nIndex = (int16_t)(hElement >> 16);
	if (nIndex < 0 || nIndex >= pDataArray->nMaxElements)
	{
		char szMessage[256];
		FOG_csprintf(szMessage, "%s index #%d (0x%x) not in [0,#%d)", pDataArray->szName, nIndex, hElement, pDataArray->nMaxElements);
		DATAARRAY_Halt(szMessage, __LINE__);
	}

	DATAARRAY_ASSERT_VALID(pDataArray);

	uint16_t* pSalt = DATAARRAY_GetElementSalt(pDataArray, nIndex);
	const uint16_t nHandleSalt = (uint16_t)hElement;
	if (*pSalt == 0 || (nHandleSalt != 0 && *pSalt != nHandleSalt))
	{
		return nullptr;
	}
	return pSalt;
}
