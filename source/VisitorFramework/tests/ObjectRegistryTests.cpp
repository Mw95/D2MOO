#include <doctest.h>

#include "ObjectRegistry.h"


TEST_SUITE("ObjectRegistryTests")
{
	TEST_CASE("NullObject maps to 0")
	{
		CHECK_EQ(ObjectRegistry::NullObject, 0);
	}

	TEST_CASE("FindObject() returns nullptr for NullObject id")
	{
		ObjectRegistry registry;
		const auto found_object = registry.FindObject(ObjectRegistry::NullObject);

		CHECK_EQ(found_object, nullptr);
	}

	TEST_CASE("FindObject() returns nullptr if object was not added")
	{
		const auto object_id = 1;
		ObjectRegistry registry;
		const auto found_object = registry.FindObject(object_id);

		CHECK_EQ(found_object, nullptr);
	}

	TEST_CASE("FindObject() returns pointer to object if it was added before")
	{
		const auto object_id = 1;
		auto object = 666;
		ObjectRegistry registry;

		registry.Add(object_id, &object);

		const auto found_object = registry.FindObject(object_id);

		CHECK_EQ(found_object, &object);
	}

	TEST_CASE("FindObject() returns pointer to object if it was registered before")
	{
		auto object = 666;
		ObjectRegistry registry;

		const auto object_id = registry.Register(&object);

		const auto found_object = registry.FindObject(object_id);

		CHECK_EQ(found_object, &object);
	}

	TEST_CASE("Register() increments object ids")
	{
		auto object1 = 666;
		auto object2 = 667;
		ObjectRegistry registry;

		const auto object_id1 = registry.Register(&object1);

		CHECK_EQ(object_id1, 1);

		const auto object_id2 = registry.Register(&object2);

		CHECK_EQ(object_id2, 2);
	}

	TEST_CASE("Register() doesn't register the same object twice")
	{
		auto object = 666;
		ObjectRegistry registry;

		const auto object_id1 = registry.Register(&object);

		CHECK_EQ(object_id1, 1);

		const auto object_id2 = registry.Register(&object);

		CHECK_EQ(object_id2, 1);
	}

	TEST_CASE("Register() doesn't register nullptr objects")
	{
		int* pointer_to_object = nullptr;
		ObjectRegistry registry;

		const auto object_id = registry.Register(pointer_to_object);

		CHECK_EQ(object_id, ObjectRegistry::NullObject);
	}

	TEST_CASE("Add() doesn't add object if nullptr object is used")
	{
		int* pointer_to_object = nullptr;
		const auto object_id = 1;

		ObjectRegistry registry;

		registry.Add(object_id, pointer_to_object);

		CHECK_EQ(registry.FindObject(object_id), nullptr);
	}

	TEST_CASE("Add() doesn't add object if NullObject id is used")
	{
		auto object = 666;
		const auto object_id = ObjectRegistry::NullObject;

		ObjectRegistry registry;

		registry.Add(object_id, &object);

		CHECK_EQ(registry.FindObject(object_id), nullptr);
	}

	TEST_CASE("Add() adds object if id and object are valid")
	{
		auto object = 666;
		const auto object_id = 1;

		ObjectRegistry registry;

		registry.Add(object_id, &object);

		CHECK_EQ(registry.FindObject(object_id), &object);
	}

	TEST_CASE("Add() doesn't overwrite existing object if same id is used")
	{
		auto object1 = 666;
		auto object2 = 667;

		const auto object_id = 1;

		ObjectRegistry registry;

		registry.Add(object_id, &object1);
		registry.Add(object_id, &object2);

		CHECK_EQ(registry.FindObject(object_id), &object1);
	}

	TEST_CASE("Add() doesn't duplicate existing object if other id used")
	{
		auto object = 666;
		const auto object_id1 = 1;
		const auto object_id2 = 2;

		ObjectRegistry registry;

		registry.Add(object_id1, &object);
		registry.Add(object_id2, &object);

		CHECK_EQ(registry.FindObject(object_id1), &object);
		CHECK_EQ(registry.FindObject(object_id2), nullptr);
	}
}
