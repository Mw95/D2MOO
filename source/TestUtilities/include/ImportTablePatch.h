#pragma once


#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <Windows.h>


// Returns the import address table slot through which `module` calls the function imported by name from `dll_name`,
// or nullptr if it does not import it.
inline void** find_import_slot_by_name(HMODULE module, const char* dll_name, const char* function_name)
{
	const auto base = reinterpret_cast<uint8_t*>(module);
	const auto dos_header = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
	const auto nt_headers = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos_header->e_lfanew);
	const auto& import_directory = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	if (import_directory.VirtualAddress == 0)
	{
		return nullptr;
	}

	for (auto descriptor = reinterpret_cast<const IMAGE_IMPORT_DESCRIPTOR*>(base + import_directory.VirtualAddress); descriptor->Name; ++descriptor)
	{
		if (_stricmp(reinterpret_cast<const char*>(base + descriptor->Name), dll_name) != 0 || descriptor->OriginalFirstThunk == 0)
		{
			continue;
		}

		auto lookup_entry = reinterpret_cast<const IMAGE_THUNK_DATA*>(base + descriptor->OriginalFirstThunk);
		auto iat_entry = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
		for (; lookup_entry->u1.AddressOfData; ++lookup_entry, ++iat_entry)
		{
			if (IMAGE_SNAP_BY_ORDINAL(lookup_entry->u1.Ordinal))
			{
				continue;
			}

			const auto import_by_name = reinterpret_cast<const IMAGE_IMPORT_BY_NAME*>(base + lookup_entry->u1.AddressOfData);
			if (std::strcmp(reinterpret_cast<const char*>(import_by_name->Name), function_name) == 0)
			{
				return reinterpret_cast<void**>(&iat_entry->u1.Function);
			}
		}
	}

	return nullptr;
}

// Replaces functions imported by name (typically Win32 functions) in the import address tables of modules.
// Unlike InlineHook, the function itself is not modified, so only the patched modules see the replacement.
// The tables are restored when this object is destroyed.
class ImportTablePatch
{
public:
	ImportTablePatch() = default;
	ImportTablePatch(const ImportTablePatch&) = delete;
	ImportTablePatch& operator=(const ImportTablePatch&) = delete;

	~ImportTablePatch()
	{
		for (auto it = m_patches.rbegin(); it != m_patches.rend(); ++it)
		{
			write(it->first, it->second);
		}
	}

	// Returns false when the module does not import the function, throws if `required`
	bool patch(HMODULE module, const char* dll_name, const char* function_name, const void* replacement, bool required = true)
	{
		void** slot = find_import_slot_by_name(module, dll_name, function_name);
		if (slot == nullptr)
		{
			if (required)
			{
				throw std::runtime_error(std::string("ImportTablePatch: the module does not import ") + dll_name + "!" + function_name);
			}
			return false;
		}

		m_patches.emplace_back(slot, *slot);
		write(slot, const_cast<void*>(replacement));
		return true;
	}

	// Patches the test executable, which contains the D2MOO implementation, and an original dll
	void patch_both(HMODULE original_module, const char* dll_name, const char* function_name, const void* replacement)
	{
		patch(GetModuleHandleA(nullptr), dll_name, function_name, replacement);
		patch(original_module, dll_name, function_name, replacement);
	}

private:
	static void write(void** slot, void* value)
	{
		DWORD old_protect = 0;
		if (!VirtualProtect(slot, sizeof(void*), PAGE_READWRITE, &old_protect))
		{
			throw std::runtime_error("ImportTablePatch: VirtualProtect failed");
		}
		*slot = value;
		VirtualProtect(slot, sizeof(void*), old_protect, &old_protect);
	}

	std::vector<std::pair<void**, void*>> m_patches;
};
