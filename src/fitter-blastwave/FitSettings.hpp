#ifndef FITSETTINGS_HPP
#define FITSETTINGS_HPP

#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
using Datamap = std::map<int, std::vector<double>>;

struct MultifitterData {
    Datamap xvals;
    Datamap yvals;
    Datamap xerrs;
    Datamap yerrs;
};

struct MultifitterSettings {
    std::vector<std::string> ParameterNames;
    std::vector<double> ParameterInitValues;
    std::vector<std::vector<double>> ParameterLimits;
    std::vector<bool> ParameterLimited;
    std::vector<bool> ParameterFixed;
    std::vector<double> ParameterStepsize;
    std::vector<bool> ParameterStepsized;
    std::vector<int> Species;
    std::map<int, std::vector<double>> FitRange;
    std::map<int, std::vector<unsigned int>> Indexmap;
    MultifitterSettings() = default;
};

struct MultifitterResults {
    MultifitterSettings settings;
    std::vector<std::vector<double>> CorrelationMatrix;
    std::vector<double> ParameterValues;
    std::vector<double> ParameterErrors;
    size_t DegreesOfFreedom;
    double Chi2;
    double MinFCN;
    double Edm;
    size_t NCalls;
    nlohmann::json j;

    MultifitterResults() = default;
    MultifitterResults(MultifitterSettings& settings_) : settings(settings_) {}

    void GenerateJSON() {
        j["ParameterNames"] = settings.ParameterNames;
        j["CorrelationMatrix"] = CorrelationMatrix;
        j["ParameterValues"] = ParameterValues;
        j["ParameterErrors"] = ParameterErrors;
        j["ParameterLimits"] = settings.ParameterLimits;
        j["ParameterLimited"] = settings.ParameterLimited;
        j["ParameterFixed"] = settings.ParameterFixed;
        j["ParameterStepsize"] = settings.ParameterStepsize;
        j["ParameterStepsized"] = settings.ParameterStepsized;
        j["DegreesOfFreedom"] = DegreesOfFreedom;
        j["Chi2"] = Chi2;
        j["MinFCN"] = MinFCN;
        j["Edm"] = Edm;
        j["NCalls"] = NCalls;
        j["Species"] = settings.Species;

        for (const auto& [key, value] : settings.FitRange) {
            j["FitRange"][std::to_string(key)] = value;
        }

        for (const auto& [key, value] : settings.Indexmap) {
            j["Indexmap"][std::to_string(key)] = value;
        }
    }

    void WritetoJSON(std::ofstream& outFile) {
        outFile << j.dump(4);
    }
};

namespace FitSets {
MultifitterSettings BGBW_1 = {
    {"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N"},
    {1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0},
    {{1, 10000000}, {1, 10000000}, {1, 10000000}, {0.01, 0.3}, {0, 0}, {0, 0}, {0, 0}, {0.01, 1}, {0.01, 3}},
    {true, true, true, true, false, false, false, true, true},
    {false, false, false, false, true, true, true, false, false},
    {1, 1, 1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
    {true, true, true, true, false, false, false, true, true},
    {211, 321, 2212},
    {{211, {0.5, 1}},
     {321, {0.2, 1.5}},
     {2212, {0.3, 3.0}}},
    {{211, {0, 3, 4, 7, 8}},
     {321, {1, 3, 5, 7, 8}},
     {2212, {2, 3, 6, 7, 8}}}};

MultifitterSettings TBW_1 = {
    {"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N", "q", "yb"},
    {1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0, 1.1, 0.5},
    {{1, 10000000}, {1, 10000000}, {1, 10000000}, {0.01, 0.3}, {0, 0}, {0, 0}, {0, 0}, {0.01, 1}, {0.01, 3}, {1.0001, 2}, {0, 0}},
    {true, true, true, true, false, false, false, true, true, true, false},
    {false, false, false, false, true, true, true, false, false, false, true},
    {1, 1, 1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0001, 0.01},
    {true, true, true, true, false, false, false, true, true, true, false},
    {211, 321, 2212},
    {{211, {0.5, 1}},
     {321, {0.2, 1.5}},
     {2212, {0.3, 3.0}}},
    {{211, {0, 3, 4, 7, 8, 9, 10}},
     {321, {1, 3, 5, 7, 8, 9, 10}},
     {2212, {2, 3, 6, 7, 8, 9, 10}}}};
}  // namespace FitSets

#endif