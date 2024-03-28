#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "DataFormat.hpp"

namespace Utilities {

// void Concatenate(std::vector<Statistics::Block> &v1, const std::vector<Statistics::Block> &v2);
// // Template functions are weird.

double igcd(double a, double b, double base);
long double GetFileSize(std::filesystem::path filepath, const int option);

std::string repeat(int n, std::string c);

int GetNBatch(std::string FileDirectory);

}  // namespace Utilities

#endif