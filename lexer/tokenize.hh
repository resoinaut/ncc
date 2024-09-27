#pragma once

#include <vector>      // std::vector
#include <optional>    // std::optional
#include <string_view> // std::string_view

#include "token.hh"

namespace lexer
{

// returns std::nullopt in case of error
std::optional<std::vector<lexer::Token>> tokenize(std::string_view source);

void process_keywords(std::vector<lexer::Token> &tokens);

}
