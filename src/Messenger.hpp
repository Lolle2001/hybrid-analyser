// Copyright (C) 2024 Lieuwe Huisman
#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "Utilities.hpp"

// Custom library
namespace cst {
// Manipulators
namespace man {
std::ostream &warning(std::ostream &os);
std::ostream &error(std::ostream &os);
std::ostream &done(std::ostream &os);
std::ostream &pending(std::ostream &os);
std::ostream &highlight(std::ostream &os);
std::ostream &debug(std::ostream &os);
std::ostream &success(std::ostream &os);
std::ostream &deprecation_warning(std::ostream &os);
std::ostream &critical(std::ostream &os);
std::ostream &trace(std::ostream &os);
std::ostream &prompt(std::ostream &os);
template <typename... Args>
inline void error(const std::string &format, Args &&...args) {
    fmt::print("\033[1;38;2;222;56;43m[ERROR]\033[0m {}", fmt::format(format, std::forward<Args>(args)...));
};

template <typename... Args>
inline void warning(const std::string &format, Args &&...args) {
    fmt::print("\033[1;38;2;252;127;0m[WARNING]\033[0m {}", fmt::format(format, std::forward<Args>(args)...));
}

template <typename... Args>
inline void success(const std::string &format, Args &&...args) {
    fmt::print("\033[1;38;2;57;181;74m[INFO]\033[0m {}", fmt::format(format, std::forward<Args>(args)...));
}
template <typename... Args>
inline void pending(const std::string &format, Args &&...args) {
    fmt::print("\033[1;38;2;255;199;6m[INFO]\033[0m {}", fmt::format(format, std::forward<Args>(args)...));
}
template <typename... Args>
inline void highlight(const std::string &format, Args &&...args) {
    fmt::print("\033[1;38;2;255;255;255m[INFO]\033[0m {}", fmt::format(format, std::forward<Args>(args)...));
}

}  // namespace man
// Decorators
namespace dec {
template <typename... Args>
inline std::string highlight(const std::string &format, Args &&...args) {
    return fmt::format("\033[1;38;2;255;255;255m{}\033[0m", fmt::format(format, std::forward<Args>(args)...));
}
template <typename... Args>
inline std::string pending(const std::string &format, Args &&...args) {
    return fmt::format("\033[1;38;2;255;199;6m{}\033[0m", fmt::format(format, std::forward<Args>(args)...));
}
template <typename... Args>
inline std::string success(const std::string &format, Args &&...args) {
    return fmt::format("\033[1;38;2;57;181;74m{}\033[0m", fmt::format(format, std::forward<Args>(args)...));
}
}  // namespace dec
// Colors
namespace color {
inline static const char *WARNING = "\033[1;38;2;252;127;0m";
inline static const char *STARTED = "\033[1;38;2;255;199;6m";
inline static const char *FINISHED = "\033[1;38;2;57;181;74m";
inline static const char *HIGHLIGHT = "\033[1;38;2;255;255;255m";
inline static const char *ERROR = "\033[1;38;2;222;56;43m";
inline static const char *DEBUG = "\033[1;34m";        // Blue
inline static const char *CRITICAL = "\033[1;41m";     // Red background
inline static const char *DEPRECATION = "\033[1;35m";  // Magenta
inline static const char *TRACE = "\033[1;37m";        // White
inline static const char *PROMPT = "\033[1;33m";
inline static const char *SUCCESS = "\033[1;32m";
inline static const char *RESET = "\033[0m";
inline static const char *REALBLACK = "\033[38;2;0;0;0m";
inline static const char *BLACK = "\033[38;2;1;1;1m";
inline static const char *RED = "\033[38;2;222;56;43m";
inline static const char *GREEN = "\033[38;2;57;181;74m";
inline static const char *YELLOW = "\033[38;2;255;199;6m";
inline static const char *BLUE = "\033[38;2;0;111;184m";
inline static const char *MAGENTA = "\033[38;2;118;38;113m";
inline static const char *CYAN = "\033[38;2;44;181;233m";
inline static const char *WHITE = "\033[38;2;204;204;204m";
inline static const char *REALWHITE = "\033[38;2;255;255;255m";

inline static const char *BOLD = "\033[1m";
}  // namespace color

}  // namespace cst

namespace Utilities {
struct PretyPrint {
    inline static const char *REALBLACK = "\033[38;2;0;0;0m";
    inline static const char *BLACK = "\033[38;2;1;1;1m";
    inline static const char *RED = "\033[38;2;222;56;43m";
    inline static const char *GREEN = "\033[38;2;57;181;74m";
    inline static const char *YELLOW = "\033[38;2;255;199;6m";
    inline static const char *BLUE = "\033[38;2;0;111;184m";
    inline static const char *MAGENTA = "\033[38;2;118;38;113m";
    inline static const char *CYAN = "\033[38;2;44;181;233m";
    inline static const char *WHITE = "\033[38;2;204;204;204m";
    inline static const char *REALWHITE = "\033[38;2;255;255;255m";

    inline static const char *BOLD = "\033[1m";

    inline static const char *WARNING = "\033[1;38;2;252;127;0m";
    inline static const char *STARTED = "\033[1;38;2;255;199;6m";
    inline static const char *FINISHED = "\033[1;38;2;57;181;74m";
    inline static const char *HIGHLIGHT = "\033[1;38;2;255;255;255m";
    inline static const char *ERROR = "\033[1;38;2;222;56;43m";
    inline static const char *DEBUG = "\033[1;34m";        // Blue
    inline static const char *CRITICAL = "\033[1;41m";     // Red background
    inline static const char *DEPRECATION = "\033[1;35m";  // Magenta
    inline static const char *TRACE = "\033[1;37m";        // White
    inline static const char *PROMPT = "\033[1;33m";
    inline static const char *SUCCESS = "\033[1;32m";

    inline static const char *RESET = "\033[0m";

    void Warning(const std::string &text);
    void Started(const std::string &text);
    void Finished(const std::string &text);
    void Highlight(const std::string &text);
    // void PrintFileSize(const std::string &filename);
};
}  // namespace Utilities

using PP = Utilities::PretyPrint;

#endif