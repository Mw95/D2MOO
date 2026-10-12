#include "TileProjects.h"

#include <cstring>

#include <Archive.h>
#include <Fog.h>

#include "FindTiles.h"
#include "TileCache.h"
#include "Tilecmp.h"


static D2TileRecordStrc* sgpTileRecords;	//D2CMP.0x6FEF1DD8


//D2CMP.0x6FE00140 (#10094)
void __stdcall D2CMP_DestroyTileHeaders()
{
	D2TileRecordStrc* ptRecord = sgpTileRecords;
	while (ptRecord)
	{
		D2TileRecordStrc* ptNext = ptRecord->pNext;
		D2CMP_TileProjectDestroy(ptRecord->pLibrary, FALSE);
		ptRecord->pLibrary = nullptr;
		FINDTILES_DestroyHash(ptRecord->pHashBlock);
		ptRecord->pHashBlock = nullptr;
		D2_FREE(ptRecord);
		ptRecord = ptNext;
	}

	sgpTileRecords = nullptr;
}

//D2CMP.0x6FE001A0 (#10095)
D2TileLibraryHeaderStrc* __stdcall D2CMP_LoadProjectRecord(D2TileLibraryHashStrc** ppHash, const char* szFileName)
{
	for (D2TileRecordStrc* ptRecord = sgpTileRecords; ptRecord; ptRecord = ptRecord->pNext)
	{
		if (!strcmp(ptRecord->szLibraryName, szFileName))
		{
			*ppHash = ptRecord->pHashBlock;
			return ptRecord->pLibrary;
		}
	}

	const int nHeaderSize = TILECACHE_GetProjectHeaderSize(szFileName);
	D2TileLibraryHeaderStrc* ptData = (D2TileLibraryHeaderStrc*)D2_ALLOC(nHeaderSize);
	D2_ASSERT(ptData);
	memset(ptData, 0x00, nHeaderSize);

	HSFILE hFile = nullptr;
	ARCHIVE_OpenFile(nullptr, szFileName, &hFile, FALSE);
	ARCHIVE_ReadFileToBuffer(nullptr, hFile, ptData, nHeaderSize);
	ARCHIVE_CloseFile(nullptr, hFile);

	D2TileLibraryHeaderStrc* ptProject = nullptr;
	TILECMP_NormalizeHeaderOnly(ptData, &ptProject, szFileName);
	D2TileLibraryHashStrc* ptHash = TILECMP_CreateFindTileHash(ptProject);

	D2TileRecordStrc* ptRecord = D2_ALLOC_STRC(D2TileRecordStrc);
	D2_ASSERT(ptRecord);
	memset(ptRecord, 0x00, sizeof(*ptRecord));
	ptRecord->pNext = sgpTileRecords;
	sgpTileRecords = ptRecord;
	ptRecord->pHashBlock = ptHash;
	ptRecord->pLibrary = ptProject;
	strcpy(ptRecord->szLibraryName, szFileName);

	*ppHash = ptRecord->pHashBlock;
	return ptProject;
}
