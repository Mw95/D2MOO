#pragma once


#include <iostream>
#include <string>


#include <TestComparator.h>


template <typename T>
void moo_check_eq(T& a, T& b, const char* context_title)
{
	std::string diff_description;
	using Type = std::remove_cv_t<std::remove_reference_t<T>>;
	if constexpr (std::is_pointer_v<Type>)
	{
		using Comparator = TestComparator<std::remove_pointer_t<Type>>;
		const auto are_objects_equal = Comparator::compare(*a, *b, context_title, diff_description);
		CHECK_MESSAGE(are_objects_equal, diff_description);
	}
	else
	{
		using Comparator = TestComparator<Type>;
		const auto are_objects_equal = Comparator::compare(a, b, context_title, diff_description);
		CHECK_MESSAGE(are_objects_equal, diff_description);
	}
}


#define MOO_CHECK_EQ(a, b, context_title)																\
	moo_check_eq(a, b, context_title)


// TODO: This can be removed eventually once all types are registered and can use MOO_CHECK_EQ
#define SKIP_MOO_CHECK_EQ(a, b, message)																\
	do {																								\
		(void)a;																						\
		(void)b;																						\
		(void)message;																					\
		std::cerr << "\nUse MOO_CHECK_EQ instead!\n";													\
		CHECK(false);																					\
	} while (0);
