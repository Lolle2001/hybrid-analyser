

#ifndef EVOLUTION_AMPT_PANIMATE_2_H
#define EVOLUTION_AMPT_PANIMATE_2_H
#include <omp.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../Histogram2D.hpp"
#include "../Progressbar.hpp"
#include "Evolution_ampt_pfinalft_2.hpp"
#include "Evolution_ampt_utilities.hpp"

namespace AMPT {
namespace Evolution {
namespace Parton {

std::istream &read_parton(std::istream &input, Evolution::Particle &particle) {
    input >> particle.ParticlePythiaID;
    input >> particle.PosX;
    input >> particle.PosY;
    input >> particle.PosZ;
    input >> particle.PosT;
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

struct CountMap {
    std::map<int, size_t> Map = {
        {-1, 0},
        {1, 0},
        {-2, 0},
        {2, 0},
        {-3, 0},
        {3, 0},
        {-4, 0},
        {4, 0},
        {-5, 0},
        {5, 0},
        {-6, 0},
        {6, 0}};
    CountMap(){

    };

    void Add(int pythiaid) {
        Map[pythiaid]++;
    }

    void Write(std::ostream &output) {
        output << std::setw(6) << std::right << Map[-1] << " ";
        output << std::setw(6) << std::right << Map[1] << " ";
        output << std::setw(6) << std::right << Map[-2] << " ";
        output << std::setw(6) << std::right << Map[2] << " ";
        output << std::setw(6) << std::right << Map[-3] << " ";
        output << std::setw(6) << std::right << Map[3] << " ";
        output << std::setw(6) << std::right << Map[-4] << " ";
        output << std::setw(6) << std::right << Map[4] << " ";
        output << std::setw(6) << std::right << Map[-5] << " ";
        output << std::setw(6) << std::right << Map[5] << " ";
        output << std::setw(6) << std::right << Map[-6] << " ";
        output << std::setw(6) << std::right << Map[6] << " ";
    }

    friend std::ostream &operator<<(std::ostream &output, CountMap &obj) {
        // output << std::setw(3) << std::right << -1 << " ";
        output << std::setw(5) << std::right << obj.Map[-1] << " ";
        // output << std::setw(3) << std::right << 1 << " ";
        output << std::setw(5) << std::right << obj.Map[1] << " ";
        // output << std::setw(3) << std::right << -2 << " ";
        output << std::setw(5) << std::right << obj.Map[-2] << " ";
        // output << std::setw(3) << std::right << 2 << " ";
        output << std::setw(5) << std::right << obj.Map[2] << " ";
        // output << std::setw(3) << std::right << -3 << " ";
        output << std::setw(5) << std::right << obj.Map[-3] << " ";
        // output << std::setw(3) << std::right << 3 << " ";
        output << std::setw(5) << std::right << obj.Map[3] << " ";
        // output << std::setw(3) << std::right << -4 << " ";
        output << std::setw(5) << std::right << obj.Map[-4] << " ";
        // output << std::setw(3) << std::right << 4 << " ";
        output << std::setw(5) << std::right << obj.Map[4] << " ";
        // output << std::setw(3) << std::right << -5 << " ";
        output << std::setw(5) << std::right << obj.Map[-5] << " ";
        // output << std::setw(3) << std::right << 5 << " ";
        output << std::setw(5) << std::right << obj.Map[5] << " ";
        // output << std::setw(3) << std::right << -6 << " ";
        output << std::setw(5) << std::right << obj.Map[-6] << " ";
        // output << std::setw(3) << std::right << 6 << " ";
        output << std::setw(5) << std::right << obj.Map[6] << " ";
        return output;
    }
};

/*
ana1/p-animate.dat
*/
class File {
   private:
    std::string InputDirectory;
    std::string OutputDirectory;

    double xmin = -100;
    double xmax = 100;
    size_t nx = 200;
    double ymin = -100;
    double ymax = 100;
    size_t ny = 200;

    std::vector<double> time;
    size_t nt = 0;

    double dx;
    double dy;

   public:
    std::vector<CountMap> ParticleCounts;
    std::vector<std::unique_ptr<Evolution::HistogramS2D>> ParticleEnergyDensity;
    std::vector<std::unique_ptr<TimeBlock>> TimeBlocks;

    File(std::string InputDirectory_) : InputDirectory(InputDirectory_){};

    void Parse(std::shared_ptr<AMPT::Evolution::Parton::Freezeout::File> finalft) {
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);

        if (file.is_open()) {
            std::string sa;
            std::istringstream iss;

            double zslice = 10;

            dx = (xmax - xmin) / (nx);
            dy = (ymax - ymin) / (ny);
            double dz = zslice * 2;

            double cellsize = dx * dy * dz;

            std::vector<int> startline;
            size_t timecounter = 0;

            while (true) {
                TimeBlock temptimeblock;
                iss = CGetline(file, sa);
                iss >> temptimeblock.Time;
                if (temptimeblock.Time == -10) {
                    break;
                }
                iss = CGetline(file, sa);
                iss >> temptimeblock.NumberOfParticles;

                temptimeblock.TimeIndex = timecounter++;

                startline.push_back(file.tellg());

                TimeBlocks.push_back(std::make_unique<TimeBlock>(temptimeblock));
                for (int p = 0; p < temptimeblock.NumberOfParticles; ++p) {
                    std::getline(file, sa);
                }
            }
            // std::cout << "hello" << std::endl;
            nt = TimeBlocks.size();
            // std::cout << nt << std::endl;
            // std::cout << startline.size() << std::endl;
            ParticleCounts.resize(nt);
            ParticleEnergyDensity.resize(nt);
            for (int i = 0; i < nt; i++) {
                ParticleEnergyDensity[i] = std::make_unique<Evolution::HistogramS2D>(xmin, xmax, nx, ymin, ymax, ny);
            }

            size_t nthread = omp_get_max_threads();
            // std::cout << nthread << std::endl;
            std::vector<std::shared_ptr<AMPT::Evolution::Parton::Freezeout::File>> freezeoutmap(nthread, finalft);

            Utilities::Progressbar bar(nt);
            bar.Print();

#pragma omp parallel for num_threads(nthread)
            for (int t = 0; t < nt; ++t) {
                std::ifstream tfile;
                tfile.open(InputDirectory, std::ios::in);
                tfile.seekg(startline[t]);
                std::pair<int, double> temppair;

                int threadid = omp_get_thread_num();
                // std::getline(tfile, sa);
                // std::cout << sa << std::endl;

                for (int p = 0; p < TimeBlocks[t]->NumberOfParticles; ++p) {
                    Particle particle;
                    read_parton(tfile, particle);
                    temppair = std::make_pair(particle.ParticlePythiaID, particle.PosT);
                    if (!freezeoutmap[threadid]->isFrozenOut(temppair)) {
                        // if (particle.PosT > TimeBlocks[t]->Time) {
                        // std::cout << particle.PosT << " " << TimeBlocks[t]->Time << std::endl;
                        particle.CalculateEnergy();
                        particle.CalculateRapidity();
                        particle.CalculatePhi();
                        ParticleCounts[t].Add(particle.ParticlePythiaID);
                        if (particle.PosZ > -zslice && particle.PosZ < zslice) {
                            ParticleEnergyDensity[t]->Add(particle.PosX, particle.PosY, particle.Energy / cellsize);
                        }
                    }
                }

                bar.Update();
#pragma omp critical
                {
                    bar.Print();
                }
            }
            std::cout << std::endl;
            // std::cout << "done" << std::endl;
        } else {
            std::cout << "Cannot Open File: " << InputDirectory << std::endl;
        }
        file.close();
    }

    void
    PrintPartonEnergyDensity(std::string Directory) {
#pragma omp parallel for
        for (int i = 0; i < ParticleEnergyDensity.size(); ++i) {
            std::ofstream file(Directory + "/parton-energy-density-" + std::to_string(i) + ".dat");
            ParticleEnergyDensity[i]->PrintContents(file);
            file.close();
        }
        // std::cout << "done" << std::endl;
    }

    void PrintInfo(std::ostream &output) {
        output << nx << " " << ny << std::endl;
        output << dx << " " << dy << std::endl;
        output << xmin << " " << xmax << std::endl;
        for (int i = 0; i < TimeBlocks.size(); ++i) {
            output << TimeBlocks[i]->Time << " ";
        }
    }

    void Write(std::ofstream &File) {
        // std::ofstream File;
        // std::string FileName = Directory + std::to_string(NRun) + "/panimate_summary.dat";
        // File.open((FileName).c_str(), std::ios::out);
        std::vector<int> pids = {-1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6};
        File << std::setw(1) << std::left << "#" << " ";
        File << std::setw(5) << std::right << "itau" << " ";
        File << std::setw(13) << std::right << "tau" << " ";
        File << std::setw(10) << std::right << "N[partons]" << " ";
        File << std::setw(6) << std::right << "N[-1]" << " ";
        File << std::setw(6) << std::right << "N[ 1]" << " ";
        File << std::setw(6) << std::right << "N[-2]" << " ";
        File << std::setw(6) << std::right << "N[ 2]" << " ";
        File << std::setw(6) << std::right << "N[-3]" << " ";
        File << std::setw(6) << std::right << "N[ 3]" << " ";
        File << std::setw(6) << std::right << "N[-4]" << " ";
        File << std::setw(6) << std::right << "N[ 4]" << " ";
        File << std::setw(6) << std::right << "N[-5]" << " ";
        File << std::setw(6) << std::right << "N[ 5]" << " ";
        File << std::setw(6) << std::right << "N[-6]" << " ";
        File << std::setw(6) << std::right << "N[ 6]" << std::endl;
        File << std::setw(1) << std::left << "#" << " ";
        File << std::setw(5) << std::right << "itau" << " ";
        File << std::setw(13) << std::right << "time" << " ";
        File << std::setw(10) << std::right << "total" << " ";
        File << std::setw(6) << std::right << -1 << " ";
        File << std::setw(6) << std::right << 1 << " ";
        File << std::setw(6) << std::right << -2 << " ";
        File << std::setw(6) << std::right << 2 << " ";
        File << std::setw(6) << std::right << -3 << " ";
        File << std::setw(6) << std::right << 3 << " ";
        File << std::setw(6) << std::right << -4 << " ";
        File << std::setw(6) << std::right << 4 << " ";
        File << std::setw(6) << std::right << -5 << " ";
        File << std::setw(6) << std::right << 5 << " ";
        File << std::setw(6) << std::right << -6 << " ";
        File << std::setw(6) << std::right << 6 << std::endl;
        if (File.is_open()) {
            // std::cout << ParticleCounts.size() << std::endl;
            for (int i = 0; i < ParticleCounts.size(); ++i) {
                File << std::setw(7) << std::right << TimeBlocks[i]->TimeIndex << " ";
                File << std::scientific << std::setw(13) << std::right << TimeBlocks[i]->Time << " ";
                File << std::setw(10) << std::right << TimeBlocks[i]->NumberOfParticles << " ";
                ParticleCounts[i].Write(File);
                // File << ParticleCounts[i]->Map[1];
                File << std::endl;
                // std::cout << ParticleCounts[i].Map.size() << std::endl;

                // File << VectorOfParseBlocks[i]<< std::endl;
            }
        } else {
            std::cout << "Cannot open file" << std::endl;
        }
        File.close();
    }

    // void Read(int NRun, std::string Directory) {
    //     std::ifstream File;
    //     std::string FileName = Directory + std::to_string(NRun) + "/panimate_summary.dat";
    //     File.open((FileName).c_str(), std::ios::in);

    //     if (File.is_open()) {
    //         ParseBlock TempBlock;
    //         int MapSize;
    //         int ID;
    //         int Count;
    //         while (File >> TempBlock.Time >> TempBlock.NumberOfParticles >> MapSize) {
    //             for (int i = 0; i < MapSize; ++i) {
    //                 File >> ID >> Count;
    //                 TempBlock.CountMap[ID] = Count;
    //             }
    //             VectorOfParseBlocks.emplace_back(TempBlock);
    //         }
    //     } else {
    //         std::cout << "Cannot open file: " + FileName << std::endl;
    //     }
    //     File.close();
    // }

    // void Print() {
    //     for (int i = 0; i < VectorOfParseBlocks.size(); ++i) {
    //         std::cout << VectorOfParseBlocks[i] << std::endl;
    //     }
    // }
};  // namespace Parton
}  // namespace Parton
}  // namespace Evolution

}  // namespace AMPT

#endif