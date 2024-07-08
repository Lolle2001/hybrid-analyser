// Copyright (C) 2024 Lieuwe Huisman
#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
// #include "DataFormat.hpp"

using index_t = unsigned int;
using filename_t = std::string;

namespace Utilities {

template <class T>
void json_to_parameter(const nlohmann::json& j, const std::string key, T& target) {
    if (j.contains(key)) {
        j.at(key).get_to(target);
    } else {
        std::cout << "[WARNING]" << "JSON file does contain parameter with key: " << key << std::endl;
    }
};
// void Concatenate(std::vector<Statistics::Block> &v1, const std::vector<Statistics::Block> &v2);
// // Template functions are weird.

double igcd(double a, double b, double base);
long double GetFileSize(std::filesystem::path filepath, const int option);

std::string repeat(int n, std::string c);
nlohmann::json read_json_safe(std::filesystem::path filename);

int GetNBatch(std::string FileDirectory);
size_t get_number_of_subfolders(
    std::filesystem::path directory,
    std::filesystem::path name,
    std::string seperation_character);
namespace Statistics {
double CalculateCommonWidth(size_t n, const std::vector<double>& edges);
double isWithinBin(double x, index_t index, const std::vector<double>& edges);
void FillIndexMap(size_t n, double min, double max, double width, const std::vector<double>& edges, std::map<int, int>& indexmap);

}  // namespace Statistics

}  // namespace Utilities

#endif