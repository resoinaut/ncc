#include <cstring>       // std::strcmp
#include <optional>      // std::optional
#include <algorithm>     // std::find
#include <unordered_set> // std::unordered_set

#include "error.hh"
#include "options.hh"

std::optional<std::unordered_set<const char *>> parse_options(int argc, char **argv)
{
	std::unordered_set<const char *> filenames;

	std::vector<int> invalid_option_indices;
	std::vector<int> duplicate_option_indices;
	std::vector<int> invalid_dash_count_option_indices;
	std::vector<std::pair<int, int>> invalid_nested_option_indices;

	std::vector<int> duplicate_filename_indices;

	auto insert_option = [&](int index, Option option) -> void
	{
		if (options.contains(option))
			duplicate_option_indices.push_back(index);
		else options.insert(option);
	};

	auto handle_filename_at = [&](int index) -> void
	{
		const char *filename = argv[index];

		if (filenames.contains(filename))
			duplicate_filename_indices.push_back(index);
		else filenames.insert(filename);
	};

	auto handle_single_dash_option_at = [&](int index) -> void
	{
		const char *options = &argv[index][1]; // skip dash

		for (std::size_t i = 0; options[i] != '\0'; i++)
			switch (options[i])
			{
			case 'e':
				insert_option(index, Option::emit_tokens);
				break;
			default:
				invalid_nested_option_indices.push_back({ index, i });
			}
	};

	auto handle_double_dash_option_at = [&](int index) -> void
	{
		const char *option = &argv[index][2]; // skip dashes

		if (!std::strcmp(option, "emit-tokens"))
		{
			insert_option(index, Option::emit_tokens);
			return;
		}

		if (!std::strcmp(option, "no-colour-codes"))
		{
			insert_option(index, Option::no_colour_codes);
			return;
		}

		invalid_option_indices.push_back(index);
	};

	for (int i = 1; i < argc; i++)
	{
		const char *arg = argv[i];

		if (arg[0] != '-')
		{
			handle_filename_at(i);
			continue;
		}

		if (arg[1] != '-')
		{
			handle_single_dash_option_at(i);
			continue;
		}

		if (arg[2] != '-')
		{
			handle_double_dash_option_at(i);
			continue;
		}

		// options starting with 3+ dashes are invalid

		invalid_dash_count_option_indices.push_back(i);
	}

	bool success = true;

	if (invalid_option_indices.size() > 0)
	{
		success = false;

		Shell shell;
		Error error;

		// build shell

		shell.append(argv[0]);

		for (int i = 1; i < argc; i++)
			shell.append(
				argv[i],
				std::find(invalid_option_indices.begin(), invalid_option_indices.end(), i) != invalid_option_indices.end()
					? Shell::Mark::failure
					: Shell::Mark::neutral
			);

		// build error

		error.change_error("invalid command-line options");
		error.attach_shell(shell);

		error.stderr_print();
	}

	if (success) return filenames;
	else return std::nullopt;
}
