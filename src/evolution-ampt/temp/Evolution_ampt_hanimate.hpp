#ifndef EVOLUTION_AMPT_HANIMATE_HPP
#define EVOLUTION_AMPT_HANIMATE_HPP

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "Evolution_ampt_format.hpp"

class File_hanimate {
   private:
    std::vector<std::unique_ptr<EventBlock>> EventBlocks;
    std::string Filename;

   public:
    void Parse() {
        std::ifstream File;
        File.open(Filename, std::ios::in);
        if (File.is_open()) {
            int NumberOfTimeSteps;
            double SizeOfTimeStep;
            File >> NumberOfTimeSteps >> SizeOfTimeStep;
            std::string line;
            double dummy1;
            while (getline(File, line)) {
                std::stringstream sline(line);
                if (!(line.find("-10") == std::string::npos)) {
                    std::cout << "Found a line" << std::endl;
                }
            }

        } else {
            std::cout << "Failed to open file" << std::endl;
        }
    }
};

#endif