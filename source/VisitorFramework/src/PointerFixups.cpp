#include "PointerFixups.h"

#include <stdexcept>

#include "ObjectRegistry.h"


void PointerFixups::Add(void** location, ObjectID target)
{
	if (location == nullptr)
	{
		return;
	}

	// Null pointers do not need patching
	if (target == ObjectRegistry::NullObject)
	{
		*location = nullptr;
		return;
	}

	m_fixups.push_back({ location, target });
}

void PointerFixups::Resolve(const ObjectRegistry& objects)
{
	for (auto& fixup : m_fixups)
	{
		void* object = objects.FindObject(fixup.TargetID);
		if (object == nullptr)
		{
			throw std::runtime_error("PointerFixups: Missing object ID");
		}

		*fixup.Location = object;
	}

	Clear();
}

size_t PointerFixups::Count() const
{
	return m_fixups.size();
}

void PointerFixups::Clear()
{
	m_fixups.clear();
}
