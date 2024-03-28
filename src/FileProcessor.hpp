#ifndef FILEPROCESSOR_HPP
#define FILEPROCESSOR_HPP

#include <omp.h>

#include <fstream>
#include <iostream>
#include <string>

#include "DataFormat.hpp"
#include "File.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

namespace AMPT {
void ReadFiles(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int collisiontype);
}
namespace iSS {
struct Parameters {
    std::string ipglasma_data_folder;
    std::string iss_data_folder;
    std::string result_folder;
    std::vector<int> iSSRun;
    std::vector<int> IPGlasmaRun;
    std::vector<int> NEvent;
};
void ReadSettings(Parameters& parameters, std::string filename);
Statistics::Block_iss GetInitialStateInfo(int NRun, int eventid, Parameters& parameters);
void ReadFiles(int iSSRun, int IPGlasmaRun, int NEvent, std::string parametername, int collisiontype);
}  // namespace iSS

#endif