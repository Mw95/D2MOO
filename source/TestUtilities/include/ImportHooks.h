#pragma once


#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <Windows.h>

#include "InlineHook.h"


// Replaces a function imported by ordinal, both for the D2MOO implementation linked into the test executable and
// for an original dll. Each target is only hooked once: the original dll may import D2MOO's dll when it was loaded first.
// The hooks are removed when this object is destroyed.
class ImportHooks
{
public:
	explicit ImportHooks(HMODULE original_module)
		: m_original_module(original_module)
	{
		if (original_module == nullptr)
		{
			throw std::runtime_error("ImportHooks: the original module is not loaded");
		}
		m_hooks.reserve(64);
	}

	ImportHooks(const ImportHooks&) = delete;
	ImportHooks& operator=(const ImportHooks&) = delete;

	// moo_target is the function called by the D2MOO implementation, usually &FUNCTION.
	// When `required` is true, the original dll must import the function.
	void hook(const char* dll_name, WORD ordinal, void* moo_target, const void* replacement, bool required = true)
	{
		void* original_target = find_imported_function_by_ordinal(m_original_module, dll_name, ordinal);
		if (original_target == nullptr && required)
		{
			throw std::runtime_error(std::string("ImportHooks: the original dll does not import ") + dll_name + " #" + std::to_string(ordinal));
		}

		hook_target(moo_target, replacement);
		hook_target(original_target, replacement);
	}

	// Hooks a function at a known address (for instance a function of the original dll itself)
	void hook_target(void* target, const void* replacement)
	{
		if (target == nullptr || std::find(m_targets.begin(), m_targets.end(), target) != m_targets.end())
		{
			return;
		}

		m_hooks.emplace_back(target, replacement);
		m_targets.push_back(target);
	}

private:
	HMODULE m_original_module;
	std::vector<InlineHook> m_hooks;
	std::vector<void*> m_targets;
};
