#include "SaveLoad.h"

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <ctime>

#include <Fog.h>
#include <Storm.h>

#include "BNet.h"


constexpr uint32_t SAVE_HEADER_MAGIC = 0xAA55AA55;
constexpr uint32_t SAVE_VERSION_CURRENT = 0x60;
constexpr uint32_t SAVE_VERSION_OLD_FORMAT_MAX = 0x5B;
constexpr uint32_t SAVE_VERSION_OLD_FORMAT_MIN = 0x47;
constexpr size_t SAVE_OLD_HEADER_SIZE = 0x82;
constexpr size_t SAVE_READ_BUFFER_SIZE = 0x2000;

enum D2SaveStatusFlags : uint32_t
{
	SAVESTATUS_NEWBIE = 0x01,
	SAVESTATUS_REALM = 0x02,
	SAVESTATUS_EXPANSION = 0x20,
};

#pragma pack(push, 1)
// Header of a .d2s file (version 0x60 / 1.10)
struct D2SaveHeaderStrc
{
	uint32_t dwMagic;							//0x00
	uint32_t dwVersion;							//0x04
	uint32_t dwSize;							//0x08
	uint32_t dwChecksum;						//0x0C
	uint32_t dwWeaponSet;						//0x10
	char szName[16];							//0x14
	uint32_t dwStatus;							//0x24
	uint8_t nClass;								//0x28
	uint8_t nStats;								//0x29
	uint8_t nSkills;							//0x2A
	uint8_t nLevel;								//0x2B
	uint32_t dwCreateTime;						//0x2C
	uint32_t dwLastPlayed;						//0x30
	uint8_t unk0x34[0x54];						//0x34
	uint8_t pComponents[16];					//0x88
	uint8_t pComponentColors[16];				//0x98
	uint8_t unk0xA8[0xA7];						//0xA8
};

// Header of a .d2s file (versions 0x47 to 0x5B)
struct D2OldSaveHeaderStrc
{
	uint32_t dwMagic;							//0x00
	uint32_t dwVersion;							//0x04
	uint8_t unk0x08[0x10];						//0x08
	uint32_t dwStatus;							//0x18
	uint8_t unk0x1C[0x06];						//0x1C
	uint8_t nClass;								//0x22
	uint8_t unk0x23;							//0x23
	uint8_t nLevel;								//0x24
	uint8_t unk0x25;							//0x25
	uint8_t pComponents[16];					//0x26
	uint8_t pComponentColors[16];				//0x36
	uint8_t unk0x46[0x3C];						//0x46
};
#pragma pack(pop)

static_assert(sizeof(D2SaveHeaderStrc) == 0x14F, "D2SaveHeaderStrc size must be 0x14F");
static_assert(sizeof(D2OldSaveHeaderStrc) == SAVE_OLD_HEADER_SIZE, "D2OldSaveHeaderStrc size must be 0x82");


//D2Launch.0x6FA3D118
uint32_t sgdwHeaderHash;
//D2Launch.0x6FA3D120
D2SaveHeaderStrc sgSaveHeader;
//D2Launch.0x6FA3D270
uint32_t sgdwGameTimeHash;

//D2Launch.0x6FA38A98
static const uint8_t sgaDefaultComponents[16] = { 1, 1, 1, 1, 1, 0xFF, 0xFF, 0xFF, 1, 1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };


// Helper function, inlined in the original game
static void SAVE_EncodePreviewInfo(D2CharacterPreviewInfoStrc* pPreviewInfo, const uint8_t* pComponents, uint8_t nClass, const uint8_t* pComponentColors, uint8_t nLevel, uint16_t nSaveFlags)
{
	FOG_Encode14BitsToString(&pPreviewInfo->nVersion, 10);
	memcpy(pPreviewInfo->pComponents, pComponents, sizeof(pPreviewInfo->pComponents));
	pPreviewInfo->nClass = nClass + 1;
	memcpy(pPreviewInfo->pComponentColors, pComponentColors, sizeof(pPreviewInfo->pComponentColors));
	pPreviewInfo->nLevel = nLevel;
	FOG_Encode14BitsToString(&pPreviewInfo->nClientFlags, nSaveFlags);
	FOG_Encode14BitsToString(&pPreviewInfo->nGuildFlags, 0);
	pPreviewInfo->nGuildEmblemBgColor = 0xFF;
	pPreviewInfo->nGuildEmblemFgColor = 0xFF;
	pPreviewInfo->nGuildEmblemType = 0xFF;
}

//D2Launch.0x6FA279F0
void __fastcall SAVE_CreateCharacter(const char* szName, uint8_t nClass, D2CharacterPreviewInfoStrc* pPreviewInfo, uint16_t nSaveFlags)
{
	memset(&sgSaveHeader, 0x00, sizeof(sgSaveHeader));
	sgSaveHeader.dwMagic = SAVE_HEADER_MAGIC;
	sgSaveHeader.dwVersion = SAVE_VERSION_CURRENT;
	SStrCopy(sgSaveHeader.szName, szName, 0x7FFFFFFF);
	sgSaveHeader.nClass = nClass;
	sgSaveHeader.nLevel = 1;
	sgSaveHeader.dwStatus = nSaveFlags | SAVESTATUS_NEWBIE;

	const uint32_t dwTime = (uint32_t)time(nullptr);
	sgSaveHeader.dwCreateTime = dwTime;
	sgSaveHeader.dwLastPlayed = dwTime;
	sgSaveHeader.dwSize = sizeof(sgSaveHeader);
	sgSaveHeader.nStats = 0x10;
	sgSaveHeader.nSkills = 0x1E;

	if (nClass == 6 || nClass == 5)
	{
		sgSaveHeader.dwStatus |= SAVESTATUS_EXPANSION;
	}

	memcpy(sgSaveHeader.pComponents, sgaDefaultComponents, sizeof(sgSaveHeader.pComponents));
	memset(sgSaveHeader.pComponentColors, 0xFF, sizeof(sgSaveHeader.pComponentColors));

	uint8_t aComponentColors[11];
	memset(aComponentColors, 0xFF, sizeof(aComponentColors));
	SAVE_EncodePreviewInfo(pPreviewInfo, sgaDefaultComponents, nClass, aComponentColors, 1, (uint16_t)sgSaveHeader.dwStatus);
	strcpy((char*)&pPreviewInfo->szGuildTag, gszEmptyString);
}

//D2Launch.0x6FA27B50
void __fastcall SAVE_SetRealmCharacter(BOOL bRealm)
{
	if (bRealm)
	{
		sgSaveHeader.dwStatus |= SAVESTATUS_REALM;
	}
}

//D2Launch.0x6FA27B60
BOOL __fastcall SAVE_WriteCharacterFile(const char* szName)
{
	char szSavePath[1024];
	char szFileName[512];
	DWORD dwBytesWritten = 0;

	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	sprintf(szFileName, "%s%s.d2s", szSavePath, szName);

	HANDLE hFile = FOG_CreateFileA(szFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
	if (!hFile)
	{
		return FALSE;
	}

	sgSaveHeader.dwChecksum = FOG_ComputeChecksum(&sgSaveHeader, sizeof(sgSaveHeader));
	FOG_WriteFile(hFile, &sgSaveHeader, sizeof(sgSaveHeader), &dwBytesWritten, nullptr);
	FOG_CloseFile(hFile);
	return TRUE;
}

//D2Launch.0x6FA27C00
void __fastcall SAVE_DeleteCharacter(const char* pszFileName, const char* szSubDirectory)
{
	char szSavePath[MAX_PATH];
	char szDirectory[MAX_PATH];
	char szFilePath[512];
	char szSearchPath[512];
	WIN32_FIND_DATAA findData;

	D2_ASSERT(*pszFileName != '\0');

	FOG_GetSavePath(szSavePath, sizeof(szSavePath));

	if (szSubDirectory && szSubDirectory[0])
	{
		SStrPrintf(szDirectory, sizeof(szDirectory), "%s%s\\", szSavePath, szSubDirectory);
		FOG_CreatePathHierarchy(szDirectory);
		SStrCopy(szSavePath, szDirectory, sizeof(szSavePath));
	}

	sprintf(szSearchPath, "%s%s.*", szSavePath, pszFileName);

	HANDLE hFind = FindFirstFileA(szSearchPath, &findData);
	while (hFind != INVALID_HANDLE_VALUE)
	{
		sprintf(szFilePath, "%s%s", szSavePath, findData.cFileName);

		if (GetFileAttributesA(szFilePath) & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!FindNextFileA(hFind, &findData))
			{
				break;
			}
		}
		else
		{
			if (!DeleteFileA(szFilePath))
			{
				break;
			}

			hFind = FindFirstFileA(szSearchPath, &findData);
		}
	}
}

//D2Launch.0x6FA27D50
void __fastcall SAVE_InitializeHashes()
{
	sgdwHeaderHash = SStrHash("Header", 0, 0);
	sgdwGameTimeHash = SStrHash("Game Time", 0, 0);
}

// Static initializer, the original game registered SAVE_InitializeHashes in the CRT initializer table
static const int sgnSaveHashesInitializer = (SAVE_InitializeHashes(), 0);

//D2Launch.0x6FA27D80
BOOL __fastcall SAVE_ReadCharacterPreview(const char* pszFileName, uint8_t* pPreviewInfo)
{
	char szSavePath[1024];
	char szFileName[512];
	uint8_t pBuffer[SAVE_READ_BUFFER_SIZE];

	D2_ASSERT(*pszFileName != '\0');

	BOOL bResult = FALSE;
	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	sprintf(szFileName, "%s%s.d2s", szSavePath, pszFileName);

	FILE* pFile = fopen(szFileName, "rb");
	if (!pFile)
	{
		return FALSE;
	}

	const size_t nRead = fread(pBuffer, 1, sizeof(pBuffer), pFile);
	const D2SaveHeaderStrc* pHeader = (const D2SaveHeaderStrc*)pBuffer;
	const D2OldSaveHeaderStrc* pOldHeader = (const D2OldSaveHeaderStrc*)pBuffer;
	if (nRead >= 8 && pHeader->dwMagic == SAVE_HEADER_MAGIC)
	{
		const uint8_t* pComponents = nullptr;
		const uint8_t* pComponentColors = nullptr;
		uint8_t nClass = 0;
		uint8_t nLevel = 0;
		uint32_t dwStatus = 0;
		BOOL bValid = FALSE;

		if (pHeader->dwVersion <= SAVE_VERSION_OLD_FORMAT_MAX)
		{
			if (nRead >= SAVE_OLD_HEADER_SIZE && pHeader->dwVersion >= SAVE_VERSION_OLD_FORMAT_MIN)
			{
				nLevel = pOldHeader->nLevel;
				dwStatus = pOldHeader->dwStatus;
				nClass = pOldHeader->nClass;
				pComponents = pOldHeader->pComponents;
				pComponentColors = pOldHeader->pComponentColors;
				bValid = TRUE;
			}
		}
		else if (nRead >= sizeof(D2SaveHeaderStrc) && pHeader->dwVersion <= SAVE_VERSION_CURRENT)
		{
			nLevel = pHeader->nLevel;
			dwStatus = pHeader->dwStatus;
			nClass = pHeader->nClass;
			pComponents = pHeader->pComponents;
			pComponentColors = pHeader->pComponentColors;
			bValid = TRUE;
		}

		if (bValid)
		{
			D2CharacterPreviewInfoStrc* pInfo = (D2CharacterPreviewInfoStrc*)pPreviewInfo;
			SAVE_EncodePreviewInfo(pInfo, pComponents[0] ? pComponents : sgaDefaultComponents, nClass, pComponentColors, nLevel, (uint16_t)dwStatus);
			((char*)&pInfo->szGuildTag)[0] = 0;
			bResult = TRUE;
		}
	}

	fclose(pFile);
	return bResult;
}

//D2Launch.0x6FA27F80
BOOL __fastcall SAVE_ConvertCharacterToExpansion(const char* szName)
{
	char szSavePath[1024];
	char szFileName[512];
	uint8_t pBuffer[SAVE_READ_BUFFER_SIZE];
	DWORD dwBytesRead = 0;
	DWORD dwBytesWritten = 0;

	FOG_GetSavePath(szSavePath, sizeof(szSavePath));
	sprintf(szFileName, "%s%s.d2s", szSavePath, szName);

	HANDLE hFile = FOG_CreateFileA(szFileName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
	if (!hFile)
	{
		return FALSE;
	}

	FOG_ReadFile(hFile, pBuffer, sizeof(pBuffer), &dwBytesRead, nullptr);
	if (dwBytesRead < 8)
	{
		return FALSE;
	}

	D2SaveHeaderStrc* pHeader = (D2SaveHeaderStrc*)pBuffer;
	if (pHeader->dwMagic != SAVE_HEADER_MAGIC)
	{
		return FALSE;
	}

	BOOL bResult = FALSE;
	if (pHeader->dwVersion <= SAVE_VERSION_OLD_FORMAT_MAX)
	{
		if (dwBytesRead < SAVE_OLD_HEADER_SIZE)
		{
			return FALSE;
		}

		uint32_t dwStatus = ((D2OldSaveHeaderStrc*)pBuffer)->dwStatus | SAVESTATUS_EXPANSION;
		FOG_SetFilePointer(hFile, offsetof(D2OldSaveHeaderStrc, dwStatus), nullptr, FILE_BEGIN);
		bResult = FOG_WriteFile(hFile, &dwStatus, sizeof(dwStatus), &dwBytesWritten, nullptr);
	}
	else
	{
		if (dwBytesRead < sizeof(D2SaveHeaderStrc))
		{
			return FALSE;
		}

		pHeader->dwStatus |= SAVESTATUS_EXPANSION;
		pHeader->dwChecksum = 0;
		pHeader->dwChecksum = FOG_ComputeChecksum(pBuffer, dwBytesRead);
		FOG_SetFilePointer(hFile, 0, nullptr, FILE_BEGIN);
		bResult = FOG_WriteFile(hFile, pBuffer, dwBytesRead, &dwBytesWritten, nullptr);
	}

	FOG_CloseFile(hFile);
	return bResult;
}
