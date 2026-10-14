#pragma once

#include <Windows.h>

#include <cstdint>

enum BnDownloadRequestType : uint32_t
{
	BNDOWNLOAD_REQUEST_VERSIONING = 0x80000001,
	BNDOWNLOAD_REQUEST_PATCH = 0x80000002,
	BNDOWNLOAD_REQUEST_AD = 0x80000003,
	BNDOWNLOAD_REQUEST_BNSERVER_INI = 0x80000004,
	BNDOWNLOAD_REQUEST_EXTRAWORK = 0x80000005,
	BNDOWNLOAD_REQUEST_REQUIREDWORK = 0x80000006,
};

enum BnDownloadFlags : uint32_t
{
	BNDOWNLOAD_FLAG_CACHE = 0x1,		// Store the downloaded file in bncache.dat
	BNDOWNLOAD_FLAG_DISK = 0x2,			// Write the downloaded file to the disk
	BNDOWNLOAD_FLAG_MEMORY = 0x4,		// Keep the downloaded file in memory only
};

enum BnDownloadStatus
{
	// Values 0 to 100 are the patch download progress percentage
	BNDOWNLOADSTATUS_PATCH_DONE = 101,
	BNDOWNLOADSTATUS_IDLE = 102,
};

enum BnUpgradeStatus
{
	BNUPGRADESTATUS_FAILED = -1,
	BNUPGRADESTATUS_NONE = 0,
	BNUPGRADESTATUS_LAUNCHED = 2,
};

#pragma pack(push, 1)
// BNFTP protocol request, followed by our own data
struct BnFtpRequest
{
	uint16_t nRequestLength;			//0x000
	uint16_t nProtocolVersion;			//0x002
	uint32_t nPlatformId;				//0x004
	uint32_t nProductId;				//0x008
	uint32_t nAdId;						//0x00C
	uint32_t nAdFileExtension;			//0x010
	uint32_t nStartPosition;			//0x014
	FILETIME tFileTime;					//0x018
	char szFileName[260];				//0x020
	char szSaveName[260];				//0x124
	uint32_t nType;						//0x228
	uint32_t nFlags;					//0x22C
};

// BNFTP protocol response header
struct BnFtpHeader
{
	uint16_t nHeaderLength;				//0x00
	uint16_t nType;						//0x02
	uint32_t nFileSize;					//0x04
	uint32_t nAdId;						//0x08
	uint32_t nAdFileExtension;			//0x0C
	FILETIME tFileTime;					//0x10
	char szFileName[1];					//0x18
};

struct BnReceivedAd
{
	uint32_t nAdId;						//0x00
	uint32_t nAdFileExtension;			//0x04
	char* szFileName;					//0x08
	char* szLinkUrl;					//0x0C
	void* pData;						//0x10
	uint32_t nDataSize;					//0x14
};

struct BnExtraWorkInfo
{
	uint16_t nGameType;					//0x000
	uint16_t nLength;					//0x002
	uint32_t nLocale;					//0x004
	uint8_t pData[0x1000 - 4];			//0x008
};
#pragma pack(pop)

using BnExtraWorkFunction = BOOL(__fastcall*)(BnExtraWorkInfo* pInfo);
using BnCheckRevisionFunction = BOOL(__stdcall*)(const char* szFileName1, const char* szFileName2, const char* szFileName3, const char* szValueString, uint32_t* pVersion, uint32_t* pChecksum, char* szExeInfo);

BOOL __fastcall BNDOWNLOAD_SetPatchFiles(const char* szPatchFiles, uint32_t nSize);
BOOL __fastcall BNDOWNLOAD_SetVersionFormula(const char* szFormula);
BOOL __fastcall BNDOWNLOAD_RequestFileTime(const char* szFileName, uint32_t nRequestId);
void __fastcall BNDOWNLOAD_RequestFile(uint32_t nType, uint32_t nFlags, uint32_t nAdId, uint32_t nAdFileExtension, FILETIME* pFileTime, const char* szFileName, const char* szSaveName);
void __fastcall BNDOWNLOAD_ProcessFile(uint32_t nType, uint32_t nFlags, uint32_t nAdId, uint32_t nAdFileExtension, FILETIME* pFileTime, const char* szFileName, const char* szSaveName, void* pBuffer, uint32_t nBufferSize, BOOL bFromCache);
BOOL __fastcall BNDOWNLOAD_ExtractDll(HANDLE hArchive, char* szDllFileName, const char* szArchiveFileName);
void __stdcall BNDOWNLOAD_CancelAll();
BOOL __stdcall BNDOWNLOAD_IsActive();
unsigned __stdcall BNDOWNLOAD_DownloadThread(void* pParam);
BOOL __fastcall BNDOWNLOAD_CheckRevision(uint32_t* pVersion, uint32_t* pChecksum, char* szExeInfo);
BOOL __fastcall BNDOWNLOAD_RunUpgrade(BOOL* pbQuit);
BOOL __fastcall BNDOWNLOAD_ApplyPatch(int32_t* upgradestatus);
void __fastcall BNDOWNLOAD_SetStatus(int32_t nStatus);
int32_t __stdcall BNDOWNLOAD_GetStatus();
BOOL __fastcall BNDOWNLOAD_StartPatch(const char* szPatchFiles, uint32_t nSize);
BOOL __fastcall BNDOWNLOAD_SetVersionFile(const char* szFileName);
BOOL __stdcall BNDOWNLOAD_HasVersionFile();
