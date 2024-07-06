// Copyright (C) 2024 Lieuwe Huisman

#include "Timer.hpp"

namespace Utilities {

// Duration::Duration(std::chrono::duration<int64_t, std::nano> &duration_) : duration(duration_){};
// Duration::Duration(
//     std::chrono::time_point<std::chrono::high_resolution_clock> &start_,
//     std::chrono::time_point<std::chrono::high_resolution_clock> &stop_) : start(start_), stop(stop_)
// {
//     GetDuration();
// };
// Duration::Duration(
//     std::chrono::time_point<std::chrono::high_resolution_clock> &start_,
//     std::chrono::time_point<std::chrono::high_resolution_clock> &stop_, char option) : start(start_), stop(stop_)
// {
//     GetDuration();
//     GetCounts(option);
// };

Duration::Duration(char option_) {
    option = option_;
}

void Duration::Start() {
    start = Clock::now();
}
void Duration::Stop() {
    stop = Clock::now();
    GetDuration();
    GetCounts(option);
}

void Duration::GetCounts(char option) {
    if (option == 'H') {
        hours = std::chrono::duration_cast<std::chrono::hours>(duration);
        duration -= hours;
        minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
        duration -= minutes;
        seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        chours = (unsigned long int)hours.count();
        cminutes = (unsigned long int)minutes.count();
        cseconds = (unsigned long int)seconds.count();
        cmilliseconds = (unsigned long int)milliseconds.count();
    } else if (option == 'M') {
        minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
        duration -= minutes;
        seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

        cminutes = (unsigned long int)minutes.count();
        cseconds = (unsigned long int)seconds.count();
        cmilliseconds = (unsigned long int)milliseconds.count();
    } else if (option == 'S') {
        seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

        cseconds = (unsigned long int)seconds.count();
        cmilliseconds = (unsigned long int)milliseconds.count();
    }
}

void Duration::GetDuration() {
    duration = stop - start;
}
};  // namespace Utilities
