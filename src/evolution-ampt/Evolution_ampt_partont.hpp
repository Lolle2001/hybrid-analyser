
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "Evolution_ampt_hanimate.hpp"

#ifndef AMPT_PARTONT_H
#define AMPT_PARTONT_H

/*
ana/parton-t.dat

*/
class AMPT_partont {
   private:
    struct Line {
        int ParticlePythiaID;
        double MomX;
        double MomY;
        double MomZ;
        double Mass;
        double PosX;
        double PosY;
        double PosZ;
        double FormationTime;
        double PseudoRapidity;

        Line(int ParticlePythiaID, double MomX_, double MomY_, double MomZ_, double Mass_, double PosX_, double PosY_, double PosZ_, double FormationTime_, double PseudoRapidity_) : ParticlePythiaID(ParticlePythiaID), MomX(MomX_), MomY(MomY_), MomZ(MomZ_), Mass(Mass_), PosX(PosX_), PosY(PosY_), PosZ(PosZ_), FormationTime(FormationTime_), PseudoRapidity(PseudoRapidity_) {}
    };

    struct Block {
        int EventNumber;
        double Time;
        int NumberOfParticles;
        int NumberOfFormedParticles;
        int BlockSize = 0;
        std::vector<Line> VectorOfLines;

        Block(int EventNumber_, double Time_, int NumberOfParticles_, int NumberOfFormedParticles_) : EventNumber(EventNumber_), Time(Time_), NumberOfParticles(NumberOfParticles_), NumberOfFormedParticles(NumberOfFormedParticles_) {}
    };

    std::vector<std::string> ExtractedString;
    int SizeOfExtractedString;
    int HeaderCounter = 0;
    int BlockCounter = -1;
    double HeaderTime = 0;
    std::string InputDirectory;

   public:
    int NumberOfTimeSteps;
    double SizeOfTimeStep;

    std::vector<Block> VectorOfBlocks;

    AMPT_partont(std::string InputDirectory_) : InputDirectory(InputDirectory_){};

    void ReadFile() {
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);
        if (file.is_open()) {
            std::string sa;
            while (getline(file, sa)) {
                ExtractedString = AMPT::Extract(sa);
                SizeOfExtractedString = ExtractedString.size();
                if (SizeOfExtractedString == 5) {
                    VectorOfBlocks.push_back(Block(
                        std::stoi(ExtractedString[1]),
                        std::stod(ExtractedString[2]),
                        std::stoi(ExtractedString[3]),
                        std::stoi(ExtractedString[4])));
                    BlockCounter += 1;
                } else if (SizeOfExtractedString == 10) {
                    VectorOfBlocks[BlockCounter].VectorOfLines.push_back(Line(
                        std::stoi(ExtractedString[0]),
                        std::stod(ExtractedString[1]),
                        std::stod(ExtractedString[2]),
                        std::stod(ExtractedString[3]),
                        std::stod(ExtractedString[4]),
                        std::stod(ExtractedString[5]),
                        std::stod(ExtractedString[6]),
                        std::stod(ExtractedString[7]),
                        std::stod(ExtractedString[8]),
                        std::stod(ExtractedString[9])));
                }
            }
        } else {
            std::cout << "Cannot Open File" << std::endl;
        }

        NumberOfTimeSteps = VectorOfBlocks.size();
        SizeOfTimeStep = std::round(VectorOfBlocks[0].Time * 1000.0) / 1000.0;
    }

    void PrintFile() {
        for (int i = 0; i < NumberOfTimeSteps; ++i) {
            std::cout << "\033[1;97;48m" << std::setw(15) << std::left << "Evnt. Num."
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(15) << std::left << "Time"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(15) << std::left << "Num. of Part."
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(15) << std::left << "Num. of Form. Part."
                      << "\033[0m";
            std::cout << std::endl;
            std::cout << std::setw(15) << std::left << VectorOfBlocks[i].EventNumber;
            std::cout << std::setw(15) << std::left << VectorOfBlocks[i].Time;
            std::cout << std::setw(15) << std::left << VectorOfBlocks[i].NumberOfParticles;
            std::cout << std::setw(15) << std::left << VectorOfBlocks[i].NumberOfFormedParticles;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "PYTHIA ID"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "Px"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "Py"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "Pz"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "m"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "X"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "Y"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "Z"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "Tf"
                      << "\033[0m";
            std::cout << "\033[1;97;48m" << std::setw(10) << std::right << "Ps. Rap."
                      << "\033[0m";
            std::cout << std::endl;
            for (int j = 0; j < VectorOfBlocks[i].VectorOfLines.size(); ++j) {
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].ParticlePythiaID;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].MomX;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].MomY;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].MomZ;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].Mass;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].PosX;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].PosY;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].PosZ;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].FormationTime;
                std::cout << std::setw(10) << std::right << VectorOfBlocks[i].VectorOfLines[j].PseudoRapidity;
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
};

#endif