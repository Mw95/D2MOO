#include "StormInternal.h"

#include <storm/List.hpp>

// Event dispatching
//
// Handlers are registered for a (type, subtype, id) triplet.
// Each (type, subtype) pair has a stack of handler tables, so that SEvtPushState and SEvtPopState can be used
// to temporarily replace the handlers. Each table is a hash table of handlers, indexed by id.
// The handlers registered last are called first.

#define SEVT_FILENAME "C:\\projects\\D2\\head\\Diablo2\\3rdParty\\STORM\\SOURCE\\SEVT.CPP"

struct HANDLERREC
{
	uint32_t dwId;                  // 0x00
	uint32_t nSequence;             // 0x04
	SEVTHANDLER pfnHandler;         // 0x08
	HANDLERREC* pNext;              // 0x0C
};

struct HANDLERTABLE
{
	HANDLERREC** ppBuckets;         // 0x00
	uint32_t nBuckets;              // 0x04
	uint32_t nCount;                // 0x08
	HANDLERTABLE* pPreviousState;   // 0x0C
};

struct TYPEREC
{
	uint32_t dwType;                // 0x00
	uint32_t dwSubType;             // 0x04
	uint32_t nLastSequence;         // 0x08
	HANDLERTABLE* pTable;           // 0x0C
	TYPEREC* pNext;                 // 0x10
};

struct BREAKCMD : TSLinkedNode<BREAKCMD>
{
	void* pData;
};

// Storm.0x6FFEA1C4
static CRITICAL_SECTION sgEvtCritSect;
// Storm.0x6FFEA1DC
static STORM_LIST(BREAKCMD) sgBreakCmdList;
// Storm.0x6FFEA1E8
static BOOL sgbModified;
// Storm.0x6FFEA1EC
static volatile LONG sgnDispatchDepth;
// Storm.0x6FFEA1F0
static TYPEREC** sgppTypeBuckets;
// Storm.0x6FFEA1F4
static uint32_t sgnTypeBuckets;
// Storm.0x6FFEA1F8
static uint32_t sgnTypeCount;

struct SEvtCriticalSectionInitializer
{
	// Storm.0x6FFC2AD0
	SEvtCriticalSectionInitializer() { InitializeCriticalSection(&sgEvtCritSect); }
	// Storm.0x6FFC2AF0
	~SEvtCriticalSectionInitializer() { DeleteCriticalSection(&sgEvtCritSect); }
};
static SEvtCriticalSectionInitializer sgEvtCritSectInitializer;


// Objects of this module are released with the default operator delete
static void SEvtDelete(void* ptr)
{
	SMemFree(ptr, "delete", -1, 0);
}

static uint32_t SEvtGetHashTableSize(uint32_t nCount)
{
	uint32_t nSize = 1;
	while (nSize <= nCount * 2 + 2)
	{
		nSize *= 2;
	}
	return nSize;
}

static TYPEREC* SEvtFindType(uint32_t dwType, uint32_t dwSubType)
{
	if (!sgppTypeBuckets || !sgnTypeBuckets)
	{
		return nullptr;
	}

	for (TYPEREC* pType = sgppTypeBuckets[(dwType ^ dwSubType) & (sgnTypeBuckets - 1)]; pType; pType = pType->pNext)
	{
		if (pType->dwType == dwType && pType->dwSubType == dwSubType)
		{
			return pType;
		}
	}
	return nullptr;
}

// Storm.0x6FFC2C60
static void SEvtDeleteTable(HANDLERTABLE* pTable)
{
	for (uint32_t i = 0; i < pTable->nBuckets; ++i)
	{
		while (HANDLERREC* pHandler = pTable->ppBuckets[i])
		{
			pTable->ppBuckets[i] = pHandler->pNext;
			SEvtDelete(pHandler);
		}
	}
	SMemFree(pTable->ppBuckets, SEVT_FILENAME, 88, 0);
	SEvtDelete(pTable);
}

// Storm.0x6FFC3010
static void SEvtCopyTable(HANDLERTABLE* pDest, const HANDLERTABLE* pSource)
{
	pDest->nBuckets = pSource->nBuckets;
	pDest->nCount = pSource->nCount;
	pDest->ppBuckets = (HANDLERREC**)SMemAlloc(pSource->nBuckets * sizeof(HANDLERREC*), SEVT_FILENAME, 62, 0);
	for (uint32_t i = 0; i < pSource->nBuckets; ++i)
	{
		HANDLERREC** ppLink = &pDest->ppBuckets[i];
		for (HANDLERREC* pHandler = pSource->ppBuckets[i]; pHandler; pHandler = pHandler->pNext)
		{
			*ppLink = (HANDLERREC*)SMemAlloc(sizeof(HANDLERREC), SEVT_FILENAME, 69, 0);
			SMemCopy(*ppLink, pHandler, sizeof(HANDLERREC));
			ppLink = &(*ppLink)->pNext;
		}
		*ppLink = nullptr;
	}
}

// Storm.0x6FFC2BA0
BOOL SEvtDestroy()
{
	EnterCriticalSection(&sgEvtCritSect);
	for (uint32_t i = 0; i < sgnTypeBuckets; ++i)
	{
		while (TYPEREC* pType = sgppTypeBuckets[i])
		{
			while (HANDLERTABLE* pTable = pType->pTable)
			{
				pType->pTable = pTable->pPreviousState;
				SEvtDeleteTable(pTable);
			}
			sgppTypeBuckets[i] = pType->pNext;
			SEvtDelete(pType);
		}
	}

	if (sgppTypeBuckets)
	{
		SEvtDelete(sgppTypeBuckets);
	}
	sgppTypeBuckets = nullptr;
	sgnTypeBuckets = 0;
	sgnTypeCount = 0;
	sgbModified = TRUE;
	LeaveCriticalSection(&sgEvtCritSect);
	return TRUE;
}

// Storm.#372
BOOL __stdcall SEvtDispatch(uint32_t dwType, uint32_t dwSubType, uint32_t dwId, void* pData)
{
	InterlockedIncrement(&sgnDispatchDepth);

	BOOL bResult = FALSE;
	HANDLERREC* pNextHandler = nullptr;
	uint32_t nLastSequence = 0xFFFFFFFF;
	do
	{
		EnterCriticalSection(&sgEvtCritSect);

		// Stop if a handler broke the chain
		for (BREAKCMD* pBreakCmd = sgBreakCmdList.Head(); pBreakCmd; pBreakCmd = pBreakCmd->Next())
		{
			if (pBreakCmd->pData == pData)
			{
				sgBreakCmdList.UnlinkNode(pBreakCmd);
				SMemFree(pBreakCmd, typeid(BREAKCMD).name(), SERR_LINECODE_OBJECT, 0);
				LeaveCriticalSection(&sgEvtCritSect);
				InterlockedDecrement(&sgnDispatchDepth);
				return bResult;
			}
		}

		// Handlers may have been (un)registered by the previous handler, find our position again
		if (!pNextHandler || sgbModified)
		{
			pNextHandler = nullptr;
			if (TYPEREC* pType = SEvtFindType(dwType, dwSubType))
			{
				HANDLERTABLE* pTable = pType->pTable;
				if (pTable->ppBuckets && pTable->nBuckets)
				{
					for (pNextHandler = pTable->ppBuckets[(pTable->nBuckets - 1) & dwId]; pNextHandler; pNextHandler = pNextHandler->pNext)
					{
						if (pNextHandler->dwId == dwId && pNextHandler->nSequence < nLastSequence)
						{
							break;
						}
					}

					if (sgnDispatchDepth == 1)
					{
						sgbModified = FALSE;
					}
				}
			}
		}

		SEVTHANDLER pfnHandler = nullptr;
		if (pNextHandler)
		{
			nLastSequence = pNextHandler->nSequence;
			pfnHandler = pNextHandler->pfnHandler;
			do
			{
				pNextHandler = pNextHandler->pNext;
			}
			while (pNextHandler && pNextHandler->dwId != dwId);
		}

		LeaveCriticalSection(&sgEvtCritSect);

		if (pfnHandler)
		{
			bResult = TRUE;
			pfnHandler(pData);
		}
	}
	while (pNextHandler);

	InterlockedDecrement(&sgnDispatchDepth);

	// Remove the break commands that were not consumed
	if (sgBreakCmdList.Head())
	{
		EnterCriticalSection(&sgEvtCritSect);
		for (BREAKCMD* pBreakCmd = sgBreakCmdList.Head(); pBreakCmd; )
		{
			if (pBreakCmd->pData == pData)
			{
				BREAKCMD* pNext = pBreakCmd->Next();
				sgBreakCmdList.UnlinkNode(pBreakCmd);
				SMemFree(pBreakCmd, typeid(BREAKCMD).name(), SERR_LINECODE_OBJECT, 0);
				pBreakCmd = pNext;
			}
			else
			{
				pBreakCmd = pBreakCmd->Next();
			}
		}
		LeaveCriticalSection(&sgEvtCritSect);
	}
	return bResult;
}

// Storm.#373
BOOL __stdcall SEvtRegisterHandler(uint32_t dwType, uint32_t dwSubType, uint32_t dwId, uint32_t dwFlags, SEVTHANDLER pfnHandler)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(pfnHandler);
	STORM_VALIDATE_ARG(!dwFlags);
	STORM_VALIDATE_END(FALSE);

	EnterCriticalSection(&sgEvtCritSect);

	TYPEREC* pType = SEvtFindType(dwType, dwSubType);
	if (!pType)
	{
		if (sgnTypeCount >= sgnTypeBuckets / 2)
		{
			// Grow the types hash table
			const uint32_t nNewBuckets = SEvtGetHashTableSize(sgnTypeCount);
			TYPEREC** ppNewBuckets = (TYPEREC**)SMemAlloc(nNewBuckets * sizeof(TYPEREC*), SEVT_FILENAME, 320, SMEM_ZEROMEMORY);
			if (sgppTypeBuckets)
			{
				for (uint32_t i = 0; i < sgnTypeBuckets; ++i)
				{
					TYPEREC* pNext;
					for (TYPEREC* pCurrent = sgppTypeBuckets[i]; pCurrent; pCurrent = pNext)
					{
						pNext = pCurrent->pNext;
						const uint32_t nIndex = (pCurrent->dwSubType ^ pCurrent->dwType) & (nNewBuckets - 1);
						pCurrent->pNext = ppNewBuckets[nIndex];
						ppNewBuckets[nIndex] = pCurrent;
					}
				}
				SMemFree(sgppTypeBuckets, SEVT_FILENAME, 337, 0);
			}
			sgppTypeBuckets = ppNewBuckets;
			sgnTypeBuckets = nNewBuckets;
		}

		const uint32_t nIndex = (dwType ^ dwSubType) & (sgnTypeBuckets - 1);
		pType = (TYPEREC*)SMemAlloc(sizeof(TYPEREC), SEVT_FILENAME, 346, SMEM_ZEROMEMORY);
		pType->dwType = dwType;
		pType->dwSubType = dwSubType;
		pType->pTable = (HANDLERTABLE*)SMemAlloc(sizeof(HANDLERTABLE), SEVT_FILENAME, 349, SMEM_ZEROMEMORY);
		pType->pNext = sgppTypeBuckets[nIndex];
		sgppTypeBuckets[nIndex] = pType;
		++sgnTypeCount;
	}

	HANDLERTABLE* pTable = pType->pTable;
	if (pTable->nCount >= pTable->nBuckets / 2)
	{
		// Grow the handlers hash table, keeping the order of the handlers
		const uint32_t nNewBuckets = SEvtGetHashTableSize(pTable->nBuckets);
		HANDLERREC** ppNewBuckets = (HANDLERREC**)SMemAlloc(nNewBuckets * sizeof(HANDLERREC*), SEVT_FILENAME, 363, SMEM_ZEROMEMORY);
		HANDLERREC*** pppTails = (HANDLERREC***)SMemAlloc(nNewBuckets * sizeof(HANDLERREC**), SEVT_FILENAME, 364, SMEM_ZEROMEMORY);
		for (uint32_t i = 0; i < nNewBuckets; ++i)
		{
			pppTails[i] = &ppNewBuckets[i];
		}

		if (pTable->ppBuckets && pTable->nBuckets)
		{
			for (uint32_t i = 0; i < pTable->nBuckets; ++i)
			{
				HANDLERREC* pNext;
				for (HANDLERREC* pCurrent = pTable->ppBuckets[i]; pCurrent; pCurrent = pNext)
				{
					pNext = pCurrent->pNext;
					pCurrent->pNext = nullptr;
					const uint32_t nIndex = pCurrent->dwId & (nNewBuckets - 1);
					*pppTails[nIndex] = pCurrent;
					pppTails[nIndex] = &pCurrent->pNext;
				}
			}
		}

		SMemFree(pppTails, SEVT_FILENAME, 383, 0);
		if (pTable->ppBuckets)
		{
			SMemFree(pTable->ppBuckets, SEVT_FILENAME, 385, 0);
		}
		pTable->ppBuckets = ppNewBuckets;
		pTable->nBuckets = nNewBuckets;
	}

	const uint32_t nIndex = (pTable->nBuckets - 1) & dwId;
	HANDLERREC* pHandler = (HANDLERREC*)SMemAlloc(sizeof(HANDLERREC), SEVT_FILENAME, 394, SMEM_ZEROMEMORY);
	pHandler->dwId = dwId;
	pHandler->nSequence = ++pType->nLastSequence;
	pHandler->pfnHandler = pfnHandler;
	pHandler->pNext = pTable->ppBuckets[nIndex];
	pTable->ppBuckets[nIndex] = pHandler;
	++pTable->nCount;

	sgbModified = TRUE;
	LeaveCriticalSection(&sgEvtCritSect);
	return TRUE;
}

// Storm.#374
BOOL __stdcall SEvtUnregisterHandler(uint32_t dwType, uint32_t dwSubType, uint32_t dwId, SEVTHANDLER pfnHandler)
{
	BOOL bResult = FALSE;
	EnterCriticalSection(&sgEvtCritSect);

	if (TYPEREC* pType = SEvtFindType(dwType, dwSubType))
	{
		HANDLERTABLE* pTable = pType->pTable;
		if (pTable->ppBuckets && pTable->nBuckets)
		{
			HANDLERREC** ppLink = &pTable->ppBuckets[(pTable->nBuckets - 1) & dwId];
			while (HANDLERREC* pHandler = *ppLink)
			{
				if (pHandler->dwId == dwId && (!pfnHandler || pHandler->pfnHandler == pfnHandler))
				{
					*ppLink = pHandler->pNext;
					SEvtDelete(pHandler);
					sgbModified = TRUE;
					bResult = TRUE;
					--pTable->nCount;
				}
				else
				{
					ppLink = &pHandler->pNext;
				}
			}
		}
	}

	LeaveCriticalSection(&sgEvtCritSect);
	return bResult;
}

// Storm.#375
BOOL __stdcall SEvtUnregisterType(uint32_t dwType, uint32_t dwSubType)
{
	BOOL bResult = FALSE;
	EnterCriticalSection(&sgEvtCritSect);

	if (TYPEREC* pType = SEvtFindType(dwType, dwSubType))
	{
		while (HANDLERTABLE* pTable = pType->pTable)
		{
			pType->pTable = pTable->pPreviousState;
			SEvtDeleteTable(pTable);
		}

		TYPEREC** ppLink = &sgppTypeBuckets[(sgnTypeBuckets - 1) & (dwType ^ dwSubType)];
		while (TYPEREC* pCurrent = *ppLink)
		{
			if (pCurrent == pType)
			{
				*ppLink = pCurrent->pNext;
				SEvtDelete(pCurrent);
				--sgnTypeCount;
			}
			else
			{
				ppLink = &pCurrent->pNext;
			}
		}

		bResult = TRUE;
		sgbModified = TRUE;
	}

	LeaveCriticalSection(&sgEvtCritSect);
	return bResult;
}

// Storm.#376
BOOL __stdcall SEvtPopState(uint32_t dwType, uint32_t dwSubType)
{
	BOOL bResult = FALSE;
	EnterCriticalSection(&sgEvtCritSect);

	if (TYPEREC* pType = SEvtFindType(dwType, dwSubType))
	{
		if (HANDLERTABLE* pPreviousState = pType->pTable->pPreviousState)
		{
			SEvtDeleteTable(pType->pTable);
			pType->pTable = pPreviousState;
		}
		else
		{
			bResult = SEvtUnregisterType(dwType, dwSubType);
		}
	}

	sgbModified = TRUE;
	LeaveCriticalSection(&sgEvtCritSect);
	return bResult;
}

// Storm.#377
BOOL __stdcall SEvtPushState(uint32_t dwType, uint32_t dwSubType)
{
	BOOL bResult = FALSE;
	EnterCriticalSection(&sgEvtCritSect);

	if (TYPEREC* pType = SEvtFindType(dwType, dwSubType))
	{
		HANDLERTABLE* pTable = (HANDLERTABLE*)SMemAlloc(sizeof(HANDLERTABLE), SEVT_FILENAME, 282, 0);
		SEvtCopyTable(pTable, pType->pTable);
		bResult = TRUE;
		pTable->pPreviousState = pType->pTable;
		pType->pTable = pTable;
		sgbModified = TRUE;
	}

	LeaveCriticalSection(&sgEvtCritSect);
	return bResult;
}

// Storm.#378
BOOL __stdcall SEvtBreakHandlerChain(void* pData)
{
	EnterCriticalSection(&sgEvtCritSect);
	BREAKCMD* pBreakCmd = sgBreakCmdList.NewNode(0, 0, 0);
	sgBreakCmdList.LinkToTail(pBreakCmd);
	pBreakCmd->pData = pData;
	LeaveCriticalSection(&sgEvtCritSect);
	return TRUE;
}
