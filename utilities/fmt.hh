#pragma once

#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

namespace fmt
{
	class Error
	{
	public:
		// constructors

		template<typename ...T>
		Error(std::string_view error, const T &...args);

		// member functions

		// Formats command-line arguments.
		Error shell(int argc, char *argv[], const std::unordered_set<int> &indices_to_mark) const;
	};
}

#include "fmt.tcc"
