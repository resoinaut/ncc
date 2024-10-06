#include <string>        // std::string
#include <cstddef>       // std::size_t
#include <cstring>       // std::strlen
#include <iostream>      // std::cerr
#include <unordered_set> // std::unordered_set

#include "fmt.hh"

fmt::Error fmt::Error::shell(int argc, char *argv[], const std::unordered_set<int> &indices_to_mark) const
{
	// *
	// * eg. .shell(argc, argv, invalid_indices) could expand to...
	// *
	// * $ ncc --invalid1 app --invalid2
	// *       ^^^^^^^^^^     ^^^^^^^^^^
	// *

	std::string shell = "$      ";
	std::string marks;

	for (int i = 0; i < argc; i++)
	{
		std::size_t length = std::strlen(argv[i]);

		if (indices_to_mark.contains(i))
		{
			marks += std::string(shell.length() - marks.length(), ' ');
			marks += std::string(length, '^');
		}

		shell += argv[i];
		shell += ' ';
	}

	shell.pop_back(); // remove trailing space

	std::cerr << '\n' << shell << '\n' << marks << '\n';

	return *this;
}
