#pragma once


#include <cstdint>
#include <cstring>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

#include <Windows.h>

#include <FogMemoryMocks.h>
#include <FunctionPair.h>
#include <ImportHooks.h>
#include <NoOpFixture.h>
#include <StormMocks.h>

#include <D2Lang.h>
#include <D2Launch.h>
#include <D2Unicode.h>
#include <Fog.h>
#include <D2WinEditBox.h>



inline HMODULE get_original_d2launch()
{
	static const HMODULE module = []()
	{
		const auto module = LoadLibraryA((std::filesystem::current_path() / "D2Launch.dll").string().c_str());
		if (module == nullptr)
		{
			throw std::runtime_error("Cannot load the original D2Launch.dll");
		}
		return module;
	}();
	return module;
}

// Address in the loaded original D2Launch.dll of an address given for the 1.10f image base
inline uintptr_t original_d2launch_address(uintptr_t nAddress)
{
	return reinterpret_cast<uintptr_t>(get_original_d2launch()) + nAddress - D2LaunchImageBase;
}

template<typename T>
T* original_d2launch_global(uintptr_t nAddress)
{
	return reinterpret_cast<T*>(original_d2launch_address(nAddress));
}

// Pair of the D2MOO function and the same function in the original D2Launch.dll
template<typename Function>
auto make_d2launch_pair(Function& function, uintptr_t nAddress)
{
	return make_function_pair(function, original_d2launch_address(nAddress));
}

// Replaces the Storm and Fog memory functions, which are only stubs in D2MOO
template<class Fixture>
struct D2LaunchStormFixture : Fixture
{
	ImportHooks hooks{ get_original_d2launch() };

	D2LaunchStormFixture()
	{
		hook_storm_mocks(hooks);
		hook_fog_memory_mocks(hooks);
	}
};


// D2LANG_GetStringFromTblIndex returns a string made of the index, D2Win_10077_EDITBOX_GetText returns the text of a fake edit box
struct D2LaunchUiMock
{
	static inline Unicode wszStrings[0x10000][8];
	static inline std::vector<short> string_calls;

	static const Unicode* __fastcall GetStringFromTblIndex(short nIndex)
	{
		string_calls.push_back(nIndex);
		Unicode* wszString = wszStrings[(uint16_t)nIndex];
		const std::string szString = "#" + std::to_string((uint16_t)nIndex);
		for (size_t i = 0; i <= szString.size(); ++i)
		{
			wszString[i] = (Unicode)(uint16_t)szString.c_str()[i];
		}
		return wszString;
	}

	// The tests pass a pointer to a Unicode string as the edit box
	static const Unicode* __fastcall EditBoxGetText(D2WinEditBoxStrc* pEditBox)
	{
		return reinterpret_cast<const Unicode*>(pEditBox);
	}
};

template<class Fixture>
struct D2LaunchUiFixture : D2LaunchStormFixture<Fixture>
{
	D2LaunchUiFixture()
	{
		this->hooks.hook("D2Lang.dll", 10004, reinterpret_cast<void*>(&D2LANG_GetStringFromTblIndex), reinterpret_cast<const void*>(&D2LaunchUiMock::GetStringFromTblIndex));
		this->hooks.hook("D2Win.dll", 10077, reinterpret_cast<void*>(&D2Win_10077_EDITBOX_GetText), reinterpret_cast<const void*>(&D2LaunchUiMock::EditBoxGetText));
		D2LaunchUiMock::string_calls.clear();
	}
};


// Fog file functions working on real files in a temporary save directory
struct D2LaunchFileMock
{
	static inline std::string szSavePath;

	static size_t __fastcall GetSavePath(char* pPathBuffer, size_t nBufferSize)
	{
		strncpy_s(pPathBuffer, nBufferSize, szSavePath.c_str(), _TRUNCATE);
		return std::strlen(pPathBuffer);
	}

	static HANDLE __fastcall CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
	{
		const HANDLE hFile = ::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		return hFile == INVALID_HANDLE_VALUE ? nullptr : hFile;
	}

	static BOOL __fastcall CloseFile(HANDLE hFile)
	{
		return ::CloseHandle(hFile);
	}

	static BOOL __fastcall ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
	{
		return ::ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
	}

	static BOOL __fastcall WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
	{
		return ::WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	}

	static DWORD __fastcall SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
	{
		return ::SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
	}

	static BOOL __fastcall CreatePathHierarchy(char* szPath)
	{
		std::error_code error;
		std::filesystem::create_directories(szPath, error);
		return !error;
	}

	// Checksum of the .d2s files
	static uint32_t __stdcall ComputeChecksum(void* pData, size_t dwSize)
	{
		uint32_t nChecksum = 0;
		for (size_t i = 0; i < dwSize; ++i)
		{
			nChecksum = ((nChecksum << 1) | (nChecksum >> 31)) + static_cast<const uint8_t*>(pData)[i];
		}
		return nChecksum;
	}

	// Stores 14 bits in two bytes, 7 bits each with the high bit set
	static void __stdcall Encode14BitsToString(uint16_t* p2Characters, uint32_t value)
	{
		uint8_t* pBytes = reinterpret_cast<uint8_t*>(p2Characters);
		pBytes[0] = (uint8_t)((value & 0x7F) | 0x80);
		pBytes[1] = (uint8_t)(((value >> 7) & 0x7F) | 0x80);
	}
};

template<class Fixture>
struct D2LaunchFileFixture : D2LaunchStormFixture<Fixture>
{
	std::filesystem::path save_directory;

	D2LaunchFileFixture()
	{
		save_directory = std::filesystem::temp_directory_path() / ("D2LaunchTests_" + std::to_string(GetCurrentProcessId()));
		std::filesystem::remove_all(save_directory);
		std::filesystem::create_directories(save_directory);
		D2LaunchFileMock::szSavePath = save_directory.string() + "\\";

		hook_fog(10115, &FOG_GetSavePath, &D2LaunchFileMock::GetSavePath);
		hook_fog(10107, &FOG_CreateFileA, &D2LaunchFileMock::CreateFileA);
		hook_fog(10109, &FOG_CloseFile, &D2LaunchFileMock::CloseFile);
		hook_fog(10110, &FOG_ReadFile, &D2LaunchFileMock::ReadFile);
		hook_fog(10111, &FOG_WriteFile, &D2LaunchFileMock::WriteFile);
		hook_fog(10112, &FOG_SetFilePointer, &D2LaunchFileMock::SetFilePointer);
		hook_fog(10114, &FOG_CreatePathHierarchy, &D2LaunchFileMock::CreatePathHierarchy);
		hook_fog(10229, &FOG_ComputeChecksum, &D2LaunchFileMock::ComputeChecksum);
		hook_fog(10086, &FOG_Encode14BitsToString, &D2LaunchFileMock::Encode14BitsToString);
	}

	~D2LaunchFileFixture()
	{
		std::error_code error;
		std::filesystem::remove_all(save_directory, error);
	}

	std::vector<uint8_t> read_file(const std::string& szName) const
	{
		std::vector<uint8_t> data;
		if (FILE* pFile = _wfopen((save_directory / szName).c_str(), L"rb"))
		{
			uint8_t buffer[0x1000];
			size_t nRead;
			while ((nRead = fread(buffer, 1, sizeof(buffer), pFile)) > 0)
			{
				data.insert(data.end(), buffer, buffer + nRead);
			}
			fclose(pFile);
		}
		return data;
	}

	void write_file(const std::string& szName, const std::vector<uint8_t>& data) const
	{
		if (FILE* pFile = _wfopen((save_directory / szName).c_str(), L"wb"))
		{
			fwrite(data.data(), 1, data.size(), pFile);
			fclose(pFile);
		}
	}

private:
	template<typename Function>
	void hook_fog(WORD nOrdinal, Function* pMooTarget, Function* pReplacement)
	{
		this->hooks.hook("Fog.dll", nOrdinal, reinterpret_cast<void*>(pMooTarget), reinterpret_cast<const void*>(pReplacement), false);
	}
};
