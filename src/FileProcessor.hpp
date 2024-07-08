// Copyright (C) 2024 Lieuwe Huisman
#ifndef FILEPROCESSOR_HPP
#define FILEPROCESSOR_HPP
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>

#include "File.hpp"
#include "Progressbar.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

namespace AMPT {

void ProcessFiles(
    std::vector<std::filesystem::path> datafiles,
    std::vector<std::filesystem::path> logfiles,
    unsigned int collisiontype,
    std::filesystem::path output_directory);

}  // namespace AMPT

namespace iSS {

Statistics::Block_iss GetInitialStateInfo(std::filesystem::path filename);
void ProcessFiles(
    std::vector<std::filesystem::path> datafiles,
    std::vector<std::filesystem::path> logfiles,
    unsigned int collisiontype,
    std::filesystem::path output_directory);
}  // namespace iSS

#endif
