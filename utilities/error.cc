#include <tuple>       // std::tuple std::tie
#include <format>      // std::vformat std::make_format_args
#include <string>      // std::string
#include <cstring>     // std::strlen
#include <iostream>    // std::cerr
#include <string_view> // std::string_view

#include "ansi.hh"
#include "error.hh"
#include "options.hh"

void Shell::append(const char *arg, Mark mark)
{
	this->_args.push_back({ .mark = mark, .arg = arg });
}

std::tuple<std::string, std::string> Shell::build() const
{
	std::string shell;
	Mark prev_arg_mark = Mark::neutral;

	for (const Arg &arg : this->_args)
	{
		// switch colours only if necessary in order to
		// avoid unnecessary string operations

		if (arg.mark != prev_arg_mark)
			switch (arg.mark)
			{
			case Mark::success:
				shell += ansi::colour::fg::green;
				break;
			case Mark::neutral:
				shell += ansi::colour::fg::reset;
				break;
			case Mark::failure:
				shell += ansi::colour::fg::magenta;
			}

		shell += arg.arg;
		shell += ' ';

		prev_arg_mark = arg.mark;
	}

	// reset the terminal colour to default if necessary

	if (prev_arg_mark != Mark::neutral)
		shell += ansi::colour::fg::reset;

	return std::tuple<std::string, std::string>(shell, std::string());
}

std::tuple<std::string, std::string> Shell::build_no_colour_codes() const
{
	// * builds the shell without using ansi colour codes

	// * marking both failures and successes would result in ambiguity
	// * without the use of different colours and so only failures are
	// * marked

	// * ie.
	// *
	// * ncc app --invalid-option --no-colour-codes
	// *         ^^^^^^^^^^^^^^^^
	// *

	std::string shell;
	std::string marks;

	for (const Arg &arg : this->_args)
	{
		if (arg.mark == Mark::failure)
		{
			marks += std::string(shell.length() - marks.length(), ' ');
			marks += std::string(std::strlen(arg.arg), '^');
		}

		shell += arg.arg;
		shell += ' ';
	}

	return std::tuple<std::string, std::string>(shell, marks);
}

void Error::attach_shell(const Shell &shell)
{
	this->_shell = &shell;
}

void Error::stderr_print(void) const
{
	if (!this->_error.empty())
	{
		bool use_colour_codes = !options.contains(Option::no_colour_codes);

		if (use_colour_codes)
			std::cerr << ansi::colour::fg::red;

		std::cerr << "error: ";

		if (use_colour_codes)
			std::cerr << ansi::colour::fg::reset;
		std::cerr << this->_error << '\n';
	}

	if (this->_shell != nullptr)
	{
		std::cerr << '\n';

		std::string shell;
		std::string marks;

		// build without using ansi colour codes if the option
		// --no-colour-codes is set

		std::tie(shell, marks) = options.contains(Option::no_colour_codes)
			? this->_shell->build_no_colour_codes()
			: this->_shell->build();

		std::cerr << "$      " << shell << '\n';

		if (!marks.empty())
		std::cerr << "       " << marks << '\n';
	}
}
