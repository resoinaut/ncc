#include <cstdlib>  // EXIT_FAILURE EXIT_SUCCESS
#include <iostream> // std::cout

#include "utilities/ansi.hh"
#include "utilities/report.hh"

int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cout << "\nncc compiler v. wip\n";
		return EXIT_SUCCESS;
	}

	std::cerr << '\n';

	if (argc > 2)
	{
		report::error("expected 1 file and encountered {}", argc - 1);
		return EXIT_FAILURE;
	}

	std::cerr << ansi::cursor::up;

	return EXIT_SUCCESS;
}
