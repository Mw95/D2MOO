#pragma once


#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

#include <Windows.h>


// Redirects the calls a module makes to an imported function by patching the module's import address table.
// Every entry of the table that currently points to `target` is replaced by `replacement`, whichever .dll it is imported from.
// The original entries are restored when the hook is destroyed.
// Contrary to InlineHook, the imported function itself is not modified, so other modules keep calling it,
// and functions shorter than a jump instruction can be redirected too.
class IatHook
{
public:
	IatHook(HMODULE module, const void* target, const void* replacement)
	{
		if (module == nullptr || target == nullptr || replacement == nullptr)
		{
			throw std::runtime_error("IatHook: module, target or replacement is null");
		}

		const auto base = reinterpret_cast<uint8_t*>(module);
		const auto dos_header = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
		const auto nt_headers = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos_header->e_lfanew);
		const auto& import_directory = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

		if (import_directory.VirtualAddress == 0)
		{
			return;
		}

		for (auto descriptor = reinterpret_cast<const IMAGE_IMPORT_DESCRIPTOR*>(base + import_directory.VirtualAddress); descriptor->Name; ++descriptor)
		{
			for (auto iat_entry = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk); iat_entry->u1.Function; ++iat_entry)
			{
				if (reinterpret_cast<const void*>(iat_entry->u1.Function) == target)
				{
					m_patched_entries.emplace_back(&iat_entry->u1.Function, iat_entry->u1.Function);
					write(&iat_entry->u1.Function, reinterpret_cast<uintptr_t>(replacement));
				}
			}
		}
	}

	IatHook(const IatHook&) = delete;
	IatHook& operator=(const IatHook&) = delete;

	IatHook(IatHook&& other) noexcept
		: m_patched_entries(std::exchange(other.m_patched_entries, {}))
	{
	}

	IatHook& operator=(IatHook&&) = delete;

	~IatHook()
	{
		for (const auto& [entry, original_value] : m_patched_entries)
		{
			write(entry, original_value);
		}
	}

	// Whether the module imports the target at all
	bool is_active() const
	{
		return !m_patched_entries.empty();
	}

private:
	using EntryType = decltype(IMAGE_THUNK_DATA::u1.Function);

	static void write(EntryType* entry, uintptr_t value)
	{
		DWORD old_protect = 0;
		if (!VirtualProtect(entry, sizeof(*entry), PAGE_READWRITE, &old_protect))
		{
			throw std::runtime_error("IatHook: VirtualProtect failed");
		}

		*entry = static_cast<EntryType>(value);

		VirtualProtect(entry, sizeof(*entry), old_protect, &old_protect);
	}

	std::vector<std::pair<EntryType*, EntryType>> m_patched_entries;
};
