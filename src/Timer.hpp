#ifndef TIMER_HPP
#define TIMER_HPP
#include <chrono>

namespace Utilities {

struct Duration {
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

    std::chrono::nanoseconds duration;
    TimePoint start;
    TimePoint stop;

    char option;

    unsigned long int cnanoseconds;
    unsigned long int cmicroseconds;
    unsigned long int cmilliseconds;
    unsigned long int cseconds;
    unsigned long int cminutes;
    unsigned long int chours;

    std::chrono::nanoseconds nanoseconds;

    std::chrono::microseconds microseconds;

    std::chrono::milliseconds milliseconds;

    std::chrono::seconds seconds;

    std::chrono::minutes minutes;

    std::chrono::hours hours;

    // Duration(std::chrono::duration<int64_t, std::nano> &duration_);
    // Duration(TimePoint &start_,TimePoint &stop_);
    // Duration(TimePoint &start_,TimePoint &stop_, char option);

    Duration(char option);

    void Start();

    void Stop();

    void GetCounts(char option);

   private:
    void GetDuration();
};
};  // namespace Utilities

#endif