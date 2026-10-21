#pragma once


#include <array>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "BinaryReader.h"
#include "FieldVisitor.h"
#include "ObjectRegistry.h"
#include "SerializationFormat.h"
#include "TypeId.h"
#include "TypeInfo.h"
#include "TypeRegistry.h"
#include "VisitorTraits.h"


// Reads an object graph written by the Serializer, see SerializationFormat.h for the layout.
// All objects and dynamic arrays are allocated and owned by the Deserializer: pointers returned by Deserialize()
// stay valid until the Deserializer is destroyed. Malformed input throws instead of producing a corrupt graph.
class Deserializer : public FieldVisitor<Deserializer>
{
public:
	using ObjectID = ObjectRegistry::ObjectID;

	explicit Deserializer(BinaryReader& reader) : m_reader(reader) {};

	Deserializer(const Deserializer&) = delete;
	Deserializer& operator=(const Deserializer&) = delete;

	// Reads one serialized block starting at the reader's current position and leaves the reader positioned after it
	template<typename T>
	T* Deserialize()
	{
		m_objects.Clear();

		const auto start_position = m_reader.Position();

		const auto header = ReadHeader(start_position);

		const auto type_table_position = start_position + header.type_table_offset;

		AllocateObjects(header.object_count, type_table_position);

		const auto end_position = m_reader.Position();

		const auto root = m_objects.FindEntry(1);

		if (root.type_id != TypeId_v<std::remove_cv_t<T>>)
		{
			throw std::runtime_error("Serialized root object has a different type");
		}

		m_reader.Seek(start_position + sizeof(SerializationFormat::Header));

		DeserializeObjects(header.object_count);

		if (m_reader.Position() != type_table_position)
		{
			throw std::runtime_error("Serialized object data does not match the object types");
		}

		m_reader.Seek(end_position);

		return static_cast<T*>(root.object);
	}

	template<auto PointerMember, typename T, size_t Rank>
	void VisitArrayElement(T& object, const char* member_name, const std::array<size_t, Rank>& indices)
	{
		ReadValue(GetArrayElement(Get<PointerMember>(object), indices));
	}

	template<auto Member, typename T>
	void VisitObject(T& object, const char* member_name)
	{
		using MemberType = std::remove_cv_t<std::remove_reference_t<decltype(Get<Member>(object))>>;

		VisitorTraits<MemberType>::Visit(*this, Get<Member>(object));
	}

	template<auto Member, typename T>
	void VisitField(T& object, const char* member_name)
	{
		using MemberType = std::remove_cv_t<std::remove_reference_t<decltype(Get<Member>(object))>>;

		static_assert(
			std::is_trivially_copyable_v<MemberType>,
			"VisitField() only accepts trivially copyable types."
		);

		m_reader.ReadBytes(&Get<Member>(object), sizeof(MemberType));
	}

	template<auto Member, typename T>
	void VisitPointer(T& object, const char* member_name)
	{
		ReadPointer(Get<Member>(object));
	}

	// Shadows FieldVisitor::DynamicArray(): the element count is read from the stream, because the count member
	// may not have been deserialized yet. The count member itself is restored when it is visited.
	template<auto PointerMember, auto CountMember, typename T>
	void DynamicArray(T& object, const char* member_name)
	{
		ReadDynamicArray<PointerMember>(object, member_name);
	}

	// Shadows FieldVisitor::DynamicArrayWithRegisteredCount(), see DynamicArray()
	template<auto PointerMember, typename T>
	void DynamicArrayWithRegisteredCount(T& object, const char* member_name, std::string_view count_key)
	{
		ReadDynamicArray<PointerMember>(object, member_name);
	}

private:
	using OwnedMemory = std::unique_ptr<void, void(*)(void*)>;

	template<auto PointerMember, typename T>
	void ReadDynamicArray(T& object, const char* member_name)
	{
		using PointerType = std::remove_cv_t<std::remove_reference_t<decltype(Get<PointerMember>(object))>>;

		static_assert(
			std::is_pointer_v<PointerType>,
			"Dynamic arrays require the array member to be a pointer."
		);

		using ElementType = std::remove_cv_t<std::remove_pointer_t<PointerType>>;

		const auto count = m_reader.Read<uint32_t>();

		if (count == SerializationFormat::NullArrayCount)
		{
			Get<PointerMember>(object) = nullptr;
			return;
		}

		// Reject counts that cannot fit in the remaining data before allocating
		if (count > m_reader.Remaining() / MinSerializedSize<ElementType>())
		{
			throw std::runtime_error(std::string("Dynamic array '") + member_name + "' exceeds the serialized data");
		}

		auto* elements = new ElementType[count]();

		m_owned_memory.emplace_back(elements, [](void* memory) { delete[] static_cast<ElementType*>(memory); });

		Get<PointerMember>(object) = elements;

		VisitDynamicArrayElements<PointerMember>(object, member_name, count);
	}

	template<typename ValueType>
	void ReadValue(ValueType& value)
	{
		if constexpr (std::is_pointer_v<ValueType>)
		{
			ReadPointer(value);
		}
		else if constexpr (HasVisitorTraits_v<ValueType, Deserializer>)
		{
			VisitorTraits<ValueType>::Visit(*this, value);
		}
		else if constexpr (std::is_trivially_copyable_v<ValueType>)
		{
			m_reader.ReadBytes(&value, sizeof(ValueType));
		}
		else
		{
			static_assert(sizeof(ValueType) == 0, "Array elements must be pointers, trivially copyable or define VisitorTraits.");
		}
	}

	template<typename Pointee>
	void ReadPointer(Pointee*& pointer)
	{
		using Type = std::remove_cv_t<Pointee>;

		const auto object_id = m_reader.Read<uint32_t>();

		if (object_id == ObjectRegistry::NullObject)
		{
			pointer = nullptr;
			return;
		}

		// All objects are allocated up front, so pointers can be resolved immediately
		const auto entry = m_objects.FindEntry(object_id);

		if (entry.object == nullptr)
		{
			throw std::runtime_error("Serialized pointer references unknown object ID " + std::to_string(object_id));
		}

		if (entry.type_id != TypeId_v<Type>)
		{
			throw std::runtime_error("Serialized pointer references object ID " + std::to_string(object_id) + " of a different type");
		}

		pointer = static_cast<Type*>(entry.object);
	}

	// Smallest number of bytes a single array element occupies in the stream (1 if unknown, e.g. for visited structs)
	template<typename ElementType>
	static constexpr size_t MinSerializedSize()
	{
		if constexpr (std::is_pointer_v<ElementType>)
		{
			return sizeof(uint32_t);
		}
		else if constexpr (!HasVisitorTraits_v<ElementType, Deserializer> && std::is_trivially_copyable_v<ElementType>)
		{
			return sizeof(ElementType);
		}
		else
		{
			return 1;
		}
	}

	SerializationFormat::Header ReadHeader(size_t start_position)
	{
		const auto header = m_reader.Read<SerializationFormat::Header>();

		if (header.magic != SerializationFormat::Magic)
		{
			throw std::runtime_error("Invalid serialization file");
		}

		if (header.object_count == 0)
		{
			throw std::runtime_error("Serialized data contains no objects");
		}

		if (header.type_table_offset < sizeof(SerializationFormat::Header)
			|| header.type_table_offset > m_reader.Size() - start_position
			|| header.object_count > (m_reader.Size() - start_position - header.type_table_offset) / sizeof(uint64_t))
		{
			throw std::runtime_error("Serialized type table is out of bounds");
		}

		return header;
	}

	void AllocateObjects(uint32_t object_count, size_t type_table_position)
	{
		m_reader.Seek(type_table_position);

		for (ObjectID object_id = 1; object_id <= object_count; ++object_id)
		{
			const auto type_id = m_reader.Read<uint64_t>();

			const TypeInfo* info = TypeRegistry::Instance().Find(type_id);

			if (info == nullptr)
			{
				throw std::runtime_error("Unknown object type " + std::to_string(type_id));
			}

			auto* memory = info->Allocate();

			m_owned_memory.emplace_back(memory, info->Destroy);

			m_objects.Add(object_id, memory, type_id);
		}
	}

	void DeserializeObjects(uint32_t object_count)
	{
		for (ObjectID object_id = 1; object_id <= object_count; ++object_id)
		{
			const auto entry = m_objects.FindEntry(object_id);

			TypeRegistry::Instance().Find(entry.type_id)->VisitWithDeserializer(*this, entry.object);
		}
	}

private:
	BinaryReader& m_reader;

	ObjectRegistry m_objects;

	// Everything allocated by this Deserializer, freed on destruction (also if deserialization throws)
	std::vector<OwnedMemory> m_owned_memory;
};
