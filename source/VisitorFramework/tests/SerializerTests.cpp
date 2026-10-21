#include <doctest.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

#include "BinaryWriter.h"
#include "DynamicArrayCountRegistry.h"
#include "SerializationFormat.h"
#include "Serializer.h"
#include "TestDataStructs.h"
#include "TypeId.h"


namespace
{
	void AppendTypeId(std::vector<uint32_t>& buffer, uint64_t type_id)
	{
		buffer.push_back(static_cast<uint32_t>(type_id));
		buffer.push_back(static_cast<uint32_t>(type_id >> 32));
	}

	void CheckBufferEquals(const BinaryWriter& writer, const std::vector<uint32_t>& expected_output)
	{
		const auto& buffer = writer.Buffer();

		REQUIRE_EQ(buffer.size(), expected_output.size() * sizeof(uint32_t));
		CHECK_EQ(memcmp(buffer.data(), expected_output.data(), buffer.size()), 0);
	}
}


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
			1, // Object count
			16, // Type table offset
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
			1, // Object count
			36, // Type table offset
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
			1, // Object count
			56, // Type table offset
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
			1, // Object count
			24, // Type table offset
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
			1, // Object count
			20, // Type table offset
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
			2, // Object count
			28, // Type table offset
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

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() serializes TestDataWithDynamicArray correctly")
	{
		const auto type_id1 = TypeId_v<TestDataWithDynamicArray>;

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

		CHECK_EQ(buffer.size(), sizeof(expected_output));
		CHECK_EQ(memcmp(buffer.data(), expected_output, sizeof(expected_output)), 0);
	}

	TEST_CASE("Serialize() throws on null root object")
	{
		SimpleTestData* root = nullptr;

		BinaryWriter writer;
		Serializer serializer(writer);

		CHECK_THROWS_AS(serializer.Serialize(root), std::runtime_error);
	}

	TEST_CASE("Serialize() throws on unregistered type IDs")
	{
		SimpleTestData simple_test_data{ 5 };

		BinaryWriter writer;
		Serializer serializer(writer);

		CHECK_THROWS_AS(serializer.Serialize(&simple_test_data, 0x1234567890ABCDEFull), std::runtime_error);
	}

	TEST_CASE("Serialize() uses the type ID of the root type by default")
	{
		SimpleTestData simple_test_data{ 5 };

		BinaryWriter explicit_writer;
		Serializer(explicit_writer).Serialize(&simple_test_data, TypeId_v<SimpleTestData>);

		BinaryWriter default_writer;
		Serializer(default_writer).Serialize(&simple_test_data);

		CHECK_EQ(explicit_writer.Buffer(), default_writer.Buffer());
	}

	TEST_CASE("Serialize() writes null pointers as object ID 0")
	{
		TestDataWithPointer test_data_with_pointer{ 7, nullptr };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_pointer);

		std::vector<uint32_t> expected_output = {
			'MOO ',
			1, // Object count
			20, // Type table offset
			7, // Object 1 x
			0, // Object 1 simple pointer object ID (nullptr)
		};
		AppendTypeId(expected_output, TypeId_v<TestDataWithPointer>);

		CheckBufferEquals(writer, expected_output);
	}

	TEST_CASE("Serialize() writes objects referenced multiple times only once")
	{
		TestData a{ 42, 43 };
		TestDataWithPointerArray test_data_with_pointer_array{};
		test_data_with_pointer_array.x = 1;
		test_data_with_pointer_array.y[0] = &a;
		test_data_with_pointer_array.y[1] = nullptr;
		test_data_with_pointer_array.y[2] = &a;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_pointer_array);

		std::vector<uint32_t> expected_output = {
			'MOO ',
			2, // Object count
			36, // Type table offset
			1, // Object 1 x
			2, // Object 1 y[0] pointer object ID
			0, // Object 1 y[1] pointer object ID (nullptr)
			2, // Object 1 y[2] pointer object ID
			42, // Object 2 x
			43, // Object 2 y
		};
		AppendTypeId(expected_output, TypeId_v<TestDataWithPointerArray>);
		AppendTypeId(expected_output, TypeId_v<TestData>);

		CheckBufferEquals(writer, expected_output);
	}

	TEST_CASE("Serialize() serializes a pointer to the first member of an object as a separate object")
	{
		TestDataWithInteriorPointer test_data_with_interior_pointer{ { 1, 2 }, nullptr };
		test_data_with_interior_pointer.inner_ptr = &test_data_with_interior_pointer.inner;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_interior_pointer);

		std::vector<uint32_t> expected_output = {
			'MOO ',
			2, // Object count
			32, // Type table offset
			1, // Object 1 inner.x
			2, // Object 1 inner.y
			2, // Object 1 inner_ptr pointer object ID
			1, // Object 2 x
			2, // Object 2 y
		};
		AppendTypeId(expected_output, TypeId_v<TestDataWithInteriorPointer>);
		AppendTypeId(expected_output, TypeId_v<TestData>);

		CheckBufferEquals(writer, expected_output);
	}

	TEST_CASE("Serialize() writes null dynamic arrays as NullArrayCount")
	{
		TestDataWithDynamicArray test_data_with_dynamic_array{};
		test_data_with_dynamic_array.x = nullptr;
		test_data_with_dynamic_array.count = 5;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_dynamic_array);

		std::vector<uint32_t> expected_output = {
			'MOO ',
			1, // Object count
			20, // Type table offset
			SerializationFormat::NullArrayCount, // Object 1 x (nullptr)
			5, // Object 1 count
		};
		AppendTypeId(expected_output, TypeId_v<TestDataWithDynamicArray>);

		CheckBufferEquals(writer, expected_output);
	}

	TEST_CASE("Serialize() writes dynamic arrays with a negative count as empty")
	{
		TestData arr[1] = { { 42, 43 } };
		TestDataWithDynamicArray test_data_with_dynamic_array{};
		test_data_with_dynamic_array.x = arr;
		test_data_with_dynamic_array.count = -1;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data_with_dynamic_array);

		std::vector<uint32_t> expected_output = {
			'MOO ',
			1, // Object count
			20, // Type table offset
			0, // Object 1 x element count
			0xFFFFFFFF, // Object 1 count (-1)
		};
		AppendTypeId(expected_output, TypeId_v<TestDataWithDynamicArray>);

		CheckBufferEquals(writer, expected_output);
	}

	TEST_CASE("Serialize() writes the registered count of dynamic arrays")
	{
		constexpr auto count_key = "TestDataWithExternalCountDynamicArray.flags";

		uint32_t flags[2] = { 10, 11 };
		TestDataWithExternalCountDynamicArray test_data{ 7, flags };

		REGISTER_DYNAMIC_ARRAY_COUNT(count_key, 2);

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data);

		DynamicArrayCountRegistry::Instance().Unregister(count_key);

		std::vector<uint32_t> expected_output = {
			'MOO ',
			1, // Object count
			28, // Type table offset
			7, // Object 1 x
			2, // Object 1 flags element count
			10, // Object 1 flags[0]
			11, // Object 1 flags[1]
		};
		AppendTypeId(expected_output, TypeId_v<TestDataWithExternalCountDynamicArray>);

		CheckBufferEquals(writer, expected_output);
	}

	TEST_CASE("Serialize() does not need a registered count for null dynamic arrays")
	{
		TestDataWithExternalCountDynamicArray test_data{ 7, nullptr };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data);

		std::vector<uint32_t> expected_output = {
			'MOO ',
			1, // Object count
			20, // Type table offset
			7, // Object 1 x
			SerializationFormat::NullArrayCount, // Object 1 flags (nullptr)
		};
		AppendTypeId(expected_output, TypeId_v<TestDataWithExternalCountDynamicArray>);

		CheckBufferEquals(writer, expected_output);
	}

	TEST_CASE("Serialize() serializes enum array elements")
	{
		TestEnum dynamic_values[2] = { TestEnum::Third, TestEnum::First };
		TestDataWithEnumArray test_data{ { TestEnum::First, TestEnum::Second, TestEnum::Third }, dynamic_values, 2 };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&test_data);

		const auto& buffer = writer.Buffer();

		const uint8_t expected_data[] = {
			1, 2, 3, // values
			2, 0, 0, 0, // dynamic_values element count
			3, 1, // dynamic_values
			2, 0, 0, 0, // dynamic_count
		};

		REQUIRE_EQ(buffer.size(), sizeof(SerializationFormat::Header) + sizeof(expected_data) + sizeof(uint64_t));
		CHECK_EQ(memcmp(buffer.data() + sizeof(SerializationFormat::Header), expected_data, sizeof(expected_data)), 0);
	}

	TEST_CASE("Serialize() produces the same output when the Serializer is reused")
	{
		A a{ 10, nullptr };
		B b{ &a, 20 };
		C c{ &b, 30, 40 };
		D d{ &a, &b, 50 };
		E e{ &b, &c, &d, 60 };

		a.e = &e;

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&e);

		const auto first_output = writer.Buffer();

		writer.Clear();

		serializer.Serialize(&e);

		CHECK_EQ(writer.Buffer(), first_output);
	}

	TEST_CASE("Serialize() writes offsets relative to the start of the block")
	{
		SimpleTestData simple_test_data{ 5 };

		BinaryWriter writer;
		writer.Write<uint32_t>(0xDEADBEEF);

		Serializer serializer(writer);

		serializer.Serialize(&simple_test_data);

		std::vector<uint32_t> expected_output = {
			0xDEADBEEF,
			'MOO ',
			1, // Object count
			16, // Type table offset
			5, // Object 1 x
		};
		AppendTypeId(expected_output, TypeId_v<SimpleTestData>);

		CheckBufferEquals(writer, expected_output);
	}
}
