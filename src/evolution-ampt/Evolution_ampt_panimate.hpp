

#ifndef AMPT_PANIMATE_H
#define AMPT_PANIMATE_H
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../Histogram2D.hpp"
#include "Evolution_ampt_hanimate.hpp"
#include "Evolution_ampt_pfinalft.hpp"
namespace AMPT {
/*
ana1/p-animate.dat
*/
class AMPT_panimate {
   private:
    struct Line {
        int ParticlePythiaID;
        double PosX;
        double PosY;
        double PosZ;
        double FormationTime;
        double MomX;
        double MomY;
        double MomZ;
        double Mass;

        Line(int ParticlePythiaID_, double PosX_, double PosY_, double PosZ_, double FormationTime_, double MomX_, double MomY_, double MomZ_, double Mass_) : ParticlePythiaID(ParticlePythiaID_), PosX(PosX_), PosY(PosY_), PosZ(PosZ_), FormationTime(FormationTime_), MomX(MomX_), MomY(MomY_), MomZ(MomZ_), Mass(Mass_) {}

        Line(){};
        friend std::istream &operator>>(std::istream &input, Line &obj) {
            input >> obj.ParticlePythiaID >> obj.PosX >> obj.PosY >> obj.PosZ >> obj.FormationTime >> obj.MomX >> obj.MomY >> obj.MomZ >> obj.Mass;

            return input;
        }
    };

    struct Block {
        double Time;
        int NumberOfParticles;
        int BlockSize = 0;
        std::vector<Line> VectorOfLines;

        Block(double Time_, int NumberOfParticles_) : Time(Time_), NumberOfParticles(NumberOfParticles_) {}
    };

    struct ParseBlock {
        double Time;
        int NumberOfParticles;
        std::map<int, int> CountMap;

        ParseBlock(){};

        void Add(int &pythiaid) {
            CountMap[pythiaid] += 1;
        }

        friend std::ostream &operator<<(std::ostream &output, ParseBlock &obj) {
            output << std::setw(8) << std::right << std::fixed << std::setprecision(2) << obj.Time << " ";
            output << std::setw(6) << std::right << obj.NumberOfParticles << " ";
            output << std::setw(3) << std::right << -1 << " ";
            output << std::setw(5) << std::right << obj.CountMap[-1] << " ";
            output << std::setw(3) << std::right << 1 << " ";
            output << std::setw(5) << std::right << obj.CountMap[1] << " ";
            output << std::setw(3) << std::right << -2 << " ";
            output << std::setw(5) << std::right << obj.CountMap[-2] << " ";
            output << std::setw(3) << std::right << 2 << " ";
            output << std::setw(5) << std::right << obj.CountMap[2] << " ";
            output << std::setw(3) << std::right << -3 << " ";
            output << std::setw(5) << std::right << obj.CountMap[-3] << " ";
            output << std::setw(3) << std::right << 3 << " ";
            output << std::setw(5) << std::right << obj.CountMap[3] << " ";
            output << std::setw(3) << std::right << -4 << " ";
            output << std::setw(5) << std::right << obj.CountMap[-4] << " ";
            output << std::setw(3) << std::right << 4 << " ";
            output << std::setw(5) << std::right << obj.CountMap[4] << " ";
            output << std::setw(3) << std::right << -5 << " ";
            output << std::setw(5) << std::right << obj.CountMap[-5] << " ";
            output << std::setw(3) << std::right << 5 << " ";
            output << std::setw(5) << std::right << obj.CountMap[5] << " ";
            output << std::setw(3) << std::right << -6 << " ";
            output << std::setw(5) << std::right << obj.CountMap[-6] << " ";
            output << std::setw(3) << std::right << 6 << " ";
            output << std::setw(5) << std::right << obj.CountMap[6] << " ";
            return output;
        }
    };

    std::vector<std::string> ExtractedString;
    int SizeOfExtractedString;
    int HeaderCounter = 0;
    int BlockCounter = -1;
    double HeaderTime = 0;
    std::string InputDirectory;

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

    std::vector<Statistics::Histogram2D> PartonEnergyDensity;

   public:
    int NumberOfTimeSteps;
    double SizeOfTimeStep;

    std::vector<Block> VectorOfBlocks;
    std::vector<ParseBlock> VectorOfParseBlocks;

    AMPT_panimate(std::string InputDirectory_) : InputDirectory(InputDirectory_){};

    void ReadFile() {
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);
        if (file.is_open()) {
            std::string sa;
            while (getline(file, sa)) {
                ExtractedString = Extract(sa);
                SizeOfExtractedString = ExtractedString.size();

                if (SizeOfExtractedString == 1) {
                    if (HeaderCounter == 0) {
                        HeaderTime = std::stod(ExtractedString[0]);
                        HeaderCounter += 1;
                    } else {
                        VectorOfBlocks.push_back(Block(HeaderTime, std::stoi(ExtractedString[0])));
                        BlockCounter += 1;
                        HeaderCounter = 0;
                    }
                } else if (SizeOfExtractedString == 9) {
                    VectorOfBlocks[BlockCounter].VectorOfLines.push_back(Line(
                        std::stoi(ExtractedString[0]),
                        std::stod(ExtractedString[1]),
                        std::stod(ExtractedString[2]),
                        std::stod(ExtractedString[3]),
                        std::stod(ExtractedString[4]),
                        std::stod(ExtractedString[5]),
                        std::stod(ExtractedString[6]),
                        std::stod(ExtractedString[7]),
                        std::stod(ExtractedString[8])));
                }
            }
        } else {
            std::cout << "Cannot Open File" << std::endl;
        }
        NumberOfTimeSteps = VectorOfBlocks.size();
        SizeOfTimeStep = std::round(VectorOfBlocks[0].Time * 1000.0) / 1000.0;
    }

    void Parse(AMPT_pfinalft *finalft) {
        double cellsize = (xbins[1] - xbins[0]) * (ybins[1] - ybins[0]);

        std::ifstream File;
        File.open(InputDirectory.c_str(), std::ios::in);

        double Time;
        int ParticleCount;
        ParseBlock TempBlock;
        Line TempLine;
        Statistics::Histogram2D TempHist;
        std::pair<int, double> TempPair;

        if (File.is_open()) {
            while (File >> TempBlock.Time) {
                if (TempBlock.Time == -10) {
                    break;
                } else {
                    TempHist = Statistics::Histogram2D("hist", xbins, ybins);
                    File >> TempBlock.NumberOfParticles;
                    for (int i = 0; i < TempBlock.NumberOfParticles; ++i) {
                        File >> TempLine;
                        TempPair = std::make_pair(TempLine.ParticlePythiaID, TempLine.FormationTime);
                        // std::cout << finalft -> FreezeOutMap[TempPair] << std::endl;
                        if (finalft->FreezeOutMap.find(TempPair) == finalft->FreezeOutMap.end()) {
                            TempBlock.Add(TempLine.ParticlePythiaID);

                            Particle particle;
                            particle.MomX = TempLine.MomX;
                            particle.MomY = TempLine.MomY;
                            particle.MomZ = TempLine.MomZ;
                            particle.Mass = TempLine.Mass;
                            particle.PosX = TempLine.PosX;
                            particle.PosY = TempLine.PosY;
                            particle.PosZ = TempLine.PosZ;
                            particle.CalculateEnergy();
                            particle.CalculateRapidity();
                            particle.CalculatePhi();
                            if (particle.PosZ >= -10 && particle.PosZ <= 10) {
                                TempHist.Add(
                                    particle.PosX,
                                    particle.PosY,
                                    particle.Energy / (cellsize * 20));
                            }
                        }
                    }
                    // std::cout << TempBlock << std::endl;
                    PartonEnergyDensity.push_back(TempHist);
                    VectorOfParseBlocks.emplace_back(TempBlock);
                    TempBlock = ParseBlock();
                }
            }
        }
    }

    void PrintPartonEnergyDensity(std::string Directory) {
        for (int i = 0; i < PartonEnergyDensity.size(); ++i) {
            std::ofstream file(Directory + "/parton-energy-density-" + std::to_string(i) + ".dat");
            PartonEnergyDensity[i].PrintTotal(file);
            file.close();
        }
    }

    void PrintInfo(std::ostream &output) {
        output << xbins.size() << " " << ybins.size() << std::endl;
        output << xbins[1] - xbins[0] << " " << ybins[1] - ybins[0] << std::endl;
        output << xbins[0] << " " << ybins[1] << std::endl;
        for (int i = 0; i < VectorOfParseBlocks.size(); ++i) {
            output << VectorOfParseBlocks[i].Time << " ";
        }
    }

    void Write(std::ofstream &File) {
        // std::ofstream File;
        // std::string FileName = Directory + std::to_string(NRun) + "/panimate_summary.dat";
        // File.open((FileName).c_str(), std::ios::out);
        std::vector<int> pids = {-1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6};
        File << std::setw(4) << "# itau"
             << " ";
        File << std::setw(13) << "tau"
             << " ";
        File << std::setw(6) << "N[partons]"
             << " ";
        // File << std::setw(6) << VectorOfParseBlocks[i].CountMap.size() << " ";
        File << std::setw(6) << "N[-1]"
             << " ";
        File << std::setw(6) << "N[1]"
             << " ";
        File << std::setw(6) << "N[-2]"
             << " ";
        File << std::setw(6) << "N[2]"
             << " ";
        File << std::setw(6) << "N[-3]"
             << " ";
        File << std::setw(6) << "N[3]"
             << " ";
        File << std::setw(6) << "N[-4]"
             << " ";
        File << std::setw(6) << "N[4]"
             << " ";
        File << std::setw(6) << "N[-5]"
             << " ";
        File << std::setw(6) << "N[5]" << std::endl;
        if (File.is_open()) {
            for (int i = 0; i < VectorOfParseBlocks.size(); ++i) {
                File << std::setw(4) << i << " ";
                File << std::scientific << std::setw(13) << VectorOfParseBlocks[i].Time << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].NumberOfParticles << " ";
                // File << std::setw(6) << VectorOfParseBlocks[i].CountMap.size() << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[-1] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[1] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[-2] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[2] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[-3] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[3] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[-4] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[4] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[-5] << " ";
                File << std::setw(6) << VectorOfParseBlocks[i].CountMap[5] << std::endl;

                // File << VectorOfParseBlocks[i]<< std::endl;
            }
        } else {
            std::cout << "Cannot open file" << std::endl;
        }
        File.close();
    }

    void Read(int NRun, std::string Directory) {
        std::ifstream File;
        std::string FileName = Directory + std::to_string(NRun) + "/panimate_summary.dat";
        File.open((FileName).c_str(), std::ios::in);

        if (File.is_open()) {
            ParseBlock TempBlock;
            int MapSize;
            int ID;
            int Count;
            while (File >> TempBlock.Time >> TempBlock.NumberOfParticles >> MapSize) {
                for (int i = 0; i < MapSize; ++i) {
                    File >> ID >> Count;
                    TempBlock.CountMap[ID] = Count;
                }
                VectorOfParseBlocks.emplace_back(TempBlock);
            }
        } else {
            std::cout << "Cannot open file: " + FileName << std::endl;
        }
        File.close();
    }

    void Print() {
        for (int i = 0; i < VectorOfParseBlocks.size(); ++i) {
            std::cout << VectorOfParseBlocks[i] << std::endl;
        }
    }
};

}  // namespace AMPT

#endif