#ifndef DATAFORMAT_HPP
#define DATAFORMAT_HPP

#include <cmath>
#include <iomanip>
#include <istream>
#include <vector>
namespace Statistics {

const unsigned int NUMBER_OF_HARMONICS = 2;

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
    double AnisotropicFlow[NUMBER_OF_HARMONICS + 1] = {0};
    double AnisotropicFlowOld[NUMBER_OF_HARMONICS + 1] = {0};
    double Phi;
    double PhiOld;
    double PseudoRapidity;
    double Rapidity;

    double AnisotropicFlowSin[NUMBER_OF_HARMONICS + 1] = {0};
    double AnisotropicFlowCos[NUMBER_OF_HARMONICS + 1] = {0};

   public:
    Line(){};

    void CalculateTransverseMomentum();
    void CalculateMomentum();
    void CalculateEnergy();
    void CalculatePhi();
    void CalculatePhi(double RPA);
    void CalculateAnisotropicFlow(int nharmonic);
    void CalculateAnisotropicFlowOld(int nharmonic);
    void CalculateTransverseMass();
    void CalculatePseudoRapidity();
    void CalculateRapidity();
    void CalculateProperties(int nharmonic_min, int nharmonic_max);

    void CalculateAnisotropicFlowSin(int nharmonic);
    void CalculateAnisotropicFlowCos(int nharmonic);

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
    double& GetAnisotropicFlowOld(int nharmonic) { return AnisotropicFlowOld[nharmonic]; }
    double GetAnisotropicFlowSin(int nharmonic) { return AnisotropicFlowSin[nharmonic]; };
    double GetAnisotropicFlowCos(int nharmonic) { return AnisotropicFlowCos[nharmonic]; };
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

std::ostream& operator<<(std::ostream& output, Line_iss& obj);

class Block {
   private:
    int EventID;
    int NumberOfParticles;
    double NumberOfChargedParticles = 0;
    double ImpactParameter;
    int NumberOfParticipantNucleons;
    int NumberOfBinaryCollisions;
    double ReactionPlaneAngle;
    double EventPlaneAngle[NUMBER_OF_HARMONICS + 1] = {0};

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

    void SetNumberOfChargedParticles(int x) { NumberOfChargedParticles = x; };
    double& GetNumberOfChargedParticles() { return NumberOfChargedParticles; };

    int& GetEventID() { return EventID; };
    int& GetNumberOfParticles() { return NumberOfParticles; }
    double& GetImpactParameter() { return ImpactParameter; }
    int& GetNumberOfParticipantNucleons() { return NumberOfParticipantNucleons; }
    int& GetNumberOfBinaryCollisions() { return NumberOfBinaryCollisions; }
    double& GetReactionPlaneAngle() { return ReactionPlaneAngle; }

    void SetEventPlaneAngle(int n, double x) { EventPlaneAngle[n] = x; }

    void CalculateEventPlaneAngle(int n, double& vnsin, double& vncos) {
        if (vncos > 0) {
            double angle = (1. / (double)n) * std::atan(vnsin / vncos);
            if (angle < 0) {
                angle += 2 * M_PI;
            }
            EventPlaneAngle[n] = angle;
        } else {
            EventPlaneAngle[n] = M_PI_2;
        }
    }
    double GetEventPlaneAngle(int n) { return EventPlaneAngle[n]; };

    virtual void Write(std::ostream& output) const;
};

class Block_iss : public Block {
   private:
    unsigned int OriginalEventID;

   public:
    Block_iss() : Block(){};

    void Write(std::ostream& output) const override {
        Block::Write(output);
        output << " <> "
               << std::setw(6) << std::left << OriginalEventID;
    }
    void SetOriginalEventID(unsigned int x) {
        OriginalEventID = x;
    }
    unsigned int& GetOriginalEventID() {
        return OriginalEventID;
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