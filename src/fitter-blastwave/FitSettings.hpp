// Copyright (C) 2024 Lieuwe Huisman
#ifndef FITSETTINGS_HPP
#define FITSETTINGS_HPP

#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
using Datamap = std::map<int, std::vector<double>>;

namespace CFitter {

struct MultiFitterData {
    Datamap xvals;
    Datamap yvals;
    Datamap xerrs;
    Datamap yerrs;
    MultiFitterData() = default;
    MultiFitterData(Datamap xvals_, Datamap yvals_, Datamap xerrs_, Datamap yerrs_)
        : xvals(xvals_), yvals(yvals_), xerrs(xerrs_), yerrs(yerrs_){};
};

struct MultiFitterSettings {
    std::vector<std::string> ParameterNames;
    std::vector<std::string> StyledNames;
    std::vector<double> ParameterInitValues;
    std::vector<std::vector<double>> ParameterLimits;
    std::vector<bool> ParameterLimited;
    std::vector<bool> ParameterFixed;
    std::vector<double> ParameterStepsize;
    std::vector<bool> ParameterStepsized;
    std::vector<int> Species;
    std::map<int, std::vector<double>> FitRange;
    std::map<int, std::vector<unsigned int>> Indexmap;
    MultiFitterSettings() = default;
};

std::ostream& operator<<(std::ostream& out, const MultiFitterSettings& obj) {
    for (unsigned int i = 0; i < obj.ParameterNames.size(); ++i) {
        out << obj.ParameterNames[i] << " " << obj.ParameterInitValues[i] << " " << std::endl;
    }
    return out;
}

struct MultiFitterResults {
    MultiFitterSettings settings;
    std::vector<std::vector<double>> CorrelationMatrix;
    std::vector<std::vector<double>> CovarianceMatrix;
    std::vector<double> ParameterValues;
    std::vector<double> ParameterErrors;
    size_t DegreesOfFreedom;
    double Chi2;
    double MinFCN;
    double Edm;
    size_t NCalls;
    size_t Status;
    nlohmann::json j;

    MultiFitterResults() = default;
    MultiFitterResults(MultiFitterSettings& settings_) : settings(settings_) {}

    void GenerateJSON() {
        j["ParameterNames"] = settings.ParameterNames;
        j["StyledNames"] = settings.StyledNames;
        j["CorrelationMatrix"] = CorrelationMatrix;
        j["CovarianceMatrix"] = CovarianceMatrix;
        j["ParameterValues"] = ParameterValues;
        j["ParameterInitValues"] = settings.ParameterInitValues;
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
        j["Status"] = Status;

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
MultiFitterSettings BGBW_1 = {
    {"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N"},
    {"A_{\\pi^{\\pm}}", "A_{K^{\\pm}}", "A_{p^{\\pm}}", "T_{\\text{kin}}", "m_{\\pi^{\\pm}}", "m_{K^{\\pm}}", "m_{p^{\\pm}}", "\\beta_{s}", "n"},
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

MultiFitterSettings BGBW_2 = {
    {"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "rho0", "rho2", "RxRy"},
    {"A_{\\pi^{\\pm}}", "A_{K^{\\pm}}", "A_{p^{\\pm}}", "T_{\\text{kin}}", "m_{\\pi^{\\pm}}", "m_{K^{\\pm}}", "m_{p^{\\pm}}", "\\rho_{0}", "\\rho_{2}", "R_{x}/R_{y}"},
    {1, 1, 1, 0.11, 0.138, 0.498, 0.938, 1.13, 0.1, 0.8},
    {{1, 10000000}, {1, 10000000}, {1, 10000000}, {0.01, 0.3}, {0, 0}, {0, 0}, {0, 0}, {0.01, 2}, {0.01, 2}, {0.01, 2}},
    {true, true, true, true, false, false, false, true, true, true},
    {false, false, false, false, true, true, true, false, false, false},
    {1, 1, 1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.001, 0.001},
    {true, true, true, true, false, false, false, true, true, true},
    {211, 321, 2212},
    {{211, {0.5, 1}},
     {321, {0.2, 1.5}},
     {2212, {0.3, 3.0}}},
    {{211, {0, 3, 4, 7, 8, 9}},
     {321, {1, 3, 5, 7, 8, 9}},
     {2212, {2, 3, 6, 7, 8, 9}}}};

MultiFitterSettings TBW_1 = {
    {"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N", "q", "yb"},
    {"A_{\\pi^{\\pm}}", "A_{K^{\\pm}}", "A_{p^{\\pm}}", "T_{\\text{kin}}", "m_{\\pi^{\\pm}}", "m_{K^{\\pm}}", "m_{p^{\\pm}}", "\\beta_{s}", "n", "q", "y_{b}"},
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

MultiFitterSettings TBW_3 = {
    {"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N", "qaa", "qpp", "Tts", "tf/tau"},
    {"A_{\\pi^{\\pm}}", "A_{K^{\\pm}}", "A_{p^{\\pm}}", "T_{\\text{kin}}", "m_{\\pi^{\\pm}}", "m_{K^{\\pm}}", "m_{p^{\\pm}}", "\\beta_{s}", "n", "q_{\\text{AA}}", "q_{\\text{pp}}", "T_{\\text{ts}}", "t_{f}/\\tau"},
    {100, 10, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 0.8, 1.005, 1.005, 0.1, 1.5},
    {{1, 10000000}, {1, 10000000}, {1, 10000000}, {0.01, 0.3}, {0, 0}, {0, 0}, {0, 0}, {0.01, 1}, {0.01, 3}, {1.001, 2}, {1.001, 2}, {0.01, 0.3}, {0.01, 5}},
    {true, true, true, false, false, false, false, true, true, true, true, true, true},
    {false, false, false, true, true, true, true, false, false, false, false, false, false},
    {1, 1, 1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0001, 0.0001, 0.01, 0.001},
    {true, true, true, false, false, false, false, true, true, true, true, true, true},
    {211, 321, 2212},
    {{211, {0.1, 8}},
     {321, {0.2, 8}},
     {2212, {0.3, 8}}},
    {{211, {0, 3, 4, 7, 8, 9, 10, 11, 12}},
     {321, {1, 3, 5, 7, 8, 9, 10, 11, 12}},
     {2212, {2, 3, 6, 7, 8, 9, 10, 11, 12}}}};
}  // namespace FitSets
}  // namespace CFitter
#endif