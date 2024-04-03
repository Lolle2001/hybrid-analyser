#ifndef DATAFORMAT_HPP
#define DATAFORMAT_HPP

#include <cmath>
#include <iomanip>
#include <istream>
#include <vector>
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

    int& GetParticlePythiaID() { return ParticlePythiaID; }
    double& GetMass() { return Mass; }
    double& GetPosT() { return PosT; }
    double& GetPosX() { return PosX; }
    double& GetPosY() { return PosY; }
    double& GetPosZ() { return PosZ; }
    double& GetMomX() { return MomX; }
    double& GetMomY() { return MomY; }
    double& GetMomZ() { return MomZ; }
    double& GetEnergy() { return Energy; }
    double& GetTransverseMomentum() { return TransverseMomentum; }
    double& GetTransverseMass() { return TransverseMass; }
    double& GetPseudoRapidity() { return PseudoRapidity; }
    double& GetRapidity() { return Rapidity; }
    double& GetMomentum() { return Momentum; }
    double& GetPhi() { return Phi; }
    double& GetAnisotropicFlow(int nharmonic) { return AnisotropicFlow[nharmonic]; }
};

class Line_ampt : public Line {
   private:
   public:
};

std::istream& operator>>(std::istream& input, Line_ampt& obj);
std::ostream& operator<<(std::ostream& output, Line_ampt& obj);

class Line_iss : public Line {
   private:
   public:
    Line_iss() : Line(){};
    Line_iss(int pid, float array[9]);
};

class Block {
   private:
    int EventID;
    int NumberOfParticles;
    double ImpactParameter;
    int NumberOfParticipantNucleons;
    int NumberOfBinaryCollisions;
    double ReactionPlaneAngle;

   public:
    Block() : EventID(0), NumberOfParticles(0), ImpactParameter(0.0), NumberOfParticipantNucleons(0), NumberOfBinaryCollisions(0), ReactionPlaneAngle(0.0){};

    Block(int eventID, int numParticles, double impactParam,
          int numParticipantNucleons, int numBinaryCollisions, double reactionPlaneAngle)
        : EventID(eventID), NumberOfParticles(numParticles), NumberOfBinaryCollisions(numBinaryCollisions), ImpactParameter(impactParam), NumberOfParticipantNucleons(numParticipantNucleons), ReactionPlaneAngle(reactionPlaneAngle) {}

    void SetEventID(int EventID_) { EventID = EventID_; }
    void SetNumberOfParticles(int NumberOfParticles_) { NumberOfParticles = NumberOfParticles_; }
    void SetImpactParameter(double ImpactParameter_) { ImpactParameter = ImpactParameter_; }
    void SetNumberOfParticipantNucleons(int NumberOfParticipantNucleons_) { NumberOfParticipantNucleons = NumberOfParticipantNucleons_; }
    void SetReactionPlaneAngle(double ReactionPlaneAngle_) { ReactionPlaneAngle = ReactionPlaneAngle_; };
    void SetNumberOfBinaryCollisions(int NumberOfBinaryCollisions_) { NumberOfBinaryCollisions = NumberOfBinaryCollisions_; }

    int& GetEventID() { return EventID; };
    int& GetNumberOfParticles() { return NumberOfParticles; }
    double& GetImpactParameter() { return ImpactParameter; }
    int& GetNumberOfParticipantNucleons() { return NumberOfParticipantNucleons; }
    int& GetNumberOfBinaryCollisions() { return NumberOfBinaryCollisions; }
    double& GetReactionPlaneAngle() { return ReactionPlaneAngle; }

    virtual void Write(std::ostream& output) const;
};

class Block_iss : public Block {
   private:
   public:
    Block_iss() : Block(){};

    // void Write(std::ostream& output) const override {
    //     Block::Write(output);
    // }
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
    void SetNumberOfParticipantNucleons_PROJ(int x) { NumberOfParticipantNucleons_PROJ = x; }
    void SetNumberOfParticipantNucleons_TARG(int x) { NumberOfParticipantNucleons_TARG = x; }
    void SetNumberOfParticipantNucleonsElastic_PROJ(int x) { NumberOfParticipantNucleonsElastic_PROJ = x; }
    void SetNumberOfParticipantNucleonsInelastic_PROJ(int x) { NumberOfParticipantNucleonsInelastic_PROJ = x; }
    void SetNumberOfParticipantNucleonsElastic_TARG(int x) { NumberOfParticipantNucleonsElastic_TARG = x; }
    void SetNumberOfParticipantNucleonsInelastic_TARG(int x) { NumberOfParticipantNucleonsInelastic_TARG = x; }

    int& GetEventIterationFlag() { return EventIterationFlag; }

    int& GetNumberOfParticipantNucleons_PROJ() { return NumberOfParticipantNucleons_PROJ; }

    int& GetNumberOfParticipantNucleons_TARG() { return NumberOfParticipantNucleons_TARG; }

    int& GetNumberOfParticipantNucleonsElastic_PROJ() { return NumberOfParticipantNucleonsElastic_PROJ; }

    int& GetNumberOfParticipantNucleonsInelastic_PROJ() { return NumberOfParticipantNucleonsInelastic_PROJ; }

    int& GetNumberOfParticipantNucleonsElastic_TARG() { return NumberOfParticipantNucleonsElastic_TARG; }

    int& GetNumberOfParticipantNucleonsInelastic_TARG() { return NumberOfParticipantNucleonsInelastic_TARG; }
    void Write(std::ostream& output) const override;
};

std::istream& operator>>(std::istream& input, Block_ampt& obj);

std::ostream& operator<<(std::ostream& output, Block_ampt& obj);

struct Log_ampt {
    int eventid;
    std::vector<int> eventiteration;
    std::vector<double> impactparameter;
    std::vector<int> ncoll;
};

std::ostream& operator<<(std::ostream& output, Log_ampt& obj);

}  // namespace Statistics

#endif