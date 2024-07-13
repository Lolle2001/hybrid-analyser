#include <fmt/core.h>

#include <chrono>
#include <iostream>
#include <string>

namespace cst {
namespace man {

// Error message formatter
template <typename... Args>
inline void error(const std::string& format, Args&&... args) {
    fmt::print("\033[1;31m[ERROR]\033[0m {}\n", fmt::format(format, std::forward<Args>(args)...));
}

}  // namespace man
}  // namespace cst

void benchmark_std_cout(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::cout << "\033[1;31m[ERROR]\033[0m " << "Iteration " << i << ": One or more input files do not exist!" << std::endl;
    }
}

void benchmark_fmt_print(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        cst::man::error("Iteration {}: One or more input files do not exist!", i);
    }
}

int test() {
    const int iterations = 100000;  // Adjust this for longer tests

    // Benchmark std::cout
    auto start_cout = std::chrono::high_resolution_clock::now();
    benchmark_std_cout(iterations);
    auto end_cout = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_cout = end_cout - start_cout;

    // Benchmark cst::man::error
    auto start_fmt = std::chrono::high_resolution_clock::now();
    benchmark_fmt_print(iterations);
    auto end_fmt = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_fmt = end_fmt - start_fmt;
    std::cout << "std::cout took " << duration_cout.count() << " seconds.\n";
    std::cout << "cst::man::error took " << duration_fmt.count() << " seconds.\n";

    return 0;
}
