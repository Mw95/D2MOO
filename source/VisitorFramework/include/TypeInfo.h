#pragma once


#include <cstdint>


class Serializer;
class Deserializer;

struct TypeInfo
{
	uint64_t TypeID;

	void* (*Allocate)();

	void (*VisitWithSerializer)(Serializer&, void*);

	void (*VisitWithDeserializer)(Deserializer&, void*);
};
