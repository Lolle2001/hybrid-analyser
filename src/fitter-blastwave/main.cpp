
#include <fstream>
#include <nlohmann/json.hpp>

#include "CillindricalBoltzmannGibbs.hpp"
#include "CillindricalTsallis.hpp"
#include "Multifitter.hpp"
#include "fitter_utilities.hpp"

using RGB = Utilities::RGB;

/*
Function to fit data from arXiv:1910.07678
*/

// ROOT::Fit::FitResult fit_bgbwd(Datamap& xdata,
//                                Datamap& ydata,
//                                );

void read_data(Datamap& xdata,
               std::vector<Datamap>& ydata,
               Datamap& xerrs,
               std::vector<Datamap>& yerrs) {
    Datamap2D tydata;
    Datamap2D tyerrs;
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chpions.json");
        nlohmann::json data = nlohmann::json::parse(file);

        tydata[211] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        tyerrs[211] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[211] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[211] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chkaons.json");
        nlohmann::json data = nlohmann::json::parse(file);

        tydata[321] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        tyerrs[321] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[321] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[321] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    {
        std::ifstream file("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy_chprotons.json");
        nlohmann::json data = nlohmann::json::parse(file);

        tydata[2212] = data["contents"]["vals"].get<std::vector<std::vector<double>>>();
        tyerrs[2212] = data["contents"]["errs"].get<std::vector<std::vector<double>>>();
        xdata[2212] = data["settings"]["mids"]["y"].get<std::vector<double>>();
        xerrs[2212] = data["settings"]["errs"]["y"].get<std::vector<double>>();
        file.close();
    }
    ydata.resize(tydata[211].size());

    for (auto& entry : tydata) {
        int size = entry.second.size();
        for (int i = 0; i < size; ++i) {
            ydata[i][entry.first] = entry.second[i];
        }
    }
    yerrs.resize(tyerrs[211].size());
    for (auto& entry : tyerrs) {
        int size = entry.second.size();
        for (int i = 0; i < size; ++i) {
            yerrs[i][entry.first] = entry.second[i];
        }
    }
}

struct FitResults {
    std::vector<std::string> ParameterNames;
    std::vector<std::vector<double>> CorrelationMatrix;
    std::vector<double> ParameterValues;
    std::vector<double> ParameterErrors;
    std::vector<std::vector<double>> ParameterLimits;
    std::vector<bool> ParameterLimited;
    std::vector<bool> ParameterFixed;
    std::vector<double> ParameterStepsize;
    std::vector<bool> ParameterStepsized;
    size_t DegreesOfFreedom;
    double Chi2;
    double MinFCN;
    double Edm;
    size_t NCalls;
    std::vector<int> Species;
    std::map<int, std::vector<double>> FitRange;
    std::map<int, std::vector<unsigned int>> Indexmap;
    nlohmann::json j;

    void GenerateJSON() {
        j["ParameterNames"] = ParameterNames;
        j["CorrelationMatrix"] = CorrelationMatrix;
        j["ParameterValues"] = ParameterValues;
        j["ParameterErrors"] = ParameterErrors;
        j["ParameterLimits"] = ParameterLimits;
        j["ParameterLimited"] = ParameterLimited;
        j["ParameterFixed"] = ParameterFixed;
        j["ParameterStepsize"] = ParameterStepsize;
        j["ParameterStepsized"] = ParameterStepsized;
        j["DegreesOfFreedom"] = DegreesOfFreedom;
        j["Chi2"] = Chi2;
        j["MinFCN"] = MinFCN;
        j["Edm"] = Edm;
        j["NCalls"] = NCalls;
        j["Species"] = Species;

        for (const auto& [key, value] : FitRange) {
            j["FitRange"][std::to_string(key)] = value;
        }

        for (const auto& [key, value] : Indexmap) {
            j["Indexmap"][std::to_string(key)] = value;
        }
    }

    void WritetoJSON(std::ofstream& outFile) {
        outFile << j.dump(4);
    }
};

void fit_bgbw_all(int argc, char** argv) {
    Datamap xdata;
    std::vector<Datamap> ydata;
    Datamap xerrs;
    std::vector<Datamap> yerrs;
    read_data(xdata, ydata, xerrs, yerrs);

    std::vector<int> pids = {211, 321, 2212};
    Indexmap parindexes =
        {{211, {0, 3, 4, 7, 8}},
         {321, {1, 3, 5, 7, 8}},
         {2212, {2, 3, 6, 7, 8}}};

    std::map<int, double> masses =
        {{211, 0.140},
         {321, 0.498},
         {2212, 0.938}};
    Datamap fitrange =
        {{211, {0.5, 1}},
         {321, {0.2, 1.5}},
         {2212, {0.3, 3.0}}};

    size_t nc = std::stoi(argv[1]);
    std::vector<std::vector<double>> finalparams(nc);
    std::vector<ROOT::Fit::FitResult> finalresults(nc);

    FitResults defaultfitsettings;
    defaultfitsettings.ParameterLimits = {{1, 10000000}, {1, 10000000}, {1, 10000000}, {0.01, 0.3}, {0, 0}, {0, 0}, {0, 0}, {0.01, 1}, {0.01, 3}};
    defaultfitsettings.ParameterLimited = {true, true, true, true, false, false, false, true, true};
    defaultfitsettings.ParameterFixed = {false, false, false, false, true, true, true, false, false};
    defaultfitsettings.ParameterNames = {"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N"};
    defaultfitsettings.ParameterStepsize = {1, 1, 1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
    defaultfitsettings.ParameterStepsized = {true, true, true, true, false, false, false, true, true};
    defaultfitsettings.Species = pids;
    defaultfitsettings.FitRange = fitrange;
    defaultfitsettings.Indexmap = parindexes;
    size_t npar = defaultfitsettings.ParameterFixed.size();
    size_t npar_free = 0;
    for (int i = 0; i < npar; ++i) {
        if (!defaultfitsettings.ParameterFixed[i]) {
            npar_free++;
        }
    }
    for (int ic = 0; ic < nc; ++ic) {
        std::vector<double> parinit = {1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0};

        Chi2 chi2;
        chi2.SetParindexes(parindexes);
        chi2.SetData(xdata, ydata[ic], xerrs, yerrs[ic]);
        chi2.SetSpecies({211, 321, 2212});
        chi2.SetFitRange(fitrange);
        chi2.SetFitFunction(BoltzmannGibbs::Cillindrical::Function, 5);

        size_t npoint = 0;

        for (int s = 0; s < defaultfitsettings.Species.size(); ++s) {
            int ts = defaultfitsettings.Species[s];
            for (int i = 0; i < xdata[ts].size(); ++i) {
                if (xdata[ts][i] >= fitrange[ts][0] &&
                    xdata[ts][i] <= fitrange[ts][1]) {
                    npoint++;
                }
            }
        }
        size_t ndf = npoint - npar_free;
        Multifitter fitter;
        fitter.FixPars({false, false, false, false, true, true, true, false, false});
        fitter.LimitPars({true, true, true, true, false, false, false, true, true});
        fitter.SetParLimits({{1, 10000000}, {1, 10000000}, {1, 10000000}, {0.01, 0.3}, {0, 0}, {0, 0}, {0, 0}, {0.01, 1}, {0.01, 3}});
        fitter.SetParStepsize({1, 1, 1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01});
        fitter.SetParNames({"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N"});
        fitter.SetParInit({1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0});
        fitter.StepsizePars({true, true, true, true, false, false, false, true, true});
        fitter.PrintPars(true);

        fitter.Run(chi2);
        finalresults[ic] = fitter.GetResult();

        double finalchi2 = chi2(fitter.GetResult().GetParams());

        finalresults[ic].SetChi2AndNdf(finalchi2, npoint);
    }
    std::vector<FitResults> JSONResults(nc);
    nlohmann::json file;

    std::vector<std::string> centralitylabels = {"0-5%", "5-10%", "10-20%", "20-30%", "30-40%", "40-50%", "50-60%", "60-70%", "70-80%", "80-90%", "90-100%"};
    for (int ic = 0; ic < nc; ++ic) {
        JSONResults[ic] = FitResults(defaultfitsettings);
        JSONResults[ic].Chi2 = finalresults[ic].Chi2();

        JSONResults[ic].CorrelationMatrix.resize(npar, std::vector<double>(npar));
        JSONResults[ic].Edm = finalresults[ic].Edm();
        JSONResults[ic].MinFCN = finalresults[ic].MinFcnValue();
        JSONResults[ic].NCalls = finalresults[ic].NCalls();
        JSONResults[ic].DegreesOfFreedom = finalresults[ic].Ndf();
        JSONResults[ic].ParameterValues.resize(npar);
        JSONResults[ic].ParameterErrors.resize(npar);
        JSONResults[ic].ParameterNames.resize(npar);
        for (index_t ipar = 0; ipar < npar; ++ipar) {
            JSONResults[ic].ParameterValues[ipar] = finalresults[ic].GetParams()[ipar];
            JSONResults[ic].ParameterErrors[ipar] = finalresults[ic].GetErrors()[ipar];
            JSONResults[ic].ParameterNames[ipar] = finalresults[ic].GetParameterName(ipar);
        }

        for (index_t ipar = 0; ipar < npar; ++ipar) {
            for (int jpar = 0; jpar < npar; ++jpar) {
                JSONResults[ic].CorrelationMatrix[ipar][jpar] = finalresults[ic].CovMatrix(ipar, jpar);
            }
        }
        JSONResults[ic].GenerateJSON();
        file["centrality"][centralitylabels[ic]] = JSONResults[ic].j;
    }
    std::ofstream outFile("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-bgbw-1.json");
    if (outFile.is_open()) {
        outFile << file.dump(4);
        outFile.close();
    } else {
        throw std::runtime_error("Could not open file for writing");
    }
}

void fit_tbw_all(int argc, char** argv) {
    Datamap xdata;
    std::vector<Datamap> ydata;
    Datamap xerrs;
    std::vector<Datamap> yerrs;
    read_data(xdata, ydata, xerrs, yerrs);

    std::vector<int> pids = {211, 321, 2212};
    Indexmap parindexes =
        {{211, {0, 3, 4, 7, 8, 9, 10}},
         {321, {1, 3, 5, 7, 8, 9, 10}},
         {2212, {2, 3, 6, 7, 8, 9, 10}}};
    std::map<int, double> masses =
        {{211, 0.140},
         {321, 0.498},
         {2212, 0.938}};
    Datamap fitrange =
        {{211, {0.5, 1}},
         {321, {0.2, 1.5}},
         {2212, {0.3, 3.0}}};

    size_t nc = std::stoi(argv[1]);
    std::vector<std::vector<double>> finalparams(nc);

    std::vector<ROOT::Fit::FitResult> finalresults(nc);

    FitResults defaultfitsettings;
    defaultfitsettings.ParameterLimits = {{1, 10000000}, {1, 10000000}, {1, 10000000}, {0.01, 0.3}, {0, 0}, {0, 0}, {0, 0}, {0.01, 1}, {0.01, 3}, {1.0001, 2}, {0, 0}};
    defaultfitsettings.ParameterLimited = {true, true, true, true, false, false, false, true, true, true, false};
    defaultfitsettings.ParameterFixed = {false, false, false, false, true, true, true, false, false, false, true};
    defaultfitsettings.ParameterNames = {"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N", "q", "yb"};
    defaultfitsettings.ParameterStepsize = {1, 1, 1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0001, 0.01};
    defaultfitsettings.ParameterStepsized = {true, true, true, true, false, false, false, true, true, true, false};
    defaultfitsettings.Species = pids;
    defaultfitsettings.FitRange = fitrange;
    defaultfitsettings.Indexmap = parindexes;

    size_t npar = defaultfitsettings.ParameterFixed.size();
    size_t npar_free = 0;
    for (int i = 0; i < npar; ++i) {
        if (!defaultfitsettings.ParameterFixed[i]) {
            npar_free++;
        }
    }

    for (int ic = 0; ic < nc; ++ic) {
        Chi2 chi2;
        chi2.SetParindexes(parindexes);
        chi2.SetData(xdata, ydata[ic], xerrs, yerrs[ic]);
        chi2.SetSpecies({211, 321, 2212});
        chi2.SetFitRange(fitrange);
        chi2.SetFitFunction(Tsallis::Cillindrical::Function, 7);

        size_t npoint = 0;

        for (int s = 0; s < defaultfitsettings.Species.size(); ++s) {
            for (int i = 0; i < xdata[defaultfitsettings.Species[s]].size(); ++i) {
                if (xdata[defaultfitsettings.Species[s]][i] >= fitrange[defaultfitsettings.Species[s]][0] && xdata[defaultfitsettings.Species[s]][i] <= fitrange[defaultfitsettings.Species[s]][1]) {
                    npoint++;
                }
            }
        }
        size_t ndf = npoint - npar_free;

        Multifitter fitter;
        fitter.FixPars({false, false, false, false, true, true, true, false, false, false, true});
        fitter.LimitPars({true, true, true, true, false, false, false, true, true, true, false});
        fitter.SetParLimits({{1, 10000000}, {1, 10000000}, {1, 10000000}, {0.01, 0.3}, {0, 0}, {0, 0}, {0, 0}, {0.01, 1}, {0.01, 3}, {1.0001, 2}, {0, 0}});
        fitter.SetParStepsize({1, 1, 1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0001, 0.01});
        fitter.SetParNames({"A211", "A321", "A2212", "Tkin", "M211", "M321", "M2212", "BetaS", "N", "q", "yb"});
        fitter.SetParInit({1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0, 1.1, 0.5});
        fitter.StepsizePars({true, true, true, true, false, false, false, true, true, true, false});
        fitter.PrintPars(true);

        fitter.Run(chi2);
        finalresults[ic] = fitter.GetResult();

        double finalchi2 = chi2(fitter.GetResult().GetParams());

        finalresults[ic].SetChi2AndNdf(finalchi2, npoint);
    }
    std::vector<FitResults> JSONResults(nc);
    nlohmann::json file;

    std::vector<std::string> centralitylabels = {"0-5%", "5-10%", "10-20%", "20-30%", "30-40%", "40-50%", "50-60%", "60-70%", "70-80%", "80-90%", "90-100%"};

    for (int ic = 0; ic < nc; ++ic) {
        JSONResults[ic] = FitResults(defaultfitsettings);
        JSONResults[ic].Chi2 = finalresults[ic].Chi2();

        JSONResults[ic].CorrelationMatrix.resize(npar, std::vector<double>(npar));
        JSONResults[ic].Edm = finalresults[ic].Edm();
        JSONResults[ic].MinFCN = finalresults[ic].MinFcnValue();
        JSONResults[ic].NCalls = finalresults[ic].NCalls();
        JSONResults[ic].DegreesOfFreedom = finalresults[ic].Ndf();
        JSONResults[ic].ParameterValues.resize(npar);
        JSONResults[ic].ParameterErrors.resize(npar);
        JSONResults[ic].ParameterNames.resize(npar);
        for (index_t ipar = 0; ipar < npar; ++ipar) {
            JSONResults[ic].ParameterValues[ipar] = finalresults[ic].GetParams()[ipar];
            JSONResults[ic].ParameterErrors[ipar] = finalresults[ic].GetErrors()[ipar];
            JSONResults[ic].ParameterNames[ipar] = finalresults[ic].GetParameterName(ipar);
        }

        for (index_t ipar = 0; ipar < npar; ++ipar) {
            for (int jpar = 0; jpar < npar; ++jpar) {
                JSONResults[ic].CorrelationMatrix[ipar][jpar] = finalresults[ic].CovMatrix(ipar, jpar);
            }
        }
        JSONResults[ic].GenerateJSON();
        file["centrality"][centralitylabels[ic]] = JSONResults[ic].j;
    }
    std::ofstream outFile("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-tbw-1.json");
    if (outFile.is_open()) {
        outFile << file.dump(4);
        outFile.close();
    } else {
        throw std::runtime_error("Could not open file for writing");
    }
}

int main(int argc, char** argv) {
    if (argc > 2) {
        std::string command = argv[2];
        if (command.compare("all") == 0 || command.compare("bgbw") == 0) {
            fit_bgbw_all(argc, argv);
        }
        if (command.compare("all") == 0 || command.compare("tbw") == 0) {
            fit_tbw_all(argc, argv);
        }
    }

    // fit_tbw_all(argc, argv);

    return 0;
}