#include <doctest.h>

#include <stdexcept>

#include "ObjectRegistry.h"
#include "PointerFixups.h"


struct ObjectRegistryFixture
{
	ObjectRegistry registry;

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;

	int id_a;
	int id_b;

	ObjectRegistryFixture() {
		id_a = registry.Register(&a);
		id_b = registry.Register(&b);
	};
};


TEST_SUITE("PointerFixupsTests")
{
	TEST_CASE("Add() does nothing if location is nullptr")
	{
		PointerFixups fixups;

		fixups.Add(nullptr, 2);

		CHECK_EQ(fixups.Count(), 0);
	}

	TEST_CASE("Add() immediately assigns nullptr to location if target is NullObject")
	{
		int x = 0;
		void* location = &x;
		PointerFixups fixups;

		CHECK_NE(location, nullptr);

		fixups.Add(&location, ObjectRegistry::NullObject);

		CHECK_EQ(fixups.Count(), 0);
		CHECK_EQ(location, nullptr);
	}

	TEST_CASE_FIXTURE(ObjectRegistryFixture, "Resolve() assigns registered values to locations")
	{
		int* p1 = &c;
		int* p2 = &d;

		PointerFixups fixups;

		fixups.Add(reinterpret_cast<void**>(&p1), id_a);
		fixups.Add(reinterpret_cast<void**>(&p2), id_b);

		CHECK_EQ(*p1, 3);
		CHECK_EQ(*p2, 4);

		fixups.Resolve(registry);

		CHECK_EQ(*p1, 1);
		CHECK_EQ(*p2, 2);
	}

	TEST_CASE_FIXTURE(ObjectRegistryFixture, "Resolve() throws if no object was registered")
	{
		int* p1 = &c;
		int* p2 = &d;
		int* p3 = &e;

		PointerFixups fixups;

		const auto id_c = 99;

		fixups.Add(reinterpret_cast<void**>(&p1), id_a);
		fixups.Add(reinterpret_cast<void**>(&p2), id_b);
		fixups.Add(reinterpret_cast<void**>(&p3), id_c);

		CHECK_THROWS_AS(fixups.Resolve(registry), std::runtime_error);
	}

	TEST_CASE("Count() returns number of inserted fixups")
	{
		int x = 0;
		void* location = &x;
		PointerFixups fixups;

		fixups.Add(&location, 1);

		CHECK_EQ(fixups.Count(), 1);

		fixups.Add(&location, 2);
		fixups.Add(&location, 3);
		fixups.Add(&location, 4);

		CHECK_EQ(fixups.Count(), 4);
	}

	TEST_CASE("Clear() deletes all fixups")
	{
		int x = 0;
		void* location = &x;
		PointerFixups fixups;

		fixups.Add(&location, 1);
		fixups.Add(&location, 2);
		fixups.Add(&location, 3);
		fixups.Add(&location, 4);

		CHECK_EQ(fixups.Count(), 4);

		fixups.Clear();

		CHECK_EQ(fixups.Count(), 0);
	}
}
