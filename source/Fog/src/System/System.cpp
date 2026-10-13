#include <Fog.h>
#include <System/System.h>
#include <Storm.h>
#include <Windows.h>
#include <time.h>

#define FOG_REGISTRY_KEY "Diablo II"
#define FOG_REGISTRY_INSTALL_PATH "InstallPath"
#define FOG_REGISTRY_SAVE_PATH "Save Path"

// Fog.0x6FFA12EC
static BOOL gbUseDirectAccess;

// Fog.0x6FF9FE10
static BOOL gbExpansionChecked;
// Fog.0x6FF9FE14
static BOOL gbIsExpansion;

// Fog.0x6FF9EDD8
// Pair of {time(), GetTickCount()} sampled at the same moment, read and written atomically.
union FOGSyncTime
{
	struct
	{
		int32_t nTime;
		DWORD dwTickCount;
	};
	LONGLONG nAtomicValue;
};
static FOGSyncTime gtSyncTime;

// 1.10f: 0x6FF5A860 (#10176)
BOOL __stdcall FOG_IsWindowsNT()
{
	OSVERSIONINFOA VersionInformation{};
	VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	return GetVersionExA(&VersionInformation) && VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT;
}

// 1.10f: 0x6FF5A740
static FOGSyncTime SYSTEM_ReadSyncTime()
{
	FOGSyncTime tResult;
	// Atomic 64 bits read
	tResult.nAtomicValue = InterlockedCompareExchange64(&gtSyncTime.nAtomicValue, 0, 0);
	return tResult;
}

// 1.10f: 0x6FF5A720
static void SYSTEM_WriteSyncTime(const FOGSyncTime& tSyncTime)
{
	InterlockedExchange64(&gtSyncTime.nAtomicValue, tSyncTime.nAtomicValue);
}

// 1.10f: Inlined in 0x6FF5A5C0 (called by FOG_InitErrorMgr)
void SYSTEM_InitializeSyncTime()
{
	FOGSyncTime tSyncTime;
	tSyncTime.nTime = (int32_t)time(nullptr);
	tSyncTime.dwTickCount = GetTickCount();
	SYSTEM_WriteSyncTime(tSyncTime);
}

// 1.10f: 0x6FF5A690 (#10055)
// Returns the current time in seconds (as time()), but extrapolated using GetTickCount and synchronized every 30 seconds.
int32_t __fastcall FOG_10055_GetSyncTime()
{
	const DWORD dwTickCount = GetTickCount();
	const FOGSyncTime tSyncTime = SYSTEM_ReadSyncTime();
	if (dwTickCount - tSyncTime.dwTickCount > 30000)
	{
		const HANDLE hCurrentThread = GetCurrentThread();
		const int nThreadPriority = GetThreadPriority(hCurrentThread);
		if (nThreadPriority != THREAD_PRIORITY_ERROR_RETURN)
		{
			SetThreadPriority(GetCurrentThread(), nThreadPriority);
		}
		SYSTEM_InitializeSyncTime();
	}
	// Note: uses the previous synchronization point even if it was just updated
	return tSyncTime.nTime + (dwTickCount - tSyncTime.dwTickCount) / 1000;
}

// 1.10f: 0x6FF5A760 (#10056)
// Returns the number of bytes available on the disk containing the save directory.
uint64_t __stdcall FOG_GetSaveDiskFreeSpace()
{
	char szPath[1024];
	FOG_GetSavePath(szPath, sizeof(szPath));

	if (HMODULE hKernel32 = LoadLibraryA("kernel32.dll"))
	{
		using GetDiskFreeSpaceExAFunc = BOOL(WINAPI*)(LPCSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);
		if (GetDiskFreeSpaceExAFunc pGetDiskFreeSpaceExA = (GetDiskFreeSpaceExAFunc)GetProcAddress(hKernel32, "GetDiskFreeSpaceExA"))
		{
			ULARGE_INTEGER nFreeBytesAvailable{};
			ULARGE_INTEGER nTotalNumberOfBytes{};
			ULARGE_INTEGER nTotalNumberOfFreeBytes{};
			pGetDiskFreeSpaceExA(szPath, &nFreeBytesAvailable, &nTotalNumberOfBytes, &nTotalNumberOfFreeBytes);
			FreeLibrary(hKernel32);
			return nFreeBytesAvailable.QuadPart;
		}
	}

	// Only keep the root directory, GetDiskFreeSpaceA does not support other directories on old systems
	for (int i = 0; i < 1024; ++i)
	{
		if (szPath[i] == '\\')
		{
			szPath[i + 1] = '\0';
			break;
		}
	}

	DWORD dwSectorsPerCluster = 0;
	DWORD dwBytesPerSector = 0;
	DWORD dwNumberOfFreeClusters = 0;
	DWORD dwTotalNumberOfClusters = 0;
	GetDiskFreeSpaceA(szPath, &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters);
	return (uint32_t)(dwNumberOfFreeClusters * dwSectorsPerCluster * dwBytesPerSector);
}

// 1.10f: 0x6FF5A840 (#10057)
void __cdecl FOG_GetGlobalMemoryStatus(MEMORYSTATUS* pMemoryStatus)
{
	memset(pMemoryStatus, 0, sizeof(*pMemoryStatus));
	pMemoryStatus->dwLength = sizeof(*pMemoryStatus);
	GlobalMemoryStatus(pMemoryStatus);
}

// 1.10f: 0x6FF5A5B0 (#10059)
DWORD __stdcall FOG_GetTickCount()
{
	return GetTickCount();
}

// 1.10f: 0x6FF5D730 (#10227)
BOOL __fastcall FOG_IsExpansion()
{
	if (!gbExpansionChecked)
	{
		gbExpansionChecked = TRUE;

		char szPath[MAX_PATH];
		FOG_GetInstallPath(szPath, MAX_PATH);
		SStrNCat(szPath, "d2exp.mpq", MAX_PATH);
		if (GetFileAttributesA(szPath) != INVALID_FILE_ATTRIBUTES)
		{
			gbIsExpansion = TRUE;
			return TRUE;
		}

		SStrCopy(szPath, "d2exp.mpq", MAX_PATH);
		if (GetFileAttributesA(szPath) != INVALID_FILE_ATTRIBUTES)
		{
			gbIsExpansion = TRUE;
			return TRUE;
		}
	}

	return gbIsExpansion;
}

// 1.10f: 0x6FF61590 (#10101)
BOOL __fastcall FOG_MPQSetConfig(int dwDirectAccessFlags, int bEnableSeekOptimization)
{
	SFileSetBasePath(".\\");
	SFileEnableDirectAccess(dwDirectAccessFlags);
	SFileSetIoErrorMode(0, nullptr);
	SFileEnableSeekOptimization(bEnableSeekOptimization);
	gbUseDirectAccess = dwDirectAccessFlags;

	int nOptionValue = 0x8000;
	StormSetOption(2, &nOptionValue, sizeof(nOptionValue));
	nOptionValue = 1;
	StormSetOption(1, &nOptionValue, sizeof(nOptionValue));
	return StormSetOption(3, &nOptionValue, sizeof(nOptionValue));
}

// 1.10f: 0x6FF61600 (#10102)
BOOL __fastcall FOG_FOpenFile(const char* szFile, HSFILE* pFileHandle)
{
	return SFileOpenFile(szFile, pFileHandle);
}

// 1.10f: 0x6FF61610 (#10103)
void __fastcall FOG_FCloseFile(HSFILE pFile)
{
	SFileCloseFile(pFile);
}

// 1.10f: 0x6FF61620 (#10104)
BOOL __fastcall FOG_FReadFile(HSFILE pFile, void* pBuffer, size_t nSize, int* nBytesRead, uint32_t a5, uint32_t a6, uint32_t a7)
{
	// Note: the order of the last 2 arguments is swapped on purpose
	return SFileFileExistsEx(pFile, pBuffer, nSize, (DWORD*)nBytesRead, (LPOVERLAPPED)a5, a7, a6);
}

// 1.10f: 0x6FF61650 (#10105)
uint32_t __fastcall FOG_FGetFileSize(HSFILE pFileHandle, uint32_t* lpFileSizeHigh)
{
	return SFileGetFileSize(pFileHandle, (LPDWORD)lpFileSizeHigh);
}

// 1.10f: 0x6FF61660 (#10106)
size_t __fastcall FOG_FSetFilePointer(HSFILE hFile, int32_t lDistanceToMove, int32_t* lpDistanceToMoveHigh, uint32_t dwMoveMethod)
{
	return SFileSetFilePointer(hFile, lDistanceToMove, (LONG*)lpDistanceToMoveHigh, dwMoveMethod);
}

// 1.10f: 0x6FF61680 (#10107)
HANDLE __fastcall FOG_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

// 1.10f: 0x6FF616B0 (#10108)
BOOL __fastcall FOG_DeleteFileA(LPCSTR lpFileName)
{
	return DeleteFileA(lpFileName);
}

// 1.10f: 0x6FF616C0 (#10109)
BOOL __fastcall FOG_CloseFile(HANDLE hFILE)
{
	return CloseHandle(hFILE);
}

// 1.10f: 0x6FF616D0 (#10110)
BOOL __fastcall FOG_ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
	return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

// 1.10f: 0x6FF616F0 (#10111)
BOOL __fastcall FOG_WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	return WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

// 1.10f: 0x6FF61710 (#10112)
DWORD __fastcall FOG_SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
{
	return SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
}

// 1.10f: 0x6FF61800 (#10113)
// Appends a trailing backslash to the path if it does not end with one already and the buffer is big enough.
void __fastcall FOG_AppendBackslash(char* szPath, size_t nBufferSize)
{
	if (!szPath || !nBufferSize)
	{
		return;
	}

	const size_t nLength = SStrLen(szPath);
	if (nLength > 0 && szPath[nLength - 1] == '\\')
	{
		return;
	}

	if (nLength + 1 < nBufferSize)
	{
		szPath[nLength] = '\\';
		szPath[nLength + 1] = '\0';
	}
}

// 1.10f: 0x6FF61730 (#10114)
// Creates all the directories of the path, the last element is only created if the path ends with a backslash.
BOOL __fastcall FOG_CreatePathHierarchy(char* szPath)
{
	if (!szPath || !szPath[0])
	{
		return FALSE;
	}

	// Skip the first character so that a leading backslash is not considered
	for (const char* pSeparator = SStrChr(szPath + 1, '\\'); pSeparator; pSeparator = SStrChr(pSeparator + 1, '\\'))
	{
		const size_t nLength = pSeparator - szPath;
		if (nLength >= MAX_PATH)
		{
			return FALSE;
		}

		char szDirectory[MAX_PATH];
		memcpy(szDirectory, szPath, nLength);
		szDirectory[nLength] = '\0';
		if (!CreateDirectoryA(szDirectory, nullptr))
		{
			const DWORD dwError = GetLastError();
			if (dwError != ERROR_ALREADY_EXISTS && dwError != ERROR_ACCESS_DENIED)
			{
				return FALSE;
			}

			if (!(GetFileAttributesA(szDirectory) & FILE_ATTRIBUTE_DIRECTORY))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

// Helper, inlined
// Copies the directory of the current module, including the trailing backslash.
static void SYSTEM_GetModuleDirectory(char* pPathBuffer, size_t nBufferSize)
{
	GetModuleFileNameA(nullptr, pPathBuffer, nBufferSize);
	pPathBuffer[nBufferSize - 1] = '\0';
	if (char* pLastSeparator = (char*)SStrChrR(pPathBuffer, '\\'))
	{
		pLastSeparator[1] = '\0';
	}
}

// Helper, inlined
// Fetches the install path from the registry, or uses the executable directory if invalid and saves it to the registry.
static void SYSTEM_GetInstallPath(char* pPathBuffer, size_t nBufferSize)
{
	if (!SRegLoadString(FOG_REGISTRY_KEY, FOG_REGISTRY_INSTALL_PATH, 0, pPathBuffer, nBufferSize))
	{
		pPathBuffer[0] = '\0';
	}

	if (GetFileAttributesA(pPathBuffer) == INVALID_FILE_ATTRIBUTES)
	{
		pPathBuffer[0] = '\0';
	}

	if (!pPathBuffer[0])
	{
		SYSTEM_GetModuleDirectory(pPathBuffer, nBufferSize);
		SRegSaveString(FOG_REGISTRY_KEY, FOG_REGISTRY_INSTALL_PATH, 0, pPathBuffer);
	}

	FOG_AppendBackslash(pPathBuffer, nBufferSize);
}

// 1.10f: 0x6FF61900 (#10115)
// Fetches the save path from the registry, or uses "<InstallPath>Save\" if invalid and saves it to the registry.
// Creates the directory hierarchy and returns whether it succeeded.
size_t __fastcall FOG_GetSavePath(char* pPathBuffer, size_t nBufferSize)
{
	if (!SRegLoadString(FOG_REGISTRY_KEY, FOG_REGISTRY_SAVE_PATH, 0, pPathBuffer, nBufferSize))
	{
		pPathBuffer[0] = '\0';
	}

	if (GetFileAttributesA(pPathBuffer) == INVALID_FILE_ATTRIBUTES)
	{
		pPathBuffer[0] = '\0';
	}

	if (!pPathBuffer[0])
	{
		SYSTEM_GetInstallPath(pPathBuffer, nBufferSize);
		SStrNCat(pPathBuffer, "Save\\", nBufferSize);
		SRegSaveString(FOG_REGISTRY_KEY, FOG_REGISTRY_SAVE_PATH, 0, pPathBuffer);
	}

	FOG_AppendBackslash(pPathBuffer, nBufferSize);
	return FOG_CreatePathHierarchy(pPathBuffer);
}

// 1.10f: 0x6FF61870 (#10116)
BOOL __fastcall FOG_GetInstallPath(char* pPathBuffer, size_t nBufferSize)
{
	SYSTEM_GetInstallPath(pPathBuffer, nBufferSize);
	// Note: original code does not set a return value
	return TRUE;
}

// 1.10f: 0x6FF61A10 (#10117)
BOOL __fastcall FOG_UseDirect()
{
	return gbUseDirectAccess;
}

// 1.10f: 0x6FF61840 (#10239)
void __fastcall FOG_GetModuleDirectory(char* pPathBuffer, size_t nBufferSize)
{
	SYSTEM_GetModuleDirectory(pPathBuffer, nBufferSize);
}
