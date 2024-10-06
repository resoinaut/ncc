#include <cctype>      // std::isalpha std::isalnum std::isdigit
#include <vector>      // std::vector
#include <cstddef>     // std::size_t
#include <optional>    // std::optional std::nullopt
#include <string_view> // std::string_view

#include "token.hh"
#include "tokenize.hh"
#include "../utilities/fmt.hh"

std::optional<std::vector<lexer::Token>> lexer::tokenize(std::string_view source)
{
	std::vector<Token> tokens;

	for (std::size_t i = 0; i < source.length(); i++)
	{
		const char curr = source[i];

		switch (curr)
		{
		case ';':
			tokens.push_back({ .kind = Token::Kind::semicolon     });
			continue;
		case '{':
			tokens.push_back({ .kind = Token::Kind::opening_curly });
			continue;
		case '}':
			tokens.push_back({ .kind = Token::Kind::closing_curly });
			continue;
		case '(':
			tokens.push_back({ .kind = Token::Kind::opening_paren });
			continue;
		case ')':
			tokens.push_back({ .kind = Token::Kind::closing_paren });
			continue;
		}

		if (std::isalpha(curr) || curr == '_')
		{
			// j = index after last character

			std::size_t j = i + 1;
			while (j < source.length() && std::isalnum(source[j]) || source[j] == '_') j++;

			tokens.push_back({
				.kind = Token::Kind::ident,
				.data = std::string(&source[i], j - i),
			});

			i = j - 1;

			continue;
		}

		if (std::isdigit(curr))
		{
			std::size_t j = i + 1;
			while (j < source.length() && std::isdigit(source[j])) j++;

			tokens.push_back({
				.kind = Token::Kind::integer,
				.data = std::string(&source[i], j - i),
			});

			i = j - 1;

			continue;
		}

		if (std::isspace(curr))
		{
			continue;
		}

		// invalid character

		fmt::Error("encountered invalid character '{}'", curr);

		return std::nullopt;
	}

	return tokens;
}

void lexer::process_keywords(std::vector<Token> &tokens)
{
	for (Token &token : tokens)
	{
		if (token.kind != Token::Kind::ident) continue;

		if (
			token.data.value() == "int"   ||
			token.data.value() == "void"  ||
			token.data.value() == "return"
		) token.kind = Token::Kind::keyword;
	}
}
