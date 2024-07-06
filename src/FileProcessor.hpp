// Copyright (C) 2024 Lieuwe Huisman
#ifndef FILEPROCESSOR_HPP
#define FILEPROCESSOR_HPP

#include <omp.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "DataFormat.hpp"
#include "File.hpp"
#include "Progressbar.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

using size_s = unsigned int;
using index_t = unsigned int;

struct Parameters {
    std::string ipglasma_data_folder;
    std::string iss_data_folder;
    std::string result_folder;
    std::string ampt_data_folder;

    nlohmann::json jsonmap;
    // std::vector<int> iSSRun;
    // std::vector<int> IPGlasmaRun;
    // std::vector<int> NEvent;
    void ReadSettings(std::string filename);
    void ReadSettingsJSON(std::string filename);
};

namespace AMPT {
struct RunInfo {
    int NRun;
    int NBatchMin;
    int NBatchMax;
    size_t BatchSize;
};
void ReadFiles(std::vector<AMPT::RunInfo> runinfo, std::string Directory, std::string OutputDirectory, Parameters& parameters, int collisiontype);
}  // namespace AMPT
namespace iSS {
struct RunInfo {
    int iSSRun;
    int IPGlasmaRun;
    size_s NEvent;
};
Statistics::Block_iss GetInitialStateInfo(int NRun, int eventid, Parameters& parameters);
Statistics::Block_iss GetInitialStateInfo(std::string);
Statistics::Block_iss GetInitialStateInfo(std::filesystem::path);
void ReadFiles(std::vector<iSS::RunInfo> runinfo, std::string OutputDirectory, Parameters& parameters, int collisiontype);
}  // namespace iSS

#endif
