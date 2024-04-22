#ifndef EVOLUTION_AMPT_FORMAT_HPP
#define EVOLUTION_AMPT_FORMAT_HPP
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>
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

    Particle(){};

    void CalculateEnergy() {
        Energy = std::sqrt(MomX * MomX + MomY * MomY + MomZ * MomZ + Mass * Mass);
    }

    void CalculateRapidity() {
        Rapidity = std::atan2(MomZ, Energy);
    }
};
// struct TimeBlock {
//     int TimeIndex;
//     double Time;
//     int NumberOfParticles;
//     int BlockSize = 0;

//     std::vector<std::unique_ptr<Particle>> Particles;

//     TimeBlock(){};

//     TimeBlock(int TimeIndex_, double Time_, int NumberOfParticles_) : TimeIndex(TimeIndex_), Time(Time_), NumberOfParticles(NumberOfParticles_) {}

//     void Add(Particle& particle) {
//         Particles.push_back(std::make_unique<Particle>(particle));
//     }
// };

// struct EventBlock {
//     int NumberOfBlocks;
//     std::vector<std::unique_ptr<TimeBlock>> TimeBlocks;

//     void Add(TimeBlock& timeblock) {
//         TimeBlocks.push_back(std::make_unique<TimeBlock>(timeblock));
//     }
// };

struct Line {
    Particle particle;
    Line(){};
};

struct Line_hanimate : Line {
    Line_hanimate() : Line(){};
};

std::istream& operator>>(std::istream& input, Line_hanimate& line) {
    input >> line.particle.ParticleLabel >> line.particle.PosX >> line.particle.PosY >> line.particle.PosZ >> line.particle.MomX >> line.particle.MomY >> line.particle.MomZ >> line.particle.Mass >> line.particle.ParticlePythiaID;
    return input;
}

// struct TimeBlock_hanimate : TimeBlock {
//     TimeBlock_hanimate() : TimeBlock(){};
//     TimeBlock_hanimate(int TimeIndex_, double Time_, int NumberOfParticles_) : TimeBlock(TimeIndex_, Time_, NumberOfParticles_) {}
// };

// std::istream& operator>>(std::istream& input, TimeBlock_hanimate& timeblock) {
//     input >> timeblock.Time;
//     return input;
// }

#endif