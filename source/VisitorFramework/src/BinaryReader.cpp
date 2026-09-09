#include "BinaryReader.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>


BinaryReader::BinaryReader(const void* data, size_t size)
	: m_begin(reinterpret_cast<const std::byte*>(data)),
	m_current(m_begin),
	m_end(m_begin + size)
{
}

size_t BinaryReader::Position() const
{
	return static_cast<size_t>(m_current - m_begin);
}

size_t BinaryReader::Remaining() const
{
	return static_cast<size_t>(m_end - m_current);
}

bool BinaryReader::End() const
{
	return m_current == m_end;
}

void BinaryReader::Seek(size_t position)
{
	if (position > Size())
	{
		throw std::out_of_range("BinaryReader::Seek");
	}

	m_current = m_begin + position;
}

void BinaryReader::Skip(size_t bytes)
{
	Require(bytes);
	m_current += bytes;
}

size_t BinaryReader::Size() const
{
	return static_cast<size_t>(m_end - m_begin);
}

void BinaryReader::ReadBytes(void* dst, size_t size)
{
	Require(size);

	std::memcpy(dst, m_current, size);

	m_current += size;
}

std::string BinaryReader::ReadString()
{
	uint32_t length = Read<uint32_t>();

	std::string result(length, '\0');

	if (length)
	{
		ReadBytes(result.data(), length);
	}

	return result;
}

void BinaryReader::Require(size_t bytes) const
{
	if (Remaining() < bytes)
	{
		throw std::out_of_range("Unexpected end of stream");
	}
}
