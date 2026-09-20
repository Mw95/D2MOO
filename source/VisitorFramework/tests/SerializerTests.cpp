#include <doctest.h>

#include <cstdint>

#include "BinaryWriter.h"
#include "Serializer.h"
#include "TestDataStructs.h"
#include "TypeId.h"


TEST_SUITE("SerializerTests")
{
	TEST_CASE("Serialize() serializes SimpleTestData correctly")
	{
		const auto type_id = TypeId_v<SimpleTestData>;

		SimpleTestData simple_test_data{ 5 };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&simple_test_data, type_id);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			12, // Object type data position
			5, // Object 1 x
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithPointer correctly")
	{
		const auto type_id1 = TypeId_v<TestDataWithPointer>;
		const auto type_id2 = TypeId_v<SimpleTestData>;

		SimpleTestData simple_test_data{ 5 };
		TestDataWithPointer test_data_with_pointer{ 7, &simple_test_data };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_pointer, type_id1);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			20,// Object type data position
			7, // Object 1 x
			2, // Object 1 simple pointer object ID
			5, // Object 2 x
			((uint32_t*)&type_id1)[0], // Object 1 TypeID
			((uint32_t*)&type_id1)[1], // Object 1 TypeID
			((uint32_t*)&type_id2)[0], // Object 2 TypeID
			((uint32_t*)&type_id2)[1], // Object 2 TypeID
		};

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes E correctly")
	{
		const auto type_id1 = TypeId_v<E>;
		const auto type_id2 = TypeId_v<B>;
		const auto type_id3 = TypeId_v<C>;
		const auto type_id4 = TypeId_v<D>;
		const auto type_id5 = TypeId_v<A>;

		A a{ 10, nullptr };
		B b{ &a, 20 };
		C c{ &b, 30, 40 };
		D d{ &a, &b, 50 };
		E e{ &b, &c, &d, 60 };

		a.e = &e;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&e, type_id1);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			64,// Object type data position

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

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithIntArray correctly")
	{
		const auto type_id = TypeId_v<TestDataWithIntArray>;

		TestDataWithIntArray test_data_with_array{ 7, { 1, 2, 3, 4, 5 } };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_array, type_id);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			32,// Object type data position
			7, // Object 1 x
			1,2,3,4,5, // Object 1 arr
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithObjectArray correctly")
	{
		const auto type_id = TypeId_v<TestDataWithObjectArray>;

		TestDataWithObjectArray test_data_with_object_array{ 7, { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 } } };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_object_array, type_id);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			52,// Object type data position
			7, // Object 1 x
			1,2,2,3,3,4,4,5,5,6, // Object 1 arr
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithObject correctly")
	{
		const auto type_id = TypeId_v<TestDataWithObject>;

		TestDataWithObject test_data_with_object_array{ 7, { 1, 2 } };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_object_array, type_id);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			20,// Object type data position
			7, // Object 1 x
			1,2, // Object 1 y
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithUnion correctly - 1")
	{
		const auto type_id = TypeId_v<TestDataWithUnion>;

		TestDataWithUnion test_data_with_union{};
		test_data_with_union.x = 0;
		test_data_with_union.y = 11;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_union, type_id);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			16,// Object type data position
			0, // Object 1 x
			11, // Object 1 y
			((uint32_t*)&type_id)[0], // Object 1 TypeID
			((uint32_t*)&type_id)[1], // Object 1 TypeID
		};

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithUnion correctly - 2")
	{
		const auto type_id1 = TypeId_v<TestDataWithUnion>;
		const auto type_id2 = TypeId_v<TestData>;

		TestData z{ 42, 43 };
		TestDataWithUnion test_data_with_union{};
		test_data_with_union.x = 1;
		test_data_with_union.z = &z;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_union, type_id1);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			24,// Object type data position
			1, // Object 1 x
			2, // Object 1 z pointer object ID
			42, // Object 2 x
			43, // Object 2 y
			((uint32_t*)&type_id1)[0], // Object 1 TypeID
			((uint32_t*)&type_id1)[1], // Object 1 TypeID
			((uint32_t*)&type_id2)[0], // Object 2 TypeID
			((uint32_t*)&type_id2)[1], // Object 2 TypeID
		};

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithPointerArray correctly")
	{
		const auto type_id1 = TypeId_v<TestDataWithPointerArray>;
		const auto type_id2 = TypeId_v<TestData>;

		TestData a{ 42, 43 };
		TestData b{ 44, 45 };
		TestData c{ 46, 47 };
		TestDataWithPointerArray test_data_with_pointer_array{};
		test_data_with_pointer_array.x = 1;
		test_data_with_pointer_array.y[0] = &a;
		test_data_with_pointer_array.y[1] = &b;
		test_data_with_pointer_array.y[2] = &c;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_pointer_array, type_id1);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			48,// Object type data position
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

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithDynamicArray correctly")
	{
		const auto type_id1 = TypeId_v<TestDataWithDynamicArray>;
		const auto type_id2 = TypeId_v<TestData>;

		TestData arr[3] = { { 42, 43 }, { 44, 45 }, { 46, 47 } };
		TestDataWithDynamicArray test_data_with_dynamic_array{};
		test_data_with_dynamic_array.x = arr;
		test_data_with_dynamic_array.count = 3;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_dynamic_array, type_id1);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			36, // Object type data position
			42, // Object 2 x
			43, // Object 2 y
			44,
			45,
			46,
			47,
			3, // Object 1 count
			((uint32_t*)&type_id1)[0], // Object 1 TypeID
			((uint32_t*)&type_id1)[1], // Object 1 TypeID
		};

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWith2DArray correctly")
	{
		const auto type_id = TypeId_v<TestDataWith2DArray>;

		TestDataWith2DArray test_data_with_2d_array{ 42, { { 1, 2, 3 }, { 4, 5, 6 } } };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_2d_array, type_id);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			36,// Object type data position
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

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWith3DArray correctly")
	{
		const auto type_id = TypeId_v<TestDataWith3DArray>;

		TestDataWith3DArray test_data_with_3d_array{ 42, { { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }, { { 13, 14, 15, 16 }, { 17, 18, 19, 20 }, { 21, 22, 23, 24 } } } };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_3d_array, type_id);

		const auto& buffer = writer.Buffer();

		const uint32_t expected_output[] = {
			'MOO ',
			108,// Object type data position
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

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}
}
