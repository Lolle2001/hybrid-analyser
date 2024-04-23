

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

namespace AMPT
{
    std::vector<std::string> Extract(const std::string &Text)
    {
        std::vector<std::string> Words;
        std::stringstream ss(Text);
        std::string Buf;

        while (ss >> Buf)
        {
            // Words.push_back(std::move(Buf));
            Words.push_back(Buf);
        }

        return Words;
    }

    struct Particle
    {
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

        void CalculateEnergy()
        {
            Energy = std::sqrt(MomX * MomX + MomY * MomY + MomZ * MomZ + Mass * Mass);
        }

        void CalculateRapidity()
        {
            Rapidity = std::atanh(MomZ / Energy);
        }

        void CalculateSpaceTimeRapidity()
        {
            SpacetimeRapidity = std::atanh(PosZ / std::sqrt(PosX * PosX + PosY * PosY + PosZ * PosZ));
        }

        void CalculatePhi()
        {
            Phi = std::atan2(PosY, PosX);
        }

        void CalculateTheta()
        {
            Theta = std::acos(PosZ / std::sqrt(PosX * PosX + PosY * PosY + PosZ * PosZ));
        }
    };
    /*
    ana1/h-animate.dat
    */
    class AMPT_hanimate
    {
    private:
        struct TimeBlock
        {
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
                int ParticlePythiaID_)
            {
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

        struct EventBlock
        {
            int EventID;
            int NumberOfTimeSteps;
            double SizeOfTimeStep;

            std::vector<TimeBlock *> TimeBlocks;

            EventBlock(int EventID_, int NumberOfTimeSteps_, double SizeOfTimeStep_) : EventID(EventID_), NumberOfTimeSteps(NumberOfTimeSteps_), SizeOfTimeStep(SizeOfTimeStep_){};
            EventBlock(int EventID_) : EventID(EventID_){};
            void push_back(TimeBlock *TimeBlock_)
            {
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
            {42, 42},
            {-42, -42},
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

        std::vector<double> xbins = {-50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38,
                                     -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25,
                                     -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12,
                                     -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1,
                                     2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                                     28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                                     41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
        std::vector<double> ybins = {-50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38,
                                     -37, -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25,
                                     -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12,
                                     -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1,
                                     2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                                     28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                                     41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

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

        void ReadFile()
        {
            std::ifstream file;
            file.open(InputDirectory.c_str(), std::ios::in);
            if (file.is_open())
            {
                std::string sa;

                getline(file, sa);
                ExtractedString = Extract(sa);
                SizeOfExtractedString = ExtractedString.size();

                NumberOfTimeSteps = std::stoi(ExtractedString[0]);
                SizeOfTimeStep = std::stod(ExtractedString[1]);

                ParticleCounts.resize(NumberOfTimeSteps);

                ParticleEnergyDensity.resize(NumberOfTimeSteps);
                for (int i = 0; i < NumberOfTimeSteps; i++)
                {
                    ParticleEnergyDensity[i] = Statistics::Histogram2D("hist", xbins, ybins);
                }

                double cellsize = (xbins[1] - xbins[0]) * (ybins[1] - ybins[0]);

                TempEventBlock = new EventBlock(
                    EventBlockCounter + 1,
                    std::stoi(ExtractedString[0]),
                    std::stod(ExtractedString[1]));
                EventBlocks.push_back(TempEventBlock);

                while (getline(file, sa))
                {
                    ExtractedString = Extract(sa);
                    SizeOfExtractedString = ExtractedString.size();
                    if (std::stoi(ExtractedString[0]) != -10)
                    {
                        if (SizeOfExtractedString == 1)
                        {
                            if (TimeBlockCounter < NumberOfTimeSteps)
                            {
                                if (HeaderCounter == 0)
                                {
                                    HeaderCounter += 1;
                                    HeaderTime = std::stod(ExtractedString[0]);
                                }
                                else if (HeaderCounter == 1)
                                {
                                    TempTimeBlock = new TimeBlock(
                                        TimeBlockCounter + 1,
                                        HeaderTime,
                                        std::stoi(ExtractedString[0]));

                                    EventBlocks[EventBlockCounter]->push_back(TempTimeBlock);

                                    // std::cout << EventBlockCounter << " " << TimeBlockCounter << " " << HeaderTime << " " << std::stoi(ExtractedString[0]) << std::endl;
                                    TimeBlockCounter += 1;
                                    HeaderCounter = 0;
                                }
                            }
                            else if (TimeBlockCounter == NumberOfTimeSteps)
                            {
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
                        }
                        else if (SizeOfExtractedString == 8)
                        {
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

                            if (particle.PosZ >= -10 && particle.PosZ <= 10)
                            {
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
            }
            else
            {
                std::cout << "Cannot Open File: " << InputDirectory << std::endl;
            }
        }

        void PrintFile()
        {
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
            for (int i = 0; i < NumberOfEvents; ++i)
            {
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

        void PrintParticleCounts(std::ostream &output)
        {
            std::vector<int> pids = {211, -211, 321, -321, 2212, -2212};
            output << std::setw(9) << std::right << "Timestep"
                   << " ";
            output << std::setw(9) << std::right << 211 << " ";
            output << std::setw(9) << std::right << -211 << " ";
            output << std::setw(9) << std::right << 321 << " ";
            output << std::setw(9) << std::right << -321 << " ";
            output << std::setw(9) << std::right << 2212 << " ";
            output << std::setw(9) << std::right << -2212 << " ";
            output << std::endl;
            for (int i = 0; i < NumberOfTimeSteps; ++i)
            {
                output << std::setw(9) << std::right << i << " ";
                for (auto &pid : pids)
                {
                    if (ParticleCounts[i].count(pid) != 0)
                    {
                        output << std::setw(9) << std::right << ParticleCounts[i][pid] << " ";
                    }
                    else
                    {
                        output << std::setw(9) << std::right << 0 << " ";
                    }
                }
                output << std::endl;
            }
        }

        void PrintParticleEnergyDensity(std::string Directory)
        {
            for (int i = 0; i < NumberOfTimeSteps; ++i)
            {
                std::ofstream file(Directory + "/hadron-energy-density-" + std::to_string(i) + ".dat");
                // ParticleEnergyDensity[i].Convert();
                ParticleEnergyDensity[i].PrintTotal(file);
                file.close();
            }
        }

        void PrintInfo(std::ostream &output)
        {
            output << NumberOfTimeSteps << " " << xbins.size() << " " << ybins.size() << std::endl;
            output << SizeOfTimeStep << " " << xbins[1] - xbins[0] << " " << ybins[1] - ybins[0] << std::endl;
            output << 0 << " " << xbins[0] << " " << ybins[1];
        }

        void operator+=(AMPT_hanimate const &obj)
        {
            EventBlocks.insert(std::end(EventBlocks), std::begin(obj.EventBlocks), std::end(obj.EventBlocks));
            NumberOfEvents += obj.NumberOfEvents;
            int StartIndex = NumberOfEvents - obj.NumberOfEvents;
            for (int i = StartIndex; i < NumberOfEvents; ++i)
            {
                EventBlocks[i]->EventID += StartIndex;
            }
        }

        AMPT_hanimate operator+(AMPT_hanimate const &obj)
        {
            EventBlocks.insert(std::end(EventBlocks), std::begin(obj.EventBlocks), std::end(obj.EventBlocks));
            NumberOfEvents += obj.NumberOfEvents;
            int StartIndex = NumberOfEvents - obj.NumberOfEvents;
            for (int i = StartIndex; i < NumberOfEvents; ++i)
            {
                EventBlocks[i]->EventID += StartIndex;
            }
            return *this;
        }
    };

    AMPT_hanimate *Combine_hanimate(int NRun, int NBatchMin, int NBatchMax, std::string Directory)
    {
        AMPT_hanimate *chanimate = new AMPT_hanimate();
        for (int i = NBatchMin; i <= NBatchMax; ++i)
        {
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

} // namespace AMPT

#endif