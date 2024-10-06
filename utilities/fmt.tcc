#include <format>      // std::vformat std::make_format_args
#include <iostream>    // std::cerr
#include <string_view> // std::string_view

#include "fmt.hh"
#include "ansi.hh"

template<typename ...T>
fmt::Error::Error(std::string_view error, const T &...args)
{
	std::cerr
		<< '\n'
		<< ansi::colour::fg::red << "error: " << ansi::colour::fg::reset
		<< std::vformat(error, std::make_format_args(args...))
		<< '\n';
}
