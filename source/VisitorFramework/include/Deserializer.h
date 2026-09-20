#pragma once


#include <array>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "BinaryReader.h"
#include "FieldVisitor.h"
#include "ObjectRegistry.h"
#include "PointerFixups.h"
#include "TypeInfo.h"
#include "TypeRegistry.h"
#include "VisitorTraits.h"


class Deserializer : public FieldVisitor<Deserializer>
{
public:
	using ObjectID = ObjectRegistry::ObjectID;

	explicit Deserializer(BinaryReader& reader) : m_reader(reader) {};

	~Deserializer()
	{
		m_objects.DeleteAllObjects();
	}

	template<typename T>
	T* Deserialize()
	{
		ReadHeader();

		AllocateObjects();

		DeserializeObjects();

		m_fixups.Resolve(m_objects);

		return reinterpret_cast<T*>(m_objects.FindObject(1));
	}

	template<auto PointerMember, typename T, size_t Rank>
	void VisitArrayElement(T& object, const char* member_name, const std::array<size_t, Rank>& indices)
	{
		auto& object_member = GetArrayElement(object.*PointerMember, indices);

		using MemberType = std::remove_cv_t<std::remove_reference_t<decltype(object_member)>>;

		if constexpr (std::is_pointer_v<MemberType>)
		{
			const auto object_id = m_reader.Read<uint32_t>();

			m_fixups.Add(reinterpret_cast<void**>(&object_member), object_id);
		}
		else if constexpr (std::is_arithmetic_v<MemberType>)
		{
			m_reader.ReadBytes(&object_member, sizeof(MemberType));
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

		m_reader.ReadBytes(&Get<Member>(object), sizeof(MemberType));
	}

	template<auto Member, typename T>
	void VisitIntegralField(T& object, const char* member_name, int allowed_difference)
	{
		using MemberType = std::remove_cv_t<std::remove_reference_t<decltype(Get<Member>(object))>>;

		static_assert(
			std::is_integral_v<MemberType>,
			"VisitIntegralField() only accepts integral types."
		);

		m_reader.ReadBytes(&Get<Member>(object), sizeof(MemberType));
	}

	template<auto Member, typename T>
	void VisitPointer(T& object, const char* member_name)
	{
		using MemberType = std::remove_cv_t<std::remove_reference_t<decltype(Get<Member>(object))>>;

		const auto object_id = m_reader.Read<uint32_t>();

		m_fixups.Add(reinterpret_cast<void**>(&Get<Member>(object)), object_id);
	}

private:
	struct PendingObject
	{
		ObjectID ID;
		uint64_t TypeID;
	};

	void ReadHeader()
	{
		constexpr uint32_t MAGIC = 'MOO ';

		const auto magic = m_reader.Read<uint32_t>();

		if (magic != MAGIC)
		{
			throw std::runtime_error("Invalid serialization file");
		}
	}

	void AllocateObjects()
	{
		const auto object_type_data_position = m_reader.Read<uint32_t>();

		const auto start_position = m_reader.Position();

		m_reader.Seek(object_type_data_position);

		auto current_object_id = 0;
		do
		{
			const auto type_id = m_reader.Read<uint64_t>();

			PendingObject pending_object{};
			pending_object.ID = ++current_object_id;
			pending_object.TypeID = type_id;

			const TypeInfo* info = TypeRegistry::Instance().Find(pending_object.TypeID);

			if (info == nullptr)
			{
				throw std::runtime_error("Unknown object type");
			}

			auto* memory = info->Allocate();

			m_objects.Add(pending_object.ID, memory);

			m_pending.push_back(pending_object);
		}
		while (!m_reader.End());

		m_reader.Seek(start_position);
	}

	void DeserializeObjects()
	{
		for (const auto& pending_object : m_pending)
		{
			const auto* info = TypeRegistry::Instance().Find(pending_object.TypeID);

			auto* address = m_objects.FindObject(pending_object.ID);

			info->VisitWithDeserializer(*this, address);
		}
	}

private:
	BinaryReader& m_reader;

	std::vector<PendingObject> m_pending;

	ObjectRegistry m_objects;

	PointerFixups m_fixups;
};
