#include "Progressbar.hpp"

namespace Utilities {

Progressbar::Progressbar(int total_) : total(total_),
                                       barwidth(60),
                                       front_string(""),
                                       start_char("["),
                                       end_char("] "),
                                       done_char("#"),
                                       todo_char("-"){};

void Progressbar::Initialize() {
}
void Progressbar::SetFrontString(std::string front_string_) {
    front_string = front_string_;
}
void Progressbar::SetStartChar(std::string x) {
    start_char = x;
}
void Progressbar::SetEndChar(std::string x) {
    end_char = x;
}
void Progressbar::SetDoneChar(std::string x) {
    done_char = x;
}
void Progressbar::SetTodoChar(std::string x) {
    todo_char = x;
}
void Progressbar::SetBarWidth(int x) {
    barwidth = x;
}

void Progressbar::Update() {
#pragma omp atomic
    counter++;
}

void Progressbar::Print() {
    frac = (float)counter / total;
    perc = (int)(frac * 100);
    width_done = (int)(frac * barwidth);
    width_todo = barwidth - width_done;
    std::cout << front_string;
    std::cout << start_char;
    std::cout << std::setw(width_done) << std::left << Utilities::repeat(width_done, done_char);
    std::cout << std::setw(width_todo) << std::left << Utilities::repeat(width_todo, todo_char);
    std::cout << end_char;
    std::cout << std::setw(3) << std::right << perc;
    std::cout << "%\r";
    std::cout.flush();
}

void Progressbar::Reset() {
    frac = 0;
    perc = 0;
    counter = 0;
}

};  // namespace Utilities
