#pragma once


#include <functional>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <sstream>
#include <typeindex>
#include <utility>
#include <vector>

#include "DifferenceDescriptor.h"


// The name of a nested field, e.g. "a->b->c[2]". Nodes share their parents, so comparing a long pointer chain does
// not copy an ever-growing name at every level. Turned into a string only when a difference is reported.
struct DiffFieldPath
{
	std::shared_ptr<DiffFieldPath> parent;
	std::string name;

	DiffFieldPath(std::shared_ptr<DiffFieldPath> parent, std::string name) : parent(std::move(parent)), name(std::move(name)) {}

	DiffFieldPath(const DiffFieldPath&) = delete;
	DiffFieldPath& operator=(const DiffFieldPath&) = delete;

	// Releases the parents iteratively, as releasing a long chain recursively could overflow the call stack
	~DiffFieldPath()
	{
		auto ancestor = std::move(parent);

		while (ancestor && ancestor.use_count() == 1)
		{
			ancestor = std::move(ancestor->parent);
		}
	}

	std::string ToString() const
	{
		std::vector<const DiffFieldPath*> nodes;

		for (auto* node = this; node != nullptr; node = node->parent.get())
		{
			nodes.push_back(node);
		}

		std::string result;

		for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
		{
			if (!result.empty())
			{
				result += "->";
			}

			result += (*it)->name;
		}

		return result;
	}
};


struct DiffContext
{
	const char* title;
	std::vector<DifferenceDescriptor> differences;

	// Objects already compared, keyed by address and type (a struct and its first member share an address),
	// mapped to the object they were compared with. Tracked for both sides to detect differently shared objects.
	using VisitedKey = std::pair<const void*, std::type_index>;
	std::map<VisitedKey, const void*> visited_objects;
	std::map<VisitedKey, const void*> visited_other_objects;

	// Comparisons of child objects which are still to be done, see DiffVisitor::CompareWith()
	std::vector<std::function<void()>> pending_comparisons;
	bool comparing = false;

	explicit DiffContext(const char* title) : title(title), differences() {}

	std::string DifferenceDescription()
	{
		std::stringstream stream;

		if (differences.empty())
		{
			return "";
		}

		if (title != nullptr)
		{
			stream << "\n\n" << title << '\n';
		}

		stream << "Found \x1b[33m" << differences.size() << "\x1b[0m difference(s):\n\n";

		for (const auto& difference : differences)
		{
			stream << "Field: \x1b[33m" << difference.field_name << "\x1b[0m\n";
			stream << "  MOO      value: \x1b[31m" << difference.object_value << "\x1b[0m\n";
			stream << "  Original value: \x1b[31m" << difference.other_value << "\x1b[0m\n";
			stream << '\n';
		}

		stream << "---------------------------" << std::endl;

		return stream.str();
	}
};
