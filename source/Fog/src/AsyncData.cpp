#include <Fog.h>
#include <Storm.h>

#include <cstring>

#define ASYNC_DATA_INITIAL_EVENT_SLOTS 0x100
#define ASYNC_DATA_MAX_EVENT_SLOTS 0x400

// Fog.0x6FF9EDE0
static int sgnPostponedPriorityChanges;
// Fog.0x6FF9EDE4
static AsyncData* sgpPostponedPriorityChanges;
// Fog.0x6FF9EDE8
static BOOL sgfAsyncDataEnabled;
// Fog.0x6FF9EDEC
static uint32_t sgnAsyncEventSlots;
// Fog.0x6FF9EDF0
static AsyncDataEventSlot* sgptAsyncEventArray;

#define ASYNC_DATA_ASSERT_VALID(pAsyncData) \
	D2_ASSERT(pAsyncData); \
	D2_ASSERTM(((pAsyncData)->nFlags & ASYNC_DATA_FLAGS_DEBUG_TAG_MASK) == ASYNC_DATA_FLAGS_DEBUG_TAG, "(ptAsyncData->dwFlags & ASYNC_DATA_FLAGS_DEBUG_TAG_MASK) == ASYNC_DATA_FLAGS_DEBUG_TAG")

// 1.10f: 0x6FF5C010 (#10089)
void __fastcall FOG_AsyncDataInitialize(BOOL bEnableAsyncOperations)
{
	D2_ASSERT(!sgfAsyncDataEnabled);

	SFileSetAsyncBudget(0x40000);
	SFileSetDataChunkSize(0x4000);
	if (!bEnableAsyncOperations)
	{
		return;
	}

	sgptAsyncEventArray = (AsyncDataEventSlot*)FOG_Alloc(ASYNC_DATA_MAX_EVENT_SLOTS * sizeof(AsyncDataEventSlot), __FILE__, __LINE__, 0);
	D2_ASSERT(sgptAsyncEventArray);
	for (int i = 0; i < ASYNC_DATA_INITIAL_EVENT_SLOTS; ++i)
	{
		sgptAsyncEventArray[i].hEvent = CreateEventA(nullptr, TRUE, FALSE, nullptr);
		sgptAsyncEventArray[i].bSlotAvailable = TRUE;
	}
	sgnAsyncEventSlots = ASYNC_DATA_INITIAL_EVENT_SLOTS;
	sgfAsyncDataEnabled = TRUE;
}

// 1.10f: 0x6FF5C0E0 (#10090)
void __fastcall FOG_AsyncDataDestroy()
{
	if (sgptAsyncEventArray)
	{
		for (uint32_t i = 0; i < sgnAsyncEventSlots; ++i)
		{
			if (sgptAsyncEventArray[i].hEvent)
			{
				CloseHandle(sgptAsyncEventArray[i].hEvent);
				sgptAsyncEventArray[i].hEvent = nullptr;
			}
		}

		FOG_Free(sgptAsyncEventArray, __FILE__, __LINE__, 0);
		sgptAsyncEventArray = nullptr;
		sgnAsyncEventSlots = 0;
	}
	sgfAsyncDataEnabled = FALSE;
}

// 1.10f: 0x6FF5C160
// Marks the data as loaded and releases the resources used for loading.
// If the callback provided replacement data, it replaces the loaded buffer.
static void ASYNCDATA_OnLoaded(AsyncData* pAsyncData)
{
	if (pAsyncData->nFlags & ASYNC_DATA_FLAGS_LOADED)
	{
		return;
	}

	if (AsyncDataEventSlot* pEventSlot = pAsyncData->pEventSlot)
	{
		ResetEvent(pEventSlot->hEvent);
		pEventSlot->bSlotAvailable = TRUE;
		pEventSlot->pAsyncOp = nullptr;
		pAsyncData->pEventSlot = nullptr;
	}

	if (pAsyncData->hFile)
	{
		FOG_FCloseFile(pAsyncData->hFile);
		pAsyncData->hFile = nullptr;
	}

	pAsyncData->nFlags |= ASYNC_DATA_FLAGS_LOADED;
	if (pAsyncData->pAsyncOpDesc.pData)
	{
		FOG_FreePool(pAsyncData->pMemPool, pAsyncData->pBuffer, __FILE__, __LINE__, 0);
		pAsyncData->pBuffer = pAsyncData->pAsyncOpDesc.pData;
		pAsyncData->nFileSize = pAsyncData->pAsyncOpDesc.nFileSize;
		memset(&pAsyncData->pAsyncOpDesc, 0, sizeof(pAsyncData->pAsyncOpDesc));
	}
}

// 1.10f: 0x6FF5C1F0
// Returns an available event slot, reclaiming the ones whose operation completed, or creating a new one.
static AsyncDataEventSlot* ASYNCDATA_GetEventSlot()
{
	if (!sgfAsyncDataEnabled)
	{
		return nullptr;
	}

	for (uint32_t i = 0; i < sgnAsyncEventSlots; ++i)
	{
		if (sgptAsyncEventArray[i].bSlotAvailable)
		{
			sgptAsyncEventArray[i].bSlotAvailable = FALSE;
			return &sgptAsyncEventArray[i];
		}
	}

	for (uint32_t i = 0; i < sgnAsyncEventSlots; ++i)
	{
		AsyncDataEventSlot* pEventSlot = &sgptAsyncEventArray[i];
		if (WaitForSingleObject(pEventSlot->hEvent, 0) == WAIT_OBJECT_0)
		{
			ASYNCDATA_OnLoaded(pEventSlot->pAsyncOp);
			pEventSlot->bSlotAvailable = FALSE;
			return pEventSlot;
		}
	}

	if (sgnAsyncEventSlots < ASYNC_DATA_MAX_EVENT_SLOTS)
	{
		AsyncDataEventSlot* pEventSlot = &sgptAsyncEventArray[sgnAsyncEventSlots++];
		pEventSlot->hEvent = CreateEventA(nullptr, TRUE, FALSE, nullptr);
		pEventSlot->bSlotAvailable = FALSE;
		return pEventSlot;
	}

	return nullptr;
}

// 1.10f: 0x6FF5C2B0 (#10091)
// Loads a file, asynchronously if possible. If pBuffer is nullptr, the buffer is allocated from pMemPool.
AsyncData* __fastcall FOG_AsyncDataLoadFileEx(void* pMemPool, const char* pFileName, BOOL bAllowAsync, LONG nFileOffset, int nFileSize, void* pBuffer, AsyncDataLoadFileCallback* asyncOpDesc, int a8, const char* sourceFile, int sourceLine)
{
	AsyncData* pAsyncData = (AsyncData*)FOG_AllocPool(pMemPool, sizeof(AsyncData), __FILE__, __LINE__, 0);
	memset(pAsyncData, 0, sizeof(AsyncData));
	pAsyncData->nFlags = ASYNC_DATA_FLAGS_DEBUG_TAG;
	if (!FOG_FOpenFile(pFileName, &pAsyncData->hFile))
	{
		FOG_FreePool(pMemPool, pAsyncData, __FILE__, __LINE__, 0);
		return nullptr;
	}

	pAsyncData->pMemPool = pMemPool;
	pAsyncData->nPriority = a8;
	if (nFileOffset && FOG_FSetFilePointer(pAsyncData->hFile, nFileOffset, nullptr, FILE_BEGIN) == (size_t)-1)
	{
		FOG_DisplayError(3, pFileName, __FILE__, __LINE__);
		exit(-1);
	}

	pAsyncData->nFileSize = nFileSize > 0 ? nFileSize : FOG_FGetFileSize(pAsyncData->hFile, nullptr);
	if (pBuffer)
	{
		pAsyncData->pBuffer = pBuffer;
		pAsyncData->nFlags &= ~ASYNC_DATA_FLAGS_OWNS_BUFFER;
	}
	else
	{
		pAsyncData->pBuffer = FOG_AllocPool(pMemPool, pAsyncData->nFileSize, sourceFile, sourceLine, 0);
		pAsyncData->nFlags |= ASYNC_DATA_FLAGS_OWNS_BUFFER;
	}

	AsyncDataLoadFileCallback* pCallbackData = nullptr;
	if (asyncOpDesc)
	{
		pAsyncData->pAsyncOpDesc = *asyncOpDesc;
		pCallbackData = &pAsyncData->pAsyncOpDesc;
	}

	if (bAllowAsync && sgfAsyncDataEnabled)
	{
		AsyncDataEventSlot* pEventSlot = ASYNCDATA_GetEventSlot();
		pAsyncData->pEventSlot = pEventSlot;
		if (!pEventSlot)
		{
			if (pAsyncData->hFile)
			{
				FOG_FCloseFile(pAsyncData->hFile);
				pAsyncData->hFile = nullptr;
			}

			if (pAsyncData->nFlags & ASYNC_DATA_FLAGS_OWNS_BUFFER)
			{
				FOG_FreePool(pMemPool, pAsyncData->pBuffer, __FILE__, __LINE__, 0);
			}
			FOG_FreePool(pMemPool, pAsyncData, __FILE__, __LINE__, 0);
			return nullptr;
		}

		pEventSlot->pAsyncOp = pAsyncData;
		pAsyncData->tOverlapped.hEvent = pEventSlot->hEvent;
		pAsyncData->tOverlapped.Offset = nFileOffset;
		FOG_FReadFile(pAsyncData->hFile, pAsyncData->pBuffer, pAsyncData->nFileSize, nullptr, (uint32_t)&pAsyncData->tOverlapped, (uint32_t)pCallbackData, a8);
		return pAsyncData;
	}

	FOG_FReadFile(pAsyncData->hFile, pAsyncData->pBuffer, pAsyncData->nFileSize, nullptr, 0, 0, a8);
	if (pCallbackData && pCallbackData->callback)
	{
		pCallbackData->callback(pAsyncData->pBuffer, pAsyncData->nFileSize, pCallbackData);
	}
	ASYNCDATA_OnLoaded(pAsyncData);
	return pAsyncData;
}

// 1.10f: 0x6FF5C480 (#10092)
BOOL __fastcall FOG_AsyncDataTestLoaded(AsyncData* pAsyncData)
{
	if (!pAsyncData)
	{
		return FALSE;
	}

	D2_ASSERTM((pAsyncData->nFlags & ASYNC_DATA_FLAGS_DEBUG_TAG_MASK) == ASYNC_DATA_FLAGS_DEBUG_TAG, "(ptAsyncData->dwFlags & ASYNC_DATA_FLAGS_DEBUG_TAG_MASK) == ASYNC_DATA_FLAGS_DEBUG_TAG");
	if (!(pAsyncData->nFlags & ASYNC_DATA_FLAGS_LOADED) && WaitForSingleObject(pAsyncData->pEventSlot->hEvent, 0) == WAIT_OBJECT_0)
	{
		ASYNCDATA_OnLoaded(pAsyncData);
	}
	return pAsyncData->nFlags & ASYNC_DATA_FLAGS_LOADED;
}

// 1.10f: 0x6FF5C630 (#10093)
// Waits for the data to be loaded, raising the priority of the request.
void __fastcall FOG_AsyncDataWaitAndGetBuffer(AsyncData* pAsyncData)
{
	ASYNC_DATA_ASSERT_VALID(pAsyncData);
	if (FOG_AsyncDataTestLoaded(pAsyncData))
	{
		return;
	}

	SFilePrioritizeRequest(pAsyncData->pBuffer, 1);
	const DWORD dwRet = WaitForSingleObject(pAsyncData->pEventSlot->hEvent, INFINITE);
	D2_ASSERT(dwRet == WAIT_OBJECT_0);
	ASYNCDATA_OnLoaded(pAsyncData);
}

// 1.10f: 0x6FF5C700 (#10094)
void* __fastcall FOG_AsyncDataGetBuffer(AsyncData* pAsyncData)
{
	ASYNC_DATA_ASSERT_VALID(pAsyncData);
	if (!(pAsyncData->nFlags & ASYNC_DATA_FLAGS_LOADED))
	{
		FOG_AsyncDataWaitAndGetBuffer(pAsyncData);
	}
	D2_ASSERTM(pAsyncData->nFlags & ASYNC_DATA_FLAGS_LOADED, "TEST_FLAG(ptAsyncData->dwFlags, ASYNC_DATA_FLAGS_LOADED)");
	return pAsyncData->pBuffer;
}

// 1.10f: 0x6FF5C790 (#10095)
DWORD __fastcall FOG_AsyncDataGetBufferSize(AsyncData* pAsyncData)
{
	ASYNC_DATA_ASSERT_VALID(pAsyncData);
	return pAsyncData->nFileSize;
}

// 1.10f: 0x6FF5C7E0 (#10096)
// Replaces the loaded buffer. The previous buffer is freed even if it was not allocated by FOG_AsyncDataLoadFileEx.
void __fastcall FOG_AsyncDataSetResults(AsyncData* pAsyncData, int nUnused, void* pBuffer, int nBufferSize)
{
	ASYNC_DATA_ASSERT_VALID(pAsyncData);
	D2_ASSERTM(pAsyncData->nFlags & ASYNC_DATA_FLAGS_LOADED, "TEST_FLAG(ptAsyncData->dwFlags, ASYNC_DATA_FLAGS_LOADED)");
	FOG_FreePool(pAsyncData->pMemPool, pAsyncData->pBuffer, __FILE__, __LINE__, 0);
	pAsyncData->pBuffer = pBuffer;
	pAsyncData->nFileSize = nBufferSize;
}

// 1.10f: 0x6FF5C880 (#10097)
void __fastcall FOG_AsyncDataFree(AsyncData* pAsyncData)
{
	ASYNC_DATA_ASSERT_VALID(pAsyncData);

	if (pAsyncData->nFlags & ASYNC_DATA_FLAGS_POSTPONED_PRIORITY_CHANGE)
	{
		for (AsyncData** ppAsyncData = &sgpPostponedPriorityChanges; *ppAsyncData; ppAsyncData = &(*ppAsyncData)->pNextPostponedPriorityChange)
		{
			if (*ppAsyncData == pAsyncData)
			{
				*ppAsyncData = pAsyncData->pNextPostponedPriorityChange;
				break;
			}
		}
	}

	if (!FOG_AsyncDataTestLoaded(pAsyncData))
	{
		SFileCancelRequest(pAsyncData->pBuffer);
		WaitForSingleObject(pAsyncData->pEventSlot->hEvent, INFINITE);
		ASYNCDATA_OnLoaded(pAsyncData);
	}

	if (pAsyncData->nFlags & ASYNC_DATA_FLAGS_OWNS_BUFFER)
	{
		D2_ASSERTM(pAsyncData->pBuffer, "ptAsyncData->ptBuffer");
		FOG_FreePool(pAsyncData->pMemPool, pAsyncData->pBuffer, __FILE__, __LINE__, 0);
		pAsyncData->pBuffer = nullptr;
		pAsyncData->nFlags &= ~ASYNC_DATA_FLAGS_DEBUG_TAG_MASK;
	}

	FOG_FreePool(pAsyncData->pMemPool, pAsyncData, __FILE__, __LINE__, 0);
}

// 1.10f: 0x6FF5C4E0 (#10099)
// Changes the priority of the request. Changes are applied later if they are postponed by FOG_AsyncDataHandlePriorityChanges.
void __fastcall FOG_AsyncDataSetPriority(AsyncData* pAsyncData, int nPriority)
{
	ASYNC_DATA_ASSERT_VALID(pAsyncData);
	D2_ASSERT(nPriority <= ASYNC_DATA_PRIORITY_NORMAL);

	if (sgnPostponedPriorityChanges > 0)
	{
		if (pAsyncData->nFlags & ASYNC_DATA_FLAGS_POSTPONED_PRIORITY_CHANGE)
		{
			if (nPriority > (int)pAsyncData->nPriority)
			{
				pAsyncData->nPriority = nPriority;
			}
		}
		else
		{
			pAsyncData->nPreviousPriority = pAsyncData->nPriority;
			pAsyncData->nPriority = nPriority;
			pAsyncData->nFlags |= ASYNC_DATA_FLAGS_POSTPONED_PRIORITY_CHANGE;
			pAsyncData->pNextPostponedPriorityChange = sgpPostponedPriorityChanges;
			sgpPostponedPriorityChanges = pAsyncData;
		}
	}
	else if (nPriority != (int)pAsyncData->nPriority)
	{
		pAsyncData->nPriority = nPriority;
		SFilePrioritizeRequest(pAsyncData->pBuffer, nPriority);
	}
}

// 1.10f: 0x6FF5C5A0 (#10100)
// Calls can be nested, the postponed priority changes are applied once every postpone has been released.
void __fastcall FOG_AsyncDataHandlePriorityChanges(BOOL bPostpone)
{
	if (bPostpone)
	{
		++sgnPostponedPriorityChanges;
		return;
	}

	D2_ASSERT(sgnPostponedPriorityChanges > 0);
	--sgnPostponedPriorityChanges;
	if (sgnPostponedPriorityChanges != 0)
	{
		return;
	}

	AsyncData* pAsyncData = sgpPostponedPriorityChanges;
	while (pAsyncData)
	{
		AsyncData* pNext = pAsyncData->pNextPostponedPriorityChange;
		if (pAsyncData->nPriority != pAsyncData->nPreviousPriority)
		{
			SFilePrioritizeRequest(pAsyncData->pBuffer, pAsyncData->nPriority);
		}
		pAsyncData->nPreviousPriority = 0;
		pAsyncData->pNextPostponedPriorityChange = nullptr;
		pAsyncData->nFlags &= ~ASYNC_DATA_FLAGS_POSTPONED_PRIORITY_CHANGE;
		pAsyncData = pNext;
	}
	sgpPostponedPriorityChanges = nullptr;
}
