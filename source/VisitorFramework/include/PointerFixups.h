#pragma once


#include <vector>

#include "ObjectRegistry.h"


class PointerFixups
{
public:
	using ObjectID = ObjectRegistry::ObjectID;

	struct Fixup
	{
		// Address of the pointer field that needs patching
		void** Location;

		// Object ID that this pointer should reference
		ObjectID TargetID;
	};

public:
	void Add(void** location, ObjectID target);

	void Resolve(const ObjectRegistry& objects);

	size_t Count() const;

	void Clear();

private:
	std::vector<Fixup> m_fixups;
};
