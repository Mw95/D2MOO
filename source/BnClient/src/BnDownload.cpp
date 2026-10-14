#include "BnDownload.h"

#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <process.h>

#include <Fog.h>
#include <Safesock.h>
#include <Storm.h>

#include "BNetGW.h"
#include "BnCache.h"
#include "BnConnect.h"
#include "BnImports.h"
#include "BnMessQueue.h"
#include "BnRecv.h"
#include "BnSend.h"


#pragma warning (disable: 28159)


BOOL gbBnDownloadCancel;
int32_t gnBnDownloadStatus;
CRITICAL_SECTION gtBnDownloadLock;
char gszBnVersionFile[MAX_PATH];
volatile LONG gnBnActiveDownloads;
char gszBnPatchFiles[256];
char gszBnVersionFormula[MAX_PATH];


//Bnclient.0x6FF03300
static void __cdecl BNDOWNLOAD_DeleteLock()
{
	DeleteCriticalSection(&gtBnDownloadLock);
}

//Bnclient.0x6FF032E0
static void __cdecl BNDOWNLOAD_InitializeLock()
{
	InitializeCriticalSection(&gtBnDownloadLock);
	atexit(BNDOWNLOAD_DeleteLock);
}

static const struct BnDownloadStaticInitializer
{
	BnDownloadStaticInitializer()
	{
		BNDOWNLOAD_InitializeLock();
	}
} gtBnDownloadStaticInitializer;

//Bnclient.0x6FF03310
BOOL __fastcall BNDOWNLOAD_SetPatchFiles(const char* szPatchFiles, uint32_t nSize)
{
	EnterCriticalSection(&gtBnDownloadLock);
	SMemCopy(gszBnPatchFiles, szPatchFiles, nSize);
	gnBnDownloadStatus = 0;
	LeaveCriticalSection(&gtBnDownloadLock);
	return TRUE;
}

//Bnclient.0x6FF03350
BOOL __fastcall BNDOWNLOAD_SetVersionFormula(const char* szFormula)
{
	SStrCopy(gszBnVersionFormula, szFormula, sizeof(gszBnVersionFormula));
	return TRUE;
}

//Bnclient.0x6FF03370
BOOL __fastcall BNDOWNLOAD_RequestFileTime(const char* szFileName, uint32_t nRequestId)
{
#pragma pack(push, 1)
	struct BnGetFileTimeRequest
	{
		uint32_t nRequestId;
		uint32_t nUnknown;
		char szFileName[MAX_PATH];
	};
#pragma pack(pop)

	BnGetFileTimeRequest tRequest;
	tRequest.nRequestId = nRequestId;
	tRequest.nUnknown = 0;
	const size_t nLength = SStrCopy(tRequest.szFileName, szFileName, sizeof(tRequest.szFileName));
	BNET_SendPacket(SID_GETFILETIME, &tRequest, offsetof(BnGetFileTimeRequest, szFileName) + nLength + 1);
	return TRUE;
}

//Bnclient.0x6FF033C0
void __fastcall BNDOWNLOAD_RequestFile(uint32_t nType, uint32_t nFlags, uint32_t nAdId, uint32_t nAdFileExtension, FILETIME* pFileTime, const char* szFileName, const char* szSaveName)
{
	if (!szFileName || !*szFileName)
	{
		return;
	}

	if (!szSaveName)
	{
		szSaveName = "";
	}

	FILETIME tCachedFileTime;
	void* pBuffer = nullptr;
	uint32_t nBufferSize = 0;
	if (BNCACHE_LoadFile(szFileName, &tCachedFileTime, &pBuffer, &nBufferSize))
	{
		if (!CompareFileTime(pFileTime, &tCachedFileTime))
		{
			if (nFlags & BNDOWNLOAD_FLAG_DISK)
			{
				HANDLE hFile = FOG_CreateFileA(szFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
				if (hFile != INVALID_HANDLE_VALUE)
				{
					DWORD nBytesWritten;
					FOG_WriteFile(hFile, pBuffer, nBufferSize, &nBytesWritten, nullptr);
					SetFileTime(hFile, pFileTime, pFileTime, pFileTime);
					FOG_CloseFile(hFile);
				}
			}

			BNDOWNLOAD_ProcessFile(nType, nFlags, nAdId, nAdFileExtension, pFileTime, szFileName, szSaveName, pBuffer, nBufferSize, TRUE);
			BNCACHE_FreeFile(pBuffer, nBufferSize);
			return;
		}

		BNCACHE_FreeFile(pBuffer, nBufferSize);
	}

	BnFtpRequest* pRequest = (BnFtpRequest*)SMemAlloc(sizeof(BnFtpRequest), __FILE__, __LINE__, 0);
	if (!pRequest)
	{
		return;
	}

	memset(pRequest, 0x00, sizeof(*pRequest));
	pRequest->nRequestLength = (uint16_t)(offsetof(BnFtpRequest, szFileName) + strlen(szFileName) + 1);
	pRequest->nProtocolVersion = 0x100;
	pRequest->nPlatformId = 'IX86';
	pRequest->nProductId = 'D2DV';
	pRequest->nAdId = nAdId;
	pRequest->nAdFileExtension = nAdFileExtension;
	pRequest->nStartPosition = 0;
	pRequest->nType = nType;
	pRequest->nFlags = nFlags;
	pRequest->tFileTime = *pFileTime;
	SStrCopy(pRequest->szFileName, szFileName, sizeof(pRequest->szFileName));
	SStrCopy(pRequest->szSaveName, szSaveName, sizeof(pRequest->szSaveName));

	InterlockedIncrement(&gnBnActiveDownloads);

	unsigned int nThreadId;
	if (HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, BNDOWNLOAD_DownloadThread, pRequest, 0, &nThreadId))
	{
		CloseHandle(hThread);
	}
}

//Bnclient.0x6FF035B0
void __fastcall BNDOWNLOAD_ProcessFile(uint32_t nType, uint32_t nFlags, uint32_t nAdId, uint32_t nAdFileExtension, FILETIME* pFileTime, const char* szFileName, const char* szSaveName, void* pBuffer, uint32_t nBufferSize, BOOL bFromCache)
{
	switch (nType)
	{
	case BNDOWNLOAD_REQUEST_VERSIONING:
	{
		BNET_DebugTrace("Processing Version file");
		strcpy(gszBnVersionFile, szFileName);
		return;
	}

	case BNDOWNLOAD_REQUEST_PATCH:
	{
		EnterCriticalSection(&gtBnDownloadLock);

		const char* szPatchFile = gszBnPatchFiles;
		while (*szPatchFile)
		{
			if (!_stricmp(szPatchFile, szFileName))
			{
				// Download the next patch file of the list
				if (*szPatchFile)
				{
					const char* szNextPatchFile = &szPatchFile[strlen(szPatchFile) + 1];
					if (*szNextPatchFile)
					{
						FILETIME tFileTime = {};
						BNDOWNLOAD_RequestFile(BNDOWNLOAD_REQUEST_PATCH, BNDOWNLOAD_FLAG_DISK, 0, 0, &tFileTime, szNextPatchFile, nullptr);
						LeaveCriticalSection(&gtBnDownloadLock);
						return;
					}
				}
				break;
			}

			szPatchFile += strlen(szPatchFile) + 1;
		}

		EnterCriticalSection(&gtBnDownloadLock);
		gszBnPatchFiles[0] = '\0';
		gszBnPatchFiles[1] = '\0';
		gnBnDownloadStatus = BNDOWNLOADSTATUS_PATCH_DONE;
		LeaveCriticalSection(&gtBnDownloadLock);

		LeaveCriticalSection(&gtBnDownloadLock);
		return;
	}

	case BNDOWNLOAD_REQUEST_AD:
	{
		BnReceivedAd tAd;
		char szMessage[4596];

		tAd.nAdId = nAdId;
		tAd.nAdFileExtension = nAdFileExtension;

		if (szFileName && strlen(szFileName))
		{
			tAd.szFileName = (char*)D2_ALLOC(strlen(szFileName) + 1);
			strcpy(tAd.szFileName, szFileName);
		}
		else
		{
			tAd.szFileName = nullptr;
		}

		if (szSaveName && strlen(szSaveName))
		{
			tAd.szLinkUrl = (char*)D2_ALLOC(strlen(szSaveName) + 1);
			strcpy(tAd.szLinkUrl, szSaveName);
		}
		else
		{
			tAd.szLinkUrl = nullptr;
		}

		if (nBufferSize && pBuffer)
		{
			tAd.pData = D2_ALLOC(nBufferSize);
			memcpy(tAd.pData, pBuffer, nBufferSize);
		}
		else
		{
			tAd.pData = nullptr;
		}
		tAd.nDataSize = nBufferSize;

		BNSEND_DisplayAd(szFileName, szSaveName);

		sprintf(szMessage, "<Received Ad: %s, %s>\n", tAd.szFileName, tAd.szLinkUrl);
		BNMESSQUEUE_PushString(1, szMessage);
		BNMESSQUEUE_PushData(3, &tAd, sizeof(tAd));
		return;
	}

	case BNDOWNLOAD_REQUEST_BNSERVER_INI:
	{
		BNET_DebugTrace("Processing Bnserver.ini file");

		const size_t nSize = SStrLen((const char*)pBuffer) + 1;
		char* szIniFile = (char*)SMemAlloc(nSize, __FILE__, __LINE__, 0);
		SStrCopy(szIniFile, (const char*)pBuffer, nSize);
		gtBnGatewayAccess.UpdateGatewaysFromIni(szIniFile);
		SMemFree(szIniFile, __FILE__, __LINE__, 0);
		gtBnGatewayAccess.SaveAndUnload();
		return;
	}

	case BNDOWNLOAD_REQUEST_EXTRAWORK:
	{
		if (bFromCache)
		{
			DeleteFileA(szFileName);
			return;
		}

		[[fallthrough]];
	}

	case BNDOWNLOAD_REQUEST_REQUIREDWORK:
	{
		char szDllFileName[MAX_PATH] = "";
		HSARCHIVE hArchive = nullptr;
		HSFILE hLocaleFile = nullptr;
		HMODULE hDll = nullptr;

		BNET_DebugTrace("Processing ExtraWork file");

		if (!SFileOpenArchive((char*)szFileName, 0, 0, &hArchive))
		{
			FOG_Trace("Failed to open ExtraWork dll %s!", szFileName);
			return;
		}

		uint32_t nAuthenticationResult;
		SFileAuthenticateArchive(hArchive, &nAuthenticationResult);
		if (nAuthenticationResult && nAuthenticationResult < 5)
		{
			BNET_DebugTrace("<ERROR: Failed ExtraWork archive authentication!>");
		}
		else if (!BNDOWNLOAD_ExtractDll(hArchive, szDllFileName, szFileName))
		{
			BNET_DebugTrace("<ERROR: Failed to extract ExtraWork DLL!>");
		}
		else
		{
			hDll = LoadLibraryA(szDllFileName);
			if (!hDll)
			{
				BNET_DebugTrace("<ERROR: Failed to load ExtraWork DLL!>");
			}
			else if (BnExtraWorkFunction pfExtraWork = (BnExtraWorkFunction)GetProcAddress(hDll, "ExtraWork"); !pfExtraWork)
			{
				BNET_DebugTrace("<ERROR: Failed to get address of ExtraWork function!>");
			}
			else if (!SFileOpenFile("data\\local\\use", &hLocaleFile))
			{
				BNET_DebugTrace("<ERROR: Failed to open game locale file!>");
			}
			else
			{
				uint8_t nLocale;
				uint32_t nBytesRead;
				if (!SFileReadFile(hLocaleFile, &nLocale, sizeof(nLocale), &nBytesRead, nullptr))
				{
					BNET_DebugTrace("<ERROR: Failed to read game locale file!>");
				}
				else if (nBytesRead != sizeof(nLocale))
				{
					BNET_DebugTrace("<ERROR: Failed to read game locale file!>");
				}
				else
				{
					SFileCloseFile(hLocaleFile);

					BnExtraWorkInfo tExtraWorkInfo;
					memset(&tExtraWorkInfo, 0x00, sizeof(tExtraWorkInfo));
					tExtraWorkInfo.nGameType = 1;
					tExtraWorkInfo.nLength = 4;
					tExtraWorkInfo.nLocale = nLocale;
					if (pfExtraWork(&tExtraWorkInfo))
					{
						BNET_SendPacket(SID_EXTRAWORK, &tExtraWorkInfo, tExtraWorkInfo.nLength + 4);
					}
					else
					{
						BNET_DebugTrace("<ERROR: ExtraWork DLL indicated failure!>");
					}
				}
			}

			if (hDll)
			{
				FreeLibrary(hDll);
			}
		}

		if (hArchive)
		{
			SFileCloseArchive(hArchive);
		}

		Sleep(50);
		DeleteFileA(szFileName);
		if (szDllFileName[0])
		{
			DeleteFileA(szDllFileName);
		}
		return;
	}

	default:
		return;
	}
}

//Bnclient.0x6FF03B00
BOOL __fastcall BNDOWNLOAD_ExtractDll(HANDLE hArchive, char* szDllFileName, const char* szArchiveFileName)
{
	HSFILE hFile = nullptr;
	BOOL bResult = FALSE;

	strcpy(szDllFileName, szArchiveFileName);
	if (strchr(szDllFileName, '.'))
	{
		*strchr(szDllFileName, '.') = '\0';
	}
	strcat(szDllFileName, ".dll");

	if (SFileOpenFileEx((HSARCHIVE)hArchive, szDllFileName, 0, &hFile))
	{
		const uint32_t nFileSize = SFileGetFileSize(hFile, nullptr);
		if (void* pBuffer = SMemAlloc(nFileSize, __FILE__, __LINE__, 0))
		{
			SFileReadFile(hFile, pBuffer, nFileSize, nullptr, nullptr);

			HANDLE hDllFile = FOG_CreateFileA(szDllFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (hDllFile != INVALID_HANDLE_VALUE)
			{
				DWORD nBytesWritten;
				FOG_WriteFile(hDllFile, pBuffer, nFileSize, &nBytesWritten, nullptr);
				FOG_CloseFile(hDllFile);
				bResult = TRUE;
			}

			SMemFree(pBuffer, __FILE__, __LINE__, 0);
		}
	}

	if (hFile)
	{
		SFileCloseFile(hFile);
	}

	return bResult;
}

//Bnclient.0x6FF03C10
void __stdcall BNDOWNLOAD_CancelAll()
{
	gbBnDownloadCancel = TRUE;
}

//Bnclient.0x6FF03C20
BOOL __stdcall BNDOWNLOAD_IsActive()
{
	return gnBnActiveDownloads > 0;
}

//Bnclient.0x6FF03C30
unsigned __stdcall BNDOWNLOAD_DownloadThread(void* pParam)
{
	BnFtpRequest* pRequest = (BnFtpRequest*)pParam;
	BnFtpHeader* pHeader = nullptr;
	uint8_t* pFileData = nullptr;
	char* szServer = nullptr;
	int nRetries = 0;
	char szServerList[512];
	char szGatewayHost[256];
	BnFtpRequest tRequest;
	uint8_t aReceiveBuffer[1460];

	szServerList[0] = '\0';
	gbBnDownloadCancel = FALSE;

	sockaddr_in tAddress;
	int nAddressLength = sizeof(tAddress);
	if (!BNET_GetPeerName((sockaddr*)&tAddress, &nAddressLength))
	{
		BNET_GetGatewayHost(szGatewayHost, sizeof(szGatewayHost));
		BNET_GetServersList(szServerList, szGatewayHost);
		szServer = strtok(szServerList, " ,;");

		memset(&tAddress, 0x00, sizeof(tAddress));
		tAddress.sin_family = AF_INET;
		tAddress.sin_port = htons(6112);
		tAddress.sin_addr.s_addr = inet_addr(szServer);
	}
	else
	{
		tAddress.sin_port = htons(6112);
		memset(tAddress.sin_zero, 0x00, sizeof(tAddress.sin_zero));
	}

	SOCKET hSocket;

retry:
	hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		goto cleanup;
	}

	if (connect(hSocket, (sockaddr*)&tAddress, sizeof(tAddress)) != 0)
	{
		if (gbBnDownloadCancel || pRequest->nType != BNDOWNLOAD_REQUEST_PATCH)
		{
			BNET_DebugTrace("Canceled download.");
			goto cleanup;
		}

		FOG_SOCKET_CloseSocket(hSocket);
		hSocket = INVALID_SOCKET;

		if (++nRetries > 3)
		{
			BNET_DebugTrace("ERROR: Failed recv from BNET for download.");
			goto cleanup;
		}

		BNET_DebugTrace("WARNING: Failed to connect to download port. Retrying...");
		Sleep(1000);

		if (szServerList[0])
		{
			szServer = strtok(szServer ? nullptr : szServerList, " ,;");
		}

		if (!szServer)
		{
			goto cleanup;
		}

		tAddress.sin_addr.s_addr = inet_addr(szServer);
		goto retry;
	}

	{
		BOOL bKeepAlive = TRUE;
		setsockopt(hSocket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&bKeepAlive, sizeof(bKeepAlive));
		int nReceiveTimeout = 15000;
		setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&nReceiveTimeout, sizeof(nReceiveTimeout));
	}

	{
		char nProtocolId = 2;
		if (send(hSocket, &nProtocolId, sizeof(nProtocolId), 0) != 1)
		{
			BNET_DebugTrace("ERROR: Failed send to BNET for download.");
			goto cleanup;
		}
	}

	memcpy(&tRequest, pRequest, sizeof(tRequest));
	if (send(hSocket, (const char*)&tRequest, pRequest->nRequestLength, 0) != pRequest->nRequestLength)
	{
		BNET_DebugTrace("ERROR: Failed send to BNET for download.");
		goto cleanup;
	}

	{
		uint32_t headersize = 0;
		for (uint32_t nReceived = 0; nReceived < sizeof(headersize); )
		{
			const int nResult = recv(hSocket, (char*)&headersize + nReceived, sizeof(headersize) - nReceived, 0);
			if (nResult == SOCKET_ERROR || nResult <= 0)
			{
				BNET_DebugTrace("ERROR: Failed send to BNET for download.");
				goto cleanup;
			}
			nReceived += nResult;
		}

		D2_ASSERT(headersize < 256);

		pHeader = (BnFtpHeader*)SMemAlloc(headersize, __FILE__, __LINE__, 0);
		if (!pHeader)
		{
			goto cleanup;
		}

		const uint32_t nRemainingHeaderSize = headersize - sizeof(headersize);
		for (uint32_t nReceived = 0; nReceived < nRemainingHeaderSize; )
		{
			const int nResult = recv(hSocket, (char*)pHeader + sizeof(headersize) + nReceived, nRemainingHeaderSize - nReceived, 0);
			if (nResult == SOCKET_ERROR || nResult <= 0)
			{
				BNET_DebugTrace("ERROR: Failed recv from BNET for download.");
				goto cleanup;
			}
			nReceived += nResult;
		}
	}

	if (gbBnDownloadCancel)
	{
		BNET_DebugTrace("Canceled download(2).");
		goto cleanup;
	}

	if (pRequest->nFlags == BNDOWNLOAD_FLAG_DISK)
	{
		// Resume the download of a partially downloaded file
		uint32_t nExistingFileSize = 0;
		HANDLE hExistingFile = FOG_CreateFileA(pHeader->szFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
		if (hExistingFile != INVALID_HANDLE_VALUE)
		{
			FILETIME tLastWriteTime;
			GetFileTime(hExistingFile, nullptr, nullptr, &tLastWriteTime);

			const int64_t nTimeDifference = (int64_t)(((uint64_t)tLastWriteTime.dwHighDateTime << 32) | tLastWriteTime.dwLowDateTime)
				- (int64_t)(((uint64_t)pHeader->tFileTime.dwHighDateTime << 32) | pHeader->tFileTime.dwLowDateTime);
			if ((nTimeDifference < 0 ? -nTimeDifference : nTimeDifference) <= 40000000)
			{
				nExistingFileSize = GetFileSize(hExistingFile, nullptr);
			}

			FOG_CloseFile(hExistingFile);
		}

		if (nExistingFileSize != pRequest->nStartPosition)
		{
			pRequest->nStartPosition = nExistingFileSize;
			FOG_SOCKET_CloseSocket(hSocket);
			SMemFree(pHeader, __FILE__, __LINE__, 0);
			pHeader = nullptr;
			goto retry;
		}

		if (gbBnDownloadCancel)
		{
			BNET_DebugTrace("Canceled download(3).");
			goto cleanup;
		}
	}

	if (const uint32_t nFlags = pRequest->nFlags; nFlags == BNDOWNLOAD_FLAG_DISK)
	{
		const uint32_t nFileSize = pHeader->nFileSize;
		const uint32_t nType = pRequest->nType;
		uint32_t nPosition = pRequest->nStartPosition;

		HANDLE hFile = FOG_CreateFileA(pHeader->szFileName, GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			if (nPosition)
			{
				FOG_SetFilePointer(hFile, nPosition, nullptr, FILE_BEGIN);
			}

			if (nType == BNDOWNLOAD_REQUEST_PATCH)
			{
				gnBnDownloadStatus = 100 * nPosition / nFileSize;
				Sleep(0);
			}

			BOOL bFailed = FALSE;
			while (nPosition < nFileSize)
			{
				uint32_t nBytesToReceive = nFileSize - nPosition;
				if (nBytesToReceive > sizeof(aReceiveBuffer))
				{
					nBytesToReceive = sizeof(aReceiveBuffer);
				}

				const int nReceived = recv(hSocket, (char*)aReceiveBuffer, nBytesToReceive, 0);
				if (nReceived == SOCKET_ERROR || nReceived <= 0 || gbBnDownloadCancel)
				{
					bFailed = TRUE;
					break;
				}

				DWORD nBytesWritten;
				FOG_WriteFile(hFile, aReceiveBuffer, nReceived, &nBytesWritten, nullptr);
				SetFileTime(hFile, &pHeader->tFileTime, &pHeader->tFileTime, &pHeader->tFileTime);
				nPosition += nReceived;

				if (nType == BNDOWNLOAD_REQUEST_PATCH)
				{
					gnBnDownloadStatus = 100 * nPosition / nFileSize;
				}
			}

			FOG_CloseFile(hFile);

			if (!bFailed)
			{
				goto process;
			}
		}

		if (gbBnDownloadCancel)
		{
			BNET_DebugTrace("ERROR: Cancelled download.");
			goto cleanup;
		}

		FOG_SOCKET_CloseSocket(hSocket);
		SMemFree(pHeader, __FILE__, __LINE__, 0);
		pHeader = nullptr;
		BNET_DebugTrace("WARNING: Failed to save to disk.");
		goto retry;
	}
	else
	{
		const uint32_t nFileSize = pHeader->nFileSize;
		const uint32_t nType = pRequest->nType;

		pFileData = (uint8_t*)SMemAlloc(nFileSize, __FILE__, __LINE__, 8);

		uint32_t nPosition = 0;
		int nReceived = 0;
		while (nPosition < nFileSize)
		{
			uint32_t nBytesToReceive = nFileSize - nPosition;
			if (nBytesToReceive > sizeof(aReceiveBuffer))
			{
				nBytesToReceive = sizeof(aReceiveBuffer);
			}

			nReceived = recv(hSocket, (char*)&pFileData[nPosition], nBytesToReceive, 0);
			if (nReceived == SOCKET_ERROR || nReceived <= 0 || gbBnDownloadCancel)
			{
				SMemFree(pFileData, __FILE__, __LINE__, 0);
				BNET_DebugTrace("<ERROR: Failed to recv file  %s in DOWNLOADTOANY, filebytes = %d, currpos = %d, bytes = %d", pHeader->szFileName, nFileSize, nPosition, nReceived);
				pFileData = nullptr;

				if (gbBnDownloadCancel)
				{
					BNET_DebugTrace("ERROR: Cancelled download(2).");
					goto cleanup;
				}

				FOG_SOCKET_CloseSocket(hSocket);
				SMemFree(pHeader, __FILE__, __LINE__, 0);
				BNET_DebugTrace("ERROR: Failed to copy file.");
				pHeader = nullptr;
				goto retry;
			}

			nPosition += nReceived;
			if (nType == BNDOWNLOAD_REQUEST_PATCH)
			{
				gnBnDownloadStatus = 100 * nPosition / nFileSize;
			}
		}

		if (nFlags & BNDOWNLOAD_FLAG_CACHE)
		{
			BNCACHE_StoreFile(pHeader->szFileName, pFileData, nFileSize, &pHeader->tFileTime, 15 * 24 * 60 * 60, 30 * 24 * 60 * 60);
		}

		if (nFlags & BNDOWNLOAD_FLAG_DISK)
		{
			HANDLE hFile = FOG_CreateFileA(pHeader->szFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				DWORD nBytesWritten;
				FOG_WriteFile(hFile, pFileData, nFileSize, &nBytesWritten, nullptr);
				SetFileTime(hFile, &pHeader->tFileTime, &pHeader->tFileTime, &pHeader->tFileTime);
				FOG_CloseFile(hFile);
			}
		}
	}

process:
	BNDOWNLOAD_ProcessFile(pRequest->nType, pRequest->nFlags, pHeader->nAdId, pHeader->nAdFileExtension, &pHeader->tFileTime, pHeader->szFileName, pRequest->szSaveName, pFileData, pHeader->nFileSize, FALSE);

cleanup:
	const uint32_t nType = pRequest->nType;

	if (hSocket != INVALID_SOCKET)
	{
		FOG_SOCKET_CloseSocket(hSocket);
	}

	if (pFileData)
	{
		SMemFree(pFileData, __FILE__, __LINE__, 0);
	}

	if (pHeader)
	{
		SMemFree(pHeader, __FILE__, __LINE__, 0);
	}

	SMemFree(pRequest, __FILE__, __LINE__, 0);

	if (nType == BNDOWNLOAD_REQUEST_PATCH && (uint32_t)gnBnDownloadStatus < 100)
	{
		EnterCriticalSection(&gtBnDownloadLock);
		gszBnPatchFiles[0] = '\0';
		gszBnPatchFiles[1] = '\0';
		gnBnDownloadStatus = BNDOWNLOADSTATUS_PATCH_DONE;
		LeaveCriticalSection(&gtBnDownloadLock);
	}

	InterlockedDecrement(&gnBnActiveDownloads);
	_endthreadex(0);
	return 0;
}

//Bnclient.0x6FF04480
BOOL __fastcall BNDOWNLOAD_CheckRevision(uint32_t* pVersion, uint32_t* pChecksum, char* szExeInfo)
{
	BOOL bResult = FALSE;

	if (pVersion)
	{
		*pVersion = 0;
	}

	if (pChecksum)
	{
		*pChecksum = 0;
	}

	if (szExeInfo)
	{
		*szExeInfo = '\0';
	}

	BNET_DebugTrace("<Running CHECK VERSION>");

	char szDllFileName[MAX_PATH] = "";
	HSARCHIVE hArchive = nullptr;

	const DWORD dwStartTick = GetTickCount();
	while (!gszBnVersionFile[0])
	{
		Sleep(10);
		if (GetTickCount() - dwStartTick > 20000)
		{
			return TRUE;
		}
	}

	if (!SFileOpenArchive(gszBnVersionFile, 0, 0, &hArchive))
	{
		FOG_Trace("Failed to open version dll %s!", gszBnVersionFile);
		return FALSE;
	}

	uint32_t nAuthenticationResult;
	SFileAuthenticateArchive(hArchive, &nAuthenticationResult);
	if (nAuthenticationResult && nAuthenticationResult < 5)
	{
		BNET_DebugTrace("<ERROR: Failed Versioning archive authentication!>");
	}
	else if (!BNDOWNLOAD_ExtractDll(hArchive, szDllFileName, gszBnVersionFile))
	{
		BNET_DebugTrace("<ERROR: Failed to extract Versioning DLL!>");
	}
	else if (HMODULE hDll = LoadLibraryA(szDllFileName))
	{
		if (BnCheckRevisionFunction pfCheckRevision = (BnCheckRevisionFunction)GetProcAddress(hDll, "CheckRevision"))
		{
			char szGameFileName[MAX_PATH] = "";
			char szBnclientFileName[MAX_PATH] = "";
			char szD2ClientFileName[MAX_PATH] = "";

			GetModuleFileNameA(GetModuleHandleA(nullptr), szGameFileName, sizeof(szGameFileName));

			SStrCopy(szBnclientFileName, szGameFileName, INT_MAX);
			SStrCopy(strrchr(szBnclientFileName, '\\') + 1, "bnclient.dll", INT_MAX);

			SStrCopy(szD2ClientFileName, szGameFileName, INT_MAX);
			SStrCopy(strrchr(szD2ClientFileName, '\\') + 1, "d2client.dll", INT_MAX);

			bResult = pfCheckRevision(szGameFileName, szBnclientFileName, szD2ClientFileName, gszBnVersionFormula, pVersion, pChecksum, szExeInfo);
		}
		else
		{
			BNET_DebugTrace("<ERROR: Failed to execute Versioning DLL!>");
		}

		FreeLibrary(hDll);
	}

	if (hArchive)
	{
		SFileCloseArchive(hArchive);
	}

	Sleep(50);
	DeleteFileA(gszBnVersionFile);
	if (szDllFileName[0])
	{
		DeleteFileA(szDllFileName);
	}

	if (!bResult)
	{
		FOG_Trace("checkrevision failed!");
	}

	return bResult;
}

//Bnclient.0x6FF04750
BOOL __fastcall BNDOWNLOAD_RunUpgrade(BOOL* pbQuit)
{
	int32_t nUpgradeStatus;
	BNDOWNLOAD_ApplyPatch(&nUpgradeStatus);

	switch (nUpgradeStatus)
	{
	case BNUPGRADESTATUS_NONE:
	case 1:
		return TRUE;

	case BNUPGRADESTATUS_LAUNCHED:
		*pbQuit = TRUE;
		return FALSE;

	default:
		return FALSE;
	}
}

//Bnclient.0x6FF04780
BOOL __fastcall BNDOWNLOAD_ApplyPatch(int32_t* upgradestatus)
{
	D2_ASSERT(upgradestatus);

	char szDirectory[MAX_PATH] = "";
	GetModuleFileNameA(nullptr, szDirectory, sizeof(szDirectory));
	szDirectory[sizeof(szDirectory) - 1] = '\0';

	char* pLastSeparator = szDirectory;
	if (*pLastSeparator)
	{
		while (SStrChr(pLastSeparator + 1, '\\'))
		{
			pLastSeparator = (char*)SStrChr(pLastSeparator + 1, '\\');
			if (!*pLastSeparator)
			{
				break;
			}
		}
	}
	*pLastSeparator = '\0';

	char szPatchFiles[1024];
	memset(szPatchFiles, 0x00, sizeof(szPatchFiles));
	if (!SRegLoadData("Patch", "Patches", 2, szPatchFiles, sizeof(szPatchFiles) - 2, nullptr) || !szPatchFiles[0])
	{
		*upgradestatus = BNUPGRADESTATUS_NONE;
		return FALSE;
	}

	char szCommandLines[1024] = "";
	char* pCommandLine = szCommandLines;
	char* szPatchFile = szPatchFiles;
	do
	{
		HSARCHIVE hArchive;
		if (!SFileOpenArchive(szPatchFile, 0, 0, &hArchive))
		{
			DeleteFileA(szPatchFile);
			*upgradestatus = BNUPGRADESTATUS_FAILED;
			return FALSE;
		}

		uint32_t nAuthenticationResult;
		SFileAuthenticateArchive(hArchive, &nAuthenticationResult);
		if (nAuthenticationResult && nAuthenticationResult < 5)
		{
			SFileCloseArchive(hArchive);
			DeleteFileA(szPatchFile);
			*upgradestatus = BNUPGRADESTATUS_FAILED;
			return FALSE;
		}

		HSFILE hPrepatchFile;
		if (SFileOpenFileEx(hArchive, "Prepatch.lst", 0, &hPrepatchFile))
		{
			const uint32_t nPrepatchSize = SFileGetFileSize(hPrepatchFile, nullptr);
			char* pPrepatch = (char*)SMemAlloc(nPrepatchSize, __FILE__, __LINE__, 0);
			if (SFileReadFile(hPrepatchFile, pPrepatch, nPrepatchSize, nullptr, nullptr) && nPrepatchSize)
			{
				const char* pCursor = pPrepatch;
				do
				{
					char szLine[256] = "";

					char* pLineEnd = szLine;
					if ((uint32_t)(pCursor - pPrepatch) < nPrepatchSize)
					{
						for (int i = 0; i < 255; ++i)
						{
							const char c = *pCursor;
							if (!c || c == '\r' || c == '\n')
							{
								break;
							}

							*pLineEnd++ = c;
							++pCursor;
							*pLineEnd = '\0';

							if ((uint32_t)(pCursor - pPrepatch) >= nPrepatchSize)
							{
								break;
							}
						}
					}

					while ((uint32_t)(pCursor - pPrepatch) < nPrepatchSize && (*pCursor == '\r' || *pCursor == '\n'))
					{
						++pCursor;
					}

					char szArgument[MAX_PATH] = "";
					char szTargetPath[MAX_PATH] = "";
					if (SStrChr(szLine, ' '))
					{
						const char* pArgument = SStrChr(szLine, ' ') + 1;
						while (*pArgument == ' ')
						{
							++pArgument;
						}

						SStrCopy(szArgument, pArgument, sizeof(szArgument));
						wsprintfA(szTargetPath, "%s\\%s", szDirectory, pArgument);
					}

					if (!_strnicmp(szLine, "delete ", 7))
					{
						DeleteFileA(szTargetPath);
					}
					else if (!_strnicmp(szLine, "extract ", 8))
					{
						HSFILE hExtractedFile;
						if (SFileOpenFileEx(hArchive, szArgument, 0, &hExtractedFile))
						{
							const uint32_t nFileSize = SFileGetFileSize(hExtractedFile, nullptr);
							void* pBuffer = SMemAlloc(nFileSize, __FILE__, __LINE__, 0);
							if (SFileReadFile(hExtractedFile, pBuffer, nFileSize, nullptr, nullptr))
							{
								HANDLE hFile = FOG_CreateFileA(szTargetPath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
								if (hFile != INVALID_HANDLE_VALUE)
								{
									DWORD nBytesWritten;
									FOG_WriteFile(hFile, pBuffer, nFileSize, &nBytesWritten, nullptr);
									FOG_CloseFile(hFile);
								}
							}

							SMemFree(pBuffer, __FILE__, __LINE__, 0);
							SFileCloseFile(hExtractedFile);
						}
					}
					else if (!_strnicmp(szLine, "execute ", 8))
					{
						pCommandLine += SStrCopy(pCommandLine, szTargetPath, INT_MAX) + 1;
					}
				}
				while ((uint32_t)(pCursor - pPrepatch) < nPrepatchSize);
			}

			SMemFree(pPrepatch, __FILE__, __LINE__, 0);
			SFileCloseFile(hPrepatchFile);
		}

		SFileCloseArchive(hArchive);
		szPatchFile += SStrLen(szPatchFile) + 1;
	}
	while (*szPatchFile);

	char szValue[900];
	sprintf(szValue, "%s\\Game.exe", szDirectory);
	SRegSaveString("Patch", "Launcher", 2, szValue);

	sprintf(szValue, "%s\\%s;%s\\%s;%s\\%s", szDirectory, "d2exp.mpq", szDirectory, "d2data.mpq", szDirectory, "d2sfx.mpq");
	SRegSaveString("Patch", "SrcData", 2, szValue);

	sprintf(szValue, "%s\\%s", szDirectory, "patch_d2.mpq");
	SRegSaveString("Patch", "DstData", 2, szValue);

	if (pCommandLine == szCommandLines)
	{
		wsprintfA(pCommandLine, "%s\\bnupdate.exe", szDirectory);
		pCommandLine += SStrLen(pCommandLine) + 1;
	}
	*pCommandLine = '\0';

	gtBnGatewayAccess.SaveAndUnload();

	for (char* szCommandLine = szCommandLines; *szCommandLine; szCommandLine += SStrLen(szCommandLine) + 1)
	{
		STARTUPINFOA tStartupInfo;
		SMemZero(&tStartupInfo, sizeof(tStartupInfo));
		tStartupInfo.cb = sizeof(tStartupInfo);

		PROCESS_INFORMATION tProcessInformation;
		if (!CreateProcessA(nullptr, szCommandLine, nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS, nullptr, szDirectory, &tStartupInfo, &tProcessInformation))
		{
			*upgradestatus = BNUPGRADESTATUS_FAILED;
			return FALSE;
		}

		CloseHandle(tProcessInformation.hThread);
		CloseHandle(tProcessInformation.hProcess);
	}

	*upgradestatus = BNUPGRADESTATUS_LAUNCHED;
	return TRUE;
}

//Bnclient.0x6FF04DD0
void __fastcall BNDOWNLOAD_SetStatus(int32_t nStatus)
{
	EnterCriticalSection(&gtBnDownloadLock);
	gnBnDownloadStatus = nStatus;
	gszBnPatchFiles[0] = '\0';
	gszBnPatchFiles[1] = '\0';
	LeaveCriticalSection(&gtBnDownloadLock);
}

//Bnclient.0x6FF04E00
int32_t __stdcall BNDOWNLOAD_GetStatus()
{
	return gnBnDownloadStatus;
}

//Bnclient.0x6FF04E10
BOOL __fastcall BNDOWNLOAD_StartPatch(const char* szPatchFiles, uint32_t nSize)
{
	if (!FOG_SOCKET_WSAStartup())
	{
		return FALSE;
	}

	gnBnDownloadStatus = 0;
	BNDOWNLOAD_SetPatchFiles(szPatchFiles, nSize);
	SRegSaveData("Patch", "Patches", 0x82, szPatchFiles, nSize + 1);

	FILETIME tFileTime = {};
	if (szPatchFiles && *szPatchFiles)
	{
		BNDOWNLOAD_RequestFile(BNDOWNLOAD_REQUEST_PATCH, BNDOWNLOAD_FLAG_DISK, 0, 0, &tFileTime, szPatchFiles, nullptr);
	}

	return FALSE;
}

//Bnclient.0x6FF05020
BOOL __fastcall BNDOWNLOAD_SetVersionFile(const char* szFileName)
{
	SStrCopy(gszBnVersionFile, szFileName, INT_MAX);
	return TRUE;
}

//Bnclient.0x6FF05040
BOOL __stdcall BNDOWNLOAD_HasVersionFile()
{
	return gszBnVersionFile[0] != '\0';
}
