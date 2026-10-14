#include "BNNews.h"

#include <cstring>

#include <Fog.h>
#include <Storm.h>

#include "BnCache.h"
#include "BnConnect.h"
#include "BnRecv.h"


// Raw type name of NewsTable::Item, used by the original code for Storm memory tracking (typeid(NewsTable::Item).raw_name())
static const char gszNewsTableItemName[] = ".?AUItem@NewsTable@@";

NewsTable gtBnNewsTable;
uint32_t gnBnNewsFirstItem;
uint32_t gnBnNewsTimestamp;
BOOL s_gettingNews;
BnNewsItemCallback gpfBnNewsItemCallback;
BnNewsDoneCallback gpfBnNewsDoneCallback;

const char* gszBnNewsCacheFileName = "BNNews-D2DV";


//Bnclient.0x6FF066F0
NewsTable::NewsTable()
{
	m_nAllocated = 0;
	m_nCount = 0;
	m_pData = nullptr;
	m_nChunkSize = 0;
}

//Bnclient.0x6FF066D0
NewsTable::~NewsTable()
{
	if (m_pData)
	{
		SMemFree(m_pData, gszNewsTableItemName, -2, 0);
	}
}

//Bnclient.0x6FF06D50
void NewsTable::Clear()
{
	if (m_pData)
	{
		SMemFree(m_pData, gszNewsTableItemName, -2, 0);
	}
}

//Bnclient.0x6FF06D90
void NewsTable::Reserve(uint32_t nAmount, BOOL bRoundToChunk)
{
	uint32_t nNewSize = m_nCount + nAmount;
	if (nNewSize <= m_nAllocated)
	{
		return;
	}

	if (bRoundToChunk)
	{
		uint32_t nChunkSize = m_nChunkSize;
		if (!nChunkSize)
		{
			if (nNewSize >= 8)
			{
				m_nChunkSize = 8;
				nChunkSize = 8;
			}
			else
			{
				// Largest power of 2 lower or equal to nNewSize
				nChunkSize = nNewSize;
				while (nChunkSize & (nChunkSize - 1))
				{
					nChunkSize &= nChunkSize - 1;
				}

				if (nChunkSize < 1)
				{
					nChunkSize = 1;
				}
			}
		}

		if (const uint32_t nRemainder = nNewSize % nChunkSize)
		{
			nNewSize += nChunkSize - nRemainder;
		}
	}

	Item* pOldData = m_pData;
	const uint32_t nNewBytes = nNewSize * sizeof(Item);
	m_nAllocated = nNewSize;
	m_pData = (Item*)SMemReAlloc(pOldData, nNewBytes, gszNewsTableItemName, -2, 0x10);
	if (m_pData)
	{
		return;
	}

	m_pData = (Item*)SMemAlloc(nNewBytes, gszNewsTableItemName, -2, 0);
	if (!pOldData)
	{
		return;
	}

	const uint32_t nItemsToCopy = nNewSize < m_nCount ? nNewSize : m_nCount;
	for (uint32_t i = 0; i < nItemsToCopy; ++i)
	{
		memcpy(&m_pData[i], &pOldData[i], sizeof(Item));
	}

	SMemFree(pOldData, gszNewsTableItemName, -2, 0);
}

//Bnclient.0x6FF06700
void __fastcall BNNEWS_SetProduct(BOOL bClassic)
{
	D2_ASSERT(!s_gettingNews);

	gszBnNewsCacheFileName = "BNNews-D2DV";
	if (!bClassic)
	{
		gszBnNewsCacheFileName = "BNNews-D2XP";
	}
}

// Calls the callbacks with all the items that are recent enough, from the newest to the oldest one
static void BNNEWS_NotifyNews()
{
	if (gpfBnNewsDoneCallback)
	{
		gpfBnNewsDoneCallback();
	}

	if (gpfBnNewsItemCallback && (int)(gtBnNewsTable.m_nCount - gnBnNewsFirstItem) > 0)
	{
		for (uint32_t i = gtBnNewsTable.m_nCount; i > gnBnNewsFirstItem; --i)
		{
			NewsTable::Item* pItem = &gtBnNewsTable.m_pData[i - 1];
			gpfBnNewsItemCallback(pItem->nTimestamp, pItem->szText);
		}
	}
}

//Bnclient.0x6FF06740
BOOL __fastcall BNNEWS_LoadBNetNews(BnNewsItemCallback pfItemCallback, BnNewsDoneCallback pfDoneCallback)
{
	s_gettingNews = TRUE;
	gpfBnNewsItemCallback = pfItemCallback;
	gpfBnNewsDoneCallback = pfDoneCallback;

	if (gtBnNewsTable.m_pData)
	{
		SMemFree(gtBnNewsTable.m_pData, gszNewsTableItemName, -2, 0);
	}

	gtBnNewsTable.m_nAllocated = 0;
	gtBnNewsTable.m_nCount = 0;
	gtBnNewsTable.m_pData = nullptr;
	gnBnNewsTimestamp = 0;
	gnBnNewsFirstItem = 0;

	BOOL bLoaded = FALSE;
	FILETIME tFileTime;
	void* pCachedFile = nullptr;
	uint32_t nCachedFileSize;
	if (!BNCACHE_LoadFile(gszBnNewsCacheFileName, &tFileTime, &pCachedFile, &nCachedFileSize))
	{
		FOG_Trace("news load: no news cached");
	}
	else
	{
		const uint32_t* pCursor = (const uint32_t*)pCachedFile;
		gnBnNewsTimestamp = *pCursor++;
		const uint32_t nItems = *pCursor++;
		if (nItems > BATTLENETCHAT_NEWSTABLE_MAXITEMS)
		{
			FOG_Trace("news load: bad item count %u", nItems);
		}
		else
		{
			gtBnNewsTable.m_nCount = 0;
			gtBnNewsTable.Reserve(nItems, FALSE);
			gnBnNewsFirstItem = 0;

			uint32_t nLastTimestamp = 0;
			uint32_t nItem = 0;
			for (; nItem < nItems; ++nItem)
			{
				gtBnNewsTable.Reserve(1, TRUE);
				NewsTable::Item* pItem = &gtBnNewsTable.m_pData[gtBnNewsTable.m_nCount++];
				pItem->nUnused = 0;
				pItem->nTimestamp = *pCursor++;

				const char* szText = (const char*)pCursor;
				const size_t nLength = strlen(szText);
				if (nLength >= sizeof(pItem->szText))
				{
					nItem = UINT32_MAX;
					break;
				}

				strcpy(pItem->szText, szText);
				pCursor = (const uint32_t*)&szText[nLength + 1];

				if (nLastTimestamp > pItem->nTimestamp)
				{
					FOG_Trace("news load: bad item ordering");
					break;
				}

				nLastTimestamp = pItem->nTimestamp;
			}

			bLoaded = nItem == nItems;
		}
	}

	if (!bLoaded)
	{
		gtBnNewsTable.Clear();
		gtBnNewsTable.m_nAllocated = 0;
		gtBnNewsTable.m_nCount = 0;
		gtBnNewsTable.m_pData = nullptr;
		gnBnNewsFirstItem = 0;
		gnBnNewsTimestamp = 0;
	}

	if (pCachedFile)
	{
		SMemFree(pCachedFile, __FILE__, __LINE__, 0);
	}

	if (bLoaded)
	{
		BNNEWS_NotifyNews();
	}

	uint32_t nTimestamp = gnBnNewsTimestamp;
	BNET_SendPacket(SID_NEWS_INFO, &nTimestamp, sizeof(nTimestamp));
	return TRUE;
}

//Bnclient.0x6FF06990
BOOL __stdcall BNNEWS_FreeBNetNews()
{
	gpfBnNewsItemCallback = nullptr;
	gpfBnNewsDoneCallback = nullptr;

	if (gtBnNewsTable.m_pData)
	{
		SMemFree(gtBnNewsTable.m_pData, gszNewsTableItemName, -2, 0);
	}

	gtBnNewsTable.m_nAllocated = 0;
	gtBnNewsTable.m_nCount = 0;
	gtBnNewsTable.m_pData = nullptr;
	s_gettingNews = FALSE;
	return TRUE;
}

//Bnclient.0x6FF069E0
BOOL __fastcall BNNEWS_StoreNewsInfo(const uint8_t* pData, uint32_t nSize)
{
	const uint32_t numItems = (int8_t)pData[0];
	const uint32_t nOldestTimestamp = *(const uint32_t*)&pData[5];
	const uint32_t nNewestTimestamp = *(const uint32_t*)&pData[9];
	const uint8_t* pCursor = &pData[13];

	D2_ASSERT(numItems <= BATTLENETCHAT_NEWSTABLE_MAXITEMS);

	for (uint32_t nItem = 0; nItem < numItems; ++nItem)
	{
		const uint32_t nTimestamp = *(const uint32_t*)pCursor;
		const char* szText = (const char*)&pCursor[4];
		pCursor = (const uint8_t*)&szText[strlen(szText) + 1];

		if (!nTimestamp)
		{
			// Message of the day
			if (gpfBnNewsItemCallback)
			{
				gpfBnNewsItemCallback(0, szText);
			}
			continue;
		}

		// Look for the position of the item, sorted by timestamp
		const uint32_t nCount = gtBnNewsTable.m_nCount;
		uint32_t nPosition = nCount;
		BOOL bReplace = FALSE;
		while (nPosition > 0)
		{
			NewsTable::Item* pItem = &gtBnNewsTable.m_pData[nPosition - 1];
			if (nTimestamp > pItem->nTimestamp)
			{
				break;
			}

			if (nTimestamp == pItem->nTimestamp)
			{
				pItem->nUnused = 0;
				strncpy(pItem->szText, szText, sizeof(pItem->szText));
				bReplace = TRUE;
				break;
			}

			--nPosition;
		}

		if (bReplace)
		{
			continue;
		}

		const uint32_t nNewCount = nCount + 1;
		if (nNewCount > nCount)
		{
			gtBnNewsTable.Reserve(nNewCount - nCount, TRUE);
		}
		gtBnNewsTable.m_nCount = nNewCount;

		for (uint32_t i = nNewCount - 1; i > nPosition; --i)
		{
			memcpy(&gtBnNewsTable.m_pData[i], &gtBnNewsTable.m_pData[i - 1], sizeof(NewsTable::Item));
		}

		NewsTable::Item* pItem = &gtBnNewsTable.m_pData[nPosition];
		pItem->nUnused = 0;
		pItem->nTimestamp = nTimestamp;
		strncpy(pItem->szText, szText, sizeof(pItem->szText));
	}

	gnBnNewsTimestamp = nNewestTimestamp;

	uint32_t nFirstItem = 0;
	while (nFirstItem < gtBnNewsTable.m_nCount && gtBnNewsTable.m_pData[nFirstItem].nTimestamp < nOldestTimestamp)
	{
		++nFirstItem;
	}
	gnBnNewsFirstItem = nFirstItem;

	const uint32_t nCount = gtBnNewsTable.m_nCount;
	const uint32_t itemUsedCount = nCount - nFirstItem;
	D2_ASSERT(itemUsedCount < BATTLENETCHAT_NEWSTABLE_MAXITEMS);

	uint32_t nCacheSize = 2 * sizeof(uint32_t);
	BOOL bValid = TRUE;
	for (uint32_t i = nFirstItem; i < nCount; ++i)
	{
		const size_t nLength = strlen(gtBnNewsTable.m_pData[i].szText);
		if (nLength >= sizeof(NewsTable::Item::szText))
		{
			bValid = FALSE;
			break;
		}

		nCacheSize += sizeof(uint32_t) + nLength + 1;
	}

	if (bValid)
	{
		if (uint32_t* pCache = (uint32_t*)D2_ALLOC(nCacheSize))
		{
			pCache[0] = gnBnNewsTimestamp;
			pCache[1] = itemUsedCount;

			uint8_t* pOutput = (uint8_t*)&pCache[2];
			for (uint32_t i = gnBnNewsFirstItem; i < nCount; ++i)
			{
				const NewsTable::Item* pItem = &gtBnNewsTable.m_pData[i];
				*(uint32_t*)pOutput = pItem->nTimestamp;
				pOutput += sizeof(uint32_t);

				const size_t nLength = strlen(pItem->szText);
				strcpy((char*)pOutput, pItem->szText);
				pOutput += nLength + 1;
			}

			SYSTEMTIME tSystemTime;
			GetSystemTime(&tSystemTime);
			FILETIME tFileTime;
			SystemTimeToFileTime(&tSystemTime, &tFileTime);
			BNCACHE_StoreFile(gszBnNewsCacheFileName, pCache, nCacheSize, &tFileTime, -1, -1);

			D2_FREE(pCache);
		}
	}

	BNNEWS_NotifyNews();
	return TRUE;
}
