#pragma once


#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

#include "BinaryWriter.h"
#include "DynamicArrayCountRegistry.h"
#include "FieldVisitor.h"
#include "ObjectRegistry.h"
#include "SerializationFormat.h"
#include "TypeId.h"
#include "TypeRegistry.h"
#include "VisitorTraits.h"


// Serializes an object graph reachable from a root object, see SerializationFormat.h for the layout.
// Every object reached through a pointer is written exactly once (cycles and shared pointers are preserved).
// Fixed and dynamic arrays are written inline into the object that owns them, so pointers into the middle
// of an object or an array are serialized as separate copies of the pointed-to object.
class Serializer : public FieldVisitor<Serializer>
{
public:
	using ObjectID = ObjectRegistry::ObjectID;

	explicit Serializer(BinaryWriter& writer) : m_writer(writer) {};

	template<typename T>
	void Serialize(T* root, uint64_t typeID = TypeId_v<std::remove_cv_t<T>>)
	{
		if (root == nullptr)
		{
			throw std::runtime_error("Cannot serialize null root object");
		}

		m_objects.Clear();
		m_object_id_queue = {};

		const auto start_position = m_writer.Position();

		WriteHeader();

		// Register the root with its known type, so it always gets the first object ID
		EnqueueObject(const_cast<std::remove_cv_t<T>*>(root), typeID);

		while (!m_object_id_queue.empty())
		{
			const auto object_id = m_object_id_queue.front();

			m_object_id_queue.pop();

			WriteObject(m_objects.FindEntry(object_id));
		}

		const auto object_count = m_objects.Count();

		m_writer.Patch(start_position + offsetof(SerializationFormat::Header, object_count), ToUInt32(object_count, "Too many objects"));
		m_writer.Patch(start_position + offsetof(SerializationFormat::Header, type_table_offset), ToUInt32(m_writer.Position() - start_position, "Serialized data too large"));

		for (ObjectID object_id = 1; object_id <= object_count; ++object_id)
		{
			m_writer.Write<uint64_t>(m_objects.FindEntry(object_id).type_id);
		}
	}

	template<auto PointerMember, typename T, size_t Rank>
	void VisitArrayElement(T& object, const char* member_name, const std::array<size_t, Rank>& indices)
	{
		WriteValue(GetArrayElement(Get<PointerMember>(object), indices));
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

		m_writer.WriteBytes(&Get<Member>(object), sizeof(MemberType));
	}

	template<auto Member, typename T>
	void VisitPointer(T& object, const char* member_name)
	{
		WritePointer(Get<Member>(object));
	}

	// Shadows FieldVisitor::DynamicArray() to write the element count in front of the elements,
	// so the Deserializer does not depend on the count member being visited before the array.
	template<auto PointerMember, auto CountMember, typename T>
	void DynamicArray(T& object, const char* member_name)
	{
		using CountType = std::remove_cv_t<std::remove_reference_t<decltype(Get<CountMember>(object))>>;

		static_assert(
			std::is_integral_v<CountType>,
			"DynamicArray() requires the count member to be an integral type."
		);

		const auto count = Get<CountMember>(object);

		if constexpr (std::is_signed_v<CountType>)
		{
			if (count < 0)
			{
				WriteDynamicArray<PointerMember>(object, member_name, 0);
				return;
			}
		}

		WriteDynamicArray<PointerMember>(object, member_name, static_cast<size_t>(count));
	}

	// Shadows FieldVisitor::DynamicArrayWithRegisteredCount(), see DynamicArray()
	template<auto PointerMember, typename T>
	void DynamicArrayWithRegisteredCount(T& object, const char* member_name, std::string_view count_key)
	{
		// The count is only looked up for allocated arrays, matching FieldVisitor::DynamicArrayWithRegisteredCount()
		const auto count = Get<PointerMember>(object) == nullptr ? 0 : DynamicArrayCountRegistry::Instance().GetCount(count_key);

		WriteDynamicArray<PointerMember>(object, member_name, count);
	}

private:
	template<auto PointerMember, typename T>
	void WriteDynamicArray(T& object, const char* member_name, size_t count)
	{
		using PointerType = std::remove_cv_t<std::remove_reference_t<decltype(Get<PointerMember>(object))>>;

		static_assert(
			std::is_pointer_v<PointerType>,
			"Dynamic arrays require the array member to be a pointer."
		);

		if (Get<PointerMember>(object) == nullptr)
		{
			m_writer.Write<uint32_t>(SerializationFormat::NullArrayCount);
			return;
		}

		if (count >= SerializationFormat::NullArrayCount)
		{
			throw std::runtime_error(std::string("Dynamic array '") + member_name + "' has too many elements");
		}

		m_writer.Write<uint32_t>(static_cast<uint32_t>(count));

		VisitDynamicArrayElements<PointerMember>(object, member_name, count);
	}

	template<typename ValueType>
	void WriteValue(ValueType& value)
	{
		using Type = std::remove_cv_t<ValueType>;

		if constexpr (std::is_pointer_v<Type>)
		{
			WritePointer(value);
		}
		else if constexpr (HasVisitorTraits_v<Type, Serializer>)
		{
			VisitorTraits<Type>::Visit(*this, const_cast<Type&>(value));
		}
		else if constexpr (std::is_trivially_copyable_v<Type>)
		{
			m_writer.WriteBytes(&value, sizeof(Type));
		}
		else
		{
			static_assert(sizeof(Type) == 0, "Array elements must be pointers, trivially copyable or define VisitorTraits.");
		}
	}

	template<typename Pointee>
	void WritePointer(Pointee* pointer)
	{
		using Type = std::remove_cv_t<Pointee>;

		m_writer.Write<uint32_t>(EnqueueObject(const_cast<Type*>(pointer), TypeId_v<Type>));
	}

	ObjectID EnqueueObject(void* object, uint64_t type_id)
	{
		if (object == nullptr)
		{
			return ObjectRegistry::NullObject;
		}

		const auto previous_count = m_objects.Count();

		const auto object_id = m_objects.Register(object, type_id);

		// Objects are queued in registration order, so they are written in object ID order
		if (m_objects.Count() != previous_count)
		{
			m_object_id_queue.push(object_id);
		}

		return object_id;
	}

	void WriteHeader()
	{
		// Count and type table offset are patched once all objects have been written
		m_writer.Write(SerializationFormat::Header{ SerializationFormat::Magic, 0, 0 });
	}

	void WriteObject(const ObjectRegistry::Entry& entry)
	{
		const auto* type = TypeRegistry::Instance().Find(entry.type_id);

		if (type == nullptr)
		{
			throw std::runtime_error("Unknown serialized type " + std::to_string(entry.type_id));
		}

		type->VisitWithSerializer(*this, entry.object);
	}

	static uint32_t ToUInt32(size_t value, const char* error)
	{
		if (value > std::numeric_limits<uint32_t>::max())
		{
			throw std::runtime_error(error);
		}

		return static_cast<uint32_t>(value);
	}

private:
	BinaryWriter& m_writer;

	ObjectRegistry m_objects;

	std::queue<ObjectID> m_object_id_queue;
};
