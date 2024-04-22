
#include <sys/stat.h>

#include "Evolution_ampt_hanimate.hpp"
#include "Evolution_ampt_panimate.hpp"
#include "Evolution_ampt_pfinalft.hpp"
int main(int argc, char** argv) {
    std::string Runnumber = argv[1];
    int partonincluded = std::stoi(argv[2]);
    if (partonincluded == 0 || partonincluded == 2) {
        AMPT::AMPT_hanimate* hanimate = new AMPT::AMPT_hanimate("/home/lieuwe/Documents/Software/AMPT/data/" + Runnumber + "/" + Runnumber + "_1/ana1/h-animate.dat");

        hanimate->ReadFile();
        // hanimate->PrintParticleCounts(std::cout);
        mkdir(("test/amptevo_" + Runnumber).c_str(), 0777);
        hanimate->PrintParticleEnergyDensity("test/amptevo_" + Runnumber);
        std::ofstream file("test/amptevo_" + Runnumber + "/info.dat");

        hanimate->PrintInfo(file);
        file.close();
        delete hanimate;
    }
    if (partonincluded == 1 || partonincluded == 2) {
        AMPT::AMPT_pfinalft* pfinalft = new AMPT::AMPT_pfinalft("/home/lieuwe/Documents/Software/AMPT/data/" + Runnumber + "/" + Runnumber + "_1/ana1/p-finalft.dat");
        pfinalft->ReadFile();
        pfinalft->MakeFreezeOutMap();
        AMPT::AMPT_panimate* panimate = new AMPT::AMPT_panimate("/home/lieuwe/Documents/Software/AMPT/data/" + Runnumber + "/" + Runnumber + "_1/ana1/p-animate.dat");
        panimate->Parse(pfinalft);

        panimate->PrintPartonEnergyDensity("test/amptevo_" + Runnumber);
        std::ofstream file("test/amptevo_" + Runnumber + "/p-info.dat");

        panimate->PrintInfo(file);
        file.close();
        delete panimate;
        delete pfinalft;
    }

    return 0;
}