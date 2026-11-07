#include "DataTbls/CustomNpcTbls.h"

#include "DataTbls/ExtraTxtColumns.h"

#include <mutex>

// Mod: custom NPC classes, see CustomNpcTbls.h. Not part of the original game.

static D2CustomNpcTxt* sgpCustomNpcs = nullptr;
static int sgnCustomNpcs = 0;
static bool sgbCustomNpcsLoaded = false;
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
	if (pRecord->nTradeAs <= 0 && !pRecord->dwRepair && !pRecord->dwHeal)
	{
		return nullptr;
	}

	return pRecord;
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
