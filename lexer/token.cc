#include <ostream> // std::ostream

#include "token.hh"

std::ostream &operator<<(std::ostream &os, const lexer::Token &token)
{
	switch (token.kind)
	{
	case lexer::Token::Kind::ident:
		os << "ident   " << token.data.value();
		break;
	case lexer::Token::Kind::keyword:
		os << "keyword " << token.data.value();
		break;
	case lexer::Token::Kind::integer:
		os << "integer " << token.data.value();
		break;
	case lexer::Token::Kind::semicolon:
		os << "semicolon";
		break;
	case lexer::Token::Kind::opening_curly:
		os << "opening curly";
		break;
	case lexer::Token::Kind::closing_curly:
		os << "closing curly";
		break;
	case lexer::Token::Kind::opening_paren:
		os << "opening paren";
		break;
	case lexer::Token::Kind::closing_paren:
		os << "closing paren";
		break;
	}

	return os;
}
