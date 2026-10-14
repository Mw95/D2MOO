#pragma once

#include <Windows.h>

#include <cstdint>

#include <BnClient.h>

#define BATTLENETCHAT_NEWSTABLE_MAXITEMS 256

#pragma pack(push, 1)
// Storm's TSGrowableArray<NewsTable::Item>
struct NewsTable
{
	struct Item
	{
		uint32_t nUnused;				//0x000
		uint32_t nTimestamp;			//0x004
		char szText[0x400];				//0x008
	};

	uint32_t m_nAllocated;				//0x00
	uint32_t m_nCount;					//0x04
	Item* m_pData;						//0x08
	uint32_t m_nChunkSize;				//0x0C

	NewsTable();
	~NewsTable();
	void Clear();
	void Reserve(uint32_t nAmount, BOOL bRoundToChunk);
};
#pragma pack(pop)

void __fastcall BNNEWS_SetProduct(BOOL bClassic);
BOOL __fastcall BNNEWS_LoadBNetNews(BnNewsItemCallback pfItemCallback, BnNewsDoneCallback pfDoneCallback);
BOOL __stdcall BNNEWS_FreeBNetNews();
BOOL __fastcall BNNEWS_StoreNewsInfo(const uint8_t* pData, uint32_t nSize);
