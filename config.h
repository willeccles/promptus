#ifndef PROMPTUS_CONFIG_H
#define PROMPTUS_CONFIG_H

#include <string_view>

namespace config {

// The actual prompt. May be more than one character. Uses the kPrompt style.
// A space will be appended to this string.
inline constexpr std::string_view kPrompt{"♥"};

// Whether to display the PWD. Uses the kPwd style.
inline constexpr bool kShowPwd{true};

// If the PWD is displayed, display only the last part of the path. For example,
// if your PWD is /home/user/mydir, this option will show only "mydir".
inline constexpr bool kPwdBasename{true};

// If the PWD is displayed, abbreviate $HOME to ~.
inline constexpr bool kPwdAbbrevHome{true};

// Change the color of the prompt based on the exit code of the previous
// program. This only works if that value is passed as a command-line arg by
// doing something like `promptus $?`.
//
// When this is enabled, the style items kPromptErr and kPromptBg are used in
// addition to kPrompt. If the last exit status was non-zero (an error), the
// kPromptErr style is applied. If the last exit status is a platform-dependent
// value indicating that the last process was put into the background with ^Z,
// the kPromptBg style is applied. If you quit a program with ^C, this will not
// be considered an error.
inline constexpr bool kPromptStatus{true};

// Enable support for python venv prompts. This option displays the python venv
// prompt in front of the prompt. This uses the kPrefix style.
inline constexpr bool kEnablePyVenv{true};

// Items which can be styled independently.
enum class StyleItem {
  kPwd,
  kPrompt,
  kPromptErr,
  kPromptBg,
  kPrefix,
  kReset,
};

// Get the color to display for a given item.
inline constexpr std::string_view Colors(StyleItem item) {
  using std::literals::operator""sv;
  switch (item) {
    case StyleItem::kPwd:
      // Working directory.
      return "\033[32m"sv;
    case StyleItem::kPrompt:
      // Prompt.
      return "\033[35m"sv;
    case StyleItem::kPromptErr:
      // Prompt (error).
      return "\033[31m"sv;
    case StyleItem::kPromptBg:
      // Prompt (process backgrounded).
      return "\033[33m"sv;
    case StyleItem::kPrefix:
      // Prefix (e.g., Python venv).
      return "\033[34m"sv;
    case StyleItem::kReset:
      // Reset style (you probably don't need to change this).
      return "\033[m"sv;
  }
}

}  // namespace config

#endif  /* PROMPTUS_CONFIG_H */
