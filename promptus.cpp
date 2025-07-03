#include <array>
#include <charconv>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <pwd.h>
#include <span>
#include <string_view>
#include <sys/types.h>
#include <sys/utsname.h>

#include <fmt/format.h>

#include "config.h"

using namespace std::literals;
using config::StyleItem;

// BACKGROUND_CODE is the exit status of a program that's
// been backgrounded. If you're unsure, try running something
// like vim, doing control-z, and then 'echo $?'.
#ifndef BACKGROUND_CODE
# ifdef __APPLE__ // macOS
#  define BACKGROUND_CODE 146
# else // Linux, presumably
#  define BACKGROUND_CODE 148
# endif
#endif

static std::optional<std::string_view> GetEnv(const char* var) {
  if (const char* v = std::getenv(var)) {
    return std::string_view{v};
  }
  return std::nullopt;
}

static bool SameFile(std::string_view a, std::string_view b) {
  std::error_code ec{};
  const bool eq = std::filesystem::equivalent(a, b, ec);
  if (ec) {
    return false;
  }
  return eq;
}

static std::string_view GetRealCwd(std::span<char> buf) {
  if (auto pwd = GetEnv("PWD"); pwd && SameFile("."sv, *pwd)) {
    pwd->copy(buf.data(), buf.size());
    return std::string_view{buf.data(), pwd->size()};
  } else {
    if (auto cwd = ::getcwd(buf.data(), buf.size())) {
      return cwd;
    }
    return {};
  }
}

constexpr std::string_view BaseName(std::string_view path) {
  const auto pos = path.rfind('/');
  if (pos != std::string_view::npos) {
    path.remove_prefix(pos + 1);
  }
  return path;
}

int main(int argc, char** argv) {
  std::string_view lescape, rescape, prefix;

  if (auto shell = GetEnv("SHELL")) {
    if (shell->ends_with("zsh"sv)) {
      lescape = "%{"sv;
      rescape = "%}"sv;
    } else if (shell->ends_with("bash"sv)) {
      lescape = "\\["sv;
      rescape = "\\]"sv;
    }
  }

  int laststatus = 0;
  if constexpr (config::kPromptStatus) {
    if (argc > 1) {
      const std::string_view arg{argv[1]};
      static_cast<void>(std::from_chars(arg.data(), arg.data() + arg.size(),
                                        laststatus));
    }
  }

  if constexpr (config::kEnablePyVenv) {
    prefix = GetEnv("VIRTUAL_ENV_PROMPT").value_or(""sv);
  }

  fmt::print("{}{}{}{}",
             lescape, Colors(StyleItem::kPrefix), rescape, prefix);
  if (!prefix.empty() && prefix.back() != ' ') {
    fmt::print(" ");
  }

  if constexpr (config::kShowUserAndHost) {
    struct ::passwd* pw = ::getpwuid(::getuid());
    struct ::utsname un;
    if (pw && ::uname(&un) != -1) {
      fmt::print("{2}{4}{3}{0}@{1}{2}{5}{3}:",
                 pw->pw_name,                 // 0
                 un.nodename,                 // 1
                 lescape,                     // 2
                 rescape,                     // 3
                 Colors(StyleItem::kUser),    // 4
                 Colors(StyleItem::kReset));  // 5
    }
  }

  if constexpr (config::kShowPwd) {
    std::array<char, PATH_MAX> pwd_buf{};
    auto pwd = GetRealCwd(std::span{pwd_buf.data(), pwd_buf.size() - 1});

    if constexpr (config::kPwdAbbrevHome) {
      if (auto home = GetEnv("HOME")) {
        if (SameFile(pwd, *home)) {
          pwd = "~"sv;
        } else {
          if constexpr (!config::kPwdBasename) {
            if (pwd.starts_with(*home)) {
              pwd_buf[home->size() - 1] = '~';
              pwd.remove_prefix(home->size() - 1);
            }
          }
        }
      }
    }

    if constexpr (config::kPwdBasename) {
      pwd = BaseName(pwd);
    }

    fmt::print("{}{}{}{}{}{}{} ",
               lescape, Colors(StyleItem::kPwd), rescape,
               pwd,
               lescape, Colors(StyleItem::kReset), rescape);
  }

  std::string_view pcolor = Colors(StyleItem::kPrompt);

  if constexpr (config::kPromptStatus) {
    if (laststatus == 0 || laststatus == 130) {
      pcolor = Colors(StyleItem::kPrompt);
    } else if (laststatus == BACKGROUND_CODE) {
      pcolor = Colors(StyleItem::kPromptBg);
    } else {
      pcolor = Colors(StyleItem::kPromptErr);
    }
  }

  fmt::print("{}{}{}{}{}{}{} ",
             lescape, pcolor, rescape,
             config::kPrompt,
             lescape, Colors(StyleItem::kReset), rescape);
}
