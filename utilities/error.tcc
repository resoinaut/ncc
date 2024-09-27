#include <format>      // std::vformat std::make_format_args
#include <string_view> // std::string_view

#include "error.hh"

template<typename ...T>
void Error::change_error(std::string_view format, const T &...args)
{
	this->_error = std::vformat(format, std::make_format_args(args...));
}
