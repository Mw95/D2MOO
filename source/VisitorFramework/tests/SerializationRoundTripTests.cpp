#include <doctest.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "BinaryReader.h"
#include "BinaryWriter.h"
#include "Deserializer.h"
#include "DynamicArrayCountRegistry.h"
#include "Serializer.h"
#include "TestDataStructs.h"


namespace
{
	// Serializes the root object and deserializes it again; the result stays valid as long as the RoundTrip lives
	class RoundTrip
	{
	public:
		template<typename T>
		T* operator()(T& root)
		{
			Serializer serializer(m_writer);
			serializer.Serialize(&root);

			m_reader = std::make_unique<BinaryReader>(m_writer.Data(), m_writer.Size());
			m_deserializer = std::make_unique<Deserializer>(*m_reader);

			auto* result = m_deserializer->Deserialize<T>();

			CHECK(m_reader->End());

			return result;
		}

	private:
		BinaryWriter m_writer;
		std::unique_ptr<BinaryReader> m_reader;
		std::unique_ptr<Deserializer> m_deserializer;
	};

	template<typename T>
	void CheckEqual(T& expected, T& actual, const char* name)
	{
		std::string diff_description;
		const auto are_objects_equal = TestComparator<T>::compare(expected, actual, name, diff_description);
		CHECK_MESSAGE(are_objects_equal, diff_description);
	}
}


TEST_SUITE("SerializationRoundTripTests")
{
	TEST_CASE("Round trip preserves SimpleTestData")
	{
		SimpleTestData simple_test_data{ -5 };

		RoundTrip round_trip;
		auto* result = round_trip(simple_test_data);

		CHECK_NE(result, &simple_test_data);
		CheckEqual(simple_test_data, *result, "simple_test_data");
	}

	TEST_CASE("Round trip preserves null pointers")
	{
		TestDataWithPointer test_data_with_pointer{ 7, nullptr };

		RoundTrip round_trip;
		auto* result = round_trip(test_data_with_pointer);

		CHECK_EQ(result->x, 7);
		CHECK_EQ(result->simple, nullptr);
	}

	TEST_CASE("Round trip preserves cycles and shared objects")
	{
		A a{ 10, nullptr };
		B b{ &a, 20 };
		C c{ &b, 30, 40 };
		D d{ &a, &b, 50 };
		E e{ &b, &c, &d, 60 };

		a.e = &e;

		RoundTrip round_trip;
		auto* result = round_trip(e);

		CheckEqual(e, *result, "e");

		CHECK_EQ(result->b->a->e, result);
		CHECK_EQ(result->c->b, result->b);
		CHECK_EQ(result->d->b, result->b);
		CHECK_EQ(result->d->a, result->b->a);
	}

	TEST_CASE("Round trip preserves self references")
	{
		LinkedListNode node{ 1, nullptr };
		node.next = &node;

		RoundTrip round_trip;
		auto* result = round_trip(node);

		CHECK_EQ(result->value, 1);
		CHECK_EQ(result->next, result);
	}

	TEST_CASE("Round trip preserves long pointer chains")
	{
		constexpr int node_count = 10000;

		std::vector<LinkedListNode> nodes(node_count);

		for (int i = 0; i < node_count; ++i)
		{
			nodes[i].value = i;
			nodes[i].next = i + 1 < node_count ? &nodes[i + 1] : nullptr;
		}

		RoundTrip round_trip;
		auto* node = round_trip(nodes[0]);

		for (int i = 0; i < node_count; ++i)
		{
			REQUIRE_NE(node, nullptr);
			REQUIRE_EQ(node->value, i);
			node = node->next;
		}

		CHECK_EQ(node, nullptr);
	}

	TEST_CASE("Round trip preserves arrays")
	{
		RoundTrip round_trip;

		SUBCASE("Int array")
		{
			TestDataWithIntArray test_data{ 7, { 1, 2, 3, 4, 5 } };
			CheckEqual(test_data, *round_trip(test_data), "test_data");
		}

		SUBCASE("Object array")
		{
			TestDataWithObjectArray test_data{ 7, { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 } } };
			CheckEqual(test_data, *round_trip(test_data), "test_data");
		}

		SUBCASE("2D array")
		{
			TestDataWith2DArray test_data{ 42, { { 1, 2, 3 }, { 4, 5, 6 } } };
			CheckEqual(test_data, *round_trip(test_data), "test_data");
		}

		SUBCASE("3D array")
		{
			TestDataWith3DArray test_data{ 42, { { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }, { { 13, 14, 15, 16 }, { 17, 18, 19, 20 }, { 21, 22, 23, 24 } } } };
			CheckEqual(test_data, *round_trip(test_data), "test_data");
		}
	}

	TEST_CASE("Round trip preserves pointer arrays with shared and null elements")
	{
		TestData a{ 42, 43 };
		TestData b{ 44, 45 };
		TestDataWithPointerArray test_data{ 1, { &a, nullptr, &a } };

		RoundTrip round_trip;
		auto* result = round_trip(test_data);

		CheckEqual(test_data, *result, "test_data");
		CHECK_EQ(result->y[0], result->y[2]);
		CHECK_EQ(result->y[1], nullptr);

		TestDataWith2DPointerArray test_data_2d{ { { &a, &b }, { nullptr, &a } } };

		RoundTrip round_trip_2d;
		auto* result_2d = round_trip_2d(test_data_2d);

		CheckEqual(test_data_2d, *result_2d, "test_data_2d");
		CHECK_EQ(result_2d->grid[0][0], result_2d->grid[1][1]);
		CHECK_EQ(result_2d->grid[1][0], nullptr);
	}

	TEST_CASE("Round trip preserves object members")
	{
		TestDataWithObject test_data{ 7, { 1, 2 } };

		RoundTrip round_trip;
		CheckEqual(test_data, *round_trip(test_data), "test_data");
	}

	TEST_CASE("Round trip preserves unions")
	{
		RoundTrip round_trip;

		SUBCASE("Field")
		{
			TestDataWithUnion test_data{};
			test_data.x = 0;
			test_data.y = 11;

			auto* result = round_trip(test_data);

			CHECK_EQ(result->x, 0);
			CHECK_EQ(result->y, 11);
		}

		SUBCASE("Pointer")
		{
			TestData z{ 42, 43 };
			TestDataWithUnion test_data{};
			test_data.x = 1;
			test_data.z = &z;

			auto* result = round_trip(test_data);

			CHECK_EQ(result->x, 1);
			REQUIRE_NE(result->z, nullptr);
			CHECK_EQ(result->z->x, 42);
			CHECK_EQ(result->z->y, 43);
		}
	}

	TEST_CASE("Round trip preserves dynamic arrays")
	{
		RoundTrip round_trip;

		SUBCASE("Count member visited after the array")
		{
			TestData arr[3] = { { 42, 43 }, { 44, 45 }, { 46, 47 } };
			TestDataWithDynamicArray test_data{ arr, 3 };

			auto* result = round_trip(test_data);

			CHECK_NE(result->x, arr);
			CheckEqual(test_data, *result, "test_data");
		}

		SUBCASE("Count member visited before the array")
		{
			TestData arr[2] = { { 42, 43 }, { 44, 45 } };
			TestDataWithCountBeforeDynamicArray test_data{ 2, arr };

			CheckEqual(test_data, *round_trip(test_data), "test_data");
		}

		SUBCASE("Empty array")
		{
			TestData arr[1] = { { 42, 43 } };
			TestDataWithDynamicArray test_data{ arr, 0 };

			auto* result = round_trip(test_data);

			CHECK_NE(result->x, nullptr);
			CHECK_EQ(result->count, 0);
		}

		SUBCASE("Null array with a non-zero count")
		{
			TestDataWithDynamicArray test_data{ nullptr, 5 };

			auto* result = round_trip(test_data);

			CHECK_EQ(result->x, nullptr);
			CHECK_EQ(result->count, 5);
		}

		SUBCASE("Negative count")
		{
			TestData arr[1] = { { 42, 43 } };
			TestDataWithDynamicArray test_data{ arr, -3 };

			auto* result = round_trip(test_data);

			CHECK_NE(result->x, nullptr);
			CHECK_EQ(result->count, -3);
		}
	}

	TEST_CASE("Round trip preserves dynamic arrays of pointers")
	{
		TestData a{ 42, 43 };
		TestData b{ 44, 45 };
		TestData* items[4] = { &a, nullptr, &b, &a };
		TestDataWithDynamicPointerArray test_data{ items, 4 };

		RoundTrip round_trip;
		auto* result = round_trip(test_data);

		CheckEqual(test_data, *result, "test_data");
		CHECK_EQ(result->items[0], result->items[3]);
		CHECK_EQ(result->items[1], nullptr);
	}

	TEST_CASE("Round trip of dynamic arrays with a registered count uses the count at serialization time")
	{
		constexpr auto count_key = "TestDataWithExternalCountDynamicArray.flags";

		uint32_t flags[3] = { 10, 11, 12 };
		TestDataWithExternalCountDynamicArray test_data{ 7, flags };

		BinaryWriter writer;

		REGISTER_DYNAMIC_ARRAY_COUNT(count_key, 3);
		Serializer(writer).Serialize(&test_data);

		// Deserialization must not depend on the registered count
		REGISTER_DYNAMIC_ARRAY_COUNT(count_key, 1000);

		BinaryReader reader(writer.Data(), writer.Size());
		Deserializer deserializer(reader);

		auto* result = deserializer.Deserialize<TestDataWithExternalCountDynamicArray>();

		DynamicArrayCountRegistry::Instance().Unregister(count_key);

		CHECK_EQ(result->x, 7);
		REQUIRE_NE(result->flags, nullptr);
		CHECK_EQ(result->flags[0], 10);
		CHECK_EQ(result->flags[1], 11);
		CHECK_EQ(result->flags[2], 12);
	}

	TEST_CASE("Round trip preserves dynamic arrays with a lazily evaluated count")
	{
		uint32_t flags[2] = { 10, 11 };
		TestDataWithLazyCountDynamicArray test_data{ flags };

		g_test_data_flag_count = 2;

		RoundTrip round_trip;
		auto* result = round_trip(test_data);

		CheckEqual(test_data, *result, "test_data");

		g_test_data_flag_count = 0;
	}

	TEST_CASE("Round trip preserves enum arrays")
	{
		TestEnum dynamic_values[2] = { TestEnum::Third, TestEnum::First };
		TestDataWithEnumArray test_data{ { TestEnum::First, TestEnum::Second, TestEnum::Third }, dynamic_values, 2 };

		RoundTrip round_trip;
		auto* result = round_trip(test_data);

		CHECK_EQ(result->values[0], TestEnum::First);
		CHECK_EQ(result->values[1], TestEnum::Second);
		CHECK_EQ(result->values[2], TestEnum::Third);
		CHECK_EQ(result->dynamic_count, 2);
		REQUIRE_NE(result->dynamic_values, nullptr);
		CHECK_EQ(result->dynamic_values[0], TestEnum::Third);
		CHECK_EQ(result->dynamic_values[1], TestEnum::First);
	}

	TEST_CASE("Round trip preserves pointers to const objects")
	{
		const TestData data{ 42, 43 };
		TestDataWithConstPointer test_data{ &data };

		RoundTrip round_trip;
		auto* result = round_trip(test_data);

		REQUIRE_NE(result->data, nullptr);
		CHECK_NE(result->data, &data);
		CHECK_EQ(result->data->x, 42);
		CHECK_EQ(result->data->y, 43);
	}

	TEST_CASE("Round trip of a pointer to the first member of an object yields an object of the right type")
	{
		TestDataWithInteriorPointer test_data{ { 1, 2 }, nullptr };
		test_data.inner_ptr = &test_data.inner;

		RoundTrip round_trip;
		auto* result = round_trip(test_data);

		CHECK_EQ(result->inner.x, 1);
		CHECK_EQ(result->inner.y, 2);
		REQUIRE_NE(result->inner_ptr, nullptr);
		CHECK_EQ(result->inner_ptr->x, 1);
		CHECK_EQ(result->inner_ptr->y, 2);
	}

	TEST_CASE("Round trip of multiple blocks in the same buffer")
	{
		SimpleTestData first{ 1 };
		TestDataWithPointer second{ 2, &first };

		BinaryWriter writer;
		Serializer serializer(writer);

		serializer.Serialize(&first);
		serializer.Serialize(&second);

		BinaryReader reader(writer.Data(), writer.Size());
		Deserializer deserializer(reader);

		auto* first_result = deserializer.Deserialize<SimpleTestData>();
		auto* second_result = deserializer.Deserialize<TestDataWithPointer>();

		CHECK(reader.End());
		CHECK_EQ(first_result->x, 1);
		CHECK_EQ(second_result->x, 2);
		REQUIRE_NE(second_result->simple, nullptr);
		CHECK_NE(second_result->simple, first_result);
		CHECK_EQ(second_result->simple->x, 1);
	}
}
