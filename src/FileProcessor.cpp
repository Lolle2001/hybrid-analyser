#include "FileProcessor.hpp"

void ReadSettings(Parameters& parameters, std::string filename) {
    std::ifstream file;

    // std::cout << filename.str() << std::endl;
    bool after_equal = false;
    file.open(filename, std::ios::in);
    if (file.is_open()) {
        std::string line;
        std::string dummy1, dummy2, dummy3;
        while (std::getline(file, line)) {
            // std::cout << dummy1 << std::endl;

            if (line.find("ipglasma_data_folder") != std::string::npos) {
                std::istringstream iss(line);
                iss >> dummy2 >> dummy3 >> parameters.ipglasma_data_folder;
            }

            if (line.find("iss_data_folder") != std::string::npos) {
                std::istringstream iss(line);
                iss >> dummy2 >> dummy3 >> parameters.iss_data_folder;
            }

            if (line.find("result_folder") != std::string::npos) {
                std::istringstream iss(line);
                iss >> dummy2 >> dummy3 >> parameters.result_folder;
            }
            if (line.find("ampt_data_folder") != std::string::npos) {
                std::istringstream iss(line);
                iss >> dummy2 >> dummy3 >> parameters.ampt_data_folder;
            }
        }
    } else {
        std::cout << "Failed to open file" << std::endl;
    }

    file.close();
}

namespace AMPT {
void ReadFiles(int NRun, int NBatchMin, int NBatchMax, std::string Directory, Parameters& parameters, int collisiontype) {
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s : %d(%d)\n", "Reading data from run (size)", NRun, NBatchMax - NBatchMin + 1);
    fflush(stdout);

    // Directory = parameters.ampt_data_folder;

    std::unique_ptr<Model::File_ampt> campt = std::make_unique<Model::File_ampt>(collisiontype);

    campt->InitializeDataContainer();
    std::vector<std::unique_ptr<Model::File_ampt>> data;

    int BatchSize = NBatchMax - NBatchMin + 1;

    data.resize(BatchSize);

    // std::cout << BatchSize << std::endl;

    double FileSize = 0;
    for (int i = 0; i < BatchSize; ++i) {
        std::stringstream FileDirectory;
        FileDirectory << Directory << "/" << NRun << "/" << NRun << "_" << i + NBatchMin << "/ana/ampt.dat";

        FileSize += Utilities::GetFileSize(FileDirectory.str(), 3);
    }
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%-14s : %s\n", "Reading data from", (Directory + "/" + std::to_string(NRun)).c_str());
    fflush(stdout);
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s : %s%.3f GB%s\n", "Total datasize to read", PP::HIGHLIGHT, FileSize, PP::RESET);
    fflush(stdout);

    std::string barstring = std::string(PP::BOLD) + std::string(PP::BLUE) + "[INFO] " + std::string(PP::RESET);
    Utilities::Progressbar pbar(BatchSize);
    pbar.SetFrontString(barstring);
    pbar.SetDoneChar("█");
    pbar.SetTodoChar("░");
    pbar.SetStartChar("║");  //"▕");
    pbar.SetEndChar("║");    //"▏");

    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s\n", "Initializing histograms...");
    fflush(stdout);

    pbar.Print();

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < BatchSize; ++i) {
            std::stringstream FileDirectory;
            std::stringstream LogDirectory;
            FileDirectory << Directory << "/" << NRun << "/" << NRun << "_" << i + NBatchMin << "/ana/ampt.dat";
            LogDirectory << Directory << "/" << NRun << "/" << NRun << "_" << i + NBatchMin << "/" << NRun << "_" << i + NBatchMin << ".log";
            data[i] = std::make_unique<Model::File_ampt>(LogDirectory.str(), FileDirectory.str(), collisiontype);
            data[i]->InitializeDataContainer();
            // data[i]->ParseLog();
            pbar.Update();
#pragma omp critical
            {
                pbar.Print();
            }
        }
    }

    Utilities::Duration Clock('M');
    Clock.Start();
    printf("\n");
    fflush(stdout);
    pbar.Reset();
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s\n", "Reading files...");
    fflush(stdout);
    pbar.Print();

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < BatchSize; ++i) {
            data[i]->Parse();

            pbar.Update();
#pragma omp critical
            {
                pbar.Print();
            }
        }
    }
    printf("\n");
    fflush(stdout);

    for (int i = 0; i < BatchSize; ++i) {
        *campt += *data[i];
    }

    Clock.Stop();

    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%03ld:%02ld.%03ld%s\n", "Reading time", PP::HIGHLIGHT, Clock.cminutes, Clock.cseconds, Clock.cmilliseconds, PP::RESET);
    fflush(stdout);

    Clock.Start();

    std::stringstream datadirectory;
    datadirectory << Directory << "/" << NRun << "/"
                  << "processed";
    system(("mkdir -p \"" + datadirectory.str() + "\"").c_str());
    campt->WriteData(datadirectory.str());

    Clock.Stop();

    long double totalsize = 0;
    std::filesystem::recursive_directory_iterator datadirectory_iter(datadirectory.str());
    for (const auto& entry : datadirectory_iter) {
        totalsize += Utilities::GetFileSize(entry.path(), 2);
        // std::cout <<  << std::endl;
    }

    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%03ld:%02ld.%03ld%s\n", "Writing time", PP::HIGHLIGHT, Clock.cminutes, Clock.cseconds, Clock.cmilliseconds, PP::RESET);
    fflush(stdout);
    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%-14s : %s\n", "Writen data to", datadirectory.str().c_str());
    fflush(stdout);
    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%.3Lf MB%s\n", "Total datasize written", PP::HIGHLIGHT, totalsize, PP::RESET);
    fflush(stdout);
}
}  // namespace AMPT

namespace iSS {

// If initial state info is coppied into the correct music folder and then iss folder,
// then initial state info can be accessed more easily. Or a file should be made where
// a list of all initial state info is stored.
Statistics::Block_iss GetInitialStateInfo(int NRun, int eventid, Parameters& parameters) {
    std::ifstream file;

    Statistics::Block_iss block;

    std::stringstream filename;

    filename << parameters.ipglasma_data_folder << "/" << NRun << "/usedParameters" << eventid << ".dat";
    // std::cout << filename.str() << std::endl;

    file.open(filename.str(), std::ios::in);
    if (file.is_open()) {
        std::string dummy1, dummy2, dummy3;
        double value;
        while (std::getline(file, dummy1)) {
            // std::cout << dummy1 << std::endl;

            if (dummy1.find("b = ") != std::string::npos) {
                std::istringstream iss(dummy1);
                iss >> dummy2 >> dummy3 >> value;
                block.SetImpactParameter(value);
            }

            if (dummy1.find("Npart = ") != std::string::npos) {
                std::istringstream iss(dummy1);
                iss >> dummy2 >> dummy3 >> value;
                block.SetNumberOfParticipantNucleons(value);
            }

            if (dummy1.find("Ncoll = ") != std::string::npos) {
                std::istringstream iss(dummy1);
                iss >> dummy2 >> dummy3 >> value;
                block.SetNumberOfBinaryCollisions(value);
            }
        }
    } else {
        std::cout << "Failed to open file" << std::endl;
    }

    file.close();
    return block;
}

void ReadFiles(int iSSRun, int IPGlasmaRun, int NEvent, std::string parametername, int collisiontype) {
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s : %d(%d)\n", "Reading data from run (size)", iSSRun, NEvent);
    fflush(stdout);

    Parameters parameters;
    ReadSettings(parameters, parametername);

    std::unique_ptr<Model::File_iss> ciss = std::make_unique<Model::File_iss>(collisiontype);
    ciss->InitializeDataContainer();
    std::vector<std::unique_ptr<Model::File_iss>> data;

    data.resize(NEvent);

    double FileSize = 0;
    for (int i = 0; i < NEvent; ++i) {
        std::stringstream directory;
        directory << parameters.iss_data_folder << "/" << iSSRun << "/" << iSSRun << "_" << std::to_string(i) << "/particle_samples.bin";

        FileSize += Utilities::GetFileSize(directory.str(), 3);
    }
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%-14s : %s\n", "Reading data from", (parameters.iss_data_folder + "/" + std::to_string(iSSRun)).c_str());
    fflush(stdout);
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s : %s%.3f GB%s\n", "Total datasize to read", PP::HIGHLIGHT, FileSize, PP::RESET);
    fflush(stdout);

    std::string barstring = std::string(PP::BOLD) + std::string(PP::BLUE) + "[INFO] " + std::string(PP::RESET);
    Utilities::Progressbar pbar(NEvent);
    pbar.SetFrontString(barstring);
    pbar.SetDoneChar("█");
    pbar.SetTodoChar("░");
    pbar.SetStartChar("║");  //"▕");
    pbar.SetEndChar("║");    //"▏");

    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s\n", "Initializing histograms...");
    fflush(stdout);

    pbar.Print();

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < NEvent; ++i) {
            Statistics::Block_iss block = GetInitialStateInfo(IPGlasmaRun, i, parameters);

            block.SetEventID(i);
            std::stringstream directory;
            directory << parameters.iss_data_folder << "/" << iSSRun << "/" << iSSRun << "_" << std::to_string(i) << "/particle_samples.bin";

            data[i] = std::make_unique<Model::File_iss>(directory.str(), collisiontype);
            data[i]->SetInitialState(block);
            data[i]->InitializeDataContainer();

            pbar.Update();
#pragma omp critical
            {
                pbar.Print();
            }
        }
    }

    Utilities::Duration Clock('M');
    Clock.Start();
    printf("\n");
    fflush(stdout);
    pbar.Reset();
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s\n", "Reading files...");
    fflush(stdout);

    pbar.Print();

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < NEvent; ++i) {
            data[i]->Parse();

            pbar.Update();

#pragma omp critical
            {
                pbar.Print();
            }
        }
    }
    printf("\n");
    fflush(stdout);

    for (int i = 0; i < NEvent; ++i) {
        *ciss += *data[i];
    }
    Clock.Stop();

    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%03ld:%02ld.%03ld%s\n", "Reading time", PP::HIGHLIGHT, Clock.cminutes, Clock.cseconds, Clock.cmilliseconds, PP::RESET);
    fflush(stdout);

    Clock.Start();

    std::stringstream directory;
    directory << parameters.iss_data_folder << "/" << iSSRun << "/" << parameters.result_folder;
    std::stringstream command;
    command << "mkdir -p " << directory.str();

    system(command.str().c_str());

    ciss->WriteData(directory.str());

    Clock.Stop();
    long double totalsize = 0;
    std::filesystem::recursive_directory_iterator datadirectory_iter(directory.str());
    for (const auto& entry : datadirectory_iter) {
        totalsize += Utilities::GetFileSize(entry.path(), 2);
        // std::cout <<  << std::endl;
    }

    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%03ld:%02ld.%03ld%s\n", "Writing time", PP::HIGHLIGHT, Clock.cminutes, Clock.cseconds, Clock.cmilliseconds, PP::RESET);
    fflush(stdout);
    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%-14s : %s\n", "Writen data to", directory.str().c_str());
    fflush(stdout);
    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%.3Lf MB%s\n", "Total datasize written", PP::HIGHLIGHT, totalsize, PP::RESET);
    fflush(stdout);
}

}  // namespace iSS
