#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "Utilities.hpp"

namespace Utilities {

class Progressbar {
   private:
    int barwidth;
    int width_done;
    int width_todo;
    float frac;
    int perc;
    std::string front_string;
    std::string start_char;
    std::string end_char;
    std::string done_char;
    std::string todo_char;
    int total;
    int counter = 0;

   public:
    Progressbar(int total_);

    void Initialize();
    void SetFrontString(std::string front_string_);

    void Update();

    void Print();

    void Reset();
};

};  // namespace Utilities

#endif