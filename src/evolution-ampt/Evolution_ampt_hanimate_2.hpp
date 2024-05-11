

#ifndef EVOLUTION_AMPT_HANIMATE_2_HPP
#define EVOLUTION_AMPT_HANIMATE_2_HPP

#include <omp.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../Progressbar.hpp"
#include "Evolution_ampt_utilities.hpp"

namespace AMPT {
namespace Evolution {
namespace Hadron {

std::istream &read_hadron(std::istream &input, Evolution::Particle &particle) {
    input >> particle.ParticleLabel;
    input >> particle.PosX;
    input >> particle.PosY;
    input >> particle.PosZ;
    input >> particle.MomX;
    input >> particle.MomY;
    input >> particle.MomZ;
    input >> particle.Mass;
    return input;
}

struct TimeBlock {
    int TimeIndex;
    double Time;
    int NumberOfParticles;

    TimeBlock(){};
};

class File {
   private:
    std::map<int, int> LabelToPythia = {{-30, -323}, {-13, -22212}, {-12, -22112}, {-11, -12212}, {-10, -12112}, {-9, -2224}, {-8, -2214}, {-7, -2114}, {-6, -1114}, {-2, -2112}, {-1, -2212}, {0, 221}, {1, 2212}, {2, 2112}, {3, -211}, {4, 111}, {5, 211}, {6, 1114}, {7, 2114}, {8, 2214}, {9, 2224}, {10, 12112}, {11, 12212}, {12, 22112}, {13, 22212}, {14, 3122}, {15, 3112}, {16, 3212}, {17, 3222}, {21, -321}, {23, 321}, {24, 311}, {25, -213}, {26, 113}, {27, 213}, {28, 223}, {29, 333}, {30, 100321}, {-14, -3122}, {-15, -3112}, {-16, -3212}, {-17, -3222}, {31, 331}, {40, 3312}, {-40, -3312}, {41, 3322}, {-41, -3322}, {45, 3334}, {-45, -3334}, {42, 1000010020}, {-42, -1000010020}, {10022, 22}};
    std::string InputDirectory;
    std::string OutputDirectory;

    double xmin = -25;
    double xmax = 25;
    size_t nx = 50;
    double ymin = -25;
    double ymax = 25;
    size_t ny = 50;

    double tmin = 0;
    double dt = 0;
    size_t nt = 0;

    double zmin_s = -1;
    double zmax_s = 1;
    size_t nz_s = 1;

    double zmin = -25;
    double zmax = 25;
    size_t nz = 50;

    double dx;
    double dy;
    double dz_s;
    double dz;

    std::vector<std::map<int, int>> ParticleCounts;
    std::vector<std::unique_ptr<Evolution::HistogramS2D>> ParticleEnergyDensity;
    std::vector<std::unique_ptr<Evolution::HistogramS3D>> EnergyDensity3D;
    std::vector<std::unique_ptr<TimeBlock>> TimeBlocks;

   public:
    File(std::string InputDirectory_, std::string OutputDirectory_) : InputDirectory(InputDirectory_), OutputDirectory(OutputDirectory_){};
    File(){};

    void ReadFileMulti() {
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);
        if (file.is_open()) {
            std::string sa;
            std::istringstream iss;
            int linenumber = 1;
            // double zslice = 10;

            dx = (xmax - xmin) / (nx);
            dy = (ymax - ymin) / (ny);
            dz_s = (zmax_s - zmin_s) / (nz_s);
            dz = (zmax - zmin) / (nz);

            double cellsize_s = dx * dy * dz_s;
            double cellsize = dx * dy * dz;

            iss = Evolution::CGetline(file, sa);
            iss >> nt >> dt;
            linenumber++;
            size_t timecounter = 0;
            ParticleCounts.resize(nt);
            ParticleEnergyDensity.resize(nt);
            EnergyDensity3D.resize(nt);
            for (int i = 0; i < nt; i++) {
                ParticleEnergyDensity[i] = std::make_unique<Evolution::HistogramS2D>(xmin, xmax, nx, ymin, ymax, ny);
                EnergyDensity3D[i] = std::make_unique<Evolution::HistogramS3D>(xmin, xmax, nx, ymin, ymax, ny, zmin, zmax, nz);
            }
            TimeBlocks.resize(nt);
            Particle tempparticle;

            std::vector<int> startline(nt);
            std::vector<int> endline(nt);

            Utilities::Progressbar bar(nt);
            bar.Print();

            for (int t = 0; t < nt; ++t) {
                TimeBlock temptimeblock;

                iss = AMPT::Evolution::CGetline(file, sa);
                iss >> temptimeblock.Time;
                iss = AMPT::Evolution::CGetline(file, sa);
                iss >> temptimeblock.NumberOfParticles;
                temptimeblock.TimeIndex = timecounter++;

                linenumber++;
                linenumber++;

                startline[t] = file.tellg();
                endline[t] = linenumber;

                TimeBlocks[t] = std::make_unique<TimeBlock>(temptimeblock);
                for (int p = 0; p < temptimeblock.NumberOfParticles; ++p) {
                    std::getline(file, sa);
                    linenumber++;
                }

                bar.Update();
                bar.Print();
            }

            std::cout << std::endl;
            bar.Reset();

            int nthread = omp_get_max_threads();

            std::vector<std::map<int, int>> ThreadLabelToPythia(nthread, LabelToPythia);

#pragma omp parallel for num_threads(nthread) schedule(dynamic)
            for (int t = 0; t < nt; ++t) {
                int threadID = omp_get_thread_num();

                std::ifstream tfile;
                std::istringstream iss;
                tfile.open(InputDirectory.c_str(), std::ios::in);

                std::string sa;

                tfile.seekg(startline[t]);
                for (int p = 0; p < TimeBlocks[t]->NumberOfParticles; ++p) {
                    Particle particle;

                    read_hadron(tfile, particle);

                    particle.ParticlePythiaID = ThreadLabelToPythia[threadID][particle.ParticleLabel];
                    particle.CalculateEnergy();
                    ParticleCounts[t][particle.ParticlePythiaID]++;
                    if (particle.PosZ >= zmin_s && particle.PosZ <= zmax_s) {
                        ParticleEnergyDensity[t]->Add(particle.PosX, particle.PosY, particle.Energy / cellsize_s);
                    }
                    EnergyDensity3D[t]->Add(particle.PosX, particle.PosY, particle.PosZ, particle.Energy / cellsize);
                }

                bar.Update();
#pragma omp critical
                {
                    bar.Print();
                }

                tfile.close();
            }

            std::cout << std::endl;

        } else {
            std::cout << "Cannot Open File: " << InputDirectory << std::endl;
        }
        file.close();
    }

    void PrintTimeBlocks() {
        std::cout << "\033[1;97;48m" << std::setw(13) << std::left << "index-tau"
                  << "| "
                  << "\033[0m";
        std::cout << "\033[1;97;48m" << std::setw(13) << std::left << "tau"
                  << "| "
                  << "\033[0m";
        std::cout << "\033[1;97;48m" << std::setw(21) << std::left << "number of particles"
                  << "| "
                  << "\033[0m";
        std::cout << std::endl;
        for (int i = 0; i < TimeBlocks.size(); ++i) {
            std::cout << std::setw(13) << std::left << TimeBlocks[i]->TimeIndex << "| ";
            std::cout << std::setw(13) << std::left << TimeBlocks[i]->Time << "| ";
            std::cout << std::setw(21) << std::left << TimeBlocks[i]->NumberOfParticles << "| ";
            std::cout << std::endl;
        }
    }

    void PrintParticleCounts(std::ostream &output) {
        std::vector<int> pids = {-323, -22212, -22112, -12212, -12112, -2224, -2214, -2114, -1114, -2112, -2212, 221, 2212, 2112, -211, 111, 211, 1114, 2114, 2214, 2224, 12112, 12212, 22112, 22212, 3122, 3112, 3212, 3222, -321, 321, 311, -213, 113, 213, 223, 333, 100321, -3122, -3112, -3212, -3222, 331, 3312, -3312, 3322, -3322, 3334, -3334, 1000010020, -1000010020, 22};

        output << std::setw(6) << std::right << "#itau" << " ";
        output << std::setw(6) << "tau" << " ";
        output << std::setw(13) << std::right << "total" << " ";
        for (auto &entry : pids) {
            output << std::setw(13) << std::right << entry << " ";
        }
        output << std::endl;
        for (int i = 0; i < ParticleCounts.size(); ++i) {
            output << std::setw(6) << std::right << i << " ";
            output << std::setw(6) << std::right << TimeBlocks[i]->Time << " ";
            size_t total = 0;
            for (auto &entry : pids) {
                total += ParticleCounts[i][entry];
            }
            output << std::setw(13) << std::right << total << " ";
            for (auto &entry : pids) {
                output << std::setw(13) << std::right << ParticleCounts[i][entry] << " ";
            }
            output << std::endl;
        }
    }

    void PrintParticleEnergyDensity(std::string Directory) {
        Utilities::Progressbar bar(nt);
        bar.Print();
#pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < nt; ++i) {
            std::ofstream file;
            file.open(Directory + "/hadron-energy-density-" + std::to_string(i) + ".dat");
            ParticleEnergyDensity[i]->PrintContents(file);
            file.close();
            file.open(Directory + "/hadron-energy-density-3D-" + std::to_string(i) + ".dat");
            EnergyDensity3D[i]->PrintContents(file);
            file.close();
            bar.Update();
#pragma omp critical
            {
                bar.Print();
            }
        }
        std::cout << std::endl;
        std::ofstream file;
        file.open(Directory + "/hadron-time.dat");
        for (int i = 0; i < nt; ++i) {
            file << TimeBlocks[i]->Time << "\n";
        }
        file.close();
    }

    void PrintInfo(std::ostream &output) {
        output << nt << " " << nx << " " << ny << std::endl;
        output << dt << " " << dx << " " << dy << std::endl;
        output << tmin << " " << xmin << " " << xmax;
    }
};
}  // namespace Hadron
}  // namespace Evolution
}  // namespace AMPT

#endif