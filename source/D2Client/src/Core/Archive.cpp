#include "Core/Archive.h"

#include <D2WinArchive.h>


//D2Client.0x6FAA1000
D2CellFileStrc* __fastcall CLIENT_LoadCellFile(const char* szFile, int32_t nType)
{
	char szPath[260];
	strcpy(szPath, szFile);
	strcat(szPath, D2CMP_GetGfxFileExtension(nType));

	void* pFile = ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(D2Win_GetArchive(), szPath, nullptr);

	D2CellFileStrc* pCellFile = nullptr;
	D2CMP_CelFileNormalize((D2CellFileStrc*)pFile, &pCellFile, __FILE__, __LINE__, -1, 0);
	return pCellFile;
}

//D2Client.0x6FAA10A0
D2CellFileStrc* __fastcall CLIENT_LoadCellFileWithFileSize(const char* szFile, size_t* pFileSize, int32_t nType)
{
	char szPath[260];
	strcpy(szPath, szFile);
	strcat(szPath, D2CMP_GetGfxFileExtension(nType));

	void* pFile = ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(D2Win_GetArchive(), szPath, pFileSize);

	D2CellFileStrc* pCellFile = nullptr;
	D2CMP_CelFileNormalize((D2CellFileStrc*)pFile, &pCellFile, __FILE__, __LINE__, -1, 0);
	return pCellFile;
}

//D2Client.0x6FAA1140
void __fastcall CLIENT_FreeCellFile(D2CellFileStrc* pCellFile)
{
	D2CMP_CelFileFreeHardware(pCellFile);

	if (pCellFile)
	{
		D2_FREE(pCellFile);
	}
}
