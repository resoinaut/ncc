#pragma once

#include <format>      // std::format
#include <iostream>    // std::cerr
#include <string_view> // std::string_view

#include "ansi.hh"

// note: these definitions are un-defined at the end of the file

#define error_colour ansi::colour::red
#define reset_colour ansi::colour::reset

namespace report
{
	template<typename ...T>
	void error(std::string_view error, T&&... args)
	{
		std::cerr
			<< error_colour << "error:" << reset_colour << ' '
			<< std::vformat(error, std::make_format_args(args...)) << '\n';
	}
}

#undef error_colour
#undef reset_colour
