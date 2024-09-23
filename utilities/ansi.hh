#pragma once

namespace ansi
{
	// note: default is named reset to avoid name collisions with the keyword
	namespace colour
	{
		namespace fg
		{
			inline constexpr const char *const black   = "\x1B[30m";
			inline constexpr const char *const red     = "\x1B[31m";
			inline constexpr const char *const green   = "\x1B[32m";
			inline constexpr const char *const yellow  = "\x1B[33m";
			inline constexpr const char *const blue    = "\x1B[34m";
			inline constexpr const char *const magenta = "\x1B[35m";
			inline constexpr const char *const cyan    = "\x1B[36m";
			inline constexpr const char *const white   = "\x1B[37m";
			inline constexpr const char *const reset   = "\x1B[39m";

			namespace bright
			{
				inline constexpr const char *const black   = "\x1B[90m";
				inline constexpr const char *const red     = "\x1B[91m";
				inline constexpr const char *const green   = "\x1B[92m";
				inline constexpr const char *const yellow  = "\x1B[93m";
				inline constexpr const char *const blue    = "\x1B[94m";
				inline constexpr const char *const magenta = "\x1B[95m";
				inline constexpr const char *const cyan    = "\x1B[96m";
				inline constexpr const char *const white   = "\x1B[97m";
			}
		}

		namespace bg
		{
			inline constexpr const char *const black   = "\x1B[40m";
			inline constexpr const char *const red     = "\x1B[41m";
			inline constexpr const char *const green   = "\x1B[42m";
			inline constexpr const char *const yellow  = "\x1B[43m";
			inline constexpr const char *const blue    = "\x1B[44m";
			inline constexpr const char *const magenta = "\x1B[45m";
			inline constexpr const char *const cyan    = "\x1B[46m";
			inline constexpr const char *const white   = "\x1B[47m";
			inline constexpr const char *const reset   = "\x1B[49m";

			namespace bright
			{
				inline constexpr const char *const black   = "\x1B[100m";
				inline constexpr const char *const red     = "\x1B[101m";
				inline constexpr const char *const green   = "\x1B[102m";
				inline constexpr const char *const yellow  = "\x1B[103m";
				inline constexpr const char *const blue    = "\x1B[104m";
				inline constexpr const char *const magenta = "\x1B[105m";
				inline constexpr const char *const cyan    = "\x1B[106m";
				inline constexpr const char *const white   = "\x1B[107m";
				inline constexpr const char *const reset   = "\x1B[109m";
			}
		}
	}

	namespace cursor
	{
		inline constexpr const char *const up    = "\x1B[A";
		inline constexpr const char *const down  = "\x1B[B";
		inline constexpr const char *const right = "\x1B[C";
		inline constexpr const char *const left  = "\x1B[D";
	}
}
