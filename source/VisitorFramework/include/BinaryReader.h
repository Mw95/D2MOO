#pragma once


#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>
#include <type_traits>


class BinaryReader
{
public:
	BinaryReader(const void* data, size_t size);

	size_t Position() const;

	size_t Remaining() const;

	bool End() const;

	void Seek(size_t position);

	void Skip(size_t bytes);

	size_t Size() const;

	void ReadBytes(void* dst, size_t size);

	template<typename T>
	T Read()
	{
		static_assert(std::is_trivially_copyable_v<T>);

		T value{};

		ReadBytes(&value, sizeof(T));

		return value;
	}

	template<typename T>
	void Read(T& value)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		ReadBytes(&value, sizeof(T));
	}

	template<typename T>
	void ReadArray(T* data, size_t count)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		ReadBytes(data, sizeof(T) * count);
	}

	std::string ReadString();

	template<typename T>
	T Peek() const
	{
		static_assert(std::is_trivially_copyable_v<T>);

		if (Remaining() < sizeof(T))
		{
			throw std::out_of_range("BinaryReader::Peek");
		}

		T value{};

		std::memcpy(&value, m_current, sizeof(T));

		return value;
	}

private:
	void Require(size_t bytes) const;

	const std::byte* m_begin;
	const std::byte* m_current;
	const std::byte* m_end;
};
