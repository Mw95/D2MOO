#pragma once


#include <cstdint>
#include <unordered_map>

#include "TypeInfo.h"


class TypeRegistry
{
public:
	static TypeRegistry& Instance();

	void Register(const TypeInfo& type_info);

	const TypeInfo* Find(uint64_t type_id) const;

private:
	std::unordered_map<uint64_t, TypeInfo> m_types;
};
