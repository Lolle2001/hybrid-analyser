// Copyright (C) 2024 Lieuwe Huisman

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

// #include "../Histogram2D.hpp"
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
        {6, 0},
        {21, 0}};
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
        output << std::setw(6) << std::right << Map[21] << " ";
    }

    friend std::ostream &operator<<(std::ostream &output, CountMap &obj) {
        output << std::setw(5) << std::right << obj.Map[-1] << " ";
        output << std::setw(5) << std::right << obj.Map[1] << " ";
        output << std::setw(5) << std::right << obj.Map[-2] << " ";
        output << std::setw(5) << std::right << obj.Map[2] << " ";
        output << std::setw(5) << std::right << obj.Map[-3] << " ";
        output << std::setw(5) << std::right << obj.Map[3] << " ";
        output << std::setw(5) << std::right << obj.Map[-4] << " ";
        output << std::setw(5) << std::right << obj.Map[4] << " ";
        output << std::setw(5) << std::right << obj.Map[-5] << " ";
        output << std::setw(5) << std::right << obj.Map[5] << " ";
        output << std::setw(5) << std::right << obj.Map[-6] << " ";
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

    double xmin = -25;
    double xmax = 25;
    size_t nx = 50;
    double ymin = -25;
    double ymax = 25;
    size_t ny = 50;

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

    std::vector<double> time;
    size_t nt = 0;

   public:
    std::vector<CountMap> ParticleCounts;
    std::vector<std::unique_ptr<Evolution::HistogramS2D>> ParticleEnergyDensity;
    Gridsettings Settings2D;
    std::vector<std::unique_ptr<Evolution::HistogramS3D>> EnergyDensity3D;
    Gridsettings Settings3D;
    std::vector<std::unique_ptr<TimeBlock>> TimeBlocks;

    File(std::string InputDirectory_) : InputDirectory(InputDirectory_){};

    void SetGrid3D(Gridsettings &settings) {
        Settings3D = settings;
    }
    void SetGrid2D(Gridsettings &settings) {
        Settings2D = settings;
    }

    void Parse(std::shared_ptr<AMPT::Evolution::Parton::Freezeout::File> finalft) {
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);

        if (file.is_open()) {
            std::string sa;
            std::istringstream iss;

            dx = (xmax - xmin) / (nx);
            dy = (ymax - ymin) / (ny);
            dz_s = (zmax_s - zmin_s) / (nz_s);
            dz = (zmax - zmin) / (nz);

            double cellsize_s = dx * dy * dz_s;
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

            nt = TimeBlocks.size();

            ParticleCounts.resize(nt);
            ParticleEnergyDensity.resize(nt);
            EnergyDensity3D.resize(nt);
            for (int i = 0; i < nt; i++) {
                ParticleEnergyDensity[i] = std::make_unique<Evolution::HistogramS2D>(
                    Settings2D.xmin,
                    Settings2D.xmax,
                    Settings2D.nx,
                    Settings2D.ymin,
                    Settings2D.ymax,
                    Settings2D.ny,
                    Settings2D.zmin,
                    Settings2D.zmax);
                EnergyDensity3D[i] = std::make_unique<Evolution::HistogramS3D>(Settings2D.xmin,
                                                                               Settings3D.xmax,
                                                                               Settings3D.nx,
                                                                               Settings3D.ymin,
                                                                               Settings3D.ymax,
                                                                               Settings3D.ny,
                                                                               Settings3D.zmin,
                                                                               Settings3D.zmax,
                                                                               Settings3D.nz);
            }

            size_t nthread = omp_get_max_threads();

            std::vector<std::shared_ptr<AMPT::Evolution::Parton::Freezeout::File>> freezeoutmap(nthread, finalft);

            Utilities::Progressbar bar(nt);
            bar.Print();

#pragma omp parallel for num_threads(nthread) schedule(dynamic)
            for (int t = 0; t < nt; ++t) {
                std::ifstream tfile;
                tfile.open(InputDirectory, std::ios::in);
                tfile.seekg(startline[t]);
                std::pair<int, double> temppair;

                int threadid = omp_get_thread_num();

                for (int p = 0; p < TimeBlocks[t]->NumberOfParticles; ++p) {
                    Particle particle;
                    read_parton(tfile, particle);
                    temppair = std::make_pair(particle.ParticlePythiaID, particle.PosT);
                    if (!freezeoutmap[threadid]->isFrozenOut(temppair)) {
                        particle.CalculateEnergy();
                        ParticleCounts[t].Add(particle.ParticlePythiaID);
                        ParticleEnergyDensity[t]->Add(particle.PosX, particle.PosY, particle.PosZ, particle.Energy / Settings2D.dvolume);
                        EnergyDensity3D[t]->Add(particle.PosX, particle.PosY, particle.PosZ, particle.Energy / Settings3D.dvolume);
                    }
                }

                bar.Update();
#pragma omp critical
                {
                    bar.Print();
                }
            }
            std::cout << std::endl;

        } else {
            std::cout << "Cannot Open File: " << InputDirectory << std::endl;
        }
        file.close();
    }

    void Print2D(std::string Directory) {
        Utilities::Progressbar bar(nt);
        bar.Print();
#pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < nt; ++i) {
            std::ofstream file;
            file.open(Directory + "/parton-energy-density-" + std::to_string(i) + ".dat");
            ParticleEnergyDensity[i]->PrintContents(file);
            file.close();
            bar.Update();
#pragma omp critical
            {
                bar.Print();
            }
        }
        std::cout << std::endl;
    }
    void PrintTime(std::string Directory) {
        std::ofstream file;
        file.open(Directory + "/parton-time.dat");
        for (int i = 0; i < nt; ++i) {
            file << TimeBlocks[i]->Time << "\n";
        }
        file.close();
    }

    void Print3D(std::string Directory) {
        Utilities::Progressbar bar(nt);
        bar.Print();
#pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < nt; ++i) {
            std::ofstream file;
            file.open(Directory + "/parton-energy-density-3D-" + std::to_string(i) + ".dat");
            EnergyDensity3D[i]->PrintContents(file);
            file.close();
            bar.Update();
#pragma omp critical
            {
                bar.Print();
            }
        }
        std::cout << std::endl;
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
        std::vector<int> pids = {-1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6};
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
        File << std::setw(6) << std::right << 6 << " ";
        File << std::setw(6) << std::right << 21 << std::endl;
        if (File.is_open()) {
            for (int i = 0; i < ParticleCounts.size(); ++i) {
                File << std::setw(7) << std::right << TimeBlocks[i]->TimeIndex << " ";
                File << std::scientific << std::setw(13) << std::right << TimeBlocks[i]->Time << " ";
                File << std::setw(10) << std::right << TimeBlocks[i]->NumberOfParticles << " ";
                ParticleCounts[i].Write(File);
                File << std::endl;
            }
        } else {
            std::cout << "Cannot open file" << std::endl;
        }
        File.close();
    }
};
}  // namespace Parton
}  // namespace Evolution

}  // namespace AMPT

#endif