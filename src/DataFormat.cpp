#include "DataFormat.hpp"

namespace Statistics {

void Line::CalculateMomentum() {
    // Needs transverse momentum
    MomentumSQR = TransverseMomentumSQR + MomZ * MomZ;
    Momentum = std::sqrt(MomentumSQR);
}

void Line::CalculateEnergy() {
    // Needs momentum
    Energy = std::sqrt(Mass * Mass + MomentumSQR);
}

void Line::CalculatePhi() {
    Phi = std::atan2(MomY, MomX);
}
void Line::CalculatePhi(double RPA) {
    PhiOld = std::atan2(MomY, MomX);
    Phi = PhiOld - RPA;
}

void Line::CalculateAnisotropicFlowOld(int nharmonic) {
    AnisotropicFlowOld[nharmonic] = std::cos(nharmonic * PhiOld);
}

void Line::CalculateTransverseMomentum() {
    TransverseMomentumSQR = MomX * MomX + MomY * MomY;
    TransverseMomentum = std::sqrt(TransverseMomentumSQR);
}

void Line::CalculateAnisotropicFlow(int nharmonic) {
    // Needs phi
    AnisotropicFlow[nharmonic] = std::cos(nharmonic * Phi);
}

void Line::CalculateAnisotropicFlowSin(int nharmonic) {
    // Needs phi
    AnisotropicFlowSin[nharmonic] = std::sin(nharmonic * Phi);
}

void Line::CalculateAnisotropicFlowCos(int nharmonic) {
    // Needs phi
    AnisotropicFlowCos[nharmonic] = std::cos(nharmonic * Phi);
}

void Line::CalculateTransverseMass() {
    // Needs transverse momentum
    TransverseMass = std::sqrt(Mass * Mass + TransverseMomentumSQR);
}

void Line::CalculatePseudoRapidity() {
    // Needs momentum
    PseudoRapidity = std::atanh(MomZ / Momentum);
}

void Line::CalculateRapidity() {
    // Needs momentum and energy
    // Energy = std::sqrt(Mass * Mass + MomentumSQR);
    Rapidity = std::atanh(MomZ / Energy);
    // Rapidity = 0.5 * std::log((Energy + MomZ) / (Energy - MomZ));
}

void Line::CalculateProperties(int nharmonic_min, int nharmonic_max) {
    CalculateTransverseMomentum();
    CalculateMomentum();
    CalculateEnergy();
    CalculatePhi();
    for (int i = nharmonic_min; i <= nharmonic_max; ++i) {
        CalculateAnisotropicFlow(i);
    }
    CalculatePseudoRapidity();
    CalculateRapidity();
}

Line_iss::Line_iss(int pid, float array[9]) {
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
}

std::istream& operator>>(std::istream& input, Line_ampt& obj) {
    int ParticlePythiaID;
    double MomX;
    double MomY;
    double MomZ;
    double Mass;
    double PosX;
    double PosY;
    double PosZ;
    double FreezeOutTime;

    input >> ParticlePythiaID >> MomX >> MomY >> MomZ >> Mass >> PosX >> PosY >> PosZ >> FreezeOutTime;

    obj.SetParticlePythiaID(ParticlePythiaID);
    obj.SetMomX(MomX);
    obj.SetMomY(MomY);
    obj.SetMomZ(MomZ);
    obj.SetMass(Mass);
    obj.SetPosX(PosX);
    obj.SetPosY(PosY);
    obj.SetPosZ(PosZ);
    obj.SetPosT(FreezeOutTime);

    return input;
}

std::ostream& operator<<(std::ostream& output, Line_ampt& obj) {
    output << std::setw(5) << std::left << obj.GetParticlePythiaID() << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetPhi() << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetTransverseMomentum() << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetAnisotropicFlow(2) << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetAnisotropicFlowCos(2) << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetAnisotropicFlowSin(2) << " ";
    return output;
}

std::ostream& operator<<(std::ostream& output, Line_iss& obj) {
    output << std::setw(5) << std::left << obj.GetParticlePythiaID() << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetPhi() << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetTransverseMomentum() << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetAnisotropicFlow(2) << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetAnisotropicFlowCos(2) << " ";
    output << std::scientific << std::setw(13) << std::right << obj.GetAnisotropicFlowSin(2) << " ";
    return output;
}

void Block::Write(std::ostream& output) const {
    output << std::setw(6) << std::left << EventID << " "
           << std::setw(9) << std::left << NumberOfParticles << " "
           << std::scientific << std::setw(13) << std::left << NumberOfChargedParticles << " "
           << std::scientific << std::setw(13) << std::left << ImpactParameter << " "
           << std::setw(4) << std::left << NumberOfParticipantNucleons << " "
           << std::setw(6) << std::left << NumberOfBinaryCollisions << " ";
    for (int n = 1; n <= NUMBER_OF_HARMONICS; ++n) {
        output << std::scientific << std::setw(13) << std::right << EventPlaneAngle[n] << " ";
    }

    output << std::scientific << std::setw(13) << std::right << ReactionPlaneAngle;
}

void Block_ampt::Write(std::ostream& output) const {
    Block::Write(output);
    output << " <> "
           << std::setw(3) << std::left << EventIterationFlag << " "
           << std::setw(4) << std::left << NumberOfParticipantNucleons_PROJ << " "
           << std::setw(4) << std::left << NumberOfParticipantNucleons_TARG << " "
           << std::setw(4) << std::left << NumberOfParticipantNucleonsElastic_PROJ << " "
           << std::setw(4) << std::left << NumberOfParticipantNucleonsInelastic_PROJ << " "
           << std::setw(4) << std::left << NumberOfParticipantNucleonsElastic_TARG << " "
           << std::setw(4) << std::left << NumberOfParticipantNucleonsInelastic_TARG;
}

std::istream& operator>>(std::istream& input, Block_ampt& obj) {
    int EventID;
    int EventIterationFlag;
    int NumberOfParticles;
    double ImpactParameter;
    int NumberOfParticipantNucleons_PROJ;
    int NumberOfParticipantNucleons_TARG;
    int NumberOfParticipantNucleonsElastic_PROJ;
    int NumberOfParticipantNucleonsInelastic_PROJ;
    int NumberOfParticipantNucleonsElastic_TARG;
    int NumberOfParticipantNucleonsInelastic_TARG;
    double PhiRP;

    input >> EventID >> EventIterationFlag >> NumberOfParticles >> ImpactParameter >> NumberOfParticipantNucleons_PROJ >> NumberOfParticipantNucleons_TARG >> NumberOfParticipantNucleonsElastic_PROJ >> NumberOfParticipantNucleonsInelastic_PROJ >> NumberOfParticipantNucleonsElastic_TARG >> NumberOfParticipantNucleonsInelastic_TARG >> PhiRP;

    obj.SetEventID(EventID);
    obj.SetEventIterationFlag(EventIterationFlag);
    obj.SetNumberOfParticles(NumberOfParticles);
    obj.SetImpactParameter(ImpactParameter);
    obj.SetNumberOfParticipantNucleons_PROJ(NumberOfParticipantNucleons_PROJ);
    obj.SetNumberOfParticipantNucleons_TARG(NumberOfParticipantNucleons_TARG);
    obj.SetNumberOfParticipantNucleonsElastic_PROJ(NumberOfParticipantNucleonsElastic_PROJ);
    obj.SetNumberOfParticipantNucleonsInelastic_PROJ(NumberOfParticipantNucleonsInelastic_PROJ);
    obj.SetNumberOfParticipantNucleonsElastic_TARG(NumberOfParticipantNucleonsElastic_TARG);
    obj.SetNumberOfParticipantNucleonsInelastic_TARG(NumberOfParticipantNucleonsInelastic_TARG);
    obj.SetReactionPlaneAngle(PhiRP);
    obj.SetNumberOfParticipantNucleons(NumberOfParticipantNucleons_PROJ + NumberOfParticipantNucleons_TARG);

    return input;
}

std::ostream& operator<<(std::ostream& output, Block_ampt& obj) {
    output << std::setw(6) << std::left << obj.GetEventID() << " ";
    output << std::setw(3) << std::left << obj.GetEventIterationFlag() << " ";
    output << std::setw(9) << std::left << obj.GetNumberOfParticles() << " ";
    output << std::scientific << std::setw(13) << std::left << obj.GetImpactParameter() << " ";
    output << std::setw(3) << std::left << obj.GetNumberOfParticipantNucleons_PROJ() << " ";
    output << std::setw(3) << std::left << obj.GetNumberOfParticipantNucleons_TARG() << " ";
    output << std::setw(3) << std::left << obj.GetNumberOfParticipantNucleonsElastic_PROJ() << " ";
    output << std::setw(3) << std::left << obj.GetNumberOfParticipantNucleonsInelastic_PROJ() << " ";
    output << std::setw(3) << std::left << obj.GetNumberOfParticipantNucleonsElastic_TARG() << " ";
    output << std::setw(3) << std::left << obj.GetNumberOfParticipantNucleonsInelastic_TARG() << " ";
    output << std::scientific << std::setw(13) << std::left << obj.GetReactionPlaneAngle() << " ";
    return output;
}

std::ostream& operator<<(std::ostream& output, Log_ampt& obj) {
    output << obj.eventid << " ";
    output << obj.eventiteration.back() << " ";
    output << obj.impactparameter.back() << " ";
    output << obj.ncoll.back() << " ";
    return output;
}

}  // namespace Statistics