#pragma once


#include <cstdint>


// Binary layout written by the Serializer and read by the Deserializer:
//
//   SerializationHeader
//   object data           Objects in object ID order (1..object_count), object 1 being the root.
//                         Pointers are stored as uint32_t object IDs (0 = nullptr).
//                         Dynamic arrays are stored inline as a uint32_t element count (NullArrayCount = nullptr) followed by the elements.
//   type table            One uint64_t type ID per object, in object ID order.
//
// All offsets are relative to the start of the header, so a serialized block can be embedded in a larger buffer.
namespace SerializationFormat
{
	constexpr uint32_t Magic = 'MOO ';

	constexpr uint32_t NullArrayCount = UINT32_MAX;

	struct Header
	{
		uint32_t magic;
		uint32_t object_count;
		uint32_t type_table_offset;
	};

	static_assert(sizeof(Header) == 12);
}
