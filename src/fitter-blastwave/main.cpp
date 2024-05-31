#include <Fit/Chi2FCN.h>
#include <Fit/Fitter.h>
#include <Math/AdaptiveIntegratorMultiDim.h>
#include <Math/Functor.h>
#include <Math/WrappedParamFunction.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TROOT.h>

#include <ROOT/TThreadExecutor.hxx>
#include <mutex>
#include <thread>

#include "CillindricalTsallis.hpp"
#include "Multifitter.hpp"
// #include <TROOT.h>
// #include <TSystem.h>
// #include <ROOT/TProcessExecutor.hxx>
#include <omp.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include "CillindricalBoltzmannGibbs.hpp"
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

void MultifitBoltzmann(int argc, char** argv) {
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
    // #pragma omp parallel for shared(pids, mass, xdata, ydata, xerrs, yerrs, parindexes)
    // #pragma omp parallel for num_threads(12)
    for (int ic = 0; ic < nc; ++ic) {
        std::vector<double> parinit = {1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0};

        Chi2 chi2;
        chi2.SetParindexes(parindexes);
        chi2.SetData(xdata, ydata[ic], xerrs, yerrs[ic]);
        chi2.SetSpecies({211, 321, 2212});
        chi2.SetFitRange(fitrange);
        chi2.SetFitFunction(BoltzmannGibbs::Cillindrical::Function, 5);

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
    }

    std::vector<std::map<int, std::shared_ptr<TGraphErrors>>> hists(nc);
    std::vector<std::map<int, std::shared_ptr<TF1>>> fitfunctions(nc);
    std::vector<std::map<int, std::shared_ptr<TF1>>> fitfunctions_scaled(nc);

    // std::vector<int> pids = {211, 321, 2212};
    std::map<int, std::vector<double>> ranges;
    ranges[211] = {0.1, 3};
    ranges[321] = {0.2, 3};
    ranges[2212] = {0.3, 3};
    std::map<int, double> scalefactor;
    scalefactor[211] = 1;
    scalefactor[321] = 1;
    scalefactor[2212] = 1;
    scalefactor[0] = std::exp2(11);
    scalefactor[1] = std::exp2(10);
    scalefactor[2] = std::exp2(9);
    scalefactor[3] = std::exp2(8);
    scalefactor[4] = std::exp2(7);
    scalefactor[5] = std::exp2(6);
    scalefactor[6] = std::exp2(5);
    scalefactor[7] = std::exp2(4);
    scalefactor[8] = std::exp2(3);
    scalefactor[9] = std::exp2(2);
    scalefactor[10] = 1;
    for (int ic = 0; ic < nc; ++ic) {
        for (int ip = 0; ip < pids.size(); ++ip) {
            int pid = pids[ip];

            fitfunctions[ic][pid] = std::make_shared<TF1>("", BoltzmannGibbs::Cillindrical::Function, ranges[pid][0], ranges[pid][1], 5);
            for (int p = 0; p < 5; ++p) {
                // std::cout << finalparams[ic][parindexes[ip][p]] << std::endl;
                fitfunctions[ic][pid]->SetParameter(p, finalparams[ic][parindexes[pid][p]]);
            }
            fitfunctions_scaled[ic][pid] = std::make_shared<TF1>("", [fitfunctions, ic, pid, scalefactor](double* x, double* params) { return scalefactor.at(ic) * fitfunctions[ic].at(pid)->Eval(x[0]); }, ranges[pid][0], ranges[pid][1], 0);

            hists[ic][pid] = std::make_shared<TGraphErrors>(
                xdata[pid].size(), xdata[pid].data(), ydata[ic][pid].data(), xerrs[pid].data(), yerrs[ic][pid].data());
            // std::cout << hists[ic][pid]->GetPointY(0) << std::endl;
            hists[ic][pid]->Scale(scalefactor[ic]);
            // std::cout << hists[ic][pid]->GetPointY(0) << std::endl;
        }
    }

    std::map<int, int> histcolors;
    histcolors[0] = 2;
    histcolors[1] = 3;
    histcolors[2] = 4;
    histcolors[3] = 5;
    histcolors[4] = 6;
    histcolors[5] = 7;
    histcolors[6] = 8;
    histcolors[7] = 9;
    histcolors[8] = 30;
    histcolors[9] = 31;
    histcolors[10] = 32;

    std::map<int, RGB> rgbcolors;
    rgbcolors[0] = RGB(201, 42, 42);
    rgbcolors[1] = RGB(253, 126, 20);
    rgbcolors[2] = RGB(255, 192, 120);
    rgbcolors[3] = RGB(192, 235, 117);
    rgbcolors[4] = RGB(140, 233, 154);
    rgbcolors[5] = RGB(56, 217, 169);
    rgbcolors[6] = RGB(102, 217, 232);
    rgbcolors[7] = RGB(77, 171, 247);
    rgbcolors[8] = RGB(34, 139, 230);
    rgbcolors[9] = RGB(24, 100, 171);
    rgbcolors[10] = RGB(95, 61, 196);

    std::map<int, int> tcolors;
    for (auto entry : rgbcolors) {
        TColor::SetColorThreshold(0.1);
        tcolors[entry.first] = TColor::GetColor((int)entry.second.r, (int)entry.second.g, (int)entry.second.b);

        // std::cout
        //     << tcolors[entry.first] << std::endl;
    }

    TApplication app("app", &argc, argv);

    std::shared_ptr<TCanvas> canvas = std::make_shared<TCanvas>();

    canvas->SetLogx();
    canvas->SetLogy();
    std::shared_ptr<TGraph> Frame = std::make_shared<TGraph>(1);

    Frame->GetXaxis()->SetLimits(0.1, 3);
    Frame->GetYaxis()->SetRangeUser(1E-2, 1E7);
    Frame->Draw("AP");

    int pid = 211;
    for (int ic = 0; ic < nc; ++ic) {
        fitfunctions_scaled[ic][pid]->Draw("L SAME");
        //     // fitfunctions[ic][pid]->Draw("L SAME");
        fitfunctions_scaled[ic][pid]->SetLineColor(kBlack);

        // TColor markerColor(colori, rgbcolors[ic].r / 255.0, rgbcolors[ic].g / 255.0, rgbcolors[ic].b / 255.0);

        hists[ic][pid]->SetMarkerColor(tcolors[ic]);
        hists[ic][pid]->SetMarkerStyle(20);

        hists[ic][pid]->SetLineColor(tcolors[ic]);
        hists[ic][pid]->SetLineStyle(1);

        hists[ic][pid]->Draw("P SAME");
        // hists[ic][pid]->SetMarkerColor(histcolors[ic]);
        // hists[ic][pid]->SetLineColor(histcolors[ic]);

        // fitfunctions[ic][pid]->SetLineColor(kBlack);
    }
    // hists[0][211]->Draw("SAME");

    // fhist->Draw("SAME");
    canvas->Modified();
    canvas->Update();

    app.Run();
}

void MultifitTsallis(int argc, char** argv) {
    Datamap xdata;
    std::vector<Datamap> ydata;
    Datamap xerrs;
    std::vector<Datamap> yerrs;
    read_data(xdata, ydata, xerrs, yerrs);
    // std::cout << "after" << std::endl;
    Indexmap parindexes =
        {{211, {0, 3, 4, 7, 8, 9, 10}},
         {321, {1, 3, 5, 7, 8, 9, 10}},
         {2212, {2, 3, 6, 7, 8, 9, 10}}};

    std::vector<int> pids = {211, 321, 2212};
    std::map<int, double> masses = {{211, 0.140}, {321, 0.498}, {2212, 0.938}};
    Datamap fitrange =
        {
            {211, {0.5, 1}},
            {321, {0.2, 1.5}},
            {2212, {0.3, 3.0}}};

    size_t nc = std::stoi(argv[1]);  // ydata[211].size();
    // std::cout << ydata[211].size() << std::endl;
    // std::vector<bool> errorstate(nc);
    std::vector<std::vector<double>> finalparams(nc);
    // #pragma omp parallel for shared(pids, mass, xdata, ydata, xerrs, yerrs, parindexes)
    // #pragma omp parallel for num_threads(12)
    for (int ic = 0; ic < nc; ++ic) {
        // std::cout << ic << std::endl;

        Chi2 chi2;
        chi2.SetParindexes(parindexes);
        chi2.SetData(xdata, ydata[ic], xerrs, yerrs[ic]);
        chi2.SetSpecies({211, 321, 2212});
        chi2.SetFitRange(fitrange);
        chi2.SetFitFunction(Tsallis::Cillindrical::Function, 7);

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
        // std::cout << ic << std::endl;
    }

    std::vector<std::map<int, std::shared_ptr<TGraphErrors>>> hists(nc);
    std::vector<std::map<int, std::shared_ptr<TF1>>> fitfunctions(nc);
    std::vector<std::map<int, std::shared_ptr<TF1>>> fitfunctions_scaled(nc);

    // std::vector<int> pids = {211, 321, 2212};
    std::map<int, std::vector<double>> ranges;
    ranges[211] = {0.1, 3};
    ranges[321] = {0.2, 3};
    ranges[2212] = {0.3, 3};
    std::map<int, double> scalefactor;
    scalefactor[211] = 1;
    scalefactor[321] = 1;
    scalefactor[2212] = 1;
    scalefactor[0] = std::exp2(11);
    scalefactor[1] = std::exp2(10);
    scalefactor[2] = std::exp2(9);
    scalefactor[3] = std::exp2(8);
    scalefactor[4] = std::exp2(7);
    scalefactor[5] = std::exp2(6);
    scalefactor[6] = std::exp2(5);
    scalefactor[7] = std::exp2(4);
    scalefactor[8] = std::exp2(3);
    scalefactor[9] = std::exp2(2);
    scalefactor[10] = 1;
    for (int ic = 0; ic < nc; ++ic) {
        for (int ip = 0; ip < pids.size(); ++ip) {
            int pid = pids[ip];

            fitfunctions[ic][pid] = std::make_shared<TF1>("", Tsallis::Cillindrical::Function, ranges[pid][0], ranges[pid][1], 7);
            for (int p = 0; p < 7; ++p) {
                // std::cout << finalparams[ic][parindexes[ip][p]] << std::endl;
                fitfunctions[ic][pid]->SetParameter(p, finalparams[ic][parindexes[pid][p]]);
            }
            fitfunctions_scaled[ic][pid] = std::make_shared<TF1>("", [fitfunctions, ic, pid, scalefactor](double* x, double* params) { return scalefactor.at(ic) * fitfunctions[ic].at(pid)->Eval(x[0]); }, ranges[pid][0], ranges[pid][1], 0);

            hists[ic][pid] = std::make_shared<TGraphErrors>(
                xdata[pid].size(), xdata[pid].data(), ydata[ic][pid].data(), xerrs[pid].data(), yerrs[ic][pid].data());
            // std::cout << hists[ic][pid]->GetPointY(0) << std::endl;
            hists[ic][pid]->Scale(scalefactor[ic]);
            // std::cout << hists[ic][pid]->GetPointY(0) << std::endl;
        }
    }

    std::map<int, int> histcolors;
    histcolors[0] = 2;
    histcolors[1] = 3;
    histcolors[2] = 4;
    histcolors[3] = 5;
    histcolors[4] = 6;
    histcolors[5] = 7;
    histcolors[6] = 8;
    histcolors[7] = 9;
    histcolors[8] = 30;
    histcolors[9] = 31;
    histcolors[10] = 32;

    std::map<int, RGB> rgbcolors;
    rgbcolors[0] = RGB(201, 42, 42);
    rgbcolors[1] = RGB(253, 126, 20);
    rgbcolors[2] = RGB(255, 192, 120);
    rgbcolors[3] = RGB(192, 235, 117);
    rgbcolors[4] = RGB(140, 233, 154);
    rgbcolors[5] = RGB(56, 217, 169);
    rgbcolors[6] = RGB(102, 217, 232);
    rgbcolors[7] = RGB(77, 171, 247);
    rgbcolors[8] = RGB(34, 139, 230);
    rgbcolors[9] = RGB(24, 100, 171);
    rgbcolors[10] = RGB(95, 61, 196);

    std::map<int, int> tcolors;
    for (auto entry : rgbcolors) {
        TColor::SetColorThreshold(0.1);
        tcolors[entry.first] = TColor::GetColor((int)entry.second.r, (int)entry.second.g, (int)entry.second.b);

        // std::cout
        //     << tcolors[entry.first] << std::endl;
    }

    TApplication app("app", &argc, argv);

    std::shared_ptr<TCanvas> canvas = std::make_shared<TCanvas>();

    canvas->SetLogx();
    canvas->SetLogy();
    std::shared_ptr<TGraph> Frame = std::make_shared<TGraph>(1);

    Frame->GetXaxis()->SetLimits(0.1, 3);
    Frame->GetYaxis()->SetRangeUser(1E-2, 1E7);
    Frame->Draw("AP");

    int pid = 211;
    for (int ic = 0; ic < nc; ++ic) {
        fitfunctions_scaled[ic][pid]->Draw("L SAME");
        //     // fitfunctions[ic][pid]->Draw("L SAME");
        fitfunctions_scaled[ic][pid]->SetLineColor(kBlack);

        // TColor markerColor(colori, rgbcolors[ic].r / 255.0, rgbcolors[ic].g / 255.0, rgbcolors[ic].b / 255.0);

        hists[ic][pid]->SetMarkerColor(tcolors[ic]);
        hists[ic][pid]->SetMarkerStyle(20);

        hists[ic][pid]->SetLineColor(tcolors[ic]);
        hists[ic][pid]->SetLineStyle(1);

        hists[ic][pid]->Draw("P SAME");
        // hists[ic][pid]->SetMarkerColor(histcolors[ic]);
        // hists[ic][pid]->SetLineColor(histcolors[ic]);

        // fitfunctions[ic][pid]->SetLineColor(kBlack);
    }
    // hists[0][211]->Draw("SAME");

    // fhist->Draw("SAME");
    canvas->Modified();
    canvas->Update();

    app.Run();
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

void MultifitBoltzmannNoPlot(int argc, char** argv) {
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
    // #pragma omp parallel for shared(pids, mass, xdata, ydata, xerrs, yerrs, parindexes)
    // #pragma omp parallel for num_threads(12)
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
    for (int ic = 0; ic < nc; ++ic) {
        std::vector<double> parinit = {1, 1, 1, 0.11, 0.138, 0.498, 0.938, 0.5, 1.0};

        Chi2 chi2;
        chi2.SetParindexes(parindexes);
        chi2.SetData(xdata, ydata[ic], xerrs, yerrs[ic]);
        chi2.SetSpecies({211, 321, 2212});
        chi2.SetFitRange(fitrange);
        chi2.SetFitFunction(BoltzmannGibbs::Cillindrical::Function, 5);

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
    }
    std::vector<FitResults> JSONResults(nc);
    nlohmann::json file;

    size_t npar = defaultfitsettings.ParameterFixed.size();

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
        for (int ipar = 0; ipar < npar; ++ipar) {
            JSONResults[ic].ParameterValues[ipar] = finalresults[ic].GetParams()[ipar];
            JSONResults[ic].ParameterErrors[ipar] = finalresults[ic].GetErrors()[ipar];
            JSONResults[ic].ParameterNames[ipar] = finalresults[ic].GetParameterName(ipar);
        }

        for (int ipar = 0; ipar < npar; ++ipar) {
            for (int jpar = 0; jpar < npar; ++jpar) {
                JSONResults[ic].CorrelationMatrix[ipar][jpar] = finalresults[ic].CovMatrix(ipar, jpar);
            }
        }
        JSONResults[ic].GenerateJSON();
        file["centrality"][centralitylabels[ic]] = JSONResults[ic].j;
    }
    std::ofstream outFile("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-bgbwd-1.json");
    if (outFile.is_open()) {
        outFile << file.dump(4);  // Dump the JSON object to the file with an indentation of 4 spaces
        outFile.close();
    } else {
        throw std::runtime_error("Could not open file for writing");
    }
}

void MultifitTsallisNoPlot(int argc, char** argv) {
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
    // #pragma omp parallel for shared(pids, mass, xdata, ydata, xerrs, yerrs, parindexes)
    // #pragma omp parallel for num_threads(12)
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
    for (int ic = 0; ic < nc; ++ic) {
        Chi2 chi2;
        chi2.SetParindexes(parindexes);
        chi2.SetData(xdata, ydata[ic], xerrs, yerrs[ic]);
        chi2.SetSpecies({211, 321, 2212});
        chi2.SetFitRange(fitrange);
        chi2.SetFitFunction(Tsallis::Cillindrical::Function, 7);

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
    }
    std::vector<FitResults> JSONResults(nc);
    nlohmann::json file;

    size_t npar = defaultfitsettings.ParameterFixed.size();
    // size_t nfree = 0;
    // for (int i = 0; i < npar; ++i) {
    //     if (!defaultfitsettings.ParameterFixed[i]) {
    //         nfree++;
    //     }
    // }
    // std::cout << finalresults[0].NPar() << std::endl;
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
        for (int ipar = 0; ipar < npar; ++ipar) {
            JSONResults[ic].ParameterValues[ipar] = finalresults[ic].GetParams()[ipar];
            JSONResults[ic].ParameterErrors[ipar] = finalresults[ic].GetErrors()[ipar];
            JSONResults[ic].ParameterNames[ipar] = finalresults[ic].GetParameterName(ipar);
        }

        for (int ipar = 0; ipar < npar; ++ipar) {
            for (int jpar = 0; jpar < npar; ++jpar) {
                JSONResults[ic].CorrelationMatrix[ipar][jpar] = finalresults[ic].CovMatrix(ipar, jpar);
            }
        }
        JSONResults[ic].GenerateJSON();
        file["centrality"][centralitylabels[ic]] = JSONResults[ic].j;
    }
    std::ofstream outFile("/home/lieuwe/Documents/Software/articles/1910.07678/processed/dNptdptdy-fitresults-tbwd-1.json");
    if (outFile.is_open()) {
        outFile << file.dump(4);  // Dump the JSON object to the file with an indentation of 4 spaces
        outFile.close();
    } else {
        throw std::runtime_error("Could not open file for writing");
    }
}

int main(int argc, char* argv[]) {
    MultifitBoltzmannNoPlot(argc, argv);
    MultifitTsallisNoPlot(argc, argv);
    // MultifitMT(argc, argv);
    // MultifitTsallis(argc, argv);
    return 0;
}