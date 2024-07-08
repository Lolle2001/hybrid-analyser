// Copyright (C) 2024 Lieuwe Huisman
#include "FileProcessor.hpp"

namespace AMPT {

void ProcessFiles(
    std::vector<std::filesystem::path> datafiles,
    std::vector<std::filesystem::path> logfiles,
    unsigned int collisiontype,
    std::filesystem::path output_directory) {
    std::string barstring;
    Utilities::Progressbar progressbar;
    std::string logstring;
    Utilities::Duration timer('H');

    size_t number_of_files = datafiles.size();

    barstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    progressbar = Utilities::Progressbar(number_of_files);
    progressbar.SetFrontString(barstring);
    // progressbar.SetDoneChar("█");
    progressbar.SetDoneChar(std::string("\033[38;2;57;181;74m█") + PP::RESET);
    progressbar.SetTodoChar("░");
    progressbar.SetStartChar("║");  //"▕");
    progressbar.SetEndChar("║");

    double filesize_data = 0;
    for (index_t i = 0; i < number_of_files; ++i) {
        filesize_data += Utilities::GetFileSize(datafiles[i], 3);
        filesize_data += Utilities::GetFileSize(logfiles[i], 3);
    }
    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Number of files to read : {}{}{}", PP::HIGHLIGHT, number_of_files, PP::RESET);
    std::cout << logstring << std::endl;
    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Total datasize to read : {}{:.3} GB{}", PP::HIGHLIGHT, filesize_data, PP::RESET);
    std::cout << logstring << std::endl;

    std::unique_ptr<Model::File_ampt> data_container_combined = std::make_unique<Model::File_ampt>(collisiontype);
    std::vector<std::unique_ptr<Model::File_ampt>> data_container(number_of_files);

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Initializing file objects ...");
    std::cout << logstring << std::endl;

    progressbar.Print();
    timer.Start();

#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (index_t i = 0; i < number_of_files; ++i) {
            data_container[i] = std::make_unique<Model::File_ampt>(logfiles[i], datafiles[i], collisiontype);
            progressbar.Update();

#pragma omp critical
            {
                progressbar.Print();
            }
        }
    }

    std::cout << std::endl;

    progressbar.Reset();

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Parsing event statistics ...");
    std::cout << logstring << std::endl;

    progressbar.Print();
#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (index_t i = 0; i < number_of_files; ++i) {
            data_container[i]->ParseEventStatistics();
            progressbar.Update();

#pragma omp critical
            {
                progressbar.Print();
            }
        }
    }
    std::cout << std::endl;

    std::unique_ptr<Model::File_ampt> dummy = std::make_unique<Model::File_ampt>(collisiontype);
    for (index_t i = 0; i < number_of_files; ++i) {
        dummy->GetFileData().InsertBlocks(data_container[i]->GetFileData());
    }

    dummy->GetFileData().CalculateCentralityClasses();

    for (index_t i = 0; i < number_of_files; ++i) {
        data_container[i]->GetFileData().SetCentralityEdges("ncharged", dummy->GetFileData().GetCentralityEdges("ncharged"));
    }
    data_container_combined->GetFileData().SetCentralityEdges("ncharged", dummy->GetFileData().GetCentralityEdges("ncharged"));

    data_container_combined->InitializeDataContainer();

    progressbar.Reset();

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Initialize data containers ...");
    std::cout << logstring << std::endl;

    progressbar.Print();
#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (index_t i = 0; i < number_of_files; ++i) {
            data_container[i]->InitializeDataContainer();
            progressbar.Update();
#pragma omp critical
            {
                progressbar.Print();
            }
        }
    }
    std::cout << std::endl;
    progressbar.Reset();

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Parsing particle statistics ...");
    std::cout << logstring << std::endl;

    progressbar.Print();

#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (index_t i = 0; i < number_of_files; ++i) {
            // data[i]->InitializeDataContainer();
            data_container[i]->ParseParticleStatistics();
            progressbar.Update();
#pragma omp critical
            {
                progressbar.Print();
            }
        }
    }
    std::cout << std::endl;
    progressbar.Reset();

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Combining statistics ...");
    std::cout << logstring << std::endl;

    progressbar.Print();

    for (index_t i = 0; i < number_of_files; ++i) {
        *data_container_combined += *data_container[i];
        // #pragma omp critical
        //         {
        progressbar.Update();
        progressbar.Print();
        // }
    }
    std::cout << std::endl;
    progressbar.Reset();

    timer.Stop();

    logstring = fmt::format("{}{}[INFO]{} ", PP::FINISHED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Analysis time : {}{:04d}:{:02d}:{:02d}.{:03d}{}", PP::HIGHLIGHT, (int)timer.chours, (int)timer.cminutes, (int)timer.cseconds, (int)timer.cmilliseconds, PP::RESET);
    std::cout << logstring << std::endl;

    timer.Start();

    std::filesystem::create_directories(output_directory);
    data_container_combined->WriteData(output_directory);

    timer.Stop();
    double filesize_result = 0;
    std::filesystem::recursive_directory_iterator output_directory_iteratator(output_directory);
    for (const auto& entry : output_directory_iteratator) {
        filesize_result += Utilities::GetFileSize(entry.path(), 2);
    }
    logstring = fmt::format("{}{}[INFO]{} ", PP::FINISHED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Writing time : {}{:04d}:{:02d}:{:02d}.{:03d}{}", PP::HIGHLIGHT, (int)timer.chours, (int)timer.cminutes, (int)timer.cseconds, (int)timer.cmilliseconds, PP::RESET);
    std::cout << logstring << std::endl;

    logstring = fmt::format("{}{}[INFO]{} ", PP::FINISHED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Total datasize written : {}{:.3} MB{}", PP::HIGHLIGHT, filesize_result, PP::RESET);
    std::cout << logstring << std::endl;
}

}  // namespace AMPT

namespace iSS {

Statistics::Block_iss GetInitialStateInfo(std::filesystem::path filename) {
    std::ifstream file;

    Statistics::Block_iss block;

    file.open(filename, std::ios::in);
    if (file.is_open()) {
        std::string dummy1, dummy2, dummy3;
        double value;
        while (std::getline(file, dummy1)) {
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
void ProcessFiles(
    std::vector<std::filesystem::path> datafiles,
    std::vector<std::filesystem::path> logfiles,
    unsigned int collisiontype,
    std::filesystem::path output_directory) {
    std::string barstring;
    Utilities::Progressbar progressbar;
    std::string logstring;
    Utilities::Duration timer('H');

    size_t number_of_files = datafiles.size();

    barstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    progressbar = Utilities::Progressbar(number_of_files);
    progressbar.SetFrontString(barstring);
    progressbar.SetDoneChar(std::string("\033[38;2;57;181;74m█") + PP::RESET);
    progressbar.SetTodoChar("░");
    progressbar.SetStartChar("║");  //"▕");
    progressbar.SetEndChar("║");

    double filesize_data = 0;
    for (index_t i = 0; i < number_of_files; ++i) {
        filesize_data += Utilities::GetFileSize(datafiles[i], 3);
        filesize_data += Utilities::GetFileSize(logfiles[i], 3);
    }
    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Number of files to read : {}{}{}", PP::HIGHLIGHT, number_of_files, PP::RESET);
    std::cout << logstring << std::endl;
    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Total datasize to read : {}{:.3} GB{}", PP::HIGHLIGHT, filesize_data, PP::RESET);
    std::cout << logstring << std::endl;

    std::unique_ptr<Model::File_iss> data_container_combined = std::make_unique<Model::File_iss>(collisiontype);
    std::vector<std::unique_ptr<Model::File_iss>> data_container(number_of_files);

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Initializing file objects ...");
    std::cout << logstring << std::endl;

    progressbar.Print();
    timer.Start();

#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (index_t i = 0; i < number_of_files; ++i) {
            Statistics::Block_iss block = iSS::GetInitialStateInfo(logfiles[i]);
            block.SetEventID(i);
            block.SetOriginalEventID(i + 1);
            data_container[i] = std::make_unique<Model::File_iss>(datafiles[i], collisiontype);
            data_container[i]->SetInitialState(block);
            progressbar.Update();

#pragma omp critical
            {
                progressbar.Print();
            }
        }
    }
    std::cout << std::endl;

    progressbar.Reset();

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Parsing event statistics ...");
    std::cout << logstring << std::endl;

    progressbar.Print();

#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (index_t i = 0; i < number_of_files; ++i) {
            data_container[i]->ParseEventStatistics();
            progressbar.Update();
#pragma omp critical
            {
                progressbar.Print();
            }
        }
    }

    std::cout << std::endl;

    std::unique_ptr<Model::File_iss> dummy = std::make_unique<Model::File_iss>(collisiontype);
    for (index_t i = 0; i < number_of_files; ++i) {
        dummy->GetFileData().InsertBlocks(data_container[i]->GetFileData());
    }

    dummy->GetFileData().CalculateCentralityClasses();

    for (index_t i = 0; i < number_of_files; ++i) {
        data_container[i]->GetFileData().SetCentralityEdges("ncharged", dummy->GetFileData().GetCentralityEdges("ncharged"));
    }
    data_container_combined->GetFileData().SetCentralityEdges("ncharged", dummy->GetFileData().GetCentralityEdges("ncharged"));

    data_container_combined->InitializeDataContainer();

    progressbar.Reset();

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Initialize data containers ...");
    std::cout << logstring << std::endl;

    progressbar.Print();

#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (index_t i = 0; i < number_of_files; ++i) {
            data_container[i]->InitializeDataContainer();
            progressbar.Update();
#pragma omp critical
            {
                progressbar.Print();
            }
        }
    }

    std::cout << std::endl;
    progressbar.Reset();

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Parsing particle statistics ...");
    std::cout << logstring << std::endl;

    progressbar.Print();

#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (index_t i = 0; i < number_of_files; ++i) {
            // data[i]->InitializeDataContainer();
            data_container[i]->ParseParticleStatistics();
            progressbar.Update();
#pragma omp critical
            {
                progressbar.Print();
            }
        }
    }
    std::cout << std::endl;
    progressbar.Reset();

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Combining statistics ...");
    std::cout << logstring << std::endl;

    progressbar.Print();

    for (index_t i = 0; i < number_of_files; ++i) {
        *data_container_combined += *data_container[i];
        progressbar.Update();
        progressbar.Print();
    }
    std::cout << std::endl;
    progressbar.Reset();

    timer.Stop();

    logstring = fmt::format("{}{}[INFO]{} ", PP::FINISHED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Analysis time : {}{:04d}:{:02d}:{:02d}.{:03d}{}", PP::HIGHLIGHT, (int)timer.chours, (int)timer.cminutes, (int)timer.cseconds, (int)timer.cmilliseconds, PP::RESET);
    std::cout << logstring << std::endl;

    timer.Start();

    std::filesystem::create_directories(output_directory);
    data_container_combined->WriteData(output_directory);

    timer.Stop();

    double filesize_result = 0;
    std::filesystem::recursive_directory_iterator output_directory_iteratator(output_directory);
    for (const auto& entry : output_directory_iteratator) {
        filesize_result += Utilities::GetFileSize(entry.path(), 2);
    }

    logstring = fmt::format("{}{}[INFO]{} ", PP::FINISHED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Writing time : {}{:04d}:{:02d}:{:02d}.{:03d}{}", PP::HIGHLIGHT, (int)timer.chours, (int)timer.cminutes, (int)timer.cseconds, (int)timer.cmilliseconds, PP::RESET);
    std::cout << logstring << std::endl;

    logstring = fmt::format("{}{}[INFO]{} ", PP::FINISHED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Total datasize written : {}{:.3} MB{}", PP::HIGHLIGHT, filesize_result, PP::RESET);
    std::cout << logstring << std::endl;
}
}  // namespace iSS
