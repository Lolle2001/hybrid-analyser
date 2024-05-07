
#include <sys/stat.h>

#include <sstream>

#include "Evolution_ampt_hanimate.hpp"
#include "Evolution_ampt_panimate.hpp"
#include "Evolution_ampt_pfinalft.hpp"
int main(int argc, char **argv) {
    std::string Runnumber = argv[1];
    std::string Datadirectory = argv[2];
    int partonincluded = std::stoi(argv[3]);
    if (partonincluded == 0 || partonincluded == 2) {
        std::stringstream animationfile;
        animationfile << Datadirectory << "/" << Runnumber << "/" << Runnumber << "_1"
                      << "/ana1/h-animate.dat";
        AMPT::AMPT_hanimate *hanimate = new AMPT::AMPT_hanimate(animationfile.str());

        hanimate->ReadFile();
        // hanimate->PrintParticleCounts(std::cout);
        std::stringstream directory;
        directory << Datadirectory << "/" << Runnumber << "/"
                  << "evolution";
        mkdir(directory.str().c_str(), 0777);

        hanimate->PrintParticleEnergyDensity(directory.str());
        std::stringstream filename;
        filename << directory.str() << "/"
                 << "hadron-info.dat";
        std::ofstream file(filename.str());

        hanimate->PrintInfo(file);
        file.close();

        filename.str("");
        filename.clear();
        filename << directory.str() << "/"
                 << "hadron-count.dat";
        file = std::ofstream(filename.str());

        hanimate->PrintParticleCounts(file);
        file.close();
        delete hanimate;
    }
    if (partonincluded == 1 || partonincluded == 2) {
        std::stringstream animationfile;
        animationfile << Datadirectory << "/" << Runnumber << "/" << Runnumber << "_1"
                      << "/ana1/p-finalft.dat";
        AMPT::AMPT_pfinalft *pfinalft = new AMPT::AMPT_pfinalft(animationfile.str());
        pfinalft->ReadFile();
        pfinalft->MakeFreezeOutMap();
        animationfile.str("");
        animationfile.clear();
        animationfile << Datadirectory << "/" << Runnumber << "/" << Runnumber << "_1"
                      << "/ana1/p-animate.dat";
        AMPT::AMPT_panimate *panimate = new AMPT::AMPT_panimate(animationfile.str());
        panimate->Parse(pfinalft);
        std::stringstream directory;
        directory << Datadirectory << "/" << Runnumber << "/"
                  << "evolution";
        mkdir(directory.str().c_str(), 0777);

        panimate->PrintPartonEnergyDensity(directory.str());
        std::stringstream filename;
        filename << directory.str() << "/"
                 << "parton-info.dat";
        std::ofstream file(filename.str());

        panimate->PrintInfo(file);
        file.close();
        filename.str("");
        filename.clear();
        filename << directory.str() << "/"
                 << "parton-count.dat";
        file = std::ofstream(filename.str());

        panimate->Write(file);

        file.close();

        delete panimate;
        delete pfinalft;
    }

    return 0;
}
