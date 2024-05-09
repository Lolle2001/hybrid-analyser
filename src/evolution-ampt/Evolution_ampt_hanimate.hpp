

#ifndef AMPT_HANIMATE_HPP
#define AMPT_HANIMATE_HPP

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../Histogram2D.hpp"
#include "../HistogramMap2D.hpp"
// #include "Evolution_ampt_format.hpp"

namespace AMPT {
std::vector<std::string> Extract(const std::string &Text) {
    std::vector<std::string> Words;
    std::stringstream ss(Text);
    std::string Buf;

    while (ss >> Buf) {
        // Words.push_back(std::move(Buf));
        Words.push_back(Buf);
    }

    return Words;
}

struct Particle {
    int ParticlePythiaID;
    int ParticleLabel;
    double PosX;
    double PosY;
    double PosZ;
    double MomX;
    double MomY;
    double MomZ;
    double Mass;
    double Energy;
    double Rapidity;
    double Phi;
    double Theta;
    double SpacetimeRapidity;

    Particle(){};

    void CalculateEnergy() {
        Energy = std::sqrt(MomX * MomX + MomY * MomY + MomZ * MomZ + Mass * Mass);
    }

    void CalculateRapidity() {
        Rapidity = std::atanh(MomZ / Energy);
    }

    void CalculateSpaceTimeRapidity() {
        SpacetimeRapidity = std::atanh(PosZ / std::sqrt(PosX * PosX + PosY * PosY + PosZ * PosZ));
    }

    void CalculatePhi() {
        Phi = std::atan2(PosY, PosX);
    }

    void CalculateTheta() {
        Theta = std::acos(PosZ / std::sqrt(PosX * PosX + PosY * PosY + PosZ * PosZ));
    }
};
/*
ana1/h-animate.dat
*/
class AMPT_hanimate {
   private:
    struct TimeBlock {
        int TimeIndex;
        double Time;
        int NumberOfParticles;
        int BlockSize = 0;

        std::vector<int> ParticleLabel;
        std::vector<double> PosX;
        std::vector<double> PosY;
        std::vector<double> PosZ;
        std::vector<double> MomX;
        std::vector<double> MomY;
        std::vector<double> MomZ;
        std::vector<double> Mass;
        std::vector<int> ParticlePythiaID;

        TimeBlock(int TimeIndex_, double Time_, int NumberOfParticles_) : TimeIndex(TimeIndex_), Time(Time_), NumberOfParticles(NumberOfParticles_) {}

        void push_back(
            int ParticleLabel_,
            double PosX_,
            double PosY_,
            double PosZ_,
            double MomX_,
            double MomY_,
            double MomZ_,
            double Mass_,
            int ParticlePythiaID_) {
            ParticleLabel.push_back(ParticleLabel_);
            PosX.push_back(PosX_);
            PosY.push_back(PosY_);
            PosZ.push_back(PosZ_);
            MomX.push_back(MomX_);
            MomY.push_back(MomY_);
            MomZ.push_back(MomZ_);
            Mass.push_back(Mass_);
            ParticlePythiaID.push_back(ParticlePythiaID_);
        }
    };

    struct EventBlock {
        int EventID;
        int NumberOfTimeSteps;
        double SizeOfTimeStep;

        std::vector<TimeBlock *> TimeBlocks;

        EventBlock(int EventID_, int NumberOfTimeSteps_, double SizeOfTimeStep_) : EventID(EventID_), NumberOfTimeSteps(NumberOfTimeSteps_), SizeOfTimeStep(SizeOfTimeStep_){};
        EventBlock(int EventID_) : EventID(EventID_){};
        void push_back(TimeBlock *TimeBlock_) {
            TimeBlocks.push_back(TimeBlock_);
        }
    };

    std::map<int, int> LabelToPythia = {
        {-30, -323},
        {-13, -22212},
        {-12, -22112},
        {-11, -12212},
        {-10, -12112},
        {-9, -2224},
        {-8, -2214},
        {-7, -2114},
        {-6, -1114},
        {-2, -2112},
        {-1, -2212},
        {0, 221},
        {1, 2212},
        {2, 2112},
        {3, -211},
        {4, 111},
        {5, 211},
        {6, 1114},
        {7, 2114},
        {8, 2214},
        {9, 2224},
        {10, 12112},
        {11, 12212},
        {12, 22112},
        {13, 22212},
        {14, 3122},
        {15, 3112},
        {16, 3212},
        {17, 3222},
        {21, -321},
        {23, 321},
        {24, 311},
        {25, -213},
        {26, 113},
        {27, 213},
        {28, 223},
        {29, 333},
        {30, 100321},
        {-14, -3122},
        {-15, -3112},
        {-16, -3212},
        {-17, -3222},
        {31, 331},
        {40, 3312},
        {-40, -3312},
        {41, 3322},
        {-41, -3322},
        {45, 3334},
        {-45, -3334},
        {42, 1000010020},
        {-42, -1000010020},
        {10022, 22}};

    std::vector<std::string> ExtractedString;
    int SizeOfExtractedString;
    int HeaderCounter = 0;
    int LabelName;

    double HeaderTime = 0;
    int EventBlockCounter = 0;
    int TimeBlockCounter = 0;
    int ParticleCounter = 0;
    bool EventBlockFlag = false;
    bool TimeBlockFlag = false;

    std::string InputDirectory;
    EventBlock *TempEventBlock;
    TimeBlock *TempTimeBlock;

    std::vector<double> xbins = {-15., -14.88, -14.76, -14.64, -14.52, -14.4, -14.28, -14.16,
                                 -14.04, -13.92, -13.8, -13.68, -13.56, -13.44, -13.32, -13.2,
                                 -13.08, -12.96, -12.84, -12.72, -12.6, -12.48, -12.36, -12.24,
                                 -12.12, -12., -11.88, -11.76, -11.64, -11.52, -11.4, -11.28,
                                 -11.16, -11.04, -10.92, -10.8, -10.68, -10.56, -10.44, -10.32,
                                 -10.2, -10.08, -9.96, -9.84, -9.72, -9.6, -9.48, -9.36,
                                 -9.24, -9.12, -9., -8.88, -8.76, -8.64, -8.52, -8.4,
                                 -8.28, -8.16, -8.04, -7.92, -7.8, -7.68, -7.56, -7.44,
                                 -7.32, -7.2, -7.08, -6.96, -6.84, -6.72, -6.6, -6.48,
                                 -6.36, -6.24, -6.12, -6., -5.88, -5.76, -5.64, -5.52,
                                 -5.4, -5.28, -5.16, -5.04, -4.92, -4.8, -4.68, -4.56,
                                 -4.44, -4.32, -4.2, -4.08, -3.96, -3.84, -3.72, -3.6,
                                 -3.48, -3.36, -3.24, -3.12, -3., -2.88, -2.76, -2.64,
                                 -2.52, -2.4, -2.28, -2.16, -2.04, -1.92, -1.8, -1.68,
                                 -1.56, -1.44, -1.32, -1.2, -1.08, -0.96, -0.84, -0.72,
                                 -0.6, -0.48, -0.36, -0.24, -0.12, 0., 0.12, 0.24,
                                 0.36, 0.48, 0.6, 0.72, 0.84, 0.96, 1.08, 1.2,
                                 1.32, 1.44, 1.56, 1.68, 1.8, 1.92, 2.04, 2.16,
                                 2.28, 2.4, 2.52, 2.64, 2.76, 2.88, 3., 3.12,
                                 3.24, 3.36, 3.48, 3.6, 3.72, 3.84, 3.96, 4.08,
                                 4.2, 4.32, 4.44, 4.56, 4.68, 4.8, 4.92, 5.04,
                                 5.16, 5.28, 5.4, 5.52, 5.64, 5.76, 5.88, 6.,
                                 6.12, 6.24, 6.36, 6.48, 6.6, 6.72, 6.84, 6.96,
                                 7.08, 7.2, 7.32, 7.44, 7.56, 7.68, 7.8, 7.92,
                                 8.04, 8.16, 8.28, 8.4, 8.52, 8.64, 8.76, 8.88,
                                 9., 9.12, 9.24, 9.36, 9.48, 9.6, 9.72, 9.84,
                                 9.96, 10.08, 10.2, 10.32, 10.44, 10.56, 10.68, 10.8,
                                 10.92, 11.04, 11.16, 11.28, 11.4, 11.52, 11.64, 11.76,
                                 11.88, 12., 12.12, 12.24, 12.36, 12.48, 12.6, 12.72,
                                 12.84, 12.96, 13.08, 13.2, 13.32, 13.44, 13.56, 13.68,
                                 13.8, 13.92, 14.04, 14.16, 14.28, 14.4, 14.52, 14.64,
                                 14.76, 14.88, 15.};

    std::vector<double> ybins = {-15., -14.88, -14.76, -14.64, -14.52, -14.4, -14.28, -14.16,
                                 -14.04, -13.92, -13.8, -13.68, -13.56, -13.44, -13.32, -13.2,
                                 -13.08, -12.96, -12.84, -12.72, -12.6, -12.48, -12.36, -12.24,
                                 -12.12, -12., -11.88, -11.76, -11.64, -11.52, -11.4, -11.28,
                                 -11.16, -11.04, -10.92, -10.8, -10.68, -10.56, -10.44, -10.32,
                                 -10.2, -10.08, -9.96, -9.84, -9.72, -9.6, -9.48, -9.36,
                                 -9.24, -9.12, -9., -8.88, -8.76, -8.64, -8.52, -8.4,
                                 -8.28, -8.16, -8.04, -7.92, -7.8, -7.68, -7.56, -7.44,
                                 -7.32, -7.2, -7.08, -6.96, -6.84, -6.72, -6.6, -6.48,
                                 -6.36, -6.24, -6.12, -6., -5.88, -5.76, -5.64, -5.52,
                                 -5.4, -5.28, -5.16, -5.04, -4.92, -4.8, -4.68, -4.56,
                                 -4.44, -4.32, -4.2, -4.08, -3.96, -3.84, -3.72, -3.6,
                                 -3.48, -3.36, -3.24, -3.12, -3., -2.88, -2.76, -2.64,
                                 -2.52, -2.4, -2.28, -2.16, -2.04, -1.92, -1.8, -1.68,
                                 -1.56, -1.44, -1.32, -1.2, -1.08, -0.96, -0.84, -0.72,
                                 -0.6, -0.48, -0.36, -0.24, -0.12, 0., 0.12, 0.24,
                                 0.36, 0.48, 0.6, 0.72, 0.84, 0.96, 1.08, 1.2,
                                 1.32, 1.44, 1.56, 1.68, 1.8, 1.92, 2.04, 2.16,
                                 2.28, 2.4, 2.52, 2.64, 2.76, 2.88, 3., 3.12,
                                 3.24, 3.36, 3.48, 3.6, 3.72, 3.84, 3.96, 4.08,
                                 4.2, 4.32, 4.44, 4.56, 4.68, 4.8, 4.92, 5.04,
                                 5.16, 5.28, 5.4, 5.52, 5.64, 5.76, 5.88, 6.,
                                 6.12, 6.24, 6.36, 6.48, 6.6, 6.72, 6.84, 6.96,
                                 7.08, 7.2, 7.32, 7.44, 7.56, 7.68, 7.8, 7.92,
                                 8.04, 8.16, 8.28, 8.4, 8.52, 8.64, 8.76, 8.88,
                                 9., 9.12, 9.24, 9.36, 9.48, 9.6, 9.72, 9.84,
                                 9.96, 10.08, 10.2, 10.32, 10.44, 10.56, 10.68, 10.8,
                                 10.92, 11.04, 11.16, 11.28, 11.4, 11.52, 11.64, 11.76,
                                 11.88, 12., 12.12, 12.24, 12.36, 12.48, 12.6, 12.72,
                                 12.84, 12.96, 13.08, 13.2, 13.32, 13.44, 13.56, 13.68,
                                 13.8, 13.92, 14.04, 14.16, 14.28, 14.4, 14.52, 14.64,
                                 14.76, 14.88, 15.};

   public:
    int NumberOfEvents = 0;
    int NumberOfTimeSteps = 0;
    double SizeOfTimeStep = 0;
    std::vector<std::map<int, int>> ParticleCounts;
    // std::vector<std::vector<std::vector<std::map<int, double>>>> ParticleEnergy;
    // std::vector<Statistics::HistogramMap2D> ParticleEnergyDensity;
    std::vector<Statistics::Histogram2D> ParticleEnergyDensity;

    std::vector<EventBlock *> EventBlocks;

    AMPT_hanimate(std::string InputDirectory_) : InputDirectory(InputDirectory_){};
    AMPT_hanimate(){};

    void ReadFile() {
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);
        if (file.is_open()) {
            std::string sa;

            getline(file, sa);
            ExtractedString = Extract(sa);
            SizeOfExtractedString = ExtractedString.size();

            NumberOfTimeSteps = std::stoi(ExtractedString[0]);
            SizeOfTimeStep = std::stod(ExtractedString[1]);

            ParticleCounts.resize(NumberOfTimeSteps);

            ParticleEnergyDensity.resize(NumberOfTimeSteps);
            for (int i = 0; i < NumberOfTimeSteps; i++) {
                ParticleEnergyDensity[i] = Statistics::Histogram2D("hist", xbins, ybins);
            }

            double cellsize = (xbins[1] - xbins[0]) * (ybins[1] - ybins[0]);

            TempEventBlock = new EventBlock(
                EventBlockCounter + 1,
                std::stoi(ExtractedString[0]),
                std::stod(ExtractedString[1]));
            EventBlocks.push_back(TempEventBlock);

            while (getline(file, sa)) {
                ExtractedString = Extract(sa);
                SizeOfExtractedString = ExtractedString.size();
                if (std::stoi(ExtractedString[0]) != -10) {
                    if (SizeOfExtractedString == 1) {
                        if (TimeBlockCounter < NumberOfTimeSteps) {
                            if (HeaderCounter == 0) {
                                HeaderCounter += 1;
                                HeaderTime = std::stod(ExtractedString[0]);
                            } else if (HeaderCounter == 1) {
                                TempTimeBlock = new TimeBlock(
                                    TimeBlockCounter + 1,
                                    HeaderTime,
                                    std::stoi(ExtractedString[0]));

                                EventBlocks[EventBlockCounter]->push_back(TempTimeBlock);

                                // std::cout << EventBlockCounter << " " << TimeBlockCounter << " " << HeaderTime << " " << std::stoi(ExtractedString[0]) << std::endl;
                                TimeBlockCounter += 1;
                                HeaderCounter = 0;
                            }
                        } else if (TimeBlockCounter == NumberOfTimeSteps) {
                            EventBlockCounter += 1;
                            HeaderTime = std::stod(ExtractedString[0]);
                            TempEventBlock = new EventBlock(
                                EventBlockCounter + 1,
                                NumberOfTimeSteps,
                                SizeOfTimeStep);
                            EventBlocks.push_back(TempEventBlock);

                            TimeBlockCounter = 0;
                            HeaderCounter = 1;
                        }
                    } else if (SizeOfExtractedString == 8) {
                        LabelName = std::stoi(ExtractedString[0]);
                        double posx = std::stod(ExtractedString[1]);
                        double posy = std::stod(ExtractedString[2]);
                        double posz = std::stod(ExtractedString[3]);

                        Particle particle;
                        particle.MomX = std::stod(ExtractedString[4]);
                        particle.MomY = std::stod(ExtractedString[5]);
                        particle.MomZ = std::stod(ExtractedString[6]);
                        particle.Mass = std::stod(ExtractedString[7]);
                        particle.PosZ = std::stod(ExtractedString[3]);
                        particle.CalculateEnergy();
                        particle.CalculateRapidity();
                        particle.CalculatePhi();
                        ParticleCounts[TimeBlockCounter - 1][LabelToPythia[LabelName]] += 1;
                        // if (particle.Rapidity >= -0.5 && particle.Rapidity <= 0.5) {
                        //     ParticleEnergyDensity[TimeBlockCounter].Add(
                        //         posx,
                        //         posy,
                        //         LabelToPythia[LabelName],
                        //         particle.Energy);
                        // }

                        if (particle.PosZ >= -10 && particle.PosZ <= 10) {
                            ParticleEnergyDensity[TimeBlockCounter].Add(
                                posx,
                                posy,
                                particle.Energy / (cellsize * 20));
                        }

                        // std::cout << EventBlockCounter << " " << TimeBlockCounter << std::endl;
                        // EventBlocks[EventBlockCounter]->TimeBlocks[TimeBlockCounter - 1]->push_back(
                        //     LabelName,
                        //     std::stod(ExtractedString[1]),
                        //     std::stod(ExtractedString[2]),
                        //     std::stod(ExtractedString[3]),
                        //     std::stod(ExtractedString[4]),
                        //     std::stod(ExtractedString[5]),
                        //     std::stod(ExtractedString[6]),
                        //     std::stod(ExtractedString[7]),
                        //     LabelToPythia[LabelName]);
                    }
                }
            }
            EventBlocks.pop_back();
            NumberOfEvents = EventBlocks.size();
            // std::cout << NumberOfEvents << std::endl;
        } else {
            std::cout << "Cannot Open File: " << InputDirectory << std::endl;
        }
    }

    void PrintFile() {
        std::cout << "\033[1;97;48m" << std::setw(9) << std::left << "Event ID"
                  << "| "
                  << "\033[0m";
        std::cout << "\033[1;97;48m" << std::setw(20) << std::left << "Number of Timesteps"
                  << "| "
                  << "\033[0m";
        std::cout << "\033[1;97;48m" << std::setw(17) << std::left << "Size of Timestep"
                  << "| "
                  << "\033[0m";
        std::cout << std::endl;
        for (int i = 0; i < NumberOfEvents; ++i) {
            std::cout << std::setw(9) << std::left << EventBlocks[i]->EventID << "| ";
            std::cout << std::setw(20) << std::left << EventBlocks[i]->NumberOfTimeSteps << "| ";
            std::cout << std::setw(17) << std::left << EventBlocks[i]->SizeOfTimeStep << "| ";
            std::cout << std::endl;
            // std::cout << "--------------------------------------------------" << std::endl;

            // for(int j = 0; j < EventBlocks[i] -> NumberOfTimeSteps; ++j){

            //     std::cout << std::setw(15) << std::left << EventBlocks[i] -> TimeBlocks[j] -> Time;
            //     std::cout << std::setw(15) << std::left << EventBlocks[i] -> TimeBlocks[j] -> NumberOfParticles;
            //     std::cout << std::endl;
            // }
        }
    }

    void PrintParticleCounts(std::ostream &output) {
        std::vector<int> pids = {-323,
                                 -22212,
                                 -22112,
                                 -12212,
                                 -12112,
                                 -2224,
                                 -2214,
                                 -2114,
                                 -1114,
                                 -2112,
                                 -2212,
                                 221,
                                 2212,
                                 2112,
                                 -211,
                                 111,
                                 211,
                                 1114,
                                 2114,
                                 2214,
                                 2224,
                                 12112,
                                 12212,
                                 22112,
                                 22212,
                                 3122,
                                 3112,
                                 3212,
                                 3222,
                                 -321,
                                 321,
                                 311,
                                 -213,
                                 113,
                                 213,
                                 223,
                                 333,
                                 100321,
                                 -3122,
                                 -3112,
                                 -3212,
                                 -3222,
                                 331,
                                 3312,
                                 -3312,
                                 3322,
                                 -3322,
                                 3334,
                                 -3334,
                                 1000010020,
                                 -1000010020,
                                 22};
        // std::vector<int> pids = {211, -211, 321, -321, 2212, -2212};
        // output << std::setw(9) << std::right << "Timestep"
        //        << " ";
        // output << std::setw(9) << std::right << 211 << " ";
        // output << std::setw(9) << std::right << -211 << " ";
        // output << std::setw(9) << std::right << 321 << " ";
        // output << std::setw(9) << std::right << -321 << " ";
        // output << std::setw(9) << std::right << 2212 << " ";
        // output << std::setw(9) << std::right << -2212 << " ";
        // output << std::endl;
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
            output << std::setw(6) << std::right << EventBlocks[0]->TimeBlocks[i]->Time << " ";
            for (auto &entry : pids) {
                output << std::setw(13) << std::right << ParticleCounts[i][entry] << " ";
            }
            output << std::endl;
            // output << std::setw(9) << std::right << i << " ";
            // for (auto &pid : pids) {
            //     if (ParticleCounts[i].count(pid) != 0) {
            //         output << std::setw(9) << std::right << ParticleCounts[i][pid] << " ";
            //     } else {
            //         output << std::setw(9) << std::right << 0 << " ";
            //     }
            // }
            // output << std::endl;
        }
    }

    void PrintParticleEnergyDensity(std::string Directory) {
        for (int i = 0; i < NumberOfTimeSteps; ++i) {
            std::ofstream file(Directory + "/hadron-energy-density-" + std::to_string(i) + ".dat");
            // ParticleEnergyDensity[i].Convert();
            ParticleEnergyDensity[i].PrintTotal(file);
            file.close();
        }
    }

    void PrintInfo(std::ostream &output) {
        output << NumberOfTimeSteps << " " << xbins.size() << " " << ybins.size() << std::endl;
        output << SizeOfTimeStep << " " << xbins[1] - xbins[0] << " " << ybins[1] - ybins[0] << std::endl;
        output << 0 << " " << xbins[0] << " " << ybins[1];
    }

    void operator+=(AMPT_hanimate const &obj) {
        EventBlocks.insert(std::end(EventBlocks), std::begin(obj.EventBlocks), std::end(obj.EventBlocks));
        NumberOfEvents += obj.NumberOfEvents;
        int StartIndex = NumberOfEvents - obj.NumberOfEvents;
        for (int i = StartIndex; i < NumberOfEvents; ++i) {
            EventBlocks[i]->EventID += StartIndex;
        }
    }

    AMPT_hanimate operator+(AMPT_hanimate const &obj) {
        EventBlocks.insert(std::end(EventBlocks), std::begin(obj.EventBlocks), std::end(obj.EventBlocks));
        NumberOfEvents += obj.NumberOfEvents;
        int StartIndex = NumberOfEvents - obj.NumberOfEvents;
        for (int i = StartIndex; i < NumberOfEvents; ++i) {
            EventBlocks[i]->EventID += StartIndex;
        }
        return *this;
    }
};

AMPT_hanimate *Combine_hanimate(int NRun, int NBatchMin, int NBatchMax, std::string Directory) {
    AMPT_hanimate *chanimate = new AMPT_hanimate();
    for (int i = NBatchMin; i <= NBatchMax; ++i) {
        AMPT_hanimate *hanimate = new AMPT_hanimate(Directory + std::to_string(NRun) + "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana1/h-animate.dat");
        hanimate->ReadFile();
        *chanimate += *hanimate;
        std::cout << "Loaded data: \033[1:97m";
        std::cout << std::to_string(NRun) + "_" + std::to_string(i);
        std::cout << "\033[0m\t";
        std::cout << "Amount of events: \033[1:97m";
        std::cout << std::to_string(hanimate->NumberOfEvents);
        std::cout << "\033[0m" << std::endl;
        delete hanimate;
    }
    return chanimate;
}

}  // namespace AMPT

#endif