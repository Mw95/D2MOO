#pragma once


#include <iostream>
#include <string>


#include <TestComparator.h>


#define MOO_CHECK_EQ(a, b, context_title)																\
	do {																								\
		std::string diff_description;																	\
		using Comparator = TestComparator<decltype(a)>;													\
		const auto are_objects_equal = Comparator::compare(a, b, context_title, diff_description);		\
		CHECK_MESSAGE(are_objects_equal, diff_description);												\
	} while (0);


// TODO: This can be removed eventually once all types are registered and can use MOO_CHECK_EQ
#define SKIP_MOO_CHECK_EQ(a, b, message)																\
	do {																								\
		(void)a;																						\
		(void)b;																						\
		(void)message;																					\
		std::cerr << "\nUse MOO_CHECK_EQ instead!\n";													\
		CHECK(false);																					\
	} while (0);
