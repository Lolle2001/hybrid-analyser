#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <cmath>
#include <filesystem>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// #include "DataFormat.hpp"

using index_t = unsigned int;
using filename_t = std::string;

namespace Utilities {

// void Concatenate(std::vector<Statistics::Block> &v1, const std::vector<Statistics::Block> &v2);
// // Template functions are weird.

double igcd(double a, double b, double base);
long double GetFileSize(std::filesystem::path filepath, const int option);

std::string repeat(int n, std::string c);

int GetNBatch(std::string FileDirectory);

namespace Statistics {
double CalculateCommonWidth(size_t n, const std::vector<double>& edges);
double isWithinBin(double x, index_t index, const std::vector<double>& edges);
void FillIndexMap(size_t n, double min, double max, double width, const std::vector<double>& edges, std::map<int, int>& indexmap);
}  // namespace Statistics

}  // namespace Utilities

#endif