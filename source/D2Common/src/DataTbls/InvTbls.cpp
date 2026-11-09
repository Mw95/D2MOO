#include <DataTbls/InvTbls.h>
#include <D2DataTbls.h>
#include <Archive.h>

// DIFFERENCE: not in the original game. The cloak slot's rectangle for every inventory.txt record. It is read from the optional
// inventory.txt columns cloakLeft/cloakRight/cloakTop/cloakBottom/cloakWidth/cloakHeight when the tables are compiled from .txt,
// and otherwise (or when the columns are absent or zero) placed left of the helm, mirroring the amulet across it.
static D2InvCompGridStrc gInventoryCloakComponents[NUM_INVENTORY_PAGE_STATS * NUM_GAME_RESOLUTIONS];

static void DATATBLS_SetDefaultCloakComponent(const D2InventoryTxt* pRecord, D2InvCompGridStrc* pCloak)
{
	const D2InvCompGridStrc& tHead = pRecord->pComponents[INV_COMP_HEAD];
	const D2InvCompGridStrc& tNeck = pRecord->pComponents[INV_COMP_NECK];

	*pCloak = {};
	if (tHead.nWidth == 0 || tHead.nHeight == 0 || tHead.rect.nRight <= tHead.rect.nLeft)
	{
		return; // A page without equipment slots (trade, stash, cube...)
	}

	const int32_t nWidth = tHead.rect.nRight - tHead.rect.nLeft;
	int32_t nGap = tNeck.rect.nLeft - tHead.rect.nRight;
	if (tNeck.nWidth == 0 || nGap < 0)
	{
		nGap = 17;
	}

	pCloak->rect.nRight = tHead.rect.nLeft - nGap;
	pCloak->rect.nLeft = pCloak->rect.nRight - nWidth;
	pCloak->rect.nTop = tHead.rect.nTop;
	pCloak->rect.nBottom = tHead.rect.nBottom;
	pCloak->nWidth = tHead.nWidth;
	pCloak->nHeight = tHead.nHeight;
}

static void DATATBLS_LoadInventoryCloakComponents(HD2ARCHIVE hArchive)
{
	const int nRecordCount = sgptDataTables->nInventoryTxtRecordCount;
	memset(gInventoryCloakComponents, 0x00, sizeof(gInventoryCloakComponents));

	if (!DATATBLS_LoadFromBin || sgptDataTables->bCompileTxt)
	{
		// The .bin written by DATATBLS_CompileTxt keeps the original record size, so the extra columns can only be read from the .txt.
		D2BinFieldStrc pCloakTbl[] =
		{
			{ "cloakLeft", TXTFIELD_DWORD, 0, 0, NULL },
			{ "cloakRight", TXTFIELD_DWORD, 0, 4, NULL },
			{ "cloakTop", TXTFIELD_DWORD, 0, 8, NULL },
			{ "cloakBottom", TXTFIELD_DWORD, 0, 12, NULL },
			{ "cloakWidth", TXTFIELD_BYTE, 0, 16, NULL },
			{ "cloakHeight", TXTFIELD_BYTE, 0, 17, NULL },
			{ "end", TXTFIELD_NONE, 0, 0, NULL },
		};

		char szFilePath[MAX_PATH] = {};
		wsprintfA(szFilePath, "%s\\%s%s", "DATA\\GLOBAL\\EXCEL", "inventory", ".txt");

		size_t dwDataSize = 0;
		void* pData = ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(hArchive, szFilePath, &dwDataSize);
		if (pData)
		{
			D2BinFileStrc* pBinFile = FOG_CreateBinFile(pData, dwDataSize);
			if (FOG_GetRecordCountFromBinFile(pBinFile) == nRecordCount)
			{
				FOG_10207(pBinFile, pCloakTbl, gInventoryCloakComponents, nRecordCount, sizeof(D2InvCompGridStrc));
			}
			FOG_FreeBinFile(pBinFile);
		}
	}

	for (int i = 0; i < nRecordCount; ++i)
	{
		D2InvCompGridStrc* pCloak = &gInventoryCloakComponents[i];
		if (pCloak->nWidth == 0 || pCloak->nHeight == 0 || pCloak->rect.nRight <= pCloak->rect.nLeft || pCloak->rect.nBottom <= pCloak->rect.nTop)
		{
			DATATBLS_SetDefaultCloakComponent(&sgptDataTables->pInventoryTxt[i], pCloak);
		}
	}
}

//D2Common.0x6FD542D0
//1.14d: 0x0065B660
void __fastcall DATATBLS_LoadInventoryTxt(HD2ARCHIVE hArchive)
{
	D2BinFieldStrc pTbl[] =
	{
		{ "invLeft", TXTFIELD_DWORD, 0, 0, NULL },
		{ "invRight", TXTFIELD_DWORD, 0, 4, NULL },
		{ "invTop", TXTFIELD_DWORD, 0, 8, NULL },
		{ "invBottom", TXTFIELD_DWORD, 0, 12, NULL },
		{ "gridX", TXTFIELD_BYTE, 0, 16, NULL },
		{ "gridY", TXTFIELD_BYTE, 0, 17, NULL },
		{ "gridLeft", TXTFIELD_DWORD, 0, 20, NULL },
		{ "gridRight", TXTFIELD_DWORD, 0, 24, NULL },
		{ "gridTop", TXTFIELD_DWORD, 0, 28, NULL },
		{ "gridBottom", TXTFIELD_DWORD, 0, 32, NULL },
		{ "gridBoxWidth", TXTFIELD_BYTE, 0, 36, NULL },
		{ "gridBoxHeight", TXTFIELD_BYTE, 0, 37, NULL },
		{ "rArmLeft", TXTFIELD_DWORD, 0, 40, NULL },
		{ "rArmRight", TXTFIELD_DWORD, 0, 44, NULL },
		{ "rArmTop", TXTFIELD_DWORD, 0, 48, NULL },
		{ "rArmBottom", TXTFIELD_DWORD, 0, 52, NULL },
		{ "rArmWidth", TXTFIELD_BYTE, 0, 56, NULL },
		{ "rArmHeight", TXTFIELD_BYTE, 0, 57, NULL },
		{ "torsoLeft", TXTFIELD_DWORD, 0, 60, NULL },
		{ "torsoRight", TXTFIELD_DWORD, 0, 64, NULL },
		{ "torsoTop", TXTFIELD_DWORD, 0, 68, NULL },
		{ "torsoBottom", TXTFIELD_DWORD, 0, 72, NULL },
		{ "torsoWidth", TXTFIELD_BYTE, 0, 76, NULL },
		{ "torsoHeight", TXTFIELD_BYTE, 0, 77, NULL },
		{ "lArmLeft", TXTFIELD_DWORD, 0, 80, NULL },
		{ "lArmRight", TXTFIELD_DWORD, 0, 84, NULL },
		{ "lArmTop", TXTFIELD_DWORD, 0, 88, NULL },
		{ "lArmBottom", TXTFIELD_DWORD, 0, 92, NULL },
		{ "lArmWidth", TXTFIELD_BYTE, 0, 96, NULL },
		{ "lArmHeight", TXTFIELD_BYTE, 0, 97, NULL },
		{ "headLeft", TXTFIELD_DWORD, 0, 100, NULL },
		{ "headRight", TXTFIELD_DWORD, 0, 104, NULL },
		{ "headTop", TXTFIELD_DWORD, 0, 108, NULL },
		{ "headBottom", TXTFIELD_DWORD, 0, 112, NULL },
		{ "headWidth", TXTFIELD_BYTE, 0, 116, NULL },
		{ "headHeight", TXTFIELD_BYTE, 0, 117, NULL },
		{ "neckLeft", TXTFIELD_DWORD, 0, 120, NULL },
		{ "neckRight", TXTFIELD_DWORD, 0, 124, NULL },
		{ "neckTop", TXTFIELD_DWORD, 0, 128, NULL },
		{ "neckBottom", TXTFIELD_DWORD, 0, 132, NULL },
		{ "neckWidth", TXTFIELD_BYTE, 0, 136, NULL },
		{ "neckHeight", TXTFIELD_BYTE, 0, 137, NULL },
		{ "rHandLeft", TXTFIELD_DWORD, 0, 140, NULL },
		{ "rHandRight", TXTFIELD_DWORD, 0, 144, NULL },
		{ "rHandTop", TXTFIELD_DWORD, 0, 148, NULL },
		{ "rHandBottom", TXTFIELD_DWORD, 0, 152, NULL },
		{ "rHandWidth", TXTFIELD_BYTE, 0, 156, NULL },
		{ "rHandHeight", TXTFIELD_BYTE, 0, 157, NULL },
		{ "lHandLeft", TXTFIELD_DWORD, 0, 160, NULL },
		{ "lHandRight", TXTFIELD_DWORD, 0, 164, NULL },
		{ "lHandTop", TXTFIELD_DWORD, 0, 168, NULL },
		{ "lHandBottom", TXTFIELD_DWORD, 0, 172, NULL },
		{ "lHandWidth", TXTFIELD_BYTE, 0, 176, NULL },
		{ "lHandHeight", TXTFIELD_BYTE, 0, 177, NULL },
		{ "beltLeft", TXTFIELD_DWORD, 0, 180, NULL },
		{ "beltRight", TXTFIELD_DWORD, 0, 184, NULL },
		{ "beltTop", TXTFIELD_DWORD, 0, 188, NULL },
		{ "beltBottom", TXTFIELD_DWORD, 0, 192, NULL },
		{ "beltWidth", TXTFIELD_BYTE, 0, 196, NULL },
		{ "beltHeight", TXTFIELD_BYTE, 0, 197, NULL },
		{ "feetLeft", TXTFIELD_DWORD, 0, 200, NULL },
		{ "feetRight", TXTFIELD_DWORD, 0, 204, NULL },
		{ "feetTop", TXTFIELD_DWORD, 0, 208, NULL },
		{ "feetBottom", TXTFIELD_DWORD, 0, 212, NULL },
		{ "feetWidth", TXTFIELD_BYTE, 0, 216, NULL },
		{ "feetHeight", TXTFIELD_BYTE, 0, 217, NULL },
		{ "glovesLeft", TXTFIELD_DWORD, 0, 220, NULL },
		{ "glovesRight", TXTFIELD_DWORD, 0, 224, NULL },
		{ "glovesTop", TXTFIELD_DWORD, 0, 228, NULL },
		{ "glovesBottom", TXTFIELD_DWORD, 0, 232, NULL },
		{ "glovesWidth", TXTFIELD_BYTE, 0, 236, NULL },
		{ "glovesHeight", TXTFIELD_BYTE, 0, 237, NULL },
		{ "end", TXTFIELD_NONE, 0, 0, NULL },
	};

	sgptDataTables->pInventoryTxt = (D2InventoryTxt*)DATATBLS_CompileTxt(hArchive, "inventory", pTbl, &sgptDataTables->nInventoryTxtRecordCount, sizeof(D2InventoryTxt));
	D2_ASSERT(sgptDataTables->nInventoryTxtRecordCount == NUM_INVENTORY_PAGE_STATS * NUM_GAME_RESOLUTIONS);

	DATATBLS_LoadInventoryCloakComponents(hArchive);
}

//D2Common.0x6FD54F10
//1.14d: 0x0065C130
void __fastcall DATATBLS_UnloadInventoryTxt()
{
	DATATBLS_UnloadBin(sgptDataTables->pInventoryTxt);
}

//D2Common.0x6FD54F20 (#10635)
//1.14d: 0x0065C180
void __stdcall DATATBLS_GetInventoryRect(int nInventoryTxtId, int bHigherRes, D2InvRectStrc* pInvRect)
{

	D2_ASSERT(sgptDataTables->pInventoryTxt);

	const int nIndex = nInventoryTxtId + 16 * bHigherRes;
	D2_ASSERT(nIndex < sgptDataTables->nInventoryTxtRecordCount);
	const D2InventoryTxt* pInventoryTxtRecord = &sgptDataTables->pInventoryTxt[nIndex];
	D2_ASSERT(pInventoryTxtRecord);

	pInvRect->nLeft = pInventoryTxtRecord->pRect.nLeft;
	pInvRect->nRight = pInventoryTxtRecord->pRect.nRight;
	pInvRect->nTop = pInventoryTxtRecord->pRect.nTop;
	pInvRect->nBottom = pInventoryTxtRecord->pRect.nBottom;
}

//D2Common.0x6FD54FB0 (#10636)
//1.14d: 0x0065C1F0
void __stdcall DATATBLS_GetInventoryGridInfo(int nInventoryTxtId, int bHigherRes, D2InventoryGridInfoStrc* pInventoryGridInfo)
{
	D2InventoryTxt* pInventoryTxtRecord = NULL;
	int nIndex = nInventoryTxtId + 16 * bHigherRes;

	D2_ASSERT(sgptDataTables->pInventoryTxt);
	D2_ASSERT(nIndex < sgptDataTables->nInventoryTxtRecordCount);
	pInventoryTxtRecord = &sgptDataTables->pInventoryTxt[nIndex];
	D2_ASSERT(pInventoryTxtRecord);

	memcpy(pInventoryGridInfo, &pInventoryTxtRecord->pGridInfo, sizeof(D2InventoryGridInfoStrc));
}

//D2Common.0x6FD55030 (#10637)
//1.14d: 0x0065C270
void __stdcall DATATBLS_GetInventoryComponentGrid(int nInventoryTxtId, int bHigherRes, D2InvCompGridStrc* pInvCompGrid, int nComponent)
{
	int nIndex = nInventoryTxtId + 16 * bHigherRes;

	D2_ASSERT(sgptDataTables->pInventoryTxt);
	D2_ASSERT(nIndex < sgptDataTables->nInventoryTxtRecordCount);

	const D2InventoryTxt* pInventoryTxtRecord = &sgptDataTables->pInventoryTxt[nIndex];
	D2_ASSERT(pInventoryTxtRecord);

	// DIFFERENCE: components past NUM_INV_COMPS come from the side table.
	if (nComponent == INV_COMP_CLOAK)
	{
		memcpy(pInvCompGrid, &gInventoryCloakComponents[nIndex], sizeof(D2InvCompGridStrc));
		return;
	}

	const D2InvCompGridStrc* ptBodyStats = &pInventoryTxtRecord->pComponents[nComponent];
	D2_ASSERT(ptBodyStats);

	memcpy(pInvCompGrid, ptBodyStats, sizeof(D2InvCompGridStrc));
}
