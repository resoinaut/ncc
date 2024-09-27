#include <vector>        // std::vector
#include <cstdlib>       // EXIT_FAILURE EXIT_SUCCESS
#include <fstream>       // std::ifstream
#include <sstream>       // std::stringstream
#include <iostream>      // std::cout
#include <optional>      // std::optional
#include <unordered_set> // std::unordered_set

#include "lexer/token.hh"
#include "lexer/tokenize.hh"

#include "utilities/ansi.hh"
#include "utilities/error.hh"
#include "utilities/options.hh"

int main(int argc, char **argv)
{
	std::cout << '\n';

	if (argc == 1)
	{
		std::cout
			<< ansi::colour::fg::bright::yellow
			<< "ncc compiler v. wip"
			<< ansi::colour::fg::reset << '\n';

		return EXIT_SUCCESS;
	}

	std::optional<std::unordered_set<const char *>> filenames = parse_options(argc, argv);
	if (!filenames.has_value()) return EXIT_FAILURE;

	if ((*filenames).size() > 1)
	{
		Error error;

		error.change_error("expected 1 source file and encountered {}", (*filenames).size());
		error.stderr_print();

		return EXIT_FAILURE;
	}

	const char *const filename = *(*filenames).begin();

	std::ifstream source(filename);

	if (!source)
	{
		Error error;

		error.change_error("failure opening file '{}'", filename);
		error.stderr_print();

		return EXIT_FAILURE;
	}

	std::stringstream buffer;

	buffer << source.rdbuf();
	source.close();

	std::optional<std::vector<lexer::Token>> tokens = lexer::tokenize(buffer.str());

	if (!tokens.has_value()) return EXIT_FAILURE;
	lexer::process_keywords(tokens.value());

	if (options.contains(Option::emit_tokens))
		for (const lexer::Token &token : tokens.value())
			std::cout << token << '\n';

	return EXIT_SUCCESS;
}
