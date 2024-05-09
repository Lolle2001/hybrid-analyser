#ifndef EVOLUTION_AMPT_PFINALFT_2_HPP
#define EVOLUTION_AMPT_PFINALFT_2_HPP

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
// ROOT Libraries

// User Libraries
// #include "Evolution_ampt_hanimate.hpp"
#include "Evolution_ampt_utilities.hpp"
namespace AMPT {
namespace Evolution {
namespace Parton {

namespace Freezeout {
// Standard Libraries

/*
p-finalt.dat gives the freeze-out space-time positions of partons. These
can be mapped to the partons in p-animate.dat to remove the ones that don't
exist anymore for every timestep.
*/

std::istream& read_particle(std::istream& input, Particle& particle) {
    input >> particle.ParticlePythiaID;
    input >> particle.PosX;
    input >> particle.PosY;
    input >> particle.PosZ;
    input >> particle.PosT;
    return input;
}

struct Block {
    int BlockSize;
    std::vector<Particle> particles;

    Block(){};
};
class File {
   private:
    std::string InputDirectory;
    std::vector<Particle> particles;

    std::vector<Block> VectorOfBlocks;
    size_t numberofparticles;

   public:
    std::map<std::pair<int, double>, bool> FreezeOutMap;

    File(std::string InputDirectory_) : InputDirectory(InputDirectory_){};

    void ReadFile() {
        std::ifstream File;
        File.open(InputDirectory.c_str(), std::ios::in);
        if (File.is_open()) {
            std::string sa;
            VectorOfBlocks.push_back(Block());
            Particle particle;
            while (read_particle(File, particle)) {
                particles.push_back(particle);
            }
            numberofparticles = particles.size();

        } else {
            std::cout << "Cannot Open File" << std::endl;
        }
    }

    void MakeFreezeOutMap() {
        for (int i = 0; i < numberofparticles; ++i) {
            std::pair<int, double> Index = std::make_pair(
                particles[i].ParticlePythiaID,
                particles[i].PosT);
            FreezeOutMap[Index] = true;
        }
    }

    bool isFrozenOut(std::pair<int, double> index) {
        return (FreezeOutMap.find(index) != FreezeOutMap.end());
    }
};
}  // namespace Freezeout
}  // namespace Parton
}  // namespace Evolution
}  // namespace AMPT

#endif