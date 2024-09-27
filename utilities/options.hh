#pragma once

#include <optional>      // std::optional
#include <unordered_set> // std::unordered_set

#include "error.hh"

enum class Option
{
	emit_tokens,
	no_colour_codes,
};

inline std::unordered_set<Option> options;

std::optional<std::unordered_set<const char *>> parse_options(int argc, char **argv);
