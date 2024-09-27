#pragma once

#include <tuple>       // std::tuple
#include <string>      // std::string
#include <vector>      // std::vector
#include <string_view> // std::string_view

class Shell
{
	friend class Error;

public:
	enum Mark
	{
		neutral,
		success,
		failure,
	};

	void append(const char *arg, Mark mark = Mark::neutral);

private:
	struct Arg
	{
		Mark mark;
		const char *arg;
	};

	std::vector<Arg> _args;

	std::tuple<std::string, std::string> build() const;
	std::tuple<std::string, std::string> build_no_colour_codes() const;
};

class Error
{
public:
	template<typename ...T>
	void change_error(std::string_view format, const T &...args);
	void attach_shell(const Shell &shell);

	void stderr_print(void) const;

private:
	std::string _error;
	const Shell *_shell = nullptr;
};

#include "error.tcc"
