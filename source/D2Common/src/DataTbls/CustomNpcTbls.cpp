#include "DataTbls/CustomNpcTbls.h"

#include "DataTbls/ExtraTxtColumns.h"
#include <D2Lang.h>

#include <cstring>
#include <mutex>

// Mod: custom NPC classes, see CustomNpcTbls.h. Not part of the original game.

static D2CustomNpcTxt* sgpCustomNpcs = nullptr;
static int sgnCustomNpcs = 0;
static bool sgbCustomNpcsLoaded = false;

constexpr int CUSTOMNPC_GOSSIP_LINES = 4;

struct D2CustomNpcGossipTxt
{
	char szGossip[CUSTOMNPC_GOSSIP_LINES][32];
	int16_t nGossipTbl[CUSTOMNPC_GOSSIP_LINES];	// resolved, -1 when not found
};

static D2CustomNpcGossipTxt* sgpCustomNpcGossip = nullptr;
static int sgnCustomNpcGossip = 0;
static std::mutex sgCustomNpcsMutex;

static void DATATBLS_EnsureCustomNpcsLoaded()
{
	if (sgbCustomNpcsLoaded)
	{
		return;
	}

	std::lock_guard<std::mutex> lock(sgCustomNpcsMutex);
	if (sgbCustomNpcsLoaded)
	{
		return;
	}

	D2BinFieldStrc pTbl[] =
	{
		{ "NpcTrade", TXTFIELD_DWORD, 0, offsetof(D2CustomNpcTxt, nTradeAs), NULL },
		{ "NpcRepair", TXTFIELD_DWORD, 0, offsetof(D2CustomNpcTxt, dwRepair), NULL },
		{ "NpcHeal", TXTFIELD_DWORD, 0, offsetof(D2CustomNpcTxt, dwHeal), NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL },
	};

	sgpCustomNpcs = (D2CustomNpcTxt*)DATATBLS_LoadExtraTxtColumns("monstats", pTbl, "NpcTrade", sizeof(D2CustomNpcTxt), &sgnCustomNpcs);

	D2BinFieldStrc pGossipTbl[] =
	{
		{ "NpcGossip1", TXTFIELD_ASCII, 31, offsetof(D2CustomNpcGossipTxt, szGossip[0]), NULL },
		{ "NpcGossip2", TXTFIELD_ASCII, 31, offsetof(D2CustomNpcGossipTxt, szGossip[1]), NULL },
		{ "NpcGossip3", TXTFIELD_ASCII, 31, offsetof(D2CustomNpcGossipTxt, szGossip[2]), NULL },
		{ "NpcGossip4", TXTFIELD_ASCII, 31, offsetof(D2CustomNpcGossipTxt, szGossip[3]), NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL },
	};

	sgpCustomNpcGossip = (D2CustomNpcGossipTxt*)DATATBLS_LoadExtraTxtColumns("monstats", pGossipTbl, "NpcGossip1", sizeof(D2CustomNpcGossipTxt), &sgnCustomNpcGossip);
	for (int i = 0; i < sgnCustomNpcGossip; ++i)
	{
		for (int j = 0; j < CUSTOMNPC_GOSSIP_LINES; ++j)
		{
			D2CustomNpcGossipTxt* pRecord = &sgpCustomNpcGossip[i];
			pRecord->nGossipTbl[j] = -1;
			if (pRecord->szGossip[j][0])
			{
				const Unicode* pUnused = nullptr;
				const int16_t nIndex = D2LANG_GetTblIndex(pRecord->szGossip[j], &pUnused);
				pRecord->nGossipTbl[j] = nIndex > 0 ? nIndex : -1;
			}
		}
	}

	// A row that only has gossip still needs a record: give it an empty one (the gossip table may have more rows).
	if (sgnCustomNpcGossip > sgnCustomNpcs)
	{
		D2CustomNpcTxt* pResized = (D2CustomNpcTxt*)D2_CALLOC_POOL(nullptr, sizeof(D2CustomNpcTxt) * sgnCustomNpcGossip);
		if (sgpCustomNpcs)
		{
			memcpy(pResized, sgpCustomNpcs, sizeof(D2CustomNpcTxt) * sgnCustomNpcs);
			D2_FREE_POOL(nullptr, sgpCustomNpcs);
		}
		sgpCustomNpcs = pResized;
		sgnCustomNpcs = sgnCustomNpcGossip;
	}

	sgbCustomNpcsLoaded = true;
}

const D2CustomNpcTxt* __fastcall DATATBLS_GetCustomNpcTxtRecord(int nMonStatsId)
{
	DATATBLS_EnsureCustomNpcsLoaded();

	if (nMonStatsId < 0 || nMonStatsId >= sgnCustomNpcs)
	{
		return nullptr;
	}

	const D2CustomNpcTxt* pRecord = &sgpCustomNpcs[nMonStatsId];
	if (pRecord->nTradeAs <= 0 && !pRecord->dwRepair && !pRecord->dwHeal && DATATBLS_GetCustomNpcGossipTblIndex(nMonStatsId, 0) == -1)
	{
		return nullptr;
	}

	return pRecord;
}

int __fastcall DATATBLS_GetCustomNpcGossipTblIndex(int nMonStatsId, int nIndex)
{
	DATATBLS_EnsureCustomNpcsLoaded();

	if (nMonStatsId < 0 || nMonStatsId >= sgnCustomNpcGossip || nIndex < 0 || nIndex >= CUSTOMNPC_GOSSIP_LINES)
	{
		return -1;
	}

	return sgpCustomNpcGossip[nMonStatsId].nGossipTbl[nIndex];
}

int __fastcall DATATBLS_GetCustomNpcClassIds(int* pClassIds, int nMax)
{
	DATATBLS_EnsureCustomNpcsLoaded();

	int nCount = 0;
	for (int i = 0; i < sgnCustomNpcs; ++i)
	{
		if (DATATBLS_GetCustomNpcTxtRecord(i))
		{
			if (pClassIds && nCount < nMax)
			{
				pClassIds[nCount] = i;
			}
			++nCount;
		}
	}

	return nCount;
}

//D2Common.#11313
const D2CustomNpcTxt* __stdcall DATATBLS_GetCustomNpcRecord(int nMonStatsId)
{
	return DATATBLS_GetCustomNpcTxtRecord(nMonStatsId);
}

//D2Common.#11314
int __stdcall DATATBLS_ListCustomNpcs(int* pClassIds, int nMax)
{
	return DATATBLS_GetCustomNpcClassIds(pClassIds, nMax);
}

//D2Common.#11318
int __stdcall DATATBLS_GetCustomNpcGossip(int nMonStatsId, int nIndex)
{
	return DATATBLS_GetCustomNpcGossipTblIndex(nMonStatsId, nIndex);
}
