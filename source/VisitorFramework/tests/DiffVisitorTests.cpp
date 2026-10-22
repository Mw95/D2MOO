#include <doctest.h>

#include <cstdint>

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
}
