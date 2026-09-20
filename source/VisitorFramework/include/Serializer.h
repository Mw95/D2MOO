#pragma once


#include <cstdint>
#include <queue>
#include <stdexcept>
#include <type_traits>
#include <unordered_set>

#include "BinaryWriter.h"
#include "FieldVisitor.h"
#include "ObjectRegistry.h"
#include "TypeId.h"
#include "TypeRegistry.h"
#include "VisitorTraits.h"


struct SerializationHeader
{
	uint32_t magic;
	uint32_t object_count;
};

struct ObjectHeader
{
	uint32_t id;
	uint64_t type_id;
};

static_assert(sizeof(SerializationHeader) == 8);


class Serializer : public FieldVisitor<Serializer>
{
public:
	using ObjectID = ObjectRegistry::ObjectID;

	explicit Serializer(BinaryWriter& writer) : m_writer(writer) {};

	template<typename T>
	void Serialize(T* root, uint64_t typeID)
	{
		if (root == nullptr)
		{
			throw std::runtime_error("Cannot serialize null root object");
		}

		// Register the root with its known type
		const auto root_object_id = m_objects.Register(root, typeID);

		WriteHeader();

		m_written_objects.insert(root_object_id);

		const auto root_entry = m_objects.FindEntry(root_object_id);

		WriteObject(root_entry);

		while (!m_object_id_queue.empty())
		{
			const auto object_id = m_object_id_queue.front();

			m_object_id_queue.pop();

			const auto entry = m_objects.FindEntry(object_id);

			WriteObject(entry);
		}

		m_writer.Patch(m_objectTypeDataPosition, m_writer.Position());

		for (auto object_id = 0; object_id < m_written_objects.size(); ++object_id)
		{
			const auto entry = m_objects.FindEntry(object_id + 1);
			m_writer.Write<uint64_t>(entry.type_id);
		}
	}

	template<auto PointerMember, typename T, size_t Rank>
	void VisitArrayElement(T& object, const char* member_name, const std::array<size_t, Rank>& indices)
	{
		auto& object_member = GetArrayElement(object.*PointerMember, indices);

		using MemberType = std::remove_cv_t<std::remove_reference_t<decltype(object_member)>>;

		if constexpr (std::is_pointer_v<MemberType>)
		{
			auto* object_ptr = object_member;

			const auto type_id = TypeId_v<std::remove_pointer_t<MemberType>>;

			const auto object_id = m_objects.Register(object_ptr, type_id);

			m_writer.Write<uint32_t>(object_id);

			if (m_written_objects.find(object_id) == m_written_objects.end())
			{
				m_object_id_queue.emplace(object_id);
				m_written_objects.insert(object_id);
			}
		}
		else if constexpr (std::is_arithmetic_v<MemberType>)
		{
			m_writer.WriteBytes(&object_member, sizeof(MemberType));
		}
		else if constexpr (HasVisitorTraits_v<MemberType, decltype(*this)>)
		{
			VisitorTraits<MemberType>::Visit(*this, object_member);
		}
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
	void VisitIntegralField(T& object, const char* member_name, int allowed_difference)
	{
		using MemberType = std::remove_cv_t<std::remove_reference_t<decltype(Get<Member>(object))>>;

		static_assert(
			std::is_trivially_copyable_v<MemberType>,
			"VisitIntegralField() only accepts trivially copyable types."
		);

		m_writer.WriteBytes(&Get<Member>(object), sizeof(MemberType));
	}

	template<auto Member, typename T>
	void VisitPointer(T& object, const char* member_name)
	{
		using MemberType = std::remove_cv_t<std::remove_reference_t<decltype(Get<Member>(object))>>;

		auto* ptr = Get<Member>(object);

		const auto typeID = TypeId_v<std::remove_pointer_t<MemberType>>;

		const auto object_id = m_objects.Register(ptr, typeID);

		m_writer.Write<uint32_t>(object_id);

		if (m_written_objects.find(object_id) == m_written_objects.end())
		{
			m_object_id_queue.emplace(object_id);
			m_written_objects.insert(object_id);
		}
	}

private:
	void WriteHeader()
	{
		constexpr uint32_t MAGIC = 'MOO ';

		const auto header = SerializationHeader{ MAGIC, 0 };

		m_writer.Write<uint32_t>(header.magic);

		// Object count placeholder
		m_objectTypeDataPosition = m_writer.Position();

		m_writer.Write<uint32_t>(0);
	}

	void WriteObject(const ObjectRegistry::Entry& entry)
	{
		const auto* type = TypeRegistry::Instance().Find(entry.type_id);

		if (type == nullptr)
		{
			throw std::runtime_error("Unknown serialized type");
		}

		type->VisitWithSerializer(*this, entry.object);
	}

private:
	BinaryWriter& m_writer;

	ObjectRegistry m_objects;

	std::queue<ObjectRegistry::ObjectID> m_object_id_queue;

	std::unordered_set<ObjectRegistry::ObjectID> m_written_objects;

	size_t m_objectTypeDataPosition = 0;
};
