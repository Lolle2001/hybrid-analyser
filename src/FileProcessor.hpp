#ifndef FILEPROCESSOR_HPP
#define FILEPROCESSOR_HPP

#include <omp.h>

#include <fstream>
#include <iostream>
#include <string>

#include "DataFormat.hpp"
#include "File.hpp"
#include "Progressbar.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

struct Parameters {
    std::string ipglasma_data_folder;
    std::string iss_data_folder;
    std::string result_folder;
    std::string ampt_data_folder;
    // std::vector<int> iSSRun;
    // std::vector<int> IPGlasmaRun;
    // std::vector<int> NEvent;
};

void ReadSettings(Parameters& parameters, std::string filename);

namespace AMPT {
struct RunInfo {
    int NRun;
    int NBatchMin;
    int NBatchMax;
    size_t BatchSize;
};
void ReadFiles(int NRun, int NBatchMin, int NBatchMax, std::string Directory, Parameters& parameters, int collisiontype);
void ReadFiles(std::vector<AMPT::RunInfo> runinfo, std::string Directory, std::string OutputDirectory, Parameters& parameters, int collisiontype);
}  // namespace AMPT
namespace iSS {
struct RunInfo {
    int iSSRun;
    int IPGlasmaRun;
    int NEvent;
};
Statistics::Block_iss GetInitialStateInfo(int NRun, int eventid, Parameters& parameters);
void ReadFiles(int iSSRun, int IPGlasmaRun, int NEvent, std::string parametername, int collisiontype);
void ReadFiles(std::vector<iSS::RunInfo> runinfo, std::string OutputDirectory, std::string parametername, int collisiontype);
}  // namespace iSS

#endif