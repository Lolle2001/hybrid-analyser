// Copyright (C) 2024 Lieuwe Huisman

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <omp.h>

#include <argparse/argparse.hpp>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "File.hpp"
#include "FileProcessor.hpp"
#include "Messenger.hpp"
#include "Utilities.hpp"

#define NAME "analyser"
#define AUTHOR "Liewe Huisman"
#define PROGRAM_VERSION "1.0.0"
#define DEBUGFLAG 0

//

void Process(int argc, char* argv[]) {
    argparse::ArgumentParser program(NAME, PROGRAM_VERSION);
    program.add_description("analyser is a program that parses and analyses the final state data from iSS and AMPT.");

    program.add_argument("-col", "--collisiontype")
        .help("specifies type of centrality binning")
        .default_value(0)
        .scan<'i', int>();

    program.add_argument("-p", "--parameter-flag")
        .default_value(false)
        .implicit_value(true);
    // .default_value(false);
    program.add_argument("-pf", "--parameter-file")
        .default_value("analyser.par");
    program.add_argument("-pd", "--parameter-directory")
        .default_value("./");

    argparse::ArgumentParser parser_ampt("ampt");

    parser_ampt.add_argument("-i", "--input")
        .nargs(argparse::nargs_pattern::any)
        .help("name of final state output file from AMPT");
    parser_ampt.add_argument("-id", "--input-directory")
        .default_value("../AMPT/data")
        .help("directory to final state output from AMPT");
    parser_ampt.add_argument("-o", "--output")
        .help("name of output directory for the analysed data")
        .nargs(argparse::nargs_pattern::any);
    parser_ampt.add_argument("-od", "--output-directory")
        .default_value("../AMPT/data")
        .help("directory to the output");

    // parser_ampt.add_argument("-ccm", "--centrality-classification-mode")
    // .choices("user","b","npart","ncoll", "Nch");

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
        .default_value("../iSS/data");
    parser_iss.add_argument("-o", "--output");
    parser_iss.add_argument("-od", "--output-directory")
        .default_value("../iSS/data");
    parser_iss.add_argument("-br", "--batch-range");
    parser_iss.add_argument("-l", "--log")
        .nargs(argparse::nargs_pattern::any);  // ipglasma file: usedParameters*.dat
    parser_iss.add_argument("-ld", "--log-directory")
        .default_value("../IPGlasma/data");

    program.add_subparser(parser_ampt);
    program.add_subparser(parser_iss);

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    std::filesystem::path parameter_path = std::filesystem::path(program.get<std::string>("-pf"));
    std::filesystem::path parameter_directory = std::filesystem::path(program.get<std::string>("-pd"));

    nlohmann::json parameter_dictionary = Utilities::read_json_safe(parameter_directory / parameter_path);

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
    logstring += fmt::format("│ {:{}} │\n", "Copyright (C) 2024 Lieuwe Huisman", width);
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

        if (program.is_used("-pf") == true || program["-p"] == true) {
            Utilities::json_to_parameter(parameter_dictionary["ampt"]["directories"], "data", data_directory);
            Utilities::json_to_parameter(parameter_dictionary["ampt"]["directories"], "data", output_directory);
            std::string suboutput;
            Utilities::json_to_parameter(parameter_dictionary["ampt"], "default_output_extension", suboutput);
            output_path /= suboutput;
        }

        std::vector<std::filesystem::path> data_files_for_test;

        for (int i = 0; i < data_paths.size(); ++i) {
            data_files_for_test.push_back(std::filesystem::absolute(data_directory / data_paths[i]));
        }

        bool data_error_state = Utilities::files_exist(data_files_for_test);
        // bool log_error_state = Utilities::files_exist(log_files_for_test);
        if (!data_error_state) {
            cst::man::error("One or more of the input files do not exist!\n");
            std::exit(1);
        }

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

        logstring += fmt::format("│ {:18} : {:{}} │\n", "Input", data_paths[0], width - 18 - 3);
        for (int i = 1; i < number_of_inputs; ++i) {
            logstring += fmt::format("│ {:18} : {:{}} │\n", " ", data_paths[i], width - 18 - 3);
        }
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

        if (program.is_used("-pf") || program.is_used("-p")) {
            Utilities::json_to_parameter(parameter_dictionary["iss"]["directories"], "data", data_directory);
            Utilities::json_to_parameter(parameter_dictionary["iss"]["directories"], "data", output_directory);
            Utilities::json_to_parameter(parameter_dictionary["ipglasma"]["directories"], "data", log_directory);
            std::string suboutput;
            Utilities::json_to_parameter(parameter_dictionary["iss"], "default_output_extension", suboutput);
            output_path /= suboutput;
        }

        std::vector<std::filesystem::path> data_files_for_test;
        std::vector<std::filesystem::path> log_files_for_test;
        for (int i = 0; i < data_paths.size(); ++i) {
            data_files_for_test.push_back(std::filesystem::absolute(data_directory / data_paths[i]));
            log_files_for_test.push_back(std::filesystem::absolute(log_directory / log_paths[i]));
        }

        bool data_error_state = Utilities::files_exist(data_files_for_test);
        bool log_error_state = Utilities::files_exist(log_files_for_test);
        if (!data_error_state || !log_error_state) {
            // std::string mes;
            // mes += fmt::format("{}[ERROR]{} ", Utilities::PretyPrint::ERROR, Utilities::PretyPrint::RESET);
            // mes += fmt::format("One or more of the input files do not exist.\n");
            std::cout << cst::man::error << "One or more of the input files do not exist!" << std::endl;
            std::exit(1);
        }

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

        logstring += fmt::format("│ {:18} : {:{}} │\n", "Input", data_paths[0], width - 18 - 3);
        for (int i = 1; i < number_of_inputs; ++i) {
            logstring += fmt::format("│ {:18} : {:{}} │\n", " ", data_paths[i], width - 18 - 3);
        }

        logstring += fmt::format("│ {:18} : {:{}} │\n", "Inputdirectory", data_directory.string(), width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Output", output_path.string(), width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Outputdirectory", output_directory.string(), width - 18 - 3);
        logstring += fmt::format("│ {:18} : {:{}} │\n", "Log", log_paths[0], width - 18 - 3);
        for (int i = 1; i < number_of_inputs; ++i) {
            logstring += fmt::format("│ {:18} : {:{}} │\n", " ", log_paths[i], width - 18 - 3);
        }
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
