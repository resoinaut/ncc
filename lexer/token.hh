#pragma once

#include <ostream>     // std::ostream
#include <optional>    // std::optional
#include <string_view> // std::string_view

#include <string>

namespace lexer
{

struct Token
{
	enum class Kind
	{
		ident,
		keyword,

		// literals

		integer,

		// delimiters

		semicolon,

		opening_curly,
		closing_curly,

		opening_paren,
		closing_paren,
	} kind;

	std::optional<std::string> data;
};

}

std::ostream &operator<<(std::ostream &os, const lexer::Token &token);
