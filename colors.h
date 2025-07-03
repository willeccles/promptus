#ifndef PROMPTUS_COLORS_H
#define PROMPTUS_COLORS_H

#include <string_view>

namespace colors {

inline constexpr std::string_view kBlack{"\033[30m"};
inline constexpr std::string_view kRed{"\033[31m"};
inline constexpr std::string_view kGreen{"\033[32m"};
inline constexpr std::string_view kYellow{"\033[33m"};
inline constexpr std::string_view kBlue{"\033[34m"};
inline constexpr std::string_view kMagenta{"\033[35m"};
inline constexpr std::string_view kCyan{"\033[36m"};
inline constexpr std::string_view kWhite{"\033[37m"};
inline constexpr std::string_view kBrightBlack{"\033[90m"};
inline constexpr std::string_view kBrightRed{"\033[91m"};
inline constexpr std::string_view kBrightGreen{"\033[92m"};
inline constexpr std::string_view kBrightYellow{"\033[93m"};
inline constexpr std::string_view kBrightBlue{"\033[94m"};
inline constexpr std::string_view kBrightMagenta{"\033[95m"};
inline constexpr std::string_view kBrightCyan{"\033[96m"};
inline constexpr std::string_view kBrightWhite{"\033[97m"};

}  // namespace colors

#endif  /* PROMPTUS_COLORS_H */
