#include "TypeRegistry.h"

#include <cstdint>
#include <stdexcept>

#include "TypeInfo.h"


TypeRegistry& TypeRegistry::Instance()
{
	static TypeRegistry registry;
	return registry;
}

void TypeRegistry::Register(const TypeInfo& type_info)
{
	auto result = m_types.emplace(type_info.TypeID, type_info);

	if (!result.second)
	{
		throw std::runtime_error("Duplicate TypeID.");
	}
}

const TypeInfo* TypeRegistry::Find(uint64_t type_id) const
{
	const auto it = m_types.find(type_id);

	if (it == m_types.end())
	{
		return nullptr;
	}

	return &it->second;
}
