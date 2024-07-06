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

    inline static const char *WARNING = "\033[1;38;2;255;0;0m";
    inline static const char *STARTED = "\033[1;38;2;255;199;6m";
    inline static const char *FINISHED = "\033[1;38;2;57;181;74m";
    inline static const char *HIGHLIGHT = "\033[1;38;2;255;255;255m";

    inline static const char *RESET = "\033[0m";

    void Warning(const std::string &text);
    void Started(const std::string &text);
    void Finished(const std::string &text);
    void Highlight(const std::string &text);
    // void PrintFileSize(const std::string &filename);
};
}  // namespace Utilities

#endif