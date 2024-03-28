#ifndef DATAFORMAT_HPP
#define DATAFORMAT_HPP

#include <cmath>
#include <iomanip>
#include <istream>

namespace Statistics {

const unsigned int NUMBER_OF_HARMONICS = 5;

class Line {
   private:
    int ParticlePythiaID;
    double MomX;
    double MomY;
    double MomZ;
    double Mass;
    double PosX;
    double PosY;
    double PosZ;
    double PosT;

    double TransverseMomentum;
    double TransverseMomentumSQR;
    double Momentum;
    double MomentumSQR;
    double Energy;
    double TransverseMass;
    double AnisotropicFlow[NUMBER_OF_HARMONICS];
    double Phi;
    double PseudoRapidity;
    double Rapidity;

   public:
    Line(){};

    void CalculateTransverseMomentum();
    void CalculateMomentum();
    void CalculateEnergy();
    void CalculatePhi();
    void CalculatePhi(double RPA);
    void CalculateAnisotropicFlow(int nharmonic);
    void CalculateTransverseMass();
    void CalculatePseudoRapidity();
    void CalculateRapidity();

    void CalculateProperties(int nharmonic_min, int nharmonic_max);

    int& GetParticlePythiaID() { return ParticlePythiaID; }
    double& GetMass() { return Mass; }
    double& GetPosT() { return PosT; }
    double& GetPosX() { return PosX; }
    double& GetPosY() { return PosY; }
    double& GetPosZ() { return PosZ; }
    double& GetMomX() { return MomX; }
    double& GetMomY() { return MomY; }
    double& GetMomZ() { return MomZ; }

    void SetParticlePythiaID(int x) { ParticlePythiaID = x; }
    void SetMass(double x) { Mass = x; }
    void SetEnergy(double x) { Energy = x; }
    void SetPosT(double x) { PosT = x; }
    void SetPosX(double x) { PosX = x; }
    void SetPosY(double x) { PosY = x; }
    void SetPosZ(double x) { PosZ = x; }
    void SetMomX(double x) { MomX = x; }
    void SetMomY(double x) { MomY = x; }
    void SetMomZ(double x) { MomZ = x; }

    double& GetEnergy() { return Energy; }
    double& GetTransverseMomentum() { return TransverseMomentum; }
    double& GetTransverseMass() { return TransverseMass; }
    double& GetPseudoRapidity() { return PseudoRapidity; }
    double& GetRapidity() { return Rapidity; }
    double& GetMomentum() { return Momentum; }
    double& GetPhi() { return Phi; }
    double& GetAnisotropicFlow(int nharmonic) {
        return AnisotropicFlow[nharmonic];
    }
};

class Line_ampt : public Line {
   private:
   public:
};

std::istream& operator>>(std::istream& input, Line_ampt& obj);

class Line_iss : public Line {
    // double elem;
   private:
   public:
    Line_iss() : Line(){};
    Line_iss(int pid, float array[9]) {
        SetParticlePythiaID(pid);
        SetMass(array[0]);
        SetPosT(array[1]);
        SetPosX(array[2]);
        SetPosY(array[3]);
        SetPosZ(array[4]);
        SetEnergy(array[5]);
        SetMomX(array[6]);
        SetMomY(array[7]);
        SetMomZ(array[8]);
    };

    // void operator>>(double array[9]);
};

class Block {
   private:
    int EventID;
    int NumberOfParticles;
    double ImpactParameter;
    int NumberOfParticipantNucleons;
    double ReactionPlaneAngle;

   public:
    Block() : EventID(0), NumberOfParticles(0), ImpactParameter(0.0), NumberOfParticipantNucleons(0), ReactionPlaneAngle(0.0){};

    Block(int eventID, int numParticles, double impactParam,
          int numParticipantNucleons, double reactionPlaneAngle)
        : EventID(eventID), NumberOfParticles(numParticles), ImpactParameter(impactParam), NumberOfParticipantNucleons(numParticipantNucleons), ReactionPlaneAngle(reactionPlaneAngle) {}

    void SetEventID(int EventID_) { EventID = EventID_; }
    void SetNumberOfParticles(int NumberOfParticles_) {
        NumberOfParticles = NumberOfParticles_;
    }
    void SetImpactParameter(double ImpactParameter_) {
        ImpactParameter = ImpactParameter_;
    }
    void SetNumberOfParticipantNucleons(int NumberOfParticipantNucleons_) {
        NumberOfParticipantNucleons = NumberOfParticipantNucleons_;
    }
    void SetReactionPlaneAngle(double ReactionPlaneAngle_) {
        ReactionPlaneAngle = ReactionPlaneAngle_;
    };

    int GetEventID() const { return EventID; };
    int GetNumberOfParticles() const { return NumberOfParticles; }
    double& GetImpactParameter() { return ImpactParameter; }
    int GetNumberOfParticipantNucleons() const {
        return NumberOfParticipantNucleons;
    }
    double GetReactionPlaneAngle() const { return ReactionPlaneAngle; }

    virtual void Write(std::ostream& output) const {
        output << std::setw(6) << std::left << EventID << " "
               << std::setw(9) << std::left << NumberOfParticles << " "
               << std::scientific << std::setw(13) << std::left << ImpactParameter << " "
               << std::setw(4) << std::left << NumberOfParticipantNucleons << " "
               << std::scientific << std::setw(13) << ReactionPlaneAngle;
    }
};

// std::istream& operator>>(std::istream& input, Block_particles & obj);

class Block_iss : public Block {
   private:
    int NumberOfCollidingNucleons;

   public:
    Block_iss() : Block(){};
    void SetNumberOfCollidingNucleons(int NumberOfCollidingNucleons_) { NumberOfCollidingNucleons = NumberOfCollidingNucleons_; }

    void Write(std::ostream& output) const override {
        Block::Write(output);
        output << " "
               << std::setw(4) << std::left << NumberOfCollidingNucleons;
    }
};

class Block_ampt : public Block {
   private:
    int EventIterationFlag;
    int NumberOfParticipantNucleons_PROJ;
    int NumberOfParticipantNucleons_TARG;
    int NumberOfParticipantNucleonsElastic_PROJ;
    int NumberOfParticipantNucleonsInelastic_PROJ;
    int NumberOfParticipantNucleonsElastic_TARG;
    int NumberOfParticipantNucleonsInelastic_TARG;

   public:
    Block_ampt() : Block(){};

    void SetEventIterationFlag(int x) { EventIterationFlag = x; }
    void SetNumberOfParticipantNucleons_PROJ(int x) {
        NumberOfParticipantNucleons_PROJ = x;
    }
    void SetNumberOfParticipantNucleons_TARG(int x) {
        NumberOfParticipantNucleons_TARG = x;
    }
    void SetNumberOfParticipantNucleonsElastic_PROJ(int x) {
        NumberOfParticipantNucleonsElastic_PROJ = x;
    }
    void SetNumberOfParticipantNucleonsInelastic_PROJ(int x) {
        NumberOfParticipantNucleonsInelastic_PROJ = x;
    }
    void SetNumberOfParticipantNucleonsElastic_TARG(int x) {
        NumberOfParticipantNucleonsElastic_TARG = x;
    }
    void SetNumberOfParticipantNucleonsInelastic_TARG(int x) {
        NumberOfParticipantNucleonsInelastic_TARG = x;
    }

    int GetEventIterationFlag() const { return EventIterationFlag; }

    int GetNumberOfParticipantNucleons_PROJ() const {
        return NumberOfParticipantNucleons_PROJ;
    }

    int GetNumberOfParticipantNucleons_TARG() const {
        return NumberOfParticipantNucleons_TARG;
    }

    int GetNumberOfParticipantNucleonsElastic_PROJ() const {
        return NumberOfParticipantNucleonsElastic_PROJ;
    }

    int GetNumberOfParticipantNucleonsInelastic_PROJ() const {
        return NumberOfParticipantNucleonsInelastic_PROJ;
    }

    int GetNumberOfParticipantNucleonsElastic_TARG() const {
        return NumberOfParticipantNucleonsElastic_TARG;
    }

    int GetNumberOfParticipantNucleonsInelastic_TARG() const {
        return NumberOfParticipantNucleonsInelastic_TARG;
    }
    void Write(std::ostream& output) const override {
        Block::Write(output);
        output << " "
               << std::setw(3) << std::left << EventIterationFlag << " "
               << std::setw(4) << std::left << NumberOfParticipantNucleons_PROJ << " "
               << std::setw(4) << std::left << NumberOfParticipantNucleons_TARG << " "
               << std::setw(4) << std::left << NumberOfParticipantNucleonsElastic_PROJ << " "
               << std::setw(4) << std::left << NumberOfParticipantNucleonsInelastic_PROJ << " "
               << std::setw(4) << std::left << NumberOfParticipantNucleonsElastic_TARG << " "
               << std::setw(4) << std::left << NumberOfParticipantNucleonsInelastic_TARG;
    }

    // void SetEventIterationFlag
};

std::istream& operator>>(std::istream& input, Block_ampt& obj);

std::ostream& operator<<(std::ostream& output, Block_ampt& obj);

// void Line_iss::operator>>(double array[9]){
//     this -> elem;

// }
}  // namespace Statistics

#endif