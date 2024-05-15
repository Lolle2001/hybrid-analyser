#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../Messenger.hpp"
#include "../Timer.hpp"
#include "../evolution-ampt/Evolution_ampt_parameters.hpp"
#include "Evolution_music_movie.hpp"

using PP = Utilities::PretyPrint;

void process_file(int argc, char **argv) {
    std::string runnumber = argv[1];
    std::string runbatch = argv[2];

    std::string parameterfile = "evo-music.par";
    if (argc > 3) {
        parameterfile = argv[3];
    }
    AMPT::Evolution::Parameters parameters(parameterfile);
    std::string datadirectory;
    AMPT::Evolution::json_to_parameter(parameters.params, "datadirectory", datadirectory);
    std::string filename = "evolution_for_movie_xyeta.dat";
    std::stringstream directory;
    directory << datadirectory << "/" << runnumber << "/" << runnumber << "_" << runbatch << "/" << filename;

    std::stringstream outputdirectory;
    std::string suboutputdirectory;
    AMPT::Evolution::json_to_parameter(parameters.params, "suboutputdirectory", suboutputdirectory);
    outputdirectory << datadirectory << "/" << runnumber << "/" << runnumber << "_" << runbatch << "/"
                    << suboutputdirectory;
    // mkdir(outputdirectory.str().c_str(), 0777);
    // read_evolution_file(directory.str(), outputdirectory.str());
    mkdir(outputdirectory.str().c_str(), 0777);
    std::unique_ptr<MUSIC::Evolution::File> file = std::make_unique<MUSIC::Evolution::File>(directory.str(), outputdirectory.str());

    file->Parse();
    file->Write(outputdirectory.str());
}

int main(int argc, char **argv) {
    std::cout << "Processing time evolution of surface..." << std::endl;
    Utilities::Duration Clock('M');
    Clock.Start();
    process_file(argc, argv);
    Clock.Stop();
    printf("%s : %s%03ld:%02ld.%03ld%s\n", "Processing time", PP::HIGHLIGHT, Clock.cminutes, Clock.cseconds, Clock.cmilliseconds, PP::RESET);
    fflush(stdout);
    return 0;
}