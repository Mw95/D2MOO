#pragma once


#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include <Windows.h>

#include <Storm.h>

#include "ImportHooks.h"


// In-memory replacement of the Storm registry functions and of SFileLoadFile, so that tests do not depend on the machine.
// Keys and file names are case insensitive.
struct StormStorageMock
{
	struct RegistryWrite
	{
		std::string szKey;
		std::string szValue;
		uint32_t nFlags;
		std::vector<uint8_t> data;	// Empty for a deletion

		bool operator==(const RegistryWrite& other) const { return szKey == other.szKey && szValue == other.szValue && nFlags == other.nFlags && data == other.data; }
	};

	static inline std::map<std::string, std::vector<uint8_t>> registry;
	static inline std::map<std::string, std::vector<uint8_t>> files;
	// Every write and deletion, in order
	static inline std::vector<RegistryWrite> registry_writes;
	// Every file name passed to SFileLoadFile, in order
	static inline std::vector<std::string> file_requests;
	static inline size_t nUnloadedFiles = 0;

	static std::string lowercase(std::string szString)
	{
		for (char& c : szString)
		{
			c = (char)std::tolower((unsigned char)c);
		}
		return szString;
	}

	static std::string registry_path(const char* szKey, const char* szValue)
	{
		return lowercase(std::string(szKey ? szKey : "") + "\\" + (szValue ? szValue : ""));
	}

	static void set_registry_data(const char* szKey, const char* szValue, const void* pData, size_t nSize)
	{
		registry[registry_path(szKey, szValue)].assign(static_cast<const uint8_t*>(pData), static_cast<const uint8_t*>(pData) + nSize);
	}

	static void set_registry_string(const char* szKey, const char* szValue, const char* szString)
	{
		set_registry_data(szKey, szValue, szString, std::strlen(szString) + 1);
	}

	static void set_registry_value(const char* szKey, const char* szValue, DWORD nValue)
	{
		set_registry_data(szKey, szValue, &nValue, sizeof(nValue));
	}

	static void set_file(const char* szFileName, const std::string& content)
	{
		files[lowercase(szFileName)].assign(content.begin(), content.end());
	}

	static const std::vector<uint8_t>* find_registry(const char* szKey, const char* szValue)
	{
		const auto it = registry.find(registry_path(szKey, szValue));
		return it == registry.end() ? nullptr : &it->second;
	}

	// Storm.#421
	static BOOL __stdcall SRegLoadData(const char* keyname, const char* valuename, uint32_t nFlags, void* lpData, uint32_t nSize, uint32_t* lpcbData)
	{
		const auto pData = find_registry(keyname, valuename);
		if (!pData)
		{
			return FALSE;
		}

		if (lpcbData)
		{
			*lpcbData = (uint32_t)pData->size();
		}

		if (lpData)
		{
			if (nSize < pData->size())
			{
				return FALSE;
			}
			std::memcpy(lpData, pData->data(), pData->size());
		}
		return TRUE;
	}

	// Storm.#422
	static BOOL __stdcall SRegLoadString(const char* keyname, const char* valuename, uint32_t nFlags, LPSTR pBuffer, size_t nBufferSize)
	{
		const auto pData = find_registry(keyname, valuename);
		if (!pData || nBufferSize == 0)
		{
			return FALSE;
		}

		const size_t nLength = std::min(std::strlen(reinterpret_cast<const char*>(pData->data())), nBufferSize - 1);
		std::memcpy(pBuffer, pData->data(), nLength);
		pBuffer[nLength] = '\0';
		return TRUE;
	}

	// Storm.#423
	static BOOL __stdcall SRegLoadValue(const char* keyname, const char* valuename, uint32_t nFlags, DWORD* value)
	{
		const auto pData = find_registry(keyname, valuename);
		if (!pData || pData->size() != sizeof(DWORD))
		{
			return FALSE;
		}

		std::memcpy(value, pData->data(), sizeof(DWORD));
		return TRUE;
	}

	// Storm.#424
	static BOOL __stdcall SRegSaveData(const char* keyname, const char* valuename, uint32_t flags, const void* lpData, uint32_t cbData)
	{
		set_registry_data(keyname, valuename, lpData, cbData);
		registry_writes.push_back({ keyname, valuename, flags, std::vector<uint8_t>(static_cast<const uint8_t*>(lpData), static_cast<const uint8_t*>(lpData) + cbData) });
		return TRUE;
	}

	// Storm.#425
	static BOOL __stdcall SRegSaveString(const char* keyname, const char* valuename, BYTE flags, const char* string)
	{
		return SRegSaveData(keyname, valuename, flags, string, (uint32_t)std::strlen(string) + 1);
	}

	// Storm.#426
	static BOOL __stdcall SRegSaveValue(const char* keyname, const char* valuename, BYTE flags, DWORD result)
	{
		return SRegSaveData(keyname, valuename, flags, &result, sizeof(result));
	}

	// Storm.#428
	static BOOL __stdcall SRegDeleteValue(const char* keyname, const char* valuename, uint32_t flags)
	{
		registry_writes.push_back({ keyname, valuename, flags, {} });
		return registry.erase(registry_path(keyname, valuename)) != 0;
	}

	// Storm.#279, the buffer is followed by nExtraBytes + 1 zeroes
	static BOOL __stdcall SFileLoadFile(const char* szFileName, void** ppBuffer, uint32_t* pSize, uint32_t nExtraBytes, LPOVERLAPPED lpOverlapped)
	{
		file_requests.emplace_back(szFileName);
		*ppBuffer = nullptr;
		if (pSize)
		{
			*pSize = 0;
		}

		const auto it = files.find(lowercase(szFileName));
		if (it == files.end())
		{
			return FALSE;
		}

		uint8_t* pBuffer = static_cast<uint8_t*>(std::calloc(1, it->second.size() + nExtraBytes + 1));
		std::memcpy(pBuffer, it->second.data(), it->second.size());
		*ppBuffer = pBuffer;
		if (pSize)
		{
			*pSize = (uint32_t)it->second.size();
		}
		return TRUE;
	}

	// Storm.#280
	static BOOL __stdcall SFileUnloadFile(void* buffer)
	{
		std::free(buffer);
		++nUnloadedFiles;
		return TRUE;
	}

	static void reset()
	{
		registry.clear();
		files.clear();
		registry_writes.clear();
		file_requests.clear();
		nUnloadedFiles = 0;
	}
};

// Installs the storage mocks. Functions the original dll does not import are only replaced for D2MOO.
inline void hook_storm_storage_mocks(ImportHooks& hooks)
{
	hooks.hook("Storm.dll", 279, reinterpret_cast<void*>(&::SFileLoadFile), reinterpret_cast<const void*>(&StormStorageMock::SFileLoadFile), false);
	hooks.hook("Storm.dll", 280, reinterpret_cast<void*>(&::SFileUnloadFile), reinterpret_cast<const void*>(&StormStorageMock::SFileUnloadFile), false);
	hooks.hook("Storm.dll", 421, reinterpret_cast<void*>(&::SRegLoadData), reinterpret_cast<const void*>(&StormStorageMock::SRegLoadData), false);
	hooks.hook("Storm.dll", 422, reinterpret_cast<void*>(&::SRegLoadString), reinterpret_cast<const void*>(&StormStorageMock::SRegLoadString), false);
	hooks.hook("Storm.dll", 423, reinterpret_cast<void*>(&::SRegLoadValue), reinterpret_cast<const void*>(&StormStorageMock::SRegLoadValue), false);
	hooks.hook("Storm.dll", 424, reinterpret_cast<void*>(&::SRegSaveData), reinterpret_cast<const void*>(&StormStorageMock::SRegSaveData), false);
	hooks.hook("Storm.dll", 425, reinterpret_cast<void*>(&::SRegSaveString), reinterpret_cast<const void*>(&StormStorageMock::SRegSaveString), false);
	hooks.hook("Storm.dll", 426, reinterpret_cast<void*>(&::SRegSaveValue), reinterpret_cast<const void*>(&StormStorageMock::SRegSaveValue), false);
	hooks.hook("Storm.dll", 428, reinterpret_cast<void*>(&::SRegDeleteValue), reinterpret_cast<const void*>(&StormStorageMock::SRegDeleteValue), false);
	StormStorageMock::reset();
}
