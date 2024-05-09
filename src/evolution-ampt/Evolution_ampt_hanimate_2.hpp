

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

// #include "../Histogram2D.hpp"
// #include "../HistogramMap2D.hpp"
#include "../Progressbar.hpp"
#include "Evolution_ampt_utilities.hpp"

// #include "Evolution_ampt_format.hpp"

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

    // std::vector<Particle> particles;
    TimeBlock(){};
};

// struct EventBlock {

class File {
   private:
    std::map<int, int> LabelToPythia = {{-30, -323}, {-13, -22212}, {-12, -22112}, {-11, -12212}, {-10, -12112}, {-9, -2224}, {-8, -2214}, {-7, -2114}, {-6, -1114}, {-2, -2112}, {-1, -2212}, {0, 221}, {1, 2212}, {2, 2112}, {3, -211}, {4, 111}, {5, 211}, {6, 1114}, {7, 2114}, {8, 2214}, {9, 2224}, {10, 12112}, {11, 12212}, {12, 22112}, {13, 22212}, {14, 3122}, {15, 3112}, {16, 3212}, {17, 3222}, {21, -321}, {23, 321}, {24, 311}, {25, -213}, {26, 113}, {27, 213}, {28, 223}, {29, 333}, {30, 100321}, {-14, -3122}, {-15, -3112}, {-16, -3212}, {-17, -3222}, {31, 331}, {40, 3312}, {-40, -3312}, {41, 3322}, {-41, -3322}, {45, 3334}, {-45, -3334}, {42, 1000010020}, {-42, -1000010020}, {10022, 22}};
    std::string InputDirectory;
    std::string OutputDirectory;

    double xmin = -100;
    double xmax = 100;
    size_t nx = 200;
    double ymin = -100;
    double ymax = 100;
    size_t ny = 200;

    double tmin = 0;
    double dt = 0;
    size_t nt = 0;

    double dx;
    double dy;

    std::vector<std::map<int, int>> ParticleCounts;
    std::vector<std::unique_ptr<Evolution::HistogramS2D>> ParticleEnergyDensity;
    std::vector<std::unique_ptr<TimeBlock>> TimeBlocks;

   public:
    File(std::string InputDirectory_, std::string OutputDirectory_) : InputDirectory(InputDirectory_), OutputDirectory(OutputDirectory_){};
    File(){};

    void ReadFile() {
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);
        if (file.is_open()) {
            std::string sa;
            std::istringstream iss;
            int linenumber = 1;
            double zslice = 10;

            dx = (xmax - xmin) / (nx);
            dy = (ymax - ymin) / (ny);
            double dz = zslice * 2;

            double cellsize = dx * dy * dz;

            getline(file, sa);

            iss = std::istringstream(sa);
            iss >> nt >> dt;

            size_t timecounter = 0;
            ParticleCounts.resize(nt);
            ParticleEnergyDensity.resize(nt);
            for (int i = 0; i < nt; i++) {
                ParticleEnergyDensity[i] = std::make_unique<Evolution::HistogramS2D>(xmin, xmax, nx, ymin, ymax, ny);
            }
            TimeBlocks.resize(nt);

            for (int t = 0; t < nt; ++t) {
                // std::ofstream outfile(OutputDirectory + "/hadron-energy-density-" + std::to_string(t) + ".dat");

                TimeBlock temptimeblock;

                iss = AMPT::Evolution::CGetline(file, sa);
                iss >> temptimeblock.Time;
                iss = AMPT::Evolution::CGetline(file, sa);
                iss >> temptimeblock.NumberOfParticles;
                // HistogramS2D temphisto(xmin, xmax, nx, ymin, ymax, ny);
                temptimeblock.TimeIndex = timecounter++;
                for (int p = 0; p < temptimeblock.NumberOfParticles; ++p) {
                    Particle particle;
                    iss = AMPT::Evolution::CGetline(file, sa);
                    iss >> particle;
                    particle.ParticlePythiaID = LabelToPythia[particle.ParticleLabel];
                    particle.CalculateEnergy();
                    particle.CalculateRapidity();
                    particle.CalculatePhi();
                    ParticleCounts[t][particle.ParticlePythiaID]++;
                    if (particle.PosZ > -zslice && particle.PosZ < zslice) {
                        // temphisto.Add(particle.PosX, particle.PosY, particle.Energy / cellsize);
                        ParticleEnergyDensity[t]->Add(particle.PosX, particle.PosY, particle.Energy / cellsize);
                    }

                    linenumber++;
                }
                // temphisto.PrintContents(outfile);

                TimeBlocks[t] = std::make_unique<TimeBlock>(temptimeblock);
            }
        } else {
            std::cout << "Cannot Open File: " << InputDirectory << std::endl;
        }
        file.close();
    }

    void ReadFileMulti() {
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);
        if (file.is_open()) {
            std::string sa;
            std::istringstream iss;
            int linenumber = 0;
            double zslice = 10;

            dx = (xmax - xmin) / (nx);
            dy = (ymax - ymin) / (ny);
            double dz = zslice * 2;

            double cellsize = dx * dy * dz;

            // getline(file, sa);
            // linenumber += sa.size();

            iss = Evolution::CGetline(file, sa);
            iss >> nt >> dt;

            size_t timecounter = 0;
            ParticleCounts.resize(nt);
            ParticleEnergyDensity.resize(nt);
            for (int i = 0; i < nt; i++) {
                ParticleEnergyDensity[i] = std::make_unique<Evolution::HistogramS2D>(xmin, xmax, nx, ymin, ymax, ny);
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
                // linenumber += sa.size();
                iss = AMPT::Evolution::CGetline(file, sa);
                iss >> temptimeblock.NumberOfParticles;
                // linenumber += sa.size();
                temptimeblock.TimeIndex = timecounter++;

                startline[t] = file.tellg();
                // std::cout << startline[t] << std::endl;
                TimeBlocks[t] = std::make_unique<TimeBlock>(temptimeblock);
                for (int p = 0; p < temptimeblock.NumberOfParticles; ++p) {
                    // file >> tempparticle;
                    std::getline(file, sa);
                    // file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    // iss = CGetline(file, sa);
                    // iss >> tempparticle;
                    // linenumber += sa.size();
                }
                bar.Update();
                bar.Print();
                // endline[t] = linenumber;
                // std::cout << startline[t] << " " << endline[t] << std::endl;
            }

            // int NumThreads = 12;
            std::cout << std::endl;
            bar.Reset();

#pragma omp parallel for
            for (int t = 0; t < nt; ++t) {
                int threadID = omp_get_thread_num();
                // #pragma omp critical
                //                 {
                //                     std::cout << threadID << " " << t << std::endl;
                //                 }
                std::ifstream tfile;
                tfile.open(InputDirectory.c_str(), std::ios::in);

                std::string sa;
                // GotoLine(tfile, startline[t]);
                tfile.seekg(startline[t]);
                for (int p = 0; p < TimeBlocks[t]->NumberOfParticles; ++p) {
                    Particle particle;
                    read_hadron(tfile, particle);
                    particle.ParticlePythiaID = LabelToPythia[particle.ParticleLabel];
                    particle.CalculateEnergy();
                    particle.CalculateRapidity();
                    particle.CalculatePhi();
                    ParticleCounts[t][particle.ParticlePythiaID]++;
                    if (particle.PosZ > -zslice && particle.PosZ < zslice) {
                        ParticleEnergyDensity[t]->Add(particle.PosX, particle.PosY, particle.Energy / cellsize);
                    }
                }

                bar.Update();
#pragma omp critical
                {
                    bar.Print();
                }
                //                 std::getline(tfile, sa);
                // #pragma omp critical
                //                 { std::cout << t << " " << startline[t] << " " << sa << std::endl; }

                tfile.close();
                // std::getline(file, sa);
                // std::cout << t << " " << startline[t] << " " << sa << std::endl;
                // GotoLine(file, endline[t]);
                // std::getline(file, sa);
                // std::cout << t << " " << endline[t] << " " << sa << std::endl;
            }

            std::cout << std::endl;

            // for (int t = 0; t < NumberOfTimeSteps; ++t) {
            //     std::ofstream outfile(OutputDirectory + "/hadron-energy-density-" + std::to_string(t) + ".dat");

            //     TimeBlock temptimeblock;

            //     iss = AMPT::CGetline(file, sa);
            //     iss >> temptimeblock.Time;
            //     iss = AMPT::CGetline(file, sa);
            //     iss >> temptimeblock.NumberOfParticles;

            //     temptimeblock.TimeIndex = timecounter++;

            //     HistogramS2D temphisto(xmin, xmax, nx, ymin, ymax, ny);
            //     for (int p = 0; p < temptimeblock.NumberOfParticles; ++p) {
            //         Particle particle;
            //         iss = AMPT::CGetline(file, sa);
            //         iss >> particle;
            //         particle.ParticlePythiaID = LabelToPythia[particle.ParticleLabel];
            //         particle.CalculateEnergy();
            //         particle.CalculateRapidity();
            //         particle.CalculatePhi();
            //         ParticleCounts[t][particle.ParticlePythiaID]++;
            //         if (particle.PosZ > -zslice && particle.PosZ < zslice) {
            //             temphisto.Add(particle.PosX, particle.PosY, particle.Energy / cellsize);
            //         }

            //         linenumber++;
            //     }
            //     temphisto.PrintContents(outfile);

            //     TimeBlocks[t] = std::make_unique<TimeBlock>(temptimeblock);
            // }
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

        output << std::setw(6) << std::right << "#itau"
               << " ";
        output << std::setw(6) << "tau"
               << " ";
        for (auto &entry : pids) {
            output << std::setw(13) << std::right << entry << " ";
        }
        output << std::endl;
        for (int i = 0; i < ParticleCounts.size(); ++i) {
            output << std::setw(6) << std::right << i << " ";
            output << std::setw(6) << std::right << TimeBlocks[i]->Time << " ";
            for (auto &entry : pids) {
                output << std::setw(13) << std::right << ParticleCounts[i][entry] << " ";
            }
            output << std::endl;
        }
    }

    void PrintParticleEnergyDensity(std::string Directory) {
#pragma omp parallel for
        for (int i = 0; i < nt; ++i) {
            std::ofstream file(Directory + "/hadron-energy-density-" + std::to_string(i) + ".dat");
            ParticleEnergyDensity[i]->PrintContents(file);
            file.close();
        }
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