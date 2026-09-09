#pragma once


#include <sstream>
#include <string>


template <typename T>
struct TestComparator {
	static bool compare(T& a, T& b, const char* context_title, std::string& diff_description)
	{
		const auto equal = a == b;

		if (a != b)
		{
			std::stringstream stream;
			stream << "\n\n" << context_title << '\n';
			stream << a << " (MOO) is NOT equal to " << b << " (Original)\n";
			diff_description = stream.str();
			return false;
		}

		return true;
	}
};
