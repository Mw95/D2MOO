#include <doctest.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

#include "BinaryReader.h"
#include "Deserializer.h"
#include "SerializationFormat.h"
#include "TestDataStructs.h"


namespace
{
	void AppendTypeId(std::vector<uint32_t>& buffer, uint64_t type_id)
	{
		buffer.push_back(static_cast<uint32_t>(type_id));
		buffer.push_back(static_cast<uint32_t>(type_id >> 32));
	}

	template<typename T>
	void CheckDeserializeThrows(const std::vector<uint32_t>& buffer)
	{
		BinaryReader reader(buffer.data(), buffer.size() * sizeof(uint32_t));
		Deserializer deserializer(reader);

		CHECK_THROWS(deserializer.Deserialize<T>());
	}
}


TEST_SUITE("DeserializerTests")
{
	TEST_CASE("Deserialize() deserializes SimpleTestData correctly")
	{
		const auto type_id = TypeId_v<SimpleTestData>;

		const uint32_t buffer[] = {
			'MOO ',
			1, // Object count
			16, // Type table offset
			5, // Object 1 x
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		BinaryReader reader(buffer, sizeof(buffer));
		Deserializer deserializer(reader);

		const auto simple_test_data = deserializer.Deserialize<SimpleTestData>();

		SimpleTestData expected_output{ 5 };

		CHECK_EQ(memcmp(simple_test_data, &expected_output, sizeof(SimpleTestData)), 0);
	}

	TEST_CASE("Deserialize() deserializes TestDataWithPointer correctly")
	{
		const auto type_id1 = TypeId_v<TestDataWithPointer>;
		const auto type_id2 = TypeId_v<SimpleTestData>;

		const uint32_t buffer[] = {
			'MOO ',
			2, // Object count
			24, // Type table offset
			7, // Object 1 x
			2, // Object 1 simple pointer object ID
			5, // Object 2 x
			((uint32_t*)&type_id1)[0], // Object 1 TypeID
			((uint32_t*)&type_id1)[1], // Object 1 TypeID
			((uint32_t*)&type_id2)[0], // Object 2 TypeID
			((uint32_t*)&type_id2)[1], // Object 2 TypeID
		};

		SimpleTestData simple_test_data{ 5 };
		TestDataWithPointer expected_output{ 7, &simple_test_data };

		BinaryReader reader(buffer, sizeof(buffer));
		Deserializer deserializer(reader);

		const auto test_data_with_pointer = deserializer.Deserialize<TestDataWithPointer>();

		CHECK_EQ(simple_test_data.x, test_data_with_pointer->simple->x);
		CHECK_EQ(expected_output.x, test_data_with_pointer->x);
	}

	TEST_CASE("Deserialize() deserializes E correctly")
	{
		const auto type_id1 = TypeId_v<E>;
		const auto type_id2 = TypeId_v<B>;
		const auto type_id3 = TypeId_v<C>;
		const auto type_id4 = TypeId_v<D>;
		const auto type_id5 = TypeId_v<A>;

		const uint32_t buffer[] = {
			'MOO ',
			5, // Object count
			68, // Type table offset

			2, // Object 1 b pointer object ID
			3, // Object 1 c pointer object ID
			4, // Object 1 d pointer object ID
			60, // Object 1 e

			5, // Object 2 a pointer object ID
			20, // Object 2 b

			2, // Object 3 b pointer object ID
			30, // Object 3 c
			40, // Object 3 d

			5, // Object 4 a pointer object ID
			2, // Object 4 b pointer object ID
			50, // Object 4 d

			10, // Object 5 a
			1, // Object 5 e pointer object ID

			((uint32_t*)&type_id1)[0], // Object 1 (e) TypeID
			((uint32_t*)&type_id1)[1], // Object 1 (e) TypeID
			((uint32_t*)&type_id2)[0], // Object 2 (b) TypeID
			((uint32_t*)&type_id2)[1], // Object 2 (b) TypeID
			((uint32_t*)&type_id3)[0], // Object 3 (c) TypeID
			((uint32_t*)&type_id3)[1], // Object 3 (c) TypeID
			((uint32_t*)&type_id4)[0], // Object 4 (d) TypeID
			((uint32_t*)&type_id4)[1], // Object 4 (d) TypeID
			((uint32_t*)&type_id5)[0], // Object 5 (a) TypeID
			((uint32_t*)&type_id5)[1], // Object 5 (a) TypeID
		};

		A a{ 10, nullptr };
		B b{ &a, 20 };
		C c{ &b, 30, 40 };
		D d{ &a, &b, 50 };
		E e{ &b, &c, &d, 60 };

		a.e = &e;

		BinaryReader reader(buffer, sizeof(buffer));
		Deserializer deserializer(reader);

		const auto deserialized_e = deserializer.Deserialize<E>();

		CHECK_EQ(e.b->a->a, deserialized_e->b->a->a);
		CHECK_EQ(e.b->b, deserialized_e->b->b);
		CHECK_EQ(e.c->b->b, deserialized_e->c->b->b);
		CHECK_EQ(e.c->c, deserialized_e->c->c);
		CHECK_EQ(e.c->d, deserialized_e->c->d);
		CHECK_EQ(e.d->a->a, deserialized_e->d->a->a);
		CHECK_EQ(e.d->b->a->a, deserialized_e->d->b->a->a);
		CHECK_EQ(e.d->b->b, deserialized_e->d->b->b);
		CHECK_EQ(e.d->d, deserialized_e->d->d);
		CHECK_EQ(e.e, deserialized_e->e);

		CHECK_EQ(deserialized_e->b->a->e, deserialized_e);
	}

	TEST_CASE("Deserialize() deserializes TestDataWithPointerArray correctly")
	{
		const auto type_id1 = TypeId_v<TestDataWithPointerArray>;
		const auto type_id2 = TypeId_v<TestData>;

		const uint32_t buffer[] = {
			'MOO ',
			4, // Object count
			52, // Type table offset
			1, // Object 1 x
			2, // Object 1 z pointer object ID
			3,
			4,
			42, // Object 2 x
			43, // Object 2 y
			44,
			45,
			46,
			47,
			((uint32_t*)&type_id1)[0], // Object 1 TypeID
			((uint32_t*)&type_id1)[1], // Object 1 TypeID
			((uint32_t*)&type_id2)[0], // Object 2 TypeID
			((uint32_t*)&type_id2)[1], // Object 2 TypeID
			((uint32_t*)&type_id2)[0], // Object 2 TypeID
			((uint32_t*)&type_id2)[1], // Object 2 TypeID
			((uint32_t*)&type_id2)[0], // Object 2 TypeID
			((uint32_t*)&type_id2)[1], // Object 2 TypeID
		};

		BinaryReader reader(buffer, sizeof(buffer));
		Deserializer deserializer(reader);

		const auto deserialized_test_data_with_pointer_array = deserializer.Deserialize<TestDataWithPointerArray>();

		TestData a{ 42, 43 };
		TestData b{ 44, 45 };
		TestData c{ 46, 47 };
		TestDataWithPointerArray test_data_with_pointer_array{};
		test_data_with_pointer_array.x = 1;
		test_data_with_pointer_array.y[0] = &a;
		test_data_with_pointer_array.y[1] = &b;
		test_data_with_pointer_array.y[2] = &c;

		CHECK_EQ(deserialized_test_data_with_pointer_array->x, test_data_with_pointer_array.x);
		CHECK_EQ(deserialized_test_data_with_pointer_array->y[0]->x, test_data_with_pointer_array.y[0]->x);
		CHECK_EQ(deserialized_test_data_with_pointer_array->y[0]->y, test_data_with_pointer_array.y[0]->y);
		CHECK_EQ(deserialized_test_data_with_pointer_array->y[1]->x, test_data_with_pointer_array.y[1]->x);
		CHECK_EQ(deserialized_test_data_with_pointer_array->y[1]->y, test_data_with_pointer_array.y[1]->y);
		CHECK_EQ(deserialized_test_data_with_pointer_array->y[2]->x, test_data_with_pointer_array.y[2]->x);
		CHECK_EQ(deserialized_test_data_with_pointer_array->y[2]->y, test_data_with_pointer_array.y[2]->y);
	}

	TEST_CASE("Deserialize() deserializes TestDataWithDynamicArray correctly")
	{
		const auto type_id = TypeId_v<TestDataWithDynamicArray>;

		const uint32_t buffer[] = {
			'MOO ',
			1, // Object count
			44, // Type table offset
			3, // Object 1 x element count
			42, // Object 1 x[0].x
			43, // Object 1 x[0].y
			44,
			45,
			46,
			47,
			3, // Object 1 count
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		BinaryReader reader(buffer, sizeof(buffer));
		Deserializer deserializer(reader);

		const auto deserialized_test_data_with_dynamic_array = deserializer.Deserialize<TestDataWithDynamicArray>();

		TestData arr[3] = { { 42, 43 }, { 44, 45 }, { 46, 47 } };
		TestDataWithDynamicArray test_data_with_dynamic_array{};
		test_data_with_dynamic_array.x = arr;
		test_data_with_dynamic_array.count = 3;

		std::string diff_description;
		using Comparator = TestComparator<decltype(test_data_with_dynamic_array)>;
		const auto are_objects_equal = Comparator::compare(test_data_with_dynamic_array, *deserialized_test_data_with_dynamic_array, "test_data_with_dynamic_array", diff_description);
		CHECK_MESSAGE(are_objects_equal, diff_description);
	}

	TEST_CASE("Deserialize() deserializes TestDataWith2DArray correctly")
	{
		const auto type_id = TypeId_v<TestDataWith2DArray>;

		const uint32_t buffer[] = {
			'MOO ',
			1, // Object count
			40, // Type table offset
			42,
			1, // Object 1 x
			2, // Object 1 z pointer object ID
			3, // Object 2 x
			4, // Object 2 y
			5,
			6,
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		BinaryReader reader(buffer, sizeof(buffer));
		Deserializer deserializer(reader);

		const auto deserialized_test_data_with_2d_array = deserializer.Deserialize<TestDataWith2DArray>();

		TestDataWith2DArray test_data_with_2d_array{ 42, { { 1, 2, 3 }, { 4, 5, 6 } } };

		std::string diff_description;
		using Comparator = TestComparator<decltype(test_data_with_2d_array)>;
		const auto are_objects_equal = Comparator::compare(test_data_with_2d_array, *deserialized_test_data_with_2d_array, "test_data_with_2d_array", diff_description);
		CHECK_MESSAGE(are_objects_equal, diff_description);
	}

	TEST_CASE("Deserialize() deserializes TestDataWith3DArray correctly")
	{
		const auto type_id = TypeId_v<TestDataWith3DArray>;

		const uint32_t buffer[] = {
			'MOO ',
			1, // Object count
			112, // Type table offset
			42,
			1, // Object 1 x
			2, // Object 1 z pointer object ID
			3, // Object 2 x
			4, // Object 2 y
			5,
			6,
			7,
			8,
			9,
			10,
			11,
			12,
			13,
			14,
			15,
			16,
			17,
			18,
			19,
			20,
			21,
			22,
			23,
			24,
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		BinaryReader reader(buffer, sizeof(buffer));
		Deserializer deserializer(reader);

		const auto deserialized_test_data_with_3d_array = deserializer.Deserialize<TestDataWith3DArray>();

		TestDataWith3DArray test_data_with_3d_array{ 42, { { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }, { { 13, 14, 15, 16 }, { 17, 18, 19, 20 }, { 21, 22, 23, 24 } } } };

		std::string diff_description;
		using Comparator = TestComparator<decltype(test_data_with_3d_array)>;
		const auto are_objects_equal = Comparator::compare(test_data_with_3d_array, *deserialized_test_data_with_3d_array, "test_data_with_3d_array", diff_description);
		CHECK_MESSAGE(are_objects_equal, diff_description);
	}

	TEST_CASE("Deserialize() deserializes null pointers")
	{
		std::vector<uint32_t> buffer = {
			'MOO ',
			1, // Object count
			20, // Type table offset
			7, // Object 1 x
			0, // Object 1 simple pointer object ID (nullptr)
		};
		AppendTypeId(buffer, TypeId_v<TestDataWithPointer>);

		BinaryReader reader(buffer.data(), buffer.size() * sizeof(uint32_t));
		Deserializer deserializer(reader);

		const auto deserialized = deserializer.Deserialize<TestDataWithPointer>();

		CHECK_EQ(deserialized->x, 7);
		CHECK_EQ(deserialized->simple, nullptr);
	}

	TEST_CASE("Deserialize() deserializes null dynamic arrays and keeps their count member")
	{
		std::vector<uint32_t> buffer = {
			'MOO ',
			1, // Object count
			20, // Type table offset
			SerializationFormat::NullArrayCount, // Object 1 x (nullptr)
			5, // Object 1 count
		};
		AppendTypeId(buffer, TypeId_v<TestDataWithDynamicArray>);

		BinaryReader reader(buffer.data(), buffer.size() * sizeof(uint32_t));
		Deserializer deserializer(reader);

		const auto deserialized = deserializer.Deserialize<TestDataWithDynamicArray>();

		CHECK_EQ(deserialized->x, nullptr);
		CHECK_EQ(deserialized->count, 5);
	}

	TEST_CASE("Deserialize() zero-initializes fields which are not visited")
	{
		std::vector<uint32_t> buffer = {
			'MOO ',
			1, // Object count
			16, // Type table offset
			7, // Object 1 x
		};
		AppendTypeId(buffer, TypeId_v<TestDataWithOmittedField>);

		BinaryReader reader(buffer.data(), buffer.size() * sizeof(uint32_t));
		Deserializer deserializer(reader);

		const auto deserialized = deserializer.Deserialize<TestDataWithOmittedField>();

		CHECK_EQ(deserialized->x, 7);
		CHECK_EQ(deserialized->omitted, 0);
	}

	TEST_CASE("Deserialize() reads a block embedded in a larger buffer and stops after it")
	{
		std::vector<uint32_t> buffer = {
			0xDEADBEEF, // Unrelated data before the block
			'MOO ',
			1, // Object count
			16, // Type table offset (relative to the block)
			5, // Object 1 x
		};
		AppendTypeId(buffer, TypeId_v<SimpleTestData>);
		buffer.push_back(0xCAFEBABE); // Unrelated data after the block

		BinaryReader reader(buffer.data(), buffer.size() * sizeof(uint32_t));
		reader.Skip(sizeof(uint32_t));

		Deserializer deserializer(reader);

		const auto deserialized = deserializer.Deserialize<SimpleTestData>();

		CHECK_EQ(deserialized->x, 5);
		CHECK_EQ(reader.Read<uint32_t>(), 0xCAFEBABE);
		CHECK(reader.End());
	}

	TEST_CASE("Deserialize() can be called repeatedly and keeps earlier results alive")
	{
		std::vector<uint32_t> buffer;

		for (const uint32_t x : { 5u, 6u })
		{
			buffer.insert(buffer.end(), { 'MOO ', 1, 16, x });
			AppendTypeId(buffer, TypeId_v<SimpleTestData>);
		}

		BinaryReader reader(buffer.data(), buffer.size() * sizeof(uint32_t));
		Deserializer deserializer(reader);

		const auto first = deserializer.Deserialize<SimpleTestData>();
		const auto second = deserializer.Deserialize<SimpleTestData>();

		CHECK_NE(first, second);
		CHECK_EQ(first->x, 5);
		CHECK_EQ(second->x, 6);
	}

	TEST_CASE("Deserialize() throws on invalid magic")
	{
		std::vector<uint32_t> buffer = { 'BAD ', 1, 16, 5 };
		AppendTypeId(buffer, TypeId_v<SimpleTestData>);

		CheckDeserializeThrows<SimpleTestData>(buffer);
	}

	TEST_CASE("Deserialize() throws on truncated header")
	{
		CheckDeserializeThrows<SimpleTestData>({ 'MOO ', 1 });
	}

	TEST_CASE("Deserialize() throws on empty input")
	{
		CheckDeserializeThrows<SimpleTestData>({});
	}

	TEST_CASE("Deserialize() throws when there are no objects")
	{
		CheckDeserializeThrows<SimpleTestData>({ 'MOO ', 0, 12 });
	}

	TEST_CASE("Deserialize() throws when the type table offset is out of bounds")
	{
		SUBCASE("Offset inside the header")
		{
			std::vector<uint32_t> buffer = { 'MOO ', 1, 4, 5 };
			AppendTypeId(buffer, TypeId_v<SimpleTestData>);

			CheckDeserializeThrows<SimpleTestData>(buffer);
		}

		SUBCASE("Offset past the end")
		{
			std::vector<uint32_t> buffer = { 'MOO ', 1, 1000, 5 };
			AppendTypeId(buffer, TypeId_v<SimpleTestData>);

			CheckDeserializeThrows<SimpleTestData>(buffer);
		}

		SUBCASE("Type table shorter than the object count")
		{
			std::vector<uint32_t> buffer = { 'MOO ', 2, 16, 5 };
			AppendTypeId(buffer, TypeId_v<SimpleTestData>);

			CheckDeserializeThrows<SimpleTestData>(buffer);
		}

		SUBCASE("Huge object count")
		{
			std::vector<uint32_t> buffer = { 'MOO ', 0xFFFFFFFF, 16, 5 };
			AppendTypeId(buffer, TypeId_v<SimpleTestData>);

			CheckDeserializeThrows<SimpleTestData>(buffer);
		}
	}

	TEST_CASE("Deserialize() throws on unknown type IDs")
	{
		std::vector<uint32_t> buffer = { 'MOO ', 1, 16, 5 };
		AppendTypeId(buffer, 0x1234567890ABCDEFull);

		CheckDeserializeThrows<SimpleTestData>(buffer);
	}

	TEST_CASE("Deserialize() throws when the root object has a different type than requested")
	{
		std::vector<uint32_t> buffer = { 'MOO ', 1, 16, 5 };
		AppendTypeId(buffer, TypeId_v<SimpleTestData>);

		CheckDeserializeThrows<TestData>(buffer);
	}

	TEST_CASE("Deserialize() throws on pointers to unknown object IDs")
	{
		std::vector<uint32_t> buffer = {
			'MOO ',
			2, // Object count
			24, // Type table offset
			7, // Object 1 x
			3, // Object 1 simple pointer object ID (does not exist)
			5, // Object 2 x
		};
		AppendTypeId(buffer, TypeId_v<TestDataWithPointer>);
		AppendTypeId(buffer, TypeId_v<SimpleTestData>);

		CheckDeserializeThrows<TestDataWithPointer>(buffer);
	}

	TEST_CASE("Deserialize() throws on pointers to objects of a different type")
	{
		std::vector<uint32_t> buffer = {
			'MOO ',
			2, // Object count
			28, // Type table offset
			7, // Object 1 x
			2, // Object 1 simple pointer object ID (a TestData instead of a SimpleTestData)
			5, // Object 2 x
			6, // Object 2 y
		};
		AppendTypeId(buffer, TypeId_v<TestDataWithPointer>);
		AppendTypeId(buffer, TypeId_v<TestData>);

		CheckDeserializeThrows<TestDataWithPointer>(buffer);
	}

	TEST_CASE("Deserialize() throws when the object data does not match the object types")
	{
		SUBCASE("Object data too long")
		{
			std::vector<uint32_t> buffer = { 'MOO ', 1, 20, 5, 6 };
			AppendTypeId(buffer, TypeId_v<SimpleTestData>);

			CheckDeserializeThrows<SimpleTestData>(buffer);
		}

		SUBCASE("Object data too short")
		{
			std::vector<uint32_t> buffer = { 'MOO ', 1, 16, 5 };
			AppendTypeId(buffer, TypeId_v<TestData>);

			CheckDeserializeThrows<TestData>(buffer);
		}

		SUBCASE("Object data truncated at the end of the buffer")
		{
			std::vector<uint32_t> buffer = { 'MOO ', 1, 12 };
			AppendTypeId(buffer, TypeId_v<TestDataWithIntArray>);

			CheckDeserializeThrows<TestDataWithIntArray>(buffer);
		}
	}

	TEST_CASE("Deserialize() throws when a dynamic array count exceeds the serialized data")
	{
		std::vector<uint32_t> buffer = {
			'MOO ',
			1, // Object count
			24, // Type table offset
			0xFFFFFFFE, // Object 1 x element count
			42, // Object 1 x[0].x
			43, // Object 1 x[0].y
		};
		AppendTypeId(buffer, TypeId_v<TestDataWithDynamicArray>);

		CheckDeserializeThrows<TestDataWithDynamicArray>(buffer);
	}
}
