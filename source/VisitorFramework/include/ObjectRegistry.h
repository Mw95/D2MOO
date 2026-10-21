#pragma once


#include <cstddef>
#include <cstdint>
#include <functional>
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

	// Objects are identified by their address and type, so e.g. a struct and its first member are distinct objects.
	template<typename T>
	ObjectID Register(T* object, uint64_t type_id = 0)
	{
		if (!object)
		{
			return NullObject;
		}

		const auto object_id = FindObjectId(object, type_id);
		if (object_id != NullObject)
		{
			return object_id;
		}

		ObjectID id = m_nextID++;

		m_pointerToID.emplace(Key{ object, type_id }, id);
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

		if (FindObjectId(object, type_id) != NullObject)
		{
			return;
		}

		m_pointerToID.emplace(Key{ object, type_id }, object_id);
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

	size_t Count() const
	{
		return m_idToEntry.size();
	}

	void Clear()
	{
		m_pointerToID.clear();
		m_idToEntry.clear();
		m_nextID = 1;
	}

private:
	struct Key
	{
		const void* object;
		uint64_t type_id;

		bool operator==(const Key& other) const
		{
			return object == other.object && type_id == other.type_id;
		}
	};

	struct KeyHash
	{
		size_t operator()(const Key& key) const
		{
			return std::hash<const void*>()(key.object) ^ (std::hash<uint64_t>()(key.type_id) * 31);
		}
	};

	ObjectID FindObjectId(const void* object, uint64_t type_id) const;

private:
	ObjectID m_nextID = 1;

	std::unordered_map<Key, ObjectID, KeyHash> m_pointerToID;
	std::unordered_map<ObjectID, Entry> m_idToEntry;
};
