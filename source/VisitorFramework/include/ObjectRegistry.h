#pragma once


#include <cstdint>
#include <unordered_map>


class ObjectRegistry
{
public:
	using ObjectID = uint32_t;

	static constexpr ObjectID NullObject = 0;

	struct Entry
	{
		ObjectID object_id;
		void* object;
		uint64_t type_id;
	};

	template<typename T>
	ObjectID Register(T* object, uint64_t type_id = 0)
	{
		if (!object)
		{
			return NullObject;
		}

		const auto object_id = FindObjectId(object);
		if (object_id != NullObject)
		{
			return object_id;
		}

		ObjectID id = m_nextID++;

		m_pointerToID.emplace(object, id);
		m_idToEntry.emplace(id, Entry{ id, object, type_id });

		return id;
	}

	template<typename T>
	void Add(ObjectID object_id, T* object, uint64_t type_id = 0)
	{
		if (object == nullptr)
		{
			return;
		}

		if (object_id == NullObject)
		{
			return;
		}

		if (FindObject(object_id) != nullptr)
		{
			return;
		}

		if (FindObjectId(object) != NullObject)
		{
			return;
		}

		m_pointerToID.emplace(object, object_id);
		m_idToEntry.emplace(object_id, Entry{ object_id, object, type_id });
	}

	void* FindObject(ObjectID object_id) const;

	const Entry FindEntry(ObjectID object_id) const
	{
		const auto it = m_idToEntry.find(object_id);
		if (it == m_idToEntry.end())
		{
			return Entry{ NullObject, nullptr, 0 };
		}

		return it->second;
	}

	void DeleteAllObjects()
	{
		for (auto& pair : m_pointerToID)
		{
			delete pair.first;
		}

		m_pointerToID.clear();
		m_idToEntry.clear();
		m_nextID = 1;
	}

private:
	ObjectID FindObjectId(void* object);

private:
	ObjectID m_nextID = 1;

	std::unordered_map<void*, ObjectID> m_pointerToID;
	std::unordered_map<ObjectID, Entry> m_idToEntry;
};
