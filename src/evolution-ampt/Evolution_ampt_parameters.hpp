// Copyright (C) 2024 Lieuwe Huisman
#ifndef EVOLUTION_AMPT_PARAMETERS_HPP
#define EVOLUTION_AMPT_PARAMETERS_HPP

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace AMPT {
namespace Evolution {

struct Parameters {
    nlohmann::json params;

    Parameters(std::string filename) {
        ReadfromJSON(filename);
    }

    void ReadfromJSON(std::string filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open JSON file." << std::endl;
            return;
        }
        try {
            file >> params;
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
            return;
        }
    }

    void Print(std::ostream &output) {
        output << "Parameters" << std::endl;
        output << params.dump(2) << std::endl;
    }
};

}  // namespace Evolution
}  // namespace AMPT

#endif
