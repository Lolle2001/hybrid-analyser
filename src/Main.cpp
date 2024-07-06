// Copyright (C) 2024 Lieuwe Huisman

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>

#include <argparse/argparse.hpp>
#include <iomanip>
#include <iostream>
#include <string>

#include "File.hpp"
#include "FileProcessor.hpp"
#include "Utilities.hpp"

namespace AMPT {
#define NAME "analyser"
#define AUTHOR "Liewe Huisman"
#define PROGRAM_VERSION "1.0.0"
#define DEBUG 0

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
    progressbar.SetDoneChar("█");
    progressbar.SetTodoChar("░");
    progressbar.SetStartChar("║");  //"▕");
    progressbar.SetEndChar("║");

    double filesize_data = 0;
    for (index_t i = 0; i < number_of_files; ++i) {
        filesize_data += Utilities::GetFileSize(datafiles[i], 3);
        filesize_data += Utilities::GetFileSize(logfiles[i], 3);
    }
    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Total datasize to read : {0:.3} GB", filesize_data);
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
    logstring += fmt::format("Analysis time : {:04d}:{:02d}:{:02d}.{:03d}", (int)timer.chours, (int)timer.cminutes, (int)timer.cseconds, (int)timer.cmilliseconds);
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
    logstring += fmt::format("Writing time : {:04}:{:02}:{:02}.{:03} ...", (int)timer.chours, (int)timer.cminutes, (int)timer.cseconds, (int)timer.cmilliseconds);
    std::cout << logstring << std::endl;

    logstring = fmt::format("{}{}[INFO]{} ", PP::FINISHED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Total datasize written : {0:.3} MB", filesize_result);
    std::cout << logstring << std::endl;
}

}  // namespace AMPT

namespace iSS {
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
    progressbar.SetDoneChar("█");
    progressbar.SetTodoChar("░");
    progressbar.SetStartChar("║");  //"▕");
    progressbar.SetEndChar("║");

    double filesize_data = 0;
    for (index_t i = 0; i < number_of_files; ++i) {
        filesize_data += Utilities::GetFileSize(datafiles[i], 3);
        filesize_data += Utilities::GetFileSize(logfiles[i], 3);
    }

    logstring = fmt::format("{}{}[INFO]{} ", PP::STARTED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Total datasize to read : {0:.3} GB", filesize_data);
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
    logstring += fmt::format("Analysis time : {:04d}:{:02d}:{:02d}.{:03d}", (int)timer.chours, (int)timer.cminutes, (int)timer.cseconds, (int)timer.cmilliseconds);
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
    logstring += fmt::format("Writing time : {:04d}:{:02d}:{:02d}.{:03d}", (int)timer.chours, (int)timer.cminutes, (int)timer.cseconds, (int)timer.cmilliseconds);
    std::cout << logstring << std::endl;

    logstring = fmt::format("{}{}[INFO]{} ", PP::FINISHED, PP::BOLD, PP::RESET);
    logstring += fmt::format("Total datasize written : {0:.3} MB", filesize_result);
    std::cout << logstring << std::endl;
}
}  // namespace iSS

void Process(int argc, char* argv[]) {
    argparse::ArgumentParser program(NAME, PROGRAM_VERSION);
    program.add_description("analyser is a program that parses and analyses the final state data from iSS and AMPT.");

    program.add_argument("-col", "--collisiontype")
        .help("specifies type of centrality binning")
        .default_value(0);

    argparse::ArgumentParser parser_ampt("ampt");

    parser_ampt.add_argument("-i", "--input")
        .nargs(argparse::nargs_pattern::any)
        .help("name of final state output file from AMPT");
    parser_ampt.add_argument("-id", "--input-directory")
        .help("directory to final state output from AMPT");
    parser_ampt.add_argument("-o", "--output")
        .help("name of output directory for the analysed data")
        .nargs(argparse::nargs_pattern::any);
    parser_ampt.add_argument("-od", "--output-directory")
        .help("directory to the output");

    // parser_ampt.add_argument("-ccm", "--centrality-classification-mode")
    // .choices("user","b","npart","ncoll", "Nch");
    parser_ampt.add_argument("-pf", "--parameter-file");
    parser_ampt.add_argument("-pd", "--parameter-directory");

    // parser_ampt.add_argument("-br", "--batch-range")
    // .help("range of event ids that must be parsed");
    // parser_ampt.add_argument("-l", "--log") // ampt.log
    // .help("name of log file from AMPT");
    // parser_ampt.add_argument("-ld", "--log-directory")
    // .help("directory to log file from AMPT");

    argparse::ArgumentParser parser_iss("iss");

    parser_iss.add_argument("-i", "--input")
        .nargs(argparse::nargs_pattern::any);
    parser_iss.add_argument("-id", "--input-directory")
        .default_value("/home/lieuwe/Documents/Software/iSS/data");
    parser_iss.add_argument("-o", "--output");
    parser_iss.add_argument("-od", "--output-directory")
        .default_value("/home/lieuwe/Documents/Software/iSS/data");
    parser_iss.add_argument("-br", "--batch-range");
    parser_iss.add_argument("-l", "--log")
        .nargs(argparse::nargs_pattern::any);  // ipglasma file: usedParameters*.dat
    parser_iss.add_argument("-ld", "--log-directory")
        .default_value("/home/lieuwe/Documents/Software/IPGlasma/data");

    program.add_subparser(parser_ampt);
    program.add_subparser(parser_iss);

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    int collisiontype = program.get<int>("-col");
    std::string centralitybinningname;
    if (collisiontype == 0) {
        centralitybinningname = "Pb-Pb at 5.02 TeV (0-5-10-20-..90-100)";
    }
    if (collisiontype == 1) {
        centralitybinningname = "p-Pb at 5.02 TeV (0-5-10-20-..90-100)";
    }
    if (collisiontype == 2) {
        centralitybinningname = "p-p at 5.02 TeV (0-100)";
    }
    if (collisiontype == 4) {
        centralitybinningname = "Pb-Pb at 5.02 TeV (0-5-10-20-..90-100) (Traiectum)";
    }
    int width = 80;
    std::string logstring;
    logstring += fmt::format("╭{}╮\n", Utilities::repeat(width + 2, "─"));
    logstring += fmt::format("│ {:{}} │\n", "Hybrid Analyser for AMPT and iSS", width);
    logstring += fmt::format("│ {:{}} │\n", "Version 1.0.0", width);
    logstring += fmt::format("│ {:{}} │\n", "Made by Lieuwe Huisman", width);
    logstring += fmt::format("│ {:{}} │\n", "Made for AMPT version: v1.26t9b-v2.26t9b", width);
    logstring += fmt::format("│ {:{}} │\n", "Made for iSS version: v2.0.0.0", width);
    logstring += fmt::format("├{}┤\n", Utilities::repeat(width + 2, "─"));
    logstring += fmt::format("│ {:18} : {:<{}} │\n", "Number of threads", omp_get_max_threads(), width - 18 - 3);
    logstring += fmt::format("│ {:18} : {:{}} │\n", "Centrality binning", centralitybinningname, width - 18 - 3);

    if (program.is_subcommand_used("ampt")) {
        // bool batch_mode = parser_ampt.is_used("-br");

        std::vector<std::string> data_paths = parser_ampt.get<std::vector<std::string>>("-i");
        std::filesystem::path data_directory = std::filesystem::path(parser_ampt.get<std::string>("-id"));
        std::filesystem::path output_path = std::filesystem::path(parser_ampt.get<std::string>("-o"));
        std::filesystem::path output_directory = std::filesystem::path(parser_ampt.get<std::string>("-od"));

        size_t number_of_inputs = data_paths.size();
        std::vector<std::filesystem::path> data_files;
        std::vector<std::filesystem::path> log_files;
        for (int i = 0; i < number_of_inputs; ++i) {
            size_t number_of_subfolders = Utilities::get_number_of_subfolders(std::filesystem::absolute(data_directory / data_paths[i]), data_paths[i], "-");
            for (int j = 0; j < number_of_subfolders; ++j) {
                std::string subpath;
                subpath = data_paths[i] + "-" + std::to_string(j + 1) + "/ana/ampt.dat";
                data_files.push_back(std::filesystem::absolute(data_directory / data_paths[i] / subpath));
                // std::cout << std::filesystem::absolute(data_directory / data_paths[i] / subpath) << std::endl;
                subpath = data_paths[i] + "-" + std::to_string(j + 1) + "/ampt.log";
                log_files.push_back(std::filesystem::absolute(data_directory / data_paths[i] / subpath));
                // std::cout << std::filesystem::absolute(data_directory / data_paths[i] / subpath) << std::endl;
            }
        }
        std::string inputs;

        for (int i = 0; i < number_of_inputs; ++i) {
            if (i < number_of_inputs - 1) {
                inputs += data_paths[i] + " ";

            } else {
                inputs += data_paths[i];
            }
        }
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Input", inputs, width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Inputdirectory", data_directory.string(), width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Output", output_path.string(), width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Outputdirectory", output_directory.string(), width - 18 - 3);
        logstring += fmt::format("╰{}╯\n", Utilities::repeat(width + 2, "─"));
        std::cout << logstring;
        AMPT::ProcessFiles(data_files, log_files, collisiontype, output_directory / output_path);

    } else if (program.is_subcommand_used("iss")) {
        // bool batch_mode = parser_iss.is_used("-br");
        std::vector<std::string> data_paths = parser_iss.get<std::vector<std::string>>("-i");
        std::filesystem::path data_directory = std::filesystem::path(parser_iss.get<std::string>("-id"));
        std::filesystem::path output_path = std::filesystem::path(parser_iss.get<std::string>("-o"));
        std::filesystem::path output_directory = std::filesystem::path(parser_iss.get<std::string>("-od"));

        std::vector<std::string> log_paths = parser_iss.get<std::vector<std::string>>("-l");
        std::filesystem::path log_directory = std::filesystem::path(parser_iss.get<std::string>("-ld"));

        size_t number_of_inputs = data_paths.size();
        std::vector<std::filesystem::path> data_files;
        std::vector<std::filesystem::path> log_files;
        for (int i = 0; i < number_of_inputs; ++i) {
            size_t number_of_subfolders = Utilities::get_number_of_subfolders(std::filesystem::absolute(data_directory / data_paths[i]), data_paths[i], "-");
            for (int j = 0; j < number_of_subfolders; ++j) {
                std::string subpath;
                subpath = data_paths[i] + "-" + std::to_string(j + 1) + "/particle_samples.bin";
                data_files.push_back(std::filesystem::absolute(data_directory / data_paths[i] / subpath));
                subpath = "usedParameters" + std::to_string(j) + ".dat";
                log_files.push_back(log_directory / log_paths[i] / subpath);
                // std::cout << data_files[j] << std::endl;
                // std::cout << log_files[j] << std::endl;
            }
        }
        std::string inputs;
        std::string logs;
        for (int i = 0; i < number_of_inputs; ++i) {
            if (i < number_of_inputs - 1) {
                inputs += data_paths[i] + " ";
                logs += log_paths[i] + " ";
            } else {
                inputs += data_paths[i];
                logs += log_paths[i] + " ";
            }
        }
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Input", inputs, width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Inputdirectory", data_directory.string(), width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Output", output_path.string(), width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Outputdirectory", output_directory.string(), width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Log", logs, width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Logdirectory", log_directory.string(), width - 18 - 3);
        logstring += fmt::format("╰{}╯\n", Utilities::repeat(width + 2, "─"));
        std::cout << logstring;
        iSS::ProcessFiles(data_files, log_files, collisiontype, output_directory / output_path);

    } else {
        std::cout << "Please use a valid command!" << std::endl;
    }
}  // namespace void Process(intargc,char*))

int main(int argc, char** argv) {
    Process(argc, argv);
}