#include "BinaryWriter.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string_view>
#include <vector>


BinaryWriter::BinaryWriter(size_t reserve)
{
	m_buffer.reserve(reserve);
}

size_t BinaryWriter::Position() const
{
	return m_buffer.size();
}

size_t BinaryWriter::Size() const
{
	return m_buffer.size();
}

bool BinaryWriter::Empty() const
{
	return m_buffer.empty();
}

void BinaryWriter::Clear()
{
	m_buffer.clear();
}

void BinaryWriter::Reserve(size_t bytes)
{
	m_buffer.reserve(bytes);
}

void BinaryWriter::WriteBytes(const void* data, size_t size)
{
	if (size == 0)
	{
		return;
	}

	const auto oldSize = m_buffer.size();
	m_buffer.resize(oldSize + size);

	std::memcpy(m_buffer.data() + oldSize, data, size);
}

void BinaryWriter::WriteString(std::string_view str)
{
	Write<uint32_t>(static_cast<uint32_t>(str.size()));

	if (!str.empty())
	{
		WriteBytes(str.data(), str.size());
	}
}

void BinaryWriter::Pad(size_t bytes, std::byte value)
{
	m_buffer.insert(m_buffer.end(), bytes, value);
}

const std::vector<std::byte>& BinaryWriter::Buffer() const
{
	return m_buffer;
}

const std::byte* BinaryWriter::Data() const
{
	return m_buffer.data();
}
