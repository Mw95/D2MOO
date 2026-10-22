#include <doctest.h>

#include <cstdint>
#include <limits>

#include "DiffVisitor.h"
#include "TestDataStructs.h"


TEST_SUITE("DiffVisitorTests")
{
	TEST_CASE("CompareWith() compares SimpleTestData correctly")
	{
		SimpleTestData simple_test_data1{ 5 };
		SimpleTestData simple_test_data2{ 6 };

		DiffContext context("Comparing SimpleTestData");
		DiffVisitor<SimpleTestData> diff_visitor(simple_test_data1, context);
		diff_visitor.CompareWith(simple_test_data2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"x",
				"5",
				"6"
			}
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithPointer correctly - 1")
	{
		SimpleTestData simple_test_data1{ 5 };
		SimpleTestData simple_test_data2{ 6 };

		TestDataWithPointer test_data1{ 10, &simple_test_data1 };
		TestDataWithPointer test_data2{ 10, &simple_test_data2 };

		DiffContext context("Comparing TestDataWithPointer");
		DiffVisitor<TestDataWithPointer> diff_visitor(test_data1, context);
		diff_visitor.CompareWith(test_data2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"simple->x",
				"5",
				"6"
			}
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithPointer correctly - 2")
	{
		SimpleTestData simple_test_data1{ 5 };

		TestDataWithPointer test_data1{ 10, &simple_test_data1 };
		TestDataWithPointer test_data2{ 10, nullptr };

		DiffContext context("Comparing TestDataWithPointer");
		DiffVisitor<TestDataWithPointer> diff_visitor(test_data1, context);
		diff_visitor.CompareWith(test_data2);

		std::stringstream formatted_ptr;
		formatted_ptr << std::hex << "0x" << reinterpret_cast<uintptr_t>(test_data1.simple);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Pointer,
				"simple",
				formatted_ptr.str(),
				"0x0"
			}
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithPointer correctly - 3")
	{
		SimpleTestData simple_test_data1{ 5 };
		SimpleTestData simple_test_data2{ 6 };

		TestDataWithPointer test_data1{ 10, &simple_test_data1 };
		TestDataWithPointer test_data2{ 11, &simple_test_data2 };

		DiffContext context("Comparing TestDataWithPointer");
		DiffVisitor<TestDataWithPointer> diff_visitor(test_data1, context);
		diff_visitor.CompareWith(test_data2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"x",
				"10",
				"11"
			},
			{
				DifferenceType::Field,
				"simple->x",
				"5",
				"6"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithObject correctly - 1")
	{
		TestDataWithObject test_data1{ 10, { 5, 6 } };
		TestDataWithObject test_data2{ 11, { 6, 7 } };

		DiffContext context("Comparing TestDataWithObject");
		DiffVisitor<TestDataWithObject> diff_visitor(test_data1, context);
		diff_visitor.CompareWith(test_data2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"x",
				"10",
				"11"
			},
			{
				DifferenceType::Field,
				"y->x",
				"5",
				"6"
			},
			{
				DifferenceType::Field,
				"y->y",
				"6",
				"7"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares E correctly")
	{
		A a1{ 10, nullptr };
		B b1{ &a1, 20 };
		C c1{ &b1, 30, 40 };
		D d1{ &a1, &b1, 50 };
		E e1{ &b1, &c1, &d1, 60 };

		a1.e = &e1;

		A a2{ 10, nullptr };
		B b2{ &a2, 20 };
		C c2{ &b2, 30, 50 };
		D d2{ &a2, &b2, 50 };
		E e2{ &b2, &c2, &d2, 70 };

		a2.e = &e2;

		DiffContext context("Comparing E");
		DiffVisitor<E> diff_visitor(e1, context, "e");
		diff_visitor.CompareWith(e2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"e->e",
				"60",
				"70"
			},
			{
				DifferenceType::Field,
				"e->c->d",
				"40",
				"50"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithIntArray correctly")
	{
		TestDataWithIntArray test_data_with_int_array1{ 1, { 2, 3, 4, 5, 6 } };
		TestDataWithIntArray test_data_with_int_array2{ 1, { 2, 3, 4, 4, 7 } };

		DiffContext context("Comparing TestDataWithIntArray");
		DiffVisitor<TestDataWithIntArray> diff_visitor(test_data_with_int_array1, context, "test_data_with_int_array");
		diff_visitor.CompareWith(test_data_with_int_array2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"test_data_with_int_array->arr[3]",
				"5",
				"4"
			},
			{
				DifferenceType::Field,
				"test_data_with_int_array->arr[4]",
				"6",
				"7"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithPointerArray correctly - 1")
	{
		TestData d1{};
		TestData d2{};
		TestData d3{};
		TestDataWithPointerArray test_data_with_pointer_array1{ 1, { &d1, &d2, &d3 } };
		TestDataWithPointerArray test_data_with_pointer_array2{ 1, { &d1, &d2, nullptr } };

		DiffContext context("Comparing TestDataWithPointerArray");
		DiffVisitor<TestDataWithPointerArray> diff_visitor(test_data_with_pointer_array1, context, "test_data_with_pointer_array");
		diff_visitor.CompareWith(test_data_with_pointer_array2);

		std::stringstream formatted_ptr;
		formatted_ptr << std::hex << "0x" << reinterpret_cast<uintptr_t>(&d3);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Pointer,
				"test_data_with_pointer_array->y[2]",
				formatted_ptr.str(),
				"0x0"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithPointerArray correctly - 2")
	{
		TestData d1{};
		TestData d2{};
		TestData d3{ 1, 2 };
		TestData d4{ 3, 4 };
		TestDataWithPointerArray test_data_with_pointer_array1{ 1, { &d1, &d2, &d3 } };
		TestDataWithPointerArray test_data_with_pointer_array2{ 1, { &d1, &d2, &d4 } };

		DiffContext context("Comparing TestDataWithPointerArray");
		DiffVisitor<TestDataWithPointerArray> diff_visitor(test_data_with_pointer_array1, context, "test_data_with_pointer_array");
		diff_visitor.CompareWith(test_data_with_pointer_array2);

		std::stringstream formatted_ptr;
		formatted_ptr << std::hex << "0x" << reinterpret_cast<uintptr_t>(&d3);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"test_data_with_pointer_array->y[2]->x",
				"1",
				"3"
			},
			{
				DifferenceType::Field,
				"test_data_with_pointer_array->y[2]->y",
				"2",
				"4"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithObjectArray correctly")
	{
		TestDataWithObjectArray test_data_with_object_array1{ 7, { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 } } };
		TestDataWithObjectArray test_data_with_object_array2{ 7, { { 1, 2 }, { 2, 3 }, { 4, 4 }, { 4, 5 }, { 5, 7 } } };

		DiffContext context("Comparing TestDataWithObjectArray");
		DiffVisitor<TestDataWithObjectArray> diff_visitor(test_data_with_object_array1, context, "test_data_with_object_array");
		diff_visitor.CompareWith(test_data_with_object_array2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"test_data_with_object_array->arr[2]->x",
				"3",
				"4"
			},
			{
				DifferenceType::Field,
				"test_data_with_object_array->arr[4]->y",
				"6",
				"7"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWithDynamicArray correctly")
	{
		TestData d1[5]{};
		TestData d2[5]{};

		d2[0].x = 1;
		d2[2].y = 2;

		TestDataWithDynamicArray test_data_with_dynamic_array1{ d1, 5 };
		TestDataWithDynamicArray test_data_with_dynamic_array2{ d2, 5 };

		DiffContext context("Comparing TestDataWithDynamicArray");
		DiffVisitor<TestDataWithDynamicArray> diff_visitor(test_data_with_dynamic_array1, context, "test_data_with_dynamic_array");
		diff_visitor.CompareWith(test_data_with_dynamic_array2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"test_data_with_dynamic_array->x[0]->x",
				"0",
				"1"
			},
			{
				DifferenceType::Field,
				"test_data_with_dynamic_array->x[2]->y",
				"0",
				"2"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() reports a difference when only one dynamic array is null")
	{
		TestData d2[2]{};

		TestDataWithDynamicArray test_data_with_dynamic_array1{ nullptr, 2 };
		TestDataWithDynamicArray test_data_with_dynamic_array2{ d2, 2 };

		DiffContext context("Comparing TestDataWithDynamicArray");
		DiffVisitor<TestDataWithDynamicArray> diff_visitor(test_data_with_dynamic_array1, context, "test_data_with_dynamic_array");
		diff_visitor.CompareWith(test_data_with_dynamic_array2);

		std::stringstream formatted_ptr;
		formatted_ptr << std::hex << "0x" << reinterpret_cast<uintptr_t>(&d2[0]);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Pointer,
				"test_data_with_dynamic_array->x",
				"0x0",
				formatted_ptr.str()
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() ignores the count of null dynamic arrays")
	{
		TestDataWithDynamicArray test_data_with_dynamic_array1{ nullptr, 3 };
		TestDataWithDynamicArray test_data_with_dynamic_array2{ nullptr, 3 };

		DiffContext context("Comparing TestDataWithDynamicArray");
		DiffVisitor<TestDataWithDynamicArray> diff_visitor(test_data_with_dynamic_array1, context, "test_data_with_dynamic_array");
		diff_visitor.CompareWith(test_data_with_dynamic_array2);

		CHECK(context.differences.empty());
	}

	TEST_CASE("CompareWith() compares only the common elements of dynamic arrays with different counts")
	{
		SUBCASE("First array is shorter")
		{
			TestData d1[1]{ { 1, 2 } };
			TestData d2[3]{ { 1, 3 }, { 4, 5 }, { 6, 7 } };

			TestDataWithDynamicArray test_data_with_dynamic_array1{ d1, 1 };
			TestDataWithDynamicArray test_data_with_dynamic_array2{ d2, 3 };

			DiffContext context("Comparing TestDataWithDynamicArray");
			DiffVisitor<TestDataWithDynamicArray> diff_visitor(test_data_with_dynamic_array1, context, "test_data_with_dynamic_array");
			diff_visitor.CompareWith(test_data_with_dynamic_array2);

			const auto expected_output = std::vector<DifferenceDescriptor>{
				{
					DifferenceType::Field,
					"test_data_with_dynamic_array->x",
					"1 elements",
					"3 elements"
				},
				{
					DifferenceType::Field,
					"test_data_with_dynamic_array->count",
					"1",
					"3"
				},
				{
					DifferenceType::Field,
					"test_data_with_dynamic_array->x[0]->y",
					"2",
					"3"
				},
			};

			CHECK_EQ(context.differences.size(), std::size(expected_output));
			CHECK_EQ(context.differences, expected_output);
		}

		SUBCASE("Second array is shorter")
		{
			TestData d1[3]{ { 1, 2 }, { 4, 5 }, { 6, 7 } };
			TestData d2[1]{ { 1, 2 } };

			TestDataWithDynamicArray test_data_with_dynamic_array1{ d1, 3 };
			TestDataWithDynamicArray test_data_with_dynamic_array2{ d2, 1 };

			DiffContext context("Comparing TestDataWithDynamicArray");
			DiffVisitor<TestDataWithDynamicArray> diff_visitor(test_data_with_dynamic_array1, context, "test_data_with_dynamic_array");
			diff_visitor.CompareWith(test_data_with_dynamic_array2);

			const auto expected_output = std::vector<DifferenceDescriptor>{
				{
					DifferenceType::Field,
					"test_data_with_dynamic_array->x",
					"3 elements",
					"1 elements"
				},
				{
					DifferenceType::Field,
					"test_data_with_dynamic_array->count",
					"3",
					"1"
				},
			};

			CHECK_EQ(context.differences.size(), std::size(expected_output));
			CHECK_EQ(context.differences, expected_output);
		}

		SUBCASE("Negative counts are treated as empty arrays")
		{
			TestData d1[1]{ { 1, 2 } };
			TestData d2[1]{ { 3, 4 } };

			TestDataWithDynamicArray test_data_with_dynamic_array1{ d1, -1 };
			TestDataWithDynamicArray test_data_with_dynamic_array2{ d2, 0 };

			DiffContext context("Comparing TestDataWithDynamicArray");
			DiffVisitor<TestDataWithDynamicArray> diff_visitor(test_data_with_dynamic_array1, context, "test_data_with_dynamic_array");
			diff_visitor.CompareWith(test_data_with_dynamic_array2);

			const auto expected_output = std::vector<DifferenceDescriptor>{
				{
					DifferenceType::Field,
					"test_data_with_dynamic_array->count",
					"-1",
					"0"
				},
			};

			CHECK_EQ(context.differences.size(), std::size(expected_output));
			CHECK_EQ(context.differences, expected_output);
		}
	}

	TEST_CASE("CompareWith() compares TestDataWith2DArray correctly")
	{
		TestDataWith2DArray test_data_with_2d_array1{ 1, { { 4, 5, 6 }, { 7, 8, 9 } } };
		TestDataWith2DArray test_data_with_2d_array2{ 1, { { 4, 5, 6 }, { 8, 8, 10 } } };

		DiffContext context("Comparing TestDataWith2DArray");
		DiffVisitor<TestDataWith2DArray> diff_visitor(test_data_with_2d_array1, context, "test_data_with_2d_array");
		diff_visitor.CompareWith(test_data_with_2d_array2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"test_data_with_2d_array->arr[1][0]",
				"7",
				"8"
			},
			{
				DifferenceType::Field,
				"test_data_with_2d_array->arr[1][2]",
				"9",
				"10"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares TestDataWith3DArray correctly")
	{
		TestDataWith3DArray test_data_with_3d_array1{ 1, { { 4, 5, 6, 7 }, { 8, 9, 10, 11 } } };
		TestDataWith3DArray test_data_with_3d_array2{ 1, { { 4, 5, 6, 7 }, { 8, 9, 10, 12 } } };

		DiffContext context("Comparing TestDataWith3DArray");
		DiffVisitor<TestDataWith3DArray> diff_visitor(test_data_with_3d_array1, context, "test_data_with_3d_array");
		diff_visitor.CompareWith(test_data_with_3d_array2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"test_data_with_3d_array->arr[1][0][3]",
				"11",
				"12"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares dynamic arrays with a registered count correctly")
	{
		uint32_t flags1[4]{ 1, 2, 3, 4 };
		uint32_t flags2[4]{ 1, 5, 3, 6 };

		TestDataWithExternalCountDynamicArray test_data1{ 7, flags1 };
		TestDataWithExternalCountDynamicArray test_data2{ 7, flags2 };

		SUBCASE("Uses the registered count")
		{
			REGISTER_DYNAMIC_ARRAY_COUNT("TestDataWithExternalCountDynamicArray.flags", 3)

			DiffContext context("Comparing TestDataWithExternalCountDynamicArray");
			DiffVisitor<TestDataWithExternalCountDynamicArray> diff_visitor(test_data1, context);
			diff_visitor.CompareWith(test_data2);

			const auto expected_output = std::vector<DifferenceDescriptor>{
				{
					DifferenceType::Field,
					"flags[1]",
					"2",
					"5"
				},
			};

			CHECK_EQ(context.differences.size(), std::size(expected_output));
			CHECK_EQ(context.differences, expected_output);
		}

		SUBCASE("Reports a difference if only one array is null")
		{
			REGISTER_DYNAMIC_ARRAY_COUNT("TestDataWithExternalCountDynamicArray.flags", 4)

			test_data2.flags = nullptr;

			DiffContext context("Comparing TestDataWithExternalCountDynamicArray");
			DiffVisitor<TestDataWithExternalCountDynamicArray> diff_visitor(test_data1, context);
			diff_visitor.CompareWith(test_data2);

			REQUIRE_EQ(context.differences.size(), 1);
			CHECK_EQ(context.differences[0].type, DifferenceType::Pointer);
			CHECK_EQ(context.differences[0].field_name, "flags");
		}

		SUBCASE("Skips null arrays without a registered count")
		{
			DynamicArrayCountRegistry::Instance().Unregister("TestDataWithExternalCountDynamicArray.flags");

			test_data1.flags = nullptr;
			test_data2.flags = nullptr;

			DiffContext context("Comparing TestDataWithExternalCountDynamicArray");
			DiffVisitor<TestDataWithExternalCountDynamicArray> diff_visitor(test_data1, context);
			diff_visitor.CompareWith(test_data2);

			CHECK(context.differences.empty());
		}

		SUBCASE("Throws if no count is registered")
		{
			DynamicArrayCountRegistry::Instance().Unregister("TestDataWithExternalCountDynamicArray.flags");

			DiffContext context("Comparing TestDataWithExternalCountDynamicArray");
			DiffVisitor<TestDataWithExternalCountDynamicArray> diff_visitor(test_data1, context);

			CHECK_THROWS_AS(diff_visitor.CompareWith(test_data2), std::runtime_error);
		}

		DynamicArrayCountRegistry::Instance().Unregister("TestDataWithExternalCountDynamicArray.flags");
	}

	TEST_CASE("CompareWith() evaluates counts defined with DEFINE_DYNAMIC_ARRAY_COUNT lazily")
	{
		uint32_t flags1[3]{ 1, 2, 3 };
		uint32_t flags2[3]{ 1, 2, 4 };

		TestDataWithLazyCountDynamicArray test_data1{ flags1 };
		TestDataWithLazyCountDynamicArray test_data2{ flags2 };

		{
			g_test_data_flag_count = 2;

			DiffContext context("Comparing TestDataWithLazyCountDynamicArray");
			DiffVisitor<TestDataWithLazyCountDynamicArray> diff_visitor(test_data1, context);
			diff_visitor.CompareWith(test_data2);

			CHECK(context.differences.empty());
		}

		{
			g_test_data_flag_count = 3;

			DiffContext context("Comparing TestDataWithLazyCountDynamicArray");
			DiffVisitor<TestDataWithLazyCountDynamicArray> diff_visitor(test_data1, context);
			diff_visitor.CompareWith(test_data2);

			REQUIRE_EQ(context.differences.size(), 1);
			CHECK_EQ(context.differences[0].field_name, "flags[2]");
		}

		g_test_data_flag_count = 0;
	}

	TEST_CASE("CompareWith() compares an object member which shares its address with the containing object")
	{
		TestDataWithFirstMemberObject object1{ { 1, 2 }, 3 };
		TestDataWithFirstMemberObject object2{ { 1, 5 }, 3 };

		TestDataWithPointerToFirstMemberObject test_data1{ &object1 };
		TestDataWithPointerToFirstMemberObject test_data2{ &object2 };

		DiffContext context("Comparing TestDataWithPointerToFirstMemberObject");
		DiffVisitor<TestDataWithPointerToFirstMemberObject> diff_visitor(test_data1, context, "test_data");
		diff_visitor.CompareWith(test_data2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"test_data->object->inner->y",
				"2",
				"5"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() reports objects which are shared on one side only")
	{
		TestData x{ 1, 2 };
		TestData y{ 1, 2 };
		TestData z{ 1, 2 };

		const auto format_pointer = [](const void* pointer)
		{
			std::stringstream stream;
			stream << std::hex << "0x" << reinterpret_cast<uintptr_t>(pointer);
			return stream.str();
		};

		SUBCASE("Shared in the first object")
		{
			TestDataWithTwoPointers test_data1{ &x, &x };
			TestDataWithTwoPointers test_data2{ &y, &z };

			DiffContext context("Comparing TestDataWithTwoPointers");
			DiffVisitor<TestDataWithTwoPointers> diff_visitor(test_data1, context, "test_data");
			diff_visitor.CompareWith(test_data2);

			const auto expected_output = std::vector<DifferenceDescriptor>{
				{
					DifferenceType::Pointer,
					"test_data->b",
					format_pointer(&x) + " (compared with " + format_pointer(&y) + " before)",
					format_pointer(&z)
				},
			};

			CHECK_EQ(context.differences.size(), std::size(expected_output));
			CHECK_EQ(context.differences, expected_output);
		}

		SUBCASE("Shared in the second object")
		{
			TestDataWithTwoPointers test_data1{ &x, &y };
			TestDataWithTwoPointers test_data2{ &z, &z };

			DiffContext context("Comparing TestDataWithTwoPointers");
			DiffVisitor<TestDataWithTwoPointers> diff_visitor(test_data1, context, "test_data");
			diff_visitor.CompareWith(test_data2);

			const auto expected_output = std::vector<DifferenceDescriptor>{
				{
					DifferenceType::Pointer,
					"test_data->b",
					format_pointer(&y),
					format_pointer(&z) + " (compared with " + format_pointer(&x) + " before)"
				},
			};

			CHECK_EQ(context.differences.size(), std::size(expected_output));
			CHECK_EQ(context.differences, expected_output);
		}

		SUBCASE("Shared in both objects")
		{
			TestDataWithTwoPointers test_data1{ &x, &x };
			TestDataWithTwoPointers test_data2{ &y, &y };

			DiffContext context("Comparing TestDataWithTwoPointers");
			DiffVisitor<TestDataWithTwoPointers> diff_visitor(test_data1, context, "test_data");
			diff_visitor.CompareWith(test_data2);

			CHECK(context.differences.empty());
		}

		SUBCASE("Same object on both sides")
		{
			TestDataWithTwoPointers test_data1{ &x, &x };
			TestDataWithTwoPointers test_data2{ &x, &x };

			DiffContext context("Comparing TestDataWithTwoPointers");
			DiffVisitor<TestDataWithTwoPointers> diff_visitor(test_data1, context, "test_data");
			diff_visitor.CompareWith(test_data2);

			CHECK(context.differences.empty());
		}
	}

	TEST_CASE("CompareWith() does not compare the root object again when it is referenced by a pointer")
	{
		LinkedListNode node1{ 1, nullptr };
		LinkedListNode node2{ 2, nullptr };
		node1.next = &node1;
		node2.next = &node2;

		DiffContext context("Comparing LinkedListNode");
		DiffVisitor<LinkedListNode> diff_visitor(node1, context, "node");
		diff_visitor.CompareWith(node2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{
				DifferenceType::Field,
				"node->value",
				"1",
				"2"
			},
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}

	TEST_CASE("CompareWith() compares floating point values with a tolerance")
	{
		const auto nan = std::numeric_limits<float>::quiet_NaN();
		const auto infinity = std::numeric_limits<double>::infinity();

		TestDataWithValueTypes test_data1{};
		TestDataWithValueTypes test_data2{};

		DiffContext context("Comparing TestDataWithValueTypes");
		DiffVisitor<TestDataWithValueTypes> diff_visitor(test_data1, context);

		SUBCASE("Values within the tolerance are equal")
		{
			test_data1.f = 1.0f;
			test_data2.f = 1.00001f;
			test_data1.floats[0] = 1.0f;
			test_data2.floats[0] = 1.00001f;

			diff_visitor.CompareWith(test_data2);

			CHECK(context.differences.empty());
		}

		SUBCASE("NaN equals only NaN")
		{
			test_data1.f = nan;
			test_data2.f = 1.0f;
			test_data1.floats[0] = 1.0f;
			test_data2.floats[0] = nan;
			test_data1.floats[1] = nan;
			test_data2.floats[1] = nan;

			diff_visitor.CompareWith(test_data2);

			REQUIRE_EQ(context.differences.size(), 2);
			CHECK_EQ(context.differences[0].field_name, "f");
			CHECK_EQ(context.differences[0].other_value, "1");
			CHECK_EQ(context.differences[1].field_name, "floats[0]");
			CHECK_EQ(context.differences[1].object_value, "1");
		}

		SUBCASE("Infinities")
		{
			test_data1.d = infinity;
			test_data2.d = infinity;

			SUBCASE("Equal infinities are equal")
			{
				diff_visitor.CompareWith(test_data2);

				CHECK(context.differences.empty());
			}

			SUBCASE("Opposite infinities are different")
			{
				test_data2.d = -infinity;

				diff_visitor.CompareWith(test_data2);

				REQUIRE_EQ(context.differences.size(), 1);
				CHECK_EQ(context.differences[0].field_name, "d");
			}
		}

		SUBCASE("Large values are printed with enough digits to tell them apart")
		{
			test_data1.f = 123456.1f;
			test_data2.f = 123456.2f;

			diff_visitor.CompareWith(test_data2);

			REQUIRE_EQ(context.differences.size(), 1);
			CHECK_NE(context.differences[0].object_value, context.differences[0].other_value);
		}
	}

	TEST_CASE("CompareWith() prints integer values without truncating or printing characters")
	{
		TestDataWithValueTypes test_data1{};
		TestDataWithValueTypes test_data2{};

		test_data1.u64 = 0x100000001ull;
		test_data2.u64 = 0x200000001ull;
		test_data1.i64 = -5000000000ll;
		test_data2.i64 = 1;
		test_data1.u32 = 4000000000u;
		test_data2.u32 = 1;
		test_data1.u8 = 200;
		test_data2.u8 = 1;
		test_data1.c = 'A';
		test_data2.c = 'B';
		test_data1.flag = true;
		test_data2.flag = false;
		test_data1.bytes[1] = 2;
		test_data2.bytes[1] = 3;

		DiffContext context("Comparing TestDataWithValueTypes");
		DiffVisitor<TestDataWithValueTypes> diff_visitor(test_data1, context);
		diff_visitor.CompareWith(test_data2);

		const auto expected_output = std::vector<DifferenceDescriptor>{
			{ DifferenceType::Field, "u64", "4294967297", "8589934593" },
			{ DifferenceType::Field, "i64", "-5000000000", "1" },
			{ DifferenceType::Field, "u32", "4000000000", "1" },
			{ DifferenceType::Field, "u8", "200", "1" },
			{ DifferenceType::Field, "c", "65", "66" },
			{ DifferenceType::Field, "flag", "1", "0" },
			{ DifferenceType::Field, "bytes[1]", "2", "3" },
		};

		CHECK_EQ(context.differences.size(), std::size(expected_output));
		CHECK_EQ(context.differences, expected_output);
	}
}
