#include <doctest.h>

#include <cstdint>

#include "BinaryReader.h"
#include "Deserializer.h"
#include "TestDataStructs.h"


TEST_SUITE("DeserializerTests")
{
	TEST_CASE("Deserialize() deserializes SimpleTestData correctly")
	{
		const auto type_id = TypeId_v<SimpleTestData>;

		const uint32_t buffer[] = {
			'MOO ',
			12, // Object type data position
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
			20,// Object type data position
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

	//TEST_CASE("Deserialize() deserializes TestDataWithDynamicArray correctly")
	//{
	//	const auto type_id1 = TypeId_v<TestDataWithDynamicArray>;
	//	const auto type_id2 = TypeId_v<TestData>;

	//	std::cout << "----------------------------------------" << std::endl;
	//	std::cout << "TypeID of TestDataWithDynamicArray: " << type_id1 << std::endl;
	//	std::cout << "TypeID of TestData: " << type_id2 << std::endl;

	//	const uint32_t buffer[] = {
	//		'MOO ',
	//		36, // Object type data position
	//		42, // Object 2 x
	//		43, // Object 2 y
	//		44,
	//		45,
	//		46,
	//		47,
	//		3, // Object 1 count
	//		((uint32_t*)&type_id1)[0], // Object 1 TypeID
	//		((uint32_t*)&type_id1)[1], // Object 1 TypeID
	//		((uint32_t*)&type_id2)[0], // Object 2 TypeID
	//		((uint32_t*)&type_id2)[1], // Object 2 TypeID
	//		((uint32_t*)&type_id2)[0], // Object 3 TypeID
	//		((uint32_t*)&type_id2)[1], // Object 3 TypeID
	//		((uint32_t*)&type_id2)[0], // Object 4 TypeID
	//		((uint32_t*)&type_id2)[1], // Object 4 TypeID
	//	};

	//	BinaryReader reader(buffer, sizeof(buffer));
	//	Deserializer deserializer(reader);

	//	const auto deserialized_test_data_with_dynamic_array = deserializer.Deserialize<TestDataWithDynamicArray>();

	//	TestData arr[3] = { { 42, 43 }, { 44, 45 }, { 46, 47 } };
	//	TestDataWithDynamicArray test_data_with_dynamic_array{};
	//	test_data_with_dynamic_array.x = arr;
	//	test_data_with_dynamic_array.count = 3;

	//	std::string diff_description;
	//	using Comparator = TestComparator<decltype(test_data_with_dynamic_array)>;
	//	const auto are_objects_equal = Comparator::compare(test_data_with_dynamic_array, *deserialized_test_data_with_dynamic_array, "test_data_with_dynamic_array", diff_description);
	//	CHECK_MESSAGE(are_objects_equal, diff_description);
	//}

	TEST_CASE("Deserialize() deserializes TestDataWith2DArray correctly")
	{
		const auto type_id = TypeId_v<TestDataWith2DArray>;

		const uint32_t buffer[] = {
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

		BinaryReader reader(buffer, sizeof(buffer));
		Deserializer deserializer(reader);

		const auto deserialized_test_data_with_3d_array = deserializer.Deserialize<TestDataWith3DArray>();

		TestDataWith3DArray test_data_with_3d_array{ 42, { { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }, { { 13, 14, 15, 16 }, { 17, 18, 19, 20 }, { 21, 22, 23, 24 } } } };

		std::string diff_description;
		using Comparator = TestComparator<decltype(test_data_with_3d_array)>;
		const auto are_objects_equal = Comparator::compare(test_data_with_3d_array, *deserialized_test_data_with_3d_array, "test_data_with_3d_array", diff_description);
		CHECK_MESSAGE(are_objects_equal, diff_description);
	}
}
