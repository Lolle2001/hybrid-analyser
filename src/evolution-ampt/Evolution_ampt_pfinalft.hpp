#ifndef AMPT_PFINALFT_H
#define AMPT_PFINALFT_H

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
// ROOT Libraries

// User Libraries
#include "Evolution_ampt_hanimate.hpp"
namespace AMPT {

// Standard Libraries

/*
p-finalt.dat gives the freeze-out space-time positions of partons. These
can be mapped to the partons in p-animate.dat to remove the ones that don't
exist anymore for every timestep.
*/
class AMPT_pfinalft {
   private:
    struct Block {
        int BlockSize;
        std::vector<int> ParticlePythiaID;
        std::vector<double> PosX;
        std::vector<double> PosY;
        std::vector<double> PosZ;
        std::vector<double> FreezeOutTime;

        Block(){};
    };

    std::vector<std::string> ExtractedString;
    int SizeOfExtractedString;
    int HeaderCounter = 0;
    int BlockCounter = -1;
    double HeaderTime = 0;
    std::string InputDirectory;

   public:
    std::map<std::pair<int, double>, bool> FreezeOutMap;

    std::vector<Block> VectorOfBlocks;

    AMPT_pfinalft(std::string InputDirectory_) : InputDirectory(InputDirectory_){};

    void ReadFile() {
        std::ifstream File;
        File.open(InputDirectory.c_str(), std::ios::in);
        if (File.is_open()) {
            std::string sa;
            VectorOfBlocks.push_back(Block());
            while (getline(File, sa)) {
                ExtractedString = Extract(sa);
                VectorOfBlocks[0].ParticlePythiaID.push_back(std::stoi(ExtractedString[0]));
                // std::cout << ExtractedString[3] << std::endl;
                // std::cout << ExtractedString[3].find("*******") << std::endl;
                try {
                    VectorOfBlocks[0].PosX.push_back(std::stod(ExtractedString[1]));
                } catch (const std::invalid_argument& e) {
                    // handle error, set to default
                    VectorOfBlocks[0].PosX.push_back(0);
                }
                try {
                    VectorOfBlocks[0].PosY.push_back(std::stod(ExtractedString[2]));
                } catch (const std::invalid_argument& e) {
                    // handle error, set to default
                    VectorOfBlocks[0].PosY.push_back(0);
                }
                try {
                    VectorOfBlocks[0].PosZ.push_back(std::stod(ExtractedString[3]));
                } catch (const std::invalid_argument& e) {
                    // handle error, set to default
                    VectorOfBlocks[0].PosZ.push_back(0);
                }

                try {
                    VectorOfBlocks[0].FreezeOutTime.push_back(std::stod(ExtractedString[4]));
                } catch (const std::invalid_argument& e) {
                    // handle error, set to default
                    VectorOfBlocks[0].FreezeOutTime.push_back(0);
                }
            }
            VectorOfBlocks[0].BlockSize = VectorOfBlocks[0].ParticlePythiaID.size();
        } else {
            std::cout << "Cannot Open File" << std::endl;
        }
    }

    void MakeFreezeOutMap() {
        for (int i = 0; i < VectorOfBlocks[0].BlockSize; ++i) {
            std::pair<int, double> Index = std::make_pair(
                VectorOfBlocks[0].ParticlePythiaID[i],
                VectorOfBlocks[0].FreezeOutTime[i]);
            FreezeOutMap[Index] = true;
        }
    }
};
}  // namespace AMPT

#endif