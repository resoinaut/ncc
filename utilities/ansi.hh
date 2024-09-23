#pragma once

namespace ansi
{
	// note: default is named reset to avoid name collisions with the keyword
	namespace colour
	{
		inline constexpr const char *const red   = "\033[31m";
		inline constexpr const char *const reset = "\033[39m";
	}

	namespace cursor
	{
		inline constexpr const char *const up    = "\033[A";
	}
}
