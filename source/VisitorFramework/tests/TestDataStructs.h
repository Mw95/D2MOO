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
