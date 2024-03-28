#include "DataFormat.hpp"

namespace Statistics {
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
    Phi = std::atan2(MomY, MomX) - RPA;
}

void Line::CalculateTransverseMomentum() {
    TransverseMomentumSQR = MomX * MomX + MomY * MomY;
    TransverseMomentum = std::sqrt(TransverseMomentumSQR);
}

void Line::CalculateAnisotropicFlow(int nharmonic) {
    // Needs phi
    AnisotropicFlow[nharmonic] = std::cos(nharmonic * Phi);
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
    Energy = std::sqrt(Mass * Mass + MomentumSQR);
    Rapidity = 0.5 * std::log((Energy + MomZ) / (Energy - MomZ));
}

void Line::CalculateProperties(int nharmonic_min, int nharmonic_max) {
    CalculateTransverseMomentum();
    CalculateMomentum();
    // CalculateEnergy();
    CalculatePhi();
    for (int i = nharmonic_min; i <= nharmonic_max; ++i) {
        CalculateAnisotropicFlow(i);
    }
    CalculatePseudoRapidity();
    CalculateRapidity();
}

}  // namespace Statistics