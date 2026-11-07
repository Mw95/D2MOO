#include <doctest.h>

#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include <ImportTablePatch.h>

#include <BnDownload.h>

#include "BnclientTestFixtures.h"


namespace
{
std::string lowercase(std::string szString)
{
	for (char& c : szString)
	{
		c = (char)std::tolower((unsigned char)c);
	}
	return szString;
}

// In-memory MPQ archives, with the Storm archive functions
struct StormArchiveMock
{
	struct Archive
	{
		std::map<std::string, std::vector<uint8_t>> files;
	};

	struct OpenFile
	{
		const std::vector<uint8_t>* pData;
		size_t nPosition;
	};

	static inline std::map<std::string, Archive> archives;
	static inline uint32_t nAuthenticationResult = 0;
	static inline std::vector<std::string> calls;
	static inline int nOpenHandles = 0;

	static BOOL __stdcall SFileOpenArchive(char* szName, int nPriority, int nFlags, HSARCHIVE* phArchive)
	{
		calls.push_back(std::string("OpenArchive ") + szName);
		*phArchive = nullptr;
		const auto it = archives.find(lowercase(szName));
		if (it == archives.end())
		{
			return FALSE;
		}
		*phArchive = reinterpret_cast<HSARCHIVE>(&it->second);
		++nOpenHandles;
		return TRUE;
	}

	static BOOL __stdcall SFileAuthenticateArchive(HSARCHIVE hArchive, uint32_t* pAuthenticationResult)
	{
		calls.push_back("AuthenticateArchive");
		*pAuthenticationResult = nAuthenticationResult;
		return TRUE;
	}

	static BOOL __stdcall SFileCloseArchive(HSARCHIVE hArchive)
	{
		calls.push_back("CloseArchive");
		--nOpenHandles;
		return TRUE;
	}

	static BOOL __stdcall SFileOpenFileEx(HSARCHIVE hArchive, const char* szFileName, uint32_t nSearchScope, HSFILE* phFile)
	{
		calls.push_back(std::string("OpenFileEx ") + szFileName + " " + std::to_string(nSearchScope));
		*phFile = nullptr;
		const Archive* pArchive = reinterpret_cast<const Archive*>(hArchive);
		const auto it = pArchive->files.find(lowercase(szFileName));
		if (it == pArchive->files.end())
		{
			return FALSE;
		}
		*phFile = reinterpret_cast<HSFILE>(new OpenFile{ &it->second, 0 });
		++nOpenHandles;
		return TRUE;
	}

	static uint32_t __stdcall SFileGetFileSize(HSFILE hFile, uint32_t* pFileSizeHigh)
	{
		if (pFileSizeHigh)
		{
			*pFileSizeHigh = 0;
		}
		return (uint32_t)reinterpret_cast<OpenFile*>(hFile)->pData->size();
	}

	static BOOL __stdcall SFileReadFile(HSFILE hFile, void* pBuffer, uint32_t nBytesToRead, uint32_t* pBytesRead, LPOVERLAPPED lpOverlapped)
	{
		OpenFile* pFile = reinterpret_cast<OpenFile*>(hFile);
		const size_t nSize = std::min<size_t>(nBytesToRead, pFile->pData->size() - pFile->nPosition);
		std::memcpy(pBuffer, pFile->pData->data() + pFile->nPosition, nSize);
		pFile->nPosition += nSize;
		if (pBytesRead)
		{
			*pBytesRead = (uint32_t)nSize;
		}
		return nSize == nBytesToRead;
	}

	static BOOL __stdcall SFileCloseFile(HSFILE hFile)
	{
		calls.push_back("CloseFile");
		delete reinterpret_cast<OpenFile*>(hFile);
		--nOpenHandles;
		return TRUE;
	}

	static void reset()
	{
		archives.clear();
		nAuthenticationResult = 0;
		calls.clear();
		nOpenHandles = 0;
	}
};

// Fog file functions mapped to Win32
struct FogFileMock
{
	static HANDLE __fastcall CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
	{
		return ::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	}

	static BOOL __fastcall CloseFile(HANDLE hFile)
	{
		return ::CloseHandle(hFile);
	}

	static BOOL __fastcall WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
	{
		return ::WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	}

	static void __cdecl Trace(const char* szFormat, ...)
	{
	}
};

// The extracted version dll is not really loaded: LoadLibraryA returns a fake module whose CheckRevision is recorded
struct VersionDllMock
{
	static inline const HMODULE hFakeModule = reinterpret_cast<HMODULE>(0x7A000000);

	static inline decltype(&::LoadLibraryA) pfRealLoadLibraryA = nullptr;
	static inline decltype(&::GetProcAddress) pfRealGetProcAddress = nullptr;
	static inline decltype(&::FreeLibrary) pfRealFreeLibrary = nullptr;
	static inline decltype(&::DeleteFileA) pfRealDeleteFileA = nullptr;

	static inline std::string szDllName;
	static inline bool bExportsCheckRevision = true;
	static inline BOOL bCheckRevisionResult = TRUE;
	static inline std::vector<std::string> calls;
	static inline std::vector<uint8_t> loadedContent;
	static inline std::vector<std::string> checkRevisionArguments;

	static HMODULE WINAPI LoadLibraryA(LPCSTR szFileName)
	{
		if (szFileName && lowercase(szFileName) == lowercase(szDllName))
		{
			calls.push_back(std::string("LoadLibraryA ") + szFileName);
			std::ifstream file(szFileName, std::ios::binary);
			loadedContent.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
			return hFakeModule;
		}
		return pfRealLoadLibraryA(szFileName);
	}

	static FARPROC WINAPI GetProcAddress(HMODULE hModule, LPCSTR szProcName)
	{
		if (hModule == hFakeModule)
		{
			calls.push_back(std::string("GetProcAddress ") + szProcName);
			return bExportsCheckRevision && std::strcmp(szProcName, "CheckRevision") == 0 ? reinterpret_cast<FARPROC>(&CheckRevision) : nullptr;
		}
		return pfRealGetProcAddress(hModule, szProcName);
	}

	static BOOL WINAPI FreeLibrary(HMODULE hModule)
	{
		if (hModule == hFakeModule)
		{
			calls.push_back("FreeLibrary");
			return TRUE;
		}
		return pfRealFreeLibrary(hModule);
	}

	static BOOL WINAPI DeleteFileA(LPCSTR szFileName)
	{
		calls.push_back(std::string("DeleteFileA ") + szFileName);
		return pfRealDeleteFileA(szFileName);
	}

	static void WINAPI Sleep(DWORD dwMilliseconds)
	{
	}

	static BOOL __stdcall CheckRevision(const char* szFileName1, const char* szFileName2, const char* szFileName3, const char* szValueString, uint32_t* pVersion, uint32_t* pChecksum, char* szExeInfo)
	{
		checkRevisionArguments = { szFileName1, szFileName2, szFileName3, szValueString };
		if (pVersion)
		{
			*pVersion = 0x01000A00;
		}
		if (pChecksum)
		{
			*pChecksum = 0xC0FFEE00 ^ (uint32_t)std::strlen(szValueString);
		}
		if (szExeInfo)
		{
			std::strcpy(szExeInfo, "Game.exe 01/01/01 00:00:00 1234567");
		}
		return bCheckRevisionResult;
	}

	static void reset()
	{
		szDllName.clear();
		bExportsCheckRevision = true;
		bCheckRevisionResult = TRUE;
		calls.clear();
		loadedContent.clear();
		checkRevisionArguments.clear();
	}
};

struct CheckRevisionApi
{
	decltype(&BNDOWNLOAD_CheckRevision) CheckRevision;
	decltype(&BNDOWNLOAD_SetVersionFile) SetVersionFile;
	decltype(&BNDOWNLOAD_SetVersionFormula) SetVersionFormula;
	char* szVersionFile;
	char* szVersionFormula;
};

const CheckRevisionApi& moo_check_revision_api()
{
	extern char gszBnVersionFile[MAX_PATH];
	extern char gszBnVersionFormula[MAX_PATH];
	static const CheckRevisionApi api = { &BNDOWNLOAD_CheckRevision, &BNDOWNLOAD_SetVersionFile, &BNDOWNLOAD_SetVersionFormula, gszBnVersionFile, gszBnVersionFormula };
	return api;
}

const CheckRevisionApi& original_check_revision_api()
{
	static const CheckRevisionApi api = {
		reinterpret_cast<decltype(&BNDOWNLOAD_CheckRevision)>(original_bnclient_address(0x6FF04480)),
		reinterpret_cast<decltype(&BNDOWNLOAD_SetVersionFile)>(original_bnclient_address(0x6FF05020)),
		reinterpret_cast<decltype(&BNDOWNLOAD_SetVersionFormula)>(original_bnclient_address(0x6FF03350)),
		original_bnclient_global<char>(0x6FF1D5A0),
		original_bnclient_global<char>(0x6FF1D7A8),
	};
	return api;
}

template<class Fixture>
struct CheckRevisionFixture : BnclientStormFixture<Fixture>
{
	ImportTablePatch patches;
	std::vector<char> mooVersionFile, originalVersionFile, mooFormula, originalFormula;

	CheckRevisionFixture()
	{
		const auto hook = [this](WORD nOrdinal, void* pMooTarget, const void* pReplacement) { this->hooks.hook("Storm.dll", nOrdinal, pMooTarget, pReplacement, false); };
		hook(251, reinterpret_cast<void*>(&::SFileAuthenticateArchive), reinterpret_cast<const void*>(&StormArchiveMock::SFileAuthenticateArchive));
		hook(252, reinterpret_cast<void*>(&::SFileCloseArchive), reinterpret_cast<const void*>(&StormArchiveMock::SFileCloseArchive));
		hook(253, reinterpret_cast<void*>(&::SFileCloseFile), reinterpret_cast<const void*>(&StormArchiveMock::SFileCloseFile));
		hook(265, reinterpret_cast<void*>(&::SFileGetFileSize), reinterpret_cast<const void*>(&StormArchiveMock::SFileGetFileSize));
		hook(266, reinterpret_cast<void*>(&::SFileOpenArchive), reinterpret_cast<const void*>(&StormArchiveMock::SFileOpenArchive));
		hook(268, reinterpret_cast<void*>(&::SFileOpenFileEx), reinterpret_cast<const void*>(&StormArchiveMock::SFileOpenFileEx));
		hook(269, reinterpret_cast<void*>(&::SFileReadFile), reinterpret_cast<const void*>(&StormArchiveMock::SFileReadFile));
		this->hooks.hook("Fog.dll", 10107, reinterpret_cast<void*>(&FOG_CreateFileA), reinterpret_cast<const void*>(&FogFileMock::CreateFileA));
		this->hooks.hook("Fog.dll", 10109, reinterpret_cast<void*>(&FOG_CloseFile), reinterpret_cast<const void*>(&FogFileMock::CloseFile));
		this->hooks.hook("Fog.dll", 10111, reinterpret_cast<void*>(&FOG_WriteFile), reinterpret_cast<const void*>(&FogFileMock::WriteFile));
		this->hooks.hook("Fog.dll", 10029, reinterpret_cast<void*>(&FOG_Trace), reinterpret_cast<const void*>(&FogFileMock::Trace), false);

		const HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
		VersionDllMock::pfRealLoadLibraryA = reinterpret_cast<decltype(&::LoadLibraryA)>(::GetProcAddress(hKernel32, "LoadLibraryA"));
		VersionDllMock::pfRealGetProcAddress = reinterpret_cast<decltype(&::GetProcAddress)>(::GetProcAddress(hKernel32, "GetProcAddress"));
		VersionDllMock::pfRealFreeLibrary = reinterpret_cast<decltype(&::FreeLibrary)>(::GetProcAddress(hKernel32, "FreeLibrary"));
		VersionDllMock::pfRealDeleteFileA = reinterpret_cast<decltype(&::DeleteFileA)>(::GetProcAddress(hKernel32, "DeleteFileA"));
		for (const auto& [szName, pReplacement] : std::initializer_list<std::pair<const char*, const void*>>{
			{ "LoadLibraryA", reinterpret_cast<const void*>(&VersionDllMock::LoadLibraryA) },
			{ "GetProcAddress", reinterpret_cast<const void*>(&VersionDllMock::GetProcAddress) },
			{ "FreeLibrary", reinterpret_cast<const void*>(&VersionDllMock::FreeLibrary) },
			{ "DeleteFileA", reinterpret_cast<const void*>(&VersionDllMock::DeleteFileA) },
			{ "Sleep", reinterpret_cast<const void*>(&VersionDllMock::Sleep) },
		})
		{
			patches.patch_both(get_original_bnclient(), "KERNEL32.dll", szName, pReplacement);
		}

		const auto save = [](const char* szBuffer) { return std::vector<char>(szBuffer, szBuffer + MAX_PATH); };
		mooVersionFile = save(moo_check_revision_api().szVersionFile);
		originalVersionFile = save(original_check_revision_api().szVersionFile);
		mooFormula = save(moo_check_revision_api().szVersionFormula);
		originalFormula = save(original_check_revision_api().szVersionFormula);
		StormArchiveMock::reset();
		VersionDllMock::reset();
	}

	~CheckRevisionFixture()
	{
		std::memcpy(moo_check_revision_api().szVersionFile, mooVersionFile.data(), MAX_PATH);
		std::memcpy(original_check_revision_api().szVersionFile, originalVersionFile.data(), MAX_PATH);
		std::memcpy(moo_check_revision_api().szVersionFormula, mooFormula.data(), MAX_PATH);
		std::memcpy(original_check_revision_api().szVersionFormula, originalFormula.data(), MAX_PATH);
		StormArchiveMock::reset();
		VersionDllMock::reset();
	}
};

struct Result
{
	BOOL bResult;
	uint32_t nVersion;
	uint32_t nChecksum;
	std::string szExeInfo;
	std::vector<std::string> archiveCalls;
	std::vector<std::string> dllCalls;
	std::vector<uint8_t> loadedContent;
	std::vector<std::string> checkRevisionArguments;
	int nOpenHandles;
	bool bDllFileLeft;

	bool operator==(const Result& other) const
	{
		return bResult == other.bResult && nVersion == other.nVersion && nChecksum == other.nChecksum && szExeInfo == other.szExeInfo
			&& archiveCalls == other.archiveCalls && dllCalls == other.dllCalls && loadedContent == other.loadedContent
			&& checkRevisionArguments == other.checkRevisionArguments && nOpenHandles == other.nOpenHandles && bDllFileLeft == other.bDllFileLeft;
	}
};

Result run(const CheckRevisionApi& api, const char* szVersionFile, const char* szFormula)
{
	StormArchiveMock::calls.clear();
	StormArchiveMock::nOpenHandles = 0;
	VersionDllMock::calls.clear();
	VersionDllMock::loadedContent.clear();
	VersionDllMock::checkRevisionArguments.clear();

	api.SetVersionFile(szVersionFile);
	api.SetVersionFormula(szFormula);

	Result result = {};
	result.nVersion = 0x11111111;
	result.nChecksum = 0x22222222;
	char szExeInfo[256];
	std::memset(szExeInfo, 'x', sizeof(szExeInfo));
	szExeInfo[255] = '\0';
	result.bResult = api.CheckRevision(&result.nVersion, &result.nChecksum, szExeInfo);
	result.szExeInfo = szExeInfo;
	result.archiveCalls = StormArchiveMock::calls;
	result.dllCalls = VersionDllMock::calls;
	result.loadedContent = VersionDllMock::loadedContent;
	result.checkRevisionArguments = VersionDllMock::checkRevisionArguments;
	result.nOpenHandles = StormArchiveMock::nOpenHandles;
	result.bDllFileLeft = !VersionDllMock::szDllName.empty() && std::filesystem::exists(VersionDllMock::szDllName);
	std::error_code error;
	if (!VersionDllMock::szDllName.empty())
	{
		std::filesystem::remove(VersionDllMock::szDllName, error);
	}
	return result;
}
}


TEST_SUITE("BnclientCheckRevisionTests")
{
	TEST_CASE_FIXTURE(CheckRevisionFixture<NoOpFixture>, "Bnclient.0x6FF04480 / Bnclient.0x6FF03B00")
	{
		std::vector<uint8_t> dllContent(0x1234);
		for (size_t i = 0; i < dllContent.size(); ++i)
		{
			dllContent[i] = (uint8_t)(i * 7 + 3);
		}

		const char* szFormula = "A=3845581634 B=880823580 C=1363937103 4 A=A-S B=B-C C=C-A A=A-B";

		struct Case
		{
			const char* szName;
			const char* szVersionFile;
			bool bArchive;
			bool bDllInArchive;
			uint32_t nAuthenticationResult;
			bool bExportsCheckRevision;
			BOOL bCheckRevisionResult;
		};

		const Case cases[] = {
			{ "Success", "IX86ver1.mpq", true, true, 0, true, TRUE },
			{ "Authenticated with a signature", "IX86ver3.mpq", true, true, 5, true, TRUE },
			{ "CheckRevision fails", "IX86ver1.mpq", true, true, 0, true, FALSE },
			{ "Missing archive", "IX86ver2.mpq", false, false, 0, true, TRUE },
			{ "Authentication failure", "IX86ver4.mpq", true, true, 2, true, TRUE },
			{ "Bad signature", "IX86ver5.mpq", true, true, 4, true, TRUE },
			{ "No dll in the archive", "IX86ver6.mpq", true, false, 0, true, TRUE },
			{ "No CheckRevision export", "IX86ver7.mpq", true, true, 0, false, TRUE },
			{ "Name without extension", "ver-IX86-1", true, true, 0, true, TRUE },
		};

		for (const Case& testCase : cases)
		{
			CAPTURE(testCase.szName);

			StormArchiveMock::archives.clear();
			std::string szDllName = testCase.szVersionFile;
			if (const size_t nDot = szDllName.find('.'); nDot != std::string::npos)
			{
				szDllName.resize(nDot);
			}
			szDllName += ".dll";
			if (testCase.bArchive)
			{
				auto& archive = StormArchiveMock::archives[lowercase(testCase.szVersionFile)];
				archive.files["readme.txt"] = { 1, 2, 3 };
				if (testCase.bDllInArchive)
				{
					archive.files[lowercase(szDllName)] = dllContent;
				}
			}
			StormArchiveMock::nAuthenticationResult = testCase.nAuthenticationResult;
			VersionDllMock::szDllName = szDllName;
			VersionDllMock::bExportsCheckRevision = testCase.bExportsCheckRevision;
			VersionDllMock::bCheckRevisionResult = testCase.bCheckRevisionResult;

			const Result moo_result = run(moo_check_revision_api(), testCase.szVersionFile, szFormula);
			const Result original_result = run(original_check_revision_api(), testCase.szVersionFile, szFormula);

			CHECK_EQ(moo_result.bResult, original_result.bResult);
			CHECK_EQ(moo_result.nVersion, original_result.nVersion);
			CHECK_EQ(moo_result.nChecksum, original_result.nChecksum);
			CHECK_EQ(moo_result.szExeInfo, original_result.szExeInfo);
			CHECK_EQ(moo_result.archiveCalls, original_result.archiveCalls);
			CHECK_EQ(moo_result.dllCalls, original_result.dllCalls);
			CHECK_MESSAGE(moo_result.loadedContent == original_result.loadedContent, "Comparing the extracted dll");
			CHECK_EQ(moo_result.checkRevisionArguments, original_result.checkRevisionArguments);
			CHECK_EQ(moo_result.nOpenHandles, original_result.nOpenHandles);
			CHECK_EQ(moo_result.bDllFileLeft, original_result.bDllFileLeft);
			CHECK_MESSAGE(moo_result == original_result, "Comparing everything observable");
		}

		// The successful case extracts the dll, passes the game files and the formula, and cleans up
		StormArchiveMock::archives.clear();
		StormArchiveMock::archives["ix86ver1.mpq"].files["ix86ver1.dll"] = dllContent;
		StormArchiveMock::nAuthenticationResult = 0;
		VersionDllMock::reset();
		VersionDllMock::szDllName = "IX86ver1.dll";
		const Result result = run(moo_check_revision_api(), "IX86ver1.mpq", szFormula);
		CHECK_EQ(result.bResult, TRUE);
		CHECK_EQ(result.nVersion, 0x01000A00);
		CHECK_MESSAGE(result.loadedContent == dllContent, "The dll is extracted");
		REQUIRE_EQ(result.checkRevisionArguments.size(), 4);
		CHECK_EQ(result.checkRevisionArguments[3], szFormula);
		CHECK_EQ(lowercase(std::filesystem::path(result.checkRevisionArguments[1]).filename().string()), "bnclient.dll");
		CHECK_EQ(lowercase(std::filesystem::path(result.checkRevisionArguments[2]).filename().string()), "d2client.dll");
		CHECK_EQ(result.nOpenHandles, 0);
		CHECK_FALSE(result.bDllFileLeft);
	}
}
