
#include <sys/stat.h>

#include <sstream>

#include "../Timer.hpp"
// #include "Evolution_ampt_hanimate.hpp"
#include "Evolution_ampt_hanimate_2.hpp"
// #include "Evolution_ampt_panimate.hpp"
#include "Evolution_ampt_panimate_2.hpp"
#include "Evolution_ampt_parameters.hpp"
// #include "Evolution_ampt_pfinalft.hpp"
#include "Evolution_ampt_pfinalft_2.hpp"

int test_hadron(int argc, char **argv, AMPT::Evolution::Parameters &parameters) {
    std::string runnumber = argv[1];
    std::string batchnumber = "1";
    if (argc > 4) {
        batchnumber = argv[4];
    }

    std::stringstream sourcedirectory;
    std::stringstream outputdirectory;

    std::stringstream hadron_animation_file;

    sourcedirectory << (std::string)parameters.params["datadirectory"] << "/";
    sourcedirectory << runnumber << "/" << runnumber << "_" << batchnumber << "/";
    sourcedirectory << (std::string)parameters.params["sourcedirectory"];

    outputdirectory << (std::string)parameters.params["datadirectory"] << "/";
    outputdirectory << runnumber << "/";
    outputdirectory << (std::string)parameters.params["outputdirectory"];

    hadron_animation_file << sourcedirectory.str() << "/";
    hadron_animation_file << (std::string)parameters.params["hadron-animation-file"];

    mkdir(outputdirectory.str().c_str(), 0777);

    std::unique_ptr<AMPT::Evolution::Hadron::File> hanimate = std::make_unique<AMPT::Evolution::Hadron::File>(hadron_animation_file.str(), outputdirectory.str());

    hanimate->ReadFileMulti();

    hanimate->PrintParticleEnergyDensity(outputdirectory.str());

    std::stringstream hadron_info_file;
    hadron_info_file << outputdirectory.str() << "/" << "hadron-info.dat";
    std::ofstream file(hadron_info_file.str());
    hanimate->PrintInfo(file);
    file.close();

    std::stringstream hadron_count_file;
    hadron_count_file << outputdirectory.str() << "/" << "hadron-count.dat";
    file = std::ofstream(hadron_count_file.str());
    hanimate->PrintParticleCounts(file);
    file.close();

    return 0;
}

int test_parton(int argc, char **argv, AMPT::Evolution::Parameters &parameters) {
    std::string runnumber = argv[1];
    std::string batchnumber = "1";
    if (argc > 4) {
        batchnumber = argv[4];
    }

    std::stringstream sourcedirectory;
    std::stringstream outputdirectory;

    std::stringstream parton_animation_file;
    std::stringstream parton_freezeout_file;

    sourcedirectory << (std::string)parameters.params["datadirectory"] << "/";
    sourcedirectory << runnumber << "/" << runnumber << "_" << batchnumber << "/";
    sourcedirectory << (std::string)parameters.params["sourcedirectory"];

    outputdirectory << (std::string)parameters.params["datadirectory"] << "/";
    outputdirectory << runnumber << "/";
    outputdirectory << (std::string)parameters.params["outputdirectory"];

    parton_animation_file << sourcedirectory.str() << "/";
    parton_animation_file << (std::string)parameters.params["parton-animation-file"];

    parton_freezeout_file << sourcedirectory.str() << "/";
    parton_freezeout_file << (std::string)parameters.params["parton-freeze-out-list"];

    std::shared_ptr<AMPT::Evolution::Parton::Freezeout::File> pfinalft = std::make_shared<AMPT::Evolution::Parton::Freezeout::File>(parton_freezeout_file.str());
    pfinalft->ReadFile();
    pfinalft->MakeFreezeOutMap();

    std::unique_ptr<AMPT::Evolution::Parton::File> panimate = std::make_unique<AMPT::Evolution::Parton::File>(parton_animation_file.str());
    panimate->Parse(pfinalft);

    mkdir(outputdirectory.str().c_str(), 0777);

    panimate->PrintPartonEnergyDensity(outputdirectory.str());

    std::stringstream parton_info_file;
    parton_info_file << outputdirectory.str() << "/" << "parton-info.dat";
    std::ofstream file(parton_info_file.str());
    panimate->PrintInfo(file);
    file.close();

    std::stringstream parton_count_file;
    parton_count_file << outputdirectory.str() << "/" << "parton-count.dat";
    file = std::ofstream(parton_count_file.str());
    panimate->Write(file);
    file.close();

    return 0;
}

int main(int argc, char **argv) {
    std::string runnumber = argv[1];
    std::string parameterfile = argv[2];
    int partonincluded = std::stoi(argv[3]);
    AMPT::Evolution::Parameters parameters(parameterfile);
    parameters.Print(std::cout);
    if (partonincluded == 0 || partonincluded == 2) {
        std::cout << "Processing animation data for hadrons..." << std::endl;
        Utilities::Duration Clock('M');
        Clock.Start();
        test_hadron(argc, argv, parameters);
        Clock.Stop();
        printf("%s : %s%03ld:%02ld.%03ld%s\n", "Processing time", PP::HIGHLIGHT, Clock.cminutes, Clock.cseconds, Clock.cmilliseconds, PP::RESET);
        fflush(stdout);
    }
    if (partonincluded == 1 || partonincluded == 2) {
        std::cout << "Processing animation data for partons..." << std::endl;
        Utilities::Duration Clock('M');
        Clock.Start();
        test_parton(argc, argv, parameters);
        Clock.Stop();
        printf("%s : %s%03ld:%02ld.%03ld%s\n", "Processing time", PP::HIGHLIGHT, Clock.cminutes, Clock.cseconds, Clock.cmilliseconds, PP::RESET);
        fflush(stdout);
    }
    return 0;
}

// int readfiles(int argc, char **argv) {
//     std::string Runnumber = argv[1];
//     std::string Datadirectory = argv[2];
//     int partonincluded = std::stoi(argv[3]);
//     if (partonincluded == 0 || partonincluded == 2) {
//         std::stringstream animationfile;
//         animationfile << Datadirectory << "/" << Runnumber << "/" << Runnumber << "_1"
//                       << "/ana1/h-animate.dat";
//         AMPT::AMPT_hanimate *hanimate = new AMPT::AMPT_hanimate(animationfile.str());

//         hanimate->ReadFile();
//         // hanimate->PrintParticleCounts(std::cout);
//         std::stringstream directory;
//         directory << Datadirectory << "/" << Runnumber << "/"
//                   << "evolution";
//         mkdir(directory.str().c_str(), 0777);

//         hanimate->PrintParticleEnergyDensity(directory.str());
//         std::stringstream filename;
//         filename << directory.str() << "/"
//                  << "hadron-info.dat";
//         std::ofstream file(filename.str());

//         hanimate->PrintInfo(file);
//         file.close();

//         filename.str("");
//         filename.clear();
//         filename << directory.str() << "/"
//                  << "hadron-count.dat";
//         file = std::ofstream(filename.str());

//         hanimate->PrintParticleCounts(file);
//         file.close();
//         delete hanimate;
//     }
//     if (partonincluded == 1 || partonincluded == 2) {
//         std::stringstream animationfile;
//         animationfile << Datadirectory << "/" << Runnumber << "/" << Runnumber << "_1"
//                       << "/ana1/p-finalft.dat";
//         AMPT::AMPT_pfinalft *pfinalft = new AMPT::AMPT_pfinalft(animationfile.str());
//         pfinalft->ReadFile();
//         pfinalft->MakeFreezeOutMap();
//         animationfile.str("");
//         animationfile.clear();
//         animationfile << Datadirectory << "/" << Runnumber << "/" << Runnumber << "_1"
//                       << "/ana1/p-animate.dat";
//         AMPT::AMPT_panimate *panimate = new AMPT::AMPT_panimate(animationfile.str());
//         panimate->Parse(pfinalft);
//         std::stringstream directory;
//         directory << Datadirectory << "/" << Runnumber << "/"
//                   << "evolution";
//         mkdir(directory.str().c_str(), 0777);

//         panimate->PrintPartonEnergyDensity(directory.str());
//         std::stringstream filename;
//         filename << directory.str() << "/"
//                  << "parton-info.dat";
//         std::ofstream file(filename.str());

//         panimate->PrintInfo(file);
//         file.close();
//         filename.str("");
//         filename.clear();
//         filename << directory.str() << "/"
//                  << "parton-count.dat";
//         file = std::ofstream(filename.str());

//         panimate->Write(file);

//         file.close();

//         delete panimate;
//         delete pfinalft;
//     }

//     return 0;
// }
