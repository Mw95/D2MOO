#include <doctest.h>

#include <iterator>
#include <stdexcept>

#include "BinaryReader.h"


TEST_SUITE("BinaryReaderTests")
{
	TEST_CASE("Constructor initializes reader with data and size")
	{
		uint8_t data[] = { 1, 2, 3, 4, 5 };
		BinaryReader reader(data, sizeof(data));

		CHECK_EQ(reader.Size(), 5);
		CHECK_EQ(reader.Position(), 0);
		CHECK_EQ(reader.Remaining(), 5);
		CHECK(!reader.End());
	}

	TEST_CASE("Position() returns current position")
	{
		uint32_t data[] = { 0x12345678, 0x9ABCDEF0 };
		BinaryReader reader(data, sizeof(data));

		CHECK_EQ(reader.Position(), 0);
		reader.Skip(4);
		CHECK_EQ(reader.Position(), 4);
		reader.Skip(4);
		CHECK_EQ(reader.Position(), 8);
	}

	TEST_CASE("Remaining() returns remaining bytes")
	{
		uint8_t data[] = { 1, 2, 3, 4, 5 };
		BinaryReader reader(data, sizeof(data));

		CHECK_EQ(reader.Remaining(), 5);
		reader.Skip(2);
		CHECK_EQ(reader.Remaining(), 3);
		reader.Skip(1);
		CHECK_EQ(reader.Remaining(), 2);
		reader.Skip(2);
		CHECK_EQ(reader.Remaining(), 0);
	}

	TEST_CASE("End() returns true when at end of stream")
	{
		uint8_t data[] = { 1, 2, 3 };
		BinaryReader reader(data, sizeof(data));

		CHECK(!reader.End());
		reader.Skip(3);
		CHECK(reader.End());
	}

	TEST_CASE("Seek() moves to absolute position")
	{
		uint8_t data[] = { 1, 2, 3, 4, 5 };
		BinaryReader reader(data, sizeof(data));

		reader.Seek(2);
		CHECK_EQ(reader.Position(), 2);
		CHECK_EQ(reader.Remaining(), 3);

		reader.Seek(0);
		CHECK_EQ(reader.Position(), 0);
		CHECK_EQ(reader.Remaining(), 5);
	}

	TEST_CASE("Seek() throws on out of range position")
	{
		uint8_t data[] = { 1, 2, 3 };
		BinaryReader reader(data, sizeof(data));

		CHECK_THROWS_AS(reader.Seek(10), std::out_of_range);
	}

	TEST_CASE("Skip() moves position forward")
	{
		uint8_t data[] = { 1, 2, 3, 4, 5 };
		BinaryReader reader(data, sizeof(data));

		reader.Skip(1);
		CHECK_EQ(reader.Position(), 1);
		reader.Skip(2);
		CHECK_EQ(reader.Position(), 3);
	}

	TEST_CASE("Skip() throws when skipping beyond stream")
	{
		uint8_t data[] = { 1, 2, 3 };
		BinaryReader reader(data, sizeof(data));

		CHECK_THROWS_AS(reader.Skip(5), std::out_of_range);
	}

	TEST_CASE("Size() returns total size")
	{
		uint8_t data[] = { 1, 2, 3, 4, 5 };
		BinaryReader reader(data, sizeof(data));

		CHECK_EQ(reader.Size(), 5);
		reader.Skip(2);
		CHECK_EQ(reader.Size(), 5);
	}

	TEST_CASE("ReadBytes() reads raw bytes")
	{
		uint8_t data[] = { 0xAA, 0xBB, 0xCC, 0xDD };
		BinaryReader reader(data, sizeof(data));

		uint8_t buffer[4]{};
		reader.ReadBytes(buffer, sizeof(buffer));

		CHECK_EQ(buffer[0], 0xAA);
		CHECK_EQ(buffer[1], 0xBB);
		CHECK_EQ(buffer[2], 0xCC);
		CHECK_EQ(buffer[3], 0xDD);
		CHECK_EQ(reader.Position(), 4);
	}

	TEST_CASE("ReadBytes() throws on insufficient data")
	{
		uint8_t data[] = { 1, 2, 3 };
		BinaryReader reader(data, sizeof(data));

		uint8_t buffer[5]{};
		CHECK_THROWS_AS(reader.ReadBytes(buffer, sizeof(buffer)), std::out_of_range);
	}

	TEST_CASE("Read<T>() reads single value")
	{
		uint32_t value = 0x12345678;
		BinaryReader reader(&value, sizeof(value));

		uint32_t result = reader.Read<uint32_t>();
		CHECK_EQ(result, 0x12345678);
		CHECK_EQ(reader.Position(), 4);
	}

	TEST_CASE("Read<T>() works with multiple types")
	{
		#pragma pack(1)
		struct TestData {
			uint8_t u8;
			uint16_t u16;
			uint32_t u32;
			uint64_t u64;
		};
		#pragma pack()

		TestData data{ 0xAA, 0xBBCC, 0xDDEEFF11, 0x2233445566778899 };

		BinaryReader reader(&data, sizeof(data));

		CHECK_EQ(reader.Read<uint8_t>(), 0xAA);
		CHECK_EQ(reader.Read<uint16_t>(), 0xBBCC);
		CHECK_EQ(reader.Read<uint32_t>(), 0xDDEEFF11);
		CHECK_EQ(reader.Read<uint64_t>(), 0x2233445566778899);
	}

	TEST_CASE("Read<T&>() reads into reference")
	{
		uint32_t value = 0x12345678;
		BinaryReader reader(&value, sizeof(value));

		uint32_t result{};
		reader.Read(result);
		CHECK_EQ(result, 0x12345678);
		CHECK_EQ(reader.Position(), 4);
	}

	TEST_CASE("Read<T>() throws on insufficient data")
	{
		uint8_t data[] = { 1, 2 };
		BinaryReader reader(data, sizeof(data));

		CHECK_THROWS_AS(reader.Read<uint32_t>(), std::out_of_range);
	}

	TEST_CASE("ReadArray<T>() reads array of values")
	{
		uint32_t data[] = { 0x11111111, 0x22222222, 0x33333333 };
		BinaryReader reader(data, sizeof(data));

		uint32_t result[3]{};
		reader.ReadArray(result, std::size(result));

		CHECK_EQ(result[0], 0x11111111);
		CHECK_EQ(result[1], 0x22222222);
		CHECK_EQ(result[2], 0x33333333);
		CHECK_EQ(reader.Position(), 12);
	}

	TEST_CASE("ReadArray<T>() throws on insufficient data")
	{
		uint32_t data[] = { 0x11111111, 0x22222222 };
		BinaryReader reader(data, sizeof(data));

		uint32_t result[3]{};
		CHECK_THROWS_AS(reader.ReadArray(result, std::size(result)), std::out_of_range);
	}

	TEST_CASE("ReadString() reads length-prefixed string")
	{
		struct StringData {
			uint32_t length;
			char data[5];
		};

		StringData data{ 5, { 'H', 'e', 'l', 'l', 'o' }};

		BinaryReader reader(&data, sizeof(data));
		std::string result = reader.ReadString();

		CHECK_EQ(result, "Hello");
		CHECK_EQ(reader.Position(), 9);
	}

	TEST_CASE("ReadString() reads empty string")
	{
		uint32_t length = 0;
		BinaryReader reader(&length, sizeof(length));

		std::string result = reader.ReadString();
		CHECK_EQ(result, "");
		CHECK_EQ(reader.Position(), 4);
	}

	TEST_CASE("ReadString() throws when insufficient data for length")
	{
		uint8_t data[] = { 0x01 };
		BinaryReader reader(data, sizeof(data));

		CHECK_THROWS_AS(reader.ReadString(), std::out_of_range);
	}

	TEST_CASE("ReadString() throws when insufficient data for string content")
	{
		struct StringData {
			uint32_t length;
			uint8_t data[2];
		};

		StringData data{ 10, { 0x41, 0x42 } };

		BinaryReader reader(&data, sizeof(data));
		CHECK_THROWS_AS(reader.ReadString(), std::out_of_range);
	}

	TEST_CASE("Peek<T>() returns value without advancing position")
	{
		uint32_t value = 0x12345678;
		BinaryReader reader(&value, sizeof(value));

		uint32_t peeked = reader.Peek<uint32_t>();
		CHECK_EQ(peeked, 0x12345678);
		CHECK_EQ(reader.Position(), 0);

		uint32_t read = reader.Read<uint32_t>();
		CHECK_EQ(read, 0x12345678);
		CHECK_EQ(reader.Position(), 4);
	}

	TEST_CASE("Peek<T>() works at different positions")
	{
		uint32_t data[] = { 0x11111111, 0x22222222, 0x33333333 };
		BinaryReader reader(data, sizeof(data));

		reader.Skip(4);
		uint32_t peeked = reader.Peek<uint32_t>();
		CHECK_EQ(peeked, 0x22222222);
		CHECK_EQ(reader.Position(), 4);
	}

	TEST_CASE("Peek<T>() throws on insufficient data")
	{
		uint8_t data[] = { 0x01 };
		BinaryReader reader(data, sizeof(data));

		CHECK_THROWS_AS(reader.Peek<uint32_t>(), std::out_of_range);
	}

	TEST_CASE("Complex reading sequence")
	{
		#pragma pack(1)
		struct ComplexData {
			uint8_t byte_val;
			uint16_t short_val;
			uint32_t int_val;
			uint64_t long_val;
		};
		#pragma pack()

		ComplexData data{ 0x11, 0x2222, 0x33333333, 0x4444444444444444 };

		BinaryReader reader(&data, sizeof(data));

		uint8_t b = reader.Read<uint8_t>();
		uint16_t s = reader.Read<uint16_t>();
		uint32_t i = reader.Read<uint32_t>();
		uint64_t l = reader.Read<uint64_t>();

		CHECK_EQ(b, 0x11);
		CHECK_EQ(s, 0x2222);
		CHECK_EQ(i, 0x33333333);
		CHECK_EQ(l, 0x4444444444444444);
		CHECK(reader.End());
	}
}
