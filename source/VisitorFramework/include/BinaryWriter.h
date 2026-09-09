#pragma once


#include <cstddef>
#include <cstring>
#include <string_view>
#include <type_traits>
#include <vector>


class BinaryWriter
{
public:
	BinaryWriter() = default;

	explicit BinaryWriter(size_t reserve);

	size_t Position() const;

	size_t Size() const;

	bool Empty() const;

	void Clear();

	void Reserve(size_t bytes);

	void WriteBytes(const void* data, size_t size);

	template<typename T>
	void Write(const T& value)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		WriteBytes(&value, sizeof(T));
	}

	template<typename T>
	void WriteArray(const T* data, size_t count)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		WriteBytes(data, sizeof(T) * count);
	}

	template<typename T, size_t N>
	void WriteArray(const T(&data)[N])
	{
		WriteArray(data, N);
	}

	void WriteString(std::string_view str);

	void Pad(size_t bytes, std::byte value = std::byte{ 0 });

	template<typename T>
	void Patch(size_t offset, const T& value)
	{
		static_assert(std::is_trivially_copyable_v<T>);

		if (offset + sizeof(T) > m_buffer.size())
		{
			throw std::out_of_range("BinaryWriter::Patch");
		}

		std::memcpy(m_buffer.data() + offset, &value, sizeof(T));
	}

	const std::vector<std::byte>& Buffer() const;

	const std::byte* Data() const;

private:
	std::vector<std::byte> m_buffer;
};
