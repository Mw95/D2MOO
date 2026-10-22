#pragma once


#include "DiffContext.h"
#include "DiffVisitor.h"
#include "Macros.h"
#include "TestComparator.h"
#include "TypeRegistration.h"


struct SimpleTestData
{
	int x;
};

BEGIN_VISIT(SimpleTestData)
	FIELD(x)
END_VISIT()

struct TestDataWithPointer
{
	int x;
	SimpleTestData* simple;
};

BEGIN_VISIT(TestDataWithPointer)
	FIELD(x)
	POINTER(simple)
END_VISIT()

struct E;

struct A
{
	int a;
	E* e;
};

BEGIN_VISIT(A)
	FIELD(a)
	POINTER(e)
END_VISIT()

struct B
{
	A* a;
	int b;
};

BEGIN_VISIT(B)
	POINTER(a)
	FIELD(b)
END_VISIT()

struct C
{
	B* b;
	int c;
	int d;
};

BEGIN_VISIT(C)
	POINTER(b)
	FIELD(c)
	FIELD(d)
END_VISIT()

struct D
{
	A* a;
	B* b;
	int d;
};

BEGIN_VISIT(D)
	POINTER(a)
	POINTER(b)
	FIELD(d)
END_VISIT()

struct E
{
	B* b;
	C* c;
	D* d;
	int e;
};

BEGIN_VISIT(E)
	POINTER(b)
	POINTER(c)
	POINTER(d)
	FIELD(e)
END_VISIT()

struct TestDataWithIntArray
{
	int x;
	int arr[5];
};

BEGIN_VISIT(TestDataWithIntArray)
	FIELD(x)
	ARRAY(arr)
END_VISIT()

struct TestData
{
	int x;
	int y;
};

BEGIN_VISIT(TestData)
	FIELD(x)
	FIELD(y)
END_VISIT()

struct TestDataWithObjectArray
{
	int x;
	TestData arr[5];
};

BEGIN_VISIT(TestDataWithObjectArray)
	FIELD(x)
	ARRAY(arr)
END_VISIT()

struct TestDataWithObject
{
	int x;
	TestData y;
};

BEGIN_VISIT(TestDataWithObject)
	FIELD(x)
	OBJECT(y)
END_VISIT()

struct TestDataWithUnion
{
	int x;
	union
	{
		int y;
		TestData* z;
	};
};

BEGIN_VISIT(TestDataWithUnion)
	FIELD(x)

	BEGIN_UNION(x)
		UNION_FIELD(0, y)
		UNION_POINTER(1, z)
	END_UNION()
END_VISIT()

struct TestDataWithPointerArray
{
	int x;
	TestData* y[3];
};

BEGIN_VISIT(TestDataWithPointerArray)
	FIELD(x)
	ARRAY(y)
END_VISIT()

struct TestDataWithDynamicArray
{
	TestData* x;
	int count;
};

BEGIN_VISIT(TestDataWithDynamicArray)
	DYNAMIC_ARRAY(x, count)
	FIELD(count)
END_VISIT()

struct TestDataWithExternalCountDynamicArray
{
	int x;
	uint32_t* flags;
};

BEGIN_VISIT(TestDataWithExternalCountDynamicArray)
	FIELD(x)
	DYNAMIC_ARRAY_KEY(flags, "TestDataWithExternalCountDynamicArray.flags")
END_VISIT()

inline size_t g_test_data_flag_count = 0;

struct TestDataWithLazyCountDynamicArray
{
	uint32_t* flags;
};

DEFINE_DYNAMIC_ARRAY_COUNT("TestDataWithLazyCountDynamicArray.flags", g_test_data_flag_count)

BEGIN_VISIT(TestDataWithLazyCountDynamicArray)
	DYNAMIC_ARRAY_KEY(flags, "TestDataWithLazyCountDynamicArray.flags")
END_VISIT()

struct TestDataWith2DArray
{
	int x;
	int arr[2][3];
};

BEGIN_VISIT(TestDataWith2DArray)
	FIELD(x)
	ARRAY(arr)
END_VISIT()

struct TestDataWith3DArray
{
	int x;
	int arr[2][3][4];
};

BEGIN_VISIT(TestDataWith3DArray)
	FIELD(x)
	ARRAY(arr)
END_VISIT()

// Like BEGIN_VISIT(), but without a TestComparator, for types the DiffVisitor does not support (enum array elements)
#define BEGIN_SERIALIZATION_VISIT(TYPE)																	\
template<>																								\
struct TypeId<TYPE>																						\
{																										\
	static constexpr uint64_t value = fnv1a(#TYPE);														\
};																										\
const auto _##TYPE##_Registered = TypeRegistration<TYPE>::Registered;									\
template<>																								\
struct VisitorTraits<TYPE>																				\
{																										\
	using Self = TYPE;																					\
	template<class Visitor>																				\
	static void Visit(Visitor& visitor, TYPE& object)													\
	{

struct TestDataWithCountBeforeDynamicArray
{
	int count;
	TestData* x;
};

BEGIN_VISIT(TestDataWithCountBeforeDynamicArray)
	FIELD(count)
	DYNAMIC_ARRAY(x, count)
END_VISIT()

struct TestDataWithDynamicPointerArray
{
	TestData** items;
	uint16_t count;
};

BEGIN_VISIT(TestDataWithDynamicPointerArray)
	DYNAMIC_ARRAY(items, count)
	FIELD(count)
END_VISIT()

struct TestDataWith2DPointerArray
{
	TestData* grid[2][2];
};

BEGIN_VISIT(TestDataWith2DPointerArray)
	ARRAY(grid)
END_VISIT()

struct TestDataWithConstPointer
{
	const TestData* data;
};

BEGIN_VISIT(TestDataWithConstPointer)
	POINTER(data)
END_VISIT()

// inner and inner_ptr share the same address, but are distinct objects of different types
struct TestDataWithInteriorPointer
{
	TestData inner;
	TestData* inner_ptr;
};

BEGIN_VISIT(TestDataWithInteriorPointer)
	OBJECT(inner)
	POINTER(inner_ptr)
END_VISIT()

// inner shares its address with the containing object
struct TestDataWithFirstMemberObject
{
	TestData inner;
	int z;
};

BEGIN_VISIT(TestDataWithFirstMemberObject)
	OBJECT(inner)
	FIELD(z)
END_VISIT()

struct TestDataWithPointerToFirstMemberObject
{
	TestDataWithFirstMemberObject* object;
};

BEGIN_VISIT(TestDataWithPointerToFirstMemberObject)
	POINTER(object)
END_VISIT()

struct TestDataWithTwoPointers
{
	TestData* a;
	TestData* b;
};

BEGIN_VISIT(TestDataWithTwoPointers)
	POINTER(a)
	POINTER(b)
END_VISIT()

struct TestDataWithValueTypes
{
	float f;
	double d;
	uint64_t u64;
	int64_t i64;
	uint32_t u32;
	uint8_t u8;
	char c;
	bool flag;
	uint8_t bytes[2];
	float floats[2];
};

BEGIN_VISIT(TestDataWithValueTypes)
	FIELD(f)
	FIELD(d)
	FIELD(u64)
	FIELD(i64)
	FIELD(u32)
	FIELD(u8)
	FIELD(c)
	FIELD(flag)
	ARRAY(bytes)
	ARRAY(floats)
END_VISIT()

struct TestDataWithOmittedField
{
	int x;
	int omitted;
};

BEGIN_VISIT(TestDataWithOmittedField)
	FIELD(x)
	OMIT(omitted)
END_VISIT()

struct LinkedListNode
{
	int value;
	LinkedListNode* next;
};

BEGIN_VISIT(LinkedListNode)
	FIELD(value)
	POINTER(next)
END_VISIT()

enum class TestEnum : uint8_t
{
	First = 1,
	Second = 2,
	Third = 3,
};

struct TestDataWithEnumArray
{
	TestEnum values[3];
	TestEnum* dynamic_values;
	int dynamic_count;
};

BEGIN_SERIALIZATION_VISIT(TestDataWithEnumArray)
	ARRAY(values)
	DYNAMIC_ARRAY(dynamic_values, dynamic_count)
	FIELD(dynamic_count)
END_VISIT()
