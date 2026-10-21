#include "ObjectRegistry.h"


void* ObjectRegistry::FindObject(ObjectRegistry::ObjectID object_id) const
{
	if (object_id == NullObject)
	{
		return nullptr;
	}

	const auto it = m_idToEntry.find(object_id);

	return it == m_idToEntry.end() ? nullptr : it->second.object;
}

ObjectRegistry::ObjectID ObjectRegistry::FindObjectId(const void* object, uint64_t type_id) const
{
	const auto it = m_pointerToID.find(Key{ object, type_id });

	if (it != m_pointerToID.end())
	{
		return it->second;
	}

	return NullObject;
}
