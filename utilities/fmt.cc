#include <string>        // std::string
#include <cstddef>       // std::size_t
#include <cstring>       // std::strlen
#include <iostream>      // std::cerr
#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

#include "fmt.hh"
#include "ansi.hh"

fmt::Error::Error(std::string_view error)
{
	std::cerr
		<< '\n'
		<< ansi::colour::fg::red << "error: " << ansi::colour::fg::reset
		<< error
		<< '\n';
}

fmt::Error fmt::Error::shell(int argc, char *argv[], const std::unordered_set<int> &indices_to_mark) const
{
	// *
	// * eg. .shell(argc, argv, invalid_indices) could expand to...
	// *
	// * $ ncc --invalid1 app --invalid2
	// *       ^^^^^^^^^^     ^^^^^^^^^^
	// *

	std::cerr << "$      ";

	// index contains the position in the command-line
	// marks contains the markings of '^' to be output later

	std::size_t index {};
	std::string marks {};

	for (int i = 0; i < argc; i++)
	{
		std::size_t length = std::strlen(argv[i]);

		if (indices_to_mark.contains(i))
		{
			marks += std::string(marks.length() - index, ' ');
			marks += std::string(length, '^');
		}

		std::cerr << ' ' << argv[i];
		index += length;
	}

	std::cerr << marks << '\n';

	return *this;
}
